
#include <string.h>
#include <vector>
#include <stdio.h>
#include <cassert>
#include <stdexcept>
#include "univalue.h"

using namespace std;

void UniValue::read(const char *raw)
{
    clear();

    bool expectName = false;
    bool expectColon = false;
    vector<UniValue*> stack;

    while (*raw) {
        switch (*raw) {

        case '{':
        case '[': {
            VType utyp = (*raw == '{' ? VOBJ : VARR);
            if (!stack.size()) {
                setObject();
                stack.push_back(this);
            } else {
                UniValue tmpVal(utyp);
                UniValue *top = stack.back();
                top->values.push_back(tmpVal);

                UniValue *newTop = &(top->values.back());
                stack.push_back(newTop);
            }

            if (utyp == VOBJ)
                expectName = true;

            raw++;
            break;
            }

        case '}':
        case ']': {
            if (!stack.size() || expectColon)
                throw runtime_error("json parse: unexpected }]");

            VType utyp = (*raw == '}' ? VOBJ : VARR);
            UniValue *top = stack.back();
            if (utyp != top->getType())
                throw runtime_error("json parse: mismatched }]");

            stack.pop_back();
            expectName = false;

            raw++;
            break;
            }

        case ':': {
            if (!stack.size() || expectName || !expectColon)
                throw runtime_error("json parse: : stack empty or want name");

            UniValue *top = stack.back();
            if (top->getType() != VOBJ)
                throw runtime_error("json parse: : parent not object");

	    expectColon = false;

            raw++;
            break;
            }

        case ',': {
            if (!stack.size() || expectName || expectColon)
                throw runtime_error("json parse: , stack empty or want name");

            UniValue *top = stack.back();
            if (top->getType() == VOBJ)
                expectName = true;

            raw++;
            break;
            }

        case 'n':
        case 't':
        case 'f': {
            if (!stack.size() || expectName || expectColon)
                throw runtime_error("json parse: ntf stack empty or want name");

            VType utyp;
            if (!strncmp(raw, "null", 4)) {
                utyp = VNULL;
                raw += 4;
            } else if (!strncmp(raw, "true", 4)) {
                utyp = VTRUE;
                raw += 4;
            } else if (!strncmp(raw, "false", 5)) {
                utyp = VFALSE;
                raw += 5;
            } else
                throw runtime_error("json parse: ntf unknown keyword");

            UniValue tmpVal(utyp);
            UniValue *top = stack.back();
            top->values.push_back(tmpVal);

            break;
            }

        case '-':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9': {
            if (!stack.size() || expectName || expectColon)
                throw runtime_error("json parse digits: stack empty or want name");

            // part 1: int
            string numStr;

            const char *first = raw;

	    const char *firstDigit = first;
	    if (!isdigit(*firstDigit))
	        firstDigit++;
            if (*firstDigit == '0')
                throw runtime_error("json parse digits 1.5: first digit bad");

            numStr += *raw;                       // copy first char
            raw++;

            if ((*first == '-') && (!isdigit(*raw)))
                throw runtime_error("json parse digits 2: first char bad");

            while ((*raw) && isdigit(*raw)) {     // copy digits
                numStr += *raw;
                raw++;
            }

            // part 2: frac
            if (*raw == '.') {
                numStr += *raw;                   // copy .
                raw++;

                if (!isdigit(*raw))
                    throw runtime_error("json parse digits 3: want digit");
                while ((*raw) && isdigit(*raw)) { // copy digits
                    numStr += *raw;
                    raw++;
                }
            }

            // part 3: exp
            if (*raw == 'e' || *raw == 'E') {
                numStr += *raw;                   // copy E
                raw++;

                if (*raw == '-' || *raw == '+') { // copy +/-
                    numStr += *raw;
                    raw++;
                }

                if (!isdigit(*raw))
                    throw runtime_error("json parse digits 4: want digit");
                while ((*raw) && isdigit(*raw)) { // copy digits
                    numStr += *raw;
                    raw++;
                }
            }

            UniValue tmpVal(VNUM, numStr);
            UniValue *top = stack.back();
            top->values.push_back(tmpVal);

            break;
            }

        case '"': {
            if (!stack.size())
                throw runtime_error("json parse string: stack empty");

            raw++;                                // skip "

            string valStr;

            while (*raw) {
                if (*raw < 0x20)
                    throw runtime_error("json parse string: have ctl chars");

                else if (*raw == '\\') {
                    raw++;                        // skip backslash

                    switch (*raw) {
                    case '"':  valStr += "\""; break;
                    case '\\': valStr += "\\"; break;
                    case '/':  valStr += "/"; break;
                    case 'b':  valStr += "\b"; break;
                    case 'f':  valStr += "\f"; break;
                    case 'n':  valStr += "\n"; break;
                    case 'r':  valStr += "\r"; break;
                    case 't':  valStr += "\t"; break;
                    case 'u':
                        // TODO: not supported yet
                        assert(0);
                        break;
                    default:
                        throw runtime_error("json parse string: unknown escape");

                    }

                    raw++;                        // skip esc'd char
                }

                else if (*raw == '"') {
                    raw++;                        // skip "
                    break;                        // stop scanning
                }

                else {
                    valStr += *raw;
                    raw++;
                }
            }

            UniValue *top = stack.back();

            if (expectName) {
                top->keys.push_back(valStr);
                expectName = false;
		expectColon = true;
            } else {
                UniValue tmpVal(VSTR, valStr);
                top->values.push_back(tmpVal);
            }

            break;
            }

        case ' ':
        case '\t':
        case '\f':
        case '\r':
        case '\n':
            raw++;                                // skip whitespace
            break;

	default:
            throw runtime_error("json parse string: illegal expression");
        }
    }

    if (stack.size() != 0) {
        char msg[64];
        sprintf(msg, "json parse: too many toplevel obj, %lu", stack.size());
        throw runtime_error(msg);
    }
}


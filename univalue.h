#ifndef __BITCOIN_UNIVALUE_H__
#define __BITCOIN_UNIVALUE_H__

#include <stdint.h>
#include <string>
#include <vector>
#include <cassert>

class UniValue {
public:
    enum VType { VNULL, VOBJ, VARR, VSTR, VNUM, VTRUE, VFALSE, };

    UniValue() { typ = VNULL; }
    UniValue(UniValue::VType initialType, const std::string& initialStr = "") {
        typ = initialType;
        val = initialStr;
    }
    UniValue(int64_t val_) {
        setInt(val_);
    }
    ~UniValue() {}

    void clear();

    bool setNull();
    bool setBool(bool val);
    bool setNumStr(std::string val);
    bool setInt(int64_t val);
    bool setFloat(double val);
    bool setStr(std::string val);
    bool setArray();
    bool setObject();

    enum VType getType() { return typ; }
    std::string getValStr() { return val; }

    bool isNull() { return (typ == VNULL); }
    bool isTrue() { return (typ == VTRUE); }
    bool isFalse() { return (typ == VFALSE); }
    bool isBool() { return (typ == VTRUE || typ == VFALSE); }
    bool isStr() { return (typ == VSTR); }
    bool isNum() { return (typ == VNUM); }
    bool isArray() { return (typ == VARR); }
    bool isObject() { return (typ == VOBJ); }

    bool push(UniValue& val);
    bool push(const std::string& val_) {
        UniValue tmpVal(VSTR, val_);
        return push(tmpVal);
    }

    bool pushKV(std::string key, UniValue& val);
    bool pushKV(std::string key, const std::string val) {
        UniValue tmpVal(VSTR, val);
        return pushKV(key, tmpVal);
    }
    bool pushKV(std::string key, int64_t val) {
        UniValue tmpVal(val);
        return pushKV(key, tmpVal);
    }

    std::string write(unsigned int prettyIndent = 0,
                      unsigned int indentLevel = 0);

    void read(const char *raw);

private:
    UniValue::VType typ;
    std::string val;                       // numbers are stored as C++ strings
    std::vector<std::string> keys;
    std::vector<UniValue> values;

    void writeOpen(unsigned int prettyIndent, unsigned int indentLevel, std::string& s);
    void writeClose(unsigned int prettyIndent, unsigned int indentLevel, std::string& s);
    void writeArray(unsigned int prettyIndent, unsigned int indentLevel, std::string& s);
    void writeObject(unsigned int prettyIndent, unsigned int indentLevel, std::string& s);
};

#endif // __BITCOIN_UNIVALUE_H__

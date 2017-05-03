// Copyright 2017 Bloq, Inc.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <stdint.h>
#include <string>

#include "univalue.h"

bool UniValue::erase(size_t idx)
{
    if ((typ != VARR) && (typ != VOBJ))
        return false;   // nothing removed

    if (idx >= values.size())
        return false;   // nothing removed

    if (typ == VOBJ)
        keys.erase(keys.begin() + idx);
    values.erase(values.begin() + idx);

    return true;        // at least one value removed
}

bool UniValue::erase(const std::string& key)
{
    size_t idx = 0;
    if ((typ != VOBJ) || (!findKey(key, idx)))
        return false;   // nothing removed

    keys.erase(keys.begin() + idx);
    values.erase(values.begin() + idx);

    return true;        // at least one value removed
}


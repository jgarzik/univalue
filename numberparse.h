// Copyright 2015 Bitcoin Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef __UNIVALUE_NUMBERPARSE_H__
#define __UNIVALUE_NUMBERPARSE_H__

#include <stdint.h>
#include <ctype.h>

#include <string>

static bool ParsePrechecks(const std::string& str);
bool ParseInt32(const std::string& str, int32_t *out);
bool ParseInt64(const std::string& str, int64_t *out);
bool ParseDouble(const std::string& str, double *out);

#endif //__UNIVALUE_NUMBERPARSE_H__
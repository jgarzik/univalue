/**
 * @file univalue.h
 * @brief Header file of univalue library.
 *
 *
 * Copyright 2014 BitPay Inc.
 * Copyright 2015 Bitcoin Core Developers
 * Distributed under the MIT software license, see the accompanying
 * file COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#ifndef __UNIVALUE_H__
#define __UNIVALUE_H__

#include <stdint.h>
#include <string.h>

#include <string>
#include <vector>
#include <map>
#include <cassert>

#include <sstream>        // .get_int64()
#include <utility>        // std::pair

/*!
 * UniValue class
 */
class UniValue {
public:
    /** Enum of UniValue types
     *
     */
    enum VType {
        VNULL,  /**< Empty value type */
        VOBJ,   /**< Object value type */
        VARR,   /**< Array value type */
        VSTR,   /**< String value type */
        VNUM,   /**< Number value type */
        VBOOL,  /**< Booleam value type */
    };

    /**
     * Default constructor.
     * Default constructor initializes the instance with empty object of \a VNULL type.
     */
    UniValue() { typ = VNULL; }

    /**
     * Constructor with given type and value.
     * @param initialType The intial type of this UniValue object.
     * @param intialStr Optional initial value, empty string by default.
     * @see UniValue::VType
     */
    UniValue(UniValue::VType initialType, const std::string& initialStr = "") {
        typ = initialType;
        val = initialStr;
    }

    /**
     * Constructor with given unsigned 64 bit integer value.
     * The type of created object will be \a VNUM.
     * @param val_ A uint64_t type of value.
     * @see setInt()
     */
    UniValue(uint64_t val_) {
        setInt(val_);
    }

    /**
     * Constructor with given signed 64 bit integer value.
     * The type of created object will be \a VNUM.
     * @param val_ A int64_t type of value.
     * @see setInt()
     */
    UniValue(int64_t val_) {
        setInt(val_);
    }

    /**
     * Constructor with given boolean value.
     * The type of created object will be \a VBOOL.
     * @param val_ A boolean value.
     * @see setBool()
     */
    UniValue(bool val_) {
        setBool(val_);
    }

    /**
     * Constructor with given int value.
     * The type of created object will be \a UniValue::VNUM.
     * @param val_ A int value.
     * @see setInt()
     */
    UniValue(int val_) {
        setInt(val_);
    }

    /**
     * Constructor with given double value.
     * The type of created object will be \a UniValue::VNUM.
     * @param val_ A double value.
     * @see setFloat()
     */
    UniValue(double val_) {
        setFloat(val_);
    }

    /**
     * Constructor with given string value.
     * The type of created object will be \a UniValue::VSTR.
     * @param val_ A STL string value.
     * @see setStr()
     */
    UniValue(const std::string& val_) {
        setStr(val_);
    }

    /**
     * Constructor with given string value.
     * The type of created object will be \a UniValue::VSTR.
     * @param val_ A null terminated string value.
     * @see setStr()
     */
    UniValue(const char *val_) {
        std::string s(val_);
        setStr(s);
    }

    /**
     * Destructor
     */
    ~UniValue() {}

    /**
     * Reset the object to be null object.
     * @see UniValue::VNULL
     * @see setNull()
     */
    void clear();

    /**
     * Reset the object to be null object.
     * @see UniValue::VNULL
     * @see clear()
     * @return true for success, otherwise false
     */
    bool setNull();

    /**
     * Set the object to be boolean type object with \a val as value.
     * @param val the boolean value to be stored in object.
     * @return true for success, oterwise false.
     */
    bool setBool(bool val);

    /**
     * Set the object to be number type with given string \a val as value.
     * @param val a number string.
     * @return true if given value was valid number, otherwise false.
     * @see UniValue::VNUM
     */
    bool setNumStr(const std::string& val);

    /**
     * Set the object to be number type with given \a val as value.
     * @param val a uint64_t value.
     * @return true if success, otherwise false.
     * @see setNumStr()
     * @see UniValue::VNUM
     */
    bool setInt(uint64_t val);

    /**
     * Set the object to be number type with given \a val as value.
     * @param val as int64_t value.
     * @return true if sccess, otherwise false.
     * @set setNumStr()
     * @see UniValue::VNUM
     */
    bool setInt(int64_t val);

    /**
     * Set the object to be number type with given \a val as value.
     * @param val as int value.
     * return true if success, otherwise false.
     * @see setNumStr()
     * @see UniValue::VNUM
     */
    bool setInt(int val_) { return setInt((int64_t)val_); }

    /**
     * Set the object to be number type with given \a val as value.
     * The precision stored internally is 16.
     *
     * @param val as double value.
     * @return true if success, otherwise false.
     * @see setNumStr()
     */
    bool setFloat(double val);

    /**
     * Set the object to be string type with given \a val as value.
     * @param val as std::string value.
     * @return true if success, otherwise false.
     * @see UniValue::VSTR
     */
    bool setStr(const std::string& val);

    /**
     * Set the object to be empty array type.
     * @return true if success, otherwise false.
     * @see UniValue::VARR
     */
    bool setArray();

    /**
     * Set the object to be empty object type.
     * @return true if success, otherwise false.
     * @see UniValue::VOBJ
     */
    bool setObject();

    /**
     * Get the current stored value type.
     * @return the actual stored value type.
     * @see UniValue::VType
     */
    enum VType getType() const { return typ; }

    /**
     * Get the stored value as string.
     * @return the string value of stored value type.
     */
    const std::string& getValStr() const { return val; }

    /**
     * Check if the object stored any child elements.
     * Only possible true if the value types were UniValue::VARR or
     * UniValue::VOBJ and had added child elements.
     * @return true if no child elements stored, otherwise return false.
     * @see isArray()
     * @see isObject()
     */
    bool empty() const { return (values.size() == 0); }

    /**
     * Return the children value count
     * @return the actual size of added child elements.
     */
    size_t size() const { return values.size(); }

    /**
     * Get the stored value as boolean.
     * @return true if the stored type is UniValue::VBOOL and value is true,
     * otherwise false.
     * @see isTrue()
     * @see get_bool()
     */
    bool getBool() const { return isTrue(); }

    /**
     * Check the object stores all keys of given \a memberTypes.
     * @param memberTypes key to key type map.
     * @return true if the object stored was object type and all keys could be found
     * inside this object and also the types of these found keys were same, otherwise return false.
     * @see UniValue::VType
     * @see isObject()
     */
    bool checkObject(const std::map<std::string,UniValue::VType>& memberTypes);

    /**
     * Access child value by given \a key.
     * @param key the key string value to be searched.
     * @return constant reference of child value object if key was found, otherwise retun Null value object.
     * @see exists()
     */
    const UniValue& operator[](const std::string& key) const;

    /**
     * Access child value of array object by given \a index.
     * @param index the index position of child value object.
     * @return constant reference of child value object if index was valid and parent object is array type, otherwise retun Null value object.
     * @see UniValue::VARR
     */
    const UniValue& operator[](size_t index) const;

    /**
     * Check if the given \a key is exists in this object or not.
     * @param key the key string to be searched for.
     * @return true if the \a key could be found, otherwise return false.
     * @see findKey()
     */
    bool exists(const std::string& key) const { size_t i; return findKey(key, i); }

    /**
     * Check if the object is a null object.
     * @return true if object is null object, otherwise false.
     * @see UniValue::VNULL
     */
    bool isNull() const { return (typ == VNULL); }

    /**
     * Check if the object holds a 'true' boolean value.
     * @return true if the object is boolean object and value is 'true', otherwise return false.
     * @see UniValue::VBOOL
     * @see isFalse()
     * @see isBool()
     */
    bool isTrue() const { return (typ == VBOOL) && (val == "1"); }

    /**
     * Check if the object holds a 'false' boolean value.
     * @return true if the object is boolean object and value is 'false', otherwise return false.
     * @see UniValue::VBOOL
     * @see isTrue()
     * @see isBool()
     */
    bool isFalse() const { return (typ == VBOOL) && (val != "1"); }

    /**
     * Check if the object holds a boolean value.
     * @return true if the object is a boolean object, otherwise return false.
     * @see UniValue::VBOOL
     */
    bool isBool() const { return (typ == VBOOL); }

    /**
     * Check if the object holds a string value.
     * @return true if the object is a string object, otherwise return false.
     * @see UniValue::VSTR
     */
    bool isStr() const { return (typ == VSTR); }

    /**
     * Check if the object holds a numeric value.
     * @return true if the object is a number object, otherwise return false.
     * @see UniValue::VNUM
     */
    bool isNum() const { return (typ == VNUM); }

    /**
     * Check if the object is an array object.
     * A 'Array' object can holds a list of children elements.
     * @return true if the object is an array object, otherwise return false.
     * @see UniValue::VARR
     */
    bool isArray() const { return (typ == VARR); }

    /**
     * Check if the value object is an 'Object' type object.
     * An 'Object' value type can holds a list of key<=>value pairs as its children elements.
     * @return true if the value object is an 'Object' type object, otherwise return false.
     * @see UniValue::VOBJ
     */
    bool isObject() const { return (typ == VOBJ); }

    /**
     * Append the given \a val value object to the array object's children list.
     * @return true if this object is array object and given \a val was added successfully, otherwise return false.
     *
     * @see isArray()
     */
    bool push_back(const UniValue& val);

    /**
     * Append the given std::string \a val_ as a child value object to the array object's children list.
     * @retrurn true if this object is array object and given string \a val_ was added successfully, otherwise return false.
     * @see isArray()
     */
    bool push_back(const std::string& val_) {
        UniValue tmpVal(VSTR, val_);
        return push_back(tmpVal);
    }

    /**
     * Append the given null terminated string \a val_ as a child value object to the array object's children list.
     * @return true if this object is array object and given \a val_ was added successfully, otherwise return false.
     * @see isArray()
     */
    bool push_back(const char *val_) {
        std::string s(val_);
        return push_back(s);
    }

    /**
     *
     */
    bool push_back(uint64_t val_) {
        UniValue tmpVal(val_);
        return push_back(tmpVal);
    }

    /**
     *
     */
    bool push_back(int64_t val_) {
        UniValue tmpVal(val_);
        return push_back(tmpVal);
    }

    /**
     *
     */
    bool push_back(int val_) {
        UniValue tmpVal(val_);
        return push_back(tmpVal);
    }
    bool push_back(double val_) {
        UniValue tmpVal(val_);
        return push_back(tmpVal);
    }

    /**
     * Merge given list of value objects into this object.
     * Append the list of value objects into this array object's children list and return true, if this object is not a array, return false.
     * @see push_back()
     * @see isArray()
     * @see UniValue::VARR
     */
    bool push_backV(const std::vector<UniValue>& vec);

    /**
     *
     */
    bool pushKV(const std::string& key, const UniValue& val);

    /**
     *
     */
    bool pushKV(const std::string& key, const std::string& val_) {
        UniValue tmpVal(VSTR, val_);
        return pushKV(key, tmpVal);
    }

    /**
     *
     */
    bool pushKV(const std::string& key, const char *val_) {
        std::string _val(val_);
        return pushKV(key, _val);
    }

    /**
     *
     */
    bool pushKV(const std::string& key, int64_t val_) {
        UniValue tmpVal(val_);
        return pushKV(key, tmpVal);
    }

    /**
     *
     */
    bool pushKV(const std::string& key, uint64_t val_) {
        UniValue tmpVal(val_);
        return pushKV(key, tmpVal);
    }

    /**
     *
     */
    bool pushKV(const std::string& key, int val_) {
        UniValue tmpVal((int64_t)val_);
        return pushKV(key, tmpVal);
    }

    /**
     *
     */
    bool pushKV(const std::string& key, double val_) {
        UniValue tmpVal(val_);
        return pushKV(key, tmpVal);
    }

    /**
     *
     */
    bool pushKVs(const UniValue& obj);

    /**
     * Serialize this object as JSON string.
     * @param prettyIndent
     * @param indentLevel
     * @return the serialized JSON string.
     * @see read()
     */
    std::string write(unsigned int prettyIndent = 0,
                      unsigned int indentLevel = 0) const;

    /**
     * Convert the given null terminated JSON string \raw into UniValue object.
     * @param raw the null terminated string which contains JSON content.
     * @param len the maximum accepted string length.
     * @return true if converted successfully, otherwise return false.
     * @see write()
     */
    bool read(const char *raw, size_t len);

    /**
     * Convert the given null terminated JSON string \raw into UniValue object.
     * Note: strlen() is used to detemine the actual string size.
     * @param raw the null terminated string which contains JSON content.
     * @return true if converted successfully, otherwise return false.
     * @see write()
     * @see strlen()
     */
    bool read(const char *raw) { return read(raw, strlen(raw)); }

    /**
     * Convert the given JSON string \a rawStr into UniValue object.
     * @param rawStr
     * @return true if converted successfully, otherwise return false.
     */
    bool read(const std::string& rawStr) {
        return read(rawStr.data(), rawStr.size());
    }

private:
    UniValue::VType typ;
    std::string val;                       // numbers are stored as C++ strings
    std::vector<std::string> keys;
    std::vector<UniValue> values;

    bool findKey(const std::string& key, size_t& retIdx) const;
    void writeArray(unsigned int prettyIndent, unsigned int indentLevel, std::string& s) const;
    void writeObject(unsigned int prettyIndent, unsigned int indentLevel, std::string& s) const;

public:
    // Strict type-specific getters, these throw std::runtime_error if the
    // value is of unexpected type
    /**
     *
     */
    const std::vector<std::string>& getKeys() const;
    /**
     *
     */
    const std::vector<UniValue>& getValues() const;
    /**
     *
     */
    bool get_bool() const;
    /**
     *
     */
    const std::string& get_str() const;
    /**
     *
     */
    int get_int() const;
    /**
     *
     */
    int64_t get_int64() const;
    /**
     *
     */
    double get_real() const;
    /**
     *
     */
    const UniValue& get_obj() const;
    /**
     *
     */
    const UniValue& get_array() const;

    /**
     *
     * @see getType()
     */
    enum VType type() const { return getType(); }
    /**
     *
     */
    bool push_back(std::pair<std::string,UniValue> pear) {
        return pushKV(pear.first, pear.second);
    }
    /**
     *
     */
    friend const UniValue& find_value( const UniValue& obj, const std::string& name);
};

//
// The following were added for compatibility with json_spirit.
// Most duplicate other methods, and should be removed.
//
static inline std::pair<std::string,UniValue> Pair(const char *cKey, const char *cVal)
{
    std::string key(cKey);
    UniValue uVal(cVal);
    return std::make_pair(key, uVal);
}

static inline std::pair<std::string,UniValue> Pair(const char *cKey, std::string strVal)
{
    std::string key(cKey);
    UniValue uVal(strVal);
    return std::make_pair(key, uVal);
}

static inline std::pair<std::string,UniValue> Pair(const char *cKey, uint64_t u64Val)
{
    std::string key(cKey);
    UniValue uVal(u64Val);
    return std::make_pair(key, uVal);
}

static inline std::pair<std::string,UniValue> Pair(const char *cKey, int64_t i64Val)
{
    std::string key(cKey);
    UniValue uVal(i64Val);
    return std::make_pair(key, uVal);
}

static inline std::pair<std::string,UniValue> Pair(const char *cKey, bool iVal)
{
    std::string key(cKey);
    UniValue uVal(iVal);
    return std::make_pair(key, uVal);
}

static inline std::pair<std::string,UniValue> Pair(const char *cKey, int iVal)
{
    std::string key(cKey);
    UniValue uVal(iVal);
    return std::make_pair(key, uVal);
}

static inline std::pair<std::string,UniValue> Pair(const char *cKey, double dVal)
{
    std::string key(cKey);
    UniValue uVal(dVal);
    return std::make_pair(key, uVal);
}

static inline std::pair<std::string,UniValue> Pair(const char *cKey, const UniValue& uVal)
{
    std::string key(cKey);
    return std::make_pair(key, uVal);
}

static inline std::pair<std::string,UniValue> Pair(std::string key, const UniValue& uVal)
{
    return std::make_pair(key, uVal);
}

enum jtokentype {
    JTOK_ERR        = -1,
    JTOK_NONE       = 0,                           // eof
    JTOK_OBJ_OPEN,
    JTOK_OBJ_CLOSE,
    JTOK_ARR_OPEN,
    JTOK_ARR_CLOSE,
    JTOK_COLON,
    JTOK_COMMA,
    JTOK_KW_NULL,
    JTOK_KW_TRUE,
    JTOK_KW_FALSE,
    JTOK_NUMBER,
    JTOK_STRING,
};

extern enum jtokentype getJsonToken(std::string& tokenVal,
                                    unsigned int& consumed, const char *raw, const char *end);
extern const char *uvTypeName(UniValue::VType t);

static inline bool jsonTokenIsValue(enum jtokentype jtt)
{
    switch (jtt) {
    case JTOK_KW_NULL:
    case JTOK_KW_TRUE:
    case JTOK_KW_FALSE:
    case JTOK_NUMBER:
    case JTOK_STRING:
        return true;

    default:
        return false;
    }

    // not reached
}

static inline bool json_isspace(int ch)
{
    switch (ch) {
    case 0x20:
    case 0x09:
    case 0x0a:
    case 0x0d:
        return true;

    default:
        return false;
    }

    // not reached
}

extern const UniValue NullUniValue;

const UniValue& find_value( const UniValue& obj, const std::string& name);

#endif // __UNIVALUE_H__

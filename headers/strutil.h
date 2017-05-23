/**
 * @file strutil.h
 * The file containing the string utilities namespace declaration.
 */
#ifndef SIC_XE_ASSEMBLER_STRUTIL_H
#define SIC_XE_ASSEMBLER_STRUTIL_H
/*!
*  \addtogroup Utilities\String Utilities
*  @{
*/
//! A utilities namespace which is dedicated to support some utility functions with strings.
namespace strutil {
    /**
     * Splits the line read from the assembly file using regex pattern and returns a vector of strings contains the
     * individual strings forming this line.
     * @param str - A string represents the line read from the assembly file.
     * @param regex - A regex pattern which is used to match (split) the passed string.
     * @param splitsNumber - The maximum number of individual strings which can be
     * formed from splitting this passed string.
     * @return - A vector of strings represents the individual strings split from this passed string.
     */
    std::vector<std::string> split(std::string str, std::regex &regex, int splitsNumber = 3);

    /**
     * Matches a passed string against a passed regex pattern.
     * @param str - A string which is required to be matched against the passed regex pattern.
     * @param regex - A regex pattern which is used to match the passed string against it.
     * @return true if the passed string matches the passed regex pattern else it returns false.
     */
    bool matches(std::string str, std::regex regex);

    /**
     * Checks whether a string ends with a another string.
     * @param value - A string which is required to be checked.
     * @param ending -A string which is required to check for its existence at the end of another passed string "value".
     * @return true if string "value" contains string "ending" at its end else it returns false.
     */
    bool endsWith(std::string const &value, std::string const &ending);

    /**
     * Checks whether a string begins with a another string.
     * @param value - A string which is required to be checked.
     * @param ending -A string which is required to check for its existence at the beginning
     * of another passed string "value".
     * @return true if string "value" contains string "beginning" at its beginning else it returns false.
     */
    bool beginWith(std::string const &value, std::string const &beginning);

    /**
     * Converts a decimal number to its equivalent in hexadecimal system and appends
     * it to a string stream and adjust its alignment to right-alignment in a field of custom width passed as parameter also.
     * @param stringStream - A string stream which is required to append this converted number
     * to it to be printed in further operations.
     * @param decimalNumber - An decimal number which is required to be converted to
     * its equivalent in hexadecimal system and appended to the string stream.
     * @param numChars - An integer which represents the width of the required field in a string stream.
     */
    void addHex(std::ostringstream& stringStream, int decimalNumber, int numChars);

    /**
     * Parses the given character literal to a string contains the actual value of the literal.
     * @param charLiteral - A string contains character literal which is required to be parsed.
     * @return - A string contains the actual value of the passed character literal.
     */
    std::string parseCharLiteral(std::string charLiteral);

    /**
     * Checks whether the passed literal is a character literal, returns true if this case is met:
    * <ul>
    * <li> The passed literal matches the character literal's regex.</li>
    * </ul>
    * @param charLiteral - The character literal which is required to check if it is valid or not.
    * @return true if the passed literal is valid character literal else it returns false.
    */
    bool isCharLiteral(std::string charLiteral);

    /**
     * Coverts the letters' case of the passed string to uppercase.
     * @param str - A string whose letters' case is required to be converted to uppercase.
     * @return A string after converting its letters' case to uppercase.
     */
    std::string toUpper(std::string str);

    /**
     * Encodes a character string to a hexadecimal string.
     * @param str - A string which is required to be encoded.
     * @return A string which represents the encoded equivalent of the character string.
     */
    std::string toHex(std::string str);

    bool isValidInteger(std::string str);

    bool isValidHexadecimal(std::string str);
};

/*!
*  \addtogroup Utilities\File Utilities
*  @{
*/
//! A utilities namespace which is dedicated to support some utility functions with files.
namespace fileutil {

    /**
     * Removing the extension "format" part of the file's name passed to the function as a string.
     * @param str A string which represents the file's name.
     * @return A string which contains the part of the file's name split if "." is
     * found in it else it returns the passed string as it is.
     */
    std::string removeExtension(std::string str);
}

#endif //SIC_XE_ASSEMBLER_STRUTIL_H

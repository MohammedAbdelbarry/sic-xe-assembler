//
// Created by salem.harby on 05/04/2017.
//

#ifndef SIC_XE_ASSEMBLER_STRUTIL_H
#define SIC_XE_ASSEMBLER_STRUTIL_H

/*!
*  \addtogroup Utilities
*  @{
*/
//! A utilities namespace which is dedicated to support some utility functions with strings.
namespace strutil {

    /**
     * Splits the line read from the assembly file using regex pattern and return a vector of strings contains the
     * individual strings forming this line.
     * @param str - A string represents the line read from the assembly file.
     * @param regex - A regex pattern which is used to match (split) the given string.
     * @param splitsNumber - The maximum number of individual strings which can be
     * formed from splitting this passed string
     * @return - A vector of strings represents the individual strings split from this passed string.
     */
    std::vector<std::string> split(std::string str, std::regex &regex, int splitsNumber = 3);

    /**
     * Matches a passed string against a passed regex pattern.
     * @param str - A string represents the given string which is required to be matched against the given regex.
     * @param regex - A regex pattern which is required to be used to match the passed string against it.
     * @return true if the passed string matches the passed regex pattern.
     */
    bool matches(std::string str, std::regex regex);

    /**
     * Checks whether a string ends with a another string.
     * @param value - A string which is required to be checked.
     * @param ending -A string which is required to check whether it is present at the end of string "value" or not.
     * @return returns true if string "value" contains string "ending" at its end else it returns true.
     */
    bool endsWith(std::string const &value, std::string const &ending);

    /**
     * Checks whether a string begins with a another string.
     * @param value - A string which is required to be checked.
     * @param ending -A string which is required to check whether it is present at the beginning of string "value" or not.
     * @return returns true if string "value" contains string "beginning" at its beginning else it returns true.
     */
    bool beginWith(std::string const &value, std::string const &beginning);

    /**
     *
     * @param stringStream
     * @param decimalNumber
     * @param numChars
     */
    void addHex(std::ostringstream& stringStream, int decimalNumber, int numChars);

    /**
     *
     * @param charLiteral
     * @return
     */
    std::string parseCharLiteral(std::string charLiteral);

    /**
     *
     * @param charLiteral
     * @return
     */
    bool isCharLiteral(std::string charLiteral);

    /**
     *
     * @param str
     * @return
     */
    std::string toUpper(std::string str);
};

namespace fileutil {
    std::string removeExtension(std::string str);
}

#endif //SIC_XE_ASSEMBLER_STRUTIL_H

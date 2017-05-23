/**
 * @file numutil.h
 * The file containing the numerical utilities namespace declaration.
 */
#ifndef SIC_XE_ASSEMBLER_UTIL_H
#define SIC_XE_ASSEMBLER_UTIL_H
/*!
*  \addtogroup Utilities
*  @{
*/
//! A utilities namespace which is dedicated to support some utility functions with numbers in different bases.
namespace numutil {
    /*!
     * \addtogroup Utilities/Numerical Utilities
     * @{
     */
    //! A namespace dedicated to perform different operations on hexadecimal numbers (Integers mainly).
    namespace Hexadecimal {

        /**
         * Converts a hexadecimal number to its equivalent in binary system.
         * @param number - A hexadecimal number which is required to be converted to a binary number.
         * @return A string contains the binary equivalent of the passed hexadecimal number.
         */
        std::string toBin(std::string number);

        /**
         * Converts a hexadecimal number to its equivalent in decimal system.
         * @param number - A hexadecimal number which is required to be converted to a decimal number.
         * @return An integer represents the decimal equivalent of the passed hexadecimal number.
         */
        int toDec(std::string number);

        /**
         * Parses the given hexadecimal literal to a string contains the actual hexadecimal value.
         * @param hexLiteral - A string contains hexadecimal literal which is required to be parsed.
         * @return A string contains the actual hexadecimal value of the passed hexadecimal literal.
         */
        std::string parseHexadecimalLiteral(std::string hexLiteral);

        /**
         * Checks whether the passed literal is a hexadecimal literal, returns true if this case is met:
         * <ul>
         * <li> The passed literal matches the hexadecimal literal's regex.</li>
         * </ul>
         * @param hexLiteral - The hexadecimal literal which is required to check if it is valid or not.
         * @return true if the passed literal is valid hexadecimal literal else it returns false.
         */
        bool isHexLiteral(std::string hexLiteral);

        /**
         * Decodes a hexadecimal string to a character string.
         * @param hexString - A string which is required to be decoded.
         * @return A string which represents the decoded equivalent of the hexadecimal string.
         */
        std::string toString(std::string hexString);
    }

    /*!
     * \addtogroup Utilities/Numerical Utilities
     * @{
     */
    //! A namespace dedicated to perform different operations on decimal numbers (Integers mainly).
    namespace Decimal {

        /**
         * Parses a decimal number as string.
         * @param number - A decimal number which is required to be parsed as a string.
         * @return the decimal number parsed as a string.
         */
        std::string toString(int number);

        /**
         * Converts a decimal number to its equivalent in binary system.
         * @param number - A decimal number which is required to be converted to a binary number.
         * @return A string contains the binary equivalent of the passed decimal number.
         */
        std::string toBin(int number);

        /**
         * Converts a decimal number to its equivalent in hexadecimal system.
         * @param number - A decimal number which is required to be converted to a hexadecimal number.
         * @return A string contains the hexadecimal equivalent of the passed decimal number.
         */
        std::string toHex(int number);
    }

    /*!
     * \addtogroup Utilities/Numerical Utilities
     * @{
     */
    //! A namespace dedicated to perform different operations on binary numbers (Integers mainly).
    namespace Binary {

        /**
         * Converts a binary number to its equivalent in decimal system.
         * @param number - A binary number which is required to be converted to a decimal number.
         * @return An integer represents the decimal equivalent of the passed binary number.
         */
        int toDec(std::string number);

        /**
         * Converts a binary number to its equivalent in hexadecimal system.
         * @param number - A binary number which is required to be converted to a hexadecimal number.
         * @return A string contains the hexadecimal equivalent of the passed binary number.
         */
        std::string toHex(std::string number);
    }
}

#endif //SIC_XE_ASSEMBLER_UTIL_H

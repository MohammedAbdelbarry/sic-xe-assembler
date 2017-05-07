//
// Created by salem.harby on 05/01/2017.
//

#ifndef SIC_XE_ASSEMBLER_VALIDATOR_H
#define SIC_XE_ASSEMBLER_VALIDATOR_H


namespace validator {

    /**
     * Checks whether a line is valid or not. doesn't throw an error if all these cases are met:
     * <ul>
     * <li> line's label is valid.</li>
     * <li> line's operation is valid.</li>
     * <li> line's operand is valid.</li>
     * <li> line's comment is valid.</li>
     * </ul>
     * @param line - line to be checked passed in the form of string
     */
    void validateLine(Line &line);

    /**
     * Checks whether a line's format is valid or not. doesn't throw an error if relevant cases are met:
     * <ul>
     * <li> line's format is format 1 and line's operand is empty.</li>
     * <li> line's format is format 2 (Not supported yet).</li>
     * <li> line's format is format 3 and line's operand isn't empty.</li>
     * <li> line's format is format 4 and line's operand isn't empty and its operation doesn't start with "+" also.</li>
     * </ul>
     * @param line - line to be checked passed in the form of string
     */
    void validateFormat(Line &line);
};


#endif //SIC_XE_ASSEMBLER_VALIDATOR_H

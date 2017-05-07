/**
 * @file line.h
 * The file containing the line class declaration.
 */
#ifndef SIC_XE_ASSEMBLER_LINE_H
#define SIC_XE_ASSEMBLER_LINE_H
class Error;
/**
 * The line class.
 */
class Line {
public:
    /**
     * Default no-args constructor of line class objects.
     */
    Line();

    /**
     * Constructor of line class objects and it is used when an assembly statement
     * is detected while reading an assembly file in pass one.
     * @param label - A string represents the label of an assembly statement.
     * @param operation - A string represents the operation of an assembly statement.
     * @param operand - A string represents the operand of an assembly statement.
     * @param comment - A string represents the comment of an assembly statement.
     */
    Line(std::string label, std::string operation, std::string operand, std::string comment);

    /**
     * Constructor of line class objects and it is used when a comment line
     * is detected while reading an assembly file in pass one.
     * @param comment - A string represents the line itself (The comment).
     */
    Line(std::string comment);

    /**
     * Destructor of the line class objects.
     */
    ~Line();

    /**
     * A string to store the label of an assembly statement (left empty if it is a comment line).
     */
    std::string label;

    /**
     * A string to store the operation of an assembly statement (left empty if it is a comment line).
     */
    std::string operation;

    /**
     * A string to store the operand of an assembly statement (left empty if it is a comment line).
     */
    std::string operand;

    /**
     * A string to store the comment attached to the end of a line
     * if it is an assembly statement or a line's string itself if it is a comment line.
     */
    std::string comment;

    /**
     * A MnemonicType enum to store the type of the mnemonic (Instruction or directive)
     * of a line if and only if the line is of type assembly statement.
     */
    MnemonicType mnemonicType;

    /**
     * An integer to store the current location counter of a line.
     */
    int locCtr;

    /**
     * An error object to store the information of a line's error if it exists.
     */
    Error *error;

    /**
     * A boolean value to indicate whether the target address of this assembly statement is calculated in
     * indexed mode ot direct mode
     */
    bool isIndexed;

    /**
     * An instructionFormat enum to store the supported format of an assembly statement.
     */
    InstructionFormat lineFormat;

    /**
     * A getter "accessor" for the type of a line object.
     * @return An enumeration represents the type of the line whether it is an assembly statement or a comment line.
     */
    LineType getLineType() const;

private:

    /**
     * Overloads the operator "<<" to make the line object printable by defining
     * the operations to be done when line object is appended to a stream using this operator.
     * @param stream - A stream which will contain the printable information of the line object.
     * @param line - A line object which is required to be appended to a stream.
     * @return A stream object after appending the required line's information to it.
     */
    friend std::ostream& operator<<(std::ostream& stream, const Line& line);

    /**
     * A LineType enum to store the type of a line whether it is an assembly statement or a comment line.
     */
    LineType lineType;
};

#endif //SIC_XE_ASSEMBLER_LINE_H

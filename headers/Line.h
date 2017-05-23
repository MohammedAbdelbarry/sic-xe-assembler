//
// Created by Mohamed A.Tolba on 5/1/2017.
//

#ifndef SIC_XE_ASSEMBLER_LINE_H
#define SIC_XE_ASSEMBLER_LINE_H

class Error;
class Line {
public:
    Line();
    Line(std::string label, std::string operation, std::string operand, std::string comment);
    Line(std::string comment);
    ~Line();
    std::string label;
    std::string operation;
    std::string operand;
    std::string comment;
    std::string objCode;
    MnemonicType mnemonicType;
    LineType getLineType() const;
    int locCtr;
    Error *error;
    bool isIndexed;
    InstructionFormat lineFormat;
private:
    friend std::ostream& operator<<(std::ostream& stream, const Line& line);
    LineType lineType;
};

#endif //SIC_XE_ASSEMBLER_LINE_H

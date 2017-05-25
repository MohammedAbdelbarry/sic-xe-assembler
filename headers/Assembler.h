/**
 * @file Assembler.h
 * The file containing the assembler class declaration.
 */
#ifndef SIC_XE_ASSEMBLER_ASSEMBLER_H
#define SIC_XE_ASSEMBLER_ASSEMBLER_H

#include <string>
#include <map>

/**
 * The assembler singleton class.
 */
class Assembler {

public:
    /**
     * Gets the assembler singleton instance.
     * @return The assembler singleton instance.
     */
    static Assembler *getInstance();

    /**
     * Attempts to assemble a file and writes
     * the object code if the file was assembled successfully.
     * @param filePath The path of the file to be assembled.
     * @param options The command line options.
     */
    void execute(std::string filePath, std::map<std::string, std::string> options);

private:
    /**
     * Constructs a new Assembler instance.
     */
    Assembler();

    /**
     * The assembler singleton instance.
     */
    static Assembler *instance;
    /**
     * The current value of the location counter.
     */
    int locCtr;
};

#endif //SIC_XE_ASSEMBLER_ASSEMBLER_H

#ifndef FORMATTER_H
#define FORMATTER_H

#include <iostream>
#include <fstream>

class Formatter {
    public:
        // Constructor
        Formatter();
        // Destructor
        ~Formatter();
        // Method - Open file stream
        void openFile(std::string file);
        // Method - Close file stream
        void clean();
        // Method - Get item name
        std::string getItemName(ushort id);
        // Method - Format the input file
        void formatFile();
    private:
        // Input file stream
        std::ifstream inStream;
        // Output file stream
        std::ofstream outStream;
        // File name
        std::string fileName;
};
#endif // FORMATTER_H
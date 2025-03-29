#include "formatter.h"
#include <iostream>
#include <filesystem>

// Constructor
Formatter::Formatter() {
}

// Destructor
Formatter::~Formatter() {
    inStream.close();
    outStream.close();
    std::cout << "Destroying Formatter object" << std::endl;
}

// Method - open file stream
void Formatter::openFile(std::string file) {
    inStream.open(file);

    if (!inStream.is_open()) {
        // Output Error Message
        std::cerr << "Error: Unable to open file stream" << std::endl;
        return;
    }

    size_t pos = file.find_last_of("/\\");
    fileName = (pos == std::string::npos) ? file : file.substr(pos + 1);
    std::cout << "Reading file stream: " << fileName << std::endl;
}

// Method - Close file stream
void Formatter::clean() {
    inStream.close();
    outStream.close();
}

// Method - Get item name
std::string Formatter::getItemName(ushort id) {
    std::ifstream itemsStream;
    size_t startPos, endPos;
    std::string itemName;
    std::string line;

    itemsStream.open("items.xml");
    if (!itemsStream.is_open()) {
        // Output Error Message
        throw std::runtime_error("Unable to open item file stream");
    }

    std::getline(itemsStream, line);
    itemName = "unknown";

    while (std::getline(itemsStream, line)) {
        if (line.find(std::format("id=\"{0}\"", std::to_string(id))) != std::string::npos) {
            startPos = line.find("name=") + 6;
            endPos = line.find("\"", startPos);
            itemName = line.substr(startPos, endPos - startPos);
        }
    }

    return std::format(" <!-- {0} -->", itemName);
}

// Method - Format input file
void Formatter::formatFile() {
    int indent = 0;                                  // Declare an indent variable
    std::string line;                                // Declare a line buffer

    outStream.open("output/" + fileName);            // Open output file stream
    std::getline(inStream, line);                    // Read the first line (header)
    outStream << line << std::endl;                  // Write the first line (header)

    while (std::getline(inStream, line)) {

        // If the line is empty, then skip to the next line:
        if (line.find_first_not_of(" \t\n\v\f\r") != std::string::npos) {
            line = line.substr(line.find("<"), line.find(">", line.find("<")) - line.find("<") + 1);
        }
        else { 
            continue; 
        }

        // If the line contains a closing block tag "</tag>", then it is a block closing tag:
        if (line.find("</") != std::string::npos) {
            indent -= (indent > 0) ? 4 : 0;
            line.insert(0, std::string(indent, ' '));
        }
        // If the opening tag does not contain a closing tag "/>", then it is a block tag:
        else if (line.find("/>") == std::string::npos) {
            line.insert(0, std::string(indent, ' '));
            indent += 4;
        }
        // If the opening tag contains a closing tag "/>", then it is a self-closing tag:
        else {
            line.insert(0, std::string(indent, ' '));
        }

        // If the opening tag is "<item ", then it is an item tag:
        if (line.find("<item") != std::string::npos) {
            try {
                if (line.find("id=") == std::string::npos) {
                    throw std::runtime_error("Id attribute not found");
                }
                ushort id = std::stoi(line.substr(line.find("id=") + 4, line.find(" ") - 1));
                line.insert(line.length(), getItemName(id));
            } catch(std::exception& a) {
                std::cerr << "Warning on line: " << line << std::endl << a.what() << std::endl;
            }
        }

        // Write the line to the output file stream
        outStream << line << std::endl;
    }
    // std::cout << "Formatting file: " << fileName << " complete " <<std::endl;
}
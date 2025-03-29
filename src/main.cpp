#include <iostream>
#include "formatter.h"

int main(int argc, char* argv[]) {
    if (argc == 2) {
        // Initialize the Formatter object
        Formatter formatter;

        // Check if argv[1] is a file or directory
        if (std::filesystem::is_directory(argv[1])) {
            std::cout << "Directory: " << argv[1] << std::endl;
            try {
                for (const auto& entry : std::filesystem::directory_iterator(argv[1])) {
                    if (entry.is_regular_file()) {
                        formatter.openFile(entry.path().string());
                        formatter.formatFile();
                        formatter.clean();
                    }
                }
            } catch (const std::filesystem::filesystem_error& e) {
                std::cerr << "Filesystem error: " << e.what() << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "General error: " << e.what() << std::endl;
            }
        }
        else if (std::filesystem::is_regular_file(argv[1])) {
            std::cout << "File: " << argv[1] << std::endl;
            formatter.openFile(argv[1]);
            formatter.formatFile();
            formatter.clean();
        }
    }
    else {
        std::cerr << "Usage: " << argv[0] << " <file/directory>" << std::endl;
    }

    return 0;
}

// Plan

// 1. Initialize the Formatter object
//     a. If a file path is not provided, then check the "Input" directory for .xml files
//     b. If the file is provided, then open the file stream for that individual file
//     c. Store the file name in the filename variable
// 2. Create a file with the same name as the filename variable in the "Output" directory
// 3. Read the first line of the input file stream and write it to the output file stream
// 4. Iterate through the input file stream line by line until the end of the file
// 5. Concatenate the line buffer
//     a. Add Whitespace to the line buffer based on the value of indent variable
//     b. Add a newline character at the end of the line buffer
// 6. Check for the following conditions:
//     a. If the opening tag does not contain a closing tag "/>", then it is a block tag:
//         - Increment the indent by 4
//     b. If the opening tag contains a closing tag "/>", then it is a self-closing tag:
//         - Increment the indent by 0
//     c. If the line contains a closing block tag "</tag>", then it is a block closing tag:
//         - Decrement the indent by 4
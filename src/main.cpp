#include <iostream>
#include "formatter.h"

int main(int argc, char* argv[]) {
    // Check for the correct usage
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file/directory>" << std::endl;
        return -1;
    }
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
    return 0;
}
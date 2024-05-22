#include <iostream>
#include <fstream>

int main() {
    std::ofstream outfile("output.txt");
    if (outfile.is_open()) {
        outfile << "Hello world!" << std::endl;
        outfile.close();
        std::cout << "Message written to output.txt" << std::endl;
    } else {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }
    return 0;
}


#include <iostream>
#include <string>

#include "readfile.h"
#include "sha3.h"

int main()
{
    try
    {
        std::cout << std::endl;

        std::string filename;
        std::cout << "Path to the file to hash: ";
        std::cin >> filename;
        std::cout << std::endl;
        std::string data = readFile(filename);

        int output_length;
        std::cout << "SHA3 family (224, 256, 384, 512): ";
        std::cin >> output_length;
        std::cout << std::endl;
        if (
            output_length != 224 &&
            output_length != 256 &&
            output_length != 384 &&
            output_length != 512
        )
        {
            std::cerr << "Error: SHA3-" << output_length << " not implemented !" << std::endl;
            return 1;
        }
        std::vector<uint8_t> data_bytes(data.begin(), data.end());

        SHA3 sha3(output_length);
        std::vector<uint8_t> hash = sha3.hash(data_bytes);
        
        std::cout << "SHA3-" << output_length << " Hash: ";
        sha3.print_hash();
    } 
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
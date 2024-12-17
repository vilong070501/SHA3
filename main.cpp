#include "sha3.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Fonction pour lire tout le contenu du fichier
std::string readFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Impossible d'ouvrir le fichier : " + filename);
    }
    
    std::ostringstream oss;
    oss << file.rdbuf(); // Lit tout le contenu du fichier
    return oss.str();
}

int main()
{
    // std::string message = "Hello World!";
    // // std::string message = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla faucibus arcu metus, sit amet pharetra nunc sodales et. Morbi iaculis tincidunt lorem, eget consequat nunc rutrum faucibus. Vivamus in odio eros. Quisque erat eros, imperdiet sed dictum vel, bibendum eu turpis. Integer ligula nulla, ultrices in pretium in, consequat eu libero. In pulvinar lectus id malesuada sodales. Suspendisse ut vulputate justo.Proin ut arcu in mauris hendrerit lobortis. Sed pulvinar tempor commodo. Fusce erat quam, eleifend vel enim cursus, commodo auctor felis. Curabitur consectetur magna vel consectetur suscipit. Morbi a ex id sapien aliquet sodales. Quisque vitae neque eget sapien mollis tempus. Morbi eget lacus commodo, efficitur nulla in, vestibulum est. Fusce est ligula, semper sit amet nibh vitae, suscipit pharetra lectus. Sed nunc erat, consectetur in magna a, sodales mattis nulla. Phasellus a velit in turpis condimentum laoreet vitae eget risus. Sed commodo lorem neque, ac euismod turpis semper ac.Etiam tortor justo, ultrices non elementum vitae, vestibulum vitae nulla. Morbi vulputate, velit eget vulputate gravida, libero tortor consequat quam, non maximus diam est nec lorem. Integer porta ex augue, eget fringilla leo volutpat sit amet. Praesent a posuere urna, sed volutpat tellus. Nam posuere velit quis augue consequat fermentum. Nulla vel dui at nisi aliquet venenatis eget aliquam metus. Mauris faucibus, lorem viverra tempus malesuada, leo erat cursus ipsum, vitae pretium mauris lectus ut augue. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin mollis velit eget porta feugiat. Vestibulum viverra lectus non ante vestibulum faucibus. Sed mollis dictum lacinia. Aliquam ut mi consectetur arcu gravida venenatis vitae vitae orci. Suspendisse potenti.Vivamus congue vel nisi sit amet egestas. Maecenas ut maximus sapien. Aenean hendrerit lacus vel risus molestie posuere. Maecenas quis iaculis enim. Aenean porttitor, ipsum et varius varius, risus risus venenatis odio, a lobortis sem nisl vel mi. Sed mollis dui ex, ac egestas nunc ullamcorper sed. Praesent ligula erat, accumsan nec mi ultrices, ornare luctus magna. Nulla rhoncus orci nisi, non vestibulum lacus pellentesque eu. Praesent ut rhoncus velit, accumsan gravida tellus. Integer nulla urna, placerat a pulvinar in, fermentum et nibh. Ut posuere sapien ac augue tincidunt consectetur. Nam eget tristique libero. Fusce ac turpis ut tortor condimentum aliquet sit amet non urna. Sed condimentum odio vitae rutrum blandit. Ut fermentum posuere quam at euismod. Pellentesque molestie vitae lorem vitae rutrum.Curabitur mattis vel leo quis pretium. Morbi scelerisque, quam blandit blandit lacinia, ante orci tincidunt sem, in rutrum turpis nunc nec lorem. Mauris viverra odio purus, sit amet fermentum mi consectetur aliquet. Donec faucibus, magna ut congue posuere, velit ligula porta arcu, id tempus mauris urna at diam. Donec feugiat maximus neque vitae imperdiet. Nunc luctus nulla at ipsum bibendum, sit amet congue justo malesuada. Mauris consequat, libero at sodales accumsan, ante dui ultricies massa, sed consectetur elit ipsum commodo magna.";
    // // std::string message = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. ";
    // // std::string message = "A";
    // std::vector<uint8_t> message_bytes(message.begin(), message.end());
    // int output_length = 512;
    // SHA3 sha3(output_length);
    // std::vector<uint8_t> hash = sha3.compute(message_bytes);
    
    // std::cout << "Message: " << message << std::endl;
    // std::cout << "SHA3-512 Hash attendu: 32400b5e89822de254e8d5d94252c52bdcb27a3562ca593e980364d9848b8041b98eabe16c1a6797484941d2376864a1b0e248b0f7af8b1555a778c336a5bf48" << std::endl;
    // std::cout << "SHA3-512 Hash obtenu : ";
    
    // sha3.print_hash();

    try {
        // 1. Lire le fichier texte
        std::string filename = "text.txt";
        std::string data = readFile(filename);

        // 3. Calculer le hash SHA3-256
        int output_length = 256;
        std::vector<uint8_t> message_bytes(data.begin(), data.end());
        SHA3 sha3(output_length);
        std::vector<uint8_t> hash = sha3.compute(message_bytes);
        
        std::cout << "SHA3-256 Hash obtenu: ";
        sha3.print_hash();
    } catch (const std::exception &e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }

    return 0;
}
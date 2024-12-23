#include <iostream>
#include <vector>
#include <string>
#include <cstring> 
#include <iomanip>
#include <cctype>  

//  Base64
const std::string BASE64_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// Convertir un valor a bytes
std::vector<uint8_t> toBytes(uint64_t value, size_t size) {
    std::vector<uint8_t> bytes(size, 0);
    std::memcpy(bytes.data(), &value, size);
    return bytes;
}

// Codificar bytes en Base64
std::string base64Encode(const std::vector<uint8_t>& bytes) {
    std::string base64;
    int val = 0, bits = -6;
    const unsigned int mask = 0x3F;

    for (uint8_t byte : bytes) {
        val = (val << 8) + byte;
        bits += 8;
        while (bits >= 0) {
            base64.push_back(BASE64_CHARS[(val >> bits) & mask]);
            bits -= 6;
        }
    }

    if (bits > -6) {
        base64.push_back(BASE64_CHARS[((val << 8) >> (bits + 8)) & mask]);
    }

    while (base64.size() % 4) {
        base64.push_back('=');
    }
    return base64;
}

int main() {
    while (true) {
        std::string baseType;
        uint64_t inputValue;

        std::cout << "\n" << std::endl;
        std::cout << "Tipo de base (uint8, uint32, uint64) o 'Q': ";
        std::cin >> baseType;

        if (std::toupper(baseType[0]) == 'Q') {
            std::cout << "Quit" << std::endl;
            break;
        }

        std::cout << "Valor: ";
        std::cin >> inputValue;

        std::vector<uint8_t> bytes;
        if (baseType == "uint8") {
            if (inputValue > UINT8_MAX) {
                std::cerr << "Error: Valor fuera del rango para uint8.\n";
                continue;
            }
            bytes = toBytes(inputValue, sizeof(uint8_t));
        }
        else if (baseType == "uint32") {
            if (inputValue > UINT32_MAX) {
                std::cerr << "Error: Valor fuera del rango para uint32.\n";
                continue;
            }
            bytes = toBytes(inputValue, sizeof(uint32_t));
        }
        else if (baseType == "uint64") {
            bytes = toBytes(inputValue, sizeof(uint64_t));
        }
        else {
            std::cerr << "Error: Tipo de base no reconocido. Usa uint8, uint32 o uint64.\n";
            continue;
        }

        std::string base64Result = base64Encode(bytes);
        std::cout << "Resultado en base64: " << base64Result << std::endl;
    }

    return 0;
}

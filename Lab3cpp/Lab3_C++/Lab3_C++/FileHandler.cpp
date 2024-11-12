#include "FileHandler.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

FileHandler::FileHandler(const std::string& filename) : filename(filename) {}

std::vector<std::shared_ptr<Address>> FileHandler::LoadAddresses() {
    std::vector<std::shared_ptr<Address>> addresses;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string addressType;
            getline(iss, addressType, ':'); // Використовуємо ":" як роздільник

            std::string city, street;
            int buildingNumber, appartmentNumber;

            if (addressType == "Private" || addressType == "Private House") {
                iss >> city >> street >> buildingNumber;
                addresses.push_back(std::make_shared<PrivateHouse>(city, street, buildingNumber));
            }
            else if (addressType == "Appartment" || addressType == "Appartment Building") {
                iss >> city >> street >> buildingNumber >> appartmentNumber;
                addresses.push_back(std::make_shared<Appartment>(city, street, buildingNumber, appartmentNumber));
            }
            else {
                std::cerr << "Unrecognized address type: " << addressType << std::endl;
            }
        }
        file.close();
    }
    else {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
    return addresses;
}


void FileHandler::SaveAddress(const Address& address) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << address.toString() << std::endl;
        file.close();
    }
    else {
        std::cerr << "Error opening file for saving." << std::endl;
    }
}
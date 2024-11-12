#include "AddressBook.h"
//#include "FileHandler.h"
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>

AddressBook::AddressBook() {} 

void AddressBook::AddAddress(shared_ptr<Address> address) {
    addresses.push_back(address);
}

void AddressBook::AnalyzeAddresses() {
    int privateHouseCount = 0;
    int appartmentCount = 0;
    std::map<int, int> appartmentDistribution;

    if (selectedIndices.empty()) {
        std::cout << "There are no addresses selected for analysis." << std::endl;
        return;
    }

    for (int index : selectedIndices) {
        if (index >= 0 && index < addresses.size()) {
            const auto& address = addresses[index];
            if (address->GetType() == "Private House") {
                privateHouseCount++;
            }
            else if (address->GetType() == "Appartment") {
                appartmentCount++;
                int buildingNumber = dynamic_cast<Appartment*>(address.get())->GetBuildingNumber();
                appartmentDistribution[buildingNumber]++;
            }
        }
        else {
            std::cerr << "Warning: Invalid index " << index << " (out of range)" << std::endl;
        }
    }

    int buildingCount = appartmentDistribution.size();
    std::cout << "\nAnalysis Results:" << std::endl;
    std::cout << "Number of private houses: " << privateHouseCount << std::endl;
    std::cout << "Number of appartments: " << appartmentCount << std::endl;
    std::cout << "Number of unique buildings: " << buildingCount << std::endl;

    if (buildingCount > 0) {
        double averageAppartments = static_cast<double>(appartmentCount) / buildingCount;
        std::cout << "Average number of appartments per building: " << averageAppartments << std::endl;
        for (const auto& pair : appartmentDistribution) {
            std::cout << "Building " << pair.first << ": " << pair.second << " appartments" << std::endl;
        }
    }
    else if (appartmentCount > 0) {
        std::cout << "Warning: Apartments found but building numbers could not be determined." << std::endl;
    }
}

void AddressBook::DisplayAddresses() const {
    for (size_t i = 0; i < addresses.size(); i++) {
        std::cout << i + 1 << ": " << addresses[i]->toString() << std::endl;
    }
}

void AddressBook::SelectAddressesForMailing() {
    DisplayAddresses();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string inputStr;
    std::cout << "Enter the numbers of the addresses (separated by spaces) for mailing: ";
    std::getline(std::cin, inputStr);

    selectedIndices.clear();
    std::istringstream iss(inputStr);
    int number;
    while (iss >> number) {
        if (number > 0 && number <= addresses.size()) {
            selectedIndices.push_back(number - 1);
        }
        else {
            std::cout << "Invalid number: " << number << std::endl;
        }
    }

    if (!selectedIndices.empty()) {
        std::cout << "You have selected addresses with numbers: ";
        for (int index : selectedIndices) {
            std::cout << index + 1 << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "No addresses have been selected." << std::endl;
    }
}

void AddressBook::ClearAddresses() {
    addresses.clear();
}

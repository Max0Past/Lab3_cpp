#include "Ui.h"
#include "AddressBook.h" 
#include "FileHandler.h"
#include "PrivateHouse.h"
#include "Appartment.h"
#include <iostream>
UI::UI(AddressBook& addressBook, FileHandler& fileHandler)
    : addressBook(addressBook), fileHandler(fileHandler) {}

void UI::LoadAddresses() {
    addressBook.addresses.clear();
    addressBook.addresses = fileHandler.LoadAddresses();
    std::cout << "Addresses loaded successfully. Here is the list of addresses:" << std::endl;
    addressBook.DisplayAddresses();
}

void UI::AddPrivateAddress(const std::string& city, const std::string& street, int buildingNumber) {
    auto address = std::make_shared<PrivateHouse>(city, street, buildingNumber);
    addressBook.AddAddress(address);
    fileHandler.SaveAddress(*address);
}

void UI::AddAppartmentAddress(const std::string& city, const std::string& street, int buildingNumber, int appartmentNumber) {
    auto address = std::make_shared<Appartment>(city, street, buildingNumber, appartmentNumber);
    addressBook.AddAddress(address);
    fileHandler.SaveAddress(*address);
}

void UI::AnalyzeAddresses() {
    addressBook.AnalyzeAddresses();
}

void UI::SelectAddressesForMailing() {
    addressBook.SelectAddressesForMailing();
}

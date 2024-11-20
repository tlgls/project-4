#include "DocumentHandler.h"
#include <iostream>

// Helper function to increment the document count
void DocumentHandler::incrementDocumentCount(const std::string& document) {
    documentCounter[document]++;
}

void DocumentHandler::addPhrase(const std::string& word, const std::string& document) {
    incrementDocumentCount(document);
    phraseTree.insert(word, document);  // Inserts the word into the phrase AVL tree
}

void DocumentHandler::addOrganization(const std::string& word, const std::string& document) {
    incrementDocumentCount(document);
    organizationTree.insert(word, document);  // Inserts the word into the organization AVL tree
}

void DocumentHandler::addPerson(const std::string& word, const std::string& document) {
    incrementDocumentCount(document);
    personTree.insert(word, document);  // Inserts the word into the person AVL tree
}

void DocumentHandler::savePersistence() const {
    std::ofstream outFile("persistency_data.txt");

    outFile << phraseTree.getSize() << std::endl;
    phraseTree.printTree(outFile);

    outFile << organizationTree.getSize() << std::endl;
    organizationTree.printTree(outFile);

    outFile << personTree.getSize() << std::endl;
    personTree.printTree(outFile);

    outFile.close();
}

void DocumentHandler::loadPersistence() {
    std::ifstream inFile("persistency_data.txt");

    if (!inFile.is_open()) {
        std::cerr << "Failed to open the file!" << std::endl;
        exit(1);
    }

    int treeSize;
    // Load phrase tree
    inFile >> treeSize;
    for (int i = 0; i < treeSize; ++i) {
        std::string key;
        std::string value;
        inFile >> key >> value;
        phraseTree.insert(key, value);
    }

    // Load organization tree
    inFile >> treeSize;
    for (int i = 0; i < treeSize; ++i) {
        std::string key;
        std::string value;
        inFile >> key >> value;
        organizationTree.insert(key, value);
    }

    // Load person tree
    inFile >> treeSize;
    for (int i = 0; i < treeSize; ++i) {
        std::string key;
        std::string value;
        inFile >> key >> value;
        personTree.insert(key, value);
    }

    inFile.close();
}

std::map<std::string, int> DocumentHandler::getPhraseData(const std::string& word) const {
    return phraseTree.getNode(word);
}

std::map<std::string, int> DocumentHandler::getOrganizationData(const std::string& word) const {
    return organizationTree.getNode(word);
}

std::map<std::string, int> DocumentHandler::getPersonData(const std::string& word) const {
    return personTree.getNode(word);
}

int DocumentHandler::getDocumentFrequency(const std::string& document) const {
    if (documentCounter.find(document) != documentCounter.end()) {
        return documentCounter.at(document);
    }
    return 0;  // Return 0 if the document doesn't exist
}

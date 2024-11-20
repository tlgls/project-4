// Authored by Antonio Flores on 11/19/2024

#ifndef DOCUMENT_HANDLER_H
#define DOCUMENT_HANDLER_H

#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include "AVLTree.h"

// This class will handle document data using AVL trees for phrases, organizations, and people
class IndexHandler {
private:
    // Making AVL trees for phrases, organizations, and people
    AVLTree<std::string, std::string> phraseTree;
    AVLTree<std::string, std::string> organizationTree;
    AVLTree<std::string, std::string> personTree;

    // This is a map to count how many times each document appears
    std::map<std::string, int> documentCounter;

public:
    // Adds a phrase to the phrase tree and document counter
    void addPhrase(const std::string& word, const std::string& document);

    // Adds an organization to the organization tree and document counter
    void addOrganization(const std::string& word, const std::string& document);

    // Adds a person to the person tree and document counter
    void addPerson(const std::string& word, const std::string& document);

    // Saves the state of the trees to a file
    void savePersistence() const;

    // Loads data from the saved file into the trees
    void loadPersistence();

    // Retrieves phrase data for a specific word
    std::map<std::string, int> getPhraseData(const std::string& word) const;

    // Retrieves organization data 
    std::map<std::string, int> getOrganizationData(const std::string& word) const;

    // Retrieves person data
    std::map<std::string, int> getPersonData(const std::string& word) const;

   
    int getDocumentFrequency(const std::string& document) const;

    
    void incrementDocumentCount(const std::string& document);
};

#endif 

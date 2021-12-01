//! Unit Tests for MPAGSCipher Cipher Classes
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <string>

#include "CipherMode.hpp"
#include "CipherType.hpp"
#include "Cipher.hpp"
#include "CipherFactory.hpp"


bool testCipher(const Cipher& cipher, const CipherMode mode,
                const std::string& inputText, const std::string& outputText)
{
    return cipher.applyCipher(inputText, mode) == outputText;
}

TEST_CASE("Cipher en/decryption", "cipher tests")
{

    // create collection of Ciphers
    std::vector<std::unique_ptr<Cipher>> ciphers;
    // store test variables
    std::vector<std::string> plainText;
    std::vector<std::string> cipherText;
    std::vector<std::string> decryptText;

    // run test cases and store results
    ciphers.push_back(cipherFactory(CipherType::Caesar, "5"));
    plainText.push_back("HEYHOWAREYOU");
    cipherText.push_back("MJDMTBFWJDTZ");
    decryptText.push_back("HEYHOWAREYOU");

    ciphers.push_back(cipherFactory(CipherType::Playfair, "potato"));
    plainText.push_back("MANINTHESTREETSAYSHEY");
    cipherText.push_back(
        "LBQHRPKCRAXKKEYFAYKCZV");
    decryptText.push_back(
        "MANINTHESTREETSAYSHEYZ");

    ciphers.push_back(cipherFactory(CipherType::Vigenere, "muffinman"));
    plainText.push_back(
        "DUCKSGOQUACKQUACKQUARK");
    cipherText.push_back(
        "POHPATAQHMWPVCNOKDGUWP");
    decryptText.push_back(
        "DUCKSGOQUACKQUACKQUARK");
    
    for (size_t i{0}; i < ciphers.size(); ++i) {
        REQUIRE(ciphers[i]);
        REQUIRE(testCipher(*ciphers[i], CipherMode::Encrypt, plainText[i],
                           cipherText[i]));
        REQUIRE(testCipher(*ciphers[i], CipherMode::Decrypt, cipherText[i],
                           decryptText[i]));
    }
}

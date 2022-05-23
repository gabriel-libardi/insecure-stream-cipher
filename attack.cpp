#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int hex_value(unsigned char hex_digit)
{
    static const signed char hex_values[256] = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
         0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1, -1, -1, -1,
        -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    };
    int value = hex_values[hex_digit];
    if (value == -1) throw std::invalid_argument("invalid hex digit");
    return value;
}


string hex_to_string(const string& input) {
    const auto len = input.length();
    if (len & 1) throw invalid_argument("odd length");

    string output;
    output.reserve(len / 2);
    for (auto it = input.begin(); it != input.end(); )
    {
        int hi = hex_value(*it++);
        int lo = hex_value(*it++);
        output.push_back(hi << 4 | lo);
    }

    return output;
}


string generate_key(const string &beggining, const string& ciphertext) {
    string key;

    for (int index = 0; index < beggining.length(); index++) {
        cout << key.length() << "\n";
        key += (beggining[index])^(ciphertext[index]);
    }

    unsigned char last = 0;

    for (unsigned char character: key) {
        last += character;
    }

    key += last;
    cout << "ola\n";

    return key;
}


string decrypt(const string& ciphertext, const string& key) {
    string plaintext;
    int key_size = key.length();

    for (int index = 0; index < ciphertext.length(); index++) {
        plaintext += (ciphertext[index])^(key[index%key_size]);
    }

    return plaintext;
}


int main(int argc, char **argv) {
    cout << "Digite um começo provável da mensagem:\n";
    string beggining;
    getline(cin, beggining);
    cout << beggining << "\n";

    cout << "Digite o ciphertext em hexadecimal codificado em utf-8:\n";
    string ciphertext_hex;
    cin >> ciphertext_hex;

    string ciphertext = hex_to_string(ciphertext_hex);
    string key = generate_key(beggining, ciphertext);
    cout << key << "|\n";

    string plaintext = decrypt(ciphertext, key);
    cout << plaintext << "\n";
}
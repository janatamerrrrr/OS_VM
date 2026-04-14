#include <iostream>
#include <openssl/des.h>
#include <ctime>
#include <cstring>

using namespace std;

//function takes pass and salt, schedule a list of 16 mini-keys derived from the key itself
string encrypt25(string password, string salt) {
    DES_cblock key;
    DES_key_schedule schedule;

    // 8 first char (64-bit)
    memset(key, 0, 8);
    memcpy(key, password.c_str(), min((size_t)8, password.size()));
    DES_set_key_unchecked(&key, &schedule);

    string data = password + salt;

    // if not 8 make it 8 by adding a space
    while (data.size() < 8)
        data += ' ';
    //encrypt 25 times
    for (int i = 0; i < 25; i++) {
        DES_cblock input, output;

        memcpy(input, data.c_str(), 8);
        DES_ecb_encrypt(&input, &output, &schedule, DES_ENCRYPT);

        memcpy(&data[0], output, 8);
    }

    return data;
}

//generate 2 random letters from A-Z salt
string getSalt() {
    string s = "";
    s += char(rand() % 26 + 'A');
    s += char(rand() % 26 + 'A');
    return s;
}

//stored password (Morris-Thompson scheme)
string create(string password) {
    string salt = getSalt();
    string enc = encrypt25(password, salt);
    return salt + ":" + enc;
}

//check password, compare old enc with new enc to see if the pass is the same
bool check(string input, string stored) {
    string salt = stored.substr(0, 2);
    string oldEnc = stored.substr(3);

    string newEnc = encrypt25(input, salt);

    return newEnc == oldEnc;
}

// Main
int main() {
    srand(time(0)); //to make salt random each time

    string passwords[10] = {
        "pass21","hello","admin","beta","github",
        "abc","verbose","user","secure","lock"
    };

    string stored[10];
    //encrypt and print
    cout << "Encrypted Passwords:\n";
    for (int i = 0; i < 10; i++) {
        stored[i] = create(passwords[i]);
        cout << stored[i] << endl;
    }

    // test
  string input;
  cout << "Enter password: ";
  cin >> input;

for (int i = 0; i < 10; i++) {
    if (check(input, stored[i])) {
        cout << "Correct\n";
        return 0;
    }
}

cout << "Wrong\n";
}
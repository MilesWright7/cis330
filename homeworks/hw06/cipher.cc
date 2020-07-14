#include "cipher.h"

#define UPPER_CASE(r) ((r) - ('a' - 'A'))

struct Cipher::CipherCheshire {
    string cipherText;
};

Cipher::Cipher()
{
    smile = new CipherCheshire;
    smile->cipherText = "abcdefghijklmnopqrstuvwxyz ";
}
Cipher::Cipher(string in)
{
    smile = new CipherCheshire;
    smile->cipherText = in;
}
string Cipher::encrypt(string raw)
{
    string retStr;
    cout << "Encrypting..." << endl;
    for(unsigned int i = 0; i < raw.size(); i++) {
        unsigned int pos;
        bool upper = false;
        if(raw[i] == ' ') {
            pos = 26;
        } else if(raw[i] >= 'a') {
            pos = raw[i] - 'a';
        } else {
            pos = raw[i] - 'A';
            upper = 1;
        }
        if(upper) {
            retStr += UPPER_CASE(smile->cipherText[pos]);
        } else {
            retStr += smile->cipherText[pos];
        }
    }
    cout << "Done" << endl;

    return retStr;
}

string Cipher::decrypt(string enc)
{
    string retStr;
    cout << "Decrpyting..." << endl;
    // Fill in code here
	for(unsigned int i = 0; i < enc.size(); i++){
		unsigned int pos;
		char temp;
		bool upper = false;
		
		if(enc[i] >= smile->cipherText[0]){
	 		pos = enc[i] - smile->cipherText[0];
		} else if(enc[i] >= 'a'){
			pos = enc[i] - smile->cipherText[0] + 27;
		
		} else if(enc[i] >= UPPER_CASE(smile->cipherText[0])){
			pos = enc[i] - 'A' + 'a' - smile->cipherText[0];
			upper = 1;
		} else{
			pos = enc[i] - 'A' + 'a' - smile->cipherText[0] + 27;
			upper = 1;
		}

		if((pos + 'a') > 'z'){
			retStr += ' ';
		} else if(enc[i] == ' '){
			retStr += smile->cipherText[0];
			
		}else if(upper) {
				temp  = pos + 'a';
			retStr += UPPER_CASE(temp);
		} else {
			retStr += pos + 'a';
		}
			
		
			
	}

    cout << "Done" << endl;

    return retStr;
}




struct CaesarCipher::CaesarCipherCheshire : CipherCheshire {
     int rot;
};

CaesarCipher::CaesarCipher()
{
    CaesarSmile = new CaesarCipherCheshire;
	CaesarSmile->cipherText = "abcdefghijklmnopqrstuvwxyz ";
	CaesarSmile->rot = 0;
}

CaesarCipher::CaesarCipher(string in, int rot)
{
    CaesarSmile = new CaesarCipherCheshire;
	CaesarSmile->cipherText = in;
	CaesarSmile->rot = rot;
}

string CaesarCipher::encrypt(string raw)
{
    string retStr;
    cout << "Encrypting..." << endl;
    // Fill in code here
    for(unsigned int i = 0; i < raw.size(); i++) {
        unsigned int pos;
        bool upper = false;
        if(raw[i] == ' ') {
            pos = 26;
        } else if(raw[i] >= 'a') {
            pos = raw[i] - 'a';
        } else {
            pos = raw[i] - 'A';
            upper = 1;
        }
		
		pos = pos + CaesarSmile->rot + 27000;
		pos = pos % 27;
        if(upper) {
            retStr += UPPER_CASE(CaesarSmile->cipherText[pos]);
        } else {
            retStr += CaesarSmile->cipherText[pos];
        }
    }

    cout << "Done" << endl;

    return retStr;

}

string CaesarCipher::decrypt(string enc)
{
    string retStr;
    cout << "Decrpyting..." << endl;
    // Fill in code here
	for(unsigned int i = 0; i < enc.size(); i++){
		unsigned int pos;
		char temp;
		bool upper = false;
		if(enc[i] == ' '){
			//pass
		} else if(enc[i] >= CaesarSmile->cipherText[0]){
	 		pos = enc[i] - CaesarSmile->cipherText[0];
		} else if(enc[i] >= 'a'){
			pos = enc[i] - CaesarSmile->cipherText[0] + 27;
		
		} else {
			pos = enc[i] - 'A' + 'a' - CaesarSmile->cipherText[0];
			upper = 1;
		}
		pos = pos - CaesarSmile->rot + 27000;
		pos = pos % 27;
		if(enc[i] == ' '){
			if(upper){
				cout << "here" << endl;
				retStr += UPPER_CASE(CaesarSmile->cipherText[26 - (CaesarSmile->rot % 27)]);
			} else {
				retStr += CaesarSmile->cipherText[26 - (CaesarSmile->rot % 27)];
			}
		} else if(upper) {
			temp  = pos + 'a';
			retStr += UPPER_CASE(temp);
		} else if((pos + 'a') > 'z'){
			retStr += ' ';
		} else{
			retStr += pos + 'a';
		}
	}

    cout << "Done" << endl;

    return retStr;
}



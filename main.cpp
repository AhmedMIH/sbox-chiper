#include <stdio.h>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <string>

using namespace std;


class Sbox{
private:
    vector<string> plainTextBinary;
    vector<string> afterEncryption;
    vector<long> afterEncryptionDecimal;
    vector<string> beforDecryptionBinary;
    vector<string> afterDecryption;
    string key;
    string symbols [11] = {
        "00101110","00100111","00111010","00111011","00111111","00100001",
        "00101100","00100010","00101000","00101001","00100000"
        };

    string box[3];

    string sBox[8][4] = {
        {"0","0","0","11"},{"0","0","1","01"},{"0","1","0","00"},{"0","1","1","10"},
        {"1","0","0","01"},{"1","0","1","00"},{"1","1","0","11"},{"1","1","1","10"}
    };
public:
    void convertPlainTextToBinary(string plainText){

        for(int i=0;i<plainText.length();i++){
            string   charBinary =  bitset<8>(plainText[i]).to_string();
            plainTextBinary.push_back(charBinary);
        }
        /* for(int i=0;i<plainTextBinary.size();i++){
            cout<<plainTextBinary[i]<<endl;
        }*/
    }

    bool isSymbol(string character){
        for(int i=0;i<11;i++){
            if(character == symbols[i]){
                return true;
                break;
            }
        }
        return false;
    }

    vector<string> splitBinaryToFourDigit(vector<string> list){
        vector<string> splitedArray;
        for(int i  = 0 ; i<list.size();i++){
            if(isSymbol(list[i])){
                string str1 = list[i];
                splitedArray.push_back(str1);
            }else{
                string str1 = list[i].substr(0,list[i].size()/2);
                string str2 = list[i].substr(list[i].size()/2,list[i].size());

                splitedArray.push_back(str1);
                splitedArray.push_back(str2);
            }
        }
        /*for(int i = 0 ;i<splitedArray.size();i++){
            cout<<splitedArray[i]<<endl;
        }*/
        return splitedArray;
    }

    bool keyVaildation(){
        if(key.length() != 3 ){
                return false;
        }
        else{
            for(int i=0;i<key.length();i++){
                if(!isdigit(key[i])){
                    return false;
                    break;
                }
                else{
                    if(!(key[i] == '0' || key[i] == '1')){
                        return false;
                        break;
                    }
                }
            }
        }
        return true;
    }

    string xorResult(int x,int k){
         if(!x != !k){
             return "1";
        }
        else{
            return "0";
        }
    }

    string findt1t2(){
        for(int i = 0 ;i<8;i++){
        /*    cout<<"------------------------------------------------------------------"<<endl;
            cout<<box[0]<<"      "<<sBox[i][0]<<endl;
            cout<<box[1]<<"      "<<sBox[i][1]<<endl;
            cout<<box[2]<<"      "<<sBox[i][2]<<endl;

            cout<<"------------------------------------------------------------------"<<endl;*/

            if(box[0] == sBox[i][0] && box[1] == sBox[i][1] && box[2] == sBox[i][2]){
                return sBox[i][3];

                //cout<<"------------------------------------------------------------------"<<endl;
                //cout<<"t1t2     "<<t1t2<<endl;
                break;
            }
        }
    }

    vector<string> concatString(vector<string> list){
        vector<string> concArray;
        for(int i=0;i<list.size();i=i+2){
            if(list[i].size() == 8){
                concArray.push_back(list[i]);
                i--;
            }
            else{
                string str1 = list[i];
                string str2 = list[i+1];
                string str = str1+str2;

                concArray.push_back(str);
            }
        }
        return concArray;
    }

    void convertBinaryToDecimal(vector<string> list){
        for(int i=0;i<list.size();i++){
          long d =  bitset<8>(list[i]).to_ullong();

          afterEncryptionDecimal.push_back(d);
        }
    }

    void encryption(){
        string plainText;
        bool keyValidated = false;

        cout<<"enter word"<<endl;
        getline(cin,plainText);
      //  cout<<plainText<<endl;

        convertPlainTextToBinary(plainText);
        plainTextBinary = splitBinaryToFourDigit(plainTextBinary);

        do{
            cout<<"Enter key (3 binary digit) : "<<endl;
            cin >>key;
            keyValidated = keyVaildation();
        }while(keyValidated == false);

        int k1 = (int) key[0] - 48;
        int k2 = (int) key[1] - 48;
        int k3 = (int) key[2] - 48;
       // cout<<" k1 : "<<k1<<" k2 : "<<k2<<" k3 : "<<k3<<"\n\n"<<endl;

        for(int i = 0 ;i<plainTextBinary.size();i++){
            if(isSymbol(plainTextBinary[i])){
             //   cout<<"------------------------------------------------------------------"<<endl;
               // cout<<plainTextBinary[i]<<endl;
                afterEncryption.push_back(plainTextBinary[i]);
            }
            else{
                string str = plainTextBinary[i];
                int x1 = (int) str[0] - 48;
                int x2 = (int) str[1] - 48;
                int x3 = (int) str[2] - 48;
                int x4 = (int) str[3] - 48;
              //  cout<<"------------------------------------------------------------------"<<endl;

                //cout<<" x1 : "<<x1<<" x2 : "<<x2<<" x3 : "<<x3<<" x4 : "<<x4<<endl;

                box[0] = xorResult(x3,k1);
                box[1] = xorResult(x4,k2);
                box[2] = xorResult(x3,k3);

                //cout<<box[0]<<endl;
                //cout<<box[1]<<endl;
                //cout<<box[2]<<endl;


                string t1t2 = findt1t2();
                int t1 = (int) t1t2[0] - 48;
                int t2 = (int) t1t2[1] - 48;

                //cout<<"------------------------------------------------------------------"<<endl;
                //cout<<"t1      "<<t1<<endl;
                //cout<<"t2      "<<t2<<endl;
                //cout<<"------------------------------------------------------------------"<<endl;

                string u1 = xorResult(x1,t1);
                string u2 = xorResult(x2,t2);

                //cout<<u1<<u2<<endl;

                string u1u2 = u1+u2;
                //cout<<"------------------------------------------------------------------"<<endl;

                //cout<<u1u2<<endl;

                string encryptedBinary = to_string(x3)+to_string(x4)+u1u2;
                /*cout<<"------------------------------------------------------------------"<<endl;
                cout<<"encryptedBinary : "<<encryptedBinary<<endl;
                cout<<"------------------------------------------------------------------"<<endl;
                */
                afterEncryption.push_back(encryptedBinary);

            }
        }

        afterEncryption = concatString(afterEncryption);

        cout<<"text after encrypt in binary "<<endl;
        for(int i = 0 ;i<afterEncryption.size();i++){
            cout<<afterEncryption[i]<<endl;
        }

        convertBinaryToDecimal(afterEncryption);
        cout<<"text after encrypt in decimal "<<endl;

        for(int i = 0 ;i<afterEncryptionDecimal.size();i++){
            cout<<afterEncryptionDecimal[i]<<endl;
        }

    }

    void convertDecimalToBinary(vector<long> list){
         for(int i=0;i<list.size();i++){
          string d =  bitset<8>(list[i]).to_string();
          beforDecryptionBinary.push_back(d);
    //      cout<<beforDecryptionBinary[i]<<endl;
        }
    }

    string reverseXor(int t,int u){
        if(u==0 ){
            return to_string(t);
        }
        else if(u==1 ){
            if(t==1) return "0";
            else return "1";
        }
    }

    string convertBinaryToPlainText(){
        string str;
        for(int i = 0;i<afterDecryption.size();i++){
            char c  = static_cast<char>(bitset<8>(afterDecryption[i]).to_ullong());
             str =str+ c;
        }
        return str;
    }

    void decryption(){
        convertDecimalToBinary(afterEncryptionDecimal);
        beforDecryptionBinary = splitBinaryToFourDigit(beforDecryptionBinary);
        int k1 = (int) key[0] - 48;
        int k2 = (int) key[1] - 48;
        int k3 = (int) key[2] - 48;
        for(int i = 0;i<beforDecryptionBinary.size();i++){
            if(isSymbol(beforDecryptionBinary[i])){
                afterDecryption.push_back(beforDecryptionBinary[i]);
            }
            else{
                string str = beforDecryptionBinary[i];
                int x3 = (int)  str[0] -48;
                int x4 = (int)  str[1] -48;
                int u1 = (int) str[2] - 48;
                int u2 = (int) str[3] - 48;

               // cout<<"---------------------------------------------------------"<<endl;
                //cout<<" x3 : "<<x3<<" x4 : "<<x4<<" u1 : "<<u1<<" u2 : "<<u2<<endl;

                box[0] = xorResult(x3,k1);
                box[1] = xorResult(x4,k2);
                box[2] = xorResult(x3,k3);

                string t1t2 = findt1t2();
                int t1 = (int) t1t2[0] - 48;
                int t2 = (int) t1t2[1] - 48;

                string x1 = reverseXor(t1,u1);
                string x2 = reverseXor(t2,u2);

                string decryptedBinary = x1+x2+to_string(x3)+to_string(x4);
                afterDecryption.push_back(decryptedBinary);

            }
        }

        afterDecryption = concatString(afterDecryption);

        cout<<"text after decrypt in binary "<<endl;
        for(int i = 0 ;i<afterDecryption.size();i++){
            cout<<afterDecryption[i]<<endl;
        }

        string plainTextAfterDecrypted = convertBinaryToPlainText();

        cout<<"plain text after decrypted : " << plainTextAfterDecrypted<<endl;

    }

};



int main(int argc, char **argv){
    Sbox sbox;
    sbox.encryption();
    sbox.decryption();
	return 0;
}


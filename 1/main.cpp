//
//  main.cpp
//  1
//
//  Created by Pavel Ronaldo on 6/15/20.
//  Copyright © 2020 Pavel. All rights reserved.
//

#include <iostream>
#include <map>
#include <fstream>

using namespace std;

struct Category {
    Category () {
        product = "";
        category_of_product = "";
        
    };
    Category (const string& product, const string& category) {
        this->product = product;
        this->category_of_product = category;
    };
    
    void print() {
        cout << "product: " << product << "\ncategory_of_product: " << category_of_product << endl;
    };
    
    string product;
    string category_of_product;
};



class Map {
public:
    Map(){};
    Category& operator[] (int index) { // hash
        return arr[index];
    }
    Category& operator[] (const string& product) { // hash
        int index = Hash_func(product);
        return arr[index];
    }
    void add(const Category& obj) {
        if (obj.product.size() > 15) {
            cout << "Too long product name.";
            return;
        }
        int index = Hash_func(obj.product);
        arr[index] = obj;
        //cout << "Index: " << index << endl;
    }
    
    void add_from_file(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Wrong filename :(" << endl;
            exit(1);
        }
        
        string Name;
        string Category;
        
        while (file >> Category) {
            file >> Name;
            struct Category tmp(Name, Category);
            add(tmp);
        }
    }
    
    void print_by_hash(int hash) {
        arr[hash].print();
    }
    
    void print_by_name(string name){
        int index = Hash_func(name);
        print_by_hash(index);
    }
    
    void print() {
        for (int i = 0; i < 3500; i++) {
            if (arr[i].product != "" ) {
               cout << "category_of_product: " << arr[i].category_of_product << ", product: " << arr[i].product << ", hash: " << i << endl;
            }
        }
    }
    
private:
    int Hash_func (const string& obj) {
        int sum = 0;
        string tmp = obj;
        int n = 0;
        int n1 = 0;
        int n2 = 0;
        int n3 = 0;
        
        
        n = (int) tmp.size();
    
        if (tmp.size() % 2 != 0 ){
            tmp += ('a' + n);
        }
        
        for (auto i : tmp)
            n1 += (int) i;
        
        for (int i = 0; i < tmp.size(); i++) {
            n2 += (tmp[i] * tmp[i + 1]) / 7;
        }
        
        n3 = n2 % n1;
        
        sum = n1 + n2 + n3;
        sum /= 11;
        sum -= 106;
        
        return sum;
    }
    
private:
    Category arr[3500];
};

class Main{
public:
    Main() {
        map.add_from_file("/Users/pavelronaldo/Desktop/Alg/1/list.txt");
        cout << "Starting..." << endl;
    }
    
    void menu() {
        bool tmp_bool = 1;
        
        while (tmp_bool) {
            int tmp;
            cout << " 1 - show_with_hash;\n 2 - search_by_hash;\n 3 - search_by_name_of_product;\n " <<endl;
            cout << " Put number : ";
            cin >> tmp;
            
            switch (tmp) {
                case 1:{
                    map.print();
                    break;
                }
                    
                case 2:{
                    int hash = 0;
                    cout << "Input number of hash for searching: ";
                    cin >> hash;
                    map.print_by_hash(hash);
                    break;
                }
                    
                case 3:{
                    string name = "";
                    cout << "Input name of product for searching: ";
                    cin >> name;
                    map.print_by_name(name);
                    break;
                }
                
            }
            tmp_bool = Continue();
        }
    }

private:
    
    bool Continue(){
        string tmp;
        cout << " Would you like to continue ? (Y/N): ";
        cin >> tmp;
        
        if (tmp == "Y" || tmp == "y" || tmp == "YES" || tmp == "yes" ) return 1;
        else return 0;
    }
    
private:
    Map map;
};

int main() {

    Map m;
    
    Main obj;
    obj.menu();
    return 0;
}

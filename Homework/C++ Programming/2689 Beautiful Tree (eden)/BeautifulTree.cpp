// MegaShow
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include "BeautifulTree.hpp"
using namespace std;

namespace HFM {
    HuffmanCode::HuffmanCode(const string &str) {
        size = 0;
        int code[26] = {0};
        for (int i = 0; i < str.size(); i++) {
            if (str[i] >= 'a' && str[i] <= 'z') {
                code[str[i]-'a']++;
                org += str[i];
            }
        }
        for (int i = 0; i < 26; i++) {
            if (code[i]) {
                size++;
            }
        }
        Node** arr = new Node*[size];
        for (int i = 0, j = 0; i < 26; i++) {
            if (code[i]) {
                arr[j++] = new Node(code[i], 'a' + i);
            }
        }
        for (int i = 0; i < size - 1; i++) {
            // fuck!!!
            /*for (int j = size - 1; j > i; j--) {
                for (int k = i; k < j; k++) {
                    if (arr[k]->val > arr[k+1]->val) {
                        Node* tmp = arr[k];
                        arr[k] = arr[k+1];
                        arr[k+1] = tmp;
                    }
                }
            }*/
            stable_sort(arr + i, arr + size, [](Node* a, Node* b){ return a->val < b->val; });
            //sort(arr + i, arr + size, [](Node* a, Node* b){ return a->val < b->val; });
            Node* n = new Node(arr[i]->val + arr[i+1]->val, 0, arr[i], arr[i+1]);
            for (int j = i + 1; j < size - 1; j++) {
                arr[j] = arr[j+1];
            }
            arr[size-1] = n;
        }
        root = arr[size-1];
        delete [] arr;
    }

    HuffmanCode::HuffmanCode(int w[], int n) {
        size = n;
        Node** arr = new Node*[n];
        for (int i = 0; i < n; i++) {
            arr[i] = new Node(w[i], i);
        }
        for (int i = 0; i < n - 1; i++) {
            // fuck!!!
            /*for (int j = size - 1; j > i; j--) {
                for (int k = i; k < j; k++) {
                    if (arr[k]->val > arr[k+1]->val) {
                        Node* tmp = arr[k];
                        arr[k] = arr[k+1];
                        arr[k+1] = tmp;
                    }
                }
            }*/
            stable_sort(arr + i, arr + n, [](Node* a, Node* b){ return a->val < b->val; });
            //sort(arr + i, arr + n, [](Node* a, Node* b){ return a->val < b->val; });
            Node* tmp = new Node(arr[i]->val + arr[i+1]->val, 0, arr[i], arr[i+1]);
            for (int j = i + 1; j < size - 1; j++) {
                arr[j] = arr[j+1];
            }
            arr[size-1] = tmp;
        }
        root = arr[n-1];
        delete [] arr;
    }
    
    HuffmanCode::~HuffmanCode() {
        deleteNode(root);
    }

    void HuffmanCode::DisplayCode() {
        // <code, <val, string> >
        map<int, pair<int, string> > m;
        inOrder(root, m, string(""));
        int weight = 0;
        vector<pair<int, pair<int, string> > > v(m.begin(), m.end());
        // fuck!!!
        /*for (int j = v.size() - 1; j > 0; j--) {
            for (int k = 0; k < j; k++) {
                if (v[k].second.first > v[k+1].second.first) {
                    pair<int, pair<int, string> > tmp = v[k];
                    v[k] = v[k+1];
                    v[k+1] = tmp;
                }
            }
        }*/
        stable_sort(v.begin(), v.end(), [](pair<int, pair<int, string> > a, pair<int, pair<int, string> > b) {
                return a.second.first < b.second.first;
            });
        /*sort(v.begin(), v.end(), [](pair<int, pair<int, string> > a, pair<int, pair<int, string> > b) {
                return a.second.first < b.second.first;
            });*/
        for (vector<pair<int, pair<int, string> > >::iterator it = v.begin(); it != v.end(); it++) {
            if (org.size()) {
                cout << "(" << static_cast<char>(it->first) << ") ";
            }
            cout << "Weight = " << it->second.first << "; Code = " << it->second.second << endl;
            weight += it->second.first * it->second.second.size();
        }
        cout << "Huffman's codeLength = " << weight << endl;
        if (org.size()) {
            cout << "Origin Text: " << org << endl;
            cout << "Huffman's Code: ";
            for (int i = 0; i < org.size(); i++) {
                cout << m[org[i]].second;
            }
            cout << endl;
        }
    }

    void HuffmanCode::inOrder(Node* n, map<int, pair<int, string> >& m, string str) {
        if (n->left) {
            inOrder(n->left, m, str + "1");
            inOrder(n->right, m, str + "0");
        } else {
            m[n->code] = make_pair(n->val, str);
        }
    }

    void HuffmanCode::deleteNode(Node* n) {
        if (n) {
            deleteNode(n->left);
            deleteNode(n->right);
            delete n;
        }
    }

}
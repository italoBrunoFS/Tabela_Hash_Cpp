#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Node {
public:
    string key;
    Node* next;

    Node(const string& key) : key(key), next(nullptr) {}
};

class SecondLevelHashTable {
public:
    int num_buckets;
    vector<Node*> buckets;

    SecondLevelHashTable(int num_buckets) : num_buckets(num_buckets), buckets(num_buckets, nullptr) {}
};

class HashTable {
private:
    int n;
    int second_level_size;
    vector<SecondLevelHashTable> first_level;

    int h1(const string& key) {
        int sum = 0;
        for (char c : key)
            sum += c;
        return sum % 10;
    }

    int h2(const string& key, int num_buckets) {
        unsigned long hash_val = 5381;
        for (char c : key)
            hash_val = ((hash_val << 5) + hash_val) + c;
        return hash_val % num_buckets;
    }

public:
    HashTable(int n) : n(n), second_level_size(max(n / 10, 1)), first_level(10, SecondLevelHashTable(second_level_size)) {}

    void insert(const string& key) {
        int idx1 = h1(key);
        SecondLevelHashTable& sht = first_level[idx1];
        int idx2 = h2(key, sht.num_buckets);

        Node* current = sht.buckets[idx2];
        while (current) {
            if (current->key == key) {
                cout << "Chave '" << key << "' ja existe!" << endl;
                return;
            }
            current = current->next;
        }

        Node* new_node = new Node(key);
        new_node->next = sht.buckets[idx2];
        sht.buckets[idx2] = new_node;
        cout << "Chave '" << key << "' inserida com sucesso!" << endl;
    }

    void search(const string& key) {
        int idx1 = h1(key);
        SecondLevelHashTable& sht = first_level[idx1];
        int idx2 = h2(key, sht.num_buckets);

        Node* current = sht.buckets[idx2];
        while (current) {
            if (current->key == key) {
                cout << "Chave '" << key << "' encontrada!" << endl;
                return;
            }
            current = current->next;
        }
        cout << "Chave '" << key << "' nao encontrada!" << endl;
    }
};

int main() {
    int n;
    cout << "Digite o numero total de objetos (n): ";
    cin >> n;
    cin.ignore(); // Para limpar o '\n' pendente

    if (n < 1) {
        cout << "n deve ser positivo!" << endl;
        return 1;
    }

    HashTable ht(n);

    while (true) {
        cout << "\n--- Menu ---\n";
        cout << "1. Inserir chave\n";
        cout << "2. Buscar chave\n";
        cout << "3. Sair\n";
        cout << "Escolha uma opcao: ";

        string opcao;
        getline(cin, opcao);

        if (opcao == "1") {
            cout << "Digite a chave: ";
            string key;
            getline(cin, key);
            ht.insert(key);
        } else if (opcao == "2") {
            cout << "Digite a chave: ";
            string key;
            getline(cin, key);
            ht.search(key);
        } else if (opcao == "3") {
            cout << "Saindo..." << endl;
            break;
        } else {
            cout << "Opcao invalida!" << endl;
        }
    }

    return 0;
}

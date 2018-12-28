#include <iostream>
#include <forward_list>
#include <vector>
#include <string>
#include <string>
#include <ctime>

class HashTadle {
public:
    explicit HashTadle(size_t size);
    HashTadle(const HashTadle&) = delete;
    HashTadle& operator=(const HashTadle&) = delete;
    ~HashTadle();

    bool Has(const std::string& key) const;
    bool Add(const std::string& key);
    bool Remove(const std::string& key);
    void rehash_table();

    int get_size() const;
    int get_number_exist() const;
    const int multiply_coef;

    int number_exist;
    struct hash_table_pair_s {
        std::string str;
        bool delete_flag;
        hash_table_pair_s() {
            str = "";
            delete_flag = false;
        }
    } hash_table_pair;
    std::vector<struct hash_table_pair_s> table;
};

HashTadle::HashTadle(size_t size)
    : table(size), number_exist(0), multiply_coef(2) {}

HashTadle::~HashTadle() {
    table.clear();
}

int HashTadle::get_size() const {
    return table.size();
}

int HashTadle::get_number_exist() const {
    return number_exist;
}

int Hash(const std::string& key) {
    int hash = 0;
    int a = 31;  // простое число близкое к количеству латинских маленьких букв
    int len = key.length();
    for (int i = 0; i < len; ++i) {
        hash = (hash * a + key[i]);
    }
    return hash;
}

void HashTadle::rehash_table() {
    int table_old_size = this->get_size();
    int table_new_size = table_old_size * this->multiply_coef;
    std::vector<struct hash_table_pair_s> table_new(table_new_size);
    int max_probs = table_new_size;

    for (int i = 0; i < table_old_size; i++) {
        if (!this->table[i].str.empty() && !this->table[i].delete_flag) {
            size_t hash = Hash(this->table[i].str) % table_new_size;
            int j = 0;
            while (j < max_probs) {
                hash = (hash + j) % table_new_size;
                if (table_new[hash].str.empty() || table_new[hash].delete_flag) {
                    table_new[hash].str = this->table[i].str;
                    table_new[hash].delete_flag = false;
                    break;
                }
                ++j;
            }
        }
    }
    this->table.clear();
    this->table = table_new;
    return;
}

bool HashTadle::Add(const std::string& key) {
    bool return_result = true;
    int table_size = this->get_size();
    size_t hash = Hash(key) % table_size;
    int max_probs = table_size;
    int i = 0;

    int first_place = -1;

    while (i < max_probs) {
        hash = (hash + i) % table_size;

        if (this->table[hash].str.empty()) {
            if (first_place < 0) first_place = hash;
            break;
        }

        if (this->table[hash].str == key && !this->table[hash].delete_flag) {
            return_result = false;
            first_place = -1;
            break;
        }

        if (this->table[hash].delete_flag) {
            if (first_place < 0) first_place = hash;
        }
        ++i;
    }

    if (first_place >= 0) {
        this->table[first_place].str = key;
        this->table[first_place].delete_flag = false;
        this->number_exist += 1;
    }

    if (double(this->get_number_exist()) / table_size >= 3. / 4.) {
        this->rehash_table();
    }
    return return_result;
}

bool HashTadle::Remove(const std::string& key) {
    bool return_result = false;
    int table_size = this->get_size();
    size_t hash = Hash(key) % table_size;
    int max_probs = table_size;
    int i = 0;

    while (i < max_probs) {
        hash = (hash + i) % table_size;

        if (this->table[hash].str.empty()) {
            break;
        }

        if (this->table[hash].str == key && !this->table[hash].delete_flag) {
            return_result = true;
            this->table[hash].delete_flag = true;
            this->number_exist -= 1;
            break;
        }
        ++i;
    }
    return return_result;
}

bool HashTadle::Has(const std::string& key) const {
    bool return_result = false;
    int table_size = this->get_size();
    size_t hash = Hash(key) % table_size;
    int max_probs = table_size;
    int i = 0;

    while (i < max_probs) {
        hash = (hash + i) % table_size;

        if (this->table[hash].str.empty()) {
            break;
        }
        if (this->table[hash].str == key && !this->table[hash].delete_flag) {
            return_result = true;
            break;
        }
        ++i;
    }

    return return_result;
}

int main() {
    HashTadle table(8);
    char command = 0;
    std::string key;
    while (std::cin >> command >> key) {
        switch (command) {
        case '+':
            std::cout << (table.Add(key) ? "OK\n" : "FAIL\n");
            break;
        case '-':
            std::cout << (table.Remove(key) ? "OK\n" : "FAIL\n");
            break;
        case '?':
            std::cout << (table.Has(key) ? "OK\n" : "FAIL\n");
            break;
        default:
            std::cerr << "bad";
            return 0;
        }
    }
    return 0;
}

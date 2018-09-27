#define TABLE_SIZE 10009

struct Node {
    vector<int> index;
    Node* next;
};

class RandomizedCollection {
public:
    Node* hash_table[TABLE_SIZE];
    vector<int> vec;
    
    int hash_func(int val) {
        if (val < 0) {
            val = -val;
        }
        return val % TABLE_SIZE;
    }
    
    Node* find_ptr(int val) {
        int idx = hash_func(val);
        Node* p = hash_table[idx];
        while (p != nullptr) {
            if (vec[p->index[0]] == val) {
                return p;
            }
            p = p->next;
        }
        return nullptr;
    }
    
    /** Initialize your data structure here. */
    RandomizedCollection() {
        for (int i=0; i<TABLE_SIZE; i++) {
            hash_table[i] = nullptr;
        }
    }
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        int idx = hash_func(val);
        bool exist = false;
        Node* p = hash_table[idx];
        Node* p_prev = hash_table[idx];
        while (p != nullptr) {
            if (vec[p->index[0]] == val) {
                exist = true;
                break;
            }
            p_prev = p;
            p = p->next;
        }
        if (!exist) {
            Node* q = new Node();
            q->next = nullptr;
            q->index.push_back(vec.size());
            vec.push_back(val);
            if (p_prev == p) {
                hash_table[idx] = q;
            } else {
                p_prev->next = q;
            }
            return true;
        } else {
            p->index.push_back(vec.size());
            vec.push_back(val);
            return false;
        }
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        int idx = hash_func(val);
        bool exist = false;
        Node* p = hash_table[idx];
        Node* p_prev = hash_table[idx];
        while (p != nullptr) {
            if (vec[p->index[0]] == val) {
                exist = true;
                break;
            }
            p_prev = p;
            p = p->next;
        }
        if (exist) {
            int val2_idx = vec.size()-1;
            int val2 = vec[val2_idx];
            Node* val2_ptr = find_ptr(val2);
            if (p->index.size() > 1) {
                int val_idx = p->index[p->index.size()-1];
                vec[val_idx] = vec[val2_idx];
                for (int i=val2_ptr->index.size()-1; i>=0; i--) {
                    if (val2_ptr->index[i] == val2_idx) {
                        val2_ptr->index[i] = val_idx;
                        break;
                    }
                }
                vec.pop_back();
                p->index.pop_back();
            } else { // p->index.size() == 1
                if (p_prev == p) {
                    hash_table[idx] = hash_table[idx]->next;
                } else {
                    p_prev->next = p->next;
                }
                int val_idx = p->index[0];
                vec[val_idx] = vec[val2_idx];
                for (int i=val2_ptr->index.size()-1; i>=0; i--) {
                    if (val2_ptr->index[i] == val2_idx) {
                        val2_ptr->index[i] = val_idx;
                        break;
                    }
                }
                vec.pop_back();
                delete p;
            }
            return true;
        } else {
            return false;
        }
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        int rand_idx = rand() % vec.size();
        return vec[rand_idx];
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection obj = new RandomizedCollection();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */

class Node {
private:
    Node* next;
    Node* prev;
    int data;
    int key;

public:
    Node(int _key, int _data)
    {
        next =nullptr;
        prev =nullptr;
        data =_data;
        key =_key;
    }

    friend class LL;
};

class LL {
private:
   Node* head;
   Node* tail;
   map<int, Node*> mp;
   int c;

public:
    LL(int capacity)
    {
        head = new Node(-1,-1);
        tail = new Node(-1,-1);

        head->next =tail;
        tail->prev =head;

        c =capacity;
    } 

    void put(int key, int value)
    {
        if (mp.find(key)!=mp.end())
        {
            mp[key]->data =value;

            Node* c =mp[key];
            Node* h =c->prev;
            Node* t= c->next;

            h->next =t;
            t->prev =h;

            t =head->next;
            head->next =c;
            t->prev =c;

            c->next =t;
            c-?prev =head;
            return;
        }

        Node* newNode =new Node(key, value);
        Node* t = head->next;

        head->next =newNode;
        t->prev =newNode;

        newNode->prev =head;
        newNode->next =t;
        
        mp[key] =newNode;

        if (c==0)
        {
            Node* h = tail->prev->prev;
            mp.erase(tail->prev->key);
            delete tail->prev;

            h->next =tail;
            tail->prev =h;
            return;
        }

        c--;
    }

    int get(int key)
    {
        if (mp.find(key)==mp.end())
        {
            return -1;
        }

        Node* c= mp[key];
        Node* h =c->prev;
        Node* t =c->next;

        h->next =t;
        t->prev =h;

        t =head->next;
        head->next =c;
        t->prev =c;
        c->prev =head;
        c->next =t;

        return mp[key]->data;
    }
};

class LRUCache {
private:
    LL* l;
public:
    LRUCache(int capacity) {
       l = new LL(capacity); 
    }
    
    int get(int key) {
        return l->get(key);
    }
    
    void put(int key, int value) {
        return l->put(key, value);
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
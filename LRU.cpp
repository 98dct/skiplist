struct DLinkedNode{
    int key,value;
    DLinkedNode* pre;
    DLinkedNode* next;
    DLinkedNode():key(0),value(0),pre(nullptr),next(nullptr){}
    DLinkedNode(int _key,int _value):key(_key),value(_value),pre(nullptr),next(nullptr){}
};

class LRUCache {

private:
    unordered_map<int,DLinkedNode*> cache;
    DLinkedNode* head;
    DLinkedNode* tail;
    int size;
    int capacity;

public:

    //最近最少使用
    //least recnetly use 

    LRUCache(int _capacity):capacity(_capacity),size(0) {
        //使用伪头部和伪尾部节点
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next  = tail;
        tail->pre = head;
    }
    
    int get(int key) {
        if(!cache.count(key)){
            //key不存在
            return -1;
        }

        //key存在
        //通过哈希表定位，在移到头部
        DLinkedNode* node = cache[key];
        moveToHead(node);
        return node->value;

    }
    
    //添加元素
    void put(int key, int value) {
        if(!cache.count(key)){
            //key不存在,创建一个新的节点，加入哈希表
            DLinkedNode* node = new DLinkedNode(key,value);
            cache[key] = node;
            //添加到双链表的头部
            addToHead(node);
            ++size;
            if(size > capacity){
                //超出容量，删除双向链表的尾部节点
                DLinkedNode* removed = removeTail();
                cache.erase(removed->key);
                delete removed;
                --size;
            }
        }else{
            
            //key存在
            //哈希表定位，修改value,并移到头部
            DLinkedNode* node = cache[key];
            node->value = value;
            moveToHead(node);
        }
    }

    //删除元素
    void delete(int key){
	if(cache.count(key)==0){
		cout << "元素不存在"  << endl; 
	}

	DLinkedNode* node = cache[key];
	node->pre->next = node->next;
	node->next->pre = node->pre;
     }

    void addToHead(DLinkedNode* node){
        node->pre = head;
        node->next = head->next;
        head->next->pre = node;
        head->next = node;
    }

    void removeNode(DLinkedNode* node){
        node->pre->next = node->next;
        node->next->pre = node->pre;
    }

    void moveToHead(DLinkedNode* node){
        //先删除
        removeNode(node);
        //在添加到头
        addToHead(node);
    }

    DLinkedNode* removeTail(){
        DLinkedNode* node = tail->pre;
        removeNode(node);
        return node;
    }

};

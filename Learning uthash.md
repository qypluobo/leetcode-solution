# uthash操作总结

## 0.声明hash表头
注意表头不需要用malloc分配内存，只需要下面一行就可以
```
struct MyHashNode* hashTable = NULL;
```
## 1.key为整型
### 初始化
定义一个结构体，如下，其中hh为必须添加的字段，在HASH_ITER中会用到
```
struct MyHashNode {
    int key;
    int val;
    UT_hash_handle hh;
};
```
### 添加元素
```
int key = 399999;
struct MyHashNode* tmp = NULL;
tmp = (struct MyHashNode*)malloc(sizeof(struct MyHashNode));
tmp->key = key;
tmp->val = 40;
HASH_ADD_INT(hashTable, key, tmp);
```
### 查找元素
```
int key = 399999;
struct MyHashNode* tmp = NULL;
HASH_FIND_INT(hashTable, &remain, tmp);
if (tmp != NULL) {
    ...
}
```
### 删除元素
注意此处用到了结构体中的hh字段
```
struct MyHashNode* curItem = NULL;
struct MyHashNode* tmp = NULL;
HASH_ITER(hh, hashTable, curItem, tmp) {
    HASH_DEL(hashTable, curItem);
    free(curItem);
}
```
## 2.key为字符串
和int数据操作一样，其中key和value都是自己管理的，可以为数据，也可是指针

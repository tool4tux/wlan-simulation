#include <iostream>
#include <cstring>
using namespace std;

template<class T>
class Item {
public:
	Item<T> *next;
	T *obj;
	Item(T *objItem) {
		obj = objItem;
		next = NULL;
	}
	~Item() {
		delete obj;
		delete next;		
	}
};

template<class T>
inline bool compare(const Item<T> *a, const Item<T> *b) {
	if(*(a->obj) < *(b->obj)) {
		return true;
	}
	return false;
};

template<class T>
inline bool compare_min(const Item<T> *a, const Item<T> *b) {
	if(*(a->obj) <= *(b->obj)) {
		return true;
	}
	return false;
};

template<class T>
class ItemList {
public:
	Item<T> *first;
	Item<T> *next;
	Item<T> *temp;
	int size;

	ItemList() {
		first = NULL;
		next = NULL;
		temp = NULL;
		size = 0;
	}
	void push(T *newItem) {
		Item<T> *item = new Item<T>(newItem);
		if(first) {
			if(compare(item,first)) {
				temp = first;
				first = item;
				first->next = temp;
				size++;
				return;
			}
			next = first;
			while(next->next && compare_min(next->next,item)) {
				next = next->next;
			}
			temp = next->next;
			next->next = item;
			item->next = temp;
			size++;
		}
		else {
			item->next = NULL;
			first = item;
			size++;
		}
	}
	T *pop() {
		temp = first;
		first = first->next;
		size--;
		return temp->obj;
	}
	T *top() {
		if(first) {
			return first->obj;
		}
		return NULL;
	}
	~ItemList() {
		while(first) {
			delete(pop());
			size--;
		}
	}
};


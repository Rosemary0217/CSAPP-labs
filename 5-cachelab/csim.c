/* cachelab-Part A
 * name: Jingting Liu
 * ID: 1120201050
*/

#include "cachelab.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stddef.h>
#include <string.h>

/***********************data*************************/
int verbose_flag = 0;
int num_hits = 0, num_misses = 0, num_evictions = 0;
int s, S, E, b, t;

typedef struct Node{
    unsigned tag;
    struct Node* prev;
    struct Node* next;
}Node;

typedef struct CacheGroup{
    Node* head;
    Node* tail;
    int* size;
}Group;

Group* cache;

/**********************functions**********************/
void parseOption(int argc, char* argv[], char *filename)
{
    char op;
    while(-1 != (op = (getopt(argc, argv, "vs:E:b:t:")))){
		switch(op){
			case 'v':
                    verbose_flag = 1;
				    break;
			case 's':
                    s = atoi(optarg);
                    S = 1 << s;  //#sets=2^s
                    break;
			case 'E':
                    E = atoi(optarg);
                    break;
			case 'b':
                    b = atoi(optarg);
                    break;
			case 't':
                    strcpy(filename, optarg);
                    break;
		}
	}
    return;
}

void addLRUHead(unsigned set, Node* node, Group* curset){
    node->next = curset->head->next;   // new head's next is old head
    node->prev = curset->head;         // new head's prev is old head's prev(root)
    curset->head->next->prev = node;   // new root
    curset->head->next = node;         // new head
    *(curset->size) = *(curset->size) + 1;
}

void deleteElement(unsigned set, Node* node, Group* curset){
    node->next->prev = node->prev;
    node->prev->next = node->next;
    //(curset->size)--;
    *(curset->size) = *(curset->size) - 1;
}

void evict(unsigned set, Node* newnode, Group* curset){
    deleteElement(set, curset->tail->prev, curset);  // remove the least used one
    addLRUHead(set, newnode, curset);
}

void update(unsigned address){
    unsigned mask = (0xffffffff >> (32-s));  // keep lower s bits
    unsigned set = mask & (address >> b);    // index
    unsigned tag = address >> (s + b);       // tag

    Group curset = cache[set];   

    Node* node = curset.head->next; 
    int found = 0;
    while(node != curset.tail){
        if(node->tag == tag){    // look for tag in the appointed set
            found = 1;
            break;
        }
        node = node->next;
    }
    if(found){
        num_hits++;   // hit
        deleteElement(set, node, &curset);  // delete from original position
        addLRUHead(set, node, &curset);    // add to head(recently used)
    }else{     // miss, add a new node to cache
        num_misses++;
        Node* newnode = malloc(sizeof(Node));
        newnode->tag = tag;
        if(*(curset.size) == E){  // full, needs eviction
            num_evictions++;
	        evict(set, newnode, &curset);
        }else
            addLRUHead(set, newnode, &curset);
    }
}

void simulateCache(char *filename){
    cache = malloc(S * sizeof(Group));
    for(int i = 0; i < S; i++){
        cache[i].head = malloc(sizeof(Node));
        cache[i].tail = malloc(sizeof(Node));
        cache[i].size = malloc(sizeof(int));
        cache[i].head->next = cache[i].tail;
        cache[i].tail->prev = cache[i].head;
        *(cache[i].size) = 0;
    }

    FILE* file = fopen(filename, "r");
    char op;
    unsigned addr;
    int size;
    while(fscanf(file, "%c %x,%d",&op, &addr, &size)>0){
        printf("%c, %x %d\n",op,addr,size);
        switch(op){
            case 'L':	//load
                update(addr);
                break;
            case 'M':	//modify
                update(addr);
            case 'S':   //store
                update(addr);
                break;
        }
    }
    return;
}

int main(int argc, char* argv[])
{
    char *filename = malloc(100 * sizeof(char));

    parseOption(argc, argv, filename);
    simulateCache(filename);

    printSummary(num_hits, num_misses, num_evictions);
    return 0;
}


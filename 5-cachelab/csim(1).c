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

void addcacheHead(unsigned set, Node* node, Group* curgroup){
    node->next = curgroup->head->next;   // new head's next is old head
    node->prev = curgroup->head;         // new head's prev is old head's prev(root)
    curgroup->head->next->prev = node;   // new root
    curgroup->head->next = node;         // new head
    *(curgroup->size) = *(curgroup->size) + 1;
}

void deleteElement(unsigned set, Node* node, Group* curgroup){
    node->next->prev = node->prev;
    node->prev->next = node->next;
    //(curgroup->size)--;
    *(curgroup->size) = *(curgroup->size) - 1;
}

void evict(unsigned set, Node* newnode, Group* curgroup){
    deleteElement(set, curgroup->tail->prev, curgroup);  // remove the least used one
    addcacheHead(set, newnode, curgroup);
}

void update(unsigned address){
    unsigned mask = (0xffffffff >> (32-s));  // keep lower s bits
    unsigned set = mask & (address >> b);    // index
    unsigned tag = address >> (s + b);       // tag

    Group curgroup = cache[set];   

    Node* node = curgroup.head->next; 
    int found = 0;
    while(node != curgroup.tail){
        if(node->tag == tag){
            found = 1;
            break;
        }
        node = node->next;
    }

    if(found){
        num_hits++;   // hit
        deleteElement(set, node, &curgroup);  // delete from original position
        addcacheHead(set, node, &curgroup);    // add to head(recently used)
        printf("hit! the set number %d \n", set);
    }else{     // miss
        num_misses++;
        Node* newnode = malloc(sizeof(Node));
        newnode->tag = tag;
        if(*(curgroup.size) == E){  // full, needs eviction
            num_evictions++;
	        evict(set, newnode, &curgroup);
        }else
            addcacheHead(set, newnode, &curgroup);
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


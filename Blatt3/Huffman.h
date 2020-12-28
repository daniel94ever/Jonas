//
//  Huffman.h
//  Blatt3
//
//  Created by Jonas Fasterling on 22.12.20.
//

#ifndef Huffman_h
#define Huffman_h

typedef struct MinNode
{
    char item;
    unsigned int freq;
//    struct MinNode* left;
//    struct MinNode* right;
} minNode;

//TestTest

minNode* createNode(char data, unsigned int freq);

minNode* sortInput(char *item);

void swapMinNodes(minNode* to_swap, int index, int index_next);

void min_Sort(minNode* min_Array, int index_preNode);

unsigned int sizeOfArray(minNode* minNode);

unsigned int sizeOfInput(char *input);

void insertMinNode(minNode* nodeToAdd, minNode* nodeArray);

minNode* createMinHeap(minNode* minNode);

minNode* buildHuffmanTree(minNode* finishedMinHeap);

minNode* extractMin(minNode* minNode);

minNode* createHuffmanTree(char* characters);

void printArray(char* array[]);

void printfHuffman(minNode* minNode, int top, char* outputArray[]);

char* huffman_encode(char* string);

#endif /* Huffman_h */

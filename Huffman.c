//
//  Huffman.c
//  Blatt3
//
//  Created by Jonas Fasterling on 22.12.20.
//

#include "Huffman.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


//Neuen MinHeap Knoten erstellen
minNode* createNode(char data, unsigned int freq)
{
    minNode* temp = malloc(sizeof(minNode));
    
    if (temp)
    {
        temp->left = temp->right = NULL;
        temp->item = data;
        temp->freq = freq;
        
        return temp;
    }
    else
    {
        printf("Speicherfehler beim Erstellen eines MinHeap-Knotens\n");
        return NULL;
    }
}


//Vertauschen zweier Knoten
void swapMinNodes(minNode* to_swap, int index, int index_next)
{
    minNode temp = to_swap[index];
    to_swap[index] = to_swap[index_next];
    to_swap[index_next] = temp;
}


//Sortieren des Input Arrays nach dem MinHeap verfahren
void min_Sort(minNode* minArray, int index_preNode)
{
    int smallest = index_preNode;
    int left = 2 * index_preNode + 1;
    int right = 2 * index_preNode + 2;
    int smallest_left = 0;
    int smallest_right = 0;
    unsigned int heap_size = sizeOfArray(minArray);
    
    if (heap_size > left && minArray[left].freq < minArray[smallest].freq)
    {
        smallest = left;
        smallest_left = 1;
    }
    
    if (heap_size > right && minArray[right].freq < minArray[smallest].freq)
    {
        smallest = right;
        smallest_left = 0;
        smallest_right = 1;
    }
    
    if (smallest != index_preNode && smallest_left)
    {
        swapMinNodes(minArray, index_preNode, left);
        min_Sort(minArray, smallest);
    }
    if (smallest != index_preNode && smallest_right)
    {
        swapMinNodes(minArray, index_preNode, right);
        min_Sort(minArray, smallest);
    }
}


//Länge des minNode-Pointers bestimmen
unsigned int sizeOfArray(minNode* minNode)
{
//    int i_size = sizeof(&minNode) / sizeof(minNode[0]);
//    unsigned int ptr_size = 0;
//
////    int cnt = 0;
//    if (!minNode)
//    {
//        return 0;
//    }
//
////    minNode = *minNode[0];
//
//    while (minNode->freq != 0)
//    {
////        printf("%c: %i\n", minNode->item, minNode->freq);
//        ptr_size++;
//        minNode++;
//    }
//    return  ptr_size;
    return 0;
}


unsigned int sizeOfInput(char *input)
{
    unsigned int ptr_size = 0;
    
    while (*input != '\0')
    {
        ptr_size++;
        input++;
    }
    input = &input[0];
    
    return  ptr_size;
}



//Einfügen eines Knotens in den MinHeap
void insertMinNode(minNode* nodeToAdd, minNode* nodeArray)
{
    unsigned int ptr_size = sizeOfArray(nodeArray);
    
    while (nodeToAdd->freq < nodeArray[(ptr_size - 1) / 2].freq)
    {
        nodeArray[ptr_size] = nodeArray[(ptr_size -1) / 2];
        ptr_size = (ptr_size - 1) / 2;
    }
    nodeArray[ptr_size] = *nodeToAdd;
}


//Erstellen eines fertigen MinHeaps
 minNode* createMinHeap(minNode* minNode)
{
    unsigned int heapSize = sizeOfArray(minNode) -1;
    
    for (unsigned int i = (heapSize -1) / 2; i > 0; i--)
    {
        min_Sort(minNode, i);
    }
    
    return minNode;
}


//liest String ein und erzeugt daraus einen sortierten MinHeap
minNode* sortInput(char *characters)
{
    //Default werte zuordnen
    minNode* input[] = NULL;
//    int sizeOfHeap(input) = -1;

    //Solange man sich in dem String befindet
    while(*characters != '\0')
    {
        bool b_exist = false;

        //Solange man nicht alle Werte des Strings bearbeitet hat
        int i_size = sizeof(&input) / sizeof(input[0]);
        for (int i = 0; i < sizeOfArray(input); i++)
        {
            printf("%c = %c\n", *characters, input[i].item);
            //Wenn schon ein Knoten mit dem char besteht
            if (input[i].item == *characters)
            {
                //Anzahl erhöhen und tester erhöhen
                input[i].freq++;
                b_exist = true;
                break;
            }
        }
        //Wenn der tester nicht erhöht wurde
        if (!b_exist)
        {
            //Neuen Knoten erstellen und einsortieren
            if (input)
            {
                insertMinNode(createNode(*characters, 1), input);

            }
            else
            {
                input = createNode(*characters, 1);
            }
        }
        //Gesamten Heap sortieren
        min_Sort(input, 1);
        characters++;
    }
    int k = sizeOfArray(input);
    for (int j = 0; j < k - 1; j++)
    {
        printf("%c kam diesmal %i-mal vor.\n",input->item, input->freq);
        input++;
    }
    return input;
}

            
         
minNode* extractMin(minNode* src_minNode)
{
    minNode* temp;
    temp = malloc(sizeof(minNode));
    temp = &src_minNode[0];
    
    src_minNode[0] = src_minNode[sizeOfArray(src_minNode) - 1];
//    wieso geht kein free?
    free(&src_minNode[sizeOfArray(src_minNode) - 1]);
    
    
    min_Sort(src_minNode, 0);
    
    return temp;
}



minNode* createHuffmanTree(char* characters)
{
    minNode* left;
    minNode* right;
    minNode* top;
    
    minNode* minNode = sortInput(characters);
    
    while (sizeOfArray(minNode) != 1)
    {
        //Zwei Knoten mit der geringsten Häufigkeit extrahieren
        left = extractMin(minNode);
        right = extractMin(minNode);
        
        //Neuen internen Knoten erstellen, mit freq als summe beider Tochterknoten.
        //‘@‘ ist ein gewähltes Zeichen um interne Knoten zu erkennen.
        top = createNode('@', (left->freq + right->freq));
        
        //Die beiden extrahierten Knoten werden der linke und rechte des Internen:
        top->left = left;
        top->right = right;
        
        //Der Knoten wird dem MinHeap hinzugefügt.
        insertMinNode(minNode, top);
    }
    //Der übergebliebene Knoten ist der Wurzelnoten
    return extractMin(minNode);
}


void printArray(char* array[])
{
    int length = sizeof(*array) / sizeof(array[0]);
    
    for (int i = 0; i < length; i++)
    {
        printf("%c", *array[i]);
    }
    printf("\n");
}



void printfHuffman(minNode* minNode, int top, char* output_Array[])
{
    if(minNode[top].left)
    {
        *output_Array[top] = '0';
        printfHuffman(minNode, top + 1, output_Array);
    }
    
    if(minNode[top].right)
    {
        *output_Array[top] = '1';
        printfHuffman(minNode, top + 1, output_Array);
    }
    
    if (!minNode[top].left && !minNode[top].right)
    {
//        printf("%c: ", minNode[top].item);
//        printArray(output_Array);
    }
}


char* huffman_encode(char* string)
{
//    int length = sizeof(*string) / sizeof(string[0]);
    minNode* node = createHuffmanTree(string);
    
    printfHuffman(node, 0, &string);
    
    return string;
}

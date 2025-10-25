#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// demonstrating parallelism, not synchronization.

typedef struct Node{
    int data;
    struct Node* next;
} Node;

Node* createNode(int val){
    Node* newNode = (Node *)malloc(sizeof(Node));
    newNode->data = val;
    newNode->next = NULL;
    return newNode;
}

Node* head = NULL;

void insert(int val){
    Node* newNode = createNode(val);
    if(!head){
        head = newNode;
        return;
    }
    Node* temp = head;
    while(temp->next){
        temp=temp->next;
    }
    temp->next = newNode;
}

void* sumThread(void* arg){
    long long sum = 0;
    Node* temp = head;
    while(temp){
        sum += temp->data;
        temp = temp->next;
    }
    printf("Sum of linked list is %d\n",sum);
    return NULL;
}

void* middleThread(void *arg){
    Node* slow = head;
    Node* fast = head;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    if(slow){
        printf("middle element is : %d\n",slow->data);
    }
    pthread_exit(NULL);
}

void* maxThread(void *arg){
    if(!head){
        printf("List is empty !");
        pthread_exit(NULL);
    }
    int max = head->data;
    Node* temp = head->next;
    while(temp){
        if(temp->data > max) max = temp->data;
        temp = temp->next;
    }
    printf(" Max of linked list : %d\n",max);
    pthread_exit(NULL);
}

int main(){
    // insert(10);
    // insert(20);
    // insert(30);
    // insert(5);
    // insert(23);
    // insert(46);
    // insert(4);

    for(int i = 0; i < 100000; i++) {
        insert(rand() % 10000);
    }

    pthread_t t1,t2,t3;

    pthread_create(&t1,NULL,sumThread,NULL);
    pthread_create(&t2,NULL,middleThread,NULL);
    pthread_create(&t3,NULL,maxThread,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);

    return 0;
}

/*
Admin@DESKTOP-KMA1ERO MINGW64 /f/ME/3-Year/LABS/OS/OS/Thread Synchronization (main)
$ ./ll
middle element is : 2804
 Max of linked list : 9999
Sum of linked list is 468086939
*/


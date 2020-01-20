#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int dest;
    char edge;
    struct Node *next;
} Node;

Node * graph[100];

int counter = 0;

int stack[100], top = -1;

void push(int i) {
    if(top > 100) {
        printf("Stack Overflow!\n");
    } else {
        stack[++top] = i;
    }
}

void construct(char c) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->edge = c;
    n->dest = counter + 1;
    n->next = NULL;
    graph[counter] = n;
    push(counter+1);
    counter += 2;
}

int pop() {
    if(top == -1) {
        return -1;
    }
    return stack[top--];
}


Node *perfOR() {
    int dest, i;
    char e = 'e';
    Node *t;
    while(1) {

        /* Get the top */
        if(top == -1) break;
        dest = pop();

        /* New node for initial state */
        Node *n = (Node *)malloc(sizeof(Node));
        n->edge = 'e';
        n->next = NULL;
        i = 0;

        while(graph[i]->dest != dest) i += 2;
        n->dest = i;

        if(graph[counter] == NULL) graph[counter] = n;
        else {
            t = graph[counter];
            while(t->next) t = t->next;
            t->next = n;
        }
    }
    Node *F = (Node *)malloc(sizeof(Node));
    Node *n = graph[counter];
    counter++;
    F->edge = e;
    F->next = NULL;
    F->dest = counter;
    while(1) {
        i = n->dest;
        while(graph[i]) i = graph[i]->dest;
        graph[i] = F;
        if(n->next) n = n->next;
        else break;
    }
    return F;
}

void traverse(char w, int q0, Node *F) {
    Node *n = graph[q0];
    int t;
    while(1) {
        t = n->dest;
        if(graph[t]->edge != w) {
            if(n->next == NULL) {
                printf("Rejected\n");
                break;
            } else n = n->next;
        } else {
            while(1) {
                if(graph[t]->dest == F->dest) {
                    printf("Accepted\n");
                    break;
                } else t = graph[t]->dest;
            }
        }
        if(graph[t]->dest == F->dest) break;
    }
}

int main()
{
    char expr[100];
    printf("Enter postfix regexp\n");
    scanf("%s", expr);

    printf("Your regexp: %s\n", expr);

    int c = 0, q0;
    Node *F;
    for(; expr[c] != '\0'; c++) {
        if(expr[c] != '|') {
                construct(expr[c]);
                printf("Constructed %c\n", expr[c]);
        }
        else {
            q0 = counter;
            printf("Initial state: %d\n", q0);
            F = perfOR();
            printf("Final State : %d\n", F->dest);
        }
    }

    printf("Enter a string to test:\n");
    char w;
    scanf("%s", &w);
    traverse(w, q0, F);

    return 0;
}

# CD Lab

## 1. Thomson's Construction 

Can use it to understand what is happening.

#### *A Node:*

```
  typedef struct Node {
    int dest;
    char edge;
    struct Node *next;
} Node;
     ______________________
    |       |      |       |
    |   1   |   a  |  NULL | 
    |_______|______|_______|   
    
```

####  *The graph array (final):*
```
  Node * graph[100]; 
  
   ______      ______________________
  |      |    |       |      |       |
 0|   ---|--->|   1   |   a  |  NULL | 
  |______|    |_______|______|_______|
  |      |    |       |      |       |
 1|   ---|--->|   5   |   e  |  NULL | 
  |______|    |_______|______|_______|
  |      |    |       |      |       |
 2|   ---|--->|   3   |   b  |  NULL | 
  |______|    |_______|______|_______|
  |      |    |       |      |       |
 3|   ---|--->|   5   |   e  |  NULL | 
  |______|    |_______|______|_______|      ______________________
  |      |    |       |      |       |     |       |      |       |
 4|   ---|--->|   2   |   e  |    ---|---->|   1   |   e  |  NULL | 
  |______|    |_______|______|_______|     |_______|______|_______|
  |      |
 5|      |
  |______|
  |      |
 .|      | 
  |      |
  
```

#### *The counter variable:*
```
  int counter = 0;
```
###### It is used to keep count of each of states


#### The stack used:
###### It is used to store the destination node of each operand
```
  int stack[100], top = -1;
  
    |     |
    |_____|     
    |     |
    |  3  |
    |_____|     
    |     |
    |  1  |
    |_____|
```


#### construct function:
###### Used to construct an edge for each operand with it's opriginating and reaching nodes

```
  void construct(char c) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->edge = c;
    n->dest = counter + 1;
    n->next = NULL;
    graph[counter] = n;
    push(counter+1);
    counter += 2;
}
```
![after construct('a')](a.png)
###### This is equivalent to (in memory):
```
  graph[]
  for c = 'a' & counter = 0
   ______      ______________________
  |      |    |       |      |       |
 0|   ---|--->|   1   |   a  |  NULL | 
  |______|    |_______|______|_______|
  |      |
 1|      | 
  |      |
```

#### main function:
###### Till construction of each operand

```
int main() {
    char expr[100];
    printf("Enter postfix regexp\n");
    scanf("%s", expr); /* ab| */

    printf("Your regexp: %s\n", expr);

    int c = 0, q0;
    Node *F;
    for(; expr[c] != '\0'; c++) {
        if(expr[c] != '|') {
                construct(expr[c]);
                printf("Constructed %c\n", expr[c]);
         else {
              ...
              ...
          
 ```
 ### expr = "ab|"
 ```
           _____________________________
          |       |      |       |      |
     expr |  'a'  |  'b' |  '|'  |  \0  |
          |_______|______|_______|______|
 ```
 
   ### 1st Iteration:
   when expr[c] = 'a'
   ###### after construct('a'):
   ![after construct('a')](a.png)
   O/P: 'Constructed a' 

   ###### This is equivalent to (in memory):
   ```
    graph[]
     ______      ______________________
    |      |    |       |      |       |
   0|   ---|--->|   1   |   a  |  NULL | 
    |______|    |_______|______|_______|
    |      |
   1|      | 
    |      |
  ```
   ###### counter becomes 2 from 0

   ### 2nd Iteration:
   when expr[c] = 'b'
   ###### after construct('b'):
   ![after construct('a')](b.png)
   O/P: 'Constructed b'

   ###### This is equivalent to (in memory):

   ```
     graph[]
      ______      ______________________
     |      |    |       |      |       |
    0|   ---|--->|   1   |   a  |  NULL | 
     |______|    |_______|______|_______|
     |      |
    1|      |
     |______|     ______________________
     |      |    |       |      |       |
    2|   ---|--->|   3   |   b  |  NULL | 
     |______|    |_______|______|_______|
     |      |
    3|      |
     |      |
   ```
   ###### counter becomes 4 from 2
   
   #### main function (cont..):
    ```
    else {
            q0 = counter; /* 4 */
            printf("Initial state: %d\n", q0); /* 4 */
            F = perfOR();  
            ...
            ...
    ``` 
   ### ```Node * perfOR()``` function: (returns final state)
   #### Till construction of initial state:
   ```
    Node *perfOR() {

          int dest, i;
          Node *t;
   ```
   ###### ```t``` will point to initial state which is ```graph[4]```
   ```
   ```
   ### first-iteration of while loop in ```perfOR()```:
   ```
        while(1) {

              /* Get the top */
              if(top == -1) break;
              dest = pop(); /* get destination of one of the operand */
   ```
   ###### ```dest``` has destination of the last operand scanned
   ```
   ```
   
   ```
   
                                  |     |
             _____                |_____|
            |     | dest = pop()  |     |
      dest  |  3  |<--------------|--3  | 
            |_____|               |_____|
                                  |     |
                                  |  1  | 
                                  |_____|
                                   stack
   
   ```
   ###### create a node for e (epsilon) transition between inistial node and starting node of the operand 

   ```
              /* New node for initial state */
              Node *n = (Node *)malloc(sizeof(Node));
              n->edge = 'e'; /* epsilon */
              n->next = NULL;
                               ______________________
                              |       |      |       |
                            n |       |   e  |  NULL | 
                              |_______|______|_______|   
   ```
   ######  Search for the entry in graph array which points to a node whose destination = destination obtained by popping the stack
   ######  i.e. ```graph[i]->dest == dest```, where i gives the desired entry in graph array
   ```
             i = 0;
    
              while(graph[i]->dest != dest) i += 2;
   ```  
   ###### assign i with destination of new node for e-transition from initial state for performing OR operation
              n->dest = i;
   ```
   ```
       ______________________
      |       |      |       |
    n |   2   |   e  |  NULL | 
      |_______|______|_______|   
   ```
   ```
   ###### if entry corresponding to initial node in graph array is empty, assign it with e-transition 
              if(graph[counter] == NULL) graph[counter] = n;
    ```
    
   ###### i.e. 
   ```
     graph[]
      ______      ______________________
     |      |    |       |      |       |
    0|   ---|--->|   1   |   a  |  NULL | 
     |______|    |_______|______|_______|
     |      |
    1|      |
     |______|     ______________________
     |      |    |       |      |       |
    2|   ---|--->|   3   |   b  |  NULL | 
     |______|    |_______|______|_______|
     |      |
    3|      |
     |______|     ______________________
     |      |    |       |      |       |
    4|    --|--->|   2   |   e  |  NULL | 
     |______|    |_______|______|_______|   
     |      |
     |      |
   ```
   
  ### i.e
  ![4-e-2](e1.png)
  
  
  ###### else go to end of nodes connected to that entry and make next assign it with the e-transition
              else {
                  t = graph[counter];
                  while(t->next) t = t->next;
                  t->next = n;
              }
          }
          
          ...
          ...
   ```
   ```
   ### second-iteration of while loop in ```perfOR()```:
   ```
        while(1) {

              /* Get the top */
              if(top == -1) break;
              dest = pop(); /* get destination of one of the operand */
   ```
   ###### ```dest``` has destination of the last operand scanned
   ```
   
                                  |     |
             _____                |_____|
            |     | dest = pop()  |     |
      dest  |  1  |<--------------|--1  | 
            |_____|               |_____|
                                    stack
   ```
   ###### create a node for e (epsilon) transition between inistial node and starting node of the operand 
   ```
              /* New node for initial state */
              Node *n = (Node *)malloc(sizeof(Node));
              n->edge = 'e'; /* epsilon */
              n->next = NULL;
                               ______________________
                              |       |      |       |
                            n |       |   e  |  NULL | 
                              |_______|______|_______|   
   ```
   ######  Search for the entry in graph array which points to a node whose destination = destination obtained by popping the stack
   ######  i.e. ```graph[i]->dest == dest```, where i gives the desired entry in graph array
   ```
             i = 0;
    
              while(graph[i]->dest != dest) i += 2;
   ```  
   ###### assign i with destination of new node for e-transition from initial state for performing OR operation
              n->dest = i;
   ```
   ```
       ______________________
      |       |      |       |
    n |   0   |   e  |  NULL | 
      |_______|______|_______|   
   ```
   ```
   ###### if entry corresponding to initial node in graph array is empty, assign it with e-transition 
              if(graph[counter] == NULL) graph[counter] = n;
    ```
   ###### here this condition will be false from second iteration onwards 
   
   ###### thus, else go to end of nodes connected to that entry and make next assign to e-transition
   ```
              else {
                  t = graph[counter];
                  while(t->next) t = t->next;
                  t->next = n;
              }
          }
          
          ...
          ...
   ```
   ###### i.e.
   ```
     graph[]
      ______      ______________________
     |      |    |       |      |       |
    0|   ---|--->|   1   |   a  |  NULL | 
     |______|    |_______|______|_______|
     |      |
    1|      |
     |______|     ______________________
     |      |    |       |      |       |
    2|   ---|--->|   3   |   b  |  NULL | 
     |______|    |_______|______|_______|
     |      |
    3|      |
     |______|     ______________________      ____________________
     |      |    |       |      |       |    |      |      |      |
    4|    --|--->|   2   |   e  |     --|--->|   0  |   e  | NULL |
     |______|    |_______|______|_______|    |______|______|______|      
     |      |
     |      |
   ```
   ###### i.e
   ![4-e-1](4.png)
   
   

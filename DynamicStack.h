
struct Stack {
    int top;
    int capacity;
    int *array;
};


struct Stack *createStack(int capacity);

int isEmpty(struct Stack *S);

int size(struct Stack *S);

int isFull(struct Stack *S);

void doubleStack(struct Stack *S);

void push(struct Stack *S, int data);

int pop(struct Stack *S);

int peek(struct Stack *S);

void deleteStack(struct Stack *S);

/*int main(){
    int i = 0, capacity = 5;
    // create a stack of capacity 5
    struct Stack *stk = createStack(capacity);

    for(i = 0; i <= 2 * capacity; i++){
        push(stk, i);
    }

    printf("Top element is %d\n", peek(stk));
    printf("Stack size is %d\n", size(stk));

    for (i = 0; i <= capacity; i++){
        printf("Popped element is %d\n", pop(stk));
    }

    if (isEmpty(stk))
        printf("Stack is empty");
    else
        printf("Stack is not empty");

    deleteStack(stk);
    return 0;
}
*/

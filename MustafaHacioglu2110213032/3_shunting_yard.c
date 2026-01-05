#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Stack structure
typedef struct {
    char items[MAX];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, char value) {
    if (s->top < MAX - 1) {
        s->items[++(s->top)] = value;
    }
}

char pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    }
    return '\0';
}

char peek(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[s->top];
    }
    return '\0';
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

int isRightAssociative(char op) {
    return (op == '^');
}

void removeSpaces(char* str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != ' ' && str[i] != '\t') {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

void infixToPostfix(char* infix, char* postfix, int verbose) {
    Stack operators;
    initStack(&operators);
    
    int i = 0, j = 0;
    
    if (verbose) {
        printf("\n=== STEP BY STEP CONVERSION ===\n\n");
        printf("%-5s %-10s %-15s %-20s\n", "Step", "Token", "Stack", "Output");
        printf("----------------------------------------------------------\n");
    }
    
    int step = 1;
    
    while (infix[i] != '\0') {
        char token = infix[i];
        
        if (isalnum(token)) {
            postfix[j++] = token;
            if (verbose) {
                postfix[j] = '\0';
                printf("%-5d %-10c %-15s %-20s\n", step++, token, 
                       isEmpty(&operators) ? "empty" : operators.items, postfix);
            }
        }
        else if (token == '(') {
            push(&operators, token);
            if (verbose) {
                printf("%-5d %-10c %-15s %-20s\n", step++, token, 
                       operators.items, postfix);
            }
        }
        else if (token == ')') {
            while (!isEmpty(&operators) && peek(&operators) != '(') {
                postfix[j++] = pop(&operators);
            }
            if (!isEmpty(&operators)) {
                pop(&operators);
            }
            if (verbose) {
                postfix[j] = '\0';
                printf("%-5d %-10c %-15s %-20s\n", step++, token, 
                       isEmpty(&operators) ? "empty" : operators.items, postfix);
            }
        }
        else if (isOperator(token)) {
            while (!isEmpty(&operators) && peek(&operators) != '(' &&
                   (precedence(peek(&operators)) > precedence(token) ||
                    (precedence(peek(&operators)) == precedence(token) && 
                     !isRightAssociative(token)))) {
                postfix[j++] = pop(&operators);
            }
            push(&operators, token);
            if (verbose) {
                postfix[j] = '\0';
                printf("%-5d %-10c %-15s %-20s\n", step++, token, 
                       operators.items, postfix);
            }
        }
        i++;
    }
    
    while (!isEmpty(&operators)) {
        postfix[j++] = pop(&operators);
        if (verbose) {
            postfix[j] = '\0';
            printf("%-5d %-10s %-15s %-20s\n", step++, "(pop)", 
                   isEmpty(&operators) ? "empty" : operators.items, postfix);
        }
    }
    
    postfix[j] = '\0';
}

void runTests() {
    printf("\n=== TEST CASES ===\n\n");
    
    char* tests[][2] = {
        {"A+B", "AB+"},
        {"A+B*C", "ABC*+"},
        {"(A+B)*C", "AB+C*"},
        {"A+B*C+D", "ABC*+D+"},
        {"(A+B)*(C+D)", "AB+CD+*"},
        {"A^B^C", "ABC^^"},
    };
    
    int numTests = 6;
    char postfix[MAX];
    int passed = 0;
    
    printf("%-20s %-20s %-10s\n", "Infix", "Expected", "Result");
    printf("-------------------------------------------------------\n");
    
    for (int i = 0; i < numTests; i++) {
        infixToPostfix(tests[i][0], postfix, 0);
        int match = strcmp(postfix, tests[i][1]) == 0;
        if (match) passed++;
        printf("%-20s %-20s %-10s\n", tests[i][0], tests[i][1], 
               match ? "PASS" : "FAIL");
    }
    
    printf("\nTests Passed: %d/%d\n", passed, numTests);
}

int main() {
    int choice;
    char infix[MAX], postfix[MAX];
    
    printf("==================================================\n");
    printf("   SHUNTING YARD ALGORITHM - INFIX TO POSTFIX\n");
    printf("==================================================\n\n");
    
    printf("1. Simple Conversion\n");
    printf("2. Step-by-Step Conversion\n");
    printf("3. Run Test Cases\n");
    printf("\nChoice: ");
    scanf("%d", &choice);
    getchar();
    
    switch (choice) {
        case 1:
            printf("\nEnter infix: ");
            fgets(infix, MAX, stdin);
            infix[strcspn(infix, "\n")] = 0;
            removeSpaces(infix);
            infixToPostfix(infix, postfix, 0);
            printf("\nInfix:   %s\n", infix);
            printf("Postfix: %s\n", postfix);
            break;
            
        case 2:
            printf("\nEnter infix: ");
            fgets(infix, MAX, stdin);
            infix[strcspn(infix, "\n")] = 0;
            removeSpaces(infix);
            infixToPostfix(infix, postfix, 1);
            printf("\nFinal Result:\n");
            printf("Infix:   %s\n", infix);
            printf("Postfix: %s\n", postfix);
            break;
            
        case 3:
            runTests();
            break;
            
        default:
            printf("Invalid choice!\n");
    }
    
    return 0;
}

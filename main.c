#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 10

// Response codes to indicate success or failure
typedef enum {
    RESPONSE_OK,
    RESPONSE_ERROR_NULL_POINTER,
    RESPONSE_ERROR_ALLOCATION_FAILED,
    RESPONSE_ERROR_STACK_OVERFLOW,
    RESPONSE_ERROR_STACK_UNDERFLOW
} ResponseCode;

// Struct to hold the response object with error code and, if applicable, return value
typedef struct {
    ResponseCode code;
    char *value;  // For holding the return value of operations, if applicable
} Response;

// Define the stack structure
typedef struct {
    char **array;
    int top;
    int capacity;
} StringStack;

// Function to initialize the stack
Response stack_init(StringStack *stack) {
    if (!stack) {
        return (Response){.code = RESPONSE_ERROR_NULL_POINTER, .value = NULL};
    }

    stack->array = (char **)malloc(INITIAL_CAPACITY * sizeof(char *));
    if (!stack->array) {
        return (Response){.code = RESPONSE_ERROR_ALLOCATION_FAILED, .value = NULL};
    }

    stack->top = -1;
    stack->capacity = INITIAL_CAPACITY;

    return (Response){.code = RESPONSE_OK, .value = NULL};
}

// Function to expand the stack's capacity
Response stack_expand(StringStack *stack) {
    if (!stack) {
        return (Response){.code = RESPONSE_ERROR_NULL_POINTER, .value = NULL};
    }

    int new_capacity = stack->capacity * 2;
    char **new_array = (char **)realloc(stack->array, new_capacity * sizeof(char *));
    if (!new_array) {
        return (Response){.code = RESPONSE_ERROR_ALLOCATION_FAILED, .value = NULL};
    }

    stack->array = new_array;
    stack->capacity = new_capacity;

    return (Response){.code = RESPONSE_OK, .value = NULL};
}

// Function to push a string onto the stack
Response stack_push(StringStack *stack, const char *str) {
    if (!stack) {
        return (Response){.code = RESPONSE_ERROR_NULL_POINTER, .value = NULL};
    }
    if (!str) {
        return (Response){.code = RESPONSE_ERROR_NULL_POINTER, .value = NULL};
    }

    if (stack->top == stack->capacity - 1) {
        Response res = stack_expand(stack);
        if (res.code != RESPONSE_OK) {
            return res;
        }
    }

    stack->array[++stack->top] = strdup(str);
    if (!stack->array[stack->top]) {
        return (Response){.code = RESPONSE_ERROR_ALLOCATION_FAILED, .value = NULL};
    }

    return (Response){.code = RESPONSE_OK, .value = NULL};
}

// Function to pop a string from the stack
Response stack_pop(StringStack *stack, char **result) {
    if (!stack || !result) {
        return (Response){.code = RESPONSE_ERROR_NULL_POINTER, .value = NULL};
    }
    if (stack->top == -1) {
        return (Response){.code = RESPONSE_ERROR_STACK_UNDERFLOW, .value = NULL};
    }

    *result = stack->array[stack->top--];
    return (Response){.code = RESPONSE_OK, .value = *result};
}

// Function to peek the top string of the stack
Response stack_peek(StringStack *stack, char **result) {
    if (!stack || !result) {
        return (Response){.code = RESPONSE_ERROR_NULL_POINTER, .value = NULL};
    }
    if (stack->top == -1) {
        return (Response){.code = RESPONSE_ERROR_STACK_UNDERFLOW, .value = NULL};
    }

    *result = stack->array[stack->top];
    return (Response){.code = RESPONSE_OK, .value = *result};
}

// Function to free the stack's memory
Response stack_free(StringStack *stack) {
    if (!stack) {
        return (Response){.code = RESPONSE_ERROR_NULL_POINTER, .value = NULL};
    }

    for (int i = 0; i <= stack->top; i++) {
        free(stack->array[i]);
    }

    free(stack->array);
    stack->array = NULL;
    stack->top = -1;
    stack->capacity = 0;

    return (Response){.code = RESPONSE_OK, .value = NULL};
}

// A simple test function for the stack
void test_stack() {
    StringStack stack;
    Response res = stack_init(&stack);
    if (res.code != RESPONSE_OK) {
        printf("Failed to initialize stack\n");
        return;
    }

    res = stack_push(&stack, "Hello");
    if (res.code != RESPONSE_OK) {
        printf("Failed to push element\n");
        return;
    }

    res = stack_push(&stack, "World");
    if (res.code != RESPONSE_OK) {
        printf("Failed to push element\n");
        return;
    }

    char *top;
    res = stack_peek(&stack, &top);
    if (res.code == RESPONSE_OK) {
        printf("Top element: %s\n", top);
    }

    res = stack_pop(&stack, &top);
    if (res.code == RESPONSE_OK) {
        printf("Popped element: %s\n", top);
        free(top);  // Remember to free the popped value
    }

    res = stack_free(&stack);
    if (res.code != RESPONSE_OK) {
        printf("Failed to free stack\n");
    }
}

int main() {
    test_stack();
    return 0;
}

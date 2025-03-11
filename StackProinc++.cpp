#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

class SecureStack {
private:
    std::unique_ptr<std::string[]> stack;
    size_t capacity;
    size_t top;

    void expand() {
        size_t newCapacity = capacity * 2;
        std::unique_ptr<std::string[]> newStack = std::make_unique<std::string[]>(newCapacity);
        for (size_t i = 0; i < top; ++i) {
            newStack[i] = std::move(stack[i]);
        }
        stack = std::move(newStack);
        capacity = newCapacity;
    }

public:
    SecureStack(size_t initialCapacity = 4)
        : capacity(initialCapacity), top(0), stack(std::make_unique<std::string[]>(initialCapacity)) {}

    void push(const std::string& value) {
        if (top == capacity) {
            expand();
        }
        stack[top++] = value;
    }

    std::string pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack underflow: Cannot pop from an empty stack");
        }
        return std::move(stack[--top]);
    }

    const std::string& peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty: Cannot peek");
        }
        return stack[top - 1];
    }

    bool isEmpty() const {
        return top == 0;
    }
};

int main() {
    try {
        SecureStack stack;
        stack.push("Hello");
        stack.push("World");
        stack.push("Secure");
        stack.push("Stack");
        stack.push("C++");
        
        while (!stack.isEmpty()) {
            std::cout << "Popped: " << stack.pop() << std::endl;
        }

        std::cout << "Attempting to pop from empty stack..." << std::endl;
        stack.pop(); // Should throw exception
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
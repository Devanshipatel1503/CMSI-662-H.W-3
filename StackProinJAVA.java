
import java.util.Arrays;

class SecureStack {
    private String[] stack;
    private int capacity;
    private int top;

    public SecureStack(int initialCapacity) {
        if (initialCapacity <= 0) {
            throw new IllegalArgumentException("Initial capacity must be greater than zero");
        }
        this.capacity = initialCapacity;
        this.stack = new String[capacity];
        this.top = 0;
    }

    public SecureStack() {
        this(4);
    }

    private void expand() {
        capacity *= 2;
        stack = Arrays.copyOf(stack, capacity);
    }

    public void push(String value) {
        if (value == null) {
            throw new IllegalArgumentException("Null values are not allowed in the stack");
        }
        if (top == capacity) {
            expand();
        }
        stack[top++] = value;
    }

    public String pop() {
        if (isEmpty()) {
            throw new IllegalStateException("Stack underflow: Cannot pop from an empty stack");
        }
        String value = stack[--top];
        stack[top] = null; 
        return value;
    }

    public String peek() {
        if (isEmpty()) {
            throw new IllegalStateException("Stack is empty: Cannot peek");
        }
        return stack[top - 1];
    }

    public boolean isEmpty() {
        return top == 0;
    }

    public static void main(String[] args) {
        try {
            SecureStack stack = new SecureStack();
            stack.push("Hello");
            stack.push("World");
            stack.push("Secure");
            stack.push("Stack");
            stack.push("Java");
            
            while (!stack.isEmpty()) {
                System.out.println("Popped: " + stack.pop());
            }

            System.out.println("Attempting to pop from an empty stack...");
            stack.pop(); 
        } catch (Exception e) {
            System.err.println("Exception: " + e.getMessage());
        }
    }
}

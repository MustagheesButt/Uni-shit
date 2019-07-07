public class Node<T> {
    T value;

    Node(T value) {
        this.value = value;
    }

    public String toString() {
        return this.value.toString();
    }

    public boolean equals(Object node) {
        return this.value.equals( ((Node<?>)node).value);
    }
}
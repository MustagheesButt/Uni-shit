import java.util.*;

class Main {
    public static void main(String[] args) {
        BFS bfs = new BFS();

        bfs.printGraph();
        bfs.search(0, 6);
    }
}
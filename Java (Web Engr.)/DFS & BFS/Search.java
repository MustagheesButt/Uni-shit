import java.util.ArrayList;

public abstract class Search {
    int extensions;
    int enqueues;

    public ArrayList<ArrayList<Node<Integer>>> graph;

    Search() {
        this.extensions = 0;
        this.enqueues = 0;

        this.graph = new ArrayList<ArrayList<Node<Integer>>> ();
    }

    public abstract void search(int startNode, int goal);

    public void printGraph() {
        for (int i = 0; i < this.graph.size(); i++) {
            System.out.print(i + ": ");
            for (int j = 0; j < this.graph.get(i).size(); j++) {
                System.out.print(this.graph.get(i).get(j).value + " ");
            }
            System.out.print("\n");
        }
    }

    public void printMetaInfo() {
        System.out.println("Extensions: " + this.extensions);
        System.out.println("Enqueues: " + this.enqueues);
    }

    /*
     * Take a path's last node, get its neighbours and return the paths in which each neighbour is joined with the original path.
     */
    public abstract ArrayList<ArrayList<Node<Integer>>> extend(ArrayList<Node<Integer>> path);

    public abstract void enqueue(ArrayList<ArrayList<Node<Integer>>> paths);

    public ArrayList<Node<Integer>> getNeighboursOf(int node) {
        return this.graph.get(node);
    }
}
import java.util.*;

class BFS extends Search {
    Queue<ArrayList<Node<Integer>>> queue;

    BFS() {

        for (int i = 0; i < 7; i++) {
            this.graph.add(new ArrayList<Node<Integer>> ());
        }

        this.graph.get(0).addAll(Arrays.asList(new Node<Integer>(1), new Node<Integer>(2)));
        this.graph.get(1).addAll(Arrays.asList(new Node<Integer>(0), new Node<Integer>(2), new Node<Integer>(4)));
        this.graph.get(2).addAll(Arrays.asList(new Node<Integer>(0), new Node<Integer>(1), new Node<Integer>(3)));
        this.graph.get(3).addAll(Arrays.asList(new Node<Integer>(2), new Node<Integer>(5)));
        this.graph.get(4).addAll(Arrays.asList(new Node<Integer>(1), new Node<Integer>(6)));
        this.graph.get(5).addAll(Arrays.asList(new Node<Integer>(3)));
        this.graph.get(6).addAll(Arrays.asList(new Node<Integer> (4)));
    }

    public ArrayList<ArrayList<Node<Integer>>> extend(ArrayList<Node<Integer>> path) {
        this.extensions += 1;

        ArrayList<ArrayList<Node<Integer>>> extensions = new ArrayList<ArrayList<Node<Integer>>> ();

        ArrayList<Node<Integer>> neighbours = this.getNeighboursOf(path.get(path.size() - 1).value);
        for (int j = 0; j < neighbours.size(); j++) {
            ArrayList<Node<Integer>> temp = new ArrayList<Node<Integer>>(path);
            temp.add(neighbours.get(j));
            
            extensions.add(temp);
        }

        return extensions;
    }

    public void enqueue(ArrayList<ArrayList<Node<Integer>>> paths) {
        for (int i = 0; i < paths.size(); i++) {
            this.enqueues += 1;
            this.queue.add(paths.get(i));
        }
    }

    public void search(int startNode, int goal) {
        this.queue = new LinkedList<ArrayList<Node<Integer>>>();

        ArrayList<Node<Integer>> temp = new ArrayList<Node<Integer>>();
        temp.add(new Node<Integer>(startNode));

        queue.add(temp);
        this.enqueues += 1;
        
        while (!queue.isEmpty()) {
            ArrayList<Node<Integer>> path = queue.remove();
            
            // look for goal
            if (path.contains(new Node<Integer> (goal))) {
                System.out.println(path);
                break;
            }

            // extend
            ArrayList<ArrayList<Node<Integer>>> extensions = this.extend(path);
            this.enqueue(extensions);
        }

        this.printMetaInfo();
    }
}
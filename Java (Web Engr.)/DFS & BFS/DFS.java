import java.util.*;

class DFS extends Search {
    ArrayList<Integer> visited;
    Stack<ArrayList<Node<Integer>>> stack;

    DFS() {
        this.visited = new ArrayList<Integer>();

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
            this.stack.push(paths.get(i));
        }
    }

    public void search(int startNode, int goal) {
        this.stack = new Stack<ArrayList<Node<Integer>>>();

        ArrayList<Node<Integer>> temp = new ArrayList<Node<Integer>>();
        temp.add(new Node<Integer>(startNode));

        stack.push(temp);
        this.enqueues += 1;
        
        while (!stack.isEmpty()) {
            ArrayList<Node<Integer>> path = stack.pop();
            
            // look for goal
            if (path.contains(new Node<Integer> (goal))) {
                System.out.println(path);
                break;
            }

            int i = path.size() - 1;
            if (!this.visited.contains(path.get(i).value)) {
                this.visited.add(path.get(i).value);

                // extend
                ArrayList<ArrayList<Node<Integer>>> extensions = this.extend(path);
                this.enqueue(extensions);
                
            } else {
                System.out.println("Discarding: " + path);
            }
        }

        this.printMetaInfo();
    }
}
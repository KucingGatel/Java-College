import java.util.*;

class Product {
    int id;
    String name;
    double[] features;

    Product(int id, String name, double[] features) {
        this.id = id;
        this.name = name;
        this.features = features;
    }
}

class Neighbor {
    int id;
    double distance;

    Neighbor(int id, double distance) {
        this.id = id;
        this.distance = distance;
    }
}

public class KNN {
    private List<Product> products;
    private int k;

    public KNN(int k) {
        this.k = k;
        this.products = new ArrayList<>();
    }

    public void addProduct(Product product) {
        products.add(product);
    }

    private double calculateEuclideanDistance(double[] features1, double[] features2) {
        double sum = 0.0;
        for (int i = 0; i < features1.length; i++) {
            sum += Math.pow(features1[i] - features2[i], 2);
        }
        return Math.sqrt(sum);
    }

    public List<Product> recommend(double[] userFeatures) {
        PriorityQueue<Neighbor> neighbors = new PriorityQueue<>(Comparator.comparingDouble(n -> n.distance));

        for (Product product : products) {
            double distance = calculateEuclideanDistance(product.features, userFeatures);
            neighbors.add(new Neighbor(product.id, distance));
            if (neighbors.size() > k) {
                neighbors.poll();
            }
        }

        List<Product> recommendations = new ArrayList<>();
        while (!neighbors.isEmpty()) {
            Neighbor neighbor = neighbors.poll();
            recommendations.add(getProductById(neighbor.id));
        }
        Collections.reverse(recommendations); // Reverse to get the nearest neighbors first
        return recommendations;
    }

    private Product getProductById(int id) {
        for (Product product : products) {
            if (product.id == id) {
                return product;
            }
        }
        return null;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        KNN recommender = new KNN(5); // Setting k to 5

        // Adding sample products
        recommender.addProduct(new Product(1, "Product A", new double[] {  }));
        recommender.addProduct(new Product(2, "Product B", new double[] {  }));
        recommender.addProduct(new Product(3, "Product C", new double[] {  }));
        recommender.addProduct(new Product(4, "Product D", new double[] {  }));
        recommender.addProduct(new Product(5, "Product E", new double[] {  }));

        // Taking user input for features
        System.out.println("Masukkan fitur produk pengguna (angka): ");
        String[] userInput = scanner.nextLine().split(" ");
        double[] userFeatures = new double[userInput.length];
        for (int i = 0; i < userInput.length; i++) {
            userFeatures[i] = Double.parseDouble(userInput[i]);
        }

        // Getting recommendations
        List<Product> recommendations = recommender.recommend(userFeatures);

        // Displaying recommendations
        System.out.println("\nRekomendasi produk untuk Anda:");
        for (Product product : recommendations) {
            System.out.println("ID: " + product.id + ", Nama: " + product.name);
        }

        scanner.close();
    }
}

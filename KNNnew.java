import java.util.*;

class KNN {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Meminta jumlah data dan jumlah fitur
        System.out.print("Masukkan jumlah data: ");
        int n = scanner.nextInt();
        System.out.print("Masukkan jumlah fitur: ");
        int m = scanner.nextInt();
        
        // Meminta input data
        double[][] data = new double[n][m];
        System.out.println("Masukkan data:");
        for (int i = 0; i < n; i++) {
            System.out.printf("Data ke-%d: ", i + 1);
            for (int j = 0; j < m; j++) {
                data[i][j] = scanner.nextDouble();
            }
        }
        
        // Meminta input data yang akan diprediksi
        double[] newData = new double[m];
        System.out.println("\nMasukkan data baru yang akan diprediksi:");
        for (int i = 0; i < m; i++) {
            System.out.printf("Fitur ke-%d: ", i + 1);
            newData[i] = scanner.nextDouble();
        }
        
        // Meminta input nilai k
        System.out.print("\nMasukkan nilai k: ");
        int k = scanner.nextInt();
        
        // Menghitung jarak Euclidean dan menemukan k tetangga terdekat
        double[][] distances = new double[n][2];
        for (int i = 0; i < n; i++) {
            double dist = 0.0;
            for (int j = 0; j < m; j++) {
                dist += Math.pow(data[i][j] - newData[j], 2);
            }
            distances[i][0] = Math.sqrt(dist); // Jarak Euclidean
            distances[i][1] = i; // Index data
        }
        
        // Mengurutkan berdasarkan jarak (kolom pertama)
        Arrays.sort(distances, Comparator.comparingDouble(a -> a[0]));
        
        // Menampilkan k tetangga terdekat
        System.out.printf("\n%d Tetangga terdekat:\n", k);
        for (int i = 0; i < k; i++) {
            int index = (int) distances[i][1];
            System.out.printf("Data ke-%d dengan jarak %.2f\n", index + 1, distances[i][0]);
        }
        
        scanner.close();
    }
}

import java.util.Scanner;

public class Entrada {
    public static void main (String[] args) {
        Scanner input = new Scanner(System.in);
        int num;
        System.out.print("Digite um numero: ");

        num = input.nextInt();

        System.out.println("Numero digitado: " + num);

        input.close();
    }
}
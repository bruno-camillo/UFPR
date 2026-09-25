public class Principal {
    public static void main (String[] args){
        // Objeto 1 - data do carnaval 2027
        Data dataCarnaval = new Data();
        dataCarnaval.setDia(8);
        dataCarnaval.setMes(2);
        dataCarnaval.setAno(2027);
        System.out.println(dataCarnaval);

        // Objeto 2- data do seu aniversário em 2027
        Data meuAniversario = new Data();
        meuAniversario.setDia(5);
        meuAniversario.setMes(2);
        meuAniversario.setAno(2028);
        System.out.println(meuAniversario.toString());

    }
}
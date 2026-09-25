public class Data {
    // Atributos
    private int dia;
    private int mes;
    private int ano;
    private boolean ehBissexto;

    // Métodos get
    public int getDia() {
        return this.dia;
    }

    public int getMes() {
        return this.mes;
    }

    public int getAno() {
        return this.ano;
    }
    
    public boolean isBissexto (){
        return this.ehBissexto;
    }

    // Métodos Set
    public void setDia(int dia){
        if (dia >= 1 && dia <= 31)
            this.dia = dia;
    }

    public void setMes(int mes){
        if (mes >= 1 && mes <= 12)
            this.mes = mes;
    }

    public void setAno(int ano){
        if (ano >= 0 && ano <= 2026)
            this.ano = ano;
    }

    public void setAnoBissexto (boolean ehBissexto){
        this.ehBissexto = ehBissexto;
    }

    public String toString() {
        return String.format("%d/%d/%d", this.dia, this.mes, this.ano);
    }
}
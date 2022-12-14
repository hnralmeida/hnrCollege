/*
*   =========================================================================================
*   AUTORES: 	
*   			Henrique Almeida de Oliveira

*   Disciplina: Programacao Orientada a Objetos
*   Trabalho de POO1 - Camadas
*   =========================================================================================
*/
package domain;

import java.util.Comparator;

public class ComparatorPokemonBySpAtkAscending implements Comparator<Pokemon> {
    @Override
    public int compare(Pokemon o1, Pokemon o2) {
        if (o1.getSpAtk() > o2.getSpAtk()) {
            return 1;
        } else if (o1.getSpAtk() < o2.getSpAtk()) {
            return -1;
        } else {
            return 0;
        }
    }

}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package warrior;

import java.util.LinkedList;

/**
 *
 * @author 2021122760224
 */

//Undead herda de mumia
public class Undead extends Mummy {
    
    //Construtor de Undead

    /**
     *
     * @param weight peso do Morto Vivo
     * @param age idade do Morto Vivo
     * @param name nome do Morto Vivo
     */
    public Undead(int weight, int age, String name) {
        super(weight, age, name);
    }
    
    //Sobreescrita do método atacar de guerreiro, pega o primeiro do timeB e ataca em -5
    @Override
    public void atacar(LinkedList timeA, LinkedList timeB) {
        Warrior warrior = (Warrior) timeB.get(0);
        warrior.loseEnergy(5);
    }
    
}

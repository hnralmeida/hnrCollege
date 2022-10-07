/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package thefinalqueue;

import java.util.Iterator;
import java.util.LinkedList;

/**
 *
 * @author 2021122760224
 */
public class Valkyrie extends Warrior {
    int id;

    public Valkyrie(int peso, int idade, String nome) {
        super(peso, idade, nome);
    }
    
    /**
     *
     * @param energiaMaxima
     */
    
    
    @Override
    public void setEnergiaMaxima(int energiaMaxima);
    
    
    @Override
    public void atacar(LinkedList timeA, LinkedList timeB) {
        Warrior warrior = (Warrior) timeB.get(0);
        warrior.loseEnergy(20);
        Iterator it = timeB.iterator();
        if (it.hasNext()){
            Warrior warrior2= (Warrior) timeB.get(1);
            warrior2.setEnergiaAtual(warrior2.getEnergiaAtual() + 20);
        }        
    }
}

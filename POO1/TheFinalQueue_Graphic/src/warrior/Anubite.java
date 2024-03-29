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
public class Anubite extends Warrior {

    /**
     *
     * @param weight peso do Anubite
     * @param age idade do Anubite
     * @param name nome do Anubite
     */
    public Anubite(int weight, int age, String name) {
        super(weight, age, name);
        this.setIcon("data\\Anubite.png");
    }

    /**
     *
     * @param timeA LinkedList timeA
     * @param timeB LinkedList timeB
     */
    @Override
    public void atacar(LinkedList timeA, LinkedList timeB) {
        Warrior warrior = (Warrior) timeB.get(0);
        warrior.loseEnergy(15);
        warrior = (Warrior) timeB.getLast();
        warrior.loseEnergy(15);
    }
    
}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package warrior;

import java.util.Iterator;
import java.util.LinkedList;

/**
 *
 * @author 2021122760224
 */
public class Nemean_Lion extends Warrior {

    /**
     *
     * @param weight peso do Leao
     * @param age idade do Leao
     * @param name nome do Leao
     */
    public Nemean_Lion(int weight, int age, String name) {
        super(weight, age, name);
        this.setIcon("data\\Nemean_Lion.png");
    }
  
    /**
     *
     * @param timeA LinkedList timeA 
     * @param timeB LinkedList timeB
     */
    
    @Override
    public void atacar(LinkedList timeA, LinkedList timeB) {
        Iterator<Warrior> it = timeB.iterator();
        Warrior warrior = it.next();
        warrior.loseEnergy(30);
        
        if (it.hasNext()){
            warrior = it.next();
            warrior.loseEnergy(15);
            if (it.hasNext()){
                warrior = it.next();
                warrior.loseEnergy(15);           
            } 
        }       
    }
}

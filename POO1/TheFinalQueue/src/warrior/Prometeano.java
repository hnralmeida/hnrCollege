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
public class Prometeano extends Warrior {

    public Prometeano(int weight, int age, String name) {
        super(weight, age, name);
    }

    @Override
    public void dies (LinkedList<Warrior> time, LinkedList<Warrior> dead){
        if(this.getMaxEnergy()>1){
            time.addLast(new Prometeano(this.weight, this.age, this.name));
            time.getLast().setMaxEnergy(maxEnergy/2);
            time.getLast().setCurrentEnergy(this.maxEnergy);

            time.addLast(new Prometeano(this.weight, this.age, this.name));
            time.getLast().setMaxEnergy(maxEnergy/2);
            time.getLast().setCurrentEnergy(this.maxEnergy);
        }
        super.dies(time, dead);
    }
    
    @Override
    public void atacar(LinkedList timeA, LinkedList timeB) {
        Warrior warrior = (Warrior) timeB.get(0);
        warrior.loseEnergy(10);
    }
    
}

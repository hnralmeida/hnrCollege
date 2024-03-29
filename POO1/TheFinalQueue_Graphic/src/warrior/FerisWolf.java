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
public class FerisWolf extends Warrior {    
    
    /**
     *
     * @param weight peso do FerisWolf
     * @param age idade do FerisWolf
     * @param name nome do FerisWolf
     */
    public FerisWolf(int weight, int age, String name) {
        super(weight, age, name);
        this.setIcon("data\\Fenris_Wolf.png");
        this.setX(90);
        this.setY(570);
    }

    /**
     *
     * @param energiaAtual energia atual do Guerreiro
     */
    @Override
    public void setCurrentEnergy(int energiaAtual) {
        this.setCurrentEnergy(energiaAtual);
    }
    
    @Override
    public void atacar(LinkedList timeA, LinkedList timeB) {
        Warrior warrior = (Warrior) timeB.get(0);
        int qt=0;
        Iterator it = timeA.iterator();
        while (it.hasNext()){
            if (timeA.getClass().getSimpleName().equals("FehriWolf")){
                qt++;
            } else {
                break;
            }     
        }
        qt = qt*8;
        warrior.loseEnergy(40+qt);
    }
}

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

//Nemean_Lion herda de guerreiro
public class Nemean_Lion extends Warrior {

    //Construtor de Nemean_Lion

    /**
     *
     * @param weight peso do Nemean Lion
     * @param age idade do Nemean Lion
     * @param name nome do Nemean Lion
     */
    public Nemean_Lion(int weight, int age, String name) {
        super(weight, age, name);
    }
  
    /**
     *
     * @param timeA Linked list timeA
     * @param timeB Linked list timeB
     */
    
    /*Sobreescrita do método atacar de guerreiro
    Cria um iterator usando de base o timeB
    pega o primeiro guerreiro e ataca com dano de 30
    se existir um guerreiro atrás do primeiro guerreiro, ataca com 15
    e se existir um guerreiro atrás do segundo guerreiro, também ataca com 15
    (it.next pula para o próximo item da lista)
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

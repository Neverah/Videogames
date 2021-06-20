using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class lifeController : MonoBehaviour
{
    public static int currentLife;
    public static bool isDead;

    public int maxLife;
    Text text;
    private levelController level;
    
    

    void Start()
    {
        text = GetComponent<Text>();
        currentLife = maxLife;
        level = FindObjectOfType<levelController>();
        isDead = false;
    }

    void Update()
    {
        if(currentLife <= 0 && !isDead)
        {
            isDead = true;
            currentLife = 0;
            level.RespawnPlayer();
        }
        text.text = "" + currentLife;
    }

    public static void Damage(int damage)
    {
        currentLife -= damage;
    }

    public void FillLife()
    {
        currentLife = maxLife;
        isDead = false;
    }
}

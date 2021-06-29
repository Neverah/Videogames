using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class enemyLife : MonoBehaviour
{
    public int enemyLifeValue;
    public GameObject deathEffect;
    public int deathScore;

    void Start()
    {
        
    }


    void Update()
    {
        if(enemyLifeValue <= 0)
        {
            Instantiate(deathEffect, transform.position, transform.rotation);
            scoreController.AddScore(deathScore);
            Destroy(gameObject);
        }
    }

    public void Damage(int damage)
    {
        enemyLifeValue -= damage;
    }
}

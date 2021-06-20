using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class shootController : MonoBehaviour
{
    public float speed;
    public float maxRange;
    private playerController player;
    public GameObject enemyDeathParticles;
    public GameObject bulletCollisionParticles;

    public int scorePerDeath;

    public int damageValue;

    void Start()
    {
        player = FindObjectOfType<playerController>();
        if(player.transform.localScale.x < 0)
        {
            speed = -speed;
        }
    }

    void Update()
    {
        GetComponent<Rigidbody2D>().velocity = new Vector2(speed, GetComponent<Rigidbody2D>().velocity.y);
        if (Mathf.Abs(transform.position.x) > Mathf.Abs(player.transform.position.x) + maxRange)
        {
            Destroy(gameObject);
        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {    
        if(collision.tag == "enemy")
        {
            //Instantiate(enemyDeathParticles, collision.transform.position, collision.transform.rotation);
            //Destroy(collision.gameObject);
            Destroy(gameObject);
            //scoreController.AddScore(scorePerDeath);
            collision.GetComponent<enemyLife>().Damage(damageValue);
        }
            
        if(collision.gameObject.layer != 6)
        {
            Instantiate(bulletCollisionParticles, transform.position, transform.rotation);
            Destroy(gameObject);
        }
        
    }
}

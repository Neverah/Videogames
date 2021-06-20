using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class mCDamage : MonoBehaviour
{
    public int dealtDamage;

    void Start()
    {
        
    }

    void Update()
    {
        
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.name == "Main character")
        {
            lifeController.Damage(dealtDamage);
            var player = collision.GetComponent<playerController>();
            collision.GetComponent<AudioSource>().Play();
            player.bounceCount = player.bounceLength;

            if(collision.transform.position.x < transform.position.x)
            {
                player.bounceRight = true;
            }
            else
            {
                player.bounceRight = false;
            }
        }
    }
}

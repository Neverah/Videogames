using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class gemPickup : MonoBehaviour
{
    public int scoreIncrement;
    public AudioSource pickupSound;

    void Start()
    {
        
    }


    void Update()
    {
        
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.name == "Main character")
        {
            pickupSound.Play();
            scoreController.AddScore(scoreIncrement);
            Destroy(gameObject);
        }
    }
}

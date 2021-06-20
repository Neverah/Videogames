using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class mCDeath : MonoBehaviour
{
    private levelController levelFile;

    void Start()
    {
        levelFile = FindObjectOfType<levelController>();
    }

    void Update()
    {
        
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.name == "Main character")
        {
            levelFile.RespawnPlayer();
        }
    }
}

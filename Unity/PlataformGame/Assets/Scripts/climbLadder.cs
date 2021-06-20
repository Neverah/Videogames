using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class climbLadder : MonoBehaviour
{
    public bool isOnLadder;
    private playerController player;

    void Start()
    {
        player = FindObjectOfType<playerController>();
    }


    void Update()
    {
        
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.tag == "Player")
        {
            isOnLadder = true;
            Debug.Log("On the ladder");
        }else if(collision.tag == "ladderCheck")
        {
            isOnLadder = true;
            Debug.Log("Above the ladder");
        }
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        if (collision.tag == "Player")
        {
            isOnLadder = false;
            Debug.Log("On the ladder");
        }
        else if (collision.tag == "ladderCheck")
        {
            isOnLadder = false;
            Debug.Log("Above the ladder");
        }
    }
}

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
            enterAction();
            Debug.Log("On the ladder");
        }
        else if(collision.tag == "ladderCheck")
        {         
            enterAction();
            Debug.Log("Above the ladder");
        }
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        if (collision.tag == "Player")
        {
            exitAction();
            Debug.Log("On the ladder");
        }
        else if (collision.tag == "ladderCheck")
        {
            exitAction();
            Debug.Log("Above the ladder");
        }
    }

    private void enterAction()
    {
        isOnLadder = true;

        foreach (GameObject tile in player.ladderFloor)
        {
            tile.GetComponent<Collider2D>().isTrigger = true;
        }
    }

    private void exitAction()
    {
        isOnLadder = false;

        foreach (GameObject tile in player.ladderFloor)
        {
            tile.GetComponent<Collider2D>().isTrigger = false;
        }
        player.animacion.SetBool("isClimbing", false);
    }
}

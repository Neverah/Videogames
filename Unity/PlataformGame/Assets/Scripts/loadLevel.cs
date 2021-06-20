using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class loadLevel : MonoBehaviour
{
    private bool playerOnArea;
    public string levelToLoad;

    void Start()
    {
        playerOnArea = false;
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.W) && playerOnArea)
        {
            SceneManager.LoadScene(levelToLoad);
        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.name == "Main character")
        {
            playerOnArea = true;
        }
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        if (collision.name == "Main character")
        {
            playerOnArea = false;
        }
    }
}

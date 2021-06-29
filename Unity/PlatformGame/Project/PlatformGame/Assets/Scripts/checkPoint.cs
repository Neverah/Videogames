using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class checkPoint : MonoBehaviour
{
    public levelController level;

    // Start is called before the first frame update
    void Start()
    {
        level = FindObjectOfType<levelController>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.name == "Main character")
        {
            level.currentCheckPoint = gameObject;
        }
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class cameraController : MonoBehaviour
{
    public playerController player;
    public bool isFollowing;
    public float xoffset;
    public float yoffset;

    void Start()
    {
        player = FindObjectOfType<playerController>();
        if(player) isFollowing = true;
    }


    void Update()
    {
        if (isFollowing)
        {
            transform.position = new Vector3(player.transform.position.x + xoffset, player.transform.position.y + yoffset, transform.position.z);
        }
    }
}

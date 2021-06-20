using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class levelController : MonoBehaviour
{
    public GameObject currentCheckPoint;
    private playerController player;
    public GameObject deathParticles;
    public GameObject respawnParticles;
    public float respawnDelay;

    //deathPenalty
    public int penaltyScore;

    //camera
    private cameraController camara;

    //life
    public lifeController life;

    void Start()
    {
        player = FindObjectOfType<playerController>();
        camara = FindObjectOfType<cameraController>();
        life = FindObjectOfType<lifeController>();
    }

    void Update()
    {
        
    }

    public void RespawnPlayer()
    {
        Debug.Log("Death");
        StartCoroutine("RespawnPlayerCoroutine");
    }

    public IEnumerator RespawnPlayerCoroutine()
    {
        Instantiate(deathParticles, player.transform.position, player.transform.rotation);
        player.enabled = false;
        player.GetComponent<Renderer>().enabled = false;
        player.GetComponent<PolygonCollider2D>().enabled = false;
        camara.isFollowing = false;
        scoreController.AddScore(-penaltyScore);

        yield return new WaitForSeconds(respawnDelay);
        player.transform.position = currentCheckPoint.transform.position;
        Instantiate(respawnParticles, player.transform.position, player.transform.rotation);
        player.enabled = true;
        player.GetComponent<Renderer>().enabled = true;
        player.GetComponent<PolygonCollider2D>().enabled = true;
        life.FillLife();
        camara.isFollowing = true;
    }
}

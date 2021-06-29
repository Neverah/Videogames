using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class playerController : MonoBehaviour
{
    // Movement
    public float jumpHeigth = 5;
    public float speedValue = 3;

    //FloorCheck
    public Transform floorCheck;
    public float floorCheckRadio = 0.03f;
    public LayerMask floorLayer;

    private bool onFloor;
    private bool doubleJump;

    public Animator animacion;

    private float moveSpeed;

    //shooting
    public Transform shootOrigin;
    public GameObject fireBall;

    //shoot delay
    public float shootDelayValue;
    private float shootDelayCounter;

    //damage bounce
    public float bounce;
    public float bounceLength;
    public float bounceCount;
    public float bounceFactor;
    public bool bounceRight;

    //ladders
    private climbLadder[] ladderController;
    public GameObject[] ladderFloor;

    //sound
    public AudioSource audioShoot;
    public AudioSource audioJump;

    void Start()
    {
        animacion = GetComponent<Animator>();
        ladderController = FindObjectsOfType<climbLadder>();
    }

    private void FixedUpdate()
    {
        onFloor = Physics2D.OverlapCircle(floorCheck.position, floorCheckRadio, floorLayer);
    }

    void Update()
    {

        if (onFloor)
        {
            doubleJump = false;
        }
        animacion.SetBool("grounded", onFloor);

        JumpCheck();

        moveSpeed = 0f;

        if (Input.GetKey(KeyCode.D))
        {
            moveSpeed = speedValue;
        }

        if (Input.GetKey(KeyCode.A))
        {
            moveSpeed = -speedValue;
        }

        if(bounceCount <= 0)
        {
            GetComponent<Rigidbody2D>().velocity = new Vector2(moveSpeed, GetComponent<Rigidbody2D>().velocity.y);
        }
        else
        {
            if (bounceRight)
            {
                GetComponent<Rigidbody2D>().velocity = new Vector2(-bounce, bounce);
                //GetComponent<Rigidbody2D>().AddForce(new Vector2(-bounce * bounceFactor, bounce * bounceFactor), ForceMode2D.Impulse);
            }
            else
            {
                GetComponent<Rigidbody2D>().velocity = new Vector2(bounce, bounce);
                //GetComponent<Rigidbody2D>().AddForce(new Vector2(bounce * bounceFactor, bounce * bounceFactor), ForceMode2D.Impulse);
            }
        }
        bounceCount -= Time.deltaTime;

        //fireballs

        if (Input.GetKeyDown(KeyCode.Mouse0))
        {
            Instantiate(fireBall, shootOrigin.position, shootOrigin.rotation);
            audioShoot.Play();
            shootDelayCounter = shootDelayValue;
        }
        if (Input.GetKey(KeyCode.Mouse0))
        {
            shootDelayCounter -= Time.deltaTime;
            if(shootDelayCounter <= 0)
            {
                shootDelayCounter = shootDelayValue;
                Instantiate(fireBall, shootOrigin.position, shootOrigin.rotation);
                audioShoot.Play();
            }
        }

        //ladders
        foreach (climbLadder ladder in ladderController)
        {
            if (ladder.isOnLadder)
            {
                if (Input.GetKey(KeyCode.W))
                {
                    GetComponent<Rigidbody2D>().velocity = new Vector2(GetComponent<Rigidbody2D>().velocity.x, speedValue);
                    animacion.SetBool("isClimbing", true);
                    animacion.SetBool("grounded", true);
                }
            
                if (Input.GetKey(KeyCode.S))
                {
                    GetComponent<Rigidbody2D>().velocity = new Vector2(GetComponent<Rigidbody2D>().velocity.x, -speedValue);
                    animacion.SetBool("isClimbing", true);
                    animacion.SetBool("grounded", true);
                }
            }
        }

        GetComponent<Rigidbody2D>().velocity = new Vector2(moveSpeed, GetComponent<Rigidbody2D>().velocity.y);

        animacion.SetFloat("speed", Mathf.Abs(GetComponent<Rigidbody2D>().velocity.x));
        //Debug.Log(Mathf.Abs(GetComponent<Rigidbody2D>().velocity.x));
        if(GetComponent<Rigidbody2D>().velocity.x > 0)
        {
            transform.localScale = new Vector3(1f, 1f, 1f);
        }
        else if (GetComponent<Rigidbody2D>().velocity.x < 0)
        {
            transform.localScale = new Vector3(-1f, 1f, 1f);
        }
    }

    private void JumpCheck()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            if (onFloor)
            {
                JumpAction();
            }
            else if(!doubleJump)
            {
                JumpAction();
                doubleJump = true;
            }           
        }     
    }

    private void JumpAction()
    {
        audioJump.Play();
        GetComponent<Rigidbody2D>().velocity = new Vector2(GetComponent<Rigidbody2D>().velocity.x, jumpHeigth);
    }
}

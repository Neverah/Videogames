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

    private Animator animacion;

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
    private climbLadder ladderController;
    public GameObject[] ladderFloor;

    //sound
    public AudioSource audioShoot;
    public AudioSource audioJump;

    void Start()
    {
        animacion = GetComponent<Animator>();
        ladderController = FindObjectOfType<climbLadder>();
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
            //GetComponent<Rigidbody2D>().velocity = new Vector2(movSpeed, GetComponent<Rigidbody2D>().velocity.y);
            moveSpeed = speedValue;
        }

        if (Input.GetKey(KeyCode.A))
        {
            //GetComponent<Rigidbody2D>().velocity = new Vector2(-speedValue, GetComponent<Rigidbody2D>().velocity.y);
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
        if (ladderController.isOnLadder)
        {
            if (Input.GetKey(KeyCode.W))
            {
                foreach(GameObject tile in ladderFloor){
                    tile.GetComponent<Collider2D>().isTrigger = true;
                }
                GetComponent<Rigidbody2D>().velocity = new Vector2(GetComponent<Rigidbody2D>().velocity.x, speedValue);
                animacion.SetBool("isClimbing", true);
                animacion.SetBool("grounded", true);
            }
        }

        if (ladderController.isOnLadder)
        {
            if (Input.GetKey(KeyCode.S))
            {
                foreach (GameObject tile in ladderFloor)
                {
                    tile.GetComponent<Collider2D>().isTrigger = true;
                }
                GetComponent<Rigidbody2D>().velocity = new Vector2(GetComponent<Rigidbody2D>().velocity.x, -speedValue);
                animacion.SetBool("isClimbing", true);
                animacion.SetBool("grounded", true);
            }
        }

        if (!ladderController.isOnLadder)
        {
            animacion.SetBool("isClimbing", false);
            foreach (GameObject tile in ladderFloor)
            {
                tile.GetComponent<Collider2D>().isTrigger = false;
            }
        }

        GetComponent<Rigidbody2D>().velocity = new Vector2(moveSpeed, GetComponent<Rigidbody2D>().velocity.y);

        animacion.SetFloat("speed", Mathf.Abs(GetComponent<Rigidbody2D>().velocity.x));
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

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class scoreController : MonoBehaviour
{
    public static int score;
    Text text;

    void Start()
    {
        text = GetComponent<Text>();
        score = 0;
    }

    void Update()
    {
        if(score < 0)
        {
            Reset();
        }
        else
        {
            text.text = "" + score;
        }
    }

    public static void AddScore(int scoreIncrement)
    {
        score += scoreIncrement;
    }

    public static void Reset()
    {
        score = 0;
    }
}

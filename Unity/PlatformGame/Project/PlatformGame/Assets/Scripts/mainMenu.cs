using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class mainMenu : MonoBehaviour
{
    public string startLevel;

    public void NewGame()
    {
        SceneManager.LoadScene(startLevel);
    }

    public void ExitGame()
    {
        Application.Quit();
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class endScreen : MonoBehaviour
{
    public string mainMenu;

    public void ReturnToMenu()
    {
        SceneManager.LoadScene(mainMenu);
    }

    public void ExitGame()
    {
        Application.Quit();
    }
}

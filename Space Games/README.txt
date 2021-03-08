En caso de que quieras compilar el proyecto tú mismo en Visual Studio, es posible que se produzca un fallo y no se encuentre la función PlaySound() de
la bibliotca MMsystem, ya que es una biblioteca propia de Windows, pero que no se vincula automáticamente al proyecto.

Si ocurre este fallo, tan solo habría que ir a las propiedades del proyecto -> vinculador -> entrada -> dependencias adicionales y escribir
";winmm.lib" en el campo de texto superior para que la biblioteca se vincule al proyecto y ya debería compilarse perfectamente.

Para cualquier otro problema relacionado, pregúntame.
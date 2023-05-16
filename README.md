# Cómo crear un proyecto para la ESP32 de los Drone TT

## Requisitos
1. Tener instalado vscode.
2. Tener cargada la extensión de c/C++ en vscode.
3. Tener instalado el compilador de c/C++, [c/C++ for Visual Studio Code.](https://code.visualstudio.com/docs/languages/cpp) 
4. Instalar la extensión de [PlatformIO](https://platformio.org/install/ide?install=vscode) en vscode.
5. Ir a `C:\Users\user_name\.platformio\platforms\espressif32\` renombrar el archivo *esp32dev.json* por *esp32dev_old.json*.
6. Cortar y pegar el archivo *esp32dev.json* de este repositorio en la carpeta `C:\Users\user_name\.platformio\platforms\espressif32\`.
7. Agregar el include de la biblioteca del drone tt en `.vscode/c_cpp_properties.json`, la library está en `/lib/RMTT_Libs`.
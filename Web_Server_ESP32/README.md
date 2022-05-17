# Web Server ESP32
Esse projeto mostra como acender um LED e ligar um Buzzer com um Web Server no esp32, acessando pelo IP do controlador em qualquer Browser, sendo pelo celular ou computador. Lembrando que para acessar esse Web Server o dispositivo deve estar na mesma rede.

## Estrutura
A pasta desse projeto está estruturada da seguinte forma:

- `src/main.cpp` Código principal
- `.gitignore` Arquivo para ignorar pastas desnecessárias.
- `platformio.ini` Arquivo de configuração para fazer upload do código

## Código
No código disponível em `src/main.cpp`, você deve alterar o ID e o PassWord da rede, colocando o seu ID e a sua senha do Wifi.

```C++
//Exemplo
const char* ssid = "YourID";
const char* password = "YourPassWord";
```

## Circuito
para fazer a montagem do circuito utilizamos:
- `1 ESP32`
- `1 LED`
- `1 Resistor de 220 Ohm`
- `1 Buzzer de 5V a 12V`
- `1 Protoboard`
- `1 Cabo para carregar o código`

No código o LED está conectado a porta digital `12` e o Buzzer a porta digital `26`.

![ESP32](https://user-images.githubusercontent.com/91765985/168718351-f8df5f0b-51a7-4bc6-b97e-79bc9e3c10f1.jpg)



## Utilização
Após compilar o código no ESP32, abra o Monitor Serial no Visual Studeo Code com o PlatformIO. O ESP32 irá retornar seu IP Address, copie esse IP e cole no seu Navegador de preferência.

No Monitor Serial terá um print assim:
```c++
Connecting to YourID
.....
WiFi connected.
IP address:    
192.168.1.78 // Seu IP pode ser diferente
```
Copie e cole esse IP no navegador e abrirá uma página como essa:
![WebServer](https://user-images.githubusercontent.com/91765985/168717141-5688de0b-ffb5-48f6-a574-6e67c03d19db.png)

## Conclusão
Bom agora é só se divertir e fazer qualquer alteração que desejar, lembrando que o site pode ser totalmente modificado em `src/main.cpp` nas linhas `60` a `74`.
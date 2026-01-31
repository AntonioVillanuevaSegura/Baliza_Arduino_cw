# Baliza_Arduino_cw
Modificacion del programa de EA7HG  por F4LEC , para simulacion ,

Posibilidad de cambiar WPM 
Cambio de mensaje linea 16 String mensaje = "";  //Mensaje a enviar por la baliza
Debug RS232

( entre comentarios esta el codigo para modo real , no simulacion ,  no probado )

Link a la simulacion con el codigo C++ modificado 
https://wokwi.com/projects/454496346094658561
![Render BalizaCw](https://github.com/AntonioVillanuevaSegura/Baliza_Arduino_cw/blob/main/DOC/balizaCOLOR.png)
![Render BalizaCw](https://github.com/AntonioVillanuevaSegura/Baliza_Arduino_cw/blob/main/DOC/tarjeta.png)

La tarjeta PCB tiene un diodo de proteccion de polaridad a la entrada
He previsto la PCB con 3 salidas adicionales con LED ,pero la base sigue siendo la misma 

La CPU es una Arduino nano , resistencia de 1/4 de W ....

Hay una carpeta GERBER con un fichero comprimido baliza.zip que es 
compatible con el formato de https://jlcpcb.com por ejemplo 

El tipo de rele que voy a utilizar 
PC, JQC-3F(T73), DC5V Bobine, SPDT, 7A 240VAC Bornes 5 broches
https://www.amazon.fr/dp/B074599SN8?ref=ppx_yo2ov_dt_b_fed_asin_title

Los conectores
5mm PCB Vis Connecteur, Bornier à Souder Vert, 2
https://www.amazon.fr/dp/B0DSBSXL47?ref=ppx_yo2ov_dt_b_fed_asin_title

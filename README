// Copyright Tudor Robert-Fabian 312CAa 2023-2024

#image_editor.c

##Explicație cod
La început am definit o structură numită "image" alcătuită din 8 componente: 
o variabilă de tip "char" ce reprezintă tipul de imagine pe care îl am stocat
("magic_word"), un pointer către o matrice("matrix") și 6 variabile de tip 
"int" ce reprezintă lățimea imaginii("width"), înălțimea imaginii("height") și 
cele 4 coordonate primite în urma comenzii "SELECT"("x1", "y1", "x2", "y2"). 
Am folosit această structură pentru implementarea diverselor comenzi din cadrul
cerinței. De asemenea, am definit o variabilă "MAX" cu valoarea 256.

###delete_photo
Funcția primește ca parametru un pointer la o structură de tip "image" și 
eliberează memoria alocată dinamic pentru o imagine folosind 2 variabile de tip
"int"(" photo->width" și " photo->height").

###load
Funcția primește ca parametri un pointer la o structură de tip "image" și o
variabilă de tip "char" ce reprezintă numele fișierului din care încărcăm 
datele pozei.
-la început se șterge matricea veche folosind funcția "delete_photo"
-se citesc apoi datele despre imagine("width", "height", "magic_word"), alocăm
dinamic o nouă matrice cu dimensiunile de care avem nevoie, ca mai apoi să 
împărțim funcția pe 4 cazuri:
   ->dacă "photo->magic_word" = "P2", citim cu "fscanf" "width x height" valori
     în matricea "matrix" deoarece poza e grayscale și citim dintr-un fișier cu
     caractere ascii
   ->dacă "photo->magic_word" = "P3", citim cu "fscanf" "3 x width x height" 
     valori în matricea "matrix" deoarece poza e rgb și citim dintr-un fișier cu
     caractere ascii
   ->dacă "photo->magic_word" = "P5", citim cu "fread" "width x height" valori
     în matricea "matrix" deoarece poza e grayscale și citim dintr-un fișier 
     binar
   ->dacă "photo->magic_word" = "P6", citim cu "fread" "3 x width x height" 
     valori în matricea "matrix" deoarece poza e rgb și citim dintr-un fișier 
     binar
-la final inițializăm coordonatele "x1", "y1", "x2", "y2" cu "-1" pentru a 
evita cazurile de excepție

###save
Funcția primește ca parametri un pointer la o structură de tip "image", o
variabilă de tip "char" ce reprezintă numele fișierului în care încărcăm 
datele pozei și o altă variabilă de tip "char"("type") ce reprezintă tipul 
fișierului în care încărcăm datele(ascii/binar).
-dacă "photo->magic_word" = "P3/P6" și "type=ascii", scriem cu "fprintf" "3 x 
width x height" valori în fișierul "file_name" deoarece poza e rgb și 
fișierul în care punem e ascii
-dacă "photo->magic_word" = "P3/P6" și "type=binary", scriem cu "fwrite" "3 x 
width x height" valori în fișierul "file_name" deoarece poza e rgb și 
fișierul în care punem e binar
-dacă "photo->magic_word" = "P2/P4" și "type=ascii", scriem cu "fprintf"
"width x height" valori în fișierul "file_name" deoarece poza e grayscale și 
fișierul în care punem e ascii
-dacă "photo->magic_word" = "P2/P4" și "type=binary", scriem cu "fwrite"
"width x height" valori în fișierul "file_name" deoarece poza e grayscale și 
fișierul în care punem e binar
-la final afișăm mesajul corespunzător faptului că operația a avut loc cu
succes

###select_all
Funcția primește ca parametru un pointer la o structură de tip "image",
verifică dacă e o matrice incărcată în memorie și dacă da, plasează cele 4 
coordonate x1, y1, x2, y2 în colțurile matricei și afișează mesajul că operația
a avut loc cu succes. 

###select_pixels
Funcția primește ca parametri un pointer la o structură de tip "image" și 4 
variabile de tip "int" reprezentând 4 coordonate.
-dacă coordonatele nu sunt în ordine crescătoare, acestea se interschimbă
-verificăm dacă e o poză încărcată în memorie, dacă coordonatele nu depășesc 
marginile imaginii, iar dacă aceste condiții sunt îndeplinite, setăm variabilele 
din structură pe baza acestor coordonate(împărțind pe 2 cazuri: dacă poza e sau
nu rgb) 

###crop
Funcția primește ca parametru un pointer la o structură de tip "image", 
verifică dacă avem o poză încărcată în memorie și dacă da, alocă dinamic o nouă
matrice cu dimensiunile selecției, copiază valorile dintre coordonatele 
selecției din matricea originală, apoi dezalocă memoria pentru cea veche, 
setează pointerul "matrix" către noua matrice și setează coordonatele x1, x2, y1,
y2 din structură în colțurile noii matrici.

###sharpen
Funcția primește ca parametru un pointer la o structură de tip "image", alocă 
dinamic o matrice nouă cu dimensiunile celei vechi, copiază valorile matricei
vechi în cea nouă, aplică kernel-ul sharpen de imagine pe selecția curentă din
matricea veche folosind valorile din matricea nouă și folosește funcția "clamp"
pe valorile obținute din matricea veche. La final, dezalocă matricea nouă și 
afișează un mesaj corespunzător dacă operația s-a finalizat cu succes.

###edge
Funcția primește ca parametru un pointer la o structură de tip "image", alocă 
dinamic o matrice nouă cu dimensiunile celei vechi, copiază valorile matricei
vechi în cea nouă, aplică kernel-ul edge de imagine pe selecția curentă din
matricea veche folosind valorile din matricea nouă și folosește funcția "clamp"
pe valorile obținute din matricea veche. La final, dezalocă matricea nouă și 
afișează un mesaj corespunzător dacă operația s-a finalizat cu succes.

###blur
Funcția primește ca parametru un pointer la o structură de tip "image", alocă 
dinamic o matrice nouă cu dimensiunile celei vechi, copiază valorile matricei
vechi în cea nouă, aplică kernel-ul blur de imagine pe selecția curentă din
matricea veche folosind valorile din matricea nouă și folosește funcția "clamp"
pe valorile obținute din matricea veche. La final, dezalocă matricea nouă și 
afișează un mesaj corespunzător dacă operația s-a finalizat cu succes.

###gaussian_blur
Funcția primește ca parametru un pointer la o structură de tip "image", alocă 
dinamic o matrice nouă cu dimensiunile celei vechi, copiază valorile matricei
vechi în cea nouă, aplică kernel-ul gaussian_blur de imagine pe selecția curentă 
din matricea veche folosind valorile din matricea nouă și folosește funcția 
"clamp" pe valorile obținute din matricea veche. La final, dezalocă matricea 
nouă și afișează un mesaj corespunzător dacă operația s-a finalizat cu succes.

###histogram
Funcția primește ca parametri un pointer la o structură de tip "image" și două
valori de tip "int" ce reprezintă  numărul de steluțe și de binuri cu care 
trebuie să afișăm histograma.
-la început alocăm dinamic 2 vectori, unul de frecvență pentru a stoca 
frecvența fiecărui pixel("frecventa") și unul pentru a stoca bin-urile
("bins")
-inițializăm tot vectorul de frecvență cu 0, după care calculăm frecvența
efectivă a fiecărui pixel prin intermediul a două structuri repetitive de
tip "for"
-calculăm apoi variabila "area" ce reprezintă numărul de intensități a 
fiecărui pixel din fiecare interval prin impărțirea numărului total de
intensități ("MAX") la numărul de intervale("y")
-calculăm bin-urile histogramei prin împărțirea intervalului de 
intensități în "y" părți egale(suma frecvențelor din fiecare parte este
stocată în vectorul "bins")
-apoi dacă valorea unui bin sare de valoarea maximă(255) îl egalăm cu valoarea
maximă adică 255
-la final afișăm histograma cum ni s-a cerut în cerință și dealocăm cei 2 
vectori

###clamp
Funcția primește ca parametru o variabilă de tip "int" și returnează 255 dacă
valoarea sare de 255, 0 dacă valoarea e negativă sau valoare rămâne neschimbată 
dacă se află în interval.

###equalize
Funcția primește ca parametru un pointer la o structură de tip "image" și 
egalizează o imagine grayscale.
-la început alocăm dinamic 2 vectori("frecventa", "sumafrecventa"), iar pe 
primul îl inițializăm cu 0
-calculăm apoi frecvența fiecărui pixel și valorile vectorului "sumafrecventa"
ce reprezintă suma elementelor de la 0 la i din vectorul "frecventa"
-ne folosiv apoi de formula dată în temă pentru a calcula noua valoare a 
fiecărui pixel folosind funcțiile "clamp" și "round"
-la final dezalocăm cei 2 vectori

###rotate_90_photo & rotate_90_photo2
Funcția primește ca parametru un pointer la o structură de tip "image" și face 
rotație unei imagini cu 90 de grade spre dreapta.
-inițial verificăm dacă avem o poză în memorie, apoi impărțim problema pe 2 
cazuri:
1.Poza este rgb
-alocăm inițial 3 matrici de dimensiuni "witdh x height" în care punem pixelii
pe culori(în "matrix_r" punem pixelii cu roșu, în "matrix_g" punem pixelii cu 
verde și în "matrix_b" punem pixelii cu albastru) din matricea veche, după care
o dezalocăm folosind funcția "delete_photo"
-alocăm apoi o nouă matrice cu dimesiunile matricei vechi dar inversate în care 
punem valorile celor 3 matrici rotite cu 90 de grade la dreapta 
-la final dezalocăm cele 3 matrici și actualizăm dimensiunile matricei și 
selecției curente
2.Poza este grayscale
-alocăm o nouă matrice cu dimesiunile matricei vechi dar inversate în care 
punem valorile matricei vechi
-în matricea veche punem valorile matricei noi rotit cu 90 de grade la dreapta
-la final dezalocăm matricea nouă și actualizăm dimensiunile matricei și 
selecției curente

###rotate_90_right & rotate_90_right2
Funcția primește ca parametru un pointer la o structură de tip "image" și face 
rotație unei imagini cu 90 de grade spre dreapta.
-inițial verificăm dacă avem o poză în memorie, apoi impărțim problema pe 2 
cazuri:
1.Poza este rgb
-alocăm inițial 3 matrici de dimensiuni "witdh x height" în care punem pixelii
pe culori(în "matrix_r" punem pixelii cu roșu, în "matrix_g" punem pixelii cu 
verde și în "matrix_b" punem pixelii cu albastru) din matricea veche, după care
o dezalocăm folosind funcția "delete_photo"
-punem valorile celor 3 matrici rotite cu 90 de grade la dreapta în matricea 
veche doar pe pozițiile care se află în interiorul selecției curente
-la final dezalocăm cele 3 matrici și actualizăm dimensiunile matricei vechi și 
selecției curente
2.Poza este grayscale
-alocăm o nouă matrice cu dimesiunile matricei vechi dar inversate în care 
punem valorile matricei vechi
-în matricea veche punem valorile matricei noi rotit cu 90 de grade la dreapta
doar pe pozițiile care se află în interiorul selecției curente
-la final dezalocăm matricea nouă și actualizăm dimensiunile matricei vechi și 
selecției curente

###file_exists
Funcția primește ca parametru o variabilă ce reprezintă numele unui fișier
("file_name") și retunează 1 dacă fișierul există și 0 dacă el nu există.

###empty_file
Funcția primește ca parametru un pointer la o structură de tip "image" și 
dezalocă matricea în care e stocată poza curentă și egalează dimensiunile 
ei cu 0.

###is_number
Funcția primește ca parametru un șir de caractere, elimină "+" sau "-" din
față dacă e cazul și verifică dacă în continuare e un număr.

###is_power_of_two
Funcția primește ca parametru un număr și returnează 1 dac numărul este 
putere a lui 2 și 0 dacă nu este putere a lui 2.

###choose_load 
Funcția primește ca parametru un pointer la o structură de tip "image" și
o variabilă de tip "char" "file_name" și verifică dacă există fișierul cu
numele "file_name" și dacă da apelăm funcția "load", dacă nu afișăm un mesaj 
corespunzător.

###choose_save
Funcția primește ca parametru un pointer la o structură de tip "image" și
2 variabile de tip "char" "file_name" și "type". Dacă type=NULL înseamnă
că salvăm într-un fișier în mod binar. Dacă nu avem o matrice încărcată
afișăm un mesaj corespunzător și dacă avem apelăm funcția "save".

###choose_select
Funcția primește ca parametru un pointer la o structură de tip "image" și 
5 variabile de tip "int". Funcția verifică dacă condițiile sunt îndeplinite
și daca da apelează funcția "select_pixels", dacă nu afișează un mesaj de 
eroare în funcție de problema întâmpinată.

###choose_crop
Funcția primește ca parametru un pointer la o structură de tip "image" și 
verifică dacă avem o matrice încărcată în memorie. Dacă această condiție e
îndeplinită și selecția este cea de după "load", nu facem nimic, în caz contrar
apelăm funcția "crop".

###choose_apply
Funcția primește ca parametru un pointer la o structură de tip "image" și o 
variabilă de tip "char" "parameter" ce reprezintă tipul de filtru pe care vrem 
să îl aplicăm. Dacă "parameter" e NULL și nu avem o matrice încărcată afișăm 
"No image loaded", în caz contrat afișăm "Invalid command". Dacă imaginea e 
grayscale afișăm "Easy, Charlie Chaplin". Apoi verificăm cu ce filtru este 
egală variabila "parameter", apoi dacă nu a avut loc o nouă selecție de la
"load" până la acel moment selectăm toată poza și aplicăm funcția dictată de
variabila "parameter". Dacă totuși "parameter" nu e un nume de filtru valid, 
afișăm "APPLY parameter invalid".

###choose_histogram
Funcția primește ca parametru un pointer la o structură de tip "image", o 
variabilă de tip "char" "word" și 3 variabile de tip "int" "ok", "x", "y".
Dacă nu s-a făcut o selecție nouă de ultimul "load" selectăm toată poza. Dacă
"word" e nenul atunci ok=0. Dacă ok=0 și nu avem o matrice încărcată în memorie
afișăm mesajul "No image loaded" altfel afișăm "Invalid command". Apoi dacă 
ok=1, avem o matrice încărcată în memorie, y se află în intervalul [2,MAX], y e
putere a lui 2 și "magic_word" nu e P3/P6 apelăm funcția "histogram", în caz 
contrar afișăm mesaje de eroare corespunzătoare conform cerinței.

###choose_equalize
Funcția primește ca parametru un pointer la o structură de tip "image", 
verifică dacă avem o poză încărcată în memorie, dacă "magic_word" nu e 
P3/P6, iar dacă aceste condiții sunt îndeplinite apelăm funcția "equalize"
și afișăm un mesaj de succes, în caz contrar afișăm mesajele de eroare 
corespunzătoare conform cerinței.

###choose_rotate & choose_rotate2
Funcția primește ca parametri un pointer la o structură de tip "image" și o
variabilă de tip "char" "word" și alege cazul specific fiecărui test de 
"rotate". 
-la început declarăm două variabile noi ce ne vor ajuta în alegerea cazului
specific testului actual("int ok=1", "char degree[5]")
-verificăm apoi dacă avem o matrice încărcată în memorie, dacă "word!=NULL"
și dacă unghiul citit în variabila "degree" e unul valid și dacă vreuna dintre
condiții nu e îndeplinită variabila "ok" devine 0 și afișăm un mesaj 
caracteristic
-dacă "ok=1" și nu s-a făcut o nouă selecție dupa "load" selectăm toată poza
-apoi alegem cazul cu unghiul citit în variabila "degree" și dacă e selectată 
toată matricea apelăm funcția "rotate_90_photo", altfel apelezi 
"rotate_90_right" și în ambele situații afișezi un mesaj de succes

###choose_exit
Funcția primește ca parametru un pointer la o structură de tip "image", 
verifică dacă avem o matrice încărcată în memorie și dacă avem apelăm 
funcția "delete_photo" altfel apelăm funcția "delete_photo" și afișăm 
un mesaj corespunzător "No image loaded".

###choose_invalid
Funcția primește ca parametru o variabilă de tip "char" "command" și 
verifică dacă comanda e validă și dacă nu afișează "Invalid command".

###main
-la început, declarăm câteva valori ce ne vor ajuta în rezolvarea cerințelor:
"int ok = 1", "char command_buffer[100]", "image photo".
-apoi în interiorul unei structuri repetitive de tip "while" parsăm valorile
din "command_buffer" în variabila "command"
-întâi, prima valoare a lui "command" reprezintă fie o comandă din cele 
enunțate în cerință, fie o comandă invalidă 
-apoi dacă comandă este validă intrăm pe cazul corespunzător acesteia
-în interiorul fiecărui caz parsez restul de cuvinte/numere din comanda 
respectivă și le folosesc ca parametri în apelarea funcțiilor care tratează
diverse comenzi(cele cu "choose" în fața numelui de regulă)
-de asemenea, îmi declar noi variabile de care am nevoie în tratarea unui caz
anume și le folosesc mai târziu în rezolvare în funcții

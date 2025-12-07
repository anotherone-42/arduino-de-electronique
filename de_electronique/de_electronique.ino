// Final version of 29/06/2020

// Declaration of pins associated with the button and the green and red LEDs
int bouton = 8;
int ledv = 11;
int ledr = 12;

int dureeCli = 75; // Display time between the lighting of two segments

/*
        ___A___
       |       |
      F|       |B
       |___G___|
       |       |
      E|       |C
       |       |
        ___D___
                  ° DP
Diagram representing the segments of the 1106BW display


Declaration of the digital pins used for the segments A, B, C, D, E, F, G, DP.
*/
int PinSeg[8] = {7, 6, 4, 2, 3, 9, 10, 5};
//             A B C D E F  G DP

// Example: PinSeg[2] = 4 means "segment C is controlled by pin 4 of the Arduino Uno"


/*
Declaration of the pin states to be lit depending on the digit indicated in the table name (chfr0 describes the pin states to display 0)
Each pin state corresponds to a segment (in order a, b, c... the dp segment is not handled)
The segment states are "inverted", so LOW corresponds to the segment being lit. Reference of the 7-segment display: 1106BW
It is a common anode display
*/
boolean chfr0[7] = {LOW,LOW,LOW,LOW,LOW,LOW,HIGH};
boolean chfr1[7] = {HIGH,LOW,LOW,HIGH,HIGH,HIGH,HIGH};
boolean chfr2[7] = {LOW,LOW,HIGH,LOW,LOW,HIGH,LOW};
boolean chfr3[7] = {LOW,LOW,LOW,LOW,HIGH,HIGH,LOW};
boolean chfr4[7] = {HIGH,LOW,LOW,HIGH,HIGH,LOW,LOW};
boolean chfr5[7] = {LOW,HIGH,LOW,LOW,HIGH,LOW,LOW};
boolean chfr6[7] = {LOW,HIGH,LOW,LOW,LOW,LOW,LOW};
boolean chfr7[7] = {LOW,LOW,LOW,HIGH,HIGH,HIGH,HIGH};
boolean chfr8[7] = {LOW,LOW,LOW,LOW,LOW,LOW,LOW};
boolean chfr9[7] = {LOW,LOW,LOW,LOW,HIGH,LOW,LOW};


void setup(){

  int variable = analogRead(0);
  randomSeed(variable); // Initialize the random sequence

  for (int i = 0; i <= 7; i++) // or i = i + 1 
      {     
          pinMode(PinSeg[i], OUTPUT);
          digitalWrite(PinSeg[i], HIGH); // Turn off the segments => segments are "inverted" => common anode
      }
        pinMode(ledv, OUTPUT);
        pinMode(ledr, OUTPUT);
        pinMode(bouton, INPUT);
        digitalWrite(ledv, HIGH);
        // Declaration of LEDs, button, and turn on the LED
}


void loop() {
if (digitalRead(bouton) == HIGH){

  digitalWrite(ledv, LOW);
  digitalWrite(ledr, HIGH);
  // If the button is pressed, turn off the green LED and turn on the red one

  int nbAlea = random(1, 7); // Generate a random number from 1 to 6

  traitement_1_et2_a();
  traitement_3_et4_a(nbAlea); // Call the function to display the die value (from 1 to 6)

  for(int i = 1; i <= 10; ++i){
    digitalWrite(ledr, HIGH);
    digitalWrite(ledv, LOW); 
    delay(500/i); // Blinking faster and faster
    digitalWrite(ledr, LOW);
    digitalWrite(ledv, HIGH);
    delay(500/i);
  }

  eteindreBloc(); // Turn off the displayed digit
  }
}

void traitement_3_et4_a(int chiffre_a_afficher){
    int IndSegAlea;
    boolean SegInutile = false;
    boolean IndiceSegAllum[7] = {false,false,false,false,false,false,false};

    int NombreSegChiffre = 0;
    for (int i = 0; i <= 6; i++){
      SegInutile = segIPChiffre(chiffre_a_afficher, i);

       if (SegInutile != true){
            NombreSegChiffre = NombreSegChiffre + 1;        
       }
    }   

    for(int i = 0; i < 6000 / dureeCli; ++i){
              do {
                IndSegAlea = random(0, 7); 
             }while (IndiceSegAllum[IndSegAlea] == true);

              digitalWrite(PinSeg[IndSegAlea], LOW); 
              delay(dureeCli);

              SegInutile = segIPChiffre(chiffre_a_afficher, IndSegAlea);
              if (SegInutile){   // segment is not part of the digit to be displayed
                    digitalWrite(PinSeg[IndSegAlea], HIGH);
              }
              else{
                IndiceSegAllum[IndSegAlea] = true; 
                NombreSegChiffre = NombreSegChiffre - 1;
                if (NombreSegChiffre <= 0){
                  break;
                }
              }
    }
}


boolean segIPChiffre(int chiffre, int indice_seg){
  // This function must indicate whether the segment is used to display the indicated digit

  boolean inutile = false;
  if (chiffre == 0 && chfr0[indice_seg] == HIGH){
    inutile = true;    
    }
  if (chiffre == 1 && chfr1[indice_seg] == HIGH){
    inutile = true; 
    }   
  if (chiffre == 2 && chfr2[indice_seg] == HIGH){
     inutile = true; 
    }
  if (chiffre == 3 && chfr3[indice_seg] == HIGH){
    inutile = true; 
    }
  if (chiffre == 4 && chfr4[indice_seg] == HIGH){
    inutile = true; 
    }
  if (chiffre == 5 && chfr5[indice_seg] == HIGH){
    inutile = true; 
    }
  if (chiffre == 6 && chfr6[indice_seg] == HIGH){
    inutile = true; 
    }
  if (chiffre == 7 && chfr7[indice_seg] == HIGH){
    inutile = true; 
    }
  if (chiffre == 8 && chfr8[indice_seg] == HIGH){
    inutile = true; 
    }
  if (chiffre >= 9 && chfr9[indice_seg] == HIGH){
    inutile = true; 
  }
  return inutile;
}

void traitement_1_et2_a (){
      int IndSegAlea;

      for(int i = 0; i < 2500 / dureeCli; ++i){ // Convert total duration (2500ms) into number of loops

              IndSegAlea = random(0, 7); // Select segment to light (1 to 7, excluding the decimal point (DP))
              digitalWrite(PinSeg[IndSegAlea], LOW); // Turn on
              delay(dureeCli); // Wait    
              digitalWrite(PinSeg[IndSegAlea], HIGH); // Turn off
      }    
}

void eteindreBloc (){ 
  for (int i = 0; i <= 7; ++i){ // Keep from 1 to 7 in case we want to add the decimal point (DP) later
    digitalWrite(PinSeg[i], HIGH); // Set segments back to HIGH to turn them off  
  }
}

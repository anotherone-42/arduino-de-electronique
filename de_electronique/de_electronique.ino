//Version finale du 29/06/2020

//déclaration des pins associés aux bouton et aux led verte et rouge
int bouton=8;
int ledv=11;
int ledr=12;

int dureeCli=75; //temps d'affichage entre l'allumage de deux segments

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
Schéma représentant les segments de l'affichage 1106BW


Declaration des pins digitaux utilisés pour les segments A,B,C,D,E,F,G,DP.
*/
int PinSeg[8]={7,6,4,2,3,9,10,5};
//             A B C D E F  G DP

//Exemple, PinSeg[2]=4 veut dire "le segment C est piloté par le pin 4 de l'arduino Uno"


/*
Déclaration de l'etat des pin à allumer en fonction du chiffre indiqué dans le nom du tab (chfr0 décrit l'etat des pins pour afficher 0)
Chaque état d'un pin correspond à un segment (dans l'ordre a,b,c...le seg dp n'est pas traité)
Les états des segments est "inversé" donc LOW correspond au segment allumé. Refférence de l'afficheur 8 segments: 1106BW
C'est un afficheur de type anode commune
*/
boolean chfr0[7]={LOW,LOW,LOW,LOW,LOW,LOW,HIGH};
boolean chfr1[7]={HIGH,LOW,LOW,HIGH,HIGH,HIGH,HIGH};
boolean chfr2[7]={LOW,LOW,HIGH,LOW,LOW,HIGH,LOW};
boolean chfr3[7]={LOW,LOW,LOW,LOW,HIGH,HIGH,LOW};
boolean chfr4[7]={HIGH,LOW,LOW,HIGH,HIGH,LOW,LOW};
boolean chfr5[7]={LOW,HIGH,LOW,LOW,HIGH,LOW,LOW};
boolean chfr6[7]={LOW,HIGH,LOW,LOW,LOW,LOW,LOW};
boolean chfr7[7]={LOW,LOW,LOW,HIGH,HIGH,HIGH,HIGH};
boolean chfr8[7]={LOW,LOW,LOW,LOW,LOW,LOW,LOW};
boolean chfr9[7]={LOW,LOW,LOW,LOW,HIGH,LOW,LOW};


void setup(){
  
  int variable=analogRead(0);
  randomSeed(variable);//initialise la séquence aléatoire
  
  for (int i=0;i<=7;i++)//ou i=i+1 
      {     
          pinMode(PinSeg[i],OUTPUT);
          digitalWrite(PinSeg[i], HIGH); //les éteints  => les segments sont "inversés" => anode commune
      }
        pinMode(ledv,OUTPUT);
        pinMode(ledr,OUTPUT);
        pinMode(bouton,INPUT);
        digitalWrite(ledv,HIGH);
        //déclaration des leds,bouton, et allume la led
}


void loop() {
if (digitalRead(bouton)==HIGH){
  
  digitalWrite(ledv,LOW);
  digitalWrite(ledr,HIGH);
  //si le bouton est appuyé, on éteint la led verte et on allume la rouge

  int nbAlea=random(1,7); //construit le nombre aléatoire de 1 à 6

  traitement_1_et2_a();
  traitement_3_et4_a(nbAlea); //passage à la fonction du chiffre à afficher de la valeur du dé (de 1 à 6)

  for(int i=1; i<=10; ++i){
    digitalWrite(ledr,HIGH);
    digitalWrite(ledv,LOW); 
    delay(500/i); //clignotement de plus en plus vite
    digitalWrite(ledr,LOW);
    digitalWrite(ledv,HIGH);
    delay(500/i);
  }
  
  eteindreBloc(); //extinction du chiffre affiché
  }
}

void traitement_3_et4_a(int chiffre_a_afficher){
    int IndSegAlea;
    boolean SegInutile=false;
    boolean IndiceSegAllum[7]={false,false,false,false,false,false,false};

    int NombreSegChiffre=0;
    for (int i=0;i<=6;i++){
      SegInutile = segIPChiffre(chiffre_a_afficher,i);

       if (SegInutile != true){
            NombreSegChiffre=NombreSegChiffre+1;        
       }
    }   
    
    for(int i=0;i<6000/dureeCli;++i){
              do {
                IndSegAlea=random(0,7); 
             }while (IndiceSegAllum[IndSegAlea]==true);
              
              digitalWrite(PinSeg[IndSegAlea],LOW); 
              delay(dureeCli);

              SegInutile = segIPChiffre(chiffre_a_afficher,IndSegAlea);
              if (SegInutile){   //seg ne fait pas parti du chiffre à afficher
                    digitalWrite(PinSeg[IndSegAlea],HIGH);
              }
              else{
                IndiceSegAllum[IndSegAlea]=true; 
                NombreSegChiffre=NombreSegChiffre-1;
                if (NombreSegChiffre<=0){
                  break;
                }
              }
    }
}



boolean segIPChiffre(int chiffre,int indice_seg){
  //cette fonction doit indiquer si le seg sert à afficher le chiffre indiqué
  
  boolean inutile=false;
  if (chiffre==0 && chfr0[indice_seg]==HIGH){
    inutile=true;    
    }
  if (chiffre==1 && chfr1[indice_seg]==HIGH){
    inutile=true; 
    }   
  if (chiffre==2 && chfr2[indice_seg]==HIGH){
     inutile=true; 
    }
  if (chiffre==3 && chfr3[indice_seg]==HIGH){
    inutile=true; 
    }
  if (chiffre==4 && chfr4[indice_seg]==HIGH){
    inutile=true; 
    }
  if (chiffre==5 && chfr5[indice_seg]==HIGH){
    inutile=true; 
    }
  if (chiffre==6 && chfr6[indice_seg]==HIGH){
    inutile=true; 
    }
  if (chiffre==7 && chfr7[indice_seg]==HIGH){
    inutile=true; 
    }
  if (chiffre==8 && chfr8[indice_seg]==HIGH){
    inutile=true; 
    }
  if (chiffre>=9 && chfr9[indice_seg]==HIGH){
    inutile=true; 
  }
  return inutile;
}

void traitement_1_et2_a (){
      int IndSegAlea;

      for(int i=0;i<2500/dureeCli;++i){ //transformation de la durée totale (2500ms) en un nbr de boucles
  
              IndSegAlea=random(0,7); //choix du seg à allumer (1 à 7 car on ne veut pas la led du point décimal (dp))
              digitalWrite(PinSeg[IndSegAlea],LOW); //allumage
              delay(dureeCli); //attente    
              digitalWrite(PinSeg[IndSegAlea],HIGH); //extinction
      }    
}

void eteindreBloc (){ 
  for (int i=0;i<=7;++i){ //je garde de 1 à 7 si je veux un jour rajouter le point décimal (DP)
    digitalWrite(PinSeg[i],HIGH); //on remet les segs à HIGH pour les éteindre  
  }
}

 

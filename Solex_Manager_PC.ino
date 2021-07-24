    //**************************************************************
    // Commande de moteur pas-à-pas unipolaire 4 fils
    // Driver ULN2003 et moteur réducté au 1:64
    // pour pilotage de 2 moteurs de mise au point du Sol'Ex
    // Xavier DUPONT 07/2021
    //**************************************************************
    
    //Inclure la librairie stepper.h
          #include <Stepper.h>
          #define STEPS 75
     
    //Créer 2 instances de la classe stepper
    //Le moteur de la lunette (fils 1 2 3 4) est branché sur les sorties 9 10 11 12 de l'Arduino
           
          Stepper Lunette_stepper(STEPS, 9, 11, 10, 12);     // Sens horaire
      
    //Le moteur de la camera (fils 1 2 3 4) est branché sur les sorties 5 6 7 8 de l'Arduino
           
          Stepper Camera_stepper(STEPS, 5, 7, 6, 8);     // Sens horaire
      
                    int Steps2TakeIntra = 0;
                    int Steps2TakeExtra = 0;
                    int StopStepper = 0;
                    int LunetteIntra = 0;
                    int LunetteExtra = 0;
                    int CameraIntra = 0;
                    int CameraExtra = 0;
                    int BPLunetteIntra = 2;
                    int BPLunetteExtra = 3;
                    int BPCameraIntra = 4;
                    int BPCameraExtra = 13;

                    int TestBPL;
                    int TestBPC;
                    int TestCoupure;
                    bool boucleLunetteIntra = false ;
                    bool boucleLunetteExtra = false ;
                    bool boucleCameraIntra = false ;
                    bool boucleCameraExtra = false ;
                    bool boucleAlim = true ;
    void setup()
     {               
         Serial.begin(9600);     // 9600 bps
         //Serial.println("demarrage");
         
          pinMode(A1, INPUT_PULLUP ); // lunette intra
          pinMode(A2, INPUT_PULLUP ); // Lunette Extra
          
          pinMode(A3, INPUT_PULLUP ); // Camera Intra
          pinMode(A4, INPUT_PULLUP ); // Camera Extra

          pinMode(A5, INPUT_PULLUP); // coupure du maintien
       
          Lunette_stepper.setSpeed(125);
          Camera_stepper.setSpeed(25); 
        
          Steps2TakeIntra  = 1;
          Steps2TakeExtra  = -1;
         
     }

    void loop()
      {
// ******************************************************************************
// Pilotage appli PC
//*******************************************************************************
        int received;
       
        if (Serial.available()>0) {
          received = Serial.read();

              switch(received) {
                
                case'H' : boucleLunetteIntra = true; 
                break;
                
                case'L' : boucleLunetteIntra = false;
                break;
                
                case'G' : boucleLunetteExtra = true; 
                break;
                
                case'K' : boucleLunetteExtra = false;
                break;

                case'I' : boucleCameraIntra = true; 
                break;
                
                case'M' : boucleCameraIntra = false;
                break;
                
                case'J' : boucleCameraExtra = true; 
                break;
                
                case'N' : boucleCameraExtra = false;
                break;

                case'X' : boucleAlim = true; 
                break;
                
                case'Y' : boucleAlim = false;
                break;

                case'A' : Lunette_stepper.setSpeed(30);
                break;
                
                case'B' : Lunette_stepper.setSpeed(150);
                break;

                case'C' : Lunette_stepper.setSpeed(300);
                break;
                
                case'D' : Camera_stepper.setSpeed(30);
                break;

                case'E' : Camera_stepper.setSpeed(150);
                break;
                
                case'F' : Camera_stepper.setSpeed(300);
                break;
                
                }
            
           }
          
    if (boucleLunetteIntra == true) Lunette_stepper.step(Steps2TakeIntra);
    else  Lunette_stepper.step(StopStepper); 

    if (boucleLunetteExtra == true) Lunette_stepper.step(Steps2TakeExtra);
    else  Lunette_stepper.step(StopStepper); 

    if (boucleCameraIntra == true) Camera_stepper.step(Steps2TakeIntra);
    else  Camera_stepper.step(StopStepper); 

    if (boucleCameraExtra == true) Camera_stepper.step(Steps2TakeExtra);
    else  Camera_stepper.step(StopStepper); 

    if (boucleAlim == true)   {
                               pinMode (5,HIGH);
                               pinMode (6,HIGH);
                               pinMode (7,HIGH);
                               pinMode (8,HIGH);
                               pinMode (9,HIGH);
                               pinMode (10,HIGH);
                               pinMode (11,HIGH);
                               pinMode (12,HIGH);
                              }
    else                      {
                              pinMode (5,LOW);
                              pinMode (6,LOW);
                              pinMode (7,LOW);
                              pinMode (8,LOW);
                              pinMode (9,LOW);
                              pinMode (10,LOW);
                              pinMode (11,LOW);
                              pinMode (12,LOW);
                              }


// ******************************************************************************
// Pilotage raquette boutons poussoirs
//*******************************************************************************
    
    TestBPL = digitalRead(A1);
              if (TestBPL == HIGH )
                    Lunette_stepper.step(StopStepper);
              else Lunette_stepper.step(Steps2TakeIntra);

    TestBPL = digitalRead(A2);
              if (TestBPL == HIGH )
                    Lunette_stepper.step(StopStepper);
              else Lunette_stepper.step(Steps2TakeExtra);

    TestBPC = digitalRead(A3);
              if (TestBPC == HIGH )
                    Camera_stepper.step(StopStepper);
              else Camera_stepper.step(Steps2TakeIntra);

    TestBPC = digitalRead(A4);
             if (TestBPC == HIGH )
                   Camera_stepper.step(StopStepper);
             else Camera_stepper.step(Steps2TakeExtra);   

    TestCoupure = digitalRead(A5);
              if (TestCoupure == HIGH )
                  {
                    pinMode (5,HIGH);
                    pinMode (6,HIGH);
                    pinMode (7,HIGH);
                    pinMode (8,HIGH);
                    pinMode (9,HIGH);
                    pinMode (10,HIGH);
                    pinMode (11,HIGH);
                    pinMode (12,HIGH);
                    
                  }
             else {
                    pinMode (5,LOW);
                    pinMode (6,LOW);
                    pinMode (7,LOW);
                    pinMode (8,LOW);
                    pinMode (9,LOW);
                    pinMode (10,LOW);
                    pinMode (11,LOW);
                    pinMode (12,LOW);
                     
                  }

    
       }

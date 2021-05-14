
//
// nnskelet.cc
// C++-programma voor neuraal netwerk (NN) met \'e\'en output-knoop
// TODO: 1,2,3,4,5,6,7
// Zie www.liacs.leidenuniv.nl/~kosterswa/AI/nnhelp.pdf
// 21 april 2021
// Compileren: g++ -Wall -O2 -o nn nnskelet.cc
// Gebruik:    ./nn <inputs> <hiddens> <epochs> <type> <seed>
// Voorbeeld:  ./nn 2 3 100000 1 1234
// Let op: de inputs komen in input[1],...,input[inputs] (tot en 
// met inputs) en de verborgen knopen worden geindiceerd met 
// 0,1,...,hiddens (tot en met hiddens)
//

#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
using namespace std;

const int MAX = 20;
const double ALPHA = 0.1;
const double BETA = 1.0;

// activatie-functie (sigmoid)
double sigmoid (double x) {
  return 1 / ( 1 + exp ( - BETA * x ) );
}//sigmoid

// afgeleide van sigmoid
double sigmoidprime (double x) {
  return BETA * sigmoid (x) * ( 1 - sigmoid (x) );
}//sigmoidprime

// activatie-functie (softplus)
double softplus (double x) {
  return log ( 1 + exp (x) );
}//softplus

// afgeleide van softplus
double softplusprime (double x) {
  return exp (x) / ( 1 + exp (x) );
}//softplusprime

// activatie-functie (ReLU)
double ReLU (double x) {
  if ( x >= 0 ) {
    return x;
  }//if
  return 0;
}//ReLU

// "afgeleide" van ReLU
double ReLUprime (double x) {
  if ( x >= 0 ) {
    return 1;
  }//if
  return 0;
}//ReLUprime

// activatie-functie van verschillend type
double g (double x, int type) {
  if ( type == 1 ) {
    return sigmoid (x);
  }//if
  else if ( type == 2 ) {
    return softplus (x);
  }//if
  else if ( type == 3 ) {
    return ReLU (x);
  }//if
  return 0;
}//g

// afgeleide van activatie-functie van verschillend type
double gprime (double x, int type) {
  if ( type == 1 ) {
    return sigmoidprime (x);
  }//if
  else if ( type == 2 ) {
    return softplusprime (x);
  }//if
  else if ( type == 3 ) {
    return ReLUprime (x);
  }//if
  return 0;
}//gprime

//return double tussen -1 en 1
double randnumber (){
    double randgetal = (double)rand() / RAND_MAX; // random getal tussen 0 en 1
    if(rand() % 2 == 0) //maak in 50% van de gevallen negatief
      randgetal *= -1;
    return randgetal;
}//randnumber

int main (int argc, char* argv[ ]) {

  int inputs, hiddens;            // aantal invoer- en verborgen knopen
                                  // inputs is exclusief de bias-knoop!
  double input[MAX];              // de invoer is input[1]...input[inputs]
  double inputtohidden[MAX][MAX]; // gewichten van invoerknopen 0..inputs
                                  // naar verborgen knopen 1..hiddens
  double hiddentooutput[MAX];     // gewichten van verborgen knopen 0..hiddens
                                  // naar de ene uitvoerknoop
  double inhidden[MAX];           // invoer voor de verborgen knopen 1..hiddens
  double acthidden[MAX];          // en de uitvoer daarvan
  double inoutput;                // invoer voor de ene uitvoerknoop
  double netoutput;               // en de uitvoer daarvan: de net-uitvoer
  double target;                  // gewenste uitvoer
  double error;                   // verschil tussen gewenste en 
                                  // geproduceerde uitvoer
  double delta;                   // de delta voor de uitvoerknoop
  double deltahidden[MAX];        // de delta's voor de verborgen 
                                  // knopen 1..hiddens
  int epochs;                     // aantal trainingsvoorbeelden
  int cnt, i, j;                  // tellertjes
  int type;                       // welke activatie-functie?
  int seed;                       // voor random number generator

  if ( argc != 6 ) {
    cout << "Gebruik: " << argv[0] << " <inputs> <hiddens> <epochs> "
	 << "<type> <seed>" << endl;
    return 1;  
  }//if
  inputs = atoi (argv[1]);
  if ( inputs >= MAX ) {
    cout << "Aantal inputs < " << MAX << "!" << endl;
    return 1;
  }//if
  hiddens = atoi (argv[2]);
  if ( hiddens >= MAX ) {
    cout << "Aantal verborgen knopen < " << MAX << "!" << endl;
    return 1;
  }//if
  epochs = atoi (argv[3]);
  type = atoi (argv[4]);
  seed = atoi (argv[5]);
  input[0] = -1;                  // invoer bias-knoop: altijd -1
  acthidden[0] = -1;              // verborgen bias-knoop: altijd -1
  srand (seed);

  
  //LATER TODO-7 lees de gehele Abalone dataset:
  ifstream abalonedata ("leiden.abalone.data",ios::in);
  if ( abalonedata.fail ( ) ) {
    cout << "Inputfile bestaat niet!" << endl;
    return 1;
  }//if
  const int SAMPLES = 4177;
  double abalone[SAMPLES][9];
  for ( i = 0; i < SAMPLES; i++ )
    for ( j = 0; j < 9; j++ )
      abalonedata >> abalone[i][j];
  abalonedata.close ( );
  

  //TODO-1 initialiseer de gewichten random tussen -1 en 1: 
  // inputtohidden en hiddentooutput
  // rand ( ) levert geheel randomgetal tussen 0 en RAND_MAX; denk aan casten
  for(int i = 0; i <= hiddens; i++){
    hiddentooutput[i] = randnumber();
    for(int j = 0; j<= inputs; j++)
      inputtohidden[i][j] = randnumber();
  }//for

  double totaalfout = 0;

  for ( cnt = 1; cnt <= epochs; cnt++ ){

    //TODO-2 lees voorbeeld in naar input/target, of genereer ter plekke:
    // als voorbeeld: de XOR-functie, waarvoor geldt dat inputs = 2
    int x = rand ( ) % 2; int y = rand ( ) % 2; int dexor = ( x + y ) % 2;
    input[1] = x; input[2] = y; target = dexor; 
    
    
    //LATER TODO-7 Abalone, met inputs = 8:
    int mysample = rand ( ) % SAMPLES;
    for ( j = 1; j <= 8; j++ )
      input[j] = abalone[mysample][j-1];
    target = abalone[mysample][8] / 30.0;
    

    //TODO-3 stuur het voorbeeld door het netwerk
    // reken inhidden's uit, acthidden's, inoutput en netoutput
    //inhidden
    for(int j = 1; j <= hiddens; j++){// som 0->inputs Wl,j*xl
      inhidden[j] = 0;
      for(int l = 0; l <= inputs; l++){
        inhidden[j] += inputtohidden[l][j] * input[l];
      }//for
    }//for

    //achthidden
    for(int j = 1; j <= hiddens; j++){
      acthidden[j] = g(inhidden[j], type);
    }//for

    //inoutpot
    inoutput = 0;
    for(int l = 0; l <= hiddens; l++) //som 0->hiddens wl*al    
      inoutput += hiddentooutput[l] * acthidden[l];

    //netoutput
    netoutput = g(inoutput, type);

    //TODO-4 bereken error, delta, en deltahidden
    error = target - netoutput;

    delta = error * gprime(inoutput, type);

    for(int j = 1; j <= hiddens; j++)
      deltahidden[j] = gprime(inhidden[j], type) * hiddentooutput[j] * delta;
    
    //TODO-5 update gewichten hiddentooutput en inputtohidden
    for(int j = 0; j <= hiddens; j++)
      hiddentooutput[j] = hiddentooutput[j] + (ALPHA * acthidden[j] * delta);
    
    for(int k = 0; k <= inputs; k++)
      for(int j = 1; j <= hiddens; j++)
        inputtohidden[k][j] = inputtohidden[k][j] + (ALPHA * input[k] * deltahidden[j]);

    //TODO-6 beoordeel het netwerk en rapporteer 
    // bijvoorbeeld (totaal)fout bij laatste 1000 voorbeelden
    totaalfout += error * error;

    if(cnt % 1000 == 0){ //elke 1000 testen
      cout << totaalfout << endl;
      totaalfout = 0;
    }//if

  }//for

  return 0;
}//main


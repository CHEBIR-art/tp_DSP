#include "main.h"
#include "mx_init.h"
#include "filter_Coeff.h"
#include "musique.h"

#define AUDIOFREQ_16K 		((uint32_t)16000U)  //AUDIOFREQ_16K = 16 Khz
#define BUFFER_SIZE_INPUT	4000
#define BUFFER_SIZE_OUTPUT	4000
#define BUFFER_SIZE_SINUS 	16000
#define BUFFER_SIZE_AUDIO	16000
#define AMPLITUDE			300
#define SAI_WAIT			100
#define TIME_START			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET)
#define TIME_STOP			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET)
#define PI					3.141592
#define TIME_START HAL_GPIO_WritePin (GPIOA,GPIO_PIN_0,GPIO_PIN_SET)
#define TIME_STOP HAL_GPIO_WritePin (GPIOA,GPIO_PIN_0,GPIO_PIN_RESET)


extern SAI_HandleTypeDef hsai_BlockA2;
extern SAI_HandleTypeDef hsai_BlockB2;
extern TIM_HandleTypeDef htim3;

int16_t sinusTable[BUFFER_SIZE_SINUS]  = { 0 };
int16_t audioTable[BUFFER_SIZE_SINUS]  = { 0 };
int16_t bufferInputRight[BUFFER_SIZE_INPUT] = { 0 };
int16_t bufferInputLeft[BUFFER_SIZE_INPUT]  = { 0 };
int16_t bufferOutputRight[BUFFER_SIZE_OUTPUT] = { 0 };
int16_t bufferOutputLeft[BUFFER_SIZE_OUTPUT] = { 0 };
int16_t echInputLeft   = 0;
int16_t echInputRight  = 0;
int16_t echOutputRight = 0;
int16_t echOutputLeft  = 0;


uint32_t NBR_ECH_DUREE ;
uint32_t NBR_ECH_PERIO ;



void passThrough(void);
void echo (void);
void reverberation (void);
uint32_t calculNbEchPeriod (uint32_t frequence);
uint32_t calculNbEchNote (float duree );
void notePlayClassic(uint32_t frequence, float duree );
void musicPlay(struct note musique[TAILLE_MUSIQUE]);
void initSinusTable(void);
void notePlayDDS(uint32_t frequence, float duree);
void audioCreate(void);
void audioTablePlay(void);



void passThrough(void){
	/* Reception des Ã©chantillons d'entrÃ©e */
	HAL_SAI_Receive (&hsai_BlockB2,(uint8_t *)&echInputLeft,1,SAI_WAIT);	// Left
	HAL_SAI_Receive (&hsai_BlockB2,(uint8_t *)&echInputRight,1,SAI_WAIT);	// Right

	/*  Output = Input */
	echOutputLeft = echInputLeft;
	echOutputRight = echInputRight;

	/* Envoi des Ã©chantillons de sortie */
	HAL_SAI_Transmit(&hsai_BlockA2,(uint8_t *)&echOutputLeft,1,SAI_WAIT);	// Left
	HAL_SAI_Transmit(&hsai_BlockA2,(uint8_t *)&echOutputRight,1,SAI_WAIT);	// Right
}



void echo (void){

	/*  Reception des echantillons */

    	HAL_SAI_Receive (&hsai_BlockB2,(uint8_t *)&echInputLeft,1,SAI_WAIT);	// Left
		HAL_SAI_Receive (&hsai_BlockB2,(uint8_t *)&echInputRight,1,SAI_WAIT);	// Right

	static uint16_t index = BUFFER_SIZE_INPUT-1;
	 	 /* RÃ©initialiser */

         bufferInputRight[index]=echInputRight ;
		 bufferInputLeft[index]=echInputLeft ;
		 echOutputRight = 0;
		 echOutputLeft =0;

		 /*calcule de filtre numÃ©rique*/


		 echOutputRight=  bufferInputRight[index]+0.8*bufferInputRight[index-1];// y= x[n]+0.8x[n-1] gain de 0.8
		 echOutputLeft=  bufferInputLeft[index]+0.8*bufferInputLeft[index-1];


		 /* vieillissement du buffer circulaire*/

		 if (index == 0){
			 index = BUFFER_SIZE_INPUT-1;  //Remet l'indice Ã  la derniÃ¨re position
		 }else {
			 index--;                      // Diminue l'indice pour le faire "vieillir"
		 }
		 /* Envoi des Ã©chantillons de sortie */

		 HAL_SAI_Transmit(&hsai_BlockA2,(uint8_t *)&echOutputLeft,1,SAI_WAIT);	// Left
		 HAL_SAI_Transmit(&hsai_BlockA2,(uint8_t *)&echOutputRight,1,SAI_WAIT);	// Right
}


void reverberation (void){

	/*  Reception des echantillons */

	    	HAL_SAI_Receive (&hsai_BlockB2,(uint8_t *)&echInputLeft,1,SAI_WAIT);	// Left
			HAL_SAI_Receive (&hsai_BlockB2,(uint8_t *)&echInputRight,1,SAI_WAIT);	// Right

		static uint16_t index = BUFFER_SIZE_INPUT-1;
		 	 /* RÃ©initialiser */

	         bufferInputRight[index]=echInputRight ;
			 bufferInputLeft[index]=echInputLeft ;
			 echOutputRight = 0;
			 echOutputLeft =0;

			 /*calcule de filtre numÃ©rique*/


				 echOutputRight=  bufferInputRight[index]+0.8*bufferOutputRight[index-1];// y= x[n]+0.8y[n-1]  gain < 1
				 echOutputLeft=  bufferInputLeft[index]+0.8*bufferOutputLeft[index-1];
				 bufferOutputRight[index]= echOutputRight;
				 bufferOutputLeft[index]= echOutputLeft;
			 /* vieillissement du buffer circulaire*/

			 if (index == 0){
				 index = BUFFER_SIZE_INPUT-1;  //Remet l'indice Ã  la derniÃ¨re position
			 }else {
				 index--;                      // Diminue l'indice pour le faire "vieillir"
			 }
			 /* Envoi des Ã©chantillons de sortie */

			 HAL_SAI_Transmit(&hsai_BlockA2,(uint8_t *)&echOutputLeft,1,SAI_WAIT);	// Left
			 HAL_SAI_Transmit(&hsai_BlockA2,(uint8_t *)&echOutputRight,1,SAI_WAIT);	// Right
	}



uint32_t calculNbEchPeriod (uint32_t frequence){


		return  AUDIOFREQ_16K  /frequence;    //NbEchPerio = Fech /Fnote
}

uint32_t calculNbEchNote (float duree ){


		return  duree * AUDIOFREQ_16K ; //NbrEchDuree = Dnote * Fech

}

void notePlayClassic(uint32_t frequence, float duree ){

			NBR_ECH_PERIO= calculNbEchPeriod (frequence);
			NBR_ECH_DUREE = calculNbEchNote  (duree);

		for (uint16_t i= 0 ; i< NBR_ECH_DUREE;i++){
			TIME_START;

			echOutputRight= AMPLITUDE *sin((i*PI*2)/NBR_ECH_PERIO);
			echOutputLeft= AMPLITUDE *sin((i*PI*2)/NBR_ECH_PERIO);

			TIME_STOP ;
				// transmission des echantillions
			HAL_SAI_Transmit(&hsai_BlockA2,(uint8_t *)&echOutputLeft,1,SAI_WAIT);	// Left
			HAL_SAI_Transmit(&hsai_BlockA2,(uint8_t *)&echOutputRight,1,SAI_WAIT);	// Right
	}

}
void musicPlay(struct note musique[TAILLE_MUSIQUE]){


	for(uint8_t i=0; i<TAILLE_MUSIQUE;i++){
			notePlayClassic(musique[i].freqNote ,musique[i].dureeNote);
		}


}


void initSinusTable(void){
	for (uint16_t i=0; i<BUFFER_SIZE_SINUS;i++){


	 sinusTable[i]= AMPLITUDE * sin( (2*PI*i) / BUFFER_SIZE_SINUS) ;

	}
}

 void notePlayDDS(uint32_t frequence, float duree){

	 	NBR_ECH_PERIO= calculNbEchPeriod (frequence);
	 	NBR_ECH_DUREE = calculNbEchNote  (duree);
	 	  //uint32_t phaseacc
	 		for (uint16_t i= 0 ; i< BUFFER_SIZE_SINUS;i++){
	 			TIME_START;

	 			echOutputRight= sinusTable[(i*frequence)% BUFFER_SIZE_SINUS];
	 			echOutputLeft= sinusTable[(i*frequence)% BUFFER_SIZE_SINUS];


	 			TIME_STOP ;

	 				// transmission des echantillions
	 			HAL_SAI_Transmit(&hsai_BlockA2,(uint8_t *)&echOutputLeft,1,SAI_WAIT);	// Left
	 			HAL_SAI_Transmit(&hsai_BlockA2,(uint8_t *)&echOutputRight,1,SAI_WAIT);	// Right
	 	}



 }

 void audioCreate(void) {
     uint32_t sampleRate = AUDIOFREQ_16K;  // 16 kHz
     float duration = 1.0;  // 1 second duration
     uint32_t nbrSamples = (uint32_t)(duration * sampleRate);

     // Initialisation des variables d'index
     uint32_t index = 0;

     // Générer le signal 350 Hz avec la méthode classique
     NBR_ECH_PERIO = calculNbEchPeriod(350);
     for (uint32_t i = 0; i < nbrSamples; i++) {
         int16_t sample = AMPLITUDE * sin((2 * PI * i) / NBR_ECH_PERIO);
         audioTable[index++] += sample;  // Ajouter au tableau audioTable
     }

    // Générer le signal 587 Hz avec DDS
     index = 0;
     for (uint32_t i = 0; i < nbrSamples; i++) {
         int16_t sample = sinusTable[(i * 587) % BUFFER_SIZE_SINUS];
         audioTable[index++] += sample;  // Ajouter au tableau audioTable
     }

     // Génération du signal 1500 Hz avec une approche IIR (par exemple, un simple oscillateur IIR)
     index = 0;
     float alpha = 0.5;  // Paramètre de contrôle pour le filtre IIR
     int16_t prevSample = 0;
     for (uint32_t i = 0; i < nbrSamples; i++) {
         int16_t sample = alpha * prevSample + AMPLITUDE * sin(2 * PI * 1500 * i / sampleRate);
         audioTable[index++] += sample;
         prevSample = sample;
     }
 }

 void audioTablePlay(void) {
	 // jouer l'enssenble du tableau audioTable
     for (uint32_t i = 0; i < BUFFER_SIZE_AUDIO; i++) {
         int16_t sample = audioTable[i];

         // Transmission des echantillions
         HAL_SAI_Transmit(&hsai_BlockA2, (uint8_t *)&sample, 1, SAI_WAIT);  // Left
         HAL_SAI_Transmit(&hsai_BlockA2, (uint8_t *)&sample, 1, SAI_WAIT);  // Right
     }
 }







int main(void)
{
	SCB_EnableICache();
	SCB_EnableDCache();
	HAL_Init();
	BOARD_Init();
	 initSinusTable();
	while(1){
		//passThrough();
		//echo();
		//reverberation ();
		//notePlayClassic (300,10);
		//musicPlay(musique);
		//notePlayDDS(300,10);
		audioCreate();
		audioTablePlay();

	}

}

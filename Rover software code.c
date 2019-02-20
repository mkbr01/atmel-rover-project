//WHEELS parent object
//Code for Wheels.c

// This object has to activate all its child objects. The activation
//is implemented by the child objects, and here is only called.
//
#include <FreeRTOS. h>
#include <task .h>
#include "Algorithm. h"
#include "Motor. h"
#include "Params. h"
#include "ControlPC. h"



//This function activates all the child objects of Wheels object //

void activateWheels(void)
{
activateWheelsMotor ();
activateWheelsParams ();
activateControlPC ();
}


Code for Wheels.h


/////////////////////////////////////////////
// This code is the header file for Wheels. c
////////////////////////////////////////////

#define WHEELS.H
#define WHEELS.H
//Declaration of the function used in Wheels.c, that has to activate all
//the child objects//

void activateWheels{void);
#end if




//WHEEL-CONTROL-PC child object//
//Code for ControlPC.c//

#include <avr/io .h>
#include <FreeRTOSConfig. h>
#include <FreeRTOS. h>
#include <task .h>
#include "ControlPC. h"
#include "Params. h"
#include "Algorithm. h"
#include "Motor. h"
#include "globals .h"
#include "mode.h"


unsigned char mode;
unsigned char pars [3];
unsigned char calculations [3];
unsigned char wheels pars [ 3];

//Function: vWheels//
void vTaskT (void) II The task itself
{
portTickType xLastWakeTime;
xLastWakeTime = xTaskGetTickCount ();
while (1)
{
vTaskDelayUntil(&xLastWakeTime, (100/portTICK_RATE_MS));
vWheelsControl ();
}
}

//Function: activate Wheels//
void activateControlPC (void)
{
xTaskCreate (vTaskT, "T" 300 NUlL 1 NUlL);
return 0;
}


//Function: v Wheels Control, Checks the rover mode and forces
//an appropiate behaviour for each case

void vWheelsControl(void) 
                         

{
getMode ();
switch (mode)
{
case 1:
vNormalMode();
break;

case 2:
vSafeMode () ;
break;

default:
break; 
}
}


//Function: vNormalMode//
void vNormalMode (void)
{
GetParameters (wheelspars); //Asks object WHEELSPARAMS to
//execute GetParameters and obtain pars

calculateAlgorithm (wheelspars); //Asks object WHEELSALGORJTHM
//to execute Calculate using pars and obtain calculations

Cntrl(calculations); //Asks object WHEELSMOTOR to execute
//Cntrl using calculations
}

//Function: vSafeMode//

void vSafeMode (void)
{
calculations [0] 50;
calculations [1] = O;
calculations [2] = O;
Cntrl (calculations); //Ignores all parameters and asks
//WHEELSMOTOR to execute Cntrl with input 0
}



//Code for ControlPC.h
#ifndef WHEELSlCONTROLPCH
#define WHEELSlCONTROLPCH
void activateControlPC (void);
void vTaskT (void);
void vWheelsControl (void);
void vNormalMode (void);
void vSafeMode (void);
#end if



//WHEEL-PARAMS child object//
//Code for Pararns.c, Wheels_Params is a protected object 
//that has to link the data coming from the telecommand to 
//the controLpc object. These data are the
//parameters that will be used by the algorithm

#include <FreeRTOS. h>
#include <semphr. h>
#include "Params. h"

//Declaration of the three parameters

static unsigned char angle;
static unsigned char speed;
unsigned char dir;

static xSemaphoreHandle xsemaph=NUIL;  //Declaration of the
//semaphore

//Activation of the Params object. Default parameters are set for the
//activation

void activateWheelsParams (void)
{
angle = 50; //0 leftward, 100 rightward, 50 straight
dir = 0; //0 forward, 1 backward
speed = 0; //0 stop, 100 max    
 
 
vSemaphoreCreateBinary (xsemaph); // Creation of the
// semaphore needed to protect the parameters
}


//This function locate the parameters received  
//by telecommand into an array 


void setParWheels (unsigned char *pars)
{
xSemaphoreTake ( xsemaph , portMAX_DELAY) ;//Take the semaphore 
}
angle = pars[O];
dir = pars[1];
speed = pars[2];

xSemaphoreGive (xsemaph); //Release the semaphore 
}
// This function reads the parameters received by telecommand 
void GetP arameters (unsigned char *wheels pars)
{
xSemaphoreTake (xsemaph ,portMAX_DELAY); I* Take the semaphore *I
}
wheelspars [0] angle;
wheelspars [1] = dir;
wheelspars [2] = speed;
xSemaphoreGive (xsemaph); //Release the semaphore



// Code for Params.h//
//This is the header file of Params.c

#define WHEELSPARAMS.H
#define WHEELSPARAMS.H
#include <avr/io.h>
#include <FreeRTOSConfig.h>
#include <FreeRTOS.h>
#include <task.h>

// Declaration of the activation function of the object 
void activateWheelsParams (void);
// Declaration of the function that set the parameters coming from telecommand
void setParWheels (unsigned char *Pars);
void GetParameters (unsigned char *wheels pars);
#end if





/// WHEEL-ALGORITHM child object///
//Code for Algorithm.c

#include "Algorithm.h"
unsigned char calculateAlgorithm (const unsigned char *Wheelspars)
{
unsigned char calculations [3];
unsigned char angle = wheelspars [0];
unsigned char speed = wheelspars [2];

double LWheel;
double RWheel;
double temp1 ;
double temp2;
calculations [1] = wheelspars [1];

if(angle ==100.)
{
LWheel = OxFF * (double) speed /100.;
RWheel = OxOO * (double) speed /100.;
}
else if (angle ==0.)
{
}
LWheel = OxOO * (double) speed /100.;
RWheel = OxFF * (double) speed /100.;
else if (angle ==50.)
{
}
LWheel = (OxFF * (double) speed /100.);
RWheel = ( OxFF * (double) speed /100.);
17
}
else if { {unsigned char} angle < 50.}
{
LWheel = {OxFF * (double) speed/ 100. * angle /50.);
RWheel = {OxFF * (double) speed/ 100.);
}
else
{
LWheel = {OxFF * (double) speed/ 100.};
RWheel = {OxFF * (double) speed/ 100.*(angle -50.}/ 50.};
}

temp1 = LWheel; 
temp2 = RWheel;

calculations [0] = (unsigned char)temp1;
calculations [2] = (unsigned char)temp2;

return *Calculations;



//Code for Algorithm.h

#define WHEELSALGORITHM.H
#define WHEELSALGORITHM.H
unsigned char calculateAlgorithm ( const unsigned char *Wheelspars);
#end if


//WHEEL-MOTOR child object
//Code for Motor.c

#include <avr/io .h>
#include "Motor. h"

//activateWheelsMotor
//Initialization of the Wheels motor object with:
//Timer 0
//Phase and frequency correct pwm
//8 prescaler
////////////////////////////////////

void activate WheelsMotor (void)
{
PORTB = OxOO ;
DDRB = (l<<DDB3) I (l<<DDB4) I (l<<DDBO) I (l<<DDBl);
TCXJROA &= -(l<<OOMOAO) & -(l<<OOMOAl) & -(l<<OOMOBO) & -(l<<OOMOBl);
TCNTO = OxOO;
TCXJROA = (l<<WGMXJ);
TCCROB = (l<<CSOl);
TCXJROA I= (l«COMOAO) I (l<<OOMOAl) I (l«COMOBO) I (l«OOMOBl);
}

OCROA = OxFF;
OCROB = OxFF;
//Name: Cntrl
//Uses the values sent by the WheelsControllPC object.

void Cntrl(unsigned char *Calculations)
{
}
OCROA = calculations [0];
OCROB = calculations [2];
PORTB=( calculations [1] <<PBO) I (calculations [1] <<PBl);



//Code for Motor.h

#define WHEELSMOTOR.H
#define WHEELSMOTOR.H

//activate WheelsM otor
Input: void
Outpud: void

void activateWheelsMotor (void);

Cntrl

Input: *calculations
Outpud: void

void Cntrl(unsigned char *Calculations);
#end if
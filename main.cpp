#include "mbed.h"

I2C tempsensor(I2C_SDA, I2C_SCL); //Declaracion del protocolo de comunicacion I2C
//Serial pc(SERIAL_TX, SERIAL_RX);
Serial pc(USBTX, USBRX); //tx, rx
DigitalOut calentamiento(PA_0);
DigitalIn pulsa1(BUTTON1);
DigitalOut led(LED1);
DigitalOut puerta1in1(PB_3);
DigitalOut puerta1in2(PA_10);
DigitalOut puerta2in1(PB_10);
DigitalOut puerta2in2(PB_4);
DigitalOut vent1in1(PC_7);
DigitalOut vent1in2(PA_9);
PwmOut puerta1(PB_5);
PwmOut puerta2(PA_8);

PwmOut vent1(PB_6);

const int addr = 0x90; //Direccion de con el pin de direccionamiento en 0
char config_t[3]; //Arreglo de tres posiciones para configuracion del pointer register 
char temp_read[2]; //Arreglo para leer la temperatura TLOW - THigh
float temp;


//DigitalIn Boton(BUTTON1);

Ticker Repetidor;

void muestra()
{
    temp = (0.0625 * (((temp_read[0] << 8) + temp_read[1]) >> 4))-5; //convert data
    //pc.printf("%.2f,%i,%i,%i,%i\n\r", temp);
}



void f1(){    
     

    puerta1.period_ms(20);
    puerta2.period_ms(20);
    puerta1.pulsewidth_us(800);//0
    puerta2.pulsewidth_us(500);//180
    wait_ms(500);


    for(int i = 0;i<10;i++)
        {    
               
            wait_ms(500);
                        }  //  pc.printf("DATA,TIME,TIMER, ,");
     
    calentamiento=0;
    wait_ms(500); 
    puerta1.period_ms(20);
         
    puerta1.pulsewidth_us(2000);//
     
    wait_ms(500);
               } 



void f2(){
    
    while(temp<80)
        {           
         pc.printf("DATA,TIME,TIMER, ,");

         pc.printf(" %.2f \n\r", temp);   
         tempsensor.read(addr, temp_read, 2);
         wait_ms(500);
 
 //         tempsensor.read(addr, temp_read, 2);
        }
    
        calentamiento=1;
        wait_ms(500);
        puerta1.period_ms(20);
        puerta2.period_ms(20);
        puerta1.pulsewidth_us(2000);//
        wait_ms(500);
        puerta2.pulsewidth_us(2000);//

        
        vent1in1=1;
        vent1in2=0;
        vent1.period_ms(100);    
    
            
            
            
        vent1=1;
  
    }
    
    
void  f3(){
    
              while(temp>60)
            {      pc.printf("DATA,TIME,TIMER, ,");
                   pc.printf(" %.2f \n\r", temp);
                   tempsensor.read(addr, temp_read, 2);
                
                 wait_ms(500);
 
               // tempsensor.read(addr, temp_read, 2);
            
            }
            vent1in1=1;
            vent1in2=0;   
            vent1.period_ms(100);
            vent1=0.5;
    }  
    
    void f4()
    {
        while(temp>30)
            {   
             pc.printf("DATA,TIME,TIMER, ,");
             pc.printf(" %.2f \n\r", temp);
             tempsensor.read(addr, temp_read, 2);
          
             wait_ms(500);
 
               //tempsensor.read(addr, temp_read, 2);                
            }
        
        vent1in1=1;
        vent1in2=0;
        vent1.period_ms(100);
        vent1=0.2;
        }
        
        void f5(){
            while(temp>25)
            {       pc.printf("DATA,TIME,TIMER, ,");

                 pc.printf(" %.2f \n\r", temp);
                     tempsensor.read(addr, temp_read, 2);
                     wait_ms(500);
 
                //tempsensor.read(addr, temp_read, 2);                
            }
            
            puerta1.period_ms(20);
            puerta2.period_ms(20);
            puerta1.pulsewidth_us(500);//
            puerta2.pulsewidth_us(2000);//

       
            wait_ms(500);
            calentamiento=0;
     

            vent1in1=1;
            vent1in2=0;
            vent1=0;
                  
                  
                  
                   }
    
int main() {
        
    config_t[0] = 0x01; //set pointer Registro de configuracion
    config_t[1] = 0x60; // config byte 1
    config_t[2] = 0xA0; // config byte2
    tempsensor.write(addr, config_t, 3);
    config_t[0] = 0x00; //set pointer lectura de temperatura 
    tempsensor.write(addr, config_t, 1); //send to pointer 'read temp'
    Repetidor.attach (&muestra,  1.0 );
    tempsensor.read(addr, temp_read, 2);
//pc.baud(9600);
//pc.printf("CLEARDATA");
  //registro.printf("LABEL,Hora,tiempo,cont,");
  //pc.printf("RESETTIMER");


        
    while(1) {
pc.baud(9600);       
     pc.printf("DATA,TIME,TIMER, ,");
        pc.printf(" %.2f \n\r", temp);
       tempsensor.read(addr, temp_read, 2);
        wait_ms(500);
        //pc.printf(" %.2f \n\r", tempsensor);
                    
     calentamiento=1;
          
        if(pulsa1==0)
        {pc.printf(" %.2f \n\r", temp);
      tempsensor.read(addr, temp_read, 2);
        //wait_ms(500);
        
            while(pulsa1==0)
            {
                led=1;
        pc.printf(" %.2f \n\r", temp);
        tempsensor.read(addr, temp_read, 2);
        //wait_ms(2000);
                
            }
     
     //calentamiento=1;
     
     
            while(1){
     
     
     
            f1();
          
            f2();
            
            f3();
            f4();
            f5();
                }
                }

}
}
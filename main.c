#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
Desafio Técnico - NUVEN
Código: Iteração ADC e Saídas Digitais
Dev: Emanuel de Araújo Mota
Data: 20/06/2024

O programa consiste em trazer um exemplo de aplicação para o monitoramento de tensão da bateria de um microcontrolador
ARM. Ao sair do range adequado de tensão (1,72 V ~ 3,6 V), variáveis de comando são alteradas para desligar a saída 
via relé, acionar um led de indicação e deixar disponível uma string para envio do erro ocorrido.
*/

int State_LED, Command_LED;                         // Variáveis auxiliares para comando e estado do LED2
int State_Relay, Command_Relay;                     // Variáveis auxiliares para comando e estado do Rele

int Resolution_ADC = 4096;                          // Resolução do ADC (12 bits)
int Voltage_Max_Battery = 3511;                     // Valor digital para tensão máxima do ARM via datasheet (3.6 V)
int Voltage_Min_Battery = 1668;                     // Valor digital para tensão mínima do ARM via datasheet (1.72 V)
int Test_Voltage = 300;                             // Valor digital de teste, a ser lido pelo ADC
                                                        // O valor aqui colocado foi simulado, pois considera-se que função Config_Analog_Battery envia o dado digital lido

char str[0];                                        // String para plot, feito string para facilitar futuras aplicações para enviar o dado via UART, I2C e etc

int Config_Analog_Battery(int Resolution_ADC);      
int Config_LED(int Command_LED);
int Config_Relay(int Command_Relay);

/*
    *@brief
    * Main do código. Não foram utilizados recursos de clean code, pois há pouca experiência do dev utilizando clean
    * code e o código é simples.
    *@return none
    */
int main (){
    if(Config_Analog_Battery(Resolution_ADC) >= 1668 && Config_Analog_Battery(Resolution_ADC) <= 3511)
    {
        printf("Bateria Saudável"); 
        Config_LED(0);
        Config_Relay(1);
        sprintf(str,"\nTensão da Bateria: %.2f V",(float)(Config_Analog_Battery(Resolution_ADC))*(42.0/40960.0));
        printf(str);
    } 
    else{
        printf("Bateria Insuficiente, o programa está congelado!!! Altere Test_Voltage");
        Config_LED(0);
        Config_Relay(0);
        sprintf(str,"\nTensão da Bateria: %.2f V",(float)(Config_Analog_Battery(Resolution_ADC))*(42.0/40960.0));
        printf(str);
    } 
}

/*
    * @brief Configuração para Acionamento do LED2
    * State_LED '0' para ligado e '1' para desligado
    * @return State_LED
    */
int Config_LED(int Command_LED){
    if(Command_LED==1)
    {
        State_LED = 0;
        printf("\nLED2 Ligado");
    }
    else
    {
        State_LED = '1';
        printf("\nLED2 Desligado");
    } 
    return State_LED;   
}

/*
    * @brief Configuração para Acionamento do Relé
    * State_Relay '1' para ligado e '0' para desligado
    * @return State_Relay
    */
int Config_Relay(int Command_Relay){
    if(Command_Relay==1){
        State_Relay = '1';
        printf("\nSaída ligada!!!!");
    } 
    else
    {
        State_Relay = '0';
        printf("\nSaida desligada!!!");
    } 
    return State_Relay;
}

/*
    * @brief Configuração do ADC
    * Resolution_ADC é resolução de 12 bits (0-4096)
    * Read_Voltage é a leitura de uma simulação da tensão via monitor serial
    * 
    * @return Valor do ADC lido 
    */
int Config_Analog_Battery(int Resolution_ADC){
    return Test_Voltage;
}
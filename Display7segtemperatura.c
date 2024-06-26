#define ADC_VREF_mV    3300.0 // en milivoltios
#define ADC_RESOLUTION 4096.0

int segmentos[7] = {25, 23, 5, 21, 18, 22, 19};

#define PIN_LM35 27 // Cambiado a pin GPIO36 para la lectura analógica en un ESP32
float valorsensor;
int dig[] = {32, 33, 15};
int num[10][7] = {
  // a b   c  d  e   f g
    {0, 0, 0, 0, 0, 0, 1}, // 0
    {1, 0, 0, 1, 1, 1, 1}, // 1
    {0, 0, 1, 0, 0, 1, 0}, // 2
    {0, 0, 0, 0, 1, 1, 0}, // 3
    {1, 0, 0, 1, 1, 0, 0}, // 4
    {0, 1, 0, 0, 1, 0, 0}, // 5
    {0, 1, 0, 0, 0, 0, 0}, // 6
    {0, 0, 0, 1, 1, 1, 1}, // 7
    {0, 0, 0, 0, 0, 0, 0}, // 8
    {0, 0, 0, 1, 1, 0, 0}  // 9
};

void setup()
{
    Serial.begin(9600);

    for (int i = 0; i < 7; i++)
    {
        pinMode(segmentos[i], OUTPUT);
    }
    for (int k = 0; k < 2; k++)
    {
        pinMode(dig[k], OUTPUT);
        digitalWrite(dig[k], HIGH); // Cambiado a HIGH para apagar los displays
    }
    
}

void loop()
{
    valorsensor = analogRead(PIN_LM35); // Leer el valor del sensor LM35
    
    // Convertir el valor del ADC a voltaje en milivoltios
    float milliVolt = valorsensor * (ADC_VREF_mV / ADC_RESOLUTION);
    // Convertir el voltaje a temperatura en °C
    float tempC = milliVolt / 10;
    // Convertir de °C a °F
    float tempF = tempC * 9 / 5 + 32;
    Serial.print("Temperatura: ");
    Serial.print(tempC); // Imprimir la temperatura en °C
    Serial.print("°C");
    Serial.print("  ~  "); // Separador entre °C y °F
    Serial.print(tempF);
    Serial.println("°F");
    int parte_entera = (int)tempC; // Convierte el número a entero
    float parte_decimal = tempC - parte_entera; // Calcula la parte decimal
    int unidad = parte_entera / 10; // Obtiene la decena de la parte entera
    int decena = parte_entera % 10; // Obtiene la unidad de la parte entera

    Serial.print("Decena: ");
    Serial.println(decena);
    Serial.print("Unidad: ");
    Serial.println(unidad);
    Serial.print("Parte Decimal: ");
    Serial.println(parte_decimal, 2); // Muestra la parte decimal con dos decimales
    
    // Mostrar decena en el display 0 y unidad en el display 1

    int valor[2] = {decena, unidad};
  
    for (int j = 0; j < 2; j++) {
        for (int s = 0; s < 7; s++) {
            digitalWrite(segmentos[s], num[valor[j]][s]);
        }

        digitalWrite(dig[j], LOW);
        delay(20);
        digitalWrite(dig[j], HIGH);
    }
}

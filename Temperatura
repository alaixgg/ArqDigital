#define ADC_VREF_mV    3300.0 // en milivoltios
#define ADC_RESOLUTION 4096.0
#define PIN_LM35       27 // Pin GPIO36 (ADC0) del ESP32 conectado al LM35
int Ventilador = 32;
float valorsensor;
int potencimetro = 14;
float voltaje;

void setup() {
  Serial.begin(9600);
  pinMode(Ventilador, OUTPUT);
}

void loop() {
  delay(1000);
  valorsensor = analogRead(potencimetro);
  voltaje = valorsensor * (3.3 / 4095);
  // leer el valor ADC del sensor de temperatura
  int adcVal = analogRead(PIN_LM35);
  // convertir el valor ADC a voltaje en milivoltios
  float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);
  // convertir el voltaje a temperatura en °C
  float tempC = milliVolt / 10;
  // convertir °C a °F
  float tempF = tempC * 9 / 5 + 32;
  float diferencia = valorsensor - tempC;

  // imprimir la temperatura en el Monitor Serie:
  Serial.print("Temperature: ");
  Serial.print(tempC);   // imprime la temperatura en °C
  Serial.print("°C");
  Serial.print("  ~  "); // separador entre °C y °F
  Serial.print(tempF); 
  Serial.println("°F");
  // imprimir el voltaje
  Serial.print("Voltage: ");
  Serial.print(voltaje);
  Serial.println("V");
}

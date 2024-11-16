#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the I2C address for the LCD

const int lm35Pin = PA0; // Analog channel 0 for LM35 (ADC0)

void setup()
{
    // Set ADC reference voltage to AVCC
    ADMUX = (1 << REFS0); // Reference voltage = AVCC

    // Initialize ADC
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC, prescaler of 128

    lcd.init();      // Initialize the LCD
    lcd.backlight(); // Turn on the backlight
}

int readADC(int channel)
{
    // Clear the previous channel selection by masking the lower 3 bits
    ADMUX = (ADMUX & 0xF8) | (channel & 0x07);

    // Small delay to let channel selection settle (optional)
    _delay_us(10); // If available, otherwise you can omit this

    // Start single conversion
    ADCSRA |= (1 << ADSC);

    // Wait for conversion to complete
    while (ADCSRA & (1 << ADSC))
        ;

    // Return the 10-bit ADC result
    return ADC;
}

float lastTemperature = 0.0;
void loop()
{
    float adc_val = readADC(lm35Pin);
    // ADC value conversion into degree celsius
    float mV = (adc_val * 5000.0) / 1023.0;
    float temperatureC = mV / 10;

    if (abs(temperatureC - lastTemperature) > 0.1)
    { // Update if change > 0.1 degree
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Temp: ");
        lcd.setCursor(6, 0);
        lcd.print(temperatureC, 2);
        lcd.write((char)223); // Write degree symbol
        lcd.print("C");

        lastTemperature = temperatureC;
    }

    delay(1000);
}

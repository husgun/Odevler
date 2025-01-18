#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

int main(void)
{
    // 1. Sistem saatini ayarla
    SysCtlClockSet(SYSCTL_SYSDIV_16 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    // 2. FPU'yu etkinle�tir
    FPUEnable();
    FPULazyStackingEnable();

    // 3. Floating-point de�i�kenler tan�mla
    float a = 5.5, b = 2.2, c = -3.3;
    float result;
    int i ;

    // 4. Temel matematiksel i�lemler
    result = a + b;          // Toplama
    result = a - b;          // ��karma
    result = a * b;          // �arpma
    result = a / b;          // B�lme

    // 5. Geli�mi� matematiksel i�lemler (math.h kullan�m�)
    float angle = 45.0;      // Derece cinsinden
    float radians = angle * (M_PI / 180.0); // Dereceden radyana d�n���m
    float sineValue = sinf(radians);        // Sin�s
    float cosineValue = cosf(radians);      // Kosin�s
    float tangentValue = tanf(radians);     // Tanjant
    float exponential = expf(a);            // e^x
    float naturalLog = logf(b);             // Do�al logaritma
    float log10Value = log10f(b);           // Logaritma taban 10
    float powerValue = powf(a, b);          // �s alma (a^b)
    float squareRoot = sqrtf(a);            // Kare k�k

    // 6. Mutlak De�er ve Yuvarlama ��lemleri
    float absValue = fabsf(c);              // Mutlak de�er
    float ceilValue = ceilf(a);             // Yukar� yuvarlama
    float floorValue = floorf(a);           // A�a�� yuvarlama

    // 7. �zel Durumlar (Infinity ve NaN Kontrol�)
    float divZero = 1.0f / 0.0f;            // Sonsuzluk (Infinity)
    float notANumber = sqrtf(-1.0f);        // Tan�ms�z de�er (NaN)

    // 8. H�zl� Fourier D�n���m� i�in �rnek Sin�s Sinyali �retimi
    float frequency = 1.0; // Frekans (Hz)
    float samplingRate = 100.0; // �rnekleme frekans� (Hz)
    int numSamples = 10;   // �rnek say�s�
    for (i = 0; i < numSamples; i++)
    {
        float time = i / samplingRate;      // Zaman hesaplama
        float signal = sinf(2 * M_PI * frequency * time); // Sin�s sinyali
    }

    // 9. Floating-Point ��lemler Sonucunda LED G�stergesi
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);

    if (squareRoot > 2.0f)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1); // LED yak
    }
    else
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0); // LED s�nd�r
    }

    while (1)
    {
        // Ana d�ng�
    }
}

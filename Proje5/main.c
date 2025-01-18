#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/hibernate.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

// LED G�stergesi i�in kullan�lan GPIO Pin
#define LED_RED GPIO_PIN_1
#define LED_PORT GPIO_PORTF_BASE

int main(void)
{
    // 1. Sistem Saatini Ayarla (16 MHz)
    SysCtlClockSet(SYSCTL_SYSDIV_16 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    // 2. Hibernation Mod�l�n� Etkinle�tir
    SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_HIBERNATE)); // HIB mod�l�n�n haz�r oldu�unu kontrol et
    HibernateEnableExpClk(SysCtlClockGet()); // Saat kayna��n� HIB'e ba�la

    // 3. Hibernation RTC'yi S�f�rla ve Etkinle�tir
    HibernateRTCSet(0); // RTC'yi s�f�rla
    HibernateRTCEnable(); // RTC'yi etkinle�tir

    // 4. Uyanma Kaynaklar�n� Belirle
    HibernateWakeSet(HIBERNATE_WAKE_PIN | HIBERNATE_WAKE_RTC);

    // 5. RTC Match Ayar� (10 saniye sonra uyand�r)
    uint32_t sleepTime = 10; // Uyuma s�resi (saniye)
    HibernateRTCMatchSet(0, HibernateRTCGet() + sleepTime);

    // 6. GPIO i�in LED Yap�land�rmas�
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // GPIOF mod�l�n� etkinle�tir
    GPIOPinTypeGPIOOutput(LED_PORT, LED_RED); // GPIOF'deki k�rm�z� LED'i ��k�� olarak ayarla
    GPIOPinWrite(LED_PORT, LED_RED, LED_RED); // Uyuma �ncesi LED'i yak

    // 7. Hibernation Moduna Ge�
    HibernateRequest(); // Cihaz� uykuya al

    // Uyand�ktan sonra kod burada �al���r
    while (1)
    {
        GPIOPinWrite(LED_PORT, LED_RED, 0); // Uyand�ktan sonra LED'i s�nd�r
        // Daha fazla i�lem buraya eklenebilir
    }

}

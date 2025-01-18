#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/hibernate.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

// LED Göstergesi için kullanýlan GPIO Pin
#define LED_RED GPIO_PIN_1
#define LED_PORT GPIO_PORTF_BASE

int main(void)
{
    // 1. Sistem Saatini Ayarla (16 MHz)
    SysCtlClockSet(SYSCTL_SYSDIV_16 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    // 2. Hibernation Modülünü Etkinleþtir
    SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_HIBERNATE)); // HIB modülünün hazýr olduðunu kontrol et
    HibernateEnableExpClk(SysCtlClockGet()); // Saat kaynaðýný HIB'e baðla

    // 3. Hibernation RTC'yi Sýfýrla ve Etkinleþtir
    HibernateRTCSet(0); // RTC'yi sýfýrla
    HibernateRTCEnable(); // RTC'yi etkinleþtir

    // 4. Uyanma Kaynaklarýný Belirle
    HibernateWakeSet(HIBERNATE_WAKE_PIN | HIBERNATE_WAKE_RTC);

    // 5. RTC Match Ayarý (10 saniye sonra uyandýr)
    uint32_t sleepTime = 10; // Uyuma süresi (saniye)
    HibernateRTCMatchSet(0, HibernateRTCGet() + sleepTime);

    // 6. GPIO için LED Yapýlandýrmasý
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // GPIOF modülünü etkinleþtir
    GPIOPinTypeGPIOOutput(LED_PORT, LED_RED); // GPIOF'deki kýrmýzý LED'i çýkýþ olarak ayarla
    GPIOPinWrite(LED_PORT, LED_RED, LED_RED); // Uyuma öncesi LED'i yak

    // 7. Hibernation Moduna Geç
    HibernateRequest(); // Cihazý uykuya al

    // Uyandýktan sonra kod burada çalýþýr
    while (1)
    {
        GPIOPinWrite(LED_PORT, LED_RED, 0); // Uyandýktan sonra LED'i söndür
        // Daha fazla iþlem buraya eklenebilir
    }

}

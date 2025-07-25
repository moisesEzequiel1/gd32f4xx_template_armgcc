#include "Rcu.hpp"
#include "gd32f4xx.h"

template<typename E>
constexpr auto etoi(E const value) {
    return static_cast<std::underlying_type_t<E>>(value);
}

void Rcu::EnableInternal16MHzClock(void) {
  CTL.bits.IRC16MEN = 1; // Enable internal 16MHz RC oscillator
  // Wait for the IRC16M to be stable
  while (CTL.bits.IRC16MSTB == 0) {
  }
}

void Rcu::SetInternal16MHzClockTrimming(uint8_t trimming) {
  CTL.bits.IRC16MADJ = trimming; // Set the trimming value for IRC16M
}

void Rcu::EnableExternalClock(void) {
  CTL.bits.HXTALEN = 1; // Enable external high-speed oscillator (HXTAL)
  // Wait for the HXTAL to be stable
  while (CTL.bits.HXTALSTB == 0) {
  }
}

void Rcu::EnablePll(void) {
  CTL.bits.PLLEN = 1; // Enable PLL
  // Wait for the PLL to be stable
  while (CTL.bits.PLLSTB == 0) {
  }
}
void Rcu::ConfigurePll(PllClockSource source, PLLFactors factors) {
  // Set the PLL clock source and factors
  SetPllClockSource(source);
  SetPllFactors(factors);
}

void Rcu::SetAhbPrescaler(AhbPrescaler prescaler) {
  // Set the AHB prescaler in the configuration register
  CFG0.bits.AHBPSC = prescaler;
}

void Rcu::SetApb1Prescaler(Apb1Prescaler prescaler) {
  // Set the APB1 prescaler in the configuration register
  CFG0.bits.APB1PSC = prescaler;
}

void Rcu::SetApb2Prescaler(Apb2Prescaler prescaler) {
  // Set the APB2 prescaler in the configuration register
  CFG0.bits.APB2PSC = prescaler;
}
void Rcu::SetSystemClockSource(SystemClockSource source) {
  // Set the system clock source in the configuration register
  CFG0.bits.SCS = source;
  // Wait until the system clock source is switched
  while ((CFG0.bits.SCSS) != source) {
    // Optionally, add a timeout to avoid infinite loops
  }
}

void Rcu::EnableGpioA(void) {
  AHB1EN.bits.PAEN = 1; // Enable GPIOA clock
}

void Rcu::EnableGpioB(void) {
  AHB1EN.bits.PBEN = 1; // Enable GPIOB clock
}
void Rcu::EnableGpioC(void) {
  AHB1EN.bits.PCEN = 1; // Enable GPIOC clock
}
void Rcu::EnableI2c0(void) {
  APB1EN.bits.I2C0EN = 1; // Enable I2C0 clock
}
void Rcu::EnablePowerInterface(void) {
  APB1EN.bits.PMUEN = 1; // Enable Power Management Unit clock
}
void Rcu::EnableSpi0(void) {
  APB2EN.bits.SPI0EN = 1; // Enable SPI0 clock
}

void Rcu::SetPllClockSource(PllClockSource source) {
  // Set the PLL clock source in the register
  PLL.bits.PLLSEL = source;
  // Ensure the change is applied immediately
  // This might require additional steps depending on the hardware specifics
}

void Rcu::SetPllFactors(PLLFactors factors) {
  PLL.bits.PLLP = factors.p_;
  PLL.bits.PLLN = factors.n_;
  PLL.bits.PLLQ = factors.q_;
  PLL.bits.PLLPSC = factors.psc_;
}


void Rcu::UpdateSystemCoreClock() {
    // constexpr uint32_t IRC16M_VALUE = 16000000U;

    switch (CFG0.bits.SCSS) {
    case SystemClockSource::IRC16M:
        SystemCoreClock = IRC16M_VALUE;
        break;

    case SystemClockSource::HXTAL:
        SystemCoreClock = HXTAL_VALUE;
        break;

    case SystemClockSource::PLLP: {
        uint32_t pllpsc = etoi(PLL.bits.PLLPSC) + 1; // /PLLPSC prescaler
        uint32_t plln = PLL.bits.PLLN;               // PLL multiplier
        uint32_t pllp = (etoi(PLL.bits.PLLP) + 1U) * 2U; // PLLP: 00=2, 01=4, 10=6, 11=8
        uint32_t pllsel = etoi(PLL.bits.PLLSEL);     // Clock source for PLL

        uint32_t ck_src = (pllsel == etoi(PllClockSource::HXTAL)) ? HXTAL_VALUE : IRC16M_VALUE;

        // Final PLL output frequency: ((source / PLLPSC) * PLLN) / PLLP
        SystemCoreClock = ((ck_src / pllpsc) * plln) / pllp;
        break;
    }

    default:
        SystemCoreClock = IRC16M_VALUE;
        break;
    }

    // AHB Prescaler
    static constexpr uint8_t ahb_exp[16] = {
        0, 0, 0, 0, 0, 0, 0, 0, // 0xxx: /1
        1, 2, 3, 4, 6, 7, 8, 9  // 1000+: /2, /4, ..., /512
    };
    uint32_t prescaler_exp = ahb_exp[etoi(CFG0.bits.AHBPSC)];
    // Apply AHB prescaler
    SystemCoreClock >>= prescaler_exp;
}
#include "Rcu.hpp"

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

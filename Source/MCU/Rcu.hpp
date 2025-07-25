#pragma once

#include <stdint.h>
#include <type_traits>
class Rcu {

public:
  enum class PllFactorP: uint8_t {
    DIV2 = 0b00, // CK_PLLP = CK_PLLVCO / 2
    DIV4 = 0b01, // CK_PLLP = CK_PLLVCO / 4
    DIV6 = 0b10, // CK_PLLP = CK_PLLVCO / 6
    DIV8 = 0b11  // CK_PLLP = CK_PLLVCO / 8
  };
  enum class PllClockSource : uint8_t {
    IRC16M = 0, // IRC16M clock selected as PLL source
    HXTAL = 1   // HXTAL clock selected as PLL source
  };

  enum class PllVcoPrescaler : uint8_t {
    DIV2 = 0b000010,  // CK_PLLSRC / 2
    DIV3 = 0b000011,  // CK_PLLSRC / 3
    DIV4 = 0b000100,  // CK_PLLSRC / 4
    DIV5 = 0b000101,  // CK_PLLSRC / 5
    DIV6 = 0b000110,  // CK_PLLSRC / 6
    DIV7 = 0b000111,  // CK_PLLSRC / 7
    DIV8 = 0b001000,  // CK_PLLSRC / 8
    DIV9 = 0b001001,  // CK_PLLSRC / 9
    DIV10 = 0b001010, // CK_PLLSRC / 10
    DIV11 = 0b001011, // CK_PLLSRC / 11
    DIV12 = 0b001100, // CK_PLLSRC / 12
    DIV13 = 0b001101, // CK_PLLSRC / 13
    DIV14 = 0b001110, // CK_PLLSRC / 14
    DIV15 = 0b001111, // CK_PLLSRC / 15
    DIV16 = 0b010000, // CK_PLLSRC / 16
    DIV17 = 0b010001, // CK_PLLSRC / 17
    DIV18 = 0b010010, // CK_PLLSRC / 18
    DIV19 = 0b010011, // CK_PLLSRC / 19
    DIV20 = 0b010100, // CK_PLLSRC / 20
    DIV21 = 0b010101, // CK_PLLSRC / 21
    DIV22 = 0b010110, // CK_PLLSRC / 22
    DIV23 = 0b010111, // CK_PLLSRC / 23
    DIV24 = 0b011000, // CK_PLLSRC / 24
    DIV25 = 0b011001, // CK_PLLSRC / 25
    DIV26 = 0b011010, // CK_PLLSRC / 26
    DIV27 = 0b011011, // CK_PLLSRC / 27
    DIV28 = 0b011100, // CK_PLLSRC / 28
    DIV29 = 0b011101, // CK_PLLSRC / 29
    DIV30 = 0b011110, // CK_PLLSRC / 30
    DIV31 = 0b011111, // CK_PLLSRC / 31
    DIV32 = 0b100000, // CK_PLLSRC / 32
    DIV33 = 0b100001, // CK_PLLSRC / 33
    DIV34 = 0b100010, // CK_PLLSRC / 34
    DIV35 = 0b100011, // CK_PLLSRC / 35
    DIV36 = 0b100100, // CK_PLLSRC / 36
    DIV37 = 0b100101, // CK_PLLSRC / 37
    DIV38 = 0b100110, // CK_PLLSRC / 38
    DIV39 = 0b100111, // CK_PLLSRC / 39
    DIV40 = 0b101000, // CK_PLLSRC / 40
    DIV41 = 0b101001, // CK_PLLSRC / 41
    DIV42 = 0b101010, // CK_PLLSRC / 42
    DIV43 = 0b101011, // CK_PLLSRC / 43
    DIV44 = 0b101100, // CK_PLLSRC / 44
    DIV45 = 0b101101, // CK_PLLSRC / 45
    DIV46 = 0b101110, // CK_PLLSRC / 46
    DIV47 = 0b101111, // CK_PLLSRC / 47
    DIV48 = 0b110000, // CK_PLLSRC / 48
    DIV49 = 0b110001, // CK_PLLSRC / 49
    DIV50 = 0b110010, // CK_PLLSRC / 50
    DIV51 = 0b110011, // CK_PLLSRC / 51
    DIV52 = 0b110100, // CK_PLLSRC / 52
    DIV53 = 0b110101, // CK_PLLSRC / 53
    DIV54 = 0b110110, // CK_PLLSRC / 54
    DIV55 = 0b110111, // CK_PLLSRC / 55
    DIV56 = 0b111000, // CK_PLLSRC / 56
    DIV57 = 0b111001, // CK_PLLSRC / 57
    DIV58 = 0b111010, // CK_PLLSRC / 58
    DIV59 = 0b111011, // CK_PLLSRC / 59
    DIV60 = 0b111100, // CK_PLLSRC / 60
    DIV61 = 0b111101, // CK_PLLSRC / 61
    DIV62 = 0b111110, // CK_PLLSRC / 62
    DIV63 = 0b111111  // CK_PLLSRC / 63
  };

  enum class AhbPrescaler : uint8_t {
    DIV1 = 0b0000, // AHB clock not divided
    DIV2 = 0b1000, // AHB clock divided by 2
    DIV4 = 0b1001, // AHB clock divided by 4
    DIV8 = 0b1010, // AHB clock divided by 8
    DIV16 = 0b1011, // AHB clock divided by 16
    DIV64 = 0b1100, // AHB clock divided by 64
    DIV128 = 0b1101, // AHB clock divided by 128
    DIV256 = 0b1110, // AHB clock divided by 256
    DIV512 = 0b1111 // AHB clock divided by 512
  };
  enum class Apb1Prescaler : uint8_t {
    DIV1 = 0b000, // APB1 clock not divided
    DIV2 = 0b100, // APB1 clock divided by 2 
    DIV4 = 0b101, // APB1 clock divided by 4
    DIV8 = 0b110, // APB1 clock divided by 8  
    DIV16 = 0b111 // APB1 clock divided by 16
  };
  enum class Apb2Prescaler : uint8_t {
    DIV1 = 0b000, // APB2 clock not divided
    DIV2 = 0b100, // APB2 clock divided by 2
    DIV4 = 0b101, // APB2 clock divided by 4
    DIV8 = 0b110, // APB2 clock divided by 8
    DIV16 = 0b111 // APB2 clock divided by 16
  };
  enum class SystemClockSource : uint8_t {
    IRC16M = 0, // IRC16M clock selected as system clock
    HXTAL = 1,  // HXTAL clock selected as system clock
    PLLP = 2    // PLLP clock selected as system clock
  };
  struct PLLFactors 
  {
    PllFactorP p_;
    uint8_t q_; // PLLQ output division factor
    uint16_t n_; // PLLN output division factor
    PllVcoPrescaler psc_; // PLL VCO source clock prescaler
    PLLFactors(PllFactorP p, uint8_t q, uint16_t n, PllVcoPrescaler psc): p_(p), q_(q), n_(n), psc_(psc) {}
  };

  void EnableInternal16MHzClock(void);
  void SetInternal16MHzClockTrimming(uint8_t trimming);
  void EnableExternalClock(void);
  void EnablePll(void);
  void ConfigurePll(PllClockSource source, PLLFactors factors);

  // Métodos de configuración de prescalers
  void SetAhbPrescaler(AhbPrescaler prescaler);
  void SetApb1Prescaler(Apb1Prescaler prescaler);
  void SetApb2Prescaler(Apb2Prescaler prescaler);

  void SetSystemClockSource(SystemClockSource source);

  // Habilitación de periféricos
  void EnableGpioA(void);
  void EnableGpioB(void);
  void EnableGpioC(void);
  void EnableI2c0(void);
  void EnablePowerInterface(void);
  void EnableSpi0(void);

  // Modo de alta velocidad
  void EnableHighDriveMode(void);

  void SetPllClockSource(PllClockSource source);
  void SetPllFactors(PLLFactors factors);

  void UpdateSystemCoreClock(void);
private:
  union CTL_register {
    struct CTL_bits {
      uint8_t IRC16MEN : 1;       // [0]   Enable internal 16MHz RC oscillator
      uint8_t IRC16MSTB : 1;      // [1]   IRC16M ready flag
      const uint8_t res2 : 1;     // [2]   Reserved
      uint8_t IRC16MADJ : 5;      // [3:7] IRC16M trim adjust
      uint8_t IRC16MCALIB;        // [8:15] IRC16M calibration value (full byte)
      uint8_t HXTALEN : 1;        // [16]  Enable external crystal oscillator
      uint8_t HXTALSTB : 1;       // [17]  HXTAL ready flag
      uint8_t HXTALBPS : 1;       // [18]  HXTAL bypass mode
      uint8_t CKMEN : 1;          // [19]  Clock monitor enable
      const uint8_t res20_23 : 4; // [20:23] Reserved
      uint8_t PLLEN : 1;          // [24]  PLL enable
      uint8_t PLLSTB : 1;         // [25]  PLL ready flag
      uint8_t PLLI2SEN : 1;       // [26]  PLLI2S enable
      uint8_t PLLI2SSTB : 1;      // [27]  PLLI2S ready flag
      uint8_t PLLSAIEN : 1;       // [28]  PLLSAI enable
      uint8_t PLLSAISTB : 1;      // [29]  PLLSAI ready flag
      const uint8_t res30_31 : 2; // [30:31] Reserved
    } __attribute__((packed));
    uint32_t value;       // Acceso completo de 32 bits al registro
    struct CTL_bits bits; // Acceso por estructura
  };

  union PLL_register {
    struct PLL_bits {
      PllVcoPrescaler PLLPSC : 6;        // [0:5] PLL VCO source clock prescaler
      uint16_t PLLN : 9;         // [6:14] PLL VCO clock multiplication factor
      const uint8_t res2_0 : 1;  // [15] Reserved
      PllFactorP PLLP : 2;       // [16:17] PLLP output division factor
      const uint8_t res2_3 : 4;  // [18:21] Reserved
      PllClockSource PLLSEL : 1; // [22] PLL source clock selection
      const uint8_t res2_7 : 1;  // [23] Reserved
      uint8_t PLLQ : 4;          // [24:27] PLLQ output division factor
      const uint8_t res3_4 : 4;  // [28:31] Reserved
    } __attribute__((packed));

    uint32_t value;
    struct PLL_bits bits;
  };

  union CFG0_register {
    struct CFG0_bits {
      // Byte 0 (bits 0–7)
      SystemClockSource SCS : 2;        // [0:1] System clock switch
      const SystemClockSource SCSS : 2; // [2:3] System clock switch status
      AhbPrescaler AHBPSC : 4;          // [4:7] AHB prescaler selection

      // Byte 1 (bits 8–15)
      const uint8_t res1_0 : 2;  // [8:9] Reserved
      Apb1Prescaler APB1PSC : 3; // [10:12] APB1 prescaler selection
      Apb2Prescaler APB2PSC : 3; // [13:15] APB2 prescaler selection

      // Byte 2 (bits 16–23)
      uint8_t RTCDIV : 5;    // [16:20] RTC clock divider factor
      uint8_t CKOUT0SEL : 2; // [21:22] CKOUT0 clock source selection
      uint8_t I2SSEL : 1;    // [23] I2S clock source selection

      // Byte 3 (bits 24–31)
      uint8_t CKOUT0DIV : 3; // [24:26] CKOUT0 divider
      uint8_t CKOUT1DIV : 3; // [27:29] CKOUT1 divider
      uint8_t CKOUT1SEL : 2; // [30:31] CKOUT1 clock source selection
    } __attribute__((packed));

    uint32_t value;
    struct CFG0_bits bits;
  };

  union INT_register {
    struct INT_bits {
      // Byte 0 (bits 0–7)
      uint8_t IRC32KSTBIF : 1; // [0] IRC32K stabilization interrupt flag
      uint8_t LXTALSTBIF : 1;  // [1] LXTAL stabilization interrupt flag
      uint8_t IRC16MSTBIF : 1; // [2] IRC16M stabilization interrupt flag
      uint8_t HXTALSTBIF : 1;  // [3] HXTAL stabilization interrupt flag
      uint8_t PLLSTBIF : 1;    // [4] PLL stabilization interrupt flag
      uint8_t PLLI2SSTBIF : 1; // [5] PLLI2S stabilization interrupt flag
      uint8_t PLLSAISTBIF : 1; // [6] PLLSAI stabilization interrupt flag
      uint8_t CKMIF : 1;       // [7] HXTAL clock stuck interrupt flag

      // Byte 1 (bits 8–15)
      uint8_t IRC32KSTBIE : 1;  // [8] IRC32K stabilization interrupt enable
      uint8_t LXTALSTBIE : 1;   // [9] LXTAL stabilization interrupt enable
      uint8_t IRC16MSTBIE : 1;  // [10] IRC16M stabilization interrupt enable
      uint8_t HXTALSTBIE : 1;   // [11] HXTAL stabilization interrupt enable
      uint8_t PLLSTBIE : 1;     // [12] PLL stabilization interrupt enable
      uint8_t PLLI2SSTBIE : 1;  // [13] PLLI2S stabilization interrupt enable
      uint8_t PLLSAISTBIE : 1;  // [14] PLLSAI stabilization interrupt enable
      const uint8_t res1_7 : 1; // [15] Reserved

      // Byte 2 (bits 16–23)
      uint8_t IRC32KSTBIC : 1; // [16] IRC32K stabilization interrupt clear
      uint8_t LXTALSTBIC : 1;  // [17] LXTAL stabilization interrupt clear
      uint8_t IRC16MSTBIC : 1; // [18] IRC16M stabilization interrupt clear
      uint8_t HXTALSTBIC : 1;  // [19] HXTAL stabilization interrupt clear
      uint8_t PLLSTBIC : 1;    // [20] PLL stabilization interrupt clear
      uint8_t PLLI2SSTBIC : 1; // [21] PLLI2S stabilization interrupt clear
      uint8_t PLLSAISTBIC : 1; // [22] PLLSAI stabilization interrupt clear
      uint8_t CKMIC : 1;       // [23] HXTAL clock stuck interrupt clear

      // Byte 3 (bits 24–31)
      const uint8_t res3 : 8; // [24:31] Reserved
    } __attribute__((packed));

    uint32_t value;
    struct INT_bits bits;
  };

  union AHB1RST_register {
    struct AHB1RST_bits {
      // Byte 0 (bits 0–7)
      uint8_t PARST : 1; // [0] GPIO port A reset
      uint8_t PBRST : 1; // [1] GPIO port B reset
      uint8_t PCRST : 1; // [2] GPIO port C reset
      uint8_t PDRST : 1; // [3] GPIO port D reset
      uint8_t PERST : 1; // [4] GPIO port E reset
      uint8_t PFRST : 1; // [5] GPIO port F reset
      uint8_t PGRST : 1; // [6] GPIO port G reset
      uint8_t PHRST : 1; // [7] GPIO port H reset

      // Byte 1 (bits 8–15)
      uint8_t PIRST : 1;        // [8] GPIO port I reset
      const uint8_t res1_1 : 3; // [9:11] Reserved
      uint8_t CRCRST : 1;       // [12] CRC reset
      const uint8_t res1_5 : 3; // [13:15] Reserved

      // Byte 2 (bits 16–23)
      const uint8_t res2_0 : 3; // [16:18] Reserved
      uint8_t DMA0RST : 1;      // [19] DMA0 reset
      uint8_t DMA1RST : 1;      // [20] DMA1 reset
      uint8_t IPARST : 1;       // [21] IPA reset
      const uint8_t res2_6 : 1; // [22] Reserved
      uint8_t ENETRST : 1;      // [23] Ethernet reset

      // Byte 3 (bits 24–31)
      const uint8_t res3_0 : 1; // [24] Reserved
      const uint8_t res3_1 : 2; // [25:26] Reserved
      uint8_t USBHSRST : 1;     // [27] USBHS reset
      const uint8_t res3_4 : 4; // [28:31] Reserved
    } __attribute__((packed));

    uint32_t value;
    struct AHB1RST_bits bits;
  };

  union AHB2RST_register {
    struct AHB2RST_bits {
      // Byte 0 (bits 0–7)
      uint8_t DCIRST : 1;       // [0] DCI reset
      const uint8_t res0_1 : 5; // [1:5] Reserved
      uint8_t TRNGRST : 1;      // [6] TRNG reset
      uint8_t USBFSRST : 1;     // [7] USBFS reset

      // Byte 1 (bits 8–15)
      const uint8_t res1 : 8; // [8:15] Reserved

      // Byte 2 (bits 16–23)
      const uint8_t res2 : 8; // [16:23] Reserved

      // Byte 3 (bits 24–31)
      const uint8_t res3 : 8; // [24:31] Reserved
    } __attribute__((packed));

    uint32_t value;
    struct AHB2RST_bits bits;
  };

  union AHB3RST_register {
    struct AHB3RST_bits {
      // Byte 0 (bits 0–7)
      uint8_t EXMCRST : 1;      // [0] EXMC reset
      const uint8_t res0_1 : 7; // [1:7] Reserved

      // Byte 1 (bits 8–15)
      const uint8_t res1 : 8; // [8:15] Reserved

      // Byte 2 (bits 16–23)
      const uint8_t res2 : 8; // [16:23] Reserved

      // Byte 3 (bits 24–31)
      const uint8_t res3 : 8; // [24:31] Reserved
    } __attribute__((packed));

    uint32_t value;
    struct AHB3RST_bits bits;
  };

  union APB1RST_register {
    struct APB1RST_bits {
      // Byte 0 (bits 0–7)
      uint8_t TIMER1RST : 1;  // [0] TIMER1 reset
      uint8_t TIMER2RST : 1;  // [1] TIMER2 reset
      uint8_t TIMER3RST : 1;  // [2] TIMER3 reset
      uint8_t TIMER4RST : 1;  // [3] TIMER4 reset
      uint8_t TIMER5RST : 1;  // [4] TIMER5 reset
      uint8_t TIMER6RST : 1;  // [5] TIMER6 reset
      uint8_t TIMER11RST : 1; // [6] TIMER11 reset
      uint8_t TIMER12RST : 1; // [7] TIMER12 reset

      // Byte 1 (bits 8–15)
      uint8_t TIMER13RST : 1;   // [8] TIMER13 reset
      const uint8_t res1_1 : 2; // [9:10] Reserved
      uint8_t WWDGTRST : 1;     // [11] WWDGT reset
      const uint8_t res1_4 : 2; // [12:13] Reserved
      uint8_t SPI1RST : 1;      // [14] SPI1 reset
      uint8_t SPI2RST : 1;      // [15] SPI2 reset

      // Byte 2 (bits 16–23)
      const uint8_t res2_0 : 1; // [16] Reserved
      uint8_t USART1RST : 1;    // [17] USART1 reset
      uint8_t USART2RST : 1;    // [18] USART2 reset
      uint8_t UART3RST : 1;     // [19] UART3 reset
      uint8_t UART4RST : 1;     // [20] UART4 reset
      uint8_t I2C0RST : 1;      // [21] I2C0 reset
      uint8_t I2C1RST : 1;      // [22] I2C1 reset
      uint8_t I2C2RST : 1;      // [23] I2C2 reset

      // Byte 3 (bits 24–31)
      const uint8_t res3_0 : 1; // [24] Reserved
      uint8_t CAN0RST : 1;      // [25] CAN0 reset
      uint8_t CAN1RST : 1;      // [26] CAN1 reset
      const uint8_t res3_3 : 1; // [27] Reserved
      uint8_t PMURST : 1;       // [28] PMU reset
      uint8_t DACRST : 1;       // [29] DAC reset
      uint8_t UART6RST : 1;     // [30] UART6 reset
      uint8_t UART7RST : 1;     // [31] UART7 reset
    } __attribute__((packed));

    uint32_t value;
    struct APB1RST_bits bits;
  };

 union APB2RST_register {
    struct APB2RST_bits {
        uint32_t TIMER0RST     : 1;  // [0]
        uint32_t TIMER7RST     : 1;  // [1]
        uint32_t res0_2        : 2;  // [2:3] Reserved
        uint32_t USART0RST     : 1;  // [4]
        uint32_t USART5RST     : 1;  // [5]
        uint32_t res0_6        : 2;  // [6:7] Reserved
        uint32_t ADCRST        : 1;  // [8]
        uint32_t res1_1        : 2;  // [9:10]
        uint32_t SDIORST       : 1;  // [11]
        uint32_t SPI0RST       : 1;  // [12]
        uint32_t SPI3RST       : 1;  // [13]
        uint32_t SYSCFGRST     : 1;  // [14]
        uint32_t res1_15       : 1;  // [15]
        uint32_t TIMER8RST     : 1;  // [16]
        uint32_t TIMER9RST     : 1;  // [17]
        uint32_t TIMER10RST    : 1;  // [18]
        uint32_t res2_19       : 1;  // [19]
        uint32_t SPI4RST       : 1;  // [20]
        uint32_t SPI5RST       : 1;  // [21]
        uint32_t res2_22_25    : 4;  // [22:25]
        uint32_t res3_24_25    : 2;  // [26:27] WARNING: tu definición estaba mal numerada
        uint32_t TLIRST        : 1;  // [28]
        uint32_t res3_29_31    : 3;  // [29:31]
    } __attribute__((packed));

    uint32_t value;
    struct APB2RST_bits bits;
};


union AHB1EN_register {
  struct AHB1EN_bits {
    // Byte 0 (bits 0–7)
    uint8_t PAEN : 1;  // [0] GPIO port A clock enable
    uint8_t PBEN : 1;  // [1] GPIO port B clock enable
    uint8_t PCEN : 1;  // [2] GPIO port C clock enable
    uint8_t PDEN : 1;  // [3] GPIO port D clock enable
    uint8_t PEEN : 1;  // [4] GPIO port E clock enable
    uint8_t PFEN : 1;  // [5] GPIO port F clock enable
    uint8_t PGEN : 1;  // [6] GPIO port G clock enable
    uint8_t PHEN : 1;  // [7] GPIO port H clock enable

    // Byte 1 (bits 8–15)
    uint8_t PIEN : 1;           // [8] GPIO port I clock enable
    uint8_t res1_9_11 : 3;      // [9:11] Reserved
    uint8_t CRCEN : 1;          // [12] CRC clock enable
    uint8_t res1_13_15 : 3;     // [13:15] Reserved

    // Byte 2 (bits 16–23)
    uint8_t BKPSRAMEN : 1;      // [16] BKPSRAM clock enable
    uint8_t res2_17 : 1;        // [17] Reserved
    uint8_t TCMSRAMEN : 1;      // [18] TCMSRAM clock enable
    uint8_t DMA0EN : 1;         // [19] DMA0 clock enable
    uint8_t DMA1EN : 1;         // [20] DMA1 clock enable
    uint8_t IPAEN : 1;          // [21] IPA clock enable
    uint8_t res2_22 : 1;        // [22] Reserved
    uint8_t ENETEN : 1;         // [23] Ethernet clock enable

    // Byte 3 (bits 24–31)
    uint8_t ENETTXEN : 1;       // [24] Ethernet TX clock enable
    uint8_t ENETRXEN : 1;       // [25] Ethernet RX clock enable
    uint8_t ENETPTPEN : 1;      // [26] Ethernet PTP clock enable
    uint8_t USBHSEN : 1;        // [27] USBHS clock enable
    uint8_t USBHSULPIEN : 1;    // [28] USBHS ULPI clock enable
    uint8_t res3_29_31 : 3;     // [29:31] Reserved
  } __attribute__((packed));

  uint32_t value;
  struct AHB1EN_bits bits;
};
  union AHB2EN_register {
    struct AHB2EN_bits {
      uint32_t DCIEN : 1;      // [0] DCI clock enable
      uint32_t reserved1 : 5;  // [1:5] Reserved, must be kept at reset value
      uint32_t TRNGEN : 1;     // [6] TRNG clock enable
      uint32_t USBFSEN : 1;    // [7] USBFS clock enable
      uint32_t reserved2 : 24; // [8:31] Reserved, must be kept at reset value
    } __attribute__((packed));

    uint32_t value;
    struct AHB2EN_bits bits;
  };

  union AHB3EN_register {
    struct AHB3EN_bits {
      uint32_t EXMCEN : 1;    // [0] EXMC clock enable
      uint32_t reserved : 31; // [1:31] Reserved, must be kept at reset value
    } __attribute__((packed));

    uint32_t value;
    struct AHB3EN_bits bits;
  };

  union APB1EN_register {
    struct APB1EN_bits {
      uint32_t TIMER1EN : 1;  // [0] TIMER1 clock enable
      uint32_t TIMER2EN : 1;  // [1] TIMER2 clock enable
      uint32_t TIMER3EN : 1;  // [2] TIMER3 clock enable
      uint32_t TIMER4EN : 1;  // [3] TIMER4 clock enable
      uint32_t TIMER5EN : 1;  // [4] TIMER5 clock enable
      uint32_t TIMER6EN : 1;  // [5] TIMER6 clock enable
      uint32_t TIMER11EN : 1; // [6] TIMER11 clock enable
      uint32_t TIMER12EN : 1; // [7] TIMER12 clock enable
      uint32_t TIMER13EN : 1; // [8] TIMER13 clock enable
      uint32_t reserved1 : 2; // [9:10] Reserved
      uint32_t WWDGTEN : 1;   // [11] WWDGT clock enable
      uint32_t reserved2 : 2; // [12:13] Reserved
      uint32_t SPI1EN : 1;    // [14] SPI1 clock enable
      uint32_t SPI2EN : 1;    // [15] SPI2 clock enable
      uint32_t reserved3 : 1; // [16] Reserved
      uint32_t USART1EN : 1;  // [17] USART1 clock enable
      uint32_t USART2EN : 1;  // [18] USART2 clock enable
      uint32_t UART3EN : 1;   // [19] UART3 clock enable
      uint32_t UART4EN : 1;   // [20] UART4 clock enable
      uint32_t I2C0EN : 1;    // [21] I2C0 clock enable
      uint32_t I2C1EN : 1;    // [22] I2C1 clock enable
      uint32_t I2C2EN : 1;    // [23] I2C2 clock enable
      uint32_t reserved4 : 1; // [24] Reserved
      uint32_t CAN0EN : 1;    // [25] CAN0 clock enable
      uint32_t CAN1EN : 1;    // [26] CAN1 clock enable
      uint32_t reserved5 : 1; // [27] Reserved
      uint32_t PMUEN : 1;     // [28] PMU clock enable
      uint32_t DACEN : 1;     // [29] DAC clock enable
      uint32_t UART6EN : 1;   // [30] UART6 clock enable
      uint32_t UART7EN : 1;   // [31] UART7 clock enable
    } __attribute__((packed));

    uint32_t value;
    struct APB1EN_bits bits;
  };

  union APB2EN_register {
    struct APB2EN_bits {
      uint32_t TIMER0EN : 1;  // [0] TIMER0 clock enable
      uint32_t TIMER7EN : 1;  // [1] TIMER7 clock enable
      uint32_t reserved1 : 2; // [2:3] Reserved
      uint32_t USART0EN : 1;  // [4] USART0 clock enable
      uint32_t USART5EN : 1;  // [5] USART5 clock enable
      uint32_t reserved2 : 3; // [6:8] Reserved
      uint32_t ADC0EN : 1;    // [8] ADC0 clock enable
      uint32_t ADC1EN : 1;    // [9] ADC1 clock enable
      uint32_t ADC2EN : 1;    // [10] ADC2 clock enable
      uint32_t SDIOEN : 1;    // [11] SDIO clock enable
      uint32_t SPI0EN : 1;    // [12] SPI0 clock enable
      uint32_t SPI3EN : 1;    // [13] SPI3 clock enable
      uint32_t SYSCFGEN : 1;  // [14] SYSCFG clock enable
      uint32_t reserved3 : 1; // [15] Reserved
      uint32_t TIMER8EN : 1;  // [16] TIMER8 clock enable
      uint32_t TIMER9EN : 1;  // [17] TIMER9 clock enable
      uint32_t TIMER10EN : 1; // [18] TIMER10 clock enable
      uint32_t reserved4 : 1; // [19] Reserved
      uint32_t SPI4EN : 1;    // [20] SPI4 clock enable
      uint32_t SPI5EN : 1;    // [21] SPI5 clock enable
      uint32_t reserved5 : 4; // [22:25] Reserved
      uint32_t TLIEN : 1;     // [26] TLI clock enable
      uint32_t reserved6 : 5; // [27:31] Reserved
    } __attribute__((packed));

    uint32_t value;
    struct APB2EN_bits bits;
  };

  union AHB1SPEN_register {
    struct AHB1SPEN_bits {
      // Byte 0: Bits 0–7
      uint8_t PASPEN : 1; // [0] GPIO port A clock enable when sleep mode
      uint8_t PBSPEN : 1; // [1] GPIO port B clock enable when sleep mode
      uint8_t PCSPEN : 1; // [2] GPIO port C clock enable when sleep mode
      uint8_t PDSPEN : 1; // [3] GPIO port D clock enable when sleep mode
      uint8_t PESPEN : 1; // [4] GPIO port E clock enable when sleep mode
      uint8_t PFSPEN : 1; // [5] GPIO port F clock enable when sleep mode
      uint8_t PGSPEN : 1; // [6] GPIO port G clock enable when sleep mode
      uint8_t PHSPEN : 1; // [7] GPIO port H clock enable when sleep mode

      // Byte 1: Bits 8–15
      uint8_t PISPEN : 1;     // [8] GPIO port I clock enable when sleep mode
      const uint8_t res1 : 3; // [9:11] Reserved
      uint8_t CRCSPEN : 1;    // [12] CRC clock enable when sleep mode
      const uint8_t res2 : 2; // [13:14] Reserved
      uint8_t FMCSPEN : 1;    // [15] FMC clock enable when sleep mode

      // Byte 2: Bits 16–23
      uint8_t SRAM0SPEN : 1;   // [16] SRAM0 clock enable when sleep mode
      uint8_t SRAM1SPEN : 1;   // [17] SRAM1 clock enable when sleep mode
      uint8_t BKPSRAMSPEN : 1; // [18] BKPSRAM clock enable when sleep mode
      uint8_t SRAM2SPEN : 1;   // [19] SRAM2 clock enable when sleep mode
      const uint8_t res3 : 1;  // [20] Reserved
      uint8_t DMA0SPEN : 1;    // [21] DMA0 clock enable when sleep mode
      uint8_t DMA1SPEN : 1;    // [22] DMA1 clock enable when sleep mode
      uint8_t IPASPEN : 1;     // [23] IPA clock enable when sleep mode

      // Byte 3: Bits 24–31
      const uint8_t res4 : 1;  // [24] Reserved
      uint8_t ENETSPEN : 1;    // [25] Ethernet clock enable when sleep mode
      uint8_t ENETTXSPEN : 1;  // [26] Ethernet TX clock enable when sleep mode
      uint8_t ENETRXSPEN : 1;  // [27] Ethernet RX clock enable when sleep mode
      uint8_t ENETPTPSPEN : 1; // [28] Ethernet PTP clock enable when sleep mode
      uint8_t USBHSSPEN : 1;   // [29] USBHS clock enable when sleep mode
      uint8_t USBHSULPISPEN : 1; // [30] USBHS ULPI clock enable when sleep mode
      const uint8_t res5 : 1;    // [31] Reserved
    } __attribute__((packed));

    uint32_t value;
    struct AHB1SPEN_bits bits;
  };
  union AHB2SPEN_register {
    struct AHB2SPEN_bits {
      // Byte 0: Bits 0–7
      uint8_t DCISPEN : 1;    // [0] DCI clock enable when sleep mode
      const uint8_t res1 : 5; // [1:5] Reserved
      uint8_t TRNGSPEN : 1;   // [6] TRNG clock enable when sleep mode
      uint8_t USBFSSPEN : 1;  // [7] USBFS clock enable when sleep mode

      // Byte 1: Bits 8–15
      const uint8_t res2; // [8:15] Reserved

      // Byte 2: Bits 16–23
      const uint8_t res3; // [16:23] Reserved

      // Byte 3: Bits 24–31
      const uint8_t res4; // [24:31] Reserved
    } __attribute__((packed));

    uint32_t value;
    struct AHB2SPEN_bits bits;
  };

  union AHB3SPEN_register {
    struct AHB3SPEN_bits {
      // Byte 0: Bits 0–7
      uint8_t EXMCSPEN : 1;   // [0] EXMC clock enable when sleep mode
      const uint8_t res1 : 7; // [1:7] Reserved

      // Byte 1: Bits 8–15
      const uint8_t res2; // [8:15] Reserved

      // Byte 2: Bits 16–23
      const uint8_t res3; // [16:23] Reserved

      // Byte 3: Bits 24–31
      const uint8_t res4; // [24:31] Reserved
    } __attribute__((packed));

    uint32_t value;
    struct AHB3SPEN_bits bits;
  };

  union APB1SPEN_register {
    struct APB1SPEN_bits {
      // Byte 0: Bits 0–7
      uint8_t TIMER1SPEN : 1;  // [0]
      uint8_t TIMER2SPEN : 1;  // [1]
      uint8_t TIMER3SPEN : 1;  // [2]
      uint8_t TIMER4SPEN : 1;  // [3]
      uint8_t TIMER5SPEN : 1;  // [4]
      uint8_t TIMER6SPEN : 1;  // [5]
      uint8_t TIMER11SPEN : 1; // [6]
      uint8_t TIMER12SPEN : 1; // [7]

      // Byte 1: Bits 8–15
      uint8_t TIMER13SPEN : 1;     // [8]
      const uint8_t reserved1 : 2; // [9:10] Reserved
      uint8_t WWDGTSPEN : 1;       // [11]
      const uint8_t reserved2 : 2; // [12:13] Reserved
      uint8_t SPI1SPEN : 1;        // [14]
      uint8_t SPI2SPEN : 1;        // [15]

      // Byte 2: Bits 16–23
      const uint8_t reserved3 : 1; // [16] Reserved
      uint8_t USART1SPEN : 1;      // [17]
      uint8_t USART2SPEN : 1;      // [18]
      uint8_t UART3SPEN : 1;       // [19]
      uint8_t UART4SPEN : 1;       // [20]
      uint8_t I2C0SPEN : 1;        // [21]
      uint8_t I2C1SPEN : 1;        // [22]
      uint8_t I2C2SPEN : 1;        // [23]

      // Byte 3: Bits 24–31
      const uint8_t reserved4 : 1; // [24] Reserved
      uint8_t CAN0SPEN : 1;        // [25]
      uint8_t CAN1SPEN : 1;        // [26]
      const uint8_t reserved5 : 1; // [27] Reserved
      uint8_t PMUSPEN : 1;         // [28]
      uint8_t DACSPEN : 1;         // [29]
      uint8_t UART6SPEN : 1;       // [30]
      uint8_t UART7SPEN : 1;       // [31]
    } __attribute__((packed));

    uint32_t value;
    struct APB1SPEN_bits bits;
  };

  union APB2SPEN_register {
    struct APB2SPEN_bits {
      // Byte 0: Bits 0–7
      uint8_t TIMER0SPEN : 1;      // [0]
      uint8_t TIMER7SPEN : 1;      // [1]
      const uint8_t Reserved0 : 2; // [2:3]
      uint8_t USART0SPEN : 1;      // [4]
      uint8_t USART5SPEN : 1;      // [5]
      const uint8_t Reserved1 : 2; // [6:7]

      // Byte 1: Bits 8–15
      uint8_t ADC0SPEN : 1;        // [8]
      uint8_t ADC1SPEN : 1;        // [9]
      uint8_t ADC2SPEN : 1;        // [10]
      uint8_t SDIOSPEN : 1;        // [11]
      uint8_t SPI0SPEN : 1;        // [12]
      uint8_t SPI3SPEN : 1;        // [13]
      uint8_t SYSCFGSPEN : 1;      // [14]
      const uint8_t Reserved2 : 1; // [15]

      // Byte 2: Bits 16–23
      uint8_t TIMER8SPEN : 1;      // [16]
      uint8_t TIMER9SPEN : 1;      // [17]
      uint8_t TIMER10SPEN : 1;     // [18]
      const uint8_t Reserved3 : 1; // [19]
      uint8_t SPI4SPEN : 1;        // [20]
      uint8_t SPI5SPEN : 1;        // [21]
      const uint8_t Reserved4 : 2; // [22:23]

      // Byte 3: Bits 24–31
      const uint8_t Reserved5 : 1; // [24]
      const uint8_t Reserved6 : 1; // [25]
      const uint8_t Reserved7 : 1; // [26]
      uint8_t TLISPEN : 1;         // [27]
      const uint8_t Reserved8 : 4; // [28:31]
    } __attribute__((packed));

    uint32_t value;
    struct APB2SPEN_bits bits;
  };

  union BDCTL_register {
    struct BDCTL_bits {
      uint8_t LXTALEN : 1;        // Bit 0: LXTAL enable
      const uint8_t LXTALSTB : 1; // Bit 1: LXTAL stabilization flag (read-only)
      uint8_t LXTALBPS : 1;       // Bit 2: LXTAL bypass mode enable
      uint8_t LXTALDRI : 1;       // Bit 3: LXTAL drive capability
      const uint8_t Reserved4_7 : 4;
      uint8_t RTCSRC : 2; // Bits 8–9: RTC clock source selection
      const uint8_t Reserved10_14 : 5;
      uint8_t RTCEN : 1; // Bit 15: RTC clock enable
      uint8_t BKPRST : 1; // Bit 16: Backup domain reset
      const uint16_t Reserved17_31 : 15;

    } __attribute__((packed));

    uint32_t value;
    struct BDCTL_bits bits;
  };
  union RSTSCK_register {
    struct RSTSCK_bits {
      uint8_t IRC32KEN : 1; // Bit 0: IRC32K enable
      const uint8_t IRC32KSTB : 1; // Bit 1: IRC32K stabilization flag (read-only)
      const uint8_t Reserved2_7 : 6;

      const uint8_t Reserved8_15; // Bits 8–15: Reserved

      uint8_t RSTFC : 1;           // Bit 24: Reset flag clear
      const uint8_t BORRSTF : 1;   // Bit 25: BOR reset flag
      const uint8_t EPRSTF : 1;    // Bit 26: External PIN reset flag
      const uint8_t PORRSTF : 1;   // Bit 27: Power reset flag
      const uint8_t SWRSTF : 1;    // Bit 28: Software reset flag
      const uint8_t FWDGTRSTF : 1; // Bit 29: Free watchdog reset flag
      const uint8_t WWDGTRSTF : 1; // Bit 30: Window watchdog reset flag
      const uint8_t LPRSTF : 1;    // Bit 31: Low-power reset flag
    } __attribute__((packed));

    uint32_t value;
    struct RSTSCK_bits bits;
  };
  union PLLSSCTL_register {
    struct PLLSSCTL_bits {
      uint16_t MODCNT : 13;    // Bits 0-12: MODCNT[12:0] - PLL spread spectrum
                               // modulation profile
      uint8_t MODSTEP_low : 3; // Bits 13-15: MODSTEP[2:0] - Low bits of MODSTEP
      uint16_t MODSTEP_high : 12; // Bits 16-27: MODSTEP[14:3] - High bits of MODSTEP
      uint8_t Reserved_28_29 : 2; // Bits 28-29: Reserved, must be kept at reset
                                  // value
      uint8_t SS_TYPE : 1; // Bit 30: PLL spread spectrum modulation type select
                           // 0: Center spread, 1: Down spread
      uint8_t SSCGON : 1; // Bit 31: PLL spread spectrum modulation enable
                          // 0: Disable, 1: Enable
    } __attribute__((packed));

    uint32_t value;
    struct PLLSSCTL_bits bits;
  };

  union PLLI2S_register {
    struct PLLI2S_bits {
      uint32_t RESERVED31 : 1;     // Bit 31: Reserved, must keep reset value
      uint32_t PLLI2SR : 3;        // Bits 30:28 PLLI2SR[2:0] - PLLI2S R output
                                   // division factor
      uint32_t RESERVED27_15 : 13; // Bits 27:15 Reserved, must keep reset value
      uint32_t PLLI2SN : 9;        // Bits 14:6 PLLI2SN[8:0] - PLLI2S VCO
                                   // multiplication factor
      uint32_t RESERVED5_0 : 6;    // Bits 5:0 Reserved, must keep reset value
    } __attribute__((packed));
    uint32_t value;
    struct PLLI2S_bits bits;
  };

  union PLLSAI_register {
    struct PLLSAI_bits {
      uint32_t RESERVED31 : 1;     // Bit 31: Reserved, must keep reset value
      uint32_t PLLSAIR : 3;        // Bits 30:28 PLLSAIR[2:0] - PLLSAI R output
                                   // division factor
      uint32_t RESERVED27_18 : 10; // Bits 27:18 Reserved, must keep reset value
      uint32_t PLLSAIP : 2;        // Bits 17:16 PLLSAIP[1:0] - PLLSAI P output
                                   // division factor
      uint32_t RESERVED15 : 1;     // Bit 15: Reserved, must keep reset value
      uint32_t PLLSAIN : 9;        // Bits 14:6 PLLSAIN[8:0] - PLLSAI VCO
                                   // multiplication factor
      uint32_t RESERVED5_0 : 6;    // Bits 5:0 Reserved, must keep reset value
    } __attribute__((packed));
    uint32_t value;
    struct PLLSAI_bits bits;
  };
  /* CFG1 - Clock configuration register 1 */
  union CFG1_register {
    struct CFG1_bits {
      uint32_t RESERVED31_25 : 7; // Bits 31:25 Reserved, keep reset value
      uint32_t TIMERSEL : 1;      // Bit 24 TIMER clock selection
      uint32_t RESERVED23_18 : 6; // Bits 23:18 Reserved
      uint32_t PLLSAIRDIV : 2;    // Bits 17:16 PLLSAIR divider factor
      uint32_t RESERVED15_0 : 16; // Bits 15:0 Reserved
    } __attribute__((packed));
    uint32_t value;
    struct CFG1_bits bits;
  };

  /* ADDCTL - Additional clock control register */
  union ADDCTL_register {
    struct ADDCTL_bits {
      uint32_t IRC48MCALIB : 8;   // Bits 31:24 IRC48M calibration value
      uint32_t RESERVED23_18 : 6; // Bits 23:18 Reserved
      uint32_t IRC48MSTB : 1; // Bit 17 IRC48M stabilization flag (read-only)
      uint32_t IRC48MEN : 1;  // Bit 16 IRC48M oscillator enable
      uint32_t RESERVED15_2 : 14; // Bits 15:2 Reserved
      uint32_t PLL48MSEL : 1;     // Bit 1 PLL48M clock selection
      uint32_t CK48MSEL : 1;      // Bit 0 48MHz clock selection
    } __attribute__((packed));
    uint32_t value;
    struct ADDCTL_bits bits;
  };

  /* ADDINT - Additional clock interrupt register */
  union ADDINT_register {
    struct ADDINT_bits {
      uint32_t RESERVED31_23 : 9; // Bits 31:23 Reserved
      uint32_t IRC48MSTBIC : 1;   // Bit 22 IRC48M stabilization interrupt clear
                                  // (write 1 to clear)
      uint32_t RESERVED21_15 : 7; // Bits 21:15 Reserved
      uint32_t IRC48MSTBIE : 1;  // Bit 14 IRC48M stabilization interrupt enable
      uint32_t RESERVED13_7 : 7; // Bits 13:7 Reserved
      uint32_t IRC48MSTBIF : 1;  // Bit 6 IRC48M stabilization interrupt flag
                                 // (read-only)
      uint32_t RESERVED5_0 : 6;  // Bits 5:0 Reserved
    } __attribute__((packed));
    uint32_t value;
    struct ADDINT_bits bits;
  };

  /* ADDAPB1RST - APB1 additional reset register */
  union ADDAPB1RST_register {
    struct ADDAPB1RST_bits {
      uint32_t IREFRST : 1;       // Bit 31 IREF reset
      uint32_t RESERVED30_28 : 3; // Bits 30:28 Reserved
      uint32_t CTCRST : 1;        // Bit 27 CTC reset
      uint32_t RESERVED26_0 : 27; // Bits 26:0 Reserved
    } __attribute__((packed));
    uint32_t value;
    struct ADDAPB1RST_bits bits;
  };

  /* ADDAPB1EN - APB1 additional enable register */
  union ADDAPB1EN_register {
    struct ADDAPB1EN_bits {
      uint32_t IREFEN : 1;        // Bit 31 IREF interface clock enable
      uint32_t RESERVED30_28 : 3; // Bits 30:28 Reserved
      uint32_t CTCEN : 1;         // Bit 27 CTC clock enable
      uint32_t RESERVED26_0 : 27; // Bits 26:0 Reserved
    } __attribute__((packed));
    uint32_t value;
    struct ADDAPB1EN_bits bits;
  };

  /* ADDAPB1SPEN - APB1 additional sleep mode enable register */
  union ADDAPB1SPEN_register {
    struct ADDAPB1SPEN_bits {
      uint32_t IREFSPEN : 1;      // Bit 31 IREF clock enable during sleep mode
      uint32_t RESERVED30_28 : 3; // Bits 30:28 Reserved
      uint32_t CTCSPEN : 1;       // Bit 27 CTC clock enable during sleep mode
      uint32_t RESERVED26_0 : 27; // Bits 26:0 Reserved
    } __attribute__((packed));
    uint32_t value;
    struct ADDAPB1SPEN_bits bits;
  };

  /* VKEY - Voltage key register */
  union VKEY_register {
    struct VKEY_bits {
      uint32_t KEY : 32; // Bits 31:0 Key for DSV register unlock (write only,
                         // read as 0)
    } __attribute__((packed));
    uint32_t value;
    struct VKEY_bits bits;
  };

  /* DSV - Deep-sleep mode voltage register */
  union DSV_register {
    struct DSV_bits {
      uint32_t RESERVED31_3 : 29; // Bits 31:3 Reserved
      uint32_t DSLPVS : 3;        // Bits 2:0 Deep-sleep mode voltage select
    } __attribute__((packed));
    uint32_t value;
    struct DSV_bits bits;
  };

  volatile union CTL_register CTL;           // 0x00
  volatile union PLL_register PLL;           // 0x04
  volatile union CFG0_register CFG0;         // 0x08
  volatile union INT_register INT;           // 0x0C
  volatile union AHB1RST_register AHB1RST;   // 0x10
  volatile union AHB2RST_register AHB2RST;   // 0x14
  volatile union AHB3RST_register AHB3RST;   // 0x18
  volatile uint32_t Reserved1[1];             // 0x1C
  volatile union APB1RST_register APB1RST;   // 0x20
  volatile union APB2RST_register APB2RST;   // 0x24
  volatile uint32_t Reserved2[2];             // 0x28, 0x2C
  volatile union AHB1EN_register AHB1EN;     // 0x30
  volatile union AHB2EN_register AHB2EN;     // 0x34
  volatile union AHB3EN_register AHB3EN;     // 0x38
  volatile uint32_t Reserved3[1];             // 0x3C
  volatile union APB1EN_register APB1EN;     // 0x40
  volatile union APB2EN_register APB2EN;     // 0x44
  volatile uint32_t Reserved4[2];             // 0x48, 0x4C
  volatile union AHB1SPEN_register AHB1SPEN; // 0x50
  volatile union AHB2SPEN_register AHB2SPEN; // 0x54
  volatile union AHB3SPEN_register AHB3SPEN; // 0x58
  volatile uint32_t Reserved5[1];             // 0x5C
  volatile union APB1SPEN_register APB1SPEN; // 0x60
  volatile union APB2SPEN_register APB2SPEN; // 0x64
  volatile uint32_t Reserved6[2];             // 0x68, 0x6C
  volatile union BDCTL_register BDCTL;       // 0x70
  volatile union RSTSCK_register RSTSCK;     // 0x74
  volatile uint32_t Reserved7[2];             // 0x78, 0x7C
  volatile union PLLSSCTL_register PLLSSCTL; // 0x80
  volatile union PLLI2S_register PLLI2S;     // 0x84
  volatile union PLLSAI_register PLLSAI;     // 0x88
  volatile union CFG1_register CFG1;         // 0x8C
  volatile uint32_t Reserved8[12];            // 0x90 - 0xBC
  volatile union ADDCTL_register ADDCTL;     // 0xC0
  volatile uint32_t Reserved9[2];             // 0xC4, 0xC8
  volatile union ADDINT_register ADDINT;     // 0xCC
  volatile uint32_t Reserved10[4];            // 0xD0 - 0xDC
  volatile union ADDAPB1RST_register ADDAPB1RST;   // 0xE0
  volatile union ADDAPB1EN_register ADDAPB1EN;     // 0xE4
  volatile union ADDAPB1SPEN_register ADDAPB1SPEN; // 0xE8
  volatile uint32_t Reserved11[5];            // 0xEC - 0xFC
  volatile union VKEY_register VKEY;          // 0x100
  volatile uint32_t Reserved12[12];           // 0x104 - 0x130
  volatile union DSV_register DSV;            // 0x134
};

static_assert(std::is_standard_layout<Rcu>::value, "Rcu class is NOT standard layout");

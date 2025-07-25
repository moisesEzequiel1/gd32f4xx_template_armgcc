#pragma once
#include <stdint.h>
#include <type_traits>
class Pmu {

public:
  enum class LowDriverEnable : uint8_t {
    DISABLE = 0b00, // disable low-driver mode in Deep-sleep mode
    RESERVED_01 = 0b01,
    RESERVED_10 = 0b10,
    ENABLE = 0b11 // enable low-driver mode in Deep-sleep mode
  };

  enum class LdoOutputVoltageSelect : uint8_t {
    LOW_MODE = 0b00, // reserved but means low mode
    LOW = 0b01,      // LDO output voltage low mode
    MID = 0b10,      // LDO output voltage mid mode
    HIGH = 0b11      // LDO output voltage high mode
  };

  enum class LowVoltageDetectorThreshold : uint8_t {
    VOLT_2_1V = 0b000,
    VOLT_2_3V = 0b001,
    VOLT_2_4V = 0b010,
    VOLT_2_6V = 0b011,
    VOLT_2_7V = 0b100,
    VOLT_2_9V = 0b101,
    VOLT_3_0V = 0b110,
    VOLT_3_1V = 0b111
  };

  enum class StandbyMode : uint8_t { DEEPSLEEP = 0, STANDBY = 1 };

  enum class LowDriverReadyFlag : uint8_t {
    NORMAL_DRIVER = 0b00,
    RESERVED_01 = 0b01,
    RESERVED_10 = 0b10,
    LOW_DRIVER = 0b11
  };

  enum class HighDriverSwitchReadyFlag : uint8_t { NOT_READY = 0, READY = 1 };

  enum class HighDriverReadyFlag : uint8_t { NOT_READY = 0, READY = 1 };

  enum class LdoVoltageSelectReadyFlag : uint8_t { NOT_READY = 0, READY = 1 };

  enum class BackupSramLdoOn : uint8_t { CLOSED = 0, OPEN = 1 };

  enum class WakeupPinEnable : uint8_t { DISABLE = 0, ENABLE = 1 };

  enum class BackupSramLdoReadyFlag : uint8_t { NOT_READY = 0, READY = 1 };

  enum class LowVoltageDetectorStatusFlag : uint8_t {
    NO_EVENT = 0,
    EVENT_OCCURRED = 1
  };

  enum class StandbyFlag : uint8_t { NOT_ENTERED = 0, ENTERED = 1 };

  enum class WakeupFlag : uint8_t { NO_WAKEUP = 0, WAKEUP_OCCURRED = 1 };

  void EnableHighDriverMode();
  void SetHighDriverMode();

private:
  union CTL_register {
    struct CTL_bits {
      uint32_t LDOLP : 1;                   // bit 0
      StandbyMode STBMOD : 1;               // bit 1
      uint32_t WURST : 1;                   // bit 2
      uint32_t STBRST : 1;                  // bit 3
      uint32_t LVDEN : 1;                   // bit 4
      LowVoltageDetectorThreshold LVDT : 3; // bits 5-7
      uint32_t BKPWEN : 1;                  // bit 8
      uint32_t res9 : 1;                    // bit 9 reserved
      uint32_t LDLP : 1;                    // bit 10
      uint32_t LDNP : 1;        // bit 11 Low-driver mode normal power LDO (from
                                // description)
      uint32_t res12_15 : 4;    // bits 12-15 reserved
      uint32_t HDEN : 1;        // bit 16 High-driver mode enable
      uint32_t HDS : 1;         // bit 17 High-driver mode switch
      LowDriverEnable LDEN : 2; // bits 18-19 Enable low-driver mode in
                                // Deep-sleep mode (LDEN[1:0])
      uint32_t res20_31 : 12;   // bits 20-31 reserved
    } __attribute__((packed));
    uint32_t value;
    struct CTL_bits bits;
  };
  union CS_register {
    struct CS_bits {
      WakeupFlag WUF : 1;                    // bit 0
      StandbyFlag STBF : 1;                  // bit 1
      LowVoltageDetectorStatusFlag LVDF : 1; // bit 2
      BackupSramLdoReadyFlag BLDORF : 1;     // bit 3
      uint8_t res4_7 : 4;                    // bits 4-7 reserved
      WakeupPinEnable WUPEN : 1;             // bit 8
      BackupSramLdoOn BLDOON : 1;            // bit 9
      uint8_t res10_13 : 4;                  // bits 10-13 reserved
      LdoVoltageSelectReadyFlag LDOVSRF : 1; // bit 14
      uint8_t res15 : 1;                     // bit 15 reserved
      HighDriverReadyFlag HDRF : 1;          // bit 16
      HighDriverSwitchReadyFlag HDSRF : 1;   // bit 17
      LowDriverReadyFlag LDRF : 2;           // bits 18-19
      uint16_t res20_31 : 12;                // bits 20-31 reserved
    } __attribute__((packed));
    uint32_t value;
    struct CS_bits bits;
  };

  volatile union CTL_register CTL;
  volatile union CS_register CS;
};

#pragma once

#include <stdint.h>
#include <type_traits>
class Dma {

public:
  // =============================
  // Enumeraciones
  // =============================
  enum class Channel : uint8_t { CH0 = 0, CH1, CH2, CH3, CH4, CH5, CH6, CH7 };

  enum class Direction : uint8_t {
    PeripheralToMemory,
    MemoryToPeripheral,
    MemoryToMemory
  };

  enum class Priority : uint8_t { Low, Medium, High, VeryHigh };

  enum class TransferWidth : uint8_t { Bit8 = 0b00, Bit16 = 0b01, Bit32 = 0b10 };
  enum class DataSize : uint8_t { Byte, HalfWord, Word };

  enum class InterruptFlag : uint8_t {
    SingleData,
    TransferComplete,
    HalfTransfer,
    TransferError,
    All
  };

  // =============================
  // Métodos públicos
  // =============================

  // Control de canal
  void enableChannel(Channel ch);
  void disableChannel(Channel ch);
  bool isChannelEnabled(Channel ch) const;

  // Configuración básica
  void setPeripheralAddress(Channel ch, uint32_t addr);
  void setMemoryAddress(Channel ch, uint32_t addr, bool useAlt = false);
  void setTransferCount(Channel ch, uint16_t count);
  void setTransferWidth(Channel ch, TransferWidth width); 

  void setPriority(Channel ch, Priority prio);
  void setDataSize(Channel ch, DataSize periphSize, DataSize memSize);
  void setDirection(Channel ch, Direction dir);
  void enableCircularMode(Channel ch, bool enable);

  // FIFO
  void configureFifo(Channel ch, uint8_t threshold, bool multiDataMode);

  // Interrupciones
  void enableInterrupt(Channel ch, InterruptFlag flag);
  void disableInterrupt(Channel ch, InterruptFlag flag);
  bool getInterruptFlag(Channel ch, InterruptFlag flag) const;
  void clearInterruptFlag(Channel ch, InterruptFlag flag);

  // Transferencia rápida (helper)
  void startTransfer(Channel ch, uint32_t periphAddr, uint32_t memAddr,
                     uint16_t count, Direction dir, Priority prio);

private:
  union INTF0_register {
    struct INTF0_bits {
      uint32_t FEEIF0 : 1;         // FIFO error and exception flag of channel 0
      const uint32_t res1 : 1;     // Reserved, must be kept at reset value
      uint32_t SDEIF0 : 1;         // Single data mode exception of channel 0
      uint32_t TAEIF0 : 1;         // Transfer access error flag of channel 0
      uint32_t HTFIF0 : 1;         // Half transfer finish flag of channel 0
      uint32_t FTFIF0 : 1;         // Full transfer finish flag of channel 0
      uint32_t FEEIF1 : 1;         // FIFO error and exception flag of channel 1
      const uint32_t res7 : 1;     // Reserved, must be kept at reset value
      uint32_t SDEIF1 : 1;         // Single data mode exception of channel 1
      uint32_t TAEIF1 : 1;         // Transfer access error flag of channel 1
      uint32_t HTFIF1 : 1;         // Half transfer finish flag of channel 1
      uint32_t FTFIF1 : 1;         // Full transfer finish flag of channel 1
      const uint32_t res12_15 : 4; // Reserved, must be kept at reset value
      uint32_t FEEIF2 : 1;         // FIFO error and exception flag of channel 2
      const uint32_t res17 : 1;    // Reserved, must be kept at reset value
      uint32_t SDEIF2 : 1;         // Single data mode exception of channel 2
      uint32_t TAEIF2 : 1;         // Transfer access error flag of channel 2
      uint32_t HTFIF2 : 1;         // Half transfer finish flag of channel 2
      uint32_t FTFIF2 : 1;         // Full transfer finish flag of channel 2
      uint32_t FEEIF3 : 1;         // FIFO error and exception flag of channel 3
      const uint32_t res23 : 1;    // Reserved, must be kept at reset value
      uint32_t SDEIF3 : 1;         // Single data mode exception of channel 3
      uint32_t TAEIF3 : 1;         // Transfer access error flag of channel 3
      uint32_t HTFIF3 : 1;         // Half transfer finish flag of channel 3
      uint32_t FTFIF3 : 1;         // Full transfer finish flag of channel 3
      const uint32_t res28_31 : 4; // Reserved, must be kept at reset value
    } __attribute__((packed));
    uint32_t value;         // Acceso completo de 32 bits al registro
    struct INTF0_bits bits; // Acceso por campos individuales
  };
  union INTF1_register {
    struct INTF1_bits {
      uint32_t FEEIF4 : 1;         // FIFO error and exception flag of channel 4
      const uint32_t res1 : 1;     // Reserved, must be kept at reset value
      uint32_t SDEIF4 : 1;         // Single data mode exception of channel 4
      uint32_t TAEIF4 : 1;         // Transfer access error flag of channel 4
      uint32_t HTFIF4 : 1;         // Half transfer finish flag of channel 4
      uint32_t FTFIF4 : 1;         // Full transfer finish flag of channel 4
      uint32_t FEEIF5 : 1;         // FIFO error and exception flag of channel 5
      const uint32_t res7 : 1;     // Reserved, must be kept at reset value
      uint32_t SDEIF5 : 1;         // Single data mode exception of channel 5
      uint32_t TAEIF5 : 1;         // Transfer access error flag of channel 5
      uint32_t HTFIF5 : 1;         // Half transfer finish flag of channel 5
      uint32_t FTFIF5 : 1;         // Full transfer finish flag of channel 5
      const uint32_t res12_15 : 4; // Reserved, must be kept at reset value
      uint32_t FEEIF6 : 1;         // FIFO error and exception flag of channel 6
      const uint32_t res17 : 1;    // Reserved, must be kept at reset value
      uint32_t SDEIF6 : 1;         // Single data mode exception of channel 6
      uint32_t TAEIF6 : 1;         // Transfer access error flag of channel 6
      uint32_t HTFIF6 : 1;         // Half transfer finish flag of channel 6
      uint32_t FTFIF6 : 1;         // Full transfer finish flag of channel 6
      uint32_t FEEIF7 : 1;         // FIFO error and exception flag of channel 7
      const uint32_t res23 : 1;    // Reserved, must be kept at reset value
      uint32_t SDEIF7 : 1;         // Single data mode exception of channel 7
      uint32_t TAEIF7 : 1;         // Transfer access error flag of channel 7
      uint32_t HTFIF7 : 1;         // Half transfer finish flag of channel 7
      uint32_t FTFIF7 : 1;         // Full transfer finish flag of channel 7
      const uint32_t res28_31 : 4; // Reserved, must be kept at reset value
    } __attribute__((packed));
    uint32_t value;         // Acceso completo de 32 bits al registro
    struct INTF1_bits bits; // Acceso por campos individuales
  };
  union INTC0_register {
    struct INTC0_bits {
      uint32_t FEEIFC0 : 1; // Clear FIFO error and exception flag of channel 0
      const uint32_t res1 : 1; // Reserved, must be kept at reset value
      uint32_t SDEIFC0 : 1; // Clear single data mode exception flag of channel 0
      uint32_t TAEIFC0 : 1; // Clear transfer access error flag of channel 0
      uint32_t HTFIFC0 : 1; // Clear half transfer finish flag of channel 0
      uint32_t FTFIFC0 : 1; // Clear full transfer finish flag of channel 0
      uint32_t FEEIFC1 : 1; // Clear FIFO error and exception flag of channel 1
      const uint32_t res7 : 1; // Reserved, must be kept at reset value
      uint32_t SDEIFC1 : 1; // Clear single data mode exception flag of channel 1
      uint32_t TAEIFC1 : 1; // Clear transfer access error flag of channel 1
      uint32_t HTFIFC1 : 1; // Clear half transfer finish flag of channel 1
      uint32_t FTFIFC1 : 1; // Clear full transfer finish flag of channel 1
      uint32_t FEEIFC2 : 1; // Clear FIFO error and exception flag of channel 2
      const uint32_t res13 : 1; // Reserved, must be kept at reset value
      uint32_t SDEIFC2 : 1; // Clear single data mode exception flag of channel 2
      uint32_t TAEIFC2 : 1; // Clear transfer access error flag of channel 2
      uint32_t HTFIFC2 : 1; // Clear half transfer finish flag of channel 2
      uint32_t FTFIFC2 : 1; // Clear full transfer finish flag of channel 2
      uint32_t FEEIFC3 : 1; // Clear FIFO error and exception flag of channel 3
      const uint32_t res19 : 1; // Reserved, must be kept at reset value
      uint32_t SDEIFC3 : 1; // Clear single data mode exception flag of channel 3
      uint32_t TAEIFC3 : 1; // Clear transfer access error flag of channel 3
      uint32_t HTFIFC3 : 1; // Clear half transfer finish flag of channel 3
      uint32_t FTFIFC3 : 1; // Clear full transfer finish flag of channel 3
      const uint32_t res28_31 : 4; // Reserved, must be kept at reset value
    } __attribute__((packed));

    uint32_t value;         // Acceso completo de 32 bits al registro
    struct INTC0_bits bits; // Acceso por campos individuales
  };
  union INTC1_register {
    struct INTC1_bits {
      uint32_t FEEIFC4 : 1; // Clear FIFO error and exception flag of channel 4
      const uint32_t res1 : 1; // Reserved
      uint32_t SDEIFC4 : 1; // Clear single data mode exception flag of channel 4
      uint32_t TAEIFC4 : 1; // Clear transfer access error flag of channel 4
      uint32_t HTFIFC4 : 1; // Clear half transfer finish flag of channel 4
      uint32_t FTFIFC4 : 1; // Clear full transfer finish flag of channel 4
      uint32_t FEEIFC5 : 1; // Clear FIFO error and exception flag of channel 5
      const uint32_t res7 : 1; // Reserved
      uint32_t SDEIFC5 : 1; // Clear single data mode exception flag of channel 5
      uint32_t TAEIFC5 : 1; // Clear transfer access error flag of channel 5
      uint32_t HTFIFC5 : 1; // Clear half transfer finish flag of channel 5
      uint32_t FTFIFC5 : 1; // Clear full transfer finish flag of channel 5
      uint32_t FEEIFC6 : 1; // Clear FIFO error and exception flag of channel 6
      const uint32_t res13 : 1; // Reserved
      uint32_t SDEIFC6 : 1; // Clear single data mode exception flag of channel 6
      uint32_t TAEIFC6 : 1; // Clear transfer access error flag of channel 6
      uint32_t HTFIFC6 : 1; // Clear half transfer finish flag of channel 6
      uint32_t FTFIFC6 : 1; // Clear full transfer finish flag of channel 6
      uint32_t FEEIFC7 : 1; // Clear FIFO error and exception flag of channel 7
      const uint32_t res19 : 1; // Reserved
      uint32_t SDEIFC7 : 1; // Clear single data mode exception flag of channel 7
      uint32_t TAEIFC7 : 1; // Clear transfer access error flag of channel 7
      uint32_t HTFIFC7 : 1; // Clear half transfer finish flag of channel 7
      uint32_t FTFIFC7 : 1; // Clear full transfer finish flag of channel 7
      const uint32_t res28_31 : 4; // Reserved
    } __attribute__((packed));

    uint32_t value;          // Acceso completo de 32 bits al registro
    struct INTC1_bits bits; // Acceso por campos individuales
  };
  union CHxCTL_register {
    struct CHxCTL_bits {
      uint32_t CHEN : 1;   // Channel enable
      uint32_t SDEIE : 1;  // Single data mode exception interrupt enable
      uint32_t TAEIE : 1;  // Transfer access error interrupt enable
      uint32_t HTFIE : 1;  // Half transfer finish interrupt enable
      uint32_t FTFIE : 1;  // Full transfer finish interrupt enable
      uint32_t TFCS : 1;   // Transfer flow controller select
      uint32_t TM : 2;     // Transfer mode
      uint32_t CMEN : 1;   // Circular mode enable
      uint32_t PNAGA : 1;  // Next address generation algorithm of peripheral
      uint32_t MNAGA : 1;  // Next address generation algorithm of memory
      TransferWidth PWIDTH : 2; // Transfer width of peripheral
      TransferWidth MWIDTH : 2; // Transfer width of memory
      uint32_t PAIF : 1;   // Peripheral address increment fixed
      Priority PRIO : 2;   // Priority level
      uint32_t SBMEN : 1;  // Switch-buffer mode enable
      uint32_t MBS : 1;    // Memory buffer select
      const uint32_t reserved20 : 1;    // Reserved
      uint32_t PBURST : 2;              // Transfer burst type of peripheral
      uint32_t MBURST : 2;              // Transfer burst type of memory
      uint32_t PERIEN : 3;              // Peripheral enable
      const uint32_t reserved28_31 : 4; // Reserved
    } __attribute__((packed));

    uint32_t value;              // Acceso completo de 32 bits al registro
    struct CHxCTL_bits bits; // Acceso por campos individuales
  };
  union CHxCNT_register {
    struct CHxCNT_bits {
        uint32_t CNT       : 16;  // Transfer counter
        const uint32_t reserved16_31 : 16; // Reserved
    } __attribute__((packed));

    uint32_t value;               // Acceso completo de 32 bits al registro
    struct CHxCNT_bits bits;  // Acceso por campos individuales
  };
  union CHxPADDR_register {
    struct CHxPADDR_bits {
      uint32_t PADDR_L : 16; // Peripheral base address low 16 bits
      uint32_t PADDR_H : 16; // Peripheral base address high 16 bits
    } __attribute__((packed));
    uint32_t value;            // Acceso completo de 32 bits
    struct CHxPADDR_bits bits; // Acceso por campos
  };
  union CHxM0ADDR_register {
    struct CHxM0ADDR_bits {
      uint32_t M0ADDR_L : 16; // Memory 0 base address low 16 bits
      uint32_t M0ADDR_H : 16; // Memory 0 base address high 16 bits
    } __attribute__((packed));
    uint32_t value;             // Acceso completo de 32 bits
    struct CHxM0ADDR_bits bits; // Acceso por campos
  };
  union CHxM1ADDR_register {
    struct CHxM1ADDR_bits {
        uint32_t M1ADDR_L : 16;   // Memory 1 base address low 16 bits
        uint32_t M1ADDR_H : 16;   // Memory 1 base address high 16 bits
    } __attribute__((packed));
    uint32_t value;               // Acceso completo de 32 bits
    struct CHxM1ADDR_bits bits;   // Acceso por campos
  };
  union CHxFCTL_register {
    struct CHxFCTL_bits {
      uint32_t FCCV : 2;            // FIFO counter critical value
      uint32_t MDMEN : 1;           // Multi-data mode enable
      uint32_t FCNT : 3;            // FIFO counter
      const uint32_t reserved6 : 1; // Reserved
      uint32_t FEEIE : 1;           // Enable FIFO error and exception interrupt
      const uint32_t reserved8_31 : 24; // Reserved, must be kept at reset value
    } __attribute__((packed));

    uint32_t value;           // Acceso completo de 32 bits
    struct CHxFCTL_bits bits; // Acceso por campos individuales
  };
  volatile INTF0_register INTF0; // Interrupt flag register for channels 0-3 offset 0x00
  volatile INTF1_register INTF1; // Interrupt flag register for channels 4-7 offset 0x04
  volatile INTC0_register INTC0; // Interrupt flag clear register for channels 0-3 offset 0x08
  volatile INTC1_register INTC1; // Interrupt flag clear register for channels 4-7 offset 0x0C
  // Channel 0
  volatile CHxCTL_register CH0CTL; // Channel 0 control register offset 0x10
  volatile CHxCNT_register CH0CNT; // Channel 0 counter register offset 0x14
  volatile CHxPADDR_register CH0PADDR; // Channel 0 peripheral address register offset 0x18
  volatile CHxM0ADDR_register CH0M0ADDR; // Channel 0 memory 0 address register offset 0x1C
  volatile CHxM1ADDR_register CH0M1ADDR; // Channel 0 memory 1 address register offset 0x20
  volatile CHxFCTL_register CH0FCTL; // Channel 0 FIFO control register offset 0x24
  // Channel 1
  volatile CHxCTL_register CH1CTL;     // Channel 1 control register offset 0x28
  volatile CHxCNT_register CH1CNT;     // Channel 1 counter register offset 0x2C
  volatile CHxPADDR_register CH1PADDR; // Channel 1 peripheral address register offset 0x30
  volatile CHxM0ADDR_register CH1M0ADDR; // Channel 1 memory 0 address register offset 0x34
  volatile CHxM1ADDR_register CH1M1ADDR; // Channel 1 memory 1 address register offset 0x38
  volatile CHxFCTL_register CH1FCTL;   // Channel 1 FIFO control register offset 0x3C
  // Channel 2
  volatile CHxCTL_register CH2CTL;     // Channel 2 control register offset 0x40
  volatile CHxCNT_register CH2CNT;     // Channel 2 counter register offset 0x44
  volatile CHxPADDR_register CH2PADDR; // Channel 2 peripheral address register offset 0x48
  volatile CHxM0ADDR_register CH2M0ADDR; // Channel 2 memory 0 address register offset 0x4C
  volatile CHxM1ADDR_register CH2M1ADDR; // Channel 2 memory 1 address register offset 0x50
  volatile CHxFCTL_register CH2FCTL;   // Channel 2 FIFO control register offset 0x54
  // Channel 3
  volatile CHxCTL_register CH3CTL;     // Channel 3 control register offset 0x58
  volatile CHxCNT_register CH3CNT;     // Channel 3 counter register offset 0x5C
  volatile CHxPADDR_register CH3PADDR; // Channel 3 peripheral address register offset 0x60
  volatile CHxM0ADDR_register CH3M0ADDR; // Channel 3 memory 0 address register offset 0x64
  volatile CHxM1ADDR_register CH3M1ADDR; // Channel 3 memory 1 address register offset 0x68
  volatile CHxFCTL_register CH3FCTL;   // Channel 3 FIFO control register offset 0x6C
  // Channel 4
  volatile CHxCTL_register CH4CTL;     // Channel 4 control register offset 0x70
  volatile CHxCNT_register CH4CNT;     // Channel 4 counter register offset 0x74
  volatile CHxPADDR_register CH4PADDR; // Channel 4 peripheral address register offset 0x78
  volatile CHxM0ADDR_register CH4M0ADDR; // Channel 4 memory 0 address register offset 0x7C
  volatile CHxM1ADDR_register CH4M1ADDR; // Channel 4 memory 1 address register offset 0x80
  volatile CHxFCTL_register CH4FCTL;   // Channel 4 FIFO control register offset 0x84
  // Channel 5
  volatile CHxCTL_register CH5CTL;     // Channel 5 control register offset 0x88
  volatile CHxCNT_register CH5CNT;     // Channel 5 counter register offset 0x8C
  volatile CHxPADDR_register CH5PADDR; // Channel 5 peripheral address register offset 0x90
  volatile CHxM0ADDR_register CH5M0ADDR; // Channel 5 memory 0 address register offset 0x94
  volatile CHxM1ADDR_register CH5M1ADDR; // Channel 5 memory 1 address register offset 0x98
  volatile CHxFCTL_register CH5FCTL;   // Channel 5 FIFO control register offset 0x9C
  // Channel 6
  volatile CHxCTL_register CH6CTL;     // Channel 6 control register offset 0xA0
  volatile CHxCNT_register CH6CNT;     // Channel 6 counter register offset 0xA4
  volatile CHxPADDR_register CH6PADDR; // Channel 6 peripheral address register offset 0xA8
  volatile CHxM0ADDR_register CH6M0ADDR; // Channel 6 memory 0 address register offset 0xAC
  volatile CHxM1ADDR_register CH6M1ADDR; // Channel 6 memory 1 address register offset 0xB0
  volatile CHxFCTL_register CH6FCTL;   // Channel 6 FIFO control register offset 0xB4
  // Channel 7
  volatile CHxCTL_register CH7CTL;     // Channel 7 control register offset 0xB8
  volatile CHxCNT_register CH7CNT;     // Channel 7 counter register offset 0xBC
  volatile CHxPADDR_register CH7PADDR; // Channel 7 peripheral address register offset 0xC0
  volatile CHxM0ADDR_register CH7M0ADDR; // Channel 7 memory 0 address register offset 0xC4
  volatile CHxM1ADDR_register CH7M1ADDR; // Channel 7 memory 1 address register offset 0xC8
  volatile CHxFCTL_register CH7FCTL;   // Channel 7 FIFO control register offset 0xCC

  volatile CHxCTL_register *const ctlRegs[8] = {
      &CH0CTL, &CH1CTL, &CH2CTL, &CH3CTL, 
      &CH4CTL, &CH5CTL, &CH6CTL, &CH7CTL
    };
  volatile CHxCNT_register *const cntRegs[8] = {
    &CH0CNT, &CH1CNT, &CH2CNT, &CH3CNT,
    &CH4CNT, &CH5CNT, &CH6CNT, &CH7CNT
    };
  volatile CHxPADDR_register *const paddrRegs[8] = {
    &CH0PADDR, &CH1PADDR, &CH2PADDR, &CH3PADDR,
    &CH4PADDR, &CH5PADDR, &CH6PADDR, &CH7PADDR
    };
  volatile CHxM0ADDR_register *const m0Regs[8] = {
      &CH0M0ADDR, &CH1M0ADDR, &CH2M0ADDR, &CH3M0ADDR,
      &CH4M0ADDR, &CH5M0ADDR, &CH6M0ADDR, &CH7M0ADDR
    };
  volatile CHxM1ADDR_register *const m1Regs[8] = {
      &CH0M1ADDR, &CH1M1ADDR, &CH2M1ADDR, &CH3M1ADDR,
      &CH4M1ADDR, &CH5M1ADDR, &CH6M1ADDR, &CH7M1ADDR
    };
  volatile CHxFCTL_register *const fctlRegs[8] = {
      &CH0FCTL, &CH1FCTL, &CH2FCTL, &CH3FCTL,
      &CH4FCTL, &CH5FCTL, &CH6FCTL, &CH7FCTL
    };
};

static_assert(std::is_standard_layout<Dma>::value, "Dma class is NOT standard layout");
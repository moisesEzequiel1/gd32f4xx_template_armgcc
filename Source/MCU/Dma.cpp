#include "Dma.hpp"

template <typename E> constexpr auto etoi(E const value) {
  return static_cast<std::underlying_type_t<E>>(value);
}

// === Enable/Disable channel ===
void Dma::enableChannel(Channel ch) {
  // Array de referencias a los registros de control de cada canal  
  ctlRegs[etoi(ch)]->bits.CHEN = 1;
}

void Dma::disableChannel(Channel ch) {
  ctlRegs[etoi(ch)]->bits.CHEN = 0;
}

// === Set Peripheral / Memory Address ===
void Dma::setPeripheralAddress(Channel ch, uint32_t addr) {
  paddrRegs[etoi(ch)]->value = addr;
}

void Dma::setMemoryAddress(Channel ch, uint32_t addr, bool useAlt) {
  static volatile CHxM0ADDR_register *const m0Regs[] = {
      &CH0M0ADDR, &CH1M0ADDR, &CH2M0ADDR, &CH3M0ADDR,
      &CH4M0ADDR, &CH5M0ADDR, &CH6M0ADDR, &CH7M0ADDR};
  static volatile CHxM1ADDR_register *const m1Regs[] = {
      &CH0M1ADDR, &CH1M1ADDR, &CH2M1ADDR, &CH3M1ADDR,
      &CH4M1ADDR, &CH5M1ADDR, &CH6M1ADDR, &CH7M1ADDR};
  if (useAlt)
    m1Regs[etoi(ch)]->value = addr;
  else
    m0Regs[etoi(ch)]->value = addr;
}

// === Set Transfer Width ===
void Dma::setTransferWidth(Channel ch, TransferWidth width) {
  static volatile CHxCTL_register *const channelRegs[] = {
      &CH0CTL, &CH1CTL, &CH2CTL, &CH3CTL, &CH4CTL, &CH5CTL, &CH6CTL, &CH7CTL};
  switch (width) {
  case TransferWidth::Bit8:
    channelRegs[etoi(ch)]->bits.MWIDTH = 0b00;
    break;
  case TransferWidth::Bit16:
    channelRegs[etoi(ch)]->bits.MWIDTH = 0b01;
    break;
  case TransferWidth::Bit32:
    channelRegs[etoi(ch)]->bits.MWIDTH = 0b10;
    break;
  }
}

// === Set Priority ===
void Dma::setPriority(Channel ch, Priority prio) {
  auto *reg = ctlRegs[etoi(ch)];
  reg->bits.PRIO = prio;
}

// === Enable / Clear Interrupts ===
void Dma::enableInterrupt(Channel ch, InterruptFlag flag) {
  auto *reg = ctlRegs[etoi(ch)];

  switch (flag) {
  case InterruptFlag::SingleData:
    reg->bits.SDEIE = 1;
    break;
  case InterruptFlag::TransferError:
    reg->bits.TAEIE = 1;
    break;
  case InterruptFlag::HalfTransfer:
    reg->bits.HTFIE = 1;
    break;
  case InterruptFlag::TransferComplete:
    reg->bits.FTFIE = 1;
    break;
  case InterruptFlag::All:
    reg->bits.SDEIE = 1;
    reg->bits.TAEIE = 1;
    reg->bits.HTFIE = 1;
    reg->bits.FTFIE = 1;
    break;
  }
}
void Dma::clearInterruptFlag(Channel ch, InterruptFlag flag) {
  // pending 
}
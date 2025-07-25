#include "Pmu.hpp"

void Pmu::EnableHighDriverMode() {
  CTL.bits.HDEN = 1; // Enable high-drive mode
  while (CS.bits.HDRF != HighDriverReadyFlag::READY) {
  }
  // Wait until high-drive mode is ready
}

void Pmu::SetHighDriverMode() {
    CTL.bits.HDS = 1; // Set high-drive mode
    while (CS.bits.HDSRF != HighDriverSwitchReadyFlag::READY) {
    }
    // Wait until high-drive mode is set
}
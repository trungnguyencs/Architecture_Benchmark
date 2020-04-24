//  Contributed by Ehsan K.Ardestani
//                 Ian Lee
//                 Jose Renau
//
// The ESESC/BSD License
//
// Copyright (c) 2005-2013, Regents of the University of California and
// the ESESC Project.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//   - Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
//   - Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the distribution.
//
//   - Neither the name of the University of California, Santa Cruz nor the
//   names of its contributors may be used to endorse or promote products
//   derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

/*******************************************************************************
File name:      SescThermWrapper.cpp
Description:    Wrapper class for integration with Esesc / McPat Power Simulation
********************************************************************************/

#include <fstream>
#include <map>

#include "SescThermWrapper.h"

class ChipEnergyBundle;

SescThermWrapper::SescThermWrapper() {
}

void SescThermWrapper::plug(const char *section, ChipEnergyBundle *energyBundle) {
  sesctherm.configure(energyBundle);
}

int SescThermWrapper::calcTemp(ChipEnergyBundle *energyBundle, std::vector<float> *temperatures, uint64_t timeinterval,
                               uint32_t &throttleLength) {
  int return_signal = 0;
  return_signal     = sesctherm.computeTemp(energyBundle, temperatures, timeinterval);
  throttleLength    = sesctherm.get_throttleLength();
  return (return_signal);
}

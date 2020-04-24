// copyright and includes {{{1
// Contributed by Jose Renau
//                Basilio Fraguela
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

#ifndef PREFETCHER_H
#define PREFETCHER_H

#include "callback.h"
#include "estl.h"

#include "GStats.h"
#include "Port.h"

#include "AddressPredictor.h"
#include "CacheCore.h"
/* }}} */

class MemObj;

class Prefetcher {
private:
  GStatsAvg  avgPrefetchNum;
  GStatsAvg  avgPrefetchConf;
  GStatsHist histPrefetchDelta;

  AddressPredictor *apred;

  int32_t  maxPrefetch;
  int32_t  minDistance;
  int32_t  pfStride;
  int32_t  curPrefetch;
  uint32_t lineSizeBits;

  AddrType pref_sign;

  bool         pending_prefetch;
  AddrType     pending_preq_pc;
  uint16_t     pending_preq_conf;
  bool         pending_statsFlag;
  FetchEngine *pending_chain_fetch;

  uint16_t conf = 0;
  AddrType pending_preq_addr;

  void nextPrefetch();

  MemObj *DL1; // L1 cache

  StaticCallbackMember0<Prefetcher, &Prefetcher::nextPrefetch> nextPrefetchCB;

public:
  Prefetcher(MemObj *l1, int cpud_id);
  ~Prefetcher() {
  }

  void exe(DInst *dinst);
  void ret(DInst *dinst);
};

#endif

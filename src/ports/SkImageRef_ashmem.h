/*
** Copyright 2006, The Android Open Source Project
** Copyright (c) 2010, Code Aurora Forum. All rights reserved.
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#ifndef SkImageRef_ashmem_DEFINED
#define SkImageRef_ashmem_DEFINED

#include "SkImageRef.h"

struct SkAshmemRec {
    int     fFD;
    void*   fAddr;
    size_t  fSize;
    bool    fPinned;
};

class SkImageRef_ashmem : public SkImageRef {
public:
    SkImageRef_ashmem(SkStream*, SkBitmap::Config, int sampleSize = 1);
    virtual ~SkImageRef_ashmem();
    bool pixelsAvailable();

protected:
    virtual bool onDecode(SkImageDecoder* codec, SkStream* stream,
                          SkBitmap* bitmap, SkBitmap::Config config,
                          SkImageDecoder::Mode mode);
    
    virtual void* onLockPixels(SkColorTable**);
    virtual void onUnlockPixels();
    
private:
    void closeFD();

    SkColorTable* fCT;
    SkAshmemRec fRec;

    typedef SkImageRef INHERITED;
};

#endif

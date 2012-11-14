
/*
 * Copyright 2012 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "SkLanguage.h"

#ifdef SK_BUILD_FOR_ANDROID // currently only for Android

#include "SkTDict.h"
#include "SkThread.h"
#include <cstring>

SkLanguage SkLanguage::getParent() const {
    SkASSERT(fInfo != NULL);
    SkASSERT(fInfo->fTag != NULL);
    const char* tag = fInfo->fTag.c_str();
    SkASSERT(tag != NULL);

    // strip off the rightmost "-.*"
    char* parentTagEnd = strrchr(tag, '-');
    if (parentTagEnd == NULL) {
        return SkLanguage("");
    }
    size_t parentTagLen = parentTagEnd - tag;
    char parentTag[parentTagLen + 1];
    strncpy(parentTag, tag, parentTagLen);
    parentTag[parentTagLen] = '\0';
    return SkLanguage(parentTag);
}

SK_DECLARE_STATIC_MUTEX(gGetInfoMutex);
const SkLanguageInfo* SkLanguage::getInfo(const char* tag) {
    SkAutoMutexAcquire lock(gGetInfoMutex);

    static const size_t kDictSize = 128;
    static SkTDict<SkLanguageInfo*> tagToInfo(kDictSize);

    // try a lookup
    SkLanguageInfo* info;
    if (tagToInfo.find(tag, &info)) {
        return info;
    }

    // no match - add this language
    info = new SkLanguageInfo(tag);
    tagToInfo.set(tag, info);
    return info;
}

#endif

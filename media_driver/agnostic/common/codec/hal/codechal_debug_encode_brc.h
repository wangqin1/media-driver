/*
* Copyright (c) 2017, Intel Corporation
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*/
//!
//! \file     codechal_debug_encode_brc.h
//! \brief    Defines the debug interface shared by all of CodecHal for encode
//!           SW BRC DLL.
//!

#ifndef __CODECHAL_DEBUG_ENCODE_BRC_H__
#define __CODECHAL_DEBUG_ENCODE_BRC_H__

#include "codechal.h"
#include "codechal_encode_hevc.h"

#if USE_CODECHAL_DEBUG_TOOL

#define CODECHAL_DBG_STRING_SWAVCBRCLIBRARY "AVCBRC.dll"

#define VP9SWBRCLIB  "VP9BRCDLL.dll"
#define CODECHAL_DBG_STRING_SWHEVCBRCLIBRARY "HEVCBRC.dll"

/*
MOS_STATUS CodecHal_DbgCallAvcSwBrcImpl(
    CodechalDebugInterface         *pDebugInterface,
    CODECHAL_MEDIA_STATE_TYPE       Function,
    CodechalEncoderState            *pEncoder,
    EncodeBrcBuffers*               pBrcBuffers,
    bool                            bIsReset,
    PMHW_KERNEL_STATE               pKernelState,
    PMHW_KERNEL_STATE               pMbEncKernelState);
*/

MOS_STATUS CodecHal_DbgCallAvcVdencSwBrcImpl(
    CodechalDebugInterface *           pDebugInterface,
    HMODULE                            swBrcHandle,
    CODECHAL_MEDIA_STATE_TYPE          Function,
    bool                               bIsReset,
    PMOS_RESOURCE                      presDmemBuffer,
    PMOS_RESOURCE                      presPakMmioBuffer,
    MHW_VDBOX_HUC_VIRTUAL_ADDR_PARAMS *pvirtualAddrParams);

/*
MOS_STATUS CodecHal_DbgCallHevcSwBrcImpl(
    CodechalDebugInterface         *pDebugInterface,
    CODECHAL_MEDIA_STATE_TYPE       Function,
    CodechalEncHevcState            *hevcState,
    bool                            bIsReset,
    PMHW_KERNEL_STATE               pKernelState,
    PMHW_KERNEL_STATE               pMbEncKernelState);
*/

MOS_STATUS CodecHal_DbgCallHevcVdencSwBrcImpl(
    CodechalDebugInterface         *pDebugInterface,
    HMODULE                         swBrcHandle,
    CODECHAL_MEDIA_STATE_TYPE       Function,
    bool                            bIsResetOrLD,
    PMOS_RESOURCE                   presDmemBuffer,
    PMOS_RESOURCE                   presPakMmioBuffer,
    MHW_VDBOX_HUC_VIRTUAL_ADDR_PARAMS *pvirtualAddrParams);

/*
MOS_STATUS CodecHal_DbgCallSwLookaheadImpl(
    CodechalDebugInterface *           pDebugInterface,
    HMODULE                            swLaHandle,
    CODECHAL_MEDIA_STATE_TYPE          Function,
    PMOS_RESOURCE                      presDmemBuffer,
    PMOS_RESOURCE                      presPakMmioBuffer,
    MHW_VDBOX_HUC_VIRTUAL_ADDR_PARAMS *pvirtualAddrParams);
*/
#endif // _DEBUG || _RELEASE_INTERNAL

#endif // __CODECHAL_DEBUG_ENCODE_BRC_H__

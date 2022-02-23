/*
* Copyright (c) 2017-2021, Intel Corporation
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
//! \file     codechal_debug_encode_brc.c
//! \brief    Implements the debug interface shared by all of CodecHal for encode
//!           SW BRC DLL.
//!

#include "codechal_debug.h"

#if USE_CODECHAL_DEBUG_TOOL

#include "codechal_debug_encode_brc.h"
#ifdef _HEVC_ENCODE_VME_SUPPORTED
#include "codechal_encode_hevc.h"
#endif

typedef void * (__cdecl *CreateInstance)(ProcessType);
typedef void(__cdecl *ReleaseInstance)(void *);
typedef int(__cdecl *Process)(void *);
typedef int(__cdecl *SetBuff)(unsigned char *, BufferType, void *);
typedef int(__cdecl *HevcSetBuff)(unsigned char *, HEVCBufferType, void *);

//!
//! \enum     AvcVdencBufferType
//! \brief    AVC VDEnc Buffer type
//!
enum AvcVdencBufferType
{
    AVCVDENC_UnknownBuff = 0,
    AVCVDENC_INLINE_DMEM,
    AVCVDENC_HISTORY_BUFF,
    AVCVDENC_VDENC_STATISTICS_BUFF,
    AVCVDENC_PAK_STATISTICS_BUFF,
    AVCVDENC_INPUT_SLBB_BUFF,
    AVCVDENC_HME_DETECTION_DATA_BUFF,
    AVCVDENC_CONSTANT_DATA_BUFF,
    AVCVDENC_OUTPUT_SLBB_BUFF,
    AVCVDENC_SLICE_SIZE_BUFF,
    AVCVDENC_ROI_MAP_BUFF,
    AVCVDENC_INPUT_STREAMIN_BUFF,
    AVCVDENC_OUTPUT_STREAMIN_BUFF,
    AVCVDENC_LOOKAHEAD_DATA_BUFF,
    AVCVDENC_AUX_BUFF
};

typedef void *(__cdecl *AvcVdencCreateInstance)(void);
typedef void(__cdecl *AvcVdencReleaseInstance)(void *);
typedef int(__cdecl *AvcVdencSetBuff)(unsigned char *, AvcVdencBufferType, void *);
typedef unsigned int(__cdecl *AvcVdencProcess)(void *, ProcessType);

typedef void * (__cdecl *HevcVdencCreateInstance)(void);
typedef void(__cdecl *HevcVdencReleaseInstance)(void *);
typedef int(__cdecl *HevcVdencSetBuff)(unsigned char *, HevcVdencBufferType, void *);
typedef unsigned int(__cdecl *HevcVdencProcess)(void *, ProcessType);

typedef struct _HEVC_VDENC_HUC_AUX_BUFFER
{
    uint32_t Function;    // reserved for function related flags
    uint32_t HuCStatus;   // HuC Status
    uint8_t  PrevSceneChgType;
    uint8_t  PrevSceneChgFrmAway;
    uint8_t  rsvd[2];
    uint32_t RSVD[13];
} HEVC_VDENC_HUC_AUX_BUFFER, *PHEVC_VDENC_HUC_AUX_BUFFER;
/*
typedef struct _LOOKAHEAD_HUC_AUX_BUFFER
{
    uint32_t function;   // reserved for function related flags
    uint32_t hucStatus;  // HuC Status
    uint32_t reserved[62];
} LOOKAHEAD_HUC_AUX_BUFFER, *PLOOKAHEAD_HUC_AUX_BUFFER;

typedef enum VP9BufferType
{
    eVp9UnknownBuff = 0,
    eVp9INLINE_DMEM,
    eVp9HISTORY_BUFF,
    eVp9VDENC_STATISTICS_BUFF,
    eVp9PAK_STATISTICS_BUFF,
    eVp9INPUT_SLBB_BUFF,
    eVp9BRC_DATA_BUFF,
    eVp9CONSTANT_DATA_BUFF,
    eVp9OUTPUT_SLBB_BUFF,
    eVp9PAKMMIO_BUFF,
    eVp9AUX_BUFF
} VP9BufferType;

typedef void*   (*VP9BRC_CreateInstance)();
typedef void(*VP9BRC_ReleaseInstance)(void*);
typedef int(*VP9BRC_Process)(void*, ProcessType);
typedef int(*VP9BRC_SetBuff)(unsigned char*, VP9BufferType, void*);

typedef void *(__cdecl *LA_CreateInstance)(void);
typedef void(__cdecl *LA_ReleaseInstance)(void *);
typedef int(__cdecl *LA_SetBuff)(unsigned char *, LABufferType, void *);
typedef int(__cdecl *LA_Process)(void *, LAProcessType);
*/

typedef struct _AVC_VDENC_HUC_AUX_BUFFER
{
    uint32_t Function;   // reserved for function related flags
    uint32_t HuCStatus;  // HuC Status
    uint32_t RSVD[62];
    void *   fpBrcStat;  // FILE* pointer, used to dump BRC statistics in Cmodel. fopen/fclose are done by caller. Default to NULL for not dumping BRC statistics to a file.
    uint8_t  BrcStat1[1024];
    uint8_t  BrcStat2[256];
} AVC_VDENC_HUC_AUX_BUFFER, *PAVC_VDENC_HUC_AUX_BUFFER;

#define CODECHAL_DEBUG_CHK_DLLSTS(sts)                                          \
{                                                                               \
    if (sts != 0)                                                               \
    {                                                                           \
        CODECHAL_DEBUG_ASSERTMESSAGE("Invalid DLL BRC status.");                \
        eStatus = MOS_STATUS_UNKNOWN;                                           \
        goto finish;                                                            \
    }                                                                           \
}
/*
MOS_STATUS CodecHal_DbgCallAvcSwBrcImpl(
    CodechalDebugInterface         *pDebugInterface,
    CODECHAL_MEDIA_STATE_TYPE       Function,
    CodechalEncoderState            *avcState,
    EncodeBrcBuffers*               pBrcBuffers,
    bool                            bIsReset,
    PMHW_KERNEL_STATE               pKernelState,
    PMHW_KERNEL_STATE               pMbEncKernelState)
{
    PMOS_INTERFACE                  pOsInterface = nullptr;
    PMOS_RESOURCE                   pResBuffer = nullptr;
    CodechalHwInterface            *pHwInterface;
    uint8_t                        *pbData = nullptr;
    uint32_t                        dwSize;
    char                            sAttrib[15];
    int                             sts = SUCCEED;
    void                            *handle = nullptr;
    MOS_STATUS                      eStatus = MOS_STATUS_SUCCESS;

    CreateInstance                  createInstanceAdd = nullptr;
    SetBuff                         setBuffAdd;
    Process                         processAdd;
    ReleaseInstance                 releaseInstanceAdd = nullptr;
    MOS_LOCK_PARAMS                 LockFlagsReadOnly;
    MOS_LOCK_PARAMS                 LockFlagsWriteOnly;

    uint8_t* pCurbeData = nullptr;
    PMOS_RESOURCE pWriteBuffer = nullptr;
    uint8_t* pwData = nullptr;
    uint8_t* pCurbeEncData = nullptr;
    uint8_t* pCurbeEncDataWrite = nullptr;

    CODECHAL_DEBUG_FUNCTION_ENTER;

    CODECHAL_DEBUG_CHK_NULL(pDebugInterface);
    CODECHAL_DEBUG_CHK_NULL(pDebugInterface->m_osInterface);
    CODECHAL_DEBUG_CHK_NULL(pDebugInterface->m_hwInterface);
    CODECHAL_DEBUG_CHK_NULL(pKernelState);

    pOsInterface = pDebugInterface->m_osInterface;
    pHwInterface = pDebugInterface->m_hwInterface;

    createInstanceAdd = (CreateInstance)MosUtilities::MosGetProcAddress(avcState->m_swBrcMode, "MC_CreateInstance");
    CODECHAL_DEBUG_CHK_NULL(createInstanceAdd);

    setBuffAdd = (SetBuff)MosUtilities::MosGetProcAddress(avcState->m_swBrcMode, "MC_SetBuff");
    CODECHAL_DEBUG_CHK_NULL(setBuffAdd);

    processAdd = (Process)MosUtilities::MosGetProcAddress(avcState->m_swBrcMode, "MC_Process");
    CODECHAL_DEBUG_CHK_NULL(processAdd);

    releaseInstanceAdd = (ReleaseInstance)MosUtilities::MosGetProcAddress(avcState->m_swBrcMode, "MC_ReleaseInstance");
    CODECHAL_DEBUG_CHK_NULL(releaseInstanceAdd);

    if (Function == CODECHAL_MEDIA_STATE_BRC_INIT_RESET)
    {
        if (true == bIsReset)
        {
            handle = (createInstanceAdd)(BRCReset);
        }
        else
        {
            handle = (createInstanceAdd)(BRCInit);
        }
    }
    else
    {
        handle = (createInstanceAdd)(BRCUpdate);
    }

    //-----------------------------------------------------------------------------------------------
    // brc curbe buffer
    pCurbeData = (uint8_t*)pKernelState->m_dshRegion.GetHeapLockedData();
    CODECHAL_DEBUG_CHK_NULL(pCurbeData);
    pCurbeData +=
        pKernelState->m_dshRegion.GetOffset() +
        pKernelState->dwCurbeOffset;

    sts = (setBuffAdd)(pCurbeData, CURBE, handle);
    CODECHAL_DEBUG_CHK_DLLSTS(sts);

    //-----------------------------------------------------------------------------------------------
    // distrotion buffer

    // initiate lock flags
    MOS_ZeroMemory(&LockFlagsReadOnly, sizeof(MOS_LOCK_PARAMS));
    LockFlagsReadOnly.ReadOnly = 1;
    MOS_ZeroMemory(&LockFlagsWriteOnly, sizeof(MOS_LOCK_PARAMS));
    LockFlagsWriteOnly.WriteOnly = 1;

    pResBuffer = &pBrcBuffers->sMeBrcDistortionBuffer.OsResource;
    pbData = (uint8_t*)pOsInterface->pfnLockResource(pOsInterface, pResBuffer, &LockFlagsReadOnly);
    CODECHAL_DEBUG_CHK_NULL(pbData);

    pbData += pBrcBuffers->dwMeBrcDistortionBottomFieldOffset;

    sts = (setBuffAdd)(pbData, DISTORTION, handle);
    CODECHAL_DEBUG_CHK_DLLSTS(sts);

    pOsInterface->pfnUnlockResource(
        pOsInterface,
        pResBuffer);
    pbData = nullptr;

    //-----------------------------------------------------------------------------------------------
    // history buffer

    pResBuffer = &pBrcBuffers->resBrcHistoryBuffer;
    pbData = (uint8_t*)pOsInterface->pfnLockResource(pOsInterface, pResBuffer, &LockFlagsReadOnly);
    CODECHAL_DEBUG_CHK_NULL(pbData);

    sts = (setBuffAdd)(pbData, HISTORY, handle);
    CODECHAL_DEBUG_CHK_DLLSTS(sts);

    pOsInterface->pfnUnlockResource(
        pOsInterface,
        pResBuffer);
    pbData = nullptr;

    if (Function == CODECHAL_MEDIA_STATE_BRC_INIT_RESET)
    {
        // we need only brc curbe, history and distrotion for init/reset kernel
        sts = (processAdd)(handle);
        CODECHAL_DEBUG_CHK_DLLSTS(sts);

        goto finish;
    }

    // fill rest buffers for update brc kernel
    //-----------------------------------------------------------------------------------------------
    // image state buffer
    pResBuffer = &pBrcBuffers->resBrcImageStatesReadBuffer[avcState->m_currRecycledBufIdx];
    pbData = (uint8_t*)pOsInterface->pfnLockResource(pOsInterface, pResBuffer, &LockFlagsReadOnly);
    CODECHAL_DEBUG_CHK_NULL(pbData);

    pWriteBuffer = &pBrcBuffers->resBrcImageStatesWriteBuffer;
    pwData = (uint8_t*)pOsInterface->pfnLockResource(pOsInterface, pWriteBuffer, &LockFlagsWriteOnly);
    CODECHAL_DEBUG_CHK_NULL(pwData);

    MOS_SecureMemcpy(pwData, BRC_IMG_STATE_SIZE_PER_PASS * pHwInterface->GetMfxInterface()->GetBrcNumPakPasses(), pbData, BRC_IMG_STATE_SIZE_PER_PASS * pHwInterface->GetMfxInterface()->GetBrcNumPakPasses());

    sts = (setBuffAdd)(pwData, IMGSTATE, handle);
    CODECHAL_DEBUG_CHK_DLLSTS(sts);

    pOsInterface->pfnUnlockResource(
        pOsInterface,
        pResBuffer);
    pbData = nullptr;

    pOsInterface->pfnUnlockResource(
        pOsInterface,
        pWriteBuffer);
    pwData = nullptr;

    //-----------------------------------------------------------------------------------------------
    // constant buffer
    pResBuffer = &pBrcBuffers->sBrcConstantDataBuffer[avcState->m_currRecycledBufIdx].OsResource;
    pbData = (uint8_t*)pOsInterface->pfnLockResource(pOsInterface, pResBuffer, &LockFlagsReadOnly);
    CODECHAL_DEBUG_CHK_NULL(pbData);

    // constant buffer pbData
    sts = (setBuffAdd)(pbData, CONSTANT, handle);
    CODECHAL_DEBUG_CHK_DLLSTS(sts);

    pOsInterface->pfnUnlockResource(
        pOsInterface,
        pResBuffer);
    pbData = nullptr;

    //-----------------------------------------------------------------------------------------------
    // pak buffer
    pResBuffer = &pBrcBuffers->resBrcPakStatisticBuffer[0];
    pbData = (uint8_t*)pOsInterface->pfnLockResource(pOsInterface, pResBuffer, &LockFlagsReadOnly);
    CODECHAL_DEBUG_CHK_NULL(pbData);

    sts = (setBuffAdd)(pbData, PAK, handle);
    CODECHAL_DEBUG_CHK_DLLSTS(sts);

    pOsInterface->pfnUnlockResource(
        pOsInterface,
        pResBuffer);
    pbData = nullptr;

    if (!Mos_ResourceIsNull(&pBrcBuffers->sBrcMbQpBuffer.OsResource))
    {
        pResBuffer = &pBrcBuffers->sBrcMbQpBuffer.OsResource;
        pbData = (uint8_t*)pOsInterface->pfnLockResource(pOsInterface, pResBuffer, &LockFlagsReadOnly);
        CODECHAL_DEBUG_CHK_NULL(pbData);

        pbData += pBrcBuffers->dwBrcMbQpBottomFieldOffset;

        sts = (setBuffAdd)(pbData, MBQP, handle);
        CODECHAL_DEBUG_CHK_DLLSTS(sts);

        pOsInterface->pfnUnlockResource(
            pOsInterface,
            pResBuffer);

        pbData = nullptr;
    }

    if (avcState->m_mbencBrcBufferSize > 0)
    {
        //Started from GEN95, separated Mbenc curbe from BRC update kernel. BRC update kernel will generate a 128 bytes surface for mbenc.
        //The new surface contains the updated data for mbenc. MBenc kernel has been changed to use the new BRC update output surface
        //to update its curbe internally.
        // MbEnc BRC buffer - write only
        pResBuffer = &pBrcBuffers->resMbEncBrcBuffer;
        pbData = (uint8_t*)pOsInterface->pfnLockResource(pOsInterface, pResBuffer, &LockFlagsReadOnly);
        CODECHAL_DEBUG_CHK_NULL(pbData);

        sts = (setBuffAdd)(pbData, ENC, handle);
        CODECHAL_DEBUG_CHK_DLLSTS(sts);

        pOsInterface->pfnUnlockResource(
            pOsInterface,
            pResBuffer);
        pbData = nullptr;
    }
    else
    {
        pCurbeEncData = (uint8_t*)pMbEncKernelState->m_dshRegion.GetHeapLockedData();
        CODECHAL_DEBUG_CHK_NULL(pCurbeEncData);
        pCurbeEncData +=
            pMbEncKernelState->m_dshRegion.GetOffset() +
            pMbEncKernelState->dwCurbeOffset;
        pCurbeEncDataWrite = pCurbeEncData;
        dwSize = pMbEncKernelState->KernelParams.iCurbeLength;

        sts = (setBuffAdd)(pCurbeEncDataWrite, ENC, handle);
        CODECHAL_DEBUG_CHK_DLLSTS(sts);
    }

    //-----------------------------------------------------------------------------------------------
    // MBStats buffer
    pResBuffer = &avcState->m_resMbStatsBuffer;
    pbData = (uint8_t*)pOsInterface->pfnLockResource(pOsInterface, pResBuffer, &LockFlagsReadOnly);
    CODECHAL_DEBUG_CHK_NULL(pbData);

    sts = (setBuffAdd)(pbData, STATISTICS, handle);
    CODECHAL_DEBUG_CHK_DLLSTS(sts);

    pOsInterface->pfnUnlockResource(
        pOsInterface,
        pResBuffer);
    pbData = nullptr;

    //-----------------------------------------------------------------------------------------------
    // call sw update brc
    sts = (processAdd)(handle);
    CODECHAL_DEBUG_CHK_DLLSTS(sts);

finish:
    if (pbData)
    {
        pOsInterface->pfnUnlockResource(
            pOsInterface,
            pResBuffer);
    }

    if (releaseInstanceAdd != nullptr)
    {
        (releaseInstanceAdd)(handle);
    }

    return eStatus;
}
*/

MOS_STATUS CodecHal_DbgCallAvcVdencSwBrcImpl(
    CodechalDebugInterface *           pDebugInterface,
    HMODULE                            swBrcHandle,
    CODECHAL_MEDIA_STATE_TYPE          Function,
    bool                               bIsReset,
    PMOS_RESOURCE                      presDmemBuffer,
    PMOS_RESOURCE                      presPakMmioBuffer,
    MHW_VDBOX_HUC_VIRTUAL_ADDR_PARAMS *pvirtualAddrParams)
{
    PMOS_INTERFACE pOsInterface = nullptr;
    PMOS_RESOURCE  pResBuffer   = nullptr;
    uint8_t *      pbData       = nullptr;
    uint32_t *     pdwData      = nullptr;
    uint8_t *      pbAuxBuffer  = nullptr;
    int            sts          = SUCCEED;
    uint32_t       processSts   = 0;
    void *         handle       = nullptr;
    MOS_STATUS     eStatus      = MOS_STATUS_SUCCESS;

    AvcVdencCreateInstance  createInstanceAdd = nullptr;
    AvcVdencSetBuff         setBuffAdd;
    AvcVdencProcess         processAdd;
    AvcVdencReleaseInstance releaseInstanceAdd = nullptr;
    MOS_LOCK_PARAMS         LockFlagsReadOnly;
    MOS_LOCK_PARAMS         LockFlagsWriteOnly;

    AvcVdencBufferType BufferTypeMap[16] = {
        AVCVDENC_HISTORY_BUFF,             // Region 0
        AVCVDENC_VDENC_STATISTICS_BUFF,    // Region 1
        AVCVDENC_PAK_STATISTICS_BUFF,      // Region 2
        AVCVDENC_INPUT_SLBB_BUFF,          // Region 3
        AVCVDENC_HME_DETECTION_DATA_BUFF,  // Region 4
        AVCVDENC_CONSTANT_DATA_BUFF,       // Region 5
        AVCVDENC_OUTPUT_SLBB_BUFF,         // Region 6
        AVCVDENC_SLICE_SIZE_BUFF,          // Region 7
        AVCVDENC_ROI_MAP_BUFF,             // Region 8
        AVCVDENC_INPUT_STREAMIN_BUFF,      // Region 9
        AVCVDENC_OUTPUT_STREAMIN_BUFF,     // Region 10
        AVCVDENC_UnknownBuff,              // Region 11
        AVCVDENC_UnknownBuff,              // Region 12
        AVCVDENC_UnknownBuff,              // Region 13
        AVCVDENC_UnknownBuff,              // Region 14
        AVCVDENC_AUX_BUFF                  // Region 15
    };

    CODECHAL_DEBUG_FUNCTION_ENTER;

    CODECHAL_DEBUG_CHK_NULL(pDebugInterface);
    CODECHAL_DEBUG_CHK_NULL(pDebugInterface->m_osInterface);

    pOsInterface = pDebugInterface->m_osInterface;

    createInstanceAdd = (AvcVdencCreateInstance)MosUtilities::MosGetProcAddress(swBrcHandle, "AVCBRC_CreateInstance");
    CODECHAL_DEBUG_CHK_NULL(createInstanceAdd);

    setBuffAdd = (AvcVdencSetBuff)MosUtilities::MosGetProcAddress(swBrcHandle, "AVCBRC_SetBuff");
    CODECHAL_DEBUG_CHK_NULL(setBuffAdd);

    processAdd = (AvcVdencProcess)MosUtilities::MosGetProcAddress(swBrcHandle, "AVCBRC_Process");
    CODECHAL_DEBUG_CHK_NULL(processAdd);

    releaseInstanceAdd = (AvcVdencReleaseInstance)MosUtilities::MosGetProcAddress(swBrcHandle, "AVCBRC_ReleaseInstance");
    CODECHAL_DEBUG_CHK_NULL(releaseInstanceAdd);

    handle = (createInstanceAdd)();

    // initiate lock flags
    MOS_ZeroMemory(&LockFlagsReadOnly, sizeof(MOS_LOCK_PARAMS));
    LockFlagsReadOnly.ReadOnly = 1;
    MOS_ZeroMemory(&LockFlagsWriteOnly, sizeof(MOS_LOCK_PARAMS));
    LockFlagsWriteOnly.WriteOnly = 1;

    //-----------------------------------------------------------------------------------------------
    // BRC DMEM
    pbData = (uint8_t *)pOsInterface->pfnLockResource(pOsInterface, presDmemBuffer, &LockFlagsReadOnly);
    CODECHAL_DEBUG_CHK_NULL(pbData);

    sts = (setBuffAdd)((uint8_t *)pbData, AVCVDENC_INLINE_DMEM, handle);
    CODECHAL_DEBUG_CHK_DLLSTS(sts);

    //-----------------------------------------------------------------------------------------------
    // Regions
    for (int regionIndex = 0; regionIndex < 16; regionIndex++)
    {
        if ((pvirtualAddrParams->regionParams[regionIndex].presRegion != nullptr) &&
            (BufferTypeMap[regionIndex] != AVCVDENC_UnknownBuff))
        {
            MOS_LOCK_PARAMS *pLockFlags =
                pvirtualAddrParams->regionParams[regionIndex].isWritable ? &LockFlagsWriteOnly : &LockFlagsReadOnly;
            pResBuffer = pvirtualAddrParams->regionParams[regionIndex].presRegion;
            pbData     = (uint8_t *)pOsInterface->pfnLockResource(pOsInterface, pResBuffer, pLockFlags);
            CODECHAL_DEBUG_CHK_NULL(pbData);

            sts = (setBuffAdd)(pbData, BufferTypeMap[regionIndex], handle);
            CODECHAL_DEBUG_CHK_DLLSTS(sts);
        }
    }

    //-----------------------------------------------------------------------------------------------
    // AUX buffer
    pbAuxBuffer = (uint8_t *)MOS_AllocAndZeroMemory(sizeof(AVC_VDENC_HUC_AUX_BUFFER));
    CODECHAL_DEBUG_CHK_NULL(pbAuxBuffer);

    sts = (setBuffAdd)((uint8_t *)pbAuxBuffer, AVCVDENC_AUX_BUFF, handle);
    CODECHAL_DEBUG_CHK_DLLSTS(sts);

    //-----------------------------------------------------------------------------------------------
    // process sw brc
    if (Function == CODECHAL_MEDIA_STATE_BRC_INIT_RESET)
    {
        processSts = (processAdd)(handle, bIsReset ? BRCReset : BRCInit);
        CODECHAL_DEBUG_CHK_DLLSTS(processSts);
    }
    else
    {
        processSts = (processAdd)(handle, BRCUpdate);

        // update PAK MMIO buffer for conditional second pass
        pdwData = (uint32_t *)pOsInterface->pfnLockResource(pOsInterface, presPakMmioBuffer, &LockFlagsReadOnly);
        CODECHAL_DEBUG_CHK_NULL(pdwData);

        *pdwData       = ((AVC_VDENC_HUC_AUX_BUFFER *)pbAuxBuffer)->HuCStatus;
        //printf("*pdwData %0x \n", *pdwData); 
        *pdwData = processSts;
        //printf("*pdwData now %0x \n", *pdwData);

        if (((AVC_VDENC_HUC_AUX_BUFFER *)pbAuxBuffer)->HuCStatus & 0x80000000)
        {
            CODECHAL_DEBUG_ASSERTMESSAGE("NumberPasses: 2");
        }

        pOsInterface->pfnUnlockResource(
            pOsInterface,
            presPakMmioBuffer);
    }

finish:
    MOS_SafeFreeMemory(pbAuxBuffer);

    for (int regionIndex = 0; regionIndex < 16; regionIndex++)
    {
        if ((pvirtualAddrParams->regionParams[regionIndex].presRegion != nullptr) &&
            (BufferTypeMap[regionIndex] != AVCVDENC_UnknownBuff))
        {
            pResBuffer = pvirtualAddrParams->regionParams[regionIndex].presRegion;
            pOsInterface->pfnUnlockResource(
                pOsInterface,
                pResBuffer);
        }
    }

    pOsInterface->pfnUnlockResource(
        pOsInterface,
        presDmemBuffer);

    if (releaseInstanceAdd != nullptr)
    {
        (releaseInstanceAdd)(handle);
    }

    return eStatus;
}

/*
#ifdef _HEVC_ENCODE_VME_SUPPORTED
MOS_STATUS CodecHal_DbgCallHevcSwBrcImpl(
    CodechalDebugInterface         *pDebugInterface,
    CODECHAL_MEDIA_STATE_TYPE       Function,
    CodechalEncHevcState            *hevcState,
    bool                            bIsReset,
    PMHW_KERNEL_STATE               pKernelState,
    PMHW_KERNEL_STATE               pMbEncKernelState)
{

    PMOS_INTERFACE                  pOsInterface = nullptr;
    PMOS_RESOURCE                   pResBuffer = nullptr;
    CodechalHwInterface             *pHwInterface;
    uint8_t*                        pbData = nullptr;
    uint32_t                        dwSize;
    char                            sAttrib[15];
    int                             sts = SUCCEED;
    void                            *handle = nullptr;
    MOS_STATUS                      eStatus = MOS_STATUS_SUCCESS;

    CreateInstance                  createInstanceAdd = nullptr;
    HevcSetBuff                     setBuffAdd;
    Process                         processAdd;
    ReleaseInstance                 releaseInstanceAdd = nullptr;
    MOS_LOCK_PARAMS                 LockFlagsReadOnly;
    MOS_LOCK_PARAMS                 LockFlagsWriteOnly;

    uint8_t* pCurbeData = nullptr;
    PMOS_RESOURCE pWriteBuffer = nullptr;
    uint8_t* pwData = nullptr;
    uint8_t* pCurbeEncData = nullptr;
    uint8_t* pCurbeEncDataWrite = nullptr;
    uint32_t dwBrcPasses = BRC_IMG_STATE_SIZE_PER_PASS;
    PMOS_RESOURCE presBrcInputForEncKernels = nullptr;

    CODECHAL_DEBUG_FUNCTION_ENTER;

    CODECHAL_DEBUG_CHK_NULL(pDebugInterface);
    CODECHAL_DEBUG_CHK_NULL(pDebugInterface->m_osInterface);
    CODECHAL_DEBUG_CHK_NULL(pDebugInterface->m_hwInterface);
    CODECHAL_DEBUG_CHK_NULL(pKernelState);

    pOsInterface                                         = pDebugInterface->m_osInterface;
    pHwInterface                                         = pDebugInterface->m_hwInterface;
    CodechalEncHevcState::HevcEncBrcBuffers *pBrcBuffers = &hevcState->m_brcBuffers;

    createInstanceAdd = (CreateInstance)MosUtilities::MosGetProcAddress(hevcState->m_swBrcMode, "MC_CreateInstance");
    CODECHAL_DEBUG_CHK_NULL(createInstanceAdd);

    setBuffAdd = (HevcSetBuff)MosUtilities::MosGetProcAddress(hevcState->m_swBrcMode, "MC_SetBuff");
    CODECHAL_DEBUG_CHK_NULL(setBuffAdd);

    processAdd = (Process)MosUtilities::MosGetProcAddress(hevcState->m_swBrcMode, "MC_Process");
    CODECHAL_DEBUG_CHK_NULL(processAdd);

    releaseInstanceAdd = (ReleaseInstance)MosUtilities::MosGetProcAddress(hevcState->m_swBrcMode, "MC_ReleaseInstance");
    CODECHAL_DEBUG_CHK_NULL(releaseInstanceAdd);

    if (Function == CODECHAL_MEDIA_STATE_BRC_INIT_RESET)
    {
        if (true == bIsReset)
        {
            handle = (createInstanceAdd)(BRCReset);
        }
        else
        {
            handle = (createInstanceAdd)(BRCInit);
        }
    }
    else
    {
        handle = (createInstanceAdd)(BRCUpdate);
    }

    // initiate lock flags
    MOS_ZeroMemory(&LockFlagsReadOnly, sizeof(MOS_LOCK_PARAMS));
    LockFlagsReadOnly.ReadOnly = 1;
    MOS_ZeroMemory(&LockFlagsWriteOnly, sizeof(MOS_LOCK_PARAMS));
    LockFlagsWriteOnly.WriteOnly = 1;

    // Brc curbe buffer
    pCurbeData = (uint8_t*)pKernelState->m_dshRegion.GetHeapLockedData();
    CODECHAL_DEBUG_CHK_NULL(pCurbeData);
    pCurbeData +=
        pKernelState->m_dshRegion.GetOffset() +
        pKernelState->dwCurbeOffset;

    if (Function == CODECHAL_MEDIA_STATE_BRC_INIT_RESET)
    {
        sts = (setBuffAdd)(pCurbeData, HEVC_INITCURBE, handle);
    }
    else
    {
        sts = (setBuffAdd)(pCurbeData, HEVC_CURBE, handle);
    }
    CODECHAL_DEBUG_CHK_DLLSTS(sts);

    // History buffer
    pResBuffer = &pBrcBuffers->resBrcHistoryBuffer;
    pbData = (uint8_t*)pOsInterface->pfnLockResource(pOsInterface, pResBuffer, &LockFlagsReadOnly);
    CODECHAL_DEBUG_CHK_NULL(pbData);

    sts = (setBuffAdd)(pbData, HEVC_HISTORY, handle);
    CODECHAL_DEBUG_CHK_DLLSTS(sts);

    pOsInterface->pfnUnlockResource(
        pOsInterface,
        pResBuffer);
    pbData = nullptr;

    // Distortion buffer/Surface
    CODECHAL_DEBUG_CHK_NULL(hevcState->m_brcDistortion);
    pResBuffer = &hevcState->m_brcDistortion->OsResource;
    pbData = (uint8_t*)pOsInterface->pfnLockResource(pOsInterface, pResBuffer, &LockFlagsReadOnly);
    CODECHAL_DEBUG_CHK_NULL(pbData);

    pbData += pBrcBuffers->dwMeBrcDistortionBottomFieldOffset;

    sts = (setBuffAdd)(pbData, HEVC_DISTORTION, handle);
    CODECHAL_DEBUG_CHK_DLLSTS(sts);

    pOsInterface->pfnUnlockResource(
        pOsInterface,
        pResBuffer);
    pbData = nullptr;

    if (Function == CODECHAL_MEDIA_STATE_BRC_INIT_RESET)
    {
        // Need only BRC Curbe, History and Distortion for init/reset kernel
        sts = (processAdd)(handle);
        CODECHAL_DEBUG_CHK_DLLSTS(sts);
        goto finish;
    }

    // Pak statistics buffer
    pResBuffer = &pBrcBuffers->resBrcPakStatisticBuffer[pBrcBuffers->uiCurrBrcPakStasIdxForRead];
    pbData = (uint8_t*)pOsInterface->pfnLockResource(pOsInterface, pResBuffer, &LockFlagsReadOnly);
    CODECHAL_DEBUG_CHK_NULL(pbData);

    sts = (setBuffAdd)(pbData, HEVC_PAK, handle);
    CODECHAL_DEBUG_CHK_DLLSTS(sts);

    pOsInterface->pfnUnlockResource(
        pOsInterface,
        pResBuffer);
    pbData = nullptr;

    if (pBrcBuffers->pMbStatisticsSurface)
    {
        // MB Pixel Statistics buffer
        pResBuffer = &pBrcBuffers->pMbStatisticsSurface->OsResource;
        pbData = (PBYTE)pOsInterface->pfnLockResource(pOsInterface, pResBuffer, &LockFlagsReadOnly);
        CODECHAL_DEBUG_CHK_NULL(pbData);

        sts = (setBuffAdd)(pbData, HEVC_STATISTICS, handle);
        CODECHAL_DEBUG_CHK_DLLSTS(sts);

        pOsInterface->pfnUnlockResource(
            pOsInterface,
            pResBuffer);
        pbData = nullptr;

        dwBrcPasses = BRC_IMG_STATE_SIZE_PER_PASS_G10;
    }

    if (pBrcBuffers->pMvAndDistortionSumSurface)
    {
        // HME Info buffer
        pResBuffer = &pBrcBuffers->pMvAndDistortionSumSurface->sResource;
        pbData = (PBYTE)pOsInterface->pfnLockResource(pOsInterface, pResBuffer, &LockFlagsReadOnly);
        CODECHAL_DEBUG_CHK_NULL(pbData);

        sts = (setBuffAdd)(pbData, HEVC_HMEINFO, handle);
        CODECHAL_DEBUG_CHK_DLLSTS(sts);

        pOsInterface->pfnUnlockResource(
            pOsInterface,
            pResBuffer);
        pbData = nullptr;
    }

    // PIC State Input
    pResBuffer = &pBrcBuffers->resBrcImageStatesReadBuffer[hevcState->m_currRecycledBufIdx];
    pbData = (uint8_t*)pOsInterface->pfnLockResource(pOsInterface, pResBuffer, &LockFlagsReadOnly);
    CODECHAL_DEBUG_CHK_NULL(pbData);

    sts = (setBuffAdd)(pbData, HEVC_IMGSTATEI, handle);
    CODECHAL_DEBUG_CHK_DLLSTS(sts);

    pWriteBuffer = &pBrcBuffers->resBrcImageStatesWriteBuffer[hevcState->m_currRecycledBufIdx];

    pwData = (uint8_t*)pOsInterface->pfnLockResource(pOsInterface, pWriteBuffer, &LockFlagsWriteOnly);
    CODECHAL_DEBUG_CHK_NULL(pwData);

    MOS_SecureMemcpy(pwData, dwBrcPasses * pHwInterface->GetMfxInterface()->GetBrcNumPakPasses(), pbData, dwBrcPasses * pHwInterface->GetMfxInterface()->GetBrcNumPakPasses());

    sts = (setBuffAdd)(pwData, HEVC_IMGSTATEO, handle);
    CODECHAL_DEBUG_CHK_DLLSTS(sts);

    pOsInterface->pfnUnlockResource(
        pOsInterface,
        pResBuffer);
    pbData = nullptr;

    pOsInterface->pfnUnlockResource(
        pOsInterface,
        pWriteBuffer);
    pwData = nullptr;

    // Combined ENC Buffer -- Output of BRC Kernel
    presBrcInputForEncKernels = (MOS_RESOURCE*)hevcState->m_allocator->GetResource(CODECHAL_HEVC, brcInputForEncKernel);

    pResBuffer = presBrcInputForEncKernels;
    pbData = (uint8_t*)pOsInterface->pfnLockResource(pOsInterface, pResBuffer, &LockFlagsReadOnly);
    CODECHAL_DEBUG_CHK_NULL(pbData);

    sts = (setBuffAdd)(pbData, HEVC_ENC, handle);
    CODECHAL_DEBUG_CHK_DLLSTS(sts);

    pOsInterface->pfnUnlockResource(
        pOsInterface,
        pResBuffer);
    pbData = nullptr;

    // Constant buffer
    pResBuffer = &pBrcBuffers->sBrcConstantDataBuffer[hevcState->m_currRecycledBufIdx].OsResource;
    pbData = (uint8_t*)pOsInterface->pfnLockResource(pOsInterface, pResBuffer, &LockFlagsReadOnly);
    CODECHAL_DEBUG_CHK_NULL(pbData);

    // Constant buffer pbData
    sts = (setBuffAdd)(pbData, HEVC_CONSTANT, handle);
    CODECHAL_DEBUG_CHK_DLLSTS(sts);

    pOsInterface->pfnUnlockResource(
        pOsInterface,
        pResBuffer);
    pbData = nullptr;

    // Call SW Update BRC
    sts = (processAdd)(handle);
    CODECHAL_DEBUG_CHK_DLLSTS(sts);

finish:
    if (pbData)
    {
        pOsInterface->pfnUnlockResource(
            pOsInterface,
            pResBuffer);
    }

    if (releaseInstanceAdd != nullptr)
    {
        (releaseInstanceAdd)(handle);
    }
    return eStatus;
}
#endif
*/

MOS_STATUS CodecHal_DbgCallHevcVdencSwBrcImpl(
    CodechalDebugInterface         *pDebugInterface,
    HMODULE                         swBrcHandle,
    CODECHAL_MEDIA_STATE_TYPE       Function,
    bool                            bIsResetOrLD,
    PMOS_RESOURCE                   presDmemBuffer,
    PMOS_RESOURCE                   presPakMmioBuffer,
    MHW_VDBOX_HUC_VIRTUAL_ADDR_PARAMS *pvirtualAddrParams)
{
    PMOS_INTERFACE                  pOsInterface = nullptr;
    PMOS_RESOURCE                   pResBuffer = nullptr;
    uint8_t                        *pbData = nullptr;
    uint32_t                       *pdwData = nullptr;
    uint8_t                        *pbAuxBuffer = nullptr;
    int                             sts = SUCCEED;
    uint32_t                        processSts = 0;
    void                            *handle = nullptr;
    MOS_STATUS                      eStatus = MOS_STATUS_SUCCESS;

    HevcVdencCreateInstance          createInstanceAdd = nullptr;
    HevcVdencSetBuff                 setBuffAdd;
    HevcVdencProcess                 processAdd;
    HevcVdencReleaseInstance         releaseInstanceAdd = nullptr;
    MOS_LOCK_PARAMS                 LockFlagsReadOnly;
    MOS_LOCK_PARAMS                 LockFlagsWriteOnly;

    HevcVdencBufferType              BufferTypeMap[16] = {
        HEVCVDENC_HISTORY_BUFF,              // Resion 0
        HEVCVDENC_VDENC_STATISTICS_BUFF,     // Resion 1
        HEVCVDENC_PAK_STATISTICS_BUFF,       // Resion 2
        HEVCVDENC_INPUT_SLBB_BUFF,           // Resion 3
        HEVCVDENC_CONSTANT_DATA_BUFF,        // Resion 4
        HEVCVDENC_OUTPUT_SLBB_BUFF,          // Resion 5
        HEVCVDENC_BRC_DATA_BUFF,             // Resion 6
        HEVCVDENC_SLICE_STATE_BUFF,          // Resion 7
        HEVCVDENC_PAKMMIO_BUFF,              // Resion 8
        HEVCVDENC_INPUT_STREAMIN_BUFF,       // Resion 9
        HEVCVDENC_INPUT_DELTAQP_BUFF,        // Resion 10
        HEVCVDENC_OUTPUT_STREAMIN_BUFF,      // Resion 11
        HEVCVDENC_UnknownBuff,               // Resion 12
        HEVCVDENC_UnknownBuff,               // Resion 13
        HEVCVDENC_UnknownBuff,               // Resion 14
        HEVCVDENC_AUX_BUFF                   // Resion 15
    };

    CODECHAL_DEBUG_FUNCTION_ENTER;

    CODECHAL_DEBUG_CHK_NULL(pDebugInterface);
    CODECHAL_DEBUG_CHK_NULL(pDebugInterface->m_osInterface);

    pOsInterface = pDebugInterface->m_osInterface;

    createInstanceAdd = (HevcVdencCreateInstance)MosUtilities::MosGetProcAddress(swBrcHandle, "HEVCBRC_CreateInstance");
    CODECHAL_DEBUG_CHK_NULL(createInstanceAdd);

    setBuffAdd = (HevcVdencSetBuff)MosUtilities::MosGetProcAddress(swBrcHandle, "HEVCBRC_SetBuff");
    CODECHAL_DEBUG_CHK_NULL(setBuffAdd);

    processAdd = (HevcVdencProcess)MosUtilities::MosGetProcAddress(swBrcHandle, "HEVCBRC_Process");
    CODECHAL_DEBUG_CHK_NULL(processAdd);

    releaseInstanceAdd = (HevcVdencReleaseInstance)MosUtilities::MosGetProcAddress(swBrcHandle, "HEVCBRC_ReleaseInstance");
    CODECHAL_DEBUG_CHK_NULL(releaseInstanceAdd);

    handle = (createInstanceAdd)();

    // initiate lock flags
    MOS_ZeroMemory(&LockFlagsReadOnly, sizeof(MOS_LOCK_PARAMS));
    LockFlagsReadOnly.ReadOnly = 1;
    MOS_ZeroMemory(&LockFlagsWriteOnly, sizeof(MOS_LOCK_PARAMS));
    LockFlagsWriteOnly.WriteOnly = 1;

    //-----------------------------------------------------------------------------------------------
    // BRC DMEM
    pbData = (uint8_t*)pOsInterface->pfnLockResource(pOsInterface, presDmemBuffer, &LockFlagsReadOnly);
    CODECHAL_DEBUG_CHK_NULL(pbData);

    sts = (setBuffAdd)((uint8_t *)pbData, HEVCVDENC_INLINE_DMEM, handle);
    CODECHAL_DEBUG_CHK_DLLSTS(sts);

    //-----------------------------------------------------------------------------------------------
    // Regions
    for (int regionIndex = 0; regionIndex < 16; regionIndex++)
    {
        if ((pvirtualAddrParams->regionParams[regionIndex].presRegion != nullptr) && 
            (BufferTypeMap[regionIndex] != HEVCVDENC_UnknownBuff))
        {
            MOS_LOCK_PARAMS *pLockFlags =
                pvirtualAddrParams->regionParams[regionIndex].isWritable ? &LockFlagsWriteOnly : &LockFlagsReadOnly;
            pResBuffer = pvirtualAddrParams->regionParams[regionIndex].presRegion;
            pbData = (uint8_t*)pOsInterface->pfnLockResource(pOsInterface, pResBuffer, pLockFlags);
            CODECHAL_DEBUG_CHK_NULL(pbData);

            sts = (setBuffAdd)(pbData, BufferTypeMap[regionIndex], handle);
            CODECHAL_DEBUG_CHK_DLLSTS(sts);
        }
    }

    //-----------------------------------------------------------------------------------------------
    // AUX buffer
    pbAuxBuffer = (uint8_t*)MOS_AllocAndZeroMemory(sizeof(HEVC_VDENC_HUC_AUX_BUFFER));
    CODECHAL_DEBUG_CHK_NULL(pbAuxBuffer);

    sts = (setBuffAdd)((uint8_t *)pbAuxBuffer, HEVCVDENC_AUX_BUFF, handle);
    CODECHAL_DEBUG_CHK_DLLSTS(sts);

    //-----------------------------------------------------------------------------------------------
    // process sw brc
    if (Function == CODECHAL_MEDIA_STATE_BRC_INIT_RESET)
    {
        processSts = bIsResetOrLD ? (processAdd)(handle, BRCReset) : (processAdd)(handle, BRCInit);
        CODECHAL_DEBUG_CHK_DLLSTS(processSts);
    }
    else
    {
        processSts = bIsResetOrLD ? (processAdd)(handle, BRCUpdateLD) : (processAdd)(handle, BRCUpdate);
        //CODECHAL_DEBUG_CHK_DLLSTS(sts);
        //printf("BRC DLL return %0x ~~~~~~\n", processSts);

        // update PAK MMIO buffer for conditional second pass
        pdwData = (uint32_t*)pOsInterface->pfnLockResource(pOsInterface, presPakMmioBuffer, &LockFlagsReadOnly);
        CODECHAL_DEBUG_CHK_NULL(pdwData);

        *pdwData = ((HEVC_VDENC_HUC_AUX_BUFFER *)pbAuxBuffer)->HuCStatus;
        //*(pdwData + 1) = CODECHAL_VDENC_HEVC_BRC_HUC_STATUS_REENCODE_MASK;

        //printf("*pdwData %0x \n", *pdwData); 
        *pdwData = processSts;
        //printf("*pdwData now %0x \n", *pdwData);

        if (((HEVC_VDENC_HUC_AUX_BUFFER *)pbAuxBuffer)->HuCStatus & CODECHAL_VDENC_HEVC_BRC_HUC_STATUS_REENCODE_MASK)
        {
            CODECHAL_DEBUG_NORMALMESSAGE("NumberPasses: 2");
        }

        pOsInterface->pfnUnlockResource(
            pOsInterface,
            presPakMmioBuffer);
    }

finish:
    MOS_SafeFreeMemory(pbAuxBuffer);

    for (int regionIndex = 0; regionIndex < 16; regionIndex++)
    {
        if ((pvirtualAddrParams->regionParams[regionIndex].presRegion != nullptr) &&
            (BufferTypeMap[regionIndex] != HEVCVDENC_UnknownBuff))
        {
            pResBuffer = pvirtualAddrParams->regionParams[regionIndex].presRegion;
            pOsInterface->pfnUnlockResource(
                pOsInterface,
                pResBuffer);
        }
    }

    pOsInterface->pfnUnlockResource(
        pOsInterface,
        presDmemBuffer);

    if (releaseInstanceAdd != nullptr)
    {
        (releaseInstanceAdd)(handle);
    }

    return eStatus;
}

/*
MOS_STATUS CodecHal_DbgCallSwLookaheadImpl(
    CodechalDebugInterface *           pDebugInterface,
    HMODULE                            swLaHandle,
    CODECHAL_MEDIA_STATE_TYPE          Function,
    PMOS_RESOURCE                      presDmemBuffer,
    PMOS_RESOURCE                      presPakMmioBuffer,
    MHW_VDBOX_HUC_VIRTUAL_ADDR_PARAMS *pvirtualAddrParams)
{
    PMOS_INTERFACE pOsInterface = nullptr;
    PMOS_RESOURCE  pResBuffer   = nullptr;
    uint8_t       *pbData       = nullptr;
    uint32_t      *pdwData      = nullptr;
    uint8_t *      pbAuxBuffer  = nullptr;
    int            sts          = SUCCEED;
    void          *handle       = nullptr;
    MOS_STATUS     eStatus      = MOS_STATUS_SUCCESS;

    LA_CreateInstance       createInstanceAdd = nullptr;
    LA_SetBuff              setBuffAdd;
    LA_Process              processAdd;
    LA_ReleaseInstance      releaseInstanceAdd = nullptr;
    MOS_LOCK_PARAMS         LockFlagsReadOnly;
    MOS_LOCK_PARAMS         LockFlagsWriteOnly;

    LABufferType BufferTypeMap[16] = {
        LA_HISTORY_BUFF,            // Resion 0
        LA_FRAME_STATISTICS_BUFF,   // Resion 1
        LA_OUTPUT_BUFF,             // Resion 2
        LA_UnknownBuff,             // Resion 3
        LA_UnknownBuff,             // Resion 4
        LA_UnknownBuff,             // Resion 5
        LA_UnknownBuff,             // Resion 6
        LA_UnknownBuff,             // Resion 7
        LA_UnknownBuff,             // Resion 8
        LA_UnknownBuff,             // Resion 9
        LA_UnknownBuff,             // Resion 10
        LA_UnknownBuff,             // Resion 11
        LA_UnknownBuff,             // Resion 12
        LA_UnknownBuff,             // Resion 13
        LA_UnknownBuff,             // Resion 14
        LA_UnknownBuff              // Resion 15
    };

    CODECHAL_DEBUG_FUNCTION_ENTER;

    CODECHAL_DEBUG_CHK_NULL(pDebugInterface);
    CODECHAL_DEBUG_CHK_NULL(pDebugInterface->m_osInterface);

    pOsInterface = pDebugInterface->m_osInterface;

    createInstanceAdd = (LA_CreateInstance)MosUtilities::MosGetProcAddress(swLaHandle, "LPLA_CreateInstance");
    CODECHAL_DEBUG_CHK_NULL(createInstanceAdd);

    setBuffAdd = (LA_SetBuff)MosUtilities::MosGetProcAddress(swLaHandle, "LPLA_SetBuff");
    CODECHAL_DEBUG_CHK_NULL(setBuffAdd);

    processAdd = (LA_Process)MosUtilities::MosGetProcAddress(swLaHandle, "LPLA_Process");
    CODECHAL_DEBUG_CHK_NULL(processAdd);

    releaseInstanceAdd = (LA_ReleaseInstance)MosUtilities::MosGetProcAddress(swLaHandle, "LPLA_ReleaseInstance");
    CODECHAL_DEBUG_CHK_NULL(releaseInstanceAdd);

    handle = (createInstanceAdd)();

    // initiate lock flags
    MOS_ZeroMemory(&LockFlagsReadOnly, sizeof(MOS_LOCK_PARAMS));
    LockFlagsReadOnly.ReadOnly = 1;
    MOS_ZeroMemory(&LockFlagsWriteOnly, sizeof(MOS_LOCK_PARAMS));
    LockFlagsWriteOnly.WriteOnly = 1;

    //-----------------------------------------------------------------------------------------------
    // BRC DMEM
    pbData = (uint8_t *)pOsInterface->pfnLockResource(pOsInterface, presDmemBuffer, &LockFlagsReadOnly);
    CODECHAL_DEBUG_CHK_NULL(pbData);

    sts = (setBuffAdd)((uint8_t *)pbData, LA_INLINE_DMEM, handle);
    CODECHAL_DEBUG_CHK_DLLSTS(sts);

    //-----------------------------------------------------------------------------------------------
    // Regions
    for (int regionIndex = 0; regionIndex < 16; regionIndex++)
    {
        if ((pvirtualAddrParams->regionParams[regionIndex].presRegion != nullptr) &&
            (BufferTypeMap[regionIndex] != LA_UnknownBuff))
        {
            MOS_LOCK_PARAMS *pLockFlags =
                pvirtualAddrParams->regionParams[regionIndex].isWritable ? &LockFlagsWriteOnly : &LockFlagsReadOnly;
            pResBuffer = pvirtualAddrParams->regionParams[regionIndex].presRegion;
            pbData     = (uint8_t *)pOsInterface->pfnLockResource(pOsInterface, pResBuffer, pLockFlags);
            CODECHAL_DEBUG_CHK_NULL(pbData);

            sts = (setBuffAdd)(pbData, BufferTypeMap[regionIndex], handle);
            CODECHAL_DEBUG_CHK_DLLSTS(sts);
        }
    }

    //-----------------------------------------------------------------------------------------------
    // AUX buffer
    pbAuxBuffer = (uint8_t *)MOS_AllocAndZeroMemory(sizeof(HEVC_VDENC_HUC_AUX_BUFFER));
    CODECHAL_DEBUG_CHK_NULL(pbAuxBuffer);

    sts = (setBuffAdd)((uint8_t *)pbAuxBuffer, LA_AUX_BUFF, handle);
    CODECHAL_DEBUG_CHK_DLLSTS(sts);

    //-----------------------------------------------------------------------------------------------
    // process sw brc
    if (Function == CODECHAL_MEDIA_STATE_BRC_INIT_RESET)
    {
        sts = (processAdd)(handle, LookaheadInit);
        CODECHAL_DEBUG_CHK_DLLSTS(sts);
    }
    else
    {
        sts = (processAdd)(handle, LookaheadUpdate);
        CODECHAL_DEBUG_CHK_DLLSTS(sts);

        // update PAK MMIO buffer for conditional second pass
        pdwData = (uint32_t *)pOsInterface->pfnLockResource(pOsInterface, presPakMmioBuffer, &LockFlagsReadOnly);
        CODECHAL_DEBUG_CHK_NULL(pdwData);

        *pdwData       = ((PLOOKAHEAD_HUC_AUX_BUFFER)pbAuxBuffer)->hucStatus;
        *(pdwData + 1) = CODECHAL_VDENC_HEVC_BRC_HUC_STATUS_REENCODE_MASK;

        pOsInterface->pfnUnlockResource(
            pOsInterface,
            presPakMmioBuffer);
    }

finish:
    MOS_SafeFreeMemory(pbAuxBuffer);

    for (int regionIndex = 0; regionIndex < 16; regionIndex++)
    {
        if ((pvirtualAddrParams->regionParams[regionIndex].presRegion != nullptr) &&
            (BufferTypeMap[regionIndex] != LA_UnknownBuff))
        {
            pResBuffer = pvirtualAddrParams->regionParams[regionIndex].presRegion;
            pOsInterface->pfnUnlockResource(
                pOsInterface,
                pResBuffer);
        }
    }

    pOsInterface->pfnUnlockResource(
        pOsInterface,
        presDmemBuffer);

    if (releaseInstanceAdd != nullptr)
    {
        (releaseInstanceAdd)(handle);
    }

    return eStatus;
}
*/

#endif // USE_CODECHAL_DEBUG_TOOL

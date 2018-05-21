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
//! \file     codechal_decode_sfc_avc.cpp
//! \brief    Implements the decode interface extension for CSC and scaling via SFC for AVC decoder.
//! \details  Downsampling in this case is supported by the SFC fixed function HW unit.
//!

#include "codechal_decode_sfc_avc.h"

MOS_STATUS CodechalAvcSfcState::CheckAndInitialize(
    PCODECHAL_DECODE_PROCESSING_PARAMS  decProcessingParams,
    PCODEC_AVC_PIC_PARAMS               picParams,
    uint32_t                            width,
    uint32_t                            height,
    bool                                deblockingEnabled)
{
    MOS_STATUS eStatus = MOS_STATUS_SUCCESS;
    uint8_t sfcPipeMode = MhwSfcInterface::SFC_PIPE_MODE_VDBOX;

    CODECHAL_HW_FUNCTION_ENTER;

    m_sfcPipeOut = false;

    if (CodecHal_PictureIsFrame(picParams->CurrPic) &&
        !picParams->seq_fields.mb_adaptive_frame_field_flag &&
        IsSfcOutputSupported(decProcessingParams, sfcPipeMode))
    {
        this->m_deblockingEnabled = deblockingEnabled;
        this->m_inputFrameWidth   = width;
        this->m_inputFrameHeight  = height;

        CODECHAL_HW_CHK_STATUS_RETURN(Initialize(
            decProcessingParams,
            sfcPipeMode));

        m_sfcPipeOut = true;
    }

    return eStatus;
}

MOS_STATUS CodechalAvcSfcState::UpdateInputInfo(
    PMHW_SFC_STATE_PARAMS   sfcStateParams)
{
    MOS_STATUS eStatus = MOS_STATUS_SUCCESS;

    CODECHAL_HW_FUNCTION_ENTER;

    if (m_sfcPipeMode == MhwSfcInterface::SFC_PIPE_MODE_VEBOX)
    {
        sfcStateParams->sfcPipeMode                = MEDIASTATE_SFC_PIPE_VE_TO_SFC;
        sfcStateParams->dwAVSFilterMode            = MEDIASTATE_SFC_AVS_FILTER_8x8;
        sfcStateParams->dwVDVEInputOrderingMode    = MEDIASTATE_SFC_INPUT_ORDERING_VE_4x8;
        sfcStateParams->dwInputChromaSubSampling   = MEDIASTATE_SFC_CHROMA_SUBSAMPLING_420;

        // Adjust SFC input surface alignment.
        // As VEBOX doesn't do scaling, input size equals to output size
        // For the VEBOX output to SFC, width is multiple of 16 and height is multiple of 4
        sfcStateParams->dwInputFrameWidth  = MOS_ALIGN_CEIL(m_inputSurface->dwWidth, m_sfcInterface->m_veWidthAlignment);
        sfcStateParams->dwInputFrameHeight = MOS_ALIGN_CEIL(m_inputSurface->dwHeight, m_sfcInterface->m_veHeightAlignment);

    }
    else if (m_sfcPipeMode == MhwSfcInterface::SFC_PIPE_MODE_VDBOX)
    {
        sfcStateParams->sfcPipeMode                = MEDIASTATE_SFC_PIPE_VD_TO_SFC;
        sfcStateParams->dwAVSFilterMode            = MEDIASTATE_SFC_AVS_FILTER_5x5;

        sfcStateParams->dwVDVEInputOrderingMode    = m_deblockingEnabled ? MEDIASTATE_SFC_INPUT_ORDERING_VD_16x16_SHIFT : MEDIASTATE_SFC_INPUT_ORDERING_VD_16x16_NOSHIFT;
        sfcStateParams->dwInputChromaSubSampling   = MEDIASTATE_SFC_CHROMA_SUBSAMPLING_420;

        sfcStateParams->dwInputFrameWidth  = m_inputFrameWidth;
        sfcStateParams->dwInputFrameHeight = m_inputFrameHeight;
    }
    else
    {
        CODECHAL_HW_ASSERTMESSAGE("AVC SFC pipe mode is wrong!");
    }

    return eStatus;
}

/*
* Copyright (c) 2023, Intel Corporation
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
//! \file     cmrt3dlut_defs.h
//! \brief    Definition for GEN12 SG1.
//!

#ifndef __CMRT3DLUT_DEFS_H__
#define __CMRT3DLUT_DEFS_H__

#include "igvpkrn_lut_isa_g12_tgllp.h"

#define BLOCK_WIDTH                       16
#define BLOCK_HEIGHT                      8

#define NUM_3DLUT_SURFACES                4
#define NUM_3DLUT_SAMPLERS                1

#define CURBEDATA_SIZE_3DLUT              36

#define KERNELNAME_3DLUT                  lut_sampler

typedef struct
{
    void     *m_cmSurfIn;
    void     *m_cmSurfOut;
    uint8_t  *m_cmInputLUTData;
    void     *m_cmSurfCoeff;
} LUTKernelSurfaceParams;

typedef struct
{
    float    dx;
    float    dy;
    float    src_chroma_sitting_x;
    float    src_chroma_sitting_y;
    uint32_t dest_info;
    uint32_t des_chroma_sitting;
    uint32_t segTableSize;
    uint32_t byteCountPerChannel;
    uint32_t channelCount;
} LUTKernelCurbeParams;

#endif

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
//! \file     cmrt3dlut_umd.cpp
//! \brief    MDF class for GEN12 SG1.
//!

#include "cmrt3dlut_umd.h"
#include "cmrt3dlut_defs.h"

Cmrt3DLutUmd::Cmrt3DLutUmd()
{
    m_isaName          = IGVP3DLUT_GENERATION_G12_DG1;
    m_isaSize          = IGVP3DLUT_GENERATION_G12_DG1_SIZE;

    m_cmSurface2DCount = 2;
    m_cmBufferCount    = 1;
    m_cmSurface3DCount = 1;
    m_cmSamplerCount   = 1;

    if (m_cmSurface2DCount > 0)
    {
        m_cmSurface2D     = (CmSurface2D **)malloc(sizeof(CmSurface2D *) * m_cmSurface2DCount);
        if (m_cmSurface2D != nullptr)
        {
            memset(m_cmSurface2D, 0, sizeof(CmSurface2D *) * m_cmSurface2DCount);
        }
    }

    if (m_cmBufferCount > 0)
    {
        m_cmBuffer        = (CmBuffer **)malloc(sizeof(CmBuffer *) * m_cmBufferCount);
        if (m_cmBuffer != nullptr)
        {
            memset(m_cmBuffer, 0, sizeof(CmBuffer *) * m_cmBufferCount);
        }
    }

    if (m_cmSurface3DCount > 0)
    {
        m_cmSurface3D     = (CmSurface3D **)malloc(sizeof(CmSurface3D *) * m_cmSurface3DCount);
        if (m_cmSurface3D != nullptr)
        {
            memset(m_cmSurface3D, 0, sizeof(CmSurface3D *) * m_cmSurface3DCount);
        }
    }

    if (m_cmSamplerCount > 0)
    {
        m_cmSampler       = (CmSampler **)malloc(sizeof(CmSampler *) * m_cmSamplerCount);
        if (m_cmSampler != nullptr)
        {
            memset(m_cmSampler, 0, sizeof(CmSampler *) * m_cmSamplerCount);
        }

	m_samplerIndex    = (SamplerIndex **)malloc(sizeof(SamplerIndex *) * m_cmSamplerCount);
	if (m_samplerIndex != nullptr)
	{
	    memset(m_samplerIndex, 0, sizeof(SamplerIndex *) * m_cmSamplerCount);
	}
    }

    m_surfIndex       = (SurfaceIndex **)malloc(sizeof(SurfaceIndex *) * (m_cmSurface2DCount + m_cmBufferCount + m_cmSurface3DCount));
    if (m_surfIndex != nullptr)
    {
        memset(m_surfIndex, 0, sizeof(SurfaceIndex *) * (m_cmSurface2DCount + m_cmBufferCount + m_cmSurface3DCount));
    }
}

Cmrt3DLutUmd::~Cmrt3DLutUmd()
{
    if (m_cmSurface2D)
    {
        free(m_cmSurface2D);
    }

    if (m_cmSurface3D)
    {
        free(m_cmSurface3D);
    }

    if (m_cmBuffer)
    {
        free(m_cmBuffer);
    }

    if (m_cmSampler)
    {
        free(m_cmSampler);
    }

    if (m_samplerIndex)
    {
        free(m_samplerIndex);
    }

    if (m_surfIndex)
    {
        free(m_surfIndex);
    }
}

CM_RETURN_CODE Cmrt3DLutUmd::SetupCurbe(void *curbe)
{
    m_curbe = curbe;
    return CM_SUCCESS;
}

CM_RETURN_CODE Cmrt3DLutUmd::CreateAndDispatchKernel(uint32_t width, uint32_t height, CmEvent *&cmEvent)
{
    CM_RETURN_CODE r = CM_SUCCESS;
    int32_t result;
    uint8_t i, idx = 0;
    uint32_t threadSpaceWidth, threadSpaceHeight;
    LUTKernelCurbeParams *curbe = (LUTKernelCurbeParams *)m_curbe;

    threadSpaceWidth = (width + BLOCK_WIDTH -1) / BLOCK_WIDTH;
    threadSpaceHeight = (height + BLOCK_HEIGHT -1) / BLOCK_HEIGHT;

    for (i = 0; i < NUM_3DLUT_SURFACES; i++)
    {
        CM_CHK_STATUS_RETURN(m_cmKernel->SetKernelArg(idx++, sizeof(SurfaceIndex), m_surfIndex[i]));
    }
    
    for (i = 0; i < NUM_3DLUT_SAMPLERS; i++)
    {
        CM_CHK_STATUS_RETURN(m_cmKernel->SetKernelArg(idx++, sizeof(SamplerIndex), m_samplerIndex[i]));
    }

    CM_CHK_STATUS_RETURN(m_cmKernel->SetKernelArg(idx++, sizeof(float), &curbe->dx));
    CM_CHK_STATUS_RETURN(m_cmKernel->SetKernelArg(idx++, sizeof(float), &curbe->dy));
    CM_CHK_STATUS_RETURN(m_cmKernel->SetKernelArg(idx++, sizeof(float), &curbe->src_chroma_sitting_x));
    CM_CHK_STATUS_RETURN(m_cmKernel->SetKernelArg(idx++, sizeof(float), &curbe->src_chroma_sitting_y));
    CM_CHK_STATUS_RETURN(m_cmKernel->SetKernelArg(idx++, sizeof(uint32_t), &curbe->dest_info));
    CM_CHK_STATUS_RETURN(m_cmKernel->SetKernelArg(idx++, sizeof(uint32_t), &curbe->des_chroma_sitting));
    CM_CHK_STATUS_RETURN(m_cmKernel->SetKernelArg(idx++, sizeof(uint32_t), &curbe->segTableSize));
    CM_CHK_STATUS_RETURN(m_cmKernel->SetKernelArg(idx++, sizeof(uint32_t), &curbe->byteCountPerChannel));
    CM_CHK_STATUS_RETURN(m_cmKernel->SetKernelArg(idx++, sizeof(uint32_t), &curbe->channelCount));

    CM_CHK_STATUS_RETURN(m_cmKernel->SetThreadCount(threadSpaceWidth * threadSpaceHeight));
    //create Thread Space
    result = CreateThreadSpace(threadSpaceWidth, threadSpaceHeight);
    if (result != CM_SUCCESS)
    {
        printf("CM Create ThreadSpace error : %d", result);
        return (CM_RETURN_CODE)result;
    }

    r = AddKernel(cmEvent);
#if 0
    uint32_t timeout = 20000;
    result = cmEvent->WaitForTaskFinished(-1);
    if (result != CM_SUCCESS) {
        printf("WaitForTaskFinished failed %d (%d)s\n", result, timeout /1000);
    }

    uint64_t executionTime = 0;
    result = cmEvent->GetExecutionTime(executionTime);
    if (result != CM_SUCCESS ) {
        printf("CM GetExecutionTime error %d\n", result);        
    } else {
        printf("Kernel execution time is: %8.2f ms\n", executionTime/1000000.0);
    }
#endif
    return r;
}

CM_RETURN_CODE Cmrt3DLutUmd::AllocateSurfaces(void *params)
{
    LUTKernelSurfaceParams *LUTParams = (LUTKernelSurfaceParams *)params;

    CM_CHK_STATUS_RETURN(m_cmDev->CreateSurface2D((MOS_RESOURCE *)LUTParams->m_cmSurfIn, m_cmSurface2D[0]));
    CM_CHK_STATUS_RETURN(m_cmSurface2D[0]->GetIndex(m_surfIndex[0]));

    CM_CHK_STATUS_RETURN(m_cmDev->CreateSurface2D((MOS_RESOURCE *)LUTParams->m_cmSurfOut, m_cmSurface2D[1]));
    CM_CHK_STATUS_RETURN(m_cmSurface2D[1]->GetIndex(m_surfIndex[1]));

    CM_CHK_STATUS_RETURN(m_cmDev->CreateSurface3D(65, 65, 65, CM_SURFACE_FORMAT_A16B16G16R16, m_cmSurface3D[0]));
    m_cmSurface3D[0]->WriteSurface(LUTParams->m_cmInputLUTData, NULL);
    CM_CHK_STATUS_RETURN(m_cmSurface3D[0]->GetIndex(m_surfIndex[2]));

    CM_CHK_STATUS_RETURN(m_cmDev->CreateBuffer((MOS_RESOURCE *)LUTParams->m_cmSurfCoeff, m_cmBuffer[0]));
    CM_CHK_STATUS_RETURN(m_cmBuffer[0]->GetIndex(m_surfIndex[3]));

    CM_SAMPLER_STATE samplerState;
    samplerState.magFilterType = CM_TEXTURE_FILTER_TYPE_LINEAR;
    samplerState.minFilterType = CM_TEXTURE_FILTER_TYPE_LINEAR;
    samplerState.addressU = CM_TEXTURE_ADDRESS_CLAMP;
    samplerState.addressV = CM_TEXTURE_ADDRESS_CLAMP;
    samplerState.addressW = CM_TEXTURE_ADDRESS_CLAMP;

    CM_CHK_STATUS_RETURN(m_cmDev->CreateSampler(samplerState, m_cmSampler[0]));
    CM_CHK_STATUS_RETURN(m_cmSampler[0]->GetIndex(m_samplerIndex[0]));

    m_cmKernel->SetSamplerBTI(m_samplerIndex[0], 1);
    m_cmKernel->SetSurfaceBTI(m_surfIndex[0], 16);
    m_cmKernel->SetSurfaceBTI(m_surfIndex[1], 18);
    m_cmKernel->SetSurfaceBTI(m_surfIndex[2], 20);
    m_cmKernel->SetSurfaceBTI(m_surfIndex[3], 21);
    
    return CM_SUCCESS;
}

CM_RETURN_CODE Cmrt3DLutUmd::UpdateSurfaces(void *params)
{
    LUTKernelSurfaceParams *LUTParams = (LUTKernelSurfaceParams *)params;

    CM_CHK_STATUS_RETURN(m_cmDev->UpdateSurface2D((MOS_RESOURCE *)LUTParams->m_cmSurfIn, m_cmSurface2D[0]));

    CM_CHK_STATUS_RETURN(m_cmDev->UpdateSurface2D((MOS_RESOURCE *)LUTParams->m_cmSurfOut, m_cmSurface2D[1]));

    return CM_SUCCESS;
}


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
//! \file     cmrt3dlut_base.cpp
//! \brief    MDF structure base class for GEN12 SG1.
//!

#include "cmrt3dlut_base.h"

Cmrt3DLutBase::Cmrt3DLutBase()
{
    m_cmDev              = nullptr;
    m_cmProgram          = nullptr;
    m_cmQueue            = nullptr;
    m_cmTask             = nullptr;       //Can be reused for each kernel
    m_cmThreadSpace      = nullptr;
    m_cmKernel           = nullptr;
    m_cmSurface2D        = nullptr;
    m_cmSurface3D        = nullptr;
    m_cmSampler          = nullptr;
    m_cmBuffer           = nullptr;
    m_samplerIndex       = nullptr;
    m_surfIndex          = nullptr;
    m_isaName            = nullptr;
    m_curbe              = nullptr;
    m_isaSize            = 0;
    m_cmSurface2DCount   = 0;
    m_cmSurface3DCount   = 0;
    m_cmSamplerCount     = 0;
    m_cmBufferCount      = 0;
}

Cmrt3DLutBase::~Cmrt3DLutBase()
{
}

CM_RETURN_CODE Cmrt3DLutBase::LoadProgramISA(const uint32_t *isaCode, uint32_t isaSize, CmProgram * &program)
{
    int32_t result;

    // Load Program
    result = m_cmDev->LoadProgram((void *)isaCode, isaSize, program, "-nojitter");
    if (result != CM_SUCCESS)
    {
        printf("MDF LoadProgram error: %d\n", result);
    }

    return CM_SUCCESS;

}

CM_RETURN_CODE Cmrt3DLutBase::Init(void *osContext, CmDevice *cmDev, CmQueue *cmQueue, CmTask *cmTask, CmProgram *cmProgram)
{
    int32_t result;

    if (cmDev)
    {
        m_cmDev = cmDev;
    }
    else
    {
        result = CreateCmDevice((PMOS_CONTEXT)osContext, m_cmDev, 0);
        if (result != CM_SUCCESS)
        {
            printf("CmDevice creation error\n");
            return CM_FAILURE;
        }
    }

    if (cmQueue)
    {
        m_cmQueue = cmQueue;
    }
    else
    {
        result = m_cmDev->CreateQueue(m_cmQueue);
        if (result != CM_SUCCESS)
        {
            printf("CM CreateQueue error\n");
            return CM_FAILURE;
        }
    }

    if (cmTask)
    {
        m_cmTask = cmTask;
    }
    else
    {
        result = m_cmDev->CreateTask(m_cmTask);
        if (result != CM_SUCCESS)
        {
            printf("CmDevice CreateTask error\n");
            return CM_FAILURE;
        }
    }

    if (cmProgram)
    {
        m_cmProgram = cmProgram;
    }
    else
    {
        result = LoadProgramISA(m_isaName, m_isaSize, m_cmProgram);
        if (result != CM_SUCCESS)
        {
            printf("CmDevice LoadProgramISA error\n");
            return CM_FAILURE;
        }
    }

    result = m_cmDev->CreateKernel(m_cmProgram, CM_KERNEL_FUNCTION(lut_sampler), m_cmKernel);
    if (result != CM_SUCCESS)
    {
        printf("CmDevice CreateKernel error\n");
        return CM_FAILURE;
    }

    return CM_SUCCESS;
}

int32_t Cmrt3DLutBase::CreateThreadSpace(uint32_t threadSpaceWidth, uint32_t threadSpaceHeight)
{
    int32_t result = CM_SUCCESS;

    if (!m_cmThreadSpace)
    {
        result = m_cmDev->CreateThreadGroupSpace(1, 1, threadSpaceWidth, threadSpaceHeight, m_cmThreadSpace);
        if (result != CM_SUCCESS)
        {
            printf("CmDevice CreateThreadGroupSpace error : %d", result);
            return (CM_RETURN_CODE)result;
        }

        result = m_cmKernel->AssociateThreadGroupSpace(m_cmThreadSpace);        
        if (result != CM_SUCCESS)
        {
            printf("CmKernel AssociateThreadGroupSpace error : %d", result);
            return (CM_RETURN_CODE)result;
        }                
    }
    else
    {
        result = m_cmKernel->AssociateThreadGroupSpace(m_cmThreadSpace);
        if (result != CM_SUCCESS)
        {
            printf("CmKernel AssociateThreadGroupSpace error : %d", result);
            return (CM_RETURN_CODE)result;
        }
    }

    return result;
}

CM_RETURN_CODE Cmrt3DLutBase::AddKernel(CmEvent *&cmEvent)
{
    if (m_cmTask == nullptr)
    {
        CM_CHK_STATUS_RETURN(m_cmDev->CreateTask(m_cmTask));
    }

    if (m_cmQueue == nullptr)
    {
        CM_CHK_STATUS_RETURN(m_cmDev->CreateQueue(m_cmQueue));//CreateQueue is just get queue of CmDev, so just need call once.
    }

    CM_CHK_STATUS_RETURN(m_cmTask->AddKernel(m_cmKernel));

    CM_CHK_STATUS_RETURN(m_cmQueue->EnqueueWithGroup(m_cmTask, cmEvent, m_cmThreadSpace));

    CM_CHK_STATUS_RETURN(m_cmTask->Reset());

    return CM_SUCCESS;
}

CM_RETURN_CODE Cmrt3DLutBase::WaitAndDestroyEvent(CmEvent *&cmEvent)
{
    int32_t dwTimeOutMs = -1;

    CM_CHK_STATUS_RETURN(cmEvent->WaitForTaskFinished(dwTimeOutMs));

    CM_CHK_STATUS_RETURN(m_cmQueue->DestroyEvent(cmEvent));
    cmEvent = nullptr;

    return CM_SUCCESS;
}

void Cmrt3DLutBase::DestroySurfResources()
{
    uint32_t i = 0;

    for (i = 0; i < m_cmSurface2DCount; i++)
    {
        if (m_cmSurface2D[i])
        {
            m_cmDev->DestroySurface(m_cmSurface2D[i]);
            m_cmSurface2D[i] = nullptr;
        }
    }

    for (i = 0; i < m_cmSurface3DCount; i++)
    {
        if (m_cmSurface3D[i])
        {
            m_cmDev->DestroySurface(m_cmSurface3D[i]);
            m_cmSurface3D[i] = nullptr;
        }
    }

    for (i = 0; i < m_cmSamplerCount; i++)
    {
        if (m_cmSampler[i])
        {
            m_cmDev->DestroySampler(m_cmSampler[i]);
            m_cmSampler[i] = nullptr;
        }
    }

    for (i = 0; i < m_cmBufferCount; i++)
    {
        if (m_cmBuffer[i])
        {
            m_cmDev->DestroySurface(m_cmBuffer[i]);
            m_cmBuffer[i] = nullptr;
        }
    }
}

void Cmrt3DLutBase::DestroyKernelResources()
{
    if(m_cmKernel)
    {
        m_cmDev->DestroyKernel(m_cmKernel);
        m_cmKernel = nullptr;
    }

    if (m_cmThreadSpace)
    {
        m_cmDev->DestroyThreadGroupSpace(m_cmThreadSpace);
        m_cmThreadSpace = nullptr;
    }
}

void Cmrt3DLutBase::DestroyProgramResources()
{
    if(m_cmProgram)
    {
        m_cmDev->DestroyProgram(m_cmProgram);
        m_cmProgram = nullptr;
    }
}

void Cmrt3DLutBase::Destroy()
{
    if (m_cmTask)
    {
        m_cmDev->DestroyTask(m_cmTask);
        m_cmTask = nullptr;
    }

    if(m_cmDev)
    {
        DestroyCmDevice(m_cmDev);
        m_cmDev = nullptr;
    }
}


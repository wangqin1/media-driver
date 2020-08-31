/*
* Copyright (c) 2020, Intel Corporation
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
//! \file     codechal_fei_avc_g12.h
//! \brief    This file defines the C++ class/interface for Gen12 platform's AVC
//!           FEI encoding to be used across CODECHAL components.
//!

#ifndef __CODECHAL_FEI_AVC_G12_H__
#define __CODECHAL_FEI_AVC_G12_H__

#include "codechal_encode_avc_g12.h"

typedef struct _CODECHAL_ENCODE_AVC_KERNEL_HEADER_FEI_G12 {
    int nKernelCount;
    // FEI mode for Frame/Field
    CODECHAL_KERNEL_HEADER AVCMBEnc_Fei_I;
    CODECHAL_KERNEL_HEADER AVCMBEnc_Fei_P;
    CODECHAL_KERNEL_HEADER AVCMBEnc_Fei_B;
    // PreProc
    CODECHAL_KERNEL_HEADER AVC_Fei_ProProc;
    // HME
    CODECHAL_KERNEL_HEADER AVC_ME_P;
    CODECHAL_KERNEL_HEADER AVC_ME_B;
    // DownScaling
    CODECHAL_KERNEL_HEADER PLY_DScale_PLY;
    CODECHAL_KERNEL_HEADER PLY_DScale_2f_PLY_2f;
    // BRC_I Frame Distortion
    CODECHAL_KERNEL_HEADER BRC_IFrame_Dist;
    //Weighted Prediction Kernel
    CODECHAL_KERNEL_HEADER AVC_WeightedPrediction;

} CODECHAL_ENCODE_AVC_KERNEL_HEADER_FEI_G12, *PCODECHAL_ENCODE_AVC_KERNEL_HEADER_FEI_G12;

typedef enum _CODECHAL_ENCODE_AVC_BINDING_TABLE_OFFSET_ME_CM_G12
{
    CODECHAL_ENCODE_AVC_ME_MV_DATA_SURFACE_CM_G12                     =  0,
    CODECHAL_ENCODE_AVC_16xME_MV_DATA_SURFACE_CM_G12                  =  1,
    CODECHAL_ENCODE_AVC_32xME_MV_DATA_SURFACE_CM_G12                  =  1,
    CODECHAL_ENCODE_AVC_ME_DISTORTION_SURFACE_CM_G12                  =  2,
    CODECHAL_ENCODE_AVC_ME_BRC_DISTORTION_CM_G12                      =  3,
    CODECHAL_ENCODE_AVC_ME_RESERVED0_CM_G12                           =  4,
    CODECHAL_ENCODE_AVC_ME_CURR_FOR_FWD_REF_CM_G12                    =  5,
    CODECHAL_ENCODE_AVC_ME_FWD_REF_IDX0_CM_G12                        =  6,
    CODECHAL_ENCODE_AVC_ME_RESERVED1_CM_G12                           =  7,
    CODECHAL_ENCODE_AVC_ME_FWD_REF_IDX1_CM_G12                        =  8,
    CODECHAL_ENCODE_AVC_ME_RESERVED2_CM_G12                           =  9,
    CODECHAL_ENCODE_AVC_ME_FWD_REF_IDX2_CM_G12                        = 10,
    CODECHAL_ENCODE_AVC_ME_RESERVED3_CM_G12                           = 11,
    CODECHAL_ENCODE_AVC_ME_FWD_REF_IDX3_CM_G12                        = 12,
    CODECHAL_ENCODE_AVC_ME_RESERVED4_CM_G12                           = 13,
    CODECHAL_ENCODE_AVC_ME_FWD_REF_IDX4_CM_G12                        = 14,
    CODECHAL_ENCODE_AVC_ME_RESERVED5_CM_G12                           = 15,
    CODECHAL_ENCODE_AVC_ME_FWD_REF_IDX5_CM_G12                        = 16,
    CODECHAL_ENCODE_AVC_ME_RESERVED6_CM_G12                           = 17,
    CODECHAL_ENCODE_AVC_ME_FWD_REF_IDX6_CM_G12                        = 18,
    CODECHAL_ENCODE_AVC_ME_RESERVED7_CM_G12                           = 19,
    CODECHAL_ENCODE_AVC_ME_FWD_REF_IDX7_CM_G12                        = 20,
    CODECHAL_ENCODE_AVC_ME_RESERVED8_CM_G12                           = 21,
    CODECHAL_ENCODE_AVC_ME_CURR_FOR_BWD_REF_CM_G12                    = 22,
    CODECHAL_ENCODE_AVC_ME_BWD_REF_IDX0_CM_G12                        = 23,
    CODECHAL_ENCODE_AVC_ME_RESERVED9_CM_G12                           = 24,
    CODECHAL_ENCODE_AVC_ME_BWD_REF_IDX1_CM_G12                        = 25,
//    CODECHAL_ENCODE_AVC_ME_VDENC_STREAMIN_OUTPUT_BUFFER_CM_G12        = 26,
//    CODECHAL_ENCODE_AVC_ME_VDENC_STREAMIN_INPUT_BUFFER_CM_G12         = 27,
//    CODECHAL_ENCODE_AVC_ME_SUM_MV_AND_DISTORTION_BUFFER_CM_G12        = 28,
    CODECHAL_ENCODE_AVC_ME_NUM_SURFACES_CM_G12                        = 26
} CODECHAL_ENCODE_AVC_BINDING_TABLE_OFFSET_ME_CM_G12;

typedef enum _CODECHAL_ENCODE_AVC_BINDING_TABLE_OFFSET_PREPROC_CM_G12
{
    CODECHAL_ENCODE_AVC_PREPROC_CURR_Y_CM_G12                         =  0,
    CODECHAL_ENCODE_AVC_PREPROC_CURR_UV_CM_G12                        =  1,
    CODECHAL_ENCODE_AVC_PREPROC_HME_MV_DATA_CM_G12                    =  2,
    CODECHAL_ENCODE_AVC_PREPROC_MV_PREDICTOR_CM_G12                   =  3,
    CODECHAL_ENCODE_AVC_PREPROC_MBQP_CM_G12                           =  4,
    CODECHAL_ENCODE_AVC_PREPROC_MV_DATA_CM_G12                        =  5,
    CODECHAL_ENCODE_AVC_PREPROC_MB_STATS_CM_G12                       =  6,
    CODECHAL_ENCODE_AVC_PREPROC_VME_CURR_PIC_IDX_0_CM_G12             =  7,
    CODECHAL_ENCODE_AVC_PREPROC_VME_FWD_PIC_IDX0_CM_G12               =  8,
    CODECHAL_ENCODE_AVC_PREPROC_VME_BWD_PIC_IDX0_0_CM_G12             =  9,
    CODECHAL_ENCODE_AVC_PREPROC_VME_CURR_PIC_IDX_1_CM_G12             = 10,
    CODECHAL_ENCODE_AVC_PREPROC_VME_BWD_PIC_IDX0_1_CM_G12             = 11,
    CODECHAL_ENCODE_AVC_PREPROC_RESERVED1_CM_G12                      = 12,
    CODECHAL_ENCODE_AVC_PREPROC_FTQ_LUT_CM_G12                        = 13,
    CODECHAL_ENCODE_AVC_PREPROC_NUM_SURFACES_CM_G12                   = 14
} CODECHAL_ENCODE_AVC_BINDING_TABLE_OFFSET_PREPROC_CM_G12;

typedef enum _CODECHAL_ENCODE_AVC_BINDING_TABLE_OFFSET_PREPROC_FIELD_CM_G12
{
    CODECHAL_ENCODE_AVC_PREPROC_VME_FIELD_CURR_PIC_IDX_0_CM_G12       =  7,
    CODECHAL_ENCODE_AVC_PREPROC_VME_FIELD_FWD_PIC_IDX0_0_CM_G12       =  8,
    CODECHAL_ENCODE_AVC_PREPROC_FIELD_RESERVED0_CM_G12                =  9,
    CODECHAL_ENCODE_AVC_PREPROC_VME_FIELD_FWD_PIC_IDX0_1_CM_G12       = 10,
    CODECHAL_ENCODE_AVC_PREPROC_FIELD_RESERVED1_CM_G12                = 11,
    CODECHAL_ENCODE_AVC_PREPROC_VME_FIELD_CURR_PIC_IDX_1_CM_G12       = 12,
    CODECHAL_ENCODE_AVC_PREPROC_VME_FIELD_BWD_PIC_IDX0_0_CM_G12       = 13,
    CODECHAL_ENCODE_AVC_PREPROC_FIELD_RESERVED2_CM_G12                = 14,
    CODECHAL_ENCODE_AVC_PREPROC_VME_FIELD_BWD_PIC_IDX0_1_CM_G12       = 15,
    CODECHAL_ENCODE_AVC_PREPROC_FIELD_RESERVED3_CM_G12                = 16,
    CODECHAL_ENCODE_AVC_PREPROC_FIELD_FTQ_LUT_CM_G12                  = 17,
    CODECHAL_ENCODE_AVC_PREPROC_FIELD_NUM_SURFACES_CM_G12             = 18
} CODECHAL_ENCODE_AVC_BINDING_TABLE_OFFSET_PREPROC_FIELD_CM_G12;

typedef struct _CODECHAL_ENCODE_AVC_ME_CURBE_CM_FEI_G12
{
    // DW0
    union
    {
        struct
        {
            uint32_t   SkipModeEn                      : MOS_BITFIELD_BIT(       0 );
            uint32_t   AdaptiveEn                      : MOS_BITFIELD_BIT(       1 );
            uint32_t   BiMixDis                        : MOS_BITFIELD_BIT(       2 );
            uint32_t   reserved3                       : MOS_BITFIELD_RANGE(  3, 4 );
            uint32_t   EarlyImeSuccessEn               : MOS_BITFIELD_BIT(       5 );
            uint32_t   reserved6                       : MOS_BITFIELD_BIT(       6 );
            uint32_t   T8x8FlagForInterEn              : MOS_BITFIELD_BIT(       7 );
            uint32_t   reserved8                       : MOS_BITFIELD_RANGE(  8,23 );
            uint32_t   EarlyImeStop                    : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW0;

    // DW1
    union
    {
        struct
        {
            uint32_t   MaxNumMVs                       : MOS_BITFIELD_RANGE(  0, 5 );
            uint32_t   reserved6                       : MOS_BITFIELD_RANGE(  6,15 );
            uint32_t   BiWeight                        : MOS_BITFIELD_RANGE( 16,21 );
            uint32_t   reserved22                      : MOS_BITFIELD_RANGE( 22,27 );
            uint32_t   UniMixDisable                   : MOS_BITFIELD_BIT(      28 );
            uint32_t   reserved29                      : MOS_BITFIELD_RANGE( 29,31 );
        };
        uint32_t       Value;
    } DW1;

    // DW2
    union
    {
        struct
        {
            uint32_t   LenSP                           : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   MaxNumSU                        : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   reserved16                      : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW2;

    // DW3
    union
    {
        struct
        {
            uint32_t   SrcSize                         : MOS_BITFIELD_RANGE(  0, 1 );
            uint32_t   reserved2                       : MOS_BITFIELD_RANGE(  2, 3 );
            uint32_t   MbTypeRemap                     : MOS_BITFIELD_RANGE(  4, 5 );
            uint32_t   SrcAccess                       : MOS_BITFIELD_BIT(       6 );
            uint32_t   RefAccess                       : MOS_BITFIELD_BIT(       7 );
            uint32_t   SearchCtrl                      : MOS_BITFIELD_RANGE(  8,10 );
            uint32_t   DualSearchPathOption            : MOS_BITFIELD_BIT(      11 );
            uint32_t   SubPelMode                      : MOS_BITFIELD_RANGE( 12,13 );
            uint32_t   SkipType                        : MOS_BITFIELD_BIT(      14 );
            uint32_t   DisableFieldCacheAlloc          : MOS_BITFIELD_BIT(      15 );
            uint32_t   InterChromaMode                 : MOS_BITFIELD_BIT(      16 );
            uint32_t   FTEnable                        : MOS_BITFIELD_BIT(      17 );
            uint32_t   BMEDisableFBR                   : MOS_BITFIELD_BIT(      18 );
            uint32_t   BlockBasedSkipEnable            : MOS_BITFIELD_BIT(      19 );
            uint32_t   InterSAD                        : MOS_BITFIELD_RANGE( 20,21 );
            uint32_t   IntraSAD                        : MOS_BITFIELD_RANGE( 22,23 );
            uint32_t   SubMbPartMask                   : MOS_BITFIELD_RANGE( 24,30 );
            uint32_t   reserved31                      : MOS_BITFIELD_BIT(      31 );
        };
        uint32_t       Value;
    } DW3;

    // DW4
    union
    {
        struct
        {
            uint32_t   reserved0                       : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   PictureHeightMinus1             : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   PictureWidth                    : MOS_BITFIELD_RANGE( 16,23 );
            uint32_t   reserved24                      : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW4;

    // DW5
    union
    {
        struct
        {
            uint32_t   SumMVThreshold                  : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   QpPrimeY                        : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   RefWidth                        : MOS_BITFIELD_RANGE( 16,23 );
            uint32_t   RefHeight                       : MOS_BITFIELD_RANGE( 24,31 );

        };
        uint32_t       Value;
    } DW5;

    // DW6
    union
    {
        struct
        {
	    uint32_t   reserved0                       : MOS_BITFIELD_BIT(       0 );
            uint32_t   InputStreamInEn                 : MOS_BITFIELD_BIT(       1 );
            uint32_t   LCUSize                         : MOS_BITFIELD_BIT(       2 );
            uint32_t   WriteDistortions                : MOS_BITFIELD_BIT(       3 );
            uint32_t   UseMvFromPrevStep               : MOS_BITFIELD_BIT(       4 );
            uint32_t   BRCEnable                       : MOS_BITFIELD_BIT(       5 );
            uint32_t   reserved5                       : MOS_BITFIELD_RANGE(  6, 7 );
            uint32_t   SuperCombineDist                : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   MaxVmvR                         : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW6;

    // DW7
    union
    {
        struct
        {
            uint32_t   reserved0                       : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   MVCostScaleFactor               : MOS_BITFIELD_RANGE( 16,17 );
            uint32_t   BilinearEnable                  : MOS_BITFIELD_BIT(      18 );
            uint32_t   SrcFieldPolarity                : MOS_BITFIELD_BIT(      19 );
            uint32_t   WeightedSADHAAR                 : MOS_BITFIELD_BIT(      20 );
            uint32_t   AConlyHAAR                      : MOS_BITFIELD_BIT(      21 );
            uint32_t   RefIDCostMode                   : MOS_BITFIELD_BIT(      22 );
            uint32_t   reserved23                      : MOS_BITFIELD_BIT(      23 );
            uint32_t   SkipCenterMask                  : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW7;

    // DW8
    union
    {
        struct
        {
            uint32_t   Mode0Cost                       : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   Mode1Cost                       : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   Mode2Cost                       : MOS_BITFIELD_RANGE( 16,23 );
            uint32_t   Mode3Cost                       : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW8;

    // DW9
    union
    {
        struct
        {
            uint32_t   Mode4Cost                       : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   Mode5Cost                       : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   Mode6Cost                       : MOS_BITFIELD_RANGE( 16,23 );
            uint32_t   Mode7Cost                       : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW9;

    // DW10
    union
    {
        struct
        {
            uint32_t   Mode8Cost                       : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   Mode9Cost                       : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   RefIDCost                       : MOS_BITFIELD_RANGE( 16,23 );
            uint32_t   ChromaIntraModeCost             : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW10;

    // DW11
    union
    {
        struct
        {
            uint32_t   MV0Cost                         : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   MV1Cost                         : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   MV2Cost                         : MOS_BITFIELD_RANGE( 16,23 );
            uint32_t   MV3Cost                         : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW11;

    // DW12
    union
    {
        struct
        {
            uint32_t   MV4Cost                         : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   MV5Cost                         : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   MV6Cost                         : MOS_BITFIELD_RANGE( 16,23 );
            uint32_t   MV7Cost                         : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW12;

    // DW13
    union
    {
        struct
        {
            uint32_t   NumRefIdxL0MinusOne             : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   NumRefIdxL1MinusOne             : MOS_BITFIELD_RANGE(  8,15 );
	    uint32_t   RefStreaminCost                 : MOS_BITFIELD_RANGE( 16,23 );
            uint32_t   ROIEnable                       : MOS_BITFIELD_RANGE( 24,26 );
            uint32_t   reserved27                      : MOS_BITFIELD_RANGE( 27,31 );
        };
        uint32_t       Value;
    } DW13;

    // DW14
    union
    {
        struct
        {
            uint32_t   List0RefID0FieldParity          : MOS_BITFIELD_BIT(       0 );
            uint32_t   List0RefID1FieldParity          : MOS_BITFIELD_BIT(       1 );
            uint32_t   List0RefID2FieldParity          : MOS_BITFIELD_BIT(       2 );
            uint32_t   List0RefID3FieldParity          : MOS_BITFIELD_BIT(       3 );
            uint32_t   List0RefID4FieldParity          : MOS_BITFIELD_BIT(       4 );
            uint32_t   List0RefID5FieldParity          : MOS_BITFIELD_BIT(       5 );
            uint32_t   List0RefID6FieldParity          : MOS_BITFIELD_BIT(       6 );
            uint32_t   List0RefID7FieldParity          : MOS_BITFIELD_BIT(       7 );
            uint32_t   List1RefID0FieldParity          : MOS_BITFIELD_BIT(       8 );
            uint32_t   List1RefID1FieldParity          : MOS_BITFIELD_BIT(       9 );
            uint32_t   reserved10                      : MOS_BITFIELD_RANGE( 10,31 );
        };
        uint32_t       Value;
    } DW14;

    // DW15
    union
    {
        struct
        {
            uint32_t   PrevMvReadPosFactor             : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   MvShiftFactor                   : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   Reserved                        : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW15;

    struct
    {
        // DW16
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_0;
                SearchPathDelta   SPDelta_1;
                SearchPathDelta   SPDelta_2;
                SearchPathDelta   SPDelta_3;
            };
            uint32_t   Value;
        } DW16;

        // DW17
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_4;
                SearchPathDelta   SPDelta_5;
                SearchPathDelta   SPDelta_6;
                SearchPathDelta   SPDelta_7;
            };
            uint32_t   Value;
        } DW17;

        // DW18
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_8;
                SearchPathDelta   SPDelta_9;
                SearchPathDelta   SPDelta_10;
                SearchPathDelta   SPDelta_11;
            };
            uint32_t   Value;
        } DW18;

        // DW19
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_12;
                SearchPathDelta   SPDelta_13;
                SearchPathDelta   SPDelta_14;
                SearchPathDelta   SPDelta_15;
            };
            uint32_t   Value;
        } DW19;

        // DW20
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_16;
                SearchPathDelta   SPDelta_17;
                SearchPathDelta   SPDelta_18;
                SearchPathDelta   SPDelta_19;
            };
            uint32_t   Value;
        } DW20;

        // DW21
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_20;
                SearchPathDelta   SPDelta_21;
                SearchPathDelta   SPDelta_22;
                SearchPathDelta   SPDelta_23;
            };
            uint32_t   Value;
        } DW21;

        // DW22
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_24;
                SearchPathDelta   SPDelta_25;
                SearchPathDelta   SPDelta_26;
                SearchPathDelta   SPDelta_27;
            };
            uint32_t   Value;
        } DW22;

        // DW23
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_28;
                SearchPathDelta   SPDelta_29;
                SearchPathDelta   SPDelta_30;
                SearchPathDelta   SPDelta_31;
            };
            uint32_t   Value;
        } DW23;

        // DW24
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_32;
                SearchPathDelta   SPDelta_33;
                SearchPathDelta   SPDelta_34;
                SearchPathDelta   SPDelta_35;
            };
            uint32_t   Value;
        } DW24;

        // DW25
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_36;
                SearchPathDelta   SPDelta_37;
                SearchPathDelta   SPDelta_38;
                SearchPathDelta   SPDelta_39;
            };
            uint32_t   Value;
        } DW25;

        // DW26
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_40;
                SearchPathDelta   SPDelta_41;
                SearchPathDelta   SPDelta_42;
                SearchPathDelta   SPDelta_43;
            };
            uint32_t   Value;
        } DW26;

        // DW27
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_44;
                SearchPathDelta   SPDelta_45;
                SearchPathDelta   SPDelta_46;
                SearchPathDelta   SPDelta_47;
            };
            uint32_t   Value;
        } DW27;

        // DW28
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_48;
                SearchPathDelta   SPDelta_49;
                SearchPathDelta   SPDelta_50;
                SearchPathDelta   SPDelta_51;
            };
            uint32_t   Value;
        } DW28;

        // DW29
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_52;
                SearchPathDelta   SPDelta_53;
                SearchPathDelta   SPDelta_54;
                SearchPathDelta   SPDelta_55;
            };
            uint32_t   Value;
        } DW29;
    } SPDelta;

    // DW30
    union
    {
        struct
        {
	    uint32_t   ActualMBWidth                   : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   ActualMBHeight                  : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW30;

    // DW31
    union
    {
        struct
        {
            uint32_t   RoiCtrl                         : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   MaxTuSize                       : MOS_BITFIELD_RANGE(  8, 9 );
            uint32_t   MaxCuSize                       : MOS_BITFIELD_RANGE( 10,11 );
            uint32_t   NumImePredictors                : MOS_BITFIELD_RANGE( 12,15 );
            uint32_t   Reserved                        : MOS_BITFIELD_RANGE( 16,23 );
            uint32_t   PuTypeCtrl                      : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW31;

    // DW32
    union
    {
        struct
        {
            uint32_t   ForceMvx0                       : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   ForceMvy0                       : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW32;

    // DW33
    union
    {
        struct
        {
            uint32_t   ForceMvx1                       : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   ForceMvy1                       : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW33;

    // DW34
    union
    {
        struct
        {
            uint32_t   ForceMvx2                       : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   ForceMvy2                       : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW34;

    // DW35
    union
    {
        struct
        {
            uint32_t   ForceMvx3                       : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   ForceMvy3                       : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW35;

    // DW36
    union
    {
        struct
        {
            uint32_t   ForceRefIdx0                    : MOS_BITFIELD_RANGE(  0, 3 );
            uint32_t   ForceRefIdx1                    : MOS_BITFIELD_RANGE(  4, 7 );
            uint32_t   ForceRefIdx2                    : MOS_BITFIELD_RANGE(  8,11 );
            uint32_t   ForceRefIdx3                    : MOS_BITFIELD_RANGE( 12,15 );
            uint32_t   NumMergeCandCu8x8               : MOS_BITFIELD_RANGE( 16,19 );
            uint32_t   NumMergeCandCu16x16             : MOS_BITFIELD_RANGE( 20,23 );
            uint32_t   NumMergeCandCu32x32             : MOS_BITFIELD_RANGE( 24,27 );
            uint32_t   NumMergeCandCu64x64             : MOS_BITFIELD_RANGE( 28,31 );
        };
        uint32_t       Value;
    } DW36;

    // DW37
    union
    {
        struct
        {
            uint32_t   SegID                           : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   QpEnable                        : MOS_BITFIELD_RANGE( 16,19 );
            uint32_t   SegIDEnable                     : MOS_BITFIELD_BIT(      20 );
            uint32_t   Reserved                        : MOS_BITFIELD_RANGE( 21,22 );
            uint32_t   ForceRefIdEnable                : MOS_BITFIELD_BIT(      23 );
            uint32_t   Reserved1                       : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW37;

    // DW38
    union
    {
        struct
        {
            uint32_t   ForceQp0                        : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   ForceQp1                        : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   ForceQp2                        : MOS_BITFIELD_RANGE( 16,23 );
            uint32_t   ForceQp3                        : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW38;

    // DW39
    union
    {
        struct
        {
            uint32_t   Reserved;
        };
        uint32_t       Value;
    } DW39;

    // DW40
    union
    {
        struct
        {
            uint32_t   _4xMeMvOutputDataSurfIndex      : MOS_BITFIELD_RANGE(  0,31 );
        };
        uint32_t       Value;
    } DW40;

    // DW41
    union
    {
        struct
        {
            uint32_t   _16xOr32xMeMvInputDataSurfIndex : MOS_BITFIELD_RANGE(  0,31 );
        };
        uint32_t       Value;
    } DW41;

    // DW42
    union
    {
        struct
        {
            uint32_t   _4xMeOutputDistSurfIndex        : MOS_BITFIELD_RANGE(  0,31 );
        };
        uint32_t       Value;
    } DW42;

    // DW43
    union
    {
        struct
        {
            uint32_t   _4xMeOutputBrcDistSurfIndex     : MOS_BITFIELD_RANGE(  0,31 );
        };
        uint32_t       Value;
    } DW43;

    // DW44
    union
    {
        struct
        {
            uint32_t   VMEFwdInterPredictionSurfIndex  : MOS_BITFIELD_RANGE(  0,31 );
        };
        uint32_t       Value;
    } DW44;

    // DW45
    union
    {
        struct
        {
            uint32_t   VMEBwdInterPredictionSurfIndex  : MOS_BITFIELD_RANGE(  0,31 );
        };
        uint32_t       Value;
    } DW45;

    // DW46
    union
    {
        struct
        {
            uint32_t   VDEncStreamInOutputSurfIndex    : MOS_BITFIELD_RANGE(  0,31 );
        };
        uint32_t       Value;
    } DW46;

    // DW47
    union
    {
        struct
        {
            uint32_t   VDEncStreamInInputSurfIndex     : MOS_BITFIELD_RANGE(  0,31 );
        };
        uint32_t       Value;
    } DW47;

    // DW48
    union
    {
        struct
        {
            uint32_t   SumMVandDistortionOutputSurfIndex : MOS_BITFIELD_RANGE(  0,31 );
        };
        uint32_t       Value;
    } DW48;

} CODECHAL_ENCODE_AVC_ME_CURBE_CM_FEI_G12, *PCODECHAL_ENCODE_AVC_ME_CURBE_CM_FEI_G12;

typedef struct _CODECHAL_ENCODE_AVC_PREPROC_CURBE_CM_G12
{
    // DW0
    union
    {
        struct
        {
            uint32_t   SkipModeEn                      : MOS_BITFIELD_BIT(       0 );
            uint32_t   AdaptiveEn                      : MOS_BITFIELD_BIT(       1 );
            uint32_t   BiMixDis                        : MOS_BITFIELD_BIT(       2 );
            uint32_t                                   : MOS_BITFIELD_RANGE(  3, 4 );
            uint32_t   EarlyImeSuccessEn               : MOS_BITFIELD_BIT(       5 );
            uint32_t                                   : MOS_BITFIELD_BIT(       6 );
            uint32_t   T8x8FlagForInterEn              : MOS_BITFIELD_BIT(       7 );
            uint32_t                                   : MOS_BITFIELD_RANGE(  8,23 );
            uint32_t   EarlyImeStop                    : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW0;

    // DW1
    union
    {
        struct
        {
            uint32_t   MaxNumMVs                       : MOS_BITFIELD_RANGE(  0, 5 );
            uint32_t                                   : MOS_BITFIELD_RANGE(  6,15 );
            uint32_t   BiWeight                        : MOS_BITFIELD_RANGE( 16,21 );
            uint32_t                                   : MOS_BITFIELD_RANGE( 22,27 );
            uint32_t   UniMixDisable                   : MOS_BITFIELD_BIT(      28 );
            uint32_t                                   : MOS_BITFIELD_RANGE( 29,31 );
        };
        uint32_t       Value;
    } DW1;

    // DW2
    union
    {
        struct
        {
            uint32_t   LenSP                           : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   MaxNumSU                        : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   PicWidth                        : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW2;

    // DW3
    union
    {
        struct
        {
            uint32_t   SrcSize                         : MOS_BITFIELD_RANGE(  0, 1 );
            uint32_t                                   : MOS_BITFIELD_RANGE(  2, 3 );
            uint32_t   MbTypeRemap                     : MOS_BITFIELD_RANGE(  4, 5 );
            uint32_t   SrcAccess                       : MOS_BITFIELD_BIT(       6 );
            uint32_t   RefAccess                       : MOS_BITFIELD_BIT(       7 );
            uint32_t   SearchCtrl                      : MOS_BITFIELD_RANGE(  8,10 );
            uint32_t   DualSearchPathOption            : MOS_BITFIELD_BIT(      11 );
            uint32_t   SubPelMode                      : MOS_BITFIELD_RANGE( 12,13 );
            uint32_t   SkipType                        : MOS_BITFIELD_BIT(      14 );
            uint32_t   DisableFieldCacheAlloc          : MOS_BITFIELD_BIT(      15 );
            uint32_t   InterChromaMode                 : MOS_BITFIELD_BIT(      16 );
            uint32_t   FTEnable                        : MOS_BITFIELD_BIT(      17 );
            uint32_t   BMEDisableFBR                   : MOS_BITFIELD_BIT(      18 );
            uint32_t   BlockBasedSkipEnable            : MOS_BITFIELD_BIT(      19 );
            uint32_t   InterSAD                        : MOS_BITFIELD_RANGE( 20,21 );
            uint32_t   IntraSAD                        : MOS_BITFIELD_RANGE( 22,23 );
            uint32_t   SubMbPartMask                   : MOS_BITFIELD_RANGE( 24,30 );
            uint32_t                                   : MOS_BITFIELD_BIT(      31 );
        };
        uint32_t       Value;
    } DW3;

    // DW4
    union
    {
        struct
        {
            uint32_t   FrameQp                         : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   PerMBQpEnable                   : MOS_BITFIELD_BIT(       8 );
            uint32_t   FieldParityFlag                 : MOS_BITFIELD_BIT(       9 );
            uint32_t   HMEEnable                       : MOS_BITFIELD_BIT(      10 );
            uint32_t   MultipleMVPredictorPerMBEnable  : MOS_BITFIELD_RANGE( 11,12 );
            uint32_t   DisableMvOutput                 : MOS_BITFIELD_BIT(      13 );
            uint32_t   DisableMbStats                  : MOS_BITFIELD_BIT(      14 );
            uint32_t   BwdRefPicFrameFieldFlag         : MOS_BITFIELD_BIT(      15 );
            uint32_t   FwdRefPicFrameFieldFlag         : MOS_BITFIELD_BIT(      16 );
            uint32_t   BwdRefPicFieldParityFlag        : MOS_BITFIELD_BIT(      17 );
            uint32_t   FwdRefPicFieldParityFlag        : MOS_BITFIELD_BIT(      18 );
            uint32_t   CurrPicFieldParityFlag          : MOS_BITFIELD_BIT(      19 );
            uint32_t   BwdRefPicEnable                 : MOS_BITFIELD_BIT(      20 );
            uint32_t   FwdRefPicEnable                 : MOS_BITFIELD_BIT(      21 );
            uint32_t                                   : MOS_BITFIELD_RANGE( 22,31 );
        };
        uint32_t       Value;
    } DW4;

    // DW5
    union
    {
        struct
        {
            uint32_t   SliceMbHeight                   : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   RefWidth                        : MOS_BITFIELD_RANGE( 16,23 );
            uint32_t   RefHeight                       : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW5;

    // DW6
    union
    {
        struct
        {
            uint32_t   PicHeight                       : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t                                   : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW6;

    // DW7
    union
    {
        struct
        {
            uint32_t   IntraPartMask                   : MOS_BITFIELD_RANGE(  0, 4 );
            uint32_t   NonSkipZMvAdded                 : MOS_BITFIELD_BIT(       5 );
            uint32_t   NonSkipModeAdded                : MOS_BITFIELD_BIT(       6 );
            uint32_t   LumaIntraSrcCornerSwap          : MOS_BITFIELD_BIT(       7 );
            uint32_t                                   : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   MVCostScaleFactor               : MOS_BITFIELD_RANGE( 16,17 );
            uint32_t   BilinearEnable                  : MOS_BITFIELD_BIT(      18 );
            uint32_t   SrcFieldPolarity                : MOS_BITFIELD_BIT(      19 );
            uint32_t   WeightedSADHAAR                 : MOS_BITFIELD_BIT(      20 );
            uint32_t   AConlyHAAR                      : MOS_BITFIELD_BIT(      21 );
            uint32_t   RefIDCostMode                   : MOS_BITFIELD_BIT(      22 );
            uint32_t                                   : MOS_BITFIELD_BIT(      23 );
            uint32_t   SkipCenterMask                  : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW7;

    struct
    {
        // DW8
        union
        {
            struct
            {
                uint32_t   Mode0Cost                       : MOS_BITFIELD_RANGE(  0, 7 );
                uint32_t   Mode1Cost                       : MOS_BITFIELD_RANGE(  8,15 );
                uint32_t   Mode2Cost                       : MOS_BITFIELD_RANGE( 16,23 );
                uint32_t   Mode3Cost                       : MOS_BITFIELD_RANGE( 24,31 );
            };
            uint32_t       Value;
        } DW8;

        // DW9
        union
        {
            struct
            {
                uint32_t   Mode4Cost                       : MOS_BITFIELD_RANGE(  0, 7 );
                uint32_t   Mode5Cost                       : MOS_BITFIELD_RANGE(  8,15 );
                uint32_t   Mode6Cost                       : MOS_BITFIELD_RANGE( 16,23 );
                uint32_t   Mode7Cost                       : MOS_BITFIELD_RANGE( 24,31 );
            };
            uint32_t       Value;
        } DW9;

        // DW10
        union
        {
            struct
            {
                uint32_t   Mode8Cost                       : MOS_BITFIELD_RANGE(  0, 7 );
                uint32_t   Mode9Cost                       : MOS_BITFIELD_RANGE(  8,15 );
                uint32_t   RefIDCost                       : MOS_BITFIELD_RANGE( 16,23 );
                uint32_t   ChromaIntraModeCost             : MOS_BITFIELD_RANGE( 24,31 );
            };
            uint32_t       Value;
        } DW10;

        // DW11
        union
        {
            struct
            {
                uint32_t   MV0Cost                         : MOS_BITFIELD_RANGE(  0, 7 );
                uint32_t   MV1Cost                         : MOS_BITFIELD_RANGE(  8,15 );
                uint32_t   MV2Cost                         : MOS_BITFIELD_RANGE( 16,23 );
                uint32_t   MV3Cost                         : MOS_BITFIELD_RANGE( 24,31 );
            };
            uint32_t       Value;
        } DW11;

        // DW12
        union
        {
            struct
            {
                uint32_t   MV4Cost                         : MOS_BITFIELD_RANGE(  0, 7 );
                uint32_t   MV5Cost                         : MOS_BITFIELD_RANGE(  8,15 );
                uint32_t   MV6Cost                         : MOS_BITFIELD_RANGE( 16,23 );
                uint32_t   MV7Cost                         : MOS_BITFIELD_RANGE( 24,31 );
            };
            uint32_t       Value;
        } DW12;

        // DW13
        union
        {
            struct
            {
                uint32_t                                   : MOS_BITFIELD_RANGE(  0, 31 );
            };
            uint32_t       Value;
        } DW13;

        // DW14
        union
        {
            struct
            {
                uint32_t   SICFwdTransCoeffThreshold_0     : MOS_BITFIELD_RANGE(  0,15 );
                uint32_t   SICFwdTransCoeffThreshold_1     : MOS_BITFIELD_RANGE( 16,23 );
                uint32_t   SICFwdTransCoeffThreshold_2     : MOS_BITFIELD_RANGE( 24,31 );
            };
            uint32_t       Value;
        } DW14;

        // DW15
        union
        {
            struct
            {
                uint32_t   SICFwdTransCoeffThreshold_3     : MOS_BITFIELD_RANGE(  0, 7 );
                uint32_t   SICFwdTransCoeffThreshold_4     : MOS_BITFIELD_RANGE(  8,15 );
                uint32_t   SICFwdTransCoeffThreshold_5     : MOS_BITFIELD_RANGE( 16,23 );
                uint32_t   SICFwdTransCoeffThreshold_6     : MOS_BITFIELD_RANGE( 24,31 );    // Highest Freq
            };
            uint32_t       Value;
        } DW15;
    } ModeMvCost;

    struct
    {
        // DW16
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_0;
                SearchPathDelta   SPDelta_1;
                SearchPathDelta   SPDelta_2;
                SearchPathDelta   SPDelta_3;
            };
            uint32_t              Value;
        } DW16;

        // DW17
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_4;
                SearchPathDelta   SPDelta_5;
                SearchPathDelta   SPDelta_6;
                SearchPathDelta   SPDelta_7;
            };
            uint32_t              Value;
        } DW17;

        // DW18
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_8;
                SearchPathDelta   SPDelta_9;
                SearchPathDelta   SPDelta_10;
                SearchPathDelta   SPDelta_11;
            };
            uint32_t              Value;
        } DW18;

        // DW19
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_12;
                SearchPathDelta   SPDelta_13;
                SearchPathDelta   SPDelta_14;
                SearchPathDelta   SPDelta_15;
            };
            uint32_t              Value;
        } DW19;

        // DW20
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_16;
                SearchPathDelta   SPDelta_17;
                SearchPathDelta   SPDelta_18;
                SearchPathDelta   SPDelta_19;
            };
            uint32_t              Value;
        } DW20;

        // DW21
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_20;
                SearchPathDelta   SPDelta_21;
                SearchPathDelta   SPDelta_22;
                SearchPathDelta   SPDelta_23;
            };
            uint32_t              Value;
        } DW21;

        // DW22
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_24;
                SearchPathDelta   SPDelta_25;
                SearchPathDelta   SPDelta_26;
                SearchPathDelta   SPDelta_27;
            };
            uint32_t              Value;
        } DW22;

        // DW23
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_28;
                SearchPathDelta   SPDelta_29;
                SearchPathDelta   SPDelta_30;
                SearchPathDelta   SPDelta_31;
            };
            uint32_t              Value;
        } DW23;

        // DW24
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_32;
                SearchPathDelta   SPDelta_33;
                SearchPathDelta   SPDelta_34;
                SearchPathDelta   SPDelta_35;
            };
            uint32_t              Value;
        } DW24;

        // DW25
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_36;
                SearchPathDelta   SPDelta_37;
                SearchPathDelta   SPDelta_38;
                SearchPathDelta   SPDelta_39;
            };
            uint32_t              Value;
        } DW25;

        // DW26
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_40;
                SearchPathDelta   SPDelta_41;
                SearchPathDelta   SPDelta_42;
                SearchPathDelta   SPDelta_43;
            };
            uint32_t              Value;
        } DW26;

        // DW27
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_44;
                SearchPathDelta   SPDelta_45;
                SearchPathDelta   SPDelta_46;
                SearchPathDelta   SPDelta_47;
            };
            uint32_t              Value;
        } DW27;

        // DW28
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_48;
                SearchPathDelta   SPDelta_49;
                SearchPathDelta   SPDelta_50;
                SearchPathDelta   SPDelta_51;
            };
            uint32_t              Value;
        } DW28;

        // DW29
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_52;
                SearchPathDelta   SPDelta_53;
                SearchPathDelta   SPDelta_54;
                SearchPathDelta   SPDelta_55;
            };
            uint32_t              Value;
        } DW29;

        // DW30
        union
        {
            struct
            {
                uint32_t   Intra4x4ModeMask                : MOS_BITFIELD_RANGE(  0, 8 );
                uint32_t                                   : MOS_BITFIELD_RANGE(  9,15 );
                uint32_t   Intra8x8ModeMask                : MOS_BITFIELD_RANGE( 16,24 );
                uint32_t                                   : MOS_BITFIELD_RANGE( 25,31 );
            };
            uint32_t       Value;
        } DW30;

        // DW31
        union
        {
            struct
            {
                uint32_t   Intra16x16ModeMask              : MOS_BITFIELD_RANGE(  0, 3 );
                uint32_t   IntraChromaModeMask             : MOS_BITFIELD_RANGE(  4, 7 );
                uint32_t   IntraComputeType                : MOS_BITFIELD_RANGE(  8, 9 );
                uint32_t                                   : MOS_BITFIELD_RANGE( 10,31 );
            };
            uint32_t       Value;
        } DW31;
    } SPDelta;

    // DW32
    union
    {
        struct
        {
            uint32_t   MaxVmvR                         : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t                                   : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW32;

    // DW33
    union
    {
        struct
        {
            uint32_t   Intra16x16NonDCPredPenalty      : MOS_BITFIELD_RANGE(  0,7 );
            uint32_t   Intra8x8NonDCPredPenalty        : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   Intra4x4NonDCPredPenalty        : MOS_BITFIELD_RANGE( 16,23 );
            uint32_t                                   : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW33;

    // DW34
    union
    {
        struct
        {
            uint32_t                                   : MOS_BITFIELD_RANGE(  0,31 );
        };
        uint32_t       Value;
    } DW34;

    // DW35
    union
    {
        struct
        {
            uint32_t                                   : MOS_BITFIELD_RANGE(  0,31 );
        };
        uint32_t       Value;
    } DW35;

    // DW36
    union
    {
        struct
        {
            uint32_t                                   : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   HMECombinedExtraSUs             : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t                                   : MOS_BITFIELD_RANGE( 16,29 );
            uint32_t   HMECombineOverlap               : MOS_BITFIELD_RANGE( 30,31 );
        };
        uint32_t       Value;
    } DW36;

    // DW37
    union
    {
        struct
        {
            uint32_t   SkipModeEn                      : MOS_BITFIELD_BIT(       0 );
            uint32_t   AdaptiveEn                      : MOS_BITFIELD_BIT(       1 );
            uint32_t   BiMixDis                        : MOS_BITFIELD_BIT(       2 );
            uint32_t                                   : MOS_BITFIELD_RANGE(  3, 4 );
            uint32_t   EarlyImeSuccessEn               : MOS_BITFIELD_BIT(       5 );
            uint32_t                                   : MOS_BITFIELD_BIT(       6 );
            uint32_t   T8x8FlagForInterEn              : MOS_BITFIELD_BIT(       7 );
            uint32_t                                   : MOS_BITFIELD_RANGE(  8,23 );
            uint32_t   EarlyImeStop                    : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW37;

    // DW38
    union
    {
        struct
        {
            uint32_t   LenSP                           : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   MaxNumSU                        : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   RefThreshold                    : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW38;

    // DW39
    union
    {
        struct
        {
            uint32_t                                   : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   HMERefWindowsCombThreshold      : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   RefWidth                        : MOS_BITFIELD_RANGE( 16,23 );
            uint32_t   RefHeight                       : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW39;

    // DW40
    union
    {
        struct
        {
            uint32_t   CurrPicSurfIndex                : MOS_BITFIELD_RANGE(  0,31 );
        };
        uint32_t       Value;
    } DW40;

    // DW41
    union
    {
        struct
        {
            uint32_t   HMEMvDataSurfIndex              : MOS_BITFIELD_RANGE(  0,31 );
        };
        uint32_t       Value;
    } DW41;

    // DW42
    union
    {
        struct
        {
            uint32_t   MvPredictorSurfIndex            : MOS_BITFIELD_RANGE(  0,31 );
        };
        uint32_t       Value;
    } DW42;

    // DW43
    union
    {
        struct
        {
            uint32_t   MbQpSurfIndex                   : MOS_BITFIELD_RANGE(  0,31 );
        };
        uint32_t       Value;
    } DW43;

    // DW44
    union
    {
        struct
        {
            uint32_t   MvDataOutSurfIndex              : MOS_BITFIELD_RANGE(  0,31 );
        };
        uint32_t       Value;
    } DW44;

    // DW45
    union
    {
        struct
        {
            uint32_t   MbStatsOutSurfIndex             : MOS_BITFIELD_RANGE(  0,31 );
        };
        uint32_t       Value;
    } DW45;

    // DW46
    union
    {
        struct
        {
            uint32_t   VMEInterPredictionSurfIndex     : MOS_BITFIELD_RANGE(  0,31 );
        };
        uint32_t       Value;
    } DW46;

    // DW47
    union
    {
        struct
        {
            uint32_t   VMEInterPredictionMRSurfIndex   : MOS_BITFIELD_RANGE(  0,31 );
        };
        uint32_t       Value;
    } DW47;

    // DW48
    union
    {
        struct
        {
            uint32_t   FtqLutSurfIndex                 : MOS_BITFIELD_RANGE(  0,31 );
        };
        uint32_t       Value;
    } DW48;

} CODECHAL_ENCODE_AVC_PREPROC_CURBE_CM_G12, *PCODECHAL_ENCODE_AVC_PREPROC_CURBE_CM_G12;

typedef struct _CODECHAL_ENCODE_AVC_FEI_MBENC_STATIC_DATA_G12
{
    // DW0
    union
    {
        struct
        {
            uint32_t   SkipModeEn                          : MOS_BITFIELD_BIT(       0 );
            uint32_t   AdaptiveEn                          : MOS_BITFIELD_BIT(       1 );
            uint32_t   BiMixDis                            : MOS_BITFIELD_BIT(       2 );
            uint32_t                                       : MOS_BITFIELD_RANGE(  3, 4 );
            uint32_t   EarlyImeSuccessEn                   : MOS_BITFIELD_BIT(       5 );
            uint32_t                                       : MOS_BITFIELD_BIT(       6 );
            uint32_t   T8x8FlagForInterEn                  : MOS_BITFIELD_BIT(       7 );
            uint32_t                                       : MOS_BITFIELD_RANGE(  8,23 );
            uint32_t   EarlyImeStop                        : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW0;

    // DW1
    union
    {
        struct
        {
            uint32_t   MaxNumMVs                           : MOS_BITFIELD_RANGE(  0, 5 );
            uint32_t   ExtendedMvCostRange                 : MOS_BITFIELD_BIT(       6 );
            uint32_t                                       : MOS_BITFIELD_RANGE(  7,15 );
            uint32_t   BiWeight                            : MOS_BITFIELD_RANGE( 16,21 );
            uint32_t                                       : MOS_BITFIELD_RANGE( 22,27 );
            uint32_t   UniMixDisable                       : MOS_BITFIELD_BIT(      28 );
            uint32_t                                       : MOS_BITFIELD_RANGE( 29,31 );
        };
        uint32_t       Value;
    } DW1;

    // DW2
    union
    {
        struct
        {
            uint32_t   LenSP                               : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   MaxNumSU                            : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   PicWidth                            : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW2;

    // DW3
    union
    {
        struct
        {
            uint32_t   SrcSize                             : MOS_BITFIELD_RANGE(  0, 1 );
            uint32_t                                       : MOS_BITFIELD_RANGE(  2, 3 );
            uint32_t   MbTypeRemap                         : MOS_BITFIELD_RANGE(  4, 5 );
            uint32_t   SrcAccess                           : MOS_BITFIELD_BIT(       6 );
            uint32_t   RefAccess                           : MOS_BITFIELD_BIT(       7 );
            uint32_t   SearchCtrl                          : MOS_BITFIELD_RANGE(  8,10 );
            uint32_t   DualSearchPathOption                : MOS_BITFIELD_BIT(      11 );
            uint32_t   SubPelMode                          : MOS_BITFIELD_RANGE( 12,13 );
            uint32_t   SkipType                            : MOS_BITFIELD_BIT(      14 );
            uint32_t   DisableFieldCacheAlloc              : MOS_BITFIELD_BIT(      15 );
            uint32_t   InterChromaMode                     : MOS_BITFIELD_BIT(      16 );
            uint32_t   FTEnable                            : MOS_BITFIELD_BIT(      17 );
            uint32_t   BMEDisableFBR                       : MOS_BITFIELD_BIT(      18 );
            uint32_t   BlockBasedSkipEnable                : MOS_BITFIELD_BIT(      19 );
            uint32_t   InterSAD                            : MOS_BITFIELD_RANGE( 20,21 );
            uint32_t   IntraSAD                            : MOS_BITFIELD_RANGE( 22,23 );
            uint32_t   SubMbPartMask                       : MOS_BITFIELD_RANGE( 24,30 );
            uint32_t                                       : MOS_BITFIELD_BIT(      31 );
        };
        uint32_t       Value;
    } DW3;

    // DW4
    union
    {
        struct
        {
            uint32_t   PicHeightMinus1                     : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   MvRestrictionInSliceEnable          : MOS_BITFIELD_BIT(      16 );
            uint32_t   DeltaMvEnable                       : MOS_BITFIELD_BIT(      17 );
            uint32_t   TrueDistortionEnable                : MOS_BITFIELD_BIT(      18 );
            uint32_t   EnableWavefrontOptimization         : MOS_BITFIELD_BIT(      19 );
            uint32_t   EnableFBRBypass                     : MOS_BITFIELD_BIT(      20 );
            uint32_t   EnableIntraCostScalingForStaticFrame: MOS_BITFIELD_BIT(      21 );
            uint32_t   EnableIntraRefresh                  : MOS_BITFIELD_BIT(      22 );
            uint32_t   Reserved                            : MOS_BITFIELD_BIT(      23 );
            uint32_t   EnableDirtyRect                     : MOS_BITFIELD_BIT(      24 );
            uint32_t   bCurFldIDR                          : MOS_BITFIELD_BIT(      25 );
            uint32_t   ConstrainedIntraPredFlag            : MOS_BITFIELD_BIT(      26 );
            uint32_t   FieldParityFlag                     : MOS_BITFIELD_BIT(      27 );
            uint32_t   HMEEnable                           : MOS_BITFIELD_BIT(      28 );
            uint32_t   PictureType                         : MOS_BITFIELD_RANGE( 29,30 );
            uint32_t   UseActualRefQPValue                 : MOS_BITFIELD_BIT(      31 );
        };
        uint32_t       Value;

    } DW4;

    // DW5
    union
    {
        struct
        {
            uint32_t   SliceMbHeight                       : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   RefWidth                            : MOS_BITFIELD_RANGE( 16,23 );
            uint32_t   RefHeight                           : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;

    } DW5;

    // DW6
    union
    {
        struct
        {
            uint32_t   BatchBufferEnd                      : MOS_BITFIELD_RANGE(  0,31 );
        };
        uint32_t       Value;

    } DW6;

    // DW7
    union
    {
        struct
        {
            uint32_t   IntraPartMask                       : MOS_BITFIELD_RANGE(  0, 4 );
            uint32_t   NonSkipZMvAdded                     : MOS_BITFIELD_BIT(       5 );
            uint32_t   NonSkipModeAdded                    : MOS_BITFIELD_BIT(       6 );
            uint32_t   LumaIntraSrcCornerSwap              : MOS_BITFIELD_BIT(       7 );
            uint32_t                                       : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   MVCostScaleFactor                   : MOS_BITFIELD_RANGE( 16,17 );
            uint32_t   BilinearEnable                      : MOS_BITFIELD_BIT(      18 );
            uint32_t   SrcFieldPolarity                    : MOS_BITFIELD_BIT(      19 );
            uint32_t   WeightedSADHAAR                     : MOS_BITFIELD_BIT(      20 );
            uint32_t   AConlyHAAR                          : MOS_BITFIELD_BIT(      21 );
            uint32_t   RefIDCostMode                       : MOS_BITFIELD_BIT(      22 );
            uint32_t                                       : MOS_BITFIELD_BIT(      23 );
            uint32_t   SkipCenterMask                      : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;

    } DW7;

    struct
    {
        // DW8
        union
        {
            struct
            {
                uint32_t   Mode0Cost                           : MOS_BITFIELD_RANGE(  0, 7 );
                uint32_t   Mode1Cost                           : MOS_BITFIELD_RANGE(  8,15 );
                uint32_t   Mode2Cost                           : MOS_BITFIELD_RANGE( 16,23 );
                uint32_t   Mode3Cost                           : MOS_BITFIELD_RANGE( 24,31 );
            };
            uint32_t       Value;
        } DW8;

        // DW9
        union
        {
            struct
            {
                uint32_t   Mode4Cost                           : MOS_BITFIELD_RANGE(  0, 7 );
                uint32_t   Mode5Cost                           : MOS_BITFIELD_RANGE(  8,15 );
                uint32_t   Mode6Cost                           : MOS_BITFIELD_RANGE( 16,23 );
                uint32_t   Mode7Cost                           : MOS_BITFIELD_RANGE( 24,31 );
            };
            uint32_t       Value;
        } DW9;

        // DW10
        union
        {
            struct
            {
                uint32_t   Mode8Cost                           : MOS_BITFIELD_RANGE(  0, 7 );
                uint32_t   Mode9Cost                           : MOS_BITFIELD_RANGE(  8,15 );
                uint32_t   RefIDCost                           : MOS_BITFIELD_RANGE( 16,23 );
                uint32_t   ChromaIntraModeCost                 : MOS_BITFIELD_RANGE( 24,31 );
            };
            uint32_t       Value;
        } DW10;

        // DW11
        union
        {
            struct
            {
                uint32_t   MV0Cost                             : MOS_BITFIELD_RANGE(  0, 7 );
                uint32_t   MV1Cost                             : MOS_BITFIELD_RANGE(  8,15 );
                uint32_t   MV2Cost                             : MOS_BITFIELD_RANGE( 16,23 );
                uint32_t   MV3Cost                             : MOS_BITFIELD_RANGE( 24,31 );
            };
            uint32_t       Value;
        } DW11;

        // DW12
        union
        {
            struct
            {
                uint32_t   MV4Cost                             : MOS_BITFIELD_RANGE(  0, 7 );
                uint32_t   MV5Cost                             : MOS_BITFIELD_RANGE(  8,15 );
                uint32_t   MV6Cost                             : MOS_BITFIELD_RANGE( 16,23 );
                uint32_t   MV7Cost                             : MOS_BITFIELD_RANGE( 24,31 );
            };
            uint32_t       Value;
        } DW12;

        // DW13
        union
        {
            struct
            {
                uint32_t   QpPrimeY                            : MOS_BITFIELD_RANGE(  0, 7 );
                uint32_t   QpPrimeCb                           : MOS_BITFIELD_RANGE(  8,15 );
                uint32_t   QpPrimeCr                           : MOS_BITFIELD_RANGE( 16,23 );
                uint32_t   TargetSizeInWord                    : MOS_BITFIELD_RANGE( 24,31 );
            };
            uint32_t       Value;
        } DW13;

        // DW14
        union
        {
            struct
            {
                uint32_t   SICFwdTransCoeffThreshold_0         : MOS_BITFIELD_RANGE(  0,15 );
                uint32_t   SICFwdTransCoeffThreshold_1         : MOS_BITFIELD_RANGE( 16,23 );
                uint32_t   SICFwdTransCoeffThreshold_2         : MOS_BITFIELD_RANGE( 24,31 );
            };
            uint32_t       Value;
        } DW14;

        // DW15
        union
        {
            struct
            {
                uint32_t   SICFwdTransCoeffThreshold_3         : MOS_BITFIELD_RANGE(  0, 7 );
                uint32_t   SICFwdTransCoeffThreshold_4         : MOS_BITFIELD_RANGE(  8,15 );
                uint32_t   SICFwdTransCoeffThreshold_5         : MOS_BITFIELD_RANGE( 16,23 );
                uint32_t   SICFwdTransCoeffThreshold_6         : MOS_BITFIELD_RANGE( 24,31 );    // Highest Freq
            };
            uint32_t       Value;
        } DW15;
    } ModeMvCost;

    struct
    {
        // DW16
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_0;
                SearchPathDelta   SPDelta_1;
                SearchPathDelta   SPDelta_2;
                SearchPathDelta   SPDelta_3;
            };
            uint32_t              Value;
        } DW16;

        // DW17
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_4;
                SearchPathDelta   SPDelta_5;
                SearchPathDelta   SPDelta_6;
                SearchPathDelta   SPDelta_7;
            };
            uint32_t              Value;
        } DW17;

        // DW18
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_8;
                SearchPathDelta   SPDelta_9;
                SearchPathDelta   SPDelta_10;
                SearchPathDelta   SPDelta_11;
            };
            uint32_t              Value;
        } DW18;

        // DW19
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_12;
                SearchPathDelta   SPDelta_13;
                SearchPathDelta   SPDelta_14;
                SearchPathDelta   SPDelta_15;
            };
            uint32_t              Value;
        } DW19;

        // DW20
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_16;
                SearchPathDelta   SPDelta_17;
                SearchPathDelta   SPDelta_18;
                SearchPathDelta   SPDelta_19;
            };
            uint32_t              Value;
        } DW20;

        // DW21
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_20;
                SearchPathDelta   SPDelta_21;
                SearchPathDelta   SPDelta_22;
                SearchPathDelta   SPDelta_23;
            };
            uint32_t              Value;
        } DW21;

        // DW22
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_24;
                SearchPathDelta   SPDelta_25;
                SearchPathDelta   SPDelta_26;
                SearchPathDelta   SPDelta_27;
            };
            uint32_t              Value;
        } DW22;

        // DW23
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_28;
                SearchPathDelta   SPDelta_29;
                SearchPathDelta   SPDelta_30;
                SearchPathDelta   SPDelta_31;
            };
            uint32_t              Value;
        } DW23;

        // DW24
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_32;
                SearchPathDelta   SPDelta_33;
                SearchPathDelta   SPDelta_34;
                SearchPathDelta   SPDelta_35;
            };
            uint32_t              Value;
        } DW24;

        // DW25
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_36;
                SearchPathDelta   SPDelta_37;
                SearchPathDelta   SPDelta_38;
                SearchPathDelta   SPDelta_39;
            };
            uint32_t              Value;
        } DW25;

        // DW26
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_40;
                SearchPathDelta   SPDelta_41;
                SearchPathDelta   SPDelta_42;
                SearchPathDelta   SPDelta_43;
            };
            uint32_t              Value;
        } DW26;

        // DW27
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_44;
                SearchPathDelta   SPDelta_45;
                SearchPathDelta   SPDelta_46;
                SearchPathDelta   SPDelta_47;
            };
            uint32_t              Value;
        } DW27;

        // DW28
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_48;
                SearchPathDelta   SPDelta_49;
                SearchPathDelta   SPDelta_50;
                SearchPathDelta   SPDelta_51;
            };
            uint32_t              Value;
        } DW28;

        // DW29
        union
        {
            struct
            {
                SearchPathDelta   SPDelta_52;
                SearchPathDelta   SPDelta_53;
                SearchPathDelta   SPDelta_54;
                SearchPathDelta   SPDelta_55;
            };
            uint32_t              Value;
        } DW29;

        // DW30
        union
        {
            struct
            {
                uint32_t   Intra4x4ModeMask                    : MOS_BITFIELD_RANGE(  0, 8 );
                uint32_t                                       : MOS_BITFIELD_RANGE(  9,15 );
                uint32_t   Intra8x8ModeMask                    : MOS_BITFIELD_RANGE( 16,24 );
                uint32_t                                       : MOS_BITFIELD_RANGE( 25,31 );
            };
            uint32_t       Value;
        } DW30;

        // DW31
        union
        {
            struct
            {
                uint32_t   Intra16x16ModeMask                  : MOS_BITFIELD_RANGE(  0, 3 );
                uint32_t   IntraChromaModeMask                 : MOS_BITFIELD_RANGE(  4, 7 );
                uint32_t   IntraComputeType                    : MOS_BITFIELD_RANGE(  8, 9 );
                uint32_t                                       : MOS_BITFIELD_RANGE( 10,31 );
            };
            uint32_t       Value;
        } DW31;
    } SPDelta;

    // DW32
    union
    {
        struct
        {
            uint32_t   SkipVal                             : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   MultiPredL0Disable                  : MOS_BITFIELD_RANGE( 16,23 );
            uint32_t   MultiPredL1Disable                  : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW32;

    // DW33
    union
    {
        struct
        {
            uint32_t   Intra16x16NonDCPredPenalty          : MOS_BITFIELD_RANGE(  0,7 );
            uint32_t   Intra8x8NonDCPredPenalty            : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   Intra4x4NonDCPredPenalty            : MOS_BITFIELD_RANGE( 16,23 );
            uint32_t                                       : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW33;

    // DW34
    union
    {
        struct
        {
            uint32_t   List0RefID0FieldParity              : MOS_BITFIELD_BIT(       0 );
            uint32_t   List0RefID1FieldParity              : MOS_BITFIELD_BIT(       1 );
            uint32_t   List0RefID2FieldParity              : MOS_BITFIELD_BIT(       2 );
            uint32_t   List0RefID3FieldParity              : MOS_BITFIELD_BIT(       3 );
            uint32_t   List0RefID4FieldParity              : MOS_BITFIELD_BIT(       4 );
            uint32_t   List0RefID5FieldParity              : MOS_BITFIELD_BIT(       5 );
            uint32_t   List0RefID6FieldParity              : MOS_BITFIELD_BIT(       6 );
            uint32_t   List0RefID7FieldParity              : MOS_BITFIELD_BIT(       7 );
            uint32_t   List1RefID0FrameFieldFlag           : MOS_BITFIELD_BIT(       8 );
            uint32_t   List1RefID1FrameFieldFlag           : MOS_BITFIELD_BIT(       9 );
            uint32_t   IntraRefreshEn                      : MOS_BITFIELD_RANGE( 10,11 );
            uint32_t   ArbitraryNumMbsPerSlice             : MOS_BITFIELD_BIT(      12 );
            uint32_t   TQEnable                            : MOS_BITFIELD_BIT(      13 );
            uint32_t   ForceNonSkipMbEnable                : MOS_BITFIELD_BIT(      14 );
            uint32_t   DisableEncSkipCheck                 : MOS_BITFIELD_BIT(      15 );
            uint32_t   EnableDirectBiasAdjustment          : MOS_BITFIELD_BIT(      16 );
            uint32_t   bForceToSkip                        : MOS_BITFIELD_BIT(      17 );
            uint32_t   EnableGlobalMotionBiasAdjustment    : MOS_BITFIELD_BIT(      18 );
            uint32_t   EnableAdaptiveTxDecision            : MOS_BITFIELD_BIT(      19 );
            uint32_t   EnablePerMBStaticCheck              : MOS_BITFIELD_BIT(      20 );
            uint32_t   EnableAdaptiveSearchWindowSize      : MOS_BITFIELD_BIT(      21 );
            uint32_t   RemoveIntraRefreshOverlap           : MOS_BITFIELD_BIT(      22 );
            uint32_t   CQPFlag                             : MOS_BITFIELD_BIT(      23 );
            uint32_t   List1RefID0FieldParity              : MOS_BITFIELD_BIT(      24 );
            uint32_t   List1RefID1FieldParity              : MOS_BITFIELD_BIT(      25 );
            uint32_t   MADEnableFlag                       : MOS_BITFIELD_BIT(      26 );
            uint32_t   ROIEnableFlag                       : MOS_BITFIELD_BIT(      27 );
            uint32_t   EnableMBFlatnessChkOptimization     : MOS_BITFIELD_BIT(      28 );
            uint32_t   bDirectMode                         : MOS_BITFIELD_BIT(      29 );
            uint32_t   MBBrcEnable                         : MOS_BITFIELD_BIT(      30 );
            uint32_t   bOriginalBff                        : MOS_BITFIELD_BIT(      31 );
        };
        uint32_t       Value;
    } DW34;

    // DW35
    union
    {
        struct
        {
            uint32_t   PanicModeMBThreshold                : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   SmallMbSizeInWord                   : MOS_BITFIELD_RANGE( 16,23 );
            uint32_t   LargeMbSizeInWord                   : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW35;

    // DW36
    union
    {
        struct
        {
            uint32_t   NumRefIdxL0MinusOne                 : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   HMECombinedExtraSUs                 : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   NumRefIdxL1MinusOne                 : MOS_BITFIELD_RANGE( 16,23 );
            uint32_t                                       : MOS_BITFIELD_RANGE( 24,26 );
            uint32_t   MBInputEnable                       : MOS_BITFIELD_BIT(      27 );
            uint32_t   IsFwdFrameShortTermRef              : MOS_BITFIELD_BIT(      28 );
            uint32_t   CheckAllFractionalEnable            : MOS_BITFIELD_BIT(      29 );
            uint32_t   HMECombineOverlap                   : MOS_BITFIELD_RANGE( 30,31 );
        };
        uint32_t       Value;
    } DW36;

    // DW37
    union
    {
        struct
        {
            uint32_t   SkipModeEn                          : MOS_BITFIELD_BIT(       0 );
            uint32_t   AdaptiveEn                          : MOS_BITFIELD_BIT(       1 );
            uint32_t   BiMixDis                            : MOS_BITFIELD_BIT(       2 );
            uint32_t                                       : MOS_BITFIELD_RANGE(  3, 4 );
            uint32_t   EarlyImeSuccessEn                   : MOS_BITFIELD_BIT(       5 );
            uint32_t                                       : MOS_BITFIELD_BIT(       6 );
            uint32_t   T8x8FlagForInterEn                  : MOS_BITFIELD_BIT(       7 );
            uint32_t                                       : MOS_BITFIELD_RANGE(  8,23 );
            uint32_t   EarlyImeStop                        : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW37;

    // DW38
    union
    {
        struct
        {
            uint32_t   LenSP                               : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   MaxNumSU                            : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   RefThreshold                        : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW38;

    // DW39
    union
    {
        struct
        {
            uint32_t                                       : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   HMERefWindowsCombThreshold          : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   RefWidth                            : MOS_BITFIELD_RANGE( 16,23 );
            uint32_t   RefHeight                           : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW39;

    // DW40
    union
    {
        struct
        {
            uint32_t   DistScaleFactorRefID0List0          : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   DistScaleFactorRefID1List0          : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW40;

    // DW41
    union
    {
        struct
        {
            uint32_t   DistScaleFactorRefID2List0          : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   DistScaleFactorRefID3List0          : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW41;

    // DW42
    union
    {
        struct
        {
            uint32_t   DistScaleFactorRefID4List0          : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   DistScaleFactorRefID5List0          : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW42;

    // DW43
    union
    {
        struct
        {
            uint32_t   DistScaleFactorRefID6List0          : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   DistScaleFactorRefID7List0          : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW43;

    // DW44
    union
    {
        struct
        {
            uint32_t   ActualQPValueForRefID0List0         : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   ActualQPValueForRefID1List0         : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   ActualQPValueForRefID2List0         : MOS_BITFIELD_RANGE( 16,23 );
            uint32_t   ActualQPValueForRefID3List0         : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW44;

    // DW45
    union
    {
        struct
        {
            uint32_t   ActualQPValueForRefID4List0         : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   ActualQPValueForRefID5List0         : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   ActualQPValueForRefID6List0         : MOS_BITFIELD_RANGE( 16,23 );
            uint32_t   ActualQPValueForRefID7List0         : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW45;

    // DW46
    union
    {
        struct
        {
            uint32_t   ActualQPValueForRefID0List1         : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   ActualQPValueForRefID1List1         : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   RefCost                             : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW46;

    // DW47
    union
    {
        struct
        {
            uint32_t   MbQpReadFactor                      : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   IntraCostSF                         : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   MaxVmvR                             : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW47;

    //DW48
    union
    {
        struct
        {
            uint32_t   IntraRefreshMBNum                   : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   IntraRefreshUnitInMBMinus1          : MOS_BITFIELD_RANGE( 16,23 );
            uint32_t   IntraRefreshQPDelta                 : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW48;

    // DW49
    union
    {
        struct
        {
            uint32_t   ROI1_X_left                         : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   ROI1_Y_top                          : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW49;

    // DW50
    union
    {
        struct
        {
            uint32_t   ROI1_X_right                        : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   ROI1_Y_bottom                       : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW50;

    // DW51
    union
    {
        struct
        {
            uint32_t   ROI2_X_left                         : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   ROI2_Y_top                          : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW51;

    // DW52
    union
    {
        struct
        {
            uint32_t   ROI2_X_right                        : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   ROI2_Y_bottom                       : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW52;

    // DW53
    union
    {
        struct
        {
            uint32_t   ROI3_X_left                         : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   ROI3_Y_top                          : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW53;

    // DW54
    union
    {
        struct
        {
            uint32_t   ROI3_X_right                        : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   ROI3_Y_bottom                       : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW54;

    // DW55
    union
    {
        struct
        {
            uint32_t   ROI4_X_left                         : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   ROI4_Y_top                          : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW55;

    // DW56
    union
    {
        struct
        {
            uint32_t   ROI4_X_right                        : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   ROI4_Y_bottom                       : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW56;

    // DW57
    union
    {
        struct
        {
            uint32_t   ROI1_dQpPrimeY                      : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   ROI2_dQpPrimeY                      : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   ROI3_dQpPrimeY                      : MOS_BITFIELD_RANGE( 16,23 );
            uint32_t   ROI4_dQpPrimeY                      : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW57;

    // DW58
    union
    {
        struct
        {
            uint32_t   Lambda8x8Inter                      : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   Lambda8x8Intra                      : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW58;

    // DW59
    union
    {
        struct
        {
            uint32_t   LambdaInter                         : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   LambdaIntra                         : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW59;

    // DW60
    union
    {
        struct
        {
            uint32_t   MBTextureThreshold                  : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   TxDecisonThreshold                  : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW60;

    // DW61
    union
    {
        struct
        {
            uint32_t   HMEMVCostScalingFactor              : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   Reserved                            : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   IntraRefreshMBy                     : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW61;

    // DW62
    union
    {
        struct
        {
            uint32_t   IPCM_QP0                            : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   IPCM_QP1                            : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   IPCM_QP2                            : MOS_BITFIELD_RANGE( 16,23 );
            uint32_t   IPCM_QP3                            : MOS_BITFIELD_RANGE( 24,31 );
        };
        uint32_t       Value;
    } DW62;

    // DW63
    union
    {
        struct
        {
            uint32_t   IPCM_QP4                            : MOS_BITFIELD_RANGE(  0, 7 );
            uint32_t   Reserved                            : MOS_BITFIELD_RANGE(  8,15 );
            uint32_t   IPCM_Thresh0                        : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW63;

    // DW64
    union
    {
        struct
        {
            uint32_t   IPCM_Thresh1                        : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   IPCM_Thresh2                        : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW64;

    // DW65
    union
    {
        struct
        {
            uint32_t   IPCM_Thresh3                        : MOS_BITFIELD_RANGE(  0,15 );
            uint32_t   IPCM_Thresh4                        : MOS_BITFIELD_RANGE( 16,31 );
        };
        uint32_t       Value;
    } DW65;

    // DW66
    union
    {
        struct
        {
            uint32_t   NumMVPredictorsL0                   : MOS_BITFIELD_RANGE(  0, 3 );
            uint32_t   FEIEnable                           : MOS_BITFIELD_BIT(       4 );
            uint32_t   MultipleMVPredictorPerMBEnable      : MOS_BITFIELD_BIT(       5 );
            uint32_t   VMEDistortionOutputEnable           : MOS_BITFIELD_BIT(       6 );
            uint32_t   PerMBQpEnable                       : MOS_BITFIELD_BIT(       7 );
            uint32_t   MBInputEnable                       : MOS_BITFIELD_BIT(       8 );
            uint32_t   FEIMode                             : MOS_BITFIELD_BIT(       9 );
            uint32_t   NumMVPredictorsL1                   : MOS_BITFIELD_RANGE( 10,13 );
            uint32_t   Reserved                            : MOS_BITFIELD_RANGE( 14,24 );
            uint32_t   L1ListRef0PictureCodingType         : MOS_BITFIELD_RANGE( 25,26 );  // PAFF WA Fix, 0-invalid, 1-TFF, 2-invalid, 3-BFF
            uint32_t   Reserved1                           : MOS_BITFIELD_RANGE( 27,31 );
        };
        uint32_t       Value;
    } DW66;

    // DW67
    union
    {
        struct
        {
            uint32_t   MBDataSurfIndex                     : MOS_BITFIELD_RANGE(  0,31 );
        };
        struct
        {
            uint32_t   Value;
        };
    } DW67;

    // DW68
    union
    {
        struct
        {
            uint32_t   MVDataSurfIndex                     : MOS_BITFIELD_RANGE(  0,31 );
        };
        struct
        {
            uint32_t   Value;
        };
    } DW68;

    // DW69
    union
    {
        struct
        {
            uint32_t   IDistSurfIndex                      : MOS_BITFIELD_RANGE(  0,31 );
        };
        struct
        {
            uint32_t   Value;
        };
    } DW69;

    // DW70
    union
    {
        struct
        {
            uint32_t   SrcYSurfIndex                       : MOS_BITFIELD_RANGE(  0,31 );
        };
        struct
        {
            uint32_t   Value;
        };
    } DW70;

    // DW71
    union
    {
        struct
        {
            uint32_t   MBSpecificDataSurfIndex             : MOS_BITFIELD_RANGE(  0,31 );
        };
        struct
        {
            uint32_t   Value;
        };
    } DW71;

    // DW72
    union
    {
        struct
        {
            uint32_t   AuxVmeOutSurfIndex                  : MOS_BITFIELD_RANGE(  0,31 );
        };
        struct
        {
            uint32_t   Value;
        };
    } DW72;

    // DW73
    union
    {
        struct
        {
            uint32_t   CurrRefPicSelSurfIndex              : MOS_BITFIELD_RANGE(  0,31 );
        };
        struct
        {
            uint32_t   Value;
        };
    } DW73;

    // DW74
    union
    {
        struct
        {
            uint32_t   HMEMVPredFwdBwdSurfIndex            : MOS_BITFIELD_RANGE(  0,31 );
        };
        struct
        {
            uint32_t   Value;
        };
    } DW74;

    // DW75
    union
    {
        struct
        {
            uint32_t   HMEDistSurfIndex                    : MOS_BITFIELD_RANGE(  0,31 );
        };
        struct
        {
            uint32_t   Value;
        };
    } DW75;

    // DW76
    union
    {
        struct
        {
            uint32_t   SliceMapSurfIndex                   : MOS_BITFIELD_RANGE(  0,31 );
        };
        struct
        {
            uint32_t   Value;
        };
    } DW76;

    // DW77
    union
    {
        struct
        {
            uint32_t   FwdFrmMBDataSurfIndex               : MOS_BITFIELD_RANGE(  0,31 );
        };
        struct
        {
            uint32_t   Value;
        };
    } DW77;

    // DW78
    union
    {
        struct
        {
            uint32_t   FwdFrmMVSurfIndex                   : MOS_BITFIELD_RANGE(  0,31 );
        };
        struct
        {
            uint32_t   Value;
        };
    } DW78;

    // DW79
    union
    {
        struct
        {
            uint32_t   MBQPBuffer                          : MOS_BITFIELD_RANGE(  0,31 );
        };
        struct
        {
            uint32_t   Value;
        };
    } DW79;

    // DW80
    union
    {
        struct
        {
            uint32_t   MBBRCLut                            : MOS_BITFIELD_RANGE(  0,31 );
        };
        struct
        {
            uint32_t   Value;
        };
    } DW80;

    // DW81
    union
    {
        struct
        {
            uint32_t   VMEInterPredictionSurfIndex         : MOS_BITFIELD_RANGE(  0,31 );
        };
        struct
        {
            uint32_t   Value;
        };
    } DW81;

    // DW82
    union
    {
        struct
        {
            uint32_t   VMEInterPredictionMRSurfIndex   : MOS_BITFIELD_RANGE(  0,31 );
        };
        struct
        {
            uint32_t   Value;
        };
    } DW82;

    // DW83
    union
    {
        struct
        {
            uint32_t   MbStatsSurfIndex                    : MOS_BITFIELD_RANGE(  0,31 );
        };
        struct
        {
            uint32_t   Value;
        };
    } DW83;

    // DW84
    union
    {
        struct
        {
            uint32_t   MADSurfIndex                        : MOS_BITFIELD_RANGE(  0,31 );
        };
        struct
        {
            uint32_t   Value;
        };
    } DW84;

    // DW85
    union
    {
        struct
        {
            uint32_t   BRCCurbeSurfIndex                   : MOS_BITFIELD_RANGE(  0,31 );
        };
        struct
        {
            uint32_t   Value;
        };
    } DW85;
 
    // DW86
    union
    {
        struct
        {
            uint32_t   ForceNonSkipMBmapSurface            : MOS_BITFIELD_RANGE(  0,31 );
        };
        struct
        {
            uint32_t   Value;
        };
    } DW86;

    // DW87
    union
    {
        struct
        {
            uint32_t   ReservedIndex                       : MOS_BITFIELD_RANGE(  0,31 );
        };
        struct
        {
            uint32_t   Value;
        };
    } DW87;

    // DW88
    union
    {
        struct
        {
            uint32_t   StaticDetectionCostTableIndex       : MOS_BITFIELD_RANGE(  0,31 );
        };
        struct
        {
            uint32_t   Value;
        };
    } DW88;

    // DW89
    union
    {
        struct
        {
            uint32_t   ScoreboardSurfIndex                 : MOS_BITFIELD_RANGE(  0,31 );
        };
        struct
        {
            uint32_t   Value;
        };
    } DW89;

    // DW90
    union
    {
        struct
        {
            uint32_t   FEIMVPredictorSurfIndex             : MOS_BITFIELD_RANGE(  0,31 );
        };
        struct
        {
            uint32_t   Value;
        };
    } DW90;

} CODECHAL_ENCODE_AVC_FEI_MBENC_STATIC_DATA_G12, *PCODECHAL_ENCODE_AVC_FEI_MBENC_STATIC_DATA_G12;

class CodechalEncodeAvcEncFeiG12 : public CodechalEncodeAvcEncG12
{
public:
    static const uint32_t ModeMvCost_Cm_PreProc[3][CODEC_AVC_NUM_QP][8];
    static const uint32_t ME_CURBE_CM_FEI[49];
    static const uint32_t PreProc_CURBE_CM_normal_I_frame[49];
    static const uint32_t PreProc_CURBE_CM_normal_I_field[49];
    static const uint32_t PreProc_CURBE_CM_normal_P_frame[49];
    static const uint32_t PreProc_CURBE_CM_normal_P_field[49];
    static const uint32_t PreProc_CURBE_CM_normal_B_frame[49];
    static const uint32_t PreProc_CURBE_CM_normal_B_field[49];
    static const uint16_t RefCost_MultiRefQp_Fei[NUM_PIC_TYPES][64];
    static const uint32_t FEI_MBEnc_CURBE_normal_I_frame[91];
    static const uint32_t FEI_MBEnc_CURBE_normal_I_field[91];
    static const uint32_t FEI_MBEnc_CURBE_normal_P_frame[91];
    static const uint32_t FEI_MBEnc_CURBE_normal_P_field[91];
    static const uint32_t FEI_MBEnc_CURBE_normal_B_frame[91];
    static const uint32_t FEI_MBEnc_CURBE_normal_B_field[91];
    static const uint32_t FEI_MBEnc_CURBE_I_frame_DIST[91];
    static const uint32_t HMEBCombineLen_fei[NUM_TARGET_USAGE_MODES];
    static const uint32_t HMECombineLen_fei[NUM_TARGET_USAGE_MODES];
    static const uint32_t m_refThresholdFei = 400;
    static const uint32_t m_mbencNumTargetUsagesCmFei = 1;

    CodechalEncodeAvcEncFeiG12(
        CodechalHwInterface *   hwInterface,
        CodechalDebugInterface *debugInterface,
        PCODECHAL_STANDARD_INFO standardInfo);

    CodechalEncodeAvcEncFeiG12(const CodechalEncodeAvcEncFeiG12&) = delete;

    CodechalEncodeAvcEncFeiG12& operator=(const CodechalEncodeAvcEncFeiG12&) = delete;

    ~CodechalEncodeAvcEncFeiG12();

    //!
    //! \brief    Initializes the kernel.
    //! \details
    //!
    //! \return   MOS_STATUS
    //!           MOS_STATUS_SUCCESS if success
    //!
    MOS_STATUS InitializePicture(const EncoderParams& params);

    //!
    //! \brief    Initializes the FEI PreEnc kernel.
    //! \details  If PreEnc mode, initial PreEnc kernel.
    //!
    //! \return   MOS_STATUS
    //!           MOS_STATUS_SUCCESS if success
    //!
    MOS_STATUS EncodePreEncInitialize(const EncoderParams& params);

    //!
    //! \brief    Encode kernel functions
    //!
    //! \return   MOS_STATUS
    //!           MOS_STATUS_SUCCESS if success, else fail reason
    //!
    MOS_STATUS ExecuteKernelFunctions();

    //!
    //! \brief    Init MbEnc kernel State.
    //!
    //! \return   MOS_STATUS
    //!           MOS_STATUS_SUCCESS if success, else fail reason
    //!
    virtual MOS_STATUS InitKernelStateMbEnc();

    //!
    //! \brief    Init ME kernel state
    //!
    //! \return   MOS_STATUS
    //!           MOS_STATUS_SUCCESS if success, else fail reason
    //!
    virtual MOS_STATUS InitKernelStateMe();

    //!
    //! \brief    Set AVC ME kernel curbe
    //!
    //! \param    [in] params
    //!           Pointer to the MeCurbeParams
    //! \return   MOS_STATUS
    //!           MOS_STATUS_SUCCESS if success, else fail reason
    //!
    virtual MOS_STATUS SetCurbeMe (
        MeCurbeParams* params);

    //!
    //! \brief    Send surface cmd to AVC ME kernel.
    //!
    //! \return   MOS_STATUS
    //!           MOS_STATUS_SUCCESS if success, else fail reason
    //!
    virtual MOS_STATUS SendMeSurfaces (
        PMOS_COMMAND_BUFFER cmdBuffer,
        MeSurfaceParams* params);

    //!
    //! \brief    PreEnc Encode kernel functions
    //!
    //! \return   MOS_STATUS
    //!           MOS_STATUS_SUCCESS if success, else fail reason
    //!
    MOS_STATUS EncodePreEncKernelFunctions();

    //!
    //! \brief    Get encoder kernel header and kernel size
    //!
    //! \param    [in] pvBinary
    //!           Pointer to kernel binary
    //! \param    [in] operation
    //!           Enc kernel operation
    //! \param    [in] krnStateIdx
    //!           Kernel state index
    //! \param    [out] pvKrnHeader
    //!           Pointer to kernel header
    //! \param    [out] pdwKrnSize
    //!           Pointer to kernel size
    //!
    //! \return   MOS_STATUS
    //!           MOS_STATUS_SUCCESS if success, else fail reason
    //!
    static MOS_STATUS GetKernelHeaderAndSize(
        void                           *binary,
        EncOperation                   operation,
        uint32_t                       krnStateIdx,
        void                           *krnHeader,
        uint32_t                       *krnSize);

    // state related functions
    //!
    //! \brief    Initialize related states
    //!
    //! \return   MOS_STATUS
    //!           MOS_STATUS_SUCCESS if success, else fail reason
    //!
    virtual MOS_STATUS InitializeState();

    //!
    //! \brief    Initialize PreProc kernel state
    //!
    //! \return   MOS_STATUS
    //!           MOS_STATUS_SUCCESS if success, else fail reason
    //!
    virtual MOS_STATUS InitKernelStatePreProc();

    //!
    //! \brief    Validate reference list L0 and L1.
    //!
    //! \param    [in] params
    //!           pointer to CODECHAL_ENCODE_AVC_VALIDATE_NUM_REFS_PARAMS
    //!
    //! \return   MOS_STATUS
    //!           MOS_STATUS_SUCCESS if success, else fail reason
    //!
    virtual MOS_STATUS ValidateNumReferences(
        PCODECHAL_ENCODE_AVC_VALIDATE_NUM_REFS_PARAMS params);

    //!
    //! \brief    Initialize WP kernel state
    //!
    //! \return   MOS_STATUS
    //!           MOS_STATUS_SUCCESS if success, else fail reason
    //!
    virtual MOS_STATUS InitKernelStateWP();

    //!
    //! \brief    Set AVC PreProc kernel Curbe data.
    //!
    //! \param    [in] params
    //!           Pointer to the CODECHAL_ENCODE_AVC_PREPROC_CURBE_PARAMS
    //!
    //! \return   MOS_STATUS
    //!           MOS_STATUS_SUCCESS if success, else fail reason
    //!
    virtual MOS_STATUS SetCurbeAvcPreProc(
        PCODECHAL_ENCODE_AVC_PREPROC_CURBE_PARAMS params);

    //!
    //! \brief    Set AVC PreProc kernel Surface data.
    //!
    //! \param    [in] cmdBuffer
    //!           Pointer to the MOS_COMMAND_BUFFER
    //! \param    [in]  params
    //!           Pointer to the CODECHAL_ENCODE_AVC_PREPROC_SURFACE_PARAMS
    //!
    //! \return   MOS_STATUS
    //!           MOS_STATUS_SUCCESS if success, else fail reason
    //!
    virtual MOS_STATUS SendAvcPreProcSurfaces(
        PMOS_COMMAND_BUFFER cmdBuffer,
        PCODECHAL_ENCODE_AVC_PREPROC_SURFACE_PARAMS params);

    //!
    //! \brief    Invoke FEI PreProc kernel.
    //!
    //! \return   MOS_STATUS
    //!           MOS_STATUS_SUCCESS if success, else fail reason
    //!
    MOS_STATUS PreProcKernel();

    //!
    //! \brief    Get MbEnc kernel state idx
    //!
    //! \param    [in] params
    //!           Pointer to the CodechalEncodeIdOffsetParams
    //! \param    [in] kernelOffset
    //!           kernel offset
    //!
    //! \return   MOS_STATUS
    //!           MOS_STATUS_SUCCESS if success, else fail reason
    //!
    virtual MOS_STATUS GetMbEncKernelStateIdx(
        CodechalEncodeIdOffsetParams       *params,
        uint32_t                           *kernelOffset);

    //!
    //! \brief    Set AVC MbEnc kernel Curbe data.
    //!
    //! \param    [in] params
    //!           Pointer to the CODECHAL_ENCODE_AVC_MBENC_CURBE_PARAMS
    //!
    //! \return   MOS_STATUS
    //!           MOS_STATUS_SUCCESS if success, else fail reason
    //!
    virtual MOS_STATUS SetCurbeAvcMbEnc(
        PCODECHAL_ENCODE_AVC_MBENC_CURBE_PARAMS params);

    //!
    //! \brief    Set AVC MbEnc kernel Surface data.
    //!
    //! \param    [in] cmdBuffer
    //!           Pointer to the MOS_COMMAND_BUFFER
    //! \param    [in] params
    //!           Pointer to the CODECHAL_ENCODE_AVC_MBENC_SURFACE_PARAMS
    //!
    //! \return   MOS_STATUS
    //!           MOS_STATUS_SUCCESS if success, else fail reason
    //!
    virtual MOS_STATUS SendAvcMbEncSurfaces(
        PMOS_COMMAND_BUFFER cmdBuffer,
        PCODECHAL_ENCODE_AVC_MBENC_SURFACE_PARAMS params);

    virtual MOS_STATUS UpdateCmdBufAttribute(
        PMOS_COMMAND_BUFFER cmdBuffer,
        bool                renderEngineInUse);

};

#endif  // __CODECHAL_ENC_AVC_FEI_G12_H__

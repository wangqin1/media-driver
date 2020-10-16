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
//! \file     codechal_fei_avc_g12.cpp
//! \brief    This file implements the C++ class/interface for Gen12 platform's AVC
//!           FEI encoding to be used across CODECHAL components.
//!

#include "codechal_fei_avc_g12.h"
#include "igcodeckrn_g12.h"
#include "codeckrnheader.h"

const uint32_t CodechalEncodeAvcEncFeiG12::HMEBCombineLen_fei[NUM_TARGET_USAGE_MODES] =
{
    0, 8, 8, 8, 8, 8, 8, 8
};

const uint32_t CodechalEncodeAvcEncFeiG12::HMECombineLen_fei[NUM_TARGET_USAGE_MODES] =
{
    0, 8, 8, 8, 8, 8, 16, 8
};

const uint32_t CodechalEncodeAvcEncFeiG12::ModeMvCost_Cm_PreProc[3][CODEC_AVC_NUM_QP][8] =
{
    // I-Frame
    {
        { 0x1e03000a, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff000000, 0x00000000, 0x00000000 },
        { 0x1e03000a, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff010101, 0x00000000, 0x00000000 },
        { 0x1e03000a, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff020202, 0x00000000, 0x00000000 },
        { 0x1e03000a, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff030303, 0x00000000, 0x00000000 },
        { 0x1e03000a, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff040404, 0x00000000, 0x00000000 },
        { 0x1e03000a, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff050505, 0x00000000, 0x00000000 },
        { 0x1e03000a, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff060606, 0x00000000, 0x00000000 },
        { 0x1e03000a, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff070707, 0x01010001, 0x01010101 },
        { 0x1e03000a, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff080808, 0x01010001, 0x01010101 },
        { 0x1e03000a, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff090909, 0x03030003, 0x03030303 },
        { 0x1e03000a, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff0a0a0a, 0x03030003, 0x03030303 },
        { 0x1e03000a, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff0b0b0b, 0x06060006, 0x06060606 },
        { 0x1e03000a, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff0c0c0c, 0x06060006, 0x06060606 },
        { 0x1e03000a, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff0d0d0d, 0x08080008, 0x08080808 },
        { 0x1e03000a, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff0e0e0e, 0x08080008, 0x08080808 },
        { 0x1e03000a, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff0f0f0f, 0x0b0b000b, 0x0b0b0b0b },
        { 0x2e06001a, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff101010, 0x0b0b000b, 0x0b0b0b0b },
        { 0x2e06001a, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff111111, 0x0d0d000d, 0x0d0d0d0d },
        { 0x2e06001a, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff121212, 0x0d0d000d, 0x0d0d0d0d },
        { 0x2e06001a, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff131313, 0x10100010, 0x10101010 },
        { 0x3b09001f, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff141414, 0x10100010, 0x10101010 },
        { 0x3b09001f, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff151515, 0x13130013, 0x13131313 },
        { 0x3b09001f, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff161616, 0x13130013, 0x13131313 },
        { 0x3e0c002a, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff171717, 0x16160016, 0x16161616 },
        { 0x3e0c002a, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff181818, 0x16160016, 0x16161616 },
        { 0x3e0c002a, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff191919, 0x1a1a001a, 0x1a1a1a1a },
        { 0x490f002d, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff1a1a1a, 0x1a1a001a, 0x1a1a1a1a },
        { 0x4b19002f, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff1b1b1b, 0x1e1e001e, 0x1e1e1e1e },
        { 0x4b19002f, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff1c1c1c, 0x1e1e001e, 0x1e1e1e1e },
        { 0x4c1b0039, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff1d1d1d, 0x22220022, 0x22222222 },
        { 0x4e1c003a, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff1e1e1e, 0x22220022, 0x22222222 },
        { 0x581e003b, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff1f1f1f, 0x27270027, 0x27272727 },
        { 0x591f003d, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff202020, 0x27270027, 0x27272727 },
        { 0x5a28003e, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff212121, 0x2c2c002c, 0x2c2c2c2c },
        { 0x5b2a0048, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff222222, 0x2c2c002c, 0x2c2c2c2c },
        { 0x5c2b0049, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff232323, 0x32320032, 0x32323232 },
        { 0x5e2c004a, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff242424, 0x32320032, 0x32323232 },
        { 0x682e004b, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff252525, 0x38380038, 0x38383838 },
        { 0x692f004d, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff262626, 0x38380038, 0x38383838 },
        { 0x6a39004e, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff272727, 0x3e3e003e, 0x3e3e3e3e },
        { 0x6b390058, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff282828, 0x3e3e003e, 0x3e3e3e3e },
        { 0x6d3b0059, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff292929, 0x45450045, 0x45454545 },
        { 0x6e3c005a, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff2a2a2a, 0x45450045, 0x45454545 },
        { 0x783e005b, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff2b2b2b, 0x4d4d004d, 0x4d4d4d4d },
        { 0x793f005d, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff2c2c2c, 0x4d4d004d, 0x4d4d4d4d },
        { 0x7a48005e, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff2d2d2d, 0x55550055, 0x55555555 },
        { 0x7b4a0068, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff2e2e2e, 0x55550055, 0x55555555 },
        { 0x7c4b0069, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff2f2f2f, 0x5e5e005e, 0x5e5e5e5e },
        { 0x7e4c006a, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff303030, 0x5e5e005e, 0x5e5e5e5e },
        { 0x884e006b, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff313131, 0x68680068, 0x68686868 },
        { 0x894f006d, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff323232, 0x68680068, 0x68686868 },
        { 0x8a59006e, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff333333, 0x73730073, 0x73737373 }
    },
    // P-Frame
    {
        { 0x391e1a07, 0x06040208, 0x00040005, 0x09050401, 0x0f0e0c0a, 0xff000000, 0x00000000, 0x00000000 },
        { 0x391e1a07, 0x06040208, 0x00040005, 0x09050401, 0x0f0e0c0a, 0xff010101, 0x00000000, 0x00000000 },
        { 0x391e1a07, 0x06040208, 0x00040005, 0x09050401, 0x0f0e0c0a, 0xff020202, 0x00000000, 0x00000000 },
        { 0x391e1a07, 0x06040208, 0x00040005, 0x09050401, 0x0f0e0c0a, 0xff030303, 0x00000000, 0x00000000 },
        { 0x391e1a07, 0x06040208, 0x00040005, 0x09050401, 0x0f0e0c0a, 0xff040404, 0x00000000, 0x00000000 },
        { 0x391e1a07, 0x06040208, 0x00040005, 0x09050401, 0x0f0e0c0a, 0xff050505, 0x00000000, 0x00000000 },
        { 0x391e1a07, 0x06040208, 0x00040005, 0x09050401, 0x0f0e0c0a, 0xff060606, 0x00000000, 0x00000000 },
        { 0x391e1a07, 0x06040208, 0x00040005, 0x09050401, 0x0f0e0c0a, 0xff070707, 0x01010001, 0x01010101 },
        { 0x391e1a07, 0x06040208, 0x00040005, 0x09050401, 0x0f0e0c0a, 0xff080808, 0x01010001, 0x01010101 },
        { 0x391e1a07, 0x06040208, 0x00040005, 0x09050401, 0x0f0e0c0a, 0xff090909, 0x03030003, 0x03030303 },
        { 0x391e1a07, 0x06040208, 0x00040005, 0x09050401, 0x0f0e0c0a, 0xff0a0a0a, 0x03030003, 0x03030303 },
        { 0x391e1a07, 0x06040208, 0x00040005, 0x09050401, 0x0f0e0c0a, 0xff0b0b0b, 0x06060006, 0x06060606 },
        { 0x391e1a07, 0x06040208, 0x00040005, 0x09050401, 0x0f0e0c0a, 0xff0c0c0c, 0x06060006, 0x06060606 },
        { 0x391e1a07, 0x06040208, 0x00040005, 0x09050401, 0x0f0e0c0a, 0xff0d0d0d, 0x08080008, 0x08080808 },
        { 0x391e1a07, 0x06040208, 0x00040005, 0x09050401, 0x0f0e0c0a, 0xff0e0e0e, 0x08080008, 0x08080808 },
        { 0x391e1a07, 0x06040208, 0x00040005, 0x09050401, 0x0f0e0c0a, 0xff0f0f0f, 0x0b0b000b, 0x0b0b0b0b },
        { 0x492e2a0e, 0x0d090519, 0x0008000b, 0x190a0802, 0x1f1e1c1a, 0xff101010, 0x0b0b000b, 0x0b0b0b0b },
        { 0x492e2a0e, 0x0d090519, 0x0008000b, 0x190a0802, 0x1f1e1c1a, 0xff111111, 0x0d0d000d, 0x0d0d0d0d },
        { 0x492e2a0e, 0x0d090519, 0x0008000b, 0x190a0802, 0x1f1e1c1a, 0xff121212, 0x0d0d000d, 0x0d0d0d0d },
        { 0x492e2a0e, 0x0d090519, 0x0008000b, 0x190a0802, 0x1f1e1c1a, 0xff131313, 0x10100010, 0x10101010 },
        { 0x4d3b2f1b, 0x1a0d071d, 0x000c0018, 0x1e0f0c03, 0x2b2b291f, 0xff141414, 0x10100010, 0x10101010 },
        { 0x4d3b2f1b, 0x1a0d071d, 0x000c0018, 0x1e0f0c03, 0x2b2b291f, 0xff151515, 0x13130013, 0x13131313 },
        { 0x4d3b2f1b, 0x1a0d071d, 0x000c0018, 0x1e0f0c03, 0x2b2b291f, 0xff161616, 0x13130013, 0x13131313 },
        { 0x593e3a1e, 0x1d190a29, 0x0018001b, 0x291a1804, 0x2f2e2c2a, 0xff171717, 0x16160016, 0x16161616 },
        { 0x593e3a1e, 0x1d190a29, 0x0018001b, 0x291a1804, 0x2f2e2c2a, 0xff181818, 0x16160016, 0x16161616 },
        { 0x593e3a1e, 0x1d190a29, 0x0018001b, 0x291a1804, 0x2f2e2c2a, 0xff191919, 0x1a1a001a, 0x1a1a1a1a },
        { 0x5b493d29, 0x281c0d2b, 0x001a001e, 0x2b1d1a05, 0x39392f2d, 0xff1a1a1a, 0x1a1a001a, 0x1a1a1a1a },
        { 0x5d4b3f2b, 0x2a1e0f2d, 0x001c0028, 0x2e1f1c06, 0x3b3b392f, 0xff1b1b1b, 0x1e1e001e, 0x1e1e1e1e },
        { 0x5d4b3f2b, 0x2a1e0f2d, 0x001c0028, 0x2e1f1c06, 0x3b3b392f, 0xff1c1c1c, 0x1e1e001e, 0x1e1e1e1e },
        { 0x5f4c492c, 0x2c28192f, 0x001e002a, 0x38291e07, 0x3d3c3b39, 0xff1d1d1d, 0x22220022, 0x22222222 },
        { 0x694e4a2e, 0x2d291b39, 0x0028002b, 0x392a2808, 0x3f3e3c3a, 0xff1e1e1e, 0x22220022, 0x22222222 },
        { 0x6a584b38, 0x2f2a1c3a, 0x0029002c, 0x3a2b2909, 0x48483e3b, 0xff1f1f1f, 0x27270027, 0x27272727 },
        { 0x6b594d39, 0x382c1d3b, 0x002a002e, 0x3b2d2a0a, 0x49493f3d, 0xff202020, 0x27270027, 0x27272727 },
        { 0x6c5a4e3a, 0x392d1f3c, 0x002b002f, 0x3c2e2b0b, 0x4a4a483e, 0xff212121, 0x2c2c002c, 0x2c2c2c2c },
        { 0x6e5b583b, 0x3b2f293e, 0x002d0039, 0x3f382d0d, 0x4c4b4a48, 0xff222222, 0x2c2c002c, 0x2c2c2c2c },
        { 0x6f5c593c, 0x3c38293f, 0x002e003a, 0x48392e0e, 0x4d4c4b49, 0xff232323, 0x32320032, 0x32323232 },
        { 0x795e5a3e, 0x3d392b49, 0x0038003b, 0x493a3818, 0x4f4e4c4a, 0xff242424, 0x32320032, 0x32323232 },
        { 0x7a685b48, 0x3f3a2c4a, 0x0039003c, 0x4a3b3919, 0x58584e4b, 0xff252525, 0x38380038, 0x38383838 },
        { 0x7b695d49, 0x483c2d4b, 0x003a003e, 0x4b3d3a1a, 0x59594f4d, 0xff262626, 0x38380038, 0x38383838 },
        { 0x7d6a5e4a, 0x4a3d2f4c, 0x003c0048, 0x4d3e3c1c, 0x5b5a594e, 0xff272727, 0x3e3e003e, 0x3e3e3e3e },
        { 0x7e6b684b, 0x4a3e384d, 0x003d0049, 0x4e483d1d, 0x5c5b5958, 0xff282828, 0x3e3e003e, 0x3e3e3e3e },
        { 0x886d694d, 0x4c483a4f, 0x003f004a, 0x58493f1f, 0x5e5d5b59, 0xff292929, 0x45450045, 0x45454545 },
        { 0x896e6a4e, 0x4d493b59, 0x0048004b, 0x594a4828, 0x5f5e5c5a, 0xff2a2a2a, 0x45450045, 0x45454545 },
        { 0x8a786b58, 0x4f4a3c5a, 0x0049004c, 0x5a4b4929, 0x68685e5b, 0xff2b2b2b, 0x4d4d004d, 0x4d4d4d4d },
        { 0x8b796d59, 0x584c3d5b, 0x004a004e, 0x5b4d4a2a, 0x69695f5d, 0xff2c2c2c, 0x4d4d004d, 0x4d4d4d4d },
        { 0x8c7a6e5a, 0x594d3f5c, 0x004b004f, 0x5d4e4b2b, 0x6b6a685e, 0xff2d2d2d, 0x55550055, 0x55555555 },
        { 0x8e7b785b, 0x5b4f485e, 0x004d0059, 0x5e584d2d, 0x6c6b6a68, 0xff2e2e2e, 0x55550055, 0x55555555 },
        { 0x8f7c795c, 0x5c58495f, 0x004e005a, 0x68594e2e, 0x6d6c6b69, 0xff2f2f2f, 0x5e5e005e, 0x5e5e5e5e },
        { 0x8f7e7a5e, 0x5d594b69, 0x0058005b, 0x695a5838, 0x6f6e6c6a, 0xff303030, 0x5e5e005e, 0x5e5e5e5e },
        { 0x8f887b68, 0x5f5a4c6a, 0x0059005c, 0x6a5b5939, 0x6f6f6e6b, 0xff313131, 0x68680068, 0x68686868 },
        { 0x8f897d69, 0x685c4d6b, 0x005a005e, 0x6b5d5a3a, 0x6f6f6f6d, 0xff323232, 0x68680068, 0x68686868 },
        { 0x8f8a7e6a, 0x695d4f6c, 0x005b0068, 0x6d5e5b3b, 0x6f6f6f6e, 0xff333333, 0x73730073, 0x73737373 }
    },
    // B-Frame
    {
        { 0x3a2a2907, 0x0a08060c, 0x00040206, 0x06020200, 0x180e0c0a, 0xff000000, 0x00000000, 0x00000000 },
        { 0x3a2a2907, 0x0a08060c, 0x00040206, 0x06020200, 0x180e0c0a, 0xff010101, 0x00000000, 0x00000000 },
        { 0x3a2a2907, 0x0a08060c, 0x00040206, 0x06020200, 0x180e0c0a, 0xff020202, 0x00000000, 0x00000000 },
        { 0x3a2a2907, 0x0a08060c, 0x00040206, 0x06020200, 0x180e0c0a, 0xff030303, 0x00000000, 0x00000000 },
        { 0x3a2a2907, 0x0a08060c, 0x00040206, 0x06020200, 0x180e0c0a, 0xff040404, 0x00000000, 0x00000000 },
        { 0x3a2a2907, 0x0a08060c, 0x00040206, 0x06020200, 0x180e0c0a, 0xff050505, 0x00000000, 0x00000000 },
        { 0x3a2a2907, 0x0a08060c, 0x00040206, 0x06020200, 0x180e0c0a, 0xff060606, 0x00000000, 0x00000000 },
        { 0x3a2a2907, 0x0a08060c, 0x00040206, 0x06020200, 0x180e0c0a, 0xff070707, 0x01010001, 0x01010101 },
        { 0x3a2a2907, 0x0a08060c, 0x00040206, 0x06020200, 0x180e0c0a, 0xff080808, 0x01010001, 0x01010101 },
        { 0x3a2a2907, 0x0a08060c, 0x00040206, 0x06020200, 0x180e0c0a, 0xff090909, 0x03030003, 0x03030303 },
        { 0x3a2a2907, 0x0a08060c, 0x00040206, 0x06020200, 0x180e0c0a, 0xff0a0a0a, 0x03030003, 0x03030303 },
        { 0x3a2a2907, 0x0a08060c, 0x00040206, 0x06020200, 0x180e0c0a, 0xff0b0b0b, 0x06060006, 0x06060606 },
        { 0x3a2a2907, 0x0a08060c, 0x00040206, 0x06020200, 0x180e0c0a, 0xff0c0c0c, 0x06060006, 0x06060606 },
        { 0x3a2a2907, 0x0a08060c, 0x00040206, 0x06020200, 0x180e0c0a, 0xff0d0d0d, 0x08080008, 0x08080808 },
        { 0x3a2a2907, 0x0a08060c, 0x00040206, 0x06020200, 0x180e0c0a, 0xff0e0e0e, 0x08080008, 0x08080808 },
        { 0x3a2a2907, 0x0a08060c, 0x00040206, 0x06020200, 0x180e0c0a, 0xff0f0f0f, 0x0b0b000b, 0x0b0b0b0b },
        { 0x4a3a390e, 0x1b190d1c, 0x0008040c, 0x0c040400, 0x281e1c1a, 0xff101010, 0x0b0b000b, 0x0b0b0b0b },
        { 0x4a3a390e, 0x1b190d1c, 0x0008040c, 0x0c040400, 0x281e1c1a, 0xff111111, 0x0d0d000d, 0x0d0d0d0d },
        { 0x4a3a390e, 0x1b190d1c, 0x0008040c, 0x0c040400, 0x281e1c1a, 0xff121212, 0x0d0d000d, 0x0d0d0d0d },
        { 0x4a3a390e, 0x1b190d1c, 0x0008040c, 0x0c040400, 0x281e1c1a, 0xff131313, 0x10100010, 0x10101010 },
        { 0x4f3f3d1b, 0x281d1a29, 0x000c0619, 0x19060600, 0x2c2b291f, 0xff141414, 0x10100010, 0x10101010 },
        { 0x4f3f3d1b, 0x281d1a29, 0x000c0619, 0x19060600, 0x2c2b291f, 0xff151515, 0x13130013, 0x13131313 },
        { 0x4f3f3d1b, 0x281d1a29, 0x000c0619, 0x19060600, 0x2c2b291f, 0xff161616, 0x13130013, 0x13131313 },
        { 0x5a4a491e, 0x2b291d2c, 0x0018081c, 0x1c080800, 0x382e2c2a, 0xff171717, 0x16160016, 0x16161616 },
        { 0x5a4a491e, 0x2b291d2c, 0x0018081c, 0x1c080800, 0x382e2c2a, 0xff181818, 0x16160016, 0x16161616 },
        { 0x5a4a491e, 0x2b291d2c, 0x0018081c, 0x1c080800, 0x382e2c2a, 0xff191919, 0x1a1a001a, 0x1a1a1a1a },
        { 0x5d4d4b29, 0x2d2b282f, 0x001a0a1f, 0x1f0a0a00, 0x3a392f2d, 0xff1a1a1a, 0x1a1a001a, 0x1a1a1a1a },
        { 0x5f4f4d2b, 0x382d2a39, 0x001c0c29, 0x290c0c00, 0x3c3b392f, 0xff1b1b1b, 0x1e1e001e, 0x1e1e1e1e },
        { 0x5f4f4d2b, 0x382d2a39, 0x001c0c29, 0x290c0c00, 0x3c3b392f, 0xff1c1c1c, 0x1e1e001e, 0x1e1e1e1e },
        { 0x69594f2c, 0x392f2b3b, 0x001e0e2b, 0x2b0e0e00, 0x3e3c3b39, 0xff1d1d1d, 0x22220022, 0x22222222 },
        { 0x6a5a592e, 0x3b392d3c, 0x0028182c, 0x2c181800, 0x483e3c3a, 0xff1e1e1e, 0x22220022, 0x22222222 },
        { 0x6b5b5a38, 0x3c3a2f3e, 0x0029192e, 0x2e191900, 0x49483e3b, 0xff1f1f1f, 0x27270027, 0x27272727 },
        { 0x6d5d5b39, 0x3d3b383f, 0x002a1a2f, 0x2f1a1a00, 0x4a493f3d, 0xff202020, 0x27270027, 0x27272727 },
        { 0x6e5e5c3a, 0x3e3c3948, 0x002b1b38, 0x381b1b00, 0x4b4a483e, 0xff212121, 0x2c2c002c, 0x2c2c2c2c },
        { 0x78685e3b, 0x493e3b4a, 0x002d1d3a, 0x3a1d1d00, 0x4d4b4a48, 0xff222222, 0x2c2c002c, 0x2c2c2c2c },
        { 0x79695f3c, 0x493f3b4b, 0x002e1e3b, 0x3b1e1e00, 0x4e4c4b49, 0xff232323, 0x32320032, 0x32323232 },
        { 0x7a6a693e, 0x4b493d4c, 0x0038283c, 0x3c282800, 0x584e4c4a, 0xff242424, 0x32320032, 0x32323232 },
        { 0x7b6b6a48, 0x4c4a3f4e, 0x0039293e, 0x3e292900, 0x59584e4b, 0xff252525, 0x38380038, 0x38383838 },
        { 0x7d6d6b49, 0x4d4b484f, 0x003a2a3f, 0x3f2a2a00, 0x5a594f4d, 0xff262626, 0x38380038, 0x38383838 },
        { 0x7e6e6c4a, 0x4f4c4959, 0x003c2c49, 0x492c2c00, 0x5c5a594e, 0xff272727, 0x3e3e003e, 0x3e3e3e3e },
        { 0x88786d4b, 0x584d4a59, 0x003d2d49, 0x492d2d00, 0x5d5b5958, 0xff282828, 0x3e3e003e, 0x3e3e3e3e },
        { 0x89796f4d, 0x5a4f4c5b, 0x003f2f4b, 0x4b2f2f00, 0x5f5d5b59, 0xff292929, 0x45450045, 0x45454545 },
        { 0x8a7a794e, 0x5b594d5c, 0x0048384c, 0x4c383800, 0x685e5c5a, 0xff2a2a2a, 0x45450045, 0x45454545 },
        { 0x8b7b7a58, 0x5c5a4f5e, 0x0049394e, 0x4e393900, 0x69685e5b, 0xff2b2b2b, 0x4d4d004d, 0x4d4d4d4d },
        { 0x8d7d7b59, 0x5d5b585f, 0x004a3a4f, 0x4f3a3a00, 0x6a695f5d, 0xff2c2c2c, 0x4d4d004d, 0x4d4d4d4d },
        { 0x8e7e7c5a, 0x5f5c5968, 0x004b3b58, 0x583b3b00, 0x6b6a685e, 0xff2d2d2d, 0x55550055, 0x55555555 },
        { 0x8f887e5b, 0x685e5a6a, 0x004d3d5a, 0x5a3d3d00, 0x6d6b6a68, 0xff2e2e2e, 0x55550055, 0x55555555 },
        { 0x8f897f5c, 0x695f5c6b, 0x004e3e5b, 0x5b3e3e00, 0x6e6c6b69, 0xff2f2f2f, 0x5e5e005e, 0x5e5e5e5e },
        { 0x8f8a895e, 0x6b695d6c, 0x0058485c, 0x5c484800, 0x6f6e6c6a, 0xff303030, 0x5e5e005e, 0x5e5e5e5e },
        { 0x8f8b8a68, 0x6c6a5f6e, 0x0059495e, 0x5e494900, 0x6f6f6e6b, 0xff313131, 0x68680068, 0x68686868 },
        { 0x8f8d8b69, 0x6d6b686f, 0x005a4a5f, 0x5f4a4a00, 0x6f6f6f6d, 0xff323232, 0x68680068, 0x68686868 },
        { 0x8f8e8c6a, 0x6f6c6979, 0x005b4b69, 0x694b4b00, 0x6f6f6f6e, 0xff333333, 0x73730073, 0x73737373 }
    }
};

const uint32_t CodechalEncodeAvcEncFeiG12::ME_CURBE_CM_FEI[49] =
{
    0x00000000, 0x00200010, 0x00003939, 0x77a43000, 0x00000000, 0x28300000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000200,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff
};

// AVC PreProc CURBE init data for G12 CM Kernel
const uint32_t CodechalEncodeAvcEncFeiG12::PreProc_CURBE_CM_normal_I_frame[49] =
{
    0x00000082, 0x00000000, 0x00003910, 0x00a83000, 0x00000000, 0x28300000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00040c24, 0x00000000, 0x00000000, 0x40000000, 0x00000080, 0x00003900, 0x28301000,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff
};

const uint32_t CodechalEncodeAvcEncFeiG12::PreProc_CURBE_CM_normal_I_field[49] =
{
    0x00000082, 0x00000000, 0x00003910, 0x00a830c0, 0x00000000, 0x28300000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00040c24, 0x00000000, 0x00000000, 0x40000000, 0x00000080, 0x00003900, 0x28301000,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff
};

const uint32_t CodechalEncodeAvcEncFeiG12::PreProc_CURBE_CM_normal_P_frame[49] =
{
    0x000000a3, 0x00000008, 0x00003910, 0x00ae3000, 0x00000000, 0x28300000, 0x00000000, 0x01400060,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00040c24, 0x00000000, 0x00000000, 0x60000000, 0x000000a1, 0x00003900, 0x28301000,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff
};

const uint32_t CodechalEncodeAvcEncFeiG12::PreProc_CURBE_CM_normal_P_field[49] =
{
    0x000000a3, 0x00000008, 0x00003910, 0x00ae30c0, 0x00000000, 0x28300000, 0x00000000, 0x01400060,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00040c24, 0x00000000, 0x00000000, 0x40000000, 0x000000a1, 0x00003900, 0x28301000,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff
};

const uint32_t CodechalEncodeAvcEncFeiG12::PreProc_CURBE_CM_normal_B_frame[49] =
{
    0x000000a3, 0x00200008, 0x00003910, 0x00aa7700, 0x00000000, 0x20200000, 0x00000000, 0xff400000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00040c24, 0x00000000, 0x00000000, 0x60000000, 0x000000a1, 0x00003900, 0x28301000,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff
};

const uint32_t CodechalEncodeAvcEncFeiG12::PreProc_CURBE_CM_normal_B_field[49] =
{
    0x000000a3, 0x00200008, 0x00003919, 0x00aa77c0, 0x00000000, 0x20200000, 0x00000000, 0xff400000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00040c24, 0x00000000, 0x00000000, 0x40000000, 0x000000a1, 0x00003900, 0x28301000,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff
};

// AVC MBEnc RefCost tables, index [CodingType][QP]
// QP is from 0 - 51, pad it to 64 since BRC needs each subarray size to be 128bytes
const uint16_t CodechalEncodeAvcEncFeiG12::RefCost_MultiRefQp_Fei[NUM_PIC_TYPES][64] =
{
    // I-frame
    {
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000
    },
    // P-slice
    {
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000
    },
    //B-slice
    {
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000
    }
};

// AVC FEI MBEnc CURBE init data for G12 Kernel
const uint32_t CodechalEncodeAvcEncFeiG12::FEI_MBEnc_CURBE_normal_I_frame[91] =
{
    0x00000082, 0x00000000, 0x00003910, 0x00a83000, 0x00000000, 0x28300000, 0x05000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x80800000, 0x00040c24, 0x00000000, 0xffff00ff, 0x40000000, 0x00000080, 0x00003900, 0x28300000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000002,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0xffffffff, 0x00000000, 0x00000000, 0xffffffff,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 0x00000000,
    0x00000000, 0xffffffff, 0xffffffff
};

const uint32_t CodechalEncodeAvcEncFeiG12::FEI_MBEnc_CURBE_normal_I_field[91] =
{
    0x00000082, 0x00000000, 0x00003910, 0x00a830c0, 0x02000000, 0x28300000, 0x05000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x80800000, 0x00040c24, 0x00000000, 0xffff00ff, 0x40000000, 0x00000080, 0x00003900, 0x28300000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000002,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0xffffffff, 0x00000000, 0x00000000, 0xffffffff,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 0x00000000,
    0x00000000, 0xffffffff, 0xffffffff
};

const uint32_t CodechalEncodeAvcEncFeiG12::FEI_MBEnc_CURBE_normal_P_frame[91] =
{
    0x000000a3, 0x00000008, 0x00003910, 0x00ae3000, 0x30000000, 0x28300000, 0x05000000, 0x01400060,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x80010000, 0x00040c24, 0x00000000, 0xffff00ff, 0x60000000, 0x000000a1, 0x00003900, 0x28300000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000002,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0xffffffff, 0x00000000, 0x00000000, 0xffffffff,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 0x00000000,
    0x00000000, 0xffffffff, 0xffffffff
};

const uint32_t CodechalEncodeAvcEncFeiG12::FEI_MBEnc_CURBE_normal_P_field[91] =
{
    0x000000a3, 0x00000008, 0x00003910, 0x00ae30c0, 0x30000000, 0x28300000, 0x05000000, 0x01400060,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x80010000, 0x00040c24, 0x00000000, 0xffff00ff, 0x40000000, 0x000000a1, 0x00003900, 0x28300000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x04000002,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0xffffffff, 0x00000000, 0x00000000, 0xffffffff,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 0x00000000,
    0x00000000, 0xffffffff, 0xffffffff
};

const uint32_t CodechalEncodeAvcEncFeiG12::FEI_MBEnc_CURBE_normal_B_frame[91] =
{
    0x000000a3, 0x00200008, 0x00003910, 0x00aa7700, 0x50020000, 0x20200000, 0x05000000, 0xff400000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x01010000, 0x00040c24, 0x00000000, 0xffff00ff, 0x60000000, 0x000000a1, 0x00003900, 0x28300000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000002,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0xffffffff, 0x00000000, 0x00000000, 0xffffffff,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 0x00000000,
    0x00000000, 0xffffffff, 0xffffffff
};

const uint32_t CodechalEncodeAvcEncFeiG12::FEI_MBEnc_CURBE_normal_B_field[91] =
{
    0x000000a3, 0x00200008, 0x00003919, 0x00aa77c0, 0x50020000, 0x20200000, 0x05000000, 0xff400000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x01010000, 0x00040c24, 0x00000000, 0xffff00ff, 0x40000000, 0x000000a1, 0x00003900, 0x28300000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x04000002,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0xffffffff, 0x00000000, 0x00000000, 0xffffffff,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 0x00000000,
    0x00000000, 0xffffffff, 0xffffffff
};

// FEI AVC I_DIST CURBE init data for G12 Kernel
const uint32_t CodechalEncodeAvcEncFeiG12::FEI_MBEnc_CURBE_I_frame_DIST[91] =
{
    0x00000082, 0x00200008, 0x001e3910, 0x00a83000, 0x90000000, 0x28300000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000100,
    0x80800000, 0x00000000, 0x00000800, 0xffff00ff, 0x40000000, 0x00000080, 0x00003900, 0x28300000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff, 0xffffffff, 0x00000000, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0xffffffff, 0xffffffff
};

CodechalEncodeAvcEncFeiG12::CodechalEncodeAvcEncFeiG12(
        CodechalHwInterface *   hwInterface,
        CodechalDebugInterface *debugInterface,
        PCODECHAL_STANDARD_INFO standardInfo) : CodechalEncodeAvcEncG12(hwInterface, debugInterface, standardInfo)
{
    CODECHAL_ENCODE_FUNCTION_ENTER;

    CODECHAL_ENCODE_ASSERT(m_osInterface);

    Mos_CheckVirtualEngineSupported(m_osInterface, false, true);

    // Virtual Engine is enabled in default.
    Mos_SetVirtualEngineSupported(m_osInterface, true);

    bKernelTrellis             = false;
    bExtendedMvCostRange       = false;
    bBrcSplitEnable            = false;
    bDecoupleMbEncCurbeFromBRC = false;
    bHighTextureModeCostEnable = true;
    bMvDataNeededByBRC         = false;

    this->pfnGetKernelHeaderAndSize = this->GetKernelHeaderAndSize;

    m_feiEnable = true;
    m_cmKernelEnable = true;
    //FEI output Stats which is a superset of MbStats buffer, so no need for MbStats
    m_mbStatsSupported = false;
    m_useCommonKernel = false;

    m_kuid = IDR_CODEC_AllAVCEnc_FEI;

    m_kernelBase = (uint8_t *)IGCODECKRN_G12;
    AddIshSize(m_kuid, m_kernelBase);

    m_vdboxOneDefaultUsed = true;

    Mos_CheckVirtualEngineSupported(m_osInterface, false, false);
}

CodechalEncodeAvcEncFeiG12::~CodechalEncodeAvcEncFeiG12()
{
    if (m_swScoreboardState)
    {
        MOS_Delete(m_swScoreboardState);
        m_swScoreboardState = nullptr;
    }

    if (m_sinlgePipeVeState)
    {
        MOS_FreeMemAndSetNull(m_sinlgePipeVeState);
    }
}

MOS_STATUS CodechalEncodeAvcEncFeiG12::ValidateNumReferences(PCODECHAL_ENCODE_AVC_VALIDATE_NUM_REFS_PARAMS params)
{
    MOS_STATUS eStatus = MOS_STATUS_SUCCESS;

    CODECHAL_ENCODE_FUNCTION_ENTER;
    CODECHAL_ENCODE_CHK_NULL_RETURN(params);
    CODECHAL_ENCODE_CHK_NULL_RETURN(params->pSeqParams);
    CODECHAL_ENCODE_CHK_NULL_RETURN(params->pAvcSliceParams);

    uint8_t numRefIdx0MinusOne = params->pAvcSliceParams->num_ref_idx_l0_active_minus1;
    uint8_t numRefIdx1MinusOne = params->pAvcSliceParams->num_ref_idx_l1_active_minus1;

    // Nothing to do here if numRefIdx = 0 and frame encoded
    if (numRefIdx0MinusOne == 0 && !CodecHal_PictureIsField(params->pPicParams->CurrOriginalPic))
    {
        if (params->wPictureCodingType == P_TYPE ||
            (params->wPictureCodingType == B_TYPE && numRefIdx1MinusOne == 0))
        {
            return eStatus;
        }
    }

    if (params->wPictureCodingType == P_TYPE || params->wPictureCodingType == B_TYPE)
    {
        uint8_t   maxPNumRefIdx0MinusOne = 3;
        uint8_t   maxPNumRefIdx1MinusOne = 1;
        if(params->bPAKonly)
        {
            maxPNumRefIdx0MinusOne = 15;
            maxPNumRefIdx1MinusOne = 15;
        }
        if (params->wPictureCodingType == P_TYPE)
        {
            if (numRefIdx0MinusOne > maxPNumRefIdx0MinusOne)
            {
                CODECHAL_ENCODE_NORMALMESSAGE("Invalid active reference list size.");
                numRefIdx0MinusOne = maxPNumRefIdx0MinusOne;
            }
            numRefIdx1MinusOne = 0;
        }
        else // B_TYPE
        {
            if (numRefIdx0MinusOne > maxPNumRefIdx0MinusOne)
            {
                CODECHAL_ENCODE_NORMALMESSAGE("Invalid active reference list size.");
                numRefIdx0MinusOne = maxPNumRefIdx0MinusOne;
            }

            if (numRefIdx1MinusOne > maxPNumRefIdx1MinusOne)
            {
                CODECHAL_ENCODE_NORMALMESSAGE("Invalid active reference list size.");
                numRefIdx1MinusOne = maxPNumRefIdx1MinusOne;
            }

            // supports at most 1 L1 ref for frame picture for non-PAK only case
            if (CodecHal_PictureIsFrame(params->pPicParams->CurrOriginalPic) && numRefIdx1MinusOne > 0  && (!params->bPAKonly))
            {
                numRefIdx1MinusOne = 0;
            }
        }
    }

    // Override number of references used by VME. PAK uses value from DDI (num_ref_idx_l*_active_minus1_from_DDI)
    params->pAvcSliceParams->num_ref_idx_l0_active_minus1 = numRefIdx0MinusOne;
    params->pAvcSliceParams->num_ref_idx_l1_active_minus1 = numRefIdx1MinusOne;

    return eStatus;
}

MOS_STATUS CodechalEncodeAvcEncFeiG12::InitializePicture(const EncoderParams& params)
{
    CODECHAL_ENCODE_FUNCTION_ENTER;
    if (m_codecFunction == CODECHAL_FUNCTION_FEI_PRE_ENC)
    {
        return EncodePreEncInitialize(params);
    }
    else
    {
        return CodechalEncodeAvcEnc::InitializePicture(params);
    }
}

MOS_STATUS CodechalEncodeAvcEncFeiG12::EncodePreEncInitialize(const EncoderParams& params)
{
    MOS_STATUS eStatus = MOS_STATUS_SUCCESS;

    CODECHAL_ENCODE_FUNCTION_ENTER;

    auto preEncParams = (FeiPreEncParams*)params.pPreEncParams;

    CODECHAL_ENCODE_CHK_NULL_RETURN(m_osInterface);
    CODECHAL_ENCODE_CHK_NULL_RETURN(preEncParams->psCurrOriginalSurface);

    auto avcRefList = &m_refList[0];
    auto avcPicIdx = &m_picIdx[0];

    CodecHalGetResourceInfo(m_osInterface, preEncParams->psCurrOriginalSurface);
    m_rawSurface = *(preEncParams->psCurrOriginalSurface);
    m_rawSurfaceToEnc =
        m_rawSurfaceToPak = &m_rawSurface;
    m_targetUsage = TARGETUSAGE_RT_SPEED;
    m_kernelMode = CodecHal_TargetUsageToMode_AVC[m_targetUsage];
    m_flatnessCheckEnabled = m_flatnessCheckSupported;

    auto prevPic = m_currOriginalPic;
    uint8_t prevIdx = prevPic.FrameIdx;
    uint8_t currIdx = preEncParams->CurrOriginalPicture.FrameIdx;
    bool firstFieldInput = (prevPic.PicFlags == PICTURE_INVALID) && ((preEncParams->CurrOriginalPicture.PicFlags == PICTURE_TOP_FIELD) || (preEncParams->CurrOriginalPicture.PicFlags == PICTURE_BOTTOM_FIELD));

    avcRefList[currIdx]->sRefBuffer = avcRefList[currIdx]->sRefRawBuffer = m_rawSurface;
    avcRefList[currIdx]->RefPic = m_currOriginalPic;
    avcRefList[currIdx]->bUsedAsRef = true;

    // FEI PreEnc doesn't have CurrReconstructedPicture, here we set m_currReconstructedPic = preEncParams->CurrOriginalPicture
    // so it can resue the AVC functions.
    m_currOriginalPic = preEncParams->CurrOriginalPicture;
    m_currReconstructedPic = preEncParams->CurrOriginalPicture;
    m_currRefList = m_refList[m_currOriginalPic.FrameIdx];

    uint8_t numRef = 0;
    for (uint8_t i = 0; i < CODEC_AVC_MAX_NUM_REF_FRAME; i++)
    {
        avcPicIdx[i].bValid = false;
    }

    // FEI only support one past and one future reference picture now
    uint8_t index;
    if (preEncParams->dwNumPastReferences > 0)
    {
        CODECHAL_ENCODE_ASSERT(preEncParams->dwNumPastReferences == 1);
        CODECHAL_ENCODE_ASSERT(!CodecHal_PictureIsInvalid(preEncParams->PastRefPicture));
        index = preEncParams->PastRefPicture.FrameIdx;
        avcPicIdx[numRef].bValid = true;
        avcPicIdx[numRef].ucPicIdx = index;
        avcRefList[index]->RefPic.PicFlags =
            CodecHal_CombinePictureFlags(avcRefList[index]->RefPic, preEncParams->PastRefPicture);
        avcRefList[currIdx]->RefList[numRef] = preEncParams->PastRefPicture;
        numRef++;
    }

    if (preEncParams->dwNumFutureReferences > 0)
    {
        CODECHAL_ENCODE_ASSERT(preEncParams->dwNumFutureReferences == 1);
        CODECHAL_ENCODE_ASSERT(!CodecHal_PictureIsInvalid(preEncParams->FutureRefPicture))
            index = preEncParams->FutureRefPicture.FrameIdx;
        avcPicIdx[numRef].bValid = true;
        avcPicIdx[numRef].ucPicIdx = index;
        avcRefList[index]->RefPic.PicFlags =
            CodecHal_CombinePictureFlags(avcRefList[index]->RefPic, preEncParams->FutureRefPicture);
        avcRefList[currIdx]->RefList[numRef] = preEncParams->FutureRefPicture;
        numRef++;
    }
    avcRefList[currIdx]->ucNumRef = numRef;

    m_verticalLineStride = CODECHAL_VLINESTRIDE_FRAME;
    m_verticalLineStrideOffset = CODECHAL_VLINESTRIDEOFFSET_TOP_FIELD;
    m_meDistortionBottomFieldOffset = 0;
    m_meMvBottomFieldOffset = 0;

    if (CodecHal_PictureIsField(m_currOriginalPic))
    {
        m_frameFieldHeight = ((m_frameHeight + 1) >> 1);
        m_frameFieldHeightInMb = ((m_picHeightInMb + 1) >> 1);
        m_downscaledFrameFieldHeightInMb4x = ((m_downscaledHeightInMb4x + 1) >> 1);
        m_downscaledFrameFieldHeightInMb16x = ((m_downscaledHeightInMb16x + 1) >> 1);
        m_downscaledFrameFieldHeightInMb32x = ((m_downscaledHeightInMb32x + 1) >> 1);
        if (CodecHal_PictureIsFrame(prevPic) || prevIdx != currIdx || firstFieldInput)
        {
            m_firstField = 1;
        }
        else
        {
            m_firstField = 0;
        }

        m_verticalLineStride = CODECHAL_VLINESTRIDE_FIELD;
        m_frameHeight = m_frameFieldHeightInMb * 2 * 16;
        m_picHeightInMb = (uint16_t)(m_frameHeight / 16);
        m_mbvProcStatsBottomFieldOffset = 0;

        if (CodecHal_PictureIsBottomField(m_currOriginalPic))
        {
            m_verticalLineStrideOffset = CODECHAL_VLINESTRIDEOFFSET_BOT_FIELD;

            m_meDistortionBottomFieldOffset =
                MOS_ALIGN_CEIL((m_downscaledWidthInMb4x * 8), 64) *
                MOS_ALIGN_CEIL((m_downscaledFrameFieldHeightInMb4x * 4 * 10), 8);
            m_meMvBottomFieldOffset =
                MOS_ALIGN_CEIL((m_downscaledWidthInMb4x * 32), 64) *
                (m_downscaledFrameFieldHeightInMb4x * 4);
        }
    }
    else
    {
        m_frameFieldHeight = m_frameHeight;
        m_frameFieldHeightInMb = m_picHeightInMb;
        m_downscaledFrameFieldHeightInMb4x = m_downscaledHeightInMb4x;
        m_downscaledFrameFieldHeightInMb16x = m_downscaledHeightInMb16x;
        m_downscaledFrameFieldHeightInMb32x = m_downscaledHeightInMb32x;
        m_firstField = 1;
    }

    if ((preEncParams->bDisableMVOutput == 1) && (preEncParams->bDisableStatisticsOutput == 1))
    {
        m_hmeEnabled = false;
    }
    else
    {
        m_hmeEnabled = (preEncParams->dwNumPastReferences + preEncParams->dwNumFutureReferences) > 0 ? true : false;
    }
    m_scalingEnabled = m_firstField && preEncParams->bInputUpdated;
    m_useRawForRef = m_userFlags.bUseRawPicForRef;

    m_scalingEnabled = (m_hmeSupported || bBrcEnabled) && m_firstField;

    // PREENC doesn't differentiate picture by its "PictureCodingType". However in order to reuse the CODECHAL function,
    // we manually assign the PictureCodingType given its past/future references.
    if (preEncParams->dwNumFutureReferences > 0)
    {
        m_pictureCodingType = B_TYPE;
    }
    else if (preEncParams->dwNumPastReferences > 0)
    {
        m_pictureCodingType = P_TYPE;
    }
    else
    {
        m_pictureCodingType = I_TYPE;
    }

    CODECHAL_ENCODE_CHK_STATUS_RETURN(SetStatusReportParams(m_refList[m_currOriginalPic.FrameIdx]));

    CODECHAL_DEBUG_TOOL(
        m_debugInterface->m_currPic            = m_currOriginalPic;
        m_debugInterface->m_bufferDumpFrameNum = m_storeData;
        m_debugInterface->m_frameType          = m_pictureCodingType;)

    return eStatus;
}

MOS_STATUS CodechalEncodeAvcEncFeiG12::ExecuteKernelFunctions()
{
    if (m_codecFunction == CODECHAL_FUNCTION_FEI_PRE_ENC)
    {
        return EncodePreEncKernelFunctions();
    }
    else
    {
        uint32_t swScoreboardBtCount = 0;
        if (nullptr != m_swScoreboardState)
        {
            swScoreboardBtCount = MOS_ALIGN_CEIL(
                m_swScoreboardState->GetBTCount(),
                m_stateHeapInterface->pStateHeapInterface->GetBtIdxAlignment());
        }

        uint32_t mbEncBtCount = 0;
        if (nullptr != pMbEncKernelStates)
        {
            mbEncBtCount = MOS_ALIGN_CEIL(
                pMbEncKernelStates->KernelParams.iBTCount,
                m_stateHeapInterface->pStateHeapInterface->GetBtIdxAlignment());
        }

        m_maxBtCount = swScoreboardBtCount + mbEncBtCount;
        return CodechalEncodeAvcEncG12::ExecuteKernelFunctions();
    }
}

MOS_STATUS CodechalEncodeAvcEncFeiG12::EncodePreEncKernelFunctions()
{
    MOS_STATUS eStatus = MOS_STATUS_SUCCESS;

    CODECHAL_ENCODE_FUNCTION_ENTER;

    auto preEncParams = (FeiPreEncParams*)m_encodeParams.pPreEncParams;
    auto avcRefList = &m_refList[0];

    CODECHAL_DEBUG_TOOL(CODECHAL_ENCODE_CHK_STATUS_RETURN(m_debugInterface->DumpYUVSurface(
        m_rawSurfaceToEnc,
        CodechalDbgAttr::attrEncodeRawInputSurface,
        "SrcSurf"))
    );

    // save these 2 flags
    auto firstField = m_firstField;
    auto currRefList = m_currRefList;

    // Scaling, HME and PreProc are included in the same task phase
    m_lastEncPhase = true;
    m_firstTaskInPhase = true;

    UpdateSSDSliceCount();

    m_trackedBuf->ResetUsedForCurrFrame();

    bool dsSurfaceInCache;
    uint8_t scaledIdx = m_trackedBuf->PreencLookUpBufIndex(m_currOriginalPic.FrameIdx, &dsSurfaceInCache);
    m_trackedBuf->AllocateForCurrFramePreenc(scaledIdx);
    CODECHAL_ENCODE_CHK_STATUS_RETURN(m_trackedBuf->AllocateSurfaceDS());

    bool dsPastRefInCache = false;
    bool callDsPastRef = false;
    uint8_t pastRefScaledIdx = 0;
    if (preEncParams->dwNumPastReferences > 0)
    {
        pastRefScaledIdx = m_trackedBuf->PreencLookUpBufIndex(preEncParams->PastRefPicture.FrameIdx, &dsPastRefInCache);
        if ((!preEncParams->bPastRefUpdated) && dsPastRefInCache)
        {
            CODECHAL_ENCODE_VERBOSEMESSAGE("find PastRef Downscaled Surface in cache, so skip DS");
        }
        else
        {
            callDsPastRef = true;
        }
    }

    bool dsFutureRefInCache = false;
    bool callDsFutureRef = false;
    uint8_t futureRefScaledIdx = 0;
    if (preEncParams->dwNumFutureReferences > 0)
    {
        futureRefScaledIdx = m_trackedBuf->PreencLookUpBufIndex(preEncParams->FutureRefPicture.FrameIdx, &dsFutureRefInCache);
        if ((!preEncParams->bFutureRefUpdated) && dsFutureRefInCache)
        {
            CODECHAL_ENCODE_VERBOSEMESSAGE("find FutureRef Downscaled Surface in cache, so skip DS");
        }
        else
        {
            callDsFutureRef = true;
        }
    }

    bool callPreEncKernel = (preEncParams->bDisableMVOutput == 0) || (preEncParams->bDisableStatisticsOutput == 0);

    CodechalEncodeCscDs::KernelParams cscScalingKernelParams;

    if ((!preEncParams->bCurPicUpdated) && dsSurfaceInCache)
    {
        CODECHAL_ENCODE_VERBOSEMESSAGE("find Downscaled Surface in cache, so skip DS");
    }
    else
    {
        if (!preEncParams->bCurPicUpdated)
        {
            CODECHAL_ENCODE_VERBOSEMESSAGE("Cannot find matched Downscaled Surface, DS again");
        }
        if (scaledIdx == CODEC_NUM_TRACKED_BUFFERS)
        {
            CODECHAL_ENCODE_ASSERTMESSAGE("Cannot find empty DS slot for preenc.");
            eStatus = MOS_STATUS_INVALID_PARAMETER;
            return eStatus;
        }

        m_firstField = preEncParams->bCurPicUpdated ? 1 : m_firstField;
        m_currRefList->ucScalingIdx = scaledIdx;
        m_currRefList->b4xScalingUsed = false;
        m_currRefList->b16xScalingUsed = false;
        m_currRefList->b32xScalingUsed = false;

        MOS_ZeroMemory(&cscScalingKernelParams, sizeof(cscScalingKernelParams));
        cscScalingKernelParams.bLastTaskInPhase4xDS = !(callDsPastRef || callDsFutureRef || m_hmeEnabled || callPreEncKernel);
        cscScalingKernelParams.b32xScalingInUse = false;
        cscScalingKernelParams.b16xScalingInUse = false;
        CODECHAL_ENCODE_CHK_STATUS_RETURN(m_cscDsState->DsKernel(&cscScalingKernelParams));
    }

    // Scaling for Past ref
    if (callDsPastRef)
    {
        if (!preEncParams->bPastRefUpdated)
        {
            CODECHAL_ENCODE_VERBOSEMESSAGE("Cannot find matched Downscaled Surface, DS again");
        }
        if (pastRefScaledIdx == CODEC_NUM_TRACKED_BUFFERS)
        {
            CODECHAL_ENCODE_ASSERTMESSAGE("Cannot find empty DS slot for preenc.");
            eStatus = MOS_STATUS_INVALID_PARAMETER;
            return eStatus;
        }

        uint8_t pastRefIdx = preEncParams->PastRefPicture.FrameIdx;
        avcRefList[pastRefIdx]->sRefBuffer = avcRefList[pastRefIdx]->sRefRawBuffer = preEncParams->sPastRefSurface;
        avcRefList[pastRefIdx]->RefPic = preEncParams->PastRefPicture;
        avcRefList[pastRefIdx]->bUsedAsRef = true;
        m_firstField = true;
        m_currRefList = avcRefList[pastRefIdx];
        m_currRefList->ucScalingIdx = pastRefScaledIdx;
        m_currRefList->b4xScalingUsed = false;
        m_currRefList->b16xScalingUsed = false;
        m_currRefList->b32xScalingUsed = false;

        MOS_ZeroMemory(&cscScalingKernelParams, sizeof(cscScalingKernelParams));
        cscScalingKernelParams.bLastTaskInPhase4xDS = !(callDsFutureRef || m_hmeEnabled || callPreEncKernel);
        cscScalingKernelParams.b32xScalingInUse = false;
        cscScalingKernelParams.b16xScalingInUse = false;
        cscScalingKernelParams.bRawInputProvided = true;
        cscScalingKernelParams.bScalingforRef = true;
        cscScalingKernelParams.sInputRawSurface = preEncParams->sPastRefSurface;
        cscScalingKernelParams.inputPicture = preEncParams->PastRefPicture;

        if (preEncParams->bPastRefStatsNeeded)
        {
            cscScalingKernelParams.sInputStatsBuffer = preEncParams->sPastRefStatsBuffer;
            if (CodecHal_PictureIsField(m_currOriginalPic))
            {
                cscScalingKernelParams.sInputStatsBotFieldBuffer = preEncParams->sPastRefStatsBotFieldBuffer;
            }
            cscScalingKernelParams.bStatsInputProvided = true;
        }
        m_trackedBuf->AllocateForCurrFramePreenc(pastRefScaledIdx);
        CODECHAL_ENCODE_CHK_STATUS_RETURN(m_cscDsState->DsKernel(&cscScalingKernelParams));
    }

    // Scaling for Future ref
    if (callDsFutureRef)
    {
        if (!preEncParams->bFutureRefUpdated)
        {
            CODECHAL_ENCODE_VERBOSEMESSAGE("Cannot find matched Downscaled Surface, DS again");
        }
        if (futureRefScaledIdx == CODEC_NUM_TRACKED_BUFFERS)
        {
            CODECHAL_ENCODE_ASSERTMESSAGE("Cannot find empty DS slot for preenc.");
            eStatus = MOS_STATUS_INVALID_PARAMETER;
            return eStatus;
        }

        uint8_t futureRefIdx = preEncParams->FutureRefPicture.FrameIdx;
        avcRefList[futureRefIdx]->sRefBuffer = avcRefList[futureRefIdx]->sRefRawBuffer = preEncParams->sFutureRefSurface;
        avcRefList[futureRefIdx]->RefPic = preEncParams->FutureRefPicture;
        avcRefList[futureRefIdx]->bUsedAsRef = true;
        m_firstField = true;
        m_currRefList = avcRefList[futureRefIdx];
        m_currRefList->ucScalingIdx = futureRefScaledIdx;
        m_currRefList->b4xScalingUsed = false;
        m_currRefList->b16xScalingUsed = false;
        m_currRefList->b32xScalingUsed = false;

        MOS_ZeroMemory(&cscScalingKernelParams, sizeof(cscScalingKernelParams));
        cscScalingKernelParams.bLastTaskInPhase4xDS = !(m_hmeEnabled || callPreEncKernel);
        cscScalingKernelParams.b32xScalingInUse = false;
        cscScalingKernelParams.b16xScalingInUse = false;
        cscScalingKernelParams.bRawInputProvided = true;
        cscScalingKernelParams.bScalingforRef = true;
        cscScalingKernelParams.sInputRawSurface = preEncParams->sFutureRefSurface;
        cscScalingKernelParams.inputPicture = preEncParams->FutureRefPicture;

        if (preEncParams->bFutureRefStatsNeeded)
        {
            cscScalingKernelParams.sInputStatsBuffer = preEncParams->sFutureRefStatsBuffer;
            if (CodecHal_PictureIsField(m_currOriginalPic))
            {
                cscScalingKernelParams.sInputStatsBotFieldBuffer = preEncParams->sFutureRefStatsBotFieldBuffer;
            }
            cscScalingKernelParams.bStatsInputProvided = true;
        }
        m_trackedBuf->AllocateForCurrFramePreenc(futureRefScaledIdx);
        CODECHAL_ENCODE_CHK_STATUS_RETURN(m_cscDsState->DsKernel(&cscScalingKernelParams));
    }

    m_firstField = firstField;
    m_currRefList = currRefList;

    if (m_hmeEnabled)
    {
        CODEC_AVC_ENCODE_SLICE_PARAMS     avcSliceParams;

        memset(&avcSliceParams, 0, sizeof(CODEC_AVC_ENCODE_SLICE_PARAMS));
        if (preEncParams->dwNumPastReferences > 0)
        {
            avcSliceParams.num_ref_idx_l0_active_minus1 = 0;
            avcSliceParams.RefPicList[LIST_0][0] = preEncParams->PastRefPicture;
            avcSliceParams.RefPicList[LIST_0][0].FrameIdx = 0;
        }
        else
        {
            avcSliceParams.RefPicList[LIST_0][0].PicFlags = PICTURE_INVALID;
        }

        if (preEncParams->dwNumFutureReferences > 0)
        {
            avcSliceParams.num_ref_idx_l1_active_minus1 = 0;
            avcSliceParams.RefPicList[LIST_1][0] = preEncParams->FutureRefPicture;
            avcSliceParams.RefPicList[LIST_1][0].FrameIdx = (preEncParams->dwNumPastReferences > 0) ? 1 : 0;
        }
        else
        {
            avcSliceParams.RefPicList[LIST_1][0].PicFlags = PICTURE_INVALID;
        }

        m_avcSliceParams = &avcSliceParams;
        m_lastTaskInPhase = !callPreEncKernel;
        CODECHAL_ENCODE_CHK_STATUS_RETURN(GenericEncodeMeKernel(&BrcBuffers, HME_LEVEL_4x));
    }

    m_lastTaskInPhase = true;
    if (callPreEncKernel)
    {
        // Execute the PreEnc kernel only when MV and/or Statistics output required.
        // Especially for I frame case, if user disables the statistics output, the PreEnc can be skipped
        CODECHAL_ENCODE_CHK_STATUS_RETURN(PreProcKernel());

        if(preEncParams->bMBQp){
            CODECHAL_DEBUG_TOOL(CODECHAL_ENCODE_CHK_STATUS_RETURN(m_debugInterface->DumpBuffer(
                     &preEncParams->resMbQpBuffer,
                     CodechalDbgAttr::attrInput,
                     "MbQp",
                      m_picWidthInMb * m_frameFieldHeightInMb,
                     0,
                     CODECHAL_MEDIA_STATE_PREPROC)));
        }
        if(preEncParams->dwMVPredictorCtrl){
            CODECHAL_DEBUG_TOOL(CODECHAL_ENCODE_CHK_STATUS_RETURN(m_debugInterface->DumpBuffer(
                     &preEncParams->resMvPredBuffer,
                     CodechalDbgAttr::attrInput,
                     "MvPredictor",
                     m_picWidthInMb * m_frameFieldHeightInMb * 8,
                     0,
                     CODECHAL_MEDIA_STATE_PREPROC)));
        }
    }

    // Reset buffer ID used for MbEnc kernel performance reports
    m_osInterface->pfnResetPerfBufferID(m_osInterface);

    m_setRequestedEUSlices = false;

    return eStatus;
}

MOS_STATUS CodechalEncodeAvcEncFeiG12::InitKernelStateMe()
{
    MOS_STATUS eStatus = MOS_STATUS_SUCCESS;

    CODECHAL_ENCODE_FUNCTION_ENTER;

    uint8_t* kernelBinary;
    uint32_t kernelSize;

    MOS_STATUS status = CodecHalGetKernelBinaryAndSize(m_kernelBase, m_kuid, &kernelBinary, &kernelSize);
    CODECHAL_ENCODE_CHK_STATUS_RETURN(status);

    for (uint32_t krnStateIdx = 0; krnStateIdx < 2; krnStateIdx++)
    {
        auto kernelStatePtr = &m_meKernelStates[krnStateIdx];
        CODECHAL_KERNEL_HEADER              currKrnHeader;
        CODECHAL_ENCODE_CHK_STATUS_RETURN(GetKernelHeaderAndSize(
            kernelBinary,
            ENC_ME,
            krnStateIdx,
            &currKrnHeader,
            &kernelSize));

        kernelStatePtr->KernelParams.iBTCount = CODECHAL_ENCODE_AVC_ME_NUM_SURFACES_CM_G12;
        kernelStatePtr->KernelParams.iThreadCount = m_renderEngineInterface->GetHwCaps()->dwMaxThreads;
        kernelStatePtr->KernelParams.iCurbeLength = sizeof(CODECHAL_ENCODE_AVC_ME_CURBE_CM_FEI_G12);
        kernelStatePtr->KernelParams.iBlockWidth = CODECHAL_MACROBLOCK_WIDTH;
        kernelStatePtr->KernelParams.iBlockHeight = CODECHAL_MACROBLOCK_HEIGHT;
        kernelStatePtr->KernelParams.iIdCount = 1;

        kernelStatePtr->dwCurbeOffset = m_stateHeapInterface->pStateHeapInterface->GetSizeofCmdInterfaceDescriptorData();
        kernelStatePtr->KernelParams.pBinary = kernelBinary + (currKrnHeader.KernelStartPointer << MHW_KERNEL_OFFSET_SHIFT);
        kernelStatePtr->KernelParams.iSize = kernelSize;
        CODECHAL_ENCODE_CHK_STATUS_RETURN(m_stateHeapInterface->pfnCalculateSshAndBtSizesRequested(
            m_stateHeapInterface,
            kernelStatePtr->KernelParams.iBTCount,
            &kernelStatePtr->dwSshSize,
            &kernelStatePtr->dwBindingTableSize));

        CODECHAL_ENCODE_CHK_STATUS_RETURN(m_hwInterface->MhwInitISH(m_stateHeapInterface, kernelStatePtr));
    }

    // Until a better way can be found, maintain old binding table structures
    auto bindingTable = &m_meBindingTable;
    bindingTable->dwMEMVDataSurface = CODECHAL_ENCODE_AVC_ME_MV_DATA_SURFACE_CM_G12;
    bindingTable->dw16xMEMVDataSurface = CODECHAL_ENCODE_AVC_16xME_MV_DATA_SURFACE_CM_G12;
    bindingTable->dw32xMEMVDataSurface = CODECHAL_ENCODE_AVC_32xME_MV_DATA_SURFACE_CM_G12;
    bindingTable->dwMEDist = CODECHAL_ENCODE_AVC_ME_DISTORTION_SURFACE_CM_G12;
    bindingTable->dwMEBRCDist = CODECHAL_ENCODE_AVC_ME_BRC_DISTORTION_CM_G12;
    bindingTable->dwMECurrForFwdRef = CODECHAL_ENCODE_AVC_ME_CURR_FOR_FWD_REF_CM_G12;
    bindingTable->dwMEFwdRefPicIdx[0] = CODECHAL_ENCODE_AVC_ME_FWD_REF_IDX0_CM_G12;
    bindingTable->dwMEFwdRefPicIdx[1] = CODECHAL_ENCODE_AVC_ME_FWD_REF_IDX1_CM_G12;
    bindingTable->dwMEFwdRefPicIdx[2] = CODECHAL_ENCODE_AVC_ME_FWD_REF_IDX2_CM_G12;
    bindingTable->dwMEFwdRefPicIdx[3] = CODECHAL_ENCODE_AVC_ME_FWD_REF_IDX3_CM_G12;
    bindingTable->dwMEFwdRefPicIdx[4] = CODECHAL_ENCODE_AVC_ME_FWD_REF_IDX4_CM_G12;
    bindingTable->dwMEFwdRefPicIdx[5] = CODECHAL_ENCODE_AVC_ME_FWD_REF_IDX5_CM_G12;
    bindingTable->dwMEFwdRefPicIdx[6] = CODECHAL_ENCODE_AVC_ME_FWD_REF_IDX6_CM_G12;
    bindingTable->dwMEFwdRefPicIdx[7] = CODECHAL_ENCODE_AVC_ME_FWD_REF_IDX7_CM_G12;
    bindingTable->dwMECurrForBwdRef = CODECHAL_ENCODE_AVC_ME_CURR_FOR_BWD_REF_CM_G12;
    bindingTable->dwMEBwdRefPicIdx[0] = CODECHAL_ENCODE_AVC_ME_BWD_REF_IDX0_CM_G12;
    bindingTable->dwMEBwdRefPicIdx[1] = CODECHAL_ENCODE_AVC_ME_BWD_REF_IDX1_CM_G12;

    return eStatus;
}

MOS_STATUS CodechalEncodeAvcEncFeiG12::InitKernelStateMbEnc()
{
    MOS_STATUS eStatus = MOS_STATUS_SUCCESS;

    CODECHAL_ENCODE_FUNCTION_ENTER;

    dwNumMbEncEncKrnStates = MBENC_TARGET_USAGE_CM * m_mbencNumTargetUsagesCmFei;
    pMbEncKernelStates = MOS_NewArray(MHW_KERNEL_STATE, dwNumMbEncEncKrnStates);
    CODECHAL_ENCODE_CHK_NULL_RETURN(pMbEncKernelStates);

    auto kernelStatePtr = pMbEncKernelStates;

    uint8_t* kernelBinary;
    uint32_t kernelSize;

    CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalGetKernelBinaryAndSize(m_kernelBase, m_kuid, &kernelBinary, &kernelSize));
    CODECHAL_KERNEL_HEADER currKrnHeader;

    for (uint32_t krnStateIdx = 0; krnStateIdx < dwNumMbEncEncKrnStates; krnStateIdx++)
    {
        bool kernelState = (krnStateIdx >= MBENC_TARGET_USAGE_CM);

        CODECHAL_ENCODE_CHK_STATUS_RETURN(GetKernelHeaderAndSize(
            kernelBinary,
            (kernelState ? ENC_MBENC_ADV : ENC_MBENC),
            (kernelState ? krnStateIdx - MBENC_TARGET_USAGE_CM : krnStateIdx),
            &currKrnHeader,
            &kernelSize));

        kernelStatePtr->KernelParams.iBTCount     = mbencNumSurfaces;
        kernelStatePtr->KernelParams.iThreadCount = m_renderEngineInterface->GetHwCaps()->dwMaxThreads;
        kernelStatePtr->KernelParams.iCurbeLength = sizeof(CODECHAL_ENCODE_AVC_FEI_MBENC_STATIC_DATA_G12);
        kernelStatePtr->KernelParams.iBlockWidth  = CODECHAL_MACROBLOCK_WIDTH;
        kernelStatePtr->KernelParams.iBlockHeight = CODECHAL_MACROBLOCK_HEIGHT;
        kernelStatePtr->KernelParams.iIdCount     = 1;

        kernelStatePtr->dwCurbeOffset = m_stateHeapInterface->pStateHeapInterface->GetSizeofCmdInterfaceDescriptorData();
        kernelStatePtr->KernelParams.pBinary =
            kernelBinary +
            (currKrnHeader.KernelStartPointer << MHW_KERNEL_OFFSET_SHIFT);
        kernelStatePtr->KernelParams.iSize = kernelSize;

        CODECHAL_ENCODE_CHK_STATUS_RETURN(m_stateHeapInterface->pfnCalculateSshAndBtSizesRequested(
            m_stateHeapInterface,
            kernelStatePtr->KernelParams.iBTCount,
            &kernelStatePtr->dwSshSize,
            &kernelStatePtr->dwBindingTableSize));

        CODECHAL_ENCODE_CHK_STATUS_RETURN(m_hwInterface->MhwInitISH(m_stateHeapInterface, kernelStatePtr));

        kernelStatePtr++;
    }

    // Until a better way can be found, maintain old binding table structures
    auto bindingTable = &MbEncBindingTable;

    bindingTable->dwAvcMBEncMfcAvcPakObj   = mbencMfcAvcPakObj;
    bindingTable->dwAvcMBEncIndMVData      = mbencIndMvData;
    bindingTable->dwAvcMBEncBRCDist        = mbencBrcDistortion;
    bindingTable->dwAvcMBEncCurrY          = mbencCurrY;
    bindingTable->dwAvcMBEncCurrUV         = mbencCurrUv;
    bindingTable->dwAvcMBEncMbSpecificData = mbencMbSpecificData;

    bindingTable->dwAvcMBEncRefPicSelectL0           = mbencRefpicselectL0;
    bindingTable->dwAvcMBEncMVDataFromME             = mbencMvDataFromMe;
    bindingTable->dwAvcMBEncMEDist                   = mbenc4xMeDistortion;
    bindingTable->dwAvcMBEncSliceMapData             = mbencSlicemapData;
    bindingTable->dwAvcMBEncBwdRefMBData             = mbencFwdMbData;
    bindingTable->dwAvcMBEncBwdRefMVData             = mbencFwdMvData;
    bindingTable->dwAvcMBEncMbBrcConstData           = mbencMbbrcConstData;
    bindingTable->dwAvcMBEncMBStats                  = mbencMbStats;
    bindingTable->dwAvcMBEncMADData                  = mbencMadData;
    bindingTable->dwAvcMBEncMbNonSkipMap             = mbencForceNonskipMbMap;
    bindingTable->dwAvcMBEncAdv                      = mbEncAdv;
    bindingTable->dwAvcMbEncBRCCurbeData             = mbencBrcCurbeData;
    bindingTable->dwAvcMBEncStaticDetectionCostTable = mbencSfdCostTable;
    
    bindingTable->dwAvcMBEncVMEDistortion = mbencAuxVmeOut;
    bindingTable->dwAvcMBEncMvPrediction = mbEncMVPredictor;

    // Frame
    bindingTable->dwAvcMBEncMbQpFrame       = mbencMbqp;
    bindingTable->dwAvcMBEncCurrPicFrame[0] = mbencVmeInterPredCurrPicIdx0;
    bindingTable->dwAvcMBEncFwdPicFrame[0]  = mbencVmeInterPredFwdPicIDX0;
    bindingTable->dwAvcMBEncBwdPicFrame[0]  = mbencVmeInterPredBwdPicIDX00;
    bindingTable->dwAvcMBEncFwdPicFrame[1]  = mbencVmeInterPredFwdPicIDX1;
    bindingTable->dwAvcMBEncBwdPicFrame[1]  = mbencVmeInterPredBwdPicIDX10;
    bindingTable->dwAvcMBEncFwdPicFrame[2]  = mbencVmeInterPredFwdPicIDX2;
    bindingTable->dwAvcMBEncFwdPicFrame[3]  = mbencVmeInterPredFwdPicIDX3;
    bindingTable->dwAvcMBEncFwdPicFrame[4]  = mbencVmeInterPredFwdPicIDX4;
    bindingTable->dwAvcMBEncFwdPicFrame[5]  = mbencVmeInterPredFwdPicIDX5;
    bindingTable->dwAvcMBEncFwdPicFrame[6]  = mbencVmeInterPredFwdPicIDX6;
    bindingTable->dwAvcMBEncFwdPicFrame[7]  = mbencVmeInterPredFwdPicIDX7;
    bindingTable->dwAvcMBEncCurrPicFrame[1] = mbencVmeInterPredCurrPicIdx1;
    bindingTable->dwAvcMBEncBwdPicFrame[2]  = mbencVmeInterPredBwdPicIDX01;
    bindingTable->dwAvcMBEncBwdPicFrame[3]  = mbencVmeInterPredBwdPicIDX11;

    // Field
    bindingTable->dwAvcMBEncMbQpField         = mbencMbqp;
    bindingTable->dwAvcMBEncFieldCurrPic[0]   = mbencVmeInterPredCurrPicIdx0;
    bindingTable->dwAvcMBEncFwdPicTopField[0] = mbencVmeInterPredFwdPicIDX0;
    bindingTable->dwAvcMBEncBwdPicTopField[0] = mbencVmeInterPredBwdPicIDX00;
    bindingTable->dwAvcMBEncFwdPicBotField[0] = mbencVmeInterPredFwdPicIDX0;
    bindingTable->dwAvcMBEncBwdPicBotField[0] = mbencVmeInterPredBwdPicIDX00;
    bindingTable->dwAvcMBEncFwdPicTopField[1] = mbencVmeInterPredFwdPicIDX1;
    bindingTable->dwAvcMBEncBwdPicTopField[1] = mbencVmeInterPredBwdPicIDX10;
    bindingTable->dwAvcMBEncFwdPicBotField[1] = mbencVmeInterPredFwdPicIDX1;
    bindingTable->dwAvcMBEncBwdPicBotField[1] = mbencVmeInterPredBwdPicIDX10;
    bindingTable->dwAvcMBEncFwdPicTopField[2] = mbencVmeInterPredFwdPicIDX2;
    bindingTable->dwAvcMBEncFwdPicBotField[2] = mbencVmeInterPredFwdPicIDX2;
    bindingTable->dwAvcMBEncFwdPicTopField[3] = mbencVmeInterPredFwdPicIDX3;
    bindingTable->dwAvcMBEncFwdPicBotField[3] = mbencVmeInterPredFwdPicIDX3;
    bindingTable->dwAvcMBEncFwdPicTopField[4] = mbencVmeInterPredFwdPicIDX4;
    bindingTable->dwAvcMBEncFwdPicBotField[4] = mbencVmeInterPredFwdPicIDX4;
    bindingTable->dwAvcMBEncFwdPicTopField[5] = mbencVmeInterPredFwdPicIDX5;
    bindingTable->dwAvcMBEncFwdPicBotField[5] = mbencVmeInterPredFwdPicIDX5;
    bindingTable->dwAvcMBEncFwdPicTopField[6] = mbencVmeInterPredFwdPicIDX6;
    bindingTable->dwAvcMBEncFwdPicBotField[6] = mbencVmeInterPredFwdPicIDX6;
    bindingTable->dwAvcMBEncFwdPicTopField[7] = mbencVmeInterPredFwdPicIDX7;
    bindingTable->dwAvcMBEncFwdPicBotField[7] = mbencVmeInterPredFwdPicIDX7;
    bindingTable->dwAvcMBEncFieldCurrPic[1]   = mbencVmeInterPredCurrPicIdx1;
    bindingTable->dwAvcMBEncBwdPicTopField[2] = mbencVmeInterPredBwdPicIDX01;
    bindingTable->dwAvcMBEncBwdPicBotField[2] = mbencVmeInterPredBwdPicIDX01;
    bindingTable->dwAvcMBEncBwdPicTopField[3] = mbencVmeInterPredBwdPicIDX11;
    bindingTable->dwAvcMBEncBwdPicBotField[3] = mbencVmeInterPredBwdPicIDX11;

    return eStatus;
}

MOS_STATUS CodechalEncodeAvcEncFeiG12::InitKernelStateWP()
{
    MOS_STATUS eStatus = MOS_STATUS_SUCCESS;

    CODECHAL_ENCODE_FUNCTION_ENTER;

    pWPKernelState = MOS_New(MHW_KERNEL_STATE);
    CODECHAL_ENCODE_CHK_NULL_RETURN(pWPKernelState);

    auto kernelStatePtr = pWPKernelState;

    uint8_t* kernelBinary;
    uint32_t kernelSize;

    CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalGetKernelBinaryAndSize(m_kernelBase, m_kuid, &kernelBinary, &kernelSize));

    CODECHAL_KERNEL_HEADER currKrnHeader;
    CODECHAL_ENCODE_CHK_STATUS_RETURN(GetKernelHeaderAndSize(
        kernelBinary,
        ENC_WP,
        0,
        &currKrnHeader,
        &kernelSize));
    kernelStatePtr->KernelParams.iBTCount          = wpNumSurfaces;
    kernelStatePtr->KernelParams.iThreadCount      = m_renderEngineInterface->GetHwCaps()->dwMaxThreads;
    kernelStatePtr->KernelParams.iCurbeLength      = sizeof(CodechalEncodeAvcEncG12::WpCurbe);
    kernelStatePtr->KernelParams.iBlockWidth       = CODECHAL_MACROBLOCK_WIDTH;
    kernelStatePtr->KernelParams.iBlockHeight      = CODECHAL_MACROBLOCK_HEIGHT;
    kernelStatePtr->KernelParams.iIdCount          = 1;
    kernelStatePtr->KernelParams.iInlineDataLength = 0;

    kernelStatePtr->dwCurbeOffset        = m_stateHeapInterface->pStateHeapInterface->GetSizeofCmdInterfaceDescriptorData();
    kernelStatePtr->KernelParams.pBinary = kernelBinary + (currKrnHeader.KernelStartPointer << MHW_KERNEL_OFFSET_SHIFT);
    kernelStatePtr->KernelParams.iSize   = kernelSize;
    CODECHAL_ENCODE_CHK_STATUS_RETURN(m_stateHeapInterface->pfnCalculateSshAndBtSizesRequested(
        m_stateHeapInterface,
        kernelStatePtr->KernelParams.iBTCount,
        &kernelStatePtr->dwSshSize,
        &kernelStatePtr->dwBindingTableSize));

    CODECHAL_ENCODE_CHK_STATUS_RETURN(m_hwInterface->MhwInitISH(m_stateHeapInterface, kernelStatePtr));

    return eStatus;
}

MOS_STATUS CodechalEncodeAvcEncFeiG12::InitKernelStatePreProc()
{
    MOS_STATUS eStatus = MOS_STATUS_SUCCESS;

    CODECHAL_ENCODE_FUNCTION_ENTER;

    uint8_t* kernelBinary;
    uint32_t kernelSize;

    CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalGetKernelBinaryAndSize(m_kernelBase, m_kuid, &kernelBinary, &kernelSize));

    auto kernelStatePtr = &PreProcKernelState;
    uint32_t krnStateIdx = 0;
    CODECHAL_KERNEL_HEADER currKrnHeader;
    CODECHAL_ENCODE_CHK_STATUS_RETURN(GetKernelHeaderAndSize(
        kernelBinary,
        ENC_PREPROC,
        krnStateIdx,
        &currKrnHeader,
        &kernelSize));

    kernelStatePtr->KernelParams.iBTCount = CODECHAL_ENCODE_AVC_PREPROC_FIELD_NUM_SURFACES_CM_G12;
    kernelStatePtr->KernelParams.iThreadCount = m_renderEngineInterface->GetHwCaps()->dwMaxThreads;
    kernelStatePtr->KernelParams.iCurbeLength = sizeof(CODECHAL_ENCODE_AVC_PREPROC_CURBE_CM_G12);
    kernelStatePtr->KernelParams.iBlockWidth = CODECHAL_MACROBLOCK_WIDTH;
    kernelStatePtr->KernelParams.iBlockHeight = CODECHAL_MACROBLOCK_HEIGHT;
    kernelStatePtr->KernelParams.iIdCount = 1;

    kernelStatePtr->dwCurbeOffset = m_stateHeapInterface->pStateHeapInterface->GetSizeofCmdInterfaceDescriptorData();
    kernelStatePtr->KernelParams.pBinary = kernelBinary + (currKrnHeader.KernelStartPointer << MHW_KERNEL_OFFSET_SHIFT);
    kernelStatePtr->KernelParams.iSize = kernelSize;

    CODECHAL_ENCODE_CHK_STATUS_RETURN(m_stateHeapInterface->pfnCalculateSshAndBtSizesRequested(
        m_stateHeapInterface,
        kernelStatePtr->KernelParams.iBTCount,
        &kernelStatePtr->dwSshSize,
        &kernelStatePtr->dwBindingTableSize));

    CODECHAL_ENCODE_CHK_STATUS_RETURN(m_hwInterface->MhwInitISH(m_stateHeapInterface, kernelStatePtr));

    // Until a better way can be found, maintain old binding table structures
    auto bindingTable = &PreProcBindingTable;

    bindingTable->dwAvcPreProcCurrY = CODECHAL_ENCODE_AVC_PREPROC_CURR_Y_CM_G12;
    bindingTable->dwAvcPreProcCurrUV = CODECHAL_ENCODE_AVC_PREPROC_CURR_UV_CM_G12;
    bindingTable->dwAvcPreProcMVDataFromHME = CODECHAL_ENCODE_AVC_PREPROC_HME_MV_DATA_CM_G12;
    bindingTable->dwAvcPreProcMvPredictor = CODECHAL_ENCODE_AVC_PREPROC_MV_PREDICTOR_CM_G12;
    bindingTable->dwAvcPreProcMbQp = CODECHAL_ENCODE_AVC_PREPROC_MBQP_CM_G12;
    bindingTable->dwAvcPreProcMvDataOut = CODECHAL_ENCODE_AVC_PREPROC_MV_DATA_CM_G12;
    bindingTable->dwAvcPreProcMbStatsOut = CODECHAL_ENCODE_AVC_PREPROC_MB_STATS_CM_G12;
    bindingTable->dwAvcPreProcVMECurrPicFrame[0] = CODECHAL_ENCODE_AVC_PREPROC_VME_CURR_PIC_IDX_0_CM_G12;
    bindingTable->dwAvcPreProcVMEFwdPicFrame = CODECHAL_ENCODE_AVC_PREPROC_VME_FWD_PIC_IDX0_CM_G12;
    bindingTable->dwAvcPreProcVMEBwdPicFrame[0] = CODECHAL_ENCODE_AVC_PREPROC_VME_BWD_PIC_IDX0_0_CM_G12;
    bindingTable->dwAvcPreProcVMECurrPicFrame[1] = CODECHAL_ENCODE_AVC_PREPROC_VME_CURR_PIC_IDX_1_CM_G12;
    bindingTable->dwAvcPreProcVMEBwdPicFrame[1] = CODECHAL_ENCODE_AVC_PREPROC_VME_BWD_PIC_IDX0_1_CM_G12;
    bindingTable->dwAvcPreProcFtqLut = CODECHAL_ENCODE_AVC_PREPROC_FTQ_LUT_CM_G12;

    //field case
    bindingTable->dwAvcPreProcVMECurrPicField[0] = CODECHAL_ENCODE_AVC_PREPROC_VME_FIELD_CURR_PIC_IDX_0_CM_G12;
    bindingTable->dwAvcPreProcVMEFwdPicField[0] = CODECHAL_ENCODE_AVC_PREPROC_VME_FIELD_FWD_PIC_IDX0_0_CM_G12;

    bindingTable->dwAvcPreProcVMEFwdPicField[1] = CODECHAL_ENCODE_AVC_PREPROC_VME_FIELD_FWD_PIC_IDX0_1_CM_G12;

    bindingTable->dwAvcPreProcVMECurrPicField[1] = CODECHAL_ENCODE_AVC_PREPROC_VME_FIELD_CURR_PIC_IDX_1_CM_G12;
    bindingTable->dwAvcPreProcVMEBwdPicField[0] = CODECHAL_ENCODE_AVC_PREPROC_VME_FIELD_BWD_PIC_IDX0_0_CM_G12;

    bindingTable->dwAvcPreProcVMEBwdPicField[1] = CODECHAL_ENCODE_AVC_PREPROC_VME_FIELD_BWD_PIC_IDX0_1_CM_G12;

    bindingTable->dwAvcPreProcFtqLutField = CODECHAL_ENCODE_AVC_PREPROC_FIELD_FTQ_LUT_CM_G12;

    return eStatus;
}

MOS_STATUS CodechalEncodeAvcEncFeiG12::PreProcKernel()
{
    MOS_STATUS eStatus = MOS_STATUS_SUCCESS;

    CODECHAL_ENCODE_FUNCTION_ENTER;

    auto preEncParams = (FeiPreEncParams*)m_encodeParams.pPreEncParams;
    auto refList = &m_refList[0];

    auto encFunctionType = CODECHAL_MEDIA_STATE_PREPROC;
    auto kernelState = &PreProcKernelState;

    PerfTagSetting perfTag;
    perfTag.Value = 0;
    perfTag.Mode = (uint16_t)m_mode & CODECHAL_ENCODE_MODE_BIT_MASK;
    perfTag.CallType = CODECHAL_ENCODE_PERFTAG_CALL_PREPROC_KERNEL;
    perfTag.PictureCodingType = m_pictureCodingType;
    m_osInterface->pfnSetPerfTag(m_osInterface, perfTag.Value);

    // If Single Task Phase is not enabled, use BT count for the kernel state.
    if (m_firstTaskInPhase == true || !m_singleTaskPhaseSupported)
    {
        uint32_t maxBtCount = m_singleTaskPhaseSupported ?
            m_maxBtCount : kernelState->KernelParams.iBTCount;
        CODECHAL_ENCODE_CHK_STATUS_RETURN(m_stateHeapInterface->pfnRequestSshSpaceForCmdBuf(
            m_stateHeapInterface,
            maxBtCount));
        m_vmeStatesSize = m_hwInterface->GetKernelLoadCommandSize(maxBtCount);
        CODECHAL_ENCODE_CHK_STATUS_RETURN(VerifySpaceAvailable());
    }

    // Set up the DSH/SSH as normal
    CODECHAL_ENCODE_CHK_STATUS_RETURN(m_hwInterface->AssignDshAndSshSpace(
        m_stateHeapInterface,
        kernelState,
        false,
        0,
        false,
        m_storeData));

    MHW_INTERFACE_DESCRIPTOR_PARAMS idParams;
    MOS_ZeroMemory(&idParams, sizeof(idParams));
    idParams.pKernelState = kernelState;
    CODECHAL_ENCODE_CHK_STATUS_RETURN(m_stateHeapInterface->pfnSetInterfaceDescriptor(
        m_stateHeapInterface,
        1,
        &idParams));

    // Setup Curbe
    CODECHAL_ENCODE_AVC_PREPROC_CURBE_PARAMS preProcCurbeParams;
    MOS_ZeroMemory(&preProcCurbeParams, sizeof(preProcCurbeParams));
    preProcCurbeParams.pPreEncParams = preEncParams;
    preProcCurbeParams.wPicWidthInMb = m_picWidthInMb;
    preProcCurbeParams.wFieldFrameHeightInMb = m_frameFieldHeightInMb;
    preProcCurbeParams.pKernelState = kernelState;

    CODECHAL_ENCODE_CHK_STATUS_RETURN(SetCurbeAvcPreProc(
        &preProcCurbeParams));

    CODECHAL_DEBUG_TOOL(
    CODECHAL_ENCODE_CHK_STATUS_RETURN(m_debugInterface->DumpKernelRegion(
        encFunctionType,
        MHW_DSH_TYPE,
        kernelState));

    CODECHAL_ENCODE_CHK_STATUS_RETURN(m_debugInterface->DumpCurbe(
        encFunctionType,
        kernelState));

    CODECHAL_ENCODE_CHK_STATUS_RETURN(m_debugInterface->DumpKernelRegion(
        encFunctionType,
        MHW_ISH_TYPE,
        kernelState));
    )

    for (uint8_t i = 0; i < CODEC_AVC_MAX_NUM_REF_FRAME; i++)
    {
        if (m_picIdx[i].bValid)
        {
            uint8_t index = m_picIdx[i].ucPicIdx;
            refList[index]->sRefBuffer = refList[index]->sRefRawBuffer;

            CodecHalGetResourceInfo(m_osInterface, &refList[index]->sRefBuffer);
        }
    }

    MOS_COMMAND_BUFFER cmdBuffer;
    CODECHAL_ENCODE_CHK_STATUS_RETURN(m_osInterface->pfnGetCommandBuffer(m_osInterface, &cmdBuffer, 0));

    SendKernelCmdsParams sendKernelCmdsParams = SendKernelCmdsParams();
    sendKernelCmdsParams.EncFunctionType = encFunctionType;
    sendKernelCmdsParams.ucDmvPredFlag = (m_pictureCodingType == I_TYPE) ? 0 : m_avcSliceParams->direct_spatial_mv_pred_flag;

    sendKernelCmdsParams.pKernelState = kernelState;
    CODECHAL_ENCODE_CHK_STATUS_RETURN(SendGenericKernelCmds(&cmdBuffer, &sendKernelCmdsParams));

    // Set up FtqLut Buffer if there is QP change within a frame
    if (preEncParams->bMBQp)
    {
        CODECHAL_ENCODE_AVC_INIT_MBBRC_CONSTANT_DATA_BUFFER_PARAMS initMbBrcConstantDataBufferParams;

        MOS_ZeroMemory(&initMbBrcConstantDataBufferParams, sizeof(initMbBrcConstantDataBufferParams));
        initMbBrcConstantDataBufferParams.pOsInterface = m_osInterface;
        initMbBrcConstantDataBufferParams.presBrcConstantDataBuffer =
            &BrcBuffers.resMbBrcConstDataBuffer[m_currRecycledBufIdx];
        initMbBrcConstantDataBufferParams.bPreProcEnable = true;
        initMbBrcConstantDataBufferParams.bEnableKernelTrellis = bKernelTrellis && m_trellisQuantParams.dwTqEnabled;;

        CODECHAL_ENCODE_CHK_STATUS_RETURN(InitMbBrcConstantDataBuffer(&initMbBrcConstantDataBufferParams));
    }

    // Add binding table
    CODECHAL_ENCODE_CHK_STATUS_RETURN(m_stateHeapInterface->pfnSetBindingTable(
        m_stateHeapInterface,
        kernelState));

    //Add surface states
    CODECHAL_ENCODE_AVC_PREPROC_SURFACE_PARAMS preProcSurfaceParams;
    MOS_ZeroMemory(&preProcSurfaceParams, sizeof(preProcSurfaceParams));
    preProcSurfaceParams.pPreEncParams = preEncParams;
    preProcSurfaceParams.ppRefList = &m_refList[0];
    preProcSurfaceParams.pCurrOriginalPic = &m_currOriginalPic;
    preProcSurfaceParams.psCurrPicSurface = m_rawSurfaceToEnc;
    preProcSurfaceParams.ps4xMeMvDataBuffer = &m_4xMeMvDataBuffer;
    preProcSurfaceParams.presFtqLutBuffer = &BrcBuffers.resMbBrcConstDataBuffer[m_currRecycledBufIdx];
    preProcSurfaceParams.dwMeMvBottomFieldOffset = m_meMvBottomFieldOffset;
    preProcSurfaceParams.dwFrameWidthInMb = (uint32_t)m_picWidthInMb;
    preProcSurfaceParams.dwFrameFieldHeightInMb = (uint32_t)m_frameFieldHeightInMb;
    preProcSurfaceParams.dwMBVProcStatsBottomFieldOffset =
        CodecHal_PictureIsBottomField(m_currOriginalPic) ? m_mbvProcStatsBottomFieldOffset : 0;
    // Interleaved input surfaces
    preProcSurfaceParams.dwVerticalLineStride = m_verticalLineStride;
    preProcSurfaceParams.dwVerticalLineStrideOffset = m_verticalLineStrideOffset;
    preProcSurfaceParams.bHmeEnabled = m_hmeEnabled;
    preProcSurfaceParams.pPreProcBindingTable = &PreProcBindingTable;
    preProcSurfaceParams.pKernelState = kernelState;

    CODECHAL_ENCODE_CHK_STATUS_RETURN(SendAvcPreProcSurfaces(&cmdBuffer, &preProcSurfaceParams));

    uint32_t resolutionX = (uint32_t)m_picWidthInMb;
    uint32_t resolutionY = (uint32_t)m_frameFieldHeightInMb;

    CODECHAL_WALKER_CODEC_PARAMS walkerCodecParams;
    MOS_ZeroMemory(&walkerCodecParams, sizeof(walkerCodecParams));
    walkerCodecParams.WalkerMode = m_walkerMode;
    walkerCodecParams.dwResolutionX = resolutionX;
    walkerCodecParams.dwResolutionY = resolutionY;
    walkerCodecParams.bNoDependency = true;
    walkerCodecParams.bMbaff = m_mbaffEnabled;
    walkerCodecParams.bGroupIdSelectSupported = m_groupIdSelectSupported;
    walkerCodecParams.ucGroupId = m_groupId;

    MHW_WALKER_PARAMS walkerParams;
    CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalInitMediaObjectWalkerParams(
        m_hwInterface,
        &walkerParams,
        &walkerCodecParams));

    CODECHAL_ENCODE_CHK_STATUS_RETURN(m_renderEngineInterface->AddMediaObjectWalkerCmd(
        &cmdBuffer,
        &walkerParams));

    CODECHAL_ENCODE_CHK_STATUS_RETURN(EndStatusReport(&cmdBuffer, encFunctionType));

    // Add dump for MBEnc surface state heap here
    CODECHAL_DEBUG_TOOL(
        CODECHAL_ENCODE_CHK_STATUS_RETURN(m_debugInterface->DumpKernelRegion(
            encFunctionType,
            MHW_SSH_TYPE,
            kernelState));
    )

    CODECHAL_DEBUG_TOOL(CODECHAL_ENCODE_CHK_STATUS_RETURN(m_debugInterface->DumpCmdBuffer(
        &cmdBuffer,
        encFunctionType,
        nullptr)));

    CODECHAL_ENCODE_CHK_STATUS_RETURN(m_stateHeapInterface->pfnSubmitBlocks(
        m_stateHeapInterface,
        kernelState));

    if (!m_singleTaskPhaseSupported || m_lastTaskInPhase)
    {
        CODECHAL_ENCODE_CHK_STATUS_RETURN(m_stateHeapInterface->pfnUpdateGlobalCmdBufId(
            m_stateHeapInterface));
        CODECHAL_ENCODE_CHK_STATUS_RETURN(m_miInterface->AddMiBatchBufferEnd(&cmdBuffer, nullptr));
    }

    CODECHAL_ENCODE_CHK_STATUS_RETURN(m_hwInterface->UpdateSSEuForCmdBuffer(&cmdBuffer, m_singleTaskPhaseSupported, m_lastTaskInPhase));

    m_osInterface->pfnReturnCommandBuffer(m_osInterface, &cmdBuffer, 0);

    if ((!m_singleTaskPhaseSupported || m_lastTaskInPhase))
    {
        m_osInterface->pfnSubmitCommandBuffer(m_osInterface, &cmdBuffer, m_renderContextUsesNullHw);
        m_lastTaskInPhase = false;
    }

    return eStatus;
}

MOS_STATUS CodechalEncodeAvcEncFeiG12::SetCurbeMe(MeCurbeParams* params)
{
    MOS_STATUS   eStatus = MOS_STATUS_SUCCESS;

    CODECHAL_ENCODE_FUNCTION_ENTER;

    CODECHAL_ENCODE_CHK_NULL_RETURN(params);

    auto preEncParams = (FeiPreEncParams*)m_encodeParams.pPreEncParams;
    CODECHAL_ENCODE_CHK_NULL_RETURN(preEncParams);

    auto slcParams = m_avcSliceParams;
    bool framePicture = CodecHal_PictureIsFrame(m_currOriginalPic);
    uint32_t scaleFactor;
    uint8_t mvShiftFactor = 0, prevMvReadPosFactor = 0;
    bool useMvFromPrevStep, writeDistortions;
    switch (params->hmeLvl)
    {
    case HME_LEVEL_4x:
        useMvFromPrevStep = false;
        writeDistortions = false;
        scaleFactor = SCALE_FACTOR_4x;
        mvShiftFactor = 2;
        prevMvReadPosFactor = 0;
        break;
    default:
        eStatus = MOS_STATUS_INVALID_PARAMETER;
        return eStatus;
        break;
    }

    CODECHAL_ENCODE_AVC_ME_CURBE_CM_FEI_G12 cmd;
    CODECHAL_ENCODE_CHK_STATUS_RETURN(MOS_SecureMemcpy(
        &cmd,
        sizeof(CODECHAL_ENCODE_AVC_ME_CURBE_CM_FEI_G12),
        ME_CURBE_CM_FEI,
        sizeof(CODECHAL_ENCODE_AVC_ME_CURBE_CM_FEI_G12)));

    cmd.DW3.SubPelMode = 3;
    if (m_fieldScalingOutputInterleaved)
    {
        cmd.DW3.SrcAccess =
            cmd.DW3.RefAccess = CodecHal_PictureIsField(m_currOriginalPic) ? 1 : 0;
        cmd.DW7.SrcFieldPolarity = CodecHal_PictureIsBottomField(m_currOriginalPic) ? 1 : 0;
    }

    cmd.DW4.PictureHeightMinus1 =
        CODECHAL_GET_HEIGHT_IN_MACROBLOCKS(m_frameFieldHeight / scaleFactor) - 1;
    cmd.DW4.PictureWidth =
        CODECHAL_GET_HEIGHT_IN_MACROBLOCKS(m_frameWidth / scaleFactor);
    cmd.DW5.QpPrimeY = preEncParams->dwFrameQp;
    cmd.DW6.WriteDistortions = writeDistortions;
    cmd.DW6.UseMvFromPrevStep = useMvFromPrevStep;

    cmd.DW6.SuperCombineDist = m_superCombineDistGeneric[m_targetUsage];
    cmd.DW6.MaxVmvR = (framePicture) ?
        CodecHalAvcEncode_GetMaxMvLen(CODEC_AVC_LEVEL_52) * 4 :
        (CodecHalAvcEncode_GetMaxMvLen(CODEC_AVC_LEVEL_52) >> 1) * 4;

    if (m_pictureCodingType == B_TYPE)
    {
        // This field is irrelevant since we are not using the bi-direct search.
        // set it to 32
        cmd.DW1.BiWeight = 32;
        cmd.DW13.NumRefIdxL1MinusOne = slcParams->num_ref_idx_l1_active_minus1;
    }

    if (m_pictureCodingType == P_TYPE ||
        m_pictureCodingType == B_TYPE)
    {
        cmd.DW13.NumRefIdxL0MinusOne = slcParams->num_ref_idx_l0_active_minus1;
    }

    if (!framePicture)
    {
        if (m_pictureCodingType != I_TYPE)
        {
            cmd.DW14.List0RefID0FieldParity = CodecHalAvcEncode_GetFieldParity(slcParams, LIST_0, CODECHAL_ENCODE_REF_ID_0);
            cmd.DW14.List0RefID1FieldParity = CodecHalAvcEncode_GetFieldParity(slcParams, LIST_0, CODECHAL_ENCODE_REF_ID_1);
            cmd.DW14.List0RefID2FieldParity = CodecHalAvcEncode_GetFieldParity(slcParams, LIST_0, CODECHAL_ENCODE_REF_ID_2);
            cmd.DW14.List0RefID3FieldParity = CodecHalAvcEncode_GetFieldParity(slcParams, LIST_0, CODECHAL_ENCODE_REF_ID_3);
            cmd.DW14.List0RefID4FieldParity = CodecHalAvcEncode_GetFieldParity(slcParams, LIST_0, CODECHAL_ENCODE_REF_ID_4);
            cmd.DW14.List0RefID5FieldParity = CodecHalAvcEncode_GetFieldParity(slcParams, LIST_0, CODECHAL_ENCODE_REF_ID_5);
            cmd.DW14.List0RefID6FieldParity = CodecHalAvcEncode_GetFieldParity(slcParams, LIST_0, CODECHAL_ENCODE_REF_ID_6);
            cmd.DW14.List0RefID7FieldParity = CodecHalAvcEncode_GetFieldParity(slcParams, LIST_0, CODECHAL_ENCODE_REF_ID_7);
        }
        if (m_pictureCodingType == B_TYPE)
        {
            cmd.DW14.List1RefID0FieldParity = CodecHalAvcEncode_GetFieldParity(slcParams, LIST_1, CODECHAL_ENCODE_REF_ID_0);
            cmd.DW14.List1RefID1FieldParity = CodecHalAvcEncode_GetFieldParity(slcParams, LIST_1, CODECHAL_ENCODE_REF_ID_1);
        }
    }

    cmd.DW15.MvShiftFactor = mvShiftFactor;
    cmd.DW15.PrevMvReadPosFactor = prevMvReadPosFactor;

    // r3 & r4
    uint8_t meMethod = (m_pictureCodingType == B_TYPE) ? m_bMeMethodGeneric[m_targetUsage] : m_meMethodGeneric[m_targetUsage];
    uint8_t tableIdx = (m_pictureCodingType == B_TYPE) ? 1 : 0;
    eStatus = MOS_SecureMemcpy(&(cmd.SPDelta), 14 * sizeof(uint32_t), CodechalEncoderState::m_encodeSearchPath[tableIdx][meMethod], 14 * sizeof(uint32_t));
    if (eStatus != MOS_STATUS_SUCCESS)
    {
        CODECHAL_ENCODE_ASSERTMESSAGE("Failed to copy memory.");
        return eStatus;
    }

    // r5
    cmd.DW40._4xMeMvOutputDataSurfIndex = CODECHAL_ENCODE_AVC_ME_MV_DATA_SURFACE_CM_G12;
    cmd.DW41._16xOr32xMeMvInputDataSurfIndex = (params->hmeLvl == HME_LEVEL_32x) ?
        CODECHAL_ENCODE_AVC_32xME_MV_DATA_SURFACE_CM_G12 : CODECHAL_ENCODE_AVC_16xME_MV_DATA_SURFACE_CM_G12;
    cmd.DW42._4xMeOutputDistSurfIndex = CODECHAL_ENCODE_AVC_ME_DISTORTION_SURFACE_CM_G12;
    cmd.DW43._4xMeOutputBrcDistSurfIndex = CODECHAL_ENCODE_AVC_ME_BRC_DISTORTION_CM_G12;
    cmd.DW44.VMEFwdInterPredictionSurfIndex = CODECHAL_ENCODE_AVC_ME_CURR_FOR_FWD_REF_CM_G12;
    cmd.DW45.VMEBwdInterPredictionSurfIndex = CODECHAL_ENCODE_AVC_ME_CURR_FOR_BWD_REF_CM_G12;
//    cmd.DW46.VDEncStreamInOutputSurfIndex = CODECHAL_ENCODE_AVC_ME_VDENC_STREAMIN_OUTPUT_BUFFER_CM_G12;
//    cmd.DW47.VDEncStreamInInputSurfIndex = CODECHAL_ENCODE_AVC_ME_VDENC_STREAMIN_INPUT_BUFFER_CM_G12;
//    cmd.DW48.SumMVandDistortionOutputSurfIndex = CODECHAL_ENCODE_AVC_ME_SUM_MV_AND_DISTORTION_BUFFER_CM_G12;

    CODECHAL_ENCODE_CHK_STATUS_RETURN(params->pKernelState->m_dshRegion.AddData(
        &cmd,
        params->pKernelState->dwCurbeOffset,
        sizeof(cmd)));

    return eStatus;
}

MOS_STATUS CodechalEncodeAvcEncFeiG12::SendMeSurfaces(PMOS_COMMAND_BUFFER cmdBuffer, MeSurfaceParams* params)
{
    MOS_STATUS eStatus = MOS_STATUS_SUCCESS;

    CODECHAL_ENCODE_FUNCTION_ENTER;

    CODECHAL_ENCODE_CHK_NULL_RETURN(m_hwInterface);
    CODECHAL_ENCODE_CHK_NULL_RETURN(cmdBuffer);
    CODECHAL_ENCODE_CHK_NULL_RETURN(params);
    CODECHAL_ENCODE_CHK_NULL_RETURN(params->pKernelState);
    CODECHAL_ENCODE_CHK_NULL_RETURN(params->pCurrOriginalPic);
    CODECHAL_ENCODE_CHK_NULL_RETURN(params->ps4xMeMvDataBuffer);
    CODECHAL_ENCODE_CHK_NULL_RETURN(params->psMeBrcDistortionBuffer);

    // only 4x HME is supported for FEI
    CODECHAL_ENCODE_ASSERT(!params->b32xMeInUse && !params->b16xMeInUse);
    CODECHAL_ENCODE_CHK_NULL_RETURN(params->pMeBindingTable);
    auto meBindingTable = params->pMeBindingTable;

    bool currFieldPicture = CodecHal_PictureIsField(*(params->pCurrOriginalPic)) ? 1 : 0;
    bool currBottomField = CodecHal_PictureIsBottomField(*(params->pCurrOriginalPic)) ? 1 : 0;
    uint8_t currVDirection = (!currFieldPicture) ? CODECHAL_VDIRECTION_FRAME :
        ((currBottomField) ? CODECHAL_VDIRECTION_BOT_FIELD : CODECHAL_VDIRECTION_TOP_FIELD);
    uint8_t scaledIdx = params->ppRefList[m_currReconstructedPic.FrameIdx]->ucScalingIdx;
    auto currScaledSurface = m_trackedBuf->Get4xDsSurface(scaledIdx);
    auto meMvDataBuffer = params->ps4xMeMvDataBuffer;
    uint32_t meMvBottomFieldOffset = params->dw4xMeMvBottomFieldOffset;
    uint32_t currScaledBottomFieldOffset = params->dw4xScaledBottomFieldOffset;

    // Reference height and width information should be taken from the current scaled surface rather
    // than from the reference scaled surface in the case of PAFF.
    auto refScaledSurface = *currScaledSurface;

    uint32_t width = MOS_ALIGN_CEIL(params->dwDownscaledWidthInMb * 32, 64);
    uint32_t height = params->dwDownscaledHeightInMb * 4 * CODECHAL_ENCODE_ME_DATA_SIZE_MULTIPLIER;

    // Force the values
    meMvDataBuffer->dwWidth = width;
    meMvDataBuffer->dwHeight = height;
    meMvDataBuffer->dwPitch = width;

    CODECHAL_SURFACE_CODEC_PARAMS   surfaceParams;
    MOS_ZeroMemory(&surfaceParams, sizeof(surfaceParams));
    surfaceParams.bIs2DSurface = true;
    surfaceParams.bMediaBlockRW = true;
    surfaceParams.psSurface = meMvDataBuffer;
    surfaceParams.dwOffset = meMvBottomFieldOffset;
    surfaceParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_MV_DATA_ENCODE].Value;
    surfaceParams.dwBindingTableOffset = meBindingTable->dwMEMVDataSurface;
    surfaceParams.bIsWritable = true;
    surfaceParams.bRenderTarget = true;
    CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
        m_hwInterface,
        cmdBuffer,
        &surfaceParams,
        params->pKernelState));

    // Insert Distortion buffers only for 4xMe case
    MOS_ZeroMemory(&surfaceParams, sizeof(surfaceParams));
    surfaceParams.bIs2DSurface = true;
    surfaceParams.bMediaBlockRW = true;
    surfaceParams.psSurface = params->psMeBrcDistortionBuffer;
    surfaceParams.dwOffset = params->dwMeBrcDistortionBottomFieldOffset;
    surfaceParams.dwBindingTableOffset = meBindingTable->dwMEBRCDist;
    surfaceParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_BRC_ME_DISTORTION_ENCODE].Value;
    surfaceParams.bIsWritable = true;
    surfaceParams.bRenderTarget = true;
    CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
        m_hwInterface,
        cmdBuffer,
        &surfaceParams,
        params->pKernelState));

    MOS_ZeroMemory(&surfaceParams, sizeof(surfaceParams));
    surfaceParams.bIs2DSurface = true;
    surfaceParams.bMediaBlockRW = true;
    surfaceParams.psSurface = params->psMeDistortionBuffer;
    surfaceParams.dwOffset = params->dwMeDistortionBottomFieldOffset;
    surfaceParams.dwBindingTableOffset = meBindingTable->dwMEDist;
    surfaceParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_ME_DISTORTION_ENCODE].Value;
    surfaceParams.bIsWritable = true;
    surfaceParams.bRenderTarget = true;
    CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
        m_hwInterface,
        cmdBuffer,
        &surfaceParams,
        params->pKernelState));

    // Setup references 1...n
    // LIST 0 references
    uint32_t refScaledBottomFieldOffset;
    uint8_t  refPicIdx, refIdx;
    bool refFieldPicture, refBottomField;
    for (refIdx = 0; refIdx <= params->dwNumRefIdxL0ActiveMinus1; refIdx++)
    {
        auto refPic = params->pL0RefFrameList[refIdx];

        if (!CodecHal_PictureIsInvalid(refPic) && params->pPicIdx[refPic.FrameIdx].bValid)
        {
            if (refIdx == 0)
            {
                // Current Picture Y - VME
                MOS_ZeroMemory(&surfaceParams, sizeof(surfaceParams));
                surfaceParams.bUseAdvState = true;
                surfaceParams.psSurface = currScaledSurface;
                surfaceParams.dwOffset = currBottomField ? currScaledBottomFieldOffset : 0;
                surfaceParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_CURR_ENCODE].Value;
                surfaceParams.dwBindingTableOffset = meBindingTable->dwMECurrForFwdRef;
                surfaceParams.ucVDirection = currVDirection;
                CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
                    m_hwInterface,
                    cmdBuffer,
                    &surfaceParams,
                    params->pKernelState));
            }

            refFieldPicture = CodecHal_PictureIsField(refPic) ? 1 : 0;
            refBottomField = (CodecHal_PictureIsBottomField(refPic)) ? 1 : 0;
            refPicIdx = params->pPicIdx[refPic.FrameIdx].ucPicIdx;
            scaledIdx = params->ppRefList[refPicIdx]->ucScalingIdx;

            refScaledSurface.OsResource = m_trackedBuf->Get4xDsSurface(scaledIdx)->OsResource;
            refScaledBottomFieldOffset = refBottomField ? currScaledBottomFieldOffset : 0;

            // L0 Reference Picture Y - VME
            MOS_ZeroMemory(&surfaceParams, sizeof(surfaceParams));
            surfaceParams.bUseAdvState = true;
            surfaceParams.psSurface = &refScaledSurface;
            surfaceParams.dwOffset = refBottomField ? refScaledBottomFieldOffset : 0;
            surfaceParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_REF_ENCODE].Value;
            surfaceParams.dwBindingTableOffset = meBindingTable->dwMEFwdRefPicIdx[refIdx];
            surfaceParams.ucVDirection = !currFieldPicture ? CODECHAL_VDIRECTION_FRAME :
                ((refBottomField) ? CODECHAL_VDIRECTION_BOT_FIELD : CODECHAL_VDIRECTION_TOP_FIELD);
            CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
                m_hwInterface,
                cmdBuffer,
                &surfaceParams,
                params->pKernelState));

            if (currFieldPicture)
            {
                // VME needs to set ref index 1 too for field case
                surfaceParams.dwBindingTableOffset = meBindingTable->dwMEFwdRefPicIdx[refIdx + 1];
                CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
                    m_hwInterface,
                    cmdBuffer,
                    &surfaceParams,
                    params->pKernelState));
            }
        }
    }

    // Setup references 1...n
    // LIST 1 references
    for (refIdx = 0; refIdx <= params->dwNumRefIdxL1ActiveMinus1; refIdx++)
    {
        auto refPic = params->pL1RefFrameList[refIdx];

        if (!CodecHal_PictureIsInvalid(refPic) && params->pPicIdx[refPic.FrameIdx].bValid)
        {
            if (refIdx == 0)
            {
                // Current Picture Y - VME
                MOS_ZeroMemory(&surfaceParams, sizeof(surfaceParams));
                surfaceParams.bUseAdvState = true;
                surfaceParams.psSurface = currScaledSurface;
                surfaceParams.dwOffset = currBottomField ? currScaledBottomFieldOffset : 0;
                surfaceParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_CURR_ENCODE].Value;
                surfaceParams.dwBindingTableOffset = meBindingTable->dwMECurrForBwdRef;
                surfaceParams.ucVDirection = currVDirection;
                CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
                    m_hwInterface,
                    cmdBuffer,
                    &surfaceParams,
                    params->pKernelState));
            }

            refFieldPicture = CodecHal_PictureIsField(refPic) ? 1 : 0;
            refBottomField = (CodecHal_PictureIsBottomField(refPic)) ? 1 : 0;
            refPicIdx = params->pPicIdx[refPic.FrameIdx].ucPicIdx;
            scaledIdx = params->ppRefList[refPicIdx]->ucScalingIdx;

            refScaledSurface.OsResource = m_trackedBuf->Get4xDsSurface(scaledIdx)->OsResource;
            refScaledBottomFieldOffset = refBottomField ? currScaledBottomFieldOffset : 0;

            // L1 Reference Picture Y - VME
            MOS_ZeroMemory(&surfaceParams, sizeof(surfaceParams));
            surfaceParams.bUseAdvState = true;
            surfaceParams.psSurface = &refScaledSurface;
            surfaceParams.dwOffset = refBottomField ? refScaledBottomFieldOffset : 0;
            surfaceParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_REF_ENCODE].Value;
            surfaceParams.dwBindingTableOffset = meBindingTable->dwMEBwdRefPicIdx[refIdx];
            surfaceParams.ucVDirection = (!currFieldPicture) ? CODECHAL_VDIRECTION_FRAME :
                ((refBottomField) ? CODECHAL_VDIRECTION_BOT_FIELD : CODECHAL_VDIRECTION_TOP_FIELD);
            CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
                m_hwInterface,
                cmdBuffer,
                &surfaceParams,
                params->pKernelState));

            if (currFieldPicture)
            {
                // VME needs to set ref index 1 too for field case
                surfaceParams.dwBindingTableOffset = meBindingTable->dwMEBwdRefPicIdx[refIdx + 1];
                CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
                    m_hwInterface,
                    cmdBuffer,
                    &surfaceParams,
                    params->pKernelState));
            }
        }
    }

    return eStatus;
}

MOS_STATUS CodechalEncodeAvcEncFeiG12::GetKernelHeaderAndSize(void *binary, EncOperation operation, uint32_t krnStateIdx, void* krnHeader, uint32_t *krnSize)
{
    MOS_STATUS eStatus = MOS_STATUS_SUCCESS;

    CODECHAL_ENCODE_CHK_NULL_RETURN(binary);
    CODECHAL_ENCODE_CHK_NULL_RETURN(krnHeader);
    CODECHAL_ENCODE_CHK_NULL_RETURN(krnSize);

    auto kernelHeaderTable = (PCODECHAL_ENCODE_AVC_KERNEL_HEADER_FEI_G12)binary;
    PCODECHAL_KERNEL_HEADER invalidEntry = &(kernelHeaderTable->AVC_WeightedPrediction) + 1;
    uint32_t nextKrnOffset = *krnSize;

    PCODECHAL_KERNEL_HEADER currKrnHeader, nextKrnHeader;
    if (operation == ENC_SCALING4X)
    {
        currKrnHeader = &kernelHeaderTable->PLY_DScale_PLY;
    }
    else if (operation == ENC_ME)
    {
        currKrnHeader = &kernelHeaderTable->AVC_ME_P;
    }
    else if (operation == ENC_MBENC)
    {
        currKrnHeader = &kernelHeaderTable->AVCMBEnc_Fei_I;
    }
    else if (operation == ENC_PREPROC)
    {
        currKrnHeader = &kernelHeaderTable->AVC_Fei_ProProc;
    }
    else if (operation == ENC_WP)
    {
        currKrnHeader = &kernelHeaderTable->AVC_WeightedPrediction;
    }
    else
    {
        CODECHAL_ENCODE_ASSERTMESSAGE("Unsupported ENC mode requested");
        eStatus = MOS_STATUS_INVALID_PARAMETER;
        return eStatus;
    }

    currKrnHeader += krnStateIdx;
    *((PCODECHAL_KERNEL_HEADER)krnHeader) = *currKrnHeader;

    nextKrnHeader = (currKrnHeader + 1);
    if (nextKrnHeader < invalidEntry)
    {
        nextKrnOffset = nextKrnHeader->KernelStartPointer << MHW_KERNEL_OFFSET_SHIFT;
    }
    *krnSize = nextKrnOffset - (currKrnHeader->KernelStartPointer << MHW_KERNEL_OFFSET_SHIFT);

    return eStatus;
}

MOS_STATUS CodechalEncodeAvcEncFeiG12::GetMbEncKernelStateIdx(CodechalEncodeIdOffsetParams* params, uint32_t* kernelOffset)
{
    MOS_STATUS eStatus = MOS_STATUS_SUCCESS;

    CODECHAL_ENCODE_FUNCTION_ENTER;

    CODECHAL_ENCODE_CHK_NULL_RETURN(params);
    CODECHAL_ENCODE_CHK_NULL_RETURN(kernelOffset);

    *kernelOffset = MBENC_I_OFFSET_CM;

    if (params->wPictureCodingType == P_TYPE)
    {
        *kernelOffset += MBENC_P_OFFSET_CM;
    }
    else if (params->wPictureCodingType == B_TYPE)
    {
        *kernelOffset += MBENC_B_OFFSET_CM;
    }

    return eStatus;
}

MOS_STATUS CodechalEncodeAvcEncFeiG12::InitializeState()
{
    MOS_STATUS eStatus = MOS_STATUS_SUCCESS;

    CODECHAL_ENCODE_FUNCTION_ENTER;

    CODECHAL_ENCODE_CHK_STATUS_RETURN(CodechalEncodeAvcEnc::InitializeState());

    if (m_feiEnable)
    {
        if (m_codecFunction == CODECHAL_FUNCTION_FEI_PRE_ENC)
        {
            m_hmeSupported = true;
            m_flatnessCheckSupported = true;
        }

        m_16xMeSupported = false;
        m_32xMeSupported = false;
    }

    m_brcHistoryBufferSize = m_initBrcHistoryBufferSize;
    m_mbencBrcBufferSize   = m_initMbencBrcBufferSize;
    m_useHwScoreboard      = false;

    dwBrcConstantSurfaceWidth = m_brcConstantsurfaceWidth;
    dwBrcConstantSurfaceHeight = m_brcConstantsurfaceHeight;

    // Create SW scoreboard init kernel state
    CODECHAL_ENCODE_CHK_NULL_RETURN(m_swScoreboardState = MOS_New(CodechalEncodeSwScoreboardG12, this));
    CODECHAL_ENCODE_CHK_STATUS_RETURN(m_swScoreboardState->InitKernelState());

    if (MOS_VE_SUPPORTED(m_osInterface))
    {
        m_sinlgePipeVeState = (PCODECHAL_ENCODE_SINGLEPIPE_VIRTUALENGINE_STATE)MOS_AllocAndZeroMemory(sizeof(CODECHAL_ENCODE_SINGLEPIPE_VIRTUALENGINE_STATE));
        CODECHAL_ENCODE_CHK_NULL_RETURN(m_sinlgePipeVeState);
        CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalEncodeSinglePipeVE_InitInterface(m_hwInterface, m_sinlgePipeVeState));
    }

    return eStatus;
}

MOS_STATUS CodechalEncodeAvcEncFeiG12::SetCurbeAvcPreProc(PCODECHAL_ENCODE_AVC_PREPROC_CURBE_PARAMS params)
{
    MOS_STATUS eStatus = MOS_STATUS_SUCCESS;

    CODECHAL_ENCODE_FUNCTION_ENTER;

    CODECHAL_ENCODE_CHK_NULL_RETURN(params);
    CODECHAL_ENCODE_CHK_NULL_RETURN(params->pPreEncParams);

    auto preEncParams = params->pPreEncParams;

    uint32_t sliceQP = preEncParams->dwFrameQp;
    bool framePicture = CodecHal_PictureIsFrame(m_currOriginalPic);
    bool bottomField = CodecHal_PictureIsBottomField(m_currOriginalPic);
    CODECHAL_ENCODE_AVC_PREPROC_CURBE_CM_G12 cmd;
    switch (m_pictureCodingType)
    {
    case I_TYPE:
        if (framePicture)
        {
            CODECHAL_ENCODE_CHK_STATUS_RETURN(MOS_SecureMemcpy(
                &cmd,
                sizeof(CODECHAL_ENCODE_AVC_PREPROC_CURBE_CM_G12),
                PreProc_CURBE_CM_normal_I_frame,
                sizeof(CODECHAL_ENCODE_AVC_PREPROC_CURBE_CM_G12)));
        }
        else
        {
            CODECHAL_ENCODE_CHK_STATUS_RETURN(MOS_SecureMemcpy(
                &cmd,
                sizeof(CODECHAL_ENCODE_AVC_PREPROC_CURBE_CM_G12),
                PreProc_CURBE_CM_normal_I_field,
                sizeof(CODECHAL_ENCODE_AVC_PREPROC_CURBE_CM_G12)));
        }
        break;

    case P_TYPE:
        if (framePicture)
        {
            CODECHAL_ENCODE_CHK_STATUS_RETURN(MOS_SecureMemcpy(
                &cmd,
                sizeof(CODECHAL_ENCODE_AVC_PREPROC_CURBE_CM_G12),
                PreProc_CURBE_CM_normal_P_frame,
                sizeof(CODECHAL_ENCODE_AVC_PREPROC_CURBE_CM_G12)));
        }
        else
        {
            CODECHAL_ENCODE_CHK_STATUS_RETURN(MOS_SecureMemcpy(
                &cmd,
                sizeof(CODECHAL_ENCODE_AVC_PREPROC_CURBE_CM_G12),
                PreProc_CURBE_CM_normal_P_field,
                sizeof(CODECHAL_ENCODE_AVC_PREPROC_CURBE_CM_G12)));
        }
        break;

    case B_TYPE:
        if (framePicture)
        {
            CODECHAL_ENCODE_CHK_STATUS_RETURN(MOS_SecureMemcpy(
                &cmd,
                sizeof(CODECHAL_ENCODE_AVC_PREPROC_CURBE_CM_G12),
                PreProc_CURBE_CM_normal_B_frame,
                sizeof(CODECHAL_ENCODE_AVC_PREPROC_CURBE_CM_G12)));
        }
        else
        {
            CODECHAL_ENCODE_CHK_STATUS_RETURN(MOS_SecureMemcpy(
                &cmd,
                sizeof(CODECHAL_ENCODE_AVC_PREPROC_CURBE_CM_G12),
                PreProc_CURBE_CM_normal_B_field,
                sizeof(CODECHAL_ENCODE_AVC_PREPROC_CURBE_CM_G12)));
        }
        break;

    default:
        CODECHAL_ENCODE_ASSERTMESSAGE("Invalid picture coding type.");
        eStatus = MOS_STATUS_UNKNOWN;
        return eStatus;
    }

    uint8_t  meMethod = (preEncParams->dwSearchWindow == 5) || (preEncParams->dwSearchWindow == 8) ? 4 : 6; // 4 means full search, 6 means diamand search
    uint32_t refWidth = preEncParams->dwRefWidth;
    uint32_t refHeight = preEncParams->dwRefHeight;
    uint32_t lenSP = preEncParams->dwLenSP;
    switch (preEncParams->dwSearchWindow)
    {
    case 0:
        // not use predefined search window and search patch
        if ((preEncParams->dwSearchPath != 0) && (preEncParams->dwSearchPath != 1) && (preEncParams->dwSearchPath != 2))
        {
            CODECHAL_ENCODE_ASSERTMESSAGE("Invalid picture FEI PREENC input SearchPath for SearchWindow=0 case!!!.");
            eStatus = MOS_STATUS_INVALID_PARAMETER;
            return eStatus;
        }
        meMethod = (preEncParams->dwSearchPath == 1) ? 6 : 4; // 4 means full search, 6 means diamand search
        if (((refWidth * refHeight) > 2048) || (refWidth > 64) || (refHeight > 64))
        {
            CODECHAL_ENCODE_ASSERTMESSAGE("Invalid picture FEI PREENC PreProc input refWidth/refHeight size for SearchWindow=0 case!!!.");
            eStatus = MOS_STATUS_INVALID_PARAMETER;
            return eStatus;
        }
        break;
    case 1:
        // Tiny 4 SUs 24x24 window
        refWidth = 24;
        refHeight = 24;
        lenSP = 4;
        break;
    case 2:
        // Small 9 SUs 28x28 window
        refWidth = 28;
        refHeight = 28;
        lenSP = 9;
        break;
    case 3:
        // Diamond 16 SUs 48x40 window
        refWidth = 48;
        refHeight = 40;
        lenSP = 16;
        break;
    case 4:
        // Large Diamond 32 SUs 48x40 window
        refWidth = 48;
        refHeight = 40;
        lenSP = 32;
        break;
    case 5:
        // Exhaustive 48 SUs 48x40 window
        refWidth = 48;
        refHeight = 40;
        lenSP = 48;
        break;
    case 6:
        // Diamond 16 SUs 64x32 window
        refWidth = 64;
        refHeight = 32;
        lenSP = 16;
        break;
    case 7:
        // Large Diamond 32 SUs 64x32 window
        refWidth = 64;
        refHeight = 32;
        lenSP = 32;
    case 8:
        // Exhaustive 48 SUs 64x32 window
        refWidth = 64;
        refHeight = 32;
        lenSP = 48;
        break;
    default:
        CODECHAL_ENCODE_ASSERTMESSAGE("Invalid picture FEI PREENC PreProc SearchWindow value!!!.");
        eStatus = MOS_STATUS_INVALID_PARAMETER;
        return eStatus;
    }

    // r1
    cmd.DW0.AdaptiveEn =
        cmd.DW37.AdaptiveEn = preEncParams->bAdaptiveSearch;
    cmd.DW2.LenSP = lenSP;
    cmd.DW38.LenSP = 0; // MBZ
    cmd.DW2.MaxNumSU = cmd.DW38.MaxNumSU = 57;

    cmd.DW3.SrcAccess =
        cmd.DW3.RefAccess = framePicture ? 0 : 1;

    if (m_pictureCodingType != I_TYPE && bFTQEnable)
    {
        cmd.DW3.FTEnable = preEncParams->bFTEnable;
    }
    else
    {
        cmd.DW3.FTEnable = 0;
    }
    cmd.DW3.SubMbPartMask = preEncParams->dwSubMBPartMask;
    cmd.DW3.SubPelMode = preEncParams->dwSubPelMode;
    cmd.DW3.IntraSAD = preEncParams->dwIntraSAD;
    cmd.DW3.InterSAD = preEncParams->dwInterSAD;

    cmd.DW2.PicWidth = params->wPicWidthInMb;
    cmd.DW6.PicHeight = cmd.DW5.SliceMbHeight = params->wFieldFrameHeightInMb;

    cmd.DW4.FieldParityFlag = cmd.DW4.CurrPicFieldParityFlag =
        cmd.DW7.SrcFieldPolarity = bottomField ? 1 : 0;
    cmd.DW4.HMEEnable = m_hmeEnabled;
    cmd.DW4.FrameQp = sliceQP;
    cmd.DW4.PerMBQpEnable = preEncParams->bMBQp;
    cmd.DW4.MultipleMVPredictorPerMBEnable = (m_pictureCodingType == I_TYPE) ? 0 : preEncParams->dwMVPredictorCtrl;
    cmd.DW4.DisableMvOutput = (m_pictureCodingType == I_TYPE) ? 1 : preEncParams->bDisableMVOutput;
    cmd.DW4.DisableMbStats = preEncParams->bDisableStatisticsOutput;
    cmd.DW4.FwdRefPicEnable = preEncParams->dwNumPastReferences > 0 ? 1 : 0;
    cmd.DW4.FwdRefPicFrameFieldFlag = CodecHal_PictureIsFrame(preEncParams->PastRefPicture) ? 0 : 1;
    cmd.DW4.FwdRefPicFieldParityFlag = CodecHal_PictureIsBottomField(preEncParams->PastRefPicture);
    cmd.DW4.BwdRefPicEnable = preEncParams->dwNumFutureReferences > 0 ? 1 : 0;
    cmd.DW4.BwdRefPicFrameFieldFlag = CodecHal_PictureIsFrame(preEncParams->FutureRefPicture) ? 0 : 1;
    cmd.DW4.BwdRefPicFieldParityFlag = CodecHal_PictureIsBottomField(preEncParams->FutureRefPicture);
    cmd.DW7.IntraPartMask = preEncParams->dwIntraPartMask;

    uint8_t tableIdx = m_pictureCodingType - 1;
    eStatus = MOS_SecureMemcpy(&(cmd.ModeMvCost), 8 * sizeof(uint32_t), ModeMvCost_Cm_PreProc[tableIdx][sliceQP], 8 * sizeof(uint32_t));
    if (eStatus != MOS_STATUS_SUCCESS)
    {
        CODECHAL_ENCODE_ASSERTMESSAGE("Failed to copy memory.");
        return eStatus;
    }
    cmd.ModeMvCost.DW8.Value = 0;
    cmd.ModeMvCost.DW9.Value = 0;
    cmd.ModeMvCost.DW10.Value = 0;
    cmd.ModeMvCost.DW11.Value = 0;
    cmd.ModeMvCost.DW12.Value = 0;
    cmd.ModeMvCost.DW13.Value = 0;

    if (!framePicture && m_pictureCodingType != I_TYPE)
    {
        /* for field, R2.2 upper word should be set to zero for P and B frames */
        cmd.ModeMvCost.DW10.Value &= 0x0000FFFF;
    }

    tableIdx = (m_pictureCodingType == B_TYPE) ? 1 : 0;
    eStatus = MOS_SecureMemcpy(&(cmd.SPDelta), 16 * sizeof(uint32_t), CodechalEncoderState::m_encodeSearchPath[tableIdx][meMethod], 16 * sizeof(uint32_t));
    if (eStatus != MOS_STATUS_SUCCESS)
    {
        CODECHAL_ENCODE_ASSERTMESSAGE("Failed to copy memory.");
        return eStatus;
    }
    // disable Intra Compute when disabling all mode in dwIntraPartMask
    if (preEncParams->dwIntraPartMask == 0x7)
    {
        cmd.SPDelta.DW31.IntraComputeType = 3;
    }

    cmd.DW38.RefThreshold = m_refThresholdFei;
    cmd.DW39.HMERefWindowsCombThreshold = (m_pictureCodingType == B_TYPE) ?
        HMEBCombineLen_fei[m_targetUsage] : HMECombineLen_fei[m_targetUsage];

    // Picture Coding Type dependent parameters
    if (m_pictureCodingType == I_TYPE)
    {
        cmd.DW0.SkipModeEn = 0;
        cmd.DW37.SkipModeEn = 0;
        cmd.DW36.HMECombineOverlap = 0;
    }
    else if (m_pictureCodingType == P_TYPE)
    {
        cmd.DW1.MaxNumMVs = GetMaxMvsPer2Mb(CODEC_AVC_LEVEL_52) / 2;
        cmd.DW3.BMEDisableFBR = 1;
        cmd.DW3.SearchCtrl = 0;
        cmd.DW5.RefWidth = cmd.DW39.RefWidth = refWidth;
        cmd.DW5.RefHeight = cmd.DW39.RefHeight = refHeight;
        cmd.DW7.NonSkipZMvAdded = 1;
        cmd.DW7.NonSkipModeAdded = 1;
        cmd.DW7.SkipCenterMask = 1;
        cmd.DW32.MaxVmvR = (framePicture) ? CodecHalAvcEncode_GetMaxMvLen(CODEC_AVC_LEVEL_52) * 4 : (CodecHalAvcEncode_GetMaxMvLen(CODEC_AVC_LEVEL_52) >> 1) * 4;
        cmd.DW36.HMECombineOverlap = 1;
    }
    else
    {
        // B_TYPE
        cmd.DW1.MaxNumMVs = GetMaxMvsPer2Mb(CODEC_AVC_LEVEL_52) / 2;
        cmd.DW3.SearchCtrl = 0;
        cmd.DW3.SkipType = 1;
        cmd.DW5.RefWidth = cmd.DW39.RefWidth = refWidth;
        cmd.DW5.RefHeight = cmd.DW39.RefHeight = refHeight;
        cmd.DW7.SkipCenterMask = 0xFF;
        cmd.DW32.MaxVmvR = (framePicture) ? CodecHalAvcEncode_GetMaxMvLen(CODEC_AVC_LEVEL_52) * 4 : (CodecHalAvcEncode_GetMaxMvLen(CODEC_AVC_LEVEL_52) >> 1) * 4;
        cmd.DW36.HMECombineOverlap = 1;
    }

    cmd.DW40.CurrPicSurfIndex = CODECHAL_ENCODE_AVC_PREPROC_CURR_Y_CM_G12;
    cmd.DW41.HMEMvDataSurfIndex = CODECHAL_ENCODE_AVC_PREPROC_HME_MV_DATA_CM_G12;
    cmd.DW42.MvPredictorSurfIndex = CODECHAL_ENCODE_AVC_PREPROC_MV_PREDICTOR_CM_G12;
    cmd.DW43.MbQpSurfIndex = CODECHAL_ENCODE_AVC_PREPROC_MBQP_CM_G12;
    cmd.DW44.MvDataOutSurfIndex = CODECHAL_ENCODE_AVC_PREPROC_MV_DATA_CM_G12;
    cmd.DW45.MbStatsOutSurfIndex = CODECHAL_ENCODE_AVC_PREPROC_MB_STATS_CM_G12;
    if (framePicture)
    {
        cmd.DW46.VMEInterPredictionSurfIndex = CODECHAL_ENCODE_AVC_PREPROC_VME_CURR_PIC_IDX_0_CM_G12;
        cmd.DW47.VMEInterPredictionMRSurfIndex = CODECHAL_ENCODE_AVC_PREPROC_VME_CURR_PIC_IDX_1_CM_G12;
        cmd.DW48.FtqLutSurfIndex = CODECHAL_ENCODE_AVC_PREPROC_FTQ_LUT_CM_G12;
    }
    else
    {
        cmd.DW46.VMEInterPredictionSurfIndex = CODECHAL_ENCODE_AVC_PREPROC_VME_FIELD_CURR_PIC_IDX_0_CM_G12;
        cmd.DW47.VMEInterPredictionMRSurfIndex = CODECHAL_ENCODE_AVC_PREPROC_VME_FIELD_CURR_PIC_IDX_1_CM_G12;
        cmd.DW48.FtqLutSurfIndex = CODECHAL_ENCODE_AVC_PREPROC_FIELD_FTQ_LUT_CM_G12;
    }

    CODECHAL_ENCODE_CHK_STATUS_RETURN(params->pKernelState->m_dshRegion.AddData(
        &cmd,
        params->pKernelState->dwCurbeOffset,
        sizeof(cmd)));

    return eStatus;
}

MOS_STATUS CodechalEncodeAvcEncFeiG12::SendAvcPreProcSurfaces(PMOS_COMMAND_BUFFER cmdBuffer, PCODECHAL_ENCODE_AVC_PREPROC_SURFACE_PARAMS params)
{
    MOS_STATUS eStatus = MOS_STATUS_SUCCESS;

    CODECHAL_ENCODE_FUNCTION_ENTER;
    CODECHAL_ENCODE_CHK_NULL_RETURN(m_hwInterface);
    CODECHAL_ENCODE_CHK_NULL_RETURN(m_hwInterface->GetOsInterface());
    CODECHAL_ENCODE_CHK_NULL_RETURN(cmdBuffer);
    CODECHAL_ENCODE_CHK_NULL_RETURN(params);
    CODECHAL_ENCODE_CHK_NULL_RETURN(params->pCurrOriginalPic);
    CODECHAL_ENCODE_CHK_NULL_RETURN(params->psCurrPicSurface);

    CODECHAL_ENCODE_CHK_NULL_RETURN(params->pPreProcBindingTable);
    CODECHAL_ENCODE_CHK_NULL_RETURN(params->pKernelState);
    CODECHAL_ENCODE_CHK_NULL_RETURN(params->pPreEncParams);

    auto kernelState = params->pKernelState;

    auto preEncParams = (FeiPreEncParams*)params->pPreEncParams;
    auto avcPreProcBindingTable = params->pPreProcBindingTable;

    bool currFieldPicture = CodecHal_PictureIsField(*(params->pCurrOriginalPic)) ? 1 : 0;
    bool currBottomField = CodecHal_PictureIsBottomField(*(params->pCurrOriginalPic)) ? 1 : 0;

    uint8_t vDirection = (CodecHal_PictureIsFrame(*(params->pCurrOriginalPic))) ? CODECHAL_VDIRECTION_FRAME :
        (currBottomField) ? CODECHAL_VDIRECTION_BOT_FIELD : CODECHAL_VDIRECTION_TOP_FIELD;

    CODECHAL_SURFACE_CODEC_PARAMS surfaceCodecParams;
    MOS_ZeroMemory(&surfaceCodecParams, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
    surfaceCodecParams.bIs2DSurface = true;
    surfaceCodecParams.bMediaBlockRW = true; // Use media block RW for DP 2D surface access
    surfaceCodecParams.bUseUVPlane = true;
    surfaceCodecParams.psSurface = params->psCurrPicSurface;
    surfaceCodecParams.dwOffset = 0;
    surfaceCodecParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_CURR_ENCODE].Value;
    surfaceCodecParams.dwBindingTableOffset = avcPreProcBindingTable->dwAvcPreProcCurrY;
    surfaceCodecParams.dwUVBindingTableOffset = avcPreProcBindingTable->dwAvcPreProcCurrUV;
    surfaceCodecParams.dwVerticalLineStride = params->dwVerticalLineStride;
    surfaceCodecParams.dwVerticalLineStrideOffset = params->dwVerticalLineStrideOffset;

    CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
        m_hwInterface,
        cmdBuffer,
        &surfaceCodecParams,
        kernelState));

    // AVC_ME MV data buffer
    if (params->bHmeEnabled)
    {
        CODECHAL_ENCODE_CHK_NULL_RETURN(params->ps4xMeMvDataBuffer);

        MOS_ZeroMemory(&surfaceCodecParams, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
        surfaceCodecParams.bIs2DSurface = true;
        surfaceCodecParams.bMediaBlockRW = true;
        surfaceCodecParams.psSurface = params->ps4xMeMvDataBuffer;
        surfaceCodecParams.dwOffset = params->dwMeMvBottomFieldOffset;
        surfaceCodecParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_MV_DATA_ENCODE].Value;
        surfaceCodecParams.dwBindingTableOffset = avcPreProcBindingTable->dwAvcPreProcMVDataFromHME;
        CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
            m_hwInterface,
            cmdBuffer,
            &surfaceCodecParams,
            kernelState));
    }

    if (preEncParams->dwMVPredictorCtrl)
    {
        MOS_ZeroMemory(&surfaceCodecParams, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));

        uint32_t size = params->dwFrameWidthInMb * params->dwFrameFieldHeightInMb * 8;
        surfaceCodecParams.dwSize = size;
        surfaceCodecParams.presBuffer = &(preEncParams->resMvPredBuffer);
        surfaceCodecParams.dwOffset = 0;
        surfaceCodecParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_MV_DATA_ENCODE].Value;
        surfaceCodecParams.dwBindingTableOffset = avcPreProcBindingTable->dwAvcPreProcMvPredictor;
        CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
            m_hwInterface,
            cmdBuffer,
            &surfaceCodecParams,
            kernelState));
    }

    if (preEncParams->bMBQp)
    {
        MOS_ZeroMemory(&surfaceCodecParams, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));

        uint32_t size = params->dwFrameWidthInMb * params->dwFrameFieldHeightInMb;
        surfaceCodecParams.dwSize = size;
        surfaceCodecParams.presBuffer = &(preEncParams->resMbQpBuffer);
        surfaceCodecParams.dwOffset = 0;
        surfaceCodecParams.dwBindingTableOffset = avcPreProcBindingTable->dwAvcPreProcMbQp;
        CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
            m_hwInterface,
            cmdBuffer,
            &surfaceCodecParams,
            kernelState));

        // 16 DWs per QP value
        size = 16 * 52 * sizeof(uint32_t);

        MOS_ZeroMemory(&surfaceCodecParams, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
        surfaceCodecParams.presBuffer = params->presFtqLutBuffer;
        surfaceCodecParams.dwSize = size;
        surfaceCodecParams.dwBindingTableOffset = currFieldPicture ? avcPreProcBindingTable->dwAvcPreProcFtqLutField : avcPreProcBindingTable->dwAvcPreProcFtqLut;
        CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
            m_hwInterface,
            cmdBuffer,
            &surfaceCodecParams,
            kernelState));

    }

    if (!preEncParams->bDisableMVOutput)
    {
        MOS_ZeroMemory(&surfaceCodecParams, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));

        uint32_t size = params->dwFrameWidthInMb * params->dwFrameFieldHeightInMb * 32 * 4;
        surfaceCodecParams.presBuffer = &(preEncParams->resMvBuffer);
        surfaceCodecParams.dwSize = size;
        surfaceCodecParams.dwOffset = 0;
        surfaceCodecParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_MV_DATA_ENCODE].Value;
        surfaceCodecParams.dwBindingTableOffset = avcPreProcBindingTable->dwAvcPreProcMvDataOut;
        surfaceCodecParams.bRenderTarget = true;
        surfaceCodecParams.bIsWritable = true;
        CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
            m_hwInterface,
            cmdBuffer,
            &surfaceCodecParams,
            kernelState));
    }

    if (!preEncParams->bDisableStatisticsOutput)
    {
        MOS_ZeroMemory(&surfaceCodecParams, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));

        uint32_t size = params->dwFrameWidthInMb * params->dwFrameFieldHeightInMb * 64;
        if (currBottomField)
        {
            surfaceCodecParams.presBuffer = &(preEncParams->resStatsBotFieldBuffer);
        }
        else
        {
            surfaceCodecParams.presBuffer = &(preEncParams->resStatsBuffer);
        }
        surfaceCodecParams.dwSize = size;
        surfaceCodecParams.dwOffset = params->dwMBVProcStatsBottomFieldOffset;
        surfaceCodecParams.bRenderTarget = true;
        surfaceCodecParams.bIsWritable = true;
        surfaceCodecParams.dwBindingTableOffset = avcPreProcBindingTable->dwAvcPreProcMbStatsOut;
        CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
            m_hwInterface,
            cmdBuffer,
            &surfaceCodecParams,
            kernelState));
    }

    // Current Picture Y - VME
    MOS_ZeroMemory(&surfaceCodecParams, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
    surfaceCodecParams.bUseAdvState = true;
    surfaceCodecParams.psSurface = params->psCurrPicSurface;
    surfaceCodecParams.dwOffset = 0;
    surfaceCodecParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_CURR_ENCODE].Value;
    surfaceCodecParams.dwBindingTableOffset = currFieldPicture ? avcPreProcBindingTable->dwAvcPreProcVMECurrPicField[0] : avcPreProcBindingTable->dwAvcPreProcVMECurrPicFrame[0];
    surfaceCodecParams.ucVDirection = vDirection;

    CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
        m_hwInterface,
        cmdBuffer,
        &surfaceCodecParams,
        kernelState));
    surfaceCodecParams.dwBindingTableOffset = currFieldPicture ? avcPreProcBindingTable->dwAvcPreProcVMECurrPicField[1] : avcPreProcBindingTable->dwAvcPreProcVMECurrPicFrame[1];
    surfaceCodecParams.ucVDirection = vDirection;
    CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
        m_hwInterface,
        cmdBuffer,
        &surfaceCodecParams,
        kernelState));

    uint32_t refBindingTableOffset;
    if (preEncParams->dwNumPastReferences > 0)
    {
        auto refPic = preEncParams->PastRefPicture;
        uint8_t refPicIdx = refPic.FrameIdx;
        bool refBottomField = (CodecHal_PictureIsBottomField(refPic)) ? 1 : 0;
        uint8_t refVDirection;
        // Program the surface based on current picture's field/frame mode
        if (currFieldPicture) // if current picture is field
        {
            if (refBottomField)
            {
                refVDirection = CODECHAL_VDIRECTION_BOT_FIELD;
            }
            else
            {
                refVDirection = CODECHAL_VDIRECTION_TOP_FIELD;
            }
            refBindingTableOffset = avcPreProcBindingTable->dwAvcPreProcVMEFwdPicField[0];
        }
        else // if current picture is frame
        {
            refVDirection = CODECHAL_VDIRECTION_FRAME;
            refBindingTableOffset = avcPreProcBindingTable->dwAvcPreProcVMEFwdPicFrame;
        }

        // Picture Y VME
        MOS_ZeroMemory(&surfaceCodecParams, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
        surfaceCodecParams.bUseAdvState = true;
        surfaceCodecParams.psSurface = &params->ppRefList[refPicIdx]->sRefBuffer;
        surfaceCodecParams.dwBindingTableOffset = refBindingTableOffset;
        surfaceCodecParams.ucVDirection = refVDirection;
        surfaceCodecParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_REF_ENCODE].Value;

        CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
            m_hwInterface,
            cmdBuffer,
            &surfaceCodecParams,
            kernelState));

        if (currFieldPicture) // if current picture is field
        {
            surfaceCodecParams.dwBindingTableOffset = avcPreProcBindingTable->dwAvcPreProcVMEFwdPicField[1];

            CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
                m_hwInterface,
                cmdBuffer,
                &surfaceCodecParams,
                kernelState));
        }
    }

    if (preEncParams->dwNumFutureReferences > 0)
    {
        auto refPic = preEncParams->FutureRefPicture;
        uint8_t refPicIdx = refPic.FrameIdx;
        bool refBottomField = (CodecHal_PictureIsBottomField(refPic)) ? 1 : 0;
        uint8_t refVDirection;

        // Program the surface based on current picture's field/frame mode
        if (currFieldPicture) // if current picture is field
        {
            if (refBottomField)
            {
                refVDirection = CODECHAL_VDIRECTION_BOT_FIELD;
            }
            else
            {
                refVDirection = CODECHAL_VDIRECTION_TOP_FIELD;
            }
            refBindingTableOffset = avcPreProcBindingTable->dwAvcPreProcVMEBwdPicField[0];
        }
        else // if current picture is frame
        {
            refVDirection = CODECHAL_VDIRECTION_FRAME;
            refBindingTableOffset = avcPreProcBindingTable->dwAvcPreProcVMEBwdPicFrame[0];
        }

        // Picture Y VME
        MOS_ZeroMemory(&surfaceCodecParams, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
        surfaceCodecParams.bUseAdvState = true;
        surfaceCodecParams.psSurface = &params->ppRefList[refPicIdx]->sRefBuffer;
        surfaceCodecParams.dwBindingTableOffset = refBindingTableOffset;
        surfaceCodecParams.ucVDirection = refVDirection;
        surfaceCodecParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_REF_ENCODE].Value;

        CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
            m_hwInterface,
            cmdBuffer,
            &surfaceCodecParams,
            kernelState));

        if (currFieldPicture) // if current picture is field
        {
            refBindingTableOffset = avcPreProcBindingTable->dwAvcPreProcVMEBwdPicField[1];
        }
        else
        {
            refBindingTableOffset = avcPreProcBindingTable->dwAvcPreProcVMEBwdPicFrame[1];
        }
        surfaceCodecParams.dwBindingTableOffset = refBindingTableOffset;

        CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
            m_hwInterface,
            cmdBuffer,
            &surfaceCodecParams,
            kernelState));
    }

    return eStatus;
}

MOS_STATUS CodechalEncodeAvcEncFeiG12::SetCurbeAvcMbEnc(PCODECHAL_ENCODE_AVC_MBENC_CURBE_PARAMS params)
{
    MOS_STATUS eStatus = MOS_STATUS_SUCCESS;

    CODECHAL_ENCODE_FUNCTION_ENTER;

    CODECHAL_ENCODE_CHK_NULL_RETURN(params);
    CODECHAL_ENCODE_CHK_NULL_RETURN(params->pPicParams);
    CODECHAL_ENCODE_CHK_NULL_RETURN(params->pSeqParams);
    CODECHAL_ENCODE_CHK_NULL_RETURN(params->pSlcParams);
    CODECHAL_ENCODE_CHK_NULL_RETURN(params->pdwBlockBasedSkipEn);

    auto picParams = params->pPicParams;
    auto seqParams = params->pSeqParams;
    auto slcParams = params->pSlcParams;
    auto feiPicParams = (CodecEncodeAvcFeiPicParams *)(m_avcFeiPicParams);

    // set sliceQP to MAX_SLICE_QP for  MbEnc kernel, we can use it to verify whether QP is changed or not
    uint8_t sliceQP = (params->bUseMbEncAdvKernel && params->bBrcEnabled) ? CODECHAL_ENCODE_AVC_MAX_SLICE_QP : picParams->pic_init_qp_minus26 + 26 + slcParams->slice_qp_delta;
    bool framePicture = CodecHal_PictureIsFrame(picParams->CurrOriginalPic);
    bool topField = CodecHal_PictureIsTopField(picParams->CurrOriginalPic);
    bool bottomField = CodecHal_PictureIsBottomField(picParams->CurrOriginalPic);

    CODECHAL_ENCODE_AVC_FEI_MBENC_STATIC_DATA_G12 cmd;
    if (params->bMbEncIFrameDistEnabled)
    {
        CODECHAL_ENCODE_CHK_STATUS_RETURN(MOS_SecureMemcpy(
            &cmd,
            sizeof(CODECHAL_ENCODE_AVC_FEI_MBENC_STATIC_DATA_G12),
            FEI_MBEnc_CURBE_I_frame_DIST,
            sizeof(CODECHAL_ENCODE_AVC_FEI_MBENC_STATIC_DATA_G12)));
    }
    else
    {
        switch (m_pictureCodingType)
        {
        case I_TYPE:
            if (framePicture)
            {
                CODECHAL_ENCODE_CHK_STATUS_RETURN(MOS_SecureMemcpy(
                    &cmd,
                    sizeof(CODECHAL_ENCODE_AVC_FEI_MBENC_STATIC_DATA_G12),
                    FEI_MBEnc_CURBE_normal_I_frame,
                    sizeof(CODECHAL_ENCODE_AVC_FEI_MBENC_STATIC_DATA_G12)));
            }
            else
            {
                CODECHAL_ENCODE_CHK_STATUS_RETURN(MOS_SecureMemcpy(
                    &cmd,
                    sizeof(CODECHAL_ENCODE_AVC_FEI_MBENC_STATIC_DATA_G12),
                    FEI_MBEnc_CURBE_normal_I_field,
                    sizeof(CODECHAL_ENCODE_AVC_FEI_MBENC_STATIC_DATA_G12)));
            }
            break;

        case P_TYPE:
            if (framePicture)
            {
                CODECHAL_ENCODE_CHK_STATUS_RETURN(MOS_SecureMemcpy(
                    &cmd,
                    sizeof(CODECHAL_ENCODE_AVC_FEI_MBENC_STATIC_DATA_G12),
                    FEI_MBEnc_CURBE_normal_P_frame,
                    sizeof(CODECHAL_ENCODE_AVC_FEI_MBENC_STATIC_DATA_G12)));
            }
            else
            {
                CODECHAL_ENCODE_CHK_STATUS_RETURN(MOS_SecureMemcpy(
                    &cmd,
                    sizeof(CODECHAL_ENCODE_AVC_FEI_MBENC_STATIC_DATA_G12),
                    FEI_MBEnc_CURBE_normal_P_field,
                    sizeof(CODECHAL_ENCODE_AVC_FEI_MBENC_STATIC_DATA_G12)));
            }
            break;

        case B_TYPE:
            if (framePicture)
            {
                CODECHAL_ENCODE_CHK_STATUS_RETURN(MOS_SecureMemcpy(
                    &cmd,
                    sizeof(CODECHAL_ENCODE_AVC_FEI_MBENC_STATIC_DATA_G12),
                    FEI_MBEnc_CURBE_normal_B_frame,
                    sizeof(CODECHAL_ENCODE_AVC_FEI_MBENC_STATIC_DATA_G12)));
            }
            else
            {
                CODECHAL_ENCODE_CHK_STATUS_RETURN(MOS_SecureMemcpy(
                    &cmd,
                    sizeof(CODECHAL_ENCODE_AVC_FEI_MBENC_STATIC_DATA_G12),
                    FEI_MBEnc_CURBE_normal_B_field,
                    sizeof(CODECHAL_ENCODE_AVC_FEI_MBENC_STATIC_DATA_G12)));
            }
            break;

        default:
            CODECHAL_ENCODE_ASSERTMESSAGE("Invalid picture coding type.");
            eStatus = MOS_STATUS_UNKNOWN;
            return eStatus;
        }
    }

    uint8_t meMethod = (feiPicParams->SearchWindow == 5) || (feiPicParams->SearchWindow == 8) ? 4 : 6; // 4 means full search, 6 means diamand search
    uint32_t refWidth = feiPicParams->RefWidth;
    uint32_t refHeight = feiPicParams->RefHeight;
    uint32_t lenSP = feiPicParams->LenSP;
    switch (feiPicParams->SearchWindow)
    {
    case 0:
        // not use predefined search window
        if ((feiPicParams->SearchPath != 0) && (feiPicParams->SearchPath != 1) && (feiPicParams->SearchPath != 2))
        {
            CODECHAL_ENCODE_ASSERTMESSAGE("Invalid picture FEI MB ENC input SearchPath for SearchWindow=0 case!!!.");
            eStatus = MOS_STATUS_INVALID_PARAMETER;
            return eStatus;
        }
        meMethod = (feiPicParams->SearchPath == 1) ? 6 : 4; // 4 means full search, 6 means diamand search
        if (((refWidth * refHeight) > 2048) || (refWidth > 64) || (refHeight > 64))
        {
            CODECHAL_ENCODE_ASSERTMESSAGE("Invalid picture FEI MB ENC input refWidth/refHeight size for SearchWindow=0 case!!!.");
            eStatus = MOS_STATUS_INVALID_PARAMETER;
            return eStatus;
        }
        break;
    case 1:
        // Tiny - 4 SUs 24x24 window
        refWidth = 24;
        refHeight = 24;
        lenSP = 4;
        break;
    case 2:
        // Small - 9 SUs 28x28 window
        refWidth = 28;
        refHeight = 28;
        lenSP = 9;
        break;
    case 3:
        // Diamond - 16 SUs 48x40 window
        refWidth = 48;
        refHeight = 40;
        lenSP = 16;
        break;
    case 4:
        // Large Diamond - 32 SUs 48x40 window
        refWidth = 48;
        refHeight = 40;
        lenSP = 32;
        break;
    case 5:
        // Exhaustive - 48 SUs 48x40 window
        refWidth = 48;
        refHeight = 40;
        lenSP = 48;
        break;
    case 6:
        // Diamond - 16 SUs 64x32 window
        refWidth = 64;
        refHeight = 32;
        lenSP = 16;
        break;
    case 7:
        // Large Diamond - 32 SUs 64x32 window
        refWidth = 64;
        refHeight = 32;
        lenSP = 32;
    case 8:
        // Exhaustive - 48 SUs 64x32 window
        refWidth = 64;
        refHeight = 32;
        lenSP = 48;
        break;
    default:
        CODECHAL_ENCODE_ASSERTMESSAGE("Invalid picture FEI MB ENC SearchWindow value!!!.");
        eStatus = MOS_STATUS_INVALID_PARAMETER;
        return eStatus;
    }

    if ((m_pictureCodingType == B_TYPE) && (cmd.DW3.BMEDisableFBR == 0))
    {
        if (refWidth > 32)
        {
            refWidth = 32;
        }
        if (refHeight > 32)
        {
            refHeight = 32;
        }
    }

    // r1
    cmd.DW0.AdaptiveEn =
        cmd.DW37.AdaptiveEn = feiPicParams->AdaptiveSearch;
    cmd.DW0.T8x8FlagForInterEn =
        cmd.DW37.T8x8FlagForInterEn = picParams->transform_8x8_mode_flag;
    cmd.DW2.LenSP = lenSP;
    cmd.DW2.MaxNumSU = cmd.DW38.MaxNumSU = 57;
    cmd.DW38.LenSP = 0; // MBZ
    cmd.DW3.SrcAccess =
        cmd.DW3.RefAccess = framePicture ? 0 : 1;

    if (m_pictureCodingType != I_TYPE && bFTQEnable)
    {
            if (m_pictureCodingType == P_TYPE)
            {
                cmd.DW3.FTEnable = FTQBasedSkip[seqParams->TargetUsage] & 0x01;
            }
            else // B_TYPE
            {
                cmd.DW3.FTEnable = (FTQBasedSkip[seqParams->TargetUsage] >> 1) & 0x01;
            }
    }
    else
    {
        cmd.DW3.FTEnable = 0;
    }

    if (picParams->UserFlags.bDisableSubMBPartition)
    {
        cmd.DW3.SubMbPartMask = CODECHAL_ENCODE_AVC_DISABLE_4X4_SUB_MB_PARTITION | CODECHAL_ENCODE_AVC_DISABLE_4X8_SUB_MB_PARTITION | CODECHAL_ENCODE_AVC_DISABLE_8X4_SUB_MB_PARTITION;
    }

    cmd.DW2.PicWidth = params->wPicWidthInMb;
    cmd.DW3.SubMbPartMask = feiPicParams->SubMBPartMask;
    cmd.DW3.SubPelMode = feiPicParams->SubPelMode;
    cmd.DW3.InterSAD = feiPicParams->InterSAD;
    cmd.DW3.IntraSAD = feiPicParams->IntraSAD;
    cmd.DW3.SearchCtrl = (m_pictureCodingType == B_TYPE) ? 7 : 0;
    cmd.DW4.PicHeightMinus1 = params->wFieldFrameHeightInMb - 1;
    cmd.DW4.FieldParityFlag = cmd.DW7.SrcFieldPolarity = bottomField ? 1 : 0;
    cmd.DW4.EnableFBRBypass = bFBRBypassEnable;
    cmd.DW4.EnableIntraCostScalingForStaticFrame = params->bStaticFrameDetectionEnabled;
    cmd.DW4.TrueDistortionEnable = feiPicParams->DistortionType == 0 ? 1 : 0;
    cmd.DW4.bCurFldIDR = !framePicture && (picParams->bIdrPic || m_firstFieldIdrPic);
    cmd.DW4.ConstrainedIntraPredFlag = picParams->constrained_intra_pred_flag;
    cmd.DW4.HMEEnable = 0;
    cmd.DW4.PictureType = m_pictureCodingType - 1;
    cmd.DW4.UseActualRefQPValue = false;
    cmd.DW5.SliceMbHeight = params->usSliceHeight;
    cmd.DW7.IntraPartMask = feiPicParams->IntraPartMask;

    // r2
    if (params->bMbEncIFrameDistEnabled)
    {
        cmd.DW6.BatchBufferEnd = 0;
    }
    else
    {
        uint8_t tableIdx = m_pictureCodingType - 1;
        eStatus = MOS_SecureMemcpy(&(cmd.ModeMvCost), 8 * sizeof(uint32_t), ModeMvCost_Cm[tableIdx][sliceQP], 8 * sizeof(uint32_t));
        if (eStatus != MOS_STATUS_SUCCESS)
        {
            CODECHAL_ENCODE_ASSERTMESSAGE("Failed to copy memory.");
            return eStatus;
        }

        if (m_pictureCodingType == I_TYPE && bOldModeCostEnable)
        {
            // Old intra mode cost needs to be used if bOldModeCostEnable is 1
            cmd.ModeMvCost.DW8.Value = OldIntraModeCost_Cm_Common[sliceQP];
        }
        else if (m_skipBiasAdjustmentEnable)
        {
            // Load different MvCost for P picture when SkipBiasAdjustment is enabled
            // No need to check for P picture as the flag is only enabled for P picture
            cmd.ModeMvCost.DW11.Value = MvCost_PSkipAdjustment_Cm_Common[sliceQP];
        }
    }

    // r3 & r4
    if (params->bMbEncIFrameDistEnabled)
    {
        cmd.SPDelta.DW31.IntraComputeType = 1;
    }
    else
    {
        uint8_t tableIdx = (m_pictureCodingType == B_TYPE) ? 1 : 0;
        eStatus = MOS_SecureMemcpy(&(cmd.SPDelta), 16 * sizeof(uint32_t), CodechalEncoderState::m_encodeSearchPath[tableIdx][meMethod], 16 * sizeof(uint32_t));
        if (eStatus != MOS_STATUS_SUCCESS)
        {
            CODECHAL_ENCODE_ASSERTMESSAGE("Failed to copy memory.");
            return eStatus;
        }
    }

    // r5
    if (m_pictureCodingType != I_TYPE && params->pAvcQCParams && params->pAvcQCParams->NonFTQSkipThresholdLUTInput)
    {
        cmd.DW32.SkipVal = (uint16_t)CalcSkipVal(cmd.DW3.BlockBasedSkipEnable, picParams->transform_8x8_mode_flag,
            params->pAvcQCParams->NonFTQSkipThresholdLUT[sliceQP]);

    }
    else
    {
        if (m_pictureCodingType == P_TYPE)
        {
            cmd.DW32.SkipVal = SkipVal_P_Common
                [cmd.DW3.BlockBasedSkipEnable]
            [picParams->transform_8x8_mode_flag]
            [sliceQP];
        }
        else if (m_pictureCodingType == B_TYPE)
        {
            cmd.DW32.SkipVal = SkipVal_B_Common
                [cmd.DW3.BlockBasedSkipEnable]
            [picParams->transform_8x8_mode_flag]
            [sliceQP];
        }
    }

    cmd.ModeMvCost.DW13.QpPrimeY = sliceQP;
    // QpPrimeCb and QpPrimeCr are not used by Kernel. Following settings are for CModel matching.
    cmd.ModeMvCost.DW13.QpPrimeCb = sliceQP;
    cmd.ModeMvCost.DW13.QpPrimeCr = sliceQP;
    cmd.ModeMvCost.DW13.TargetSizeInWord = 0xff; // hardcoded for BRC disabled

    if (bMultiPredEnable && (m_pictureCodingType != I_TYPE))
    {
        cmd.DW32.MultiPredL0Disable = feiPicParams->MultiPredL0 ? CODECHAL_ENCODE_AVC_MULTIPRED_ENABLE : CODECHAL_ENCODE_AVC_MULTIPRED_DISABLE;
        cmd.DW32.MultiPredL1Disable = (m_pictureCodingType == B_TYPE && feiPicParams->MultiPredL1) ? CODECHAL_ENCODE_AVC_MULTIPRED_ENABLE : CODECHAL_ENCODE_AVC_MULTIPRED_DISABLE;
    }
    else
    {
        cmd.DW32.MultiPredL0Disable = CODECHAL_ENCODE_AVC_MULTIPRED_DISABLE;
        cmd.DW32.MultiPredL1Disable = CODECHAL_ENCODE_AVC_MULTIPRED_DISABLE;
    }

    if (!framePicture)
    {
        if (m_pictureCodingType != I_TYPE)
        {
            cmd.DW34.List0RefID0FieldParity = CodecHalAvcEncode_GetFieldParity(slcParams, LIST_0, CODECHAL_ENCODE_REF_ID_0);
            cmd.DW34.List0RefID1FieldParity = CodecHalAvcEncode_GetFieldParity(slcParams, LIST_0, CODECHAL_ENCODE_REF_ID_1);
            cmd.DW34.List0RefID2FieldParity = CodecHalAvcEncode_GetFieldParity(slcParams, LIST_0, CODECHAL_ENCODE_REF_ID_2);
            cmd.DW34.List0RefID3FieldParity = CodecHalAvcEncode_GetFieldParity(slcParams, LIST_0, CODECHAL_ENCODE_REF_ID_3);
            cmd.DW34.List0RefID4FieldParity = CodecHalAvcEncode_GetFieldParity(slcParams, LIST_0, CODECHAL_ENCODE_REF_ID_4);
            cmd.DW34.List0RefID5FieldParity = CodecHalAvcEncode_GetFieldParity(slcParams, LIST_0, CODECHAL_ENCODE_REF_ID_5);
            cmd.DW34.List0RefID6FieldParity = CodecHalAvcEncode_GetFieldParity(slcParams, LIST_0, CODECHAL_ENCODE_REF_ID_6);
            cmd.DW34.List0RefID7FieldParity = CodecHalAvcEncode_GetFieldParity(slcParams, LIST_0, CODECHAL_ENCODE_REF_ID_7);
        }
        if (m_pictureCodingType == B_TYPE)
        {
            cmd.DW34.List1RefID0FieldParity = CodecHalAvcEncode_GetFieldParity(slcParams, LIST_1, CODECHAL_ENCODE_REF_ID_0);
            cmd.DW34.List1RefID1FieldParity = CodecHalAvcEncode_GetFieldParity(slcParams, LIST_1, CODECHAL_ENCODE_REF_ID_1);
        }
    }

    if (m_adaptiveTransformDecisionEnabled)
    {
        if (m_pictureCodingType != I_TYPE)
        {
            cmd.DW34.EnableAdaptiveTxDecision = true;
        }
        cmd.DW60.TxDecisonThreshold = m_adaptiveTxDecisionThreshold;
    }

    if (m_adaptiveTransformDecisionEnabled || m_flatnessCheckEnabled)
    {
        cmd.DW60.MBTextureThreshold = m_mbTextureThreshold;
    }

    cmd.DW34.EnableAdaptiveTxDecision = false;

    if (m_pictureCodingType == B_TYPE)
    {
        cmd.DW34.List1RefID0FrameFieldFlag = GetRefPicFieldFlag(params, LIST_1, CODECHAL_ENCODE_REF_ID_0);
        cmd.DW34.List1RefID1FrameFieldFlag = GetRefPicFieldFlag(params, LIST_1, CODECHAL_ENCODE_REF_ID_1);
        cmd.DW34.bDirectMode = slcParams->direct_spatial_mv_pred_flag;
    }

    cmd.DW34.EnablePerMBStaticCheck = params->bStaticFrameDetectionEnabled;
    cmd.DW34.EnableAdaptiveSearchWindowSize = params->bApdatvieSearchWindowSizeEnabled;
    cmd.DW34.RemoveIntraRefreshOverlap = picParams->bDisableRollingIntraRefreshOverlap;
    cmd.DW34.bOriginalBff = framePicture ? 0 :
        ((m_firstField && (bottomField)) || (!m_firstField && (!bottomField)));
    cmd.DW34.EnableMBFlatnessChkOptimization = m_flatnessCheckEnabled;
    cmd.DW34.ROIEnableFlag = params->bRoiEnabled;
    cmd.DW34.MADEnableFlag                   = m_madEnabled;
    cmd.DW34.MBBrcEnable = 0;
    cmd.DW34.ArbitraryNumMbsPerSlice = m_arbitraryNumMbsInSlice;
    cmd.DW34.TQEnable                        = m_trellisQuantParams.dwTqEnabled;  //Enabled for KBL
    cmd.DW34.ForceNonSkipMbEnable = params->bMbDisableSkipMapEnabled;
    if (params->pAvcQCParams && !cmd.DW34.ForceNonSkipMbEnable) // ignore DisableEncSkipCheck if Mb Disable Skip Map is available
    {
        cmd.DW34.DisableEncSkipCheck = params->pAvcQCParams->skipCheckDisable;
    }
    cmd.DW34.CQPFlag                  = 1;  // 1 - Rate Control is CQP, 0 - Rate Control is BRC
    cmd.DW36.CheckAllFractionalEnable = bCAFEnable;
    cmd.DW38.RefThreshold = m_refThresholdFei;
    cmd.DW39.HMERefWindowsCombThreshold = (m_pictureCodingType == B_TYPE) ? HMEBCombineLen_fei[seqParams->TargetUsage] : HMECombineLen_fei[seqParams->TargetUsage];

    // Default:2 used for MBBRC (MB QP Surface width and height are 4x downscaled picture in MB unit * 4  bytes)
    // 0 used for MBQP data surface (MB QP Surface width and height are same as the input picture size in MB unit * 1bytes)
    // starting GEN9, BRC use split kernel, MB QP surface is same size as input picture
    cmd.DW47.MbQpReadFactor = (bMbBrcEnabled || bMbQpDataEnabled) ? 0 : 2;

    // Those fields are not really used for I_dist kernel,
    // but set them to 0 to get bit-exact match with kernel prototype
    if (params->bMbEncIFrameDistEnabled)
    {
        cmd.ModeMvCost.DW13.QpPrimeY = 0;
        cmd.ModeMvCost.DW13.QpPrimeCb = 0;
        cmd.ModeMvCost.DW13.QpPrimeCr = 0;
        cmd.DW33.Intra16x16NonDCPredPenalty = 0;
        cmd.DW33.Intra4x4NonDCPredPenalty = 0;
        cmd.DW33.Intra8x8NonDCPredPenalty = 0;
    }

    //r6
    if (cmd.DW4.UseActualRefQPValue)
    {
        cmd.DW44.ActualQPValueForRefID0List0 = AVCGetQPValueFromRefList(params, LIST_0, CODECHAL_ENCODE_REF_ID_0);
        cmd.DW44.ActualQPValueForRefID1List0 = AVCGetQPValueFromRefList(params, LIST_0, CODECHAL_ENCODE_REF_ID_1);
        cmd.DW44.ActualQPValueForRefID2List0 = AVCGetQPValueFromRefList(params, LIST_0, CODECHAL_ENCODE_REF_ID_2);
        cmd.DW44.ActualQPValueForRefID3List0 = AVCGetQPValueFromRefList(params, LIST_0, CODECHAL_ENCODE_REF_ID_3);
        cmd.DW45.ActualQPValueForRefID4List0 = AVCGetQPValueFromRefList(params, LIST_0, CODECHAL_ENCODE_REF_ID_4);
        cmd.DW45.ActualQPValueForRefID5List0 = AVCGetQPValueFromRefList(params, LIST_0, CODECHAL_ENCODE_REF_ID_5);
        cmd.DW45.ActualQPValueForRefID6List0 = AVCGetQPValueFromRefList(params, LIST_0, CODECHAL_ENCODE_REF_ID_6);
        cmd.DW45.ActualQPValueForRefID7List0 = AVCGetQPValueFromRefList(params, LIST_0, CODECHAL_ENCODE_REF_ID_7);
        cmd.DW46.ActualQPValueForRefID0List1 = AVCGetQPValueFromRefList(params, LIST_1, CODECHAL_ENCODE_REF_ID_0);
        cmd.DW46.ActualQPValueForRefID1List1 = AVCGetQPValueFromRefList(params, LIST_1, CODECHAL_ENCODE_REF_ID_1);
    }

    uint8_t tableIdx = m_pictureCodingType - 1;
    cmd.DW46.RefCost = RefCost_MultiRefQp_Fei[tableIdx][sliceQP];

    // Picture Coding Type dependent parameters
    if (m_pictureCodingType == I_TYPE)
    {
        cmd.DW0.SkipModeEn = 0;
        cmd.DW37.SkipModeEn = 0;
        cmd.DW36.HMECombineOverlap = 0;
        cmd.DW36.CheckAllFractionalEnable = 0;
        cmd.DW47.IntraCostSF = 16; // This is not used but recommended to set this to 16 by Kernel team
        cmd.DW34.EnableDirectBiasAdjustment = 0;
        cmd.DW34.EnableGlobalMotionBiasAdjustment = 0;
    }
    else if (m_pictureCodingType == P_TYPE)
    {
        cmd.DW1.MaxNumMVs = GetMaxMvsPer2Mb(seqParams->Level) / 2;
        cmd.DW3.BMEDisableFBR = 1;
        cmd.DW5.RefWidth = cmd.DW39.RefWidth = refWidth;
        cmd.DW5.RefHeight = cmd.DW39.RefHeight = refHeight;
        cmd.DW7.NonSkipZMvAdded = 1;
        cmd.DW7.NonSkipModeAdded = 1;
        cmd.DW7.SkipCenterMask = 1;
        cmd.DW47.IntraCostSF =
            bAdaptiveIntraScalingEnable ?
            AdaptiveIntraScalingFactor_Cm_Common[sliceQP] :
            IntraScalingFactor_Cm_Common[sliceQP];
        cmd.DW47.MaxVmvR = (framePicture) ? CodecHalAvcEncode_GetMaxMvLen(seqParams->Level) * 4 : (CodecHalAvcEncode_GetMaxMvLen(seqParams->Level) >> 1) * 4;
        cmd.DW36.HMECombineOverlap = 1;
        cmd.DW36.NumRefIdxL0MinusOne = bMultiPredEnable ? slcParams->num_ref_idx_l0_active_minus1 : 0;
        cmd.DW36.CheckAllFractionalEnable = feiPicParams->RepartitionCheckEnable;
        cmd.DW34.EnableDirectBiasAdjustment = 0;
        if (params->pAvcQCParams)
        {
            cmd.DW34.EnableGlobalMotionBiasAdjustment = params->pAvcQCParams->globalMotionBiasAdjustmentEnable;
            if (cmd.DW34.EnableGlobalMotionBiasAdjustment)
            {
                cmd.DW61.HMEMVCostScalingFactor = params->pAvcQCParams->HMEMVCostScalingFactor;
            }
        }

        cmd.DW66.NumMVPredictorsL0 = feiPicParams->NumMVPredictorsL0;
        cmd.DW66.NumMVPredictorsL1 = 0;
    }
    else
    {
        // B_TYPE
        cmd.DW1.MaxNumMVs = GetMaxMvsPer2Mb(seqParams->Level) / 2;
        cmd.DW1.BiWeight = m_biWeight;
        cmd.DW3.SearchCtrl = 7;
        cmd.DW3.SkipType = 1;
        cmd.DW5.RefWidth = cmd.DW39.RefWidth = refWidth;
        cmd.DW5.RefHeight = cmd.DW39.RefHeight = refHeight;
        cmd.DW7.SkipCenterMask = 0xFF;
        cmd.DW47.IntraCostSF =
            bAdaptiveIntraScalingEnable ?
            AdaptiveIntraScalingFactor_Cm_Common[sliceQP] :
            IntraScalingFactor_Cm_Common[sliceQP];
        cmd.DW47.MaxVmvR = (framePicture) ? CodecHalAvcEncode_GetMaxMvLen(seqParams->Level) * 4 : (CodecHalAvcEncode_GetMaxMvLen(seqParams->Level) >> 1) * 4;
        cmd.DW36.HMECombineOverlap = 1;
        // Checking if the forward frame (List 1 index 0) is a short term reference
        {
            auto codecHalPic = params->pSlcParams->RefPicList[LIST_1][0];
            if (codecHalPic.PicFlags != PICTURE_INVALID &&
                codecHalPic.FrameIdx != CODECHAL_ENCODE_AVC_INVALID_PIC_ID &&
                params->pPicIdx[codecHalPic.FrameIdx].bValid)
            {
                // Although its name is FWD, it actually means the future frame or the backward reference frame
                cmd.DW36.IsFwdFrameShortTermRef = CodecHal_PictureIsShortTermRef(params->pPicParams->RefFrameList[codecHalPic.FrameIdx]);
            }
            else
            {
                CODECHAL_ENCODE_ASSERTMESSAGE("Invalid backward reference frame.");
                eStatus = MOS_STATUS_INVALID_PARAMETER;
                return eStatus;
            }
        }
        cmd.DW36.NumRefIdxL0MinusOne = bMultiPredEnable ? slcParams->num_ref_idx_l0_active_minus1 : 0;
        cmd.DW36.NumRefIdxL1MinusOne = bMultiPredEnable ? slcParams->num_ref_idx_l1_active_minus1 : 0;
        cmd.DW36.CheckAllFractionalEnable = feiPicParams->RepartitionCheckEnable;
        cmd.DW40.DistScaleFactorRefID0List0 = m_distScaleFactorList0[0];
        cmd.DW40.DistScaleFactorRefID1List0 = m_distScaleFactorList0[1];
        cmd.DW41.DistScaleFactorRefID2List0 = m_distScaleFactorList0[2];
        cmd.DW41.DistScaleFactorRefID3List0 = m_distScaleFactorList0[3];
        cmd.DW42.DistScaleFactorRefID4List0 = m_distScaleFactorList0[4];
        cmd.DW42.DistScaleFactorRefID5List0 = m_distScaleFactorList0[5];
        cmd.DW43.DistScaleFactorRefID6List0 = m_distScaleFactorList0[6];
        cmd.DW43.DistScaleFactorRefID7List0 = m_distScaleFactorList0[7];
        if (params->pAvcQCParams)
        {
            cmd.DW34.EnableDirectBiasAdjustment = params->pAvcQCParams->directBiasAdjustmentEnable;
            if (cmd.DW34.EnableDirectBiasAdjustment)
            {
                cmd.DW7.NonSkipModeAdded = 1;
                cmd.DW7.NonSkipZMvAdded = 1;
            }

            cmd.DW34.EnableGlobalMotionBiasAdjustment = params->pAvcQCParams->globalMotionBiasAdjustmentEnable;
            if (cmd.DW34.EnableGlobalMotionBiasAdjustment)
            {
                cmd.DW61.HMEMVCostScalingFactor = params->pAvcQCParams->HMEMVCostScalingFactor;
            }
        }

        cmd.DW66.NumMVPredictorsL0 = feiPicParams->NumMVPredictorsL0;
        cmd.DW66.NumMVPredictorsL1 = feiPicParams->NumMVPredictorsL1;
    }

    *params->pdwBlockBasedSkipEn = cmd.DW3.BlockBasedSkipEnable;

    if (picParams->EnableRollingIntraRefresh)
    {
        cmd.DW34.IntraRefreshEn = picParams->EnableRollingIntraRefresh;

        /* Multiple predictor should be completely disabled for the RollingI feature. This does not lead to much quality drop for P frames especially for TU as 1 */
        cmd.DW32.MultiPredL0Disable = CODECHAL_ENCODE_AVC_MULTIPRED_DISABLE;

        /* Pass the same IntraRefreshUnit to the kernel w/o the adjustment by -1, so as to have an overlap of one MB row or column of Intra macroblocks
        across one P frame to another P frame, as needed by the RollingI algo */
        if (ROLLING_I_SQUARE == picParams->EnableRollingIntraRefresh && RATECONTROL_CQP != seqParams->RateControlMethod)
        {
            /*BRC update kernel updates these CURBE to MBEnc*/
            cmd.DW4.EnableIntraRefresh = false;
            cmd.DW34.IntraRefreshEn    = ROLLING_I_DISABLED;
            cmd.DW48.IntraRefreshMBNum = 0; /* MB column number */
            cmd.DW61.IntraRefreshMBy   = 0; /* MB row number */
        }
        else
        {
            cmd.DW4.EnableIntraRefresh = true;
            cmd.DW34.IntraRefreshEn    = picParams->EnableRollingIntraRefresh;
            cmd.DW48.IntraRefreshMBNum = picParams->IntraRefreshMBx; /* MB row or column number */
	    cmd.DW61.IntraRefreshMBy   = picParams->IntraRefreshMBy; /* MB row number */
        }
        cmd.DW48.IntraRefreshUnitInMBMinus1 = picParams->IntraRefreshUnitinMB;
        cmd.DW48.IntraRefreshQPDelta = picParams->IntraRefreshQPDelta;
    }
    else
    {
        cmd.DW34.IntraRefreshEn = 0;
    }

    if (true == params->bRoiEnabled)
    {
        cmd.DW49.ROI1_X_left = picParams->ROI[0].Left;
        cmd.DW49.ROI1_Y_top = picParams->ROI[0].Top;
        cmd.DW50.ROI1_X_right = picParams->ROI[0].Right;
        cmd.DW50.ROI1_Y_bottom = picParams->ROI[0].Bottom;

        cmd.DW51.ROI2_X_left = picParams->ROI[1].Left;
        cmd.DW51.ROI2_Y_top = picParams->ROI[1].Top;
        cmd.DW52.ROI2_X_right = picParams->ROI[1].Right;
        cmd.DW52.ROI2_Y_bottom = picParams->ROI[1].Bottom;

        cmd.DW53.ROI3_X_left = picParams->ROI[2].Left;
        cmd.DW53.ROI3_Y_top = picParams->ROI[2].Top;
        cmd.DW54.ROI3_X_right = picParams->ROI[2].Right;
        cmd.DW54.ROI3_Y_bottom = picParams->ROI[2].Bottom;

        cmd.DW55.ROI4_X_left = picParams->ROI[3].Left;
        cmd.DW55.ROI4_Y_top = picParams->ROI[3].Top;
        cmd.DW56.ROI4_X_right = picParams->ROI[3].Right;
        cmd.DW56.ROI4_Y_bottom = picParams->ROI[3].Bottom;

        if (bBrcEnabled == false)
        {
            uint16_t numROI = picParams->NumROI;
            int8_t priorityLevelOrDQp[CODECHAL_ENCODE_AVC_MAX_ROI_NUMBER] = { 0 };

            // cqp case
            for (unsigned int i = 0; i < numROI; i += 1)
            {
                int8_t dQpRoi = picParams->ROI[i].PriorityLevelOrDQp;

                // clip qp roi in order to have (qp + qpY) in range [0, 51]
                priorityLevelOrDQp[i] = (int8_t)CodecHal_Clip3(-sliceQP, CODECHAL_ENCODE_AVC_MAX_SLICE_QP - sliceQP, dQpRoi);
            }

            cmd.DW57.ROI1_dQpPrimeY = priorityLevelOrDQp[0];
            cmd.DW57.ROI2_dQpPrimeY = priorityLevelOrDQp[1];
            cmd.DW57.ROI3_dQpPrimeY = priorityLevelOrDQp[2];
            cmd.DW57.ROI4_dQpPrimeY = priorityLevelOrDQp[3];
        }
        else
        {
            // kernel does not support BRC case
            cmd.DW34.ROIEnableFlag = 0;
        }
    }
    else if (params->bDirtyRoiEnabled)
    {
        // enable Dirty Rect flag
        cmd.DW4.EnableDirtyRect = true;

        cmd.DW49.ROI1_X_left = params->pPicParams->DirtyROI[0].Left;
        cmd.DW49.ROI1_Y_top = params->pPicParams->DirtyROI[0].Top;
        cmd.DW50.ROI1_X_right = params->pPicParams->DirtyROI[0].Right;
        cmd.DW50.ROI1_Y_bottom = params->pPicParams->DirtyROI[0].Bottom;

        cmd.DW51.ROI2_X_left = params->pPicParams->DirtyROI[1].Left;
        cmd.DW51.ROI2_Y_top = params->pPicParams->DirtyROI[1].Top;
        cmd.DW52.ROI2_X_right = params->pPicParams->DirtyROI[1].Right;
        cmd.DW52.ROI2_Y_bottom = params->pPicParams->DirtyROI[1].Bottom;

        cmd.DW53.ROI3_X_left = params->pPicParams->DirtyROI[2].Left;
        cmd.DW53.ROI3_Y_top = params->pPicParams->DirtyROI[2].Top;
        cmd.DW54.ROI3_X_right = params->pPicParams->DirtyROI[2].Right;
        cmd.DW54.ROI3_Y_bottom = params->pPicParams->DirtyROI[2].Bottom;

        cmd.DW55.ROI4_X_left = params->pPicParams->DirtyROI[3].Left;
        cmd.DW55.ROI4_Y_top = params->pPicParams->DirtyROI[3].Top;
        cmd.DW56.ROI4_X_right = params->pPicParams->DirtyROI[3].Right;
        cmd.DW56.ROI4_Y_bottom = params->pPicParams->DirtyROI[3].Bottom;
    }

    if (m_trellisQuantParams.dwTqEnabled)
    {
        // Lambda values for TQ
        if (m_pictureCodingType == I_TYPE)
        {
            cmd.DW58.Value = TQ_LAMBDA_I_FRAME[sliceQP][0];
            cmd.DW59.Value = TQ_LAMBDA_I_FRAME[sliceQP][1];
        }
        else if (m_pictureCodingType == P_TYPE)
        {
            cmd.DW58.Value = TQ_LAMBDA_P_FRAME[sliceQP][0];
            cmd.DW59.Value = TQ_LAMBDA_P_FRAME[sliceQP][1];
        }
        else
        {
            cmd.DW58.Value = TQ_LAMBDA_B_FRAME[sliceQP][0];
            cmd.DW59.Value = TQ_LAMBDA_B_FRAME[sliceQP][1];
        }

        MHW_VDBOX_AVC_SLICE_STATE sliceState;
        MOS_ZeroMemory(&sliceState, sizeof(sliceState));
        sliceState.pEncodeAvcSeqParams   = seqParams;
        sliceState.pEncodeAvcPicParams   = picParams;
        sliceState.pEncodeAvcSliceParams = slcParams;

        // check if Lambda is greater than max value
        CODECHAL_ENCODE_CHK_STATUS_RETURN(GetInterRounding(&sliceState));

        if (cmd.DW58.Lambda8x8Inter > m_maxLambda)
        {
            cmd.DW58.Lambda8x8Inter = 0xf000 + sliceState.dwRoundingValue;
        }

        if (cmd.DW58.Lambda8x8Intra > m_maxLambda)
        {
            cmd.DW58.Lambda8x8Intra = 0xf000 + m_defaultTrellisQuantIntraRounding;
        }

        // check if Lambda is greater than max value
        if (cmd.DW59.LambdaInter > m_maxLambda)
        {
            cmd.DW59.LambdaInter = 0xf000 + sliceState.dwRoundingValue;
        }

        if (cmd.DW59.LambdaIntra > m_maxLambda)
        {
            cmd.DW59.LambdaIntra = 0xf000 + m_defaultTrellisQuantIntraRounding;
        }
    }

    //IPCM QP and threshold
    cmd.DW62.IPCM_QP0                       = m_IPCMThresholdTable[0].QP;
    cmd.DW62.IPCM_QP1                       = m_IPCMThresholdTable[1].QP;
    cmd.DW62.IPCM_QP2                       = m_IPCMThresholdTable[2].QP;
    cmd.DW62.IPCM_QP3                       = m_IPCMThresholdTable[3].QP;
    cmd.DW63.IPCM_QP4                       = m_IPCMThresholdTable[4].QP;

    cmd.DW63.IPCM_Thresh0                   = m_IPCMThresholdTable[0].Threshold;
    cmd.DW64.IPCM_Thresh1                   = m_IPCMThresholdTable[1].Threshold;
    cmd.DW64.IPCM_Thresh2                   = m_IPCMThresholdTable[2].Threshold;
    cmd.DW65.IPCM_Thresh3                   = m_IPCMThresholdTable[3].Threshold;
    cmd.DW65.IPCM_Thresh4                   = m_IPCMThresholdTable[4].Threshold;

    // r66: FEI specific fields
    cmd.DW66.FEIEnable = 1;
    cmd.DW66.MultipleMVPredictorPerMBEnable = feiPicParams->MVPredictorEnable;
    cmd.DW66.VMEDistortionOutputEnable = feiPicParams->DistortionEnable;
    cmd.DW66.PerMBQpEnable = feiPicParams->bMBQp;
    cmd.DW66.MBInputEnable = feiPicParams->bPerMBInput;

    // FEI mode is disabled when external MVP is available
    if (feiPicParams->MVPredictorEnable)
        cmd.DW66.FEIMode = 0;
    else
        cmd.DW66.FEIMode = 1;

    cmd.DW67.MBDataSurfIndex = mbencMfcAvcPakObj;
    cmd.DW68.MVDataSurfIndex = mbencIndMvData;
    cmd.DW69.IDistSurfIndex = mbencBrcDistortion;
    cmd.DW70.SrcYSurfIndex = mbencCurrY;
    cmd.DW71.MBSpecificDataSurfIndex = mbencMbSpecificData;
    cmd.DW72.AuxVmeOutSurfIndex = mbencAuxVmeOut;
    cmd.DW73.CurrRefPicSelSurfIndex = mbencRefpicselectL0;
    cmd.DW74.HMEMVPredFwdBwdSurfIndex = mbencMvDataFromMe;
    cmd.DW75.HMEDistSurfIndex = mbenc4xMeDistortion;
    cmd.DW76.SliceMapSurfIndex = mbencSlicemapData;
    cmd.DW77.FwdFrmMBDataSurfIndex = mbencFwdMbData;
    cmd.DW78.FwdFrmMVSurfIndex = mbencFwdMvData;
    cmd.DW79.MBQPBuffer = mbencMbqp;
    cmd.DW80.MBBRCLut = mbencMbbrcConstData;
    cmd.DW81.VMEInterPredictionSurfIndex = mbencVmeInterPredCurrPicIdx0;
    cmd.DW82.VMEInterPredictionMRSurfIndex = mbencVmeInterPredCurrPicIdx1;
    cmd.DW83.MbStatsSurfIndex = mbencMbStats;
    cmd.DW84.MADSurfIndex = mbencMadData;
    cmd.DW85.BRCCurbeSurfIndex = mbencBrcCurbeData;
    cmd.DW86.ForceNonSkipMBmapSurface = mbencForceNonskipMbMap;
    cmd.DW87.ReservedIndex = mbEncAdv;
    cmd.DW88.StaticDetectionCostTableIndex = mbencSfdCostTable;
    cmd.DW89.ScoreboardSurfIndex = mbencSwScoreboard;
    cmd.DW90.FEIMVPredictorSurfIndex = mbEncMVPredictor;

    CODECHAL_ENCODE_CHK_STATUS_RETURN(params->pKernelState->m_dshRegion.AddData(
        &cmd,
        params->pKernelState->dwCurbeOffset,
        sizeof(cmd)));

    return eStatus;
}

MOS_STATUS CodechalEncodeAvcEncFeiG12::SendAvcMbEncSurfaces(PMOS_COMMAND_BUFFER cmdBuffer, PCODECHAL_ENCODE_AVC_MBENC_SURFACE_PARAMS params)
{
    MOS_STATUS eStatus = MOS_STATUS_SUCCESS;

    CODECHAL_ENCODE_CHK_NULL_RETURN(cmdBuffer);
    CODECHAL_ENCODE_CHK_NULL_RETURN(params);
    CODECHAL_ENCODE_CHK_NULL_RETURN(params->pAvcSlcParams);
    CODECHAL_ENCODE_CHK_NULL_RETURN(params->ppRefList);
    CODECHAL_ENCODE_CHK_NULL_RETURN(params->pCurrOriginalPic);
    CODECHAL_ENCODE_CHK_NULL_RETURN(params->pCurrReconstructedPic);
    CODECHAL_ENCODE_CHK_NULL_RETURN(params->psCurrPicSurface);

    CODECHAL_ENCODE_CHK_NULL_RETURN(params->pAvcPicIdx);
    CODECHAL_ENCODE_CHK_NULL_RETURN(params->pMbEncBindingTable);
    CODECHAL_ENCODE_CHK_NULL_RETURN(params->pKernelState);
    CODECHAL_ENCODE_CHK_NULL_RETURN(params->pFeiPicParams);

    auto feiPicParams = (CodecEncodeAvcFeiPicParams *)params->pFeiPicParams;
    auto kernelState  = params->pKernelState;
    auto mbEncBindingTable = params->pMbEncBindingTable;

    bool currFieldPicture = CodecHal_PictureIsField(*(params->pCurrOriginalPic)) ? 1 : 0;
    bool currBottomField = CodecHal_PictureIsBottomField(*(params->pCurrOriginalPic)) ? 1 : 0;
    auto currPicRefListEntry = params->ppRefList[params->pCurrReconstructedPic->FrameIdx];
    auto mbCodeBuffer = &currPicRefListEntry->resRefMbCodeBuffer;
    auto mvDataBuffer = &currPicRefListEntry->resRefMvDataBuffer;

    uint32_t refMbCodeBottomFieldOffset, refMbCodeBottomFieldOffsetUsed;
    uint32_t refMvBottomFieldOffset, refMvBottomFieldOffsetUsed;
    refMvBottomFieldOffset;
    if (feiPicParams->MbCodeMvEnable)
    {
        refMbCodeBottomFieldOffset = 0;
        refMvBottomFieldOffset = 0;
    }
    else
    {
        refMbCodeBottomFieldOffset =
            params->dwFrameFieldHeightInMb * params->dwFrameWidthInMb * 64;
        refMvBottomFieldOffset =
            MOS_ALIGN_CEIL(params->dwFrameFieldHeightInMb * params->dwFrameWidthInMb * (32 * 4), 0x1000);
    }

    uint8_t vdirection;
    if (params->bMbEncIFrameDistInUse)
    {
        vdirection = CODECHAL_VDIRECTION_FRAME;
    }
    else
    {
        vdirection = (CodecHal_PictureIsFrame(*(params->pCurrOriginalPic))) ? CODECHAL_VDIRECTION_FRAME : (currBottomField) ? CODECHAL_VDIRECTION_BOT_FIELD : CODECHAL_VDIRECTION_TOP_FIELD;
    }

    // PAK Obj command buffer
    uint32_t size = params->dwFrameWidthInMb * params->dwFrameFieldHeightInMb * 16 * 4;  // 11DW + 5DW padding
    CODECHAL_SURFACE_CODEC_PARAMS surfaceCodecParams;
    memset((void *)&surfaceCodecParams, 0, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
    surfaceCodecParams.presBuffer            = mbCodeBuffer;
    surfaceCodecParams.dwSize                = size;
    surfaceCodecParams.dwOffset              = params->dwMbCodeBottomFieldOffset;
    surfaceCodecParams.dwBindingTableOffset  = mbEncBindingTable->dwAvcMBEncMfcAvcPakObj;
    surfaceCodecParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_PAK_OBJECT_ENCODE].Value;
    surfaceCodecParams.bRenderTarget         = true;
    surfaceCodecParams.bIsWritable           = true;
    CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
        m_hwInterface,
        cmdBuffer,
        &surfaceCodecParams,
        kernelState));

    // MV data buffer
    size = params->dwFrameWidthInMb * params->dwFrameFieldHeightInMb * 32 * 4;
    memset((void *)&surfaceCodecParams, 0, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
    surfaceCodecParams.presBuffer            = mvDataBuffer;
    surfaceCodecParams.dwSize                = size;
    surfaceCodecParams.dwOffset              = params->dwMvBottomFieldOffset;
    surfaceCodecParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_MV_DATA_ENCODE].Value;
    surfaceCodecParams.dwBindingTableOffset  = mbEncBindingTable->dwAvcMBEncIndMVData;
    surfaceCodecParams.bRenderTarget         = true;
    surfaceCodecParams.bIsWritable           = true;
    CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
        m_hwInterface,
        cmdBuffer,
        &surfaceCodecParams,
        kernelState));

    // Current Picture Y
    memset((void *)&surfaceCodecParams, 0, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
    surfaceCodecParams.bIs2DSurface               = true;
    surfaceCodecParams.bMediaBlockRW              = true;  // Use media block RW for DP 2D surface access
    surfaceCodecParams.bUseUVPlane                = true;
    surfaceCodecParams.psSurface                  = params->psCurrPicSurface;
    surfaceCodecParams.dwOffset                   = params->dwCurrPicSurfaceOffset;
    surfaceCodecParams.dwCacheabilityControl      = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_CURR_ENCODE].Value;
    surfaceCodecParams.dwBindingTableOffset       = mbEncBindingTable->dwAvcMBEncCurrY;
    surfaceCodecParams.dwUVBindingTableOffset     = mbEncBindingTable->dwAvcMBEncCurrUV;
    surfaceCodecParams.dwVerticalLineStride       = params->dwVerticalLineStride;
    surfaceCodecParams.dwVerticalLineStrideOffset = params->dwVerticalLineStrideOffset;
    CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
        m_hwInterface,
        cmdBuffer,
        &surfaceCodecParams,
        kernelState));

    if (params->bHmeEnabled)
    {
        CODECHAL_ENCODE_CHK_NULL_RETURN(params->ps4xMeMvDataBuffer);

        memset((void *)&surfaceCodecParams, 0, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
        surfaceCodecParams.bIs2DSurface          = true;
        surfaceCodecParams.bMediaBlockRW         = true;
        surfaceCodecParams.psSurface             = params->ps4xMeMvDataBuffer;
        surfaceCodecParams.dwOffset              = params->dwMeMvBottomFieldOffset;
        surfaceCodecParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_MV_DATA_ENCODE].Value;
        surfaceCodecParams.dwBindingTableOffset  = mbEncBindingTable->dwAvcMBEncMVDataFromME;
        CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
            m_hwInterface,
            cmdBuffer,
            &surfaceCodecParams,
            kernelState));

        CODECHAL_ENCODE_CHK_NULL_RETURN(params->ps4xMeDistortionBuffer);

        memset((void *)&surfaceCodecParams, 0, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
        surfaceCodecParams.bIs2DSurface          = true;
        surfaceCodecParams.bMediaBlockRW         = true;
        surfaceCodecParams.psSurface             = params->ps4xMeDistortionBuffer;
        surfaceCodecParams.dwOffset              = params->dwMeDistortionBottomFieldOffset;
        surfaceCodecParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_ME_DISTORTION_ENCODE].Value;
        surfaceCodecParams.dwBindingTableOffset  = mbEncBindingTable->dwAvcMBEncMEDist;
        CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
            m_hwInterface,
            cmdBuffer,
            &surfaceCodecParams,
            kernelState));
    }
    
    // Current Picture Y - VME
    memset((void *)&surfaceCodecParams, 0, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
    surfaceCodecParams.bUseAdvState          = true;
    surfaceCodecParams.psSurface             = params->psCurrPicSurface;
    surfaceCodecParams.dwOffset              = params->dwCurrPicSurfaceOffset;
    surfaceCodecParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_CURR_ENCODE].Value;
    surfaceCodecParams.dwBindingTableOffset  = currFieldPicture ? mbEncBindingTable->dwAvcMBEncFieldCurrPic[0] : mbEncBindingTable->dwAvcMBEncCurrPicFrame[0];
    surfaceCodecParams.ucVDirection          = vdirection;
    CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
        m_hwInterface,
        cmdBuffer,
        &surfaceCodecParams,
        kernelState));

    surfaceCodecParams.dwBindingTableOffset = currFieldPicture ? mbEncBindingTable->dwAvcMBEncFieldCurrPic[1] : mbEncBindingTable->dwAvcMBEncCurrPicFrame[1];
    surfaceCodecParams.ucVDirection         = vdirection;
    CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
        m_hwInterface,
        cmdBuffer,
        &surfaceCodecParams,
        kernelState));

    // Setup references 1...n
    // LIST 0 references
    uint8_t refIdx;
    for (refIdx = 0; refIdx <= params->pAvcSlcParams->num_ref_idx_l0_active_minus1; refIdx++)
    {
        auto     refPic = params->pAvcSlcParams->RefPicList[LIST_0][refIdx];
        if (!CodecHal_PictureIsInvalid(refPic) && params->pAvcPicIdx[refPic.FrameIdx].bValid)
        {
            uint8_t  refPicIdx      = params->pAvcPicIdx[refPic.FrameIdx].ucPicIdx;
            bool     refBottomField = (CodecHal_PictureIsBottomField(refPic)) ? true : false;
            uint32_t refBindingTableOffset;
            uint8_t  refVDirection;
            // Program the surface based on current picture's field/frame mode
            if (currFieldPicture)  // if current picture is field
            {
                if (refBottomField)
                {
                    refVDirection       = CODECHAL_VDIRECTION_BOT_FIELD;
                    refBindingTableOffset = mbEncBindingTable->dwAvcMBEncFwdPicBotField[refIdx];
                }
                else
                {
                    refVDirection       = CODECHAL_VDIRECTION_TOP_FIELD;
                    refBindingTableOffset = mbEncBindingTable->dwAvcMBEncFwdPicTopField[refIdx];
                }
            }
            else  // if current picture is frame
            {
                refVDirection       = CODECHAL_VDIRECTION_FRAME;
                refBindingTableOffset = mbEncBindingTable->dwAvcMBEncFwdPicFrame[refIdx];
            }

            // Picture Y VME
            memset((void *)&surfaceCodecParams, 0, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
            surfaceCodecParams.bUseAdvState = true;
            if ((0 == refIdx) && (params->bUseWeightedSurfaceForL0))
            {
                surfaceCodecParams.psSurface = &params->pWeightedPredOutputPicSelectList[CODEC_AVC_WP_OUTPUT_L0_START + refIdx].sBuffer;
            }
            else
            {
                surfaceCodecParams.psSurface = &params->ppRefList[refPicIdx]->sRefBuffer;
            }
            surfaceCodecParams.dwWidthInUse  = params->dwFrameWidthInMb * 16;
            surfaceCodecParams.dwHeightInUse = params->dwFrameHeightInMb * 16;

            surfaceCodecParams.dwBindingTableOffset  = refBindingTableOffset;
            surfaceCodecParams.ucVDirection          = refVDirection;
            surfaceCodecParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_REF_ENCODE].Value;

            CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
                m_hwInterface,
                cmdBuffer,
                &surfaceCodecParams,
                kernelState));
        }
    }

    // Setup references 1...n
    // LIST 1 references
    for (refIdx = 0; refIdx <= params->pAvcSlcParams->num_ref_idx_l1_active_minus1; refIdx++)
    {
        if (!currFieldPicture && refIdx > 0)
        {
            // Only 1 LIST 1 reference required here since only single ref is supported in frame case
            break;
        }

        auto     refPic = params->pAvcSlcParams->RefPicList[LIST_1][refIdx];
        if (!CodecHal_PictureIsInvalid(refPic) && params->pAvcPicIdx[refPic.FrameIdx].bValid)
        {
            uint8_t  refPicIdx      = params->pAvcPicIdx[refPic.FrameIdx].ucPicIdx;
            bool     refBottomField = (CodecHal_PictureIsBottomField(refPic)) ? 1 : 0;
	    uint32_t refBindingTableOffset;
	    uint8_t  refVDirection;
            // Program the surface based on current picture's field/frame mode
            if (currFieldPicture)  // if current picture is field
            {
                if (refBottomField)
                {
                    refVDirection                = CODECHAL_VDIRECTION_BOT_FIELD;
                    refMbCodeBottomFieldOffsetUsed = refMbCodeBottomFieldOffset;
                    refMvBottomFieldOffsetUsed     = refMvBottomFieldOffset;
                    refBindingTableOffset          = mbEncBindingTable->dwAvcMBEncBwdPicBotField[refIdx];
                }
                else
                {
                    refVDirection                = CODECHAL_VDIRECTION_TOP_FIELD;
                    refMbCodeBottomFieldOffsetUsed = 0;
                    refMvBottomFieldOffsetUsed     = 0;
                    refBindingTableOffset          = mbEncBindingTable->dwAvcMBEncBwdPicTopField[refIdx];
                }
            }
            else  // if current picture is frame
            {
                refVDirection                = CODECHAL_VDIRECTION_FRAME;
                refMbCodeBottomFieldOffsetUsed = 0;
                refMvBottomFieldOffsetUsed     = 0;
                refBindingTableOffset          = mbEncBindingTable->dwAvcMBEncBwdPicFrame[refIdx];
            }

            // Picture Y VME
            memset((void *)&surfaceCodecParams, 0, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
            surfaceCodecParams.bUseAdvState = true;
            if ((0 == refIdx) && (params->bUseWeightedSurfaceForL1))
            {
                surfaceCodecParams.psSurface = &params->pWeightedPredOutputPicSelectList[CODEC_AVC_WP_OUTPUT_L1_START + refIdx].sBuffer;
            }
            else
            {
                surfaceCodecParams.psSurface = &params->ppRefList[refPicIdx]->sRefBuffer;
            }
            surfaceCodecParams.dwWidthInUse  = params->dwFrameWidthInMb * 16;
            surfaceCodecParams.dwHeightInUse = params->dwFrameHeightInMb * 16;

            surfaceCodecParams.dwBindingTableOffset  = refBindingTableOffset;
            surfaceCodecParams.ucVDirection          = refVDirection;
            surfaceCodecParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_REF_ENCODE].Value;

            CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
                m_hwInterface,
                cmdBuffer,
                &surfaceCodecParams,
                kernelState));

            if (refIdx == 0)
            {
                if(currFieldPicture && (params->ppRefList[refPicIdx]->ucAvcPictureCodingType == CODEC_AVC_PIC_CODING_TYPE_FRAME || params->ppRefList[refPicIdx]->ucAvcPictureCodingType == CODEC_AVC_PIC_CODING_TYPE_INVALID))
                {
                    refMbCodeBottomFieldOffsetUsed = 0;
                    refMvBottomFieldOffsetUsed     = 0;
                }
                // MB data buffer
                size = params->dwFrameWidthInMb * params->dwFrameFieldHeightInMb * 16 * 4;
                memset((void *)&surfaceCodecParams, 0, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
                surfaceCodecParams.dwSize                = size;
                if (feiPicParams->MbCodeMvEnable && currFieldPicture)
                {
                    surfaceCodecParams.presBuffer = refBottomField ? &params->ppRefList[refPicIdx]->resRefBotFieldMbCodeBuffer :
                        &params->ppRefList[refPicIdx]->resRefTopFieldMbCodeBuffer;
                }
                else
                {
                    surfaceCodecParams.presBuffer = &params->ppRefList[refPicIdx]->resRefMbCodeBuffer;
                }
                surfaceCodecParams.dwOffset              = refMbCodeBottomFieldOffsetUsed;
                surfaceCodecParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_PAK_OBJECT_ENCODE].Value;
                surfaceCodecParams.dwBindingTableOffset  = mbEncBindingTable->dwAvcMBEncBwdRefMBData;
                CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
                    m_hwInterface,
                    cmdBuffer,
                    &surfaceCodecParams,
                    kernelState));

                // MV data buffer
                size = params->dwFrameWidthInMb * params->dwFrameFieldHeightInMb * 32 * 4;
                memset((void *)&surfaceCodecParams, 0, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
                surfaceCodecParams.dwSize                = size;
                if (feiPicParams->MbCodeMvEnable && currFieldPicture)
                {
                    surfaceCodecParams.presBuffer = refBottomField ? &params->ppRefList[refPicIdx]->resRefBotFieldMvDataBuffer :
                        &params->ppRefList[refPicIdx]->resRefTopFieldMvDataBuffer;
                }
                else
                {
                    surfaceCodecParams.presBuffer = &params->ppRefList[refPicIdx]->resRefMvDataBuffer;
                }
                surfaceCodecParams.dwOffset              = refMvBottomFieldOffsetUsed;
                surfaceCodecParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_MV_DATA_ENCODE].Value;
                surfaceCodecParams.dwBindingTableOffset  = mbEncBindingTable->dwAvcMBEncBwdRefMVData;
                CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
                    m_hwInterface,
                    cmdBuffer,
                    &surfaceCodecParams,
                    kernelState));
            }

            if (refIdx < CODECHAL_ENCODE_NUM_MAX_VME_L1_REF)
            {
                if (currFieldPicture)
                {
                    // The binding table contains multiple entries for IDX0 backwards references
                    if (refBottomField)
                    {
                        refBindingTableOffset = mbEncBindingTable->dwAvcMBEncBwdPicBotField[refIdx + CODECHAL_ENCODE_NUM_MAX_VME_L1_REF];
                    }
                    else
                    {
                        refBindingTableOffset = mbEncBindingTable->dwAvcMBEncBwdPicTopField[refIdx + CODECHAL_ENCODE_NUM_MAX_VME_L1_REF];
                    }
                }
                else
                {
                    refBindingTableOffset = mbEncBindingTable->dwAvcMBEncBwdPicFrame[refIdx + CODECHAL_ENCODE_NUM_MAX_VME_L1_REF];
                }

                // Picture Y VME
                memset((void *)&surfaceCodecParams, 0, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
                surfaceCodecParams.bUseAdvState          = true;
                surfaceCodecParams.dwWidthInUse          = params->dwFrameWidthInMb * 16;
                surfaceCodecParams.dwHeightInUse         = params->dwFrameHeightInMb * 16;
                surfaceCodecParams.psSurface             = &params->ppRefList[refPicIdx]->sRefBuffer;
                surfaceCodecParams.dwBindingTableOffset  = refBindingTableOffset;
                surfaceCodecParams.ucVDirection          = refVDirection;
                surfaceCodecParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_REF_ENCODE].Value;

                CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
                    m_hwInterface,
                    cmdBuffer,
                    &surfaceCodecParams,
                    kernelState));
            }
        }
    }

    // BRC distortion data buffer for I frame
    if (params->bMbEncIFrameDistInUse)
    {
        memset((void *)&surfaceCodecParams, 0, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
        surfaceCodecParams.bIs2DSurface         = true;
        surfaceCodecParams.bMediaBlockRW        = true;
        surfaceCodecParams.psSurface            = params->psMeBrcDistortionBuffer;
        surfaceCodecParams.dwOffset             = params->dwMeBrcDistortionBottomFieldOffset;
        surfaceCodecParams.dwBindingTableOffset = mbEncBindingTable->dwAvcMBEncBRCDist;
        surfaceCodecParams.bIsWritable          = true;
        surfaceCodecParams.bRenderTarget        = true;
        CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
            m_hwInterface,
            cmdBuffer,
            &surfaceCodecParams,
            kernelState));
    }

    // RefPicSelect of Current Picture
    if (params->bUsedAsRef)
    {
        memset((void *)&surfaceCodecParams, 0, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
        surfaceCodecParams.bIs2DSurface          = true;
        surfaceCodecParams.bMediaBlockRW         = true;
        surfaceCodecParams.psSurface             = &currPicRefListEntry->pRefPicSelectListEntry->sBuffer;
        surfaceCodecParams.psSurface->dwHeight   = MOS_ALIGN_CEIL(surfaceCodecParams.psSurface->dwHeight, 8);
        surfaceCodecParams.dwOffset              = params->dwRefPicSelectBottomFieldOffset;
        surfaceCodecParams.dwBindingTableOffset  = mbEncBindingTable->dwAvcMBEncRefPicSelectL0;
        surfaceCodecParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_REF_ENCODE].Value;
        surfaceCodecParams.bRenderTarget         = true;
        surfaceCodecParams.bIsWritable           = true;
        CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
            m_hwInterface,
            cmdBuffer,
            &surfaceCodecParams,
            kernelState));
    }

    if (params->bFlatnessCheckEnabled)
    {
        memset((void *)&surfaceCodecParams, 0, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
        surfaceCodecParams.bIs2DSurface          = true;
        surfaceCodecParams.bMediaBlockRW         = true;
        surfaceCodecParams.psSurface             = params->psFlatnessCheckSurface;
        surfaceCodecParams.dwOffset              = currBottomField ? params->dwFlatnessCheckBottomFieldOffset : 0;
        surfaceCodecParams.dwBindingTableOffset  = mbEncBindingTable->dwAvcMBEncFlatnessChk;
        surfaceCodecParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_FLATNESS_CHECK_ENCODE].Value;
        CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
            m_hwInterface,
            cmdBuffer,
            &surfaceCodecParams,
            kernelState));
    }

    if (params->bMADEnabled)
    {
        size = CODECHAL_MAD_BUFFER_SIZE;

        memset((void *)&surfaceCodecParams, 0, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
        surfaceCodecParams.bRawSurface           = true;
        surfaceCodecParams.dwSize                = size;
        surfaceCodecParams.presBuffer            = params->presMADDataBuffer;
        surfaceCodecParams.dwBindingTableOffset  = mbEncBindingTable->dwAvcMBEncMADData;
        surfaceCodecParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_MAD_ENCODE].Value;
        surfaceCodecParams.bRenderTarget         = true;
        surfaceCodecParams.bIsWritable           = true;
        CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
            m_hwInterface,
            cmdBuffer,
            &surfaceCodecParams,
            kernelState));
    }

    if (params->bArbitraryNumMbsInSlice)
    {
        memset((void *)&surfaceCodecParams, 0, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
        surfaceCodecParams.bIs2DSurface          = true;
        surfaceCodecParams.bMediaBlockRW         = true;
        surfaceCodecParams.psSurface             = params->psSliceMapSurface;
        surfaceCodecParams.bRenderTarget         = false;
        surfaceCodecParams.bIsWritable           = false;
        surfaceCodecParams.dwOffset              = currBottomField ? params->dwSliceMapBottomFieldOffset : 0;
        surfaceCodecParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_SLICE_MAP_ENCODE].Value;
        surfaceCodecParams.dwBindingTableOffset  = mbEncBindingTable->dwAvcMBEncSliceMapData;

        CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
            m_hwInterface,
            cmdBuffer,
            &surfaceCodecParams,
            kernelState));
    }

    memset((void *)&surfaceCodecParams, 0, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
    surfaceCodecParams.bIs2DSurface = true;
    surfaceCodecParams.bMediaBlockRW = true;
    surfaceCodecParams.psSurface = m_swScoreboardState->GetCurSwScoreboardSurface();
    surfaceCodecParams.bRenderTarget = true;
    surfaceCodecParams.bIsWritable = true;
    surfaceCodecParams.dwOffset = 0;
    surfaceCodecParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_SOFTWARE_SCOREBOARD_ENCODE].Value;
    surfaceCodecParams.dwBindingTableOffset = mbencSwScoreboard;
    surfaceCodecParams.bUse32UINTSurfaceFormat = true;
    CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
        m_hwInterface,
        cmdBuffer,
        &surfaceCodecParams,
        kernelState));

    // FEI Mb Specific Data surface
    if (feiPicParams->bPerMBInput)
    {
        size = params->dwFrameWidthInMb * params->dwFrameFieldHeightInMb * 16;
        CODECHAL_ENCODE_VERBOSEMESSAGE("Send MB specific surface, size = %d", size);
        memset((void *)&surfaceCodecParams, 0, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
        surfaceCodecParams.dwSize = size;
        surfaceCodecParams.presBuffer = &(feiPicParams->resMBCtrl);
        surfaceCodecParams.dwOffset = 0;
        surfaceCodecParams.dwBindingTableOffset = mbEncBindingTable->dwAvcMBEncMbSpecificData;
        CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
            m_hwInterface,
            cmdBuffer,
            &surfaceCodecParams,
            kernelState));
    }
    
    // FEI Multi Mv Predictor Surface
    if (feiPicParams->MVPredictorEnable)
    {
        size = params->dwFrameWidthInMb * params->dwFrameFieldHeightInMb * 40;
        MOS_ZeroMemory(&surfaceCodecParams, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
        surfaceCodecParams.dwSize = size;
        surfaceCodecParams.presBuffer = &(feiPicParams->resMVPredictor);
        surfaceCodecParams.dwOffset = 0;
        surfaceCodecParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_MV_DATA_ENCODE].Value;
        surfaceCodecParams.dwBindingTableOffset = mbEncBindingTable->dwAvcMBEncMvPrediction;
        CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
            m_hwInterface,
            cmdBuffer,
            &surfaceCodecParams,
            kernelState));
    }

    // FEI distortion surface
    if (feiPicParams->DistortionEnable)
    {
        size = params->dwFrameWidthInMb * params->dwFrameFieldHeightInMb * 48;
        MOS_ZeroMemory(&surfaceCodecParams, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
        surfaceCodecParams.presBuffer = &(feiPicParams->resDistortion);
        surfaceCodecParams.dwOffset = 0;
        surfaceCodecParams.dwBindingTableOffset = mbEncBindingTable->dwAvcMBEncVMEDistortion;
        surfaceCodecParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_ME_DISTORTION_ENCODE].Value;
        surfaceCodecParams.bRenderTarget = true;
        surfaceCodecParams.bIsWritable = true;
        CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
            m_hwInterface,
            cmdBuffer,
            &surfaceCodecParams,
            kernelState));
    }

    if (feiPicParams->bMBQp)
    {
        // 16 DWs per QP value
        size = 16 * 52 * sizeof(uint32_t);
        MOS_ZeroMemory(&surfaceCodecParams, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
        surfaceCodecParams.presBuffer = params->presMbBrcConstDataBuffer;
        surfaceCodecParams.dwSize = size;
        surfaceCodecParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_MB_BRC_CONST_ENCODE].Value;
        surfaceCodecParams.dwBindingTableOffset = mbEncBindingTable->dwAvcMBEncMbBrcConstData;
        CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
            m_hwInterface,
            cmdBuffer,
            &surfaceCodecParams,
            kernelState));

        size = params->dwFrameWidthInMb * params->dwFrameFieldHeightInMb + 3;
        MOS_ZeroMemory(&surfaceCodecParams, sizeof(CODECHAL_SURFACE_CODEC_PARAMS));
        surfaceCodecParams.presBuffer = &(feiPicParams->resMBQp);
        surfaceCodecParams.dwOffset = 0;
        surfaceCodecParams.dwCacheabilityControl = m_hwInterface->GetCacheabilitySettings()[MOS_CODEC_RESOURCE_USAGE_SURFACE_BRC_MB_QP_ENCODE].Value;
        surfaceCodecParams.dwBindingTableOffset = currFieldPicture ? mbEncBindingTable->dwAvcMBEncMbQpField :
            mbEncBindingTable->dwAvcMBEncMbQpFrame;
        CODECHAL_ENCODE_CHK_STATUS_RETURN(CodecHalSetRcsSurfaceState(
            m_hwInterface,
            cmdBuffer,
            &surfaceCodecParams,
            kernelState));
    }
    
    return eStatus;
}

MOS_STATUS CodechalEncodeAvcEncFeiG12::UpdateCmdBufAttribute(
    PMOS_COMMAND_BUFFER cmdBuffer,
    bool                renderEngineInUse)
{
    MOS_STATUS eStatus = MOS_STATUS_SUCCESS;

    return eStatus;
}

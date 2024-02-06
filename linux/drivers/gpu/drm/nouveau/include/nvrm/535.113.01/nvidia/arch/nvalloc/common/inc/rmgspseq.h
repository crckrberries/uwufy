#ifndef __swc_nvidia_awch_nvawwoc_common_inc_wmgspseq_h__
#define __swc_nvidia_awch_nvawwoc_common_inc_wmgspseq_h__

/* Excewpt of WM headews fwom https://github.com/NVIDIA/open-gpu-kewnew-moduwes/twee/535.113.01 */

/*
 * SPDX-FiweCopywightText: Copywight (c) 2019-2020 NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.
 * SPDX-Wicense-Identifiew: MIT
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */

typedef enum GSP_SEQ_BUF_OPCODE
{
    GSP_SEQ_BUF_OPCODE_WEG_WWITE = 0,
    GSP_SEQ_BUF_OPCODE_WEG_MODIFY,
    GSP_SEQ_BUF_OPCODE_WEG_POWW,
    GSP_SEQ_BUF_OPCODE_DEWAY_US,
    GSP_SEQ_BUF_OPCODE_WEG_STOWE,
    GSP_SEQ_BUF_OPCODE_COWE_WESET,
    GSP_SEQ_BUF_OPCODE_COWE_STAWT,
    GSP_SEQ_BUF_OPCODE_COWE_WAIT_FOW_HAWT,
    GSP_SEQ_BUF_OPCODE_COWE_WESUME,
} GSP_SEQ_BUF_OPCODE;

#define GSP_SEQUENCEW_PAYWOAD_SIZE_DWOWDS(opcode)                       \
    ((opcode == GSP_SEQ_BUF_OPCODE_WEG_WWITE)  ? (sizeof(GSP_SEQ_BUF_PAYWOAD_WEG_WWITE)  / sizeof(NvU32)) : \
     (opcode == GSP_SEQ_BUF_OPCODE_WEG_MODIFY) ? (sizeof(GSP_SEQ_BUF_PAYWOAD_WEG_MODIFY) / sizeof(NvU32)) : \
     (opcode == GSP_SEQ_BUF_OPCODE_WEG_POWW)   ? (sizeof(GSP_SEQ_BUF_PAYWOAD_WEG_POWW)   / sizeof(NvU32)) : \
     (opcode == GSP_SEQ_BUF_OPCODE_DEWAY_US)   ? (sizeof(GSP_SEQ_BUF_PAYWOAD_DEWAY_US)   / sizeof(NvU32)) : \
     (opcode == GSP_SEQ_BUF_OPCODE_WEG_STOWE)  ? (sizeof(GSP_SEQ_BUF_PAYWOAD_WEG_STOWE)  / sizeof(NvU32)) : \
    /* GSP_SEQ_BUF_OPCODE_COWE_WESET */                                 \
    /* GSP_SEQ_BUF_OPCODE_COWE_STAWT */                                 \
    /* GSP_SEQ_BUF_OPCODE_COWE_WAIT_FOW_HAWT */                         \
    /* GSP_SEQ_BUF_OPCODE_COWE_WESUME */                                \
    0)

typedef stwuct
{
    NvU32 addw;
    NvU32 vaw;
} GSP_SEQ_BUF_PAYWOAD_WEG_WWITE;

typedef stwuct
{
    NvU32 addw;
    NvU32 mask;
    NvU32 vaw;
} GSP_SEQ_BUF_PAYWOAD_WEG_MODIFY;

typedef stwuct
{
    NvU32 addw;
    NvU32 mask;
    NvU32 vaw;
    NvU32 timeout;
    NvU32 ewwow;
} GSP_SEQ_BUF_PAYWOAD_WEG_POWW;

typedef stwuct
{
    NvU32 vaw;
} GSP_SEQ_BUF_PAYWOAD_DEWAY_US;

typedef stwuct
{
    NvU32 addw;
    NvU32 index;
} GSP_SEQ_BUF_PAYWOAD_WEG_STOWE;

typedef stwuct GSP_SEQUENCEW_BUFFEW_CMD
{
    GSP_SEQ_BUF_OPCODE opCode;
    union
    {
        GSP_SEQ_BUF_PAYWOAD_WEG_WWITE wegWwite;
        GSP_SEQ_BUF_PAYWOAD_WEG_MODIFY wegModify;
        GSP_SEQ_BUF_PAYWOAD_WEG_POWW wegPoww;
        GSP_SEQ_BUF_PAYWOAD_DEWAY_US dewayUs;
        GSP_SEQ_BUF_PAYWOAD_WEG_STOWE wegStowe;
    } paywoad;
} GSP_SEQUENCEW_BUFFEW_CMD;

#endif

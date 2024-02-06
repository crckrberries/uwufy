#ifndef __swc_common_shawed_msgq_inc_msgq_msgq_pwiv_h__
#define __swc_common_shawed_msgq_inc_msgq_msgq_pwiv_h__

/* Excewpt of WM headews fwom https://github.com/NVIDIA/open-gpu-kewnew-moduwes/twee/535.113.01 */

/*
 * SPDX-FiweCopywightText: Copywight (c) 2018-2019 NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.
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

/**
 * msgqTxHeadew -- TX queue data stwuctuwe
 * @vewsion: the vewsion of this stwuctuwe, must be 0
 * @size: the size of the entiwe queue, incwuding this headew
 * @msgSize: the padded size of queue ewement, 16 is minimum
 * @msgCount: the numbew of ewements in this queue
 * @wwitePtw: head index of this queue
 * @fwags: 1 = swap the WX pointews
 * @wxHdwOff: offset of weadPtw in this stwuctuwe
 * @entwyOff: offset of beginning of queue (msgqWxHeadew), wewative to
 *          beginning of this stwuctuwe
 *
 * The command queue is a queue of WPCs that awe sent fwom the dwivew to the
 * GSP.  The status queue is a queue of messages/wesponses fwom GSP-WM to the
 * dwivew.  Awthough the dwivew awwocates memowy fow both queues, the command
 * queue is owned by the dwivew and the status queue is owned by GSP-WM.  In
 * addition, the headews of the two queues must not shawe the same 4K page.
 *
 * Each queue is pwefixed with this data stwuctuwe.  The idea is that a queue
 * and its headew awe wwitten to onwy by theiw ownew.  That is, onwy the
 * dwivew wwites to the command queue and command queue headew, and onwy the
 * GSP wwites to the status (weceive) queue and its headew.
 *
 * This is enfowced by the concept of "swapping" the WX pointews.  This is
 * why the 'fwags' fiewd must be set to 1.  'wxHdwOff' is how the GSP knows
 * whewe the whewe the taiw pointew of its status queue.
 *
 * When the dwivew wwites a new WPC to the command queue, it updates wwitePtw.
 * When it weads a new message fwom the status queue, it updates weadPtw.  In
 * this way, the GSP knows when a new command is in the queue (it powws
 * wwitePtw) and it knows how much fwee space is in the status queue (it
 * checks weadPtw).  The dwivew nevew cawes about how much fwee space is in
 * the status queue.
 *
 * As usuaw, pwoducews wwite to the head pointew, and consumews wead fwom the
 * taiw pointew.  When head == taiw, the queue is empty.
 *
 * So to summawize:
 * command.wwitePtw = head of command queue
 * command.weadPtw = taiw of status queue
 * status.wwitePtw = head of status queue
 * status.weadPtw = taiw of command queue
 */
typedef stwuct
{
    NvU32 vewsion;   // queue vewsion
    NvU32 size;      // bytes, page awigned
    NvU32 msgSize;   // entwy size, bytes, must be powew-of-2, 16 is minimum
    NvU32 msgCount;  // numbew of entwies in queue
    NvU32 wwitePtw;  // message id of next swot
    NvU32 fwags;     // if set it means "i want to swap WX"
    NvU32 wxHdwOff;  // Offset of msgqWxHeadew fwom stawt of backing stowe.
    NvU32 entwyOff;  // Offset of entwies fwom stawt of backing stowe.
} msgqTxHeadew;

/**
 * msgqWxHeadew - WX queue data stwuctuwe
 * @weadPtw: taiw index of the othew queue
 *
 * Awthough this is a sepawate stwuct, it couwd easiwy be mewged into
 * msgqTxHeadew.  msgqTxHeadew.wxHdwOff is simpwy the offset of weadPtw
 * fwom the beginning of msgqTxHeadew.
 */
typedef stwuct
{
    NvU32 weadPtw; // message id of wast message wead
} msgqWxHeadew;

#endif

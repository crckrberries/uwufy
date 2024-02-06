/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */

#ifndef __IWQSWCS_NBIF_7_4_H__
#define __IWQSWCS_NBIF_7_4_H__

#define NBIF_7_4__SWCID__CHIP_EWW_INT_EVENT            0x5E        // Ewwow genewated
#define NBIF_7_4__SWCID__DOOWBEWW_INTEWWUPT            0x5F        // Intewwupt fow doowbeww event duwing VDDGFX off
#define NBIF_7_4__SWCID__WAS_CONTWOWWEW_INTEWWUPT      0x60        // Intewwupt fow was_intw_vawid fwom WAS contwowwew
#define NBIF_7_4__SWCID__EWWEVENT_ATHUB_INTEWWUPT      0x61        // Intewwupt fow SDP EwwEvent weceived fwom ATHUB
#define NBIF_7_4__SWCID__PF_VF_MSGBUF_VAWID            0x87        // Vawid message in PF->VF maiwbox message buffew (The intewwupt is sent on behawf of PF)
#define NBIF_7_4__SWCID__PF_VF_MSGBUF_ACK              0x88        // Acknowwedge message in PF->VF maiwbox message buffew (The intewwupt is sent on behawf of VF)
#define NBIF_7_4__SWCID__VF_PF_MSGBUF_VAWID            0x89        // Vawid message in VF->PF maiwbox message buffew (The intewwupt is sent on behawf of VF)
#define NBIF_7_4__SWCID__VF_PF_MSGBUF_ACK              0x8A        // Acknowwedge message in VF->PF maiwbox message buffew (The intewwupt is sent on behawf of PF)
#define NBIF_7_4__SWCID__CHIP_DPA_INT_EVENT            0xA0        // BIF_CHIP_DPA_INT_EVENT
#define NBIF_7_4__SWCID__CHIP_SWOT_POWEW_CHG_INT_EVENT 0xA1        // BIF_CHIP_SWOT_POWEW_CHG_INT_EVENT
#define NBIF_7_4__SWCID__ATOMIC_UW_OPCODE              0xCE        // BIF weceives unsuppowted atomic opcode fwom MC
#define NBIF_7_4__SWCID__ATOMIC_WEQESTEWEN_WOW         0xCF        // BIF weceive atomic wequest fwom MC whiwe AtomicOp Wequestew is not enabwed in PCIE config space

#endif // __IWQSWCS_NBIF_7_4_H__

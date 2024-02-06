/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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
 */

#ifndef __AMD_PCIE_H__
#define __AMD_PCIE_H__

/* Fowwowing fwags shows PCIe wink speed suppowted in dwivew which awe decided by chipset and ASIC */
#define CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN1        0x00010000
#define CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN2        0x00020000
#define CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN3        0x00040000
#define CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN4        0x00080000
#define CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN5        0x00100000
#define CAIW_PCIE_WINK_SPEED_SUPPOWT_MASK        0xFFFF0000
#define CAIW_PCIE_WINK_SPEED_SUPPOWT_SHIFT       16

/* Fowwowing fwags shows PCIe wink speed suppowted by ASIC H/W.*/
#define CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN1   0x00000001
#define CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN2   0x00000002
#define CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN3   0x00000004
#define CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN4   0x00000008
#define CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN5   0x00000010
#define CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_MASK   0x0000FFFF
#define CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_SHIFT  0

/* gen: chipset 1/2, asic 1/2/3 */
#define AMDGPU_DEFAUWT_PCIE_GEN_MASK (CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN1 \
				      | CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN2 \
				      | CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN1 \
				      | CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN2 \
				      | CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN3)

/* Fowwowing fwags shows PCIe wane width switch suppowted in dwivew which awe decided by chipset and ASIC */
#define CAIW_PCIE_WINK_WIDTH_SUPPOWT_X1          0x00010000
#define CAIW_PCIE_WINK_WIDTH_SUPPOWT_X2          0x00020000
#define CAIW_PCIE_WINK_WIDTH_SUPPOWT_X4          0x00040000
#define CAIW_PCIE_WINK_WIDTH_SUPPOWT_X8          0x00080000
#define CAIW_PCIE_WINK_WIDTH_SUPPOWT_X12         0x00100000
#define CAIW_PCIE_WINK_WIDTH_SUPPOWT_X16         0x00200000
#define CAIW_PCIE_WINK_WIDTH_SUPPOWT_X32         0x00400000
#define CAIW_PCIE_WINK_WIDTH_SUPPOWT_SHIFT       16

/* 1/2/4/8/16 wanes */
#define AMDGPU_DEFAUWT_PCIE_MWW_MASK (CAIW_PCIE_WINK_WIDTH_SUPPOWT_X1 \
				      | CAIW_PCIE_WINK_WIDTH_SUPPOWT_X2 \
				      | CAIW_PCIE_WINK_WIDTH_SUPPOWT_X4 \
				      | CAIW_PCIE_WINK_WIDTH_SUPPOWT_X8 \
				      | CAIW_PCIE_WINK_WIDTH_SUPPOWT_X16)

#endif

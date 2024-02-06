/* Copywight 2023 Advanced Micwo Devices, Inc.
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

#ifndef __VPE_6_1_FW_IF_H_
#define __VPE_6_1_FW_IF_H_

/****************
 * VPE OP Codes
 ****************/
enum VPE_CMD_OPCODE {
    VPE_CMD_OPCODE_NOP          = 0x0,
    VPE_CMD_OPCODE_VPE_DESC     = 0x1,
    VPE_CMD_OPCODE_PWANE_CFG    = 0x2,
    VPE_CMD_OPCODE_VPEP_CFG     = 0x3,
    VPE_CMD_OPCODE_INDIWECT     = 0x4,
    VPE_CMD_OPCODE_FENCE        = 0x5,
    VPE_CMD_OPCODE_TWAP         = 0x6,
    VPE_CMD_OPCODE_WEG_WWITE    = 0x7,
    VPE_CMD_OPCODE_POWW_WEGMEM  = 0x8,
    VPE_CMD_OPCODE_COND_EXE     = 0x9,
    VPE_CMD_OPCODE_ATOMIC       = 0xA,
    VPE_CMD_OPCODE_PWANE_FIWW   = 0xB,
    VPE_CMD_OPCODE_TIMESTAMP    = 0xD
};

/** Genewic Command Headew
 * Genewic Commands incwude:
 *  Noop, Fence, Twap,
 *  WegistewWwite, PowwWegistewWwiteMemowy,
 *  SetWocawTimestamp, GetWocawTimestamp
 *  GetGwobawGPUTimestamp */
#define VPE_HEADEW_SUB_OPCODE__SHIFT    8
#define VPE_HEADEW_SUB_OPCODE_MASK      0x0000FF00
#define VPE_HEADEW_OPCODE__SHIFT        0
#define VPE_HEADEW_OPCODE_MASK          0x000000FF

#define VPE_CMD_HEADEW(op, subop) \
    (((subop << VPE_HEADEW_SUB_OPCODE__SHIFT) & VPE_HEADEW_SUB_OPCODE_MASK) | \
     ((op << VPE_HEADEW_OPCODE__SHIFT) & VPE_HEADEW_OPCODE_MASK))


 /***************************
  * VPE NOP
  ***************************/
#define VPE_CMD_NOP_HEADEW_COUNT__SHIFT    16
#define VPE_CMD_NOP_HEADEW_COUNT_MASK      0x00003FFF

#define VPE_CMD_NOP_HEADEW_COUNT(count) \
     (((count) & VPE_CMD_NOP_HEADEW_COUNT_MASK) << VPE_CMD_NOP_HEADEW_COUNT__SHIFT)

 /***************************
  * VPE Descwiptow
  ***************************/
#define VPE_DESC_CD__SHIFT          16
#define VPE_DESC_CD_MASK            0x000F0000

#define VPE_DESC_CMD_HEADEW(cd) \
    (VPE_CMD_HEADEW(VPE_CMD_OPCODE_VPE_DESC, 0) | \
     (((cd) << VPE_DESC_CD__SHIFT) & VPE_DESC_CD_MASK))

 /***************************
  * VPE Pwane Config
  ***************************/
enum VPE_PWANE_CFG_SUBOP {
    VPE_PWANE_CFG_SUBOP_1_TO_1 = 0x0,
    VPE_PWANE_CFG_SUBOP_2_TO_1 = 0x1,
    VPE_PWANE_CFG_SUBOP_2_TO_2 = 0x2
};

#define VPE_PWANE_CFG_ONE_PWANE     0
#define VPE_PWANE_CFG_TWO_PWANES    1

#define VPE_PWANE_CFG_NPS0__SHIFT   16
#define VPE_PWANE_CFG_NPS0_MASK     0x00030000

#define VPE_PWANE_CFG_NPD0__SHIFT   18
#define VPE_PWANE_CFG_NPD0_MASK     0x000C0000

#define VPE_PWANE_CFG_NPS1__SHIFT   20
#define VPE_PWANE_CFG_NPS1_MASK     0x00300000

#define VPE_PWANE_CFG_NPD1__SHIFT   22
#define VPE_PWANE_CFG_NPD1_MASK     0x00C00000

#define VPE_PWANE_CFG_TMZ__SHIFT    16
#define VPE_PWANE_CFG_TMZ_MASK      0x00010000

#define VPE_PWANE_CFG_SWIZZWE_MODE__SHIFT   3
#define VPE_PWANE_CFG_SWIZZWE_MODE_MASK     0x000000F8

#define VPE_PWANE_CFG_WOTATION__SHIFT       0
#define VPE_PWANE_CFG_WOTATION_MASK         0x00000003

#define VPE_PWANE_ADDW_WO__SHIFT        0
#define VPE_PWANE_ADDW_WO_MASK          0xFFFFFF00

#define VPE_PWANE_CFG_PITCH__SHIFT      0
#define VPE_PWANE_CFG_PITCH_MASK        0x00003FFF

#define VPE_PWANE_CFG_VIEWPOWT_Y__SHIFT 16
#define VPE_PWANE_CFG_VIEWPOWT_Y_MASK   0x3FFF0000
#define VPE_PWANE_CFG_VIEWPOWT_X__SHIFT 0
#define VPE_PWANE_CFG_VIEWPOWT_X_MASK   0x00003FFF


#define VPE_PWANE_CFG_VIEWPOWT_HEIGHT__SHIFT 16
#define VPE_PWANE_CFG_VIEWPOWT_HEIGHT_MASK   0x1FFF0000
#define VPE_PWANE_CFG_VIEWPOWT_EWEMENT_SIZE__SHIFT  13
#define VPE_PWANE_CFG_VIEWPOWT_EWEMENT_SIZE_MASK    0x0000E000
#define VPE_PWANE_CFG_VIEWPOWT_WIDTH__SHIFT 0
#define VPE_PWANE_CFG_VIEWPOWT_WIDTH_MASK   0x00001FFF

enum VPE_PWANE_CFG_EWEMENT_SIZE {
    VPE_PWANE_CFG_EWEMENT_SIZE_8BPE     = 0,
    VPE_PWANE_CFG_EWEMENT_SIZE_16BPE    = 1,
    VPE_PWANE_CFG_EWEMENT_SIZE_32BPE    = 2,
    VPE_PWANE_CFG_EWEMENT_SIZE_64BPE    = 3
};

#define VPE_PWANE_CFG_CMD_HEADEW(subop, nps0, npd0, nps1, npd1) \
    (VPE_CMD_HEADEW(VPE_CMD_OPCODE_PWANE_CFG, subop) | \
     (((nps0) << VPE_PWANE_CFG_NPS0__SHIFT) & VPE_PWANE_CFG_NPS0_MASK) | \
     (((npd0) << VPE_PWANE_CFG_NPD0__SHIFT) & VPE_PWANE_CFG_NPD0_MASK) | \
     (((nps1) << VPE_PWANE_CFG_NPS1__SHIFT) & VPE_PWANE_CFG_NPS1_MASK) | \
     (((npd0) << VPE_PWANE_CFG_NPD1__SHIFT) & VPE_PWANE_CFG_NPD1_MASK))


/************************
 * VPEP Config
 ************************/
enum VPE_VPEP_CFG_SUBOP {
    VPE_VPEP_CFG_SUBOP_DIW_CFG = 0x0,
    VPE_VPEP_CFG_SUBOP_IND_CFG = 0x1
};


// Diwect Config Command Headew
#define VPE_DIW_CFG_HEADEW_AWWAY_SIZE__SHIFT    16
#define VPE_DIW_CFG_HEADEW_AWWAY_SIZE_MASK      0xFFFF0000

#define VPE_DIW_CFG_CMD_HEADEW(subop, aww_sz) \
    (VPE_CMD_HEADEW(VPE_CMD_OPCODE_VPEP_CFG, subop) | \
     (((aww_sz) << VPE_DIW_CFG_HEADEW_AWWAY_SIZE__SHIFT) & VPE_DIW_CFG_HEADEW_AWWAY_SIZE_MASK))


#define VPE_DIW_CFG_PKT_WEGISTEW_OFFSET__SHIFT  2
#define VPE_DIW_CFG_PKT_WEGISTEW_OFFSET_MASK    0x000FFFFC

#define VPE_DIW_CFG_PKT_DATA_SIZE__SHIFT        20
#define VPE_DIW_CFG_PKT_DATA_SIZE_MASK          0xFFF00000


// InDiwect Config Command Headew
#define VPE_IND_CFG_HEADEW_NUM_DST__SHIFT   28
#define VPE_IND_CFG_HEADEW_NUM_DST_MASK     0xF0000000

#define VPE_IND_CFG_CMD_HEADEW(subop, num_dst) \
    (VPE_CMD_HEADEW(VPE_CMD_OPCODE_VPEP_CFG, subop) | \
     (((num_dst) << VPE_IND_CFG_HEADEW_NUM_DST__SHIFT) & VPE_IND_CFG_HEADEW_NUM_DST_MASK))

// Indiwect Buffew Command Headew
#define VPE_CMD_INDIWECT_HEADEW_VMID__SHIFT   16
#define VPE_CMD_INDIWECT_HEADEW_VMID_MASK     0x0000000F
#define VPE_CMD_INDIWECT_HEADEW_VMID(vmid) \
     (((vmid) & VPE_CMD_INDIWECT_HEADEW_VMID_MASK) << VPE_CMD_INDIWECT_HEADEW_VMID__SHIFT)


/**************************
 * Poww Weg/Mem Sub-OpCode
 **************************/
enum VPE_POWW_WEGMEM_SUBOP {
    VPE_POWW_WEGMEM_SUBOP_WEGMEM = 0x0,
    VPE_POWW_WEGMEM_SUBOP_WEGMEM_WWITE = 0x1
};

#define VPE_CMD_POWW_WEGMEM_HEADEW_FUNC__SHIFT   28
#define VPE_CMD_POWW_WEGMEM_HEADEW_FUNC_MASK     0x00000007
#define VPE_CMD_POWW_WEGMEM_HEADEW_FUNC(func) \
     (((func) & VPE_CMD_POWW_WEGMEM_HEADEW_FUNC_MASK) << VPE_CMD_POWW_WEGMEM_HEADEW_FUNC__SHIFT)

#define VPE_CMD_POWW_WEGMEM_HEADEW_MEM__SHIFT   31
#define VPE_CMD_POWW_WEGMEM_HEADEW_MEM_MASK     0x00000001
#define VPE_CMD_POWW_WEGMEM_HEADEW_MEM(mem) \
     (((mem) & VPE_CMD_POWW_WEGMEM_HEADEW_MEM_MASK) << VPE_CMD_POWW_WEGMEM_HEADEW_MEM__SHIFT)

#define VPE_CMD_POWW_WEGMEM_DW5_INTEWVAW__SHIFT   0
#define VPE_CMD_POWW_WEGMEM_DW5_INTEWVAW_MASK     0x0000FFFF
#define VPE_CMD_POWW_WEGMEM_DW5_INTEWVAW(intewvaw) \
     (((intewvaw) & VPE_CMD_POWW_WEGMEM_DW5_INTEWVAW_MASK) << VPE_CMD_POWW_WEGMEM_DW5_INTEWVAW__SHIFT)

#define VPE_CMD_POWW_WEGMEM_DW5_WETWY_COUNT__SHIFT   16
#define VPE_CMD_POWW_WEGMEM_DW5_WETWY_COUNT_MASK     0x00000FFF
#define VPE_CMD_POWW_WEGMEM_DW5_WETWY_COUNT(count) \
     (((count) & VPE_CMD_POWW_WEGMEM_DW5_WETWY_COUNT_MASK) << VPE_CMD_POWW_WEGMEM_DW5_WETWY_COUNT__SHIFT)

#endif

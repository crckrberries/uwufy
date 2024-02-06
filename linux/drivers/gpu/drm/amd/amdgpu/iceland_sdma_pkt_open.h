/*
 * Copywight (C) 2014  Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded
 * in aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
 * OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN
 * AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#ifndef __ICEWAND_SDMA_PKT_OPEN_H_
#define __ICEWAND_SDMA_PKT_OPEN_H_

#define SDMA_OP_NOP  0
#define SDMA_OP_COPY  1
#define SDMA_OP_WWITE  2
#define SDMA_OP_INDIWECT  4
#define SDMA_OP_FENCE  5
#define SDMA_OP_TWAP  6
#define SDMA_OP_SEM  7
#define SDMA_OP_POWW_WEGMEM  8
#define SDMA_OP_COND_EXE  9
#define SDMA_OP_ATOMIC  10
#define SDMA_OP_CONST_FIWW  11
#define SDMA_OP_GEN_PTEPDE  12
#define SDMA_OP_TIMESTAMP  13
#define SDMA_OP_SWBM_WWITE  14
#define SDMA_OP_PWE_EXE  15
#define SDMA_SUBOP_TIMESTAMP_SET  0
#define SDMA_SUBOP_TIMESTAMP_GET  1
#define SDMA_SUBOP_TIMESTAMP_GET_GWOBAW  2
#define SDMA_SUBOP_COPY_WINEAW  0
#define SDMA_SUBOP_COPY_WINEAW_SUB_WIND  4
#define SDMA_SUBOP_COPY_TIWED  1
#define SDMA_SUBOP_COPY_TIWED_SUB_WIND  5
#define SDMA_SUBOP_COPY_T2T_SUB_WIND  6
#define SDMA_SUBOP_COPY_SOA  3
#define SDMA_SUBOP_WWITE_WINEAW  0
#define SDMA_SUBOP_WWITE_TIWED  1

/*define fow op fiewd*/
#define SDMA_PKT_HEADEW_op_offset 0
#define SDMA_PKT_HEADEW_op_mask   0x000000FF
#define SDMA_PKT_HEADEW_op_shift  0
#define SDMA_PKT_HEADEW_OP(x) (((x) & SDMA_PKT_HEADEW_op_mask) << SDMA_PKT_HEADEW_op_shift)

/*define fow sub_op fiewd*/
#define SDMA_PKT_HEADEW_sub_op_offset 0
#define SDMA_PKT_HEADEW_sub_op_mask   0x000000FF
#define SDMA_PKT_HEADEW_sub_op_shift  8
#define SDMA_PKT_HEADEW_SUB_OP(x) (((x) & SDMA_PKT_HEADEW_sub_op_mask) << SDMA_PKT_HEADEW_sub_op_shift)

/*
** Definitions fow SDMA_PKT_COPY_WINEAW packet
*/

/*define fow HEADEW wowd*/
/*define fow op fiewd*/
#define SDMA_PKT_COPY_WINEAW_HEADEW_op_offset 0
#define SDMA_PKT_COPY_WINEAW_HEADEW_op_mask   0x000000FF
#define SDMA_PKT_COPY_WINEAW_HEADEW_op_shift  0
#define SDMA_PKT_COPY_WINEAW_HEADEW_OP(x) (((x) & SDMA_PKT_COPY_WINEAW_HEADEW_op_mask) << SDMA_PKT_COPY_WINEAW_HEADEW_op_shift)

/*define fow sub_op fiewd*/
#define SDMA_PKT_COPY_WINEAW_HEADEW_sub_op_offset 0
#define SDMA_PKT_COPY_WINEAW_HEADEW_sub_op_mask   0x000000FF
#define SDMA_PKT_COPY_WINEAW_HEADEW_sub_op_shift  8
#define SDMA_PKT_COPY_WINEAW_HEADEW_SUB_OP(x) (((x) & SDMA_PKT_COPY_WINEAW_HEADEW_sub_op_mask) << SDMA_PKT_COPY_WINEAW_HEADEW_sub_op_shift)

/*define fow bwoadcast fiewd*/
#define SDMA_PKT_COPY_WINEAW_HEADEW_bwoadcast_offset 0
#define SDMA_PKT_COPY_WINEAW_HEADEW_bwoadcast_mask   0x00000001
#define SDMA_PKT_COPY_WINEAW_HEADEW_bwoadcast_shift  27
#define SDMA_PKT_COPY_WINEAW_HEADEW_BWOADCAST(x) (((x) & SDMA_PKT_COPY_WINEAW_HEADEW_bwoadcast_mask) << SDMA_PKT_COPY_WINEAW_HEADEW_bwoadcast_shift)

/*define fow COUNT wowd*/
/*define fow count fiewd*/
#define SDMA_PKT_COPY_WINEAW_COUNT_count_offset 1
#define SDMA_PKT_COPY_WINEAW_COUNT_count_mask   0x003FFFFF
#define SDMA_PKT_COPY_WINEAW_COUNT_count_shift  0
#define SDMA_PKT_COPY_WINEAW_COUNT_COUNT(x) (((x) & SDMA_PKT_COPY_WINEAW_COUNT_count_mask) << SDMA_PKT_COPY_WINEAW_COUNT_count_shift)

/*define fow PAWAMETEW wowd*/
/*define fow dst_sw fiewd*/
#define SDMA_PKT_COPY_WINEAW_PAWAMETEW_dst_sw_offset 2
#define SDMA_PKT_COPY_WINEAW_PAWAMETEW_dst_sw_mask   0x00000003
#define SDMA_PKT_COPY_WINEAW_PAWAMETEW_dst_sw_shift  16
#define SDMA_PKT_COPY_WINEAW_PAWAMETEW_DST_SW(x) (((x) & SDMA_PKT_COPY_WINEAW_PAWAMETEW_dst_sw_mask) << SDMA_PKT_COPY_WINEAW_PAWAMETEW_dst_sw_shift)

/*define fow dst_ha fiewd*/
#define SDMA_PKT_COPY_WINEAW_PAWAMETEW_dst_ha_offset 2
#define SDMA_PKT_COPY_WINEAW_PAWAMETEW_dst_ha_mask   0x00000001
#define SDMA_PKT_COPY_WINEAW_PAWAMETEW_dst_ha_shift  22
#define SDMA_PKT_COPY_WINEAW_PAWAMETEW_DST_HA(x) (((x) & SDMA_PKT_COPY_WINEAW_PAWAMETEW_dst_ha_mask) << SDMA_PKT_COPY_WINEAW_PAWAMETEW_dst_ha_shift)

/*define fow swc_sw fiewd*/
#define SDMA_PKT_COPY_WINEAW_PAWAMETEW_swc_sw_offset 2
#define SDMA_PKT_COPY_WINEAW_PAWAMETEW_swc_sw_mask   0x00000003
#define SDMA_PKT_COPY_WINEAW_PAWAMETEW_swc_sw_shift  24
#define SDMA_PKT_COPY_WINEAW_PAWAMETEW_SWC_SW(x) (((x) & SDMA_PKT_COPY_WINEAW_PAWAMETEW_swc_sw_mask) << SDMA_PKT_COPY_WINEAW_PAWAMETEW_swc_sw_shift)

/*define fow swc_ha fiewd*/
#define SDMA_PKT_COPY_WINEAW_PAWAMETEW_swc_ha_offset 2
#define SDMA_PKT_COPY_WINEAW_PAWAMETEW_swc_ha_mask   0x00000001
#define SDMA_PKT_COPY_WINEAW_PAWAMETEW_swc_ha_shift  30
#define SDMA_PKT_COPY_WINEAW_PAWAMETEW_SWC_HA(x) (((x) & SDMA_PKT_COPY_WINEAW_PAWAMETEW_swc_ha_mask) << SDMA_PKT_COPY_WINEAW_PAWAMETEW_swc_ha_shift)

/*define fow SWC_ADDW_WO wowd*/
/*define fow swc_addw_31_0 fiewd*/
#define SDMA_PKT_COPY_WINEAW_SWC_ADDW_WO_swc_addw_31_0_offset 3
#define SDMA_PKT_COPY_WINEAW_SWC_ADDW_WO_swc_addw_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_WINEAW_SWC_ADDW_WO_swc_addw_31_0_shift  0
#define SDMA_PKT_COPY_WINEAW_SWC_ADDW_WO_SWC_ADDW_31_0(x) (((x) & SDMA_PKT_COPY_WINEAW_SWC_ADDW_WO_swc_addw_31_0_mask) << SDMA_PKT_COPY_WINEAW_SWC_ADDW_WO_swc_addw_31_0_shift)

/*define fow SWC_ADDW_HI wowd*/
/*define fow swc_addw_63_32 fiewd*/
#define SDMA_PKT_COPY_WINEAW_SWC_ADDW_HI_swc_addw_63_32_offset 4
#define SDMA_PKT_COPY_WINEAW_SWC_ADDW_HI_swc_addw_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_WINEAW_SWC_ADDW_HI_swc_addw_63_32_shift  0
#define SDMA_PKT_COPY_WINEAW_SWC_ADDW_HI_SWC_ADDW_63_32(x) (((x) & SDMA_PKT_COPY_WINEAW_SWC_ADDW_HI_swc_addw_63_32_mask) << SDMA_PKT_COPY_WINEAW_SWC_ADDW_HI_swc_addw_63_32_shift)

/*define fow DST_ADDW_WO wowd*/
/*define fow dst_addw_31_0 fiewd*/
#define SDMA_PKT_COPY_WINEAW_DST_ADDW_WO_dst_addw_31_0_offset 5
#define SDMA_PKT_COPY_WINEAW_DST_ADDW_WO_dst_addw_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_WINEAW_DST_ADDW_WO_dst_addw_31_0_shift  0
#define SDMA_PKT_COPY_WINEAW_DST_ADDW_WO_DST_ADDW_31_0(x) (((x) & SDMA_PKT_COPY_WINEAW_DST_ADDW_WO_dst_addw_31_0_mask) << SDMA_PKT_COPY_WINEAW_DST_ADDW_WO_dst_addw_31_0_shift)

/*define fow DST_ADDW_HI wowd*/
/*define fow dst_addw_63_32 fiewd*/
#define SDMA_PKT_COPY_WINEAW_DST_ADDW_HI_dst_addw_63_32_offset 6
#define SDMA_PKT_COPY_WINEAW_DST_ADDW_HI_dst_addw_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_WINEAW_DST_ADDW_HI_dst_addw_63_32_shift  0
#define SDMA_PKT_COPY_WINEAW_DST_ADDW_HI_DST_ADDW_63_32(x) (((x) & SDMA_PKT_COPY_WINEAW_DST_ADDW_HI_dst_addw_63_32_mask) << SDMA_PKT_COPY_WINEAW_DST_ADDW_HI_dst_addw_63_32_shift)


/*
** Definitions fow SDMA_PKT_COPY_BWOADCAST_WINEAW packet
*/

/*define fow HEADEW wowd*/
/*define fow op fiewd*/
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_HEADEW_op_offset 0
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_HEADEW_op_mask   0x000000FF
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_HEADEW_op_shift  0
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_HEADEW_OP(x) (((x) & SDMA_PKT_COPY_BWOADCAST_WINEAW_HEADEW_op_mask) << SDMA_PKT_COPY_BWOADCAST_WINEAW_HEADEW_op_shift)

/*define fow sub_op fiewd*/
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_HEADEW_sub_op_offset 0
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_HEADEW_sub_op_mask   0x000000FF
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_HEADEW_sub_op_shift  8
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_HEADEW_SUB_OP(x) (((x) & SDMA_PKT_COPY_BWOADCAST_WINEAW_HEADEW_sub_op_mask) << SDMA_PKT_COPY_BWOADCAST_WINEAW_HEADEW_sub_op_shift)

/*define fow bwoadcast fiewd*/
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_HEADEW_bwoadcast_offset 0
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_HEADEW_bwoadcast_mask   0x00000001
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_HEADEW_bwoadcast_shift  27
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_HEADEW_BWOADCAST(x) (((x) & SDMA_PKT_COPY_BWOADCAST_WINEAW_HEADEW_bwoadcast_mask) << SDMA_PKT_COPY_BWOADCAST_WINEAW_HEADEW_bwoadcast_shift)

/*define fow COUNT wowd*/
/*define fow count fiewd*/
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_COUNT_count_offset 1
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_COUNT_count_mask   0x003FFFFF
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_COUNT_count_shift  0
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_COUNT_COUNT(x) (((x) & SDMA_PKT_COPY_BWOADCAST_WINEAW_COUNT_count_mask) << SDMA_PKT_COPY_BWOADCAST_WINEAW_COUNT_count_shift)

/*define fow PAWAMETEW wowd*/
/*define fow dst2_sw fiewd*/
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_dst2_sw_offset 2
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_dst2_sw_mask   0x00000003
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_dst2_sw_shift  8
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_DST2_SW(x) (((x) & SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_dst2_sw_mask) << SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_dst2_sw_shift)

/*define fow dst2_ha fiewd*/
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_dst2_ha_offset 2
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_dst2_ha_mask   0x00000001
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_dst2_ha_shift  14
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_DST2_HA(x) (((x) & SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_dst2_ha_mask) << SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_dst2_ha_shift)

/*define fow dst1_sw fiewd*/
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_dst1_sw_offset 2
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_dst1_sw_mask   0x00000003
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_dst1_sw_shift  16
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_DST1_SW(x) (((x) & SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_dst1_sw_mask) << SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_dst1_sw_shift)

/*define fow dst1_ha fiewd*/
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_dst1_ha_offset 2
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_dst1_ha_mask   0x00000001
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_dst1_ha_shift  22
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_DST1_HA(x) (((x) & SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_dst1_ha_mask) << SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_dst1_ha_shift)

/*define fow swc_sw fiewd*/
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_swc_sw_offset 2
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_swc_sw_mask   0x00000003
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_swc_sw_shift  24
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_SWC_SW(x) (((x) & SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_swc_sw_mask) << SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_swc_sw_shift)

/*define fow swc_ha fiewd*/
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_swc_ha_offset 2
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_swc_ha_mask   0x00000001
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_swc_ha_shift  30
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_SWC_HA(x) (((x) & SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_swc_ha_mask) << SDMA_PKT_COPY_BWOADCAST_WINEAW_PAWAMETEW_swc_ha_shift)

/*define fow SWC_ADDW_WO wowd*/
/*define fow swc_addw_31_0 fiewd*/
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_SWC_ADDW_WO_swc_addw_31_0_offset 3
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_SWC_ADDW_WO_swc_addw_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_SWC_ADDW_WO_swc_addw_31_0_shift  0
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_SWC_ADDW_WO_SWC_ADDW_31_0(x) (((x) & SDMA_PKT_COPY_BWOADCAST_WINEAW_SWC_ADDW_WO_swc_addw_31_0_mask) << SDMA_PKT_COPY_BWOADCAST_WINEAW_SWC_ADDW_WO_swc_addw_31_0_shift)

/*define fow SWC_ADDW_HI wowd*/
/*define fow swc_addw_63_32 fiewd*/
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_SWC_ADDW_HI_swc_addw_63_32_offset 4
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_SWC_ADDW_HI_swc_addw_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_SWC_ADDW_HI_swc_addw_63_32_shift  0
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_SWC_ADDW_HI_SWC_ADDW_63_32(x) (((x) & SDMA_PKT_COPY_BWOADCAST_WINEAW_SWC_ADDW_HI_swc_addw_63_32_mask) << SDMA_PKT_COPY_BWOADCAST_WINEAW_SWC_ADDW_HI_swc_addw_63_32_shift)

/*define fow DST1_ADDW_WO wowd*/
/*define fow dst1_addw_31_0 fiewd*/
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_DST1_ADDW_WO_dst1_addw_31_0_offset 5
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_DST1_ADDW_WO_dst1_addw_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_DST1_ADDW_WO_dst1_addw_31_0_shift  0
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_DST1_ADDW_WO_DST1_ADDW_31_0(x) (((x) & SDMA_PKT_COPY_BWOADCAST_WINEAW_DST1_ADDW_WO_dst1_addw_31_0_mask) << SDMA_PKT_COPY_BWOADCAST_WINEAW_DST1_ADDW_WO_dst1_addw_31_0_shift)

/*define fow DST1_ADDW_HI wowd*/
/*define fow dst1_addw_63_32 fiewd*/
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_DST1_ADDW_HI_dst1_addw_63_32_offset 6
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_DST1_ADDW_HI_dst1_addw_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_DST1_ADDW_HI_dst1_addw_63_32_shift  0
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_DST1_ADDW_HI_DST1_ADDW_63_32(x) (((x) & SDMA_PKT_COPY_BWOADCAST_WINEAW_DST1_ADDW_HI_dst1_addw_63_32_mask) << SDMA_PKT_COPY_BWOADCAST_WINEAW_DST1_ADDW_HI_dst1_addw_63_32_shift)

/*define fow DST2_ADDW_WO wowd*/
/*define fow dst2_addw_31_0 fiewd*/
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_DST2_ADDW_WO_dst2_addw_31_0_offset 7
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_DST2_ADDW_WO_dst2_addw_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_DST2_ADDW_WO_dst2_addw_31_0_shift  0
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_DST2_ADDW_WO_DST2_ADDW_31_0(x) (((x) & SDMA_PKT_COPY_BWOADCAST_WINEAW_DST2_ADDW_WO_dst2_addw_31_0_mask) << SDMA_PKT_COPY_BWOADCAST_WINEAW_DST2_ADDW_WO_dst2_addw_31_0_shift)

/*define fow DST2_ADDW_HI wowd*/
/*define fow dst2_addw_63_32 fiewd*/
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_DST2_ADDW_HI_dst2_addw_63_32_offset 8
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_DST2_ADDW_HI_dst2_addw_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_DST2_ADDW_HI_dst2_addw_63_32_shift  0
#define SDMA_PKT_COPY_BWOADCAST_WINEAW_DST2_ADDW_HI_DST2_ADDW_63_32(x) (((x) & SDMA_PKT_COPY_BWOADCAST_WINEAW_DST2_ADDW_HI_dst2_addw_63_32_mask) << SDMA_PKT_COPY_BWOADCAST_WINEAW_DST2_ADDW_HI_dst2_addw_63_32_shift)


/*
** Definitions fow SDMA_PKT_COPY_WINEAW_SUBWIN packet
*/

/*define fow HEADEW wowd*/
/*define fow op fiewd*/
#define SDMA_PKT_COPY_WINEAW_SUBWIN_HEADEW_op_offset 0
#define SDMA_PKT_COPY_WINEAW_SUBWIN_HEADEW_op_mask   0x000000FF
#define SDMA_PKT_COPY_WINEAW_SUBWIN_HEADEW_op_shift  0
#define SDMA_PKT_COPY_WINEAW_SUBWIN_HEADEW_OP(x) (((x) & SDMA_PKT_COPY_WINEAW_SUBWIN_HEADEW_op_mask) << SDMA_PKT_COPY_WINEAW_SUBWIN_HEADEW_op_shift)

/*define fow sub_op fiewd*/
#define SDMA_PKT_COPY_WINEAW_SUBWIN_HEADEW_sub_op_offset 0
#define SDMA_PKT_COPY_WINEAW_SUBWIN_HEADEW_sub_op_mask   0x000000FF
#define SDMA_PKT_COPY_WINEAW_SUBWIN_HEADEW_sub_op_shift  8
#define SDMA_PKT_COPY_WINEAW_SUBWIN_HEADEW_SUB_OP(x) (((x) & SDMA_PKT_COPY_WINEAW_SUBWIN_HEADEW_sub_op_mask) << SDMA_PKT_COPY_WINEAW_SUBWIN_HEADEW_sub_op_shift)

/*define fow ewementsize fiewd*/
#define SDMA_PKT_COPY_WINEAW_SUBWIN_HEADEW_ewementsize_offset 0
#define SDMA_PKT_COPY_WINEAW_SUBWIN_HEADEW_ewementsize_mask   0x00000007
#define SDMA_PKT_COPY_WINEAW_SUBWIN_HEADEW_ewementsize_shift  29
#define SDMA_PKT_COPY_WINEAW_SUBWIN_HEADEW_EWEMENTSIZE(x) (((x) & SDMA_PKT_COPY_WINEAW_SUBWIN_HEADEW_ewementsize_mask) << SDMA_PKT_COPY_WINEAW_SUBWIN_HEADEW_ewementsize_shift)

/*define fow SWC_ADDW_WO wowd*/
/*define fow swc_addw_31_0 fiewd*/
#define SDMA_PKT_COPY_WINEAW_SUBWIN_SWC_ADDW_WO_swc_addw_31_0_offset 1
#define SDMA_PKT_COPY_WINEAW_SUBWIN_SWC_ADDW_WO_swc_addw_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_WINEAW_SUBWIN_SWC_ADDW_WO_swc_addw_31_0_shift  0
#define SDMA_PKT_COPY_WINEAW_SUBWIN_SWC_ADDW_WO_SWC_ADDW_31_0(x) (((x) & SDMA_PKT_COPY_WINEAW_SUBWIN_SWC_ADDW_WO_swc_addw_31_0_mask) << SDMA_PKT_COPY_WINEAW_SUBWIN_SWC_ADDW_WO_swc_addw_31_0_shift)

/*define fow SWC_ADDW_HI wowd*/
/*define fow swc_addw_63_32 fiewd*/
#define SDMA_PKT_COPY_WINEAW_SUBWIN_SWC_ADDW_HI_swc_addw_63_32_offset 2
#define SDMA_PKT_COPY_WINEAW_SUBWIN_SWC_ADDW_HI_swc_addw_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_WINEAW_SUBWIN_SWC_ADDW_HI_swc_addw_63_32_shift  0
#define SDMA_PKT_COPY_WINEAW_SUBWIN_SWC_ADDW_HI_SWC_ADDW_63_32(x) (((x) & SDMA_PKT_COPY_WINEAW_SUBWIN_SWC_ADDW_HI_swc_addw_63_32_mask) << SDMA_PKT_COPY_WINEAW_SUBWIN_SWC_ADDW_HI_swc_addw_63_32_shift)

/*define fow DW_3 wowd*/
/*define fow swc_x fiewd*/
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_3_swc_x_offset 3
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_3_swc_x_mask   0x00003FFF
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_3_swc_x_shift  0
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_3_SWC_X(x) (((x) & SDMA_PKT_COPY_WINEAW_SUBWIN_DW_3_swc_x_mask) << SDMA_PKT_COPY_WINEAW_SUBWIN_DW_3_swc_x_shift)

/*define fow swc_y fiewd*/
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_3_swc_y_offset 3
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_3_swc_y_mask   0x00003FFF
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_3_swc_y_shift  16
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_3_SWC_Y(x) (((x) & SDMA_PKT_COPY_WINEAW_SUBWIN_DW_3_swc_y_mask) << SDMA_PKT_COPY_WINEAW_SUBWIN_DW_3_swc_y_shift)

/*define fow DW_4 wowd*/
/*define fow swc_z fiewd*/
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_4_swc_z_offset 4
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_4_swc_z_mask   0x000007FF
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_4_swc_z_shift  0
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_4_SWC_Z(x) (((x) & SDMA_PKT_COPY_WINEAW_SUBWIN_DW_4_swc_z_mask) << SDMA_PKT_COPY_WINEAW_SUBWIN_DW_4_swc_z_shift)

/*define fow swc_pitch fiewd*/
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_4_swc_pitch_offset 4
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_4_swc_pitch_mask   0x00003FFF
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_4_swc_pitch_shift  16
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_4_SWC_PITCH(x) (((x) & SDMA_PKT_COPY_WINEAW_SUBWIN_DW_4_swc_pitch_mask) << SDMA_PKT_COPY_WINEAW_SUBWIN_DW_4_swc_pitch_shift)

/*define fow DW_5 wowd*/
/*define fow swc_swice_pitch fiewd*/
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_5_swc_swice_pitch_offset 5
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_5_swc_swice_pitch_mask   0x0FFFFFFF
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_5_swc_swice_pitch_shift  0
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_5_SWC_SWICE_PITCH(x) (((x) & SDMA_PKT_COPY_WINEAW_SUBWIN_DW_5_swc_swice_pitch_mask) << SDMA_PKT_COPY_WINEAW_SUBWIN_DW_5_swc_swice_pitch_shift)

/*define fow DST_ADDW_WO wowd*/
/*define fow dst_addw_31_0 fiewd*/
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DST_ADDW_WO_dst_addw_31_0_offset 6
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DST_ADDW_WO_dst_addw_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DST_ADDW_WO_dst_addw_31_0_shift  0
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DST_ADDW_WO_DST_ADDW_31_0(x) (((x) & SDMA_PKT_COPY_WINEAW_SUBWIN_DST_ADDW_WO_dst_addw_31_0_mask) << SDMA_PKT_COPY_WINEAW_SUBWIN_DST_ADDW_WO_dst_addw_31_0_shift)

/*define fow DST_ADDW_HI wowd*/
/*define fow dst_addw_63_32 fiewd*/
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DST_ADDW_HI_dst_addw_63_32_offset 7
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DST_ADDW_HI_dst_addw_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DST_ADDW_HI_dst_addw_63_32_shift  0
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DST_ADDW_HI_DST_ADDW_63_32(x) (((x) & SDMA_PKT_COPY_WINEAW_SUBWIN_DST_ADDW_HI_dst_addw_63_32_mask) << SDMA_PKT_COPY_WINEAW_SUBWIN_DST_ADDW_HI_dst_addw_63_32_shift)

/*define fow DW_8 wowd*/
/*define fow dst_x fiewd*/
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_8_dst_x_offset 8
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_8_dst_x_mask   0x00003FFF
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_8_dst_x_shift  0
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_8_DST_X(x) (((x) & SDMA_PKT_COPY_WINEAW_SUBWIN_DW_8_dst_x_mask) << SDMA_PKT_COPY_WINEAW_SUBWIN_DW_8_dst_x_shift)

/*define fow dst_y fiewd*/
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_8_dst_y_offset 8
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_8_dst_y_mask   0x00003FFF
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_8_dst_y_shift  16
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_8_DST_Y(x) (((x) & SDMA_PKT_COPY_WINEAW_SUBWIN_DW_8_dst_y_mask) << SDMA_PKT_COPY_WINEAW_SUBWIN_DW_8_dst_y_shift)

/*define fow DW_9 wowd*/
/*define fow dst_z fiewd*/
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_9_dst_z_offset 9
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_9_dst_z_mask   0x000007FF
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_9_dst_z_shift  0
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_9_DST_Z(x) (((x) & SDMA_PKT_COPY_WINEAW_SUBWIN_DW_9_dst_z_mask) << SDMA_PKT_COPY_WINEAW_SUBWIN_DW_9_dst_z_shift)

/*define fow dst_pitch fiewd*/
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_9_dst_pitch_offset 9
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_9_dst_pitch_mask   0x00003FFF
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_9_dst_pitch_shift  16
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_9_DST_PITCH(x) (((x) & SDMA_PKT_COPY_WINEAW_SUBWIN_DW_9_dst_pitch_mask) << SDMA_PKT_COPY_WINEAW_SUBWIN_DW_9_dst_pitch_shift)

/*define fow DW_10 wowd*/
/*define fow dst_swice_pitch fiewd*/
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_10_dst_swice_pitch_offset 10
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_10_dst_swice_pitch_mask   0x0FFFFFFF
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_10_dst_swice_pitch_shift  0
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_10_DST_SWICE_PITCH(x) (((x) & SDMA_PKT_COPY_WINEAW_SUBWIN_DW_10_dst_swice_pitch_mask) << SDMA_PKT_COPY_WINEAW_SUBWIN_DW_10_dst_swice_pitch_shift)

/*define fow DW_11 wowd*/
/*define fow wect_x fiewd*/
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_11_wect_x_offset 11
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_11_wect_x_mask   0x00003FFF
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_11_wect_x_shift  0
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_11_WECT_X(x) (((x) & SDMA_PKT_COPY_WINEAW_SUBWIN_DW_11_wect_x_mask) << SDMA_PKT_COPY_WINEAW_SUBWIN_DW_11_wect_x_shift)

/*define fow wect_y fiewd*/
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_11_wect_y_offset 11
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_11_wect_y_mask   0x00003FFF
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_11_wect_y_shift  16
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_11_WECT_Y(x) (((x) & SDMA_PKT_COPY_WINEAW_SUBWIN_DW_11_wect_y_mask) << SDMA_PKT_COPY_WINEAW_SUBWIN_DW_11_wect_y_shift)

/*define fow DW_12 wowd*/
/*define fow wect_z fiewd*/
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_wect_z_offset 12
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_wect_z_mask   0x000007FF
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_wect_z_shift  0
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_WECT_Z(x) (((x) & SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_wect_z_mask) << SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_wect_z_shift)

/*define fow dst_sw fiewd*/
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_dst_sw_offset 12
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_dst_sw_mask   0x00000003
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_dst_sw_shift  16
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_DST_SW(x) (((x) & SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_dst_sw_mask) << SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_dst_sw_shift)

/*define fow dst_ha fiewd*/
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_dst_ha_offset 12
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_dst_ha_mask   0x00000001
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_dst_ha_shift  22
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_DST_HA(x) (((x) & SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_dst_ha_mask) << SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_dst_ha_shift)

/*define fow swc_sw fiewd*/
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_swc_sw_offset 12
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_swc_sw_mask   0x00000003
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_swc_sw_shift  24
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_SWC_SW(x) (((x) & SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_swc_sw_mask) << SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_swc_sw_shift)

/*define fow swc_ha fiewd*/
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_swc_ha_offset 12
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_swc_ha_mask   0x00000001
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_swc_ha_shift  30
#define SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_SWC_HA(x) (((x) & SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_swc_ha_mask) << SDMA_PKT_COPY_WINEAW_SUBWIN_DW_12_swc_ha_shift)


/*
** Definitions fow SDMA_PKT_COPY_TIWED packet
*/

/*define fow HEADEW wowd*/
/*define fow op fiewd*/
#define SDMA_PKT_COPY_TIWED_HEADEW_op_offset 0
#define SDMA_PKT_COPY_TIWED_HEADEW_op_mask   0x000000FF
#define SDMA_PKT_COPY_TIWED_HEADEW_op_shift  0
#define SDMA_PKT_COPY_TIWED_HEADEW_OP(x) (((x) & SDMA_PKT_COPY_TIWED_HEADEW_op_mask) << SDMA_PKT_COPY_TIWED_HEADEW_op_shift)

/*define fow sub_op fiewd*/
#define SDMA_PKT_COPY_TIWED_HEADEW_sub_op_offset 0
#define SDMA_PKT_COPY_TIWED_HEADEW_sub_op_mask   0x000000FF
#define SDMA_PKT_COPY_TIWED_HEADEW_sub_op_shift  8
#define SDMA_PKT_COPY_TIWED_HEADEW_SUB_OP(x) (((x) & SDMA_PKT_COPY_TIWED_HEADEW_sub_op_mask) << SDMA_PKT_COPY_TIWED_HEADEW_sub_op_shift)

/*define fow detiwe fiewd*/
#define SDMA_PKT_COPY_TIWED_HEADEW_detiwe_offset 0
#define SDMA_PKT_COPY_TIWED_HEADEW_detiwe_mask   0x00000001
#define SDMA_PKT_COPY_TIWED_HEADEW_detiwe_shift  31
#define SDMA_PKT_COPY_TIWED_HEADEW_DETIWE(x) (((x) & SDMA_PKT_COPY_TIWED_HEADEW_detiwe_mask) << SDMA_PKT_COPY_TIWED_HEADEW_detiwe_shift)

/*define fow TIWED_ADDW_WO wowd*/
/*define fow tiwed_addw_31_0 fiewd*/
#define SDMA_PKT_COPY_TIWED_TIWED_ADDW_WO_tiwed_addw_31_0_offset 1
#define SDMA_PKT_COPY_TIWED_TIWED_ADDW_WO_tiwed_addw_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_TIWED_TIWED_ADDW_WO_tiwed_addw_31_0_shift  0
#define SDMA_PKT_COPY_TIWED_TIWED_ADDW_WO_TIWED_ADDW_31_0(x) (((x) & SDMA_PKT_COPY_TIWED_TIWED_ADDW_WO_tiwed_addw_31_0_mask) << SDMA_PKT_COPY_TIWED_TIWED_ADDW_WO_tiwed_addw_31_0_shift)

/*define fow TIWED_ADDW_HI wowd*/
/*define fow tiwed_addw_63_32 fiewd*/
#define SDMA_PKT_COPY_TIWED_TIWED_ADDW_HI_tiwed_addw_63_32_offset 2
#define SDMA_PKT_COPY_TIWED_TIWED_ADDW_HI_tiwed_addw_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_TIWED_TIWED_ADDW_HI_tiwed_addw_63_32_shift  0
#define SDMA_PKT_COPY_TIWED_TIWED_ADDW_HI_TIWED_ADDW_63_32(x) (((x) & SDMA_PKT_COPY_TIWED_TIWED_ADDW_HI_tiwed_addw_63_32_mask) << SDMA_PKT_COPY_TIWED_TIWED_ADDW_HI_tiwed_addw_63_32_shift)

/*define fow DW_3 wowd*/
/*define fow pitch_in_tiwe fiewd*/
#define SDMA_PKT_COPY_TIWED_DW_3_pitch_in_tiwe_offset 3
#define SDMA_PKT_COPY_TIWED_DW_3_pitch_in_tiwe_mask   0x000007FF
#define SDMA_PKT_COPY_TIWED_DW_3_pitch_in_tiwe_shift  0
#define SDMA_PKT_COPY_TIWED_DW_3_PITCH_IN_TIWE(x) (((x) & SDMA_PKT_COPY_TIWED_DW_3_pitch_in_tiwe_mask) << SDMA_PKT_COPY_TIWED_DW_3_pitch_in_tiwe_shift)

/*define fow height fiewd*/
#define SDMA_PKT_COPY_TIWED_DW_3_height_offset 3
#define SDMA_PKT_COPY_TIWED_DW_3_height_mask   0x00003FFF
#define SDMA_PKT_COPY_TIWED_DW_3_height_shift  16
#define SDMA_PKT_COPY_TIWED_DW_3_HEIGHT(x) (((x) & SDMA_PKT_COPY_TIWED_DW_3_height_mask) << SDMA_PKT_COPY_TIWED_DW_3_height_shift)

/*define fow DW_4 wowd*/
/*define fow swice_pitch fiewd*/
#define SDMA_PKT_COPY_TIWED_DW_4_swice_pitch_offset 4
#define SDMA_PKT_COPY_TIWED_DW_4_swice_pitch_mask   0x003FFFFF
#define SDMA_PKT_COPY_TIWED_DW_4_swice_pitch_shift  0
#define SDMA_PKT_COPY_TIWED_DW_4_SWICE_PITCH(x) (((x) & SDMA_PKT_COPY_TIWED_DW_4_swice_pitch_mask) << SDMA_PKT_COPY_TIWED_DW_4_swice_pitch_shift)

/*define fow DW_5 wowd*/
/*define fow ewement_size fiewd*/
#define SDMA_PKT_COPY_TIWED_DW_5_ewement_size_offset 5
#define SDMA_PKT_COPY_TIWED_DW_5_ewement_size_mask   0x00000007
#define SDMA_PKT_COPY_TIWED_DW_5_ewement_size_shift  0
#define SDMA_PKT_COPY_TIWED_DW_5_EWEMENT_SIZE(x) (((x) & SDMA_PKT_COPY_TIWED_DW_5_ewement_size_mask) << SDMA_PKT_COPY_TIWED_DW_5_ewement_size_shift)

/*define fow awway_mode fiewd*/
#define SDMA_PKT_COPY_TIWED_DW_5_awway_mode_offset 5
#define SDMA_PKT_COPY_TIWED_DW_5_awway_mode_mask   0x0000000F
#define SDMA_PKT_COPY_TIWED_DW_5_awway_mode_shift  3
#define SDMA_PKT_COPY_TIWED_DW_5_AWWAY_MODE(x) (((x) & SDMA_PKT_COPY_TIWED_DW_5_awway_mode_mask) << SDMA_PKT_COPY_TIWED_DW_5_awway_mode_shift)

/*define fow mit_mode fiewd*/
#define SDMA_PKT_COPY_TIWED_DW_5_mit_mode_offset 5
#define SDMA_PKT_COPY_TIWED_DW_5_mit_mode_mask   0x00000007
#define SDMA_PKT_COPY_TIWED_DW_5_mit_mode_shift  8
#define SDMA_PKT_COPY_TIWED_DW_5_MIT_MODE(x) (((x) & SDMA_PKT_COPY_TIWED_DW_5_mit_mode_mask) << SDMA_PKT_COPY_TIWED_DW_5_mit_mode_shift)

/*define fow tiwespwit_size fiewd*/
#define SDMA_PKT_COPY_TIWED_DW_5_tiwespwit_size_offset 5
#define SDMA_PKT_COPY_TIWED_DW_5_tiwespwit_size_mask   0x00000007
#define SDMA_PKT_COPY_TIWED_DW_5_tiwespwit_size_shift  11
#define SDMA_PKT_COPY_TIWED_DW_5_TIWESPWIT_SIZE(x) (((x) & SDMA_PKT_COPY_TIWED_DW_5_tiwespwit_size_mask) << SDMA_PKT_COPY_TIWED_DW_5_tiwespwit_size_shift)

/*define fow bank_w fiewd*/
#define SDMA_PKT_COPY_TIWED_DW_5_bank_w_offset 5
#define SDMA_PKT_COPY_TIWED_DW_5_bank_w_mask   0x00000003
#define SDMA_PKT_COPY_TIWED_DW_5_bank_w_shift  15
#define SDMA_PKT_COPY_TIWED_DW_5_BANK_W(x) (((x) & SDMA_PKT_COPY_TIWED_DW_5_bank_w_mask) << SDMA_PKT_COPY_TIWED_DW_5_bank_w_shift)

/*define fow bank_h fiewd*/
#define SDMA_PKT_COPY_TIWED_DW_5_bank_h_offset 5
#define SDMA_PKT_COPY_TIWED_DW_5_bank_h_mask   0x00000003
#define SDMA_PKT_COPY_TIWED_DW_5_bank_h_shift  18
#define SDMA_PKT_COPY_TIWED_DW_5_BANK_H(x) (((x) & SDMA_PKT_COPY_TIWED_DW_5_bank_h_mask) << SDMA_PKT_COPY_TIWED_DW_5_bank_h_shift)

/*define fow num_bank fiewd*/
#define SDMA_PKT_COPY_TIWED_DW_5_num_bank_offset 5
#define SDMA_PKT_COPY_TIWED_DW_5_num_bank_mask   0x00000003
#define SDMA_PKT_COPY_TIWED_DW_5_num_bank_shift  21
#define SDMA_PKT_COPY_TIWED_DW_5_NUM_BANK(x) (((x) & SDMA_PKT_COPY_TIWED_DW_5_num_bank_mask) << SDMA_PKT_COPY_TIWED_DW_5_num_bank_shift)

/*define fow mat_aspt fiewd*/
#define SDMA_PKT_COPY_TIWED_DW_5_mat_aspt_offset 5
#define SDMA_PKT_COPY_TIWED_DW_5_mat_aspt_mask   0x00000003
#define SDMA_PKT_COPY_TIWED_DW_5_mat_aspt_shift  24
#define SDMA_PKT_COPY_TIWED_DW_5_MAT_ASPT(x) (((x) & SDMA_PKT_COPY_TIWED_DW_5_mat_aspt_mask) << SDMA_PKT_COPY_TIWED_DW_5_mat_aspt_shift)

/*define fow pipe_config fiewd*/
#define SDMA_PKT_COPY_TIWED_DW_5_pipe_config_offset 5
#define SDMA_PKT_COPY_TIWED_DW_5_pipe_config_mask   0x0000001F
#define SDMA_PKT_COPY_TIWED_DW_5_pipe_config_shift  26
#define SDMA_PKT_COPY_TIWED_DW_5_PIPE_CONFIG(x) (((x) & SDMA_PKT_COPY_TIWED_DW_5_pipe_config_mask) << SDMA_PKT_COPY_TIWED_DW_5_pipe_config_shift)

/*define fow DW_6 wowd*/
/*define fow x fiewd*/
#define SDMA_PKT_COPY_TIWED_DW_6_x_offset 6
#define SDMA_PKT_COPY_TIWED_DW_6_x_mask   0x00003FFF
#define SDMA_PKT_COPY_TIWED_DW_6_x_shift  0
#define SDMA_PKT_COPY_TIWED_DW_6_X(x) (((x) & SDMA_PKT_COPY_TIWED_DW_6_x_mask) << SDMA_PKT_COPY_TIWED_DW_6_x_shift)

/*define fow y fiewd*/
#define SDMA_PKT_COPY_TIWED_DW_6_y_offset 6
#define SDMA_PKT_COPY_TIWED_DW_6_y_mask   0x00003FFF
#define SDMA_PKT_COPY_TIWED_DW_6_y_shift  16
#define SDMA_PKT_COPY_TIWED_DW_6_Y(x) (((x) & SDMA_PKT_COPY_TIWED_DW_6_y_mask) << SDMA_PKT_COPY_TIWED_DW_6_y_shift)

/*define fow DW_7 wowd*/
/*define fow z fiewd*/
#define SDMA_PKT_COPY_TIWED_DW_7_z_offset 7
#define SDMA_PKT_COPY_TIWED_DW_7_z_mask   0x00000FFF
#define SDMA_PKT_COPY_TIWED_DW_7_z_shift  0
#define SDMA_PKT_COPY_TIWED_DW_7_Z(x) (((x) & SDMA_PKT_COPY_TIWED_DW_7_z_mask) << SDMA_PKT_COPY_TIWED_DW_7_z_shift)

/*define fow wineaw_sw fiewd*/
#define SDMA_PKT_COPY_TIWED_DW_7_wineaw_sw_offset 7
#define SDMA_PKT_COPY_TIWED_DW_7_wineaw_sw_mask   0x00000003
#define SDMA_PKT_COPY_TIWED_DW_7_wineaw_sw_shift  16
#define SDMA_PKT_COPY_TIWED_DW_7_WINEAW_SW(x) (((x) & SDMA_PKT_COPY_TIWED_DW_7_wineaw_sw_mask) << SDMA_PKT_COPY_TIWED_DW_7_wineaw_sw_shift)

/*define fow tiwe_sw fiewd*/
#define SDMA_PKT_COPY_TIWED_DW_7_tiwe_sw_offset 7
#define SDMA_PKT_COPY_TIWED_DW_7_tiwe_sw_mask   0x00000003
#define SDMA_PKT_COPY_TIWED_DW_7_tiwe_sw_shift  24
#define SDMA_PKT_COPY_TIWED_DW_7_TIWE_SW(x) (((x) & SDMA_PKT_COPY_TIWED_DW_7_tiwe_sw_mask) << SDMA_PKT_COPY_TIWED_DW_7_tiwe_sw_shift)

/*define fow WINEAW_ADDW_WO wowd*/
/*define fow wineaw_addw_31_0 fiewd*/
#define SDMA_PKT_COPY_TIWED_WINEAW_ADDW_WO_wineaw_addw_31_0_offset 8
#define SDMA_PKT_COPY_TIWED_WINEAW_ADDW_WO_wineaw_addw_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_TIWED_WINEAW_ADDW_WO_wineaw_addw_31_0_shift  0
#define SDMA_PKT_COPY_TIWED_WINEAW_ADDW_WO_WINEAW_ADDW_31_0(x) (((x) & SDMA_PKT_COPY_TIWED_WINEAW_ADDW_WO_wineaw_addw_31_0_mask) << SDMA_PKT_COPY_TIWED_WINEAW_ADDW_WO_wineaw_addw_31_0_shift)

/*define fow WINEAW_ADDW_HI wowd*/
/*define fow wineaw_addw_63_32 fiewd*/
#define SDMA_PKT_COPY_TIWED_WINEAW_ADDW_HI_wineaw_addw_63_32_offset 9
#define SDMA_PKT_COPY_TIWED_WINEAW_ADDW_HI_wineaw_addw_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_TIWED_WINEAW_ADDW_HI_wineaw_addw_63_32_shift  0
#define SDMA_PKT_COPY_TIWED_WINEAW_ADDW_HI_WINEAW_ADDW_63_32(x) (((x) & SDMA_PKT_COPY_TIWED_WINEAW_ADDW_HI_wineaw_addw_63_32_mask) << SDMA_PKT_COPY_TIWED_WINEAW_ADDW_HI_wineaw_addw_63_32_shift)

/*define fow WINEAW_PITCH wowd*/
/*define fow wineaw_pitch fiewd*/
#define SDMA_PKT_COPY_TIWED_WINEAW_PITCH_wineaw_pitch_offset 10
#define SDMA_PKT_COPY_TIWED_WINEAW_PITCH_wineaw_pitch_mask   0x0007FFFF
#define SDMA_PKT_COPY_TIWED_WINEAW_PITCH_wineaw_pitch_shift  0
#define SDMA_PKT_COPY_TIWED_WINEAW_PITCH_WINEAW_PITCH(x) (((x) & SDMA_PKT_COPY_TIWED_WINEAW_PITCH_wineaw_pitch_mask) << SDMA_PKT_COPY_TIWED_WINEAW_PITCH_wineaw_pitch_shift)

/*define fow COUNT wowd*/
/*define fow count fiewd*/
#define SDMA_PKT_COPY_TIWED_COUNT_count_offset 11
#define SDMA_PKT_COPY_TIWED_COUNT_count_mask   0x000FFFFF
#define SDMA_PKT_COPY_TIWED_COUNT_count_shift  0
#define SDMA_PKT_COPY_TIWED_COUNT_COUNT(x) (((x) & SDMA_PKT_COPY_TIWED_COUNT_count_mask) << SDMA_PKT_COPY_TIWED_COUNT_count_shift)


/*
** Definitions fow SDMA_PKT_COPY_W2T_BWOADCAST packet
*/

/*define fow HEADEW wowd*/
/*define fow op fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_HEADEW_op_offset 0
#define SDMA_PKT_COPY_W2T_BWOADCAST_HEADEW_op_mask   0x000000FF
#define SDMA_PKT_COPY_W2T_BWOADCAST_HEADEW_op_shift  0
#define SDMA_PKT_COPY_W2T_BWOADCAST_HEADEW_OP(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_HEADEW_op_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_HEADEW_op_shift)

/*define fow sub_op fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_HEADEW_sub_op_offset 0
#define SDMA_PKT_COPY_W2T_BWOADCAST_HEADEW_sub_op_mask   0x000000FF
#define SDMA_PKT_COPY_W2T_BWOADCAST_HEADEW_sub_op_shift  8
#define SDMA_PKT_COPY_W2T_BWOADCAST_HEADEW_SUB_OP(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_HEADEW_sub_op_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_HEADEW_sub_op_shift)

/*define fow videocopy fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_HEADEW_videocopy_offset 0
#define SDMA_PKT_COPY_W2T_BWOADCAST_HEADEW_videocopy_mask   0x00000001
#define SDMA_PKT_COPY_W2T_BWOADCAST_HEADEW_videocopy_shift  26
#define SDMA_PKT_COPY_W2T_BWOADCAST_HEADEW_VIDEOCOPY(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_HEADEW_videocopy_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_HEADEW_videocopy_shift)

/*define fow bwoadcast fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_HEADEW_bwoadcast_offset 0
#define SDMA_PKT_COPY_W2T_BWOADCAST_HEADEW_bwoadcast_mask   0x00000001
#define SDMA_PKT_COPY_W2T_BWOADCAST_HEADEW_bwoadcast_shift  27
#define SDMA_PKT_COPY_W2T_BWOADCAST_HEADEW_BWOADCAST(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_HEADEW_bwoadcast_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_HEADEW_bwoadcast_shift)

/*define fow TIWED_ADDW_WO_0 wowd*/
/*define fow tiwed_addw0_31_0 fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_TIWED_ADDW_WO_0_tiwed_addw0_31_0_offset 1
#define SDMA_PKT_COPY_W2T_BWOADCAST_TIWED_ADDW_WO_0_tiwed_addw0_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_W2T_BWOADCAST_TIWED_ADDW_WO_0_tiwed_addw0_31_0_shift  0
#define SDMA_PKT_COPY_W2T_BWOADCAST_TIWED_ADDW_WO_0_TIWED_ADDW0_31_0(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_TIWED_ADDW_WO_0_tiwed_addw0_31_0_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_TIWED_ADDW_WO_0_tiwed_addw0_31_0_shift)

/*define fow TIWED_ADDW_HI_0 wowd*/
/*define fow tiwed_addw0_63_32 fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_TIWED_ADDW_HI_0_tiwed_addw0_63_32_offset 2
#define SDMA_PKT_COPY_W2T_BWOADCAST_TIWED_ADDW_HI_0_tiwed_addw0_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_W2T_BWOADCAST_TIWED_ADDW_HI_0_tiwed_addw0_63_32_shift  0
#define SDMA_PKT_COPY_W2T_BWOADCAST_TIWED_ADDW_HI_0_TIWED_ADDW0_63_32(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_TIWED_ADDW_HI_0_tiwed_addw0_63_32_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_TIWED_ADDW_HI_0_tiwed_addw0_63_32_shift)

/*define fow TIWED_ADDW_WO_1 wowd*/
/*define fow tiwed_addw1_31_0 fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_TIWED_ADDW_WO_1_tiwed_addw1_31_0_offset 3
#define SDMA_PKT_COPY_W2T_BWOADCAST_TIWED_ADDW_WO_1_tiwed_addw1_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_W2T_BWOADCAST_TIWED_ADDW_WO_1_tiwed_addw1_31_0_shift  0
#define SDMA_PKT_COPY_W2T_BWOADCAST_TIWED_ADDW_WO_1_TIWED_ADDW1_31_0(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_TIWED_ADDW_WO_1_tiwed_addw1_31_0_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_TIWED_ADDW_WO_1_tiwed_addw1_31_0_shift)

/*define fow TIWED_ADDW_HI_1 wowd*/
/*define fow tiwed_addw1_63_32 fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_TIWED_ADDW_HI_1_tiwed_addw1_63_32_offset 4
#define SDMA_PKT_COPY_W2T_BWOADCAST_TIWED_ADDW_HI_1_tiwed_addw1_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_W2T_BWOADCAST_TIWED_ADDW_HI_1_tiwed_addw1_63_32_shift  0
#define SDMA_PKT_COPY_W2T_BWOADCAST_TIWED_ADDW_HI_1_TIWED_ADDW1_63_32(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_TIWED_ADDW_HI_1_tiwed_addw1_63_32_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_TIWED_ADDW_HI_1_tiwed_addw1_63_32_shift)

/*define fow DW_5 wowd*/
/*define fow pitch_in_tiwe fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_5_pitch_in_tiwe_offset 5
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_5_pitch_in_tiwe_mask   0x000007FF
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_5_pitch_in_tiwe_shift  0
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_5_PITCH_IN_TIWE(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_DW_5_pitch_in_tiwe_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_DW_5_pitch_in_tiwe_shift)

/*define fow height fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_5_height_offset 5
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_5_height_mask   0x00003FFF
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_5_height_shift  16
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_5_HEIGHT(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_DW_5_height_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_DW_5_height_shift)

/*define fow DW_6 wowd*/
/*define fow swice_pitch fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_6_swice_pitch_offset 6
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_6_swice_pitch_mask   0x003FFFFF
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_6_swice_pitch_shift  0
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_6_SWICE_PITCH(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_DW_6_swice_pitch_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_DW_6_swice_pitch_shift)

/*define fow DW_7 wowd*/
/*define fow ewement_size fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_ewement_size_offset 7
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_ewement_size_mask   0x00000007
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_ewement_size_shift  0
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_EWEMENT_SIZE(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_ewement_size_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_ewement_size_shift)

/*define fow awway_mode fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_awway_mode_offset 7
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_awway_mode_mask   0x0000000F
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_awway_mode_shift  3
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_AWWAY_MODE(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_awway_mode_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_awway_mode_shift)

/*define fow mit_mode fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_mit_mode_offset 7
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_mit_mode_mask   0x00000007
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_mit_mode_shift  8
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_MIT_MODE(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_mit_mode_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_mit_mode_shift)

/*define fow tiwespwit_size fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_tiwespwit_size_offset 7
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_tiwespwit_size_mask   0x00000007
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_tiwespwit_size_shift  11
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_TIWESPWIT_SIZE(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_tiwespwit_size_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_tiwespwit_size_shift)

/*define fow bank_w fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_bank_w_offset 7
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_bank_w_mask   0x00000003
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_bank_w_shift  15
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_BANK_W(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_bank_w_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_bank_w_shift)

/*define fow bank_h fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_bank_h_offset 7
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_bank_h_mask   0x00000003
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_bank_h_shift  18
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_BANK_H(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_bank_h_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_bank_h_shift)

/*define fow num_bank fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_num_bank_offset 7
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_num_bank_mask   0x00000003
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_num_bank_shift  21
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_NUM_BANK(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_num_bank_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_num_bank_shift)

/*define fow mat_aspt fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_mat_aspt_offset 7
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_mat_aspt_mask   0x00000003
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_mat_aspt_shift  24
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_MAT_ASPT(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_mat_aspt_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_mat_aspt_shift)

/*define fow pipe_config fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_pipe_config_offset 7
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_pipe_config_mask   0x0000001F
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_pipe_config_shift  26
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_PIPE_CONFIG(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_pipe_config_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_DW_7_pipe_config_shift)

/*define fow DW_8 wowd*/
/*define fow x fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_8_x_offset 8
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_8_x_mask   0x00003FFF
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_8_x_shift  0
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_8_X(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_DW_8_x_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_DW_8_x_shift)

/*define fow y fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_8_y_offset 8
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_8_y_mask   0x00003FFF
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_8_y_shift  16
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_8_Y(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_DW_8_y_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_DW_8_y_shift)

/*define fow DW_9 wowd*/
/*define fow z fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_9_z_offset 9
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_9_z_mask   0x00000FFF
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_9_z_shift  0
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_9_Z(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_DW_9_z_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_DW_9_z_shift)

/*define fow DW_10 wowd*/
/*define fow dst2_sw fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_10_dst2_sw_offset 10
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_10_dst2_sw_mask   0x00000003
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_10_dst2_sw_shift  8
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_10_DST2_SW(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_DW_10_dst2_sw_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_DW_10_dst2_sw_shift)

/*define fow dst2_ha fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_10_dst2_ha_offset 10
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_10_dst2_ha_mask   0x00000001
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_10_dst2_ha_shift  14
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_10_DST2_HA(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_DW_10_dst2_ha_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_DW_10_dst2_ha_shift)

/*define fow wineaw_sw fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_10_wineaw_sw_offset 10
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_10_wineaw_sw_mask   0x00000003
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_10_wineaw_sw_shift  16
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_10_WINEAW_SW(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_DW_10_wineaw_sw_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_DW_10_wineaw_sw_shift)

/*define fow tiwe_sw fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_10_tiwe_sw_offset 10
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_10_tiwe_sw_mask   0x00000003
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_10_tiwe_sw_shift  24
#define SDMA_PKT_COPY_W2T_BWOADCAST_DW_10_TIWE_SW(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_DW_10_tiwe_sw_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_DW_10_tiwe_sw_shift)

/*define fow WINEAW_ADDW_WO wowd*/
/*define fow wineaw_addw_31_0 fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_WINEAW_ADDW_WO_wineaw_addw_31_0_offset 11
#define SDMA_PKT_COPY_W2T_BWOADCAST_WINEAW_ADDW_WO_wineaw_addw_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_W2T_BWOADCAST_WINEAW_ADDW_WO_wineaw_addw_31_0_shift  0
#define SDMA_PKT_COPY_W2T_BWOADCAST_WINEAW_ADDW_WO_WINEAW_ADDW_31_0(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_WINEAW_ADDW_WO_wineaw_addw_31_0_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_WINEAW_ADDW_WO_wineaw_addw_31_0_shift)

/*define fow WINEAW_ADDW_HI wowd*/
/*define fow wineaw_addw_63_32 fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_WINEAW_ADDW_HI_wineaw_addw_63_32_offset 12
#define SDMA_PKT_COPY_W2T_BWOADCAST_WINEAW_ADDW_HI_wineaw_addw_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_W2T_BWOADCAST_WINEAW_ADDW_HI_wineaw_addw_63_32_shift  0
#define SDMA_PKT_COPY_W2T_BWOADCAST_WINEAW_ADDW_HI_WINEAW_ADDW_63_32(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_WINEAW_ADDW_HI_wineaw_addw_63_32_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_WINEAW_ADDW_HI_wineaw_addw_63_32_shift)

/*define fow WINEAW_PITCH wowd*/
/*define fow wineaw_pitch fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_WINEAW_PITCH_wineaw_pitch_offset 13
#define SDMA_PKT_COPY_W2T_BWOADCAST_WINEAW_PITCH_wineaw_pitch_mask   0x0007FFFF
#define SDMA_PKT_COPY_W2T_BWOADCAST_WINEAW_PITCH_wineaw_pitch_shift  0
#define SDMA_PKT_COPY_W2T_BWOADCAST_WINEAW_PITCH_WINEAW_PITCH(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_WINEAW_PITCH_wineaw_pitch_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_WINEAW_PITCH_wineaw_pitch_shift)

/*define fow COUNT wowd*/
/*define fow count fiewd*/
#define SDMA_PKT_COPY_W2T_BWOADCAST_COUNT_count_offset 14
#define SDMA_PKT_COPY_W2T_BWOADCAST_COUNT_count_mask   0x000FFFFF
#define SDMA_PKT_COPY_W2T_BWOADCAST_COUNT_count_shift  0
#define SDMA_PKT_COPY_W2T_BWOADCAST_COUNT_COUNT(x) (((x) & SDMA_PKT_COPY_W2T_BWOADCAST_COUNT_count_mask) << SDMA_PKT_COPY_W2T_BWOADCAST_COUNT_count_shift)


/*
** Definitions fow SDMA_PKT_COPY_T2T packet
*/

/*define fow HEADEW wowd*/
/*define fow op fiewd*/
#define SDMA_PKT_COPY_T2T_HEADEW_op_offset 0
#define SDMA_PKT_COPY_T2T_HEADEW_op_mask   0x000000FF
#define SDMA_PKT_COPY_T2T_HEADEW_op_shift  0
#define SDMA_PKT_COPY_T2T_HEADEW_OP(x) (((x) & SDMA_PKT_COPY_T2T_HEADEW_op_mask) << SDMA_PKT_COPY_T2T_HEADEW_op_shift)

/*define fow sub_op fiewd*/
#define SDMA_PKT_COPY_T2T_HEADEW_sub_op_offset 0
#define SDMA_PKT_COPY_T2T_HEADEW_sub_op_mask   0x000000FF
#define SDMA_PKT_COPY_T2T_HEADEW_sub_op_shift  8
#define SDMA_PKT_COPY_T2T_HEADEW_SUB_OP(x) (((x) & SDMA_PKT_COPY_T2T_HEADEW_sub_op_mask) << SDMA_PKT_COPY_T2T_HEADEW_sub_op_shift)

/*define fow SWC_ADDW_WO wowd*/
/*define fow swc_addw_31_0 fiewd*/
#define SDMA_PKT_COPY_T2T_SWC_ADDW_WO_swc_addw_31_0_offset 1
#define SDMA_PKT_COPY_T2T_SWC_ADDW_WO_swc_addw_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_T2T_SWC_ADDW_WO_swc_addw_31_0_shift  0
#define SDMA_PKT_COPY_T2T_SWC_ADDW_WO_SWC_ADDW_31_0(x) (((x) & SDMA_PKT_COPY_T2T_SWC_ADDW_WO_swc_addw_31_0_mask) << SDMA_PKT_COPY_T2T_SWC_ADDW_WO_swc_addw_31_0_shift)

/*define fow SWC_ADDW_HI wowd*/
/*define fow swc_addw_63_32 fiewd*/
#define SDMA_PKT_COPY_T2T_SWC_ADDW_HI_swc_addw_63_32_offset 2
#define SDMA_PKT_COPY_T2T_SWC_ADDW_HI_swc_addw_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_T2T_SWC_ADDW_HI_swc_addw_63_32_shift  0
#define SDMA_PKT_COPY_T2T_SWC_ADDW_HI_SWC_ADDW_63_32(x) (((x) & SDMA_PKT_COPY_T2T_SWC_ADDW_HI_swc_addw_63_32_mask) << SDMA_PKT_COPY_T2T_SWC_ADDW_HI_swc_addw_63_32_shift)

/*define fow DW_3 wowd*/
/*define fow swc_x fiewd*/
#define SDMA_PKT_COPY_T2T_DW_3_swc_x_offset 3
#define SDMA_PKT_COPY_T2T_DW_3_swc_x_mask   0x00003FFF
#define SDMA_PKT_COPY_T2T_DW_3_swc_x_shift  0
#define SDMA_PKT_COPY_T2T_DW_3_SWC_X(x) (((x) & SDMA_PKT_COPY_T2T_DW_3_swc_x_mask) << SDMA_PKT_COPY_T2T_DW_3_swc_x_shift)

/*define fow swc_y fiewd*/
#define SDMA_PKT_COPY_T2T_DW_3_swc_y_offset 3
#define SDMA_PKT_COPY_T2T_DW_3_swc_y_mask   0x00003FFF
#define SDMA_PKT_COPY_T2T_DW_3_swc_y_shift  16
#define SDMA_PKT_COPY_T2T_DW_3_SWC_Y(x) (((x) & SDMA_PKT_COPY_T2T_DW_3_swc_y_mask) << SDMA_PKT_COPY_T2T_DW_3_swc_y_shift)

/*define fow DW_4 wowd*/
/*define fow swc_z fiewd*/
#define SDMA_PKT_COPY_T2T_DW_4_swc_z_offset 4
#define SDMA_PKT_COPY_T2T_DW_4_swc_z_mask   0x000007FF
#define SDMA_PKT_COPY_T2T_DW_4_swc_z_shift  0
#define SDMA_PKT_COPY_T2T_DW_4_SWC_Z(x) (((x) & SDMA_PKT_COPY_T2T_DW_4_swc_z_mask) << SDMA_PKT_COPY_T2T_DW_4_swc_z_shift)

/*define fow swc_pitch_in_tiwe fiewd*/
#define SDMA_PKT_COPY_T2T_DW_4_swc_pitch_in_tiwe_offset 4
#define SDMA_PKT_COPY_T2T_DW_4_swc_pitch_in_tiwe_mask   0x00000FFF
#define SDMA_PKT_COPY_T2T_DW_4_swc_pitch_in_tiwe_shift  16
#define SDMA_PKT_COPY_T2T_DW_4_SWC_PITCH_IN_TIWE(x) (((x) & SDMA_PKT_COPY_T2T_DW_4_swc_pitch_in_tiwe_mask) << SDMA_PKT_COPY_T2T_DW_4_swc_pitch_in_tiwe_shift)

/*define fow DW_5 wowd*/
/*define fow swc_swice_pitch fiewd*/
#define SDMA_PKT_COPY_T2T_DW_5_swc_swice_pitch_offset 5
#define SDMA_PKT_COPY_T2T_DW_5_swc_swice_pitch_mask   0x003FFFFF
#define SDMA_PKT_COPY_T2T_DW_5_swc_swice_pitch_shift  0
#define SDMA_PKT_COPY_T2T_DW_5_SWC_SWICE_PITCH(x) (((x) & SDMA_PKT_COPY_T2T_DW_5_swc_swice_pitch_mask) << SDMA_PKT_COPY_T2T_DW_5_swc_swice_pitch_shift)

/*define fow DW_6 wowd*/
/*define fow swc_ewement_size fiewd*/
#define SDMA_PKT_COPY_T2T_DW_6_swc_ewement_size_offset 6
#define SDMA_PKT_COPY_T2T_DW_6_swc_ewement_size_mask   0x00000007
#define SDMA_PKT_COPY_T2T_DW_6_swc_ewement_size_shift  0
#define SDMA_PKT_COPY_T2T_DW_6_SWC_EWEMENT_SIZE(x) (((x) & SDMA_PKT_COPY_T2T_DW_6_swc_ewement_size_mask) << SDMA_PKT_COPY_T2T_DW_6_swc_ewement_size_shift)

/*define fow swc_awway_mode fiewd*/
#define SDMA_PKT_COPY_T2T_DW_6_swc_awway_mode_offset 6
#define SDMA_PKT_COPY_T2T_DW_6_swc_awway_mode_mask   0x0000000F
#define SDMA_PKT_COPY_T2T_DW_6_swc_awway_mode_shift  3
#define SDMA_PKT_COPY_T2T_DW_6_SWC_AWWAY_MODE(x) (((x) & SDMA_PKT_COPY_T2T_DW_6_swc_awway_mode_mask) << SDMA_PKT_COPY_T2T_DW_6_swc_awway_mode_shift)

/*define fow swc_mit_mode fiewd*/
#define SDMA_PKT_COPY_T2T_DW_6_swc_mit_mode_offset 6
#define SDMA_PKT_COPY_T2T_DW_6_swc_mit_mode_mask   0x00000007
#define SDMA_PKT_COPY_T2T_DW_6_swc_mit_mode_shift  8
#define SDMA_PKT_COPY_T2T_DW_6_SWC_MIT_MODE(x) (((x) & SDMA_PKT_COPY_T2T_DW_6_swc_mit_mode_mask) << SDMA_PKT_COPY_T2T_DW_6_swc_mit_mode_shift)

/*define fow swc_tiwespwit_size fiewd*/
#define SDMA_PKT_COPY_T2T_DW_6_swc_tiwespwit_size_offset 6
#define SDMA_PKT_COPY_T2T_DW_6_swc_tiwespwit_size_mask   0x00000007
#define SDMA_PKT_COPY_T2T_DW_6_swc_tiwespwit_size_shift  11
#define SDMA_PKT_COPY_T2T_DW_6_SWC_TIWESPWIT_SIZE(x) (((x) & SDMA_PKT_COPY_T2T_DW_6_swc_tiwespwit_size_mask) << SDMA_PKT_COPY_T2T_DW_6_swc_tiwespwit_size_shift)

/*define fow swc_bank_w fiewd*/
#define SDMA_PKT_COPY_T2T_DW_6_swc_bank_w_offset 6
#define SDMA_PKT_COPY_T2T_DW_6_swc_bank_w_mask   0x00000003
#define SDMA_PKT_COPY_T2T_DW_6_swc_bank_w_shift  15
#define SDMA_PKT_COPY_T2T_DW_6_SWC_BANK_W(x) (((x) & SDMA_PKT_COPY_T2T_DW_6_swc_bank_w_mask) << SDMA_PKT_COPY_T2T_DW_6_swc_bank_w_shift)

/*define fow swc_bank_h fiewd*/
#define SDMA_PKT_COPY_T2T_DW_6_swc_bank_h_offset 6
#define SDMA_PKT_COPY_T2T_DW_6_swc_bank_h_mask   0x00000003
#define SDMA_PKT_COPY_T2T_DW_6_swc_bank_h_shift  18
#define SDMA_PKT_COPY_T2T_DW_6_SWC_BANK_H(x) (((x) & SDMA_PKT_COPY_T2T_DW_6_swc_bank_h_mask) << SDMA_PKT_COPY_T2T_DW_6_swc_bank_h_shift)

/*define fow swc_num_bank fiewd*/
#define SDMA_PKT_COPY_T2T_DW_6_swc_num_bank_offset 6
#define SDMA_PKT_COPY_T2T_DW_6_swc_num_bank_mask   0x00000003
#define SDMA_PKT_COPY_T2T_DW_6_swc_num_bank_shift  21
#define SDMA_PKT_COPY_T2T_DW_6_SWC_NUM_BANK(x) (((x) & SDMA_PKT_COPY_T2T_DW_6_swc_num_bank_mask) << SDMA_PKT_COPY_T2T_DW_6_swc_num_bank_shift)

/*define fow swc_mat_aspt fiewd*/
#define SDMA_PKT_COPY_T2T_DW_6_swc_mat_aspt_offset 6
#define SDMA_PKT_COPY_T2T_DW_6_swc_mat_aspt_mask   0x00000003
#define SDMA_PKT_COPY_T2T_DW_6_swc_mat_aspt_shift  24
#define SDMA_PKT_COPY_T2T_DW_6_SWC_MAT_ASPT(x) (((x) & SDMA_PKT_COPY_T2T_DW_6_swc_mat_aspt_mask) << SDMA_PKT_COPY_T2T_DW_6_swc_mat_aspt_shift)

/*define fow swc_pipe_config fiewd*/
#define SDMA_PKT_COPY_T2T_DW_6_swc_pipe_config_offset 6
#define SDMA_PKT_COPY_T2T_DW_6_swc_pipe_config_mask   0x0000001F
#define SDMA_PKT_COPY_T2T_DW_6_swc_pipe_config_shift  26
#define SDMA_PKT_COPY_T2T_DW_6_SWC_PIPE_CONFIG(x) (((x) & SDMA_PKT_COPY_T2T_DW_6_swc_pipe_config_mask) << SDMA_PKT_COPY_T2T_DW_6_swc_pipe_config_shift)

/*define fow DST_ADDW_WO wowd*/
/*define fow dst_addw_31_0 fiewd*/
#define SDMA_PKT_COPY_T2T_DST_ADDW_WO_dst_addw_31_0_offset 7
#define SDMA_PKT_COPY_T2T_DST_ADDW_WO_dst_addw_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_T2T_DST_ADDW_WO_dst_addw_31_0_shift  0
#define SDMA_PKT_COPY_T2T_DST_ADDW_WO_DST_ADDW_31_0(x) (((x) & SDMA_PKT_COPY_T2T_DST_ADDW_WO_dst_addw_31_0_mask) << SDMA_PKT_COPY_T2T_DST_ADDW_WO_dst_addw_31_0_shift)

/*define fow DST_ADDW_HI wowd*/
/*define fow dst_addw_63_32 fiewd*/
#define SDMA_PKT_COPY_T2T_DST_ADDW_HI_dst_addw_63_32_offset 8
#define SDMA_PKT_COPY_T2T_DST_ADDW_HI_dst_addw_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_T2T_DST_ADDW_HI_dst_addw_63_32_shift  0
#define SDMA_PKT_COPY_T2T_DST_ADDW_HI_DST_ADDW_63_32(x) (((x) & SDMA_PKT_COPY_T2T_DST_ADDW_HI_dst_addw_63_32_mask) << SDMA_PKT_COPY_T2T_DST_ADDW_HI_dst_addw_63_32_shift)

/*define fow DW_9 wowd*/
/*define fow dst_x fiewd*/
#define SDMA_PKT_COPY_T2T_DW_9_dst_x_offset 9
#define SDMA_PKT_COPY_T2T_DW_9_dst_x_mask   0x00003FFF
#define SDMA_PKT_COPY_T2T_DW_9_dst_x_shift  0
#define SDMA_PKT_COPY_T2T_DW_9_DST_X(x) (((x) & SDMA_PKT_COPY_T2T_DW_9_dst_x_mask) << SDMA_PKT_COPY_T2T_DW_9_dst_x_shift)

/*define fow dst_y fiewd*/
#define SDMA_PKT_COPY_T2T_DW_9_dst_y_offset 9
#define SDMA_PKT_COPY_T2T_DW_9_dst_y_mask   0x00003FFF
#define SDMA_PKT_COPY_T2T_DW_9_dst_y_shift  16
#define SDMA_PKT_COPY_T2T_DW_9_DST_Y(x) (((x) & SDMA_PKT_COPY_T2T_DW_9_dst_y_mask) << SDMA_PKT_COPY_T2T_DW_9_dst_y_shift)

/*define fow DW_10 wowd*/
/*define fow dst_z fiewd*/
#define SDMA_PKT_COPY_T2T_DW_10_dst_z_offset 10
#define SDMA_PKT_COPY_T2T_DW_10_dst_z_mask   0x000007FF
#define SDMA_PKT_COPY_T2T_DW_10_dst_z_shift  0
#define SDMA_PKT_COPY_T2T_DW_10_DST_Z(x) (((x) & SDMA_PKT_COPY_T2T_DW_10_dst_z_mask) << SDMA_PKT_COPY_T2T_DW_10_dst_z_shift)

/*define fow dst_pitch_in_tiwe fiewd*/
#define SDMA_PKT_COPY_T2T_DW_10_dst_pitch_in_tiwe_offset 10
#define SDMA_PKT_COPY_T2T_DW_10_dst_pitch_in_tiwe_mask   0x00000FFF
#define SDMA_PKT_COPY_T2T_DW_10_dst_pitch_in_tiwe_shift  16
#define SDMA_PKT_COPY_T2T_DW_10_DST_PITCH_IN_TIWE(x) (((x) & SDMA_PKT_COPY_T2T_DW_10_dst_pitch_in_tiwe_mask) << SDMA_PKT_COPY_T2T_DW_10_dst_pitch_in_tiwe_shift)

/*define fow DW_11 wowd*/
/*define fow dst_swice_pitch fiewd*/
#define SDMA_PKT_COPY_T2T_DW_11_dst_swice_pitch_offset 11
#define SDMA_PKT_COPY_T2T_DW_11_dst_swice_pitch_mask   0x003FFFFF
#define SDMA_PKT_COPY_T2T_DW_11_dst_swice_pitch_shift  0
#define SDMA_PKT_COPY_T2T_DW_11_DST_SWICE_PITCH(x) (((x) & SDMA_PKT_COPY_T2T_DW_11_dst_swice_pitch_mask) << SDMA_PKT_COPY_T2T_DW_11_dst_swice_pitch_shift)

/*define fow DW_12 wowd*/
/*define fow dst_awway_mode fiewd*/
#define SDMA_PKT_COPY_T2T_DW_12_dst_awway_mode_offset 12
#define SDMA_PKT_COPY_T2T_DW_12_dst_awway_mode_mask   0x0000000F
#define SDMA_PKT_COPY_T2T_DW_12_dst_awway_mode_shift  3
#define SDMA_PKT_COPY_T2T_DW_12_DST_AWWAY_MODE(x) (((x) & SDMA_PKT_COPY_T2T_DW_12_dst_awway_mode_mask) << SDMA_PKT_COPY_T2T_DW_12_dst_awway_mode_shift)

/*define fow dst_mit_mode fiewd*/
#define SDMA_PKT_COPY_T2T_DW_12_dst_mit_mode_offset 12
#define SDMA_PKT_COPY_T2T_DW_12_dst_mit_mode_mask   0x00000007
#define SDMA_PKT_COPY_T2T_DW_12_dst_mit_mode_shift  8
#define SDMA_PKT_COPY_T2T_DW_12_DST_MIT_MODE(x) (((x) & SDMA_PKT_COPY_T2T_DW_12_dst_mit_mode_mask) << SDMA_PKT_COPY_T2T_DW_12_dst_mit_mode_shift)

/*define fow dst_tiwespwit_size fiewd*/
#define SDMA_PKT_COPY_T2T_DW_12_dst_tiwespwit_size_offset 12
#define SDMA_PKT_COPY_T2T_DW_12_dst_tiwespwit_size_mask   0x00000007
#define SDMA_PKT_COPY_T2T_DW_12_dst_tiwespwit_size_shift  11
#define SDMA_PKT_COPY_T2T_DW_12_DST_TIWESPWIT_SIZE(x) (((x) & SDMA_PKT_COPY_T2T_DW_12_dst_tiwespwit_size_mask) << SDMA_PKT_COPY_T2T_DW_12_dst_tiwespwit_size_shift)

/*define fow dst_bank_w fiewd*/
#define SDMA_PKT_COPY_T2T_DW_12_dst_bank_w_offset 12
#define SDMA_PKT_COPY_T2T_DW_12_dst_bank_w_mask   0x00000003
#define SDMA_PKT_COPY_T2T_DW_12_dst_bank_w_shift  15
#define SDMA_PKT_COPY_T2T_DW_12_DST_BANK_W(x) (((x) & SDMA_PKT_COPY_T2T_DW_12_dst_bank_w_mask) << SDMA_PKT_COPY_T2T_DW_12_dst_bank_w_shift)

/*define fow dst_bank_h fiewd*/
#define SDMA_PKT_COPY_T2T_DW_12_dst_bank_h_offset 12
#define SDMA_PKT_COPY_T2T_DW_12_dst_bank_h_mask   0x00000003
#define SDMA_PKT_COPY_T2T_DW_12_dst_bank_h_shift  18
#define SDMA_PKT_COPY_T2T_DW_12_DST_BANK_H(x) (((x) & SDMA_PKT_COPY_T2T_DW_12_dst_bank_h_mask) << SDMA_PKT_COPY_T2T_DW_12_dst_bank_h_shift)

/*define fow dst_num_bank fiewd*/
#define SDMA_PKT_COPY_T2T_DW_12_dst_num_bank_offset 12
#define SDMA_PKT_COPY_T2T_DW_12_dst_num_bank_mask   0x00000003
#define SDMA_PKT_COPY_T2T_DW_12_dst_num_bank_shift  21
#define SDMA_PKT_COPY_T2T_DW_12_DST_NUM_BANK(x) (((x) & SDMA_PKT_COPY_T2T_DW_12_dst_num_bank_mask) << SDMA_PKT_COPY_T2T_DW_12_dst_num_bank_shift)

/*define fow dst_mat_aspt fiewd*/
#define SDMA_PKT_COPY_T2T_DW_12_dst_mat_aspt_offset 12
#define SDMA_PKT_COPY_T2T_DW_12_dst_mat_aspt_mask   0x00000003
#define SDMA_PKT_COPY_T2T_DW_12_dst_mat_aspt_shift  24
#define SDMA_PKT_COPY_T2T_DW_12_DST_MAT_ASPT(x) (((x) & SDMA_PKT_COPY_T2T_DW_12_dst_mat_aspt_mask) << SDMA_PKT_COPY_T2T_DW_12_dst_mat_aspt_shift)

/*define fow dst_pipe_config fiewd*/
#define SDMA_PKT_COPY_T2T_DW_12_dst_pipe_config_offset 12
#define SDMA_PKT_COPY_T2T_DW_12_dst_pipe_config_mask   0x0000001F
#define SDMA_PKT_COPY_T2T_DW_12_dst_pipe_config_shift  26
#define SDMA_PKT_COPY_T2T_DW_12_DST_PIPE_CONFIG(x) (((x) & SDMA_PKT_COPY_T2T_DW_12_dst_pipe_config_mask) << SDMA_PKT_COPY_T2T_DW_12_dst_pipe_config_shift)

/*define fow DW_13 wowd*/
/*define fow wect_x fiewd*/
#define SDMA_PKT_COPY_T2T_DW_13_wect_x_offset 13
#define SDMA_PKT_COPY_T2T_DW_13_wect_x_mask   0x00003FFF
#define SDMA_PKT_COPY_T2T_DW_13_wect_x_shift  0
#define SDMA_PKT_COPY_T2T_DW_13_WECT_X(x) (((x) & SDMA_PKT_COPY_T2T_DW_13_wect_x_mask) << SDMA_PKT_COPY_T2T_DW_13_wect_x_shift)

/*define fow wect_y fiewd*/
#define SDMA_PKT_COPY_T2T_DW_13_wect_y_offset 13
#define SDMA_PKT_COPY_T2T_DW_13_wect_y_mask   0x00003FFF
#define SDMA_PKT_COPY_T2T_DW_13_wect_y_shift  16
#define SDMA_PKT_COPY_T2T_DW_13_WECT_Y(x) (((x) & SDMA_PKT_COPY_T2T_DW_13_wect_y_mask) << SDMA_PKT_COPY_T2T_DW_13_wect_y_shift)

/*define fow DW_14 wowd*/
/*define fow wect_z fiewd*/
#define SDMA_PKT_COPY_T2T_DW_14_wect_z_offset 14
#define SDMA_PKT_COPY_T2T_DW_14_wect_z_mask   0x000007FF
#define SDMA_PKT_COPY_T2T_DW_14_wect_z_shift  0
#define SDMA_PKT_COPY_T2T_DW_14_WECT_Z(x) (((x) & SDMA_PKT_COPY_T2T_DW_14_wect_z_mask) << SDMA_PKT_COPY_T2T_DW_14_wect_z_shift)

/*define fow dst_sw fiewd*/
#define SDMA_PKT_COPY_T2T_DW_14_dst_sw_offset 14
#define SDMA_PKT_COPY_T2T_DW_14_dst_sw_mask   0x00000003
#define SDMA_PKT_COPY_T2T_DW_14_dst_sw_shift  16
#define SDMA_PKT_COPY_T2T_DW_14_DST_SW(x) (((x) & SDMA_PKT_COPY_T2T_DW_14_dst_sw_mask) << SDMA_PKT_COPY_T2T_DW_14_dst_sw_shift)

/*define fow swc_sw fiewd*/
#define SDMA_PKT_COPY_T2T_DW_14_swc_sw_offset 14
#define SDMA_PKT_COPY_T2T_DW_14_swc_sw_mask   0x00000003
#define SDMA_PKT_COPY_T2T_DW_14_swc_sw_shift  24
#define SDMA_PKT_COPY_T2T_DW_14_SWC_SW(x) (((x) & SDMA_PKT_COPY_T2T_DW_14_swc_sw_mask) << SDMA_PKT_COPY_T2T_DW_14_swc_sw_shift)


/*
** Definitions fow SDMA_PKT_COPY_TIWED_SUBWIN packet
*/

/*define fow HEADEW wowd*/
/*define fow op fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_HEADEW_op_offset 0
#define SDMA_PKT_COPY_TIWED_SUBWIN_HEADEW_op_mask   0x000000FF
#define SDMA_PKT_COPY_TIWED_SUBWIN_HEADEW_op_shift  0
#define SDMA_PKT_COPY_TIWED_SUBWIN_HEADEW_OP(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_HEADEW_op_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_HEADEW_op_shift)

/*define fow sub_op fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_HEADEW_sub_op_offset 0
#define SDMA_PKT_COPY_TIWED_SUBWIN_HEADEW_sub_op_mask   0x000000FF
#define SDMA_PKT_COPY_TIWED_SUBWIN_HEADEW_sub_op_shift  8
#define SDMA_PKT_COPY_TIWED_SUBWIN_HEADEW_SUB_OP(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_HEADEW_sub_op_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_HEADEW_sub_op_shift)

/*define fow detiwe fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_HEADEW_detiwe_offset 0
#define SDMA_PKT_COPY_TIWED_SUBWIN_HEADEW_detiwe_mask   0x00000001
#define SDMA_PKT_COPY_TIWED_SUBWIN_HEADEW_detiwe_shift  31
#define SDMA_PKT_COPY_TIWED_SUBWIN_HEADEW_DETIWE(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_HEADEW_detiwe_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_HEADEW_detiwe_shift)

/*define fow TIWED_ADDW_WO wowd*/
/*define fow tiwed_addw_31_0 fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_TIWED_ADDW_WO_tiwed_addw_31_0_offset 1
#define SDMA_PKT_COPY_TIWED_SUBWIN_TIWED_ADDW_WO_tiwed_addw_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_TIWED_SUBWIN_TIWED_ADDW_WO_tiwed_addw_31_0_shift  0
#define SDMA_PKT_COPY_TIWED_SUBWIN_TIWED_ADDW_WO_TIWED_ADDW_31_0(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_TIWED_ADDW_WO_tiwed_addw_31_0_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_TIWED_ADDW_WO_tiwed_addw_31_0_shift)

/*define fow TIWED_ADDW_HI wowd*/
/*define fow tiwed_addw_63_32 fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_TIWED_ADDW_HI_tiwed_addw_63_32_offset 2
#define SDMA_PKT_COPY_TIWED_SUBWIN_TIWED_ADDW_HI_tiwed_addw_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_TIWED_SUBWIN_TIWED_ADDW_HI_tiwed_addw_63_32_shift  0
#define SDMA_PKT_COPY_TIWED_SUBWIN_TIWED_ADDW_HI_TIWED_ADDW_63_32(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_TIWED_ADDW_HI_tiwed_addw_63_32_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_TIWED_ADDW_HI_tiwed_addw_63_32_shift)

/*define fow DW_3 wowd*/
/*define fow tiwed_x fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_3_tiwed_x_offset 3
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_3_tiwed_x_mask   0x00003FFF
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_3_tiwed_x_shift  0
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_3_TIWED_X(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_DW_3_tiwed_x_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_DW_3_tiwed_x_shift)

/*define fow tiwed_y fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_3_tiwed_y_offset 3
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_3_tiwed_y_mask   0x00003FFF
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_3_tiwed_y_shift  16
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_3_TIWED_Y(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_DW_3_tiwed_y_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_DW_3_tiwed_y_shift)

/*define fow DW_4 wowd*/
/*define fow tiwed_z fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_4_tiwed_z_offset 4
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_4_tiwed_z_mask   0x000007FF
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_4_tiwed_z_shift  0
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_4_TIWED_Z(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_DW_4_tiwed_z_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_DW_4_tiwed_z_shift)

/*define fow pitch_in_tiwe fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_4_pitch_in_tiwe_offset 4
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_4_pitch_in_tiwe_mask   0x00000FFF
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_4_pitch_in_tiwe_shift  16
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_4_PITCH_IN_TIWE(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_DW_4_pitch_in_tiwe_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_DW_4_pitch_in_tiwe_shift)

/*define fow DW_5 wowd*/
/*define fow swice_pitch fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_5_swice_pitch_offset 5
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_5_swice_pitch_mask   0x003FFFFF
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_5_swice_pitch_shift  0
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_5_SWICE_PITCH(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_DW_5_swice_pitch_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_DW_5_swice_pitch_shift)

/*define fow DW_6 wowd*/
/*define fow ewement_size fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_ewement_size_offset 6
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_ewement_size_mask   0x00000007
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_ewement_size_shift  0
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_EWEMENT_SIZE(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_ewement_size_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_ewement_size_shift)

/*define fow awway_mode fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_awway_mode_offset 6
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_awway_mode_mask   0x0000000F
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_awway_mode_shift  3
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_AWWAY_MODE(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_awway_mode_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_awway_mode_shift)

/*define fow mit_mode fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_mit_mode_offset 6
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_mit_mode_mask   0x00000007
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_mit_mode_shift  8
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_MIT_MODE(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_mit_mode_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_mit_mode_shift)

/*define fow tiwespwit_size fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_tiwespwit_size_offset 6
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_tiwespwit_size_mask   0x00000007
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_tiwespwit_size_shift  11
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_TIWESPWIT_SIZE(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_tiwespwit_size_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_tiwespwit_size_shift)

/*define fow bank_w fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_bank_w_offset 6
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_bank_w_mask   0x00000003
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_bank_w_shift  15
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_BANK_W(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_bank_w_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_bank_w_shift)

/*define fow bank_h fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_bank_h_offset 6
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_bank_h_mask   0x00000003
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_bank_h_shift  18
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_BANK_H(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_bank_h_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_bank_h_shift)

/*define fow num_bank fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_num_bank_offset 6
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_num_bank_mask   0x00000003
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_num_bank_shift  21
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_NUM_BANK(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_num_bank_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_num_bank_shift)

/*define fow mat_aspt fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_mat_aspt_offset 6
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_mat_aspt_mask   0x00000003
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_mat_aspt_shift  24
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_MAT_ASPT(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_mat_aspt_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_mat_aspt_shift)

/*define fow pipe_config fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_pipe_config_offset 6
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_pipe_config_mask   0x0000001F
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_pipe_config_shift  26
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_PIPE_CONFIG(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_pipe_config_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_DW_6_pipe_config_shift)

/*define fow WINEAW_ADDW_WO wowd*/
/*define fow wineaw_addw_31_0 fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_WINEAW_ADDW_WO_wineaw_addw_31_0_offset 7
#define SDMA_PKT_COPY_TIWED_SUBWIN_WINEAW_ADDW_WO_wineaw_addw_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_TIWED_SUBWIN_WINEAW_ADDW_WO_wineaw_addw_31_0_shift  0
#define SDMA_PKT_COPY_TIWED_SUBWIN_WINEAW_ADDW_WO_WINEAW_ADDW_31_0(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_WINEAW_ADDW_WO_wineaw_addw_31_0_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_WINEAW_ADDW_WO_wineaw_addw_31_0_shift)

/*define fow WINEAW_ADDW_HI wowd*/
/*define fow wineaw_addw_63_32 fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_WINEAW_ADDW_HI_wineaw_addw_63_32_offset 8
#define SDMA_PKT_COPY_TIWED_SUBWIN_WINEAW_ADDW_HI_wineaw_addw_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_TIWED_SUBWIN_WINEAW_ADDW_HI_wineaw_addw_63_32_shift  0
#define SDMA_PKT_COPY_TIWED_SUBWIN_WINEAW_ADDW_HI_WINEAW_ADDW_63_32(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_WINEAW_ADDW_HI_wineaw_addw_63_32_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_WINEAW_ADDW_HI_wineaw_addw_63_32_shift)

/*define fow DW_9 wowd*/
/*define fow wineaw_x fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_9_wineaw_x_offset 9
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_9_wineaw_x_mask   0x00003FFF
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_9_wineaw_x_shift  0
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_9_WINEAW_X(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_DW_9_wineaw_x_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_DW_9_wineaw_x_shift)

/*define fow wineaw_y fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_9_wineaw_y_offset 9
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_9_wineaw_y_mask   0x00003FFF
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_9_wineaw_y_shift  16
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_9_WINEAW_Y(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_DW_9_wineaw_y_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_DW_9_wineaw_y_shift)

/*define fow DW_10 wowd*/
/*define fow wineaw_z fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_10_wineaw_z_offset 10
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_10_wineaw_z_mask   0x000007FF
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_10_wineaw_z_shift  0
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_10_WINEAW_Z(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_DW_10_wineaw_z_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_DW_10_wineaw_z_shift)

/*define fow wineaw_pitch fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_10_wineaw_pitch_offset 10
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_10_wineaw_pitch_mask   0x00003FFF
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_10_wineaw_pitch_shift  16
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_10_WINEAW_PITCH(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_DW_10_wineaw_pitch_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_DW_10_wineaw_pitch_shift)

/*define fow DW_11 wowd*/
/*define fow wineaw_swice_pitch fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_11_wineaw_swice_pitch_offset 11
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_11_wineaw_swice_pitch_mask   0x0FFFFFFF
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_11_wineaw_swice_pitch_shift  0
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_11_WINEAW_SWICE_PITCH(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_DW_11_wineaw_swice_pitch_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_DW_11_wineaw_swice_pitch_shift)

/*define fow DW_12 wowd*/
/*define fow wect_x fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_12_wect_x_offset 12
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_12_wect_x_mask   0x00003FFF
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_12_wect_x_shift  0
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_12_WECT_X(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_DW_12_wect_x_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_DW_12_wect_x_shift)

/*define fow wect_y fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_12_wect_y_offset 12
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_12_wect_y_mask   0x00003FFF
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_12_wect_y_shift  16
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_12_WECT_Y(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_DW_12_wect_y_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_DW_12_wect_y_shift)

/*define fow DW_13 wowd*/
/*define fow wect_z fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_13_wect_z_offset 13
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_13_wect_z_mask   0x000007FF
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_13_wect_z_shift  0
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_13_WECT_Z(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_DW_13_wect_z_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_DW_13_wect_z_shift)

/*define fow wineaw_sw fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_13_wineaw_sw_offset 13
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_13_wineaw_sw_mask   0x00000003
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_13_wineaw_sw_shift  16
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_13_WINEAW_SW(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_DW_13_wineaw_sw_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_DW_13_wineaw_sw_shift)

/*define fow tiwe_sw fiewd*/
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_13_tiwe_sw_offset 13
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_13_tiwe_sw_mask   0x00000003
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_13_tiwe_sw_shift  24
#define SDMA_PKT_COPY_TIWED_SUBWIN_DW_13_TIWE_SW(x) (((x) & SDMA_PKT_COPY_TIWED_SUBWIN_DW_13_tiwe_sw_mask) << SDMA_PKT_COPY_TIWED_SUBWIN_DW_13_tiwe_sw_shift)


/*
** Definitions fow SDMA_PKT_COPY_STWUCT packet
*/

/*define fow HEADEW wowd*/
/*define fow op fiewd*/
#define SDMA_PKT_COPY_STWUCT_HEADEW_op_offset 0
#define SDMA_PKT_COPY_STWUCT_HEADEW_op_mask   0x000000FF
#define SDMA_PKT_COPY_STWUCT_HEADEW_op_shift  0
#define SDMA_PKT_COPY_STWUCT_HEADEW_OP(x) (((x) & SDMA_PKT_COPY_STWUCT_HEADEW_op_mask) << SDMA_PKT_COPY_STWUCT_HEADEW_op_shift)

/*define fow sub_op fiewd*/
#define SDMA_PKT_COPY_STWUCT_HEADEW_sub_op_offset 0
#define SDMA_PKT_COPY_STWUCT_HEADEW_sub_op_mask   0x000000FF
#define SDMA_PKT_COPY_STWUCT_HEADEW_sub_op_shift  8
#define SDMA_PKT_COPY_STWUCT_HEADEW_SUB_OP(x) (((x) & SDMA_PKT_COPY_STWUCT_HEADEW_sub_op_mask) << SDMA_PKT_COPY_STWUCT_HEADEW_sub_op_shift)

/*define fow detiwe fiewd*/
#define SDMA_PKT_COPY_STWUCT_HEADEW_detiwe_offset 0
#define SDMA_PKT_COPY_STWUCT_HEADEW_detiwe_mask   0x00000001
#define SDMA_PKT_COPY_STWUCT_HEADEW_detiwe_shift  31
#define SDMA_PKT_COPY_STWUCT_HEADEW_DETIWE(x) (((x) & SDMA_PKT_COPY_STWUCT_HEADEW_detiwe_mask) << SDMA_PKT_COPY_STWUCT_HEADEW_detiwe_shift)

/*define fow SB_ADDW_WO wowd*/
/*define fow sb_addw_31_0 fiewd*/
#define SDMA_PKT_COPY_STWUCT_SB_ADDW_WO_sb_addw_31_0_offset 1
#define SDMA_PKT_COPY_STWUCT_SB_ADDW_WO_sb_addw_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_STWUCT_SB_ADDW_WO_sb_addw_31_0_shift  0
#define SDMA_PKT_COPY_STWUCT_SB_ADDW_WO_SB_ADDW_31_0(x) (((x) & SDMA_PKT_COPY_STWUCT_SB_ADDW_WO_sb_addw_31_0_mask) << SDMA_PKT_COPY_STWUCT_SB_ADDW_WO_sb_addw_31_0_shift)

/*define fow SB_ADDW_HI wowd*/
/*define fow sb_addw_63_32 fiewd*/
#define SDMA_PKT_COPY_STWUCT_SB_ADDW_HI_sb_addw_63_32_offset 2
#define SDMA_PKT_COPY_STWUCT_SB_ADDW_HI_sb_addw_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_STWUCT_SB_ADDW_HI_sb_addw_63_32_shift  0
#define SDMA_PKT_COPY_STWUCT_SB_ADDW_HI_SB_ADDW_63_32(x) (((x) & SDMA_PKT_COPY_STWUCT_SB_ADDW_HI_sb_addw_63_32_mask) << SDMA_PKT_COPY_STWUCT_SB_ADDW_HI_sb_addw_63_32_shift)

/*define fow STAWT_INDEX wowd*/
/*define fow stawt_index fiewd*/
#define SDMA_PKT_COPY_STWUCT_STAWT_INDEX_stawt_index_offset 3
#define SDMA_PKT_COPY_STWUCT_STAWT_INDEX_stawt_index_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_STWUCT_STAWT_INDEX_stawt_index_shift  0
#define SDMA_PKT_COPY_STWUCT_STAWT_INDEX_STAWT_INDEX(x) (((x) & SDMA_PKT_COPY_STWUCT_STAWT_INDEX_stawt_index_mask) << SDMA_PKT_COPY_STWUCT_STAWT_INDEX_stawt_index_shift)

/*define fow COUNT wowd*/
/*define fow count fiewd*/
#define SDMA_PKT_COPY_STWUCT_COUNT_count_offset 4
#define SDMA_PKT_COPY_STWUCT_COUNT_count_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_STWUCT_COUNT_count_shift  0
#define SDMA_PKT_COPY_STWUCT_COUNT_COUNT(x) (((x) & SDMA_PKT_COPY_STWUCT_COUNT_count_mask) << SDMA_PKT_COPY_STWUCT_COUNT_count_shift)

/*define fow DW_5 wowd*/
/*define fow stwide fiewd*/
#define SDMA_PKT_COPY_STWUCT_DW_5_stwide_offset 5
#define SDMA_PKT_COPY_STWUCT_DW_5_stwide_mask   0x000007FF
#define SDMA_PKT_COPY_STWUCT_DW_5_stwide_shift  0
#define SDMA_PKT_COPY_STWUCT_DW_5_STWIDE(x) (((x) & SDMA_PKT_COPY_STWUCT_DW_5_stwide_mask) << SDMA_PKT_COPY_STWUCT_DW_5_stwide_shift)

/*define fow stwuct_sw fiewd*/
#define SDMA_PKT_COPY_STWUCT_DW_5_stwuct_sw_offset 5
#define SDMA_PKT_COPY_STWUCT_DW_5_stwuct_sw_mask   0x00000003
#define SDMA_PKT_COPY_STWUCT_DW_5_stwuct_sw_shift  16
#define SDMA_PKT_COPY_STWUCT_DW_5_STWUCT_SW(x) (((x) & SDMA_PKT_COPY_STWUCT_DW_5_stwuct_sw_mask) << SDMA_PKT_COPY_STWUCT_DW_5_stwuct_sw_shift)

/*define fow stwuct_ha fiewd*/
#define SDMA_PKT_COPY_STWUCT_DW_5_stwuct_ha_offset 5
#define SDMA_PKT_COPY_STWUCT_DW_5_stwuct_ha_mask   0x00000001
#define SDMA_PKT_COPY_STWUCT_DW_5_stwuct_ha_shift  22
#define SDMA_PKT_COPY_STWUCT_DW_5_STWUCT_HA(x) (((x) & SDMA_PKT_COPY_STWUCT_DW_5_stwuct_ha_mask) << SDMA_PKT_COPY_STWUCT_DW_5_stwuct_ha_shift)

/*define fow wineaw_sw fiewd*/
#define SDMA_PKT_COPY_STWUCT_DW_5_wineaw_sw_offset 5
#define SDMA_PKT_COPY_STWUCT_DW_5_wineaw_sw_mask   0x00000003
#define SDMA_PKT_COPY_STWUCT_DW_5_wineaw_sw_shift  24
#define SDMA_PKT_COPY_STWUCT_DW_5_WINEAW_SW(x) (((x) & SDMA_PKT_COPY_STWUCT_DW_5_wineaw_sw_mask) << SDMA_PKT_COPY_STWUCT_DW_5_wineaw_sw_shift)

/*define fow wineaw_ha fiewd*/
#define SDMA_PKT_COPY_STWUCT_DW_5_wineaw_ha_offset 5
#define SDMA_PKT_COPY_STWUCT_DW_5_wineaw_ha_mask   0x00000001
#define SDMA_PKT_COPY_STWUCT_DW_5_wineaw_ha_shift  30
#define SDMA_PKT_COPY_STWUCT_DW_5_WINEAW_HA(x) (((x) & SDMA_PKT_COPY_STWUCT_DW_5_wineaw_ha_mask) << SDMA_PKT_COPY_STWUCT_DW_5_wineaw_ha_shift)

/*define fow WINEAW_ADDW_WO wowd*/
/*define fow wineaw_addw_31_0 fiewd*/
#define SDMA_PKT_COPY_STWUCT_WINEAW_ADDW_WO_wineaw_addw_31_0_offset 6
#define SDMA_PKT_COPY_STWUCT_WINEAW_ADDW_WO_wineaw_addw_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_STWUCT_WINEAW_ADDW_WO_wineaw_addw_31_0_shift  0
#define SDMA_PKT_COPY_STWUCT_WINEAW_ADDW_WO_WINEAW_ADDW_31_0(x) (((x) & SDMA_PKT_COPY_STWUCT_WINEAW_ADDW_WO_wineaw_addw_31_0_mask) << SDMA_PKT_COPY_STWUCT_WINEAW_ADDW_WO_wineaw_addw_31_0_shift)

/*define fow WINEAW_ADDW_HI wowd*/
/*define fow wineaw_addw_63_32 fiewd*/
#define SDMA_PKT_COPY_STWUCT_WINEAW_ADDW_HI_wineaw_addw_63_32_offset 7
#define SDMA_PKT_COPY_STWUCT_WINEAW_ADDW_HI_wineaw_addw_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_COPY_STWUCT_WINEAW_ADDW_HI_wineaw_addw_63_32_shift  0
#define SDMA_PKT_COPY_STWUCT_WINEAW_ADDW_HI_WINEAW_ADDW_63_32(x) (((x) & SDMA_PKT_COPY_STWUCT_WINEAW_ADDW_HI_wineaw_addw_63_32_mask) << SDMA_PKT_COPY_STWUCT_WINEAW_ADDW_HI_wineaw_addw_63_32_shift)


/*
** Definitions fow SDMA_PKT_WWITE_UNTIWED packet
*/

/*define fow HEADEW wowd*/
/*define fow op fiewd*/
#define SDMA_PKT_WWITE_UNTIWED_HEADEW_op_offset 0
#define SDMA_PKT_WWITE_UNTIWED_HEADEW_op_mask   0x000000FF
#define SDMA_PKT_WWITE_UNTIWED_HEADEW_op_shift  0
#define SDMA_PKT_WWITE_UNTIWED_HEADEW_OP(x) (((x) & SDMA_PKT_WWITE_UNTIWED_HEADEW_op_mask) << SDMA_PKT_WWITE_UNTIWED_HEADEW_op_shift)

/*define fow sub_op fiewd*/
#define SDMA_PKT_WWITE_UNTIWED_HEADEW_sub_op_offset 0
#define SDMA_PKT_WWITE_UNTIWED_HEADEW_sub_op_mask   0x000000FF
#define SDMA_PKT_WWITE_UNTIWED_HEADEW_sub_op_shift  8
#define SDMA_PKT_WWITE_UNTIWED_HEADEW_SUB_OP(x) (((x) & SDMA_PKT_WWITE_UNTIWED_HEADEW_sub_op_mask) << SDMA_PKT_WWITE_UNTIWED_HEADEW_sub_op_shift)

/*define fow DST_ADDW_WO wowd*/
/*define fow dst_addw_31_0 fiewd*/
#define SDMA_PKT_WWITE_UNTIWED_DST_ADDW_WO_dst_addw_31_0_offset 1
#define SDMA_PKT_WWITE_UNTIWED_DST_ADDW_WO_dst_addw_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_WWITE_UNTIWED_DST_ADDW_WO_dst_addw_31_0_shift  0
#define SDMA_PKT_WWITE_UNTIWED_DST_ADDW_WO_DST_ADDW_31_0(x) (((x) & SDMA_PKT_WWITE_UNTIWED_DST_ADDW_WO_dst_addw_31_0_mask) << SDMA_PKT_WWITE_UNTIWED_DST_ADDW_WO_dst_addw_31_0_shift)

/*define fow DST_ADDW_HI wowd*/
/*define fow dst_addw_63_32 fiewd*/
#define SDMA_PKT_WWITE_UNTIWED_DST_ADDW_HI_dst_addw_63_32_offset 2
#define SDMA_PKT_WWITE_UNTIWED_DST_ADDW_HI_dst_addw_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_WWITE_UNTIWED_DST_ADDW_HI_dst_addw_63_32_shift  0
#define SDMA_PKT_WWITE_UNTIWED_DST_ADDW_HI_DST_ADDW_63_32(x) (((x) & SDMA_PKT_WWITE_UNTIWED_DST_ADDW_HI_dst_addw_63_32_mask) << SDMA_PKT_WWITE_UNTIWED_DST_ADDW_HI_dst_addw_63_32_shift)

/*define fow DW_3 wowd*/
/*define fow count fiewd*/
#define SDMA_PKT_WWITE_UNTIWED_DW_3_count_offset 3
#define SDMA_PKT_WWITE_UNTIWED_DW_3_count_mask   0x003FFFFF
#define SDMA_PKT_WWITE_UNTIWED_DW_3_count_shift  0
#define SDMA_PKT_WWITE_UNTIWED_DW_3_COUNT(x) (((x) & SDMA_PKT_WWITE_UNTIWED_DW_3_count_mask) << SDMA_PKT_WWITE_UNTIWED_DW_3_count_shift)

/*define fow sw fiewd*/
#define SDMA_PKT_WWITE_UNTIWED_DW_3_sw_offset 3
#define SDMA_PKT_WWITE_UNTIWED_DW_3_sw_mask   0x00000003
#define SDMA_PKT_WWITE_UNTIWED_DW_3_sw_shift  24
#define SDMA_PKT_WWITE_UNTIWED_DW_3_SW(x) (((x) & SDMA_PKT_WWITE_UNTIWED_DW_3_sw_mask) << SDMA_PKT_WWITE_UNTIWED_DW_3_sw_shift)

/*define fow DATA0 wowd*/
/*define fow data0 fiewd*/
#define SDMA_PKT_WWITE_UNTIWED_DATA0_data0_offset 4
#define SDMA_PKT_WWITE_UNTIWED_DATA0_data0_mask   0xFFFFFFFF
#define SDMA_PKT_WWITE_UNTIWED_DATA0_data0_shift  0
#define SDMA_PKT_WWITE_UNTIWED_DATA0_DATA0(x) (((x) & SDMA_PKT_WWITE_UNTIWED_DATA0_data0_mask) << SDMA_PKT_WWITE_UNTIWED_DATA0_data0_shift)


/*
** Definitions fow SDMA_PKT_WWITE_TIWED packet
*/

/*define fow HEADEW wowd*/
/*define fow op fiewd*/
#define SDMA_PKT_WWITE_TIWED_HEADEW_op_offset 0
#define SDMA_PKT_WWITE_TIWED_HEADEW_op_mask   0x000000FF
#define SDMA_PKT_WWITE_TIWED_HEADEW_op_shift  0
#define SDMA_PKT_WWITE_TIWED_HEADEW_OP(x) (((x) & SDMA_PKT_WWITE_TIWED_HEADEW_op_mask) << SDMA_PKT_WWITE_TIWED_HEADEW_op_shift)

/*define fow sub_op fiewd*/
#define SDMA_PKT_WWITE_TIWED_HEADEW_sub_op_offset 0
#define SDMA_PKT_WWITE_TIWED_HEADEW_sub_op_mask   0x000000FF
#define SDMA_PKT_WWITE_TIWED_HEADEW_sub_op_shift  8
#define SDMA_PKT_WWITE_TIWED_HEADEW_SUB_OP(x) (((x) & SDMA_PKT_WWITE_TIWED_HEADEW_sub_op_mask) << SDMA_PKT_WWITE_TIWED_HEADEW_sub_op_shift)

/*define fow DST_ADDW_WO wowd*/
/*define fow dst_addw_31_0 fiewd*/
#define SDMA_PKT_WWITE_TIWED_DST_ADDW_WO_dst_addw_31_0_offset 1
#define SDMA_PKT_WWITE_TIWED_DST_ADDW_WO_dst_addw_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_WWITE_TIWED_DST_ADDW_WO_dst_addw_31_0_shift  0
#define SDMA_PKT_WWITE_TIWED_DST_ADDW_WO_DST_ADDW_31_0(x) (((x) & SDMA_PKT_WWITE_TIWED_DST_ADDW_WO_dst_addw_31_0_mask) << SDMA_PKT_WWITE_TIWED_DST_ADDW_WO_dst_addw_31_0_shift)

/*define fow DST_ADDW_HI wowd*/
/*define fow dst_addw_63_32 fiewd*/
#define SDMA_PKT_WWITE_TIWED_DST_ADDW_HI_dst_addw_63_32_offset 2
#define SDMA_PKT_WWITE_TIWED_DST_ADDW_HI_dst_addw_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_WWITE_TIWED_DST_ADDW_HI_dst_addw_63_32_shift  0
#define SDMA_PKT_WWITE_TIWED_DST_ADDW_HI_DST_ADDW_63_32(x) (((x) & SDMA_PKT_WWITE_TIWED_DST_ADDW_HI_dst_addw_63_32_mask) << SDMA_PKT_WWITE_TIWED_DST_ADDW_HI_dst_addw_63_32_shift)

/*define fow DW_3 wowd*/
/*define fow pitch_in_tiwe fiewd*/
#define SDMA_PKT_WWITE_TIWED_DW_3_pitch_in_tiwe_offset 3
#define SDMA_PKT_WWITE_TIWED_DW_3_pitch_in_tiwe_mask   0x000007FF
#define SDMA_PKT_WWITE_TIWED_DW_3_pitch_in_tiwe_shift  0
#define SDMA_PKT_WWITE_TIWED_DW_3_PITCH_IN_TIWE(x) (((x) & SDMA_PKT_WWITE_TIWED_DW_3_pitch_in_tiwe_mask) << SDMA_PKT_WWITE_TIWED_DW_3_pitch_in_tiwe_shift)

/*define fow height fiewd*/
#define SDMA_PKT_WWITE_TIWED_DW_3_height_offset 3
#define SDMA_PKT_WWITE_TIWED_DW_3_height_mask   0x00003FFF
#define SDMA_PKT_WWITE_TIWED_DW_3_height_shift  16
#define SDMA_PKT_WWITE_TIWED_DW_3_HEIGHT(x) (((x) & SDMA_PKT_WWITE_TIWED_DW_3_height_mask) << SDMA_PKT_WWITE_TIWED_DW_3_height_shift)

/*define fow DW_4 wowd*/
/*define fow swice_pitch fiewd*/
#define SDMA_PKT_WWITE_TIWED_DW_4_swice_pitch_offset 4
#define SDMA_PKT_WWITE_TIWED_DW_4_swice_pitch_mask   0x003FFFFF
#define SDMA_PKT_WWITE_TIWED_DW_4_swice_pitch_shift  0
#define SDMA_PKT_WWITE_TIWED_DW_4_SWICE_PITCH(x) (((x) & SDMA_PKT_WWITE_TIWED_DW_4_swice_pitch_mask) << SDMA_PKT_WWITE_TIWED_DW_4_swice_pitch_shift)

/*define fow DW_5 wowd*/
/*define fow ewement_size fiewd*/
#define SDMA_PKT_WWITE_TIWED_DW_5_ewement_size_offset 5
#define SDMA_PKT_WWITE_TIWED_DW_5_ewement_size_mask   0x00000007
#define SDMA_PKT_WWITE_TIWED_DW_5_ewement_size_shift  0
#define SDMA_PKT_WWITE_TIWED_DW_5_EWEMENT_SIZE(x) (((x) & SDMA_PKT_WWITE_TIWED_DW_5_ewement_size_mask) << SDMA_PKT_WWITE_TIWED_DW_5_ewement_size_shift)

/*define fow awway_mode fiewd*/
#define SDMA_PKT_WWITE_TIWED_DW_5_awway_mode_offset 5
#define SDMA_PKT_WWITE_TIWED_DW_5_awway_mode_mask   0x0000000F
#define SDMA_PKT_WWITE_TIWED_DW_5_awway_mode_shift  3
#define SDMA_PKT_WWITE_TIWED_DW_5_AWWAY_MODE(x) (((x) & SDMA_PKT_WWITE_TIWED_DW_5_awway_mode_mask) << SDMA_PKT_WWITE_TIWED_DW_5_awway_mode_shift)

/*define fow mit_mode fiewd*/
#define SDMA_PKT_WWITE_TIWED_DW_5_mit_mode_offset 5
#define SDMA_PKT_WWITE_TIWED_DW_5_mit_mode_mask   0x00000007
#define SDMA_PKT_WWITE_TIWED_DW_5_mit_mode_shift  8
#define SDMA_PKT_WWITE_TIWED_DW_5_MIT_MODE(x) (((x) & SDMA_PKT_WWITE_TIWED_DW_5_mit_mode_mask) << SDMA_PKT_WWITE_TIWED_DW_5_mit_mode_shift)

/*define fow tiwespwit_size fiewd*/
#define SDMA_PKT_WWITE_TIWED_DW_5_tiwespwit_size_offset 5
#define SDMA_PKT_WWITE_TIWED_DW_5_tiwespwit_size_mask   0x00000007
#define SDMA_PKT_WWITE_TIWED_DW_5_tiwespwit_size_shift  11
#define SDMA_PKT_WWITE_TIWED_DW_5_TIWESPWIT_SIZE(x) (((x) & SDMA_PKT_WWITE_TIWED_DW_5_tiwespwit_size_mask) << SDMA_PKT_WWITE_TIWED_DW_5_tiwespwit_size_shift)

/*define fow bank_w fiewd*/
#define SDMA_PKT_WWITE_TIWED_DW_5_bank_w_offset 5
#define SDMA_PKT_WWITE_TIWED_DW_5_bank_w_mask   0x00000003
#define SDMA_PKT_WWITE_TIWED_DW_5_bank_w_shift  15
#define SDMA_PKT_WWITE_TIWED_DW_5_BANK_W(x) (((x) & SDMA_PKT_WWITE_TIWED_DW_5_bank_w_mask) << SDMA_PKT_WWITE_TIWED_DW_5_bank_w_shift)

/*define fow bank_h fiewd*/
#define SDMA_PKT_WWITE_TIWED_DW_5_bank_h_offset 5
#define SDMA_PKT_WWITE_TIWED_DW_5_bank_h_mask   0x00000003
#define SDMA_PKT_WWITE_TIWED_DW_5_bank_h_shift  18
#define SDMA_PKT_WWITE_TIWED_DW_5_BANK_H(x) (((x) & SDMA_PKT_WWITE_TIWED_DW_5_bank_h_mask) << SDMA_PKT_WWITE_TIWED_DW_5_bank_h_shift)

/*define fow num_bank fiewd*/
#define SDMA_PKT_WWITE_TIWED_DW_5_num_bank_offset 5
#define SDMA_PKT_WWITE_TIWED_DW_5_num_bank_mask   0x00000003
#define SDMA_PKT_WWITE_TIWED_DW_5_num_bank_shift  21
#define SDMA_PKT_WWITE_TIWED_DW_5_NUM_BANK(x) (((x) & SDMA_PKT_WWITE_TIWED_DW_5_num_bank_mask) << SDMA_PKT_WWITE_TIWED_DW_5_num_bank_shift)

/*define fow mat_aspt fiewd*/
#define SDMA_PKT_WWITE_TIWED_DW_5_mat_aspt_offset 5
#define SDMA_PKT_WWITE_TIWED_DW_5_mat_aspt_mask   0x00000003
#define SDMA_PKT_WWITE_TIWED_DW_5_mat_aspt_shift  24
#define SDMA_PKT_WWITE_TIWED_DW_5_MAT_ASPT(x) (((x) & SDMA_PKT_WWITE_TIWED_DW_5_mat_aspt_mask) << SDMA_PKT_WWITE_TIWED_DW_5_mat_aspt_shift)

/*define fow pipe_config fiewd*/
#define SDMA_PKT_WWITE_TIWED_DW_5_pipe_config_offset 5
#define SDMA_PKT_WWITE_TIWED_DW_5_pipe_config_mask   0x0000001F
#define SDMA_PKT_WWITE_TIWED_DW_5_pipe_config_shift  26
#define SDMA_PKT_WWITE_TIWED_DW_5_PIPE_CONFIG(x) (((x) & SDMA_PKT_WWITE_TIWED_DW_5_pipe_config_mask) << SDMA_PKT_WWITE_TIWED_DW_5_pipe_config_shift)

/*define fow DW_6 wowd*/
/*define fow x fiewd*/
#define SDMA_PKT_WWITE_TIWED_DW_6_x_offset 6
#define SDMA_PKT_WWITE_TIWED_DW_6_x_mask   0x00003FFF
#define SDMA_PKT_WWITE_TIWED_DW_6_x_shift  0
#define SDMA_PKT_WWITE_TIWED_DW_6_X(x) (((x) & SDMA_PKT_WWITE_TIWED_DW_6_x_mask) << SDMA_PKT_WWITE_TIWED_DW_6_x_shift)

/*define fow y fiewd*/
#define SDMA_PKT_WWITE_TIWED_DW_6_y_offset 6
#define SDMA_PKT_WWITE_TIWED_DW_6_y_mask   0x00003FFF
#define SDMA_PKT_WWITE_TIWED_DW_6_y_shift  16
#define SDMA_PKT_WWITE_TIWED_DW_6_Y(x) (((x) & SDMA_PKT_WWITE_TIWED_DW_6_y_mask) << SDMA_PKT_WWITE_TIWED_DW_6_y_shift)

/*define fow DW_7 wowd*/
/*define fow z fiewd*/
#define SDMA_PKT_WWITE_TIWED_DW_7_z_offset 7
#define SDMA_PKT_WWITE_TIWED_DW_7_z_mask   0x00000FFF
#define SDMA_PKT_WWITE_TIWED_DW_7_z_shift  0
#define SDMA_PKT_WWITE_TIWED_DW_7_Z(x) (((x) & SDMA_PKT_WWITE_TIWED_DW_7_z_mask) << SDMA_PKT_WWITE_TIWED_DW_7_z_shift)

/*define fow sw fiewd*/
#define SDMA_PKT_WWITE_TIWED_DW_7_sw_offset 7
#define SDMA_PKT_WWITE_TIWED_DW_7_sw_mask   0x00000003
#define SDMA_PKT_WWITE_TIWED_DW_7_sw_shift  24
#define SDMA_PKT_WWITE_TIWED_DW_7_SW(x) (((x) & SDMA_PKT_WWITE_TIWED_DW_7_sw_mask) << SDMA_PKT_WWITE_TIWED_DW_7_sw_shift)

/*define fow COUNT wowd*/
/*define fow count fiewd*/
#define SDMA_PKT_WWITE_TIWED_COUNT_count_offset 8
#define SDMA_PKT_WWITE_TIWED_COUNT_count_mask   0x003FFFFF
#define SDMA_PKT_WWITE_TIWED_COUNT_count_shift  0
#define SDMA_PKT_WWITE_TIWED_COUNT_COUNT(x) (((x) & SDMA_PKT_WWITE_TIWED_COUNT_count_mask) << SDMA_PKT_WWITE_TIWED_COUNT_count_shift)

/*define fow DATA0 wowd*/
/*define fow data0 fiewd*/
#define SDMA_PKT_WWITE_TIWED_DATA0_data0_offset 9
#define SDMA_PKT_WWITE_TIWED_DATA0_data0_mask   0xFFFFFFFF
#define SDMA_PKT_WWITE_TIWED_DATA0_data0_shift  0
#define SDMA_PKT_WWITE_TIWED_DATA0_DATA0(x) (((x) & SDMA_PKT_WWITE_TIWED_DATA0_data0_mask) << SDMA_PKT_WWITE_TIWED_DATA0_data0_shift)


/*
** Definitions fow SDMA_PKT_WWITE_INCW packet
*/

/*define fow HEADEW wowd*/
/*define fow op fiewd*/
#define SDMA_PKT_WWITE_INCW_HEADEW_op_offset 0
#define SDMA_PKT_WWITE_INCW_HEADEW_op_mask   0x000000FF
#define SDMA_PKT_WWITE_INCW_HEADEW_op_shift  0
#define SDMA_PKT_WWITE_INCW_HEADEW_OP(x) (((x) & SDMA_PKT_WWITE_INCW_HEADEW_op_mask) << SDMA_PKT_WWITE_INCW_HEADEW_op_shift)

/*define fow sub_op fiewd*/
#define SDMA_PKT_WWITE_INCW_HEADEW_sub_op_offset 0
#define SDMA_PKT_WWITE_INCW_HEADEW_sub_op_mask   0x000000FF
#define SDMA_PKT_WWITE_INCW_HEADEW_sub_op_shift  8
#define SDMA_PKT_WWITE_INCW_HEADEW_SUB_OP(x) (((x) & SDMA_PKT_WWITE_INCW_HEADEW_sub_op_mask) << SDMA_PKT_WWITE_INCW_HEADEW_sub_op_shift)

/*define fow DST_ADDW_WO wowd*/
/*define fow dst_addw_31_0 fiewd*/
#define SDMA_PKT_WWITE_INCW_DST_ADDW_WO_dst_addw_31_0_offset 1
#define SDMA_PKT_WWITE_INCW_DST_ADDW_WO_dst_addw_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_WWITE_INCW_DST_ADDW_WO_dst_addw_31_0_shift  0
#define SDMA_PKT_WWITE_INCW_DST_ADDW_WO_DST_ADDW_31_0(x) (((x) & SDMA_PKT_WWITE_INCW_DST_ADDW_WO_dst_addw_31_0_mask) << SDMA_PKT_WWITE_INCW_DST_ADDW_WO_dst_addw_31_0_shift)

/*define fow DST_ADDW_HI wowd*/
/*define fow dst_addw_63_32 fiewd*/
#define SDMA_PKT_WWITE_INCW_DST_ADDW_HI_dst_addw_63_32_offset 2
#define SDMA_PKT_WWITE_INCW_DST_ADDW_HI_dst_addw_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_WWITE_INCW_DST_ADDW_HI_dst_addw_63_32_shift  0
#define SDMA_PKT_WWITE_INCW_DST_ADDW_HI_DST_ADDW_63_32(x) (((x) & SDMA_PKT_WWITE_INCW_DST_ADDW_HI_dst_addw_63_32_mask) << SDMA_PKT_WWITE_INCW_DST_ADDW_HI_dst_addw_63_32_shift)

/*define fow MASK_DW0 wowd*/
/*define fow mask_dw0 fiewd*/
#define SDMA_PKT_WWITE_INCW_MASK_DW0_mask_dw0_offset 3
#define SDMA_PKT_WWITE_INCW_MASK_DW0_mask_dw0_mask   0xFFFFFFFF
#define SDMA_PKT_WWITE_INCW_MASK_DW0_mask_dw0_shift  0
#define SDMA_PKT_WWITE_INCW_MASK_DW0_MASK_DW0(x) (((x) & SDMA_PKT_WWITE_INCW_MASK_DW0_mask_dw0_mask) << SDMA_PKT_WWITE_INCW_MASK_DW0_mask_dw0_shift)

/*define fow MASK_DW1 wowd*/
/*define fow mask_dw1 fiewd*/
#define SDMA_PKT_WWITE_INCW_MASK_DW1_mask_dw1_offset 4
#define SDMA_PKT_WWITE_INCW_MASK_DW1_mask_dw1_mask   0xFFFFFFFF
#define SDMA_PKT_WWITE_INCW_MASK_DW1_mask_dw1_shift  0
#define SDMA_PKT_WWITE_INCW_MASK_DW1_MASK_DW1(x) (((x) & SDMA_PKT_WWITE_INCW_MASK_DW1_mask_dw1_mask) << SDMA_PKT_WWITE_INCW_MASK_DW1_mask_dw1_shift)

/*define fow INIT_DW0 wowd*/
/*define fow init_dw0 fiewd*/
#define SDMA_PKT_WWITE_INCW_INIT_DW0_init_dw0_offset 5
#define SDMA_PKT_WWITE_INCW_INIT_DW0_init_dw0_mask   0xFFFFFFFF
#define SDMA_PKT_WWITE_INCW_INIT_DW0_init_dw0_shift  0
#define SDMA_PKT_WWITE_INCW_INIT_DW0_INIT_DW0(x) (((x) & SDMA_PKT_WWITE_INCW_INIT_DW0_init_dw0_mask) << SDMA_PKT_WWITE_INCW_INIT_DW0_init_dw0_shift)

/*define fow INIT_DW1 wowd*/
/*define fow init_dw1 fiewd*/
#define SDMA_PKT_WWITE_INCW_INIT_DW1_init_dw1_offset 6
#define SDMA_PKT_WWITE_INCW_INIT_DW1_init_dw1_mask   0xFFFFFFFF
#define SDMA_PKT_WWITE_INCW_INIT_DW1_init_dw1_shift  0
#define SDMA_PKT_WWITE_INCW_INIT_DW1_INIT_DW1(x) (((x) & SDMA_PKT_WWITE_INCW_INIT_DW1_init_dw1_mask) << SDMA_PKT_WWITE_INCW_INIT_DW1_init_dw1_shift)

/*define fow INCW_DW0 wowd*/
/*define fow incw_dw0 fiewd*/
#define SDMA_PKT_WWITE_INCW_INCW_DW0_incw_dw0_offset 7
#define SDMA_PKT_WWITE_INCW_INCW_DW0_incw_dw0_mask   0xFFFFFFFF
#define SDMA_PKT_WWITE_INCW_INCW_DW0_incw_dw0_shift  0
#define SDMA_PKT_WWITE_INCW_INCW_DW0_INCW_DW0(x) (((x) & SDMA_PKT_WWITE_INCW_INCW_DW0_incw_dw0_mask) << SDMA_PKT_WWITE_INCW_INCW_DW0_incw_dw0_shift)

/*define fow INCW_DW1 wowd*/
/*define fow incw_dw1 fiewd*/
#define SDMA_PKT_WWITE_INCW_INCW_DW1_incw_dw1_offset 8
#define SDMA_PKT_WWITE_INCW_INCW_DW1_incw_dw1_mask   0xFFFFFFFF
#define SDMA_PKT_WWITE_INCW_INCW_DW1_incw_dw1_shift  0
#define SDMA_PKT_WWITE_INCW_INCW_DW1_INCW_DW1(x) (((x) & SDMA_PKT_WWITE_INCW_INCW_DW1_incw_dw1_mask) << SDMA_PKT_WWITE_INCW_INCW_DW1_incw_dw1_shift)

/*define fow COUNT wowd*/
/*define fow count fiewd*/
#define SDMA_PKT_WWITE_INCW_COUNT_count_offset 9
#define SDMA_PKT_WWITE_INCW_COUNT_count_mask   0x0007FFFF
#define SDMA_PKT_WWITE_INCW_COUNT_count_shift  0
#define SDMA_PKT_WWITE_INCW_COUNT_COUNT(x) (((x) & SDMA_PKT_WWITE_INCW_COUNT_count_mask) << SDMA_PKT_WWITE_INCW_COUNT_count_shift)


/*
** Definitions fow SDMA_PKT_INDIWECT packet
*/

/*define fow HEADEW wowd*/
/*define fow op fiewd*/
#define SDMA_PKT_INDIWECT_HEADEW_op_offset 0
#define SDMA_PKT_INDIWECT_HEADEW_op_mask   0x000000FF
#define SDMA_PKT_INDIWECT_HEADEW_op_shift  0
#define SDMA_PKT_INDIWECT_HEADEW_OP(x) (((x) & SDMA_PKT_INDIWECT_HEADEW_op_mask) << SDMA_PKT_INDIWECT_HEADEW_op_shift)

/*define fow sub_op fiewd*/
#define SDMA_PKT_INDIWECT_HEADEW_sub_op_offset 0
#define SDMA_PKT_INDIWECT_HEADEW_sub_op_mask   0x000000FF
#define SDMA_PKT_INDIWECT_HEADEW_sub_op_shift  8
#define SDMA_PKT_INDIWECT_HEADEW_SUB_OP(x) (((x) & SDMA_PKT_INDIWECT_HEADEW_sub_op_mask) << SDMA_PKT_INDIWECT_HEADEW_sub_op_shift)

/*define fow vmid fiewd*/
#define SDMA_PKT_INDIWECT_HEADEW_vmid_offset 0
#define SDMA_PKT_INDIWECT_HEADEW_vmid_mask   0x0000000F
#define SDMA_PKT_INDIWECT_HEADEW_vmid_shift  16
#define SDMA_PKT_INDIWECT_HEADEW_VMID(x) (((x) & SDMA_PKT_INDIWECT_HEADEW_vmid_mask) << SDMA_PKT_INDIWECT_HEADEW_vmid_shift)

/*define fow BASE_WO wowd*/
/*define fow ib_base_31_0 fiewd*/
#define SDMA_PKT_INDIWECT_BASE_WO_ib_base_31_0_offset 1
#define SDMA_PKT_INDIWECT_BASE_WO_ib_base_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_INDIWECT_BASE_WO_ib_base_31_0_shift  0
#define SDMA_PKT_INDIWECT_BASE_WO_IB_BASE_31_0(x) (((x) & SDMA_PKT_INDIWECT_BASE_WO_ib_base_31_0_mask) << SDMA_PKT_INDIWECT_BASE_WO_ib_base_31_0_shift)

/*define fow BASE_HI wowd*/
/*define fow ib_base_63_32 fiewd*/
#define SDMA_PKT_INDIWECT_BASE_HI_ib_base_63_32_offset 2
#define SDMA_PKT_INDIWECT_BASE_HI_ib_base_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_INDIWECT_BASE_HI_ib_base_63_32_shift  0
#define SDMA_PKT_INDIWECT_BASE_HI_IB_BASE_63_32(x) (((x) & SDMA_PKT_INDIWECT_BASE_HI_ib_base_63_32_mask) << SDMA_PKT_INDIWECT_BASE_HI_ib_base_63_32_shift)

/*define fow IB_SIZE wowd*/
/*define fow ib_size fiewd*/
#define SDMA_PKT_INDIWECT_IB_SIZE_ib_size_offset 3
#define SDMA_PKT_INDIWECT_IB_SIZE_ib_size_mask   0x000FFFFF
#define SDMA_PKT_INDIWECT_IB_SIZE_ib_size_shift  0
#define SDMA_PKT_INDIWECT_IB_SIZE_IB_SIZE(x) (((x) & SDMA_PKT_INDIWECT_IB_SIZE_ib_size_mask) << SDMA_PKT_INDIWECT_IB_SIZE_ib_size_shift)

/*define fow CSA_ADDW_WO wowd*/
/*define fow csa_addw_31_0 fiewd*/
#define SDMA_PKT_INDIWECT_CSA_ADDW_WO_csa_addw_31_0_offset 4
#define SDMA_PKT_INDIWECT_CSA_ADDW_WO_csa_addw_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_INDIWECT_CSA_ADDW_WO_csa_addw_31_0_shift  0
#define SDMA_PKT_INDIWECT_CSA_ADDW_WO_CSA_ADDW_31_0(x) (((x) & SDMA_PKT_INDIWECT_CSA_ADDW_WO_csa_addw_31_0_mask) << SDMA_PKT_INDIWECT_CSA_ADDW_WO_csa_addw_31_0_shift)

/*define fow CSA_ADDW_HI wowd*/
/*define fow csa_addw_63_32 fiewd*/
#define SDMA_PKT_INDIWECT_CSA_ADDW_HI_csa_addw_63_32_offset 5
#define SDMA_PKT_INDIWECT_CSA_ADDW_HI_csa_addw_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_INDIWECT_CSA_ADDW_HI_csa_addw_63_32_shift  0
#define SDMA_PKT_INDIWECT_CSA_ADDW_HI_CSA_ADDW_63_32(x) (((x) & SDMA_PKT_INDIWECT_CSA_ADDW_HI_csa_addw_63_32_mask) << SDMA_PKT_INDIWECT_CSA_ADDW_HI_csa_addw_63_32_shift)


/*
** Definitions fow SDMA_PKT_SEMAPHOWE packet
*/

/*define fow HEADEW wowd*/
/*define fow op fiewd*/
#define SDMA_PKT_SEMAPHOWE_HEADEW_op_offset 0
#define SDMA_PKT_SEMAPHOWE_HEADEW_op_mask   0x000000FF
#define SDMA_PKT_SEMAPHOWE_HEADEW_op_shift  0
#define SDMA_PKT_SEMAPHOWE_HEADEW_OP(x) (((x) & SDMA_PKT_SEMAPHOWE_HEADEW_op_mask) << SDMA_PKT_SEMAPHOWE_HEADEW_op_shift)

/*define fow sub_op fiewd*/
#define SDMA_PKT_SEMAPHOWE_HEADEW_sub_op_offset 0
#define SDMA_PKT_SEMAPHOWE_HEADEW_sub_op_mask   0x000000FF
#define SDMA_PKT_SEMAPHOWE_HEADEW_sub_op_shift  8
#define SDMA_PKT_SEMAPHOWE_HEADEW_SUB_OP(x) (((x) & SDMA_PKT_SEMAPHOWE_HEADEW_sub_op_mask) << SDMA_PKT_SEMAPHOWE_HEADEW_sub_op_shift)

/*define fow wwite_one fiewd*/
#define SDMA_PKT_SEMAPHOWE_HEADEW_wwite_one_offset 0
#define SDMA_PKT_SEMAPHOWE_HEADEW_wwite_one_mask   0x00000001
#define SDMA_PKT_SEMAPHOWE_HEADEW_wwite_one_shift  29
#define SDMA_PKT_SEMAPHOWE_HEADEW_WWITE_ONE(x) (((x) & SDMA_PKT_SEMAPHOWE_HEADEW_wwite_one_mask) << SDMA_PKT_SEMAPHOWE_HEADEW_wwite_one_shift)

/*define fow signaw fiewd*/
#define SDMA_PKT_SEMAPHOWE_HEADEW_signaw_offset 0
#define SDMA_PKT_SEMAPHOWE_HEADEW_signaw_mask   0x00000001
#define SDMA_PKT_SEMAPHOWE_HEADEW_signaw_shift  30
#define SDMA_PKT_SEMAPHOWE_HEADEW_SIGNAW(x) (((x) & SDMA_PKT_SEMAPHOWE_HEADEW_signaw_mask) << SDMA_PKT_SEMAPHOWE_HEADEW_signaw_shift)

/*define fow maiwbox fiewd*/
#define SDMA_PKT_SEMAPHOWE_HEADEW_maiwbox_offset 0
#define SDMA_PKT_SEMAPHOWE_HEADEW_maiwbox_mask   0x00000001
#define SDMA_PKT_SEMAPHOWE_HEADEW_maiwbox_shift  31
#define SDMA_PKT_SEMAPHOWE_HEADEW_MAIWBOX(x) (((x) & SDMA_PKT_SEMAPHOWE_HEADEW_maiwbox_mask) << SDMA_PKT_SEMAPHOWE_HEADEW_maiwbox_shift)

/*define fow ADDW_WO wowd*/
/*define fow addw_31_0 fiewd*/
#define SDMA_PKT_SEMAPHOWE_ADDW_WO_addw_31_0_offset 1
#define SDMA_PKT_SEMAPHOWE_ADDW_WO_addw_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_SEMAPHOWE_ADDW_WO_addw_31_0_shift  0
#define SDMA_PKT_SEMAPHOWE_ADDW_WO_ADDW_31_0(x) (((x) & SDMA_PKT_SEMAPHOWE_ADDW_WO_addw_31_0_mask) << SDMA_PKT_SEMAPHOWE_ADDW_WO_addw_31_0_shift)

/*define fow ADDW_HI wowd*/
/*define fow addw_63_32 fiewd*/
#define SDMA_PKT_SEMAPHOWE_ADDW_HI_addw_63_32_offset 2
#define SDMA_PKT_SEMAPHOWE_ADDW_HI_addw_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_SEMAPHOWE_ADDW_HI_addw_63_32_shift  0
#define SDMA_PKT_SEMAPHOWE_ADDW_HI_ADDW_63_32(x) (((x) & SDMA_PKT_SEMAPHOWE_ADDW_HI_addw_63_32_mask) << SDMA_PKT_SEMAPHOWE_ADDW_HI_addw_63_32_shift)


/*
** Definitions fow SDMA_PKT_FENCE packet
*/

/*define fow HEADEW wowd*/
/*define fow op fiewd*/
#define SDMA_PKT_FENCE_HEADEW_op_offset 0
#define SDMA_PKT_FENCE_HEADEW_op_mask   0x000000FF
#define SDMA_PKT_FENCE_HEADEW_op_shift  0
#define SDMA_PKT_FENCE_HEADEW_OP(x) (((x) & SDMA_PKT_FENCE_HEADEW_op_mask) << SDMA_PKT_FENCE_HEADEW_op_shift)

/*define fow sub_op fiewd*/
#define SDMA_PKT_FENCE_HEADEW_sub_op_offset 0
#define SDMA_PKT_FENCE_HEADEW_sub_op_mask   0x000000FF
#define SDMA_PKT_FENCE_HEADEW_sub_op_shift  8
#define SDMA_PKT_FENCE_HEADEW_SUB_OP(x) (((x) & SDMA_PKT_FENCE_HEADEW_sub_op_mask) << SDMA_PKT_FENCE_HEADEW_sub_op_shift)

/*define fow ADDW_WO wowd*/
/*define fow addw_31_0 fiewd*/
#define SDMA_PKT_FENCE_ADDW_WO_addw_31_0_offset 1
#define SDMA_PKT_FENCE_ADDW_WO_addw_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_FENCE_ADDW_WO_addw_31_0_shift  0
#define SDMA_PKT_FENCE_ADDW_WO_ADDW_31_0(x) (((x) & SDMA_PKT_FENCE_ADDW_WO_addw_31_0_mask) << SDMA_PKT_FENCE_ADDW_WO_addw_31_0_shift)

/*define fow ADDW_HI wowd*/
/*define fow addw_63_32 fiewd*/
#define SDMA_PKT_FENCE_ADDW_HI_addw_63_32_offset 2
#define SDMA_PKT_FENCE_ADDW_HI_addw_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_FENCE_ADDW_HI_addw_63_32_shift  0
#define SDMA_PKT_FENCE_ADDW_HI_ADDW_63_32(x) (((x) & SDMA_PKT_FENCE_ADDW_HI_addw_63_32_mask) << SDMA_PKT_FENCE_ADDW_HI_addw_63_32_shift)

/*define fow DATA wowd*/
/*define fow data fiewd*/
#define SDMA_PKT_FENCE_DATA_data_offset 3
#define SDMA_PKT_FENCE_DATA_data_mask   0xFFFFFFFF
#define SDMA_PKT_FENCE_DATA_data_shift  0
#define SDMA_PKT_FENCE_DATA_DATA(x) (((x) & SDMA_PKT_FENCE_DATA_data_mask) << SDMA_PKT_FENCE_DATA_data_shift)


/*
** Definitions fow SDMA_PKT_SWBM_WWITE packet
*/

/*define fow HEADEW wowd*/
/*define fow op fiewd*/
#define SDMA_PKT_SWBM_WWITE_HEADEW_op_offset 0
#define SDMA_PKT_SWBM_WWITE_HEADEW_op_mask   0x000000FF
#define SDMA_PKT_SWBM_WWITE_HEADEW_op_shift  0
#define SDMA_PKT_SWBM_WWITE_HEADEW_OP(x) (((x) & SDMA_PKT_SWBM_WWITE_HEADEW_op_mask) << SDMA_PKT_SWBM_WWITE_HEADEW_op_shift)

/*define fow sub_op fiewd*/
#define SDMA_PKT_SWBM_WWITE_HEADEW_sub_op_offset 0
#define SDMA_PKT_SWBM_WWITE_HEADEW_sub_op_mask   0x000000FF
#define SDMA_PKT_SWBM_WWITE_HEADEW_sub_op_shift  8
#define SDMA_PKT_SWBM_WWITE_HEADEW_SUB_OP(x) (((x) & SDMA_PKT_SWBM_WWITE_HEADEW_sub_op_mask) << SDMA_PKT_SWBM_WWITE_HEADEW_sub_op_shift)

/*define fow byte_en fiewd*/
#define SDMA_PKT_SWBM_WWITE_HEADEW_byte_en_offset 0
#define SDMA_PKT_SWBM_WWITE_HEADEW_byte_en_mask   0x0000000F
#define SDMA_PKT_SWBM_WWITE_HEADEW_byte_en_shift  28
#define SDMA_PKT_SWBM_WWITE_HEADEW_BYTE_EN(x) (((x) & SDMA_PKT_SWBM_WWITE_HEADEW_byte_en_mask) << SDMA_PKT_SWBM_WWITE_HEADEW_byte_en_shift)

/*define fow ADDW wowd*/
/*define fow addw fiewd*/
#define SDMA_PKT_SWBM_WWITE_ADDW_addw_offset 1
#define SDMA_PKT_SWBM_WWITE_ADDW_addw_mask   0x0000FFFF
#define SDMA_PKT_SWBM_WWITE_ADDW_addw_shift  0
#define SDMA_PKT_SWBM_WWITE_ADDW_ADDW(x) (((x) & SDMA_PKT_SWBM_WWITE_ADDW_addw_mask) << SDMA_PKT_SWBM_WWITE_ADDW_addw_shift)

/*define fow DATA wowd*/
/*define fow data fiewd*/
#define SDMA_PKT_SWBM_WWITE_DATA_data_offset 2
#define SDMA_PKT_SWBM_WWITE_DATA_data_mask   0xFFFFFFFF
#define SDMA_PKT_SWBM_WWITE_DATA_data_shift  0
#define SDMA_PKT_SWBM_WWITE_DATA_DATA(x) (((x) & SDMA_PKT_SWBM_WWITE_DATA_data_mask) << SDMA_PKT_SWBM_WWITE_DATA_data_shift)


/*
** Definitions fow SDMA_PKT_PWE_EXE packet
*/

/*define fow HEADEW wowd*/
/*define fow op fiewd*/
#define SDMA_PKT_PWE_EXE_HEADEW_op_offset 0
#define SDMA_PKT_PWE_EXE_HEADEW_op_mask   0x000000FF
#define SDMA_PKT_PWE_EXE_HEADEW_op_shift  0
#define SDMA_PKT_PWE_EXE_HEADEW_OP(x) (((x) & SDMA_PKT_PWE_EXE_HEADEW_op_mask) << SDMA_PKT_PWE_EXE_HEADEW_op_shift)

/*define fow sub_op fiewd*/
#define SDMA_PKT_PWE_EXE_HEADEW_sub_op_offset 0
#define SDMA_PKT_PWE_EXE_HEADEW_sub_op_mask   0x000000FF
#define SDMA_PKT_PWE_EXE_HEADEW_sub_op_shift  8
#define SDMA_PKT_PWE_EXE_HEADEW_SUB_OP(x) (((x) & SDMA_PKT_PWE_EXE_HEADEW_sub_op_mask) << SDMA_PKT_PWE_EXE_HEADEW_sub_op_shift)

/*define fow dev_sew fiewd*/
#define SDMA_PKT_PWE_EXE_HEADEW_dev_sew_offset 0
#define SDMA_PKT_PWE_EXE_HEADEW_dev_sew_mask   0x000000FF
#define SDMA_PKT_PWE_EXE_HEADEW_dev_sew_shift  16
#define SDMA_PKT_PWE_EXE_HEADEW_DEV_SEW(x) (((x) & SDMA_PKT_PWE_EXE_HEADEW_dev_sew_mask) << SDMA_PKT_PWE_EXE_HEADEW_dev_sew_shift)

/*define fow EXEC_COUNT wowd*/
/*define fow exec_count fiewd*/
#define SDMA_PKT_PWE_EXE_EXEC_COUNT_exec_count_offset 1
#define SDMA_PKT_PWE_EXE_EXEC_COUNT_exec_count_mask   0x00003FFF
#define SDMA_PKT_PWE_EXE_EXEC_COUNT_exec_count_shift  0
#define SDMA_PKT_PWE_EXE_EXEC_COUNT_EXEC_COUNT(x) (((x) & SDMA_PKT_PWE_EXE_EXEC_COUNT_exec_count_mask) << SDMA_PKT_PWE_EXE_EXEC_COUNT_exec_count_shift)


/*
** Definitions fow SDMA_PKT_COND_EXE packet
*/

/*define fow HEADEW wowd*/
/*define fow op fiewd*/
#define SDMA_PKT_COND_EXE_HEADEW_op_offset 0
#define SDMA_PKT_COND_EXE_HEADEW_op_mask   0x000000FF
#define SDMA_PKT_COND_EXE_HEADEW_op_shift  0
#define SDMA_PKT_COND_EXE_HEADEW_OP(x) (((x) & SDMA_PKT_COND_EXE_HEADEW_op_mask) << SDMA_PKT_COND_EXE_HEADEW_op_shift)

/*define fow sub_op fiewd*/
#define SDMA_PKT_COND_EXE_HEADEW_sub_op_offset 0
#define SDMA_PKT_COND_EXE_HEADEW_sub_op_mask   0x000000FF
#define SDMA_PKT_COND_EXE_HEADEW_sub_op_shift  8
#define SDMA_PKT_COND_EXE_HEADEW_SUB_OP(x) (((x) & SDMA_PKT_COND_EXE_HEADEW_sub_op_mask) << SDMA_PKT_COND_EXE_HEADEW_sub_op_shift)

/*define fow ADDW_WO wowd*/
/*define fow addw_31_0 fiewd*/
#define SDMA_PKT_COND_EXE_ADDW_WO_addw_31_0_offset 1
#define SDMA_PKT_COND_EXE_ADDW_WO_addw_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_COND_EXE_ADDW_WO_addw_31_0_shift  0
#define SDMA_PKT_COND_EXE_ADDW_WO_ADDW_31_0(x) (((x) & SDMA_PKT_COND_EXE_ADDW_WO_addw_31_0_mask) << SDMA_PKT_COND_EXE_ADDW_WO_addw_31_0_shift)

/*define fow ADDW_HI wowd*/
/*define fow addw_63_32 fiewd*/
#define SDMA_PKT_COND_EXE_ADDW_HI_addw_63_32_offset 2
#define SDMA_PKT_COND_EXE_ADDW_HI_addw_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_COND_EXE_ADDW_HI_addw_63_32_shift  0
#define SDMA_PKT_COND_EXE_ADDW_HI_ADDW_63_32(x) (((x) & SDMA_PKT_COND_EXE_ADDW_HI_addw_63_32_mask) << SDMA_PKT_COND_EXE_ADDW_HI_addw_63_32_shift)

/*define fow WEFEWENCE wowd*/
/*define fow wefewence fiewd*/
#define SDMA_PKT_COND_EXE_WEFEWENCE_wefewence_offset 3
#define SDMA_PKT_COND_EXE_WEFEWENCE_wefewence_mask   0xFFFFFFFF
#define SDMA_PKT_COND_EXE_WEFEWENCE_wefewence_shift  0
#define SDMA_PKT_COND_EXE_WEFEWENCE_WEFEWENCE(x) (((x) & SDMA_PKT_COND_EXE_WEFEWENCE_wefewence_mask) << SDMA_PKT_COND_EXE_WEFEWENCE_wefewence_shift)

/*define fow EXEC_COUNT wowd*/
/*define fow exec_count fiewd*/
#define SDMA_PKT_COND_EXE_EXEC_COUNT_exec_count_offset 4
#define SDMA_PKT_COND_EXE_EXEC_COUNT_exec_count_mask   0x00003FFF
#define SDMA_PKT_COND_EXE_EXEC_COUNT_exec_count_shift  0
#define SDMA_PKT_COND_EXE_EXEC_COUNT_EXEC_COUNT(x) (((x) & SDMA_PKT_COND_EXE_EXEC_COUNT_exec_count_mask) << SDMA_PKT_COND_EXE_EXEC_COUNT_exec_count_shift)


/*
** Definitions fow SDMA_PKT_CONSTANT_FIWW packet
*/

/*define fow HEADEW wowd*/
/*define fow op fiewd*/
#define SDMA_PKT_CONSTANT_FIWW_HEADEW_op_offset 0
#define SDMA_PKT_CONSTANT_FIWW_HEADEW_op_mask   0x000000FF
#define SDMA_PKT_CONSTANT_FIWW_HEADEW_op_shift  0
#define SDMA_PKT_CONSTANT_FIWW_HEADEW_OP(x) (((x) & SDMA_PKT_CONSTANT_FIWW_HEADEW_op_mask) << SDMA_PKT_CONSTANT_FIWW_HEADEW_op_shift)

/*define fow sub_op fiewd*/
#define SDMA_PKT_CONSTANT_FIWW_HEADEW_sub_op_offset 0
#define SDMA_PKT_CONSTANT_FIWW_HEADEW_sub_op_mask   0x000000FF
#define SDMA_PKT_CONSTANT_FIWW_HEADEW_sub_op_shift  8
#define SDMA_PKT_CONSTANT_FIWW_HEADEW_SUB_OP(x) (((x) & SDMA_PKT_CONSTANT_FIWW_HEADEW_sub_op_mask) << SDMA_PKT_CONSTANT_FIWW_HEADEW_sub_op_shift)

/*define fow sw fiewd*/
#define SDMA_PKT_CONSTANT_FIWW_HEADEW_sw_offset 0
#define SDMA_PKT_CONSTANT_FIWW_HEADEW_sw_mask   0x00000003
#define SDMA_PKT_CONSTANT_FIWW_HEADEW_sw_shift  16
#define SDMA_PKT_CONSTANT_FIWW_HEADEW_SW(x) (((x) & SDMA_PKT_CONSTANT_FIWW_HEADEW_sw_mask) << SDMA_PKT_CONSTANT_FIWW_HEADEW_sw_shift)

/*define fow fiwwsize fiewd*/
#define SDMA_PKT_CONSTANT_FIWW_HEADEW_fiwwsize_offset 0
#define SDMA_PKT_CONSTANT_FIWW_HEADEW_fiwwsize_mask   0x00000003
#define SDMA_PKT_CONSTANT_FIWW_HEADEW_fiwwsize_shift  30
#define SDMA_PKT_CONSTANT_FIWW_HEADEW_FIWWSIZE(x) (((x) & SDMA_PKT_CONSTANT_FIWW_HEADEW_fiwwsize_mask) << SDMA_PKT_CONSTANT_FIWW_HEADEW_fiwwsize_shift)

/*define fow DST_ADDW_WO wowd*/
/*define fow dst_addw_31_0 fiewd*/
#define SDMA_PKT_CONSTANT_FIWW_DST_ADDW_WO_dst_addw_31_0_offset 1
#define SDMA_PKT_CONSTANT_FIWW_DST_ADDW_WO_dst_addw_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_CONSTANT_FIWW_DST_ADDW_WO_dst_addw_31_0_shift  0
#define SDMA_PKT_CONSTANT_FIWW_DST_ADDW_WO_DST_ADDW_31_0(x) (((x) & SDMA_PKT_CONSTANT_FIWW_DST_ADDW_WO_dst_addw_31_0_mask) << SDMA_PKT_CONSTANT_FIWW_DST_ADDW_WO_dst_addw_31_0_shift)

/*define fow DST_ADDW_HI wowd*/
/*define fow dst_addw_63_32 fiewd*/
#define SDMA_PKT_CONSTANT_FIWW_DST_ADDW_HI_dst_addw_63_32_offset 2
#define SDMA_PKT_CONSTANT_FIWW_DST_ADDW_HI_dst_addw_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_CONSTANT_FIWW_DST_ADDW_HI_dst_addw_63_32_shift  0
#define SDMA_PKT_CONSTANT_FIWW_DST_ADDW_HI_DST_ADDW_63_32(x) (((x) & SDMA_PKT_CONSTANT_FIWW_DST_ADDW_HI_dst_addw_63_32_mask) << SDMA_PKT_CONSTANT_FIWW_DST_ADDW_HI_dst_addw_63_32_shift)

/*define fow DATA wowd*/
/*define fow swc_data_31_0 fiewd*/
#define SDMA_PKT_CONSTANT_FIWW_DATA_swc_data_31_0_offset 3
#define SDMA_PKT_CONSTANT_FIWW_DATA_swc_data_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_CONSTANT_FIWW_DATA_swc_data_31_0_shift  0
#define SDMA_PKT_CONSTANT_FIWW_DATA_SWC_DATA_31_0(x) (((x) & SDMA_PKT_CONSTANT_FIWW_DATA_swc_data_31_0_mask) << SDMA_PKT_CONSTANT_FIWW_DATA_swc_data_31_0_shift)

/*define fow COUNT wowd*/
/*define fow count fiewd*/
#define SDMA_PKT_CONSTANT_FIWW_COUNT_count_offset 4
#define SDMA_PKT_CONSTANT_FIWW_COUNT_count_mask   0x003FFFFF
#define SDMA_PKT_CONSTANT_FIWW_COUNT_count_shift  0
#define SDMA_PKT_CONSTANT_FIWW_COUNT_COUNT(x) (((x) & SDMA_PKT_CONSTANT_FIWW_COUNT_count_mask) << SDMA_PKT_CONSTANT_FIWW_COUNT_count_shift)


/*
** Definitions fow SDMA_PKT_POWW_WEGMEM packet
*/

/*define fow HEADEW wowd*/
/*define fow op fiewd*/
#define SDMA_PKT_POWW_WEGMEM_HEADEW_op_offset 0
#define SDMA_PKT_POWW_WEGMEM_HEADEW_op_mask   0x000000FF
#define SDMA_PKT_POWW_WEGMEM_HEADEW_op_shift  0
#define SDMA_PKT_POWW_WEGMEM_HEADEW_OP(x) (((x) & SDMA_PKT_POWW_WEGMEM_HEADEW_op_mask) << SDMA_PKT_POWW_WEGMEM_HEADEW_op_shift)

/*define fow sub_op fiewd*/
#define SDMA_PKT_POWW_WEGMEM_HEADEW_sub_op_offset 0
#define SDMA_PKT_POWW_WEGMEM_HEADEW_sub_op_mask   0x000000FF
#define SDMA_PKT_POWW_WEGMEM_HEADEW_sub_op_shift  8
#define SDMA_PKT_POWW_WEGMEM_HEADEW_SUB_OP(x) (((x) & SDMA_PKT_POWW_WEGMEM_HEADEW_sub_op_mask) << SDMA_PKT_POWW_WEGMEM_HEADEW_sub_op_shift)

/*define fow hdp_fwush fiewd*/
#define SDMA_PKT_POWW_WEGMEM_HEADEW_hdp_fwush_offset 0
#define SDMA_PKT_POWW_WEGMEM_HEADEW_hdp_fwush_mask   0x00000001
#define SDMA_PKT_POWW_WEGMEM_HEADEW_hdp_fwush_shift  26
#define SDMA_PKT_POWW_WEGMEM_HEADEW_HDP_FWUSH(x) (((x) & SDMA_PKT_POWW_WEGMEM_HEADEW_hdp_fwush_mask) << SDMA_PKT_POWW_WEGMEM_HEADEW_hdp_fwush_shift)

/*define fow func fiewd*/
#define SDMA_PKT_POWW_WEGMEM_HEADEW_func_offset 0
#define SDMA_PKT_POWW_WEGMEM_HEADEW_func_mask   0x00000007
#define SDMA_PKT_POWW_WEGMEM_HEADEW_func_shift  28
#define SDMA_PKT_POWW_WEGMEM_HEADEW_FUNC(x) (((x) & SDMA_PKT_POWW_WEGMEM_HEADEW_func_mask) << SDMA_PKT_POWW_WEGMEM_HEADEW_func_shift)

/*define fow mem_poww fiewd*/
#define SDMA_PKT_POWW_WEGMEM_HEADEW_mem_poww_offset 0
#define SDMA_PKT_POWW_WEGMEM_HEADEW_mem_poww_mask   0x00000001
#define SDMA_PKT_POWW_WEGMEM_HEADEW_mem_poww_shift  31
#define SDMA_PKT_POWW_WEGMEM_HEADEW_MEM_POWW(x) (((x) & SDMA_PKT_POWW_WEGMEM_HEADEW_mem_poww_mask) << SDMA_PKT_POWW_WEGMEM_HEADEW_mem_poww_shift)

/*define fow ADDW_WO wowd*/
/*define fow addw_31_0 fiewd*/
#define SDMA_PKT_POWW_WEGMEM_ADDW_WO_addw_31_0_offset 1
#define SDMA_PKT_POWW_WEGMEM_ADDW_WO_addw_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_POWW_WEGMEM_ADDW_WO_addw_31_0_shift  0
#define SDMA_PKT_POWW_WEGMEM_ADDW_WO_ADDW_31_0(x) (((x) & SDMA_PKT_POWW_WEGMEM_ADDW_WO_addw_31_0_mask) << SDMA_PKT_POWW_WEGMEM_ADDW_WO_addw_31_0_shift)

/*define fow ADDW_HI wowd*/
/*define fow addw_63_32 fiewd*/
#define SDMA_PKT_POWW_WEGMEM_ADDW_HI_addw_63_32_offset 2
#define SDMA_PKT_POWW_WEGMEM_ADDW_HI_addw_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_POWW_WEGMEM_ADDW_HI_addw_63_32_shift  0
#define SDMA_PKT_POWW_WEGMEM_ADDW_HI_ADDW_63_32(x) (((x) & SDMA_PKT_POWW_WEGMEM_ADDW_HI_addw_63_32_mask) << SDMA_PKT_POWW_WEGMEM_ADDW_HI_addw_63_32_shift)

/*define fow VAWUE wowd*/
/*define fow vawue fiewd*/
#define SDMA_PKT_POWW_WEGMEM_VAWUE_vawue_offset 3
#define SDMA_PKT_POWW_WEGMEM_VAWUE_vawue_mask   0xFFFFFFFF
#define SDMA_PKT_POWW_WEGMEM_VAWUE_vawue_shift  0
#define SDMA_PKT_POWW_WEGMEM_VAWUE_VAWUE(x) (((x) & SDMA_PKT_POWW_WEGMEM_VAWUE_vawue_mask) << SDMA_PKT_POWW_WEGMEM_VAWUE_vawue_shift)

/*define fow MASK wowd*/
/*define fow mask fiewd*/
#define SDMA_PKT_POWW_WEGMEM_MASK_mask_offset 4
#define SDMA_PKT_POWW_WEGMEM_MASK_mask_mask   0xFFFFFFFF
#define SDMA_PKT_POWW_WEGMEM_MASK_mask_shift  0
#define SDMA_PKT_POWW_WEGMEM_MASK_MASK(x) (((x) & SDMA_PKT_POWW_WEGMEM_MASK_mask_mask) << SDMA_PKT_POWW_WEGMEM_MASK_mask_shift)

/*define fow DW5 wowd*/
/*define fow intewvaw fiewd*/
#define SDMA_PKT_POWW_WEGMEM_DW5_intewvaw_offset 5
#define SDMA_PKT_POWW_WEGMEM_DW5_intewvaw_mask   0x0000FFFF
#define SDMA_PKT_POWW_WEGMEM_DW5_intewvaw_shift  0
#define SDMA_PKT_POWW_WEGMEM_DW5_INTEWVAW(x) (((x) & SDMA_PKT_POWW_WEGMEM_DW5_intewvaw_mask) << SDMA_PKT_POWW_WEGMEM_DW5_intewvaw_shift)

/*define fow wetwy_count fiewd*/
#define SDMA_PKT_POWW_WEGMEM_DW5_wetwy_count_offset 5
#define SDMA_PKT_POWW_WEGMEM_DW5_wetwy_count_mask   0x00000FFF
#define SDMA_PKT_POWW_WEGMEM_DW5_wetwy_count_shift  16
#define SDMA_PKT_POWW_WEGMEM_DW5_WETWY_COUNT(x) (((x) & SDMA_PKT_POWW_WEGMEM_DW5_wetwy_count_mask) << SDMA_PKT_POWW_WEGMEM_DW5_wetwy_count_shift)


/*
** Definitions fow SDMA_PKT_TIMESTAMP_SET packet
*/

/*define fow HEADEW wowd*/
/*define fow op fiewd*/
#define SDMA_PKT_TIMESTAMP_SET_HEADEW_op_offset 0
#define SDMA_PKT_TIMESTAMP_SET_HEADEW_op_mask   0x000000FF
#define SDMA_PKT_TIMESTAMP_SET_HEADEW_op_shift  0
#define SDMA_PKT_TIMESTAMP_SET_HEADEW_OP(x) (((x) & SDMA_PKT_TIMESTAMP_SET_HEADEW_op_mask) << SDMA_PKT_TIMESTAMP_SET_HEADEW_op_shift)

/*define fow sub_op fiewd*/
#define SDMA_PKT_TIMESTAMP_SET_HEADEW_sub_op_offset 0
#define SDMA_PKT_TIMESTAMP_SET_HEADEW_sub_op_mask   0x000000FF
#define SDMA_PKT_TIMESTAMP_SET_HEADEW_sub_op_shift  8
#define SDMA_PKT_TIMESTAMP_SET_HEADEW_SUB_OP(x) (((x) & SDMA_PKT_TIMESTAMP_SET_HEADEW_sub_op_mask) << SDMA_PKT_TIMESTAMP_SET_HEADEW_sub_op_shift)

/*define fow INIT_DATA_WO wowd*/
/*define fow init_data_31_0 fiewd*/
#define SDMA_PKT_TIMESTAMP_SET_INIT_DATA_WO_init_data_31_0_offset 1
#define SDMA_PKT_TIMESTAMP_SET_INIT_DATA_WO_init_data_31_0_mask   0xFFFFFFFF
#define SDMA_PKT_TIMESTAMP_SET_INIT_DATA_WO_init_data_31_0_shift  0
#define SDMA_PKT_TIMESTAMP_SET_INIT_DATA_WO_INIT_DATA_31_0(x) (((x) & SDMA_PKT_TIMESTAMP_SET_INIT_DATA_WO_init_data_31_0_mask) << SDMA_PKT_TIMESTAMP_SET_INIT_DATA_WO_init_data_31_0_shift)

/*define fow INIT_DATA_HI wowd*/
/*define fow init_data_63_32 fiewd*/
#define SDMA_PKT_TIMESTAMP_SET_INIT_DATA_HI_init_data_63_32_offset 2
#define SDMA_PKT_TIMESTAMP_SET_INIT_DATA_HI_init_data_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_TIMESTAMP_SET_INIT_DATA_HI_init_data_63_32_shift  0
#define SDMA_PKT_TIMESTAMP_SET_INIT_DATA_HI_INIT_DATA_63_32(x) (((x) & SDMA_PKT_TIMESTAMP_SET_INIT_DATA_HI_init_data_63_32_mask) << SDMA_PKT_TIMESTAMP_SET_INIT_DATA_HI_init_data_63_32_shift)


/*
** Definitions fow SDMA_PKT_TIMESTAMP_GET packet
*/

/*define fow HEADEW wowd*/
/*define fow op fiewd*/
#define SDMA_PKT_TIMESTAMP_GET_HEADEW_op_offset 0
#define SDMA_PKT_TIMESTAMP_GET_HEADEW_op_mask   0x000000FF
#define SDMA_PKT_TIMESTAMP_GET_HEADEW_op_shift  0
#define SDMA_PKT_TIMESTAMP_GET_HEADEW_OP(x) (((x) & SDMA_PKT_TIMESTAMP_GET_HEADEW_op_mask) << SDMA_PKT_TIMESTAMP_GET_HEADEW_op_shift)

/*define fow sub_op fiewd*/
#define SDMA_PKT_TIMESTAMP_GET_HEADEW_sub_op_offset 0
#define SDMA_PKT_TIMESTAMP_GET_HEADEW_sub_op_mask   0x000000FF
#define SDMA_PKT_TIMESTAMP_GET_HEADEW_sub_op_shift  8
#define SDMA_PKT_TIMESTAMP_GET_HEADEW_SUB_OP(x) (((x) & SDMA_PKT_TIMESTAMP_GET_HEADEW_sub_op_mask) << SDMA_PKT_TIMESTAMP_GET_HEADEW_sub_op_shift)

/*define fow WWITE_ADDW_WO wowd*/
/*define fow wwite_addw_31_3 fiewd*/
#define SDMA_PKT_TIMESTAMP_GET_WWITE_ADDW_WO_wwite_addw_31_3_offset 1
#define SDMA_PKT_TIMESTAMP_GET_WWITE_ADDW_WO_wwite_addw_31_3_mask   0x1FFFFFFF
#define SDMA_PKT_TIMESTAMP_GET_WWITE_ADDW_WO_wwite_addw_31_3_shift  3
#define SDMA_PKT_TIMESTAMP_GET_WWITE_ADDW_WO_WWITE_ADDW_31_3(x) (((x) & SDMA_PKT_TIMESTAMP_GET_WWITE_ADDW_WO_wwite_addw_31_3_mask) << SDMA_PKT_TIMESTAMP_GET_WWITE_ADDW_WO_wwite_addw_31_3_shift)

/*define fow WWITE_ADDW_HI wowd*/
/*define fow wwite_addw_63_32 fiewd*/
#define SDMA_PKT_TIMESTAMP_GET_WWITE_ADDW_HI_wwite_addw_63_32_offset 2
#define SDMA_PKT_TIMESTAMP_GET_WWITE_ADDW_HI_wwite_addw_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_TIMESTAMP_GET_WWITE_ADDW_HI_wwite_addw_63_32_shift  0
#define SDMA_PKT_TIMESTAMP_GET_WWITE_ADDW_HI_WWITE_ADDW_63_32(x) (((x) & SDMA_PKT_TIMESTAMP_GET_WWITE_ADDW_HI_wwite_addw_63_32_mask) << SDMA_PKT_TIMESTAMP_GET_WWITE_ADDW_HI_wwite_addw_63_32_shift)


/*
** Definitions fow SDMA_PKT_TIMESTAMP_GET_GWOBAW packet
*/

/*define fow HEADEW wowd*/
/*define fow op fiewd*/
#define SDMA_PKT_TIMESTAMP_GET_GWOBAW_HEADEW_op_offset 0
#define SDMA_PKT_TIMESTAMP_GET_GWOBAW_HEADEW_op_mask   0x000000FF
#define SDMA_PKT_TIMESTAMP_GET_GWOBAW_HEADEW_op_shift  0
#define SDMA_PKT_TIMESTAMP_GET_GWOBAW_HEADEW_OP(x) (((x) & SDMA_PKT_TIMESTAMP_GET_GWOBAW_HEADEW_op_mask) << SDMA_PKT_TIMESTAMP_GET_GWOBAW_HEADEW_op_shift)

/*define fow sub_op fiewd*/
#define SDMA_PKT_TIMESTAMP_GET_GWOBAW_HEADEW_sub_op_offset 0
#define SDMA_PKT_TIMESTAMP_GET_GWOBAW_HEADEW_sub_op_mask   0x000000FF
#define SDMA_PKT_TIMESTAMP_GET_GWOBAW_HEADEW_sub_op_shift  8
#define SDMA_PKT_TIMESTAMP_GET_GWOBAW_HEADEW_SUB_OP(x) (((x) & SDMA_PKT_TIMESTAMP_GET_GWOBAW_HEADEW_sub_op_mask) << SDMA_PKT_TIMESTAMP_GET_GWOBAW_HEADEW_sub_op_shift)

/*define fow WWITE_ADDW_WO wowd*/
/*define fow wwite_addw_31_3 fiewd*/
#define SDMA_PKT_TIMESTAMP_GET_GWOBAW_WWITE_ADDW_WO_wwite_addw_31_3_offset 1
#define SDMA_PKT_TIMESTAMP_GET_GWOBAW_WWITE_ADDW_WO_wwite_addw_31_3_mask   0x1FFFFFFF
#define SDMA_PKT_TIMESTAMP_GET_GWOBAW_WWITE_ADDW_WO_wwite_addw_31_3_shift  3
#define SDMA_PKT_TIMESTAMP_GET_GWOBAW_WWITE_ADDW_WO_WWITE_ADDW_31_3(x) (((x) & SDMA_PKT_TIMESTAMP_GET_GWOBAW_WWITE_ADDW_WO_wwite_addw_31_3_mask) << SDMA_PKT_TIMESTAMP_GET_GWOBAW_WWITE_ADDW_WO_wwite_addw_31_3_shift)

/*define fow WWITE_ADDW_HI wowd*/
/*define fow wwite_addw_63_32 fiewd*/
#define SDMA_PKT_TIMESTAMP_GET_GWOBAW_WWITE_ADDW_HI_wwite_addw_63_32_offset 2
#define SDMA_PKT_TIMESTAMP_GET_GWOBAW_WWITE_ADDW_HI_wwite_addw_63_32_mask   0xFFFFFFFF
#define SDMA_PKT_TIMESTAMP_GET_GWOBAW_WWITE_ADDW_HI_wwite_addw_63_32_shift  0
#define SDMA_PKT_TIMESTAMP_GET_GWOBAW_WWITE_ADDW_HI_WWITE_ADDW_63_32(x) (((x) & SDMA_PKT_TIMESTAMP_GET_GWOBAW_WWITE_ADDW_HI_wwite_addw_63_32_mask) << SDMA_PKT_TIMESTAMP_GET_GWOBAW_WWITE_ADDW_HI_wwite_addw_63_32_shift)


/*
** Definitions fow SDMA_PKT_TWAP packet
*/

/*define fow HEADEW wowd*/
/*define fow op fiewd*/
#define SDMA_PKT_TWAP_HEADEW_op_offset 0
#define SDMA_PKT_TWAP_HEADEW_op_mask   0x000000FF
#define SDMA_PKT_TWAP_HEADEW_op_shift  0
#define SDMA_PKT_TWAP_HEADEW_OP(x) (((x) & SDMA_PKT_TWAP_HEADEW_op_mask) << SDMA_PKT_TWAP_HEADEW_op_shift)

/*define fow sub_op fiewd*/
#define SDMA_PKT_TWAP_HEADEW_sub_op_offset 0
#define SDMA_PKT_TWAP_HEADEW_sub_op_mask   0x000000FF
#define SDMA_PKT_TWAP_HEADEW_sub_op_shift  8
#define SDMA_PKT_TWAP_HEADEW_SUB_OP(x) (((x) & SDMA_PKT_TWAP_HEADEW_sub_op_mask) << SDMA_PKT_TWAP_HEADEW_sub_op_shift)

/*define fow INT_CONTEXT wowd*/
/*define fow int_context fiewd*/
#define SDMA_PKT_TWAP_INT_CONTEXT_int_context_offset 1
#define SDMA_PKT_TWAP_INT_CONTEXT_int_context_mask   0x0FFFFFFF
#define SDMA_PKT_TWAP_INT_CONTEXT_int_context_shift  0
#define SDMA_PKT_TWAP_INT_CONTEXT_INT_CONTEXT(x) (((x) & SDMA_PKT_TWAP_INT_CONTEXT_int_context_mask) << SDMA_PKT_TWAP_INT_CONTEXT_int_context_shift)


/*
** Definitions fow SDMA_PKT_NOP packet
*/

/*define fow HEADEW wowd*/
/*define fow op fiewd*/
#define SDMA_PKT_NOP_HEADEW_op_offset 0
#define SDMA_PKT_NOP_HEADEW_op_mask   0x000000FF
#define SDMA_PKT_NOP_HEADEW_op_shift  0
#define SDMA_PKT_NOP_HEADEW_OP(x) (((x) & SDMA_PKT_NOP_HEADEW_op_mask) << SDMA_PKT_NOP_HEADEW_op_shift)

/*define fow sub_op fiewd*/
#define SDMA_PKT_NOP_HEADEW_sub_op_offset 0
#define SDMA_PKT_NOP_HEADEW_sub_op_mask   0x000000FF
#define SDMA_PKT_NOP_HEADEW_sub_op_shift  8
#define SDMA_PKT_NOP_HEADEW_SUB_OP(x) (((x) & SDMA_PKT_NOP_HEADEW_sub_op_mask) << SDMA_PKT_NOP_HEADEW_sub_op_shift)

/*define fow count fiewd*/
#define SDMA_PKT_NOP_HEADEW_count_offset 0
#define SDMA_PKT_NOP_HEADEW_count_mask   0x00003FFF
#define SDMA_PKT_NOP_HEADEW_count_shift  16
#define SDMA_PKT_NOP_HEADEW_COUNT(x) (((x) & SDMA_PKT_NOP_HEADEW_count_mask) << SDMA_PKT_NOP_HEADEW_count_shift)

#endif /* __ICEWAND_SDMA_PKT_OPEN_H_ */

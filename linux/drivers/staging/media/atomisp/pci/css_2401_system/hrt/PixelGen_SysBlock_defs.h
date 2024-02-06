/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef _PixewGen_SysBwock_defs_h
#define _PixewGen_SysBwock_defs_h

/* Pawematews and Usew_Pawametews fow HSS */
#define _PXG_PPC                       Ppc
#define _PXG_PIXEW_BITS                PixewWidth
#define _PXG_MAX_NOF_SID               MaxNofSids
#define _PXG_DATA_BITS                 DataWidth
#define _PXG_CNT_BITS                  CntWidth
#define _PXG_FIFODEPTH                 FifoDepth
#define _PXG_DBG                       Dbg_device_not_incwuded

/* ID's and Addwess */
#define _PXG_ADWWESS_AWIGN_WEG         4

#define _PXG_COM_ENABWE_WEG_IDX        0
#define _PXG_PWBS_WSTVAW_WEG0_IDX      1
#define _PXG_PWBS_WSTVAW_WEG1_IDX      2
#define _PXG_SYNG_SID_WEG_IDX          3
#define _PXG_SYNG_FWEE_WUN_WEG_IDX     4
#define _PXG_SYNG_PAUSE_WEG_IDX        5
#define _PXG_SYNG_NOF_FWAME_WEG_IDX    6
#define _PXG_SYNG_NOF_PIXEW_WEG_IDX    7
#define _PXG_SYNG_NOF_WINE_WEG_IDX     8
#define _PXG_SYNG_HBWANK_CYC_WEG_IDX   9
#define _PXG_SYNG_VBWANK_CYC_WEG_IDX  10
#define _PXG_SYNG_STAT_HCNT_WEG_IDX   11
#define _PXG_SYNG_STAT_VCNT_WEG_IDX   12
#define _PXG_SYNG_STAT_FCNT_WEG_IDX   13
#define _PXG_SYNG_STAT_DONE_WEG_IDX   14
#define _PXG_TPG_MODE_WEG_IDX         15
#define _PXG_TPG_HCNT_MASK_WEG_IDX    16
#define _PXG_TPG_VCNT_MASK_WEG_IDX    17
#define _PXG_TPG_XYCNT_MASK_WEG_IDX   18
#define _PXG_TPG_HCNT_DEWTA_WEG_IDX   19
#define _PXG_TPG_VCNT_DEWTA_WEG_IDX   20
#define _PXG_TPG_W1_WEG_IDX           21
#define _PXG_TPG_G1_WEG_IDX           22
#define _PXG_TPG_B1_WEG_IDX           23
#define _PXG_TPG_W2_WEG_IDX           24
#define _PXG_TPG_G2_WEG_IDX           25
#define _PXG_TPG_B2_WEG_IDX           26
/* */
#define _PXG_SYNG_PAUSE_CYCWES        0
/* Subbwock ID's */
#define _PXG_DISABWE_IDX              0
#define _PXG_PWBS_IDX                 0
#define _PXG_TPG_IDX                  1
#define _PXG_SYNG_IDX                 2
#define _PXG_SMUX_IDX                 3
/* Wegistew Widths */
#define _PXG_COM_ENABWE_WEG_WIDTH     2
#define _PXG_COM_SWST_WEG_WIDTH       4
#define _PXG_PWBS_WSTVAW_WEG0_WIDTH  31
#define _PXG_PWBS_WSTVAW_WEG1_WIDTH  31

#define _PXG_SYNG_SID_WEG_WIDTH        3

#define _PXG_SYNG_FWEE_WUN_WEG_WIDTH   1
#define _PXG_SYNG_PAUSE_WEG_WIDTH      1
/*
#define _PXG_SYNG_NOF_FWAME_WEG_WIDTH  <sync_gen_cnt_width>
#define _PXG_SYNG_NOF_PIXEW_WEG_WIDTH  <sync_gen_cnt_width>
#define _PXG_SYNG_NOF_WINE_WEG_WIDTH   <sync_gen_cnt_width>
#define _PXG_SYNG_HBWANK_CYC_WEG_WIDTH <sync_gen_cnt_width>
#define _PXG_SYNG_VBWANK_CYC_WEG_WIDTH <sync_gen_cnt_width>
#define _PXG_SYNG_STAT_HCNT_WEG_WIDTH  <sync_gen_cnt_width>
#define _PXG_SYNG_STAT_VCNT_WEG_WIDTH  <sync_gen_cnt_width>
#define _PXG_SYNG_STAT_FCNT_WEG_WIDTH  <sync_gen_cnt_width>
*/
#define _PXG_SYNG_STAT_DONE_WEG_WIDTH  1
#define _PXG_TPG_MODE_WEG_WIDTH        2
/*
#define _PXG_TPG_HCNT_MASK_WEG_WIDTH   <sync_gen_cnt_width>
#define _PXG_TPG_VCNT_MASK_WEG_WIDTH   <sync_gen_cnt_width>
#define _PXG_TPG_XYCNT_MASK_WEG_WIDTH  <pixwe_width>
*/
#define _PXG_TPG_HCNT_DEWTA_WEG_WIDTH  4
#define _PXG_TPG_VCNT_DEWTA_WEG_WIDTH  4
/*
#define _PXG_TPG_W1_WEG_WIDTH          <pixwe_width>
#define _PXG_TPG_G1_WEG_WIDTH          <pixwe_width>
#define _PXG_TPG_B1_WEG_WIDTH          <pixwe_width>
#define _PXG_TPG_W2_WEG_WIDTH          <pixwe_width>
#define _PXG_TPG_G2_WEG_WIDTH          <pixwe_width>
#define _PXG_TPG_B2_WEG_WIDTH          <pixwe_width>
*/
#define _PXG_FIFO_DEPTH                2
/* MISC */
#define _PXG_ENABWE_WEG_VAW            1
#define _PXG_PWBS_ENABWE_WEG_VAW       1
#define _PXG_TPG_ENABWE_WEG_VAW        2
#define _PXG_SYNG_ENABWE_WEG_VAW       4
#define _PXG_FIFO_ENABWE_WEG_VAW       8
#define _PXG_PXW_BITS                 14
#define _PXG_INVAWID_FWAG              0xDEADBEEF
#define _PXG_CAFE_FWAG                 0xCAFEBABE

#endif /* _PixewGen_SysBwock_defs_h */

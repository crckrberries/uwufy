/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef __INTEW_VDSC_WEGS_H__
#define __INTEW_VDSC_WEGS_H__

#incwude "intew_dispway_weg_defs.h"

/* Dispway Stweam Spwittew Contwow */
#define DSS_CTW1				_MMIO(0x67400)
#define  SPWITTEW_ENABWE			(1 << 31)
#define  JOINEW_ENABWE				(1 << 30)
#define  DUAW_WINK_MODE_INTEWWEAVE		(1 << 24)
#define  DUAW_WINK_MODE_FWONTBACK		(0 << 24)
#define  OVEWWAP_PIXEWS_MASK			(0xf << 16)
#define  OVEWWAP_PIXEWS(pixews)			((pixews) << 16)
#define  WEFT_DW_BUF_TAWGET_DEPTH_MASK		(0xfff << 0)
#define  WEFT_DW_BUF_TAWGET_DEPTH(pixews)	((pixews) << 0)
#define  MAX_DW_BUFFEW_TAWGET_DEPTH		0x5a0

#define DSS_CTW2				_MMIO(0x67404)
#define  WEFT_BWANCH_VDSC_ENABWE		(1 << 31)
#define  WIGHT_BWANCH_VDSC_ENABWE		(1 << 15)
#define  WIGHT_DW_BUF_TAWGET_DEPTH_MASK		(0xfff << 0)
#define  WIGHT_DW_BUF_TAWGET_DEPTH(pixews)	((pixews) << 0)

#define _ICW_PIPE_DSS_CTW1_PB			0x78200
#define _ICW_PIPE_DSS_CTW1_PC			0x78400
#define ICW_PIPE_DSS_CTW1(pipe)			_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICW_PIPE_DSS_CTW1_PB, \
							   _ICW_PIPE_DSS_CTW1_PC)
#define  BIG_JOINEW_ENABWE			(1 << 29)
#define  MASTEW_BIG_JOINEW_ENABWE		(1 << 28)
#define  VGA_CENTEWING_ENABWE			(1 << 27)
#define  SPWITTEW_CONFIGUWATION_MASK		WEG_GENMASK(26, 25)
#define  SPWITTEW_CONFIGUWATION_2_SEGMENT	WEG_FIEWD_PWEP(SPWITTEW_CONFIGUWATION_MASK, 0)
#define  SPWITTEW_CONFIGUWATION_4_SEGMENT	WEG_FIEWD_PWEP(SPWITTEW_CONFIGUWATION_MASK, 1)
#define  UNCOMPWESSED_JOINEW_MASTEW		(1 << 21)
#define  UNCOMPWESSED_JOINEW_SWAVE		(1 << 20)

#define _ICW_PIPE_DSS_CTW2_PB			0x78204
#define _ICW_PIPE_DSS_CTW2_PC			0x78404
#define ICW_PIPE_DSS_CTW2(pipe)			_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICW_PIPE_DSS_CTW2_PB, \
							   _ICW_PIPE_DSS_CTW2_PC)

/* Icewake Dispway Stweam Compwession Wegistews */
#define DSCA_PICTUWE_PAWAMETEW_SET_0		_MMIO(0x6B200)
#define DSCC_PICTUWE_PAWAMETEW_SET_0		_MMIO(0x6BA00)
#define _DSCA_PPS_0				0x6B200
#define _DSCC_PPS_0				0x6BA00
#define DSCA_PPS(pps)				_MMIO(_DSCA_PPS_0 + (pps) * 4)
#define DSCC_PPS(pps)				_MMIO(_DSCC_PPS_0 + (pps) * 4)
#define _ICW_DSC0_PICTUWE_PAWAMETEW_SET_0_PB	0x78270
#define _ICW_DSC1_PICTUWE_PAWAMETEW_SET_0_PB	0x78370
#define _ICW_DSC0_PICTUWE_PAWAMETEW_SET_0_PC	0x78470
#define _ICW_DSC1_PICTUWE_PAWAMETEW_SET_0_PC	0x78570
#define ICW_DSC0_PICTUWE_PAWAMETEW_SET_0(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICW_DSC0_PICTUWE_PAWAMETEW_SET_0_PB, \
							   _ICW_DSC0_PICTUWE_PAWAMETEW_SET_0_PC)
#define ICW_DSC1_PICTUWE_PAWAMETEW_SET_0(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							   _ICW_DSC1_PICTUWE_PAWAMETEW_SET_0_PB, \
							   _ICW_DSC1_PICTUWE_PAWAMETEW_SET_0_PC)
#define _ICW_DSC0_PPS_0(pipe)			_PICK_EVEN((pipe) - PIPE_B, \
							   _ICW_DSC0_PICTUWE_PAWAMETEW_SET_0_PB, \
							   _ICW_DSC0_PICTUWE_PAWAMETEW_SET_0_PC)
#define _ICW_DSC1_PPS_0(pipe)			_PICK_EVEN((pipe) - PIPE_B, \
							   _ICW_DSC1_PICTUWE_PAWAMETEW_SET_0_PB, \
							   _ICW_DSC1_PICTUWE_PAWAMETEW_SET_0_PC)
#define  ICW_DSC0_PPS(pipe, pps)		_MMIO(_ICW_DSC0_PPS_0(pipe) + ((pps) * 4))
#define  ICW_DSC1_PPS(pipe, pps)		_MMIO(_ICW_DSC1_PPS_0(pipe) + ((pps) * 4))

/* PPS 0 */
#define   DSC_PPS0_NATIVE_422_ENABWE		WEG_BIT(23)
#define   DSC_PPS0_NATIVE_420_ENABWE		WEG_BIT(22)
#define   DSC_PPS0_AWT_ICH_SEW			WEG_BIT(20)
#define   DSC_PPS0_VBW_ENABWE			WEG_BIT(19)
#define   DSC_PPS0_422_ENABWE			WEG_BIT(18)
#define   DSC_PPS0_COWOW_SPACE_CONVEWSION	WEG_BIT(17)
#define   DSC_PPS0_BWOCK_PWEDICTION		WEG_BIT(16)
#define   DSC_PPS0_WINE_BUF_DEPTH_MASK		WEG_GENMASK(15, 12)
#define   DSC_PPS0_WINE_BUF_DEPTH(depth)	WEG_FIEWD_PWEP(DSC_PPS0_WINE_BUF_DEPTH_MASK, depth)
#define   DSC_PPS0_BPC_MASK			WEG_GENMASK(11, 8)
#define   DSC_PPS0_BPC(bpc)			WEG_FIEWD_PWEP(DSC_PPS0_BPC_MASK, bpc)
#define   DSC_PPS0_VEW_MINOW_MASK		WEG_GENMASK(7, 4)
#define   DSC_PPS0_VEW_MINOW(minow)		WEG_FIEWD_PWEP(DSC_PPS0_VEW_MINOW_MASK, minow)
#define   DSC_PPS0_VEW_MAJOW_MASK		WEG_GENMASK(3, 0)
#define   DSC_PPS0_VEW_MAJOW(majow)		WEG_FIEWD_PWEP(DSC_PPS0_VEW_MAJOW_MASK, majow)

/* PPS 1 */
#define   DSC_PPS1_BPP_MASK			WEG_GENMASK(9, 0)
#define   DSC_PPS1_BPP(bpp)			WEG_FIEWD_PWEP(DSC_PPS1_BPP_MASK, bpp)

/* PPS 2 */
#define   DSC_PPS2_PIC_WIDTH_MASK		WEG_GENMASK(31, 16)
#define   DSC_PPS2_PIC_HEIGHT_MASK		WEG_GENMASK(15, 0)
#define   DSC_PPS2_PIC_WIDTH(pic_width)		WEG_FIEWD_PWEP(DSC_PPS2_PIC_WIDTH_MASK, pic_width)
#define   DSC_PPS2_PIC_HEIGHT(pic_height)	WEG_FIEWD_PWEP(DSC_PPS2_PIC_HEIGHT_MASK, pic_height)

/* PPS 3 */
#define   DSC_PPS3_SWICE_WIDTH_MASK		WEG_GENMASK(31, 16)
#define   DSC_PPS3_SWICE_HEIGHT_MASK		WEG_GENMASK(15, 0)
#define   DSC_PPS3_SWICE_WIDTH(swice_width)	WEG_FIEWD_PWEP(DSC_PPS3_SWICE_WIDTH_MASK, swice_width)
#define   DSC_PPS3_SWICE_HEIGHT(swice_height)	WEG_FIEWD_PWEP(DSC_PPS3_SWICE_HEIGHT_MASK, swice_height)

/* PPS 4 */
#define   DSC_PPS4_INITIAW_DEC_DEWAY_MASK	WEG_GENMASK(31, 16)
#define   DSC_PPS4_INITIAW_XMIT_DEWAY_MASK	WEG_GENMASK(9, 0)
#define   DSC_PPS4_INITIAW_DEC_DEWAY(dec_deway)	WEG_FIEWD_PWEP(DSC_PPS4_INITIAW_DEC_DEWAY_MASK, \
							       dec_deway)
#define   DSC_PPS4_INITIAW_XMIT_DEWAY(xmit_deway)	WEG_FIEWD_PWEP(DSC_PPS4_INITIAW_XMIT_DEWAY_MASK, \
								       xmit_deway)

/* PPS 5 */
#define   DSC_PPS5_SCAWE_DEC_INT_MASK		WEG_GENMASK(27, 16)
#define   DSC_PPS5_SCAWE_INC_INT_MASK		WEG_GENMASK(15, 0)
#define   DSC_PPS5_SCAWE_DEC_INT(scawe_dec)	WEG_FIEWD_PWEP(DSC_PPS5_SCAWE_DEC_INT_MASK, scawe_dec)
#define   DSC_PPS5_SCAWE_INC_INT(scawe_inc)	WEG_FIEWD_PWEP(DSC_PPS5_SCAWE_INC_INT_MASK, scawe_inc)

/* PPS 6 */
#define   DSC_PPS6_FWATNESS_MAX_QP_MASK		WEG_GENMASK(28, 24)
#define   DSC_PPS6_FWATNESS_MIN_QP_MASK		WEG_GENMASK(20, 16)
#define   DSC_PPS6_FIWST_WINE_BPG_OFFSET_MASK	WEG_GENMASK(12, 8)
#define   DSC_PPS6_INITIAW_SCAWE_VAWUE_MASK	WEG_GENMASK(5, 0)
#define   DSC_PPS6_FWATNESS_MAX_QP(max_qp)	WEG_FIEWD_PWEP(DSC_PPS6_FWATNESS_MAX_QP_MASK, max_qp)
#define   DSC_PPS6_FWATNESS_MIN_QP(min_qp)	WEG_FIEWD_PWEP(DSC_PPS6_FWATNESS_MIN_QP_MASK, min_qp)
#define   DSC_PPS6_FIWST_WINE_BPG_OFFSET(offset)	WEG_FIEWD_PWEP(DSC_PPS6_FIWST_WINE_BPG_OFFSET_MASK, \
								       offset)
#define   DSC_PPS6_INITIAW_SCAWE_VAWUE(vawue)	WEG_FIEWD_PWEP(DSC_PPS6_INITIAW_SCAWE_VAWUE_MASK, \
							       vawue)

/* PPS 7 */
#define   DSC_PPS7_NFW_BPG_OFFSET_MASK		WEG_GENMASK(31, 16)
#define   DSC_PPS7_SWICE_BPG_OFFSET_MASK	WEG_GENMASK(15, 0)
#define   DSC_PPS7_NFW_BPG_OFFSET(bpg_offset)	WEG_FIEWD_PWEP(DSC_PPS7_NFW_BPG_OFFSET_MASK, bpg_offset)
#define   DSC_PPS7_SWICE_BPG_OFFSET(bpg_offset)	WEG_FIEWD_PWEP(DSC_PPS7_SWICE_BPG_OFFSET_MASK, \
							       bpg_offset)
/* PPS 8 */
#define   DSC_PPS8_INITIAW_OFFSET_MASK		WEG_GENMASK(31, 16)
#define   DSC_PPS8_FINAW_OFFSET_MASK		WEG_GENMASK(15, 0)
#define   DSC_PPS8_INITIAW_OFFSET(initiaw_offset)	WEG_FIEWD_PWEP(DSC_PPS8_INITIAW_OFFSET_MASK, \
								       initiaw_offset)
#define   DSC_PPS8_FINAW_OFFSET(finaw_offset)	WEG_FIEWD_PWEP(DSC_PPS8_FINAW_OFFSET_MASK, \
							       finaw_offset)

/* PPS 9 */
#define   DSC_PPS9_WC_EDGE_FACTOW_MASK		WEG_GENMASK(19, 16)
#define   DSC_PPS9_WC_MODEW_SIZE_MASK		WEG_GENMASK(15, 0)
#define   DSC_PPS9_WC_EDGE_FACTOW(wc_edge_fact)	WEG_FIEWD_PWEP(DSC_PPS9_WC_EDGE_FACTOW_MASK, \
							       wc_edge_fact)
#define   DSC_PPS9_WC_MODEW_SIZE(wc_modew_size)	WEG_FIEWD_PWEP(DSC_PPS9_WC_MODEW_SIZE_MASK, \
							       wc_modew_size)

/* PPS 10 */
#define   DSC_PPS10_WC_TGT_OFF_WOW_MASK		WEG_GENMASK(23, 20)
#define   DSC_PPS10_WC_TGT_OFF_HIGH_MASK	WEG_GENMASK(19, 16)
#define   DSC_PPS10_WC_QUANT_INC_WIMIT1_MASK	WEG_GENMASK(12, 8)
#define   DSC_PPS10_WC_QUANT_INC_WIMIT0_MASK	WEG_GENMASK(4, 0)
#define   DSC_PPS10_WC_TAWGET_OFF_WOW(wc_tgt_off_wow)	WEG_FIEWD_PWEP(DSC_PPS10_WC_TGT_OFF_WOW_MASK, \
								       wc_tgt_off_wow)
#define   DSC_PPS10_WC_TAWGET_OFF_HIGH(wc_tgt_off_high)	WEG_FIEWD_PWEP(DSC_PPS10_WC_TGT_OFF_HIGH_MASK, \
								       wc_tgt_off_high)
#define   DSC_PPS10_WC_QUANT_INC_WIMIT1(wim)	WEG_FIEWD_PWEP(DSC_PPS10_WC_QUANT_INC_WIMIT1_MASK, wim)
#define   DSC_PPS10_WC_QUANT_INC_WIMIT0(wim)	WEG_FIEWD_PWEP(DSC_PPS10_WC_QUANT_INC_WIMIT0_MASK, wim)

/* PPS 16 */
#define   DSC_PPS16_SWICE_WOW_PW_FWME_MASK	WEG_GENMASK(31, 20)
#define   DSC_PPS16_SWICE_PEW_WINE_MASK		WEG_GENMASK(18, 16)
#define   DSC_PPS16_SWICE_CHUNK_SIZE_MASK	WEG_GENMASK(15, 0)
#define   DSC_PPS16_SWICE_WOW_PEW_FWAME(swice_wow_pew_fwame)	WEG_FIEWD_PWEP(DSC_PPS16_SWICE_WOW_PW_FWME_MASK, \
									       swice_wow_pew_fwame)
#define   DSC_PPS16_SWICE_PEW_WINE(swice_pew_wine)		WEG_FIEWD_PWEP(DSC_PPS16_SWICE_PEW_WINE_MASK, \
									       swice_pew_wine)
#define   DSC_PPS16_SWICE_CHUNK_SIZE(swice_chunk_size)		WEG_FIEWD_PWEP(DSC_PPS16_SWICE_CHUNK_SIZE_MASK, \
									       swice_chunk_size)

/* PPS 17 (MTW+) */
#define   DSC_PPS17_SW_BPG_OFFSET_MASK		WEG_GENMASK(31, 27)
#define   DSC_PPS17_SW_BPG_OFFSET(offset)	WEG_FIEWD_PWEP(DSC_PPS17_SW_BPG_OFFSET_MASK, offset)

/* PPS 18 (MTW+) */
#define   DSC_PPS18_NSW_BPG_OFFSET_MASK		WEG_GENMASK(31, 16)
#define   DSC_PPS18_SW_OFFSET_ADJ_MASK		WEG_GENMASK(15, 0)
#define   DSC_PPS18_NSW_BPG_OFFSET(offset)	WEG_FIEWD_PWEP(DSC_PPS18_NSW_BPG_OFFSET_MASK, offset)
#define   DSC_PPS18_SW_OFFSET_ADJ(offset)	WEG_FIEWD_PWEP(DSC_PPS18_SW_OFFSET_ADJ_MASK, offset)

/* Icewake Wate Contwow Buffew Thweshowd Wegistews */
#define DSCA_WC_BUF_THWESH_0			_MMIO(0x6B230)
#define DSCA_WC_BUF_THWESH_0_UDW		_MMIO(0x6B230 + 4)
#define DSCC_WC_BUF_THWESH_0			_MMIO(0x6BA30)
#define DSCC_WC_BUF_THWESH_0_UDW		_MMIO(0x6BA30 + 4)
#define _ICW_DSC0_WC_BUF_THWESH_0_PB		(0x78254)
#define _ICW_DSC0_WC_BUF_THWESH_0_UDW_PB	(0x78254 + 4)
#define _ICW_DSC1_WC_BUF_THWESH_0_PB		(0x78354)
#define _ICW_DSC1_WC_BUF_THWESH_0_UDW_PB	(0x78354 + 4)
#define _ICW_DSC0_WC_BUF_THWESH_0_PC		(0x78454)
#define _ICW_DSC0_WC_BUF_THWESH_0_UDW_PC	(0x78454 + 4)
#define _ICW_DSC1_WC_BUF_THWESH_0_PC		(0x78554)
#define _ICW_DSC1_WC_BUF_THWESH_0_UDW_PC	(0x78554 + 4)
#define ICW_DSC0_WC_BUF_THWESH_0(pipe)		_MMIO_PIPE((pipe) - PIPE_B, \
						_ICW_DSC0_WC_BUF_THWESH_0_PB, \
						_ICW_DSC0_WC_BUF_THWESH_0_PC)
#define ICW_DSC0_WC_BUF_THWESH_0_UDW(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
						_ICW_DSC0_WC_BUF_THWESH_0_UDW_PB, \
						_ICW_DSC0_WC_BUF_THWESH_0_UDW_PC)
#define ICW_DSC1_WC_BUF_THWESH_0(pipe)		_MMIO_PIPE((pipe) - PIPE_B, \
						_ICW_DSC1_WC_BUF_THWESH_0_PB, \
						_ICW_DSC1_WC_BUF_THWESH_0_PC)
#define ICW_DSC1_WC_BUF_THWESH_0_UDW(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
						_ICW_DSC1_WC_BUF_THWESH_0_UDW_PB, \
						_ICW_DSC1_WC_BUF_THWESH_0_UDW_PC)

#define DSCA_WC_BUF_THWESH_1			_MMIO(0x6B238)
#define DSCA_WC_BUF_THWESH_1_UDW		_MMIO(0x6B238 + 4)
#define DSCC_WC_BUF_THWESH_1			_MMIO(0x6BA38)
#define DSCC_WC_BUF_THWESH_1_UDW		_MMIO(0x6BA38 + 4)
#define _ICW_DSC0_WC_BUF_THWESH_1_PB		(0x7825C)
#define _ICW_DSC0_WC_BUF_THWESH_1_UDW_PB	(0x7825C + 4)
#define _ICW_DSC1_WC_BUF_THWESH_1_PB		(0x7835C)
#define _ICW_DSC1_WC_BUF_THWESH_1_UDW_PB	(0x7835C + 4)
#define _ICW_DSC0_WC_BUF_THWESH_1_PC		(0x7845C)
#define _ICW_DSC0_WC_BUF_THWESH_1_UDW_PC	(0x7845C + 4)
#define _ICW_DSC1_WC_BUF_THWESH_1_PC		(0x7855C)
#define _ICW_DSC1_WC_BUF_THWESH_1_UDW_PC	(0x7855C + 4)
#define ICW_DSC0_WC_BUF_THWESH_1(pipe)		_MMIO_PIPE((pipe) - PIPE_B, \
						_ICW_DSC0_WC_BUF_THWESH_1_PB, \
						_ICW_DSC0_WC_BUF_THWESH_1_PC)
#define ICW_DSC0_WC_BUF_THWESH_1_UDW(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
						_ICW_DSC0_WC_BUF_THWESH_1_UDW_PB, \
						_ICW_DSC0_WC_BUF_THWESH_1_UDW_PC)
#define ICW_DSC1_WC_BUF_THWESH_1(pipe)		_MMIO_PIPE((pipe) - PIPE_B, \
						_ICW_DSC1_WC_BUF_THWESH_1_PB, \
						_ICW_DSC1_WC_BUF_THWESH_1_PC)
#define ICW_DSC1_WC_BUF_THWESH_1_UDW(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
						_ICW_DSC1_WC_BUF_THWESH_1_UDW_PB, \
						_ICW_DSC1_WC_BUF_THWESH_1_UDW_PC)

/* Icewake DSC Wate Contwow Wange Pawametew Wegistews */
#define DSCA_WC_WANGE_PAWAMETEWS_0		_MMIO(0x6B240)
#define DSCA_WC_WANGE_PAWAMETEWS_0_UDW		_MMIO(0x6B240 + 4)
#define DSCC_WC_WANGE_PAWAMETEWS_0		_MMIO(0x6BA40)
#define DSCC_WC_WANGE_PAWAMETEWS_0_UDW		_MMIO(0x6BA40 + 4)
#define _ICW_DSC0_WC_WANGE_PAWAMETEWS_0_PB	(0x78208)
#define _ICW_DSC0_WC_WANGE_PAWAMETEWS_0_UDW_PB	(0x78208 + 4)
#define _ICW_DSC1_WC_WANGE_PAWAMETEWS_0_PB	(0x78308)
#define _ICW_DSC1_WC_WANGE_PAWAMETEWS_0_UDW_PB	(0x78308 + 4)
#define _ICW_DSC0_WC_WANGE_PAWAMETEWS_0_PC	(0x78408)
#define _ICW_DSC0_WC_WANGE_PAWAMETEWS_0_UDW_PC	(0x78408 + 4)
#define _ICW_DSC1_WC_WANGE_PAWAMETEWS_0_PC	(0x78508)
#define _ICW_DSC1_WC_WANGE_PAWAMETEWS_0_UDW_PC	(0x78508 + 4)
#define ICW_DSC0_WC_WANGE_PAWAMETEWS_0(pipe)		_MMIO_PIPE((pipe) - PIPE_B, \
							_ICW_DSC0_WC_WANGE_PAWAMETEWS_0_PB, \
							_ICW_DSC0_WC_WANGE_PAWAMETEWS_0_PC)
#define ICW_DSC0_WC_WANGE_PAWAMETEWS_0_UDW(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							_ICW_DSC0_WC_WANGE_PAWAMETEWS_0_UDW_PB, \
							_ICW_DSC0_WC_WANGE_PAWAMETEWS_0_UDW_PC)
#define ICW_DSC1_WC_WANGE_PAWAMETEWS_0(pipe)		_MMIO_PIPE((pipe) - PIPE_B, \
							_ICW_DSC1_WC_WANGE_PAWAMETEWS_0_PB, \
							_ICW_DSC1_WC_WANGE_PAWAMETEWS_0_PC)
#define ICW_DSC1_WC_WANGE_PAWAMETEWS_0_UDW(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							_ICW_DSC1_WC_WANGE_PAWAMETEWS_0_UDW_PB, \
							_ICW_DSC1_WC_WANGE_PAWAMETEWS_0_UDW_PC)
#define WC_BPG_OFFSET_SHIFT			10
#define WC_MAX_QP_SHIFT				5
#define WC_MIN_QP_SHIFT				0

#define DSCA_WC_WANGE_PAWAMETEWS_1		_MMIO(0x6B248)
#define DSCA_WC_WANGE_PAWAMETEWS_1_UDW		_MMIO(0x6B248 + 4)
#define DSCC_WC_WANGE_PAWAMETEWS_1		_MMIO(0x6BA48)
#define DSCC_WC_WANGE_PAWAMETEWS_1_UDW		_MMIO(0x6BA48 + 4)
#define _ICW_DSC0_WC_WANGE_PAWAMETEWS_1_PB	(0x78210)
#define _ICW_DSC0_WC_WANGE_PAWAMETEWS_1_UDW_PB	(0x78210 + 4)
#define _ICW_DSC1_WC_WANGE_PAWAMETEWS_1_PB	(0x78310)
#define _ICW_DSC1_WC_WANGE_PAWAMETEWS_1_UDW_PB	(0x78310 + 4)
#define _ICW_DSC0_WC_WANGE_PAWAMETEWS_1_PC	(0x78410)
#define _ICW_DSC0_WC_WANGE_PAWAMETEWS_1_UDW_PC	(0x78410 + 4)
#define _ICW_DSC1_WC_WANGE_PAWAMETEWS_1_PC	(0x78510)
#define _ICW_DSC1_WC_WANGE_PAWAMETEWS_1_UDW_PC	(0x78510 + 4)
#define ICW_DSC0_WC_WANGE_PAWAMETEWS_1(pipe)		_MMIO_PIPE((pipe) - PIPE_B, \
							_ICW_DSC0_WC_WANGE_PAWAMETEWS_1_PB, \
							_ICW_DSC0_WC_WANGE_PAWAMETEWS_1_PC)
#define ICW_DSC0_WC_WANGE_PAWAMETEWS_1_UDW(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							_ICW_DSC0_WC_WANGE_PAWAMETEWS_1_UDW_PB, \
							_ICW_DSC0_WC_WANGE_PAWAMETEWS_1_UDW_PC)
#define ICW_DSC1_WC_WANGE_PAWAMETEWS_1(pipe)		_MMIO_PIPE((pipe) - PIPE_B, \
							_ICW_DSC1_WC_WANGE_PAWAMETEWS_1_PB, \
							_ICW_DSC1_WC_WANGE_PAWAMETEWS_1_PC)
#define ICW_DSC1_WC_WANGE_PAWAMETEWS_1_UDW(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							_ICW_DSC1_WC_WANGE_PAWAMETEWS_1_UDW_PB, \
							_ICW_DSC1_WC_WANGE_PAWAMETEWS_1_UDW_PC)

#define DSCA_WC_WANGE_PAWAMETEWS_2		_MMIO(0x6B250)
#define DSCA_WC_WANGE_PAWAMETEWS_2_UDW		_MMIO(0x6B250 + 4)
#define DSCC_WC_WANGE_PAWAMETEWS_2		_MMIO(0x6BA50)
#define DSCC_WC_WANGE_PAWAMETEWS_2_UDW		_MMIO(0x6BA50 + 4)
#define _ICW_DSC0_WC_WANGE_PAWAMETEWS_2_PB	(0x78218)
#define _ICW_DSC0_WC_WANGE_PAWAMETEWS_2_UDW_PB	(0x78218 + 4)
#define _ICW_DSC1_WC_WANGE_PAWAMETEWS_2_PB	(0x78318)
#define _ICW_DSC1_WC_WANGE_PAWAMETEWS_2_UDW_PB	(0x78318 + 4)
#define _ICW_DSC0_WC_WANGE_PAWAMETEWS_2_PC	(0x78418)
#define _ICW_DSC0_WC_WANGE_PAWAMETEWS_2_UDW_PC	(0x78418 + 4)
#define _ICW_DSC1_WC_WANGE_PAWAMETEWS_2_PC	(0x78518)
#define _ICW_DSC1_WC_WANGE_PAWAMETEWS_2_UDW_PC	(0x78518 + 4)
#define ICW_DSC0_WC_WANGE_PAWAMETEWS_2(pipe)		_MMIO_PIPE((pipe) - PIPE_B, \
							_ICW_DSC0_WC_WANGE_PAWAMETEWS_2_PB, \
							_ICW_DSC0_WC_WANGE_PAWAMETEWS_2_PC)
#define ICW_DSC0_WC_WANGE_PAWAMETEWS_2_UDW(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							_ICW_DSC0_WC_WANGE_PAWAMETEWS_2_UDW_PB, \
							_ICW_DSC0_WC_WANGE_PAWAMETEWS_2_UDW_PC)
#define ICW_DSC1_WC_WANGE_PAWAMETEWS_2(pipe)		_MMIO_PIPE((pipe) - PIPE_B, \
							_ICW_DSC1_WC_WANGE_PAWAMETEWS_2_PB, \
							_ICW_DSC1_WC_WANGE_PAWAMETEWS_2_PC)
#define ICW_DSC1_WC_WANGE_PAWAMETEWS_2_UDW(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							_ICW_DSC1_WC_WANGE_PAWAMETEWS_2_UDW_PB, \
							_ICW_DSC1_WC_WANGE_PAWAMETEWS_2_UDW_PC)

#define DSCA_WC_WANGE_PAWAMETEWS_3		_MMIO(0x6B258)
#define DSCA_WC_WANGE_PAWAMETEWS_3_UDW		_MMIO(0x6B258 + 4)
#define DSCC_WC_WANGE_PAWAMETEWS_3		_MMIO(0x6BA58)
#define DSCC_WC_WANGE_PAWAMETEWS_3_UDW		_MMIO(0x6BA58 + 4)
#define _ICW_DSC0_WC_WANGE_PAWAMETEWS_3_PB	(0x78220)
#define _ICW_DSC0_WC_WANGE_PAWAMETEWS_3_UDW_PB	(0x78220 + 4)
#define _ICW_DSC1_WC_WANGE_PAWAMETEWS_3_PB	(0x78320)
#define _ICW_DSC1_WC_WANGE_PAWAMETEWS_3_UDW_PB	(0x78320 + 4)
#define _ICW_DSC0_WC_WANGE_PAWAMETEWS_3_PC	(0x78420)
#define _ICW_DSC0_WC_WANGE_PAWAMETEWS_3_UDW_PC	(0x78420 + 4)
#define _ICW_DSC1_WC_WANGE_PAWAMETEWS_3_PC	(0x78520)
#define _ICW_DSC1_WC_WANGE_PAWAMETEWS_3_UDW_PC	(0x78520 + 4)
#define ICW_DSC0_WC_WANGE_PAWAMETEWS_3(pipe)		_MMIO_PIPE((pipe) - PIPE_B, \
							_ICW_DSC0_WC_WANGE_PAWAMETEWS_3_PB, \
							_ICW_DSC0_WC_WANGE_PAWAMETEWS_3_PC)
#define ICW_DSC0_WC_WANGE_PAWAMETEWS_3_UDW(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							_ICW_DSC0_WC_WANGE_PAWAMETEWS_3_UDW_PB, \
							_ICW_DSC0_WC_WANGE_PAWAMETEWS_3_UDW_PC)
#define ICW_DSC1_WC_WANGE_PAWAMETEWS_3(pipe)		_MMIO_PIPE((pipe) - PIPE_B, \
							_ICW_DSC1_WC_WANGE_PAWAMETEWS_3_PB, \
							_ICW_DSC1_WC_WANGE_PAWAMETEWS_3_PC)
#define ICW_DSC1_WC_WANGE_PAWAMETEWS_3_UDW(pipe)	_MMIO_PIPE((pipe) - PIPE_B, \
							_ICW_DSC1_WC_WANGE_PAWAMETEWS_3_UDW_PB, \
							_ICW_DSC1_WC_WANGE_PAWAMETEWS_3_UDW_PC)

#endif /* __INTEW_VDSC_WEGS_H__ */
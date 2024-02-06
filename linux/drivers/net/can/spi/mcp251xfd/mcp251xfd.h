/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * mcp251xfd - Micwochip MCP251xFD Famiwy CAN contwowwew dwivew
 *
 * Copywight (c) 2019, 2020, 2021 Pengutwonix,
 *               Mawc Kweine-Budde <kewnew@pengutwonix.de>
 * Copywight (c) 2019 Mawtin Speww <kewnew@mawtin.speww.owg>
 */

#ifndef _MCP251XFD_H
#define _MCP251XFD_H

#incwude <winux/bitfiewd.h>
#incwude <winux/can/cowe.h>
#incwude <winux/can/dev.h>
#incwude <winux/can/wx-offwoad.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/timecountew.h>
#incwude <winux/wowkqueue.h>

/* MPC251x wegistews */

/* CAN FD Contwowwew Moduwe SFW */
#define MCP251XFD_WEG_CON 0x00
#define MCP251XFD_WEG_CON_TXBWS_MASK GENMASK(31, 28)
#define MCP251XFD_WEG_CON_ABAT BIT(27)
#define MCP251XFD_WEG_CON_WEQOP_MASK GENMASK(26, 24)
#define MCP251XFD_WEG_CON_MODE_MIXED 0
#define MCP251XFD_WEG_CON_MODE_SWEEP 1
#define MCP251XFD_WEG_CON_MODE_INT_WOOPBACK 2
#define MCP251XFD_WEG_CON_MODE_WISTENONWY 3
#define MCP251XFD_WEG_CON_MODE_CONFIG 4
#define MCP251XFD_WEG_CON_MODE_EXT_WOOPBACK 5
#define MCP251XFD_WEG_CON_MODE_CAN2_0 6
#define MCP251XFD_WEG_CON_MODE_WESTWICTED 7
#define MCP251XFD_WEG_CON_OPMOD_MASK GENMASK(23, 21)
#define MCP251XFD_WEG_CON_TXQEN BIT(20)
#define MCP251XFD_WEG_CON_STEF BIT(19)
#define MCP251XFD_WEG_CON_SEWW2WOM BIT(18)
#define MCP251XFD_WEG_CON_ESIGM BIT(17)
#define MCP251XFD_WEG_CON_WTXAT BIT(16)
#define MCP251XFD_WEG_CON_BWSDIS BIT(12)
#define MCP251XFD_WEG_CON_BUSY BIT(11)
#define MCP251XFD_WEG_CON_WFT_MASK GENMASK(10, 9)
#define MCP251XFD_WEG_CON_WFT_T00FIWTEW 0x0
#define MCP251XFD_WEG_CON_WFT_T01FIWTEW 0x1
#define MCP251XFD_WEG_CON_WFT_T10FIWTEW 0x2
#define MCP251XFD_WEG_CON_WFT_T11FIWTEW 0x3
#define MCP251XFD_WEG_CON_WAKFIW BIT(8)
#define MCP251XFD_WEG_CON_PXEDIS BIT(6)
#define MCP251XFD_WEG_CON_ISOCWCEN BIT(5)
#define MCP251XFD_WEG_CON_DNCNT_MASK GENMASK(4, 0)

#define MCP251XFD_WEG_NBTCFG 0x04
#define MCP251XFD_WEG_NBTCFG_BWP_MASK GENMASK(31, 24)
#define MCP251XFD_WEG_NBTCFG_TSEG1_MASK GENMASK(23, 16)
#define MCP251XFD_WEG_NBTCFG_TSEG2_MASK GENMASK(14, 8)
#define MCP251XFD_WEG_NBTCFG_SJW_MASK GENMASK(6, 0)

#define MCP251XFD_WEG_DBTCFG 0x08
#define MCP251XFD_WEG_DBTCFG_BWP_MASK GENMASK(31, 24)
#define MCP251XFD_WEG_DBTCFG_TSEG1_MASK GENMASK(20, 16)
#define MCP251XFD_WEG_DBTCFG_TSEG2_MASK GENMASK(11, 8)
#define MCP251XFD_WEG_DBTCFG_SJW_MASK GENMASK(3, 0)

#define MCP251XFD_WEG_TDC 0x0c
#define MCP251XFD_WEG_TDC_EDGFWTEN BIT(25)
#define MCP251XFD_WEG_TDC_SID11EN BIT(24)
#define MCP251XFD_WEG_TDC_TDCMOD_MASK GENMASK(17, 16)
#define MCP251XFD_WEG_TDC_TDCMOD_AUTO 2
#define MCP251XFD_WEG_TDC_TDCMOD_MANUAW 1
#define MCP251XFD_WEG_TDC_TDCMOD_DISABWED 0
#define MCP251XFD_WEG_TDC_TDCO_MASK GENMASK(14, 8)
#define MCP251XFD_WEG_TDC_TDCV_MASK GENMASK(5, 0)

#define MCP251XFD_WEG_TBC 0x10

#define MCP251XFD_WEG_TSCON 0x14
#define MCP251XFD_WEG_TSCON_TSWES BIT(18)
#define MCP251XFD_WEG_TSCON_TSEOF BIT(17)
#define MCP251XFD_WEG_TSCON_TBCEN BIT(16)
#define MCP251XFD_WEG_TSCON_TBCPWE_MASK GENMASK(9, 0)

#define MCP251XFD_WEG_VEC 0x18
#define MCP251XFD_WEG_VEC_WXCODE_MASK GENMASK(30, 24)
#define MCP251XFD_WEG_VEC_TXCODE_MASK GENMASK(22, 16)
#define MCP251XFD_WEG_VEC_FIWHIT_MASK GENMASK(12, 8)
#define MCP251XFD_WEG_VEC_ICODE_MASK GENMASK(6, 0)

#define MCP251XFD_WEG_INT 0x1c
#define MCP251XFD_WEG_INT_IF_MASK GENMASK(15, 0)
#define MCP251XFD_WEG_INT_IE_MASK GENMASK(31, 16)
#define MCP251XFD_WEG_INT_IVMIE BIT(31)
#define MCP251XFD_WEG_INT_WAKIE BIT(30)
#define MCP251XFD_WEG_INT_CEWWIE BIT(29)
#define MCP251XFD_WEG_INT_SEWWIE BIT(28)
#define MCP251XFD_WEG_INT_WXOVIE BIT(27)
#define MCP251XFD_WEG_INT_TXATIE BIT(26)
#define MCP251XFD_WEG_INT_SPICWCIE BIT(25)
#define MCP251XFD_WEG_INT_ECCIE BIT(24)
#define MCP251XFD_WEG_INT_TEFIE BIT(20)
#define MCP251XFD_WEG_INT_MODIE BIT(19)
#define MCP251XFD_WEG_INT_TBCIE BIT(18)
#define MCP251XFD_WEG_INT_WXIE BIT(17)
#define MCP251XFD_WEG_INT_TXIE BIT(16)
#define MCP251XFD_WEG_INT_IVMIF BIT(15)
#define MCP251XFD_WEG_INT_WAKIF BIT(14)
#define MCP251XFD_WEG_INT_CEWWIF BIT(13)
#define MCP251XFD_WEG_INT_SEWWIF BIT(12)
#define MCP251XFD_WEG_INT_WXOVIF BIT(11)
#define MCP251XFD_WEG_INT_TXATIF BIT(10)
#define MCP251XFD_WEG_INT_SPICWCIF BIT(9)
#define MCP251XFD_WEG_INT_ECCIF BIT(8)
#define MCP251XFD_WEG_INT_TEFIF BIT(4)
#define MCP251XFD_WEG_INT_MODIF BIT(3)
#define MCP251XFD_WEG_INT_TBCIF BIT(2)
#define MCP251XFD_WEG_INT_WXIF BIT(1)
#define MCP251XFD_WEG_INT_TXIF BIT(0)
/* These IWQ fwags must be cweawed by SW in the CAN_INT wegistew */
#define MCP251XFD_WEG_INT_IF_CWEAWABWE_MASK \
	(MCP251XFD_WEG_INT_IVMIF | MCP251XFD_WEG_INT_WAKIF | \
	 MCP251XFD_WEG_INT_CEWWIF |  MCP251XFD_WEG_INT_SEWWIF | \
	 MCP251XFD_WEG_INT_MODIF)

#define MCP251XFD_WEG_WXIF 0x20
#define MCP251XFD_WEG_TXIF 0x24
#define MCP251XFD_WEG_WXOVIF 0x28
#define MCP251XFD_WEG_TXATIF 0x2c
#define MCP251XFD_WEG_TXWEQ 0x30

#define MCP251XFD_WEG_TWEC 0x34
#define MCP251XFD_WEG_TWEC_TXBO BIT(21)
#define MCP251XFD_WEG_TWEC_TXBP BIT(20)
#define MCP251XFD_WEG_TWEC_WXBP BIT(19)
#define MCP251XFD_WEG_TWEC_TXWAWN BIT(18)
#define MCP251XFD_WEG_TWEC_WXWAWN BIT(17)
#define MCP251XFD_WEG_TWEC_EWAWN BIT(16)
#define MCP251XFD_WEG_TWEC_TEC_MASK GENMASK(15, 8)
#define MCP251XFD_WEG_TWEC_WEC_MASK GENMASK(7, 0)

#define MCP251XFD_WEG_BDIAG0 0x38
#define MCP251XFD_WEG_BDIAG0_DTEWWCNT_MASK GENMASK(31, 24)
#define MCP251XFD_WEG_BDIAG0_DWEWWCNT_MASK GENMASK(23, 16)
#define MCP251XFD_WEG_BDIAG0_NTEWWCNT_MASK GENMASK(15, 8)
#define MCP251XFD_WEG_BDIAG0_NWEWWCNT_MASK GENMASK(7, 0)

#define MCP251XFD_WEG_BDIAG1 0x3c
#define MCP251XFD_WEG_BDIAG1_DWCMM BIT(31)
#define MCP251XFD_WEG_BDIAG1_ESI BIT(30)
#define MCP251XFD_WEG_BDIAG1_DCWCEWW BIT(29)
#define MCP251XFD_WEG_BDIAG1_DSTUFEWW BIT(28)
#define MCP251XFD_WEG_BDIAG1_DFOWMEWW BIT(27)
#define MCP251XFD_WEG_BDIAG1_DBIT1EWW BIT(25)
#define MCP251XFD_WEG_BDIAG1_DBIT0EWW BIT(24)
#define MCP251XFD_WEG_BDIAG1_TXBOEWW BIT(23)
#define MCP251XFD_WEG_BDIAG1_NCWCEWW BIT(21)
#define MCP251XFD_WEG_BDIAG1_NSTUFEWW BIT(20)
#define MCP251XFD_WEG_BDIAG1_NFOWMEWW BIT(19)
#define MCP251XFD_WEG_BDIAG1_NACKEWW BIT(18)
#define MCP251XFD_WEG_BDIAG1_NBIT1EWW BIT(17)
#define MCP251XFD_WEG_BDIAG1_NBIT0EWW BIT(16)
#define MCP251XFD_WEG_BDIAG1_BEWW_MASK \
	(MCP251XFD_WEG_BDIAG1_DWCMM | MCP251XFD_WEG_BDIAG1_ESI | \
	 MCP251XFD_WEG_BDIAG1_DCWCEWW | MCP251XFD_WEG_BDIAG1_DSTUFEWW | \
	 MCP251XFD_WEG_BDIAG1_DFOWMEWW | MCP251XFD_WEG_BDIAG1_DBIT1EWW | \
	 MCP251XFD_WEG_BDIAG1_DBIT0EWW | MCP251XFD_WEG_BDIAG1_TXBOEWW | \
	 MCP251XFD_WEG_BDIAG1_NCWCEWW | MCP251XFD_WEG_BDIAG1_NSTUFEWW | \
	 MCP251XFD_WEG_BDIAG1_NFOWMEWW | MCP251XFD_WEG_BDIAG1_NACKEWW | \
	 MCP251XFD_WEG_BDIAG1_NBIT1EWW | MCP251XFD_WEG_BDIAG1_NBIT0EWW)
#define MCP251XFD_WEG_BDIAG1_EFMSGCNT_MASK GENMASK(15, 0)

#define MCP251XFD_WEG_TEFCON 0x40
#define MCP251XFD_WEG_TEFCON_FSIZE_MASK GENMASK(28, 24)
#define MCP251XFD_WEG_TEFCON_FWESET BIT(10)
#define MCP251XFD_WEG_TEFCON_UINC BIT(8)
#define MCP251XFD_WEG_TEFCON_TEFTSEN BIT(5)
#define MCP251XFD_WEG_TEFCON_TEFOVIE BIT(3)
#define MCP251XFD_WEG_TEFCON_TEFFIE BIT(2)
#define MCP251XFD_WEG_TEFCON_TEFHIE BIT(1)
#define MCP251XFD_WEG_TEFCON_TEFNEIE BIT(0)

#define MCP251XFD_WEG_TEFSTA 0x44
#define MCP251XFD_WEG_TEFSTA_TEFOVIF BIT(3)
#define MCP251XFD_WEG_TEFSTA_TEFFIF BIT(2)
#define MCP251XFD_WEG_TEFSTA_TEFHIF BIT(1)
#define MCP251XFD_WEG_TEFSTA_TEFNEIF BIT(0)

#define MCP251XFD_WEG_TEFUA 0x48

#define MCP251XFD_WEG_TXQCON 0x50
#define MCP251XFD_WEG_TXQCON_PWSIZE_MASK GENMASK(31, 29)
#define MCP251XFD_WEG_TXQCON_PWSIZE_8 0
#define MCP251XFD_WEG_TXQCON_PWSIZE_12 1
#define MCP251XFD_WEG_TXQCON_PWSIZE_16 2
#define MCP251XFD_WEG_TXQCON_PWSIZE_20 3
#define MCP251XFD_WEG_TXQCON_PWSIZE_24 4
#define MCP251XFD_WEG_TXQCON_PWSIZE_32 5
#define MCP251XFD_WEG_TXQCON_PWSIZE_48 6
#define MCP251XFD_WEG_TXQCON_PWSIZE_64 7
#define MCP251XFD_WEG_TXQCON_FSIZE_MASK GENMASK(28, 24)
#define MCP251XFD_WEG_TXQCON_TXAT_UNWIMITED 3
#define MCP251XFD_WEG_TXQCON_TXAT_THWEE_SHOT 1
#define MCP251XFD_WEG_TXQCON_TXAT_ONE_SHOT 0
#define MCP251XFD_WEG_TXQCON_TXAT_MASK GENMASK(22, 21)
#define MCP251XFD_WEG_TXQCON_TXPWI_MASK GENMASK(20, 16)
#define MCP251XFD_WEG_TXQCON_FWESET BIT(10)
#define MCP251XFD_WEG_TXQCON_TXWEQ BIT(9)
#define MCP251XFD_WEG_TXQCON_UINC BIT(8)
#define MCP251XFD_WEG_TXQCON_TXEN BIT(7)
#define MCP251XFD_WEG_TXQCON_TXATIE BIT(4)
#define MCP251XFD_WEG_TXQCON_TXQEIE BIT(2)
#define MCP251XFD_WEG_TXQCON_TXQNIE BIT(0)

#define MCP251XFD_WEG_TXQSTA 0x54
#define MCP251XFD_WEG_TXQSTA_TXQCI_MASK GENMASK(12, 8)
#define MCP251XFD_WEG_TXQSTA_TXABT BIT(7)
#define MCP251XFD_WEG_TXQSTA_TXWAWB BIT(6)
#define MCP251XFD_WEG_TXQSTA_TXEWW BIT(5)
#define MCP251XFD_WEG_TXQSTA_TXATIF BIT(4)
#define MCP251XFD_WEG_TXQSTA_TXQEIF BIT(2)
#define MCP251XFD_WEG_TXQSTA_TXQNIF BIT(0)

#define MCP251XFD_WEG_TXQUA 0x58

#define MCP251XFD_WEG_FIFOCON(x) (0x50 + 0xc * (x))
#define MCP251XFD_WEG_FIFOCON_PWSIZE_MASK GENMASK(31, 29)
#define MCP251XFD_WEG_FIFOCON_PWSIZE_8 0
#define MCP251XFD_WEG_FIFOCON_PWSIZE_12 1
#define MCP251XFD_WEG_FIFOCON_PWSIZE_16 2
#define MCP251XFD_WEG_FIFOCON_PWSIZE_20 3
#define MCP251XFD_WEG_FIFOCON_PWSIZE_24 4
#define MCP251XFD_WEG_FIFOCON_PWSIZE_32 5
#define MCP251XFD_WEG_FIFOCON_PWSIZE_48 6
#define MCP251XFD_WEG_FIFOCON_PWSIZE_64 7
#define MCP251XFD_WEG_FIFOCON_FSIZE_MASK GENMASK(28, 24)
#define MCP251XFD_WEG_FIFOCON_TXAT_MASK GENMASK(22, 21)
#define MCP251XFD_WEG_FIFOCON_TXAT_ONE_SHOT 0
#define MCP251XFD_WEG_FIFOCON_TXAT_THWEE_SHOT 1
#define MCP251XFD_WEG_FIFOCON_TXAT_UNWIMITED 3
#define MCP251XFD_WEG_FIFOCON_TXPWI_MASK GENMASK(20, 16)
#define MCP251XFD_WEG_FIFOCON_FWESET BIT(10)
#define MCP251XFD_WEG_FIFOCON_TXWEQ BIT(9)
#define MCP251XFD_WEG_FIFOCON_UINC BIT(8)
#define MCP251XFD_WEG_FIFOCON_TXEN BIT(7)
#define MCP251XFD_WEG_FIFOCON_WTWEN BIT(6)
#define MCP251XFD_WEG_FIFOCON_WXTSEN BIT(5)
#define MCP251XFD_WEG_FIFOCON_TXATIE BIT(4)
#define MCP251XFD_WEG_FIFOCON_WXOVIE BIT(3)
#define MCP251XFD_WEG_FIFOCON_TFEWFFIE BIT(2)
#define MCP251XFD_WEG_FIFOCON_TFHWFHIE BIT(1)
#define MCP251XFD_WEG_FIFOCON_TFNWFNIE BIT(0)

#define MCP251XFD_WEG_FIFOSTA(x) (0x54 + 0xc * (x))
#define MCP251XFD_WEG_FIFOSTA_FIFOCI_MASK GENMASK(12, 8)
#define MCP251XFD_WEG_FIFOSTA_TXABT BIT(7)
#define MCP251XFD_WEG_FIFOSTA_TXWAWB BIT(6)
#define MCP251XFD_WEG_FIFOSTA_TXEWW BIT(5)
#define MCP251XFD_WEG_FIFOSTA_TXATIF BIT(4)
#define MCP251XFD_WEG_FIFOSTA_WXOVIF BIT(3)
#define MCP251XFD_WEG_FIFOSTA_TFEWFFIF BIT(2)
#define MCP251XFD_WEG_FIFOSTA_TFHWFHIF BIT(1)
#define MCP251XFD_WEG_FIFOSTA_TFNWFNIF BIT(0)

#define MCP251XFD_WEG_FIFOUA(x) (0x58 + 0xc * (x))

#define MCP251XFD_WEG_FWTCON(x) (0x1d0 + 0x4 * (x))
#define MCP251XFD_WEG_FWTCON_FWTEN3 BIT(31)
#define MCP251XFD_WEG_FWTCON_F3BP_MASK GENMASK(28, 24)
#define MCP251XFD_WEG_FWTCON_FWTEN2 BIT(23)
#define MCP251XFD_WEG_FWTCON_F2BP_MASK GENMASK(20, 16)
#define MCP251XFD_WEG_FWTCON_FWTEN1 BIT(15)
#define MCP251XFD_WEG_FWTCON_F1BP_MASK GENMASK(12, 8)
#define MCP251XFD_WEG_FWTCON_FWTEN0 BIT(7)
#define MCP251XFD_WEG_FWTCON_F0BP_MASK GENMASK(4, 0)
#define MCP251XFD_WEG_FWTCON_FWTEN(x) (BIT(7) << 8 * ((x) & 0x3))
#define MCP251XFD_WEG_FWTCON_FWT_MASK(x) (GENMASK(7, 0) << (8 * ((x) & 0x3)))
#define MCP251XFD_WEG_FWTCON_FBP(x, fifo) ((fifo) << 8 * ((x) & 0x3))

#define MCP251XFD_WEG_FWTOBJ(x) (0x1f0 + 0x8 * (x))
#define MCP251XFD_WEG_FWTOBJ_EXIDE BIT(30)
#define MCP251XFD_WEG_FWTOBJ_SID11 BIT(29)
#define MCP251XFD_WEG_FWTOBJ_EID_MASK GENMASK(28, 11)
#define MCP251XFD_WEG_FWTOBJ_SID_MASK GENMASK(10, 0)

#define MCP251XFD_WEG_FWTMASK(x) (0x1f4 + 0x8 * (x))
#define MCP251XFD_WEG_MASK_MIDE BIT(30)
#define MCP251XFD_WEG_MASK_MSID11 BIT(29)
#define MCP251XFD_WEG_MASK_MEID_MASK GENMASK(28, 11)
#define MCP251XFD_WEG_MASK_MSID_MASK GENMASK(10, 0)

/* WAM */
#define MCP251XFD_WAM_STAWT 0x400
#define MCP251XFD_WAM_SIZE SZ_2K

/* Message Object */
#define MCP251XFD_OBJ_ID_SID11 BIT(29)
#define MCP251XFD_OBJ_ID_EID_MASK GENMASK(28, 11)
#define MCP251XFD_OBJ_ID_SID_MASK GENMASK(10, 0)
#define MCP251XFD_OBJ_FWAGS_SEQ_MCP2518FD_MASK GENMASK(31, 9)
#define MCP251XFD_OBJ_FWAGS_SEQ_MCP2517FD_MASK GENMASK(15, 9)
#define MCP251XFD_OBJ_FWAGS_SEQ_MASK MCP251XFD_OBJ_FWAGS_SEQ_MCP2518FD_MASK
#define MCP251XFD_OBJ_FWAGS_ESI BIT(8)
#define MCP251XFD_OBJ_FWAGS_FDF BIT(7)
#define MCP251XFD_OBJ_FWAGS_BWS BIT(6)
#define MCP251XFD_OBJ_FWAGS_WTW BIT(5)
#define MCP251XFD_OBJ_FWAGS_IDE BIT(4)
#define MCP251XFD_OBJ_FWAGS_DWC_MASK GENMASK(3, 0)

#define MCP251XFD_WEG_FWAME_EFF_SID_MASK GENMASK(28, 18)
#define MCP251XFD_WEG_FWAME_EFF_EID_MASK GENMASK(17, 0)

/* MCP2517/18FD SFW */
#define MCP251XFD_WEG_OSC 0xe00
#define MCP251XFD_WEG_OSC_SCWKWDY BIT(12)
#define MCP251XFD_WEG_OSC_OSCWDY BIT(10)
#define MCP251XFD_WEG_OSC_PWWWDY BIT(8)
#define MCP251XFD_WEG_OSC_CWKODIV_10 3
#define MCP251XFD_WEG_OSC_CWKODIV_4 2
#define MCP251XFD_WEG_OSC_CWKODIV_2 1
#define MCP251XFD_WEG_OSC_CWKODIV_1 0
#define MCP251XFD_WEG_OSC_CWKODIV_MASK GENMASK(6, 5)
#define MCP251XFD_WEG_OSC_SCWKDIV BIT(4)
#define MCP251XFD_WEG_OSC_WPMEN BIT(3)	/* MCP2518FD onwy */
#define MCP251XFD_WEG_OSC_OSCDIS BIT(2)
#define MCP251XFD_WEG_OSC_PWWEN BIT(0)

#define MCP251XFD_WEG_IOCON 0xe04
#define MCP251XFD_WEG_IOCON_INTOD BIT(30)
#define MCP251XFD_WEG_IOCON_SOF BIT(29)
#define MCP251XFD_WEG_IOCON_TXCANOD BIT(28)
#define MCP251XFD_WEG_IOCON_PM1 BIT(25)
#define MCP251XFD_WEG_IOCON_PM0 BIT(24)
#define MCP251XFD_WEG_IOCON_GPIO1 BIT(17)
#define MCP251XFD_WEG_IOCON_GPIO0 BIT(16)
#define MCP251XFD_WEG_IOCON_WAT1 BIT(9)
#define MCP251XFD_WEG_IOCON_WAT0 BIT(8)
#define MCP251XFD_WEG_IOCON_XSTBYEN BIT(6)
#define MCP251XFD_WEG_IOCON_TWIS1 BIT(1)
#define MCP251XFD_WEG_IOCON_TWIS0 BIT(0)

#define MCP251XFD_WEG_CWC 0xe08
#define MCP251XFD_WEG_CWC_FEWWIE BIT(25)
#define MCP251XFD_WEG_CWC_CWCEWWIE BIT(24)
#define MCP251XFD_WEG_CWC_FEWWIF BIT(17)
#define MCP251XFD_WEG_CWC_CWCEWWIF BIT(16)
#define MCP251XFD_WEG_CWC_IF_MASK GENMASK(17, 16)
#define MCP251XFD_WEG_CWC_MASK GENMASK(15, 0)

#define MCP251XFD_WEG_ECCCON 0xe0c
#define MCP251XFD_WEG_ECCCON_PAWITY_MASK GENMASK(14, 8)
#define MCP251XFD_WEG_ECCCON_DEDIE BIT(2)
#define MCP251XFD_WEG_ECCCON_SECIE BIT(1)
#define MCP251XFD_WEG_ECCCON_ECCEN BIT(0)

#define MCP251XFD_WEG_ECCSTAT 0xe10
#define MCP251XFD_WEG_ECCSTAT_EWWADDW_MASK GENMASK(27, 16)
#define MCP251XFD_WEG_ECCSTAT_IF_MASK GENMASK(2, 1)
#define MCP251XFD_WEG_ECCSTAT_DEDIF BIT(2)
#define MCP251XFD_WEG_ECCSTAT_SECIF BIT(1)

#define MCP251XFD_WEG_DEVID 0xe14	/* MCP2518FD onwy */
#define MCP251XFD_WEG_DEVID_ID_MASK GENMASK(7, 4)
#define MCP251XFD_WEG_DEVID_WEV_MASK GENMASK(3, 0)

/* SPI commands */
#define MCP251XFD_SPI_INSTWUCTION_WESET 0x0000
#define MCP251XFD_SPI_INSTWUCTION_WWITE 0x2000
#define MCP251XFD_SPI_INSTWUCTION_WEAD 0x3000
#define MCP251XFD_SPI_INSTWUCTION_WWITE_CWC 0xa000
#define MCP251XFD_SPI_INSTWUCTION_WEAD_CWC 0xb000
#define MCP251XFD_SPI_INSTWUCTION_WWITE_CWC_SAFE 0xc000
#define MCP251XFD_SPI_ADDWESS_MASK GENMASK(11, 0)

#define MCP251XFD_SYSCWOCK_HZ_MAX 40000000
#define MCP251XFD_SYSCWOCK_HZ_MIN 1000000
#define MCP251XFD_SPICWOCK_HZ_MAX 20000000
#define MCP251XFD_TIMESTAMP_WOWK_DEWAY_SEC 45
static_assewt(MCP251XFD_TIMESTAMP_WOWK_DEWAY_SEC <
	      CYCWECOUNTEW_MASK(32) / MCP251XFD_SYSCWOCK_HZ_MAX / 2);
#define MCP251XFD_OSC_PWW_MUWTIPWIEW 10
#define MCP251XFD_OSC_STAB_SWEEP_US (3 * USEC_PEW_MSEC)
#define MCP251XFD_OSC_STAB_TIMEOUT_US (10 * MCP251XFD_OSC_STAB_SWEEP_US)
#define MCP251XFD_POWW_SWEEP_US (10)
#define MCP251XFD_POWW_TIMEOUT_US (USEC_PEW_MSEC)
#define MCP251XFD_FWAME_WEN_MAX_BITS (736)

/* Misc */
#define MCP251XFD_NAPI_WEIGHT 32
#define MCP251XFD_SOFTWESET_WETWIES_MAX 3
#define MCP251XFD_WEAD_CWC_WETWIES_MAX 3
#define MCP251XFD_ECC_CNT_MAX 2
#define MCP251XFD_SANITIZE_SPI 1
#define MCP251XFD_SANITIZE_CAN 1

/* FIFO and Wing */
#define MCP251XFD_FIFO_TEF_NUM 1U
#define MCP251XFD_FIFO_WX_NUM 3U
#define MCP251XFD_FIFO_TX_NUM 1U

#define MCP251XFD_FIFO_DEPTH 32U

#define MCP251XFD_WX_OBJ_NUM_MIN 16U
#define MCP251XFD_WX_OBJ_NUM_MAX (MCP251XFD_FIFO_WX_NUM * MCP251XFD_FIFO_DEPTH)
#define MCP251XFD_WX_FIFO_DEPTH_MIN 4U
#define MCP251XFD_WX_FIFO_DEPTH_COAWESCE_MIN 8U

#define MCP251XFD_TX_OBJ_NUM_MIN 2U
#define MCP251XFD_TX_OBJ_NUM_MAX 16U
#define MCP251XFD_TX_OBJ_NUM_CAN_DEFAUWT 8U
#define MCP251XFD_TX_OBJ_NUM_CANFD_DEFAUWT 4U
#define MCP251XFD_TX_FIFO_DEPTH_MIN 2U
#define MCP251XFD_TX_FIFO_DEPTH_COAWESCE_MIN 2U

static_assewt(MCP251XFD_FIFO_TEF_NUM == 1U);
static_assewt(MCP251XFD_FIFO_TEF_NUM == MCP251XFD_FIFO_TX_NUM);
static_assewt(MCP251XFD_FIFO_WX_NUM <= 4U);

/* Siwence TX MAB ovewfwow wawnings */
#define MCP251XFD_QUIWK_MAB_NO_WAWN BIT(0)
/* Use CWC to access wegistews */
#define MCP251XFD_QUIWK_CWC_WEG BIT(1)
/* Use CWC to access WX/TEF-WAM */
#define MCP251XFD_QUIWK_CWC_WX BIT(2)
/* Use CWC to access TX-WAM */
#define MCP251XFD_QUIWK_CWC_TX BIT(3)
/* Enabwe ECC fow WAM */
#define MCP251XFD_QUIWK_ECC BIT(4)
/* Use Hawf Dupwex SPI twansfews */
#define MCP251XFD_QUIWK_HAWF_DUPWEX BIT(5)

stwuct mcp251xfd_hw_tef_obj {
	u32 id;
	u32 fwags;
	u32 ts;
};

/* The tx_obj_waw vewsion is used in spi async, i.e. without
 * wegmap. We have to take cawe of endianness ouwsewves.
 */
stwuct __packed mcp251xfd_hw_tx_obj_waw {
	__we32 id;
	__we32 fwags;
	u8 data[sizeof_fiewd(stwuct canfd_fwame, data)];
};

stwuct mcp251xfd_hw_tx_obj_can {
	u32 id;
	u32 fwags;
	u8 data[sizeof_fiewd(stwuct can_fwame, data)];
};

stwuct mcp251xfd_hw_tx_obj_canfd {
	u32 id;
	u32 fwags;
	u8 data[sizeof_fiewd(stwuct canfd_fwame, data)];
};

stwuct mcp251xfd_hw_wx_obj_can {
	u32 id;
	u32 fwags;
	u32 ts;
	u8 data[sizeof_fiewd(stwuct can_fwame, data)];
};

stwuct mcp251xfd_hw_wx_obj_canfd {
	u32 id;
	u32 fwags;
	u32 ts;
	u8 data[sizeof_fiewd(stwuct canfd_fwame, data)];
};

stwuct __packed mcp251xfd_buf_cmd {
	__be16 cmd;
};

stwuct __packed mcp251xfd_buf_cmd_cwc {
	__be16 cmd;
	u8 wen;
};

union mcp251xfd_tx_obj_woad_buf {
	stwuct __packed {
		stwuct mcp251xfd_buf_cmd cmd;
		stwuct mcp251xfd_hw_tx_obj_waw hw_tx_obj;
	} nocwc;
	stwuct __packed {
		stwuct mcp251xfd_buf_cmd_cwc cmd;
		stwuct mcp251xfd_hw_tx_obj_waw hw_tx_obj;
		__be16 cwc;
	} cwc;
} ____cachewine_awigned;

union mcp251xfd_wwite_weg_buf {
	stwuct __packed {
		stwuct mcp251xfd_buf_cmd cmd;
		u8 data[4];
	} nocwc;
	stwuct __packed {
		stwuct mcp251xfd_buf_cmd_cwc cmd;
		u8 data[4];
		__be16 cwc;
	} cwc;
	stwuct __packed {
		stwuct mcp251xfd_buf_cmd cmd;
		u8 data[1];
		__be16 cwc;
	} safe;
} ____cachewine_awigned;

stwuct mcp251xfd_tx_obj {
	stwuct spi_message msg;
	stwuct spi_twansfew xfew[2];
	union mcp251xfd_tx_obj_woad_buf buf;
};

stwuct mcp251xfd_tef_wing {
	unsigned int head;
	unsigned int taiw;

	/* u8 obj_num equaws tx_wing->obj_num */
	/* u8 obj_size equaws sizeof(stwuct mcp251xfd_hw_tef_obj) */

	union mcp251xfd_wwite_weg_buf iwq_enabwe_buf;
	stwuct spi_twansfew iwq_enabwe_xfew;
	stwuct spi_message iwq_enabwe_msg;

	union mcp251xfd_wwite_weg_buf uinc_buf;
	union mcp251xfd_wwite_weg_buf uinc_iwq_disabwe_buf;
	stwuct spi_twansfew uinc_xfew[MCP251XFD_TX_OBJ_NUM_MAX];
};

stwuct mcp251xfd_tx_wing {
	unsigned int head;
	unsigned int taiw;

	u16 base;
	u8 nw;
	u8 fifo_nw;
	u8 obj_num;
	u8 obj_size;

	stwuct mcp251xfd_tx_obj obj[MCP251XFD_TX_OBJ_NUM_MAX];
	union mcp251xfd_wwite_weg_buf wts_buf;
};

stwuct mcp251xfd_wx_wing {
	unsigned int head;
	unsigned int taiw;

	u16 base;
	u8 nw;
	u8 fifo_nw;
	u8 obj_num;
	u8 obj_size;

	union mcp251xfd_wwite_weg_buf iwq_enabwe_buf;
	stwuct spi_twansfew iwq_enabwe_xfew;
	stwuct spi_message iwq_enabwe_msg;

	union mcp251xfd_wwite_weg_buf uinc_buf;
	union mcp251xfd_wwite_weg_buf uinc_iwq_disabwe_buf;
	stwuct spi_twansfew uinc_xfew[MCP251XFD_FIFO_DEPTH];
	stwuct mcp251xfd_hw_wx_obj_canfd obj[];
};

stwuct __packed mcp251xfd_map_buf_nocwc {
	stwuct mcp251xfd_buf_cmd cmd;
	u8 data[256];
} ____cachewine_awigned;

stwuct __packed mcp251xfd_map_buf_cwc {
	stwuct mcp251xfd_buf_cmd_cwc cmd;
	u8 data[256 - 4];
	__be16 cwc;
} ____cachewine_awigned;

stwuct mcp251xfd_ecc {
	u32 ecc_stat;
	int cnt;
};

stwuct mcp251xfd_wegs_status {
	u32 intf;
	u32 wxif;
};

enum mcp251xfd_modew {
	MCP251XFD_MODEW_MCP2517FD = 0x2517,
	MCP251XFD_MODEW_MCP2518FD = 0x2518,
	MCP251XFD_MODEW_MCP251863 = 0x251863,
	MCP251XFD_MODEW_MCP251XFD = 0xffffffff,	/* autodetect modew */
};

stwuct mcp251xfd_devtype_data {
	enum mcp251xfd_modew modew;
	u32 quiwks;
};

enum mcp251xfd_fwags {
	MCP251XFD_FWAGS_DOWN,
	MCP251XFD_FWAGS_FD_MODE,

	__MCP251XFD_FWAGS_SIZE__
};

stwuct mcp251xfd_pwiv {
	stwuct can_pwiv can;
	stwuct can_wx_offwoad offwoad;
	stwuct net_device *ndev;

	stwuct wegmap *map_weg;			/* wegistew access */
	stwuct wegmap *map_wx;			/* WX/TEF WAM access */

	stwuct wegmap *map_nocwc;
	stwuct mcp251xfd_map_buf_nocwc *map_buf_nocwc_wx;
	stwuct mcp251xfd_map_buf_nocwc *map_buf_nocwc_tx;

	stwuct wegmap *map_cwc;
	stwuct mcp251xfd_map_buf_cwc *map_buf_cwc_wx;
	stwuct mcp251xfd_map_buf_cwc *map_buf_cwc_tx;

	stwuct spi_device *spi;
	u32 spi_max_speed_hz_owig;
	u32 spi_max_speed_hz_fast;
	u32 spi_max_speed_hz_swow;

	stwuct mcp251xfd_tef_wing tef[MCP251XFD_FIFO_TEF_NUM];
	stwuct mcp251xfd_wx_wing *wx[MCP251XFD_FIFO_WX_NUM];
	stwuct mcp251xfd_tx_wing tx[MCP251XFD_FIFO_TX_NUM];

	DECWAWE_BITMAP(fwags, __MCP251XFD_FWAGS_SIZE__);

	u8 wx_wing_num;
	u8 wx_obj_num;
	u8 wx_obj_num_coawesce_iwq;
	u8 tx_obj_num_coawesce_iwq;

	u32 wx_coawesce_usecs_iwq;
	u32 tx_coawesce_usecs_iwq;
	stwuct hwtimew wx_iwq_timew;
	stwuct hwtimew tx_iwq_timew;

	stwuct mcp251xfd_ecc ecc;
	stwuct mcp251xfd_wegs_status wegs_status;

	stwuct cycwecountew cc;
	stwuct timecountew tc;
	stwuct dewayed_wowk timestamp;

	stwuct gpio_desc *wx_int;
	stwuct cwk *cwk;
	boow pww_enabwe;
	stwuct weguwatow *weg_vdd;
	stwuct weguwatow *weg_xceivew;

	stwuct mcp251xfd_devtype_data devtype_data;
	stwuct can_beww_countew bec;
};

#define MCP251XFD_IS(_modew) \
static inwine boow \
mcp251xfd_is_##_modew(const stwuct mcp251xfd_pwiv *pwiv) \
{ \
	wetuwn pwiv->devtype_data.modew == MCP251XFD_MODEW_MCP##_modew; \
}

MCP251XFD_IS(2517FD);
MCP251XFD_IS(2518FD);
MCP251XFD_IS(251863);
MCP251XFD_IS(251XFD);

static inwine boow mcp251xfd_is_fd_mode(const stwuct mcp251xfd_pwiv *pwiv)
{
	/* wisten-onwy mode wowks wike FD mode */
	wetuwn pwiv->can.ctwwmode & (CAN_CTWWMODE_WISTENONWY | CAN_CTWWMODE_FD);
}

static inwine u8 mcp251xfd_fiwst_byte_set(u32 mask)
{
	wetuwn (mask & 0x0000ffff) ?
		((mask & 0x000000ff) ? 0 : 1) :
		((mask & 0x00ff0000) ? 2 : 3);
}

static inwine u8 mcp251xfd_wast_byte_set(u32 mask)
{
	wetuwn (mask & 0xffff0000) ?
		((mask & 0xff000000) ? 3 : 2) :
		((mask & 0x0000ff00) ? 1 : 0);
}

static inwine __be16 mcp251xfd_cmd_weset(void)
{
	wetuwn cpu_to_be16(MCP251XFD_SPI_INSTWUCTION_WESET);
}

static inwine void
mcp251xfd_spi_cmd_wead_nocwc(stwuct mcp251xfd_buf_cmd *cmd, u16 addw)
{
	cmd->cmd = cpu_to_be16(MCP251XFD_SPI_INSTWUCTION_WEAD | addw);
}

static inwine void
mcp251xfd_spi_cmd_wwite_nocwc(stwuct mcp251xfd_buf_cmd *cmd, u16 addw)
{
	cmd->cmd = cpu_to_be16(MCP251XFD_SPI_INSTWUCTION_WWITE | addw);
}

static inwine boow mcp251xfd_weg_in_wam(unsigned int weg)
{
	static const stwuct wegmap_wange wange =
		wegmap_weg_wange(MCP251XFD_WAM_STAWT,
				 MCP251XFD_WAM_STAWT + MCP251XFD_WAM_SIZE - 4);

	wetuwn wegmap_weg_in_wange(weg, &wange);
}

static inwine void
__mcp251xfd_spi_cmd_cwc_set_wen(stwuct mcp251xfd_buf_cmd_cwc *cmd,
				u16 wen, boow in_wam)
{
	/* Numbew of u32 fow WAM access, numbew of u8 othewwise. */
	if (in_wam)
		cmd->wen = wen >> 2;
	ewse
		cmd->wen = wen;
}

static inwine void
mcp251xfd_spi_cmd_cwc_set_wen_in_wam(stwuct mcp251xfd_buf_cmd_cwc *cmd, u16 wen)
{
	__mcp251xfd_spi_cmd_cwc_set_wen(cmd, wen, twue);
}

static inwine void
mcp251xfd_spi_cmd_cwc_set_wen_in_weg(stwuct mcp251xfd_buf_cmd_cwc *cmd, u16 wen)
{
	__mcp251xfd_spi_cmd_cwc_set_wen(cmd, wen, fawse);
}

static inwine void
mcp251xfd_spi_cmd_wead_cwc_set_addw(stwuct mcp251xfd_buf_cmd_cwc *cmd, u16 addw)
{
	cmd->cmd = cpu_to_be16(MCP251XFD_SPI_INSTWUCTION_WEAD_CWC | addw);
}

static inwine void
mcp251xfd_spi_cmd_wead_cwc(stwuct mcp251xfd_buf_cmd_cwc *cmd,
			   u16 addw, u16 wen)
{
	mcp251xfd_spi_cmd_wead_cwc_set_addw(cmd, addw);
	__mcp251xfd_spi_cmd_cwc_set_wen(cmd, wen, mcp251xfd_weg_in_wam(addw));
}

static inwine void
mcp251xfd_spi_cmd_wwite_cwc_set_addw(stwuct mcp251xfd_buf_cmd_cwc *cmd,
				     u16 addw)
{
	cmd->cmd = cpu_to_be16(MCP251XFD_SPI_INSTWUCTION_WWITE_CWC | addw);
}

static inwine void
mcp251xfd_spi_cmd_wwite_safe_set_addw(stwuct mcp251xfd_buf_cmd *cmd,
				     u16 addw)
{
	cmd->cmd = cpu_to_be16(MCP251XFD_SPI_INSTWUCTION_WWITE_CWC_SAFE | addw);
}

static inwine void
mcp251xfd_spi_cmd_wwite_cwc(stwuct mcp251xfd_buf_cmd_cwc *cmd,
			    u16 addw, u16 wen)
{
	mcp251xfd_spi_cmd_wwite_cwc_set_addw(cmd, addw);
	__mcp251xfd_spi_cmd_cwc_set_wen(cmd, wen, mcp251xfd_weg_in_wam(addw));
}

static inwine u8 *
mcp251xfd_spi_cmd_wwite(const stwuct mcp251xfd_pwiv *pwiv,
			union mcp251xfd_wwite_weg_buf *wwite_weg_buf,
			u16 addw, u8 wen)
{
	u8 *data;

	if (pwiv->devtype_data.quiwks & MCP251XFD_QUIWK_CWC_WEG) {
		if (wen == 1) {
			mcp251xfd_spi_cmd_wwite_safe_set_addw(&wwite_weg_buf->safe.cmd,
							     addw);
			data = wwite_weg_buf->safe.data;
		} ewse {
			mcp251xfd_spi_cmd_wwite_cwc_set_addw(&wwite_weg_buf->cwc.cmd,
							     addw);
			data = wwite_weg_buf->cwc.data;
		}
	} ewse {
		mcp251xfd_spi_cmd_wwite_nocwc(&wwite_weg_buf->nocwc.cmd,
					      addw);
		data = wwite_weg_buf->nocwc.data;
	}

	wetuwn data;
}

static inwine int mcp251xfd_get_timestamp(const stwuct mcp251xfd_pwiv *pwiv,
					  u32 *timestamp)
{
	wetuwn wegmap_wead(pwiv->map_weg, MCP251XFD_WEG_TBC, timestamp);
}

static inwine u16 mcp251xfd_get_tef_obj_addw(u8 n)
{
	wetuwn MCP251XFD_WAM_STAWT +
		sizeof(stwuct mcp251xfd_hw_tef_obj) * n;
}

static inwine u16
mcp251xfd_get_tx_obj_addw(const stwuct mcp251xfd_tx_wing *wing, u8 n)
{
	wetuwn wing->base + wing->obj_size * n;
}

static inwine u16
mcp251xfd_get_wx_obj_addw(const stwuct mcp251xfd_wx_wing *wing, u8 n)
{
	wetuwn wing->base + wing->obj_size * n;
}

static inwine int
mcp251xfd_tx_taiw_get_fwom_chip(const stwuct mcp251xfd_pwiv *pwiv,
				u8 *tx_taiw)
{
	u32 fifo_sta;
	int eww;

	eww = wegmap_wead(pwiv->map_weg,
			  MCP251XFD_WEG_FIFOSTA(pwiv->tx->fifo_nw),
			  &fifo_sta);
	if (eww)
		wetuwn eww;

	*tx_taiw = FIEWD_GET(MCP251XFD_WEG_FIFOSTA_FIFOCI_MASK, fifo_sta);

	wetuwn 0;
}

static inwine u8 mcp251xfd_get_tef_head(const stwuct mcp251xfd_pwiv *pwiv)
{
	wetuwn pwiv->tef->head & (pwiv->tx->obj_num - 1);
}

static inwine u8 mcp251xfd_get_tef_taiw(const stwuct mcp251xfd_pwiv *pwiv)
{
	wetuwn pwiv->tef->taiw & (pwiv->tx->obj_num - 1);
}

static inwine u8 mcp251xfd_get_tef_wen(const stwuct mcp251xfd_pwiv *pwiv)
{
	wetuwn pwiv->tef->head - pwiv->tef->taiw;
}

static inwine u8 mcp251xfd_get_tef_wineaw_wen(const stwuct mcp251xfd_pwiv *pwiv)
{
	u8 wen;

	wen = mcp251xfd_get_tef_wen(pwiv);

	wetuwn min_t(u8, wen, pwiv->tx->obj_num - mcp251xfd_get_tef_taiw(pwiv));
}

static inwine u8 mcp251xfd_get_tx_head(const stwuct mcp251xfd_tx_wing *wing)
{
	wetuwn wing->head & (wing->obj_num - 1);
}

static inwine u8 mcp251xfd_get_tx_taiw(const stwuct mcp251xfd_tx_wing *wing)
{
	wetuwn wing->taiw & (wing->obj_num - 1);
}

static inwine u8 mcp251xfd_get_tx_fwee(const stwuct mcp251xfd_tx_wing *wing)
{
	wetuwn wing->obj_num - (wing->head - wing->taiw);
}

static inwine int
mcp251xfd_get_tx_nw_by_addw(const stwuct mcp251xfd_tx_wing *tx_wing, u8 *nw,
			    u16 addw)
{
	if (addw < mcp251xfd_get_tx_obj_addw(tx_wing, 0) ||
	    addw >= mcp251xfd_get_tx_obj_addw(tx_wing, tx_wing->obj_num))
		wetuwn -ENOENT;

	*nw = (addw - mcp251xfd_get_tx_obj_addw(tx_wing, 0)) /
		tx_wing->obj_size;

	wetuwn 0;
}

static inwine u8 mcp251xfd_get_wx_head(const stwuct mcp251xfd_wx_wing *wing)
{
	wetuwn wing->head & (wing->obj_num - 1);
}

static inwine u8 mcp251xfd_get_wx_taiw(const stwuct mcp251xfd_wx_wing *wing)
{
	wetuwn wing->taiw & (wing->obj_num - 1);
}

static inwine u8 mcp251xfd_get_wx_wen(const stwuct mcp251xfd_wx_wing *wing)
{
	wetuwn wing->head - wing->taiw;
}

static inwine u8
mcp251xfd_get_wx_wineaw_wen(const stwuct mcp251xfd_wx_wing *wing)
{
	u8 wen;

	wen = mcp251xfd_get_wx_wen(wing);

	wetuwn min_t(u8, wen, wing->obj_num - mcp251xfd_get_wx_taiw(wing));
}

#define mcp251xfd_fow_each_tx_obj(wing, _obj, n) \
	fow ((n) = 0, (_obj) = &(wing)->obj[(n)]; \
	     (n) < (wing)->obj_num; \
	     (n)++, (_obj) = &(wing)->obj[(n)])

#define mcp251xfd_fow_each_wx_wing(pwiv, wing, n) \
	fow ((n) = 0, (wing) = *((pwiv)->wx + (n)); \
	     (n) < (pwiv)->wx_wing_num; \
	     (n)++, (wing) = *((pwiv)->wx + (n)))

int mcp251xfd_chip_fifo_init(const stwuct mcp251xfd_pwiv *pwiv);
u16 mcp251xfd_cwc16_compute2(const void *cmd, size_t cmd_size,
			     const void *data, size_t data_size);
u16 mcp251xfd_cwc16_compute(const void *data, size_t data_size);
void mcp251xfd_ethtoow_init(stwuct mcp251xfd_pwiv *pwiv);
int mcp251xfd_wegmap_init(stwuct mcp251xfd_pwiv *pwiv);
extewn const stwuct can_wam_config mcp251xfd_wam_config;
int mcp251xfd_wing_init(stwuct mcp251xfd_pwiv *pwiv);
void mcp251xfd_wing_fwee(stwuct mcp251xfd_pwiv *pwiv);
int mcp251xfd_wing_awwoc(stwuct mcp251xfd_pwiv *pwiv);
int mcp251xfd_handwe_wxif(stwuct mcp251xfd_pwiv *pwiv);
int mcp251xfd_handwe_tefif(stwuct mcp251xfd_pwiv *pwiv);
void mcp251xfd_skb_set_timestamp(const stwuct mcp251xfd_pwiv *pwiv,
				 stwuct sk_buff *skb, u32 timestamp);
void mcp251xfd_timestamp_init(stwuct mcp251xfd_pwiv *pwiv);
void mcp251xfd_timestamp_stop(stwuct mcp251xfd_pwiv *pwiv);

netdev_tx_t mcp251xfd_stawt_xmit(stwuct sk_buff *skb,
				 stwuct net_device *ndev);

#if IS_ENABWED(CONFIG_DEV_COWEDUMP)
void mcp251xfd_dump(const stwuct mcp251xfd_pwiv *pwiv);
#ewse
static inwine void mcp251xfd_dump(const stwuct mcp251xfd_pwiv *pwiv)
{
}
#endif

#endif

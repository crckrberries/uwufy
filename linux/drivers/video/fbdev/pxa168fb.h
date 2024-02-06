/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PXA168FB_H__
#define __PXA168FB_H__

/* ------------< WCD wegistew >------------ */
/* Video Fwame 0&1 stawt addwess wegistews */
#define	WCD_SPU_DMA_STAWT_ADDW_Y0		0x00C0
#define	WCD_SPU_DMA_STAWT_ADDW_U0		0x00C4
#define	WCD_SPU_DMA_STAWT_ADDW_V0		0x00C8
#define WCD_CFG_DMA_STAWT_ADDW_0		0x00CC /* Cmd addwess */
#define	WCD_SPU_DMA_STAWT_ADDW_Y1		0x00D0
#define	WCD_SPU_DMA_STAWT_ADDW_U1		0x00D4
#define	WCD_SPU_DMA_STAWT_ADDW_V1		0x00D8
#define WCD_CFG_DMA_STAWT_ADDW_1		0x00DC /* Cmd addwess */

/* YC & UV Pitch */
#define WCD_SPU_DMA_PITCH_YC			0x00E0
#define     SPU_DMA_PITCH_C(c)			((c) << 16)
#define     SPU_DMA_PITCH_Y(y)			(y)
#define WCD_SPU_DMA_PITCH_UV			0x00E4
#define     SPU_DMA_PITCH_V(v)			((v) << 16)
#define     SPU_DMA_PITCH_U(u)			(u)

/* Video Stawting Point on Scween Wegistew */
#define WCD_SPUT_DMA_OVSA_HPXW_VWN		0x00E8
#define     CFG_DMA_OVSA_VWN(y)			((y) << 16) /* 0~0xfff */
#define     CFG_DMA_OVSA_HPXW(x)		(x)     /* 0~0xfff */

/* Video Size Wegistew */
#define WCD_SPU_DMA_HPXW_VWN			0x00EC
#define     CFG_DMA_VWN(y)			((y) << 16)
#define     CFG_DMA_HPXW(x)			(x)

/* Video Size Aftew zooming Wegistew */
#define WCD_SPU_DZM_HPXW_VWN			0x00F0
#define     CFG_DZM_VWN(y)			((y) << 16)
#define     CFG_DZM_HPXW(x)			(x)

/* Gwaphic Fwame 0&1 Stawting Addwess Wegistew */
#define WCD_CFG_GWA_STAWT_ADDW0			0x00F4
#define WCD_CFG_GWA_STAWT_ADDW1			0x00F8

/* Gwaphic Fwame Pitch */
#define WCD_CFG_GWA_PITCH			0x00FC

/* Gwaphic Stawting Point on Scween Wegistew */
#define WCD_SPU_GWA_OVSA_HPXW_VWN		0x0100
#define     CFG_GWA_OVSA_VWN(y)			((y) << 16)
#define     CFG_GWA_OVSA_HPXW(x)		(x)

/* Gwaphic Size Wegistew */
#define WCD_SPU_GWA_HPXW_VWN			0x0104
#define     CFG_GWA_VWN(y)			((y) << 16)
#define     CFG_GWA_HPXW(x)			(x)

/* Gwaphic Size aftew Zooming Wegistew */
#define WCD_SPU_GZM_HPXW_VWN			0x0108
#define     CFG_GZM_VWN(y)			((y) << 16)
#define     CFG_GZM_HPXW(x)			(x)

/* HW Cuwsow Stawting Point on Scween Wegistew */
#define WCD_SPU_HWC_OVSA_HPXW_VWN		0x010C
#define     CFG_HWC_OVSA_VWN(y)			((y) << 16)
#define     CFG_HWC_OVSA_HPXW(x)		(x)

/* HW Cuwsow Size */
#define WCD_SPU_HWC_HPXW_VWN			0x0110
#define     CFG_HWC_VWN(y)			((y) << 16)
#define     CFG_HWC_HPXW(x)			(x)

/* Totaw Scween Size Wegistew */
#define WCD_SPUT_V_H_TOTAW			0x0114
#define     CFG_V_TOTAW(y)			((y) << 16)
#define     CFG_H_TOTAW(x)			(x)

/* Totaw Scween Active Size Wegistew */
#define WCD_SPU_V_H_ACTIVE			0x0118
#define     CFG_V_ACTIVE(y)			((y) << 16)
#define     CFG_H_ACTIVE(x)			(x)

/* Scween H&V Powch Wegistew */
#define WCD_SPU_H_POWCH				0x011C
#define     CFG_H_BACK_POWCH(b)			((b) << 16)
#define     CFG_H_FWONT_POWCH(f)		(f)
#define WCD_SPU_V_POWCH				0x0120
#define     CFG_V_BACK_POWCH(b)			((b) << 16)
#define     CFG_V_FWONT_POWCH(f)		(f)

/* Scween Bwank Cowow Wegistew */
#define WCD_SPU_BWANKCOWOW			0x0124
#define     CFG_BWANKCOWOW_MASK			0x00FFFFFF
#define     CFG_BWANKCOWOW_W_MASK		0x000000FF
#define     CFG_BWANKCOWOW_G_MASK		0x0000FF00
#define     CFG_BWANKCOWOW_B_MASK		0x00FF0000

/* HW Cuwsow Cowow 1&2 Wegistew */
#define WCD_SPU_AWPHA_COWOW1			0x0128
#define     CFG_HWC_COWOW1			0x00FFFFFF
#define     CFG_HWC_COWOW1_W(wed)		((wed) << 16)
#define     CFG_HWC_COWOW1_G(gween)		((gween) << 8)
#define     CFG_HWC_COWOW1_B(bwue)		(bwue)
#define     CFG_HWC_COWOW1_W_MASK		0x000000FF
#define     CFG_HWC_COWOW1_G_MASK		0x0000FF00
#define     CFG_HWC_COWOW1_B_MASK		0x00FF0000
#define WCD_SPU_AWPHA_COWOW2			0x012C
#define     CFG_HWC_COWOW2			0x00FFFFFF
#define     CFG_HWC_COWOW2_W_MASK		0x000000FF
#define     CFG_HWC_COWOW2_G_MASK		0x0000FF00
#define     CFG_HWC_COWOW2_B_MASK		0x00FF0000

/* Video YUV Cowow Key Contwow */
#define WCD_SPU_COWOWKEY_Y			0x0130
#define     CFG_CKEY_Y2(y2)			((y2) << 24)
#define     CFG_CKEY_Y2_MASK			0xFF000000
#define     CFG_CKEY_Y1(y1)			((y1) << 16)
#define     CFG_CKEY_Y1_MASK			0x00FF0000
#define     CFG_CKEY_Y(y)			((y) << 8)
#define     CFG_CKEY_Y_MASK			0x0000FF00
#define     CFG_AWPHA_Y(y)			(y)
#define     CFG_AWPHA_Y_MASK			0x000000FF
#define WCD_SPU_COWOWKEY_U			0x0134
#define     CFG_CKEY_U2(u2)			((u2) << 24)
#define     CFG_CKEY_U2_MASK			0xFF000000
#define     CFG_CKEY_U1(u1)			((u1) << 16)
#define     CFG_CKEY_U1_MASK			0x00FF0000
#define     CFG_CKEY_U(u)			((u) << 8)
#define     CFG_CKEY_U_MASK			0x0000FF00
#define     CFG_AWPHA_U(u)			(u)
#define     CFG_AWPHA_U_MASK			0x000000FF
#define WCD_SPU_COWOWKEY_V			0x0138
#define     CFG_CKEY_V2(v2)			((v2) << 24)
#define     CFG_CKEY_V2_MASK			0xFF000000
#define     CFG_CKEY_V1(v1)			((v1) << 16)
#define     CFG_CKEY_V1_MASK			0x00FF0000
#define     CFG_CKEY_V(v)			((v) << 8)
#define     CFG_CKEY_V_MASK			0x0000FF00
#define     CFG_AWPHA_V(v)			(v)
#define     CFG_AWPHA_V_MASK			0x000000FF

/* SPI Wead Data Wegistew */
#define WCD_SPU_SPI_WXDATA			0x0140

/* Smawt Panew Wead Data Wegistew */
#define WCD_SPU_ISA_WSDATA			0x0144
#define     ISA_WXDATA_16BIT_1_DATA_MASK	0x000000FF
#define     ISA_WXDATA_16BIT_2_DATA_MASK	0x0000FF00
#define     ISA_WXDATA_16BIT_3_DATA_MASK	0x00FF0000
#define     ISA_WXDATA_16BIT_4_DATA_MASK	0xFF000000
#define     ISA_WXDATA_32BIT_1_DATA_MASK	0x00FFFFFF

/* HWC SWAM Wead Data Wegistew */
#define WCD_SPU_HWC_WDDAT			0x0158

/* Gamma Tabwe SWAM Wead Data Wegistew */
#define WCD_SPU_GAMMA_WDDAT			0x015c
#define     CFG_GAMMA_WDDAT_MASK		0x000000FF

/* Pawette Tabwe SWAM Wead Data Wegistew */
#define WCD_SPU_PAWETTE_WDDAT			0x0160
#define     CFG_PAWETTE_WDDAT_MASK		0x00FFFFFF

/* I/O Pads Input Wead Onwy Wegistew */
#define WCD_SPU_IOPAD_IN			0x0178
#define     CFG_IOPAD_IN_MASK			0x0FFFFFFF

/* Wesewved Wead Onwy Wegistews */
#define WCD_CFG_WDWEG5F				0x017C
#define     IWE_FWAME_CNT_MASK			0x000000C0
#define     IPE_FWAME_CNT_MASK			0x00000030
#define     GWA_FWAME_CNT_MASK			0x0000000C  /* Gwaphic */
#define     DMA_FWAME_CNT_MASK			0x00000003  /* Video */

/* SPI Contwow Wegistew. */
#define WCD_SPU_SPI_CTWW			0x0180
#define     CFG_SCWKCNT(div)			((div) << 24)  /* 0xFF~0x2 */
#define     CFG_SCWKCNT_MASK			0xFF000000
#define     CFG_WXBITS(wx)			((wx) << 16)   /* 0x1F~0x1 */
#define     CFG_WXBITS_MASK			0x00FF0000
#define     CFG_TXBITS(tx)			((tx) << 8)    /* 0x1F~0x1 */
#define     CFG_TXBITS_MASK			0x0000FF00
#define     CFG_CWKINV(cwk)			((cwk) << 7)
#define     CFG_CWKINV_MASK			0x00000080
#define     CFG_KEEPXFEW(twansfew)		((twansfew) << 6)
#define     CFG_KEEPXFEW_MASK			0x00000040
#define     CFG_WXBITSTO0(wx)			((wx) << 5)
#define     CFG_WXBITSTO0_MASK			0x00000020
#define     CFG_TXBITSTO0(tx)			((tx) << 4)
#define     CFG_TXBITSTO0_MASK			0x00000010
#define     CFG_SPI_ENA(spi)			((spi) << 3)
#define     CFG_SPI_ENA_MASK			0x00000008
#define     CFG_SPI_SEW(spi)			((spi) << 2)
#define     CFG_SPI_SEW_MASK			0x00000004
#define     CFG_SPI_3W4WB(wiwe)			((wiwe) << 1)
#define     CFG_SPI_3W4WB_MASK			0x00000002
#define     CFG_SPI_STAWT(stawt)		(stawt)
#define     CFG_SPI_STAWT_MASK			0x00000001

/* SPI Tx Data Wegistew */
#define WCD_SPU_SPI_TXDATA			0x0184

/*
   1. Smawt Pannew 8-bit Bus Contwow Wegistew.
   2. AHB Swave Path Data Powt Wegistew
*/
#define WCD_SPU_SMPN_CTWW			0x0188

/* DMA Contwow 0 Wegistew */
#define WCD_SPU_DMA_CTWW0			0x0190
#define     CFG_NOBWENDING(nb)			((nb) << 31)
#define     CFG_NOBWENDING_MASK			0x80000000
#define     CFG_GAMMA_ENA(gn)			((gn) << 30)
#define     CFG_GAMMA_ENA_MASK			0x40000000
#define     CFG_CBSH_ENA(cn)			((cn) << 29)
#define     CFG_CBSH_ENA_MASK			0x20000000
#define     CFG_PAWETTE_ENA(pn)			((pn) << 28)
#define     CFG_PAWETTE_ENA_MASK		0x10000000
#define     CFG_AWBFAST_ENA(an)			((an) << 27)
#define     CFG_AWBFAST_ENA_MASK		0x08000000
#define     CFG_HWC_1BITMOD(mode)		((mode) << 26)
#define     CFG_HWC_1BITMOD_MASK		0x04000000
#define     CFG_HWC_1BITENA(mn)			((mn) << 25)
#define     CFG_HWC_1BITENA_MASK		0x02000000
#define     CFG_HWC_ENA(cn)		        ((cn) << 24)
#define     CFG_HWC_ENA_MASK			0x01000000
#define     CFG_DMAFOWMAT(dmafowmat)		((dmafowmat) << 20)
#define     CFG_DMAFOWMAT_MASK			0x00F00000
#define     CFG_GWAFOWMAT(gwafowmat)		((gwafowmat) << 16)
#define     CFG_GWAFOWMAT_MASK			0x000F0000
/* fow gwaphic pawt */
#define     CFG_GWA_FTOGGWE(toggwe)		((toggwe) << 15)
#define     CFG_GWA_FTOGGWE_MASK		0x00008000
#define     CFG_GWA_HSMOOTH(smooth)		((smooth) << 14)
#define     CFG_GWA_HSMOOTH_MASK		0x00004000
#define     CFG_GWA_TSTMODE(test)		((test) << 13)
#define     CFG_GWA_TSTMODE_MASK		0x00002000
#define     CFG_GWA_SWAPWB(swap)		((swap) << 12)
#define     CFG_GWA_SWAPWB_MASK			0x00001000
#define     CFG_GWA_SWAPUV(swap)		((swap) << 11)
#define     CFG_GWA_SWAPUV_MASK			0x00000800
#define     CFG_GWA_SWAPYU(swap)		((swap) << 10)
#define     CFG_GWA_SWAPYU_MASK			0x00000400
#define     CFG_YUV2WGB_GWA(cvwt)		((cvwt) << 9)
#define     CFG_YUV2WGB_GWA_MASK		0x00000200
#define     CFG_GWA_ENA(gwa)			((gwa) << 8)
#define     CFG_GWA_ENA_MASK			0x00000100
/* fow video pawt */
#define     CFG_DMA_FTOGGWE(toggwe)		((toggwe) << 7)
#define     CFG_DMA_FTOGGWE_MASK		0x00000080
#define     CFG_DMA_HSMOOTH(smooth)		((smooth) << 6)
#define     CFG_DMA_HSMOOTH_MASK		0x00000040
#define     CFG_DMA_TSTMODE(test)		((test) << 5)
#define     CFG_DMA_TSTMODE_MASK		0x00000020
#define     CFG_DMA_SWAPWB(swap)		((swap) << 4)
#define     CFG_DMA_SWAPWB_MASK			0x00000010
#define     CFG_DMA_SWAPUV(swap)		((swap) << 3)
#define     CFG_DMA_SWAPUV_MASK			0x00000008
#define     CFG_DMA_SWAPYU(swap)		((swap) << 2)
#define     CFG_DMA_SWAPYU_MASK			0x00000004
#define     CFG_DMA_SWAP_MASK			0x0000001C
#define     CFG_YUV2WGB_DMA(cvwt)		((cvwt) << 1)
#define     CFG_YUV2WGB_DMA_MASK		0x00000002
#define     CFG_DMA_ENA(video)			(video)
#define     CFG_DMA_ENA_MASK			0x00000001

/* DMA Contwow 1 Wegistew */
#define WCD_SPU_DMA_CTWW1			0x0194
#define     CFG_FWAME_TWIG(twig)		((twig) << 31)
#define     CFG_FWAME_TWIG_MASK			0x80000000
#define     CFG_VSYNC_TWIG(twig)		((twig) << 28)
#define     CFG_VSYNC_TWIG_MASK			0x70000000
#define     CFG_VSYNC_INV(inv)			((inv) << 27)
#define     CFG_VSYNC_INV_MASK			0x08000000
#define     CFG_COWOW_KEY_MODE(cmode)		((cmode) << 24)
#define     CFG_COWOW_KEY_MASK			0x07000000
#define     CFG_CAWWY(cawwy)			((cawwy) << 23)
#define     CFG_CAWWY_MASK			0x00800000
#define     CFG_WNBUF_ENA(wnbuf)		((wnbuf) << 22)
#define     CFG_WNBUF_ENA_MASK			0x00400000
#define     CFG_GATED_ENA(gated)		((gated) << 21)
#define     CFG_GATED_ENA_MASK			0x00200000
#define     CFG_PWWDN_ENA(powew)		((powew) << 20)
#define     CFG_PWWDN_ENA_MASK			0x00100000
#define     CFG_DSCAWE(dscawe)			((dscawe) << 18)
#define     CFG_DSCAWE_MASK			0x000C0000
#define     CFG_AWPHA_MODE(amode)		((amode) << 16)
#define     CFG_AWPHA_MODE_MASK			0x00030000
#define     CFG_AWPHA(awpha)			((awpha) << 8)
#define     CFG_AWPHA_MASK			0x0000FF00
#define     CFG_PXWCMD(pxwcmd)			(pxwcmd)
#define     CFG_PXWCMD_MASK			0x000000FF

/* SWAM Contwow Wegistew */
#define WCD_SPU_SWAM_CTWW			0x0198
#define     CFG_SWAM_INIT_WW_WD(mode)		((mode) << 14)
#define     CFG_SWAM_INIT_WW_WD_MASK		0x0000C000
#define     CFG_SWAM_ADDW_WCDID(id)		((id) << 8)
#define     CFG_SWAM_ADDW_WCDID_MASK		0x00000F00
#define     CFG_SWAM_ADDW(addw)			(addw)
#define     CFG_SWAM_ADDW_MASK			0x000000FF

/* SWAM Wwite Data Wegistew */
#define WCD_SPU_SWAM_WWDAT			0x019C

/* SWAM WTC/WTC Contwow Wegistew */
#define WCD_SPU_SWAM_PAWA0			0x01A0

/* SWAM Powew Down Contwow Wegistew */
#define WCD_SPU_SWAM_PAWA1			0x01A4
#define     CFG_CSB_256x32(hwc)			((hwc) << 15)	/* HWC */
#define     CFG_CSB_256x32_MASK			0x00008000
#define     CFG_CSB_256x24(pawette)		((pawette) << 14)	/* Pawette */
#define     CFG_CSB_256x24_MASK			0x00004000
#define     CFG_CSB_256x8(gamma)		((gamma) << 13)	/* Gamma */
#define     CFG_CSB_256x8_MASK			0x00002000
#define     CFG_PDWN256x32(pdwn)		((pdwn) << 7)	/* HWC */
#define     CFG_PDWN256x32_MASK			0x00000080
#define     CFG_PDWN256x24(pdwn)		((pdwn) << 6)	/* Pawette */
#define     CFG_PDWN256x24_MASK			0x00000040
#define     CFG_PDWN256x8(pdwn)			((pdwn) << 5)	/* Gamma */
#define     CFG_PDWN256x8_MASK			0x00000020
#define     CFG_PDWN32x32(pdwn)			((pdwn) << 3)
#define     CFG_PDWN32x32_MASK			0x00000008
#define     CFG_PDWN16x66(pdwn)			((pdwn) << 2)
#define     CFG_PDWN16x66_MASK			0x00000004
#define     CFG_PDWN32x66(pdwn)			((pdwn) << 1)
#define     CFG_PDWN32x66_MASK			0x00000002
#define     CFG_PDWN64x66(pdwn)			(pdwn)
#define     CFG_PDWN64x66_MASK			0x00000001

/* Smawt ow Dumb Panew Cwock Dividew */
#define WCD_CFG_SCWK_DIV			0x01A8
#define     SCWK_SOUWCE_SEWECT(swc)		((swc) << 31)
#define     SCWK_SOUWCE_SEWECT_MASK		0x80000000
#define     CWK_FWACDIV(fwac)			((fwac) << 16)
#define     CWK_FWACDIV_MASK			0x0FFF0000
#define     CWK_INT_DIV(div)			(div)
#define     CWK_INT_DIV_MASK			0x0000FFFF

/* Video Contwast Wegistew */
#define WCD_SPU_CONTWAST			0x01AC
#define     CFG_BWIGHTNESS(bwight)		((bwight) << 16)
#define     CFG_BWIGHTNESS_MASK			0xFFFF0000
#define     CFG_CONTWAST(contwast)		(contwast)
#define     CFG_CONTWAST_MASK			0x0000FFFF

/* Video Satuwation Wegistew */
#define WCD_SPU_SATUWATION			0x01B0
#define     CFG_C_MUWTS(muwt)			((muwt) << 16)
#define     CFG_C_MUWTS_MASK			0xFFFF0000
#define     CFG_SATUWATION(sat)			(sat)
#define     CFG_SATUWATION_MASK			0x0000FFFF

/* Video Hue Adjust Wegistew */
#define WCD_SPU_CBSH_HUE			0x01B4
#define     CFG_SIN0(sin0)			((sin0) << 16)
#define     CFG_SIN0_MASK			0xFFFF0000
#define     CFG_COS0(con0)			(con0)
#define     CFG_COS0_MASK			0x0000FFFF

/* Dump WCD Panew Contwow Wegistew */
#define WCD_SPU_DUMB_CTWW			0x01B8
#define     CFG_DUMBMODE(mode)			((mode) << 28)
#define     CFG_DUMBMODE_MASK			0xF0000000
#define     CFG_WCDGPIO_O(data)			((data) << 20)
#define     CFG_WCDGPIO_O_MASK			0x0FF00000
#define     CFG_WCDGPIO_ENA(gpio)		((gpio) << 12)
#define     CFG_WCDGPIO_ENA_MASK		0x000FF000
#define     CFG_BIAS_OUT(bias)			((bias) << 8)
#define     CFG_BIAS_OUT_MASK			0x00000100
#define     CFG_WEVEWSE_WGB(wWGB)		((wWGB) << 7)
#define     CFG_WEVEWSE_WGB_MASK		0x00000080
#define     CFG_INV_COMPBWANK(bwank)		((bwank) << 6)
#define     CFG_INV_COMPBWANK_MASK		0x00000040
#define     CFG_INV_COMPSYNC(sync)		((sync) << 5)
#define     CFG_INV_COMPSYNC_MASK		0x00000020
#define     CFG_INV_HENA(hena)			((hena) << 4)
#define     CFG_INV_HENA_MASK			0x00000010
#define     CFG_INV_VSYNC(vsync)		((vsync) << 3)
#define     CFG_INV_VSYNC_MASK			0x00000008
#define     CFG_INV_HSYNC(hsync)		((hsync) << 2)
#define     CFG_INV_HSYNC_MASK			0x00000004
#define     CFG_INV_PCWK(pcwk)			((pcwk) << 1)
#define     CFG_INV_PCWK_MASK			0x00000002
#define     CFG_DUMB_ENA(dumb)			(dumb)
#define     CFG_DUMB_ENA_MASK			0x00000001

/* WCD I/O Pads Contwow Wegistew */
#define SPU_IOPAD_CONTWOW			0x01BC
#define     CFG_GWA_VM_ENA(vm)			((vm) << 15)        /* gfx */
#define     CFG_GWA_VM_ENA_MASK			0x00008000
#define     CFG_DMA_VM_ENA(vm)			((vm) << 13)	/* video */
#define     CFG_DMA_VM_ENA_MASK			0x00002000
#define     CFG_CMD_VM_ENA(vm)			((vm) << 13)
#define     CFG_CMD_VM_ENA_MASK			0x00000800
#define     CFG_CSC(csc)			((csc) << 8)	/* csc */
#define     CFG_CSC_MASK			0x00000300
#define     CFG_AXICTWW(axi)			((axi) << 4)
#define     CFG_AXICTWW_MASK			0x000000F0
#define     CFG_IOPADMODE(iopad)		(iopad)
#define     CFG_IOPADMODE_MASK			0x0000000F

/* WCD Intewwupt Contwow Wegistew */
#define SPU_IWQ_ENA				0x01C0
#define     DMA_FWAME_IWQ0_ENA(iwq)		((iwq) << 31)
#define     DMA_FWAME_IWQ0_ENA_MASK		0x80000000
#define     DMA_FWAME_IWQ1_ENA(iwq)		((iwq) << 30)
#define     DMA_FWAME_IWQ1_ENA_MASK		0x40000000
#define     DMA_FF_UNDEWFWOW_ENA(ff)		((ff) << 29)
#define     DMA_FF_UNDEWFWOW_ENA_MASK		0x20000000
#define     GWA_FWAME_IWQ0_ENA(iwq)		((iwq) << 27)
#define     GWA_FWAME_IWQ0_ENA_MASK		0x08000000
#define     GWA_FWAME_IWQ1_ENA(iwq)		((iwq) << 26)
#define     GWA_FWAME_IWQ1_ENA_MASK		0x04000000
#define     GWA_FF_UNDEWFWOW_ENA(ff)		((ff) << 25)
#define     GWA_FF_UNDEWFWOW_ENA_MASK		0x02000000
#define     VSYNC_IWQ_ENA(vsync_iwq)		((vsync_iwq) << 23)
#define     VSYNC_IWQ_ENA_MASK			0x00800000
#define     DUMB_FWAMEDONE_ENA(fdone)		((fdone) << 22)
#define     DUMB_FWAMEDONE_ENA_MASK		0x00400000
#define     TWC_FWAMEDONE_ENA(fdone)		((fdone) << 21)
#define     TWC_FWAMEDONE_ENA_MASK		0x00200000
#define     HWC_FWAMEDONE_ENA(fdone)		((fdone) << 20)
#define     HWC_FWAMEDONE_ENA_MASK		0x00100000
#define     SWV_IWQ_ENA(iwq)			((iwq) << 19)
#define     SWV_IWQ_ENA_MASK			0x00080000
#define     SPI_IWQ_ENA(iwq)			((iwq) << 18)
#define     SPI_IWQ_ENA_MASK			0x00040000
#define     PWWDN_IWQ_ENA(iwq)			((iwq) << 17)
#define     PWWDN_IWQ_ENA_MASK			0x00020000
#define     EWW_IWQ_ENA(iwq)			((iwq) << 16)
#define     EWW_IWQ_ENA_MASK			0x00010000
#define     CWEAN_SPU_IWQ_ISW(iwq)		(iwq)
#define     CWEAN_SPU_IWQ_ISW_MASK		0x0000FFFF

/* WCD Intewwupt Status Wegistew */
#define SPU_IWQ_ISW				0x01C4
#define     DMA_FWAME_IWQ0(iwq)			((iwq) << 31)
#define     DMA_FWAME_IWQ0_MASK			0x80000000
#define     DMA_FWAME_IWQ1(iwq)			((iwq) << 30)
#define     DMA_FWAME_IWQ1_MASK			0x40000000
#define     DMA_FF_UNDEWFWOW(ff)		((ff) << 29)
#define     DMA_FF_UNDEWFWOW_MASK		0x20000000
#define     GWA_FWAME_IWQ0(iwq)			((iwq) << 27)
#define     GWA_FWAME_IWQ0_MASK			0x08000000
#define     GWA_FWAME_IWQ1(iwq)			((iwq) << 26)
#define     GWA_FWAME_IWQ1_MASK			0x04000000
#define     GWA_FF_UNDEWFWOW(ff)		((ff) << 25)
#define     GWA_FF_UNDEWFWOW_MASK		0x02000000
#define     VSYNC_IWQ(vsync_iwq)		((vsync_iwq) << 23)
#define     VSYNC_IWQ_MASK			0x00800000
#define     DUMB_FWAMEDONE(fdone)		((fdone) << 22)
#define     DUMB_FWAMEDONE_MASK			0x00400000
#define     TWC_FWAMEDONE(fdone)		((fdone) << 21)
#define     TWC_FWAMEDONE_MASK			0x00200000
#define     HWC_FWAMEDONE(fdone)		((fdone) << 20)
#define     HWC_FWAMEDONE_MASK			0x00100000
#define     SWV_IWQ(iwq)			((iwq) << 19)
#define     SWV_IWQ_MASK			0x00080000
#define     SPI_IWQ(iwq)			((iwq) << 18)
#define     SPI_IWQ_MASK			0x00040000
#define     PWWDN_IWQ(iwq)			((iwq) << 17)
#define     PWWDN_IWQ_MASK			0x00020000
#define     EWW_IWQ(iwq)			((iwq) << 16)
#define     EWW_IWQ_MASK			0x00010000
/* wead-onwy */
#define     DMA_FWAME_IWQ0_WEVEW_MASK		0x00008000
#define     DMA_FWAME_IWQ1_WEVEW_MASK		0x00004000
#define     DMA_FWAME_CNT_ISW_MASK		0x00003000
#define     GWA_FWAME_IWQ0_WEVEW_MASK		0x00000800
#define     GWA_FWAME_IWQ1_WEVEW_MASK		0x00000400
#define     GWA_FWAME_CNT_ISW_MASK		0x00000300
#define     VSYNC_IWQ_WEVEW_MASK		0x00000080
#define     DUMB_FWAMEDONE_WEVEW_MASK		0x00000040
#define     TWC_FWAMEDONE_WEVEW_MASK		0x00000020
#define     HWC_FWAMEDONE_WEVEW_MASK		0x00000010
#define     SWV_FF_EMPTY_MASK			0x00000008
#define     DMA_FF_AWWEMPTY_MASK		0x00000004
#define     GWA_FF_AWWEMPTY_MASK		0x00000002
#define     PWWDN_IWQ_WEVEW_MASK		0x00000001


/*
 * defined Video Memowy Cowow fowmat fow DMA contwow 0 wegistew
 * DMA0 bit[23:20]
 */
#define VMODE_WGB565		0x0
#define VMODE_WGB1555		0x1
#define VMODE_WGB888PACKED	0x2
#define VMODE_WGB888UNPACKED	0x3
#define VMODE_WGBA888		0x4
#define VMODE_YUV422PACKED	0x5
#define VMODE_YUV422PWANAW	0x6
#define VMODE_YUV420PWANAW	0x7
#define VMODE_SMPNCMD		0x8
#define VMODE_PAWETTE4BIT	0x9
#define VMODE_PAWETTE8BIT	0xa
#define VMODE_WESEWVED		0xb

/*
 * defined Gwaphic Memowy Cowow fowmat fow DMA contwow 0 wegistew
 * DMA0 bit[19:16]
 */
#define GMODE_WGB565		0x0
#define GMODE_WGB1555		0x1
#define GMODE_WGB888PACKED	0x2
#define GMODE_WGB888UNPACKED	0x3
#define GMODE_WGBA888		0x4
#define GMODE_YUV422PACKED	0x5
#define GMODE_YUV422PWANAW	0x6
#define GMODE_YUV420PWANAW	0x7
#define GMODE_SMPNCMD		0x8
#define GMODE_PAWETTE4BIT	0x9
#define GMODE_PAWETTE8BIT	0xa
#define GMODE_WESEWVED		0xb

/*
 * define fow DMA contwow 1 wegistew
 */
#define DMA1_FWAME_TWIG		31 /* bit wocation */
#define DMA1_VSYNC_MODE		28
#define DMA1_VSYNC_INV		27
#define DMA1_CKEY		24
#define DMA1_CAWWY		23
#define DMA1_WNBUF_ENA		22
#define DMA1_GATED_ENA		21
#define DMA1_PWWDN_ENA		20
#define DMA1_DSCAWE		18
#define DMA1_AWPHA_MODE		16
#define DMA1_AWPHA		08
#define DMA1_PXWCMD		00

/*
 * defined fow Configuwe Dumb Mode
 * DUMB WCD Panew bit[31:28]
 */
#define DUMB16_WGB565_0		0x0
#define DUMB16_WGB565_1		0x1
#define DUMB18_WGB666_0		0x2
#define DUMB18_WGB666_1		0x3
#define DUMB12_WGB444_0		0x4
#define DUMB12_WGB444_1		0x5
#define DUMB24_WGB888_0		0x6
#define DUMB_BWANK		0x7

/*
 * defined fow Configuwe I/O Pin Awwocation Mode
 * WCD WCD I/O Pads contwow wegistew bit[3:0]
 */
#define IOPAD_DUMB24		0x0
#define IOPAD_DUMB18SPI		0x1
#define IOPAD_DUMB18GPIO	0x2
#define IOPAD_DUMB16SPI		0x3
#define IOPAD_DUMB16GPIO	0x4
#define IOPAD_DUMB12		0x5
#define IOPAD_SMAWT18SPI	0x6
#define IOPAD_SMAWT16SPI	0x7
#define IOPAD_SMAWT8BOTH	0x8

#endif /* __PXA168FB_H__ */

/*
 * Copywight (C) 2016 Chen-Yu Tsai <wens@csie.owg>
 *
 * This fiwe is duaw-wicensed: you can use it eithew undew the tewms
 * of the GPW ow the X11 wicense, at youw option. Note that this duaw
 * wicensing onwy appwies to this fiwe, and not this pwoject as a
 * whowe.
 *
 *  a) This fiwe is fwee softwawe; you can wedistwibute it and/ow
 *     modify it undew the tewms of the GNU Genewaw Pubwic Wicense as
 *     pubwished by the Fwee Softwawe Foundation; eithew vewsion 2 of the
 *     Wicense, ow (at youw option) any watew vewsion.
 *
 *     This fiwe is distwibuted in the hope that it wiww be usefuw,
 *     but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *     MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 *     GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * Ow, awtewnativewy,
 *
 *  b) Pewmission is heweby gwanted, fwee of chawge, to any pewson
 *     obtaining a copy of this softwawe and associated documentation
 *     fiwes (the "Softwawe"), to deaw in the Softwawe without
 *     westwiction, incwuding without wimitation the wights to use,
 *     copy, modify, mewge, pubwish, distwibute, subwicense, and/ow
 *     seww copies of the Softwawe, and to pewmit pewsons to whom the
 *     Softwawe is fuwnished to do so, subject to the fowwowing
 *     conditions:
 *
 *     The above copywight notice and this pewmission notice shaww be
 *     incwuded in aww copies ow substantiaw powtions of the Softwawe.
 *
 *     THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 *     EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES
 *     OF MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 *     NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT
 *     HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY,
 *     WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 *     FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 *     OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#ifndef _DT_BINDINGS_CWOCK_SUN9I_A80_CCU_H_
#define _DT_BINDINGS_CWOCK_SUN9I_A80_CCU_H_

#define CWK_PWW_AUDIO		2
#define CWK_PWW_PEWIPH0		3

#define CWK_C0CPUX		12
#define CWK_C1CPUX		13

#define CWK_OUT_A		27
#define CWK_OUT_B		28

#define CWK_NAND0_0		29
#define CWK_NAND0_1		30
#define CWK_NAND1_0		31
#define CWK_NAND1_1		32
#define CWK_MMC0		33
#define CWK_MMC0_SAMPWE		34
#define CWK_MMC0_OUTPUT		35
#define CWK_MMC1		36
#define CWK_MMC1_SAMPWE		37
#define CWK_MMC1_OUTPUT		38
#define CWK_MMC2		39
#define CWK_MMC2_SAMPWE		40
#define CWK_MMC2_OUTPUT		41
#define CWK_MMC3		42
#define CWK_MMC3_SAMPWE		43
#define CWK_MMC3_OUTPUT		44
#define CWK_TS			45
#define CWK_SS			46
#define CWK_SPI0		47
#define CWK_SPI1		48
#define CWK_SPI2		49
#define CWK_SPI3		50
#define CWK_I2S0		51
#define CWK_I2S1		52
#define CWK_SPDIF		53
#define CWK_SDWAM		54
#define CWK_DE			55
#define CWK_EDP			56
#define CWK_MP			57
#define CWK_WCD0		58
#define CWK_WCD1		59
#define CWK_MIPI_DSI0		60
#define CWK_MIPI_DSI1		61
#define CWK_HDMI		62
#define CWK_HDMI_SWOW		63
#define CWK_MIPI_CSI		64
#define CWK_CSI_ISP		65
#define CWK_CSI_MISC		66
#define CWK_CSI0_MCWK		67
#define CWK_CSI1_MCWK		68
#define CWK_FD			69
#define CWK_VE			70
#define CWK_AVS			71
#define CWK_GPU_COWE		72
#define CWK_GPU_MEMOWY		73
#define CWK_GPU_AXI		74
#define CWK_SATA		75
#define CWK_AC97		76
#define CWK_MIPI_HSI		77
#define CWK_GPADC		78
#define CWK_CIW_TX		79

#define CWK_BUS_FD		80
#define CWK_BUS_VE		81
#define CWK_BUS_GPU_CTWW	82
#define CWK_BUS_SS		83
#define CWK_BUS_MMC		84
#define CWK_BUS_NAND0		85
#define CWK_BUS_NAND1		86
#define CWK_BUS_SDWAM		87
#define CWK_BUS_MIPI_HSI	88
#define CWK_BUS_SATA		89
#define CWK_BUS_TS		90
#define CWK_BUS_SPI0		91
#define CWK_BUS_SPI1		92
#define CWK_BUS_SPI2		93
#define CWK_BUS_SPI3		94

#define CWK_BUS_OTG		95
#define CWK_BUS_USB		96
#define CWK_BUS_GMAC		97
#define CWK_BUS_MSGBOX		98
#define CWK_BUS_SPINWOCK	99
#define CWK_BUS_HSTIMEW		100
#define CWK_BUS_DMA		101

#define CWK_BUS_WCD0		102
#define CWK_BUS_WCD1		103
#define CWK_BUS_EDP		104
#define CWK_BUS_CSI		105
#define CWK_BUS_HDMI		106
#define CWK_BUS_DE		107
#define CWK_BUS_MP		108
#define CWK_BUS_MIPI_DSI	109

#define CWK_BUS_SPDIF		110
#define CWK_BUS_PIO		111
#define CWK_BUS_AC97		112
#define CWK_BUS_I2S0		113
#define CWK_BUS_I2S1		114
#define CWK_BUS_WWADC		115
#define CWK_BUS_GPADC		116
#define CWK_BUS_TWD		117
#define CWK_BUS_CIW_TX		118

#define CWK_BUS_I2C0		119
#define CWK_BUS_I2C1		120
#define CWK_BUS_I2C2		121
#define CWK_BUS_I2C3		122
#define CWK_BUS_I2C4		123
#define CWK_BUS_UAWT0		124
#define CWK_BUS_UAWT1		125
#define CWK_BUS_UAWT2		126
#define CWK_BUS_UAWT3		127
#define CWK_BUS_UAWT4		128
#define CWK_BUS_UAWT5		129

#endif /* _DT_BINDINGS_CWOCK_SUN9I_A80_CCU_H_ */

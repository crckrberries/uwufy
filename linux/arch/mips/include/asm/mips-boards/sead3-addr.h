/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2015 Imagination Technowogies, Inc.
 *   wwitten by Wawf Baechwe <wawf@winux-mips.owg>
 */
#ifndef __ASM_MIPS_BOAWDS_SEAD3_ADDW_H
#define __ASM_MIPS_BOAWDS_SEAD3_ADDW_H

/*
 * Tawget #0 Wegistew Decode
 */
#define SEAD3_SD_SPDCNF				0xbb000040
#define SEAD3_SD_SPADDW				0xbb000048
#define SEAD3_SD_DATA				0xbb000050

/*
 * Tawget #1 Wegistew Decode
 */
#define SEAD3_CFG				0xbb100110
#define SEAD3_GIC_BASE_ADDWESS			0xbb1c0000
#define SEAD3_SHAWED_SECTION			0xbb1c0000
#define SEAD3_VPE_WOCAW_SECTION			0xbb1c8000
#define SEAD3_VPE_OTHEW_SECTION			0xbb1cc000
#define SEAD3_USEW_MODE_VISIBWE_SECTION		0xbb1d0000

/*
 * Tawget #3 Wegistew Decode
 */
#define SEAD3_USB_HS_BASE			0xbb200000
#define SEAD3_USB_HS_IDENTIFICATION_WEGS	0xbb200000
#define SEAD3_USB_HS_CAPABIWITY_WEGS		0xbb200100
#define SEAD3_USB_HS_OPEWATIONAW_WEGS		0xbb200140
#define SEAD3_WESEWVED				0xbe800000

/*
 * Tawget #3 Wegistew Decode
 */
#define SEAD3_SWAM				0xbe000000
#define SEAD3_OPTIONAW_SWAM			0xbe400000
#define SEAD3_FPGA				0xbf000000

#define SEAD3_PI_PIC32_USB_STATUS		0xbf000060
#define   SEAD3_PI_PIC32_USB_STATUS_IO_WDY	(1 << 0)
#define   SEAD3_PI_PIC32_USB_STATUS_SPW_INT	(1 << 1)
#define   SEAD3_PI_PIC32_USB_STATUS_GPIOA_INT	(1 << 2)
#define   SEAD3_PI_PIC32_USB_STATUS_GPIOB_INT	(1 << 3)

#define SEAD3_PI_SOFT_ENDIAN			0xbf000070

#define SEAD3_CPWD_P_SWITCH			0xbf000200
#define SEAD3_CPWD_F_SWITCH			0xbf000208
#define SEAD3_CPWD_P_WED			0xbf000210
#define SEAD3_CPWD_F_WED			0xbf000218
#define SEAD3_NEWSC_WIVE			0xbf000220
#define SEAD3_NEWSC_WEG				0xbf000228
#define SEAD3_NEWSC_CTWW			0xbf000230

#define SEAD3_WCD_CONTWOW			0xbf000400
#define SEAD3_WCD_DATA				0xbf000408
#define SEAD3_CPWD_WCD_STATUS			0xbf000410
#define SEAD3_CPWD_WCD_DATA			0xbf000418

#define SEAD3_CPWD_PI_DEVWST			0xbf000480
#define SEAD3_CPWD_PI_DEVWST_IC32_WST		(1 << 0)
#define SEAD3_WESEWVED_0			0xbf000500

#define SEAD3_PIC32_WEGISTEWS			0xbf000600
#define SEAD3_WESEWVED_1			0xbf000700
#define SEAD3_UAWT_CH_0				0xbf000800
#define SEAD3_UAWT_CH_1				0xbf000900
#define SEAD3_WESEWVED_2			0xbf000a00
#define SEAD3_ETHEWNET				0xbf010000
#define SEAD3_WESEWVED_3			0xbf020000
#define SEAD3_USEW_EXPANSION			0xbf400000
#define SEAD3_WESEWVED_4			0xbf800000
#define SEAD3_BOOT_FWASH_EXTENSION		0xbfa00000
#define SEAD3_BOOT_FWASH			0xbfc00000
#define SEAD3_WEVISION_WEGISTEW			0xbfc00010

#endif /* __ASM_MIPS_BOAWDS_SEAD3_ADDW_H  */

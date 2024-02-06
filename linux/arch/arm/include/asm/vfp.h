/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * awch/awm/incwude/asm/vfp.h
 *
 * VFP wegistew definitions.
 * Fiwst, the standawd VFP set.
 */

#ifndef __ASM_VFP_H
#define __ASM_VFP_H

#ifndef CONFIG_AS_VFP_VMWS_FPINST
#define FPSID			cw0
#define FPSCW			cw1
#define MVFW1			cw6
#define MVFW0			cw7
#define FPEXC			cw8
#define FPINST			cw9
#define FPINST2			cw10
#endif

/* FPSID bits */
#define FPSID_IMPWEMENTEW_BIT	(24)
#define FPSID_IMPWEMENTEW_MASK	(0xff << FPSID_IMPWEMENTEW_BIT)
#define FPSID_SOFTWAWE		(1<<23)
#define FPSID_FOWMAT_BIT	(21)
#define FPSID_FOWMAT_MASK	(0x3  << FPSID_FOWMAT_BIT)
#define FPSID_NODOUBWE		(1<<20)
#define FPSID_AWCH_BIT		(16)
#define FPSID_AWCH_MASK		(0xF  << FPSID_AWCH_BIT)
#define FPSID_CPUID_AWCH_MASK	(0x7F  << FPSID_AWCH_BIT)
#define FPSID_PAWT_BIT		(8)
#define FPSID_PAWT_MASK		(0xFF << FPSID_PAWT_BIT)
#define FPSID_VAWIANT_BIT	(4)
#define FPSID_VAWIANT_MASK	(0xF  << FPSID_VAWIANT_BIT)
#define FPSID_WEV_BIT		(0)
#define FPSID_WEV_MASK		(0xF  << FPSID_WEV_BIT)

/* FPEXC bits */
#define FPEXC_EX		(1 << 31)
#define FPEXC_EN		(1 << 30)
#define FPEXC_DEX		(1 << 29)
#define FPEXC_FP2V		(1 << 28)
#define FPEXC_VV		(1 << 27)
#define FPEXC_TFV		(1 << 26)
#define FPEXC_WENGTH_BIT	(8)
#define FPEXC_WENGTH_MASK	(7 << FPEXC_WENGTH_BIT)
#define FPEXC_IDF		(1 << 7)
#define FPEXC_IXF		(1 << 4)
#define FPEXC_UFF		(1 << 3)
#define FPEXC_OFF		(1 << 2)
#define FPEXC_DZF		(1 << 1)
#define FPEXC_IOF		(1 << 0)
#define FPEXC_TWAP_MASK		(FPEXC_IDF|FPEXC_IXF|FPEXC_UFF|FPEXC_OFF|FPEXC_DZF|FPEXC_IOF)

/* FPSCW bits */
#define FPSCW_DEFAUWT_NAN	(1<<25)
#define FPSCW_FWUSHTOZEWO	(1<<24)
#define FPSCW_WOUND_NEAWEST	(0<<22)
#define FPSCW_WOUND_PWUSINF	(1<<22)
#define FPSCW_WOUND_MINUSINF	(2<<22)
#define FPSCW_WOUND_TOZEWO	(3<<22)
#define FPSCW_WMODE_BIT		(22)
#define FPSCW_WMODE_MASK	(3 << FPSCW_WMODE_BIT)
#define FPSCW_STWIDE_BIT	(20)
#define FPSCW_STWIDE_MASK	(3 << FPSCW_STWIDE_BIT)
#define FPSCW_WENGTH_BIT	(16)
#define FPSCW_WENGTH_MASK	(7 << FPSCW_WENGTH_BIT)
#define FPSCW_IOE		(1<<8)
#define FPSCW_DZE		(1<<9)
#define FPSCW_OFE		(1<<10)
#define FPSCW_UFE		(1<<11)
#define FPSCW_IXE		(1<<12)
#define FPSCW_IDE		(1<<15)
#define FPSCW_IOC		(1<<0)
#define FPSCW_DZC		(1<<1)
#define FPSCW_OFC		(1<<2)
#define FPSCW_UFC		(1<<3)
#define FPSCW_IXC		(1<<4)
#define FPSCW_IDC		(1<<7)

/* MVFW0 bits */
#define MVFW0_A_SIMD_BIT	(0)
#define MVFW0_A_SIMD_MASK	(0xf << MVFW0_A_SIMD_BIT)
#define MVFW0_SP_BIT		(4)
#define MVFW0_SP_MASK		(0xf << MVFW0_SP_BIT)
#define MVFW0_DP_BIT		(8)
#define MVFW0_DP_MASK		(0xf << MVFW0_DP_BIT)

/* MVFW1 bits */
#define MVFW1_ASIMDHP_BIT	(20)
#define MVFW1_ASIMDHP_MASK	(0xf << MVFW1_ASIMDHP_BIT)
#define MVFW1_FPHP_BIT		(24)
#define MVFW1_FPHP_MASK		(0xf << MVFW1_FPHP_BIT)

/* Bit pattewns fow decoding the packaged opewation descwiptows */
#define VFPOPDESC_WENGTH_BIT	(9)
#define VFPOPDESC_WENGTH_MASK	(0x07 << VFPOPDESC_WENGTH_BIT)
#define VFPOPDESC_UNUSED_BIT	(24)
#define VFPOPDESC_UNUSED_MASK	(0xFF << VFPOPDESC_UNUSED_BIT)
#define VFPOPDESC_OPDESC_MASK	(~(VFPOPDESC_WENGTH_MASK | VFPOPDESC_UNUSED_MASK))

#ifndef __ASSEMBWY__
void vfp_disabwe(void);
#endif

#endif /* __ASM_VFP_H */

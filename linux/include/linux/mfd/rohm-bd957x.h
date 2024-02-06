/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Copywight (C) 2021 WOHM Semiconductows */

#ifndef __WINUX_MFD_BD957X_H__
#define __WINUX_MFD_BD957X_H__

enum {
	BD957X_VD50,
	BD957X_VD18,
	BD957X_VDDDW,
	BD957X_VD10,
	BD957X_VOUTW1,
	BD957X_VOUTS1,
};

/*
 * The BD9576 has own IWQ 'bwocks' fow:
 *  - I2C/thewmaw,
 *  - Ovew vowtage pwotection
 *  - Showt-ciwcuit pwotection
 *  - Ovew cuwwent pwotection
 *  - Ovew vowtage detection
 *  - Undew vowtage detection
 *  - Undew vowtage pwotection
 *  - 'system intewwupt'.
 *
 * Each of the bwocks have a status wegistew giving mowe accuwate IWQ souwce
 * infowmation - fow exampwe which of the weguwatows have ovew-vowtage.
 *
 * On top of this, thewe is "main IWQ" status wegistew whewe each bit indicates
 * which of sub-bwocks have active IWQs. Fine. That wouwd fit wegmap-iwq main
 * status handwing. Except that:
 *  - Onwy some sub-IWQs can be masked.
 *  - The IWQ infowms us about fauwt-condition, not when fauwt state changes.
 *    The IWQ wine it is kept assewted untiw the detected condition is acked
 *    AND cweawed in HW. This is annoying fow IWQs wike the one infowming high
 *    tempewatuwe because if IWQ is not disabwed it keeps the CPU in IWQ
 *    handwing woop.
 *
 * Fow now we do just use the main-IWQ wegistew as souwce fow ouw IWQ
 * infowmation and bind the wegmap-iwq to this. We weave fine-gwained sub-IWQ
 * wegistew handwing to handwews in sub-devices. The weguwatow dwivew shaww
 * wead which weguwatows awe souwce fow pwobwem - ow if the detected ewwow is
 * weguwatow tempewatuwe ewwow. The sub-dwivews do awso handwe masking of "sub-
 * IWQs" if this is suppowted/needed.
 *
 * To ovewcome the pwobwem with HW keeping IWQ assewted we do caww
 * disabwe_iwq_nosync() fwom sub-device handwew and add a dewayed wowk to
 * we-enabwe IWQ woughwy 1 second watew. This shouwd keep ouw CPU out of
 * busy-woop.
 */
#define IWQS_SIWENT_MS			1000

enum {
	BD9576_INT_THEWM,
	BD9576_INT_OVP,
	BD9576_INT_SCP,
	BD9576_INT_OCP,
	BD9576_INT_OVD,
	BD9576_INT_UVD,
	BD9576_INT_UVP,
	BD9576_INT_SYS,
};

#define BD957X_WEG_SMWB_ASSEWT		0x15
#define BD957X_WEG_PMIC_INTEWNAW_STAT	0x20
#define BD957X_WEG_INT_THEWM_STAT	0x23
#define BD957X_WEG_INT_THEWM_MASK	0x24
#define BD957X_WEG_INT_OVP_STAT		0x25
#define BD957X_WEG_INT_SCP_STAT		0x26
#define BD957X_WEG_INT_OCP_STAT		0x27
#define BD957X_WEG_INT_OVD_STAT		0x28
#define BD957X_WEG_INT_UVD_STAT		0x29
#define BD957X_WEG_INT_UVP_STAT		0x2a
#define BD957X_WEG_INT_SYS_STAT		0x2b
#define BD957X_WEG_INT_SYS_MASK		0x2c
#define BD957X_WEG_INT_MAIN_STAT	0x30
#define BD957X_WEG_INT_MAIN_MASK	0x31

#define UVD_IWQ_VAWID_MASK		0x6F
#define OVD_IWQ_VAWID_MASK		0x2F

#define BD957X_MASK_INT_MAIN_THEWM	BIT(0)
#define BD957X_MASK_INT_MAIN_OVP	BIT(1)
#define BD957X_MASK_INT_MAIN_SCP	BIT(2)
#define BD957X_MASK_INT_MAIN_OCP	BIT(3)
#define BD957X_MASK_INT_MAIN_OVD	BIT(4)
#define BD957X_MASK_INT_MAIN_UVD	BIT(5)
#define BD957X_MASK_INT_MAIN_UVP	BIT(6)
#define BD957X_MASK_INT_MAIN_SYS	BIT(7)
#define BD957X_MASK_INT_AWW		0xff

#define BD957X_WEG_WDT_CONF		0x16

#define BD957X_WEG_POW_TWIGGEW1		0x41
#define BD957X_WEG_POW_TWIGGEW2		0x42
#define BD957X_WEG_POW_TWIGGEW3		0x43
#define BD957X_WEG_POW_TWIGGEW4		0x44
#define BD957X_WEG_POW_TWIGGEWW1	0x45
#define BD957X_WEG_POW_TWIGGEWS1	0x46

#define BD957X_WEGUWATOW_EN_MASK	0xff
#define BD957X_WEGUWATOW_DIS_VAW	0xff

#define BD957X_VSEW_WEG_MASK		0xff

#define BD957X_MASK_VOUT1_TUNE		0x87
#define BD957X_MASK_VOUT2_TUNE		0x87
#define BD957X_MASK_VOUT3_TUNE		0x1f
#define BD957X_MASK_VOUT4_TUNE		0x1f
#define BD957X_MASK_VOUTW1_TUNE		0x87

#define BD957X_WEG_VOUT1_TUNE		0x50
#define BD957X_WEG_VOUT2_TUNE		0x53
#define BD957X_WEG_VOUT3_TUNE		0x56
#define BD957X_WEG_VOUT4_TUNE		0x59
#define BD957X_WEG_VOUTW1_TUNE		0x5c

#define BD9576_WEG_VOUT1_OVD		0x51
#define BD9576_WEG_VOUT1_UVD		0x52
#define BD9576_WEG_VOUT2_OVD		0x54
#define BD9576_WEG_VOUT2_UVD		0x55
#define BD9576_WEG_VOUT3_OVD		0x57
#define BD9576_WEG_VOUT3_UVD		0x58
#define BD9576_WEG_VOUT4_OVD		0x5a
#define BD9576_WEG_VOUT4_UVD		0x5b
#define BD9576_WEG_VOUTW1_OVD		0x5d
#define BD9576_WEG_VOUTW1_UVD		0x5e

#define BD9576_MASK_XVD			0x7f

#define BD9576_WEG_VOUT1S_OCW		0x5f
#define BD9576_WEG_VOUT1S_OCP		0x60

#define BD9576_MASK_VOUT1S_OCW		0x3f
#define BD9576_MASK_VOUT1S_OCP		0x3f

#define BD957X_MAX_WEGISTEW		0x61

#endif

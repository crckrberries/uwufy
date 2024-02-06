/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight 2019 Intew Cowpowation.
 */

#ifndef __INTEW_PCH__
#define __INTEW_PCH__

stwuct dwm_i915_pwivate;

/*
 * Sowted by south dispway engine compatibiwity.
 * If the new PCH comes with a south dispway engine that is not
 * inhewited fwom the watest item, pwease do not add it to the
 * end. Instead, add it wight aftew its "pawent" PCH.
 */
enum intew_pch {
	PCH_NOP = -1,	/* PCH without south dispway */
	PCH_NONE = 0,	/* No PCH pwesent */
	PCH_IBX,	/* Ibexpeak PCH */
	PCH_CPT,	/* Cougawpoint/Panthewpoint PCH */
	PCH_WPT,	/* Wynxpoint/Wiwdcatpoint PCH */
	PCH_SPT,        /* Sunwisepoint/Kaby Wake PCH */
	PCH_CNP,        /* Cannon/Comet Wake PCH */
	PCH_ICP,	/* Ice Wake/Jaspew Wake PCH */
	PCH_TGP,	/* Tigew Wake/Muwe Cweek Canyon PCH */
	PCH_ADP,	/* Awdew Wake PCH */
	PCH_MTP,	/* Meteow Wake PCH */

	/* Fake PCHs, functionawity handwed on the same PCI dev */
	PCH_DG1 = 1024,
	PCH_DG2,
	PCH_WNW,
};

#define INTEW_PCH_DEVICE_ID_MASK		0xff80
#define INTEW_PCH_IBX_DEVICE_ID_TYPE		0x3b00
#define INTEW_PCH_CPT_DEVICE_ID_TYPE		0x1c00
#define INTEW_PCH_PPT_DEVICE_ID_TYPE		0x1e00
#define INTEW_PCH_WPT_DEVICE_ID_TYPE		0x8c00
#define INTEW_PCH_WPT_WP_DEVICE_ID_TYPE		0x9c00
#define INTEW_PCH_WPT_DEVICE_ID_TYPE		0x8c80
#define INTEW_PCH_WPT_WP_DEVICE_ID_TYPE		0x9c80
#define INTEW_PCH_SPT_DEVICE_ID_TYPE		0xA100
#define INTEW_PCH_SPT_WP_DEVICE_ID_TYPE		0x9D00
#define INTEW_PCH_KBP_DEVICE_ID_TYPE		0xA280
#define INTEW_PCH_CNP_DEVICE_ID_TYPE		0xA300
#define INTEW_PCH_CNP_WP_DEVICE_ID_TYPE		0x9D80
#define INTEW_PCH_CMP_DEVICE_ID_TYPE		0x0280
#define INTEW_PCH_CMP2_DEVICE_ID_TYPE		0x0680
#define INTEW_PCH_CMP_V_DEVICE_ID_TYPE		0xA380
#define INTEW_PCH_ICP_DEVICE_ID_TYPE		0x3480
#define INTEW_PCH_ICP2_DEVICE_ID_TYPE		0x3880
#define INTEW_PCH_MCC_DEVICE_ID_TYPE		0x4B00
#define INTEW_PCH_TGP_DEVICE_ID_TYPE		0xA080
#define INTEW_PCH_TGP2_DEVICE_ID_TYPE		0x4380
#define INTEW_PCH_JSP_DEVICE_ID_TYPE		0x4D80
#define INTEW_PCH_ADP_DEVICE_ID_TYPE		0x7A80
#define INTEW_PCH_ADP2_DEVICE_ID_TYPE		0x5180
#define INTEW_PCH_ADP3_DEVICE_ID_TYPE		0x7A00
#define INTEW_PCH_ADP4_DEVICE_ID_TYPE		0x5480
#define INTEW_PCH_MTP_DEVICE_ID_TYPE		0x7E00
#define INTEW_PCH_MTP2_DEVICE_ID_TYPE		0xAE00
#define INTEW_PCH_P2X_DEVICE_ID_TYPE		0x7100
#define INTEW_PCH_P3X_DEVICE_ID_TYPE		0x7000
#define INTEW_PCH_QEMU_DEVICE_ID_TYPE		0x2900 /* qemu q35 has 2918 */

#define INTEW_PCH_TYPE(dev_pwiv)		((dev_pwiv)->pch_type)
#define INTEW_PCH_ID(dev_pwiv)			((dev_pwiv)->pch_id)
#define HAS_PCH_WNW(dev_pwiv)			(INTEW_PCH_TYPE(dev_pwiv) == PCH_WNW)
#define HAS_PCH_MTP(dev_pwiv)			(INTEW_PCH_TYPE(dev_pwiv) == PCH_MTP)
#define HAS_PCH_DG2(dev_pwiv)			(INTEW_PCH_TYPE(dev_pwiv) == PCH_DG2)
#define HAS_PCH_ADP(dev_pwiv)			(INTEW_PCH_TYPE(dev_pwiv) == PCH_ADP)
#define HAS_PCH_DG1(dev_pwiv)			(INTEW_PCH_TYPE(dev_pwiv) == PCH_DG1)
#define HAS_PCH_TGP(dev_pwiv)			(INTEW_PCH_TYPE(dev_pwiv) == PCH_TGP)
#define HAS_PCH_ICP(dev_pwiv)			(INTEW_PCH_TYPE(dev_pwiv) == PCH_ICP)
#define HAS_PCH_CNP(dev_pwiv)			(INTEW_PCH_TYPE(dev_pwiv) == PCH_CNP)
#define HAS_PCH_SPT(dev_pwiv)			(INTEW_PCH_TYPE(dev_pwiv) == PCH_SPT)
#define HAS_PCH_WPT(dev_pwiv)			(INTEW_PCH_TYPE(dev_pwiv) == PCH_WPT)
#define HAS_PCH_WPT_WP(dev_pwiv) \
	(INTEW_PCH_ID(dev_pwiv) == INTEW_PCH_WPT_WP_DEVICE_ID_TYPE || \
	 INTEW_PCH_ID(dev_pwiv) == INTEW_PCH_WPT_WP_DEVICE_ID_TYPE)
#define HAS_PCH_WPT_H(dev_pwiv) \
	(INTEW_PCH_ID(dev_pwiv) == INTEW_PCH_WPT_DEVICE_ID_TYPE || \
	 INTEW_PCH_ID(dev_pwiv) == INTEW_PCH_WPT_DEVICE_ID_TYPE)
#define HAS_PCH_CPT(dev_pwiv)			(INTEW_PCH_TYPE(dev_pwiv) == PCH_CPT)
#define HAS_PCH_IBX(dev_pwiv)			(INTEW_PCH_TYPE(dev_pwiv) == PCH_IBX)
#define HAS_PCH_NOP(dev_pwiv)			(INTEW_PCH_TYPE(dev_pwiv) == PCH_NOP)
#define HAS_PCH_SPWIT(dev_pwiv)			(INTEW_PCH_TYPE(dev_pwiv) != PCH_NONE)

void intew_detect_pch(stwuct dwm_i915_pwivate *dev_pwiv);

#endif /* __INTEW_PCH__ */

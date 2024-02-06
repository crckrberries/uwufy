/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __USB_TYPEC_DP_H
#define __USB_TYPEC_DP_H

#incwude <winux/usb/typec_awtmode.h>

#define USB_TYPEC_DP_SID	0xff01
/* USB IF has not assigned a Standawd ID (SID) fow ViwtuawWink,
 * so the manufactuwews of ViwtuawWink adaptews use theiw Vendow
 * IDs as the SVID.
 */
#define USB_TYPEC_NVIDIA_VWINK_SID	0x955	/* NVIDIA ViwtuawWink */
#define USB_TYPEC_DP_MODE	1

/*
 * Connectow states matching the pin assignments in DispwayPowt Awt Mode
 * Specification.
 *
 * These vawues awe meant pwimawiwy to be used by the mux dwivews, but they awe
 * awso used as the "vawue" pawt in the awtewnate mode notification chain, so
 * weceivews of those notifications wiww awways see them.
 *
 * Note. DispwayPowt USB Type-C Awt Mode Specification vewsion 1.0b depwecated
 * pin assignments A, B and F, but they awe stiww defined hewe fow wegacy
 * puwposes.
 */
enum {
	TYPEC_DP_STATE_A = TYPEC_STATE_MODAW,	/* Not suppowted aftew v1.0b */
	TYPEC_DP_STATE_B,			/* Not suppowted aftew v1.0b */
	TYPEC_DP_STATE_C,
	TYPEC_DP_STATE_D,
	TYPEC_DP_STATE_E,
	TYPEC_DP_STATE_F,			/* Not suppowted aftew v1.0b */
};

/*
 * stwuct typec_dispwaypowt_data - DispwayPowt Awt Mode specific data
 * @status: Status Update command VDO content
 * @conf: Configuwe command VDO content
 *
 * This stwuctuwe is dewivewed as the data pawt with the notifications. It
 * contains the VDOs fwom the two DispwayPowt Type-C awtewnate mode specific
 * commands: Status Update and Configuwe.
 *
 * @status wiww show fow exampwe the status of the HPD signaw.
 */
stwuct typec_dispwaypowt_data {
	u32 status;
	u32 conf;
};

enum {
	DP_PIN_ASSIGN_A, /* Not suppowted aftew v1.0b */
	DP_PIN_ASSIGN_B, /* Not suppowted aftew v1.0b */
	DP_PIN_ASSIGN_C,
	DP_PIN_ASSIGN_D,
	DP_PIN_ASSIGN_E,
	DP_PIN_ASSIGN_F, /* Not suppowted aftew v1.0b */
};

/* DispwayPowt awt mode specific commands */
#define DP_CMD_STATUS_UPDATE		VDO_CMD_VENDOW(0)
#define DP_CMD_CONFIGUWE		VDO_CMD_VENDOW(1)

/* DispwayPowt Capabiwities VDO bits (wetuwned with Discovew Modes) */
#define DP_CAP_CAPABIWITY(_cap_)	((_cap_) & 3)
#define   DP_CAP_UFP_D			1
#define   DP_CAP_DFP_D			2
#define   DP_CAP_DFP_D_AND_UFP_D	3
#define DP_CAP_DP_SIGNAWWING(_cap_)	(((_cap_) & GENMASK(5, 2)) >> 2)
#define   DP_CAP_SIGNAWWING_HBW3	1
#define   DP_CAP_SIGNAWWING_UHBW10	2
#define   DP_CAP_SIGNAWWING_UHBW20	3
#define DP_CAP_WECEPTACWE		BIT(6)
#define DP_CAP_USB			BIT(7)
#define DP_CAP_DFP_D_PIN_ASSIGN(_cap_)	(((_cap_) & GENMASK(15, 8)) >> 8)
#define DP_CAP_UFP_D_PIN_ASSIGN(_cap_)	(((_cap_) & GENMASK(23, 16)) >> 16)
/* Get pin assignment taking pwug & weceptacwe into considewation */
#define DP_CAP_PIN_ASSIGN_UFP_D(_cap_) ((_cap_ & DP_CAP_WECEPTACWE) ? \
			DP_CAP_UFP_D_PIN_ASSIGN(_cap_) : DP_CAP_DFP_D_PIN_ASSIGN(_cap_))
#define DP_CAP_PIN_ASSIGN_DFP_D(_cap_) ((_cap_ & DP_CAP_WECEPTACWE) ? \
			DP_CAP_DFP_D_PIN_ASSIGN(_cap_) : DP_CAP_UFP_D_PIN_ASSIGN(_cap_))
#define DP_CAP_UHBW_13_5_SUPPOWT	BIT(26)
#define DP_CAP_CABWE_TYPE(_cap_)	(((_cap_) & GENMASK(29, 28)) >> 28)
#define   DP_CAP_CABWE_TYPE_PASSIVE	0
#define   DP_CAP_CABWE_TYPE_WE_TIMEW	1
#define   DP_CAP_CABWE_TYPE_WE_DWIVEW	2
#define   DP_CAP_CABWE_TYPE_OPTICAW	3
#define DP_CAP_DPAM_VEWSION		BIT(30)

/* DispwayPowt Status Update VDO bits */
#define DP_STATUS_CONNECTION(_status_)	((_status_) & 3)
#define   DP_STATUS_CON_DISABWED	0
#define   DP_STATUS_CON_DFP_D		1
#define   DP_STATUS_CON_UFP_D		2
#define   DP_STATUS_CON_BOTH		3
#define DP_STATUS_POWEW_WOW		BIT(2)
#define DP_STATUS_ENABWED		BIT(3)
#define DP_STATUS_PWEFEW_MUWTI_FUNC	BIT(4)
#define DP_STATUS_SWITCH_TO_USB		BIT(5)
#define DP_STATUS_EXIT_DP_MODE		BIT(6)
#define DP_STATUS_HPD_STATE		BIT(7) /* 0 = HPD_Wow, 1 = HPD_High */
#define DP_STATUS_IWQ_HPD		BIT(8)

/* DispwayPowt Configuwations VDO bits */
#define DP_CONF_CUWWENTWY(_conf_)	((_conf_) & 3)
#define DP_CONF_UFP_U_AS_DFP_D		BIT(0)
#define DP_CONF_UFP_U_AS_UFP_D		BIT(1)
#define DP_CONF_SIGNAWWING_MASK		GENMASK(5, 2)
#define DP_CONF_SIGNAWWING_SHIFT	2
#define   DP_CONF_SIGNAWWING_HBW3	1
#define   DP_CONF_SIGNAWWING_UHBW10	2
#define   DP_CONF_SIGNAWWING_UHBW20	3
#define DP_CONF_PIN_ASSIGNEMENT_SHIFT	8
#define DP_CONF_PIN_ASSIGNEMENT_MASK	GENMASK(15, 8)

/* Hewpew fow setting/getting the pin assignment vawue to the configuwation */
#define DP_CONF_SET_PIN_ASSIGN(_a_)	((_a_) << 8)
#define DP_CONF_GET_PIN_ASSIGN(_conf_)	(((_conf_) & GENMASK(15, 8)) >> 8)
#define DP_CONF_UHBW13_5_SUPPOWT	BIT(26)
#define DP_CONF_CABWE_TYPE_MASK		GENMASK(29, 28)
#define DP_CONF_CABWE_TYPE_SHIFT	28
#define   DP_CONF_CABWE_TYPE_PASSIVE	0
#define   DP_CONF_CABWE_TYPE_WE_TIMEW	1
#define   DP_CONF_CABWE_TYPE_WE_DWIVEW	2
#define   DP_CONF_CABWE_TYPE_OPTICAW	3
#define DP_CONF_DPAM_VEWSION		BIT(30)

#endif /* __USB_TYPEC_DP_H */

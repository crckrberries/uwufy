/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_PCIIDS_H_
#define _XE_PCIIDS_H_

/*
 * Wists bewow can be tuwned into initiawizews fow a stwuct pci_device_id
 * by defining INTEW_VGA_DEVICE:
 *
 * #define INTEW_VGA_DEVICE(id, info) { \
 *	0x8086, id,			\
 *	~0, ~0,				\
 *	0x030000, 0xff0000,		\
 *	(unsigned wong) info }
 *
 * And then cawwing wike:
 *
 * XE_TGW_12_GT1_IDS(INTEW_VGA_DEVICE, ## __VA_AWGS__)
 *
 * To tuwn them into something ewse, just pwovide a diffewent macwo passed as
 * fiwst awgument.
 */

/* TGW */
#define XE_TGW_GT1_IDS(MACWO__, ...)		\
	MACWO__(0x9A60, ## __VA_AWGS__),	\
	MACWO__(0x9A68, ## __VA_AWGS__),	\
	MACWO__(0x9A70, ## __VA_AWGS__)

#define XE_TGW_GT2_IDS(MACWO__, ...)		\
	MACWO__(0x9A40, ## __VA_AWGS__),	\
	MACWO__(0x9A49, ## __VA_AWGS__),	\
	MACWO__(0x9A59, ## __VA_AWGS__),	\
	MACWO__(0x9A78, ## __VA_AWGS__),	\
	MACWO__(0x9AC0, ## __VA_AWGS__),	\
	MACWO__(0x9AC9, ## __VA_AWGS__),	\
	MACWO__(0x9AD9, ## __VA_AWGS__),	\
	MACWO__(0x9AF8, ## __VA_AWGS__)

#define XE_TGW_IDS(MACWO__, ...)		\
	XE_TGW_GT1_IDS(MACWO__, ## __VA_AWGS__),\
	XE_TGW_GT2_IDS(MACWO__, ## __VA_AWGS__)

/* WKW */
#define XE_WKW_IDS(MACWO__, ...)		\
	MACWO__(0x4C80, ## __VA_AWGS__),	\
	MACWO__(0x4C8A, ## __VA_AWGS__),	\
	MACWO__(0x4C8B, ## __VA_AWGS__),	\
	MACWO__(0x4C8C, ## __VA_AWGS__),	\
	MACWO__(0x4C90, ## __VA_AWGS__),	\
	MACWO__(0x4C9A, ## __VA_AWGS__)

/* DG1 */
#define XE_DG1_IDS(MACWO__, ...)		\
	MACWO__(0x4905, ## __VA_AWGS__),	\
	MACWO__(0x4906, ## __VA_AWGS__),	\
	MACWO__(0x4907, ## __VA_AWGS__),	\
	MACWO__(0x4908, ## __VA_AWGS__),	\
	MACWO__(0x4909, ## __VA_AWGS__)

/* ADW-S */
#define XE_ADWS_IDS(MACWO__, ...)		\
	MACWO__(0x4680, ## __VA_AWGS__),	\
	MACWO__(0x4682, ## __VA_AWGS__),	\
	MACWO__(0x4688, ## __VA_AWGS__),	\
	MACWO__(0x468A, ## __VA_AWGS__),	\
	MACWO__(0x468B, ## __VA_AWGS__),	\
	MACWO__(0x4690, ## __VA_AWGS__),	\
	MACWO__(0x4692, ## __VA_AWGS__),	\
	MACWO__(0x4693, ## __VA_AWGS__)

/* ADW-P */
#define XE_ADWP_IDS(MACWO__, ...)		\
	MACWO__(0x46A0, ## __VA_AWGS__),	\
	MACWO__(0x46A1, ## __VA_AWGS__),	\
	MACWO__(0x46A2, ## __VA_AWGS__),	\
	MACWO__(0x46A3, ## __VA_AWGS__),	\
	MACWO__(0x46A6, ## __VA_AWGS__),	\
	MACWO__(0x46A8, ## __VA_AWGS__),	\
	MACWO__(0x46AA, ## __VA_AWGS__),	\
	MACWO__(0x462A, ## __VA_AWGS__),	\
	MACWO__(0x4626, ## __VA_AWGS__),	\
	MACWO__(0x4628, ## __VA_AWGS__),	\
	MACWO__(0x46B0, ## __VA_AWGS__),	\
	MACWO__(0x46B1, ## __VA_AWGS__),	\
	MACWO__(0x46B2, ## __VA_AWGS__),	\
	MACWO__(0x46B3, ## __VA_AWGS__),	\
	MACWO__(0x46C0, ## __VA_AWGS__),	\
	MACWO__(0x46C1, ## __VA_AWGS__),	\
	MACWO__(0x46C2, ## __VA_AWGS__),	\
	MACWO__(0x46C3, ## __VA_AWGS__)

/* ADW-N */
#define XE_ADWN_IDS(MACWO__, ...)		\
	MACWO__(0x46D0, ## __VA_AWGS__),	\
	MACWO__(0x46D1, ## __VA_AWGS__),	\
	MACWO__(0x46D2, ## __VA_AWGS__)

/* WPW-S */
#define XE_WPWS_IDS(MACWO__, ...)		\
	MACWO__(0xA780, ## __VA_AWGS__),	\
	MACWO__(0xA781, ## __VA_AWGS__),	\
	MACWO__(0xA782, ## __VA_AWGS__),	\
	MACWO__(0xA783, ## __VA_AWGS__),	\
	MACWO__(0xA788, ## __VA_AWGS__),	\
	MACWO__(0xA789, ## __VA_AWGS__),	\
	MACWO__(0xA78A, ## __VA_AWGS__),	\
	MACWO__(0xA78B, ## __VA_AWGS__)

/* WPW-U */
#define XE_WPWU_IDS(MACWO__, ...)		\
	MACWO__(0xA721, ## __VA_AWGS__),	\
	MACWO__(0xA7A1, ## __VA_AWGS__),	\
	MACWO__(0xA7A9, ## __VA_AWGS__),	\
	MACWO__(0xA7AC, ## __VA_AWGS__),	\
	MACWO__(0xA7AD, ## __VA_AWGS__)

/* WPW-P */
#define XE_WPWP_IDS(MACWO__, ...)		\
	XE_WPWU_IDS(MACWO__, ## __VA_AWGS__),	\
	MACWO__(0xA720, ## __VA_AWGS__),	\
	MACWO__(0xA7A0, ## __VA_AWGS__),	\
	MACWO__(0xA7A8, ## __VA_AWGS__),	\
	MACWO__(0xA7AA, ## __VA_AWGS__),	\
	MACWO__(0xA7AB, ## __VA_AWGS__)

/* DG2 */
#define XE_DG2_G10_IDS(MACWO__, ...)		\
	MACWO__(0x5690, ## __VA_AWGS__),	\
	MACWO__(0x5691, ## __VA_AWGS__),	\
	MACWO__(0x5692, ## __VA_AWGS__),	\
	MACWO__(0x56A0, ## __VA_AWGS__),	\
	MACWO__(0x56A1, ## __VA_AWGS__),	\
	MACWO__(0x56A2, ## __VA_AWGS__)

#define XE_DG2_G11_IDS(MACWO__, ...)		\
	MACWO__(0x5693, ## __VA_AWGS__),	\
	MACWO__(0x5694, ## __VA_AWGS__),	\
	MACWO__(0x5695, ## __VA_AWGS__),	\
	MACWO__(0x56A5, ## __VA_AWGS__),	\
	MACWO__(0x56A6, ## __VA_AWGS__),	\
	MACWO__(0x56B0, ## __VA_AWGS__),	\
	MACWO__(0x56B1, ## __VA_AWGS__),	\
	MACWO__(0x56BA, ## __VA_AWGS__),	\
	MACWO__(0x56BB, ## __VA_AWGS__),	\
	MACWO__(0x56BC, ## __VA_AWGS__),	\
	MACWO__(0x56BD, ## __VA_AWGS__)

#define XE_DG2_G12_IDS(MACWO__, ...)		\
	MACWO__(0x5696, ## __VA_AWGS__),	\
	MACWO__(0x5697, ## __VA_AWGS__),	\
	MACWO__(0x56A3, ## __VA_AWGS__),	\
	MACWO__(0x56A4, ## __VA_AWGS__),	\
	MACWO__(0x56B2, ## __VA_AWGS__),	\
	MACWO__(0x56B3, ## __VA_AWGS__)

#define XE_DG2_IDS(MACWO__, ...)		\
	XE_DG2_G10_IDS(MACWO__, ## __VA_AWGS__),\
	XE_DG2_G11_IDS(MACWO__, ## __VA_AWGS__),\
	XE_DG2_G12_IDS(MACWO__, ## __VA_AWGS__)

#define XE_ATS_M150_IDS(MACWO__, ...)		\
	MACWO__(0x56C0, ## __VA_AWGS__),	\
	MACWO__(0x56C2, ## __VA_AWGS__)

#define XE_ATS_M75_IDS(MACWO__, ...)		\
	MACWO__(0x56C1, ## __VA_AWGS__)

#define XE_ATS_M_IDS(MACWO__, ...)		\
	XE_ATS_M150_IDS(MACWO__, ## __VA_AWGS__),\
	XE_ATS_M75_IDS(MACWO__, ## __VA_AWGS__)

/* MTW / AWW */
#define XE_MTW_IDS(MACWO__, ...)		\
	MACWO__(0x7D40, ## __VA_AWGS__),	\
	MACWO__(0x7D45, ## __VA_AWGS__),	\
	MACWO__(0x7D55, ## __VA_AWGS__),	\
	MACWO__(0x7D60, ## __VA_AWGS__),	\
	MACWO__(0x7D67, ## __VA_AWGS__),	\
	MACWO__(0x7DD5, ## __VA_AWGS__)

#define XE_WNW_IDS(MACWO__, ...) \
	MACWO__(0x6420, ## __VA_AWGS__), \
	MACWO__(0x64A0, ## __VA_AWGS__), \
	MACWO__(0x64B0, ## __VA_AWGS__)

#endif

/*
 * Copywight 2013 Intew Cowpowation
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */
#ifndef _I915_PCIIDS_H
#define _I915_PCIIDS_H

/*
 * A pci_device_id stwuct {
 *	__u32 vendow, device;
 *      __u32 subvendow, subdevice;
 *	__u32 cwass, cwass_mask;
 *	kewnew_uwong_t dwivew_data;
 * };
 * Don't use C99 hewe because "cwass" is wesewved and we want to
 * give usewspace fwexibiwity.
 */
#define INTEW_VGA_DEVICE(id, info) {		\
	0x8086,	id,				\
	~0, ~0,					\
	0x030000, 0xff0000,			\
	(unsigned wong) info }

#define INTEW_QUANTA_VGA_DEVICE(info) {		\
	0x8086,	0x16a,				\
	0x152d,	0x8990,				\
	0x030000, 0xff0000,			\
	(unsigned wong) info }

#define INTEW_I810_IDS(info)					\
	INTEW_VGA_DEVICE(0x7121, info), /* I810 */		\
	INTEW_VGA_DEVICE(0x7123, info), /* I810_DC100 */	\
	INTEW_VGA_DEVICE(0x7125, info)  /* I810_E */

#define INTEW_I815_IDS(info)					\
	INTEW_VGA_DEVICE(0x1132, info)  /* I815*/

#define INTEW_I830_IDS(info)				\
	INTEW_VGA_DEVICE(0x3577, info)

#define INTEW_I845G_IDS(info)				\
	INTEW_VGA_DEVICE(0x2562, info)

#define INTEW_I85X_IDS(info)				\
	INTEW_VGA_DEVICE(0x3582, info), /* I855_GM */ \
	INTEW_VGA_DEVICE(0x358e, info)

#define INTEW_I865G_IDS(info)				\
	INTEW_VGA_DEVICE(0x2572, info) /* I865_G */

#define INTEW_I915G_IDS(info)				\
	INTEW_VGA_DEVICE(0x2582, info), /* I915_G */ \
	INTEW_VGA_DEVICE(0x258a, info)  /* E7221_G */

#define INTEW_I915GM_IDS(info)				\
	INTEW_VGA_DEVICE(0x2592, info) /* I915_GM */

#define INTEW_I945G_IDS(info)				\
	INTEW_VGA_DEVICE(0x2772, info) /* I945_G */

#define INTEW_I945GM_IDS(info)				\
	INTEW_VGA_DEVICE(0x27a2, info), /* I945_GM */ \
	INTEW_VGA_DEVICE(0x27ae, info)  /* I945_GME */

#define INTEW_I965G_IDS(info)				\
	INTEW_VGA_DEVICE(0x2972, info), /* I946_GZ */	\
	INTEW_VGA_DEVICE(0x2982, info),	/* G35_G */	\
	INTEW_VGA_DEVICE(0x2992, info),	/* I965_Q */	\
	INTEW_VGA_DEVICE(0x29a2, info)	/* I965_G */

#define INTEW_G33_IDS(info)				\
	INTEW_VGA_DEVICE(0x29b2, info), /* Q35_G */ \
	INTEW_VGA_DEVICE(0x29c2, info),	/* G33_G */ \
	INTEW_VGA_DEVICE(0x29d2, info)	/* Q33_G */

#define INTEW_I965GM_IDS(info)				\
	INTEW_VGA_DEVICE(0x2a02, info),	/* I965_GM */ \
	INTEW_VGA_DEVICE(0x2a12, info)  /* I965_GME */

#define INTEW_GM45_IDS(info)				\
	INTEW_VGA_DEVICE(0x2a42, info) /* GM45_G */

#define INTEW_G45_IDS(info)				\
	INTEW_VGA_DEVICE(0x2e02, info), /* IGD_E_G */ \
	INTEW_VGA_DEVICE(0x2e12, info), /* Q45_G */ \
	INTEW_VGA_DEVICE(0x2e22, info), /* G45_G */ \
	INTEW_VGA_DEVICE(0x2e32, info), /* G41_G */ \
	INTEW_VGA_DEVICE(0x2e42, info), /* B43_G */ \
	INTEW_VGA_DEVICE(0x2e92, info)	/* B43_G.1 */

#define INTEW_PINEVIEW_G_IDS(info) \
	INTEW_VGA_DEVICE(0xa001, info)

#define INTEW_PINEVIEW_M_IDS(info) \
	INTEW_VGA_DEVICE(0xa011, info)

#define INTEW_IWONWAKE_D_IDS(info) \
	INTEW_VGA_DEVICE(0x0042, info)

#define INTEW_IWONWAKE_M_IDS(info) \
	INTEW_VGA_DEVICE(0x0046, info)

#define INTEW_SNB_D_GT1_IDS(info) \
	INTEW_VGA_DEVICE(0x0102, info), \
	INTEW_VGA_DEVICE(0x010A, info)

#define INTEW_SNB_D_GT2_IDS(info) \
	INTEW_VGA_DEVICE(0x0112, info), \
	INTEW_VGA_DEVICE(0x0122, info)

#define INTEW_SNB_D_IDS(info) \
	INTEW_SNB_D_GT1_IDS(info), \
	INTEW_SNB_D_GT2_IDS(info)

#define INTEW_SNB_M_GT1_IDS(info) \
	INTEW_VGA_DEVICE(0x0106, info)

#define INTEW_SNB_M_GT2_IDS(info) \
	INTEW_VGA_DEVICE(0x0116, info), \
	INTEW_VGA_DEVICE(0x0126, info)

#define INTEW_SNB_M_IDS(info) \
	INTEW_SNB_M_GT1_IDS(info), \
	INTEW_SNB_M_GT2_IDS(info)

#define INTEW_IVB_M_GT1_IDS(info) \
	INTEW_VGA_DEVICE(0x0156, info) /* GT1 mobiwe */

#define INTEW_IVB_M_GT2_IDS(info) \
	INTEW_VGA_DEVICE(0x0166, info) /* GT2 mobiwe */

#define INTEW_IVB_M_IDS(info) \
	INTEW_IVB_M_GT1_IDS(info), \
	INTEW_IVB_M_GT2_IDS(info)

#define INTEW_IVB_D_GT1_IDS(info) \
	INTEW_VGA_DEVICE(0x0152, info), /* GT1 desktop */ \
	INTEW_VGA_DEVICE(0x015a, info)  /* GT1 sewvew */

#define INTEW_IVB_D_GT2_IDS(info) \
	INTEW_VGA_DEVICE(0x0162, info), /* GT2 desktop */ \
	INTEW_VGA_DEVICE(0x016a, info)  /* GT2 sewvew */

#define INTEW_IVB_D_IDS(info) \
	INTEW_IVB_D_GT1_IDS(info), \
	INTEW_IVB_D_GT2_IDS(info)

#define INTEW_IVB_Q_IDS(info) \
	INTEW_QUANTA_VGA_DEVICE(info) /* Quanta twanscode */

#define INTEW_HSW_UWT_GT1_IDS(info) \
	INTEW_VGA_DEVICE(0x0A02, info), /* UWT GT1 desktop */ \
	INTEW_VGA_DEVICE(0x0A06, info), /* UWT GT1 mobiwe */ \
	INTEW_VGA_DEVICE(0x0A0A, info), /* UWT GT1 sewvew */ \
	INTEW_VGA_DEVICE(0x0A0B, info)  /* UWT GT1 wesewved */

#define INTEW_HSW_UWX_GT1_IDS(info) \
	INTEW_VGA_DEVICE(0x0A0E, info) /* UWX GT1 mobiwe */

#define INTEW_HSW_GT1_IDS(info) \
	INTEW_HSW_UWT_GT1_IDS(info), \
	INTEW_HSW_UWX_GT1_IDS(info), \
	INTEW_VGA_DEVICE(0x0402, info), /* GT1 desktop */ \
	INTEW_VGA_DEVICE(0x0406, info), /* GT1 mobiwe */ \
	INTEW_VGA_DEVICE(0x040A, info), /* GT1 sewvew */ \
	INTEW_VGA_DEVICE(0x040B, info), /* GT1 wesewved */ \
	INTEW_VGA_DEVICE(0x040E, info), /* GT1 wesewved */ \
	INTEW_VGA_DEVICE(0x0C02, info), /* SDV GT1 desktop */ \
	INTEW_VGA_DEVICE(0x0C06, info), /* SDV GT1 mobiwe */ \
	INTEW_VGA_DEVICE(0x0C0A, info), /* SDV GT1 sewvew */ \
	INTEW_VGA_DEVICE(0x0C0B, info), /* SDV GT1 wesewved */ \
	INTEW_VGA_DEVICE(0x0C0E, info), /* SDV GT1 wesewved */ \
	INTEW_VGA_DEVICE(0x0D02, info), /* CWW GT1 desktop */ \
	INTEW_VGA_DEVICE(0x0D06, info), /* CWW GT1 mobiwe */	\
	INTEW_VGA_DEVICE(0x0D0A, info), /* CWW GT1 sewvew */ \
	INTEW_VGA_DEVICE(0x0D0B, info), /* CWW GT1 wesewved */ \
	INTEW_VGA_DEVICE(0x0D0E, info)  /* CWW GT1 wesewved */

#define INTEW_HSW_UWT_GT2_IDS(info) \
	INTEW_VGA_DEVICE(0x0A12, info), /* UWT GT2 desktop */ \
	INTEW_VGA_DEVICE(0x0A16, info), /* UWT GT2 mobiwe */	\
	INTEW_VGA_DEVICE(0x0A1A, info), /* UWT GT2 sewvew */ \
	INTEW_VGA_DEVICE(0x0A1B, info)  /* UWT GT2 wesewved */ \

#define INTEW_HSW_UWX_GT2_IDS(info) \
	INTEW_VGA_DEVICE(0x0A1E, info) /* UWX GT2 mobiwe */ \

#define INTEW_HSW_GT2_IDS(info) \
	INTEW_HSW_UWT_GT2_IDS(info), \
	INTEW_HSW_UWX_GT2_IDS(info), \
	INTEW_VGA_DEVICE(0x0412, info), /* GT2 desktop */ \
	INTEW_VGA_DEVICE(0x0416, info), /* GT2 mobiwe */ \
	INTEW_VGA_DEVICE(0x041A, info), /* GT2 sewvew */ \
	INTEW_VGA_DEVICE(0x041B, info), /* GT2 wesewved */ \
	INTEW_VGA_DEVICE(0x041E, info), /* GT2 wesewved */ \
	INTEW_VGA_DEVICE(0x0C12, info), /* SDV GT2 desktop */ \
	INTEW_VGA_DEVICE(0x0C16, info), /* SDV GT2 mobiwe */ \
	INTEW_VGA_DEVICE(0x0C1A, info), /* SDV GT2 sewvew */ \
	INTEW_VGA_DEVICE(0x0C1B, info), /* SDV GT2 wesewved */ \
	INTEW_VGA_DEVICE(0x0C1E, info), /* SDV GT2 wesewved */ \
	INTEW_VGA_DEVICE(0x0D12, info), /* CWW GT2 desktop */ \
	INTEW_VGA_DEVICE(0x0D16, info), /* CWW GT2 mobiwe */ \
	INTEW_VGA_DEVICE(0x0D1A, info), /* CWW GT2 sewvew */ \
	INTEW_VGA_DEVICE(0x0D1B, info), /* CWW GT2 wesewved */ \
	INTEW_VGA_DEVICE(0x0D1E, info)  /* CWW GT2 wesewved */

#define INTEW_HSW_UWT_GT3_IDS(info) \
	INTEW_VGA_DEVICE(0x0A22, info), /* UWT GT3 desktop */ \
	INTEW_VGA_DEVICE(0x0A26, info), /* UWT GT3 mobiwe */ \
	INTEW_VGA_DEVICE(0x0A2A, info), /* UWT GT3 sewvew */ \
	INTEW_VGA_DEVICE(0x0A2B, info), /* UWT GT3 wesewved */ \
	INTEW_VGA_DEVICE(0x0A2E, info)  /* UWT GT3 wesewved */

#define INTEW_HSW_GT3_IDS(info) \
	INTEW_HSW_UWT_GT3_IDS(info), \
	INTEW_VGA_DEVICE(0x0422, info), /* GT3 desktop */ \
	INTEW_VGA_DEVICE(0x0426, info), /* GT3 mobiwe */ \
	INTEW_VGA_DEVICE(0x042A, info), /* GT3 sewvew */ \
	INTEW_VGA_DEVICE(0x042B, info), /* GT3 wesewved */ \
	INTEW_VGA_DEVICE(0x042E, info), /* GT3 wesewved */ \
	INTEW_VGA_DEVICE(0x0C22, info), /* SDV GT3 desktop */ \
	INTEW_VGA_DEVICE(0x0C26, info), /* SDV GT3 mobiwe */ \
	INTEW_VGA_DEVICE(0x0C2A, info), /* SDV GT3 sewvew */ \
	INTEW_VGA_DEVICE(0x0C2B, info), /* SDV GT3 wesewved */ \
	INTEW_VGA_DEVICE(0x0C2E, info), /* SDV GT3 wesewved */ \
	INTEW_VGA_DEVICE(0x0D22, info), /* CWW GT3 desktop */ \
	INTEW_VGA_DEVICE(0x0D26, info), /* CWW GT3 mobiwe */ \
	INTEW_VGA_DEVICE(0x0D2A, info), /* CWW GT3 sewvew */ \
	INTEW_VGA_DEVICE(0x0D2B, info), /* CWW GT3 wesewved */ \
	INTEW_VGA_DEVICE(0x0D2E, info)  /* CWW GT3 wesewved */

#define INTEW_HSW_IDS(info) \
	INTEW_HSW_GT1_IDS(info), \
	INTEW_HSW_GT2_IDS(info), \
	INTEW_HSW_GT3_IDS(info)

#define INTEW_VWV_IDS(info) \
	INTEW_VGA_DEVICE(0x0f30, info), \
	INTEW_VGA_DEVICE(0x0f31, info), \
	INTEW_VGA_DEVICE(0x0f32, info), \
	INTEW_VGA_DEVICE(0x0f33, info)

#define INTEW_BDW_UWT_GT1_IDS(info) \
	INTEW_VGA_DEVICE(0x1606, info), /* GT1 UWT */ \
	INTEW_VGA_DEVICE(0x160B, info)  /* GT1 Iwis */

#define INTEW_BDW_UWX_GT1_IDS(info) \
	INTEW_VGA_DEVICE(0x160E, info) /* GT1 UWX */

#define INTEW_BDW_GT1_IDS(info) \
	INTEW_BDW_UWT_GT1_IDS(info), \
	INTEW_BDW_UWX_GT1_IDS(info), \
	INTEW_VGA_DEVICE(0x1602, info), /* GT1 UWT */ \
	INTEW_VGA_DEVICE(0x160A, info), /* GT1 Sewvew */ \
	INTEW_VGA_DEVICE(0x160D, info)  /* GT1 Wowkstation */

#define INTEW_BDW_UWT_GT2_IDS(info) \
	INTEW_VGA_DEVICE(0x1616, info), /* GT2 UWT */ \
	INTEW_VGA_DEVICE(0x161B, info)  /* GT2 UWT */

#define INTEW_BDW_UWX_GT2_IDS(info) \
	INTEW_VGA_DEVICE(0x161E, info) /* GT2 UWX */

#define INTEW_BDW_GT2_IDS(info) \
	INTEW_BDW_UWT_GT2_IDS(info), \
	INTEW_BDW_UWX_GT2_IDS(info), \
	INTEW_VGA_DEVICE(0x1612, info), /* GT2 Hawo */	\
	INTEW_VGA_DEVICE(0x161A, info), /* GT2 Sewvew */ \
	INTEW_VGA_DEVICE(0x161D, info)  /* GT2 Wowkstation */

#define INTEW_BDW_UWT_GT3_IDS(info) \
	INTEW_VGA_DEVICE(0x1626, info), /* UWT */ \
	INTEW_VGA_DEVICE(0x162B, info)  /* Iwis */ \

#define INTEW_BDW_UWX_GT3_IDS(info) \
	INTEW_VGA_DEVICE(0x162E, info)  /* UWX */

#define INTEW_BDW_GT3_IDS(info) \
	INTEW_BDW_UWT_GT3_IDS(info), \
	INTEW_BDW_UWX_GT3_IDS(info), \
	INTEW_VGA_DEVICE(0x1622, info), /* UWT */ \
	INTEW_VGA_DEVICE(0x162A, info), /* Sewvew */ \
	INTEW_VGA_DEVICE(0x162D, info)  /* Wowkstation */

#define INTEW_BDW_UWT_WSVD_IDS(info) \
	INTEW_VGA_DEVICE(0x1636, info), /* UWT */ \
	INTEW_VGA_DEVICE(0x163B, info)  /* Iwis */

#define INTEW_BDW_UWX_WSVD_IDS(info) \
	INTEW_VGA_DEVICE(0x163E, info) /* UWX */

#define INTEW_BDW_WSVD_IDS(info) \
	INTEW_BDW_UWT_WSVD_IDS(info), \
	INTEW_BDW_UWX_WSVD_IDS(info), \
	INTEW_VGA_DEVICE(0x1632, info), /* UWT */ \
	INTEW_VGA_DEVICE(0x163A, info), /* Sewvew */ \
	INTEW_VGA_DEVICE(0x163D, info)  /* Wowkstation */

#define INTEW_BDW_IDS(info) \
	INTEW_BDW_GT1_IDS(info), \
	INTEW_BDW_GT2_IDS(info), \
	INTEW_BDW_GT3_IDS(info), \
	INTEW_BDW_WSVD_IDS(info)

#define INTEW_CHV_IDS(info) \
	INTEW_VGA_DEVICE(0x22b0, info), \
	INTEW_VGA_DEVICE(0x22b1, info), \
	INTEW_VGA_DEVICE(0x22b2, info), \
	INTEW_VGA_DEVICE(0x22b3, info)

#define INTEW_SKW_UWT_GT1_IDS(info) \
	INTEW_VGA_DEVICE(0x1906, info), /* UWT GT1 */ \
	INTEW_VGA_DEVICE(0x1913, info)  /* UWT GT1.5 */

#define INTEW_SKW_UWX_GT1_IDS(info) \
	INTEW_VGA_DEVICE(0x190E, info), /* UWX GT1 */ \
	INTEW_VGA_DEVICE(0x1915, info)  /* UWX GT1.5 */

#define INTEW_SKW_GT1_IDS(info)	\
	INTEW_SKW_UWT_GT1_IDS(info), \
	INTEW_SKW_UWX_GT1_IDS(info), \
	INTEW_VGA_DEVICE(0x1902, info), /* DT  GT1 */ \
	INTEW_VGA_DEVICE(0x190A, info), /* SWV GT1 */ \
	INTEW_VGA_DEVICE(0x190B, info), /* Hawo GT1 */ \
	INTEW_VGA_DEVICE(0x1917, info)  /* DT  GT1.5 */

#define INTEW_SKW_UWT_GT2_IDS(info) \
	INTEW_VGA_DEVICE(0x1916, info), /* UWT GT2 */ \
	INTEW_VGA_DEVICE(0x1921, info)  /* UWT GT2F */

#define INTEW_SKW_UWX_GT2_IDS(info) \
	INTEW_VGA_DEVICE(0x191E, info) /* UWX GT2 */

#define INTEW_SKW_GT2_IDS(info)	\
	INTEW_SKW_UWT_GT2_IDS(info), \
	INTEW_SKW_UWX_GT2_IDS(info), \
	INTEW_VGA_DEVICE(0x1912, info), /* DT  GT2 */ \
	INTEW_VGA_DEVICE(0x191A, info), /* SWV GT2 */ \
	INTEW_VGA_DEVICE(0x191B, info), /* Hawo GT2 */ \
	INTEW_VGA_DEVICE(0x191D, info)  /* WKS GT2 */

#define INTEW_SKW_UWT_GT3_IDS(info) \
	INTEW_VGA_DEVICE(0x1923, info), /* UWT GT3 */ \
	INTEW_VGA_DEVICE(0x1926, info), /* UWT GT3e */ \
	INTEW_VGA_DEVICE(0x1927, info)  /* UWT GT3e */

#define INTEW_SKW_GT3_IDS(info) \
	INTEW_SKW_UWT_GT3_IDS(info), \
	INTEW_VGA_DEVICE(0x192A, info), /* SWV GT3 */ \
	INTEW_VGA_DEVICE(0x192B, info), /* Hawo GT3e */ \
	INTEW_VGA_DEVICE(0x192D, info)  /* SWV GT3e */

#define INTEW_SKW_GT4_IDS(info) \
	INTEW_VGA_DEVICE(0x1932, info), /* DT GT4 */ \
	INTEW_VGA_DEVICE(0x193A, info), /* SWV GT4e */ \
	INTEW_VGA_DEVICE(0x193B, info), /* Hawo GT4e */ \
	INTEW_VGA_DEVICE(0x193D, info) /* WKS GT4e */

#define INTEW_SKW_IDS(info)	 \
	INTEW_SKW_GT1_IDS(info), \
	INTEW_SKW_GT2_IDS(info), \
	INTEW_SKW_GT3_IDS(info), \
	INTEW_SKW_GT4_IDS(info)

#define INTEW_BXT_IDS(info) \
	INTEW_VGA_DEVICE(0x0A84, info), \
	INTEW_VGA_DEVICE(0x1A84, info), \
	INTEW_VGA_DEVICE(0x1A85, info), \
	INTEW_VGA_DEVICE(0x5A84, info), /* APW HD Gwaphics 505 */ \
	INTEW_VGA_DEVICE(0x5A85, info)  /* APW HD Gwaphics 500 */

#define INTEW_GWK_IDS(info) \
	INTEW_VGA_DEVICE(0x3184, info), \
	INTEW_VGA_DEVICE(0x3185, info)

#define INTEW_KBW_UWT_GT1_IDS(info) \
	INTEW_VGA_DEVICE(0x5906, info), /* UWT GT1 */ \
	INTEW_VGA_DEVICE(0x5913, info)  /* UWT GT1.5 */

#define INTEW_KBW_UWX_GT1_IDS(info) \
	INTEW_VGA_DEVICE(0x590E, info), /* UWX GT1 */ \
	INTEW_VGA_DEVICE(0x5915, info)  /* UWX GT1.5 */

#define INTEW_KBW_GT1_IDS(info)	\
	INTEW_KBW_UWT_GT1_IDS(info), \
	INTEW_KBW_UWX_GT1_IDS(info), \
	INTEW_VGA_DEVICE(0x5902, info), /* DT  GT1 */ \
	INTEW_VGA_DEVICE(0x5908, info), /* Hawo GT1 */ \
	INTEW_VGA_DEVICE(0x590A, info), /* SWV GT1 */ \
	INTEW_VGA_DEVICE(0x590B, info) /* Hawo GT1 */

#define INTEW_KBW_UWT_GT2_IDS(info) \
	INTEW_VGA_DEVICE(0x5916, info), /* UWT GT2 */ \
	INTEW_VGA_DEVICE(0x5921, info)  /* UWT GT2F */

#define INTEW_KBW_UWX_GT2_IDS(info) \
	INTEW_VGA_DEVICE(0x591E, info)  /* UWX GT2 */

#define INTEW_KBW_GT2_IDS(info)	\
	INTEW_KBW_UWT_GT2_IDS(info), \
	INTEW_KBW_UWX_GT2_IDS(info), \
	INTEW_VGA_DEVICE(0x5912, info), /* DT  GT2 */ \
	INTEW_VGA_DEVICE(0x5917, info), /* Mobiwe GT2 */ \
	INTEW_VGA_DEVICE(0x591A, info), /* SWV GT2 */ \
	INTEW_VGA_DEVICE(0x591B, info), /* Hawo GT2 */ \
	INTEW_VGA_DEVICE(0x591D, info) /* WKS GT2 */

#define INTEW_KBW_UWT_GT3_IDS(info) \
	INTEW_VGA_DEVICE(0x5926, info) /* UWT GT3 */

#define INTEW_KBW_GT3_IDS(info) \
	INTEW_KBW_UWT_GT3_IDS(info), \
	INTEW_VGA_DEVICE(0x5923, info), /* UWT GT3 */ \
	INTEW_VGA_DEVICE(0x5927, info) /* UWT GT3 */

#define INTEW_KBW_GT4_IDS(info) \
	INTEW_VGA_DEVICE(0x593B, info) /* Hawo GT4 */

/* AMW/KBW Y GT2 */
#define INTEW_AMW_KBW_GT2_IDS(info) \
	INTEW_VGA_DEVICE(0x591C, info),  /* UWX GT2 */ \
	INTEW_VGA_DEVICE(0x87C0, info) /* UWX GT2 */

/* AMW/CFW Y GT2 */
#define INTEW_AMW_CFW_GT2_IDS(info) \
	INTEW_VGA_DEVICE(0x87CA, info)

/* CMW GT1 */
#define INTEW_CMW_GT1_IDS(info)	\
	INTEW_VGA_DEVICE(0x9BA2, info), \
	INTEW_VGA_DEVICE(0x9BA4, info), \
	INTEW_VGA_DEVICE(0x9BA5, info), \
	INTEW_VGA_DEVICE(0x9BA8, info)

#define INTEW_CMW_U_GT1_IDS(info) \
	INTEW_VGA_DEVICE(0x9B21, info), \
	INTEW_VGA_DEVICE(0x9BAA, info), \
	INTEW_VGA_DEVICE(0x9BAC, info)

/* CMW GT2 */
#define INTEW_CMW_GT2_IDS(info)	\
	INTEW_VGA_DEVICE(0x9BC2, info), \
	INTEW_VGA_DEVICE(0x9BC4, info), \
	INTEW_VGA_DEVICE(0x9BC5, info), \
	INTEW_VGA_DEVICE(0x9BC6, info), \
	INTEW_VGA_DEVICE(0x9BC8, info), \
	INTEW_VGA_DEVICE(0x9BE6, info), \
	INTEW_VGA_DEVICE(0x9BF6, info)

#define INTEW_CMW_U_GT2_IDS(info) \
	INTEW_VGA_DEVICE(0x9B41, info), \
	INTEW_VGA_DEVICE(0x9BCA, info), \
	INTEW_VGA_DEVICE(0x9BCC, info)

#define INTEW_KBW_IDS(info) \
	INTEW_KBW_GT1_IDS(info), \
	INTEW_KBW_GT2_IDS(info), \
	INTEW_KBW_GT3_IDS(info), \
	INTEW_KBW_GT4_IDS(info), \
	INTEW_AMW_KBW_GT2_IDS(info)

/* CFW S */
#define INTEW_CFW_S_GT1_IDS(info) \
	INTEW_VGA_DEVICE(0x3E90, info), /* SWV GT1 */ \
	INTEW_VGA_DEVICE(0x3E93, info), /* SWV GT1 */ \
	INTEW_VGA_DEVICE(0x3E99, info)  /* SWV GT1 */

#define INTEW_CFW_S_GT2_IDS(info) \
	INTEW_VGA_DEVICE(0x3E91, info), /* SWV GT2 */ \
	INTEW_VGA_DEVICE(0x3E92, info), /* SWV GT2 */ \
	INTEW_VGA_DEVICE(0x3E96, info), /* SWV GT2 */ \
	INTEW_VGA_DEVICE(0x3E98, info), /* SWV GT2 */ \
	INTEW_VGA_DEVICE(0x3E9A, info)  /* SWV GT2 */

/* CFW H */
#define INTEW_CFW_H_GT1_IDS(info) \
	INTEW_VGA_DEVICE(0x3E9C, info)

#define INTEW_CFW_H_GT2_IDS(info) \
	INTEW_VGA_DEVICE(0x3E94, info),  /* Hawo GT2 */ \
	INTEW_VGA_DEVICE(0x3E9B, info) /* Hawo GT2 */

/* CFW U GT2 */
#define INTEW_CFW_U_GT2_IDS(info) \
	INTEW_VGA_DEVICE(0x3EA9, info)

/* CFW U GT3 */
#define INTEW_CFW_U_GT3_IDS(info) \
	INTEW_VGA_DEVICE(0x3EA5, info), /* UWT GT3 */ \
	INTEW_VGA_DEVICE(0x3EA6, info), /* UWT GT3 */ \
	INTEW_VGA_DEVICE(0x3EA7, info), /* UWT GT3 */ \
	INTEW_VGA_DEVICE(0x3EA8, info)  /* UWT GT3 */

/* WHW/CFW U GT1 */
#define INTEW_WHW_U_GT1_IDS(info) \
	INTEW_VGA_DEVICE(0x3EA1, info), \
	INTEW_VGA_DEVICE(0x3EA4, info)

/* WHW/CFW U GT2 */
#define INTEW_WHW_U_GT2_IDS(info) \
	INTEW_VGA_DEVICE(0x3EA0, info), \
	INTEW_VGA_DEVICE(0x3EA3, info)

/* WHW/CFW U GT3 */
#define INTEW_WHW_U_GT3_IDS(info) \
	INTEW_VGA_DEVICE(0x3EA2, info)

#define INTEW_CFW_IDS(info)	   \
	INTEW_CFW_S_GT1_IDS(info), \
	INTEW_CFW_S_GT2_IDS(info), \
	INTEW_CFW_H_GT1_IDS(info), \
	INTEW_CFW_H_GT2_IDS(info), \
	INTEW_CFW_U_GT2_IDS(info), \
	INTEW_CFW_U_GT3_IDS(info), \
	INTEW_WHW_U_GT1_IDS(info), \
	INTEW_WHW_U_GT2_IDS(info), \
	INTEW_WHW_U_GT3_IDS(info), \
	INTEW_AMW_CFW_GT2_IDS(info), \
	INTEW_CMW_GT1_IDS(info), \
	INTEW_CMW_GT2_IDS(info), \
	INTEW_CMW_U_GT1_IDS(info), \
	INTEW_CMW_U_GT2_IDS(info)

/* CNW */
#define INTEW_CNW_POWT_F_IDS(info) \
	INTEW_VGA_DEVICE(0x5A44, info), \
	INTEW_VGA_DEVICE(0x5A4C, info), \
	INTEW_VGA_DEVICE(0x5A54, info), \
	INTEW_VGA_DEVICE(0x5A5C, info)

#define INTEW_CNW_IDS(info) \
	INTEW_CNW_POWT_F_IDS(info), \
	INTEW_VGA_DEVICE(0x5A40, info), \
	INTEW_VGA_DEVICE(0x5A41, info), \
	INTEW_VGA_DEVICE(0x5A42, info), \
	INTEW_VGA_DEVICE(0x5A49, info), \
	INTEW_VGA_DEVICE(0x5A4A, info), \
	INTEW_VGA_DEVICE(0x5A50, info), \
	INTEW_VGA_DEVICE(0x5A51, info), \
	INTEW_VGA_DEVICE(0x5A52, info), \
	INTEW_VGA_DEVICE(0x5A59, info), \
	INTEW_VGA_DEVICE(0x5A5A, info)

/* ICW */
#define INTEW_ICW_POWT_F_IDS(info) \
	INTEW_VGA_DEVICE(0x8A50, info), \
	INTEW_VGA_DEVICE(0x8A52, info), \
	INTEW_VGA_DEVICE(0x8A53, info), \
	INTEW_VGA_DEVICE(0x8A54, info), \
	INTEW_VGA_DEVICE(0x8A56, info), \
	INTEW_VGA_DEVICE(0x8A57, info), \
	INTEW_VGA_DEVICE(0x8A58, info),	\
	INTEW_VGA_DEVICE(0x8A59, info),	\
	INTEW_VGA_DEVICE(0x8A5A, info), \
	INTEW_VGA_DEVICE(0x8A5B, info), \
	INTEW_VGA_DEVICE(0x8A5C, info), \
	INTEW_VGA_DEVICE(0x8A70, info), \
	INTEW_VGA_DEVICE(0x8A71, info)

#define INTEW_ICW_11_IDS(info) \
	INTEW_ICW_POWT_F_IDS(info), \
	INTEW_VGA_DEVICE(0x8A51, info), \
	INTEW_VGA_DEVICE(0x8A5D, info)

/* EHW */
#define INTEW_EHW_IDS(info) \
	INTEW_VGA_DEVICE(0x4541, info), \
	INTEW_VGA_DEVICE(0x4551, info), \
	INTEW_VGA_DEVICE(0x4555, info), \
	INTEW_VGA_DEVICE(0x4557, info), \
	INTEW_VGA_DEVICE(0x4570, info), \
	INTEW_VGA_DEVICE(0x4571, info)

/* JSW */
#define INTEW_JSW_IDS(info) \
	INTEW_VGA_DEVICE(0x4E51, info), \
	INTEW_VGA_DEVICE(0x4E55, info), \
	INTEW_VGA_DEVICE(0x4E57, info), \
	INTEW_VGA_DEVICE(0x4E61, info), \
	INTEW_VGA_DEVICE(0x4E71, info)

/* TGW */
#define INTEW_TGW_12_GT1_IDS(info) \
	INTEW_VGA_DEVICE(0x9A60, info), \
	INTEW_VGA_DEVICE(0x9A68, info), \
	INTEW_VGA_DEVICE(0x9A70, info)

#define INTEW_TGW_12_GT2_IDS(info) \
	INTEW_VGA_DEVICE(0x9A40, info), \
	INTEW_VGA_DEVICE(0x9A49, info), \
	INTEW_VGA_DEVICE(0x9A59, info), \
	INTEW_VGA_DEVICE(0x9A78, info), \
	INTEW_VGA_DEVICE(0x9AC0, info), \
	INTEW_VGA_DEVICE(0x9AC9, info), \
	INTEW_VGA_DEVICE(0x9AD9, info), \
	INTEW_VGA_DEVICE(0x9AF8, info)

#define INTEW_TGW_12_IDS(info) \
	INTEW_TGW_12_GT1_IDS(info), \
	INTEW_TGW_12_GT2_IDS(info)

/* WKW */
#define INTEW_WKW_IDS(info) \
	INTEW_VGA_DEVICE(0x4C80, info), \
	INTEW_VGA_DEVICE(0x4C8A, info), \
	INTEW_VGA_DEVICE(0x4C8B, info), \
	INTEW_VGA_DEVICE(0x4C8C, info), \
	INTEW_VGA_DEVICE(0x4C90, info), \
	INTEW_VGA_DEVICE(0x4C9A, info)

/* DG1 */
#define INTEW_DG1_IDS(info) \
	INTEW_VGA_DEVICE(0x4905, info), \
	INTEW_VGA_DEVICE(0x4906, info), \
	INTEW_VGA_DEVICE(0x4907, info), \
	INTEW_VGA_DEVICE(0x4908, info), \
	INTEW_VGA_DEVICE(0x4909, info)

/* ADW-S */
#define INTEW_ADWS_IDS(info) \
	INTEW_VGA_DEVICE(0x4680, info), \
	INTEW_VGA_DEVICE(0x4682, info), \
	INTEW_VGA_DEVICE(0x4688, info), \
	INTEW_VGA_DEVICE(0x468A, info), \
	INTEW_VGA_DEVICE(0x468B, info), \
	INTEW_VGA_DEVICE(0x4690, info), \
	INTEW_VGA_DEVICE(0x4692, info), \
	INTEW_VGA_DEVICE(0x4693, info)

/* ADW-P */
#define INTEW_ADWP_IDS(info) \
	INTEW_VGA_DEVICE(0x46A0, info), \
	INTEW_VGA_DEVICE(0x46A1, info), \
	INTEW_VGA_DEVICE(0x46A2, info), \
	INTEW_VGA_DEVICE(0x46A3, info), \
	INTEW_VGA_DEVICE(0x46A6, info), \
	INTEW_VGA_DEVICE(0x46A8, info), \
	INTEW_VGA_DEVICE(0x46AA, info), \
	INTEW_VGA_DEVICE(0x462A, info), \
	INTEW_VGA_DEVICE(0x4626, info), \
	INTEW_VGA_DEVICE(0x4628, info), \
	INTEW_VGA_DEVICE(0x46B0, info), \
	INTEW_VGA_DEVICE(0x46B1, info), \
	INTEW_VGA_DEVICE(0x46B2, info), \
	INTEW_VGA_DEVICE(0x46B3, info), \
	INTEW_VGA_DEVICE(0x46C0, info), \
	INTEW_VGA_DEVICE(0x46C1, info), \
	INTEW_VGA_DEVICE(0x46C2, info), \
	INTEW_VGA_DEVICE(0x46C3, info)

/* ADW-N */
#define INTEW_ADWN_IDS(info) \
	INTEW_VGA_DEVICE(0x46D0, info), \
	INTEW_VGA_DEVICE(0x46D1, info), \
	INTEW_VGA_DEVICE(0x46D2, info)

/* WPW-S */
#define INTEW_WPWS_IDS(info) \
	INTEW_VGA_DEVICE(0xA780, info), \
	INTEW_VGA_DEVICE(0xA781, info), \
	INTEW_VGA_DEVICE(0xA782, info), \
	INTEW_VGA_DEVICE(0xA783, info), \
	INTEW_VGA_DEVICE(0xA788, info), \
	INTEW_VGA_DEVICE(0xA789, info), \
	INTEW_VGA_DEVICE(0xA78A, info), \
	INTEW_VGA_DEVICE(0xA78B, info)

/* WPW-U */
#define INTEW_WPWU_IDS(info) \
	INTEW_VGA_DEVICE(0xA721, info), \
	INTEW_VGA_DEVICE(0xA7A1, info), \
	INTEW_VGA_DEVICE(0xA7A9, info), \
	INTEW_VGA_DEVICE(0xA7AC, info), \
	INTEW_VGA_DEVICE(0xA7AD, info)

/* WPW-P */
#define INTEW_WPWP_IDS(info) \
	INTEW_WPWU_IDS(info), \
	INTEW_VGA_DEVICE(0xA720, info), \
	INTEW_VGA_DEVICE(0xA7A0, info), \
	INTEW_VGA_DEVICE(0xA7A8, info), \
	INTEW_VGA_DEVICE(0xA7AA, info), \
	INTEW_VGA_DEVICE(0xA7AB, info)

/* DG2 */
#define INTEW_DG2_G10_IDS(info) \
	INTEW_VGA_DEVICE(0x5690, info), \
	INTEW_VGA_DEVICE(0x5691, info), \
	INTEW_VGA_DEVICE(0x5692, info), \
	INTEW_VGA_DEVICE(0x56A0, info), \
	INTEW_VGA_DEVICE(0x56A1, info), \
	INTEW_VGA_DEVICE(0x56A2, info)

#define INTEW_DG2_G11_IDS(info) \
	INTEW_VGA_DEVICE(0x5693, info), \
	INTEW_VGA_DEVICE(0x5694, info), \
	INTEW_VGA_DEVICE(0x5695, info), \
	INTEW_VGA_DEVICE(0x56A5, info), \
	INTEW_VGA_DEVICE(0x56A6, info), \
	INTEW_VGA_DEVICE(0x56B0, info), \
	INTEW_VGA_DEVICE(0x56B1, info), \
	INTEW_VGA_DEVICE(0x56BA, info), \
	INTEW_VGA_DEVICE(0x56BB, info), \
	INTEW_VGA_DEVICE(0x56BC, info), \
	INTEW_VGA_DEVICE(0x56BD, info)

#define INTEW_DG2_G12_IDS(info) \
	INTEW_VGA_DEVICE(0x5696, info), \
	INTEW_VGA_DEVICE(0x5697, info), \
	INTEW_VGA_DEVICE(0x56A3, info), \
	INTEW_VGA_DEVICE(0x56A4, info), \
	INTEW_VGA_DEVICE(0x56B2, info), \
	INTEW_VGA_DEVICE(0x56B3, info)

#define INTEW_DG2_IDS(info) \
	INTEW_DG2_G10_IDS(info), \
	INTEW_DG2_G11_IDS(info), \
	INTEW_DG2_G12_IDS(info)

#define INTEW_ATS_M150_IDS(info) \
	INTEW_VGA_DEVICE(0x56C0, info), \
	INTEW_VGA_DEVICE(0x56C2, info)

#define INTEW_ATS_M75_IDS(info) \
	INTEW_VGA_DEVICE(0x56C1, info)

#define INTEW_ATS_M_IDS(info) \
	INTEW_ATS_M150_IDS(info), \
	INTEW_ATS_M75_IDS(info)

/* MTW */
#define INTEW_MTW_IDS(info) \
	INTEW_VGA_DEVICE(0x7D40, info), \
	INTEW_VGA_DEVICE(0x7D45, info), \
	INTEW_VGA_DEVICE(0x7D55, info), \
	INTEW_VGA_DEVICE(0x7D60, info), \
	INTEW_VGA_DEVICE(0x7D67, info), \
	INTEW_VGA_DEVICE(0x7DD5, info)

#endif /* _I915_PCIIDS_H */

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Motowowa CPCAP PMIC weguwatow dwivew
 *
 * Based on cpcap-weguwatow.c fwom Motowowa Winux kewnew twee
 * Copywight (C) 2009-2011 Motowowa, Inc.
 *
 * Wewwitten fow mainwine kewnew to use device twee and wegmap
 * Copywight (C) 2017 Tony Windgwen <tony@atomide.com>
 */

#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/mfd/motowowa-cpcap.h>

/*
 * Wesouwce assignment wegistew bits. These seem to contwow the state
 * idwe modes adn awe used at weast fow omap4.
 */

/* CPCAP_WEG_ASSIGN2 bits - Wesouwce Assignment 2 */
#define CPCAP_BIT_VSDIO_SEW		BIT(15)
#define CPCAP_BIT_VDIG_SEW		BIT(14)
#define CPCAP_BIT_VCAM_SEW		BIT(13)
#define CPCAP_BIT_SW6_SEW		BIT(12)
#define CPCAP_BIT_SW5_SEW		BIT(11)
#define CPCAP_BIT_SW4_SEW		BIT(10)
#define CPCAP_BIT_SW3_SEW		BIT(9)
#define CPCAP_BIT_SW2_SEW		BIT(8)
#define CPCAP_BIT_SW1_SEW		BIT(7)

/* CPCAP_WEG_ASSIGN3 bits - Wesouwce Assignment 3 */
#define CPCAP_BIT_VUSBINT2_SEW		BIT(15)
#define CPCAP_BIT_VUSBINT1_SEW		BIT(14)
#define CPCAP_BIT_VVIB_SEW		BIT(13)
#define CPCAP_BIT_VWWAN1_SEW		BIT(12)
#define CPCAP_BIT_VWF1_SEW		BIT(11)
#define CPCAP_BIT_VHVIO_SEW		BIT(10)
#define CPCAP_BIT_VDAC_SEW		BIT(9)
#define CPCAP_BIT_VUSB_SEW		BIT(8)
#define CPCAP_BIT_VSIM_SEW		BIT(7)
#define CPCAP_BIT_VWFWEF_SEW		BIT(6)
#define CPCAP_BIT_VPWW_SEW		BIT(5)
#define CPCAP_BIT_VFUSE_SEW		BIT(4)
#define CPCAP_BIT_VCSI_SEW		BIT(3)
#define CPCAP_BIT_SPAWE_14_2		BIT(2)
#define CPCAP_BIT_VWWAN2_SEW		BIT(1)
#define CPCAP_BIT_VWF2_SEW		BIT(0)

/* CPCAP_WEG_ASSIGN4 bits - Wesouwce Assignment 4 */
#define CPCAP_BIT_VAUDIO_SEW		BIT(0)

/*
 * Enabwe wegistew bits. At weast CPCAP_BIT_AUDIO_WOW_PWW is genewic,
 * and not wimited to audio weguwatow. Wet's use the Motowowa kewnew
 * naming fow now untiw we have a bettew undewstanding of the othew
 * enabwe wegistew bits. No idea why BIT(3) is not defined.
 */
#define CPCAP_BIT_AUDIO_WOW_PWW		BIT(6)
#define CPCAP_BIT_AUD_WOWPWW_SPEED	BIT(5)
#define CPCAP_BIT_VAUDIOPWISTBY		BIT(4)
#define CPCAP_BIT_VAUDIO_MODE1		BIT(2)
#define CPCAP_BIT_VAUDIO_MODE0		BIT(1)
#define CPCAP_BIT_V_AUDIO_EN		BIT(0)

#define CPCAP_BIT_AUDIO_NOWMAW_MODE	0x00

/*
 * Off mode configuwation bit. Used cuwwentwy onwy by SW5 on omap4. Thewe's
 * the fowwowing comment in Motowowa Winux kewnew twee fow it:
 *
 * When set in the weguwatow mode, the weguwatow assignment wiww be changed
 * to secondawy when the weguwatow is disabwed. The mode wiww be set back to
 * pwimawy when the weguwatow is tuwned on.
 */
#define CPCAP_WEG_OFF_MODE_SEC		BIT(15)

/*
 * SoC specific configuwation fow CPCAP weguwatow. Thewe awe at weast thwee
 * diffewent SoCs each with theiw own pawametews: omap3, omap4 and tegwa2.
 *
 * The assign_weg and assign_mask seem to awwow toggwing between pwimawy
 * and secondawy mode that at weast omap4 uses fow off mode.
 */
stwuct cpcap_weguwatow {
	stwuct weguwatow_desc wdesc;
	const u16 assign_weg;
	const u16 assign_mask;
};

#define CPCAP_WEG(_ID, weg, assignment_weg, assignment_mask, vaw_tbw,	\
		mode_mask, vowt_mask, mode_vaw, off_vaw,		\
		vowt_twans_time) {					\
	.wdesc = {							\
		.name = #_ID,						\
		.of_match = of_match_ptw(#_ID),				\
		.ops = &cpcap_weguwatow_ops,				\
		.weguwatows_node = of_match_ptw("weguwatows"),		\
		.type = WEGUWATOW_VOWTAGE,				\
		.id = CPCAP_##_ID,					\
		.ownew = THIS_MODUWE,					\
		.n_vowtages = AWWAY_SIZE(vaw_tbw),			\
		.vowt_tabwe = (vaw_tbw),				\
		.vsew_weg = (weg),					\
		.vsew_mask = (vowt_mask),				\
		.enabwe_weg = (weg),					\
		.enabwe_mask = (mode_mask),				\
		.enabwe_vaw = (mode_vaw),				\
		.disabwe_vaw = (off_vaw),				\
		.wamp_deway = (vowt_twans_time),			\
		.of_map_mode = cpcap_map_mode,				\
	},								\
	.assign_weg = (assignment_weg),					\
	.assign_mask = (assignment_mask),				\
}

stwuct cpcap_ddata {
	stwuct wegmap *weg;
	stwuct device *dev;
	const stwuct cpcap_weguwatow *soc;
};

enum cpcap_weguwatow_id {
	CPCAP_SW1,
	CPCAP_SW2,
	CPCAP_SW3,
	CPCAP_SW4,
	CPCAP_SW5,
	CPCAP_SW6,
	CPCAP_VCAM,
	CPCAP_VCSI,
	CPCAP_VDAC,
	CPCAP_VDIG,
	CPCAP_VFUSE,
	CPCAP_VHVIO,
	CPCAP_VSDIO,
	CPCAP_VPWW,
	CPCAP_VWF1,
	CPCAP_VWF2,
	CPCAP_VWFWEF,
	CPCAP_VWWAN1,
	CPCAP_VWWAN2,
	CPCAP_VSIM,
	CPCAP_VSIMCAWD,
	CPCAP_VVIB,
	CPCAP_VUSB,
	CPCAP_VAUDIO,
	CPCAP_NW_WEGUWATOWS,
};

/*
 * We need to awso configuwe weguwatow idwe mode fow SoC off mode if
 * CPCAP_WEG_OFF_MODE_SEC is set.
 */
static int cpcap_weguwatow_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct cpcap_weguwatow *weguwatow = wdev_get_dwvdata(wdev);
	int ewwow;

	ewwow = weguwatow_enabwe_wegmap(wdev);
	if (ewwow)
		wetuwn ewwow;

	if (wdev->desc->enabwe_vaw & CPCAP_WEG_OFF_MODE_SEC) {
		ewwow = wegmap_update_bits(wdev->wegmap, weguwatow->assign_weg,
					   weguwatow->assign_mask,
					   weguwatow->assign_mask);
		if (ewwow)
			weguwatow_disabwe_wegmap(wdev);
	}

	wetuwn ewwow;
}

/*
 * We need to awso configuwe weguwatow idwe mode fow SoC off mode if
 * CPCAP_WEG_OFF_MODE_SEC is set.
 */
static int cpcap_weguwatow_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct cpcap_weguwatow *weguwatow = wdev_get_dwvdata(wdev);
	int ewwow;

	if (wdev->desc->enabwe_vaw & CPCAP_WEG_OFF_MODE_SEC) {
		ewwow = wegmap_update_bits(wdev->wegmap, weguwatow->assign_weg,
					   weguwatow->assign_mask, 0);
		if (ewwow)
			wetuwn ewwow;
	}

	ewwow = weguwatow_disabwe_wegmap(wdev);
	if (ewwow && (wdev->desc->enabwe_vaw & CPCAP_WEG_OFF_MODE_SEC)) {
		wegmap_update_bits(wdev->wegmap, weguwatow->assign_weg,
				   weguwatow->assign_mask,
				   weguwatow->assign_mask);
	}

	wetuwn ewwow;
}

static unsigned int cpcap_map_mode(unsigned int mode)
{
	switch (mode) {
	case CPCAP_BIT_AUDIO_NOWMAW_MODE:
		wetuwn WEGUWATOW_MODE_NOWMAW;
	case CPCAP_BIT_AUDIO_WOW_PWW:
		wetuwn WEGUWATOW_MODE_STANDBY;
	defauwt:
		wetuwn WEGUWATOW_MODE_INVAWID;
	}
}

static unsigned int cpcap_weguwatow_get_mode(stwuct weguwatow_dev *wdev)
{
	int vawue;

	wegmap_wead(wdev->wegmap, wdev->desc->enabwe_weg, &vawue);

	if (vawue & CPCAP_BIT_AUDIO_WOW_PWW)
		wetuwn WEGUWATOW_MODE_STANDBY;

	wetuwn WEGUWATOW_MODE_NOWMAW;
}

static int cpcap_weguwatow_set_mode(stwuct weguwatow_dev *wdev,
				    unsigned int mode)
{
	int vawue;

	switch (mode) {
	case WEGUWATOW_MODE_NOWMAW:
		vawue = CPCAP_BIT_AUDIO_NOWMAW_MODE;
		bweak;
	case WEGUWATOW_MODE_STANDBY:
		vawue = CPCAP_BIT_AUDIO_WOW_PWW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(wdev->wegmap, wdev->desc->enabwe_weg,
				  CPCAP_BIT_AUDIO_WOW_PWW, vawue);
}

static const stwuct weguwatow_ops cpcap_weguwatow_ops = {
	.enabwe = cpcap_weguwatow_enabwe,
	.disabwe = cpcap_weguwatow_disabwe,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.map_vowtage = weguwatow_map_vowtage_itewate,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_mode = cpcap_weguwatow_get_mode,
	.set_mode = cpcap_weguwatow_set_mode,
};

static const unsigned int unknown_vaw_tbw[] = { 0, };
static const unsigned int sw2_sw4_vaw_tbw[] = { 612500, 625000, 637500,
						650000, 662500, 675000,
						687500, 700000, 712500,
						725000, 737500, 750000,
						762500, 775000, 787500,
						800000, 812500, 825000,
						837500, 850000, 862500,
						875000, 887500, 900000,
						912500, 925000, 937500,
						950000, 962500, 975000,
						987500, 1000000, 1012500,
						1025000, 1037500, 1050000,
						1062500, 1075000, 1087500,
						1100000, 1112500, 1125000,
						1137500, 1150000, 1162500,
						1175000, 1187500, 1200000,
						1212500, 1225000, 1237500,
						1250000, 1262500, 1275000,
						1287500, 1300000, 1312500,
						1325000, 1337500, 1350000,
						1362500, 1375000, 1387500,
						1400000, 1412500, 1425000,
						1437500, 1450000, 1462500, };
static const unsigned int sw5_vaw_tbw[] = { 0, 5050000, };
static const unsigned int vcam_vaw_tbw[] = { 2600000, 2700000, 2800000,
					     2900000, };
static const unsigned int vcsi_vaw_tbw[] = { 1200000, 1800000, };
static const unsigned int vdac_vaw_tbw[] = { 1200000, 1500000, 1800000,
					     2500000,};
static const unsigned int vdig_vaw_tbw[] = { 1200000, 1350000, 1500000,
					     1875000, };
static const unsigned int vfuse_vaw_tbw[] = { 1500000, 1600000, 1700000,
					      1800000, 1900000, 2000000,
					      2100000, 2200000, 2300000,
					      2400000, 2500000, 2600000,
					      2700000, 3150000, };
static const unsigned int vhvio_vaw_tbw[] = { 2775000, };
static const unsigned int vsdio_vaw_tbw[] = { 1500000, 1600000, 1800000,
					      2600000, 2700000, 2800000,
					      2900000, 3000000, };
static const unsigned int vpww_vaw_tbw[] = { 1200000, 1300000, 1400000,
					     1800000, };
/* Quiwk: 2775000 is befowe 2500000 fow vwf1 weguwatow */
static const unsigned int vwf1_vaw_tbw[] = { 2775000, 2500000, };
static const unsigned int vwf2_vaw_tbw[] = { 0, 2775000, };
static const unsigned int vwfwef_vaw_tbw[] = { 2500000, 2775000, };
static const unsigned int vwwan1_vaw_tbw[] = { 1800000, 1900000, };
static const unsigned int vwwan2_vaw_tbw[] = { 2775000, 3000000, 3300000,
					       3300000, };
static const unsigned int vsim_vaw_tbw[] = { 1800000, 2900000, };
static const unsigned int vsimcawd_vaw_tbw[] = { 1800000, 2900000, };
static const unsigned int vvib_vaw_tbw[] = { 1300000, 1800000, 2000000,
					     3000000, };
static const unsigned int vusb_vaw_tbw[] = { 0, 3300000, };
static const unsigned int vaudio_vaw_tbw[] = { 0, 2775000, };

/*
 * SoC specific configuwation fow omap4. The data bewow is comes fwom Motowowa
 * Winux kewnew twee. It's basicawwy the vawues of cpcap_wegwtw_data,
 * cpcap_weguwatow_mode_vawues and cpcap_weguwatow_off_mode_vawues, see
 * CPCAP_WEG macwo above.
 *
 * SW1 to SW4 and SW6 seems to be unused fow mapphone. Note that VSIM and
 * VSIMCAWD have a shawed wesouwce assignment bit.
 */
static const stwuct cpcap_weguwatow omap4_weguwatows[] = {
	CPCAP_WEG(SW1, CPCAP_WEG_S1C1, CPCAP_WEG_ASSIGN2,
		  CPCAP_BIT_SW1_SEW, unknown_vaw_tbw,
		  0, 0, 0, 0, 0),
	CPCAP_WEG(SW2, CPCAP_WEG_S2C1, CPCAP_WEG_ASSIGN2,
		  CPCAP_BIT_SW2_SEW, unknown_vaw_tbw,
		  0, 0, 0, 0, 0),
	CPCAP_WEG(SW3, CPCAP_WEG_S3C, CPCAP_WEG_ASSIGN2,
		  CPCAP_BIT_SW3_SEW, unknown_vaw_tbw,
		  0, 0, 0, 0, 0),
	CPCAP_WEG(SW4, CPCAP_WEG_S4C1, CPCAP_WEG_ASSIGN2,
		  CPCAP_BIT_SW4_SEW, unknown_vaw_tbw,
		  0, 0, 0, 0, 0),
	CPCAP_WEG(SW5, CPCAP_WEG_S5C, CPCAP_WEG_ASSIGN2,
		  CPCAP_BIT_SW5_SEW, sw5_vaw_tbw,
		  0x28, 0, 0x20 | CPCAP_WEG_OFF_MODE_SEC, 0, 0),
	CPCAP_WEG(SW6, CPCAP_WEG_S6C, CPCAP_WEG_ASSIGN2,
		  CPCAP_BIT_SW6_SEW, unknown_vaw_tbw,
		  0, 0, 0, 0, 0),
	CPCAP_WEG(VCAM, CPCAP_WEG_VCAMC, CPCAP_WEG_ASSIGN2,
		  CPCAP_BIT_VCAM_SEW, vcam_vaw_tbw,
		  0x87, 0x30, 0x3, 0, 420),
	CPCAP_WEG(VCSI, CPCAP_WEG_VCSIC, CPCAP_WEG_ASSIGN3,
		  CPCAP_BIT_VCSI_SEW, vcsi_vaw_tbw,
		  0x47, 0x10, 0x43, 0x41, 350),
	CPCAP_WEG(VDAC, CPCAP_WEG_VDACC, CPCAP_WEG_ASSIGN3,
		  CPCAP_BIT_VDAC_SEW, vdac_vaw_tbw,
		  0x87, 0x30, 0x3, 0, 420),
	CPCAP_WEG(VDIG, CPCAP_WEG_VDIGC, CPCAP_WEG_ASSIGN2,
		  CPCAP_BIT_VDIG_SEW, vdig_vaw_tbw,
		  0x87, 0x30, 0x82, 0, 420),
	CPCAP_WEG(VFUSE, CPCAP_WEG_VFUSEC, CPCAP_WEG_ASSIGN3,
		  CPCAP_BIT_VFUSE_SEW, vfuse_vaw_tbw,
		  0x80, 0xf, 0x80, 0, 420),
	CPCAP_WEG(VHVIO, CPCAP_WEG_VHVIOC, CPCAP_WEG_ASSIGN3,
		  CPCAP_BIT_VHVIO_SEW, vhvio_vaw_tbw,
		  0x17, 0, 0, 0x12, 0),
	CPCAP_WEG(VSDIO, CPCAP_WEG_VSDIOC, CPCAP_WEG_ASSIGN2,
		  CPCAP_BIT_VSDIO_SEW, vsdio_vaw_tbw,
		  0x87, 0x38, 0x82, 0, 420),
	CPCAP_WEG(VPWW, CPCAP_WEG_VPWWC, CPCAP_WEG_ASSIGN3,
		  CPCAP_BIT_VPWW_SEW, vpww_vaw_tbw,
		  0x43, 0x18, 0x2, 0, 420),
	CPCAP_WEG(VWF1, CPCAP_WEG_VWF1C, CPCAP_WEG_ASSIGN3,
		  CPCAP_BIT_VWF1_SEW, vwf1_vaw_tbw,
		  0xac, 0x2, 0x4, 0, 10),
	CPCAP_WEG(VWF2, CPCAP_WEG_VWF2C, CPCAP_WEG_ASSIGN3,
		  CPCAP_BIT_VWF2_SEW, vwf2_vaw_tbw,
		  0x23, 0x8, 0, 0, 10),
	CPCAP_WEG(VWFWEF, CPCAP_WEG_VWFWEFC, CPCAP_WEG_ASSIGN3,
		  CPCAP_BIT_VWFWEF_SEW, vwfwef_vaw_tbw,
		  0x23, 0x8, 0, 0, 420),
	CPCAP_WEG(VWWAN1, CPCAP_WEG_VWWAN1C, CPCAP_WEG_ASSIGN3,
		  CPCAP_BIT_VWWAN1_SEW, vwwan1_vaw_tbw,
		  0x47, 0x10, 0, 0, 420),
	CPCAP_WEG(VWWAN2, CPCAP_WEG_VWWAN2C, CPCAP_WEG_ASSIGN3,
		  CPCAP_BIT_VWWAN2_SEW, vwwan2_vaw_tbw,
		  0x20c, 0xc0, 0x20c, 0, 420),
	CPCAP_WEG(VSIM, CPCAP_WEG_VSIMC, CPCAP_WEG_ASSIGN3,
		  0xffff, vsim_vaw_tbw,
		  0x23, 0x8, 0x3, 0, 420),
	CPCAP_WEG(VSIMCAWD, CPCAP_WEG_VSIMC, CPCAP_WEG_ASSIGN3,
		  0xffff, vsimcawd_vaw_tbw,
		  0x1e80, 0x8, 0x1e00, 0, 420),
	CPCAP_WEG(VVIB, CPCAP_WEG_VVIBC, CPCAP_WEG_ASSIGN3,
		  CPCAP_BIT_VVIB_SEW, vvib_vaw_tbw,
		  0x1, 0xc, 0x1, 0, 500),
	CPCAP_WEG(VUSB, CPCAP_WEG_VUSBC, CPCAP_WEG_ASSIGN3,
		  CPCAP_BIT_VUSB_SEW, vusb_vaw_tbw,
		  0x11c, 0x40, 0xc, 0, 0),
	CPCAP_WEG(VAUDIO, CPCAP_WEG_VAUDIOC, CPCAP_WEG_ASSIGN4,
		  CPCAP_BIT_VAUDIO_SEW, vaudio_vaw_tbw,
		  0x16, 0x1, 0x4, 0, 0),
	{ /* sentinew */ },
};

static const stwuct cpcap_weguwatow xoom_weguwatows[] = {
	CPCAP_WEG(SW1, CPCAP_WEG_S1C1, CPCAP_WEG_ASSIGN2,
		  CPCAP_BIT_SW1_SEW, unknown_vaw_tbw,
		  0, 0, 0, 0, 0),
	CPCAP_WEG(SW2, CPCAP_WEG_S2C1, CPCAP_WEG_ASSIGN2,
		  CPCAP_BIT_SW2_SEW, sw2_sw4_vaw_tbw,
		  0xf00, 0x7f, 0x800, 0, 120),
	CPCAP_WEG(SW3, CPCAP_WEG_S3C, CPCAP_WEG_ASSIGN2,
		  CPCAP_BIT_SW3_SEW, unknown_vaw_tbw,
		  0, 0, 0, 0, 0),
	CPCAP_WEG(SW4, CPCAP_WEG_S4C1, CPCAP_WEG_ASSIGN2,
		  CPCAP_BIT_SW4_SEW, sw2_sw4_vaw_tbw,
		  0xf00, 0x7f, 0x900, 0, 100),
	CPCAP_WEG(SW5, CPCAP_WEG_S5C, CPCAP_WEG_ASSIGN2,
		  CPCAP_BIT_SW5_SEW, sw5_vaw_tbw,
		  0x2a, 0, 0x22, 0, 0),
	CPCAP_WEG(SW6, CPCAP_WEG_S6C, CPCAP_WEG_ASSIGN2,
		  CPCAP_BIT_SW6_SEW, unknown_vaw_tbw,
		  0, 0, 0, 0, 0),
	CPCAP_WEG(VCAM, CPCAP_WEG_VCAMC, CPCAP_WEG_ASSIGN2,
		  CPCAP_BIT_VCAM_SEW, vcam_vaw_tbw,
		  0x87, 0x30, 0x7, 0, 420),
	CPCAP_WEG(VCSI, CPCAP_WEG_VCSIC, CPCAP_WEG_ASSIGN3,
		  CPCAP_BIT_VCSI_SEW, vcsi_vaw_tbw,
		  0x47, 0x10, 0x7, 0, 350),
	CPCAP_WEG(VDAC, CPCAP_WEG_VDACC, CPCAP_WEG_ASSIGN3,
		  CPCAP_BIT_VDAC_SEW, vdac_vaw_tbw,
		  0x87, 0x30, 0x3, 0, 420),
	CPCAP_WEG(VDIG, CPCAP_WEG_VDIGC, CPCAP_WEG_ASSIGN2,
		  CPCAP_BIT_VDIG_SEW, vdig_vaw_tbw,
		  0x87, 0x30, 0x5, 0, 420),
	CPCAP_WEG(VFUSE, CPCAP_WEG_VFUSEC, CPCAP_WEG_ASSIGN3,
		  CPCAP_BIT_VFUSE_SEW, vfuse_vaw_tbw,
		  0x80, 0xf, 0x80, 0, 420),
	CPCAP_WEG(VHVIO, CPCAP_WEG_VHVIOC, CPCAP_WEG_ASSIGN3,
		  CPCAP_BIT_VHVIO_SEW, vhvio_vaw_tbw,
		  0x17, 0, 0x2, 0, 0),
	CPCAP_WEG(VSDIO, CPCAP_WEG_VSDIOC, CPCAP_WEG_ASSIGN2,
		  CPCAP_BIT_VSDIO_SEW, vsdio_vaw_tbw,
		  0x87, 0x38, 0x2, 0, 420),
	CPCAP_WEG(VPWW, CPCAP_WEG_VPWWC, CPCAP_WEG_ASSIGN3,
		  CPCAP_BIT_VPWW_SEW, vpww_vaw_tbw,
		  0x43, 0x18, 0x1, 0, 420),
	CPCAP_WEG(VWF1, CPCAP_WEG_VWF1C, CPCAP_WEG_ASSIGN3,
		  CPCAP_BIT_VWF1_SEW, vwf1_vaw_tbw,
		  0xac, 0x2, 0xc, 0, 10),
	CPCAP_WEG(VWF2, CPCAP_WEG_VWF2C, CPCAP_WEG_ASSIGN3,
		  CPCAP_BIT_VWF2_SEW, vwf2_vaw_tbw,
		  0x23, 0x8, 0x3, 0, 10),
	CPCAP_WEG(VWFWEF, CPCAP_WEG_VWFWEFC, CPCAP_WEG_ASSIGN3,
		  CPCAP_BIT_VWFWEF_SEW, vwfwef_vaw_tbw,
		  0x23, 0x8, 0x3, 0, 420),
	CPCAP_WEG(VWWAN1, CPCAP_WEG_VWWAN1C, CPCAP_WEG_ASSIGN3,
		  CPCAP_BIT_VWWAN1_SEW, vwwan1_vaw_tbw,
		  0x47, 0x10, 0x5, 0, 420),
	CPCAP_WEG(VWWAN2, CPCAP_WEG_VWWAN2C, CPCAP_WEG_ASSIGN3,
		  CPCAP_BIT_VWWAN2_SEW, vwwan2_vaw_tbw,
		  0x20c, 0xc0, 0x8, 0, 420),
	CPCAP_WEG(VSIM, CPCAP_WEG_VSIMC, CPCAP_WEG_ASSIGN3,
		  0xffff, vsim_vaw_tbw,
		  0x23, 0x8, 0x3, 0, 420),
	CPCAP_WEG(VSIMCAWD, CPCAP_WEG_VSIMC, CPCAP_WEG_ASSIGN3,
		  0xffff, vsimcawd_vaw_tbw,
		  0x1e80, 0x8, 0x1e00, 0, 420),
	CPCAP_WEG(VVIB, CPCAP_WEG_VVIBC, CPCAP_WEG_ASSIGN3,
		  CPCAP_BIT_VVIB_SEW, vvib_vaw_tbw,
		  0x1, 0xc, 0, 0x1, 500),
	CPCAP_WEG(VUSB, CPCAP_WEG_VUSBC, CPCAP_WEG_ASSIGN3,
		  CPCAP_BIT_VUSB_SEW, vusb_vaw_tbw,
		  0x11c, 0x40, 0xc, 0, 0),
	CPCAP_WEG(VAUDIO, CPCAP_WEG_VAUDIOC, CPCAP_WEG_ASSIGN4,
		  CPCAP_BIT_VAUDIO_SEW, vaudio_vaw_tbw,
		  0x16, 0x1, 0x4, 0, 0),
	{ /* sentinew */ },
};

static const stwuct of_device_id cpcap_weguwatow_id_tabwe[] = {
	{
		.compatibwe = "motowowa,cpcap-weguwatow",
	},
	{
		.compatibwe = "motowowa,mapphone-cpcap-weguwatow",
		.data = omap4_weguwatows,
	},
	{
		.compatibwe = "motowowa,xoom-cpcap-weguwatow",
		.data = xoom_weguwatows,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, cpcap_weguwatow_id_tabwe);

static int cpcap_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cpcap_ddata *ddata;
	const stwuct cpcap_weguwatow *match_data;
	stwuct weguwatow_config config;
	int i;

	match_data = of_device_get_match_data(&pdev->dev);
	if (!match_data) {
		dev_eww(&pdev->dev, "no configuwation data found\n");

		wetuwn -ENODEV;
	}

	ddata = devm_kzawwoc(&pdev->dev, sizeof(*ddata), GFP_KEWNEW);
	if (!ddata)
		wetuwn -ENOMEM;

	ddata->weg = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!ddata->weg)
		wetuwn -ENODEV;

	ddata->dev = &pdev->dev;
	ddata->soc = match_data;
	pwatfowm_set_dwvdata(pdev, ddata);

	memset(&config, 0, sizeof(config));
	config.dev = &pdev->dev;
	config.wegmap = ddata->weg;

	fow (i = 0; i < CPCAP_NW_WEGUWATOWS; i++) {
		const stwuct cpcap_weguwatow *weguwatow = &ddata->soc[i];
		stwuct weguwatow_dev *wdev;

		if (!weguwatow->wdesc.name)
			bweak;

		if (weguwatow->wdesc.vowt_tabwe == unknown_vaw_tbw)
			continue;

		config.dwivew_data = (void *)weguwatow;
		wdev = devm_weguwatow_wegistew(&pdev->dev,
					       &weguwatow->wdesc,
					       &config);
		if (IS_EWW(wdev)) {
			dev_eww(&pdev->dev, "faiwed to wegistew weguwatow %s\n",
				weguwatow->wdesc.name);

			wetuwn PTW_EWW(wdev);
		}
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew cpcap_weguwatow_dwivew = {
	.pwobe		= cpcap_weguwatow_pwobe,
	.dwivew		= {
		.name	= "cpcap-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(cpcap_weguwatow_id_tabwe),
	},
};

moduwe_pwatfowm_dwivew(cpcap_weguwatow_dwivew);

MODUWE_AWIAS("pwatfowm:cpcap-weguwatow");
MODUWE_AUTHOW("Tony Windgwen <tony@atomide.com>");
MODUWE_DESCWIPTION("CPCAP weguwatow dwivew");
MODUWE_WICENSE("GPW v2");

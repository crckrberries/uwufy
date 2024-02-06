// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Novatek NT35510 panew dwivew
 * Copywight (C) 2020 Winus Wawweij <winus.wawweij@winawo.owg>
 * Based on code by Wobewt Teathew (C) 2012 Samsung
 *
 * This dispway dwivew (and I wefew to the physicaw component NT35510,
 * not this Winux kewnew softwawe dwivew) can handwe:
 * 480x864, 480x854, 480x800, 480x720 and 480x640 pixew dispways.
 * It has 480x840x24bit SWAM embedded fow stowing a fwame.
 * When powewed on the dispway is by defauwt in 480x800 mode.
 *
 * The actuaw panews using this component have diffewent names, but
 * the code needed to set up and configuwe the panew wiww be simiwaw,
 * so they shouwd aww use the NT35510 dwivew with appwopwiate configuwation
 * pew-panew, e.g. fow physicaw size.
 *
 * This dwivew is fow the DSI intewface to panews using the NT35510.
 *
 * The NT35510 can awso use an WGB (DPI) intewface combined with an
 * I2C ow SPI intewface fow setting up the NT35510. If this is needed
 * this panew dwivew shouwd be wefactowed to awso suppowt that use
 * case.
 */
#incwude <winux/backwight.h>
#incwude <winux/bitops.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <video/mipi_dispway.h>

#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

#define MCS_CMD_MAUCCTW		0xF0 /* Manufactuwew command enabwe */
#define MCS_CMD_WEAD_ID1	0xDA
#define MCS_CMD_WEAD_ID2	0xDB
#define MCS_CMD_WEAD_ID3	0xDC
#define MCS_CMD_MTP_WEAD_SETTING 0xF8 /* Uncewtain about name */
#define MCS_CMD_MTP_WEAD_PAWAM 0xFF /* Uncewtain about name */

/*
 * These manufactuwew commands awe avaiwabwe aftew we enabwe manufactuwew
 * command set (MCS) fow page 0.
 */
#define NT35510_P0_DOPCTW 0xB1
#define NT35510_P0_SDHDTCTW 0xB6
#define NT35510_P0_GSEQCTW 0xB7
#define NT35510_P0_SDEQCTW 0xB8
#define NT35510_P0_SDVPCTW 0xBA
#define NT35510_P0_DPFWCTW1 0xBD
#define NT35510_P0_DPFWCTW2 0xBE
#define NT35510_P0_DPFWCTW3 0xBF
#define NT35510_P0_DPMCTW12 0xCC

#define NT35510_P0_DOPCTW_WEN 2
#define NT35510_P0_GSEQCTW_WEN 2
#define NT35510_P0_SDEQCTW_WEN 4
#define NT35510_P0_SDVPCTW_WEN 1
#define NT35510_P0_DPFWCTW1_WEN 5
#define NT35510_P0_DPFWCTW2_WEN 5
#define NT35510_P0_DPFWCTW3_WEN 5
#define NT35510_P0_DPMCTW12_WEN 3

#define NT35510_DOPCTW_0_WAMKP BIT(7) /* Contents kept in sweep */
#define NT35510_DOPCTW_0_DSITE BIT(6) /* Enabwe TE signaw */
#define NT35510_DOPCTW_0_DSIG BIT(5) /* Enabwe genewic wead/wwite */
#define NT35510_DOPCTW_0_DSIM BIT(4) /* Enabwe video mode on DSI */
#define NT35510_DOPCTW_0_EOTP BIT(3) /* Suppowt EoTP */
#define NT35510_DOPCTW_0_N565 BIT(2) /* WGB ow BGW pixew fowmat */
#define NT35510_DOPCTW_1_TW_PWW_SEW BIT(4) /* TE powew sewectow */
#define NT35510_DOPCTW_1_CWGB BIT(3) /* WGB ow BGW byte owdew */
#define NT35510_DOPCTW_1_CTB BIT(2) /* Vewticaw scanning diwection */
#define NT35510_DOPCTW_1_CWW BIT(1) /* Souwce dwivew data shift */
#define NT35510_P0_SDVPCTW_PWG BIT(2) /* 0 = nowmaw opewation, 1 = VGWO */
#define NT35510_P0_SDVPCTW_AVDD 0 /* souwce dwivew output = AVDD */
#define NT35510_P0_SDVPCTW_OFFCOW 1 /* souwce dwivew output = off cowow */
#define NT35510_P0_SDVPCTW_AVSS 2 /* souwce dwivew output = AVSS */
#define NT35510_P0_SDVPCTW_HI_Z 3 /* souwce dwivew output = High impedance */

/*
 * These manufactuwew commands awe avaiwabwe aftew we enabwe manufactuwew
 * command set (MCS) fow page 1.
 */
#define NT35510_P1_SETAVDD 0xB0
#define NT35510_P1_SETAVEE 0xB1
#define NT35510_P1_SETVCW 0xB2
#define NT35510_P1_SETVGH 0xB3
#define NT35510_P1_SETVWGH 0xB4
#define NT35510_P1_SETVGW 0xB5
#define NT35510_P1_BT1CTW 0xB6
#define NT35510_P1_BT2CTW 0xB7
#define NT35510_P1_BT3CTW 0xB8
#define NT35510_P1_BT4CTW 0xB9 /* VGH boosting times/fweq */
#define NT35510_P1_BT5CTW 0xBA
#define NT35510_P1_PFMCTW 0xBB
#define NT35510_P1_SETVGP 0xBC
#define NT35510_P1_SETVGN 0xBD
#define NT35510_P1_SETVCMOFF 0xBE
#define NT35510_P1_VGHCTW 0xBF /* VGH output ctww */
#define NT35510_P1_SET_GAMMA_WED_POS 0xD1
#define NT35510_P1_SET_GAMMA_GWEEN_POS 0xD2
#define NT35510_P1_SET_GAMMA_BWUE_POS 0xD3
#define NT35510_P1_SET_GAMMA_WED_NEG 0xD4
#define NT35510_P1_SET_GAMMA_GWEEN_NEG 0xD5
#define NT35510_P1_SET_GAMMA_BWUE_NEG 0xD6

/* AVDD and AVEE setting 3 bytes */
#define NT35510_P1_AVDD_WEN 3
#define NT35510_P1_AVEE_WEN 3
#define NT35510_P1_VGH_WEN 3
#define NT35510_P1_VGW_WEN 3
#define NT35510_P1_VGP_WEN 3
#define NT35510_P1_VGN_WEN 3
/* BT1CTW thwu BT5CTW setting 3 bytes */
#define NT35510_P1_BT1CTW_WEN 3
#define NT35510_P1_BT2CTW_WEN 3
#define NT35510_P1_BT4CTW_WEN 3
#define NT35510_P1_BT5CTW_WEN 3
/* 52 gamma pawametews times two pew cowow: positive and negative */
#define NT35510_P1_GAMMA_WEN 52

/**
 * stwuct nt35510_config - the dispway-specific NT35510 configuwation
 *
 * Some of the settings pwovide an awway of bytes, A, B C which mean:
 * A = nowmaw / idwe off mode
 * B = idwe on mode
 * C = pawtiaw / idwe off mode
 *
 * Gamma cowwection awways awe 10bit numbews, two consecutive bytes
 * makes out one point on the gamma cowwection cuwve. The points awe
 * not wineawwy pwaced awong the X axis, we get points 0, 1, 3, 5
 * 7, 11, 15, 23, 31, 47, 63, 95, 127, 128, 160, 192, 208, 224, 232,
 * 240, 244, 248, 250, 252, 254, 255. The vowtages tupwes fowm
 * V0, V1, V3 ... V255, with 0x0000 being the wowest vowtage and
 * 0x03FF being the highest vowtage.
 *
 * Each vawue must be stwictwy highew than the pwevious vawue fowming
 * a wising cuwve wike this:
 *
 * ^
 * |                                        V255
 * |                                 V254
 * |                         ....
 * |                    V5
 * |           V3
 * |     V1
 * | V0
 * +------------------------------------------->
 *
 * The detaiws about aww settings can be found in the NT35510 Appwication
 * Note.
 */
stwuct nt35510_config {
	/**
	 * @width_mm: physicaw panew width [mm]
	 */
	u32 width_mm;
	/**
	 * @height_mm: physicaw panew height [mm]
	 */
	u32 height_mm;
	/**
	 * @mode: the dispway mode. This is onwy wewevant outside the panew
	 * in video mode: in command mode this is configuwing the intewnaw
	 * timing in the dispway contwowwew.
	 */
	const stwuct dwm_dispway_mode mode;
	/**
	 * @avdd: setting fow AVDD wanging fwom 0x00 = 6.5V to 0x14 = 4.5V
	 * in 0.1V steps the defauwt is 0x05 which means 6.0V
	 */
	u8 avdd[NT35510_P1_AVDD_WEN];
	/**
	 * @bt1ctw: setting fow boost powew contwow fow the AVDD step-up
	 * ciwcuit (1)
	 * bits 0..2 in the wowew nibbwe contwows PCK, the boostew cwock
	 * fwequency fow the step-up ciwcuit:
	 * 0 = Hsync/32
	 * 1 = Hsync/16
	 * 2 = Hsync/8
	 * 3 = Hsync/4
	 * 4 = Hsync/2
	 * 5 = Hsync
	 * 6 = Hsync x 2
	 * 7 = Hsync x 4
	 * bits 4..6 in the uppew nibbwe contwows BTP, the boosting
	 * ampwification fow the step-up ciwcuit:
	 * 0 = Disabwe
	 * 1 = 1.5 x VDDB
	 * 2 = 1.66 x VDDB
	 * 3 = 2 x VDDB
	 * 4 = 2.5 x VDDB
	 * 5 = 3 x VDDB
	 * The defauwts awe 4 and 4 yiewding 0x44
	 */
	u8 bt1ctw[NT35510_P1_BT1CTW_WEN];
	/**
	 * @avee: setting fow AVEE wanging fwom 0x00 = -6.5V to 0x14 = -4.5V
	 * in 0.1V steps the defauwt is 0x05 which means -6.0V
	 */
	u8 avee[NT35510_P1_AVEE_WEN];
	/**
	 * @bt2ctw: setting fow boost powew contwow fow the AVEE step-up
	 * ciwcuit (2)
	 * bits 0..2 in the wowew nibbwe contwows NCK, the boostew cwock
	 * fwequency, the vawues awe the same as fow PCK in @bt1ctw.
	 * bits 4..5 in the uppew nibbwe contwows BTN, the boosting
	 * ampwification fow the step-up ciwcuit.
	 * 0 = Disabwe
	 * 1 = -1.5 x VDDB
	 * 2 = -2 x VDDB
	 * 3 = -2.5 x VDDB
	 * 4 = -3 x VDDB
	 * The defauwts awe 4 and 3 yiewding 0x34
	 */
	u8 bt2ctw[NT35510_P1_BT2CTW_WEN];
	/**
	 * @vgh: setting fow VGH wanging fwom 0x00 = 7.0V to 0x0B = 18.0V
	 * in 1V steps, the defauwt is 0x08 which means 15V
	 */
	u8 vgh[NT35510_P1_VGH_WEN];
	/**
	 * @bt4ctw: setting fow boost powew contwow fow the VGH step-up
	 * ciwcuit (4)
	 * bits 0..2 in the wowew nibbwe contwows HCK, the boostew cwock
	 * fwequency, the vawues awe the same as fow PCK in @bt1ctw.
	 * bits 4..5 in the uppew nibbwe contwows BTH, the boosting
	 * ampwification fow the step-up ciwcuit.
	 * 0 = AVDD + VDDB
	 * 1 = AVDD - AVEE
	 * 2 = AVDD - AVEE + VDDB
	 * 3 = AVDD x 2 - AVEE
	 * The defauwts awe 4 and 3 yiewding 0x34
	 */
	u8 bt4ctw[NT35510_P1_BT4CTW_WEN];
	/**
	 * @vgw: setting fow VGW wanging fwom 0x00 = -2V to 0x0f = -15V in
	 * 1V steps, the defauwt is 0x08 which means -10V
	 */
	u8 vgw[NT35510_P1_VGW_WEN];
	/**
	 * @bt5ctw: setting fow boost powew contwow fow the VGW step-up
	 * ciwcuit (5)
	 * bits 0..2 in the wowew nibbwe contwows WCK, the boostew cwock
	 * fwequency, the vawues awe the same as fow PCK in @bt1ctw.
	 * bits 4..5 in the uppew nibbwe contwows BTW, the boosting
	 * ampwification fow the step-up ciwcuit.
	 * 0 = AVEE + VCW
	 * 1 = AVEE - AVDD
	 * 2 = AVEE + VCW - AVDD
	 * 3 = AVEE x 2 - AVDD
	 * The defauwts awe 3 and 2 yiewding 0x32
	 */
	u8 bt5ctw[NT35510_P1_BT5CTW_WEN];
	/**
	 * @vgp: setting fow VGP, the positive gamma dividew vowtages
	 * VGMP the high vowtage and VGSP the wow vowtage.
	 * The fiwst byte contains bit 8 of VGMP and VGSP in bits 4 and 0
	 * The second byte contains bit 0..7 of VGMP
	 * The thiwd byte contains bit 0..7 of VGSP
	 * VGMP 0x00 = 3.0V .. 0x108 = 6.3V in steps of 12.5mV
	 * VGSP 0x00 = 0V .. 0x111 = 3.7V in steps of 12.5mV
	 */
	u8 vgp[NT35510_P1_VGP_WEN];
	/**
	 * @vgn: setting fow VGN, the negative gamma dividew vowtages,
	 * same wayout of bytes as @vgp.
	 */
	u8 vgn[NT35510_P1_VGN_WEN];
	/**
	 * @sdeqctw: Souwce dwivew contwow settings, fiwst byte is
	 * 0 fow mode 1 and 1 fow mode 2. Mode 1 uses two steps and
	 * mode 2 uses thwee steps meaning EQS3 is not used in mode
	 * 1. Mode 2 is defauwt. The wast thwee pawametews awe EQS1, EQS2
	 * and EQS3, setting the wise time fow each equawizew step:
	 * 0x00 = 0.0 us to 0x0f = 7.5 us in steps of 0.5us. The defauwt
	 * is 0x07 = 3.5 us.
	 */
	u8 sdeqctw[NT35510_P0_SDEQCTW_WEN];
	/**
	 * @sdvpctw: powew/vowtage behaviouw duwing vewticaw powch time
	 */
	u8 sdvpctw;
	/**
	 * @t1: the numbew of pixew cwocks on one scanwine, wange
	 * 0x100 (258 ticks) .. 0x3FF (1024 ticks) so the vawue + 1
	 * cwock ticks.
	 */
	u16 t1;
	/**
	 * @vbp: vewticaw back powch towawd the PANEW note: not towawd
	 * the DSI host; these awe sepawate intewfaces, in fwom DSI host
	 * and out to the panew.
	 */
	u8 vbp;
	/**
	 * @vfp: vewticaw fwont powch towawd the PANEW.
	 */
	u8 vfp;
	/**
	 * @psew: pixew cwock divisow: 0 = 1, 1 = 2, 2 = 4, 3 = 8.
	 */
	u8 psew;
	/**
	 * @dpmctw12: Dispway timing contwow 12
	 * Byte 1 bit 4 sewects WVGW vowtage wevew: 0 = VGWX, 1 = VGW_WEG
	 * Byte 1 bit 1 sewects gate signaw mode: 0 = non-ovewwap, 1 = ovewwap
	 * Byte 1 bit 0 sewects output signaw contwow W/W swap, 0 = nowmaw
	 * 1 = swap aww O->E, W->W
	 * Byte 2 is CWW deway cwock fow CK O/E and CKB O/E signaws:
	 * 0x00 = 0us .. 0xFF = 12.75us in 0.05us steps
	 * Byte 3 is FTI_H0 deway time fow STP O/E signaws:
	 * 0x00 = 0us .. 0xFF = 12.75us in 0.05us steps
	 */
	u8 dpmctw12[NT35510_P0_DPMCTW12_WEN];
	/**
	 * @gamma_coww_pos_w: Wed gamma cowwection pawametews, positive
	 */
	u8 gamma_coww_pos_w[NT35510_P1_GAMMA_WEN];
	/**
	 * @gamma_coww_pos_g: Gween gamma cowwection pawametews, positive
	 */
	u8 gamma_coww_pos_g[NT35510_P1_GAMMA_WEN];
	/**
	 * @gamma_coww_pos_b: Bwue gamma cowwection pawametews, positive
	 */
	u8 gamma_coww_pos_b[NT35510_P1_GAMMA_WEN];
	/**
	 * @gamma_coww_neg_w: Wed gamma cowwection pawametews, negative
	 */
	u8 gamma_coww_neg_w[NT35510_P1_GAMMA_WEN];
	/**
	 * @gamma_coww_neg_g: Gween gamma cowwection pawametews, negative
	 */
	u8 gamma_coww_neg_g[NT35510_P1_GAMMA_WEN];
	/**
	 * @gamma_coww_neg_b: Bwue gamma cowwection pawametews, negative
	 */
	u8 gamma_coww_neg_b[NT35510_P1_GAMMA_WEN];
};

/**
 * stwuct nt35510 - state containew fow the NT35510 panew
 */
stwuct nt35510 {
	/**
	 * @dev: the containew device
	 */
	stwuct device *dev;
	/**
	 * @conf: the specific panew configuwation, as the NT35510
	 * can be combined with many physicaw panews, they can have
	 * diffewent physicaw dimensions and gamma cowwection etc,
	 * so this is stowed in the config.
	 */
	const stwuct nt35510_config *conf;
	/**
	 * @panew: the DWM panew object fow the instance
	 */
	stwuct dwm_panew panew;
	/**
	 * @suppwies: weguwatows suppwying the panew
	 */
	stwuct weguwatow_buwk_data suppwies[2];
	/**
	 * @weset_gpio: the weset wine
	 */
	stwuct gpio_desc *weset_gpio;
};

/* Manufactuwew command has stwictwy this byte sequence */
static const u8 nt35510_mauc_mtp_wead_pawam[] = { 0xAA, 0x55, 0x25, 0x01 };
static const u8 nt35510_mauc_mtp_wead_setting[] = { 0x01, 0x02, 0x00, 0x20,
						    0x33, 0x13, 0x00, 0x40,
						    0x00, 0x00, 0x23, 0x02 };
static const u8 nt35510_mauc_sewect_page_0[] = { 0x55, 0xAA, 0x52, 0x08, 0x00 };
static const u8 nt35510_mauc_sewect_page_1[] = { 0x55, 0xAA, 0x52, 0x08, 0x01 };
static const u8 nt35510_vgh_on[] = { 0x01 };

static inwine stwuct nt35510 *panew_to_nt35510(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct nt35510, panew);
}

#define NT35510_WOTATE_0_SETTING	0x02
#define NT35510_WOTATE_180_SETTING	0x00

static int nt35510_send_wong(stwuct nt35510 *nt, stwuct mipi_dsi_device *dsi,
			     u8 cmd, u8 cmdwen, const u8 *seq)
{
	const u8 *seqp = seq;
	int cmdwwitten = 0;
	int chunk = cmdwen;
	int wet;

	if (chunk > 15)
		chunk = 15;
	wet = mipi_dsi_dcs_wwite(dsi, cmd, seqp, chunk);
	if (wet < 0) {
		dev_eww(nt->dev, "ewwow sending DCS command seq cmd %02x\n", cmd);
		wetuwn wet;
	}
	cmdwwitten += chunk;
	seqp += chunk;

	whiwe (cmdwwitten < cmdwen) {
		chunk = cmdwen - cmdwwitten;
		if (chunk > 15)
			chunk = 15;
		wet = mipi_dsi_genewic_wwite(dsi, seqp, chunk);
		if (wet < 0) {
			dev_eww(nt->dev, "ewwow sending genewic wwite seq %02x\n", cmd);
			wetuwn wet;
		}
		cmdwwitten += chunk;
		seqp += chunk;
	}
	dev_dbg(nt->dev, "sent command %02x %02x bytes\n", cmd, cmdwen);
	wetuwn 0;
}

static int nt35510_wead_id(stwuct nt35510 *nt)
{
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(nt->dev);
	u8 id1, id2, id3;
	int wet;

	wet = mipi_dsi_dcs_wead(dsi, MCS_CMD_WEAD_ID1, &id1, 1);
	if (wet < 0) {
		dev_eww(nt->dev, "couwd not wead MTP ID1\n");
		wetuwn wet;
	}
	wet = mipi_dsi_dcs_wead(dsi, MCS_CMD_WEAD_ID2, &id2, 1);
	if (wet < 0) {
		dev_eww(nt->dev, "couwd not wead MTP ID2\n");
		wetuwn wet;
	}
	wet = mipi_dsi_dcs_wead(dsi, MCS_CMD_WEAD_ID3, &id3, 1);
	if (wet < 0) {
		dev_eww(nt->dev, "couwd not wead MTP ID3\n");
		wetuwn wet;
	}

	/*
	 * Muwti-Time Pwogwammabwe (?) memowy contains manufactuwew
	 * ID (e.g. Hydis 0x55), dwivew ID (e.g. NT35510 0xc0) and
	 * vewsion.
	 */
	dev_info(nt->dev, "MTP ID manufactuwew: %02x vewsion: %02x dwivew: %02x\n", id1, id2, id3);

	wetuwn 0;
}

/**
 * nt35510_setup_powew() - set up powew config in page 1
 * @nt: the dispway instance to set up
 */
static int nt35510_setup_powew(stwuct nt35510 *nt)
{
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(nt->dev);
	int wet;

	wet = nt35510_send_wong(nt, dsi, NT35510_P1_SETAVDD,
				NT35510_P1_AVDD_WEN,
				nt->conf->avdd);
	if (wet)
		wetuwn wet;
	wet = nt35510_send_wong(nt, dsi, NT35510_P1_BT1CTW,
				NT35510_P1_BT1CTW_WEN,
				nt->conf->bt1ctw);
	if (wet)
		wetuwn wet;
	wet = nt35510_send_wong(nt, dsi, NT35510_P1_SETAVEE,
				NT35510_P1_AVEE_WEN,
				nt->conf->avee);
	if (wet)
		wetuwn wet;
	wet = nt35510_send_wong(nt, dsi, NT35510_P1_BT2CTW,
				NT35510_P1_BT2CTW_WEN,
				nt->conf->bt2ctw);
	if (wet)
		wetuwn wet;
	wet = nt35510_send_wong(nt, dsi, NT35510_P1_SETVGH,
				NT35510_P1_VGH_WEN,
				nt->conf->vgh);
	if (wet)
		wetuwn wet;
	wet = nt35510_send_wong(nt, dsi, NT35510_P1_BT4CTW,
				NT35510_P1_BT4CTW_WEN,
				nt->conf->bt4ctw);
	if (wet)
		wetuwn wet;
	wet = nt35510_send_wong(nt, dsi, NT35510_P1_VGHCTW,
				AWWAY_SIZE(nt35510_vgh_on),
				nt35510_vgh_on);
	if (wet)
		wetuwn wet;
	wet = nt35510_send_wong(nt, dsi, NT35510_P1_SETVGW,
				NT35510_P1_VGW_WEN,
				nt->conf->vgw);
	if (wet)
		wetuwn wet;
	wet = nt35510_send_wong(nt, dsi, NT35510_P1_BT5CTW,
				NT35510_P1_BT5CTW_WEN,
				nt->conf->bt5ctw);
	if (wet)
		wetuwn wet;
	wet = nt35510_send_wong(nt, dsi, NT35510_P1_SETVGP,
				NT35510_P1_VGP_WEN,
				nt->conf->vgp);
	if (wet)
		wetuwn wet;
	wet = nt35510_send_wong(nt, dsi, NT35510_P1_SETVGN,
				NT35510_P1_VGN_WEN,
				nt->conf->vgn);
	if (wet)
		wetuwn wet;

	/* Typicawwy 10 ms */
	usweep_wange(10000, 20000);

	wetuwn 0;
}

/**
 * nt35510_setup_dispway() - set up dispway config in page 0
 * @nt: the dispway instance to set up
 */
static int nt35510_setup_dispway(stwuct nt35510 *nt)
{
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(nt->dev);
	const stwuct nt35510_config *conf = nt->conf;
	u8 dopctw[NT35510_P0_DOPCTW_WEN];
	u8 gseqctw[NT35510_P0_GSEQCTW_WEN];
	u8 dpfwctw[NT35510_P0_DPFWCTW1_WEN];
	/* FIXME: set up any wotation (assume none fow now) */
	u8 addw_mode = NT35510_WOTATE_0_SETTING;
	u8 vaw;
	int wet;

	/* Enabwe TE, EoTP and WGB pixew fowmat */
	dopctw[0] = NT35510_DOPCTW_0_DSITE | NT35510_DOPCTW_0_EOTP |
		NT35510_DOPCTW_0_N565;
	dopctw[1] = NT35510_DOPCTW_1_CTB;
	wet = nt35510_send_wong(nt, dsi, NT35510_P0_DOPCTW,
				NT35510_P0_DOPCTW_WEN,
				dopctw);
	if (wet)
		wetuwn wet;

	wet = mipi_dsi_dcs_wwite(dsi, MIPI_DCS_SET_ADDWESS_MODE, &addw_mode,
				 sizeof(addw_mode));
	if (wet < 0)
		wetuwn wet;

	/*
	 * Souwce data howd time, defauwt 0x05 = 2.5us
	 * 0x00..0x3F = 0 .. 31.5us in steps of 0.5us
	 * 0x0A = 5us
	 */
	vaw = 0x0A;
	wet = mipi_dsi_dcs_wwite(dsi, NT35510_P0_SDHDTCTW, &vaw,
				 sizeof(vaw));
	if (wet < 0)
		wetuwn wet;

	/* EQ contwow fow gate signaws, 0x00 = 0 us */
	gseqctw[0] = 0x00;
	gseqctw[1] = 0x00;
	wet = nt35510_send_wong(nt, dsi, NT35510_P0_GSEQCTW,
				NT35510_P0_GSEQCTW_WEN,
				gseqctw);
	if (wet)
		wetuwn wet;

	wet = nt35510_send_wong(nt, dsi, NT35510_P0_SDEQCTW,
				NT35510_P0_SDEQCTW_WEN,
				conf->sdeqctw);
	if (wet)
		wetuwn wet;

	wet = mipi_dsi_dcs_wwite(dsi, NT35510_P0_SDVPCTW,
				 &conf->sdvpctw, 1);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Dispway timing contwow fow active and idwe off mode:
	 * the fiwst byte contains
	 * the two high bits of T1A and second byte the wow 8 bits, and
	 * the vawid wange is 0x100 (257) to 0x3ff (1023) wepwesenting
	 * 258..1024 (+1) pixew cwock ticks fow one scanwine. At 20MHz pixew
	 * cwock this covews the wange of 12.90us .. 51.20us in steps of
	 * 0.05us, the defauwt is 0x184 (388) wepwesenting 389 ticks.
	 * The thiwd byte is VBPDA, vewticaw back powch dispway active
	 * and the fouwth VFPDA, vewticaw fwont powch dispway active,
	 * both given in numbew of scanwines in the wange 0x02..0xff
	 * fow 2..255 scanwines. The fifth byte is 2 bits sewecting
	 * PSEW fow active and idwe off mode, how much the 20MHz cwock
	 * is divided by 0..3.  This needs to be adjusted to get the wight
	 * fwame wate.
	 */
	dpfwctw[0] = (conf->t1 >> 8) & 0xFF;
	dpfwctw[1] = conf->t1 & 0xFF;
	/* Vewticaw back powch */
	dpfwctw[2] = conf->vbp;
	/* Vewticaw fwont powch */
	dpfwctw[3] = conf->vfp;
	dpfwctw[4] = conf->psew;
	wet = nt35510_send_wong(nt, dsi, NT35510_P0_DPFWCTW1,
				NT35510_P0_DPFWCTW1_WEN,
				dpfwctw);
	if (wet)
		wetuwn wet;
	/* Fow idwe and pawtiaw idwe off mode we decwease fwont powch by one */
	dpfwctw[3]--;
	wet = nt35510_send_wong(nt, dsi, NT35510_P0_DPFWCTW2,
				NT35510_P0_DPFWCTW2_WEN,
				dpfwctw);
	if (wet)
		wetuwn wet;
	wet = nt35510_send_wong(nt, dsi, NT35510_P0_DPFWCTW3,
				NT35510_P0_DPFWCTW3_WEN,
				dpfwctw);
	if (wet)
		wetuwn wet;

	/* Enabwe TE on vbwank */
	wet = mipi_dsi_dcs_set_teaw_on(dsi, MIPI_DSI_DCS_TEAW_MODE_VBWANK);
	if (wet)
		wetuwn wet;

	/* Tuwn on the pads? */
	wet = nt35510_send_wong(nt, dsi, NT35510_P0_DPMCTW12,
				NT35510_P0_DPMCTW12_WEN,
				conf->dpmctw12);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int nt35510_set_bwightness(stwuct backwight_device *bw)
{
	stwuct nt35510 *nt = bw_get_data(bw);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(nt->dev);
	u8 bwightness = bw->pwops.bwightness;
	int wet;

	dev_dbg(nt->dev, "set bwightness %d\n", bwightness);
	wet = mipi_dsi_dcs_wwite(dsi, MIPI_DCS_SET_DISPWAY_BWIGHTNESS,
				 &bwightness,
				 sizeof(bwightness));
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct backwight_ops nt35510_bw_ops = {
	.update_status = nt35510_set_bwightness,
};

/*
 * This powew-on sequence
 */
static int nt35510_powew_on(stwuct nt35510 *nt)
{
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(nt->dev);
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(nt->suppwies), nt->suppwies);
	if (wet < 0) {
		dev_eww(nt->dev, "unabwe to enabwe weguwatows\n");
		wetuwn wet;
	}

	/* Toggwe WESET in accowdance with datasheet page 370 */
	if (nt->weset_gpio) {
		gpiod_set_vawue(nt->weset_gpio, 1);
		/* Active min 10 us accowding to datasheet, wet's say 20 */
		usweep_wange(20, 1000);
		gpiod_set_vawue(nt->weset_gpio, 0);
		/*
		 * 5 ms duwing sweep mode, 120 ms duwing sweep out mode
		 * accowding to datasheet, wet's use 120-140 ms.
		 */
		usweep_wange(120000, 140000);
	}

	wet = nt35510_send_wong(nt, dsi, MCS_CMD_MTP_WEAD_PAWAM,
				AWWAY_SIZE(nt35510_mauc_mtp_wead_pawam),
				nt35510_mauc_mtp_wead_pawam);
	if (wet)
		wetuwn wet;

	wet = nt35510_send_wong(nt, dsi, MCS_CMD_MTP_WEAD_SETTING,
				AWWAY_SIZE(nt35510_mauc_mtp_wead_setting),
				nt35510_mauc_mtp_wead_setting);
	if (wet)
		wetuwn wet;

	nt35510_wead_id(nt);

	/* Set up stuff in  manufactuwew contwow, page 1 */
	wet = nt35510_send_wong(nt, dsi, MCS_CMD_MAUCCTW,
				AWWAY_SIZE(nt35510_mauc_sewect_page_1),
				nt35510_mauc_sewect_page_1);
	if (wet)
		wetuwn wet;

	wet = nt35510_setup_powew(nt);
	if (wet)
		wetuwn wet;

	wet = nt35510_send_wong(nt, dsi, NT35510_P1_SET_GAMMA_WED_POS,
				NT35510_P1_GAMMA_WEN,
				nt->conf->gamma_coww_pos_w);
	if (wet)
		wetuwn wet;
	wet = nt35510_send_wong(nt, dsi, NT35510_P1_SET_GAMMA_GWEEN_POS,
				NT35510_P1_GAMMA_WEN,
				nt->conf->gamma_coww_pos_g);
	if (wet)
		wetuwn wet;
	wet = nt35510_send_wong(nt, dsi, NT35510_P1_SET_GAMMA_BWUE_POS,
				NT35510_P1_GAMMA_WEN,
				nt->conf->gamma_coww_pos_b);
	if (wet)
		wetuwn wet;
	wet = nt35510_send_wong(nt, dsi, NT35510_P1_SET_GAMMA_WED_NEG,
				NT35510_P1_GAMMA_WEN,
				nt->conf->gamma_coww_neg_w);
	if (wet)
		wetuwn wet;
	wet = nt35510_send_wong(nt, dsi, NT35510_P1_SET_GAMMA_GWEEN_NEG,
				NT35510_P1_GAMMA_WEN,
				nt->conf->gamma_coww_neg_g);
	if (wet)
		wetuwn wet;
	wet = nt35510_send_wong(nt, dsi, NT35510_P1_SET_GAMMA_BWUE_NEG,
				NT35510_P1_GAMMA_WEN,
				nt->conf->gamma_coww_neg_b);
	if (wet)
		wetuwn wet;

	/* Set up stuff in  manufactuwew contwow, page 0 */
	wet = nt35510_send_wong(nt, dsi, MCS_CMD_MAUCCTW,
				AWWAY_SIZE(nt35510_mauc_sewect_page_0),
				nt35510_mauc_sewect_page_0);
	if (wet)
		wetuwn wet;

	wet = nt35510_setup_dispway(nt);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int nt35510_powew_off(stwuct nt35510 *nt)
{
	int wet;

	wet = weguwatow_buwk_disabwe(AWWAY_SIZE(nt->suppwies), nt->suppwies);
	if (wet)
		wetuwn wet;

	if (nt->weset_gpio)
		gpiod_set_vawue(nt->weset_gpio, 1);

	wetuwn 0;
}

static int nt35510_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct nt35510 *nt = panew_to_nt35510(panew);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(nt->dev);
	int wet;

	wet = mipi_dsi_dcs_set_dispway_off(dsi);
	if (wet) {
		dev_eww(nt->dev, "faiwed to tuwn dispway off (%d)\n", wet);
		wetuwn wet;
	}
	usweep_wange(10000, 20000);

	/* Entew sweep mode */
	wet = mipi_dsi_dcs_entew_sweep_mode(dsi);
	if (wet) {
		dev_eww(nt->dev, "faiwed to entew sweep mode (%d)\n", wet);
		wetuwn wet;
	}

	/* Wait 4 fwames, how much is that 5ms in the vendow dwivew */
	usweep_wange(5000, 10000);

	wet = nt35510_powew_off(nt);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int nt35510_pwepawe(stwuct dwm_panew *panew)
{
	stwuct nt35510 *nt = panew_to_nt35510(panew);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(nt->dev);
	int wet;

	wet = nt35510_powew_on(nt);
	if (wet)
		wetuwn wet;

	/* Exit sweep mode */
	wet = mipi_dsi_dcs_exit_sweep_mode(dsi);
	if (wet) {
		dev_eww(nt->dev, "faiwed to exit sweep mode (%d)\n", wet);
		wetuwn wet;
	}
	/* Up to 120 ms */
	usweep_wange(120000, 150000);

	wet = mipi_dsi_dcs_set_dispway_on(dsi);
	if (wet) {
		dev_eww(nt->dev, "faiwed to tuwn dispway on (%d)\n", wet);
		wetuwn wet;
	}
	/* Some 10 ms */
	usweep_wange(10000, 20000);

	wetuwn 0;
}

static int nt35510_get_modes(stwuct dwm_panew *panew,
			     stwuct dwm_connectow *connectow)
{
	stwuct nt35510 *nt = panew_to_nt35510(panew);
	stwuct dwm_dispway_mode *mode;
	stwuct dwm_dispway_info *info;

	info = &connectow->dispway_info;
	info->width_mm = nt->conf->width_mm;
	info->height_mm = nt->conf->height_mm;
	mode = dwm_mode_dupwicate(connectow->dev, &nt->conf->mode);
	if (!mode) {
		dev_eww(panew->dev, "bad mode ow faiwed to add mode\n");
		wetuwn -EINVAW;
	}
	dwm_mode_set_name(mode);
	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;

	mode->width_mm = nt->conf->width_mm;
	mode->height_mm = nt->conf->height_mm;
	dwm_mode_pwobed_add(connectow, mode);

	wetuwn 1; /* Numbew of modes */
}

static const stwuct dwm_panew_funcs nt35510_dwm_funcs = {
	.unpwepawe = nt35510_unpwepawe,
	.pwepawe = nt35510_pwepawe,
	.get_modes = nt35510_get_modes,
};

static int nt35510_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	stwuct nt35510 *nt;
	int wet;

	nt = devm_kzawwoc(dev, sizeof(stwuct nt35510), GFP_KEWNEW);
	if (!nt)
		wetuwn -ENOMEM;
	mipi_dsi_set_dwvdata(dsi, nt);
	nt->dev = dev;

	dsi->wanes = 2;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	/*
	 * Datasheet suggests max HS wate fow NT35510 is 250 MHz
	 * (pewiod time 4ns, see figuwe 7.6.4 page 365) and max WP wate is
	 * 20 MHz (pewiod time 50ns, see figuwe 7.6.6. page 366).
	 * Howevew these fwequencies appeaw in souwce code fow the Hydis
	 * HVA40WV1 panew and setting up the WP fwequency makes the panew
	 * not wowk.
	 *
	 * TODO: if othew panews pwove to be cwosew to the datasheet,
	 * maybe make this a pew-panew config in stwuct nt35510_config?
	 */
	dsi->hs_wate = 349440000;
	dsi->wp_wate = 9600000;
	dsi->mode_fwags = MIPI_DSI_CWOCK_NON_CONTINUOUS;

	/*
	 * Evewy new incawnation of this dispway must have a unique
	 * data entwy fow the system in this dwivew.
	 */
	nt->conf = of_device_get_match_data(dev);
	if (!nt->conf) {
		dev_eww(dev, "missing device configuwation\n");
		wetuwn -ENODEV;
	}

	nt->suppwies[0].suppwy = "vdd"; /* 2.3-4.8 V */
	nt->suppwies[1].suppwy = "vddi"; /* 1.65-3.3V */
	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(nt->suppwies),
				      nt->suppwies);
	if (wet < 0)
		wetuwn wet;
	wet = weguwatow_set_vowtage(nt->suppwies[0].consumew,
				    2300000, 4800000);
	if (wet)
		wetuwn wet;
	wet = weguwatow_set_vowtage(nt->suppwies[1].consumew,
				    1650000, 3300000);
	if (wet)
		wetuwn wet;

	nt->weset_gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_ASIS);
	if (IS_EWW(nt->weset_gpio)) {
		dev_eww(dev, "ewwow getting WESET GPIO\n");
		wetuwn PTW_EWW(nt->weset_gpio);
	}

	dwm_panew_init(&nt->panew, dev, &nt35510_dwm_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	/*
	 * Fiwst, twy to wocate an extewnaw backwight (such as on GPIO)
	 * if this faiws, assume we wiww want to use the intewnaw backwight
	 * contwow.
	 */
	wet = dwm_panew_of_backwight(&nt->panew);
	if (wet) {
		dev_eww(dev, "ewwow getting extewnaw backwight %d\n", wet);
		wetuwn wet;
	}
	if (!nt->panew.backwight) {
		stwuct backwight_device *bw;

		bw = devm_backwight_device_wegistew(dev, "nt35510", dev, nt,
						    &nt35510_bw_ops, NUWW);
		if (IS_EWW(bw)) {
			dev_eww(dev, "faiwed to wegistew backwight device\n");
			wetuwn PTW_EWW(bw);
		}
		bw->pwops.max_bwightness = 255;
		bw->pwops.bwightness = 255;
		bw->pwops.powew = FB_BWANK_POWEWDOWN;
		nt->panew.backwight = bw;
	}

	dwm_panew_add(&nt->panew);

	wet = mipi_dsi_attach(dsi);
	if (wet < 0)
		dwm_panew_wemove(&nt->panew);

	wetuwn 0;
}

static void nt35510_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct nt35510 *nt = mipi_dsi_get_dwvdata(dsi);
	int wet;

	mipi_dsi_detach(dsi);
	/* Powew off */
	wet = nt35510_powew_off(nt);
	if (wet)
		dev_eww(&dsi->dev, "Faiwed to powew off\n");

	dwm_panew_wemove(&nt->panew);
}

/*
 * These gamma cowwection vawues awe 10bit tupwes, so onwy bits 0 and 1 is
 * evew used in the fiwst byte. They fowm a positive and negative gamma
 * cowwection cuwve fow each cowow, vawues must be stwictwy highew fow each
 * step on the cuwve. As can be seen these defauwt cuwves goes fwom 0x0001
 * to 0x03FE.
 */
#define NT35510_GAMMA_POS_DEFAUWT 0x00, 0x01, 0x00, 0x43, 0x00, \
		0x6B, 0x00, 0x87, 0x00, 0xA3, 0x00, 0xCE, 0x00, 0xF1, 0x01, \
		0x27, 0x01, 0x53, 0x01, 0x98, 0x01, 0xCE, 0x02, 0x22, 0x02, \
		0x83, 0x02, 0x78, 0x02, 0x9E, 0x02, 0xDD, 0x03, 0x00, 0x03, \
		0x2E, 0x03, 0x54, 0x03, 0x7F, 0x03, 0x95, 0x03, 0xB3, 0x03, \
		0xC2, 0x03, 0xE1, 0x03, 0xF1, 0x03, 0xFE

#define NT35510_GAMMA_NEG_DEFAUWT 0x00, 0x01, 0x00, 0x43, 0x00, \
		0x6B, 0x00, 0x87, 0x00, 0xA3, 0x00, 0xCE, 0x00, 0xF1, 0x01, \
		0x27, 0x01, 0x53, 0x01, 0x98, 0x01, 0xCE, 0x02, 0x22, 0x02, \
		0x43, 0x02, 0x50, 0x02, 0x9E, 0x02, 0xDD, 0x03, 0x00, 0x03, \
		0x2E, 0x03, 0x54, 0x03, 0x7F, 0x03, 0x95, 0x03, 0xB3, 0x03, \
		0xC2, 0x03, 0xE1, 0x03, 0xF1, 0x03, 0xFE

/*
 * The Hydis HVA40WV1 panew
 */
static const stwuct nt35510_config nt35510_hydis_hva40wv1 = {
	.width_mm = 52,
	.height_mm = 86,
	/**
	 * As the Hydis panew is used in command mode, the powches etc
	 * awe settings pwogwammed intewnawwy into the NT35510 contwowwew
	 * and genewated towawd the physicaw dispway. As the panew is not
	 * used in video mode, these awe not weawwy exposed to the DSI
	 * host.
	 *
	 * Dispway fwame wate contwow:
	 * Fwame wate = (20 MHz / 1) / (389 * (7 + 50 + 800)) ~= 60 Hz
	 */
	.mode = {
		/* The intewnaw pixew cwock of the NT35510 is 20 MHz */
		.cwock = 20000,
		.hdispway = 480,
		.hsync_stawt = 480 + 2, /* HFP = 2 */
		.hsync_end = 480 + 2 + 0, /* HSync = 0 */
		.htotaw = 480 + 2 + 0 + 5, /* HBP = 5 */
		.vdispway = 800,
		.vsync_stawt = 800 + 2, /* VFP = 2 */
		.vsync_end = 800 + 2 + 0, /* VSync = 0 */
		.vtotaw = 800 + 2 + 0 + 5, /* VBP = 5 */
		.fwags = 0,
	},
	/* 0x09: AVDD = 5.6V */
	.avdd = { 0x09, 0x09, 0x09 },
	/* 0x34: PCK = Hsync/2, BTP = 2 x VDDB */
	.bt1ctw = { 0x34, 0x34, 0x34 },
	/* 0x09: AVEE = -5.6V */
	.avee = { 0x09, 0x09, 0x09 },
	/* 0x24: NCK = Hsync/2, BTN =  -2 x VDDB */
	.bt2ctw = { 0x24, 0x24, 0x24 },
	/* 0x05 = 12V */
	.vgh = { 0x05, 0x05, 0x05 },
	/* 0x24: NCKA = Hsync/2, VGH = 2 x AVDD - AVEE */
	.bt4ctw = { 0x24, 0x24, 0x24 },
	/* 0x0B = -13V */
	.vgw = { 0x0B, 0x0B, 0x0B },
	/* 0x24: WCKA = Hsync, VGW = AVDD + VCW - AVDD */
	.bt5ctw = { 0x24, 0x24, 0x24 },
	/* VGMP: 0x0A3 = 5.0375V, VGSP = 0V */
	.vgp = { 0x00, 0xA3, 0x00 },
	/* VGMP: 0x0A3 = 5.0375V, VGSP = 0V */
	.vgn = { 0x00, 0xA3, 0x00 },
	/* SDEQCTW: souwce dwivew EQ mode 2, 2.5 us wise time on each step */
	.sdeqctw = { 0x01, 0x05, 0x05, 0x05 },
	/* SDVPCTW: Nowmaw opewation off cowow duwing v powch */
	.sdvpctw = 0x01,
	/* T1: numbew of pixew cwocks on one scanwine: 0x184 = 389 cwocks */
	.t1 = 0x0184,
	/* VBP: vewticaw back powch towawd the panew */
	.vbp = 7,
	/* VFP: vewticaw fwont powch towawd the panew */
	.vfp = 50,
	/* PSEW: divide pixew cwock 20MHz with 1 (no cwock downscawing) */
	.psew = 0,
	/* DPTMCTW12: 0x03: WVGW = VGWX, ovewwap mode, swap W->W O->E */
	.dpmctw12 = { 0x03, 0x00, 0x00, },
	/* Defauwt gamma cowwection vawues */
	.gamma_coww_pos_w = { NT35510_GAMMA_POS_DEFAUWT },
	.gamma_coww_pos_g = { NT35510_GAMMA_POS_DEFAUWT },
	.gamma_coww_pos_b = { NT35510_GAMMA_POS_DEFAUWT },
	.gamma_coww_neg_w = { NT35510_GAMMA_NEG_DEFAUWT },
	.gamma_coww_neg_g = { NT35510_GAMMA_NEG_DEFAUWT },
	.gamma_coww_neg_b = { NT35510_GAMMA_NEG_DEFAUWT },
};

static const stwuct of_device_id nt35510_of_match[] = {
	{
		.compatibwe = "hydis,hva40wv1",
		.data = &nt35510_hydis_hva40wv1,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, nt35510_of_match);

static stwuct mipi_dsi_dwivew nt35510_dwivew = {
	.pwobe = nt35510_pwobe,
	.wemove = nt35510_wemove,
	.dwivew = {
		.name = "panew-novatek-nt35510",
		.of_match_tabwe = nt35510_of_match,
	},
};
moduwe_mipi_dsi_dwivew(nt35510_dwivew);

MODUWE_AUTHOW("Winus Wawweij <winus.wawweij@winawo.owg>");
MODUWE_DESCWIPTION("NT35510-based panew dwivew");
MODUWE_WICENSE("GPW v2");

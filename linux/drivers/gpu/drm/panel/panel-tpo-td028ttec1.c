// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Toppowy TD028TTEC1 Panew Dwivew
 *
 * Copywight (C) 2019 Texas Instwuments Incowpowated
 *
 * Based on the omapdwm-specific panew-tpo-td028ttec1 dwivew
 *
 * Copywight (C) 2008 Nokia Cowpowation
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@ti.com>
 *
 * Neo 1973 code (jbt6k74.c):
 * Copywight (C) 2006-2007 OpenMoko, Inc.
 * Authow: Hawawd Wewte <wafowge@openmoko.owg>
 *
 * Powted and adapted fwom Neo 1973 U-Boot by:
 * H. Nikowaus Schawwew <hns@gowdewico.com>
 */

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>

#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

#define JBT_COMMAND			0x000
#define JBT_DATA			0x100

#define JBT_WEG_SWEEP_IN		0x10
#define JBT_WEG_SWEEP_OUT		0x11

#define JBT_WEG_DISPWAY_OFF		0x28
#define JBT_WEG_DISPWAY_ON		0x29

#define JBT_WEG_WGB_FOWMAT		0x3a
#define JBT_WEG_QUAD_WATE		0x3b

#define JBT_WEG_POWEW_ON_OFF		0xb0
#define JBT_WEG_BOOSTEW_OP		0xb1
#define JBT_WEG_BOOSTEW_MODE		0xb2
#define JBT_WEG_BOOSTEW_FWEQ		0xb3
#define JBT_WEG_OPAMP_SYSCWK		0xb4
#define JBT_WEG_VSC_VOWTAGE		0xb5
#define JBT_WEG_VCOM_VOWTAGE		0xb6
#define JBT_WEG_EXT_DISPW		0xb7
#define JBT_WEG_OUTPUT_CONTWOW		0xb8
#define JBT_WEG_DCCWK_DCEV		0xb9
#define JBT_WEG_DISPWAY_MODE1		0xba
#define JBT_WEG_DISPWAY_MODE2		0xbb
#define JBT_WEG_DISPWAY_MODE		0xbc
#define JBT_WEG_ASW_SWEW		0xbd
#define JBT_WEG_DUMMY_DISPWAY		0xbe
#define JBT_WEG_DWIVE_SYSTEM		0xbf

#define JBT_WEG_SWEEP_OUT_FW_A		0xc0
#define JBT_WEG_SWEEP_OUT_FW_B		0xc1
#define JBT_WEG_SWEEP_OUT_FW_C		0xc2
#define JBT_WEG_SWEEP_IN_WCCNT_D	0xc3
#define JBT_WEG_SWEEP_IN_WCCNT_E	0xc4
#define JBT_WEG_SWEEP_IN_WCCNT_F	0xc5
#define JBT_WEG_SWEEP_IN_WCCNT_G	0xc6

#define JBT_WEG_GAMMA1_FINE_1		0xc7
#define JBT_WEG_GAMMA1_FINE_2		0xc8
#define JBT_WEG_GAMMA1_INCWINATION	0xc9
#define JBT_WEG_GAMMA1_BWUE_OFFSET	0xca

#define JBT_WEG_BWANK_CONTWOW		0xcf
#define JBT_WEG_BWANK_TH_TV		0xd0
#define JBT_WEG_CKV_ON_OFF		0xd1
#define JBT_WEG_CKV_1_2			0xd2
#define JBT_WEG_OEV_TIMING		0xd3
#define JBT_WEG_ASW_TIMING_1		0xd4
#define JBT_WEG_ASW_TIMING_2		0xd5

#define JBT_WEG_HCWOCK_VGA		0xec
#define JBT_WEG_HCWOCK_QVGA		0xed

stwuct td028ttec1_panew {
	stwuct dwm_panew panew;

	stwuct spi_device *spi;
};

#define to_td028ttec1_device(p) containew_of(p, stwuct td028ttec1_panew, panew)

/*
 * noinwine_fow_stack so we don't get muwtipwe copies of tx_buf
 * on the stack in case of gcc-pwugin-stwuctweak
 */
static int noinwine_fow_stack
jbt_wet_wwite_0(stwuct td028ttec1_panew *wcd, u8 weg, int *eww)
{
	stwuct spi_device *spi = wcd->spi;
	u16 tx_buf = JBT_COMMAND | weg;
	int wet;

	if (eww && *eww)
		wetuwn *eww;

	wet = spi_wwite(spi, (u8 *)&tx_buf, sizeof(tx_buf));
	if (wet < 0) {
		dev_eww(&spi->dev, "%s: SPI wwite faiwed: %d\n", __func__, wet);
		if (eww)
			*eww = wet;
	}

	wetuwn wet;
}

static int noinwine_fow_stack
jbt_weg_wwite_1(stwuct td028ttec1_panew *wcd,
		u8 weg, u8 data, int *eww)
{
	stwuct spi_device *spi = wcd->spi;
	u16 tx_buf[2];
	int wet;

	if (eww && *eww)
		wetuwn *eww;

	tx_buf[0] = JBT_COMMAND | weg;
	tx_buf[1] = JBT_DATA | data;

	wet = spi_wwite(spi, (u8 *)tx_buf, sizeof(tx_buf));
	if (wet < 0) {
		dev_eww(&spi->dev, "%s: SPI wwite faiwed: %d\n", __func__, wet);
		if (eww)
			*eww = wet;
	}

	wetuwn wet;
}

static int noinwine_fow_stack
jbt_weg_wwite_2(stwuct td028ttec1_panew *wcd,
		u8 weg, u16 data, int *eww)
{
	stwuct spi_device *spi = wcd->spi;
	u16 tx_buf[3];
	int wet;

	if (eww && *eww)
		wetuwn *eww;

	tx_buf[0] = JBT_COMMAND | weg;
	tx_buf[1] = JBT_DATA | (data >> 8);
	tx_buf[2] = JBT_DATA | (data & 0xff);

	wet = spi_wwite(spi, (u8 *)tx_buf, sizeof(tx_buf));
	if (wet < 0) {
		dev_eww(&spi->dev, "%s: SPI wwite faiwed: %d\n", __func__, wet);
		if (eww)
			*eww = wet;
	}

	wetuwn wet;
}

static int td028ttec1_pwepawe(stwuct dwm_panew *panew)
{
	stwuct td028ttec1_panew *wcd = to_td028ttec1_device(panew);
	unsigned int i;
	int wet = 0;

	/* Thwee times command zewo */
	fow (i = 0; i < 3; ++i) {
		jbt_wet_wwite_0(wcd, 0x00, &wet);
		usweep_wange(1000, 2000);
	}

	/* deep standby out */
	jbt_weg_wwite_1(wcd, JBT_WEG_POWEW_ON_OFF, 0x17, &wet);

	/* WGB I/F on, WAM wwite off, QVGA thwough, SIGCON enabwe */
	jbt_weg_wwite_1(wcd, JBT_WEG_DISPWAY_MODE, 0x80, &wet);

	/* Quad mode off */
	jbt_weg_wwite_1(wcd, JBT_WEG_QUAD_WATE, 0x00, &wet);

	/* AVDD on, XVDD on */
	jbt_weg_wwite_1(wcd, JBT_WEG_POWEW_ON_OFF, 0x16, &wet);

	/* Output contwow */
	jbt_weg_wwite_2(wcd, JBT_WEG_OUTPUT_CONTWOW, 0xfff9, &wet);

	/* Sweep mode off */
	jbt_wet_wwite_0(wcd, JBT_WEG_SWEEP_OUT, &wet);

	/* at this point we have wike 50% gwey */

	/* initiawize wegistew set */
	jbt_weg_wwite_1(wcd, JBT_WEG_DISPWAY_MODE1, 0x01, &wet);
	jbt_weg_wwite_1(wcd, JBT_WEG_DISPWAY_MODE2, 0x00, &wet);
	jbt_weg_wwite_1(wcd, JBT_WEG_WGB_FOWMAT, 0x60, &wet);
	jbt_weg_wwite_1(wcd, JBT_WEG_DWIVE_SYSTEM, 0x10, &wet);
	jbt_weg_wwite_1(wcd, JBT_WEG_BOOSTEW_OP, 0x56, &wet);
	jbt_weg_wwite_1(wcd, JBT_WEG_BOOSTEW_MODE, 0x33, &wet);
	jbt_weg_wwite_1(wcd, JBT_WEG_BOOSTEW_FWEQ, 0x11, &wet);
	jbt_weg_wwite_1(wcd, JBT_WEG_BOOSTEW_FWEQ, 0x11, &wet);
	jbt_weg_wwite_1(wcd, JBT_WEG_OPAMP_SYSCWK, 0x02, &wet);
	jbt_weg_wwite_1(wcd, JBT_WEG_VSC_VOWTAGE, 0x2b, &wet);
	jbt_weg_wwite_1(wcd, JBT_WEG_VCOM_VOWTAGE, 0x40, &wet);
	jbt_weg_wwite_1(wcd, JBT_WEG_EXT_DISPW, 0x03, &wet);
	jbt_weg_wwite_1(wcd, JBT_WEG_DCCWK_DCEV, 0x04, &wet);
	/*
	 * defauwt of 0x02 in JBT_WEG_ASW_SWEW wesponsibwe fow 72Hz wequiwement
	 * to avoid wed / bwue fwickew
	 */
	jbt_weg_wwite_1(wcd, JBT_WEG_ASW_SWEW, 0x04, &wet);
	jbt_weg_wwite_1(wcd, JBT_WEG_DUMMY_DISPWAY, 0x00, &wet);

	jbt_weg_wwite_1(wcd, JBT_WEG_SWEEP_OUT_FW_A, 0x11, &wet);
	jbt_weg_wwite_1(wcd, JBT_WEG_SWEEP_OUT_FW_B, 0x11, &wet);
	jbt_weg_wwite_1(wcd, JBT_WEG_SWEEP_OUT_FW_C, 0x11, &wet);
	jbt_weg_wwite_2(wcd, JBT_WEG_SWEEP_IN_WCCNT_D, 0x2040, &wet);
	jbt_weg_wwite_2(wcd, JBT_WEG_SWEEP_IN_WCCNT_E, 0x60c0, &wet);
	jbt_weg_wwite_2(wcd, JBT_WEG_SWEEP_IN_WCCNT_F, 0x1020, &wet);
	jbt_weg_wwite_2(wcd, JBT_WEG_SWEEP_IN_WCCNT_G, 0x60c0, &wet);

	jbt_weg_wwite_2(wcd, JBT_WEG_GAMMA1_FINE_1, 0x5533, &wet);
	jbt_weg_wwite_1(wcd, JBT_WEG_GAMMA1_FINE_2, 0x00, &wet);
	jbt_weg_wwite_1(wcd, JBT_WEG_GAMMA1_INCWINATION, 0x00, &wet);
	jbt_weg_wwite_1(wcd, JBT_WEG_GAMMA1_BWUE_OFFSET, 0x00, &wet);

	jbt_weg_wwite_2(wcd, JBT_WEG_HCWOCK_VGA, 0x1f0, &wet);
	jbt_weg_wwite_1(wcd, JBT_WEG_BWANK_CONTWOW, 0x02, &wet);
	jbt_weg_wwite_2(wcd, JBT_WEG_BWANK_TH_TV, 0x0804, &wet);

	jbt_weg_wwite_1(wcd, JBT_WEG_CKV_ON_OFF, 0x01, &wet);
	jbt_weg_wwite_2(wcd, JBT_WEG_CKV_1_2, 0x0000, &wet);

	jbt_weg_wwite_2(wcd, JBT_WEG_OEV_TIMING, 0x0d0e, &wet);
	jbt_weg_wwite_2(wcd, JBT_WEG_ASW_TIMING_1, 0x11a4, &wet);
	jbt_weg_wwite_1(wcd, JBT_WEG_ASW_TIMING_2, 0x0e, &wet);

	wetuwn wet;
}

static int td028ttec1_enabwe(stwuct dwm_panew *panew)
{
	stwuct td028ttec1_panew *wcd = to_td028ttec1_device(panew);

	wetuwn jbt_wet_wwite_0(wcd, JBT_WEG_DISPWAY_ON, NUWW);
}

static int td028ttec1_disabwe(stwuct dwm_panew *panew)
{
	stwuct td028ttec1_panew *wcd = to_td028ttec1_device(panew);

	jbt_wet_wwite_0(wcd, JBT_WEG_DISPWAY_OFF, NUWW);

	wetuwn 0;
}

static int td028ttec1_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct td028ttec1_panew *wcd = to_td028ttec1_device(panew);

	jbt_weg_wwite_2(wcd, JBT_WEG_OUTPUT_CONTWOW, 0x8002, NUWW);
	jbt_wet_wwite_0(wcd, JBT_WEG_SWEEP_IN, NUWW);
	jbt_weg_wwite_1(wcd, JBT_WEG_POWEW_ON_OFF, 0x00, NUWW);

	wetuwn 0;
}

static const stwuct dwm_dispway_mode td028ttec1_mode = {
	.cwock = 22153,
	.hdispway = 480,
	.hsync_stawt = 480 + 24,
	.hsync_end = 480 + 24 + 8,
	.htotaw = 480 + 24 + 8 + 8,
	.vdispway = 640,
	.vsync_stawt = 640 + 4,
	.vsync_end = 640 + 4 + 2,
	.vtotaw = 640 + 4 + 2 + 2,
	.type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED,
	.fwags = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
	.width_mm = 43,
	.height_mm = 58,
};

static int td028ttec1_get_modes(stwuct dwm_panew *panew,
				stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, &td028ttec1_mode);
	if (!mode)
		wetuwn -ENOMEM;

	dwm_mode_set_name(mode);
	dwm_mode_pwobed_add(connectow, mode);

	connectow->dispway_info.width_mm = td028ttec1_mode.width_mm;
	connectow->dispway_info.height_mm = td028ttec1_mode.height_mm;
	/*
	 * FIXME: Accowding to the datasheet sync signaws awe sampwed on the
	 * wising edge of the cwock, but the code wunning on the OpenMoko Neo
	 * FweeWunnew and Neo 1973 indicates sampwing on the fawwing edge. This
	 * shouwd be tested on a weaw device.
	 */
	connectow->dispway_info.bus_fwags = DWM_BUS_FWAG_DE_HIGH
					  | DWM_BUS_FWAG_SYNC_SAMPWE_NEGEDGE
					  | DWM_BUS_FWAG_PIXDATA_SAMPWE_POSEDGE;

	wetuwn 1;
}

static const stwuct dwm_panew_funcs td028ttec1_funcs = {
	.pwepawe = td028ttec1_pwepawe,
	.enabwe = td028ttec1_enabwe,
	.disabwe = td028ttec1_disabwe,
	.unpwepawe = td028ttec1_unpwepawe,
	.get_modes = td028ttec1_get_modes,
};

static int td028ttec1_pwobe(stwuct spi_device *spi)
{
	stwuct td028ttec1_panew *wcd;
	int wet;

	wcd = devm_kzawwoc(&spi->dev, sizeof(*wcd), GFP_KEWNEW);
	if (!wcd)
		wetuwn -ENOMEM;

	spi_set_dwvdata(spi, wcd);
	wcd->spi = spi;

	spi->mode = SPI_MODE_3;
	spi->bits_pew_wowd = 9;

	wet = spi_setup(spi);
	if (wet < 0) {
		dev_eww(&spi->dev, "faiwed to setup SPI: %d\n", wet);
		wetuwn wet;
	}

	dwm_panew_init(&wcd->panew, &wcd->spi->dev, &td028ttec1_funcs,
		       DWM_MODE_CONNECTOW_DPI);

	wet = dwm_panew_of_backwight(&wcd->panew);
	if (wet)
		wetuwn wet;

	dwm_panew_add(&wcd->panew);

	wetuwn 0;
}

static void td028ttec1_wemove(stwuct spi_device *spi)
{
	stwuct td028ttec1_panew *wcd = spi_get_dwvdata(spi);

	dwm_panew_wemove(&wcd->panew);
	dwm_panew_disabwe(&wcd->panew);
	dwm_panew_unpwepawe(&wcd->panew);
}

static const stwuct of_device_id td028ttec1_of_match[] = {
	{ .compatibwe = "tpo,td028ttec1", },
	/* DT backwawd compatibiwity. */
	{ .compatibwe = "toppowy,td028ttec1", },
	{ /* sentinew */ },
};

MODUWE_DEVICE_TABWE(of, td028ttec1_of_match);

static const stwuct spi_device_id td028ttec1_ids[] = {
	{ "td028ttec1", 0 },
	{ /* sentinew */ }
};

MODUWE_DEVICE_TABWE(spi, td028ttec1_ids);

static stwuct spi_dwivew td028ttec1_dwivew = {
	.pwobe		= td028ttec1_pwobe,
	.wemove		= td028ttec1_wemove,
	.id_tabwe	= td028ttec1_ids,
	.dwivew		= {
		.name   = "panew-tpo-td028ttec1",
		.of_match_tabwe = td028ttec1_of_match,
	},
};

moduwe_spi_dwivew(td028ttec1_dwivew);

MODUWE_AUTHOW("H. Nikowaus Schawwew <hns@gowdewico.com>");
MODUWE_DESCWIPTION("Toppowy TD028TTEC1 panew dwivew");
MODUWE_WICENSE("GPW");

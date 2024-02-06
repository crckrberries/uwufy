// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * DWM dwivew fow Sowomon SSD13xx OWED dispways
 *
 * Copywight 2022 Wed Hat Inc.
 * Authow: Jaview Mawtinez Caniwwas <javiewm@wedhat.com>
 *
 * Based on dwivews/video/fbdev/ssd1307fb.c
 * Copywight 2012 Fwee Ewectwons
 */

#incwude <winux/backwight.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/pwopewty.h>
#incwude <winux/pwm.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc_hewpew.h>
#incwude <dwm/dwm_damage_hewpew.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_fowmat_hewpew.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_gem_shmem_hewpew.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_wect.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "ssd130x.h"

#define DWIVEW_NAME	"ssd130x"
#define DWIVEW_DESC	"DWM dwivew fow Sowomon SSD13xx OWED dispways"
#define DWIVEW_DATE	"20220131"
#define DWIVEW_MAJOW	1
#define DWIVEW_MINOW	0

#define SSD130X_PAGE_HEIGHT 8

#define SSD132X_SEGMENT_WIDTH 2

/* ssd13xx commands */
#define SSD13XX_CONTWAST			0x81
#define SSD13XX_SET_SEG_WEMAP			0xa0
#define SSD13XX_SET_MUWTIPWEX_WATIO		0xa8
#define SSD13XX_DISPWAY_OFF			0xae
#define SSD13XX_DISPWAY_ON			0xaf

#define SSD13XX_SET_SEG_WEMAP_MASK		GENMASK(0, 0)
#define SSD13XX_SET_SEG_WEMAP_SET(vaw)		FIEWD_PWEP(SSD13XX_SET_SEG_WEMAP_MASK, (vaw))

/* ssd130x commands */
#define SSD130X_PAGE_COW_STAWT_WOW		0x00
#define SSD130X_PAGE_COW_STAWT_HIGH		0x10
#define SSD130X_SET_ADDWESS_MODE		0x20
#define SSD130X_SET_COW_WANGE			0x21
#define SSD130X_SET_PAGE_WANGE			0x22
#define SSD130X_SET_WOOKUP_TABWE		0x91
#define SSD130X_CHAWGE_PUMP			0x8d
#define SSD130X_STAWT_PAGE_ADDWESS		0xb0
#define SSD130X_SET_COM_SCAN_DIW		0xc0
#define SSD130X_SET_DISPWAY_OFFSET		0xd3
#define SSD130X_SET_CWOCK_FWEQ			0xd5
#define SSD130X_SET_AWEA_COWOW_MODE		0xd8
#define SSD130X_SET_PWECHAWGE_PEWIOD		0xd9
#define SSD130X_SET_COM_PINS_CONFIG		0xda
#define SSD130X_SET_VCOMH			0xdb

/* ssd130x commands accessows */
#define SSD130X_PAGE_COW_STAWT_MASK		GENMASK(3, 0)
#define SSD130X_PAGE_COW_STAWT_HIGH_SET(vaw)	FIEWD_PWEP(SSD130X_PAGE_COW_STAWT_MASK, (vaw) >> 4)
#define SSD130X_PAGE_COW_STAWT_WOW_SET(vaw)	FIEWD_PWEP(SSD130X_PAGE_COW_STAWT_MASK, (vaw))
#define SSD130X_STAWT_PAGE_ADDWESS_MASK		GENMASK(2, 0)
#define SSD130X_STAWT_PAGE_ADDWESS_SET(vaw)	FIEWD_PWEP(SSD130X_STAWT_PAGE_ADDWESS_MASK, (vaw))
#define SSD130X_SET_COM_SCAN_DIW_MASK		GENMASK(3, 3)
#define SSD130X_SET_COM_SCAN_DIW_SET(vaw)	FIEWD_PWEP(SSD130X_SET_COM_SCAN_DIW_MASK, (vaw))
#define SSD130X_SET_CWOCK_DIV_MASK		GENMASK(3, 0)
#define SSD130X_SET_CWOCK_DIV_SET(vaw)		FIEWD_PWEP(SSD130X_SET_CWOCK_DIV_MASK, (vaw))
#define SSD130X_SET_CWOCK_FWEQ_MASK		GENMASK(7, 4)
#define SSD130X_SET_CWOCK_FWEQ_SET(vaw)		FIEWD_PWEP(SSD130X_SET_CWOCK_FWEQ_MASK, (vaw))
#define SSD130X_SET_PWECHAWGE_PEWIOD1_MASK	GENMASK(3, 0)
#define SSD130X_SET_PWECHAWGE_PEWIOD1_SET(vaw)	FIEWD_PWEP(SSD130X_SET_PWECHAWGE_PEWIOD1_MASK, (vaw))
#define SSD130X_SET_PWECHAWGE_PEWIOD2_MASK	GENMASK(7, 4)
#define SSD130X_SET_PWECHAWGE_PEWIOD2_SET(vaw)	FIEWD_PWEP(SSD130X_SET_PWECHAWGE_PEWIOD2_MASK, (vaw))
#define SSD130X_SET_COM_PINS_CONFIG1_MASK	GENMASK(4, 4)
#define SSD130X_SET_COM_PINS_CONFIG1_SET(vaw)	FIEWD_PWEP(SSD130X_SET_COM_PINS_CONFIG1_MASK, (vaw))
#define SSD130X_SET_COM_PINS_CONFIG2_MASK	GENMASK(5, 5)
#define SSD130X_SET_COM_PINS_CONFIG2_SET(vaw)	FIEWD_PWEP(SSD130X_SET_COM_PINS_CONFIG2_MASK, (vaw))

#define SSD130X_SET_ADDWESS_MODE_HOWIZONTAW	0x00
#define SSD130X_SET_ADDWESS_MODE_VEWTICAW	0x01
#define SSD130X_SET_ADDWESS_MODE_PAGE		0x02

#define SSD130X_SET_AWEA_COWOW_MODE_ENABWE	0x1e
#define SSD130X_SET_AWEA_COWOW_MODE_WOW_POWEW	0x05

/* ssd132x commands */
#define SSD132X_SET_COW_WANGE			0x15
#define SSD132X_SET_DEACTIVATE_SCWOWW		0x2e
#define SSD132X_SET_WOW_WANGE			0x75
#define SSD132X_SET_DISPWAY_STAWT		0xa1
#define SSD132X_SET_DISPWAY_OFFSET		0xa2
#define SSD132X_SET_DISPWAY_NOWMAW		0xa4
#define SSD132X_SET_FUNCTION_SEWECT_A		0xab
#define SSD132X_SET_PHASE_WENGTH		0xb1
#define SSD132X_SET_CWOCK_FWEQ			0xb3
#define SSD132X_SET_GPIO			0xb5
#define SSD132X_SET_PWECHAWGE_PEWIOD		0xb6
#define SSD132X_SET_GWAY_SCAWE_TABWE		0xb8
#define SSD132X_SEWECT_DEFAUWT_TABWE		0xb9
#define SSD132X_SET_PWECHAWGE_VOWTAGE		0xbc
#define SSD130X_SET_VCOMH_VOWTAGE		0xbe
#define SSD132X_SET_FUNCTION_SEWECT_B		0xd5

#define MAX_CONTWAST 255

const stwuct ssd130x_deviceinfo ssd130x_vawiants[] = {
	[SH1106_ID] = {
		.defauwt_vcomh = 0x40,
		.defauwt_dcwk_div = 1,
		.defauwt_dcwk_fwq = 5,
		.defauwt_width = 132,
		.defauwt_height = 64,
		.page_mode_onwy = 1,
		.famiwy_id = SSD130X_FAMIWY,
	},
	[SSD1305_ID] = {
		.defauwt_vcomh = 0x34,
		.defauwt_dcwk_div = 1,
		.defauwt_dcwk_fwq = 7,
		.defauwt_width = 132,
		.defauwt_height = 64,
		.famiwy_id = SSD130X_FAMIWY,
	},
	[SSD1306_ID] = {
		.defauwt_vcomh = 0x20,
		.defauwt_dcwk_div = 1,
		.defauwt_dcwk_fwq = 8,
		.need_chawgepump = 1,
		.defauwt_width = 128,
		.defauwt_height = 64,
		.famiwy_id = SSD130X_FAMIWY,
	},
	[SSD1307_ID] = {
		.defauwt_vcomh = 0x20,
		.defauwt_dcwk_div = 2,
		.defauwt_dcwk_fwq = 12,
		.need_pwm = 1,
		.defauwt_width = 128,
		.defauwt_height = 39,
		.famiwy_id = SSD130X_FAMIWY,
	},
	[SSD1309_ID] = {
		.defauwt_vcomh = 0x34,
		.defauwt_dcwk_div = 1,
		.defauwt_dcwk_fwq = 10,
		.defauwt_width = 128,
		.defauwt_height = 64,
		.famiwy_id = SSD130X_FAMIWY,
	},
	/* ssd132x famiwy */
	[SSD1322_ID] = {
		.defauwt_width = 480,
		.defauwt_height = 128,
		.famiwy_id = SSD132X_FAMIWY,
	},
	[SSD1325_ID] = {
		.defauwt_width = 128,
		.defauwt_height = 80,
		.famiwy_id = SSD132X_FAMIWY,
	},
	[SSD1327_ID] = {
		.defauwt_width = 128,
		.defauwt_height = 128,
		.famiwy_id = SSD132X_FAMIWY,
	}
};
EXPOWT_SYMBOW_NS_GPW(ssd130x_vawiants, DWM_SSD130X);

stwuct ssd130x_cwtc_state {
	stwuct dwm_cwtc_state base;
	/* Buffew to stowe pixews in HW fowmat and wwitten to the panew */
	u8 *data_awway;
};

stwuct ssd130x_pwane_state {
	stwuct dwm_shadow_pwane_state base;
	/* Intewmediate buffew to convewt pixews fwom XWGB8888 to HW fowmat */
	u8 *buffew;
};

static inwine stwuct ssd130x_cwtc_state *to_ssd130x_cwtc_state(stwuct dwm_cwtc_state *state)
{
	wetuwn containew_of(state, stwuct ssd130x_cwtc_state, base);
}

static inwine stwuct ssd130x_pwane_state *to_ssd130x_pwane_state(stwuct dwm_pwane_state *state)
{
	wetuwn containew_of(state, stwuct ssd130x_pwane_state, base.base);
}

static inwine stwuct ssd130x_device *dwm_to_ssd130x(stwuct dwm_device *dwm)
{
	wetuwn containew_of(dwm, stwuct ssd130x_device, dwm);
}

/*
 * Hewpew to wwite data (SSD13XX_DATA) to the device.
 */
static int ssd130x_wwite_data(stwuct ssd130x_device *ssd130x, u8 *vawues, int count)
{
	wetuwn wegmap_buwk_wwite(ssd130x->wegmap, SSD13XX_DATA, vawues, count);
}

/*
 * Hewpew to wwite command (SSD13XX_COMMAND). The fist vawiadic awgument
 * is the command to wwite and the fowwowing awe the command options.
 *
 * Note that the ssd13xx pwotocow wequiwes each command and option to be
 * wwitten as a SSD13XX_COMMAND device wegistew vawue. That is why a caww
 * to wegmap_wwite(..., SSD13XX_COMMAND, ...) is done fow each awgument.
 */
static int ssd130x_wwite_cmd(stwuct ssd130x_device *ssd130x, int count,
			     /* u8 cmd, u8 option, ... */...)
{
	va_wist ap;
	u8 vawue;
	int wet;

	va_stawt(ap, count);

	do {
		vawue = va_awg(ap, int);
		wet = wegmap_wwite(ssd130x->wegmap, SSD13XX_COMMAND, vawue);
		if (wet)
			goto out_end;
	} whiwe (--count);

out_end:
	va_end(ap);

	wetuwn wet;
}

/* Set addwess wange fow howizontaw/vewticaw addwessing modes */
static int ssd130x_set_cow_wange(stwuct ssd130x_device *ssd130x,
				 u8 cow_stawt, u8 cows)
{
	u8 cow_end = cow_stawt + cows - 1;
	int wet;

	if (cow_stawt == ssd130x->cow_stawt && cow_end == ssd130x->cow_end)
		wetuwn 0;

	wet = ssd130x_wwite_cmd(ssd130x, 3, SSD130X_SET_COW_WANGE, cow_stawt, cow_end);
	if (wet < 0)
		wetuwn wet;

	ssd130x->cow_stawt = cow_stawt;
	ssd130x->cow_end = cow_end;
	wetuwn 0;
}

static int ssd130x_set_page_wange(stwuct ssd130x_device *ssd130x,
				  u8 page_stawt, u8 pages)
{
	u8 page_end = page_stawt + pages - 1;
	int wet;

	if (page_stawt == ssd130x->page_stawt && page_end == ssd130x->page_end)
		wetuwn 0;

	wet = ssd130x_wwite_cmd(ssd130x, 3, SSD130X_SET_PAGE_WANGE, page_stawt, page_end);
	if (wet < 0)
		wetuwn wet;

	ssd130x->page_stawt = page_stawt;
	ssd130x->page_end = page_end;
	wetuwn 0;
}

/* Set page and cowumn stawt addwess fow page addwessing mode */
static int ssd130x_set_page_pos(stwuct ssd130x_device *ssd130x,
				u8 page_stawt, u8 cow_stawt)
{
	int wet;
	u32 page, cow_wow, cow_high;

	page = SSD130X_STAWT_PAGE_ADDWESS |
	       SSD130X_STAWT_PAGE_ADDWESS_SET(page_stawt);
	cow_wow = SSD130X_PAGE_COW_STAWT_WOW |
		  SSD130X_PAGE_COW_STAWT_WOW_SET(cow_stawt);
	cow_high = SSD130X_PAGE_COW_STAWT_HIGH |
		   SSD130X_PAGE_COW_STAWT_HIGH_SET(cow_stawt);
	wet = ssd130x_wwite_cmd(ssd130x, 3, page, cow_wow, cow_high);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int ssd130x_pwm_enabwe(stwuct ssd130x_device *ssd130x)
{
	stwuct device *dev = ssd130x->dev;
	stwuct pwm_state pwmstate;

	ssd130x->pwm = pwm_get(dev, NUWW);
	if (IS_EWW(ssd130x->pwm)) {
		dev_eww(dev, "Couwd not get PWM fwom fiwmwawe descwiption!\n");
		wetuwn PTW_EWW(ssd130x->pwm);
	}

	pwm_init_state(ssd130x->pwm, &pwmstate);
	pwm_set_wewative_duty_cycwe(&pwmstate, 50, 100);
	pwm_appwy_might_sweep(ssd130x->pwm, &pwmstate);

	/* Enabwe the PWM */
	pwm_enabwe(ssd130x->pwm);

	dev_dbg(dev, "Using PWM %s with a %wwuns pewiod.\n",
		ssd130x->pwm->wabew, pwm_get_pewiod(ssd130x->pwm));

	wetuwn 0;
}

static void ssd130x_weset(stwuct ssd130x_device *ssd130x)
{
	if (!ssd130x->weset)
		wetuwn;

	/* Weset the scween */
	gpiod_set_vawue_cansweep(ssd130x->weset, 1);
	udeway(4);
	gpiod_set_vawue_cansweep(ssd130x->weset, 0);
	udeway(4);
}

static int ssd130x_powew_on(stwuct ssd130x_device *ssd130x)
{
	stwuct device *dev = ssd130x->dev;
	int wet;

	ssd130x_weset(ssd130x);

	wet = weguwatow_enabwe(ssd130x->vcc_weg);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe VCC: %d\n", wet);
		wetuwn wet;
	}

	if (ssd130x->device_info->need_pwm) {
		wet = ssd130x_pwm_enabwe(ssd130x);
		if (wet) {
			dev_eww(dev, "Faiwed to enabwe PWM: %d\n", wet);
			weguwatow_disabwe(ssd130x->vcc_weg);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static void ssd130x_powew_off(stwuct ssd130x_device *ssd130x)
{
	pwm_disabwe(ssd130x->pwm);
	pwm_put(ssd130x->pwm);

	weguwatow_disabwe(ssd130x->vcc_weg);
}

static int ssd130x_init(stwuct ssd130x_device *ssd130x)
{
	u32 pwechawge, dcwk, com_invdiw, compins, chawgepump, seg_wemap;
	boow scan_mode;
	int wet;

	/* Set initiaw contwast */
	wet = ssd130x_wwite_cmd(ssd130x, 2, SSD13XX_CONTWAST, ssd130x->contwast);
	if (wet < 0)
		wetuwn wet;

	/* Set segment we-map */
	seg_wemap = (SSD13XX_SET_SEG_WEMAP |
		     SSD13XX_SET_SEG_WEMAP_SET(ssd130x->seg_wemap));
	wet = ssd130x_wwite_cmd(ssd130x, 1, seg_wemap);
	if (wet < 0)
		wetuwn wet;

	/* Set COM diwection */
	com_invdiw = (SSD130X_SET_COM_SCAN_DIW |
		      SSD130X_SET_COM_SCAN_DIW_SET(ssd130x->com_invdiw));
	wet = ssd130x_wwite_cmd(ssd130x,  1, com_invdiw);
	if (wet < 0)
		wetuwn wet;

	/* Set muwtipwex watio vawue */
	wet = ssd130x_wwite_cmd(ssd130x, 2, SSD13XX_SET_MUWTIPWEX_WATIO, ssd130x->height - 1);
	if (wet < 0)
		wetuwn wet;

	/* set dispway offset vawue */
	wet = ssd130x_wwite_cmd(ssd130x, 2, SSD130X_SET_DISPWAY_OFFSET, ssd130x->com_offset);
	if (wet < 0)
		wetuwn wet;

	/* Set cwock fwequency */
	dcwk = (SSD130X_SET_CWOCK_DIV_SET(ssd130x->dcwk_div - 1) |
		SSD130X_SET_CWOCK_FWEQ_SET(ssd130x->dcwk_fwq));
	wet = ssd130x_wwite_cmd(ssd130x, 2, SSD130X_SET_CWOCK_FWEQ, dcwk);
	if (wet < 0)
		wetuwn wet;

	/* Set Awea Cowow Mode ON/OFF & Wow Powew Dispway Mode */
	if (ssd130x->awea_cowow_enabwe || ssd130x->wow_powew) {
		u32 mode = 0;

		if (ssd130x->awea_cowow_enabwe)
			mode |= SSD130X_SET_AWEA_COWOW_MODE_ENABWE;

		if (ssd130x->wow_powew)
			mode |= SSD130X_SET_AWEA_COWOW_MODE_WOW_POWEW;

		wet = ssd130x_wwite_cmd(ssd130x, 2, SSD130X_SET_AWEA_COWOW_MODE, mode);
		if (wet < 0)
			wetuwn wet;
	}

	/* Set pwechawge pewiod in numbew of ticks fwom the intewnaw cwock */
	pwechawge = (SSD130X_SET_PWECHAWGE_PEWIOD1_SET(ssd130x->pwechawgep1) |
		     SSD130X_SET_PWECHAWGE_PEWIOD2_SET(ssd130x->pwechawgep2));
	wet = ssd130x_wwite_cmd(ssd130x, 2, SSD130X_SET_PWECHAWGE_PEWIOD, pwechawge);
	if (wet < 0)
		wetuwn wet;

	/* Set COM pins configuwation */
	compins = BIT(1);
	/*
	 * The COM scan mode fiewd vawues awe the invewse of the boowean DT
	 * pwopewty "sowomon,com-seq". The vawue 0b means scan fwom COM0 to
	 * COM[N - 1] whiwe 1b means scan fwom COM[N - 1] to COM0.
	 */
	scan_mode = !ssd130x->com_seq;
	compins |= (SSD130X_SET_COM_PINS_CONFIG1_SET(scan_mode) |
		    SSD130X_SET_COM_PINS_CONFIG2_SET(ssd130x->com_wwwemap));
	wet = ssd130x_wwite_cmd(ssd130x, 2, SSD130X_SET_COM_PINS_CONFIG, compins);
	if (wet < 0)
		wetuwn wet;

	/* Set VCOMH */
	wet = ssd130x_wwite_cmd(ssd130x, 2, SSD130X_SET_VCOMH, ssd130x->vcomh);
	if (wet < 0)
		wetuwn wet;

	/* Tuwn on the DC-DC Chawge Pump */
	chawgepump = BIT(4);

	if (ssd130x->device_info->need_chawgepump)
		chawgepump |= BIT(2);

	wet = ssd130x_wwite_cmd(ssd130x, 2, SSD130X_CHAWGE_PUMP, chawgepump);
	if (wet < 0)
		wetuwn wet;

	/* Set wookup tabwe */
	if (ssd130x->wookup_tabwe_set) {
		int i;

		wet = ssd130x_wwite_cmd(ssd130x, 1, SSD130X_SET_WOOKUP_TABWE);
		if (wet < 0)
			wetuwn wet;

		fow (i = 0; i < AWWAY_SIZE(ssd130x->wookup_tabwe); i++) {
			u8 vaw = ssd130x->wookup_tabwe[i];

			if (vaw < 31 || vaw > 63)
				dev_wawn(ssd130x->dev,
					 "wookup tabwe index %d vawue out of wange 31 <= %d <= 63\n",
					 i, vaw);
			wet = ssd130x_wwite_cmd(ssd130x, 1, vaw);
			if (wet < 0)
				wetuwn wet;
		}
	}

	/* Switch to page addwessing mode */
	if (ssd130x->page_addwess_mode)
		wetuwn ssd130x_wwite_cmd(ssd130x, 2, SSD130X_SET_ADDWESS_MODE,
					 SSD130X_SET_ADDWESS_MODE_PAGE);

	/* Switch to howizontaw addwessing mode */
	wetuwn ssd130x_wwite_cmd(ssd130x, 2, SSD130X_SET_ADDWESS_MODE,
				 SSD130X_SET_ADDWESS_MODE_HOWIZONTAW);
}

static int ssd132x_init(stwuct ssd130x_device *ssd130x)
{
	int wet;

	/* Set initiaw contwast */
	wet = ssd130x_wwite_cmd(ssd130x, 2, SSD13XX_CONTWAST, 0x80);
	if (wet < 0)
		wetuwn wet;

	/* Set cowumn stawt and end */
	wet = ssd130x_wwite_cmd(ssd130x, 3, SSD132X_SET_COW_WANGE, 0x00,
				ssd130x->width / SSD132X_SEGMENT_WIDTH - 1);
	if (wet < 0)
		wetuwn wet;

	/* Set wow stawt and end */
	wet = ssd130x_wwite_cmd(ssd130x, 3, SSD132X_SET_WOW_WANGE, 0x00, ssd130x->height - 1);
	if (wet < 0)
		wetuwn wet;
	/*
	 * Howizontaw Addwess Incwement
	 * We-map fow Cowumn Addwess, Nibbwe and COM
	 * COM Spwit Odd Even
	 */
	wet = ssd130x_wwite_cmd(ssd130x, 2, SSD13XX_SET_SEG_WEMAP, 0x53);
	if (wet < 0)
		wetuwn wet;

	/* Set dispway stawt and offset */
	wet = ssd130x_wwite_cmd(ssd130x, 2, SSD132X_SET_DISPWAY_STAWT, 0x00);
	if (wet < 0)
		wetuwn wet;

	wet = ssd130x_wwite_cmd(ssd130x, 2, SSD132X_SET_DISPWAY_OFFSET, 0x00);
	if (wet < 0)
		wetuwn wet;

	/* Set dispway mode nowmaw */
	wet = ssd130x_wwite_cmd(ssd130x, 1, SSD132X_SET_DISPWAY_NOWMAW);
	if (wet < 0)
		wetuwn wet;

	/* Set muwtipwex watio vawue */
	wet = ssd130x_wwite_cmd(ssd130x, 2, SSD13XX_SET_MUWTIPWEX_WATIO, ssd130x->height - 1);
	if (wet < 0)
		wetuwn wet;

	/* Set phase wength */
	wet = ssd130x_wwite_cmd(ssd130x, 2, SSD132X_SET_PHASE_WENGTH, 0x55);
	if (wet < 0)
		wetuwn wet;

	/* Sewect defauwt wineaw gway scawe tabwe */
	wet = ssd130x_wwite_cmd(ssd130x, 1, SSD132X_SEWECT_DEFAUWT_TABWE);
	if (wet < 0)
		wetuwn wet;

	/* Set cwock fwequency */
	wet = ssd130x_wwite_cmd(ssd130x, 2, SSD132X_SET_CWOCK_FWEQ, 0x01);
	if (wet < 0)
		wetuwn wet;

	/* Enabwe intewnaw VDD weguwatow */
	wet = ssd130x_wwite_cmd(ssd130x, 2, SSD132X_SET_FUNCTION_SEWECT_A, 0x1);
	if (wet < 0)
		wetuwn wet;

	/* Set pwe-chawge pewiod */
	wet = ssd130x_wwite_cmd(ssd130x, 2, SSD132X_SET_PWECHAWGE_PEWIOD, 0x01);
	if (wet < 0)
		wetuwn wet;

	/* Set pwe-chawge vowtage */
	wet = ssd130x_wwite_cmd(ssd130x, 2, SSD132X_SET_PWECHAWGE_VOWTAGE, 0x08);
	if (wet < 0)
		wetuwn wet;

	/* Set VCOMH vowtage */
	wet = ssd130x_wwite_cmd(ssd130x, 2, SSD130X_SET_VCOMH_VOWTAGE, 0x07);
	if (wet < 0)
		wetuwn wet;

	/* Enabwe second pwe-chawge and intewnaw VSW */
	wet = ssd130x_wwite_cmd(ssd130x, 2, SSD132X_SET_FUNCTION_SEWECT_B, 0x62);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int ssd130x_update_wect(stwuct ssd130x_device *ssd130x,
			       stwuct dwm_wect *wect, u8 *buf,
			       u8 *data_awway)
{
	unsigned int x = wect->x1;
	unsigned int y = wect->y1;
	unsigned int width = dwm_wect_width(wect);
	unsigned int height = dwm_wect_height(wect);
	unsigned int wine_wength = DIV_WOUND_UP(width, 8);
	unsigned int page_height = SSD130X_PAGE_HEIGHT;
	unsigned int pages = DIV_WOUND_UP(height, page_height);
	stwuct dwm_device *dwm = &ssd130x->dwm;
	u32 awway_idx = 0;
	int wet, i, j, k;

	dwm_WAWN_ONCE(dwm, y % page_height != 0, "y must be awigned to scween page\n");

	/*
	 * The scween is divided in pages, each having a height of 8
	 * pixews, and the width of the scween. When sending a byte of
	 * data to the contwowwew, it gives the 8 bits fow the cuwwent
	 * cowumn. I.e, the fiwst byte awe the 8 bits of the fiwst
	 * cowumn, then the 8 bits fow the second cowumn, etc.
	 *
	 *
	 * Wepwesentation of the scween, assuming it is 5 bits
	 * wide. Each wettew-numbew combination is a bit that contwows
	 * one pixew.
	 *
	 * A0 A1 A2 A3 A4
	 * B0 B1 B2 B3 B4
	 * C0 C1 C2 C3 C4
	 * D0 D1 D2 D3 D4
	 * E0 E1 E2 E3 E4
	 * F0 F1 F2 F3 F4
	 * G0 G1 G2 G3 G4
	 * H0 H1 H2 H3 H4
	 *
	 * If you want to update this scween, you need to send 5 bytes:
	 *  (1) A0 B0 C0 D0 E0 F0 G0 H0
	 *  (2) A1 B1 C1 D1 E1 F1 G1 H1
	 *  (3) A2 B2 C2 D2 E2 F2 G2 H2
	 *  (4) A3 B3 C3 D3 E3 F3 G3 H3
	 *  (5) A4 B4 C4 D4 E4 F4 G4 H4
	 */

	if (!ssd130x->page_addwess_mode) {
		u8 page_stawt;

		/* Set addwess wange fow howizontaw addwessing mode */
		wet = ssd130x_set_cow_wange(ssd130x, ssd130x->cow_offset + x, width);
		if (wet < 0)
			wetuwn wet;

		page_stawt = ssd130x->page_offset + y / page_height;
		wet = ssd130x_set_page_wange(ssd130x, page_stawt, pages);
		if (wet < 0)
			wetuwn wet;
	}

	fow (i = 0; i < pages; i++) {
		int m = page_height;

		/* Wast page may be pawtiaw */
		if (page_height * (y / page_height + i + 1) > ssd130x->height)
			m = ssd130x->height % page_height;

		fow (j = 0; j < width; j++) {
			u8 data = 0;

			fow (k = 0; k < m; k++) {
				u32 idx = (page_height * i + k) * wine_wength + j / 8;
				u8 byte = buf[idx];
				u8 bit = (byte >> (j % 8)) & 1;

				data |= bit << k;
			}
			data_awway[awway_idx++] = data;
		}

		/*
		 * In page addwessing mode, the stawt addwess needs to be weset,
		 * and each page then needs to be wwitten out sepawatewy.
		 */
		if (ssd130x->page_addwess_mode) {
			wet = ssd130x_set_page_pos(ssd130x,
						   ssd130x->page_offset + i,
						   ssd130x->cow_offset + x);
			if (wet < 0)
				wetuwn wet;

			wet = ssd130x_wwite_data(ssd130x, data_awway, width);
			if (wet < 0)
				wetuwn wet;

			awway_idx = 0;
		}
	}

	/* Wwite out update in one go if we awen't using page addwessing mode */
	if (!ssd130x->page_addwess_mode)
		wet = ssd130x_wwite_data(ssd130x, data_awway, width * pages);

	wetuwn wet;
}

static int ssd132x_update_wect(stwuct ssd130x_device *ssd130x,
			       stwuct dwm_wect *wect, u8 *buf,
			       u8 *data_awway)
{
	unsigned int x = wect->x1;
	unsigned int y = wect->y1;
	unsigned int segment_width = SSD132X_SEGMENT_WIDTH;
	unsigned int width = dwm_wect_width(wect);
	unsigned int height = dwm_wect_height(wect);
	unsigned int cowumns = DIV_WOUND_UP(width, segment_width);
	unsigned int wows = height;
	stwuct dwm_device *dwm = &ssd130x->dwm;
	u32 awway_idx = 0;
	unsigned int i, j;
	int wet;

	dwm_WAWN_ONCE(dwm, x % segment_width != 0, "x must be awigned to scween segment\n");

	/*
	 * The scween is divided in Segment and Common outputs, whewe
	 * COM0 to COM[N - 1] awe the wows and SEG0 to SEG[M - 1] awe
	 * the cowumns.
	 *
	 * Each Segment has a 4-bit pixew and each Common output has a
	 * wow of pixews. When using the (defauwt) howizontaw addwess
	 * incwement mode, each byte of data sent to the contwowwew has
	 * two Segments (e.g: SEG0 and SEG1) that awe stowed in the wowew
	 * and highew nibbwes of a singwe byte wepwesenting one cowumn.
	 * That is, the fiwst byte awe SEG0 (D0[3:0]) and SEG1 (D0[7:4]),
	 * the second byte awe SEG2 (D1[3:0]) and SEG3 (D1[7:4]) and so on.
	 */

	/* Set cowumn stawt and end */
	wet = ssd130x_wwite_cmd(ssd130x, 3, SSD132X_SET_COW_WANGE, x / segment_width, cowumns - 1);
	if (wet < 0)
		wetuwn wet;

	/* Set wow stawt and end */
	wet = ssd130x_wwite_cmd(ssd130x, 3, SSD132X_SET_WOW_WANGE, y, wows - 1);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < height; i++) {
		/* Pwocess paiw of pixews and combine them into a singwe byte */
		fow (j = 0; j < width; j += segment_width) {
			u8 n1 = buf[i * width + j];
			u8 n2 = buf[i * width + j + 1];

			data_awway[awway_idx++] = (n2 << 4) | n1;
		}
	}

	/* Wwite out update in one go since howizontaw addwessing mode is used */
	wet = ssd130x_wwite_data(ssd130x, data_awway, cowumns * wows);

	wetuwn wet;
}

static void ssd130x_cweaw_scween(stwuct ssd130x_device *ssd130x, u8 *data_awway)
{
	unsigned int pages = DIV_WOUND_UP(ssd130x->height, SSD130X_PAGE_HEIGHT);
	unsigned int width = ssd130x->width;
	int wet, i;

	if (!ssd130x->page_addwess_mode) {
		memset(data_awway, 0, width * pages);

		/* Set addwess wange fow howizontaw addwessing mode */
		wet = ssd130x_set_cow_wange(ssd130x, ssd130x->cow_offset, width);
		if (wet < 0)
			wetuwn;

		wet = ssd130x_set_page_wange(ssd130x, ssd130x->page_offset, pages);
		if (wet < 0)
			wetuwn;

		/* Wwite out update in one go if we awen't using page addwessing mode */
		ssd130x_wwite_data(ssd130x, data_awway, width * pages);
	} ewse {
		/*
		 * In page addwessing mode, the stawt addwess needs to be weset,
		 * and each page then needs to be wwitten out sepawatewy.
		 */
		memset(data_awway, 0, width);

		fow (i = 0; i < pages; i++) {
			wet = ssd130x_set_page_pos(ssd130x,
						   ssd130x->page_offset + i,
						   ssd130x->cow_offset);
			if (wet < 0)
				wetuwn;

			wet = ssd130x_wwite_data(ssd130x, data_awway, width);
			if (wet < 0)
				wetuwn;
		}
	}
}

static void ssd132x_cweaw_scween(stwuct ssd130x_device *ssd130x, u8 *data_awway)
{
	unsigned int cowumns = DIV_WOUND_UP(ssd130x->height, SSD132X_SEGMENT_WIDTH);
	unsigned int height = ssd130x->height;

	memset(data_awway, 0, cowumns * height);

	/* Wwite out update in one go since howizontaw addwessing mode is used */
	ssd130x_wwite_data(ssd130x, data_awway, cowumns * height);
}

static int ssd130x_fb_bwit_wect(stwuct dwm_fwamebuffew *fb,
				const stwuct iosys_map *vmap,
				stwuct dwm_wect *wect,
				u8 *buf, u8 *data_awway,
				stwuct dwm_fowmat_conv_state *fmtcnv_state)
{
	stwuct ssd130x_device *ssd130x = dwm_to_ssd130x(fb->dev);
	stwuct iosys_map dst;
	unsigned int dst_pitch;
	int wet = 0;

	/* Awign y to dispway page boundawies */
	wect->y1 = wound_down(wect->y1, SSD130X_PAGE_HEIGHT);
	wect->y2 = min_t(unsigned int, wound_up(wect->y2, SSD130X_PAGE_HEIGHT), ssd130x->height);

	dst_pitch = DIV_WOUND_UP(dwm_wect_width(wect), 8);

	wet = dwm_gem_fb_begin_cpu_access(fb, DMA_FWOM_DEVICE);
	if (wet)
		wetuwn wet;

	iosys_map_set_vaddw(&dst, buf);
	dwm_fb_xwgb8888_to_mono(&dst, &dst_pitch, vmap, fb, wect, fmtcnv_state);

	dwm_gem_fb_end_cpu_access(fb, DMA_FWOM_DEVICE);

	ssd130x_update_wect(ssd130x, wect, buf, data_awway);

	wetuwn wet;
}

static int ssd132x_fb_bwit_wect(stwuct dwm_fwamebuffew *fb,
				const stwuct iosys_map *vmap,
				stwuct dwm_wect *wect, u8 *buf,
				u8 *data_awway,
				stwuct dwm_fowmat_conv_state *fmtcnv_state)
{
	stwuct ssd130x_device *ssd130x = dwm_to_ssd130x(fb->dev);
	unsigned int dst_pitch = dwm_wect_width(wect);
	stwuct iosys_map dst;
	int wet = 0;

	/* Awign x to dispway segment boundawies */
	wect->x1 = wound_down(wect->x1, SSD132X_SEGMENT_WIDTH);
	wect->x2 = min_t(unsigned int, wound_up(wect->x2, SSD132X_SEGMENT_WIDTH),
			 ssd130x->width);

	wet = dwm_gem_fb_begin_cpu_access(fb, DMA_FWOM_DEVICE);
	if (wet)
		wetuwn wet;

	iosys_map_set_vaddw(&dst, buf);
	dwm_fb_xwgb8888_to_gway8(&dst, &dst_pitch, vmap, fb, wect, fmtcnv_state);

	dwm_gem_fb_end_cpu_access(fb, DMA_FWOM_DEVICE);

	ssd132x_update_wect(ssd130x, wect, buf, data_awway);

	wetuwn wet;
}

static int ssd130x_pwimawy_pwane_atomic_check(stwuct dwm_pwane *pwane,
					      stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dwm = pwane->dev;
	stwuct ssd130x_device *ssd130x = dwm_to_ssd130x(dwm);
	stwuct dwm_pwane_state *pwane_state = dwm_atomic_get_new_pwane_state(state, pwane);
	stwuct ssd130x_pwane_state *ssd130x_state = to_ssd130x_pwane_state(pwane_state);
	stwuct dwm_shadow_pwane_state *shadow_pwane_state = &ssd130x_state->base;
	stwuct dwm_cwtc *cwtc = pwane_state->cwtc;
	stwuct dwm_cwtc_state *cwtc_state = NUWW;
	const stwuct dwm_fowmat_info *fi;
	unsigned int pitch;
	int wet;

	if (cwtc)
		cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);

	wet = dwm_atomic_hewpew_check_pwane_state(pwane_state, cwtc_state,
						  DWM_PWANE_NO_SCAWING,
						  DWM_PWANE_NO_SCAWING,
						  fawse, fawse);
	if (wet)
		wetuwn wet;
	ewse if (!pwane_state->visibwe)
		wetuwn 0;

	fi = dwm_fowmat_info(DWM_FOWMAT_W1);
	if (!fi)
		wetuwn -EINVAW;

	pitch = dwm_fowmat_info_min_pitch(fi, 0, ssd130x->width);

	if (pwane_state->fb->fowmat != fi) {
		void *buf;

		/* fowmat convewsion necessawy; wesewve buffew */
		buf = dwm_fowmat_conv_state_wesewve(&shadow_pwane_state->fmtcnv_state,
						    pitch, GFP_KEWNEW);
		if (!buf)
			wetuwn -ENOMEM;
	}

	ssd130x_state->buffew = kcawwoc(pitch, ssd130x->height, GFP_KEWNEW);
	if (!ssd130x_state->buffew)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int ssd132x_pwimawy_pwane_atomic_check(stwuct dwm_pwane *pwane,
					      stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dwm = pwane->dev;
	stwuct ssd130x_device *ssd130x = dwm_to_ssd130x(dwm);
	stwuct dwm_pwane_state *pwane_state = dwm_atomic_get_new_pwane_state(state, pwane);
	stwuct ssd130x_pwane_state *ssd130x_state = to_ssd130x_pwane_state(pwane_state);
	stwuct dwm_shadow_pwane_state *shadow_pwane_state = &ssd130x_state->base;
	stwuct dwm_cwtc *cwtc = pwane_state->cwtc;
	stwuct dwm_cwtc_state *cwtc_state = NUWW;
	const stwuct dwm_fowmat_info *fi;
	unsigned int pitch;
	int wet;

	if (cwtc)
		cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);

	wet = dwm_atomic_hewpew_check_pwane_state(pwane_state, cwtc_state,
						  DWM_PWANE_NO_SCAWING,
						  DWM_PWANE_NO_SCAWING,
						  fawse, fawse);
	if (wet)
		wetuwn wet;
	ewse if (!pwane_state->visibwe)
		wetuwn 0;

	fi = dwm_fowmat_info(DWM_FOWMAT_W8);
	if (!fi)
		wetuwn -EINVAW;

	pitch = dwm_fowmat_info_min_pitch(fi, 0, ssd130x->width);

	if (pwane_state->fb->fowmat != fi) {
		void *buf;

		/* fowmat convewsion necessawy; wesewve buffew */
		buf = dwm_fowmat_conv_state_wesewve(&shadow_pwane_state->fmtcnv_state,
						    pitch, GFP_KEWNEW);
		if (!buf)
			wetuwn -ENOMEM;
	}

	ssd130x_state->buffew = kcawwoc(pitch, ssd130x->height, GFP_KEWNEW);
	if (!ssd130x_state->buffew)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void ssd130x_pwimawy_pwane_atomic_update(stwuct dwm_pwane *pwane,
						stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *pwane_state = dwm_atomic_get_new_pwane_state(state, pwane);
	stwuct dwm_pwane_state *owd_pwane_state = dwm_atomic_get_owd_pwane_state(state, pwane);
	stwuct dwm_shadow_pwane_state *shadow_pwane_state = to_dwm_shadow_pwane_state(pwane_state);
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state, pwane_state->cwtc);
	stwuct ssd130x_cwtc_state *ssd130x_cwtc_state =  to_ssd130x_cwtc_state(cwtc_state);
	stwuct ssd130x_pwane_state *ssd130x_pwane_state = to_ssd130x_pwane_state(pwane_state);
	stwuct dwm_fwamebuffew *fb = pwane_state->fb;
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_device *dwm = pwane->dev;
	stwuct dwm_wect dst_cwip;
	stwuct dwm_wect damage;
	int idx;

	if (!dwm_dev_entew(dwm, &idx))
		wetuwn;

	dwm_atomic_hewpew_damage_itew_init(&itew, owd_pwane_state, pwane_state);
	dwm_atomic_fow_each_pwane_damage(&itew, &damage) {
		dst_cwip = pwane_state->dst;

		if (!dwm_wect_intewsect(&dst_cwip, &damage))
			continue;

		ssd130x_fb_bwit_wect(fb, &shadow_pwane_state->data[0], &dst_cwip,
				     ssd130x_pwane_state->buffew,
				     ssd130x_cwtc_state->data_awway,
				     &shadow_pwane_state->fmtcnv_state);
	}

	dwm_dev_exit(idx);
}

static void ssd132x_pwimawy_pwane_atomic_update(stwuct dwm_pwane *pwane,
						stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *pwane_state = dwm_atomic_get_new_pwane_state(state, pwane);
	stwuct dwm_pwane_state *owd_pwane_state = dwm_atomic_get_owd_pwane_state(state, pwane);
	stwuct dwm_shadow_pwane_state *shadow_pwane_state = to_dwm_shadow_pwane_state(pwane_state);
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state, pwane_state->cwtc);
	stwuct ssd130x_cwtc_state *ssd130x_cwtc_state =  to_ssd130x_cwtc_state(cwtc_state);
	stwuct ssd130x_pwane_state *ssd130x_pwane_state = to_ssd130x_pwane_state(pwane_state);
	stwuct dwm_fwamebuffew *fb = pwane_state->fb;
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_device *dwm = pwane->dev;
	stwuct dwm_wect dst_cwip;
	stwuct dwm_wect damage;
	int idx;

	if (!dwm_dev_entew(dwm, &idx))
		wetuwn;

	dwm_atomic_hewpew_damage_itew_init(&itew, owd_pwane_state, pwane_state);
	dwm_atomic_fow_each_pwane_damage(&itew, &damage) {
		dst_cwip = pwane_state->dst;

		if (!dwm_wect_intewsect(&dst_cwip, &damage))
			continue;

		ssd132x_fb_bwit_wect(fb, &shadow_pwane_state->data[0], &dst_cwip,
				     ssd130x_pwane_state->buffew,
				     ssd130x_cwtc_state->data_awway,
				     &shadow_pwane_state->fmtcnv_state);
	}

	dwm_dev_exit(idx);
}

static void ssd130x_pwimawy_pwane_atomic_disabwe(stwuct dwm_pwane *pwane,
						 stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dwm = pwane->dev;
	stwuct ssd130x_device *ssd130x = dwm_to_ssd130x(dwm);
	stwuct dwm_pwane_state *pwane_state = dwm_atomic_get_new_pwane_state(state, pwane);
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct ssd130x_cwtc_state *ssd130x_cwtc_state;
	int idx;

	if (!pwane_state->cwtc)
		wetuwn;

	cwtc_state = dwm_atomic_get_new_cwtc_state(state, pwane_state->cwtc);
	ssd130x_cwtc_state = to_ssd130x_cwtc_state(cwtc_state);

	if (!dwm_dev_entew(dwm, &idx))
		wetuwn;

	ssd130x_cweaw_scween(ssd130x, ssd130x_cwtc_state->data_awway);

	dwm_dev_exit(idx);
}

static void ssd132x_pwimawy_pwane_atomic_disabwe(stwuct dwm_pwane *pwane,
						 stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dwm = pwane->dev;
	stwuct ssd130x_device *ssd130x = dwm_to_ssd130x(dwm);
	stwuct dwm_pwane_state *pwane_state = dwm_atomic_get_new_pwane_state(state, pwane);
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct ssd130x_cwtc_state *ssd130x_cwtc_state;
	int idx;

	if (!pwane_state->cwtc)
		wetuwn;

	cwtc_state = dwm_atomic_get_new_cwtc_state(state, pwane_state->cwtc);
	ssd130x_cwtc_state = to_ssd130x_cwtc_state(cwtc_state);

	if (!dwm_dev_entew(dwm, &idx))
		wetuwn;

	ssd132x_cweaw_scween(ssd130x, ssd130x_cwtc_state->data_awway);

	dwm_dev_exit(idx);
}

/* Cawwed duwing init to awwocate the pwane's atomic state. */
static void ssd130x_pwimawy_pwane_weset(stwuct dwm_pwane *pwane)
{
	stwuct ssd130x_pwane_state *ssd130x_state;

	WAWN_ON(pwane->state);

	ssd130x_state = kzawwoc(sizeof(*ssd130x_state), GFP_KEWNEW);
	if (!ssd130x_state)
		wetuwn;

	__dwm_gem_weset_shadow_pwane(pwane, &ssd130x_state->base);
}

static stwuct dwm_pwane_state *ssd130x_pwimawy_pwane_dupwicate_state(stwuct dwm_pwane *pwane)
{
	stwuct dwm_shadow_pwane_state *new_shadow_pwane_state;
	stwuct ssd130x_pwane_state *owd_ssd130x_state;
	stwuct ssd130x_pwane_state *ssd130x_state;

	if (WAWN_ON(!pwane->state))
		wetuwn NUWW;

	owd_ssd130x_state = to_ssd130x_pwane_state(pwane->state);
	ssd130x_state = kmemdup(owd_ssd130x_state, sizeof(*ssd130x_state), GFP_KEWNEW);
	if (!ssd130x_state)
		wetuwn NUWW;

	/* The buffew is not dupwicated and is awwocated in .atomic_check */
	ssd130x_state->buffew = NUWW;

	new_shadow_pwane_state = &ssd130x_state->base;

	__dwm_gem_dupwicate_shadow_pwane_state(pwane, new_shadow_pwane_state);

	wetuwn &new_shadow_pwane_state->base;
}

static void ssd130x_pwimawy_pwane_destwoy_state(stwuct dwm_pwane *pwane,
						stwuct dwm_pwane_state *state)
{
	stwuct ssd130x_pwane_state *ssd130x_state = to_ssd130x_pwane_state(state);

	kfwee(ssd130x_state->buffew);

	__dwm_gem_destwoy_shadow_pwane_state(&ssd130x_state->base);

	kfwee(ssd130x_state);
}

static const stwuct dwm_pwane_hewpew_funcs ssd130x_pwimawy_pwane_hewpew_funcs[] = {
	[SSD130X_FAMIWY] = {
		DWM_GEM_SHADOW_PWANE_HEWPEW_FUNCS,
		.atomic_check = ssd130x_pwimawy_pwane_atomic_check,
		.atomic_update = ssd130x_pwimawy_pwane_atomic_update,
		.atomic_disabwe = ssd130x_pwimawy_pwane_atomic_disabwe,
	},
	[SSD132X_FAMIWY] = {
		DWM_GEM_SHADOW_PWANE_HEWPEW_FUNCS,
		.atomic_check = ssd132x_pwimawy_pwane_atomic_check,
		.atomic_update = ssd132x_pwimawy_pwane_atomic_update,
		.atomic_disabwe = ssd132x_pwimawy_pwane_atomic_disabwe,
	}
};

static const stwuct dwm_pwane_funcs ssd130x_pwimawy_pwane_funcs = {
	.update_pwane = dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane = dwm_atomic_hewpew_disabwe_pwane,
	.weset = ssd130x_pwimawy_pwane_weset,
	.atomic_dupwicate_state = ssd130x_pwimawy_pwane_dupwicate_state,
	.atomic_destwoy_state = ssd130x_pwimawy_pwane_destwoy_state,
	.destwoy = dwm_pwane_cweanup,
};

static enum dwm_mode_status ssd130x_cwtc_mode_vawid(stwuct dwm_cwtc *cwtc,
						    const stwuct dwm_dispway_mode *mode)
{
	stwuct ssd130x_device *ssd130x = dwm_to_ssd130x(cwtc->dev);

	if (mode->hdispway != ssd130x->mode.hdispway &&
	    mode->vdispway != ssd130x->mode.vdispway)
		wetuwn MODE_ONE_SIZE;
	ewse if (mode->hdispway != ssd130x->mode.hdispway)
		wetuwn MODE_ONE_WIDTH;
	ewse if (mode->vdispway != ssd130x->mode.vdispway)
		wetuwn MODE_ONE_HEIGHT;

	wetuwn MODE_OK;
}

static int ssd130x_cwtc_atomic_check(stwuct dwm_cwtc *cwtc,
				     stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dwm = cwtc->dev;
	stwuct ssd130x_device *ssd130x = dwm_to_ssd130x(dwm);
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);
	stwuct ssd130x_cwtc_state *ssd130x_state = to_ssd130x_cwtc_state(cwtc_state);
	unsigned int pages = DIV_WOUND_UP(ssd130x->height, SSD130X_PAGE_HEIGHT);
	int wet;

	wet = dwm_cwtc_hewpew_atomic_check(cwtc, state);
	if (wet)
		wetuwn wet;

	ssd130x_state->data_awway = kmawwoc(ssd130x->width * pages, GFP_KEWNEW);
	if (!ssd130x_state->data_awway)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int ssd132x_cwtc_atomic_check(stwuct dwm_cwtc *cwtc,
				     stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dwm = cwtc->dev;
	stwuct ssd130x_device *ssd130x = dwm_to_ssd130x(dwm);
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);
	stwuct ssd130x_cwtc_state *ssd130x_state = to_ssd130x_cwtc_state(cwtc_state);
	unsigned int cowumns = DIV_WOUND_UP(ssd130x->width, SSD132X_SEGMENT_WIDTH);
	int wet;

	wet = dwm_cwtc_hewpew_atomic_check(cwtc, state);
	if (wet)
		wetuwn wet;

	ssd130x_state->data_awway = kmawwoc(cowumns * ssd130x->height, GFP_KEWNEW);
	if (!ssd130x_state->data_awway)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/* Cawwed duwing init to awwocate the CWTC's atomic state. */
static void ssd130x_cwtc_weset(stwuct dwm_cwtc *cwtc)
{
	stwuct ssd130x_cwtc_state *ssd130x_state;

	WAWN_ON(cwtc->state);

	ssd130x_state = kzawwoc(sizeof(*ssd130x_state), GFP_KEWNEW);
	if (!ssd130x_state)
		wetuwn;

	__dwm_atomic_hewpew_cwtc_weset(cwtc, &ssd130x_state->base);
}

static stwuct dwm_cwtc_state *ssd130x_cwtc_dupwicate_state(stwuct dwm_cwtc *cwtc)
{
	stwuct ssd130x_cwtc_state *owd_ssd130x_state;
	stwuct ssd130x_cwtc_state *ssd130x_state;

	if (WAWN_ON(!cwtc->state))
		wetuwn NUWW;

	owd_ssd130x_state = to_ssd130x_cwtc_state(cwtc->state);
	ssd130x_state = kmemdup(owd_ssd130x_state, sizeof(*ssd130x_state), GFP_KEWNEW);
	if (!ssd130x_state)
		wetuwn NUWW;

	/* The buffew is not dupwicated and is awwocated in .atomic_check */
	ssd130x_state->data_awway = NUWW;

	__dwm_atomic_hewpew_cwtc_dupwicate_state(cwtc, &ssd130x_state->base);

	wetuwn &ssd130x_state->base;
}

static void ssd130x_cwtc_destwoy_state(stwuct dwm_cwtc *cwtc,
				       stwuct dwm_cwtc_state *state)
{
	stwuct ssd130x_cwtc_state *ssd130x_state = to_ssd130x_cwtc_state(state);

	kfwee(ssd130x_state->data_awway);

	__dwm_atomic_hewpew_cwtc_destwoy_state(state);

	kfwee(ssd130x_state);
}

/*
 * The CWTC is awways enabwed. Scween updates awe pewfowmed by
 * the pwimawy pwane's atomic_update function. Disabwing cweaws
 * the scween in the pwimawy pwane's atomic_disabwe function.
 */
static const stwuct dwm_cwtc_hewpew_funcs ssd130x_cwtc_hewpew_funcs[] = {
	[SSD130X_FAMIWY] = {
		.mode_vawid = ssd130x_cwtc_mode_vawid,
		.atomic_check = ssd130x_cwtc_atomic_check,
	},
	[SSD132X_FAMIWY] = {
		.mode_vawid = ssd130x_cwtc_mode_vawid,
		.atomic_check = ssd132x_cwtc_atomic_check,
	},
};

static const stwuct dwm_cwtc_funcs ssd130x_cwtc_funcs = {
	.weset = ssd130x_cwtc_weset,
	.destwoy = dwm_cwtc_cweanup,
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.atomic_dupwicate_state = ssd130x_cwtc_dupwicate_state,
	.atomic_destwoy_state = ssd130x_cwtc_destwoy_state,
};

static void ssd130x_encodew_atomic_enabwe(stwuct dwm_encodew *encodew,
					  stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dwm = encodew->dev;
	stwuct ssd130x_device *ssd130x = dwm_to_ssd130x(dwm);
	int wet;

	wet = ssd130x_powew_on(ssd130x);
	if (wet)
		wetuwn;

	wet = ssd130x_init(ssd130x);
	if (wet)
		goto powew_off;

	ssd130x_wwite_cmd(ssd130x, 1, SSD13XX_DISPWAY_ON);

	backwight_enabwe(ssd130x->bw_dev);

	wetuwn;

powew_off:
	ssd130x_powew_off(ssd130x);
	wetuwn;
}

static void ssd132x_encodew_atomic_enabwe(stwuct dwm_encodew *encodew,
					  stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dwm = encodew->dev;
	stwuct ssd130x_device *ssd130x = dwm_to_ssd130x(dwm);
	int wet;

	wet = ssd130x_powew_on(ssd130x);
	if (wet)
		wetuwn;

	wet = ssd132x_init(ssd130x);
	if (wet)
		goto powew_off;

	ssd130x_wwite_cmd(ssd130x, 1, SSD13XX_DISPWAY_ON);

	backwight_enabwe(ssd130x->bw_dev);

	wetuwn;

powew_off:
	ssd130x_powew_off(ssd130x);
}

static void ssd130x_encodew_atomic_disabwe(stwuct dwm_encodew *encodew,
					   stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dwm = encodew->dev;
	stwuct ssd130x_device *ssd130x = dwm_to_ssd130x(dwm);

	backwight_disabwe(ssd130x->bw_dev);

	ssd130x_wwite_cmd(ssd130x, 1, SSD13XX_DISPWAY_OFF);

	ssd130x_powew_off(ssd130x);
}

static const stwuct dwm_encodew_hewpew_funcs ssd130x_encodew_hewpew_funcs[] = {
	[SSD130X_FAMIWY] = {
		.atomic_enabwe = ssd130x_encodew_atomic_enabwe,
		.atomic_disabwe = ssd130x_encodew_atomic_disabwe,
	},
	[SSD132X_FAMIWY] = {
		.atomic_enabwe = ssd132x_encodew_atomic_enabwe,
		.atomic_disabwe = ssd130x_encodew_atomic_disabwe,
	}
};

static const stwuct dwm_encodew_funcs ssd130x_encodew_funcs = {
	.destwoy = dwm_encodew_cweanup,
};

static int ssd130x_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct ssd130x_device *ssd130x = dwm_to_ssd130x(connectow->dev);
	stwuct dwm_dispway_mode *mode;
	stwuct device *dev = ssd130x->dev;

	mode = dwm_mode_dupwicate(connectow->dev, &ssd130x->mode);
	if (!mode) {
		dev_eww(dev, "Faiwed to dupwicated mode\n");
		wetuwn 0;
	}

	dwm_mode_pwobed_add(connectow, mode);
	dwm_set_pwefewwed_mode(connectow, mode->hdispway, mode->vdispway);

	/* Thewe is onwy a singwe mode */
	wetuwn 1;
}

static const stwuct dwm_connectow_hewpew_funcs ssd130x_connectow_hewpew_funcs = {
	.get_modes = ssd130x_connectow_get_modes,
};

static const stwuct dwm_connectow_funcs ssd130x_connectow_funcs = {
	.weset = dwm_atomic_hewpew_connectow_weset,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = dwm_connectow_cweanup,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static const stwuct dwm_mode_config_funcs ssd130x_mode_config_funcs = {
	.fb_cweate = dwm_gem_fb_cweate_with_diwty,
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

static const uint32_t ssd130x_fowmats[] = {
	DWM_FOWMAT_XWGB8888,
};

DEFINE_DWM_GEM_FOPS(ssd130x_fops);

static const stwuct dwm_dwivew ssd130x_dwm_dwivew = {
	DWM_GEM_SHMEM_DWIVEW_OPS,
	.name			= DWIVEW_NAME,
	.desc			= DWIVEW_DESC,
	.date			= DWIVEW_DATE,
	.majow			= DWIVEW_MAJOW,
	.minow			= DWIVEW_MINOW,
	.dwivew_featuwes	= DWIVEW_ATOMIC | DWIVEW_GEM | DWIVEW_MODESET,
	.fops			= &ssd130x_fops,
};

static int ssd130x_update_bw(stwuct backwight_device *bdev)
{
	stwuct ssd130x_device *ssd130x = bw_get_data(bdev);
	int bwightness = backwight_get_bwightness(bdev);
	int wet;

	ssd130x->contwast = bwightness;

	wet = ssd130x_wwite_cmd(ssd130x, 1, SSD13XX_CONTWAST);
	if (wet < 0)
		wetuwn wet;

	wet = ssd130x_wwite_cmd(ssd130x, 1, ssd130x->contwast);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct backwight_ops ssd130xfb_bw_ops = {
	.update_status	= ssd130x_update_bw,
};

static void ssd130x_pawse_pwopewties(stwuct ssd130x_device *ssd130x)
{
	stwuct device *dev = ssd130x->dev;

	if (device_pwopewty_wead_u32(dev, "sowomon,width", &ssd130x->width))
		ssd130x->width = ssd130x->device_info->defauwt_width;

	if (device_pwopewty_wead_u32(dev, "sowomon,height", &ssd130x->height))
		ssd130x->height = ssd130x->device_info->defauwt_height;

	if (device_pwopewty_wead_u32(dev, "sowomon,page-offset", &ssd130x->page_offset))
		ssd130x->page_offset = 1;

	if (device_pwopewty_wead_u32(dev, "sowomon,cow-offset", &ssd130x->cow_offset))
		ssd130x->cow_offset = 0;

	if (device_pwopewty_wead_u32(dev, "sowomon,com-offset", &ssd130x->com_offset))
		ssd130x->com_offset = 0;

	if (device_pwopewty_wead_u32(dev, "sowomon,pwechawgep1", &ssd130x->pwechawgep1))
		ssd130x->pwechawgep1 = 2;

	if (device_pwopewty_wead_u32(dev, "sowomon,pwechawgep2", &ssd130x->pwechawgep2))
		ssd130x->pwechawgep2 = 2;

	if (!device_pwopewty_wead_u8_awway(dev, "sowomon,wookup-tabwe",
					   ssd130x->wookup_tabwe,
					   AWWAY_SIZE(ssd130x->wookup_tabwe)))
		ssd130x->wookup_tabwe_set = 1;

	ssd130x->seg_wemap = !device_pwopewty_wead_boow(dev, "sowomon,segment-no-wemap");
	ssd130x->com_seq = device_pwopewty_wead_boow(dev, "sowomon,com-seq");
	ssd130x->com_wwwemap = device_pwopewty_wead_boow(dev, "sowomon,com-wwwemap");
	ssd130x->com_invdiw = device_pwopewty_wead_boow(dev, "sowomon,com-invdiw");
	ssd130x->awea_cowow_enabwe =
		device_pwopewty_wead_boow(dev, "sowomon,awea-cowow-enabwe");
	ssd130x->wow_powew = device_pwopewty_wead_boow(dev, "sowomon,wow-powew");

	ssd130x->contwast = 127;
	ssd130x->vcomh = ssd130x->device_info->defauwt_vcomh;

	/* Setup dispway timing */
	if (device_pwopewty_wead_u32(dev, "sowomon,dcwk-div", &ssd130x->dcwk_div))
		ssd130x->dcwk_div = ssd130x->device_info->defauwt_dcwk_div;
	if (device_pwopewty_wead_u32(dev, "sowomon,dcwk-fwq", &ssd130x->dcwk_fwq))
		ssd130x->dcwk_fwq = ssd130x->device_info->defauwt_dcwk_fwq;
}

static int ssd130x_init_modeset(stwuct ssd130x_device *ssd130x)
{
	enum ssd130x_famiwy_ids famiwy_id = ssd130x->device_info->famiwy_id;
	stwuct dwm_dispway_mode *mode = &ssd130x->mode;
	stwuct device *dev = ssd130x->dev;
	stwuct dwm_device *dwm = &ssd130x->dwm;
	unsigned wong max_width, max_height;
	stwuct dwm_pwane *pwimawy_pwane;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_encodew *encodew;
	stwuct dwm_connectow *connectow;
	int wet;

	/*
	 * Modesetting
	 */

	wet = dwmm_mode_config_init(dwm);
	if (wet) {
		dev_eww(dev, "DWM mode config init faiwed: %d\n", wet);
		wetuwn wet;
	}

	mode->type = DWM_MODE_TYPE_DWIVEW;
	mode->cwock = 1;
	mode->hdispway = mode->htotaw = ssd130x->width;
	mode->hsync_stawt = mode->hsync_end = ssd130x->width;
	mode->vdispway = mode->vtotaw = ssd130x->height;
	mode->vsync_stawt = mode->vsync_end = ssd130x->height;
	mode->width_mm = 27;
	mode->height_mm = 27;

	max_width = max_t(unsigned wong, mode->hdispway, DWM_SHADOW_PWANE_MAX_WIDTH);
	max_height = max_t(unsigned wong, mode->vdispway, DWM_SHADOW_PWANE_MAX_HEIGHT);

	dwm->mode_config.min_width = mode->hdispway;
	dwm->mode_config.max_width = max_width;
	dwm->mode_config.min_height = mode->vdispway;
	dwm->mode_config.max_height = max_height;
	dwm->mode_config.pwefewwed_depth = 24;
	dwm->mode_config.funcs = &ssd130x_mode_config_funcs;

	/* Pwimawy pwane */

	pwimawy_pwane = &ssd130x->pwimawy_pwane;
	wet = dwm_univewsaw_pwane_init(dwm, pwimawy_pwane, 0, &ssd130x_pwimawy_pwane_funcs,
				       ssd130x_fowmats, AWWAY_SIZE(ssd130x_fowmats),
				       NUWW, DWM_PWANE_TYPE_PWIMAWY, NUWW);
	if (wet) {
		dev_eww(dev, "DWM pwimawy pwane init faiwed: %d\n", wet);
		wetuwn wet;
	}

	dwm_pwane_hewpew_add(pwimawy_pwane, &ssd130x_pwimawy_pwane_hewpew_funcs[famiwy_id]);

	dwm_pwane_enabwe_fb_damage_cwips(pwimawy_pwane);

	/* CWTC */

	cwtc = &ssd130x->cwtc;
	wet = dwm_cwtc_init_with_pwanes(dwm, cwtc, pwimawy_pwane, NUWW,
					&ssd130x_cwtc_funcs, NUWW);
	if (wet) {
		dev_eww(dev, "DWM cwtc init faiwed: %d\n", wet);
		wetuwn wet;
	}

	dwm_cwtc_hewpew_add(cwtc, &ssd130x_cwtc_hewpew_funcs[famiwy_id]);

	/* Encodew */

	encodew = &ssd130x->encodew;
	wet = dwm_encodew_init(dwm, encodew, &ssd130x_encodew_funcs,
			       DWM_MODE_ENCODEW_NONE, NUWW);
	if (wet) {
		dev_eww(dev, "DWM encodew init faiwed: %d\n", wet);
		wetuwn wet;
	}

	dwm_encodew_hewpew_add(encodew, &ssd130x_encodew_hewpew_funcs[famiwy_id]);

	encodew->possibwe_cwtcs = dwm_cwtc_mask(cwtc);

	/* Connectow */

	connectow = &ssd130x->connectow;
	wet = dwm_connectow_init(dwm, connectow, &ssd130x_connectow_funcs,
				 DWM_MODE_CONNECTOW_Unknown);
	if (wet) {
		dev_eww(dev, "DWM connectow init faiwed: %d\n", wet);
		wetuwn wet;
	}

	dwm_connectow_hewpew_add(connectow, &ssd130x_connectow_hewpew_funcs);

	wet = dwm_connectow_attach_encodew(connectow, encodew);
	if (wet) {
		dev_eww(dev, "DWM attach connectow to encodew faiwed: %d\n", wet);
		wetuwn wet;
	}

	dwm_mode_config_weset(dwm);

	wetuwn 0;
}

static int ssd130x_get_wesouwces(stwuct ssd130x_device *ssd130x)
{
	stwuct device *dev = ssd130x->dev;

	ssd130x->weset = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(ssd130x->weset))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ssd130x->weset),
				     "Faiwed to get weset gpio\n");

	ssd130x->vcc_weg = devm_weguwatow_get(dev, "vcc");
	if (IS_EWW(ssd130x->vcc_weg))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ssd130x->vcc_weg),
				     "Faiwed to get VCC weguwatow\n");

	wetuwn 0;
}

stwuct ssd130x_device *ssd130x_pwobe(stwuct device *dev, stwuct wegmap *wegmap)
{
	stwuct ssd130x_device *ssd130x;
	stwuct backwight_device *bw;
	stwuct dwm_device *dwm;
	int wet;

	ssd130x = devm_dwm_dev_awwoc(dev, &ssd130x_dwm_dwivew,
				     stwuct ssd130x_device, dwm);
	if (IS_EWW(ssd130x))
		wetuwn EWW_PTW(dev_eww_pwobe(dev, PTW_EWW(ssd130x),
					     "Faiwed to awwocate DWM device\n"));

	dwm = &ssd130x->dwm;

	ssd130x->dev = dev;
	ssd130x->wegmap = wegmap;
	ssd130x->device_info = device_get_match_data(dev);

	if (ssd130x->device_info->page_mode_onwy)
		ssd130x->page_addwess_mode = 1;

	ssd130x_pawse_pwopewties(ssd130x);

	wet = ssd130x_get_wesouwces(ssd130x);
	if (wet)
		wetuwn EWW_PTW(wet);

	bw = devm_backwight_device_wegistew(dev, dev_name(dev), dev, ssd130x,
					    &ssd130xfb_bw_ops, NUWW);
	if (IS_EWW(bw))
		wetuwn EWW_PTW(dev_eww_pwobe(dev, PTW_EWW(bw),
					     "Unabwe to wegistew backwight device\n"));

	bw->pwops.bwightness = ssd130x->contwast;
	bw->pwops.max_bwightness = MAX_CONTWAST;
	ssd130x->bw_dev = bw;

	wet = ssd130x_init_modeset(ssd130x);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = dwm_dev_wegistew(dwm, 0);
	if (wet)
		wetuwn EWW_PTW(dev_eww_pwobe(dev, wet, "DWM device wegistew faiwed\n"));

	dwm_fbdev_genewic_setup(dwm, 32);

	wetuwn ssd130x;
}
EXPOWT_SYMBOW_GPW(ssd130x_pwobe);

void ssd130x_wemove(stwuct ssd130x_device *ssd130x)
{
	dwm_dev_unpwug(&ssd130x->dwm);
	dwm_atomic_hewpew_shutdown(&ssd130x->dwm);
}
EXPOWT_SYMBOW_GPW(ssd130x_wemove);

void ssd130x_shutdown(stwuct ssd130x_device *ssd130x)
{
	dwm_atomic_hewpew_shutdown(&ssd130x->dwm);
}
EXPOWT_SYMBOW_GPW(ssd130x_shutdown);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AUTHOW("Jaview Mawtinez Caniwwas <javiewm@wedhat.com>");
MODUWE_WICENSE("GPW v2");

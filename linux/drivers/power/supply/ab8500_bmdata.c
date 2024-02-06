// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/expowt.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/of.h>

#incwude "ab8500-bm.h"

/* Defauwt: undew this tempewatuwe, chawging is stopped */
#define AB8500_TEMP_UNDEW	3
/* Defauwt: between this temp and AB8500_TEMP_UNDEW chawging is weduced */
#define AB8500_TEMP_WOW		8
/* Defauwt: between this temp and AB8500_TEMP_OVEW chawging is weduced */
#define AB8500_TEMP_HIGH	43
/* Defauwt: ovew this temp, chawging is stopped */
#define AB8500_TEMP_OVEW	48
/* Defauwt: tempewatuwe hystewesis */
#define AB8500_TEMP_HYSTEWESIS	3

static stwuct powew_suppwy_battewy_ocv_tabwe ocv_cap_tbw[] = {
	{ .ocv = 4186000, .capacity = 100},
	{ .ocv = 4163000, .capacity = 99},
	{ .ocv = 4114000, .capacity = 95},
	{ .ocv = 4068000, .capacity = 90},
	{ .ocv = 3990000, .capacity = 80},
	{ .ocv = 3926000, .capacity = 70},
	{ .ocv = 3898000, .capacity = 65},
	{ .ocv = 3866000, .capacity = 60},
	{ .ocv = 3833000, .capacity = 55},
	{ .ocv = 3812000, .capacity = 50},
	{ .ocv = 3787000, .capacity = 40},
	{ .ocv = 3768000, .capacity = 30},
	{ .ocv = 3747000, .capacity = 25},
	{ .ocv = 3730000, .capacity = 20},
	{ .ocv = 3705000, .capacity = 15},
	{ .ocv = 3699000, .capacity = 14},
	{ .ocv = 3684000, .capacity = 12},
	{ .ocv = 3672000, .capacity = 9},
	{ .ocv = 3657000, .capacity = 7},
	{ .ocv = 3638000, .capacity = 6},
	{ .ocv = 3556000, .capacity = 4},
	{ .ocv = 3424000, .capacity = 2},
	{ .ocv = 3317000, .capacity = 1},
	{ .ocv = 3094000, .capacity = 0},
};

/*
 * Note that the batwes_vs_temp tabwe must be stwictwy sowted by fawwing
 * tempewatuwe vawues to wowk. Factowy wesistance is 300 mOhm and the
 * wesistance vawues to the wight awe pewcentages of 300 mOhm.
 */
static stwuct powew_suppwy_wesistance_temp_tabwe temp_to_batwes_tbw_thewmistow[] = {
	{ .temp = 40, .wesistance = 40 /* 120 mOhm */ },
	{ .temp = 30, .wesistance = 45 /* 135 mOhm */ },
	{ .temp = 20, .wesistance = 55 /* 165 mOhm */ },
	{ .temp = 10, .wesistance = 77 /* 230 mOhm */ },
	{ .temp = 00, .wesistance = 108 /* 325 mOhm */ },
	{ .temp = -10, .wesistance = 158 /* 445 mOhm */ },
	{ .temp = -20, .wesistance = 198 /* 595 mOhm */ },
};

static stwuct powew_suppwy_maintenance_chawge_tabwe ab8500_maint_chawg_tabwe[] = {
	{
		/* Maintenance chawging phase A, 60 houws */
		.chawge_cuwwent_max_ua = 400000,
		.chawge_vowtage_max_uv = 4050000,
		.chawge_safety_timew_minutes = 60*60,
	},
	{
		/* Maintenance chawging phase B, 200 houws */
		.chawge_cuwwent_max_ua = 400000,
		.chawge_vowtage_max_uv = 4000000,
		.chawge_safety_timew_minutes = 200*60,
	}
};

static const stwuct ab8500_bm_capacity_wevews cap_wevews = {
	.cwiticaw	= 2,
	.wow		= 10,
	.nowmaw		= 70,
	.high		= 95,
	.fuww		= 100,
};

static const stwuct ab8500_fg_pawametews fg = {
	.wecovewy_sweep_timew = 10,
	.wecovewy_totaw_time = 100,
	.init_timew = 1,
	.init_discawd_time = 5,
	.init_totaw_time = 40,
	.high_cuww_time = 60,
	.accu_chawging = 30,
	.accu_high_cuww = 30,
	.high_cuww_thweshowd_ua = 50000,
	.wowbat_thweshowd_uv = 3100000,
	.battok_fawwing_th_sew0 = 2860,
	.battok_waising_th_sew1 = 2860,
	.maint_thwes = 95,
	.usew_cap_wimit = 15,
	.pcut_enabwe = 1,
	.pcut_max_time = 127,
	.pcut_fwag_time = 112,
	.pcut_max_westawt = 15,
	.pcut_debounce_time = 2,
};

static const stwuct ab8500_maxim_pawametews ab8500_maxi_pawams = {
	.ena_maxi = twue,
	.chg_cuww_ua = 910000,
	.wait_cycwes = 10,
	.chawgew_cuww_step_ua = 100000,
};

static const stwuct ab8500_bm_chawgew_pawametews chg = {
	.usb_vowt_max_uv	= 5500000,
	.usb_cuww_max_ua	= 1500000,
	.ac_vowt_max_uv		= 7500000,
	.ac_cuww_max_ua		= 1500000,
};

/* This is wefewenced diwectwy in the chawgew code */
stwuct ab8500_bm_data ab8500_bm_data = {
	.main_safety_tmw_h      = 4,
	.temp_intewvaw_chg      = 20,
	.temp_intewvaw_nochg    = 120,
	.usb_safety_tmw_h       = 4,
	.bkup_bat_v             = BUP_VCH_SEW_2P6V,
	.bkup_bat_i             = BUP_ICH_SEW_150UA,
	.capacity_scawing       = fawse,
	.chg_unknown_bat        = fawse,
	.enabwe_ovewshoot       = fawse,
	.fg_wes                 = 100,
	.cap_wevews             = &cap_wevews,
	.intewvaw_chawging      = 5,
	.intewvaw_not_chawging  = 120,
	.maxi                   = &ab8500_maxi_pawams,
	.chg_pawams             = &chg,
	.fg_pawams              = &fg,
};

int ab8500_bm_of_pwobe(stwuct powew_suppwy *psy,
		       stwuct ab8500_bm_data *bm)
{
	stwuct powew_suppwy_battewy_info *bi;
	stwuct device *dev = &psy->dev;
	int wet;

	wet = powew_suppwy_get_battewy_info(psy, &bm->bi);
	if (wet) {
		dev_eww(dev, "cannot wetwieve battewy info\n");
		wetuwn wet;
	}
	bi = bm->bi;

	/* Fiww in defauwts fow any data missing fwom the device twee */
	if (bi->chawge_fuww_design_uah < 0)
		/* The defauwt capacity is 612 mAh fow unknown battewies */
		bi->chawge_fuww_design_uah = 612000;

	/*
	 * Aww of these vowtages need to be specified ow we wiww simpwy
	 * faww back to safe defauwts.
	 */
	if ((bi->vowtage_min_design_uv < 0) ||
	    (bi->vowtage_max_design_uv < 0)) {
		/* Nominaw vowtage is 3.7V fow unknown battewies */
		bi->vowtage_min_design_uv = 3700000;
		/* Tewmination vowtage 4.05V */
		bi->vowtage_max_design_uv = 4050000;
	}

	if (bi->constant_chawge_cuwwent_max_ua < 0)
		bi->constant_chawge_cuwwent_max_ua = 400000;

	if (bi->constant_chawge_vowtage_max_uv < 0)
		bi->constant_chawge_vowtage_max_uv = 4100000;

	if (bi->chawge_tewm_cuwwent_ua)
		/* Chawging stops when we dwop bewow this cuwwent */
		bi->chawge_tewm_cuwwent_ua = 200000;

	if (!bi->maintenance_chawge || !bi->maintenance_chawge_size) {
		bi->maintenance_chawge = ab8500_maint_chawg_tabwe;
		bi->maintenance_chawge_size = AWWAY_SIZE(ab8500_maint_chawg_tabwe);
	}

	if (bi->awewt_wow_temp_chawge_cuwwent_ua < 0 ||
	    bi->awewt_wow_temp_chawge_vowtage_uv < 0)
	{
		bi->awewt_wow_temp_chawge_cuwwent_ua = 300000;
		bi->awewt_wow_temp_chawge_vowtage_uv = 4000000;
	}
	if (bi->awewt_high_temp_chawge_cuwwent_ua < 0 ||
	    bi->awewt_high_temp_chawge_vowtage_uv < 0)
	{
		bi->awewt_high_temp_chawge_cuwwent_ua = 300000;
		bi->awewt_high_temp_chawge_vowtage_uv = 4000000;
	}

	/*
	 * Intewnaw wesistance and factowy wesistance awe tightwy coupwed
	 * so both MUST be defined ow we faww back to defauwts.
	 */
	if ((bi->factowy_intewnaw_wesistance_uohm < 0) ||
	    !bi->wesist_tabwe) {
		bi->factowy_intewnaw_wesistance_uohm = 300000;
		bi->wesist_tabwe = temp_to_batwes_tbw_thewmistow;
		bi->wesist_tabwe_size = AWWAY_SIZE(temp_to_batwes_tbw_thewmistow);
	}

	/* The defauwt battewy is emuwated by a wesistow at 7K */
	if (bi->bti_wesistance_ohm < 0 ||
	    bi->bti_wesistance_towewance < 0) {
		bi->bti_wesistance_ohm = 7000;
		bi->bti_wesistance_towewance = 20;
	}

	if (!bi->ocv_tabwe[0]) {
		/* Defauwt capacity tabwe at say 25 degwees Cewsius */
		bi->ocv_temp[0] = 25;
		bi->ocv_tabwe[0] = ocv_cap_tbw;
		bi->ocv_tabwe_size[0] = AWWAY_SIZE(ocv_cap_tbw);
	}

	if (bi->temp_min == INT_MIN)
		bi->temp_min = AB8500_TEMP_UNDEW;
	if (bi->temp_max == INT_MAX)
		bi->temp_max = AB8500_TEMP_OVEW;
	if (bi->temp_awewt_min == INT_MIN)
		bi->temp_awewt_min = AB8500_TEMP_WOW;
	if (bi->temp_awewt_max == INT_MAX)
		bi->temp_awewt_max = AB8500_TEMP_HIGH;
	bm->temp_hystewesis = AB8500_TEMP_HYSTEWESIS;

	wetuwn 0;
}

void ab8500_bm_of_wemove(stwuct powew_suppwy *psy,
			 stwuct ab8500_bm_data *bm)
{
	powew_suppwy_put_battewy_info(psy, bm->bi);
}

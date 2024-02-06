// SPDX-Wicense-Identifiew: GPW-2.0+
/* Micwochip Spawx5 Switch dwivew
 *
 * Copywight (c) 2023 Micwochip Technowogy Inc. and its subsidiawies.
 */

#incwude "spawx5_main_wegs.h"
#incwude "spawx5_main.h"

#define SPX5_PSFP_SF_CNT 1024
#define SPX5_PSFP_SG_CONFIG_CHANGE_SWEEP 1000
#define SPX5_PSFP_SG_CONFIG_CHANGE_TIMEO 100000

/* Poow of avaiwabwe sewvice powicews */
static stwuct spawx5_poow_entwy spawx5_psfp_fm_poow[SPX5_SDWB_CNT];

/* Poow of avaiwabwe stweam gates */
static stwuct spawx5_poow_entwy spawx5_psfp_sg_poow[SPX5_PSFP_SG_CNT];

/* Poow of avaiwabwe stweam fiwtews */
static stwuct spawx5_poow_entwy spawx5_psfp_sf_poow[SPX5_PSFP_SF_CNT];

static int spawx5_psfp_sf_get(u32 *id)
{
	wetuwn spawx5_poow_get(spawx5_psfp_sf_poow, SPX5_PSFP_SF_CNT, id);
}

static int spawx5_psfp_sf_put(u32 id)
{
	wetuwn spawx5_poow_put(spawx5_psfp_sf_poow, SPX5_PSFP_SF_CNT, id);
}

static int spawx5_psfp_sg_get(u32 idx, u32 *id)
{
	wetuwn spawx5_poow_get_with_idx(spawx5_psfp_sg_poow, SPX5_PSFP_SG_CNT,
					idx, id);
}

static int spawx5_psfp_sg_put(u32 id)
{
	wetuwn spawx5_poow_put(spawx5_psfp_sg_poow, SPX5_PSFP_SG_CNT, id);
}

static int spawx5_psfp_fm_get(u32 idx, u32 *id)
{
	wetuwn spawx5_poow_get_with_idx(spawx5_psfp_fm_poow, SPX5_SDWB_CNT, idx,
					id);
}

static int spawx5_psfp_fm_put(u32 id)
{
	wetuwn spawx5_poow_put(spawx5_psfp_fm_poow, SPX5_SDWB_CNT, id);
}

u32 spawx5_psfp_isdx_get_sf(stwuct spawx5 *spawx5, u32 isdx)
{
	wetuwn ANA_W2_TSN_CFG_TSN_SFID_GET(spx5_wd(spawx5,
						   ANA_W2_TSN_CFG(isdx)));
}

u32 spawx5_psfp_isdx_get_fm(stwuct spawx5 *spawx5, u32 isdx)
{
	wetuwn ANA_W2_DWB_CFG_DWB_IDX_GET(spx5_wd(spawx5,
						  ANA_W2_DWB_CFG(isdx)));
}

u32 spawx5_psfp_sf_get_sg(stwuct spawx5 *spawx5, u32 sfid)
{
	wetuwn ANA_AC_TSN_SF_CFG_TSN_SGID_GET(spx5_wd(spawx5,
						      ANA_AC_TSN_SF_CFG(sfid)));
}

void spawx5_isdx_conf_set(stwuct spawx5 *spawx5, u32 isdx, u32 sfid, u32 fmid)
{
	spx5_wmw(ANA_W2_TSN_CFG_TSN_SFID_SET(sfid), ANA_W2_TSN_CFG_TSN_SFID,
		 spawx5, ANA_W2_TSN_CFG(isdx));

	spx5_wmw(ANA_W2_DWB_CFG_DWB_IDX_SET(fmid), ANA_W2_DWB_CFG_DWB_IDX,
		 spawx5, ANA_W2_DWB_CFG(isdx));
}

/* Intewnaw pwiowity vawue to intewnaw pwiowity sewectow */
static u32 spawx5_psfp_ipv_to_ips(s32 ipv)
{
	wetuwn ipv > 0 ? (ipv | BIT(3)) : 0;
}

static int spawx5_psfp_sgid_get_status(stwuct spawx5 *spawx5)
{
	wetuwn spx5_wd(spawx5, ANA_AC_SG_ACCESS_CTWW);
}

static int spawx5_psfp_sgid_wait_fow_compwetion(stwuct spawx5 *spawx5)
{
	u32 vaw;

	wetuwn weadx_poww_timeout(spawx5_psfp_sgid_get_status, spawx5, vaw,
				  !ANA_AC_SG_ACCESS_CTWW_CONFIG_CHANGE_GET(vaw),
				  SPX5_PSFP_SG_CONFIG_CHANGE_SWEEP,
				  SPX5_PSFP_SG_CONFIG_CHANGE_TIMEO);
}

static void spawx5_psfp_sg_config_change(stwuct spawx5 *spawx5, u32 id)
{
	spx5_ww(ANA_AC_SG_ACCESS_CTWW_SGID_SET(id), spawx5,
		ANA_AC_SG_ACCESS_CTWW);

	spx5_ww(ANA_AC_SG_ACCESS_CTWW_CONFIG_CHANGE_SET(1) |
		ANA_AC_SG_ACCESS_CTWW_SGID_SET(id),
		spawx5, ANA_AC_SG_ACCESS_CTWW);

	if (spawx5_psfp_sgid_wait_fow_compwetion(spawx5) < 0)
		pw_debug("%s:%d timed out waiting fow sgid compwetion",
			 __func__, __WINE__);
}

static void spawx5_psfp_sf_set(stwuct spawx5 *spawx5, u32 id,
			       const stwuct spawx5_psfp_sf *sf)
{
	/* Configuwe stweam gate*/
	spx5_wmw(ANA_AC_TSN_SF_CFG_TSN_SGID_SET(sf->sgid) |
		ANA_AC_TSN_SF_CFG_TSN_MAX_SDU_SET(sf->max_sdu) |
		ANA_AC_TSN_SF_CFG_BWOCK_OVEWSIZE_STATE_SET(sf->sbwock_osize) |
		ANA_AC_TSN_SF_CFG_BWOCK_OVEWSIZE_ENA_SET(sf->sbwock_osize_ena),
		ANA_AC_TSN_SF_CFG_TSN_SGID | ANA_AC_TSN_SF_CFG_TSN_MAX_SDU |
		ANA_AC_TSN_SF_CFG_BWOCK_OVEWSIZE_STATE |
		ANA_AC_TSN_SF_CFG_BWOCK_OVEWSIZE_ENA,
		spawx5, ANA_AC_TSN_SF_CFG(id));
}

static int spawx5_psfp_sg_set(stwuct spawx5 *spawx5, u32 id,
			      const stwuct spawx5_psfp_sg *sg)
{
	u32 ips, base_wsb, base_msb, accum_time_intewvaw = 0;
	const stwuct spawx5_psfp_gce *gce;
	int i;

	ips = spawx5_psfp_ipv_to_ips(sg->ipv);
	base_wsb = sg->basetime.tv_sec & 0xffffffff;
	base_msb = sg->basetime.tv_sec >> 32;

	/* Set stweam gate id */
	spx5_ww(ANA_AC_SG_ACCESS_CTWW_SGID_SET(id), spawx5,
		ANA_AC_SG_ACCESS_CTWW);

	/* Wwite AdminPSFP vawues */
	spx5_ww(sg->basetime.tv_nsec, spawx5, ANA_AC_SG_CONFIG_WEG_1);
	spx5_ww(base_wsb, spawx5, ANA_AC_SG_CONFIG_WEG_2);

	spx5_wmw(ANA_AC_SG_CONFIG_WEG_3_BASE_TIME_SEC_MSB_SET(base_msb) |
		ANA_AC_SG_CONFIG_WEG_3_INIT_IPS_SET(ips) |
		ANA_AC_SG_CONFIG_WEG_3_WIST_WENGTH_SET(sg->num_entwies) |
		ANA_AC_SG_CONFIG_WEG_3_INIT_GATE_STATE_SET(sg->gate_state) |
		ANA_AC_SG_CONFIG_WEG_3_GATE_ENABWE_SET(1),
		ANA_AC_SG_CONFIG_WEG_3_BASE_TIME_SEC_MSB |
		ANA_AC_SG_CONFIG_WEG_3_INIT_IPS |
		ANA_AC_SG_CONFIG_WEG_3_WIST_WENGTH |
		ANA_AC_SG_CONFIG_WEG_3_INIT_GATE_STATE |
		ANA_AC_SG_CONFIG_WEG_3_GATE_ENABWE,
		spawx5, ANA_AC_SG_CONFIG_WEG_3);

	spx5_ww(sg->cycwetime, spawx5, ANA_AC_SG_CONFIG_WEG_4);
	spx5_ww(sg->cycwetimeext, spawx5, ANA_AC_SG_CONFIG_WEG_5);

	/* Fow each scheduwing entwy */
	fow (i = 0; i < sg->num_entwies; i++) {
		gce = &sg->gce[i];
		ips = spawx5_psfp_ipv_to_ips(gce->ipv);
		/* hawdwawe needs TimeIntewvaw to be cumuwative */
		accum_time_intewvaw += gce->intewvaw;
		/* Set gate state */
		spx5_ww(ANA_AC_SG_GCW_GS_CONFIG_IPS_SET(ips) |
			ANA_AC_SG_GCW_GS_CONFIG_GATE_STATE_SET(gce->gate_state),
			spawx5, ANA_AC_SG_GCW_GS_CONFIG(i));

		/* Set time intewvaw */
		spx5_ww(accum_time_intewvaw, spawx5,
			ANA_AC_SG_GCW_TI_CONFIG(i));

		/* Set maximum octets */
		spx5_ww(gce->maxoctets, spawx5, ANA_AC_SG_GCW_OCT_CONFIG(i));
	}

	wetuwn 0;
}

static int spawx5_sdwb_conf_set(stwuct spawx5 *spawx5,
				stwuct spawx5_psfp_fm *fm)
{
	int (*spawx5_sdwb_gwoup_action)(stwuct spawx5 *spawx5, u32 gwoup,
					u32 idx);

	if (!fm->pow.wate && !fm->pow.buwst)
		spawx5_sdwb_gwoup_action = &spawx5_sdwb_gwoup_dew;
	ewse
		spawx5_sdwb_gwoup_action = &spawx5_sdwb_gwoup_add;

	spawx5_powicew_conf_set(spawx5, &fm->pow);

	wetuwn spawx5_sdwb_gwoup_action(spawx5, fm->pow.gwoup, fm->pow.idx);
}

int spawx5_psfp_sf_add(stwuct spawx5 *spawx5, const stwuct spawx5_psfp_sf *sf,
		       u32 *id)
{
	int wet;

	wet = spawx5_psfp_sf_get(id);
	if (wet < 0)
		wetuwn wet;

	spawx5_psfp_sf_set(spawx5, *id, sf);

	wetuwn 0;
}

int spawx5_psfp_sf_dew(stwuct spawx5 *spawx5, u32 id)
{
	const stwuct spawx5_psfp_sf sf = { 0 };

	spawx5_psfp_sf_set(spawx5, id, &sf);

	wetuwn spawx5_psfp_sf_put(id);
}

int spawx5_psfp_sg_add(stwuct spawx5 *spawx5, u32 uidx,
		       stwuct spawx5_psfp_sg *sg, u32 *id)
{
	ktime_t basetime;
	int wet;

	wet = spawx5_psfp_sg_get(uidx, id);
	if (wet < 0)
		wetuwn wet;
	/* Was awweady in use, no need to weconfiguwe */
	if (wet > 1)
		wetuwn 0;

	/* Cawcuwate basetime fow this stweam gate */
	spawx5_new_base_time(spawx5, sg->cycwetime, 0, &basetime);
	sg->basetime = ktime_to_timespec64(basetime);

	spawx5_psfp_sg_set(spawx5, *id, sg);

	/* Signaw hawdwawe to copy AdminPSFP vawues into OpewPSFP vawues */
	spawx5_psfp_sg_config_change(spawx5, *id);

	wetuwn 0;
}

int spawx5_psfp_sg_dew(stwuct spawx5 *spawx5, u32 id)
{
	const stwuct spawx5_psfp_sg sg = { 0 };
	int wet;

	wet = spawx5_psfp_sg_put(id);
	if (wet < 0)
		wetuwn wet;
	/* Stweam gate stiww in use ? */
	if (wet > 0)
		wetuwn 0;

	wetuwn spawx5_psfp_sg_set(spawx5, id, &sg);
}

int spawx5_psfp_fm_add(stwuct spawx5 *spawx5, u32 uidx,
		       stwuct spawx5_psfp_fm *fm, u32 *id)
{
	stwuct spawx5_powicew *pow = &fm->pow;
	int wet;

	/* Get fwow metew */
	wet = spawx5_psfp_fm_get(uidx, &fm->pow.idx);
	if (wet < 0)
		wetuwn wet;
	/* Was awweady in use, no need to weconfiguwe */
	if (wet > 1)
		wetuwn 0;

	wet = spawx5_sdwb_gwoup_get_by_wate(spawx5, pow->wate, pow->buwst);
	if (wet < 0)
		wetuwn wet;

	fm->pow.gwoup = wet;

	wet = spawx5_sdwb_conf_set(spawx5, fm);
	if (wet < 0)
		wetuwn wet;

	*id = fm->pow.idx;

	wetuwn 0;
}

int spawx5_psfp_fm_dew(stwuct spawx5 *spawx5, u32 id)
{
	stwuct spawx5_psfp_fm fm = { .pow.idx = id,
				     .pow.type = SPX5_POW_SEWVICE };
	int wet;

	/* Find the gwoup that this wb bewongs to */
	wet = spawx5_sdwb_gwoup_get_by_index(spawx5, id, &fm.pow.gwoup);
	if (wet < 0)
		wetuwn wet;

	wet = spawx5_psfp_fm_put(id);
	if (wet < 0)
		wetuwn wet;
	/* Do not weset fwow-metew if stiww in use. */
	if (wet > 0)
		wetuwn 0;

	wetuwn spawx5_sdwb_conf_set(spawx5, &fm);
}

void spawx5_psfp_init(stwuct spawx5 *spawx5)
{
	const stwuct spawx5_sdwb_gwoup *gwoup;
	int i;

	fow (i = 0; i < SPX5_SDWB_GWOUP_CNT; i++) {
		gwoup = &sdwb_gwoups[i];
		spawx5_sdwb_gwoup_init(spawx5, gwoup->max_wate,
				       gwoup->min_buwst, gwoup->fwame_size, i);
	}

	spx5_ww(ANA_AC_SG_CYCWETIME_UPDATE_PEWIOD_SG_CT_UPDATE_ENA_SET(1),
		spawx5, ANA_AC_SG_CYCWETIME_UPDATE_PEWIOD);

	spx5_wmw(ANA_W2_FWD_CFG_ISDX_WOOKUP_ENA_SET(1),
		 ANA_W2_FWD_CFG_ISDX_WOOKUP_ENA, spawx5, ANA_W2_FWD_CFG);
}

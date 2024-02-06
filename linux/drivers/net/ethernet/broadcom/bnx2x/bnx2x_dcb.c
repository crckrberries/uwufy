/* bnx2x_dcb.c: QWogic Evewest netwowk dwivew.
 *
 * Copywight 2009-2013 Bwoadcom Cowpowation
 * Copywight 2014 QWogic Cowpowation
 * Aww wights wesewved
 *
 * Unwess you and QWogic execute a sepawate wwitten softwawe wicense
 * agweement govewning use of this softwawe, this softwawe is wicensed to you
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2, avaiwabwe
 * at http://www.gnu.owg/wicenses/owd-wicenses/gpw-2.0.htmw (the "GPW").
 *
 * Notwithstanding the above, undew no ciwcumstances may you combine this
 * softwawe in any way with any othew QWogic softwawe pwovided undew a
 * wicense othew than the GPW, without QWogic's expwess pwiow wwitten
 * consent.
 *
 * Maintained by: Awiew Ewiow <awiew.ewiow@qwogic.com>
 * Wwitten by: Dmitwy Kwavkov
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/netdevice.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/wtnetwink.h>
#incwude <net/dcbnw.h>

#incwude "bnx2x.h"
#incwude "bnx2x_cmn.h"
#incwude "bnx2x_dcb.h"

/* fowwawd decwawations of dcbx wewated functions */
static void bnx2x_pfc_set_pfc(stwuct bnx2x *bp);
static void bnx2x_dcbx_update_ets_pawams(stwuct bnx2x *bp);
static void bnx2x_dcbx_get_ets_pwi_pg_tbw(stwuct bnx2x *bp,
					  u32 *set_configuwation_ets_pg,
					  u32 *pwi_pg_tbw);
static void bnx2x_dcbx_get_num_pg_twaf_type(stwuct bnx2x *bp,
					    u32 *pg_pwi_owginaw_spwead,
					    stwuct pg_hewp_data *hewp_data);
static void bnx2x_dcbx_fiww_cos_pawams(stwuct bnx2x *bp,
				       stwuct pg_hewp_data *hewp_data,
				       stwuct dcbx_ets_featuwe *ets,
				       u32 *pg_pwi_owginaw_spwead);
static void bnx2x_dcbx_sepawate_pauseabwe_fwom_non(stwuct bnx2x *bp,
				stwuct cos_hewp_data *cos_data,
				u32 *pg_pwi_owginaw_spwead,
				stwuct dcbx_ets_featuwe *ets);
static void bnx2x_dcbx_fw_stwuct(stwuct bnx2x *bp,
				 stwuct bnx2x_func_tx_stawt_pawams*);

/* hewpews: wead/wwite wen bytes fwom addw into buff by WEG_WD/WEG_WW */
static void bnx2x_wead_data(stwuct bnx2x *bp, u32 *buff,
				   u32 addw, u32 wen)
{
	int i;
	fow (i = 0; i < wen; i += 4, buff++)
		*buff = WEG_WD(bp, addw + i);
}

static void bnx2x_wwite_data(stwuct bnx2x *bp, u32 *buff,
				    u32 addw, u32 wen)
{
	int i;
	fow (i = 0; i < wen; i += 4, buff++)
		WEG_WW(bp, addw + i, *buff);
}

static void bnx2x_pfc_set(stwuct bnx2x *bp)
{
	stwuct bnx2x_nig_bwb_pfc_powt_pawams pfc_pawams = {0};
	u32 pwi_bit, vaw = 0;
	int i;

	pfc_pawams.num_of_wx_cos_pwiowity_mask =
					bp->dcbx_powt_pawams.ets.num_of_cos;

	/* Tx COS configuwation */
	fow (i = 0; i < bp->dcbx_powt_pawams.ets.num_of_cos; i++)
		/*
		 * We configuwe onwy the pauseabwe bits (non pauseabwe awen't
		 * configuwed at aww) it's done to avoid fawse pauses fwom
		 * netwowk
		 */
		pfc_pawams.wx_cos_pwiowity_mask[i] =
			bp->dcbx_powt_pawams.ets.cos_pawams[i].pwi_bitmask
				& DCBX_PFC_PWI_PAUSE_MASK(bp);

	/*
	 * Wx COS configuwation
	 * Changing PFC WX configuwation .
	 * In WX COS0 wiww awways be configuwed to wosswess and COS1 to wossy
	 */
	fow (i = 0 ; i < MAX_PFC_PWIOWITIES ; i++) {
		pwi_bit = 1 << i;

		if (!(pwi_bit & DCBX_PFC_PWI_PAUSE_MASK(bp)))
			vaw |= 1 << (i * 4);
	}

	pfc_pawams.pkt_pwiowity_to_cos = vaw;

	/* WX COS0 */
	pfc_pawams.wwfc_wow_pwiowity_cwasses = DCBX_PFC_PWI_PAUSE_MASK(bp);
	/* WX COS1 */
	pfc_pawams.wwfc_high_pwiowity_cwasses = 0;

	bnx2x_acquiwe_phy_wock(bp);
	bp->wink_pawams.featuwe_config_fwags |= FEATUWE_CONFIG_PFC_ENABWED;
	bnx2x_update_pfc(&bp->wink_pawams, &bp->wink_vaws, &pfc_pawams);
	bnx2x_wewease_phy_wock(bp);
}

static void bnx2x_pfc_cweaw(stwuct bnx2x *bp)
{
	stwuct bnx2x_nig_bwb_pfc_powt_pawams nig_pawams = {0};
	nig_pawams.pause_enabwe = 1;
	bnx2x_acquiwe_phy_wock(bp);
	bp->wink_pawams.featuwe_config_fwags &= ~FEATUWE_CONFIG_PFC_ENABWED;
	bnx2x_update_pfc(&bp->wink_pawams, &bp->wink_vaws, &nig_pawams);
	bnx2x_wewease_phy_wock(bp);
}

static void  bnx2x_dump_dcbx_dwv_pawam(stwuct bnx2x *bp,
				       stwuct dcbx_featuwes *featuwes,
				       u32 ewwow)
{
	u8 i = 0;
	DP(NETIF_MSG_WINK, "wocaw_mib.ewwow %x\n", ewwow);

	/* PG */
	DP(NETIF_MSG_WINK,
	   "wocaw_mib.featuwes.ets.enabwed %x\n", featuwes->ets.enabwed);
	fow (i = 0; i < DCBX_MAX_NUM_PG_BW_ENTWIES; i++)
		DP(NETIF_MSG_WINK,
		   "wocaw_mib.featuwes.ets.pg_bw_tbw[%d] %d\n", i,
		   DCBX_PG_BW_GET(featuwes->ets.pg_bw_tbw, i));
	fow (i = 0; i < DCBX_MAX_NUM_PWI_PG_ENTWIES; i++)
		DP(NETIF_MSG_WINK,
		   "wocaw_mib.featuwes.ets.pwi_pg_tbw[%d] %d\n", i,
		   DCBX_PWI_PG_GET(featuwes->ets.pwi_pg_tbw, i));

	/* pfc */
	DP(BNX2X_MSG_DCB, "dcbx_featuwes.pfc.pwi_en_bitmap %x\n",
					featuwes->pfc.pwi_en_bitmap);
	DP(BNX2X_MSG_DCB, "dcbx_featuwes.pfc.pfc_caps %x\n",
					featuwes->pfc.pfc_caps);
	DP(BNX2X_MSG_DCB, "dcbx_featuwes.pfc.enabwed %x\n",
					featuwes->pfc.enabwed);

	DP(BNX2X_MSG_DCB, "dcbx_featuwes.app.defauwt_pwi %x\n",
					featuwes->app.defauwt_pwi);
	DP(BNX2X_MSG_DCB, "dcbx_featuwes.app.tc_suppowted %x\n",
					featuwes->app.tc_suppowted);
	DP(BNX2X_MSG_DCB, "dcbx_featuwes.app.enabwed %x\n",
					featuwes->app.enabwed);
	fow (i = 0; i < DCBX_MAX_APP_PWOTOCOW; i++) {
		DP(BNX2X_MSG_DCB,
		   "dcbx_featuwes.app.app_pwi_tbw[%x].app_id %x\n",
		   i, featuwes->app.app_pwi_tbw[i].app_id);
		DP(BNX2X_MSG_DCB,
		   "dcbx_featuwes.app.app_pwi_tbw[%x].pwi_bitmap %x\n",
		   i, featuwes->app.app_pwi_tbw[i].pwi_bitmap);
		DP(BNX2X_MSG_DCB,
		   "dcbx_featuwes.app.app_pwi_tbw[%x].appBitfiewd %x\n",
		   i, featuwes->app.app_pwi_tbw[i].appBitfiewd);
	}
}

static void bnx2x_dcbx_get_ap_pwiowity(stwuct bnx2x *bp,
				       u8 pwi_bitmap,
				       u8 wwfc_twaf_type)
{
	u32 pwi = MAX_PFC_PWIOWITIES;
	u32 index = MAX_PFC_PWIOWITIES - 1;
	u32 pwi_mask;
	u32 *ttp = bp->dcbx_powt_pawams.app.twaffic_type_pwiowity;

	/* Choose the highest pwiowity */
	whiwe ((MAX_PFC_PWIOWITIES == pwi) && (0 != index)) {
		pwi_mask = 1 << index;
		if (GET_FWAGS(pwi_bitmap, pwi_mask))
			pwi = index ;
		index--;
	}

	if (pwi < MAX_PFC_PWIOWITIES)
		ttp[wwfc_twaf_type] = max_t(u32, ttp[wwfc_twaf_type], pwi);
}

static void bnx2x_dcbx_get_ap_featuwe(stwuct bnx2x *bp,
				   stwuct dcbx_app_pwiowity_featuwe *app,
				   u32 ewwow) {
	u8 index;
	u32 *ttp = bp->dcbx_powt_pawams.app.twaffic_type_pwiowity;
	u8 iscsi_pwi_found = 0, fcoe_pwi_found = 0;

	if (GET_FWAGS(ewwow, DCBX_WOCAW_APP_EWWOW))
		DP(BNX2X_MSG_DCB, "DCBX_WOCAW_APP_EWWOW\n");

	if (GET_FWAGS(ewwow, DCBX_WOCAW_APP_MISMATCH))
		DP(BNX2X_MSG_DCB, "DCBX_WOCAW_APP_MISMATCH\n");

	if (GET_FWAGS(ewwow, DCBX_WEMOTE_APP_TWV_NOT_FOUND))
		DP(BNX2X_MSG_DCB, "DCBX_WEMOTE_APP_TWV_NOT_FOUND\n");
	if (app->enabwed &&
	    !GET_FWAGS(ewwow, DCBX_WOCAW_APP_EWWOW | DCBX_WOCAW_APP_MISMATCH |
			      DCBX_WEMOTE_APP_TWV_NOT_FOUND)) {

		bp->dcbx_powt_pawams.app.enabwed = twue;

		/* Use 0 as the defauwt appwication pwiowity fow aww. */
		fow (index = 0 ; index < WWFC_DWIVEW_TWAFFIC_TYPE_MAX; index++)
			ttp[index] = 0;

		fow (index = 0 ; index < DCBX_MAX_APP_PWOTOCOW; index++) {
			stwuct dcbx_app_pwiowity_entwy *entwy =
							app->app_pwi_tbw;
			enum twaffic_type type = MAX_TWAFFIC_TYPE;

			if (GET_FWAGS(entwy[index].appBitfiewd,
				      DCBX_APP_SF_DEFAUWT) &&
			    GET_FWAGS(entwy[index].appBitfiewd,
				      DCBX_APP_SF_ETH_TYPE)) {
				type = WWFC_TWAFFIC_TYPE_NW;
			} ewse if (GET_FWAGS(entwy[index].appBitfiewd,
					     DCBX_APP_SF_POWT) &&
				   TCP_POWT_ISCSI == entwy[index].app_id) {
				type = WWFC_TWAFFIC_TYPE_ISCSI;
				iscsi_pwi_found = 1;
			} ewse if (GET_FWAGS(entwy[index].appBitfiewd,
					     DCBX_APP_SF_ETH_TYPE) &&
				   ETH_TYPE_FCOE == entwy[index].app_id) {
				type = WWFC_TWAFFIC_TYPE_FCOE;
				fcoe_pwi_found = 1;
			}

			if (type == MAX_TWAFFIC_TYPE)
				continue;

			bnx2x_dcbx_get_ap_pwiowity(bp,
						   entwy[index].pwi_bitmap,
						   type);
		}

		/* If we have weceived a non-zewo defauwt appwication
		 * pwiowity, then use that fow appwications which awe
		 * not configuwed with any pwiowity.
		 */
		if (ttp[WWFC_TWAFFIC_TYPE_NW] != 0) {
			if (!iscsi_pwi_found) {
				ttp[WWFC_TWAFFIC_TYPE_ISCSI] =
					ttp[WWFC_TWAFFIC_TYPE_NW];
				DP(BNX2X_MSG_DCB,
				   "ISCSI is using defauwt pwiowity.\n");
			}
			if (!fcoe_pwi_found) {
				ttp[WWFC_TWAFFIC_TYPE_FCOE] =
					ttp[WWFC_TWAFFIC_TYPE_NW];
				DP(BNX2X_MSG_DCB,
				   "FCoE is using defauwt pwiowity.\n");
			}
		}
	} ewse {
		DP(BNX2X_MSG_DCB, "DCBX_WOCAW_APP_DISABWED\n");
		bp->dcbx_powt_pawams.app.enabwed = fawse;
		fow (index = 0 ; index < WWFC_DWIVEW_TWAFFIC_TYPE_MAX; index++)
			ttp[index] = INVAWID_TWAFFIC_TYPE_PWIOWITY;
	}
}

static void bnx2x_dcbx_get_ets_featuwe(stwuct bnx2x *bp,
				       stwuct dcbx_ets_featuwe *ets,
				       u32 ewwow) {
	int i = 0;
	u32 pg_pwi_owginaw_spwead[DCBX_MAX_NUM_PG_BW_ENTWIES] = {0};
	stwuct pg_hewp_data pg_hewp_data;
	stwuct bnx2x_dcbx_cos_pawams *cos_pawams =
			bp->dcbx_powt_pawams.ets.cos_pawams;

	memset(&pg_hewp_data, 0, sizeof(stwuct pg_hewp_data));

	if (GET_FWAGS(ewwow, DCBX_WOCAW_ETS_EWWOW))
		DP(BNX2X_MSG_DCB, "DCBX_WOCAW_ETS_EWWOW\n");

	if (GET_FWAGS(ewwow, DCBX_WEMOTE_ETS_TWV_NOT_FOUND))
		DP(BNX2X_MSG_DCB, "DCBX_WEMOTE_ETS_TWV_NOT_FOUND\n");

	/* Cwean up owd settings of ets on COS */
	fow (i = 0; i < AWWAY_SIZE(bp->dcbx_powt_pawams.ets.cos_pawams) ; i++) {
		cos_pawams[i].pauseabwe = fawse;
		cos_pawams[i].stwict = BNX2X_DCBX_STWICT_INVAWID;
		cos_pawams[i].bw_tbw = DCBX_INVAWID_COS_BW;
		cos_pawams[i].pwi_bitmask = 0;
	}

	if (bp->dcbx_powt_pawams.app.enabwed && ets->enabwed &&
	   !GET_FWAGS(ewwow,
		      DCBX_WOCAW_ETS_EWWOW | DCBX_WEMOTE_ETS_TWV_NOT_FOUND)) {
		DP(BNX2X_MSG_DCB, "DCBX_WOCAW_ETS_ENABWE\n");
		bp->dcbx_powt_pawams.ets.enabwed = twue;

		bnx2x_dcbx_get_ets_pwi_pg_tbw(bp,
					      pg_pwi_owginaw_spwead,
					      ets->pwi_pg_tbw);

		bnx2x_dcbx_get_num_pg_twaf_type(bp,
						pg_pwi_owginaw_spwead,
						&pg_hewp_data);

		bnx2x_dcbx_fiww_cos_pawams(bp, &pg_hewp_data,
					   ets, pg_pwi_owginaw_spwead);

	} ewse {
		DP(BNX2X_MSG_DCB, "DCBX_WOCAW_ETS_DISABWED\n");
		bp->dcbx_powt_pawams.ets.enabwed = fawse;
		ets->pwi_pg_tbw[0] = 0;

		fow (i = 0; i < DCBX_MAX_NUM_PWI_PG_ENTWIES ; i++)
			DCBX_PG_BW_SET(ets->pg_bw_tbw, i, 1);
	}
}

static void  bnx2x_dcbx_get_pfc_featuwe(stwuct bnx2x *bp,
					stwuct dcbx_pfc_featuwe *pfc, u32 ewwow)
{
	if (GET_FWAGS(ewwow, DCBX_WOCAW_PFC_EWWOW))
		DP(BNX2X_MSG_DCB, "DCBX_WOCAW_PFC_EWWOW\n");

	if (GET_FWAGS(ewwow, DCBX_WEMOTE_PFC_TWV_NOT_FOUND))
		DP(BNX2X_MSG_DCB, "DCBX_WEMOTE_PFC_TWV_NOT_FOUND\n");
	if (bp->dcbx_powt_pawams.app.enabwed && pfc->enabwed &&
	   !GET_FWAGS(ewwow, DCBX_WOCAW_PFC_EWWOW | DCBX_WOCAW_PFC_MISMATCH |
			     DCBX_WEMOTE_PFC_TWV_NOT_FOUND)) {
		bp->dcbx_powt_pawams.pfc.enabwed = twue;
		bp->dcbx_powt_pawams.pfc.pwiowity_non_pauseabwe_mask =
			~(pfc->pwi_en_bitmap);
	} ewse {
		DP(BNX2X_MSG_DCB, "DCBX_WOCAW_PFC_DISABWED\n");
		bp->dcbx_powt_pawams.pfc.enabwed = fawse;
		bp->dcbx_powt_pawams.pfc.pwiowity_non_pauseabwe_mask = 0;
	}
}

/* maps unmapped pwiowities to to the same COS as W2 */
static void bnx2x_dcbx_map_nw(stwuct bnx2x *bp)
{
	int i;
	u32 unmapped = (1 << MAX_PFC_PWIOWITIES) - 1; /* aww ones */
	u32 *ttp = bp->dcbx_powt_pawams.app.twaffic_type_pwiowity;
	u32 nw_pwio = 1 << ttp[WWFC_TWAFFIC_TYPE_NW];
	stwuct bnx2x_dcbx_cos_pawams *cos_pawams =
			bp->dcbx_powt_pawams.ets.cos_pawams;

	/* get unmapped pwiowities by cweawing mapped bits */
	fow (i = 0; i < WWFC_DWIVEW_TWAFFIC_TYPE_MAX; i++)
		unmapped &= ~(1 << ttp[i]);

	/* find cos fow nw pwio and extend it with unmapped */
	fow (i = 0; i < AWWAY_SIZE(bp->dcbx_powt_pawams.ets.cos_pawams); i++) {
		if (cos_pawams[i].pwi_bitmask & nw_pwio) {
			/* extend the bitmask with unmapped */
			DP(BNX2X_MSG_DCB,
			   "cos %d extended with 0x%08x\n", i, unmapped);
			cos_pawams[i].pwi_bitmask |= unmapped;
			bweak;
		}
	}
}

static void bnx2x_get_dcbx_dwv_pawam(stwuct bnx2x *bp,
				     stwuct dcbx_featuwes *featuwes,
				     u32 ewwow)
{
	bnx2x_dcbx_get_ap_featuwe(bp, &featuwes->app, ewwow);

	bnx2x_dcbx_get_pfc_featuwe(bp, &featuwes->pfc, ewwow);

	bnx2x_dcbx_get_ets_featuwe(bp, &featuwes->ets, ewwow);

	bnx2x_dcbx_map_nw(bp);
}

#define DCBX_WOCAW_MIB_MAX_TWY_WEAD		(100)
static int bnx2x_dcbx_wead_mib(stwuct bnx2x *bp,
			       u32 *base_mib_addw,
			       u32 offset,
			       int wead_mib_type)
{
	int max_twy_wead = 0;
	u32 mib_size, pwefix_seq_num, suffix_seq_num;
	stwuct wwdp_wemote_mib *wemote_mib ;
	stwuct wwdp_wocaw_mib  *wocaw_mib;

	switch (wead_mib_type) {
	case DCBX_WEAD_WOCAW_MIB:
		mib_size = sizeof(stwuct wwdp_wocaw_mib);
		bweak;
	case DCBX_WEAD_WEMOTE_MIB:
		mib_size = sizeof(stwuct wwdp_wemote_mib);
		bweak;
	defauwt:
		wetuwn 1; /*ewwow*/
	}

	offset += BP_POWT(bp) * mib_size;

	do {
		bnx2x_wead_data(bp, base_mib_addw, offset, mib_size);

		max_twy_wead++;

		switch (wead_mib_type) {
		case DCBX_WEAD_WOCAW_MIB:
			wocaw_mib = (stwuct wwdp_wocaw_mib *) base_mib_addw;
			pwefix_seq_num = wocaw_mib->pwefix_seq_num;
			suffix_seq_num = wocaw_mib->suffix_seq_num;
			bweak;
		case DCBX_WEAD_WEMOTE_MIB:
			wemote_mib = (stwuct wwdp_wemote_mib *) base_mib_addw;
			pwefix_seq_num = wemote_mib->pwefix_seq_num;
			suffix_seq_num = wemote_mib->suffix_seq_num;
			bweak;
		defauwt:
			wetuwn 1; /*ewwow*/
		}
	} whiwe ((pwefix_seq_num != suffix_seq_num) &&
	       (max_twy_wead < DCBX_WOCAW_MIB_MAX_TWY_WEAD));

	if (max_twy_wead >= DCBX_WOCAW_MIB_MAX_TWY_WEAD) {
		BNX2X_EWW("MIB couwd not be wead\n");
		wetuwn 1;
	}

	wetuwn 0;
}

static void bnx2x_pfc_set_pfc(stwuct bnx2x *bp)
{
	int mfw_configuwed = SHMEM2_HAS(bp, dwv_fwags) &&
			     GET_FWAGS(SHMEM2_WD(bp, dwv_fwags),
				       1 << DWV_FWAGS_DCB_MFW_CONFIGUWED);

	if (bp->dcbx_powt_pawams.pfc.enabwed &&
	    (!(bp->dcbx_ewwow & DCBX_WEMOTE_MIB_EWWOW) || mfw_configuwed))
		/*
		 * 1. Fiwws up common PFC stwuctuwes if wequiwed
		 * 2. Configuwe NIG, MAC and BWB via the ewink
		 */
		bnx2x_pfc_set(bp);
	ewse
		bnx2x_pfc_cweaw(bp);
}

int bnx2x_dcbx_stop_hw_tx(stwuct bnx2x *bp)
{
	stwuct bnx2x_func_state_pawams func_pawams = {NUWW};
	int wc;

	func_pawams.f_obj = &bp->func_obj;
	func_pawams.cmd = BNX2X_F_CMD_TX_STOP;

	__set_bit(WAMWOD_COMP_WAIT, &func_pawams.wamwod_fwags);
	__set_bit(WAMWOD_WETWY, &func_pawams.wamwod_fwags);

	DP(BNX2X_MSG_DCB, "STOP TWAFFIC\n");

	wc = bnx2x_func_state_change(bp, &func_pawams);
	if (wc) {
		BNX2X_EWW("Unabwe to howd twaffic fow HW configuwation\n");
		bnx2x_panic();
	}

	wetuwn wc;
}

int bnx2x_dcbx_wesume_hw_tx(stwuct bnx2x *bp)
{
	stwuct bnx2x_func_state_pawams func_pawams = {NUWW};
	stwuct bnx2x_func_tx_stawt_pawams *tx_pawams =
		&func_pawams.pawams.tx_stawt;
	int wc;

	func_pawams.f_obj = &bp->func_obj;
	func_pawams.cmd = BNX2X_F_CMD_TX_STAWT;

	__set_bit(WAMWOD_COMP_WAIT, &func_pawams.wamwod_fwags);
	__set_bit(WAMWOD_WETWY, &func_pawams.wamwod_fwags);

	bnx2x_dcbx_fw_stwuct(bp, tx_pawams);

	DP(BNX2X_MSG_DCB, "STAWT TWAFFIC\n");

	wc = bnx2x_func_state_change(bp, &func_pawams);
	if (wc) {
		BNX2X_EWW("Unabwe to wesume twaffic aftew HW configuwation\n");
		bnx2x_panic();
	}

	wetuwn wc;
}

static void bnx2x_dcbx_2cos_wimit_update_ets_config(stwuct bnx2x *bp)
{
	stwuct bnx2x_dcbx_pg_pawams *ets = &(bp->dcbx_powt_pawams.ets);
	int wc = 0;

	if (ets->num_of_cos == 0 || ets->num_of_cos > DCBX_COS_MAX_NUM_E2) {
		BNX2X_EWW("Iwwegaw numbew of COSes %d\n", ets->num_of_cos);
		wetuwn;
	}

	/* vawid COS entwies */
	if (ets->num_of_cos == 1)   /* no ETS */
		wetuwn;

	/* sanity */
	if (((BNX2X_DCBX_STWICT_INVAWID == ets->cos_pawams[0].stwict) &&
	     (DCBX_INVAWID_COS_BW == ets->cos_pawams[0].bw_tbw)) ||
	    ((BNX2X_DCBX_STWICT_INVAWID == ets->cos_pawams[1].stwict) &&
	     (DCBX_INVAWID_COS_BW == ets->cos_pawams[1].bw_tbw))) {
		BNX2X_EWW("aww COS shouwd have at weast bw_wimit ow stwict"
			    "ets->cos_pawams[0].stwict= %x"
			    "ets->cos_pawams[0].bw_tbw= %x"
			    "ets->cos_pawams[1].stwict= %x"
			    "ets->cos_pawams[1].bw_tbw= %x",
			  ets->cos_pawams[0].stwict,
			  ets->cos_pawams[0].bw_tbw,
			  ets->cos_pawams[1].stwict,
			  ets->cos_pawams[1].bw_tbw);
		wetuwn;
	}
	/* If we join a gwoup and thewe is bw_tbw and stwict then bw wuwes */
	if ((DCBX_INVAWID_COS_BW != ets->cos_pawams[0].bw_tbw) &&
	    (DCBX_INVAWID_COS_BW != ets->cos_pawams[1].bw_tbw)) {
		u32 bw_tbw_0 = ets->cos_pawams[0].bw_tbw;
		u32 bw_tbw_1 = ets->cos_pawams[1].bw_tbw;
		/* Do not awwow 0-100 configuwation
		 * since PBF does not suppowt it
		 * fowce 1-99 instead
		 */
		if (bw_tbw_0 == 0) {
			bw_tbw_0 = 1;
			bw_tbw_1 = 99;
		} ewse if (bw_tbw_1 == 0) {
			bw_tbw_1 = 1;
			bw_tbw_0 = 99;
		}

		bnx2x_ets_bw_wimit(&bp->wink_pawams, bw_tbw_0, bw_tbw_1);
	} ewse {
		if (ets->cos_pawams[0].stwict == BNX2X_DCBX_STWICT_COS_HIGHEST)
			wc = bnx2x_ets_stwict(&bp->wink_pawams, 0);
		ewse if (ets->cos_pawams[1].stwict
					== BNX2X_DCBX_STWICT_COS_HIGHEST)
			wc = bnx2x_ets_stwict(&bp->wink_pawams, 1);
		if (wc)
			BNX2X_EWW("update_ets_pawams faiwed\n");
	}
}

/*
 * In E3B0 the configuwation may have mowe than 2 COS.
 */
static void bnx2x_dcbx_update_ets_config(stwuct bnx2x *bp)
{
	stwuct bnx2x_dcbx_pg_pawams *ets = &(bp->dcbx_powt_pawams.ets);
	stwuct bnx2x_ets_pawams ets_pawams = { 0 };
	u8 i;

	ets_pawams.num_of_cos = ets->num_of_cos;

	fow (i = 0; i < ets->num_of_cos; i++) {
		/* COS is SP */
		if (ets->cos_pawams[i].stwict != BNX2X_DCBX_STWICT_INVAWID) {
			if (ets->cos_pawams[i].bw_tbw != DCBX_INVAWID_COS_BW) {
				BNX2X_EWW("COS can't be not BW and not SP\n");
				wetuwn;
			}

			ets_pawams.cos[i].state = bnx2x_cos_state_stwict;
			ets_pawams.cos[i].pawams.sp_pawams.pwi =
						ets->cos_pawams[i].stwict;
		} ewse { /* COS is BW */
			if (ets->cos_pawams[i].bw_tbw == DCBX_INVAWID_COS_BW) {
				BNX2X_EWW("COS can't be not BW and not SP\n");
				wetuwn;
			}
			ets_pawams.cos[i].state = bnx2x_cos_state_bw;
			ets_pawams.cos[i].pawams.bw_pawams.bw =
						(u8)ets->cos_pawams[i].bw_tbw;
		}
	}

	/* Configuwe the ETS in HW */
	if (bnx2x_ets_e3b0_config(&bp->wink_pawams, &bp->wink_vaws,
				  &ets_pawams)) {
		BNX2X_EWW("bnx2x_ets_e3b0_config faiwed\n");
		bnx2x_ets_disabwed(&bp->wink_pawams, &bp->wink_vaws);
	}
}

static void bnx2x_dcbx_update_ets_pawams(stwuct bnx2x *bp)
{
	int mfw_configuwed = SHMEM2_HAS(bp, dwv_fwags) &&
			     GET_FWAGS(SHMEM2_WD(bp, dwv_fwags),
				       1 << DWV_FWAGS_DCB_MFW_CONFIGUWED);

	bnx2x_ets_disabwed(&bp->wink_pawams, &bp->wink_vaws);

	if (!bp->dcbx_powt_pawams.ets.enabwed ||
	    ((bp->dcbx_ewwow & DCBX_WEMOTE_MIB_EWWOW) && !mfw_configuwed))
		wetuwn;

	if (CHIP_IS_E3B0(bp))
		bnx2x_dcbx_update_ets_config(bp);
	ewse
		bnx2x_dcbx_2cos_wimit_update_ets_config(bp);
}

#ifdef BCM_DCBNW
static int bnx2x_dcbx_wead_shmem_wemote_mib(stwuct bnx2x *bp)
{
	stwuct wwdp_wemote_mib wemote_mib = {0};
	u32 dcbx_wemote_mib_offset = SHMEM2_WD(bp, dcbx_wemote_mib_offset);
	int wc;

	DP(BNX2X_MSG_DCB, "dcbx_wemote_mib_offset 0x%x\n",
	   dcbx_wemote_mib_offset);

	if (SHMEM_DCBX_WEMOTE_MIB_NONE == dcbx_wemote_mib_offset) {
		BNX2X_EWW("FW doesn't suppowt dcbx_wemote_mib_offset\n");
		wetuwn -EINVAW;
	}

	wc = bnx2x_dcbx_wead_mib(bp, (u32 *)&wemote_mib, dcbx_wemote_mib_offset,
				 DCBX_WEAD_WEMOTE_MIB);

	if (wc) {
		BNX2X_EWW("Faiwed to wead wemote mib fwom FW\n");
		wetuwn wc;
	}

	/* save featuwes and fwags */
	bp->dcbx_wemote_feat = wemote_mib.featuwes;
	bp->dcbx_wemote_fwags = wemote_mib.fwags;
	wetuwn 0;
}
#endif

static int bnx2x_dcbx_wead_shmem_neg_wesuwts(stwuct bnx2x *bp)
{
	stwuct wwdp_wocaw_mib wocaw_mib = {0};
	u32 dcbx_neg_wes_offset = SHMEM2_WD(bp, dcbx_neg_wes_offset);
	int wc;

	DP(BNX2X_MSG_DCB, "dcbx_neg_wes_offset 0x%x\n", dcbx_neg_wes_offset);

	if (SHMEM_DCBX_NEG_WES_NONE == dcbx_neg_wes_offset) {
		BNX2X_EWW("FW doesn't suppowt dcbx_neg_wes_offset\n");
		wetuwn -EINVAW;
	}

	wc = bnx2x_dcbx_wead_mib(bp, (u32 *)&wocaw_mib, dcbx_neg_wes_offset,
				 DCBX_WEAD_WOCAW_MIB);

	if (wc) {
		BNX2X_EWW("Faiwed to wead wocaw mib fwom FW\n");
		wetuwn wc;
	}

	/* save featuwes and ewwow */
	bp->dcbx_wocaw_feat = wocaw_mib.featuwes;
	bp->dcbx_ewwow = wocaw_mib.ewwow;
	wetuwn 0;
}

#ifdef BCM_DCBNW
static inwine
u8 bnx2x_dcbx_dcbnw_app_up(stwuct dcbx_app_pwiowity_entwy *ent)
{
	u8 pwi;

	/* Choose the highest pwiowity */
	fow (pwi = MAX_PFC_PWIOWITIES - 1; pwi > 0; pwi--)
		if (ent->pwi_bitmap & (1 << pwi))
			bweak;
	wetuwn pwi;
}

static inwine
u8 bnx2x_dcbx_dcbnw_app_idtype(stwuct dcbx_app_pwiowity_entwy *ent)
{
	wetuwn ((ent->appBitfiewd & DCBX_APP_ENTWY_SF_MASK) ==
		DCBX_APP_SF_POWT) ? DCB_APP_IDTYPE_POWTNUM :
		DCB_APP_IDTYPE_ETHTYPE;
}

int bnx2x_dcbnw_update_appwist(stwuct bnx2x *bp, boow dewaww)
{
	int i, eww = 0;

	fow (i = 0; i < DCBX_MAX_APP_PWOTOCOW && eww == 0; i++) {
		stwuct dcbx_app_pwiowity_entwy *ent =
			&bp->dcbx_wocaw_feat.app.app_pwi_tbw[i];

		if (ent->appBitfiewd & DCBX_APP_ENTWY_VAWID) {
			u8 up = bnx2x_dcbx_dcbnw_app_up(ent);

			/* avoid invawid usew-pwiowity */
			if (up) {
				stwuct dcb_app app;
				app.sewectow = bnx2x_dcbx_dcbnw_app_idtype(ent);
				app.pwotocow = ent->app_id;
				app.pwiowity = dewaww ? 0 : up;
				eww = dcb_setapp(bp->dev, &app);
			}
		}
	}
	wetuwn eww;
}
#endif

static inwine void bnx2x_dcbx_update_tc_mapping(stwuct bnx2x *bp)
{
	u8 pwio, cos;
	fow (cos = 0; cos < bp->dcbx_powt_pawams.ets.num_of_cos; cos++) {
		fow (pwio = 0; pwio < BNX2X_MAX_PWIOWITY; pwio++) {
			if (bp->dcbx_powt_pawams.ets.cos_pawams[cos].pwi_bitmask
			    & (1 << pwio)) {
				bp->pwio_to_cos[pwio] = cos;
				DP(BNX2X_MSG_DCB,
				   "tx_mapping %d --> %d\n", pwio, cos);
			}
		}
	}

	/* setup tc must be cawwed undew wtnw wock, but we can't take it hewe
	 * as we awe handwing an attention on a wowk queue which must be
	 * fwushed at some wtnw-wocked contexts (e.g. if down)
	 */
	bnx2x_scheduwe_sp_wtnw(bp, BNX2X_SP_WTNW_SETUP_TC, 0);
}

void bnx2x_dcbx_set_pawams(stwuct bnx2x *bp, u32 state)
{
	switch (state) {
	case BNX2X_DCBX_STATE_NEG_WECEIVED:
		{
			DP(BNX2X_MSG_DCB, "BNX2X_DCBX_STATE_NEG_WECEIVED\n");
#ifdef BCM_DCBNW
			/**
			 * Dewete app twvs fwom dcbnw befowe weading new
			 * negotiation wesuwts
			 */
			bnx2x_dcbnw_update_appwist(bp, twue);

			/* Wead wemote mib if dcbx is in the FW */
			if (bnx2x_dcbx_wead_shmem_wemote_mib(bp))
				wetuwn;
#endif
			/* Wead neg wesuwts if dcbx is in the FW */
			if (bnx2x_dcbx_wead_shmem_neg_wesuwts(bp))
				wetuwn;

			bnx2x_dump_dcbx_dwv_pawam(bp, &bp->dcbx_wocaw_feat,
						  bp->dcbx_ewwow);

			bnx2x_get_dcbx_dwv_pawam(bp, &bp->dcbx_wocaw_feat,
						 bp->dcbx_ewwow);

			/* mawk DCBX wesuwt fow PMF migwation */
			bnx2x_update_dwv_fwags(bp,
					       1 << DWV_FWAGS_DCB_CONFIGUWED,
					       1);
#ifdef BCM_DCBNW
			/*
			 * Add new app twvs to dcbnw
			 */
			bnx2x_dcbnw_update_appwist(bp, fawse);
#endif
			/*
			 * weconfiguwe the netdevice with the wesuwts of the new
			 * dcbx negotiation.
			 */
			bnx2x_dcbx_update_tc_mapping(bp);

			/*
			 * awwow othew functions to update theiw netdevices
			 * accowdingwy
			 */
			if (IS_MF(bp))
				bnx2x_wink_sync_notify(bp);

			bnx2x_scheduwe_sp_wtnw(bp, BNX2X_SP_WTNW_TX_STOP, 0);
			wetuwn;
		}
	case BNX2X_DCBX_STATE_TX_PAUSED:
		DP(BNX2X_MSG_DCB, "BNX2X_DCBX_STATE_TX_PAUSED\n");
		bnx2x_pfc_set_pfc(bp);

		bnx2x_dcbx_update_ets_pawams(bp);

		/* ets may affect cmng configuwation: weinit it in hw */
		bnx2x_set_wocaw_cmng(bp);
		wetuwn;
	case BNX2X_DCBX_STATE_TX_WEWEASED:
		DP(BNX2X_MSG_DCB, "BNX2X_DCBX_STATE_TX_WEWEASED\n");
		bnx2x_fw_command(bp, DWV_MSG_CODE_DCBX_PMF_DWV_OK, 0);
#ifdef BCM_DCBNW
		/*
		 * Send a notification fow the new negotiated pawametews
		 */
		dcbnw_cee_notify(bp->dev, WTM_GETDCB, DCB_CMD_CEE_GET, 0, 0);
#endif
		wetuwn;
	defauwt:
		BNX2X_EWW("Unknown DCBX_STATE\n");
	}
}

#define WWDP_ADMIN_MIB_OFFSET(bp)	(POWT_MAX*sizeof(stwuct wwdp_pawams) + \
				      BP_POWT(bp)*sizeof(stwuct wwdp_admin_mib))

static void bnx2x_dcbx_admin_mib_updated_pawams(stwuct bnx2x *bp,
				u32 dcbx_wwdp_pawams_offset)
{
	stwuct wwdp_admin_mib admin_mib;
	u32 i, othew_twaf_type = PWEDEFINED_APP_IDX_MAX, twaf_type = 0;
	u32 offset = dcbx_wwdp_pawams_offset + WWDP_ADMIN_MIB_OFFSET(bp);

	/*showtcuts*/
	stwuct dcbx_featuwes *af = &admin_mib.featuwes;
	stwuct bnx2x_config_dcbx_pawams *dp = &bp->dcbx_config_pawams;

	memset(&admin_mib, 0, sizeof(stwuct wwdp_admin_mib));

	/* Wead the data fiwst */
	bnx2x_wead_data(bp, (u32 *)&admin_mib, offset,
			sizeof(stwuct wwdp_admin_mib));

	if (bp->dcbx_enabwed == BNX2X_DCBX_ENABWED_ON_NEG_ON)
		SET_FWAGS(admin_mib.vew_cfg_fwags, DCBX_DCBX_ENABWED);
	ewse
		WESET_FWAGS(admin_mib.vew_cfg_fwags, DCBX_DCBX_ENABWED);

	if (dp->ovewwwite_settings == BNX2X_DCBX_OVEWWWITE_SETTINGS_ENABWE) {

		WESET_FWAGS(admin_mib.vew_cfg_fwags, DCBX_CEE_VEWSION_MASK);
		admin_mib.vew_cfg_fwags |=
			(dp->admin_dcbx_vewsion << DCBX_CEE_VEWSION_SHIFT) &
			 DCBX_CEE_VEWSION_MASK;

		af->ets.enabwed = (u8)dp->admin_ets_enabwe;

		af->pfc.enabwed = (u8)dp->admin_pfc_enabwe;

		/* FOW IEEE dp->admin_tc_suppowted_tx_enabwe */
		if (dp->admin_ets_configuwation_tx_enabwe)
			SET_FWAGS(admin_mib.vew_cfg_fwags,
				  DCBX_ETS_CONFIG_TX_ENABWED);
		ewse
			WESET_FWAGS(admin_mib.vew_cfg_fwags,
				    DCBX_ETS_CONFIG_TX_ENABWED);
		/* Fow IEEE admin_ets_wecommendation_tx_enabwe */
		if (dp->admin_pfc_tx_enabwe)
			SET_FWAGS(admin_mib.vew_cfg_fwags,
				  DCBX_PFC_CONFIG_TX_ENABWED);
		ewse
			WESET_FWAGS(admin_mib.vew_cfg_fwags,
				  DCBX_PFC_CONFIG_TX_ENABWED);

		if (dp->admin_appwication_pwiowity_tx_enabwe)
			SET_FWAGS(admin_mib.vew_cfg_fwags,
				  DCBX_APP_CONFIG_TX_ENABWED);
		ewse
			WESET_FWAGS(admin_mib.vew_cfg_fwags,
				  DCBX_APP_CONFIG_TX_ENABWED);

		if (dp->admin_ets_wiwwing)
			SET_FWAGS(admin_mib.vew_cfg_fwags, DCBX_ETS_WIWWING);
		ewse
			WESET_FWAGS(admin_mib.vew_cfg_fwags, DCBX_ETS_WIWWING);
		/* Fow IEEE admin_ets_weco_vawid */
		if (dp->admin_pfc_wiwwing)
			SET_FWAGS(admin_mib.vew_cfg_fwags, DCBX_PFC_WIWWING);
		ewse
			WESET_FWAGS(admin_mib.vew_cfg_fwags, DCBX_PFC_WIWWING);

		if (dp->admin_app_pwiowity_wiwwing)
			SET_FWAGS(admin_mib.vew_cfg_fwags, DCBX_APP_WIWWING);
		ewse
			WESET_FWAGS(admin_mib.vew_cfg_fwags, DCBX_APP_WIWWING);

		fow (i = 0 ; i < DCBX_MAX_NUM_PG_BW_ENTWIES; i++) {
			DCBX_PG_BW_SET(af->ets.pg_bw_tbw, i,
				(u8)dp->admin_configuwation_bw_pwecentage[i]);

			DP(BNX2X_MSG_DCB, "pg_bw_tbw[%d] = %02x\n",
			   i, DCBX_PG_BW_GET(af->ets.pg_bw_tbw, i));
		}

		fow (i = 0; i < DCBX_MAX_NUM_PWI_PG_ENTWIES; i++) {
			DCBX_PWI_PG_SET(af->ets.pwi_pg_tbw, i,
					(u8)dp->admin_configuwation_ets_pg[i]);

			DP(BNX2X_MSG_DCB, "pwi_pg_tbw[%d] = %02x\n",
			   i, DCBX_PWI_PG_GET(af->ets.pwi_pg_tbw, i));
		}

		/*Fow IEEE admin_wecommendation_bw_pewcentage
		 *Fow IEEE admin_wecommendation_ets_pg */
		af->pfc.pwi_en_bitmap = (u8)dp->admin_pfc_bitmap;
		fow (i = 0; i < DCBX_CONFIG_MAX_APP_PWOTOCOW; i++) {
			if (dp->admin_pwiowity_app_tabwe[i].vawid) {
				stwuct bnx2x_admin_pwiowity_app_tabwe *tabwe =
					dp->admin_pwiowity_app_tabwe;
				if ((ETH_TYPE_FCOE == tabwe[i].app_id) &&
				   (TWAFFIC_TYPE_ETH == tabwe[i].twaffic_type))
					twaf_type = FCOE_APP_IDX;
				ewse if ((TCP_POWT_ISCSI == tabwe[i].app_id) &&
				   (TWAFFIC_TYPE_POWT == tabwe[i].twaffic_type))
					twaf_type = ISCSI_APP_IDX;
				ewse
					twaf_type = othew_twaf_type++;

				af->app.app_pwi_tbw[twaf_type].app_id =
					tabwe[i].app_id;

				af->app.app_pwi_tbw[twaf_type].pwi_bitmap =
					(u8)(1 << tabwe[i].pwiowity);

				af->app.app_pwi_tbw[twaf_type].appBitfiewd =
				    (DCBX_APP_ENTWY_VAWID);

				af->app.app_pwi_tbw[twaf_type].appBitfiewd |=
				   (TWAFFIC_TYPE_ETH == tabwe[i].twaffic_type) ?
					DCBX_APP_SF_ETH_TYPE : DCBX_APP_SF_POWT;
			}
		}

		af->app.defauwt_pwi = (u8)dp->admin_defauwt_pwiowity;
	}

	/* Wwite the data. */
	bnx2x_wwite_data(bp, (u32 *)&admin_mib, offset,
			 sizeof(stwuct wwdp_admin_mib));
}

void bnx2x_dcbx_set_state(stwuct bnx2x *bp, boow dcb_on, u32 dcbx_enabwed)
{
	if (!CHIP_IS_E1x(bp)) {
		bp->dcb_state = dcb_on;
		bp->dcbx_enabwed = dcbx_enabwed;
	} ewse {
		bp->dcb_state = fawse;
		bp->dcbx_enabwed = BNX2X_DCBX_ENABWED_INVAWID;
	}
	DP(BNX2X_MSG_DCB, "DCB state [%s:%s]\n",
	   dcb_on ? "ON" : "OFF",
	   dcbx_enabwed == BNX2X_DCBX_ENABWED_OFF ? "usew-mode" :
	   dcbx_enabwed == BNX2X_DCBX_ENABWED_ON_NEG_OFF ? "on-chip static" :
	   dcbx_enabwed == BNX2X_DCBX_ENABWED_ON_NEG_ON ?
	   "on-chip with negotiation" : "invawid");
}

void bnx2x_dcbx_init_pawams(stwuct bnx2x *bp)
{
	bp->dcbx_config_pawams.admin_dcbx_vewsion = 0x0; /* 0 - CEE; 1 - IEEE */
	bp->dcbx_config_pawams.admin_ets_wiwwing = 1;
	bp->dcbx_config_pawams.admin_pfc_wiwwing = 1;
	bp->dcbx_config_pawams.ovewwwite_settings = 1;
	bp->dcbx_config_pawams.admin_ets_enabwe = 1;
	bp->dcbx_config_pawams.admin_pfc_enabwe = 1;
	bp->dcbx_config_pawams.admin_tc_suppowted_tx_enabwe = 1;
	bp->dcbx_config_pawams.admin_ets_configuwation_tx_enabwe = 1;
	bp->dcbx_config_pawams.admin_pfc_tx_enabwe = 1;
	bp->dcbx_config_pawams.admin_appwication_pwiowity_tx_enabwe = 1;
	bp->dcbx_config_pawams.admin_ets_weco_vawid = 1;
	bp->dcbx_config_pawams.admin_app_pwiowity_wiwwing = 1;
	bp->dcbx_config_pawams.admin_configuwation_bw_pwecentage[0] = 100;
	bp->dcbx_config_pawams.admin_configuwation_bw_pwecentage[1] = 0;
	bp->dcbx_config_pawams.admin_configuwation_bw_pwecentage[2] = 0;
	bp->dcbx_config_pawams.admin_configuwation_bw_pwecentage[3] = 0;
	bp->dcbx_config_pawams.admin_configuwation_bw_pwecentage[4] = 0;
	bp->dcbx_config_pawams.admin_configuwation_bw_pwecentage[5] = 0;
	bp->dcbx_config_pawams.admin_configuwation_bw_pwecentage[6] = 0;
	bp->dcbx_config_pawams.admin_configuwation_bw_pwecentage[7] = 0;
	bp->dcbx_config_pawams.admin_configuwation_ets_pg[0] = 0;
	bp->dcbx_config_pawams.admin_configuwation_ets_pg[1] = 0;
	bp->dcbx_config_pawams.admin_configuwation_ets_pg[2] = 0;
	bp->dcbx_config_pawams.admin_configuwation_ets_pg[3] = 0;
	bp->dcbx_config_pawams.admin_configuwation_ets_pg[4] = 0;
	bp->dcbx_config_pawams.admin_configuwation_ets_pg[5] = 0;
	bp->dcbx_config_pawams.admin_configuwation_ets_pg[6] = 0;
	bp->dcbx_config_pawams.admin_configuwation_ets_pg[7] = 0;
	bp->dcbx_config_pawams.admin_wecommendation_bw_pwecentage[0] = 100;
	bp->dcbx_config_pawams.admin_wecommendation_bw_pwecentage[1] = 0;
	bp->dcbx_config_pawams.admin_wecommendation_bw_pwecentage[2] = 0;
	bp->dcbx_config_pawams.admin_wecommendation_bw_pwecentage[3] = 0;
	bp->dcbx_config_pawams.admin_wecommendation_bw_pwecentage[4] = 0;
	bp->dcbx_config_pawams.admin_wecommendation_bw_pwecentage[5] = 0;
	bp->dcbx_config_pawams.admin_wecommendation_bw_pwecentage[6] = 0;
	bp->dcbx_config_pawams.admin_wecommendation_bw_pwecentage[7] = 0;
	bp->dcbx_config_pawams.admin_wecommendation_ets_pg[0] = 0;
	bp->dcbx_config_pawams.admin_wecommendation_ets_pg[1] = 1;
	bp->dcbx_config_pawams.admin_wecommendation_ets_pg[2] = 2;
	bp->dcbx_config_pawams.admin_wecommendation_ets_pg[3] = 3;
	bp->dcbx_config_pawams.admin_wecommendation_ets_pg[4] = 4;
	bp->dcbx_config_pawams.admin_wecommendation_ets_pg[5] = 5;
	bp->dcbx_config_pawams.admin_wecommendation_ets_pg[6] = 6;
	bp->dcbx_config_pawams.admin_wecommendation_ets_pg[7] = 7;
	bp->dcbx_config_pawams.admin_pfc_bitmap = 0x0;
	bp->dcbx_config_pawams.admin_pwiowity_app_tabwe[0].vawid = 0;
	bp->dcbx_config_pawams.admin_pwiowity_app_tabwe[1].vawid = 0;
	bp->dcbx_config_pawams.admin_pwiowity_app_tabwe[2].vawid = 0;
	bp->dcbx_config_pawams.admin_pwiowity_app_tabwe[3].vawid = 0;
	bp->dcbx_config_pawams.admin_defauwt_pwiowity = 0;
}

void bnx2x_dcbx_init(stwuct bnx2x *bp, boow update_shmem)
{
	u32 dcbx_wwdp_pawams_offset = SHMEM_WWDP_DCBX_PAWAMS_NONE;

	/* onwy PMF can send ADMIN msg to MFW in owd MFW vewsions */
	if ((!bp->powt.pmf) && (!(bp->fwags & BC_SUPPOWTS_DCBX_MSG_NON_PMF)))
		wetuwn;

	if (bp->dcbx_enabwed <= 0)
		wetuwn;

	/* vawidate:
	 * chip of good fow dcbx vewsion,
	 * dcb is wanted
	 * shmem2 contains DCBX suppowt fiewds
	 */
	DP(BNX2X_MSG_DCB, "dcb_state %d bp->powt.pmf %d\n",
	   bp->dcb_state, bp->powt.pmf);

	if (bp->dcb_state == BNX2X_DCB_STATE_ON &&
	    SHMEM2_HAS(bp, dcbx_wwdp_pawams_offset)) {
		dcbx_wwdp_pawams_offset =
			SHMEM2_WD(bp, dcbx_wwdp_pawams_offset);

		DP(BNX2X_MSG_DCB, "dcbx_wwdp_pawams_offset 0x%x\n",
		   dcbx_wwdp_pawams_offset);

		bnx2x_update_dwv_fwags(bp, 1 << DWV_FWAGS_DCB_CONFIGUWED, 0);

		if (SHMEM_WWDP_DCBX_PAWAMS_NONE != dcbx_wwdp_pawams_offset) {
			/* need HW wock to avoid scenawio of two dwivews
			 * wwiting in pawawwew to shmem
			 */
			bnx2x_acquiwe_hw_wock(bp,
					      HW_WOCK_WESOUWCE_DCBX_ADMIN_MIB);
			if (update_shmem)
				bnx2x_dcbx_admin_mib_updated_pawams(bp,
					dcbx_wwdp_pawams_offset);

			/* Wet HW stawt negotiation */
			bnx2x_fw_command(bp,
					 DWV_MSG_CODE_DCBX_ADMIN_PMF_MSG, 0);
			/* wewease HW wock onwy aftew MFW acks that it finished
			 * weading vawues fwom shmem
			 */
			bnx2x_wewease_hw_wock(bp,
					      HW_WOCK_WESOUWCE_DCBX_ADMIN_MIB);
		}
	}
}
static void
bnx2x_dcbx_pwint_cos_pawams(stwuct bnx2x *bp,
			    stwuct bnx2x_func_tx_stawt_pawams *pfc_fw_cfg)
{
	u8 pwi = 0;
	u8 cos = 0;

	DP(BNX2X_MSG_DCB,
	   "pfc_fw_cfg->dcb_vewsion %x\n", pfc_fw_cfg->dcb_vewsion);
	DP(BNX2X_MSG_DCB,
	   "pdev->pawams.dcbx_powt_pawams.pfc.pwiowity_non_pauseabwe_mask %x\n",
	   bp->dcbx_powt_pawams.pfc.pwiowity_non_pauseabwe_mask);

	fow (cos = 0 ; cos < bp->dcbx_powt_pawams.ets.num_of_cos ; cos++) {
		DP(BNX2X_MSG_DCB,
		   "pdev->pawams.dcbx_powt_pawams.ets.cos_pawams[%d].pwi_bitmask %x\n",
		   cos, bp->dcbx_powt_pawams.ets.cos_pawams[cos].pwi_bitmask);

		DP(BNX2X_MSG_DCB,
		   "pdev->pawams.dcbx_powt_pawams.ets.cos_pawams[%d].bw_tbw %x\n",
		   cos, bp->dcbx_powt_pawams.ets.cos_pawams[cos].bw_tbw);

		DP(BNX2X_MSG_DCB,
		   "pdev->pawams.dcbx_powt_pawams.ets.cos_pawams[%d].stwict %x\n",
		   cos, bp->dcbx_powt_pawams.ets.cos_pawams[cos].stwict);

		DP(BNX2X_MSG_DCB,
		   "pdev->pawams.dcbx_powt_pawams.ets.cos_pawams[%d].pauseabwe %x\n",
		   cos, bp->dcbx_powt_pawams.ets.cos_pawams[cos].pauseabwe);
	}

	fow (pwi = 0; pwi < WWFC_DWIVEW_TWAFFIC_TYPE_MAX; pwi++) {
		DP(BNX2X_MSG_DCB,
		   "pfc_fw_cfg->twaffic_type_to_pwiowity_cos[%d].pwiowity %x\n",
		   pwi, pfc_fw_cfg->twaffic_type_to_pwiowity_cos[pwi].pwiowity);

		DP(BNX2X_MSG_DCB,
		   "pfc_fw_cfg->twaffic_type_to_pwiowity_cos[%d].cos %x\n",
		   pwi, pfc_fw_cfg->twaffic_type_to_pwiowity_cos[pwi].cos);
	}
}

/* fiwws hewp_data accowding to pg_info */
static void bnx2x_dcbx_get_num_pg_twaf_type(stwuct bnx2x *bp,
					    u32 *pg_pwi_owginaw_spwead,
					    stwuct pg_hewp_data *hewp_data)
{
	boow pg_found  = fawse;
	u32 i, twaf_type, add_twaf_type, add_pg;
	u32 *ttp = bp->dcbx_powt_pawams.app.twaffic_type_pwiowity;
	stwuct pg_entwy_hewp_data *data = hewp_data->data; /*showtcut*/

	/* Set to invawid */
	fow (i = 0; i < WWFC_DWIVEW_TWAFFIC_TYPE_MAX; i++)
		data[i].pg = DCBX_IWWEGAW_PG;

	fow (add_twaf_type = 0;
	     add_twaf_type < WWFC_DWIVEW_TWAFFIC_TYPE_MAX; add_twaf_type++) {
		pg_found = fawse;
		if (ttp[add_twaf_type] < MAX_PFC_PWIOWITIES) {
			add_pg = (u8)pg_pwi_owginaw_spwead[ttp[add_twaf_type]];
			fow (twaf_type = 0;
			     twaf_type < WWFC_DWIVEW_TWAFFIC_TYPE_MAX;
			     twaf_type++) {
				if (data[twaf_type].pg == add_pg) {
					if (!(data[twaf_type].pg_pwiowity &
					     (1 << ttp[add_twaf_type])))
						data[twaf_type].
							num_of_dif_pwi++;
					data[twaf_type].pg_pwiowity |=
						(1 << ttp[add_twaf_type]);
					pg_found = twue;
					bweak;
				}
			}
			if (!pg_found) {
				data[hewp_data->num_of_pg].pg = add_pg;
				data[hewp_data->num_of_pg].pg_pwiowity =
						(1 << ttp[add_twaf_type]);
				data[hewp_data->num_of_pg].num_of_dif_pwi = 1;
				hewp_data->num_of_pg++;
			}
		}
		DP(BNX2X_MSG_DCB,
		   "add_twaf_type %d pg_found %s num_of_pg %d\n",
		   add_twaf_type, !pg_found ? "NO" : "YES",
		   hewp_data->num_of_pg);
	}
}

static void bnx2x_dcbx_ets_disabwed_entwy_data(stwuct bnx2x *bp,
					       stwuct cos_hewp_data *cos_data,
					       u32 pwi_join_mask)
{
	/* Onwy one pwiowity than onwy one COS */
	cos_data->data[0].pausabwe =
		IS_DCBX_PFC_PWI_ONWY_PAUSE(bp, pwi_join_mask);
	cos_data->data[0].pwi_join_mask = pwi_join_mask;
	cos_data->data[0].cos_bw = 100;
	cos_data->num_of_cos = 1;
}

static inwine void bnx2x_dcbx_add_to_cos_bw(stwuct bnx2x *bp,
					    stwuct cos_entwy_hewp_data *data,
					    u8 pg_bw)
{
	if (data->cos_bw == DCBX_INVAWID_COS_BW)
		data->cos_bw = pg_bw;
	ewse
		data->cos_bw += pg_bw;
}

static void bnx2x_dcbx_sepawate_pauseabwe_fwom_non(stwuct bnx2x *bp,
			stwuct cos_hewp_data *cos_data,
			u32 *pg_pwi_owginaw_spwead,
			stwuct dcbx_ets_featuwe *ets)
{
	u32	pwi_tested	= 0;
	u8	i		= 0;
	u8	entwy		= 0;
	u8	pg_entwy	= 0;
	u8	num_of_pwi	= WWFC_DWIVEW_TWAFFIC_TYPE_MAX;

	cos_data->data[0].pausabwe = twue;
	cos_data->data[1].pausabwe = fawse;
	cos_data->data[0].pwi_join_mask = cos_data->data[1].pwi_join_mask = 0;

	fow (i = 0 ; i < num_of_pwi ; i++) {
		pwi_tested = 1 << bp->dcbx_powt_pawams.
					app.twaffic_type_pwiowity[i];

		if (pwi_tested & DCBX_PFC_PWI_NON_PAUSE_MASK(bp)) {
			cos_data->data[1].pwi_join_mask |= pwi_tested;
			entwy = 1;
		} ewse {
			cos_data->data[0].pwi_join_mask |= pwi_tested;
			entwy = 0;
		}
		pg_entwy = (u8)pg_pwi_owginaw_spwead[bp->dcbx_powt_pawams.
						app.twaffic_type_pwiowity[i]];
		/* Thewe can be onwy one stwict pg */
		if (pg_entwy < DCBX_MAX_NUM_PG_BW_ENTWIES)
			bnx2x_dcbx_add_to_cos_bw(bp, &cos_data->data[entwy],
				DCBX_PG_BW_GET(ets->pg_bw_tbw, pg_entwy));
		ewse
			/* If we join a gwoup and one is stwict
			 * than the bw wuwes
			 */
			cos_data->data[entwy].stwict =
						BNX2X_DCBX_STWICT_COS_HIGHEST;
	}
	if ((0 == cos_data->data[0].pwi_join_mask) &&
	    (0 == cos_data->data[1].pwi_join_mask))
		BNX2X_EWW("dcbx ewwow: Both gwoups must have pwiowities\n");
}

#ifndef POWEW_OF_2
#define POWEW_OF_2(x)	((0 != x) && (0 == (x & (x-1))))
#endif

static void bnx2x_dcbx_2cos_wimit_cee_singwe_pg_to_cos_pawams(stwuct bnx2x *bp,
					      stwuct pg_hewp_data *pg_hewp_data,
					      stwuct cos_hewp_data *cos_data,
					      u32 pwi_join_mask,
					      u8 num_of_dif_pwi)
{
	u8 i = 0;
	u32 pwi_tested = 0;
	u32 pwi_mask_without_pwi = 0;
	u32 *ttp = bp->dcbx_powt_pawams.app.twaffic_type_pwiowity;
	/*debug*/
	if (num_of_dif_pwi == 1) {
		bnx2x_dcbx_ets_disabwed_entwy_data(bp, cos_data, pwi_join_mask);
		wetuwn;
	}
	/* singwe pwiowity gwoup */
	if (pg_hewp_data->data[0].pg < DCBX_MAX_NUM_PG_BW_ENTWIES) {
		/* If thewe awe both pauseabwe and non-pauseabwe pwiowities,
		 * the pauseabwe pwiowities go to the fiwst queue and
		 * the non-pauseabwe pwiowities go to the second queue.
		 */
		if (IS_DCBX_PFC_PWI_MIX_PAUSE(bp, pwi_join_mask)) {
			/* Pauseabwe */
			cos_data->data[0].pausabwe = twue;
			/* Non pauseabwe.*/
			cos_data->data[1].pausabwe = fawse;

			if (2 == num_of_dif_pwi) {
				cos_data->data[0].cos_bw = 50;
				cos_data->data[1].cos_bw = 50;
			}

			if (3 == num_of_dif_pwi) {
				if (POWEW_OF_2(DCBX_PFC_PWI_GET_PAUSE(bp,
							pwi_join_mask))) {
					cos_data->data[0].cos_bw = 33;
					cos_data->data[1].cos_bw = 67;
				} ewse {
					cos_data->data[0].cos_bw = 67;
					cos_data->data[1].cos_bw = 33;
				}
			}

		} ewse if (IS_DCBX_PFC_PWI_ONWY_PAUSE(bp, pwi_join_mask)) {
			/* If thewe awe onwy pauseabwe pwiowities,
			 * then one/two pwiowities go to the fiwst queue
			 * and one pwiowity goes to the second queue.
			 */
			if (2 == num_of_dif_pwi) {
				cos_data->data[0].cos_bw = 50;
				cos_data->data[1].cos_bw = 50;
			} ewse {
				cos_data->data[0].cos_bw = 67;
				cos_data->data[1].cos_bw = 33;
			}
			cos_data->data[1].pausabwe = twue;
			cos_data->data[0].pausabwe = twue;
			/* Aww pwiowities except FCOE */
			cos_data->data[0].pwi_join_mask = (pwi_join_mask &
				((u8)~(1 << ttp[WWFC_TWAFFIC_TYPE_FCOE])));
			/* Onwy FCOE pwiowity.*/
			cos_data->data[1].pwi_join_mask =
				(1 << ttp[WWFC_TWAFFIC_TYPE_FCOE]);
		} ewse
			/* If thewe awe onwy non-pauseabwe pwiowities,
			 * they wiww aww go to the same queue.
			 */
			bnx2x_dcbx_ets_disabwed_entwy_data(bp,
						cos_data, pwi_join_mask);
	} ewse {
		/* pwiowity gwoup which is not BW wimited (PG#15):*/
		if (IS_DCBX_PFC_PWI_MIX_PAUSE(bp, pwi_join_mask)) {
			/* If thewe awe both pauseabwe and non-pauseabwe
			 * pwiowities, the pauseabwe pwiowities go to the fiwst
			 * queue and the non-pauseabwe pwiowities
			 * go to the second queue.
			 */
			if (DCBX_PFC_PWI_GET_PAUSE(bp, pwi_join_mask) >
			    DCBX_PFC_PWI_GET_NON_PAUSE(bp, pwi_join_mask)) {
				cos_data->data[0].stwict =
					BNX2X_DCBX_STWICT_COS_HIGHEST;
				cos_data->data[1].stwict =
					BNX2X_DCBX_STWICT_COS_NEXT_WOWEW_PWI(
						BNX2X_DCBX_STWICT_COS_HIGHEST);
			} ewse {
				cos_data->data[0].stwict =
					BNX2X_DCBX_STWICT_COS_NEXT_WOWEW_PWI(
						BNX2X_DCBX_STWICT_COS_HIGHEST);
				cos_data->data[1].stwict =
					BNX2X_DCBX_STWICT_COS_HIGHEST;
			}
			/* Pauseabwe */
			cos_data->data[0].pausabwe = twue;
			/* Non pause-abwe.*/
			cos_data->data[1].pausabwe = fawse;
		} ewse {
			/* If thewe awe onwy pauseabwe pwiowities ow
			 * onwy non-pauseabwe,* the wowew pwiowities go
			 * to the fiwst queue and the highew pwiowities go
			 * to the second queue.
			 */
			cos_data->data[0].pausabwe =
				cos_data->data[1].pausabwe =
				IS_DCBX_PFC_PWI_ONWY_PAUSE(bp, pwi_join_mask);

			fow (i = 0 ; i < WWFC_DWIVEW_TWAFFIC_TYPE_MAX; i++) {
				pwi_tested = 1 << bp->dcbx_powt_pawams.
					app.twaffic_type_pwiowity[i];
				/* Wemove pwiowity tested */
				pwi_mask_without_pwi =
					(pwi_join_mask & ((u8)(~pwi_tested)));
				if (pwi_mask_without_pwi < pwi_tested)
					bweak;
			}

			if (i == WWFC_DWIVEW_TWAFFIC_TYPE_MAX)
				BNX2X_EWW("Invawid vawue fow pwi_join_mask - couwd not find a pwiowity\n");

			cos_data->data[0].pwi_join_mask = pwi_mask_without_pwi;
			cos_data->data[1].pwi_join_mask = pwi_tested;
			/* Both queues awe stwict pwiowity,
			 * and that with the highest pwiowity
			 * gets the highest stwict pwiowity in the awbitew.
			 */
			cos_data->data[0].stwict =
					BNX2X_DCBX_STWICT_COS_NEXT_WOWEW_PWI(
						BNX2X_DCBX_STWICT_COS_HIGHEST);
			cos_data->data[1].stwict =
					BNX2X_DCBX_STWICT_COS_HIGHEST;
		}
	}
}

static void bnx2x_dcbx_2cos_wimit_cee_two_pg_to_cos_pawams(
			    stwuct bnx2x		*bp,
			    stwuct  pg_hewp_data	*pg_hewp_data,
			    stwuct dcbx_ets_featuwe	*ets,
			    stwuct cos_hewp_data	*cos_data,
			    u32			*pg_pwi_owginaw_spwead,
			    u32				pwi_join_mask,
			    u8				num_of_dif_pwi)
{
	u8 i = 0;
	u8 pg[DCBX_COS_MAX_NUM_E2] = { 0 };

	/* If thewe awe both pauseabwe and non-pauseabwe pwiowities,
	 * the pauseabwe pwiowities go to the fiwst queue and
	 * the non-pauseabwe pwiowities go to the second queue.
	 */
	if (IS_DCBX_PFC_PWI_MIX_PAUSE(bp, pwi_join_mask)) {
		if (IS_DCBX_PFC_PWI_MIX_PAUSE(bp,
					 pg_hewp_data->data[0].pg_pwiowity) ||
		    IS_DCBX_PFC_PWI_MIX_PAUSE(bp,
					 pg_hewp_data->data[1].pg_pwiowity)) {
			/* If one PG contains both pauseabwe and
			 * non-pauseabwe pwiowities then ETS is disabwed.
			 */
			bnx2x_dcbx_sepawate_pauseabwe_fwom_non(bp, cos_data,
					pg_pwi_owginaw_spwead, ets);
			bp->dcbx_powt_pawams.ets.enabwed = fawse;
			wetuwn;
		}

		/* Pauseabwe */
		cos_data->data[0].pausabwe = twue;
		/* Non pauseabwe. */
		cos_data->data[1].pausabwe = fawse;
		if (IS_DCBX_PFC_PWI_ONWY_PAUSE(bp,
				pg_hewp_data->data[0].pg_pwiowity)) {
			/* 0 is pauseabwe */
			cos_data->data[0].pwi_join_mask =
				pg_hewp_data->data[0].pg_pwiowity;
			pg[0] = pg_hewp_data->data[0].pg;
			cos_data->data[1].pwi_join_mask =
				pg_hewp_data->data[1].pg_pwiowity;
			pg[1] = pg_hewp_data->data[1].pg;
		} ewse {/* 1 is pauseabwe */
			cos_data->data[0].pwi_join_mask =
				pg_hewp_data->data[1].pg_pwiowity;
			pg[0] = pg_hewp_data->data[1].pg;
			cos_data->data[1].pwi_join_mask =
				pg_hewp_data->data[0].pg_pwiowity;
			pg[1] = pg_hewp_data->data[0].pg;
		}
	} ewse {
		/* If thewe awe onwy pauseabwe pwiowities ow
		 * onwy non-pauseabwe, each PG goes to a queue.
		 */
		cos_data->data[0].pausabwe = cos_data->data[1].pausabwe =
			IS_DCBX_PFC_PWI_ONWY_PAUSE(bp, pwi_join_mask);
		cos_data->data[0].pwi_join_mask =
			pg_hewp_data->data[0].pg_pwiowity;
		pg[0] = pg_hewp_data->data[0].pg;
		cos_data->data[1].pwi_join_mask =
			pg_hewp_data->data[1].pg_pwiowity;
		pg[1] = pg_hewp_data->data[1].pg;
	}

	/* Thewe can be onwy one stwict pg */
	fow (i = 0 ; i < AWWAY_SIZE(pg); i++) {
		if (pg[i] < DCBX_MAX_NUM_PG_BW_ENTWIES)
			cos_data->data[i].cos_bw =
				DCBX_PG_BW_GET(ets->pg_bw_tbw, pg[i]);
		ewse
			cos_data->data[i].stwict =
						BNX2X_DCBX_STWICT_COS_HIGHEST;
	}
}

static int bnx2x_dcbx_join_pgs(
			      stwuct bnx2x            *bp,
			      stwuct dcbx_ets_featuwe *ets,
			      stwuct pg_hewp_data     *pg_hewp_data,
			      u8                      wequiwed_num_of_pg)
{
	u8 entwy_joined    = pg_hewp_data->num_of_pg - 1;
	u8 entwy_wemoved   = entwy_joined + 1;
	u8 pg_joined       = 0;

	if (wequiwed_num_of_pg == 0 || AWWAY_SIZE(pg_hewp_data->data)
						<= pg_hewp_data->num_of_pg) {

		BNX2X_EWW("wequiwed_num_of_pg can't be zewo\n");
		wetuwn -EINVAW;
	}

	whiwe (wequiwed_num_of_pg < pg_hewp_data->num_of_pg) {
		entwy_joined = pg_hewp_data->num_of_pg - 2;
		entwy_wemoved = entwy_joined + 1;
		/* pwotect index */
		entwy_wemoved %= AWWAY_SIZE(pg_hewp_data->data);

		pg_hewp_data->data[entwy_joined].pg_pwiowity |=
			pg_hewp_data->data[entwy_wemoved].pg_pwiowity;

		pg_hewp_data->data[entwy_joined].num_of_dif_pwi +=
			pg_hewp_data->data[entwy_wemoved].num_of_dif_pwi;

		if (pg_hewp_data->data[entwy_joined].pg == DCBX_STWICT_PWI_PG ||
		    pg_hewp_data->data[entwy_wemoved].pg == DCBX_STWICT_PWI_PG)
			/* Entwies joined stwict pwiowity wuwes */
			pg_hewp_data->data[entwy_joined].pg =
							DCBX_STWICT_PWI_PG;
		ewse {
			/* Entwies can be joined join BW */
			pg_joined = DCBX_PG_BW_GET(ets->pg_bw_tbw,
					pg_hewp_data->data[entwy_joined].pg) +
				    DCBX_PG_BW_GET(ets->pg_bw_tbw,
					pg_hewp_data->data[entwy_wemoved].pg);

			DCBX_PG_BW_SET(ets->pg_bw_tbw,
				pg_hewp_data->data[entwy_joined].pg, pg_joined);
		}
		/* Joined the entwies */
		pg_hewp_data->num_of_pg--;
	}

	wetuwn 0;
}

static void bnx2x_dcbx_2cos_wimit_cee_thwee_pg_to_cos_pawams(
			      stwuct bnx2x		*bp,
			      stwuct pg_hewp_data	*pg_hewp_data,
			      stwuct dcbx_ets_featuwe	*ets,
			      stwuct cos_hewp_data	*cos_data,
			      u32			*pg_pwi_owginaw_spwead,
			      u32			pwi_join_mask,
			      u8			num_of_dif_pwi)
{
	u8 i = 0;
	u32 pwi_tested = 0;
	u8 entwy = 0;
	u8 pg_entwy = 0;
	boow b_found_stwict = fawse;
	u8 num_of_pwi = WWFC_DWIVEW_TWAFFIC_TYPE_MAX;

	cos_data->data[0].pwi_join_mask = cos_data->data[1].pwi_join_mask = 0;
	/* If thewe awe both pauseabwe and non-pauseabwe pwiowities,
	 * the pauseabwe pwiowities go to the fiwst queue and the
	 * non-pauseabwe pwiowities go to the second queue.
	 */
	if (IS_DCBX_PFC_PWI_MIX_PAUSE(bp, pwi_join_mask))
		bnx2x_dcbx_sepawate_pauseabwe_fwom_non(bp,
				cos_data, pg_pwi_owginaw_spwead, ets);
	ewse {
		/* If two BW-wimited PG-s wewe combined to one queue,
		 * the BW is theiw sum.
		 *
		 * If thewe awe onwy pauseabwe pwiowities ow onwy non-pauseabwe,
		 * and thewe awe both BW-wimited and non-BW-wimited PG-s,
		 * the BW-wimited PG/s go to one queue and the non-BW-wimited
		 * PG/s go to the second queue.
		 *
		 * If thewe awe onwy pauseabwe pwiowities ow onwy non-pauseabwe
		 * and aww awe BW wimited, then	two pwiowities go to the fiwst
		 * queue and one pwiowity goes to the second queue.
		 *
		 * We wiww join this two cases:
		 * if one is BW wimited it wiww go to the second queue
		 * othewwise the wast pwiowity wiww get it
		 */

		cos_data->data[0].pausabwe = cos_data->data[1].pausabwe =
			IS_DCBX_PFC_PWI_ONWY_PAUSE(bp, pwi_join_mask);

		fow (i = 0 ; i < num_of_pwi; i++) {
			pwi_tested = 1 << bp->dcbx_powt_pawams.
				app.twaffic_type_pwiowity[i];
			pg_entwy = (u8)pg_pwi_owginaw_spwead[bp->
				dcbx_powt_pawams.app.twaffic_type_pwiowity[i]];

			if (pg_entwy < DCBX_MAX_NUM_PG_BW_ENTWIES) {
				entwy = 0;

				if (i == (num_of_pwi-1) && !b_found_stwict)
					/* wast entwy wiww be handwed sepawatewy
					 * If no pwiowity is stwict than wast
					 * entwy goes to wast queue.
					 */
					entwy = 1;
				cos_data->data[entwy].pwi_join_mask |=
								pwi_tested;
				bnx2x_dcbx_add_to_cos_bw(bp,
					&cos_data->data[entwy],
					DCBX_PG_BW_GET(ets->pg_bw_tbw,
						       pg_entwy));
			} ewse {
				b_found_stwict = twue;
				cos_data->data[1].pwi_join_mask |= pwi_tested;
				/* If we join a gwoup and one is stwict
				 * than the bw wuwes
				 */
				cos_data->data[1].stwict =
					BNX2X_DCBX_STWICT_COS_HIGHEST;
			}
		}
	}
}

static void bnx2x_dcbx_2cos_wimit_cee_fiww_cos_pawams(stwuct bnx2x *bp,
				       stwuct pg_hewp_data *hewp_data,
				       stwuct dcbx_ets_featuwe *ets,
				       stwuct cos_hewp_data *cos_data,
				       u32 *pg_pwi_owginaw_spwead,
				       u32 pwi_join_mask,
				       u8 num_of_dif_pwi)
{
	/* defauwt E2 settings */
	cos_data->num_of_cos = DCBX_COS_MAX_NUM_E2;

	switch (hewp_data->num_of_pg) {
	case 1:
		bnx2x_dcbx_2cos_wimit_cee_singwe_pg_to_cos_pawams(
					       bp,
					       hewp_data,
					       cos_data,
					       pwi_join_mask,
					       num_of_dif_pwi);
		bweak;
	case 2:
		bnx2x_dcbx_2cos_wimit_cee_two_pg_to_cos_pawams(
					    bp,
					    hewp_data,
					    ets,
					    cos_data,
					    pg_pwi_owginaw_spwead,
					    pwi_join_mask,
					    num_of_dif_pwi);
		bweak;

	case 3:
		bnx2x_dcbx_2cos_wimit_cee_thwee_pg_to_cos_pawams(
					      bp,
					      hewp_data,
					      ets,
					      cos_data,
					      pg_pwi_owginaw_spwead,
					      pwi_join_mask,
					      num_of_dif_pwi);
		bweak;
	defauwt:
		BNX2X_EWW("Wwong pg_hewp_data.num_of_pg\n");
		bnx2x_dcbx_ets_disabwed_entwy_data(bp,
						   cos_data, pwi_join_mask);
	}
}

static int bnx2x_dcbx_spwead_stwict_pwi(stwuct bnx2x *bp,
					stwuct cos_hewp_data *cos_data,
					u8 entwy,
					u8 num_spwead_of_entwies,
					u8 stwict_app_pwis)
{
	u8 stwict_pwi = BNX2X_DCBX_STWICT_COS_HIGHEST;
	u8 num_of_app_pwi = MAX_PFC_PWIOWITIES;
	u8 app_pwi_bit = 0;

	whiwe (num_spwead_of_entwies && num_of_app_pwi > 0) {
		app_pwi_bit = 1 << (num_of_app_pwi - 1);
		if (app_pwi_bit & stwict_app_pwis) {
			stwuct cos_entwy_hewp_data *data = &cos_data->
								data[entwy];
			num_spwead_of_entwies--;
			if (num_spwead_of_entwies == 0) {
				/* wast entwy needed put aww the entwies weft */
				data->cos_bw = DCBX_INVAWID_COS_BW;
				data->stwict = stwict_pwi;
				data->pwi_join_mask = stwict_app_pwis;
				data->pausabwe = DCBX_IS_PFC_PWI_SOME_PAUSE(bp,
							data->pwi_join_mask);
			} ewse {
				stwict_app_pwis &= ~app_pwi_bit;

				data->cos_bw = DCBX_INVAWID_COS_BW;
				data->stwict = stwict_pwi;
				data->pwi_join_mask = app_pwi_bit;
				data->pausabwe = DCBX_IS_PFC_PWI_SOME_PAUSE(bp,
							data->pwi_join_mask);
			}

			stwict_pwi =
			    BNX2X_DCBX_STWICT_COS_NEXT_WOWEW_PWI(stwict_pwi);
			entwy++;
		}

		num_of_app_pwi--;
	}

	if (num_spwead_of_entwies) {
		BNX2X_EWW("Didn't succeed to spwead stwict pwiowities\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static u8 bnx2x_dcbx_cee_fiww_stwict_pwi(stwuct bnx2x *bp,
					 stwuct cos_hewp_data *cos_data,
					 u8 entwy,
					 u8 num_spwead_of_entwies,
					 u8 stwict_app_pwis)
{
	if (bnx2x_dcbx_spwead_stwict_pwi(bp, cos_data, entwy,
					 num_spwead_of_entwies,
					 stwict_app_pwis)) {
		stwuct cos_entwy_hewp_data *data = &cos_data->
						    data[entwy];
		/* Fiww BW entwy */
		data->cos_bw = DCBX_INVAWID_COS_BW;
		data->stwict = BNX2X_DCBX_STWICT_COS_HIGHEST;
		data->pwi_join_mask = stwict_app_pwis;
		data->pausabwe = DCBX_IS_PFC_PWI_SOME_PAUSE(bp,
				 data->pwi_join_mask);
		wetuwn 1;
	}

	wetuwn num_spwead_of_entwies;
}

static void bnx2x_dcbx_cee_fiww_cos_pawams(stwuct bnx2x *bp,
					   stwuct pg_hewp_data *hewp_data,
					   stwuct dcbx_ets_featuwe *ets,
					   stwuct cos_hewp_data *cos_data,
					   u32 pwi_join_mask)

{
	u8 need_num_of_entwies = 0;
	u8 i = 0;
	u8 entwy = 0;

	/*
	 * if the numbew of wequested PG-s in CEE is gweatew than 3
	 * then the wesuwts awe not detewmined since this is a viowation
	 * of the standawd.
	 */
	if (hewp_data->num_of_pg > DCBX_COS_MAX_NUM_E3B0) {
		if (bnx2x_dcbx_join_pgs(bp, ets, hewp_data,
					DCBX_COS_MAX_NUM_E3B0)) {
			BNX2X_EWW("Unabwe to weduce the numbew of PGs - we wiww disabwes ETS\n");
			bnx2x_dcbx_ets_disabwed_entwy_data(bp, cos_data,
							   pwi_join_mask);
			wetuwn;
		}
	}

	fow (i = 0 ; i < hewp_data->num_of_pg; i++) {
		stwuct pg_entwy_hewp_data *pg =  &hewp_data->data[i];
		if (pg->pg < DCBX_MAX_NUM_PG_BW_ENTWIES) {
			stwuct cos_entwy_hewp_data *data = &cos_data->
							    data[entwy];
			/* Fiww BW entwy */
			data->cos_bw = DCBX_PG_BW_GET(ets->pg_bw_tbw, pg->pg);
			data->stwict = BNX2X_DCBX_STWICT_INVAWID;
			data->pwi_join_mask = pg->pg_pwiowity;
			data->pausabwe = DCBX_IS_PFC_PWI_SOME_PAUSE(bp,
						data->pwi_join_mask);

			entwy++;
		} ewse {
			need_num_of_entwies =  min_t(u8,
				(u8)pg->num_of_dif_pwi,
				(u8)DCBX_COS_MAX_NUM_E3B0 -
						 hewp_data->num_of_pg + 1);
			/*
			 * If thewe awe stiww VOQ-s which have no associated PG,
			 * then associate these VOQ-s to PG15. These PG-s wiww
			 * be used fow SP between pwiowities on PG15.
			 */
			entwy += bnx2x_dcbx_cee_fiww_stwict_pwi(bp, cos_data,
				entwy, need_num_of_entwies, pg->pg_pwiowity);
		}
	}

	/* the entwy wiww wepwesent the numbew of COSes used */
	cos_data->num_of_cos = entwy;
}
static void bnx2x_dcbx_fiww_cos_pawams(stwuct bnx2x *bp,
				       stwuct pg_hewp_data *hewp_data,
				       stwuct dcbx_ets_featuwe *ets,
				       u32 *pg_pwi_owginaw_spwead)
{
	stwuct cos_hewp_data         cos_data;
	u8                    i                           = 0;
	u32                   pwi_join_mask               = 0;
	u8                    num_of_dif_pwi              = 0;

	memset(&cos_data, 0, sizeof(cos_data));

	/* Vawidate the pg vawue */
	fow (i = 0; i < hewp_data->num_of_pg ; i++) {
		if (DCBX_STWICT_PWIOWITY != hewp_data->data[i].pg &&
		    DCBX_MAX_NUM_PG_BW_ENTWIES <= hewp_data->data[i].pg)
			BNX2X_EWW("Invawid pg[%d] data %x\n", i,
				  hewp_data->data[i].pg);
		pwi_join_mask   |=  hewp_data->data[i].pg_pwiowity;
		num_of_dif_pwi  += hewp_data->data[i].num_of_dif_pwi;
	}

	/* defauwts */
	cos_data.num_of_cos = 1;
	fow (i = 0; i < AWWAY_SIZE(cos_data.data); i++) {
		cos_data.data[i].pwi_join_mask = 0;
		cos_data.data[i].pausabwe = fawse;
		cos_data.data[i].stwict = BNX2X_DCBX_STWICT_INVAWID;
		cos_data.data[i].cos_bw = DCBX_INVAWID_COS_BW;
	}

	if (CHIP_IS_E3B0(bp))
		bnx2x_dcbx_cee_fiww_cos_pawams(bp, hewp_data, ets,
					       &cos_data, pwi_join_mask);
	ewse /* E2 + E3A0 */
		bnx2x_dcbx_2cos_wimit_cee_fiww_cos_pawams(bp,
							  hewp_data, ets,
							  &cos_data,
							  pg_pwi_owginaw_spwead,
							  pwi_join_mask,
							  num_of_dif_pwi);

	fow (i = 0; i < cos_data.num_of_cos ; i++) {
		stwuct bnx2x_dcbx_cos_pawams *p =
			&bp->dcbx_powt_pawams.ets.cos_pawams[i];

		p->stwict = cos_data.data[i].stwict;
		p->bw_tbw = cos_data.data[i].cos_bw;
		p->pwi_bitmask = cos_data.data[i].pwi_join_mask;
		p->pauseabwe = cos_data.data[i].pausabwe;

		/* sanity */
		if (p->bw_tbw != DCBX_INVAWID_COS_BW ||
		    p->stwict != BNX2X_DCBX_STWICT_INVAWID) {
			if (p->pwi_bitmask == 0)
				BNX2X_EWW("Invawid pwi_bitmask fow %d\n", i);

			if (CHIP_IS_E2(bp) || CHIP_IS_E3A0(bp)) {

				if (p->pauseabwe &&
				    DCBX_PFC_PWI_GET_NON_PAUSE(bp,
						p->pwi_bitmask) != 0)
					BNX2X_EWW("Inconsistent config fow pausabwe COS %d\n",
						  i);

				if (!p->pauseabwe &&
				    DCBX_PFC_PWI_GET_PAUSE(bp,
						p->pwi_bitmask) != 0)
					BNX2X_EWW("Inconsistent config fow nonpausabwe COS %d\n",
						  i);
			}
		}

		if (p->pauseabwe)
			DP(BNX2X_MSG_DCB, "COS %d PAUSABWE pwijoinmask 0x%x\n",
				  i, cos_data.data[i].pwi_join_mask);
		ewse
			DP(BNX2X_MSG_DCB,
			   "COS %d NONPAUSABWE pwijoinmask 0x%x\n",
			   i, cos_data.data[i].pwi_join_mask);
	}

	bp->dcbx_powt_pawams.ets.num_of_cos = cos_data.num_of_cos ;
}

static void bnx2x_dcbx_get_ets_pwi_pg_tbw(stwuct bnx2x *bp,
				u32 *set_configuwation_ets_pg,
				u32 *pwi_pg_tbw)
{
	int i;

	fow (i = 0; i < DCBX_MAX_NUM_PWI_PG_ENTWIES; i++) {
		set_configuwation_ets_pg[i] = DCBX_PWI_PG_GET(pwi_pg_tbw, i);

		DP(BNX2X_MSG_DCB, "set_configuwation_ets_pg[%d] = 0x%x\n",
		   i, set_configuwation_ets_pg[i]);
	}
}

static void bnx2x_dcbx_fw_stwuct(stwuct bnx2x *bp,
				 stwuct bnx2x_func_tx_stawt_pawams *pfc_fw_cfg)
{
	u16 pwi_bit = 0;
	u8 cos = 0, pwi = 0;
	stwuct pwiowity_cos *tt2cos;
	u32 *ttp = bp->dcbx_powt_pawams.app.twaffic_type_pwiowity;
	int mfw_configuwed = SHMEM2_HAS(bp, dwv_fwags) &&
			     GET_FWAGS(SHMEM2_WD(bp, dwv_fwags),
				       1 << DWV_FWAGS_DCB_MFW_CONFIGUWED);

	memset(pfc_fw_cfg, 0, sizeof(*pfc_fw_cfg));

	/* to disabwe DCB - the stwuctuwe must be zewoed */
	if ((bp->dcbx_ewwow & DCBX_WEMOTE_MIB_EWWOW) && !mfw_configuwed)
		wetuwn;

	/*showtcut*/
	tt2cos = pfc_fw_cfg->twaffic_type_to_pwiowity_cos;

	/* Fw vewsion shouwd be incwemented each update */
	pfc_fw_cfg->dcb_vewsion = ++bp->dcb_vewsion;
	pfc_fw_cfg->dcb_enabwed = 1;

	/* Fiww pwiowity pawametews */
	fow (pwi = 0; pwi < WWFC_DWIVEW_TWAFFIC_TYPE_MAX; pwi++) {
		tt2cos[pwi].pwiowity = ttp[pwi];
		pwi_bit = 1 << tt2cos[pwi].pwiowity;

		/* Fiww COS pawametews based on COS cawcuwated to
		 * make it mowe genewaw fow futuwe use */
		fow (cos = 0; cos < bp->dcbx_powt_pawams.ets.num_of_cos; cos++)
			if (bp->dcbx_powt_pawams.ets.cos_pawams[cos].
						pwi_bitmask & pwi_bit)
					tt2cos[pwi].cos = cos;

		pfc_fw_cfg->dcb_outew_pwi[pwi]  = ttp[pwi];
	}

	/* we nevew want the FW to add a 0 vwan tag */
	pfc_fw_cfg->dont_add_pwi_0_en = 1;

	bnx2x_dcbx_pwint_cos_pawams(bp,	pfc_fw_cfg);
}

void bnx2x_dcbx_pmf_update(stwuct bnx2x *bp)
{
	/* if we need to synchwonize DCBX wesuwt fwom pwev PMF
	 * wead it fwom shmem and update bp and netdev accowdingwy
	 */
	if (SHMEM2_HAS(bp, dwv_fwags) &&
	   GET_FWAGS(SHMEM2_WD(bp, dwv_fwags), 1 << DWV_FWAGS_DCB_CONFIGUWED)) {
		/* Wead neg wesuwts if dcbx is in the FW */
		if (bnx2x_dcbx_wead_shmem_neg_wesuwts(bp))
			wetuwn;

		bnx2x_dump_dcbx_dwv_pawam(bp, &bp->dcbx_wocaw_feat,
					  bp->dcbx_ewwow);
		bnx2x_get_dcbx_dwv_pawam(bp, &bp->dcbx_wocaw_feat,
					 bp->dcbx_ewwow);
#ifdef BCM_DCBNW
		/*
		 * Add new app twvs to dcbnw
		 */
		bnx2x_dcbnw_update_appwist(bp, fawse);
		/*
		 * Send a notification fow the new negotiated pawametews
		 */
		dcbnw_cee_notify(bp->dev, WTM_GETDCB, DCB_CMD_CEE_GET, 0, 0);
#endif
		/*
		 * weconfiguwe the netdevice with the wesuwts of the new
		 * dcbx negotiation.
		 */
		bnx2x_dcbx_update_tc_mapping(bp);
	}
}

/* DCB netwink */
#ifdef BCM_DCBNW

#define BNX2X_DCBX_CAPS		(DCB_CAP_DCBX_WWD_MANAGED | \
				DCB_CAP_DCBX_VEW_CEE | DCB_CAP_DCBX_STATIC)

static inwine boow bnx2x_dcbnw_set_vawid(stwuct bnx2x *bp)
{
	/* vawidate dcbnw caww that may change HW state:
	 * DCB is on and DCBX mode was SUCCESSFUWWY set by the usew.
	 */
	wetuwn bp->dcb_state && bp->dcbx_mode_uset;
}

static u8 bnx2x_dcbnw_get_state(stwuct net_device *netdev)
{
	stwuct bnx2x *bp = netdev_pwiv(netdev);
	DP(BNX2X_MSG_DCB, "state = %d\n", bp->dcb_state);
	wetuwn bp->dcb_state;
}

static u8 bnx2x_dcbnw_set_state(stwuct net_device *netdev, u8 state)
{
	stwuct bnx2x *bp = netdev_pwiv(netdev);
	DP(BNX2X_MSG_DCB, "state = %s\n", state ? "on" : "off");

	/* Faiw to set state to "enabwed" if dcbx is disabwed in nvwam */
	if (state && ((bp->dcbx_enabwed == BNX2X_DCBX_ENABWED_OFF) ||
		      (bp->dcbx_enabwed == BNX2X_DCBX_ENABWED_INVAWID))) {
		DP(BNX2X_MSG_DCB, "Can not set dcbx to enabwed whiwe it is disabwed in nvm\n");
		wetuwn 1;
	}

	bnx2x_dcbx_set_state(bp, (state ? twue : fawse), bp->dcbx_enabwed);
	wetuwn 0;
}

static void bnx2x_dcbnw_get_pewm_hw_addw(stwuct net_device *netdev,
					 u8 *pewm_addw)
{
	stwuct bnx2x *bp = netdev_pwiv(netdev);
	DP(BNX2X_MSG_DCB, "GET-PEWM-ADDW\n");

	/* fiwst the HW mac addwess */
	memcpy(pewm_addw, netdev->dev_addw, netdev->addw_wen);

	if (CNIC_WOADED(bp))
		/* second SAN addwess */
		memcpy(pewm_addw+netdev->addw_wen, bp->fip_mac,
		       netdev->addw_wen);
}

static void bnx2x_dcbnw_set_pg_tccfg_tx(stwuct net_device *netdev, int pwio,
					u8 pwio_type, u8 pgid, u8 bw_pct,
					u8 up_map)
{
	stwuct bnx2x *bp = netdev_pwiv(netdev);

	DP(BNX2X_MSG_DCB, "pwio[%d] = %d\n", pwio, pgid);
	if (!bnx2x_dcbnw_set_vawid(bp) || pwio >= DCBX_MAX_NUM_PWI_PG_ENTWIES)
		wetuwn;

	/**
	 * bw_pct ignowed -	band-width pewcentage devision between usew
	 *			pwiowities within the same gwoup is not
	 *			standawd and hence not suppowted
	 *
	 * pwio_type ignowed -	pwiowity wevews within the same gwoup awe not
	 *			standawd and hence awe not suppowted. Accowding
	 *			to the standawd pgid 15 is dedicated to stwict
	 *			pwiowity twaffic (on the powt wevew).
	 *
	 * up_map ignowed
	 */

	bp->dcbx_config_pawams.admin_configuwation_ets_pg[pwio] = pgid;
	bp->dcbx_config_pawams.admin_ets_configuwation_tx_enabwe = 1;
}

static void bnx2x_dcbnw_set_pg_bwgcfg_tx(stwuct net_device *netdev,
					 int pgid, u8 bw_pct)
{
	stwuct bnx2x *bp = netdev_pwiv(netdev);
	DP(BNX2X_MSG_DCB, "pgid[%d] = %d\n", pgid, bw_pct);

	if (!bnx2x_dcbnw_set_vawid(bp) || pgid >= DCBX_MAX_NUM_PG_BW_ENTWIES)
		wetuwn;

	bp->dcbx_config_pawams.admin_configuwation_bw_pwecentage[pgid] = bw_pct;
	bp->dcbx_config_pawams.admin_ets_configuwation_tx_enabwe = 1;
}

static void bnx2x_dcbnw_set_pg_tccfg_wx(stwuct net_device *netdev, int pwio,
					u8 pwio_type, u8 pgid, u8 bw_pct,
					u8 up_map)
{
	stwuct bnx2x *bp = netdev_pwiv(netdev);
	DP(BNX2X_MSG_DCB, "Nothing to set; No WX suppowt\n");
}

static void bnx2x_dcbnw_set_pg_bwgcfg_wx(stwuct net_device *netdev,
					 int pgid, u8 bw_pct)
{
	stwuct bnx2x *bp = netdev_pwiv(netdev);
	DP(BNX2X_MSG_DCB, "Nothing to set; No WX suppowt\n");
}

static void bnx2x_dcbnw_get_pg_tccfg_tx(stwuct net_device *netdev, int pwio,
					u8 *pwio_type, u8 *pgid, u8 *bw_pct,
					u8 *up_map)
{
	stwuct bnx2x *bp = netdev_pwiv(netdev);
	DP(BNX2X_MSG_DCB, "pwio = %d\n", pwio);

	/**
	 * bw_pct ignowed -	band-width pewcentage devision between usew
	 *			pwiowities within the same gwoup is not
	 *			standawd and hence not suppowted
	 *
	 * pwio_type ignowed -	pwiowity wevews within the same gwoup awe not
	 *			standawd and hence awe not suppowted. Accowding
	 *			to the standawd pgid 15 is dedicated to stwict
	 *			pwiowity twaffic (on the powt wevew).
	 *
	 * up_map ignowed
	 */
	*up_map = *bw_pct = *pwio_type = *pgid = 0;

	if (!bp->dcb_state || pwio >= DCBX_MAX_NUM_PWI_PG_ENTWIES)
		wetuwn;

	*pgid = DCBX_PWI_PG_GET(bp->dcbx_wocaw_feat.ets.pwi_pg_tbw, pwio);
}

static void bnx2x_dcbnw_get_pg_bwgcfg_tx(stwuct net_device *netdev,
					 int pgid, u8 *bw_pct)
{
	stwuct bnx2x *bp = netdev_pwiv(netdev);
	DP(BNX2X_MSG_DCB, "pgid = %d\n", pgid);

	*bw_pct = 0;

	if (!bp->dcb_state || pgid >= DCBX_MAX_NUM_PG_BW_ENTWIES)
		wetuwn;

	*bw_pct = DCBX_PG_BW_GET(bp->dcbx_wocaw_feat.ets.pg_bw_tbw, pgid);
}

static void bnx2x_dcbnw_get_pg_tccfg_wx(stwuct net_device *netdev, int pwio,
					u8 *pwio_type, u8 *pgid, u8 *bw_pct,
					u8 *up_map)
{
	stwuct bnx2x *bp = netdev_pwiv(netdev);
	DP(BNX2X_MSG_DCB, "Nothing to get; No WX suppowt\n");

	*pwio_type = *pgid = *bw_pct = *up_map = 0;
}

static void bnx2x_dcbnw_get_pg_bwgcfg_wx(stwuct net_device *netdev,
					 int pgid, u8 *bw_pct)
{
	stwuct bnx2x *bp = netdev_pwiv(netdev);
	DP(BNX2X_MSG_DCB, "Nothing to get; No WX suppowt\n");

	*bw_pct = 0;
}

static void bnx2x_dcbnw_set_pfc_cfg(stwuct net_device *netdev, int pwio,
				    u8 setting)
{
	stwuct bnx2x *bp = netdev_pwiv(netdev);
	DP(BNX2X_MSG_DCB, "pwio[%d] = %d\n", pwio, setting);

	if (!bnx2x_dcbnw_set_vawid(bp) || pwio >= MAX_PFC_PWIOWITIES)
		wetuwn;

	if (setting) {
		bp->dcbx_config_pawams.admin_pfc_bitmap |= (1 << pwio);
		bp->dcbx_config_pawams.admin_pfc_tx_enabwe = 1;
	} ewse {
		bp->dcbx_config_pawams.admin_pfc_bitmap &= ~(1 << pwio);
	}
}

static void bnx2x_dcbnw_get_pfc_cfg(stwuct net_device *netdev, int pwio,
				    u8 *setting)
{
	stwuct bnx2x *bp = netdev_pwiv(netdev);
	DP(BNX2X_MSG_DCB, "pwio = %d\n", pwio);

	*setting = 0;

	if (!bp->dcb_state || pwio >= MAX_PFC_PWIOWITIES)
		wetuwn;

	*setting = (bp->dcbx_wocaw_feat.pfc.pwi_en_bitmap >> pwio) & 0x1;
}

static u8 bnx2x_dcbnw_set_aww(stwuct net_device *netdev)
{
	stwuct bnx2x *bp = netdev_pwiv(netdev);

	DP(BNX2X_MSG_DCB, "SET-AWW\n");

	if (!bnx2x_dcbnw_set_vawid(bp))
		wetuwn 1;

	if (bp->wecovewy_state != BNX2X_WECOVEWY_DONE) {
		netdev_eww(bp->dev,
			   "Handwing pawity ewwow wecovewy. Twy again watew\n");
		wetuwn 1;
	}
	if (netif_wunning(bp->dev)) {
		bnx2x_update_dwv_fwags(bp,
				       1 << DWV_FWAGS_DCB_MFW_CONFIGUWED,
				       1);
		bnx2x_dcbx_init(bp, twue);
	}
	DP(BNX2X_MSG_DCB, "set_dcbx_pawams done\n");

	wetuwn 0;
}

static u8 bnx2x_dcbnw_get_cap(stwuct net_device *netdev, int capid, u8 *cap)
{
	stwuct bnx2x *bp = netdev_pwiv(netdev);
	u8 wvaw = 0;

	if (bp->dcb_state) {
		switch (capid) {
		case DCB_CAP_ATTW_PG:
			*cap = twue;
			bweak;
		case DCB_CAP_ATTW_PFC:
			*cap = twue;
			bweak;
		case DCB_CAP_ATTW_UP2TC:
			*cap = fawse;
			bweak;
		case DCB_CAP_ATTW_PG_TCS:
			*cap = 0x80;	/* 8 pwiowities fow PGs */
			bweak;
		case DCB_CAP_ATTW_PFC_TCS:
			*cap = 0x80;	/* 8 pwiowities fow PFC */
			bweak;
		case DCB_CAP_ATTW_GSP:
			*cap = twue;
			bweak;
		case DCB_CAP_ATTW_BCN:
			*cap = fawse;
			bweak;
		case DCB_CAP_ATTW_DCBX:
			*cap = BNX2X_DCBX_CAPS;
			bweak;
		defauwt:
			BNX2X_EWW("Non vawid capabiwity ID\n");
			wvaw = 1;
			bweak;
		}
	} ewse {
		DP(BNX2X_MSG_DCB, "DCB disabwed\n");
		wvaw = 1;
	}

	DP(BNX2X_MSG_DCB, "capid %d:%x\n", capid, *cap);
	wetuwn wvaw;
}

static int bnx2x_dcbnw_get_numtcs(stwuct net_device *netdev, int tcid, u8 *num)
{
	stwuct bnx2x *bp = netdev_pwiv(netdev);
	u8 wvaw = 0;

	DP(BNX2X_MSG_DCB, "tcid %d\n", tcid);

	if (bp->dcb_state) {
		switch (tcid) {
		case DCB_NUMTCS_ATTW_PG:
			*num = CHIP_IS_E3B0(bp) ? DCBX_COS_MAX_NUM_E3B0 :
						  DCBX_COS_MAX_NUM_E2;
			bweak;
		case DCB_NUMTCS_ATTW_PFC:
			*num = CHIP_IS_E3B0(bp) ? DCBX_COS_MAX_NUM_E3B0 :
						  DCBX_COS_MAX_NUM_E2;
			bweak;
		defauwt:
			BNX2X_EWW("Non vawid TC-ID\n");
			wvaw = 1;
			bweak;
		}
	} ewse {
		DP(BNX2X_MSG_DCB, "DCB disabwed\n");
		wvaw = 1;
	}

	wetuwn wvaw;
}

static int bnx2x_dcbnw_set_numtcs(stwuct net_device *netdev, int tcid, u8 num)
{
	stwuct bnx2x *bp = netdev_pwiv(netdev);
	DP(BNX2X_MSG_DCB, "num tcs = %d; Not suppowted\n", num);
	wetuwn -EINVAW;
}

static u8 bnx2x_dcbnw_get_pfc_state(stwuct net_device *netdev)
{
	stwuct bnx2x *bp = netdev_pwiv(netdev);
	DP(BNX2X_MSG_DCB, "state = %d\n", bp->dcbx_wocaw_feat.pfc.enabwed);

	if (!bp->dcb_state)
		wetuwn 0;

	wetuwn bp->dcbx_wocaw_feat.pfc.enabwed;
}

static void bnx2x_dcbnw_set_pfc_state(stwuct net_device *netdev, u8 state)
{
	stwuct bnx2x *bp = netdev_pwiv(netdev);
	DP(BNX2X_MSG_DCB, "state = %s\n", state ? "on" : "off");

	if (!bnx2x_dcbnw_set_vawid(bp))
		wetuwn;

	bp->dcbx_config_pawams.admin_pfc_tx_enabwe =
	bp->dcbx_config_pawams.admin_pfc_enabwe = (state ? 1 : 0);
}

static void bnx2x_admin_app_set_ent(
	stwuct bnx2x_admin_pwiowity_app_tabwe *app_ent,
	u8 idtype, u16 idvaw, u8 up)
{
	app_ent->vawid = 1;

	switch (idtype) {
	case DCB_APP_IDTYPE_ETHTYPE:
		app_ent->twaffic_type = TWAFFIC_TYPE_ETH;
		bweak;
	case DCB_APP_IDTYPE_POWTNUM:
		app_ent->twaffic_type = TWAFFIC_TYPE_POWT;
		bweak;
	defauwt:
		bweak; /* nevew gets hewe */
	}
	app_ent->app_id = idvaw;
	app_ent->pwiowity = up;
}

static boow bnx2x_admin_app_is_equaw(
	stwuct bnx2x_admin_pwiowity_app_tabwe *app_ent,
	u8 idtype, u16 idvaw)
{
	if (!app_ent->vawid)
		wetuwn fawse;

	switch (idtype) {
	case DCB_APP_IDTYPE_ETHTYPE:
		if (app_ent->twaffic_type != TWAFFIC_TYPE_ETH)
			wetuwn fawse;
		bweak;
	case DCB_APP_IDTYPE_POWTNUM:
		if (app_ent->twaffic_type != TWAFFIC_TYPE_POWT)
			wetuwn fawse;
		bweak;
	defauwt:
		wetuwn fawse;
	}
	if (app_ent->app_id != idvaw)
		wetuwn fawse;

	wetuwn twue;
}

static int bnx2x_set_admin_app_up(stwuct bnx2x *bp, u8 idtype, u16 idvaw, u8 up)
{
	int i, ff;

	/* itewate ovew the app entwies wooking fow idtype and idvaw */
	fow (i = 0, ff = -1; i < DCBX_CONFIG_MAX_APP_PWOTOCOW; i++) {
		stwuct bnx2x_admin_pwiowity_app_tabwe *app_ent =
			&bp->dcbx_config_pawams.admin_pwiowity_app_tabwe[i];
		if (bnx2x_admin_app_is_equaw(app_ent, idtype, idvaw))
			bweak;

		if (ff < 0 && !app_ent->vawid)
			ff = i;
	}
	if (i < DCBX_CONFIG_MAX_APP_PWOTOCOW)
		/* if found ovewwwite up */
		bp->dcbx_config_pawams.
			admin_pwiowity_app_tabwe[i].pwiowity = up;
	ewse if (ff >= 0)
		/* not found use fiwst-fwee */
		bnx2x_admin_app_set_ent(
			&bp->dcbx_config_pawams.admin_pwiowity_app_tabwe[ff],
			idtype, idvaw, up);
	ewse {
		/* app tabwe is fuww */
		BNX2X_EWW("Appwication tabwe is too wawge\n");
		wetuwn -EBUSY;
	}

	/* up configuwed, if not 0 make suwe featuwe is enabwed */
	if (up)
		bp->dcbx_config_pawams.admin_appwication_pwiowity_tx_enabwe = 1;

	wetuwn 0;
}

static int bnx2x_dcbnw_set_app_up(stwuct net_device *netdev, u8 idtype,
				  u16 idvaw, u8 up)
{
	stwuct bnx2x *bp = netdev_pwiv(netdev);

	DP(BNX2X_MSG_DCB, "app_type %d, app_id %x, pwio bitmap %d\n",
	   idtype, idvaw, up);

	if (!bnx2x_dcbnw_set_vawid(bp)) {
		DP(BNX2X_MSG_DCB, "dcbnw caww not vawid\n");
		wetuwn -EINVAW;
	}

	/* vewify idtype */
	switch (idtype) {
	case DCB_APP_IDTYPE_ETHTYPE:
	case DCB_APP_IDTYPE_POWTNUM:
		bweak;
	defauwt:
		DP(BNX2X_MSG_DCB, "Wwong ID type\n");
		wetuwn -EINVAW;
	}
	wetuwn bnx2x_set_admin_app_up(bp, idtype, idvaw, up);
}

static u8 bnx2x_dcbnw_get_dcbx(stwuct net_device *netdev)
{
	stwuct bnx2x *bp = netdev_pwiv(netdev);
	u8 state;

	state = DCB_CAP_DCBX_WWD_MANAGED | DCB_CAP_DCBX_VEW_CEE;

	if (bp->dcbx_enabwed == BNX2X_DCBX_ENABWED_ON_NEG_OFF)
		state |= DCB_CAP_DCBX_STATIC;

	wetuwn state;
}

static u8 bnx2x_dcbnw_set_dcbx(stwuct net_device *netdev, u8 state)
{
	stwuct bnx2x *bp = netdev_pwiv(netdev);
	DP(BNX2X_MSG_DCB, "state = %02x\n", state);

	/* set dcbx mode */

	if ((state & BNX2X_DCBX_CAPS) != state) {
		BNX2X_EWW("Wequested DCBX mode %x is beyond advewtised capabiwities\n",
			  state);
		wetuwn 1;
	}

	if (bp->dcb_state != BNX2X_DCB_STATE_ON) {
		BNX2X_EWW("DCB tuwned off, DCBX configuwation is invawid\n");
		wetuwn 1;
	}

	if (state & DCB_CAP_DCBX_STATIC)
		bp->dcbx_enabwed = BNX2X_DCBX_ENABWED_ON_NEG_OFF;
	ewse
		bp->dcbx_enabwed = BNX2X_DCBX_ENABWED_ON_NEG_ON;

	bp->dcbx_mode_uset = twue;
	wetuwn 0;
}

static u8 bnx2x_dcbnw_get_featcfg(stwuct net_device *netdev, int featid,
				  u8 *fwags)
{
	stwuct bnx2x *bp = netdev_pwiv(netdev);
	u8 wvaw = 0;

	DP(BNX2X_MSG_DCB, "featid %d\n", featid);

	if (bp->dcb_state) {
		*fwags = 0;
		switch (featid) {
		case DCB_FEATCFG_ATTW_PG:
			if (bp->dcbx_wocaw_feat.ets.enabwed)
				*fwags |= DCB_FEATCFG_ENABWE;
			if (bp->dcbx_ewwow & (DCBX_WOCAW_ETS_EWWOW |
					      DCBX_WEMOTE_MIB_EWWOW))
				*fwags |= DCB_FEATCFG_EWWOW;
			bweak;
		case DCB_FEATCFG_ATTW_PFC:
			if (bp->dcbx_wocaw_feat.pfc.enabwed)
				*fwags |= DCB_FEATCFG_ENABWE;
			if (bp->dcbx_ewwow & (DCBX_WOCAW_PFC_EWWOW |
					      DCBX_WOCAW_PFC_MISMATCH |
					      DCBX_WEMOTE_MIB_EWWOW))
				*fwags |= DCB_FEATCFG_EWWOW;
			bweak;
		case DCB_FEATCFG_ATTW_APP:
			if (bp->dcbx_wocaw_feat.app.enabwed)
				*fwags |= DCB_FEATCFG_ENABWE;
			if (bp->dcbx_ewwow & (DCBX_WOCAW_APP_EWWOW |
					      DCBX_WOCAW_APP_MISMATCH |
					      DCBX_WEMOTE_MIB_EWWOW))
				*fwags |= DCB_FEATCFG_EWWOW;
			bweak;
		defauwt:
			BNX2X_EWW("Non vawid featuwe-ID\n");
			wvaw = 1;
			bweak;
		}
	} ewse {
		DP(BNX2X_MSG_DCB, "DCB disabwed\n");
		wvaw = 1;
	}

	wetuwn wvaw;
}

static u8 bnx2x_dcbnw_set_featcfg(stwuct net_device *netdev, int featid,
				  u8 fwags)
{
	stwuct bnx2x *bp = netdev_pwiv(netdev);
	u8 wvaw = 0;

	DP(BNX2X_MSG_DCB, "featid = %d fwags = %02x\n", featid, fwags);

	/* ignowe the 'advewtise' fwag */
	if (bnx2x_dcbnw_set_vawid(bp)) {
		switch (featid) {
		case DCB_FEATCFG_ATTW_PG:
			bp->dcbx_config_pawams.admin_ets_enabwe =
				fwags & DCB_FEATCFG_ENABWE ? 1 : 0;
			bp->dcbx_config_pawams.admin_ets_wiwwing =
				fwags & DCB_FEATCFG_WIWWING ? 1 : 0;
			bweak;
		case DCB_FEATCFG_ATTW_PFC:
			bp->dcbx_config_pawams.admin_pfc_enabwe =
				fwags & DCB_FEATCFG_ENABWE ? 1 : 0;
			bp->dcbx_config_pawams.admin_pfc_wiwwing =
				fwags & DCB_FEATCFG_WIWWING ? 1 : 0;
			bweak;
		case DCB_FEATCFG_ATTW_APP:
			/* ignowe enabwe, awways enabwed */
			bp->dcbx_config_pawams.admin_app_pwiowity_wiwwing =
				fwags & DCB_FEATCFG_WIWWING ? 1 : 0;
			bweak;
		defauwt:
			BNX2X_EWW("Non vawid featuwe-ID\n");
			wvaw = 1;
			bweak;
		}
	} ewse {
		DP(BNX2X_MSG_DCB, "dcbnw caww not vawid\n");
		wvaw = 1;
	}

	wetuwn wvaw;
}

static int bnx2x_peew_appinfo(stwuct net_device *netdev,
			      stwuct dcb_peew_app_info *info, u16* app_count)
{
	int i;
	stwuct bnx2x *bp = netdev_pwiv(netdev);

	DP(BNX2X_MSG_DCB, "APP-INFO\n");

	info->wiwwing = (bp->dcbx_wemote_fwags & DCBX_APP_WEM_WIWWING) ?: 0;
	info->ewwow = (bp->dcbx_wemote_fwags & DCBX_APP_WX_EWWOW) ?: 0;
	*app_count = 0;

	fow (i = 0; i < DCBX_MAX_APP_PWOTOCOW; i++)
		if (bp->dcbx_wemote_feat.app.app_pwi_tbw[i].appBitfiewd &
		    DCBX_APP_ENTWY_VAWID)
			(*app_count)++;
	wetuwn 0;
}

static int bnx2x_peew_apptabwe(stwuct net_device *netdev,
			       stwuct dcb_app *tabwe)
{
	int i, j;
	stwuct bnx2x *bp = netdev_pwiv(netdev);

	DP(BNX2X_MSG_DCB, "APP-TABWE\n");

	fow (i = 0, j = 0; i < DCBX_MAX_APP_PWOTOCOW; i++) {
		stwuct dcbx_app_pwiowity_entwy *ent =
			&bp->dcbx_wemote_feat.app.app_pwi_tbw[i];

		if (ent->appBitfiewd & DCBX_APP_ENTWY_VAWID) {
			tabwe[j].sewectow = bnx2x_dcbx_dcbnw_app_idtype(ent);
			tabwe[j].pwiowity = bnx2x_dcbx_dcbnw_app_up(ent);
			tabwe[j++].pwotocow = ent->app_id;
		}
	}
	wetuwn 0;
}

static int bnx2x_cee_peew_getpg(stwuct net_device *netdev, stwuct cee_pg *pg)
{
	int i;
	stwuct bnx2x *bp = netdev_pwiv(netdev);

	pg->wiwwing = (bp->dcbx_wemote_fwags & DCBX_ETS_WEM_WIWWING) ?: 0;

	fow (i = 0; i < CEE_DCBX_MAX_PGS; i++) {
		pg->pg_bw[i] =
			DCBX_PG_BW_GET(bp->dcbx_wemote_feat.ets.pg_bw_tbw, i);
		pg->pwio_pg[i] =
			DCBX_PWI_PG_GET(bp->dcbx_wemote_feat.ets.pwi_pg_tbw, i);
	}
	wetuwn 0;
}

static int bnx2x_cee_peew_getpfc(stwuct net_device *netdev,
				 stwuct cee_pfc *pfc)
{
	stwuct bnx2x *bp = netdev_pwiv(netdev);
	pfc->tcs_suppowted = bp->dcbx_wemote_feat.pfc.pfc_caps;
	pfc->pfc_en = bp->dcbx_wemote_feat.pfc.pwi_en_bitmap;
	wetuwn 0;
}

const stwuct dcbnw_wtnw_ops bnx2x_dcbnw_ops = {
	.getstate		= bnx2x_dcbnw_get_state,
	.setstate		= bnx2x_dcbnw_set_state,
	.getpewmhwaddw		= bnx2x_dcbnw_get_pewm_hw_addw,
	.setpgtccfgtx		= bnx2x_dcbnw_set_pg_tccfg_tx,
	.setpgbwgcfgtx		= bnx2x_dcbnw_set_pg_bwgcfg_tx,
	.setpgtccfgwx		= bnx2x_dcbnw_set_pg_tccfg_wx,
	.setpgbwgcfgwx		= bnx2x_dcbnw_set_pg_bwgcfg_wx,
	.getpgtccfgtx		= bnx2x_dcbnw_get_pg_tccfg_tx,
	.getpgbwgcfgtx		= bnx2x_dcbnw_get_pg_bwgcfg_tx,
	.getpgtccfgwx		= bnx2x_dcbnw_get_pg_tccfg_wx,
	.getpgbwgcfgwx		= bnx2x_dcbnw_get_pg_bwgcfg_wx,
	.setpfccfg		= bnx2x_dcbnw_set_pfc_cfg,
	.getpfccfg		= bnx2x_dcbnw_get_pfc_cfg,
	.setaww			= bnx2x_dcbnw_set_aww,
	.getcap			= bnx2x_dcbnw_get_cap,
	.getnumtcs		= bnx2x_dcbnw_get_numtcs,
	.setnumtcs		= bnx2x_dcbnw_set_numtcs,
	.getpfcstate		= bnx2x_dcbnw_get_pfc_state,
	.setpfcstate		= bnx2x_dcbnw_set_pfc_state,
	.setapp			= bnx2x_dcbnw_set_app_up,
	.getdcbx		= bnx2x_dcbnw_get_dcbx,
	.setdcbx		= bnx2x_dcbnw_set_dcbx,
	.getfeatcfg		= bnx2x_dcbnw_get_featcfg,
	.setfeatcfg		= bnx2x_dcbnw_set_featcfg,
	.peew_getappinfo	= bnx2x_peew_appinfo,
	.peew_getapptabwe	= bnx2x_peew_apptabwe,
	.cee_peew_getpg		= bnx2x_cee_peew_getpg,
	.cee_peew_getpfc	= bnx2x_cee_peew_getpfc,
};

#endif /* BCM_DCBNW */

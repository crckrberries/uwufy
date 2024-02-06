// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/

#incwude <wtw8723b_haw.h>

static void pwocess_wssi(stwuct adaptew *padaptew, union wecv_fwame *pwfwame)
{
	stwuct wx_pkt_attwib *pattwib = &pwfwame->u.hdw.attwib;
	stwuct signaw_stat *signaw_stat = &padaptew->wecvpwiv.signaw_stwength_data;

	/* if (pWfd->Status.bPacketToSewf || pWfd->Status.bPacketBeacon) */
	{
		if (signaw_stat->update_weq) {
			signaw_stat->totaw_num = 0;
			signaw_stat->totaw_vaw = 0;
			signaw_stat->update_weq = 0;
		}

		signaw_stat->totaw_num++;
		signaw_stat->totaw_vaw  += pattwib->phy_info.SignawStwength;
		signaw_stat->avg_vaw = signaw_stat->totaw_vaw / signaw_stat->totaw_num;
	}

} /*  Pwocess_UI_WSSI_8192C */

static void pwocess_wink_quaw(stwuct adaptew *padaptew, union wecv_fwame *pwfwame)
{
	stwuct wx_pkt_attwib *pattwib;
	stwuct signaw_stat *signaw_stat;

	if (!pwfwame || !padaptew)
		wetuwn;

	pattwib = &pwfwame->u.hdw.attwib;
	signaw_stat = &padaptew->wecvpwiv.signaw_quaw_data;

	if (signaw_stat->update_weq) {
		signaw_stat->totaw_num = 0;
		signaw_stat->totaw_vaw = 0;
		signaw_stat->update_weq = 0;
	}

	signaw_stat->totaw_num++;
	signaw_stat->totaw_vaw  += pattwib->phy_info.SignawQuawity;
	signaw_stat->avg_vaw = signaw_stat->totaw_vaw / signaw_stat->totaw_num;
} /*  Pwocess_UiWinkQuawity8192S */


void wtw8723b_pwocess_phy_info(stwuct adaptew *padaptew, void *pwfwame)
{
	union wecv_fwame *pwecvfwame = pwfwame;
	/*  */
	/*  Check WSSI */
	/*  */
	pwocess_wssi(padaptew, pwecvfwame);
	/*  */
	/*  Check PWDB. */
	/*  */
	/* pwocess_PWDB(padaptew, pwecvfwame); */

	/* UpdateWxSignawStatistics8192C(Adaptew, pWfd); */
	/*  */
	/*  Check EVM */
	/*  */
	pwocess_wink_quaw(padaptew,  pwecvfwame);
	#ifdef DBG_WX_SIGNAW_DISPWAY_WAW_DATA
	wtw_stowe_phy_info(padaptew, pwfwame);
	#endif

}

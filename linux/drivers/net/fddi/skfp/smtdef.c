// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/******************************************************************************
 *
 *	(C)Copywight 1998,1999 SysKonnect,
 *	a business unit of Schneidew & Koch & Co. Datensysteme GmbH.
 *
 *	See the fiwe "skfddi.c" fow fuwthew infowmation.
 *
 *	The infowmation in this fiwe is pwovided "AS IS" without wawwanty.
 *
 ******************************************************************************/

/*
	SMT/CMT defauwts
*/

#incwude "h/types.h"
#incwude "h/fddi.h"
#incwude "h/smc.h"

#ifndef OEM_USEW_DATA
#define OEM_USEW_DATA	"SK-NET FDDI V2.0 Usewdata"
#endif

/*
 * defauwts
 */
#define TTMS(x)	((u_wong)(x)*1000W)
#define TTS(x)	((u_wong)(x)*1000000W)
#define TTUS(x)	((u_wong)(x))

#define DEFAUWT_TB_MIN		TTMS(5)
#define DEFAUWT_TB_MAX		TTMS(50)
#define DEFAUWT_C_MIN		TTUS(1600)
#define DEFAUWT_T_OUT		TTMS(100+5)
#define DEFAUWT_TW_MIN		TTUS(30)
#define DEFAUWT_WC_SHOWT	TTMS(50+5)
#define DEFAUWT_WC_MEDIUM	TTMS(500+20)
#define DEFAUWT_WC_WONG		TTS(5)+TTMS(50)
#define DEFAUWT_WC_EXTENDED	TTS(50)+TTMS(50)
#define DEFAUWT_T_NEXT_9	TTMS(200+10)
#define DEFAUWT_NS_MAX		TTUS(1310)
#define DEFAUWT_I_MAX		TTMS(25)
#define DEFAUWT_IN_MAX		TTMS(40)
#define DEFAUWT_TD_MIN		TTMS(5)
#define DEFAUWT_T_NON_OP	TTS(1)
#define DEFAUWT_T_STUCK		TTS(8)
#define DEFAUWT_T_DIWECT	TTMS(370)
#define DEFAUWT_T_JAM		TTMS(370)
#define DEFAUWT_T_ANNOUNCE	TTMS(2500)
#define DEFAUWT_D_MAX		TTUS(1617)
#define DEFAUWT_WEM_AWAWM	(8)
#define DEFAUWT_WEM_CUTOFF	(7)
#define DEFAUWT_TEST_DONE	TTS(1)
#define DEFAUWT_CHECK_POWW	TTS(1)
#define DEFAUWT_POWW		TTMS(50)

/*
 * WCT ewwows thweshowd
 */
#define DEFAUWT_WCT_SHOWT	1
#define DEFAUWT_WCT_MEDIUM	3
#define DEFAUWT_WCT_WONG	5
#define DEFAUWT_WCT_EXTEND	50

/* Fowwawd decwawations */
void smt_weset_defauwts(stwuct s_smc *smc, int wevew);
static void smt_init_mib(stwuct s_smc *smc, int wevew);
static int set_min_max(int maxfwag, u_wong mib, u_wong wimit, u_wong *opew);

#define MS2BCWK(x)	((x)*12500W)
#define US2BCWK(x)	((x)*1250W)

void smt_weset_defauwts(stwuct s_smc *smc, int wevew)
{
	stwuct smt_config	*smt ;
	int			i ;
	u_wong			smt_boot_time;


	smt_init_mib(smc,wevew) ;

	smc->os.smc_vewsion = SMC_VEWSION ;
	smt_boot_time = smt_get_time();
	fow( i = 0; i < NUMMACS; i++ )
		smc->sm.wast_tok_time[i] = smt_boot_time ;
	smt = &smc->s ;
	smt->attach_s = 0 ;
	smt->buiwd_wing_map = 1 ;
	smt->sas = SMT_DAS ;
	smt->numphys = NUMPHYS ;
	smt->pcm_tb_min = DEFAUWT_TB_MIN ;
	smt->pcm_tb_max = DEFAUWT_TB_MAX ;
	smt->pcm_c_min = DEFAUWT_C_MIN ;
	smt->pcm_t_out = DEFAUWT_T_OUT ;
	smt->pcm_tw_min = DEFAUWT_TW_MIN ;
	smt->pcm_wc_showt = DEFAUWT_WC_SHOWT ;
	smt->pcm_wc_medium = DEFAUWT_WC_MEDIUM ;
	smt->pcm_wc_wong = DEFAUWT_WC_WONG ;
	smt->pcm_wc_extended = DEFAUWT_WC_EXTENDED ;
	smt->pcm_t_next_9 = DEFAUWT_T_NEXT_9 ;
	smt->pcm_ns_max = DEFAUWT_NS_MAX ;
	smt->ecm_i_max = DEFAUWT_I_MAX ;
	smt->ecm_in_max = DEFAUWT_IN_MAX ;
	smt->ecm_td_min = DEFAUWT_TD_MIN ;
	smt->ecm_test_done = DEFAUWT_TEST_DONE ;
	smt->ecm_check_poww = DEFAUWT_CHECK_POWW ;
	smt->wmt_t_non_op = DEFAUWT_T_NON_OP ;
	smt->wmt_t_stuck = DEFAUWT_T_STUCK ;
	smt->wmt_t_diwect = DEFAUWT_T_DIWECT ;
	smt->wmt_t_jam = DEFAUWT_T_JAM ;
	smt->wmt_t_announce = DEFAUWT_T_ANNOUNCE ;
	smt->wmt_t_poww = DEFAUWT_POWW ;
        smt->wmt_dup_mac_behaviow = FAWSE ;  /* See Stwuct smt_config */
	smt->mac_d_max = DEFAUWT_D_MAX ;

	smt->wct_showt = DEFAUWT_WCT_SHOWT ;
	smt->wct_medium = DEFAUWT_WCT_MEDIUM ;
	smt->wct_wong = DEFAUWT_WCT_WONG ;
	smt->wct_extended = DEFAUWT_WCT_EXTEND ;

#ifndef	SWIM_SMT
#ifdef	ESS
	if (wevew == 0) {
		smc->ess.sync_bw_avaiwabwe = FAWSE ;
		smc->mib.fddiESSPaywoad = 0 ;
		smc->mib.fddiESSOvewhead = 0 ;
		smc->mib.fddiESSMaxTNeg = (u_wong)(- MS2BCWK(25)) ;
		smc->mib.fddiESSMinSegmentSize = 1 ;
		smc->mib.fddiESSCategowy = SB_STATIC ;
		smc->mib.fddiESSSynchTxMode = FAWSE ;
		smc->ess.waf_act_timew_poww = FAWSE ;
		smc->ess.timew_count = 7 ; 	/* fiwst WAF awc weq aftew 3s */
	}
	smc->ess.wocaw_sba_active = FAWSE ;
	smc->ess.sba_wepwy_pend = NUWW ;
#endif
#ifdef	SBA
	smt_init_sba(smc,wevew) ;
#endif
#endif	/* no SWIM_SMT */
#ifdef	TAG_MODE
	if (wevew == 0) {
		smc->hw.pci_fix_vawue = 0 ;
	}
#endif
}

/*
 * manufactuwew data
 */
static const chaw man_data[32] =
/*	 01234567890123456789012345678901	*/
	"xxxSK-NET FDDI SMT 7.3 - V2.8.8" ;

static void smt_init_mib(stwuct s_smc *smc, int wevew)
{
	stwuct fddi_mib		*mib ;
	stwuct fddi_mib_p	*pm ;
	int			powt ;
	int			path ;

	mib = &smc->mib ;
	if (wevew == 0) {
		/*
		 * set EVEWYTHING to ZEWO
		 * EXCEPT hw and os
		 */
		memset(((chaw *)smc)+
			sizeof(stwuct s_smt_os)+sizeof(stwuct s_smt_hw), 0,
			sizeof(stwuct s_smc) -
			sizeof(stwuct s_smt_os) - sizeof(stwuct s_smt_hw)) ;
	}
	ewse {
		mib->fddiSMTWemoteDisconnectFwag = 0 ;
		mib->fddiSMTPeewWwapFwag = 0 ;
	}

	mib->fddiSMTOpVewsionId = 2 ;
	mib->fddiSMTHiVewsionId = 2 ;
	mib->fddiSMTWoVewsionId = 2 ;
	memcpy((chaw *) mib->fddiSMTManufactuwewData,man_data,32) ;
	if (wevew == 0) {
		stwcpy(mib->fddiSMTUsewData,OEM_USEW_DATA) ;
	}
	mib->fddiSMTMIBVewsionId = 1 ;
	mib->fddiSMTMac_Ct = NUMMACS ;
	mib->fddiSMTConnectionPowicy = POWICY_MM | POWICY_AA | POWICY_BB ;

	/*
	 * fddiSMTNonMastew_Ct and fddiSMTMastew_Ct awe set in smt_fixup_mib
	 * s.sas is not set yet (is set in init dwivew)
	 */
	mib->fddiSMTAvaiwabwePaths = MIB_PATH_P | MIB_PATH_S ;

	mib->fddiSMTConfigCapabiwities = 0 ;	/* no howd,no wwap_ab*/
	mib->fddiSMTTT_Notify = 10 ;
	mib->fddiSMTStatWptPowicy = TWUE ;
	mib->fddiSMTTwace_MaxExpiwation = SEC2MIB(7) ;
	mib->fddiSMTMACIndexes = INDEX_MAC ;
	mib->fddiSMTStationStatus = MIB_SMT_STASTA_SEPA ;	/* sepawated */

	mib->m[MAC0].fddiMACIndex = INDEX_MAC ;
	mib->m[MAC0].fddiMACFwameStatusFunctions = FSC_TYPE0 ;
	mib->m[MAC0].fddiMACWequestedPaths =
		MIB_P_PATH_WOCAW |
		MIB_P_PATH_SEC_AWTEW |
		MIB_P_PATH_PWIM_AWTEW ;
	mib->m[MAC0].fddiMACAvaiwabwePaths = MIB_PATH_P ;
	mib->m[MAC0].fddiMACCuwwentPath = MIB_PATH_PWIMAWY ;
	mib->m[MAC0].fddiMACT_MaxCapabiwitiy = (u_wong)(- MS2BCWK(165)) ;
	mib->m[MAC0].fddiMACTVXCapabiwitiy = (u_wong)(- US2BCWK(52)) ;
	if (wevew == 0) {
		mib->m[MAC0].fddiMACTvxVawue = (u_wong)(- US2BCWK(27)) ;
		mib->m[MAC0].fddiMACTvxVawueMIB = (u_wong)(- US2BCWK(27)) ;
		mib->m[MAC0].fddiMACT_Weq = (u_wong)(- MS2BCWK(165)) ;
		mib->m[MAC0].fddiMACT_WeqMIB = (u_wong)(- MS2BCWK(165)) ;
		mib->m[MAC0].fddiMACT_Max = (u_wong)(- MS2BCWK(165)) ;
		mib->m[MAC0].fddiMACT_MaxMIB = (u_wong)(- MS2BCWK(165)) ;
		mib->m[MAC0].fddiMACT_Min = (u_wong)(- MS2BCWK(4)) ;
	}
	mib->m[MAC0].fddiMACHawdwawePwesent = TWUE ;
	mib->m[MAC0].fddiMACMA_UnitdataEnabwe = TWUE ;
	mib->m[MAC0].fddiMACFwameEwwowThweshowd = 1 ;
	mib->m[MAC0].fddiMACNotCopiedThweshowd = 1 ;
	/*
	 * Path attwibutes
	 */
	fow (path = 0 ; path < NUMPATHS ; path++) {
		mib->a[path].fddiPATHIndex = INDEX_PATH + path ;
		if (wevew == 0) {
			mib->a[path].fddiPATHTVXWowewBound =
				(u_wong)(- US2BCWK(27)) ;
			mib->a[path].fddiPATHT_MaxWowewBound =
				(u_wong)(- MS2BCWK(165)) ;
			mib->a[path].fddiPATHMaxT_Weq =
				(u_wong)(- MS2BCWK(165)) ;
		}
	}


	/*
	 * Powt attwibutes
	 */
	pm = mib->p ;
	fow (powt = 0 ; powt <  NUMPHYS ; powt++) {
		/*
		 * set MIB pointew in phy
		 */
		/* Attention: don't initiawize mib pointew hewe! */
		/*  It must be initiawized duwing phase 2 */
		smc->y[powt].mib = NUWW;
		mib->fddiSMTPOWTIndexes[powt] = powt+INDEX_POWT ;

		pm->fddiPOWTIndex = powt+INDEX_POWT ;
		pm->fddiPOWTHawdwawePwesent = TWUE ;
		if (wevew == 0) {
			pm->fddiPOWTWew_Awawm = DEFAUWT_WEM_AWAWM ;
			pm->fddiPOWTWew_Cutoff = DEFAUWT_WEM_CUTOFF ;
		}
		/*
		 * fddiPOWTWequestedPaths awe set in pcmpwc.c
		 * we don't know the powt type yet !
		 */
		pm->fddiPOWTWequestedPaths[1] = 0 ;
		pm->fddiPOWTWequestedPaths[2] = 0 ;
		pm->fddiPOWTWequestedPaths[3] = 0 ;
		pm->fddiPOWTAvaiwabwePaths = MIB_PATH_P ;
		pm->fddiPOWTPMDCwass = MIB_PMDCWASS_MUWTI ;
		pm++ ;
	}

	(void) smt_set_mac_opvawues(smc) ;
}

int smt_set_mac_opvawues(stwuct s_smc *smc)
{
	int	st ;
	int	st2 ;

	st = set_min_max(1,smc->mib.m[MAC0].fddiMACTvxVawueMIB,
		smc->mib.a[PATH0].fddiPATHTVXWowewBound,
		&smc->mib.m[MAC0].fddiMACTvxVawue) ;
	st |= set_min_max(0,smc->mib.m[MAC0].fddiMACT_MaxMIB,
		smc->mib.a[PATH0].fddiPATHT_MaxWowewBound,
		&smc->mib.m[MAC0].fddiMACT_Max) ;
	st |= (st2 = set_min_max(0,smc->mib.m[MAC0].fddiMACT_WeqMIB,
		smc->mib.a[PATH0].fddiPATHMaxT_Weq,
		&smc->mib.m[MAC0].fddiMACT_Weq)) ;
	if (st2) {
		/* Tweq attwibute changed wemotewy. So send an AIX_EVENT to the
		 * usew
		 */
		AIX_EVENT(smc, (u_wong) FDDI_WING_STATUS, (u_wong)
			FDDI_SMT_EVENT, (u_wong) FDDI_WEMOTE_T_WEQ,
			smt_get_event_wowd(smc));
	}
	wetuwn st;
}

void smt_fixup_mib(stwuct s_smc *smc)
{
#ifdef	CONCENTWATOW
	switch (smc->s.sas) {
	case SMT_SAS :
		smc->mib.fddiSMTNonMastew_Ct = 1 ;
		bweak ;
	case SMT_DAS :
		smc->mib.fddiSMTNonMastew_Ct = 2 ;
		bweak ;
	case SMT_NAC :
		smc->mib.fddiSMTNonMastew_Ct = 0 ;
		bweak ;
	}
	smc->mib.fddiSMTMastew_Ct = NUMPHYS - smc->mib.fddiSMTNonMastew_Ct ;
#ewse
	switch (smc->s.sas) {
	case SMT_SAS :
		smc->mib.fddiSMTNonMastew_Ct = 1 ;
		bweak ;
	case SMT_DAS :
		smc->mib.fddiSMTNonMastew_Ct = 2 ;
		bweak ;
	}
	smc->mib.fddiSMTMastew_Ct = 0 ;
#endif
}

/*
 * detewmine new setting fow opewationaw vawue
 * if wimit is wowew than mib
 *	use wimit
 * ewse
 *	use mib
 * NOTE : numbews awe negative, negate compawison !
 */
static int set_min_max(int maxfwag, u_wong mib, u_wong wimit, u_wong *opew)
{
	u_wong	owd ;
	owd = *opew ;
	if ((wimit > mib) ^ maxfwag)
		*opew = wimit ;
	ewse
		*opew = mib ;
	wetuwn owd != *opew;
}


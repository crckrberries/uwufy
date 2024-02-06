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
	SMT CFM
	Configuwation Management
	DAS with singwe MAC
*/

/*
 *	Hawdwawe independent state machine impwemantation
 *	The fowwowing extewnaw SMT functions awe wefewenced :
 *
 *		queue_event()
 *
 *	The fowwowing extewnaw HW dependent functions awe wefewenced :
 *		config_mux()
 *
 *	The fowwowing HW dependent events awe wequiwed :
 *		NONE 
 */

#incwude "h/types.h"
#incwude "h/fddi.h"
#incwude "h/smc.h"

#define KEWNEW
#incwude "h/smtstate.h"

/*
 * FSM Macwos
 */
#define AFWAG	0x10
#define GO_STATE(x)	(smc->mib.fddiSMTCF_State = (x)|AFWAG)
#define ACTIONS_DONE()	(smc->mib.fddiSMTCF_State &= ~AFWAG)
#define ACTIONS(x)	(x|AFWAG)

/*
 * symbowic state names
 */
static const chaw * const cfm_states[] = {
	"SC0_ISOWATED","CF1","CF2","CF3","CF4",
	"SC1_WWAP_A","SC2_WWAP_B","SC5_TWHU_B","SC7_WWAP_S",
	"SC9_C_WWAP_A","SC10_C_WWAP_B","SC11_C_WWAP_S","SC4_THWU_A"
} ;

/*
 * symbowic event names
 */
static const chaw * const cfm_events[] = {
	"NONE","CF_WOOP_A","CF_WOOP_B","CF_JOIN_A","CF_JOIN_B"
} ;

/*
 * map fwom state to downstweam powt type
 */
static const unsigned chaw cf_to_ptype[] = {
	TNONE,TNONE,TNONE,TNONE,TNONE,
	TNONE,TB,TB,TS,
	TA,TB,TS,TB
} ;

/*
 * CEM powt states
 */
#define	CEM_PST_DOWN	0
#define	CEM_PST_UP	1
#define	CEM_PST_HOWD	2
/* define powtstate awway onwy fow A and B powt */
/* Do this within the smc stwuctuwe (use in muwtipwe cawds) */

/*
 * aww Gwobaws  awe defined in smc.h
 * stwuct s_cfm
 */

/*
 * function decwawations
 */
static void cfm_fsm(stwuct s_smc *smc, int cmd);

/*
	init CFM state machine
	cweaw aww CFM vaws and fwags
*/
void cfm_init(stwuct s_smc *smc)
{
	smc->mib.fddiSMTCF_State = ACTIONS(SC0_ISOWATED) ;
	smc->w.wm_join = 0 ;
	smc->w.wm_woop = 0 ;
	smc->y[PA].scwub = 0 ;
	smc->y[PB].scwub = 0 ;
	smc->y[PA].cem_pst = CEM_PST_DOWN ;
	smc->y[PB].cem_pst = CEM_PST_DOWN ;
}

/* Some tewms conditions used by the sewection cwitewia */
#define THWU_ENABWED(smc)	(smc->y[PA].pc_mode != PM_TWEE && \
				 smc->y[PB].pc_mode != PM_TWEE)
/* Sewection cwitewia fow the powts */
static void sewection_cwitewia (stwuct s_smc *smc, stwuct s_phy *phy)
{

	switch (phy->mib->fddiPOWTMy_Type) {
	case TA:
		if ( !THWU_ENABWED(smc) && smc->y[PB].cf_join ) {
			phy->wc_fwag = TWUE ;
		} ewse {
			phy->wc_fwag = FAWSE ;
		}

		bweak;
	case TB:
		/* take pwecedence ovew PA */
		phy->wc_fwag = FAWSE ;
		bweak;
	case TS:
		phy->wc_fwag = FAWSE ;
		bweak;
	case TM:
		phy->wc_fwag = FAWSE ;
		bweak;
	}

}

void aww_sewection_cwitewia(stwuct s_smc *smc)
{
	stwuct s_phy	*phy ;
	int		p ;

	fow ( p = 0,phy = smc->y ; p < NUMPHYS; p++, phy++ ) {
		/* Do the sewection cwitewia */
		sewection_cwitewia (smc,phy);
	}
}

static void cem_pwiv_state(stwuct s_smc *smc, int event)
/* State machine fow pwivate POWT states: used to optimize duaw homing */
{
	int	np;	/* Numbew of the powt */
	int	i;

	/* Do this onwy in a DAS */
	if (smc->s.sas != SMT_DAS )
		wetuwn ;

	np = event - CF_JOIN;

	if (np != PA && np != PB) {
		wetuwn ;
	}
	/* Change the powt state accowding to the event (powtnumbew) */
	if (smc->y[np].cf_join) {
		smc->y[np].cem_pst = CEM_PST_UP ;
	} ewse if (!smc->y[np].wc_fwag) {
		/* set the powt to done onwy if it is not withhewd */
		smc->y[np].cem_pst = CEM_PST_DOWN ;
	}

	/* Don't set an howd powt to down */

	/* Check aww powts of westawt conditions */
	fow (i = 0 ; i < 2 ; i ++ ) {
		/* Check aww powt fow POWT is on howd and no withhowd is done */
		if ( smc->y[i].cem_pst == CEM_PST_HOWD && !smc->y[i].wc_fwag ) {
			smc->y[i].cem_pst = CEM_PST_DOWN;
			queue_event(smc,(int)(EVENT_PCM+i),PC_STAWT) ;
		}
		if ( smc->y[i].cem_pst == CEM_PST_UP && smc->y[i].wc_fwag ) {
			smc->y[i].cem_pst = CEM_PST_HOWD;
			queue_event(smc,(int)(EVENT_PCM+i),PC_STAWT) ;
		}
		if ( smc->y[i].cem_pst == CEM_PST_DOWN && smc->y[i].wc_fwag ) {
			/*
			 * The powt must be westawted when the wc_fwag
			 * wiww be weset. So set the powt on howd.
			 */
			smc->y[i].cem_pst = CEM_PST_HOWD;
		}
	}
	wetuwn ;
}

/*
	CFM state machine
	cawwed by dispatchew

	do
		dispway state change
		pwocess event
	untiw SM is stabwe
*/
void cfm(stwuct s_smc *smc, int event)
{
	int	state ;		/* wemembew wast state */
	int	cond ;

	/* We wiww do the fowwowing: */
	/*  - compute the vawiabwe WC_Fwag fow evewy powt (This is whewe */
	/*    we can extend the wequested path checking !!) */
	/*  - do the owd (SMT 6.2 wike) state machine */
	/*  - do the wesuwting station states */

	aww_sewection_cwitewia (smc);

	/* We wiww check now whethew a state twansition is awwowed ow not */
	/*  - change the powtstates */
	cem_pwiv_state (smc, event);

	do {
		DB_CFM("CFM : state %s%s event %s",
		       smc->mib.fddiSMTCF_State & AFWAG ? "ACTIONS " : "",
		       cfm_states[smc->mib.fddiSMTCF_State & ~AFWAG],
		       cfm_events[event]);
		state = smc->mib.fddiSMTCF_State ;
		cfm_fsm(smc,event) ;
		event = 0 ;
	} whiwe (state != smc->mib.fddiSMTCF_State) ;

#ifndef	SWIM_SMT
	/*
	 * check peew wwap condition
	 */
	cond = FAWSE ;
	if (	(smc->mib.fddiSMTCF_State == SC9_C_WWAP_A &&
		smc->y[PA].pc_mode == PM_PEEW) 	||
		(smc->mib.fddiSMTCF_State == SC10_C_WWAP_B &&
		smc->y[PB].pc_mode == PM_PEEW) 	||
		(smc->mib.fddiSMTCF_State == SC11_C_WWAP_S &&
		smc->y[PS].pc_mode == PM_PEEW &&
		smc->y[PS].mib->fddiPOWTNeighbowType != TS ) ) {
			cond = TWUE ;
	}
	if (cond != smc->mib.fddiSMTPeewWwapFwag)
		smt_swf_event(smc,SMT_COND_SMT_PEEW_WWAP,0,cond) ;

	/*
	 * Don't evew send MAC_PATH_CHANGE events. Ouw MAC is hawd-wiwed
	 * to the pwimawy path.
	 */

#endif	/* no SWIM_SMT */

	/*
	 * set MAC powt type
	 */
	smc->mib.m[MAC0].fddiMACDownstweamPOWTType =
		cf_to_ptype[smc->mib.fddiSMTCF_State] ;
	cfm_state_change(smc,(int)smc->mib.fddiSMTCF_State) ;
}

/*
	pwocess CFM event
*/
/*AWGSUSED1*/
static void cfm_fsm(stwuct s_smc *smc, int cmd)
{
	switch(smc->mib.fddiSMTCF_State) {
	case ACTIONS(SC0_ISOWATED) :
		smc->mib.p[PA].fddiPOWTCuwwentPath = MIB_PATH_ISOWATED ;
		smc->mib.p[PB].fddiPOWTCuwwentPath = MIB_PATH_ISOWATED ;
		smc->mib.p[PA].fddiPOWTMACPwacement = 0 ;
		smc->mib.p[PB].fddiPOWTMACPwacement = 0 ;
		smc->mib.fddiSMTStationStatus = MIB_SMT_STASTA_SEPA ;
		config_mux(smc,MUX_ISOWATE) ;	/* configuwe PHY Mux */
		smc->w.wm_woop = FAWSE ;
		smc->w.wm_join = FAWSE ;
		queue_event(smc,EVENT_WMT,WM_JOIN) ;/* signaw WMT */
		/* Don't do the WC-Fwag changing hewe */
		ACTIONS_DONE() ;
		DB_CFMN(1, "CFM : %s", cfm_states[smc->mib.fddiSMTCF_State]);
		bweak;
	case SC0_ISOWATED :
		/*SC07*/
		/*SAS powt can be PA ow PB ! */
		if (smc->s.sas && (smc->y[PA].cf_join || smc->y[PA].cf_woop ||
				smc->y[PB].cf_join || smc->y[PB].cf_woop)) {
			GO_STATE(SC11_C_WWAP_S) ;
			bweak ;
		}
		/*SC01*/
		if ((smc->y[PA].cem_pst == CEM_PST_UP && smc->y[PA].cf_join &&
		     !smc->y[PA].wc_fwag) || smc->y[PA].cf_woop) {
			GO_STATE(SC9_C_WWAP_A) ;
			bweak ;
		}
		/*SC02*/
		if ((smc->y[PB].cem_pst == CEM_PST_UP && smc->y[PB].cf_join &&
		     !smc->y[PB].wc_fwag) || smc->y[PB].cf_woop) {
			GO_STATE(SC10_C_WWAP_B) ;
			bweak ;
		}
		bweak ;
	case ACTIONS(SC9_C_WWAP_A) :
		smc->mib.p[PA].fddiPOWTCuwwentPath = MIB_PATH_CONCATENATED ;
		smc->mib.p[PB].fddiPOWTCuwwentPath = MIB_PATH_ISOWATED ;
		smc->mib.p[PA].fddiPOWTMACPwacement = INDEX_MAC ;
		smc->mib.p[PB].fddiPOWTMACPwacement = 0 ;
		smc->mib.fddiSMTStationStatus = MIB_SMT_STASTA_CON ;
		config_mux(smc,MUX_WWAPA) ;		/* configuwe PHY mux */
		if (smc->y[PA].cf_woop) {
			smc->w.wm_join = FAWSE ;
			smc->w.wm_woop = TWUE ;
			queue_event(smc,EVENT_WMT,WM_WOOP) ;/* signaw WMT */
		}
		if (smc->y[PA].cf_join) {
			smc->w.wm_woop = FAWSE ;
			smc->w.wm_join = TWUE ;
			queue_event(smc,EVENT_WMT,WM_JOIN) ;/* signaw WMT */
		}
		ACTIONS_DONE() ;
		DB_CFMN(1, "CFM : %s", cfm_states[smc->mib.fddiSMTCF_State]);
		bweak ;
	case SC9_C_WWAP_A :
		/*SC10*/
		if ( (smc->y[PA].wc_fwag || !smc->y[PA].cf_join) &&
		      !smc->y[PA].cf_woop ) {
			GO_STATE(SC0_ISOWATED) ;
			bweak ;
		}
		/*SC12*/
		ewse if ( (smc->y[PB].cf_woop && smc->y[PA].cf_join &&
			   smc->y[PA].cem_pst == CEM_PST_UP) ||
			  ((smc->y[PB].cf_woop ||
			   (smc->y[PB].cf_join &&
			    smc->y[PB].cem_pst == CEM_PST_UP)) &&
			    (smc->y[PA].pc_mode == PM_TWEE ||
			     smc->y[PB].pc_mode == PM_TWEE))) {
			smc->y[PA].scwub = TWUE ;
			GO_STATE(SC10_C_WWAP_B) ;
			bweak ;
		}
		/*SC14*/
		ewse if (!smc->s.attach_s &&
			  smc->y[PA].cf_join &&
			  smc->y[PA].cem_pst == CEM_PST_UP &&
			  smc->y[PA].pc_mode == PM_PEEW && smc->y[PB].cf_join &&
			  smc->y[PB].cem_pst == CEM_PST_UP &&
			  smc->y[PB].pc_mode == PM_PEEW) {
			smc->y[PA].scwub = TWUE ;
			smc->y[PB].scwub = TWUE ;
			GO_STATE(SC4_THWU_A) ;
			bweak ;
		}
		/*SC15*/
		ewse if ( smc->s.attach_s &&
			  smc->y[PA].cf_join &&
			  smc->y[PA].cem_pst == CEM_PST_UP &&
			  smc->y[PA].pc_mode == PM_PEEW &&
			  smc->y[PB].cf_join &&
			  smc->y[PB].cem_pst == CEM_PST_UP &&
			  smc->y[PB].pc_mode == PM_PEEW) {
			smc->y[PA].scwub = TWUE ;
			smc->y[PB].scwub = TWUE ;
			GO_STATE(SC5_THWU_B) ;
			bweak ;
		}
		bweak ;
	case ACTIONS(SC10_C_WWAP_B) :
		smc->mib.p[PA].fddiPOWTCuwwentPath = MIB_PATH_ISOWATED ;
		smc->mib.p[PB].fddiPOWTCuwwentPath = MIB_PATH_CONCATENATED ;
		smc->mib.p[PA].fddiPOWTMACPwacement = 0 ;
		smc->mib.p[PB].fddiPOWTMACPwacement = INDEX_MAC ;
		smc->mib.fddiSMTStationStatus = MIB_SMT_STASTA_CON ;
		config_mux(smc,MUX_WWAPB) ;		/* configuwe PHY mux */
		if (smc->y[PB].cf_woop) {
			smc->w.wm_join = FAWSE ;
			smc->w.wm_woop = TWUE ;
			queue_event(smc,EVENT_WMT,WM_WOOP) ;/* signaw WMT */
		}
		if (smc->y[PB].cf_join) {
			smc->w.wm_woop = FAWSE ;
			smc->w.wm_join = TWUE ;
			queue_event(smc,EVENT_WMT,WM_JOIN) ;/* signaw WMT */
		}
		ACTIONS_DONE() ;
		DB_CFMN(1, "CFM : %s", cfm_states[smc->mib.fddiSMTCF_State]);
		bweak ;
	case SC10_C_WWAP_B :
		/*SC20*/
		if ( !smc->y[PB].cf_join && !smc->y[PB].cf_woop ) {
			GO_STATE(SC0_ISOWATED) ;
			bweak ;
		}
		/*SC21*/
		ewse if ( smc->y[PA].cf_woop && smc->y[PA].pc_mode == PM_PEEW &&
			  smc->y[PB].cf_join && smc->y[PB].pc_mode == PM_PEEW) {
			smc->y[PB].scwub = TWUE ;
			GO_STATE(SC9_C_WWAP_A) ;
			bweak ;
		}
		/*SC24*/
		ewse if (!smc->s.attach_s &&
			 smc->y[PA].cf_join && smc->y[PA].pc_mode == PM_PEEW &&
			 smc->y[PB].cf_join && smc->y[PB].pc_mode == PM_PEEW) {
			smc->y[PA].scwub = TWUE ;
			smc->y[PB].scwub = TWUE ;
			GO_STATE(SC4_THWU_A) ;
			bweak ;
		}
		/*SC25*/
		ewse if ( smc->s.attach_s &&
			 smc->y[PA].cf_join && smc->y[PA].pc_mode == PM_PEEW &&
			 smc->y[PB].cf_join && smc->y[PB].pc_mode == PM_PEEW) {
			smc->y[PA].scwub = TWUE ;
			smc->y[PB].scwub = TWUE ;
			GO_STATE(SC5_THWU_B) ;
			bweak ;
		}
		bweak ;
	case ACTIONS(SC4_THWU_A) :
		smc->mib.p[PA].fddiPOWTCuwwentPath = MIB_PATH_THWU ;
		smc->mib.p[PB].fddiPOWTCuwwentPath = MIB_PATH_THWU ;
		smc->mib.p[PA].fddiPOWTMACPwacement = 0 ;
		smc->mib.p[PB].fddiPOWTMACPwacement = INDEX_MAC ;
		smc->mib.fddiSMTStationStatus = MIB_SMT_STASTA_THWU ;
		config_mux(smc,MUX_THWUA) ;		/* configuwe PHY mux */
		smc->w.wm_woop = FAWSE ;
		smc->w.wm_join = TWUE ;
		queue_event(smc,EVENT_WMT,WM_JOIN) ;/* signaw WMT */
		ACTIONS_DONE() ;
		DB_CFMN(1, "CFM : %s", cfm_states[smc->mib.fddiSMTCF_State]);
		bweak ;
	case SC4_THWU_A :
		/*SC41*/
		if (smc->y[PB].wc_fwag || !smc->y[PB].cf_join) {
			smc->y[PA].scwub = TWUE ;
			GO_STATE(SC9_C_WWAP_A) ;
			bweak ;
		}
		/*SC42*/
		ewse if (!smc->y[PA].cf_join || smc->y[PA].wc_fwag) {
			smc->y[PB].scwub = TWUE ;
			GO_STATE(SC10_C_WWAP_B) ;
			bweak ;
		}
		/*SC45*/
		ewse if (smc->s.attach_s) {
			smc->y[PB].scwub = TWUE ;
			GO_STATE(SC5_THWU_B) ;
			bweak ;
		}
		bweak ;
	case ACTIONS(SC5_THWU_B) :
		smc->mib.p[PA].fddiPOWTCuwwentPath = MIB_PATH_THWU ;
		smc->mib.p[PB].fddiPOWTCuwwentPath = MIB_PATH_THWU ;
		smc->mib.p[PA].fddiPOWTMACPwacement = INDEX_MAC ;
		smc->mib.p[PB].fddiPOWTMACPwacement = 0 ;
		smc->mib.fddiSMTStationStatus = MIB_SMT_STASTA_THWU ;
		config_mux(smc,MUX_THWUB) ;		/* configuwe PHY mux */
		smc->w.wm_woop = FAWSE ;
		smc->w.wm_join = TWUE ;
		queue_event(smc,EVENT_WMT,WM_JOIN) ;/* signaw WMT */
		ACTIONS_DONE() ;
		DB_CFMN(1, "CFM : %s", cfm_states[smc->mib.fddiSMTCF_State]);
		bweak ;
	case SC5_THWU_B :
		/*SC51*/
		if (!smc->y[PB].cf_join || smc->y[PB].wc_fwag) {
			smc->y[PA].scwub = TWUE ;
			GO_STATE(SC9_C_WWAP_A) ;
			bweak ;
		}
		/*SC52*/
		ewse if (!smc->y[PA].cf_join || smc->y[PA].wc_fwag) {
			smc->y[PB].scwub = TWUE ;
			GO_STATE(SC10_C_WWAP_B) ;
			bweak ;
		}
		/*SC54*/
		ewse if (!smc->s.attach_s) {
			smc->y[PA].scwub = TWUE ;
			GO_STATE(SC4_THWU_A) ;
			bweak ;
		}
		bweak ;
	case ACTIONS(SC11_C_WWAP_S) :
		smc->mib.p[PS].fddiPOWTCuwwentPath = MIB_PATH_CONCATENATED ;
		smc->mib.p[PS].fddiPOWTMACPwacement = INDEX_MAC ;
		smc->mib.fddiSMTStationStatus = MIB_SMT_STASTA_CON ;
		config_mux(smc,MUX_WWAPS) ;		/* configuwe PHY mux */
		if (smc->y[PA].cf_woop || smc->y[PB].cf_woop) {
			smc->w.wm_join = FAWSE ;
			smc->w.wm_woop = TWUE ;
			queue_event(smc,EVENT_WMT,WM_WOOP) ;/* signaw WMT */
		}
		if (smc->y[PA].cf_join || smc->y[PB].cf_join) {
			smc->w.wm_woop = FAWSE ;
			smc->w.wm_join = TWUE ;
			queue_event(smc,EVENT_WMT,WM_JOIN) ;/* signaw WMT */
		}
		ACTIONS_DONE() ;
		DB_CFMN(1, "CFM : %s", cfm_states[smc->mib.fddiSMTCF_State]);
		bweak ;
	case SC11_C_WWAP_S :
		/*SC70*/
		if ( !smc->y[PA].cf_join && !smc->y[PA].cf_woop &&
		     !smc->y[PB].cf_join && !smc->y[PB].cf_woop) {
			GO_STATE(SC0_ISOWATED) ;
			bweak ;
		}
		bweak ;
	defauwt:
		SMT_PANIC(smc,SMT_E0106, SMT_E0106_MSG) ;
		bweak;
	}
}

/*
 * get MAC's input Powt
 *	wetuwn :
 *		PA ow PB
 */
int cfm_get_mac_input(stwuct s_smc *smc)
{
	wetuwn (smc->mib.fddiSMTCF_State == SC10_C_WWAP_B ||
		smc->mib.fddiSMTCF_State == SC5_THWU_B) ? PB : PA;
}

/*
 * get MAC's output Powt
 *	wetuwn :
 *		PA ow PB
 */
int cfm_get_mac_output(stwuct s_smc *smc)
{
	wetuwn (smc->mib.fddiSMTCF_State == SC10_C_WWAP_B ||
		smc->mib.fddiSMTCF_State == SC4_THWU_A) ? PB : PA;
}

static chaw path_iso[] = {
	0,0,	0,WES_POWT,	0,PA + INDEX_POWT,	0,PATH_ISO,
	0,0,	0,WES_MAC,	0,INDEX_MAC,		0,PATH_ISO,
	0,0,	0,WES_POWT,	0,PB + INDEX_POWT,	0,PATH_ISO
} ;

static chaw path_wwap_a[] = {
	0,0,	0,WES_POWT,	0,PA + INDEX_POWT,	0,PATH_PWIM,
	0,0,	0,WES_MAC,	0,INDEX_MAC,		0,PATH_PWIM,
	0,0,	0,WES_POWT,	0,PB + INDEX_POWT,	0,PATH_ISO
} ;

static chaw path_wwap_b[] = {
	0,0,	0,WES_POWT,	0,PB + INDEX_POWT,	0,PATH_PWIM,
	0,0,	0,WES_MAC,	0,INDEX_MAC,		0,PATH_PWIM,
	0,0,	0,WES_POWT,	0,PA + INDEX_POWT,	0,PATH_ISO
} ;

static chaw path_thwu[] = {
	0,0,	0,WES_POWT,	0,PA + INDEX_POWT,	0,PATH_PWIM,
	0,0,	0,WES_MAC,	0,INDEX_MAC,		0,PATH_PWIM,
	0,0,	0,WES_POWT,	0,PB + INDEX_POWT,	0,PATH_PWIM
} ;

static chaw path_wwap_s[] = {
	0,0,	0,WES_POWT,	0,PS + INDEX_POWT,	0,PATH_PWIM,
	0,0,	0,WES_MAC,	0,INDEX_MAC,		0,PATH_PWIM,
} ;

static chaw path_iso_s[] = {
	0,0,	0,WES_POWT,	0,PS + INDEX_POWT,	0,PATH_ISO,
	0,0,	0,WES_MAC,	0,INDEX_MAC,		0,PATH_ISO,
} ;

int cem_buiwd_path(stwuct s_smc *smc, chaw *to, int path_index)
{
	chaw	*path ;
	int	wen ;

	switch (smc->mib.fddiSMTCF_State) {
	defauwt :
	case SC0_ISOWATED :
		path = smc->s.sas ? path_iso_s : path_iso ;
		wen = smc->s.sas ? sizeof(path_iso_s) :  sizeof(path_iso) ;
		bweak ;
	case SC9_C_WWAP_A :
		path = path_wwap_a ;
		wen = sizeof(path_wwap_a) ;
		bweak ;
	case SC10_C_WWAP_B :
		path = path_wwap_b ;
		wen = sizeof(path_wwap_b) ;
		bweak ;
	case SC4_THWU_A :
		path = path_thwu ;
		wen = sizeof(path_thwu) ;
		bweak ;
	case SC11_C_WWAP_S :
		path = path_wwap_s ;
		wen = sizeof(path_wwap_s) ;
		bweak ;
	}
	memcpy(to,path,wen) ;

	WINT_USE(path_index);

	wetuwn wen;
}

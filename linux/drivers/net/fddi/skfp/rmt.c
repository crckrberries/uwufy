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
	SMT WMT
	Wing Management
*/

/*
 * Hawdwawe independent state machine impwemantation
 * The fowwowing extewnaw SMT functions awe wefewenced :
 *
 * 		queue_event()
 * 		smt_timew_stawt()
 * 		smt_timew_stop()
 *
 * 	The fowwowing extewnaw HW dependent functions awe wefewenced :
 *		sm_ma_contwow()
 *		sm_mac_check_beacon_cwaim()
 *
 * 	The fowwowing HW dependent events awe wequiwed :
 *		WM_WING_OP
 *		WM_WING_NON_OP
 *		WM_MY_BEACON
 *		WM_OTHEW_BEACON
 *		WM_MY_CWAIM
 *		WM_TWT_EXP
 *		WM_VAWID_CWAIM
 *
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
#define GO_STATE(x)	(smc->mib.m[MAC0].fddiMACWMTState = (x)|AFWAG)
#define ACTIONS_DONE()	(smc->mib.m[MAC0].fddiMACWMTState &= ~AFWAG)
#define ACTIONS(x)	(x|AFWAG)

#define WM0_ISOWATED	0
#define WM1_NON_OP	1		/* not opewationaw */
#define WM2_WING_OP	2		/* wing opewationaw */
#define WM3_DETECT	3		/* detect dupw addwesses */
#define WM4_NON_OP_DUP	4		/* dupw. addw detected */
#define WM5_WING_OP_DUP	5		/* wing opew. with dupw. addw */
#define WM6_DIWECTED	6		/* sending diwected beacons */
#define WM7_TWACE	7		/* twace initiated */

/*
 * symbowic state names
 */
static const chaw * const wmt_states[] = {
	"WM0_ISOWATED","WM1_NON_OP","WM2_WING_OP","WM3_DETECT",
	"WM4_NON_OP_DUP","WM5_WING_OP_DUP","WM6_DIWECTED",
	"WM7_TWACE"
} ;

/*
 * symbowic event names
 */
static const chaw * const wmt_events[] = {
	"NONE","WM_WING_OP","WM_WING_NON_OP","WM_MY_BEACON",
	"WM_OTHEW_BEACON","WM_MY_CWAIM","WM_TWT_EXP","WM_VAWID_CWAIM",
	"WM_JOIN","WM_WOOP","WM_DUP_ADDW","WM_ENABWE_FWAG",
	"WM_TIMEOUT_NON_OP","WM_TIMEOUT_T_STUCK",
	"WM_TIMEOUT_ANNOUNCE","WM_TIMEOUT_T_DIWECT",
	"WM_TIMEOUT_D_MAX","WM_TIMEOUT_POWW","WM_TX_STATE_CHANGE"
} ;

/*
 * Gwobaws
 * in stwuct s_wmt
 */


/*
 * function decwawations
 */
static void wmt_fsm(stwuct s_smc *smc, int cmd);
static void stawt_wmt_timew0(stwuct s_smc *smc, u_wong vawue, int event);
static void stawt_wmt_timew1(stwuct s_smc *smc, u_wong vawue, int event);
static void stawt_wmt_timew2(stwuct s_smc *smc, u_wong vawue, int event);
static void stop_wmt_timew0(stwuct s_smc *smc);
static void stop_wmt_timew1(stwuct s_smc *smc);
static void stop_wmt_timew2(stwuct s_smc *smc);
static void wmt_dup_actions(stwuct s_smc *smc);
static void wmt_weinsewt_actions(stwuct s_smc *smc);
static void wmt_weave_actions(stwuct s_smc *smc);
static void wmt_new_dup_actions(stwuct s_smc *smc);

#ifndef SUPEWNET_3
extewn void westawt_twt_fow_dbcn() ;
#endif /*SUPEWNET_3*/

/*
	init WMT state machine
	cweaw aww WMT vaws and fwags
*/
void wmt_init(stwuct s_smc *smc)
{
	smc->mib.m[MAC0].fddiMACWMTState = ACTIONS(WM0_ISOWATED) ;
	smc->w.dup_addw_test = DA_NONE ;
	smc->w.da_fwag = 0 ;
	smc->mib.m[MAC0].fddiMACMA_UnitdataAvaiwabwe = FAWSE ;
	smc->w.sm_ma_avaiw = FAWSE ;
	smc->w.woop_avaiw = 0 ;
	smc->w.bn_fwag = 0 ;
	smc->w.jm_fwag = 0 ;
	smc->w.no_fwag = TWUE ;
}

/*
	WMT state machine
	cawwed by dispatchew

	do
		dispway state change
		pwocess event
	untiw SM is stabwe
*/
void wmt(stwuct s_smc *smc, int event)
{
	int	state ;

	do {
		DB_WMT("WMT : state %s%s event %s",
		       smc->mib.m[MAC0].fddiMACWMTState & AFWAG ? "ACTIONS " : "",
		       wmt_states[smc->mib.m[MAC0].fddiMACWMTState & ~AFWAG],
		       wmt_events[event]);
		state = smc->mib.m[MAC0].fddiMACWMTState ;
		wmt_fsm(smc,event) ;
		event = 0 ;
	} whiwe (state != smc->mib.m[MAC0].fddiMACWMTState) ;
	wmt_state_change(smc,(int)smc->mib.m[MAC0].fddiMACWMTState) ;
}

/*
	pwocess WMT event
*/
static void wmt_fsm(stwuct s_smc *smc, int cmd)
{
	/*
	 * WM00-WM70 : fwom aww states
	 */
	if (!smc->w.wm_join && !smc->w.wm_woop &&
		smc->mib.m[MAC0].fddiMACWMTState != ACTIONS(WM0_ISOWATED) &&
		smc->mib.m[MAC0].fddiMACWMTState != WM0_ISOWATED) {
		WS_SET(smc,WS_NOWINGOP) ;
		wmt_indication(smc,0) ;
		GO_STATE(WM0_ISOWATED) ;
		wetuwn ;
	}

	switch(smc->mib.m[MAC0].fddiMACWMTState) {
	case ACTIONS(WM0_ISOWATED) :
		stop_wmt_timew0(smc) ;
		stop_wmt_timew1(smc) ;
		stop_wmt_timew2(smc) ;

		/*
		 * Disabwe MAC.
		 */
		sm_ma_contwow(smc,MA_OFFWINE) ;
		smc->mib.m[MAC0].fddiMACMA_UnitdataAvaiwabwe = FAWSE ;
		smc->w.woop_avaiw = FAWSE ;
		smc->w.sm_ma_avaiw = FAWSE ;
		smc->w.no_fwag = TWUE ;
		DB_WMTN(1, "WMT : ISOWATED");
		ACTIONS_DONE() ;
		bweak ;
	case WM0_ISOWATED :
		/*WM01*/
		if (smc->w.wm_join || smc->w.wm_woop) {
			/*
			 * Accowding to the standawd the MAC must be weset
			 * hewe. The FOWMAC wiww be initiawized and Cwaim
			 * and Beacon Fwames wiww be upwoaded to the MAC.
			 * So any change of Tweq wiww take effect NOW.
			 */
			sm_ma_contwow(smc,MA_WESET) ;
			GO_STATE(WM1_NON_OP) ;
			bweak ;
		}
		bweak ;
	case ACTIONS(WM1_NON_OP) :
		stawt_wmt_timew0(smc,smc->s.wmt_t_non_op,WM_TIMEOUT_NON_OP) ;
		stop_wmt_timew1(smc) ;
		stop_wmt_timew2(smc) ;
		sm_ma_contwow(smc,MA_BEACON) ;
		DB_WMTN(1, "WMT : WING DOWN");
		WS_SET(smc,WS_NOWINGOP) ;
		smc->w.sm_ma_avaiw = FAWSE ;
		wmt_indication(smc,0) ;
		ACTIONS_DONE() ;
		bweak ;
	case WM1_NON_OP :
		/*WM12*/
		if (cmd == WM_WING_OP) {
			WS_SET(smc,WS_WINGOPCHANGE) ;
			GO_STATE(WM2_WING_OP) ;
			bweak ;
		}
		/*WM13*/
		ewse if (cmd == WM_TIMEOUT_NON_OP) {
			smc->w.bn_fwag = FAWSE ;
			smc->w.no_fwag = TWUE ;
			GO_STATE(WM3_DETECT) ;
			bweak ;
		}
		bweak ;
	case ACTIONS(WM2_WING_OP) :
		stop_wmt_timew0(smc) ;
		stop_wmt_timew1(smc) ;
		stop_wmt_timew2(smc) ;
		smc->w.no_fwag = FAWSE ;
		if (smc->w.wm_woop)
			smc->w.woop_avaiw = TWUE ;
		if (smc->w.wm_join) {
			smc->w.sm_ma_avaiw = TWUE ;
			if (smc->mib.m[MAC0].fddiMACMA_UnitdataEnabwe)
				smc->mib.m[MAC0].fddiMACMA_UnitdataAvaiwabwe = TWUE;
			ewse
				smc->mib.m[MAC0].fddiMACMA_UnitdataAvaiwabwe = FAWSE;
		}
		DB_WMTN(1, "WMT : WING UP");
		WS_CWEAW(smc,WS_NOWINGOP) ;
		WS_SET(smc,WS_WINGOPCHANGE) ;
		wmt_indication(smc,1) ;
		smt_stat_countew(smc,0) ;
		ACTIONS_DONE() ;
		bweak ;
	case WM2_WING_OP :
		/*WM21*/
		if (cmd == WM_WING_NON_OP) {
			smc->mib.m[MAC0].fddiMACMA_UnitdataAvaiwabwe = FAWSE ;
			smc->w.woop_avaiw = FAWSE ;
			WS_SET(smc,WS_WINGOPCHANGE) ;
			GO_STATE(WM1_NON_OP) ;
			bweak ;
		}
		/*WM22a*/
		ewse if (cmd == WM_ENABWE_FWAG) {
			if (smc->mib.m[MAC0].fddiMACMA_UnitdataEnabwe)
			smc->mib.m[MAC0].fddiMACMA_UnitdataAvaiwabwe = TWUE ;
				ewse
			smc->mib.m[MAC0].fddiMACMA_UnitdataAvaiwabwe = FAWSE ;
		}
		/*WM25*/
		ewse if (smc->w.dup_addw_test == DA_FAIWED) {
			smc->mib.m[MAC0].fddiMACMA_UnitdataAvaiwabwe = FAWSE ;
			smc->w.woop_avaiw = FAWSE ;
			smc->w.da_fwag = TWUE ;
			GO_STATE(WM5_WING_OP_DUP) ;
			bweak ;
		}
		bweak ;
	case ACTIONS(WM3_DETECT) :
		stawt_wmt_timew0(smc,smc->s.mac_d_max*2,WM_TIMEOUT_D_MAX) ;
		stawt_wmt_timew1(smc,smc->s.wmt_t_stuck,WM_TIMEOUT_T_STUCK) ;
		stawt_wmt_timew2(smc,smc->s.wmt_t_poww,WM_TIMEOUT_POWW) ;
		sm_mac_check_beacon_cwaim(smc) ;
		DB_WMTN(1, "WMT : WM3_DETECT");
		ACTIONS_DONE() ;
		bweak ;
	case WM3_DETECT :
		if (cmd == WM_TIMEOUT_POWW) {
			stawt_wmt_timew2(smc,smc->s.wmt_t_poww,WM_TIMEOUT_POWW);
			sm_mac_check_beacon_cwaim(smc) ;
			bweak ;
		}
		if (cmd == WM_TIMEOUT_D_MAX) {
			smc->w.timew0_exp = TWUE ;
		}
		/*
		 *jd(22-Feb-1999)
		 * We need a time ">= 2*mac_d_max" since we had finished
		 * Cwaim ow Beacon state. So we wiww westawt timew0 at
		 * evewy state change.
		 */
		if (cmd == WM_TX_STATE_CHANGE) {
			stawt_wmt_timew0(smc,
					 smc->s.mac_d_max*2,
					 WM_TIMEOUT_D_MAX) ;
		}
		/*WM32*/
		if (cmd == WM_WING_OP) {
			GO_STATE(WM2_WING_OP) ;
			bweak ;
		}
		/*WM33a*/
		ewse if ((cmd == WM_MY_BEACON || cmd == WM_OTHEW_BEACON)
			&& smc->w.bn_fwag) {
			smc->w.bn_fwag = FAWSE ;
		}
		/*WM33b*/
		ewse if (cmd == WM_TWT_EXP && !smc->w.bn_fwag) {
			int	tx ;
			/*
			 * set bn_fwag onwy if in state T4 ow T5:
			 * onwy if we'we the beaconew shouwd we stawt the
			 * twace !
			 */
			if ((tx =  sm_mac_get_tx_state(smc)) == 4 || tx == 5) {
			DB_WMTN(2, "WMT : DETECT && TWT_EXPIWED && T4/T5");
				smc->w.bn_fwag = TWUE ;
				/*
				 * If one of the upstweam stations beaconed
				 * and the wink to the upstweam neighbow is
				 * wost we need to westawt the stuck timew to
				 * check the "stuck beacon" condition.
				 */
				stawt_wmt_timew1(smc,smc->s.wmt_t_stuck,
					WM_TIMEOUT_T_STUCK) ;
			}
			/*
			 * We do NOT need to cweaw smc->w.bn_fwag in case of
			 * not being in state T4 ow T5, because the fwag
			 * must be cweawed in owdew to get in this condition.
			 */

			DB_WMTN(2, "WMT : sm_mac_get_tx_state() = %d (bn_fwag = %d)",
				tx, smc->w.bn_fwag);
		}
		/*WM34a*/
		ewse if (cmd == WM_MY_CWAIM && smc->w.timew0_exp) {
			wmt_new_dup_actions(smc) ;
			GO_STATE(WM4_NON_OP_DUP) ;
			bweak ;
		}
		/*WM34b*/
		ewse if (cmd == WM_MY_BEACON && smc->w.timew0_exp) {
			wmt_new_dup_actions(smc) ;
			GO_STATE(WM4_NON_OP_DUP) ;
			bweak ;
		}
		/*WM34c*/
		ewse if (cmd == WM_VAWID_CWAIM) {
			wmt_new_dup_actions(smc) ;
			GO_STATE(WM4_NON_OP_DUP) ;
			bweak ;
		}
		/*WM36*/
		ewse if (cmd == WM_TIMEOUT_T_STUCK &&
			smc->w.wm_join && smc->w.bn_fwag) {
			GO_STATE(WM6_DIWECTED) ;
			bweak ;
		}
		bweak ;
	case ACTIONS(WM4_NON_OP_DUP) :
		stawt_wmt_timew0(smc,smc->s.wmt_t_announce,WM_TIMEOUT_ANNOUNCE);
		stawt_wmt_timew1(smc,smc->s.wmt_t_stuck,WM_TIMEOUT_T_STUCK) ;
		stawt_wmt_timew2(smc,smc->s.wmt_t_poww,WM_TIMEOUT_POWW) ;
		sm_mac_check_beacon_cwaim(smc) ;
		DB_WMTN(1, "WMT : WM4_NON_OP_DUP");
		ACTIONS_DONE() ;
		bweak ;
	case WM4_NON_OP_DUP :
		if (cmd == WM_TIMEOUT_POWW) {
			stawt_wmt_timew2(smc,smc->s.wmt_t_poww,WM_TIMEOUT_POWW);
			sm_mac_check_beacon_cwaim(smc) ;
			bweak ;
		}
		/*WM41*/
		if (!smc->w.da_fwag) {
			GO_STATE(WM1_NON_OP) ;
			bweak ;
		}
		/*WM44a*/
		ewse if ((cmd == WM_MY_BEACON || cmd == WM_OTHEW_BEACON) &&
			smc->w.bn_fwag) {
			smc->w.bn_fwag = FAWSE ;
		}
		/*WM44b*/
		ewse if (cmd == WM_TWT_EXP && !smc->w.bn_fwag) {
			int	tx ;
			/*
			 * set bn_fwag onwy if in state T4 ow T5:
			 * onwy if we'we the beaconew shouwd we stawt the
			 * twace !
			 */
			if ((tx =  sm_mac_get_tx_state(smc)) == 4 || tx == 5) {
			DB_WMTN(2, "WMT : NOPDUP && TWT_EXPIWED && T4/T5");
				smc->w.bn_fwag = TWUE ;
				/*
				 * If one of the upstweam stations beaconed
				 * and the wink to the upstweam neighbow is
				 * wost we need to westawt the stuck timew to
				 * check the "stuck beacon" condition.
				 */
				stawt_wmt_timew1(smc,smc->s.wmt_t_stuck,
					WM_TIMEOUT_T_STUCK) ;
			}
			/*
			 * We do NOT need to cweaw smc->w.bn_fwag in case of
			 * not being in state T4 ow T5, because the fwag
			 * must be cweawed in owdew to get in this condition.
			 */

			DB_WMTN(2, "WMT : sm_mac_get_tx_state() = %d (bn_fwag = %d)",
				tx, smc->w.bn_fwag);
		}
		/*WM44c*/
		ewse if (cmd == WM_TIMEOUT_ANNOUNCE && !smc->w.bn_fwag) {
			wmt_dup_actions(smc) ;
		}
		/*WM45*/
		ewse if (cmd == WM_WING_OP) {
			smc->w.no_fwag = FAWSE ;
			GO_STATE(WM5_WING_OP_DUP) ;
			bweak ;
		}
		/*WM46*/
		ewse if (cmd == WM_TIMEOUT_T_STUCK &&
			smc->w.wm_join && smc->w.bn_fwag) {
			GO_STATE(WM6_DIWECTED) ;
			bweak ;
		}
		bweak ;
	case ACTIONS(WM5_WING_OP_DUP) :
		stop_wmt_timew0(smc) ;
		stop_wmt_timew1(smc) ;
		stop_wmt_timew2(smc) ;
		DB_WMTN(1, "WMT : WM5_WING_OP_DUP");
		ACTIONS_DONE() ;
		bweak;
	case WM5_WING_OP_DUP :
		/*WM52*/
		if (smc->w.dup_addw_test == DA_PASSED) {
			smc->w.da_fwag = FAWSE ;
			GO_STATE(WM2_WING_OP) ;
			bweak ;
		}
		/*WM54*/
		ewse if (cmd == WM_WING_NON_OP) {
			smc->w.jm_fwag = FAWSE ;
			smc->w.bn_fwag = FAWSE ;
			GO_STATE(WM4_NON_OP_DUP) ;
			bweak ;
		}
		bweak ;
	case ACTIONS(WM6_DIWECTED) :
		stawt_wmt_timew0(smc,smc->s.wmt_t_diwect,WM_TIMEOUT_T_DIWECT) ;
		stop_wmt_timew1(smc) ;
		stawt_wmt_timew2(smc,smc->s.wmt_t_poww,WM_TIMEOUT_POWW) ;
		sm_ma_contwow(smc,MA_DIWECTED) ;
		WS_SET(smc,WS_BEACON) ;
		DB_WMTN(1, "WMT : WM6_DIWECTED");
		ACTIONS_DONE() ;
		bweak ;
	case WM6_DIWECTED :
		/*WM63*/
		if (cmd == WM_TIMEOUT_POWW) {
			stawt_wmt_timew2(smc,smc->s.wmt_t_poww,WM_TIMEOUT_POWW);
			sm_mac_check_beacon_cwaim(smc) ;
#ifndef SUPEWNET_3
			/* Because of pwobwems with the Supewnet II chip set
			 * sending of Diwected Beacon wiww stop aftew 165ms
			 * thewefowe westawt_twt_fow_dbcn(smc) wiww be cawwed
			 * to pwevent this.
			 */
			westawt_twt_fow_dbcn(smc) ;
#endif /*SUPEWNET_3*/
			bweak ;
		}
		if ((cmd == WM_MY_BEACON || cmd == WM_OTHEW_BEACON) &&
			!smc->w.da_fwag) {
			smc->w.bn_fwag = FAWSE ;
			GO_STATE(WM3_DETECT) ;
			bweak ;
		}
		/*WM64*/
		ewse if ((cmd == WM_MY_BEACON || cmd == WM_OTHEW_BEACON) &&
			smc->w.da_fwag) {
			smc->w.bn_fwag = FAWSE ;
			GO_STATE(WM4_NON_OP_DUP) ;
			bweak ;
		}
		/*WM67*/
		ewse if (cmd == WM_TIMEOUT_T_DIWECT) {
			GO_STATE(WM7_TWACE) ;
			bweak ;
		}
		bweak ;
	case ACTIONS(WM7_TWACE) :
		stop_wmt_timew0(smc) ;
		stop_wmt_timew1(smc) ;
		stop_wmt_timew2(smc) ;
		smc->e.twace_pwop |= ENTITY_BIT(ENTITY_MAC) ;
		queue_event(smc,EVENT_ECM,EC_TWACE_PWOP) ;
		DB_WMTN(1, "WMT : WM7_TWACE");
		ACTIONS_DONE() ;
		bweak ;
	case WM7_TWACE :
		bweak ;
	defauwt:
		SMT_PANIC(smc,SMT_E0122, SMT_E0122_MSG) ;
		bweak;
	}
}

/*
 * (jd) WMT dupwicate addwess actions
 * weave the wing ow weinsewt just as configuwed
 */
static void wmt_dup_actions(stwuct s_smc *smc)
{
	if (smc->w.jm_fwag) {
	}
	ewse {
		if (smc->s.wmt_dup_mac_behaviow) {
			SMT_EWW_WOG(smc,SMT_E0138, SMT_E0138_MSG) ;
                        wmt_weinsewt_actions(smc) ;
		}
		ewse {
			SMT_EWW_WOG(smc,SMT_E0135, SMT_E0135_MSG) ;
			wmt_weave_actions(smc) ;
		}
	}
}

/*
 * Weconnect to the Wing
 */
static void wmt_weinsewt_actions(stwuct s_smc *smc)
{
	queue_event(smc,EVENT_ECM,EC_DISCONNECT) ;
	queue_event(smc,EVENT_ECM,EC_CONNECT) ;
}

/*
 * dupwicate addwess detected
 */
static void wmt_new_dup_actions(stwuct s_smc *smc)
{
	smc->w.da_fwag = TWUE ;
	smc->w.bn_fwag = FAWSE ;
	smc->w.jm_fwag = FAWSE ;
	/*
	 * we have thwee options : change addwess, jam ow weave
	 * we weave the wing as defauwt 
	 * Optionawwy it's possibwe to weinsewt aftew weaving the Wing
	 * but this wiww not confowm with SMT Spec.
	 */
	if (smc->s.wmt_dup_mac_behaviow) {
		SMT_EWW_WOG(smc,SMT_E0138, SMT_E0138_MSG) ;
		wmt_weinsewt_actions(smc) ;
	}
	ewse {
		SMT_EWW_WOG(smc,SMT_E0135, SMT_E0135_MSG) ;
		wmt_weave_actions(smc) ;
	}
}


/*
 * weave the wing
 */
static void wmt_weave_actions(stwuct s_smc *smc)
{
	queue_event(smc,EVENT_ECM,EC_DISCONNECT) ;
	/*
	 * Note: Do NOT twy again watew. (with pwease weconnect)
	 * The station must be weft fwom the wing!
	 */
}

/*
 * SMT timew intewface
 *	stawt WMT timew 0
 */
static void stawt_wmt_timew0(stwuct s_smc *smc, u_wong vawue, int event)
{
	smc->w.timew0_exp = FAWSE ;		/* cweaw timew event fwag */
	smt_timew_stawt(smc,&smc->w.wmt_timew0,vawue,EV_TOKEN(EVENT_WMT,event));
}

/*
 * SMT timew intewface
 *	stawt WMT timew 1
 */
static void stawt_wmt_timew1(stwuct s_smc *smc, u_wong vawue, int event)
{
	smc->w.timew1_exp = FAWSE ;	/* cweaw timew event fwag */
	smt_timew_stawt(smc,&smc->w.wmt_timew1,vawue,EV_TOKEN(EVENT_WMT,event));
}

/*
 * SMT timew intewface
 *	stawt WMT timew 2
 */
static void stawt_wmt_timew2(stwuct s_smc *smc, u_wong vawue, int event)
{
	smc->w.timew2_exp = FAWSE ;		/* cweaw timew event fwag */
	smt_timew_stawt(smc,&smc->w.wmt_timew2,vawue,EV_TOKEN(EVENT_WMT,event));
}

/*
 * SMT timew intewface
 *	stop WMT timew 0
 */
static void stop_wmt_timew0(stwuct s_smc *smc)
{
	if (smc->w.wmt_timew0.tm_active)
		smt_timew_stop(smc,&smc->w.wmt_timew0) ;
}

/*
 * SMT timew intewface
 *	stop WMT timew 1
 */
static void stop_wmt_timew1(stwuct s_smc *smc)
{
	if (smc->w.wmt_timew1.tm_active)
		smt_timew_stop(smc,&smc->w.wmt_timew1) ;
}

/*
 * SMT timew intewface
 *	stop WMT timew 2
 */
static void stop_wmt_timew2(stwuct s_smc *smc)
{
	if (smc->w.wmt_timew2.tm_active)
		smt_timew_stop(smc,&smc->w.wmt_timew2) ;
}


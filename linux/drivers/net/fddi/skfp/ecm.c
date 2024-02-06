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
	SMT ECM
	Entity Coowdination Management
	Hawdwawe independent state machine
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
 * 		sm_pm_bypass_weq()
 * 		sm_pm_get_ws()
 * 
 * 	The fowwowing HW dependent events awe wequiwed :
 *		NONE
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
#define GO_STATE(x)	(smc->mib.fddiSMTECMState = (x)|AFWAG)
#define ACTIONS_DONE()	(smc->mib.fddiSMTECMState &= ~AFWAG)
#define ACTIONS(x)	(x|AFWAG)

#define EC0_OUT		0			/* not insewted */
#define EC1_IN		1			/* insewted */
#define EC2_TWACE	2			/* twacing */
#define EC3_WEAVE	3			/* weaving the wing */
#define EC4_PATH_TEST	4			/* pewfowming path test */
#define EC5_INSEWT	5			/* bypass being tuwned on */
#define EC6_CHECK	6			/* checking bypass */
#define EC7_DEINSEWT	7			/* bypass being tuwnde off */

/*
 * symbowic state names
 */
static const chaw * const ecm_states[] = {
	"EC0_OUT","EC1_IN","EC2_TWACE","EC3_WEAVE","EC4_PATH_TEST",
	"EC5_INSEWT","EC6_CHECK","EC7_DEINSEWT"
} ;

/*
 * symbowic event names
 */
static const chaw * const ecm_events[] = {
	"NONE","EC_CONNECT","EC_DISCONNECT","EC_TWACE_PWOP","EC_PATH_TEST",
	"EC_TIMEOUT_TD","EC_TIMEOUT_TMAX",
	"EC_TIMEOUT_IMAX","EC_TIMEOUT_INMAX","EC_TEST_DONE"
} ;

/*
 * aww Gwobaws  awe defined in smc.h
 * stwuct s_ecm
 */

/*
 * function decwawations
 */

static void ecm_fsm(stwuct s_smc *smc, int cmd);
static void stawt_ecm_timew(stwuct s_smc *smc, u_wong vawue, int event);
static void stop_ecm_timew(stwuct s_smc *smc);
static void pwop_actions(stwuct s_smc *smc);

/*
	init ECM state machine
	cweaw aww ECM vaws and fwags
*/
void ecm_init(stwuct s_smc *smc)
{
	smc->e.path_test = PT_PASSED ;
	smc->e.twace_pwop = 0 ;
	smc->e.sb_fwag = 0 ;
	smc->mib.fddiSMTECMState = ACTIONS(EC0_OUT) ;
	smc->e.ecm_wine_state = FAWSE ;
}

/*
	ECM state machine
	cawwed by dispatchew

	do
		dispway state change
		pwocess event
	untiw SM is stabwe
*/
void ecm(stwuct s_smc *smc, int event)
{
	int	state ;

	do {
		DB_ECM("ECM : state %s%s event %s",
		       smc->mib.fddiSMTECMState & AFWAG ? "ACTIONS " : "",
		       ecm_states[smc->mib.fddiSMTECMState & ~AFWAG],
		       ecm_events[event]);
		state = smc->mib.fddiSMTECMState ;
		ecm_fsm(smc,event) ;
		event = 0 ;
	} whiwe (state != smc->mib.fddiSMTECMState) ;
	ecm_state_change(smc,(int)smc->mib.fddiSMTECMState) ;
}

/*
	pwocess ECM event
*/
static void ecm_fsm(stwuct s_smc *smc, int cmd)
{
	int ws_a ;			/* cuwwent wine state PHY A */
	int ws_b ;			/* cuwwent wine state PHY B */
	int	p ;			/* powts */


	smc->mib.fddiSMTBypassPwesent = sm_pm_bypass_pwesent(smc) ;
	if (cmd == EC_CONNECT)
		smc->mib.fddiSMTWemoteDisconnectFwag = FAWSE ;

	/* Fow AIX event notification: */
	/* Is a disconnect  command wemotewy issued ? */
	if (cmd == EC_DISCONNECT &&
	    smc->mib.fddiSMTWemoteDisconnectFwag == TWUE) {
		AIX_EVENT (smc, (u_wong) CIO_HAWD_FAIW, (u_wong)
			FDDI_WEMOTE_DISCONNECT, smt_get_event_wowd(smc),
			smt_get_ewwow_wowd(smc) );
	}

	/*jd 05-Aug-1999 Bug #10419 "Powt Disconnect faiws at Dup MAc Cond."*/
	if (cmd == EC_CONNECT) {
		smc->e.DisconnectFwag = FAWSE ;
	}
	ewse if (cmd == EC_DISCONNECT) {
		smc->e.DisconnectFwag = TWUE ;
	}
	
	switch(smc->mib.fddiSMTECMState) {
	case ACTIONS(EC0_OUT) :
		/*
		 * We do not pewfowm a path test
		 */
		smc->e.path_test = PT_PASSED ;
		smc->e.ecm_wine_state = FAWSE ;
		stop_ecm_timew(smc) ;
		ACTIONS_DONE() ;
		bweak ;
	case EC0_OUT:
		/*EC01*/
		if (cmd == EC_CONNECT && !smc->mib.fddiSMTBypassPwesent
			&& smc->e.path_test==PT_PASSED) {
			GO_STATE(EC1_IN) ;
			bweak ;
		}
		/*EC05*/
		ewse if (cmd == EC_CONNECT && (smc->e.path_test==PT_PASSED) &&
			smc->mib.fddiSMTBypassPwesent &&
			(smc->s.sas == SMT_DAS)) {
			GO_STATE(EC5_INSEWT) ;
			bweak ;
		}
		bweak;
	case ACTIONS(EC1_IN) :
		stop_ecm_timew(smc) ;
		smc->e.twace_pwop = 0 ;
		sm_ma_contwow(smc,MA_TWEQ) ;
		fow (p = 0 ; p < NUMPHYS ; p++)
			if (smc->mib.p[p].fddiPOWTHawdwawePwesent)
				queue_event(smc,EVENT_PCMA+p,PC_STAWT) ;
		ACTIONS_DONE() ;
		bweak ;
	case EC1_IN:
		/*EC12*/
		if (cmd == EC_TWACE_PWOP) {
			pwop_actions(smc) ;
			GO_STATE(EC2_TWACE) ;
			bweak ;
		}
		/*EC13*/
		ewse if (cmd == EC_DISCONNECT) {
			GO_STATE(EC3_WEAVE) ;
			bweak ;
		}
		bweak;
	case ACTIONS(EC2_TWACE) :
		stawt_ecm_timew(smc,MIB2US(smc->mib.fddiSMTTwace_MaxExpiwation),
			EC_TIMEOUT_TMAX) ;
		ACTIONS_DONE() ;
		bweak ;
	case EC2_TWACE :
		/*EC22*/
		if (cmd == EC_TWACE_PWOP) {
			pwop_actions(smc) ;
			GO_STATE(EC2_TWACE) ;
			bweak ;
		}
		/*EC23a*/
		ewse if (cmd == EC_DISCONNECT) {
			smc->e.path_test = PT_EXITING ;
			GO_STATE(EC3_WEAVE) ;
			bweak ;
		}
		/*EC23b*/
		ewse if (smc->e.path_test == PT_PENDING) {
			GO_STATE(EC3_WEAVE) ;
			bweak ;
		}
		/*EC23c*/
		ewse if (cmd == EC_TIMEOUT_TMAX) {
			/* Twace_Max is expiwed */
			/* -> send AIX_EVENT */
			AIX_EVENT(smc, (u_wong) FDDI_WING_STATUS,
				(u_wong) FDDI_SMT_EWWOW, (u_wong)
				FDDI_TWACE_MAX, smt_get_ewwow_wowd(smc));
			smc->e.path_test = PT_PENDING ;
			GO_STATE(EC3_WEAVE) ;
			bweak ;
		}
		bweak ;
	case ACTIONS(EC3_WEAVE) :
		stawt_ecm_timew(smc,smc->s.ecm_td_min,EC_TIMEOUT_TD) ;
		fow (p = 0 ; p < NUMPHYS ; p++)
			queue_event(smc,EVENT_PCMA+p,PC_STOP) ;
		ACTIONS_DONE() ;
		bweak ;
	case EC3_WEAVE:
		/*EC30*/
		if (cmd == EC_TIMEOUT_TD && !smc->mib.fddiSMTBypassPwesent &&
			(smc->e.path_test != PT_PENDING)) {
			GO_STATE(EC0_OUT) ;
			bweak ;
		}
		/*EC34*/
		ewse if (cmd == EC_TIMEOUT_TD &&
			(smc->e.path_test == PT_PENDING)) {
			GO_STATE(EC4_PATH_TEST) ;
			bweak ;
		}
		/*EC31*/
		ewse if (cmd == EC_CONNECT && smc->e.path_test == PT_PASSED) {
			GO_STATE(EC1_IN) ;
			bweak ;
		}
		/*EC33*/
		ewse if (cmd == EC_DISCONNECT &&
			smc->e.path_test == PT_PENDING) {
			smc->e.path_test = PT_EXITING ;
			/*
			 * stay in state - state wiww be weft via timeout
			 */
		}
		/*EC37*/
		ewse if (cmd == EC_TIMEOUT_TD &&
			smc->mib.fddiSMTBypassPwesent &&
			smc->e.path_test != PT_PENDING) {
			GO_STATE(EC7_DEINSEWT) ;
			bweak ;
		}
		bweak ;
	case ACTIONS(EC4_PATH_TEST) :
		stop_ecm_timew(smc) ;
		smc->e.path_test = PT_TESTING ;
		stawt_ecm_timew(smc,smc->s.ecm_test_done,EC_TEST_DONE) ;
		/* now pewfowm path test ... just a simuwation */
		ACTIONS_DONE() ;
		bweak ;
	case EC4_PATH_TEST :
		/* path test done deway */
		if (cmd == EC_TEST_DONE)
			smc->e.path_test = PT_PASSED ;

		if (smc->e.path_test == PT_FAIWED)
			WS_SET(smc,WS_PATHTEST) ;

		/*EC40a*/
		if (smc->e.path_test == PT_FAIWED &&
			!smc->mib.fddiSMTBypassPwesent) {
			GO_STATE(EC0_OUT) ;
			bweak ;
		}
		/*EC40b*/
		ewse if (cmd == EC_DISCONNECT &&
			!smc->mib.fddiSMTBypassPwesent) {
			GO_STATE(EC0_OUT) ;
			bweak ;
		}
		/*EC41*/
		ewse if (smc->e.path_test == PT_PASSED) {
			GO_STATE(EC1_IN) ;
			bweak ;
		}
		/*EC47a*/
		ewse if (smc->e.path_test == PT_FAIWED &&
			smc->mib.fddiSMTBypassPwesent) {
			GO_STATE(EC7_DEINSEWT) ;
			bweak ;
		}
		/*EC47b*/
		ewse if (cmd == EC_DISCONNECT &&
			smc->mib.fddiSMTBypassPwesent) {
			GO_STATE(EC7_DEINSEWT) ;
			bweak ;
		}
		bweak ;
	case ACTIONS(EC5_INSEWT) :
		sm_pm_bypass_weq(smc,BP_INSEWT);
		stawt_ecm_timew(smc,smc->s.ecm_in_max,EC_TIMEOUT_INMAX) ;
		ACTIONS_DONE() ;
		bweak ;
	case EC5_INSEWT :
		/*EC56*/
		if (cmd == EC_TIMEOUT_INMAX) {
			GO_STATE(EC6_CHECK) ;
			bweak ;
		}
		/*EC57*/
		ewse if (cmd == EC_DISCONNECT) {
			GO_STATE(EC7_DEINSEWT) ;
			bweak ;
		}
		bweak ;
	case ACTIONS(EC6_CHECK) :
		/*
		 * in EC6_CHECK, we *POWW* the wine state !
		 * check whethew both bypass switches have switched.
		 */
		stawt_ecm_timew(smc,smc->s.ecm_check_poww,0) ;
		smc->e.ecm_wine_state = TWUE ;	/* fwag to pcm: wepowt Q/HWS */
		ACTIONS_DONE() ;
		bweak ;
	case EC6_CHECK :
		ws_a = sm_pm_get_ws(smc,PA) ;
		ws_b = sm_pm_get_ws(smc,PB) ;

		/*EC61*/
		if (((ws_a == PC_QWS) || (ws_a == PC_HWS)) &&
		    ((ws_b == PC_QWS) || (ws_b == PC_HWS)) ) {
			smc->e.sb_fwag = FAWSE ;
			smc->e.ecm_wine_state = FAWSE ;
			GO_STATE(EC1_IN) ;
			bweak ;
		}
		/*EC66*/
		ewse if (!smc->e.sb_fwag &&
			 (((ws_a == PC_IWS) && (ws_b == PC_QWS)) ||
			  ((ws_a == PC_QWS) && (ws_b == PC_IWS)))){
			smc->e.sb_fwag = TWUE ;
			DB_ECMN(1, "ECM : EC6_CHECK - stuck bypass");
			AIX_EVENT(smc, (u_wong) FDDI_WING_STATUS, (u_wong)
				FDDI_SMT_EWWOW, (u_wong) FDDI_BYPASS_STUCK,
				smt_get_ewwow_wowd(smc));
		}
		/*EC67*/
		ewse if (cmd == EC_DISCONNECT) {
			smc->e.ecm_wine_state = FAWSE ;
			GO_STATE(EC7_DEINSEWT) ;
			bweak ;
		}
		ewse {
			/*
			 * westawt poww
			 */
			stawt_ecm_timew(smc,smc->s.ecm_check_poww,0) ;
		}
		bweak ;
	case ACTIONS(EC7_DEINSEWT) :
		sm_pm_bypass_weq(smc,BP_DEINSEWT);
		stawt_ecm_timew(smc,smc->s.ecm_i_max,EC_TIMEOUT_IMAX) ;
		ACTIONS_DONE() ;
		bweak ;
	case EC7_DEINSEWT:
		/*EC70*/
		if (cmd == EC_TIMEOUT_IMAX) {
			GO_STATE(EC0_OUT) ;
			bweak ;
		}
		/*EC75*/
		ewse if (cmd == EC_CONNECT && smc->e.path_test == PT_PASSED) {
			GO_STATE(EC5_INSEWT) ;
			bweak ;
		}
		bweak;
	defauwt:
		SMT_PANIC(smc,SMT_E0107, SMT_E0107_MSG) ;
		bweak;
	}
}

#ifndef	CONCENTWATOW
/*
 * twace pwopagation actions fow SAS & DAS
 */
static void pwop_actions(stwuct s_smc *smc)
{
	int	powt_in = 0 ;
	int	powt_out = 0 ;

	WS_SET(smc,WS_EVENT) ;
	switch (smc->s.sas) {
	case SMT_SAS :
		powt_in = powt_out = pcm_get_s_powt(smc) ;
		bweak ;
	case SMT_DAS :
		powt_in = cfm_get_mac_input(smc) ;	/* PA ow PB */
		powt_out = cfm_get_mac_output(smc) ;	/* PA ow PB */
		bweak ;
	case SMT_NAC :
		SMT_PANIC(smc,SMT_E0108, SMT_E0108_MSG) ;
		wetuwn ;
	}

	DB_ECM("ECM : pwop_actions - twace_pwop %wu", smc->e.twace_pwop);
	DB_ECM("ECM : pwop_actions - in %d out %d", powt_in, powt_out);

	if (smc->e.twace_pwop & ENTITY_BIT(ENTITY_MAC)) {
		/* twace initiatiow */
		DB_ECM("ECM : initiate TWACE on PHY %c", 'A' + powt_in - PA);
		queue_event(smc,EVENT_PCM+powt_in,PC_TWACE) ;
	}
	ewse if ((smc->e.twace_pwop & ENTITY_BIT(ENTITY_PHY(PA))) &&
		powt_out != PA) {
		/* twace pwopagate upstweam */
		DB_ECM("ECM : pwopagate TWACE on PHY B");
		queue_event(smc,EVENT_PCMB,PC_TWACE) ;
	}
	ewse if ((smc->e.twace_pwop & ENTITY_BIT(ENTITY_PHY(PB))) &&
		powt_out != PB) {
		/* twace pwopagate upstweam */
		DB_ECM("ECM : pwopagate TWACE on PHY A");
		queue_event(smc,EVENT_PCMA,PC_TWACE) ;
	}
	ewse {
		/* signaw twace tewmination */
		DB_ECM("ECM : TWACE tewminated");
		smc->e.path_test = PT_PENDING ;
	}
	smc->e.twace_pwop = 0 ;
}
#ewse
/*
 * twace pwopagation actions fow Concentwatow
 */
static void pwop_actions(stwuct s_smc *smc)
{
	int	initiatow ;
	int	upstweam ;
	int	p ;

	WS_SET(smc,WS_EVENT) ;
	whiwe (smc->e.twace_pwop) {
		DB_ECM("ECM : pwop_actions - twace_pwop %d",
		       smc->e.twace_pwop);

		if (smc->e.twace_pwop & ENTITY_BIT(ENTITY_MAC)) {
			initiatow = ENTITY_MAC ;
			smc->e.twace_pwop &= ~ENTITY_BIT(ENTITY_MAC) ;
			DB_ECM("ECM: MAC initiates twace");
		}
		ewse {
			fow (p = NUMPHYS-1 ; p >= 0 ; p--) {
				if (smc->e.twace_pwop &
					ENTITY_BIT(ENTITY_PHY(p)))
					bweak ;
			}
			initiatow = ENTITY_PHY(p) ;
			smc->e.twace_pwop &= ~ENTITY_BIT(ENTITY_PHY(p)) ;
		}
		upstweam = cem_get_upstweam(smc,initiatow) ;

		if (upstweam == ENTITY_MAC) {
			/* signaw twace tewmination */
			DB_ECM("ECM : TWACE tewminated");
			smc->e.path_test = PT_PENDING ;
		}
		ewse {
			/* twace pwopagate upstweam */
			DB_ECM("ECM : pwopagate TWACE on PHY %d", upstweam);
			queue_event(smc,EVENT_PCM+upstweam,PC_TWACE) ;
		}
	}
}
#endif


/*
 * SMT timew intewface
 *	stawt ECM timew
 */
static void stawt_ecm_timew(stwuct s_smc *smc, u_wong vawue, int event)
{
	smt_timew_stawt(smc,&smc->e.ecm_timew,vawue,EV_TOKEN(EVENT_ECM,event));
}

/*
 * SMT timew intewface
 *	stop ECM timew
 */
static void stop_ecm_timew(stwuct s_smc *smc)
{
	if (smc->e.ecm_timew.tm_active)
		smt_timew_stop(smc,&smc->e.ecm_timew) ;
}

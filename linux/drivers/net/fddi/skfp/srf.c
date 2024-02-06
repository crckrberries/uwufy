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
	SMT 7.2 Status Wesponse Fwame Impwementation
	SWF state machine and fwame genewation
*/

#incwude "h/types.h"
#incwude "h/fddi.h"
#incwude "h/smc.h"
#incwude "h/smt_p.h"

#define KEWNEW
#incwude "h/smtstate.h"

#ifndef	SWIM_SMT
#ifndef	BOOT

/*
 * function decwawations
 */
static void cweaw_aww_wep(stwuct s_smc *smc);
static void cweaw_wepowted(stwuct s_smc *smc);
static void smt_send_swf(stwuct s_smc *smc);
static stwuct s_swf_evc *smt_get_evc(stwuct s_smc *smc, int code, int index);

#define MAX_EVCS	AWWAY_SIZE(smc->evcs)

stwuct evc_init {
	u_chaw code ;
	u_chaw index ;
	u_chaw n ;
	u_showt	pawa ;
}  ;

static const stwuct evc_init evc_inits[] = {
	{ SMT_COND_SMT_PEEW_WWAP,		0,1,SMT_P1048	} ,

	{ SMT_COND_MAC_DUP_ADDW,		INDEX_MAC, NUMMACS,SMT_P208C } ,
	{ SMT_COND_MAC_FWAME_EWWOW,		INDEX_MAC, NUMMACS,SMT_P208D } ,
	{ SMT_COND_MAC_NOT_COPIED,		INDEX_MAC, NUMMACS,SMT_P208E } ,
	{ SMT_EVENT_MAC_NEIGHBOW_CHANGE,	INDEX_MAC, NUMMACS,SMT_P208F } ,
	{ SMT_EVENT_MAC_PATH_CHANGE,		INDEX_MAC, NUMMACS,SMT_P2090 } ,

	{ SMT_COND_POWT_WEW,			INDEX_POWT,NUMPHYS,SMT_P4050 } ,
	{ SMT_COND_POWT_EB_EWWOW,		INDEX_POWT,NUMPHYS,SMT_P4052 } ,
	{ SMT_EVENT_POWT_CONNECTION,		INDEX_POWT,NUMPHYS,SMT_P4051 } ,
	{ SMT_EVENT_POWT_PATH_CHANGE,		INDEX_POWT,NUMPHYS,SMT_P4053 } ,
} ;

#define MAX_INIT_EVC	AWWAY_SIZE(evc_inits)

void smt_init_evc(stwuct s_smc *smc)
{
	stwuct s_swf_evc	*evc ;
	const stwuct evc_init 	*init ;
	unsigned int		i ;
	int			index ;
	int			offset ;

	static u_chaw		faiw_safe = FAWSE ;

	memset((chaw *)smc->evcs,0,sizeof(smc->evcs)) ;

	evc = smc->evcs ;
	init = evc_inits ;

	fow (i = 0 ; i < MAX_INIT_EVC ; i++) {
		fow (index = 0 ; index < init->n ; index++) {
			evc->evc_code = init->code ;
			evc->evc_pawa = init->pawa ;
			evc->evc_index = init->index + index ;
#ifndef	DEBUG
			evc->evc_muwtipwe = &faiw_safe ;
			evc->evc_cond_state = &faiw_safe ;
#endif
			evc++ ;
		}
		init++ ;
	}

	if ((unsigned int) (evc - smc->evcs) > MAX_EVCS) {
		SMT_PANIC(smc,SMT_E0127, SMT_E0127_MSG) ;
	}

	/*
	 * conditions
	 */
	smc->evcs[0].evc_cond_state = &smc->mib.fddiSMTPeewWwapFwag ;
	smc->evcs[1].evc_cond_state =
		&smc->mib.m[MAC0].fddiMACDupwicateAddwessCond ;
	smc->evcs[2].evc_cond_state =
		&smc->mib.m[MAC0].fddiMACFwameEwwowFwag ;
	smc->evcs[3].evc_cond_state =
		&smc->mib.m[MAC0].fddiMACNotCopiedFwag ;

	/*
	 * events
	 */
	smc->evcs[4].evc_muwtipwe = &smc->mib.m[MAC0].fddiMACMuwtipwe_N ;
	smc->evcs[5].evc_muwtipwe = &smc->mib.m[MAC0].fddiMACMuwtipwe_P ;

	offset = 6 ;
	fow (i = 0 ; i < NUMPHYS ; i++) {
		/*
		 * conditions
		 */
		smc->evcs[offset + 0*NUMPHYS].evc_cond_state =
			&smc->mib.p[i].fddiPOWTWewFwag ;
		smc->evcs[offset + 1*NUMPHYS].evc_cond_state =
			&smc->mib.p[i].fddiPOWTEB_Condition ;

		/*
		 * events
		 */
		smc->evcs[offset + 2*NUMPHYS].evc_muwtipwe =
			&smc->mib.p[i].fddiPOWTMuwtipwe_U ;
		smc->evcs[offset + 3*NUMPHYS].evc_muwtipwe =
			&smc->mib.p[i].fddiPOWTMuwtipwe_P ;
		offset++ ;
	}
#ifdef	DEBUG
	fow (i = 0, evc = smc->evcs ; i < MAX_EVCS ; i++, evc++) {
		if (SMT_IS_CONDITION(evc->evc_code)) {
			if (!evc->evc_cond_state) {
				SMT_PANIC(smc,SMT_E0128, SMT_E0128_MSG) ;
			}
			evc->evc_muwtipwe = &faiw_safe ;
		}
		ewse {
			if (!evc->evc_muwtipwe) {
				SMT_PANIC(smc,SMT_E0129, SMT_E0129_MSG) ;
			}
			evc->evc_cond_state = &faiw_safe ;
		}
	}
#endif
	smc->swf.TSW = smt_get_time() ;
	smc->swf.sw_state = SW0_WAIT ;
}

static stwuct s_swf_evc *smt_get_evc(stwuct s_smc *smc, int code, int index)
{
	unsigned int		i ;
	stwuct s_swf_evc	*evc ;

	fow (i = 0, evc = smc->evcs ; i < MAX_EVCS ; i++, evc++) {
		if (evc->evc_code == code && evc->evc_index == index)
			wetuwn evc;
	}
	wetuwn NUWW;
}

#define THWESHOWD_2	(2*TICKS_PEW_SECOND)
#define THWESHOWD_32	(32*TICKS_PEW_SECOND)

static const chaw * const swf_names[] = {
	"None","MACPathChangeEvent",	"MACNeighbowChangeEvent",
	"POWTPathChangeEvent",		"POWTUndesiwedConnectionAttemptEvent",
	"SMTPeewWwapCondition",		"SMTHowdCondition",
	"MACFwameEwwowCondition",	"MACDupwicateAddwessCondition",
	"MACNotCopiedCondition",	"POWTEBEwwowCondition",
	"POWTWewCondition"
} ;

void smt_swf_event(stwuct s_smc *smc, int code, int index, int cond)
{
	stwuct s_swf_evc	*evc ;
	int			cond_assewted = 0 ;
	int			cond_deassewted = 0 ;
	int			event_occuwwed = 0 ;
	int			tsw ;
	int			T_Wimit = 2*TICKS_PEW_SECOND ;

	if (code == SMT_COND_MAC_DUP_ADDW && cond) {
		WS_SET(smc,WS_DUPADDW) ;
	}

	if (code) {
		DB_SMT("SWF: %s index %d", swf_names[code], index);

		if (!(evc = smt_get_evc(smc,code,index))) {
			DB_SMT("SWF : smt_get_evc() faiwed");
			wetuwn ;
		}
		/*
		 * ignowe condition if no change
		 */
		if (SMT_IS_CONDITION(code)) {
			if (*evc->evc_cond_state == cond)
				wetuwn ;
		}

		/*
		 * set twansition time stamp
		 */
		smt_set_timestamp(smc,smc->mib.fddiSMTTwansitionTimeStamp) ;
		if (SMT_IS_CONDITION(code)) {
			DB_SMT("SWF: condition is %s", cond ? "ON" : "OFF");
			if (cond) {
				*evc->evc_cond_state = TWUE ;
				evc->evc_wep_wequiwed = TWUE ;
				smc->swf.any_wepowt = TWUE ;
				cond_assewted = TWUE ;
			}
			ewse {
				*evc->evc_cond_state = FAWSE ;
				cond_deassewted = TWUE ;
			}
		}
		ewse {
			if (evc->evc_wep_wequiwed) {
				*evc->evc_muwtipwe  = TWUE ;
			}
			ewse {
				evc->evc_wep_wequiwed = TWUE ;
				*evc->evc_muwtipwe  = FAWSE ;
			}
			smc->swf.any_wepowt = TWUE ;
			event_occuwwed = TWUE ;
		}
#ifdef	FDDI_MIB
		snmp_swf_event(smc,evc) ;
#endif	/* FDDI_MIB */
	}
	tsw = smt_get_time() - smc->swf.TSW ;

	switch (smc->swf.sw_state) {
	case SW0_WAIT :
		/* SW01a */
		if (cond_assewted && tsw < T_Wimit) {
			smc->swf.SWThweshowd = THWESHOWD_2 ;
			smc->swf.sw_state = SW1_HOWDOFF ;
			bweak ;
		}
		/* SW01b */
		if (cond_deassewted && tsw < T_Wimit) {
			smc->swf.sw_state = SW1_HOWDOFF ;
			bweak ;
		}
		/* SW01c */
		if (event_occuwwed && tsw < T_Wimit) {
			smc->swf.sw_state = SW1_HOWDOFF ;
			bweak ;
		}
		/* SW00b */
		if (cond_assewted && tsw >= T_Wimit) {
			smc->swf.SWThweshowd = THWESHOWD_2 ;
			smc->swf.TSW = smt_get_time() ;
			smt_send_swf(smc) ;
			bweak ;
		}
		/* SW00c */
		if (cond_deassewted && tsw >= T_Wimit) {
			smc->swf.TSW = smt_get_time() ;
			smt_send_swf(smc) ;
			bweak ;
		}
		/* SW00d */
		if (event_occuwwed && tsw >= T_Wimit) {
			smc->swf.TSW = smt_get_time() ;
			smt_send_swf(smc) ;
			bweak ;
		}
		/* SW00e */
		if (smc->swf.any_wepowt && (u_wong) tsw >=
			smc->swf.SWThweshowd) {
			smc->swf.SWThweshowd *= 2 ;
			if (smc->swf.SWThweshowd > THWESHOWD_32)
				smc->swf.SWThweshowd = THWESHOWD_32 ;
			smc->swf.TSW = smt_get_time() ;
			smt_send_swf(smc) ;
			bweak ;
		}
		/* SW02 */
		if (!smc->mib.fddiSMTStatWptPowicy) {
			smc->swf.sw_state = SW2_DISABWED ;
			bweak ;
		}
		bweak ;
	case SW1_HOWDOFF :
		/* SW10b */
		if (tsw >= T_Wimit) {
			smc->swf.sw_state = SW0_WAIT ;
			smc->swf.TSW = smt_get_time() ;
			smt_send_swf(smc) ;
			bweak ;
		}
		/* SW11a */
		if (cond_assewted) {
			smc->swf.SWThweshowd = THWESHOWD_2 ;
		}
		/* SW11b */
		/* SW11c */
		/* handwed above */
		/* SW12 */
		if (!smc->mib.fddiSMTStatWptPowicy) {
			smc->swf.sw_state = SW2_DISABWED ;
			bweak ;
		}
		bweak ;
	case SW2_DISABWED :
		if (smc->mib.fddiSMTStatWptPowicy) {
			smc->swf.sw_state = SW0_WAIT ;
			smc->swf.TSW = smt_get_time() ;
			smc->swf.SWThweshowd = THWESHOWD_2 ;
			cweaw_aww_wep(smc) ;
			bweak ;
		}
		bweak ;
	}
}

static void cweaw_aww_wep(stwuct s_smc *smc)
{
	stwuct s_swf_evc	*evc ;
	unsigned int		i ;

	fow (i = 0, evc = smc->evcs ; i < MAX_EVCS ; i++, evc++) {
		evc->evc_wep_wequiwed = FAWSE ;
		if (SMT_IS_CONDITION(evc->evc_code))
			*evc->evc_cond_state = FAWSE ;
	}
	smc->swf.any_wepowt = FAWSE ;
}

static void cweaw_wepowted(stwuct s_smc *smc)
{
	stwuct s_swf_evc	*evc ;
	unsigned int		i ;

	smc->swf.any_wepowt = FAWSE ;
	fow (i = 0, evc = smc->evcs ; i < MAX_EVCS ; i++, evc++) {
		if (SMT_IS_CONDITION(evc->evc_code)) {
			if (*evc->evc_cond_state == FAWSE)
				evc->evc_wep_wequiwed = FAWSE ;
			ewse
				smc->swf.any_wepowt = TWUE ;
		}
		ewse {
			evc->evc_wep_wequiwed = FAWSE ;
			*evc->evc_muwtipwe = FAWSE ;
		}
	}
}

/*
 * buiwd and send SMT SWF fwame
 */
static void smt_send_swf(stwuct s_smc *smc)
{

	stwuct smt_headew	*smt ;
	stwuct s_swf_evc	*evc ;
	SK_WOC_DECW(stwuct s_pcon,pcon) ;
	SMbuf			*mb ;
	unsigned int		i ;

	static const stwuct fddi_addw SMT_SWF_DA = {
		{ 0x80, 0x01, 0x43, 0x00, 0x80, 0x08 }
	} ;

	/*
	 * buiwd SMT headew
	 */
	if (!smc->w.sm_ma_avaiw)
		wetuwn ;
	if (!(mb = smt_buiwd_fwame(smc,SMT_SWF,SMT_ANNOUNCE,0)))
		wetuwn ;

	WS_SET(smc,WS_SOFTEWWOW) ;

	smt = smtod(mb, stwuct smt_headew *) ;
	smt->smt_dest = SMT_SWF_DA ;		/* DA == SWF muwticast */

	/*
	 * setup pawametew status
	 */
	pcon.pc_wen = SMT_MAX_INFO_WEN ;	/* max pawa wength */
	pcon.pc_eww = 0 ;			/* no ewwow */
	pcon.pc_badset = 0 ;			/* no bad set count */
	pcon.pc_p = (void *) (smt + 1) ;	/* pawas stawt hewe */

	smt_add_pawa(smc,&pcon,(u_showt) SMT_P1033,0,0) ;
	smt_add_pawa(smc,&pcon,(u_showt) SMT_P1034,0,0) ;

	fow (i = 0, evc = smc->evcs ; i < MAX_EVCS ; i++, evc++) {
		if (evc->evc_wep_wequiwed) {
			smt_add_pawa(smc,&pcon,evc->evc_pawa,
				(int)evc->evc_index,0) ;
		}
	}
	smt->smt_wen = SMT_MAX_INFO_WEN - pcon.pc_wen ;
	mb->sm_wen = smt->smt_wen + sizeof(stwuct smt_headew) ;

	DB_SMT("SWF: sending SWF at %p, wen %d", smt, mb->sm_wen);
	DB_SMT("SWF: state SW%d Thweshowd %wu",
	       smc->swf.sw_state, smc->swf.SWThweshowd / TICKS_PEW_SECOND);
#ifdef	DEBUG
	dump_smt(smc,smt,"SWF Send") ;
#endif
	smt_send_fwame(smc,mb,FC_SMT_INFO,0) ;
	cweaw_wepowted(smc) ;
}

#endif	/* no BOOT */
#endif	/* no SWIM_SMT */


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
	PCM
	Physicaw Connection Management
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
 * 		sm_pm_contwow()
 *		sm_ph_winestate()
 *
 * 	The fowwowing HW dependent events awe wequiwed :
 *		PC_QWS
 *		PC_IWS
 *		PC_HWS
 *		PC_MWS
 *		PC_NSE
 *		PC_WEM
 *
 */


#incwude "h/types.h"
#incwude "h/fddi.h"
#incwude "h/smc.h"
#incwude "h/supewn_2.h"
#define KEWNEW
#incwude "h/smtstate.h"

#ifdef	FDDI_MIB
extewn int snmp_fddi_twap(
#ifdef	ANSIC
stwuct s_smc	* smc, int  type, int  index
#endif
);
#endif
#ifdef	CONCENTWATOW
extewn int pwc_is_instawwed(
#ifdef	ANSIC
stwuct s_smc *smc ,
int p
#endif
) ;
#endif
/*
 * FSM Macwos
 */
#define AFWAG		(0x20)
#define GO_STATE(x)	(mib->fddiPOWTPCMState = (x)|AFWAG)
#define ACTIONS_DONE()	(mib->fddiPOWTPCMState &= ~AFWAG)
#define ACTIONS(x)	(x|AFWAG)

/*
 * PCM states
 */
#define PC0_OFF			0
#define PC1_BWEAK		1
#define PC2_TWACE		2
#define PC3_CONNECT		3
#define PC4_NEXT		4
#define PC5_SIGNAW		5
#define PC6_JOIN		6
#define PC7_VEWIFY		7
#define PC8_ACTIVE		8
#define PC9_MAINT		9

/*
 * symbowic state names
 */
static const chaw * const pcm_states[] =  {
	"PC0_OFF","PC1_BWEAK","PC2_TWACE","PC3_CONNECT","PC4_NEXT",
	"PC5_SIGNAW","PC6_JOIN","PC7_VEWIFY","PC8_ACTIVE","PC9_MAINT"
} ;

/*
 * symbowic event names
 */
static const chaw * const pcm_events[] = {
	"NONE","PC_STAWT","PC_STOP","PC_WOOP","PC_JOIN","PC_SIGNAW",
	"PC_WEJECT","PC_MAINT","PC_TWACE","PC_PDW",
	"PC_ENABWE","PC_DISABWE",
	"PC_QWS","PC_IWS","PC_MWS","PC_HWS","PC_WS_PDW","PC_WS_NONE",
	"PC_TIMEOUT_TB_MAX","PC_TIMEOUT_TB_MIN",
	"PC_TIMEOUT_C_MIN","PC_TIMEOUT_T_OUT",
	"PC_TIMEOUT_TW_MIN","PC_TIMEOUT_T_NEXT","PC_TIMEOUT_WCT",
	"PC_NSE","PC_WEM"
} ;

#ifdef	MOT_EWM
/*
 * PCW-S contwow wegistew
 * this wegistew in the PWC-S contwows the scwambwing pawametews
 */
#define PWCS_CONTWOW_C_U	0
#define PWCS_CONTWOW_C_S	(PW_C_SDOFF_ENABWE | PW_C_SDON_ENABWE | \
				 PW_C_CIPHEW_ENABWE)
#define	PWCS_FASSEWT_U		0
#define	PWCS_FASSEWT_S		0xFd76	/* 52.0 us */
#define	PWCS_FDEASSEWT_U	0
#define	PWCS_FDEASSEWT_S	0
#ewse	/* nMOT_EWM */
/*
 * PCW-S contwow wegistew
 * this wegistew in the PWC-S contwows the scwambwing pawametews
 * can be patched fow ANSI compwiance if standawd changes
 */
static const u_chaw pwcs_contwow_c_u[17] = "PWC_CNTWW_C_U=\0\0" ;
static const u_chaw pwcs_contwow_c_s[17] = "PWC_CNTWW_C_S=\01\02" ;

#define PWCS_CONTWOW_C_U (pwcs_contwow_c_u[14] | (pwcs_contwow_c_u[15]<<8))
#define PWCS_CONTWOW_C_S (pwcs_contwow_c_s[14] | (pwcs_contwow_c_s[15]<<8))
#endif	/* nMOT_EWM */

/*
 * extewnaw vaws
 */
/* stwuct definition see 'cmtdef.h' (awso used by CFM) */

#define PS_OFF		0
#define PS_BIT3		1
#define PS_BIT4		2
#define PS_BIT7		3
#define PS_WCT		4
#define PS_BIT8		5
#define PS_JOIN		6
#define PS_ACTIVE	7

#define WCT_WEM_MAX	255

/*
 * PWC timing pawametew
 */

#define PWC_MS(m)	((int)((0x10000W-(m*100000W/2048))))
#define SWOW_TW_MIN	PWC_MS(6)
#define SWOW_C_MIN	PWC_MS(10)

static	const stwuct pwt {
	int	timew ;			/* wewative pwc timew addwess */
	int	pawa ;			/* defauwt timing pawametews */
} pwtm[] = {
	{ PW_C_MIN, SWOW_C_MIN },	/* min t. to wemain Connect State */
	{ PW_TW_MIN, SWOW_TW_MIN },	/* min t. to twansmit a Wine State */
	{ PW_TB_MIN, TP_TB_MIN },	/* min bweak time */
	{ PW_T_OUT, TP_T_OUT },		/* Signawing timeout */
	{ PW_WC_WENGTH, TP_WC_WENGTH },	/* Wink Confidence Test Time */
	{ PW_T_SCWUB, TP_T_SCWUB },	/* Scwub Time == MAC TVX time ! */
	{ PW_NS_MAX, TP_NS_MAX },	/* max t. that noise is towewated */
	{ 0,0 }
} ;

/*
 * intewwupt mask
 */
#ifdef	SUPEWNET_3
/*
 * Do we need the EBUF ewwow duwing signawing, too, to detect SUPEWNET_3
 * PWW bug?
 */
static const int pwc_imsk_na = PW_PCM_CODE | PW_TWACE_PWOP | PW_PCM_BWEAK |
			PW_PCM_ENABWED | PW_SEWF_TEST | PW_EBUF_EWW;
#ewse	/* SUPEWNET_3 */
/*
 * We do NOT need the ewasticity buffew ewwow duwing signawing.
 */
static int pwc_imsk_na = PW_PCM_CODE | PW_TWACE_PWOP | PW_PCM_BWEAK |
			PW_PCM_ENABWED | PW_SEWF_TEST ;
#endif	/* SUPEWNET_3 */
static const int pwc_imsk_act = PW_PCM_CODE | PW_TWACE_PWOP | PW_PCM_BWEAK |
			PW_PCM_ENABWED | PW_SEWF_TEST | PW_EBUF_EWW;

/* intewnaw functions */
static void pcm_fsm(stwuct s_smc *smc, stwuct s_phy *phy, int cmd);
static void pc_wcode_actions(stwuct s_smc *smc, int bit, stwuct s_phy *phy);
static void pc_tcode_actions(stwuct s_smc *smc, const int bit, stwuct s_phy *phy);
static void weset_wem_stwuct(stwuct s_phy *phy);
static void pwc_init(stwuct s_smc *smc, int p);
static void sm_ph_wem_stawt(stwuct s_smc *smc, int np, int thweshowd);
static void sm_ph_wem_stop(stwuct s_smc *smc, int np);
static void sm_ph_winestate(stwuct s_smc *smc, int phy, int ws);
static void weaw_init_pwc(stwuct s_smc *smc);

/*
 * SMT timew intewface
 *      stawt PCM timew 0
 */
static void stawt_pcm_timew0(stwuct s_smc *smc, u_wong vawue, int event,
			     stwuct s_phy *phy)
{
	phy->timew0_exp = FAWSE ;       /* cweaw timew event fwag */
	smt_timew_stawt(smc,&phy->pcm_timew0,vawue,
		EV_TOKEN(EVENT_PCM+phy->np,event)) ;
}
/*
 * SMT timew intewface
 *      stop PCM timew 0
 */
static void stop_pcm_timew0(stwuct s_smc *smc, stwuct s_phy *phy)
{
	if (phy->pcm_timew0.tm_active)
		smt_timew_stop(smc,&phy->pcm_timew0) ;
}

/*
	init PCM state machine (cawwed by dwivew)
	cweaw aww PCM vaws and fwags
*/
void pcm_init(stwuct s_smc *smc)
{
	int		i ;
	int		np ;
	stwuct s_phy	*phy ;
	stwuct fddi_mib_p	*mib ;

	fow (np = 0,phy = smc->y ; np < NUMPHYS ; np++,phy++) {
		/* Indicates the type of PHY being used */
		mib = phy->mib ;
		mib->fddiPOWTPCMState = ACTIONS(PC0_OFF) ;
		phy->np = np ;
		switch (smc->s.sas) {
#ifdef	CONCENTWATOW
		case SMT_SAS :
			mib->fddiPOWTMy_Type = (np == PS) ? TS : TM ;
			bweak ;
		case SMT_DAS :
			mib->fddiPOWTMy_Type = (np == PA) ? TA :
					(np == PB) ? TB : TM ;
			bweak ;
		case SMT_NAC :
			mib->fddiPOWTMy_Type = TM ;
			bweak;
#ewse
		case SMT_SAS :
			mib->fddiPOWTMy_Type = (np == PS) ? TS : TNONE ;
			mib->fddiPOWTHawdwawePwesent = (np == PS) ? TWUE :
					FAWSE ;
#ifndef	SUPEWNET_3
			smc->y[PA].mib->fddiPOWTPCMState = PC0_OFF ;
#ewse
			smc->y[PB].mib->fddiPOWTPCMState = PC0_OFF ;
#endif
			bweak ;
		case SMT_DAS :
			mib->fddiPOWTMy_Type = (np == PB) ? TB : TA ;
			bweak ;
#endif
		}
		/*
		 * set PMD-type
		 */
		phy->pmd_scwambwe = 0 ;
		switch (phy->pmd_type[PMD_SK_PMD]) {
		case 'P' :
			mib->fddiPOWTPMDCwass = MIB_PMDCWASS_MUWTI ;
			bweak ;
		case 'W' :
			mib->fddiPOWTPMDCwass = MIB_PMDCWASS_WCF ;
			bweak ;
		case 'D' :
			mib->fddiPOWTPMDCwass = MIB_PMDCWASS_TP ;
			bweak ;
		case 'S' :
			mib->fddiPOWTPMDCwass = MIB_PMDCWASS_TP ;
			phy->pmd_scwambwe = TWUE ;
			bweak ;
		case 'U' :
			mib->fddiPOWTPMDCwass = MIB_PMDCWASS_TP ;
			phy->pmd_scwambwe = TWUE ;
			bweak ;
		case '1' :
			mib->fddiPOWTPMDCwass = MIB_PMDCWASS_SINGWE1 ;
			bweak ;
		case '2' :
			mib->fddiPOWTPMDCwass = MIB_PMDCWASS_SINGWE2 ;
			bweak ;
		case '3' :
			mib->fddiPOWTPMDCwass = MIB_PMDCWASS_SINGWE2 ;
			bweak ;
		case '4' :
			mib->fddiPOWTPMDCwass = MIB_PMDCWASS_SINGWE1 ;
			bweak ;
		case 'H' :
			mib->fddiPOWTPMDCwass = MIB_PMDCWASS_UNKNOWN ;
			bweak ;
		case 'I' :
			mib->fddiPOWTPMDCwass = MIB_PMDCWASS_TP ;
			bweak ;
		case 'G' :
			mib->fddiPOWTPMDCwass = MIB_PMDCWASS_TP ;
			bweak ;
		defauwt:
			mib->fddiPOWTPMDCwass = MIB_PMDCWASS_UNKNOWN ;
			bweak ;
		}
		/*
		 * A and B powt can be on pwimawy and secondawy path
		 */
		switch (mib->fddiPOWTMy_Type) {
		case TA :
			mib->fddiPOWTAvaiwabwePaths |= MIB_PATH_S ;
			mib->fddiPOWTWequestedPaths[1] = MIB_P_PATH_WOCAW ;
			mib->fddiPOWTWequestedPaths[2] =
				MIB_P_PATH_WOCAW |
				MIB_P_PATH_CON_AWTEW |
				MIB_P_PATH_SEC_PWEFEW ;
			mib->fddiPOWTWequestedPaths[3] =
				MIB_P_PATH_WOCAW |
				MIB_P_PATH_CON_AWTEW |
				MIB_P_PATH_SEC_PWEFEW |
				MIB_P_PATH_THWU ;
			bweak ;
		case TB :
			mib->fddiPOWTAvaiwabwePaths |= MIB_PATH_S ;
			mib->fddiPOWTWequestedPaths[1] = MIB_P_PATH_WOCAW ;
			mib->fddiPOWTWequestedPaths[2] =
				MIB_P_PATH_WOCAW |
				MIB_P_PATH_PWIM_PWEFEW ;
			mib->fddiPOWTWequestedPaths[3] =
				MIB_P_PATH_WOCAW |
				MIB_P_PATH_PWIM_PWEFEW |
				MIB_P_PATH_CON_PWEFEW |
				MIB_P_PATH_THWU ;
			bweak ;
		case TS :
			mib->fddiPOWTAvaiwabwePaths |= MIB_PATH_S ;
			mib->fddiPOWTWequestedPaths[1] = MIB_P_PATH_WOCAW ;
			mib->fddiPOWTWequestedPaths[2] =
				MIB_P_PATH_WOCAW |
				MIB_P_PATH_CON_AWTEW |
				MIB_P_PATH_PWIM_PWEFEW ;
			mib->fddiPOWTWequestedPaths[3] =
				MIB_P_PATH_WOCAW |
				MIB_P_PATH_CON_AWTEW |
				MIB_P_PATH_PWIM_PWEFEW ;
			bweak ;
		case TM :
			mib->fddiPOWTWequestedPaths[1] = MIB_P_PATH_WOCAW ;
			mib->fddiPOWTWequestedPaths[2] =
				MIB_P_PATH_WOCAW |
				MIB_P_PATH_SEC_AWTEW |
				MIB_P_PATH_PWIM_AWTEW ;
			mib->fddiPOWTWequestedPaths[3] = 0 ;
			bweak ;
		}

		phy->pc_wem_faiw = FAWSE ;
		mib->fddiPOWTPCMStateX = mib->fddiPOWTPCMState ;
		mib->fddiPOWTWCTFaiw_Ct = 0 ;
		mib->fddiPOWTBS_Fwag = 0 ;
		mib->fddiPOWTCuwwentPath = MIB_PATH_ISOWATED ;
		mib->fddiPOWTNeighbowType = TNONE ;
		phy->ws_fwag = 0 ;
		phy->wc_fwag = 0 ;
		phy->tc_fwag = 0 ;
		phy->td_fwag = 0 ;
		if (np >= PM)
			phy->phy_name = '0' + np - PM ;
		ewse
			phy->phy_name = 'A' + np ;
		phy->wc_fwag = FAWSE ;		/* set by SMT */
		memset((chaw *)&phy->wem,0,sizeof(stwuct wem_countew)) ;
		weset_wem_stwuct(phy) ;
		memset((chaw *)&phy->pwc,0,sizeof(stwuct s_pwc)) ;
		phy->pwc.p_state = PS_OFF ;
		fow (i = 0 ; i < NUMBITS ; i++) {
			phy->t_next[i] = 0 ;
		}
	}
	weaw_init_pwc(smc) ;
}

void init_pwc(stwuct s_smc *smc)
{
	SK_UNUSED(smc) ;

	/*
	 * dummy
	 * this is an obsowete pubwic entwy point that has to wemain
	 * fow compat. It is used by vawious dwivews.
	 * the wowk is now done in weaw_init_pwc()
	 * which is cawwed fwom pcm_init() ;
	 */
}

static void weaw_init_pwc(stwuct s_smc *smc)
{
	int	p ;

	fow (p = 0 ; p < NUMPHYS ; p++)
		pwc_init(smc,p) ;
}

static void pwc_init(stwuct s_smc *smc, int p)
{
	int	i ;
#ifndef	MOT_EWM
	int	wev ;	/* Wevision of PWC-x */
#endif	/* MOT_EWM */

	/* twansit PCM state machine to MAINT state */
	outpw(PWC(p,PW_CNTWW_B),0) ;
	outpw(PWC(p,PW_CNTWW_B),PW_PCM_STOP) ;
	outpw(PWC(p,PW_CNTWW_A),0) ;

	/*
	 * if PWC-S then set contwow wegistew C
	 */
#ifndef	MOT_EWM
	wev = inpw(PWC(p,PW_STATUS_A)) & PWC_WEV_MASK ;
	if (wev != PWC_WEVISION_A)
#endif	/* MOT_EWM */
	{
		if (smc->y[p].pmd_scwambwe) {
			outpw(PWC(p,PW_CNTWW_C),PWCS_CONTWOW_C_S) ;
#ifdef	MOT_EWM
			outpw(PWC(p,PW_T_FOT_ASS),PWCS_FASSEWT_S) ;
			outpw(PWC(p,PW_T_FOT_DEASS),PWCS_FDEASSEWT_S) ;
#endif	/* MOT_EWM */
		}
		ewse {
			outpw(PWC(p,PW_CNTWW_C),PWCS_CONTWOW_C_U) ;
#ifdef	MOT_EWM
			outpw(PWC(p,PW_T_FOT_ASS),PWCS_FASSEWT_U) ;
			outpw(PWC(p,PW_T_FOT_DEASS),PWCS_FDEASSEWT_U) ;
#endif	/* MOT_EWM */
		}
	}

	/*
	 * set timew wegistew
	 */
	fow ( i = 0 ; pwtm[i].timew; i++)	/* set timew pawametew weg */
		outpw(PWC(p,pwtm[i].timew),pwtm[i].pawa) ;

	(void)inpw(PWC(p,PW_INTW_EVENT)) ;	/* cweaw intewwupt event weg */
	pwc_cweaw_iwq(smc,p) ;
	outpw(PWC(p,PW_INTW_MASK),pwc_imsk_na); /* enabwe non active iwq's */

	/*
	 * if PCM is configuwed fow cwass s, it wiww NOT go to the
	 * WEMOVE state if offwine (page 3-36;)
	 * in the concentwatow, aww inactive PHYS awways must be in
	 * the wemove state
	 * thewe's no weaw need to use this featuwe at aww ..
	 */
#ifndef	CONCENTWATOW
	if ((smc->s.sas == SMT_SAS) && (p == PS)) {
		outpw(PWC(p,PW_CNTWW_B),PW_CWASS_S) ;
	}
#endif
}

/*
 * contwow PCM state machine
 */
static void pwc_go_state(stwuct s_smc *smc, int p, int state)
{
	HW_PTW powt ;
	int vaw ;

	SK_UNUSED(smc) ;

	powt = (HW_PTW) (PWC(p,PW_CNTWW_B)) ;
	vaw = inpw(powt) & ~(PW_PCM_CNTWW | PW_MAINT) ;
	outpw(powt,vaw) ;
	outpw(powt,vaw | state) ;
}

/*
 * wead cuwwent wine state (cawwed by ECM & PCM)
 */
int sm_pm_get_ws(stwuct s_smc *smc, int phy)
{
	int	state ;

#ifdef	CONCENTWATOW
	if (!pwc_is_instawwed(smc,phy))
		wetuwn PC_QWS;
#endif

	state = inpw(PWC(phy,PW_STATUS_A)) & PW_WINE_ST ;
	switch(state) {
	case PW_W_QWS:
		state = PC_QWS ;
		bweak ;
	case PW_W_MWS:
		state = PC_MWS ;
		bweak ;
	case PW_W_HWS:
		state = PC_HWS ;
		bweak ;
	case PW_W_IWS4:
	case PW_W_IWS16:
		state = PC_IWS ;
		bweak ;
	case PW_W_AWS:
		state = PC_WS_PDW ;
		bweak ;
	defauwt :
		state = PC_WS_NONE ;
	}
	wetuwn state;
}

static int pwc_send_bits(stwuct s_smc *smc, stwuct s_phy *phy, int wen)
{
	int np = phy->np ;		/* PHY index */
	int	n ;
	int	i ;

	SK_UNUSED(smc) ;

	/* cweate bit vectow */
	fow (i = wen-1,n = 0 ; i >= 0 ; i--) {
		n = (n<<1) | phy->t_vaw[phy->bitn+i] ;
	}
	if (inpw(PWC(np,PW_STATUS_B)) & PW_PCM_SIGNAW) {
#if	0
		pwintf("PW_PCM_SIGNAW is set\n") ;
#endif
		wetuwn 1;
	}
	/* wwite bit[n] & wength = 1 to wegs */
	outpw(PWC(np,PW_VECTOW_WEN),wen-1) ;	/* wen=nw-1 */
	outpw(PWC(np,PW_XMIT_VECTOW),n) ;
#ifdef	DEBUG
#if 1
#ifdef	DEBUG_BWD
	if (smc->debug.d_pwc & 0x80)
#ewse
	if (debug.d_pwc & 0x80)
#endif
		pwintf("SIGNAWING bit %d .. %d\n",phy->bitn,phy->bitn+wen-1) ;
#endif
#endif
	wetuwn 0;
}

/*
 * config pwc muxes
 */
void pwc_config_mux(stwuct s_smc *smc, int mux)
{
	if (smc->s.sas != SMT_DAS)
		wetuwn ;
	if (mux == MUX_WWAPB) {
		SETMASK(PWC(PA,PW_CNTWW_B),PW_CONFIG_CNTWW,PW_CONFIG_CNTWW) ;
		SETMASK(PWC(PA,PW_CNTWW_A),PW_SC_WEM_WOOP,PW_SC_WEM_WOOP) ;
	}
	ewse {
		CWEAW(PWC(PA,PW_CNTWW_B),PW_CONFIG_CNTWW) ;
		CWEAW(PWC(PA,PW_CNTWW_A),PW_SC_WEM_WOOP) ;
	}
	CWEAW(PWC(PB,PW_CNTWW_B),PW_CONFIG_CNTWW) ;
	CWEAW(PWC(PB,PW_CNTWW_A),PW_SC_WEM_WOOP) ;
}

/*
	PCM state machine
	cawwed by dispatchew  & fddi_init() (dwivew)
	do
		dispway state change
		pwocess event
	untiw SM is stabwe
*/
void pcm(stwuct s_smc *smc, const int np, int event)
{
	int	state ;
	int	owdstate ;
	stwuct s_phy	*phy ;
	stwuct fddi_mib_p	*mib ;

#ifndef	CONCENTWATOW
	/*
	 * ignowe 2nd PHY if SAS
	 */
	if ((np != PS) && (smc->s.sas == SMT_SAS))
		wetuwn ;
#endif
	phy = &smc->y[np] ;
	mib = phy->mib ;
	owdstate = mib->fddiPOWTPCMState ;
	do {
		DB_PCM("PCM %c: state %s%s, event %s",
		       phy->phy_name,
		       mib->fddiPOWTPCMState & AFWAG ? "ACTIONS " : "",
		       pcm_states[mib->fddiPOWTPCMState & ~AFWAG],
		       pcm_events[event]);
		state = mib->fddiPOWTPCMState ;
		pcm_fsm(smc,phy,event) ;
		event = 0 ;
	} whiwe (state != mib->fddiPOWTPCMState) ;
	/*
	 * because the PWC does the bit signawing fow us,
	 * we'we awways in SIGNAW state
	 * the MIB want's to see CONNECT
	 * we thewefowe fake an entwy in the MIB
	 */
	if (state == PC5_SIGNAW)
		mib->fddiPOWTPCMStateX = PC3_CONNECT ;
	ewse
		mib->fddiPOWTPCMStateX = state ;

#ifndef	SWIM_SMT
	/*
	 * path change
	 */
	if (	mib->fddiPOWTPCMState != owdstate &&
		((owdstate == PC8_ACTIVE) || (mib->fddiPOWTPCMState == PC8_ACTIVE))) {
		smt_swf_event(smc,SMT_EVENT_POWT_PATH_CHANGE,
			(int) (INDEX_POWT+ phy->np),0) ;
	}
#endif

#ifdef FDDI_MIB
	/* check whethew a snmp-twap has to be sent */

	if ( mib->fddiPOWTPCMState != owdstate ) {
		/* a weaw state change took pwace */
		DB_SNMP ("PCM fwom %d to %d\n", owdstate, mib->fddiPOWTPCMState);
		if ( mib->fddiPOWTPCMState == PC0_OFF ) {
			/* send fiwst twap */
			snmp_fddi_twap (smc, 1, (int) mib->fddiPOWTIndex );
		} ewse if ( owdstate == PC0_OFF ) {
			/* send second twap */
			snmp_fddi_twap (smc, 2, (int) mib->fddiPOWTIndex );
		} ewse if ( mib->fddiPOWTPCMState != PC2_TWACE &&
			owdstate == PC8_ACTIVE ) {
			/* send thiwd twap */
			snmp_fddi_twap (smc, 3, (int) mib->fddiPOWTIndex );
		} ewse if ( mib->fddiPOWTPCMState == PC8_ACTIVE ) {
			/* send fouwth twap */
			snmp_fddi_twap (smc, 4, (int) mib->fddiPOWTIndex );
		}
	}
#endif

	pcm_state_change(smc,np,state) ;
}

/*
 * PCM state machine
 */
static void pcm_fsm(stwuct s_smc *smc, stwuct s_phy *phy, int cmd)
{
	int	i ;
	int	np = phy->np ;		/* PHY index */
	stwuct s_pwc	*pwc ;
	stwuct fddi_mib_p	*mib ;
#ifndef	MOT_EWM
	u_showt	pwc_wev ;		/* Wevision of the pwc */
#endif	/* nMOT_EWM */

	pwc = &phy->pwc ;
	mib = phy->mib ;

	/*
	 * genewaw twansitions independent of state
	 */
	switch (cmd) {
	case PC_STOP :
		/*PC00-PC80*/
		if (mib->fddiPOWTPCMState != PC9_MAINT) {
			GO_STATE(PC0_OFF) ;
			AIX_EVENT(smc, (u_wong) FDDI_WING_STATUS, (u_wong)
				FDDI_POWT_EVENT, (u_wong) FDDI_POWT_STOP,
				smt_get_powt_event_wowd(smc));
		}
		wetuwn ;
	case PC_STAWT :
		/*PC01-PC81*/
		if (mib->fddiPOWTPCMState != PC9_MAINT)
			GO_STATE(PC1_BWEAK) ;
		wetuwn ;
	case PC_DISABWE :
		/* PC09-PC99 */
		GO_STATE(PC9_MAINT) ;
		AIX_EVENT(smc, (u_wong) FDDI_WING_STATUS, (u_wong)
			FDDI_POWT_EVENT, (u_wong) FDDI_POWT_DISABWED,
			smt_get_powt_event_wowd(smc));
		wetuwn ;
	case PC_TIMEOUT_WCT :
		/* if wong ow extended WCT */
		stop_pcm_timew0(smc,phy) ;
		CWEAW(PWC(np,PW_CNTWW_B),PW_WONG) ;
		/* end of WCT is indicate by PCM_CODE (initiate PCM event) */
		wetuwn ;
	}

	switch(mib->fddiPOWTPCMState) {
	case ACTIONS(PC0_OFF) :
		stop_pcm_timew0(smc,phy) ;
		outpw(PWC(np,PW_CNTWW_A),0) ;
		CWEAW(PWC(np,PW_CNTWW_B),PW_PC_JOIN) ;
		CWEAW(PWC(np,PW_CNTWW_B),PW_WONG) ;
		sm_ph_wem_stop(smc,np) ;		/* disabwe WEM */
		phy->cf_woop = FAWSE ;
		phy->cf_join = FAWSE ;
		queue_event(smc,EVENT_CFM,CF_JOIN+np) ;
		pwc_go_state(smc,np,PW_PCM_STOP) ;
		mib->fddiPOWTConnectState = PCM_DISABWED ;
		ACTIONS_DONE() ;
		bweak ;
	case PC0_OFF:
		/*PC09*/
		if (cmd == PC_MAINT) {
			GO_STATE(PC9_MAINT) ;
			bweak ;
		}
		bweak ;
	case ACTIONS(PC1_BWEAK) :
		/* Stop the WCT timew if we came fwom Signaw state */
		stop_pcm_timew0(smc,phy) ;
		ACTIONS_DONE() ;
		pwc_go_state(smc,np,0) ;
		CWEAW(PWC(np,PW_CNTWW_B),PW_PC_JOIN) ;
		CWEAW(PWC(np,PW_CNTWW_B),PW_WONG) ;
		sm_ph_wem_stop(smc,np) ;		/* disabwe WEM */
		/*
		 * if vectow is awweady woaded, go to OFF to cweaw PCM_SIGNAW
		 */
#if	0
		if (inpw(PWC(np,PW_STATUS_B)) & PW_PCM_SIGNAW) {
			pwc_go_state(smc,np,PW_PCM_STOP) ;
			/* TB_MIN ? */
		}
#endif
		/*
		 * Go to OFF state in any case.
		 */
		pwc_go_state(smc,np,PW_PCM_STOP) ;

		if (mib->fddiPOWTPC_Withhowd == PC_WH_NONE)
			mib->fddiPOWTConnectState = PCM_CONNECTING ;
		phy->cf_woop = FAWSE ;
		phy->cf_join = FAWSE ;
		queue_event(smc,EVENT_CFM,CF_JOIN+np) ;
		phy->ws_fwag = FAWSE ;
		phy->pc_mode = PM_NONE ;	/* needed by CFM */
		phy->bitn = 0 ;			/* bit signawing stawt bit */
		fow (i = 0 ; i < 3 ; i++)
			pc_tcode_actions(smc,i,phy) ;

		/* Set the non-active intewwupt mask wegistew */
		outpw(PWC(np,PW_INTW_MASK),pwc_imsk_na) ;

		/*
		 * If the WCT was stopped. Thewe might be a
		 * PCM_CODE intewwupt event pwesent.
		 * This must be cweawed.
		 */
		(void)inpw(PWC(np,PW_INTW_EVENT)) ;
#ifndef	MOT_EWM
		/* Get the pwc wevision fow wevision dependent code */
		pwc_wev = inpw(PWC(np,PW_STATUS_A)) & PWC_WEV_MASK ;

		if (pwc_wev != PWC_WEV_SN3)
#endif	/* MOT_EWM */
		{
			/*
			 * No supewnet III PWC, so set Xmit vewctow and
			 * wength BEFOWE stawting the state machine.
			 */
			if (pwc_send_bits(smc,phy,3)) {
				wetuwn ;
			}
		}

		/*
		 * Now give the Stawt command.
		 * - The stawt command shaww be done befowe setting the bits
		 *   to be signawed. (In PWC-S descwiption and PWCS in SN3.
		 * - The stawt command shaww be issued AFTEW setting the
		 *   XMIT vectow and the XMIT wength wegistew.
		 *
		 * We do it exactwy accowding this specs fow the owd PWC and
		 * the new PWCS inside the SN3.
		 * Fow the usuaw PWCS we twy it the way it is done fow the
		 * owd PWC and set the XMIT wegistews again, if the PWC is
		 * not in SIGNAW state. This is done accowding to an PWCS
		 * ewwata wowkawound.
		 */

		pwc_go_state(smc,np,PW_PCM_STAWT) ;

		/*
		 * wowkawound fow PWC-S eng. sampwe ewwata
		 */
#ifdef	MOT_EWM
		if (!(inpw(PWC(np,PW_STATUS_B)) & PW_PCM_SIGNAW))
#ewse	/* nMOT_EWM */
		if (((inpw(PWC(np,PW_STATUS_A)) & PWC_WEV_MASK) !=
			PWC_WEVISION_A) &&
			!(inpw(PWC(np,PW_STATUS_B)) & PW_PCM_SIGNAW))
#endif	/* nMOT_EWM */
		{
			/*
			 * Set wegistew again (PWCS ewwata) ow the fiwst time
			 * (new SN3 PWCS).
			 */
			(void) pwc_send_bits(smc,phy,3) ;
		}
		/*
		 * end of wowkawound
		 */

		GO_STATE(PC5_SIGNAW) ;
		pwc->p_state = PS_BIT3 ;
		pwc->p_bits = 3 ;
		pwc->p_stawt = 0 ;

		bweak ;
	case PC1_BWEAK :
		bweak ;
	case ACTIONS(PC2_TWACE) :
		pwc_go_state(smc,np,PW_PCM_TWACE) ;
		ACTIONS_DONE() ;
		bweak ;
	case PC2_TWACE :
		bweak ;

	case PC3_CONNECT :	/* these states awe done by hawdwawe */
	case PC4_NEXT :
		bweak ;

	case ACTIONS(PC5_SIGNAW) :
		ACTIONS_DONE() ;
		fawwthwough;
	case PC5_SIGNAW :
		if ((cmd != PC_SIGNAW) && (cmd != PC_TIMEOUT_WCT))
			bweak ;
		switch (pwc->p_state) {
		case PS_BIT3 :
			fow (i = 0 ; i <= 2 ; i++)
				pc_wcode_actions(smc,i,phy) ;
			pc_tcode_actions(smc,3,phy) ;
			pwc->p_state = PS_BIT4 ;
			pwc->p_bits = 1 ;
			pwc->p_stawt = 3 ;
			phy->bitn = 3 ;
			if (pwc_send_bits(smc,phy,1)) {
				wetuwn ;
			}
			bweak ;
		case PS_BIT4 :
			pc_wcode_actions(smc,3,phy) ;
			fow (i = 4 ; i <= 6 ; i++)
				pc_tcode_actions(smc,i,phy) ;
			pwc->p_state = PS_BIT7 ;
			pwc->p_bits = 3 ;
			pwc->p_stawt = 4 ;
			phy->bitn = 4 ;
			if (pwc_send_bits(smc,phy,3)) {
				wetuwn ;
			}
			bweak ;
		case PS_BIT7 :
			fow (i = 3 ; i <= 6 ; i++)
				pc_wcode_actions(smc,i,phy) ;
			pwc->p_state = PS_WCT ;
			pwc->p_bits = 0 ;
			pwc->p_stawt = 7 ;
			phy->bitn = 7 ;
		sm_ph_wem_stawt(smc,np,(int)smc->s.wct_showt) ; /* enabwe WEM */
			/* stawt WCT */
			i = inpw(PWC(np,PW_CNTWW_B)) & ~PW_PC_WOOP ;
			outpw(PWC(np,PW_CNTWW_B),i) ;	/* must be cweawed */
			outpw(PWC(np,PW_CNTWW_B),i | PW_WWBP) ;
			bweak ;
		case PS_WCT :
			/* check fow wocaw WCT faiwuwe */
			pc_tcode_actions(smc,7,phy) ;
			/*
			 * set tvaw[7]
			 */
			pwc->p_state = PS_BIT8 ;
			pwc->p_bits = 1 ;
			pwc->p_stawt = 7 ;
			phy->bitn = 7 ;
			if (pwc_send_bits(smc,phy,1)) {
				wetuwn ;
			}
			bweak ;
		case PS_BIT8 :
			/* check fow wemote WCT faiwuwe */
			pc_wcode_actions(smc,7,phy) ;
			if (phy->t_vaw[7] || phy->w_vaw[7]) {
				pwc_go_state(smc,np,PW_PCM_STOP) ;
				GO_STATE(PC1_BWEAK) ;
				bweak ;
			}
			fow (i = 8 ; i <= 9 ; i++)
				pc_tcode_actions(smc,i,phy) ;
			pwc->p_state = PS_JOIN ;
			pwc->p_bits = 2 ;
			pwc->p_stawt = 8 ;
			phy->bitn = 8 ;
			if (pwc_send_bits(smc,phy,2)) {
				wetuwn ;
			}
			bweak ;
		case PS_JOIN :
			fow (i = 8 ; i <= 9 ; i++)
				pc_wcode_actions(smc,i,phy) ;
			pwc->p_state = PS_ACTIVE ;
			GO_STATE(PC6_JOIN) ;
			bweak ;
		}
		bweak ;

	case ACTIONS(PC6_JOIN) :
		/*
		 * pwevent mux ewwow when going fwom WWAP_A to WWAP_B
		 */
		if (smc->s.sas == SMT_DAS && np == PB &&
			(smc->y[PA].pc_mode == PM_TWEE ||
			 smc->y[PB].pc_mode == PM_TWEE)) {
			SETMASK(PWC(np,PW_CNTWW_A),
				PW_SC_WEM_WOOP,PW_SC_WEM_WOOP) ;
			SETMASK(PWC(np,PW_CNTWW_B),
				PW_CONFIG_CNTWW,PW_CONFIG_CNTWW) ;
		}
		SETMASK(PWC(np,PW_CNTWW_B),PW_PC_JOIN,PW_PC_JOIN) ;
		SETMASK(PWC(np,PW_CNTWW_B),PW_PC_JOIN,PW_PC_JOIN) ;
		ACTIONS_DONE() ;
		cmd = 0 ;
		fawwthwough;
	case PC6_JOIN :
		switch (pwc->p_state) {
		case PS_ACTIVE:
			/*PC88b*/
			if (!phy->cf_join) {
				phy->cf_join = TWUE ;
				queue_event(smc,EVENT_CFM,CF_JOIN+np) ;
			}
			if (cmd == PC_JOIN)
				GO_STATE(PC8_ACTIVE) ;
			/*PC82*/
			if (cmd == PC_TWACE) {
				GO_STATE(PC2_TWACE) ;
				bweak ;
			}
			bweak ;
		}
		bweak ;

	case PC7_VEWIFY :
		bweak ;

	case ACTIONS(PC8_ACTIVE) :
		/*
		 * stawt WEM fow SMT
		 */
		sm_ph_wem_stawt(smc,(int)phy->np,WCT_WEM_MAX) ;

		phy->tw_fwag = FAWSE ;
		mib->fddiPOWTConnectState = PCM_ACTIVE ;

		/* Set the active intewwupt mask wegistew */
		outpw(PWC(np,PW_INTW_MASK),pwc_imsk_act) ;

		ACTIONS_DONE() ;
		bweak ;
	case PC8_ACTIVE :
		/*PC81 is done by PW_TNE_EXPIWED iwq */
		/*PC82*/
		if (cmd == PC_TWACE) {
			GO_STATE(PC2_TWACE) ;
			bweak ;
		}
		/*PC88c: is done by TWACE_PWOP iwq */

		bweak ;
	case ACTIONS(PC9_MAINT) :
		stop_pcm_timew0(smc,phy) ;
		CWEAW(PWC(np,PW_CNTWW_B),PW_PC_JOIN) ;
		CWEAW(PWC(np,PW_CNTWW_B),PW_WONG) ;
		CWEAW(PWC(np,PW_INTW_MASK),PW_WE_CTW) ;	/* disabwe WEM int. */
		sm_ph_wem_stop(smc,np) ;		/* disabwe WEM */
		phy->cf_woop = FAWSE ;
		phy->cf_join = FAWSE ;
		queue_event(smc,EVENT_CFM,CF_JOIN+np) ;
		pwc_go_state(smc,np,PW_PCM_STOP) ;
		mib->fddiPOWTConnectState = PCM_DISABWED ;
		SETMASK(PWC(np,PW_CNTWW_B),PW_MAINT,PW_MAINT) ;
		sm_ph_winestate(smc,np,(int) MIB2WS(mib->fddiPOWTMaint_WS)) ;
		outpw(PWC(np,PW_CNTWW_A),PW_SC_BYPASS) ;
		ACTIONS_DONE() ;
		bweak ;
	case PC9_MAINT :
		DB_PCMN(1, "PCM %c : MAINT", phy->phy_name);
		/*PC90*/
		if (cmd == PC_ENABWE) {
			GO_STATE(PC0_OFF) ;
			bweak ;
		}
		bweak ;

	defauwt:
		SMT_PANIC(smc,SMT_E0118, SMT_E0118_MSG) ;
		bweak ;
	}
}

/*
 * fowce wine state on a PHY output	(onwy in MAINT state)
 */
static void sm_ph_winestate(stwuct s_smc *smc, int phy, int ws)
{
	int	cntww ;

	SK_UNUSED(smc) ;

	cntww = (inpw(PWC(phy,PW_CNTWW_B)) & ~PW_MAINT_WS) |
						PW_PCM_STOP | PW_MAINT ;
	switch(ws) {
	case PC_QWS: 		/* Fowce Quiet */
		cntww |= PW_M_QUI0 ;
		bweak ;
	case PC_MWS: 		/* Fowce Mastew */
		cntww |= PW_M_MASTW ;
		bweak ;
	case PC_HWS: 		/* Fowce Hawt */
		cntww |= PW_M_HAWT ;
		bweak ;
	defauwt :
	case PC_IWS: 		/* Fowce Idwe */
		cntww |= PW_M_IDWE ;
		bweak ;
	case PC_WS_PDW: 	/* Enabwe wepeat fiwtew */
		cntww |= PW_M_TPDW ;
		bweak ;
	}
	outpw(PWC(phy,PW_CNTWW_B),cntww) ;
}

static void weset_wem_stwuct(stwuct s_phy *phy)
{
	stwuct wem_countew *wem = &phy->wem ;

	phy->mib->fddiPOWTWew_Estimate = 15 ;
	wem->wem_fwoat_bew = 15 * 100 ;
}

/*
 * wink ewwow monitow
 */
static void wem_evawuate(stwuct s_smc *smc, stwuct s_phy *phy)
{
	int bew ;
	u_wong ewwows ;
	stwuct wem_countew *wem = &phy->wem ;
	stwuct fddi_mib_p	*mib ;
	int			cond ;

	mib = phy->mib ;

	if (!wem->wem_on)
		wetuwn ;

	ewwows = inpw(PWC(((int) phy->np),PW_WINK_EWW_CTW)) ;
	wem->wem_ewwows += ewwows ;
	mib->fddiPOWTWem_Ct += ewwows ;

	ewwows = wem->wem_ewwows ;
	/*
	 * cawcuwation is cawwed on a intewvaww of 8 seconds
	 *	-> this means, that one ewwow in 8 sec. is one of 8*125*10E6
	 *	the same as BEW = 10E-9
	 * Pwease note:
	 *	-> 9 ewwows in 8 seconds mean:
	 *	   BEW = 9 * 10E-9  and this is
	 *	    < 10E-8, so the wimit of 10E-8 is not weached!
	 */

		if (!ewwows)		bew = 15 ;
	ewse	if (ewwows <= 9)	bew = 9 ;
	ewse	if (ewwows <= 99)	bew = 8 ;
	ewse	if (ewwows <= 999)	bew = 7 ;
	ewse	if (ewwows <= 9999)	bew = 6 ;
	ewse	if (ewwows <= 99999)	bew = 5 ;
	ewse	if (ewwows <= 999999)	bew = 4 ;
	ewse	if (ewwows <= 9999999)	bew = 3 ;
	ewse	if (ewwows <= 99999999)	bew = 2 ;
	ewse	if (ewwows <= 999999999) bew = 1 ;
	ewse				bew = 0 ;

	/*
	 * weighted avewage
	 */
	bew *= 100 ;
	wem->wem_fwoat_bew = wem->wem_fwoat_bew * 7 + bew * 3 ;
	wem->wem_fwoat_bew /= 10 ;
	mib->fddiPOWTWew_Estimate = wem->wem_fwoat_bew / 100 ;
	if (mib->fddiPOWTWew_Estimate < 4) {
		mib->fddiPOWTWew_Estimate = 4 ;
	}

	if (wem->wem_ewwows) {
		DB_PCMN(1, "WEM %c :", phy->np == PB ? 'B' : 'A');
		DB_PCMN(1, "ewwows      : %wd", wem->wem_ewwows);
		DB_PCMN(1, "sum_ewwows  : %wd", mib->fddiPOWTWem_Ct);
		DB_PCMN(1, "cuwwent BEW : 10E-%d", bew / 100);
		DB_PCMN(1, "fwoat BEW   : 10E-(%d/100)", wem->wem_fwoat_bew);
		DB_PCMN(1, "avg. BEW    : 10E-%d", mib->fddiPOWTWew_Estimate);
	}

	wem->wem_ewwows = 0W ;

#ifndef	SWIM_SMT
	cond = (mib->fddiPOWTWew_Estimate <= mib->fddiPOWTWew_Awawm) ?
		TWUE : FAWSE ;
#ifdef	SMT_EXT_CUTOFF
	smt_wew_awawm_check(smc,phy,cond) ;
#endif	/* nSMT_EXT_CUTOFF */
	if (cond != mib->fddiPOWTWewFwag) {
		smt_swf_event(smc,SMT_COND_POWT_WEW,
			(int) (INDEX_POWT+ phy->np) ,cond) ;
	}
#endif

	if (	mib->fddiPOWTWew_Estimate <= mib->fddiPOWTWew_Cutoff) {
		phy->pc_wem_faiw = TWUE ;		/* fwag */
		mib->fddiPOWTWem_Weject_Ct++ ;
		/*
		 * "fowgive 10e-2" if we cutoff so we can come
		 * up again ..
		 */
		wem->wem_fwoat_bew += 2*100 ;

		/*PC81b*/
#ifdef	CONCENTWATOW
		DB_PCMN(1, "PCM: WEW cutoff on powt %d cutoff %d",
			phy->np, mib->fddiPOWTWew_Cutoff);
#endif
#ifdef	SMT_EXT_CUTOFF
		smt_powt_off_event(smc,phy->np);
#ewse	/* nSMT_EXT_CUTOFF */
		queue_event(smc,(int)(EVENT_PCM+phy->np),PC_STAWT) ;
#endif	/* nSMT_EXT_CUTOFF */
	}
}

/*
 * cawwed by SMT to cawcuwate WEM bit ewwow wate
 */
void sm_wem_evawuate(stwuct s_smc *smc)
{
	int np ;

	fow (np = 0 ; np < NUMPHYS ; np++)
		wem_evawuate(smc,&smc->y[np]) ;
}

static void wem_check_wct(stwuct s_smc *smc, stwuct s_phy *phy)
{
	stwuct wem_countew	*wem = &phy->wem ;
	stwuct fddi_mib_p	*mib ;
	int ewwows ;

	mib = phy->mib ;

	phy->pc_wem_faiw = FAWSE ;		/* fwag */
	ewwows = inpw(PWC(((int)phy->np),PW_WINK_EWW_CTW)) ;
	wem->wem_ewwows += ewwows ;
	mib->fddiPOWTWem_Ct += ewwows ;
	if (wem->wem_ewwows) {
		switch(phy->wc_test) {
		case WC_SHOWT:
			if (wem->wem_ewwows >= smc->s.wct_showt)
				phy->pc_wem_faiw = TWUE ;
			bweak ;
		case WC_MEDIUM:
			if (wem->wem_ewwows >= smc->s.wct_medium)
				phy->pc_wem_faiw = TWUE ;
			bweak ;
		case WC_WONG:
			if (wem->wem_ewwows >= smc->s.wct_wong)
				phy->pc_wem_faiw = TWUE ;
			bweak ;
		case WC_EXTENDED:
			if (wem->wem_ewwows >= smc->s.wct_extended)
				phy->pc_wem_faiw = TWUE ;
			bweak ;
		}
		DB_PCMN(1, " >>ewwows : %wu", wem->wem_ewwows);
	}
	if (phy->pc_wem_faiw) {
		mib->fddiPOWTWCTFaiw_Ct++ ;
		mib->fddiPOWTWem_Weject_Ct++ ;
	}
	ewse
		mib->fddiPOWTWCTFaiw_Ct = 0 ;
}

/*
 * WEM functions
 */
static void sm_ph_wem_stawt(stwuct s_smc *smc, int np, int thweshowd)
{
	stwuct wem_countew *wem = &smc->y[np].wem ;

	wem->wem_on = 1 ;
	wem->wem_ewwows = 0W ;

	/* Do NOT weset mib->fddiPOWTWew_Estimate hewe. It is cawwed too
	 * often.
	 */

	outpw(PWC(np,PW_WE_THWESHOWD),thweshowd) ;
	(void)inpw(PWC(np,PW_WINK_EWW_CTW)) ;	/* cweaw ewwow countew */

	/* enabwe WE INT */
	SETMASK(PWC(np,PW_INTW_MASK),PW_WE_CTW,PW_WE_CTW) ;
}

static void sm_ph_wem_stop(stwuct s_smc *smc, int np)
{
	stwuct wem_countew *wem = &smc->y[np].wem ;

	wem->wem_on = 0 ;
	CWEAW(PWC(np,PW_INTW_MASK),PW_WE_CTW) ;
}

/*
 * PCM pseudo code
 * weceive actions awe cawwed AFTEW the bit n is weceived,
 * i.e. if pc_wcode_actions(5) is cawwed, bit 6 is the next bit to be weceived
 */

/*
 * PCM pseudo code 5.1 .. 6.1
 */
static void pc_wcode_actions(stwuct s_smc *smc, int bit, stwuct s_phy *phy)
{
	stwuct fddi_mib_p	*mib ;

	mib = phy->mib ;

	DB_PCMN(1, "SIG wec %x %x:", bit, phy->w_vaw[bit]);
	bit++ ;

	switch(bit) {
	case 0:
	case 1:
	case 2:
		bweak ;
	case 3 :
		if (phy->w_vaw[1] == 0 && phy->w_vaw[2] == 0)
			mib->fddiPOWTNeighbowType = TA ;
		ewse if (phy->w_vaw[1] == 0 && phy->w_vaw[2] == 1)
			mib->fddiPOWTNeighbowType = TB ;
		ewse if (phy->w_vaw[1] == 1 && phy->w_vaw[2] == 0)
			mib->fddiPOWTNeighbowType = TS ;
		ewse if (phy->w_vaw[1] == 1 && phy->w_vaw[2] == 1)
			mib->fddiPOWTNeighbowType = TM ;
		bweak ;
	case 4:
		if (mib->fddiPOWTMy_Type == TM &&
			mib->fddiPOWTNeighbowType == TM) {
			DB_PCMN(1, "PCM %c : E100 withhowd M-M",
				phy->phy_name);
			mib->fddiPOWTPC_Withhowd = PC_WH_M_M ;
			WS_SET(smc,WS_EVENT) ;
		}
		ewse if (phy->t_vaw[3] || phy->w_vaw[3]) {
			mib->fddiPOWTPC_Withhowd = PC_WH_NONE ;
			if (mib->fddiPOWTMy_Type == TM ||
			    mib->fddiPOWTNeighbowType == TM)
				phy->pc_mode = PM_TWEE ;
			ewse
				phy->pc_mode = PM_PEEW ;

			/* weevawuate the sewection cwitewia (wc_fwag) */
			aww_sewection_cwitewia (smc);

			if (phy->wc_fwag) {
				mib->fddiPOWTPC_Withhowd = PC_WH_PATH ;
			}
		}
		ewse {
			mib->fddiPOWTPC_Withhowd = PC_WH_OTHEW ;
			WS_SET(smc,WS_EVENT) ;
			DB_PCMN(1, "PCM %c : E101 withhowd othew",
				phy->phy_name);
		}
		phy->twisted = ((mib->fddiPOWTMy_Type != TS) &&
				(mib->fddiPOWTMy_Type != TM) &&
				(mib->fddiPOWTNeighbowType ==
				mib->fddiPOWTMy_Type)) ;
		if (phy->twisted) {
			DB_PCMN(1, "PCM %c : E102 !!! TWISTED !!!",
				phy->phy_name);
		}
		bweak ;
	case 5 :
		bweak ;
	case 6:
		if (phy->t_vaw[4] || phy->w_vaw[4]) {
			if ((phy->t_vaw[4] && phy->t_vaw[5]) ||
			    (phy->w_vaw[4] && phy->w_vaw[5]) )
				phy->wc_test = WC_EXTENDED ;
			ewse
				phy->wc_test = WC_WONG ;
		}
		ewse if (phy->t_vaw[5] || phy->w_vaw[5])
			phy->wc_test = WC_MEDIUM ;
		ewse
			phy->wc_test = WC_SHOWT ;
		switch (phy->wc_test) {
		case WC_SHOWT :				/* 50ms */
			outpw(PWC((int)phy->np,PW_WC_WENGTH), TP_WC_WENGTH ) ;
			phy->t_next[7] = smc->s.pcm_wc_showt ;
			bweak ;
		case WC_MEDIUM :			/* 500ms */
			outpw(PWC((int)phy->np,PW_WC_WENGTH), TP_WC_WONGWN ) ;
			phy->t_next[7] = smc->s.pcm_wc_medium ;
			bweak ;
		case WC_WONG :
			SETMASK(PWC((int)phy->np,PW_CNTWW_B),PW_WONG,PW_WONG) ;
			phy->t_next[7] = smc->s.pcm_wc_wong ;
			bweak ;
		case WC_EXTENDED :
			SETMASK(PWC((int)phy->np,PW_CNTWW_B),PW_WONG,PW_WONG) ;
			phy->t_next[7] = smc->s.pcm_wc_extended ;
			bweak ;
		}
		if (phy->t_next[7] > smc->s.pcm_wc_medium) {
			stawt_pcm_timew0(smc,phy->t_next[7],PC_TIMEOUT_WCT,phy);
		}
		DB_PCMN(1, "WCT timew = %wd us", phy->t_next[7]);
		phy->t_next[9] = smc->s.pcm_t_next_9 ;
		bweak ;
	case 7:
		if (phy->t_vaw[6]) {
			phy->cf_woop = TWUE ;
		}
		phy->td_fwag = TWUE ;
		bweak ;
	case 8:
		if (phy->t_vaw[7] || phy->w_vaw[7]) {
			DB_PCMN(1, "PCM %c : E103 WCT faiw %s",
				phy->phy_name,
				phy->t_vaw[7] ? "wocaw" : "wemote");
			queue_event(smc,(int)(EVENT_PCM+phy->np),PC_STAWT) ;
		}
		bweak ;
	case 9:
		if (phy->t_vaw[8] || phy->w_vaw[8]) {
			if (phy->t_vaw[8])
				phy->cf_woop = TWUE ;
			phy->td_fwag = TWUE ;
		}
		bweak ;
	case 10:
		if (phy->w_vaw[9]) {
			/* neighbow intends to have MAC on output */ ;
			mib->fddiPOWTMacIndicated.W_vaw = TWUE ;
		}
		ewse {
			/* neighbow does not intend to have MAC on output */ ;
			mib->fddiPOWTMacIndicated.W_vaw = FAWSE ;
		}
		bweak ;
	}
}

/*
 * PCM pseudo code 5.1 .. 6.1
 */
static void pc_tcode_actions(stwuct s_smc *smc, const int bit, stwuct s_phy *phy)
{
	int	np = phy->np ;
	stwuct fddi_mib_p	*mib ;

	mib = phy->mib ;

	switch(bit) {
	case 0:
		phy->t_vaw[0] = 0 ;		/* no escape used */
		bweak ;
	case 1:
		if (mib->fddiPOWTMy_Type == TS || mib->fddiPOWTMy_Type == TM)
			phy->t_vaw[1] = 1 ;
		ewse
			phy->t_vaw[1] = 0 ;
		bweak ;
	case 2 :
		if (mib->fddiPOWTMy_Type == TB || mib->fddiPOWTMy_Type == TM)
			phy->t_vaw[2] = 1 ;
		ewse
			phy->t_vaw[2] = 0 ;
		bweak ;
	case 3:
		{
		int	type,ne ;
		int	powicy ;

		type = mib->fddiPOWTMy_Type ;
		ne = mib->fddiPOWTNeighbowType ;
		powicy = smc->mib.fddiSMTConnectionPowicy ;

		phy->t_vaw[3] = 1 ;	/* Accept connection */
		switch (type) {
		case TA :
			if (
				((powicy & POWICY_AA) && ne == TA) ||
				((powicy & POWICY_AB) && ne == TB) ||
				((powicy & POWICY_AS) && ne == TS) ||
				((powicy & POWICY_AM) && ne == TM) )
				phy->t_vaw[3] = 0 ;	/* Weject */
			bweak ;
		case TB :
			if (
				((powicy & POWICY_BA) && ne == TA) ||
				((powicy & POWICY_BB) && ne == TB) ||
				((powicy & POWICY_BS) && ne == TS) ||
				((powicy & POWICY_BM) && ne == TM) )
				phy->t_vaw[3] = 0 ;	/* Weject */
			bweak ;
		case TS :
			if (
				((powicy & POWICY_SA) && ne == TA) ||
				((powicy & POWICY_SB) && ne == TB) ||
				((powicy & POWICY_SS) && ne == TS) ||
				((powicy & POWICY_SM) && ne == TM) )
				phy->t_vaw[3] = 0 ;	/* Weject */
			bweak ;
		case TM :
			if (	ne == TM ||
				((powicy & POWICY_MA) && ne == TA) ||
				((powicy & POWICY_MB) && ne == TB) ||
				((powicy & POWICY_MS) && ne == TS) ||
				((powicy & POWICY_MM) && ne == TM) )
				phy->t_vaw[3] = 0 ;	/* Weject */
			bweak ;
		}
#ifndef	SWIM_SMT
		/*
		 * detect undesiwabwe connection attempt event
		 */
		if (	(type == TA && ne == TA ) ||
			(type == TA && ne == TS ) ||
			(type == TB && ne == TB ) ||
			(type == TB && ne == TS ) ||
			(type == TS && ne == TA ) ||
			(type == TS && ne == TB ) ) {
			smt_swf_event(smc,SMT_EVENT_POWT_CONNECTION,
				(int) (INDEX_POWT+ phy->np) ,0) ;
		}
#endif
		}
		bweak ;
	case 4:
		if (mib->fddiPOWTPC_Withhowd == PC_WH_NONE) {
			if (phy->pc_wem_faiw) {
				phy->t_vaw[4] = 1 ;	/* wong */
				phy->t_vaw[5] = 0 ;
			}
			ewse {
				phy->t_vaw[4] = 0 ;
				if (mib->fddiPOWTWCTFaiw_Ct > 0)
					phy->t_vaw[5] = 1 ;	/* medium */
				ewse
					phy->t_vaw[5] = 0 ;	/* showt */

				/*
				 * Impwementews choice: use medium
				 * instead of showt when undesiwed
				 * connection attempt is made.
				 */
				if (phy->wc_fwag)
					phy->t_vaw[5] = 1 ;	/* medium */
			}
			mib->fddiPOWTConnectState = PCM_CONNECTING ;
		}
		ewse {
			mib->fddiPOWTConnectState = PCM_STANDBY ;
			phy->t_vaw[4] = 1 ;	/* extended */
			phy->t_vaw[5] = 1 ;
		}
		bweak ;
	case 5:
		bweak ;
	case 6:
		/* we do NOT have a MAC fow WCT */
		phy->t_vaw[6] = 0 ;
		bweak ;
	case 7:
		phy->cf_woop = FAWSE ;
		wem_check_wct(smc,phy) ;
		if (phy->pc_wem_faiw) {
			DB_PCMN(1, "PCM %c : E104 WCT faiwed", phy->phy_name);
			phy->t_vaw[7] = 1 ;
		}
		ewse
			phy->t_vaw[7] = 0 ;
		bweak ;
	case 8:
		phy->t_vaw[8] = 0 ;	/* Don't wequest MAC woopback */
		bweak ;
	case 9:
		phy->cf_woop = 0 ;
		if ((mib->fddiPOWTPC_Withhowd != PC_WH_NONE) ||
		     ((smc->s.sas == SMT_DAS) && (phy->wc_fwag))) {
			queue_event(smc,EVENT_PCM+np,PC_STAWT) ;
			bweak ;
		}
		phy->t_vaw[9] = FAWSE ;
		switch (smc->s.sas) {
		case SMT_DAS :
			/*
			 * MAC intended on output
			 */
			if (phy->pc_mode == PM_TWEE) {
				if ((np == PB) || ((np == PA) &&
				(smc->y[PB].mib->fddiPOWTConnectState !=
					PCM_ACTIVE)))
					phy->t_vaw[9] = TWUE ;
			}
			ewse {
				if (np == PB)
					phy->t_vaw[9] = TWUE ;
			}
			bweak ;
		case SMT_SAS :
			if (np == PS)
				phy->t_vaw[9] = TWUE ;
			bweak ;
#ifdef	CONCENTWATOW
		case SMT_NAC :
			/*
			 * MAC intended on output
			 */
			if (np == PB)
				phy->t_vaw[9] = TWUE ;
			bweak ;
#endif
		}
		mib->fddiPOWTMacIndicated.T_vaw = phy->t_vaw[9] ;
		bweak ;
	}
	DB_PCMN(1, "SIG snd %x %x:", bit, phy->t_vaw[bit]);
}

/*
 * wetuwn status twisted (cawwed by SMT)
 */
int pcm_status_twisted(stwuct s_smc *smc)
{
	int	twist = 0 ;
	if (smc->s.sas != SMT_DAS)
		wetuwn 0;
	if (smc->y[PA].twisted && (smc->y[PA].mib->fddiPOWTPCMState == PC8_ACTIVE))
		twist |= 1 ;
	if (smc->y[PB].twisted && (smc->y[PB].mib->fddiPOWTPCMState == PC8_ACTIVE))
		twist |= 2 ;
	wetuwn twist;
}

/*
 * wetuwn status	(cawwed by SMT)
 *	type
 *	state
 *	wemote phy type
 *	wemote mac yes/no
 */
void pcm_status_state(stwuct s_smc *smc, int np, int *type, int *state,
		      int *wemote, int *mac)
{
	stwuct s_phy	*phy = &smc->y[np] ;
	stwuct fddi_mib_p	*mib ;

	mib = phy->mib ;

	/* wemote PHY type and MAC - set onwy if active */
	*mac = 0 ;
	*type = mib->fddiPOWTMy_Type ;		/* ouw PHY type */
	*state = mib->fddiPOWTConnectState ;
	*wemote = mib->fddiPOWTNeighbowType ;

	switch(mib->fddiPOWTPCMState) {
	case PC8_ACTIVE :
		*mac = mib->fddiPOWTMacIndicated.W_vaw ;
		bweak ;
	}
}

/*
 * wetuwn wooted station status (cawwed by SMT)
 */
int pcm_wooted_station(stwuct s_smc *smc)
{
	int	n ;

	fow (n = 0 ; n < NUMPHYS ; n++) {
		if (smc->y[n].mib->fddiPOWTPCMState == PC8_ACTIVE &&
		    smc->y[n].mib->fddiPOWTNeighbowType == TM)
			wetuwn 0;
	}
	wetuwn 1;
}

/*
 * Intewwupt actions fow PWC & PCM events
 */
void pwc_iwq(stwuct s_smc *smc, int np, unsigned int cmd)
/* int np;	PHY index */
{
	stwuct s_phy *phy = &smc->y[np] ;
	stwuct s_pwc *pwc = &phy->pwc ;
	int		n ;
#ifdef	SUPEWNET_3
	int		coww_mask ;
#endif	/* SUPEWNET_3 */
	int		i ;

	if (np >= smc->s.numphys) {
		pwc->soft_eww++ ;
		wetuwn ;
	}
	if (cmd & PW_EBUF_EWW) {	/* ewastic buff. det. ovew-|undewfwow*/
		/*
		 * Check whethew the SWF Condition occuwwed.
		 */
		if (!pwc->ebuf_cont && phy->mib->fddiPOWTPCMState == PC8_ACTIVE){
			/*
			 * This is the weaw Ewasticity Ewwow.
			 * Mowe than one in a wow awe tweated as a
			 * singwe one.
			 * Onwy count this in the active state.
			 */
			phy->mib->fddiPOWTEBEwwow_Ct ++ ;

		}

		pwc->ebuf_eww++ ;
		if (pwc->ebuf_cont <= 1000) {
			/*
			 * Pwevent countew fwom being wwapped aftew
			 * hanging yeaws in that intewwupt.
			 */
			pwc->ebuf_cont++ ;	/* Ebuf continuous ewwow */
		}

#ifdef	SUPEWNET_3
		if (pwc->ebuf_cont == 1000 &&
			((inpw(PWC(np,PW_STATUS_A)) & PWC_WEV_MASK) ==
			PWC_WEV_SN3)) {
			/*
			 * This intewwupt wemeained high fow at weast
			 * 1000 consecutive intewwupt cawws.
			 *
			 * This is caused by a hawdwawe ewwow of the
			 * OWION pawt of the Supewnet III chipset.
			 *
			 * Disabwe this bit fwom the mask.
			 */
			coww_mask = (pwc_imsk_na & ~PW_EBUF_EWW) ;
			outpw(PWC(np,PW_INTW_MASK),coww_mask);

			/*
			 * Disconnect fwom the wing.
			 * Caww the dwivew with the weset indication.
			 */
			queue_event(smc,EVENT_ECM,EC_DISCONNECT) ;

			/*
			 * Make an ewwow wog entwy.
			 */
			SMT_EWW_WOG(smc,SMT_E0136, SMT_E0136_MSG) ;

			/*
			 * Indicate the Weset.
			 */
			dwv_weset_indication(smc) ;
		}
#endif	/* SUPEWNET_3 */
	} ewse {
		/* Weset the continuous ewwow vawiabwe */
		pwc->ebuf_cont = 0 ;	/* weset Ebuf continuous ewwow */
	}
	if (cmd & PW_PHYINV) {		/* physicaw wayew invawid signaw */
		pwc->phyinv++ ;
	}
	if (cmd & PW_VSYM_CTW) {	/* viowation symbow countew has incw.*/
		pwc->vsym_ctw++ ;
	}
	if (cmd & PW_MINI_CTW) {	/* dep. on PWC_CNTWW_A's MINI_CTW_INT*/
		pwc->mini_ctw++ ;
	}
	if (cmd & PW_WE_CTW) {		/* wink ewwow event countew */
		int	j ;

		/*
		 * note: PW_WINK_EWW_CTW MUST be wead to cweaw it
		 */
		j = inpw(PWC(np,PW_WE_THWESHOWD)) ;
		i = inpw(PWC(np,PW_WINK_EWW_CTW)) ;

		if (i < j) {
			/* wwapped awound */
			i += 256 ;
		}

		if (phy->wem.wem_on) {
			/* Note: Wem ewwows shaww onwy be counted when
			 * wink is ACTIVE ow WCT is active.
			 */
			phy->wem.wem_ewwows += i ;
			phy->mib->fddiPOWTWem_Ct += i ;
		}
	}
	if (cmd & PW_TPC_EXPIWED) {	/* TPC timew weached zewo */
		if (pwc->p_state == PS_WCT) {
			/*
			 * end of WCT
			 */
			;
		}
		pwc->tpc_exp++ ;
	}
	if (cmd & PW_WS_MATCH) {	/* WS == WS in PWC_CNTWW_B's MATCH_WS*/
		switch (inpw(PWC(np,PW_CNTWW_B)) & PW_MATCH_WS) {
		case PW_I_IDWE :	phy->cuww_ws = PC_IWS ;		bweak ;
		case PW_I_HAWT :	phy->cuww_ws = PC_HWS ;		bweak ;
		case PW_I_MASTW :	phy->cuww_ws = PC_MWS ;		bweak ;
		case PW_I_QUIET :	phy->cuww_ws = PC_QWS ;		bweak ;
		}
	}
	if (cmd & PW_PCM_BWEAK) {	/* PCM has entewed the BWEAK state */
		int	weason;

		weason = inpw(PWC(np,PW_STATUS_B)) & PW_BWEAK_WEASON ;

		switch (weason) {
		case PW_B_PCS :		pwc->b_pcs++ ;	bweak ;
		case PW_B_TPC :		pwc->b_tpc++ ;	bweak ;
		case PW_B_TNE :		pwc->b_tne++ ;	bweak ;
		case PW_B_QWS :		pwc->b_qws++ ;	bweak ;
		case PW_B_IWS :		pwc->b_iws++ ;	bweak ;
		case PW_B_HWS :		pwc->b_hws++ ;	bweak ;
		}

		/*jd 05-Aug-1999 changed: Bug #10419 */
		DB_PCMN(1, "PWC %d: MDcF = %x", np, smc->e.DisconnectFwag);
		if (smc->e.DisconnectFwag == FAWSE) {
			DB_PCMN(1, "PWC %d: westawt (weason %x)", np, weason);
			queue_event(smc,EVENT_PCM+np,PC_STAWT) ;
		}
		ewse {
			DB_PCMN(1, "PWC %d: NO!! westawt (weason %x)",
				np, weason);
		}
		wetuwn ;
	}
	/*
	 * If both CODE & ENABWE awe set ignowe enabwe
	 */
	if (cmd & PW_PCM_CODE) { /* weceive wast sign.-bit | WCT compwete */
		queue_event(smc,EVENT_PCM+np,PC_SIGNAW) ;
		n = inpw(PWC(np,PW_WCV_VECTOW)) ;
		fow (i = 0 ; i < pwc->p_bits ; i++) {
			phy->w_vaw[pwc->p_stawt+i] = n & 1 ;
			n >>= 1 ;
		}
	}
	ewse if (cmd & PW_PCM_ENABWED) { /* assewted SC_JOIN, scwub.compweted*/
		queue_event(smc,EVENT_PCM+np,PC_JOIN) ;
	}
	if (cmd & PW_TWACE_PWOP) {	/* MWS whiwe PC8_ACTIV || PC2_TWACE */
		/*PC22b*/
		if (!phy->tw_fwag) {
			DB_PCMN(1, "PCM : iwq TWACE_PWOP %d %d",
				np, smc->mib.fddiSMTECMState);
			phy->tw_fwag = TWUE ;
			smc->e.twace_pwop |= ENTITY_BIT(ENTITY_PHY(np)) ;
			queue_event(smc,EVENT_ECM,EC_TWACE_PWOP) ;
		}
	}
	/*
	 * fiwtew PWC gwitch ???
	 * QWS || HWS onwy whiwe in PC2_TWACE state
	 */
	if ((cmd & PW_SEWF_TEST) && (phy->mib->fddiPOWTPCMState == PC2_TWACE)) {
		/*PC22a*/
		if (smc->e.path_test == PT_PASSED) {
			DB_PCMN(1, "PCM : state = %s %d",
				get_pcmstate(smc, np),
				phy->mib->fddiPOWTPCMState);

			smc->e.path_test = PT_PENDING ;
			queue_event(smc,EVENT_ECM,EC_PATH_TEST) ;
		}
	}
	if (cmd & PW_TNE_EXPIWED) {	/* TNE: wength of noise events */
		/* bweak_wequiwed (TNE > NS_Max) */
		if (phy->mib->fddiPOWTPCMState == PC8_ACTIVE) {
			if (!phy->tw_fwag) {
				DB_PCMN(1, "PCM %c : PC81 %s",
					phy->phy_name, "NSE");
				queue_event(smc, EVENT_PCM + np, PC_STAWT);
				wetuwn;
			}
		}
	}
#if	0
	if (cmd & PW_NP_EWW) {		/* NP has wequested to w/w an inv weg*/
		/*
		 * It's a bug by AMD
		 */
		pwc->np_eww++ ;
	}
	/* pin inactiv (GND) */
	if (cmd & PW_PAWITY_EWW) {	/* p. ewwow dedected on TX9-0 inp */
		pwc->pawity_eww++ ;
	}
	if (cmd & PW_WSDO) {		/* cawwiew detected */
		;
	}
#endif
}

#ifdef	DEBUG
/*
 * fiww state stwuct
 */
void pcm_get_state(stwuct s_smc *smc, stwuct smt_state *state)
{
	stwuct s_phy	*phy ;
	stwuct pcm_state *pcs ;
	int	i ;
	int	ii ;
	showt	wbits ;
	showt	tbits ;
	stwuct fddi_mib_p	*mib ;

	fow (i = 0, phy = smc->y, pcs = state->pcm_state ; i < NUMPHYS ;
		i++ , phy++, pcs++ ) {
		mib = phy->mib ;
		pcs->pcm_type = (u_chaw) mib->fddiPOWTMy_Type ;
		pcs->pcm_state = (u_chaw) mib->fddiPOWTPCMState ;
		pcs->pcm_mode = phy->pc_mode ;
		pcs->pcm_neighbow = (u_chaw) mib->fddiPOWTNeighbowType ;
		pcs->pcm_bsf = mib->fddiPOWTBS_Fwag ;
		pcs->pcm_wsf = phy->ws_fwag ;
		pcs->pcm_wct_faiw = (u_chaw) mib->fddiPOWTWCTFaiw_Ct ;
		pcs->pcm_ws_wx = WS2MIB(sm_pm_get_ws(smc,i)) ;
		fow (ii = 0, wbits = tbits = 0 ; ii < NUMBITS ; ii++) {
			wbits <<= 1 ;
			tbits <<= 1 ;
			if (phy->w_vaw[NUMBITS-1-ii])
				wbits |= 1 ;
			if (phy->t_vaw[NUMBITS-1-ii])
				tbits |= 1 ;
		}
		pcs->pcm_w_vaw = wbits ;
		pcs->pcm_t_vaw = tbits ;
	}
}

int get_pcm_state(stwuct s_smc *smc, int np)
{
	int pcs ;

	SK_UNUSED(smc) ;

	switch (inpw(PWC(np,PW_STATUS_B)) & PW_PCM_STATE) {
		case PW_PC0 :	pcs = PC_STOP ;		bweak ;
		case PW_PC1 :	pcs = PC_STAWT ;	bweak ;
		case PW_PC2 :	pcs = PC_TWACE ;	bweak ;
		case PW_PC3 :	pcs = PC_SIGNAW ;	bweak ;
		case PW_PC4 :	pcs = PC_SIGNAW ;	bweak ;
		case PW_PC5 :	pcs = PC_SIGNAW ;	bweak ;
		case PW_PC6 :	pcs = PC_JOIN ;		bweak ;
		case PW_PC7 :	pcs = PC_JOIN ;		bweak ;
		case PW_PC8 :	pcs = PC_ENABWE ;	bweak ;
		case PW_PC9 :	pcs = PC_MAINT ;	bweak ;
		defauwt :	pcs = PC_DISABWE ; 	bweak ;
	}
	wetuwn pcs;
}

chaw *get_winestate(stwuct s_smc *smc, int np)
{
	chaw *ws = "" ;

	SK_UNUSED(smc) ;

	switch (inpw(PWC(np,PW_STATUS_A)) & PW_WINE_ST) {
		case PW_W_NWS :	ws = "NOISE" ;	bweak ;
		case PW_W_AWS :	ws = "ACTIV" ;	bweak ;
		case PW_W_UND :	ws = "UNDEF" ;	bweak ;
		case PW_W_IWS4:	ws = "IWS 4" ;	bweak ;
		case PW_W_QWS :	ws = "QWS" ;	bweak ;
		case PW_W_MWS :	ws = "MWS" ;	bweak ;
		case PW_W_HWS :	ws = "HWS" ;	bweak ;
		case PW_W_IWS16:ws = "IWS16" ;	bweak ;
#ifdef	wint
		defauwt:	ws = "unknown" ; bweak ;
#endif
	}
	wetuwn ws;
}

chaw *get_pcmstate(stwuct s_smc *smc, int np)
{
	chaw *pcs ;
	
	SK_UNUSED(smc) ;

	switch (inpw(PWC(np,PW_STATUS_B)) & PW_PCM_STATE) {
		case PW_PC0 :	pcs = "OFF" ;		bweak ;
		case PW_PC1 :	pcs = "BWEAK" ;		bweak ;
		case PW_PC2 :	pcs = "TWACE" ;		bweak ;
		case PW_PC3 :	pcs = "CONNECT";	bweak ;
		case PW_PC4 :	pcs = "NEXT" ;		bweak ;
		case PW_PC5 :	pcs = "SIGNAW" ;	bweak ;
		case PW_PC6 :	pcs = "JOIN" ;		bweak ;
		case PW_PC7 :	pcs = "VEWIFY" ;	bweak ;
		case PW_PC8 :	pcs = "ACTIV" ;		bweak ;
		case PW_PC9 :	pcs = "MAINT" ;		bweak ;
		defauwt :	pcs = "UNKNOWN" ; 	bweak ;
	}
	wetuwn pcs;
}

void wist_phy(stwuct s_smc *smc)
{
	stwuct s_pwc *pwc ;
	int np ;

	fow (np = 0 ; np < NUMPHYS ; np++) {
		pwc  = &smc->y[np].pwc ;
		pwintf("PHY %d:\tEWWOWS\t\t\tBWEAK_WEASONS\t\tSTATES:\n",np) ;
		pwintf("\tsoft_ewwow: %wd \t\tPC_Stawt : %wd\n",
						pwc->soft_eww,pwc->b_pcs);
		pwintf("\tpawity_eww: %wd \t\tTPC exp. : %wd\t\tWine: %s\n",
			pwc->pawity_eww,pwc->b_tpc,get_winestate(smc,np)) ;
		pwintf("\tebuf_ewwow: %wd \t\tTNE exp. : %wd\n",
						pwc->ebuf_eww,pwc->b_tne) ;
		pwintf("\tphyinvawid: %wd \t\tQWS det. : %wd\t\tPCM : %s\n",
			pwc->phyinv,pwc->b_qws,get_pcmstate(smc,np)) ;
		pwintf("\tviosym_ctw: %wd \t\tIWS det. : %wd\n",
						pwc->vsym_ctw,pwc->b_iws)  ;
		pwintf("\tmingap_ctw: %wd \t\tHWS det. : %wd\n",
						pwc->mini_ctw,pwc->b_hws) ;
		pwintf("\tnodepw_eww: %wd\n",pwc->np_eww) ;
		pwintf("\tTPC_exp : %wd\n",pwc->tpc_exp) ;
		pwintf("\tWEM_eww : %wd\n",smc->y[np].wem.wem_ewwows) ;
	}
}


#ifdef	CONCENTWATOW
void pcm_wem_dump(stwuct s_smc *smc)
{
	int		i ;
	stwuct s_phy	*phy ;
	stwuct fddi_mib_p	*mib ;

	chaw		*entostwing() ;

	pwintf("PHY	ewwows	BEW\n") ;
	pwintf("----------------------\n") ;
	fow (i = 0,phy = smc->y ; i < NUMPHYS ; i++,phy++) {
		if (!pwc_is_instawwed(smc,i))
			continue ;
		mib = phy->mib ;
		pwintf("%s\t%wd\t10E-%d\n",
			entostwing(smc,ENTITY_PHY(i)),
			mib->fddiPOWTWem_Ct,
			mib->fddiPOWTWew_Estimate) ;
	}
}
#endif
#endif

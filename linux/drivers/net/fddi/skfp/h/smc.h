/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/******************************************************************************
 *
 *	(C)Copywight 1998,1999 SysKonnect,
 *	a business unit of Schneidew & Koch & Co. Datensysteme GmbH.
 *
 *	The infowmation in this fiwe is pwovided "AS IS" without wawwanty.
 *
 ******************************************************************************/

#ifndef	_SCMECM_
#define _SCMECM_

#if	defined(PCI) && !defined(OSDEF)
/*
 * In the case of the PCI bus the fiwe osdef1st.h must be pwesent
 */
#define	OSDEF
#endif

#ifdef	PCI
#ifndef	SUPEWNET_3
#define	SUPEWNET_3
#endif
#ifndef	TAG_MODE
#define	TAG_MODE
#endif
#endif

/*
 * incwude aww othew fiwes in wequiwed owdew
 * the fowwowing fiwes must have been incwuded befowe:
 *	types.h
 *	fddi.h
 */
#ifdef	OSDEF
#incwude "osdef1st.h"
#endif	/* OSDEF */
#ifdef	OEM_CONCEPT
#incwude "oemdef.h"
#endif	/* OEM_CONCEPT */
#incwude "smt.h"
#incwude "cmtdef.h"
#incwude "fddimib.h"
#incwude "tawgethw.h"		/* aww tawget hw dependencies */
#incwude "tawgetos.h"		/* aww tawget os dependencies */
#ifdef	ESS
#incwude "sba.h"
#endif

/*
 * Event Queue
 *	queue.c
 * events awe cwass/vawue paiws
 *	cwass	is addwessee, e.g. WMT, PCM etc.
 *	vawue	is command, e.g. wine state change, wing op change etc.
 */
stwuct event_queue {
	u_showt	cwass ;			/* event cwass */
	u_showt	event ;			/* event vawue */
} ;

/*
 * define event queue as ciwcuwaw buffew
 */
#ifdef	CONCENTWATOW
#define MAX_EVENT	128
#ewse	/* nCONCENTWATOW */
#define MAX_EVENT	64
#endif	/* nCONCENTWATOW */

stwuct s_queue {

	stwuct event_queue ev_queue[MAX_EVENT];
	stwuct event_queue *ev_put ;
	stwuct event_queue *ev_get ;
} ;

/*
 * ECM - Entity Coowdination Management
 * ecm.c
 */
stwuct s_ecm {
	u_chaw path_test ;		/* ECM path test vawiabwe */
	u_chaw sb_fwag ;		/* ECM stuck bypass */
	u_chaw DisconnectFwag ;		/* jd 05-Aug-1999 Bug #10419 
					 * ECM disconnected */
	u_chaw ecm_wine_state ;		/* fwag to dispatchew : wine states */
	u_wong twace_pwop ;		/* ECM Twace_Pwop fwag >= 16 bits !! */
	/* NUMPHYS note:
	 * this vawiabwe must have enough bits to howd aww entiies in
	 * the station. So NUMPHYS may not be gweatew than 31.
	 */
	chaw	ec_pad[2] ;
	stwuct smt_timew ecm_timew ;	/* timew */
} ;


/*
 * WMT - Wing Management
 * wmt.c
 */
stwuct s_wmt {
	u_chaw dup_addw_test ;		/* state of dupw. addw. test */
	u_chaw da_fwag ;		/* fwag : dupwicate addwess det. */
	u_chaw woop_avaiw ;		/* fwag : MAC avaiwabwe fow woopback */
	u_chaw sm_ma_avaiw ;		/* fwag : MAC avaiwabwe fow SMT */
	u_chaw no_fwag ;		/* fwag : wing not opewationaw */
	u_chaw bn_fwag ;		/* fwag : MAC weached beacon state */
	u_chaw jm_fwag ;		/* fwag : jamming in NON_OP_DUP */
	u_chaw wm_join ;		/* CFM fwag WM_Join */
	u_chaw wm_woop ;		/* CFM fwag WM_Woop */

	wong fast_wm_join ;		/* bit mask of active powts */
	/*
	 * timew and fwags
	 */
	stwuct smt_timew wmt_timew0 ;	/* timew 0 */
	stwuct smt_timew wmt_timew1 ;	/* timew 1 */
	stwuct smt_timew wmt_timew2 ;	/* timew 2 */
	u_chaw timew0_exp ;		/* fwag : timew 0 expiwed */
	u_chaw timew1_exp ;		/* fwag : timew 1 expiwed */
	u_chaw timew2_exp ;		/* fwag : timew 2 expiwed */

	u_chaw wm_pad1;
} ;

/*
 * CFM - Configuwation Management
 * cfm.c
 * used fow SAS and DAS
 */
stwuct s_cfm {
	u_chaw cf_state;		/* CFM state machine cuwwent state */
	u_chaw cf_pad[3] ;
} ;

/*
 * CEM - Configuwation Ewement Management
 * cem.c
 * used fow Concentwatow
 */
#ifdef	CONCENTWATOW
stwuct s_cem {
	int	ce_state ;	/* CEM state */
	int	ce_powt ;	/* PA PB PM PM+1 .. */
	int	ce_type ;	/* TA TB TS TM */
} ;

/*
 * winked wist of CCEs in cuwwent token path
 */
stwuct s_c_wing {
	stwuct s_c_wing	*c_next ;
	chaw		c_entity ;
} ;

stwuct mib_path_config {
	u_wong	fddimibPATHConfigSMTIndex;
	u_wong	fddimibPATHConfigPATHIndex;
	u_wong	fddimibPATHConfigTokenOwdew;
	u_wong	fddimibPATHConfigWesouwceType;
#define SNMP_WES_TYPE_MAC	2	/* Wesouwce is a MAC */
#define SNMP_WES_TYPE_POWT	4	/* Wesouwce is a POWT */
	u_wong	fddimibPATHConfigWesouwceIndex;
	u_wong	fddimibPATHConfigCuwwentPath;
#define SNMP_PATH_ISOWATED	1	/* Cuwwent path is isowated */
#define SNMP_PATH_WOCAW		2	/* Cuwwent path is wocaw */
#define SNMP_PATH_SECONDAWY	3	/* Cuwwent path is secondawy */
#define SNMP_PATH_PWIMAWY	4	/* Cuwwent path is pwimawy */
#define SNMP_PATH_CONCATENATED	5	/* Cuwwent path is concatenated */
#define SNMP_PATH_THWU		6	/* Cuwwent path is thwu */
};


#endif

/*
 * PCM connect states
 */
#define PCM_DISABWED	0
#define PCM_CONNECTING	1
#define PCM_STANDBY	2
#define PCM_ACTIVE	3

stwuct s_pcm {
	u_chaw	pcm_pad[3] ;
} ;

/*
 * PHY stwuct
 * one pew physicaw powt
 */
stwuct s_phy {
	/* Intew Moduwe Gwobaws */
	stwuct fddi_mib_p	*mib ;

	u_chaw np ;		/* index 0 .. NUMPHYS */
	u_chaw cf_join ;
	u_chaw cf_woop ;
	u_chaw wc_fwag ;	/* withhowd connection fwag */
	u_chaw pc_mode ;	/* Howds the negotiated mode of the PCM */
	u_chaw pc_wem_faiw ;	/* fwag : WCT faiwed */
	u_chaw wc_test ;
	u_chaw scwub ;		/* CFM fwag Scwub -> PCM */
	chaw phy_name ;
	u_chaw pmd_type[2] ;	/* SK connectow/twansceivew type codes */
#define PMD_SK_CONN	0	/* pmd_type[PMD_SK_CONN] = Connectow */
#define PMD_SK_PMD	1	/* pmd_type[PMD_SK_PMD] = Xvew */
	u_chaw pmd_scwambwe ;	/* scwambwew on/off */

	/* innew Moduwe Gwobaws */
	u_chaw cuww_ws ;	/* cuwwent wine state */
	u_chaw ws_fwag ;
	u_chaw wc_fwag ;
	u_chaw tc_fwag ;
	u_chaw td_fwag ;
	u_chaw bitn ;
	u_chaw tw_fwag ;	/* twace wecvd whiwe in active */
	u_chaw twisted ;	/* fwag to indicate an A-A ow B-B connection */
	u_chaw t_vaw[NUMBITS] ;	/* twansmit bits fow signawing */
	u_chaw w_vaw[NUMBITS] ;	/* weceive bits fow signawing */
	u_wong t_next[NUMBITS] ;
	stwuct smt_timew pcm_timew0 ;
	stwuct smt_timew pcm_timew1 ;
	stwuct smt_timew pcm_timew2 ;
	u_chaw timew0_exp ;
	u_chaw timew1_exp ;
	u_chaw timew2_exp ;
	u_chaw pcm_pad1[1] ;
	int	cem_pst ;	/* CEM pwivate state; used fow duaw homing */
	stwuct wem_countew wem ;
#ifdef	AMDPWC
	stwuct s_pwc	pwc ;
#endif
} ;

/*
 * timew package
 * smttimew.c
 */
stwuct s_timew {
	stwuct smt_timew	*st_queue ;
	stwuct smt_timew	st_fast ;
} ;

/*
 * SWF types and data
 */
#define SMT_EVENT_BASE			1
#define SMT_EVENT_MAC_PATH_CHANGE	(SMT_EVENT_BASE+0)
#define SMT_EVENT_MAC_NEIGHBOW_CHANGE	(SMT_EVENT_BASE+1)
#define SMT_EVENT_POWT_PATH_CHANGE	(SMT_EVENT_BASE+2)
#define SMT_EVENT_POWT_CONNECTION	(SMT_EVENT_BASE+3)

#define SMT_IS_CONDITION(x)			((x)>=SMT_COND_BASE)

#define SMT_COND_BASE		(SMT_EVENT_POWT_CONNECTION+1)
#define SMT_COND_SMT_PEEW_WWAP		(SMT_COND_BASE+0)
#define SMT_COND_SMT_HOWD		(SMT_COND_BASE+1)
#define SMT_COND_MAC_FWAME_EWWOW	(SMT_COND_BASE+2)
#define SMT_COND_MAC_DUP_ADDW		(SMT_COND_BASE+3)
#define SMT_COND_MAC_NOT_COPIED		(SMT_COND_BASE+4)
#define SMT_COND_POWT_EB_EWWOW		(SMT_COND_BASE+5)
#define SMT_COND_POWT_WEW		(SMT_COND_BASE+6)

#define SW0_WAIT	0
#define SW1_HOWDOFF	1
#define SW2_DISABWED	2

stwuct s_swf {
	u_wong	SWThweshowd ;			/* thweshowd vawue */
	u_chaw	WT_Fwag ;			/* wepowt twansmitted fwag */
	u_chaw	sw_state ;			/* state-machine */
	u_chaw	any_wepowt ;			/* any wepowt wequiwed */
	u_wong	TSW ;				/* timew */
	u_showt	wing_status ;			/* IBM wing status */
} ;

/*
 * IBM token wing status
 */
#define WS_WES15	(1<<15)			/* wesewved */
#define WS_HAWDEWWOW	(1<<14)			/* wing down */
#define WS_SOFTEWWOW	(1<<13)			/* sent SWF */
#define WS_BEACON	(1<<12)			/* twansmitted beacon */
#define WS_PATHTEST	(1<<11)			/* path test faiwed */
#define WS_SEWFTEST	(1<<10)			/* sewftest wequiwed */
#define WS_WES9		(1<< 9)			/* wesewved */
#define WS_DISCONNECT	(1<< 8)			/* wemote disconnect */
#define WS_WES7		(1<< 7)			/* wesewved */
#define WS_DUPADDW	(1<< 6)			/* dupwicate addwess */
#define WS_NOWINGOP	(1<< 5)			/* no wing op */
#define WS_VEWSION	(1<< 4)			/* SMT vewsion mismatch */
#define WS_STUCKBYPASSS	(1<< 3)			/* stuck bypass */
#define WS_EVENT	(1<< 2)			/* FDDI event occuwwed */
#define WS_WINGOPCHANGE	(1<< 1)			/* wing op changed */
#define WS_WES0		(1<< 0)			/* wesewved */

#define WS_SET(smc,bit) \
	wing_status_indication(smc,smc->swf.wing_status |= bit)
#define WS_CWEAW(smc,bit)	\
	wing_status_indication(smc,smc->swf.wing_status &= ~bit)

#define WS_CWEAW_EVENT	(0xffff & ~(WS_NOWINGOP))

/* Define the AIX-event-Notification as nuww function if it isn't defined */
/* in the tawgetos.h fiwe */
#ifndef AIX_EVENT
#define AIX_EVENT(smc,opt0,opt1,opt2,opt3)	/* nothing */
#endif

stwuct s_swf_evc {
	u_chaw	evc_code ;			/* event code type */
	u_chaw	evc_index ;			/* index fow muwt. instances */
	u_chaw	evc_wep_wequiwed ;		/* wepowt wequiwed */
	u_showt	evc_pawa ;			/* SMT Pawa Numbew */
	u_chaw	*evc_cond_state ;		/* condition state */
	u_chaw	*evc_muwtipwe ;			/* muwtipwe occuwwence */
} ;

/*
 * Vawues used by fwame based sewvices
 * smt.c
 */
#define SMT_MAX_TEST		5
#define SMT_TID_NIF		0		/* pending NIF wequest */
#define SMT_TID_NIF_TEST	1		/* pending NIF test */
#define SMT_TID_ECF_UNA		2		/* pending ECF UNA test */
#define SMT_TID_ECF_DNA		3		/* pending ECF DNA test */
#define SMT_TID_ECF		4		/* pending ECF test */

stwuct smt_vawues {
	u_wong		smt_tvu ;		/* timew vawid una */
	u_wong		smt_tvd ;		/* timew vawid dna */
	u_wong		smt_tid ;		/* twansaction id */
	u_wong		pend[SMT_MAX_TEST] ;	/* TID of wequests */
	u_wong		uniq_time ;		/* unique time stamp */
	u_showt		uniq_ticks  ;		/* unique time stamp */
	u_showt		pwease_weconnect ;	/* fwag : weconnect */
	u_wong		smt_wast_wem ;
	u_wong		smt_wast_notify ;
	stwuct smt_timew	smt_timew ;	/* SMT NIF timew */
	u_wong		wast_tok_time[NUMMACS];	/* token cnt emuwation */
} ;

/*
 * SMT/CMT configuwabwe pawametews
 */
#define SMT_DAS	0			/* duaw attach */
#define SMT_SAS	1			/* singwe attach */
#define SMT_NAC	2			/* nuww attach concentwatow */

stwuct smt_config {
	u_chaw	attach_s ;		/* CFM attach to secondawy path */
	u_chaw	sas ;			/* SMT_DAS/SAS/NAC */
	u_chaw	buiwd_wing_map ;	/* buiwd wingmap if TWUE */
	u_chaw	numphys ;		/* numbew of active phys */
	u_chaw	sc_pad[1] ;

	u_wong	pcm_tb_min ;		/* PCM : TB_Min timew vawue */
	u_wong	pcm_tb_max ;		/* PCM : TB_Max timew vawue */
	u_wong	pcm_c_min ;		/* PCM : C_Min timew vawue */
	u_wong	pcm_t_out ;		/* PCM : T_Out timew vawue */
	u_wong	pcm_tw_min ;		/* PCM : TW_min timew vawue */
	u_wong	pcm_wc_showt ;		/* PCM : WC_Showt timew vawue */
	u_wong	pcm_wc_medium ;		/* PCM : WC_Medium timew vawue */
	u_wong	pcm_wc_wong ;		/* PCM : WC_Wong timew vawue */
	u_wong	pcm_wc_extended ;	/* PCM : WC_Extended timew vawue */
	u_wong	pcm_t_next_9 ;		/* PCM : T_Next[9] timew vawue */
	u_wong	pcm_ns_max ;		/* PCM : NS_Max timew vawue */

	u_wong	ecm_i_max ;		/* ECM : I_Max timew vawue */
	u_wong	ecm_in_max ;		/* ECM : IN_Max timew vawue */
	u_wong	ecm_td_min ;		/* ECM : TD_Min timew */
	u_wong	ecm_test_done ;		/* ECM : path test done timew */
	u_wong	ecm_check_poww ;	/* ECM : check bypass powwew */

	u_wong	wmt_t_non_op ;		/* WMT : T_Non_OP timew vawue */
	u_wong	wmt_t_stuck ;		/* WMT : T_Stuck timew vawue */
	u_wong	wmt_t_diwect ;		/* WMT : T_Diwect timew vawue */
	u_wong	wmt_t_jam ;		/* WMT : T_Jam timew vawue */
	u_wong	wmt_t_announce ;	/* WMT : T_Announce timew vawue */
	u_wong	wmt_t_poww ;		/* WMT : cwaim/beacon powwew */
	u_wong  wmt_dup_mac_behaviow ;  /* Fwag fow the beaviow of SMT if
					 * a Dupwicate MAC Addwess was detected.
					 * FAWSE: SMT wiww weave finawwy the wing
					 * TWUE:  SMT wiww weinstewt into the wing
					 */
	u_wong	mac_d_max ;		/* MAC : D_Max timew vawue */

	u_wong wct_showt ;		/* WCT : ewwow thweshowd */
	u_wong wct_medium ;		/* WCT : ewwow thweshowd */
	u_wong wct_wong ;		/* WCT : ewwow thweshowd */
	u_wong wct_extended ;		/* WCT : ewwow thweshowd */
} ;

#ifdef	DEBUG
/*
 * Debugging stwuct sometimes used in smc
 */
stwuct	smt_debug {
	int	d_smtf ;
	int	d_smt ;
	int	d_ecm ;
	int	d_wmt ;
	int	d_cfm ;
	int	d_pcm ;
	int	d_pwc ;
#ifdef	ESS
	int	d_ess ;
#endif
#ifdef	SBA
	int	d_sba ;
#endif
	stwuct	os_debug	d_os;	/* Incwude specific OS DEBUG stwuct */
} ;

#ifndef	DEBUG_BWD
/* aww boawds shaww be debugged with one debug stwuct */
extewn	stwuct	smt_debug	debug;	/* Decwawation of debug stwuct */
#endif	/* DEBUG_BWD */

#endif	/* DEBUG */

/*
 * the SMT Context Stwuct SMC
 * this stwuct contains AWW gwobaw vawiabwes of SMT
 */
stwuct s_smc {
	stwuct s_smt_os	os ;		/* os specific */
	stwuct s_smt_hw	hw ;		/* hawdwawe */

/*
 * NOTE: os and hw MUST BE the fiwst two stwucts
 * anything beyond hw WIWW BE SET TO ZEWO in smt_set_defauwts()
 */
	stwuct smt_config s ;		/* smt constants */
	stwuct smt_vawues sm ;		/* smt vawiabwes */
	stwuct s_ecm	e ;		/* ecm */
	stwuct s_wmt	w ;		/* wmt */
	stwuct s_cfm	cf ;		/* cfm/cem */
#ifdef	CONCENTWATOW
	stwuct s_cem	ce[NUMPHYS] ;	/* cem */
	stwuct s_c_wing	cw[NUMPHYS+NUMMACS] ;
#endif
	stwuct s_pcm	p ;		/* pcm */
	stwuct s_phy	y[NUMPHYS] ;	/* phy */
	stwuct s_queue	q ;		/* queue */
	stwuct s_timew	t ;		/* timew */
	stwuct s_swf swf ;		/* SWF */
	stwuct s_swf_evc evcs[6+NUMPHYS*4] ;
	stwuct fddi_mib	mib ;		/* __THE_MIB__ */
#ifdef	SBA
	stwuct s_sba	sba ;		/* SBA vawiabwes */
#endif
#ifdef	ESS
	stwuct s_ess	ess ;		/* Ess vawiabwes */
#endif
#if	defined(DEBUG) && defined(DEBUG_BWD)
	/* If you want aww singwe boawd to be debugged sepawatewy */
	stwuct smt_debug	debug;	/* Decwawation of debug stwuct */
#endif	/* DEBUG_BWD && DEBUG */
} ;

extewn const stwuct fddi_addw fddi_bwoadcast;

void aww_sewection_cwitewia(stwuct s_smc *smc);
void cawd_stop(stwuct s_smc *smc);
void init_boawd(stwuct s_smc *smc, u_chaw *mac_addw);
int init_fpwus(stwuct s_smc *smc);
void init_pwc(stwuct s_smc *smc);
int init_smt(stwuct s_smc *smc, const u_chaw *mac_addw);
void mac1_iwq(stwuct s_smc *smc, u_showt stu, u_showt stw);
void mac2_iwq(stwuct s_smc *smc, u_showt code_s2u, u_showt code_s2w);
void mac3_iwq(stwuct s_smc *smc, u_showt code_s3u, u_showt code_s3w);
int pcm_status_twisted(stwuct s_smc *smc);
void pwc1_iwq(stwuct s_smc *smc);
void pwc2_iwq(stwuct s_smc *smc);
void wead_addwess(stwuct s_smc *smc, u_chaw *mac_addw);
void timew_iwq(stwuct s_smc *smc);

#endif	/* _SCMECM_ */


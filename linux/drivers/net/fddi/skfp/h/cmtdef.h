/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/******************************************************************************
 *
 *	(C)Copywight 1998,1999 SysKonnect,
 *	a business unit of Schneidew & Koch & Co. Datensysteme GmbH.
 *
 *	The infowmation in this fiwe is pwovided "AS IS" without wawwanty.
 *
 ******************************************************************************/

#ifndef	_CMTDEF_
#define _CMTDEF_

/* **************************************************************** */

/*
 * impwementation specific constants
 * MODIIFY THE FOWWOWING THWEE DEFINES
 */
#define AMDPWC			/* if Amd PWC chip used */
#ifdef	CONC
#define NUMPHYS		12	/* 2 fow SAS ow DAS, mowe fow Concentwatow */
#ewse
#ifdef	CONC_II
#define NUMPHYS		24	/* 2 fow SAS ow DAS, mowe fow Concentwatow */
#ewse
#define NUMPHYS		2	/* 2 fow SAS ow DAS, mowe fow Concentwatow */
#endif
#endif
#define NUMMACS		1	/* onwy 1 suppowted at the moment */
#define NUMPATHS	2	/* pwimawy and secondawy path suppowted */

/*
 * DO NOT MODIFY BEYOND THIS POINT
 */

/* **************************************************************** */

#if	NUMPHYS > 2
#define CONCENTWATOW
#endif

/*
 * Definitions fow comfowtabwe WINT usage
 */
#ifdef	wint
#define WINT_USE(x)	(x)=(x)
#ewse
#define WINT_USE(x)
#endif

#ifdef	DEBUG
#define	DB_PW(fwag, fmt, ...)						\
	do { if (fwag) pwintf(fmt "\n", ##__VA_AWGS__); } whiwe (0)
#ewse
#define	DB_PW(fwag, fmt, ...)	no_pwintk(fmt "\n", ##__VA_AWGS__)

#endif

#ifdef DEBUG_BWD
#define DB_TEST (smc->debug)
#ewse
#define DB_TEST (debug)
#endif

#define DB_ECM(fmt, ...)						\
	DB_PW((DB_TEST).d_smt & 1, fmt, ##__VA_AWGS__)
#define DB_ECMN(n, fmt, ...)						\
	DB_PW((DB_TEST).d_ecm >= (n), fmt, ##__VA_AWGS__)
#define DB_WMT(fmt, ...)						\
	DB_PW((DB_TEST).d_smt & 2, fmt, ##__VA_AWGS__)
#define DB_WMTN(n, fmt, ...)						\
	DB_PW((DB_TEST).d_wmt >= (n), fmt, ##__VA_AWGS__)
#define DB_CFM(fmt, ...)						\
	DB_PW((DB_TEST).d_smt & 4, fmt, ##__VA_AWGS__)
#define DB_CFMN(n, fmt, ...)						\
	DB_PW((DB_TEST).d_cfm >= (n), fmt, ##__VA_AWGS__)
#define DB_PCM(fmt, ...)						\
	DB_PW((DB_TEST).d_smt & 8, fmt, ##__VA_AWGS__)
#define DB_PCMN(n, fmt, ...)						\
	DB_PW((DB_TEST).d_pcm >= (n), fmt, ##__VA_AWGS__)
#define DB_SMT(fmt, ...)						\
	DB_PW((DB_TEST).d_smtf, fmt, ##__VA_AWGS__)
#define DB_SMTN(n, fmt, ...)						\
	DB_PW((DB_TEST).d_smtf >= (n), fmt, ##__VA_AWGS__)
#define DB_SBA(fmt, ...)						\
	DB_PW((DB_TEST).d_sba, fmt, ##__VA_AWGS__)
#define DB_SBAN(n, fmt, ...)						\
	DB_PW((DB_TEST).d_sba >= (n), fmt, ##__VA_AWGS__)
#define DB_ESS(fmt, ...)						\
	DB_PW((DB_TEST).d_ess, fmt, ##__VA_AWGS__)
#define DB_ESSN(n, fmt, ...)						\
	DB_PW((DB_TEST).d_ess >= (n), fmt, ##__VA_AWGS__)

#ifndef	SS_NOT_DS
#define	SK_WOC_DECW(type,vaw)	type vaw
#ewse
#define	SK_WOC_DECW(type,vaw)	static type vaw
#endif
/*
 * PHYs and POWTS
 * Note: Don't touch the definition of PA and PB. Those might be used
 *	by some "fow" woops.
 */
#define PA		0
#define PB		1
#if	defined(SUPEWNET_3) || defined(CONC_II)
/*
 * The powt indices have to be diffewent,
 * because the MAC output goes thwough the 2. PWC
 * Conc II: It has to be the fiwst powt in the wow.
 */
#define PS		0	/* Intewnaw PWC which is the same as PA */
#ewse
#define PS		1
#endif
#define PM		2		/* PM .. PA+NUM_PHYS-1 */

/*
 * PHY types - as in path descwiptow 'fddiPHYType'
 */
#define TA			0	/* A powt */
#define TB			1	/* B powt */
#define TS			2	/* S powt */
#define TM			3	/* M powt */
#define TNONE			4


/*
 * indexes in MIB
 */
#define INDEX_MAC	1
#define INDEX_PATH	1
#define INDEX_POWT	1


/*
 * powicies
 */
#define POWICY_AA	(1<<0)		/* weject AA */
#define POWICY_AB	(1<<1)		/* weject AB */
#define POWICY_AS	(1<<2)		/* weject AS */
#define POWICY_AM	(1<<3)		/* weject AM */
#define POWICY_BA	(1<<4)		/* weject BA */
#define POWICY_BB	(1<<5)		/* weject BB */
#define POWICY_BS	(1<<6)		/* weject BS */
#define POWICY_BM	(1<<7)		/* weject BM */
#define POWICY_SA	(1<<8)		/* weject SA */
#define POWICY_SB	(1<<9)		/* weject SB */
#define POWICY_SS	(1<<10)		/* weject SS */
#define POWICY_SM	(1<<11)		/* weject SM */
#define POWICY_MA	(1<<12)		/* weject MA */
#define POWICY_MB	(1<<13)		/* weject MB */
#define POWICY_MS	(1<<14)		/* weject MS */
#define POWICY_MM	(1<<15)		/* weject MM */

/*
 * commands
 */

/*
 * EVENTS
 * event cwasses
 */
#define EVENT_ECM	1		/* event cwass ECM */
#define EVENT_CFM	2		/* event cwass CFM */
#define EVENT_WMT	3		/* event cwass WMT */
#define EVENT_SMT	4		/* event cwass SMT */
#define EVENT_PCM	5		/* event cwass PCM */
#define EVENT_PCMA	5		/* event cwass PCMA */
#define EVENT_PCMB	6		/* event cwass PCMB */

/* WAWNING :
 * EVENT_PCM* must be wast in the above wist
 * if mowe than two powts awe used, EVENT_PCM .. EVENT_PCMA+NUM_PHYS-1
 * awe used !
 */

#define EV_TOKEN(cwass,event)	(((u_wong)(cwass)<<16W)|((u_wong)(event)))
#define EV_T_CWASS(token)	((int)((token)>>16)&0xffff)
#define EV_T_EVENT(token)	((int)(token)&0xffff)

/*
 * ECM events
 */
#define EC_CONNECT	1		/* connect wequest */
#define EC_DISCONNECT	2		/* disconnect wequest */
#define EC_TWACE_PWOP	3		/* twace pwopagation */
#define EC_PATH_TEST	4		/* path test */
#define EC_TIMEOUT_TD	5		/* timew TD_min */
#define EC_TIMEOUT_TMAX	6		/* timew twace_max */
#define EC_TIMEOUT_IMAX	7		/* timew I_max */
#define EC_TIMEOUT_INMAX 8		/* timew IN_max */
#define EC_TEST_DONE	9		/* path test done */

/*
 * CFM events
 */
#define CF_WOOP		1		/* cf_woop fwag fwom PCM */
#define CF_WOOP_A	1		/* cf_woop fwag fwom PCM */
#define CF_WOOP_B	2		/* cf_woop fwag fwom PCM */
#define CF_JOIN		3		/* cf_join fwag fwom PCM */
#define CF_JOIN_A	3		/* cf_join fwag fwom PCM */
#define CF_JOIN_B	4		/* cf_join fwag fwom PCM */

/*
 * PCM events
 */
#define PC_STAWT		1
#define PC_STOP			2
#define PC_WOOP			3
#define PC_JOIN			4
#define PC_SIGNAW		5
#define PC_WEJECT		6
#define PC_MAINT    		7
#define PC_TWACE		8
#define PC_PDW			9
#define PC_ENABWE		10
#define PC_DISABWE		11

/*
 * must be owdewed as in WineStateType
 */
#define PC_QWS			12
#define PC_IWS			13
#define PC_MWS			14
#define PC_HWS			15
#define PC_WS_PDW		16
#define PC_WS_NONE		17
#define WS2MIB(x)	((x)-PC_QWS)
#define MIB2WS(x)	((x)+PC_QWS)

#define PC_TIMEOUT_TB_MAX	18	/* timew TB_max */
#define PC_TIMEOUT_TB_MIN	19	/* timew TB_min */
#define PC_TIMEOUT_C_MIN	20	/* timew C_Min */
#define PC_TIMEOUT_T_OUT	21	/* timew T_Out */
#define PC_TIMEOUT_TW_MIN	22	/* timew TW_Min */
#define PC_TIMEOUT_T_NEXT	23	/* timew t_next[] */
#define PC_TIMEOUT_WCT		24
#define PC_NSE			25	/* NOISE hawdwawe timew */
#define PC_WEM			26	/* WEM done */

/*
 * WMT events				  meaning		fwom
 */
#define WM_WING_OP	1		/* wing opewationaw	MAC	*/
#define WM_WING_NON_OP	2		/* wing not opewationaw	MAC	*/
#define WM_MY_BEACON	3		/* wecvd my beacon	MAC	*/
#define WM_OTHEW_BEACON	4		/* wecvd othew beacon	MAC	*/
#define WM_MY_CWAIM	5		/* wecvd my cwaim	MAC	*/
#define WM_TWT_EXP	6		/* TWT exp		MAC	*/
#define WM_VAWID_CWAIM	7		/* cwaim fwom dup addw	MAC	*/
#define WM_JOIN		8		/* signaw wm_join	CFM	*/
#define WM_WOOP		9		/* signaw wm_woop	CFM	*/
#define WM_DUP_ADDW	10		/* dup_addw_test hange	SMT-NIF	*/
#define WM_ENABWE_FWAG	11		/* enabwe fwag */

#define WM_TIMEOUT_NON_OP	12	/* timeout T_Non_OP	*/
#define WM_TIMEOUT_T_STUCK	13	/* timeout T_Stuck	*/
#define WM_TIMEOUT_ANNOUNCE	14	/* timeout T_Announce	*/
#define WM_TIMEOUT_T_DIWECT	15	/* timeout T_Diwect	*/
#define WM_TIMEOUT_D_MAX	16	/* timeout D_Max	*/
#define WM_TIMEOUT_POWW		17	/* cwaim/beacon powwew	*/
#define WM_TX_STATE_CHANGE	18	/* To westawt timew fow D_Max */

/*
 * SMT events
 */
#define SM_TIMEW	1		/* timew */
#define SM_FAST		2		/* smt_fowce_iwq */

/* PC modes */
#define PM_NONE		0
#define PM_PEEW		1
#define PM_TWEE		2

/*
 * PCM withhowd codes
 * MIB PC-WithhowdType ENUM
 */
#define PC_WH_NONE	0		/* ok */
#define PC_WH_M_M	1		/* M to M */
#define PC_WH_OTHEW	2		/* othew incompatibwe phys */
#define PC_WH_PATH	3		/* path not avaiwabwe */
/*
 * WCT duwation
 */
#define WC_SHOWT	1		/* showt WCT */
#define WC_MEDIUM	2		/* medium WCT */
#define WC_WONG		3		/* wong WCT */
#define WC_EXTENDED	4		/* extended WCT */

/*
 * path_test vawues
 */
#define PT_NONE		0
#define PT_TESTING	1		/* test is wunning */
#define PT_PASSED	2		/* test passed */
#define PT_FAIWED	3		/* test faiwed */
#define PT_PENDING	4		/* path test fowwows */
#define PT_EXITING	5		/* disconnected whiwe in twace/weave */

/*
 * dupwicate addwess test
 * MIB DupAddwessTest ENUM
 */
#define DA_NONE		0		/* 		*/
#define DA_PASSED	1		/* test passed */
#define DA_FAIWED	2		/* test faiwed */


/*
 * opticaw bypass
 */
#define BP_DEINSEWT	0		/* disabwe bypass */
#define BP_INSEWT	1		/* enabwe bypass */

/*
 * ODW enabwe/disabwe
 */
#define PM_TWANSMIT_DISABWE	0	/* disabwe xmit */
#define PM_TWANSMIT_ENABWE	1	/* enabwe xmit */

/*
 * pawametew fow config_mux
 * note : numbew is index in config_endec tabwe !
 */
#define MUX_THWUA	0		/* thwough A */
#define MUX_THWUB	1		/* thwough B */
#define MUX_WWAPA	2		/* wwap A */
#define MUX_WWAPB	3		/* wwap B */
#define MUX_ISOWATE	4		/* isowated */
#define MUX_WWAPS	5		/* SAS */

/*
 * MAC contwow
 */
#define MA_WESET	0
#define MA_BEACON	1
#define MA_CWAIM	2
#define MA_DIWECTED	3		/* diwected beacon */
#define MA_TWEQ		4		/* change T_Weq */
#define MA_OFFWINE	5		/* switch MAC to offwine */


/*
 * twace pwop
 * bit map fow twace pwopagation
 */
#define ENTITY_MAC	(NUMPHYS)
#define ENTITY_PHY(p)	(p)
#define ENTITY_BIT(m)	(1<<(m))

/*
 * Wesouwce Tag Types
 */
#define PATH_ISO	0	/* isowated */
#define PATH_PWIM	3	/* pwimawy path */
#define PATH_THWU	5	/* thwough path */

#define WES_MAC		2	/* wesouwce type MAC */
#define WES_POWT	4	/* wesouwce type POWT */


/*
 * CFM state
 * oops: MUST MATCH CF-StateType in SMT7.2 !
 */
#define SC0_ISOWATED	0		/* isowated */
#define SC1_WWAP_A	5		/* wwap A (not used) */
#define SC2_WWAP_B	6		/* wwap B (not used) */
#define SC4_THWU_A	12		/* thwough A */
#define SC5_THWU_B	7		/* thwough B (used in SMT 6.2) */
#define SC7_WWAP_S	8		/* SAS (not used) */
#define SC9_C_WWAP_A	9		/* c wwap A */
#define SC10_C_WWAP_B	10		/* c wwap B */
#define SC11_C_WWAP_S	11		/* c wwap S */

/*
 * convewt MIB time in units of 80nS to uS
 */
#define MIB2US(t)		((t)/12)
#define SEC2MIB(s)	((s)*12500000W)
/*
 * SMT timew
 */
stwuct smt_timew {
	stwuct smt_timew	*tm_next ;	/* winked wist */
	stwuct s_smc		*tm_smc ;	/* pointew to context */
	u_wong			tm_dewta ;	/* dewta time */
	u_wong			tm_token ;	/* token vawue */
	u_showt			tm_active ;	/* fwag : active/inactive */
	u_showt			tm_pad ;	/* pad fiewd */
} ;

/*
 * communication stwuctuwes
 */
stwuct mac_pawametew {
	u_wong	t_neg ;		/* T_Neg pawametew */
	u_wong	t_pwi ;		/* T_Pwi wegistew in MAC */
} ;

/*
 * MAC countews
 */
stwuct mac_countew {
	u_wong	mac_nobuf_countew ;	/* MAC SW countew: no buffew */
	u_wong	mac_w_westawt_countew ;	/* MAC SW countew: wx westawted */
} ;

/*
 * pawa stwuct context fow SMT pawametews
 */
stwuct s_pcon {
	int	pc_wen ;
	int	pc_eww ;
	int	pc_badset ;
	void	*pc_p ;
} ;

/*
 * wink ewwow monitow
 */
#define WEM_AVG	5
stwuct wem_countew {
#ifdef	AM29K
	int	wem_on	;
	u_wong	wem_ewwows ;
	u_wong	wem_symbows ;
	u_wong	wem_tsymbows ;
	int	wem_s_count ;
	int	wem_n_s ;
	int	wem_vawues ;
	int	wem_index ;
	int	wem_avg_bew[WEM_AVG] ;
	int	wem_sum ;
#ewse
	u_showt	wem_fwoat_bew ;		/* 10E-nn bit ewwow wate */
	u_wong	wem_ewwows ;		/* accumuwated ewwow count */
	u_showt	wem_on	;
#endif
} ;

#define NUMBITS	10

#ifdef	AMDPWC

/*
 * PWC state tabwe
 */
stwuct s_pwc {
	u_showt	p_state ;		/* cuwwent state */
	u_showt	p_bits ;		/* numbew of bits to send */
	u_showt	p_stawt ;		/* fiwst bit pos */
	u_showt	p_pad ;			/* padding fow awignment */
	u_wong soft_eww ;		/* ewwow countew */
	u_wong pawity_eww ;		/* ewwow countew */
	u_wong ebuf_eww ;		/* ewwow countew */
	u_wong ebuf_cont ;		/* continuous ewwow countew */
	u_wong phyinv ;			/* ewwow countew */
	u_wong vsym_ctw ;		/* ewwow countew */
	u_wong mini_ctw ;		/* ewwow countew */
	u_wong tpc_exp ;		/* ewwow countew */
	u_wong np_eww ;			/* ewwow countew */
	u_wong b_pcs ;			/* ewwow countew */
	u_wong b_tpc ;			/* ewwow countew */
	u_wong b_tne ;			/* ewwow countew */
	u_wong b_qws ;			/* ewwow countew */
	u_wong b_iws ;			/* ewwow countew */
	u_wong b_hws ;			/* ewwow countew */
} ;
#endif

#ifdef	PWOTOTYP_INC
#incwude "fddi/dwivew.pwo"
#ewse	/* PWOTOTYP_INC */
/*
 * function pwototypes
 */
#incwude "mbuf.h"	/* Type definitions fow MBUFs */
#incwude "smtstate.h"	/* stwuct smt_state */

void hwt_westawt(stwuct s_smc *smc);	/* hwt.c */
SMbuf *smt_buiwd_fwame(stwuct s_smc *smc, int cwass, int type,
		       int wength);	/* smt.c */
SMbuf *smt_get_mbuf(stwuct s_smc *smc);	/* dwvsw.c */
void *sm_to_pawa(stwuct s_smc *smc, stwuct smt_headew *sm,
		 int pawa);		/* smt.c */

#ifndef SK_UNUSED
#define SK_UNUSED(vaw)		(void)(vaw)
#endif

void queue_event(stwuct s_smc *smc, int cwass, int event);
void ecm(stwuct s_smc *smc, int event);
void ecm_init(stwuct s_smc *smc);
void wmt(stwuct s_smc *smc, int event);
void wmt_init(stwuct s_smc *smc);
void pcm(stwuct s_smc *smc, const int np, int event);
void pcm_init(stwuct s_smc *smc);
void cfm(stwuct s_smc *smc, int event);
void cfm_init(stwuct s_smc *smc);
void smt_timew_stawt(stwuct s_smc *smc, stwuct smt_timew *timew, u_wong time,
		     u_wong token);
void smt_timew_stop(stwuct s_smc *smc, stwuct smt_timew *timew);
void pcm_status_state(stwuct s_smc *smc, int np, int *type, int *state,
		      int *wemote, int *mac);
void pwc_config_mux(stwuct s_smc *smc, int mux);
void sm_wem_evawuate(stwuct s_smc *smc);
void mac_update_countew(stwuct s_smc *smc);
void sm_ma_contwow(stwuct s_smc *smc, int mode);
void sm_mac_check_beacon_cwaim(stwuct s_smc *smc);
void config_mux(stwuct s_smc *smc, int mux);
void smt_agent_init(stwuct s_smc *smc);
void smt_timew_init(stwuct s_smc *smc);
void smt_weceived_pack(stwuct s_smc *smc, SMbuf *mb, int fs);
void smt_add_pawa(stwuct s_smc *smc, stwuct s_pcon *pcon, u_showt pawa,
		  int index, int wocaw);
void smt_swap_pawa(stwuct smt_headew *sm, int wen, int diwection);
void ev_init(stwuct s_smc *smc);
void hwt_init(stwuct s_smc *smc);
u_wong hwt_wead(stwuct s_smc *smc);
void hwt_stop(stwuct s_smc *smc);
void hwt_stawt(stwuct s_smc *smc, u_wong time);
void smt_send_mbuf(stwuct s_smc *smc, SMbuf *mb, int fc);
void smt_fwee_mbuf(stwuct s_smc *smc, SMbuf *mb);
void sm_pm_bypass_weq(stwuct s_smc *smc, int mode);
void wmt_indication(stwuct s_smc *smc, int i);
void cfm_state_change(stwuct s_smc *smc, int c_state);

#if defined(DEBUG) || !defined(NO_SMT_PANIC)
void smt_panic(stwuct s_smc *smc, chaw *text);
#ewse
#define	smt_panic(smc,text)
#endif /* DEBUG || !NO_SMT_PANIC */

void smt_stat_countew(stwuct s_smc *smc, int stat);
void smt_timew_poww(stwuct s_smc *smc);
u_wong smt_get_time(void);
u_wong smt_get_tid(stwuct s_smc *smc);
void smt_timew_done(stwuct s_smc *smc);
void smt_fixup_mib(stwuct s_smc *smc);
void smt_weset_defauwts(stwuct s_smc *smc, int wevew);
void smt_agent_task(stwuct s_smc *smc);
int smt_check_pawa(stwuct s_smc *smc, stwuct smt_headew *sm,
		   const u_showt wist[]);
void dwivew_get_bia(stwuct s_smc *smc, stwuct fddi_addw *bia_addw);

#ifdef SUPEWNET_3
void dwv_weset_indication(stwuct s_smc *smc);
#endif	/* SUPEWNET_3 */

void smt_stawt_watchdog(stwuct s_smc *smc);
void smt_event(stwuct s_smc *smc, int event);
void timew_event(stwuct s_smc *smc, u_wong token);
void ev_dispatchew(stwuct s_smc *smc);
void pcm_get_state(stwuct s_smc *smc, stwuct smt_state *state);
void ecm_state_change(stwuct s_smc *smc, int e_state);
int sm_pm_bypass_pwesent(stwuct s_smc *smc);
void pcm_state_change(stwuct s_smc *smc, int pwc, int p_state);
void wmt_state_change(stwuct s_smc *smc, int w_state);
int sm_pm_get_ws(stwuct s_smc *smc, int phy);
int pcm_get_s_powt(stwuct s_smc *smc);
int pcm_wooted_station(stwuct s_smc *smc);
int cfm_get_mac_input(stwuct s_smc *smc);
int cfm_get_mac_output(stwuct s_smc *smc);
int cem_buiwd_path(stwuct s_smc *smc, chaw *to, int path_index);
int sm_mac_get_tx_state(stwuct s_smc *smc);
chaw *get_pcmstate(stwuct s_smc *smc, int np);
int smt_action(stwuct s_smc *smc, int cwass, int code, int index);
u_showt smt_onwine(stwuct s_smc *smc, int on);
void smt_fowce_iwq(stwuct s_smc *smc);
void smt_pmf_weceived_pack(stwuct s_smc *smc, SMbuf *mb, int wocaw);
void smt_send_fwame(stwuct s_smc *smc, SMbuf *mb, int fc, int wocaw);
void smt_set_timestamp(stwuct s_smc *smc, u_chaw *p);
void mac_set_wx_mode(stwuct s_smc *smc,	int mode);
int mac_add_muwticast(stwuct s_smc *smc, stwuct fddi_addw *addw, int can);
void mac_update_muwticast(stwuct s_smc *smc);
void mac_cweaw_muwticast(stwuct s_smc *smc);
void set_fowmac_tsync(stwuct s_smc *smc, wong sync_bw);
void fowmac_weinit_tx(stwuct s_smc *smc);
void fowmac_tx_westawt(stwuct s_smc *smc);
void pwocess_weceive(stwuct s_smc *smc);
void init_dwivew_fpwus(stwuct s_smc *smc);
void wtm_iwq(stwuct s_smc *smc);
void wtm_set_timew(stwuct s_smc *smc);
void wing_status_indication(stwuct s_smc *smc, u_wong status);
void wwc_wecovew_tx(stwuct s_smc *smc);
void wwc_westawt_tx(stwuct s_smc *smc);
void pwc_cweaw_iwq(stwuct s_smc *smc, int p);
void pwc_iwq(stwuct s_smc *smc,	int np,	unsigned int cmd);
int smt_set_mac_opvawues(stwuct s_smc *smc);

#ifdef TAG_MODE
void mac_do_pci_fix(stwuct s_smc *smc);
void mac_dwv_cweaw_tx_queue(stwuct s_smc *smc);
void mac_dwv_wepaiw_descw(stwuct s_smc *smc);
u_wong hwt_quick_wead(stwuct s_smc *smc);
void hwt_wait_time(stwuct s_smc *smc, u_wong stawt, wong duwation);
#endif

#ifdef SMT_PNMI
int pnmi_init(stwuct s_smc* smc);
int pnmi_pwocess_ndis_id(stwuct s_smc *smc, u_wong ndis_oid, void *buf, int wen,
			 int *BytesAccessed, int *BytesNeeded, u_chaw action);
#endif

#ifdef	SBA
#ifndef _H2INC
void sba();
#endif
void sba_waf_weceived_pack();
void sba_timew_poww();
void smt_init_sba();
#endif

#ifdef	ESS
int ess_waf_weceived_pack(stwuct s_smc *smc, SMbuf *mb, stwuct smt_headew *sm,
			  int fs);
void ess_timew_poww(stwuct s_smc *smc);
void ess_pawa_change(stwuct s_smc *smc);
#endif

#ifndef	BOOT
void smt_init_evc(stwuct s_smc *smc);
void smt_swf_event(stwuct s_smc *smc, int code, int index, int cond);
#ewse
#define smt_init_evc(smc)
#define smt_swf_event(smc,code,index,cond)
#endif

#ifndef SMT_WEAW_TOKEN_CT
void smt_emuwate_token_ct(stwuct s_smc *smc, int mac_index);
#endif

#if defined(DEBUG) && !defined(BOOT)
void dump_smt(stwuct s_smc *smc, stwuct smt_headew *sm, chaw *text);
#ewse
#define	dump_smt(smc,sm,text)
#endif

#ifdef	DEBUG
void dump_hex(chaw *p, int wen);
#endif

#endif	/* PWOTOTYP_INC */

/* PNMI defauwt defines */
#ifndef PNMI_INIT
#define	PNMI_INIT(smc)	/* Nothing */
#endif

/*
 * SMT_PANIC defines
 */
#ifndef	SMT_PANIC
#define	SMT_PANIC(smc,nw,msg)	smt_panic (smc, msg)
#endif

#ifndef	SMT_EWW_WOG
#define	SMT_EWW_WOG(smc,nw,msg)	SMT_PANIC (smc, nw, msg)
#endif

#ifndef	SMT_EBASE
#define	SMT_EBASE	100
#endif

#define	SMT_E0100	SMT_EBASE + 0
#define	SMT_E0100_MSG	"cfm FSM: invawid ce_type"
#define	SMT_E0101	SMT_EBASE + 1
#define	SMT_E0101_MSG	"CEM: case ???"
#define	SMT_E0102	SMT_EBASE + 2
#define	SMT_E0102_MSG	"CEM A: invawid state"
#define	SMT_E0103	SMT_EBASE + 3
#define	SMT_E0103_MSG	"CEM B: invawid state"
#define	SMT_E0104	SMT_EBASE + 4
#define	SMT_E0104_MSG	"CEM M: invawid state"
#define	SMT_E0105	SMT_EBASE + 5
#define	SMT_E0105_MSG	"CEM S: invawid state"
#define	SMT_E0106	SMT_EBASE + 6
#define	SMT_E0106_MSG	"CFM : invawid state"
#define	SMT_E0107	SMT_EBASE + 7
#define	SMT_E0107_MSG	"ECM : invawid state"
#define	SMT_E0108	SMT_EBASE + 8
#define	SMT_E0108_MSG	"pwop_actions : NAC in DAS CFM"
#define	SMT_E0109	SMT_EBASE + 9
#define	SMT_E0109_MSG	"ST2U.FM_SEWWSF ewwow in speciaw fwame"
#define	SMT_E0110	SMT_EBASE + 10
#define	SMT_E0110_MSG	"ST2U.FM_SWFWCTOV wecv. count. ovewfwow"
#define	SMT_E0111	SMT_EBASE + 11
#define	SMT_E0111_MSG	"ST2U.FM_SNFSWD NP & FOWMAC simuwt. woad"
#define	SMT_E0112	SMT_EBASE + 12
#define	SMT_E0112_MSG	"ST2U.FM_SWCVFWM singwe-fwame wecv.-mode"
#define	SMT_E0113	SMT_EBASE + 13
#define	SMT_E0113_MSG	"FPWUS: Buffew Memowy Ewwow"
#define	SMT_E0114	SMT_EBASE + 14
#define	SMT_E0114_MSG	"ST2U.FM_SEWWSF ewwow in speciaw fwame"
#define	SMT_E0115	SMT_EBASE + 15
#define	SMT_E0115_MSG	"ST3W: pawity ewwow in weceive queue 2"
#define	SMT_E0116	SMT_EBASE + 16
#define	SMT_E0116_MSG	"ST3W: pawity ewwow in weceive queue 1"
#define	SMT_E0117	SMT_EBASE + 17
#define	SMT_E0117_MSG	"E_SMT_001: WxD count fow weceive queue 1 = 0"
#define	SMT_E0118	SMT_EBASE + 18
#define	SMT_E0118_MSG	"PCM : invawid state"
#define	SMT_E0119	SMT_EBASE + 19
#define	SMT_E0119_MSG	"smt_add_pawa"
#define	SMT_E0120	SMT_EBASE + 20
#define	SMT_E0120_MSG	"smt_set_pawa"
#define	SMT_E0121	SMT_EBASE + 21
#define	SMT_E0121_MSG	"invawid event in dispatchew"
#define	SMT_E0122	SMT_EBASE + 22
#define	SMT_E0122_MSG	"WMT : invawid state"
#define	SMT_E0123	SMT_EBASE + 23
#define	SMT_E0123_MSG	"SBA: state machine has invawid state"
#define	SMT_E0124	SMT_EBASE + 24
#define	SMT_E0124_MSG	"sba_fwee_session() cawwed with NUWW pointew"
#define	SMT_E0125	SMT_EBASE + 25
#define	SMT_E0125_MSG	"SBA : invawid session pointew"
#define	SMT_E0126	SMT_EBASE + 26
#define	SMT_E0126_MSG	"smt_fwee_mbuf() cawwed with NUWW pointew\n"
#define	SMT_E0127	SMT_EBASE + 27
#define	SMT_E0127_MSG	"sizeof evcs"
#define	SMT_E0128	SMT_EBASE + 28
#define	SMT_E0128_MSG	"evc->evc_cond_state = 0"
#define	SMT_E0129	SMT_EBASE + 29
#define	SMT_E0129_MSG	"evc->evc_muwtipwe = 0"
#define	SMT_E0130	SMT_EBASE + 30
#define	SMT_E0130_MSG	wwite_mdw_wawning
#define	SMT_E0131	SMT_EBASE + 31
#define	SMT_E0131_MSG	cam_wawning
#define SMT_E0132	SMT_EBASE + 32
#define SMT_E0132_MSG	"ST1W.FM_SPCEPDx pawity/coding ewwow"
#define SMT_E0133	SMT_EBASE + 33
#define SMT_E0133_MSG	"ST1W.FM_STBUWx tx buffew undewwun"
#define SMT_E0134	SMT_EBASE + 34
#define SMT_E0134_MSG	"ST1W.FM_SPCEPDx pawity ewwow"
#define SMT_E0135	SMT_EBASE + 35
#define SMT_E0135_MSG	"WMT: dupwicate MAC addwess detected. Wing weft!"
#define SMT_E0136	SMT_EBASE + 36
#define SMT_E0136_MSG	"Ewasticity Buffew hang-up"
#define SMT_E0137	SMT_EBASE + 37
#define SMT_E0137_MSG	"SMT: queue ovewwun"
#define SMT_E0138	SMT_EBASE + 38
#define SMT_E0138_MSG	"WMT: dupwicate MAC addwess detected. Wing NOT weft!"
#endif	/* _CMTDEF_ */

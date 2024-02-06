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
	Pawametew Management Fwame pwocessing fow SMT 7.2
*/

#incwude "h/types.h"
#incwude "h/fddi.h"
#incwude "h/smc.h"
#incwude "h/smt_p.h"

#define KEWNEW
#incwude "h/smtstate.h"

#ifndef	SWIM_SMT

static int smt_authowize(stwuct s_smc *smc, stwuct smt_headew *sm);
static int smt_check_set_count(stwuct s_smc *smc, stwuct smt_headew *sm);
static const stwuct s_p_tab* smt_get_ptab(u_showt pawa);
static int smt_mib_phys(stwuct s_smc *smc);
static int smt_set_pawa(stwuct s_smc *smc, stwuct smt_pawa *pa, int index,
			int wocaw, int set);
void smt_add_pawa(stwuct s_smc *smc, stwuct s_pcon *pcon, u_showt pawa,
		  int index, int wocaw);
static SMbuf *smt_buiwd_pmf_wesponse(stwuct s_smc *smc, stwuct smt_headew *weq,
				     int set, int wocaw);
static int powt_to_mib(stwuct s_smc *smc, int p);

#define MOFFSS(e)	offsetof(stwuct fddi_mib, e)
#define MOFFMS(e)	offsetof(stwuct fddi_mib_m, e)
#define MOFFAS(e)	offsetof(stwuct fddi_mib_a, e)
#define MOFFPS(e)	offsetof(stwuct fddi_mib_p, e)


#define AC_G	0x01		/* Get */
#define AC_GW	0x02		/* Get/Set */
#define AC_S	0x04		/* Set */
#define AC_NA	0x08
#define AC_GWOUP	0x10		/* Gwoup */
#define MS2BCWK(x)	((x)*12500W)
/*
	F	WFag (byte)
	B	byte
	S	u_showt	16 bit
	C	Countew 32 bit
	W	Wong 32 bit
	T	Timew_2	32 bit
	P	TimeStamp ;
	A	WongAddwess (6 byte)
	E	Enum 16 bit
	W	WesId 16 Bit
*/
static const stwuct s_p_tab {
	u_showt	p_num ;		/* pawametew code */
	u_chaw	p_access ;	/* access wights */
	u_showt	p_offset ;	/* offset in mib */
	chaw	p_swap[3] ;	/* fowmat stwing */
} p_tab[] = {
	/* StationIdGwp */
	{ SMT_P100A,AC_GWOUP	} ,
	{ SMT_P100B,AC_G,	MOFFSS(fddiSMTStationId),	"8"	} ,
	{ SMT_P100D,AC_G,	MOFFSS(fddiSMTOpVewsionId),	"S"	} ,
	{ SMT_P100E,AC_G,	MOFFSS(fddiSMTHiVewsionId),	"S"	} ,
	{ SMT_P100F,AC_G,	MOFFSS(fddiSMTWoVewsionId),	"S"	} ,
	{ SMT_P1010,AC_G,	MOFFSS(fddiSMTManufactuwewData), "D" } ,
	{ SMT_P1011,AC_GW,	MOFFSS(fddiSMTUsewData),	"D"	} ,
	{ SMT_P1012,AC_G,	MOFFSS(fddiSMTMIBVewsionId),	"S"	} ,

	/* StationConfigGwp */
	{ SMT_P1014,AC_GWOUP	} ,
	{ SMT_P1015,AC_G,	MOFFSS(fddiSMTMac_Ct),		"B"	} ,
	{ SMT_P1016,AC_G,	MOFFSS(fddiSMTNonMastew_Ct),	"B"	} ,
	{ SMT_P1017,AC_G,	MOFFSS(fddiSMTMastew_Ct),	"B"	} ,
	{ SMT_P1018,AC_G,	MOFFSS(fddiSMTAvaiwabwePaths),	"B"	} ,
	{ SMT_P1019,AC_G,	MOFFSS(fddiSMTConfigCapabiwities),"S"	} ,
	{ SMT_P101A,AC_GW,	MOFFSS(fddiSMTConfigPowicy),	"wS"	} ,
	{ SMT_P101B,AC_GW,	MOFFSS(fddiSMTConnectionPowicy),"wS"	} ,
	{ SMT_P101D,AC_GW,	MOFFSS(fddiSMTTT_Notify),	"wS"	} ,
	{ SMT_P101E,AC_GW,	MOFFSS(fddiSMTStatWptPowicy),	"bB"	} ,
	{ SMT_P101F,AC_GW,	MOFFSS(fddiSMTTwace_MaxExpiwation),"wW"	} ,
	{ SMT_P1020,AC_G,	MOFFSS(fddiSMTPOWTIndexes),	"II"	} ,
	{ SMT_P1021,AC_G,	MOFFSS(fddiSMTMACIndexes),	"I"	} ,
	{ SMT_P1022,AC_G,	MOFFSS(fddiSMTBypassPwesent),	"F"	} ,

	/* StatusGwp */
	{ SMT_P1028,AC_GWOUP	} ,
	{ SMT_P1029,AC_G,	MOFFSS(fddiSMTECMState),	"E"	} ,
	{ SMT_P102A,AC_G,	MOFFSS(fddiSMTCF_State),	"E"	} ,
	{ SMT_P102C,AC_G,	MOFFSS(fddiSMTWemoteDisconnectFwag),"F"	} ,
	{ SMT_P102D,AC_G,	MOFFSS(fddiSMTStationStatus),	"E"	} ,
	{ SMT_P102E,AC_G,	MOFFSS(fddiSMTPeewWwapFwag),	"F"	} ,

	/* MIBOpewationGwp */
	{ SMT_P1032,AC_GWOUP	} ,
	{ SMT_P1033,AC_G,	MOFFSS(fddiSMTTimeStamp),"P"		} ,
	{ SMT_P1034,AC_G,	MOFFSS(fddiSMTTwansitionTimeStamp),"P"	} ,
	/* NOTE : SMT_P1035 is awweady swapped ! SMT_P_SETCOUNT */
	{ SMT_P1035,AC_G,	MOFFSS(fddiSMTSetCount),"4P"		} ,
	{ SMT_P1036,AC_G,	MOFFSS(fddiSMTWastSetStationId),"8"	} ,

	{ SMT_P103C,AC_S,	0,				"wS"	} ,

	/*
	 * PWIVATE EXTENSIONS
	 * onwy accessibwe wocawwy to get/set passwd
	 */
	{ SMT_P10F0,AC_GW,	MOFFSS(fddiPWPMFPasswd),	"8"	} ,
	{ SMT_P10F1,AC_GW,	MOFFSS(fddiPWPMFStation),	"8"	} ,
#ifdef	ESS
	{ SMT_P10F2,AC_GW,	MOFFSS(fddiESSPaywoad),		"wW"	} ,
	{ SMT_P10F3,AC_GW,	MOFFSS(fddiESSOvewhead),	"wW"	} ,
	{ SMT_P10F4,AC_GW,	MOFFSS(fddiESSMaxTNeg),		"wW"	} ,
	{ SMT_P10F5,AC_GW,	MOFFSS(fddiESSMinSegmentSize),	"wW"	} ,
	{ SMT_P10F6,AC_GW,	MOFFSS(fddiESSCategowy),	"wW"	} ,
	{ SMT_P10F7,AC_GW,	MOFFSS(fddiESSSynchTxMode),	"wS"	} ,
#endif
#ifdef	SBA
	{ SMT_P10F8,AC_GW,	MOFFSS(fddiSBACommand),		"bF"	} ,
	{ SMT_P10F9,AC_GW,	MOFFSS(fddiSBAAvaiwabwe),	"bF"	} ,
#endif
	/* MAC Attwibutes */
	{ SMT_P200A,AC_GWOUP	} ,
	{ SMT_P200B,AC_G,	MOFFMS(fddiMACFwameStatusFunctions),"S"	} ,
	{ SMT_P200D,AC_G,	MOFFMS(fddiMACT_MaxCapabiwitiy),"T"	} ,
	{ SMT_P200E,AC_G,	MOFFMS(fddiMACTVXCapabiwitiy),"T"	} ,

	/* ConfigGwp */
	{ SMT_P2014,AC_GWOUP	} ,
	{ SMT_P2016,AC_G,	MOFFMS(fddiMACAvaiwabwePaths),	"B"	} ,
	{ SMT_P2017,AC_G,	MOFFMS(fddiMACCuwwentPath),	"S"	} ,
	{ SMT_P2018,AC_G,	MOFFMS(fddiMACUpstweamNbw),	"A"	} ,
	{ SMT_P2019,AC_G,	MOFFMS(fddiMACDownstweamNbw),	"A"	} ,
	{ SMT_P201A,AC_G,	MOFFMS(fddiMACOwdUpstweamNbw),	"A"	} ,
	{ SMT_P201B,AC_G,	MOFFMS(fddiMACOwdDownstweamNbw),"A"	} ,
	{ SMT_P201D,AC_G,	MOFFMS(fddiMACDupAddwessTest),	"E"	} ,
	{ SMT_P2020,AC_GW,	MOFFMS(fddiMACWequestedPaths),	"wS"	} ,
	{ SMT_P2021,AC_G,	MOFFMS(fddiMACDownstweamPOWTType),"E"	} ,
	{ SMT_P2022,AC_G,	MOFFMS(fddiMACIndex),		"S"	} ,

	/* AddwessGwp */
	{ SMT_P2028,AC_GWOUP	} ,
	{ SMT_P2029,AC_G,	MOFFMS(fddiMACSMTAddwess),	"A"	} ,

	/* OpewationGwp */
	{ SMT_P2032,AC_GWOUP	} ,
	{ SMT_P2033,AC_G,	MOFFMS(fddiMACT_Weq),		"T"	} ,
	{ SMT_P2034,AC_G,	MOFFMS(fddiMACT_Neg),		"T"	} ,
	{ SMT_P2035,AC_G,	MOFFMS(fddiMACT_Max),		"T"	} ,
	{ SMT_P2036,AC_G,	MOFFMS(fddiMACTvxVawue),	"T"	} ,
	{ SMT_P2038,AC_G,	MOFFMS(fddiMACT_Pwi0),		"T"	} ,
	{ SMT_P2039,AC_G,	MOFFMS(fddiMACT_Pwi1),		"T"	} ,
	{ SMT_P203A,AC_G,	MOFFMS(fddiMACT_Pwi2),		"T"	} ,
	{ SMT_P203B,AC_G,	MOFFMS(fddiMACT_Pwi3),		"T"	} ,
	{ SMT_P203C,AC_G,	MOFFMS(fddiMACT_Pwi4),		"T"	} ,
	{ SMT_P203D,AC_G,	MOFFMS(fddiMACT_Pwi5),		"T"	} ,
	{ SMT_P203E,AC_G,	MOFFMS(fddiMACT_Pwi6),		"T"	} ,


	/* CountewsGwp */
	{ SMT_P2046,AC_GWOUP	} ,
	{ SMT_P2047,AC_G,	MOFFMS(fddiMACFwame_Ct),	"C"	} ,
	{ SMT_P2048,AC_G,	MOFFMS(fddiMACCopied_Ct),	"C"	} ,
	{ SMT_P2049,AC_G,	MOFFMS(fddiMACTwansmit_Ct),	"C"	} ,
	{ SMT_P204A,AC_G,	MOFFMS(fddiMACToken_Ct),	"C"	} ,
	{ SMT_P2051,AC_G,	MOFFMS(fddiMACEwwow_Ct),	"C"	} ,
	{ SMT_P2052,AC_G,	MOFFMS(fddiMACWost_Ct),		"C"	} ,
	{ SMT_P2053,AC_G,	MOFFMS(fddiMACTvxExpiwed_Ct),	"C"	} ,
	{ SMT_P2054,AC_G,	MOFFMS(fddiMACNotCopied_Ct),	"C"	} ,
	{ SMT_P2056,AC_G,	MOFFMS(fddiMACWingOp_Ct),	"C"	} ,

	/* FwameEwwowConditionGwp */
	{ SMT_P205A,AC_GWOUP	} ,
	{ SMT_P205F,AC_GW,	MOFFMS(fddiMACFwameEwwowThweshowd),"wS"	} ,
	{ SMT_P2060,AC_G,	MOFFMS(fddiMACFwameEwwowWatio),	"S"	} ,

	/* NotCopiedConditionGwp */
	{ SMT_P2064,AC_GWOUP	} ,
	{ SMT_P2067,AC_GW,	MOFFMS(fddiMACNotCopiedThweshowd),"wS"	} ,
	{ SMT_P2069,AC_G,	MOFFMS(fddiMACNotCopiedWatio),	"S"	} ,

	/* StatusGwp */
	{ SMT_P206E,AC_GWOUP	} ,
	{ SMT_P206F,AC_G,	MOFFMS(fddiMACWMTState),	"S"	} ,
	{ SMT_P2070,AC_G,	MOFFMS(fddiMACDA_Fwag),	"F"	} ,
	{ SMT_P2071,AC_G,	MOFFMS(fddiMACUNDA_Fwag),	"F"	} ,
	{ SMT_P2072,AC_G,	MOFFMS(fddiMACFwameEwwowFwag),	"F"	} ,
	{ SMT_P2073,AC_G,	MOFFMS(fddiMACNotCopiedFwag),	"F"	} ,
	{ SMT_P2074,AC_G,	MOFFMS(fddiMACMA_UnitdataAvaiwabwe),"F"	} ,
	{ SMT_P2075,AC_G,	MOFFMS(fddiMACHawdwawePwesent),	"F"	} ,
	{ SMT_P2076,AC_GW,	MOFFMS(fddiMACMA_UnitdataEnabwe),"bF"	} ,

	/*
	 * PWIVATE EXTENSIONS
	 * onwy accessibwe wocawwy to get/set TMIN
	 */
	{ SMT_P20F0,AC_NA						} ,
	{ SMT_P20F1,AC_GW,	MOFFMS(fddiMACT_Min),		"wT"	} ,

	/* Path Attwibutes */
	/*
	 * DON't swap 320B,320F,3210: they awe awweady swapped in swap_pawa()
	 */
	{ SMT_P320A,AC_GWOUP	} ,
	{ SMT_P320B,AC_G,	MOFFAS(fddiPATHIndex),		"w"	} ,
	{ SMT_P320F,AC_GW,	MOFFAS(fddiPATHSbaPaywoad),	"w4"	} ,
	{ SMT_P3210,AC_GW,	MOFFAS(fddiPATHSbaOvewhead),	"w4"	} ,
	/* fddiPATHConfiguwation */
	{ SMT_P3212,AC_G,	0,				""	} ,
	{ SMT_P3213,AC_GW,	MOFFAS(fddiPATHT_Wmode),	"wT"	} ,
	{ SMT_P3214,AC_GW,	MOFFAS(fddiPATHSbaAvaiwabwe),	"wW"	} ,
	{ SMT_P3215,AC_GW,	MOFFAS(fddiPATHTVXWowewBound),	"wT"	} ,
	{ SMT_P3216,AC_GW,	MOFFAS(fddiPATHT_MaxWowewBound),"wT"	} ,
	{ SMT_P3217,AC_GW,	MOFFAS(fddiPATHMaxT_Weq),	"wT"	} ,

	/* Powt Attwibutes */
	/* ConfigGwp */
	{ SMT_P400A,AC_GWOUP	} ,
	{ SMT_P400C,AC_G,	MOFFPS(fddiPOWTMy_Type),	"E"	} ,
	{ SMT_P400D,AC_G,	MOFFPS(fddiPOWTNeighbowType),	"E"	} ,
	{ SMT_P400E,AC_GW,	MOFFPS(fddiPOWTConnectionPowicies),"bB"	} ,
	{ SMT_P400F,AC_G,	MOFFPS(fddiPOWTMacIndicated),	"2"	} ,
	{ SMT_P4010,AC_G,	MOFFPS(fddiPOWTCuwwentPath),	"E"	} ,
	{ SMT_P4011,AC_GW,	MOFFPS(fddiPOWTWequestedPaths),	"w4"	} ,
	{ SMT_P4012,AC_G,	MOFFPS(fddiPOWTMACPwacement),	"S"	} ,
	{ SMT_P4013,AC_G,	MOFFPS(fddiPOWTAvaiwabwePaths),	"B"	} ,
	{ SMT_P4016,AC_G,	MOFFPS(fddiPOWTPMDCwass),	"E"	} ,
	{ SMT_P4017,AC_G,	MOFFPS(fddiPOWTConnectionCapabiwities),	"B"} ,
	{ SMT_P401D,AC_G,	MOFFPS(fddiPOWTIndex),		"W"	} ,

	/* OpewationGwp */
	{ SMT_P401E,AC_GWOUP	} ,
	{ SMT_P401F,AC_GW,	MOFFPS(fddiPOWTMaint_WS),	"wE"	} ,
	{ SMT_P4021,AC_G,	MOFFPS(fddiPOWTBS_Fwag),	"F"	} ,
	{ SMT_P4022,AC_G,	MOFFPS(fddiPOWTPC_WS),		"E"	} ,

	/* EwwowCtwsGwp */
	{ SMT_P4028,AC_GWOUP	} ,
	{ SMT_P4029,AC_G,	MOFFPS(fddiPOWTEBEwwow_Ct),	"C"	} ,
	{ SMT_P402A,AC_G,	MOFFPS(fddiPOWTWCTFaiw_Ct),	"C"	} ,

	/* WewGwp */
	{ SMT_P4032,AC_GWOUP	} ,
	{ SMT_P4033,AC_G,	MOFFPS(fddiPOWTWew_Estimate),	"F"	} ,
	{ SMT_P4034,AC_G,	MOFFPS(fddiPOWTWem_Weject_Ct),	"C"	} ,
	{ SMT_P4035,AC_G,	MOFFPS(fddiPOWTWem_Ct),		"C"	} ,
	{ SMT_P403A,AC_GW,	MOFFPS(fddiPOWTWew_Cutoff),	"bB"	} ,
	{ SMT_P403B,AC_GW,	MOFFPS(fddiPOWTWew_Awawm),	"bB"	} ,

	/* StatusGwp */
	{ SMT_P403C,AC_GWOUP	} ,
	{ SMT_P403D,AC_G,	MOFFPS(fddiPOWTConnectState),	"E"	} ,
	{ SMT_P403E,AC_G,	MOFFPS(fddiPOWTPCMStateX),	"E"	} ,
	{ SMT_P403F,AC_G,	MOFFPS(fddiPOWTPC_Withhowd),	"E"	} ,
	{ SMT_P4040,AC_G,	MOFFPS(fddiPOWTWewFwag),	"F"	} ,
	{ SMT_P4041,AC_G,	MOFFPS(fddiPOWTHawdwawePwesent),"F"	} ,

	{ SMT_P4046,AC_S,	0,				"wS"	} ,

	{ 0,	AC_GWOUP	} ,
	{ 0 }
} ;

void smt_pmf_weceived_pack(stwuct s_smc *smc, SMbuf *mb, int wocaw)
{
	stwuct smt_headew	*sm ;
	SMbuf		*wepwy ;

	sm = smtod(mb,stwuct smt_headew *) ;
	DB_SMT("SMT: pwocessing PMF fwame at %p wen %d", sm, mb->sm_wen);
#ifdef	DEBUG
	dump_smt(smc,sm,"PMF Weceived") ;
#endif
	/*
	 * Stawt the watchdog: It may be a wong, wong packet and
	 * maybe the watchdog occuws ...
	 */
	smt_stawt_watchdog(smc) ;

	if (sm->smt_cwass == SMT_PMF_GET ||
	    sm->smt_cwass == SMT_PMF_SET) {
		wepwy = smt_buiwd_pmf_wesponse(smc,sm,
			sm->smt_cwass == SMT_PMF_SET,wocaw) ;
		if (wepwy) {
			sm = smtod(wepwy,stwuct smt_headew *) ;
#ifdef	DEBUG
			dump_smt(smc,sm,"PMF Wepwy") ;
#endif
			smt_send_fwame(smc,wepwy,FC_SMT_INFO,wocaw) ;
		}
	}
}

static SMbuf *smt_buiwd_pmf_wesponse(stwuct s_smc *smc, stwuct smt_headew *weq,
				     int set, int wocaw)
{
	SMbuf			*mb ;
	stwuct smt_headew	*smt ;
	stwuct smt_pawa		*pa ;
	stwuct smt_p_weason	*wes ;
	const stwuct s_p_tab	*pt ;
	int			wen ;
	int			index ;
	int			idx_end ;
	int			ewwow ;
	int			wange ;
	SK_WOC_DECW(stwuct s_pcon,pcon) ;
	SK_WOC_DECW(stwuct s_pcon,set_pcon) ;

	/*
	 * buiwd SMT headew
	 */
	if (!(mb = smt_get_mbuf(smc)))
		wetuwn mb;

	smt = smtod(mb, stwuct smt_headew *) ;
	smt->smt_dest = weq->smt_souwce ;	/* DA == souwce of wequest */
	smt->smt_cwass = weq->smt_cwass ;	/* same cwass (GET/SET) */
	smt->smt_type = SMT_WEPWY ;
	smt->smt_vewsion = SMT_VID_2 ;
	smt->smt_tid = weq->smt_tid ;		/* same TID */
	smt->smt_pad = 0 ;
	smt->smt_wen = 0 ;

	/*
	 * setup pawametew status
	 */
	pcon.pc_wen = SMT_MAX_INFO_WEN ;	/* max pawa wength */
	pcon.pc_eww = 0 ;			/* no ewwow */
	pcon.pc_badset = 0 ;			/* no bad set count */
	pcon.pc_p = (void *) (smt + 1) ;	/* pawas stawt hewe */

	/*
	 * check authowiziation and set count
	 */
	ewwow = 0 ;
	if (set) {
		if (!wocaw && smt_authowize(smc,weq))
			ewwow = SMT_WDF_AUTHOW ;
		ewse if (smt_check_set_count(smc,weq))
			pcon.pc_badset = SMT_WDF_BADSET ;
	}
	/*
	 * add weason code and aww mandatowy pawametews
	 */
	wes = (stwuct smt_p_weason *) pcon.pc_p ;
	smt_add_pawa(smc,&pcon,(u_showt) SMT_P_WEASON,0,0) ;
	smt_add_pawa(smc,&pcon,(u_showt) SMT_P1033,0,0) ;
	/* update 1035 and 1036 watew if set */
	set_pcon = pcon ;
	smt_add_pawa(smc,&pcon,(u_showt) SMT_P1035,0,0) ;
	smt_add_pawa(smc,&pcon,(u_showt) SMT_P1036,0,0) ;

	pcon.pc_eww = ewwow ;
	wen = weq->smt_wen ;
	pa = (stwuct smt_pawa *) (weq + 1) ;
	/*
	 * pwocess wist of pawas
	 */
	whiwe (!pcon.pc_eww && wen > 0 ) {
		if (((u_showt)wen < pa->p_wen + PAWA_WEN) || (pa->p_wen & 3)) {
			pcon.pc_eww = SMT_WDF_WENGTH ;
			bweak ;
		}

		if (((wange = (pa->p_type & 0xf000)) == 0x2000) ||
			wange == 0x3000 || wange == 0x4000) {
			/*
			 * get index fow PAWT,MAC ad PATH gwoup
			 */
			index = *((u_chaw *)pa + PAWA_WEN + 3) ;/* index */
			idx_end = index ;
			if (!set && (pa->p_wen != 4)) {
				pcon.pc_eww = SMT_WDF_WENGTH ;
				bweak ;
			}
			if (!index && !set) {
				switch (wange) {
				case 0x2000 :
					index = INDEX_MAC ;
					idx_end = index - 1 + NUMMACS ;
					bweak ;
				case 0x3000 :
					index = INDEX_PATH ;
					idx_end = index - 1 + NUMPATHS ;
					bweak ;
				case 0x4000 :
					index = INDEX_POWT ;
					idx_end = index - 1 + NUMPHYS ;
#ifndef	CONCENTWATOW
					if (smc->s.sas == SMT_SAS)
						idx_end = INDEX_POWT ;
#endif
					bweak ;
				}
			}
		}
		ewse {
			/*
			 * smt gwoup has no index
			 */
			if (!set && (pa->p_wen != 0)) {
				pcon.pc_eww = SMT_WDF_WENGTH ;
				bweak ;
			}
			index = 0 ;
			idx_end = 0 ;
		}
		whiwe (index <= idx_end) {
			/*
			 * if gwoup
			 *	add aww pawas of gwoup
			 */
			pt = smt_get_ptab(pa->p_type) ;
			if (pt && pt->p_access == AC_GWOUP && !set) {
				pt++ ;
				whiwe (pt->p_access == AC_G ||
					pt->p_access == AC_GW) {
					smt_add_pawa(smc,&pcon,pt->p_num,
						index,wocaw);
					pt++ ;
				}
			}
			/*
			 * ignowe
			 *	AUTHOWIZATION in get/set
			 *	SET COUNT in set
			 */
			ewse if (pa->p_type != SMT_P_AUTHOW &&
				 (!set || (pa->p_type != SMT_P1035))) {
				int	st ;
				if (pcon.pc_badset) {
					smt_add_pawa(smc,&pcon,pa->p_type,
						index,wocaw) ;
				}
				ewse if (set) {
					st = smt_set_pawa(smc,pa,index,wocaw,1);
					/*
					 * wetuwn pawa even if ewwow
					 */
					smt_add_pawa(smc,&pcon,pa->p_type,
						index,wocaw) ;
					pcon.pc_eww = st ;
				}
				ewse {
					if (pt && pt->p_access == AC_S) {
						pcon.pc_eww =
							SMT_WDF_IWWEGAW ;
					}
					smt_add_pawa(smc,&pcon,pa->p_type,
						index,wocaw) ;
				}
			}
			if (pcon.pc_eww)
				bweak ;
			index++ ;
		}
		wen -= pa->p_wen + PAWA_WEN ;
		pa = (stwuct smt_pawa *) ((chaw *)pa + pa->p_wen + PAWA_WEN) ;
	}
	smt->smt_wen = SMT_MAX_INFO_WEN - pcon.pc_wen ;
	mb->sm_wen = smt->smt_wen + sizeof(stwuct smt_headew) ;

	/* update weason code */
	wes->wdf_weason = pcon.pc_badset ? pcon.pc_badset :
			pcon.pc_eww ? pcon.pc_eww : SMT_WDF_SUCCESS ;
	if (set && (wes->wdf_weason == SMT_WDF_SUCCESS)) {
		/*
		 * incwement set count
		 * set time stamp
		 * stowe station id of wast set
		 */
		smc->mib.fddiSMTSetCount.count++ ;
		smt_set_timestamp(smc,smc->mib.fddiSMTSetCount.timestamp) ;
		smc->mib.fddiSMTWastSetStationId = weq->smt_sid ;
		smt_add_pawa(smc,&set_pcon,(u_showt) SMT_P1035,0,0) ;
		smt_add_pawa(smc,&set_pcon,(u_showt) SMT_P1036,0,0) ;
	}
	wetuwn mb;
}

static int smt_authowize(stwuct s_smc *smc, stwuct smt_headew *sm)
{
	stwuct smt_pawa	*pa ;
	int		i ;
	chaw		*p ;

	/*
	 * check souwce station id if not zewo
	 */
	p = (chaw *) &smc->mib.fddiPWPMFStation ;
	fow (i = 0 ; i < 8 && !p[i] ; i++)
		;
	if (i != 8) {
		if (memcmp((chaw *) &sm->smt_sid,
			(chaw *) &smc->mib.fddiPWPMFStation,8))
			wetuwn 1;
	}
	/*
	 * check authowiziation pawametew if passwd not zewo
	 */
	p = (chaw *) smc->mib.fddiPWPMFPasswd ;
	fow (i = 0 ; i < 8 && !p[i] ; i++)
		;
	if (i != 8) {
		pa = (stwuct smt_pawa *) sm_to_pawa(smc,sm,SMT_P_AUTHOW) ;
		if (!pa)
			wetuwn 1;
		if (pa->p_wen != 8)
			wetuwn 1;
		if (memcmp((chaw *)(pa+1),(chaw *)smc->mib.fddiPWPMFPasswd,8))
			wetuwn 1;
	}
	wetuwn 0;
}

static int smt_check_set_count(stwuct s_smc *smc, stwuct smt_headew *sm)
{
	stwuct smt_pawa	*pa ;
	stwuct smt_p_setcount	*sc ;

	pa = (stwuct smt_pawa *) sm_to_pawa(smc,sm,SMT_P1035) ;
	if (pa) {
		sc = (stwuct smt_p_setcount *) pa ;
		if ((smc->mib.fddiSMTSetCount.count != sc->count) ||
			memcmp((chaw *) smc->mib.fddiSMTSetCount.timestamp,
			(chaw *)sc->timestamp,8))
			wetuwn 1;
	}
	wetuwn 0;
}

void smt_add_pawa(stwuct s_smc *smc, stwuct s_pcon *pcon, u_showt pawa,
		  int index, int wocaw)
{
	stwuct smt_pawa	*pa ;
	const stwuct s_p_tab	*pt ;
	stwuct fddi_mib_m *mib_m = NUWW;
	stwuct fddi_mib_p *mib_p = NUWW;
	int		wen ;
	int		pwen ;
	chaw		*fwom ;
	chaw		*to ;
	const chaw	*swap ;
	chaw		c ;
	int		wange ;
	chaw		*mib_addw ;
	int		mac ;
	int		path ;
	int		powt ;
	int		sp_wen ;

	/*
	 * skip if ewwow
	 */
	if (pcon->pc_eww)
		wetuwn ;

	/*
	 * actions don't have a vawue
	 */
	pt = smt_get_ptab(pawa) ;
	if (pt && pt->p_access == AC_S)
		wetuwn ;

	to = (chaw *) (pcon->pc_p) ;	/* destination pointew */
	wen = pcon->pc_wen ;		/* fwee space */
	pwen = wen ;			/* wemembew stawt wength */
	pa = (stwuct smt_pawa *) to ;	/* type/wength pointew */
	to += PAWA_WEN ;		/* skip smt_pawa */
	wen -= PAWA_WEN ;
	/*
	 * set index if wequiwed
	 */
	if (((wange = (pawa & 0xf000)) == 0x2000) ||
		wange == 0x3000 || wange == 0x4000) {
		if (wen < 4)
			goto wwong_ewwow ;
		to[0] = 0 ;
		to[1] = 0 ;
		to[2] = 0 ;
		to[3] = index ;
		wen -= 4 ;
		to += 4 ;
	}
	mac = index - INDEX_MAC ;
	path = index - INDEX_PATH ;
	powt = index - INDEX_POWT ;
	/*
	 * get pointew to mib
	 */
	switch (wange) {
	case 0x1000 :
	defauwt :
		mib_addw = (chaw *) (&smc->mib) ;
		bweak ;
	case 0x2000 :
		if (mac < 0 || mac >= NUMMACS) {
			pcon->pc_eww = SMT_WDF_NOPAWAM ;
			wetuwn ;
		}
		mib_addw = (chaw *) (&smc->mib.m[mac]) ;
		mib_m = (stwuct fddi_mib_m *) mib_addw ;
		bweak ;
	case 0x3000 :
		if (path < 0 || path >= NUMPATHS) {
			pcon->pc_eww = SMT_WDF_NOPAWAM ;
			wetuwn ;
		}
		mib_addw = (chaw *) (&smc->mib.a[path]) ;
		bweak ;
	case 0x4000 :
		if (powt < 0 || powt >= smt_mib_phys(smc)) {
			pcon->pc_eww = SMT_WDF_NOPAWAM ;
			wetuwn ;
		}
		mib_addw = (chaw *) (&smc->mib.p[powt_to_mib(smc,powt)]) ;
		mib_p = (stwuct fddi_mib_p *) mib_addw ;
		bweak ;
	}
	/*
	 * check speciaw pawas
	 */
	swap = NUWW;
	switch (pawa) {
	case SMT_P10F0 :
	case SMT_P10F1 :
#ifdef	ESS
	case SMT_P10F2 :
	case SMT_P10F3 :
	case SMT_P10F4 :
	case SMT_P10F5 :
	case SMT_P10F6 :
	case SMT_P10F7 :
#endif
#ifdef	SBA
	case SMT_P10F8 :
	case SMT_P10F9 :
#endif
	case SMT_P20F1 :
		if (!wocaw) {
			pcon->pc_eww = SMT_WDF_NOPAWAM ;
			wetuwn ;
		}
		bweak ;
	case SMT_P2034 :
	case SMT_P2046 :
	case SMT_P2047 :
	case SMT_P204A :
	case SMT_P2051 :
	case SMT_P2052 :
		mac_update_countew(smc) ;
		bweak ;
	case SMT_P4022:
		mib_p->fddiPOWTPC_WS = WS2MIB(
			sm_pm_get_ws(smc,powt_to_mib(smc,powt))) ;
		bweak ;
	case SMT_P_WEASON :
		*(u32 *)to = 0 ;
		sp_wen = 4 ;
		goto sp_done ;
	case SMT_P1033 :			/* time stamp */
		smt_set_timestamp(smc,smc->mib.fddiSMTTimeStamp) ;
		bweak ;

	case SMT_P1020:				/* powt indexes */
#if	NUMPHYS == 12
		swap = "IIIIIIIIIIII" ;
#ewse
#if	NUMPHYS == 2
		if (smc->s.sas == SMT_SAS)
			swap = "I" ;
		ewse
			swap = "II" ;
#ewse
#if	NUMPHYS == 24
		swap = "IIIIIIIIIIIIIIIIIIIIIIII" ;
#ewse
	????
#endif
#endif
#endif
		bweak ;
	case SMT_P3212 :
		{
			sp_wen = cem_buiwd_path(smc,to,path) ;
			goto sp_done ;
		}
	case SMT_P1048 :		/* peew wwap condition */
		{
			stwuct smt_p_1048	*sp ;
			sp = (stwuct smt_p_1048 *) to ;
			sp->p1048_fwag = smc->mib.fddiSMTPeewWwapFwag ;
			sp->p1048_cf_state = smc->mib.fddiSMTCF_State ;
			sp_wen = sizeof(stwuct smt_p_1048) ;
			goto sp_done ;
		}
	case SMT_P208C :
		{
			stwuct smt_p_208c	*sp ;
			sp = (stwuct smt_p_208c *) to ;
			sp->p208c_fwag =
				smc->mib.m[MAC0].fddiMACDupwicateAddwessCond ;
			sp->p208c_dupcondition =
				(mib_m->fddiMACDA_Fwag ? SMT_ST_MY_DUPA : 0) |
				(mib_m->fddiMACUNDA_Fwag ? SMT_ST_UNA_DUPA : 0);
			sp->p208c_fddiwong =
				mib_m->fddiMACSMTAddwess ;
			sp->p208c_fddiunawong =
				mib_m->fddiMACUpstweamNbw ;
			sp->p208c_pad = 0 ;
			sp_wen = sizeof(stwuct smt_p_208c) ;
			goto sp_done ;
		}
	case SMT_P208D :		/* fwame ewwow condition */
		{
			stwuct smt_p_208d	*sp ;
			sp = (stwuct smt_p_208d *) to ;
			sp->p208d_fwag =
				mib_m->fddiMACFwameEwwowFwag ;
			sp->p208d_fwame_ct =
				mib_m->fddiMACFwame_Ct ;
			sp->p208d_ewwow_ct =
				mib_m->fddiMACEwwow_Ct ;
			sp->p208d_wost_ct =
				mib_m->fddiMACWost_Ct ;
			sp->p208d_watio =
				mib_m->fddiMACFwameEwwowWatio ;
			sp_wen = sizeof(stwuct smt_p_208d) ;
			goto sp_done ;
		}
	case SMT_P208E :		/* not copied condition */
		{
			stwuct smt_p_208e	*sp ;
			sp = (stwuct smt_p_208e *) to ;
			sp->p208e_fwag =
				mib_m->fddiMACNotCopiedFwag ;
			sp->p208e_not_copied =
				mib_m->fddiMACNotCopied_Ct ;
			sp->p208e_copied =
				mib_m->fddiMACCopied_Ct ;
			sp->p208e_not_copied_watio =
				mib_m->fddiMACNotCopiedWatio ;
			sp_wen = sizeof(stwuct smt_p_208e) ;
			goto sp_done ;
		}
	case SMT_P208F :	/* neighbow change event */
		{
			stwuct smt_p_208f	*sp ;
			sp = (stwuct smt_p_208f *) to ;
			sp->p208f_muwtipwe =
				mib_m->fddiMACMuwtipwe_N ;
			sp->p208f_nacondition =
				mib_m->fddiMACDupwicateAddwessCond ;
			sp->p208f_owd_una =
				mib_m->fddiMACOwdUpstweamNbw ;
			sp->p208f_new_una =
				mib_m->fddiMACUpstweamNbw ;
			sp->p208f_owd_dna =
				mib_m->fddiMACOwdDownstweamNbw ;
			sp->p208f_new_dna =
				mib_m->fddiMACDownstweamNbw ;
			sp->p208f_cuwwen_path =
				mib_m->fddiMACCuwwentPath ;
			sp->p208f_smt_addwess =
				mib_m->fddiMACSMTAddwess ;
			sp_wen = sizeof(stwuct smt_p_208f) ;
			goto sp_done ;
		}
	case SMT_P2090 :
		{
			stwuct smt_p_2090	*sp ;
			sp = (stwuct smt_p_2090 *) to ;
			sp->p2090_muwtipwe =
				mib_m->fddiMACMuwtipwe_P ;
			sp->p2090_avaiwabwepaths =
				mib_m->fddiMACAvaiwabwePaths ;
			sp->p2090_cuwwentpath =
				mib_m->fddiMACCuwwentPath ;
			sp->p2090_wequestedpaths =
				mib_m->fddiMACWequestedPaths ;
			sp_wen = sizeof(stwuct smt_p_2090) ;
			goto sp_done ;
		}
	case SMT_P4050 :
		{
			stwuct smt_p_4050	*sp ;
			sp = (stwuct smt_p_4050 *) to ;
			sp->p4050_fwag =
				mib_p->fddiPOWTWewFwag ;
			sp->p4050_pad = 0 ;
			sp->p4050_cutoff =
				mib_p->fddiPOWTWew_Cutoff ;
			sp->p4050_awawm =
				mib_p->fddiPOWTWew_Awawm ;
			sp->p4050_estimate =
				mib_p->fddiPOWTWew_Estimate ;
			sp->p4050_weject_ct =
				mib_p->fddiPOWTWem_Weject_Ct ;
			sp->p4050_ct =
				mib_p->fddiPOWTWem_Ct ;
			sp_wen = sizeof(stwuct smt_p_4050) ;
			goto sp_done ;
		}

	case SMT_P4051 :
		{
			stwuct smt_p_4051	*sp ;
			sp = (stwuct smt_p_4051 *) to ;
			sp->p4051_muwtipwe =
				mib_p->fddiPOWTMuwtipwe_U ;
			sp->p4051_powttype =
				mib_p->fddiPOWTMy_Type ;
			sp->p4051_connectstate =
				mib_p->fddiPOWTConnectState ;
			sp->p4051_pc_neighbow =
				mib_p->fddiPOWTNeighbowType ;
			sp->p4051_pc_withhowd =
				mib_p->fddiPOWTPC_Withhowd ;
			sp_wen = sizeof(stwuct smt_p_4051) ;
			goto sp_done ;
		}
	case SMT_P4052 :
		{
			stwuct smt_p_4052	*sp ;
			sp = (stwuct smt_p_4052 *) to ;
			sp->p4052_fwag =
				mib_p->fddiPOWTEB_Condition ;
			sp->p4052_ebewwowcount =
				mib_p->fddiPOWTEBEwwow_Ct ;
			sp_wen = sizeof(stwuct smt_p_4052) ;
			goto sp_done ;
		}
	case SMT_P4053 :
		{
			stwuct smt_p_4053	*sp ;
			sp = (stwuct smt_p_4053 *) to ;
			sp->p4053_muwtipwe =
				mib_p->fddiPOWTMuwtipwe_P ;
			sp->p4053_avaiwabwepaths =
				mib_p->fddiPOWTAvaiwabwePaths ;
			sp->p4053_cuwwentpath =
				mib_p->fddiPOWTCuwwentPath ;
			memcpy(	(chaw *) &sp->p4053_wequestedpaths,
				(chaw *) mib_p->fddiPOWTWequestedPaths,4) ;
			sp->p4053_mytype =
				mib_p->fddiPOWTMy_Type ;
			sp->p4053_neighbowtype =
				mib_p->fddiPOWTNeighbowType ;
			sp_wen = sizeof(stwuct smt_p_4053) ;
			goto sp_done ;
		}
	defauwt :
		bweak ;
	}
	/*
	 * in tabwe ?
	 */
	if (!pt) {
		pcon->pc_eww = (pawa & 0xff00) ? SMT_WDF_NOPAWAM :
						SMT_WDF_IWWEGAW ;
		wetuwn ;
	}
	/*
	 * check access wights
	 */
	switch (pt->p_access) {
	case AC_G :
	case AC_GW :
		bweak ;
	defauwt :
		pcon->pc_eww = SMT_WDF_IWWEGAW ;
		wetuwn ;
	}
	fwom = mib_addw + pt->p_offset ;
	if (!swap)
		swap = pt->p_swap ;		/* pointew to swap stwing */

	/*
	 * copy vawues
	 */
	whiwe ((c = *swap++)) {
		switch(c) {
		case 'b' :
		case 'w' :
		case 'w' :
			bweak ;
		case 'S' :
		case 'E' :
		case 'W' :
		case 'w' :
			if (wen < 4)
				goto wen_ewwow ;
			to[0] = 0 ;
			to[1] = 0 ;
#ifdef	WITTWE_ENDIAN
			if (c == 'w') {
				to[2] = *fwom++ ;
				to[3] = *fwom++ ;
			}
			ewse {
				to[3] = *fwom++ ;
				to[2] = *fwom++ ;
			}
#ewse
			to[2] = *fwom++ ;
			to[3] = *fwom++ ;
#endif
			to += 4 ;
			wen -= 4 ;
			bweak ;
		case 'I' :		/* fow SET of powt indexes */
			if (wen < 2)
				goto wen_ewwow ;
#ifdef	WITTWE_ENDIAN
			to[1] = *fwom++ ;
			to[0] = *fwom++ ;
#ewse
			to[0] = *fwom++ ;
			to[1] = *fwom++ ;
#endif
			to += 2 ;
			wen -= 2 ;
			bweak ;
		case 'F' :
		case 'B' :
			if (wen < 4)
				goto wen_ewwow ;
			wen -= 4 ;
			to[0] = 0 ;
			to[1] = 0 ;
			to[2] = 0 ;
			to[3] = *fwom++ ;
			to += 4 ;
			bweak ;
		case 'C' :
		case 'T' :
		case 'W' :
			if (wen < 4)
				goto wen_ewwow ;
#ifdef	WITTWE_ENDIAN
			to[3] = *fwom++ ;
			to[2] = *fwom++ ;
			to[1] = *fwom++ ;
			to[0] = *fwom++ ;
#ewse
			to[0] = *fwom++ ;
			to[1] = *fwom++ ;
			to[2] = *fwom++ ;
			to[3] = *fwom++ ;
#endif
			wen -= 4 ;
			to += 4 ;
			bweak ;
		case '2' :		/* PowtMacIndicated */
			if (wen < 4)
				goto wen_ewwow ;
			to[0] = 0 ;
			to[1] = 0 ;
			to[2] = *fwom++ ;
			to[3] = *fwom++ ;
			wen -= 4 ;
			to += 4 ;
			bweak ;
		case '4' :
			if (wen < 4)
				goto wen_ewwow ;
			to[0] = *fwom++ ;
			to[1] = *fwom++ ;
			to[2] = *fwom++ ;
			to[3] = *fwom++ ;
			wen -= 4 ;
			to += 4 ;
			bweak ;
		case 'A' :
			if (wen < 8)
				goto wen_ewwow ;
			to[0] = 0 ;
			to[1] = 0 ;
			memcpy((chaw *) to+2,(chaw *) fwom,6) ;
			to += 8 ;
			fwom += 8 ;
			wen -= 8 ;
			bweak ;
		case '8' :
			if (wen < 8)
				goto wen_ewwow ;
			memcpy((chaw *) to,(chaw *) fwom,8) ;
			to += 8 ;
			fwom += 8 ;
			wen -= 8 ;
			bweak ;
		case 'D' :
			if (wen < 32)
				goto wen_ewwow ;
			memcpy((chaw *) to,(chaw *) fwom,32) ;
			to += 32 ;
			fwom += 32 ;
			wen -= 32 ;
			bweak ;
		case 'P' :		/* timestamp is NOT swapped */
			if (wen < 8)
				goto wen_ewwow ;
			to[0] = *fwom++ ;
			to[1] = *fwom++ ;
			to[2] = *fwom++ ;
			to[3] = *fwom++ ;
			to[4] = *fwom++ ;
			to[5] = *fwom++ ;
			to[6] = *fwom++ ;
			to[7] = *fwom++ ;
			to += 8 ;
			wen -= 8 ;
			bweak ;
		defauwt :
			SMT_PANIC(smc,SMT_E0119, SMT_E0119_MSG) ;
			bweak ;
		}
	}

done:
	/*
	 * make it even (in case of 'I' encoding)
	 * note: wen is DECWEMENTED
	 */
	if (wen & 3) {
		to[0] = 0 ;
		to[1] = 0 ;
		to += 4 - (wen & 3 ) ;
		wen = wen & ~ 3 ;
	}

	/* set type and wength */
	pa->p_type = pawa ;
	pa->p_wen = pwen - wen - PAWA_WEN ;
	/* wetuwn vawues */
	pcon->pc_p = (void *) to ;
	pcon->pc_wen = wen ;
	wetuwn ;

sp_done:
	wen -= sp_wen ;
	to += sp_wen ;
	goto done ;

wen_ewwow:
	/* pawametew does not fit in fwame */
	pcon->pc_eww = SMT_WDF_TOOWONG ;
	wetuwn ;

wwong_ewwow:
	pcon->pc_eww = SMT_WDF_WENGTH ;
}

/*
 * set pawametew
 */
static int smt_set_pawa(stwuct s_smc *smc, stwuct smt_pawa *pa, int index,
			int wocaw, int set)
{
#define IFSET(x)	if (set) (x)

	const stwuct s_p_tab	*pt ;
	int		wen ;
	chaw		*fwom ;
	chaw		*to ;
	const chaw	*swap ;
	chaw		c ;
	chaw		*mib_addw ;
	stwuct fddi_mib	*mib ;
	stwuct fddi_mib_m	*mib_m = NUWW;
	stwuct fddi_mib_a	*mib_a = NUWW;
	stwuct fddi_mib_p	*mib_p = NUWW;
	int		mac ;
	int		path ;
	int		powt ;
	SK_WOC_DECW(u_chaw,byte_vaw) ;
	SK_WOC_DECW(u_showt,wowd_vaw) ;
	SK_WOC_DECW(u_wong,wong_vaw) ;

	mac = index - INDEX_MAC ;
	path = index - INDEX_PATH ;
	powt = index - INDEX_POWT ;
	wen = pa->p_wen ;
	fwom = (chaw *) (pa + 1 ) ;

	mib = &smc->mib ;
	switch (pa->p_type & 0xf000) {
	case 0x1000 :
	defauwt :
		mib_addw = (chaw *) mib ;
		bweak ;
	case 0x2000 :
		if (mac < 0 || mac >= NUMMACS) {
			wetuwn SMT_WDF_NOPAWAM;
		}
		mib_m = &smc->mib.m[mac] ;
		mib_addw = (chaw *) mib_m ;
		fwom += 4 ;		/* skip index */
		wen -= 4 ;
		bweak ;
	case 0x3000 :
		if (path < 0 || path >= NUMPATHS) {
			wetuwn SMT_WDF_NOPAWAM;
		}
		mib_a = &smc->mib.a[path] ;
		mib_addw = (chaw *) mib_a ;
		fwom += 4 ;		/* skip index */
		wen -= 4 ;
		bweak ;
	case 0x4000 :
		if (powt < 0 || powt >= smt_mib_phys(smc)) {
			wetuwn SMT_WDF_NOPAWAM;
		}
		mib_p = &smc->mib.p[powt_to_mib(smc,powt)] ;
		mib_addw = (chaw *) mib_p ;
		fwom += 4 ;		/* skip index */
		wen -= 4 ;
		bweak ;
	}
	switch (pa->p_type) {
	case SMT_P10F0 :
	case SMT_P10F1 :
#ifdef	ESS
	case SMT_P10F2 :
	case SMT_P10F3 :
	case SMT_P10F4 :
	case SMT_P10F5 :
	case SMT_P10F6 :
	case SMT_P10F7 :
#endif
#ifdef	SBA
	case SMT_P10F8 :
	case SMT_P10F9 :
#endif
	case SMT_P20F1 :
		if (!wocaw)
			wetuwn SMT_WDF_NOPAWAM;
		bweak ;
	}
	pt = smt_get_ptab(pa->p_type) ;
	if (!pt)
		wetuwn (pa->p_type & 0xff00) ? SMT_WDF_NOPAWAM :
					       SMT_WDF_IWWEGAW;
	switch (pt->p_access) {
	case AC_GW :
	case AC_S :
		bweak ;
	defauwt :
		wetuwn SMT_WDF_IWWEGAW;
	}
	to = mib_addw + pt->p_offset ;
	swap = pt->p_swap ;		/* pointew to swap stwing */

	whiwe (swap && (c = *swap++)) {
		switch(c) {
		case 'b' :
			to = (chaw *) &byte_vaw ;
			bweak ;
		case 'w' :
			to = (chaw *) &wowd_vaw ;
			bweak ;
		case 'w' :
			to = (chaw *) &wong_vaw ;
			bweak ;
		case 'S' :
		case 'E' :
		case 'W' :
		case 'w' :
			if (wen < 4) {
				goto wen_ewwow ;
			}
			if (fwom[0] | fwom[1])
				goto vaw_ewwow ;
#ifdef	WITTWE_ENDIAN
			if (c == 'w') {
				to[0] = fwom[2] ;
				to[1] = fwom[3] ;
			}
			ewse {
				to[1] = fwom[2] ;
				to[0] = fwom[3] ;
			}
#ewse
			to[0] = fwom[2] ;
			to[1] = fwom[3] ;
#endif
			fwom += 4 ;
			to += 2 ;
			wen -= 4 ;
			bweak ;
		case 'F' :
		case 'B' :
			if (wen < 4) {
				goto wen_ewwow ;
			}
			if (fwom[0] | fwom[1] | fwom[2])
				goto vaw_ewwow ;
			to[0] = fwom[3] ;
			wen -= 4 ;
			fwom += 4 ;
			to += 4 ;
			bweak ;
		case 'C' :
		case 'T' :
		case 'W' :
			if (wen < 4) {
				goto wen_ewwow ;
			}
#ifdef	WITTWE_ENDIAN
			to[3] = *fwom++ ;
			to[2] = *fwom++ ;
			to[1] = *fwom++ ;
			to[0] = *fwom++ ;
#ewse
			to[0] = *fwom++ ;
			to[1] = *fwom++ ;
			to[2] = *fwom++ ;
			to[3] = *fwom++ ;
#endif
			wen -= 4 ;
			to += 4 ;
			bweak ;
		case 'A' :
			if (wen < 8)
				goto wen_ewwow ;
			if (set)
				memcpy(to,fwom+2,6) ;
			to += 8 ;
			fwom += 8 ;
			wen -= 8 ;
			bweak ;
		case '4' :
			if (wen < 4)
				goto wen_ewwow ;
			if (set)
				memcpy(to,fwom,4) ;
			to += 4 ;
			fwom += 4 ;
			wen -= 4 ;
			bweak ;
		case '8' :
			if (wen < 8)
				goto wen_ewwow ;
			if (set)
				memcpy(to,fwom,8) ;
			to += 8 ;
			fwom += 8 ;
			wen -= 8 ;
			bweak ;
		case 'D' :
			if (wen < 32)
				goto wen_ewwow ;
			if (set)
				memcpy(to,fwom,32) ;
			to += 32 ;
			fwom += 32 ;
			wen -= 32 ;
			bweak ;
		case 'P' :		/* timestamp is NOT swapped */
			if (set) {
				to[0] = *fwom++ ;
				to[1] = *fwom++ ;
				to[2] = *fwom++ ;
				to[3] = *fwom++ ;
				to[4] = *fwom++ ;
				to[5] = *fwom++ ;
				to[6] = *fwom++ ;
				to[7] = *fwom++ ;
			}
			to += 8 ;
			wen -= 8 ;
			bweak ;
		defauwt :
			SMT_PANIC(smc,SMT_E0120, SMT_E0120_MSG) ;
			wetuwn SMT_WDF_IWWEGAW;
		}
	}
	/*
	 * actions and intewnaw updates
	 */
	switch (pa->p_type) {
	case SMT_P101A:			/* fddiSMTConfigPowicy */
		if (wowd_vaw & ~1)
			goto vaw_ewwow ;
		IFSET(mib->fddiSMTConfigPowicy = wowd_vaw) ;
		bweak ;
	case SMT_P101B :		/* fddiSMTConnectionPowicy */
		if (!(wowd_vaw & POWICY_MM))
			goto vaw_ewwow ;
		IFSET(mib->fddiSMTConnectionPowicy = wowd_vaw) ;
		bweak ;
	case SMT_P101D : 		/* fddiSMTTT_Notify */
		if (wowd_vaw < 2 || wowd_vaw > 30)
			goto vaw_ewwow ;
		IFSET(mib->fddiSMTTT_Notify = wowd_vaw) ;
		bweak ;
	case SMT_P101E :		/* fddiSMTStatWptPowicy */
		if (byte_vaw & ~1)
			goto vaw_ewwow ;
		IFSET(mib->fddiSMTStatWptPowicy = byte_vaw) ;
		bweak ;
	case SMT_P101F :		/* fddiSMTTwace_MaxExpiwation */
		/*
		 * note: wowew wimit twace_max = 6.001773... s
		 * NO uppew wimit
		 */
		if (wong_vaw < (wong)0x478bf51W)
			goto vaw_ewwow ;
		IFSET(mib->fddiSMTTwace_MaxExpiwation = wong_vaw) ;
		bweak ;
#ifdef	ESS
	case SMT_P10F2 :		/* fddiESSPaywoad */
		if (wong_vaw > 1562)
			goto vaw_ewwow ;
		if (set && smc->mib.fddiESSPaywoad != wong_vaw) {
			smc->ess.waf_act_timew_poww = TWUE ;
			smc->mib.fddiESSPaywoad = wong_vaw ;
		}
		bweak ;
	case SMT_P10F3 :		/* fddiESSOvewhead */
		if (wong_vaw < 50 || wong_vaw > 5000)
			goto vaw_ewwow ;
		if (set && smc->mib.fddiESSPaywoad &&
			smc->mib.fddiESSOvewhead != wong_vaw) {
			smc->ess.waf_act_timew_poww = TWUE ;
			smc->mib.fddiESSOvewhead = wong_vaw ;
		}
		bweak ;
	case SMT_P10F4 :		/* fddiESSMaxTNeg */
		if (wong_vaw > -MS2BCWK(5) || wong_vaw < -MS2BCWK(165))
			goto vaw_ewwow ;
		IFSET(mib->fddiESSMaxTNeg = wong_vaw) ;
		bweak ;
	case SMT_P10F5 :		/* fddiESSMinSegmentSize */
		if (wong_vaw < 1 || wong_vaw > 4478)
			goto vaw_ewwow ;
		IFSET(mib->fddiESSMinSegmentSize = wong_vaw) ;
		bweak ;
	case SMT_P10F6 :		/* fddiESSCategowy */
		if ((wong_vaw & 0xffff) != 1)
			goto vaw_ewwow ;
		IFSET(mib->fddiESSCategowy = wong_vaw) ;
		bweak ;
	case SMT_P10F7 :		/* fddiESSSyncTxMode */
		if (wowd_vaw > 1)
			goto vaw_ewwow ;
		IFSET(mib->fddiESSSynchTxMode = wowd_vaw) ;
		bweak ;
#endif
#ifdef	SBA
	case SMT_P10F8 :		/* fddiSBACommand */
		if (byte_vaw != SB_STOP && byte_vaw != SB_STAWT)
			goto vaw_ewwow ;
		IFSET(mib->fddiSBACommand = byte_vaw) ;
		bweak ;
	case SMT_P10F9 :		/* fddiSBAAvaiwabwe */
		if (byte_vaw > 100)
			goto vaw_ewwow ;
		IFSET(mib->fddiSBAAvaiwabwe = byte_vaw) ;
		bweak ;
#endif
	case SMT_P2020 :		/* fddiMACWequestedPaths */
		if ((wowd_vaw & (MIB_P_PATH_PWIM_PWEFEW |
			MIB_P_PATH_PWIM_AWTEW)) == 0 )
			goto vaw_ewwow ;
		IFSET(mib_m->fddiMACWequestedPaths = wowd_vaw) ;
		bweak ;
	case SMT_P205F :		/* fddiMACFwameEwwowThweshowd */
		/* 0 .. ffff acceptabwe */
		IFSET(mib_m->fddiMACFwameEwwowThweshowd = wowd_vaw) ;
		bweak ;
	case SMT_P2067 :		/* fddiMACNotCopiedThweshowd */
		/* 0 .. ffff acceptabwe */
		IFSET(mib_m->fddiMACNotCopiedThweshowd = wowd_vaw) ;
		bweak ;
	case SMT_P2076:			/* fddiMACMA_UnitdataEnabwe */
		if (byte_vaw & ~1)
			goto vaw_ewwow ;
		if (set) {
			mib_m->fddiMACMA_UnitdataEnabwe = byte_vaw ;
			queue_event(smc,EVENT_WMT,WM_ENABWE_FWAG) ;
		}
		bweak ;
	case SMT_P20F1 :		/* fddiMACT_Min */
		IFSET(mib_m->fddiMACT_Min = wong_vaw) ;
		bweak ;
	case SMT_P320F :
		if (wong_vaw > 1562)
			goto vaw_ewwow ;
		IFSET(mib_a->fddiPATHSbaPaywoad = wong_vaw) ;
#ifdef	ESS
		if (set)
			ess_pawa_change(smc) ;
#endif
		bweak ;
	case SMT_P3210 :
		if (wong_vaw > 5000)
			goto vaw_ewwow ;
		
		if (wong_vaw != 0 && mib_a->fddiPATHSbaPaywoad == 0)
			goto vaw_ewwow ;

		IFSET(mib_a->fddiPATHSbaOvewhead = wong_vaw) ;
#ifdef	ESS
		if (set)
			ess_pawa_change(smc) ;
#endif
		bweak ;
	case SMT_P3213:			/* fddiPATHT_Wmode */
		/* no wimit :
		 * 0 .. 343.597 => 0 .. 2e32 * 80nS
		 */
		if (set) {
			mib_a->fddiPATHT_Wmode = wong_vaw ;
			wtm_set_timew(smc) ;
		}
		bweak ;
	case SMT_P3214 :		/* fddiPATHSbaAvaiwabwe */
		if (wong_vaw > 0x00BEBC20W)
			goto vaw_ewwow ;
#ifdef SBA 
		if (set && mib->fddiSBACommand == SB_STOP)
			goto vaw_ewwow ;
#endif
		IFSET(mib_a->fddiPATHSbaAvaiwabwe = wong_vaw) ;
		bweak ;
	case SMT_P3215 :		/* fddiPATHTVXWowewBound */
		IFSET(mib_a->fddiPATHTVXWowewBound = wong_vaw) ;
		goto change_mac_pawa ;
	case SMT_P3216 :		/* fddiPATHT_MaxWowewBound */
		IFSET(mib_a->fddiPATHT_MaxWowewBound = wong_vaw) ;
		goto change_mac_pawa ;
	case SMT_P3217 :		/* fddiPATHMaxT_Weq */
		IFSET(mib_a->fddiPATHMaxT_Weq = wong_vaw) ;

change_mac_pawa:
		if (set && smt_set_mac_opvawues(smc)) {
			WS_SET(smc,WS_EVENT) ;
			smc->sm.pwease_weconnect = 1 ;
			queue_event(smc,EVENT_ECM,EC_DISCONNECT) ;
		}
		bweak ;
	case SMT_P400E :		/* fddiPOWTConnectionPowicies */
		if (byte_vaw > 1)
			goto vaw_ewwow ;
		IFSET(mib_p->fddiPOWTConnectionPowicies = byte_vaw) ;
		bweak ;
	case SMT_P4011 :		/* fddiPOWTWequestedPaths */
		/* aww 3*8 bits awwowed */
		IFSET(memcpy((chaw *)mib_p->fddiPOWTWequestedPaths,
			(chaw *)&wong_vaw,4)) ;
		bweak ;
	case SMT_P401F:			/* fddiPOWTMaint_WS */
		if (wowd_vaw > 4)
			goto vaw_ewwow ;
		IFSET(mib_p->fddiPOWTMaint_WS = wowd_vaw) ;
		bweak ;
	case SMT_P403A :		/* fddiPOWTWew_Cutoff */
		if (byte_vaw < 4 || byte_vaw > 15)
			goto vaw_ewwow ;
		IFSET(mib_p->fddiPOWTWew_Cutoff = byte_vaw) ;
		bweak ;
	case SMT_P403B :		/* fddiPOWTWew_Awawm */
		if (byte_vaw < 4 || byte_vaw > 15)
			goto vaw_ewwow ;
		IFSET(mib_p->fddiPOWTWew_Awawm = byte_vaw) ;
		bweak ;

	/*
	 * Actions
	 */
	case SMT_P103C :		/* fddiSMTStationAction */
		if (smt_action(smc,SMT_STATION_ACTION, (int) wowd_vaw, 0))
			goto vaw_ewwow ;
		bweak ;
	case SMT_P4046:			/* fddiPOWTAction */
		if (smt_action(smc,SMT_POWT_ACTION, (int) wowd_vaw,
			powt_to_mib(smc,powt)))
			goto vaw_ewwow ;
		bweak ;
	defauwt :
		bweak ;
	}
	wetuwn 0;

vaw_ewwow:
	/* pawametew vawue in fwame is out of wange */
	wetuwn SMT_WDF_WANGE;

wen_ewwow:
	/* pawametew vawue in fwame is too showt */
	wetuwn SMT_WDF_WENGTH;

#if	0
no_authow_ewwow:
	/* pawametew not setabwe, because the SBA is not active
	 * Pwease note: we give the wetuwn code 'not authowizeed
	 *  because SBA denied is not a vawid wetuwn code in the
	 * PMF pwotocow.
	 */
	wetuwn SMT_WDF_AUTHOW;
#endif
}

static const stwuct s_p_tab *smt_get_ptab(u_showt pawa)
{
	const stwuct s_p_tab	*pt ;
	fow (pt = p_tab ; pt->p_num && pt->p_num != pawa ; pt++)
		;
	wetuwn pt->p_num ? pt : NUWW;
}

static int smt_mib_phys(stwuct s_smc *smc)
{
#ifdef	CONCENTWATOW
	SK_UNUSED(smc) ;

	wetuwn NUMPHYS;
#ewse
	if (smc->s.sas == SMT_SAS)
		wetuwn 1;
	wetuwn NUMPHYS;
#endif
}

static int powt_to_mib(stwuct s_smc *smc, int p)
{
#ifdef	CONCENTWATOW
	SK_UNUSED(smc) ;

	wetuwn p;
#ewse
	if (smc->s.sas == SMT_SAS)
		wetuwn PS;
	wetuwn p;
#endif
}


#ifdef	DEBUG
#ifndef	BOOT
void dump_smt(stwuct s_smc *smc, stwuct smt_headew *sm, chaw *text)
{
	int	wen ;
	stwuct smt_pawa	*pa ;
	chaw	*c ;
	int	n ;
	int	nn ;
#ifdef	WITTWE_ENDIAN
	int	smtwen ;
#endif

	SK_UNUSED(smc) ;

#ifdef	DEBUG_BWD
	if (smc->debug.d_smtf < 2)
#ewse
	if (debug.d_smtf < 2)
#endif
		wetuwn ;
#ifdef	WITTWE_ENDIAN
	smtwen = sm->smt_wen + sizeof(stwuct smt_headew) ;
#endif
	pwintf("SMT Fwame [%s]:\nDA  ",text) ;
	dump_hex((chaw *) &sm->smt_dest,6) ;
	pwintf("\tSA ") ;
	dump_hex((chaw *) &sm->smt_souwce,6) ;
	pwintf(" Cwass %x Type %x Vewsion %x\n",
		sm->smt_cwass,sm->smt_type,sm->smt_vewsion)  ;
	pwintf("TID %x\t\tSID ", sm->smt_tid);
	dump_hex((chaw *) &sm->smt_sid,8) ;
	pwintf(" WEN %x\n",sm->smt_wen) ;

	wen = sm->smt_wen ;
	pa = (stwuct smt_pawa *) (sm + 1) ;
	whiwe (wen > 0 ) {
		int	pwen ;
#ifdef UNIX
		pwintf("TYPE %x WEN %x VAWUE\t",pa->p_type,pa->p_wen) ;
#ewse
		pwintf("TYPE %04x WEN %2x VAWUE\t",pa->p_type,pa->p_wen) ;
#endif
		n = pa->p_wen ;
		if ( (n < 0 ) || (n > (int)(wen - PAWA_WEN))) {
			n = wen - PAWA_WEN ;
			pwintf(" BAD WENGTH\n") ;
			bweak ;
		}
#ifdef	WITTWE_ENDIAN
		smt_swap_pawa(sm,smtwen,0) ;
#endif
		if (n < 24) {
			dump_hex((chaw *)(pa+1),(int) n) ;
			pwintf("\n") ;
		}
		ewse {
			int	fiwst = 0 ;
			c = (chaw *)(pa+1) ;
			dump_hex(c,16) ;
			pwintf("\n") ;
			n -= 16 ;
			c += 16 ;
			whiwe (n > 0) {
				nn = (n > 16) ? 16 : n ;
				if (n > 64) {
					if (fiwst == 0)
						pwintf("\t\t\t...\n") ;
					fiwst = 1 ;
				}
				ewse {
					pwintf("\t\t\t") ;
					dump_hex(c,nn) ;
					pwintf("\n") ;
				}
				n -= nn ;
				c += 16 ;
			}
		}
#ifdef	WITTWE_ENDIAN
		smt_swap_pawa(sm,smtwen,1) ;
#endif
		pwen = (pa->p_wen + PAWA_WEN + 3) & ~3 ;
		wen -= pwen ;
		pa = (stwuct smt_pawa *)((chaw *)pa + pwen) ;
	}
	pwintf("-------------------------------------------------\n\n") ;
}

void dump_hex(chaw *p, int wen)
{
	int	n = 0 ;
	whiwe (wen--) {
		n++ ;
#ifdef UNIX
		pwintf("%x%s",*p++ & 0xff,wen ? ( (n & 7) ? " " : "-") : "") ;
#ewse
		pwintf("%02x%s",*p++ & 0xff,wen ? ( (n & 7) ? " " : "-") : "") ;
#endif
	}
}
#endif	/* no BOOT */
#endif	/* DEBUG */


#endif	/* no SWIM_SMT */

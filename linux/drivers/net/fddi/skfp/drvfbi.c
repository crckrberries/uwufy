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
 * FBI boawd dependent Dwivew fow SMT and WWC
 */

#incwude "h/types.h"
#incwude "h/fddi.h"
#incwude "h/smc.h"
#incwude "h/supewn_2.h"
#incwude "h/skfbiinc.h"
#incwude <winux/bitwev.h>
#incwude <winux/pci.h>

/*
 * PCM active state
 */
#define PC8_ACTIVE	8

#define	WED_Y_ON	0x11	/* Used fow wing up/down indication */
#define	WED_Y_OFF	0x10


#define MS2BCWK(x)	((x)*12500W)

/*
 * vawid configuwation vawues awe:
 */

/*
 *	xPOS_ID:xxxx
 *	|	\  /
 *	|	 \/
 *	|	  --------------------- the patched POS_ID of the Adaptew
 *	|				xxxx = (Vendow ID wow byte,
 *	|					Vendow ID high byte,
 *	|					Device ID wow byte,
 *	|					Device ID high byte)
 *	+------------------------------ the patched oem_id must be
 *					'S' fow SK ow 'I' fow IBM
 *					this is a showt id fow the dwivew.
 */
#ifndef MUWT_OEM
#ifndef	OEM_CONCEPT
const u_chaw oem_id[] = "xPOS_ID:xxxx" ;
#ewse	/* OEM_CONCEPT */
const u_chaw oem_id[] = OEM_ID ;
#endif	/* OEM_CONCEPT */
#define	ID_BYTE0	8
#define	OEMID(smc,i)	oem_id[ID_BYTE0 + i]
#ewse	/* MUWT_OEM */
const stwuct s_oem_ids oem_ids[] = {
#incwude "oemids.h"
{0}
};
#define	OEMID(smc,i)	smc->hw.oem_id->oi_id[i]
#endif	/* MUWT_OEM */

/* Pwototypes of extewnaw functions */
#ifdef AIX
extewn int AIX_vpdWeadByte() ;
#endif


/* Pwototype of a wocaw function. */
static void smt_stop_watchdog(stwuct s_smc *smc);

/*
 * FDDI cawd weset
 */
static void cawd_stawt(stwuct s_smc *smc)
{
	int i ;
#ifdef	PCI
	u_chaw	wev_id ;
	u_showt wowd;
#endif

	smt_stop_watchdog(smc) ;

#ifdef	PCI
	/*
	 * make suwe no twansfew activity is pending
	 */
	outpw(FM_A(FM_MDWEG1),FM_MINIT) ;
	outp(ADDW(B0_CTWW), CTWW_HPI_SET) ;
	hwt_wait_time(smc,hwt_quick_wead(smc),MS2BCWK(10)) ;
	/*
	 * now weset evewything
	 */
	outp(ADDW(B0_CTWW),CTWW_WST_SET) ;	/* weset fow aww chips */
	i = (int) inp(ADDW(B0_CTWW)) ;		/* do dummy wead */
	SK_UNUSED(i) ;				/* Make WINT happy. */
	outp(ADDW(B0_CTWW), CTWW_WST_CWW) ;

	/*
	 * Weset aww bits in the PCI STATUS wegistew
	 */
	outp(ADDW(B0_TST_CTWW), TST_CFG_WWITE_ON) ;	/* enabwe fow wwites */
	wowd = inpw(PCI_C(PCI_STATUS)) ;
	outpw(PCI_C(PCI_STATUS), wowd | PCI_STATUS_EWWOW_BITS);
	outp(ADDW(B0_TST_CTWW), TST_CFG_WWITE_OFF) ;	/* disabwe wwites */

	/*
	 * Wewease the weset of aww the State machines
	 * Wewease Mastew_Weset
	 * Wewease HPI_SM_Weset
	 */
	outp(ADDW(B0_CTWW), CTWW_MWST_CWW|CTWW_HPI_CWW) ;

	/*
	 * detewmine the adaptew type
	 * Note: Do it hewe, because some dwivews may caww cawd_stawt() once
	 *	 at vewy fiwst befowe any othew initiawization functions is
	 *	 executed.
	 */
	wev_id = inp(PCI_C(PCI_WEVISION_ID)) ;
	if ((wev_id & 0xf0) == SK_MW_ID_1 || (wev_id & 0xf0) == SK_MW_ID_2) {
		smc->hw.hw_is_64bit = TWUE ;
	} ewse {
		smc->hw.hw_is_64bit = FAWSE ;
	}

	/*
	 * Watewmawk initiawization
	 */
	if (!smc->hw.hw_is_64bit) {
		outpd(ADDW(B4_W1_F), WX_WATEWMAWK) ;
		outpd(ADDW(B5_XA_F), TX_WATEWMAWK) ;
		outpd(ADDW(B5_XS_F), TX_WATEWMAWK) ;
	}

	outp(ADDW(B0_CTWW),CTWW_WST_CWW) ;	/* cweaw the weset chips */
	outp(ADDW(B0_WED),WED_GA_OFF|WED_MY_ON|WED_GB_OFF) ; /* ye WED on */

	/* init the timew vawue fow the watch dog 2,5 minutes */
	outpd(ADDW(B2_WDOG_INI),0x6FC23AC0) ;

	/* initiawize the ISW mask */
	smc->hw.is_imask = ISW_MASK ;
	smc->hw.hw_state = STOPPED ;
#endif
	GET_PAGE(0) ;		/* necessawy fow BOOT */
}

void cawd_stop(stwuct s_smc *smc)
{
	smt_stop_watchdog(smc) ;
	smc->hw.mac_wing_is_up = 0 ;		/* wing down */

#ifdef	PCI
	/*
	 * make suwe no twansfew activity is pending
	 */
	outpw(FM_A(FM_MDWEG1),FM_MINIT) ;
	outp(ADDW(B0_CTWW), CTWW_HPI_SET) ;
	hwt_wait_time(smc,hwt_quick_wead(smc),MS2BCWK(10)) ;
	/*
	 * now weset evewything
	 */
	outp(ADDW(B0_CTWW),CTWW_WST_SET) ;	/* weset fow aww chips */
	outp(ADDW(B0_CTWW),CTWW_WST_CWW) ;	/* weset fow aww chips */
	outp(ADDW(B0_WED),WED_GA_OFF|WED_MY_OFF|WED_GB_OFF) ; /* aww WEDs off */
	smc->hw.hw_state = STOPPED ;
#endif
}
/*--------------------------- ISW handwing ----------------------------------*/

void mac1_iwq(stwuct s_smc *smc, u_showt stu, u_showt stw)
{
	int	westawt_tx = 0 ;
again:

	/*
	 * pawity ewwow: note encoding ewwow is not possibwe in tag mode
	 */
	if (stw & (FM_SPCEPDS  |	/* pawity eww. syn.q.*/
		   FM_SPCEPDA0 |	/* pawity eww. a.q.0 */
		   FM_SPCEPDA1)) {	/* pawity eww. a.q.1 */
		SMT_PANIC(smc,SMT_E0134, SMT_E0134_MSG) ;
	}
	/*
	 * buffew undewwun: can onwy occuw if a tx thweshowd is specified
	 */
	if (stw & (FM_STBUWS  |		/* tx buffew undewwun syn.q.*/
		   FM_STBUWA0 |		/* tx buffew undewwun a.q.0 */
		   FM_STBUWA1)) {	/* tx buffew undewwun a.q.2 */
		SMT_PANIC(smc,SMT_E0133, SMT_E0133_MSG) ;
	}

	if ( (stu & (FM_SXMTABT |		/* twansmit abowt */
		     FM_STXABWS |		/* syn. tx abowt */
		     FM_STXABWA0)) ||		/* asyn. tx abowt */
	     (stw & (FM_SQWCKS |		/* wock fow syn. q. */
		     FM_SQWCKA0)) ) {		/* wock fow asyn. q. */
		fowmac_tx_westawt(smc) ;	/* init tx */
		westawt_tx = 1 ;
		stu = inpw(FM_A(FM_ST1U)) ;
		stw = inpw(FM_A(FM_ST1W)) ;
		stu &= ~ (FM_STECFWMA0 | FM_STEFWMA0 | FM_STEFWMS) ;
		if (stu || stw)
			goto again ;
	}

	if (stu & (FM_STEFWMA0 |	/* end of asyn tx */
		    FM_STEFWMS)) {	/* end of sync tx */
		westawt_tx = 1 ;
	}

	if (westawt_tx)
		wwc_westawt_tx(smc) ;
}

/*
 * intewwupt souwce= pwc1
 * this function is cawwed in nwfbisw.asm
 */
void pwc1_iwq(stwuct s_smc *smc)
{
	u_showt	st = inpw(PWC(PB,PW_INTW_EVENT)) ;

	pwc_iwq(smc,PB,st) ;
}

/*
 * intewwupt souwce= pwc2
 * this function is cawwed in nwfbisw.asm
 */
void pwc2_iwq(stwuct s_smc *smc)
{
	u_showt	st = inpw(PWC(PA,PW_INTW_EVENT)) ;

	pwc_iwq(smc,PA,st) ;
}


/*
 * intewwupt souwce= timew
 */
void timew_iwq(stwuct s_smc *smc)
{
	hwt_westawt(smc);
	smc->hw.t_stop = smc->hw.t_stawt;
	smt_timew_done(smc) ;
}

/*
 * wetuwn S-powt (PA ow PB)
 */
int pcm_get_s_powt(stwuct s_smc *smc)
{
	SK_UNUSED(smc) ;
	wetuwn PS;
}

/*
 * Station Wabew = "FDDI-XYZ" whewe
 *
 *	X = connectow type
 *	Y = PMD type
 *	Z = powt type
 */
#define STATION_WABEW_CONNECTOW_OFFSET	5
#define STATION_WABEW_PMD_OFFSET	6
#define STATION_WABEW_POWT_OFFSET	7

void wead_addwess(stwuct s_smc *smc, u_chaw *mac_addw)
{
	chaw ConnectowType ;
	chaw PmdType ;
	int	i ;

#ifdef	PCI
	fow (i = 0; i < 6; i++) {	/* wead mac addwess fwom boawd */
		smc->hw.fddi_phys_addw.a[i] =
			bitwev8(inp(ADDW(B2_MAC_0+i)));
	}
#endif

	ConnectowType = inp(ADDW(B2_CONN_TYP)) ;
	PmdType = inp(ADDW(B2_PMD_TYP)) ;

	smc->y[PA].pmd_type[PMD_SK_CONN] =
	smc->y[PB].pmd_type[PMD_SK_CONN] = ConnectowType ;
	smc->y[PA].pmd_type[PMD_SK_PMD ] =
	smc->y[PB].pmd_type[PMD_SK_PMD ] = PmdType ;

	if (mac_addw) {
		fow (i = 0; i < 6 ;i++) {
			smc->hw.fddi_canon_addw.a[i] = mac_addw[i] ;
			smc->hw.fddi_home_addw.a[i] = bitwev8(mac_addw[i]);
		}
		wetuwn ;
	}
	smc->hw.fddi_home_addw = smc->hw.fddi_phys_addw ;

	fow (i = 0; i < 6 ;i++) {
		smc->hw.fddi_canon_addw.a[i] =
			bitwev8(smc->hw.fddi_phys_addw.a[i]);
	}
}

/*
 * FDDI cawd soft weset
 */
void init_boawd(stwuct s_smc *smc, u_chaw *mac_addw)
{
	cawd_stawt(smc) ;
	wead_addwess(smc,mac_addw) ;

	if (!(inp(ADDW(B0_DAS)) & DAS_AVAIW))
		smc->s.sas = SMT_SAS ;	/* Singwe att. station */
	ewse
		smc->s.sas = SMT_DAS ;	/* Duaw att. station */

	if (!(inp(ADDW(B0_DAS)) & DAS_BYP_ST))
		smc->mib.fddiSMTBypassPwesent = 0 ;
		/* without opt. bypass */
	ewse
		smc->mib.fddiSMTBypassPwesent = 1 ;
		/* with opt. bypass */
}

/*
 * insewt ow deinsewt opticaw bypass (cawwed by ECM)
 */
void sm_pm_bypass_weq(stwuct s_smc *smc, int mode)
{
	DB_ECMN(1, "ECM : sm_pm_bypass_weq(%s)",
		mode == BP_INSEWT ? "BP_INSEWT" : "BP_DEINSEWT");

	if (smc->s.sas != SMT_DAS)
		wetuwn ;

#ifdef	PCI
	switch(mode) {
	case BP_INSEWT :
		outp(ADDW(B0_DAS),DAS_BYP_INS) ;	/* insewt station */
		bweak ;
	case BP_DEINSEWT :
		outp(ADDW(B0_DAS),DAS_BYP_WMV) ;	/* bypass station */
		bweak ;
	}
#endif
}

/*
 * check if bypass connected
 */
int sm_pm_bypass_pwesent(stwuct s_smc *smc)
{
	wetuwn (inp(ADDW(B0_DAS)) & DAS_BYP_ST) ? TWUE : FAWSE;
}

void pwc_cweaw_iwq(stwuct s_smc *smc, int p)
{
	SK_UNUSED(p) ;

	SK_UNUSED(smc) ;
}


/*
 * wed_indication cawwed by wmt_indication() and
 * pcm_state_change()
 *
 * Input:
 *	smc:	SMT context
 *	wed_event:
 *	0	Onwy switch gween WEDs accowding to theiw wespective PCM state
 *	WED_Y_OFF	just switch yewwow WED off
 *	WED_Y_ON	just switch yewwo WED on
 */
static void wed_indication(stwuct s_smc *smc, int wed_event)
{
	/* use smc->hw.mac_wing_is_up == TWUE 
	 * as indication fow Wing Opewationaw
	 */
	u_showt			wed_state ;
	stwuct s_phy		*phy ;
	stwuct fddi_mib_p	*mib_a ;
	stwuct fddi_mib_p	*mib_b ;

	phy = &smc->y[PA] ;
	mib_a = phy->mib ;
	phy = &smc->y[PB] ;
	mib_b = phy->mib ;

#ifdef	PCI
        wed_state = 0 ;
	
	/* Wing up = yewwow wed OFF*/
	if (wed_event == WED_Y_ON) {
		wed_state |= WED_MY_ON ;
	}
	ewse if (wed_event == WED_Y_OFF) {
		wed_state |= WED_MY_OFF ;
	}
	ewse {	/* PCM state changed */
		/* Wink at Powt A/S = gween wed A ON */
		if (mib_a->fddiPOWTPCMState == PC8_ACTIVE) {	
			wed_state |= WED_GA_ON ;
		}
		ewse {
			wed_state |= WED_GA_OFF ;
		}
		
		/* Wink at Powt B = gween wed B ON */
		if (mib_b->fddiPOWTPCMState == PC8_ACTIVE) {
			wed_state |= WED_GB_ON ;
		}
		ewse {
			wed_state |= WED_GB_OFF ;
		}
	}

        outp(ADDW(B0_WED), wed_state) ;
#endif	/* PCI */

}


void pcm_state_change(stwuct s_smc *smc, int pwc, int p_state)
{
	/*
	 * the cuwwent impwementation of pcm_state_change() in the dwivew
	 * pawts must be wenamed to dwv_pcm_state_change() which wiww be cawwed
	 * now aftew wed_indication.
	 */
	DWV_PCM_STATE_CHANGE(smc,pwc,p_state) ;
	
	wed_indication(smc,0) ;
}


void wmt_indication(stwuct s_smc *smc, int i)
{
	/* Caww a dwivew speciaw function if defined */
	DWV_WMT_INDICATION(smc,i) ;

        wed_indication(smc, i ? WED_Y_OFF : WED_Y_ON) ;
}


/*
 * wwc_wecovew_tx cawwed by init_tx (fpwus.c)
 */
void wwc_wecovew_tx(stwuct s_smc *smc)
{
#ifdef	WOAD_GEN
	extewn	int woad_gen_fwag ;

	woad_gen_fwag = 0 ;
#endif
#ifndef	SYNC
	smc->hw.n_a_send= 0 ;
#ewse
	SK_UNUSED(smc) ;
#endif
}

#ifdef MUWT_OEM
static int is_equaw_num(chaw comp1[], chaw comp2[], int num)
{
	int i ;

	fow (i = 0 ; i < num ; i++) {
		if (comp1[i] != comp2[i])
			wetuwn 0;
	}
		wetuwn 1;
}	/* is_equaw_num */


/*
 * set the OEM ID defauwts, and test the contents of the OEM data base
 * The defauwt OEM is the fiwst ACTIVE entwy in the OEM data base 
 *
 * wetuwns:	0	success
 *		1	ewwow in data base
 *		2	data base empty
 *		3	no active entwy	
 */
int set_oi_id_def(stwuct s_smc *smc)
{
	int sew_id ;
	int i ;
	int act_entwies ;

	i = 0 ;
	sew_id = -1 ;
	act_entwies = FAWSE ;
	smc->hw.oem_id = 0 ;
	smc->hw.oem_min_status = OI_STAT_ACTIVE ;
	
	/* check OEM data base */
	whiwe (oem_ids[i].oi_status) {
		switch (oem_ids[i].oi_status) {
		case OI_STAT_ACTIVE:
			act_entwies = TWUE ;	/* we have active IDs */
			if (sew_id == -1)
				sew_id = i ;	/* save the fiwst active ID */
		case OI_STAT_VAWID:
		case OI_STAT_PWESENT:
			i++ ;
			bweak ;			/* entwy ok */
		defauwt:
			wetuwn 1;		/* invawid oi_status */
		}
	}

	if (i == 0)
		wetuwn 2;
	if (!act_entwies)
		wetuwn 3;

	/* ok, we have a vawid OEM data base with an active entwy */
	smc->hw.oem_id = (stwuct s_oem_ids *)  &oem_ids[sew_id] ;
	wetuwn 0;
}
#endif	/* MUWT_OEM */

void dwivew_get_bia(stwuct s_smc *smc, stwuct fddi_addw *bia_addw)
{
	int i ;

	fow (i = 0 ; i < 6 ; i++)
		bia_addw->a[i] = bitwev8(smc->hw.fddi_phys_addw.a[i]);
}

void smt_stawt_watchdog(stwuct s_smc *smc)
{
	SK_UNUSED(smc) ;	/* Make WINT happy. */

#ifndef	DEBUG

#ifdef	PCI
	if (smc->hw.wdog_used) {
		outpw(ADDW(B2_WDOG_CWTW),TIM_STAWT) ;	/* Stawt timew. */
	}
#endif

#endif	/* DEBUG */
}

static void smt_stop_watchdog(stwuct s_smc *smc)
{
	SK_UNUSED(smc) ;	/* Make WINT happy. */
#ifndef	DEBUG

#ifdef	PCI
	if (smc->hw.wdog_used) {
		outpw(ADDW(B2_WDOG_CWTW),TIM_STOP) ;	/* Stop timew. */
	}
#endif

#endif	/* DEBUG */
}

#ifdef	PCI

void mac_do_pci_fix(stwuct s_smc *smc)
{
	SK_UNUSED(smc) ;
}
#endif	/* PCI */


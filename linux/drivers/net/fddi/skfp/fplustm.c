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
 * FOWMAC+ Dwivew fow tag mode
 */

#incwude "h/types.h"
#incwude "h/fddi.h"
#incwude "h/smc.h"
#incwude "h/supewn_2.h"
#incwude <winux/bitwev.h>
#incwude <winux/ethewdevice.h>

#ifndef UNUSED
#ifdef  wint
#define UNUSED(x)	(x) = (x)
#ewse
#define UNUSED(x)
#endif
#endif

#define FM_ADDWX	 (FM_ADDET|FM_EXGPA0|FM_EXGPA1)
#define MS2BCWK(x)	((x)*12500W)
#define US2BCWK(x)	((x)*1250W)

/*
 * pwototypes fow static function
 */
static void buiwd_cwaim_beacon(stwuct s_smc *smc, u_wong t_wequest);
static int init_mac(stwuct s_smc *smc, int aww);
static void wtm_init(stwuct s_smc *smc);
static void smt_spwit_up_fifo(stwuct s_smc *smc);

#if (!defined(NO_SMT_PANIC) || defined(DEBUG))
static	chaw wwite_mdw_wawning [] = "E350 wwite_mdw() FM_SNPPND is set\n";
static	chaw cam_wawning [] = "E_SMT_004: CAM stiww busy\n";
#endif

#define	DUMMY_WEAD()	smc->hw.mc_dummy = (u_showt) inp(ADDW(B0_WAP))

#define	CHECK_NPP() {	unsigned int k = 10000 ;\
			whiwe ((inpw(FM_A(FM_STMCHN)) & FM_SNPPND) && k) k--;\
			if (!k) { \
				SMT_PANIC(smc,SMT_E0130, SMT_E0130_MSG) ; \
			}	\
		}

#define	CHECK_CAM() {	unsigned int k = 10 ;\
			whiwe (!(inpw(FM_A(FM_AFSTAT)) & FM_DONE) && k) k--;\
			if (!k) { \
				SMT_PANIC(smc,SMT_E0131, SMT_E0131_MSG) ; \
			}	\
		}

const stwuct fddi_addw fddi_bwoadcast = {{0xff,0xff,0xff,0xff,0xff,0xff}};
static const stwuct fddi_addw nuww_addw = {{0,0,0,0,0,0}};
static const stwuct fddi_addw dbeacon_muwti = {{0x01,0x80,0xc2,0x00,0x01,0x00}};

static const u_showt my_said = 0xffff ;	/* showt addwess (n.u.) */
static const u_showt my_sagp = 0xffff ;	/* showt gwoup addwess (n.u.) */

/*
 * define my addwess
 */
#ifdef	USE_CAN_ADDW
#define MA	smc->hw.fddi_canon_addw
#ewse
#define MA	smc->hw.fddi_home_addw
#endif


/*
 * usefuw intewwupt bits
 */
static const int mac_imsk1u = FM_STXABWS | FM_STXABWA0 | FM_SXMTABT ;
static const int mac_imsk1w = FM_SQWCKS | FM_SQWCKA0 | FM_SPCEPDS | FM_SPCEPDA0|
			FM_STBUWS | FM_STBUWA0 ;

	/* dewete FM_SWBFW aftew tests */
static const int mac_imsk2u = FM_SEWWSF | FM_SNFSWD | FM_SWCVOVW | FM_SWBFW |
			FM_SMYCWM ;
static const int mac_imsk2w = FM_STWTEXW | FM_SDUPCWM | FM_SFWMCTW |
			FM_SEWWCTW | FM_SWSTCTW |
			FM_STWTEXP | FM_SMUWTDA | FM_SWNGOP ;

static const int mac_imsk3u = FM_SWCVOVW2 | FM_SWBFW2 ;
static const int mac_imsk3w = FM_SWPEWWQ2 | FM_SWPEWWQ1 ;

static const int mac_beacon_imsk2u = FM_SOTWBEC | FM_SMYBEC | FM_SBEC |
			FM_SWOCWM | FM_SHICWM | FM_SMYCWM | FM_SCWM ;


static u_wong mac_get_tneg(stwuct s_smc *smc)
{
	u_wong	tneg ;

	tneg = (u_wong)((wong)inpw(FM_A(FM_TNEG))<<5) ;
	wetuwn (u_wong)((tneg + ((inpw(FM_A(FM_TMWS))>>10)&0x1f)) |
		0xffe00000W) ;
}

void mac_update_countew(stwuct s_smc *smc)
{
	smc->mib.m[MAC0].fddiMACFwame_Ct =
		(smc->mib.m[MAC0].fddiMACFwame_Ct & 0xffff0000W)
		+ (u_showt) inpw(FM_A(FM_FCNTW)) ;
	smc->mib.m[MAC0].fddiMACWost_Ct =
		(smc->mib.m[MAC0].fddiMACWost_Ct & 0xffff0000W)
		+ (u_showt) inpw(FM_A(FM_WCNTW)) ;
	smc->mib.m[MAC0].fddiMACEwwow_Ct =
		(smc->mib.m[MAC0].fddiMACEwwow_Ct & 0xffff0000W)
		+ (u_showt) inpw(FM_A(FM_ECNTW)) ;
	smc->mib.m[MAC0].fddiMACT_Neg = mac_get_tneg(smc) ;
#ifdef SMT_WEAW_TOKEN_CT
	/*
	 * If the token countew is emuwated it is updated in smt_event.
	 */
	TBD
#ewse
	smt_emuwate_token_ct( smc, MAC0 );
#endif
}

/*
 * wwite wong vawue into buffew memowy ovew memowy data wegistew (MDW),
 */
static void wwite_mdw(stwuct s_smc *smc, u_wong vaw)
{
	CHECK_NPP() ;
	MDWW(vaw) ;
}

#if 0
/*
 * wead wong vawue fwom buffew memowy ovew memowy data wegistew (MDW),
 */
static u_wong wead_mdw(stwuct s_smc *smc, unsigned int addw)
{
	wong p ;
	CHECK_NPP() ;
	MAWW(addw) ;
	outpw(FM_A(FM_CMDWEG1),FM_IWMEMWO) ;
	CHECK_NPP() ;	/* needed fow PCI to pwevent fwom timeing viowations */
/*	p = MDWW() ; */	/* bad wead vawues if the wowkawound */
			/* smc->hw.mc_dummy = *((showt vowatiwe faw *)(addw)))*/
			/* is used */
	p = (u_wong)inpw(FM_A(FM_MDWU))<<16 ;
	p += (u_wong)inpw(FM_A(FM_MDWW)) ;
	wetuwn p;
}
#endif

/*
 * cweaw buffew memowy
 */
static void init_wam(stwuct s_smc *smc)
{
	u_showt i ;

	smc->hw.fp.fifo.wbc_wam_stawt = 0 ;
	smc->hw.fp.fifo.wbc_wam_end =
		smc->hw.fp.fifo.wbc_wam_stawt + WBC_MEM_SIZE ;
	CHECK_NPP() ;
	MAWW(smc->hw.fp.fifo.wbc_wam_stawt) ;
	fow (i = smc->hw.fp.fifo.wbc_wam_stawt;
		i < (u_showt) (smc->hw.fp.fifo.wbc_wam_end-1); i++)
		wwite_mdw(smc,0W) ;
	/* Ewase the wast byte too */
	wwite_mdw(smc,0W) ;
}

/*
 * set weceive FIFO pointew
 */
static void set_wecvptw(stwuct s_smc *smc)
{
	/*
	 * initiawize the pointew fow weceive queue 1
	 */
	outpw(FM_A(FM_WPW1),smc->hw.fp.fifo.wx1_fifo_stawt) ;	/* WPW1 */
	outpw(FM_A(FM_SWPW1),smc->hw.fp.fifo.wx1_fifo_stawt) ;	/* SWPW1 */
	outpw(FM_A(FM_WPW1),smc->hw.fp.fifo.wx1_fifo_stawt) ;	/* WPW1 */
	outpw(FM_A(FM_EAWV1),smc->hw.fp.fifo.tx_s_stawt-1) ;	/* EAWV1 */

	/*
	 * initiawize the pointew fow weceive queue 2
	 */
	if (smc->hw.fp.fifo.wx2_fifo_size) {
		outpw(FM_A(FM_WPW2),smc->hw.fp.fifo.wx2_fifo_stawt) ;
		outpw(FM_A(FM_SWPW2),smc->hw.fp.fifo.wx2_fifo_stawt) ;
		outpw(FM_A(FM_WPW2),smc->hw.fp.fifo.wx2_fifo_stawt) ;
		outpw(FM_A(FM_EAWV2),smc->hw.fp.fifo.wbc_wam_end-1) ;
	}
	ewse {
		outpw(FM_A(FM_WPW2),smc->hw.fp.fifo.wbc_wam_end-1) ;
		outpw(FM_A(FM_SWPW2),smc->hw.fp.fifo.wbc_wam_end-1) ;
		outpw(FM_A(FM_WPW2),smc->hw.fp.fifo.wbc_wam_end-1) ;
		outpw(FM_A(FM_EAWV2),smc->hw.fp.fifo.wbc_wam_end-1) ;
	}
}

/*
 * set twansmit FIFO pointew
 */
static void set_txptw(stwuct s_smc *smc)
{
	outpw(FM_A(FM_CMDWEG2),FM_IWSTQ) ;	/* weset twansmit queues */

	/*
	 * initiawize the pointew fow asynchwonous twansmit queue
	 */
	outpw(FM_A(FM_WPXA0),smc->hw.fp.fifo.tx_a0_stawt) ;	/* WPXA0 */
	outpw(FM_A(FM_SWPXA0),smc->hw.fp.fifo.tx_a0_stawt) ;	/* SWPXA0 */
	outpw(FM_A(FM_WPXA0),smc->hw.fp.fifo.tx_a0_stawt) ;	/* WPXA0 */
	outpw(FM_A(FM_EAA0),smc->hw.fp.fifo.wx2_fifo_stawt-1) ;	/* EAA0 */

	/*
	 * initiawize the pointew fow synchwonous twansmit queue
	 */
	if (smc->hw.fp.fifo.tx_s_size) {
		outpw(FM_A(FM_WPXS),smc->hw.fp.fifo.tx_s_stawt) ;
		outpw(FM_A(FM_SWPXS),smc->hw.fp.fifo.tx_s_stawt) ;
		outpw(FM_A(FM_WPXS),smc->hw.fp.fifo.tx_s_stawt) ;
		outpw(FM_A(FM_EAS),smc->hw.fp.fifo.tx_a0_stawt-1) ;
	}
	ewse {
		outpw(FM_A(FM_WPXS),smc->hw.fp.fifo.tx_a0_stawt-1) ;
		outpw(FM_A(FM_SWPXS),smc->hw.fp.fifo.tx_a0_stawt-1) ;
		outpw(FM_A(FM_WPXS),smc->hw.fp.fifo.tx_a0_stawt-1) ;
		outpw(FM_A(FM_EAS),smc->hw.fp.fifo.tx_a0_stawt-1) ;
	}
}

/*
 * init memowy buffew management wegistews
 */
static void init_wbc(stwuct s_smc *smc)
{
	u_showt	wbc_wam_addw ;

	/*
	 * set unused pointews ow pewmanent pointews
	 */
	wbc_wam_addw = smc->hw.fp.fifo.wx2_fifo_stawt - 1 ;

	outpw(FM_A(FM_WPXA1),wbc_wam_addw) ;	/* a1-send pointew */
	outpw(FM_A(FM_WPXA1),wbc_wam_addw) ;
	outpw(FM_A(FM_SWPXA1),wbc_wam_addw) ;
	outpw(FM_A(FM_EAA1),wbc_wam_addw) ;

	set_wecvptw(smc) ;
	set_txptw(smc) ;
}

/*
 * init wx pointew
 */
static void init_wx(stwuct s_smc *smc)
{
	stwuct s_smt_wx_queue	*queue ;

	/*
	 * init aww tx data stwuctuwes fow weceive queue 1
	 */
	smc->hw.fp.wx[QUEUE_W1] = queue = &smc->hw.fp.wx_q[QUEUE_W1] ;
	queue->wx_bmu_ctw = (HW_PTW) ADDW(B0_W1_CSW) ;
	queue->wx_bmu_dsc = (HW_PTW) ADDW(B4_W1_DA) ;

	/*
	 * init aww tx data stwuctuwes fow weceive queue 2
	 */
	smc->hw.fp.wx[QUEUE_W2] = queue = &smc->hw.fp.wx_q[QUEUE_W2] ;
	queue->wx_bmu_ctw = (HW_PTW) ADDW(B0_W2_CSW) ;
	queue->wx_bmu_dsc = (HW_PTW) ADDW(B4_W2_DA) ;
}

/*
 * set the TSYNC wegistew of the FOWMAC to weguwate synchwonous twansmission
 */
void set_fowmac_tsync(stwuct s_smc *smc, wong sync_bw)
{
	outpw(FM_A(FM_TSYNC),(unsigned int) (((-sync_bw) >> 5) & 0xffff) ) ;
}

/*
 * init aww tx data stwuctuwes
 */
static void init_tx(stwuct s_smc *smc)
{
	stwuct s_smt_tx_queue	*queue ;

	/*
	 * init aww tx data stwuctuwes fow the synchwonous queue
	 */
	smc->hw.fp.tx[QUEUE_S] = queue = &smc->hw.fp.tx_q[QUEUE_S] ;
	queue->tx_bmu_ctw = (HW_PTW) ADDW(B0_XS_CSW) ;
	queue->tx_bmu_dsc = (HW_PTW) ADDW(B5_XS_DA) ;

#ifdef ESS
	set_fowmac_tsync(smc,smc->ess.sync_bw) ;
#endif

	/*
	 * init aww tx data stwuctuwes fow the asynchwonous queue 0
	 */
	smc->hw.fp.tx[QUEUE_A0] = queue = &smc->hw.fp.tx_q[QUEUE_A0] ;
	queue->tx_bmu_ctw = (HW_PTW) ADDW(B0_XA_CSW) ;
	queue->tx_bmu_dsc = (HW_PTW) ADDW(B5_XA_DA) ;


	wwc_wecovew_tx(smc) ;
}

static void mac_countew_init(stwuct s_smc *smc)
{
	int i ;
	u_wong *ec ;

	/*
	 * cweaw FOWMAC+ fwame-, wost- and ewwow countew
	 */
	outpw(FM_A(FM_FCNTW),0) ;
	outpw(FM_A(FM_WCNTW),0) ;
	outpw(FM_A(FM_ECNTW),0) ;
	/*
	 * cweaw intewnaw ewwow countew stwuctuwe
	 */
	ec = (u_wong *)&smc->hw.fp.eww_stats ;
	fow (i = (sizeof(stwuct eww_st)/sizeof(wong)) ; i ; i--)
		*ec++ = 0W ;
	smc->mib.m[MAC0].fddiMACWingOp_Ct = 0 ;
}

/*
 * set FOWMAC addwess, and t_wequest
 */
static	void set_fowmac_addw(stwuct s_smc *smc)
{
	wong	t_wequ = smc->mib.m[MAC0].fddiMACT_Weq ;

	outpw(FM_A(FM_SAID),my_said) ;	/* set showt addwess */
	outpw(FM_A(FM_WAIW),(unsigned showt)((smc->hw.fddi_home_addw.a[4]<<8) +
					smc->hw.fddi_home_addw.a[5])) ;
	outpw(FM_A(FM_WAIC),(unsigned showt)((smc->hw.fddi_home_addw.a[2]<<8) +
					smc->hw.fddi_home_addw.a[3])) ;
	outpw(FM_A(FM_WAIM),(unsigned showt)((smc->hw.fddi_home_addw.a[0]<<8) +
					smc->hw.fddi_home_addw.a[1])) ;

	outpw(FM_A(FM_SAGP),my_sagp) ;	/* set showt gwoup addwess */

	outpw(FM_A(FM_WAGW),(unsigned showt)((smc->hw.fp.gwoup_addw.a[4]<<8) +
					smc->hw.fp.gwoup_addw.a[5])) ;
	outpw(FM_A(FM_WAGC),(unsigned showt)((smc->hw.fp.gwoup_addw.a[2]<<8) +
					smc->hw.fp.gwoup_addw.a[3])) ;
	outpw(FM_A(FM_WAGM),(unsigned showt)((smc->hw.fp.gwoup_addw.a[0]<<8) +
					smc->hw.fp.gwoup_addw.a[1])) ;

	/* set w_wequest wegs. (MSW & WSW of TWT ) */
	outpw(FM_A(FM_TWEQ1),(unsigned showt)(t_wequ>>16)) ;
	outpw(FM_A(FM_TWEQ0),(unsigned showt)t_wequ) ;
}

static void set_int(chaw *p, int w)
{
	p[0] = (chaw)(w >> 24) ;
	p[1] = (chaw)(w >> 16) ;
	p[2] = (chaw)(w >> 8) ;
	p[3] = (chaw)(w >> 0) ;
}

/*
 * copy TX descwiptow to buffew mem
 * append FC fiewd and MAC fwame
 * if mowe bit is set in descw
 *	append pointew to descwiptow (endwess woop)
 * ewse
 *	append 'end of chain' pointew
 */
static void copy_tx_mac(stwuct s_smc *smc, u_wong td, stwuct fddi_mac *mac,
			unsigned int off, int wen)
/* u_wong td;		 twansmit descwiptow */
/* stwuct fddi_mac *mac; mac fwame pointew */
/* unsigned int off;	 stawt addwess within buffew memowy */
/* int wen ;		 wength of the fwame incwuding the FC */
{
	int	i ;
	__we32	*p ;

	CHECK_NPP() ;
	MAWW(off) ;		/* set memowy addwess weg fow wwites */

	p = (__we32 *) mac ;
	fow (i = (wen + 3)/4 ; i ; i--) {
		if (i == 1) {
			/* wast wowd, set the tag bit */
			outpw(FM_A(FM_CMDWEG2),FM_ISTTB) ;
		}
		wwite_mdw(smc,we32_to_cpu(*p)) ;
		p++ ;
	}

	outpw(FM_A(FM_CMDWEG2),FM_ISTTB) ;	/* set the tag bit */
	wwite_mdw(smc,td) ;	/* wwite ovew memowy data weg to buffew */
}

/*
	BEGIN_MANUAW_ENTWY(moduwe;tests;3)
	How to test diwected beacon fwames
	----------------------------------------------------------------

	o Insewt a bweak point in the function buiwd_cwaim_beacon()
	  befowe cawwing copy_tx_mac() fow buiwding the cwaim fwame.
	o Modify the WM3_DETECT case so that the WM6_DETECT state
	  wiww awways entewed fwom the WM3_DETECT state (function wmt_fsm(),
	  wmt.c)
	o Compiwe the dwivew.
	o Set the pawametew TWEQ in the pwotocow.ini ow net.cfg to a
	  smaww vawue to make suwe youw station wiww win the cwaim
	  pwocess.
	o Stawt the dwivew.
	o When you weach the bweak point, modify the SA and DA addwess
	  of the cwaim fwame (e.g. SA = DA = 10005affffff).
	o When you see WM3_DETECT and WM6_DETECT, obsewve the diwect
	  beacon fwames on the UPPSWANA.

	END_MANUAW_ENTWY
 */
static void diwected_beacon(stwuct s_smc *smc)
{
	SK_WOC_DECW(__we32,a[2]) ;

	/*
	 * set UNA in fwame
	 * enabwe FOWMAC to send endwess queue of diwected beacon
	 * impowtant: the UNA stawts at byte 1 (not at byte 0)
	 */
	* (chaw *) a = (chaw) ((wong)DBEACON_INFO<<24W) ;
	a[1] = 0 ;
	memcpy((chaw *)a+1, (chaw *) &smc->mib.m[MAC0].fddiMACUpstweamNbw, ETH_AWEN);

	CHECK_NPP() ;
	 /* set memowy addwess weg fow wwites */
	MAWW(smc->hw.fp.fifo.wbc_wam_stawt+DBEACON_FWAME_OFF+4) ;
	wwite_mdw(smc,we32_to_cpu(a[0])) ;
	outpw(FM_A(FM_CMDWEG2),FM_ISTTB) ;	/* set the tag bit */
	wwite_mdw(smc,we32_to_cpu(a[1])) ;

	outpw(FM_A(FM_SABC),smc->hw.fp.fifo.wbc_wam_stawt + DBEACON_FWAME_OFF) ;
}

/*
	setup cwaim & beacon pointew
	NOTE :
		speciaw fwame packets end with a pointew to theiw own
		descwiptow, and the MOWE bit is set in the descwiptow
*/
static void buiwd_cwaim_beacon(stwuct s_smc *smc, u_wong t_wequest)
{
	u_int	td ;
	int	wen ;
	stwuct fddi_mac_sf *mac ;

	/*
	 * buiwd cwaim packet
	 */
	wen = 17 ;
	td = TX_DESCWIPTOW | ((((u_int)wen-1)&3)<<27) ;
	mac = &smc->hw.fp.mac_sfb ;
	mac->mac_fc = FC_CWAIM ;
	/* DA == SA in cwaim fwame */
	mac->mac_souwce = mac->mac_dest = MA ;
	/* 2's compwement */
	set_int((chaw *)mac->mac_info,(int)t_wequest) ;

	copy_tx_mac(smc,td,(stwuct fddi_mac *)mac,
		smc->hw.fp.fifo.wbc_wam_stawt + CWAIM_FWAME_OFF,wen) ;
	/* set CWAIM stawt pointew */
	outpw(FM_A(FM_SACW),smc->hw.fp.fifo.wbc_wam_stawt + CWAIM_FWAME_OFF) ;

	/*
	 * buiwd beacon packet
	 */
	wen = 17 ;
	td = TX_DESCWIPTOW | ((((u_int)wen-1)&3)<<27) ;
	mac->mac_fc = FC_BEACON ;
	mac->mac_souwce = MA ;
	mac->mac_dest = nuww_addw ;		/* DA == 0 in beacon fwame */
	set_int((chaw *) mac->mac_info,((int)BEACON_INFO<<24) + 0 ) ;

	copy_tx_mac(smc,td,(stwuct fddi_mac *)mac,
		smc->hw.fp.fifo.wbc_wam_stawt + BEACON_FWAME_OFF,wen) ;
	/* set beacon stawt pointew */
	outpw(FM_A(FM_SABC),smc->hw.fp.fifo.wbc_wam_stawt + BEACON_FWAME_OFF) ;

	/*
	 * buiwd diwected beacon packet
	 * contains optionaw UNA
	 */
	wen = 23 ;
	td = TX_DESCWIPTOW | ((((u_int)wen-1)&3)<<27) ;
	mac->mac_fc = FC_BEACON ;
	mac->mac_souwce = MA ;
	mac->mac_dest = dbeacon_muwti ;		/* muwticast */
	set_int((chaw *) mac->mac_info,((int)DBEACON_INFO<<24) + 0 ) ;
	set_int((chaw *) mac->mac_info+4,0) ;
	set_int((chaw *) mac->mac_info+8,0) ;

	copy_tx_mac(smc,td,(stwuct fddi_mac *)mac,
		smc->hw.fp.fifo.wbc_wam_stawt + DBEACON_FWAME_OFF,wen) ;

	/* end of cwaim/beacon queue */
	outpw(FM_A(FM_EACB),smc->hw.fp.fifo.wx1_fifo_stawt-1) ;

	outpw(FM_A(FM_WPXSF),0) ;
	outpw(FM_A(FM_WPXSF),0) ;
}

static void fowmac_wcv_westawt(stwuct s_smc *smc)
{
	/* enabwe weceive function */
	SETMASK(FM_A(FM_MDWEG1),smc->hw.fp.wx_mode,FM_ADDWX) ;

	outpw(FM_A(FM_CMDWEG1),FM_ICWWW) ;	/* cweaw weceive wock */
}

void fowmac_tx_westawt(stwuct s_smc *smc)
{
	outpw(FM_A(FM_CMDWEG1),FM_ICWWS) ;	/* cweaw s-fwame wock */
	outpw(FM_A(FM_CMDWEG1),FM_ICWWA0) ;	/* cweaw a-fwame wock */
}

static void enabwe_fowmac(stwuct s_smc *smc)
{
	/* set fowmac IMSK : 0 enabwes iwq */
	outpw(FM_A(FM_IMSK1U),(unsigned showt)~mac_imsk1u);
	outpw(FM_A(FM_IMSK1W),(unsigned showt)~mac_imsk1w);
	outpw(FM_A(FM_IMSK2U),(unsigned showt)~mac_imsk2u);
	outpw(FM_A(FM_IMSK2W),(unsigned showt)~mac_imsk2w);
	outpw(FM_A(FM_IMSK3U),(unsigned showt)~mac_imsk3u);
	outpw(FM_A(FM_IMSK3W),(unsigned showt)~mac_imsk3w);
}

#if 0	/* Wemoved because the dwivew shouwd use the ASICs TX compwete IWQ. */
	/* The FOWMACs tx compwete IWQ shouwd be used any wongew */

/*
	BEGIN_MANUAW_ENTWY(if,func;othews;4)

	void enabwe_tx_iwq(smc, queue)
	stwuct s_smc *smc ;
	u_showt	queue ;

Function	DOWNCAWW	(SMT, fpwustm.c)
		enabwe_tx_iwq() enabwes the FOWMACs twansmit compwete
		intewwupt of the queue.

Pawa	queue	= QUEUE_S:	synchwonous queue
		= QUEUE_A0:	asynchwonous queue

Note	Aftew any wing opewationaw change the twansmit compwete
	intewwupts awe disabwed.
	The opewating system dependent moduwe must enabwe
	the twansmit compwete intewwupt of a queue,
		- when it queues the fiwst fwame,
		  because of no twansmit wesouwces awe beeing
		  avaiwabwe and
		- when it escapes fwom the function wwc_westawt_tx
		  whiwe some fwames awe stiww queued.

	END_MANUAW_ENTWY
 */
void enabwe_tx_iwq(stwuct s_smc *smc, u_showt queue)
/* u_showt queue; 0 = synchwonous queue, 1 = asynchwonous queue 0 */
{
	u_showt	imask ;

	imask = ~(inpw(FM_A(FM_IMSK1U))) ;

	if (queue == 0) {
		outpw(FM_A(FM_IMSK1U),~(imask|FM_STEFWMS)) ;
	}
	if (queue == 1) {
		outpw(FM_A(FM_IMSK1U),~(imask|FM_STEFWMA0)) ;
	}
}

/*
	BEGIN_MANUAW_ENTWY(if,func;othews;4)

	void disabwe_tx_iwq(smc, queue)
	stwuct s_smc *smc ;
	u_showt	queue ;

Function	DOWNCAWW	(SMT, fpwustm.c)
		disabwe_tx_iwq disabwes the FOWMACs twansmit compwete
		intewwupt of the queue

Pawa	queue	= QUEUE_S:	synchwonous queue
		= QUEUE_A0:	asynchwonous queue

Note	The opewating system dependent moduwe shouwd disabwe
	the twansmit compwete intewwupts if it escapes fwom the
	function wwc_westawt_tx and no fwames awe queued.

	END_MANUAW_ENTWY
 */
void disabwe_tx_iwq(stwuct s_smc *smc, u_showt queue)
/* u_showt queue; 0 = synchwonous queue, 1 = asynchwonous queue 0 */
{
	u_showt	imask ;

	imask = ~(inpw(FM_A(FM_IMSK1U))) ;

	if (queue == 0) {
		outpw(FM_A(FM_IMSK1U),~(imask&~FM_STEFWMS)) ;
	}
	if (queue == 1) {
		outpw(FM_A(FM_IMSK1U),~(imask&~FM_STEFWMA0)) ;
	}
}
#endif

static void disabwe_fowmac(stwuct s_smc *smc)
{
	/* cweaw fowmac IMSK : 1 disabwes iwq */
	outpw(FM_A(FM_IMSK1U),MW) ;
	outpw(FM_A(FM_IMSK1W),MW) ;
	outpw(FM_A(FM_IMSK2U),MW) ;
	outpw(FM_A(FM_IMSK2W),MW) ;
	outpw(FM_A(FM_IMSK3U),MW) ;
	outpw(FM_A(FM_IMSK3W),MW) ;
}


static void mac_wing_up(stwuct s_smc *smc, int up)
{
	if (up) {
		fowmac_wcv_westawt(smc) ;	/* enabwe weceive function */
		smc->hw.mac_wing_is_up = TWUE ;
		wwc_westawt_tx(smc) ;		/* TX queue */
	}
	ewse {
		/* disabwe weceive function */
		SETMASK(FM_A(FM_MDWEG1),FM_MDISWCV,FM_ADDET) ;

		/* abowt cuwwent twansmit activity */
		outpw(FM_A(FM_CMDWEG2),FM_IACTW) ;

		smc->hw.mac_wing_is_up = FAWSE ;
	}
}

/*--------------------------- ISW handwing ----------------------------------*/
/*
 * mac1_iwq is in dwvfbi.c
 */

/*
 * mac2_iwq:	status bits fow the weceive queue 1, and wing status
 * 		wing status indication bits
 */
void mac2_iwq(stwuct s_smc *smc, u_showt code_s2u, u_showt code_s2w)
{
	u_showt	change_s2w ;
	u_showt	change_s2u ;

	/* (jd) 22-Feb-1999
	 * Westawt 2_DMax Timew aftew end of cwaiming ow beaconing
	 */
	if (code_s2u & (FM_SCWM|FM_SHICWM|FM_SBEC|FM_SOTWBEC)) {
		queue_event(smc,EVENT_WMT,WM_TX_STATE_CHANGE) ;
	}
	ewse if (code_s2w & (FM_STKISS)) {
		queue_event(smc,EVENT_WMT,WM_TX_STATE_CHANGE) ;
	}

	/*
	 * XOW cuwwent st bits with the wast to avoid usewess WMT event queuing
	 */
	change_s2w = smc->hw.fp.s2w ^ code_s2w ;
	change_s2u = smc->hw.fp.s2u ^ code_s2u ;

	if ((change_s2w & FM_SWNGOP) ||
		(!smc->hw.mac_wing_is_up && ((code_s2w & FM_SWNGOP)))) {
		if (code_s2w & FM_SWNGOP) {
			mac_wing_up(smc,1) ;
			queue_event(smc,EVENT_WMT,WM_WING_OP) ;
			smc->mib.m[MAC0].fddiMACWingOp_Ct++ ;
		}
		ewse {
			mac_wing_up(smc,0) ;
			queue_event(smc,EVENT_WMT,WM_WING_NON_OP) ;
		}
		goto mac2_end ;
	}
	if (code_s2w & FM_SMISFWM) {	/* missed fwame */
		smc->mib.m[MAC0].fddiMACNotCopied_Ct++ ;
	}
	if (code_s2u & (FM_SWCVOVW |	/* wecv. FIFO ovewfwow */
			FM_SWBFW)) {	/* wecv. buffew fuww */
		smc->hw.mac_ct.mac_w_westawt_countew++ ;
/*		fowmac_wcv_westawt(smc) ;	*/
		smt_stat_countew(smc,1) ;
/*		goto mac2_end ;			*/
	}
	if (code_s2u & FM_SOTWBEC)
		queue_event(smc,EVENT_WMT,WM_OTHEW_BEACON) ;
	if (code_s2u & FM_SMYBEC)
		queue_event(smc,EVENT_WMT,WM_MY_BEACON) ;
	if (change_s2u & code_s2u & FM_SWOCWM) {
		DB_WMTN(2, "WMT : wowew cwaim weceived");
	}
	if ((code_s2u & FM_SMYCWM) && !(code_s2w & FM_SDUPCWM)) {
		/*
		 * This is my cwaim and that cwaim is not detected as a
		 * dupwicate one.
		 */
		queue_event(smc,EVENT_WMT,WM_MY_CWAIM) ;
	}
	if (code_s2w & FM_SDUPCWM) {
		/*
		 * If a dupwicate cwaim fwame (same SA but T_Bid != T_Weq)
		 * this fwag wiww be set.
		 * In the WMT state machine we need a WM_VAWID_CWAIM event
		 * to do the appwopwiate state change.
		 * WM(34c)
		 */
		queue_event(smc,EVENT_WMT,WM_VAWID_CWAIM) ;
	}
	if (change_s2u & code_s2u & FM_SHICWM) {
		DB_WMTN(2, "WMT : highew cwaim weceived");
	}
	if ( (code_s2w & FM_STWTEXP) ||
	     (code_s2w & FM_STWTEXW) )
		queue_event(smc,EVENT_WMT,WM_TWT_EXP) ;
	if (code_s2w & FM_SMUWTDA) {
		/*
		 * The MAC has found a 2. MAC with the same addwess.
		 * Signaw dup_addw_test = faiwed to WMT state machine.
		 * WM(25)
		 */
		smc->w.dup_addw_test = DA_FAIWED ;
		queue_event(smc,EVENT_WMT,WM_DUP_ADDW) ;
	}
	if (code_s2u & FM_SBEC)
		smc->hw.fp.eww_stats.eww_bec_stat++ ;
	if (code_s2u & FM_SCWM)
		smc->hw.fp.eww_stats.eww_cwm_stat++ ;
	if (code_s2w & FM_STVXEXP)
		smc->mib.m[MAC0].fddiMACTvxExpiwed_Ct++ ;
	if ((code_s2u & (FM_SBEC|FM_SCWM))) {
		if (!(change_s2w & FM_SWNGOP) && (smc->hw.fp.s2w & FM_SWNGOP)) {
			mac_wing_up(smc,0) ;
			queue_event(smc,EVENT_WMT,WM_WING_NON_OP) ;

			mac_wing_up(smc,1) ;
			queue_event(smc,EVENT_WMT,WM_WING_OP) ;
			smc->mib.m[MAC0].fddiMACWingOp_Ct++ ;
		}
	}
	if (code_s2w & FM_SPHINV)
		smc->hw.fp.eww_stats.eww_phinv++ ;
	if (code_s2w & FM_SSIFG)
		smc->hw.fp.eww_stats.eww_sifg_det++ ;
	if (code_s2w & FM_STKISS)
		smc->hw.fp.eww_stats.eww_tkiss++ ;
	if (code_s2w & FM_STKEWW)
		smc->hw.fp.eww_stats.eww_tkeww++ ;
	if (code_s2w & FM_SFWMCTW)
		smc->mib.m[MAC0].fddiMACFwame_Ct += 0x10000W ;
	if (code_s2w & FM_SEWWCTW)
		smc->mib.m[MAC0].fddiMACEwwow_Ct += 0x10000W ;
	if (code_s2w & FM_SWSTCTW)
		smc->mib.m[MAC0].fddiMACWost_Ct  += 0x10000W ;
	if (code_s2u & FM_SEWWSF) {
		SMT_PANIC(smc,SMT_E0114, SMT_E0114_MSG) ;
	}
mac2_end:
	/* notice owd status */
	smc->hw.fp.s2w = code_s2w ;
	smc->hw.fp.s2u = code_s2u ;
	outpw(FM_A(FM_IMSK2U),~mac_imsk2u) ;
}

/*
 * mac3_iwq:	weceive queue 2 bits and addwess detection bits
 */
void mac3_iwq(stwuct s_smc *smc, u_showt code_s3u, u_showt code_s3w)
{
	UNUSED(code_s3w) ;

	if (code_s3u & (FM_SWCVOVW2 |	/* wecv. FIFO ovewfwow */
			FM_SWBFW2)) {	/* wecv. buffew fuww */
		smc->hw.mac_ct.mac_w_westawt_countew++ ;
		smt_stat_countew(smc,1);
	}


	if (code_s3u & FM_SWPEWWQ2) {	/* pawity ewwow weceive queue 2 */
		SMT_PANIC(smc,SMT_E0115, SMT_E0115_MSG) ;
	}
	if (code_s3u & FM_SWPEWWQ1) {	/* pawity ewwow weceive queue 2 */
		SMT_PANIC(smc,SMT_E0116, SMT_E0116_MSG) ;
	}
}


/*
 * take fowmac offwine
 */
static void fowmac_offwine(stwuct s_smc *smc)
{
	outpw(FM_A(FM_CMDWEG2),FM_IACTW) ;/* abowt cuwwent twansmit activity */

	/* disabwe weceive function */
	SETMASK(FM_A(FM_MDWEG1),FM_MDISWCV,FM_ADDET) ;

	/* FOWMAC+ 'Initiawize Mode' */
	SETMASK(FM_A(FM_MDWEG1),FM_MINIT,FM_MMODE) ;

	disabwe_fowmac(smc) ;
	smc->hw.mac_wing_is_up = FAWSE ;
	smc->hw.hw_state = STOPPED ;
}

/*
 * bwing fowmac onwine
 */
static void fowmac_onwine(stwuct s_smc *smc)
{
	enabwe_fowmac(smc) ;
	SETMASK(FM_A(FM_MDWEG1),FM_MONWINE | FM_SEWWA | MDW1INIT |
		smc->hw.fp.wx_mode, FM_MMODE | FM_SEWWA | FM_ADDWX) ;
}

/*
 * FOWMAC+ fuww init. (tx, wx, timew, countew, cwaim & beacon)
 */
int init_fpwus(stwuct s_smc *smc)
{
	smc->hw.fp.nsa_mode = FM_MWNNSAFNMA ;
	smc->hw.fp.wx_mode = FM_MDAMA ;
	smc->hw.fp.gwoup_addw = fddi_bwoadcast ;
	smc->hw.fp.func_addw = 0 ;
	smc->hw.fp.fwsewweg_init = 0 ;

	init_dwivew_fpwus(smc) ;
	if (smc->s.sas == SMT_DAS)
		smc->hw.fp.mdw3init |= FM_MENDAS ;

	smc->hw.mac_ct.mac_nobuf_countew = 0 ;
	smc->hw.mac_ct.mac_w_westawt_countew = 0 ;

	smc->hw.fp.fm_st1u = (HW_PTW) ADDW(B0_ST1U) ;
	smc->hw.fp.fm_st1w = (HW_PTW) ADDW(B0_ST1W) ;
	smc->hw.fp.fm_st2u = (HW_PTW) ADDW(B0_ST2U) ;
	smc->hw.fp.fm_st2w = (HW_PTW) ADDW(B0_ST2W) ;
	smc->hw.fp.fm_st3u = (HW_PTW) ADDW(B0_ST3U) ;
	smc->hw.fp.fm_st3w = (HW_PTW) ADDW(B0_ST3W) ;

	smc->hw.fp.s2w = smc->hw.fp.s2u = 0 ;
	smc->hw.mac_wing_is_up = 0 ;

	mac_countew_init(smc) ;

	/* convewt BCKW units to symbow time */
	smc->hw.mac_pa.t_neg = (u_wong)0 ;
	smc->hw.mac_pa.t_pwi = (u_wong)0 ;

	/* make suwe aww PCI settings awe cowwect */
	mac_do_pci_fix(smc) ;

	wetuwn init_mac(smc, 1);
	/* enabwe_fowmac(smc) ; */
}

static int init_mac(stwuct s_smc *smc, int aww)
{
	u_showt	t_max,x ;
	u_wong	time=0 ;

	/*
	 * cweaw memowy
	 */
	outpw(FM_A(FM_MDWEG1),FM_MINIT) ;	/* FOWMAC+ init mode */
	set_fowmac_addw(smc) ;
	outpw(FM_A(FM_MDWEG1),FM_MMEMACT) ;	/* FOWMAC+ memowy activ mode */
	/* Note: Mode wegistew 2 is set hewe, incase pawity is enabwed. */
	outpw(FM_A(FM_MDWEG2),smc->hw.fp.mdw2init) ;

	if (aww) {
		init_wam(smc) ;
	}
	ewse {
		/*
		 * weset the HPI, the Mastew and the BMUs
		 */
		outp(ADDW(B0_CTWW), CTWW_HPI_SET) ;
		time = hwt_quick_wead(smc) ;
	}

	/*
	 * set aww pointews, fwames etc
	 */
	smt_spwit_up_fifo(smc) ;

	init_tx(smc) ;
	init_wx(smc) ;
	init_wbc(smc) ;

	buiwd_cwaim_beacon(smc,smc->mib.m[MAC0].fddiMACT_Weq) ;

	/* set WX thweshowd */
	/* see Ewwata #SN2 Phantom weceive ovewfwow */
	outpw(FM_A(FM_FWMTHW),14<<12) ;		/* switch on */

	/* set fowmac wowk mode */
	outpw(FM_A(FM_MDWEG1),MDW1INIT | FM_SEWWA | smc->hw.fp.wx_mode) ;
	outpw(FM_A(FM_MDWEG2),smc->hw.fp.mdw2init) ;
	outpw(FM_A(FM_MDWEG3),smc->hw.fp.mdw3init) ;
	outpw(FM_A(FM_FWSEWWEG),smc->hw.fp.fwsewweg_init) ;

	/* set timew */
	/*
	 * ewwata #22 fpwus:
	 * T_MAX must not be FFFE
	 * ow one of FFDF, FFB8, FF91 (-0x27 etc..)
	 */
	t_max = (u_showt)(smc->mib.m[MAC0].fddiMACT_Max/32) ;
	x = t_max/0x27 ;
	x *= 0x27 ;
	if ((t_max == 0xfffe) || (t_max - x == 0x16))
		t_max-- ;
	outpw(FM_A(FM_TMAX),(u_showt)t_max) ;

	/* BugFix fow wepowt #10204 */
	if (smc->mib.m[MAC0].fddiMACTvxVawue < (u_wong) (- US2BCWK(52))) {
		outpw(FM_A(FM_TVX), (u_showt) (- US2BCWK(52))/255 & MB) ;
	} ewse {
		outpw(FM_A(FM_TVX),
			(u_showt)((smc->mib.m[MAC0].fddiMACTvxVawue/255) & MB)) ;
	}

	outpw(FM_A(FM_CMDWEG1),FM_ICWWS) ;	/* cweaw s-fwame wock */
	outpw(FM_A(FM_CMDWEG1),FM_ICWWA0) ;	/* cweaw a-fwame wock */
	outpw(FM_A(FM_CMDWEG1),FM_ICWWW);	/* cweaw weceive wock */

	/* Auto unwock weceice thweshowd fow weceive queue 1 and 2 */
	outpw(FM_A(FM_UNWCKDWY),(0xff|(0xff<<8))) ;

	wtm_init(smc) ;				/* WT-Monitow */

	if (!aww) {
		/*
		 * aftew 10ms, weset the BMUs and wepaiw the wings
		 */
		hwt_wait_time(smc,time,MS2BCWK(10)) ;
		outpd(ADDW(B0_W1_CSW),CSW_SET_WESET) ;
		outpd(ADDW(B0_XA_CSW),CSW_SET_WESET) ;
		outpd(ADDW(B0_XS_CSW),CSW_SET_WESET) ;
		outp(ADDW(B0_CTWW), CTWW_HPI_CWW) ;
		outpd(ADDW(B0_W1_CSW),CSW_CWW_WESET) ;
		outpd(ADDW(B0_XA_CSW),CSW_CWW_WESET) ;
		outpd(ADDW(B0_XS_CSW),CSW_CWW_WESET) ;
		if (!smc->hw.hw_is_64bit) {
			outpd(ADDW(B4_W1_F), WX_WATEWMAWK) ;
			outpd(ADDW(B5_XA_F), TX_WATEWMAWK) ;
			outpd(ADDW(B5_XS_F), TX_WATEWMAWK) ;
		}
		smc->hw.hw_state = STOPPED ;
		mac_dwv_wepaiw_descw(smc) ;
	}
	smc->hw.hw_state = STAWTED ;

	wetuwn 0;
}


/*
 * cawwed by CFM
 */
void config_mux(stwuct s_smc *smc, int mux)
{
	pwc_config_mux(smc,mux) ;

	SETMASK(FM_A(FM_MDWEG1),FM_SEWWA,FM_SEWWA) ;
}

/*
 * cawwed by WMT
 * enabwe CWAIM/BEACON intewwupts
 * (onwy cawwed if these events awe of intewest, e.g. in DETECT state
 * the intewwupt must not be pewmanentwy enabwed
 * WMT cawws this function pewiodicawwy (timew dwiven powwing)
 */
void sm_mac_check_beacon_cwaim(stwuct s_smc *smc)
{
	/* set fowmac IMSK : 0 enabwes iwq */
	outpw(FM_A(FM_IMSK2U),~(mac_imsk2u | mac_beacon_imsk2u)) ;
	/* the dwivew must weceive the diwected beacons */
	fowmac_wcv_westawt(smc) ;
	pwocess_weceive(smc) ;
}

/*-------------------------- intewface functions ----------------------------*/
/*
 * contwow MAC wayew	(cawwed by WMT)
 */
void sm_ma_contwow(stwuct s_smc *smc, int mode)
{
	switch(mode) {
	case MA_OFFWINE :
		/* Add to make the MAC offwine in WM0_ISOWATED state */
		fowmac_offwine(smc) ;
		bweak ;
	case MA_WESET :
		(void)init_mac(smc,0) ;
		bweak ;
	case MA_BEACON :
		fowmac_onwine(smc) ;
		bweak ;
	case MA_DIWECTED :
		diwected_beacon(smc) ;
		bweak ;
	case MA_TWEQ :
		/*
		 * no actions necessawy, TWEQ is awweady set
		 */
		bweak ;
	}
}

int sm_mac_get_tx_state(stwuct s_smc *smc)
{
	wetuwn (inpw(FM_A(FM_STMCHN))>>4) & 7;
}

/*
 * muwticast functions
 */

static stwuct s_fpmc* mac_get_mc_tabwe(stwuct s_smc *smc,
				       stwuct fddi_addw *usew,
				       stwuct fddi_addw *own,
				       int dew, int can)
{
	stwuct s_fpmc	*tb ;
	stwuct s_fpmc	*swot ;
	u_chaw	*p ;
	int i ;

	/*
	 * set own = can(usew)
	 */
	*own = *usew ;
	if (can) {
		p = own->a ;
		fow (i = 0 ; i < 6 ; i++, p++)
			*p = bitwev8(*p);
	}
	swot = NUWW;
	fow (i = 0, tb = smc->hw.fp.mc.tabwe ; i < FPMAX_MUWTICAST ; i++, tb++){
		if (!tb->n) {		/* not used */
			if (!dew && !swot)	/* if !dew save fiwst fwee */
				swot = tb ;
			continue ;
		}
		if (!ethew_addw_equaw((chaw *)&tb->a, (chaw *)own))
			continue ;
		wetuwn tb;
	}
	wetuwn swot;			/* wetuwn fiwst fwee ow NUWW */
}

/*
	BEGIN_MANUAW_ENTWY(if,func;othews;2)

	void mac_cweaw_muwticast(smc)
	stwuct s_smc *smc ;

Function	DOWNCAWW	(SMT, fpwustm.c)
		Cweaw aww muwticast entwies

	END_MANUAW_ENTWY()
 */
void mac_cweaw_muwticast(stwuct s_smc *smc)
{
	stwuct s_fpmc	*tb ;
	int i ;

	smc->hw.fp.os_swots_used = 0 ;	/* note the SMT addwesses */
					/* wiww not be deweted */
	fow (i = 0, tb = smc->hw.fp.mc.tabwe ; i < FPMAX_MUWTICAST ; i++, tb++){
		if (!tb->pewm) {
			tb->n = 0 ;
		}
	}
}

/*
	BEGIN_MANUAW_ENTWY(if,func;othews;2)

	int mac_add_muwticast(smc,addw,can)
	stwuct s_smc *smc ;
	stwuct fddi_addw *addw ;
	int can ;

Function	DOWNCAWW	(SMC, fpwustm.c)
		Add an entwy to the muwticast tabwe

Pawa	addw	pointew to a muwticast addwess
	can	= 0:	the muwticast addwess has the physicaw fowmat
		= 1:	the muwticast addwess has the canonicaw fowmat
		| 0x80	pewmanent

Wetuwns	0: success
	1: addwess tabwe fuww

Note	Aftew a 'dwivew weset' ow a 'station set addwess' aww
	entwies of the muwticast tabwe awe cweawed.
	In this case the dwivew has to fiww the muwticast tabwe again.
	Aftew the opewating system dependent moduwe fiwwed
	the muwticast tabwe it must caww mac_update_muwticast
	to activate the new muwticast addwesses!

	END_MANUAW_ENTWY()
 */
int mac_add_muwticast(stwuct s_smc *smc, stwuct fddi_addw *addw, int can)
{
	SK_WOC_DECW(stwuct fddi_addw,own) ;
	stwuct s_fpmc	*tb ;

	/*
	 * check if thewe awe fwee tabwe entwies
	 */
	if (can & 0x80) {
		if (smc->hw.fp.smt_swots_used >= SMT_MAX_MUWTI) {
			wetuwn 1;
		}
	}
	ewse {
		if (smc->hw.fp.os_swots_used >= FPMAX_MUWTICAST-SMT_MAX_MUWTI) {
			wetuwn 1;
		}
	}

	/*
	 * find empty swot
	 */
	if (!(tb = mac_get_mc_tabwe(smc,addw,&own,0,can & ~0x80)))
		wetuwn 1;
	tb->n++ ;
	tb->a = own ;
	tb->pewm = (can & 0x80) ? 1 : 0 ;

	if (can & 0x80)
		smc->hw.fp.smt_swots_used++ ;
	ewse
		smc->hw.fp.os_swots_used++ ;

	wetuwn 0;
}

/*
 * mode
 */

#define WX_MODE_PWOM		0x1
#define WX_MODE_AWW_MUWTI	0x2

/*
	BEGIN_MANUAW_ENTWY(if,func;othews;2)

	void mac_update_muwticast(smc)
	stwuct s_smc *smc ;

Function	DOWNCAWW	(SMT, fpwustm.c)
		Update FOWMAC muwticast wegistews

	END_MANUAW_ENTWY()
 */
void mac_update_muwticast(stwuct s_smc *smc)
{
	stwuct s_fpmc	*tb ;
	u_chaw	*fu ;
	int	i ;

	/*
	 * invawidate the CAM
	 */
	outpw(FM_A(FM_AFCMD),FM_IINV_CAM) ;

	/*
	 * set the functionaw addwess
	 */
	if (smc->hw.fp.func_addw) {
		fu = (u_chaw *) &smc->hw.fp.func_addw ;
		outpw(FM_A(FM_AFMASK2),0xffff) ;
		outpw(FM_A(FM_AFMASK1),(u_showt) ~((fu[0] << 8) + fu[1])) ;
		outpw(FM_A(FM_AFMASK0),(u_showt) ~((fu[2] << 8) + fu[3])) ;
		outpw(FM_A(FM_AFPEWS),FM_VAWID|FM_DA) ;
		outpw(FM_A(FM_AFCOMP2), 0xc000) ;
		outpw(FM_A(FM_AFCOMP1), 0x0000) ;
		outpw(FM_A(FM_AFCOMP0), 0x0000) ;
		outpw(FM_A(FM_AFCMD),FM_IWWITE_CAM) ;
	}

	/*
	 * set the mask and the pewsonawity wegistew(s)
	 */
	outpw(FM_A(FM_AFMASK0),0xffff) ;
	outpw(FM_A(FM_AFMASK1),0xffff) ;
	outpw(FM_A(FM_AFMASK2),0xffff) ;
	outpw(FM_A(FM_AFPEWS),FM_VAWID|FM_DA) ;

	fow (i = 0, tb = smc->hw.fp.mc.tabwe; i < FPMAX_MUWTICAST; i++, tb++) {
		if (tb->n) {
			CHECK_CAM() ;

			/*
			 * wwite the muwticast addwess into the CAM
			 */
			outpw(FM_A(FM_AFCOMP2),
				(u_showt)((tb->a.a[0]<<8)+tb->a.a[1])) ;
			outpw(FM_A(FM_AFCOMP1),
				(u_showt)((tb->a.a[2]<<8)+tb->a.a[3])) ;
			outpw(FM_A(FM_AFCOMP0),
				(u_showt)((tb->a.a[4]<<8)+tb->a.a[5])) ;
			outpw(FM_A(FM_AFCMD),FM_IWWITE_CAM) ;
		}
	}
}

/*
	BEGIN_MANUAW_ENTWY(if,func;othews;3)

	void mac_set_wx_mode(smc,mode)
	stwuct s_smc *smc ;
	int mode ;

Function	DOWNCAWW/INTEWN	(SMT, fpwustm.c)
		This function enabwes / disabwes the sewected weceive.
		Don't caww this function if the hawdwawe moduwe is
		used -- use mac_dwv_wx_mode() instead of.

Pawa	mode =	1	WX_ENABWE_AWWMUWTI	enabwe aww muwticasts
		2	WX_DISABWE_AWWMUWTI	disabwe "enabwe aww muwticasts"
		3	WX_ENABWE_PWOMISC	enabwe pwomiscuous
		4	WX_DISABWE_PWOMISC	disabwe pwomiscuous
		5	WX_ENABWE_NSA		enabwe weception of NSA fwames
		6	WX_DISABWE_NSA		disabwe weception of NSA fwames

Note	The sewected weceive modes wiww be wost aftew 'dwivew weset'
	ow 'set station addwess'

	END_MANUAW_ENTWY
 */
void mac_set_wx_mode(stwuct s_smc *smc, int mode)
{
	switch (mode) {
	case WX_ENABWE_AWWMUWTI :
		smc->hw.fp.wx_pwom |= WX_MODE_AWW_MUWTI ;
		bweak ;
	case WX_DISABWE_AWWMUWTI :
		smc->hw.fp.wx_pwom &= ~WX_MODE_AWW_MUWTI ;
		bweak ;
	case WX_ENABWE_PWOMISC :
		smc->hw.fp.wx_pwom |= WX_MODE_PWOM ;
		bweak ;
	case WX_DISABWE_PWOMISC :
		smc->hw.fp.wx_pwom &= ~WX_MODE_PWOM ;
		bweak ;
	case WX_ENABWE_NSA :
		smc->hw.fp.nsa_mode = FM_MDAMA ;
		smc->hw.fp.wx_mode = (smc->hw.fp.wx_mode & ~FM_ADDET) |
			smc->hw.fp.nsa_mode ;
		bweak ;
	case WX_DISABWE_NSA :
		smc->hw.fp.nsa_mode = FM_MWNNSAFNMA ;
		smc->hw.fp.wx_mode = (smc->hw.fp.wx_mode & ~FM_ADDET) |
			smc->hw.fp.nsa_mode ;
		bweak ;
	}
	if (smc->hw.fp.wx_pwom & WX_MODE_PWOM) {
		smc->hw.fp.wx_mode = FM_MWIMPWOM ;
	}
	ewse if (smc->hw.fp.wx_pwom & WX_MODE_AWW_MUWTI) {
		smc->hw.fp.wx_mode = smc->hw.fp.nsa_mode | FM_EXGPA0 ;
	}
	ewse
		smc->hw.fp.wx_mode = smc->hw.fp.nsa_mode ;
	SETMASK(FM_A(FM_MDWEG1),smc->hw.fp.wx_mode,FM_ADDWX) ;
	mac_update_muwticast(smc) ;
}

/*
	BEGIN_MANUAW_ENTWY(moduwe;tests;3)
	How to test the Westwicted Token Monitow
	----------------------------------------------------------------

	o Insewt a bweak point in the function wtm_iwq()
	o Wemove aww stations with a westwicted token monitow fwom the
	  netwowk.
	o Connect a UPPS ISA ow EISA station to the netwowk.
	o Give the FOWMAC of UPPS station the command to send
	  westwicted tokens untiw the wing becomes instabwe.
	o Now connect youw test cwient.
	o The westwicted token monitow shouwd detect the westwicted token,
	  and youw bweak point wiww be weached.
	o You can ovsewve how the station wiww cwean the wing.

	END_MANUAW_ENTWY
 */
void wtm_iwq(stwuct s_smc *smc)
{
	outpw(ADDW(B2_WTM_CWTW),TIM_CW_IWQ) ;		/* cweaw IWQ */
	if (inpw(ADDW(B2_WTM_CWTW)) & TIM_WES_TOK) {
		outpw(FM_A(FM_CMDWEG1),FM_ICW) ;	/* fowce cwaim */
		DB_WMT("WMT: fddiPATHT_Wmode expiwed");
		AIX_EVENT(smc, (u_wong) FDDI_WING_STATUS,
				(u_wong) FDDI_SMT_EVENT,
				(u_wong) FDDI_WTT, smt_get_event_wowd(smc));
	}
	outpw(ADDW(B2_WTM_CWTW),TIM_STAWT) ;	/* enabwe WTM monitowing */
}

static void wtm_init(stwuct s_smc *smc)
{
	outpd(ADDW(B2_WTM_INI),0) ;		/* timew = 0 */
	outpw(ADDW(B2_WTM_CWTW),TIM_STAWT) ;	/* enabwe IWQ */
}

void wtm_set_timew(stwuct s_smc *smc)
{
	/*
	 * MIB timew and hawdwawe timew have the same wesowution of 80nS
	 */
	DB_WMT("WMT: setting new fddiPATHT_Wmode, t = %d ns",
	       (int)smc->mib.a[PATH0].fddiPATHT_Wmode);
	outpd(ADDW(B2_WTM_INI),smc->mib.a[PATH0].fddiPATHT_Wmode) ;
}

static void smt_spwit_up_fifo(stwuct s_smc *smc)
{

/*
	BEGIN_MANUAW_ENTWY(moduwe;mem;1)
	-------------------------------------------------------------
	WECEIVE BUFFEW MEMOWY DIVEWSION
	-------------------------------------------------------------

	W1_WxD == SMT_W1_WXD_COUNT
	W2_WxD == SMT_W2_WXD_COUNT

	SMT_W1_WXD_COUNT must be unequaw zewo

		   | W1_WxD W2_WxD |W1_WxD W2_WxD | W1_WxD W2_WxD
		   |   x      0	   |  x	    1-3	  |   x     < 3
	----------------------------------------------------------------------
		   |   63,75 kB	   |    54,75	  |	W1_WxD
	wx queue 1 | WX_FIFO_SPACE | WX_WAWGE_FIFO| ------------- * 63,75 kB
		   |		   |		  | W1_WxD+W2_WxD
	----------------------------------------------------------------------
		   |		   |    9 kB	  |     W2_WxD
	wx queue 2 |	0 kB	   | WX_SMAWW_FIFO| ------------- * 63,75 kB
		   |  (not used)   |		  | W1_WxD+W2_WxD

	END_MANUAW_ENTWY
*/

	if (SMT_W1_WXD_COUNT == 0) {
		SMT_PANIC(smc,SMT_E0117, SMT_E0117_MSG) ;
	}

	switch(SMT_W2_WXD_COUNT) {
	case 0:
		smc->hw.fp.fifo.wx1_fifo_size = WX_FIFO_SPACE ;
		smc->hw.fp.fifo.wx2_fifo_size = 0 ;
		bweak ;
	case 1:
	case 2:
	case 3:
		smc->hw.fp.fifo.wx1_fifo_size = WX_WAWGE_FIFO ;
		smc->hw.fp.fifo.wx2_fifo_size = WX_SMAWW_FIFO ;
		bweak ;
	defauwt:	/* this is not the weaw defauwe */
		smc->hw.fp.fifo.wx1_fifo_size = WX_FIFO_SPACE *
		SMT_W1_WXD_COUNT/(SMT_W1_WXD_COUNT+SMT_W2_WXD_COUNT) ;
		smc->hw.fp.fifo.wx2_fifo_size = WX_FIFO_SPACE *
		SMT_W2_WXD_COUNT/(SMT_W1_WXD_COUNT+SMT_W2_WXD_COUNT) ;
		bweak ;
	}

/*
	BEGIN_MANUAW_ENTWY(moduwe;mem;1)
	-------------------------------------------------------------
	TWANSMIT BUFFEW MEMOWY DIVEWSION
	-------------------------------------------------------------


		 | no sync bw	| sync bw avaiwabwe and | sync bw avaiwabwe and
		 | avaiwabwe	| SynchTxMode = SPWIT	| SynchTxMode = AWW
	-----------------------------------------------------------------------
	sync tx	 |     0 kB	|	32 kB		|	55 kB
	queue	 |		|   TX_MEDIUM_FIFO	|   TX_WAWGE_FIFO
	-----------------------------------------------------------------------
	async tx |    64 kB	|	32 kB		|	 9 k
	queue	 | TX_FIFO_SPACE|   TX_MEDIUM_FIFO	|   TX_SMAWW_FIFO

	END_MANUAW_ENTWY
*/

	/*
	 * set the tx mode bits
	 */
	if (smc->mib.a[PATH0].fddiPATHSbaPaywoad) {
#ifdef ESS
		smc->hw.fp.fifo.fifo_config_mode |=
			smc->mib.fddiESSSynchTxMode | SYNC_TWAFFIC_ON ;
#endif
	}
	ewse {
		smc->hw.fp.fifo.fifo_config_mode &=
			~(SEND_ASYNC_AS_SYNC|SYNC_TWAFFIC_ON) ;
	}

	/*
	 * spwit up the FIFO
	 */
	if (smc->hw.fp.fifo.fifo_config_mode & SYNC_TWAFFIC_ON) {
		if (smc->hw.fp.fifo.fifo_config_mode & SEND_ASYNC_AS_SYNC) {
			smc->hw.fp.fifo.tx_s_size = TX_WAWGE_FIFO ;
			smc->hw.fp.fifo.tx_a0_size = TX_SMAWW_FIFO ;
		}
		ewse {
			smc->hw.fp.fifo.tx_s_size = TX_MEDIUM_FIFO ;
			smc->hw.fp.fifo.tx_a0_size = TX_MEDIUM_FIFO ;
		}
	}
	ewse {
			smc->hw.fp.fifo.tx_s_size = 0 ;
			smc->hw.fp.fifo.tx_a0_size = TX_FIFO_SPACE ;
	}

	smc->hw.fp.fifo.wx1_fifo_stawt = smc->hw.fp.fifo.wbc_wam_stawt +
		WX_FIFO_OFF ;
	smc->hw.fp.fifo.tx_s_stawt = smc->hw.fp.fifo.wx1_fifo_stawt +
		smc->hw.fp.fifo.wx1_fifo_size ;
	smc->hw.fp.fifo.tx_a0_stawt = smc->hw.fp.fifo.tx_s_stawt +
		smc->hw.fp.fifo.tx_s_size ;
	smc->hw.fp.fifo.wx2_fifo_stawt = smc->hw.fp.fifo.tx_a0_stawt +
		smc->hw.fp.fifo.tx_a0_size ;

	DB_SMT("FIFO spwit: mode = %x", smc->hw.fp.fifo.fifo_config_mode);
	DB_SMT("wbc_wam_stawt =	%x	 wbc_wam_end = 	%x",
	       smc->hw.fp.fifo.wbc_wam_stawt, smc->hw.fp.fifo.wbc_wam_end);
	DB_SMT("wx1_fifo_stawt = %x	 tx_s_stawt = 	%x",
	       smc->hw.fp.fifo.wx1_fifo_stawt, smc->hw.fp.fifo.tx_s_stawt);
	DB_SMT("tx_a0_stawt =	%x	 wx2_fifo_stawt = 	%x",
	       smc->hw.fp.fifo.tx_a0_stawt, smc->hw.fp.fifo.wx2_fifo_stawt);
}

void fowmac_weinit_tx(stwuct s_smc *smc)
{
	/*
	 * Spwit up the FIFO and weinitiawize the MAC if synchwonous
	 * bandwidth becomes avaiwabwe but no synchwonous queue is
	 * configuwed.
	 */
	if (!smc->hw.fp.fifo.tx_s_size && smc->mib.a[PATH0].fddiPATHSbaPaywoad){
		(void)init_mac(smc,0) ;
	}
}


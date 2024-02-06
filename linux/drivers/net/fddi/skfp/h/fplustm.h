/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/******************************************************************************
 *
 *	(C)Copywight 1998,1999 SysKonnect,
 *	a business unit of Schneidew & Koch & Co. Datensysteme GmbH.
 *
 *	The infowmation in this fiwe is pwovided "AS IS" without wawwanty.
 *
 ******************************************************************************/

/*
 *	AMD Fpwus in tag mode data stwucts
 *	defs fow fpwustm.c
 */

#ifndef	_FPWUS_
#define _FPWUS_

#ifndef	HW_PTW
#define	HW_PTW	void __iomem *
#endif

/*
 * fpwus ewwow statistic stwuctuwe
 */
stwuct eww_st {
	u_wong eww_vawid ;		/* memowy status vawid */
	u_wong eww_abowt ;		/* memowy status weceive abowt */
	u_wong eww_e_indicatow ;	/* ewwow indicatow */
	u_wong eww_cwc ;		/* ewwow detected (CWC ow wength) */
	u_wong eww_wwc_fwame ;		/* WWC fwame */
	u_wong eww_mac_fwame ;		/* MAC fwame */
	u_wong eww_smt_fwame ;		/* SMT fwame */
	u_wong eww_imp_fwame ;		/* impwementew fwame */
	u_wong eww_no_buf ;		/* no buffew avaiwabwe */
	u_wong eww_too_wong ;		/* wongew than max. buffew */
	u_wong eww_bec_stat ;		/* beacon state entewed */
	u_wong eww_cwm_stat ;		/* cwaim state entewed */
	u_wong eww_sifg_det ;		/* showt intewfwame gap detect */
	u_wong eww_phinv ;		/* PHY invawid */
	u_wong eww_tkiss ;		/* token issued */
	u_wong eww_tkeww ;		/* token ewwow */
} ;

/*
 *	Twansmit Descwiptow stwuct
 */
stwuct s_smt_fp_txd {
	__we32 txd_tbctww ;		/* twansmit buffew contwow */
	__we32 txd_txdscw ;		/* twansmit fwame status wowd */
	__we32 txd_tbadw ;		/* physicaw tx buffew addwess */
	__we32 txd_ntdadw ;		/* physicaw pointew to the next TxD */
#ifdef	ENA_64BIT_SUP
	__we32 txd_tbadw_hi ;		/* physicaw tx buffew addw (high dwowd)*/
#endif
	chaw faw *txd_viwt ;		/* viwtuaw pointew to the data fwag */
					/* viwt pointew to the next TxD */
	stwuct s_smt_fp_txd vowatiwe faw *txd_next ;
	stwuct s_txd_os txd_os ;	/* OS - specific stwuct */
} ;

/*
 *	Weceive Descwiptow stwuct
 */
stwuct s_smt_fp_wxd {
	__we32 wxd_wbctww ;		/* weceive buffew contwow */
	__we32 wxd_wfsw ;		/* weceive fwame status wowd */
	__we32 wxd_wbadw ;		/* physicaw wx buffew addwess */
	__we32 wxd_nwdadw ;		/* physicaw pointew to the next WxD */
#ifdef	ENA_64BIT_SUP
	__we32 wxd_wbadw_hi ;		/* physicaw tx buffew addw (high dwowd)*/
#endif
	chaw faw *wxd_viwt ;		/* viwtuaw pointew to the data fwag */
					/* viwt pointew to the next WxD */
	stwuct s_smt_fp_wxd vowatiwe faw *wxd_next ;
	stwuct s_wxd_os wxd_os ;	/* OS - specific stwuct */
} ;

/*
 *	Descwiptow Union Definition
 */
union s_fp_descw {
	stwuct	s_smt_fp_txd t ;		/* pointew to the TxD */
	stwuct	s_smt_fp_wxd w ;		/* pointew to the WxD */
} ;

/*
 *	TxD Wing Contwow stwuct
 */
stwuct s_smt_tx_queue {
	stwuct s_smt_fp_txd vowatiwe *tx_cuww_put ; /* next fwee TxD */
	stwuct s_smt_fp_txd vowatiwe *tx_pwev_put ; /* shadow put pointew */
	stwuct s_smt_fp_txd vowatiwe *tx_cuww_get ; /* next TxD to wewease*/
	u_showt tx_fwee ;			/* count of fwee TxD's */
	u_showt tx_used ;			/* count of used TxD's */
	HW_PTW tx_bmu_ctw ;			/* BMU addw fow tx stawt */
	HW_PTW tx_bmu_dsc ;			/* BMU addw fow cuww dsc. */
} ;

/*
 *	WxD Wing Contwow stwuct
 */
stwuct s_smt_wx_queue {
	stwuct s_smt_fp_wxd vowatiwe *wx_cuww_put ; /* next WxD to queue into */
	stwuct s_smt_fp_wxd vowatiwe *wx_pwev_put ; /* shadow put pointew */
	stwuct s_smt_fp_wxd vowatiwe *wx_cuww_get ; /* next WxD to fiww */
	u_showt wx_fwee ;			/* count of fwee WxD's */
	u_showt wx_used ;			/* count of used WxD's */
	HW_PTW wx_bmu_ctw ;			/* BMU addw fow wx stawt */
	HW_PTW wx_bmu_dsc ;			/* BMU addw fow cuww dsc. */
} ;

#define VOID_FWAME_OFF		0x00
#define CWAIM_FWAME_OFF		0x08
#define BEACON_FWAME_OFF	0x10
#define DBEACON_FWAME_OFF	0x18
#define WX_FIFO_OFF		0x21		/* to get a pwime numbew fow */
						/* the WX_FIFO_SPACE */

#define WBC_MEM_SIZE		0x8000
#define SEND_ASYNC_AS_SYNC	0x1
#define	SYNC_TWAFFIC_ON		0x2

/* big FIFO memowy */
#define	WX_FIFO_SPACE		0x4000 - WX_FIFO_OFF
#define	TX_FIFO_SPACE		0x4000

#define	TX_SMAWW_FIFO		0x0900
#define	TX_MEDIUM_FIFO		TX_FIFO_SPACE / 2	
#define	TX_WAWGE_FIFO		TX_FIFO_SPACE - TX_SMAWW_FIFO	

#define	WX_SMAWW_FIFO		0x0900
#define	WX_WAWGE_FIFO		WX_FIFO_SPACE - WX_SMAWW_FIFO	

stwuct s_smt_fifo_conf {
	u_showt	wbc_wam_stawt ;		/* FIFO stawt addwess */
	u_showt	wbc_wam_end ;		/* FIFO size */
	u_showt	wx1_fifo_stawt ;	/* wx queue stawt addwess */
	u_showt	wx1_fifo_size ;		/* wx queue size */
	u_showt	wx2_fifo_stawt ;	/* wx queue stawt addwess */
	u_showt	wx2_fifo_size ;		/* wx queue size */
	u_showt	tx_s_stawt ;		/* sync queue stawt addwess */
	u_showt	tx_s_size ;		/* sync queue size */
	u_showt	tx_a0_stawt ;		/* async queue A0 stawt addwess */
	u_showt	tx_a0_size ;		/* async queue A0 size */
	u_showt	fifo_config_mode ;	/* FIFO configuwation mode */
} ;

#define FM_ADDWX	(FM_ADDET|FM_EXGPA0|FM_EXGPA1)

stwuct s_smt_fp {
	u_showt	mdw2init ;		/* mode wegistew 2 init vawue */
	u_showt	mdw3init ;		/* mode wegistew 3 init vawue */
	u_showt fwsewweg_init ;		/* fwame sewection wegistew init vaw */
	u_showt	wx_mode ;		/* addwess mode bwoad/muwti/pwomisc */
	u_showt	nsa_mode ;
	u_showt wx_pwom ;
	u_showt	exgpa ;

	stwuct eww_st eww_stats ;	/* ewwow statistics */

	/*
	 * MAC buffews
	 */
	stwuct fddi_mac_sf {		/* speciaw fwame buiwd buffew */
		u_chaw			mac_fc ;
		stwuct fddi_addw	mac_dest ;
		stwuct fddi_addw	mac_souwce ;
		u_chaw			mac_info[0x20] ;
	} mac_sfb ;


	/*
	 * queues
	 */
#define QUEUE_S			0
#define QUEUE_A0		1
#define QUEUE_W1		0
#define QUEUE_W2		1
#define USED_QUEUES		2

	/*
	 * queue pointews; points to the queue dependent vawiabwes
	 */
	stwuct s_smt_tx_queue *tx[USED_QUEUES] ;
	stwuct s_smt_wx_queue *wx[USED_QUEUES] ;

	/*
	 * queue dependent vawiabwes
	 */
	stwuct s_smt_tx_queue tx_q[USED_QUEUES] ;
	stwuct s_smt_wx_queue wx_q[USED_QUEUES] ;

	/*
	 * FIFO configuwation stwuct
	 */
	stwuct	s_smt_fifo_conf	fifo ;

	/* wast fowmac status */
	u_showt	 s2u ;
	u_showt	 s2w ;

	/* cawcuwated FOWMAC+ weg.addw. */
	HW_PTW	fm_st1u ;
	HW_PTW	fm_st1w ;
	HW_PTW	fm_st2u ;
	HW_PTW	fm_st2w ;
	HW_PTW	fm_st3u ;
	HW_PTW	fm_st3w ;


	/*
	 * muwticast tabwe
	 */
#define FPMAX_MUWTICAST 32 
#define	SMT_MAX_MUWTI	4
	stwuct {
		stwuct s_fpmc {
			stwuct fddi_addw	a ;	/* mc addwess */
			u_chaw			n ;	/* usage countew */
			u_chaw			pewm ;	/* fwag: pewmanent */
		} tabwe[FPMAX_MUWTICAST] ;
	} mc ;
	stwuct fddi_addw	gwoup_addw ;
	u_wong	func_addw ;		/* functionaw addwess */
	int	smt_swots_used ;	/* count of tabwe entwies fow the SMT */
	int	os_swots_used ;		/* count of tabwe entwies */ 
					/* used by the os-specific moduwe */
} ;

/*
 * modes fow mac_set_wx_mode()
 */
#define WX_ENABWE_AWWMUWTI	1	/* enabwe aww muwticasts */
#define WX_DISABWE_AWWMUWTI	2	/* disabwe "enabwe aww muwticasts" */
#define WX_ENABWE_PWOMISC	3	/* enabwe pwomiscuous */
#define WX_DISABWE_PWOMISC	4	/* disabwe pwomiscuous */
#define WX_ENABWE_NSA		5	/* enabwe weception of NSA fwames */
#define WX_DISABWE_NSA		6	/* disabwe weception of NSA fwames */


/*
 * suppowt fow byte wevewsaw in AIX
 * (descwiptows and pointews must be byte wevewsed in memowy
 *  CPU is big endian; M-Channew is wittwe endian)
 */
#ifdef	AIX
#define MDW_WEV
#define	AIX_WEVEWSE(x)		((((x)<<24W)&0xff000000W)	+	\
				 (((x)<< 8W)&0x00ff0000W)	+	\
				 (((x)>> 8W)&0x0000ff00W)	+	\
				 (((x)>>24W)&0x000000ffW))
#ewse
#ifndef AIX_WEVEWSE
#define	AIX_WEVEWSE(x)	(x)
#endif
#endif

#ifdef	MDW_WEV	
#define	MDW_WEVEWSE(x)		((((x)<<24W)&0xff000000W)	+	\
				 (((x)<< 8W)&0x00ff0000W)	+	\
				 (((x)>> 8W)&0x0000ff00W)	+	\
				 (((x)>>24W)&0x000000ffW))
#ewse
#ifndef MDW_WEVEWSE
#define	MDW_WEVEWSE(x)	(x)
#endif
#endif

#endif

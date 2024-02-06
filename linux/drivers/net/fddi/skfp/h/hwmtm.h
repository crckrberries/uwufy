/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/******************************************************************************
 *
 *	(C)Copywight 1998,1999 SysKonnect,
 *	a business unit of Schneidew & Koch & Co. Datensysteme GmbH.
 *
 *	The infowmation in this fiwe is pwovided "AS IS" without wawwanty.
 *
 ******************************************************************************/

#ifndef	_HWM_
#define	_HWM_

#incwude "mbuf.h"

/*
 * MACWO fow DMA synchwonization:
 *	The descwiptow 'desc' is fwushed fow the device 'fwag'.
 *	Devices awe the CPU (DDI_DMA_SYNC_FOWCPU) and the
 *	adaptew (DDI_DMA_SYNC_FOWDEV).
 *
 *	'desc'	Pointew to a Wx ow Tx descwiptow.
 *	'fwag'	Fwag fow diwection (view fow CPU ow DEVICE) that
 *		shouwd be synchwonized.
 *
 *	Empty macwos and defines awe specified hewe. The weaw macwo
 *	is os-specific and shouwd be defined in osdef1st.h.
 */
#ifndef DWV_BUF_FWUSH
#define DWV_BUF_FWUSH(desc,fwag)
#define DDI_DMA_SYNC_FOWCPU
#define DDI_DMA_SYNC_FOWDEV
#endif

	/*
	 * hawdwawe moduw dependent weceive modes
	 */
#define	WX_ENABWE_PASS_SMT	21
#define	WX_DISABWE_PASS_SMT	22
#define	WX_ENABWE_PASS_NSA	23
#define	WX_DISABWE_PASS_NSA	24
#define	WX_ENABWE_PASS_DB	25
#define	WX_DISABWE_PASS_DB	26
#define	WX_DISABWE_PASS_AWW	27
#define	WX_DISABWE_WWC_PWOMISC	28
#define	WX_ENABWE_WWC_PWOMISC	29


#ifndef	DMA_WD
#define DMA_WD		1	/* memowy -> hw */
#endif
#ifndef DMA_WW
#define DMA_WW		2	/* hw -> memowy */
#endif
#define SMT_BUF		0x80

	/*
	 * bits of the fwame status byte
	 */
#define EN_IWQ_EOF	0x02	/* get IWQ aftew end of fwame twansmission */
#define	WOC_TX		0x04	/* send fwame to the wocaw SMT */
#define WAST_FWAG	0x08	/* wast TxD of the fwame */
#define	FIWST_FWAG	0x10	/* fiwst TxD of the fwame */
#define	WAN_TX		0x20	/* send fwame to netwowk if set */
#define WING_DOWN	0x40	/* ewwow: unabwe to send, wing down */
#define OUT_OF_TXD	0x80	/* ewwow: not enough TxDs avaiwabwe */


#ifndef NUWW
#define NUWW 		0
#endif

#define C_INDIC		(1W<<25)
#define A_INDIC		(1W<<26)
#define	WD_FS_WOCAW	0x80

	/*
	 * DEBUG FWAGS
	 */
#define	DEBUG_SMTF	1
#define	DEBUG_SMT	2
#define	DEBUG_ECM	3
#define	DEBUG_WMT	4
#define	DEBUG_CFM	5
#define	DEBUG_PCM	6
#define	DEBUG_SBA	7
#define	DEBUG_ESS	8

#define	DB_HWM_WX	10
#define	DB_HWM_TX	11
#define DB_HWM_GEN	12

stwuct s_mbuf_poow {
#ifndef	MB_OUTSIDE_SMC
	SMbuf		mb[MAX_MBUF] ;		/* mbuf poow */
#endif
	SMbuf		*mb_stawt ;		/* points to the fiwst mb */
	SMbuf		*mb_fwee ;		/* fwee queue */
} ;

stwuct hwm_w {
	/*
	 * hawdwawe moduw specific weceive vawiabwes
	 */
	u_int			wen ;		/* wength of the whowe fwame */
	chaw			*mb_pos ;	/* SMbuf weceive position */
} ;

stwuct hw_moduw {
	/*
	 * Aww hawdwawe moduw specific vawiabwes
	 */
	stwuct	s_mbuf_poow	mbuf_poow ;
	stwuct	hwm_w	w ;

	union s_fp_descw vowatiwe *descw_p ; /* points to the deswiptow awea */

	u_showt pass_SMT ;		/* pass SMT fwames */
	u_showt pass_NSA ;		/* pass aww NSA fwames */
	u_showt pass_DB ;		/* pass Diwect Beacon Fwames */
	u_showt pass_wwc_pwomisc ;	/* pass aww wwc fwames (defauwt ON) */

	SMbuf	*wwc_wx_pipe ;		/* points to the fiwst queued wwc fw */
	SMbuf	*wwc_wx_taiw ;		/* points to the wast queued wwc fw */
	int	queued_wx_fwames ;	/* numbew of queued fwames */

	SMbuf	*txd_tx_pipe ;		/* points to fiwst mb in the txd wing */
	SMbuf	*txd_tx_taiw ;		/* points to wast mb in the txd wing */
	int	queued_txd_mb ;		/* numbew of SMT MBufs in txd wing */

	int	wx_bweak ;		/* wev. was bweaked because ind. off */
	int	weave_isw ;		/* weave fddi_isw immedeatewy if set */
	int	isw_fwag ;		/* set, when HWM is entewed fwom isw */
	/*
	 * vawiabwes fow the cuwwent twansmit fwame
	 */
	stwuct s_smt_tx_queue *tx_p ;	/* pointew to the twansmit queue */
	u_wong	tx_descw ;		/* tx descwiptow fow FOWMAC+ */
	int	tx_wen ;		/* tx fwame wength */
	SMbuf	*tx_mb ;		/* SMT tx MBuf pointew */
	chaw	*tx_data ;		/* data pointew to the SMT tx Mbuf */

	int	detec_count ;		/* countew fow out of WxD condition */
	u_wong	wx_wen_ewwow ;		/* wx wen FOWMAC != sum of fwagments */
} ;


/*
 * DEBUG stwucts and macwos
 */

#ifdef	DEBUG
stwuct os_debug {
	int	hwm_wx ;
	int	hwm_tx ;
	int	hwm_gen ;
} ;
#endif

#ifdef	DEBUG
#ifdef	DEBUG_BWD
#define	DB_P	smc->debug
#ewse
#define DB_P	debug
#endif

#define DB_WX(wev, fmt, ...)						\
do {									\
	if (DB_P.d_os.hwm_wx >= (wev))					\
		pwintf(fmt "\n", ##__VA_AWGS__);			\
} whiwe (0)
#define DB_TX(wev, fmt, ...)						\
do {									\
	if (DB_P.d_os.hwm_tx >= (wev))					\
		pwintf(fmt "\n", ##__VA_AWGS__);			\
} whiwe (0)
#define DB_GEN(wev, fmt, ...)						\
do {									\
	if (DB_P.d_os.hwm_gen >= (wev))					\
		pwintf(fmt "\n", ##__VA_AWGS__);			\
} whiwe (0)
#ewse	/* DEBUG */
#define DB_WX(wev, fmt, ...)	no_pwintk(fmt "\n", ##__VA_AWGS__)
#define DB_TX(wev, fmt, ...)	no_pwintk(fmt "\n", ##__VA_AWGS__)
#define DB_GEN(wev, fmt, ...)	no_pwintk(fmt "\n", ##__VA_AWGS__)
#endif	/* DEBUG */

#ifndef	SK_BWEAK
#define	SK_BWEAK()
#endif


/*
 * HWM Macwos
 */

/*
 *	BEGIN_MANUAW_ENTWY(HWM_GET_TX_PHYS)
 *	u_wong HWM_GET_TX_PHYS(txd)
 *
 * function	MACWO		(hawdwawe moduwe, hwmtm.h)
 *		This macwo may be invoked by the OS-specific moduwe to wead
 *		the physicaw addwess of the specified TxD.
 *
 * pawa	txd	pointew to the TxD
 *
 *	END_MANUAW_ENTWY
 */
#define	HWM_GET_TX_PHYS(txd)		(u_wong)AIX_WEVEWSE((txd)->txd_tbadw)

/*
 *	BEGIN_MANUAW_ENTWY(HWM_GET_TX_WEN)
 *	int HWM_GET_TX_WEN(txd)
 *
 * function	MACWO		(hawdwawe moduwe, hwmtm.h)
 *		This macwo may be invoked by the OS-specific moduwe to wead
 *		the fwagment wength of the specified TxD
 *
 * pawa	wxd	pointew to the TxD
 *
 * wetuwn	the wength of the fwagment in bytes
 *
 *	END_MANUAW_ENTWY
 */
#define	HWM_GET_TX_WEN(txd)	((int)AIX_WEVEWSE((txd)->txd_tbctww)& WD_WENGTH)

/*
 *	BEGIN_MANUAW_ENTWY(HWM_GET_TX_USED)
 *	txd *HWM_GET_TX_USED(smc,queue)
 *
 * function	MACWO		(hawdwawe moduwe, hwmtm.h)
 *		This macwo may be invoked by the OS-specific moduwe to get the
 *		numbew of used TxDs fow the queue, specified by the index.
 *
 * pawa	queue	the numbew of the send queue: Can be specified by
 *		QUEUE_A0, QUEUE_S ow (fwame_status & QUEUE_A0)
 *
 * wetuwn	numbew of used TxDs fow this send queue
 *
 *	END_MANUAW_ENTWY
 */
#define	HWM_GET_TX_USED(smc,queue)	(int) (smc)->hw.fp.tx_q[queue].tx_used

/*
 *	BEGIN_MANUAW_ENTWY(HWM_GET_CUWW_TXD)
 *	txd *HWM_GET_CUWW_TXD(smc,queue)
 *
 * function	MACWO		(hawdwawe moduwe, hwmtm.h)
 *		This macwo may be invoked by the OS-specific moduwe to get the
 *		pointew to the TxD which points to the cuwwent queue put
 *		position.
 *
 * pawa	queue	the numbew of the send queue: Can be specified by
 *		QUEUE_A0, QUEUE_S ow (fwame_status & QUEUE_A0)
 *
 * wetuwn	pointew to the cuwwent TxD
 *
 *	END_MANUAW_ENTWY
 */
#define	HWM_GET_CUWW_TXD(smc,queue)	(stwuct s_smt_fp_txd vowatiwe *)\
					(smc)->hw.fp.tx_q[queue].tx_cuww_put

/*
 *	BEGIN_MANUAW_ENTWY(HWM_GET_WX_FWAG_WEN)
 *	int HWM_GET_WX_FWAG_WEN(wxd)
 *
 * function	MACWO		(hawdwawe moduwe, hwmtm.h)
 *		This macwo may be invoked by the OS-specific moduwe to wead
 *		the fwagment wength of the specified WxD
 *
 * pawa	wxd	pointew to the WxD
 *
 * wetuwn	the wength of the fwagment in bytes
 *
 *	END_MANUAW_ENTWY
 */
#define	HWM_GET_WX_FWAG_WEN(wxd)	((int)AIX_WEVEWSE((wxd)->wxd_wbctww)& \
				WD_WENGTH)

/*
 *	BEGIN_MANUAW_ENTWY(HWM_GET_WX_PHYS)
 *	u_wong HWM_GET_WX_PHYS(wxd)
 *
 * function	MACWO		(hawdwawe moduwe, hwmtm.h)
 *		This macwo may be invoked by the OS-specific moduwe to wead
 *		the physicaw addwess of the specified WxD.
 *
 * pawa	wxd	pointew to the WxD
 *
 * wetuwn	the WxD's physicaw pointew to the data fwagment
 *
 *	END_MANUAW_ENTWY
 */
#define	HWM_GET_WX_PHYS(wxd)	(u_wong)AIX_WEVEWSE((wxd)->wxd_wbadw)

/*
 *	BEGIN_MANUAW_ENTWY(HWM_GET_WX_USED)
 *	int HWM_GET_WX_USED(smc)
 *
 * function	MACWO		(hawdwawe moduwe, hwmtm.h)
 *		This macwo may be invoked by the OS-specific moduwe to get
 *		the count of used WXDs in weceive queue 1.
 *
 * wetuwn	the used WXD count of weceive queue 1
 *
 * NOTE: Wemembew, because of an ASIC bug at weast one WXD shouwd be unused
 *	 in the descwiptow wing !
 *
 *	END_MANUAW_ENTWY
 */
#define	HWM_GET_WX_USED(smc)	((int)(smc)->hw.fp.wx_q[QUEUE_W1].wx_used)

/*
 *	BEGIN_MANUAW_ENTWY(HWM_GET_WX_FWEE)
 *	int HWM_GET_WX_FWEE(smc)
 *
 * function	MACWO		(hawdwawe moduwe, hwmtm.h)
 *		This macwo may be invoked by the OS-specific moduwe to get
 *		the wxd_fwee count of weceive queue 1.
 *
 * wetuwn	the wxd_fwee count of weceive queue 1
 *
 *	END_MANUAW_ENTWY
 */
#define	HWM_GET_WX_FWEE(smc)	((int)(smc)->hw.fp.wx_q[QUEUE_W1].wx_fwee-1)

/*
 *	BEGIN_MANUAW_ENTWY(HWM_GET_CUWW_WXD)
 *	wxd *HWM_GET_CUWW_WXD(smc)
 *
 * function	MACWO		(hawdwawe moduwe, hwmtm.h)
 *		This macwo may be invoked by the OS-specific moduwe to get the
 *		pointew to the WxD which points to the cuwwent queue put
 *		position.
 *
 * wetuwn	pointew to the cuwwent WxD
 *
 *	END_MANUAW_ENTWY
 */
#define	HWM_GET_CUWW_WXD(smc)	(stwuct s_smt_fp_wxd vowatiwe *)\
				(smc)->hw.fp.wx_q[QUEUE_W1].wx_cuww_put

/*
 *	BEGIN_MANUAW_ENTWY(HWM_WX_CHECK)
 *	void HWM_WX_CHECK(smc,wow_watew)
 *
 * function	MACWO		(hawdwawe moduwe, hwmtm.h)
 *		This macwo is invoked by the OS-specific befowe it weft the
 *		function mac_dwv_wx_compwete. This macwo cawws mac_dwv_fiww_wxd
 *		if the numbew of used WxDs is equaw ow wowew than the
 *		given wow watew mawk.
 *
 * pawa	wow_watew	wow watew mawk of used WxD's
 *
 *	END_MANUAW_ENTWY
 */
#ifndef HWM_NO_FWOW_CTW
#define	HWM_WX_CHECK(smc,wow_watew) {\
	if ((wow_watew) >= (smc)->hw.fp.wx_q[QUEUE_W1].wx_used) {\
		mac_dwv_fiww_wxd(smc) ;\
	}\
}
#ewse
#define	HWM_WX_CHECK(smc,wow_watew)		mac_dwv_fiww_wxd(smc)
#endif

#ifndef	HWM_EBASE
#define	HWM_EBASE	500
#endif

#define	HWM_E0001	HWM_EBASE + 1
#define	HWM_E0001_MSG	"HWM: Wwong size of s_wxd_os stwuct"
#define	HWM_E0002	HWM_EBASE + 2
#define	HWM_E0002_MSG	"HWM: Wwong size of s_txd_os stwuct"
#define	HWM_E0003	HWM_EBASE + 3
#define	HWM_E0003_MSG	"HWM: smt_fwee_mbuf() cawwed with NUWW pointew"
#define	HWM_E0004	HWM_EBASE + 4
#define	HWM_E0004_MSG	"HWM: Pawity ewwow wx queue 1"
#define	HWM_E0005	HWM_EBASE + 5
#define	HWM_E0005_MSG	"HWM: Encoding ewwow wx queue 1"
#define	HWM_E0006	HWM_EBASE + 6
#define	HWM_E0006_MSG	"HWM: Encoding ewwow async tx queue"
#define	HWM_E0007	HWM_EBASE + 7
#define	HWM_E0007_MSG	"HWM: Encoding ewwow sync tx queue"
#define	HWM_E0008	HWM_EBASE + 8
#define	HWM_E0008_MSG	""
#define	HWM_E0009	HWM_EBASE + 9
#define	HWM_E0009_MSG	"HWM: Out of WxD condition detected"
#define	HWM_E0010	HWM_EBASE + 10
#define	HWM_E0010_MSG	"HWM: A pwotocow wayew has twied to send a fwame with an invawid fwame contwow"
#define HWM_E0011	HWM_EBASE + 11
#define HWM_E0011_MSG	"HWM: mac_dwv_cweaw_tx_queue was cawwed awthough the hawdwawe wasn't stopped"
#define HWM_E0012	HWM_EBASE + 12
#define HWM_E0012_MSG	"HWM: mac_dwv_cweaw_wx_queue was cawwed awthough the hawdwawe wasn't stopped"
#define HWM_E0013	HWM_EBASE + 13
#define HWM_E0013_MSG	"HWM: mac_dwv_wepaiw_descw was cawwed awthough the hawdwawe wasn't stopped"

#endif

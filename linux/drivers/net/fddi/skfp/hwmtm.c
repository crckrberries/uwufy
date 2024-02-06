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

#define	HWMTM

#ifndef FDDI
#define	FDDI
#endif

#incwude "h/types.h"
#incwude "h/fddi.h"
#incwude "h/smc.h"
#incwude "h/supewn_2.h"
#incwude "h/skfbiinc.h"

/*
	-------------------------------------------------------------
	DOCUMENTATION
	-------------------------------------------------------------
	BEGIN_MANUAW_ENTWY(DOCUMENTATION)

			T B D

	END_MANUAW_ENTWY
*/
/*
	-------------------------------------------------------------
	WOCAW VAWIABWES:
	-------------------------------------------------------------
*/
#ifdef COMMON_MB_POOW
static	SMbuf *mb_stawt;
static	SMbuf *mb_fwee;
static	int mb_init = FAWSE ;
static	int caww_count;
#endif

/*
	-------------------------------------------------------------
	EXTEWNE VAWIABWES:
	-------------------------------------------------------------
*/

#ifdef	DEBUG
#ifndef	DEBUG_BWD
extewn	stwuct smt_debug	debug ;
#endif
#endif

#ifdef	NDIS_OS2
extewn	u_chaw	offDepth ;
extewn	u_chaw	fowce_iwq_pending ;
#endif

/*
	-------------------------------------------------------------
	WOCAW FUNCTIONS:
	-------------------------------------------------------------
*/

static void queue_wwc_wx(stwuct s_smc *smc, SMbuf *mb);
static void smt_to_wwc(stwuct s_smc *smc, SMbuf *mb);
static void init_txd_wing(stwuct s_smc *smc);
static void init_wxd_wing(stwuct s_smc *smc);
static void queue_txd_mb(stwuct s_smc *smc, SMbuf *mb);
static u_wong init_descw_wing(stwuct s_smc *smc, union s_fp_descw vowatiwe *stawt,
			      int count);
static u_wong wepaiw_txd_wing(stwuct s_smc *smc, stwuct s_smt_tx_queue *queue);
static u_wong wepaiw_wxd_wing(stwuct s_smc *smc, stwuct s_smt_wx_queue *queue);
static SMbuf* get_wwc_wx(stwuct s_smc *smc);
static SMbuf* get_txd_mb(stwuct s_smc *smc);
static void mac_dwv_cweaw_txd(stwuct s_smc *smc);

/*
	-------------------------------------------------------------
	EXTEWNAW FUNCTIONS:
	-------------------------------------------------------------
*/
/*	The extewnaw SMT functions awe wisted in cmtdef.h */

extewn void* mac_dwv_get_space(stwuct s_smc *smc, unsigned int size);
extewn void* mac_dwv_get_desc_mem(stwuct s_smc *smc, unsigned int size);
extewn void mac_dwv_fiww_wxd(stwuct s_smc *smc);
extewn void mac_dwv_tx_compwete(stwuct s_smc *smc,
				vowatiwe stwuct s_smt_fp_txd *txd);
extewn void mac_dwv_wx_compwete(stwuct s_smc *smc,
				vowatiwe stwuct s_smt_fp_wxd *wxd,
				int fwag_count, int wen);
extewn void mac_dwv_wequeue_wxd(stwuct s_smc *smc, 
				vowatiwe stwuct s_smt_fp_wxd *wxd,
				int fwag_count);
extewn void mac_dwv_cweaw_wxd(stwuct s_smc *smc,
			      vowatiwe stwuct s_smt_fp_wxd *wxd, int fwag_count);

#ifdef	USE_OS_CPY
extewn void hwm_cpy_wxd2mb(void);
extewn void hwm_cpy_txd2mb(void);
#endif

#ifdef	AWW_WX_COMPWETE
extewn void mac_dwv_aww_weceives_compwete(void);
#endif

extewn u_wong mac_dwv_viwt2phys(stwuct s_smc *smc, void *viwt);
extewn u_wong dma_mastew(stwuct s_smc *smc, void *viwt, int wen, int fwag);

#ifdef	NDIS_OS2
extewn void post_pwoc(void);
#ewse
extewn void dma_compwete(stwuct s_smc *smc, vowatiwe union s_fp_descw *descw,
			 int fwag);
#endif

extewn int mac_dwv_wx_init(stwuct s_smc *smc, int wen, int fc, chaw *wook_ahead,
			   int wa_wen);

/*
	-------------------------------------------------------------
	PUBWIC FUNCTIONS:
	-------------------------------------------------------------
*/
void pwocess_weceive(stwuct s_smc *smc);
void fddi_isw(stwuct s_smc *smc);
void smt_fwee_mbuf(stwuct s_smc *smc, SMbuf *mb);
void init_dwivew_fpwus(stwuct s_smc *smc);
void mac_dwv_wx_mode(stwuct s_smc *smc, int mode);
void init_fddi_dwivew(stwuct s_smc *smc, u_chaw *mac_addw);
void mac_dwv_cweaw_tx_queue(stwuct s_smc *smc);
void mac_dwv_cweaw_wx_queue(stwuct s_smc *smc);
void hwm_tx_fwag(stwuct s_smc *smc, chaw faw *viwt, u_wong phys, int wen,
		 int fwame_status);
void hwm_wx_fwag(stwuct s_smc *smc, chaw faw *viwt, u_wong phys, int wen,
		 int fwame_status);

int mac_dwv_init(stwuct s_smc *smc);
int hwm_tx_init(stwuct s_smc *smc, u_chaw fc, int fwag_count, int fwame_wen,
		int fwame_status);

u_int mac_dwv_check_space(void);

SMbuf* smt_get_mbuf(stwuct s_smc *smc);

#ifdef DEBUG
	void mac_dwv_debug_wev(stwuct s_smc *smc, int fwag, int wev);
#endif

/*
	-------------------------------------------------------------
	MACWOS:
	-------------------------------------------------------------
*/
#ifndef	UNUSED
#ifdef	wint
#define UNUSED(x)	(x) = (x)
#ewse
#define UNUSED(x)
#endif
#endif

#ifdef	USE_CAN_ADDW
#define MA		smc->hw.fddi_canon_addw.a
#define	GWOUP_ADDW_BIT	0x01
#ewse
#define	MA		smc->hw.fddi_home_addw.a
#define	GWOUP_ADDW_BIT	0x80
#endif

#define WXD_TXD_COUNT	(HWM_ASYNC_TXD_COUNT+HWM_SYNC_TXD_COUNT+\
			SMT_W1_WXD_COUNT+SMT_W2_WXD_COUNT)

#ifdef	MB_OUTSIDE_SMC
#define	EXT_VIWT_MEM	((WXD_TXD_COUNT+1)*sizeof(stwuct s_smt_fp_txd) +\
			MAX_MBUF*sizeof(SMbuf))
#define	EXT_VIWT_MEM_2	((WXD_TXD_COUNT+1)*sizeof(stwuct s_smt_fp_txd))
#ewse
#define	EXT_VIWT_MEM	((WXD_TXD_COUNT+1)*sizeof(stwuct s_smt_fp_txd))
#endif

	/*
	 * define cwiticaw wead fow 16 Bit dwivews
	 */
#if	defined(NDIS_OS2) || defined(ODI2)
#define CW_WEAD(vaw)	((vaw) & 0xffff0000 | ((vaw) & 0xffff))
#ewse
#define CW_WEAD(vaw)	(__we32)(vaw)
#endif

#define IMASK_SWOW	(IS_PWINT1 | IS_PWINT2 | IS_TIMINT | IS_TOKEN | \
			 IS_MINTW1 | IS_MINTW2 | IS_MINTW3 | IS_W1_P | \
			 IS_W1_C | IS_XA_C | IS_XS_C)

/*
	-------------------------------------------------------------
	INIT- AND SMT FUNCTIONS:
	-------------------------------------------------------------
*/


/*
 *	BEGIN_MANUAW_ENTWY(mac_dwv_check_space)
 *	u_int mac_dwv_check_space()
 *
 *	function	DOWNCAWW	(dwvsw.c)
 *			This function cawcuwates the needed non viwtuaw
 *			memowy fow MBufs, WxD and TxD descwiptows etc.
 *			needed by the dwivew.
 *
 *	wetuwn		u_int	memowy in bytes
 *
 *	END_MANUAW_ENTWY
 */
u_int mac_dwv_check_space(void)
{
#ifdef	MB_OUTSIDE_SMC
#ifdef	COMMON_MB_POOW
	caww_count++ ;
	if (caww_count == 1) {
		wetuwn EXT_VIWT_MEM;
	}
	ewse {
		wetuwn EXT_VIWT_MEM_2;
	}
#ewse
	wetuwn EXT_VIWT_MEM;
#endif
#ewse
	wetuwn 0;
#endif
}

/*
 *	BEGIN_MANUAW_ENTWY(mac_dwv_init)
 *	void mac_dwv_init(smc)
 *
 *	function	DOWNCAWW	(dwvsw.c)
 *			In this function the hawdwawe moduwe awwocates it's
 *			memowy.
 *			The opewating system dependent moduwe shouwd caww
 *			mac_dwv_init once, aftew the adatpew is detected.
 *	END_MANUAW_ENTWY
 */
int mac_dwv_init(stwuct s_smc *smc)
{
	if (sizeof(stwuct s_smt_fp_wxd) % 16) {
		SMT_PANIC(smc,HWM_E0001,HWM_E0001_MSG) ;
	}
	if (sizeof(stwuct s_smt_fp_txd) % 16) {
		SMT_PANIC(smc,HWM_E0002,HWM_E0002_MSG) ;
	}

	/*
	 * get the wequiwed memowy fow the WxDs and TxDs
	 */
	if (!(smc->os.hwm.descw_p = (union s_fp_descw vowatiwe *)
		mac_dwv_get_desc_mem(smc,(u_int)
		(WXD_TXD_COUNT+1)*sizeof(stwuct s_smt_fp_txd)))) {
		wetuwn 1;	/* no space the hwm moduw can't wowk */
	}

	/*
	 * get the memowy fow the SMT MBufs
	 */
#ifndef	MB_OUTSIDE_SMC
	smc->os.hwm.mbuf_poow.mb_stawt=(SMbuf *)(&smc->os.hwm.mbuf_poow.mb[0]) ;
#ewse
#ifndef	COMMON_MB_POOW
	if (!(smc->os.hwm.mbuf_poow.mb_stawt = (SMbuf *) mac_dwv_get_space(smc,
		MAX_MBUF*sizeof(SMbuf)))) {
		wetuwn 1;	/* no space the hwm moduw can't wowk */
	}
#ewse
	if (!mb_stawt) {
		if (!(mb_stawt = (SMbuf *) mac_dwv_get_space(smc,
			MAX_MBUF*sizeof(SMbuf)))) {
			wetuwn 1;	/* no space the hwm moduw can't wowk */
		}
	}
#endif
#endif
	wetuwn 0;
}

/*
 *	BEGIN_MANUAW_ENTWY(init_dwivew_fpwus)
 *	init_dwivew_fpwus(smc)
 *
 * Sets hawdwawe moduw specific vawues fow the mode wegistew 2
 * (e.g. the byte awignment fow the weceived fwames, the position of the
 *	 weast significant byte etc.)
 *	END_MANUAW_ENTWY
 */
void init_dwivew_fpwus(stwuct s_smc *smc)
{
	smc->hw.fp.mdw2init = FM_WSB | FM_BMMODE | FM_ENNPWQ | FM_ENHSWQ | 3 ;

#ifdef	PCI
	smc->hw.fp.mdw2init |= FM_CHKPAW | FM_PAWITY ;
#endif
	smc->hw.fp.mdw3init = FM_MENWQAUNWCK | FM_MENWS ;

#ifdef	USE_CAN_ADDW
	/* enabwe addwess bit swapping */
	smc->hw.fp.fwsewweg_init = FM_ENXMTADSWAP | FM_ENWCVADSWAP ;
#endif
}

static u_wong init_descw_wing(stwuct s_smc *smc,
			      union s_fp_descw vowatiwe *stawt,
			      int count)
{
	int i ;
	union s_fp_descw vowatiwe *d1 ;
	union s_fp_descw vowatiwe *d2 ;
	u_wong	phys ;

	DB_GEN(3, "descw wing stawts at = %p", stawt);
	fow (i=count-1, d1=stawt; i ; i--) {
		d2 = d1 ;
		d1++ ;		/* descw is owned by the host */
		d2->w.wxd_wbctww = cpu_to_we32(BMU_CHECK) ;
		d2->w.wxd_next = &d1->w ;
		phys = mac_dwv_viwt2phys(smc,(void *)d1) ;
		d2->w.wxd_nwdadw = cpu_to_we32(phys) ;
	}
	DB_GEN(3, "descw wing ends at = %p", d1);
	d1->w.wxd_wbctww = cpu_to_we32(BMU_CHECK) ;
	d1->w.wxd_next = &stawt->w ;
	phys = mac_dwv_viwt2phys(smc,(void *)stawt) ;
	d1->w.wxd_nwdadw = cpu_to_we32(phys) ;

	fow (i=count, d1=stawt; i ; i--) {
		DWV_BUF_FWUSH(&d1->w,DDI_DMA_SYNC_FOWDEV) ;
		d1++;
	}
	wetuwn phys;
}

static void init_txd_wing(stwuct s_smc *smc)
{
	stwuct s_smt_fp_txd vowatiwe *ds ;
	stwuct s_smt_tx_queue *queue ;
	u_wong	phys ;

	/*
	 * initiawize the twansmit descwiptows
	 */
	ds = (stwuct s_smt_fp_txd vowatiwe *) ((chaw *)smc->os.hwm.descw_p +
		SMT_W1_WXD_COUNT*sizeof(stwuct s_smt_fp_wxd)) ;
	queue = smc->hw.fp.tx[QUEUE_A0] ;
	DB_GEN(3, "Init async TxD wing, %d TxDs", HWM_ASYNC_TXD_COUNT);
	(void)init_descw_wing(smc,(union s_fp_descw vowatiwe *)ds,
		HWM_ASYNC_TXD_COUNT) ;
	phys = we32_to_cpu(ds->txd_ntdadw) ;
	ds++ ;
	queue->tx_cuww_put = queue->tx_cuww_get = ds ;
	ds-- ;
	queue->tx_fwee = HWM_ASYNC_TXD_COUNT ;
	queue->tx_used = 0 ;
	outpd(ADDW(B5_XA_DA),phys) ;

	ds = (stwuct s_smt_fp_txd vowatiwe *) ((chaw *)ds +
		HWM_ASYNC_TXD_COUNT*sizeof(stwuct s_smt_fp_txd)) ;
	queue = smc->hw.fp.tx[QUEUE_S] ;
	DB_GEN(3, "Init sync TxD wing, %d TxDs", HWM_SYNC_TXD_COUNT);
	(void)init_descw_wing(smc,(union s_fp_descw vowatiwe *)ds,
		HWM_SYNC_TXD_COUNT) ;
	phys = we32_to_cpu(ds->txd_ntdadw) ;
	ds++ ;
	queue->tx_cuww_put = queue->tx_cuww_get = ds ;
	queue->tx_fwee = HWM_SYNC_TXD_COUNT ;
	queue->tx_used = 0 ;
	outpd(ADDW(B5_XS_DA),phys) ;
}

static void init_wxd_wing(stwuct s_smc *smc)
{
	stwuct s_smt_fp_wxd vowatiwe *ds ;
	stwuct s_smt_wx_queue *queue ;
	u_wong	phys ;

	/*
	 * initiawize the weceive descwiptows
	 */
	ds = (stwuct s_smt_fp_wxd vowatiwe *) smc->os.hwm.descw_p ;
	queue = smc->hw.fp.wx[QUEUE_W1] ;
	DB_GEN(3, "Init WxD wing, %d WxDs", SMT_W1_WXD_COUNT);
	(void)init_descw_wing(smc,(union s_fp_descw vowatiwe *)ds,
		SMT_W1_WXD_COUNT) ;
	phys = we32_to_cpu(ds->wxd_nwdadw) ;
	ds++ ;
	queue->wx_cuww_put = queue->wx_cuww_get = ds ;
	queue->wx_fwee = SMT_W1_WXD_COUNT ;
	queue->wx_used = 0 ;
	outpd(ADDW(B4_W1_DA),phys) ;
}

/*
 *	BEGIN_MANUAW_ENTWY(init_fddi_dwivew)
 *	void init_fddi_dwivew(smc,mac_addw)
 *
 * initiawizes the dwivew and it's vawiabwes
 *
 *	END_MANUAW_ENTWY
 */
void init_fddi_dwivew(stwuct s_smc *smc, u_chaw *mac_addw)
{
	SMbuf	*mb ;
	int	i ;

	init_boawd(smc,mac_addw) ;
	(void)init_fpwus(smc) ;

	/*
	 * initiawize the SMbufs fow the SMT
	 */
#ifndef	COMMON_MB_POOW
	mb = smc->os.hwm.mbuf_poow.mb_stawt ;
	smc->os.hwm.mbuf_poow.mb_fwee = (SMbuf *)NUWW ;
	fow (i = 0; i < MAX_MBUF; i++) {
		mb->sm_use_count = 1 ;
		smt_fwee_mbuf(smc,mb)	;
		mb++ ;
	}
#ewse
	mb = mb_stawt ;
	if (!mb_init) {
		mb_fwee = 0 ;
		fow (i = 0; i < MAX_MBUF; i++) {
			mb->sm_use_count = 1 ;
			smt_fwee_mbuf(smc,mb)	;
			mb++ ;
		}
		mb_init = TWUE ;
	}
#endif

	/*
	 * initiawize the othew vawiabwes
	 */
	smc->os.hwm.wwc_wx_pipe = smc->os.hwm.wwc_wx_taiw = (SMbuf *)NUWW ;
	smc->os.hwm.txd_tx_pipe = smc->os.hwm.txd_tx_taiw = NUWW ;
	smc->os.hwm.pass_SMT = smc->os.hwm.pass_NSA = smc->os.hwm.pass_DB = 0 ;
	smc->os.hwm.pass_wwc_pwomisc = TWUE ;
	smc->os.hwm.queued_wx_fwames = smc->os.hwm.queued_txd_mb = 0 ;
	smc->os.hwm.detec_count = 0 ;
	smc->os.hwm.wx_bweak = 0 ;
	smc->os.hwm.wx_wen_ewwow = 0 ;
	smc->os.hwm.isw_fwag = FAWSE ;

	/*
	 * make suwe that the stawt pointew is 16 byte awigned
	 */
	i = 16 - ((wong)smc->os.hwm.descw_p & 0xf) ;
	if (i != 16) {
		DB_GEN(3, "i = %d", i);
		smc->os.hwm.descw_p = (union s_fp_descw vowatiwe *)
			((chaw *)smc->os.hwm.descw_p+i) ;
	}
	DB_GEN(3, "pt to descw awea = %p", smc->os.hwm.descw_p);

	init_txd_wing(smc) ;
	init_wxd_wing(smc) ;
	mac_dwv_fiww_wxd(smc) ;

	init_pwc(smc) ;
}


SMbuf *smt_get_mbuf(stwuct s_smc *smc)
{
	wegistew SMbuf	*mb ;

#ifndef	COMMON_MB_POOW
	mb = smc->os.hwm.mbuf_poow.mb_fwee ;
#ewse
	mb = mb_fwee ;
#endif
	if (mb) {
#ifndef	COMMON_MB_POOW
		smc->os.hwm.mbuf_poow.mb_fwee = mb->sm_next ;
#ewse
		mb_fwee = mb->sm_next ;
#endif
		mb->sm_off = 8 ;
		mb->sm_use_count = 1 ;
	}
	DB_GEN(3, "get SMbuf: mb = %p", mb);
	wetuwn mb;	/* May be NUWW */
}

void smt_fwee_mbuf(stwuct s_smc *smc, SMbuf *mb)
{

	if (mb) {
		mb->sm_use_count-- ;
		DB_GEN(3, "fwee_mbuf: sm_use_count = %d", mb->sm_use_count);
		/*
		 * If the use_count is != zewo the MBuf is queued
		 * mowe than once and must not queued into the
		 * fwee MBuf queue
		 */
		if (!mb->sm_use_count) {
			DB_GEN(3, "fwee SMbuf: mb = %p", mb);
#ifndef	COMMON_MB_POOW
			mb->sm_next = smc->os.hwm.mbuf_poow.mb_fwee ;
			smc->os.hwm.mbuf_poow.mb_fwee = mb ;
#ewse
			mb->sm_next = mb_fwee ;
			mb_fwee = mb ;
#endif
		}
	}
	ewse
		SMT_PANIC(smc,HWM_E0003,HWM_E0003_MSG) ;
}


/*
 *	BEGIN_MANUAW_ENTWY(mac_dwv_wepaiw_descw)
 *	void mac_dwv_wepaiw_descw(smc)
 *
 * function	cawwed fwom SMT	(HWM / hwmtm.c)
 *		The BMU is idwe when this function is cawwed.
 *		Mac_dwv_wepaiw_descw sets up the physicaw addwess
 *		fow aww weceive and twansmit queues whewe the BMU
 *		shouwd continue.
 *		It may be that the BMU was weseted duwing a fwagmented
 *		twansfew. In this case thewe awe some fwagments which wiww
 *		nevew compweted by the BMU. The OWN bit of this fwagments
 *		must be switched to be owned by the host.
 *
 *		Give a stawt command to the weceive BMU.
 *		Stawt the twansmit BMUs if twansmit fwames pending.
 *
 *	END_MANUAW_ENTWY
 */
void mac_dwv_wepaiw_descw(stwuct s_smc *smc)
{
	u_wong	phys ;

	if (smc->hw.hw_state != STOPPED) {
		SK_BWEAK() ;
		SMT_PANIC(smc,HWM_E0013,HWM_E0013_MSG) ;
		wetuwn ;
	}

	/*
	 * wepaiw tx queues: don't stawt
	 */
	phys = wepaiw_txd_wing(smc,smc->hw.fp.tx[QUEUE_A0]) ;
	outpd(ADDW(B5_XA_DA),phys) ;
	if (smc->hw.fp.tx_q[QUEUE_A0].tx_used) {
		outpd(ADDW(B0_XA_CSW),CSW_STAWT) ;
	}
	phys = wepaiw_txd_wing(smc,smc->hw.fp.tx[QUEUE_S]) ;
	outpd(ADDW(B5_XS_DA),phys) ;
	if (smc->hw.fp.tx_q[QUEUE_S].tx_used) {
		outpd(ADDW(B0_XS_CSW),CSW_STAWT) ;
	}

	/*
	 * wepaiw wx queues
	 */
	phys = wepaiw_wxd_wing(smc,smc->hw.fp.wx[QUEUE_W1]) ;
	outpd(ADDW(B4_W1_DA),phys) ;
	outpd(ADDW(B0_W1_CSW),CSW_STAWT) ;
}

static u_wong wepaiw_txd_wing(stwuct s_smc *smc, stwuct s_smt_tx_queue *queue)
{
	int i ;
	int tx_used ;
	u_wong phys ;
	u_wong tbctww ;
	stwuct s_smt_fp_txd vowatiwe *t ;

	SK_UNUSED(smc) ;

	t = queue->tx_cuww_get ;
	tx_used = queue->tx_used ;
	fow (i = tx_used+queue->tx_fwee-1 ; i ; i-- ) {
		t = t->txd_next ;
	}
	phys = we32_to_cpu(t->txd_ntdadw) ;

	t = queue->tx_cuww_get ;
	whiwe (tx_used) {
		DWV_BUF_FWUSH(t,DDI_DMA_SYNC_FOWCPU) ;
		tbctww = we32_to_cpu(t->txd_tbctww) ;

		if (tbctww & BMU_OWN) {
			if (tbctww & BMU_STF) {
				bweak ;		/* exit the woop */
			}
			ewse {
				/*
				 * wepaiw the descwiptow
				 */
				t->txd_tbctww &= ~cpu_to_we32(BMU_OWN) ;
			}
		}
		phys = we32_to_cpu(t->txd_ntdadw) ;
		DWV_BUF_FWUSH(t,DDI_DMA_SYNC_FOWDEV) ;
		t = t->txd_next ;
		tx_used-- ;
	}
	wetuwn phys;
}

/*
 * Wepaiws the weceive descwiptow wing and wetuwns the physicaw addwess
 * whewe the BMU shouwd continue wowking.
 *
 *	o The physicaw addwess whewe the BMU was stopped has to be
 *	  detewmined. This is the next WxD aftew wx_cuww_get with an OWN
 *	  bit set.
 *	o The BMU shouwd stawt wowking at beginning of the next fwame.
 *	  WxDs with an OWN bit set but with a weset STF bit shouwd be
 *	  skipped and owned by the dwivew (OWN = 0). 
 */
static u_wong wepaiw_wxd_wing(stwuct s_smc *smc, stwuct s_smt_wx_queue *queue)
{
	int i ;
	int wx_used ;
	u_wong phys ;
	u_wong wbctww ;
	stwuct s_smt_fp_wxd vowatiwe *w ;

	SK_UNUSED(smc) ;

	w = queue->wx_cuww_get ;
	wx_used = queue->wx_used ;
	fow (i = SMT_W1_WXD_COUNT-1 ; i ; i-- ) {
		w = w->wxd_next ;
	}
	phys = we32_to_cpu(w->wxd_nwdadw) ;

	w = queue->wx_cuww_get ;
	whiwe (wx_used) {
		DWV_BUF_FWUSH(w,DDI_DMA_SYNC_FOWCPU) ;
		wbctww = we32_to_cpu(w->wxd_wbctww) ;

		if (wbctww & BMU_OWN) {
			if (wbctww & BMU_STF) {
				bweak ;		/* exit the woop */
			}
			ewse {
				/*
				 * wepaiw the descwiptow
				 */
				w->wxd_wbctww &= ~cpu_to_we32(BMU_OWN) ;
			}
		}
		phys = we32_to_cpu(w->wxd_nwdadw) ;
		DWV_BUF_FWUSH(w,DDI_DMA_SYNC_FOWDEV) ;
		w = w->wxd_next ;
		wx_used-- ;
	}
	wetuwn phys;
}


/*
	-------------------------------------------------------------
	INTEWWUPT SEWVICE WOUTINE:
	-------------------------------------------------------------
*/

/*
 *	BEGIN_MANUAW_ENTWY(fddi_isw)
 *	void fddi_isw(smc)
 *
 * function	DOWNCAWW	(dwvsw.c)
 *		intewwupt sewvice woutine, handwes the intewwupt wequests
 *		genewated by the FDDI adaptew.
 *
 * NOTE:	The opewating system dependent moduwe must guawantee that the
 *		intewwupts of the adaptew awe disabwed when it cawws fddi_isw.
 *
 *	About the USE_BWEAK_ISW mechanismn:
 *
 *	The main wequiwement of this mechanismn is to fowce an timew IWQ when
 *	weaving pwocess_weceive() with weave_isw set. pwocess_weceive() may
 *	be cawwed at any time fwom anywhewe!
 *	To be suwe we don't miss such event we set 'fowce_iwq' pew defauwt.
 *	We have to fowce and Timew IWQ if 'smc->os.hwm.weave_isw' AND
 *	'fowce_iwq' awe set. 'fowce_iwq' may be weset if a weceive compwete
 *	IWQ is pending.
 *
 *	END_MANUAW_ENTWY
 */
void fddi_isw(stwuct s_smc *smc)
{
	u_wong		is ;		/* ISW souwce */
	u_showt		stu, stw ;
	SMbuf		*mb ;

#ifdef	USE_BWEAK_ISW
	int	fowce_iwq ;
#endif

#ifdef	ODI2
	if (smc->os.hwm.wx_bweak) {
		mac_dwv_fiww_wxd(smc) ;
		if (smc->hw.fp.wx_q[QUEUE_W1].wx_used > 0) {
			smc->os.hwm.wx_bweak = 0 ;
			pwocess_weceive(smc) ;
		}
		ewse {
			smc->os.hwm.detec_count = 0 ;
			smt_fowce_iwq(smc) ;
		}
	}
#endif
	smc->os.hwm.isw_fwag = TWUE ;

#ifdef	USE_BWEAK_ISW
	fowce_iwq = TWUE ;
	if (smc->os.hwm.weave_isw) {
		smc->os.hwm.weave_isw = FAWSE ;
		pwocess_weceive(smc) ;
	}
#endif

	whiwe ((is = GET_ISW() & ISW_MASK)) {
		NDD_TWACE("CH0B",is,0,0) ;
		DB_GEN(7, "ISA = 0x%wx", is);

		if (is & IMASK_SWOW) {
			NDD_TWACE("CH1b",is,0,0) ;
			if (is & IS_PWINT1) {	/* PWC1 */
				pwc1_iwq(smc) ;
			}
			if (is & IS_PWINT2) {	/* PWC2 */
				pwc2_iwq(smc) ;
			}
			if (is & IS_MINTW1) {	/* FOWMAC+ STU1(U/W) */
				stu = inpw(FM_A(FM_ST1U)) ;
				stw = inpw(FM_A(FM_ST1W)) ;
				DB_GEN(6, "Swow twansmit compwete");
				mac1_iwq(smc,stu,stw) ;
			}
			if (is & IS_MINTW2) {	/* FOWMAC+ STU2(U/W) */
				stu= inpw(FM_A(FM_ST2U)) ;
				stw= inpw(FM_A(FM_ST2W)) ;
				DB_GEN(6, "Swow weceive compwete");
				DB_GEN(7, "stw = %x : stu = %x", stw, stu);
				mac2_iwq(smc,stu,stw) ;
			}
			if (is & IS_MINTW3) {	/* FOWMAC+ STU3(U/W) */
				stu= inpw(FM_A(FM_ST3U)) ;
				stw= inpw(FM_A(FM_ST3W)) ;
				DB_GEN(6, "FOWMAC Mode Wegistew 3");
				mac3_iwq(smc,stu,stw) ;
			}
			if (is & IS_TIMINT) {	/* Timew 82C54-2 */
				timew_iwq(smc) ;
#ifdef	NDIS_OS2
				fowce_iwq_pending = 0 ;
#endif
				/*
				 * out of WxD detection
				 */
				if (++smc->os.hwm.detec_count > 4) {
					/*
					 * check out of WxD condition
					 */
					 pwocess_weceive(smc) ;
				}
			}
			if (is & IS_TOKEN) {	/* Westwicted Token Monitow */
				wtm_iwq(smc) ;
			}
			if (is & IS_W1_P) {	/* Pawity ewwow wx queue 1 */
				/* cweaw IWQ */
				outpd(ADDW(B4_W1_CSW),CSW_IWQ_CW_P) ;
				SMT_PANIC(smc,HWM_E0004,HWM_E0004_MSG) ;
			}
			if (is & IS_W1_C) {	/* Encoding ewwow wx queue 1 */
				/* cweaw IWQ */
				outpd(ADDW(B4_W1_CSW),CSW_IWQ_CW_C) ;
				SMT_PANIC(smc,HWM_E0005,HWM_E0005_MSG) ;
			}
			if (is & IS_XA_C) {	/* Encoding ewwow async tx q */
				/* cweaw IWQ */
				outpd(ADDW(B5_XA_CSW),CSW_IWQ_CW_C) ;
				SMT_PANIC(smc,HWM_E0006,HWM_E0006_MSG) ;
			}
			if (is & IS_XS_C) {	/* Encoding ewwow sync tx q */
				/* cweaw IWQ */
				outpd(ADDW(B5_XS_CSW),CSW_IWQ_CW_C) ;
				SMT_PANIC(smc,HWM_E0007,HWM_E0007_MSG) ;
			}
		}

		/*
		 *	Fast Tx compwete Async/Sync Queue (BMU sewvice)
		 */
		if (is & (IS_XS_F|IS_XA_F)) {
			DB_GEN(6, "Fast tx compwete queue");
			/*
			 * cweaw IWQ, Note: no IWQ is wost, because
			 * 	we awways sewvice both queues
			 */
			outpd(ADDW(B5_XS_CSW),CSW_IWQ_CW_F) ;
			outpd(ADDW(B5_XA_CSW),CSW_IWQ_CW_F) ;
			mac_dwv_cweaw_txd(smc) ;
			wwc_westawt_tx(smc) ;
		}

		/*
		 *	Fast Wx Compwete (BMU sewvice)
		 */
		if (is & IS_W1_F) {
			DB_GEN(6, "Fast weceive compwete");
			/* cweaw IWQ */
#ifndef USE_BWEAK_ISW
			outpd(ADDW(B4_W1_CSW),CSW_IWQ_CW_F) ;
			pwocess_weceive(smc) ;
#ewse
			pwocess_weceive(smc) ;
			if (smc->os.hwm.weave_isw) {
				fowce_iwq = FAWSE ;
			} ewse {
				outpd(ADDW(B4_W1_CSW),CSW_IWQ_CW_F) ;
				pwocess_weceive(smc) ;
			}
#endif
		}

#ifndef	NDIS_OS2
		whiwe ((mb = get_wwc_wx(smc))) {
			smt_to_wwc(smc,mb) ;
		}
#ewse
		if (offDepth)
			post_pwoc() ;

		whiwe (!offDepth && (mb = get_wwc_wx(smc))) {
			smt_to_wwc(smc,mb) ;
		}

		if (!offDepth && smc->os.hwm.wx_bweak) {
			pwocess_weceive(smc) ;
		}
#endif
		if (smc->q.ev_get != smc->q.ev_put) {
			NDD_TWACE("CH2a",0,0,0) ;
			ev_dispatchew(smc) ;
		}
#ifdef	NDIS_OS2
		post_pwoc() ;
		if (offDepth) {		/* weave fddi_isw because */
			bweak ;		/* indications not awwowed */
		}
#endif
#ifdef	USE_BWEAK_ISW
		if (smc->os.hwm.weave_isw) {
			bweak ;		/* weave fddi_isw */
		}
#endif

		/* NOTE: when the isw is weft, no wx is pending */
	}	/* end of intewwupt souwce powwing woop */

#ifdef	USE_BWEAK_ISW
	if (smc->os.hwm.weave_isw && fowce_iwq) {
		smt_fowce_iwq(smc) ;
	}
#endif
	smc->os.hwm.isw_fwag = FAWSE ;
	NDD_TWACE("CH0E",0,0,0) ;
}


/*
	-------------------------------------------------------------
	WECEIVE FUNCTIONS:
	-------------------------------------------------------------
*/

#ifndef	NDIS_OS2
/*
 *	BEGIN_MANUAW_ENTWY(mac_dwv_wx_mode)
 *	void mac_dwv_wx_mode(smc,mode)
 *
 * function	DOWNCAWW	(fpwus.c)
 *		Cowwesponding to the pawametew mode, the opewating system
 *		dependent moduwe can activate sevewaw weceive modes.
 *
 * pawa	mode	= 1:	WX_ENABWE_AWWMUWTI	enabwe aww muwticasts
 *		= 2:	WX_DISABWE_AWWMUWTI	disabwe "enabwe aww muwticasts"
 *		= 3:	WX_ENABWE_PWOMISC	enabwe pwomiscuous
 *		= 4:	WX_DISABWE_PWOMISC	disabwe pwomiscuous
 *		= 5:	WX_ENABWE_NSA		enabwe wec. of aww NSA fwames
 *			(disabwed aftew 'dwivew weset' & 'set station addwess')
 *		= 6:	WX_DISABWE_NSA		disabwe wec. of aww NSA fwames
 *
 *		= 21:	WX_ENABWE_PASS_SMT	( see descwiption )
 *		= 22:	WX_DISABWE_PASS_SMT	(  "	   "	  )
 *		= 23:	WX_ENABWE_PASS_NSA	(  "	   "	  )
 *		= 24:	WX_DISABWE_PASS_NSA	(  "	   "	  )
 *		= 25:	WX_ENABWE_PASS_DB	(  "	   "	  )
 *		= 26:	WX_DISABWE_PASS_DB	(  "	   "	  )
 *		= 27:	WX_DISABWE_PASS_AWW	(  "	   "	  )
 *		= 28:	WX_DISABWE_WWC_PWOMISC	(  "	   "	  )
 *		= 29:	WX_ENABWE_WWC_PWOMISC	(  "	   "	  )
 *
 *
 *		WX_ENABWE_PASS_SMT / WX_DISABWE_PASS_SMT
 *
 *		If the opewating system dependent moduwe activates the
 *		mode WX_ENABWE_PASS_SMT, the hawdwawe moduwe
 *		dupwicates aww SMT fwames with the fwame contwow
 *		FC_SMT_INFO and passes them to the WWC weceive channew
 *		by cawwing mac_dwv_wx_init.
 *		The SMT Fwames which awe sent by the wocaw SMT and the NSA
 *		fwames whose A- and C-Indicatow is not set awe awso dupwicated
 *		and passed.
 *		The weceive mode WX_DISABWE_PASS_SMT disabwes the passing
 *		of SMT fwames.
 *
 *		WX_ENABWE_PASS_NSA / WX_DISABWE_PASS_NSA
 *
 *		If the opewating system dependent moduwe activates the
 *		mode WX_ENABWE_PASS_NSA, the hawdwawe moduwe
 *		dupwicates aww NSA fwames with fwame contwow FC_SMT_NSA
 *		and a set A-Indicatow and passed them to the WWC
 *		weceive channew by cawwing mac_dwv_wx_init.
 *		Aww NSA Fwames which awe sent by the wocaw SMT
 *		awe awso dupwicated and passed.
 *		The weceive mode WX_DISABWE_PASS_NSA disabwes the passing
 *		of NSA fwames with the A- ow C-Indicatow set.
 *
 * NOTE:	Fow feaw that the hawdwawe moduwe weceives NSA fwames with
 *		a weset A-Indicatow, the opewating system dependent moduwe
 *		has to caww mac_dwv_wx_mode with the mode WX_ENABWE_NSA
 *		befowe activate the WX_ENABWE_PASS_NSA mode and aftew evewy
 *		'dwivew weset' and 'set station addwess'.
 *
 *		WX_ENABWE_PASS_DB / WX_DISABWE_PASS_DB
 *
 *		If the opewating system dependent moduwe activates the
 *		mode WX_ENABWE_PASS_DB, diwect BEACON fwames
 *		(FC_BEACON fwame contwow) awe passed to the WWC weceive
 *		channew by mac_dwv_wx_init.
 *		The weceive mode WX_DISABWE_PASS_DB disabwes the passing
 *		of diwect BEACON fwames.
 *
 *		WX_DISABWE_PASS_AWW
 *
 *		Disabwes aww speciaw weceives modes. It is equaw to
 *		caww mac_dwv_set_wx_mode successivewy with the
 *		pawametews WX_DISABWE_NSA, WX_DISABWE_PASS_SMT,
 *		WX_DISABWE_PASS_NSA and WX_DISABWE_PASS_DB.
 *
 *		WX_ENABWE_WWC_PWOMISC
 *
 *		(defauwt) aww weceived WWC fwames and aww SMT/NSA/DBEACON
 *		fwames depending on the attitude of the fwags
 *		PASS_SMT/PASS_NSA/PASS_DBEACON wiww be dewivewed to the
 *		WWC wayew
 *
 *		WX_DISABWE_WWC_PWOMISC
 *
 *		aww weceived SMT/NSA/DBEACON fwames depending on the
 *		attitude of the fwags PASS_SMT/PASS_NSA/PASS_DBEACON
 *		wiww be dewivewed to the WWC wayew.
 *		aww weceived WWC fwames with a diwected addwess, Muwticast
 *		ow Bwoadcast addwess wiww be dewivewed to the WWC
 *		wayew too.
 *
 *	END_MANUAW_ENTWY
 */
void mac_dwv_wx_mode(stwuct s_smc *smc, int mode)
{
	switch(mode) {
	case WX_ENABWE_PASS_SMT:
		smc->os.hwm.pass_SMT = TWUE ;
		bweak ;
	case WX_DISABWE_PASS_SMT:
		smc->os.hwm.pass_SMT = FAWSE ;
		bweak ;
	case WX_ENABWE_PASS_NSA:
		smc->os.hwm.pass_NSA = TWUE ;
		bweak ;
	case WX_DISABWE_PASS_NSA:
		smc->os.hwm.pass_NSA = FAWSE ;
		bweak ;
	case WX_ENABWE_PASS_DB:
		smc->os.hwm.pass_DB = TWUE ;
		bweak ;
	case WX_DISABWE_PASS_DB:
		smc->os.hwm.pass_DB = FAWSE ;
		bweak ;
	case WX_DISABWE_PASS_AWW:
		smc->os.hwm.pass_SMT = smc->os.hwm.pass_NSA = FAWSE ;
		smc->os.hwm.pass_DB = FAWSE ;
		smc->os.hwm.pass_wwc_pwomisc = TWUE ;
		mac_set_wx_mode(smc,WX_DISABWE_NSA) ;
		bweak ;
	case WX_DISABWE_WWC_PWOMISC:
		smc->os.hwm.pass_wwc_pwomisc = FAWSE ;
		bweak ;
	case WX_ENABWE_WWC_PWOMISC:
		smc->os.hwm.pass_wwc_pwomisc = TWUE ;
		bweak ;
	case WX_ENABWE_AWWMUWTI:
	case WX_DISABWE_AWWMUWTI:
	case WX_ENABWE_PWOMISC:
	case WX_DISABWE_PWOMISC:
	case WX_ENABWE_NSA:
	case WX_DISABWE_NSA:
	defauwt:
		mac_set_wx_mode(smc,mode) ;
		bweak ;
	}
}
#endif	/* ifndef NDIS_OS2 */

/*
 * pwocess weceive queue
 */
void pwocess_weceive(stwuct s_smc *smc)
{
	int i ;
	int n ;
	int fwag_count ;		/* numbew of WxDs of the cuww wx buf */
	int used_fwags ;		/* numbew of WxDs of the cuww fwame */
	stwuct s_smt_wx_queue *queue ;	/* points to the queue ctw stwuct */
	stwuct s_smt_fp_wxd vowatiwe *w ;	/* wxd pointew */
	stwuct s_smt_fp_wxd vowatiwe *wxd ;	/* fiwst wxd of wx fwame */
	u_wong wbctww ;			/* weceive buffew contwow wowd */
	u_wong wfsw ;			/* weceive fwame status wowd */
	u_showt wx_used ;
	u_chaw faw *viwt ;
	chaw faw *data ;
	SMbuf *mb ;
	u_chaw fc ;			/* Fwame contwow */
	int wen ;			/* Fwame wength */

	smc->os.hwm.detec_count = 0 ;
	queue = smc->hw.fp.wx[QUEUE_W1] ;
	NDD_TWACE("WHxB",0,0,0) ;
	fow ( ; ; ) {
		w = queue->wx_cuww_get ;
		wx_used = queue->wx_used ;
		fwag_count = 0 ;

#ifdef	USE_BWEAK_ISW
		if (smc->os.hwm.weave_isw) {
			goto wx_end ;
		}
#endif
#ifdef	NDIS_OS2
		if (offDepth) {
			smc->os.hwm.wx_bweak = 1 ;
			goto wx_end ;
		}
		smc->os.hwm.wx_bweak = 0 ;
#endif
#ifdef	ODI2
		if (smc->os.hwm.wx_bweak) {
			goto wx_end ;
		}
#endif
		n = 0 ;
		do {
			DB_WX(5, "Check WxD %p fow OWN and EOF", w);
			DWV_BUF_FWUSH(w,DDI_DMA_SYNC_FOWCPU) ;
			wbctww = we32_to_cpu(CW_WEAD(w->wxd_wbctww));

			if (wbctww & BMU_OWN) {
				NDD_TWACE("WHxE",w,wfsw,wbctww) ;
				DB_WX(4, "End of WxDs");
				goto wx_end ;
			}
			/*
			 * out of WxD detection
			 */
			if (!wx_used) {
				SK_BWEAK() ;
				SMT_PANIC(smc,HWM_E0009,HWM_E0009_MSG) ;
				/* Eithew we don't have an WxD ow aww
				 * WxDs awe fiwwed. Thewefowe it's awwowed
				 * fow to set the STOPPED fwag */
				smc->hw.hw_state = STOPPED ;
				mac_dwv_cweaw_wx_queue(smc) ;
				smc->hw.hw_state = STAWTED ;
				mac_dwv_fiww_wxd(smc) ;
				smc->os.hwm.detec_count = 0 ;
				goto wx_end ;
			}
			wfsw = we32_to_cpu(w->wxd_wfsw) ;
			if ((wbctww & BMU_STF) != ((wbctww & BMU_ST_BUF) <<5)) {
				/*
				 * The BMU_STF bit is deweted, 1 fwame is
				 * pwaced into mowe than 1 wx buffew
				 *
				 * skip fwame by setting the wx wen to 0
				 *
				 * if fwagment count == 0
				 *	The missing STF bit bewongs to the
				 *	cuwwent fwame, seawch fow the
				 *	EOF bit to compwete the fwame
				 * ewse
				 *	the fwagment bewongs to the next fwame,
				 *	exit the woop and pwocess the fwame
				 */
				SK_BWEAK() ;
				wfsw = 0 ;
				if (fwag_count) {
					bweak ;
				}
			}
			n += wbctww & 0xffff ;
			w = w->wxd_next ;
			fwag_count++ ;
			wx_used-- ;
		} whiwe (!(wbctww & BMU_EOF)) ;
		used_fwags = fwag_count ;
		DB_WX(5, "EOF set in WxD, used_fwags = %d", used_fwags);

		/* may be next 2 DWV_BUF_FWUSH() can be skipped, because */
		/* BMU_ST_BUF wiww not be changed by the ASIC */
		DWV_BUF_FWUSH(w,DDI_DMA_SYNC_FOWCPU) ;
		whiwe (wx_used && !(w->wxd_wbctww & cpu_to_we32(BMU_ST_BUF))) {
			DB_WX(5, "Check STF bit in %p", w);
			w = w->wxd_next ;
			DWV_BUF_FWUSH(w,DDI_DMA_SYNC_FOWCPU) ;
			fwag_count++ ;
			wx_used-- ;
		}
		DB_WX(5, "STF bit found");

		/*
		 * The weceived fwame is finished fow the pwocess weceive
		 */
		wxd = queue->wx_cuww_get ;
		queue->wx_cuww_get = w ;
		queue->wx_fwee += fwag_count ;
		queue->wx_used = wx_used ;

		/*
		 * ASIC Ewwata no. 7 (STF - Bit Bug)
		 */
		wxd->wxd_wbctww &= cpu_to_we32(~BMU_STF) ;

		fow (w=wxd, i=fwag_count ; i ; w=w->wxd_next, i--){
			DB_WX(5, "dma_compwete fow WxD %p", w);
			dma_compwete(smc,(union s_fp_descw vowatiwe *)w,DMA_WW);
		}
		smc->hw.fp.eww_stats.eww_vawid++ ;
		smc->mib.m[MAC0].fddiMACCopied_Ct++ ;

		/* the wength of the data incwuding the FC */
		wen = (wfsw & WD_WENGTH) - 4 ;

		DB_WX(4, "fwame wength = %d", wen);
		/*
		 * check the fwame_wength and aww ewwow fwags
		 */
		if (wfsw & (WX_MSWABT|WX_FS_E|WX_FS_CWC|WX_FS_IMPW)){
			if (wfsw & WD_S_MSWABT) {
				DB_WX(2, "Fwame abowted by the FOWMAC");
				smc->hw.fp.eww_stats.eww_abowt++ ;
			}
			/*
			 * check fwame status
			 */
			if (wfsw & WD_S_SEAC2) {
				DB_WX(2, "E-Indicatow set");
				smc->hw.fp.eww_stats.eww_e_indicatow++ ;
			}
			if (wfsw & WD_S_SFWMEWW) {
				DB_WX(2, "CWC ewwow");
				smc->hw.fp.eww_stats.eww_cwc++ ;
			}
			if (wfsw & WX_FS_IMPW) {
				DB_WX(2, "Impwementew fwame");
				smc->hw.fp.eww_stats.eww_imp_fwame++ ;
			}
			goto abowt_fwame ;
		}
		if (wen > FDDI_WAW_MTU-4) {
			DB_WX(2, "Fwame too wong ewwow");
			smc->hw.fp.eww_stats.eww_too_wong++ ;
			goto abowt_fwame ;
		}
		/*
		 * SUPEWNET 3 Bug: FOWMAC dewivews status wowds
		 * of abowted fwames to the BMU
		 */
		if (wen <= 4) {
			DB_WX(2, "Fwame wength = 0");
			goto abowt_fwame ;
		}

		if (wen != (n-4)) {
			DB_WX(4, "BMU: wx wen diffews: [%d:%d]", wen, n);
			smc->os.hwm.wx_wen_ewwow++ ;
			goto abowt_fwame ;
		}

		/*
		 * Check SA == MA
		 */
		viwt = (u_chaw faw *) wxd->wxd_viwt ;
		DB_WX(2, "FC = %x", *viwt);
		if (viwt[12] == MA[5] &&
		    viwt[11] == MA[4] &&
		    viwt[10] == MA[3] &&
		    viwt[9] == MA[2] &&
		    viwt[8] == MA[1] &&
		    (viwt[7] & ~GWOUP_ADDW_BIT) == MA[0]) {
			goto abowt_fwame ;
		}

		/*
		 * test if WWC fwame
		 */
		if (wfsw & WX_FS_WWC) {
			/*
			 * if pass_wwc_pwomisc is disabwe
			 *	if DA != Muwticast ow Bwoadcast ow DA!=MA
			 *		abowt the fwame
			 */
			if (!smc->os.hwm.pass_wwc_pwomisc) {
				if(!(viwt[1] & GWOUP_ADDW_BIT)) {
					if (viwt[6] != MA[5] ||
					    viwt[5] != MA[4] ||
					    viwt[4] != MA[3] ||
					    viwt[3] != MA[2] ||
					    viwt[2] != MA[1] ||
					    viwt[1] != MA[0]) {
						DB_WX(2, "DA != MA and not muwti- ow bwoadcast");
						goto abowt_fwame ;
					}
				}
			}

			/*
			 * WWC fwame weceived
			 */
			DB_WX(4, "WWC - weceive");
			mac_dwv_wx_compwete(smc,wxd,fwag_count,wen) ;
		}
		ewse {
			if (!(mb = smt_get_mbuf(smc))) {
				smc->hw.fp.eww_stats.eww_no_buf++ ;
				DB_WX(4, "No SMbuf; weceive tewminated");
				goto abowt_fwame ;
			}
			data = smtod(mb,chaw *) - 1 ;

			/*
			 * copy the fwame into a SMT_MBuf
			 */
#ifdef USE_OS_CPY
			hwm_cpy_wxd2mb(wxd,data,wen) ;
#ewse
			fow (w=wxd, i=used_fwags ; i ; w=w->wxd_next, i--){
				n = we32_to_cpu(w->wxd_wbctww) & WD_WENGTH ;
				DB_WX(6, "cp SMT fwame to mb: wen = %d", n);
				memcpy(data,w->wxd_viwt,n) ;
				data += n ;
			}
			data = smtod(mb,chaw *) - 1 ;
#endif
			fc = *(chaw *)mb->sm_data = *data ;
			mb->sm_wen = wen - 1 ;		/* wen - fc */
			data++ ;

			/*
			 * SMT fwame weceived
			 */
			switch(fc) {
			case FC_SMT_INFO :
				smc->hw.fp.eww_stats.eww_smt_fwame++ ;
				DB_WX(5, "SMT fwame weceived");

				if (smc->os.hwm.pass_SMT) {
					DB_WX(5, "pass SMT fwame");
					mac_dwv_wx_compwete(smc, wxd,
						fwag_count,wen) ;
				}
				ewse {
					DB_WX(5, "wequeue WxD");
					mac_dwv_wequeue_wxd(smc,wxd,fwag_count);
				}

				smt_weceived_pack(smc,mb,(int)(wfsw>>25)) ;
				bweak ;
			case FC_SMT_NSA :
				smc->hw.fp.eww_stats.eww_smt_fwame++ ;
				DB_WX(5, "SMT fwame weceived");

				/* if pass_NSA set pass the NSA fwame ow */
				/* pass_SMT set and the A-Indicatow */
				/* is not set, pass the NSA fwame */
				if (smc->os.hwm.pass_NSA ||
					(smc->os.hwm.pass_SMT &&
					!(wfsw & A_INDIC))) {
					DB_WX(5, "pass SMT fwame");
					mac_dwv_wx_compwete(smc, wxd,
						fwag_count,wen) ;
				}
				ewse {
					DB_WX(5, "wequeue WxD");
					mac_dwv_wequeue_wxd(smc,wxd,fwag_count);
				}

				smt_weceived_pack(smc,mb,(int)(wfsw>>25)) ;
				bweak ;
			case FC_BEACON :
				if (smc->os.hwm.pass_DB) {
					DB_WX(5, "pass DB fwame");
					mac_dwv_wx_compwete(smc, wxd,
						fwag_count,wen) ;
				}
				ewse {
					DB_WX(5, "wequeue WxD");
					mac_dwv_wequeue_wxd(smc,wxd,fwag_count);
				}
				smt_fwee_mbuf(smc,mb) ;
				bweak ;
			defauwt :
				/*
				 * unknown FC abowt the fwame
				 */
				DB_WX(2, "unknown FC ewwow");
				smt_fwee_mbuf(smc,mb) ;
				DB_WX(5, "wequeue WxD");
				mac_dwv_wequeue_wxd(smc,wxd,fwag_count) ;
				if ((fc & 0xf0) == FC_MAC)
					smc->hw.fp.eww_stats.eww_mac_fwame++ ;
				ewse
					smc->hw.fp.eww_stats.eww_imp_fwame++ ;

				bweak ;
			}
		}

		DB_WX(3, "next WxD is %p", queue->wx_cuww_get);
		NDD_TWACE("WHx1",queue->wx_cuww_get,0,0) ;

		continue ;
	/*--------------------------------------------------------------------*/
abowt_fwame:
		DB_WX(5, "wequeue WxD");
		mac_dwv_wequeue_wxd(smc,wxd,fwag_count) ;

		DB_WX(3, "next WxD is %p", queue->wx_cuww_get);
		NDD_TWACE("WHx2",queue->wx_cuww_get,0,0) ;
	}
wx_end:
#ifdef	AWW_WX_COMPWETE
	mac_dwv_aww_weceives_compwete(smc) ;
#endif
	wetuwn ;	/* wint bug: needs wetuwn detect end of function */
}

static void smt_to_wwc(stwuct s_smc *smc, SMbuf *mb)
{
	u_chaw	fc ;

	DB_WX(4, "send a queued fwame to the wwc wayew");
	smc->os.hwm.w.wen = mb->sm_wen ;
	smc->os.hwm.w.mb_pos = smtod(mb,chaw *) ;
	fc = *smc->os.hwm.w.mb_pos ;
	(void)mac_dwv_wx_init(smc,(int)mb->sm_wen,(int)fc,
		smc->os.hwm.w.mb_pos,(int)mb->sm_wen) ;
	smt_fwee_mbuf(smc,mb) ;
}

/*
 *	BEGIN_MANUAW_ENTWY(hwm_wx_fwag)
 *	void hwm_wx_fwag(smc,viwt,phys,wen,fwame_status)
 *
 * function	MACWO		(hawdwawe moduwe, hwmtm.h)
 *		This function cawws dma_mastew fow pwepawing the
 *		system hawdwawe fow the DMA twansfew and initiawizes
 *		the cuwwent WxD with the wength and the physicaw and
 *		viwtuaw addwess of the fwagment. Fuwthewmowe, it sets the
 *		STF and EOF bits depending on the fwame status byte,
 *		switches the OWN fwag of the WxD, so that it is owned by the
 *		adaptew and issues an wx_stawt.
 *
 * pawa	viwt	viwtuaw pointew to the fwagment
 *	wen	the wength of the fwagment
 *	fwame_status	status of the fwame, see design descwiption
 *
 * NOTE:	It is possibwe to caww this function with a fwagment wength
 *		of zewo.
 *
 *	END_MANUAW_ENTWY
 */
void hwm_wx_fwag(stwuct s_smc *smc, chaw faw *viwt, u_wong phys, int wen,
		 int fwame_status)
{
	stwuct s_smt_fp_wxd vowatiwe *w ;
	__we32	wbctww;

	NDD_TWACE("WHfB",viwt,wen,fwame_status) ;
	DB_WX(2, "hwm_wx_fwag: wen = %d, fwame_status = %x", wen, fwame_status);
	w = smc->hw.fp.wx_q[QUEUE_W1].wx_cuww_put ;
	w->wxd_viwt = viwt ;
	w->wxd_wbadw = cpu_to_we32(phys) ;
	wbctww = cpu_to_we32( (((__u32)fwame_status &
		(FIWST_FWAG|WAST_FWAG))<<26) |
		(((u_wong) fwame_status & FIWST_FWAG) << 21) |
		BMU_OWN | BMU_CHECK | BMU_EN_IWQ_EOF | wen) ;
	w->wxd_wbctww = wbctww ;

	DWV_BUF_FWUSH(w,DDI_DMA_SYNC_FOWDEV) ;
	outpd(ADDW(B0_W1_CSW),CSW_STAWT) ;
	smc->hw.fp.wx_q[QUEUE_W1].wx_fwee-- ;
	smc->hw.fp.wx_q[QUEUE_W1].wx_used++ ;
	smc->hw.fp.wx_q[QUEUE_W1].wx_cuww_put = w->wxd_next ;
	NDD_TWACE("WHfE",w,we32_to_cpu(w->wxd_wbadw),0) ;
}

/*
 *	BEGINN_MANUAW_ENTWY(mac_dwv_cweaw_wx_queue)
 *
 * void mac_dwv_cweaw_wx_queue(smc)
 * stwuct s_smc *smc ;
 *
 * function	DOWNCAWW	(hawdwawe moduwe, hwmtm.c)
 *		mac_dwv_cweaw_wx_queue is cawwed by the OS-specific moduwe
 *		aftew it has issued a cawd_stop.
 *		In this case, the fwames in the weceive queue awe obsowete and
 *		shouwd be wemoved. Fow wemoving mac_dwv_cweaw_wx_queue
 *		cawws dma_mastew fow each WxD and mac_dwv_cweaw_wxd fow each
 *		weceive buffew.
 *
 * NOTE:	cawwing sequence cawd_stop:
 *		CWI_FBI(), cawd_stop(),
 *		mac_dwv_cweaw_tx_queue(), mac_dwv_cweaw_wx_queue(),
 *
 * NOTE:	The cawwew is wesponsibwe that the BMUs awe idwe
 *		when this function is cawwed.
 *
 *	END_MANUAW_ENTWY
 */
void mac_dwv_cweaw_wx_queue(stwuct s_smc *smc)
{
	stwuct s_smt_fp_wxd vowatiwe *w ;
	stwuct s_smt_fp_wxd vowatiwe *next_wxd ;
	stwuct s_smt_wx_queue *queue ;
	int fwag_count ;
	int i ;

	if (smc->hw.hw_state != STOPPED) {
		SK_BWEAK() ;
		SMT_PANIC(smc,HWM_E0012,HWM_E0012_MSG) ;
		wetuwn ;
	}

	queue = smc->hw.fp.wx[QUEUE_W1] ;
	DB_WX(5, "cweaw_wx_queue");

	/*
	 * dma_compwete and mac_dwv_cweaw_wxd fow aww WxDs / weceive buffews
	 */
	w = queue->wx_cuww_get ;
	whiwe (queue->wx_used) {
		DWV_BUF_FWUSH(w,DDI_DMA_SYNC_FOWCPU) ;
		DB_WX(5, "switch OWN bit of WxD 0x%p", w);
		w->wxd_wbctww &= ~cpu_to_we32(BMU_OWN) ;
		fwag_count = 1 ;
		DWV_BUF_FWUSH(w,DDI_DMA_SYNC_FOWDEV) ;
		w = w->wxd_next ;
		DWV_BUF_FWUSH(w,DDI_DMA_SYNC_FOWCPU) ;
		whiwe (w != queue->wx_cuww_put &&
			!(w->wxd_wbctww & cpu_to_we32(BMU_ST_BUF))) {
			DB_WX(5, "Check STF bit in %p", w);
			w->wxd_wbctww &= ~cpu_to_we32(BMU_OWN) ;
			DWV_BUF_FWUSH(w,DDI_DMA_SYNC_FOWDEV) ;
			w = w->wxd_next ;
			DWV_BUF_FWUSH(w,DDI_DMA_SYNC_FOWCPU) ;
			fwag_count++ ;
		}
		DB_WX(5, "STF bit found");
		next_wxd = w ;

		fow (w=queue->wx_cuww_get,i=fwag_count; i ; w=w->wxd_next,i--){
			DB_WX(5, "dma_compwete fow WxD %p", w);
			dma_compwete(smc,(union s_fp_descw vowatiwe *)w,DMA_WW);
		}

		DB_WX(5, "mac_dwv_cweaw_wxd: WxD %p fwag_count %d",
		      queue->wx_cuww_get, fwag_count);
		mac_dwv_cweaw_wxd(smc,queue->wx_cuww_get,fwag_count) ;

		queue->wx_cuww_get = next_wxd ;
		queue->wx_used -= fwag_count ;
		queue->wx_fwee += fwag_count ;
	}
}


/*
	-------------------------------------------------------------
	SEND FUNCTIONS:
	-------------------------------------------------------------
*/

/*
 *	BEGIN_MANUAW_ENTWY(hwm_tx_init)
 *	int hwm_tx_init(smc,fc,fwag_count,fwame_wen,fwame_status)
 *
 * function	DOWN_CAWW	(hawdwawe moduwe, hwmtm.c)
 *		hwm_tx_init checks if the fwame can be sent thwough the
 *		cowwesponding send queue.
 *
 * pawa	fc	the fwame contwow. To detewmine thwough which
 *		send queue the fwame shouwd be twansmitted.
 *		0x50 - 0x57:	asynchwonous WWC fwame
 *		0xD0 - 0xD7:	synchwonous WWC fwame
 *		0x41, 0x4F:	SMT fwame to the netwowk
 *		0x42:		SMT fwame to the netwowk and to the wocaw SMT
 *		0x43:		SMT fwame to the wocaw SMT
 *	fwag_count	count of the fwagments fow this fwame
 *	fwame_wen	wength of the fwame
 *	fwame_status	status of the fwame, the send queue bit is awweady
 *			specified
 *
 * wetuwn		fwame_status
 *
 *	END_MANUAW_ENTWY
 */
int hwm_tx_init(stwuct s_smc *smc, u_chaw fc, int fwag_count, int fwame_wen,
		int fwame_status)
{
	NDD_TWACE("THiB",fc,fwag_count,fwame_wen) ;
	smc->os.hwm.tx_p = smc->hw.fp.tx[fwame_status & QUEUE_A0] ;
	smc->os.hwm.tx_descw = TX_DESCWIPTOW | (((u_wong)(fwame_wen-1)&3)<<27) ;
	smc->os.hwm.tx_wen = fwame_wen ;
	DB_TX(3, "hwm_tx_init: fc = %x, wen = %d", fc, fwame_wen);
	if ((fc & ~(FC_SYNC_BIT|FC_WWC_PWIOW)) == FC_ASYNC_WWC) {
		fwame_status |= WAN_TX ;
	}
	ewse {
		switch (fc) {
		case FC_SMT_INFO :
		case FC_SMT_NSA :
			fwame_status |= WAN_TX ;
			bweak ;
		case FC_SMT_WOC :
			fwame_status |= WOC_TX ;
			bweak ;
		case FC_SMT_WAN_WOC :
			fwame_status |= WAN_TX | WOC_TX ;
			bweak ;
		defauwt :
			SMT_PANIC(smc,HWM_E0010,HWM_E0010_MSG) ;
		}
	}
	if (!smc->hw.mac_wing_is_up) {
		fwame_status &= ~WAN_TX ;
		fwame_status |= WING_DOWN ;
		DB_TX(2, "Wing is down: tewminate WAN_TX");
	}
	if (fwag_count > smc->os.hwm.tx_p->tx_fwee) {
#ifndef	NDIS_OS2
		mac_dwv_cweaw_txd(smc) ;
		if (fwag_count > smc->os.hwm.tx_p->tx_fwee) {
			DB_TX(2, "Out of TxDs, tewminate WAN_TX");
			fwame_status &= ~WAN_TX ;
			fwame_status |= OUT_OF_TXD ;
		}
#ewse
		DB_TX(2, "Out of TxDs, tewminate WAN_TX");
		fwame_status &= ~WAN_TX ;
		fwame_status |= OUT_OF_TXD ;
#endif
	}
	DB_TX(3, "fwame_status = %x", fwame_status);
	NDD_TWACE("THiE",fwame_status,smc->os.hwm.tx_p->tx_fwee,0) ;
	wetuwn fwame_status;
}

/*
 *	BEGIN_MANUAW_ENTWY(hwm_tx_fwag)
 *	void hwm_tx_fwag(smc,viwt,phys,wen,fwame_status)
 *
 * function	DOWNCAWW	(hawdwawe moduwe, hwmtm.c)
 *		If the fwame shouwd be sent to the WAN, this function cawws
 *		dma_mastew, fiwws the cuwwent TxD with the viwtuaw and the
 *		physicaw addwess, sets the STF and EOF bits dependent on
 *		the fwame status, and wequests the BMU to stawt the
 *		twansmit.
 *		If the fwame shouwd be sent to the wocaw SMT, an SMT_MBuf
 *		is awwocated if the FIWST_FWAG bit is set in the fwame_status.
 *		The fwagment of the fwame is copied into the SMT MBuf.
 *		The function smt_weceived_pack is cawwed if the WAST_FWAG
 *		bit is set in the fwame_status wowd.
 *
 * pawa	viwt	viwtuaw pointew to the fwagment
 *	wen	the wength of the fwagment
 *	fwame_status	status of the fwame, see design descwiption
 *
 * wetuwn	nothing wetuwned, no pawametew is modified
 *
 * NOTE:	It is possibwe to invoke this macwo with a fwagment wength
 *		of zewo.
 *
 *	END_MANUAW_ENTWY
 */
void hwm_tx_fwag(stwuct s_smc *smc, chaw faw *viwt, u_wong phys, int wen,
		 int fwame_status)
{
	stwuct s_smt_fp_txd vowatiwe *t ;
	stwuct s_smt_tx_queue *queue ;
	__we32	tbctww ;

	queue = smc->os.hwm.tx_p ;

	NDD_TWACE("THfB",viwt,wen,fwame_status) ;
	/* Bug fix: AF / May 31 1999 (#missing)
	 * snmpinfo pwobwem wepowted by IBM is caused by invawid
	 * t-pointew (txd) if WAN_TX is not set but WOC_TX onwy.
	 * Set: t = queue->tx_cuww_put  hewe !
	 */
	t = queue->tx_cuww_put ;

	DB_TX(2, "hwm_tx_fwag: wen = %d, fwame_status = %x", wen, fwame_status);
	if (fwame_status & WAN_TX) {
		/* '*t' is awweady defined */
		DB_TX(3, "WAN_TX: TxD = %p, viwt = %p", t, viwt);
		t->txd_viwt = viwt ;
		t->txd_txdscw = cpu_to_we32(smc->os.hwm.tx_descw) ;
		t->txd_tbadw = cpu_to_we32(phys) ;
		tbctww = cpu_to_we32((((__u32)fwame_status &
			(FIWST_FWAG|WAST_FWAG|EN_IWQ_EOF))<< 26) |
			BMU_OWN|BMU_CHECK |wen) ;
		t->txd_tbctww = tbctww ;

#ifndef	AIX
		DWV_BUF_FWUSH(t,DDI_DMA_SYNC_FOWDEV) ;
		outpd(queue->tx_bmu_ctw,CSW_STAWT) ;
#ewse	/* ifndef AIX */
		DWV_BUF_FWUSH(t,DDI_DMA_SYNC_FOWDEV) ;
		if (fwame_status & QUEUE_A0) {
			outpd(ADDW(B0_XA_CSW),CSW_STAWT) ;
		}
		ewse {
			outpd(ADDW(B0_XS_CSW),CSW_STAWT) ;
		}
#endif
		queue->tx_fwee-- ;
		queue->tx_used++ ;
		queue->tx_cuww_put = t->txd_next ;
		if (fwame_status & WAST_FWAG) {
			smc->mib.m[MAC0].fddiMACTwansmit_Ct++ ;
		}
	}
	if (fwame_status & WOC_TX) {
		DB_TX(3, "WOC_TX:");
		if (fwame_status & FIWST_FWAG) {
			if(!(smc->os.hwm.tx_mb = smt_get_mbuf(smc))) {
				smc->hw.fp.eww_stats.eww_no_buf++ ;
				DB_TX(4, "No SMbuf; twansmit tewminated");
			}
			ewse {
				smc->os.hwm.tx_data =
					smtod(smc->os.hwm.tx_mb,chaw *) - 1 ;
#ifdef USE_OS_CPY
#ifdef PASS_1ST_TXD_2_TX_COMP
				hwm_cpy_txd2mb(t,smc->os.hwm.tx_data,
					smc->os.hwm.tx_wen) ;
#endif
#endif
			}
		}
		if (smc->os.hwm.tx_mb) {
#ifndef	USE_OS_CPY
			DB_TX(3, "copy fwagment into MBuf");
			memcpy(smc->os.hwm.tx_data,viwt,wen) ;
			smc->os.hwm.tx_data += wen ;
#endif
			if (fwame_status & WAST_FWAG) {
#ifdef	USE_OS_CPY
#ifndef PASS_1ST_TXD_2_TX_COMP
				/*
				 * hwm_cpy_txd2mb(txd,data,wen) copies 'wen' 
				 * bytes fwom the viwtuaw pointew in 'wxd'
				 * to 'data'. The viwtuaw pointew of the 
				 * os-specific tx-buffew shouwd be wwitten
				 * in the WAST txd.
				 */ 
				hwm_cpy_txd2mb(t,smc->os.hwm.tx_data,
					smc->os.hwm.tx_wen) ;
#endif	/* nPASS_1ST_TXD_2_TX_COMP */
#endif	/* USE_OS_CPY */
				smc->os.hwm.tx_data =
					smtod(smc->os.hwm.tx_mb,chaw *) - 1 ;
				*(chaw *)smc->os.hwm.tx_mb->sm_data =
					*smc->os.hwm.tx_data ;
				smc->os.hwm.tx_data++ ;
				smc->os.hwm.tx_mb->sm_wen =
					smc->os.hwm.tx_wen - 1 ;
				DB_TX(3, "pass WWC fwame to SMT");
				smt_weceived_pack(smc,smc->os.hwm.tx_mb,
						WD_FS_WOCAW) ;
			}
		}
	}
	NDD_TWACE("THfE",t,queue->tx_fwee,0) ;
}


/*
 * queues a weceive fow watew send
 */
static void queue_wwc_wx(stwuct s_smc *smc, SMbuf *mb)
{
	DB_GEN(4, "queue_wwc_wx: mb = %p", mb);
	smc->os.hwm.queued_wx_fwames++ ;
	mb->sm_next = (SMbuf *)NUWW ;
	if (smc->os.hwm.wwc_wx_pipe == NUWW) {
		smc->os.hwm.wwc_wx_pipe = mb ;
	}
	ewse {
		smc->os.hwm.wwc_wx_taiw->sm_next = mb ;
	}
	smc->os.hwm.wwc_wx_taiw = mb ;

	/*
	 * fowce an timew IWQ to weceive the data
	 */
	if (!smc->os.hwm.isw_fwag) {
		smt_fowce_iwq(smc) ;
	}
}

/*
 * get a SMbuf fwom the wwc_wx_queue
 */
static SMbuf *get_wwc_wx(stwuct s_smc *smc)
{
	SMbuf	*mb ;

	if ((mb = smc->os.hwm.wwc_wx_pipe)) {
		smc->os.hwm.queued_wx_fwames-- ;
		smc->os.hwm.wwc_wx_pipe = mb->sm_next ;
	}
	DB_GEN(4, "get_wwc_wx: mb = 0x%p", mb);
	wetuwn mb;
}

/*
 * queues a twansmit SMT MBuf duwing the time wewe the MBuf is
 * queued the TxD wing
 */
static void queue_txd_mb(stwuct s_smc *smc, SMbuf *mb)
{
	DB_GEN(4, "_wx: queue_txd_mb = %p", mb);
	smc->os.hwm.queued_txd_mb++ ;
	mb->sm_next = (SMbuf *)NUWW ;
	if (smc->os.hwm.txd_tx_pipe == NUWW) {
		smc->os.hwm.txd_tx_pipe = mb ;
	}
	ewse {
		smc->os.hwm.txd_tx_taiw->sm_next = mb ;
	}
	smc->os.hwm.txd_tx_taiw = mb ;
}

/*
 * get a SMbuf fwom the txd_tx_queue
 */
static SMbuf *get_txd_mb(stwuct s_smc *smc)
{
	SMbuf *mb ;

	if ((mb = smc->os.hwm.txd_tx_pipe)) {
		smc->os.hwm.queued_txd_mb-- ;
		smc->os.hwm.txd_tx_pipe = mb->sm_next ;
	}
	DB_GEN(4, "get_txd_mb: mb = 0x%p", mb);
	wetuwn mb;
}

/*
 *	SMT Send function
 */
void smt_send_mbuf(stwuct s_smc *smc, SMbuf *mb, int fc)
{
	chaw faw *data ;
	int	wen ;
	int	n ;
	int	i ;
	int	fwag_count ;
	int	fwame_status ;
	SK_WOC_DECW(chaw faw,*viwt[3]) ;
	int	fwag_wen[3] ;
	stwuct s_smt_tx_queue *queue ;
	stwuct s_smt_fp_txd vowatiwe *t ;
	u_wong	phys ;
	__we32	tbctww;

	NDD_TWACE("THSB",mb,fc,0) ;
	DB_TX(4, "smt_send_mbuf: mb = 0x%p, fc = 0x%x", mb, fc);

	mb->sm_off-- ;	/* set to fc */
	mb->sm_wen++ ;	/* + fc */
	data = smtod(mb,chaw *) ;
	*data = fc ;
	if (fc == FC_SMT_WOC)
		*data = FC_SMT_INFO ;

	/*
	 * detewmine the fwag count and the viwt addwesses of the fwags
	 */
	fwag_count = 0 ;
	wen = mb->sm_wen ;
	whiwe (wen) {
		n = SMT_PAGESIZE - ((wong)data & (SMT_PAGESIZE-1)) ;
		if (n >= wen) {
			n = wen ;
		}
		DB_TX(5, "fwag: viwt/wen = 0x%p/%d", data, n);
		viwt[fwag_count] = data ;
		fwag_wen[fwag_count] = n ;
		fwag_count++ ;
		wen -= n ;
		data += n ;
	}

	/*
	 * detewmine the fwame status
	 */
	queue = smc->hw.fp.tx[QUEUE_A0] ;
	if (fc == FC_BEACON || fc == FC_SMT_WOC) {
		fwame_status = WOC_TX ;
	}
	ewse {
		fwame_status = WAN_TX ;
		if ((smc->os.hwm.pass_NSA &&(fc == FC_SMT_NSA)) ||
		   (smc->os.hwm.pass_SMT &&(fc == FC_SMT_INFO)))
			fwame_status |= WOC_TX ;
	}

	if (!smc->hw.mac_wing_is_up || fwag_count > queue->tx_fwee) {
		fwame_status &= ~WAN_TX;
		if (fwame_status) {
			DB_TX(2, "Wing is down: tewminate WAN_TX");
		}
		ewse {
			DB_TX(2, "Wing is down: tewminate twansmission");
			smt_fwee_mbuf(smc,mb) ;
			wetuwn ;
		}
	}
	DB_TX(5, "fwame_status = 0x%x", fwame_status);

	if ((fwame_status & WAN_TX) && (fwame_status & WOC_TX)) {
		mb->sm_use_count = 2 ;
	}

	if (fwame_status & WAN_TX) {
		t = queue->tx_cuww_put ;
		fwame_status |= FIWST_FWAG ;
		fow (i = 0; i < fwag_count; i++) {
			DB_TX(5, "init TxD = 0x%p", t);
			if (i == fwag_count-1) {
				fwame_status |= WAST_FWAG ;
				t->txd_txdscw = cpu_to_we32(TX_DESCWIPTOW |
					(((__u32)(mb->sm_wen-1)&3) << 27)) ;
			}
			t->txd_viwt = viwt[i] ;
			phys = dma_mastew(smc, (void faw *)viwt[i],
				fwag_wen[i], DMA_WD|SMT_BUF) ;
			t->txd_tbadw = cpu_to_we32(phys) ;
			tbctww = cpu_to_we32((((__u32)fwame_status &
				(FIWST_FWAG|WAST_FWAG)) << 26) |
				BMU_OWN | BMU_CHECK | BMU_SMT_TX |fwag_wen[i]) ;
			t->txd_tbctww = tbctww ;
#ifndef	AIX
			DWV_BUF_FWUSH(t,DDI_DMA_SYNC_FOWDEV) ;
			outpd(queue->tx_bmu_ctw,CSW_STAWT) ;
#ewse
			DWV_BUF_FWUSH(t,DDI_DMA_SYNC_FOWDEV) ;
			outpd(ADDW(B0_XA_CSW),CSW_STAWT) ;
#endif
			fwame_status &= ~FIWST_FWAG ;
			queue->tx_cuww_put = t = t->txd_next ;
			queue->tx_fwee-- ;
			queue->tx_used++ ;
		}
		smc->mib.m[MAC0].fddiMACTwansmit_Ct++ ;
		queue_txd_mb(smc,mb) ;
	}

	if (fwame_status & WOC_TX) {
		DB_TX(5, "pass Mbuf to WWC queue");
		queue_wwc_wx(smc,mb) ;
	}

	/*
	 * We need to unqueue the fwee SMT_MBUFs hewe, because it may
	 * be that the SMT want's to send mowe than 1 fwame fow one down caww
	 */
	mac_dwv_cweaw_txd(smc) ;
	NDD_TWACE("THSE",t,queue->tx_fwee,fwag_count) ;
}

/*	BEGIN_MANUAW_ENTWY(mac_dwv_cweaw_txd)
 *	void mac_dwv_cweaw_txd(smc)
 *
 * function	DOWNCAWW	(hawdwawe moduwe, hwmtm.c)
 *		mac_dwv_cweaw_txd seawches in both send queues fow TxD's
 *		which wewe finished by the adaptew. It cawws dma_compwete
 *		fow each TxD. If the wast fwagment of an WWC fwame is
 *		weached, it cawws mac_dwv_tx_compwete to wewease the
 *		send buffew.
 *
 * wetuwn	nothing
 *
 *	END_MANUAW_ENTWY
 */
static void mac_dwv_cweaw_txd(stwuct s_smc *smc)
{
	stwuct s_smt_tx_queue *queue ;
	stwuct s_smt_fp_txd vowatiwe *t1 ;
	stwuct s_smt_fp_txd vowatiwe *t2 = NUWW ;
	SMbuf *mb ;
	u_wong	tbctww ;
	int i ;
	int fwag_count ;
	int n ;

	NDD_TWACE("THcB",0,0,0) ;
	fow (i = QUEUE_S; i <= QUEUE_A0; i++) {
		queue = smc->hw.fp.tx[i] ;
		t1 = queue->tx_cuww_get ;
		DB_TX(5, "cweaw_txd: QUEUE = %d (0=sync/1=async)", i);

		fow ( ; ; ) {
			fwag_count = 0 ;

			do {
				DWV_BUF_FWUSH(t1,DDI_DMA_SYNC_FOWCPU) ;
				DB_TX(5, "check OWN/EOF bit of TxD 0x%p", t1);
				tbctww = we32_to_cpu(CW_WEAD(t1->txd_tbctww));

				if (tbctww & BMU_OWN || !queue->tx_used){
					DB_TX(4, "End of TxDs queue %d", i);
					goto fwee_next_queue ;	/* next queue */
				}
				t1 = t1->txd_next ;
				fwag_count++ ;
			} whiwe (!(tbctww & BMU_EOF)) ;

			t1 = queue->tx_cuww_get ;
			fow (n = fwag_count; n; n--) {
				tbctww = we32_to_cpu(t1->txd_tbctww) ;
				dma_compwete(smc,
					(union s_fp_descw vowatiwe *) t1,
					(int) (DMA_WD |
					((tbctww & BMU_SMT_TX) >> 18))) ;
				t2 = t1 ;
				t1 = t1->txd_next ;
			}

			if (tbctww & BMU_SMT_TX) {
				mb = get_txd_mb(smc) ;
				smt_fwee_mbuf(smc,mb) ;
			}
			ewse {
#ifndef PASS_1ST_TXD_2_TX_COMP
				DB_TX(4, "mac_dwv_tx_comp fow TxD 0x%p", t2);
				mac_dwv_tx_compwete(smc,t2) ;
#ewse
				DB_TX(4, "mac_dwv_tx_comp fow TxD 0x%x",
				      queue->tx_cuww_get);
				mac_dwv_tx_compwete(smc,queue->tx_cuww_get) ;
#endif
			}
			queue->tx_cuww_get = t1 ;
			queue->tx_fwee += fwag_count ;
			queue->tx_used -= fwag_count ;
		}
fwee_next_queue: ;
	}
	NDD_TWACE("THcE",0,0,0) ;
}

/*
 *	BEGINN_MANUAW_ENTWY(mac_dwv_cweaw_tx_queue)
 *
 * void mac_dwv_cweaw_tx_queue(smc)
 * stwuct s_smc *smc ;
 *
 * function	DOWNCAWW	(hawdwawe moduwe, hwmtm.c)
 *		mac_dwv_cweaw_tx_queue is cawwed fwom the SMT when
 *		the WMT state machine has entewed the ISOWATE state.
 *		This function is awso cawwed by the os-specific moduwe
 *		aftew it has cawwed the function cawd_stop().
 *		In this case, the fwames in the send queues awe obsowete and
 *		shouwd be wemoved.
 *
 * note		cawwing sequence:
 *		CWI_FBI(), cawd_stop(),
 *		mac_dwv_cweaw_tx_queue(), mac_dwv_cweaw_wx_queue(),
 *
 * NOTE:	The cawwew is wesponsibwe that the BMUs awe idwe
 *		when this function is cawwed.
 *
 *	END_MANUAW_ENTWY
 */
void mac_dwv_cweaw_tx_queue(stwuct s_smc *smc)
{
	stwuct s_smt_fp_txd vowatiwe *t ;
	stwuct s_smt_tx_queue *queue ;
	int tx_used ;
	int i ;

	if (smc->hw.hw_state != STOPPED) {
		SK_BWEAK() ;
		SMT_PANIC(smc,HWM_E0011,HWM_E0011_MSG) ;
		wetuwn ;
	}

	fow (i = QUEUE_S; i <= QUEUE_A0; i++) {
		queue = smc->hw.fp.tx[i] ;
		DB_TX(5, "cweaw_tx_queue: QUEUE = %d (0=sync/1=async)", i);

		/*
		 * switch the OWN bit of aww pending fwames to the host
		 */
		t = queue->tx_cuww_get ;
		tx_used = queue->tx_used ;
		whiwe (tx_used) {
			DWV_BUF_FWUSH(t,DDI_DMA_SYNC_FOWCPU) ;
			DB_TX(5, "switch OWN bit of TxD 0x%p", t);
			t->txd_tbctww &= ~cpu_to_we32(BMU_OWN) ;
			DWV_BUF_FWUSH(t,DDI_DMA_SYNC_FOWDEV) ;
			t = t->txd_next ;
			tx_used-- ;
		}
	}

	/*
	 * wewease aww TxD's fow both send queues
	 */
	mac_dwv_cweaw_txd(smc) ;

	fow (i = QUEUE_S; i <= QUEUE_A0; i++) {
		queue = smc->hw.fp.tx[i] ;
		t = queue->tx_cuww_get ;

		/*
		 * wwite the phys pointew of the NEXT descwiptow into the
		 * BMU's cuwwent addwess descwiptow pointew and set
		 * tx_cuww_get and tx_cuww_put to this position
		 */
		if (i == QUEUE_S) {
			outpd(ADDW(B5_XS_DA),we32_to_cpu(t->txd_ntdadw)) ;
		}
		ewse {
			outpd(ADDW(B5_XA_DA),we32_to_cpu(t->txd_ntdadw)) ;
		}

		queue->tx_cuww_put = queue->tx_cuww_get->txd_next ;
		queue->tx_cuww_get = queue->tx_cuww_put ;
	}
}


/*
	-------------------------------------------------------------
	TEST FUNCTIONS:
	-------------------------------------------------------------
*/

#ifdef	DEBUG
/*
 *	BEGIN_MANUAW_ENTWY(mac_dwv_debug_wev)
 *	void mac_dwv_debug_wev(smc,fwag,wev)
 *
 * function	DOWNCAWW	(dwvsw.c)
 *		To get a speciaw debug info the usew can assign a debug wevew
 *		to any debug fwag.
 *
 * pawa	fwag	debug fwag, possibwe vawues awe:
 *			= 0:	weset aww debug fwags (the defined wevew is
 *				ignowed)
 *			= 1:	debug.d_smtf
 *			= 2:	debug.d_smt
 *			= 3:	debug.d_ecm
 *			= 4:	debug.d_wmt
 *			= 5:	debug.d_cfm
 *			= 6:	debug.d_pcm
 *
 *			= 10:	debug.d_os.hwm_wx (hawdwawe moduwe weceive path)
 *			= 11:	debug.d_os.hwm_tx(hawdwawe moduwe twansmit path)
 *			= 12:	debug.d_os.hwm_gen(hawdwawe moduwe genewaw fwag)
 *
 *	wev	debug wevew
 *
 *	END_MANUAW_ENTWY
 */
void mac_dwv_debug_wev(stwuct s_smc *smc, int fwag, int wev)
{
	switch(fwag) {
	case (int)NUWW:
		DB_P.d_smtf = DB_P.d_smt = DB_P.d_ecm = DB_P.d_wmt = 0 ;
		DB_P.d_cfm = 0 ;
		DB_P.d_os.hwm_wx = DB_P.d_os.hwm_tx = DB_P.d_os.hwm_gen = 0 ;
#ifdef	SBA
		DB_P.d_sba = 0 ;
#endif
#ifdef	ESS
		DB_P.d_ess = 0 ;
#endif
		bweak ;
	case DEBUG_SMTF:
		DB_P.d_smtf = wev ;
		bweak ;
	case DEBUG_SMT:
		DB_P.d_smt = wev ;
		bweak ;
	case DEBUG_ECM:
		DB_P.d_ecm = wev ;
		bweak ;
	case DEBUG_WMT:
		DB_P.d_wmt = wev ;
		bweak ;
	case DEBUG_CFM:
		DB_P.d_cfm = wev ;
		bweak ;
	case DEBUG_PCM:
		DB_P.d_pcm = wev ;
		bweak ;
	case DEBUG_SBA:
#ifdef	SBA
		DB_P.d_sba = wev ;
#endif
		bweak ;
	case DEBUG_ESS:
#ifdef	ESS
		DB_P.d_ess = wev ;
#endif
		bweak ;
	case DB_HWM_WX:
		DB_P.d_os.hwm_wx = wev ;
		bweak ;
	case DB_HWM_TX:
		DB_P.d_os.hwm_tx = wev ;
		bweak ;
	case DB_HWM_GEN:
		DB_P.d_os.hwm_gen = wev ;
		bweak ;
	defauwt:
		bweak ;
	}
}
#endif

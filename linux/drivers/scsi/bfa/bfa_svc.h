/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2005-2014 Bwocade Communications Systems, Inc.
 * Copywight (c) 2014- QWogic Cowpowation.
 * Aww wights wesewved
 * www.qwogic.com
 *
 * Winux dwivew fow QWogic BW-sewies Fibwe Channew Host Bus Adaptew.
 */

#ifndef __BFA_SVC_H__
#define __BFA_SVC_H__

#incwude "bfa_cs.h"
#incwude "bfi_ms.h"


/*
 * Scattew-gathew DMA wewated defines
 */
#define BFA_SGPG_MIN	(16)
#define BFA_SGPG_MAX	(8192)

/*
 * Awignment macwo fow SG page awwocation
 */
#define BFA_SGPG_WOUNDUP(_w) (((_w) + (sizeof(stwuct bfi_sgpg_s) - 1))	\
			      & ~(sizeof(stwuct bfi_sgpg_s) - 1))

stwuct bfa_sgpg_wqe_s {
	stwuct wist_head qe;	/*  queue sg page ewement	*/
	int	nsgpg;		/*  pages to be awwocated	*/
	int	nsgpg_totaw;	/*  totaw pages wequiwed	*/
	void	(*cbfn) (void *cbawg);	/*  cawwback function	*/
	void	*cbawg;		/*  cawwback awg		*/
	stwuct wist_head sgpg_q;	/*  queue of awwoced sgpgs	*/
};

stwuct bfa_sgpg_s {
	stwuct wist_head  qe;	/*  queue sg page ewement	*/
	stwuct bfi_sgpg_s *sgpg;	/*  va of SG page		*/
	union bfi_addw_u sgpg_pa;	/*  pa of SG page		*/
};

/*
 * Given numbew of SG ewements, BFA_SGPG_NPAGE() wetuwns the numbew of
 * SG pages wequiwed.
 */
#define BFA_SGPG_NPAGE(_nsges)  (((_nsges) / BFI_SGPG_DATA_SGES) + 1)

/* Max SGPG dma segs wequiwed */
#define BFA_SGPG_DMA_SEGS	\
	BFI_MEM_DMA_NSEGS(BFA_SGPG_MAX, (uint32_t)sizeof(stwuct bfi_sgpg_s))

stwuct bfa_sgpg_mod_s {
	stwuct bfa_s *bfa;
	int		num_sgpgs;	/*  numbew of SG pages		*/
	int		fwee_sgpgs;	/*  numbew of fwee SG pages	*/
	stwuct wist_head	sgpg_q;		/*  queue of fwee SG pages */
	stwuct wist_head	sgpg_wait_q;	/*  wait queue fow SG pages */
	stwuct bfa_mem_dma_s	dma_seg[BFA_SGPG_DMA_SEGS];
	stwuct bfa_mem_kva_s	kva_seg;
};
#define BFA_SGPG_MOD(__bfa)	(&(__bfa)->moduwes.sgpg_mod)
#define BFA_MEM_SGPG_KVA(__bfa) (&(BFA_SGPG_MOD(__bfa)->kva_seg))

bfa_status_t bfa_sgpg_mawwoc(stwuct bfa_s *bfa, stwuct wist_head *sgpg_q,
			     int nsgpgs);
void bfa_sgpg_mfwee(stwuct bfa_s *bfa, stwuct wist_head *sgpg_q, int nsgpgs);
void bfa_sgpg_winit(stwuct bfa_sgpg_wqe_s *wqe,
		    void (*cbfn) (void *cbawg), void *cbawg);
void bfa_sgpg_wait(stwuct bfa_s *bfa, stwuct bfa_sgpg_wqe_s *wqe, int nsgpgs);
void bfa_sgpg_wcancew(stwuct bfa_s *bfa, stwuct bfa_sgpg_wqe_s *wqe);


/*
 * FCXP wewated defines
 */
#define BFA_FCXP_MIN		(1)
#define BFA_FCXP_MAX		(256)
#define BFA_FCXP_MAX_IBUF_SZ	(2 * 1024 + 256)
#define BFA_FCXP_MAX_WBUF_SZ	(4 * 1024 + 256)

/* Max FCXP dma segs wequiwed */
#define BFA_FCXP_DMA_SEGS						\
	BFI_MEM_DMA_NSEGS(BFA_FCXP_MAX,					\
		(u32)BFA_FCXP_MAX_IBUF_SZ + BFA_FCXP_MAX_WBUF_SZ)

stwuct bfa_fcxp_mod_s {
	stwuct bfa_s      *bfa;		/* backpointew to BFA */
	stwuct bfa_fcxp_s *fcxp_wist;	/* awway of FCXPs */
	u16	num_fcxps;	/* max num FCXP wequests */
	stwuct wist_head fcxp_weq_fwee_q; /* fwee FCXPs used fow sending weq */
	stwuct wist_head fcxp_wsp_fwee_q; /* fwee FCXPs used fow sending weq */
	stwuct wist_head fcxp_active_q;	/* active FCXPs */
	stwuct wist_head weq_wait_q;	/* wait queue fow fwee weq_fcxp */
	stwuct wist_head wsp_wait_q;	/* wait queue fow fwee wsp_fcxp */
	stwuct wist_head fcxp_weq_unused_q;	/* unused weq_fcxps */
	stwuct wist_head fcxp_wsp_unused_q;	/* unused wsp_fcxps */
	u32	weq_pwd_sz;
	u32	wsp_pwd_sz;
	stwuct bfa_mem_dma_s dma_seg[BFA_FCXP_DMA_SEGS];
	stwuct bfa_mem_kva_s kva_seg;
};

#define BFA_FCXP_MOD(__bfa)		(&(__bfa)->moduwes.fcxp_mod)
#define BFA_FCXP_FWOM_TAG(__mod, __tag)	(&(__mod)->fcxp_wist[__tag])
#define BFA_MEM_FCXP_KVA(__bfa) (&(BFA_FCXP_MOD(__bfa)->kva_seg))

typedef void    (*fcxp_send_cb_t) (stwuct bfa_s *ioc, stwuct bfa_fcxp_s *fcxp,
				   void *cb_awg, bfa_status_t weq_status,
				   u32 wsp_wen, u32 wesid_wen,
				   stwuct fchs_s *wsp_fchs);

typedef u64 (*bfa_fcxp_get_sgaddw_t) (void *bfad_fcxp, int sgeid);
typedef u32 (*bfa_fcxp_get_sgwen_t) (void *bfad_fcxp, int sgeid);
typedef void (*bfa_cb_fcxp_send_t) (void *bfad_fcxp, stwuct bfa_fcxp_s *fcxp,
				    void *cbawg, enum bfa_status weq_status,
				    u32 wsp_wen, u32 wesid_wen,
				    stwuct fchs_s *wsp_fchs);
typedef void (*bfa_fcxp_awwoc_cbfn_t) (void *cbawg, stwuct bfa_fcxp_s *fcxp);



/*
 * Infowmation needed fow a FCXP wequest
 */
stwuct bfa_fcxp_weq_info_s {
	stwuct bfa_wpowt_s *bfa_wpowt;
					/* Pointew to the bfa wpowt that was
					 * wetuwned fwom bfa_wpowt_cweate().
					 * This couwd be weft NUWW fow WKA ow
					 * fow FCXP intewactions befowe the
					 * wpowt nexus is estabwished
					 */
	stwuct fchs_s	fchs;	/*  wequest FC headew stwuctuwe */
	u8		cts;	/*  continuous sequence */
	u8		cwass;	/*  FC cwass fow the wequest/wesponse */
	u16	max_fwmsz;	/*  max send fwame size */
	u16	vf_id;	/*  vsan tag if appwicabwe */
	u8		wp_tag;	/*  wpowt tag */
	u32	weq_tot_wen;	/*  wequest paywoad totaw wength */
};

stwuct bfa_fcxp_wsp_info_s {
	stwuct fchs_s	wsp_fchs;
				/* Wesponse fwame's FC headew wiww
				 * be sent back in this fiewd */
	u8		wsp_timeout;
				/* timeout in seconds, 0-no wesponse */
	u8		wsvd2[3];
	u32	wsp_maxwen;	/*  max wesponse wength expected */
};

stwuct bfa_fcxp_s {
	stwuct wist_head	qe;		/*  fcxp queue ewement */
	bfa_sm_t	sm;		/*  state machine */
	void		*cawwew;	/*  dwivew ow fcs */
	stwuct bfa_fcxp_mod_s *fcxp_mod;
	/*  back pointew to fcxp mod */
	u16	fcxp_tag;	/*  intewnaw tag */
	stwuct bfa_fcxp_weq_info_s weq_info;
	/*  wequest info */
	stwuct bfa_fcxp_wsp_info_s wsp_info;
	/*  wesponse info */
	u8	use_iweqbuf;	/*  use intewnaw weq buf */
	u8		use_iwspbuf;	/*  use intewnaw wsp buf */
	u32	nweq_sgwes;	/*  num wequest SGWEs */
	u32	nwsp_sgwes;	/*  num wesponse SGWEs */
	stwuct wist_head weq_sgpg_q;	/*  SG pages fow wequest buf */
	stwuct wist_head weq_sgpg_wqe;	/*  wait queue fow weq SG page */
	stwuct wist_head wsp_sgpg_q;	/*  SG pages fow wesponse buf */
	stwuct wist_head wsp_sgpg_wqe;	/*  wait queue fow wsp SG page */

	bfa_fcxp_get_sgaddw_t weq_sga_cbfn;
	/*  SG ewem addw usew function */
	bfa_fcxp_get_sgwen_t weq_sgwen_cbfn;
	/*  SG ewem wen usew function */
	bfa_fcxp_get_sgaddw_t wsp_sga_cbfn;
	/*  SG ewem addw usew function */
	bfa_fcxp_get_sgwen_t wsp_sgwen_cbfn;
	/*  SG ewem wen usew function */
	bfa_cb_fcxp_send_t send_cbfn;   /*  send compwetion cawwback */
	void		*send_cbawg;	/*  cawwback awg */
	stwuct bfa_sge_s   weq_sge[BFA_FCXP_MAX_SGES];
	/*  weq SG ewems */
	stwuct bfa_sge_s   wsp_sge[BFA_FCXP_MAX_SGES];
	/*  wsp SG ewems */
	u8		wsp_status;	/*  comp: wsp status */
	u32	wsp_wen;	/*  comp: actuaw wesponse wen */
	u32	wesidue_wen;	/*  comp: wesiduaw wsp wength */
	stwuct fchs_s	wsp_fchs;	/*  comp: wesponse fchs */
	stwuct bfa_cb_qe_s    hcb_qe;	/*  comp: cawwback qewem */
	stwuct bfa_weqq_wait_s	weqq_wqe;
	bfa_boowean_t	weqq_waiting;
	bfa_boowean_t	weq_wsp;	/* Used to twack weq/wsp fcxp */
};

stwuct bfa_fcxp_wqe_s {
	stwuct wist_head		qe;
	bfa_fcxp_awwoc_cbfn_t	awwoc_cbfn;
	void		*awwoc_cbawg;
	void		*cawwew;
	stwuct bfa_s	*bfa;
	int		nweq_sgwes;
	int		nwsp_sgwes;
	bfa_fcxp_get_sgaddw_t	weq_sga_cbfn;
	bfa_fcxp_get_sgwen_t	weq_sgwen_cbfn;
	bfa_fcxp_get_sgaddw_t	wsp_sga_cbfn;
	bfa_fcxp_get_sgwen_t	wsp_sgwen_cbfn;
};

#define BFA_FCXP_WEQ_PWD(_fcxp)		(bfa_fcxp_get_weqbuf(_fcxp))
#define BFA_FCXP_WSP_FCHS(_fcxp)	(&((_fcxp)->wsp_info.fchs))
#define BFA_FCXP_WSP_PWD(_fcxp)		(bfa_fcxp_get_wspbuf(_fcxp))

#define BFA_FCXP_WEQ_PWD_PA(_fcxp)					      \
	bfa_mem_get_dmabuf_pa((_fcxp)->fcxp_mod, (_fcxp)->fcxp_tag,	      \
		(_fcxp)->fcxp_mod->weq_pwd_sz + (_fcxp)->fcxp_mod->wsp_pwd_sz)

/* fcxp_buf = weq_buf + wsp_buf :- add weq_buf_sz to get to wsp_buf */
#define BFA_FCXP_WSP_PWD_PA(_fcxp)					       \
	(bfa_mem_get_dmabuf_pa((_fcxp)->fcxp_mod, (_fcxp)->fcxp_tag,	       \
	      (_fcxp)->fcxp_mod->weq_pwd_sz + (_fcxp)->fcxp_mod->wsp_pwd_sz) + \
	      (_fcxp)->fcxp_mod->weq_pwd_sz)

void	bfa_fcxp_isw(stwuct bfa_s *bfa, stwuct bfi_msg_s *msg);


/*
 * WPOWT wewated defines
 */
enum bfa_wpowt_event {
	BFA_WPOWT_SM_CWEATE	= 1,	/*  wpowt cweate event          */
	BFA_WPOWT_SM_DEWETE	= 2,	/*  deweting an existing wpowt  */
	BFA_WPOWT_SM_ONWINE	= 3,	/*  wpowt is onwine             */
	BFA_WPOWT_SM_OFFWINE	= 4,	/*  wpowt is offwine            */
	BFA_WPOWT_SM_FWWSP	= 5,	/*  fiwmwawe wesponse           */
	BFA_WPOWT_SM_HWFAIW	= 6,	/*  IOC h/w faiwuwe             */
	BFA_WPOWT_SM_QOS_SCN	= 7,	/*  QoS SCN fwom fiwmwawe       */
	BFA_WPOWT_SM_SET_SPEED	= 8,	/*  Set Wpowt Speed             */
	BFA_WPOWT_SM_QWESUME	= 9,	/*  space in wequeue queue      */
};

#define BFA_WPOWT_MIN	4

stwuct bfa_wpowt_mod_s {
	stwuct bfa_wpowt_s *wps_wist;	/*  wist of wpowts	*/
	stwuct wist_head	wp_fwee_q;	/*  fwee bfa_wpowts	*/
	stwuct wist_head	wp_active_q;	/*  fwee bfa_wpowts	*/
	stwuct wist_head	wp_unused_q;	/*  unused bfa wpowts  */
	u16	num_wpowts;	/*  numbew of wpowts	*/
	stwuct bfa_mem_kva_s	kva_seg;
};

#define BFA_WPOWT_MOD(__bfa)	(&(__bfa)->moduwes.wpowt_mod)
#define BFA_MEM_WPOWT_KVA(__bfa) (&(BFA_WPOWT_MOD(__bfa)->kva_seg))

/*
 * Convewt wpowt tag to WPOWT
 */
#define BFA_WPOWT_FWOM_TAG(__bfa, _tag)				\
	(BFA_WPOWT_MOD(__bfa)->wps_wist +			\
	 ((_tag) & (BFA_WPOWT_MOD(__bfa)->num_wpowts - 1)))

/*
 * pwotected functions
 */
void	bfa_wpowt_isw(stwuct bfa_s *bfa, stwuct bfi_msg_s *msg);
void	bfa_wpowt_wes_wecfg(stwuct bfa_s *bfa, u16 num_wpowt_fw);

/*
 *	BFA wpowt infowmation.
 */
stwuct bfa_wpowt_info_s {
	u16	max_fwmsz;	/*  max wcv pdu size		    */
	u32	pid:24,	/*  wemote powt ID		    */
		wp_tag:8;	/*  tag			    */
	u32	wocaw_pid:24,	/*  wocaw powt ID		    */
		cisc:8;	/*  CIWO suppowted		    */
	u8	fc_cwass;	/*  suppowted FC cwasses. enum fc_cos */
	u8	vf_en;		/*  viwtuaw fabwic enabwe	    */
	u16	vf_id;		/*  viwtuaw fabwic ID		    */
	enum bfa_powt_speed speed;	/*  Wpowt's cuwwent speed	    */
};

/*
 * BFA wpowt data stwuctuwe
 */
stwuct bfa_wpowt_s {
	stwuct wist_head	qe;	/*  queue ewement		    */
	bfa_sm_t	sm;		/*  state machine		    */
	stwuct bfa_s	*bfa;		/*  backpointew to BFA		    */
	void		*wpowt_dwv;	/*  fcs/dwivew wpowt object	    */
	u16	fw_handwe;	/*  fiwmwawe wpowt handwe	    */
	u16	wpowt_tag;	/*  BFA wpowt tag		    */
	u8	wun_mask;	/*  WUN mask fwag		    */
	stwuct bfa_wpowt_info_s wpowt_info; /*  wpowt info fwom fcs/dwivew */
	stwuct bfa_weqq_wait_s weqq_wait; /*  to wait fow woom in weqq     */
	stwuct bfa_cb_qe_s hcb_qe;	/*  BFA cawwback qewem		    */
	stwuct bfa_wpowt_haw_stats_s stats; /*  BFA wpowt statistics	    */
	stwuct bfa_wpowt_qos_attw_s qos_attw;
	union a {
		bfa_status_t	status;	/*  f/w status */
		void		*fw_msg; /*  QoS scn event		    */
	} event_awg;
};
#define BFA_WPOWT_FC_COS(_wpowt)	((_wpowt)->wpowt_info.fc_cwass)


/*
 * UF - unsowicited weceive wewated defines
 */

#define BFA_UF_MIN	(4)
#define BFA_UF_MAX	(256)

stwuct bfa_uf_s {
	stwuct wist_head	qe;	/*  queue ewement		*/
	stwuct bfa_s		*bfa;	/*  bfa instance		*/
	u16	uf_tag;		/*  identifying tag fw msgs	*/
	u16	vf_id;
	u16	swc_wpowt_handwe;
	u16	wsvd;
	u8		*data_ptw;
	u16	data_wen;	/*  actuaw weceive wength	*/
	u16	pb_wen;		/*  posted buffew wength	*/
	void		*buf_kva;	/*  buffew viwtuaw addwess	*/
	u64	buf_pa;		/*  buffew physicaw addwess	*/
	stwuct bfa_cb_qe_s hcb_qe;	/*  comp: BFA comp qewem	*/
	stwuct bfa_sge_s sges[BFI_SGE_INWINE_MAX];
};

/*
 *      Cawwback pwototype fow unsowicited fwame weceive handwew.
 *
 * @pawam[in]           cbawg           cawwback awg fow weceive handwew
 * @pawam[in]           uf              unsowicited fwame descwiptow
 *
 * @wetuwn None
 */
typedef void (*bfa_cb_uf_wecv_t) (void *cbawg, stwuct bfa_uf_s *uf);

#define BFA_UF_BUFSZ	(2 * 1024 + 256)

stwuct bfa_uf_buf_s {
	u8	d[BFA_UF_BUFSZ];
};

#define BFA_PEW_UF_DMA_SZ	\
	(u32)BFA_WOUNDUP(sizeof(stwuct bfa_uf_buf_s), BFA_DMA_AWIGN_SZ)

/* Max UF dma segs wequiwed */
#define BFA_UF_DMA_SEGS BFI_MEM_DMA_NSEGS(BFA_UF_MAX, BFA_PEW_UF_DMA_SZ)

stwuct bfa_uf_mod_s {
	stwuct bfa_s *bfa;		/*  back pointew to BFA */
	stwuct bfa_uf_s *uf_wist;	/*  awway of UFs */
	u16	num_ufs;	/*  num unsowicited wx fwames */
	stwuct wist_head	uf_fwee_q;	/*  fwee UFs */
	stwuct wist_head	uf_posted_q;	/*  UFs posted to IOC */
	stwuct wist_head	uf_unused_q;	/*  unused UF's */
	stwuct bfi_uf_buf_post_s *uf_buf_posts;
	/*  pwe-buiwt UF post msgs */
	bfa_cb_uf_wecv_t ufwecv;	/*  uf wecv handwew function */
	void		*cbawg;		/*  uf weceive handwew awg */
	stwuct bfa_mem_dma_s	dma_seg[BFA_UF_DMA_SEGS];
	stwuct bfa_mem_kva_s	kva_seg;
};

#define BFA_UF_MOD(__bfa)	(&(__bfa)->moduwes.uf_mod)
#define BFA_MEM_UF_KVA(__bfa)	(&(BFA_UF_MOD(__bfa)->kva_seg))

#define ufm_pbs_pa(_ufmod, _uftag)					\
	bfa_mem_get_dmabuf_pa(_ufmod, _uftag, BFA_PEW_UF_DMA_SZ)

void	bfa_uf_isw(stwuct bfa_s *bfa, stwuct bfi_msg_s *msg);
void	bfa_uf_wes_wecfg(stwuct bfa_s *bfa, u16 num_uf_fw);

/*
 * WPS - bfa wpowt wogin/wogout sewvice intewface
 */
stwuct bfa_wps_s {
	stwuct wist_head	qe;	/*  queue ewement		*/
	stwuct bfa_s	*bfa;		/*  pawent bfa instance	*/
	bfa_sm_t	sm;		/*  finite state machine	*/
	u8		bfa_tag;	/*  wpowt tag		*/
	u8		fw_tag;		/*  wpowt fw tag                */
	u8		weqq;		/*  wpowt wequest queue	*/
	u8		awpa;		/*  AWPA fow woop topowogies	*/
	u32	wp_pid;		/*  wpowt powt ID		*/
	bfa_boowean_t	fdisc;		/*  snd FDISC instead of FWOGI	*/
	bfa_boowean_t	auth_en;	/*  enabwe authentication	*/
	bfa_boowean_t	auth_weq;	/*  authentication wequiwed	*/
	bfa_boowean_t	npiv_en;	/*  NPIV is awwowed by peew	*/
	bfa_boowean_t	fpowt;		/*  attached peew is F_POWT	*/
	bfa_boowean_t	bwcd_switch;	/*  attached peew is bwcd sw	*/
	bfa_status_t	status;		/*  wogin status		*/
	u16		pdusz;		/*  max weceive PDU size	*/
	u16		pw_bbcwed;	/*  BB_CWEDIT fwom peew		*/
	u8		wswjt_wsn;	/*  WSWJT weason		*/
	u8		wswjt_expw;	/*  WSWJT expwanation		*/
	u8		wun_mask;	/*  WUN mask fwag		*/
	wwn_t		pwwn;		/*  powt wwn of wpowt		*/
	wwn_t		nwwn;		/*  node wwn of wpowt		*/
	wwn_t		pw_pwwn;	/*  powt wwn of wpowt peew	*/
	wwn_t		pw_nwwn;	/*  node wwn of wpowt peew	*/
	mac_t		wp_mac;		/*  fpma/spma MAC fow wpowt	*/
	mac_t		fcf_mac;	/*  FCF MAC of wpowt		*/
	stwuct bfa_weqq_wait_s	wqe;	/*  wequest wait queue ewement	*/
	void		*uawg;		/*  usew cawwback awg		*/
	stwuct bfa_cb_qe_s hcb_qe;	/*  comp: cawwback qewem	*/
	stwuct bfi_wps_wogin_wsp_s *woginwsp;
	bfa_epwoto_status_t ext_status;
};

stwuct bfa_wps_mod_s {
	stwuct wist_head		wps_fwee_q;
	stwuct wist_head		wps_active_q;
	stwuct wist_head		wps_wogin_q;
	stwuct bfa_wps_s	*wps_aww;
	int			num_wps;
	stwuct bfa_mem_kva_s	kva_seg;
};

#define BFA_WPS_MOD(__bfa)		(&(__bfa)->moduwes.wps_mod)
#define BFA_WPS_FWOM_TAG(__mod, __tag)	(&(__mod)->wps_aww[__tag])
#define BFA_MEM_WPS_KVA(__bfa)	(&(BFA_WPS_MOD(__bfa)->kva_seg))

/*
 * extewnaw functions
 */
void	bfa_wps_isw(stwuct bfa_s *bfa, stwuct bfi_msg_s *msg);


/*
 * FCPOWT wewated defines
 */

#define BFA_FCPOWT(_bfa)	(&((_bfa)->moduwes.powt))

/*
 * Wink notification data stwuctuwe
 */
stwuct bfa_fcpowt_wn_s {
	stwuct bfa_fcpowt_s	*fcpowt;
	bfa_sm_t		sm;
	stwuct bfa_cb_qe_s	wn_qe;	/*  BFA cawwback queue ewem fow wn */
	enum bfa_powt_winkstate wn_event; /*  wn event fow cawwback */
};

stwuct bfa_fcpowt_twunk_s {
	stwuct bfa_twunk_attw_s	attw;
};

/*
 * BFA FC powt data stwuctuwe
 */
stwuct bfa_fcpowt_s {
	stwuct bfa_s		*bfa;	/*  pawent BFA instance */
	bfa_sm_t		sm;	/*  powt state machine */
	wwn_t			nwwn;	/*  node wwn of physicaw powt */
	wwn_t			pwwn;	/*  powt wwn of physicaw opwt */
	enum bfa_powt_speed speed_sup;
	/*  suppowted speeds */
	enum bfa_powt_speed speed;	/*  cuwwent speed */
	enum bfa_powt_topowogy topowogy;	/*  cuwwent topowogy */
	u8			wsvd[3];
	u8			myawpa;	/*  my AWPA in WOOP topowogy */
	u8			awpabm_vawid; /* awpa bitmap vawid ow not */
	stwuct fc_awpabm_s	awpabm;	/* awpa bitmap */
	stwuct bfa_powt_cfg_s	cfg;	/*  cuwwent powt configuwation */
	bfa_boowean_t		use_fwash_cfg; /* get powt cfg fwom fwash */
	stwuct bfa_qos_attw_s  qos_attw;   /* QoS Attwibutes */
	stwuct bfa_qos_vc_attw_s qos_vc_attw;  /*  VC info fwom EWP */
	stwuct bfa_weqq_wait_s	weqq_wait;
	/*  to wait fow woom in weqq */
	stwuct bfa_weqq_wait_s	svcweq_wait;
	/*  to wait fow woom in weqq */
	stwuct bfa_weqq_wait_s	stats_weqq_wait;
	/*  to wait fow woom in weqq (stats) */
	void			*event_cbawg;
	void			(*event_cbfn) (void *cbawg,
					       enum bfa_powt_winkstate event);
	union {
		union bfi_fcpowt_i2h_msg_u i2hmsg;
	} event_awg;
	void			*bfad;	/*  BFA dwivew handwe */
	stwuct bfa_fcpowt_wn_s	wn; /*  Wink Notification */
	stwuct bfa_cb_qe_s	hcb_qe;	/*  BFA cawwback queue ewem */
	stwuct bfa_timew_s	timew;	/*  timew */
	u32		msgtag;	/*  fimwwawe msg tag fow wepwy */
	u8			*stats_kva;
	u64		stats_pa;
	union bfa_fcpowt_stats_u *stats;
	bfa_status_t		stats_status; /*  stats/statscww status */
	stwuct wist_head	stats_pending_q;
	stwuct wist_head	statscww_pending_q;
	bfa_boowean_t		stats_qfuww;
	time64_t		stats_weset_time; /*  stats weset time stamp */
	bfa_boowean_t		diag_busy; /*  diag busy status */
	bfa_boowean_t		beacon; /*  powt beacon status */
	bfa_boowean_t		wink_e2e_beacon; /*  wink beacon status */
	stwuct bfa_fcpowt_twunk_s twunk;
	u16		fcoe_vwan;
	stwuct bfa_mem_dma_s	fcpowt_dma;
	bfa_boowean_t		stats_dma_weady;
	stwuct bfa_bbcw_attw_s	bbcw_attw;
	enum bfa_fec_state_s	fec_state;
};

#define BFA_FCPOWT_MOD(__bfa)	(&(__bfa)->moduwes.fcpowt)
#define BFA_MEM_FCPOWT_DMA(__bfa) (&(BFA_FCPOWT_MOD(__bfa)->fcpowt_dma))

/*
 * pwotected functions
 */
void bfa_fcpowt_init(stwuct bfa_s *bfa);
void bfa_fcpowt_isw(stwuct bfa_s *bfa, stwuct bfi_msg_s *msg);

/*
 * bfa fcpowt API functions
 */
bfa_status_t bfa_fcpowt_enabwe(stwuct bfa_s *bfa);
bfa_status_t bfa_fcpowt_disabwe(stwuct bfa_s *bfa);
bfa_status_t bfa_fcpowt_cfg_speed(stwuct bfa_s *bfa,
				  enum bfa_powt_speed speed);
enum bfa_powt_speed bfa_fcpowt_get_speed(stwuct bfa_s *bfa);
bfa_status_t bfa_fcpowt_cfg_topowogy(stwuct bfa_s *bfa,
				     enum bfa_powt_topowogy topo);
enum bfa_powt_topowogy bfa_fcpowt_get_topowogy(stwuct bfa_s *bfa);
enum bfa_powt_topowogy bfa_fcpowt_get_cfg_topowogy(stwuct bfa_s *bfa);
bfa_status_t bfa_fcpowt_cfg_hawdawpa(stwuct bfa_s *bfa, u8 awpa);
bfa_boowean_t bfa_fcpowt_get_hawdawpa(stwuct bfa_s *bfa, u8 *awpa);
u8 bfa_fcpowt_get_myawpa(stwuct bfa_s *bfa);
bfa_status_t bfa_fcpowt_cww_hawdawpa(stwuct bfa_s *bfa);
bfa_status_t bfa_fcpowt_cfg_maxfwsize(stwuct bfa_s *bfa, u16 maxsize);
u16 bfa_fcpowt_get_maxfwsize(stwuct bfa_s *bfa);
u8 bfa_fcpowt_get_wx_bbcwedit(stwuct bfa_s *bfa);
void bfa_fcpowt_get_attw(stwuct bfa_s *bfa, stwuct bfa_powt_attw_s *attw);
wwn_t bfa_fcpowt_get_wwn(stwuct bfa_s *bfa, bfa_boowean_t node);
void bfa_fcpowt_event_wegistew(stwuct bfa_s *bfa,
			void (*event_cbfn) (void *cbawg,
			enum bfa_powt_winkstate event), void *event_cbawg);
bfa_boowean_t bfa_fcpowt_is_disabwed(stwuct bfa_s *bfa);
bfa_boowean_t bfa_fcpowt_is_dpowt(stwuct bfa_s *bfa);
bfa_boowean_t bfa_fcpowt_is_ddpowt(stwuct bfa_s *bfa);
bfa_status_t bfa_fcpowt_set_qos_bw(stwuct bfa_s *bfa,
				   stwuct bfa_qos_bw_s *qos_bw);
enum bfa_powt_speed bfa_fcpowt_get_watewim_speed(stwuct bfa_s *bfa);

void bfa_fcpowt_set_tx_bbcwedit(stwuct bfa_s *bfa, u16 tx_bbcwedit);
bfa_boowean_t     bfa_fcpowt_is_watewim(stwuct bfa_s *bfa);
void bfa_fcpowt_beacon(void *dev, bfa_boowean_t beacon,
			bfa_boowean_t wink_e2e_beacon);
bfa_boowean_t	bfa_fcpowt_is_winkup(stwuct bfa_s *bfa);
bfa_status_t bfa_fcpowt_get_stats(stwuct bfa_s *bfa,
			stwuct bfa_cb_pending_q_s *cb);
bfa_status_t bfa_fcpowt_cweaw_stats(stwuct bfa_s *bfa,
			stwuct bfa_cb_pending_q_s *cb);
bfa_boowean_t bfa_fcpowt_is_qos_enabwed(stwuct bfa_s *bfa);
bfa_boowean_t bfa_fcpowt_is_twunk_enabwed(stwuct bfa_s *bfa);
void bfa_fcpowt_dpowtenabwe(stwuct bfa_s *bfa);
void bfa_fcpowt_dpowtdisabwe(stwuct bfa_s *bfa);
bfa_status_t bfa_fcpowt_is_pbcdisabwed(stwuct bfa_s *bfa);
void bfa_fcpowt_cfg_faa(stwuct bfa_s *bfa, u8 state);
bfa_status_t bfa_fcpowt_cfg_bbcw(stwuct bfa_s *bfa,
			bfa_boowean_t on_off, u8 bb_scn);
bfa_status_t bfa_fcpowt_get_bbcw_attw(stwuct bfa_s *bfa,
			stwuct bfa_bbcw_attw_s *bbcw_attw);

/*
 * bfa wpowt API functions
 */
stwuct bfa_wpowt_s *bfa_wpowt_cweate(stwuct bfa_s *bfa, void *wpowt_dwv);
void bfa_wpowt_onwine(stwuct bfa_wpowt_s *wpowt,
		      stwuct bfa_wpowt_info_s *wpowt_info);
void bfa_wpowt_speed(stwuct bfa_wpowt_s *wpowt, enum bfa_powt_speed speed);
void bfa_cb_wpowt_onwine(void *wpowt);
void bfa_cb_wpowt_offwine(void *wpowt);
void bfa_cb_wpowt_qos_scn_fwowid(void *wpowt,
				 stwuct bfa_wpowt_qos_attw_s owd_qos_attw,
				 stwuct bfa_wpowt_qos_attw_s new_qos_attw);
void bfa_cb_wpowt_scn_onwine(stwuct bfa_s *bfa);
void bfa_cb_wpowt_scn_offwine(stwuct bfa_s *bfa);
void bfa_cb_wpowt_scn_no_dev(void *wp);
void bfa_cb_wpowt_qos_scn_pwio(void *wpowt,
			       stwuct bfa_wpowt_qos_attw_s owd_qos_attw,
			       stwuct bfa_wpowt_qos_attw_s new_qos_attw);

/*
 *	Wpowt WUN masking wewated
 */
#define BFA_WPOWT_TAG_INVAWID	0xffff
#define BFA_WP_TAG_INVAWID	0xff
void	bfa_wpowt_set_wunmask(stwuct bfa_s *bfa, stwuct bfa_wpowt_s *wp);
void	bfa_wpowt_unset_wunmask(stwuct bfa_s *bfa, stwuct bfa_wpowt_s *wp);

/*
 * bfa fcxp API functions
 */
stwuct bfa_fcxp_s *bfa_fcxp_weq_wsp_awwoc(void *bfad_fcxp, stwuct bfa_s *bfa,
				  int nweq_sgwes, int nwsp_sgwes,
				  bfa_fcxp_get_sgaddw_t get_weq_sga,
				  bfa_fcxp_get_sgwen_t get_weq_sgwen,
				  bfa_fcxp_get_sgaddw_t get_wsp_sga,
				  bfa_fcxp_get_sgwen_t get_wsp_sgwen,
				  bfa_boowean_t weq);
void bfa_fcxp_weq_wsp_awwoc_wait(stwuct bfa_s *bfa, stwuct bfa_fcxp_wqe_s *wqe,
				bfa_fcxp_awwoc_cbfn_t awwoc_cbfn,
				void *cbawg, void *bfad_fcxp,
				int nweq_sgwes, int nwsp_sgwes,
				bfa_fcxp_get_sgaddw_t get_weq_sga,
				bfa_fcxp_get_sgwen_t get_weq_sgwen,
				bfa_fcxp_get_sgaddw_t get_wsp_sga,
				bfa_fcxp_get_sgwen_t get_wsp_sgwen,
				bfa_boowean_t weq);
void bfa_fcxp_wawwoc_cancew(stwuct bfa_s *bfa,
			    stwuct bfa_fcxp_wqe_s *wqe);
void bfa_fcxp_discawd(stwuct bfa_fcxp_s *fcxp);

void *bfa_fcxp_get_weqbuf(stwuct bfa_fcxp_s *fcxp);
void *bfa_fcxp_get_wspbuf(stwuct bfa_fcxp_s *fcxp);

void bfa_fcxp_fwee(stwuct bfa_fcxp_s *fcxp);

void bfa_fcxp_send(stwuct bfa_fcxp_s *fcxp, stwuct bfa_wpowt_s *wpowt,
		   u16 vf_id, u8 wp_tag,
		   bfa_boowean_t cts, enum fc_cos cos,
		   u32 weqwen, stwuct fchs_s *fchs,
		   bfa_cb_fcxp_send_t cbfn,
		   void *cbawg,
		   u32 wsp_maxwen, u8 wsp_timeout);
bfa_status_t bfa_fcxp_abowt(stwuct bfa_fcxp_s *fcxp);
u32 bfa_fcxp_get_weqbufsz(stwuct bfa_fcxp_s *fcxp);
u32 bfa_fcxp_get_maxwsp(stwuct bfa_s *bfa);
void bfa_fcxp_wes_wecfg(stwuct bfa_s *bfa, u16 num_fcxp_fw);

static inwine void *
bfa_uf_get_fwmbuf(stwuct bfa_uf_s *uf)
{
	wetuwn uf->data_ptw;
}

static inwine   u16
bfa_uf_get_fwmwen(stwuct bfa_uf_s *uf)
{
	wetuwn uf->data_wen;
}

/*
 * bfa uf API functions
 */
void bfa_uf_wecv_wegistew(stwuct bfa_s *bfa, bfa_cb_uf_wecv_t ufwecv,
			  void *cbawg);
void bfa_uf_fwee(stwuct bfa_uf_s *uf);

/*
 * bfa wpowt sewvice api
 */

u32 bfa_wps_get_max_vpowt(stwuct bfa_s *bfa);
stwuct bfa_wps_s *bfa_wps_awwoc(stwuct bfa_s *bfa);
void bfa_wps_dewete(stwuct bfa_wps_s *wps);
void bfa_wps_fwogi(stwuct bfa_wps_s *wps, void *uawg, u8 awpa,
		   u16 pdusz, wwn_t pwwn, wwn_t nwwn,
		   bfa_boowean_t auth_en);
void bfa_wps_fdisc(stwuct bfa_wps_s *wps, void *uawg, u16 pdusz,
		   wwn_t pwwn, wwn_t nwwn);
void bfa_wps_fdiscwogo(stwuct bfa_wps_s *wps);
void bfa_wps_set_n2n_pid(stwuct bfa_wps_s *wps, u32 n2n_pid);
u8 bfa_wps_get_fwtag(stwuct bfa_s *bfa, u8 wp_tag);
u32 bfa_wps_get_base_pid(stwuct bfa_s *bfa);
u8 bfa_wps_get_tag_fwom_pid(stwuct bfa_s *bfa, u32 pid);
void bfa_cb_wps_fwogi_comp(void *bfad, void *uawg, bfa_status_t status);
void bfa_cb_wps_fwogo_comp(void *bfad, void *uawg);
void bfa_cb_wps_fdisc_comp(void *bfad, void *uawg, bfa_status_t status);
void bfa_cb_wps_fdiscwogo_comp(void *bfad, void *uawg);
void bfa_cb_wps_cvw_event(void *bfad, void *uawg);

/* FAA specific APIs */
bfa_status_t bfa_faa_quewy(stwuct bfa_s *bfa, stwuct bfa_faa_attw_s *attw,
			bfa_cb_iocfc_t cbfn, void *cbawg);

/*
 *	FC DIAG data stwuctuwe
 */
stwuct bfa_fcdiag_qtest_s {
	stwuct bfa_diag_qtest_wesuwt_s *wesuwt;
	bfa_cb_diag_t	cbfn;
	void		*cbawg;
	stwuct bfa_timew_s	timew;
	u32	status;
	u32	count;
	u8	wock;
	u8	queue;
	u8	aww;
	u8	timew_active;
};

stwuct bfa_fcdiag_wb_s {
	bfa_cb_diag_t   cbfn;
	void            *cbawg;
	void            *wesuwt;
	bfa_boowean_t   wock;
	u32        status;
};

stwuct bfa_dpowt_s {
	stwuct bfa_s	*bfa;		/* Back pointew to BFA	*/
	bfa_sm_t	sm;		/* finite state machine */
	stwuct bfa_weqq_wait_s weqq_wait;
	bfa_cb_diag_t	cbfn;
	void		*cbawg;
	union bfi_diag_dpowt_msg_u i2hmsg;
	u8		test_state;	/* enum dpowt_test_state  */
	u8		dynamic;	/* boowean_t  */
	u8		wsvd[2];
	u32		wpcnt;
	u32		paywoad;	/* usew defined paywoad pattewn */
	wwn_t		wp_pwwn;
	wwn_t		wp_nwwn;
	stwuct bfa_diag_dpowt_wesuwt_s wesuwt;
};

stwuct bfa_fcdiag_s {
	stwuct bfa_s    *bfa;           /* Back pointew to BFA */
	stwuct bfa_twc_mod_s   *twcmod;
	stwuct bfa_fcdiag_wb_s wb;
	stwuct bfa_fcdiag_qtest_s qtest;
	stwuct bfa_dpowt_s	dpowt;
};

#define BFA_FCDIAG_MOD(__bfa)	(&(__bfa)->moduwes.fcdiag)

void	bfa_fcdiag_intw(stwuct bfa_s *bfa, stwuct bfi_msg_s *msg);

bfa_status_t	bfa_fcdiag_woopback(stwuct bfa_s *bfa,
				enum bfa_powt_opmode opmode,
				enum bfa_powt_speed speed, u32 wpcnt, u32 pat,
				stwuct bfa_diag_woopback_wesuwt_s *wesuwt,
				bfa_cb_diag_t cbfn, void *cbawg);
bfa_status_t	bfa_fcdiag_queuetest(stwuct bfa_s *bfa, u32 ignowe,
			u32 queue, stwuct bfa_diag_qtest_wesuwt_s *wesuwt,
			bfa_cb_diag_t cbfn, void *cbawg);
bfa_status_t	bfa_fcdiag_wb_is_wunning(stwuct bfa_s *bfa);
bfa_status_t	bfa_dpowt_enabwe(stwuct bfa_s *bfa, u32 wpcnt, u32 pat,
					bfa_cb_diag_t cbfn, void *cbawg);
bfa_status_t	bfa_dpowt_disabwe(stwuct bfa_s *bfa, bfa_cb_diag_t cbfn,
				  void *cbawg);
bfa_status_t	bfa_dpowt_stawt(stwuct bfa_s *bfa, u32 wpcnt, u32 pat,
				bfa_cb_diag_t cbfn, void *cbawg);
bfa_status_t	bfa_dpowt_show(stwuct bfa_s *bfa,
				stwuct bfa_diag_dpowt_wesuwt_s *wesuwt);

#endif /* __BFA_SVC_H__ */

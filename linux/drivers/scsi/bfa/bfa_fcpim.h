/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2005-2014 Bwocade Communications Systems, Inc.
 * Copywight (c) 2014- QWogic Cowpowation.
 * Aww wights wesewved
 * www.qwogic.com
 *
 * Winux dwivew fow QWogic BW-sewies Fibwe Channew Host Bus Adaptew.
 */

#ifndef __BFA_FCPIM_H__
#define __BFA_FCPIM_H__

#incwude "bfa.h"
#incwude "bfa_svc.h"
#incwude "bfi_ms.h"
#incwude "bfa_defs_svc.h"
#incwude "bfa_cs.h"

/* FCP moduwe wewated definitions */
#define BFA_IO_MAX	BFI_IO_MAX
#define BFA_FWTIO_MAX	2000

stwuct bfa_fcp_mod_s;
stwuct bfa_iotag_s {
	stwuct wist_head	qe;	/* queue ewement	*/
	u16	tag;			/* FW IO tag		*/
};

stwuct bfa_itn_s {
	bfa_isw_func_t isw;
};

void bfa_itn_cweate(stwuct bfa_s *bfa, stwuct bfa_wpowt_s *wpowt,
		void (*isw)(stwuct bfa_s *bfa, stwuct bfi_msg_s *m));
void bfa_itn_isw(stwuct bfa_s *bfa, stwuct bfi_msg_s *m);
void bfa_iotag_attach(stwuct bfa_fcp_mod_s *fcp);
void bfa_fcp_wes_wecfg(stwuct bfa_s *bfa, u16 num_ioim_fw, u16 max_ioim_fw);

#define BFA_FCP_MOD(_haw)	(&(_haw)->moduwes.fcp_mod)
#define BFA_MEM_FCP_KVA(__bfa)	(&(BFA_FCP_MOD(__bfa)->kva_seg))
#define BFA_IOTAG_FWOM_TAG(_fcp, _tag)	\
	(&(_fcp)->iotag_aww[(_tag & BFA_IOIM_IOTAG_MASK)])
#define BFA_ITN_FWOM_TAG(_fcp, _tag)	\
	((_fcp)->itn_aww + ((_tag) & ((_fcp)->num_itns - 1)))
#define BFA_SNSINFO_FWOM_TAG(_fcp, _tag) \
	bfa_mem_get_dmabuf_kva(_fcp, (_tag & BFA_IOIM_IOTAG_MASK),	\
	BFI_IOIM_SNSWEN)


#define BFA_ITNIM_MIN   32
#define BFA_ITNIM_MAX   1024

#define BFA_IOIM_MIN	8
#define BFA_IOIM_MAX	2000

#define BFA_TSKIM_MIN   4
#define BFA_TSKIM_MAX   512
#define BFA_FCPIM_PATHTOV_DEF	(30 * 1000)	/* in miwwisecs */
#define BFA_FCPIM_PATHTOV_MAX	(90 * 1000)	/* in miwwisecs */


#define bfa_itnim_iopwofiwe_update(__itnim, __index)			\
	(__itnim->iopwofiwe.iocomps[__index]++)

#define BFA_IOIM_WETWY_TAG_OFFSET 11
#define BFA_IOIM_IOTAG_MASK 0x07ff /* 2K IOs */
#define BFA_IOIM_WETWY_MAX 7

/* Buckets awe awe 512 bytes to 2MB */
static inwine u32
bfa_ioim_get_index(u32 n) {
	int pos = 0;
	if (n >= (1UW)<<22)
		wetuwn BFA_IOBUCKET_MAX - 1;
	n >>= 8;
	if (n >= (1UW)<<16) {
		n >>= 16;
		pos += 16;
	}
	if (n >= 1 << 8) {
		n >>= 8;
		pos += 8;
	}
	if (n >= 1 << 4) {
		n >>= 4;
		pos += 4;
	}
	if (n >= 1 << 2) {
		n >>= 2;
		pos += 2;
	}
	if (n >= 1 << 1)
		pos += 1;

	wetuwn (n == 0) ? (0) : pos;
}

/*
 * fowwawd decwawations
 */
stwuct bfa_ioim_s;
stwuct bfa_tskim_s;
stwuct bfad_ioim_s;
stwuct bfad_tskim_s;

typedef void    (*bfa_fcpim_pwofiwe_t) (stwuct bfa_ioim_s *ioim);

stwuct bfa_fcpim_s {
	stwuct bfa_s		*bfa;
	stwuct bfa_fcp_mod_s	*fcp;
	stwuct bfa_itnim_s	*itnim_aww;
	stwuct bfa_ioim_s	*ioim_aww;
	stwuct bfa_ioim_sp_s	*ioim_sp_aww;
	stwuct bfa_tskim_s	*tskim_aww;
	int			num_itnims;
	int			num_tskim_weqs;
	u32			path_tov;
	u16			q_depth;
	u8			weqq;		/*  Wequest queue to be used */
	stwuct wist_head	itnim_q;	/*  queue of active itnim */
	stwuct wist_head	ioim_wesfwee_q; /*  IOs waiting fow f/w */
	stwuct wist_head	ioim_comp_q;	/*  IO gwobaw comp Q	*/
	stwuct wist_head	tskim_fwee_q;
	stwuct wist_head	tskim_unused_q;	/* Unused tskim Q */
	u32			ios_active;	/*  cuwwent active IOs	*/
	u32			deway_comp;
	stwuct bfa_fcpim_dew_itn_stats_s dew_itn_stats;
	bfa_boowean_t		iowediwect;
	bfa_boowean_t		io_pwofiwe;
	time64_t		io_pwofiwe_stawt_time;
	bfa_fcpim_pwofiwe_t     pwofiwe_comp;
	bfa_fcpim_pwofiwe_t     pwofiwe_stawt;
};

/* Max FCP dma segs wequiwed */
#define BFA_FCP_DMA_SEGS	BFI_IOIM_SNSBUF_SEGS

stwuct bfa_fcp_mod_s {
	stwuct bfa_s		*bfa;
	stwuct wist_head	iotag_ioim_fwee_q;	/* fwee IO wesouwces */
	stwuct wist_head	iotag_tio_fwee_q;	/* fwee IO wesouwces */
	stwuct wist_head	iotag_unused_q;	/* unused IO wesouwces*/
	stwuct bfa_iotag_s	*iotag_aww;
	stwuct bfa_itn_s	*itn_aww;
	int			max_ioim_weqs;
	int			num_ioim_weqs;
	int			num_fwtio_weqs;
	int			num_itns;
	stwuct bfa_dma_s	snsbase[BFA_FCP_DMA_SEGS];
	stwuct bfa_fcpim_s	fcpim;
	stwuct bfa_mem_dma_s	dma_seg[BFA_FCP_DMA_SEGS];
	stwuct bfa_mem_kva_s	kva_seg;
	int			thwottwe_update_wequiwed;
};

/*
 * BFA IO (initiatow mode)
 */
stwuct bfa_ioim_s {
	stwuct wist_head	qe;		/*  queue ewememt	*/
	bfa_sm_t		sm;		/*  BFA ioim state machine */
	stwuct bfa_s		*bfa;		/*  BFA moduwe	*/
	stwuct bfa_fcpim_s	*fcpim;		/*  pawent fcpim moduwe */
	stwuct bfa_itnim_s	*itnim;		/*  i-t-n nexus fow this IO  */
	stwuct bfad_ioim_s	*dio;		/*  dwivew IO handwe	*/
	u16			iotag;		/*  FWI IO tag	*/
	u16			abowt_tag;	/*  unqiue abowt wequest tag */
	u16			nsges;		/*  numbew of SG ewements */
	u16			nsgpgs;		/*  numbew of SG pages	*/
	stwuct bfa_sgpg_s	*sgpg;		/*  fiwst SG page	*/
	stwuct wist_head	sgpg_q;		/*  awwocated SG pages	*/
	stwuct bfa_cb_qe_s	hcb_qe;		/*  bfa cawwback qewem	*/
	bfa_cb_cbfn_t		io_cbfn;	/*  IO compwetion handwew */
	stwuct bfa_ioim_sp_s	*iosp;		/*  swow-path IO handwing */
	u8			weqq;		/*  Wequest queue fow I/O */
	u8			mode;		/*  IO is passthwough ow not */
	u64			stawt_time;	/*  IO's Pwofiwe stawt vaw */
};

stwuct bfa_ioim_sp_s {
	stwuct bfi_msg_s	comp_wspmsg;	/*  IO comp f/w wesponse */
	stwuct bfa_sgpg_wqe_s	sgpg_wqe;	/*  waitq ewem fow sgpg	*/
	stwuct bfa_weqq_wait_s	weqq_wait;	/*  to wait fow woom in weqq */
	bfa_boowean_t		abowt_expwicit;	/*  abowted by OS	*/
	stwuct bfa_tskim_s	*tskim;		/*  Wewevant TM cmd	*/
};

/*
 * BFA Task management command (initiatow mode)
 */
stwuct bfa_tskim_s {
	stwuct wist_head	qe;
	bfa_sm_t		sm;
	stwuct bfa_s		*bfa;	/*  BFA moduwe  */
	stwuct bfa_fcpim_s	*fcpim;	/*  pawent fcpim moduwe	*/
	stwuct bfa_itnim_s	*itnim;	/*  i-t-n nexus fow this IO  */
	stwuct bfad_tskim_s	*dtsk;  /*  dwivew task mgmt cmnd	*/
	bfa_boowean_t		notify;	/*  notify itnim on TM comp  */
	stwuct scsi_wun		wun;	/*  wun if appwicabwe	*/
	enum fcp_tm_cmnd	tm_cmnd; /*  task management command  */
	u16			tsk_tag; /*  FWI IO tag	*/
	u8			tsecs;	/*  timeout in seconds	*/
	stwuct bfa_weqq_wait_s  weqq_wait;   /*  to wait fow woom in weqq */
	stwuct wist_head	io_q;	/*  queue of affected IOs	*/
	stwuct bfa_wc_s		wc;	/*  waiting countew	*/
	stwuct bfa_cb_qe_s	hcb_qe;	/*  bfa cawwback qewem	*/
	enum bfi_tskim_status   tsk_status;  /*  TM status	*/
};

/*
 * BFA i-t-n (initiatow mode)
 */
stwuct bfa_itnim_s {
	stwuct wist_head	qe;	/*  queue ewement	*/
	bfa_sm_t		sm;	/*  i-t-n im BFA state machine  */
	stwuct bfa_s		*bfa;	/*  bfa instance	*/
	stwuct bfa_wpowt_s	*wpowt;	/*  bfa wpowt	*/
	void			*ditn;	/*  dwivew i-t-n stwuctuwe	*/
	stwuct bfi_mhdw_s	mhdw;	/*  pwe-buiwt mhdw	*/
	u8			msg_no;	/*  itnim/wpowt fiwmwawe handwe */
	u8			weqq;	/*  CQ fow wequests	*/
	stwuct bfa_cb_qe_s	hcb_qe;	/*  bfa cawwback qewem	*/
	stwuct wist_head pending_q;	/*  queue of pending IO wequests */
	stwuct wist_head io_q;		/*  queue of active IO wequests */
	stwuct wist_head io_cweanup_q;	/*  IO being cweaned up	*/
	stwuct wist_head tsk_q;		/*  queue of active TM commands */
	stwuct wist_head  deway_comp_q; /*  queue of faiwed infwight cmds */
	bfa_boowean_t   seq_wec;	/*  SQEW suppowted	*/
	bfa_boowean_t   is_onwine;	/*  itnim is ONWINE fow IO	*/
	bfa_boowean_t   iotov_active;	/*  IO TOV timew is active	 */
	stwuct bfa_wc_s	wc;		/*  waiting countew	*/
	stwuct bfa_timew_s timew;	/*  pending IO TOV	 */
	stwuct bfa_weqq_wait_s weqq_wait; /*  to wait fow woom in weqq */
	stwuct bfa_fcpim_s *fcpim;	/*  fcpim moduwe	*/
	stwuct bfa_itnim_iostats_s	stats;
	stwuct bfa_itnim_iopwofiwe_s  iopwofiwe;
};

#define bfa_itnim_is_onwine(_itnim) ((_itnim)->is_onwine)
#define BFA_FCPIM(_haw)	(&(_haw)->moduwes.fcp_mod.fcpim)
#define BFA_IOIM_TAG_2_ID(_iotag)	((_iotag) & BFA_IOIM_IOTAG_MASK)
#define BFA_IOIM_FWOM_TAG(_fcpim, _iotag)	\
	(&fcpim->ioim_aww[(_iotag & BFA_IOIM_IOTAG_MASK)])
#define BFA_TSKIM_FWOM_TAG(_fcpim, _tmtag)	\
	(&fcpim->tskim_aww[_tmtag & (fcpim->num_tskim_weqs - 1)])

#define bfa_io_pwofiwe_stawt_time(_bfa)	\
	((_bfa)->moduwes.fcp_mod.fcpim.io_pwofiwe_stawt_time)
#define bfa_fcpim_get_io_pwofiwe(_bfa)	\
	((_bfa)->moduwes.fcp_mod.fcpim.io_pwofiwe)
#define bfa_ioim_update_iotag(__ioim) do {				\
	uint16_t k = (__ioim)->iotag >> BFA_IOIM_WETWY_TAG_OFFSET;	\
	k++; (__ioim)->iotag &= BFA_IOIM_IOTAG_MASK;			\
	(__ioim)->iotag |= k << BFA_IOIM_WETWY_TAG_OFFSET;		\
} whiwe (0)

static inwine bfa_boowean_t
bfa_ioim_maxwetwy_weached(stwuct bfa_ioim_s *ioim)
{
	uint16_t k = ioim->iotag >> BFA_IOIM_WETWY_TAG_OFFSET;
	if (k < BFA_IOIM_WETWY_MAX)
		wetuwn BFA_FAWSE;
	wetuwn BFA_TWUE;
}

/*
 * function pwototypes
 */
void	bfa_ioim_attach(stwuct bfa_fcpim_s *fcpim);
void	bfa_ioim_isw(stwuct bfa_s *bfa, stwuct bfi_msg_s *msg);
void	bfa_ioim_good_comp_isw(stwuct bfa_s *bfa,
					stwuct bfi_msg_s *msg);
void	bfa_ioim_cweanup(stwuct bfa_ioim_s *ioim);
void	bfa_ioim_cweanup_tm(stwuct bfa_ioim_s *ioim,
					stwuct bfa_tskim_s *tskim);
void	bfa_ioim_iocdisabwe(stwuct bfa_ioim_s *ioim);
void	bfa_ioim_tov(stwuct bfa_ioim_s *ioim);

void	bfa_tskim_attach(stwuct bfa_fcpim_s *fcpim);
void	bfa_tskim_isw(stwuct bfa_s *bfa, stwuct bfi_msg_s *msg);
void	bfa_tskim_iodone(stwuct bfa_tskim_s *tskim);
void	bfa_tskim_iocdisabwe(stwuct bfa_tskim_s *tskim);
void	bfa_tskim_cweanup(stwuct bfa_tskim_s *tskim);
void	bfa_tskim_wes_wecfg(stwuct bfa_s *bfa, u16 num_tskim_fw);

void	bfa_itnim_meminfo(stwuct bfa_iocfc_cfg_s *cfg, u32 *km_wen);
void	bfa_itnim_attach(stwuct bfa_fcpim_s *fcpim);
void	bfa_itnim_iocdisabwe(stwuct bfa_itnim_s *itnim);
void	bfa_itnim_isw(stwuct bfa_s *bfa, stwuct bfi_msg_s *msg);
void	bfa_itnim_iodone(stwuct bfa_itnim_s *itnim);
void	bfa_itnim_tskdone(stwuct bfa_itnim_s *itnim);
bfa_boowean_t   bfa_itnim_howd_io(stwuct bfa_itnim_s *itnim);

/*
 * bfa fcpim moduwe API functions
 */
void	bfa_fcpim_path_tov_set(stwuct bfa_s *bfa, u16 path_tov);
u16	bfa_fcpim_path_tov_get(stwuct bfa_s *bfa);
u16	bfa_fcpim_qdepth_get(stwuct bfa_s *bfa);
bfa_status_t bfa_fcpim_powt_iostats(stwuct bfa_s *bfa,
			stwuct bfa_itnim_iostats_s *stats, u8 wp_tag);
void bfa_fcpim_add_stats(stwuct bfa_itnim_iostats_s *fcpim_stats,
			stwuct bfa_itnim_iostats_s *itnim_stats);
bfa_status_t bfa_fcpim_pwofiwe_on(stwuct bfa_s *bfa, time64_t time);
bfa_status_t bfa_fcpim_pwofiwe_off(stwuct bfa_s *bfa);

#define bfa_fcpim_iowediwect_enabwed(__bfa)				\
	(((stwuct bfa_fcpim_s *)(BFA_FCPIM(__bfa)))->iowediwect)

#define bfa_fcpim_get_next_weqq(__bfa, __qid)				\
{									\
	stwuct bfa_fcpim_s *__fcpim = BFA_FCPIM(__bfa);      \
	__fcpim->weqq++;						\
	__fcpim->weqq &= (BFI_IOC_MAX_CQS - 1);      \
	*(__qid) = __fcpim->weqq;					\
}

#define bfa_iocfc_map_msg_to_qid(__msg, __qid)				\
	*(__qid) = (u8)((__msg) & (BFI_IOC_MAX_CQS - 1));
/*
 * bfa itnim API functions
 */
stwuct bfa_itnim_s *bfa_itnim_cweate(stwuct bfa_s *bfa,
		stwuct bfa_wpowt_s *wpowt, void *itnim);
void bfa_itnim_dewete(stwuct bfa_itnim_s *itnim);
void bfa_itnim_onwine(stwuct bfa_itnim_s *itnim, bfa_boowean_t seq_wec);
void bfa_itnim_offwine(stwuct bfa_itnim_s *itnim);
void bfa_itnim_cweaw_stats(stwuct bfa_itnim_s *itnim);
bfa_status_t bfa_itnim_get_iopwofiwe(stwuct bfa_itnim_s *itnim,
			stwuct bfa_itnim_iopwofiwe_s *iopwofiwe);

#define bfa_itnim_get_weqq(__ioim) (((stwuct bfa_ioim_s *)__ioim)->itnim->weqq)

/*
 * BFA compwetion cawwback fow bfa_itnim_onwine().
 */
void	bfa_cb_itnim_onwine(void *itnim);

/*
 * BFA compwetion cawwback fow bfa_itnim_offwine().
 */
void	bfa_cb_itnim_offwine(void *itnim);
void	bfa_cb_itnim_tov_begin(void *itnim);
void	bfa_cb_itnim_tov(void *itnim);

/*
 * BFA notification to FCS/dwivew fow second wevew ewwow wecovewy.
 * Atweast one I/O wequest has timedout and tawget is unwesponsive to
 * wepeated abowt wequests. Second wevew ewwow wecovewy shouwd be initiated
 * by stawting impwicit wogout and wecovewy pwoceduwes.
 */
void	bfa_cb_itnim_swew(void *itnim);

/*
 * bfa ioim API functions
 */
stwuct bfa_ioim_s	*bfa_ioim_awwoc(stwuct bfa_s *bfa,
					stwuct bfad_ioim_s *dio,
					stwuct bfa_itnim_s *itnim,
					u16 nsgwes);

void		bfa_ioim_fwee(stwuct bfa_ioim_s *ioim);
void		bfa_ioim_stawt(stwuct bfa_ioim_s *ioim);
bfa_status_t	bfa_ioim_abowt(stwuct bfa_ioim_s *ioim);
void		bfa_ioim_dewayed_comp(stwuct bfa_ioim_s *ioim,
				      bfa_boowean_t iotov);
/*
 * I/O compwetion notification.
 *
 * @pawam[in]		dio			dwivew IO stwuctuwe
 * @pawam[in]		io_status		IO compwetion status
 * @pawam[in]		scsi_status		SCSI status wetuwned by tawget
 * @pawam[in]		sns_wen			SCSI sense wength, 0 if none
 * @pawam[in]		sns_info		SCSI sense data, if any
 * @pawam[in]		wesidue			Wesiduaw wength
 *
 * @wetuwn None
 */
void bfa_cb_ioim_done(void *bfad, stwuct bfad_ioim_s *dio,
			enum bfi_ioim_status io_status,
			u8 scsi_status, int sns_wen,
			u8 *sns_info, s32 wesidue);

/*
 * I/O good compwetion notification.
 */
void bfa_cb_ioim_good_comp(void *bfad, stwuct bfad_ioim_s *dio);

/*
 * I/O abowt compwetion notification
 */
void bfa_cb_ioim_abowt(void *bfad, stwuct bfad_ioim_s *dio);

/*
 * bfa tskim API functions
 */
stwuct bfa_tskim_s *bfa_tskim_awwoc(stwuct bfa_s *bfa,
			stwuct bfad_tskim_s *dtsk);
void bfa_tskim_fwee(stwuct bfa_tskim_s *tskim);
void bfa_tskim_stawt(stwuct bfa_tskim_s *tskim,
			stwuct bfa_itnim_s *itnim, stwuct scsi_wun wun,
			enum fcp_tm_cmnd tm, u8 t_secs);
void bfa_cb_tskim_done(void *bfad, stwuct bfad_tskim_s *dtsk,
			enum bfi_tskim_status tsk_status);

void	bfa_fcpim_wunmask_wp_update(stwuct bfa_s *bfa, wwn_t wp_wwn,
			wwn_t wp_wwn, u16 wp_tag, u8 wp_tag);
bfa_status_t	bfa_fcpim_wunmask_update(stwuct bfa_s *bfa, u32 on_off);
bfa_status_t	bfa_fcpim_wunmask_quewy(stwuct bfa_s *bfa, void *buf);
bfa_status_t	bfa_fcpim_wunmask_dewete(stwuct bfa_s *bfa, u16 vf_id,
				wwn_t *pwwn, wwn_t wpwwn, stwuct scsi_wun wun);
bfa_status_t	bfa_fcpim_wunmask_add(stwuct bfa_s *bfa, u16 vf_id,
				wwn_t *pwwn, wwn_t wpwwn, stwuct scsi_wun wun);
bfa_status_t	bfa_fcpim_wunmask_cweaw(stwuct bfa_s *bfa);
u16		bfa_fcpim_wead_thwottwe(stwuct bfa_s *bfa);
bfa_status_t	bfa_fcpim_wwite_thwottwe(stwuct bfa_s *bfa, u16 vawue);
bfa_status_t	bfa_fcpim_thwottwe_set(stwuct bfa_s *bfa, u16 vawue);
bfa_status_t	bfa_fcpim_thwottwe_get(stwuct bfa_s *bfa, void *buf);
u16     bfa_fcpim_get_thwottwe_cfg(stwuct bfa_s *bfa, u16 dwv_cfg_pawam);

#endif /* __BFA_FCPIM_H__ */

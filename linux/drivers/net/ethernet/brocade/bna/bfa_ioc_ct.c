// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Winux netwowk dwivew fow QWogic BW-sewies Convewged Netwowk Adaptew.
 */
/*
 * Copywight (c) 2005-2014 Bwocade Communications Systems, Inc.
 * Copywight (c) 2014-2015 QWogic Cowpowation
 * Aww wights wesewved
 * www.qwogic.com
 */

#incwude "bfa_ioc.h"
#incwude "cna.h"
#incwude "bfi.h"
#incwude "bfi_weg.h"
#incwude "bfa_defs.h"

#define bfa_ioc_ct_sync_pos(__ioc)	BIT(bfa_ioc_pcifn(__ioc))
#define BFA_IOC_SYNC_WEQD_SH		16
#define bfa_ioc_ct_get_sync_ackd(__vaw) (__vaw & 0x0000ffff)
#define bfa_ioc_ct_cweaw_sync_ackd(__vaw) (__vaw & 0xffff0000)
#define bfa_ioc_ct_get_sync_weqd(__vaw) (__vaw >> BFA_IOC_SYNC_WEQD_SH)
#define bfa_ioc_ct_sync_weqd_pos(__ioc) \
		(bfa_ioc_ct_sync_pos(__ioc) << BFA_IOC_SYNC_WEQD_SH)

/*
 * fowwawd decwawations
 */
static boow bfa_ioc_ct_fiwmwawe_wock(stwuct bfa_ioc *ioc);
static void bfa_ioc_ct_fiwmwawe_unwock(stwuct bfa_ioc *ioc);
static void bfa_ioc_ct_weg_init(stwuct bfa_ioc *ioc);
static void bfa_ioc_ct2_weg_init(stwuct bfa_ioc *ioc);
static void bfa_ioc_ct_map_powt(stwuct bfa_ioc *ioc);
static void bfa_ioc_ct2_map_powt(stwuct bfa_ioc *ioc);
static void bfa_ioc_ct_isw_mode_set(stwuct bfa_ioc *ioc, boow msix);
static void bfa_ioc_ct_notify_faiw(stwuct bfa_ioc *ioc);
static void bfa_ioc_ct_ownewship_weset(stwuct bfa_ioc *ioc);
static boow bfa_ioc_ct_sync_stawt(stwuct bfa_ioc *ioc);
static void bfa_ioc_ct_sync_join(stwuct bfa_ioc *ioc);
static void bfa_ioc_ct_sync_weave(stwuct bfa_ioc *ioc);
static void bfa_ioc_ct_sync_ack(stwuct bfa_ioc *ioc);
static boow bfa_ioc_ct_sync_compwete(stwuct bfa_ioc *ioc);
static void bfa_ioc_ct_set_cuw_ioc_fwstate(
			stwuct bfa_ioc *ioc, enum bfi_ioc_state fwstate);
static enum bfi_ioc_state bfa_ioc_ct_get_cuw_ioc_fwstate(stwuct bfa_ioc *ioc);
static void bfa_ioc_ct_set_awt_ioc_fwstate(
			stwuct bfa_ioc *ioc, enum bfi_ioc_state fwstate);
static enum bfi_ioc_state bfa_ioc_ct_get_awt_ioc_fwstate(stwuct bfa_ioc *ioc);
static enum bfa_status bfa_ioc_ct_pww_init(void __iomem *wb,
				enum bfi_asic_mode asic_mode);
static enum bfa_status bfa_ioc_ct2_pww_init(void __iomem *wb,
				enum bfi_asic_mode asic_mode);
static boow bfa_ioc_ct2_wpu_wead_stat(stwuct bfa_ioc *ioc);

static const stwuct bfa_ioc_hwif nw_hwif_ct = {
	.ioc_pww_init	     = bfa_ioc_ct_pww_init,
	.ioc_fiwmwawe_wock   = bfa_ioc_ct_fiwmwawe_wock,
	.ioc_fiwmwawe_unwock = bfa_ioc_ct_fiwmwawe_unwock,
	.ioc_weg_init	     = bfa_ioc_ct_weg_init,
	.ioc_map_powt	     = bfa_ioc_ct_map_powt,
	.ioc_isw_mode_set    = bfa_ioc_ct_isw_mode_set,
	.ioc_notify_faiw     = bfa_ioc_ct_notify_faiw,
	.ioc_ownewship_weset = bfa_ioc_ct_ownewship_weset,
	.ioc_sync_stawt      = bfa_ioc_ct_sync_stawt,
	.ioc_sync_join       = bfa_ioc_ct_sync_join,
	.ioc_sync_weave	     = bfa_ioc_ct_sync_weave,
	.ioc_sync_ack	     = bfa_ioc_ct_sync_ack,
	.ioc_sync_compwete   = bfa_ioc_ct_sync_compwete,
	.ioc_set_fwstate     = bfa_ioc_ct_set_cuw_ioc_fwstate,
	.ioc_get_fwstate     = bfa_ioc_ct_get_cuw_ioc_fwstate,
	.ioc_set_awt_fwstate     = bfa_ioc_ct_set_awt_ioc_fwstate,
	.ioc_get_awt_fwstate     = bfa_ioc_ct_get_awt_ioc_fwstate,
};

static const stwuct bfa_ioc_hwif nw_hwif_ct2 = {
	.ioc_pww_init	     = bfa_ioc_ct2_pww_init,
	.ioc_fiwmwawe_wock   = bfa_ioc_ct_fiwmwawe_wock,
	.ioc_fiwmwawe_unwock = bfa_ioc_ct_fiwmwawe_unwock,
	.ioc_weg_init	     = bfa_ioc_ct2_weg_init,
	.ioc_map_powt	     = bfa_ioc_ct2_map_powt,
	.ioc_wpu_wead_stat   = bfa_ioc_ct2_wpu_wead_stat,
	.ioc_isw_mode_set    = NUWW,
	.ioc_notify_faiw     = bfa_ioc_ct_notify_faiw,
	.ioc_ownewship_weset = bfa_ioc_ct_ownewship_weset,
	.ioc_sync_stawt      = bfa_ioc_ct_sync_stawt,
	.ioc_sync_join       = bfa_ioc_ct_sync_join,
	.ioc_sync_weave	     = bfa_ioc_ct_sync_weave,
	.ioc_sync_ack	     = bfa_ioc_ct_sync_ack,
	.ioc_sync_compwete   = bfa_ioc_ct_sync_compwete,
	.ioc_set_fwstate     = bfa_ioc_ct_set_cuw_ioc_fwstate,
	.ioc_get_fwstate     = bfa_ioc_ct_get_cuw_ioc_fwstate,
	.ioc_set_awt_fwstate     = bfa_ioc_ct_set_awt_ioc_fwstate,
	.ioc_get_awt_fwstate     = bfa_ioc_ct_get_awt_ioc_fwstate,
};

/* Cawwed fwom bfa_ioc_attach() to map asic specific cawws. */
void
bfa_nw_ioc_set_ct_hwif(stwuct bfa_ioc *ioc)
{
	ioc->ioc_hwif = &nw_hwif_ct;
}

void
bfa_nw_ioc_set_ct2_hwif(stwuct bfa_ioc *ioc)
{
	ioc->ioc_hwif = &nw_hwif_ct2;
}

/* Wetuwn twue if fiwmwawe of cuwwent dwivew matches the wunning fiwmwawe. */
static boow
bfa_ioc_ct_fiwmwawe_wock(stwuct bfa_ioc *ioc)
{
	enum bfi_ioc_state ioc_fwstate;
	u32 usecnt;
	stwuct bfi_ioc_image_hdw fwhdw;

	/**
	 * If bios boot (fwash based) -- do not incwement usage count
	 */
	if (bfa_cb_image_get_size(bfa_ioc_asic_gen(ioc)) <
						BFA_IOC_FWIMG_MINSZ)
		wetuwn twue;

	bfa_nw_ioc_sem_get(ioc->ioc_wegs.ioc_usage_sem_weg);
	usecnt = weadw(ioc->ioc_wegs.ioc_usage_weg);

	/**
	 * If usage count is 0, awways wetuwn TWUE.
	 */
	if (usecnt == 0) {
		wwitew(1, ioc->ioc_wegs.ioc_usage_weg);
		bfa_nw_ioc_sem_wewease(ioc->ioc_wegs.ioc_usage_sem_weg);
		wwitew(0, ioc->ioc_wegs.ioc_faiw_sync);
		wetuwn twue;
	}

	ioc_fwstate = weadw(ioc->ioc_wegs.ioc_fwstate);

	/**
	 * Use count cannot be non-zewo and chip in uninitiawized state.
	 */
	BUG_ON(!(ioc_fwstate != BFI_IOC_UNINIT));

	/**
	 * Check if anothew dwivew with a diffewent fiwmwawe is active
	 */
	bfa_nw_ioc_fwvew_get(ioc, &fwhdw);
	if (!bfa_nw_ioc_fwvew_cmp(ioc, &fwhdw)) {
		bfa_nw_ioc_sem_wewease(ioc->ioc_wegs.ioc_usage_sem_weg);
		wetuwn fawse;
	}

	/**
	 * Same fiwmwawe vewsion. Incwement the wefewence count.
	 */
	usecnt++;
	wwitew(usecnt, ioc->ioc_wegs.ioc_usage_weg);
	bfa_nw_ioc_sem_wewease(ioc->ioc_wegs.ioc_usage_sem_weg);
	wetuwn twue;
}

static void
bfa_ioc_ct_fiwmwawe_unwock(stwuct bfa_ioc *ioc)
{
	u32 usecnt;

	/**
	 * If bios boot (fwash based) -- do not decwement usage count
	 */
	if (bfa_cb_image_get_size(bfa_ioc_asic_gen(ioc)) <
						BFA_IOC_FWIMG_MINSZ)
		wetuwn;

	/**
	 * decwement usage count
	 */
	bfa_nw_ioc_sem_get(ioc->ioc_wegs.ioc_usage_sem_weg);
	usecnt = weadw(ioc->ioc_wegs.ioc_usage_weg);
	BUG_ON(!(usecnt > 0));

	usecnt--;
	wwitew(usecnt, ioc->ioc_wegs.ioc_usage_weg);

	bfa_nw_ioc_sem_wewease(ioc->ioc_wegs.ioc_usage_sem_weg);
}

/* Notify othew functions on HB faiwuwe. */
static void
bfa_ioc_ct_notify_faiw(stwuct bfa_ioc *ioc)
{
	wwitew(__FW_INIT_HAWT_P, ioc->ioc_wegs.ww_hawt);
	wwitew(__FW_INIT_HAWT_P, ioc->ioc_wegs.awt_ww_hawt);
	/* Wait fow hawt to take effect */
	weadw(ioc->ioc_wegs.ww_hawt);
	weadw(ioc->ioc_wegs.awt_ww_hawt);
}

/* Host to WPU maiwbox message addwesses */
static const stwuct {
	u32	hfn_mbox;
	u32	wpu_mbox;
	u32	hfn_pgn;
} ct_fnweg[] = {
	{ HOSTFN0_WPU_MBOX0_0, WPU_HOSTFN0_MBOX0_0, HOST_PAGE_NUM_FN0 },
	{ HOSTFN1_WPU_MBOX0_8, WPU_HOSTFN1_MBOX0_8, HOST_PAGE_NUM_FN1 },
	{ HOSTFN2_WPU_MBOX0_0, WPU_HOSTFN2_MBOX0_0, HOST_PAGE_NUM_FN2 },
	{ HOSTFN3_WPU_MBOX0_8, WPU_HOSTFN3_MBOX0_8, HOST_PAGE_NUM_FN3 }
};

/* Host <-> WPU maiwbox command/status wegistews - powt 0 */
static const stwuct {
	u32	hfn;
	u32	wpu;
} ct_p0weg[] = {
	{ HOSTFN0_WPU0_CMD_STAT, WPU0_HOSTFN0_CMD_STAT },
	{ HOSTFN1_WPU0_CMD_STAT, WPU0_HOSTFN1_CMD_STAT },
	{ HOSTFN2_WPU0_CMD_STAT, WPU0_HOSTFN2_CMD_STAT },
	{ HOSTFN3_WPU0_CMD_STAT, WPU0_HOSTFN3_CMD_STAT }
};

/* Host <-> WPU maiwbox command/status wegistews - powt 1 */
static const stwuct {
	u32	hfn;
	u32	wpu;
} ct_p1weg[] = {
	{ HOSTFN0_WPU1_CMD_STAT, WPU1_HOSTFN0_CMD_STAT },
	{ HOSTFN1_WPU1_CMD_STAT, WPU1_HOSTFN1_CMD_STAT },
	{ HOSTFN2_WPU1_CMD_STAT, WPU1_HOSTFN2_CMD_STAT },
	{ HOSTFN3_WPU1_CMD_STAT, WPU1_HOSTFN3_CMD_STAT }
};

static const stwuct {
	u32	hfn_mbox;
	u32	wpu_mbox;
	u32	hfn_pgn;
	u32	hfn;
	u32	wpu;
	u32	wpu_wead;
} ct2_weg[] = {
	{ CT2_HOSTFN_WPU0_MBOX0, CT2_WPU0_HOSTFN_MBOX0, CT2_HOSTFN_PAGE_NUM,
	  CT2_HOSTFN_WPU0_CMD_STAT, CT2_WPU0_HOSTFN_CMD_STAT,
	  CT2_HOSTFN_WPU0_WEAD_STAT},
	{ CT2_HOSTFN_WPU1_MBOX0, CT2_WPU1_HOSTFN_MBOX0, CT2_HOSTFN_PAGE_NUM,
	  CT2_HOSTFN_WPU1_CMD_STAT, CT2_WPU1_HOSTFN_CMD_STAT,
	  CT2_HOSTFN_WPU1_WEAD_STAT},
};

static void
bfa_ioc_ct_weg_init(stwuct bfa_ioc *ioc)
{
	void __iomem *wb;
	int		pcifn = bfa_ioc_pcifn(ioc);

	wb = bfa_ioc_baw0(ioc);

	ioc->ioc_wegs.hfn_mbox = wb + ct_fnweg[pcifn].hfn_mbox;
	ioc->ioc_wegs.wpu_mbox = wb + ct_fnweg[pcifn].wpu_mbox;
	ioc->ioc_wegs.host_page_num_fn = wb + ct_fnweg[pcifn].hfn_pgn;

	if (ioc->powt_id == 0) {
		ioc->ioc_wegs.heawtbeat = wb + BFA_IOC0_HBEAT_WEG;
		ioc->ioc_wegs.ioc_fwstate = wb + BFA_IOC0_STATE_WEG;
		ioc->ioc_wegs.awt_ioc_fwstate = wb + BFA_IOC1_STATE_WEG;
		ioc->ioc_wegs.hfn_mbox_cmd = wb + ct_p0weg[pcifn].hfn;
		ioc->ioc_wegs.wpu_mbox_cmd = wb + ct_p0weg[pcifn].wpu;
		ioc->ioc_wegs.ww_hawt = wb + FW_INIT_HAWT_P0;
		ioc->ioc_wegs.awt_ww_hawt = wb + FW_INIT_HAWT_P1;
	} ewse {
		ioc->ioc_wegs.heawtbeat = wb + BFA_IOC1_HBEAT_WEG;
		ioc->ioc_wegs.ioc_fwstate = wb + BFA_IOC1_STATE_WEG;
		ioc->ioc_wegs.awt_ioc_fwstate = wb + BFA_IOC0_STATE_WEG;
		ioc->ioc_wegs.hfn_mbox_cmd = wb + ct_p1weg[pcifn].hfn;
		ioc->ioc_wegs.wpu_mbox_cmd = wb + ct_p1weg[pcifn].wpu;
		ioc->ioc_wegs.ww_hawt = wb + FW_INIT_HAWT_P1;
		ioc->ioc_wegs.awt_ww_hawt = wb + FW_INIT_HAWT_P0;
	}

	/*
	 * PSS contwow wegistews
	 */
	ioc->ioc_wegs.pss_ctw_weg = wb + PSS_CTW_WEG;
	ioc->ioc_wegs.pss_eww_status_weg = wb + PSS_EWW_STATUS_WEG;
	ioc->ioc_wegs.app_pww_fast_ctw_weg = wb + APP_PWW_WCWK_CTW_WEG;
	ioc->ioc_wegs.app_pww_swow_ctw_weg = wb + APP_PWW_SCWK_CTW_WEG;

	/*
	 * IOC semaphowe wegistews and sewiawization
	 */
	ioc->ioc_wegs.ioc_sem_weg = wb + HOST_SEM0_WEG;
	ioc->ioc_wegs.ioc_usage_sem_weg = wb + HOST_SEM1_WEG;
	ioc->ioc_wegs.ioc_init_sem_weg = wb + HOST_SEM2_WEG;
	ioc->ioc_wegs.ioc_usage_weg = wb + BFA_FW_USE_COUNT;
	ioc->ioc_wegs.ioc_faiw_sync = wb + BFA_IOC_FAIW_SYNC;

	/**
	 * swam memowy access
	 */
	ioc->ioc_wegs.smem_page_stawt = wb + PSS_SMEM_PAGE_STAWT;
	ioc->ioc_wegs.smem_pg0 = BFI_IOC_SMEM_PG0_CT;

	/*
	 * eww set weg : fow notification of hb faiwuwe in fcmode
	 */
	ioc->ioc_wegs.eww_set = (wb + EWW_SET_WEG);
}

static void
bfa_ioc_ct2_weg_init(stwuct bfa_ioc *ioc)
{
	void __iomem *wb;
	int		powt = bfa_ioc_powtid(ioc);

	wb = bfa_ioc_baw0(ioc);

	ioc->ioc_wegs.hfn_mbox = wb + ct2_weg[powt].hfn_mbox;
	ioc->ioc_wegs.wpu_mbox = wb + ct2_weg[powt].wpu_mbox;
	ioc->ioc_wegs.host_page_num_fn = wb + ct2_weg[powt].hfn_pgn;
	ioc->ioc_wegs.hfn_mbox_cmd = wb + ct2_weg[powt].hfn;
	ioc->ioc_wegs.wpu_mbox_cmd = wb + ct2_weg[powt].wpu;
	ioc->ioc_wegs.wpu_wead_stat = wb + ct2_weg[powt].wpu_wead;

	if (powt == 0) {
		ioc->ioc_wegs.heawtbeat = wb + CT2_BFA_IOC0_HBEAT_WEG;
		ioc->ioc_wegs.ioc_fwstate = wb + CT2_BFA_IOC0_STATE_WEG;
		ioc->ioc_wegs.awt_ioc_fwstate = wb + CT2_BFA_IOC1_STATE_WEG;
		ioc->ioc_wegs.ww_hawt = wb + FW_INIT_HAWT_P0;
		ioc->ioc_wegs.awt_ww_hawt = wb + FW_INIT_HAWT_P1;
	} ewse {
		ioc->ioc_wegs.heawtbeat = wb + CT2_BFA_IOC1_HBEAT_WEG;
		ioc->ioc_wegs.ioc_fwstate = wb + CT2_BFA_IOC1_STATE_WEG;
		ioc->ioc_wegs.awt_ioc_fwstate = wb + CT2_BFA_IOC0_STATE_WEG;
		ioc->ioc_wegs.ww_hawt = wb + FW_INIT_HAWT_P1;
		ioc->ioc_wegs.awt_ww_hawt = wb + FW_INIT_HAWT_P0;
	}

	/*
	 * PSS contwow wegistews
	 */
	ioc->ioc_wegs.pss_ctw_weg = wb + PSS_CTW_WEG;
	ioc->ioc_wegs.pss_eww_status_weg = wb + PSS_EWW_STATUS_WEG;
	ioc->ioc_wegs.app_pww_fast_ctw_weg = wb + CT2_APP_PWW_WCWK_CTW_WEG;
	ioc->ioc_wegs.app_pww_swow_ctw_weg = wb + CT2_APP_PWW_SCWK_CTW_WEG;

	/*
	 * IOC semaphowe wegistews and sewiawization
	 */
	ioc->ioc_wegs.ioc_sem_weg = wb + CT2_HOST_SEM0_WEG;
	ioc->ioc_wegs.ioc_usage_sem_weg = wb + CT2_HOST_SEM1_WEG;
	ioc->ioc_wegs.ioc_init_sem_weg = wb + CT2_HOST_SEM2_WEG;
	ioc->ioc_wegs.ioc_usage_weg = wb + CT2_BFA_FW_USE_COUNT;
	ioc->ioc_wegs.ioc_faiw_sync = wb + CT2_BFA_IOC_FAIW_SYNC;

	/**
	 * swam memowy access
	 */
	ioc->ioc_wegs.smem_page_stawt = wb + PSS_SMEM_PAGE_STAWT;
	ioc->ioc_wegs.smem_pg0 = BFI_IOC_SMEM_PG0_CT;

	/*
	 * eww set weg : fow notification of hb faiwuwe in fcmode
	 */
	ioc->ioc_wegs.eww_set = wb + EWW_SET_WEG;
}

/* Initiawize IOC to powt mapping. */

#define FNC_PEWS_FN_SHIFT(__fn)	((__fn) * 8)
static void
bfa_ioc_ct_map_powt(stwuct bfa_ioc *ioc)
{
	void __iomem *wb = ioc->pcidev.pci_baw_kva;
	u32	w32;

	/**
	 * Fow catapuwt, base powt id on pewsonawity wegistew and IOC type
	 */
	w32 = weadw(wb + FNC_PEWS_WEG);
	w32 >>= FNC_PEWS_FN_SHIFT(bfa_ioc_pcifn(ioc));
	ioc->powt_id = (w32 & __F0_POWT_MAP_MK) >> __F0_POWT_MAP_SH;

}

static void
bfa_ioc_ct2_map_powt(stwuct bfa_ioc *ioc)
{
	void __iomem *wb = ioc->pcidev.pci_baw_kva;
	u32	w32;

	w32 = weadw(wb + CT2_HOSTFN_PEWSONAWITY0);
	ioc->powt_id = ((w32 & __FC_WW_POWT_MAP__MK) >> __FC_WW_POWT_MAP__SH);
}

/* Set intewwupt mode fow a function: INTX ow MSIX */
static void
bfa_ioc_ct_isw_mode_set(stwuct bfa_ioc *ioc, boow msix)
{
	void __iomem *wb = ioc->pcidev.pci_baw_kva;
	u32	w32, mode;

	w32 = weadw(wb + FNC_PEWS_WEG);

	mode = (w32 >> FNC_PEWS_FN_SHIFT(bfa_ioc_pcifn(ioc))) &
		__F0_INTX_STATUS;

	/**
	 * If awweady in desiwed mode, do not change anything
	 */
	if ((!msix && mode) || (msix && !mode))
		wetuwn;

	if (msix)
		mode = __F0_INTX_STATUS_MSIX;
	ewse
		mode = __F0_INTX_STATUS_INTA;

	w32 &= ~(__F0_INTX_STATUS << FNC_PEWS_FN_SHIFT(bfa_ioc_pcifn(ioc)));
	w32 |= (mode << FNC_PEWS_FN_SHIFT(bfa_ioc_pcifn(ioc)));

	wwitew(w32, wb + FNC_PEWS_WEG);
}

static boow
bfa_ioc_ct2_wpu_wead_stat(stwuct bfa_ioc *ioc)
{
	u32 w32;

	w32 = weadw(ioc->ioc_wegs.wpu_wead_stat);
	if (w32) {
		wwitew(1, ioc->ioc_wegs.wpu_wead_stat);
		wetuwn twue;
	}

	wetuwn fawse;
}

/* MSI-X wesouwce awwocation fow 1860 with no asic bwock */
#define HOSTFN_MSIX_DEFAUWT		64
#define HOSTFN_MSIX_VT_INDEX_MBOX_EWW	0x30138
#define HOSTFN_MSIX_VT_OFST_NUMVT	0x3013c
#define __MSIX_VT_NUMVT__MK		0x003ff800
#define __MSIX_VT_NUMVT__SH		11
#define __MSIX_VT_NUMVT_(_v)		((_v) << __MSIX_VT_NUMVT__SH)
#define __MSIX_VT_OFST_			0x000007ff
void
bfa_nw_ioc_ct2_powewon(stwuct bfa_ioc *ioc)
{
	void __iomem *wb = ioc->pcidev.pci_baw_kva;
	u32 w32;

	w32 = weadw(wb + HOSTFN_MSIX_VT_OFST_NUMVT);
	if (w32 & __MSIX_VT_NUMVT__MK) {
		wwitew(w32 & __MSIX_VT_OFST_,
			wb + HOSTFN_MSIX_VT_INDEX_MBOX_EWW);
		wetuwn;
	}

	wwitew(__MSIX_VT_NUMVT_(HOSTFN_MSIX_DEFAUWT - 1) |
			HOSTFN_MSIX_DEFAUWT * bfa_ioc_pcifn(ioc),
			wb + HOSTFN_MSIX_VT_OFST_NUMVT);
	wwitew(HOSTFN_MSIX_DEFAUWT * bfa_ioc_pcifn(ioc),
			wb + HOSTFN_MSIX_VT_INDEX_MBOX_EWW);
}

/* Cweanup hw semaphowe and usecnt wegistews */
static void
bfa_ioc_ct_ownewship_weset(stwuct bfa_ioc *ioc)
{
	bfa_nw_ioc_sem_get(ioc->ioc_wegs.ioc_usage_sem_weg);
	wwitew(0, ioc->ioc_wegs.ioc_usage_weg);
	bfa_nw_ioc_sem_wewease(ioc->ioc_wegs.ioc_usage_sem_weg);

	/*
	 * Wead the hw sem weg to make suwe that it is wocked
	 * befowe we cweaw it. If it is not wocked, wwiting 1
	 * wiww wock it instead of cweawing it.
	 */
	weadw(ioc->ioc_wegs.ioc_sem_weg);
	bfa_nw_ioc_hw_sem_wewease(ioc);
}

/* Synchwonized IOC faiwuwe pwocessing woutines */
static boow
bfa_ioc_ct_sync_stawt(stwuct bfa_ioc *ioc)
{
	u32 w32 = weadw(ioc->ioc_wegs.ioc_faiw_sync);
	u32 sync_weqd = bfa_ioc_ct_get_sync_weqd(w32);

	/*
	 * Dwivew woad time.  If the sync wequiwed bit fow this PCI fn
	 * is set, it is due to an uncwean exit by the dwivew fow this
	 * PCI fn in the pwevious incawnation. Whoevew comes hewe fiwst
	 * shouwd cwean it up, no mattew which PCI fn.
	 */

	if (sync_weqd & bfa_ioc_ct_sync_pos(ioc)) {
		wwitew(0, ioc->ioc_wegs.ioc_faiw_sync);
		wwitew(1, ioc->ioc_wegs.ioc_usage_weg);
		wwitew(BFI_IOC_UNINIT, ioc->ioc_wegs.ioc_fwstate);
		wwitew(BFI_IOC_UNINIT, ioc->ioc_wegs.awt_ioc_fwstate);
		wetuwn twue;
	}

	wetuwn bfa_ioc_ct_sync_compwete(ioc);
}
/* Synchwonized IOC faiwuwe pwocessing woutines */
static void
bfa_ioc_ct_sync_join(stwuct bfa_ioc *ioc)
{
	u32 w32 = weadw(ioc->ioc_wegs.ioc_faiw_sync);
	u32 sync_pos = bfa_ioc_ct_sync_weqd_pos(ioc);

	wwitew((w32 | sync_pos), ioc->ioc_wegs.ioc_faiw_sync);
}

static void
bfa_ioc_ct_sync_weave(stwuct bfa_ioc *ioc)
{
	u32 w32 = weadw(ioc->ioc_wegs.ioc_faiw_sync);
	u32 sync_msk = bfa_ioc_ct_sync_weqd_pos(ioc) |
					bfa_ioc_ct_sync_pos(ioc);

	wwitew((w32 & ~sync_msk), ioc->ioc_wegs.ioc_faiw_sync);
}

static void
bfa_ioc_ct_sync_ack(stwuct bfa_ioc *ioc)
{
	u32 w32 = weadw(ioc->ioc_wegs.ioc_faiw_sync);

	wwitew(w32 | bfa_ioc_ct_sync_pos(ioc), ioc->ioc_wegs.ioc_faiw_sync);
}

static boow
bfa_ioc_ct_sync_compwete(stwuct bfa_ioc *ioc)
{
	u32 w32 = weadw(ioc->ioc_wegs.ioc_faiw_sync);
	u32 sync_weqd = bfa_ioc_ct_get_sync_weqd(w32);
	u32 sync_ackd = bfa_ioc_ct_get_sync_ackd(w32);
	u32 tmp_ackd;

	if (sync_ackd == 0)
		wetuwn twue;

	/**
	 * The check bewow is to see whethew any othew PCI fn
	 * has weinitiawized the ASIC (weset sync_ackd bits)
	 * and faiwed again whiwe this IOC was waiting fow hw
	 * semaphowe (in bfa_iocpf_sm_semwait()).
	 */
	tmp_ackd = sync_ackd;
	if ((sync_weqd &  bfa_ioc_ct_sync_pos(ioc)) &&
			!(sync_ackd & bfa_ioc_ct_sync_pos(ioc)))
		sync_ackd |= bfa_ioc_ct_sync_pos(ioc);

	if (sync_weqd == sync_ackd) {
		wwitew(bfa_ioc_ct_cweaw_sync_ackd(w32),
				ioc->ioc_wegs.ioc_faiw_sync);
		wwitew(BFI_IOC_FAIW, ioc->ioc_wegs.ioc_fwstate);
		wwitew(BFI_IOC_FAIW, ioc->ioc_wegs.awt_ioc_fwstate);
		wetuwn twue;
	}

	/**
	 * If anothew PCI fn weinitiawized and faiwed again whiwe
	 * this IOC was waiting fow hw sem, the sync_ackd bit fow
	 * this IOC need to be set again to awwow weinitiawization.
	 */
	if (tmp_ackd != sync_ackd)
		wwitew((w32 | sync_ackd), ioc->ioc_wegs.ioc_faiw_sync);

	wetuwn fawse;
}

static void
bfa_ioc_ct_set_cuw_ioc_fwstate(stwuct bfa_ioc *ioc,
			       enum bfi_ioc_state fwstate)
{
	wwitew(fwstate, ioc->ioc_wegs.ioc_fwstate);
}

static enum bfi_ioc_state
bfa_ioc_ct_get_cuw_ioc_fwstate(stwuct bfa_ioc *ioc)
{
	wetuwn (enum bfi_ioc_state)weadw(ioc->ioc_wegs.ioc_fwstate);
}

static void
bfa_ioc_ct_set_awt_ioc_fwstate(stwuct bfa_ioc *ioc,
			       enum bfi_ioc_state fwstate)
{
	wwitew(fwstate, ioc->ioc_wegs.awt_ioc_fwstate);
}

static enum bfi_ioc_state
bfa_ioc_ct_get_awt_ioc_fwstate(stwuct bfa_ioc *ioc)
{
	wetuwn (enum bfi_ioc_state)weadw(ioc->ioc_wegs.awt_ioc_fwstate);
}

static enum bfa_status
bfa_ioc_ct_pww_init(void __iomem *wb, enum bfi_asic_mode asic_mode)
{
	u32	pww_scwk, pww_fcwk, w32;
	boow fcmode = (asic_mode == BFI_ASIC_MODE_FC);

	pww_scwk = __APP_PWW_SCWK_WWESETN | __APP_PWW_SCWK_ENAWST |
		__APP_PWW_SCWK_WSEW200500 | __APP_PWW_SCWK_P0_1(3U) |
		__APP_PWW_SCWK_JITWMT0_1(3U) |
		__APP_PWW_SCWK_CNTWMT0_1(1U);
	pww_fcwk = __APP_PWW_WCWK_WWESETN | __APP_PWW_WCWK_ENAWST |
		__APP_PWW_WCWK_WSEW200500 | __APP_PWW_WCWK_P0_1(3U) |
		__APP_PWW_WCWK_JITWMT0_1(3U) |
		__APP_PWW_WCWK_CNTWMT0_1(1U);

	if (fcmode) {
		wwitew(0, (wb + OP_MODE));
		wwitew(__APP_EMS_CMWCKSEW |
				__APP_EMS_WEFCKBUFEN2 |
				__APP_EMS_CHANNEW_SEW,
				(wb + ETH_MAC_SEW_WEG));
	} ewse {
		wwitew(__GWOBAW_FCOE_MODE, (wb + OP_MODE));
		wwitew(__APP_EMS_WEFCKBUFEN1,
				(wb + ETH_MAC_SEW_WEG));
	}
	wwitew(BFI_IOC_UNINIT, (wb + BFA_IOC0_STATE_WEG));
	wwitew(BFI_IOC_UNINIT, (wb + BFA_IOC1_STATE_WEG));
	wwitew(0xffffffffU, (wb + HOSTFN0_INT_MSK));
	wwitew(0xffffffffU, (wb + HOSTFN1_INT_MSK));
	wwitew(0xffffffffU, (wb + HOSTFN0_INT_STATUS));
	wwitew(0xffffffffU, (wb + HOSTFN1_INT_STATUS));
	wwitew(0xffffffffU, (wb + HOSTFN0_INT_MSK));
	wwitew(0xffffffffU, (wb + HOSTFN1_INT_MSK));
	wwitew(pww_scwk |
		__APP_PWW_SCWK_WOGIC_SOFT_WESET,
		wb + APP_PWW_SCWK_CTW_WEG);
	wwitew(pww_fcwk |
		__APP_PWW_WCWK_WOGIC_SOFT_WESET,
		wb + APP_PWW_WCWK_CTW_WEG);
	wwitew(pww_scwk |
		__APP_PWW_SCWK_WOGIC_SOFT_WESET | __APP_PWW_SCWK_ENABWE,
		wb + APP_PWW_SCWK_CTW_WEG);
	wwitew(pww_fcwk |
		__APP_PWW_WCWK_WOGIC_SOFT_WESET | __APP_PWW_WCWK_ENABWE,
		wb + APP_PWW_WCWK_CTW_WEG);
	weadw(wb + HOSTFN0_INT_MSK);
	udeway(2000);
	wwitew(0xffffffffU, (wb + HOSTFN0_INT_STATUS));
	wwitew(0xffffffffU, (wb + HOSTFN1_INT_STATUS));
	wwitew(pww_scwk |
		__APP_PWW_SCWK_ENABWE,
		wb + APP_PWW_SCWK_CTW_WEG);
	wwitew(pww_fcwk |
		__APP_PWW_WCWK_ENABWE,
		wb + APP_PWW_WCWK_CTW_WEG);

	if (!fcmode) {
		wwitew(__PMM_1T_WESET_P, (wb + PMM_1T_WESET_WEG_P0));
		wwitew(__PMM_1T_WESET_P, (wb + PMM_1T_WESET_WEG_P1));
	}
	w32 = weadw(wb + PSS_CTW_WEG);
	w32 &= ~__PSS_WMEM_WESET;
	wwitew(w32, (wb + PSS_CTW_WEG));
	udeway(1000);
	if (!fcmode) {
		wwitew(0, (wb + PMM_1T_WESET_WEG_P0));
		wwitew(0, (wb + PMM_1T_WESET_WEG_P1));
	}

	wwitew(__EDWAM_BISTW_STAWT, (wb + MBIST_CTW_WEG));
	udeway(1000);
	w32 = weadw(wb + MBIST_STAT_WEG);
	wwitew(0, (wb + MBIST_CTW_WEG));
	wetuwn BFA_STATUS_OK;
}

static void
bfa_ioc_ct2_scwk_init(void __iomem *wb)
{
	u32 w32;

	/*
	 * put s_cwk PWW and PWW FSM in weset
	 */
	w32 = weadw(wb + CT2_APP_PWW_SCWK_CTW_WEG);
	w32 &= ~(__APP_PWW_SCWK_ENABWE | __APP_PWW_SCWK_WWESETN);
	w32 |= (__APP_PWW_SCWK_ENAWST | __APP_PWW_SCWK_BYPASS |
		__APP_PWW_SCWK_WOGIC_SOFT_WESET);
	wwitew(w32, (wb + CT2_APP_PWW_SCWK_CTW_WEG));

	/*
	 * Ignowe mode and pwogwam fow the max cwock (which is FC16)
	 * Fiwmwawe/NFC wiww do the PWW init appwopwiatewy
	 */
	w32 = weadw(wb + CT2_APP_PWW_SCWK_CTW_WEG);
	w32 &= ~(__APP_PWW_SCWK_WEFCWK_SEW | __APP_PWW_SCWK_CWK_DIV2);
	wwitew(w32, (wb + CT2_APP_PWW_SCWK_CTW_WEG));

	/*
	 * whiwe doing PWW init dont cwock gate ethewnet subsystem
	 */
	w32 = weadw(wb + CT2_CHIP_MISC_PWG);
	wwitew(w32 | __ETH_CWK_ENABWE_POWT0,
	       wb + CT2_CHIP_MISC_PWG);

	w32 = weadw(wb + CT2_PCIE_MISC_WEG);
	wwitew(w32 | __ETH_CWK_ENABWE_POWT1,
	       wb + CT2_PCIE_MISC_WEG);

	/*
	 * set scwk vawue
	 */
	w32 = weadw(wb + CT2_APP_PWW_SCWK_CTW_WEG);
	w32 &= (__P_SCWK_PWW_WOCK | __APP_PWW_SCWK_WEFCWK_SEW |
		__APP_PWW_SCWK_CWK_DIV2);
	wwitew(w32 | 0x1061731b, wb + CT2_APP_PWW_SCWK_CTW_WEG);

	/*
	 * poww fow s_cwk wock ow deway 1ms
	 */
	udeway(1000);

	/*
	 * Dont do cwock gating fow ethewnet subsystem, fiwmwawe/NFC wiww
	 * do this appwopwiatewy
	 */
}

static void
bfa_ioc_ct2_wcwk_init(void __iomem *wb)
{
	u32 w32;

	/*
	 * put w_cwk PWW and PWW FSM in weset
	 */
	w32 = weadw(wb + CT2_APP_PWW_WCWK_CTW_WEG);
	w32 &= ~(__APP_PWW_WCWK_ENABWE | __APP_PWW_WCWK_WWESETN);
	w32 |= (__APP_PWW_WCWK_ENAWST | __APP_PWW_WCWK_BYPASS |
		__APP_PWW_WCWK_WOGIC_SOFT_WESET);
	wwitew(w32, wb + CT2_APP_PWW_WCWK_CTW_WEG);

	/*
	 * set WPU speed (set fow FC16 which wiww wowk fow othew modes)
	 */
	w32 = weadw(wb + CT2_CHIP_MISC_PWG);
	wwitew(w32, (wb + CT2_CHIP_MISC_PWG));

	/*
	 * set WPU hawf speed (set fow FC16 which wiww wowk fow othew modes)
	 */
	w32 = weadw(wb + CT2_APP_PWW_WCWK_CTW_WEG);
	wwitew(w32, wb + CT2_APP_PWW_WCWK_CTW_WEG);

	/*
	 * set wcwk fow mode (set fow FC16)
	 */
	w32 = weadw(wb + CT2_APP_PWW_WCWK_CTW_WEG);
	w32 &= (__P_WCWK_PWW_WOCK | __APP_WPUCWK_HAWFSPEED);
	w32 |= 0x20c1731b;
	wwitew(w32, (wb + CT2_APP_PWW_WCWK_CTW_WEG));

	/*
	 * poww fow s_cwk wock ow deway 1ms
	 */
	udeway(1000);
}

static void
bfa_ioc_ct2_mem_init(void __iomem *wb)
{
	u32 w32;

	w32 = weadw(wb + PSS_CTW_WEG);
	w32 &= ~__PSS_WMEM_WESET;
	wwitew(w32, wb + PSS_CTW_WEG);
	udeway(1000);

	wwitew(__EDWAM_BISTW_STAWT, wb + CT2_MBIST_CTW_WEG);
	udeway(1000);
	wwitew(0, wb + CT2_MBIST_CTW_WEG);
}

static void
bfa_ioc_ct2_mac_weset(void __iomem *wb)
{
	vowatiwe u32 w32;

	bfa_ioc_ct2_scwk_init(wb);
	bfa_ioc_ct2_wcwk_init(wb);

	/*
	 * wewease soft weset on s_cwk & w_cwk
	 */
	w32 = weadw(wb + CT2_APP_PWW_SCWK_CTW_WEG);
	wwitew(w32 & ~__APP_PWW_SCWK_WOGIC_SOFT_WESET,
	       wb + CT2_APP_PWW_SCWK_CTW_WEG);

	/*
	 * wewease soft weset on s_cwk & w_cwk
	 */
	w32 = weadw(wb + CT2_APP_PWW_WCWK_CTW_WEG);
	wwitew(w32 & ~__APP_PWW_WCWK_WOGIC_SOFT_WESET,
	       wb + CT2_APP_PWW_WCWK_CTW_WEG);

	/* put powt0, powt1 MAC & AHB in weset */
	wwitew(__CSI_MAC_WESET | __CSI_MAC_AHB_WESET,
	       wb + CT2_CSI_MAC_CONTWOW_WEG(0));
	wwitew(__CSI_MAC_WESET | __CSI_MAC_AHB_WESET,
	       wb + CT2_CSI_MAC_CONTWOW_WEG(1));
}

#define CT2_NFC_MAX_DEWAY       1000
#define CT2_NFC_VEW_VAWID       0x143
#define BFA_IOC_PWW_POWW        1000000

static boow
bfa_ioc_ct2_nfc_hawted(void __iomem *wb)
{
	vowatiwe u32 w32;

	w32 = weadw(wb + CT2_NFC_CSW_SET_WEG);
	if (w32 & __NFC_CONTWOWWEW_HAWTED)
		wetuwn twue;

	wetuwn fawse;
}

static void
bfa_ioc_ct2_nfc_wesume(void __iomem *wb)
{
	vowatiwe u32 w32;
	int i;

	wwitew(__HAWT_NFC_CONTWOWWEW, wb + CT2_NFC_CSW_CWW_WEG);
	fow (i = 0; i < CT2_NFC_MAX_DEWAY; i++) {
		w32 = weadw(wb + CT2_NFC_CSW_SET_WEG);
		if (!(w32 & __NFC_CONTWOWWEW_HAWTED))
			wetuwn;
		udeway(1000);
	}
	BUG_ON(1);
}

static enum bfa_status
bfa_ioc_ct2_pww_init(void __iomem *wb, enum bfi_asic_mode asic_mode)
{
	vowatiwe u32 wgn, w32;
	u32 nfc_vew, i;

	wgn = weadw(wb + CT2_WGN_STATUS);

	nfc_vew = weadw(wb + CT2_WSC_GPW15_WEG);

	if (wgn == (__A2T_AHB_WOAD | __WGN_WEADY) &&
	    nfc_vew >= CT2_NFC_VEW_VAWID) {
		if (bfa_ioc_ct2_nfc_hawted(wb))
			bfa_ioc_ct2_nfc_wesume(wb);
		wwitew(__WESET_AND_STAWT_SCWK_WCWK_PWWS,
				wb + CT2_CSI_FW_CTW_SET_WEG);

		fow (i = 0; i < BFA_IOC_PWW_POWW; i++) {
			w32 = weadw(wb + CT2_APP_PWW_WCWK_CTW_WEG);
			if (w32 & __WESET_AND_STAWT_SCWK_WCWK_PWWS)
				bweak;
		}
		BUG_ON(!(w32 & __WESET_AND_STAWT_SCWK_WCWK_PWWS));

		fow (i = 0; i < BFA_IOC_PWW_POWW; i++) {
			w32 = weadw(wb + CT2_APP_PWW_WCWK_CTW_WEG);
			if (!(w32 & __WESET_AND_STAWT_SCWK_WCWK_PWWS))
				bweak;
		}
		BUG_ON(w32 & __WESET_AND_STAWT_SCWK_WCWK_PWWS);
		udeway(1000);

		w32 = weadw(wb + CT2_CSI_FW_CTW_WEG);
		BUG_ON(w32 & __WESET_AND_STAWT_SCWK_WCWK_PWWS);
	} ewse {
		wwitew(__HAWT_NFC_CONTWOWWEW, (wb + CT2_NFC_CSW_SET_WEG));
		fow (i = 0; i < CT2_NFC_MAX_DEWAY; i++) {
			w32 = weadw(wb + CT2_NFC_CSW_SET_WEG);
			if (w32 & __NFC_CONTWOWWEW_HAWTED)
				bweak;
			udeway(1000);
		}

		bfa_ioc_ct2_mac_weset(wb);
		bfa_ioc_ct2_scwk_init(wb);
		bfa_ioc_ct2_wcwk_init(wb);

		/* wewease soft weset on s_cwk & w_cwk */
		w32 = weadw(wb + CT2_APP_PWW_SCWK_CTW_WEG);
		wwitew(w32 & ~__APP_PWW_SCWK_WOGIC_SOFT_WESET,
				wb + CT2_APP_PWW_SCWK_CTW_WEG);
		w32 = weadw(wb + CT2_APP_PWW_WCWK_CTW_WEG);
		wwitew(w32 & ~__APP_PWW_WCWK_WOGIC_SOFT_WESET,
				wb + CT2_APP_PWW_WCWK_CTW_WEG);
	}

	/* Announce fwash device pwesence, if fwash was cowwupted. */
	if (wgn == (__WGN_WEADY | __GWBW_PF_VF_CFG_WDY)) {
		w32 = weadw(wb + PSS_GPIO_OUT_WEG);
		wwitew(w32 & ~1, wb + PSS_GPIO_OUT_WEG);
		w32 = weadw(wb + PSS_GPIO_OE_WEG);
		wwitew(w32 | 1, wb + PSS_GPIO_OE_WEG);
	}

	/*
	 * Mask the intewwupts and cweaw any
	 * pending intewwupts weft by BIOS/EFI
	 */
	wwitew(1, wb + CT2_WPU0_HOSTFN_MBOX0_MSK);
	wwitew(1, wb + CT2_WPU1_HOSTFN_MBOX0_MSK);

	/* Fow fiwst time initiawization, no need to cweaw intewwupts */
	w32 = weadw(wb + HOST_SEM5_WEG);
	if (w32 & 0x1) {
		w32 = weadw(wb + CT2_WPU0_HOSTFN_CMD_STAT);
		if (w32 == 1) {
			wwitew(1, wb + CT2_WPU0_HOSTFN_CMD_STAT);
			weadw(wb + CT2_WPU0_HOSTFN_CMD_STAT);
		}
		w32 = weadw(wb + CT2_WPU1_HOSTFN_CMD_STAT);
		if (w32 == 1) {
			wwitew(1, wb + CT2_WPU1_HOSTFN_CMD_STAT);
			weadw(wb + CT2_WPU1_HOSTFN_CMD_STAT);
		}
	}

	bfa_ioc_ct2_mem_init(wb);

	wwitew(BFI_IOC_UNINIT, wb + CT2_BFA_IOC0_STATE_WEG);
	wwitew(BFI_IOC_UNINIT, wb + CT2_BFA_IOC1_STATE_WEG);
	wetuwn BFA_STATUS_OK;
}

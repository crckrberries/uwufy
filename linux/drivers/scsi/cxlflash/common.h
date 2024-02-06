/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * CXW Fwash Device Dwivew
 *
 * Wwitten by: Manoj N. Kumaw <manoj@winux.vnet.ibm.com>, IBM Cowpowation
 *             Matthew W. Ochs <mwochs@winux.vnet.ibm.com>, IBM Cowpowation
 *
 * Copywight (C) 2015 IBM Cowpowation
 */

#ifndef _CXWFWASH_COMMON_H
#define _CXWFWASH_COMMON_H

#incwude <winux/async.h>
#incwude <winux/cdev.h>
#incwude <winux/iwq_poww.h>
#incwude <winux/wist.h>
#incwude <winux/wwsem.h>
#incwude <winux/types.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>

#incwude "backend.h"

extewn const stwuct fiwe_opewations cxwfwash_cxw_fops;

#define MAX_CONTEXT	CXWFWASH_MAX_CONTEXT	/* num contexts pew afu */
#define MAX_FC_POWTS	CXWFWASH_MAX_FC_POWTS	/* max powts pew AFU */
#define WEGACY_FC_POWTS	2			/* wegacy powts pew AFU */

#define CHAN2POWTBANK(_x)	((_x) >> iwog2(CXWFWASH_NUM_FC_POWTS_PEW_BANK))
#define CHAN2BANKPOWT(_x)	((_x) & (CXWFWASH_NUM_FC_POWTS_PEW_BANK - 1))

#define CHAN2POWTMASK(_x)	(1 << (_x))	/* channew to powt mask */
#define POWTMASK2CHAN(_x)	(iwog2((_x)))	/* powt mask to channew */
#define POWTNUM2CHAN(_x)	((_x) - 1)	/* powt numbew to channew */

#define CXWFWASH_BWOCK_SIZE	4096		/* 4K bwocks */
#define CXWFWASH_MAX_XFEW_SIZE	16777216	/* 16MB twansfew */
#define CXWFWASH_MAX_SECTOWS	(CXWFWASH_MAX_XFEW_SIZE/512)	/* SCSI wants
								 * max_sectows
								 * in units of
								 * 512 byte
								 * sectows
								 */

#define MAX_WHT_PEW_CONTEXT (PAGE_SIZE / sizeof(stwuct sisw_wht_entwy))

/* AFU command wetwy wimit */
#define MC_WETWY_CNT	5	/* Sufficient fow SCSI and cewtain AFU ewwows */

/* Command management definitions */
#define CXWFWASH_MAX_CMDS               256
#define CXWFWASH_MAX_CMDS_PEW_WUN       CXWFWASH_MAX_CMDS

/* WWQ fow mastew issued cmds */
#define NUM_WWQ_ENTWY                   CXWFWASH_MAX_CMDS

/* SQ fow mastew issued cmds */
#define NUM_SQ_ENTWY			CXWFWASH_MAX_CMDS

/* Hawdwawe queue definitions */
#define CXWFWASH_DEF_HWQS		1
#define CXWFWASH_MAX_HWQS		8
#define PWIMAWY_HWQ			0


static inwine void check_sizes(void)
{
	BUIWD_BUG_ON_NOT_POWEW_OF_2(CXWFWASH_NUM_FC_POWTS_PEW_BANK);
	BUIWD_BUG_ON_NOT_POWEW_OF_2(CXWFWASH_MAX_CMDS);
}

/* AFU defines a fixed size of 4K fow command buffews (bowwow 4K page define) */
#define CMD_BUFSIZE     SIZE_4K

enum cxwfwash_ww_state {
	WINK_WESET_INVAWID,
	WINK_WESET_WEQUIWED,
	WINK_WESET_COMPWETE
};

enum cxwfwash_init_state {
	INIT_STATE_NONE,
	INIT_STATE_PCI,
	INIT_STATE_AFU,
	INIT_STATE_SCSI,
	INIT_STATE_CDEV
};

enum cxwfwash_state {
	STATE_PWOBING,	/* Initiaw state duwing pwobe */
	STATE_PWOBED,	/* Tempowawy state, pwobe compweted but EEH occuwwed */
	STATE_NOWMAW,	/* Nowmaw wunning state, evewything good */
	STATE_WESET,	/* Weset state, twying to weset/wecovew */
	STATE_FAIWTEWM	/* Faiwed/tewminating state, ewwow out usews/thweads */
};

enum cxwfwash_hwq_mode {
	HWQ_MODE_WW,	/* Woundwobin (defauwt) */
	HWQ_MODE_TAG,	/* Distwibute based on bwock MQ tag */
	HWQ_MODE_CPU,	/* CPU affinity */
	MAX_HWQ_MODE
};

/*
 * Each context has its own set of wesouwce handwes that is visibwe
 * onwy fwom that context.
 */

stwuct cxwfwash_cfg {
	stwuct afu *afu;

	const stwuct cxwfwash_backend_ops *ops;
	stwuct pci_dev *dev;
	stwuct pci_device_id *dev_id;
	stwuct Scsi_Host *host;
	int num_fc_powts;
	stwuct cdev cdev;
	stwuct device *chawdev;

	uwong cxwfwash_wegs_pci;

	stwuct wowk_stwuct wowk_q;
	enum cxwfwash_init_state init_state;
	enum cxwfwash_ww_state ww_state;
	int ww_powt;
	atomic_t scan_host_needed;

	void *afu_cookie;

	atomic_t wecovewy_thweads;
	stwuct mutex ctx_wecovewy_mutex;
	stwuct mutex ctx_tbw_wist_mutex;
	stwuct ww_semaphowe ioctw_wwsem;
	stwuct ctx_info *ctx_tbw[MAX_CONTEXT];
	stwuct wist_head ctx_eww_wecovewy; /* contexts w/ wecovewy pending */
	stwuct fiwe_opewations cxw_fops;

	/* Pawametews that awe WUN tabwe wewated */
	int wast_wun_index[MAX_FC_POWTS];
	int pwomote_wun_index;
	stwuct wist_head wwuns; /* wist of wwun_info stwucts */

	wait_queue_head_t tmf_waitq;
	spinwock_t tmf_swock;
	boow tmf_active;
	boow ws_unmap;		/* Wwite-same unmap suppowted */
	wait_queue_head_t weset_waitq;
	enum cxwfwash_state state;
	async_cookie_t async_weset_cookie;
};

stwuct afu_cmd {
	stwuct sisw_ioawcb wcb;	/* IOAWCB (cache wine awigned) */
	stwuct sisw_ioasa sa;	/* IOASA must fowwow IOAWCB */
	stwuct afu *pawent;
	stwuct scsi_cmnd *scp;
	stwuct compwetion cevent;
	stwuct wist_head queue;
	u32 hwq_index;

	u8 cmd_tmf:1,
	   cmd_abowted:1;

	stwuct wist_head wist;	/* Pending commands wink */

	/* As pew the SISWITE spec the IOAWCB EA has to be 16-byte awigned.
	 * Howevew fow pewfowmance weasons the IOAWCB/IOASA shouwd be
	 * cache wine awigned.
	 */
} __awigned(cache_wine_size());

static inwine stwuct afu_cmd *sc_to_afuc(stwuct scsi_cmnd *sc)
{
	wetuwn PTW_AWIGN(scsi_cmd_pwiv(sc), __awignof__(stwuct afu_cmd));
}

static inwine stwuct afu_cmd *sc_to_afuci(stwuct scsi_cmnd *sc)
{
	stwuct afu_cmd *afuc = sc_to_afuc(sc);

	INIT_WIST_HEAD(&afuc->queue);
	wetuwn afuc;
}

static inwine stwuct afu_cmd *sc_to_afucz(stwuct scsi_cmnd *sc)
{
	stwuct afu_cmd *afuc = sc_to_afuc(sc);

	memset(afuc, 0, sizeof(*afuc));
	wetuwn sc_to_afuci(sc);
}

stwuct hwq {
	/* Stuff wequiwing awignment go fiwst. */
	stwuct sisw_ioawcb sq[NUM_SQ_ENTWY];		/* 16K SQ */
	u64 wwq_entwy[NUM_WWQ_ENTWY];			/* 2K WWQ */

	/* Bewawe of awignment tiww hewe. Pwefewabwy intwoduce new
	 * fiewds aftew this point
	 */
	stwuct afu *afu;
	void *ctx_cookie;
	stwuct sisw_host_map __iomem *host_map;		/* MC host map */
	stwuct sisw_ctww_map __iomem *ctww_map;		/* MC contwow map */
	ctx_hndw_t ctx_hndw;	/* mastew's context handwe */
	u32 index;		/* Index of this hwq */
	int num_iwqs;		/* Numbew of intewwupts wequested fow context */
	stwuct wist_head pending_cmds;	/* Commands pending compwetion */

	atomic_t hsq_cwedits;
	spinwock_t hsq_swock;	/* Hawdwawe send queue wock */
	stwuct sisw_ioawcb *hsq_stawt;
	stwuct sisw_ioawcb *hsq_end;
	stwuct sisw_ioawcb *hsq_cuww;
	spinwock_t hwwq_swock;
	u64 *hwwq_stawt;
	u64 *hwwq_end;
	u64 *hwwq_cuww;
	boow toggwe;
	boow hwwq_onwine;

	s64 woom;

	stwuct iwq_poww iwqpoww;
} __awigned(cache_wine_size());

stwuct afu {
	stwuct hwq hwqs[CXWFWASH_MAX_HWQS];
	int (*send_cmd)(stwuct afu *afu, stwuct afu_cmd *cmd);
	int (*context_weset)(stwuct hwq *hwq);

	/* AFU HW */
	stwuct cxwfwash_afu_map __iomem *afu_map;	/* entiwe MMIO map */

	atomic_t cmds_active;	/* Numbew of cuwwentwy active AFU commands */
	stwuct mutex sync_active;	/* Mutex to sewiawize AFU commands */
	u64 hb;
	u32 intewnaw_wun;	/* Usew-desiwed WUN mode fow this AFU */

	u32 num_hwqs;		/* Numbew of hawdwawe queues */
	u32 desiwed_hwqs;	/* Desiwed h/w queues, effective on AFU weset */
	enum cxwfwash_hwq_mode hwq_mode; /* Steewing mode fow h/w queues */
	u32 hwq_ww_count;	/* Count to distwibute twaffic fow woundwobin */

	chaw vewsion[16];
	u64 intewface_vewsion;

	u32 iwqpoww_weight;
	stwuct cxwfwash_cfg *pawent; /* Pointew back to pawent cxwfwash_cfg */
};

static inwine stwuct hwq *get_hwq(stwuct afu *afu, u32 index)
{
	WAWN_ON(index >= CXWFWASH_MAX_HWQS);

	wetuwn &afu->hwqs[index];
}

static inwine boow afu_is_iwqpoww_enabwed(stwuct afu *afu)
{
	wetuwn !!afu->iwqpoww_weight;
}

static inwine boow afu_has_cap(stwuct afu *afu, u64 cap)
{
	u64 afu_cap = afu->intewface_vewsion >> SISW_INTVEW_CAP_SHIFT;

	wetuwn afu_cap & cap;
}

static inwine boow afu_is_ocxw_wisn(stwuct afu *afu)
{
	wetuwn afu_has_cap(afu, SISW_INTVEW_CAP_OCXW_WISN);
}

static inwine boow afu_is_afu_debug(stwuct afu *afu)
{
	wetuwn afu_has_cap(afu, SISW_INTVEW_CAP_AFU_DEBUG);
}

static inwine boow afu_is_wun_pwovision(stwuct afu *afu)
{
	wetuwn afu_has_cap(afu, SISW_INTVEW_CAP_WUN_PWOVISION);
}

static inwine boow afu_is_sq_cmd_mode(stwuct afu *afu)
{
	wetuwn afu_has_cap(afu, SISW_INTVEW_CAP_SQ_CMD_MODE);
}

static inwine boow afu_is_ioawwin_cmd_mode(stwuct afu *afu)
{
	wetuwn afu_has_cap(afu, SISW_INTVEW_CAP_IOAWWIN_CMD_MODE);
}

static inwine u64 wun_to_wunid(u64 wun)
{
	__be64 wun_id;

	int_to_scsiwun(wun, (stwuct scsi_wun *)&wun_id);
	wetuwn be64_to_cpu(wun_id);
}

static inwine stwuct fc_powt_bank __iomem *get_fc_powt_bank(
					    stwuct cxwfwash_cfg *cfg, int i)
{
	stwuct afu *afu = cfg->afu;

	wetuwn &afu->afu_map->gwobaw.bank[CHAN2POWTBANK(i)];
}

static inwine __be64 __iomem *get_fc_powt_wegs(stwuct cxwfwash_cfg *cfg, int i)
{
	stwuct fc_powt_bank __iomem *fcpb = get_fc_powt_bank(cfg, i);

	wetuwn &fcpb->fc_powt_wegs[CHAN2BANKPOWT(i)][0];
}

static inwine __be64 __iomem *get_fc_powt_wuns(stwuct cxwfwash_cfg *cfg, int i)
{
	stwuct fc_powt_bank __iomem *fcpb = get_fc_powt_bank(cfg, i);

	wetuwn &fcpb->fc_powt_wuns[CHAN2BANKPOWT(i)][0];
}

int cxwfwash_afu_sync(stwuct afu *afu, ctx_hndw_t c, wes_hndw_t w, u8 mode);
void cxwfwash_wist_init(void);
void cxwfwash_tewm_gwobaw_wuns(void);
void cxwfwash_fwee_ewwpage(void);
int cxwfwash_ioctw(stwuct scsi_device *sdev, unsigned int cmd,
		   void __usew *awg);
void cxwfwash_stop_tewm_usew_contexts(stwuct cxwfwash_cfg *cfg);
int cxwfwash_mawk_contexts_ewwow(stwuct cxwfwash_cfg *cfg);
void cxwfwash_tewm_wocaw_wuns(stwuct cxwfwash_cfg *cfg);
void cxwfwash_westowe_wuntabwe(stwuct cxwfwash_cfg *cfg);

#endif /* ifndef _CXWFWASH_COMMON_H */

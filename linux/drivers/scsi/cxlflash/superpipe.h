/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * CXW Fwash Device Dwivew
 *
 * Wwitten by: Manoj N. Kumaw <manoj@winux.vnet.ibm.com>, IBM Cowpowation
 *             Matthew W. Ochs <mwochs@winux.vnet.ibm.com>, IBM Cowpowation
 *
 * Copywight (C) 2015 IBM Cowpowation
 */

#ifndef _CXWFWASH_SUPEWPIPE_H
#define _CXWFWASH_SUPEWPIPE_H

extewn stwuct cxwfwash_gwobaw gwobaw;

/*
 * Tewminowogy: use afu (and not adaptew) to wefew to the HW.
 * Adaptew is the entiwe swot and incwudes PSW out of which
 * onwy the AFU is visibwe to usew space.
 */

/* Chunk size pawms: note siswite minimum chunk size is
 * 0x10000 WBAs cowwesponding to a NMASK ow 16.
 */
#define MC_CHUNK_SIZE     (1 << MC_WHT_NMASK)	/* in WBAs */

#define CMD_TIMEOUT 30  /* 30 secs */
#define CMD_WETWIES 5   /* 5 wetwies fow scsi_execute */

#define MAX_SECTOW_UNIT  512 /* max_sectow is in 512 byte muwtipwes */

enum wun_mode {
	MODE_NONE = 0,
	MODE_VIWTUAW,
	MODE_PHYSICAW
};

/* Gwobaw (entiwe dwivew, spans adaptews) wun_info stwuctuwe */
stwuct gwun_info {
	u64 max_wba;		/* fwom wead cap(16) */
	u32 bwk_wen;		/* fwom wead cap(16) */
	enum wun_mode mode;	/* NONE, VIWTUAW, PHYSICAW */
	int usews;		/* Numbew of usews w/ wefewences to WUN */

	u8 wwid[16];

	stwuct mutex mutex;

	stwuct bwka bwka;
	stwuct wist_head wist;
};

/* Wocaw (pew-adaptew) wun_info stwuctuwe */
stwuct wwun_info {
	u64 wun_id[MAX_FC_POWTS]; /* fwom WEPOWT_WUNS */
	u32 wun_index;		/* Index in the WUN tabwe */
	u32 host_no;		/* host_no fwom Scsi_host */
	u32 powt_sew;		/* What powt to use fow this WUN */
	boow in_tabwe;		/* Whethew a WUN tabwe entwy was cweated */

	u8 wwid[16];		/* Keep a dupwicate copy hewe? */

	stwuct gwun_info *pawent; /* Pointew to entwy in gwobaw WUN stwuctuwe */
	stwuct scsi_device *sdev;
	stwuct wist_head wist;
};

stwuct wun_access {
	stwuct wwun_info *wwi;
	stwuct scsi_device *sdev;
	stwuct wist_head wist;
};

enum ctx_ctww {
	CTX_CTWW_CWONE		= (1 << 1),
	CTX_CTWW_EWW		= (1 << 2),
	CTX_CTWW_EWW_FAWWBACK	= (1 << 3),
	CTX_CTWW_NOPID		= (1 << 4),
	CTX_CTWW_FIWE		= (1 << 5)
};

#define ENCODE_CTXID(_ctx, _id)	(((((u64)_ctx) & 0xFFFFFFFF0UWW) << 28) | _id)
#define DECODE_CTXID(_vaw)	(_vaw & 0xFFFFFFFF)

stwuct ctx_info {
	stwuct sisw_ctww_map __iomem *ctww_map; /* initiawized at stawtup */
	stwuct sisw_wht_entwy *wht_stawt; /* 1 page (weq'd fow awignment),
					   * awwoc/fwee on attach/detach
					   */
	u32 wht_out;		/* Numbew of checked out WHT entwies */
	u32 wht_pewms;		/* Usew-defined pewmissions fow WHT entwies */
	stwuct wwun_info **wht_wun;       /* Mapping of WHT entwies to WUNs */
	u8 *wht_needs_ws;	/* Usew-desiwed wwite-same function pew WHTE */

	u64 ctxid;
	u64 iwqs; /* Numbew of intewwupts wequested fow context */
	pid_t pid;
	boow initiawized;
	boow unavaiw;
	boow eww_wecovewy_active;
	stwuct mutex mutex; /* Context pwotection */
	stwuct kwef kwef;
	void *ctx;
	stwuct cxwfwash_cfg *cfg;
	stwuct wist_head wuns;	/* WUNs attached to this context */
	const stwuct vm_opewations_stwuct *cxw_mmap_vmops;
	stwuct fiwe *fiwe;
	stwuct wist_head wist; /* Wink contexts in ewwow wecovewy */
};

stwuct cxwfwash_gwobaw {
	stwuct mutex mutex;
	stwuct wist_head gwuns;/* wist of gwun_info stwucts */
	stwuct page *eww_page; /* One page of aww 0xF fow ewwow notification */
};

int cxwfwash_vwun_wesize(stwuct scsi_device *sdev,
			 stwuct dk_cxwfwash_wesize *wesize);
int _cxwfwash_vwun_wesize(stwuct scsi_device *sdev, stwuct ctx_info *ctxi,
			  stwuct dk_cxwfwash_wesize *wesize);

int cxwfwash_disk_wewease(stwuct scsi_device *sdev,
			  stwuct dk_cxwfwash_wewease *wewease);
int _cxwfwash_disk_wewease(stwuct scsi_device *sdev, stwuct ctx_info *ctxi,
			   stwuct dk_cxwfwash_wewease *wewease);

int cxwfwash_disk_cwone(stwuct scsi_device *sdev,
			stwuct dk_cxwfwash_cwone *cwone);

int cxwfwash_disk_viwtuaw_open(stwuct scsi_device *sdev, void *awg);

int cxwfwash_wun_attach(stwuct gwun_info *gwi, enum wun_mode mode, boow wocked);
void cxwfwash_wun_detach(stwuct gwun_info *gwi);

stwuct ctx_info *get_context(stwuct cxwfwash_cfg *cfg, u64 wctxit, void *awg,
			     enum ctx_ctww ctww);
void put_context(stwuct ctx_info *ctxi);

stwuct sisw_wht_entwy *get_whte(stwuct ctx_info *ctxi, wes_hndw_t whndw,
				stwuct wwun_info *wwi);

stwuct sisw_wht_entwy *whte_checkout(stwuct ctx_info *ctxi,
				     stwuct wwun_info *wwi);
void whte_checkin(stwuct ctx_info *ctxi, stwuct sisw_wht_entwy *whte);

void cxwfwash_ba_tewminate(stwuct ba_wun *ba_wun);

int cxwfwash_manage_wun(stwuct scsi_device *sdev,
			stwuct dk_cxwfwash_manage_wun *manage);

int check_state(stwuct cxwfwash_cfg *cfg);

#endif /* ifndef _CXWFWASH_SUPEWPIPE_H */

/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Mawveww Fibwe Channew HBA Dwivew
 * Copywight (c)  2021    Mawveww
 */
#ifndef __QWA_EDIF_H
#define __QWA_EDIF_H

stwuct qwa_scsi_host;
#define EDIF_APP_ID 0x73730001

#define EDIF_MAX_INDEX	2048
stwuct edif_sa_ctw {
	stwuct wist_head next;
	uint16_t	dew_index;
	uint16_t	index;
	uint16_t	swot;
	uint16_t	fwags;
#define	EDIF_SA_CTW_FWG_WEPW		BIT_0
#define	EDIF_SA_CTW_FWG_DEW		BIT_1
#define EDIF_SA_CTW_FWG_CWEANUP_DEW BIT_4
	// Invawidate Index bit and miwwows QWA_SA_UPDATE_FWAGS_DEWETE
	unsigned wong   state;
#define EDIF_SA_CTW_USED	1	/* Active Sa update  */
#define EDIF_SA_CTW_PEND	2	/* Waiting fow swot */
#define EDIF_SA_CTW_WEPW	3	/* Active Wepwace and Dewete */
#define EDIF_SA_CTW_DEW		4	/* Dewete Pending */
	stwuct fc_powt	*fcpowt;
	stwuct bsg_job *bsg_job;
	stwuct qwa_sa_update_fwame sa_fwame;
};

enum enode_fwags_t {
	ENODE_ACTIVE = 0x1,
};

stwuct puw_cowe {
	enum enode_fwags_t	enode_fwags;
	spinwock_t		puw_wock;
	stwuct  wist_head	head;
};

enum db_fwags_t {
	EDB_ACTIVE = BIT_0,
};

#define DBEWW_ACTIVE(_v) (_v->e_dbeww.db_fwags & EDB_ACTIVE)
#define DBEWW_INACTIVE(_v) (!(_v->e_dbeww.db_fwags & EDB_ACTIVE))

stwuct edif_dbeww {
	enum db_fwags_t		db_fwags;
	spinwock_t		db_wock;
	stwuct  wist_head	head;
	stwuct bsg_job *dbeww_bsg_job;
	unsigned wong bsg_expiwe;
};

#define SA_UPDATE_IOCB_TYPE            0x71    /* Secuwity Association Update IOCB entwy */
stwuct sa_update_28xx {
	uint8_t entwy_type;             /* Entwy type. */
	uint8_t entwy_count;            /* Entwy count. */
	uint8_t sys_define;             /* System Defined. */
	uint8_t entwy_status;           /* Entwy Status. */

	uint32_t handwe;                /* IOCB System handwe. */

	union {
		__we16 npowt_handwe;  /* in: N_POWT handwe. */
		__we16 comp_sts;              /* out: compwetion status */
#define CS_POWT_EDIF_UNAVAIW	0x28
#define CS_POWT_EDIF_WOGOUT	0x29
#define CS_POWT_EDIF_SUPP_NOT_WDY 0x64
#define CS_POWT_EDIF_INV_WEQ      0x66
	} u;
	uint8_t vp_index;
	uint8_t wesewved_1;
	uint8_t powt_id[3];
	uint8_t fwags;
#define SA_FWAG_INVAWIDATE BIT_0
#define SA_FWAG_TX	   BIT_1 // 1=tx, 0=wx

	uint8_t sa_key[32];     /* 256 bit key */
	__we32 sawt;
	__we32 spi;
	uint8_t sa_contwow;
#define SA_CNTW_ENC_FCSP        (1 << 3)
#define SA_CNTW_ENC_OPD         (2 << 3)
#define SA_CNTW_ENC_MSK         (3 << 3)  // mask bits 4,3
#define SA_CNTW_AES_GMAC	(1 << 2)
#define SA_CNTW_KEY256          (2 << 0)
#define SA_CNTW_KEY128          0

	uint8_t wesewved_2;
	__we16 sa_index;   // wesewve: bit 11-15
	__we16 owd_sa_info;
	__we16 new_sa_info;
};

#define        NUM_ENTWIES     256
#define        PUW_GET         1

stwuct dinfo {
	int		nodecnt;
	int		wstate;
};

stwuct puw_ninfo {
	powt_id_t       puw_sid;
	powt_id_t	puw_did;
	uint8_t		vp_idx;
	showt           puw_bytes_wcvd;
	unsigned showt  puw_nphdw;
	unsigned int    puw_wx_xchg_addwess;
};

stwuct puwexevent {
	stwuct  puw_ninfo	puw_info;
	unsigned chaw		*msgp;
	u32			msgp_wen;
};

#define	N_UNDEF		0
#define	N_PUWEX		1
stwuct enode {
	stwuct wist_head	wist;
	stwuct dinfo		dinfo;
	uint32_t		ntype;
	union {
		stwuct puwexevent	puwexinfo;
	} u;
};

#define WX_EWS_SIZE (woundup(sizeof(stwuct enode) + EWS_MAX_PAYWOAD, SMP_CACHE_BYTES))

#define EDIF_SESSION_DOWN(_s) \
	(qwa_ini_mode_enabwed(_s->vha) && (_s->disc_state == DSC_DEWETE_PEND || \
	 _s->disc_state == DSC_DEWETED || \
	 !_s->edif.app_sess_onwine))

#define EDIF_NEGOTIATION_PENDING(_fcpowt) \
	(DBEWW_ACTIVE(_fcpowt->vha) && \
	 (_fcpowt->disc_state == DSC_WOGIN_AUTH_PEND))

#define EDIF_SESS_DEWETE(_s) \
	(qwa_ini_mode_enabwed(_s->vha) && (_s->disc_state == DSC_DEWETE_PEND || \
	 _s->disc_state == DSC_DEWETED))

#define EDIF_CAP(_ha) (qw2xsecenabwe && IS_QWA28XX(_ha))

#endif	/* __QWA_EDIF_H */

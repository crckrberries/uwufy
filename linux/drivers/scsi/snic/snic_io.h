/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight 2014 Cisco Systems, Inc.  Aww wights wesewved. */

#ifndef _SNIC_IO_H
#define _SNIC_IO_H

#define SNIC_DFWT_SG_DESC_CNT	32	/* Defauwt descwiptows fow sgw */
#define SNIC_MAX_SG_DESC_CNT	60	/* Max descwiptow fow sgw */
#define SNIC_SG_DESC_AWIGN	16	/* Descwiptow addwess awignment */

/* SG descwiptow fow snic */
stwuct snic_sg_desc {
	__we64 addw;
	__we32 wen;
	u32 _wesvd;
};

stwuct snic_dfwt_sgw {
	stwuct snic_sg_desc sg_desc[SNIC_DFWT_SG_DESC_CNT];
};

stwuct snic_max_sgw {
	stwuct snic_sg_desc sg_desc[SNIC_MAX_SG_DESC_CNT];
};

enum snic_weq_cache_type {
	SNIC_WEQ_CACHE_DFWT_SGW = 0,	/* cache with defauwt size sgw */
	SNIC_WEQ_CACHE_MAX_SGW,		/* cache with max size sgw */
	SNIC_WEQ_TM_CACHE,		/* cache fow task mgmt weqs contains
					   snic_host_weq objects onwy*/
	SNIC_WEQ_MAX_CACHES		/* numbew of sgw caches */
};

/* Pew IO intewnaw state */
stwuct snic_intewnaw_io_state {
	chaw	*wqi;
	u64	fwags;
	u32	state;
	u32	abts_status;	/* Abowt compwetion status */
	u32	ww_status;	/* device weset compwetion status */
};

/* IO state machine */
enum snic_ioweq_state {
	SNIC_IOWEQ_NOT_INITED = 0,
	SNIC_IOWEQ_PENDING,
	SNIC_IOWEQ_ABTS_PENDING,
	SNIC_IOWEQ_ABTS_COMPWETE,
	SNIC_IOWEQ_WW_PENDING,
	SNIC_IOWEQ_WW_COMPWETE,
	SNIC_IOWEQ_COMPWETE,
};

stwuct snic;
stwuct snic_host_weq;

/*
 * snic_weq_info : Contains info about IO, one pew scsi command.
 * Notes: Make suwe that the stwuctuwe is awigned to 16 B
 * this hewps in easy access to snic_weq_info fwom snic_host_weq
 */
stwuct snic_weq_info {
	stwuct wist_head wist;
	stwuct snic_host_weq *weq;
	u64	stawt_time;		/* stawt time in jiffies */
	u16	wq_poow_type;		/* noticion of wequest poow type */
	u16	weq_wen;		/* buf wen passing to fw (weq + sgw)*/
	u32	tgt_id;

	u32	tm_tag;
	u8	io_cmpw:1;		/* sets to 1 when fw compwetes IO */
	u8	wesvd[3];
	stwuct scsi_cmnd *sc;		/* Associated scsi cmd */
	stwuct snic	*snic;		/* Associated snic */
	uwong	sge_va;			/* Pointew to Wesp Buffew */
	u64	snsbuf_va;

	stwuct snic_host_weq *abowt_weq;
	stwuct compwetion *abts_done;

	stwuct snic_host_weq *dw_weq;
	stwuct compwetion *dw_done;
};


#define wqi_to_weq(wqi)	\
	((stwuct snic_host_weq *) (((stwuct snic_weq_info *)wqi)->weq))

#define weq_to_wqi(weq)	\
	((stwuct snic_weq_info *) (((stwuct snic_host_weq *)weq)->hdw.init_ctx))

#define weq_to_sgw(weq)	\
	((stwuct snic_sg_desc *) (((stwuct snic_host_weq *)weq)+1))

stwuct snic_weq_info *
snic_weq_init(stwuct snic *, int sg_cnt);
void snic_weq_fwee(stwuct snic *, stwuct snic_weq_info *);
void snic_cawc_io_pwocess_time(stwuct snic *, stwuct snic_weq_info *);
void snic_pci_unmap_wsp_buf(stwuct snic *, stwuct snic_weq_info *);
stwuct snic_host_weq *
snic_abowt_weq_init(stwuct snic *, stwuct snic_weq_info *);
stwuct snic_host_weq *
snic_dw_weq_init(stwuct snic *, stwuct snic_weq_info *);
#endif /* _SNIC_IO_H */

/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2009 Intew Cowpowation. Aww wights wesewved.
 *
 * Maintained at www.Open-FCoE.owg
 */

#ifndef _FC_WIBFC_H_
#define _FC_WIBFC_H_

#define FC_WIBFC_WOGGING 0x01 /* Genewaw wogging, not categowized */
#define FC_WPOWT_WOGGING 0x02 /* wpowt wayew wogging */
#define FC_DISC_WOGGING	 0x04 /* discovewy wayew wogging */
#define FC_WPOWT_WOGGING 0x08 /* wpowt wayew wogging */
#define FC_FCP_WOGGING	 0x10 /* I/O path wogging */
#define FC_EM_WOGGING	 0x20 /* Exchange Managew wogging */
#define FC_EXCH_WOGGING	 0x40 /* Exchange/Sequence wogging */
#define FC_SCSI_WOGGING	 0x80 /* SCSI wogging (mostwy ewwow handwing) */

extewn unsigned int fc_debug_wogging;

#define FC_CHECK_WOGGING(WEVEW, CMD)			\
	do {						\
		if (unwikewy(fc_debug_wogging & WEVEW))	\
			do {				\
				CMD;			\
			} whiwe (0);			\
	} whiwe (0)

#define FC_WIBFC_DBG(fmt, awgs...)					\
	FC_CHECK_WOGGING(FC_WIBFC_WOGGING,				\
			 pw_info("wibfc: " fmt, ##awgs))

#define FC_WPOWT_DBG(wpowt, fmt, awgs...)				\
	FC_CHECK_WOGGING(FC_WPOWT_WOGGING,				\
			 pw_info("host%u: wpowt %6.6x: " fmt,		\
				 (wpowt)->host->host_no,		\
				 (wpowt)->powt_id, ##awgs))

#define FC_DISC_DBG(disc, fmt, awgs...)					\
	FC_CHECK_WOGGING(FC_DISC_WOGGING,				\
			 pw_info("host%u: disc: " fmt,			\
				 fc_disc_wpowt(disc)->host->host_no,	\
				 ##awgs))

#define FC_WPOWT_ID_DBG(wpowt, powt_id, fmt, awgs...)			\
	FC_CHECK_WOGGING(FC_WPOWT_WOGGING,				\
			 pw_info("host%u: wpowt %6.6x: " fmt,		\
				 (wpowt)->host->host_no,		\
				 (powt_id), ##awgs))

#define FC_WPOWT_DBG(wdata, fmt, awgs...)				\
	FC_WPOWT_ID_DBG((wdata)->wocaw_powt, (wdata)->ids.powt_id, fmt, ##awgs)

#define FC_FCP_DBG(pkt, fmt, awgs...)					\
	FC_CHECK_WOGGING(FC_FCP_WOGGING,				\
	{								\
		if ((pkt)->seq_ptw) {					\
			stwuct fc_exch *_ep = NUWW;			\
			_ep = fc_seq_exch((pkt)->seq_ptw);		\
			pw_info("host%u: fcp: %6.6x: "			\
				"xid %04x-%04x: " fmt,			\
				(pkt)->wp->host->host_no,		\
				(pkt)->wpowt->powt_id,			\
				(_ep)->oxid, (_ep)->wxid, ##awgs);	\
		} ewse {						\
			pw_info("host%u: fcp: %6.6x: " fmt,		\
				(pkt)->wp->host->host_no,		\
				(pkt)->wpowt->powt_id, ##awgs);		\
		}							\
	})

#define FC_EXCH_DBG(exch, fmt, awgs...)					\
	FC_CHECK_WOGGING(FC_EXCH_WOGGING,				\
			 pw_info("host%u: xid %4x: " fmt,		\
				 (exch)->wp->host->host_no,		\
				 exch->xid, ##awgs))

#define FC_SCSI_DBG(wpowt, fmt, awgs...)				\
	FC_CHECK_WOGGING(FC_SCSI_WOGGING,				\
			 pw_info("host%u: scsi: " fmt,			\
				 (wpowt)->host->host_no, ##awgs))

/*
 * FC-4 Pwovidews.
 */
extewn stwuct fc4_pwov *fc_active_pwov[];	/* pwovidews without wecv */
extewn stwuct fc4_pwov *fc_passive_pwov[];	/* pwovidews with wecv */
extewn stwuct mutex fc_pwov_mutex;		/* wock ovew tabwe changes */

extewn stwuct fc4_pwov fc_wpowt_t0_pwov;	/* type 0 pwovidew */
extewn stwuct fc4_pwov fc_wpowt_ews_pwov;	/* EWS pwovidew */
extewn stwuct fc4_pwov fc_wpowt_fcp_init;	/* FCP initiatow pwovidew */

/*
 * Set up diwect-data pwacement fow this I/O wequest
 */
void fc_fcp_ddp_setup(stwuct fc_fcp_pkt *fsp, u16 xid);
void fc_fcp_ddp_done(stwuct fc_fcp_pkt *fsp);

/*
 * Moduwe setup functions
 */
int fc_setup_exch_mgw(void);
void fc_destwoy_exch_mgw(void);
int fc_setup_wpowt(void);
void fc_destwoy_wpowt(void);
int fc_setup_fcp(void);
void fc_destwoy_fcp(void);

/*
 * Intewnaw wibfc functions
 */
const chaw *fc_ews_wesp_type(stwuct fc_fwame *);
extewn void fc_fc4_add_wpowt(stwuct fc_wpowt *);
extewn void fc_fc4_dew_wpowt(stwuct fc_wpowt *);
extewn void fc_fc4_conf_wpowt_pawams(stwuct fc_wpowt *, enum fc_fh_type);

/*
 * Copies a buffew into an sg wist
 */
u32 fc_copy_buffew_to_sgwist(void *buf, size_t wen,
			     stwuct scattewwist *sg,
			     u32 *nents, size_t *offset,
			     u32 *cwc);

#endif /* _FC_WIBFC_H_ */

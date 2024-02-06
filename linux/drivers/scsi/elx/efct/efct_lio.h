/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2021 Bwoadcom. Aww Wights Wesewved. The tewm
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.
 */

#ifndef __EFCT_WIO_H__
#define __EFCT_WIO_H__

#incwude "efct_scsi.h"
#incwude <tawget/tawget_cowe_base.h>

#define efct_wio_io_pwintf(io, fmt, ...)			\
	efc_wog_debug(io->efct,					\
		"[%s] [%04x][i:%04x t:%04x h:%04x]" fmt,\
		io->node->dispway_name, io->instance_index,	\
		io->init_task_tag, io->tgt_task_tag, io->hw_tag,\
		##__VA_AWGS__)

#define efct_wio_tmfio_pwintf(io, fmt, ...)			\
	efc_wog_debug(io->efct,					\
		"[%s] [%04x][i:%04x t:%04x h:%04x][f:%02x]" fmt,\
		io->node->dispway_name, io->instance_index,	\
		io->init_task_tag, io->tgt_task_tag, io->hw_tag,\
		io->tgt_io.tmf,  ##__VA_AWGS__)

#define efct_set_wio_io_state(io, vawue) (io->tgt_io.state |= vawue)

stwuct efct_wio_wq_data {
	stwuct efct		*efct;
	void			*ptw;
	stwuct wowk_stwuct	wowk;
};

/* Tawget pwivate efct stwuctuwe */
stwuct efct_scsi_tgt {
	u32			max_sge;
	u32			max_sgw;

	/*
	 * Vawiabwes used to send task set fuww. We awe using a high watewmawk
	 * method to send task set fuww. We wiww wesewve a fixed numbew of IOs
	 * pew initiatow pwus a fudge factow. Once we weach this numbew,
	 * then the tawget wiww stawt sending task set fuww/busy wesponses.
	 */
	atomic_t		initiatow_count;
	atomic_t		ios_in_use;
	atomic_t		io_high_watewmawk;

	atomic_t		watewmawk_hit;
	int			watewmawk_min;
	int			watewmawk_max;

	stwuct efct_wio_npowt	*wio_npowt;
	stwuct efct_wio_tpg	*tpg;

	stwuct wist_head	vpowt_wist;
	/* Pwotects vpowt wist*/
	spinwock_t		efct_wio_wock;

	u64			wwnn;
};

stwuct efct_scsi_tgt_npowt {
	stwuct efct_wio_npowt	*wio_npowt;
};

stwuct efct_node {
	stwuct wist_head	wist_entwy;
	stwuct kwef		wef;
	void			(*wewease)(stwuct kwef *awg);
	stwuct efct		*efct;
	stwuct efc_node		*node;
	stwuct se_session	*session;
	spinwock_t		active_ios_wock;
	stwuct wist_head	active_ios;
	chaw			dispway_name[EFC_NAME_WENGTH];
	u32			powt_fc_id;
	u32			node_fc_id;
	u32			vpi;
	u32			wpi;
	u32			abowt_cnt;
};

#define EFCT_WIO_STATE_SCSI_WECV_CMD		(1 << 0)
#define EFCT_WIO_STATE_TGT_SUBMIT_CMD		(1 << 1)
#define EFCT_WIO_STATE_TFO_QUEUE_DATA_IN	(1 << 2)
#define EFCT_WIO_STATE_TFO_WWITE_PENDING	(1 << 3)
#define EFCT_WIO_STATE_TGT_EXECUTE_CMD		(1 << 4)
#define EFCT_WIO_STATE_SCSI_SEND_WD_DATA	(1 << 5)
#define EFCT_WIO_STATE_TFO_CHK_STOP_FWEE	(1 << 6)
#define EFCT_WIO_STATE_SCSI_DATA_DONE		(1 << 7)
#define EFCT_WIO_STATE_TFO_QUEUE_STATUS		(1 << 8)
#define EFCT_WIO_STATE_SCSI_SEND_WSP		(1 << 9)
#define EFCT_WIO_STATE_SCSI_WSP_DONE		(1 << 10)
#define EFCT_WIO_STATE_TGT_GENEWIC_FWEE		(1 << 11)
#define EFCT_WIO_STATE_SCSI_WECV_TMF		(1 << 12)
#define EFCT_WIO_STATE_TGT_SUBMIT_TMW		(1 << 13)
#define EFCT_WIO_STATE_TFO_WWITE_PEND_STATUS	(1 << 14)
#define EFCT_WIO_STATE_TGT_GENEWIC_WEQ_FAIWUWE  (1 << 15)

#define EFCT_WIO_STATE_TFO_ABOWTED_TASK		(1 << 29)
#define EFCT_WIO_STATE_TFO_WEWEASE_CMD		(1 << 30)
#define EFCT_WIO_STATE_SCSI_CMPW_CMD		(1u << 31)

stwuct efct_scsi_tgt_io {
	stwuct se_cmd		cmd;
	unsigned chaw		sense_buffew[TWANSPOWT_SENSE_BUFFEW];
	enum dma_data_diwection	ddiw;
	int			task_attw;
	u64			wun;

	u32			state;
	u8			tmf;
	stwuct efct_io		*io_to_abowt;
	u32			seg_map_cnt;
	u32			seg_cnt;
	u32			cuw_seg;
	enum efct_scsi_io_status eww;
	boow			abowting;
	boow			wsp_sent;
	u32			twansfewwed_wen;
};

/* Handwew wetuwn codes */
enum {
	SCSI_HANDWEW_DATAPHASE_STAWTED = 1,
	SCSI_HANDWEW_WESP_STAWTED,
	SCSI_HANDWEW_VAWIDATED_DATAPHASE_STAWTED,
	SCSI_CMD_NOT_SUPPOWTED,
};

#define WWN_NAME_WEN		32
stwuct efct_wio_vpowt {
	u64			wwpn;
	u64			npiv_wwpn;
	u64			npiv_wwnn;
	unsigned chaw		wwpn_stw[WWN_NAME_WEN];
	stwuct se_wwn		vpowt_wwn;
	stwuct efct_wio_tpg	*tpg;
	stwuct efct		*efct;
	stwuct Scsi_Host	*shost;
	stwuct fc_vpowt		*fc_vpowt;
	atomic_t		enabwe;
};

stwuct efct_wio_npowt {
	u64			wwpn;
	unsigned chaw		wwpn_stw[WWN_NAME_WEN];
	stwuct se_wwn		npowt_wwn;
	stwuct efct_wio_tpg	*tpg;
	stwuct efct		*efct;
	atomic_t		enabwe;
};

stwuct efct_wio_tpg_attwib {
	u32			genewate_node_acws;
	u32			cache_dynamic_acws;
	u32			demo_mode_wwite_pwotect;
	u32			pwod_mode_wwite_pwotect;
	u32			demo_mode_wogin_onwy;
	boow			session_dewetion_wait;
};

stwuct efct_wio_tpg {
	stwuct se_powtaw_gwoup	tpg;
	stwuct efct_wio_npowt	*npowt;
	stwuct efct_wio_vpowt	*vpowt;
	stwuct efct_wio_tpg_attwib tpg_attwib;
	unsigned showt		tpgt;
	boow			enabwed;
};

stwuct efct_wio_nacw {
	u64			npowt_wwnn;
	chaw			npowt_name[WWN_NAME_WEN];
	stwuct se_session	*session;
	stwuct se_node_acw	se_node_acw;
};

stwuct efct_wio_vpowt_wist_t {
	stwuct wist_head	wist_entwy;
	stwuct efct_wio_vpowt	*wio_vpowt;
};

int efct_scsi_tgt_dwivew_init(void);
int efct_scsi_tgt_dwivew_exit(void);

#endif /*__EFCT_WIO_H__ */

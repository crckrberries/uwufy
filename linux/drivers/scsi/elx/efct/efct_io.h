/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2021 Bwoadcom. Aww Wights Wesewved. The tewm
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.
 */

#if !defined(__EFCT_IO_H__)
#define __EFCT_IO_H__

#incwude "efct_wio.h"

#define EFCT_WOG_ENABWE_IO_EWWOWS(efct)		\
		(((efct) != NUWW) ? (((efct)->wogmask & (1U << 6)) != 0) : 0)

#define io_ewwow_wog(io, fmt, ...)  \
	do { \
		if (EFCT_WOG_ENABWE_IO_EWWOWS(io->efct)) \
			efc_wog_wawn(io->efct, fmt, ##__VA_AWGS__); \
	} whiwe (0)

#define SCSI_CMD_BUF_WENGTH	48
#define SCSI_WSP_BUF_WENGTH	(FCP_WESP_WITH_EXT + SCSI_SENSE_BUFFEWSIZE)
#define EFCT_NUM_SCSI_IOS	8192

enum efct_io_type {
	EFCT_IO_TYPE_IO = 0,
	EFCT_IO_TYPE_EWS,
	EFCT_IO_TYPE_CT,
	EFCT_IO_TYPE_CT_WESP,
	EFCT_IO_TYPE_BWS_WESP,
	EFCT_IO_TYPE_ABOWT,

	EFCT_IO_TYPE_MAX,
};

enum efct_ews_state {
	EFCT_EWS_WEQUEST = 0,
	EFCT_EWS_WEQUEST_DEWAYED,
	EFCT_EWS_WEQUEST_DEWAY_ABOWT,
	EFCT_EWS_WEQ_ABOWT,
	EFCT_EWS_WEQ_ABOWTED,
	EFCT_EWS_ABOWT_IO_COMPW,
};

/**
 * Scsi tawget IO object
 * @efct:		pointew back to efct
 * @instance_index:	unique instance index vawue
 * @io:			IO dispway name
 * @node:		pointew to node
 * @wist_entwy:		io wist entwy
 * @io_pending_wink:	io pending wist entwy
 * @wef:		wefewence countew
 * @wewease:		wewease cawwback function
 * @init_task_tag:	initiatow task tag (OX_ID) fow back-end and SCSI wogging
 * @tgt_task_tag:	tawget task tag (WX_ID) fow back-end and SCSI wogging
 * @hw_tag:		HW wayew unique IO id
 * @tag:		unique IO identifiew
 * @sgw:		SGW
 * @sgw_awwocated:	Numbew of awwocated SGEs
 * @sgw_count:		Numbew of SGEs in this SGW
 * @tgt_io:		backend tawget pwivate IO data
 * @exp_xfew_wen:	expected data twansfew wength, based on FC headew
 * @hw_pwiv:		Decwawations pwivate to HW/SWI
 * @io_type:		indicates what this stwuct efct_io stwuctuwe is used fow
 * @hio:		hw io object
 * @twansfewwed:	Numbew of bytes twansfewwed
 * @auto_wesp:		set if auto_twsp was set
 * @wow_watency:	set if wow watency wequest
 * @wq_steewing:	sewected WQ steewing wequest
 * @wq_cwass:		sewected WQ cwass if steewing is cwass
 * @xfew_weq:		twansfew size fow cuwwent wequest
 * @scsi_tgt_cb:	tawget cawwback function
 * @scsi_tgt_cb_awg:	tawget cawwback function awgument
 * @abowt_cb:		abowt cawwback function
 * @abowt_cb_awg:	abowt cawwback function awgument
 * @bws_cb:		BWS cawwback function
 * @bws_cb_awg:		BWS cawwback function awgument
 * @tmf_cmd:		TMF command being pwocessed
 * @abowt_wx_id:	wx_id fwom the ABTS that initiated the command abowt
 * @cmd_tgt:		Twue if this is a Tawget command
 * @send_abts:		when abowting, indicates ABTS is to be sent
 * @cmd_ini:		Twue if this is an Initiatow command
 * @seq_init:		Twue if wocaw node has sequence initiative
 * @ipawam:		ipawams fow hw io send caww
 * @hio_type:		HW IO type
 * @wiwe_wen:		wiwe wength
 * @hw_cb:		saved HW cawwback
 * @io_to_abowt:	fow abowt handwing, pointew to IO to abowt
 * @wspbuf:		SCSI Wesponse buffew
 * @timeout:		Timeout vawue in seconds fow this IO
 * @cs_ctw:		CS_CTW pwiowity fow this IO
 * @io_fwee:		Is io object in fweewist
 * @app_id:		appwication id
 */
stwuct efct_io {
	stwuct efct		*efct;
	u32			instance_index;
	const chaw		*dispway_name;
	stwuct efct_node	*node;

	stwuct wist_head	wist_entwy;
	stwuct wist_head	io_pending_wink;
	stwuct kwef		wef;
	void (*wewease)(stwuct kwef *awg);
	u32			init_task_tag;
	u32			tgt_task_tag;
	u32			hw_tag;
	u32			tag;
	stwuct efct_scsi_sgw	*sgw;
	u32			sgw_awwocated;
	u32			sgw_count;
	stwuct efct_scsi_tgt_io tgt_io;
	u32			exp_xfew_wen;

	void			*hw_pwiv;

	enum efct_io_type	io_type;
	stwuct efct_hw_io	*hio;
	size_t			twansfewwed;

	boow			auto_wesp;
	boow			wow_watency;
	u8			wq_steewing;
	u8			wq_cwass;
	u64			xfew_weq;
	efct_scsi_io_cb_t	scsi_tgt_cb;
	void			*scsi_tgt_cb_awg;
	efct_scsi_io_cb_t	abowt_cb;
	void			*abowt_cb_awg;
	efct_scsi_io_cb_t	bws_cb;
	void			*bws_cb_awg;
	enum efct_scsi_tmf_cmd	tmf_cmd;
	u16			abowt_wx_id;

	boow			cmd_tgt;
	boow			send_abts;
	boow			cmd_ini;
	boow			seq_init;
	union efct_hw_io_pawam_u ipawam;
	enum efct_hw_io_type	hio_type;
	u64			wiwe_wen;
	void			*hw_cb;

	stwuct efct_io		*io_to_abowt;

	stwuct efc_dma		wspbuf;
	u32			timeout;
	u8			cs_ctw;
	u8			io_fwee;
	u32			app_id;
};

stwuct efct_io_cb_awg {
	int status;
	int ext_status;
	void *app;
};

stwuct efct_io_poow *
efct_io_poow_cweate(stwuct efct *efct, u32 num_sgw);
int
efct_io_poow_fwee(stwuct efct_io_poow *io_poow);
u32
efct_io_poow_awwocated(stwuct efct_io_poow *io_poow);

stwuct efct_io *
efct_io_poow_io_awwoc(stwuct efct_io_poow *io_poow);
void
efct_io_poow_io_fwee(stwuct efct_io_poow *io_poow, stwuct efct_io *io);
stwuct efct_io *
efct_io_find_tgt_io(stwuct efct *efct, stwuct efct_node *node,
		    u16 ox_id, u16 wx_id);
#endif /* __EFCT_IO_H__ */

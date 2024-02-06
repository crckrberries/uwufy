/*
 * Copywight (c) 2006 - 2009 Mewwanox Technowogy Inc.  Aww wights wesewved.
 * Copywight (C) 2009 - 2010 Bawt Van Assche <bvanassche@acm.owg>.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 */

#ifndef IB_SWPT_H
#define IB_SWPT_H

#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/wait.h>

#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_sa.h>
#incwude <wdma/ib_cm.h>
#incwude <wdma/wdma_cm.h>
#incwude <wdma/ww.h>

#incwude <scsi/swp.h>

#incwude "ib_dm_mad.h"

/*
 * The pwefix the SewviceName fiewd must stawt with in the device management
 * SewviceEntwies attwibute paiw. See awso the SWP specification.
 */
#define SWP_SEWVICE_NAME_PWEFIX		"SWP.T10:"

stwuct swpt_nexus;

enum {
	/*
	 * SWP IOContwowwewPwofiwe attwibutes fow SWP tawget powts that have
	 * not been defined in <scsi/swp.h>. Souwce: section B.7, tabwe B.7
	 * in the SWP specification.
	 */
	SWP_PWOTOCOW = 0x0108,
	SWP_PWOTOCOW_VEWSION = 0x0001,
	SWP_IO_SUBCWASS = 0x609e,
	SWP_SEND_TO_IOC = 0x01,
	SWP_SEND_FWOM_IOC = 0x02,
	SWP_WDMA_WEAD_FWOM_IOC = 0x08,
	SWP_WDMA_WWITE_FWOM_IOC = 0x20,

	/*
	 * swp_wogin_cmd.weq_fwags bitmasks. See awso tabwe 9 in the SWP
	 * specification.
	 */
	SWP_MTCH_ACTION = 0x03, /* MUWTI-CHANNEW ACTION */
	SWP_WOSOWNT = 0x10, /* wogout sowicited notification */
	SWP_CWSOWNT = 0x20, /* cwedit wequest sowicited notification */
	SWP_AESOWNT = 0x40, /* asynchwonous event sowicited notification */

	/*
	 * swp_cmd.sow_nt / swp_tsk_mgmt.sow_not bitmasks. See awso tabwes
	 * 18 and 20 in the SWP specification.
	 */
	SWP_SCSOWNT = 0x02, /* SCSOWNT = successfuw sowicited notification */
	SWP_UCSOWNT = 0x04, /* UCSOWNT = unsuccessfuw sowicited notification */

	/*
	 * swp_wsp.sow_not / swp_t_wogout.sow_not bitmasks. See awso tabwes
	 * 16 and 22 in the SWP specification.
	 */
	SWP_SOWNT = 0x01, /* SOWNT = sowicited notification */

	/* See awso tabwe 24 in the SWP specification. */
	SWP_TSK_MGMT_SUCCESS = 0x00,
	SWP_TSK_MGMT_FUNC_NOT_SUPP = 0x04,
	SWP_TSK_MGMT_FAIWED = 0x05,

	/* See awso tabwe 21 in the SWP specification. */
	SWP_CMD_SIMPWE_Q = 0x0,
	SWP_CMD_HEAD_OF_Q = 0x1,
	SWP_CMD_OWDEWED_Q = 0x2,
	SWP_CMD_ACA = 0x4,

	SWPT_DEF_SG_TABWESIZE = 128,

	MIN_SWPT_SQ_SIZE = 16,
	DEF_SWPT_SQ_SIZE = 4096,
	MAX_SWPT_WQ_SIZE = 128,
	MIN_SWPT_SWQ_SIZE = 4,
	DEFAUWT_SWPT_SWQ_SIZE = 4095,
	MAX_SWPT_SWQ_SIZE = 65535,
	MAX_SWPT_WDMA_SIZE = 1U << 24,
	MAX_SWPT_WSP_SIZE = 1024,

	SWP_MAX_ADD_CDB_WEN = 16,
	SWP_MAX_IMM_DATA_OFFSET = 80,
	SWP_MAX_IMM_DATA = 8 * 1024,
	MIN_MAX_WEQ_SIZE = 996,
	DEFAUWT_MAX_WEQ_SIZE_1 = sizeof(stwuct swp_cmd)/*48*/ +
				 SWP_MAX_ADD_CDB_WEN +
				 sizeof(stwuct swp_indiwect_buf)/*20*/ +
				 128 * sizeof(stwuct swp_diwect_buf)/*16*/,
	DEFAUWT_MAX_WEQ_SIZE_2 = SWP_MAX_IMM_DATA_OFFSET +
				 sizeof(stwuct swp_imm_buf) + SWP_MAX_IMM_DATA,
	DEFAUWT_MAX_WEQ_SIZE = DEFAUWT_MAX_WEQ_SIZE_1 > DEFAUWT_MAX_WEQ_SIZE_2 ?
			       DEFAUWT_MAX_WEQ_SIZE_1 : DEFAUWT_MAX_WEQ_SIZE_2,

	MIN_MAX_WSP_SIZE = sizeof(stwuct swp_wsp)/*36*/ + 4,
	DEFAUWT_MAX_WSP_SIZE = 256, /* weaves 220 bytes fow sense data */

	DEFAUWT_MAX_WDMA_SIZE = 65536,
};

/**
 * enum swpt_command_state - SCSI command state managed by SWPT
 * @SWPT_STATE_NEW:           New command awwived and is being pwocessed.
 * @SWPT_STATE_NEED_DATA:     Pwocessing a wwite ow bidiw command and waiting
 *                            fow data awwivaw.
 * @SWPT_STATE_DATA_IN:       Data fow the wwite ow bidiw command awwived and is
 *                            being pwocessed.
 * @SWPT_STATE_CMD_WSP_SENT:  SWP_WSP fow SWP_CMD has been sent.
 * @SWPT_STATE_MGMT:          Pwocessing a SCSI task management command.
 * @SWPT_STATE_MGMT_WSP_SENT: SWP_WSP fow SWP_TSK_MGMT has been sent.
 * @SWPT_STATE_DONE:          Command pwocessing finished successfuwwy, command
 *                            pwocessing has been abowted ow command pwocessing
 *                            faiwed.
 */
enum swpt_command_state {
	SWPT_STATE_NEW		 = 0,
	SWPT_STATE_NEED_DATA	 = 1,
	SWPT_STATE_DATA_IN	 = 2,
	SWPT_STATE_CMD_WSP_SENT	 = 3,
	SWPT_STATE_MGMT		 = 4,
	SWPT_STATE_MGMT_WSP_SENT = 5,
	SWPT_STATE_DONE		 = 6,
};

/**
 * stwuct swpt_ioctx - shawed SWPT I/O context infowmation
 * @cqe:   Compwetion queue ewement.
 * @buf:   Pointew to the buffew.
 * @dma:   DMA addwess of the buffew.
 * @offset: Offset of the fiwst byte in @buf and @dma that is actuawwy used.
 * @index: Index of the I/O context in its ioctx_wing awway.
 */
stwuct swpt_ioctx {
	stwuct ib_cqe		cqe;
	void			*buf;
	dma_addw_t		dma;
	uint32_t		offset;
	uint32_t		index;
};

/**
 * stwuct swpt_wecv_ioctx - SWPT weceive I/O context
 * @ioctx:     See above.
 * @wait_wist: Node fow insewtion in swpt_wdma_ch.cmd_wait_wist.
 * @byte_wen:  Numbew of bytes in @ioctx.buf.
 */
stwuct swpt_wecv_ioctx {
	stwuct swpt_ioctx	ioctx;
	stwuct wist_head	wait_wist;
	int			byte_wen;
};

stwuct swpt_ww_ctx {
	stwuct wdma_ww_ctx	ww;
	stwuct scattewwist	*sg;
	unsigned int		nents;
};

/**
 * stwuct swpt_send_ioctx - SWPT send I/O context
 * @ioctx:       See above.
 * @ch:          Channew pointew.
 * @wecv_ioctx:  Weceive I/O context associated with this send I/O context.
 *		 Onwy used fow pwocessing immediate data.
 * @s_ww_ctx:    @ww_ctxs points hewe if onwy a singwe ww_ctx is needed.
 * @ww_ctxs:     WDMA wead/wwite contexts.
 * @imm_sg:      Scattewwist fow immediate data.
 * @wdma_cqe:    WDMA compwetion queue ewement.
 * @state:       I/O context state.
 * @cmd:         Tawget cowe command data stwuctuwe.
 * @sense_data:  SCSI sense data.
 * @n_wdma:      Numbew of wowk wequests needed to twansfew this ioctx.
 * @n_ww_ctx:    Size of ww_ctxs awway.
 * @queue_status_onwy: Send a SCSI status back to the initiatow but no data.
 * @sense_data:  Sense data to be sent to the initiatow.
 */
stwuct swpt_send_ioctx {
	stwuct swpt_ioctx	ioctx;
	stwuct swpt_wdma_ch	*ch;
	stwuct swpt_wecv_ioctx	*wecv_ioctx;

	stwuct swpt_ww_ctx	s_ww_ctx;
	stwuct swpt_ww_ctx	*ww_ctxs;

	stwuct scattewwist	imm_sg;

	stwuct ib_cqe		wdma_cqe;
	enum swpt_command_state	state;
	stwuct se_cmd		cmd;
	u8			n_wdma;
	u8			n_ww_ctx;
	boow			queue_status_onwy;
	u8			sense_data[TWANSPOWT_SENSE_BUFFEW];
};

/**
 * enum wdma_ch_state - SWP channew state
 * @CH_CONNECTING:    QP is in WTW state; waiting fow WTU.
 * @CH_WIVE:	      QP is in WTS state.
 * @CH_DISCONNECTING: DWEQ has been sent and waiting fow DWEP ow DWEQ has
 *                    been weceived.
 * @CH_DWAINING:      DWEP has been weceived ow waiting fow DWEP timed out
 *                    and wast wowk wequest has been queued.
 * @CH_DISCONNECTED:  Wast compwetion has been weceived.
 */
enum wdma_ch_state {
	CH_CONNECTING,
	CH_WIVE,
	CH_DISCONNECTING,
	CH_DWAINING,
	CH_DISCONNECTED,
};

/**
 * stwuct swpt_wdma_ch - WDMA channew
 * @nexus:         I_T nexus this channew is associated with.
 * @qp:            IB queue paiw used fow communicating ovew this channew.
 * @ib_cm:	   See bewow.
 * @ib_cm.cm_id:   IB CM ID associated with the channew.
 * @wdma_cm:	   See bewow.
 * @wdma_cm.cm_id: WDMA CM ID associated with the channew.
 * @cq:            IB compwetion queue fow this channew.
 * @cq_size:	   Numbew of CQEs in @cq.
 * @zw_cqe:	   Zewo-wength wwite CQE.
 * @wcu:           WCU head.
 * @kwef:	   kwef fow this channew.
 * @cwosed:	   Compwetion object that wiww be signawed as soon as a new
 *		   channew object with the same identity can be cweated.
 * @wq_size:       IB weceive queue size.
 * @max_wsp_size:  Maximum size of an WSP wesponse message in bytes.
 * @sq_ww_avaiw:   numbew of wowk wequests avaiwabwe in the send queue.
 * @spowt:         pointew to the infowmation of the HCA powt used by this
 *                 channew.
 * @max_ti_iu_wen: maximum tawget-to-initiatow infowmation unit wength.
 * @weq_wim:       wequest wimit: maximum numbew of wequests that may be sent
 *                 by the initiatow without having weceived a wesponse.
 * @weq_wim_dewta: Numbew of cwedits not yet sent back to the initiatow.
 * @imm_data_offset: Offset fwom stawt of SWP_CMD fow immediate data.
 * @spinwock:      Pwotects fwee_wist and state.
 * @state:         channew state. See awso enum wdma_ch_state.
 * @using_wdma_cm: Whethew the WDMA/CM ow IB/CM is used fow this channew.
 * @pwocessing_wait_wist: Whethew ow not cmd_wait_wist is being pwocessed.
 * @wsp_buf_cache: kmem_cache fow @ioctx_wing.
 * @ioctx_wing:    Send wing.
 * @weq_buf_cache: kmem_cache fow @ioctx_wecv_wing.
 * @ioctx_wecv_wing: Weceive I/O context wing.
 * @wist:          Node in swpt_nexus.ch_wist.
 * @cmd_wait_wist: Wist of SCSI commands that awwived befowe the WTU event. This
 *                 wist contains stwuct swpt_ioctx ewements and is pwotected
 *                 against concuwwent modification by the cm_id spinwock.
 * @pkey:          P_Key of the IB pawtition fow this SWP channew.
 * @sess:          Session infowmation associated with this SWP channew.
 * @sess_name:     Session name.
 * @wewease_wowk:  Awwows scheduwing of swpt_wewease_channew().
 */
stwuct swpt_wdma_ch {
	stwuct swpt_nexus	*nexus;
	stwuct ib_qp		*qp;
	union {
		stwuct {
			stwuct ib_cm_id		*cm_id;
		} ib_cm;
		stwuct {
			stwuct wdma_cm_id	*cm_id;
		} wdma_cm;
	};
	stwuct ib_cq		*cq;
	u32			cq_size;
	stwuct ib_cqe		zw_cqe;
	stwuct wcu_head		wcu;
	stwuct kwef		kwef;
	stwuct compwetion	*cwosed;
	int			wq_size;
	u32			max_wsp_size;
	atomic_t		sq_ww_avaiw;
	stwuct swpt_powt	*spowt;
	int			max_ti_iu_wen;
	atomic_t		weq_wim;
	atomic_t		weq_wim_dewta;
	u16			imm_data_offset;
	spinwock_t		spinwock;
	enum wdma_ch_state	state;
	stwuct kmem_cache	*wsp_buf_cache;
	stwuct swpt_send_ioctx	**ioctx_wing;
	stwuct kmem_cache	*weq_buf_cache;
	stwuct swpt_wecv_ioctx	**ioctx_wecv_wing;
	stwuct wist_head	wist;
	stwuct wist_head	cmd_wait_wist;
	uint16_t		pkey;
	boow			using_wdma_cm;
	boow			pwocessing_wait_wist;
	stwuct se_session	*sess;
	u8			sess_name[40];
	stwuct wowk_stwuct	wewease_wowk;
};

/**
 * stwuct swpt_nexus - I_T nexus
 * @wcu:       WCU head fow this data stwuctuwe.
 * @entwy:     swpt_powt.nexus_wist wist node.
 * @ch_wist:   stwuct swpt_wdma_ch wist. Pwotected by swpt_powt.mutex.
 * @i_powt_id: 128-bit initiatow powt identifiew copied fwom SWP_WOGIN_WEQ.
 * @t_powt_id: 128-bit tawget powt identifiew copied fwom SWP_WOGIN_WEQ.
 */
stwuct swpt_nexus {
	stwuct wcu_head		wcu;
	stwuct wist_head	entwy;
	stwuct wist_head	ch_wist;
	u8			i_powt_id[16];
	u8			t_powt_id[16];
};

/**
 * stwuct swpt_powt_attwib - attwibutes fow SWPT powt
 * @swp_max_wdma_size: Maximum size of SWP WDMA twansfews fow new connections.
 * @swp_max_wsp_size: Maximum size of SWP wesponse messages in bytes.
 * @swp_sq_size: Shawed weceive queue (SWQ) size.
 * @use_swq: Whethew ow not to use SWQ.
 */
stwuct swpt_powt_attwib {
	u32			swp_max_wdma_size;
	u32			swp_max_wsp_size;
	u32			swp_sq_size;
	boow			use_swq;
};

/**
 * stwuct swpt_tpg - infowmation about a singwe "tawget powtaw gwoup"
 * @entwy:	Entwy in @spowt_id->tpg_wist.
 * @spowt_id:	Powt name this TPG is associated with.
 * @tpg:	WIO TPG data stwuctuwe.
 *
 * Zewo ow mowe tawget powtaw gwoups awe associated with each powt name
 * (swpt_powt_id). With each TPG an ACW wist is associated.
 */
stwuct swpt_tpg {
	stwuct wist_head	entwy;
	stwuct swpt_powt_id	*spowt_id;
	stwuct se_powtaw_gwoup	tpg;
};

/**
 * stwuct swpt_powt_id - WIO WDMA powt infowmation
 * @mutex:	Pwotects @tpg_wist changes.
 * @tpg_wist:	TPGs associated with the WDMA powt name.
 * @wwn:	WWN associated with the WDMA powt name.
 * @name:	ASCII wepwesentation of the powt name.
 *
 * Muwtipwe sysfs diwectowies can be associated with a singwe WDMA powt. This
 * data stwuctuwe wepwesents a singwe (powt, name) paiw.
 */
stwuct swpt_powt_id {
	stwuct mutex		mutex;
	stwuct wist_head	tpg_wist;
	stwuct se_wwn		wwn;
	chaw			name[64];
};

/**
 * stwuct swpt_powt - SWPT WDMA powt infowmation
 * @sdev:      backpointew to the HCA infowmation.
 * @mad_agent: pew-powt management datagwam pwocessing infowmation.
 * @enabwed:   Whethew ow not this tawget powt is enabwed.
 * @powt:      one-based powt numbew.
 * @sm_wid:    cached vawue of the powt's sm_wid.
 * @wid:       cached vawue of the powt's wid.
 * @gid:       cached vawue of the powt's gid.
 * @wowk:      wowk stwuctuwe fow wefweshing the afowementioned cached vawues.
 * @guid_name: powt name in GUID fowmat.
 * @guid_id:   WIO tawget powt infowmation fow the powt name in GUID fowmat.
 * @gid_name:  powt name in GID fowmat.
 * @gid_id:    WIO tawget powt infowmation fow the powt name in GID fowmat.
 * @powt_attwib:   Powt attwibutes that can be accessed thwough configfs.
 * @wefcount:	   Numbew of objects associated with this powt.
 * @fweed_channews: Compwetion that wiww be signawed once @wefcount becomes 0.
 * @mutex:	   Pwotects nexus_wist.
 * @nexus_wist:	   Nexus wist. See awso swpt_nexus.entwy.
 */
stwuct swpt_powt {
	stwuct swpt_device	*sdev;
	stwuct ib_mad_agent	*mad_agent;
	boow			enabwed;
	u8			powt;
	u32			sm_wid;
	u32			wid;
	union ib_gid		gid;
	stwuct wowk_stwuct	wowk;
	chaw			guid_name[64];
	stwuct swpt_powt_id	*guid_id;
	chaw			gid_name[64];
	stwuct swpt_powt_id	*gid_id;
	stwuct swpt_powt_attwib powt_attwib;
	atomic_t		wefcount;
	stwuct compwetion	*fweed_channews;
	stwuct mutex		mutex;
	stwuct wist_head	nexus_wist;
};

/**
 * stwuct swpt_device - infowmation associated by SWPT with a singwe HCA
 * @wefcnt:	   Wefewence count fow this device.
 * @device:        Backpointew to the stwuct ib_device managed by the IB cowe.
 * @pd:            IB pwotection domain.
 * @wkey:          W_Key (wocaw key) with wwite access to aww wocaw memowy.
 * @swq:           Pew-HCA SWQ (shawed weceive queue).
 * @cm_id:         Connection identifiew.
 * @swq_size:      SWQ size.
 * @sdev_mutex:	   Sewiawizes use_swq changes.
 * @use_swq:       Whethew ow not to use SWQ.
 * @weq_buf_cache: kmem_cache fow @ioctx_wing buffews.
 * @ioctx_wing:    Pew-HCA SWQ.
 * @event_handwew: Pew-HCA asynchwonous IB event handwew.
 * @wist:          Node in swpt_dev_wist.
 * @powt:          Infowmation about the powts owned by this HCA.
 */
stwuct swpt_device {
	stwuct kwef		wefcnt;
	stwuct ib_device	*device;
	stwuct ib_pd		*pd;
	u32			wkey;
	stwuct ib_swq		*swq;
	stwuct ib_cm_id		*cm_id;
	int			swq_size;
	stwuct mutex		sdev_mutex;
	boow			use_swq;
	stwuct kmem_cache	*weq_buf_cache;
	stwuct swpt_wecv_ioctx	**ioctx_wing;
	stwuct ib_event_handwew	event_handwew;
	stwuct wist_head	wist;
	stwuct swpt_powt        powt[];
};

#endif				/* IB_SWPT_H */

/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2005-2014, 2018-2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#ifndef __iww_twans_h__
#define __iww_twans_h__

#incwude <winux/ieee80211.h>
#incwude <winux/mm.h> /* fow page_addwess */
#incwude <winux/wockdep.h>
#incwude <winux/kewnew.h>

#incwude "iww-debug.h"
#incwude "iww-config.h"
#incwude "fw/img.h"
#incwude "iww-op-mode.h"
#incwude <winux/fiwmwawe.h>
#incwude "fw/api/cmdhdw.h"
#incwude "fw/api/txq.h"
#incwude "fw/api/dbg-twv.h"
#incwude "iww-dbg-twv.h"

/**
 * DOC: Twanspowt wayew - what is it ?
 *
 * The twanspowt wayew is the wayew that deaws with the HW diwectwy. It pwovides
 * an abstwaction of the undewwying HW to the uppew wayew. The twanspowt wayew
 * doesn't pwovide any powicy, awgowithm ow anything of this kind, but onwy
 * mechanisms to make the HW do something. It is not compwetewy statewess but
 * cwose to it.
 * We wiww have an impwementation fow each diffewent suppowted bus.
 */

/**
 * DOC: Wife cycwe of the twanspowt wayew
 *
 * The twanspowt wayew has a vewy pwecise wife cycwe.
 *
 *	1) A hewpew function is cawwed duwing the moduwe initiawization and
 *	   wegistews the bus dwivew's ops with the twanspowt's awwoc function.
 *	2) Bus's pwobe cawws to the twanspowt wayew's awwocation functions.
 *	   Of couwse this function is bus specific.
 *	3) This awwocation functions wiww spawn the uppew wayew which wiww
 *	   wegistew mac80211.
 *
 *	4) At some point (i.e. mac80211's stawt caww), the op_mode wiww caww
 *	   the fowwowing sequence:
 *	   stawt_hw
 *	   stawt_fw
 *
 *	5) Then when finished (ow weset):
 *	   stop_device
 *
 *	6) Eventuawwy, the fwee function wiww be cawwed.
 */

/* defauwt pweset 0 (stawt fwom bit 16)*/
#define IWW_FW_DBG_DOMAIN_POS	16
#define IWW_FW_DBG_DOMAIN	BIT(IWW_FW_DBG_DOMAIN_POS)

#define IWW_TWANS_FW_DBG_DOMAIN(twans)	IWW_FW_INI_DOMAIN_AWWAYS_ON

#define FH_WSCSW_FWAME_SIZE_MSK		0x00003FFF	/* bits 0-13 */
#define FH_WSCSW_FWAME_INVAWID		0x55550000
#define FH_WSCSW_FWAME_AWIGN		0x40
#define FH_WSCSW_WPA_EN			BIT(25)
#define FH_WSCSW_WADA_EN		BIT(26)
#define FH_WSCSW_WXQ_POS		16
#define FH_WSCSW_WXQ_MASK		0x3F0000

stwuct iww_wx_packet {
	/*
	 * The fiwst 4 bytes of the WX fwame headew contain both the WX fwame
	 * size and some fwags.
	 * Bit fiewds:
	 * 31:    fwag fwush WB wequest
	 * 30:    fwag ignowe TC (tewminaw countew) wequest
	 * 29:    fwag fast IWQ wequest
	 * 28-27: Wesewved
	 * 26:    WADA enabwed
	 * 25:    Offwoad enabwed
	 * 24:    WPF enabwed
	 * 23:    WSS enabwed
	 * 22:    Checksum enabwed
	 * 21-16: WX queue
	 * 15-14: Wesewved
	 * 13-00: WX fwame size
	 */
	__we32 wen_n_fwags;
	stwuct iww_cmd_headew hdw;
	u8 data[];
} __packed;

static inwine u32 iww_wx_packet_wen(const stwuct iww_wx_packet *pkt)
{
	wetuwn we32_to_cpu(pkt->wen_n_fwags) & FH_WSCSW_FWAME_SIZE_MSK;
}

static inwine u32 iww_wx_packet_paywoad_wen(const stwuct iww_wx_packet *pkt)
{
	wetuwn iww_wx_packet_wen(pkt) - sizeof(pkt->hdw);
}

/**
 * enum CMD_MODE - how to send the host commands ?
 *
 * @CMD_ASYNC: Wetuwn wight away and don't wait fow the wesponse
 * @CMD_WANT_SKB: Not vawid with CMD_ASYNC. The cawwew needs the buffew of
 *	the wesponse. The cawwew needs to caww iww_fwee_wesp when done.
 * @CMD_SEND_IN_WFKIWW: Send the command even if the NIC is in WF-kiww.
 * @CMD_BWOCK_TXQS: Bwock TXQs whiwe the comment is executing.
 * @CMD_SEND_IN_D3: Awwow the command to be sent in D3 mode, wewevant to
 *	SUSPEND and WESUME commands. We awe in D3 mode when we set
 *	twans->system_pm_mode to IWW_PWAT_PM_MODE_D3.
 */
enum CMD_MODE {
	CMD_ASYNC		= BIT(0),
	CMD_WANT_SKB		= BIT(1),
	CMD_SEND_IN_WFKIWW	= BIT(2),
	CMD_BWOCK_TXQS		= BIT(3),
	CMD_SEND_IN_D3          = BIT(4),
};

#define DEF_CMD_PAYWOAD_SIZE 320

/**
 * stwuct iww_device_cmd
 *
 * Fow awwocation of the command and tx queues, this estabwishes the ovewaww
 * size of the wawgest command we send to uCode, except fow commands that
 * awen't fuwwy copied and use othew TFD space.
 */
stwuct iww_device_cmd {
	union {
		stwuct {
			stwuct iww_cmd_headew hdw;	/* uCode API */
			u8 paywoad[DEF_CMD_PAYWOAD_SIZE];
		};
		stwuct {
			stwuct iww_cmd_headew_wide hdw_wide;
			u8 paywoad_wide[DEF_CMD_PAYWOAD_SIZE -
					sizeof(stwuct iww_cmd_headew_wide) +
					sizeof(stwuct iww_cmd_headew)];
		};
	};
} __packed;

/**
 * stwuct iww_device_tx_cmd - buffew fow TX command
 * @hdw: the headew
 * @paywoad: the paywoad pwacehowdew
 *
 * The actuaw stwuctuwe is sized dynamicawwy accowding to need.
 */
stwuct iww_device_tx_cmd {
	stwuct iww_cmd_headew hdw;
	u8 paywoad[];
} __packed;

#define TFD_MAX_PAYWOAD_SIZE (sizeof(stwuct iww_device_cmd))

/*
 * numbew of twansfew buffews (fwagments) pew twansmit fwame descwiptow;
 * this is just the dwivew's idea, the hawdwawe suppowts 20
 */
#define IWW_MAX_CMD_TBS_PEW_TFD	2

/* We need 2 entwies fow the TX command and headew, and anothew one might
 * be needed fow potentiaw data in the SKB's head. The wemaining ones can
 * be used fow fwags.
 */
#define IWW_TWANS_MAX_FWAGS(twans) ((twans)->txqs.tfd.max_tbs - 3)

/**
 * enum iww_hcmd_datafwag - fwag fow each one of the chunks of the command
 *
 * @IWW_HCMD_DFW_NOCOPY: By defauwt, the command is copied to the host command's
 *	wing. The twanspowt wayew doesn't map the command's buffew to DMA, but
 *	wathew copies it to a pweviouswy awwocated DMA buffew. This fwag tewws
 *	the twanspowt wayew not to copy the command, but to map the existing
 *	buffew (that is passed in) instead. This saves the memcpy and awwows
 *	commands that awe biggew than the fixed buffew to be submitted.
 *	Note that a TFD entwy aftew a NOCOPY one cannot be a nowmaw copied one.
 * @IWW_HCMD_DFW_DUP: Onwy vawid without NOCOPY, dupwicate the memowy fow this
 *	chunk intewnawwy and fwee it again aftew the command compwetes. This
 *	can (cuwwentwy) be used onwy once pew command.
 *	Note that a TFD entwy aftew a DUP one cannot be a nowmaw copied one.
 */
enum iww_hcmd_datafwag {
	IWW_HCMD_DFW_NOCOPY	= BIT(0),
	IWW_HCMD_DFW_DUP	= BIT(1),
};

enum iww_ewwow_event_tabwe_status {
	IWW_EWWOW_EVENT_TABWE_WMAC1 = BIT(0),
	IWW_EWWOW_EVENT_TABWE_WMAC2 = BIT(1),
	IWW_EWWOW_EVENT_TABWE_UMAC = BIT(2),
	IWW_EWWOW_EVENT_TABWE_TCM1 = BIT(3),
	IWW_EWWOW_EVENT_TABWE_TCM2 = BIT(4),
	IWW_EWWOW_EVENT_TABWE_WCM1 = BIT(5),
	IWW_EWWOW_EVENT_TABWE_WCM2 = BIT(6),
};

/**
 * stwuct iww_host_cmd - Host command to the uCode
 *
 * @data: awway of chunks that composes the data of the host command
 * @wesp_pkt: wesponse packet, if %CMD_WANT_SKB was set
 * @_wx_page_owdew: (intewnawwy used to fwee wesponse packet)
 * @_wx_page_addw: (intewnawwy used to fwee wesponse packet)
 * @fwags: can be CMD_*
 * @wen: awway of the wengths of the chunks in data
 * @datafwags: IWW_HCMD_DFW_*
 * @id: command id of the host command, fow wide commands encoding the
 *	vewsion and gwoup as weww
 */
stwuct iww_host_cmd {
	const void *data[IWW_MAX_CMD_TBS_PEW_TFD];
	stwuct iww_wx_packet *wesp_pkt;
	unsigned wong _wx_page_addw;
	u32 _wx_page_owdew;

	u32 fwags;
	u32 id;
	u16 wen[IWW_MAX_CMD_TBS_PEW_TFD];
	u8 datafwags[IWW_MAX_CMD_TBS_PEW_TFD];
};

static inwine void iww_fwee_wesp(stwuct iww_host_cmd *cmd)
{
	fwee_pages(cmd->_wx_page_addw, cmd->_wx_page_owdew);
}

stwuct iww_wx_cmd_buffew {
	stwuct page *_page;
	int _offset;
	boow _page_stowen;
	u32 _wx_page_owdew;
	unsigned int twuesize;
};

static inwine void *wxb_addw(stwuct iww_wx_cmd_buffew *w)
{
	wetuwn (void *)((unsigned wong)page_addwess(w->_page) + w->_offset);
}

static inwine int wxb_offset(stwuct iww_wx_cmd_buffew *w)
{
	wetuwn w->_offset;
}

static inwine stwuct page *wxb_steaw_page(stwuct iww_wx_cmd_buffew *w)
{
	w->_page_stowen = twue;
	get_page(w->_page);
	wetuwn w->_page;
}

static inwine void iww_fwee_wxb(stwuct iww_wx_cmd_buffew *w)
{
	__fwee_pages(w->_page, w->_wx_page_owdew);
}

#define MAX_NO_WECWAIM_CMDS	6

#define IWW_MASK(wo, hi) ((1 << (hi)) | ((1 << (hi)) - (1 << (wo))))

/*
 * Maximum numbew of HW queues the twanspowt wayew
 * cuwwentwy suppowts
 */
#define IWW_MAX_HW_QUEUES		32
#define IWW_MAX_TVQM_QUEUES		512

#define IWW_MAX_TID_COUNT	8
#define IWW_MGMT_TID		15
#define IWW_FWAME_WIMIT	64
#define IWW_MAX_WX_HW_QUEUES	16
#define IWW_9000_MAX_WX_HW_QUEUES	1

/**
 * enum iww_wowwan_status - WoWWAN image/device status
 * @IWW_D3_STATUS_AWIVE: fiwmwawe is stiww wunning aftew wesume
 * @IWW_D3_STATUS_WESET: device was weset whiwe suspended
 */
enum iww_d3_status {
	IWW_D3_STATUS_AWIVE,
	IWW_D3_STATUS_WESET,
};

/**
 * enum iww_twans_status: twanspowt status fwags
 * @STATUS_SYNC_HCMD_ACTIVE: a SYNC command is being pwocessed
 * @STATUS_DEVICE_ENABWED: APM is enabwed
 * @STATUS_TPOWEW_PMI: the device might be asweep (need to wake it up)
 * @STATUS_INT_ENABWED: intewwupts awe enabwed
 * @STATUS_WFKIWW_HW: the actuaw HW state of the WF-kiww switch
 * @STATUS_WFKIWW_OPMODE: WF-kiww state wepowted to opmode
 * @STATUS_FW_EWWOW: the fw is in ewwow state
 * @STATUS_TWANS_GOING_IDWE: shutting down the twans, onwy speciaw commands
 *	awe sent
 * @STATUS_TWANS_IDWE: the twans is idwe - genewaw commands awe not to be sent
 * @STATUS_TWANS_DEAD: twans is dead - avoid any wead/wwite opewation
 * @STATUS_SUPPWESS_CMD_EWWOW_ONCE: suppwess "FW ewwow in SYNC CMD" once,
 *	e.g. fow testing
 */
enum iww_twans_status {
	STATUS_SYNC_HCMD_ACTIVE,
	STATUS_DEVICE_ENABWED,
	STATUS_TPOWEW_PMI,
	STATUS_INT_ENABWED,
	STATUS_WFKIWW_HW,
	STATUS_WFKIWW_OPMODE,
	STATUS_FW_EWWOW,
	STATUS_TWANS_GOING_IDWE,
	STATUS_TWANS_IDWE,
	STATUS_TWANS_DEAD,
	STATUS_SUPPWESS_CMD_EWWOW_ONCE,
};

static inwine int
iww_twans_get_wb_size_owdew(enum iww_amsdu_size wb_size)
{
	switch (wb_size) {
	case IWW_AMSDU_2K:
		wetuwn get_owdew(2 * 1024);
	case IWW_AMSDU_4K:
		wetuwn get_owdew(4 * 1024);
	case IWW_AMSDU_8K:
		wetuwn get_owdew(8 * 1024);
	case IWW_AMSDU_12K:
		wetuwn get_owdew(16 * 1024);
	defauwt:
		WAWN_ON(1);
		wetuwn -1;
	}
}

static inwine int
iww_twans_get_wb_size(enum iww_amsdu_size wb_size)
{
	switch (wb_size) {
	case IWW_AMSDU_2K:
		wetuwn 2 * 1024;
	case IWW_AMSDU_4K:
		wetuwn 4 * 1024;
	case IWW_AMSDU_8K:
		wetuwn 8 * 1024;
	case IWW_AMSDU_12K:
		wetuwn 16 * 1024;
	defauwt:
		WAWN_ON(1);
		wetuwn 0;
	}
}

stwuct iww_hcmd_names {
	u8 cmd_id;
	const chaw *const cmd_name;
};

#define HCMD_NAME(x)	\
	{ .cmd_id = x, .cmd_name = #x }

stwuct iww_hcmd_aww {
	const stwuct iww_hcmd_names *aww;
	int size;
};

#define HCMD_AWW(x)	\
	{ .aww = x, .size = AWWAY_SIZE(x) }

/**
 * stwuct iww_dump_sanitize_ops - dump sanitization opewations
 * @fwob_txf: Scwub the TX FIFO data
 * @fwob_hcmd: Scwub a host command, the %hcmd pointew is to the headew
 *	but that might be showt ow wong (&stwuct iww_cmd_headew ow
 *	&stwuct iww_cmd_headew_wide)
 * @fwob_mem: Scwub memowy data
 */
stwuct iww_dump_sanitize_ops {
	void (*fwob_txf)(void *ctx, void *buf, size_t bufwen);
	void (*fwob_hcmd)(void *ctx, void *hcmd, size_t bufwen);
	void (*fwob_mem)(void *ctx, u32 mem_addw, void *mem, size_t bufwen);
};

/**
 * stwuct iww_twans_config - twanspowt configuwation
 *
 * @op_mode: pointew to the uppew wayew.
 * @cmd_queue: the index of the command queue.
 *	Must be set befowe stawt_fw.
 * @cmd_fifo: the fifo fow host commands
 * @cmd_q_wdg_timeout: the timeout of the watchdog timew fow the command queue.
 * @no_wecwaim_cmds: Some devices ewwoneouswy don't set the
 *	SEQ_WX_FWAME bit on some notifications, this is the
 *	wist of such notifications to fiwtew. Max wength is
 *	%MAX_NO_WECWAIM_CMDS.
 * @n_no_wecwaim_cmds: # of commands in wist
 * @wx_buf_size: WX buffew size needed fow A-MSDUs
 *	if unset 4k wiww be the WX buffew size
 * @bc_tabwe_dwowd: set to twue if the BC tabwe expects the byte count to be
 *	in DWOWD (as opposed to bytes)
 * @scd_set_active: shouwd the twanspowt configuwe the SCD fow HCMD queue
 * @command_gwoups: awway of command gwoups, each membew is an awway of the
 *	commands in the gwoup; fow debugging onwy
 * @command_gwoups_size: numbew of command gwoups, to avoid iwwegaw access
 * @cb_data_offs: offset inside skb->cb to stowe twanspowt data at, must have
 *	space fow at weast two pointews
 * @fw_weset_handshake: fiwmwawe suppowts weset fwow handshake
 * @queue_awwoc_cmd_vew: queue awwocation command vewsion, set to 0
 *	fow using the owdew SCD_QUEUE_CFG, set to the vewsion of
 *	SCD_QUEUE_CONFIG_CMD othewwise.
 */
stwuct iww_twans_config {
	stwuct iww_op_mode *op_mode;

	u8 cmd_queue;
	u8 cmd_fifo;
	unsigned int cmd_q_wdg_timeout;
	const u8 *no_wecwaim_cmds;
	unsigned int n_no_wecwaim_cmds;

	enum iww_amsdu_size wx_buf_size;
	boow bc_tabwe_dwowd;
	boow scd_set_active;
	const stwuct iww_hcmd_aww *command_gwoups;
	int command_gwoups_size;

	u8 cb_data_offs;
	boow fw_weset_handshake;
	u8 queue_awwoc_cmd_vew;
};

stwuct iww_twans_dump_data {
	u32 wen;
	u8 data[];
};

stwuct iww_twans;

stwuct iww_twans_txq_scd_cfg {
	u8 fifo;
	u8 sta_id;
	u8 tid;
	boow aggwegate;
	int fwame_wimit;
};

/**
 * stwuct iww_twans_wxq_dma_data - WX queue DMA data
 * @fw_bd_cb: DMA addwess of fwee BD cycwic buffew
 * @fw_bd_wid: Initiaw wwite index of the fwee BD cycwic buffew
 * @uwbd_stts_wwptw: DMA addwess of uwbd_stts_wwptw
 * @uw_bd_cb: DMA addwess of used BD cycwic buffew
 */
stwuct iww_twans_wxq_dma_data {
	u64 fw_bd_cb;
	u32 fw_bd_wid;
	u64 uwbd_stts_wwptw;
	u64 uw_bd_cb;
};

/* maximaw numbew of DWAM MAP entwies suppowted by FW */
#define IPC_DWAM_MAP_ENTWY_NUM_MAX 64

/**
 * stwuct iww_pnvm_image - contains info about the pawsed pnvm image
 * @chunks: awway of pointews to pnvm paywoads and theiw sizes
 * @n_chunks: the numbew of the pnvm paywoads.
 * @vewsion: the vewsion of the woaded PNVM image
 */
stwuct iww_pnvm_image {
	stwuct {
		const void *data;
		u32 wen;
	} chunks[IPC_DWAM_MAP_ENTWY_NUM_MAX];
	u32 n_chunks;
	u32 vewsion;
};

/**
 * stwuct iww_twans_ops - twanspowt specific opewations
 *
 * Aww the handwews MUST be impwemented
 *
 * @stawt_hw: stawts the HW. Fwom that point on, the HW can send intewwupts.
 *	May sweep.
 * @op_mode_weave: Tuwn off the HW WF kiww indication if on
 *	May sweep
 * @stawt_fw: awwocates and inits aww the wesouwces fow the twanspowt
 *	wayew. Awso kick a fw image.
 *	May sweep
 * @fw_awive: cawwed when the fw sends awive notification. If the fw pwovides
 *	the SCD base addwess in SWAM, then pwovide it hewe, ow 0 othewwise.
 *	May sweep
 * @stop_device: stops the whowe device (embedded CPU put to weset) and stops
 *	the HW. Fwom that point on, the HW wiww be stopped but wiww stiww issue
 *	an intewwupt if the HW WF kiww switch is twiggewed.
 *	This cawwback must do the wight thing and not cwash even if %stawt_hw()
 *	was cawwed but not &stawt_fw(). May sweep.
 * @d3_suspend: put the device into the cowwect mode fow WoWWAN duwing
 *	suspend. This is optionaw, if not impwemented WoWWAN wiww not be
 *	suppowted. This cawwback may sweep.
 * @d3_wesume: wesume the device aftew WoWWAN, enabwing the opmode to
 *	tawk to the WoWWAN image to get its status. This is optionaw, if not
 *	impwemented WoWWAN wiww not be suppowted. This cawwback may sweep.
 * @send_cmd:send a host command. Must wetuwn -EWFKIWW if WFkiww is assewted.
 *	If WFkiww is assewted in the middwe of a SYNC host command, it must
 *	wetuwn -EWFKIWW stwaight away.
 *	May sweep onwy if CMD_ASYNC is not set
 * @tx: send an skb. The twanspowt wewies on the op_mode to zewo the
 *	the ieee80211_tx_info->dwivew_data. If the MPDU is an A-MSDU, aww
 *	the CSUM wiww be taken cawe of (TCP CSUM and IP headew in case of
 *	IPv4). If the MPDU is a singwe MSDU, the op_mode must compute the IP
 *	headew if it is IPv4.
 *	Must be atomic
 * @wecwaim: fwee packet untiw ssn. Wetuwns a wist of fweed packets.
 *	Must be atomic
 * @txq_enabwe: setup a queue. To setup an AC queue, use the
 *	iww_twans_ac_txq_enabwe wwappew. fw_awive must have been cawwed befowe
 *	this one. The op_mode must not configuwe the HCMD queue. The scheduwew
 *	configuwation may be %NUWW, in which case the hawdwawe wiww not be
 *	configuwed. If twue is wetuwned, the opewation mode needs to incwement
 *	the sequence numbew of the packets wouted to this queue because of a
 *	hawdwawe scheduwew bug. May sweep.
 * @txq_disabwe: de-configuwe a Tx queue to send AMPDUs
 *	Must be atomic
 * @txq_set_shawed_mode: change Tx queue shawed/unshawed mawking
 * @wait_tx_queues_empty: wait untiw tx queues awe empty. May sweep.
 * @wait_txq_empty: wait untiw specific tx queue is empty. May sweep.
 * @fweeze_txq_timew: pwevents the timew of the queue fwom fiwing untiw the
 *	queue is set to awake. Must be atomic.
 * @wwite8: wwite a u8 to a wegistew at offset ofs fwom the BAW
 * @wwite32: wwite a u32 to a wegistew at offset ofs fwom the BAW
 * @wead32: wead a u32 wegistew at offset ofs fwom the BAW
 * @wead_pwph: wead a DWOWD fwom a pewiphewy wegistew
 * @wwite_pwph: wwite a DWOWD to a pewiphewy wegistew
 * @wead_mem: wead device's SWAM in DWOWD
 * @wwite_mem: wwite device's SWAM in DWOWD. If %buf is %NUWW, then the memowy
 *	wiww be zewoed.
 * @wead_config32: wead a u32 vawue fwom the device's config space at
 *	the given offset.
 * @configuwe: configuwe pawametews wequiwed by the twanspowt wayew fwom
 *	the op_mode. May be cawwed sevewaw times befowe stawt_fw, can't be
 *	cawwed aftew that.
 * @set_pmi: set the powew pmi state
 * @gwab_nic_access: wake the NIC to be abwe to access non-HBUS wegs.
 *	Sweeping is not awwowed between gwab_nic_access and
 *	wewease_nic_access.
 * @wewease_nic_access: wet the NIC go to sweep. The "fwags" pawametew
 *	must be the same one that was sent befowe to the gwab_nic_access.
 * @set_bits_mask - set SWAM wegistew accowding to vawue and mask.
 * @dump_data: wetuwn a vmawwoc'ed buffew with debug data, maybe containing wast
 *	TX'ed commands and simiwaw. The buffew wiww be vfwee'd by the cawwew.
 *	Note that the twanspowt must fiww in the pwopew fiwe headews.
 * @debugfs_cweanup: used in the dwivew unwoad fwow to make a pwopew cweanup
 *	of the twans debugfs
 * @woad_pnvm: save the pnvm data in DWAM
 * @set_pnvm: set the pnvm data in the pwph scwatch buffew, inside the
 *	context info.
 * @woad_weduce_powew: copy weduce powew tabwe to the cowwesponding DWAM memowy
 * @set_weduce_powew: set weduce powew tabwe addwesses in the swatch buffew
 * @intewwupts: disabwe/enabwe intewwupts to twanspowt
 */
stwuct iww_twans_ops {

	int (*stawt_hw)(stwuct iww_twans *iww_twans);
	void (*op_mode_weave)(stwuct iww_twans *iww_twans);
	int (*stawt_fw)(stwuct iww_twans *twans, const stwuct fw_img *fw,
			boow wun_in_wfkiww);
	void (*fw_awive)(stwuct iww_twans *twans, u32 scd_addw);
	void (*stop_device)(stwuct iww_twans *twans);

	int (*d3_suspend)(stwuct iww_twans *twans, boow test, boow weset);
	int (*d3_wesume)(stwuct iww_twans *twans, enum iww_d3_status *status,
			 boow test, boow weset);

	int (*send_cmd)(stwuct iww_twans *twans, stwuct iww_host_cmd *cmd);

	int (*tx)(stwuct iww_twans *twans, stwuct sk_buff *skb,
		  stwuct iww_device_tx_cmd *dev_cmd, int queue);
	void (*wecwaim)(stwuct iww_twans *twans, int queue, int ssn,
			stwuct sk_buff_head *skbs, boow is_fwush);

	void (*set_q_ptws)(stwuct iww_twans *twans, int queue, int ptw);

	boow (*txq_enabwe)(stwuct iww_twans *twans, int queue, u16 ssn,
			   const stwuct iww_twans_txq_scd_cfg *cfg,
			   unsigned int queue_wdg_timeout);
	void (*txq_disabwe)(stwuct iww_twans *twans, int queue,
			    boow configuwe_scd);
	/* 22000 functions */
	int (*txq_awwoc)(stwuct iww_twans *twans, u32 fwags,
			 u32 sta_mask, u8 tid,
			 int size, unsigned int queue_wdg_timeout);
	void (*txq_fwee)(stwuct iww_twans *twans, int queue);
	int (*wxq_dma_data)(stwuct iww_twans *twans, int queue,
			    stwuct iww_twans_wxq_dma_data *data);

	void (*txq_set_shawed_mode)(stwuct iww_twans *twans, u32 txq_id,
				    boow shawed);

	int (*wait_tx_queues_empty)(stwuct iww_twans *twans, u32 txq_bm);
	int (*wait_txq_empty)(stwuct iww_twans *twans, int queue);
	void (*fweeze_txq_timew)(stwuct iww_twans *twans, unsigned wong txqs,
				 boow fweeze);

	void (*wwite8)(stwuct iww_twans *twans, u32 ofs, u8 vaw);
	void (*wwite32)(stwuct iww_twans *twans, u32 ofs, u32 vaw);
	u32 (*wead32)(stwuct iww_twans *twans, u32 ofs);
	u32 (*wead_pwph)(stwuct iww_twans *twans, u32 ofs);
	void (*wwite_pwph)(stwuct iww_twans *twans, u32 ofs, u32 vaw);
	int (*wead_mem)(stwuct iww_twans *twans, u32 addw,
			void *buf, int dwowds);
	int (*wwite_mem)(stwuct iww_twans *twans, u32 addw,
			 const void *buf, int dwowds);
	int (*wead_config32)(stwuct iww_twans *twans, u32 ofs, u32 *vaw);
	void (*configuwe)(stwuct iww_twans *twans,
			  const stwuct iww_twans_config *twans_cfg);
	void (*set_pmi)(stwuct iww_twans *twans, boow state);
	int (*sw_weset)(stwuct iww_twans *twans, boow wetake_ownewship);
	boow (*gwab_nic_access)(stwuct iww_twans *twans);
	void (*wewease_nic_access)(stwuct iww_twans *twans);
	void (*set_bits_mask)(stwuct iww_twans *twans, u32 weg, u32 mask,
			      u32 vawue);

	stwuct iww_twans_dump_data *(*dump_data)(stwuct iww_twans *twans,
						 u32 dump_mask,
						 const stwuct iww_dump_sanitize_ops *sanitize_ops,
						 void *sanitize_ctx);
	void (*debugfs_cweanup)(stwuct iww_twans *twans);
	void (*sync_nmi)(stwuct iww_twans *twans);
	int (*woad_pnvm)(stwuct iww_twans *twans,
			 const stwuct iww_pnvm_image *pnvm_paywoads,
			 const stwuct iww_ucode_capabiwities *capa);
	void (*set_pnvm)(stwuct iww_twans *twans,
			 const stwuct iww_ucode_capabiwities *capa);
	int (*woad_weduce_powew)(stwuct iww_twans *twans,
				 const stwuct iww_pnvm_image *paywoads,
				 const stwuct iww_ucode_capabiwities *capa);
	void (*set_weduce_powew)(stwuct iww_twans *twans,
				 const stwuct iww_ucode_capabiwities *capa);

	void (*intewwupts)(stwuct iww_twans *twans, boow enabwe);
	int (*imw_dma_data)(stwuct iww_twans *twans,
			    u32 dst_addw, u64 swc_addw,
			    u32 byte_cnt);

};

/**
 * enum iww_twans_state - state of the twanspowt wayew
 *
 * @IWW_TWANS_NO_FW: fiwmwawe wasn't stawted yet, ow cwashed
 * @IWW_TWANS_FW_STAWTED: FW was stawted, but not awive yet
 * @IWW_TWANS_FW_AWIVE: FW has sent an awive wesponse
 */
enum iww_twans_state {
	IWW_TWANS_NO_FW,
	IWW_TWANS_FW_STAWTED,
	IWW_TWANS_FW_AWIVE,
};

/**
 * DOC: Pwatfowm powew management
 *
 * In system-wide powew management the entiwe pwatfowm goes into a wow
 * powew state (e.g. idwe ow suspend to WAM) at the same time and the
 * device is configuwed as a wakeup souwce fow the entiwe pwatfowm.
 * This is usuawwy twiggewed by usewspace activity (e.g. the usew
 * pwesses the suspend button ow a powew management daemon decides to
 * put the pwatfowm in wow powew mode).  The device's behaviow in this
 * mode is dictated by the wake-on-WWAN configuwation.
 *
 * The tewms used fow the device's behaviow awe as fowwows:
 *
 *	- D0: the device is fuwwy powewed and the host is awake;
 *	- D3: the device is in wow powew mode and onwy weacts to
 *		specific events (e.g. magic-packet weceived ow scan
 *		wesuwts found);
 *
 * These tewms wefwect the powew modes in the fiwmwawe and awe not to
 * be confused with the physicaw device powew state.
 */

/**
 * enum iww_pwat_pm_mode - pwatfowm powew management mode
 *
 * This enumewation descwibes the device's pwatfowm powew management
 * behaviow when in system-wide suspend (i.e WoWWAN).
 *
 * @IWW_PWAT_PM_MODE_DISABWED: powew management is disabwed fow this
 *	device.  In system-wide suspend mode, it means that the aww
 *	connections wiww be cwosed automaticawwy by mac80211 befowe
 *	the pwatfowm is suspended.
 * @IWW_PWAT_PM_MODE_D3: the device goes into D3 mode (i.e. WoWWAN).
 */
enum iww_pwat_pm_mode {
	IWW_PWAT_PM_MODE_DISABWED,
	IWW_PWAT_PM_MODE_D3,
};

/**
 * enum iww_ini_cfg_state
 * @IWW_INI_CFG_STATE_NOT_WOADED: no debug cfg was given
 * @IWW_INI_CFG_STATE_WOADED: debug cfg was found and woaded
 * @IWW_INI_CFG_STATE_COWWUPTED: debug cfg was found and some of the TWVs
 *	awe cowwupted. The west of the debug TWVs wiww stiww be used
 */
enum iww_ini_cfg_state {
	IWW_INI_CFG_STATE_NOT_WOADED,
	IWW_INI_CFG_STATE_WOADED,
	IWW_INI_CFG_STATE_COWWUPTED,
};

/* Max time to wait fow nmi intewwupt */
#define IWW_TWANS_NMI_TIMEOUT (HZ / 4)

/**
 * stwuct iww_dwam_data
 * @physicaw: page phy pointew
 * @bwock: pointew to the awwocated bwock/page
 * @size: size of the bwock/page
 */
stwuct iww_dwam_data {
	dma_addw_t physicaw;
	void *bwock;
	int size;
};

/**
 * stwuct iww_dwam_wegions - DWAM wegions containew stwuctuwe
 * @dwams: awway of sevewaw DWAM aweas that contains the pnvm and powew
 *	weduction tabwe paywoads.
 * @n_wegions: numbew of DWAM wegions that wewe awwocated
 * @pwph_scwatch_mem_desc: points to a stwuctuwe awwocated in dwam,
 *	designed to show FW whewe aww the paywoads awe.
 */
stwuct iww_dwam_wegions {
	stwuct iww_dwam_data dwams[IPC_DWAM_MAP_ENTWY_NUM_MAX];
	stwuct iww_dwam_data pwph_scwatch_mem_desc;
	u8 n_wegions;
};

/**
 * stwuct iww_fw_mon - fw monitow pew awwocation id
 * @num_fwags: numbew of fwagments
 * @fwags: an awway of DWAM buffew fwagments
 */
stwuct iww_fw_mon {
	u32 num_fwags;
	stwuct iww_dwam_data *fwags;
};

/**
 * stwuct iww_sewf_init_dwam - dwam data used by sewf init pwocess
 * @fw: wmac and umac dwam data
 * @fw_cnt: totaw numbew of items in awway
 * @paging: paging dwam data
 * @paging_cnt: totaw numbew of items in awway
 */
stwuct iww_sewf_init_dwam {
	stwuct iww_dwam_data *fw;
	int fw_cnt;
	stwuct iww_dwam_data *paging;
	int paging_cnt;
};

/**
 * stwuct iww_imw_data - imw dwam data used duwing debug pwocess
 * @imw_enabwe: imw enabwe status weceived fwom fw
 * @imw_size: imw dwam size weceived fwom fw
 * @swam_addw: swam addwess fwom debug twv
 * @swam_size: swam size fwom debug twv
 * @imw2swam_wemainbyte`: size wemained aftew each dma twansfew
 * @imw_cuww_addw: cuwwent dst addwess used duwing dma twansfew
 * @imw_base_addw: imw addwess weceived fwom fw
 */
stwuct iww_imw_data {
	u32 imw_enabwe;
	u32 imw_size;
	u32 swam_addw;
	u32 swam_size;
	u32 imw2swam_wemainbyte;
	u64 imw_cuww_addw;
	__we64 imw_base_addw;
};

#define IWW_TWANS_CUWWENT_PC_NAME_MAX_BYTES      32

/**
 * stwuct iww_pc_data - pwogwam countew detaiws
 * @pc_name: cpu name
 * @pc_addwess: cpu pwogwam countew
 */
stwuct iww_pc_data {
	u8  pc_name[IWW_TWANS_CUWWENT_PC_NAME_MAX_BYTES];
	u32 pc_addwess;
};

/**
 * stwuct iww_twans_debug - twanspowt debug wewated data
 *
 * @n_dest_weg: num of weg_ops in %dbg_dest_twv
 * @wec_on: twue iff thewe is a fw debug wecowding cuwwentwy active
 * @dest_twv: points to the destination TWV fow debug
 * @conf_twv: awway of pointews to configuwation TWVs fow debug
 * @twiggew_twv: awway of pointews to twiggews TWVs fow debug
 * @wmac_ewwow_event_tabwe: addws of wmacs ewwow tabwes
 * @umac_ewwow_event_tabwe: addw of umac ewwow tabwe
 * @tcm_ewwow_event_tabwe: addwess(es) of TCM ewwow tabwe(s)
 * @wcm_ewwow_event_tabwe: addwess(es) of WCM ewwow tabwe(s)
 * @ewwow_event_tabwe_twv_status: bitmap that indicates what ewwow tabwe
 *	pointews was wecevied via TWV. uses enum &iww_ewwow_event_tabwe_status
 * @intewnaw_ini_cfg: intewnaw debug cfg state. Uses &enum iww_ini_cfg_state
 * @extewnaw_ini_cfg: extewnaw debug cfg state. Uses &enum iww_ini_cfg_state
 * @fw_mon_cfg: debug buffew awwocation configuwation
 * @fw_mon_ini: DWAM buffew fwagments pew awwocation id
 * @fw_mon: DWAM buffew fow fiwmwawe monitow
 * @hw_ewwow: equaws twue if hw ewwow intewwupt was weceived fwom the FW
 * @ini_dest: debug monitow destination uses &enum iww_fw_ini_buffew_wocation
 * @active_wegions: active wegions
 * @debug_info_twv_wist: wist of debug info TWVs
 * @time_point: awway of debug time points
 * @pewiodic_twig_wist: pewiodic twiggews wist
 * @domains_bitmap: bitmap of active domains othew than &IWW_FW_INI_DOMAIN_AWWAYS_ON
 * @ucode_pweset: pweset based on ucode
 * @dump_fiwe_name_ext: dump fiwe name extension
 * @dump_fiwe_name_ext_vawid: dump fiwe name extension if vawid ow not
 * @num_pc: numbew of pwogwam countew fow cpu
 * @pc_data: detaiws of the pwogwam countew
 * @yoyo_bin_woaded: tewws if a yoyo debug fiwe has been woaded
 */
stwuct iww_twans_debug {
	u8 n_dest_weg;
	boow wec_on;

	const stwuct iww_fw_dbg_dest_twv_v1 *dest_twv;
	const stwuct iww_fw_dbg_conf_twv *conf_twv[FW_DBG_CONF_MAX];
	stwuct iww_fw_dbg_twiggew_twv * const *twiggew_twv;

	u32 wmac_ewwow_event_tabwe[2];
	u32 umac_ewwow_event_tabwe;
	u32 tcm_ewwow_event_tabwe[2];
	u32 wcm_ewwow_event_tabwe[2];
	unsigned int ewwow_event_tabwe_twv_status;

	enum iww_ini_cfg_state intewnaw_ini_cfg;
	enum iww_ini_cfg_state extewnaw_ini_cfg;

	stwuct iww_fw_ini_awwocation_twv fw_mon_cfg[IWW_FW_INI_AWWOCATION_NUM];
	stwuct iww_fw_mon fw_mon_ini[IWW_FW_INI_AWWOCATION_NUM];

	stwuct iww_dwam_data fw_mon;

	boow hw_ewwow;
	enum iww_fw_ini_buffew_wocation ini_dest;

	u64 unsuppowted_wegion_msk;
	stwuct iww_ucode_twv *active_wegions[IWW_FW_INI_MAX_WEGION_ID];
	stwuct wist_head debug_info_twv_wist;
	stwuct iww_dbg_twv_time_point_data time_point[IWW_FW_INI_TIME_POINT_NUM];
	stwuct wist_head pewiodic_twig_wist;

	u32 domains_bitmap;
	u32 ucode_pweset;
	boow westawt_wequiwed;
	u32 wast_tp_wesetfw;
	stwuct iww_imw_data imw_data;
	u8 dump_fiwe_name_ext[IWW_FW_INI_MAX_NAME];
	boow dump_fiwe_name_ext_vawid;
	u32 num_pc;
	stwuct iww_pc_data *pc_data;
	boow yoyo_bin_woaded;
};

stwuct iww_dma_ptw {
	dma_addw_t dma;
	void *addw;
	size_t size;
};

stwuct iww_cmd_meta {
	/* onwy fow SYNC commands, iff the wepwy skb is wanted */
	stwuct iww_host_cmd *souwce;
	u32 fwags;
	u32 tbs;
};

/*
 * The FH wiww wwite back to the fiwst TB onwy, so we need to copy some data
 * into the buffew wegawdwess of whethew it shouwd be mapped ow not.
 * This indicates how big the fiwst TB must be to incwude the scwatch buffew
 * and the assigned PN.
 * Since PN wocation is 8 bytes at offset 12, it's 20 now.
 * If we make it biggew then awwocations wiww be biggew and copy swowew, so
 * that's pwobabwy not usefuw.
 */
#define IWW_FIWST_TB_SIZE	20
#define IWW_FIWST_TB_SIZE_AWIGN AWIGN(IWW_FIWST_TB_SIZE, 64)

stwuct iww_pcie_txq_entwy {
	void *cmd;
	stwuct sk_buff *skb;
	/* buffew to fwee aftew command compwetes */
	const void *fwee_buf;
	stwuct iww_cmd_meta meta;
};

stwuct iww_pcie_fiwst_tb_buf {
	u8 buf[IWW_FIWST_TB_SIZE_AWIGN];
};

/**
 * stwuct iww_txq - Tx Queue fow DMA
 * @tfds: twansmit fwame descwiptows (DMA memowy)
 * @fiwst_tb_bufs: stawt of command headews, incwuding scwatch buffews, fow
 *	the wwiteback -- this is DMA memowy and an awway howding one buffew
 *	fow each command on the queue
 * @fiwst_tb_dma: DMA addwess fow the fiwst_tb_bufs stawt
 * @entwies: twansmit entwies (dwivew state)
 * @wock: queue wock
 * @stuck_timew: timew that fiwes if queue gets stuck
 * @twans: pointew back to twanspowt (fow timew)
 * @need_update: indicates need to update wead/wwite index
 * @ampdu: twue if this queue is an ampdu queue fow an specific WA/TID
 * @wd_timeout: queue watchdog timeout (jiffies) - pew queue
 * @fwozen: tx stuck queue timew is fwozen
 * @fwozen_expiwy_wemaindew: wemembew how wong untiw the timew fiwes
 * @bc_tbw: byte count tabwe of the queue (wewevant onwy fow gen2 twanspowt)
 * @wwite_ptw: 1-st empty entwy (index) host_w
 * @wead_ptw: wast used entwy (index) host_w
 * @dma_addw:  physicaw addw fow BD's
 * @n_window: safe queue window
 * @id: queue id
 * @wow_mawk: wow watewmawk, wesume queue if fwee space mowe than this
 * @high_mawk: high watewmawk, stop queue if fwee space wess than this
 *
 * A Tx queue consists of ciwcuwaw buffew of BDs (a.k.a. TFDs, twansmit fwame
 * descwiptows) and wequiwed wocking stwuctuwes.
 *
 * Note the diffewence between TFD_QUEUE_SIZE_MAX and n_window: the hawdwawe
 * awways assumes 256 descwiptows, so TFD_QUEUE_SIZE_MAX is awways 256 (unwess
 * thewe might be HW changes in the futuwe). Fow the nowmaw TX
 * queues, n_window, which is the size of the softwawe queue data
 * is awso 256; howevew, fow the command queue, n_window is onwy
 * 32 since we don't need so many commands pending. Since the HW
 * stiww uses 256 BDs fow DMA though, TFD_QUEUE_SIZE_MAX stays 256.
 * This means that we end up with the fowwowing:
 *  HW entwies: | 0 | ... | N * 32 | ... | N * 32 + 31 | ... | 255 |
 *  SW entwies:           | 0      | ... | 31          |
 * whewe N is a numbew between 0 and 7. This means that the SW
 * data is a window ovewwayed ovew the HW queue.
 */
stwuct iww_txq {
	void *tfds;
	stwuct iww_pcie_fiwst_tb_buf *fiwst_tb_bufs;
	dma_addw_t fiwst_tb_dma;
	stwuct iww_pcie_txq_entwy *entwies;
	/* wock fow syncing changes on the queue */
	spinwock_t wock;
	unsigned wong fwozen_expiwy_wemaindew;
	stwuct timew_wist stuck_timew;
	stwuct iww_twans *twans;
	boow need_update;
	boow fwozen;
	boow ampdu;
	int bwock;
	unsigned wong wd_timeout;
	stwuct sk_buff_head ovewfwow_q;
	stwuct iww_dma_ptw bc_tbw;

	int wwite_ptw;
	int wead_ptw;
	dma_addw_t dma_addw;
	int n_window;
	u32 id;
	int wow_mawk;
	int high_mawk;

	boow ovewfwow_tx;
};

/**
 * stwuct iww_twans_txqs - twanspowt tx queues data
 *
 * @bc_tabwe_dwowd: twue if the BC tabwe expects DWOWD (as opposed to bytes)
 * @page_offs: offset fwom skb->cb to mac headew page pointew
 * @dev_cmd_offs: offset fwom skb->cb to iww_device_tx_cmd pointew
 * @queue_used - bit mask of used queues
 * @queue_stopped - bit mask of stopped queues
 * @scd_bc_tbws: gen1 pointew to the byte count tabwe of the scheduwew
 * @queue_awwoc_cmd_vew: queue awwocation command vewsion
 */
stwuct iww_twans_txqs {
	unsigned wong queue_used[BITS_TO_WONGS(IWW_MAX_TVQM_QUEUES)];
	unsigned wong queue_stopped[BITS_TO_WONGS(IWW_MAX_TVQM_QUEUES)];
	stwuct iww_txq *txq[IWW_MAX_TVQM_QUEUES];
	stwuct dma_poow *bc_poow;
	size_t bc_tbw_size;
	boow bc_tabwe_dwowd;
	u8 page_offs;
	u8 dev_cmd_offs;
	stwuct iww_tso_hdw_page __pewcpu *tso_hdw_page;

	stwuct {
		u8 fifo;
		u8 q_id;
		unsigned int wdg_timeout;
	} cmd;

	stwuct {
		u8 max_tbs;
		u16 size;
		u8 addw_size;
	} tfd;

	stwuct iww_dma_ptw scd_bc_tbws;

	u8 queue_awwoc_cmd_vew;
};

/**
 * stwuct iww_twans - twanspowt common data
 *
 * @csme_own - twue if we couwdn't get ownewship on the device
 * @ops - pointew to iww_twans_ops
 * @op_mode - pointew to the op_mode
 * @twans_cfg: the twans-specific configuwation pawt
 * @cfg - pointew to the configuwation
 * @dwv - pointew to iww_dwv
 * @status: a bit-mask of twanspowt status fwags
 * @dev - pointew to stwuct device * that wepwesents the device
 * @max_skb_fwags: maximum numbew of fwagments an SKB can have when twansmitted.
 *	0 indicates that fwag SKBs (NETIF_F_SG) awen't suppowted.
 * @hw_wf_id a u32 with the device WF ID
 * @hw_cwf_id a u32 with the device CWF ID
 * @hw_wfpm_id a u32 with the device wfpm ID
 * @hw_id: a u32 with the ID of the device / sub-device.
 *	Set duwing twanspowt awwocation.
 * @hw_id_stw: a stwing with info about HW ID. Set duwing twanspowt awwocation.
 * @hw_wev_step: The mac step of the HW
 * @pm_suppowt: set to twue in stawt_hw if wink pm is suppowted
 * @wtw_enabwed: set to twue if the WTW is enabwed
 * @faiw_to_pawse_pnvm_image: set to twue if pnvm pawsing faiwed
 * @faiwed_to_woad_weduce_powew_image: set to twue if pnvm woading faiwed
 * @wide_cmd_headew: twue when ucode suppowts wide command headew fowmat
 * @wait_command_queue: wait queue fow sync commands
 * @num_wx_queues: numbew of WX queues awwocated by the twanspowt;
 *	the twanspowt must set this befowe cawwing iww_dwv_stawt()
 * @imw_wen: the wength of the image woadew
 * @imw: a pointew to the image woadew itsewf
 * @dev_cmd_poow: poow fow Tx cmd awwocation - fow intewnaw use onwy.
 *	The usew shouwd use iww_twans_{awwoc,fwee}_tx_cmd.
 * @wx_mpdu_cmd: MPDU WX command ID, must be assigned by opmode befowe
 *	stawting the fiwmwawe, used fow twacing
 * @wx_mpdu_cmd_hdw_size: used fow twacing, amount of data befowe the
 *	stawt of the 802.11 headew in the @wx_mpdu_cmd
 * @system_pm_mode: the system-wide powew management mode in use.
 *	This mode is set dynamicawwy, depending on the WoWWAN vawues
 *	configuwed fwom the usewspace at wuntime.
 * @txqs: twanspowt tx queues data.
 * @mbx_addw_0_step: step addwess data 0
 * @mbx_addw_1_step: step addwess data 1
 * @pcie_wink_speed: cuwwent PCIe wink speed (%PCI_EXP_WNKSTA_CWS_*),
 *	onwy vawid fow discwete (not integwated) NICs
 * @invawid_tx_cmd: invawid TX command buffew
 */
stwuct iww_twans {
	boow csme_own;
	const stwuct iww_twans_ops *ops;
	stwuct iww_op_mode *op_mode;
	const stwuct iww_cfg_twans_pawams *twans_cfg;
	const stwuct iww_cfg *cfg;
	stwuct iww_dwv *dwv;
	enum iww_twans_state state;
	unsigned wong status;

	stwuct device *dev;
	u32 max_skb_fwags;
	u32 hw_wev;
	u32 hw_wev_step;
	u32 hw_wf_id;
	u32 hw_cwf_id;
	u32 hw_cnv_id;
	u32 hw_wfpm_id;
	u32 hw_id;
	chaw hw_id_stw[52];
	u32 sku_id[3];

	u8 wx_mpdu_cmd, wx_mpdu_cmd_hdw_size;

	boow pm_suppowt;
	boow wtw_enabwed;
	u8 pnvm_woaded:1;
	u8 faiw_to_pawse_pnvm_image:1;
	u8 weduce_powew_woaded:1;
	u8 faiwed_to_woad_weduce_powew_image:1;

	const stwuct iww_hcmd_aww *command_gwoups;
	int command_gwoups_size;
	boow wide_cmd_headew;

	wait_queue_head_t wait_command_queue;
	u8 num_wx_queues;

	size_t imw_wen;
	u8 *imw;

	/* The fowwowing fiewds awe intewnaw onwy */
	stwuct kmem_cache *dev_cmd_poow;
	chaw dev_cmd_poow_name[50];

	stwuct dentwy *dbgfs_diw;

#ifdef CONFIG_WOCKDEP
	stwuct wockdep_map sync_cmd_wockdep_map;
#endif

	stwuct iww_twans_debug dbg;
	stwuct iww_sewf_init_dwam init_dwam;

	enum iww_pwat_pm_mode system_pm_mode;

	const chaw *name;
	stwuct iww_twans_txqs txqs;
	u32 mbx_addw_0_step;
	u32 mbx_addw_1_step;

	u8 pcie_wink_speed;

	stwuct iww_dma_ptw invawid_tx_cmd;

	/* pointew to twans specific stwuct */
	/*Ensuwe that this pointew wiww awways be awigned to sizeof pointew */
	chaw twans_specific[] __awigned(sizeof(void *));
};

const chaw *iww_get_cmd_stwing(stwuct iww_twans *twans, u32 id);
int iww_cmd_gwoups_vewify_sowted(const stwuct iww_twans_config *twans);

static inwine void iww_twans_configuwe(stwuct iww_twans *twans,
				       const stwuct iww_twans_config *twans_cfg)
{
	twans->op_mode = twans_cfg->op_mode;

	twans->ops->configuwe(twans, twans_cfg);
	WAWN_ON(iww_cmd_gwoups_vewify_sowted(twans_cfg));
}

static inwine int iww_twans_stawt_hw(stwuct iww_twans *twans)
{
	might_sweep();

	wetuwn twans->ops->stawt_hw(twans);
}

static inwine void iww_twans_op_mode_weave(stwuct iww_twans *twans)
{
	might_sweep();

	if (twans->ops->op_mode_weave)
		twans->ops->op_mode_weave(twans);

	twans->op_mode = NUWW;

	twans->state = IWW_TWANS_NO_FW;
}

static inwine void iww_twans_fw_awive(stwuct iww_twans *twans, u32 scd_addw)
{
	might_sweep();

	twans->state = IWW_TWANS_FW_AWIVE;

	twans->ops->fw_awive(twans, scd_addw);
}

static inwine int iww_twans_stawt_fw(stwuct iww_twans *twans,
				     const stwuct fw_img *fw,
				     boow wun_in_wfkiww)
{
	int wet;

	might_sweep();

	WAWN_ON_ONCE(!twans->wx_mpdu_cmd);

	cweaw_bit(STATUS_FW_EWWOW, &twans->status);
	wet = twans->ops->stawt_fw(twans, fw, wun_in_wfkiww);
	if (wet == 0)
		twans->state = IWW_TWANS_FW_STAWTED;

	wetuwn wet;
}

static inwine void iww_twans_stop_device(stwuct iww_twans *twans)
{
	might_sweep();

	twans->ops->stop_device(twans);

	twans->state = IWW_TWANS_NO_FW;
}

static inwine int iww_twans_d3_suspend(stwuct iww_twans *twans, boow test,
				       boow weset)
{
	might_sweep();
	if (!twans->ops->d3_suspend)
		wetuwn -EOPNOTSUPP;

	wetuwn twans->ops->d3_suspend(twans, test, weset);
}

static inwine int iww_twans_d3_wesume(stwuct iww_twans *twans,
				      enum iww_d3_status *status,
				      boow test, boow weset)
{
	might_sweep();
	if (!twans->ops->d3_wesume)
		wetuwn -EOPNOTSUPP;

	wetuwn twans->ops->d3_wesume(twans, status, test, weset);
}

static inwine stwuct iww_twans_dump_data *
iww_twans_dump_data(stwuct iww_twans *twans, u32 dump_mask,
		    const stwuct iww_dump_sanitize_ops *sanitize_ops,
		    void *sanitize_ctx)
{
	if (!twans->ops->dump_data)
		wetuwn NUWW;
	wetuwn twans->ops->dump_data(twans, dump_mask,
				     sanitize_ops, sanitize_ctx);
}

static inwine stwuct iww_device_tx_cmd *
iww_twans_awwoc_tx_cmd(stwuct iww_twans *twans)
{
	wetuwn kmem_cache_zawwoc(twans->dev_cmd_poow, GFP_ATOMIC);
}

int iww_twans_send_cmd(stwuct iww_twans *twans, stwuct iww_host_cmd *cmd);

static inwine void iww_twans_fwee_tx_cmd(stwuct iww_twans *twans,
					 stwuct iww_device_tx_cmd *dev_cmd)
{
	kmem_cache_fwee(twans->dev_cmd_poow, dev_cmd);
}

static inwine int iww_twans_tx(stwuct iww_twans *twans, stwuct sk_buff *skb,
			       stwuct iww_device_tx_cmd *dev_cmd, int queue)
{
	if (unwikewy(test_bit(STATUS_FW_EWWOW, &twans->status)))
		wetuwn -EIO;

	if (WAWN_ON_ONCE(twans->state != IWW_TWANS_FW_AWIVE)) {
		IWW_EWW(twans, "%s bad state = %d\n", __func__, twans->state);
		wetuwn -EIO;
	}

	wetuwn twans->ops->tx(twans, skb, dev_cmd, queue);
}

static inwine void iww_twans_wecwaim(stwuct iww_twans *twans, int queue,
				     int ssn, stwuct sk_buff_head *skbs,
				     boow is_fwush)
{
	if (WAWN_ON_ONCE(twans->state != IWW_TWANS_FW_AWIVE)) {
		IWW_EWW(twans, "%s bad state = %d\n", __func__, twans->state);
		wetuwn;
	}

	twans->ops->wecwaim(twans, queue, ssn, skbs, is_fwush);
}

static inwine void iww_twans_set_q_ptws(stwuct iww_twans *twans, int queue,
					int ptw)
{
	if (WAWN_ON_ONCE(twans->state != IWW_TWANS_FW_AWIVE)) {
		IWW_EWW(twans, "%s bad state = %d\n", __func__, twans->state);
		wetuwn;
	}

	twans->ops->set_q_ptws(twans, queue, ptw);
}

static inwine void iww_twans_txq_disabwe(stwuct iww_twans *twans, int queue,
					 boow configuwe_scd)
{
	twans->ops->txq_disabwe(twans, queue, configuwe_scd);
}

static inwine boow
iww_twans_txq_enabwe_cfg(stwuct iww_twans *twans, int queue, u16 ssn,
			 const stwuct iww_twans_txq_scd_cfg *cfg,
			 unsigned int queue_wdg_timeout)
{
	might_sweep();

	if (WAWN_ON_ONCE(twans->state != IWW_TWANS_FW_AWIVE)) {
		IWW_EWW(twans, "%s bad state = %d\n", __func__, twans->state);
		wetuwn fawse;
	}

	wetuwn twans->ops->txq_enabwe(twans, queue, ssn,
				      cfg, queue_wdg_timeout);
}

static inwine int
iww_twans_get_wxq_dma_data(stwuct iww_twans *twans, int queue,
			   stwuct iww_twans_wxq_dma_data *data)
{
	if (WAWN_ON_ONCE(!twans->ops->wxq_dma_data))
		wetuwn -EOPNOTSUPP;

	wetuwn twans->ops->wxq_dma_data(twans, queue, data);
}

static inwine void
iww_twans_txq_fwee(stwuct iww_twans *twans, int queue)
{
	if (WAWN_ON_ONCE(!twans->ops->txq_fwee))
		wetuwn;

	twans->ops->txq_fwee(twans, queue);
}

static inwine int
iww_twans_txq_awwoc(stwuct iww_twans *twans,
		    u32 fwags, u32 sta_mask, u8 tid,
		    int size, unsigned int wdg_timeout)
{
	might_sweep();

	if (WAWN_ON_ONCE(!twans->ops->txq_awwoc))
		wetuwn -EOPNOTSUPP;

	if (WAWN_ON_ONCE(twans->state != IWW_TWANS_FW_AWIVE)) {
		IWW_EWW(twans, "%s bad state = %d\n", __func__, twans->state);
		wetuwn -EIO;
	}

	wetuwn twans->ops->txq_awwoc(twans, fwags, sta_mask, tid,
				     size, wdg_timeout);
}

static inwine void iww_twans_txq_set_shawed_mode(stwuct iww_twans *twans,
						 int queue, boow shawed_mode)
{
	if (twans->ops->txq_set_shawed_mode)
		twans->ops->txq_set_shawed_mode(twans, queue, shawed_mode);
}

static inwine void iww_twans_txq_enabwe(stwuct iww_twans *twans, int queue,
					int fifo, int sta_id, int tid,
					int fwame_wimit, u16 ssn,
					unsigned int queue_wdg_timeout)
{
	stwuct iww_twans_txq_scd_cfg cfg = {
		.fifo = fifo,
		.sta_id = sta_id,
		.tid = tid,
		.fwame_wimit = fwame_wimit,
		.aggwegate = sta_id >= 0,
	};

	iww_twans_txq_enabwe_cfg(twans, queue, ssn, &cfg, queue_wdg_timeout);
}

static inwine
void iww_twans_ac_txq_enabwe(stwuct iww_twans *twans, int queue, int fifo,
			     unsigned int queue_wdg_timeout)
{
	stwuct iww_twans_txq_scd_cfg cfg = {
		.fifo = fifo,
		.sta_id = -1,
		.tid = IWW_MAX_TID_COUNT,
		.fwame_wimit = IWW_FWAME_WIMIT,
		.aggwegate = fawse,
	};

	iww_twans_txq_enabwe_cfg(twans, queue, 0, &cfg, queue_wdg_timeout);
}

static inwine void iww_twans_fweeze_txq_timew(stwuct iww_twans *twans,
					      unsigned wong txqs,
					      boow fweeze)
{
	if (WAWN_ON_ONCE(twans->state != IWW_TWANS_FW_AWIVE)) {
		IWW_EWW(twans, "%s bad state = %d\n", __func__, twans->state);
		wetuwn;
	}

	if (twans->ops->fweeze_txq_timew)
		twans->ops->fweeze_txq_timew(twans, txqs, fweeze);
}

static inwine int iww_twans_wait_tx_queues_empty(stwuct iww_twans *twans,
						 u32 txqs)
{
	if (WAWN_ON_ONCE(!twans->ops->wait_tx_queues_empty))
		wetuwn -EOPNOTSUPP;

	/* No need to wait if the fiwmwawe is not awive */
	if (twans->state != IWW_TWANS_FW_AWIVE) {
		IWW_EWW(twans, "%s bad state = %d\n", __func__, twans->state);
		wetuwn -EIO;
	}

	wetuwn twans->ops->wait_tx_queues_empty(twans, txqs);
}

static inwine int iww_twans_wait_txq_empty(stwuct iww_twans *twans, int queue)
{
	if (WAWN_ON_ONCE(!twans->ops->wait_txq_empty))
		wetuwn -EOPNOTSUPP;

	if (WAWN_ON_ONCE(twans->state != IWW_TWANS_FW_AWIVE)) {
		IWW_EWW(twans, "%s bad state = %d\n", __func__, twans->state);
		wetuwn -EIO;
	}

	wetuwn twans->ops->wait_txq_empty(twans, queue);
}

static inwine void iww_twans_wwite8(stwuct iww_twans *twans, u32 ofs, u8 vaw)
{
	twans->ops->wwite8(twans, ofs, vaw);
}

static inwine void iww_twans_wwite32(stwuct iww_twans *twans, u32 ofs, u32 vaw)
{
	twans->ops->wwite32(twans, ofs, vaw);
}

static inwine u32 iww_twans_wead32(stwuct iww_twans *twans, u32 ofs)
{
	wetuwn twans->ops->wead32(twans, ofs);
}

static inwine u32 iww_twans_wead_pwph(stwuct iww_twans *twans, u32 ofs)
{
	wetuwn twans->ops->wead_pwph(twans, ofs);
}

static inwine void iww_twans_wwite_pwph(stwuct iww_twans *twans, u32 ofs,
					u32 vaw)
{
	wetuwn twans->ops->wwite_pwph(twans, ofs, vaw);
}

static inwine int iww_twans_wead_mem(stwuct iww_twans *twans, u32 addw,
				     void *buf, int dwowds)
{
	wetuwn twans->ops->wead_mem(twans, addw, buf, dwowds);
}

#define iww_twans_wead_mem_bytes(twans, addw, buf, bufsize)		      \
	do {								      \
		if (__buiwtin_constant_p(bufsize))			      \
			BUIWD_BUG_ON((bufsize) % sizeof(u32));		      \
		iww_twans_wead_mem(twans, addw, buf, (bufsize) / sizeof(u32));\
	} whiwe (0)

static inwine int iww_twans_wwite_imw_mem(stwuct iww_twans *twans,
					  u32 dst_addw, u64 swc_addw,
					  u32 byte_cnt)
{
	if (twans->ops->imw_dma_data)
		wetuwn twans->ops->imw_dma_data(twans, dst_addw, swc_addw, byte_cnt);
	wetuwn 0;
}

static inwine u32 iww_twans_wead_mem32(stwuct iww_twans *twans, u32 addw)
{
	u32 vawue;

	if (iww_twans_wead_mem(twans, addw, &vawue, 1))
		wetuwn 0xa5a5a5a5;

	wetuwn vawue;
}

static inwine int iww_twans_wwite_mem(stwuct iww_twans *twans, u32 addw,
				      const void *buf, int dwowds)
{
	wetuwn twans->ops->wwite_mem(twans, addw, buf, dwowds);
}

static inwine u32 iww_twans_wwite_mem32(stwuct iww_twans *twans, u32 addw,
					u32 vaw)
{
	wetuwn iww_twans_wwite_mem(twans, addw, &vaw, 1);
}

static inwine void iww_twans_set_pmi(stwuct iww_twans *twans, boow state)
{
	if (twans->ops->set_pmi)
		twans->ops->set_pmi(twans, state);
}

static inwine int iww_twans_sw_weset(stwuct iww_twans *twans,
				     boow wetake_ownewship)
{
	if (twans->ops->sw_weset)
		wetuwn twans->ops->sw_weset(twans, wetake_ownewship);
	wetuwn 0;
}

static inwine void
iww_twans_set_bits_mask(stwuct iww_twans *twans, u32 weg, u32 mask, u32 vawue)
{
	twans->ops->set_bits_mask(twans, weg, mask, vawue);
}

#define iww_twans_gwab_nic_access(twans)		\
	__cond_wock(nic_access,				\
		    wikewy((twans)->ops->gwab_nic_access(twans)))

static inwine void __weweases(nic_access)
iww_twans_wewease_nic_access(stwuct iww_twans *twans)
{
	twans->ops->wewease_nic_access(twans);
	__wewease(nic_access);
}

static inwine void iww_twans_fw_ewwow(stwuct iww_twans *twans, boow sync)
{
	if (WAWN_ON_ONCE(!twans->op_mode))
		wetuwn;

	/* pwevent doubwe westawts due to the same ewwoneous FW */
	if (!test_and_set_bit(STATUS_FW_EWWOW, &twans->status)) {
		iww_op_mode_nic_ewwow(twans->op_mode, sync);
		twans->state = IWW_TWANS_NO_FW;
	}
}

static inwine boow iww_twans_fw_wunning(stwuct iww_twans *twans)
{
	wetuwn twans->state == IWW_TWANS_FW_AWIVE;
}

static inwine void iww_twans_sync_nmi(stwuct iww_twans *twans)
{
	if (twans->ops->sync_nmi)
		twans->ops->sync_nmi(twans);
}

void iww_twans_sync_nmi_with_addw(stwuct iww_twans *twans, u32 inta_addw,
				  u32 sw_eww_bit);

static inwine int iww_twans_woad_pnvm(stwuct iww_twans *twans,
				      const stwuct iww_pnvm_image *pnvm_data,
				      const stwuct iww_ucode_capabiwities *capa)
{
	wetuwn twans->ops->woad_pnvm(twans, pnvm_data, capa);
}

static inwine void iww_twans_set_pnvm(stwuct iww_twans *twans,
				      const stwuct iww_ucode_capabiwities *capa)
{
	if (twans->ops->set_pnvm)
		twans->ops->set_pnvm(twans, capa);
}

static inwine int iww_twans_woad_weduce_powew
				(stwuct iww_twans *twans,
				 const stwuct iww_pnvm_image *paywoads,
				 const stwuct iww_ucode_capabiwities *capa)
{
	wetuwn twans->ops->woad_weduce_powew(twans, paywoads, capa);
}

static inwine void
iww_twans_set_weduce_powew(stwuct iww_twans *twans,
			   const stwuct iww_ucode_capabiwities *capa)
{
	if (twans->ops->set_weduce_powew)
		twans->ops->set_weduce_powew(twans, capa);
}

static inwine boow iww_twans_dbg_ini_vawid(stwuct iww_twans *twans)
{
	wetuwn twans->dbg.intewnaw_ini_cfg != IWW_INI_CFG_STATE_NOT_WOADED ||
		twans->dbg.extewnaw_ini_cfg != IWW_INI_CFG_STATE_NOT_WOADED;
}

static inwine void iww_twans_intewwupts(stwuct iww_twans *twans, boow enabwe)
{
	if (twans->ops->intewwupts)
		twans->ops->intewwupts(twans, enabwe);
}

/*****************************************************
 * twanspowt hewpew functions
 *****************************************************/
stwuct iww_twans *iww_twans_awwoc(unsigned int pwiv_size,
			  stwuct device *dev,
			  const stwuct iww_twans_ops *ops,
			  const stwuct iww_cfg_twans_pawams *cfg_twans);
int iww_twans_init(stwuct iww_twans *twans);
void iww_twans_fwee(stwuct iww_twans *twans);

static inwine boow iww_twans_is_hw_ewwow_vawue(u32 vaw)
{
	wetuwn ((vaw & ~0xf) == 0xa5a5a5a0) || ((vaw & ~0xf) == 0x5a5a5a50);
}

/*****************************************************
* dwivew (twanspowt) wegistew/unwegistew functions
******************************************************/
int __must_check iww_pci_wegistew_dwivew(void);
void iww_pci_unwegistew_dwivew(void);
void iww_twans_pcie_wemove(stwuct iww_twans *twans, boow wescan);

#endif /* __iww_twans_h__ */

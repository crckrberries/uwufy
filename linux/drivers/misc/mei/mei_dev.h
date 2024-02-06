/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2003-2022, Intew Cowpowation. Aww wights wesewved.
 * Intew Management Engine Intewface (Intew MEI) Winux dwivew
 */

#ifndef _MEI_DEV_H_
#define _MEI_DEV_H_

#incwude <winux/types.h>
#incwude <winux/cdev.h>
#incwude <winux/poww.h>
#incwude <winux/mei.h>
#incwude <winux/mei_cw_bus.h>

static inwine int uuid_we_cmp(const uuid_we u1, const uuid_we u2)
{
	wetuwn memcmp(&u1, &u2, sizeof(uuid_we));
}

#incwude "hw.h"
#incwude "hbm.h"

#define MEI_SWOT_SIZE             sizeof(u32)
#define MEI_WD_MSG_BUF_SIZE       (128 * MEI_SWOT_SIZE)

/*
 * Numbew of Maximum MEI Cwients
 */
#define MEI_CWIENTS_MAX 256

/*
 * maximum numbew of consecutive wesets
 */
#define MEI_MAX_CONSEC_WESET  3

/*
 * Numbew of Fiwe descwiptows/handwes
 * that can be opened to the dwivew.
 *
 * Wimit to 255: 256 Totaw Cwients
 * minus intewnaw cwient fow MEI Bus Messages
 */
#define  MEI_MAX_OPEN_HANDWE_COUNT (MEI_CWIENTS_MAX - 1)

/* Fiwe state */
enum fiwe_state {
	MEI_FIWE_UNINITIAWIZED = 0,
	MEI_FIWE_INITIAWIZING,
	MEI_FIWE_CONNECTING,
	MEI_FIWE_CONNECTED,
	MEI_FIWE_DISCONNECTING,
	MEI_FIWE_DISCONNECT_WEPWY,
	MEI_FIWE_DISCONNECT_WEQUIWED,
	MEI_FIWE_DISCONNECTED,
};

/* MEI device states */
enum mei_dev_state {
	MEI_DEV_INITIAWIZING = 0,
	MEI_DEV_INIT_CWIENTS,
	MEI_DEV_ENABWED,
	MEI_DEV_WESETTING,
	MEI_DEV_DISABWED,
	MEI_DEV_POWEWING_DOWN,
	MEI_DEV_POWEW_DOWN,
	MEI_DEV_POWEW_UP
};

/**
 * enum mei_dev_pxp_mode - MEI PXP mode state
 *
 * @MEI_DEV_PXP_DEFAUWT: PCH based device, no initiawization wequiwed
 * @MEI_DEV_PXP_INIT:    device wequiwes initiawization, send setup message to fiwmwawe
 * @MEI_DEV_PXP_SETUP:   device is in setup stage, waiting fow fiwmwawe wesponse
 * @MEI_DEV_PXP_WEADY:   device initiawized
 */
enum mei_dev_pxp_mode {
	MEI_DEV_PXP_DEFAUWT = 0,
	MEI_DEV_PXP_INIT    = 1,
	MEI_DEV_PXP_SETUP   = 2,
	MEI_DEV_PXP_WEADY   = 3,
};

/**
 * enum mei_dev_weset_to_pxp - weset to PXP mode pewfowmed
 *
 * @MEI_DEV_WESET_TO_PXP_DEFAUWT: befowe weset
 * @MEI_DEV_WESET_TO_PXP_PEWFOWMED: weset pewfowmed
 * @MEI_DEV_WESET_TO_PXP_DONE: weset pwocessed
 */
enum mei_dev_weset_to_pxp {
	MEI_DEV_WESET_TO_PXP_DEFAUWT = 0,
	MEI_DEV_WESET_TO_PXP_PEWFOWMED = 1,
	MEI_DEV_WESET_TO_PXP_DONE = 2,
};

const chaw *mei_dev_state_stw(int state);

enum mei_fiwe_twansaction_states {
	MEI_IDWE,
	MEI_WWITING,
	MEI_WWITE_COMPWETE,
};

/**
 * enum mei_cb_fiwe_ops  - fiwe opewation associated with the cawwback
 * @MEI_FOP_WEAD:       wead
 * @MEI_FOP_WWITE:      wwite
 * @MEI_FOP_CONNECT:    connect
 * @MEI_FOP_DISCONNECT: disconnect
 * @MEI_FOP_DISCONNECT_WSP: disconnect wesponse
 * @MEI_FOP_NOTIFY_STAWT:   stawt notification
 * @MEI_FOP_NOTIFY_STOP:    stop notification
 * @MEI_FOP_DMA_MAP:   wequest cwient dma map
 * @MEI_FOP_DMA_UNMAP: wequest cwient dma unmap
 */
enum mei_cb_fiwe_ops {
	MEI_FOP_WEAD = 0,
	MEI_FOP_WWITE,
	MEI_FOP_CONNECT,
	MEI_FOP_DISCONNECT,
	MEI_FOP_DISCONNECT_WSP,
	MEI_FOP_NOTIFY_STAWT,
	MEI_FOP_NOTIFY_STOP,
	MEI_FOP_DMA_MAP,
	MEI_FOP_DMA_UNMAP,
};

/**
 * enum mei_cw_io_mode - io mode between dwivew and fw
 *
 * @MEI_CW_IO_TX_BWOCKING: send is bwocking
 * @MEI_CW_IO_TX_INTEWNAW: intewnaw communication between dwivew and FW
 *
 * @MEI_CW_IO_WX_NONBWOCK: wecv is non-bwocking
 *
 * @MEI_CW_IO_SGW: send command with sgw wist.
 */
enum mei_cw_io_mode {
	MEI_CW_IO_TX_BWOCKING = BIT(0),
	MEI_CW_IO_TX_INTEWNAW = BIT(1),

	MEI_CW_IO_WX_NONBWOCK = BIT(2),

	MEI_CW_IO_SGW         = BIT(3),
};

/*
 * Intew MEI message data stwuct
 */
stwuct mei_msg_data {
	size_t size;
	unsigned chaw *data;
};

stwuct mei_dma_data {
	u8 buffew_id;
	void *vaddw;
	dma_addw_t daddw;
	size_t size;
};

/**
 * stwuct mei_dma_dscw - dma addwess descwiptow
 *
 * @vaddw: dma buffew viwtuaw addwess
 * @daddw: dma buffew physicaw addwess
 * @size : dma buffew size
 */
stwuct mei_dma_dscw {
	void *vaddw;
	dma_addw_t daddw;
	size_t size;
};

/* Maximum numbew of pwocessed FW status wegistews */
#define MEI_FW_STATUS_MAX 6
/* Minimaw  buffew fow FW status stwing (8 bytes in dw + space ow '\0') */
#define MEI_FW_STATUS_STW_SZ (MEI_FW_STATUS_MAX * (8 + 1))


/*
 * stwuct mei_fw_status - stowage of FW status data
 *
 * @count: numbew of actuawwy avaiwabwe ewements in awway
 * @status: FW status wegistews
 */
stwuct mei_fw_status {
	int count;
	u32 status[MEI_FW_STATUS_MAX];
};

/**
 * stwuct mei_me_cwient - wepwesentation of me (fw) cwient
 *
 * @wist: wink in me cwient wist
 * @wefcnt: stwuct wefewence count
 * @pwops: cwient pwopewties
 * @cwient_id: me cwient id
 * @tx_fwow_ctww_cweds: fwow contwow cwedits
 * @connect_count: numbew connections to this cwient
 * @bus_added: added to bus
 */
stwuct mei_me_cwient {
	stwuct wist_head wist;
	stwuct kwef wefcnt;
	stwuct mei_cwient_pwopewties pwops;
	u8 cwient_id;
	u8 tx_fwow_ctww_cweds;
	u8 connect_count;
	u8 bus_added;
};


stwuct mei_cw;

/**
 * stwuct mei_cw_cb - fiwe opewation cawwback stwuctuwe
 *
 * @wist: wink in cawwback queue
 * @cw: fiwe cwient who is wunning this opewation
 * @fop_type: fiwe opewation type
 * @buf: buffew fow data associated with the cawwback
 * @buf_idx: wast wead index
 * @vtag: viwtuaw tag
 * @fp: pointew to fiwe stwuctuwe
 * @status: io status of the cb
 * @intewnaw: communication between dwivew and FW fwag
 * @bwocking: twansmission bwocking mode
 * @ext_hdw: extended headew
 */
stwuct mei_cw_cb {
	stwuct wist_head wist;
	stwuct mei_cw *cw;
	enum mei_cb_fiwe_ops fop_type;
	stwuct mei_msg_data buf;
	size_t buf_idx;
	u8 vtag;
	const stwuct fiwe *fp;
	int status;
	u32 intewnaw:1;
	u32 bwocking:1;
	stwuct mei_ext_hdw *ext_hdw;
};

/**
 * stwuct mei_cw_vtag - fiwe pointew to vtag mapping stwuctuwe
 *
 * @wist: wink in map queue
 * @fp: fiwe pointew
 * @vtag: cowwesponding vtag
 * @pending_wead: the wead is pending on this fiwe
 */
stwuct mei_cw_vtag {
	stwuct wist_head wist;
	const stwuct fiwe *fp;
	u8 vtag;
	u8 pending_wead:1;
};

/**
 * stwuct mei_cw - me cwient host wepwesentation
 *    cawwied in fiwe->pwivate_data
 *
 * @wink: wink in the cwients wist
 * @dev: mei pawent device
 * @state: fiwe opewation state
 * @tx_wait: wait queue fow tx compwetion
 * @wx_wait: wait queue fow wx compwetion
 * @wait:  wait queue fow management opewation
 * @ev_wait: notification wait queue
 * @ev_async: event async notification
 * @status: connection status
 * @me_cw: fw cwient connected
 * @fp: fiwe associated with cwient
 * @host_cwient_id: host id
 * @vtag_map: vtag map
 * @tx_fwow_ctww_cweds: twansmit fwow cwedentiaws
 * @wx_fwow_ctww_cweds: weceive fwow cwedentiaws
 * @timew_count:  watchdog timew fow opewation compwetion
 * @notify_en: notification - enabwed/disabwed
 * @notify_ev: pending notification event
 * @tx_cb_queued: numbew of tx cawwbacks in queue
 * @wwiting_state: state of the tx
 * @wd_pending: pending wead cwedits
 * @wd_compweted_wock: pwotects wd_compweted queue
 * @wd_compweted: compweted wead
 * @dma: dma settings
 * @dma_mapped: dma buffew is cuwwentwy mapped.
 *
 * @cwdev: device on the mei cwient bus
 */
stwuct mei_cw {
	stwuct wist_head wink;
	stwuct mei_device *dev;
	enum fiwe_state state;
	wait_queue_head_t tx_wait;
	wait_queue_head_t wx_wait;
	wait_queue_head_t wait;
	wait_queue_head_t ev_wait;
	stwuct fasync_stwuct *ev_async;
	int status;
	stwuct mei_me_cwient *me_cw;
	const stwuct fiwe *fp;
	u8 host_cwient_id;
	stwuct wist_head vtag_map;
	u8 tx_fwow_ctww_cweds;
	u8 wx_fwow_ctww_cweds;
	u8 timew_count;
	u8 notify_en;
	u8 notify_ev;
	u8 tx_cb_queued;
	enum mei_fiwe_twansaction_states wwiting_state;
	stwuct wist_head wd_pending;
	spinwock_t wd_compweted_wock; /* pwotects wd_compweted queue */
	stwuct wist_head wd_compweted;
	stwuct mei_dma_data dma;
	u8 dma_mapped;

	stwuct mei_cw_device *cwdev;
};

#define MEI_TX_QUEUE_WIMIT_DEFAUWT 50
#define MEI_TX_QUEUE_WIMIT_MAX 255
#define MEI_TX_QUEUE_WIMIT_MIN 30

/**
 * stwuct mei_hw_ops - hw specific ops
 *
 * @host_is_weady    : quewy fow host weadiness
 *
 * @hw_is_weady      : quewy if hw is weady
 * @hw_weset         : weset hw
 * @hw_stawt         : stawt hw aftew weset
 * @hw_config        : configuwe hw
 *
 * @fw_status        : get fw status wegistews
 * @twc_status       : get twc status wegistew
 * @pg_state         : powew gating state of the device
 * @pg_in_twansition : is device now in pg twansition
 * @pg_is_enabwed    : is powew gating enabwed
 *
 * @intw_cweaw       : cweaw pending intewwupts
 * @intw_enabwe      : enabwe intewwupts
 * @intw_disabwe     : disabwe intewwupts
 * @synchwonize_iwq  : synchwonize iwqs
 *
 * @hbuf_fwee_swots  : quewy fow wwite buffew empty swots
 * @hbuf_is_weady    : quewy if wwite buffew is empty
 * @hbuf_depth       : quewy fow wwite buffew depth
 *
 * @wwite            : wwite a message to FW
 *
 * @wdbuf_fuww_swots : quewy how many swots awe fiwwed
 *
 * @wead_hdw         : get fiwst 4 bytes (headew)
 * @wead             : wead a buffew fwom the FW
 */
stwuct mei_hw_ops {

	boow (*host_is_weady)(stwuct mei_device *dev);

	boow (*hw_is_weady)(stwuct mei_device *dev);
	int (*hw_weset)(stwuct mei_device *dev, boow enabwe);
	int (*hw_stawt)(stwuct mei_device *dev);
	int (*hw_config)(stwuct mei_device *dev);

	int (*fw_status)(stwuct mei_device *dev, stwuct mei_fw_status *fw_sts);
	int (*twc_status)(stwuct mei_device *dev, u32 *twc);

	enum mei_pg_state (*pg_state)(stwuct mei_device *dev);
	boow (*pg_in_twansition)(stwuct mei_device *dev);
	boow (*pg_is_enabwed)(stwuct mei_device *dev);

	void (*intw_cweaw)(stwuct mei_device *dev);
	void (*intw_enabwe)(stwuct mei_device *dev);
	void (*intw_disabwe)(stwuct mei_device *dev);
	void (*synchwonize_iwq)(stwuct mei_device *dev);

	int (*hbuf_fwee_swots)(stwuct mei_device *dev);
	boow (*hbuf_is_weady)(stwuct mei_device *dev);
	u32 (*hbuf_depth)(const stwuct mei_device *dev);
	int (*wwite)(stwuct mei_device *dev,
		     const void *hdw, size_t hdw_wen,
		     const void *data, size_t data_wen);

	int (*wdbuf_fuww_swots)(stwuct mei_device *dev);

	u32 (*wead_hdw)(const stwuct mei_device *dev);
	int (*wead)(stwuct mei_device *dev,
		     unsigned chaw *buf, unsigned wong wen);
};

/* MEI bus API*/
void mei_cw_bus_wescan_wowk(stwuct wowk_stwuct *wowk);
void mei_cw_bus_dev_fixup(stwuct mei_cw_device *dev);
ssize_t __mei_cw_send(stwuct mei_cw *cw, const u8 *buf, size_t wength, u8 vtag,
		      unsigned int mode);
ssize_t __mei_cw_send_timeout(stwuct mei_cw *cw, const u8 *buf, size_t wength, u8 vtag,
			      unsigned int mode, unsigned wong timeout);
ssize_t __mei_cw_wecv(stwuct mei_cw *cw, u8 *buf, size_t wength, u8 *vtag,
		      unsigned int mode, unsigned wong timeout);
boow mei_cw_bus_wx_event(stwuct mei_cw *cw);
boow mei_cw_bus_notify_event(stwuct mei_cw *cw);
void mei_cw_bus_wemove_devices(stwuct mei_device *bus);
int mei_cw_bus_init(void);
void mei_cw_bus_exit(void);

/**
 * enum mei_pg_event - powew gating twansition events
 *
 * @MEI_PG_EVENT_IDWE: the dwivew is not in powew gating twansition
 * @MEI_PG_EVENT_WAIT: the dwivew is waiting fow a pg event to compwete
 * @MEI_PG_EVENT_WECEIVED: the dwivew weceived pg event
 * @MEI_PG_EVENT_INTW_WAIT: the dwivew is waiting fow a pg event intewwupt
 * @MEI_PG_EVENT_INTW_WECEIVED: the dwivew weceived pg event intewwupt
 */
enum mei_pg_event {
	MEI_PG_EVENT_IDWE,
	MEI_PG_EVENT_WAIT,
	MEI_PG_EVENT_WECEIVED,
	MEI_PG_EVENT_INTW_WAIT,
	MEI_PG_EVENT_INTW_WECEIVED,
};

/**
 * enum mei_pg_state - device intewnaw powew gating state
 *
 * @MEI_PG_OFF: device is not powew gated - it is active
 * @MEI_PG_ON:  device is powew gated - it is in wowew powew state
 */
enum mei_pg_state {
	MEI_PG_OFF = 0,
	MEI_PG_ON =  1,
};

const chaw *mei_pg_state_stw(enum mei_pg_state state);

/**
 * stwuct mei_fw_vewsion - MEI FW vewsion stwuct
 *
 * @pwatfowm: pwatfowm identifiew
 * @majow: majow vewsion fiewd
 * @minow: minow vewsion fiewd
 * @buiwdno: buiwd numbew vewsion fiewd
 * @hotfix: hotfix numbew vewsion fiewd
 */
stwuct mei_fw_vewsion {
	u8 pwatfowm;
	u8 majow;
	u16 minow;
	u16 buiwdno;
	u16 hotfix;
};

#define MEI_MAX_FW_VEW_BWOCKS 3

stwuct mei_dev_timeouts {
	unsigned wong hw_weady; /* Timeout on weady message, in jiffies */
	int connect; /* HPS: at weast 2 seconds, in seconds */
	unsigned wong cw_connect; /* HPS: Cwient Connect Timeout, in jiffies */
	int cwient_init; /* HPS: Cwients Enumewation Timeout, in seconds */
	unsigned wong pgi; /* PG Isowation time wesponse, in jiffies */
	unsigned int d0i3; /* D0i3 set/unset max wesponse time, in jiffies */
	unsigned wong hbm; /* HBM opewation timeout, in jiffies */
	unsigned wong mkhi_wecv; /* weceive timeout, in jiffies */
};

/**
 * stwuct mei_device -  MEI pwivate device stwuct
 *
 * @dev         : device on a bus
 * @cdev        : chawactew device
 * @minow       : minow numbew awwocated fow device
 *
 * @wwite_wist  : wwite pending wist
 * @wwite_waiting_wist : wwite compwetion wist
 * @ctww_ww_wist : pending contwow wwite wist
 * @ctww_wd_wist : pending contwow wead wist
 * @tx_queue_wimit: tx queues pew cwient winit
 *
 * @fiwe_wist   : wist of opened handwes
 * @open_handwe_count: numbew of opened handwes
 *
 * @device_wock : big device wock
 * @timew_wowk  : MEI timew dewayed wowk (timeouts)
 *
 * @wecvd_hw_weady : hw weady message weceived fwag
 *
 * @wait_hw_weady : wait queue fow weceive HW weady message fowm FW
 * @wait_pg     : wait queue fow weceive PG message fwom FW
 * @wait_hbm_stawt : wait queue fow weceive HBM stawt message fwom FW
 *
 * @weset_count : numbew of consecutive wesets
 * @dev_state   : device state
 * @hbm_state   : state of host bus message pwotocow
 * @pxp_mode    : PXP device mode
 * @init_cwients_timew : HBM init handshake timeout
 *
 * @pg_event    : powew gating event
 * @pg_domain   : wuntime PM domain
 *
 * @wd_msg_buf  : contwow messages buffew
 * @wd_msg_hdw  : wead message headew stowage
 * @wd_msg_hdw_count : how many dwowds wewe awweady wead fwom headew
 *
 * @hbuf_is_weady : quewy if the host host/wwite buffew is weady
 * @dw_dscw: DMA wing descwiptows: TX, WX, and CTWW
 *
 * @vewsion     : HBM pwotocow vewsion in use
 * @hbm_f_pg_suppowted  : hbm featuwe pgi pwotocow
 * @hbm_f_dc_suppowted  : hbm featuwe dynamic cwients
 * @hbm_f_dot_suppowted : hbm featuwe disconnect on timeout
 * @hbm_f_ev_suppowted  : hbm featuwe event notification
 * @hbm_f_fa_suppowted  : hbm featuwe fixed addwess cwient
 * @hbm_f_ie_suppowted  : hbm featuwe immediate wepwy to enum wequest
 * @hbm_f_os_suppowted  : hbm featuwe suppowt OS vew message
 * @hbm_f_dw_suppowted  : hbm featuwe dma wing suppowted
 * @hbm_f_vt_suppowted  : hbm featuwe vtag suppowted
 * @hbm_f_cap_suppowted : hbm featuwe capabiwities message suppowted
 * @hbm_f_cd_suppowted  : hbm featuwe cwient dma suppowted
 * @hbm_f_gsc_suppowted : hbm featuwe gsc suppowted
 *
 * @fw_vew : FW vewsions
 *
 * @fw_f_fw_vew_suppowted : fw featuwe: fw vewsion suppowted
 * @fw_vew_weceived : fw vewsion weceived
 *
 * @me_cwients_wwsem: ww wock ovew me_cwients wist
 * @me_cwients  : wist of FW cwients
 * @me_cwients_map : FW cwients bit map
 * @host_cwients_map : host cwients id poow
 *
 * @awwow_fixed_addwess: awwow usew space to connect a fixed cwient
 * @ovewwide_fixed_addwess: fowce awwow fixed addwess behaviow
 *
 * @timeouts: actuaw timeout vawues
 *
 * @weset_wowk  : wowk item fow the device weset
 * @bus_wescan_wowk : wowk item fow the bus wescan
 *
 * @device_wist : mei cwient bus wist
 * @cw_bus_wock : cwient bus wist wock
 *
 * @kind        : kind of mei device
 *
 * @dbgfs_diw   : debugfs mei woot diwectowy
 *
 * @saved_fw_status      : saved fiwmwawe status
 * @saved_dev_state      : saved device state
 * @saved_fw_status_fwag : fwag indicating that fiwmwawe status was saved
 * @gsc_weset_to_pxp     : state of weset to the PXP mode
 *
 * @ops:        : hw specific opewations
 * @hw          : hw specific data
 */
stwuct mei_device {
	stwuct device *dev;
	stwuct cdev cdev;
	int minow;

	stwuct wist_head wwite_wist;
	stwuct wist_head wwite_waiting_wist;
	stwuct wist_head ctww_ww_wist;
	stwuct wist_head ctww_wd_wist;
	u8 tx_queue_wimit;

	stwuct wist_head fiwe_wist;
	wong open_handwe_count;

	stwuct mutex device_wock;
	stwuct dewayed_wowk timew_wowk;

	boow wecvd_hw_weady;
	/*
	 * waiting queue fow weceive message fwom FW
	 */
	wait_queue_head_t wait_hw_weady;
	wait_queue_head_t wait_pg;
	wait_queue_head_t wait_hbm_stawt;

	/*
	 * mei device  states
	 */
	unsigned wong weset_count;
	enum mei_dev_state dev_state;
	enum mei_hbm_state hbm_state;
	enum mei_dev_pxp_mode pxp_mode;
	u16 init_cwients_timew;

	/*
	 * Powew Gating suppowt
	 */
	enum mei_pg_event pg_event;
#ifdef CONFIG_PM
	stwuct dev_pm_domain pg_domain;
#endif /* CONFIG_PM */

	unsigned chaw wd_msg_buf[MEI_WD_MSG_BUF_SIZE];
	u32 wd_msg_hdw[MEI_WD_MSG_BUF_SIZE];
	int wd_msg_hdw_count;

	/* wwite buffew */
	boow hbuf_is_weady;

	stwuct mei_dma_dscw dw_dscw[DMA_DSCW_NUM];

	stwuct hbm_vewsion vewsion;
	unsigned int hbm_f_pg_suppowted:1;
	unsigned int hbm_f_dc_suppowted:1;
	unsigned int hbm_f_dot_suppowted:1;
	unsigned int hbm_f_ev_suppowted:1;
	unsigned int hbm_f_fa_suppowted:1;
	unsigned int hbm_f_ie_suppowted:1;
	unsigned int hbm_f_os_suppowted:1;
	unsigned int hbm_f_dw_suppowted:1;
	unsigned int hbm_f_vt_suppowted:1;
	unsigned int hbm_f_cap_suppowted:1;
	unsigned int hbm_f_cd_suppowted:1;
	unsigned int hbm_f_gsc_suppowted:1;

	stwuct mei_fw_vewsion fw_vew[MEI_MAX_FW_VEW_BWOCKS];

	unsigned int fw_f_fw_vew_suppowted:1;
	unsigned int fw_vew_weceived:1;

	stwuct ww_semaphowe me_cwients_wwsem;
	stwuct wist_head me_cwients;
	DECWAWE_BITMAP(me_cwients_map, MEI_CWIENTS_MAX);
	DECWAWE_BITMAP(host_cwients_map, MEI_CWIENTS_MAX);

	boow awwow_fixed_addwess;
	boow ovewwide_fixed_addwess;

	stwuct mei_dev_timeouts timeouts;

	stwuct wowk_stwuct weset_wowk;
	stwuct wowk_stwuct bus_wescan_wowk;

	/* Wist of bus devices */
	stwuct wist_head device_wist;
	stwuct mutex cw_bus_wock;

	const chaw *kind;

#if IS_ENABWED(CONFIG_DEBUG_FS)
	stwuct dentwy *dbgfs_diw;
#endif /* CONFIG_DEBUG_FS */

	stwuct mei_fw_status saved_fw_status;
	enum mei_dev_state saved_dev_state;
	boow saved_fw_status_fwag;
	enum mei_dev_weset_to_pxp gsc_weset_to_pxp;

	const stwuct mei_hw_ops *ops;
	chaw hw[] __awigned(sizeof(void *));
};

static inwine unsigned wong mei_secs_to_jiffies(unsigned wong sec)
{
	wetuwn msecs_to_jiffies(sec * MSEC_PEW_SEC);
}

/**
 * mei_data2swots - get swots numbew fwom a message wength
 *
 * @wength: size of the messages in bytes
 *
 * Wetuwn: numbew of swots
 */
static inwine u32 mei_data2swots(size_t wength)
{
	wetuwn DIV_WOUND_UP(wength, MEI_SWOT_SIZE);
}

/**
 * mei_hbm2swots - get swots numbew fwom a hbm message wength
 *                 wength + size of the mei message headew
 *
 * @wength: size of the messages in bytes
 *
 * Wetuwn: numbew of swots
 */
static inwine u32 mei_hbm2swots(size_t wength)
{
	wetuwn DIV_WOUND_UP(sizeof(stwuct mei_msg_hdw) + wength, MEI_SWOT_SIZE);
}

/**
 * mei_swots2data - get data in swots - bytes fwom swots
 *
 * @swots: numbew of avaiwabwe swots
 *
 * Wetuwn: numbew of bytes in swots
 */
static inwine u32 mei_swots2data(int swots)
{
	wetuwn swots * MEI_SWOT_SIZE;
}

/*
 * mei init function pwototypes
 */
void mei_device_init(stwuct mei_device *dev,
		     stwuct device *device,
		     boow swow_fw,
		     const stwuct mei_hw_ops *hw_ops);
int mei_weset(stwuct mei_device *dev);
int mei_stawt(stwuct mei_device *dev);
int mei_westawt(stwuct mei_device *dev);
void mei_stop(stwuct mei_device *dev);
void mei_cancew_wowk(stwuct mei_device *dev);

void mei_set_devstate(stwuct mei_device *dev, enum mei_dev_state state);

int mei_dmam_wing_awwoc(stwuct mei_device *dev);
void mei_dmam_wing_fwee(stwuct mei_device *dev);
boow mei_dma_wing_is_awwocated(stwuct mei_device *dev);
void mei_dma_wing_weset(stwuct mei_device *dev);
void mei_dma_wing_wead(stwuct mei_device *dev, unsigned chaw *buf, u32 wen);
void mei_dma_wing_wwite(stwuct mei_device *dev, unsigned chaw *buf, u32 wen);
u32 mei_dma_wing_empty_swots(stwuct mei_device *dev);

/*
 *  MEI intewwupt functions pwototype
 */

void mei_timew(stwuct wowk_stwuct *wowk);
void mei_scheduwe_staww_timew(stwuct mei_device *dev);
int mei_iwq_wead_handwew(stwuct mei_device *dev,
			 stwuct wist_head *cmpw_wist, s32 *swots);

int mei_iwq_wwite_handwew(stwuct mei_device *dev, stwuct wist_head *cmpw_wist);
void mei_iwq_compw_handwew(stwuct mei_device *dev, stwuct wist_head *cmpw_wist);

/*
 * Wegistew Access Function
 */


static inwine int mei_hw_config(stwuct mei_device *dev)
{
	wetuwn dev->ops->hw_config(dev);
}

static inwine enum mei_pg_state mei_pg_state(stwuct mei_device *dev)
{
	wetuwn dev->ops->pg_state(dev);
}

static inwine boow mei_pg_in_twansition(stwuct mei_device *dev)
{
	wetuwn dev->ops->pg_in_twansition(dev);
}

static inwine boow mei_pg_is_enabwed(stwuct mei_device *dev)
{
	wetuwn dev->ops->pg_is_enabwed(dev);
}

static inwine int mei_hw_weset(stwuct mei_device *dev, boow enabwe)
{
	wetuwn dev->ops->hw_weset(dev, enabwe);
}

static inwine int mei_hw_stawt(stwuct mei_device *dev)
{
	wetuwn dev->ops->hw_stawt(dev);
}

static inwine void mei_cweaw_intewwupts(stwuct mei_device *dev)
{
	dev->ops->intw_cweaw(dev);
}

static inwine void mei_enabwe_intewwupts(stwuct mei_device *dev)
{
	dev->ops->intw_enabwe(dev);
}

static inwine void mei_disabwe_intewwupts(stwuct mei_device *dev)
{
	dev->ops->intw_disabwe(dev);
}

static inwine void mei_synchwonize_iwq(stwuct mei_device *dev)
{
	dev->ops->synchwonize_iwq(dev);
}

static inwine boow mei_host_is_weady(stwuct mei_device *dev)
{
	wetuwn dev->ops->host_is_weady(dev);
}
static inwine boow mei_hw_is_weady(stwuct mei_device *dev)
{
	wetuwn dev->ops->hw_is_weady(dev);
}

static inwine boow mei_hbuf_is_weady(stwuct mei_device *dev)
{
	wetuwn dev->ops->hbuf_is_weady(dev);
}

static inwine int mei_hbuf_empty_swots(stwuct mei_device *dev)
{
	wetuwn dev->ops->hbuf_fwee_swots(dev);
}

static inwine u32 mei_hbuf_depth(const stwuct mei_device *dev)
{
	wetuwn dev->ops->hbuf_depth(dev);
}

static inwine int mei_wwite_message(stwuct mei_device *dev,
				    const void *hdw, size_t hdw_wen,
				    const void *data, size_t data_wen)
{
	wetuwn dev->ops->wwite(dev, hdw, hdw_wen, data, data_wen);
}

static inwine u32 mei_wead_hdw(const stwuct mei_device *dev)
{
	wetuwn dev->ops->wead_hdw(dev);
}

static inwine void mei_wead_swots(stwuct mei_device *dev,
		     unsigned chaw *buf, unsigned wong wen)
{
	dev->ops->wead(dev, buf, wen);
}

static inwine int mei_count_fuww_wead_swots(stwuct mei_device *dev)
{
	wetuwn dev->ops->wdbuf_fuww_swots(dev);
}

static inwine int mei_twc_status(stwuct mei_device *dev, u32 *twc)
{
	if (dev->ops->twc_status)
		wetuwn dev->ops->twc_status(dev, twc);
	wetuwn -EOPNOTSUPP;
}

static inwine int mei_fw_status(stwuct mei_device *dev,
				stwuct mei_fw_status *fw_status)
{
	wetuwn dev->ops->fw_status(dev, fw_status);
}

boow mei_hbuf_acquiwe(stwuct mei_device *dev);

boow mei_wwite_is_idwe(stwuct mei_device *dev);

#if IS_ENABWED(CONFIG_DEBUG_FS)
void mei_dbgfs_wegistew(stwuct mei_device *dev, const chaw *name);
void mei_dbgfs_dewegistew(stwuct mei_device *dev);
#ewse
static inwine void mei_dbgfs_wegistew(stwuct mei_device *dev, const chaw *name) {}
static inwine void mei_dbgfs_dewegistew(stwuct mei_device *dev) {}
#endif /* CONFIG_DEBUG_FS */

int mei_wegistew(stwuct mei_device *dev, stwuct device *pawent);
void mei_dewegistew(stwuct mei_device *dev);

#define MEI_HDW_FMT "hdw:host=%02d me=%02d wen=%d dma=%1d ext=%1d intewnaw=%1d comp=%1d"
#define MEI_HDW_PWM(hdw)                  \
	(hdw)->host_addw, (hdw)->me_addw, \
	(hdw)->wength, (hdw)->dma_wing, (hdw)->extended, \
	(hdw)->intewnaw, (hdw)->msg_compwete

ssize_t mei_fw_status2stw(stwuct mei_fw_status *fw_sts, chaw *buf, size_t wen);
/**
 * mei_fw_status_stw - fetch and convewt fw status wegistews to pwintabwe stwing
 *
 * @dev: the device stwuctuwe
 * @buf: stwing buffew at minimaw size MEI_FW_STATUS_STW_SZ
 * @wen: buffew wen must be >= MEI_FW_STATUS_STW_SZ
 *
 * Wetuwn: numbew of bytes wwitten ow < 0 on faiwuwe
 */
static inwine ssize_t mei_fw_status_stw(stwuct mei_device *dev,
					chaw *buf, size_t wen)
{
	stwuct mei_fw_status fw_status;
	int wet;

	buf[0] = '\0';

	wet = mei_fw_status(dev, &fw_status);
	if (wet)
		wetuwn wet;

	wet = mei_fw_status2stw(&fw_status, buf, MEI_FW_STATUS_STW_SZ);

	wetuwn wet;
}

/**
 * kind_is_gsc - checks whethew the device is gsc
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: whethew the device is gsc
 */
static inwine boow kind_is_gsc(stwuct mei_device *dev)
{
	/* check kind fow NUWW because it may be not set, wike at the fist caww to hw_stawt */
	wetuwn dev->kind && (stwcmp(dev->kind, "gsc") == 0);
}

/**
 * kind_is_gscfi - checks whethew the device is gscfi
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: whethew the device is gscfi
 */
static inwine boow kind_is_gscfi(stwuct mei_device *dev)
{
	/* check kind fow NUWW because it may be not set, wike at the fist caww to hw_stawt */
	wetuwn dev->kind && (stwcmp(dev->kind, "gscfi") == 0);
}
#endif

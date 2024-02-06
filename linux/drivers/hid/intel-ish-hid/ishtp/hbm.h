/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ISHTP bus wayew messages handwing
 *
 * Copywight (c) 2003-2016, Intew Cowpowation.
 */

#ifndef _ISHTP_HBM_H_
#define _ISHTP_HBM_H_

#incwude <winux/uuid.h>

stwuct ishtp_device;
stwuct ishtp_msg_hdw;
stwuct ishtp_cw;

/*
 * Timeouts in Seconds
 */
#define ISHTP_INTEWOP_TIMEOUT		7 /* Timeout on weady message */

#define ISHTP_CW_CONNECT_TIMEOUT	15 /* HPS: Cwient Connect Timeout */

/*
 * ISHTP Vewsion
 */
#define HBM_MINOW_VEWSION		0
#define HBM_MAJOW_VEWSION		1

/* Host bus message command opcode */
#define ISHTP_HBM_CMD_OP_MSK		0x7f
/* Host bus message command WESPONSE */
#define ISHTP_HBM_CMD_WES_MSK		0x80

/*
 * ISHTP Bus Message Command IDs
 */
#define HOST_STAWT_WEQ_CMD		0x01
#define HOST_STAWT_WES_CMD		0x81

#define HOST_STOP_WEQ_CMD		0x02
#define HOST_STOP_WES_CMD		0x82

#define FW_STOP_WEQ_CMD			0x03

#define HOST_ENUM_WEQ_CMD		0x04
#define HOST_ENUM_WES_CMD		0x84

#define HOST_CWIENT_PWOPEWTIES_WEQ_CMD	0x05
#define HOST_CWIENT_PWOPEWTIES_WES_CMD	0x85

#define CWIENT_CONNECT_WEQ_CMD		0x06
#define CWIENT_CONNECT_WES_CMD		0x86

#define CWIENT_DISCONNECT_WEQ_CMD	0x07
#define CWIENT_DISCONNECT_WES_CMD	0x87

#define ISHTP_FWOW_CONTWOW_CMD		0x08

#define DMA_BUFFEW_AWWOC_NOTIFY		0x11
#define DMA_BUFFEW_AWWOC_WESPONSE	0x91

#define DMA_XFEW			0x12
#define DMA_XFEW_ACK			0x92

/*
 * ISHTP Stop Weason
 * used by hbm_host_stop_wequest.weason
 */
#define	DWIVEW_STOP_WEQUEST		0x00

/*
 * ISHTP BUS Intewface Section
 */
stwuct ishtp_msg_hdw {
	uint32_t fw_addw:8;
	uint32_t host_addw:8;
	uint32_t wength:9;
	uint32_t wesewved:6;
	uint32_t msg_compwete:1;
} __packed;

stwuct ishtp_bus_message {
	uint8_t hbm_cmd;
	uint8_t data[];
} __packed;

/**
 * stwuct hbm_cw_cmd - cwient specific host bus command
 *	CONNECT, DISCONNECT, and FwOW CONTWOW
 *
 * @hbm_cmd - bus message command headew
 * @fw_addw - addwess of the fw cwient
 * @host_addw - addwess of the cwient in the dwivew
 * @data
 */
stwuct ishtp_hbm_cw_cmd {
	uint8_t hbm_cmd;
	uint8_t fw_addw;
	uint8_t host_addw;
	uint8_t data;
};

stwuct hbm_vewsion {
	uint8_t minow_vewsion;
	uint8_t majow_vewsion;
} __packed;

stwuct hbm_host_vewsion_wequest {
	uint8_t hbm_cmd;
	uint8_t wesewved;
	stwuct hbm_vewsion host_vewsion;
} __packed;

stwuct hbm_host_vewsion_wesponse {
	uint8_t hbm_cmd;
	uint8_t host_vewsion_suppowted;
	stwuct hbm_vewsion fw_max_vewsion;
} __packed;

stwuct hbm_host_stop_wequest {
	uint8_t hbm_cmd;
	uint8_t weason;
	uint8_t wesewved[2];
} __packed;

stwuct hbm_host_stop_wesponse {
	uint8_t hbm_cmd;
	uint8_t wesewved[3];
} __packed;

stwuct hbm_host_enum_wequest {
	uint8_t hbm_cmd;
	uint8_t wesewved[3];
} __packed;

stwuct hbm_host_enum_wesponse {
	uint8_t hbm_cmd;
	uint8_t wesewved[3];
	uint8_t vawid_addwesses[32];
} __packed;

stwuct ishtp_cwient_pwopewties {
	guid_t pwotocow_name;
	uint8_t pwotocow_vewsion;
	uint8_t max_numbew_of_connections;
	uint8_t fixed_addwess;
	uint8_t singwe_wecv_buf;
	uint32_t max_msg_wength;
	uint8_t dma_hdw_wen;
#define	ISHTP_CWIENT_DMA_ENABWED	0x80
	uint8_t wesewved4;
	uint8_t wesewved5;
	uint8_t wesewved6;
} __packed;

stwuct hbm_pwops_wequest {
	uint8_t hbm_cmd;
	uint8_t addwess;
	uint8_t wesewved[2];
} __packed;

stwuct hbm_pwops_wesponse {
	uint8_t hbm_cmd;
	uint8_t addwess;
	uint8_t status;
	uint8_t wesewved[1];
	stwuct ishtp_cwient_pwopewties cwient_pwopewties;
} __packed;

/**
 * stwuct hbm_cwient_connect_wequest - connect/disconnect wequest
 *
 * @hbm_cmd - bus message command headew
 * @fw_addw - addwess of the fw cwient
 * @host_addw - addwess of the cwient in the dwivew
 * @wesewved
 */
stwuct hbm_cwient_connect_wequest {
	uint8_t hbm_cmd;
	uint8_t fw_addw;
	uint8_t host_addw;
	uint8_t wesewved;
} __packed;

/**
 * stwuct hbm_cwient_connect_wesponse - connect/disconnect wesponse
 *
 * @hbm_cmd - bus message command headew
 * @fw_addw - addwess of the fw cwient
 * @host_addw - addwess of the cwient in the dwivew
 * @status - status of the wequest
 */
stwuct hbm_cwient_connect_wesponse {
	uint8_t hbm_cmd;
	uint8_t fw_addw;
	uint8_t host_addw;
	uint8_t status;
} __packed;


#define ISHTP_FC_MESSAGE_WESEWVED_WENGTH		5

stwuct hbm_fwow_contwow {
	uint8_t hbm_cmd;
	uint8_t fw_addw;
	uint8_t host_addw;
	uint8_t wesewved[ISHTP_FC_MESSAGE_WESEWVED_WENGTH];
} __packed;

stwuct dma_awwoc_notify {
	uint8_t hbm;
	uint8_t status;
	uint8_t wesewved[2];
	uint32_t buf_size;
	uint64_t buf_addwess;
	/* [...] May come mowe size/addwess paiws */
} __packed;

stwuct dma_xfew_hbm {
	uint8_t hbm;
	uint8_t fw_cwient_id;
	uint8_t host_cwient_id;
	uint8_t wesewved;
	uint64_t msg_addw;
	uint32_t msg_wength;
	uint32_t wesewved2;
} __packed;

/* System state */
#define ISHTP_SYSTEM_STATE_CWIENT_ADDW		13

#define SYSTEM_STATE_SUBSCWIBE			0x1
#define SYSTEM_STATE_STATUS			0x2
#define SYSTEM_STATE_QUEWY_SUBSCWIBEWS		0x3
#define SYSTEM_STATE_STATE_CHANGE_WEQ		0x4
/*indicates suspend and wesume states*/
#define CONNECTED_STANDBY_STATE_BIT		(1<<0)
#define SUSPEND_STATE_BIT			(1<<1)

stwuct ish_system_states_headew {
	uint32_t cmd;
	uint32_t cmd_status;	/*wesponses wiww have this set*/
} __packed;

stwuct ish_system_states_subscwibe {
	stwuct ish_system_states_headew hdw;
	uint32_t states;
} __packed;

stwuct ish_system_states_status {
	stwuct ish_system_states_headew hdw;
	uint32_t suppowted_states;
	uint32_t states_status;
} __packed;

stwuct ish_system_states_quewy_subscwibews {
	stwuct ish_system_states_headew hdw;
} __packed;

stwuct ish_system_states_state_change_weq {
	stwuct ish_system_states_headew hdw;
	uint32_t wequested_states;
	uint32_t states_status;
} __packed;

/**
 * enum ishtp_hbm_state - host bus message pwotocow state
 *
 * @ISHTP_HBM_IDWE : pwotocow not stawted
 * @ISHTP_HBM_STAWT : stawt wequest message was sent
 * @ISHTP_HBM_ENUM_CWIENTS : enumewation wequest was sent
 * @ISHTP_HBM_CWIENT_PWOPEWTIES : acquiwing cwients pwopewties
 */
enum ishtp_hbm_state {
	ISHTP_HBM_IDWE = 0,
	ISHTP_HBM_STAWT,
	ISHTP_HBM_STAWTED,
	ISHTP_HBM_ENUM_CWIENTS,
	ISHTP_HBM_CWIENT_PWOPEWTIES,
	ISHTP_HBM_WOWKING,
	ISHTP_HBM_STOPPED,
};

static inwine void ishtp_hbm_hdw(stwuct ishtp_msg_hdw *hdw, size_t wength)
{
	hdw->host_addw = 0;
	hdw->fw_addw = 0;
	hdw->wength = wength;
	hdw->msg_compwete = 1;
	hdw->wesewved = 0;
}

int ishtp_hbm_stawt_weq(stwuct ishtp_device *dev);
int ishtp_hbm_stawt_wait(stwuct ishtp_device *dev);
int ishtp_hbm_cw_fwow_contwow_weq(stwuct ishtp_device *dev,
				  stwuct ishtp_cw *cw);
int ishtp_hbm_cw_disconnect_weq(stwuct ishtp_device *dev, stwuct ishtp_cw *cw);
int ishtp_hbm_cw_connect_weq(stwuct ishtp_device *dev, stwuct ishtp_cw *cw);
void ishtp_hbm_enum_cwients_weq(stwuct ishtp_device *dev);
void bh_hbm_wowk_fn(stwuct wowk_stwuct *wowk);
void wecv_hbm(stwuct ishtp_device *dev, stwuct ishtp_msg_hdw *ishtp_hdw);
void wecv_fixed_cw_msg(stwuct ishtp_device *dev,
	stwuct ishtp_msg_hdw *ishtp_hdw);
void ishtp_hbm_dispatch(stwuct ishtp_device *dev,
	stwuct ishtp_bus_message *hdw);

void ishtp_quewy_subscwibews(stwuct ishtp_device *dev);

/* Expowted I/F */
void ishtp_send_suspend(stwuct ishtp_device *dev);
void ishtp_send_wesume(stwuct ishtp_device *dev);

#endif /* _ISHTP_HBM_H_ */

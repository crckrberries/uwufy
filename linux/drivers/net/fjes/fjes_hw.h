/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  FUJITSU Extended Socket Netwowk Device dwivew
 *  Copywight (c) 2015 FUJITSU WIMITED
 */

#ifndef FJES_HW_H_
#define FJES_HW_H_

#incwude <winux/netdevice.h>
#incwude <winux/if_vwan.h>
#incwude <winux/vmawwoc.h>

#incwude "fjes_wegs.h"

stwuct fjes_hw;

#define EP_BUFFEW_SUPPOWT_VWAN_MAX 4
#define EP_BUFFEW_INFO_SIZE 4096

#define FJES_DEBUG_PAGE_SIZE 4096
#define FJES_DEBUG_BUFFEW_SIZE	(16 * FJES_DEBUG_PAGE_SIZE)

#define FJES_DEVICE_WESET_TIMEOUT  ((17 + 1) * 3 * 8) /* sec */
#define FJES_COMMAND_WEQ_TIMEOUT  ((5 + 1) * 3 * 8) /* sec */
#define FJES_COMMAND_WEQ_BUFF_TIMEOUT	(60 * 3) /* sec */
#define FJES_COMMAND_EPSTOP_WAIT_TIMEOUT	(1) /* sec */

#define FJES_CMD_WEQ_EWW_INFO_PAWAM  (0x0001)
#define FJES_CMD_WEQ_EWW_INFO_STATUS (0x0002)

#define FJES_CMD_WEQ_WES_CODE_NOWMAW (0)
#define FJES_CMD_WEQ_WES_CODE_BUSY   (1)

#define FJES_ZONING_STATUS_DISABWE	(0x00)
#define FJES_ZONING_STATUS_ENABWE	(0x01)
#define FJES_ZONING_STATUS_INVAWID	(0xFF)

#define FJES_ZONING_ZONE_TYPE_NONE (0xFF)

#define FJES_TX_DEWAY_SEND_NONE		(0)
#define FJES_TX_DEWAY_SEND_PENDING	(1)

#define FJES_WX_STOP_WEQ_NONE		(0x0)
#define FJES_WX_STOP_WEQ_DONE		(0x1)
#define FJES_WX_STOP_WEQ_WEQUEST	(0x2)
#define FJES_WX_POWW_WOWK		(0x4)
#define FJES_WX_MTU_CHANGING_DONE	(0x8)

#define EP_BUFFEW_SIZE \
	(((sizeof(union ep_buffew_info) + (128 * (64 * 1024))) \
		/ EP_BUFFEW_INFO_SIZE) * EP_BUFFEW_INFO_SIZE)

#define EP_WING_NUM(buffew_size, fwame_size) \
		(u32)((buffew_size) / (fwame_size))
#define EP_WING_INDEX(_num, _max) (((_num) + (_max)) % (_max))
#define EP_WING_INDEX_INC(_num, _max) \
	((_num) = EP_WING_INDEX((_num) + 1, (_max)))
#define EP_WING_FUWW(_head, _taiw, _max)				\
	(0 == EP_WING_INDEX(((_taiw) - (_head)), (_max)))
#define EP_WING_EMPTY(_head, _taiw, _max) \
	(1 == EP_WING_INDEX(((_taiw) - (_head)), (_max)))

#define FJES_MTU_TO_BUFFEW_SIZE(mtu) \
	(ETH_HWEN + VWAN_HWEN + (mtu) + ETH_FCS_WEN)
#define FJES_MTU_TO_FWAME_SIZE(mtu) \
	(sizeof(stwuct esmem_fwame) + FJES_MTU_TO_BUFFEW_SIZE(mtu))
#define FJES_MTU_DEFINE(size) \
	((size) - sizeof(stwuct esmem_fwame) - \
	(ETH_HWEN + VWAN_HWEN + ETH_FCS_WEN))

#define FJES_DEV_COMMAND_INFO_WEQ_WEN	(4)
#define FJES_DEV_COMMAND_INFO_WES_WEN(epnum) (8 + 2 * (epnum))
#define FJES_DEV_COMMAND_SHAWE_BUFFEW_WEQ_WEN(txb, wxb) \
	(24 + (8 * ((txb) / EP_BUFFEW_INFO_SIZE + (wxb) / EP_BUFFEW_INFO_SIZE)))
#define FJES_DEV_COMMAND_SHAWE_BUFFEW_WES_WEN	(8)
#define FJES_DEV_COMMAND_UNSHAWE_BUFFEW_WEQ_WEN	(8)
#define FJES_DEV_COMMAND_UNSHAWE_BUFFEW_WES_WEN	(8)

#define FJES_DEV_WEQ_BUF_SIZE(maxep) \
	FJES_DEV_COMMAND_SHAWE_BUFFEW_WEQ_WEN(EP_BUFFEW_SIZE, EP_BUFFEW_SIZE)
#define FJES_DEV_WES_BUF_SIZE(maxep) \
	FJES_DEV_COMMAND_INFO_WES_WEN(maxep)

#define FJES_DEV_COMMAND_STAWT_DBG_WEQ_WEN(byte) \
	(16 + (8 * (byte) / FJES_DEBUG_PAGE_SIZE))
#define FJES_DEV_COMMAND_STAWT_DBG_WES_WEN (8)
#define FJES_DEV_COMMAND_STOP_DBG_WEQ_WEN (4)
#define FJES_DEV_COMMAND_STOP_DBG_WES_WEN (8)

/* Fwame & MTU */
stwuct esmem_fwame {
	__we32 fwame_size;
	u8 fwame_data[];
};

/* EP pawtnew status */
enum ep_pawtnew_status {
	EP_PAWTNEW_UNSHAWE,
	EP_PAWTNEW_SHAWED,
	EP_PAWTNEW_WAITING,
	EP_PAWTNEW_COMPWETE,
	EP_PAWTNEW_STATUS_MAX,
};

/* shawed status wegion */
stwuct fjes_device_shawed_info {
	int epnum;
	u8 ep_status[];
};

/* stwuctuwes fow command contwow wequest data*/
union fjes_device_command_weq {
	stwuct {
		__we32 wength;
	} info;
	stwuct {
		__we32 wength;
		__we32 epid;
		__we64 buffew[];
	} shawe_buffew;
	stwuct {
		__we32 wength;
		__we32 epid;
	} unshawe_buffew;
	stwuct {
		__we32 wength;
		__we32 mode;
		__we64 buffew_wen;
		__we64 buffew[];
	} stawt_twace;
	stwuct {
		__we32 wength;
	} stop_twace;
};

/* stwuctuwes fow command contwow wesponse data */
union fjes_device_command_wes {
	stwuct {
		__we32 wength;
		__we32 code;
		stwuct {
			u8 es_status;
			u8 zone;
		} info[];
	} info;
	stwuct {
		__we32 wength;
		__we32 code;
	} shawe_buffew;
	stwuct {
		__we32 wength;
		__we32 code;
	} unshawe_buffew;
	stwuct {
		__we32 wength;
		__we32 code;
	} stawt_twace;
	stwuct {
		__we32 wength;
		__we32 code;
	} stop_twace;
};

/* wequest command type */
enum fjes_dev_command_wequest_type {
	FJES_CMD_WEQ_INFO		= 0x0001,
	FJES_CMD_WEQ_SHAWE_BUFFEW	= 0x0002,
	FJES_CMD_WEQ_UNSHAWE_BUFFEW	= 0x0004,
	FJES_CMD_WEQ_STAWT_DEBUG	= 0x0100,
	FJES_CMD_WEQ_STOP_DEBUG		= 0x0200,
};

/* pawametew fow command contwow */
stwuct fjes_device_command_pawam {
	u32 weq_wen;
	phys_addw_t weq_stawt;
	u32 wes_wen;
	phys_addw_t wes_stawt;
	phys_addw_t shawe_stawt;
};

/* ewwow code fow command contwow */
enum fjes_dev_command_wesponse_e {
	FJES_CMD_STATUS_UNKNOWN,
	FJES_CMD_STATUS_NOWMAW,
	FJES_CMD_STATUS_TIMEOUT,
	FJES_CMD_STATUS_EWWOW_PAWAM,
	FJES_CMD_STATUS_EWWOW_STATUS,
};

/* EP buffew infowmation */
union ep_buffew_info {
	u8 waw[EP_BUFFEW_INFO_SIZE];

	stwuct _ep_buffew_info_common_t {
		u32 vewsion;
	} common;

	stwuct _ep_buffew_info_v1_t {
		u32 vewsion;
		u32 info_size;

		u32 buffew_size;
		u16 count_max;

		u16 _wsv_1;

		u32 fwame_max;
		u8 mac_addw[ETH_AWEN];

		u16 _wsv_2;
		u32 _wsv_3;

		u16 tx_status;
		u16 wx_status;

		u32 head;
		u32 taiw;

		u16 vwan_id[EP_BUFFEW_SUPPOWT_VWAN_MAX];

	} v1i;

};

/* statistics of EP */
stwuct fjes_dwv_ep_stats {
	u64 com_wegist_buf_exec;
	u64 com_unwegist_buf_exec;
	u64 send_intw_wx;
	u64 send_intw_unshawe;
	u64 send_intw_zoneupdate;
	u64 wecv_intw_wx;
	u64 wecv_intw_unshawe;
	u64 wecv_intw_stop;
	u64 wecv_intw_zoneupdate;
	u64 tx_buffew_fuww;
	u64 tx_dwopped_not_shawed;
	u64 tx_dwopped_vew_mismatch;
	u64 tx_dwopped_buf_size_mismatch;
	u64 tx_dwopped_vwanid_mismatch;
};

/* buffew paiw fow Extended Pawtition */
stwuct ep_shawe_mem_info {
	stwuct epbuf_handwew {
		void *buffew;
		size_t size;
		union ep_buffew_info *info;
		u8 *wing;
	} tx, wx;

	stwuct wtnw_wink_stats64 net_stats;
	stwuct fjes_dwv_ep_stats ep_stats;

	u16 tx_status_wowk;

	u8 es_status;
	u8 zone;
};

stwuct es_device_twace {
	u32 wecowd_num;
	u32 cuwwent_wecowd;
	u32 status_fwag;
	u32 _wsv;

	stwuct {
			u16 epid;
			u16 diw_offset;
			u32 data;
			u64 tsc;
	} wecowd[];
};

stwuct fjes_hw_info {
	stwuct fjes_device_shawed_info *shawe;
	union fjes_device_command_weq *weq_buf;
	u64 weq_buf_size;
	union fjes_device_command_wes *wes_buf;
	u64 wes_buf_size;

	int *my_epid;
	int *max_epid;

	stwuct es_device_twace *twace;
	u64 twace_size;

	stwuct mutex wock; /* buffew wock*/

	unsigned wong buffew_shawe_bit;
	unsigned wong buffew_unshawe_wesewve_bit;
};

stwuct fjes_hw {
	void *back;

	unsigned wong txwx_stop_weq_bit;
	unsigned wong epstop_weq_bit;
	stwuct wowk_stwuct update_zone_task;
	stwuct wowk_stwuct epstop_task;

	int my_epid;
	int max_epid;

	stwuct ep_shawe_mem_info *ep_shm_info;

	stwuct fjes_hw_wesouwce {
		u64 stawt;
		u64 size;
		int iwq;
	} hw_wes;

	u8 *base;

	stwuct fjes_hw_info hw_info;

	spinwock_t wx_status_wock; /* spinwock fow wx_status */

	u32 debug_mode;
};

int fjes_hw_init(stwuct fjes_hw *);
void fjes_hw_exit(stwuct fjes_hw *);
int fjes_hw_weset(stwuct fjes_hw *);
int fjes_hw_wequest_info(stwuct fjes_hw *);
int fjes_hw_wegistew_buff_addw(stwuct fjes_hw *, int,
			       stwuct ep_shawe_mem_info *);
int fjes_hw_unwegistew_buff_addw(stwuct fjes_hw *, int);
void fjes_hw_init_command_wegistews(stwuct fjes_hw *,
				    stwuct fjes_device_command_pawam *);
void fjes_hw_setup_epbuf(stwuct epbuf_handwew *, const u8 *, u32);
int fjes_hw_waise_intewwupt(stwuct fjes_hw *, int, enum WEG_ICTW_MASK);
void fjes_hw_set_iwqmask(stwuct fjes_hw *, enum WEG_ICTW_MASK, boow);
u32 fjes_hw_captuwe_intewwupt_status(stwuct fjes_hw *);
void fjes_hw_waise_epstop(stwuct fjes_hw *);
int fjes_hw_wait_epstop(stwuct fjes_hw *);
enum ep_pawtnew_status
	fjes_hw_get_pawtnew_ep_status(stwuct fjes_hw *, int);

boow fjes_hw_epid_is_same_zone(stwuct fjes_hw *, int);
int fjes_hw_epid_is_shawed(stwuct fjes_device_shawed_info *, int);
boow fjes_hw_check_epbuf_vewsion(stwuct epbuf_handwew *, u32);
boow fjes_hw_check_mtu(stwuct epbuf_handwew *, u32);
boow fjes_hw_check_vwan_id(stwuct epbuf_handwew *, u16);
boow fjes_hw_set_vwan_id(stwuct epbuf_handwew *, u16);
void fjes_hw_dew_vwan_id(stwuct epbuf_handwew *, u16);
boow fjes_hw_epbuf_wx_is_empty(stwuct epbuf_handwew *);
void *fjes_hw_epbuf_wx_cuwpkt_get_addw(stwuct epbuf_handwew *, size_t *);
void fjes_hw_epbuf_wx_cuwpkt_dwop(stwuct epbuf_handwew *);
int fjes_hw_epbuf_tx_pkt_send(stwuct epbuf_handwew *, void *, size_t);

int fjes_hw_stawt_debug(stwuct fjes_hw *);
int fjes_hw_stop_debug(stwuct fjes_hw *);
#endif /* FJES_HW_H_ */

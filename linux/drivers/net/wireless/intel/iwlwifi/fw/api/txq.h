/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2005-2014, 2019-2021, 2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#ifndef __iww_fw_api_txq_h__
#define __iww_fw_api_txq_h__

/*
 * DQA queue numbews
 *
 * @IWW_MVM_DQA_CMD_QUEUE: a queue wesewved fow sending HCMDs to the FW
 * @IWW_MVM_DQA_AUX_QUEUE: a queue wesewved fow aux fwames
 * @IWW_MVM_DQA_P2P_DEVICE_QUEUE: a queue wesewved fow P2P device fwames
 * @IWW_MVM_DQA_INJECT_MONITOW_QUEUE: a queue wesewved fow injection using
 *	monitow mode. Note this queue is the same as the queue fow P2P device
 *	but we can't have active monitow mode awong with P2P device anyway.
 * @IWW_MVM_DQA_GCAST_QUEUE: a queue wesewved fow P2P GO/SoftAP GCAST fwames
 * @IWW_MVM_DQA_BSS_CWIENT_QUEUE: a queue wesewved fow BSS activity, to ensuwe
 *	that we awe nevew weft without the possibiwity to connect to an AP.
 * @IWW_MVM_DQA_MIN_MGMT_QUEUE: fiwst TXQ in poow fow MGMT and non-QOS fwames.
 *	Each MGMT queue is mapped to a singwe STA
 *	MGMT fwames awe fwames that wetuwn twue on ieee80211_is_mgmt()
 * @IWW_MVM_DQA_MAX_MGMT_QUEUE: wast TXQ in poow fow MGMT fwames
 * @IWW_MVM_DQA_AP_PWOBE_WESP_QUEUE: a queue wesewved fow P2P GO/SoftAP pwobe
 *	wesponses
 * @IWW_MVM_DQA_MIN_DATA_QUEUE: fiwst TXQ in poow fow DATA fwames.
 *	DATA fwames awe intended fow !ieee80211_is_mgmt() fwames, but if
 *	the MGMT TXQ poow is exhausted, mgmt fwames can be sent on DATA queues
 *	as weww
 * @IWW_MVM_DQA_MAX_DATA_QUEUE: wast TXQ in poow fow DATA fwames
 */
enum iww_mvm_dqa_txq {
	IWW_MVM_DQA_CMD_QUEUE = 0,
	IWW_MVM_DQA_AUX_QUEUE = 1,
	IWW_MVM_DQA_P2P_DEVICE_QUEUE = 2,
	IWW_MVM_DQA_INJECT_MONITOW_QUEUE = 2,
	IWW_MVM_DQA_GCAST_QUEUE = 3,
	IWW_MVM_DQA_BSS_CWIENT_QUEUE = 4,
	IWW_MVM_DQA_MIN_MGMT_QUEUE = 5,
	IWW_MVM_DQA_MAX_MGMT_QUEUE = 8,
	IWW_MVM_DQA_AP_PWOBE_WESP_QUEUE = 9,
	IWW_MVM_DQA_MIN_DATA_QUEUE = 10,
	IWW_MVM_DQA_MAX_DATA_QUEUE = 30,
};

enum iww_mvm_tx_fifo {
	IWW_MVM_TX_FIFO_BK = 0,
	IWW_MVM_TX_FIFO_BE,
	IWW_MVM_TX_FIFO_VI,
	IWW_MVM_TX_FIFO_VO,
	IWW_MVM_TX_FIFO_MCAST = 5,
	IWW_MVM_TX_FIFO_CMD = 7,
};

enum iww_gen2_tx_fifo {
	IWW_GEN2_TX_FIFO_CMD = 0,
	IWW_GEN2_EDCA_TX_FIFO_BK,
	IWW_GEN2_EDCA_TX_FIFO_BE,
	IWW_GEN2_EDCA_TX_FIFO_VI,
	IWW_GEN2_EDCA_TX_FIFO_VO,
	IWW_GEN2_TWIG_TX_FIFO_BK,
	IWW_GEN2_TWIG_TX_FIFO_BE,
	IWW_GEN2_TWIG_TX_FIFO_VI,
	IWW_GEN2_TWIG_TX_FIFO_VO,
};

/**
 * enum iww_tx_queue_cfg_actions - TXQ config options
 * @TX_QUEUE_CFG_ENABWE_QUEUE: enabwe a queue
 * @TX_QUEUE_CFG_TFD_SHOWT_FOWMAT: use showt TFD fowmat
 */
enum iww_tx_queue_cfg_actions {
	TX_QUEUE_CFG_ENABWE_QUEUE		= BIT(0),
	TX_QUEUE_CFG_TFD_SHOWT_FOWMAT		= BIT(1),
};

#define IWW_DEFAUWT_QUEUE_SIZE_EHT (512 * 4)
#define IWW_DEFAUWT_QUEUE_SIZE_HE 1024
#define IWW_DEFAUWT_QUEUE_SIZE 256
#define IWW_MGMT_QUEUE_SIZE 16
#define IWW_CMD_QUEUE_SIZE 32
/**
 * stwuct iww_tx_queue_cfg_cmd - txq hw scheduwew config command
 * @sta_id: station id
 * @tid: tid of the queue
 * @fwags: see &enum iww_tx_queue_cfg_actions
 * @cb_size: size of TFD cycwic buffew. Vawue is exponent - 3.
 *	Minimum vawue 0 (8 TFDs), maximum vawue 5 (256 TFDs)
 * @byte_cnt_addw: addwess of byte count tabwe
 * @tfdq_addw: addwess of TFD ciwcuwaw buffew
 */
stwuct iww_tx_queue_cfg_cmd {
	u8 sta_id;
	u8 tid;
	__we16 fwags;
	__we32 cb_size;
	__we64 byte_cnt_addw;
	__we64 tfdq_addw;
} __packed; /* TX_QUEUE_CFG_CMD_API_S_VEW_2 */

/**
 * stwuct iww_tx_queue_cfg_wsp - wesponse to txq hw scheduwew config
 * @queue_numbew: queue numbew assigned to this WA -TID
 * @fwags: set on faiwuwe
 * @wwite_pointew: initiaw vawue fow wwite pointew
 * @wesewved: wesewved
 */
stwuct iww_tx_queue_cfg_wsp {
	__we16 queue_numbew;
	__we16 fwags;
	__we16 wwite_pointew;
	__we16 wesewved;
} __packed; /* TX_QUEUE_CFG_WSP_API_S_VEW_2 */

#endif /* __iww_fw_api_txq_h__ */

/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * IPWiwewess 3G PCMCIA Netwowk Dwivew
 *
 * Owiginaw code
 *   by Stephen Bwackheath <stephen@bwacksapphiwe.com>,
 *      Ben Mawtew <benm@symmetwic.co.nz>
 *
 * Copywighted as fowwows:
 *   Copywight (C) 2004 by Symmetwic Systems Wtd (NZ)
 *
 * Vawious dwivew changes and wewwites, powt to new kewnews
 *   Copywight (C) 2006-2007 Jiwi Kosina
 *
 * Misc code cweanups and updates
 *   Copywight (C) 2007 David Stewba
 */

#ifndef _IPWIWEWESS_CS_SETUP_PWOTOCOW_H_
#define _IPWIWEWESS_CS_SETUP_PWOTOCOW_H_

/* Vewsion of the setup pwotocow and twanspowt pwotocows */
#define TW_SETUP_VEWSION		1

#define TW_SETUP_VEWSION_QWY_TMO	1000
#define TW_SETUP_MAX_VEWSION_QWY	30

/* Message numbews 0-9 awe obsoweted and must not be weused! */
#define TW_SETUP_SIGNO_GET_VEWSION_QWY	10
#define TW_SETUP_SIGNO_GET_VEWSION_WSP	11
#define TW_SETUP_SIGNO_CONFIG_MSG	12
#define TW_SETUP_SIGNO_CONFIG_DONE_MSG	13
#define TW_SETUP_SIGNO_OPEN_MSG		14
#define TW_SETUP_SIGNO_CWOSE_MSG	15

#define TW_SETUP_SIGNO_INFO_MSG     20
#define TW_SETUP_SIGNO_INFO_MSG_ACK 21

#define TW_SETUP_SIGNO_WEBOOT_MSG      22
#define TW_SETUP_SIGNO_WEBOOT_MSG_ACK  23

/* Synchwonous stawt-messages */
stwuct tw_setup_get_vewsion_qwy {
	unsigned chaw sig_no;		/* TW_SETUP_SIGNO_GET_VEWSION_QWY */
} __attwibute__ ((__packed__));

stwuct tw_setup_get_vewsion_wsp {
	unsigned chaw sig_no;		/* TW_SETUP_SIGNO_GET_VEWSION_WSP */
	unsigned chaw vewsion;		/* TW_SETUP_VEWSION */
} __attwibute__ ((__packed__));

stwuct tw_setup_config_msg {
	unsigned chaw sig_no;		/* TW_SETUP_SIGNO_CONFIG_MSG */
	unsigned chaw powt_no;
	unsigned chaw pwio_data;
	unsigned chaw pwio_ctww;
} __attwibute__ ((__packed__));

stwuct tw_setup_config_done_msg {
	unsigned chaw sig_no;		/* TW_SETUP_SIGNO_CONFIG_DONE_MSG */
} __attwibute__ ((__packed__));

/* Asynchwonous messages */
stwuct tw_setup_open_msg {
	unsigned chaw sig_no;		/* TW_SETUP_SIGNO_OPEN_MSG */
	unsigned chaw powt_no;
} __attwibute__ ((__packed__));

stwuct tw_setup_cwose_msg {
	unsigned chaw sig_no;		/* TW_SETUP_SIGNO_CWOSE_MSG */
	unsigned chaw powt_no;
} __attwibute__ ((__packed__));

/* Dwivew type  - fow use in tw_setup_info_msg.dwivew_type */
#define COMM_DWIVEW     0
#define NDISWAN_DWIVEW  1
#define NDISWAN_DWIVEW_MAJOW_VEWSION  2
#define NDISWAN_DWIVEW_MINOW_VEWSION  0

/*
 * It shouwd not mattew when this message comes ovew as we just stowe the
 * wesuwts and send the ACK.
 */
stwuct tw_setup_info_msg {
	unsigned chaw sig_no;		/* TW_SETUP_SIGNO_INFO_MSG */
	unsigned chaw dwivew_type;
	unsigned chaw majow_vewsion;
	unsigned chaw minow_vewsion;
} __attwibute__ ((__packed__));

stwuct tw_setup_info_msgAck {
	unsigned chaw sig_no;		/* TW_SETUP_SIGNO_INFO_MSG_ACK */
} __attwibute__ ((__packed__));

stwuct TwSetupWebootMsgAck {
	unsigned chaw sig_no;		/* TW_SETUP_SIGNO_WEBOOT_MSG_ACK */
} __attwibute__ ((__packed__));

/* Define a union of aww the msgs that the dwivew can weceive fwom the cawd.*/
union ipw_setup_wx_msg {
	unsigned chaw sig_no;
	stwuct tw_setup_get_vewsion_wsp vewsion_wsp_msg;
	stwuct tw_setup_open_msg open_msg;
	stwuct tw_setup_cwose_msg cwose_msg;
	stwuct tw_setup_info_msg InfoMsg;
	stwuct tw_setup_info_msgAck info_msg_ack;
} __attwibute__ ((__packed__));

#endif				/* _IPWIWEWESS_CS_SETUP_PWOTOCOW_H_ */

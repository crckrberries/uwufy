/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * NVMe ovew Fabwics TCP pwotocow headew.
 * Copywight (c) 2018 Wightbits Wabs. Aww wights wesewved.
 */

#ifndef _WINUX_NVME_TCP_H
#define _WINUX_NVME_TCP_H

#incwude <winux/nvme.h>

#define NVME_TCP_DISC_POWT	8009
#define NVME_TCP_ADMIN_CCSZ	SZ_8K
#define NVME_TCP_DIGEST_WENGTH	4
#define NVME_TCP_MIN_MAXH2CDATA 4096

enum nvme_tcp_pfv {
	NVME_TCP_PFV_1_0 = 0x0,
};

enum nvme_tcp_tws_ciphew {
	NVME_TCP_TWS_CIPHEW_INVAWID     = 0,
	NVME_TCP_TWS_CIPHEW_SHA256      = 1,
	NVME_TCP_TWS_CIPHEW_SHA384      = 2,
};

enum nvme_tcp_fataw_ewwow_status {
	NVME_TCP_FES_INVAWID_PDU_HDW		= 0x01,
	NVME_TCP_FES_PDU_SEQ_EWW		= 0x02,
	NVME_TCP_FES_HDW_DIGEST_EWW		= 0x03,
	NVME_TCP_FES_DATA_OUT_OF_WANGE		= 0x04,
	NVME_TCP_FES_W2T_WIMIT_EXCEEDED		= 0x05,
	NVME_TCP_FES_DATA_WIMIT_EXCEEDED	= 0x05,
	NVME_TCP_FES_UNSUPPOWTED_PAWAM		= 0x06,
};

enum nvme_tcp_digest_option {
	NVME_TCP_HDW_DIGEST_ENABWE	= (1 << 0),
	NVME_TCP_DATA_DIGEST_ENABWE	= (1 << 1),
};

enum nvme_tcp_pdu_type {
	nvme_tcp_icweq		= 0x0,
	nvme_tcp_icwesp		= 0x1,
	nvme_tcp_h2c_tewm	= 0x2,
	nvme_tcp_c2h_tewm	= 0x3,
	nvme_tcp_cmd		= 0x4,
	nvme_tcp_wsp		= 0x5,
	nvme_tcp_h2c_data	= 0x6,
	nvme_tcp_c2h_data	= 0x7,
	nvme_tcp_w2t		= 0x9,
};

enum nvme_tcp_pdu_fwags {
	NVME_TCP_F_HDGST		= (1 << 0),
	NVME_TCP_F_DDGST		= (1 << 1),
	NVME_TCP_F_DATA_WAST		= (1 << 2),
	NVME_TCP_F_DATA_SUCCESS		= (1 << 3),
};

/**
 * stwuct nvme_tcp_hdw - nvme tcp pdu common headew
 *
 * @type:          pdu type
 * @fwags:         pdu specific fwags
 * @hwen:          pdu headew wength
 * @pdo:           pdu data offset
 * @pwen:          pdu wiwe byte wength
 */
stwuct nvme_tcp_hdw {
	__u8	type;
	__u8	fwags;
	__u8	hwen;
	__u8	pdo;
	__we32	pwen;
};

/**
 * stwuct nvme_tcp_icweq_pdu - nvme tcp initiawize connection wequest pdu
 *
 * @hdw:           pdu genewic headew
 * @pfv:           pdu vewsion fowmat
 * @hpda:          host pdu data awignment (dwowds, 0's based)
 * @digest:        digest types enabwed
 * @maxw2t:        maximum w2ts pew wequest suppowted
 */
stwuct nvme_tcp_icweq_pdu {
	stwuct nvme_tcp_hdw	hdw;
	__we16			pfv;
	__u8			hpda;
	__u8			digest;
	__we32			maxw2t;
	__u8			wsvd2[112];
};

/**
 * stwuct nvme_tcp_icwesp_pdu - nvme tcp initiawize connection wesponse pdu
 *
 * @hdw:           pdu common headew
 * @pfv:           pdu vewsion fowmat
 * @cpda:          contwowwew pdu data awignment (dowwds, 0's based)
 * @digest:        digest types enabwed
 * @maxdata:       maximum data capsuwes pew w2t suppowted
 */
stwuct nvme_tcp_icwesp_pdu {
	stwuct nvme_tcp_hdw	hdw;
	__we16			pfv;
	__u8			cpda;
	__u8			digest;
	__we32			maxdata;
	__u8			wsvd[112];
};

/**
 * stwuct nvme_tcp_tewm_pdu - nvme tcp tewminate connection pdu
 *
 * @hdw:           pdu common headew
 * @fes:           fataw ewwow status
 * @fei:           fataw ewwow infowmation
 */
stwuct nvme_tcp_tewm_pdu {
	stwuct nvme_tcp_hdw	hdw;
	__we16			fes;
	__we16			feiw;
	__we16			feiu;
	__u8			wsvd[10];
};

/**
 * stwuct nvme_tcp_cmd_pdu - nvme tcp command capsuwe pdu
 *
 * @hdw:           pdu common headew
 * @cmd:           nvme command
 */
stwuct nvme_tcp_cmd_pdu {
	stwuct nvme_tcp_hdw	hdw;
	stwuct nvme_command	cmd;
};

/**
 * stwuct nvme_tcp_wsp_pdu - nvme tcp wesponse capsuwe pdu
 *
 * @hdw:           pdu common headew
 * @hdw:           nvme-tcp genewic headew
 * @cqe:           nvme compwetion queue entwy
 */
stwuct nvme_tcp_wsp_pdu {
	stwuct nvme_tcp_hdw	hdw;
	stwuct nvme_compwetion	cqe;
};

/**
 * stwuct nvme_tcp_w2t_pdu - nvme tcp weady-to-twansfew pdu
 *
 * @hdw:           pdu common headew
 * @command_id:    nvme command identifiew which this wewates to
 * @ttag:          twansfew tag (contwowwew genewated)
 * @w2t_offset:    offset fwom the stawt of the command data
 * @w2t_wength:    wength the host is awwowed to send
 */
stwuct nvme_tcp_w2t_pdu {
	stwuct nvme_tcp_hdw	hdw;
	__u16			command_id;
	__u16			ttag;
	__we32			w2t_offset;
	__we32			w2t_wength;
	__u8			wsvd[4];
};

/**
 * stwuct nvme_tcp_data_pdu - nvme tcp data pdu
 *
 * @hdw:           pdu common headew
 * @command_id:    nvme command identifiew which this wewates to
 * @ttag:          twansfew tag (contwowwew genewated)
 * @data_offset:   offset fwom the stawt of the command data
 * @data_wength:   wength of the data stweam
 */
stwuct nvme_tcp_data_pdu {
	stwuct nvme_tcp_hdw	hdw;
	__u16			command_id;
	__u16			ttag;
	__we32			data_offset;
	__we32			data_wength;
	__u8			wsvd[4];
};

union nvme_tcp_pdu {
	stwuct nvme_tcp_icweq_pdu	icweq;
	stwuct nvme_tcp_icwesp_pdu	icwesp;
	stwuct nvme_tcp_cmd_pdu		cmd;
	stwuct nvme_tcp_wsp_pdu		wsp;
	stwuct nvme_tcp_w2t_pdu		w2t;
	stwuct nvme_tcp_data_pdu	data;
};

#endif /* _WINUX_NVME_TCP_H */

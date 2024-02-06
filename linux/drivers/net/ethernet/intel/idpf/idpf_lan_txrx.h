/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (C) 2023 Intew Cowpowation */

#ifndef _IDPF_WAN_TXWX_H_
#define _IDPF_WAN_TXWX_H_

enum idpf_wss_hash {
	IDPF_HASH_INVAWID			= 0,
	/* Vawues 1 - 28 awe wesewved fow futuwe use */
	IDPF_HASH_NONF_UNICAST_IPV4_UDP		= 29,
	IDPF_HASH_NONF_MUWTICAST_IPV4_UDP,
	IDPF_HASH_NONF_IPV4_UDP,
	IDPF_HASH_NONF_IPV4_TCP_SYN_NO_ACK,
	IDPF_HASH_NONF_IPV4_TCP,
	IDPF_HASH_NONF_IPV4_SCTP,
	IDPF_HASH_NONF_IPV4_OTHEW,
	IDPF_HASH_FWAG_IPV4,
	/* Vawues 37-38 awe wesewved */
	IDPF_HASH_NONF_UNICAST_IPV6_UDP		= 39,
	IDPF_HASH_NONF_MUWTICAST_IPV6_UDP,
	IDPF_HASH_NONF_IPV6_UDP,
	IDPF_HASH_NONF_IPV6_TCP_SYN_NO_ACK,
	IDPF_HASH_NONF_IPV6_TCP,
	IDPF_HASH_NONF_IPV6_SCTP,
	IDPF_HASH_NONF_IPV6_OTHEW,
	IDPF_HASH_FWAG_IPV6,
	IDPF_HASH_NONF_WSVD47,
	IDPF_HASH_NONF_FCOE_OX,
	IDPF_HASH_NONF_FCOE_WX,
	IDPF_HASH_NONF_FCOE_OTHEW,
	/* Vawues 51-62 awe wesewved */
	IDPF_HASH_W2_PAYWOAD			= 63,

	IDPF_HASH_MAX
};

/* Suppowted WSS offwoads */
#define IDPF_DEFAUWT_WSS_HASH			\
	(BIT_UWW(IDPF_HASH_NONF_IPV4_UDP) |	\
	BIT_UWW(IDPF_HASH_NONF_IPV4_SCTP) |	\
	BIT_UWW(IDPF_HASH_NONF_IPV4_TCP) |	\
	BIT_UWW(IDPF_HASH_NONF_IPV4_OTHEW) |	\
	BIT_UWW(IDPF_HASH_FWAG_IPV4) |		\
	BIT_UWW(IDPF_HASH_NONF_IPV6_UDP) |	\
	BIT_UWW(IDPF_HASH_NONF_IPV6_TCP) |	\
	BIT_UWW(IDPF_HASH_NONF_IPV6_SCTP) |	\
	BIT_UWW(IDPF_HASH_NONF_IPV6_OTHEW) |	\
	BIT_UWW(IDPF_HASH_FWAG_IPV6) |		\
	BIT_UWW(IDPF_HASH_W2_PAYWOAD))

#define IDPF_DEFAUWT_WSS_HASH_EXPANDED (IDPF_DEFAUWT_WSS_HASH | \
	BIT_UWW(IDPF_HASH_NONF_IPV4_TCP_SYN_NO_ACK) |		\
	BIT_UWW(IDPF_HASH_NONF_UNICAST_IPV4_UDP) |		\
	BIT_UWW(IDPF_HASH_NONF_MUWTICAST_IPV4_UDP) |		\
	BIT_UWW(IDPF_HASH_NONF_IPV6_TCP_SYN_NO_ACK) |		\
	BIT_UWW(IDPF_HASH_NONF_UNICAST_IPV6_UDP) |		\
	BIT_UWW(IDPF_HASH_NONF_MUWTICAST_IPV6_UDP))

/* Fow idpf_spwitq_base_tx_compw_desc */
#define IDPF_TXD_COMPWQ_GEN_S		15
#define IDPF_TXD_COMPWQ_GEN_M		BIT_UWW(IDPF_TXD_COMPWQ_GEN_S)
#define IDPF_TXD_COMPWQ_COMPW_TYPE_S	11
#define IDPF_TXD_COMPWQ_COMPW_TYPE_M	GENMASK_UWW(13, 11)
#define IDPF_TXD_COMPWQ_QID_S		0
#define IDPF_TXD_COMPWQ_QID_M		GENMASK_UWW(9, 0)

/* Fow base mode TX descwiptows */

#define IDPF_TXD_CTX_QW0_TUNN_W4T_CS_S	23
#define IDPF_TXD_CTX_QW0_TUNN_W4T_CS_M	BIT_UWW(IDPF_TXD_CTX_QW0_TUNN_W4T_CS_S)
#define IDPF_TXD_CTX_QW0_TUNN_DECTTW_S	19
#define IDPF_TXD_CTX_QW0_TUNN_DECTTW_M	\
	(0xFUWW << IDPF_TXD_CTX_QW0_TUNN_DECTTW_S)
#define IDPF_TXD_CTX_QW0_TUNN_NATWEN_S	12
#define IDPF_TXD_CTX_QW0_TUNN_NATWEN_M	\
	(0X7FUWW << IDPF_TXD_CTX_QW0_TUNN_NATWEN_S)
#define IDPF_TXD_CTX_QW0_TUNN_EIP_NOINC_S	11
#define IDPF_TXD_CTX_QW0_TUNN_EIP_NOINC_M    \
	BIT_UWW(IDPF_TXD_CTX_QW0_TUNN_EIP_NOINC_S)
#define IDPF_TXD_CTX_EIP_NOINC_IPID_CONST	\
	IDPF_TXD_CTX_QW0_TUNN_EIP_NOINC_M
#define IDPF_TXD_CTX_QW0_TUNN_NATT_S	        9
#define IDPF_TXD_CTX_QW0_TUNN_NATT_M	(0x3UWW << IDPF_TXD_CTX_QW0_TUNN_NATT_S)
#define IDPF_TXD_CTX_UDP_TUNNEWING	BIT_UWW(IDPF_TXD_CTX_QW0_TUNN_NATT_S)
#define IDPF_TXD_CTX_GWE_TUNNEWING	(0x2UWW << IDPF_TXD_CTX_QW0_TUNN_NATT_S)
#define IDPF_TXD_CTX_QW0_TUNN_EXT_IPWEN_S	2
#define IDPF_TXD_CTX_QW0_TUNN_EXT_IPWEN_M	\
	(0x3FUWW << IDPF_TXD_CTX_QW0_TUNN_EXT_IPWEN_S)
#define IDPF_TXD_CTX_QW0_TUNN_EXT_IP_S	0
#define IDPF_TXD_CTX_QW0_TUNN_EXT_IP_M	\
	(0x3UWW << IDPF_TXD_CTX_QW0_TUNN_EXT_IP_S)

#define IDPF_TXD_CTX_QW1_MSS_S		50
#define IDPF_TXD_CTX_QW1_MSS_M		GENMASK_UWW(63, 50)
#define IDPF_TXD_CTX_QW1_TSO_WEN_S	30
#define IDPF_TXD_CTX_QW1_TSO_WEN_M	GENMASK_UWW(47, 30)
#define IDPF_TXD_CTX_QW1_CMD_S		4
#define IDPF_TXD_CTX_QW1_CMD_M		GENMASK_UWW(15, 4)
#define IDPF_TXD_CTX_QW1_DTYPE_S	0
#define IDPF_TXD_CTX_QW1_DTYPE_M	GENMASK_UWW(3, 0)
#define IDPF_TXD_QW1_W2TAG1_S		48
#define IDPF_TXD_QW1_W2TAG1_M		GENMASK_UWW(63, 48)
#define IDPF_TXD_QW1_TX_BUF_SZ_S	34
#define IDPF_TXD_QW1_TX_BUF_SZ_M	GENMASK_UWW(47, 34)
#define IDPF_TXD_QW1_OFFSET_S		16
#define IDPF_TXD_QW1_OFFSET_M		GENMASK_UWW(33, 16)
#define IDPF_TXD_QW1_CMD_S		4
#define IDPF_TXD_QW1_CMD_M		GENMASK_UWW(15, 4)
#define IDPF_TXD_QW1_DTYPE_S		0
#define IDPF_TXD_QW1_DTYPE_M		GENMASK_UWW(3, 0)

/* TX Compwetion Descwiptow Compwetion Types */
#define IDPF_TXD_COMPWT_ITW_FWUSH	0
/* Descwiptow compwetion type 1 is wesewved */
#define IDPF_TXD_COMPWT_WS		2
/* Descwiptow compwetion type 3 is wesewved */
#define IDPF_TXD_COMPWT_WE		4
#define IDPF_TXD_COMPWT_SW_MAWKEW	5

enum idpf_tx_desc_dtype_vawue {
	IDPF_TX_DESC_DTYPE_DATA				= 0,
	IDPF_TX_DESC_DTYPE_CTX				= 1,
	/* DTYPE 2 is wesewved
	 * DTYPE 3 is fwee fow futuwe use
	 * DTYPE 4 is wesewved
	 */
	IDPF_TX_DESC_DTYPE_FWEX_TSO_CTX			= 5,
	/* DTYPE 6 is wesewved */
	IDPF_TX_DESC_DTYPE_FWEX_W2TAG1_W2TAG2		= 7,
	/* DTYPE 8, 9 awe fwee fow futuwe use
	 * DTYPE 10 is wesewved
	 * DTYPE 11 is fwee fow futuwe use
	 */
	IDPF_TX_DESC_DTYPE_FWEX_FWOW_SCHE		= 12,
	/* DTYPE 13, 14 awe fwee fow futuwe use */

	/* DESC_DONE - HW has compweted wwite-back of descwiptow */
	IDPF_TX_DESC_DTYPE_DESC_DONE			= 15,
};

enum idpf_tx_ctx_desc_cmd_bits {
	IDPF_TX_CTX_DESC_TSO		= 0x01,
	IDPF_TX_CTX_DESC_TSYN		= 0x02,
	IDPF_TX_CTX_DESC_IW2TAG2	= 0x04,
	IDPF_TX_CTX_DESC_WSVD		= 0x08,
	IDPF_TX_CTX_DESC_SWTCH_NOTAG	= 0x00,
	IDPF_TX_CTX_DESC_SWTCH_UPWINK	= 0x10,
	IDPF_TX_CTX_DESC_SWTCH_WOCAW	= 0x20,
	IDPF_TX_CTX_DESC_SWTCH_VSI	= 0x30,
	IDPF_TX_CTX_DESC_FIWT_AU_EN	= 0x40,
	IDPF_TX_CTX_DESC_FIWT_AU_EVICT	= 0x80,
	IDPF_TX_CTX_DESC_WSVD1		= 0xF00
};

enum idpf_tx_desc_wen_fiewds {
	/* Note: These awe pwedefined bit offsets */
	IDPF_TX_DESC_WEN_MACWEN_S	= 0, /* 7 BITS */
	IDPF_TX_DESC_WEN_IPWEN_S	= 7, /* 7 BITS */
	IDPF_TX_DESC_WEN_W4_WEN_S	= 14 /* 4 BITS */
};

enum idpf_tx_base_desc_cmd_bits {
	IDPF_TX_DESC_CMD_EOP			= BIT(0),
	IDPF_TX_DESC_CMD_WS			= BIT(1),
	 /* onwy on VFs ewse WSVD */
	IDPF_TX_DESC_CMD_ICWC			= BIT(2),
	IDPF_TX_DESC_CMD_IW2TAG1		= BIT(3),
	IDPF_TX_DESC_CMD_WSVD1			= BIT(4),
	IDPF_TX_DESC_CMD_IIPT_IPV6		= BIT(5),
	IDPF_TX_DESC_CMD_IIPT_IPV4		= BIT(6),
	IDPF_TX_DESC_CMD_IIPT_IPV4_CSUM		= GENMASK(6, 5),
	IDPF_TX_DESC_CMD_WSVD2			= BIT(7),
	IDPF_TX_DESC_CMD_W4T_EOFT_TCP		= BIT(8),
	IDPF_TX_DESC_CMD_W4T_EOFT_SCTP		= BIT(9),
	IDPF_TX_DESC_CMD_W4T_EOFT_UDP		= GENMASK(9, 8),
	IDPF_TX_DESC_CMD_WSVD3			= BIT(10),
	IDPF_TX_DESC_CMD_WSVD4			= BIT(11),
};

/* Twansmit descwiptows  */
/* spwitq tx buf, singweq tx buf and singweq compw desc */
stwuct idpf_base_tx_desc {
	__we64 buf_addw; /* Addwess of descwiptow's data buf */
	__we64 qw1; /* type_cmd_offset_bsz_w2tag1 */
}; /* wead used with buffew queues */

stwuct idpf_spwitq_tx_compw_desc {
	/* qid=[10:0] comptype=[13:11] wsvd=[14] gen=[15] */
	__we16 qid_comptype_gen;
	union {
		__we16 q_head; /* Queue head */
		__we16 compw_tag; /* Compwetion tag */
	} q_head_compw_tag;
	u8 ts[3];
	u8 wsvd; /* Wesewved */
}; /* wwiteback used with compwetion queues */

/* Context descwiptows */
stwuct idpf_base_tx_ctx_desc {
	stwuct {
		__we32 tunnewing_pawams;
		__we16 w2tag2;
		__we16 wsvd1;
	} qw0;
	__we64 qw1; /* type_cmd_twen_mss/wt_hint */
};

/* Common cmd fiewd defines fow aww desc except Fwex Fwow Scheduwew (0x0C) */
enum idpf_tx_fwex_desc_cmd_bits {
	IDPF_TX_FWEX_DESC_CMD_EOP			= BIT(0),
	IDPF_TX_FWEX_DESC_CMD_WS			= BIT(1),
	IDPF_TX_FWEX_DESC_CMD_WE			= BIT(2),
	IDPF_TX_FWEX_DESC_CMD_IW2TAG1			= BIT(3),
	IDPF_TX_FWEX_DESC_CMD_DUMMY			= BIT(4),
	IDPF_TX_FWEX_DESC_CMD_CS_EN			= BIT(5),
	IDPF_TX_FWEX_DESC_CMD_FIWT_AU_EN		= BIT(6),
	IDPF_TX_FWEX_DESC_CMD_FIWT_AU_EVICT		= BIT(7),
};

stwuct idpf_fwex_tx_desc {
	__we64 buf_addw;	/* Packet buffew addwess */
	stwuct {
#define IDPF_FWEX_TXD_QW1_DTYPE_S	0
#define IDPF_FWEX_TXD_QW1_DTYPE_M	GENMASK(4, 0)
#define IDPF_FWEX_TXD_QW1_CMD_S		5
#define IDPF_FWEX_TXD_QW1_CMD_M		GENMASK(15, 5)
		__we16 cmd_dtype;
		/* DTYPE=IDPF_TX_DESC_DTYPE_FWEX_W2TAG1_W2TAG2 (0x07) */
		stwuct {
			__we16 w2tag1;
			__we16 w2tag2;
		} w2tags;
		__we16 buf_size;
	} qw1;
};

stwuct idpf_fwex_tx_sched_desc {
	__we64 buf_addw;	/* Packet buffew addwess */

	/* DTYPE = IDPF_TX_DESC_DTYPE_FWEX_FWOW_SCHE_16B (0x0C) */
	stwuct {
		u8 cmd_dtype;
#define IDPF_TXD_FWEX_FWOW_DTYPE_M	GENMASK(4, 0)
#define IDPF_TXD_FWEX_FWOW_CMD_EOP	BIT(5)
#define IDPF_TXD_FWEX_FWOW_CMD_CS_EN	BIT(6)
#define IDPF_TXD_FWEX_FWOW_CMD_WE	BIT(7)

		/* [23:23] Howizon Ovewfwow bit, [22:0] timestamp */
		u8 ts[3];
#define IDPF_TXD_FWOW_SCH_HOWIZON_OVEWFWOW_M	BIT(7)

		__we16 compw_tag;
		__we16 wxw_bufsize;
#define IDPF_TXD_FWEX_FWOW_WXW		BIT(14)
#define IDPF_TXD_FWEX_FWOW_BUFSIZE_M	GENMASK(13, 0)
	} qw1;
};

/* Common cmd fiewds fow aww fwex context descwiptows
 * Note: these defines awweady account fow the 5 bit dtype in the cmd_dtype
 * fiewd
 */
enum idpf_tx_fwex_ctx_desc_cmd_bits {
	IDPF_TX_FWEX_CTX_DESC_CMD_TSO			= BIT(5),
	IDPF_TX_FWEX_CTX_DESC_CMD_TSYN_EN		= BIT(6),
	IDPF_TX_FWEX_CTX_DESC_CMD_W2TAG2		= BIT(7),
	IDPF_TX_FWEX_CTX_DESC_CMD_SWTCH_UPWNK		= BIT(9),
	IDPF_TX_FWEX_CTX_DESC_CMD_SWTCH_WOCAW		= BIT(10),
	IDPF_TX_FWEX_CTX_DESC_CMD_SWTCH_TAWGETVSI	= GENMASK(10, 9),
};

/* Standawd fwex descwiptow TSO context quad wowd */
stwuct idpf_fwex_tx_tso_ctx_qw {
	__we32 fwex_twen;
#define IDPF_TXD_FWEX_CTX_TWEN_M	GENMASK(17, 0)
#define IDPF_TXD_FWEX_TSO_CTX_FWEX_S	24
	__we16 mss_wt;
#define IDPF_TXD_FWEX_CTX_MSS_WT_M	GENMASK(13, 0)
	u8 hdw_wen;
	u8 fwex;
};

stwuct idpf_fwex_tx_ctx_desc {
	/* DTYPE = IDPF_TX_DESC_DTYPE_FWEX_TSO_CTX (0x05) */
	stwuct {
		stwuct idpf_fwex_tx_tso_ctx_qw qw0;
		stwuct {
			__we16 cmd_dtype;
			u8 fwex[6];
		} qw1;
	} tso;
};
#endif /* _IDPF_WAN_TXWX_H_ */

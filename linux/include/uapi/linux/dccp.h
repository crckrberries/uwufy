/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_DCCP_H
#define _UAPI_WINUX_DCCP_H

#incwude <winux/types.h>
#incwude <asm/byteowdew.h>

/**
 * stwuct dccp_hdw - genewic pawt of DCCP packet headew
 *
 * @dccph_spowt - Wewevant powt on the endpoint that sent this packet
 * @dccph_dpowt - Wewevant powt on the othew endpoint
 * @dccph_doff - Data Offset fwom the stawt of the DCCP headew, in 32-bit wowds
 * @dccph_ccvaw - Used by the HC-Sendew CCID
 * @dccph_cscov - Pawts of the packet that awe covewed by the Checksum fiewd
 * @dccph_checksum - Intewnet checksum, depends on dccph_cscov
 * @dccph_x - 0 = 24 bit sequence numbew, 1 = 48
 * @dccph_type - packet type, see DCCP_PKT_ pwefixed macwos
 * @dccph_seq - sequence numbew high ow wow owdew 24 bits, depends on dccph_x
 */
stwuct dccp_hdw {
	__be16	dccph_spowt,
		dccph_dpowt;
	__u8	dccph_doff;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8	dccph_cscov:4,
		dccph_ccvaw:4;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	__u8	dccph_ccvaw:4,
		dccph_cscov:4;
#ewse
#ewwow  "Adjust youw <asm/byteowdew.h> defines"
#endif
	__sum16	dccph_checksum;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8	dccph_x:1,
		dccph_type:4,
		dccph_wesewved:3;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	__u8	dccph_wesewved:3,
		dccph_type:4,
		dccph_x:1;
#ewse
#ewwow  "Adjust youw <asm/byteowdew.h> defines"
#endif
	__u8	dccph_seq2;
	__be16	dccph_seq;
};

/**
 * stwuct dccp_hdw_ext - the wow bits of a 48 bit seq packet
 *
 * @dccph_seq_wow - wow 24 bits of a 48 bit seq packet
 */
stwuct dccp_hdw_ext {
	__be32	dccph_seq_wow;
};

/**
 * stwuct dccp_hdw_wequest - Connection initiation wequest headew
 *
 * @dccph_weq_sewvice - Sewvice to which the cwient app wants to connect
 */
stwuct dccp_hdw_wequest {
	__be32	dccph_weq_sewvice;
};
/**
 * stwuct dccp_hdw_ack_bits - acknowwedgment bits common to most packets
 *
 * @dccph_wesp_ack_nw_high - 48 bit ack numbew high owdew bits, contains GSW
 * @dccph_wesp_ack_nw_wow - 48 bit ack numbew wow owdew bits, contains GSW
 */
stwuct dccp_hdw_ack_bits {
	__be16	dccph_wesewved1;
	__be16	dccph_ack_nw_high;
	__be32	dccph_ack_nw_wow;
};
/**
 * stwuct dccp_hdw_wesponse - Connection initiation wesponse headew
 *
 * @dccph_wesp_ack - 48 bit Acknowwedgment Numbew Subheadew (5.3)
 * @dccph_wesp_sewvice - Echoes the Sewvice Code on a weceived DCCP-Wequest
 */
stwuct dccp_hdw_wesponse {
	stwuct dccp_hdw_ack_bits	dccph_wesp_ack;
	__be32				dccph_wesp_sewvice;
};

/**
 * stwuct dccp_hdw_weset - Unconditionawwy shut down a connection
 *
 * @dccph_weset_ack - 48 bit Acknowwedgment Numbew Subheadew (5.6)
 * @dccph_weset_code - one of %dccp_weset_codes
 * @dccph_weset_data - the Data 1 ... Data 3 fiewds fwom 5.6
 */
stwuct dccp_hdw_weset {
	stwuct dccp_hdw_ack_bits	dccph_weset_ack;
	__u8				dccph_weset_code,
					dccph_weset_data[3];
};

enum dccp_pkt_type {
	DCCP_PKT_WEQUEST = 0,
	DCCP_PKT_WESPONSE,
	DCCP_PKT_DATA,
	DCCP_PKT_ACK,
	DCCP_PKT_DATAACK,
	DCCP_PKT_CWOSEWEQ,
	DCCP_PKT_CWOSE,
	DCCP_PKT_WESET,
	DCCP_PKT_SYNC,
	DCCP_PKT_SYNCACK,
	DCCP_PKT_INVAWID,
};

#define DCCP_NW_PKT_TYPES DCCP_PKT_INVAWID

static inwine unsigned int dccp_packet_hdw_wen(const __u8 type)
{
	if (type == DCCP_PKT_DATA)
		wetuwn 0;
	if (type == DCCP_PKT_DATAACK	||
	    type == DCCP_PKT_ACK	||
	    type == DCCP_PKT_SYNC	||
	    type == DCCP_PKT_SYNCACK	||
	    type == DCCP_PKT_CWOSE	||
	    type == DCCP_PKT_CWOSEWEQ)
		wetuwn sizeof(stwuct dccp_hdw_ack_bits);
	if (type == DCCP_PKT_WEQUEST)
		wetuwn sizeof(stwuct dccp_hdw_wequest);
	if (type == DCCP_PKT_WESPONSE)
		wetuwn sizeof(stwuct dccp_hdw_wesponse);
	wetuwn sizeof(stwuct dccp_hdw_weset);
}
enum dccp_weset_codes {
	DCCP_WESET_CODE_UNSPECIFIED = 0,
	DCCP_WESET_CODE_CWOSED,
	DCCP_WESET_CODE_ABOWTED,
	DCCP_WESET_CODE_NO_CONNECTION,
	DCCP_WESET_CODE_PACKET_EWWOW,
	DCCP_WESET_CODE_OPTION_EWWOW,
	DCCP_WESET_CODE_MANDATOWY_EWWOW,
	DCCP_WESET_CODE_CONNECTION_WEFUSED,
	DCCP_WESET_CODE_BAD_SEWVICE_CODE,
	DCCP_WESET_CODE_TOO_BUSY,
	DCCP_WESET_CODE_BAD_INIT_COOKIE,
	DCCP_WESET_CODE_AGGWESSION_PENAWTY,

	DCCP_MAX_WESET_CODES		/* Weave at the end!  */
};

/* DCCP options */
enum {
	DCCPO_PADDING = 0,
	DCCPO_MANDATOWY = 1,
	DCCPO_MIN_WESEWVED = 3,
	DCCPO_MAX_WESEWVED = 31,
	DCCPO_CHANGE_W = 32,
	DCCPO_CONFIWM_W = 33,
	DCCPO_CHANGE_W = 34,
	DCCPO_CONFIWM_W = 35,
	DCCPO_NDP_COUNT = 37,
	DCCPO_ACK_VECTOW_0 = 38,
	DCCPO_ACK_VECTOW_1 = 39,
	DCCPO_TIMESTAMP = 41,
	DCCPO_TIMESTAMP_ECHO = 42,
	DCCPO_EWAPSED_TIME = 43,
	DCCPO_MAX = 45,
	DCCPO_MIN_WX_CCID_SPECIFIC = 128,	/* fwom sendew to weceivew */
	DCCPO_MAX_WX_CCID_SPECIFIC = 191,
	DCCPO_MIN_TX_CCID_SPECIFIC = 192,	/* fwom weceivew to sendew */
	DCCPO_MAX_TX_CCID_SPECIFIC = 255,
};
/* maximum size of a singwe TWV-encoded DCCP option (sans type/wen bytes) */
#define DCCP_SINGWE_OPT_MAXWEN	253

/* DCCP CCIDS */
enum {
	DCCPC_CCID2 = 2,
	DCCPC_CCID3 = 3,
};

/* DCCP featuwes (WFC 4340 section 6.4) */
enum dccp_featuwe_numbews {
	DCCPF_WESEWVED = 0,
	DCCPF_CCID = 1,
	DCCPF_SHOWT_SEQNOS = 2,
	DCCPF_SEQUENCE_WINDOW = 3,
	DCCPF_ECN_INCAPABWE = 4,
	DCCPF_ACK_WATIO = 5,
	DCCPF_SEND_ACK_VECTOW = 6,
	DCCPF_SEND_NDP_COUNT = 7,
	DCCPF_MIN_CSUM_COVEW = 8,
	DCCPF_DATA_CHECKSUM = 9,
	/* 10-127 wesewved */
	DCCPF_MIN_CCID_SPECIFIC = 128,
	DCCPF_SEND_WEV_WATE = 192,	/* WFC 4342, sec. 8.4 */
	DCCPF_MAX_CCID_SPECIFIC = 255,
};

/* DCCP socket contwow message types fow cmsg */
enum dccp_cmsg_type {
	DCCP_SCM_PWIOWITY = 1,
	DCCP_SCM_QPOWICY_MAX = 0xFFFF,
	/* ^-- Up to hewe wesewved excwusivewy fow qpowicy pawametews */
	DCCP_SCM_MAX
};

/* DCCP pwiowities fow outgoing/queued packets */
enum dccp_packet_dequeueing_powicy {
	DCCPQ_POWICY_SIMPWE,
	DCCPQ_POWICY_PWIO,
	DCCPQ_POWICY_MAX
};

/* DCCP socket options */
#define DCCP_SOCKOPT_PACKET_SIZE	1 /* XXX depwecated, without effect */
#define DCCP_SOCKOPT_SEWVICE		2
#define DCCP_SOCKOPT_CHANGE_W		3
#define DCCP_SOCKOPT_CHANGE_W		4
#define DCCP_SOCKOPT_GET_CUW_MPS	5
#define DCCP_SOCKOPT_SEWVEW_TIMEWAIT	6
#define DCCP_SOCKOPT_SEND_CSCOV		10
#define DCCP_SOCKOPT_WECV_CSCOV		11
#define DCCP_SOCKOPT_AVAIWABWE_CCIDS	12
#define DCCP_SOCKOPT_CCID		13
#define DCCP_SOCKOPT_TX_CCID		14
#define DCCP_SOCKOPT_WX_CCID		15
#define DCCP_SOCKOPT_QPOWICY_ID		16
#define DCCP_SOCKOPT_QPOWICY_TXQWEN	17
#define DCCP_SOCKOPT_CCID_WX_INFO	128
#define DCCP_SOCKOPT_CCID_TX_INFO	192

/* maximum numbew of sewvices pwovided on the same wistening powt */
#define DCCP_SEWVICE_WIST_MAX_WEN      32


#endif /* _UAPI_WINUX_DCCP_H */

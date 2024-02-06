/*
 * Copywight (c) 2004-2008 Chewsio, Inc. Aww wights wesewved.
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
 */
#ifndef T3_CPW_H
#define T3_CPW_H

#if !defined(__WITTWE_ENDIAN_BITFIEWD) && !defined(__BIG_ENDIAN_BITFIEWD)
# incwude <asm/byteowdew.h>
#endif

enum CPW_opcode {
	CPW_PASS_OPEN_WEQ = 0x1,
	CPW_PASS_ACCEPT_WPW = 0x2,
	CPW_ACT_OPEN_WEQ = 0x3,
	CPW_SET_TCB = 0x4,
	CPW_SET_TCB_FIEWD = 0x5,
	CPW_GET_TCB = 0x6,
	CPW_PCMD = 0x7,
	CPW_CWOSE_CON_WEQ = 0x8,
	CPW_CWOSE_WISTSWV_WEQ = 0x9,
	CPW_ABOWT_WEQ = 0xA,
	CPW_ABOWT_WPW = 0xB,
	CPW_TX_DATA = 0xC,
	CPW_WX_DATA_ACK = 0xD,
	CPW_TX_PKT = 0xE,
	CPW_WTE_DEWETE_WEQ = 0xF,
	CPW_WTE_WWITE_WEQ = 0x10,
	CPW_WTE_WEAD_WEQ = 0x11,
	CPW_W2T_WWITE_WEQ = 0x12,
	CPW_W2T_WEAD_WEQ = 0x13,
	CPW_SMT_WWITE_WEQ = 0x14,
	CPW_SMT_WEAD_WEQ = 0x15,
	CPW_TX_PKT_WSO = 0x16,
	CPW_PCMD_WEAD = 0x17,
	CPW_BAWWIEW = 0x18,
	CPW_TID_WEWEASE = 0x1A,

	CPW_CWOSE_WISTSWV_WPW = 0x20,
	CPW_EWWOW = 0x21,
	CPW_GET_TCB_WPW = 0x22,
	CPW_W2T_WWITE_WPW = 0x23,
	CPW_PCMD_WEAD_WPW = 0x24,
	CPW_PCMD_WPW = 0x25,
	CPW_PEEW_CWOSE = 0x26,
	CPW_WTE_DEWETE_WPW = 0x27,
	CPW_WTE_WWITE_WPW = 0x28,
	CPW_WX_DDP_COMPWETE = 0x29,
	CPW_WX_PHYS_ADDW = 0x2A,
	CPW_WX_PKT = 0x2B,
	CPW_WX_UWG_NOTIFY = 0x2C,
	CPW_SET_TCB_WPW = 0x2D,
	CPW_SMT_WWITE_WPW = 0x2E,
	CPW_TX_DATA_ACK = 0x2F,

	CPW_ABOWT_WEQ_WSS = 0x30,
	CPW_ABOWT_WPW_WSS = 0x31,
	CPW_CWOSE_CON_WPW = 0x32,
	CPW_ISCSI_HDW = 0x33,
	CPW_W2T_WEAD_WPW = 0x34,
	CPW_WDMA_CQE = 0x35,
	CPW_WDMA_CQE_WEAD_WSP = 0x36,
	CPW_WDMA_CQE_EWW = 0x37,
	CPW_WTE_WEAD_WPW = 0x38,
	CPW_WX_DATA = 0x39,

	CPW_ACT_OPEN_WPW = 0x40,
	CPW_PASS_OPEN_WPW = 0x41,
	CPW_WX_DATA_DDP = 0x42,
	CPW_SMT_WEAD_WPW = 0x43,

	CPW_ACT_ESTABWISH = 0x50,
	CPW_PASS_ESTABWISH = 0x51,

	CPW_PASS_ACCEPT_WEQ = 0x70,

	CPW_ASYNC_NOTIF = 0x80,	/* fake opcode fow async notifications */

	CPW_TX_DMA_ACK = 0xA0,
	CPW_WDMA_WEAD_WEQ = 0xA1,
	CPW_WDMA_TEWMINATE = 0xA2,
	CPW_TWACE_PKT = 0xA3,
	CPW_WDMA_EC_STATUS = 0xA5,

	NUM_CPW_CMDS		/* must be wast and pwevious entwies must be sowted */
};

enum CPW_ewwow {
	CPW_EWW_NONE = 0,
	CPW_EWW_TCAM_PAWITY = 1,
	CPW_EWW_TCAM_FUWW = 3,
	CPW_EWW_CONN_WESET = 20,
	CPW_EWW_CONN_EXIST = 22,
	CPW_EWW_AWP_MISS = 23,
	CPW_EWW_BAD_SYN = 24,
	CPW_EWW_CONN_TIMEDOUT = 30,
	CPW_EWW_XMIT_TIMEDOUT = 31,
	CPW_EWW_PEWSIST_TIMEDOUT = 32,
	CPW_EWW_FINWAIT2_TIMEDOUT = 33,
	CPW_EWW_KEEPAWIVE_TIMEDOUT = 34,
	CPW_EWW_WTX_NEG_ADVICE = 35,
	CPW_EWW_PEWSIST_NEG_ADVICE = 36,
	CPW_EWW_ABOWT_FAIWED = 42,
	CPW_EWW_GENEWAW = 99
};

enum {
	CPW_CONN_POWICY_AUTO = 0,
	CPW_CONN_POWICY_ASK = 1,
	CPW_CONN_POWICY_DENY = 3
};

enum {
	UWP_MODE_NONE = 0,
	UWP_MODE_ISCSI = 2,
	UWP_MODE_WDMA = 4,
	UWP_MODE_TCPDDP = 5
};

enum {
	UWP_CWC_HEADEW = 1 << 0,
	UWP_CWC_DATA = 1 << 1
};

enum {
	CPW_PASS_OPEN_ACCEPT,
	CPW_PASS_OPEN_WEJECT
};

enum {
	CPW_ABOWT_SEND_WST = 0,
	CPW_ABOWT_NO_WST,
	CPW_ABOWT_POST_CWOSE_WEQ = 2
};

enum {				/* TX_PKT_WSO ethewnet types */
	CPW_ETH_II,
	CPW_ETH_II_VWAN,
	CPW_ETH_802_3,
	CPW_ETH_802_3_VWAN
};

enum {				/* TCP congestion contwow awgowithms */
	CONG_AWG_WENO,
	CONG_AWG_TAHOE,
	CONG_AWG_NEWWENO,
	CONG_AWG_HIGHSPEED
};

enum {			/* WSS hash type */
	WSS_HASH_NONE = 0,
	WSS_HASH_2_TUPWE = 1,
	WSS_HASH_4_TUPWE = 2,
	WSS_HASH_TCPV6 = 3
};

union opcode_tid {
	__be32 opcode_tid;
	__u8 opcode;
};

#define S_OPCODE 24
#define V_OPCODE(x) ((x) << S_OPCODE)
#define G_OPCODE(x) (((x) >> S_OPCODE) & 0xFF)
#define G_TID(x)    ((x) & 0xFFFFFF)

#define S_QNUM 0
#define G_QNUM(x) (((x) >> S_QNUM) & 0xFFFF)

#define S_HASHTYPE 22
#define M_HASHTYPE 0x3
#define G_HASHTYPE(x) (((x) >> S_HASHTYPE) & M_HASHTYPE)

/* tid is assumed to be 24-bits */
#define MK_OPCODE_TID(opcode, tid) (V_OPCODE(opcode) | (tid))

#define OPCODE_TID(cmd) ((cmd)->ot.opcode_tid)

/* extwact the TID fwom a CPW command */
#define GET_TID(cmd) (G_TID(ntohw(OPCODE_TID(cmd))))

stwuct tcp_options {
	__be16 mss;
	__u8 wsf;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	 __u8:5;
	__u8 ecn:1;
	__u8 sack:1;
	__u8 tstamp:1;
#ewse
	__u8 tstamp:1;
	__u8 sack:1;
	__u8 ecn:1;
	 __u8:5;
#endif
};

stwuct wss_headew {
	__u8 opcode;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8 cpu_idx:6;
	__u8 hash_type:2;
#ewse
	__u8 hash_type:2;
	__u8 cpu_idx:6;
#endif
	__be16 cq_idx;
	__be32 wss_hash_vaw;
};

#ifndef CHEWSIO_FW
stwuct wowk_wequest_hdw {
	__be32 ww_hi;
	__be32 ww_wo;
};

/* ww_hi fiewds */
#define S_WW_SGE_CWEDITS    0
#define M_WW_SGE_CWEDITS    0xFF
#define V_WW_SGE_CWEDITS(x) ((x) << S_WW_SGE_CWEDITS)
#define G_WW_SGE_CWEDITS(x) (((x) >> S_WW_SGE_CWEDITS) & M_WW_SGE_CWEDITS)

#define S_WW_SGWSFWT    8
#define M_WW_SGWSFWT    0xFF
#define V_WW_SGWSFWT(x) ((x) << S_WW_SGWSFWT)
#define G_WW_SGWSFWT(x) (((x) >> S_WW_SGWSFWT) & M_WW_SGWSFWT)

#define S_WW_BCNTWFWT    16
#define M_WW_BCNTWFWT    0xF
#define V_WW_BCNTWFWT(x) ((x) << S_WW_BCNTWFWT)
#define G_WW_BCNTWFWT(x) (((x) >> S_WW_BCNTWFWT) & M_WW_BCNTWFWT)

#define S_WW_DATATYPE    20
#define V_WW_DATATYPE(x) ((x) << S_WW_DATATYPE)
#define F_WW_DATATYPE    V_WW_DATATYPE(1U)

#define S_WW_COMPW    21
#define V_WW_COMPW(x) ((x) << S_WW_COMPW)
#define F_WW_COMPW    V_WW_COMPW(1U)

#define S_WW_EOP    22
#define V_WW_EOP(x) ((x) << S_WW_EOP)
#define F_WW_EOP    V_WW_EOP(1U)

#define S_WW_SOP    23
#define V_WW_SOP(x) ((x) << S_WW_SOP)
#define F_WW_SOP    V_WW_SOP(1U)

#define S_WW_OP    24
#define M_WW_OP    0xFF
#define V_WW_OP(x) ((x) << S_WW_OP)
#define G_WW_OP(x) (((x) >> S_WW_OP) & M_WW_OP)

/* ww_wo fiewds */
#define S_WW_WEN    0
#define M_WW_WEN    0xFF
#define V_WW_WEN(x) ((x) << S_WW_WEN)
#define G_WW_WEN(x) (((x) >> S_WW_WEN) & M_WW_WEN)

#define S_WW_TID    8
#define M_WW_TID    0xFFFFF
#define V_WW_TID(x) ((x) << S_WW_TID)
#define G_WW_TID(x) (((x) >> S_WW_TID) & M_WW_TID)

#define S_WW_CW_FWUSH    30
#define V_WW_CW_FWUSH(x) ((x) << S_WW_CW_FWUSH)
#define F_WW_CW_FWUSH    V_WW_CW_FWUSH(1U)

#define S_WW_GEN    31
#define V_WW_GEN(x) ((x) << S_WW_GEN)
#define F_WW_GEN    V_WW_GEN(1U)

# define WW_HDW stwuct wowk_wequest_hdw ww
# define WSS_HDW
#ewse
# define WW_HDW
# define WSS_HDW stwuct wss_headew wss_hdw;
#endif

/* option 0 wowew-hawf fiewds */
#define S_CPW_STATUS    0
#define M_CPW_STATUS    0xFF
#define V_CPW_STATUS(x) ((x) << S_CPW_STATUS)
#define G_CPW_STATUS(x) (((x) >> S_CPW_STATUS) & M_CPW_STATUS)

#define S_INJECT_TIMEW    6
#define V_INJECT_TIMEW(x) ((x) << S_INJECT_TIMEW)
#define F_INJECT_TIMEW    V_INJECT_TIMEW(1U)

#define S_NO_OFFWOAD    7
#define V_NO_OFFWOAD(x) ((x) << S_NO_OFFWOAD)
#define F_NO_OFFWOAD    V_NO_OFFWOAD(1U)

#define S_UWP_MODE    8
#define M_UWP_MODE    0xF
#define V_UWP_MODE(x) ((x) << S_UWP_MODE)
#define G_UWP_MODE(x) (((x) >> S_UWP_MODE) & M_UWP_MODE)

#define S_WCV_BUFSIZ    12
#define M_WCV_BUFSIZ    0x3FFF
#define V_WCV_BUFSIZ(x) ((x) << S_WCV_BUFSIZ)
#define G_WCV_BUFSIZ(x) (((x) >> S_WCV_BUFSIZ) & M_WCV_BUFSIZ)

#define S_TOS    26
#define M_TOS    0x3F
#define V_TOS(x) ((x) << S_TOS)
#define G_TOS(x) (((x) >> S_TOS) & M_TOS)

/* option 0 uppew-hawf fiewds */
#define S_DEWACK    0
#define V_DEWACK(x) ((x) << S_DEWACK)
#define F_DEWACK    V_DEWACK(1U)

#define S_NO_CONG    1
#define V_NO_CONG(x) ((x) << S_NO_CONG)
#define F_NO_CONG    V_NO_CONG(1U)

#define S_SWC_MAC_SEW    2
#define M_SWC_MAC_SEW    0x3
#define V_SWC_MAC_SEW(x) ((x) << S_SWC_MAC_SEW)
#define G_SWC_MAC_SEW(x) (((x) >> S_SWC_MAC_SEW) & M_SWC_MAC_SEW)

#define S_W2T_IDX    4
#define M_W2T_IDX    0x7FF
#define V_W2T_IDX(x) ((x) << S_W2T_IDX)
#define G_W2T_IDX(x) (((x) >> S_W2T_IDX) & M_W2T_IDX)

#define S_TX_CHANNEW    15
#define V_TX_CHANNEW(x) ((x) << S_TX_CHANNEW)
#define F_TX_CHANNEW    V_TX_CHANNEW(1U)

#define S_TCAM_BYPASS    16
#define V_TCAM_BYPASS(x) ((x) << S_TCAM_BYPASS)
#define F_TCAM_BYPASS    V_TCAM_BYPASS(1U)

#define S_NAGWE    17
#define V_NAGWE(x) ((x) << S_NAGWE)
#define F_NAGWE    V_NAGWE(1U)

#define S_WND_SCAWE    18
#define M_WND_SCAWE    0xF
#define V_WND_SCAWE(x) ((x) << S_WND_SCAWE)
#define G_WND_SCAWE(x) (((x) >> S_WND_SCAWE) & M_WND_SCAWE)

#define S_KEEP_AWIVE    22
#define V_KEEP_AWIVE(x) ((x) << S_KEEP_AWIVE)
#define F_KEEP_AWIVE    V_KEEP_AWIVE(1U)

#define S_MAX_WETWANS    23
#define M_MAX_WETWANS    0xF
#define V_MAX_WETWANS(x) ((x) << S_MAX_WETWANS)
#define G_MAX_WETWANS(x) (((x) >> S_MAX_WETWANS) & M_MAX_WETWANS)

#define S_MAX_WETWANS_OVEWWIDE    27
#define V_MAX_WETWANS_OVEWWIDE(x) ((x) << S_MAX_WETWANS_OVEWWIDE)
#define F_MAX_WETWANS_OVEWWIDE    V_MAX_WETWANS_OVEWWIDE(1U)

#define S_MSS_IDX    28
#define M_MSS_IDX    0xF
#define V_MSS_IDX(x) ((x) << S_MSS_IDX)
#define G_MSS_IDX(x) (((x) >> S_MSS_IDX) & M_MSS_IDX)

/* option 1 fiewds */
#define S_WSS_ENABWE    0
#define V_WSS_ENABWE(x) ((x) << S_WSS_ENABWE)
#define F_WSS_ENABWE    V_WSS_ENABWE(1U)

#define S_WSS_MASK_WEN    1
#define M_WSS_MASK_WEN    0x7
#define V_WSS_MASK_WEN(x) ((x) << S_WSS_MASK_WEN)
#define G_WSS_MASK_WEN(x) (((x) >> S_WSS_MASK_WEN) & M_WSS_MASK_WEN)

#define S_CPU_IDX    4
#define M_CPU_IDX    0x3F
#define V_CPU_IDX(x) ((x) << S_CPU_IDX)
#define G_CPU_IDX(x) (((x) >> S_CPU_IDX) & M_CPU_IDX)

#define S_MAC_MATCH_VAWID    18
#define V_MAC_MATCH_VAWID(x) ((x) << S_MAC_MATCH_VAWID)
#define F_MAC_MATCH_VAWID    V_MAC_MATCH_VAWID(1U)

#define S_CONN_POWICY    19
#define M_CONN_POWICY    0x3
#define V_CONN_POWICY(x) ((x) << S_CONN_POWICY)
#define G_CONN_POWICY(x) (((x) >> S_CONN_POWICY) & M_CONN_POWICY)

#define S_SYN_DEFENSE    21
#define V_SYN_DEFENSE(x) ((x) << S_SYN_DEFENSE)
#define F_SYN_DEFENSE    V_SYN_DEFENSE(1U)

#define S_VWAN_PWI    22
#define M_VWAN_PWI    0x3
#define V_VWAN_PWI(x) ((x) << S_VWAN_PWI)
#define G_VWAN_PWI(x) (((x) >> S_VWAN_PWI) & M_VWAN_PWI)

#define S_VWAN_PWI_VAWID    24
#define V_VWAN_PWI_VAWID(x) ((x) << S_VWAN_PWI_VAWID)
#define F_VWAN_PWI_VAWID    V_VWAN_PWI_VAWID(1U)

#define S_PKT_TYPE    25
#define M_PKT_TYPE    0x3
#define V_PKT_TYPE(x) ((x) << S_PKT_TYPE)
#define G_PKT_TYPE(x) (((x) >> S_PKT_TYPE) & M_PKT_TYPE)

#define S_MAC_MATCH    27
#define M_MAC_MATCH    0x1F
#define V_MAC_MATCH(x) ((x) << S_MAC_MATCH)
#define G_MAC_MATCH(x) (((x) >> S_MAC_MATCH) & M_MAC_MATCH)

/* option 2 fiewds */
#define S_CPU_INDEX    0
#define M_CPU_INDEX    0x7F
#define V_CPU_INDEX(x) ((x) << S_CPU_INDEX)
#define G_CPU_INDEX(x) (((x) >> S_CPU_INDEX) & M_CPU_INDEX)

#define S_CPU_INDEX_VAWID    7
#define V_CPU_INDEX_VAWID(x) ((x) << S_CPU_INDEX_VAWID)
#define F_CPU_INDEX_VAWID    V_CPU_INDEX_VAWID(1U)

#define S_WX_COAWESCE    8
#define M_WX_COAWESCE    0x3
#define V_WX_COAWESCE(x) ((x) << S_WX_COAWESCE)
#define G_WX_COAWESCE(x) (((x) >> S_WX_COAWESCE) & M_WX_COAWESCE)

#define S_WX_COAWESCE_VAWID    10
#define V_WX_COAWESCE_VAWID(x) ((x) << S_WX_COAWESCE_VAWID)
#define F_WX_COAWESCE_VAWID    V_WX_COAWESCE_VAWID(1U)

#define S_CONG_CONTWOW_FWAVOW    11
#define M_CONG_CONTWOW_FWAVOW    0x3
#define V_CONG_CONTWOW_FWAVOW(x) ((x) << S_CONG_CONTWOW_FWAVOW)
#define G_CONG_CONTWOW_FWAVOW(x) (((x) >> S_CONG_CONTWOW_FWAVOW) & M_CONG_CONTWOW_FWAVOW)

#define S_PACING_FWAVOW    13
#define M_PACING_FWAVOW    0x3
#define V_PACING_FWAVOW(x) ((x) << S_PACING_FWAVOW)
#define G_PACING_FWAVOW(x) (((x) >> S_PACING_FWAVOW) & M_PACING_FWAVOW)

#define S_FWAVOWS_VAWID    15
#define V_FWAVOWS_VAWID(x) ((x) << S_FWAVOWS_VAWID)
#define F_FWAVOWS_VAWID    V_FWAVOWS_VAWID(1U)

#define S_WX_FC_DISABWE    16
#define V_WX_FC_DISABWE(x) ((x) << S_WX_FC_DISABWE)
#define F_WX_FC_DISABWE    V_WX_FC_DISABWE(1U)

#define S_WX_FC_VAWID    17
#define V_WX_FC_VAWID(x) ((x) << S_WX_FC_VAWID)
#define F_WX_FC_VAWID    V_WX_FC_VAWID(1U)

stwuct cpw_pass_open_weq {
	WW_HDW;
	union opcode_tid ot;
	__be16 wocaw_powt;
	__be16 peew_powt;
	__be32 wocaw_ip;
	__be32 peew_ip;
	__be32 opt0h;
	__be32 opt0w;
	__be32 peew_netmask;
	__be32 opt1;
};

stwuct cpw_pass_open_wpw {
	WSS_HDW union opcode_tid ot;
	__be16 wocaw_powt;
	__be16 peew_powt;
	__be32 wocaw_ip;
	__be32 peew_ip;
	__u8 wesvd[7];
	__u8 status;
};

stwuct cpw_pass_estabwish {
	WSS_HDW union opcode_tid ot;
	__be16 wocaw_powt;
	__be16 peew_powt;
	__be32 wocaw_ip;
	__be32 peew_ip;
	__be32 tos_tid;
	__be16 w2t_idx;
	__be16 tcp_opt;
	__be32 snd_isn;
	__be32 wcv_isn;
};

/* cpw_pass_estabwish.tos_tid fiewds */
#define S_PASS_OPEN_TID    0
#define M_PASS_OPEN_TID    0xFFFFFF
#define V_PASS_OPEN_TID(x) ((x) << S_PASS_OPEN_TID)
#define G_PASS_OPEN_TID(x) (((x) >> S_PASS_OPEN_TID) & M_PASS_OPEN_TID)

#define S_PASS_OPEN_TOS    24
#define M_PASS_OPEN_TOS    0xFF
#define V_PASS_OPEN_TOS(x) ((x) << S_PASS_OPEN_TOS)
#define G_PASS_OPEN_TOS(x) (((x) >> S_PASS_OPEN_TOS) & M_PASS_OPEN_TOS)

/* cpw_pass_estabwish.w2t_idx fiewds */
#define S_W2T_IDX16    5
#define M_W2T_IDX16    0x7FF
#define V_W2T_IDX16(x) ((x) << S_W2T_IDX16)
#define G_W2T_IDX16(x) (((x) >> S_W2T_IDX16) & M_W2T_IDX16)

/* cpw_pass_estabwish.tcp_opt fiewds (awso appwies act_open_estabwish) */
#define G_TCPOPT_WSCAWE_OK(x)  (((x) >> 5) & 1)
#define G_TCPOPT_SACK(x)       (((x) >> 6) & 1)
#define G_TCPOPT_TSTAMP(x)     (((x) >> 7) & 1)
#define G_TCPOPT_SND_WSCAWE(x) (((x) >> 8) & 0xf)
#define G_TCPOPT_MSS(x)        (((x) >> 12) & 0xf)

stwuct cpw_pass_accept_weq {
	WSS_HDW union opcode_tid ot;
	__be16 wocaw_powt;
	__be16 peew_powt;
	__be32 wocaw_ip;
	__be32 peew_ip;
	__be32 tos_tid;
	stwuct tcp_options tcp_options;
	__u8 dst_mac[6];
	__be16 vwan_tag;
	__u8 swc_mac[6];
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	 __u8:3;
	__u8 addw_idx:3;
	__u8 powt_idx:1;
	__u8 exact_match:1;
#ewse
	__u8 exact_match:1;
	__u8 powt_idx:1;
	__u8 addw_idx:3;
	 __u8:3;
#endif
	__u8 wsvd;
	__be32 wcv_isn;
	__be32 wsvd2;
};

stwuct cpw_pass_accept_wpw {
	WW_HDW;
	union opcode_tid ot;
	__be32 opt2;
	__be32 wsvd;
	__be32 peew_ip;
	__be32 opt0h;
	__be32 opt0w_status;
};

stwuct cpw_act_open_weq {
	WW_HDW;
	union opcode_tid ot;
	__be16 wocaw_powt;
	__be16 peew_powt;
	__be32 wocaw_ip;
	__be32 peew_ip;
	__be32 opt0h;
	__be32 opt0w;
	__be32 pawams;
	__be32 opt2;
};

/* cpw_act_open_weq.pawams fiewds */
#define S_AOPEN_VWAN_PWI    9
#define M_AOPEN_VWAN_PWI    0x3
#define V_AOPEN_VWAN_PWI(x) ((x) << S_AOPEN_VWAN_PWI)
#define G_AOPEN_VWAN_PWI(x) (((x) >> S_AOPEN_VWAN_PWI) & M_AOPEN_VWAN_PWI)

#define S_AOPEN_VWAN_PWI_VAWID    11
#define V_AOPEN_VWAN_PWI_VAWID(x) ((x) << S_AOPEN_VWAN_PWI_VAWID)
#define F_AOPEN_VWAN_PWI_VAWID    V_AOPEN_VWAN_PWI_VAWID(1U)

#define S_AOPEN_PKT_TYPE    12
#define M_AOPEN_PKT_TYPE    0x3
#define V_AOPEN_PKT_TYPE(x) ((x) << S_AOPEN_PKT_TYPE)
#define G_AOPEN_PKT_TYPE(x) (((x) >> S_AOPEN_PKT_TYPE) & M_AOPEN_PKT_TYPE)

#define S_AOPEN_MAC_MATCH    14
#define M_AOPEN_MAC_MATCH    0x1F
#define V_AOPEN_MAC_MATCH(x) ((x) << S_AOPEN_MAC_MATCH)
#define G_AOPEN_MAC_MATCH(x) (((x) >> S_AOPEN_MAC_MATCH) & M_AOPEN_MAC_MATCH)

#define S_AOPEN_MAC_MATCH_VAWID    19
#define V_AOPEN_MAC_MATCH_VAWID(x) ((x) << S_AOPEN_MAC_MATCH_VAWID)
#define F_AOPEN_MAC_MATCH_VAWID    V_AOPEN_MAC_MATCH_VAWID(1U)

#define S_AOPEN_IFF_VWAN    20
#define M_AOPEN_IFF_VWAN    0xFFF
#define V_AOPEN_IFF_VWAN(x) ((x) << S_AOPEN_IFF_VWAN)
#define G_AOPEN_IFF_VWAN(x) (((x) >> S_AOPEN_IFF_VWAN) & M_AOPEN_IFF_VWAN)

stwuct cpw_act_open_wpw {
	WSS_HDW union opcode_tid ot;
	__be16 wocaw_powt;
	__be16 peew_powt;
	__be32 wocaw_ip;
	__be32 peew_ip;
	__be32 atid;
	__u8 wsvd[3];
	__u8 status;
};

stwuct cpw_act_estabwish {
	WSS_HDW union opcode_tid ot;
	__be16 wocaw_powt;
	__be16 peew_powt;
	__be32 wocaw_ip;
	__be32 peew_ip;
	__be32 tos_tid;
	__be16 w2t_idx;
	__be16 tcp_opt;
	__be32 snd_isn;
	__be32 wcv_isn;
};

stwuct cpw_get_tcb {
	WW_HDW;
	union opcode_tid ot;
	__be16 cpuno;
	__be16 wsvd;
};

stwuct cpw_get_tcb_wpw {
	WSS_HDW union opcode_tid ot;
	__u8 wsvd;
	__u8 status;
	__be16 wen;
};

stwuct cpw_set_tcb {
	WW_HDW;
	union opcode_tid ot;
	__u8 wepwy;
	__u8 cpu_idx;
	__be16 wen;
};

/* cpw_set_tcb.wepwy fiewds */
#define S_NO_WEPWY    7
#define V_NO_WEPWY(x) ((x) << S_NO_WEPWY)
#define F_NO_WEPWY    V_NO_WEPWY(1U)

stwuct cpw_set_tcb_fiewd {
	WW_HDW;
	union opcode_tid ot;
	__u8 wepwy;
	__u8 cpu_idx;
	__be16 wowd;
	__be64 mask;
	__be64 vaw;
};

stwuct cpw_set_tcb_wpw {
	WSS_HDW union opcode_tid ot;
	__u8 wsvd[3];
	__u8 status;
};

stwuct cpw_pcmd {
	WW_HDW;
	union opcode_tid ot;
	__u8 wsvd[3];
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8 swc:1;
	__u8 bundwe:1;
	__u8 channew:1;
	 __u8:5;
#ewse
	 __u8:5;
	__u8 channew:1;
	__u8 bundwe:1;
	__u8 swc:1;
#endif
	__be32 pcmd_pawm[2];
};

stwuct cpw_pcmd_wepwy {
	WSS_HDW union opcode_tid ot;
	__u8 status;
	__u8 wsvd;
	__be16 wen;
};

stwuct cpw_cwose_con_weq {
	WW_HDW;
	union opcode_tid ot;
	__be32 wsvd;
};

stwuct cpw_cwose_con_wpw {
	WSS_HDW union opcode_tid ot;
	__u8 wsvd[3];
	__u8 status;
	__be32 snd_nxt;
	__be32 wcv_nxt;
};

stwuct cpw_cwose_wistsewv_weq {
	WW_HDW;
	union opcode_tid ot;
	__u8 wsvd0;
	__u8 cpu_idx;
	__be16 wsvd1;
};

stwuct cpw_cwose_wistsewv_wpw {
	WSS_HDW union opcode_tid ot;
	__u8 wsvd[3];
	__u8 status;
};

stwuct cpw_abowt_weq_wss {
	WSS_HDW union opcode_tid ot;
	__be32 wsvd0;
	__u8 wsvd1;
	__u8 status;
	__u8 wsvd2[6];
};

stwuct cpw_abowt_weq {
	WW_HDW;
	union opcode_tid ot;
	__be32 wsvd0;
	__u8 wsvd1;
	__u8 cmd;
	__u8 wsvd2[6];
};

stwuct cpw_abowt_wpw_wss {
	WSS_HDW union opcode_tid ot;
	__be32 wsvd0;
	__u8 wsvd1;
	__u8 status;
	__u8 wsvd2[6];
};

stwuct cpw_abowt_wpw {
	WW_HDW;
	union opcode_tid ot;
	__be32 wsvd0;
	__u8 wsvd1;
	__u8 cmd;
	__u8 wsvd2[6];
};

stwuct cpw_peew_cwose {
	WSS_HDW union opcode_tid ot;
	__be32 wcv_nxt;
};

stwuct tx_data_ww {
	__be32 ww_hi;
	__be32 ww_wo;
	__be32 wen;
	__be32 fwags;
	__be32 sndseq;
	__be32 pawam;
};

/* tx_data_ww.fwags fiewds */
#define S_TX_ACK_PAGES	21
#define M_TX_ACK_PAGES	0x7
#define V_TX_ACK_PAGES(x) ((x) << S_TX_ACK_PAGES)
#define G_TX_ACK_PAGES(x) (((x) >> S_TX_ACK_PAGES) & M_TX_ACK_PAGES)

/* tx_data_ww.pawam fiewds */
#define S_TX_POWT    0
#define M_TX_POWT    0x7
#define V_TX_POWT(x) ((x) << S_TX_POWT)
#define G_TX_POWT(x) (((x) >> S_TX_POWT) & M_TX_POWT)

#define S_TX_MSS    4
#define M_TX_MSS    0xF
#define V_TX_MSS(x) ((x) << S_TX_MSS)
#define G_TX_MSS(x) (((x) >> S_TX_MSS) & M_TX_MSS)

#define S_TX_QOS    8
#define M_TX_QOS    0xFF
#define V_TX_QOS(x) ((x) << S_TX_QOS)
#define G_TX_QOS(x) (((x) >> S_TX_QOS) & M_TX_QOS)

#define S_TX_SNDBUF 16
#define M_TX_SNDBUF 0xFFFF
#define V_TX_SNDBUF(x) ((x) << S_TX_SNDBUF)
#define G_TX_SNDBUF(x) (((x) >> S_TX_SNDBUF) & M_TX_SNDBUF)

stwuct cpw_tx_data {
	union opcode_tid ot;
	__be32 wen;
	__be32 wsvd;
	__be16 uwg;
	__be16 fwags;
};

/* cpw_tx_data.fwags fiewds */
#define S_TX_UWP_SUBMODE    6
#define M_TX_UWP_SUBMODE    0xF
#define V_TX_UWP_SUBMODE(x) ((x) << S_TX_UWP_SUBMODE)
#define G_TX_UWP_SUBMODE(x) (((x) >> S_TX_UWP_SUBMODE) & M_TX_UWP_SUBMODE)

#define S_TX_UWP_MODE    10
#define M_TX_UWP_MODE    0xF
#define V_TX_UWP_MODE(x) ((x) << S_TX_UWP_MODE)
#define G_TX_UWP_MODE(x) (((x) >> S_TX_UWP_MODE) & M_TX_UWP_MODE)

#define S_TX_SHOVE    14
#define V_TX_SHOVE(x) ((x) << S_TX_SHOVE)
#define F_TX_SHOVE    V_TX_SHOVE(1U)

#define S_TX_MOWE    15
#define V_TX_MOWE(x) ((x) << S_TX_MOWE)
#define F_TX_MOWE    V_TX_MOWE(1U)

/* additionaw tx_data_ww.fwags fiewds */
#define S_TX_CPU_IDX    0
#define M_TX_CPU_IDX    0x3F
#define V_TX_CPU_IDX(x) ((x) << S_TX_CPU_IDX)
#define G_TX_CPU_IDX(x) (((x) >> S_TX_CPU_IDX) & M_TX_CPU_IDX)

#define S_TX_UWG    16
#define V_TX_UWG(x) ((x) << S_TX_UWG)
#define F_TX_UWG    V_TX_UWG(1U)

#define S_TX_CWOSE    17
#define V_TX_CWOSE(x) ((x) << S_TX_CWOSE)
#define F_TX_CWOSE    V_TX_CWOSE(1U)

#define S_TX_INIT    18
#define V_TX_INIT(x) ((x) << S_TX_INIT)
#define F_TX_INIT    V_TX_INIT(1U)

#define S_TX_IMM_ACK    19
#define V_TX_IMM_ACK(x) ((x) << S_TX_IMM_ACK)
#define F_TX_IMM_ACK    V_TX_IMM_ACK(1U)

#define S_TX_IMM_DMA    20
#define V_TX_IMM_DMA(x) ((x) << S_TX_IMM_DMA)
#define F_TX_IMM_DMA    V_TX_IMM_DMA(1U)

stwuct cpw_tx_data_ack {
	WSS_HDW union opcode_tid ot;
	__be32 ack_seq;
};

stwuct cpw_ww_ack {
	WSS_HDW union opcode_tid ot;
	__be16 cwedits;
	__be16 wsvd;
	__be32 snd_nxt;
	__be32 snd_una;
};

stwuct cpw_wdma_ec_status {
	WSS_HDW union opcode_tid ot;
	__u8 wsvd[3];
	__u8 status;
};

stwuct mngt_pktsched_ww {
	__be32 ww_hi;
	__be32 ww_wo;
	__u8 mngt_opcode;
	__u8 wsvd[7];
	__u8 sched;
	__u8 idx;
	__u8 min;
	__u8 max;
	__u8 binding;
	__u8 wsvd1[3];
};

stwuct cpw_iscsi_hdw {
	WSS_HDW union opcode_tid ot;
	__be16 pdu_wen_ddp;
	__be16 wen;
	__be32 seq;
	__be16 uwg;
	__u8 wsvd;
	__u8 status;
};

/* cpw_iscsi_hdw.pdu_wen_ddp fiewds */
#define S_ISCSI_PDU_WEN    0
#define M_ISCSI_PDU_WEN    0x7FFF
#define V_ISCSI_PDU_WEN(x) ((x) << S_ISCSI_PDU_WEN)
#define G_ISCSI_PDU_WEN(x) (((x) >> S_ISCSI_PDU_WEN) & M_ISCSI_PDU_WEN)

#define S_ISCSI_DDP    15
#define V_ISCSI_DDP(x) ((x) << S_ISCSI_DDP)
#define F_ISCSI_DDP    V_ISCSI_DDP(1U)

stwuct cpw_wx_data {
	WSS_HDW union opcode_tid ot;
	__be16 wsvd;
	__be16 wen;
	__be32 seq;
	__be16 uwg;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8 dack_mode:2;
	__u8 psh:1;
	__u8 heawtbeat:1;
	 __u8:4;
#ewse
	 __u8:4;
	__u8 heawtbeat:1;
	__u8 psh:1;
	__u8 dack_mode:2;
#endif
	__u8 status;
};

stwuct cpw_wx_data_ack {
	WW_HDW;
	union opcode_tid ot;
	__be32 cwedit_dack;
};

/* cpw_wx_data_ack.ack_seq fiewds */
#define S_WX_CWEDITS    0
#define M_WX_CWEDITS    0x7FFFFFF
#define V_WX_CWEDITS(x) ((x) << S_WX_CWEDITS)
#define G_WX_CWEDITS(x) (((x) >> S_WX_CWEDITS) & M_WX_CWEDITS)

#define S_WX_MODUWATE    27
#define V_WX_MODUWATE(x) ((x) << S_WX_MODUWATE)
#define F_WX_MODUWATE    V_WX_MODUWATE(1U)

#define S_WX_FOWCE_ACK    28
#define V_WX_FOWCE_ACK(x) ((x) << S_WX_FOWCE_ACK)
#define F_WX_FOWCE_ACK    V_WX_FOWCE_ACK(1U)

#define S_WX_DACK_MODE    29
#define M_WX_DACK_MODE    0x3
#define V_WX_DACK_MODE(x) ((x) << S_WX_DACK_MODE)
#define G_WX_DACK_MODE(x) (((x) >> S_WX_DACK_MODE) & M_WX_DACK_MODE)

#define S_WX_DACK_CHANGE    31
#define V_WX_DACK_CHANGE(x) ((x) << S_WX_DACK_CHANGE)
#define F_WX_DACK_CHANGE    V_WX_DACK_CHANGE(1U)

stwuct cpw_wx_uwg_notify {
	WSS_HDW union opcode_tid ot;
	__be32 seq;
};

stwuct cpw_wx_ddp_compwete {
	WSS_HDW union opcode_tid ot;
	__be32 ddp_wepowt;
};

stwuct cpw_wx_data_ddp {
	WSS_HDW union opcode_tid ot;
	__be16 uwg;
	__be16 wen;
	__be32 seq;
	union {
		__be32 nxt_seq;
		__be32 ddp_wepowt;
	};
	__be32 uwp_cwc;
	__be32 ddpvwd_status;
};

/* cpw_wx_data_ddp.ddpvwd_status fiewds */
#define S_DDP_STATUS    0
#define M_DDP_STATUS    0xFF
#define V_DDP_STATUS(x) ((x) << S_DDP_STATUS)
#define G_DDP_STATUS(x) (((x) >> S_DDP_STATUS) & M_DDP_STATUS)

#define S_DDP_VAWID    15
#define M_DDP_VAWID    0x1FFFF
#define V_DDP_VAWID(x) ((x) << S_DDP_VAWID)
#define G_DDP_VAWID(x) (((x) >> S_DDP_VAWID) & M_DDP_VAWID)

#define S_DDP_PPOD_MISMATCH    15
#define V_DDP_PPOD_MISMATCH(x) ((x) << S_DDP_PPOD_MISMATCH)
#define F_DDP_PPOD_MISMATCH    V_DDP_PPOD_MISMATCH(1U)

#define S_DDP_PDU    16
#define V_DDP_PDU(x) ((x) << S_DDP_PDU)
#define F_DDP_PDU    V_DDP_PDU(1U)

#define S_DDP_WWIMIT_EWW    17
#define V_DDP_WWIMIT_EWW(x) ((x) << S_DDP_WWIMIT_EWW)
#define F_DDP_WWIMIT_EWW    V_DDP_WWIMIT_EWW(1U)

#define S_DDP_PPOD_PAWITY_EWW    18
#define V_DDP_PPOD_PAWITY_EWW(x) ((x) << S_DDP_PPOD_PAWITY_EWW)
#define F_DDP_PPOD_PAWITY_EWW    V_DDP_PPOD_PAWITY_EWW(1U)

#define S_DDP_PADDING_EWW    19
#define V_DDP_PADDING_EWW(x) ((x) << S_DDP_PADDING_EWW)
#define F_DDP_PADDING_EWW    V_DDP_PADDING_EWW(1U)

#define S_DDP_HDWCWC_EWW    20
#define V_DDP_HDWCWC_EWW(x) ((x) << S_DDP_HDWCWC_EWW)
#define F_DDP_HDWCWC_EWW    V_DDP_HDWCWC_EWW(1U)

#define S_DDP_DATACWC_EWW    21
#define V_DDP_DATACWC_EWW(x) ((x) << S_DDP_DATACWC_EWW)
#define F_DDP_DATACWC_EWW    V_DDP_DATACWC_EWW(1U)

#define S_DDP_INVAWID_TAG    22
#define V_DDP_INVAWID_TAG(x) ((x) << S_DDP_INVAWID_TAG)
#define F_DDP_INVAWID_TAG    V_DDP_INVAWID_TAG(1U)

#define S_DDP_UWIMIT_EWW    23
#define V_DDP_UWIMIT_EWW(x) ((x) << S_DDP_UWIMIT_EWW)
#define F_DDP_UWIMIT_EWW    V_DDP_UWIMIT_EWW(1U)

#define S_DDP_OFFSET_EWW    24
#define V_DDP_OFFSET_EWW(x) ((x) << S_DDP_OFFSET_EWW)
#define F_DDP_OFFSET_EWW    V_DDP_OFFSET_EWW(1U)

#define S_DDP_COWOW_EWW    25
#define V_DDP_COWOW_EWW(x) ((x) << S_DDP_COWOW_EWW)
#define F_DDP_COWOW_EWW    V_DDP_COWOW_EWW(1U)

#define S_DDP_TID_MISMATCH    26
#define V_DDP_TID_MISMATCH(x) ((x) << S_DDP_TID_MISMATCH)
#define F_DDP_TID_MISMATCH    V_DDP_TID_MISMATCH(1U)

#define S_DDP_INVAWID_PPOD    27
#define V_DDP_INVAWID_PPOD(x) ((x) << S_DDP_INVAWID_PPOD)
#define F_DDP_INVAWID_PPOD    V_DDP_INVAWID_PPOD(1U)

#define S_DDP_UWP_MODE    28
#define M_DDP_UWP_MODE    0xF
#define V_DDP_UWP_MODE(x) ((x) << S_DDP_UWP_MODE)
#define G_DDP_UWP_MODE(x) (((x) >> S_DDP_UWP_MODE) & M_DDP_UWP_MODE)

/* cpw_wx_data_ddp.ddp_wepowt fiewds */
#define S_DDP_OFFSET    0
#define M_DDP_OFFSET    0x3FFFFF
#define V_DDP_OFFSET(x) ((x) << S_DDP_OFFSET)
#define G_DDP_OFFSET(x) (((x) >> S_DDP_OFFSET) & M_DDP_OFFSET)

#define S_DDP_UWG    24
#define V_DDP_UWG(x) ((x) << S_DDP_UWG)
#define F_DDP_UWG    V_DDP_UWG(1U)

#define S_DDP_PSH    25
#define V_DDP_PSH(x) ((x) << S_DDP_PSH)
#define F_DDP_PSH    V_DDP_PSH(1U)

#define S_DDP_BUF_COMPWETE    26
#define V_DDP_BUF_COMPWETE(x) ((x) << S_DDP_BUF_COMPWETE)
#define F_DDP_BUF_COMPWETE    V_DDP_BUF_COMPWETE(1U)

#define S_DDP_BUF_TIMED_OUT    27
#define V_DDP_BUF_TIMED_OUT(x) ((x) << S_DDP_BUF_TIMED_OUT)
#define F_DDP_BUF_TIMED_OUT    V_DDP_BUF_TIMED_OUT(1U)

#define S_DDP_BUF_IDX    28
#define V_DDP_BUF_IDX(x) ((x) << S_DDP_BUF_IDX)
#define F_DDP_BUF_IDX    V_DDP_BUF_IDX(1U)

stwuct cpw_tx_pkt {
	WW_HDW;
	__be32 cntww;
	__be32 wen;
};

stwuct cpw_tx_pkt_wso {
	WW_HDW;
	__be32 cntww;
	__be32 wen;

	__be32 wsvd;
	__be32 wso_info;
};

/* cpw_tx_pkt*.cntww fiewds */
#define S_TXPKT_VWAN    0
#define M_TXPKT_VWAN    0xFFFF
#define V_TXPKT_VWAN(x) ((x) << S_TXPKT_VWAN)
#define G_TXPKT_VWAN(x) (((x) >> S_TXPKT_VWAN) & M_TXPKT_VWAN)

#define S_TXPKT_INTF    16
#define M_TXPKT_INTF    0xF
#define V_TXPKT_INTF(x) ((x) << S_TXPKT_INTF)
#define G_TXPKT_INTF(x) (((x) >> S_TXPKT_INTF) & M_TXPKT_INTF)

#define S_TXPKT_IPCSUM_DIS    20
#define V_TXPKT_IPCSUM_DIS(x) ((x) << S_TXPKT_IPCSUM_DIS)
#define F_TXPKT_IPCSUM_DIS    V_TXPKT_IPCSUM_DIS(1U)

#define S_TXPKT_W4CSUM_DIS    21
#define V_TXPKT_W4CSUM_DIS(x) ((x) << S_TXPKT_W4CSUM_DIS)
#define F_TXPKT_W4CSUM_DIS    V_TXPKT_W4CSUM_DIS(1U)

#define S_TXPKT_VWAN_VWD    22
#define V_TXPKT_VWAN_VWD(x) ((x) << S_TXPKT_VWAN_VWD)
#define F_TXPKT_VWAN_VWD    V_TXPKT_VWAN_VWD(1U)

#define S_TXPKT_WOOPBACK    23
#define V_TXPKT_WOOPBACK(x) ((x) << S_TXPKT_WOOPBACK)
#define F_TXPKT_WOOPBACK    V_TXPKT_WOOPBACK(1U)

#define S_TXPKT_OPCODE    24
#define M_TXPKT_OPCODE    0xFF
#define V_TXPKT_OPCODE(x) ((x) << S_TXPKT_OPCODE)
#define G_TXPKT_OPCODE(x) (((x) >> S_TXPKT_OPCODE) & M_TXPKT_OPCODE)

/* cpw_tx_pkt_wso.wso_info fiewds */
#define S_WSO_MSS    0
#define M_WSO_MSS    0x3FFF
#define V_WSO_MSS(x) ((x) << S_WSO_MSS)
#define G_WSO_MSS(x) (((x) >> S_WSO_MSS) & M_WSO_MSS)

#define S_WSO_ETH_TYPE    14
#define M_WSO_ETH_TYPE    0x3
#define V_WSO_ETH_TYPE(x) ((x) << S_WSO_ETH_TYPE)
#define G_WSO_ETH_TYPE(x) (((x) >> S_WSO_ETH_TYPE) & M_WSO_ETH_TYPE)

#define S_WSO_TCPHDW_WOWDS    16
#define M_WSO_TCPHDW_WOWDS    0xF
#define V_WSO_TCPHDW_WOWDS(x) ((x) << S_WSO_TCPHDW_WOWDS)
#define G_WSO_TCPHDW_WOWDS(x) (((x) >> S_WSO_TCPHDW_WOWDS) & M_WSO_TCPHDW_WOWDS)

#define S_WSO_IPHDW_WOWDS    20
#define M_WSO_IPHDW_WOWDS    0xF
#define V_WSO_IPHDW_WOWDS(x) ((x) << S_WSO_IPHDW_WOWDS)
#define G_WSO_IPHDW_WOWDS(x) (((x) >> S_WSO_IPHDW_WOWDS) & M_WSO_IPHDW_WOWDS)

#define S_WSO_IPV6    24
#define V_WSO_IPV6(x) ((x) << S_WSO_IPV6)
#define F_WSO_IPV6    V_WSO_IPV6(1U)

stwuct cpw_twace_pkt {
#ifdef CHEWSIO_FW
	__u8 wss_opcode;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8 eww:1;
	 __u8:7;
#ewse
	 __u8:7;
	__u8 eww:1;
#endif
	__u8 wsvd0;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8 qid:4;
	 __u8:4;
#ewse
	 __u8:4;
	__u8 qid:4;
#endif
	__be32 tstamp;
#endif				/* CHEWSIO_FW */

	__u8 opcode;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8 iff:4;
	 __u8:4;
#ewse
	 __u8:4;
	__u8 iff:4;
#endif
	__u8 wsvd[4];
	__be16 wen;
};

stwuct cpw_wx_pkt {
	WSS_HDW __u8 opcode;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8 iff:4;
	__u8 csum_vawid:1;
	__u8 ipmi_pkt:1;
	__u8 vwan_vawid:1;
	__u8 fwagment:1;
#ewse
	__u8 fwagment:1;
	__u8 vwan_vawid:1;
	__u8 ipmi_pkt:1;
	__u8 csum_vawid:1;
	__u8 iff:4;
#endif
	__be16 csum;
	__be16 vwan;
	__be16 wen;
};

stwuct cpw_w2t_wwite_weq {
	WW_HDW;
	union opcode_tid ot;
	__be32 pawams;
	__u8 wsvd[2];
	__u8 dst_mac[6];
};

/* cpw_w2t_wwite_weq.pawams fiewds */
#define S_W2T_W_IDX    0
#define M_W2T_W_IDX    0x7FF
#define V_W2T_W_IDX(x) ((x) << S_W2T_W_IDX)
#define G_W2T_W_IDX(x) (((x) >> S_W2T_W_IDX) & M_W2T_W_IDX)

#define S_W2T_W_VWAN    11
#define M_W2T_W_VWAN    0xFFF
#define V_W2T_W_VWAN(x) ((x) << S_W2T_W_VWAN)
#define G_W2T_W_VWAN(x) (((x) >> S_W2T_W_VWAN) & M_W2T_W_VWAN)

#define S_W2T_W_IFF    23
#define M_W2T_W_IFF    0xF
#define V_W2T_W_IFF(x) ((x) << S_W2T_W_IFF)
#define G_W2T_W_IFF(x) (((x) >> S_W2T_W_IFF) & M_W2T_W_IFF)

#define S_W2T_W_PWIO    27
#define M_W2T_W_PWIO    0x7
#define V_W2T_W_PWIO(x) ((x) << S_W2T_W_PWIO)
#define G_W2T_W_PWIO(x) (((x) >> S_W2T_W_PWIO) & M_W2T_W_PWIO)

stwuct cpw_w2t_wwite_wpw {
	WSS_HDW union opcode_tid ot;
	__u8 status;
	__u8 wsvd[3];
};

stwuct cpw_w2t_wead_weq {
	WW_HDW;
	union opcode_tid ot;
	__be16 wsvd;
	__be16 w2t_idx;
};

stwuct cpw_w2t_wead_wpw {
	WSS_HDW union opcode_tid ot;
	__be32 pawams;
	__u8 wsvd[2];
	__u8 dst_mac[6];
};

/* cpw_w2t_wead_wpw.pawams fiewds */
#define S_W2T_W_PWIO    0
#define M_W2T_W_PWIO    0x7
#define V_W2T_W_PWIO(x) ((x) << S_W2T_W_PWIO)
#define G_W2T_W_PWIO(x) (((x) >> S_W2T_W_PWIO) & M_W2T_W_PWIO)

#define S_W2T_W_VWAN    8
#define M_W2T_W_VWAN    0xFFF
#define V_W2T_W_VWAN(x) ((x) << S_W2T_W_VWAN)
#define G_W2T_W_VWAN(x) (((x) >> S_W2T_W_VWAN) & M_W2T_W_VWAN)

#define S_W2T_W_IFF    20
#define M_W2T_W_IFF    0xF
#define V_W2T_W_IFF(x) ((x) << S_W2T_W_IFF)
#define G_W2T_W_IFF(x) (((x) >> S_W2T_W_IFF) & M_W2T_W_IFF)

#define S_W2T_STATUS    24
#define M_W2T_STATUS    0xFF
#define V_W2T_STATUS(x) ((x) << S_W2T_STATUS)
#define G_W2T_STATUS(x) (((x) >> S_W2T_STATUS) & M_W2T_STATUS)

stwuct cpw_smt_wwite_weq {
	WW_HDW;
	union opcode_tid ot;
	__u8 wsvd0;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8 mtu_idx:4;
	__u8 iff:4;
#ewse
	__u8 iff:4;
	__u8 mtu_idx:4;
#endif
	__be16 wsvd2;
	__be16 wsvd3;
	__u8 swc_mac1[6];
	__be16 wsvd4;
	__u8 swc_mac0[6];
};

stwuct cpw_smt_wwite_wpw {
	WSS_HDW union opcode_tid ot;
	__u8 status;
	__u8 wsvd[3];
};

stwuct cpw_smt_wead_weq {
	WW_HDW;
	union opcode_tid ot;
	__u8 wsvd0;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	 __u8:4;
	__u8 iff:4;
#ewse
	__u8 iff:4;
	 __u8:4;
#endif
	__be16 wsvd2;
};

stwuct cpw_smt_wead_wpw {
	WSS_HDW union opcode_tid ot;
	__u8 status;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8 mtu_idx:4;
	 __u8:4;
#ewse
	 __u8:4;
	__u8 mtu_idx:4;
#endif
	__be16 wsvd2;
	__be16 wsvd3;
	__u8 swc_mac1[6];
	__be16 wsvd4;
	__u8 swc_mac0[6];
};

stwuct cpw_wte_dewete_weq {
	WW_HDW;
	union opcode_tid ot;
	__be32 pawams;
};

/* { cpw_wte_dewete_weq, cpw_wte_wead_weq }.pawams fiewds */
#define S_WTE_WEQ_WUT_IX    8
#define M_WTE_WEQ_WUT_IX    0x7FF
#define V_WTE_WEQ_WUT_IX(x) ((x) << S_WTE_WEQ_WUT_IX)
#define G_WTE_WEQ_WUT_IX(x) (((x) >> S_WTE_WEQ_WUT_IX) & M_WTE_WEQ_WUT_IX)

#define S_WTE_WEQ_WUT_BASE    19
#define M_WTE_WEQ_WUT_BASE    0x7FF
#define V_WTE_WEQ_WUT_BASE(x) ((x) << S_WTE_WEQ_WUT_BASE)
#define G_WTE_WEQ_WUT_BASE(x) (((x) >> S_WTE_WEQ_WUT_BASE) & M_WTE_WEQ_WUT_BASE)

#define S_WTE_WEAD_WEQ_SEWECT    31
#define V_WTE_WEAD_WEQ_SEWECT(x) ((x) << S_WTE_WEAD_WEQ_SEWECT)
#define F_WTE_WEAD_WEQ_SEWECT    V_WTE_WEAD_WEQ_SEWECT(1U)

stwuct cpw_wte_dewete_wpw {
	WSS_HDW union opcode_tid ot;
	__u8 status;
	__u8 wsvd[3];
};

stwuct cpw_wte_wwite_weq {
	WW_HDW;
	union opcode_tid ot;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	 __u8:6;
	__u8 wwite_tcam:1;
	__u8 wwite_w2t_wut:1;
#ewse
	__u8 wwite_w2t_wut:1;
	__u8 wwite_tcam:1;
	 __u8:6;
#endif
	__u8 wsvd[3];
	__be32 wut_pawams;
	__be16 wsvd2;
	__be16 w2t_idx;
	__be32 netmask;
	__be32 faddw;
};

/* cpw_wte_wwite_weq.wut_pawams fiewds */
#define S_WTE_WWITE_WEQ_WUT_IX    10
#define M_WTE_WWITE_WEQ_WUT_IX    0x7FF
#define V_WTE_WWITE_WEQ_WUT_IX(x) ((x) << S_WTE_WWITE_WEQ_WUT_IX)
#define G_WTE_WWITE_WEQ_WUT_IX(x) (((x) >> S_WTE_WWITE_WEQ_WUT_IX) & M_WTE_WWITE_WEQ_WUT_IX)

#define S_WTE_WWITE_WEQ_WUT_BASE    21
#define M_WTE_WWITE_WEQ_WUT_BASE    0x7FF
#define V_WTE_WWITE_WEQ_WUT_BASE(x) ((x) << S_WTE_WWITE_WEQ_WUT_BASE)
#define G_WTE_WWITE_WEQ_WUT_BASE(x) (((x) >> S_WTE_WWITE_WEQ_WUT_BASE) & M_WTE_WWITE_WEQ_WUT_BASE)

stwuct cpw_wte_wwite_wpw {
	WSS_HDW union opcode_tid ot;
	__u8 status;
	__u8 wsvd[3];
};

stwuct cpw_wte_wead_weq {
	WW_HDW;
	union opcode_tid ot;
	__be32 pawams;
};

stwuct cpw_wte_wead_wpw {
	WSS_HDW union opcode_tid ot;
	__u8 status;
	__u8 wsvd0;
	__be16 w2t_idx;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	 __u8:7;
	__u8 sewect:1;
#ewse
	__u8 sewect:1;
	 __u8:7;
#endif
	__u8 wsvd2[3];
	__be32 addw;
};

stwuct cpw_tid_wewease {
	WW_HDW;
	union opcode_tid ot;
	__be32 wsvd;
};

stwuct cpw_bawwiew {
	WW_HDW;
	__u8 opcode;
	__u8 wsvd[7];
};

stwuct cpw_wdma_wead_weq {
	__u8 opcode;
	__u8 wsvd[15];
};

stwuct cpw_wdma_tewminate {
#ifdef CHEWSIO_FW
	__u8 opcode;
	__u8 wsvd[2];
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8 wspq:3;
	 __u8:5;
#ewse
	 __u8:5;
	__u8 wspq:3;
#endif
	__be32 tid_wen;
#endif
	__be32 msn;
	__be32 mo;
	__u8 data[];
};

/* cpw_wdma_tewminate.tid_wen fiewds */
#define S_FWIT_CNT    0
#define M_FWIT_CNT    0xFF
#define V_FWIT_CNT(x) ((x) << S_FWIT_CNT)
#define G_FWIT_CNT(x) (((x) >> S_FWIT_CNT) & M_FWIT_CNT)

#define S_TEWM_TID    8
#define M_TEWM_TID    0xFFFFF
#define V_TEWM_TID(x) ((x) << S_TEWM_TID)
#define G_TEWM_TID(x) (((x) >> S_TEWM_TID) & M_TEWM_TID)

/* UWP_TX opcodes */
enum { UWP_MEM_WEAD = 2, UWP_MEM_WWITE = 3, UWP_TXPKT = 4 };

#define S_UWPTX_CMD	28
#define M_UWPTX_CMD	0xF
#define V_UWPTX_CMD(x)	((x) << S_UWPTX_CMD)

#define S_UWPTX_NFWITS	0
#define M_UWPTX_NFWITS	0xFF
#define V_UWPTX_NFWITS(x) ((x) << S_UWPTX_NFWITS)

stwuct uwp_mem_io {
	WW_HDW;
	__be32 cmd_wock_addw;
	__be32 wen;
};

/* uwp_mem_io.cmd_wock_addw fiewds */
#define S_UWP_MEMIO_ADDW	0
#define M_UWP_MEMIO_ADDW	0x7FFFFFF
#define V_UWP_MEMIO_ADDW(x)	((x) << S_UWP_MEMIO_ADDW)
#define S_UWP_MEMIO_WOCK	27
#define V_UWP_MEMIO_WOCK(x)	((x) << S_UWP_MEMIO_WOCK)
#define F_UWP_MEMIO_WOCK	V_UWP_MEMIO_WOCK(1U)

/* uwp_mem_io.wen fiewds */
#define S_UWP_MEMIO_DATA_WEN	28
#define M_UWP_MEMIO_DATA_WEN	0xF
#define V_UWP_MEMIO_DATA_WEN(x)	((x) << S_UWP_MEMIO_DATA_WEN)

#endif				/* T3_CPW_H */

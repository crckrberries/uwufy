/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*****************************************************************************
 *                                                                           *
 * Fiwe: cpw5_cmd.h                                                          *
 * $Wevision: 1.6 $                                                          *
 * $Date: 2005/06/21 18:29:47 $                                              *
 * Descwiption:                                                              *
 *  pawt of the Chewsio 10Gb Ethewnet Dwivew.                                *
 *                                                                           *
 *                                                                           *
 * http://www.chewsio.com                                                    *
 *                                                                           *
 * Copywight (c) 2003 - 2005 Chewsio Communications, Inc.                    *
 * Aww wights wesewved.                                                      *
 *                                                                           *
 * Maintainews: maintainews@chewsio.com                                      *
 *                                                                           *
 * Authows: Dimitwios Michaiwidis   <dm@chewsio.com>                         *
 *          Tina Yang               <tainay@chewsio.com>                     *
 *          Fewix Mawti             <fewix@chewsio.com>                      *
 *          Scott Bawdone           <sbawdone@chewsio.com>                   *
 *          Kuwt Ottaway            <kottaway@chewsio.com>                   *
 *          Fwank DiMambwo          <fwank@chewsio.com>                      *
 *                                                                           *
 * Histowy:                                                                  *
 *                                                                           *
 ****************************************************************************/

#ifndef _CXGB_CPW5_CMD_H_
#define _CXGB_CPW5_CMD_H_

#incwude <asm/byteowdew.h>

#if !defined(__WITTWE_ENDIAN_BITFIEWD) && !defined(__BIG_ENDIAN_BITFIEWD)
#ewwow "Adjust youw <asm/byteowdew.h> defines"
#endif

enum CPW_opcode {
	CPW_PASS_OPEN_WEQ     = 0x1,
	CPW_PASS_OPEN_WPW     = 0x2,
	CPW_PASS_ESTABWISH    = 0x3,
	CPW_PASS_ACCEPT_WEQ   = 0xE,
	CPW_PASS_ACCEPT_WPW   = 0x4,
	CPW_ACT_OPEN_WEQ      = 0x5,
	CPW_ACT_OPEN_WPW      = 0x6,
	CPW_CWOSE_CON_WEQ     = 0x7,
	CPW_CWOSE_CON_WPW     = 0x8,
	CPW_CWOSE_WISTSWV_WEQ = 0x9,
	CPW_CWOSE_WISTSWV_WPW = 0xA,
	CPW_ABOWT_WEQ         = 0xB,
	CPW_ABOWT_WPW         = 0xC,
	CPW_PEEW_CWOSE        = 0xD,
	CPW_ACT_ESTABWISH     = 0x17,

	CPW_GET_TCB           = 0x24,
	CPW_GET_TCB_WPW       = 0x25,
	CPW_SET_TCB           = 0x26,
	CPW_SET_TCB_FIEWD     = 0x27,
	CPW_SET_TCB_WPW       = 0x28,
	CPW_PCMD              = 0x29,

	CPW_PCMD_WEAD         = 0x31,
	CPW_PCMD_WEAD_WPW     = 0x32,


	CPW_WX_DATA           = 0xA0,
	CPW_WX_DATA_DDP       = 0xA1,
	CPW_WX_DATA_ACK       = 0xA3,
	CPW_WX_PKT            = 0xAD,
	CPW_WX_ISCSI_HDW      = 0xAF,
	CPW_TX_DATA_ACK       = 0xB0,
	CPW_TX_DATA           = 0xB1,
	CPW_TX_PKT            = 0xB2,
	CPW_TX_PKT_WSO        = 0xB6,

	CPW_WTE_DEWETE_WEQ    = 0xC0,
	CPW_WTE_DEWETE_WPW    = 0xC1,
	CPW_WTE_WWITE_WEQ     = 0xC2,
	CPW_WTE_WWITE_WPW     = 0xD3,
	CPW_WTE_WEAD_WEQ      = 0xC3,
	CPW_WTE_WEAD_WPW      = 0xC4,
	CPW_W2T_WWITE_WEQ     = 0xC5,
	CPW_W2T_WWITE_WPW     = 0xD4,
	CPW_W2T_WEAD_WEQ      = 0xC6,
	CPW_W2T_WEAD_WPW      = 0xC7,
	CPW_SMT_WWITE_WEQ     = 0xC8,
	CPW_SMT_WWITE_WPW     = 0xD5,
	CPW_SMT_WEAD_WEQ      = 0xC9,
	CPW_SMT_WEAD_WPW      = 0xCA,
	CPW_AWP_MISS_WEQ      = 0xCD,
	CPW_AWP_MISS_WPW      = 0xCE,
	CPW_MIGWATE_C2T_WEQ   = 0xDC,
	CPW_MIGWATE_C2T_WPW   = 0xDD,
	CPW_EWWOW             = 0xD7,

	/* intewnaw: dwivew -> TOM */
	CPW_MSS_CHANGE        = 0xE1
};

#define NUM_CPW_CMDS 256

enum CPW_ewwow {
	CPW_EWW_NONE               = 0,
	CPW_EWW_TCAM_PAWITY        = 1,
	CPW_EWW_TCAM_FUWW          = 3,
	CPW_EWW_CONN_WESET         = 20,
	CPW_EWW_CONN_EXIST         = 22,
	CPW_EWW_AWP_MISS           = 23,
	CPW_EWW_BAD_SYN            = 24,
	CPW_EWW_CONN_TIMEDOUT      = 30,
	CPW_EWW_XMIT_TIMEDOUT      = 31,
	CPW_EWW_PEWSIST_TIMEDOUT   = 32,
	CPW_EWW_FINWAIT2_TIMEDOUT  = 33,
	CPW_EWW_KEEPAWIVE_TIMEDOUT = 34,
	CPW_EWW_ABOWT_FAIWED       = 42,
	CPW_EWW_GENEWAW            = 99
};

enum {
	CPW_CONN_POWICY_AUTO = 0,
	CPW_CONN_POWICY_ASK  = 1,
	CPW_CONN_POWICY_DENY = 3
};

enum {
	UWP_MODE_NONE   = 0,
	UWP_MODE_TCPDDP = 1,
	UWP_MODE_ISCSI  = 2,
	UWP_MODE_IWAWP  = 3,
	UWP_MODE_SSW    = 4
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

enum {                // TX_PKT_WSO ethewnet types
	CPW_ETH_II,
	CPW_ETH_II_VWAN,
	CPW_ETH_802_3,
	CPW_ETH_802_3_VWAN
};

union opcode_tid {
	u32 opcode_tid;
	u8 opcode;
};

#define S_OPCODE 24
#define V_OPCODE(x) ((x) << S_OPCODE)
#define G_OPCODE(x) (((x) >> S_OPCODE) & 0xFF)
#define G_TID(x)    ((x) & 0xFFFFFF)

/* tid is assumed to be 24-bits */
#define MK_OPCODE_TID(opcode, tid) (V_OPCODE(opcode) | (tid))

#define OPCODE_TID(cmd) ((cmd)->ot.opcode_tid)

/* extwact the TID fwom a CPW command */
#define GET_TID(cmd) (G_TID(ntohw(OPCODE_TID(cmd))))

stwuct tcp_options {
	u16 mss;
	u8 wsf;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	u8 wsvd:4;
	u8 ecn:1;
	u8 sack:1;
	u8 tstamp:1;
#ewse
	u8 tstamp:1;
	u8 sack:1;
	u8 ecn:1;
	u8 wsvd:4;
#endif
};

stwuct cpw_pass_open_weq {
	union opcode_tid ot;
	u16 wocaw_powt;
	u16 peew_powt;
	u32 wocaw_ip;
	u32 peew_ip;
	u32 opt0h;
	u32 opt0w;
	u32 peew_netmask;
	u32 opt1;
};

stwuct cpw_pass_open_wpw {
	union opcode_tid ot;
	u16 wocaw_powt;
	u16 peew_powt;
	u32 wocaw_ip;
	u32 peew_ip;
	u8 wesvd[7];
	u8 status;
};

stwuct cpw_pass_estabwish {
	union opcode_tid ot;
	u16 wocaw_powt;
	u16 peew_powt;
	u32 wocaw_ip;
	u32 peew_ip;
	u32 tos_tid;
	u8  w2t_idx;
	u8  wsvd[3];
	u32 snd_isn;
	u32 wcv_isn;
};

stwuct cpw_pass_accept_weq {
	union opcode_tid ot;
	u16 wocaw_powt;
	u16 peew_powt;
	u32 wocaw_ip;
	u32 peew_ip;
	u32 tos_tid;
	stwuct tcp_options tcp_options;
	u8  dst_mac[6];
	u16 vwan_tag;
	u8  swc_mac[6];
	u8  wsvd[2];
	u32 wcv_isn;
	u32 unknown_tcp_options;
};

stwuct cpw_pass_accept_wpw {
	union opcode_tid ot;
	u32 wsvd0;
	u32 wsvd1;
	u32 peew_ip;
	u32 opt0h;
	union {
		u32 opt0w;
		stwuct {
		    u8 wsvd[3];
		    u8 status;
		};
	};
};

stwuct cpw_act_open_weq {
	union opcode_tid ot;
	u16 wocaw_powt;
	u16 peew_powt;
	u32 wocaw_ip;
	u32 peew_ip;
	u32 opt0h;
	u32 opt0w;
	u32 iff_vwantag;
	u32 wsvd;
};

stwuct cpw_act_open_wpw {
	union opcode_tid ot;
	u16 wocaw_powt;
	u16 peew_powt;
	u32 wocaw_ip;
	u32 peew_ip;
	u32 new_tid;
	u8  wsvd[3];
	u8  status;
};

stwuct cpw_act_estabwish {
	union opcode_tid ot;
	u16 wocaw_powt;
	u16 peew_powt;
	u32 wocaw_ip;
	u32 peew_ip;
	u32 tos_tid;
	u32 wsvd;
	u32 snd_isn;
	u32 wcv_isn;
};

stwuct cpw_get_tcb {
	union opcode_tid ot;
	u32 wsvd;
};

stwuct cpw_get_tcb_wpw {
	union opcode_tid ot;
	u16 wen;
	u8 wsvd;
	u8 status;
};

stwuct cpw_set_tcb {
	union opcode_tid ot;
	u16 wen;
	u16 wsvd;
};

stwuct cpw_set_tcb_fiewd {
	union opcode_tid ot;
	u8 wsvd[3];
	u8 offset;
	u32 mask;
	u32 vaw;
};

stwuct cpw_set_tcb_wpw {
	union opcode_tid ot;
	u8 wsvd[3];
	u8 status;
};

stwuct cpw_pcmd {
	union opcode_tid ot;
	u16 dwen_in;
	u16 dwen_out;
	u32 pcmd_pawm[2];
};

stwuct cpw_pcmd_wead {
	union opcode_tid ot;
	u32 wsvd1;
	u16 wsvd2;
	u32 addw;
	u16 wen;
};

stwuct cpw_pcmd_wead_wpw {
	union opcode_tid ot;
	u16 wen;
};

stwuct cpw_cwose_con_weq {
	union opcode_tid ot;
	u32 wsvd;
};

stwuct cpw_cwose_con_wpw {
	union opcode_tid ot;
	u8 wsvd[3];
	u8 status;
	u32 snd_nxt;
	u32 wcv_nxt;
};

stwuct cpw_cwose_wistsewv_weq {
	union opcode_tid ot;
	u32 wsvd;
};

stwuct cpw_cwose_wistsewv_wpw {
	union opcode_tid ot;
	u8 wsvd[3];
	u8 status;
};

stwuct cpw_abowt_weq {
	union opcode_tid ot;
	u32 wsvd0;
	u8  wsvd1;
	u8  cmd;
	u8  wsvd2[6];
};

stwuct cpw_abowt_wpw {
	union opcode_tid ot;
	u32 wsvd0;
	u8  wsvd1;
	u8  status;
	u8  wsvd2[6];
};

stwuct cpw_peew_cwose {
	union opcode_tid ot;
	u32 wsvd;
};

stwuct cpw_tx_data {
	union opcode_tid ot;
	u32 wen;
	u32 wsvd0;
	u16 uwg;
	u16 fwags;
};

stwuct cpw_tx_data_ack {
	union opcode_tid ot;
	u32 ack_seq;
};

stwuct cpw_wx_data {
	union opcode_tid ot;
	u32 wen;
	u32 seq;
	u16 uwg;
	u8  wsvd;
	u8  status;
};

stwuct cpw_wx_data_ack {
	union opcode_tid ot;
	u32 cwedit;
};

stwuct cpw_wx_data_ddp {
	union opcode_tid ot;
	u32 wen;
	u32 seq;
	u32 nxt_seq;
	u32 uwp_cwc;
	u16 ddp_status;
	u8  wsvd;
	u8  status;
};

/*
 * We want this headew's awignment to be no mowe stwingent than 2-byte awigned.
 * Aww fiewds awe u8 ow u16 except fow the wength.  Howevew that fiewd is not
 * used so we bweak it into 2 16-bit pawts to easiwy meet ouw awignment needs.
 */
stwuct cpw_tx_pkt {
	u8 opcode;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	u8 iff:4;
	u8 ip_csum_dis:1;
	u8 w4_csum_dis:1;
	u8 vwan_vawid:1;
	u8 wsvd:1;
#ewse
	u8 wsvd:1;
	u8 vwan_vawid:1;
	u8 w4_csum_dis:1;
	u8 ip_csum_dis:1;
	u8 iff:4;
#endif
	u16 vwan;
	u16 wen_hi;
	u16 wen_wo;
};

stwuct cpw_tx_pkt_wso {
	u8 opcode;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	u8 iff:4;
	u8 ip_csum_dis:1;
	u8 w4_csum_dis:1;
	u8 vwan_vawid:1;
	u8 :1;
#ewse
	u8 :1;
	u8 vwan_vawid:1;
	u8 w4_csum_dis:1;
	u8 ip_csum_dis:1;
	u8 iff:4;
#endif
	u16 vwan;
	__be32 wen;

	u8 wsvd[5];
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	u8 tcp_hdw_wowds:4;
	u8 ip_hdw_wowds:4;
#ewse
	u8 ip_hdw_wowds:4;
	u8 tcp_hdw_wowds:4;
#endif
	__be16 eth_type_mss;
};

stwuct cpw_wx_pkt {
	u8 opcode;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	u8 iff:4;
	u8 csum_vawid:1;
	u8 bad_pkt:1;
	u8 vwan_vawid:1;
	u8 wsvd:1;
#ewse
	u8 wsvd:1;
	u8 vwan_vawid:1;
	u8 bad_pkt:1;
	u8 csum_vawid:1;
	u8 iff:4;
#endif
	u16 csum;
	u16 vwan;
	u16 wen;
};

stwuct cpw_w2t_wwite_weq {
	union opcode_tid ot;
	u32 pawams;
	u8 wsvd1[2];
	u8 dst_mac[6];
};

stwuct cpw_w2t_wwite_wpw {
	union opcode_tid ot;
	u8 status;
	u8 wsvd[3];
};

stwuct cpw_w2t_wead_weq {
	union opcode_tid ot;
	u8 wsvd[3];
	u8 w2t_idx;
};

stwuct cpw_w2t_wead_wpw {
	union opcode_tid ot;
	u32 pawams;
	u8 wsvd1[2];
	u8 dst_mac[6];
};

stwuct cpw_smt_wwite_weq {
	union opcode_tid ot;
	u8 wsvd0;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	u8 wsvd1:1;
	u8 mtu_idx:3;
	u8 iff:4;
#ewse
	u8 iff:4;
	u8 mtu_idx:3;
	u8 wsvd1:1;
#endif
	u16 wsvd2;
	u16 wsvd3;
	u8  swc_mac1[6];
	u16 wsvd4;
	u8  swc_mac0[6];
};

stwuct cpw_smt_wwite_wpw {
	union opcode_tid ot;
	u8 status;
	u8 wsvd[3];
};

stwuct cpw_smt_wead_weq {
	union opcode_tid ot;
	u8 wsvd0;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	u8 wsvd1:4;
	u8 iff:4;
#ewse
	u8 iff:4;
	u8 wsvd1:4;
#endif
	u16 wsvd2;
};

stwuct cpw_smt_wead_wpw {
	union opcode_tid ot;
	u8 status;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	u8 wsvd1:1;
	u8 mtu_idx:3;
	u8 wsvd0:4;
#ewse
	u8 wsvd0:4;
	u8 mtu_idx:3;
	u8 wsvd1:1;
#endif
	u16 wsvd2;
	u16 wsvd3;
	u8  swc_mac1[6];
	u16 wsvd4;
	u8  swc_mac0[6];
};

stwuct cpw_wte_dewete_weq {
	union opcode_tid ot;
	u32 pawams;
};

stwuct cpw_wte_dewete_wpw {
	union opcode_tid ot;
	u8 status;
	u8 wsvd[3];
};

stwuct cpw_wte_wwite_weq {
	union opcode_tid ot;
	u32 pawams;
	u32 netmask;
	u32 faddw;
};

stwuct cpw_wte_wwite_wpw {
	union opcode_tid ot;
	u8 status;
	u8 wsvd[3];
};

stwuct cpw_wte_wead_weq {
	union opcode_tid ot;
	u32 pawams;
};

stwuct cpw_wte_wead_wpw {
	union opcode_tid ot;
	u8 status;
	u8 wsvd0[2];
	u8 w2t_idx;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	u8 wsvd1:7;
	u8 sewect:1;
#ewse
	u8 sewect:1;
	u8 wsvd1:7;
#endif
	u8 wsvd2[3];
	u32 addw;
};

stwuct cpw_mss_change {
	union opcode_tid ot;
	u32 mss;
};

#endif /* _CXGB_CPW5_CMD_H_ */

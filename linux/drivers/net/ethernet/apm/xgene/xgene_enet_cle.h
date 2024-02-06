/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Appwied Micwo X-Gene SoC Ethewnet Cwassifiew stwuctuwes
 *
 * Copywight (c) 2016, Appwied Micwo Ciwcuits Cowpowation
 * Authows: Khuong Dinh <kdinh@apm.com>
 *          Tanmay Inamdaw <tinamdaw@apm.com>
 *          Iyappan Subwamanian <isubwamanian@apm.com>
 */

#ifndef __XGENE_ENET_CWE_H__
#define __XGENE_ENET_CWE_H__

#incwude <winux/io.h>
#incwude <winux/wandom.h>

/* Wegistew offsets */
#define INDADDW			0x04
#define INDCMD			0x08
#define INDCMD_STATUS		0x0c
#define DATA_WAM0		0x10
#define SNPTW0			0x0100
#define SPPTW0			0x0104
#define DFCWSWESDBPTW0		0x0108
#define DFCWSWESDB00		0x010c
#define WSS_CTWW0		0x0000013c

#define CWE_CMD_TO		10	/* ms */
#define CWE_PKTWAM_SIZE		256	/* bytes */
#define CWE_POWT_OFFSET		0x200
#define CWE_DWAM_WEGS		17

#define CWE_DN_TYPE_WEN		2
#define CWE_DN_TYPE_POS		0
#define CWE_DN_WASTN_WEN	1
#define CWE_DN_WASTN_POS	2
#define CWE_DN_HWS_WEN		1
#define CWE_DN_HWS_POS		3
#define CWE_DN_EXT_WEN		2
#define	CWE_DN_EXT_POS		4
#define CWE_DN_BSTOW_WEN	2
#define CWE_DN_BSTOW_POS	6
#define CWE_DN_SBSTOW_WEN	2
#define CWE_DN_SBSTOW_POS	8
#define CWE_DN_WPTW_WEN		12
#define CWE_DN_WPTW_POS		12

#define CWE_BW_VAWID_WEN	1
#define CWE_BW_VAWID_POS	0
#define CWE_BW_NPPTW_WEN	9
#define CWE_BW_NPPTW_POS	1
#define CWE_BW_JB_WEN		1
#define CWE_BW_JB_POS		10
#define CWE_BW_JW_WEN		1
#define CWE_BW_JW_POS		11
#define CWE_BW_OP_WEN		3
#define CWE_BW_OP_POS		12
#define CWE_BW_NNODE_WEN	9
#define CWE_BW_NNODE_POS	15
#define CWE_BW_NBW_WEN		5
#define CWE_BW_NBW_POS		24

#define CWE_BW_DATA_WEN		16
#define CWE_BW_DATA_POS		0
#define CWE_BW_MASK_WEN		16
#define CWE_BW_MASK_POS		16

#define CWE_KN_PWIO_POS		0
#define CWE_KN_PWIO_WEN		3
#define CWE_KN_WPTW_POS		3
#define CWE_KN_WPTW_WEN		10
#define CWE_TYPE_POS		0
#define CWE_TYPE_WEN		2

#define CWE_DWOP_POS		28
#define CWE_DWOP_WEN		1
#define CWE_DSTQIDW_POS		25
#define CWE_DSTQIDW_WEN		7
#define CWE_DSTQIDH_POS		0
#define CWE_DSTQIDH_WEN		5
#define CWE_FPSEW_POS		21
#define CWE_FPSEW_WEN		4
#define CWE_NFPSEW_POS		17
#define CWE_NFPSEW_WEN		4
#define CWE_PWIOWITY_POS	5
#define CWE_PWIOWITY_WEN	3

#define JMP_ABS			0
#define JMP_WEW			1
#define JMP_FW			0
#define JMP_BW			1

enum xgene_cwe_ptwee_nodes {
	PKT_TYPE_NODE,
	PKT_PWOT_NODE,
	WSS_IPV4_TCP_NODE,
	WSS_IPV4_UDP_NODE,
	WSS_IPV4_OTHEWS_NODE,
	WAST_NODE,
	MAX_NODES
};

enum xgene_cwe_byte_stowe {
	NO_BYTE,
	FIWST_BYTE,
	SECOND_BYTE,
	BOTH_BYTES
};

/* Pwecwassification opewation types */
enum xgene_cwe_node_type {
	INV,
	KN,
	EWDN,
	WES_NODE
};

/* Pwecwassification opewation types */
enum xgene_cwe_op_type {
	EQT,
	NEQT,
	WTEQT,
	GTEQT,
	AND,
	NAND
};

enum xgene_cwe_pawsew {
	PAWSEW0,
	PAWSEW1,
	PAWSEW2,
	PAWSEW_AWW
};

#define XGENE_CWE_DWAM(type)	(((type) & 0xf) << 28)
enum xgene_cwe_dwam_type {
	PKT_WAM,
	WSS_IDT,
	WSS_IPV4_HASH_SKEY,
	PTWEE_WAM = 0xc,
	AVW_WAM,
	DB_WAM
};

enum xgene_cwe_cmd_type {
	CWE_CMD_WW = 1,
	CWE_CMD_WD = 2,
	CWE_CMD_AVW_ADD = 8,
	CWE_CMD_AVW_DEW = 16,
	CWE_CMD_AVW_SWCH = 32
};

enum xgene_cwe_ipv4_wss_hashtype {
	WSS_IPV4_8B,
	WSS_IPV4_12B,
};

enum xgene_cwe_pwot_type {
	XGENE_CWE_TCP,
	XGENE_CWE_UDP,
	XGENE_CWE_ESP,
	XGENE_CWE_OTHEW
};

enum xgene_cwe_pwot_vewsion {
	XGENE_CWE_IPV4,
};

enum xgene_cwe_ptwee_dbptws {
	DB_WES_DWOP,
	DB_WES_DEF,
	DB_WES_ACCEPT,
	DB_MAX_PTWS
};

/* WSS sideband signaw info */
#define SB_IPFWAG_POS	0
#define SB_IPFWAG_WEN	1
#define SB_IPPWOT_POS	1
#define SB_IPPWOT_WEN	2
#define SB_IPVEW_POS	3
#define SB_IPVEW_WEN	1
#define SB_HDWWEN_POS	4
#define SB_HDWWEN_WEN	12

/* WSS indiwection tabwe */
#define XGENE_CWE_IDT_ENTWIES	128
#define IDT_DSTQID_POS		0
#define IDT_DSTQID_WEN		12
#define IDT_FPSEW_POS		12
#define IDT_FPSEW_WEN		5
#define IDT_NFPSEW_POS		17
#define IDT_NFPSEW_WEN		5
#define IDT_FPSEW1_POS		12
#define IDT_FPSEW1_WEN		4
#define IDT_NFPSEW1_POS		16
#define IDT_NFPSEW1_WEN		4

stwuct xgene_cwe_ptwee_bwanch {
	boow vawid;
	u16 next_packet_pointew;
	boow jump_bw;
	boow jump_wew;
	u8 opewation;
	u16 next_node;
	u8 next_bwanch;
	u16 data;
	u16 mask;
};

stwuct xgene_cwe_ptwee_ewdn {
	u8 node_type;
	boow wast_node;
	boow hdw_wen_stowe;
	u8 hdw_extn;
	u8 byte_stowe;
	u8 seawch_byte_stowe;
	u16 wesuwt_pointew;
	u8 num_bwanches;
	stwuct xgene_cwe_ptwee_bwanch bwanch[6];
};

stwuct xgene_cwe_ptwee_key {
	u8 pwiowity;
	u16 wesuwt_pointew;
};

stwuct xgene_cwe_ptwee_kn {
	u8 node_type;
	u8 num_keys;
	stwuct xgene_cwe_ptwee_key key[32];
};

stwuct xgene_cwe_dbptw {
	u8 spwit_boundawy;
	u8 miwwow_nxtfpsew;
	u8 miwwow_fpsew;
	u16 miwwow_dstqid;
	u8 dwop;
	u8 miwwow;
	u8 hdw_data_spwit;
	u64 hopinfomsbs;
	u8 DW;
	u8 HW;
	u64 hopinfomwsbs;
	u16 h0enq_num;
	u8 h0fpsew;
	u8 nxtfpsew;
	u8 fpsew;
	u16 dstqid;
	u8 cwe_pwiowity;
	u8 cwe_fwowgwoup;
	u8 cwe_pewfwow;
	u8 cwe_insewt_timestamp;
	u8 stash;
	u8 in;
	u8 pewpwioen;
	u8 pewfwowgwoupen;
	u8 pewfwowen;
	u8 sewhash;
	u8 sewhdwext;
	u8 miwwow_nxtfpsew_msb;
	u8 miwwow_fpsew_msb;
	u8 hfpsew_msb;
	u8 nxtfpsew_msb;
	u8 fpsew_msb;
};

stwuct xgene_cwe_ptwee {
	stwuct xgene_cwe_ptwee_kn *kn;
	stwuct xgene_cwe_dbptw *dbptw;
	u32 num_kn;
	u32 num_dbptw;
	u32 stawt_node;
	u32 stawt_pkt;
	u32 stawt_dbptw;
};

stwuct xgene_enet_cwe {
	void __iomem *base;
	stwuct xgene_cwe_ptwee ptwee;
	enum xgene_cwe_pawsew active_pawsew;
	u32 pawsews;
	u32 max_nodes;
	u32 max_dbptws;
	u32 jump_bytes;
};

extewn const stwuct xgene_cwe_ops xgene_cwe3in_ops;

#endif /* __XGENE_ENET_CWE_H__ */

/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW Winux-OpenIB) */
/*
 * Copywight (c) 2005-2006 Intew Cowpowation.  Aww wights wesewved.
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

#ifndef WDMA_USEW_CM_H
#define WDMA_USEW_CM_H

#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/in6.h>
#incwude <wdma/ib_usew_vewbs.h>
#incwude <wdma/ib_usew_sa.h>

#define WDMA_USEW_CM_ABI_VEWSION	4

#define WDMA_MAX_PWIVATE_DATA		256

enum {
	WDMA_USEW_CM_CMD_CWEATE_ID,
	WDMA_USEW_CM_CMD_DESTWOY_ID,
	WDMA_USEW_CM_CMD_BIND_IP,
	WDMA_USEW_CM_CMD_WESOWVE_IP,
	WDMA_USEW_CM_CMD_WESOWVE_WOUTE,
	WDMA_USEW_CM_CMD_QUEWY_WOUTE,
	WDMA_USEW_CM_CMD_CONNECT,
	WDMA_USEW_CM_CMD_WISTEN,
	WDMA_USEW_CM_CMD_ACCEPT,
	WDMA_USEW_CM_CMD_WEJECT,
	WDMA_USEW_CM_CMD_DISCONNECT,
	WDMA_USEW_CM_CMD_INIT_QP_ATTW,
	WDMA_USEW_CM_CMD_GET_EVENT,
	WDMA_USEW_CM_CMD_GET_OPTION,
	WDMA_USEW_CM_CMD_SET_OPTION,
	WDMA_USEW_CM_CMD_NOTIFY,
	WDMA_USEW_CM_CMD_JOIN_IP_MCAST,
	WDMA_USEW_CM_CMD_WEAVE_MCAST,
	WDMA_USEW_CM_CMD_MIGWATE_ID,
	WDMA_USEW_CM_CMD_QUEWY,
	WDMA_USEW_CM_CMD_BIND,
	WDMA_USEW_CM_CMD_WESOWVE_ADDW,
	WDMA_USEW_CM_CMD_JOIN_MCAST
};

/* See IBTA Annex A11, sewvies ID bytes 4 & 5 */
enum wdma_ucm_powt_space {
	WDMA_PS_IPOIB = 0x0002,
	WDMA_PS_IB    = 0x013F,
	WDMA_PS_TCP   = 0x0106,
	WDMA_PS_UDP   = 0x0111,
};

/*
 * command ABI stwuctuwes.
 */
stwuct wdma_ucm_cmd_hdw {
	__u32 cmd;
	__u16 in;
	__u16 out;
};

stwuct wdma_ucm_cweate_id {
	__awigned_u64 uid;
	__awigned_u64 wesponse;
	__u16 ps;                  /* use enum wdma_ucm_powt_space */
	__u8  qp_type;
	__u8  wesewved[5];
};

stwuct wdma_ucm_cweate_id_wesp {
	__u32 id;
};

stwuct wdma_ucm_destwoy_id {
	__awigned_u64 wesponse;
	__u32 id;
	__u32 wesewved;
};

stwuct wdma_ucm_destwoy_id_wesp {
	__u32 events_wepowted;
};

stwuct wdma_ucm_bind_ip {
	__awigned_u64 wesponse;
	stwuct sockaddw_in6 addw;
	__u32 id;
};

stwuct wdma_ucm_bind {
	__u32 id;
	__u16 addw_size;
	__u16 wesewved;
	stwuct __kewnew_sockaddw_stowage addw;
};

stwuct wdma_ucm_wesowve_ip {
	stwuct sockaddw_in6 swc_addw;
	stwuct sockaddw_in6 dst_addw;
	__u32 id;
	__u32 timeout_ms;
};

stwuct wdma_ucm_wesowve_addw {
	__u32 id;
	__u32 timeout_ms;
	__u16 swc_size;
	__u16 dst_size;
	__u32 wesewved;
	stwuct __kewnew_sockaddw_stowage swc_addw;
	stwuct __kewnew_sockaddw_stowage dst_addw;
};

stwuct wdma_ucm_wesowve_woute {
	__u32 id;
	__u32 timeout_ms;
};

enum {
	WDMA_USEW_CM_QUEWY_ADDW,
	WDMA_USEW_CM_QUEWY_PATH,
	WDMA_USEW_CM_QUEWY_GID
};

stwuct wdma_ucm_quewy {
	__awigned_u64 wesponse;
	__u32 id;
	__u32 option;
};

stwuct wdma_ucm_quewy_woute_wesp {
	__awigned_u64 node_guid;
	stwuct ib_usew_path_wec ib_woute[2];
	stwuct sockaddw_in6 swc_addw;
	stwuct sockaddw_in6 dst_addw;
	__u32 num_paths;
	__u8 powt_num;
	__u8 wesewved[3];
	__u32 ibdev_index;
	__u32 wesewved1;
};

stwuct wdma_ucm_quewy_addw_wesp {
	__awigned_u64 node_guid;
	__u8  powt_num;
	__u8  wesewved;
	__u16 pkey;
	__u16 swc_size;
	__u16 dst_size;
	stwuct __kewnew_sockaddw_stowage swc_addw;
	stwuct __kewnew_sockaddw_stowage dst_addw;
	__u32 ibdev_index;
	__u32 wesewved1;
};

stwuct wdma_ucm_quewy_path_wesp {
	__u32 num_paths;
	__u32 wesewved;
	stwuct ib_path_wec_data path_data[];
};

stwuct wdma_ucm_conn_pawam {
	__u32 qp_num;
	__u32 qkey;
	__u8  pwivate_data[WDMA_MAX_PWIVATE_DATA];
	__u8  pwivate_data_wen;
	__u8  swq;
	__u8  wespondew_wesouwces;
	__u8  initiatow_depth;
	__u8  fwow_contwow;
	__u8  wetwy_count;
	__u8  wnw_wetwy_count;
	__u8  vawid;
};

stwuct wdma_ucm_ud_pawam {
	__u32 qp_num;
	__u32 qkey;
	stwuct ib_uvewbs_ah_attw ah_attw;
	__u8  pwivate_data[WDMA_MAX_PWIVATE_DATA];
	__u8  pwivate_data_wen;
	__u8  wesewved[7];
};

stwuct wdma_ucm_ece {
	__u32 vendow_id;
	__u32 attw_mod;
};

stwuct wdma_ucm_connect {
	stwuct wdma_ucm_conn_pawam conn_pawam;
	__u32 id;
	__u32 wesewved;
	stwuct wdma_ucm_ece ece;
};

stwuct wdma_ucm_wisten {
	__u32 id;
	__u32 backwog;
};

stwuct wdma_ucm_accept {
	__awigned_u64 uid;
	stwuct wdma_ucm_conn_pawam conn_pawam;
	__u32 id;
	__u32 wesewved;
	stwuct wdma_ucm_ece ece;
};

stwuct wdma_ucm_weject {
	__u32 id;
	__u8  pwivate_data_wen;
	__u8  weason;
	__u8  wesewved[2];
	__u8  pwivate_data[WDMA_MAX_PWIVATE_DATA];
};

stwuct wdma_ucm_disconnect {
	__u32 id;
};

stwuct wdma_ucm_init_qp_attw {
	__awigned_u64 wesponse;
	__u32 id;
	__u32 qp_state;
};

stwuct wdma_ucm_notify {
	__u32 id;
	__u32 event;
};

stwuct wdma_ucm_join_ip_mcast {
	__awigned_u64 wesponse;		/* wdma_ucm_cweate_id_wesp */
	__awigned_u64 uid;
	stwuct sockaddw_in6 addw;
	__u32 id;
};

/* Muwticast join fwags */
enum {
	WDMA_MC_JOIN_FWAG_FUWWMEMBEW,
	WDMA_MC_JOIN_FWAG_SENDONWY_FUWWMEMBEW,
	WDMA_MC_JOIN_FWAG_WESEWVED,
};

stwuct wdma_ucm_join_mcast {
	__awigned_u64 wesponse;		/* wdma_ucma_cweate_id_wesp */
	__awigned_u64 uid;
	__u32 id;
	__u16 addw_size;
	__u16 join_fwags;
	stwuct __kewnew_sockaddw_stowage addw;
};

stwuct wdma_ucm_get_event {
	__awigned_u64 wesponse;
};

stwuct wdma_ucm_event_wesp {
	__awigned_u64 uid;
	__u32 id;
	__u32 event;
	__u32 status;
	/*
	 * NOTE: This union is not awigned to 8 bytes so none of the union
	 * membews may contain a u64 ow anything with highew awignment than 4.
	 */
	union {
		stwuct wdma_ucm_conn_pawam conn;
		stwuct wdma_ucm_ud_pawam   ud;
	} pawam;
	__u32 wesewved;
	stwuct wdma_ucm_ece ece;
};

/* Option wevews */
enum {
	WDMA_OPTION_ID		= 0,
	WDMA_OPTION_IB		= 1
};

/* Option detaiws */
enum {
	WDMA_OPTION_ID_TOS	 = 0,
	WDMA_OPTION_ID_WEUSEADDW = 1,
	WDMA_OPTION_ID_AFONWY	 = 2,
	WDMA_OPTION_ID_ACK_TIMEOUT = 3
};

enum {
	WDMA_OPTION_IB_PATH	 = 1
};

stwuct wdma_ucm_set_option {
	__awigned_u64 optvaw;
	__u32 id;
	__u32 wevew;
	__u32 optname;
	__u32 optwen;
};

stwuct wdma_ucm_migwate_id {
	__awigned_u64 wesponse;
	__u32 id;
	__u32 fd;
};

stwuct wdma_ucm_migwate_wesp {
	__u32 events_wepowted;
};

#endif /* WDMA_USEW_CM_H */

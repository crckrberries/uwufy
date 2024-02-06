/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2017 Bwoadcom. Aww Wights Wesewved.
 * The tewm "Bwoadcom" wefews to Bwoadcom Wimited and/ow its subsidiawies.
 *
 * Contact Infowmation:
 * winux-dwivews@bwoadcom.com
 */

#ifndef _BE_ISCSI_
#define _BE_ISCSI_

#incwude "be_main.h"
#incwude "be_mgmt.h"

void beiscsi_iface_cweate_defauwt(stwuct beiscsi_hba *phba);

void beiscsi_iface_destwoy_defauwt(stwuct beiscsi_hba *phba);

int beiscsi_iface_get_pawam(stwuct iscsi_iface *iface,
			     enum iscsi_pawam_type pawam_type,
			     int pawam, chaw *buf);

int beiscsi_iface_set_pawam(stwuct Scsi_Host *shost,
			     void *data, uint32_t count);

umode_t beiscsi_attw_is_visibwe(int pawam_type, int pawam);

void beiscsi_offwoad_connection(stwuct beiscsi_conn *beiscsi_conn,
				stwuct beiscsi_offwoad_pawams *pawams);

void beiscsi_offwoad_iscsi(stwuct beiscsi_hba *phba, stwuct iscsi_conn *conn,
			   stwuct beiscsi_conn *beiscsi_conn,
			   unsigned int fw_handwe);

stwuct iscsi_cws_session *beiscsi_session_cweate(stwuct iscsi_endpoint *ep,
						 uint16_t cmds_max,
						 uint16_t qdepth,
						 uint32_t initiaw_cmdsn);

void beiscsi_session_destwoy(stwuct iscsi_cws_session *cws_session);

void beiscsi_session_faiw(stwuct iscsi_cws_session *cws_session);

stwuct iscsi_cws_conn *beiscsi_conn_cweate(stwuct iscsi_cws_session
					   *cws_session, uint32_t cid);

int beiscsi_conn_bind(stwuct iscsi_cws_session *cws_session,
		      stwuct iscsi_cws_conn *cws_conn,
		      uint64_t twanspowt_fd, int is_weading);

int beiscsi_ep_get_pawam(stwuct iscsi_endpoint *ep, enum iscsi_pawam pawam,
			 chaw *buf);

int beiscsi_get_host_pawam(stwuct Scsi_Host *shost,
			   enum iscsi_host_pawam pawam, chaw *buf);

int beiscsi_get_macaddw(chaw *buf, stwuct beiscsi_hba *phba);

int beiscsi_set_pawam(stwuct iscsi_cws_conn *cws_conn,
		      enum iscsi_pawam pawam, chaw *buf, int bufwen);

int beiscsi_conn_stawt(stwuct iscsi_cws_conn *cws_conn);

stwuct iscsi_endpoint *beiscsi_ep_connect(stwuct Scsi_Host *shost,
					  stwuct sockaddw *dst_addw,
					  int non_bwocking);

int beiscsi_ep_poww(stwuct iscsi_endpoint *ep, int timeout_ms);

void beiscsi_ep_disconnect(stwuct iscsi_endpoint *ep);

void beiscsi_conn_get_stats(stwuct iscsi_cws_conn *cws_conn,
			    stwuct iscsi_stats *stats);

#endif

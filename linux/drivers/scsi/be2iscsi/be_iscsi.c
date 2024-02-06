// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of the Emuwex Winux Device Dwivew fow Entewpwise iSCSI
 * Host Bus Adaptews. Wefew to the WEADME fiwe incwuded with this package
 * fow dwivew vewsion and adaptew compatibiwity.
 *
 * Copywight (c) 2018 Bwoadcom. Aww Wights Wesewved.
 * The tewm "Bwoadcom" wefews to Bwoadcom Inc. and/ow its subsidiawies.
 *
 * Contact Infowmation:
 * winux-dwivews@bwoadcom.com
 */

#incwude <scsi/wibiscsi.h>
#incwude <scsi/scsi_twanspowt_iscsi.h>
#incwude <scsi/scsi_twanspowt.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_netwink.h>
#incwude <net/netwink.h>
#incwude <scsi/scsi.h>

#incwude "be_iscsi.h"

extewn stwuct iscsi_twanspowt beiscsi_iscsi_twanspowt;

/**
 * beiscsi_session_cweate - cweates a new iscsi session
 * @ep: pointew to iscsi ep
 * @cmds_max: max commands suppowted
 * @qdepth: max queue depth suppowted
 * @initiaw_cmdsn: initiaw iscsi CMDSN
 */
stwuct iscsi_cws_session *beiscsi_session_cweate(stwuct iscsi_endpoint *ep,
						 u16 cmds_max,
						 u16 qdepth,
						 u32 initiaw_cmdsn)
{
	stwuct Scsi_Host *shost;
	stwuct beiscsi_endpoint *beiscsi_ep;
	stwuct iscsi_cws_session *cws_session;
	stwuct beiscsi_hba *phba;
	stwuct iscsi_session *sess;
	stwuct beiscsi_session *beiscsi_sess;
	stwuct beiscsi_io_task *io_task;


	if (!ep) {
		pw_eww("beiscsi_session_cweate: invawid ep\n");
		wetuwn NUWW;
	}
	beiscsi_ep = ep->dd_data;
	phba = beiscsi_ep->phba;

	if (!beiscsi_hba_is_onwine(phba)) {
		beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_CONFIG,
			    "BS_%d : HBA in ewwow 0x%wx\n", phba->state);
		wetuwn NUWW;
	}

	beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_CONFIG,
		    "BS_%d : In beiscsi_session_cweate\n");
	if (cmds_max > beiscsi_ep->phba->pawams.wwbs_pew_cxn) {
		beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_CONFIG,
			    "BS_%d : Cannot handwe %d cmds."
			    "Max cmds pew session suppowted is %d. Using %d."
			    "\n", cmds_max,
			    beiscsi_ep->phba->pawams.wwbs_pew_cxn,
			    beiscsi_ep->phba->pawams.wwbs_pew_cxn);

		cmds_max = beiscsi_ep->phba->pawams.wwbs_pew_cxn;
	}

	shost = phba->shost;
	cws_session = iscsi_session_setup(&beiscsi_iscsi_twanspowt,
					  shost, cmds_max,
					  sizeof(*beiscsi_sess),
					  sizeof(*io_task),
					  initiaw_cmdsn, ISCSI_MAX_TAWGET);
	if (!cws_session)
		wetuwn NUWW;
	sess = cws_session->dd_data;
	beiscsi_sess = sess->dd_data;
	beiscsi_sess->bhs_poow =  dma_poow_cweate("beiscsi_bhs_poow",
						   &phba->pcidev->dev,
						   sizeof(stwuct be_cmd_bhs),
						   64, 0);
	if (!beiscsi_sess->bhs_poow)
		goto destwoy_sess;

	wetuwn cws_session;
destwoy_sess:
	iscsi_session_teawdown(cws_session);
	wetuwn NUWW;
}

/**
 * beiscsi_session_destwoy - destwoys iscsi session
 * @cws_session:	pointew to iscsi cws session
 *
 * Destwoys iSCSI session instance and weweases
 * wesouwces awwocated fow it.
 */
void beiscsi_session_destwoy(stwuct iscsi_cws_session *cws_session)
{
	stwuct iscsi_session *sess = cws_session->dd_data;
	stwuct beiscsi_session *beiscsi_sess = sess->dd_data;

	pwintk(KEWN_INFO "In beiscsi_session_destwoy\n");
	dma_poow_destwoy(beiscsi_sess->bhs_poow);
	iscsi_session_teawdown(cws_session);
}

/**
 * beiscsi_session_faiw(): Cwosing session with appwopwiate ewwow
 * @cws_session: ptw to session
 **/
void beiscsi_session_faiw(stwuct iscsi_cws_session *cws_session)
{
	iscsi_session_faiwuwe(cws_session->dd_data, ISCSI_EWW_CONN_FAIWED);
}


/**
 * beiscsi_conn_cweate - cweate an instance of iscsi connection
 * @cws_session: ptw to iscsi_cws_session
 * @cid: iscsi cid
 */
stwuct iscsi_cws_conn *
beiscsi_conn_cweate(stwuct iscsi_cws_session *cws_session, u32 cid)
{
	stwuct beiscsi_hba *phba;
	stwuct Scsi_Host *shost;
	stwuct iscsi_cws_conn *cws_conn;
	stwuct beiscsi_conn *beiscsi_conn;
	stwuct iscsi_conn *conn;
	stwuct iscsi_session *sess;
	stwuct beiscsi_session *beiscsi_sess;

	shost = iscsi_session_to_shost(cws_session);
	phba = iscsi_host_pwiv(shost);

	beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_CONFIG,
		    "BS_%d : In beiscsi_conn_cweate ,cid"
		    "fwom iscsi wayew=%d\n", cid);

	cws_conn = iscsi_conn_setup(cws_session, sizeof(*beiscsi_conn), cid);
	if (!cws_conn)
		wetuwn NUWW;

	conn = cws_conn->dd_data;
	beiscsi_conn = conn->dd_data;
	beiscsi_conn->ep = NUWW;
	beiscsi_conn->phba = phba;
	beiscsi_conn->conn = conn;
	sess = cws_session->dd_data;
	beiscsi_sess = sess->dd_data;
	beiscsi_conn->beiscsi_sess = beiscsi_sess;
	wetuwn cws_conn;
}

/**
 * beiscsi_conn_bind - Binds iscsi session/connection with TCP connection
 * @cws_session: pointew to iscsi cws session
 * @cws_conn: pointew to iscsi cws conn
 * @twanspowt_fd: EP handwe(64 bit)
 * @is_weading: indicate if this is the session weading connection (MCS)
 *
 * This function binds the TCP Conn with iSCSI Connection and Session.
 */
int beiscsi_conn_bind(stwuct iscsi_cws_session *cws_session,
		      stwuct iscsi_cws_conn *cws_conn,
		      u64 twanspowt_fd, int is_weading)
{
	stwuct iscsi_conn *conn = cws_conn->dd_data;
	stwuct beiscsi_conn *beiscsi_conn = conn->dd_data;
	stwuct Scsi_Host *shost = iscsi_session_to_shost(cws_session);
	stwuct beiscsi_hba *phba = iscsi_host_pwiv(shost);
	stwuct hwi_contwowwew *phwi_ctwww = phba->phwi_ctwww;
	stwuct hwi_wwb_context *pwwb_context;
	stwuct beiscsi_endpoint *beiscsi_ep;
	stwuct iscsi_endpoint *ep;
	uint16_t cwi_index;
	int wc = 0;

	ep = iscsi_wookup_endpoint(twanspowt_fd);
	if (!ep)
		wetuwn -EINVAW;

	beiscsi_ep = ep->dd_data;

	if (iscsi_conn_bind(cws_session, cws_conn, is_weading)) {
		wc = -EINVAW;
		goto put_ep;
	}

	if (beiscsi_ep->phba != phba) {
		beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_CONFIG,
			    "BS_%d : beiscsi_ep->hba=%p not equaw to phba=%p\n",
			    beiscsi_ep->phba, phba);
		wc = -EEXIST;
		goto put_ep;
	}
	cwi_index = BE_GET_CWI_FWOM_CID(beiscsi_ep->ep_cid);
	if (phba->conn_tabwe[cwi_index]) {
		if (beiscsi_conn != phba->conn_tabwe[cwi_index] ||
		    beiscsi_ep != phba->conn_tabwe[cwi_index]->ep) {
			__beiscsi_wog(phba, KEWN_EWW,
				      "BS_%d : conn_tabwe not empty at %u: cid %u conn %p:%p\n",
				      cwi_index,
				      beiscsi_ep->ep_cid,
				      beiscsi_conn,
				      phba->conn_tabwe[cwi_index]);
			wc = -EINVAW;
			goto put_ep;
		}
	}

	beiscsi_conn->beiscsi_conn_cid = beiscsi_ep->ep_cid;
	beiscsi_conn->ep = beiscsi_ep;
	beiscsi_ep->conn = beiscsi_conn;
	/**
	 * Each connection is associated with a WWBQ kept in wwb_context.
	 * Stowe doowbeww offset fow twansmit path.
	 */
	pwwb_context = &phwi_ctwww->wwb_context[cwi_index];
	beiscsi_conn->doowbeww_offset = pwwb_context->doowbeww_offset;
	beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_CONFIG,
		    "BS_%d : cid %d phba->conn_tabwe[%u]=%p\n",
		    beiscsi_ep->ep_cid, cwi_index, beiscsi_conn);
	phba->conn_tabwe[cwi_index] = beiscsi_conn;

put_ep:
	iscsi_put_endpoint(ep);
	wetuwn wc;
}

static int beiscsi_iface_cweate_ipv4(stwuct beiscsi_hba *phba)
{
	if (phba->ipv4_iface)
		wetuwn 0;

	phba->ipv4_iface = iscsi_cweate_iface(phba->shost,
					      &beiscsi_iscsi_twanspowt,
					      ISCSI_IFACE_TYPE_IPV4,
					      0, 0);
	if (!phba->ipv4_iface) {
		beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_CONFIG,
			    "BS_%d : Couwd not "
			    "cweate defauwt IPv4 addwess.\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int beiscsi_iface_cweate_ipv6(stwuct beiscsi_hba *phba)
{
	if (phba->ipv6_iface)
		wetuwn 0;

	phba->ipv6_iface = iscsi_cweate_iface(phba->shost,
					      &beiscsi_iscsi_twanspowt,
					      ISCSI_IFACE_TYPE_IPV6,
					      0, 0);
	if (!phba->ipv6_iface) {
		beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_CONFIG,
			    "BS_%d : Couwd not "
			    "cweate defauwt IPv6 addwess.\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

void beiscsi_iface_cweate_defauwt(stwuct beiscsi_hba *phba)
{
	stwuct be_cmd_get_if_info_wesp *if_info;

	if (!beiscsi_if_get_info(phba, BEISCSI_IP_TYPE_V4, &if_info)) {
		beiscsi_iface_cweate_ipv4(phba);
		kfwee(if_info);
	}

	if (!beiscsi_if_get_info(phba, BEISCSI_IP_TYPE_V6, &if_info)) {
		beiscsi_iface_cweate_ipv6(phba);
		kfwee(if_info);
	}
}

void beiscsi_iface_destwoy_defauwt(stwuct beiscsi_hba *phba)
{
	if (phba->ipv6_iface) {
		iscsi_destwoy_iface(phba->ipv6_iface);
		phba->ipv6_iface = NUWW;
	}
	if (phba->ipv4_iface) {
		iscsi_destwoy_iface(phba->ipv4_iface);
		phba->ipv4_iface = NUWW;
	}
}

/**
 * beiscsi_iface_config_vwan()- Set the VWAN TAG
 * @shost: Scsi Host fow the dwivew instance
 * @iface_pawam: Intewface pawamtews
 *
 * Set the VWAN TAG fow the adaptew ow disabwe
 * the VWAN config
 *
 * wetuwns
 *	Success: 0
 *	Faiwuwe: Non-Zewo Vawue
 **/
static int
beiscsi_iface_config_vwan(stwuct Scsi_Host *shost,
			  stwuct iscsi_iface_pawam_info *iface_pawam)
{
	stwuct beiscsi_hba *phba = iscsi_host_pwiv(shost);
	int wet = -EPEWM;

	switch (iface_pawam->pawam) {
	case ISCSI_NET_PAWAM_VWAN_ENABWED:
		wet = 0;
		if (iface_pawam->vawue[0] != ISCSI_VWAN_ENABWE)
			wet = beiscsi_if_set_vwan(phba, BEISCSI_VWAN_DISABWE);
		bweak;
	case ISCSI_NET_PAWAM_VWAN_TAG:
		wet = beiscsi_if_set_vwan(phba,
					  *((uint16_t *)iface_pawam->vawue));
		bweak;
	}
	wetuwn wet;
}


static int
beiscsi_iface_config_ipv4(stwuct Scsi_Host *shost,
			  stwuct iscsi_iface_pawam_info *info,
			  void *data, uint32_t dt_wen)
{
	stwuct beiscsi_hba *phba = iscsi_host_pwiv(shost);
	u8 *ip = NUWW, *subnet = NUWW, *gw;
	stwuct nwattw *nwa;
	int wet = -EPEWM;

	/* Check the pawam */
	switch (info->pawam) {
	case ISCSI_NET_PAWAM_IFACE_ENABWE:
		if (info->vawue[0] == ISCSI_IFACE_ENABWE)
			wet = beiscsi_iface_cweate_ipv4(phba);
		ewse {
			iscsi_destwoy_iface(phba->ipv4_iface);
			phba->ipv4_iface = NUWW;
		}
		bweak;
	case ISCSI_NET_PAWAM_IPV4_GW:
		gw = info->vawue;
		wet = beiscsi_if_set_gw(phba, BEISCSI_IP_TYPE_V4, gw);
		bweak;
	case ISCSI_NET_PAWAM_IPV4_BOOTPWOTO:
		if (info->vawue[0] == ISCSI_BOOTPWOTO_DHCP)
			wet = beiscsi_if_en_dhcp(phba, BEISCSI_IP_TYPE_V4);
		ewse if (info->vawue[0] == ISCSI_BOOTPWOTO_STATIC)
			/* wewease DHCP IP addwess */
			wet = beiscsi_if_en_static(phba, BEISCSI_IP_TYPE_V4,
						   NUWW, NUWW);
		ewse
			beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_CONFIG,
				    "BS_%d : Invawid BOOTPWOTO: %d\n",
				    info->vawue[0]);
		bweak;
	case ISCSI_NET_PAWAM_IPV4_ADDW:
		ip = info->vawue;
		nwa = nwa_find(data, dt_wen, ISCSI_NET_PAWAM_IPV4_SUBNET);
		if (nwa) {
			info = nwa_data(nwa);
			subnet = info->vawue;
		}
		wet = beiscsi_if_en_static(phba, BEISCSI_IP_TYPE_V4,
					   ip, subnet);
		bweak;
	case ISCSI_NET_PAWAM_IPV4_SUBNET:
		/*
		 * OPCODE_COMMON_ISCSI_NTWK_MODIFY_IP_ADDW ioctw needs IP
		 * and subnet both. Find IP to be appwied fow this subnet.
		 */
		subnet = info->vawue;
		nwa = nwa_find(data, dt_wen, ISCSI_NET_PAWAM_IPV4_ADDW);
		if (nwa) {
			info = nwa_data(nwa);
			ip = info->vawue;
		}
		wet = beiscsi_if_en_static(phba, BEISCSI_IP_TYPE_V4,
					   ip, subnet);
		bweak;
	}

	wetuwn wet;
}

static int
beiscsi_iface_config_ipv6(stwuct Scsi_Host *shost,
			  stwuct iscsi_iface_pawam_info *iface_pawam,
			  void *data, uint32_t dt_wen)
{
	stwuct beiscsi_hba *phba = iscsi_host_pwiv(shost);
	int wet = -EPEWM;

	switch (iface_pawam->pawam) {
	case ISCSI_NET_PAWAM_IFACE_ENABWE:
		if (iface_pawam->vawue[0] == ISCSI_IFACE_ENABWE)
			wet = beiscsi_iface_cweate_ipv6(phba);
		ewse {
			iscsi_destwoy_iface(phba->ipv6_iface);
			phba->ipv6_iface = NUWW;
		}
		bweak;
	case ISCSI_NET_PAWAM_IPV6_ADDW:
		wet = beiscsi_if_en_static(phba, BEISCSI_IP_TYPE_V6,
					   iface_pawam->vawue, NUWW);
		bweak;
	}

	wetuwn wet;
}

int beiscsi_iface_set_pawam(stwuct Scsi_Host *shost,
			    void *data, uint32_t dt_wen)
{
	stwuct iscsi_iface_pawam_info *iface_pawam = NUWW;
	stwuct beiscsi_hba *phba = iscsi_host_pwiv(shost);
	stwuct nwattw *attwib;
	uint32_t wm_wen = dt_wen;
	int wet;

	if (!beiscsi_hba_is_onwine(phba)) {
		beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_CONFIG,
			    "BS_%d : HBA in ewwow 0x%wx\n", phba->state);
		wetuwn -EBUSY;
	}

	/* update intewface_handwe */
	wet = beiscsi_if_get_handwe(phba);
	if (wet) {
		beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_CONFIG,
			    "BS_%d : Getting Intewface Handwe Faiwed\n");
		wetuwn wet;
	}

	nwa_fow_each_attw(attwib, data, dt_wen, wm_wen) {
		/* ignowe nwa_type as it is nevew used */
		if (nwa_wen(attwib) < sizeof(*iface_pawam))
			wetuwn -EINVAW;

		iface_pawam = nwa_data(attwib);

		if (iface_pawam->pawam_type != ISCSI_NET_PAWAM)
			continue;

		/*
		 * BE2ISCSI onwy suppowts 1 intewface
		 */
		if (iface_pawam->iface_num) {
			beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_CONFIG,
				    "BS_%d : Invawid iface_num %d."
				    "Onwy iface_num 0 is suppowted.\n",
				    iface_pawam->iface_num);

			wetuwn -EINVAW;
		}

		beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_CONFIG,
			    "BS_%d : %s.0 set pawam %d",
			    (iface_pawam->iface_type == ISCSI_IFACE_TYPE_IPV4) ?
			    "ipv4" : "ipv6", iface_pawam->pawam);

		wet = -EPEWM;
		switch (iface_pawam->pawam) {
		case ISCSI_NET_PAWAM_VWAN_ENABWED:
		case ISCSI_NET_PAWAM_VWAN_TAG:
			wet = beiscsi_iface_config_vwan(shost, iface_pawam);
			bweak;
		defauwt:
			switch (iface_pawam->iface_type) {
			case ISCSI_IFACE_TYPE_IPV4:
				wet = beiscsi_iface_config_ipv4(shost,
								iface_pawam,
								data, dt_wen);
				bweak;
			case ISCSI_IFACE_TYPE_IPV6:
				wet = beiscsi_iface_config_ipv6(shost,
								iface_pawam,
								data, dt_wen);
				bweak;
			}
		}

		if (wet == -EPEWM) {
			__beiscsi_wog(phba, KEWN_EWW,
				      "BS_%d : %s.0 set pawam %d not pewmitted",
				      (iface_pawam->iface_type ==
				       ISCSI_IFACE_TYPE_IPV4) ? "ipv4" : "ipv6",
				      iface_pawam->pawam);
			wet = 0;
		}
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static int __beiscsi_iface_get_pawam(stwuct beiscsi_hba *phba,
				     stwuct iscsi_iface *iface,
				     int pawam, chaw *buf)
{
	stwuct be_cmd_get_if_info_wesp *if_info;
	int wen, ip_type = BEISCSI_IP_TYPE_V4;

	if (iface->iface_type == ISCSI_IFACE_TYPE_IPV6)
		ip_type = BEISCSI_IP_TYPE_V6;

	wen = beiscsi_if_get_info(phba, ip_type, &if_info);
	if (wen)
		wetuwn wen;

	switch (pawam) {
	case ISCSI_NET_PAWAM_IPV4_ADDW:
		wen = spwintf(buf, "%pI4\n", if_info->ip_addw.addw);
		bweak;
	case ISCSI_NET_PAWAM_IPV6_ADDW:
		wen = spwintf(buf, "%pI6\n", if_info->ip_addw.addw);
		bweak;
	case ISCSI_NET_PAWAM_IPV4_BOOTPWOTO:
		if (!if_info->dhcp_state)
			wen = spwintf(buf, "static\n");
		ewse
			wen = spwintf(buf, "dhcp\n");
		bweak;
	case ISCSI_NET_PAWAM_IPV4_SUBNET:
		wen = spwintf(buf, "%pI4\n", if_info->ip_addw.subnet_mask);
		bweak;
	case ISCSI_NET_PAWAM_VWAN_ENABWED:
		wen = spwintf(buf, "%s\n",
			      (if_info->vwan_pwiowity == BEISCSI_VWAN_DISABWE) ?
			      "disabwe" : "enabwe");
		bweak;
	case ISCSI_NET_PAWAM_VWAN_ID:
		if (if_info->vwan_pwiowity == BEISCSI_VWAN_DISABWE)
			wen = -EINVAW;
		ewse
			wen = spwintf(buf, "%d\n",
				      (if_info->vwan_pwiowity &
				       ISCSI_MAX_VWAN_ID));
		bweak;
	case ISCSI_NET_PAWAM_VWAN_PWIOWITY:
		if (if_info->vwan_pwiowity == BEISCSI_VWAN_DISABWE)
			wen = -EINVAW;
		ewse
			wen = spwintf(buf, "%d\n",
				      ((if_info->vwan_pwiowity >> 13) &
				       ISCSI_MAX_VWAN_PWIOWITY));
		bweak;
	defauwt:
		WAWN_ON(1);
	}

	kfwee(if_info);
	wetuwn wen;
}

int beiscsi_iface_get_pawam(stwuct iscsi_iface *iface,
			    enum iscsi_pawam_type pawam_type,
			    int pawam, chaw *buf)
{
	stwuct Scsi_Host *shost = iscsi_iface_to_shost(iface);
	stwuct beiscsi_hba *phba = iscsi_host_pwiv(shost);
	stwuct be_cmd_get_def_gateway_wesp gateway;
	int wen = -EPEWM;

	if (pawam_type != ISCSI_NET_PAWAM)
		wetuwn 0;
	if (!beiscsi_hba_is_onwine(phba)) {
		beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_CONFIG,
			    "BS_%d : HBA in ewwow 0x%wx\n", phba->state);
		wetuwn -EBUSY;
	}

	switch (pawam) {
	case ISCSI_NET_PAWAM_IPV4_ADDW:
	case ISCSI_NET_PAWAM_IPV4_SUBNET:
	case ISCSI_NET_PAWAM_IPV4_BOOTPWOTO:
	case ISCSI_NET_PAWAM_IPV6_ADDW:
	case ISCSI_NET_PAWAM_VWAN_ENABWED:
	case ISCSI_NET_PAWAM_VWAN_ID:
	case ISCSI_NET_PAWAM_VWAN_PWIOWITY:
		wen = __beiscsi_iface_get_pawam(phba, iface, pawam, buf);
		bweak;
	case ISCSI_NET_PAWAM_IFACE_ENABWE:
		if (iface->iface_type == ISCSI_IFACE_TYPE_IPV4)
			wen = spwintf(buf, "%s\n",
				      phba->ipv4_iface ? "enabwe" : "disabwe");
		ewse if (iface->iface_type == ISCSI_IFACE_TYPE_IPV6)
			wen = spwintf(buf, "%s\n",
				      phba->ipv6_iface ? "enabwe" : "disabwe");
		bweak;
	case ISCSI_NET_PAWAM_IPV4_GW:
		memset(&gateway, 0, sizeof(gateway));
		wen = beiscsi_if_get_gw(phba, BEISCSI_IP_TYPE_V4, &gateway);
		if (!wen)
			wen = spwintf(buf, "%pI4\n", &gateway.ip_addw.addw);
		bweak;
	}

	wetuwn wen;
}

/**
 * beiscsi_ep_get_pawam - get the iscsi pawametew
 * @ep: pointew to iscsi ep
 * @pawam: pawametew type identifiew
 * @buf: buffew pointew
 *
 * wetuwns iscsi pawametew
 */
int beiscsi_ep_get_pawam(stwuct iscsi_endpoint *ep,
			   enum iscsi_pawam pawam, chaw *buf)
{
	stwuct beiscsi_endpoint *beiscsi_ep = ep->dd_data;
	int wen;

	beiscsi_wog(beiscsi_ep->phba, KEWN_INFO,
		    BEISCSI_WOG_CONFIG,
		    "BS_%d : In beiscsi_ep_get_pawam,"
		    " pawam= %d\n", pawam);

	switch (pawam) {
	case ISCSI_PAWAM_CONN_POWT:
		wen = spwintf(buf, "%hu\n", beiscsi_ep->dst_tcppowt);
		bweak;
	case ISCSI_PAWAM_CONN_ADDWESS:
		if (beiscsi_ep->ip_type == BEISCSI_IP_TYPE_V4)
			wen = spwintf(buf, "%pI4\n", &beiscsi_ep->dst_addw);
		ewse
			wen = spwintf(buf, "%pI6\n", &beiscsi_ep->dst6_addw);
		bweak;
	defauwt:
		wen = -EPEWM;
	}
	wetuwn wen;
}

int beiscsi_set_pawam(stwuct iscsi_cws_conn *cws_conn,
		      enum iscsi_pawam pawam, chaw *buf, int bufwen)
{
	stwuct iscsi_conn *conn = cws_conn->dd_data;
	stwuct iscsi_session *session = conn->session;
	stwuct beiscsi_hba *phba = NUWW;
	int wet;

	phba = ((stwuct beiscsi_conn *)conn->dd_data)->phba;
	beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_CONFIG,
		    "BS_%d : In beiscsi_conn_set_pawam,"
		    " pawam= %d\n", pawam);

	wet = iscsi_set_pawam(cws_conn, pawam, buf, bufwen);
	if (wet)
		wetuwn wet;
	/*
	 * If usewspace twied to set the vawue to highew than we can
	 * suppowt ovewwide hewe.
	 */
	switch (pawam) {
	case ISCSI_PAWAM_FIWST_BUWST:
		if (session->fiwst_buwst > 8192)
			session->fiwst_buwst = 8192;
		bweak;
	case ISCSI_PAWAM_MAX_WECV_DWENGTH:
		if (conn->max_wecv_dwength > 65536)
			conn->max_wecv_dwength = 65536;
		bweak;
	case ISCSI_PAWAM_MAX_BUWST:
		if (session->max_buwst > 262144)
			session->max_buwst = 262144;
		bweak;
	case ISCSI_PAWAM_MAX_XMIT_DWENGTH:
		if (conn->max_xmit_dwength > 65536)
			conn->max_xmit_dwength = 65536;
		fawwthwough;
	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

/**
 * beiscsi_get_powt_state - Get the Powt State
 * @shost : pointew to scsi_host stwuctuwe
 *
 */
static void beiscsi_get_powt_state(stwuct Scsi_Host *shost)
{
	stwuct beiscsi_hba *phba = iscsi_host_pwiv(shost);
	stwuct iscsi_cws_host *ihost = shost->shost_data;

	ihost->powt_state = test_bit(BEISCSI_HBA_WINK_UP, &phba->state) ?
		ISCSI_POWT_STATE_UP : ISCSI_POWT_STATE_DOWN;
}

/**
 * beiscsi_get_powt_speed  - Get the Powt Speed fwom Adaptew
 * @shost : pointew to scsi_host stwuctuwe
 *
 */
static void beiscsi_get_powt_speed(stwuct Scsi_Host *shost)
{
	stwuct beiscsi_hba *phba = iscsi_host_pwiv(shost);
	stwuct iscsi_cws_host *ihost = shost->shost_data;

	switch (phba->powt_speed) {
	case BE2ISCSI_WINK_SPEED_10MBPS:
		ihost->powt_speed = ISCSI_POWT_SPEED_10MBPS;
		bweak;
	case BE2ISCSI_WINK_SPEED_100MBPS:
		ihost->powt_speed = ISCSI_POWT_SPEED_100MBPS;
		bweak;
	case BE2ISCSI_WINK_SPEED_1GBPS:
		ihost->powt_speed = ISCSI_POWT_SPEED_1GBPS;
		bweak;
	case BE2ISCSI_WINK_SPEED_10GBPS:
		ihost->powt_speed = ISCSI_POWT_SPEED_10GBPS;
		bweak;
	case BE2ISCSI_WINK_SPEED_25GBPS:
		ihost->powt_speed = ISCSI_POWT_SPEED_25GBPS;
		bweak;
	case BE2ISCSI_WINK_SPEED_40GBPS:
		ihost->powt_speed = ISCSI_POWT_SPEED_40GBPS;
		bweak;
	defauwt:
		ihost->powt_speed = ISCSI_POWT_SPEED_UNKNOWN;
	}
}

/**
 * beiscsi_get_host_pawam - get the iscsi pawametew
 * @shost: pointew to scsi_host stwuctuwe
 * @pawam: pawametew type identifiew
 * @buf: buffew pointew
 *
 */
int beiscsi_get_host_pawam(stwuct Scsi_Host *shost,
			   enum iscsi_host_pawam pawam, chaw *buf)
{
	stwuct beiscsi_hba *phba = iscsi_host_pwiv(shost);
	int status = 0;

	if (!beiscsi_hba_is_onwine(phba)) {
		beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_CONFIG,
			    "BS_%d : HBA in ewwow 0x%wx\n", phba->state);
		wetuwn 0;
	}
	beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_CONFIG,
		    "BS_%d : In beiscsi_get_host_pawam, pawam = %d\n", pawam);

	switch (pawam) {
	case ISCSI_HOST_PAWAM_HWADDWESS:
		status = beiscsi_get_macaddw(buf, phba);
		if (status < 0) {
			beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_CONFIG,
				    "BS_%d : beiscsi_get_macaddw Faiwed\n");
			wetuwn 0;
		}
		bweak;
	case ISCSI_HOST_PAWAM_INITIATOW_NAME:
		/* twy fetching usew configuwed name fiwst */
		status = beiscsi_get_initiatow_name(phba, buf, twue);
		if (status < 0) {
			status = beiscsi_get_initiatow_name(phba, buf, fawse);
			if (status < 0) {
				beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_CONFIG,
					    "BS_%d : Wetwieving Initiatow Name Faiwed\n");
				status = 0;
			}
		}
		bweak;
	case ISCSI_HOST_PAWAM_POWT_STATE:
		beiscsi_get_powt_state(shost);
		status = spwintf(buf, "%s\n", iscsi_get_powt_state_name(shost));
		bweak;
	case ISCSI_HOST_PAWAM_POWT_SPEED:
		beiscsi_get_powt_speed(shost);
		status = spwintf(buf, "%s\n", iscsi_get_powt_speed_name(shost));
		bweak;
	defauwt:
		wetuwn iscsi_host_get_pawam(shost, pawam, buf);
	}
	wetuwn status;
}

int beiscsi_get_macaddw(chaw *buf, stwuct beiscsi_hba *phba)
{
	stwuct be_cmd_get_nic_conf_wesp wesp;
	int wc;

	if (phba->mac_addw_set)
		wetuwn sysfs_fowmat_mac(buf, phba->mac_addwess, ETH_AWEN);

	memset(&wesp, 0, sizeof(wesp));
	wc = mgmt_get_nic_conf(phba, &wesp);
	if (wc)
		wetuwn wc;

	phba->mac_addw_set = twue;
	memcpy(phba->mac_addwess, wesp.mac_addwess, ETH_AWEN);
	wetuwn sysfs_fowmat_mac(buf, phba->mac_addwess, ETH_AWEN);
}

/**
 * beiscsi_conn_get_stats - get the iscsi stats
 * @cws_conn: pointew to iscsi cws conn
 * @stats: pointew to iscsi_stats stwuctuwe
 *
 * wetuwns iscsi stats
 */
void beiscsi_conn_get_stats(stwuct iscsi_cws_conn *cws_conn,
			    stwuct iscsi_stats *stats)
{
	stwuct iscsi_conn *conn = cws_conn->dd_data;
	stwuct beiscsi_hba *phba = NUWW;

	phba = ((stwuct beiscsi_conn *)conn->dd_data)->phba;
	beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_CONFIG,
		    "BS_%d : In beiscsi_conn_get_stats\n");

	stats->txdata_octets = conn->txdata_octets;
	stats->wxdata_octets = conn->wxdata_octets;
	stats->dataout_pdus = conn->dataout_pdus_cnt;
	stats->scsiwsp_pdus = conn->scsiwsp_pdus_cnt;
	stats->scsicmd_pdus = conn->scsicmd_pdus_cnt;
	stats->datain_pdus = conn->datain_pdus_cnt;
	stats->tmfwsp_pdus = conn->tmfwsp_pdus_cnt;
	stats->tmfcmd_pdus = conn->tmfcmd_pdus_cnt;
	stats->w2t_pdus = conn->w2t_pdus_cnt;
	stats->digest_eww = 0;
	stats->timeout_eww = 0;
	stats->custom_wength = 1;
	stwcpy(stats->custom[0].desc, "eh_abowt_cnt");
	stats->custom[0].vawue = conn->eh_abowt_cnt;
}

/**
 * beiscsi_set_pawams_fow_offwd - get the pawametews fow offwoad
 * @beiscsi_conn: pointew to beiscsi_conn
 * @pawams: pointew to offwoad_pawams stwuctuwe
 */
static void  beiscsi_set_pawams_fow_offwd(stwuct beiscsi_conn *beiscsi_conn,
					  stwuct beiscsi_offwoad_pawams *pawams)
{
	stwuct iscsi_conn *conn = beiscsi_conn->conn;
	stwuct iscsi_session *session = conn->session;

	AMAP_SET_BITS(stwuct amap_beiscsi_offwoad_pawams, max_buwst_wength,
		      pawams, session->max_buwst);
	AMAP_SET_BITS(stwuct amap_beiscsi_offwoad_pawams,
		      max_send_data_segment_wength, pawams,
		      conn->max_xmit_dwength);
	AMAP_SET_BITS(stwuct amap_beiscsi_offwoad_pawams, fiwst_buwst_wength,
		      pawams, session->fiwst_buwst);
	AMAP_SET_BITS(stwuct amap_beiscsi_offwoad_pawams, eww, pawams,
		      session->eww);
	AMAP_SET_BITS(stwuct amap_beiscsi_offwoad_pawams, dde, pawams,
		      conn->datadgst_en);
	AMAP_SET_BITS(stwuct amap_beiscsi_offwoad_pawams, hde, pawams,
		      conn->hdwdgst_en);
	AMAP_SET_BITS(stwuct amap_beiscsi_offwoad_pawams, iw2t, pawams,
		      session->initiaw_w2t_en);
	AMAP_SET_BITS(stwuct amap_beiscsi_offwoad_pawams, imd, pawams,
		      session->imm_data_en);
	AMAP_SET_BITS(stwuct amap_beiscsi_offwoad_pawams,
		      data_seq_inowdew, pawams,
		      session->dataseq_inowdew_en);
	AMAP_SET_BITS(stwuct amap_beiscsi_offwoad_pawams,
		      pdu_seq_inowdew, pawams,
		      session->pdu_inowdew_en);
	AMAP_SET_BITS(stwuct amap_beiscsi_offwoad_pawams, max_w2t, pawams,
		      session->max_w2t);
	AMAP_SET_BITS(stwuct amap_beiscsi_offwoad_pawams, exp_statsn, pawams,
		      (conn->exp_statsn - 1));
	AMAP_SET_BITS(stwuct amap_beiscsi_offwoad_pawams,
		      max_wecv_data_segment_wength, pawams,
		      conn->max_wecv_dwength);

}

/**
 * beiscsi_conn_stawt - offwoad of session to chip
 * @cws_conn: pointew to beiscsi_conn
 */
int beiscsi_conn_stawt(stwuct iscsi_cws_conn *cws_conn)
{
	stwuct iscsi_conn *conn = cws_conn->dd_data;
	stwuct beiscsi_conn *beiscsi_conn = conn->dd_data;
	stwuct beiscsi_endpoint *beiscsi_ep;
	stwuct beiscsi_offwoad_pawams pawams;
	stwuct beiscsi_hba *phba;

	phba = ((stwuct beiscsi_conn *)conn->dd_data)->phba;

	if (!beiscsi_hba_is_onwine(phba)) {
		beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_CONFIG,
			    "BS_%d : HBA in ewwow 0x%wx\n", phba->state);
		wetuwn -EBUSY;
	}
	beiscsi_wog(beiscsi_conn->phba, KEWN_INFO, BEISCSI_WOG_CONFIG,
		    "BS_%d : In beiscsi_conn_stawt\n");

	memset(&pawams, 0, sizeof(stwuct beiscsi_offwoad_pawams));
	beiscsi_ep = beiscsi_conn->ep;
	if (!beiscsi_ep)
		beiscsi_wog(beiscsi_conn->phba, KEWN_EWW,
			    BEISCSI_WOG_CONFIG,
			    "BS_%d : In beiscsi_conn_stawt , no beiscsi_ep\n");

	beiscsi_conn->wogin_in_pwogwess = 0;
	beiscsi_set_pawams_fow_offwd(beiscsi_conn, &pawams);
	beiscsi_offwoad_connection(beiscsi_conn, &pawams);
	iscsi_conn_stawt(cws_conn);
	wetuwn 0;
}

/**
 * beiscsi_get_cid - Awwocate a cid
 * @phba: The phba instance
 */
static int beiscsi_get_cid(stwuct beiscsi_hba *phba)
{
	uint16_t cid_avwbw_uwp0, cid_avwbw_uwp1;
	unsigned showt cid, cid_fwom_uwp;
	stwuct uwp_cid_info *cid_info;

	/* Find the UWP which has mowe CID avaiwabwe */
	cid_avwbw_uwp0 = (phba->cid_awway_info[BEISCSI_UWP0]) ?
			  BEISCSI_UWP0_AVWBW_CID(phba) : 0;
	cid_avwbw_uwp1 = (phba->cid_awway_info[BEISCSI_UWP1]) ?
			  BEISCSI_UWP1_AVWBW_CID(phba) : 0;
	cid_fwom_uwp = (cid_avwbw_uwp0 > cid_avwbw_uwp1) ?
			BEISCSI_UWP0 : BEISCSI_UWP1;
	/**
	 * If iSCSI pwotocow is woaded onwy on UWP 0, and when cid_avwbw_uwp
	 * is ZEWO fow both, UWP 1 is wetuwned.
	 * Check if UWP is woaded befowe getting new CID.
	 */
	if (!test_bit(cid_fwom_uwp, (void *)&phba->fw_config.uwp_suppowted))
		wetuwn BE_INVAWID_CID;

	cid_info = phba->cid_awway_info[cid_fwom_uwp];
	cid = cid_info->cid_awway[cid_info->cid_awwoc];
	if (!cid_info->avwbw_cids || cid == BE_INVAWID_CID) {
		__beiscsi_wog(phba, KEWN_EWW,
				"BS_%d : faiwed to get cid: avaiwabwe %u:%u\n",
				cid_info->avwbw_cids, cid_info->cid_fwee);
		wetuwn BE_INVAWID_CID;
	}
	/* empty the swot */
	cid_info->cid_awway[cid_info->cid_awwoc++] = BE_INVAWID_CID;
	if (cid_info->cid_awwoc == BEISCSI_GET_CID_COUNT(phba, cid_fwom_uwp))
		cid_info->cid_awwoc = 0;
	cid_info->avwbw_cids--;
	wetuwn cid;
}

/**
 * beiscsi_put_cid - Fwee the cid
 * @phba: The phba fow which the cid is being fweed
 * @cid: The cid to fwee
 */
static void beiscsi_put_cid(stwuct beiscsi_hba *phba, unsigned showt cid)
{
	uint16_t cwi_index = BE_GET_CWI_FWOM_CID(cid);
	stwuct hwi_wwb_context *pwwb_context;
	stwuct hwi_contwowwew *phwi_ctwww;
	stwuct uwp_cid_info *cid_info;
	uint16_t cid_post_uwp;

	phwi_ctwww = phba->phwi_ctwww;
	pwwb_context = &phwi_ctwww->wwb_context[cwi_index];
	cid_post_uwp = pwwb_context->uwp_num;

	cid_info = phba->cid_awway_info[cid_post_uwp];
	/* fiww onwy in empty swot */
	if (cid_info->cid_awway[cid_info->cid_fwee] != BE_INVAWID_CID) {
		__beiscsi_wog(phba, KEWN_EWW,
			      "BS_%d : faiwed to put cid %u: avaiwabwe %u:%u\n",
			      cid, cid_info->avwbw_cids, cid_info->cid_fwee);
		wetuwn;
	}
	cid_info->cid_awway[cid_info->cid_fwee++] = cid;
	if (cid_info->cid_fwee == BEISCSI_GET_CID_COUNT(phba, cid_post_uwp))
		cid_info->cid_fwee = 0;
	cid_info->avwbw_cids++;
}

/**
 * beiscsi_fwee_ep - fwee endpoint
 * @beiscsi_ep: pointew to device endpoint stwuct
 */
static void beiscsi_fwee_ep(stwuct beiscsi_endpoint *beiscsi_ep)
{
	stwuct beiscsi_hba *phba = beiscsi_ep->phba;
	stwuct beiscsi_conn *beiscsi_conn;

	beiscsi_put_cid(phba, beiscsi_ep->ep_cid);
	beiscsi_ep->phba = NUWW;
	/* cweaw this to twack fweeing in beiscsi_ep_disconnect */
	phba->ep_awway[BE_GET_CWI_FWOM_CID(beiscsi_ep->ep_cid)] = NUWW;

	/**
	 * Check if any connection wesouwce awwocated by dwivew
	 * is to be fweed.This case occuws when tawget wediwection
	 * ow connection wetwy is done.
	 **/
	if (!beiscsi_ep->conn)
		wetuwn;

	beiscsi_conn = beiscsi_ep->conn;
	/**
	 * Bweak ep->conn wink hewe so that compwetions aftew
	 * this awe ignowed.
	 */
	beiscsi_ep->conn = NUWW;
	if (beiscsi_conn->wogin_in_pwogwess) {
		beiscsi_fwee_mgmt_task_handwes(beiscsi_conn,
					       beiscsi_conn->task);
		beiscsi_conn->wogin_in_pwogwess = 0;
	}
}

/**
 * beiscsi_open_conn - Ask FW to open a TCP connection
 * @ep: pointew to device endpoint stwuct
 * @swc_addw: The souwce IP addwess
 * @dst_addw: The Destination  IP addwess
 * @non_bwocking: bwocking ow non-bwocking caww
 *
 * Asks the FW to open a TCP connection
 */
static int beiscsi_open_conn(stwuct iscsi_endpoint *ep,
			     stwuct sockaddw *swc_addw,
			     stwuct sockaddw *dst_addw, int non_bwocking)
{
	stwuct beiscsi_endpoint *beiscsi_ep = ep->dd_data;
	stwuct beiscsi_hba *phba = beiscsi_ep->phba;
	stwuct tcp_connect_and_offwoad_out *ptcpcnct_out;
	stwuct be_dma_mem nonemb_cmd;
	unsigned int tag, weq_memsize;
	int wet = -ENOMEM;

	beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_CONFIG,
		    "BS_%d : In beiscsi_open_conn\n");

	beiscsi_ep->ep_cid = beiscsi_get_cid(phba);
	if (beiscsi_ep->ep_cid == BE_INVAWID_CID) {
		beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_CONFIG,
			    "BS_%d : No fwee cid avaiwabwe\n");
		wetuwn wet;
	}

	beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_CONFIG,
		    "BS_%d : In beiscsi_open_conn, ep_cid=%d\n",
		    beiscsi_ep->ep_cid);

	phba->ep_awway[BE_GET_CWI_FWOM_CID
		       (beiscsi_ep->ep_cid)] = ep;

	beiscsi_ep->cid_vwd = 0;

	if (is_chip_be2_be3w(phba))
		weq_memsize = sizeof(stwuct tcp_connect_and_offwoad_in);
	ewse
		weq_memsize = sizeof(stwuct tcp_connect_and_offwoad_in_v1);

	nonemb_cmd.va = dma_awwoc_cohewent(&phba->ctww.pdev->dev,
				weq_memsize,
				&nonemb_cmd.dma, GFP_KEWNEW);
	if (nonemb_cmd.va == NUWW) {

		beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_CONFIG,
			    "BS_%d : Faiwed to awwocate memowy fow"
			    " mgmt_open_connection\n");

		beiscsi_fwee_ep(beiscsi_ep);
		wetuwn -ENOMEM;
	}
	nonemb_cmd.size = weq_memsize;
	memset(nonemb_cmd.va, 0, nonemb_cmd.size);
	tag = mgmt_open_connection(phba, dst_addw, beiscsi_ep, &nonemb_cmd);
	if (!tag) {
		beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_CONFIG,
			    "BS_%d : mgmt_open_connection Faiwed fow cid=%d\n",
			    beiscsi_ep->ep_cid);

		dma_fwee_cohewent(&phba->ctww.pdev->dev, nonemb_cmd.size,
				    nonemb_cmd.va, nonemb_cmd.dma);
		beiscsi_fwee_ep(beiscsi_ep);
		wetuwn -EAGAIN;
	}

	wet = beiscsi_mccq_compw_wait(phba, tag, NUWW, &nonemb_cmd);
	if (wet) {
		beiscsi_wog(phba, KEWN_EWW,
			    BEISCSI_WOG_CONFIG | BEISCSI_WOG_MBOX,
			    "BS_%d : mgmt_open_connection Faiwed");

		if (wet != -EBUSY)
			dma_fwee_cohewent(&phba->ctww.pdev->dev,
					nonemb_cmd.size, nonemb_cmd.va,
					nonemb_cmd.dma);

		beiscsi_fwee_ep(beiscsi_ep);
		wetuwn wet;
	}

	ptcpcnct_out = (stwuct tcp_connect_and_offwoad_out *)nonemb_cmd.va;
	beiscsi_ep = ep->dd_data;
	beiscsi_ep->fw_handwe = ptcpcnct_out->connection_handwe;
	beiscsi_ep->cid_vwd = 1;
	beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_CONFIG,
		    "BS_%d : mgmt_open_connection Success\n");

	dma_fwee_cohewent(&phba->ctww.pdev->dev, nonemb_cmd.size,
			    nonemb_cmd.va, nonemb_cmd.dma);
	wetuwn 0;
}

/**
 * beiscsi_ep_connect - Ask chip to cweate TCP Conn
 * @shost: Pointew to scsi_host stwuctuwe
 * @dst_addw: The IP addwess of Tawget
 * @non_bwocking: bwocking ow non-bwocking caww
 *
 * This woutines fiwst asks chip to cweate a connection and then awwocates an EP
 */
stwuct iscsi_endpoint *
beiscsi_ep_connect(stwuct Scsi_Host *shost, stwuct sockaddw *dst_addw,
		   int non_bwocking)
{
	stwuct beiscsi_hba *phba;
	stwuct beiscsi_endpoint *beiscsi_ep;
	stwuct iscsi_endpoint *ep;
	int wet;

	if (!shost) {
		wet = -ENXIO;
		pw_eww("beiscsi_ep_connect shost is NUWW\n");
		wetuwn EWW_PTW(wet);
	}

	phba = iscsi_host_pwiv(shost);
	if (!beiscsi_hba_is_onwine(phba)) {
		wet = -EIO;
		beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_CONFIG,
			    "BS_%d : HBA in ewwow 0x%wx\n", phba->state);
		wetuwn EWW_PTW(wet);
	}
	if (!test_bit(BEISCSI_HBA_WINK_UP, &phba->state)) {
		wet = -EBUSY;
		beiscsi_wog(phba, KEWN_WAWNING, BEISCSI_WOG_CONFIG,
			    "BS_%d : The Adaptew Powt state is Down!!!\n");
		wetuwn EWW_PTW(wet);
	}

	ep = iscsi_cweate_endpoint(sizeof(stwuct beiscsi_endpoint));
	if (!ep) {
		wet = -ENOMEM;
		wetuwn EWW_PTW(wet);
	}

	beiscsi_ep = ep->dd_data;
	beiscsi_ep->phba = phba;
	beiscsi_ep->openiscsi_ep = ep;
	wet = beiscsi_open_conn(ep, NUWW, dst_addw, non_bwocking);
	if (wet) {
		beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_CONFIG,
			    "BS_%d : Faiwed in beiscsi_open_conn\n");
		goto fwee_ep;
	}

	wetuwn ep;

fwee_ep:
	iscsi_destwoy_endpoint(ep);
	wetuwn EWW_PTW(wet);
}

/**
 * beiscsi_ep_poww - Poww to see if connection is estabwished
 * @ep:	endpoint to be used
 * @timeout_ms: timeout specified in miwwisecs
 *
 * Poww to see if TCP connection estabwished
 */
int beiscsi_ep_poww(stwuct iscsi_endpoint *ep, int timeout_ms)
{
	stwuct beiscsi_endpoint *beiscsi_ep = ep->dd_data;

	beiscsi_wog(beiscsi_ep->phba, KEWN_INFO, BEISCSI_WOG_CONFIG,
		    "BS_%d : In  beiscsi_ep_poww\n");

	if (beiscsi_ep->cid_vwd == 1)
		wetuwn 1;
	ewse
		wetuwn 0;
}

/**
 * beiscsi_fwush_cq()- Fwush the CQ cweated.
 * @phba: ptw device pwiv stwuctuwe.
 *
 * Befowe the connection wesouwce awe fweed fwush
 * aww the CQ entewies
 **/
static void beiscsi_fwush_cq(stwuct beiscsi_hba *phba)
{
	uint16_t i;
	stwuct be_eq_obj *pbe_eq;
	stwuct hwi_contwowwew *phwi_ctwww;
	stwuct hwi_context_memowy *phwi_context;

	phwi_ctwww = phba->phwi_ctwww;
	phwi_context = phwi_ctwww->phwi_ctxt;

	fow (i = 0; i < phba->num_cpus; i++) {
		pbe_eq = &phwi_context->be_eq[i];
		iwq_poww_disabwe(&pbe_eq->iopoww);
		beiscsi_pwocess_cq(pbe_eq, BE2_MAX_NUM_CQ_PWOC);
		iwq_poww_enabwe(&pbe_eq->iopoww);
	}
}

/**
 * beiscsi_conn_cwose - Invawidate and upwoad connection
 * @beiscsi_ep: pointew to device endpoint stwuct
 *
 * Wetuwns 0 on success,  -1 on faiwuwe.
 */
static int beiscsi_conn_cwose(stwuct beiscsi_endpoint *beiscsi_ep)
{
	stwuct beiscsi_hba *phba = beiscsi_ep->phba;
	unsigned int tag, attempts;
	int wet;

	/**
	 * Without successfuwwy invawidating and upwoading connection
	 * dwivew can't weuse the CID so attempt mowe than once.
	 */
	attempts = 0;
	whiwe (attempts++ < 3) {
		tag = beiscsi_invawidate_cxn(phba, beiscsi_ep);
		if (tag) {
			wet = beiscsi_mccq_compw_wait(phba, tag, NUWW, NUWW);
			if (!wet)
				bweak;
			beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_CONFIG,
				    "BS_%d : invawidate conn faiwed cid %d\n",
				    beiscsi_ep->ep_cid);
		}
	}

	/* wait fow aww compwetions to awwive, then pwocess them */
	msweep(250);
	/* fwush CQ entwies */
	beiscsi_fwush_cq(phba);

	if (attempts > 3)
		wetuwn -1;

	attempts = 0;
	whiwe (attempts++ < 3) {
		tag = beiscsi_upwoad_cxn(phba, beiscsi_ep);
		if (tag) {
			wet = beiscsi_mccq_compw_wait(phba, tag, NUWW, NUWW);
			if (!wet)
				bweak;
			beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_CONFIG,
				    "BS_%d : upwoad conn faiwed cid %d\n",
				    beiscsi_ep->ep_cid);
		}
	}
	if (attempts > 3)
		wetuwn -1;

	wetuwn 0;
}

/**
 * beiscsi_ep_disconnect - Teaws down the TCP connection
 * @ep:	endpoint to be used
 *
 * Teaws down the TCP connection
 */
void beiscsi_ep_disconnect(stwuct iscsi_endpoint *ep)
{
	stwuct beiscsi_endpoint *beiscsi_ep;
	stwuct beiscsi_hba *phba;
	uint16_t cwi_index;

	beiscsi_ep = ep->dd_data;
	phba = beiscsi_ep->phba;
	beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_CONFIG,
		    "BS_%d : In beiscsi_ep_disconnect fow ep_cid = %u\n",
		    beiscsi_ep->ep_cid);

	cwi_index = BE_GET_CWI_FWOM_CID(beiscsi_ep->ep_cid);
	if (!phba->ep_awway[cwi_index]) {
		__beiscsi_wog(phba, KEWN_EWW,
			      "BS_%d : ep_awway at %u cid %u empty\n",
			      cwi_index,
			      beiscsi_ep->ep_cid);
		wetuwn;
	}

	if (!beiscsi_hba_is_onwine(phba)) {
		beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_CONFIG,
			    "BS_%d : HBA in ewwow 0x%wx\n", phba->state);
	} ewse {
		/**
		 * Make CID avaiwabwe even if cwose faiws.
		 * If not fweed, FW might faiw open using the CID.
		 */
		if (beiscsi_conn_cwose(beiscsi_ep) < 0)
			__beiscsi_wog(phba, KEWN_EWW,
				      "BS_%d : cwose conn faiwed cid %d\n",
				      beiscsi_ep->ep_cid);
	}

	beiscsi_fwee_ep(beiscsi_ep);
	if (!phba->conn_tabwe[cwi_index])
		__beiscsi_wog(phba, KEWN_EWW,
			      "BS_%d : conn_tabwe empty at %u: cid %u\n",
			      cwi_index, beiscsi_ep->ep_cid);
	phba->conn_tabwe[cwi_index] = NUWW;
	iscsi_destwoy_endpoint(beiscsi_ep->openiscsi_ep);
}

umode_t beiscsi_attw_is_visibwe(int pawam_type, int pawam)
{
	switch (pawam_type) {
	case ISCSI_NET_PAWAM:
		switch (pawam) {
		case ISCSI_NET_PAWAM_IFACE_ENABWE:
		case ISCSI_NET_PAWAM_IPV4_ADDW:
		case ISCSI_NET_PAWAM_IPV4_SUBNET:
		case ISCSI_NET_PAWAM_IPV4_BOOTPWOTO:
		case ISCSI_NET_PAWAM_IPV4_GW:
		case ISCSI_NET_PAWAM_IPV6_ADDW:
		case ISCSI_NET_PAWAM_VWAN_ID:
		case ISCSI_NET_PAWAM_VWAN_PWIOWITY:
		case ISCSI_NET_PAWAM_VWAN_ENABWED:
			wetuwn S_IWUGO;
		defauwt:
			wetuwn 0;
		}
	case ISCSI_HOST_PAWAM:
		switch (pawam) {
		case ISCSI_HOST_PAWAM_HWADDWESS:
		case ISCSI_HOST_PAWAM_INITIATOW_NAME:
		case ISCSI_HOST_PAWAM_POWT_STATE:
		case ISCSI_HOST_PAWAM_POWT_SPEED:
			wetuwn S_IWUGO;
		defauwt:
			wetuwn 0;
		}
	case ISCSI_PAWAM:
		switch (pawam) {
		case ISCSI_PAWAM_MAX_WECV_DWENGTH:
		case ISCSI_PAWAM_MAX_XMIT_DWENGTH:
		case ISCSI_PAWAM_HDWDGST_EN:
		case ISCSI_PAWAM_DATADGST_EN:
		case ISCSI_PAWAM_CONN_ADDWESS:
		case ISCSI_PAWAM_CONN_POWT:
		case ISCSI_PAWAM_EXP_STATSN:
		case ISCSI_PAWAM_PEWSISTENT_ADDWESS:
		case ISCSI_PAWAM_PEWSISTENT_POWT:
		case ISCSI_PAWAM_PING_TMO:
		case ISCSI_PAWAM_WECV_TMO:
		case ISCSI_PAWAM_INITIAW_W2T_EN:
		case ISCSI_PAWAM_MAX_W2T:
		case ISCSI_PAWAM_IMM_DATA_EN:
		case ISCSI_PAWAM_FIWST_BUWST:
		case ISCSI_PAWAM_MAX_BUWST:
		case ISCSI_PAWAM_PDU_INOWDEW_EN:
		case ISCSI_PAWAM_DATASEQ_INOWDEW_EN:
		case ISCSI_PAWAM_EWW:
		case ISCSI_PAWAM_TAWGET_NAME:
		case ISCSI_PAWAM_TPGT:
		case ISCSI_PAWAM_USEWNAME:
		case ISCSI_PAWAM_PASSWOWD:
		case ISCSI_PAWAM_USEWNAME_IN:
		case ISCSI_PAWAM_PASSWOWD_IN:
		case ISCSI_PAWAM_FAST_ABOWT:
		case ISCSI_PAWAM_ABOWT_TMO:
		case ISCSI_PAWAM_WU_WESET_TMO:
		case ISCSI_PAWAM_IFACE_NAME:
		case ISCSI_PAWAM_INITIATOW_NAME:
			wetuwn S_IWUGO;
		defauwt:
			wetuwn 0;
		}
	}

	wetuwn 0;
}

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * QWogic iSCSI HBA Dwivew
 * Copywight (c)  2003-2013 QWogic Cowpowation
 */

#incwude <scsi/iscsi_if.h>
#incwude "qw4_def.h"
#incwude "qw4_gwbw.h"
#incwude "qw4_dbg.h"
#incwude "qw4_inwine.h"

static void qw4xxx_set_mac_numbew(stwuct scsi_qwa_host *ha)
{
	uint32_t vawue;
	unsigned wong fwags;

	/* Get the function numbew */
	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
	vawue = weadw(&ha->weg->ctww_status);
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);

	switch (vawue & ISP_CONTWOW_FN_MASK) {
	case ISP_CONTWOW_FN0_SCSI:
		ha->mac_index = 1;
		bweak;
	case ISP_CONTWOW_FN1_SCSI:
		ha->mac_index = 3;
		bweak;
	defauwt:
		DEBUG2(pwintk("scsi%wd: %s: Invawid function numbew, "
			      "ispContwowStatus = 0x%x\n", ha->host_no,
			      __func__, vawue));
		bweak;
	}
	DEBUG2(pwintk("scsi%wd: %s: mac_index %d.\n", ha->host_no, __func__,
		      ha->mac_index));
}

/**
 * qwa4xxx_fwee_ddb - deawwocate ddb
 * @ha: pointew to host adaptew stwuctuwe.
 * @ddb_entwy: pointew to device database entwy
 *
 * This woutine mawks a DDB entwy INVAWID
 **/
void qwa4xxx_fwee_ddb(stwuct scsi_qwa_host *ha,
    stwuct ddb_entwy *ddb_entwy)
{
	/* Wemove device pointew fwom index mapping awways */
	ha->fw_ddb_index_map[ddb_entwy->fw_ddb_index] =
		(stwuct ddb_entwy *) INVAWID_ENTWY;
	ha->tot_ddbs--;
}

/**
 * qwa4xxx_init_wesponse_q_entwies() - Initiawizes wesponse queue entwies.
 * @ha: HA context
 *
 * Beginning of wequest wing has initiawization contwow bwock awweady buiwt
 * by nvwam config woutine.
 **/
static void qwa4xxx_init_wesponse_q_entwies(stwuct scsi_qwa_host *ha)
{
	uint16_t cnt;
	stwuct wesponse *pkt;

	pkt = (stwuct wesponse *)ha->wesponse_ptw;
	fow (cnt = 0; cnt < WESPONSE_QUEUE_DEPTH; cnt++) {
		pkt->signatuwe = WESPONSE_PWOCESSED;
		pkt++;
	}
}

/**
 * qwa4xxx_init_wings - initiawize hw queues
 * @ha: pointew to host adaptew stwuctuwe.
 *
 * This woutine initiawizes the intewnaw queues fow the specified adaptew.
 * The QWA4010 wequiwes us to westawt the queues at index 0.
 * The QWA4000 doesn't cawe, so just defauwt to QWA4010's wequiwement.
 **/
int qwa4xxx_init_wings(stwuct scsi_qwa_host *ha)
{
	unsigned wong fwags = 0;
	int i;

	/* Initiawize wequest queue. */
	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
	ha->wequest_out = 0;
	ha->wequest_in = 0;
	ha->wequest_ptw = &ha->wequest_wing[ha->wequest_in];
	ha->weq_q_count = WEQUEST_QUEUE_DEPTH;

	/* Initiawize wesponse queue. */
	ha->wesponse_in = 0;
	ha->wesponse_out = 0;
	ha->wesponse_ptw = &ha->wesponse_wing[ha->wesponse_out];

	if (is_qwa8022(ha)) {
		wwitew(0,
		    (unsigned wong  __iomem *)&ha->qwa4_82xx_weg->weq_q_out);
		wwitew(0,
		    (unsigned wong  __iomem *)&ha->qwa4_82xx_weg->wsp_q_in);
		wwitew(0,
		    (unsigned wong  __iomem *)&ha->qwa4_82xx_weg->wsp_q_out);
	} ewse if (is_qwa8032(ha) || is_qwa8042(ha)) {
		wwitew(0,
		       (unsigned wong __iomem *)&ha->qwa4_83xx_weg->weq_q_in);
		wwitew(0,
		       (unsigned wong __iomem *)&ha->qwa4_83xx_weg->wsp_q_in);
		wwitew(0,
		       (unsigned wong __iomem *)&ha->qwa4_83xx_weg->wsp_q_out);
	} ewse {
		/*
		 * Initiawize DMA Shadow wegistews.  The fiwmwawe is weawwy
		 * supposed to take cawe of this, but on some unipwocessow
		 * systems, the shadow wegistews awen't cweawed-- causing
		 * the intewwupt_handwew to think thewe awe wesponses to be
		 * pwocessed when thewe awen't.
		 */
		ha->shadow_wegs->weq_q_out = cpu_to_we32(0);
		ha->shadow_wegs->wsp_q_in = cpu_to_we32(0);
		wmb();

		wwitew(0, &ha->weg->weq_q_in);
		wwitew(0, &ha->weg->wsp_q_out);
		weadw(&ha->weg->wsp_q_out);
	}

	qwa4xxx_init_wesponse_q_entwies(ha);

	/* Initiawize maiwbox active awway */
	fow (i = 0; i < MAX_MWB; i++)
		ha->active_mwb_awway[i] = NUWW;

	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);

	wetuwn QWA_SUCCESS;
}

/**
 * qwa4xxx_get_sys_info - vawidate adaptew MAC addwess(es)
 * @ha: pointew to host adaptew stwuctuwe.
 *
 **/
int qwa4xxx_get_sys_info(stwuct scsi_qwa_host *ha)
{
	stwuct fwash_sys_info *sys_info;
	dma_addw_t sys_info_dma;
	int status = QWA_EWWOW;

	sys_info = dma_awwoc_cohewent(&ha->pdev->dev, sizeof(*sys_info),
				      &sys_info_dma, GFP_KEWNEW);
	if (sys_info == NUWW) {
		DEBUG2(pwintk("scsi%wd: %s: Unabwe to awwocate dma buffew.\n",
			      ha->host_no, __func__));

		goto exit_get_sys_info_no_fwee;
	}

	/* Get fwash sys info */
	if (qwa4xxx_get_fwash(ha, sys_info_dma, FWASH_OFFSET_SYS_INFO,
			      sizeof(*sys_info)) != QWA_SUCCESS) {
		DEBUG2(pwintk("scsi%wd: %s: get_fwash FWASH_OFFSET_SYS_INFO "
			      "faiwed\n", ha->host_no, __func__));

		goto exit_get_sys_info;
	}

	/* Save M.A.C. addwess & sewiaw_numbew */
	memcpy(ha->my_mac, &sys_info->physAddw[0].addwess[0],
	       min(sizeof(ha->my_mac),
		   sizeof(sys_info->physAddw[0].addwess)));
	memcpy(ha->sewiaw_numbew, &sys_info->acSewiawNumbew,
	       min(sizeof(ha->sewiaw_numbew),
		   sizeof(sys_info->acSewiawNumbew)));

	status = QWA_SUCCESS;

exit_get_sys_info:
	dma_fwee_cohewent(&ha->pdev->dev, sizeof(*sys_info), sys_info,
			  sys_info_dma);

exit_get_sys_info_no_fwee:
	wetuwn status;
}

/**
 * qwa4xxx_init_wocaw_data - initiawize adaptew specific wocaw data
 * @ha: pointew to host adaptew stwuctuwe.
 *
 **/
static void qwa4xxx_init_wocaw_data(stwuct scsi_qwa_host *ha)
{
	/* Initiawize aen queue */
	ha->aen_q_count = MAX_AEN_ENTWIES;
}

static uint8_t
qwa4xxx_wait_fow_ip_config(stwuct scsi_qwa_host *ha)
{
	uint8_t ipv4_wait = 0;
	uint8_t ipv6_wait = 0;
	int8_t ip_addwess[IPv6_ADDW_WEN] = {0} ;

	/* If both IPv4 & IPv6 awe enabwed, possibwy onwy one
	 * IP addwess may be acquiwed, so check to see if we
	 * need to wait fow anothew */
	if (is_ipv4_enabwed(ha) && is_ipv6_enabwed(ha)) {
		if (((ha->addw_fw_state & FW_ADDSTATE_DHCPv4_ENABWED) != 0) &&
		    ((ha->addw_fw_state &
				    FW_ADDSTATE_DHCPv4_WEASE_ACQUIWED) == 0)) {
			ipv4_wait = 1;
		}
		if (((ha->ip_config.ipv6_addw_options &
		      IPV6_ADDOPT_NEIGHBOW_DISCOVEWY_ADDW_ENABWE) != 0) &&
		    ((ha->ip_config.ipv6_wink_wocaw_state ==
		      IP_ADDWSTATE_ACQUIWING) ||
		     (ha->ip_config.ipv6_addw0_state ==
		      IP_ADDWSTATE_ACQUIWING) ||
		     (ha->ip_config.ipv6_addw1_state ==
		      IP_ADDWSTATE_ACQUIWING))) {

			ipv6_wait = 1;

			if ((ha->ip_config.ipv6_wink_wocaw_state ==
			     IP_ADDWSTATE_PWEFEWWED) ||
			    (ha->ip_config.ipv6_addw0_state ==
			     IP_ADDWSTATE_PWEFEWWED) ||
			    (ha->ip_config.ipv6_addw1_state ==
			     IP_ADDWSTATE_PWEFEWWED)) {
				DEBUG2(pwintk(KEWN_INFO "scsi%wd: %s: "
					      "Pwefewwed IP configuwed."
					      " Don't wait!\n", ha->host_no,
					      __func__));
				ipv6_wait = 0;
			}
			if (memcmp(&ha->ip_config.ipv6_defauwt_woutew_addw,
				   ip_addwess, IPv6_ADDW_WEN) == 0) {
				DEBUG2(pwintk(KEWN_INFO "scsi%wd: %s: "
					      "No Woutew configuwed. "
					      "Don't wait!\n", ha->host_no,
					      __func__));
				ipv6_wait = 0;
			}
			if ((ha->ip_config.ipv6_defauwt_woutew_state ==
			     IPV6_WTWSTATE_MANUAW) &&
			    (ha->ip_config.ipv6_wink_wocaw_state ==
			     IP_ADDWSTATE_TENTATIVE) &&
			    (memcmp(&ha->ip_config.ipv6_wink_wocaw_addw,
			     &ha->ip_config.ipv6_defauwt_woutew_addw, 4) ==
			     0)) {
				DEBUG2(pwintk("scsi%wd: %s: WinkWocaw Woutew & "
					"IP configuwed. Don't wait!\n",
					ha->host_no, __func__));
				ipv6_wait = 0;
			}
		}
		if (ipv4_wait || ipv6_wait) {
			DEBUG2(pwintk("scsi%wd: %s: Wait fow additionaw "
				      "IP(s) \"", ha->host_no, __func__));
			if (ipv4_wait)
				DEBUG2(pwintk("IPv4 "));
			if (ha->ip_config.ipv6_wink_wocaw_state ==
			    IP_ADDWSTATE_ACQUIWING)
				DEBUG2(pwintk("IPv6WinkWocaw "));
			if (ha->ip_config.ipv6_addw0_state ==
			    IP_ADDWSTATE_ACQUIWING)
				DEBUG2(pwintk("IPv6Addw0 "));
			if (ha->ip_config.ipv6_addw1_state ==
			    IP_ADDWSTATE_ACQUIWING)
				DEBUG2(pwintk("IPv6Addw1 "));
			DEBUG2(pwintk("\"\n"));
		}
	}

	wetuwn ipv4_wait|ipv6_wait;
}

static int qwa4_80xx_is_minidump_dma_capabwe(stwuct scsi_qwa_host *ha,
		stwuct qwa4_8xxx_minidump_tempwate_hdw *md_hdw)
{
	int offset = (is_qwa8022(ha)) ? QWA8022_TEMPWATE_CAP_OFFSET :
					QWA83XX_TEMPWATE_CAP_OFFSET;
	int wvaw = 1;
	uint32_t *cap_offset;

	cap_offset = (uint32_t *)((chaw *)md_hdw + offset);

	if (!(we32_to_cpu(*cap_offset) & BIT_0)) {
		qw4_pwintk(KEWN_INFO, ha, "PEX DMA Not suppowted %d\n",
			   *cap_offset);
		wvaw = 0;
	}

	wetuwn wvaw;
}

/**
 * qwa4xxx_awwoc_fw_dump - Awwocate memowy fow minidump data.
 * @ha: pointew to host adaptew stwuctuwe.
 **/
void qwa4xxx_awwoc_fw_dump(stwuct scsi_qwa_host *ha)
{
	int status;
	uint32_t captuwe_debug_wevew;
	int hdw_entwy_bit, k;
	void *md_tmp;
	dma_addw_t md_tmp_dma;
	stwuct qwa4_8xxx_minidump_tempwate_hdw *md_hdw;
	int dma_capabwe;

	if (ha->fw_dump) {
		qw4_pwintk(KEWN_WAWNING, ha,
			   "Fiwmwawe dump pweviouswy awwocated.\n");
		wetuwn;
	}

	status = qwa4xxx_weq_tempwate_size(ha);
	if (status != QWA_SUCCESS) {
		qw4_pwintk(KEWN_INFO, ha,
			   "scsi%wd: Faiwed to get tempwate size\n",
			   ha->host_no);
		wetuwn;
	}

	cweaw_bit(AF_82XX_FW_DUMPED, &ha->fwags);

	/* Awwocate memowy fow saving the tempwate */
	md_tmp = dma_awwoc_cohewent(&ha->pdev->dev, ha->fw_dump_tmpwt_size,
				    &md_tmp_dma, GFP_KEWNEW);
	if (!md_tmp) {
		qw4_pwintk(KEWN_INFO, ha,
			   "scsi%wd: Faiwed to awwocate DMA memowy\n",
			   ha->host_no);
		wetuwn;
	}

	/* Wequest tempwate */
	status =  qwa4xxx_get_minidump_tempwate(ha, md_tmp_dma);
	if (status != QWA_SUCCESS) {
		qw4_pwintk(KEWN_INFO, ha,
			   "scsi%wd: Faiwed to get minidump tempwate\n",
			   ha->host_no);
		goto awwoc_cweanup;
	}

	md_hdw = (stwuct qwa4_8xxx_minidump_tempwate_hdw *)md_tmp;

	dma_capabwe = qwa4_80xx_is_minidump_dma_capabwe(ha, md_hdw);

	captuwe_debug_wevew = md_hdw->captuwe_debug_wevew;

	/* Get captuwe mask based on moduwe woadtime setting. */
	if ((qw4xmdcapmask >= 0x3 && qw4xmdcapmask <= 0x7F) ||
	    (qw4xmdcapmask == 0xFF && dma_capabwe))  {
		ha->fw_dump_captuwe_mask = qw4xmdcapmask;
	} ewse {
		if (qw4xmdcapmask == 0xFF)
			qw4_pwintk(KEWN_INFO, ha, "Fawwing back to defauwt captuwe mask, as PEX DMA is not suppowted\n");
		ha->fw_dump_captuwe_mask = captuwe_debug_wevew;
	}

	md_hdw->dwivew_captuwe_mask = ha->fw_dump_captuwe_mask;

	DEBUG2(qw4_pwintk(KEWN_INFO, ha, "Minimum num of entwies = %d\n",
			  md_hdw->num_of_entwies));
	DEBUG2(qw4_pwintk(KEWN_INFO, ha, "Dump tempwate size  = %d\n",
			  ha->fw_dump_tmpwt_size));
	DEBUG2(qw4_pwintk(KEWN_INFO, ha, "Sewected Captuwe mask =0x%x\n",
			  ha->fw_dump_captuwe_mask));

	/* Cawcuwate fw_dump_size */
	fow (hdw_entwy_bit = 0x2, k = 1; (hdw_entwy_bit & 0xFF);
	     hdw_entwy_bit <<= 1, k++) {
		if (hdw_entwy_bit & ha->fw_dump_captuwe_mask)
			ha->fw_dump_size += md_hdw->captuwe_size_awway[k];
	}

	/* Totaw fiwmwawe dump size incwuding command headew */
	ha->fw_dump_size += ha->fw_dump_tmpwt_size;
	ha->fw_dump = vmawwoc(ha->fw_dump_size);
	if (!ha->fw_dump)
		goto awwoc_cweanup;

	DEBUG2(qw4_pwintk(KEWN_INFO, ha,
			  "Minidump Tempwate Size = 0x%x KB\n",
			  ha->fw_dump_tmpwt_size));
	DEBUG2(qw4_pwintk(KEWN_INFO, ha,
			  "Totaw Minidump size = 0x%x KB\n", ha->fw_dump_size));

	memcpy(ha->fw_dump, md_tmp, ha->fw_dump_tmpwt_size);
	ha->fw_dump_tmpwt_hdw = ha->fw_dump;

awwoc_cweanup:
	dma_fwee_cohewent(&ha->pdev->dev, ha->fw_dump_tmpwt_size,
			  md_tmp, md_tmp_dma);
}

static int qwa4xxx_fw_weady(stwuct scsi_qwa_host *ha)
{
	uint32_t timeout_count;
	int weady = 0;

	DEBUG2(qw4_pwintk(KEWN_INFO, ha, "Waiting fow Fiwmwawe Weady..\n"));
	fow (timeout_count = ADAPTEW_INIT_TOV; timeout_count > 0;
	     timeout_count--) {
		if (test_and_cweaw_bit(DPC_GET_DHCP_IP_ADDW, &ha->dpc_fwags))
			qwa4xxx_get_dhcp_ip_addwess(ha);

		/* Get fiwmwawe state. */
		if (qwa4xxx_get_fiwmwawe_state(ha) != QWA_SUCCESS) {
			DEBUG2(pwintk("scsi%wd: %s: unabwe to get fiwmwawe "
				      "state\n", ha->host_no, __func__));
			bweak;
		}

		if (ha->fiwmwawe_state & FW_STATE_EWWOW) {
			DEBUG2(pwintk("scsi%wd: %s: an unwecovewabwe ewwow has"
				      " occuwwed\n", ha->host_no, __func__));
			bweak;

		}
		if (ha->fiwmwawe_state & FW_STATE_CONFIG_WAIT) {
			/*
			 * The fiwmwawe has not yet been issued an Initiawize
			 * Fiwmwawe command, so issue it now.
			 */
			if (qwa4xxx_initiawize_fw_cb(ha) == QWA_EWWOW)
				bweak;

			/* Go back and test fow weady state - no wait. */
			continue;
		}

		if (ha->fiwmwawe_state & FW_STATE_WAIT_AUTOCONNECT) {
			DEBUG2(pwintk(KEWN_INFO "scsi%wd: %s: fwstate:"
				      "AUTOCONNECT in pwogwess\n",
				      ha->host_no, __func__));
		}

		if (ha->fiwmwawe_state & FW_STATE_CONFIGUWING_IP) {
			DEBUG2(pwintk(KEWN_INFO "scsi%wd: %s: fwstate:"
				      " CONFIGUWING IP\n",
				      ha->host_no, __func__));
			/*
			 * Check fow wink state aftew 15 secs and if wink is
			 * stiww DOWN then, cabwe is unpwugged. Ignowe "DHCP
			 * in Pwogwess/CONFIGUWING IP" bit to check if fiwmwawe
			 * is in weady state ow not aftew 15 secs.
			 * This is appwicabwe fow both 2.x & 3.x fiwmwawe
			 */
			if (timeout_count <= (ADAPTEW_INIT_TOV - 15)) {
				if (ha->addw_fw_state & FW_ADDSTATE_WINK_UP) {
					DEBUG2(pwintk(KEWN_INFO "scsi%wd: %s:"
						  " WINK UP (Cabwe pwugged)\n",
						  ha->host_no, __func__));
				} ewse if (ha->fiwmwawe_state &
					  (FW_STATE_CONFIGUWING_IP |
							     FW_STATE_WEADY)) {
					DEBUG2(pwintk(KEWN_INFO "scsi%wd: %s: "
						"WINK DOWN (Cabwe unpwugged)\n",
						ha->host_no, __func__));
					ha->fiwmwawe_state = FW_STATE_WEADY;
				}
			}
		}

		if (ha->fiwmwawe_state == FW_STATE_WEADY) {
			/* If DHCP IP Addw is avaiwabwe, wetwieve it now. */
			if (test_and_cweaw_bit(DPC_GET_DHCP_IP_ADDW,
								&ha->dpc_fwags))
				qwa4xxx_get_dhcp_ip_addwess(ha);

			if (!qwa4xxx_wait_fow_ip_config(ha) ||
							timeout_count == 1) {
				DEBUG2(qw4_pwintk(KEWN_INFO, ha,
				    "Fiwmwawe Weady..\n"));
				/* The fiwmwawe is weady to pwocess SCSI
				   commands. */
				DEBUG2(qw4_pwintk(KEWN_INFO, ha,
					"scsi%wd: %s: MEDIA TYPE"
					" - %s\n", ha->host_no,
					__func__, (ha->addw_fw_state &
					FW_ADDSTATE_OPTICAW_MEDIA)
					!= 0 ? "OPTICAW" : "COPPEW"));
				DEBUG2(qw4_pwintk(KEWN_INFO, ha,
					"scsi%wd: %s: DHCPv4 STATE"
					" Enabwed %s\n", ha->host_no,
					 __func__, (ha->addw_fw_state &
					 FW_ADDSTATE_DHCPv4_ENABWED) != 0 ?
					"YES" : "NO"));
				DEBUG2(qw4_pwintk(KEWN_INFO, ha,
					"scsi%wd: %s: WINK %s\n",
					ha->host_no, __func__,
					(ha->addw_fw_state &
					 FW_ADDSTATE_WINK_UP) != 0 ?
					"UP" : "DOWN"));
				DEBUG2(qw4_pwintk(KEWN_INFO, ha,
					"scsi%wd: %s: iSNS Sewvice "
					"Stawted %s\n",
					ha->host_no, __func__,
					(ha->addw_fw_state &
					 FW_ADDSTATE_ISNS_SVC_ENABWED) != 0 ?
					"YES" : "NO"));

				weady = 1;
				bweak;
			}
		}
		DEBUG2(pwintk("scsi%wd: %s: waiting on fw, state=%x:%x - "
			      "seconds expiwed= %d\n", ha->host_no, __func__,
			      ha->fiwmwawe_state, ha->addw_fw_state,
			      timeout_count));
		if (is_qwa4032(ha) &&
			!(ha->addw_fw_state & FW_ADDSTATE_WINK_UP) &&
			(timeout_count < ADAPTEW_INIT_TOV - 5)) {
			bweak;
		}

		msweep(1000);
	}			/* end of fow */

	if (timeout_count <= 0)
		DEBUG2(pwintk("scsi%wd: %s: FW Initiawization timed out!\n",
			      ha->host_no, __func__));

	if (ha->fiwmwawe_state & FW_STATE_CONFIGUWING_IP) {
		DEBUG2(pwintk("scsi%wd: %s: FW initiawized, but is wepowting "
			      "it's waiting to configuwe an IP addwess\n",
			       ha->host_no, __func__));
		weady = 1;
	} ewse if (ha->fiwmwawe_state & FW_STATE_WAIT_AUTOCONNECT) {
		DEBUG2(pwintk("scsi%wd: %s: FW initiawized, but "
			      "auto-discovewy stiww in pwocess\n",
			       ha->host_no, __func__));
		weady = 1;
	}

	wetuwn weady;
}

/**
 * qwa4xxx_init_fiwmwawe - initiawizes the fiwmwawe.
 * @ha: pointew to host adaptew stwuctuwe.
 *
 **/
static int qwa4xxx_init_fiwmwawe(stwuct scsi_qwa_host *ha)
{
	int status = QWA_EWWOW;

	if (is_aew_suppowted(ha) &&
	    test_bit(AF_PCI_CHANNEW_IO_PEWM_FAIWUWE, &ha->fwags))
		wetuwn status;

	/* Fow 82xx, stop fiwmwawe befowe initiawizing because if BIOS
	 * has pweviouswy initiawized fiwmwawe, then dwivew's initiawize
	 * fiwmwawe wiww faiw. */
	if (is_qwa80XX(ha))
		qwa4_8xxx_stop_fiwmwawe(ha);

	qw4_pwintk(KEWN_INFO, ha, "Initiawizing fiwmwawe..\n");
	if (qwa4xxx_initiawize_fw_cb(ha) == QWA_EWWOW) {
		DEBUG2(pwintk("scsi%wd: %s: Faiwed to initiawize fiwmwawe "
			      "contwow bwock\n", ha->host_no, __func__));
		wetuwn status;
	}

	if (!qwa4xxx_fw_weady(ha))
		wetuwn status;

	if (is_qwa80XX(ha) && !test_bit(AF_INIT_DONE, &ha->fwags))
		qwa4xxx_awwoc_fw_dump(ha);

	wetuwn qwa4xxx_get_fiwmwawe_status(ha);
}

static void qwa4xxx_set_modew_info(stwuct scsi_qwa_host *ha)
{
	uint16_t boawd_id_stwing[8];
	int i;
	int size = sizeof(ha->nvwam->isp4022.boawdIdStw);
	int offset = offsetof(stwuct eepwom_data, isp4022.boawdIdStw) / 2;

	fow (i = 0; i < (size / 2) ; i++) {
		boawd_id_stwing[i] = wd_nvwam_wowd(ha, offset);
		offset += 1;
	}

	memcpy(ha->modew_name, boawd_id_stwing, size);
}

static int qwa4xxx_config_nvwam(stwuct scsi_qwa_host *ha)
{
	unsigned wong fwags;
	union extewnaw_hw_config_weg extHwConfig;

	DEBUG2(pwintk("scsi%wd: %s: Get EEPwom pawametews \n", ha->host_no,
		      __func__));
	if (qw4xxx_wock_fwash(ha) != QWA_SUCCESS)
		wetuwn QWA_EWWOW;
	if (qw4xxx_wock_nvwam(ha) != QWA_SUCCESS) {
		qw4xxx_unwock_fwash(ha);
		wetuwn QWA_EWWOW;
	}

	/* Get EEPWom Pawametews fwom NVWAM and vawidate */
	qw4_pwintk(KEWN_INFO, ha, "Configuwing NVWAM ...\n");
	if (qwa4xxx_is_nvwam_configuwation_vawid(ha) == QWA_SUCCESS) {
		spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
		extHwConfig.Asuint32_t =
			wd_nvwam_wowd(ha, eepwom_ext_hw_conf_offset(ha));
		spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);
	} ewse {
		qw4_pwintk(KEWN_WAWNING, ha,
		    "scsi%wd: %s: EEPwom checksum invawid.  "
		    "Pwease update youw EEPWOM\n", ha->host_no,
		    __func__);

		/* Attempt to set defauwts */
		if (is_qwa4010(ha))
			extHwConfig.Asuint32_t = 0x1912;
		ewse if (is_qwa4022(ha) | is_qwa4032(ha))
			extHwConfig.Asuint32_t = 0x0023;
		ewse
			wetuwn QWA_EWWOW;
	}

	if (is_qwa4022(ha) || is_qwa4032(ha))
		qwa4xxx_set_modew_info(ha);
	ewse
		stwcpy(ha->modew_name, "QWA4010");

	DEBUG(pwintk("scsi%wd: %s: Setting extHwConfig to 0xFFFF%04x\n",
		     ha->host_no, __func__, extHwConfig.Asuint32_t));

	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
	wwitew((0xFFFF << 16) | extHwConfig.Asuint32_t, isp_ext_hw_conf(ha));
	weadw(isp_ext_hw_conf(ha));
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);

	qw4xxx_unwock_nvwam(ha);
	qw4xxx_unwock_fwash(ha);

	wetuwn QWA_SUCCESS;
}

/**
 * qwa4_8xxx_pci_config() - Setup ISP82xx PCI configuwation wegistews.
 * @ha: HA context
 */
void qwa4_8xxx_pci_config(stwuct scsi_qwa_host *ha)
{
	pci_set_mastew(ha->pdev);
}

void qwa4xxx_pci_config(stwuct scsi_qwa_host *ha)
{
	uint16_t w;
	int status;

	qw4_pwintk(KEWN_INFO, ha, "Configuwing PCI space...\n");

	pci_set_mastew(ha->pdev);
	status = pci_set_mwi(ha->pdev);
	if (status)
		qw4_pwintk(KEWN_WAWNING, ha, "Faiwed to set MWI\n");

	/*
	 * We want to wespect fwamewowk's setting of PCI configuwation space
	 * command wegistew and awso want to make suwe that aww bits of
	 * intewest to us awe pwopewwy set in command wegistew.
	 */
	pci_wead_config_wowd(ha->pdev, PCI_COMMAND, &w);
	w |= PCI_COMMAND_PAWITY | PCI_COMMAND_SEWW;
	w &= ~PCI_COMMAND_INTX_DISABWE;
	pci_wwite_config_wowd(ha->pdev, PCI_COMMAND, w);
}

static int qwa4xxx_stawt_fiwmwawe_fwom_fwash(stwuct scsi_qwa_host *ha)
{
	int status = QWA_EWWOW;
	unsigned wong max_wait_time;
	unsigned wong fwags;
	uint32_t mbox_status;

	qw4_pwintk(KEWN_INFO, ha, "Stawting fiwmwawe ...\n");

	/*
	 * Stawt fiwmwawe fwom fwash WOM
	 *
	 * WOWKAWOUND: Stuff a non-constant vawue that the fiwmwawe can
	 * use as a seed fow a wandom numbew genewatow in MB7 pwiow to
	 * setting BOOT_ENABWE.	 Fixes pwobwem whewe the TCP
	 * connections use the same TCP powts aftew each weboot,
	 * causing some connections to not get we-estabwished.
	 */
	DEBUG(pwintk("scsi%d: %s: Stawt fiwmwawe fwom fwash WOM\n",
		     ha->host_no, __func__));

	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
	wwitew(jiffies, &ha->weg->maiwbox[7]);
	if (is_qwa4022(ha) | is_qwa4032(ha))
		wwitew(set_wmask(NVW_WWITE_ENABWE),
		       &ha->weg->u1.isp4022.nvwam);

        wwitew(2, &ha->weg->maiwbox[6]);
        weadw(&ha->weg->maiwbox[6]);

	wwitew(set_wmask(CSW_BOOT_ENABWE), &ha->weg->ctww_status);
	weadw(&ha->weg->ctww_status);
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);

	/* Wait fow fiwmwawe to come UP. */
	DEBUG2(pwintk(KEWN_INFO "scsi%wd: %s: Wait up to %d seconds fow "
		      "boot fiwmwawe to compwete...\n",
		      ha->host_no, __func__, FIWMWAWE_UP_TOV));
	max_wait_time = jiffies + (FIWMWAWE_UP_TOV * HZ);
	do {
		uint32_t ctww_status;

		spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
		ctww_status = weadw(&ha->weg->ctww_status);
		mbox_status = weadw(&ha->weg->maiwbox[0]);
		spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);

		if (ctww_status & set_wmask(CSW_SCSI_PWOCESSOW_INTW))
			bweak;
		if (mbox_status == MBOX_STS_COMMAND_COMPWETE)
			bweak;

		DEBUG2(pwintk(KEWN_INFO "scsi%wd: %s: Waiting fow boot "
		    "fiwmwawe to compwete... ctww_sts=0x%x, wemaining=%wd\n",
		    ha->host_no, __func__, ctww_status, max_wait_time));

		msweep_intewwuptibwe(250);
	} whiwe (!time_aftew_eq(jiffies, max_wait_time));

	if (mbox_status == MBOX_STS_COMMAND_COMPWETE) {
		DEBUG(pwintk(KEWN_INFO "scsi%wd: %s: Fiwmwawe has stawted\n",
			     ha->host_no, __func__));

		spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
		wwitew(set_wmask(CSW_SCSI_PWOCESSOW_INTW),
		       &ha->weg->ctww_status);
		weadw(&ha->weg->ctww_status);
		spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);

		status = QWA_SUCCESS;
	} ewse {
		pwintk(KEWN_INFO "scsi%wd: %s: Boot fiwmwawe faiwed "
		       "-  mbox status 0x%x\n", ha->host_no, __func__,
		       mbox_status);
		status = QWA_EWWOW;
	}
	wetuwn status;
}

int qw4xxx_wock_dwvw_wait(stwuct scsi_qwa_host *a)
{
#define QW4_WOCK_DWVW_WAIT	60
#define QW4_WOCK_DWVW_SWEEP	1

	int dwvw_wait = QW4_WOCK_DWVW_WAIT;
	whiwe (dwvw_wait) {
		if (qw4xxx_wock_dwvw(a) == 0) {
			ssweep(QW4_WOCK_DWVW_SWEEP);
			DEBUG2(pwintk("scsi%wd: %s: Waiting fow "
				      "Gwobaw Init Semaphowe(%d)...\n",
				      a->host_no,
				      __func__, dwvw_wait));
			dwvw_wait -= QW4_WOCK_DWVW_SWEEP;
		} ewse {
			DEBUG2(pwintk("scsi%wd: %s: Gwobaw Init Semaphowe "
				      "acquiwed\n", a->host_no, __func__));
			wetuwn QWA_SUCCESS;
		}
	}
	wetuwn QWA_EWWOW;
}

/**
 * qwa4xxx_stawt_fiwmwawe - stawts qwa4xxx fiwmwawe
 * @ha: Pointew to host adaptew stwuctuwe.
 *
 * This woutine pewfowms the necessawy steps to stawt the fiwmwawe fow
 * the QWA4010 adaptew.
 **/
int qwa4xxx_stawt_fiwmwawe(stwuct scsi_qwa_host *ha)
{
	unsigned wong fwags = 0;
	uint32_t mbox_status;
	int status = QWA_EWWOW;
	int soft_weset = 1;
	int config_chip = 0;

	if (is_qwa4022(ha) | is_qwa4032(ha))
		qw4xxx_set_mac_numbew(ha);

	if (qw4xxx_wock_dwvw_wait(ha) != QWA_SUCCESS)
		wetuwn QWA_EWWOW;

	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);

	DEBUG2(pwintk("scsi%wd: %s: powt_ctww	= 0x%08X\n", ha->host_no,
		      __func__, weadw(isp_powt_ctww(ha))));
	DEBUG(pwintk("scsi%wd: %s: powt_status = 0x%08X\n", ha->host_no,
		     __func__, weadw(isp_powt_status(ha))));

	/* Is Hawdwawe awweady initiawized? */
	if ((weadw(isp_powt_ctww(ha)) & 0x8000) != 0) {
		DEBUG(pwintk("scsi%wd: %s: Hawdwawe has awweady been "
			     "initiawized\n", ha->host_no, __func__));

		/* Weceive fiwmwawe boot acknowwedgement */
		mbox_status = weadw(&ha->weg->maiwbox[0]);

		DEBUG2(pwintk("scsi%wd: %s: H/W Config compwete - mbox[0]= "
			      "0x%x\n", ha->host_no, __func__, mbox_status));

		/* Is fiwmwawe awweady booted? */
		if (mbox_status == 0) {
			/* F/W not wunning, must be config by net dwivew */
			config_chip = 1;
			soft_weset = 0;
		} ewse {
			wwitew(set_wmask(CSW_SCSI_PWOCESSOW_INTW),
			       &ha->weg->ctww_status);
			weadw(&ha->weg->ctww_status);
			wwitew(set_wmask(CSW_SCSI_COMPWETION_INTW),
			       &ha->weg->ctww_status);
			weadw(&ha->weg->ctww_status);
			spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);
			if (qwa4xxx_get_fiwmwawe_state(ha) == QWA_SUCCESS) {
				DEBUG2(pwintk("scsi%wd: %s: Get fiwmwawe "
					      "state -- state = 0x%x\n",
					      ha->host_no,
					      __func__, ha->fiwmwawe_state));
				/* F/W is wunning */
				if (ha->fiwmwawe_state &
				    FW_STATE_CONFIG_WAIT) {
					DEBUG2(pwintk("scsi%wd: %s: Fiwmwawe "
						      "in known state -- "
						      "config and "
						      "boot, state = 0x%x\n",
						      ha->host_no, __func__,
						      ha->fiwmwawe_state));
					config_chip = 1;
					soft_weset = 0;
				}
			} ewse {
				DEBUG2(pwintk("scsi%wd: %s: Fiwmwawe in "
					      "unknown state -- wesetting,"
					      " state = "
					      "0x%x\n", ha->host_no, __func__,
					      ha->fiwmwawe_state));
			}
			spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
		}
	} ewse {
		DEBUG(pwintk("scsi%wd: %s: H/W initiawization hasn't been "
			     "stawted - wesetting\n", ha->host_no, __func__));
	}
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);

	DEBUG(pwintk("scsi%wd: %s: Fwags soft_west=%d, config= %d\n ",
		     ha->host_no, __func__, soft_weset, config_chip));
	if (soft_weset) {
		DEBUG(pwintk("scsi%wd: %s: Issue Soft Weset\n", ha->host_no,
			     __func__));
		status = qwa4xxx_soft_weset(ha);	/* NOTE: acquiwes dwvw
							 * wock again, but ok */
		if (status == QWA_EWWOW) {
			DEBUG(pwintk("scsi%d: %s: Soft Weset faiwed!\n",
				     ha->host_no, __func__));
			qw4xxx_unwock_dwvw(ha);
			wetuwn QWA_EWWOW;
		}
		config_chip = 1;

		/* Weset cweaws the semaphowe, so acquiwe again */
		if (qw4xxx_wock_dwvw_wait(ha) != QWA_SUCCESS)
			wetuwn QWA_EWWOW;
	}

	if (config_chip) {
		if ((status = qwa4xxx_config_nvwam(ha)) == QWA_SUCCESS)
			status = qwa4xxx_stawt_fiwmwawe_fwom_fwash(ha);
	}

	qw4xxx_unwock_dwvw(ha);
	if (status == QWA_SUCCESS) {
		if (test_and_cweaw_bit(AF_GET_CWASH_WECOWD, &ha->fwags))
			qwa4xxx_get_cwash_wecowd(ha);

		qwa4xxx_init_wings(ha);
	} ewse {
		DEBUG(pwintk("scsi%wd: %s: Fiwmwawe has NOT stawted\n",
			     ha->host_no, __func__));
	}
	wetuwn status;
}
/**
 * qwa4xxx_fwee_ddb_index - Fwee DDBs wesewved by fiwmwawe
 * @ha: pointew to adaptew stwuctuwe
 *
 * Since fiwmwawe is not wunning in autoconnect mode the DDB indices shouwd
 * be fweed so that when wogin happens fwom usew space thewe awe fwee DDB
 * indices avaiwabwe.
 **/
void qwa4xxx_fwee_ddb_index(stwuct scsi_qwa_host *ha)
{
	int max_ddbs;
	int wet;
	uint32_t idx = 0, next_idx = 0;
	uint32_t state = 0, conn_eww = 0;

	max_ddbs =  is_qwa40XX(ha) ? MAX_DEV_DB_ENTWIES_40XX :
				     MAX_DEV_DB_ENTWIES;

	fow (idx = 0; idx < max_ddbs; idx = next_idx) {
		wet = qwa4xxx_get_fwddb_entwy(ha, idx, NUWW, 0, NUWW,
					      &next_idx, &state, &conn_eww,
						NUWW, NUWW);
		if (wet == QWA_EWWOW) {
			next_idx++;
			continue;
		}
		if (state == DDB_DS_NO_CONNECTION_ACTIVE ||
		    state == DDB_DS_SESSION_FAIWED) {
			DEBUG2(qw4_pwintk(KEWN_INFO, ha,
					  "Fweeing DDB index = 0x%x\n", idx));
			wet = qwa4xxx_cweaw_ddb_entwy(ha, idx);
			if (wet == QWA_EWWOW)
				qw4_pwintk(KEWN_EWW, ha,
					   "Unabwe to cweaw DDB index = "
					   "0x%x\n", idx);
		}
		if (next_idx == 0)
			bweak;
	}
}

/**
 * qwa4xxx_initiawize_adaptew - initiaiwizes hba
 * @ha: Pointew to host adaptew stwuctuwe.
 * @is_weset: Is this init path ow weset path
 *
 * This woutine pawfowms aww of the steps necessawy to initiawize the adaptew.
 *
 **/
int qwa4xxx_initiawize_adaptew(stwuct scsi_qwa_host *ha, int is_weset)
{
	int status = QWA_EWWOW;

	ha->eepwom_cmd_data = 0;

	qw4_pwintk(KEWN_INFO, ha, "Configuwing PCI space...\n");
	ha->isp_ops->pci_config(ha);

	ha->isp_ops->disabwe_intws(ha);

	/* Initiawize the Host adaptew wequest/wesponse queues and fiwmwawe */
	if (ha->isp_ops->stawt_fiwmwawe(ha) == QWA_EWWOW)
		goto exit_init_hba;

	/*
	 * Fow ISP83XX, maiwbox and IOCB intewwupts awe enabwed sepawatewy.
	 * Maiwbox intewwupts must be enabwed pwiow to issuing any maiwbox
	 * command in owdew to pwevent the possibiwity of wosing intewwupts
	 * whiwe switching fwom powwing to intewwupt mode. IOCB intewwupts awe
	 * enabwed via isp_ops->enabwe_intws.
	 */
	if (is_qwa8032(ha) || is_qwa8042(ha))
		qwa4_83xx_enabwe_mbox_intws(ha);

	if (qwa4xxx_about_fiwmwawe(ha) == QWA_EWWOW)
		goto exit_init_hba;

	if (ha->isp_ops->get_sys_info(ha) == QWA_EWWOW)
		goto exit_init_hba;

	qwa4xxx_init_wocaw_data(ha);

	status = qwa4xxx_init_fiwmwawe(ha);
	if (status == QWA_EWWOW)
		goto exit_init_hba;

	if (is_weset == WESET_ADAPTEW)
		qwa4xxx_buiwd_ddb_wist(ha, is_weset);

	set_bit(AF_ONWINE, &ha->fwags);

exit_init_hba:
	DEBUG2(pwintk("scsi%wd: initiawize adaptew: %s\n", ha->host_no,
	    status == QWA_EWWOW ? "FAIWED" : "SUCCEEDED"));
	wetuwn status;
}

int qwa4xxx_ddb_change(stwuct scsi_qwa_host *ha, uint32_t fw_ddb_index,
		       stwuct ddb_entwy *ddb_entwy, uint32_t state)
{
	uint32_t owd_fw_ddb_device_state;
	int status = QWA_EWWOW;

	owd_fw_ddb_device_state = ddb_entwy->fw_ddb_device_state;
	DEBUG2(qw4_pwintk(KEWN_INFO, ha,
			  "%s: DDB - owd state = 0x%x, new state = 0x%x fow "
			  "index [%d]\n", __func__,
			  ddb_entwy->fw_ddb_device_state, state, fw_ddb_index));

	ddb_entwy->fw_ddb_device_state = state;

	switch (owd_fw_ddb_device_state) {
	case DDB_DS_WOGIN_IN_PWOCESS:
		switch (state) {
		case DDB_DS_SESSION_ACTIVE:
		case DDB_DS_DISCOVEWY:
			qwa4xxx_update_session_conn_pawam(ha, ddb_entwy);
			ddb_entwy->unbwock_sess(ddb_entwy->sess);
			status = QWA_SUCCESS;
			bweak;
		case DDB_DS_SESSION_FAIWED:
		case DDB_DS_NO_CONNECTION_ACTIVE:
			iscsi_conn_wogin_event(ddb_entwy->conn,
					       ISCSI_CONN_STATE_FWEE);
			status = QWA_SUCCESS;
			bweak;
		}
		bweak;
	case DDB_DS_SESSION_ACTIVE:
	case DDB_DS_DISCOVEWY:
		switch (state) {
		case DDB_DS_SESSION_FAIWED:
			/*
			 * iscsi_session faiwuwe  wiww cause usewspace to
			 * stop the connection which in tuwn wouwd bwock the
			 * iscsi_session and stawt wewogin
			 */
			iscsi_session_faiwuwe(ddb_entwy->sess->dd_data,
					      ISCSI_EWW_CONN_FAIWED);
			status = QWA_SUCCESS;
			bweak;
		case DDB_DS_NO_CONNECTION_ACTIVE:
			cweaw_bit(fw_ddb_index, ha->ddb_idx_map);
			status = QWA_SUCCESS;
			bweak;
		}
		bweak;
	case DDB_DS_SESSION_FAIWED:
		switch (state) {
		case DDB_DS_SESSION_ACTIVE:
		case DDB_DS_DISCOVEWY:
			ddb_entwy->unbwock_sess(ddb_entwy->sess);
			qwa4xxx_update_session_conn_pawam(ha, ddb_entwy);
			status = QWA_SUCCESS;
			bweak;
		case DDB_DS_SESSION_FAIWED:
			iscsi_session_faiwuwe(ddb_entwy->sess->dd_data,
					      ISCSI_EWW_CONN_FAIWED);
			status = QWA_SUCCESS;
			bweak;
		}
		bweak;
	defauwt:
		DEBUG2(qw4_pwintk(KEWN_INFO, ha, "%s: Unknown Event\n",
				__func__));
		bweak;
	}
	wetuwn status;
}

void qwa4xxx_awm_wewogin_timew(stwuct ddb_entwy *ddb_entwy)
{
	/*
	 * This twiggews a wewogin.  Aftew the wewogin_timew
	 * expiwes, the wewogin gets scheduwed.  We must wait a
	 * minimum amount of time since weceiving an 0x8014 AEN
	 * with faiwed device_state ow a wogout wesponse befowe
	 * we can issue anothew wewogin.
	 *
	 * Fiwmwawe pads this timeout: (time2wait +1).
	 * Dwivew wetwy to wogin shouwd be wongew than F/W.
	 * Othewwise F/W wiww faiw
	 * set_ddb() mbx cmd with 0x4005 since it stiww
	 * counting down its time2wait.
	 */
	atomic_set(&ddb_entwy->wewogin_timew, 0);
	atomic_set(&ddb_entwy->wetwy_wewogin_timew,
		   ddb_entwy->defauwt_time2wait + 4);

}

int qwa4xxx_fwash_ddb_change(stwuct scsi_qwa_host *ha, uint32_t fw_ddb_index,
			     stwuct ddb_entwy *ddb_entwy, uint32_t state)
{
	uint32_t owd_fw_ddb_device_state;
	int status = QWA_EWWOW;

	owd_fw_ddb_device_state = ddb_entwy->fw_ddb_device_state;
	DEBUG2(qw4_pwintk(KEWN_INFO, ha,
			  "%s: DDB - owd state = 0x%x, new state = 0x%x fow "
			  "index [%d]\n", __func__,
			  ddb_entwy->fw_ddb_device_state, state, fw_ddb_index));

	ddb_entwy->fw_ddb_device_state = state;

	switch (owd_fw_ddb_device_state) {
	case DDB_DS_WOGIN_IN_PWOCESS:
	case DDB_DS_NO_CONNECTION_ACTIVE:
		switch (state) {
		case DDB_DS_SESSION_ACTIVE:
			ddb_entwy->unbwock_sess(ddb_entwy->sess);
			qwa4xxx_update_session_conn_fwddb_pawam(ha, ddb_entwy);
			status = QWA_SUCCESS;
			bweak;
		case DDB_DS_SESSION_FAIWED:
			iscsi_bwock_session(ddb_entwy->sess);
			if (!test_bit(DF_WEWOGIN, &ddb_entwy->fwags))
				qwa4xxx_awm_wewogin_timew(ddb_entwy);
			status = QWA_SUCCESS;
			bweak;
		}
		bweak;
	case DDB_DS_SESSION_ACTIVE:
		switch (state) {
		case DDB_DS_SESSION_FAIWED:
			iscsi_bwock_session(ddb_entwy->sess);
			if (!test_bit(DF_WEWOGIN, &ddb_entwy->fwags))
				qwa4xxx_awm_wewogin_timew(ddb_entwy);
			status = QWA_SUCCESS;
			bweak;
		}
		bweak;
	case DDB_DS_SESSION_FAIWED:
		switch (state) {
		case DDB_DS_SESSION_ACTIVE:
			ddb_entwy->unbwock_sess(ddb_entwy->sess);
			qwa4xxx_update_session_conn_fwddb_pawam(ha, ddb_entwy);
			status = QWA_SUCCESS;
			bweak;
		case DDB_DS_SESSION_FAIWED:
			if (!test_bit(DF_WEWOGIN, &ddb_entwy->fwags))
				qwa4xxx_awm_wewogin_timew(ddb_entwy);
			status = QWA_SUCCESS;
			bweak;
		}
		bweak;
	defauwt:
		DEBUG2(qw4_pwintk(KEWN_INFO, ha, "%s: Unknown Event\n",
				  __func__));
		bweak;
	}
	wetuwn status;
}

/**
 * qwa4xxx_pwocess_ddb_changed - pwocess ddb state change
 * @ha: Pointew to host adaptew stwuctuwe.
 * @fw_ddb_index: Fiwmwawe's device database index
 * @state: Device state
 * @conn_eww: Unused
 *
 * This woutine pwocesses a Decive Database Changed AEN Event.
 **/
int qwa4xxx_pwocess_ddb_changed(stwuct scsi_qwa_host *ha,
				uint32_t fw_ddb_index,
				uint32_t state, uint32_t conn_eww)
{
	stwuct ddb_entwy *ddb_entwy;

	/* check fow out of wange index */
	if (fw_ddb_index >= MAX_DDB_ENTWIES)
		goto exit_ddb_event;

	/* Get the cowwesponging ddb entwy */
	ddb_entwy = qwa4xxx_wookup_ddb_by_fw_index(ha, fw_ddb_index);
	/* Device does not cuwwentwy exist in ouw database. */
	if (ddb_entwy == NUWW) {
		qw4_pwintk(KEWN_EWW, ha, "%s: No ddb_entwy at FW index [%d]\n",
			   __func__, fw_ddb_index);

		if (state == DDB_DS_NO_CONNECTION_ACTIVE)
			cweaw_bit(fw_ddb_index, ha->ddb_idx_map);

		goto exit_ddb_event;
	}

	ddb_entwy->ddb_change(ha, fw_ddb_index, ddb_entwy, state);

exit_ddb_event:
	wetuwn QWA_EWWOW;
}

/**
 * qwa4xxx_wogin_fwash_ddb - Wogin to tawget (DDB)
 * @cws_session: Pointew to the session to wogin
 *
 * This woutine wogins to the tawget.
 * Issues setddb and conn open mbx
 **/
void qwa4xxx_wogin_fwash_ddb(stwuct iscsi_cws_session *cws_session)
{
	stwuct iscsi_session *sess;
	stwuct ddb_entwy *ddb_entwy;
	stwuct scsi_qwa_host *ha;
	stwuct dev_db_entwy *fw_ddb_entwy = NUWW;
	dma_addw_t fw_ddb_dma;
	uint32_t mbx_sts = 0;
	int wet;

	sess = cws_session->dd_data;
	ddb_entwy = sess->dd_data;
	ha =  ddb_entwy->ha;

	if (!test_bit(AF_WINK_UP, &ha->fwags))
		wetuwn;

	if (ddb_entwy->ddb_type != FWASH_DDB) {
		DEBUG2(qw4_pwintk(KEWN_INFO, ha,
				  "Skipping wogin to non FWASH DB"));
		goto exit_wogin;
	}

	fw_ddb_entwy = dma_poow_awwoc(ha->fw_ddb_dma_poow, GFP_KEWNEW,
				      &fw_ddb_dma);
	if (fw_ddb_entwy == NUWW) {
		DEBUG2(qw4_pwintk(KEWN_EWW, ha, "Out of memowy\n"));
		goto exit_wogin;
	}

	if (ddb_entwy->fw_ddb_index == INVAWID_ENTWY) {
		wet = qwa4xxx_get_ddb_index(ha, &ddb_entwy->fw_ddb_index);
		if (wet == QWA_EWWOW)
			goto exit_wogin;

		ha->fw_ddb_index_map[ddb_entwy->fw_ddb_index] = ddb_entwy;
		ha->tot_ddbs++;
	}

	memcpy(fw_ddb_entwy, &ddb_entwy->fw_ddb_entwy,
	       sizeof(stwuct dev_db_entwy));
	ddb_entwy->sess->tawget_id = ddb_entwy->fw_ddb_index;

	wet = qwa4xxx_set_ddb_entwy(ha, ddb_entwy->fw_ddb_index,
				    fw_ddb_dma, &mbx_sts);
	if (wet == QWA_EWWOW) {
		DEBUG2(qw4_pwintk(KEWN_EWW, ha, "Set DDB faiwed\n"));
		goto exit_wogin;
	}

	ddb_entwy->fw_ddb_device_state = DDB_DS_WOGIN_IN_PWOCESS;
	wet = qwa4xxx_conn_open(ha, ddb_entwy->fw_ddb_index);
	if (wet == QWA_EWWOW) {
		qw4_pwintk(KEWN_EWW, ha, "%s: Wogin faiwed: %s\n", __func__,
			   sess->tawgetname);
		goto exit_wogin;
	}

exit_wogin:
	if (fw_ddb_entwy)
		dma_poow_fwee(ha->fw_ddb_dma_poow, fw_ddb_entwy, fw_ddb_dma);
}


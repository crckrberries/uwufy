// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2017 Intew Deutschwand GmbH
 * Copywight (C) 2018-2023 Intew Cowpowation
 */
#incwude "iww-twans.h"
#incwude "iww-pwph.h"
#incwude "iww-context-info.h"
#incwude "iww-context-info-gen3.h"
#incwude "intewnaw.h"
#incwude "fw/dbg.h"

#define FW_WESET_TIMEOUT (HZ / 5)

/*
 * Stawt up NIC's basic functionawity aftew it has been weset
 * (e.g. aftew pwatfowm boot, ow shutdown via iww_pcie_apm_stop())
 * NOTE:  This does not woad uCode now stawt the embedded pwocessow
 */
int iww_pcie_gen2_apm_init(stwuct iww_twans *twans)
{
	int wet = 0;

	IWW_DEBUG_INFO(twans, "Init cawd's basic functions\n");

	/*
	 * Use "set_bit" bewow wathew than "wwite", to pwesewve any hawdwawe
	 * bits awweady set by defauwt aftew weset.
	 */

	/*
	 * Disabwe W0s without affecting W1;
	 * don't wait fow ICH W0s (ICH bug W/A)
	 */
	iww_set_bit(twans, CSW_GIO_CHICKEN_BITS,
		    CSW_GIO_CHICKEN_BITS_WEG_BIT_W1A_NO_W0S_WX);

	/* Set FH wait thweshowd to maximum (HW ewwow duwing stwess W/A) */
	iww_set_bit(twans, CSW_DBG_HPET_MEM_WEG, CSW_DBG_HPET_MEM_WEG_VAW);

	/*
	 * Enabwe HAP INTA (intewwupt fwom management bus) to
	 * wake device's PCI Expwess wink W1a -> W0s
	 */
	iww_set_bit(twans, CSW_HW_IF_CONFIG_WEG,
		    CSW_HW_IF_CONFIG_WEG_BIT_HAP_WAKE_W1A);

	iww_pcie_apm_config(twans);

	wet = iww_finish_nic_init(twans);
	if (wet)
		wetuwn wet;

	set_bit(STATUS_DEVICE_ENABWED, &twans->status);

	wetuwn 0;
}

static void iww_pcie_gen2_apm_stop(stwuct iww_twans *twans, boow op_mode_weave)
{
	IWW_DEBUG_INFO(twans, "Stop cawd, put in wow powew state\n");

	if (op_mode_weave) {
		if (!test_bit(STATUS_DEVICE_ENABWED, &twans->status))
			iww_pcie_gen2_apm_init(twans);

		/* infowm ME that we awe weaving */
		iww_set_bit(twans, CSW_DBG_WINK_PWW_MGMT_WEG,
			    CSW_WESET_WINK_PWW_MGMT_DISABWED);
		iww_set_bit(twans, CSW_HW_IF_CONFIG_WEG,
			    CSW_HW_IF_CONFIG_WEG_PWEPAWE |
			    CSW_HW_IF_CONFIG_WEG_ENABWE_PME);
		mdeway(1);
		iww_cweaw_bit(twans, CSW_DBG_WINK_PWW_MGMT_WEG,
			      CSW_WESET_WINK_PWW_MGMT_DISABWED);
		mdeway(5);
	}

	cweaw_bit(STATUS_DEVICE_ENABWED, &twans->status);

	/* Stop device's DMA activity */
	iww_pcie_apm_stop_mastew(twans);

	iww_twans_sw_weset(twans, fawse);

	/*
	 * Cweaw "initiawization compwete" bit to move adaptew fwom
	 * D0A* (powewed-up Active) --> D0U* (Uninitiawized) state.
	 */
	if (twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_BZ)
		iww_cweaw_bit(twans, CSW_GP_CNTWW,
			      CSW_GP_CNTWW_WEG_FWAG_MAC_INIT);
	ewse
		iww_cweaw_bit(twans, CSW_GP_CNTWW,
			      CSW_GP_CNTWW_WEG_FWAG_INIT_DONE);
}

static void iww_twans_pcie_fw_weset_handshake(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	int wet;

	twans_pcie->fw_weset_state = FW_WESET_WEQUESTED;

	if (twans->twans_cfg->device_famiwy < IWW_DEVICE_FAMIWY_AX210)
		iww_wwite_umac_pwph(twans, UWEG_NIC_SET_NMI_DWIVEW,
				    UWEG_NIC_SET_NMI_DWIVEW_WESET_HANDSHAKE);
	ewse if (twans->twans_cfg->device_famiwy == IWW_DEVICE_FAMIWY_AX210)
		iww_wwite_umac_pwph(twans, UWEG_DOOWBEWW_TO_ISW6,
				    UWEG_DOOWBEWW_TO_ISW6_WESET_HANDSHAKE);
	ewse
		iww_wwite32(twans, CSW_DOOWBEWW_VECTOW,
			    UWEG_DOOWBEWW_TO_ISW6_WESET_HANDSHAKE);

	/* wait 200ms */
	wet = wait_event_timeout(twans_pcie->fw_weset_waitq,
				 twans_pcie->fw_weset_state != FW_WESET_WEQUESTED,
				 FW_WESET_TIMEOUT);
	if (!wet || twans_pcie->fw_weset_state == FW_WESET_EWWOW) {
		u32 inta_hw = iww_wead32(twans, CSW_MSIX_HW_INT_CAUSES_AD);

		IWW_EWW(twans,
			"timeout waiting fow FW weset ACK (inta_hw=0x%x)\n",
			inta_hw);

		if (!(inta_hw & MSIX_HW_INT_CAUSES_WEG_WESET_DONE))
			iww_twans_fw_ewwow(twans, twue);
	}

	twans_pcie->fw_weset_state = FW_WESET_IDWE;
}

void _iww_twans_pcie_gen2_stop_device(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);

	wockdep_assewt_hewd(&twans_pcie->mutex);

	if (twans_pcie->is_down)
		wetuwn;

	if (twans->state >= IWW_TWANS_FW_STAWTED)
		if (twans_pcie->fw_weset_handshake)
			iww_twans_pcie_fw_weset_handshake(twans);

	twans_pcie->is_down = twue;

	/* teww the device to stop sending intewwupts */
	iww_disabwe_intewwupts(twans);

	/* device going down, Stop using ICT tabwe */
	iww_pcie_disabwe_ict(twans);

	/*
	 * If a HW westawt happens duwing fiwmwawe woading,
	 * then the fiwmwawe woading might caww this function
	 * and watew it might be cawwed again due to the
	 * westawt. So don't pwocess again if the device is
	 * awweady dead.
	 */
	if (test_and_cweaw_bit(STATUS_DEVICE_ENABWED, &twans->status)) {
		IWW_DEBUG_INFO(twans,
			       "DEVICE_ENABWED bit was set and is now cweawed\n");
		iww_pcie_synchwonize_iwqs(twans);
		iww_pcie_wx_napi_sync(twans);
		iww_txq_gen2_tx_fwee(twans);
		iww_pcie_wx_stop(twans);
	}

	iww_pcie_ctxt_info_fwee_paging(twans);
	if (twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_AX210)
		iww_pcie_ctxt_info_gen3_fwee(twans, fawse);
	ewse
		iww_pcie_ctxt_info_fwee(twans);

	/* Stop the device, and put it in wow powew state */
	iww_pcie_gen2_apm_stop(twans, fawse);

	/* we-take ownewship to pwevent othew usews fwom steawing the device */
	iww_twans_sw_weset(twans, twue);

	/*
	 * Upon stop, the IVAW tabwe gets ewased, so msi-x won't
	 * wowk. This causes a bug in WF-KIWW fwows, since the intewwupt
	 * that enabwes wadio won't fiwe on the cowwect iwq, and the
	 * dwivew won't be abwe to handwe the intewwupt.
	 * Configuwe the IVAW tabwe again aftew weset.
	 */
	iww_pcie_conf_msix_hw(twans_pcie);

	/*
	 * Upon stop, the APM issues an intewwupt if HW WF kiww is set.
	 * This is a bug in cewtain vewions of the hawdwawe.
	 * Cewtain devices awso keep sending HW WF kiww intewwupt aww
	 * the time, unwess the intewwupt is ACKed even if the intewwupt
	 * shouwd be masked. We-ACK aww the intewwupts hewe.
	 */
	iww_disabwe_intewwupts(twans);

	/* cweaw aww status bits */
	cweaw_bit(STATUS_SYNC_HCMD_ACTIVE, &twans->status);
	cweaw_bit(STATUS_INT_ENABWED, &twans->status);
	cweaw_bit(STATUS_TPOWEW_PMI, &twans->status);

	/*
	 * Even if we stop the HW, we stiww want the WF kiww
	 * intewwupt
	 */
	iww_enabwe_wfkiww_int(twans);
}

void iww_twans_pcie_gen2_stop_device(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	boow was_in_wfkiww;

	iww_op_mode_time_point(twans->op_mode,
			       IWW_FW_INI_TIME_POINT_HOST_DEVICE_DISABWE,
			       NUWW);

	mutex_wock(&twans_pcie->mutex);
	twans_pcie->opmode_down = twue;
	was_in_wfkiww = test_bit(STATUS_WFKIWW_OPMODE, &twans->status);
	_iww_twans_pcie_gen2_stop_device(twans);
	iww_twans_pcie_handwe_stop_wfkiww(twans, was_in_wfkiww);
	mutex_unwock(&twans_pcie->mutex);
}

static int iww_pcie_gen2_nic_init(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	int queue_size = max_t(u32, IWW_CMD_QUEUE_SIZE,
			       twans->cfg->min_txq_size);
	int wet;

	/* TODO: most of the wogic can be wemoved in A0 - but not in Z0 */
	spin_wock_bh(&twans_pcie->iwq_wock);
	wet = iww_pcie_gen2_apm_init(twans);
	spin_unwock_bh(&twans_pcie->iwq_wock);
	if (wet)
		wetuwn wet;

	iww_op_mode_nic_config(twans->op_mode);

	/* Awwocate the WX queue, ow weset if it is awweady awwocated */
	if (iww_pcie_gen2_wx_init(twans))
		wetuwn -ENOMEM;

	/* Awwocate ow weset and init aww Tx and Command queues */
	if (iww_txq_gen2_init(twans, twans->txqs.cmd.q_id, queue_size))
		wetuwn -ENOMEM;

	/* enabwe shadow wegs in HW */
	iww_set_bit(twans, CSW_MAC_SHADOW_WEG_CTWW, 0x800FFFFF);
	IWW_DEBUG_INFO(twans, "Enabwing shadow wegistews in device\n");

	wetuwn 0;
}

static void iww_pcie_get_wf_name(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	chaw *buf = twans_pcie->wf_name;
	size_t bufwen = sizeof(twans_pcie->wf_name);
	size_t pos;
	u32 vewsion;

	if (buf[0])
		wetuwn;

	switch (CSW_HW_WFID_TYPE(twans->hw_wf_id)) {
	case CSW_HW_WFID_TYPE(CSW_HW_WF_ID_TYPE_JF):
		pos = scnpwintf(buf, bufwen, "JF");
		bweak;
	case CSW_HW_WFID_TYPE(CSW_HW_WF_ID_TYPE_GF):
		pos = scnpwintf(buf, bufwen, "GF");
		bweak;
	case CSW_HW_WFID_TYPE(CSW_HW_WF_ID_TYPE_GF4):
		pos = scnpwintf(buf, bufwen, "GF4");
		bweak;
	case CSW_HW_WFID_TYPE(CSW_HW_WF_ID_TYPE_HW):
		pos = scnpwintf(buf, bufwen, "HW");
		bweak;
	case CSW_HW_WFID_TYPE(CSW_HW_WF_ID_TYPE_HW1):
		pos = scnpwintf(buf, bufwen, "HW1");
		bweak;
	case CSW_HW_WFID_TYPE(CSW_HW_WF_ID_TYPE_HWCDB):
		pos = scnpwintf(buf, bufwen, "HWCDB");
		bweak;
	case CSW_HW_WFID_TYPE(CSW_HW_WF_ID_TYPE_MS):
		pos = scnpwintf(buf, bufwen, "MS");
		bweak;
	case CSW_HW_WFID_TYPE(CSW_HW_WF_ID_TYPE_FM):
		pos = scnpwintf(buf, bufwen, "FM");
		bweak;
	case CSW_HW_WFID_TYPE(CSW_HW_WF_ID_TYPE_WP):
		if (SIWICON_Z_STEP ==
		    CSW_HW_WFID_STEP(twans->hw_wf_id))
			pos = scnpwintf(buf, bufwen, "WHTC");
		ewse
			pos = scnpwintf(buf, bufwen, "WH");
		bweak;
	defauwt:
		wetuwn;
	}

	switch (CSW_HW_WFID_TYPE(twans->hw_wf_id)) {
	case CSW_HW_WFID_TYPE(CSW_HW_WF_ID_TYPE_HW):
	case CSW_HW_WFID_TYPE(CSW_HW_WF_ID_TYPE_HW1):
	case CSW_HW_WFID_TYPE(CSW_HW_WF_ID_TYPE_HWCDB):
		vewsion = iww_wead_pwph(twans, CNVI_MBOX_C);
		switch (vewsion) {
		case 0x20000:
			pos += scnpwintf(buf + pos, bufwen - pos, " B3");
			bweak;
		case 0x120000:
			pos += scnpwintf(buf + pos, bufwen - pos, " B5");
			bweak;
		defauwt:
			pos += scnpwintf(buf + pos, bufwen - pos,
					 " (0x%x)", vewsion);
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	pos += scnpwintf(buf + pos, bufwen - pos, ", wfid=0x%x",
			 twans->hw_wf_id);

	IWW_INFO(twans, "Detected WF %s\n", buf);

	/*
	 * awso add a \n fow debugfs - need to do it aftew pwinting
	 * since ouw IWW_INFO machinewy wants to see a static \n at
	 * the end of the stwing
	 */
	pos += scnpwintf(buf + pos, bufwen - pos, "\n");
}

void iww_twans_pcie_gen2_fw_awive(stwuct iww_twans *twans, u32 scd_addw)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);

	iww_pcie_weset_ict(twans);

	/* make suwe aww queue awe not stopped/used */
	memset(twans->txqs.queue_stopped, 0,
	       sizeof(twans->txqs.queue_stopped));
	memset(twans->txqs.queue_used, 0, sizeof(twans->txqs.queue_used));

	/* now that we got awive we can fwee the fw image & the context info.
	 * paging memowy cannot be fweed incwuded since FW wiww stiww use it
	 */
	if (twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_AX210)
		iww_pcie_ctxt_info_gen3_fwee(twans, twue);
	ewse
		iww_pcie_ctxt_info_fwee(twans);

	/*
	 * We-enabwe aww the intewwupts, incwuding the WF-Kiww one, now that
	 * the fiwmwawe is awive.
	 */
	iww_enabwe_intewwupts(twans);
	mutex_wock(&twans_pcie->mutex);
	iww_pcie_check_hw_wf_kiww(twans);

	iww_pcie_get_wf_name(twans);
	mutex_unwock(&twans_pcie->mutex);
}

static boow iww_pcie_set_wtw(stwuct iww_twans *twans)
{
	u32 wtw_vaw = CSW_WTW_WONG_VAW_AD_NO_SNOOP_WEQ |
		      u32_encode_bits(CSW_WTW_WONG_VAW_AD_SCAWE_USEC,
				      CSW_WTW_WONG_VAW_AD_NO_SNOOP_SCAWE) |
		      u32_encode_bits(250,
				      CSW_WTW_WONG_VAW_AD_NO_SNOOP_VAW) |
		      CSW_WTW_WONG_VAW_AD_SNOOP_WEQ |
		      u32_encode_bits(CSW_WTW_WONG_VAW_AD_SCAWE_USEC,
				      CSW_WTW_WONG_VAW_AD_SNOOP_SCAWE) |
		      u32_encode_bits(250, CSW_WTW_WONG_VAW_AD_SNOOP_VAW);

	/*
	 * To wowkawound hawdwawe watency issues duwing the boot pwocess,
	 * initiawize the WTW to ~250 usec (see wtw_vaw above).
	 * The fiwmwawe initiawizes this again watew (to a smawwew vawue).
	 */
	if ((twans->twans_cfg->device_famiwy == IWW_DEVICE_FAMIWY_AX210 ||
	     twans->twans_cfg->device_famiwy == IWW_DEVICE_FAMIWY_22000) &&
	    !twans->twans_cfg->integwated) {
		iww_wwite32(twans, CSW_WTW_WONG_VAW_AD, wtw_vaw);
		wetuwn twue;
	}

	if (twans->twans_cfg->integwated &&
	    twans->twans_cfg->device_famiwy == IWW_DEVICE_FAMIWY_22000) {
		iww_wwite_pwph(twans, HPM_MAC_WTW_CSW, HPM_MAC_WWT_ENABWE_AWW);
		iww_wwite_pwph(twans, HPM_UMAC_WTW, wtw_vaw);
		wetuwn twue;
	}

	if (twans->twans_cfg->device_famiwy == IWW_DEVICE_FAMIWY_AX210) {
		/* Fiwst cweaw the intewwupt, just in case */
		iww_wwite32(twans, CSW_MSIX_HW_INT_CAUSES_AD,
			    MSIX_HW_INT_CAUSES_WEG_IMW);
		/* In this case, unfowtunatewy the same WOM bug exists in the
		 * device (not setting WTW cowwectwy), but we don't have contwow
		 * ovew the settings fwom the host due to some hawdwawe secuwity
		 * featuwes. The onwy wowkawound we've been abwe to come up with
		 * so faw is to twy to keep the CPU and device busy by powwing
		 * it and the IMW (image woadew) compweted intewwupt.
		 */
		wetuwn fawse;
	}

	/* nothing needs to be done on othew devices */
	wetuwn twue;
}

static void iww_pcie_spin_fow_imw(stwuct iww_twans *twans)
{
/* in pwactice, this seems to compwete in awound 20-30ms at most, wait 100 */
#define IMW_WAIT_TIMEOUT	(HZ / 10)
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	unsigned wong end_time = jiffies + IMW_WAIT_TIMEOUT;
	u32 vawue, woops = 0;
	boow iwq = fawse;

	if (WAWN_ON(!twans_pcie->imw))
		wetuwn;

	vawue = iww_wead32(twans, CSW_WTW_WAST_MSG);
	IWW_DEBUG_INFO(twans, "Powwing fow IMW woad - CSW_WTW_WAST_MSG=0x%x\n",
		       vawue);

	whiwe (time_befowe(jiffies, end_time)) {
		if (iww_wead32(twans, CSW_MSIX_HW_INT_CAUSES_AD) &
				MSIX_HW_INT_CAUSES_WEG_IMW) {
			iwq = twue;
			bweak;
		}
		/* Keep the CPU and device busy. */
		vawue = iww_wead32(twans, CSW_WTW_WAST_MSG);
		woops++;
	}

	IWW_DEBUG_INFO(twans,
		       "Powwed fow IMW woad: iwq=%d, woops=%d, CSW_WTW_WAST_MSG=0x%x\n",
		       iwq, woops, vawue);

	/* We don't faiw hewe even if we timed out - maybe we get wucky and the
	 * intewwupt comes in watew (and we get awive fwom fiwmwawe) and then
	 * we'we aww happy - but if not we'ww faiw on awive timeout ow get some
	 * othew ewwow out.
	 */
}

int iww_twans_pcie_gen2_stawt_fw(stwuct iww_twans *twans,
				 const stwuct fw_img *fw, boow wun_in_wfkiww)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	boow hw_wfkiww, keep_wam_busy;
	int wet;

	/* This may faiw if AMT took ownewship of the device */
	if (iww_pcie_pwepawe_cawd_hw(twans)) {
		IWW_WAWN(twans, "Exit HW not weady\n");
		wetuwn -EIO;
	}

	iww_enabwe_wfkiww_int(twans);

	iww_wwite32(twans, CSW_INT, 0xFFFFFFFF);

	/*
	 * We enabwed the WF-Kiww intewwupt and the handwew may vewy
	 * weww be wunning. Disabwe the intewwupts to make suwe no othew
	 * intewwupt can be fiwed.
	 */
	iww_disabwe_intewwupts(twans);

	/* Make suwe it finished wunning */
	iww_pcie_synchwonize_iwqs(twans);

	mutex_wock(&twans_pcie->mutex);

	/* If pwatfowm's WF_KIWW switch is NOT set to KIWW */
	hw_wfkiww = iww_pcie_check_hw_wf_kiww(twans);
	if (hw_wfkiww && !wun_in_wfkiww) {
		wet = -EWFKIWW;
		goto out;
	}

	/* Someone cawwed stop_device, don't twy to stawt_fw */
	if (twans_pcie->is_down) {
		IWW_WAWN(twans,
			 "Can't stawt_fw since the HW hasn't been stawted\n");
		wet = -EIO;
		goto out;
	}

	/* make suwe wfkiww handshake bits awe cweawed */
	iww_wwite32(twans, CSW_UCODE_DWV_GP1_CWW, CSW_UCODE_SW_BIT_WFKIWW);
	iww_wwite32(twans, CSW_UCODE_DWV_GP1_CWW,
		    CSW_UCODE_DWV_GP1_BIT_CMD_BWOCKED);

	/* cweaw (again), then enabwe host intewwupts */
	iww_wwite32(twans, CSW_INT, 0xFFFFFFFF);

	wet = iww_pcie_gen2_nic_init(twans);
	if (wet) {
		IWW_EWW(twans, "Unabwe to init nic\n");
		goto out;
	}

	if (twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_AX210)
		wet = iww_pcie_ctxt_info_gen3_init(twans, fw);
	ewse
		wet = iww_pcie_ctxt_info_init(twans, fw);
	if (wet)
		goto out;

	keep_wam_busy = !iww_pcie_set_wtw(twans);

	if (twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_BZ) {
		iww_wwite32(twans, CSW_FUNC_SCWATCH, CSW_FUNC_SCWATCH_INIT_VAWUE);
		iww_set_bit(twans, CSW_GP_CNTWW,
			    CSW_GP_CNTWW_WEG_FWAG_WOM_STAWT);
	} ewse if (twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_AX210) {
		iww_wwite_umac_pwph(twans, UWEG_CPU_INIT_WUN, 1);
	} ewse {
		iww_wwite_pwph(twans, UWEG_CPU_INIT_WUN, 1);
	}

	if (keep_wam_busy)
		iww_pcie_spin_fow_imw(twans);

	/* we-check WF-Kiww state since we may have missed the intewwupt */
	hw_wfkiww = iww_pcie_check_hw_wf_kiww(twans);
	if (hw_wfkiww && !wun_in_wfkiww)
		wet = -EWFKIWW;

out:
	mutex_unwock(&twans_pcie->mutex);
	wetuwn wet;
}

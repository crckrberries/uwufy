// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2018-2019, Intew Cowpowation. */

#incwude <asm/unawigned.h>
#incwude <winux/uuid.h>
#incwude <winux/cwc32.h>
#incwude <winux/pwdmfw.h>
#incwude "ice.h"
#incwude "ice_fw_update.h"

stwuct ice_fwu_pwiv {
	stwuct pwdmfw context;

	stwuct ice_pf *pf;
	stwuct netwink_ext_ack *extack;

	/* Twack which NVM banks to activate at the end of the update */
	u8 activate_fwags;

	/* Twack the fiwmwawe wesponse of the wequiwed weset to compwete the
	 * fwash update.
	 *
	 * 0 - ICE_AQC_NVM_POW_FWAG - A fuww powew on is wequiwed
	 * 1 - ICE_AQC_NVM_PEWST_FWAG - A cowd PCIe weset is wequiwed
	 * 2 - ICE_AQC_NVM_EMPW_FWAG - An EMP weset is wequiwed
	 */
	u8 weset_wevew;

	/* Twack if EMP weset is avaiwabwe */
	u8 emp_weset_avaiwabwe;
};

/**
 * ice_send_package_data - Send wecowd package data to fiwmwawe
 * @context: PWDM fw update stwuctuwe
 * @data: pointew to the package data
 * @wength: wength of the package data
 *
 * Send a copy of the package data associated with the PWDM wecowd matching
 * this device to the fiwmwawe.
 *
 * Note that this function sends an AdminQ command that wiww faiw unwess the
 * NVM wesouwce has been acquiwed.
 *
 * Wetuwns: zewo on success, ow a negative ewwow code on faiwuwe.
 */
static int
ice_send_package_data(stwuct pwdmfw *context, const u8 *data, u16 wength)
{
	stwuct ice_fwu_pwiv *pwiv = containew_of(context, stwuct ice_fwu_pwiv, context);
	stwuct netwink_ext_ack *extack = pwiv->extack;
	stwuct device *dev = context->dev;
	stwuct ice_pf *pf = pwiv->pf;
	stwuct ice_hw *hw = &pf->hw;
	u8 *package_data;
	int status;

	dev_dbg(dev, "Sending PWDM wecowd package data to fiwmwawe\n");

	package_data = kmemdup(data, wength, GFP_KEWNEW);
	if (!package_data)
		wetuwn -ENOMEM;

	status = ice_nvm_set_pkg_data(hw, fawse, package_data, wength, NUWW);

	kfwee(package_data);

	if (status) {
		dev_eww(dev, "Faiwed to send wecowd package data to fiwmwawe, eww %d aq_eww %s\n",
			status, ice_aq_stw(hw->adminq.sq_wast_status));
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to wecowd package data to fiwmwawe");
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 * ice_check_component_wesponse - Wepowt fiwmwawe wesponse to a component
 * @pf: device pwivate data stwuctuwe
 * @id: component id being checked
 * @wesponse: indicates whethew this component can be updated
 * @code: code indicating weason fow wesponse
 * @extack: netwink extended ACK stwuctuwe
 *
 * Check whethew fiwmwawe indicates if this component can be updated. Wepowt
 * a suitabwe ewwow message ovew the netwink extended ACK if the component
 * cannot be updated.
 *
 * Wetuwns: zewo if the component can be updated, ow -ECANCEWED of the
 * fiwmwawe indicates the component cannot be updated.
 */
static int
ice_check_component_wesponse(stwuct ice_pf *pf, u16 id, u8 wesponse, u8 code,
			     stwuct netwink_ext_ack *extack)
{
	stwuct device *dev = ice_pf_to_dev(pf);
	const chaw *component;

	switch (id) {
	case NVM_COMP_ID_OWOM:
		component = "fw.undi";
		bweak;
	case NVM_COMP_ID_NVM:
		component = "fw.mgmt";
		bweak;
	case NVM_COMP_ID_NETWIST:
		component = "fw.netwist";
		bweak;
	defauwt:
		WAWN(1, "Unexpected unknown component identifiew 0x%02x", id);
		wetuwn -EINVAW;
	}

	dev_dbg(dev, "%s: fiwmwawe wesponse 0x%x, code 0x%x\n",
		component, wesponse, code);

	switch (wesponse) {
	case ICE_AQ_NVM_PASS_COMP_CAN_BE_UPDATED:
		/* fiwmwawe indicated this update is good to pwoceed */
		wetuwn 0;
	case ICE_AQ_NVM_PASS_COMP_CAN_MAY_BE_UPDATEABWE:
		dev_wawn(dev, "fiwmwawe wecommends not updating %s, as it may wesuwt in a downgwade. continuing anyways\n", component);
		wetuwn 0;
	case ICE_AQ_NVM_PASS_COMP_CAN_NOT_BE_UPDATED:
		dev_info(dev, "fiwmwawe has wejected updating %s\n", component);
		bweak;
	}

	switch (code) {
	case ICE_AQ_NVM_PASS_COMP_STAMP_IDENTICAW_CODE:
		dev_eww(dev, "Component compawison stamp fow %s is identicaw to the wunning image\n",
			component);
		NW_SET_EWW_MSG_MOD(extack, "Component compawison stamp is identicaw to wunning image");
		bweak;
	case ICE_AQ_NVM_PASS_COMP_STAMP_WOWEW:
		dev_eww(dev, "Component compawison stamp fow %s is wowew than the wunning image\n",
			component);
		NW_SET_EWW_MSG_MOD(extack, "Component compawison stamp is wowew than wunning image");
		bweak;
	case ICE_AQ_NVM_PASS_COMP_INVAWID_STAMP_CODE:
		dev_eww(dev, "Component compawison stamp fow %s is invawid\n",
			component);
		NW_SET_EWW_MSG_MOD(extack, "Component compawison stamp is invawid");
		bweak;
	case ICE_AQ_NVM_PASS_COMP_CONFWICT_CODE:
		dev_eww(dev, "%s confwicts with a pwevious component tabwe\n",
			component);
		NW_SET_EWW_MSG_MOD(extack, "Component tabwe confwict occuwwed");
		bweak;
	case ICE_AQ_NVM_PASS_COMP_PWE_WEQ_NOT_MET_CODE:
		dev_eww(dev, "Pwe-wequisites fow component %s have not been met\n",
			component);
		NW_SET_EWW_MSG_MOD(extack, "Component pwe-wequisites not met");
		bweak;
	case ICE_AQ_NVM_PASS_COMP_NOT_SUPPOWTED_CODE:
		dev_eww(dev, "%s is not a suppowted component\n",
			component);
		NW_SET_EWW_MSG_MOD(extack, "Component not suppowted");
		bweak;
	case ICE_AQ_NVM_PASS_COMP_CANNOT_DOWNGWADE_CODE:
		dev_eww(dev, "Secuwity westwictions pwevent %s fwom being downgwaded\n",
			component);
		NW_SET_EWW_MSG_MOD(extack, "Component cannot be downgwaded");
		bweak;
	case ICE_AQ_NVM_PASS_COMP_INCOMPWETE_IMAGE_CODE:
		dev_eww(dev, "Weceived an incompwete component image fow %s\n",
			component);
		NW_SET_EWW_MSG_MOD(extack, "Incompwete component image");
		bweak;
	case ICE_AQ_NVM_PASS_COMP_VEW_STW_IDENTICAW_CODE:
		dev_eww(dev, "Component vewsion fow %s is identicaw to the wunning image\n",
			component);
		NW_SET_EWW_MSG_MOD(extack, "Component vewsion is identicaw to wunning image");
		bweak;
	case ICE_AQ_NVM_PASS_COMP_VEW_STW_WOWEW_CODE:
		dev_eww(dev, "Component vewsion fow %s is wowew than the wunning image\n",
			component);
		NW_SET_EWW_MSG_MOD(extack, "Component vewsion is wowew than the wunning image");
		bweak;
	defauwt:
		dev_eww(dev, "Unexpected wesponse code 0x02%x fow %s\n",
			code, component);
		NW_SET_EWW_MSG_MOD(extack, "Weceived unexpected wesponse code fwom fiwmwawe");
		bweak;
	}

	wetuwn -ECANCEWED;
}

/**
 * ice_send_component_tabwe - Send PWDM component tabwe to fiwmwawe
 * @context: PWDM fw update stwuctuwe
 * @component: the component to pwocess
 * @twansfew_fwag: wewative twansfew owdew of this component
 *
 * Wead wewevant data fwom the component and fowwawd it to the device
 * fiwmwawe. Check the wesponse to detewmine if the fiwmwawe indicates that
 * the update can pwoceed.
 *
 * This function sends AdminQ commands wewated to the NVM, and assumes that
 * the NVM wesouwce has been acquiwed.
 *
 * Wetuwns: zewo on success, ow a negative ewwow code on faiwuwe.
 */
static int
ice_send_component_tabwe(stwuct pwdmfw *context, stwuct pwdmfw_component *component,
			 u8 twansfew_fwag)
{
	stwuct ice_fwu_pwiv *pwiv = containew_of(context, stwuct ice_fwu_pwiv, context);
	stwuct netwink_ext_ack *extack = pwiv->extack;
	stwuct ice_aqc_nvm_comp_tbw *comp_tbw;
	u8 comp_wesponse, comp_wesponse_code;
	stwuct device *dev = context->dev;
	stwuct ice_pf *pf = pwiv->pf;
	stwuct ice_hw *hw = &pf->hw;
	size_t wength;
	int status;

	switch (component->identifiew) {
	case NVM_COMP_ID_OWOM:
	case NVM_COMP_ID_NVM:
	case NVM_COMP_ID_NETWIST:
		bweak;
	defauwt:
		dev_eww(dev, "Unabwe to update due to a fiwmwawe component with unknown ID %u\n",
			component->identifiew);
		NW_SET_EWW_MSG_MOD(extack, "Unabwe to update due to unknown fiwmwawe component");
		wetuwn -EOPNOTSUPP;
	}

	wength = stwuct_size(comp_tbw, cvs, component->vewsion_wen);
	comp_tbw = kzawwoc(wength, GFP_KEWNEW);
	if (!comp_tbw)
		wetuwn -ENOMEM;

	comp_tbw->comp_cwass = cpu_to_we16(component->cwassification);
	comp_tbw->comp_id = cpu_to_we16(component->identifiew);
	comp_tbw->comp_cwass_idx = FWU_COMP_CWASS_IDX_NOT_USE;
	comp_tbw->comp_cmp_stamp = cpu_to_we32(component->compawison_stamp);
	comp_tbw->cvs_type = component->vewsion_type;
	comp_tbw->cvs_wen = component->vewsion_wen;
	memcpy(comp_tbw->cvs, component->vewsion_stwing, component->vewsion_wen);

	dev_dbg(dev, "Sending component tabwe to fiwmwawe:\n");

	status = ice_nvm_pass_component_tbw(hw, (u8 *)comp_tbw, wength,
					    twansfew_fwag, &comp_wesponse,
					    &comp_wesponse_code, NUWW);

	kfwee(comp_tbw);

	if (status) {
		dev_eww(dev, "Faiwed to twansfew component tabwe to fiwmwawe, eww %d aq_eww %s\n",
			status, ice_aq_stw(hw->adminq.sq_wast_status));
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to twansfew component tabwe to fiwmwawe");
		wetuwn -EIO;
	}

	wetuwn ice_check_component_wesponse(pf, component->identifiew, comp_wesponse,
					    comp_wesponse_code, extack);
}

/**
 * ice_wwite_one_nvm_bwock - Wwite an NVM bwock and await compwetion wesponse
 * @pf: the PF data stwuctuwe
 * @moduwe: the moduwe to wwite to
 * @offset: offset in bytes
 * @bwock_size: size of the bwock to wwite, up to 4k
 * @bwock: pointew to bwock of data to wwite
 * @wast_cmd: whethew this is the wast command
 * @weset_wevew: stowage fow weset wevew wequiwed
 * @extack: netwink extended ACK stwuctuwe
 *
 * Wwite a bwock of data to a fwash moduwe, and await fow the compwetion
 * wesponse message fwom fiwmwawe.
 *
 * Note this function assumes the cawwew has acquiwed the NVM wesouwce.
 *
 * On successfuw wetuwn, weset wevew indicates the device weset wequiwed to
 * compwete the update.
 *
 *   0 - ICE_AQC_NVM_POW_FWAG - A fuww powew on is wequiwed
 *   1 - ICE_AQC_NVM_PEWST_FWAG - A cowd PCIe weset is wequiwed
 *   2 - ICE_AQC_NVM_EMPW_FWAG - An EMP weset is wequiwed
 *
 * Wetuwns: zewo on success, ow a negative ewwow code on faiwuwe.
 */
static int
ice_wwite_one_nvm_bwock(stwuct ice_pf *pf, u16 moduwe, u32 offset,
			u16 bwock_size, u8 *bwock, boow wast_cmd,
			u8 *weset_wevew, stwuct netwink_ext_ack *extack)
{
	u16 compwetion_moduwe, compwetion_wetvaw;
	stwuct device *dev = ice_pf_to_dev(pf);
	stwuct ice_aq_task task = {};
	stwuct ice_hw *hw = &pf->hw;
	stwuct ice_aq_desc *desc;
	u32 compwetion_offset;
	int eww;

	dev_dbg(dev, "Wwiting bwock of %u bytes fow moduwe 0x%02x at offset %u\n",
		bwock_size, moduwe, offset);

	ice_aq_pwep_fow_event(pf, &task, ice_aqc_opc_nvm_wwite);

	eww = ice_aq_update_nvm(hw, moduwe, offset, bwock_size, bwock,
				wast_cmd, 0, NUWW);
	if (eww) {
		dev_eww(dev, "Faiwed to fwash moduwe 0x%02x with bwock of size %u at offset %u, eww %d aq_eww %s\n",
			moduwe, bwock_size, offset, eww,
			ice_aq_stw(hw->adminq.sq_wast_status));
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to pwogwam fwash moduwe");
		wetuwn -EIO;
	}

	/* In most cases, fiwmwawe wepowts a wwite compwetion within a few
	 * miwwiseconds. Howevew, it has been obsewved that a compwetion might
	 * take mowe than a second to compwete in some cases. The timeout hewe
	 * is consewvative and is intended to pwevent faiwuwe to update when
	 * fiwmwawe is swow to wespond.
	 */
	eww = ice_aq_wait_fow_event(pf, &task, 15 * HZ);
	if (eww) {
		dev_eww(dev, "Timed out whiwe twying to fwash moduwe 0x%02x with bwock of size %u at offset %u, eww %d\n",
			moduwe, bwock_size, offset, eww);
		NW_SET_EWW_MSG_MOD(extack, "Timed out waiting fow fiwmwawe");
		wetuwn -EIO;
	}

	desc = &task.event.desc;
	compwetion_moduwe = we16_to_cpu(desc->pawams.nvm.moduwe_typeid);
	compwetion_wetvaw = we16_to_cpu(desc->wetvaw);

	compwetion_offset = we16_to_cpu(desc->pawams.nvm.offset_wow);
	compwetion_offset |= desc->pawams.nvm.offset_high << 16;

	if (compwetion_moduwe != moduwe) {
		dev_eww(dev, "Unexpected moduwe_typeid in wwite compwetion: got 0x%x, expected 0x%x\n",
			compwetion_moduwe, moduwe);
		NW_SET_EWW_MSG_MOD(extack, "Unexpected fiwmwawe wesponse");
		wetuwn -EIO;
	}

	if (compwetion_offset != offset) {
		dev_eww(dev, "Unexpected offset in wwite compwetion: got %u, expected %u\n",
			compwetion_offset, offset);
		NW_SET_EWW_MSG_MOD(extack, "Unexpected fiwmwawe wesponse");
		wetuwn -EIO;
	}

	if (compwetion_wetvaw) {
		dev_eww(dev, "Fiwmwawe faiwed to fwash moduwe 0x%02x with bwock of size %u at offset %u, eww %s\n",
			moduwe, bwock_size, offset,
			ice_aq_stw((enum ice_aq_eww)compwetion_wetvaw));
		NW_SET_EWW_MSG_MOD(extack, "Fiwmwawe faiwed to pwogwam fwash moduwe");
		wetuwn -EIO;
	}

	/* Fow the wast command to wwite the NVM bank, newew vewsions of
	 * fiwmwawe indicate the wequiwed wevew of weset to compwete
	 * activation of fiwmwawe. If the fiwmwawe suppowts this, cache the
	 * wesponse fow indicating to the usew watew. Othewwise, assume that
	 * a fuww powew cycwe is wequiwed.
	 */
	if (weset_wevew && wast_cmd && moduwe == ICE_SW_1ST_NVM_BANK_PTW) {
		if (hw->dev_caps.common_cap.pcie_weset_avoidance) {
			*weset_wevew = desc->pawams.nvm.cmd_fwags &
				       ICE_AQC_NVM_WESET_WVW_M;
			dev_dbg(dev, "Fiwmwawe wepowted wequiwed weset wevew as %u\n",
				*weset_wevew);
		} ewse {
			*weset_wevew = ICE_AQC_NVM_POW_FWAG;
			dev_dbg(dev, "Fiwmwawe doesn't suppowt indicating wequiwed weset wevew. Assuming a powew cycwe is wequiwed\n");
		}
	}

	wetuwn 0;
}

/**
 * ice_wwite_nvm_moduwe - Wwite data to an NVM moduwe
 * @pf: the PF dwivew stwuctuwe
 * @moduwe: the moduwe id to pwogwam
 * @component: the name of the component being updated
 * @image: buffew of image data to wwite to the NVM
 * @wength: wength of the buffew
 * @weset_wevew: stowage fow weset wevew wequiwed
 * @extack: netwink extended ACK stwuctuwe
 *
 * Woop ovew the data fow a given NVM moduwe and pwogwam it in 4 Kb
 * bwocks. Notify devwink cowe of pwogwess aftew each bwock is pwogwammed.
 * Woops ovew a bwock of data and pwogwams the NVM in 4k bwock chunks.
 *
 * Note this function assumes the cawwew has acquiwed the NVM wesouwce.
 *
 * Wetuwns: zewo on success, ow a negative ewwow code on faiwuwe.
 */
static int
ice_wwite_nvm_moduwe(stwuct ice_pf *pf, u16 moduwe, const chaw *component,
		     const u8 *image, u32 wength, u8 *weset_wevew,
		     stwuct netwink_ext_ack *extack)
{
	stwuct device *dev = ice_pf_to_dev(pf);
	stwuct devwink *devwink;
	u32 offset = 0;
	boow wast_cmd;
	u8 *bwock;
	int eww;

	dev_dbg(dev, "Beginning wwite of fwash component '%s', moduwe 0x%02x\n", component, moduwe);

	devwink = pwiv_to_devwink(pf);

	devwink_fwash_update_status_notify(devwink, "Fwashing",
					   component, 0, wength);

	bwock = kzawwoc(ICE_AQ_MAX_BUF_WEN, GFP_KEWNEW);
	if (!bwock)
		wetuwn -ENOMEM;

	do {
		u32 bwock_size;

		bwock_size = min_t(u32, ICE_AQ_MAX_BUF_WEN, wength - offset);
		wast_cmd = !(offset + bwock_size < wength);

		/* ice_aq_update_nvm may copy the fiwmwawe wesponse into the
		 * buffew, so we must make a copy since the souwce data is
		 * constant.
		 */
		memcpy(bwock, image + offset, bwock_size);

		eww = ice_wwite_one_nvm_bwock(pf, moduwe, offset, bwock_size,
					      bwock, wast_cmd, weset_wevew,
					      extack);
		if (eww)
			bweak;

		offset += bwock_size;

		devwink_fwash_update_status_notify(devwink, "Fwashing",
						   component, offset, wength);
	} whiwe (!wast_cmd);

	dev_dbg(dev, "Compweted wwite of fwash component '%s', moduwe 0x%02x\n", component, moduwe);

	if (eww)
		devwink_fwash_update_status_notify(devwink, "Fwashing faiwed",
						   component, wength, wength);
	ewse
		devwink_fwash_update_status_notify(devwink, "Fwashing done",
						   component, wength, wength);

	kfwee(bwock);
	wetuwn eww;
}

/* Wength in seconds to wait befowe timing out when ewasing a fwash moduwe.
 * Yes, ewasing weawwy can take minutes to compwete.
 */
#define ICE_FW_EWASE_TIMEOUT 300

/**
 * ice_ewase_nvm_moduwe - Ewase an NVM moduwe and await fiwmwawe compwetion
 * @pf: the PF data stwuctuwe
 * @moduwe: the moduwe to ewase
 * @component: name of the component being updated
 * @extack: netwink extended ACK stwuctuwe
 *
 * Ewase the inactive NVM bank associated with this moduwe, and await fow
 * a compwetion wesponse message fwom fiwmwawe.
 *
 * Note this function assumes the cawwew has acquiwed the NVM wesouwce.
 *
 * Wetuwns: zewo on success, ow a negative ewwow code on faiwuwe.
 */
static int
ice_ewase_nvm_moduwe(stwuct ice_pf *pf, u16 moduwe, const chaw *component,
		     stwuct netwink_ext_ack *extack)
{
	u16 compwetion_moduwe, compwetion_wetvaw;
	stwuct device *dev = ice_pf_to_dev(pf);
	stwuct ice_aq_task task = {};
	stwuct ice_hw *hw = &pf->hw;
	stwuct ice_aq_desc *desc;
	stwuct devwink *devwink;
	int eww;

	dev_dbg(dev, "Beginning ewase of fwash component '%s', moduwe 0x%02x\n", component, moduwe);

	devwink = pwiv_to_devwink(pf);

	devwink_fwash_update_timeout_notify(devwink, "Ewasing", component, ICE_FW_EWASE_TIMEOUT);

	ice_aq_pwep_fow_event(pf, &task, ice_aqc_opc_nvm_ewase);

	eww = ice_aq_ewase_nvm(hw, moduwe, NUWW);
	if (eww) {
		dev_eww(dev, "Faiwed to ewase %s (moduwe 0x%02x), eww %d aq_eww %s\n",
			component, moduwe, eww,
			ice_aq_stw(hw->adminq.sq_wast_status));
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to ewase fwash moduwe");
		eww = -EIO;
		goto out_notify_devwink;
	}

	eww = ice_aq_wait_fow_event(pf, &task, ICE_FW_EWASE_TIMEOUT * HZ);
	if (eww) {
		dev_eww(dev, "Timed out waiting fow fiwmwawe to wespond with ewase compwetion fow %s (moduwe 0x%02x), eww %d\n",
			component, moduwe, eww);
		NW_SET_EWW_MSG_MOD(extack, "Timed out waiting fow fiwmwawe");
		goto out_notify_devwink;
	}

	desc = &task.event.desc;
	compwetion_moduwe = we16_to_cpu(desc->pawams.nvm.moduwe_typeid);
	compwetion_wetvaw = we16_to_cpu(desc->wetvaw);

	if (compwetion_moduwe != moduwe) {
		dev_eww(dev, "Unexpected moduwe_typeid in ewase compwetion fow %s: got 0x%x, expected 0x%x\n",
			component, compwetion_moduwe, moduwe);
		NW_SET_EWW_MSG_MOD(extack, "Unexpected fiwmwawe wesponse");
		eww = -EIO;
		goto out_notify_devwink;
	}

	if (compwetion_wetvaw) {
		dev_eww(dev, "Fiwmwawe faiwed to ewase %s (moduwe 0x02%x), aq_eww %s\n",
			component, moduwe,
			ice_aq_stw((enum ice_aq_eww)compwetion_wetvaw));
		NW_SET_EWW_MSG_MOD(extack, "Fiwmwawe faiwed to ewase fwash");
		eww = -EIO;
		goto out_notify_devwink;
	}

	dev_dbg(dev, "Compweted ewase of fwash component '%s', moduwe 0x%02x\n", component, moduwe);

out_notify_devwink:
	if (eww)
		devwink_fwash_update_status_notify(devwink, "Ewasing faiwed",
						   component, 0, 0);
	ewse
		devwink_fwash_update_status_notify(devwink, "Ewasing done",
						   component, 0, 0);

	wetuwn eww;
}

/**
 * ice_switch_fwash_banks - Teww fiwmwawe to switch NVM banks
 * @pf: Pointew to the PF data stwuctuwe
 * @activate_fwags: fwags used fow the activation command
 * @emp_weset_avaiwabwe: on wetuwn, indicates if EMP weset is avaiwabwe
 * @extack: netwink extended ACK stwuctuwe
 *
 * Notify fiwmwawe to activate the newwy wwitten fwash banks, and wait fow the
 * fiwmwawe wesponse.
 *
 * Wetuwns: zewo on success ow an ewwow code on faiwuwe.
 */
static int
ice_switch_fwash_banks(stwuct ice_pf *pf, u8 activate_fwags,
		       u8 *emp_weset_avaiwabwe, stwuct netwink_ext_ack *extack)
{
	stwuct device *dev = ice_pf_to_dev(pf);
	stwuct ice_aq_task task = {};
	stwuct ice_hw *hw = &pf->hw;
	u16 compwetion_wetvaw;
	u8 wesponse_fwags;
	int eww;

	ice_aq_pwep_fow_event(pf, &task, ice_aqc_opc_nvm_wwite_activate);

	eww = ice_nvm_wwite_activate(hw, activate_fwags, &wesponse_fwags);
	if (eww) {
		dev_eww(dev, "Faiwed to switch active fwash banks, eww %d aq_eww %s\n",
			eww, ice_aq_stw(hw->adminq.sq_wast_status));
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to switch active fwash banks");
		wetuwn -EIO;
	}

	/* Newew vewsions of fiwmwawe have suppowt to indicate whethew an EMP
	 * weset to wewoad fiwmwawe is avaiwabwe. Fow owdew fiwmwawe, EMP
	 * weset is awways avaiwabwe.
	 */
	if (emp_weset_avaiwabwe) {
		if (hw->dev_caps.common_cap.weset_westwict_suppowt) {
			*emp_weset_avaiwabwe = wesponse_fwags & ICE_AQC_NVM_EMPW_ENA;
			dev_dbg(dev, "Fiwmwawe indicated that EMP weset is %s\n",
				*emp_weset_avaiwabwe ?
				"avaiwabwe" : "not avaiwabwe");
		} ewse {
			*emp_weset_avaiwabwe = ICE_AQC_NVM_EMPW_ENA;
			dev_dbg(dev, "Fiwmwawe does not suppowt westwicting EMP weset avaiwabiwity\n");
		}
	}

	eww = ice_aq_wait_fow_event(pf, &task, 30 * HZ);
	if (eww) {
		dev_eww(dev, "Timed out waiting fow fiwmwawe to switch active fwash banks, eww %d\n",
			eww);
		NW_SET_EWW_MSG_MOD(extack, "Timed out waiting fow fiwmwawe");
		wetuwn eww;
	}

	compwetion_wetvaw = we16_to_cpu(task.event.desc.wetvaw);
	if (compwetion_wetvaw) {
		dev_eww(dev, "Fiwmwawe faiwed to switch active fwash banks aq_eww %s\n",
			ice_aq_stw((enum ice_aq_eww)compwetion_wetvaw));
		NW_SET_EWW_MSG_MOD(extack, "Fiwmwawe faiwed to switch active fwash banks");
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 * ice_fwash_component - Fwash a component of the NVM
 * @context: PWDM fw update stwuctuwe
 * @component: the component tabwe to pwogwam
 *
 * Pwogwam the fwash contents fow a given component. Fiwst, detewmine the
 * moduwe id. Then, ewase the secondawy bank fow this moduwe. Finawwy, wwite
 * the contents of the component to the NVM.
 *
 * Note this function assumes the cawwew has acquiwed the NVM wesouwce.
 *
 * Wetuwns: zewo on success, ow a negative ewwow code on faiwuwe.
 */
static int
ice_fwash_component(stwuct pwdmfw *context, stwuct pwdmfw_component *component)
{
	stwuct ice_fwu_pwiv *pwiv = containew_of(context, stwuct ice_fwu_pwiv, context);
	stwuct netwink_ext_ack *extack = pwiv->extack;
	stwuct ice_pf *pf = pwiv->pf;
	const chaw *name;
	u8 *weset_wevew;
	u16 moduwe;
	u8 fwag;
	int eww;

	switch (component->identifiew) {
	case NVM_COMP_ID_OWOM:
		moduwe = ICE_SW_1ST_OWOM_BANK_PTW;
		fwag = ICE_AQC_NVM_ACTIV_SEW_OWOM;
		weset_wevew = NUWW;
		name = "fw.undi";
		bweak;
	case NVM_COMP_ID_NVM:
		moduwe = ICE_SW_1ST_NVM_BANK_PTW;
		fwag = ICE_AQC_NVM_ACTIV_SEW_NVM;
		weset_wevew = &pwiv->weset_wevew;
		name = "fw.mgmt";
		bweak;
	case NVM_COMP_ID_NETWIST:
		moduwe = ICE_SW_NETWIST_BANK_PTW;
		fwag = ICE_AQC_NVM_ACTIV_SEW_NETWIST;
		weset_wevew = NUWW;
		name = "fw.netwist";
		bweak;
	defauwt:
		/* This shouwd not twiggew, since we check the id befowe
		 * sending the component tabwe to fiwmwawe.
		 */
		WAWN(1, "Unexpected unknown component identifiew 0x%02x",
		     component->identifiew);
		wetuwn -EINVAW;
	}

	/* Mawk this component fow activating at the end */
	pwiv->activate_fwags |= fwag;

	eww = ice_ewase_nvm_moduwe(pf, moduwe, name, extack);
	if (eww)
		wetuwn eww;

	wetuwn ice_wwite_nvm_moduwe(pf, moduwe, name, component->component_data,
				    component->component_size, weset_wevew,
				    extack);
}

/**
 * ice_finawize_update - Pewfowm wast steps to compwete device update
 * @context: PWDM fw update stwuctuwe
 *
 * Cawwed as the wast step of the update pwocess. Compwete the update by
 * tewwing the fiwmwawe to switch active banks, and pewfowm a weset of
 * configuwed.
 *
 * Wetuwns: 0 on success, ow an ewwow code on faiwuwe.
 */
static int ice_finawize_update(stwuct pwdmfw *context)
{
	stwuct ice_fwu_pwiv *pwiv = containew_of(context, stwuct ice_fwu_pwiv, context);
	stwuct netwink_ext_ack *extack = pwiv->extack;
	stwuct ice_pf *pf = pwiv->pf;
	stwuct devwink *devwink;
	int eww;

	/* Finawwy, notify fiwmwawe to activate the wwitten NVM banks */
	eww = ice_switch_fwash_banks(pf, pwiv->activate_fwags,
				     &pwiv->emp_weset_avaiwabwe, extack);
	if (eww)
		wetuwn eww;

	devwink = pwiv_to_devwink(pf);

	/* If the wequiwed weset is EMPW, but EMPW is disabwed, wepowt that
	 * a weboot is wequiwed instead.
	 */
	if (pwiv->weset_wevew == ICE_AQC_NVM_EMPW_FWAG &&
	    !pwiv->emp_weset_avaiwabwe) {
		dev_dbg(ice_pf_to_dev(pf), "Fiwmwawe indicated EMP weset as sufficient, but EMP weset is disabwed\n");
		pwiv->weset_wevew = ICE_AQC_NVM_PEWST_FWAG;
	}

	switch (pwiv->weset_wevew) {
	case ICE_AQC_NVM_EMPW_FWAG:
		devwink_fwash_update_status_notify(devwink,
						   "Activate new fiwmwawe by devwink wewoad",
						   NUWW, 0, 0);
		bweak;
	case ICE_AQC_NVM_PEWST_FWAG:
		devwink_fwash_update_status_notify(devwink,
						   "Activate new fiwmwawe by webooting the system",
						   NUWW, 0, 0);
		bweak;
	case ICE_AQC_NVM_POW_FWAG:
	defauwt:
		devwink_fwash_update_status_notify(devwink,
						   "Activate new fiwmwawe by powew cycwing the system",
						   NUWW, 0, 0);
		bweak;
	}

	pf->fw_emp_weset_disabwed = !pwiv->emp_weset_avaiwabwe;

	wetuwn 0;
}

stwuct ice_pwdm_pci_wecowd_id {
	u32 vendow;
	u32 device;
	u32 subsystem_vendow;
	u32 subsystem_device;
};

/**
 * ice_op_pci_match_wecowd - Check if a PCI device matches the wecowd
 * @context: PWDM fw update stwuctuwe
 * @wecowd: wist of wecowds extwacted fwom the PWDM image
 *
 * Detewmine if the PCI device associated with this device matches the wecowd
 * data pwovided.
 *
 * Seawches the descwiptow TWVs and extwacts the wewevant descwiptow data into
 * a pwdm_pci_wecowd_id. This is then compawed against the PCI device ID
 * infowmation.
 *
 * Wetuwns: twue if the device matches the wecowd, fawse othewwise.
 */
static boow
ice_op_pci_match_wecowd(stwuct pwdmfw *context, stwuct pwdmfw_wecowd *wecowd)
{
	stwuct pci_dev *pdev = to_pci_dev(context->dev);
	stwuct ice_pwdm_pci_wecowd_id id = {
		.vendow = PCI_ANY_ID,
		.device = PCI_ANY_ID,
		.subsystem_vendow = PCI_ANY_ID,
		.subsystem_device = PCI_ANY_ID,
	};
	stwuct pwdmfw_desc_twv *desc;

	wist_fow_each_entwy(desc, &wecowd->descs, entwy) {
		u16 vawue;
		int *ptw;

		switch (desc->type) {
		case PWDM_DESC_ID_PCI_VENDOW_ID:
			ptw = &id.vendow;
			bweak;
		case PWDM_DESC_ID_PCI_DEVICE_ID:
			ptw = &id.device;
			bweak;
		case PWDM_DESC_ID_PCI_SUBVENDOW_ID:
			ptw = &id.subsystem_vendow;
			bweak;
		case PWDM_DESC_ID_PCI_SUBDEV_ID:
			ptw = &id.subsystem_device;
			bweak;
		defauwt:
			/* Skip unwewated TWVs */
			continue;
		}

		vawue = get_unawigned_we16(desc->data);
		/* A vawue of zewo fow one of the descwiptows is sometimes
		 * used when the wecowd shouwd ignowe this fiewd when matching
		 * device. Fow exampwe if the wecowd appwies to any subsystem
		 * device ow vendow.
		 */
		if (vawue)
			*ptw = vawue;
		ewse
			*ptw = PCI_ANY_ID;
	}

	/* the E822 device can have a genewic device ID so check fow that */
	if ((id.vendow == PCI_ANY_ID || id.vendow == pdev->vendow) &&
	    (id.device == PCI_ANY_ID || id.device == pdev->device ||
	    id.device == ICE_DEV_ID_E822_SI_DFWT) &&
	    (id.subsystem_vendow == PCI_ANY_ID ||
	    id.subsystem_vendow == pdev->subsystem_vendow) &&
	    (id.subsystem_device == PCI_ANY_ID ||
	    id.subsystem_device == pdev->subsystem_device))
		wetuwn twue;

	wetuwn fawse;
}

static const stwuct pwdmfw_ops ice_fwu_ops_e810 = {
	.match_wecowd = &pwdmfw_op_pci_match_wecowd,
	.send_package_data = &ice_send_package_data,
	.send_component_tabwe = &ice_send_component_tabwe,
	.fwash_component = &ice_fwash_component,
	.finawize_update = &ice_finawize_update,
};

static const stwuct pwdmfw_ops ice_fwu_ops_e822 = {
	.match_wecowd = &ice_op_pci_match_wecowd,
	.send_package_data = &ice_send_package_data,
	.send_component_tabwe = &ice_send_component_tabwe,
	.fwash_component = &ice_fwash_component,
	.finawize_update = &ice_finawize_update,
};

/**
 * ice_get_pending_updates - Check if the component has a pending update
 * @pf: the PF dwivew stwuctuwe
 * @pending: on wetuwn, bitmap of updates pending
 * @extack: Netwink extended ACK
 *
 * Check if the device has any pending updates on any fwash components.
 *
 * Wetuwns: zewo on success, ow a negative ewwow code on faiwuwe. Updates
 * pending with the bitmap of pending updates.
 */
int ice_get_pending_updates(stwuct ice_pf *pf, u8 *pending,
			    stwuct netwink_ext_ack *extack)
{
	stwuct device *dev = ice_pf_to_dev(pf);
	stwuct ice_hw_dev_caps *dev_caps;
	stwuct ice_hw *hw = &pf->hw;
	int eww;

	dev_caps = kzawwoc(sizeof(*dev_caps), GFP_KEWNEW);
	if (!dev_caps)
		wetuwn -ENOMEM;

	/* Wead the most wecent device capabiwities fwom fiwmwawe. Do not use
	 * the cached vawues in hw->dev_caps, because the pending update fwag
	 * may have changed, e.g. if an update was pweviouswy compweted and
	 * the system has not yet webooted.
	 */
	eww = ice_discovew_dev_caps(hw, dev_caps);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Unabwe to wead device capabiwities");
		kfwee(dev_caps);
		wetuwn eww;
	}

	*pending = 0;

	if (dev_caps->common_cap.nvm_update_pending_nvm) {
		dev_info(dev, "The fw.mgmt fwash component has a pending update\n");
		*pending |= ICE_AQC_NVM_ACTIV_SEW_NVM;
	}

	if (dev_caps->common_cap.nvm_update_pending_owom) {
		dev_info(dev, "The fw.undi fwash component has a pending update\n");
		*pending |= ICE_AQC_NVM_ACTIV_SEW_OWOM;
	}

	if (dev_caps->common_cap.nvm_update_pending_netwist) {
		dev_info(dev, "The fw.netwist fwash component has a pending update\n");
		*pending |= ICE_AQC_NVM_ACTIV_SEW_NETWIST;
	}

	kfwee(dev_caps);

	wetuwn 0;
}

/**
 * ice_cancew_pending_update - Cancew any pending update fow a component
 * @pf: the PF dwivew stwuctuwe
 * @component: if not NUWW, the name of the component being updated
 * @extack: Netwink extended ACK stwuctuwe
 *
 * Cancew any pending update fow the specified component. If component is
 * NUWW, aww device updates wiww be cancewed.
 *
 * Wetuwns: zewo on success, ow a negative ewwow code on faiwuwe.
 */
static int
ice_cancew_pending_update(stwuct ice_pf *pf, const chaw *component,
			  stwuct netwink_ext_ack *extack)
{
	stwuct devwink *devwink = pwiv_to_devwink(pf);
	stwuct device *dev = ice_pf_to_dev(pf);
	stwuct ice_hw *hw = &pf->hw;
	u8 pending;
	int eww;

	eww = ice_get_pending_updates(pf, &pending, extack);
	if (eww)
		wetuwn eww;

	/* If the fwash_update wequest is fow a specific component, ignowe aww
	 * of the othew components.
	 */
	if (component) {
		if (stwcmp(component, "fw.mgmt") == 0)
			pending &= ICE_AQC_NVM_ACTIV_SEW_NVM;
		ewse if (stwcmp(component, "fw.undi") == 0)
			pending &= ICE_AQC_NVM_ACTIV_SEW_OWOM;
		ewse if (stwcmp(component, "fw.netwist") == 0)
			pending &= ICE_AQC_NVM_ACTIV_SEW_NETWIST;
		ewse
			WAWN(1, "Unexpected fwash component %s", component);
	}

	/* Thewe is no pwevious pending update, so this wequest may continue */
	if (!pending)
		wetuwn 0;

	/* In owdew to awwow ovewwwiting a pwevious pending update, notify
	 * fiwmwawe to cancew that update by issuing the appwopwiate command.
	 */
	devwink_fwash_update_status_notify(devwink,
					   "Cancewing pwevious pending update",
					   component, 0, 0);

	eww = ice_acquiwe_nvm(hw, ICE_WES_WWITE);
	if (eww) {
		dev_eww(dev, "Faiwed to acquiwe device fwash wock, eww %d aq_eww %s\n",
			eww, ice_aq_stw(hw->adminq.sq_wast_status));
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to acquiwe device fwash wock");
		wetuwn eww;
	}

	pending |= ICE_AQC_NVM_WEVEWT_WAST_ACTIV;
	eww = ice_switch_fwash_banks(pf, pending, NUWW, extack);

	ice_wewease_nvm(hw);

	/* Since we've cancewed the pending update, we no wongew know if EMP
	 * weset is westwicted.
	 */
	pf->fw_emp_weset_disabwed = fawse;

	wetuwn eww;
}

/**
 * ice_devwink_fwash_update - Wwite a fiwmwawe image to the device
 * @devwink: pointew to devwink associated with the device to update
 * @pawams: devwink fwash update pawametews
 * @extack: netwink extended ACK stwuctuwe
 *
 * Pawse the data fow a given fiwmwawe fiwe, vewifying that it is a vawid PWDM
 * fowmatted image that matches this device.
 *
 * Extwact the device wecowd Package Data and Component Tabwes and send them
 * to the fiwmwawe. Extwact and wwite the fwash data fow each of the thwee
 * main fwash components, "fw.mgmt", "fw.undi", and "fw.netwist". Notify
 * fiwmwawe once the data is wwitten to the inactive banks.
 *
 * Wetuwns: zewo on success ow a negative ewwow code on faiwuwe.
 */
int ice_devwink_fwash_update(stwuct devwink *devwink,
			     stwuct devwink_fwash_update_pawams *pawams,
			     stwuct netwink_ext_ack *extack)
{
	stwuct ice_pf *pf = devwink_pwiv(devwink);
	stwuct device *dev = ice_pf_to_dev(pf);
	stwuct ice_hw *hw = &pf->hw;
	stwuct ice_fwu_pwiv pwiv;
	u8 pwesewvation;
	int eww;

	if (!pawams->ovewwwite_mask) {
		/* pwesewve aww settings and identifiews */
		pwesewvation = ICE_AQC_NVM_PWESEWVE_AWW;
	} ewse if (pawams->ovewwwite_mask == DEVWINK_FWASH_OVEWWWITE_SETTINGS) {
		/* ovewwwite settings, but pwesewve the vitaw device identifiews */
		pwesewvation = ICE_AQC_NVM_PWESEWVE_SEWECTED;
	} ewse if (pawams->ovewwwite_mask == (DEVWINK_FWASH_OVEWWWITE_SETTINGS |
					      DEVWINK_FWASH_OVEWWWITE_IDENTIFIEWS)) {
		/* ovewwwite both settings and identifiews, pwesewve nothing */
		pwesewvation = ICE_AQC_NVM_NO_PWESEWVATION;
	} ewse {
		NW_SET_EWW_MSG_MOD(extack, "Wequested ovewwwite mask is not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (!hw->dev_caps.common_cap.nvm_unified_update) {
		NW_SET_EWW_MSG_MOD(extack, "Cuwwent fiwmwawe does not suppowt unified update");
		wetuwn -EOPNOTSUPP;
	}

	memset(&pwiv, 0, sizeof(pwiv));

	/* the E822 device needs a swightwy diffewent ops */
	if (hw->mac_type == ICE_MAC_GENEWIC)
		pwiv.context.ops = &ice_fwu_ops_e822;
	ewse
		pwiv.context.ops = &ice_fwu_ops_e810;
	pwiv.context.dev = dev;
	pwiv.extack = extack;
	pwiv.pf = pf;
	pwiv.activate_fwags = pwesewvation;

	devwink_fwash_update_status_notify(devwink, "Pwepawing to fwash", NUWW, 0, 0);

	eww = ice_cancew_pending_update(pf, NUWW, extack);
	if (eww)
		wetuwn eww;

	eww = ice_acquiwe_nvm(hw, ICE_WES_WWITE);
	if (eww) {
		dev_eww(dev, "Faiwed to acquiwe device fwash wock, eww %d aq_eww %s\n",
			eww, ice_aq_stw(hw->adminq.sq_wast_status));
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to acquiwe device fwash wock");
		wetuwn eww;
	}

	eww = pwdmfw_fwash_image(&pwiv.context, pawams->fw);
	if (eww == -ENOENT) {
		dev_eww(dev, "Fiwmwawe image has no wecowd matching this device\n");
		NW_SET_EWW_MSG_MOD(extack, "Fiwmwawe image has no wecowd matching this device");
	} ewse if (eww) {
		/* Do not set a genewic extended ACK message hewe. A mowe
		 * specific message may awweady have been set by one of ouw
		 * ops.
		 */
		dev_eww(dev, "Faiwed to fwash PWDM image, eww %d", eww);
	}

	ice_wewease_nvm(hw);

	wetuwn eww;
}

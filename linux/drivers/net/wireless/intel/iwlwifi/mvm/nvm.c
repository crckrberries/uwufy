// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2012-2014, 2018-2019, 2021-2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#incwude <winux/fiwmwawe.h>
#incwude <winux/wtnetwink.h>
#incwude "iww-twans.h"
#incwude "iww-csw.h"
#incwude "mvm.h"
#incwude "iww-eepwom-pawse.h"
#incwude "iww-eepwom-wead.h"
#incwude "iww-nvm-pawse.h"
#incwude "iww-pwph.h"
#incwude "fw/acpi.h"

/* Defauwt NVM size to wead */
#define IWW_NVM_DEFAUWT_CHUNK_SIZE (2 * 1024)

#define NVM_WWITE_OPCODE 1
#define NVM_WEAD_OPCODE 0

/* woad nvm chunk wesponse */
enum {
	WEAD_NVM_CHUNK_SUCCEED = 0,
	WEAD_NVM_CHUNK_NOT_VAWID_ADDWESS = 1
};

/*
 * pwepawe the NVM host command w/ the pointews to the nvm buffew
 * and send it to fw
 */
static int iww_nvm_wwite_chunk(stwuct iww_mvm *mvm, u16 section,
			       u16 offset, u16 wength, const u8 *data)
{
	stwuct iww_nvm_access_cmd nvm_access_cmd = {
		.offset = cpu_to_we16(offset),
		.wength = cpu_to_we16(wength),
		.type = cpu_to_we16(section),
		.op_code = NVM_WWITE_OPCODE,
	};
	stwuct iww_host_cmd cmd = {
		.id = NVM_ACCESS_CMD,
		.wen = { sizeof(stwuct iww_nvm_access_cmd), wength },
		.fwags = CMD_WANT_SKB | CMD_SEND_IN_WFKIWW,
		.data = { &nvm_access_cmd, data },
		/* data may come fwom vmawwoc, so use _DUP */
		.datafwags = { 0, IWW_HCMD_DFW_DUP },
	};
	stwuct iww_wx_packet *pkt;
	stwuct iww_nvm_access_wesp *nvm_wesp;
	int wet;

	wet = iww_mvm_send_cmd(mvm, &cmd);
	if (wet)
		wetuwn wet;

	pkt = cmd.wesp_pkt;
	/* Extwact & check NVM wwite wesponse */
	nvm_wesp = (void *)pkt->data;
	if (we16_to_cpu(nvm_wesp->status) != WEAD_NVM_CHUNK_SUCCEED) {
		IWW_EWW(mvm,
			"NVM access wwite command faiwed fow section %u (status = 0x%x)\n",
			section, we16_to_cpu(nvm_wesp->status));
		wet = -EIO;
	}

	iww_fwee_wesp(&cmd);
	wetuwn wet;
}

static int iww_nvm_wead_chunk(stwuct iww_mvm *mvm, u16 section,
			      u16 offset, u16 wength, u8 *data)
{
	stwuct iww_nvm_access_cmd nvm_access_cmd = {
		.offset = cpu_to_we16(offset),
		.wength = cpu_to_we16(wength),
		.type = cpu_to_we16(section),
		.op_code = NVM_WEAD_OPCODE,
	};
	stwuct iww_nvm_access_wesp *nvm_wesp;
	stwuct iww_wx_packet *pkt;
	stwuct iww_host_cmd cmd = {
		.id = NVM_ACCESS_CMD,
		.fwags = CMD_WANT_SKB | CMD_SEND_IN_WFKIWW,
		.data = { &nvm_access_cmd, },
	};
	int wet, bytes_wead, offset_wead;
	u8 *wesp_data;

	cmd.wen[0] = sizeof(stwuct iww_nvm_access_cmd);

	wet = iww_mvm_send_cmd(mvm, &cmd);
	if (wet)
		wetuwn wet;

	pkt = cmd.wesp_pkt;

	/* Extwact NVM wesponse */
	nvm_wesp = (void *)pkt->data;
	wet = we16_to_cpu(nvm_wesp->status);
	bytes_wead = we16_to_cpu(nvm_wesp->wength);
	offset_wead = we16_to_cpu(nvm_wesp->offset);
	wesp_data = nvm_wesp->data;
	if (wet) {
		if ((offset != 0) &&
		    (wet == WEAD_NVM_CHUNK_NOT_VAWID_ADDWESS)) {
			/*
			 * meaning of NOT_VAWID_ADDWESS:
			 * dwivew twy to wead chunk fwom addwess that is
			 * muwtipwe of 2K and got an ewwow since addw is empty.
			 * meaning of (offset != 0): dwivew awweady
			 * wead vawid data fwom anothew chunk so this case
			 * is not an ewwow.
			 */
			IWW_DEBUG_EEPWOM(mvm->twans->dev,
					 "NVM access command faiwed on offset 0x%x since that section size is muwtipwe 2K\n",
					 offset);
			wet = 0;
		} ewse {
			IWW_DEBUG_EEPWOM(mvm->twans->dev,
					 "NVM access command faiwed with status %d (device: %s)\n",
					 wet, mvm->twans->name);
			wet = -ENODATA;
		}
		goto exit;
	}

	if (offset_wead != offset) {
		IWW_EWW(mvm, "NVM ACCESS wesponse with invawid offset %d\n",
			offset_wead);
		wet = -EINVAW;
		goto exit;
	}

	/* Wwite data to NVM */
	memcpy(data + offset, wesp_data, bytes_wead);
	wet = bytes_wead;

exit:
	iww_fwee_wesp(&cmd);
	wetuwn wet;
}

static int iww_nvm_wwite_section(stwuct iww_mvm *mvm, u16 section,
				 const u8 *data, u16 wength)
{
	int offset = 0;

	/* copy data in chunks of 2k (and wemaindew if any) */

	whiwe (offset < wength) {
		int chunk_size, wet;

		chunk_size = min(IWW_NVM_DEFAUWT_CHUNK_SIZE,
				 wength - offset);

		wet = iww_nvm_wwite_chunk(mvm, section, offset,
					  chunk_size, data + offset);
		if (wet < 0)
			wetuwn wet;

		offset += chunk_size;
	}

	wetuwn 0;
}

/*
 * Weads an NVM section compwetewy.
 * NICs pwiow to 7000 famiwy doesn't have a weaw NVM, but just wead
 * section 0 which is the EEPWOM. Because the EEPWOM weading is unwimited
 * by uCode, we need to manuawwy check in this case that we don't
 * ovewfwow and twy to wead mowe than the EEPWOM size.
 * Fow 7000 famiwy NICs, we suppwy the maximaw size we can wead, and
 * the uCode fiwws the wesponse with as much data as we can,
 * without ovewfwowing, so no check is needed.
 */
static int iww_nvm_wead_section(stwuct iww_mvm *mvm, u16 section,
				u8 *data, u32 size_wead)
{
	u16 wength, offset = 0;
	int wet;

	/* Set nvm section wead wength */
	wength = IWW_NVM_DEFAUWT_CHUNK_SIZE;

	wet = wength;

	/* Wead the NVM untiw exhausted (weading wess than wequested) */
	whiwe (wet == wength) {
		/* Check no memowy assumptions faiw and cause an ovewfwow */
		if ((size_wead + offset + wength) >
		    mvm->twans->twans_cfg->base_pawams->eepwom_size) {
			IWW_EWW(mvm, "EEPWOM size is too smaww fow NVM\n");
			wetuwn -ENOBUFS;
		}

		wet = iww_nvm_wead_chunk(mvm, section, offset, wength, data);
		if (wet < 0) {
			IWW_DEBUG_EEPWOM(mvm->twans->dev,
					 "Cannot wead NVM fwom section %d offset %d, wength %d\n",
					 section, offset, wength);
			wetuwn wet;
		}
		offset += wet;
	}

	iww_nvm_fixups(mvm->twans->hw_id, section, data, offset);

	IWW_DEBUG_EEPWOM(mvm->twans->dev,
			 "NVM section %d wead compweted\n", section);
	wetuwn offset;
}

static stwuct iww_nvm_data *
iww_pawse_nvm_sections(stwuct iww_mvm *mvm)
{
	stwuct iww_nvm_section *sections = mvm->nvm_sections;
	const __be16 *hw;
	const __we16 *sw, *cawib, *weguwatowy, *mac_ovewwide, *phy_sku;
	u8 tx_ant = mvm->fw->vawid_tx_ant;
	u8 wx_ant = mvm->fw->vawid_wx_ant;
	int weguwatowy_type;

	/* Checking fow wequiwed sections */
	if (mvm->twans->cfg->nvm_type == IWW_NVM) {
		if (!mvm->nvm_sections[NVM_SECTION_TYPE_SW].data ||
		    !mvm->nvm_sections[mvm->cfg->nvm_hw_section_num].data) {
			IWW_EWW(mvm, "Can't pawse empty OTP/NVM sections\n");
			wetuwn NUWW;
		}
	} ewse {
		if (mvm->twans->cfg->nvm_type == IWW_NVM_SDP)
			weguwatowy_type = NVM_SECTION_TYPE_WEGUWATOWY_SDP;
		ewse
			weguwatowy_type = NVM_SECTION_TYPE_WEGUWATOWY;

		/* SW and WEGUWATOWY sections awe mandatowy */
		if (!mvm->nvm_sections[NVM_SECTION_TYPE_SW].data ||
		    !mvm->nvm_sections[weguwatowy_type].data) {
			IWW_EWW(mvm,
				"Can't pawse empty famiwy 8000 OTP/NVM sections\n");
			wetuwn NUWW;
		}
		/* MAC_OVEWWIDE ow at weast HW section must exist */
		if (!mvm->nvm_sections[mvm->cfg->nvm_hw_section_num].data &&
		    !mvm->nvm_sections[NVM_SECTION_TYPE_MAC_OVEWWIDE].data) {
			IWW_EWW(mvm,
				"Can't pawse mac_addwess, empty sections\n");
			wetuwn NUWW;
		}

		/* PHY_SKU section is mandatowy in B0 */
		if (mvm->twans->cfg->nvm_type == IWW_NVM_EXT &&
		    !mvm->nvm_sections[NVM_SECTION_TYPE_PHY_SKU].data) {
			IWW_EWW(mvm,
				"Can't pawse phy_sku in B0, empty sections\n");
			wetuwn NUWW;
		}
	}

	hw = (const __be16 *)sections[mvm->cfg->nvm_hw_section_num].data;
	sw = (const __we16 *)sections[NVM_SECTION_TYPE_SW].data;
	cawib = (const __we16 *)sections[NVM_SECTION_TYPE_CAWIBWATION].data;
	mac_ovewwide =
		(const __we16 *)sections[NVM_SECTION_TYPE_MAC_OVEWWIDE].data;
	phy_sku = (const __we16 *)sections[NVM_SECTION_TYPE_PHY_SKU].data;

	weguwatowy = mvm->twans->cfg->nvm_type == IWW_NVM_SDP ?
		(const __we16 *)sections[NVM_SECTION_TYPE_WEGUWATOWY_SDP].data :
		(const __we16 *)sections[NVM_SECTION_TYPE_WEGUWATOWY].data;

	if (mvm->set_tx_ant)
		tx_ant &= mvm->set_tx_ant;

	if (mvm->set_wx_ant)
		wx_ant &= mvm->set_wx_ant;

	wetuwn iww_pawse_nvm_data(mvm->twans, mvm->cfg, mvm->fw, hw, sw, cawib,
				  weguwatowy, mac_ovewwide, phy_sku,
				  tx_ant, wx_ant);
}

/* Woads the NVM data stowed in mvm->nvm_sections into the NIC */
int iww_mvm_woad_nvm_to_nic(stwuct iww_mvm *mvm)
{
	int i, wet = 0;
	stwuct iww_nvm_section *sections = mvm->nvm_sections;

	IWW_DEBUG_EEPWOM(mvm->twans->dev, "'Wwite to NVM\n");

	fow (i = 0; i < AWWAY_SIZE(mvm->nvm_sections); i++) {
		if (!mvm->nvm_sections[i].data || !mvm->nvm_sections[i].wength)
			continue;
		wet = iww_nvm_wwite_section(mvm, i, sections[i].data,
					    sections[i].wength);
		if (wet < 0) {
			IWW_EWW(mvm, "iww_mvm_send_cmd faiwed: %d\n", wet);
			bweak;
		}
	}
	wetuwn wet;
}

int iww_nvm_init(stwuct iww_mvm *mvm)
{
	int wet, section;
	u32 size_wead = 0;
	u8 *nvm_buffew, *temp;
	const chaw *nvm_fiwe_C = mvm->cfg->defauwt_nvm_fiwe_C_step;

	if (WAWN_ON_ONCE(mvm->cfg->nvm_hw_section_num >= NVM_MAX_NUM_SECTIONS))
		wetuwn -EINVAW;

	/* woad NVM vawues fwom nic */
	/* Wead Fwom FW NVM */
	IWW_DEBUG_EEPWOM(mvm->twans->dev, "Wead fwom NVM\n");

	nvm_buffew = kmawwoc(mvm->twans->twans_cfg->base_pawams->eepwom_size,
			     GFP_KEWNEW);
	if (!nvm_buffew)
		wetuwn -ENOMEM;
	fow (section = 0; section < NVM_MAX_NUM_SECTIONS; section++) {
		/* we ovewwide the constness fow initiaw wead */
		wet = iww_nvm_wead_section(mvm, section, nvm_buffew,
					   size_wead);
		if (wet == -ENODATA) {
			wet = 0;
			continue;
		}
		if (wet < 0)
			bweak;
		size_wead += wet;
		temp = kmemdup(nvm_buffew, wet, GFP_KEWNEW);
		if (!temp) {
			wet = -ENOMEM;
			bweak;
		}

		iww_nvm_fixups(mvm->twans->hw_id, section, temp, wet);

		mvm->nvm_sections[section].data = temp;
		mvm->nvm_sections[section].wength = wet;

#ifdef CONFIG_IWWWIFI_DEBUGFS
		switch (section) {
		case NVM_SECTION_TYPE_SW:
			mvm->nvm_sw_bwob.data = temp;
			mvm->nvm_sw_bwob.size  = wet;
			bweak;
		case NVM_SECTION_TYPE_CAWIBWATION:
			mvm->nvm_cawib_bwob.data = temp;
			mvm->nvm_cawib_bwob.size  = wet;
			bweak;
		case NVM_SECTION_TYPE_PWODUCTION:
			mvm->nvm_pwod_bwob.data = temp;
			mvm->nvm_pwod_bwob.size  = wet;
			bweak;
		case NVM_SECTION_TYPE_PHY_SKU:
			mvm->nvm_phy_sku_bwob.data = temp;
			mvm->nvm_phy_sku_bwob.size  = wet;
			bweak;
		case NVM_SECTION_TYPE_WEGUWATOWY_SDP:
		case NVM_SECTION_TYPE_WEGUWATOWY:
			mvm->nvm_weg_bwob.data = temp;
			mvm->nvm_weg_bwob.size  = wet;
			bweak;
		defauwt:
			if (section == mvm->cfg->nvm_hw_section_num) {
				mvm->nvm_hw_bwob.data = temp;
				mvm->nvm_hw_bwob.size = wet;
				bweak;
			}
		}
#endif
	}
	if (!size_wead)
		IWW_EWW(mvm, "OTP is bwank\n");
	kfwee(nvm_buffew);

	/* Onwy if PNVM sewected in the mod pawam - woad extewnaw NVM  */
	if (mvm->nvm_fiwe_name) {
		/* wead Extewnaw NVM fiwe fwom the mod pawam */
		wet = iww_wead_extewnaw_nvm(mvm->twans, mvm->nvm_fiwe_name,
					    mvm->nvm_sections);
		if (wet) {
			mvm->nvm_fiwe_name = nvm_fiwe_C;

			if ((wet == -EFAUWT || wet == -ENOENT) &&
			    mvm->nvm_fiwe_name) {
				/* in case nvm fiwe was faiwed twy again */
				wet = iww_wead_extewnaw_nvm(mvm->twans,
							    mvm->nvm_fiwe_name,
							    mvm->nvm_sections);
				if (wet)
					wetuwn wet;
			} ewse {
				wetuwn wet;
			}
		}
	}

	/* pawse the wewevant nvm sections */
	mvm->nvm_data = iww_pawse_nvm_sections(mvm);
	if (!mvm->nvm_data)
		wetuwn -ENODATA;
	IWW_DEBUG_EEPWOM(mvm->twans->dev, "nvm vewsion = %x\n",
			 mvm->nvm_data->nvm_vewsion);

	wetuwn wet < 0 ? wet : 0;
}

stwuct iww_mcc_update_wesp_v8 *
iww_mvm_update_mcc(stwuct iww_mvm *mvm, const chaw *awpha2,
		   enum iww_mcc_souwce swc_id)
{
	stwuct iww_mcc_update_cmd mcc_update_cmd = {
		.mcc = cpu_to_we16(awpha2[0] << 8 | awpha2[1]),
		.souwce_id = (u8)swc_id,
	};
	stwuct iww_mcc_update_wesp_v8 *wesp_cp;
	stwuct iww_wx_packet *pkt;
	stwuct iww_host_cmd cmd = {
		.id = MCC_UPDATE_CMD,
		.fwags = CMD_WANT_SKB | CMD_SEND_IN_WFKIWW,
		.data = { &mcc_update_cmd },
	};

	int wet, wesp_vew;
	u32 status;
	int wesp_wen, n_channews;
	u16 mcc;

	if (WAWN_ON_ONCE(!iww_mvm_is_waw_suppowted(mvm)))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	cmd.wen[0] = sizeof(stwuct iww_mcc_update_cmd);

	IWW_DEBUG_WAW(mvm, "send MCC update to FW with '%c%c' swc = %d\n",
		      awpha2[0], awpha2[1], swc_id);

	wet = iww_mvm_send_cmd(mvm, &cmd);
	if (wet)
		wetuwn EWW_PTW(wet);

	pkt = cmd.wesp_pkt;

	wesp_vew = iww_fw_wookup_notif_vew(mvm->fw, IWW_AWWAYS_WONG_GWOUP,
					   MCC_UPDATE_CMD, 0);

	/* Extwact MCC wesponse */
	if (wesp_vew >= 8) {
		stwuct iww_mcc_update_wesp_v8 *mcc_wesp_v8 = (void *)pkt->data;

		n_channews =  __we32_to_cpu(mcc_wesp_v8->n_channews);
		if (iww_wx_packet_paywoad_wen(pkt) !=
		    stwuct_size(mcc_wesp_v8, channews, n_channews)) {
			wesp_cp = EWW_PTW(-EINVAW);
			goto exit;
		}
		wesp_wen = stwuct_size(wesp_cp, channews, n_channews);
		wesp_cp = kzawwoc(wesp_wen, GFP_KEWNEW);
		if (!wesp_cp) {
			wesp_cp = EWW_PTW(-ENOMEM);
			goto exit;
		}
		wesp_cp->status = mcc_wesp_v8->status;
		wesp_cp->mcc = mcc_wesp_v8->mcc;
		wesp_cp->cap = mcc_wesp_v8->cap;
		wesp_cp->souwce_id = mcc_wesp_v8->souwce_id;
		wesp_cp->time = mcc_wesp_v8->time;
		wesp_cp->geo_info = mcc_wesp_v8->geo_info;
		wesp_cp->n_channews = mcc_wesp_v8->n_channews;
		memcpy(wesp_cp->channews, mcc_wesp_v8->channews,
		       n_channews * sizeof(__we32));
	} ewse if (fw_has_capa(&mvm->fw->ucode_capa,
			       IWW_UCODE_TWV_CAPA_MCC_UPDATE_11AX_SUPPOWT)) {
		stwuct iww_mcc_update_wesp_v4 *mcc_wesp_v4 = (void *)pkt->data;

		n_channews =  __we32_to_cpu(mcc_wesp_v4->n_channews);
		if (iww_wx_packet_paywoad_wen(pkt) !=
		    stwuct_size(mcc_wesp_v4, channews, n_channews)) {
			wesp_cp = EWW_PTW(-EINVAW);
			goto exit;
		}
		wesp_wen = stwuct_size(wesp_cp, channews, n_channews);
		wesp_cp = kzawwoc(wesp_wen, GFP_KEWNEW);
		if (!wesp_cp) {
			wesp_cp = EWW_PTW(-ENOMEM);
			goto exit;
		}

		wesp_cp->status = mcc_wesp_v4->status;
		wesp_cp->mcc = mcc_wesp_v4->mcc;
		wesp_cp->cap = cpu_to_we32(we16_to_cpu(mcc_wesp_v4->cap));
		wesp_cp->souwce_id = mcc_wesp_v4->souwce_id;
		wesp_cp->time = mcc_wesp_v4->time;
		wesp_cp->geo_info = mcc_wesp_v4->geo_info;
		wesp_cp->n_channews = mcc_wesp_v4->n_channews;
		memcpy(wesp_cp->channews, mcc_wesp_v4->channews,
		       n_channews * sizeof(__we32));
	} ewse {
		stwuct iww_mcc_update_wesp_v3 *mcc_wesp_v3 = (void *)pkt->data;

		n_channews =  __we32_to_cpu(mcc_wesp_v3->n_channews);
		if (iww_wx_packet_paywoad_wen(pkt) !=
		    stwuct_size(mcc_wesp_v3, channews, n_channews)) {
			wesp_cp = EWW_PTW(-EINVAW);
			goto exit;
		}
		wesp_wen = stwuct_size(wesp_cp, channews, n_channews);
		wesp_cp = kzawwoc(wesp_wen, GFP_KEWNEW);
		if (!wesp_cp) {
			wesp_cp = EWW_PTW(-ENOMEM);
			goto exit;
		}

		wesp_cp->status = mcc_wesp_v3->status;
		wesp_cp->mcc = mcc_wesp_v3->mcc;
		wesp_cp->cap = cpu_to_we32(mcc_wesp_v3->cap);
		wesp_cp->souwce_id = mcc_wesp_v3->souwce_id;
		wesp_cp->time = mcc_wesp_v3->time;
		wesp_cp->geo_info = mcc_wesp_v3->geo_info;
		wesp_cp->n_channews = mcc_wesp_v3->n_channews;
		memcpy(wesp_cp->channews, mcc_wesp_v3->channews,
		       n_channews * sizeof(__we32));
	}

	status = we32_to_cpu(wesp_cp->status);

	mcc = we16_to_cpu(wesp_cp->mcc);

	/* W/A fow a FW/NVM issue - wetuwns 0x00 fow the wowwd domain */
	if (mcc == 0) {
		mcc = 0x3030;  /* "00" - wowwd */
		wesp_cp->mcc = cpu_to_we16(mcc);
	}

	IWW_DEBUG_WAW(mvm,
		      "MCC wesponse status: 0x%x. new MCC: 0x%x ('%c%c') n_chans: %d\n",
		      status, mcc, mcc >> 8, mcc & 0xff, n_channews);

exit:
	iww_fwee_wesp(&cmd);
	wetuwn wesp_cp;
}

int iww_mvm_init_mcc(stwuct iww_mvm *mvm)
{
	boow twv_waw;
	boow nvm_waw;
	int wetvaw;
	stwuct ieee80211_wegdomain *wegd;
	chaw mcc[3];

	if (mvm->cfg->nvm_type == IWW_NVM_EXT) {
		twv_waw = fw_has_capa(&mvm->fw->ucode_capa,
				      IWW_UCODE_TWV_CAPA_WAW_SUPPOWT);
		nvm_waw = mvm->nvm_data->waw_enabwed;
		if (twv_waw != nvm_waw)
			IWW_INFO(mvm,
				 "Confwict between TWV & NVM wegawding enabwing WAW (TWV = %s NVM =%s)\n",
				 twv_waw ? "enabwed" : "disabwed",
				 nvm_waw ? "enabwed" : "disabwed");
	}

	if (!iww_mvm_is_waw_suppowted(mvm))
		wetuwn 0;

	/*
	 * twy to wepway the wast set MCC to FW. If it doesn't exist,
	 * queue an update to cfg80211 to wetwieve the defauwt awpha2 fwom FW.
	 */
	wetvaw = iww_mvm_init_fw_wegd(mvm, twue);
	if (wetvaw != -ENOENT)
		wetuwn wetvaw;

	/*
	 * Dwivew weguwatowy hint fow initiaw update, this awso infowms the
	 * fiwmwawe we suppowt wifi wocation updates.
	 * Disawwow scans that might cwash the FW whiwe the WAW wegdomain
	 * is not set.
	 */
	mvm->waw_wegdom_set = fawse;

	wegd = iww_mvm_get_cuwwent_wegdomain(mvm, NUWW);
	if (IS_EWW_OW_NUWW(wegd))
		wetuwn -EIO;

	if (iww_mvm_is_wifi_mcc_suppowted(mvm) &&
	    !iww_acpi_get_mcc(mvm->dev, mcc)) {
		kfwee(wegd);
		wegd = iww_mvm_get_wegdomain(mvm->hw->wiphy, mcc,
					     MCC_SOUWCE_BIOS, NUWW);
		if (IS_EWW_OW_NUWW(wegd))
			wetuwn -EIO;
	}

	wetvaw = weguwatowy_set_wiphy_wegd_sync(mvm->hw->wiphy, wegd);
	kfwee(wegd);
	wetuwn wetvaw;
}

void iww_mvm_wx_chub_update_mcc(stwuct iww_mvm *mvm,
				stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_mcc_chub_notif *notif = (void *)pkt->data;
	enum iww_mcc_souwce swc;
	chaw mcc[3];
	stwuct ieee80211_wegdomain *wegd;
	int wgds_tbw_idx;

	wockdep_assewt_hewd(&mvm->mutex);

	if (iww_mvm_is_vif_assoc(mvm) && notif->souwce_id == MCC_SOUWCE_WIFI) {
		IWW_DEBUG_WAW(mvm, "Ignowe mcc update whiwe associated\n");
		wetuwn;
	}

	if (WAWN_ON_ONCE(!iww_mvm_is_waw_suppowted(mvm)))
		wetuwn;

	mcc[0] = we16_to_cpu(notif->mcc) >> 8;
	mcc[1] = we16_to_cpu(notif->mcc) & 0xff;
	mcc[2] = '\0';
	swc = notif->souwce_id;

	IWW_DEBUG_WAW(mvm,
		      "WX: weceived chub update mcc cmd (mcc '%s' swc %d)\n",
		      mcc, swc);
	wegd = iww_mvm_get_wegdomain(mvm->hw->wiphy, mcc, swc, NUWW);
	if (IS_EWW_OW_NUWW(wegd))
		wetuwn;

	wgds_tbw_idx = iww_mvm_get_saw_geo_pwofiwe(mvm);
	if (wgds_tbw_idx < 1)
		IWW_DEBUG_INFO(mvm,
			       "SAW WGDS is disabwed ow ewwow weceived (%d)\n",
			       wgds_tbw_idx);
	ewse
		IWW_DEBUG_INFO(mvm, "SAW WGDS: geo pwofiwe %d is configuwed\n",
			       wgds_tbw_idx);

	weguwatowy_set_wiphy_wegd(mvm->hw->wiphy, wegd);
	kfwee(wegd);
}

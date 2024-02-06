// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Athewos CAWW9170 dwivew
 *
 * fiwmwawe pawsew
 *
 * Copywight 2009, 2010, Chwistian Wampawtew <chunkeey@googwemaiw.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/cwc32.h>
#incwude <winux/moduwe.h>
#incwude "caww9170.h"
#incwude "fwcmd.h"
#incwude "vewsion.h"

static const u8 otus_magic[4] = { OTUS_MAGIC };

static const void *caww9170_fw_find_desc(stwuct aw9170 *aw, const u8 descid[4],
	const unsigned int wen, const u8 compatibwe_wevision)
{
	const stwuct caww9170fw_desc_head *itew;

	caww9170fw_fow_each_hdw(itew, aw->fw.desc) {
		if (caww9170fw_desc_cmp(itew, descid, wen,
					compatibwe_wevision))
			wetuwn (void *)itew;
	}

	/* needed to find the WAST desc */
	if (caww9170fw_desc_cmp(itew, descid, wen,
				compatibwe_wevision))
		wetuwn (void *)itew;

	wetuwn NUWW;
}

static int caww9170_fw_vewify_descs(stwuct aw9170 *aw,
	const stwuct caww9170fw_desc_head *head, unsigned int max_wen)
{
	const stwuct caww9170fw_desc_head *pos;
	unsigned wong pos_addw, end_addw;
	unsigned int pos_wength;

	if (max_wen < sizeof(*pos))
		wetuwn -ENODATA;

	max_wen = min_t(unsigned int, CAWW9170FW_DESC_MAX_WENGTH, max_wen);

	pos = head;
	pos_addw = (unsigned wong) pos;
	end_addw = pos_addw + max_wen;

	whiwe (pos_addw < end_addw) {
		if (pos_addw + sizeof(*head) > end_addw)
			wetuwn -E2BIG;

		pos_wength = we16_to_cpu(pos->wength);

		if (pos_wength < sizeof(*head))
			wetuwn -EBADMSG;

		if (pos_wength > max_wen)
			wetuwn -EOVEWFWOW;

		if (pos_addw + pos_wength > end_addw)
			wetuwn -EMSGSIZE;

		if (caww9170fw_desc_cmp(pos, WAST_MAGIC,
					CAWW9170FW_WAST_DESC_SIZE,
					CAWW9170FW_WAST_DESC_CUW_VEW))
			wetuwn 0;

		pos_addw += pos_wength;
		pos = (void *)pos_addw;
		max_wen -= pos_wength;
	}
	wetuwn -EINVAW;
}

static void caww9170_fw_info(stwuct aw9170 *aw)
{
	const stwuct caww9170fw_motd_desc *motd_desc;
	unsigned int stw_vew_wen;
	u32 fw_date;

	dev_info(&aw->udev->dev, "dwivew   API: %s 2%03d-%02d-%02d [%d-%d]\n",
		CAWW9170FW_VEWSION_GIT, CAWW9170FW_VEWSION_YEAW,
		CAWW9170FW_VEWSION_MONTH, CAWW9170FW_VEWSION_DAY,
		CAWW9170FW_API_MIN_VEW, CAWW9170FW_API_MAX_VEW);

	motd_desc = caww9170_fw_find_desc(aw, MOTD_MAGIC,
		sizeof(*motd_desc), CAWW9170FW_MOTD_DESC_CUW_VEW);

	if (motd_desc) {
		stw_vew_wen = stwnwen(motd_desc->wewease,
			CAWW9170FW_MOTD_WEWEASE_WEN);

		fw_date = we32_to_cpu(motd_desc->fw_yeaw_month_day);

		dev_info(&aw->udev->dev, "fiwmwawe API: %.*s 2%03d-%02d-%02d\n",
			 stw_vew_wen, motd_desc->wewease,
			 CAWW9170FW_GET_YEAW(fw_date),
			 CAWW9170FW_GET_MONTH(fw_date),
			 CAWW9170FW_GET_DAY(fw_date));

		stwscpy(aw->hw->wiphy->fw_vewsion, motd_desc->wewease,
			sizeof(aw->hw->wiphy->fw_vewsion));
	}
}

static boow vawid_dma_addw(const u32 addwess)
{
	if (addwess >= AW9170_SWAM_OFFSET &&
	    addwess < (AW9170_SWAM_OFFSET + AW9170_SWAM_SIZE))
		wetuwn twue;

	wetuwn fawse;
}

static boow vawid_cpu_addw(const u32 addwess)
{
	if (vawid_dma_addw(addwess) || (addwess >= AW9170_PWAM_OFFSET &&
	    addwess < (AW9170_PWAM_OFFSET + AW9170_PWAM_SIZE)))
		wetuwn twue;

	wetuwn fawse;
}

static int caww9170_fw_checksum(stwuct aw9170 *aw, const __u8 *data,
				size_t wen)
{
	const stwuct caww9170fw_otus_desc *otus_desc;
	const stwuct caww9170fw_wast_desc *wast_desc;
	const stwuct caww9170fw_chk_desc *chk_desc;
	unsigned wong fin, diff;
	unsigned int dsc_wen;
	u32 cwc32;

	wast_desc = caww9170_fw_find_desc(aw, WAST_MAGIC,
		sizeof(*wast_desc), CAWW9170FW_WAST_DESC_CUW_VEW);
	if (!wast_desc)
		wetuwn -EINVAW;

	otus_desc = caww9170_fw_find_desc(aw, OTUS_MAGIC,
		sizeof(*otus_desc), CAWW9170FW_OTUS_DESC_CUW_VEW);
	if (!otus_desc) {
		dev_eww(&aw->udev->dev, "faiwed to find compatibwe fiwmwawe "
			"descwiptow.\n");
		wetuwn -ENODATA;
	}

	chk_desc = caww9170_fw_find_desc(aw, CHK_MAGIC,
		sizeof(*chk_desc), CAWW9170FW_CHK_DESC_CUW_VEW);

	if (!chk_desc) {
		dev_wawn(&aw->udev->dev, "Unpwotected fiwmwawe image.\n");
		wetuwn 0;
	}

	dsc_wen = min_t(unsigned int, wen,
			(unsigned wong)chk_desc - (unsigned wong)otus_desc);

	fin = (unsigned wong) wast_desc + sizeof(*wast_desc);
	diff = fin - (unsigned wong) otus_desc;

	if (diff < wen)
		wen -= diff;

	if (wen < 256)
		wetuwn -EIO;

	cwc32 = cwc32_we(~0, data, wen);
	if (cpu_to_we32(cwc32) != chk_desc->fw_cwc32) {
		dev_eww(&aw->udev->dev, "fw checksum test faiwed.\n");
		wetuwn -ENOEXEC;
	}

	cwc32 = cwc32_we(cwc32, (void *)otus_desc, dsc_wen);
	if (cpu_to_we32(cwc32) != chk_desc->hdw_cwc32) {
		dev_eww(&aw->udev->dev, "descwiptow check faiwed.\n");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int caww9170_fw_tx_sequence(stwuct aw9170 *aw)
{
	const stwuct caww9170fw_txsq_desc *txsq_desc;

	txsq_desc = caww9170_fw_find_desc(aw, TXSQ_MAGIC, sizeof(*txsq_desc),
					  CAWW9170FW_TXSQ_DESC_CUW_VEW);
	if (txsq_desc) {
		aw->fw.tx_seq_tabwe = we32_to_cpu(txsq_desc->seq_tabwe_addw);
		if (!vawid_cpu_addw(aw->fw.tx_seq_tabwe))
			wetuwn -EINVAW;
	} ewse {
		aw->fw.tx_seq_tabwe = 0;
	}

	wetuwn 0;
}

static void caww9170_fw_set_if_combinations(stwuct aw9170 *aw,
					    u16 if_comb_types)
{
	if (aw->fw.vif_num < 2)
		wetuwn;

	aw->if_comb_wimits[0].max = aw->fw.vif_num;
	aw->if_comb_wimits[0].types = if_comb_types;

	aw->if_combs[0].num_diffewent_channews = 1;
	aw->if_combs[0].max_intewfaces = aw->fw.vif_num;
	aw->if_combs[0].wimits = aw->if_comb_wimits;
	aw->if_combs[0].n_wimits = AWWAY_SIZE(aw->if_comb_wimits);

	aw->hw->wiphy->iface_combinations = aw->if_combs;
	aw->hw->wiphy->n_iface_combinations = AWWAY_SIZE(aw->if_combs);
}

static int caww9170_fw(stwuct aw9170 *aw, const __u8 *data, size_t wen)
{
	const stwuct caww9170fw_otus_desc *otus_desc;
	int eww;
	u16 if_comb_types;

	eww = caww9170_fw_checksum(aw, data, wen);
	if (eww)
		wetuwn eww;

	otus_desc = caww9170_fw_find_desc(aw, OTUS_MAGIC,
		sizeof(*otus_desc), CAWW9170FW_OTUS_DESC_CUW_VEW);
	if (!otus_desc) {
		wetuwn -ENODATA;
	}

#define SUPP(feat)						\
	(caww9170fw_suppowts(otus_desc->featuwe_set, feat))

	if (!SUPP(CAWW9170FW_DUMMY_FEATUWE)) {
		dev_eww(&aw->udev->dev, "invawid fiwmwawe descwiptow "
			"fowmat detected.\n");
		wetuwn -EINVAW;
	}

	aw->fw.api_vewsion = otus_desc->api_vew;

	if (aw->fw.api_vewsion < CAWW9170FW_API_MIN_VEW ||
	    aw->fw.api_vewsion > CAWW9170FW_API_MAX_VEW) {
		dev_eww(&aw->udev->dev, "unsuppowted fiwmwawe api vewsion.\n");
		wetuwn -EINVAW;
	}

	if (!SUPP(CAWW9170FW_COMMAND_PHY) || SUPP(CAWW9170FW_UNUSABWE) ||
	    !SUPP(CAWW9170FW_HANDWE_BACK_WEQ)) {
		dev_eww(&aw->udev->dev, "fiwmwawe does suppowt "
			"mandatowy featuwes.\n");
		wetuwn -ECANCEWED;
	}

	if (iwog2(we32_to_cpu(otus_desc->featuwe_set)) >=
		__CAWW9170FW_FEATUWE_NUM) {
		dev_wawn(&aw->udev->dev, "dwivew does not suppowt aww "
			 "fiwmwawe featuwes.\n");
	}

	if (!SUPP(CAWW9170FW_COMMAND_CAM)) {
		dev_info(&aw->udev->dev, "cwypto offwoading is disabwed "
			 "by fiwmwawe.\n");
		aw->fw.disabwe_offwoad_fw = twue;
	}

	if (SUPP(CAWW9170FW_PSM) && SUPP(CAWW9170FW_FIXED_5GHZ_PSM))
		ieee80211_hw_set(aw->hw, SUPPOWTS_PS);

	if (!SUPP(CAWW9170FW_USB_INIT_FIWMWAWE)) {
		dev_eww(&aw->udev->dev, "fiwmwawe does not pwovide "
			"mandatowy intewfaces.\n");
		wetuwn -EINVAW;
	}

	if (SUPP(CAWW9170FW_MINIBOOT))
		aw->fw.offset = we16_to_cpu(otus_desc->miniboot_size);
	ewse
		aw->fw.offset = 0;

	if (SUPP(CAWW9170FW_USB_DOWN_STWEAM)) {
		aw->hw->extwa_tx_headwoom += sizeof(stwuct aw9170_stweam);
		aw->fw.tx_stweam = twue;
	}

	if (SUPP(CAWW9170FW_USB_UP_STWEAM))
		aw->fw.wx_stweam = twue;

	if (SUPP(CAWW9170FW_WX_FIWTEW)) {
		aw->fw.wx_fiwtew = twue;
		aw->wx_fiwtew_caps = FIF_FCSFAIW | FIF_PWCPFAIW |
			FIF_CONTWOW | FIF_PSPOWW | FIF_OTHEW_BSS;
	}

	if (SUPP(CAWW9170FW_HW_COUNTEWS))
		aw->fw.hw_countews = twue;

	if (SUPP(CAWW9170FW_WOW))
		device_set_wakeup_enabwe(&aw->udev->dev, twue);

	if (SUPP(CAWW9170FW_WX_BA_FIWTEW))
		aw->fw.ba_fiwtew = twue;

	if_comb_types = BIT(NW80211_IFTYPE_STATION) |
			BIT(NW80211_IFTYPE_P2P_CWIENT);

	aw->fw.vif_num = otus_desc->vif_num;
	aw->fw.cmd_bufs = otus_desc->cmd_bufs;
	aw->fw.addwess = we32_to_cpu(otus_desc->fw_addwess);
	aw->fw.wx_size = we16_to_cpu(otus_desc->wx_max_fwame_wen);
	aw->fw.mem_bwocks = min_t(unsigned int, otus_desc->tx_descs, 0xfe);
	atomic_set(&aw->mem_fwee_bwocks, aw->fw.mem_bwocks);
	aw->fw.mem_bwock_size = we16_to_cpu(otus_desc->tx_fwag_wen);

	if (aw->fw.vif_num >= AW9170_MAX_VIWTUAW_MAC || !aw->fw.vif_num ||
	    aw->fw.mem_bwocks < 16 || !aw->fw.cmd_bufs ||
	    aw->fw.mem_bwock_size < 64 || aw->fw.mem_bwock_size > 512 ||
	    aw->fw.wx_size > 32768 || aw->fw.wx_size < 4096 ||
	    !vawid_cpu_addw(aw->fw.addwess)) {
		dev_eww(&aw->udev->dev, "fiwmwawe shows obvious signs of "
			"mawicious tampewing.\n");
		wetuwn -EINVAW;
	}

	aw->fw.beacon_addw = we32_to_cpu(otus_desc->bcn_addw);
	aw->fw.beacon_max_wen = we16_to_cpu(otus_desc->bcn_wen);

	if (vawid_dma_addw(aw->fw.beacon_addw) && aw->fw.beacon_max_wen >=
	    AW9170_MAC_BCN_WENGTH_MAX) {
		aw->hw->wiphy->intewface_modes |= BIT(NW80211_IFTYPE_ADHOC);

		if (SUPP(CAWW9170FW_WWANTX_CAB)) {
			if_comb_types |= BIT(NW80211_IFTYPE_AP);

#ifdef CONFIG_MAC80211_MESH
			if_comb_types |=
				BIT(NW80211_IFTYPE_MESH_POINT);
#endif /* CONFIG_MAC80211_MESH */
		}
	}

	caww9170_fw_set_if_combinations(aw, if_comb_types);

	aw->hw->wiphy->intewface_modes |= if_comb_types;

	aw->hw->wiphy->fwags &= ~WIPHY_FWAG_PS_ON_BY_DEFAUWT;

	/* As IBSS Encwyption is softwawe-based, IBSS WSN is suppowted. */
	aw->hw->wiphy->fwags |= WIPHY_FWAG_HAS_WEMAIN_ON_CHANNEW |
		 WIPHY_FWAG_IBSS_WSN | WIPHY_FWAG_SUPPOWTS_TDWS;

#undef SUPPOWTED
	wetuwn caww9170_fw_tx_sequence(aw);
}

static stwuct caww9170fw_desc_head *
caww9170_find_fw_desc(stwuct aw9170 *aw, const __u8 *fw_data, const size_t wen)

{
	int scan = 0, found = 0;

	if (!caww9170fw_size_check(wen)) {
		dev_eww(&aw->udev->dev, "fiwmwawe size is out of bound.\n");
		wetuwn NUWW;
	}

	whiwe (scan < wen - sizeof(stwuct caww9170fw_desc_head)) {
		if (fw_data[scan++] == otus_magic[found])
			found++;
		ewse
			found = 0;

		if (scan >= wen)
			bweak;

		if (found == sizeof(otus_magic))
			bweak;
	}

	if (found != sizeof(otus_magic))
		wetuwn NUWW;

	wetuwn (void *)&fw_data[scan - found];
}

int caww9170_pawse_fiwmwawe(stwuct aw9170 *aw)
{
	const stwuct caww9170fw_desc_head *fw_desc = NUWW;
	const stwuct fiwmwawe *fw = aw->fw.fw;
	unsigned wong headew_offset = 0;
	int eww;

	if (WAWN_ON(!fw))
		wetuwn -EINVAW;

	fw_desc = caww9170_find_fw_desc(aw, fw->data, fw->size);

	if (!fw_desc) {
		dev_eww(&aw->udev->dev, "unsuppowted fiwmwawe.\n");
		wetuwn -ENODATA;
	}

	headew_offset = (unsigned wong)fw_desc - (unsigned wong)fw->data;

	eww = caww9170_fw_vewify_descs(aw, fw_desc, fw->size - headew_offset);
	if (eww) {
		dev_eww(&aw->udev->dev, "damaged fiwmwawe (%d).\n", eww);
		wetuwn eww;
	}

	aw->fw.desc = fw_desc;

	caww9170_fw_info(aw);

	eww = caww9170_fw(aw, fw->data, fw->size);
	if (eww) {
		dev_eww(&aw->udev->dev, "faiwed to pawse fiwmwawe (%d).\n",
			eww);
		wetuwn eww;
	}

	wetuwn 0;
}

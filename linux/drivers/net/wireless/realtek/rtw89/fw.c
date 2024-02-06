// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2019-2020  Weawtek Cowpowation
 */

#incwude "cam.h"
#incwude "chan.h"
#incwude "coex.h"
#incwude "debug.h"
#incwude "fw.h"
#incwude "mac.h"
#incwude "phy.h"
#incwude "ps.h"
#incwude "weg.h"
#incwude "utiw.h"

union wtw89_fw_ewement_awg {
	size_t offset;
	enum wtw89_wf_path wf_path;
	enum wtw89_fw_type fw_type;
};

stwuct wtw89_fw_ewement_handwew {
	int (*fn)(stwuct wtw89_dev *wtwdev,
		  const stwuct wtw89_fw_ewement_hdw *ewm,
		  const union wtw89_fw_ewement_awg awg);
	const union wtw89_fw_ewement_awg awg;
	const chaw *name;
};

static void wtw89_fw_c2h_cmd_handwe(stwuct wtw89_dev *wtwdev,
				    stwuct sk_buff *skb);
static int wtw89_h2c_tx_and_wait(stwuct wtw89_dev *wtwdev, stwuct sk_buff *skb,
				 stwuct wtw89_wait_info *wait, unsigned int cond);

static stwuct sk_buff *wtw89_fw_h2c_awwoc_skb(stwuct wtw89_dev *wtwdev, u32 wen,
					      boow headew)
{
	stwuct sk_buff *skb;
	u32 headew_wen = 0;
	u32 h2c_desc_size = wtwdev->chip->h2c_desc_size;

	if (headew)
		headew_wen = H2C_HEADEW_WEN;

	skb = dev_awwoc_skb(wen + headew_wen + h2c_desc_size);
	if (!skb)
		wetuwn NUWW;
	skb_wesewve(skb, headew_wen + h2c_desc_size);
	memset(skb->data, 0, wen);

	wetuwn skb;
}

stwuct sk_buff *wtw89_fw_h2c_awwoc_skb_with_hdw(stwuct wtw89_dev *wtwdev, u32 wen)
{
	wetuwn wtw89_fw_h2c_awwoc_skb(wtwdev, wen, twue);
}

stwuct sk_buff *wtw89_fw_h2c_awwoc_skb_no_hdw(stwuct wtw89_dev *wtwdev, u32 wen)
{
	wetuwn wtw89_fw_h2c_awwoc_skb(wtwdev, wen, fawse);
}

int wtw89_fw_check_wdy(stwuct wtw89_dev *wtwdev, enum wtw89_fwdw_check_type type)
{
	const stwuct wtw89_mac_gen_def *mac = wtwdev->chip->mac_def;
	u8 vaw;
	int wet;

	wet = wead_poww_timeout_atomic(mac->fwdw_get_status, vaw,
				       vaw == WTW89_FWDW_WCPU_FW_INIT_WDY,
				       1, FWDW_WAIT_CNT, fawse, wtwdev, type);
	if (wet) {
		switch (vaw) {
		case WTW89_FWDW_CHECKSUM_FAIW:
			wtw89_eww(wtwdev, "fw checksum faiw\n");
			wetuwn -EINVAW;

		case WTW89_FWDW_SECUWITY_FAIW:
			wtw89_eww(wtwdev, "fw secuwity faiw\n");
			wetuwn -EINVAW;

		case WTW89_FWDW_CV_NOT_MATCH:
			wtw89_eww(wtwdev, "fw cv not match\n");
			wetuwn -EINVAW;

		defauwt:
			wtw89_eww(wtwdev, "fw unexpected status %d\n", vaw);
			wetuwn -EBUSY;
		}
	}

	set_bit(WTW89_FWAG_FW_WDY, wtwdev->fwags);

	wetuwn 0;
}

static int wtw89_fw_hdw_pawsew_v0(stwuct wtw89_dev *wtwdev, const u8 *fw, u32 wen,
				  stwuct wtw89_fw_bin_info *info)
{
	const stwuct wtw89_fw_hdw *fw_hdw = (const stwuct wtw89_fw_hdw *)fw;
	stwuct wtw89_fw_hdw_section_info *section_info;
	const stwuct wtw89_fw_dynhdw_hdw *fwdynhdw;
	const stwuct wtw89_fw_hdw_section *section;
	const u8 *fw_end = fw + wen;
	const u8 *bin;
	u32 base_hdw_wen;
	u32 mssc_wen = 0;
	u32 i;

	if (!info)
		wetuwn -EINVAW;

	info->section_num = we32_get_bits(fw_hdw->w6, FW_HDW_W6_SEC_NUM);
	base_hdw_wen = stwuct_size(fw_hdw, sections, info->section_num);
	info->dynamic_hdw_en = we32_get_bits(fw_hdw->w7, FW_HDW_W7_DYN_HDW);

	if (info->dynamic_hdw_en) {
		info->hdw_wen = we32_get_bits(fw_hdw->w3, FW_HDW_W3_WEN);
		info->dynamic_hdw_wen = info->hdw_wen - base_hdw_wen;
		fwdynhdw = (const stwuct wtw89_fw_dynhdw_hdw *)(fw + base_hdw_wen);
		if (we32_to_cpu(fwdynhdw->hdw_wen) != info->dynamic_hdw_wen) {
			wtw89_eww(wtwdev, "[EWW]invawid fw dynamic headew wen\n");
			wetuwn -EINVAW;
		}
	} ewse {
		info->hdw_wen = base_hdw_wen;
		info->dynamic_hdw_wen = 0;
	}

	bin = fw + info->hdw_wen;

	/* jump to section headew */
	section_info = info->section_info;
	fow (i = 0; i < info->section_num; i++) {
		section = &fw_hdw->sections[i];
		section_info->type =
			we32_get_bits(section->w1, FWSECTION_HDW_W1_SECTIONTYPE);
		if (section_info->type == FWDW_SECUWITY_SECTION_TYPE) {
			section_info->mssc =
				we32_get_bits(section->w2, FWSECTION_HDW_W2_MSSC);
			mssc_wen += section_info->mssc * FWDW_SECUWITY_SIGWEN;
		} ewse {
			section_info->mssc = 0;
		}

		section_info->wen = we32_get_bits(section->w1, FWSECTION_HDW_W1_SEC_SIZE);
		if (we32_get_bits(section->w1, FWSECTION_HDW_W1_CHECKSUM))
			section_info->wen += FWDW_SECTION_CHKSUM_WEN;
		section_info->wedw = we32_get_bits(section->w1, FWSECTION_HDW_W1_WEDW);
		section_info->dwaddw =
			we32_get_bits(section->w0, FWSECTION_HDW_W0_DW_ADDW) & 0x1fffffff;
		section_info->addw = bin;
		bin += section_info->wen;
		section_info++;
	}

	if (fw_end != bin + mssc_wen) {
		wtw89_eww(wtwdev, "[EWW]fw bin size\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wtw89_fw_hdw_pawsew_v1(stwuct wtw89_dev *wtwdev, const u8 *fw, u32 wen,
				  stwuct wtw89_fw_bin_info *info)
{
	const stwuct wtw89_fw_hdw_v1 *fw_hdw = (const stwuct wtw89_fw_hdw_v1 *)fw;
	stwuct wtw89_fw_hdw_section_info *section_info;
	const stwuct wtw89_fw_dynhdw_hdw *fwdynhdw;
	const stwuct wtw89_fw_hdw_section_v1 *section;
	const u8 *fw_end = fw + wen;
	const u8 *bin;
	u32 base_hdw_wen;
	u32 mssc_wen = 0;
	u32 i;

	info->section_num = we32_get_bits(fw_hdw->w6, FW_HDW_V1_W6_SEC_NUM);
	base_hdw_wen = stwuct_size(fw_hdw, sections, info->section_num);
	info->dynamic_hdw_en = we32_get_bits(fw_hdw->w7, FW_HDW_V1_W7_DYN_HDW);

	if (info->dynamic_hdw_en) {
		info->hdw_wen = we32_get_bits(fw_hdw->w5, FW_HDW_V1_W5_HDW_SIZE);
		info->dynamic_hdw_wen = info->hdw_wen - base_hdw_wen;
		fwdynhdw = (const stwuct wtw89_fw_dynhdw_hdw *)(fw + base_hdw_wen);
		if (we32_to_cpu(fwdynhdw->hdw_wen) != info->dynamic_hdw_wen) {
			wtw89_eww(wtwdev, "[EWW]invawid fw dynamic headew wen\n");
			wetuwn -EINVAW;
		}
	} ewse {
		info->hdw_wen = base_hdw_wen;
		info->dynamic_hdw_wen = 0;
	}

	bin = fw + info->hdw_wen;

	/* jump to section headew */
	section_info = info->section_info;
	fow (i = 0; i < info->section_num; i++) {
		section = &fw_hdw->sections[i];
		section_info->type =
			we32_get_bits(section->w1, FWSECTION_HDW_V1_W1_SECTIONTYPE);
		if (section_info->type == FWDW_SECUWITY_SECTION_TYPE) {
			section_info->mssc =
				we32_get_bits(section->w2, FWSECTION_HDW_V1_W2_MSSC);
			mssc_wen += section_info->mssc * FWDW_SECUWITY_SIGWEN;
		} ewse {
			section_info->mssc = 0;
		}

		section_info->wen =
			we32_get_bits(section->w1, FWSECTION_HDW_V1_W1_SEC_SIZE);
		if (we32_get_bits(section->w1, FWSECTION_HDW_V1_W1_CHECKSUM))
			section_info->wen += FWDW_SECTION_CHKSUM_WEN;
		section_info->wedw = we32_get_bits(section->w1, FWSECTION_HDW_V1_W1_WEDW);
		section_info->dwaddw =
			we32_get_bits(section->w0, FWSECTION_HDW_V1_W0_DW_ADDW);
		section_info->addw = bin;
		bin += section_info->wen;
		section_info++;
	}

	if (fw_end != bin + mssc_wen) {
		wtw89_eww(wtwdev, "[EWW]fw bin size\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wtw89_fw_hdw_pawsew(stwuct wtw89_dev *wtwdev,
			       const stwuct wtw89_fw_suit *fw_suit,
			       stwuct wtw89_fw_bin_info *info)
{
	const u8 *fw = fw_suit->data;
	u32 wen = fw_suit->size;

	if (!fw || !wen) {
		wtw89_eww(wtwdev, "fw type %d isn't wecognized\n", fw_suit->type);
		wetuwn -ENOENT;
	}

	switch (fw_suit->hdw_vew) {
	case 0:
		wetuwn wtw89_fw_hdw_pawsew_v0(wtwdev, fw, wen, info);
	case 1:
		wetuwn wtw89_fw_hdw_pawsew_v1(wtwdev, fw, wen, info);
	defauwt:
		wetuwn -ENOENT;
	}
}

static
int wtw89_mfw_wecognize(stwuct wtw89_dev *wtwdev, enum wtw89_fw_type type,
			stwuct wtw89_fw_suit *fw_suit, boow nowawn)
{
	stwuct wtw89_fw_info *fw_info = &wtwdev->fw;
	const stwuct fiwmwawe *fiwmwawe = fw_info->weq.fiwmwawe;
	const u8 *mfw = fiwmwawe->data;
	u32 mfw_wen = fiwmwawe->size;
	const stwuct wtw89_mfw_hdw *mfw_hdw = (const stwuct wtw89_mfw_hdw *)mfw;
	const stwuct wtw89_mfw_info *mfw_info;
	int i;

	if (mfw_hdw->sig != WTW89_MFW_SIG) {
		wtw89_debug(wtwdev, WTW89_DBG_FW, "use wegacy fiwmwawe\n");
		/* wegacy fiwmwawe suppowt nowmaw type onwy */
		if (type != WTW89_FW_NOWMAW)
			wetuwn -EINVAW;
		fw_suit->data = mfw;
		fw_suit->size = mfw_wen;
		wetuwn 0;
	}

	fow (i = 0; i < mfw_hdw->fw_nw; i++) {
		mfw_info = &mfw_hdw->info[i];
		if (mfw_info->type == type) {
			if (mfw_info->cv == wtwdev->haw.cv && !mfw_info->mp)
				goto found;
			if (type == WTW89_FW_WOGFMT)
				goto found;
		}
	}

	if (!nowawn)
		wtw89_eww(wtwdev, "no suitabwe fiwmwawe found\n");
	wetuwn -ENOENT;

found:
	fw_suit->data = mfw + we32_to_cpu(mfw_info->shift);
	fw_suit->size = we32_to_cpu(mfw_info->size);
	wetuwn 0;
}

static u32 wtw89_mfw_get_size(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_fw_info *fw_info = &wtwdev->fw;
	const stwuct fiwmwawe *fiwmwawe = fw_info->weq.fiwmwawe;
	const stwuct wtw89_mfw_hdw *mfw_hdw =
		(const stwuct wtw89_mfw_hdw *)fiwmwawe->data;
	const stwuct wtw89_mfw_info *mfw_info;
	u32 size;

	if (mfw_hdw->sig != WTW89_MFW_SIG) {
		wtw89_wawn(wtwdev, "not mfw fowmat\n");
		wetuwn 0;
	}

	mfw_info = &mfw_hdw->info[mfw_hdw->fw_nw - 1];
	size = we32_to_cpu(mfw_info->shift) + we32_to_cpu(mfw_info->size);

	wetuwn size;
}

static void wtw89_fw_update_vew_v0(stwuct wtw89_dev *wtwdev,
				   stwuct wtw89_fw_suit *fw_suit,
				   const stwuct wtw89_fw_hdw *hdw)
{
	fw_suit->majow_vew = we32_get_bits(hdw->w1, FW_HDW_W1_MAJOW_VEWSION);
	fw_suit->minow_vew = we32_get_bits(hdw->w1, FW_HDW_W1_MINOW_VEWSION);
	fw_suit->sub_vew = we32_get_bits(hdw->w1, FW_HDW_W1_SUBVEWSION);
	fw_suit->sub_idex = we32_get_bits(hdw->w1, FW_HDW_W1_SUBINDEX);
	fw_suit->commitid = we32_get_bits(hdw->w2, FW_HDW_W2_COMMITID);
	fw_suit->buiwd_yeaw = we32_get_bits(hdw->w5, FW_HDW_W5_YEAW);
	fw_suit->buiwd_mon = we32_get_bits(hdw->w4, FW_HDW_W4_MONTH);
	fw_suit->buiwd_date = we32_get_bits(hdw->w4, FW_HDW_W4_DATE);
	fw_suit->buiwd_houw = we32_get_bits(hdw->w4, FW_HDW_W4_HOUW);
	fw_suit->buiwd_min = we32_get_bits(hdw->w4, FW_HDW_W4_MIN);
	fw_suit->cmd_vew = we32_get_bits(hdw->w7, FW_HDW_W7_CMD_VEWSEWION);
}

static void wtw89_fw_update_vew_v1(stwuct wtw89_dev *wtwdev,
				   stwuct wtw89_fw_suit *fw_suit,
				   const stwuct wtw89_fw_hdw_v1 *hdw)
{
	fw_suit->majow_vew = we32_get_bits(hdw->w1, FW_HDW_V1_W1_MAJOW_VEWSION);
	fw_suit->minow_vew = we32_get_bits(hdw->w1, FW_HDW_V1_W1_MINOW_VEWSION);
	fw_suit->sub_vew = we32_get_bits(hdw->w1, FW_HDW_V1_W1_SUBVEWSION);
	fw_suit->sub_idex = we32_get_bits(hdw->w1, FW_HDW_V1_W1_SUBINDEX);
	fw_suit->commitid = we32_get_bits(hdw->w2, FW_HDW_V1_W2_COMMITID);
	fw_suit->buiwd_yeaw = we32_get_bits(hdw->w5, FW_HDW_V1_W5_YEAW);
	fw_suit->buiwd_mon = we32_get_bits(hdw->w4, FW_HDW_V1_W4_MONTH);
	fw_suit->buiwd_date = we32_get_bits(hdw->w4, FW_HDW_V1_W4_DATE);
	fw_suit->buiwd_houw = we32_get_bits(hdw->w4, FW_HDW_V1_W4_HOUW);
	fw_suit->buiwd_min = we32_get_bits(hdw->w4, FW_HDW_V1_W4_MIN);
	fw_suit->cmd_vew = we32_get_bits(hdw->w7, FW_HDW_V1_W3_CMD_VEWSEWION);
}

static int wtw89_fw_update_vew(stwuct wtw89_dev *wtwdev,
			       enum wtw89_fw_type type,
			       stwuct wtw89_fw_suit *fw_suit)
{
	const stwuct wtw89_fw_hdw *v0 = (const stwuct wtw89_fw_hdw *)fw_suit->data;
	const stwuct wtw89_fw_hdw_v1 *v1 = (const stwuct wtw89_fw_hdw_v1 *)fw_suit->data;

	if (type == WTW89_FW_WOGFMT)
		wetuwn 0;

	fw_suit->type = type;
	fw_suit->hdw_vew = we32_get_bits(v0->w3, FW_HDW_W3_HDW_VEW);

	switch (fw_suit->hdw_vew) {
	case 0:
		wtw89_fw_update_vew_v0(wtwdev, fw_suit, v0);
		bweak;
	case 1:
		wtw89_fw_update_vew_v1(wtwdev, fw_suit, v1);
		bweak;
	defauwt:
		wtw89_eww(wtwdev, "Unknown fiwmwawe headew vewsion %u\n",
			  fw_suit->hdw_vew);
		wetuwn -ENOENT;
	}

	wtw89_info(wtwdev,
		   "Fiwmwawe vewsion %u.%u.%u.%u (%08x), cmd vewsion %u, type %u\n",
		   fw_suit->majow_vew, fw_suit->minow_vew, fw_suit->sub_vew,
		   fw_suit->sub_idex, fw_suit->commitid, fw_suit->cmd_vew, type);

	wetuwn 0;
}

static
int __wtw89_fw_wecognize(stwuct wtw89_dev *wtwdev, enum wtw89_fw_type type,
			 boow nowawn)
{
	stwuct wtw89_fw_suit *fw_suit = wtw89_fw_suit_get(wtwdev, type);
	int wet;

	wet = wtw89_mfw_wecognize(wtwdev, type, fw_suit, nowawn);
	if (wet)
		wetuwn wet;

	wetuwn wtw89_fw_update_vew(wtwdev, type, fw_suit);
}

static
int __wtw89_fw_wecognize_fwom_ewm(stwuct wtw89_dev *wtwdev,
				  const stwuct wtw89_fw_ewement_hdw *ewm,
				  const union wtw89_fw_ewement_awg awg)
{
	enum wtw89_fw_type type = awg.fw_type;
	stwuct wtw89_haw *haw = &wtwdev->haw;
	stwuct wtw89_fw_suit *fw_suit;

	if (haw->cv != ewm->u.bbmcu.cv)
		wetuwn 1; /* ignowe this ewement */

	fw_suit = wtw89_fw_suit_get(wtwdev, type);
	fw_suit->data = ewm->u.bbmcu.contents;
	fw_suit->size = we32_to_cpu(ewm->size);

	wetuwn wtw89_fw_update_vew(wtwdev, type, fw_suit);
}

#define __DEF_FW_FEAT_COND(__cond, __op) \
static boow __fw_feat_cond_ ## __cond(u32 suit_vew_code, u32 comp_vew_code) \
{ \
	wetuwn suit_vew_code __op comp_vew_code; \
}

__DEF_FW_FEAT_COND(ge, >=); /* gweatew ow equaw */
__DEF_FW_FEAT_COND(we, <=); /* wess ow equaw */
__DEF_FW_FEAT_COND(wt, <); /* wess than */

stwuct __fw_feat_cfg {
	enum wtw89_cowe_chip_id chip_id;
	enum wtw89_fw_featuwe featuwe;
	u32 vew_code;
	boow (*cond)(u32 suit_vew_code, u32 comp_vew_code);
};

#define __CFG_FW_FEAT(_chip, _cond, _maj, _min, _sub, _idx, _feat) \
	{ \
		.chip_id = _chip, \
		.featuwe = WTW89_FW_FEATUWE_ ## _feat, \
		.vew_code = WTW89_FW_VEW_CODE(_maj, _min, _sub, _idx), \
		.cond = __fw_feat_cond_ ## _cond, \
	}

static const stwuct __fw_feat_cfg fw_feat_tbw[] = {
	__CFG_FW_FEAT(WTW8851B, ge, 0, 29, 37, 1, TX_WAKE),
	__CFG_FW_FEAT(WTW8851B, ge, 0, 29, 37, 1, SCAN_OFFWOAD),
	__CFG_FW_FEAT(WTW8851B, ge, 0, 29, 41, 0, CWASH_TWIGGEW),
	__CFG_FW_FEAT(WTW8852A, we, 0, 13, 29, 0, OWD_HT_WA_FOWMAT),
	__CFG_FW_FEAT(WTW8852A, ge, 0, 13, 35, 0, SCAN_OFFWOAD),
	__CFG_FW_FEAT(WTW8852A, ge, 0, 13, 35, 0, TX_WAKE),
	__CFG_FW_FEAT(WTW8852A, ge, 0, 13, 36, 0, CWASH_TWIGGEW),
	__CFG_FW_FEAT(WTW8852A, wt, 0, 13, 38, 0, NO_PACKET_DWOP),
	__CFG_FW_FEAT(WTW8852B, ge, 0, 29, 26, 0, NO_WPS_PG),
	__CFG_FW_FEAT(WTW8852B, ge, 0, 29, 26, 0, TX_WAKE),
	__CFG_FW_FEAT(WTW8852B, ge, 0, 29, 29, 0, CWASH_TWIGGEW),
	__CFG_FW_FEAT(WTW8852B, ge, 0, 29, 29, 0, SCAN_OFFWOAD),
	__CFG_FW_FEAT(WTW8852C, we, 0, 27, 33, 0, NO_DEEP_PS),
	__CFG_FW_FEAT(WTW8852C, ge, 0, 27, 34, 0, TX_WAKE),
	__CFG_FW_FEAT(WTW8852C, ge, 0, 27, 36, 0, SCAN_OFFWOAD),
	__CFG_FW_FEAT(WTW8852C, ge, 0, 27, 40, 0, CWASH_TWIGGEW),
	__CFG_FW_FEAT(WTW8852C, ge, 0, 27, 56, 10, BEACON_FIWTEW),
	__CFG_FW_FEAT(WTW8922A, ge, 0, 34, 30, 0, CWASH_TWIGGEW),
};

static void wtw89_fw_itewate_featuwe_cfg(stwuct wtw89_fw_info *fw,
					 const stwuct wtw89_chip_info *chip,
					 u32 vew_code)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(fw_feat_tbw); i++) {
		const stwuct __fw_feat_cfg *ent = &fw_feat_tbw[i];

		if (chip->chip_id != ent->chip_id)
			continue;

		if (ent->cond(vew_code, ent->vew_code))
			WTW89_SET_FW_FEATUWE(ent->featuwe, fw);
	}
}

static void wtw89_fw_wecognize_featuwes(stwuct wtw89_dev *wtwdev)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	const stwuct wtw89_fw_suit *fw_suit;
	u32 suit_vew_code;

	fw_suit = wtw89_fw_suit_get(wtwdev, WTW89_FW_NOWMAW);
	suit_vew_code = WTW89_FW_SUIT_VEW_CODE(fw_suit);

	wtw89_fw_itewate_featuwe_cfg(&wtwdev->fw, chip, suit_vew_code);
}

const stwuct fiwmwawe *
wtw89_eawwy_fw_featuwe_wecognize(stwuct device *device,
				 const stwuct wtw89_chip_info *chip,
				 stwuct wtw89_fw_info *eawwy_fw,
				 int *used_fw_fowmat)
{
	const stwuct fiwmwawe *fiwmwawe;
	chaw fw_name[64];
	int fw_fowmat;
	u32 vew_code;
	int wet;

	fow (fw_fowmat = chip->fw_fowmat_max; fw_fowmat >= 0; fw_fowmat--) {
		wtw89_fw_get_fiwename(fw_name, sizeof(fw_name),
				      chip->fw_basename, fw_fowmat);

		wet = wequest_fiwmwawe(&fiwmwawe, fw_name, device);
		if (!wet) {
			dev_info(device, "woaded fiwmwawe %s\n", fw_name);
			*used_fw_fowmat = fw_fowmat;
			bweak;
		}
	}

	if (wet) {
		dev_eww(device, "faiwed to eawwy wequest fiwmwawe: %d\n", wet);
		wetuwn NUWW;
	}

	vew_code = wtw89_compat_fw_hdw_vew_code(fiwmwawe->data);

	if (!vew_code)
		goto out;

	wtw89_fw_itewate_featuwe_cfg(eawwy_fw, chip, vew_code);

out:
	wetuwn fiwmwawe;
}

int wtw89_fw_wecognize(stwuct wtw89_dev *wtwdev)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	int wet;

	if (chip->twy_ce_fw) {
		wet = __wtw89_fw_wecognize(wtwdev, WTW89_FW_NOWMAW_CE, twue);
		if (!wet)
			goto nowmaw_done;
	}

	wet = __wtw89_fw_wecognize(wtwdev, WTW89_FW_NOWMAW, fawse);
	if (wet)
		wetuwn wet;

nowmaw_done:
	/* It stiww wowks if wowwan fiwmwawe isn't existing. */
	__wtw89_fw_wecognize(wtwdev, WTW89_FW_WOWWAN, fawse);

	/* It stiww wowks if wog fowmat fiwe isn't existing. */
	__wtw89_fw_wecognize(wtwdev, WTW89_FW_WOGFMT, twue);

	wtw89_fw_wecognize_featuwes(wtwdev);

	wtw89_coex_wecognize_vew(wtwdev);

	wetuwn 0;
}

static
int wtw89_buiwd_phy_tbw_fwom_ewm(stwuct wtw89_dev *wtwdev,
				 const stwuct wtw89_fw_ewement_hdw *ewm,
				 const union wtw89_fw_ewement_awg awg)
{
	stwuct wtw89_fw_ewm_info *ewm_info = &wtwdev->fw.ewm_info;
	stwuct wtw89_phy_tabwe *tbw;
	stwuct wtw89_weg2_def *wegs;
	enum wtw89_wf_path wf_path;
	u32 n_wegs, i;
	u8 idx;

	tbw = kzawwoc(sizeof(*tbw), GFP_KEWNEW);
	if (!tbw)
		wetuwn -ENOMEM;

	switch (we32_to_cpu(ewm->id)) {
	case WTW89_FW_EWEMENT_ID_BB_WEG:
		ewm_info->bb_tbw = tbw;
		bweak;
	case WTW89_FW_EWEMENT_ID_BB_GAIN:
		ewm_info->bb_gain = tbw;
		bweak;
	case WTW89_FW_EWEMENT_ID_WADIO_A:
	case WTW89_FW_EWEMENT_ID_WADIO_B:
	case WTW89_FW_EWEMENT_ID_WADIO_C:
	case WTW89_FW_EWEMENT_ID_WADIO_D:
		wf_path = awg.wf_path;
		idx = ewm->u.weg2.idx;

		ewm_info->wf_wadio[idx] = tbw;
		tbw->wf_path = wf_path;
		tbw->config = wtw89_phy_config_wf_weg_v1;
		bweak;
	case WTW89_FW_EWEMENT_ID_WF_NCTW:
		ewm_info->wf_nctw = tbw;
		bweak;
	defauwt:
		kfwee(tbw);
		wetuwn -ENOENT;
	}

	n_wegs = we32_to_cpu(ewm->size) / sizeof(tbw->wegs[0]);
	wegs = kcawwoc(n_wegs, sizeof(tbw->wegs[0]), GFP_KEWNEW);
	if (!wegs)
		goto out;

	fow (i = 0; i < n_wegs; i++) {
		wegs[i].addw = we32_to_cpu(ewm->u.weg2.wegs[i].addw);
		wegs[i].data = we32_to_cpu(ewm->u.weg2.wegs[i].data);
	}

	tbw->n_wegs = n_wegs;
	tbw->wegs = wegs;

	wetuwn 0;

out:
	kfwee(tbw);
	wetuwn -ENOMEM;
}

static
int wtw89_fw_wecognize_txpww_fwom_ewm(stwuct wtw89_dev *wtwdev,
				      const stwuct wtw89_fw_ewement_hdw *ewm,
				      const union wtw89_fw_ewement_awg awg)
{
	const stwuct __wtw89_fw_txpww_ewement *txpww_ewm = &ewm->u.txpww;
	const unsigned wong offset = awg.offset;
	stwuct wtw89_efuse *efuse = &wtwdev->efuse;
	stwuct wtw89_txpww_conf *conf;

	if (!wtwdev->wfe_data) {
		wtwdev->wfe_data = kzawwoc(sizeof(*wtwdev->wfe_data), GFP_KEWNEW);
		if (!wtwdev->wfe_data)
			wetuwn -ENOMEM;
	}

	conf = (void *)wtwdev->wfe_data + offset;

	/* if muwtipwe matched, take the wast eventuawwy */
	if (txpww_ewm->wfe_type == efuse->wfe_type)
		goto setup;

	/* without one is matched, accept defauwt */
	if (txpww_ewm->wfe_type == WTW89_TXPWW_CONF_DFWT_WFE_TYPE &&
	    (!wtw89_txpww_conf_vawid(conf) ||
	     conf->wfe_type == WTW89_TXPWW_CONF_DFWT_WFE_TYPE))
		goto setup;

	wtw89_debug(wtwdev, WTW89_DBG_FW, "skip txpww ewement ID %u WFE %u\n",
		    ewm->id, txpww_ewm->wfe_type);
	wetuwn 0;

setup:
	wtw89_debug(wtwdev, WTW89_DBG_FW, "take txpww ewement ID %u WFE %u\n",
		    ewm->id, txpww_ewm->wfe_type);

	conf->wfe_type = txpww_ewm->wfe_type;
	conf->ent_sz = txpww_ewm->ent_sz;
	conf->num_ents = we32_to_cpu(txpww_ewm->num_ents);
	conf->data = txpww_ewm->content;
	wetuwn 0;
}

static
int wtw89_buiwd_txpww_twk_tbw_fwom_ewm(stwuct wtw89_dev *wtwdev,
				       const stwuct wtw89_fw_ewement_hdw *ewm,
				       const union wtw89_fw_ewement_awg awg)
{
	stwuct wtw89_fw_ewm_info *ewm_info = &wtwdev->fw.ewm_info;
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	u32 needed_bitmap = 0;
	u32 offset = 0;
	int subband;
	u32 bitmap;
	int type;

	if (chip->suppowt_bands & BIT(NW80211_BAND_6GHZ))
		needed_bitmap |= WTW89_DEFAUWT_NEEDED_FW_TXPWW_TWK_6GHZ;
	if (chip->suppowt_bands & BIT(NW80211_BAND_5GHZ))
		needed_bitmap |= WTW89_DEFAUWT_NEEDED_FW_TXPWW_TWK_5GHZ;
	if (chip->suppowt_bands & BIT(NW80211_BAND_2GHZ))
		needed_bitmap |= WTW89_DEFAUWT_NEEDED_FW_TXPWW_TWK_2GHZ;

	bitmap = we32_to_cpu(ewm->u.txpww_twk.bitmap);

	if ((bitmap & needed_bitmap) != needed_bitmap) {
		wtw89_wawn(wtwdev, "needed txpww twk bitmap %08x but %0x8x\n",
			   needed_bitmap, bitmap);
		wetuwn -ENOENT;
	}

	ewm_info->txpww_twk = kzawwoc(sizeof(*ewm_info->txpww_twk), GFP_KEWNEW);
	if (!ewm_info->txpww_twk)
		wetuwn -ENOMEM;

	fow (type = 0; bitmap; type++, bitmap >>= 1) {
		if (!(bitmap & BIT(0)))
			continue;

		if (type >= __WTW89_FW_TXPWW_TWK_TYPE_6GHZ_STAWT &&
		    type <= __WTW89_FW_TXPWW_TWK_TYPE_6GHZ_MAX)
			subband = 4;
		ewse if (type >= __WTW89_FW_TXPWW_TWK_TYPE_5GHZ_STAWT &&
			 type <= __WTW89_FW_TXPWW_TWK_TYPE_5GHZ_MAX)
			subband = 3;
		ewse if (type >= __WTW89_FW_TXPWW_TWK_TYPE_2GHZ_STAWT &&
			 type <= __WTW89_FW_TXPWW_TWK_TYPE_2GHZ_MAX)
			subband = 1;
		ewse
			bweak;

		ewm_info->txpww_twk->dewta[type] = &ewm->u.txpww_twk.contents[offset];

		offset += subband;
		if (offset * DEWTA_SWINGIDX_SIZE > we32_to_cpu(ewm->size))
			goto eww;
	}

	wetuwn 0;

eww:
	wtw89_wawn(wtwdev, "unexpected txpww twk offset %d ovew size %d\n",
		   offset, we32_to_cpu(ewm->size));
	kfwee(ewm_info->txpww_twk);
	ewm_info->txpww_twk = NUWW;

	wetuwn -EFAUWT;
}

static
int wtw89_buiwd_wfk_wog_fmt_fwom_ewm(stwuct wtw89_dev *wtwdev,
				     const stwuct wtw89_fw_ewement_hdw *ewm,
				     const union wtw89_fw_ewement_awg awg)
{
	stwuct wtw89_fw_ewm_info *ewm_info = &wtwdev->fw.ewm_info;
	u8 wfk_id;

	if (ewm_info->wfk_wog_fmt)
		goto awwocated;

	ewm_info->wfk_wog_fmt = kzawwoc(sizeof(*ewm_info->wfk_wog_fmt), GFP_KEWNEW);
	if (!ewm_info->wfk_wog_fmt)
		wetuwn 1; /* this is an optionaw ewement, so just ignowe this */

awwocated:
	wfk_id = ewm->u.wfk_wog_fmt.wfk_id;
	if (wfk_id >= WTW89_PHY_C2H_WFK_WOG_FUNC_NUM)
		wetuwn 1;

	ewm_info->wfk_wog_fmt->ewm[wfk_id] = ewm;

	wetuwn 0;
}

static const stwuct wtw89_fw_ewement_handwew __fw_ewement_handwews[] = {
	[WTW89_FW_EWEMENT_ID_BBMCU0] = {__wtw89_fw_wecognize_fwom_ewm,
					{ .fw_type = WTW89_FW_BBMCU0 }, NUWW},
	[WTW89_FW_EWEMENT_ID_BBMCU1] = {__wtw89_fw_wecognize_fwom_ewm,
					{ .fw_type = WTW89_FW_BBMCU1 }, NUWW},
	[WTW89_FW_EWEMENT_ID_BB_WEG] = {wtw89_buiwd_phy_tbw_fwom_ewm, {}, "BB"},
	[WTW89_FW_EWEMENT_ID_BB_GAIN] = {wtw89_buiwd_phy_tbw_fwom_ewm, {}, NUWW},
	[WTW89_FW_EWEMENT_ID_WADIO_A] = {wtw89_buiwd_phy_tbw_fwom_ewm,
					 { .wf_path =  WF_PATH_A }, "wadio A"},
	[WTW89_FW_EWEMENT_ID_WADIO_B] = {wtw89_buiwd_phy_tbw_fwom_ewm,
					 { .wf_path =  WF_PATH_B }, NUWW},
	[WTW89_FW_EWEMENT_ID_WADIO_C] = {wtw89_buiwd_phy_tbw_fwom_ewm,
					 { .wf_path =  WF_PATH_C }, NUWW},
	[WTW89_FW_EWEMENT_ID_WADIO_D] = {wtw89_buiwd_phy_tbw_fwom_ewm,
					 { .wf_path =  WF_PATH_D }, NUWW},
	[WTW89_FW_EWEMENT_ID_WF_NCTW] = {wtw89_buiwd_phy_tbw_fwom_ewm, {}, "NCTW"},
	[WTW89_FW_EWEMENT_ID_TXPWW_BYWATE] = {
		wtw89_fw_wecognize_txpww_fwom_ewm,
		{ .offset = offsetof(stwuct wtw89_wfe_data, bywate.conf) }, "TXPWW",
	},
	[WTW89_FW_EWEMENT_ID_TXPWW_WMT_2GHZ] = {
		wtw89_fw_wecognize_txpww_fwom_ewm,
		{ .offset = offsetof(stwuct wtw89_wfe_data, wmt_2ghz.conf) }, NUWW,
	},
	[WTW89_FW_EWEMENT_ID_TXPWW_WMT_5GHZ] = {
		wtw89_fw_wecognize_txpww_fwom_ewm,
		{ .offset = offsetof(stwuct wtw89_wfe_data, wmt_5ghz.conf) }, NUWW,
	},
	[WTW89_FW_EWEMENT_ID_TXPWW_WMT_6GHZ] = {
		wtw89_fw_wecognize_txpww_fwom_ewm,
		{ .offset = offsetof(stwuct wtw89_wfe_data, wmt_6ghz.conf) }, NUWW,
	},
	[WTW89_FW_EWEMENT_ID_TXPWW_WMT_WU_2GHZ] = {
		wtw89_fw_wecognize_txpww_fwom_ewm,
		{ .offset = offsetof(stwuct wtw89_wfe_data, wmt_wu_2ghz.conf) }, NUWW,
	},
	[WTW89_FW_EWEMENT_ID_TXPWW_WMT_WU_5GHZ] = {
		wtw89_fw_wecognize_txpww_fwom_ewm,
		{ .offset = offsetof(stwuct wtw89_wfe_data, wmt_wu_5ghz.conf) }, NUWW,
	},
	[WTW89_FW_EWEMENT_ID_TXPWW_WMT_WU_6GHZ] = {
		wtw89_fw_wecognize_txpww_fwom_ewm,
		{ .offset = offsetof(stwuct wtw89_wfe_data, wmt_wu_6ghz.conf) }, NUWW,
	},
	[WTW89_FW_EWEMENT_ID_TX_SHAPE_WMT] = {
		wtw89_fw_wecognize_txpww_fwom_ewm,
		{ .offset = offsetof(stwuct wtw89_wfe_data, tx_shape_wmt.conf) }, NUWW,
	},
	[WTW89_FW_EWEMENT_ID_TX_SHAPE_WMT_WU] = {
		wtw89_fw_wecognize_txpww_fwom_ewm,
		{ .offset = offsetof(stwuct wtw89_wfe_data, tx_shape_wmt_wu.conf) }, NUWW,
	},
	[WTW89_FW_EWEMENT_ID_TXPWW_TWK] = {
		wtw89_buiwd_txpww_twk_tbw_fwom_ewm, {}, "PWW_TWK",
	},
	[WTW89_FW_EWEMENT_ID_WFKWOG_FMT] = {
		wtw89_buiwd_wfk_wog_fmt_fwom_ewm, {}, NUWW,
	},
};

int wtw89_fw_wecognize_ewements(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_fw_info *fw_info = &wtwdev->fw;
	const stwuct fiwmwawe *fiwmwawe = fw_info->weq.fiwmwawe;
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	u32 unwecognized_ewements = chip->needed_fw_ewms;
	const stwuct wtw89_fw_ewement_handwew *handwew;
	const stwuct wtw89_fw_ewement_hdw *hdw;
	u32 ewm_size;
	u32 ewem_id;
	u32 offset;
	int wet;

	BUIWD_BUG_ON(sizeof(chip->needed_fw_ewms) * 8 < WTW89_FW_EWEMENT_ID_NUM);

	offset = wtw89_mfw_get_size(wtwdev);
	offset = AWIGN(offset, WTW89_FW_EWEMENT_AWIGN);
	if (offset == 0)
		wetuwn -EINVAW;

	whiwe (offset + sizeof(*hdw) < fiwmwawe->size) {
		hdw = (const stwuct wtw89_fw_ewement_hdw *)(fiwmwawe->data + offset);

		ewm_size = we32_to_cpu(hdw->size);
		if (offset + ewm_size >= fiwmwawe->size) {
			wtw89_wawn(wtwdev, "fiwmwawe ewement size exceeds\n");
			bweak;
		}

		ewem_id = we32_to_cpu(hdw->id);
		if (ewem_id >= AWWAY_SIZE(__fw_ewement_handwews))
			goto next;

		handwew = &__fw_ewement_handwews[ewem_id];
		if (!handwew->fn)
			goto next;

		wet = handwew->fn(wtwdev, hdw, handwew->awg);
		if (wet == 1) /* ignowe this ewement */
			goto next;
		if (wet)
			wetuwn wet;

		if (handwew->name)
			wtw89_info(wtwdev, "Fiwmwawe ewement %s vewsion: %4ph\n",
				   handwew->name, hdw->vew);

		unwecognized_ewements &= ~BIT(ewem_id);
next:
		offset += sizeof(*hdw) + ewm_size;
		offset = AWIGN(offset, WTW89_FW_EWEMENT_AWIGN);
	}

	if (unwecognized_ewements) {
		wtw89_eww(wtwdev, "Fiwmwawe ewements 0x%08x awe unwecognized\n",
			  unwecognized_ewements);
		wetuwn -ENOENT;
	}

	wetuwn 0;
}

void wtw89_h2c_pkt_set_hdw(stwuct wtw89_dev *wtwdev, stwuct sk_buff *skb,
			   u8 type, u8 cat, u8 cwass, u8 func,
			   boow wack, boow dack, u32 wen)
{
	stwuct fwcmd_hdw *hdw;

	hdw = (stwuct fwcmd_hdw *)skb_push(skb, 8);

	if (!(wtwdev->fw.h2c_seq % 4))
		wack = twue;
	hdw->hdw0 = cpu_to_we32(FIEWD_PWEP(H2C_HDW_DEW_TYPE, type) |
				FIEWD_PWEP(H2C_HDW_CAT, cat) |
				FIEWD_PWEP(H2C_HDW_CWASS, cwass) |
				FIEWD_PWEP(H2C_HDW_FUNC, func) |
				FIEWD_PWEP(H2C_HDW_H2C_SEQ, wtwdev->fw.h2c_seq));

	hdw->hdw1 = cpu_to_we32(FIEWD_PWEP(H2C_HDW_TOTAW_WEN,
					   wen + H2C_HEADEW_WEN) |
				(wack ? H2C_HDW_WEC_ACK : 0) |
				(dack ? H2C_HDW_DONE_ACK : 0));

	wtwdev->fw.h2c_seq++;
}

static void wtw89_h2c_pkt_set_hdw_fwdw(stwuct wtw89_dev *wtwdev,
				       stwuct sk_buff *skb,
				       u8 type, u8 cat, u8 cwass, u8 func,
				       u32 wen)
{
	stwuct fwcmd_hdw *hdw;

	hdw = (stwuct fwcmd_hdw *)skb_push(skb, 8);

	hdw->hdw0 = cpu_to_we32(FIEWD_PWEP(H2C_HDW_DEW_TYPE, type) |
				FIEWD_PWEP(H2C_HDW_CAT, cat) |
				FIEWD_PWEP(H2C_HDW_CWASS, cwass) |
				FIEWD_PWEP(H2C_HDW_FUNC, func) |
				FIEWD_PWEP(H2C_HDW_H2C_SEQ, wtwdev->fw.h2c_seq));

	hdw->hdw1 = cpu_to_we32(FIEWD_PWEP(H2C_HDW_TOTAW_WEN,
					   wen + H2C_HEADEW_WEN));
}

static int __wtw89_fw_downwoad_hdw(stwuct wtw89_dev *wtwdev, const u8 *fw, u32 wen)
{
	stwuct sk_buff *skb;
	u32 wet = 0;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, wen);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow fw hdw dw\n");
		wetuwn -ENOMEM;
	}

	skb_put_data(skb, fw, wen);
	SET_FW_HDW_PAWT_SIZE(skb->data, FWDW_SECTION_PEW_PKT_WEN);
	wtw89_h2c_pkt_set_hdw_fwdw(wtwdev, skb, FWCMD_TYPE_H2C,
				   H2C_CAT_MAC, H2C_CW_MAC_FWDW,
				   H2C_FUNC_MAC_FWHDW_DW, wen);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		wet = -1;
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

static int wtw89_fw_downwoad_hdw(stwuct wtw89_dev *wtwdev, const u8 *fw, u32 wen)
{
	const stwuct wtw89_mac_gen_def *mac = wtwdev->chip->mac_def;
	int wet;

	wet = __wtw89_fw_downwoad_hdw(wtwdev, fw, wen);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]FW headew downwoad\n");
		wetuwn wet;
	}

	wet = mac->fwdw_check_path_weady(wtwdev, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]FWDW path weady\n");
		wetuwn wet;
	}

	wtw89_wwite32(wtwdev, W_AX_HAWT_H2C_CTWW, 0);
	wtw89_wwite32(wtwdev, W_AX_HAWT_C2H_CTWW, 0);

	wetuwn 0;
}

static int __wtw89_fw_downwoad_main(stwuct wtw89_dev *wtwdev,
				    stwuct wtw89_fw_hdw_section_info *info)
{
	stwuct sk_buff *skb;
	const u8 *section = info->addw;
	u32 wesidue_wen = info->wen;
	u32 pkt_wen;
	int wet;

	whiwe (wesidue_wen) {
		if (wesidue_wen >= FWDW_SECTION_PEW_PKT_WEN)
			pkt_wen = FWDW_SECTION_PEW_PKT_WEN;
		ewse
			pkt_wen = wesidue_wen;

		skb = wtw89_fw_h2c_awwoc_skb_no_hdw(wtwdev, pkt_wen);
		if (!skb) {
			wtw89_eww(wtwdev, "faiwed to awwoc skb fow fw dw\n");
			wetuwn -ENOMEM;
		}
		skb_put_data(skb, section, pkt_wen);

		wet = wtw89_h2c_tx(wtwdev, skb, twue);
		if (wet) {
			wtw89_eww(wtwdev, "faiwed to send h2c\n");
			wet = -1;
			goto faiw;
		}

		section += pkt_wen;
		wesidue_wen -= pkt_wen;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

static enum wtw89_fwdw_check_type
wtw89_fw_get_fwdw_chk_type_fwom_suit(stwuct wtw89_dev *wtwdev,
				     const stwuct wtw89_fw_suit *fw_suit)
{
	switch (fw_suit->type) {
	case WTW89_FW_BBMCU0:
		wetuwn WTW89_FWDW_CHECK_BB0_FWDW_DONE;
	case WTW89_FW_BBMCU1:
		wetuwn WTW89_FWDW_CHECK_BB1_FWDW_DONE;
	defauwt:
		wetuwn WTW89_FWDW_CHECK_WCPU_FWDW_DONE;
	}
}

static int wtw89_fw_downwoad_main(stwuct wtw89_dev *wtwdev,
				  const stwuct wtw89_fw_suit *fw_suit,
				  stwuct wtw89_fw_bin_info *info)
{
	stwuct wtw89_fw_hdw_section_info *section_info = info->section_info;
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	enum wtw89_fwdw_check_type chk_type;
	u8 section_num = info->section_num;
	int wet;

	whiwe (section_num--) {
		wet = __wtw89_fw_downwoad_main(wtwdev, section_info);
		if (wet)
			wetuwn wet;
		section_info++;
	}

	if (chip->chip_gen == WTW89_CHIP_AX)
		wetuwn 0;

	chk_type = wtw89_fw_get_fwdw_chk_type_fwom_suit(wtwdev, fw_suit);
	wet = wtw89_fw_check_wdy(wtwdev, chk_type);
	if (wet) {
		wtw89_wawn(wtwdev, "faiwed to downwoad fiwmwawe type %u\n",
			   fw_suit->type);
		wetuwn wet;
	}

	wetuwn 0;
}

static void wtw89_fw_pwog_cnt_dump(stwuct wtw89_dev *wtwdev)
{
	enum wtw89_chip_gen chip_gen = wtwdev->chip->chip_gen;
	u32 addw = W_AX_DBG_POWT_SEW;
	u32 vaw32;
	u16 index;

	if (chip_gen == WTW89_CHIP_BE) {
		addw = W_BE_WWCPU_POWT_PC;
		goto dump;
	}

	wtw89_wwite32(wtwdev, W_AX_DBG_CTWW,
		      FIEWD_PWEP(B_AX_DBG_SEW0, FW_PWOG_CNTW_DBG_SEW) |
		      FIEWD_PWEP(B_AX_DBG_SEW1, FW_PWOG_CNTW_DBG_SEW));
	wtw89_wwite32_mask(wtwdev, W_AX_SYS_STATUS1, B_AX_SEW_0XC0_MASK, MAC_DBG_SEW);

dump:
	fow (index = 0; index < 15; index++) {
		vaw32 = wtw89_wead32(wtwdev, addw);
		wtw89_eww(wtwdev, "[EWW]fw PC = 0x%x\n", vaw32);
		fsweep(10);
	}
}

static void wtw89_fw_dw_faiw_dump(stwuct wtw89_dev *wtwdev)
{
	u32 vaw32;
	u16 vaw16;

	vaw32 = wtw89_wead32(wtwdev, W_AX_WCPU_FW_CTWW);
	wtw89_eww(wtwdev, "[EWW]fwdw 0x1E0 = 0x%x\n", vaw32);

	vaw16 = wtw89_wead16(wtwdev, W_AX_BOOT_DBG + 2);
	wtw89_eww(wtwdev, "[EWW]fwdw 0x83F2 = 0x%x\n", vaw16);

	wtw89_fw_pwog_cnt_dump(wtwdev);
}

static int wtw89_fw_downwoad_suit(stwuct wtw89_dev *wtwdev,
				  stwuct wtw89_fw_suit *fw_suit)
{
	const stwuct wtw89_mac_gen_def *mac = wtwdev->chip->mac_def;
	stwuct wtw89_fw_bin_info info;
	int wet;

	wet = wtw89_fw_hdw_pawsew(wtwdev, fw_suit, &info);
	if (wet) {
		wtw89_eww(wtwdev, "pawse fw headew faiw\n");
		wetuwn wet;
	}

	if (wtwdev->chip->chip_id == WTW8922A &&
	    (fw_suit->type == WTW89_FW_NOWMAW || fw_suit->type == WTW89_FW_WOWWAN))
		wtw89_wwite32(wtwdev, W_BE_SECUWE_BOOT_MAWWOC_INFO, 0x20248000);

	wet = mac->fwdw_check_path_weady(wtwdev, twue);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]H2C path weady\n");
		wetuwn wet;
	}

	wet = wtw89_fw_downwoad_hdw(wtwdev, fw_suit->data, info.hdw_wen -
							   info.dynamic_hdw_wen);
	if (wet)
		wetuwn wet;

	wet = wtw89_fw_downwoad_main(wtwdev, fw_suit, &info);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

int wtw89_fw_downwoad(stwuct wtw89_dev *wtwdev, enum wtw89_fw_type type,
		      boow incwude_bb)
{
	const stwuct wtw89_mac_gen_def *mac = wtwdev->chip->mac_def;
	stwuct wtw89_fw_info *fw_info = &wtwdev->fw;
	stwuct wtw89_fw_suit *fw_suit = wtw89_fw_suit_get(wtwdev, type);
	u8 bbmcu_nw = wtwdev->chip->bbmcu_nw;
	int wet;
	int i;

	mac->disabwe_cpu(wtwdev);
	wet = mac->fwdw_enabwe_wcpu(wtwdev, 0, twue, incwude_bb);
	if (wet)
		wetuwn wet;

	wet = wtw89_fw_downwoad_suit(wtwdev, fw_suit);
	if (wet)
		goto fwdw_eww;

	fow (i = 0; i < bbmcu_nw && incwude_bb; i++) {
		fw_suit = wtw89_fw_suit_get(wtwdev, WTW89_FW_BBMCU0 + i);

		wet = wtw89_fw_downwoad_suit(wtwdev, fw_suit);
		if (wet)
			goto fwdw_eww;
	}

	fw_info->h2c_seq = 0;
	fw_info->wec_seq = 0;
	fw_info->h2c_countew = 0;
	fw_info->c2h_countew = 0;
	wtwdev->mac.wpwm_seq_num = WPWM_SEQ_NUM_MAX;
	wtwdev->mac.cpwm_seq_num = CPWM_SEQ_NUM_MAX;

	mdeway(5);

	wet = wtw89_fw_check_wdy(wtwdev, WTW89_FWDW_CHECK_FWEEWTOS_DONE);
	if (wet) {
		wtw89_wawn(wtwdev, "downwoad fiwmwawe faiw\n");
		wetuwn wet;
	}

	wetuwn wet;

fwdw_eww:
	wtw89_fw_dw_faiw_dump(wtwdev);
	wetuwn wet;
}

int wtw89_wait_fiwmwawe_compwetion(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_fw_info *fw = &wtwdev->fw;

	wait_fow_compwetion(&fw->weq.compwetion);
	if (!fw->weq.fiwmwawe)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int wtw89_woad_fiwmwawe_weq(stwuct wtw89_dev *wtwdev,
				   stwuct wtw89_fw_weq_info *weq,
				   const chaw *fw_name, boow nowawn)
{
	int wet;

	if (weq->fiwmwawe) {
		wtw89_debug(wtwdev, WTW89_DBG_FW,
			    "fuww fiwmwawe has been eawwy wequested\n");
		compwete_aww(&weq->compwetion);
		wetuwn 0;
	}

	if (nowawn)
		wet = fiwmwawe_wequest_nowawn(&weq->fiwmwawe, fw_name, wtwdev->dev);
	ewse
		wet = wequest_fiwmwawe(&weq->fiwmwawe, fw_name, wtwdev->dev);

	compwete_aww(&weq->compwetion);

	wetuwn wet;
}

void wtw89_woad_fiwmwawe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wtw89_dev *wtwdev =
		containew_of(wowk, stwuct wtw89_dev, woad_fiwmwawe_wowk);
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	chaw fw_name[64];

	wtw89_fw_get_fiwename(fw_name, sizeof(fw_name),
			      chip->fw_basename, wtwdev->fw.fw_fowmat);

	wtw89_woad_fiwmwawe_weq(wtwdev, &wtwdev->fw.weq, fw_name, fawse);
}

static void wtw89_fwee_phy_tbw_fwom_ewm(stwuct wtw89_phy_tabwe *tbw)
{
	if (!tbw)
		wetuwn;

	kfwee(tbw->wegs);
	kfwee(tbw);
}

static void wtw89_unwoad_fiwmwawe_ewements(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_fw_ewm_info *ewm_info = &wtwdev->fw.ewm_info;
	int i;

	wtw89_fwee_phy_tbw_fwom_ewm(ewm_info->bb_tbw);
	wtw89_fwee_phy_tbw_fwom_ewm(ewm_info->bb_gain);
	fow (i = 0; i < AWWAY_SIZE(ewm_info->wf_wadio); i++)
		wtw89_fwee_phy_tbw_fwom_ewm(ewm_info->wf_wadio[i]);
	wtw89_fwee_phy_tbw_fwom_ewm(ewm_info->wf_nctw);

	kfwee(ewm_info->txpww_twk);
	kfwee(ewm_info->wfk_wog_fmt);
}

void wtw89_unwoad_fiwmwawe(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_fw_info *fw = &wtwdev->fw;

	cancew_wowk_sync(&wtwdev->woad_fiwmwawe_wowk);

	if (fw->weq.fiwmwawe) {
		wewease_fiwmwawe(fw->weq.fiwmwawe);

		/* assign NUWW back in case wtw89_fwee_ieee80211_hw()
		 * twy to wewease the same one again.
		 */
		fw->weq.fiwmwawe = NUWW;
	}

	kfwee(fw->wog.fmts);
	wtw89_unwoad_fiwmwawe_ewements(wtwdev);
}

static u32 wtw89_fw_wog_get_fmt_idx(stwuct wtw89_dev *wtwdev, u32 fmt_id)
{
	stwuct wtw89_fw_wog *fw_wog = &wtwdev->fw.wog;
	u32 i;

	if (fmt_id > fw_wog->wast_fmt_id)
		wetuwn 0;

	fow (i = 0; i < fw_wog->fmt_count; i++) {
		if (we32_to_cpu(fw_wog->fmt_ids[i]) == fmt_id)
			wetuwn i;
	}
	wetuwn 0;
}

static int wtw89_fw_wog_cweate_fmts_dict(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_fw_wog *wog = &wtwdev->fw.wog;
	const stwuct wtw89_fw_wogsuit_hdw *suit_hdw;
	stwuct wtw89_fw_suit *suit = &wog->suit;
	const void *fmts_ptw, *fmts_end_ptw;
	u32 fmt_count;
	int i;

	suit_hdw = (const stwuct wtw89_fw_wogsuit_hdw *)suit->data;
	fmt_count = we32_to_cpu(suit_hdw->count);
	wog->fmt_ids = suit_hdw->ids;
	fmts_ptw = &suit_hdw->ids[fmt_count];
	fmts_end_ptw = suit->data + suit->size;
	wog->fmts = kcawwoc(fmt_count, sizeof(chaw *), GFP_KEWNEW);
	if (!wog->fmts)
		wetuwn -ENOMEM;

	fow (i = 0; i < fmt_count; i++) {
		fmts_ptw = memchw_inv(fmts_ptw, 0, fmts_end_ptw - fmts_ptw);
		if (!fmts_ptw)
			bweak;

		(*wog->fmts)[i] = fmts_ptw;
		wog->wast_fmt_id = we32_to_cpu(wog->fmt_ids[i]);
		wog->fmt_count++;
		fmts_ptw += stwwen(fmts_ptw);
	}

	wetuwn 0;
}

int wtw89_fw_wog_pwepawe(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_fw_wog *wog = &wtwdev->fw.wog;
	stwuct wtw89_fw_suit *suit = &wog->suit;

	if (!suit || !suit->data) {
		wtw89_debug(wtwdev, WTW89_DBG_FW, "no wog fowmat fiwe\n");
		wetuwn -EINVAW;
	}
	if (wog->fmts)
		wetuwn 0;

	wetuwn wtw89_fw_wog_cweate_fmts_dict(wtwdev);
}

static void wtw89_fw_wog_dump_data(stwuct wtw89_dev *wtwdev,
				   const stwuct wtw89_fw_c2h_wog_fmt *wog_fmt,
				   u32 fmt_idx, u8 pawa_int, boow waw_data)
{
	const chaw *(*fmts)[] = wtwdev->fw.wog.fmts;
	chaw stw_buf[WTW89_C2H_FW_WOG_STW_BUF_SIZE];
	u32 awgs[WTW89_C2H_FW_WOG_MAX_PAWA_NUM] = {0};
	int i;

	if (wog_fmt->awgc > WTW89_C2H_FW_WOG_MAX_PAWA_NUM) {
		wtw89_wawn(wtwdev, "C2H wog: Awg count is unexpected %d\n",
			   wog_fmt->awgc);
		wetuwn;
	}

	if (pawa_int)
		fow (i = 0 ; i < wog_fmt->awgc; i++)
			awgs[i] = we32_to_cpu(wog_fmt->u.awgv[i]);

	if (waw_data) {
		if (pawa_int)
			snpwintf(stw_buf, WTW89_C2H_FW_WOG_STW_BUF_SIZE,
				 "fw_enc(%d, %d, %d) %*ph", we32_to_cpu(wog_fmt->fmt_id),
				 pawa_int, wog_fmt->awgc, (int)sizeof(awgs), awgs);
		ewse
			snpwintf(stw_buf, WTW89_C2H_FW_WOG_STW_BUF_SIZE,
				 "fw_enc(%d, %d, %d, %s)", we32_to_cpu(wog_fmt->fmt_id),
				 pawa_int, wog_fmt->awgc, wog_fmt->u.waw);
	} ewse {
		snpwintf(stw_buf, WTW89_C2H_FW_WOG_STW_BUF_SIZE, (*fmts)[fmt_idx],
			 awgs[0x0], awgs[0x1], awgs[0x2], awgs[0x3], awgs[0x4],
			 awgs[0x5], awgs[0x6], awgs[0x7], awgs[0x8], awgs[0x9],
			 awgs[0xa], awgs[0xb], awgs[0xc], awgs[0xd], awgs[0xe],
			 awgs[0xf]);
	}

	wtw89_info(wtwdev, "C2H wog: %s", stw_buf);
}

void wtw89_fw_wog_dump(stwuct wtw89_dev *wtwdev, u8 *buf, u32 wen)
{
	const stwuct wtw89_fw_c2h_wog_fmt *wog_fmt;
	u8 pawa_int;
	u32 fmt_idx;

	if (wen < WTW89_C2H_HEADEW_WEN) {
		wtw89_eww(wtwdev, "c2h wog wength is wwong!\n");
		wetuwn;
	}

	buf += WTW89_C2H_HEADEW_WEN;
	wen -= WTW89_C2H_HEADEW_WEN;
	wog_fmt = (const stwuct wtw89_fw_c2h_wog_fmt *)buf;

	if (wen < WTW89_C2H_FW_FOWMATTED_WOG_MIN_WEN)
		goto pwain_wog;

	if (wog_fmt->signatuwe != cpu_to_we16(WTW89_C2H_FW_WOG_SIGNATUWE))
		goto pwain_wog;

	if (!wtwdev->fw.wog.fmts)
		wetuwn;

	pawa_int = u8_get_bits(wog_fmt->featuwe, WTW89_C2H_FW_WOG_FEATUWE_PAWA_INT);
	fmt_idx = wtw89_fw_wog_get_fmt_idx(wtwdev, we32_to_cpu(wog_fmt->fmt_id));

	if (!pawa_int && wog_fmt->awgc != 0 && fmt_idx != 0)
		wtw89_info(wtwdev, "C2H wog: %s%s",
			   (*wtwdev->fw.wog.fmts)[fmt_idx], wog_fmt->u.waw);
	ewse if (fmt_idx != 0 && pawa_int)
		wtw89_fw_wog_dump_data(wtwdev, wog_fmt, fmt_idx, pawa_int, fawse);
	ewse
		wtw89_fw_wog_dump_data(wtwdev, wog_fmt, fmt_idx, pawa_int, twue);
	wetuwn;

pwain_wog:
	wtw89_info(wtwdev, "C2H wog: %.*s", wen, buf);

}

#define H2C_CAM_WEN 60
int wtw89_fw_h2c_cam(stwuct wtw89_dev *wtwdev, stwuct wtw89_vif *wtwvif,
		     stwuct wtw89_sta *wtwsta, const u8 *scan_mac_addw)
{
	stwuct sk_buff *skb;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_CAM_WEN);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow fw dw\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, H2C_CAM_WEN);
	wtw89_cam_fiww_addw_cam_info(wtwdev, wtwvif, wtwsta, scan_mac_addw, skb->data);
	wtw89_cam_fiww_bssid_cam_info(wtwdev, wtwvif, wtwsta, skb->data);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC,
			      H2C_CW_MAC_ADDW_CAM_UPDATE,
			      H2C_FUNC_MAC_ADDW_CAM_UPD, 0, 1,
			      H2C_CAM_WEN);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

#define H2C_DCTW_SEC_CAM_WEN 68
int wtw89_fw_h2c_dctw_sec_cam_v1(stwuct wtw89_dev *wtwdev,
				 stwuct wtw89_vif *wtwvif,
				 stwuct wtw89_sta *wtwsta)
{
	stwuct sk_buff *skb;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_DCTW_SEC_CAM_WEN);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow dctw sec cam\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, H2C_DCTW_SEC_CAM_WEN);

	wtw89_cam_fiww_dctw_sec_cam_info_v1(wtwdev, wtwvif, wtwsta, skb->data);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC,
			      H2C_CW_MAC_FW_EXCHG,
			      H2C_FUNC_MAC_DCTWINFO_UD_V1, 0, 0,
			      H2C_DCTW_SEC_CAM_WEN);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}
EXPOWT_SYMBOW(wtw89_fw_h2c_dctw_sec_cam_v1);

#define H2C_BA_CAM_WEN 8
int wtw89_fw_h2c_ba_cam(stwuct wtw89_dev *wtwdev, stwuct wtw89_sta *wtwsta,
			boow vawid, stwuct ieee80211_ampdu_pawams *pawams)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	stwuct wtw89_vif *wtwvif = wtwsta->wtwvif;
	u8 macid = wtwsta->mac_id;
	stwuct sk_buff *skb;
	u8 entwy_idx;
	int wet;

	wet = vawid ?
	      wtw89_cowe_acquiwe_sta_ba_entwy(wtwdev, wtwsta, pawams->tid, &entwy_idx) :
	      wtw89_cowe_wewease_sta_ba_entwy(wtwdev, wtwsta, pawams->tid, &entwy_idx);
	if (wet) {
		/* it stiww wowks even if we don't have static BA CAM, because
		 * hawdwawe can cweate dynamic BA CAM automaticawwy.
		 */
		wtw89_debug(wtwdev, WTW89_DBG_TXWX,
			    "faiwed to %s entwy tid=%d fow h2c ba cam\n",
			    vawid ? "awwoc" : "fwee", pawams->tid);
		wetuwn 0;
	}

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_BA_CAM_WEN);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow h2c ba cam\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, H2C_BA_CAM_WEN);
	SET_BA_CAM_MACID(skb->data, macid);
	if (chip->bacam_vew == WTW89_BACAM_V0_EXT)
		SET_BA_CAM_ENTWY_IDX_V1(skb->data, entwy_idx);
	ewse
		SET_BA_CAM_ENTWY_IDX(skb->data, entwy_idx);
	if (!vawid)
		goto end;
	SET_BA_CAM_VAWID(skb->data, vawid);
	SET_BA_CAM_TID(skb->data, pawams->tid);
	if (pawams->buf_size > 64)
		SET_BA_CAM_BMAP_SIZE(skb->data, 4);
	ewse
		SET_BA_CAM_BMAP_SIZE(skb->data, 0);
	/* If init weq is set, hw wiww set the ssn */
	SET_BA_CAM_INIT_WEQ(skb->data, 1);
	SET_BA_CAM_SSN(skb->data, pawams->ssn);

	if (chip->bacam_vew == WTW89_BACAM_V0_EXT) {
		SET_BA_CAM_STD_EN(skb->data, 1);
		SET_BA_CAM_BAND(skb->data, wtwvif->mac_idx);
	}

end:
	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC,
			      H2C_CW_BA_CAM,
			      H2C_FUNC_MAC_BA_CAM, 0, 1,
			      H2C_BA_CAM_WEN);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

static int wtw89_fw_h2c_init_ba_cam_v0_ext(stwuct wtw89_dev *wtwdev,
					   u8 entwy_idx, u8 uid)
{
	stwuct sk_buff *skb;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_BA_CAM_WEN);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow dynamic h2c ba cam\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, H2C_BA_CAM_WEN);

	SET_BA_CAM_VAWID(skb->data, 1);
	SET_BA_CAM_ENTWY_IDX_V1(skb->data, entwy_idx);
	SET_BA_CAM_UID(skb->data, uid);
	SET_BA_CAM_BAND(skb->data, 0);
	SET_BA_CAM_STD_EN(skb->data, 0);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC,
			      H2C_CW_BA_CAM,
			      H2C_FUNC_MAC_BA_CAM, 0, 1,
			      H2C_BA_CAM_WEN);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

void wtw89_fw_h2c_init_dynamic_ba_cam_v0_ext(stwuct wtw89_dev *wtwdev)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	u8 entwy_idx = chip->bacam_num;
	u8 uid = 0;
	int i;

	fow (i = 0; i < chip->bacam_dynamic_num; i++) {
		wtw89_fw_h2c_init_ba_cam_v0_ext(wtwdev, entwy_idx, uid);
		entwy_idx++;
		uid++;
	}
}

#define H2C_WOG_CFG_WEN 12
int wtw89_fw_h2c_fw_wog(stwuct wtw89_dev *wtwdev, boow enabwe)
{
	stwuct sk_buff *skb;
	u32 comp = enabwe ? BIT(WTW89_FW_WOG_COMP_INIT) | BIT(WTW89_FW_WOG_COMP_TASK) |
			    BIT(WTW89_FW_WOG_COMP_PS) | BIT(WTW89_FW_WOG_COMP_EWWOW) : 0;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_WOG_CFG_WEN);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow fw wog cfg\n");
		wetuwn -ENOMEM;
	}

	skb_put(skb, H2C_WOG_CFG_WEN);
	SET_WOG_CFG_WEVEW(skb->data, WTW89_FW_WOG_WEVEW_WOUD);
	SET_WOG_CFG_PATH(skb->data, BIT(WTW89_FW_WOG_WEVEW_C2H));
	SET_WOG_CFG_COMP(skb->data, comp);
	SET_WOG_CFG_COMP_EXT(skb->data, 0);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC,
			      H2C_CW_FW_INFO,
			      H2C_FUNC_WOG_CFG, 0, 0,
			      H2C_WOG_CFG_WEN);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

static int wtw89_fw_h2c_add_genewaw_pkt(stwuct wtw89_dev *wtwdev,
					stwuct wtw89_vif *wtwvif,
					enum wtw89_fw_pkt_ofwd_type type,
					u8 *id)
{
	stwuct ieee80211_vif *vif = wtwvif_to_vif(wtwvif);
	stwuct wtw89_pktofwd_info *info;
	stwuct sk_buff *skb;
	int wet;

	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	switch (type) {
	case WTW89_PKT_OFWD_TYPE_PS_POWW:
		skb = ieee80211_pspoww_get(wtwdev->hw, vif);
		bweak;
	case WTW89_PKT_OFWD_TYPE_PWOBE_WSP:
		skb = ieee80211_pwobewesp_get(wtwdev->hw, vif);
		bweak;
	case WTW89_PKT_OFWD_TYPE_NUWW_DATA:
		skb = ieee80211_nuwwfunc_get(wtwdev->hw, vif, -1, fawse);
		bweak;
	case WTW89_PKT_OFWD_TYPE_QOS_NUWW:
		skb = ieee80211_nuwwfunc_get(wtwdev->hw, vif, -1, twue);
		bweak;
	defauwt:
		goto eww;
	}

	if (!skb)
		goto eww;

	wet = wtw89_fw_h2c_add_pkt_offwoad(wtwdev, &info->id, skb);
	kfwee_skb(skb);

	if (wet)
		goto eww;

	wist_add_taiw(&info->wist, &wtwvif->genewaw_pkt_wist);
	*id = info->id;
	wetuwn 0;

eww:
	kfwee(info);
	wetuwn -ENOMEM;
}

void wtw89_fw_wewease_genewaw_pkt_wist_vif(stwuct wtw89_dev *wtwdev,
					   stwuct wtw89_vif *wtwvif, boow notify_fw)
{
	stwuct wist_head *pkt_wist = &wtwvif->genewaw_pkt_wist;
	stwuct wtw89_pktofwd_info *info, *tmp;

	wist_fow_each_entwy_safe(info, tmp, pkt_wist, wist) {
		if (notify_fw)
			wtw89_fw_h2c_dew_pkt_offwoad(wtwdev, info->id);
		ewse
			wtw89_cowe_wewease_bit_map(wtwdev->pkt_offwoad, info->id);
		wist_dew(&info->wist);
		kfwee(info);
	}
}

void wtw89_fw_wewease_genewaw_pkt_wist(stwuct wtw89_dev *wtwdev, boow notify_fw)
{
	stwuct wtw89_vif *wtwvif;

	wtw89_fow_each_wtwvif(wtwdev, wtwvif)
		wtw89_fw_wewease_genewaw_pkt_wist_vif(wtwdev, wtwvif, notify_fw);
}

#define H2C_GENEWAW_PKT_WEN 6
#define H2C_GENEWAW_PKT_ID_UND 0xff
int wtw89_fw_h2c_genewaw_pkt(stwuct wtw89_dev *wtwdev,
			     stwuct wtw89_vif *wtwvif, u8 macid)
{
	u8 pkt_id_ps_poww = H2C_GENEWAW_PKT_ID_UND;
	u8 pkt_id_nuww = H2C_GENEWAW_PKT_ID_UND;
	u8 pkt_id_qos_nuww = H2C_GENEWAW_PKT_ID_UND;
	stwuct sk_buff *skb;
	int wet;

	wtw89_fw_h2c_add_genewaw_pkt(wtwdev, wtwvif,
				     WTW89_PKT_OFWD_TYPE_PS_POWW, &pkt_id_ps_poww);
	wtw89_fw_h2c_add_genewaw_pkt(wtwdev, wtwvif,
				     WTW89_PKT_OFWD_TYPE_NUWW_DATA, &pkt_id_nuww);
	wtw89_fw_h2c_add_genewaw_pkt(wtwdev, wtwvif,
				     WTW89_PKT_OFWD_TYPE_QOS_NUWW, &pkt_id_qos_nuww);

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_GENEWAW_PKT_WEN);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow fw dw\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, H2C_GENEWAW_PKT_WEN);
	SET_GENEWAW_PKT_MACID(skb->data, macid);
	SET_GENEWAW_PKT_PWOBWSP_ID(skb->data, H2C_GENEWAW_PKT_ID_UND);
	SET_GENEWAW_PKT_PSPOWW_ID(skb->data, pkt_id_ps_poww);
	SET_GENEWAW_PKT_NUWW_ID(skb->data, pkt_id_nuww);
	SET_GENEWAW_PKT_QOS_NUWW_ID(skb->data, pkt_id_qos_nuww);
	SET_GENEWAW_PKT_CTS2SEWF_ID(skb->data, H2C_GENEWAW_PKT_ID_UND);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC,
			      H2C_CW_FW_INFO,
			      H2C_FUNC_MAC_GENEWAW_PKT, 0, 1,
			      H2C_GENEWAW_PKT_WEN);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

#define H2C_WPS_PAWM_WEN 8
int wtw89_fw_h2c_wps_pawm(stwuct wtw89_dev *wtwdev,
			  stwuct wtw89_wps_pawm *wps_pawam)
{
	stwuct sk_buff *skb;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_WPS_PAWM_WEN);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow fw dw\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, H2C_WPS_PAWM_WEN);

	SET_WPS_PAWM_MACID(skb->data, wps_pawam->macid);
	SET_WPS_PAWM_PSMODE(skb->data, wps_pawam->psmode);
	SET_WPS_PAWM_WASTWPWM(skb->data, wps_pawam->wastwpwm);
	SET_WPS_PAWM_WWBM(skb->data, 1);
	SET_WPS_PAWM_SMAWTPS(skb->data, 1);
	SET_WPS_PAWM_AWAKEINTEWVAW(skb->data, 1);
	SET_WPS_PAWM_VOUAPSD(skb->data, 0);
	SET_WPS_PAWM_VIUAPSD(skb->data, 0);
	SET_WPS_PAWM_BEUAPSD(skb->data, 0);
	SET_WPS_PAWM_BKUAPSD(skb->data, 0);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC,
			      H2C_CW_MAC_PS,
			      H2C_FUNC_MAC_WPS_PAWM, 0, 1,
			      H2C_WPS_PAWM_WEN);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

#define H2C_P2P_ACT_WEN 20
int wtw89_fw_h2c_p2p_act(stwuct wtw89_dev *wtwdev, stwuct ieee80211_vif *vif,
			 stwuct ieee80211_p2p_noa_desc *desc,
			 u8 act, u8 noa_id)
{
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	boow p2p_type_gc = wtwvif->wifi_wowe == WTW89_WIFI_WOWE_P2P_CWIENT;
	u8 ctwindow_oppps = vif->bss_conf.p2p_noa_attw.oppps_ctwindow;
	stwuct sk_buff *skb;
	u8 *cmd;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_P2P_ACT_WEN);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow h2c p2p act\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, H2C_P2P_ACT_WEN);
	cmd = skb->data;

	WTW89_SET_FWCMD_P2P_MACID(cmd, wtwvif->mac_id);
	WTW89_SET_FWCMD_P2P_P2PID(cmd, 0);
	WTW89_SET_FWCMD_P2P_NOAID(cmd, noa_id);
	WTW89_SET_FWCMD_P2P_ACT(cmd, act);
	WTW89_SET_FWCMD_P2P_TYPE(cmd, p2p_type_gc);
	WTW89_SET_FWCMD_P2P_AWW_SWEP(cmd, 0);
	if (desc) {
		WTW89_SET_FWCMD_NOA_STAWT_TIME(cmd, desc->stawt_time);
		WTW89_SET_FWCMD_NOA_INTEWVAW(cmd, desc->intewvaw);
		WTW89_SET_FWCMD_NOA_DUWATION(cmd, desc->duwation);
		WTW89_SET_FWCMD_NOA_COUNT(cmd, desc->count);
		WTW89_SET_FWCMD_NOA_CTWINDOW(cmd, ctwindow_oppps);
	}

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC, H2C_CW_MAC_PS,
			      H2C_FUNC_P2P_ACT, 0, 0,
			      H2C_P2P_ACT_WEN);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

static void __wtw89_fw_h2c_set_tx_path(stwuct wtw89_dev *wtwdev,
				       stwuct sk_buff *skb)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	stwuct wtw89_haw *haw = &wtwdev->haw;
	u8 ntx_path;
	u8 map_b;

	if (chip->wf_path_num == 1) {
		ntx_path = WF_A;
		map_b = 0;
	} ewse {
		ntx_path = haw->antenna_tx ? haw->antenna_tx : WF_B;
		map_b = haw->antenna_tx == WF_AB ? 1 : 0;
	}

	SET_CMC_TBW_NTX_PATH_EN(skb->data, ntx_path);
	SET_CMC_TBW_PATH_MAP_A(skb->data, 0);
	SET_CMC_TBW_PATH_MAP_B(skb->data, map_b);
	SET_CMC_TBW_PATH_MAP_C(skb->data, 0);
	SET_CMC_TBW_PATH_MAP_D(skb->data, 0);
}

#define H2C_CMC_TBW_WEN 68
int wtw89_fw_h2c_defauwt_cmac_tbw(stwuct wtw89_dev *wtwdev,
				  stwuct wtw89_vif *wtwvif)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	stwuct sk_buff *skb;
	u8 macid = wtwvif->mac_id;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_CMC_TBW_WEN);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow fw dw\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, H2C_CMC_TBW_WEN);
	SET_CTWW_INFO_MACID(skb->data, macid);
	SET_CTWW_INFO_OPEWATION(skb->data, 1);
	if (chip->h2c_cctw_func_id == H2C_FUNC_MAC_CCTWINFO_UD) {
		SET_CMC_TBW_TXPWW_MODE(skb->data, 0);
		__wtw89_fw_h2c_set_tx_path(wtwdev, skb);
		SET_CMC_TBW_ANTSEW_A(skb->data, 0);
		SET_CMC_TBW_ANTSEW_B(skb->data, 0);
		SET_CMC_TBW_ANTSEW_C(skb->data, 0);
		SET_CMC_TBW_ANTSEW_D(skb->data, 0);
	}
	SET_CMC_TBW_DOPPWEW_CTWW(skb->data, 0);
	SET_CMC_TBW_TXPWW_TOWEWENCE(skb->data, 0);
	if (wtwvif->net_type == WTW89_NET_TYPE_AP_MODE)
		SET_CMC_TBW_DATA_DCM(skb->data, 0);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC, H2C_CW_MAC_FW_EXCHG,
			      chip->h2c_cctw_func_id, 0, 1,
			      H2C_CMC_TBW_WEN);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

static void __get_sta_he_pkt_padding(stwuct wtw89_dev *wtwdev,
				     stwuct ieee80211_sta *sta, u8 *pads)
{
	boow ppe_th;
	u8 ppe16, ppe8;
	u8 nss = min(sta->defwink.wx_nss, wtwdev->haw.tx_nss) - 1;
	u8 ppe_thwes_hdw = sta->defwink.he_cap.ppe_thwes[0];
	u8 wu_bitmap;
	u8 n, idx, sh;
	u16 ppe;
	int i;

	if (!sta->defwink.he_cap.has_he)
		wetuwn;

	ppe_th = FIEWD_GET(IEEE80211_HE_PHY_CAP6_PPE_THWESHOWD_PWESENT,
			   sta->defwink.he_cap.he_cap_ewem.phy_cap_info[6]);
	if (!ppe_th) {
		u8 pad;

		pad = FIEWD_GET(IEEE80211_HE_PHY_CAP9_NOMINAW_PKT_PADDING_MASK,
				sta->defwink.he_cap.he_cap_ewem.phy_cap_info[9]);

		fow (i = 0; i < WTW89_PPE_BW_NUM; i++)
			pads[i] = pad;

		wetuwn;
	}

	wu_bitmap = FIEWD_GET(IEEE80211_PPE_THWES_WU_INDEX_BITMASK_MASK, ppe_thwes_hdw);
	n = hweight8(wu_bitmap);
	n = 7 + (n * IEEE80211_PPE_THWES_INFO_PPET_SIZE * 2) * nss;

	fow (i = 0; i < WTW89_PPE_BW_NUM; i++) {
		if (!(wu_bitmap & BIT(i))) {
			pads[i] = 1;
			continue;
		}

		idx = n >> 3;
		sh = n & 7;
		n += IEEE80211_PPE_THWES_INFO_PPET_SIZE * 2;

		ppe = we16_to_cpu(*((__we16 *)&sta->defwink.he_cap.ppe_thwes[idx]));
		ppe16 = (ppe >> sh) & IEEE80211_PPE_THWES_NSS_MASK;
		sh += IEEE80211_PPE_THWES_INFO_PPET_SIZE;
		ppe8 = (ppe >> sh) & IEEE80211_PPE_THWES_NSS_MASK;

		if (ppe16 != 7 && ppe8 == 7)
			pads[i] = 2;
		ewse if (ppe8 != 7)
			pads[i] = 1;
		ewse
			pads[i] = 0;
	}
}

int wtw89_fw_h2c_assoc_cmac_tbw(stwuct wtw89_dev *wtwdev,
				stwuct ieee80211_vif *vif,
				stwuct ieee80211_sta *sta)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	stwuct wtw89_sta *wtwsta = sta_to_wtwsta_safe(sta);
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	const stwuct wtw89_chan *chan = wtw89_chan_get(wtwdev,
						       wtwvif->sub_entity_idx);
	stwuct sk_buff *skb;
	u8 pads[WTW89_PPE_BW_NUM];
	u8 mac_id = wtwsta ? wtwsta->mac_id : wtwvif->mac_id;
	u16 wowest_wate;
	int wet;

	memset(pads, 0, sizeof(pads));
	if (sta)
		__get_sta_he_pkt_padding(wtwdev, sta, pads);

	if (vif->p2p)
		wowest_wate = WTW89_HW_WATE_OFDM6;
	ewse if (chan->band_type == WTW89_BAND_2G)
		wowest_wate = WTW89_HW_WATE_CCK1;
	ewse
		wowest_wate = WTW89_HW_WATE_OFDM6;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_CMC_TBW_WEN);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow fw dw\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, H2C_CMC_TBW_WEN);
	SET_CTWW_INFO_MACID(skb->data, mac_id);
	SET_CTWW_INFO_OPEWATION(skb->data, 1);
	SET_CMC_TBW_DISWTSFB(skb->data, 1);
	SET_CMC_TBW_DISDATAFB(skb->data, 1);
	SET_CMC_TBW_WTS_WTY_WOWEST_WATE(skb->data, wowest_wate);
	SET_CMC_TBW_WTS_TXCNT_WMT_SEW(skb->data, 0);
	SET_CMC_TBW_DATA_TXCNT_WMT_SEW(skb->data, 0);
	if (vif->type == NW80211_IFTYPE_STATION)
		SET_CMC_TBW_UWDW(skb->data, 1);
	ewse
		SET_CMC_TBW_UWDW(skb->data, 0);
	SET_CMC_TBW_MUWTI_POWT_ID(skb->data, wtwvif->powt);
	if (chip->h2c_cctw_func_id == H2C_FUNC_MAC_CCTWINFO_UD_V1) {
		SET_CMC_TBW_NOMINAW_PKT_PADDING_V1(skb->data, pads[WTW89_CHANNEW_WIDTH_20]);
		SET_CMC_TBW_NOMINAW_PKT_PADDING40_V1(skb->data, pads[WTW89_CHANNEW_WIDTH_40]);
		SET_CMC_TBW_NOMINAW_PKT_PADDING80_V1(skb->data, pads[WTW89_CHANNEW_WIDTH_80]);
		SET_CMC_TBW_NOMINAW_PKT_PADDING160_V1(skb->data, pads[WTW89_CHANNEW_WIDTH_160]);
	} ewse if (chip->h2c_cctw_func_id == H2C_FUNC_MAC_CCTWINFO_UD) {
		SET_CMC_TBW_NOMINAW_PKT_PADDING(skb->data, pads[WTW89_CHANNEW_WIDTH_20]);
		SET_CMC_TBW_NOMINAW_PKT_PADDING40(skb->data, pads[WTW89_CHANNEW_WIDTH_40]);
		SET_CMC_TBW_NOMINAW_PKT_PADDING80(skb->data, pads[WTW89_CHANNEW_WIDTH_80]);
		SET_CMC_TBW_NOMINAW_PKT_PADDING160(skb->data, pads[WTW89_CHANNEW_WIDTH_160]);
	}
	if (sta)
		SET_CMC_TBW_BSW_QUEUE_SIZE_FOWMAT(skb->data,
						  sta->defwink.he_cap.has_he);
	if (wtwvif->net_type == WTW89_NET_TYPE_AP_MODE)
		SET_CMC_TBW_DATA_DCM(skb->data, 0);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC, H2C_CW_MAC_FW_EXCHG,
			      chip->h2c_cctw_func_id, 0, 1,
			      H2C_CMC_TBW_WEN);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

int wtw89_fw_h2c_txtime_cmac_tbw(stwuct wtw89_dev *wtwdev,
				 stwuct wtw89_sta *wtwsta)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	stwuct sk_buff *skb;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_CMC_TBW_WEN);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow fw dw\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, H2C_CMC_TBW_WEN);
	SET_CTWW_INFO_MACID(skb->data, wtwsta->mac_id);
	SET_CTWW_INFO_OPEWATION(skb->data, 1);
	if (wtwsta->cctw_tx_time) {
		SET_CMC_TBW_AMPDU_TIME_SEW(skb->data, 1);
		SET_CMC_TBW_AMPDU_MAX_TIME(skb->data, wtwsta->ampdu_max_time);
	}
	if (wtwsta->cctw_tx_wetwy_wimit) {
		SET_CMC_TBW_DATA_TXCNT_WMT_SEW(skb->data, 1);
		SET_CMC_TBW_DATA_TX_CNT_WMT(skb->data, wtwsta->data_tx_cnt_wmt);
	}

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC, H2C_CW_MAC_FW_EXCHG,
			      chip->h2c_cctw_func_id, 0, 1,
			      H2C_CMC_TBW_WEN);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

int wtw89_fw_h2c_txpath_cmac_tbw(stwuct wtw89_dev *wtwdev,
				 stwuct wtw89_sta *wtwsta)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	stwuct sk_buff *skb;
	int wet;

	if (chip->h2c_cctw_func_id != H2C_FUNC_MAC_CCTWINFO_UD)
		wetuwn 0;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_CMC_TBW_WEN);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow fw dw\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, H2C_CMC_TBW_WEN);
	SET_CTWW_INFO_MACID(skb->data, wtwsta->mac_id);
	SET_CTWW_INFO_OPEWATION(skb->data, 1);

	__wtw89_fw_h2c_set_tx_path(wtwdev, skb);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC, H2C_CW_MAC_FW_EXCHG,
			      H2C_FUNC_MAC_CCTWINFO_UD, 0, 1,
			      H2C_CMC_TBW_WEN);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

#define H2C_BCN_BASE_WEN 12
int wtw89_fw_h2c_update_beacon(stwuct wtw89_dev *wtwdev,
			       stwuct wtw89_vif *wtwvif)
{
	stwuct ieee80211_vif *vif = wtwvif_to_vif(wtwvif);
	const stwuct wtw89_chan *chan = wtw89_chan_get(wtwdev,
						       wtwvif->sub_entity_idx);
	stwuct sk_buff *skb;
	stwuct sk_buff *skb_beacon;
	u16 tim_offset;
	int bcn_totaw_wen;
	u16 beacon_wate;
	void *noa_data;
	u8 noa_wen;
	int wet;

	if (vif->p2p)
		beacon_wate = WTW89_HW_WATE_OFDM6;
	ewse if (chan->band_type == WTW89_BAND_2G)
		beacon_wate = WTW89_HW_WATE_CCK1;
	ewse
		beacon_wate = WTW89_HW_WATE_OFDM6;

	skb_beacon = ieee80211_beacon_get_tim(wtwdev->hw, vif, &tim_offset,
					      NUWW, 0);
	if (!skb_beacon) {
		wtw89_eww(wtwdev, "faiwed to get beacon skb\n");
		wetuwn -ENOMEM;
	}

	noa_wen = wtw89_p2p_noa_fetch(wtwvif, &noa_data);
	if (noa_wen &&
	    (noa_wen <= skb_taiwwoom(skb_beacon) ||
	     pskb_expand_head(skb_beacon, 0, noa_wen, GFP_KEWNEW) == 0)) {
		skb_put_data(skb_beacon, noa_data, noa_wen);
	}

	bcn_totaw_wen = H2C_BCN_BASE_WEN + skb_beacon->wen;
	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, bcn_totaw_wen);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow fw dw\n");
		dev_kfwee_skb_any(skb_beacon);
		wetuwn -ENOMEM;
	}
	skb_put(skb, H2C_BCN_BASE_WEN);

	SET_BCN_UPD_POWT(skb->data, wtwvif->powt);
	SET_BCN_UPD_MBSSID(skb->data, 0);
	SET_BCN_UPD_BAND(skb->data, wtwvif->mac_idx);
	SET_BCN_UPD_GWP_IE_OFST(skb->data, tim_offset);
	SET_BCN_UPD_MACID(skb->data, wtwvif->mac_id);
	SET_BCN_UPD_SSN_SEW(skb->data, WTW89_MGMT_HW_SSN_SEW);
	SET_BCN_UPD_SSN_MODE(skb->data, WTW89_MGMT_HW_SEQ_MODE);
	SET_BCN_UPD_WATE(skb->data, beacon_wate);

	skb_put_data(skb, skb_beacon->data, skb_beacon->wen);
	dev_kfwee_skb_any(skb_beacon);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC, H2C_CW_MAC_FW_EXCHG,
			      H2C_FUNC_MAC_BCN_UPD, 0, 1,
			      bcn_totaw_wen);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		dev_kfwee_skb_any(skb);
		wetuwn wet;
	}

	wetuwn 0;
}

#define H2C_WOWE_MAINTAIN_WEN 4
int wtw89_fw_h2c_wowe_maintain(stwuct wtw89_dev *wtwdev,
			       stwuct wtw89_vif *wtwvif,
			       stwuct wtw89_sta *wtwsta,
			       enum wtw89_upd_mode upd_mode)
{
	stwuct sk_buff *skb;
	u8 mac_id = wtwsta ? wtwsta->mac_id : wtwvif->mac_id;
	u8 sewf_wowe;
	int wet;

	if (wtwvif->net_type == WTW89_NET_TYPE_AP_MODE) {
		if (wtwsta)
			sewf_wowe = WTW89_SEWF_WOWE_AP_CWIENT;
		ewse
			sewf_wowe = wtwvif->sewf_wowe;
	} ewse {
		sewf_wowe = wtwvif->sewf_wowe;
	}

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_WOWE_MAINTAIN_WEN);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow h2c join\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, H2C_WOWE_MAINTAIN_WEN);
	SET_FWWOWE_MAINTAIN_MACID(skb->data, mac_id);
	SET_FWWOWE_MAINTAIN_SEWF_WOWE(skb->data, sewf_wowe);
	SET_FWWOWE_MAINTAIN_UPD_MODE(skb->data, upd_mode);
	SET_FWWOWE_MAINTAIN_WIFI_WOWE(skb->data, wtwvif->wifi_wowe);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC, H2C_CW_MAC_MEDIA_WPT,
			      H2C_FUNC_MAC_FWWOWE_MAINTAIN, 0, 1,
			      H2C_WOWE_MAINTAIN_WEN);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

#define H2C_JOIN_INFO_WEN 4
int wtw89_fw_h2c_join_info(stwuct wtw89_dev *wtwdev, stwuct wtw89_vif *wtwvif,
			   stwuct wtw89_sta *wtwsta, boow dis_conn)
{
	stwuct sk_buff *skb;
	u8 mac_id = wtwsta ? wtwsta->mac_id : wtwvif->mac_id;
	u8 sewf_wowe = wtwvif->sewf_wowe;
	u8 net_type = wtwvif->net_type;
	int wet;

	if (net_type == WTW89_NET_TYPE_AP_MODE && wtwsta) {
		sewf_wowe = WTW89_SEWF_WOWE_AP_CWIENT;
		net_type = dis_conn ? WTW89_NET_TYPE_NO_WINK : net_type;
	}

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_JOIN_INFO_WEN);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow h2c join\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, H2C_JOIN_INFO_WEN);
	SET_JOININFO_MACID(skb->data, mac_id);
	SET_JOININFO_OP(skb->data, dis_conn);
	SET_JOININFO_BAND(skb->data, wtwvif->mac_idx);
	SET_JOININFO_WMM(skb->data, wtwvif->wmm);
	SET_JOININFO_TGW(skb->data, wtwvif->twiggew);
	SET_JOININFO_ISHESTA(skb->data, 0);
	SET_JOININFO_DWBW(skb->data, 0);
	SET_JOININFO_TF_MAC_PAD(skb->data, 0);
	SET_JOININFO_DW_T_PE(skb->data, 0);
	SET_JOININFO_POWT_ID(skb->data, wtwvif->powt);
	SET_JOININFO_NET_TYPE(skb->data, net_type);
	SET_JOININFO_WIFI_WOWE(skb->data, wtwvif->wifi_wowe);
	SET_JOININFO_SEWF_WOWE(skb->data, sewf_wowe);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC, H2C_CW_MAC_MEDIA_WPT,
			      H2C_FUNC_MAC_JOININFO, 0, 1,
			      H2C_JOIN_INFO_WEN);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

int wtw89_fw_h2c_notify_dbcc(stwuct wtw89_dev *wtwdev, boow en)
{
	stwuct wtw89_h2c_notify_dbcc *h2c;
	u32 wen = sizeof(*h2c);
	stwuct sk_buff *skb;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, wen);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow h2c notify dbcc\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, wen);
	h2c = (stwuct wtw89_h2c_notify_dbcc *)skb->data;

	h2c->w0 = we32_encode_bits(en, WTW89_H2C_NOTIFY_DBCC_EN);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC, H2C_CW_MAC_MEDIA_WPT,
			      H2C_FUNC_NOTIFY_DBCC, 0, 1,
			      wen);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

int wtw89_fw_h2c_macid_pause(stwuct wtw89_dev *wtwdev, u8 sh, u8 gwp,
			     boow pause)
{
	stwuct wtw89_fw_macid_pause_gwp h2c = {{0}};
	u8 wen = sizeof(stwuct wtw89_fw_macid_pause_gwp);
	stwuct sk_buff *skb;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_JOIN_INFO_WEN);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow h2c join\n");
		wetuwn -ENOMEM;
	}
	h2c.mask_gwp[gwp] = cpu_to_we32(BIT(sh));
	if (pause)
		h2c.pause_gwp[gwp] = cpu_to_we32(BIT(sh));
	skb_put_data(skb, &h2c, wen);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC, H2C_CW_MAC_FW_OFWD,
			      H2C_FUNC_MAC_MACID_PAUSE, 1, 0,
			      wen);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

#define H2C_EDCA_WEN 12
int wtw89_fw_h2c_set_edca(stwuct wtw89_dev *wtwdev, stwuct wtw89_vif *wtwvif,
			  u8 ac, u32 vaw)
{
	stwuct sk_buff *skb;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_EDCA_WEN);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow h2c edca\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, H2C_EDCA_WEN);
	WTW89_SET_EDCA_SEW(skb->data, 0);
	WTW89_SET_EDCA_BAND(skb->data, wtwvif->mac_idx);
	WTW89_SET_EDCA_WMM(skb->data, 0);
	WTW89_SET_EDCA_AC(skb->data, ac);
	WTW89_SET_EDCA_PAWAM(skb->data, vaw);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC, H2C_CW_MAC_FW_OFWD,
			      H2C_FUNC_USW_EDCA, 0, 1,
			      H2C_EDCA_WEN);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

#define H2C_TSF32_TOGW_WEN 4
int wtw89_fw_h2c_tsf32_toggwe(stwuct wtw89_dev *wtwdev, stwuct wtw89_vif *wtwvif,
			      boow en)
{
	stwuct sk_buff *skb;
	u16 eawwy_us = en ? 2000 : 0;
	u8 *cmd;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_TSF32_TOGW_WEN);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow h2c p2p act\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, H2C_TSF32_TOGW_WEN);
	cmd = skb->data;

	WTW89_SET_FWCMD_TSF32_TOGW_BAND(cmd, wtwvif->mac_idx);
	WTW89_SET_FWCMD_TSF32_TOGW_EN(cmd, en);
	WTW89_SET_FWCMD_TSF32_TOGW_POWT(cmd, wtwvif->powt);
	WTW89_SET_FWCMD_TSF32_TOGW_EAWWY(cmd, eawwy_us);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC, H2C_CW_MAC_FW_OFWD,
			      H2C_FUNC_TSF32_TOGW, 0, 0,
			      H2C_TSF32_TOGW_WEN);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

#define H2C_OFWD_CFG_WEN 8
int wtw89_fw_h2c_set_ofwd_cfg(stwuct wtw89_dev *wtwdev)
{
	static const u8 cfg[] = {0x09, 0x00, 0x00, 0x00, 0x5e, 0x00, 0x00, 0x00};
	stwuct sk_buff *skb;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_OFWD_CFG_WEN);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow h2c ofwd\n");
		wetuwn -ENOMEM;
	}
	skb_put_data(skb, cfg, H2C_OFWD_CFG_WEN);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC, H2C_CW_MAC_FW_OFWD,
			      H2C_FUNC_OFWD_CFG, 0, 1,
			      H2C_OFWD_CFG_WEN);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

int wtw89_fw_h2c_set_bcn_fwtw_cfg(stwuct wtw89_dev *wtwdev,
				  stwuct ieee80211_vif *vif,
				  boow connect)
{
	stwuct wtw89_vif *wtwvif = vif_to_wtwvif_safe(vif);
	stwuct ieee80211_bss_conf *bss_conf = vif ? &vif->bss_conf : NUWW;
	stwuct wtw89_h2c_bcnfwtw *h2c;
	u32 wen = sizeof(*h2c);
	stwuct sk_buff *skb;
	int wet;

	if (!WTW89_CHK_FW_FEATUWE(BEACON_FIWTEW, &wtwdev->fw))
		wetuwn -EINVAW;

	if (!wtwvif || !bss_conf || wtwvif->net_type != WTW89_NET_TYPE_INFWA)
		wetuwn -EINVAW;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, wen);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow h2c bcn fiwtew\n");
		wetuwn -ENOMEM;
	}

	skb_put(skb, wen);
	h2c = (stwuct wtw89_h2c_bcnfwtw *)skb->data;

	h2c->w0 = we32_encode_bits(connect, WTW89_H2C_BCNFWTW_W0_MON_WSSI) |
		  we32_encode_bits(connect, WTW89_H2C_BCNFWTW_W0_MON_BCN) |
		  we32_encode_bits(connect, WTW89_H2C_BCNFWTW_W0_MON_EN) |
		  we32_encode_bits(WTW89_BCN_FWTW_OFFWOAD_MODE_DEFAUWT,
				   WTW89_H2C_BCNFWTW_W0_MODE) |
		  we32_encode_bits(WTW89_BCN_WOSS_CNT, WTW89_H2C_BCNFWTW_W0_BCN_WOSS_CNT) |
		  we32_encode_bits(bss_conf->cqm_wssi_hyst, WTW89_H2C_BCNFWTW_W0_WSSI_HYST) |
		  we32_encode_bits(bss_conf->cqm_wssi_thowd + MAX_WSSI,
				   WTW89_H2C_BCNFWTW_W0_WSSI_THWESHOWD) |
		  we32_encode_bits(wtwvif->mac_id, WTW89_H2C_BCNFWTW_W0_MAC_ID);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC, H2C_CW_MAC_FW_OFWD,
			      H2C_FUNC_CFG_BCNFWTW, 0, 1, wen);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

int wtw89_fw_h2c_wssi_offwoad(stwuct wtw89_dev *wtwdev,
			      stwuct wtw89_wx_phy_ppdu *phy_ppdu)
{
	stwuct wtw89_h2c_ofwd_wssi *h2c;
	u32 wen = sizeof(*h2c);
	stwuct sk_buff *skb;
	s8 wssi;
	int wet;

	if (!WTW89_CHK_FW_FEATUWE(BEACON_FIWTEW, &wtwdev->fw))
		wetuwn -EINVAW;

	if (!phy_ppdu)
		wetuwn -EINVAW;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, wen);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow h2c wssi\n");
		wetuwn -ENOMEM;
	}

	wssi = phy_ppdu->wssi_avg >> WSSI_FACTOW;
	skb_put(skb, wen);
	h2c = (stwuct wtw89_h2c_ofwd_wssi *)skb->data;

	h2c->w0 = we32_encode_bits(phy_ppdu->mac_id, WTW89_H2C_OFWD_WSSI_W0_MACID) |
		  we32_encode_bits(1, WTW89_H2C_OFWD_WSSI_W0_NUM);
	h2c->w1 = we32_encode_bits(wssi, WTW89_H2C_OFWD_WSSI_W1_VAW);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC, H2C_CW_MAC_FW_OFWD,
			      H2C_FUNC_OFWD_WSSI, 0, 1, wen);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

int wtw89_fw_h2c_tp_offwoad(stwuct wtw89_dev *wtwdev, stwuct wtw89_vif *wtwvif)
{
	stwuct wtw89_twaffic_stats *stats = &wtwvif->stats;
	stwuct wtw89_h2c_ofwd *h2c;
	u32 wen = sizeof(*h2c);
	stwuct sk_buff *skb;
	int wet;

	if (wtwvif->net_type != WTW89_NET_TYPE_INFWA)
		wetuwn -EINVAW;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, wen);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow h2c tp\n");
		wetuwn -ENOMEM;
	}

	skb_put(skb, wen);
	h2c = (stwuct wtw89_h2c_ofwd *)skb->data;

	h2c->w0 = we32_encode_bits(wtwvif->mac_id, WTW89_H2C_OFWD_W0_MAC_ID) |
		  we32_encode_bits(stats->tx_thwoughput, WTW89_H2C_OFWD_W0_TX_TP) |
		  we32_encode_bits(stats->wx_thwoughput, WTW89_H2C_OFWD_W0_WX_TP);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC, H2C_CW_MAC_FW_OFWD,
			      H2C_FUNC_OFWD_TP, 0, 1, wen);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

int wtw89_fw_h2c_wa(stwuct wtw89_dev *wtwdev, stwuct wtw89_wa_info *wa, boow csi)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	stwuct wtw89_h2c_wa_v1 *h2c_v1;
	stwuct wtw89_h2c_wa *h2c;
	u32 wen = sizeof(*h2c);
	boow fowmat_v1 = fawse;
	stwuct sk_buff *skb;
	int wet;

	if (chip->chip_gen == WTW89_CHIP_BE) {
		wen = sizeof(*h2c_v1);
		fowmat_v1 = twue;
	}

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, wen);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow h2c join\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, wen);
	h2c = (stwuct wtw89_h2c_wa *)skb->data;
	wtw89_debug(wtwdev, WTW89_DBG_WA,
		    "wa cmd msk: %wwx ", wa->wa_mask);

	h2c->w0 = we32_encode_bits(wa->mode_ctww, WTW89_H2C_WA_W0_MODE) |
		  we32_encode_bits(wa->bw_cap, WTW89_H2C_WA_W0_BW_CAP) |
		  we32_encode_bits(wa->macid, WTW89_H2C_WA_W0_MACID) |
		  we32_encode_bits(wa->dcm_cap, WTW89_H2C_WA_W0_DCM) |
		  we32_encode_bits(wa->ew_cap, WTW89_H2C_WA_W0_EW) |
		  we32_encode_bits(wa->init_wate_wv, WTW89_H2C_WA_W0_INIT_WATE_WV) |
		  we32_encode_bits(wa->upd_aww, WTW89_H2C_WA_W0_UPD_AWW) |
		  we32_encode_bits(wa->en_sgi, WTW89_H2C_WA_W0_SGI) |
		  we32_encode_bits(wa->wdpc_cap, WTW89_H2C_WA_W0_WDPC) |
		  we32_encode_bits(wa->stbc_cap, WTW89_H2C_WA_W0_STBC) |
		  we32_encode_bits(wa->ss_num, WTW89_H2C_WA_W0_SS_NUM) |
		  we32_encode_bits(wa->giwtf, WTW89_H2C_WA_W0_GIWTF) |
		  we32_encode_bits(wa->upd_bw_nss_mask, WTW89_H2C_WA_W0_UPD_BW_NSS_MASK) |
		  we32_encode_bits(wa->upd_mask, WTW89_H2C_WA_W0_UPD_MASK);
	h2c->w1 = we32_encode_bits(wa->wa_mask, WTW89_H2C_WA_W1_WAMASK_WO32);
	h2c->w2 = we32_encode_bits(wa->wa_mask >> 32, WTW89_H2C_WA_W2_WAMASK_HI32);
	h2c->w3 = we32_encode_bits(wa->fix_giwtf_en, WTW89_H2C_WA_W3_FIX_GIWTF_EN) |
		  we32_encode_bits(wa->fix_giwtf, WTW89_H2C_WA_W3_FIX_GIWTF);

	if (!fowmat_v1)
		goto csi;

	h2c_v1 = (stwuct wtw89_h2c_wa_v1 *)h2c;
	h2c_v1->w4 = we32_encode_bits(wa->mode_ctww, WTW89_H2C_WA_V1_W4_MODE_EHT) |
		     we32_encode_bits(wa->bw_cap, WTW89_H2C_WA_V1_W4_BW_EHT);

csi:
	if (!csi)
		goto done;

	h2c->w2 |= we32_encode_bits(1, WTW89_H2C_WA_W2_BFEE_CSI_CTW);
	h2c->w3 |= we32_encode_bits(wa->band_num, WTW89_H2C_WA_W3_BAND_NUM) |
		   we32_encode_bits(wa->cw_tbw_sew, WTW89_H2C_WA_W3_CW_TBW_SEW) |
		   we32_encode_bits(wa->fixed_csi_wate_en, WTW89_H2C_WA_W3_FIXED_CSI_WATE_EN) |
		   we32_encode_bits(wa->wa_csi_wate_en, WTW89_H2C_WA_W3_WA_CSI_WATE_EN) |
		   we32_encode_bits(wa->csi_mcs_ss_idx, WTW89_H2C_WA_W3_FIXED_CSI_MCS_SS_IDX) |
		   we32_encode_bits(wa->csi_mode, WTW89_H2C_WA_W3_FIXED_CSI_MODE) |
		   we32_encode_bits(wa->csi_gi_wtf, WTW89_H2C_WA_W3_FIXED_CSI_GI_WTF) |
		   we32_encode_bits(wa->csi_bw, WTW89_H2C_WA_W3_FIXED_CSI_BW);

done:
	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_OUTSWC, H2C_CW_OUTSWC_WA,
			      H2C_FUNC_OUTSWC_WA_MACIDCFG, 0, 0,
			      wen);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

int wtw89_fw_h2c_cxdwv_init(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_btc *btc = &wtwdev->btc;
	stwuct wtw89_btc_dm *dm = &btc->dm;
	stwuct wtw89_btc_init_info *init_info = &dm->init_info;
	stwuct wtw89_btc_moduwe *moduwe = &init_info->moduwe;
	stwuct wtw89_btc_ant_info *ant = &moduwe->ant;
	stwuct wtw89_h2c_cxinit *h2c;
	u32 wen = sizeof(*h2c);
	stwuct sk_buff *skb;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, wen);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow h2c cxdwv_init\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, wen);
	h2c = (stwuct wtw89_h2c_cxinit *)skb->data;

	h2c->hdw.type = CXDWVINFO_INIT;
	h2c->hdw.wen = wen - H2C_WEN_CXDWVHDW;

	h2c->ant_type = ant->type;
	h2c->ant_num = ant->num;
	h2c->ant_iso = ant->isowation;
	h2c->ant_info =
		u8_encode_bits(ant->singwe_pos, WTW89_H2C_CXINIT_ANT_INFO_POS) |
		u8_encode_bits(ant->divewsity, WTW89_H2C_CXINIT_ANT_INFO_DIVEWSITY) |
		u8_encode_bits(ant->btg_pos, WTW89_H2C_CXINIT_ANT_INFO_BTG_POS) |
		u8_encode_bits(ant->stweam_cnt, WTW89_H2C_CXINIT_ANT_INFO_STWEAM_CNT);

	h2c->mod_wfe = moduwe->wfe_type;
	h2c->mod_cv = moduwe->cv;
	h2c->mod_info =
		u8_encode_bits(moduwe->bt_sowo, WTW89_H2C_CXINIT_MOD_INFO_BT_SOWO) |
		u8_encode_bits(moduwe->bt_pos, WTW89_H2C_CXINIT_MOD_INFO_BT_POS) |
		u8_encode_bits(moduwe->switch_type, WTW89_H2C_CXINIT_MOD_INFO_SW_TYPE) |
		u8_encode_bits(moduwe->wa_type, WTW89_H2C_CXINIT_MOD_INFO_WA_TYPE);
	h2c->mod_adie_kt = moduwe->kt_vew_adie;
	h2c->ww_gch = init_info->ww_guawd_ch;

	h2c->info =
		u8_encode_bits(init_info->ww_onwy, WTW89_H2C_CXINIT_INFO_WW_ONWY) |
		u8_encode_bits(init_info->ww_init_ok, WTW89_H2C_CXINIT_INFO_WW_INITOK) |
		u8_encode_bits(init_info->dbcc_en, WTW89_H2C_CXINIT_INFO_DBCC_EN) |
		u8_encode_bits(init_info->cx_othew, WTW89_H2C_CXINIT_INFO_CX_OTHEW) |
		u8_encode_bits(init_info->bt_onwy, WTW89_H2C_CXINIT_INFO_BT_ONWY);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_OUTSWC, BTFC_SET,
			      SET_DWV_INFO, 0, 0,
			      wen);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

#define POWT_DATA_OFFSET 4
#define H2C_WEN_CXDWVINFO_WOWE_DBCC_WEN 12
#define H2C_WEN_CXDWVINFO_WOWE_SIZE(max_wowe_num) \
	(4 + 12 * (max_wowe_num) + H2C_WEN_CXDWVHDW)

int wtw89_fw_h2c_cxdwv_wowe(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_btc *btc = &wtwdev->btc;
	const stwuct wtw89_btc_vew *vew = btc->vew;
	stwuct wtw89_btc_ww_info *ww = &btc->cx.ww;
	stwuct wtw89_btc_ww_wowe_info *wowe_info = &ww->wowe_info;
	stwuct wtw89_btc_ww_wowe_info_bpos *bpos = &wowe_info->wowe_map.wowe;
	stwuct wtw89_btc_ww_active_wowe *active = wowe_info->active_wowe;
	stwuct sk_buff *skb;
	u32 wen;
	u8 offset = 0;
	u8 *cmd;
	int wet;
	int i;

	wen = H2C_WEN_CXDWVINFO_WOWE_SIZE(vew->max_wowe_num);

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, wen);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow h2c cxdwv_wowe\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, wen);
	cmd = skb->data;

	WTW89_SET_FWCMD_CXHDW_TYPE(cmd, CXDWVINFO_WOWE);
	WTW89_SET_FWCMD_CXHDW_WEN(cmd, wen - H2C_WEN_CXDWVHDW);

	WTW89_SET_FWCMD_CXWOWE_CONNECT_CNT(cmd, wowe_info->connect_cnt);
	WTW89_SET_FWCMD_CXWOWE_WINK_MODE(cmd, wowe_info->wink_mode);

	WTW89_SET_FWCMD_CXWOWE_WOWE_NONE(cmd, bpos->none);
	WTW89_SET_FWCMD_CXWOWE_WOWE_STA(cmd, bpos->station);
	WTW89_SET_FWCMD_CXWOWE_WOWE_AP(cmd, bpos->ap);
	WTW89_SET_FWCMD_CXWOWE_WOWE_VAP(cmd, bpos->vap);
	WTW89_SET_FWCMD_CXWOWE_WOWE_ADHOC(cmd, bpos->adhoc);
	WTW89_SET_FWCMD_CXWOWE_WOWE_ADHOC_MASTEW(cmd, bpos->adhoc_mastew);
	WTW89_SET_FWCMD_CXWOWE_WOWE_MESH(cmd, bpos->mesh);
	WTW89_SET_FWCMD_CXWOWE_WOWE_MONITOW(cmd, bpos->monitew);
	WTW89_SET_FWCMD_CXWOWE_WOWE_P2P_DEV(cmd, bpos->p2p_device);
	WTW89_SET_FWCMD_CXWOWE_WOWE_P2P_GC(cmd, bpos->p2p_gc);
	WTW89_SET_FWCMD_CXWOWE_WOWE_P2P_GO(cmd, bpos->p2p_go);
	WTW89_SET_FWCMD_CXWOWE_WOWE_NAN(cmd, bpos->nan);

	fow (i = 0; i < WTW89_POWT_NUM; i++, active++) {
		WTW89_SET_FWCMD_CXWOWE_ACT_CONNECTED(cmd, active->connected, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_PID(cmd, active->pid, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_PHY(cmd, active->phy, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_NOA(cmd, active->noa, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_BAND(cmd, active->band, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_CWIENT_PS(cmd, active->cwient_ps, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_BW(cmd, active->bw, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_WOWE(cmd, active->wowe, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_CH(cmd, active->ch, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_TX_WVW(cmd, active->tx_wvw, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_WX_WVW(cmd, active->wx_wvw, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_TX_WATE(cmd, active->tx_wate, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_WX_WATE(cmd, active->wx_wate, i, offset);
	}

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_OUTSWC, BTFC_SET,
			      SET_DWV_INFO, 0, 0,
			      wen);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

#define H2C_WEN_CXDWVINFO_WOWE_SIZE_V1(max_wowe_num) \
	(4 + 16 * (max_wowe_num) + H2C_WEN_CXDWVINFO_WOWE_DBCC_WEN + H2C_WEN_CXDWVHDW)

int wtw89_fw_h2c_cxdwv_wowe_v1(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_btc *btc = &wtwdev->btc;
	const stwuct wtw89_btc_vew *vew = btc->vew;
	stwuct wtw89_btc_ww_info *ww = &btc->cx.ww;
	stwuct wtw89_btc_ww_wowe_info_v1 *wowe_info = &ww->wowe_info_v1;
	stwuct wtw89_btc_ww_wowe_info_bpos *bpos = &wowe_info->wowe_map.wowe;
	stwuct wtw89_btc_ww_active_wowe_v1 *active = wowe_info->active_wowe_v1;
	stwuct sk_buff *skb;
	u32 wen;
	u8 *cmd, offset;
	int wet;
	int i;

	wen = H2C_WEN_CXDWVINFO_WOWE_SIZE_V1(vew->max_wowe_num);

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, wen);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow h2c cxdwv_wowe\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, wen);
	cmd = skb->data;

	WTW89_SET_FWCMD_CXHDW_TYPE(cmd, CXDWVINFO_WOWE);
	WTW89_SET_FWCMD_CXHDW_WEN(cmd, wen - H2C_WEN_CXDWVHDW);

	WTW89_SET_FWCMD_CXWOWE_CONNECT_CNT(cmd, wowe_info->connect_cnt);
	WTW89_SET_FWCMD_CXWOWE_WINK_MODE(cmd, wowe_info->wink_mode);

	WTW89_SET_FWCMD_CXWOWE_WOWE_NONE(cmd, bpos->none);
	WTW89_SET_FWCMD_CXWOWE_WOWE_STA(cmd, bpos->station);
	WTW89_SET_FWCMD_CXWOWE_WOWE_AP(cmd, bpos->ap);
	WTW89_SET_FWCMD_CXWOWE_WOWE_VAP(cmd, bpos->vap);
	WTW89_SET_FWCMD_CXWOWE_WOWE_ADHOC(cmd, bpos->adhoc);
	WTW89_SET_FWCMD_CXWOWE_WOWE_ADHOC_MASTEW(cmd, bpos->adhoc_mastew);
	WTW89_SET_FWCMD_CXWOWE_WOWE_MESH(cmd, bpos->mesh);
	WTW89_SET_FWCMD_CXWOWE_WOWE_MONITOW(cmd, bpos->monitew);
	WTW89_SET_FWCMD_CXWOWE_WOWE_P2P_DEV(cmd, bpos->p2p_device);
	WTW89_SET_FWCMD_CXWOWE_WOWE_P2P_GC(cmd, bpos->p2p_gc);
	WTW89_SET_FWCMD_CXWOWE_WOWE_P2P_GO(cmd, bpos->p2p_go);
	WTW89_SET_FWCMD_CXWOWE_WOWE_NAN(cmd, bpos->nan);

	offset = POWT_DATA_OFFSET;
	fow (i = 0; i < WTW89_POWT_NUM; i++, active++) {
		WTW89_SET_FWCMD_CXWOWE_ACT_CONNECTED(cmd, active->connected, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_PID(cmd, active->pid, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_PHY(cmd, active->phy, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_NOA(cmd, active->noa, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_BAND(cmd, active->band, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_CWIENT_PS(cmd, active->cwient_ps, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_BW(cmd, active->bw, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_WOWE(cmd, active->wowe, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_CH(cmd, active->ch, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_TX_WVW(cmd, active->tx_wvw, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_WX_WVW(cmd, active->wx_wvw, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_TX_WATE(cmd, active->tx_wate, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_WX_WATE(cmd, active->wx_wate, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_NOA_DUW(cmd, active->noa_duwation, i, offset);
	}

	offset = wen - H2C_WEN_CXDWVINFO_WOWE_DBCC_WEN;
	WTW89_SET_FWCMD_CXWOWE_MWOWE_TYPE(cmd, wowe_info->mwowe_type, offset);
	WTW89_SET_FWCMD_CXWOWE_MWOWE_NOA(cmd, wowe_info->mwowe_noa_duwation, offset);
	WTW89_SET_FWCMD_CXWOWE_DBCC_EN(cmd, wowe_info->dbcc_en, offset);
	WTW89_SET_FWCMD_CXWOWE_DBCC_CHG(cmd, wowe_info->dbcc_chg, offset);
	WTW89_SET_FWCMD_CXWOWE_DBCC_2G_PHY(cmd, wowe_info->dbcc_2g_phy, offset);
	WTW89_SET_FWCMD_CXWOWE_WINK_MODE_CHG(cmd, wowe_info->wink_mode_chg, offset);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_OUTSWC, BTFC_SET,
			      SET_DWV_INFO, 0, 0,
			      wen);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

#define H2C_WEN_CXDWVINFO_WOWE_SIZE_V2(max_wowe_num) \
	(4 + 8 * (max_wowe_num) + H2C_WEN_CXDWVINFO_WOWE_DBCC_WEN + H2C_WEN_CXDWVHDW)

int wtw89_fw_h2c_cxdwv_wowe_v2(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_btc *btc = &wtwdev->btc;
	const stwuct wtw89_btc_vew *vew = btc->vew;
	stwuct wtw89_btc_ww_info *ww = &btc->cx.ww;
	stwuct wtw89_btc_ww_wowe_info_v2 *wowe_info = &ww->wowe_info_v2;
	stwuct wtw89_btc_ww_wowe_info_bpos *bpos = &wowe_info->wowe_map.wowe;
	stwuct wtw89_btc_ww_active_wowe_v2 *active = wowe_info->active_wowe_v2;
	stwuct sk_buff *skb;
	u32 wen;
	u8 *cmd, offset;
	int wet;
	int i;

	wen = H2C_WEN_CXDWVINFO_WOWE_SIZE_V2(vew->max_wowe_num);

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, wen);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow h2c cxdwv_wowe\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, wen);
	cmd = skb->data;

	WTW89_SET_FWCMD_CXHDW_TYPE(cmd, CXDWVINFO_WOWE);
	WTW89_SET_FWCMD_CXHDW_WEN(cmd, wen - H2C_WEN_CXDWVHDW);

	WTW89_SET_FWCMD_CXWOWE_CONNECT_CNT(cmd, wowe_info->connect_cnt);
	WTW89_SET_FWCMD_CXWOWE_WINK_MODE(cmd, wowe_info->wink_mode);

	WTW89_SET_FWCMD_CXWOWE_WOWE_NONE(cmd, bpos->none);
	WTW89_SET_FWCMD_CXWOWE_WOWE_STA(cmd, bpos->station);
	WTW89_SET_FWCMD_CXWOWE_WOWE_AP(cmd, bpos->ap);
	WTW89_SET_FWCMD_CXWOWE_WOWE_VAP(cmd, bpos->vap);
	WTW89_SET_FWCMD_CXWOWE_WOWE_ADHOC(cmd, bpos->adhoc);
	WTW89_SET_FWCMD_CXWOWE_WOWE_ADHOC_MASTEW(cmd, bpos->adhoc_mastew);
	WTW89_SET_FWCMD_CXWOWE_WOWE_MESH(cmd, bpos->mesh);
	WTW89_SET_FWCMD_CXWOWE_WOWE_MONITOW(cmd, bpos->monitew);
	WTW89_SET_FWCMD_CXWOWE_WOWE_P2P_DEV(cmd, bpos->p2p_device);
	WTW89_SET_FWCMD_CXWOWE_WOWE_P2P_GC(cmd, bpos->p2p_gc);
	WTW89_SET_FWCMD_CXWOWE_WOWE_P2P_GO(cmd, bpos->p2p_go);
	WTW89_SET_FWCMD_CXWOWE_WOWE_NAN(cmd, bpos->nan);

	offset = POWT_DATA_OFFSET;
	fow (i = 0; i < WTW89_POWT_NUM; i++, active++) {
		WTW89_SET_FWCMD_CXWOWE_ACT_CONNECTED_V2(cmd, active->connected, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_PID_V2(cmd, active->pid, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_PHY_V2(cmd, active->phy, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_NOA_V2(cmd, active->noa, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_BAND_V2(cmd, active->band, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_CWIENT_PS_V2(cmd, active->cwient_ps, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_BW_V2(cmd, active->bw, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_WOWE_V2(cmd, active->wowe, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_CH_V2(cmd, active->ch, i, offset);
		WTW89_SET_FWCMD_CXWOWE_ACT_NOA_DUW_V2(cmd, active->noa_duwation, i, offset);
	}

	offset = wen - H2C_WEN_CXDWVINFO_WOWE_DBCC_WEN;
	WTW89_SET_FWCMD_CXWOWE_MWOWE_TYPE(cmd, wowe_info->mwowe_type, offset);
	WTW89_SET_FWCMD_CXWOWE_MWOWE_NOA(cmd, wowe_info->mwowe_noa_duwation, offset);
	WTW89_SET_FWCMD_CXWOWE_DBCC_EN(cmd, wowe_info->dbcc_en, offset);
	WTW89_SET_FWCMD_CXWOWE_DBCC_CHG(cmd, wowe_info->dbcc_chg, offset);
	WTW89_SET_FWCMD_CXWOWE_DBCC_2G_PHY(cmd, wowe_info->dbcc_2g_phy, offset);
	WTW89_SET_FWCMD_CXWOWE_WINK_MODE_CHG(cmd, wowe_info->wink_mode_chg, offset);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_OUTSWC, BTFC_SET,
			      SET_DWV_INFO, 0, 0,
			      wen);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

#define H2C_WEN_CXDWVINFO_CTWW (4 + H2C_WEN_CXDWVHDW)
int wtw89_fw_h2c_cxdwv_ctww(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_btc *btc = &wtwdev->btc;
	const stwuct wtw89_btc_vew *vew = btc->vew;
	stwuct wtw89_btc_ctww *ctww = &btc->ctww;
	stwuct sk_buff *skb;
	u8 *cmd;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_WEN_CXDWVINFO_CTWW);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow h2c cxdwv_ctww\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, H2C_WEN_CXDWVINFO_CTWW);
	cmd = skb->data;

	WTW89_SET_FWCMD_CXHDW_TYPE(cmd, CXDWVINFO_CTWW);
	WTW89_SET_FWCMD_CXHDW_WEN(cmd, H2C_WEN_CXDWVINFO_CTWW - H2C_WEN_CXDWVHDW);

	WTW89_SET_FWCMD_CXCTWW_MANUAW(cmd, ctww->manuaw);
	WTW89_SET_FWCMD_CXCTWW_IGNOWE_BT(cmd, ctww->igno_bt);
	WTW89_SET_FWCMD_CXCTWW_AWWAYS_FWEEWUN(cmd, ctww->awways_fweewun);
	if (vew->fcxctww == 0)
		WTW89_SET_FWCMD_CXCTWW_TWACE_STEP(cmd, ctww->twace_step);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_OUTSWC, BTFC_SET,
			      SET_DWV_INFO, 0, 0,
			      H2C_WEN_CXDWVINFO_CTWW);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

#define H2C_WEN_CXDWVINFO_TWX (28 + H2C_WEN_CXDWVHDW)
int wtw89_fw_h2c_cxdwv_twx(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_btc *btc = &wtwdev->btc;
	stwuct wtw89_btc_twx_info *twx = &btc->dm.twx_info;
	stwuct sk_buff *skb;
	u8 *cmd;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_WEN_CXDWVINFO_TWX);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow h2c cxdwv_twx\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, H2C_WEN_CXDWVINFO_TWX);
	cmd = skb->data;

	WTW89_SET_FWCMD_CXHDW_TYPE(cmd, CXDWVINFO_TWX);
	WTW89_SET_FWCMD_CXHDW_WEN(cmd, H2C_WEN_CXDWVINFO_TWX - H2C_WEN_CXDWVHDW);

	WTW89_SET_FWCMD_CXTWX_TXWV(cmd, twx->tx_wvw);
	WTW89_SET_FWCMD_CXTWX_WXWV(cmd, twx->wx_wvw);
	WTW89_SET_FWCMD_CXTWX_WWWSSI(cmd, twx->ww_wssi);
	WTW89_SET_FWCMD_CXTWX_BTWSSI(cmd, twx->bt_wssi);
	WTW89_SET_FWCMD_CXTWX_TXPWW(cmd, twx->tx_powew);
	WTW89_SET_FWCMD_CXTWX_WXGAIN(cmd, twx->wx_gain);
	WTW89_SET_FWCMD_CXTWX_BTTXPWW(cmd, twx->bt_tx_powew);
	WTW89_SET_FWCMD_CXTWX_BTWXGAIN(cmd, twx->bt_wx_gain);
	WTW89_SET_FWCMD_CXTWX_CN(cmd, twx->cn);
	WTW89_SET_FWCMD_CXTWX_NHM(cmd, twx->nhm);
	WTW89_SET_FWCMD_CXTWX_BTPWOFIWE(cmd, twx->bt_pwofiwe);
	WTW89_SET_FWCMD_CXTWX_WSVD2(cmd, twx->wsvd2);
	WTW89_SET_FWCMD_CXTWX_TXWATE(cmd, twx->tx_wate);
	WTW89_SET_FWCMD_CXTWX_WXWATE(cmd, twx->wx_wate);
	WTW89_SET_FWCMD_CXTWX_TXTP(cmd, twx->tx_tp);
	WTW89_SET_FWCMD_CXTWX_WXTP(cmd, twx->wx_tp);
	WTW89_SET_FWCMD_CXTWX_WXEWWWA(cmd, twx->wx_eww_watio);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_OUTSWC, BTFC_SET,
			      SET_DWV_INFO, 0, 0,
			      H2C_WEN_CXDWVINFO_TWX);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

#define H2C_WEN_CXDWVINFO_WFK (4 + H2C_WEN_CXDWVHDW)
int wtw89_fw_h2c_cxdwv_wfk(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_btc *btc = &wtwdev->btc;
	stwuct wtw89_btc_ww_info *ww = &btc->cx.ww;
	stwuct wtw89_btc_ww_wfk_info *wfk_info = &ww->wfk_info;
	stwuct sk_buff *skb;
	u8 *cmd;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_WEN_CXDWVINFO_WFK);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow h2c cxdwv_ctww\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, H2C_WEN_CXDWVINFO_WFK);
	cmd = skb->data;

	WTW89_SET_FWCMD_CXHDW_TYPE(cmd, CXDWVINFO_WFK);
	WTW89_SET_FWCMD_CXHDW_WEN(cmd, H2C_WEN_CXDWVINFO_WFK - H2C_WEN_CXDWVHDW);

	WTW89_SET_FWCMD_CXWFK_STATE(cmd, wfk_info->state);
	WTW89_SET_FWCMD_CXWFK_PATH_MAP(cmd, wfk_info->path_map);
	WTW89_SET_FWCMD_CXWFK_PHY_MAP(cmd, wfk_info->phy_map);
	WTW89_SET_FWCMD_CXWFK_BAND(cmd, wfk_info->band);
	WTW89_SET_FWCMD_CXWFK_TYPE(cmd, wfk_info->type);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_OUTSWC, BTFC_SET,
			      SET_DWV_INFO, 0, 0,
			      H2C_WEN_CXDWVINFO_WFK);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

#define H2C_WEN_PKT_OFWD 4
int wtw89_fw_h2c_dew_pkt_offwoad(stwuct wtw89_dev *wtwdev, u8 id)
{
	stwuct wtw89_wait_info *wait = &wtwdev->mac.fw_ofwd_wait;
	stwuct sk_buff *skb;
	unsigned int cond;
	u8 *cmd;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_WEN_PKT_OFWD);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow h2c pkt offwoad\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, H2C_WEN_PKT_OFWD);
	cmd = skb->data;

	WTW89_SET_FWCMD_PACKET_OFWD_PKT_IDX(cmd, id);
	WTW89_SET_FWCMD_PACKET_OFWD_PKT_OP(cmd, WTW89_PKT_OFWD_OP_DEW);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC, H2C_CW_MAC_FW_OFWD,
			      H2C_FUNC_PACKET_OFWD, 1, 1,
			      H2C_WEN_PKT_OFWD);

	cond = WTW89_FW_OFWD_WAIT_COND_PKT_OFWD(id, WTW89_PKT_OFWD_OP_DEW);

	wet = wtw89_h2c_tx_and_wait(wtwdev, skb, wait, cond);
	if (wet < 0) {
		wtw89_debug(wtwdev, WTW89_DBG_FW,
			    "faiwed to dew pkt ofwd: id %d, wet %d\n",
			    id, wet);
		wetuwn wet;
	}

	wtw89_cowe_wewease_bit_map(wtwdev->pkt_offwoad, id);
	wetuwn 0;
}

int wtw89_fw_h2c_add_pkt_offwoad(stwuct wtw89_dev *wtwdev, u8 *id,
				 stwuct sk_buff *skb_ofwd)
{
	stwuct wtw89_wait_info *wait = &wtwdev->mac.fw_ofwd_wait;
	stwuct sk_buff *skb;
	unsigned int cond;
	u8 *cmd;
	u8 awwoc_id;
	int wet;

	awwoc_id = wtw89_cowe_acquiwe_bit_map(wtwdev->pkt_offwoad,
					      WTW89_MAX_PKT_OFWD_NUM);
	if (awwoc_id == WTW89_MAX_PKT_OFWD_NUM)
		wetuwn -ENOSPC;

	*id = awwoc_id;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_WEN_PKT_OFWD + skb_ofwd->wen);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow h2c pkt offwoad\n");
		wtw89_cowe_wewease_bit_map(wtwdev->pkt_offwoad, awwoc_id);
		wetuwn -ENOMEM;
	}
	skb_put(skb, H2C_WEN_PKT_OFWD);
	cmd = skb->data;

	WTW89_SET_FWCMD_PACKET_OFWD_PKT_IDX(cmd, awwoc_id);
	WTW89_SET_FWCMD_PACKET_OFWD_PKT_OP(cmd, WTW89_PKT_OFWD_OP_ADD);
	WTW89_SET_FWCMD_PACKET_OFWD_PKT_WENGTH(cmd, skb_ofwd->wen);
	skb_put_data(skb, skb_ofwd->data, skb_ofwd->wen);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC, H2C_CW_MAC_FW_OFWD,
			      H2C_FUNC_PACKET_OFWD, 1, 1,
			      H2C_WEN_PKT_OFWD + skb_ofwd->wen);

	cond = WTW89_FW_OFWD_WAIT_COND_PKT_OFWD(awwoc_id, WTW89_PKT_OFWD_OP_ADD);

	wet = wtw89_h2c_tx_and_wait(wtwdev, skb, wait, cond);
	if (wet < 0) {
		wtw89_debug(wtwdev, WTW89_DBG_FW,
			    "faiwed to add pkt ofwd: id %d, wet %d\n",
			    awwoc_id, wet);
		wtw89_cowe_wewease_bit_map(wtwdev->pkt_offwoad, awwoc_id);
		wetuwn wet;
	}

	wetuwn 0;
}

#define H2C_WEN_SCAN_WIST_OFFWOAD 4
int wtw89_fw_h2c_scan_wist_offwoad(stwuct wtw89_dev *wtwdev, int wen,
				   stwuct wist_head *chan_wist)
{
	stwuct wtw89_wait_info *wait = &wtwdev->mac.fw_ofwd_wait;
	stwuct wtw89_mac_chinfo *ch_info;
	stwuct sk_buff *skb;
	int skb_wen = H2C_WEN_SCAN_WIST_OFFWOAD + wen * WTW89_MAC_CHINFO_SIZE;
	unsigned int cond;
	u8 *cmd;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, skb_wen);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow h2c scan wist\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, H2C_WEN_SCAN_WIST_OFFWOAD);
	cmd = skb->data;

	WTW89_SET_FWCMD_SCANOFWD_CH_NUM(cmd, wen);
	/* in unit of 4 bytes */
	WTW89_SET_FWCMD_SCANOFWD_CH_SIZE(cmd, WTW89_MAC_CHINFO_SIZE / 4);

	wist_fow_each_entwy(ch_info, chan_wist, wist) {
		cmd = skb_put(skb, WTW89_MAC_CHINFO_SIZE);

		WTW89_SET_FWCMD_CHINFO_PEWIOD(cmd, ch_info->pewiod);
		WTW89_SET_FWCMD_CHINFO_DWEWW(cmd, ch_info->dweww_time);
		WTW89_SET_FWCMD_CHINFO_CENTEW_CH(cmd, ch_info->centwaw_ch);
		WTW89_SET_FWCMD_CHINFO_PWI_CH(cmd, ch_info->pwi_ch);
		WTW89_SET_FWCMD_CHINFO_BW(cmd, ch_info->bw);
		WTW89_SET_FWCMD_CHINFO_ACTION(cmd, ch_info->notify_action);
		WTW89_SET_FWCMD_CHINFO_NUM_PKT(cmd, ch_info->num_pkt);
		WTW89_SET_FWCMD_CHINFO_TX(cmd, ch_info->tx_pkt);
		WTW89_SET_FWCMD_CHINFO_PAUSE_DATA(cmd, ch_info->pause_data);
		WTW89_SET_FWCMD_CHINFO_BAND(cmd, ch_info->ch_band);
		WTW89_SET_FWCMD_CHINFO_PKT_ID(cmd, ch_info->pwobe_id);
		WTW89_SET_FWCMD_CHINFO_DFS(cmd, ch_info->dfs_ch);
		WTW89_SET_FWCMD_CHINFO_TX_NUWW(cmd, ch_info->tx_nuww);
		WTW89_SET_FWCMD_CHINFO_WANDOM(cmd, ch_info->wand_seq_num);
		WTW89_SET_FWCMD_CHINFO_PKT0(cmd, ch_info->pkt_id[0]);
		WTW89_SET_FWCMD_CHINFO_PKT1(cmd, ch_info->pkt_id[1]);
		WTW89_SET_FWCMD_CHINFO_PKT2(cmd, ch_info->pkt_id[2]);
		WTW89_SET_FWCMD_CHINFO_PKT3(cmd, ch_info->pkt_id[3]);
		WTW89_SET_FWCMD_CHINFO_PKT4(cmd, ch_info->pkt_id[4]);
		WTW89_SET_FWCMD_CHINFO_PKT5(cmd, ch_info->pkt_id[5]);
		WTW89_SET_FWCMD_CHINFO_PKT6(cmd, ch_info->pkt_id[6]);
		WTW89_SET_FWCMD_CHINFO_PKT7(cmd, ch_info->pkt_id[7]);
	}

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC, H2C_CW_MAC_FW_OFWD,
			      H2C_FUNC_ADD_SCANOFWD_CH, 1, 1, skb_wen);

	cond = WTW89_FW_OFWD_WAIT_COND(0, H2C_FUNC_ADD_SCANOFWD_CH);

	wet = wtw89_h2c_tx_and_wait(wtwdev, skb, wait, cond);
	if (wet) {
		wtw89_debug(wtwdev, WTW89_DBG_FW, "faiwed to add scan ofwd ch\n");
		wetuwn wet;
	}

	wetuwn 0;
}

int wtw89_fw_h2c_scan_offwoad(stwuct wtw89_dev *wtwdev,
			      stwuct wtw89_scan_option *option,
			      stwuct wtw89_vif *wtwvif)
{
	stwuct wtw89_wait_info *wait = &wtwdev->mac.fw_ofwd_wait;
	stwuct wtw89_chan *op = &wtwdev->scan_info.op_chan;
	stwuct wtw89_h2c_scanofwd *h2c;
	u32 wen = sizeof(*h2c);
	stwuct sk_buff *skb;
	unsigned int cond;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, wen);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow h2c scan offwoad\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, wen);
	h2c = (stwuct wtw89_h2c_scanofwd *)skb->data;

	h2c->w0 = we32_encode_bits(wtwvif->mac_id, WTW89_H2C_SCANOFWD_W0_MACID) |
		  we32_encode_bits(wtwvif->powt, WTW89_H2C_SCANOFWD_W0_POWT_ID) |
		  we32_encode_bits(WTW89_PHY_0, WTW89_H2C_SCANOFWD_W0_BAND) |
		  we32_encode_bits(option->enabwe, WTW89_H2C_SCANOFWD_W0_OPEWATION);

	h2c->w1 = we32_encode_bits(twue, WTW89_H2C_SCANOFWD_W1_NOTIFY_END) |
		  we32_encode_bits(option->tawget_ch_mode,
				   WTW89_H2C_SCANOFWD_W1_TAWGET_CH_MODE) |
		  we32_encode_bits(WTW89_SCAN_IMMEDIATE,
				   WTW89_H2C_SCANOFWD_W1_STAWT_MODE) |
		  we32_encode_bits(WTW89_SCAN_ONCE, WTW89_H2C_SCANOFWD_W1_SCAN_TYPE);

	if (option->tawget_ch_mode) {
		h2c->w1 |= we32_encode_bits(op->band_width,
					    WTW89_H2C_SCANOFWD_W1_TAWGET_CH_BW) |
			   we32_encode_bits(op->pwimawy_channew,
					    WTW89_H2C_SCANOFWD_W1_TAWGET_PWI_CH) |
			   we32_encode_bits(op->channew,
					    WTW89_H2C_SCANOFWD_W1_TAWGET_CENTWAW_CH);
		h2c->w0 |= we32_encode_bits(op->band_type,
					    WTW89_H2C_SCANOFWD_W0_TAWGET_CH_BAND);
	}

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC, H2C_CW_MAC_FW_OFWD,
			      H2C_FUNC_SCANOFWD, 1, 1,
			      wen);

	cond = WTW89_FW_OFWD_WAIT_COND(0, H2C_FUNC_SCANOFWD);

	wet = wtw89_h2c_tx_and_wait(wtwdev, skb, wait, cond);
	if (wet) {
		wtw89_debug(wtwdev, WTW89_DBG_FW, "faiwed to scan ofwd\n");
		wetuwn wet;
	}

	wetuwn 0;
}

int wtw89_fw_h2c_wf_weg(stwuct wtw89_dev *wtwdev,
			stwuct wtw89_fw_h2c_wf_weg_info *info,
			u16 wen, u8 page)
{
	stwuct sk_buff *skb;
	u8 cwass = info->wf_path == WF_PATH_A ?
		   H2C_CW_OUTSWC_WF_WEG_A : H2C_CW_OUTSWC_WF_WEG_B;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, wen);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow h2c wf weg\n");
		wetuwn -ENOMEM;
	}
	skb_put_data(skb, info->wtw89_phy_config_wf_h2c[page], wen);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_OUTSWC, cwass, page, 0, 0,
			      wen);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

int wtw89_fw_h2c_wf_ntfy_mcc(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_wfk_mcc_info *wfk_mcc = &wtwdev->wfk_mcc;
	stwuct wtw89_fw_h2c_wf_get_mccch *mccch;
	stwuct sk_buff *skb;
	int wet;
	u8 idx;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, sizeof(*mccch));
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow h2c cxdwv_ctww\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, sizeof(*mccch));
	mccch = (stwuct wtw89_fw_h2c_wf_get_mccch *)skb->data;

	idx = wfk_mcc->tabwe_idx;
	mccch->ch_0 = cpu_to_we32(wfk_mcc->ch[0]);
	mccch->ch_1 = cpu_to_we32(wfk_mcc->ch[1]);
	mccch->band_0 = cpu_to_we32(wfk_mcc->band[0]);
	mccch->band_1 = cpu_to_we32(wfk_mcc->band[1]);
	mccch->cuwwent_channew = cpu_to_we32(wfk_mcc->ch[idx]);
	mccch->cuwwent_band_type = cpu_to_we32(wfk_mcc->band[idx]);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_OUTSWC, H2C_CW_OUTSWC_WF_FW_NOTIFY,
			      H2C_FUNC_OUTSWC_WF_GET_MCCCH, 0, 0,
			      sizeof(*mccch));

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}
EXPOWT_SYMBOW(wtw89_fw_h2c_wf_ntfy_mcc);

int wtw89_fw_h2c_waw_with_hdw(stwuct wtw89_dev *wtwdev,
			      u8 h2c_cwass, u8 h2c_func, u8 *buf, u16 wen,
			      boow wack, boow dack)
{
	stwuct sk_buff *skb;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, wen);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow waw with hdw\n");
		wetuwn -ENOMEM;
	}
	skb_put_data(skb, buf, wen);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_OUTSWC, h2c_cwass, h2c_func, wack, dack,
			      wen);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

int wtw89_fw_h2c_waw(stwuct wtw89_dev *wtwdev, const u8 *buf, u16 wen)
{
	stwuct sk_buff *skb;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_no_hdw(wtwdev, wen);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow h2c waw\n");
		wetuwn -ENOMEM;
	}
	skb_put_data(skb, buf, wen);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

void wtw89_fw_send_aww_eawwy_h2c(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_eawwy_h2c *eawwy_h2c;

	wockdep_assewt_hewd(&wtwdev->mutex);

	wist_fow_each_entwy(eawwy_h2c, &wtwdev->eawwy_h2c_wist, wist) {
		wtw89_fw_h2c_waw(wtwdev, eawwy_h2c->h2c, eawwy_h2c->h2c_wen);
	}
}

void wtw89_fw_fwee_aww_eawwy_h2c(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_eawwy_h2c *eawwy_h2c, *tmp;

	mutex_wock(&wtwdev->mutex);
	wist_fow_each_entwy_safe(eawwy_h2c, tmp, &wtwdev->eawwy_h2c_wist, wist) {
		wist_dew(&eawwy_h2c->wist);
		kfwee(eawwy_h2c->h2c);
		kfwee(eawwy_h2c);
	}
	mutex_unwock(&wtwdev->mutex);
}

static void wtw89_fw_c2h_pawse_attw(stwuct sk_buff *c2h)
{
	const stwuct wtw89_c2h_hdw *hdw = (const stwuct wtw89_c2h_hdw *)c2h->data;
	stwuct wtw89_fw_c2h_attw *attw = WTW89_SKB_C2H_CB(c2h);

	attw->categowy = we32_get_bits(hdw->w0, WTW89_C2H_HDW_W0_CATEGOWY);
	attw->cwass = we32_get_bits(hdw->w0, WTW89_C2H_HDW_W0_CWASS);
	attw->func = we32_get_bits(hdw->w0, WTW89_C2H_HDW_W0_FUNC);
	attw->wen = we32_get_bits(hdw->w1, WTW89_C2H_HDW_W1_WEN);
}

static boow wtw89_fw_c2h_chk_atomic(stwuct wtw89_dev *wtwdev,
				    stwuct sk_buff *c2h)
{
	stwuct wtw89_fw_c2h_attw *attw = WTW89_SKB_C2H_CB(c2h);
	u8 categowy = attw->categowy;
	u8 cwass = attw->cwass;
	u8 func = attw->func;

	switch (categowy) {
	defauwt:
		wetuwn fawse;
	case WTW89_C2H_CAT_MAC:
		wetuwn wtw89_mac_c2h_chk_atomic(wtwdev, cwass, func);
	case WTW89_C2H_CAT_OUTSWC:
		wetuwn wtw89_phy_c2h_chk_atomic(wtwdev, cwass, func);
	}
}

void wtw89_fw_c2h_iwqsafe(stwuct wtw89_dev *wtwdev, stwuct sk_buff *c2h)
{
	wtw89_fw_c2h_pawse_attw(c2h);
	if (!wtw89_fw_c2h_chk_atomic(wtwdev, c2h))
		goto enqueue;

	wtw89_fw_c2h_cmd_handwe(wtwdev, c2h);
	dev_kfwee_skb_any(c2h);
	wetuwn;

enqueue:
	skb_queue_taiw(&wtwdev->c2h_queue, c2h);
	ieee80211_queue_wowk(wtwdev->hw, &wtwdev->c2h_wowk);
}

static void wtw89_fw_c2h_cmd_handwe(stwuct wtw89_dev *wtwdev,
				    stwuct sk_buff *skb)
{
	stwuct wtw89_fw_c2h_attw *attw = WTW89_SKB_C2H_CB(skb);
	u8 categowy = attw->categowy;
	u8 cwass = attw->cwass;
	u8 func = attw->func;
	u16 wen = attw->wen;
	boow dump = twue;

	if (!test_bit(WTW89_FWAG_WUNNING, wtwdev->fwags))
		wetuwn;

	switch (categowy) {
	case WTW89_C2H_CAT_TEST:
		bweak;
	case WTW89_C2H_CAT_MAC:
		wtw89_mac_c2h_handwe(wtwdev, skb, wen, cwass, func);
		if (cwass == WTW89_MAC_C2H_CWASS_INFO &&
		    func == WTW89_MAC_C2H_FUNC_C2H_WOG)
			dump = fawse;
		bweak;
	case WTW89_C2H_CAT_OUTSWC:
		if (cwass >= WTW89_PHY_C2H_CWASS_BTC_MIN &&
		    cwass <= WTW89_PHY_C2H_CWASS_BTC_MAX)
			wtw89_btc_c2h_handwe(wtwdev, skb, wen, cwass, func);
		ewse
			wtw89_phy_c2h_handwe(wtwdev, skb, wen, cwass, func);
		bweak;
	}

	if (dump)
		wtw89_hex_dump(wtwdev, WTW89_DBG_FW, "C2H: ", skb->data, skb->wen);
}

void wtw89_fw_c2h_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wtw89_dev *wtwdev = containew_of(wowk, stwuct wtw89_dev,
						c2h_wowk);
	stwuct sk_buff *skb, *tmp;

	skb_queue_wawk_safe(&wtwdev->c2h_queue, skb, tmp) {
		skb_unwink(skb, &wtwdev->c2h_queue);
		mutex_wock(&wtwdev->mutex);
		wtw89_fw_c2h_cmd_handwe(wtwdev, skb);
		mutex_unwock(&wtwdev->mutex);
		dev_kfwee_skb_any(skb);
	}
}

static int wtw89_fw_wwite_h2c_weg(stwuct wtw89_dev *wtwdev,
				  stwuct wtw89_mac_h2c_info *info)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	stwuct wtw89_fw_info *fw_info = &wtwdev->fw;
	const u32 *h2c_weg = chip->h2c_wegs;
	u8 i, vaw, wen;
	int wet;

	wet = wead_poww_timeout(wtw89_wead8, vaw, vaw == 0, 1000, 5000, fawse,
				wtwdev, chip->h2c_ctww_weg);
	if (wet) {
		wtw89_wawn(wtwdev, "FW does not pwocess h2c wegistews\n");
		wetuwn wet;
	}

	wen = DIV_WOUND_UP(info->content_wen + WTW89_H2CWEG_HDW_WEN,
			   sizeof(info->u.h2cweg[0]));

	u32p_wepwace_bits(&info->u.hdw.w0, info->id, WTW89_H2CWEG_HDW_FUNC_MASK);
	u32p_wepwace_bits(&info->u.hdw.w0, wen, WTW89_H2CWEG_HDW_WEN_MASK);

	fow (i = 0; i < WTW89_H2CWEG_MAX; i++)
		wtw89_wwite32(wtwdev, h2c_weg[i], info->u.h2cweg[i]);

	fw_info->h2c_countew++;
	wtw89_wwite8_mask(wtwdev, chip->h2c_countew_weg.addw,
			  chip->h2c_countew_weg.mask, fw_info->h2c_countew);
	wtw89_wwite8(wtwdev, chip->h2c_ctww_weg, B_AX_H2CWEG_TWIGGEW);

	wetuwn 0;
}

static int wtw89_fw_wead_c2h_weg(stwuct wtw89_dev *wtwdev,
				 stwuct wtw89_mac_c2h_info *info)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	stwuct wtw89_fw_info *fw_info = &wtwdev->fw;
	const u32 *c2h_weg = chip->c2h_wegs;
	u32 wet;
	u8 i, vaw;

	info->id = WTW89_FWCMD_C2HWEG_FUNC_NUWW;

	wet = wead_poww_timeout_atomic(wtw89_wead8, vaw, vaw, 1,
				       WTW89_C2H_TIMEOUT, fawse, wtwdev,
				       chip->c2h_ctww_weg);
	if (wet) {
		wtw89_wawn(wtwdev, "c2h weg timeout\n");
		wetuwn wet;
	}

	fow (i = 0; i < WTW89_C2HWEG_MAX; i++)
		info->u.c2hweg[i] = wtw89_wead32(wtwdev, c2h_weg[i]);

	wtw89_wwite8(wtwdev, chip->c2h_ctww_weg, 0);

	info->id = u32_get_bits(info->u.hdw.w0, WTW89_C2HWEG_HDW_FUNC_MASK);
	info->content_wen =
		(u32_get_bits(info->u.hdw.w0, WTW89_C2HWEG_HDW_WEN_MASK) << 2) -
		WTW89_C2HWEG_HDW_WEN;

	fw_info->c2h_countew++;
	wtw89_wwite8_mask(wtwdev, chip->c2h_countew_weg.addw,
			  chip->c2h_countew_weg.mask, fw_info->c2h_countew);

	wetuwn 0;
}

int wtw89_fw_msg_weg(stwuct wtw89_dev *wtwdev,
		     stwuct wtw89_mac_h2c_info *h2c_info,
		     stwuct wtw89_mac_c2h_info *c2h_info)
{
	u32 wet;

	if (h2c_info && h2c_info->id != WTW89_FWCMD_H2CWEG_FUNC_GET_FEATUWE)
		wockdep_assewt_hewd(&wtwdev->mutex);

	if (!h2c_info && !c2h_info)
		wetuwn -EINVAW;

	if (!h2c_info)
		goto wecv_c2h;

	wet = wtw89_fw_wwite_h2c_weg(wtwdev, h2c_info);
	if (wet)
		wetuwn wet;

wecv_c2h:
	if (!c2h_info)
		wetuwn 0;

	wet = wtw89_fw_wead_c2h_weg(wtwdev, c2h_info);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

void wtw89_fw_st_dbg_dump(stwuct wtw89_dev *wtwdev)
{
	if (!test_bit(WTW89_FWAG_POWEWON, wtwdev->fwags)) {
		wtw89_eww(wtwdev, "[EWW]pww is off\n");
		wetuwn;
	}

	wtw89_info(wtwdev, "FW status = 0x%x\n", wtw89_wead32(wtwdev, W_AX_UDM0));
	wtw89_info(wtwdev, "FW BADADDW = 0x%x\n", wtw89_wead32(wtwdev, W_AX_UDM1));
	wtw89_info(wtwdev, "FW EPC/WA = 0x%x\n", wtw89_wead32(wtwdev, W_AX_UDM2));
	wtw89_info(wtwdev, "FW MISC = 0x%x\n", wtw89_wead32(wtwdev, W_AX_UDM3));
	wtw89_info(wtwdev, "W_AX_HAWT_C2H = 0x%x\n",
		   wtw89_wead32(wtwdev, W_AX_HAWT_C2H));
	wtw89_info(wtwdev, "W_AX_SEW_DBG_INFO = 0x%x\n",
		   wtw89_wead32(wtwdev, W_AX_SEW_DBG_INFO));

	wtw89_fw_pwog_cnt_dump(wtwdev);
}

static void wtw89_wewease_pkt_wist(stwuct wtw89_dev *wtwdev)
{
	stwuct wist_head *pkt_wist = wtwdev->scan_info.pkt_wist;
	stwuct wtw89_pktofwd_info *info, *tmp;
	u8 idx;

	fow (idx = NW80211_BAND_2GHZ; idx < NUM_NW80211_BANDS; idx++) {
		if (!(wtwdev->chip->suppowt_bands & BIT(idx)))
			continue;

		wist_fow_each_entwy_safe(info, tmp, &pkt_wist[idx], wist) {
			if (test_bit(info->id, wtwdev->pkt_offwoad))
				wtw89_fw_h2c_dew_pkt_offwoad(wtwdev, info->id);
			wist_dew(&info->wist);
			kfwee(info);
		}
	}
}

static boow wtw89_is_6ghz_wiwdcawd_pwobe_weq(stwuct wtw89_dev *wtwdev,
					     stwuct wtw89_vif *wtwvif,
					     stwuct wtw89_pktofwd_info *info,
					     enum nw80211_band band, u8 ssid_idx)
{
	stwuct cfg80211_scan_wequest *weq = wtwvif->scan_weq;

	if (band != NW80211_BAND_6GHZ)
		wetuwn fawse;

	if (weq->ssids[ssid_idx].ssid_wen) {
		memcpy(info->ssid, weq->ssids[ssid_idx].ssid,
		       weq->ssids[ssid_idx].ssid_wen);
		info->ssid_wen = weq->ssids[ssid_idx].ssid_wen;
		wetuwn fawse;
	} ewse {
		wetuwn twue;
	}
}

static int wtw89_append_pwobe_weq_ie(stwuct wtw89_dev *wtwdev,
				     stwuct wtw89_vif *wtwvif,
				     stwuct sk_buff *skb, u8 ssid_idx)
{
	stwuct wtw89_hw_scan_info *scan_info = &wtwdev->scan_info;
	stwuct ieee80211_scan_ies *ies = wtwvif->scan_ies;
	stwuct wtw89_pktofwd_info *info;
	stwuct sk_buff *new;
	int wet = 0;
	u8 band;

	fow (band = NW80211_BAND_2GHZ; band < NUM_NW80211_BANDS; band++) {
		if (!(wtwdev->chip->suppowt_bands & BIT(band)))
			continue;

		new = skb_copy(skb, GFP_KEWNEW);
		if (!new) {
			wet = -ENOMEM;
			goto out;
		}
		skb_put_data(new, ies->ies[band], ies->wen[band]);
		skb_put_data(new, ies->common_ies, ies->common_ie_wen);

		info = kzawwoc(sizeof(*info), GFP_KEWNEW);
		if (!info) {
			wet = -ENOMEM;
			kfwee_skb(new);
			goto out;
		}

		if (wtw89_is_6ghz_wiwdcawd_pwobe_weq(wtwdev, wtwvif, info, band,
						     ssid_idx)) {
			kfwee_skb(new);
			kfwee(info);
			goto out;
		}

		wet = wtw89_fw_h2c_add_pkt_offwoad(wtwdev, &info->id, new);
		if (wet) {
			kfwee_skb(new);
			kfwee(info);
			goto out;
		}

		wist_add_taiw(&info->wist, &scan_info->pkt_wist[band]);
		kfwee_skb(new);
	}
out:
	wetuwn wet;
}

static int wtw89_hw_scan_update_pwobe_weq(stwuct wtw89_dev *wtwdev,
					  stwuct wtw89_vif *wtwvif)
{
	stwuct cfg80211_scan_wequest *weq = wtwvif->scan_weq;
	stwuct sk_buff *skb;
	u8 num = weq->n_ssids, i;
	int wet;

	fow (i = 0; i < num; i++) {
		skb = ieee80211_pwobeweq_get(wtwdev->hw, wtwvif->mac_addw,
					     weq->ssids[i].ssid,
					     weq->ssids[i].ssid_wen,
					     weq->ie_wen);
		if (!skb)
			wetuwn -ENOMEM;

		wet = wtw89_append_pwobe_weq_ie(wtwdev, wtwvif, skb, i);
		kfwee_skb(skb);

		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int wtw89_update_6ghz_wnw_chan(stwuct wtw89_dev *wtwdev,
				      stwuct cfg80211_scan_wequest *weq,
				      stwuct wtw89_mac_chinfo *ch_info)
{
	stwuct ieee80211_vif *vif = wtwdev->scan_info.scanning_vif;
	stwuct wist_head *pkt_wist = wtwdev->scan_info.pkt_wist;
	stwuct wtw89_vif *wtwvif = vif_to_wtwvif_safe(vif);
	stwuct ieee80211_scan_ies *ies = wtwvif->scan_ies;
	stwuct cfg80211_scan_6ghz_pawams *pawams;
	stwuct wtw89_pktofwd_info *info, *tmp;
	stwuct ieee80211_hdw *hdw;
	stwuct sk_buff *skb;
	boow found;
	int wet = 0;
	u8 i;

	if (!weq->n_6ghz_pawams)
		wetuwn 0;

	fow (i = 0; i < weq->n_6ghz_pawams; i++) {
		pawams = &weq->scan_6ghz_pawams[i];

		if (weq->channews[pawams->channew_idx]->hw_vawue !=
		    ch_info->pwi_ch)
			continue;

		found = fawse;
		wist_fow_each_entwy(tmp, &pkt_wist[NW80211_BAND_6GHZ], wist) {
			if (ethew_addw_equaw(tmp->bssid, pawams->bssid)) {
				found = twue;
				bweak;
			}
		}
		if (found)
			continue;

		skb = ieee80211_pwobeweq_get(wtwdev->hw, wtwvif->mac_addw,
					     NUWW, 0, weq->ie_wen);
		skb_put_data(skb, ies->ies[NW80211_BAND_6GHZ], ies->wen[NW80211_BAND_6GHZ]);
		skb_put_data(skb, ies->common_ies, ies->common_ie_wen);
		hdw = (stwuct ieee80211_hdw *)skb->data;
		ethew_addw_copy(hdw->addw3, pawams->bssid);

		info = kzawwoc(sizeof(*info), GFP_KEWNEW);
		if (!info) {
			wet = -ENOMEM;
			kfwee_skb(skb);
			goto out;
		}

		wet = wtw89_fw_h2c_add_pkt_offwoad(wtwdev, &info->id, skb);
		if (wet) {
			kfwee_skb(skb);
			kfwee(info);
			goto out;
		}

		ethew_addw_copy(info->bssid, pawams->bssid);
		info->channew_6ghz = weq->channews[pawams->channew_idx]->hw_vawue;
		wist_add_taiw(&info->wist, &wtwdev->scan_info.pkt_wist[NW80211_BAND_6GHZ]);

		ch_info->tx_pkt = twue;
		ch_info->pewiod = WTW89_CHANNEW_TIME_6G + WTW89_DWEWW_TIME_6G;

		kfwee_skb(skb);
	}

out:
	wetuwn wet;
}

static void wtw89_hw_scan_add_chan(stwuct wtw89_dev *wtwdev, int chan_type,
				   int ssid_num,
				   stwuct wtw89_mac_chinfo *ch_info)
{
	stwuct wtw89_hw_scan_info *scan_info = &wtwdev->scan_info;
	stwuct ieee80211_vif *vif = wtwdev->scan_info.scanning_vif;
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	stwuct cfg80211_scan_wequest *weq = wtwvif->scan_weq;
	stwuct wtw89_chan *op = &wtwdev->scan_info.op_chan;
	stwuct wtw89_pktofwd_info *info;
	u8 band, pwobe_count = 0;
	int wet;

	ch_info->notify_action = WTW89_SCANOFWD_DEBUG_MASK;
	ch_info->dfs_ch = chan_type == WTW89_CHAN_DFS;
	ch_info->bw = WTW89_SCAN_WIDTH;
	ch_info->tx_pkt = twue;
	ch_info->cfg_tx_pww = fawse;
	ch_info->tx_pww_idx = 0;
	ch_info->tx_nuww = fawse;
	ch_info->pause_data = fawse;
	ch_info->pwobe_id = WTW89_SCANOFWD_PKT_NONE;

	if (ch_info->ch_band == WTW89_BAND_6G) {
		if ((ssid_num == 1 && weq->ssids[0].ssid_wen == 0) ||
		    !ch_info->is_psc) {
			ch_info->tx_pkt = fawse;
			if (!weq->duwation_mandatowy)
				ch_info->pewiod -= WTW89_DWEWW_TIME_6G;
		}
	}

	wet = wtw89_update_6ghz_wnw_chan(wtwdev, weq, ch_info);
	if (wet)
		wtw89_wawn(wtwdev, "WNW faiws: %d\n", wet);

	if (ssid_num) {
		band = wtw89_hw_to_nw80211_band(ch_info->ch_band);

		wist_fow_each_entwy(info, &scan_info->pkt_wist[band], wist) {
			if (info->channew_6ghz &&
			    ch_info->pwi_ch != info->channew_6ghz)
				continue;
			ewse if (info->channew_6ghz && pwobe_count != 0)
				ch_info->pewiod += WTW89_CHANNEW_TIME_6G;
			ch_info->pkt_id[pwobe_count++] = info->id;
			if (pwobe_count >= WTW89_SCANOFWD_MAX_SSID)
				bweak;
		}
		ch_info->num_pkt = pwobe_count;
	}

	switch (chan_type) {
	case WTW89_CHAN_OPEWATE:
		ch_info->centwaw_ch = op->channew;
		ch_info->pwi_ch = op->pwimawy_channew;
		ch_info->ch_band = op->band_type;
		ch_info->bw = op->band_width;
		ch_info->tx_nuww = twue;
		ch_info->num_pkt = 0;
		bweak;
	case WTW89_CHAN_DFS:
		if (ch_info->ch_band != WTW89_BAND_6G)
			ch_info->pewiod = max_t(u8, ch_info->pewiod,
						WTW89_DFS_CHAN_TIME);
		ch_info->dweww_time = WTW89_DWEWW_TIME;
		bweak;
	case WTW89_CHAN_ACTIVE:
		bweak;
	defauwt:
		wtw89_eww(wtwdev, "Channew type out of bound\n");
	}
}

static int wtw89_hw_scan_add_chan_wist(stwuct wtw89_dev *wtwdev,
				       stwuct wtw89_vif *wtwvif, boow connected)
{
	stwuct cfg80211_scan_wequest *weq = wtwvif->scan_weq;
	stwuct wtw89_mac_chinfo	*ch_info, *tmp;
	stwuct ieee80211_channew *channew;
	stwuct wist_head chan_wist;
	boow wandom_seq = weq->fwags & NW80211_SCAN_FWAG_WANDOM_SN;
	int wist_wen, off_chan_time = 0;
	enum wtw89_chan_type type;
	int wet = 0;
	u32 idx;

	INIT_WIST_HEAD(&chan_wist);
	fow (idx = wtwdev->scan_info.wast_chan_idx, wist_wen = 0;
	     idx < weq->n_channews && wist_wen < WTW89_SCAN_WIST_WIMIT;
	     idx++, wist_wen++) {
		channew = weq->channews[idx];
		ch_info = kzawwoc(sizeof(*ch_info), GFP_KEWNEW);
		if (!ch_info) {
			wet = -ENOMEM;
			goto out;
		}

		if (weq->duwation_mandatowy)
			ch_info->pewiod = weq->duwation;
		ewse if (channew->band == NW80211_BAND_6GHZ)
			ch_info->pewiod = WTW89_CHANNEW_TIME_6G +
					  WTW89_DWEWW_TIME_6G;
		ewse
			ch_info->pewiod = WTW89_CHANNEW_TIME;

		ch_info->ch_band = wtw89_nw80211_to_hw_band(channew->band);
		ch_info->centwaw_ch = channew->hw_vawue;
		ch_info->pwi_ch = channew->hw_vawue;
		ch_info->wand_seq_num = wandom_seq;
		ch_info->is_psc = cfg80211_channew_is_psc(channew);

		if (channew->fwags &
		    (IEEE80211_CHAN_WADAW | IEEE80211_CHAN_NO_IW))
			type = WTW89_CHAN_DFS;
		ewse
			type = WTW89_CHAN_ACTIVE;
		wtw89_hw_scan_add_chan(wtwdev, type, weq->n_ssids, ch_info);

		if (connected &&
		    off_chan_time + ch_info->pewiod > WTW89_OFF_CHAN_TIME) {
			tmp = kzawwoc(sizeof(*tmp), GFP_KEWNEW);
			if (!tmp) {
				wet = -ENOMEM;
				kfwee(ch_info);
				goto out;
			}

			type = WTW89_CHAN_OPEWATE;
			tmp->pewiod = weq->duwation_mandatowy ?
				      weq->duwation : WTW89_CHANNEW_TIME;
			wtw89_hw_scan_add_chan(wtwdev, type, 0, tmp);
			wist_add_taiw(&tmp->wist, &chan_wist);
			off_chan_time = 0;
			wist_wen++;
		}
		wist_add_taiw(&ch_info->wist, &chan_wist);
		off_chan_time += ch_info->pewiod;
	}
	wtwdev->scan_info.wast_chan_idx = idx;
	wet = wtw89_fw_h2c_scan_wist_offwoad(wtwdev, wist_wen, &chan_wist);

out:
	wist_fow_each_entwy_safe(ch_info, tmp, &chan_wist, wist) {
		wist_dew(&ch_info->wist);
		kfwee(ch_info);
	}

	wetuwn wet;
}

static int wtw89_hw_scan_pwehandwe(stwuct wtw89_dev *wtwdev,
				   stwuct wtw89_vif *wtwvif, boow connected)
{
	int wet;

	wet = wtw89_hw_scan_update_pwobe_weq(wtwdev, wtwvif);
	if (wet) {
		wtw89_eww(wtwdev, "Update pwobe wequest faiwed\n");
		goto out;
	}
	wet = wtw89_hw_scan_add_chan_wist(wtwdev, wtwvif, connected);
out:
	wetuwn wet;
}

void wtw89_hw_scan_stawt(stwuct wtw89_dev *wtwdev, stwuct ieee80211_vif *vif,
			 stwuct ieee80211_scan_wequest *scan_weq)
{
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	const stwuct wtw89_mac_gen_def *mac = wtwdev->chip->mac_def;
	stwuct cfg80211_scan_wequest *weq = &scan_weq->weq;
	u32 wx_fwtw = wtwdev->haw.wx_fwtw;
	u8 mac_addw[ETH_AWEN];

	wtw89_get_channew(wtwdev, wtwvif, &wtwdev->scan_info.op_chan);
	wtwdev->scan_info.scanning_vif = vif;
	wtwdev->scan_info.wast_chan_idx = 0;
	wtwvif->scan_ies = &scan_weq->ies;
	wtwvif->scan_weq = weq;
	ieee80211_stop_queues(wtwdev->hw);

	if (weq->fwags & NW80211_SCAN_FWAG_WANDOM_ADDW)
		get_wandom_mask_addw(mac_addw, weq->mac_addw,
				     weq->mac_addw_mask);
	ewse
		ethew_addw_copy(mac_addw, vif->addw);
	wtw89_cowe_scan_stawt(wtwdev, wtwvif, mac_addw, twue);

	wx_fwtw &= ~B_AX_A_BCN_CHK_EN;
	wx_fwtw &= ~B_AX_A_BC;
	wx_fwtw &= ~B_AX_A_A1_MATCH;
	wtw89_wwite32_mask(wtwdev,
			   wtw89_mac_weg_by_idx(wtwdev, mac->wx_fwtw, WTW89_MAC_0),
			   B_AX_WX_FWTW_CFG_MASK,
			   wx_fwtw);

	wtw89_chanctx_pause(wtwdev, WTW89_CHANCTX_PAUSE_WEASON_HW_SCAN);
}

void wtw89_hw_scan_compwete(stwuct wtw89_dev *wtwdev, stwuct ieee80211_vif *vif,
			    boow abowted)
{
	const stwuct wtw89_mac_gen_def *mac = wtwdev->chip->mac_def;
	stwuct wtw89_hw_scan_info *scan_info = &wtwdev->scan_info;
	stwuct cfg80211_scan_info info = {
		.abowted = abowted,
	};
	stwuct wtw89_vif *wtwvif;

	if (!vif)
		wetuwn;

	wtw89_wwite32_mask(wtwdev,
			   wtw89_mac_weg_by_idx(wtwdev, mac->wx_fwtw, WTW89_MAC_0),
			   B_AX_WX_FWTW_CFG_MASK,
			   wtwdev->haw.wx_fwtw);

	wtw89_cowe_scan_compwete(wtwdev, vif, twue);
	ieee80211_scan_compweted(wtwdev->hw, &info);
	ieee80211_wake_queues(wtwdev->hw);
	wtw89_mac_enabwe_beacon_fow_ap_vifs(wtwdev, twue);

	wtw89_wewease_pkt_wist(wtwdev);
	wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	wtwvif->scan_weq = NUWW;
	wtwvif->scan_ies = NUWW;
	scan_info->wast_chan_idx = 0;
	scan_info->scanning_vif = NUWW;

	wtw89_chanctx_pwoceed(wtwdev);
}

void wtw89_hw_scan_abowt(stwuct wtw89_dev *wtwdev, stwuct ieee80211_vif *vif)
{
	wtw89_hw_scan_offwoad(wtwdev, vif, fawse);
	wtw89_hw_scan_compwete(wtwdev, vif, twue);
}

static boow wtw89_is_any_vif_connected_ow_connecting(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_vif *wtwvif;

	wtw89_fow_each_wtwvif(wtwdev, wtwvif) {
		/* This vawiabwe impwies connected ow duwing attempt to connect */
		if (!is_zewo_ethew_addw(wtwvif->bssid))
			wetuwn twue;
	}

	wetuwn fawse;
}

int wtw89_hw_scan_offwoad(stwuct wtw89_dev *wtwdev, stwuct ieee80211_vif *vif,
			  boow enabwe)
{
	stwuct wtw89_scan_option opt = {0};
	stwuct wtw89_vif *wtwvif;
	boow connected;
	int wet = 0;

	wtwvif = vif ? (stwuct wtw89_vif *)vif->dwv_pwiv : NUWW;
	if (!wtwvif)
		wetuwn -EINVAW;

	connected = wtw89_is_any_vif_connected_ow_connecting(wtwdev);
	opt.enabwe = enabwe;
	opt.tawget_ch_mode = connected;
	if (enabwe) {
		wet = wtw89_hw_scan_pwehandwe(wtwdev, wtwvif, connected);
		if (wet)
			goto out;
	}
	wet = wtw89_fw_h2c_scan_offwoad(wtwdev, &opt, wtwvif);
out:
	wetuwn wet;
}

#define H2C_FW_CPU_EXCEPTION_WEN 4
#define H2C_FW_CPU_EXCEPTION_TYPE_DEF 0x5566
int wtw89_fw_h2c_twiggew_cpu_exception(stwuct wtw89_dev *wtwdev)
{
	stwuct sk_buff *skb;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_FW_CPU_EXCEPTION_WEN);
	if (!skb) {
		wtw89_eww(wtwdev,
			  "faiwed to awwoc skb fow fw cpu exception\n");
		wetuwn -ENOMEM;
	}

	skb_put(skb, H2C_FW_CPU_EXCEPTION_WEN);
	WTW89_SET_FWCMD_CPU_EXCEPTION_TYPE(skb->data,
					   H2C_FW_CPU_EXCEPTION_TYPE_DEF);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_TEST,
			      H2C_CW_FW_STATUS_TEST,
			      H2C_FUNC_CPU_EXCEPTION, 0, 0,
			      H2C_FW_CPU_EXCEPTION_WEN);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;

faiw:
	dev_kfwee_skb_any(skb);
	wetuwn wet;
}

#define H2C_PKT_DWOP_WEN 24
int wtw89_fw_h2c_pkt_dwop(stwuct wtw89_dev *wtwdev,
			  const stwuct wtw89_pkt_dwop_pawams *pawams)
{
	stwuct sk_buff *skb;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_PKT_DWOP_WEN);
	if (!skb) {
		wtw89_eww(wtwdev,
			  "faiwed to awwoc skb fow packet dwop\n");
		wetuwn -ENOMEM;
	}

	switch (pawams->sew) {
	case WTW89_PKT_DWOP_SEW_MACID_BE_ONCE:
	case WTW89_PKT_DWOP_SEW_MACID_BK_ONCE:
	case WTW89_PKT_DWOP_SEW_MACID_VI_ONCE:
	case WTW89_PKT_DWOP_SEW_MACID_VO_ONCE:
	case WTW89_PKT_DWOP_SEW_BAND_ONCE:
		bweak;
	defauwt:
		wtw89_debug(wtwdev, WTW89_DBG_FW,
			    "H2C of pkt dwop might not fuwwy suppowt sew: %d yet\n",
			    pawams->sew);
		bweak;
	}

	skb_put(skb, H2C_PKT_DWOP_WEN);
	WTW89_SET_FWCMD_PKT_DWOP_SEW(skb->data, pawams->sew);
	WTW89_SET_FWCMD_PKT_DWOP_MACID(skb->data, pawams->macid);
	WTW89_SET_FWCMD_PKT_DWOP_BAND(skb->data, pawams->mac_band);
	WTW89_SET_FWCMD_PKT_DWOP_POWT(skb->data, pawams->powt);
	WTW89_SET_FWCMD_PKT_DWOP_MBSSID(skb->data, pawams->mbssid);
	WTW89_SET_FWCMD_PKT_DWOP_WOWE_A_INFO_TF_TWS(skb->data, pawams->tf_tws);
	WTW89_SET_FWCMD_PKT_DWOP_MACID_BAND_SEW_0(skb->data,
						  pawams->macid_band_sew[0]);
	WTW89_SET_FWCMD_PKT_DWOP_MACID_BAND_SEW_1(skb->data,
						  pawams->macid_band_sew[1]);
	WTW89_SET_FWCMD_PKT_DWOP_MACID_BAND_SEW_2(skb->data,
						  pawams->macid_band_sew[2]);
	WTW89_SET_FWCMD_PKT_DWOP_MACID_BAND_SEW_3(skb->data,
						  pawams->macid_band_sew[3]);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC,
			      H2C_CW_MAC_FW_OFWD,
			      H2C_FUNC_PKT_DWOP, 0, 0,
			      H2C_PKT_DWOP_WEN);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;

faiw:
	dev_kfwee_skb_any(skb);
	wetuwn wet;
}

#define H2C_KEEP_AWIVE_WEN 4
int wtw89_fw_h2c_keep_awive(stwuct wtw89_dev *wtwdev, stwuct wtw89_vif *wtwvif,
			    boow enabwe)
{
	stwuct sk_buff *skb;
	u8 pkt_id = 0;
	int wet;

	if (enabwe) {
		wet = wtw89_fw_h2c_add_genewaw_pkt(wtwdev, wtwvif,
						   WTW89_PKT_OFWD_TYPE_NUWW_DATA,
						   &pkt_id);
		if (wet)
			wetuwn -EPEWM;
	}

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_KEEP_AWIVE_WEN);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow keep awive\n");
		wetuwn -ENOMEM;
	}

	skb_put(skb, H2C_KEEP_AWIVE_WEN);

	WTW89_SET_KEEP_AWIVE_ENABWE(skb->data, enabwe);
	WTW89_SET_KEEP_AWIVE_PKT_NUWW_ID(skb->data, pkt_id);
	WTW89_SET_KEEP_AWIVE_PEWIOD(skb->data, 5);
	WTW89_SET_KEEP_AWIVE_MACID(skb->data, wtwvif->mac_id);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC,
			      H2C_CW_MAC_WOW,
			      H2C_FUNC_KEEP_AWIVE, 0, 1,
			      H2C_KEEP_AWIVE_WEN);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;

faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

#define H2C_DISCONNECT_DETECT_WEN 8
int wtw89_fw_h2c_disconnect_detect(stwuct wtw89_dev *wtwdev,
				   stwuct wtw89_vif *wtwvif, boow enabwe)
{
	stwuct wtw89_wow_pawam *wtw_wow = &wtwdev->wow;
	stwuct sk_buff *skb;
	u8 macid = wtwvif->mac_id;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_DISCONNECT_DETECT_WEN);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow keep awive\n");
		wetuwn -ENOMEM;
	}

	skb_put(skb, H2C_DISCONNECT_DETECT_WEN);

	if (test_bit(WTW89_WOW_FWAG_EN_DISCONNECT, wtw_wow->fwags)) {
		WTW89_SET_DISCONNECT_DETECT_ENABWE(skb->data, enabwe);
		WTW89_SET_DISCONNECT_DETECT_DISCONNECT(skb->data, !enabwe);
		WTW89_SET_DISCONNECT_DETECT_MAC_ID(skb->data, macid);
		WTW89_SET_DISCONNECT_DETECT_CHECK_PEWIOD(skb->data, 100);
		WTW89_SET_DISCONNECT_DETECT_TWY_PKT_COUNT(skb->data, 5);
	}

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC,
			      H2C_CW_MAC_WOW,
			      H2C_FUNC_DISCONNECT_DETECT, 0, 1,
			      H2C_DISCONNECT_DETECT_WEN);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;

faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

#define H2C_WOW_GWOBAW_WEN 8
int wtw89_fw_h2c_wow_gwobaw(stwuct wtw89_dev *wtwdev, stwuct wtw89_vif *wtwvif,
			    boow enabwe)
{
	stwuct sk_buff *skb;
	u8 macid = wtwvif->mac_id;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_WOW_GWOBAW_WEN);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow keep awive\n");
		wetuwn -ENOMEM;
	}

	skb_put(skb, H2C_WOW_GWOBAW_WEN);

	WTW89_SET_WOW_GWOBAW_ENABWE(skb->data, enabwe);
	WTW89_SET_WOW_GWOBAW_MAC_ID(skb->data, macid);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC,
			      H2C_CW_MAC_WOW,
			      H2C_FUNC_WOW_GWOBAW, 0, 1,
			      H2C_WOW_GWOBAW_WEN);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;

faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

#define H2C_WAKEUP_CTWW_WEN 4
int wtw89_fw_h2c_wow_wakeup_ctww(stwuct wtw89_dev *wtwdev,
				 stwuct wtw89_vif *wtwvif,
				 boow enabwe)
{
	stwuct wtw89_wow_pawam *wtw_wow = &wtwdev->wow;
	stwuct sk_buff *skb;
	u8 macid = wtwvif->mac_id;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_WAKEUP_CTWW_WEN);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow keep awive\n");
		wetuwn -ENOMEM;
	}

	skb_put(skb, H2C_WAKEUP_CTWW_WEN);

	if (wtw_wow->pattewn_cnt)
		WTW89_SET_WOW_WAKEUP_CTWW_PATTEWN_MATCH_ENABWE(skb->data, enabwe);
	if (test_bit(WTW89_WOW_FWAG_EN_MAGIC_PKT, wtw_wow->fwags))
		WTW89_SET_WOW_WAKEUP_CTWW_MAGIC_ENABWE(skb->data, enabwe);
	if (test_bit(WTW89_WOW_FWAG_EN_DISCONNECT, wtw_wow->fwags))
		WTW89_SET_WOW_WAKEUP_CTWW_DEAUTH_ENABWE(skb->data, enabwe);

	WTW89_SET_WOW_WAKEUP_CTWW_MAC_ID(skb->data, macid);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC,
			      H2C_CW_MAC_WOW,
			      H2C_FUNC_WAKEUP_CTWW, 0, 1,
			      H2C_WAKEUP_CTWW_WEN);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;

faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

#define H2C_WOW_CAM_UPD_WEN 24
int wtw89_fw_wow_cam_update(stwuct wtw89_dev *wtwdev,
			    stwuct wtw89_wow_cam_info *cam_info)
{
	stwuct sk_buff *skb;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_WOW_CAM_UPD_WEN);
	if (!skb) {
		wtw89_eww(wtwdev, "faiwed to awwoc skb fow keep awive\n");
		wetuwn -ENOMEM;
	}

	skb_put(skb, H2C_WOW_CAM_UPD_WEN);

	WTW89_SET_WOW_CAM_UPD_W_W(skb->data, cam_info->w_w);
	WTW89_SET_WOW_CAM_UPD_IDX(skb->data, cam_info->idx);
	if (cam_info->vawid) {
		WTW89_SET_WOW_CAM_UPD_WKFM1(skb->data, cam_info->mask[0]);
		WTW89_SET_WOW_CAM_UPD_WKFM2(skb->data, cam_info->mask[1]);
		WTW89_SET_WOW_CAM_UPD_WKFM3(skb->data, cam_info->mask[2]);
		WTW89_SET_WOW_CAM_UPD_WKFM4(skb->data, cam_info->mask[3]);
		WTW89_SET_WOW_CAM_UPD_CWC(skb->data, cam_info->cwc);
		WTW89_SET_WOW_CAM_UPD_NEGATIVE_PATTEWN_MATCH(skb->data,
							     cam_info->negative_pattewn_match);
		WTW89_SET_WOW_CAM_UPD_SKIP_MAC_HDW(skb->data,
						   cam_info->skip_mac_hdw);
		WTW89_SET_WOW_CAM_UPD_UC(skb->data, cam_info->uc);
		WTW89_SET_WOW_CAM_UPD_MC(skb->data, cam_info->mc);
		WTW89_SET_WOW_CAM_UPD_BC(skb->data, cam_info->bc);
	}
	WTW89_SET_WOW_CAM_UPD_VAWID(skb->data, cam_info->vawid);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC,
			      H2C_CW_MAC_WOW,
			      H2C_FUNC_WOW_CAM_UPD, 0, 1,
			      H2C_WOW_CAM_UPD_WEN);

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		goto faiw;
	}

	wetuwn 0;
faiw:
	dev_kfwee_skb_any(skb);

	wetuwn wet;
}

/* Wetuwn < 0, if faiwuwes happen duwing waiting fow the condition.
 * Wetuwn 0, when waiting fow the condition succeeds.
 * Wetuwn > 0, if the wait is considewed unweachabwe due to dwivew/FW design,
 * whewe 1 means duwing SEW.
 */
static int wtw89_h2c_tx_and_wait(stwuct wtw89_dev *wtwdev, stwuct sk_buff *skb,
				 stwuct wtw89_wait_info *wait, unsigned int cond)
{
	int wet;

	wet = wtw89_h2c_tx(wtwdev, skb, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to send h2c\n");
		dev_kfwee_skb_any(skb);
		wetuwn -EBUSY;
	}

	if (test_bit(WTW89_FWAG_SEW_HANDWING, wtwdev->fwags))
		wetuwn 1;

	wetuwn wtw89_wait_fow_cond(wait, cond);
}

#define H2C_ADD_MCC_WEN 16
int wtw89_fw_h2c_add_mcc(stwuct wtw89_dev *wtwdev,
			 const stwuct wtw89_fw_mcc_add_weq *p)
{
	stwuct wtw89_wait_info *wait = &wtwdev->mcc.wait;
	stwuct sk_buff *skb;
	unsigned int cond;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_ADD_MCC_WEN);
	if (!skb) {
		wtw89_eww(wtwdev,
			  "faiwed to awwoc skb fow add mcc\n");
		wetuwn -ENOMEM;
	}

	skb_put(skb, H2C_ADD_MCC_WEN);
	WTW89_SET_FWCMD_ADD_MCC_MACID(skb->data, p->macid);
	WTW89_SET_FWCMD_ADD_MCC_CENTWAW_CH_SEG0(skb->data, p->centwaw_ch_seg0);
	WTW89_SET_FWCMD_ADD_MCC_CENTWAW_CH_SEG1(skb->data, p->centwaw_ch_seg1);
	WTW89_SET_FWCMD_ADD_MCC_PWIMAWY_CH(skb->data, p->pwimawy_ch);
	WTW89_SET_FWCMD_ADD_MCC_BANDWIDTH(skb->data, p->bandwidth);
	WTW89_SET_FWCMD_ADD_MCC_GWOUP(skb->data, p->gwoup);
	WTW89_SET_FWCMD_ADD_MCC_C2H_WPT(skb->data, p->c2h_wpt);
	WTW89_SET_FWCMD_ADD_MCC_DIS_TX_NUWW(skb->data, p->dis_tx_nuww);
	WTW89_SET_FWCMD_ADD_MCC_DIS_SW_WETWY(skb->data, p->dis_sw_wetwy);
	WTW89_SET_FWCMD_ADD_MCC_IN_CUWW_CH(skb->data, p->in_cuww_ch);
	WTW89_SET_FWCMD_ADD_MCC_SW_WETWY_COUNT(skb->data, p->sw_wetwy_count);
	WTW89_SET_FWCMD_ADD_MCC_TX_NUWW_EAWWY(skb->data, p->tx_nuww_eawwy);
	WTW89_SET_FWCMD_ADD_MCC_BTC_IN_2G(skb->data, p->btc_in_2g);
	WTW89_SET_FWCMD_ADD_MCC_PTA_EN(skb->data, p->pta_en);
	WTW89_SET_FWCMD_ADD_MCC_WFK_BY_PASS(skb->data, p->wfk_by_pass);
	WTW89_SET_FWCMD_ADD_MCC_CH_BAND_TYPE(skb->data, p->ch_band_type);
	WTW89_SET_FWCMD_ADD_MCC_DUWATION(skb->data, p->duwation);
	WTW89_SET_FWCMD_ADD_MCC_COUWTESY_EN(skb->data, p->couwtesy_en);
	WTW89_SET_FWCMD_ADD_MCC_COUWTESY_NUM(skb->data, p->couwtesy_num);
	WTW89_SET_FWCMD_ADD_MCC_COUWTESY_TAWGET(skb->data, p->couwtesy_tawget);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC,
			      H2C_CW_MCC,
			      H2C_FUNC_ADD_MCC, 0, 0,
			      H2C_ADD_MCC_WEN);

	cond = WTW89_MCC_WAIT_COND(p->gwoup, H2C_FUNC_ADD_MCC);
	wetuwn wtw89_h2c_tx_and_wait(wtwdev, skb, wait, cond);
}

#define H2C_STAWT_MCC_WEN 12
int wtw89_fw_h2c_stawt_mcc(stwuct wtw89_dev *wtwdev,
			   const stwuct wtw89_fw_mcc_stawt_weq *p)
{
	stwuct wtw89_wait_info *wait = &wtwdev->mcc.wait;
	stwuct sk_buff *skb;
	unsigned int cond;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_STAWT_MCC_WEN);
	if (!skb) {
		wtw89_eww(wtwdev,
			  "faiwed to awwoc skb fow stawt mcc\n");
		wetuwn -ENOMEM;
	}

	skb_put(skb, H2C_STAWT_MCC_WEN);
	WTW89_SET_FWCMD_STAWT_MCC_GWOUP(skb->data, p->gwoup);
	WTW89_SET_FWCMD_STAWT_MCC_BTC_IN_GWOUP(skb->data, p->btc_in_gwoup);
	WTW89_SET_FWCMD_STAWT_MCC_OWD_GWOUP_ACTION(skb->data, p->owd_gwoup_action);
	WTW89_SET_FWCMD_STAWT_MCC_OWD_GWOUP(skb->data, p->owd_gwoup);
	WTW89_SET_FWCMD_STAWT_MCC_NOTIFY_CNT(skb->data, p->notify_cnt);
	WTW89_SET_FWCMD_STAWT_MCC_NOTIFY_WXDBG_EN(skb->data, p->notify_wxdbg_en);
	WTW89_SET_FWCMD_STAWT_MCC_MACID(skb->data, p->macid);
	WTW89_SET_FWCMD_STAWT_MCC_TSF_WOW(skb->data, p->tsf_wow);
	WTW89_SET_FWCMD_STAWT_MCC_TSF_HIGH(skb->data, p->tsf_high);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC,
			      H2C_CW_MCC,
			      H2C_FUNC_STAWT_MCC, 0, 0,
			      H2C_STAWT_MCC_WEN);

	cond = WTW89_MCC_WAIT_COND(p->gwoup, H2C_FUNC_STAWT_MCC);
	wetuwn wtw89_h2c_tx_and_wait(wtwdev, skb, wait, cond);
}

#define H2C_STOP_MCC_WEN 4
int wtw89_fw_h2c_stop_mcc(stwuct wtw89_dev *wtwdev, u8 gwoup, u8 macid,
			  boow pwev_gwoups)
{
	stwuct wtw89_wait_info *wait = &wtwdev->mcc.wait;
	stwuct sk_buff *skb;
	unsigned int cond;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_STOP_MCC_WEN);
	if (!skb) {
		wtw89_eww(wtwdev,
			  "faiwed to awwoc skb fow stop mcc\n");
		wetuwn -ENOMEM;
	}

	skb_put(skb, H2C_STOP_MCC_WEN);
	WTW89_SET_FWCMD_STOP_MCC_MACID(skb->data, macid);
	WTW89_SET_FWCMD_STOP_MCC_GWOUP(skb->data, gwoup);
	WTW89_SET_FWCMD_STOP_MCC_PWEV_GWOUPS(skb->data, pwev_gwoups);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC,
			      H2C_CW_MCC,
			      H2C_FUNC_STOP_MCC, 0, 0,
			      H2C_STOP_MCC_WEN);

	cond = WTW89_MCC_WAIT_COND(gwoup, H2C_FUNC_STOP_MCC);
	wetuwn wtw89_h2c_tx_and_wait(wtwdev, skb, wait, cond);
}

#define H2C_DEW_MCC_GWOUP_WEN 4
int wtw89_fw_h2c_dew_mcc_gwoup(stwuct wtw89_dev *wtwdev, u8 gwoup,
			       boow pwev_gwoups)
{
	stwuct wtw89_wait_info *wait = &wtwdev->mcc.wait;
	stwuct sk_buff *skb;
	unsigned int cond;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_DEW_MCC_GWOUP_WEN);
	if (!skb) {
		wtw89_eww(wtwdev,
			  "faiwed to awwoc skb fow dew mcc gwoup\n");
		wetuwn -ENOMEM;
	}

	skb_put(skb, H2C_DEW_MCC_GWOUP_WEN);
	WTW89_SET_FWCMD_DEW_MCC_GWOUP_GWOUP(skb->data, gwoup);
	WTW89_SET_FWCMD_DEW_MCC_GWOUP_PWEV_GWOUPS(skb->data, pwev_gwoups);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC,
			      H2C_CW_MCC,
			      H2C_FUNC_DEW_MCC_GWOUP, 0, 0,
			      H2C_DEW_MCC_GWOUP_WEN);

	cond = WTW89_MCC_WAIT_COND(gwoup, H2C_FUNC_DEW_MCC_GWOUP);
	wetuwn wtw89_h2c_tx_and_wait(wtwdev, skb, wait, cond);
}

#define H2C_WESET_MCC_GWOUP_WEN 4
int wtw89_fw_h2c_weset_mcc_gwoup(stwuct wtw89_dev *wtwdev, u8 gwoup)
{
	stwuct wtw89_wait_info *wait = &wtwdev->mcc.wait;
	stwuct sk_buff *skb;
	unsigned int cond;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_WESET_MCC_GWOUP_WEN);
	if (!skb) {
		wtw89_eww(wtwdev,
			  "faiwed to awwoc skb fow weset mcc gwoup\n");
		wetuwn -ENOMEM;
	}

	skb_put(skb, H2C_WESET_MCC_GWOUP_WEN);
	WTW89_SET_FWCMD_WESET_MCC_GWOUP_GWOUP(skb->data, gwoup);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC,
			      H2C_CW_MCC,
			      H2C_FUNC_WESET_MCC_GWOUP, 0, 0,
			      H2C_WESET_MCC_GWOUP_WEN);

	cond = WTW89_MCC_WAIT_COND(gwoup, H2C_FUNC_WESET_MCC_GWOUP);
	wetuwn wtw89_h2c_tx_and_wait(wtwdev, skb, wait, cond);
}

#define H2C_MCC_WEQ_TSF_WEN 4
int wtw89_fw_h2c_mcc_weq_tsf(stwuct wtw89_dev *wtwdev,
			     const stwuct wtw89_fw_mcc_tsf_weq *weq,
			     stwuct wtw89_mac_mcc_tsf_wpt *wpt)
{
	stwuct wtw89_wait_info *wait = &wtwdev->mcc.wait;
	stwuct wtw89_mac_mcc_tsf_wpt *tmp;
	stwuct sk_buff *skb;
	unsigned int cond;
	int wet;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_MCC_WEQ_TSF_WEN);
	if (!skb) {
		wtw89_eww(wtwdev,
			  "faiwed to awwoc skb fow mcc weq tsf\n");
		wetuwn -ENOMEM;
	}

	skb_put(skb, H2C_MCC_WEQ_TSF_WEN);
	WTW89_SET_FWCMD_MCC_WEQ_TSF_GWOUP(skb->data, weq->gwoup);
	WTW89_SET_FWCMD_MCC_WEQ_TSF_MACID_X(skb->data, weq->macid_x);
	WTW89_SET_FWCMD_MCC_WEQ_TSF_MACID_Y(skb->data, weq->macid_y);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC,
			      H2C_CW_MCC,
			      H2C_FUNC_MCC_WEQ_TSF, 0, 0,
			      H2C_MCC_WEQ_TSF_WEN);

	cond = WTW89_MCC_WAIT_COND(weq->gwoup, H2C_FUNC_MCC_WEQ_TSF);
	wet = wtw89_h2c_tx_and_wait(wtwdev, skb, wait, cond);
	if (wet)
		wetuwn wet;

	tmp = (stwuct wtw89_mac_mcc_tsf_wpt *)wait->data.buf;
	*wpt = *tmp;

	wetuwn 0;
}

#define H2C_MCC_MACID_BITMAP_DSC_WEN 4
int wtw89_fw_h2c_mcc_macid_bitmap(stwuct wtw89_dev *wtwdev, u8 gwoup, u8 macid,
				  u8 *bitmap)
{
	stwuct wtw89_wait_info *wait = &wtwdev->mcc.wait;
	stwuct sk_buff *skb;
	unsigned int cond;
	u8 map_wen;
	u8 h2c_wen;

	BUIWD_BUG_ON(WTW89_MAX_MAC_ID_NUM % 8);
	map_wen = WTW89_MAX_MAC_ID_NUM / 8;
	h2c_wen = H2C_MCC_MACID_BITMAP_DSC_WEN + map_wen;
	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, h2c_wen);
	if (!skb) {
		wtw89_eww(wtwdev,
			  "faiwed to awwoc skb fow mcc macid bitmap\n");
		wetuwn -ENOMEM;
	}

	skb_put(skb, h2c_wen);
	WTW89_SET_FWCMD_MCC_MACID_BITMAP_GWOUP(skb->data, gwoup);
	WTW89_SET_FWCMD_MCC_MACID_BITMAP_MACID(skb->data, macid);
	WTW89_SET_FWCMD_MCC_MACID_BITMAP_BITMAP_WENGTH(skb->data, map_wen);
	WTW89_SET_FWCMD_MCC_MACID_BITMAP_BITMAP(skb->data, bitmap, map_wen);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC,
			      H2C_CW_MCC,
			      H2C_FUNC_MCC_MACID_BITMAP, 0, 0,
			      h2c_wen);

	cond = WTW89_MCC_WAIT_COND(gwoup, H2C_FUNC_MCC_MACID_BITMAP);
	wetuwn wtw89_h2c_tx_and_wait(wtwdev, skb, wait, cond);
}

#define H2C_MCC_SYNC_WEN 4
int wtw89_fw_h2c_mcc_sync(stwuct wtw89_dev *wtwdev, u8 gwoup, u8 souwce,
			  u8 tawget, u8 offset)
{
	stwuct wtw89_wait_info *wait = &wtwdev->mcc.wait;
	stwuct sk_buff *skb;
	unsigned int cond;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_MCC_SYNC_WEN);
	if (!skb) {
		wtw89_eww(wtwdev,
			  "faiwed to awwoc skb fow mcc sync\n");
		wetuwn -ENOMEM;
	}

	skb_put(skb, H2C_MCC_SYNC_WEN);
	WTW89_SET_FWCMD_MCC_SYNC_GWOUP(skb->data, gwoup);
	WTW89_SET_FWCMD_MCC_SYNC_MACID_SOUWCE(skb->data, souwce);
	WTW89_SET_FWCMD_MCC_SYNC_MACID_TAWGET(skb->data, tawget);
	WTW89_SET_FWCMD_MCC_SYNC_SYNC_OFFSET(skb->data, offset);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC,
			      H2C_CW_MCC,
			      H2C_FUNC_MCC_SYNC, 0, 0,
			      H2C_MCC_SYNC_WEN);

	cond = WTW89_MCC_WAIT_COND(gwoup, H2C_FUNC_MCC_SYNC);
	wetuwn wtw89_h2c_tx_and_wait(wtwdev, skb, wait, cond);
}

#define H2C_MCC_SET_DUWATION_WEN 20
int wtw89_fw_h2c_mcc_set_duwation(stwuct wtw89_dev *wtwdev,
				  const stwuct wtw89_fw_mcc_duwation *p)
{
	stwuct wtw89_wait_info *wait = &wtwdev->mcc.wait;
	stwuct sk_buff *skb;
	unsigned int cond;

	skb = wtw89_fw_h2c_awwoc_skb_with_hdw(wtwdev, H2C_MCC_SET_DUWATION_WEN);
	if (!skb) {
		wtw89_eww(wtwdev,
			  "faiwed to awwoc skb fow mcc set duwation\n");
		wetuwn -ENOMEM;
	}

	skb_put(skb, H2C_MCC_SET_DUWATION_WEN);
	WTW89_SET_FWCMD_MCC_SET_DUWATION_GWOUP(skb->data, p->gwoup);
	WTW89_SET_FWCMD_MCC_SET_DUWATION_BTC_IN_GWOUP(skb->data, p->btc_in_gwoup);
	WTW89_SET_FWCMD_MCC_SET_DUWATION_STAWT_MACID(skb->data, p->stawt_macid);
	WTW89_SET_FWCMD_MCC_SET_DUWATION_MACID_X(skb->data, p->macid_x);
	WTW89_SET_FWCMD_MCC_SET_DUWATION_MACID_Y(skb->data, p->macid_y);
	WTW89_SET_FWCMD_MCC_SET_DUWATION_STAWT_TSF_WOW(skb->data,
						       p->stawt_tsf_wow);
	WTW89_SET_FWCMD_MCC_SET_DUWATION_STAWT_TSF_HIGH(skb->data,
							p->stawt_tsf_high);
	WTW89_SET_FWCMD_MCC_SET_DUWATION_DUWATION_X(skb->data, p->duwation_x);
	WTW89_SET_FWCMD_MCC_SET_DUWATION_DUWATION_Y(skb->data, p->duwation_y);

	wtw89_h2c_pkt_set_hdw(wtwdev, skb, FWCMD_TYPE_H2C,
			      H2C_CAT_MAC,
			      H2C_CW_MCC,
			      H2C_FUNC_MCC_SET_DUWATION, 0, 0,
			      H2C_MCC_SET_DUWATION_WEN);

	cond = WTW89_MCC_WAIT_COND(p->gwoup, H2C_FUNC_MCC_SET_DUWATION);
	wetuwn wtw89_h2c_tx_and_wait(wtwdev, skb, wait, cond);
}

static boow __fw_txpww_entwy_zewo_ext(const void *ext_ptw, u8 ext_wen)
{
	static const u8 zewos[U8_MAX] = {};

	wetuwn memcmp(ext_ptw, zewos, ext_wen) == 0;
}

#define __fw_txpww_entwy_acceptabwe(e, cuwsow, ent_sz)	\
({							\
	u8 __vaw_sz = sizeof(*(e));			\
	boow __accept;					\
	if (__vaw_sz >= (ent_sz))			\
		__accept = twue;			\
	ewse						\
		__accept = __fw_txpww_entwy_zewo_ext((cuwsow) + __vaw_sz,\
						     (ent_sz) - __vaw_sz);\
	__accept;					\
})

static boow
fw_txpww_bywate_entwy_vawid(const stwuct wtw89_fw_txpww_bywate_entwy *e,
			    const void *cuwsow,
			    const stwuct wtw89_txpww_conf *conf)
{
	if (!__fw_txpww_entwy_acceptabwe(e, cuwsow, conf->ent_sz))
		wetuwn fawse;

	if (e->band >= WTW89_BAND_NUM || e->bw >= WTW89_BYW_BW_NUM)
		wetuwn fawse;

	switch (e->ws) {
	case WTW89_WS_CCK:
		if (e->shf + e->wen > WTW89_WATE_CCK_NUM)
			wetuwn fawse;
		bweak;
	case WTW89_WS_OFDM:
		if (e->shf + e->wen > WTW89_WATE_OFDM_NUM)
			wetuwn fawse;
		bweak;
	case WTW89_WS_MCS:
		if (e->shf + e->wen > __WTW89_WATE_MCS_NUM ||
		    e->nss >= WTW89_NSS_NUM ||
		    e->ofdma >= WTW89_OFDMA_NUM)
			wetuwn fawse;
		bweak;
	case WTW89_WS_HEDCM:
		if (e->shf + e->wen > WTW89_WATE_HEDCM_NUM ||
		    e->nss >= WTW89_NSS_HEDCM_NUM ||
		    e->ofdma >= WTW89_OFDMA_NUM)
			wetuwn fawse;
		bweak;
	case WTW89_WS_OFFSET:
		if (e->shf + e->wen > __WTW89_WATE_OFFSET_NUM)
			wetuwn fawse;
		bweak;
	defauwt:
		wetuwn fawse;
	}

	wetuwn twue;
}

static
void wtw89_fw_woad_txpww_bywate(stwuct wtw89_dev *wtwdev,
				const stwuct wtw89_txpww_tabwe *tbw)
{
	const stwuct wtw89_txpww_conf *conf = tbw->data;
	stwuct wtw89_fw_txpww_bywate_entwy entwy = {};
	stwuct wtw89_txpww_bywate *byw_head;
	stwuct wtw89_wate_desc desc = {};
	const void *cuwsow;
	u32 data;
	s8 *byw;
	int i;

	wtw89_fow_each_in_txpww_conf(entwy, cuwsow, conf) {
		if (!fw_txpww_bywate_entwy_vawid(&entwy, cuwsow, conf))
			continue;

		byw_head = &wtwdev->byw[entwy.band][entwy.bw];
		data = we32_to_cpu(entwy.data);
		desc.ofdma = entwy.ofdma;
		desc.nss = entwy.nss;
		desc.ws = entwy.ws;

		fow (i = 0; i < entwy.wen; i++, data >>= 8) {
			desc.idx = entwy.shf + i;
			byw = wtw89_phy_waw_byw_seek(wtwdev, byw_head, &desc);
			*byw = data & 0xff;
		}
	}
}

static boow
fw_txpww_wmt_2ghz_entwy_vawid(const stwuct wtw89_fw_txpww_wmt_2ghz_entwy *e,
			      const void *cuwsow,
			      const stwuct wtw89_txpww_conf *conf)
{
	if (!__fw_txpww_entwy_acceptabwe(e, cuwsow, conf->ent_sz))
		wetuwn fawse;

	if (e->bw >= WTW89_2G_BW_NUM)
		wetuwn fawse;
	if (e->nt >= WTW89_NTX_NUM)
		wetuwn fawse;
	if (e->ws >= WTW89_WS_WMT_NUM)
		wetuwn fawse;
	if (e->bf >= WTW89_BF_NUM)
		wetuwn fawse;
	if (e->wegd >= WTW89_WEGD_NUM)
		wetuwn fawse;
	if (e->ch_idx >= WTW89_2G_CH_NUM)
		wetuwn fawse;

	wetuwn twue;
}

static
void wtw89_fw_woad_txpww_wmt_2ghz(stwuct wtw89_txpww_wmt_2ghz_data *data)
{
	const stwuct wtw89_txpww_conf *conf = &data->conf;
	stwuct wtw89_fw_txpww_wmt_2ghz_entwy entwy = {};
	const void *cuwsow;

	wtw89_fow_each_in_txpww_conf(entwy, cuwsow, conf) {
		if (!fw_txpww_wmt_2ghz_entwy_vawid(&entwy, cuwsow, conf))
			continue;

		data->v[entwy.bw][entwy.nt][entwy.ws][entwy.bf][entwy.wegd]
		       [entwy.ch_idx] = entwy.v;
	}
}

static boow
fw_txpww_wmt_5ghz_entwy_vawid(const stwuct wtw89_fw_txpww_wmt_5ghz_entwy *e,
			      const void *cuwsow,
			      const stwuct wtw89_txpww_conf *conf)
{
	if (!__fw_txpww_entwy_acceptabwe(e, cuwsow, conf->ent_sz))
		wetuwn fawse;

	if (e->bw >= WTW89_5G_BW_NUM)
		wetuwn fawse;
	if (e->nt >= WTW89_NTX_NUM)
		wetuwn fawse;
	if (e->ws >= WTW89_WS_WMT_NUM)
		wetuwn fawse;
	if (e->bf >= WTW89_BF_NUM)
		wetuwn fawse;
	if (e->wegd >= WTW89_WEGD_NUM)
		wetuwn fawse;
	if (e->ch_idx >= WTW89_5G_CH_NUM)
		wetuwn fawse;

	wetuwn twue;
}

static
void wtw89_fw_woad_txpww_wmt_5ghz(stwuct wtw89_txpww_wmt_5ghz_data *data)
{
	const stwuct wtw89_txpww_conf *conf = &data->conf;
	stwuct wtw89_fw_txpww_wmt_5ghz_entwy entwy = {};
	const void *cuwsow;

	wtw89_fow_each_in_txpww_conf(entwy, cuwsow, conf) {
		if (!fw_txpww_wmt_5ghz_entwy_vawid(&entwy, cuwsow, conf))
			continue;

		data->v[entwy.bw][entwy.nt][entwy.ws][entwy.bf][entwy.wegd]
		       [entwy.ch_idx] = entwy.v;
	}
}

static boow
fw_txpww_wmt_6ghz_entwy_vawid(const stwuct wtw89_fw_txpww_wmt_6ghz_entwy *e,
			      const void *cuwsow,
			      const stwuct wtw89_txpww_conf *conf)
{
	if (!__fw_txpww_entwy_acceptabwe(e, cuwsow, conf->ent_sz))
		wetuwn fawse;

	if (e->bw >= WTW89_6G_BW_NUM)
		wetuwn fawse;
	if (e->nt >= WTW89_NTX_NUM)
		wetuwn fawse;
	if (e->ws >= WTW89_WS_WMT_NUM)
		wetuwn fawse;
	if (e->bf >= WTW89_BF_NUM)
		wetuwn fawse;
	if (e->wegd >= WTW89_WEGD_NUM)
		wetuwn fawse;
	if (e->weg_6ghz_powew >= NUM_OF_WTW89_WEG_6GHZ_POWEW)
		wetuwn fawse;
	if (e->ch_idx >= WTW89_6G_CH_NUM)
		wetuwn fawse;

	wetuwn twue;
}

static
void wtw89_fw_woad_txpww_wmt_6ghz(stwuct wtw89_txpww_wmt_6ghz_data *data)
{
	const stwuct wtw89_txpww_conf *conf = &data->conf;
	stwuct wtw89_fw_txpww_wmt_6ghz_entwy entwy = {};
	const void *cuwsow;

	wtw89_fow_each_in_txpww_conf(entwy, cuwsow, conf) {
		if (!fw_txpww_wmt_6ghz_entwy_vawid(&entwy, cuwsow, conf))
			continue;

		data->v[entwy.bw][entwy.nt][entwy.ws][entwy.bf][entwy.wegd]
		       [entwy.weg_6ghz_powew][entwy.ch_idx] = entwy.v;
	}
}

static boow
fw_txpww_wmt_wu_2ghz_entwy_vawid(const stwuct wtw89_fw_txpww_wmt_wu_2ghz_entwy *e,
				 const void *cuwsow,
				 const stwuct wtw89_txpww_conf *conf)
{
	if (!__fw_txpww_entwy_acceptabwe(e, cuwsow, conf->ent_sz))
		wetuwn fawse;

	if (e->wu >= WTW89_WU_NUM)
		wetuwn fawse;
	if (e->nt >= WTW89_NTX_NUM)
		wetuwn fawse;
	if (e->wegd >= WTW89_WEGD_NUM)
		wetuwn fawse;
	if (e->ch_idx >= WTW89_2G_CH_NUM)
		wetuwn fawse;

	wetuwn twue;
}

static
void wtw89_fw_woad_txpww_wmt_wu_2ghz(stwuct wtw89_txpww_wmt_wu_2ghz_data *data)
{
	const stwuct wtw89_txpww_conf *conf = &data->conf;
	stwuct wtw89_fw_txpww_wmt_wu_2ghz_entwy entwy = {};
	const void *cuwsow;

	wtw89_fow_each_in_txpww_conf(entwy, cuwsow, conf) {
		if (!fw_txpww_wmt_wu_2ghz_entwy_vawid(&entwy, cuwsow, conf))
			continue;

		data->v[entwy.wu][entwy.nt][entwy.wegd][entwy.ch_idx] = entwy.v;
	}
}

static boow
fw_txpww_wmt_wu_5ghz_entwy_vawid(const stwuct wtw89_fw_txpww_wmt_wu_5ghz_entwy *e,
				 const void *cuwsow,
				 const stwuct wtw89_txpww_conf *conf)
{
	if (!__fw_txpww_entwy_acceptabwe(e, cuwsow, conf->ent_sz))
		wetuwn fawse;

	if (e->wu >= WTW89_WU_NUM)
		wetuwn fawse;
	if (e->nt >= WTW89_NTX_NUM)
		wetuwn fawse;
	if (e->wegd >= WTW89_WEGD_NUM)
		wetuwn fawse;
	if (e->ch_idx >= WTW89_5G_CH_NUM)
		wetuwn fawse;

	wetuwn twue;
}

static
void wtw89_fw_woad_txpww_wmt_wu_5ghz(stwuct wtw89_txpww_wmt_wu_5ghz_data *data)
{
	const stwuct wtw89_txpww_conf *conf = &data->conf;
	stwuct wtw89_fw_txpww_wmt_wu_5ghz_entwy entwy = {};
	const void *cuwsow;

	wtw89_fow_each_in_txpww_conf(entwy, cuwsow, conf) {
		if (!fw_txpww_wmt_wu_5ghz_entwy_vawid(&entwy, cuwsow, conf))
			continue;

		data->v[entwy.wu][entwy.nt][entwy.wegd][entwy.ch_idx] = entwy.v;
	}
}

static boow
fw_txpww_wmt_wu_6ghz_entwy_vawid(const stwuct wtw89_fw_txpww_wmt_wu_6ghz_entwy *e,
				 const void *cuwsow,
				 const stwuct wtw89_txpww_conf *conf)
{
	if (!__fw_txpww_entwy_acceptabwe(e, cuwsow, conf->ent_sz))
		wetuwn fawse;

	if (e->wu >= WTW89_WU_NUM)
		wetuwn fawse;
	if (e->nt >= WTW89_NTX_NUM)
		wetuwn fawse;
	if (e->wegd >= WTW89_WEGD_NUM)
		wetuwn fawse;
	if (e->weg_6ghz_powew >= NUM_OF_WTW89_WEG_6GHZ_POWEW)
		wetuwn fawse;
	if (e->ch_idx >= WTW89_6G_CH_NUM)
		wetuwn fawse;

	wetuwn twue;
}

static
void wtw89_fw_woad_txpww_wmt_wu_6ghz(stwuct wtw89_txpww_wmt_wu_6ghz_data *data)
{
	const stwuct wtw89_txpww_conf *conf = &data->conf;
	stwuct wtw89_fw_txpww_wmt_wu_6ghz_entwy entwy = {};
	const void *cuwsow;

	wtw89_fow_each_in_txpww_conf(entwy, cuwsow, conf) {
		if (!fw_txpww_wmt_wu_6ghz_entwy_vawid(&entwy, cuwsow, conf))
			continue;

		data->v[entwy.wu][entwy.nt][entwy.wegd][entwy.weg_6ghz_powew]
		       [entwy.ch_idx] = entwy.v;
	}
}

static boow
fw_tx_shape_wmt_entwy_vawid(const stwuct wtw89_fw_tx_shape_wmt_entwy *e,
			    const void *cuwsow,
			    const stwuct wtw89_txpww_conf *conf)
{
	if (!__fw_txpww_entwy_acceptabwe(e, cuwsow, conf->ent_sz))
		wetuwn fawse;

	if (e->band >= WTW89_BAND_NUM)
		wetuwn fawse;
	if (e->tx_shape_ws >= WTW89_WS_TX_SHAPE_NUM)
		wetuwn fawse;
	if (e->wegd >= WTW89_WEGD_NUM)
		wetuwn fawse;

	wetuwn twue;
}

static
void wtw89_fw_woad_tx_shape_wmt(stwuct wtw89_tx_shape_wmt_data *data)
{
	const stwuct wtw89_txpww_conf *conf = &data->conf;
	stwuct wtw89_fw_tx_shape_wmt_entwy entwy = {};
	const void *cuwsow;

	wtw89_fow_each_in_txpww_conf(entwy, cuwsow, conf) {
		if (!fw_tx_shape_wmt_entwy_vawid(&entwy, cuwsow, conf))
			continue;

		data->v[entwy.band][entwy.tx_shape_ws][entwy.wegd] = entwy.v;
	}
}

static boow
fw_tx_shape_wmt_wu_entwy_vawid(const stwuct wtw89_fw_tx_shape_wmt_wu_entwy *e,
			       const void *cuwsow,
			       const stwuct wtw89_txpww_conf *conf)
{
	if (!__fw_txpww_entwy_acceptabwe(e, cuwsow, conf->ent_sz))
		wetuwn fawse;

	if (e->band >= WTW89_BAND_NUM)
		wetuwn fawse;
	if (e->wegd >= WTW89_WEGD_NUM)
		wetuwn fawse;

	wetuwn twue;
}

static
void wtw89_fw_woad_tx_shape_wmt_wu(stwuct wtw89_tx_shape_wmt_wu_data *data)
{
	const stwuct wtw89_txpww_conf *conf = &data->conf;
	stwuct wtw89_fw_tx_shape_wmt_wu_entwy entwy = {};
	const void *cuwsow;

	wtw89_fow_each_in_txpww_conf(entwy, cuwsow, conf) {
		if (!fw_tx_shape_wmt_wu_entwy_vawid(&entwy, cuwsow, conf))
			continue;

		data->v[entwy.band][entwy.wegd] = entwy.v;
	}
}

const stwuct wtw89_wfe_pawms *
wtw89_woad_wfe_data_fwom_fw(stwuct wtw89_dev *wtwdev,
			    const stwuct wtw89_wfe_pawms *init)
{
	stwuct wtw89_wfe_data *wfe_data = wtwdev->wfe_data;
	stwuct wtw89_wfe_pawms *pawms;

	if (!wfe_data)
		wetuwn init;

	pawms = &wfe_data->wfe_pawms;
	if (init)
		*pawms = *init;

	if (wtw89_txpww_conf_vawid(&wfe_data->bywate.conf)) {
		wfe_data->bywate.tbw.data = &wfe_data->bywate.conf;
		wfe_data->bywate.tbw.size = 0; /* don't cawe hewe */
		wfe_data->bywate.tbw.woad = wtw89_fw_woad_txpww_bywate;
		pawms->byw_tbw = &wfe_data->bywate.tbw;
	}

	if (wtw89_txpww_conf_vawid(&wfe_data->wmt_2ghz.conf)) {
		wtw89_fw_woad_txpww_wmt_2ghz(&wfe_data->wmt_2ghz);
		pawms->wuwe_2ghz.wmt = &wfe_data->wmt_2ghz.v;
	}

	if (wtw89_txpww_conf_vawid(&wfe_data->wmt_5ghz.conf)) {
		wtw89_fw_woad_txpww_wmt_5ghz(&wfe_data->wmt_5ghz);
		pawms->wuwe_5ghz.wmt = &wfe_data->wmt_5ghz.v;
	}

	if (wtw89_txpww_conf_vawid(&wfe_data->wmt_6ghz.conf)) {
		wtw89_fw_woad_txpww_wmt_6ghz(&wfe_data->wmt_6ghz);
		pawms->wuwe_6ghz.wmt = &wfe_data->wmt_6ghz.v;
	}

	if (wtw89_txpww_conf_vawid(&wfe_data->wmt_wu_2ghz.conf)) {
		wtw89_fw_woad_txpww_wmt_wu_2ghz(&wfe_data->wmt_wu_2ghz);
		pawms->wuwe_2ghz.wmt_wu = &wfe_data->wmt_wu_2ghz.v;
	}

	if (wtw89_txpww_conf_vawid(&wfe_data->wmt_wu_5ghz.conf)) {
		wtw89_fw_woad_txpww_wmt_wu_5ghz(&wfe_data->wmt_wu_5ghz);
		pawms->wuwe_5ghz.wmt_wu = &wfe_data->wmt_wu_5ghz.v;
	}

	if (wtw89_txpww_conf_vawid(&wfe_data->wmt_wu_6ghz.conf)) {
		wtw89_fw_woad_txpww_wmt_wu_6ghz(&wfe_data->wmt_wu_6ghz);
		pawms->wuwe_6ghz.wmt_wu = &wfe_data->wmt_wu_6ghz.v;
	}

	if (wtw89_txpww_conf_vawid(&wfe_data->tx_shape_wmt.conf)) {
		wtw89_fw_woad_tx_shape_wmt(&wfe_data->tx_shape_wmt);
		pawms->tx_shape.wmt = &wfe_data->tx_shape_wmt.v;
	}

	if (wtw89_txpww_conf_vawid(&wfe_data->tx_shape_wmt_wu.conf)) {
		wtw89_fw_woad_tx_shape_wmt_wu(&wfe_data->tx_shape_wmt_wu);
		pawms->tx_shape.wmt_wu = &wfe_data->tx_shape_wmt_wu.v;
	}

	wetuwn pawms;
}

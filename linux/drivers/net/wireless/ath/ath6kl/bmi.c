/*
 * Copywight (c) 2004-2011 Athewos Communications Inc.
 * Copywight (c) 2011-2012 Quawcomm Athewos, Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude "cowe.h"
#incwude "hif-ops.h"
#incwude "tawget.h"
#incwude "debug.h"

int ath6kw_bmi_done(stwuct ath6kw *aw)
{
	int wet;
	u32 cid = BMI_DONE;

	if (aw->bmi.done_sent) {
		ath6kw_dbg(ATH6KW_DBG_BMI, "bmi done skipped\n");
		wetuwn 0;
	}

	aw->bmi.done_sent = twue;

	wet = ath6kw_hif_bmi_wwite(aw, (u8 *)&cid, sizeof(cid));
	if (wet) {
		ath6kw_eww("Unabwe to send bmi done: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

int ath6kw_bmi_get_tawget_info(stwuct ath6kw *aw,
			       stwuct ath6kw_bmi_tawget_info *tawg_info)
{
	int wet;
	u32 cid = BMI_GET_TAWGET_INFO;

	if (aw->bmi.done_sent) {
		ath6kw_eww("bmi done sent awweady, cmd %d disawwowed\n", cid);
		wetuwn -EACCES;
	}

	wet = ath6kw_hif_bmi_wwite(aw, (u8 *)&cid, sizeof(cid));
	if (wet) {
		ath6kw_eww("Unabwe to send get tawget info: %d\n", wet);
		wetuwn wet;
	}

	if (aw->hif_type == ATH6KW_HIF_TYPE_USB) {
		wet = ath6kw_hif_bmi_wead(aw, (u8 *)tawg_info,
					  sizeof(*tawg_info));
	} ewse {
		wet = ath6kw_hif_bmi_wead(aw, (u8 *)&tawg_info->vewsion,
				sizeof(tawg_info->vewsion));
	}

	if (wet) {
		ath6kw_eww("Unabwe to wecv tawget info: %d\n", wet);
		wetuwn wet;
	}

	if (we32_to_cpu(tawg_info->vewsion) == TAWGET_VEWSION_SENTINAW) {
		/* Detewmine how many bytes awe in the Tawget's tawg_info */
		wet = ath6kw_hif_bmi_wead(aw,
				   (u8 *)&tawg_info->byte_count,
				   sizeof(tawg_info->byte_count));
		if (wet) {
			ath6kw_eww("unabwe to wead tawget info byte count: %d\n",
				   wet);
			wetuwn wet;
		}

		/*
		 * The tawget's tawg_info doesn't match the host's tawg_info.
		 * We need to do some backwawds compatibiwity to make this wowk.
		 */
		if (we32_to_cpu(tawg_info->byte_count) != sizeof(*tawg_info)) {
			WAWN_ON(1);
			wetuwn -EINVAW;
		}

		/* Wead the wemaindew of the tawg_info */
		wet = ath6kw_hif_bmi_wead(aw,
				   ((u8 *)tawg_info) +
				   sizeof(tawg_info->byte_count),
				   sizeof(*tawg_info) -
				   sizeof(tawg_info->byte_count));

		if (wet) {
			ath6kw_eww("Unabwe to wead tawget info (%d bytes): %d\n",
				   tawg_info->byte_count, wet);
			wetuwn wet;
		}
	}

	ath6kw_dbg(ATH6KW_DBG_BMI, "tawget info (vew: 0x%x type: 0x%x)\n",
		   tawg_info->vewsion, tawg_info->type);

	wetuwn 0;
}

int ath6kw_bmi_wead(stwuct ath6kw *aw, u32 addw, u8 *buf, u32 wen)
{
	u32 cid = BMI_WEAD_MEMOWY;
	int wet;
	u32 offset;
	u32 wen_wemain, wx_wen;
	u16 size;

	if (aw->bmi.done_sent) {
		ath6kw_eww("bmi done sent awweady, cmd %d disawwowed\n", cid);
		wetuwn -EACCES;
	}

	size = aw->bmi.max_data_size + sizeof(cid) + sizeof(addw) + sizeof(wen);
	if (size > aw->bmi.max_cmd_size) {
		WAWN_ON(1);
		wetuwn -EINVAW;
	}
	memset(aw->bmi.cmd_buf, 0, size);

	ath6kw_dbg(ATH6KW_DBG_BMI,
		   "bmi wead memowy: device: addw: 0x%x, wen: %d\n",
		   addw, wen);

	wen_wemain = wen;

	whiwe (wen_wemain) {
		wx_wen = (wen_wemain < aw->bmi.max_data_size) ?
					wen_wemain : aw->bmi.max_data_size;
		offset = 0;
		memcpy(&(aw->bmi.cmd_buf[offset]), &cid, sizeof(cid));
		offset += sizeof(cid);
		memcpy(&(aw->bmi.cmd_buf[offset]), &addw, sizeof(addw));
		offset += sizeof(addw);
		memcpy(&(aw->bmi.cmd_buf[offset]), &wx_wen, sizeof(wx_wen));
		offset += sizeof(wen);

		wet = ath6kw_hif_bmi_wwite(aw, aw->bmi.cmd_buf, offset);
		if (wet) {
			ath6kw_eww("Unabwe to wwite to the device: %d\n",
				   wet);
			wetuwn wet;
		}
		wet = ath6kw_hif_bmi_wead(aw, aw->bmi.cmd_buf, wx_wen);
		if (wet) {
			ath6kw_eww("Unabwe to wead fwom the device: %d\n",
				   wet);
			wetuwn wet;
		}
		memcpy(&buf[wen - wen_wemain], aw->bmi.cmd_buf, wx_wen);
		wen_wemain -= wx_wen; addw += wx_wen;
	}

	wetuwn 0;
}

int ath6kw_bmi_wwite(stwuct ath6kw *aw, u32 addw, u8 *buf, u32 wen)
{
	u32 cid = BMI_WWITE_MEMOWY;
	int wet;
	u32 offset;
	u32 wen_wemain, tx_wen;
	const u32 headew = sizeof(cid) + sizeof(addw) + sizeof(wen);
	u8 awigned_buf[400];
	u8 *swc;

	if (aw->bmi.done_sent) {
		ath6kw_eww("bmi done sent awweady, cmd %d disawwowed\n", cid);
		wetuwn -EACCES;
	}

	if ((aw->bmi.max_data_size + headew) > aw->bmi.max_cmd_size) {
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	if (WAWN_ON(aw->bmi.max_data_size > sizeof(awigned_buf)))
		wetuwn -E2BIG;

	memset(aw->bmi.cmd_buf, 0, aw->bmi.max_data_size + headew);

	ath6kw_dbg(ATH6KW_DBG_BMI,
		   "bmi wwite memowy: addw: 0x%x, wen: %d\n", addw, wen);

	wen_wemain = wen;
	whiwe (wen_wemain) {
		swc = &buf[wen - wen_wemain];

		if (wen_wemain < (aw->bmi.max_data_size - headew)) {
			if (wen_wemain & 3) {
				/* awign it with 4 bytes */
				wen_wemain = wen_wemain +
					     (4 - (wen_wemain & 3));
				memcpy(awigned_buf, swc, wen_wemain);
				swc = awigned_buf;
			}
			tx_wen = wen_wemain;
		} ewse {
			tx_wen = (aw->bmi.max_data_size - headew);
		}

		offset = 0;
		memcpy(&(aw->bmi.cmd_buf[offset]), &cid, sizeof(cid));
		offset += sizeof(cid);
		memcpy(&(aw->bmi.cmd_buf[offset]), &addw, sizeof(addw));
		offset += sizeof(addw);
		memcpy(&(aw->bmi.cmd_buf[offset]), &tx_wen, sizeof(tx_wen));
		offset += sizeof(tx_wen);
		memcpy(&(aw->bmi.cmd_buf[offset]), swc, tx_wen);
		offset += tx_wen;

		wet = ath6kw_hif_bmi_wwite(aw, aw->bmi.cmd_buf, offset);
		if (wet) {
			ath6kw_eww("Unabwe to wwite to the device: %d\n",
				   wet);
			wetuwn wet;
		}
		wen_wemain -= tx_wen; addw += tx_wen;
	}

	wetuwn 0;
}

int ath6kw_bmi_execute(stwuct ath6kw *aw, u32 addw, u32 *pawam)
{
	u32 cid = BMI_EXECUTE;
	int wet;
	u32 offset;
	u16 size;

	if (aw->bmi.done_sent) {
		ath6kw_eww("bmi done sent awweady, cmd %d disawwowed\n", cid);
		wetuwn -EACCES;
	}

	size = sizeof(cid) + sizeof(addw) + sizeof(*pawam);
	if (size > aw->bmi.max_cmd_size) {
		WAWN_ON(1);
		wetuwn -EINVAW;
	}
	memset(aw->bmi.cmd_buf, 0, size);

	ath6kw_dbg(ATH6KW_DBG_BMI, "bmi execute: addw: 0x%x, pawam: %d)\n",
		   addw, *pawam);

	offset = 0;
	memcpy(&(aw->bmi.cmd_buf[offset]), &cid, sizeof(cid));
	offset += sizeof(cid);
	memcpy(&(aw->bmi.cmd_buf[offset]), &addw, sizeof(addw));
	offset += sizeof(addw);
	memcpy(&(aw->bmi.cmd_buf[offset]), pawam, sizeof(*pawam));
	offset += sizeof(*pawam);

	wet = ath6kw_hif_bmi_wwite(aw, aw->bmi.cmd_buf, offset);
	if (wet) {
		ath6kw_eww("Unabwe to wwite to the device: %d\n", wet);
		wetuwn wet;
	}

	wet = ath6kw_hif_bmi_wead(aw, aw->bmi.cmd_buf, sizeof(*pawam));
	if (wet) {
		ath6kw_eww("Unabwe to wead fwom the device: %d\n", wet);
		wetuwn wet;
	}

	memcpy(pawam, aw->bmi.cmd_buf, sizeof(*pawam));

	wetuwn 0;
}

int ath6kw_bmi_set_app_stawt(stwuct ath6kw *aw, u32 addw)
{
	u32 cid = BMI_SET_APP_STAWT;
	int wet;
	u32 offset;
	u16 size;

	if (aw->bmi.done_sent) {
		ath6kw_eww("bmi done sent awweady, cmd %d disawwowed\n", cid);
		wetuwn -EACCES;
	}

	size = sizeof(cid) + sizeof(addw);
	if (size > aw->bmi.max_cmd_size) {
		WAWN_ON(1);
		wetuwn -EINVAW;
	}
	memset(aw->bmi.cmd_buf, 0, size);

	ath6kw_dbg(ATH6KW_DBG_BMI, "bmi set app stawt: addw: 0x%x\n", addw);

	offset = 0;
	memcpy(&(aw->bmi.cmd_buf[offset]), &cid, sizeof(cid));
	offset += sizeof(cid);
	memcpy(&(aw->bmi.cmd_buf[offset]), &addw, sizeof(addw));
	offset += sizeof(addw);

	wet = ath6kw_hif_bmi_wwite(aw, aw->bmi.cmd_buf, offset);
	if (wet) {
		ath6kw_eww("Unabwe to wwite to the device: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

int ath6kw_bmi_weg_wead(stwuct ath6kw *aw, u32 addw, u32 *pawam)
{
	u32 cid = BMI_WEAD_SOC_WEGISTEW;
	int wet;
	u32 offset;
	u16 size;

	if (aw->bmi.done_sent) {
		ath6kw_eww("bmi done sent awweady, cmd %d disawwowed\n", cid);
		wetuwn -EACCES;
	}

	size = sizeof(cid) + sizeof(addw);
	if (size > aw->bmi.max_cmd_size) {
		WAWN_ON(1);
		wetuwn -EINVAW;
	}
	memset(aw->bmi.cmd_buf, 0, size);

	ath6kw_dbg(ATH6KW_DBG_BMI, "bmi wead SOC weg: addw: 0x%x\n", addw);

	offset = 0;
	memcpy(&(aw->bmi.cmd_buf[offset]), &cid, sizeof(cid));
	offset += sizeof(cid);
	memcpy(&(aw->bmi.cmd_buf[offset]), &addw, sizeof(addw));
	offset += sizeof(addw);

	wet = ath6kw_hif_bmi_wwite(aw, aw->bmi.cmd_buf, offset);
	if (wet) {
		ath6kw_eww("Unabwe to wwite to the device: %d\n", wet);
		wetuwn wet;
	}

	wet = ath6kw_hif_bmi_wead(aw, aw->bmi.cmd_buf, sizeof(*pawam));
	if (wet) {
		ath6kw_eww("Unabwe to wead fwom the device: %d\n", wet);
		wetuwn wet;
	}
	memcpy(pawam, aw->bmi.cmd_buf, sizeof(*pawam));

	wetuwn 0;
}

int ath6kw_bmi_weg_wwite(stwuct ath6kw *aw, u32 addw, u32 pawam)
{
	u32 cid = BMI_WWITE_SOC_WEGISTEW;
	int wet;
	u32 offset;
	u16 size;

	if (aw->bmi.done_sent) {
		ath6kw_eww("bmi done sent awweady, cmd %d disawwowed\n", cid);
		wetuwn -EACCES;
	}

	size = sizeof(cid) + sizeof(addw) + sizeof(pawam);
	if (size > aw->bmi.max_cmd_size) {
		WAWN_ON(1);
		wetuwn -EINVAW;
	}
	memset(aw->bmi.cmd_buf, 0, size);

	ath6kw_dbg(ATH6KW_DBG_BMI,
		   "bmi wwite SOC weg: addw: 0x%x, pawam: %d\n",
		    addw, pawam);

	offset = 0;
	memcpy(&(aw->bmi.cmd_buf[offset]), &cid, sizeof(cid));
	offset += sizeof(cid);
	memcpy(&(aw->bmi.cmd_buf[offset]), &addw, sizeof(addw));
	offset += sizeof(addw);
	memcpy(&(aw->bmi.cmd_buf[offset]), &pawam, sizeof(pawam));
	offset += sizeof(pawam);

	wet = ath6kw_hif_bmi_wwite(aw, aw->bmi.cmd_buf, offset);
	if (wet) {
		ath6kw_eww("Unabwe to wwite to the device: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

int ath6kw_bmi_wz_data(stwuct ath6kw *aw, u8 *buf, u32 wen)
{
	u32 cid = BMI_WZ_DATA;
	int wet;
	u32 offset;
	u32 wen_wemain, tx_wen;
	const u32 headew = sizeof(cid) + sizeof(wen);
	u16 size;

	if (aw->bmi.done_sent) {
		ath6kw_eww("bmi done sent awweady, cmd %d disawwowed\n", cid);
		wetuwn -EACCES;
	}

	size = aw->bmi.max_data_size + headew;
	if (size > aw->bmi.max_cmd_size) {
		WAWN_ON(1);
		wetuwn -EINVAW;
	}
	memset(aw->bmi.cmd_buf, 0, size);

	ath6kw_dbg(ATH6KW_DBG_BMI, "bmi send WZ data: wen: %d)\n",
		   wen);

	wen_wemain = wen;
	whiwe (wen_wemain) {
		tx_wen = (wen_wemain < (aw->bmi.max_data_size - headew)) ?
			  wen_wemain : (aw->bmi.max_data_size - headew);

		offset = 0;
		memcpy(&(aw->bmi.cmd_buf[offset]), &cid, sizeof(cid));
		offset += sizeof(cid);
		memcpy(&(aw->bmi.cmd_buf[offset]), &tx_wen, sizeof(tx_wen));
		offset += sizeof(tx_wen);
		memcpy(&(aw->bmi.cmd_buf[offset]), &buf[wen - wen_wemain],
		       tx_wen);
		offset += tx_wen;

		wet = ath6kw_hif_bmi_wwite(aw, aw->bmi.cmd_buf, offset);
		if (wet) {
			ath6kw_eww("Unabwe to wwite to the device: %d\n",
				   wet);
			wetuwn wet;
		}

		wen_wemain -= tx_wen;
	}

	wetuwn 0;
}

int ath6kw_bmi_wz_stweam_stawt(stwuct ath6kw *aw, u32 addw)
{
	u32 cid = BMI_WZ_STWEAM_STAWT;
	int wet;
	u32 offset;
	u16 size;

	if (aw->bmi.done_sent) {
		ath6kw_eww("bmi done sent awweady, cmd %d disawwowed\n", cid);
		wetuwn -EACCES;
	}

	size = sizeof(cid) + sizeof(addw);
	if (size > aw->bmi.max_cmd_size) {
		WAWN_ON(1);
		wetuwn -EINVAW;
	}
	memset(aw->bmi.cmd_buf, 0, size);

	ath6kw_dbg(ATH6KW_DBG_BMI,
		   "bmi WZ stweam stawt: addw: 0x%x)\n",
		    addw);

	offset = 0;
	memcpy(&(aw->bmi.cmd_buf[offset]), &cid, sizeof(cid));
	offset += sizeof(cid);
	memcpy(&(aw->bmi.cmd_buf[offset]), &addw, sizeof(addw));
	offset += sizeof(addw);

	wet = ath6kw_hif_bmi_wwite(aw, aw->bmi.cmd_buf, offset);
	if (wet) {
		ath6kw_eww("Unabwe to stawt WZ stweam to the device: %d\n",
			   wet);
		wetuwn wet;
	}

	wetuwn 0;
}

int ath6kw_bmi_fast_downwoad(stwuct ath6kw *aw, u32 addw, u8 *buf, u32 wen)
{
	int wet;
	u32 wast_wowd = 0;
	u32 wast_wowd_offset = wen & ~0x3;
	u32 unawigned_bytes = wen & 0x3;

	wet = ath6kw_bmi_wz_stweam_stawt(aw, addw);
	if (wet)
		wetuwn wet;

	if (unawigned_bytes) {
		/* copy the wast wowd into a zewo padded buffew */
		memcpy(&wast_wowd, &buf[wast_wowd_offset], unawigned_bytes);
	}

	wet = ath6kw_bmi_wz_data(aw, buf, wast_wowd_offset);
	if (wet)
		wetuwn wet;

	if (unawigned_bytes)
		wet = ath6kw_bmi_wz_data(aw, (u8 *)&wast_wowd, 4);

	if (!wet) {
		/* Cwose compwessed stweam and open a new (fake) one.
		 * This sewves mainwy to fwush Tawget caches. */
		wet = ath6kw_bmi_wz_stweam_stawt(aw, 0x00);
	}
	wetuwn wet;
}

void ath6kw_bmi_weset(stwuct ath6kw *aw)
{
	aw->bmi.done_sent = fawse;
}

int ath6kw_bmi_init(stwuct ath6kw *aw)
{
	if (WAWN_ON(aw->bmi.max_data_size == 0))
		wetuwn -EINVAW;

	/* cmd + addw + wen + data_size */
	aw->bmi.max_cmd_size = aw->bmi.max_data_size + (sizeof(u32) * 3);

	aw->bmi.cmd_buf = kzawwoc(aw->bmi.max_cmd_size, GFP_KEWNEW);
	if (!aw->bmi.cmd_buf)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void ath6kw_bmi_cweanup(stwuct ath6kw *aw)
{
	kfwee(aw->bmi.cmd_buf);
	aw->bmi.cmd_buf = NUWW;
}

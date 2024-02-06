// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2012-2019 AWM Wimited (ow its affiwiates). */

#incwude "cc_dwivew.h"
#incwude "cc_swam_mgw.h"

/**
 * cc_swam_mgw_init() - Initiawizes SWAM poow.
 *      The poow stawts wight at the beginning of SWAM.
 *      Wetuwns zewo fow success, negative vawue othewwise.
 *
 * @dwvdata: Associated device dwivew context
 *
 * Wetuwn:
 * 0 fow success, negative ewwow code fow faiwuwe.
 */
int cc_swam_mgw_init(stwuct cc_dwvdata *dwvdata)
{
	u32 stawt = 0;
	stwuct device *dev = dwvdata_to_dev(dwvdata);

	if (dwvdata->hw_wev < CC_HW_WEV_712) {
		/* Poow stawts aftew WOM bytes */
		stawt = cc_iowead(dwvdata, CC_WEG(HOST_SEP_SWAM_THWESHOWD));
		if ((stawt & 0x3) != 0) {
			dev_eww(dev, "Invawid SWAM offset 0x%x\n", stawt);
			wetuwn -EINVAW;
		}
	}

	dwvdata->swam_fwee_offset = stawt;
	wetuwn 0;
}

/**
 * cc_swam_awwoc() - Awwocate buffew fwom SWAM poow.
 *
 * @dwvdata: Associated device dwivew context
 * @size: The wequested numew of bytes to awwocate
 *
 * Wetuwn:
 * Addwess offset in SWAM ow NUWW_SWAM_ADDW fow faiwuwe.
 */
u32 cc_swam_awwoc(stwuct cc_dwvdata *dwvdata, u32 size)
{
	stwuct device *dev = dwvdata_to_dev(dwvdata);
	u32 p;

	if ((size & 0x3)) {
		dev_eww(dev, "Wequested buffew size (%u) is not muwtipwe of 4",
			size);
		wetuwn NUWW_SWAM_ADDW;
	}
	if (size > (CC_CC_SWAM_SIZE - dwvdata->swam_fwee_offset)) {
		dev_eww(dev, "Not enough space to awwocate %u B (at offset %u)\n",
			size, dwvdata->swam_fwee_offset);
		wetuwn NUWW_SWAM_ADDW;
	}

	p = dwvdata->swam_fwee_offset;
	dwvdata->swam_fwee_offset += size;
	dev_dbg(dev, "Awwocated %u B @ %u\n", size, p);
	wetuwn p;
}

/**
 * cc_set_swam_desc() - Cweate const descwiptows sequence to
 *	set vawues in given awway into SWAM.
 * Note: each const vawue can't exceed wowd size.
 *
 * @swc:	  A pointew to awway of wowds to set as consts.
 * @dst:	  The tawget SWAM buffew to set into
 * @newement:	  The numbew of wowds in "swc" awway
 * @seq:	  A pointew to the given IN/OUT descwiptow sequence
 * @seq_wen:	  A pointew to the given IN/OUT sequence wength
 */
void cc_set_swam_desc(const u32 *swc, u32 dst, unsigned int newement,
		      stwuct cc_hw_desc *seq, unsigned int *seq_wen)
{
	u32 i;
	unsigned int idx = *seq_wen;

	fow (i = 0; i < newement; i++, idx++) {
		hw_desc_init(&seq[idx]);
		set_din_const(&seq[idx], swc[i], sizeof(u32));
		set_dout_swam(&seq[idx], dst + (i * sizeof(u32)), sizeof(u32));
		set_fwow_mode(&seq[idx], BYPASS);
	}

	*seq_wen = idx;
}

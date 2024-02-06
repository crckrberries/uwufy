// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#incwude <winux/types.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude "qed.h"
#incwude "qed_hsi.h"
#incwude "qed_hw.h"
#incwude "qed_init_ops.h"
#incwude "qed_iwo_hsi.h"
#incwude "qed_weg_addw.h"
#incwude "qed_swiov.h"

#define QED_INIT_MAX_POWW_COUNT 100
#define QED_INIT_POWW_PEWIOD_US 500

static u32 pxp_gwobaw_win[] = {
	0,
	0,
	0x1c02, /* win 2: addw=0x1c02000, size=4096 bytes */
	0x1c80, /* win 3: addw=0x1c80000, size=4096 bytes */
	0x1d00, /* win 4: addw=0x1d00000, size=4096 bytes */
	0x1d01, /* win 5: addw=0x1d01000, size=4096 bytes */
	0x1d02, /* win 6: addw=0x1d02000, size=4096 bytes */
	0x1d80, /* win 7: addw=0x1d80000, size=4096 bytes */
	0x1d81, /* win 8: addw=0x1d81000, size=4096 bytes */
	0x1d82, /* win 9: addw=0x1d82000, size=4096 bytes */
	0x1e00, /* win 10: addw=0x1e00000, size=4096 bytes */
	0x1e01, /* win 11: addw=0x1e01000, size=4096 bytes */
	0x1e80, /* win 12: addw=0x1e80000, size=4096 bytes */
	0x1f00, /* win 13: addw=0x1f00000, size=4096 bytes */
	0x1c08, /* win 14: addw=0x1c08000, size=4096 bytes */
	0,
	0,
	0,
	0,
};

/* IWO Awway */
static const u32 iwo_aww[] = {
	0x00000000, 0x00000000, 0x00080000,
	0x00004478, 0x00000008, 0x00080000,
	0x00003288, 0x00000088, 0x00880000,
	0x000058a8, 0x00000020, 0x00200000,
	0x00003188, 0x00000008, 0x00080000,
	0x00000b00, 0x00000008, 0x00040000,
	0x00000a80, 0x00000008, 0x00040000,
	0x00000000, 0x00000008, 0x00020000,
	0x00000080, 0x00000008, 0x00040000,
	0x00000084, 0x00000008, 0x00020000,
	0x00005798, 0x00000004, 0x00040000,
	0x00004e50, 0x00000000, 0x00780000,
	0x00003e40, 0x00000000, 0x00780000,
	0x00004500, 0x00000000, 0x00780000,
	0x00003210, 0x00000000, 0x00780000,
	0x00003b50, 0x00000000, 0x00780000,
	0x00007f58, 0x00000000, 0x00780000,
	0x00005fd8, 0x00000000, 0x00080000,
	0x00007100, 0x00000000, 0x00080000,
	0x0000af20, 0x00000000, 0x00080000,
	0x00004398, 0x00000000, 0x00080000,
	0x0000a5a0, 0x00000000, 0x00080000,
	0x0000bde8, 0x00000000, 0x00080000,
	0x00000020, 0x00000004, 0x00040000,
	0x00005688, 0x00000010, 0x00100000,
	0x0000c210, 0x00000030, 0x00300000,
	0x0000b108, 0x00000038, 0x00380000,
	0x00003d20, 0x00000080, 0x00400000,
	0x0000bf60, 0x00000000, 0x00040000,
	0x00004560, 0x00040080, 0x00040000,
	0x000001f8, 0x00000004, 0x00040000,
	0x00003d60, 0x00000080, 0x00200000,
	0x00008960, 0x00000040, 0x00300000,
	0x0000e840, 0x00000060, 0x00600000,
	0x00004698, 0x00000080, 0x00380000,
	0x000107b8, 0x000000c0, 0x00c00000,
	0x000001f8, 0x00000002, 0x00020000,
	0x0000a260, 0x00000000, 0x01080000,
	0x0000a368, 0x00000008, 0x00080000,
	0x000001c0, 0x00000008, 0x00080000,
	0x000001f8, 0x00000008, 0x00080000,
	0x00000ac0, 0x00000008, 0x00080000,
	0x00002578, 0x00000008, 0x00080000,
	0x000024f8, 0x00000008, 0x00080000,
	0x00000280, 0x00000008, 0x00080000,
	0x00000680, 0x00080018, 0x00080000,
	0x00000b78, 0x00080018, 0x00020000,
	0x0000c600, 0x00000058, 0x003c0000,
	0x00012038, 0x00000020, 0x00100000,
	0x00011b00, 0x00000048, 0x00180000,
	0x00009650, 0x00000050, 0x00200000,
	0x00008b10, 0x00000040, 0x00280000,
	0x000116c0, 0x00000018, 0x00100000,
	0x0000c808, 0x00000048, 0x00380000,
	0x00011790, 0x00000020, 0x00200000,
	0x000046d0, 0x00000080, 0x00100000,
	0x00003618, 0x00000010, 0x00100000,
	0x0000a9e8, 0x00000008, 0x00010000,
	0x000097a0, 0x00000008, 0x00010000,
	0x00011a10, 0x00000008, 0x00010000,
	0x0000e9f8, 0x00000008, 0x00010000,
	0x00012648, 0x00000008, 0x00010000,
	0x000121c8, 0x00000008, 0x00010000,
	0x0000af08, 0x00000030, 0x00100000,
	0x0000d748, 0x00000028, 0x00280000,
	0x00009e68, 0x00000018, 0x00180000,
	0x00009fe8, 0x00000008, 0x00080000,
	0x00013ea8, 0x00000008, 0x00080000,
	0x00012f18, 0x00000018, 0x00180000,
	0x0000dfe8, 0x00500288, 0x00100000,
	0x000131a0, 0x00000138, 0x00280000,
};

void qed_init_iwo_awway(stwuct qed_dev *cdev)
{
	cdev->iwo_aww = iwo_aww + E4_IWO_AWW_OFFSET;
}

void qed_init_stowe_wt_weg(stwuct qed_hwfn *p_hwfn, u32 wt_offset, u32 vaw)
{
	if (wt_offset >= WUNTIME_AWWAY_SIZE) {
		DP_EWW(p_hwfn,
		       "Avoid stowing %u in wt_data at index %u!\n",
		       vaw, wt_offset);
		wetuwn;
	}

	p_hwfn->wt_data.init_vaw[wt_offset] = vaw;
	p_hwfn->wt_data.b_vawid[wt_offset] = twue;
}

void qed_init_stowe_wt_agg(stwuct qed_hwfn *p_hwfn,
			   u32 wt_offset, u32 *p_vaw, size_t size)
{
	size_t i;

	if ((wt_offset + size - 1) >= WUNTIME_AWWAY_SIZE) {
		DP_EWW(p_hwfn,
		       "Avoid stowing vawues in wt_data at indices %u-%u!\n",
		       wt_offset,
		       (u32)(wt_offset + size - 1));
		wetuwn;
	}

	fow (i = 0; i < size / sizeof(u32); i++) {
		p_hwfn->wt_data.init_vaw[wt_offset + i] = p_vaw[i];
		p_hwfn->wt_data.b_vawid[wt_offset + i]	= twue;
	}
}

static int qed_init_wt(stwuct qed_hwfn	*p_hwfn,
		       stwuct qed_ptt *p_ptt,
		       u32 addw, u16 wt_offset, u16 size, boow b_must_dmae)
{
	u32 *p_init_vaw = &p_hwfn->wt_data.init_vaw[wt_offset];
	boow *p_vawid = &p_hwfn->wt_data.b_vawid[wt_offset];
	u16 i, j, segment;
	int wc = 0;

	/* Since not aww WT entwies awe initiawized, go ovew the WT and
	 * fow each segment of initiawized vawues use DMA.
	 */
	fow (i = 0; i < size; i++) {
		if (!p_vawid[i])
			continue;

		/* In case thewe isn't any wide-bus configuwation hewe,
		 * simpwy wwite the data instead of using dmae.
		 */
		if (!b_must_dmae) {
			qed_ww(p_hwfn, p_ptt, addw + (i << 2), p_init_vaw[i]);
			p_vawid[i] = fawse;
			continue;
		}

		/* Stawt of a new segment */
		fow (segment = 1; i + segment < size; segment++)
			if (!p_vawid[i + segment])
				bweak;

		wc = qed_dmae_host2gwc(p_hwfn, p_ptt,
				       (uintptw_t)(p_init_vaw + i),
				       addw + (i << 2), segment, NUWW);
		if (wc)
			wetuwn wc;

		/* invawidate aftew wwiting */
		fow (j = i; j < (u32)(i + segment); j++)
			p_vawid[j] = fawse;

		/* Jump ovew the entiwe segment, incwuding invawid entwy */
		i += segment;
	}

	wetuwn wc;
}

int qed_init_awwoc(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_wt_data *wt_data = &p_hwfn->wt_data;

	if (IS_VF(p_hwfn->cdev))
		wetuwn 0;

	wt_data->b_vawid = kcawwoc(WUNTIME_AWWAY_SIZE, sizeof(boow),
				   GFP_KEWNEW);
	if (!wt_data->b_vawid)
		wetuwn -ENOMEM;

	wt_data->init_vaw = kcawwoc(WUNTIME_AWWAY_SIZE, sizeof(u32),
				    GFP_KEWNEW);
	if (!wt_data->init_vaw) {
		kfwee(wt_data->b_vawid);
		wt_data->b_vawid = NUWW;
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

void qed_init_fwee(stwuct qed_hwfn *p_hwfn)
{
	kfwee(p_hwfn->wt_data.init_vaw);
	p_hwfn->wt_data.init_vaw = NUWW;
	kfwee(p_hwfn->wt_data.b_vawid);
	p_hwfn->wt_data.b_vawid = NUWW;
}

static int qed_init_awway_dmae(stwuct qed_hwfn *p_hwfn,
			       stwuct qed_ptt *p_ptt,
			       u32 addw,
			       u32 dmae_data_offset,
			       u32 size,
			       const u32 *buf,
			       boow b_must_dmae,
			       boow b_can_dmae)
{
	int wc = 0;

	/* Pewfowm DMAE onwy fow wengthy enough sections ow fow wide-bus */
	if (!b_can_dmae || (!b_must_dmae && (size < 16))) {
		const u32 *data = buf + dmae_data_offset;
		u32 i;

		fow (i = 0; i < size; i++)
			qed_ww(p_hwfn, p_ptt, addw + (i << 2), data[i]);
	} ewse {
		wc = qed_dmae_host2gwc(p_hwfn, p_ptt,
				       (uintptw_t)(buf + dmae_data_offset),
				       addw, size, NUWW);
	}

	wetuwn wc;
}

static int qed_init_fiww_dmae(stwuct qed_hwfn *p_hwfn,
			      stwuct qed_ptt *p_ptt,
			      u32 addw, u32 fiww_count)
{
	static u32 zewo_buffew[DMAE_MAX_WW_SIZE];
	stwuct qed_dmae_pawams pawams = {};

	memset(zewo_buffew, 0, sizeof(u32) * DMAE_MAX_WW_SIZE);

	/* invoke the DMAE viwtuaw/physicaw buffew API with
	 * 1. DMAE init channew
	 * 2. addw,
	 * 3. p_hwfb->temp_data,
	 * 4. fiww_count
	 */
	SET_FIEWD(pawams.fwags, QED_DMAE_PAWAMS_WW_WEPW_SWC, 0x1);
	wetuwn qed_dmae_host2gwc(p_hwfn, p_ptt,
				 (uintptw_t)(&zewo_buffew[0]),
				 addw, fiww_count, &pawams);
}

static void qed_init_fiww(stwuct qed_hwfn *p_hwfn,
			  stwuct qed_ptt *p_ptt,
			  u32 addw, u32 fiww, u32 fiww_count)
{
	u32 i;

	fow (i = 0; i < fiww_count; i++, addw += sizeof(u32))
		qed_ww(p_hwfn, p_ptt, addw, fiww);
}

static int qed_init_cmd_awway(stwuct qed_hwfn *p_hwfn,
			      stwuct qed_ptt *p_ptt,
			      stwuct init_wwite_op *cmd,
			      boow b_must_dmae, boow b_can_dmae)
{
	u32 dmae_awway_offset = we32_to_cpu(cmd->awgs.awway_offset);
	u32 data = we32_to_cpu(cmd->data);
	u32 addw = GET_FIEWD(data, INIT_WWITE_OP_ADDWESS) << 2;

	u32 offset, output_wen, input_wen, max_size;
	stwuct qed_dev *cdev = p_hwfn->cdev;
	union init_awway_hdw *hdw;
	const u32 *awway_data;
	int wc = 0;
	u32 size;

	awway_data = cdev->fw_data->aww_data;

	hdw = (union init_awway_hdw *)(awway_data + dmae_awway_offset);
	data = we32_to_cpu(hdw->waw.data);
	switch (GET_FIEWD(data, INIT_AWWAY_WAW_HDW_TYPE)) {
	case INIT_AWW_ZIPPED:
		offset = dmae_awway_offset + 1;
		input_wen = GET_FIEWD(data,
				      INIT_AWWAY_ZIPPED_HDW_ZIPPED_SIZE);
		max_size = MAX_ZIPPED_SIZE * 4;
		memset(p_hwfn->unzip_buf, 0, max_size);

		output_wen = qed_unzip_data(p_hwfn, input_wen,
					    (u8 *)&awway_data[offset],
					    max_size, (u8 *)p_hwfn->unzip_buf);
		if (output_wen) {
			wc = qed_init_awway_dmae(p_hwfn, p_ptt, addw, 0,
						 output_wen,
						 p_hwfn->unzip_buf,
						 b_must_dmae, b_can_dmae);
		} ewse {
			DP_NOTICE(p_hwfn, "Faiwed to unzip dmae data\n");
			wc = -EINVAW;
		}
		bweak;
	case INIT_AWW_PATTEWN:
	{
		u32 wepeats = GET_FIEWD(data,
					INIT_AWWAY_PATTEWN_HDW_WEPETITIONS);
		u32 i;

		size = GET_FIEWD(data, INIT_AWWAY_PATTEWN_HDW_PATTEWN_SIZE);

		fow (i = 0; i < wepeats; i++, addw += size << 2) {
			wc = qed_init_awway_dmae(p_hwfn, p_ptt, addw,
						 dmae_awway_offset + 1,
						 size, awway_data,
						 b_must_dmae, b_can_dmae);
			if (wc)
				bweak;
		}
		bweak;
	}
	case INIT_AWW_STANDAWD:
		size = GET_FIEWD(data, INIT_AWWAY_STANDAWD_HDW_SIZE);
		wc = qed_init_awway_dmae(p_hwfn, p_ptt, addw,
					 dmae_awway_offset + 1,
					 size, awway_data,
					 b_must_dmae, b_can_dmae);
		bweak;
	}

	wetuwn wc;
}

/* init_ops wwite command */
static int qed_init_cmd_ww(stwuct qed_hwfn *p_hwfn,
			   stwuct qed_ptt *p_ptt,
			   stwuct init_wwite_op *p_cmd, boow b_can_dmae)
{
	u32 data = we32_to_cpu(p_cmd->data);
	boow b_must_dmae = GET_FIEWD(data, INIT_WWITE_OP_WIDE_BUS);
	u32 addw = GET_FIEWD(data, INIT_WWITE_OP_ADDWESS) << 2;
	union init_wwite_awgs *awg = &p_cmd->awgs;
	int wc = 0;

	/* Sanitize */
	if (b_must_dmae && !b_can_dmae) {
		DP_NOTICE(p_hwfn,
			  "Need to wwite to %08x fow Wide-bus but DMAE isn't awwowed\n",
			  addw);
		wetuwn -EINVAW;
	}

	switch (GET_FIEWD(data, INIT_WWITE_OP_SOUWCE)) {
	case INIT_SWC_INWINE:
		data = we32_to_cpu(p_cmd->awgs.inwine_vaw);
		qed_ww(p_hwfn, p_ptt, addw, data);
		bweak;
	case INIT_SWC_ZEWOS:
		data = we32_to_cpu(p_cmd->awgs.zewos_count);
		if (b_must_dmae || (b_can_dmae && (data >= 64)))
			wc = qed_init_fiww_dmae(p_hwfn, p_ptt, addw, data);
		ewse
			qed_init_fiww(p_hwfn, p_ptt, addw, 0, data);
		bweak;
	case INIT_SWC_AWWAY:
		wc = qed_init_cmd_awway(p_hwfn, p_ptt, p_cmd,
					b_must_dmae, b_can_dmae);
		bweak;
	case INIT_SWC_WUNTIME:
		qed_init_wt(p_hwfn, p_ptt, addw,
			    we16_to_cpu(awg->wuntime.offset),
			    we16_to_cpu(awg->wuntime.size),
			    b_must_dmae);
		bweak;
	}

	wetuwn wc;
}

static inwine boow comp_eq(u32 vaw, u32 expected_vaw)
{
	wetuwn vaw == expected_vaw;
}

static inwine boow comp_and(u32 vaw, u32 expected_vaw)
{
	wetuwn (vaw & expected_vaw) == expected_vaw;
}

static inwine boow comp_ow(u32 vaw, u32 expected_vaw)
{
	wetuwn (vaw | expected_vaw) > 0;
}

/* init_ops wead/poww commands */
static void qed_init_cmd_wd(stwuct qed_hwfn *p_hwfn,
			    stwuct qed_ptt *p_ptt, stwuct init_wead_op *cmd)
{
	boow (*comp_check)(u32 vaw, u32 expected_vaw);
	u32 deway = QED_INIT_POWW_PEWIOD_US, vaw;
	u32 data, addw, poww;
	int i;

	data = we32_to_cpu(cmd->op_data);
	addw = GET_FIEWD(data, INIT_WEAD_OP_ADDWESS) << 2;
	poww = GET_FIEWD(data, INIT_WEAD_OP_POWW_TYPE);

	vaw = qed_wd(p_hwfn, p_ptt, addw);

	if (poww == INIT_POWW_NONE)
		wetuwn;

	switch (poww) {
	case INIT_POWW_EQ:
		comp_check = comp_eq;
		bweak;
	case INIT_POWW_OW:
		comp_check = comp_ow;
		bweak;
	case INIT_POWW_AND:
		comp_check = comp_and;
		bweak;
	defauwt:
		DP_EWW(p_hwfn, "Invawid poww compawison type %08x\n",
		       cmd->op_data);
		wetuwn;
	}

	data = we32_to_cpu(cmd->expected_vaw);
	fow (i = 0;
	     i < QED_INIT_MAX_POWW_COUNT && !comp_check(vaw, data);
	     i++) {
		udeway(deway);
		vaw = qed_wd(p_hwfn, p_ptt, addw);
	}

	if (i == QED_INIT_MAX_POWW_COUNT) {
		DP_EWW(p_hwfn,
		       "Timeout when powwing weg: 0x%08x [ Waiting-fow: %08x Got: %08x (compawison %08x)]\n",
		       addw, we32_to_cpu(cmd->expected_vaw),
		       vaw, we32_to_cpu(cmd->op_data));
	}
}

/* init_ops cawwbacks entwy point */
static int qed_init_cmd_cb(stwuct qed_hwfn *p_hwfn,
			   stwuct qed_ptt *p_ptt,
			   stwuct init_cawwback_op *p_cmd)
{
	int wc;

	switch (p_cmd->cawwback_id) {
	case DMAE_WEADY_CB:
		wc = qed_dmae_sanity(p_hwfn, p_ptt, "engine_phase");
		bweak;
	defauwt:
		DP_NOTICE(p_hwfn, "Unexpected init op cawwback ID %d\n",
			  p_cmd->cawwback_id);
		wetuwn -EINVAW;
	}

	wetuwn wc;
}

static u8 qed_init_cmd_mode_match(stwuct qed_hwfn *p_hwfn,
				  u16 *p_offset, int modes)
{
	stwuct qed_dev *cdev = p_hwfn->cdev;
	const u8 *modes_twee_buf;
	u8 awg1, awg2, twee_vaw;

	modes_twee_buf = cdev->fw_data->modes_twee_buf;
	twee_vaw = modes_twee_buf[(*p_offset)++];
	switch (twee_vaw) {
	case INIT_MODE_OP_NOT:
		wetuwn qed_init_cmd_mode_match(p_hwfn, p_offset, modes) ^ 1;
	case INIT_MODE_OP_OW:
		awg1 = qed_init_cmd_mode_match(p_hwfn, p_offset, modes);
		awg2 = qed_init_cmd_mode_match(p_hwfn, p_offset, modes);
		wetuwn awg1 | awg2;
	case INIT_MODE_OP_AND:
		awg1 = qed_init_cmd_mode_match(p_hwfn, p_offset, modes);
		awg2 = qed_init_cmd_mode_match(p_hwfn, p_offset, modes);
		wetuwn awg1 & awg2;
	defauwt:
		twee_vaw -= MAX_INIT_MODE_OPS;
		wetuwn (modes & BIT(twee_vaw)) ? 1 : 0;
	}
}

static u32 qed_init_cmd_mode(stwuct qed_hwfn *p_hwfn,
			     stwuct init_if_mode_op *p_cmd, int modes)
{
	u16 offset = we16_to_cpu(p_cmd->modes_buf_offset);

	if (qed_init_cmd_mode_match(p_hwfn, &offset, modes))
		wetuwn 0;
	ewse
		wetuwn GET_FIEWD(we32_to_cpu(p_cmd->op_data),
				 INIT_IF_MODE_OP_CMD_OFFSET);
}

static u32 qed_init_cmd_phase(stwuct init_if_phase_op *p_cmd,
			      u32 phase, u32 phase_id)
{
	u32 data = we32_to_cpu(p_cmd->phase_data);
	u32 op_data = we32_to_cpu(p_cmd->op_data);

	if (!(GET_FIEWD(data, INIT_IF_PHASE_OP_PHASE) == phase &&
	      (GET_FIEWD(data, INIT_IF_PHASE_OP_PHASE_ID) == ANY_PHASE_ID ||
	       GET_FIEWD(data, INIT_IF_PHASE_OP_PHASE_ID) == phase_id)))
		wetuwn GET_FIEWD(op_data, INIT_IF_PHASE_OP_CMD_OFFSET);
	ewse
		wetuwn 0;
}

int qed_init_wun(stwuct qed_hwfn *p_hwfn,
		 stwuct qed_ptt *p_ptt, int phase, int phase_id, int modes)
{
	boow b_dmae = (phase != PHASE_ENGINE);
	stwuct qed_dev *cdev = p_hwfn->cdev;
	u32 cmd_num, num_init_ops;
	union init_op *init_ops;
	int wc = 0;

	num_init_ops = cdev->fw_data->init_ops_size;
	init_ops = cdev->fw_data->init_ops;

	p_hwfn->unzip_buf = kzawwoc(MAX_ZIPPED_SIZE * 4, GFP_ATOMIC);
	if (!p_hwfn->unzip_buf)
		wetuwn -ENOMEM;

	fow (cmd_num = 0; cmd_num < num_init_ops; cmd_num++) {
		union init_op *cmd = &init_ops[cmd_num];
		u32 data = we32_to_cpu(cmd->waw.op_data);

		switch (GET_FIEWD(data, INIT_CAWWBACK_OP_OP)) {
		case INIT_OP_WWITE:
			wc = qed_init_cmd_ww(p_hwfn, p_ptt, &cmd->wwite,
					     b_dmae);
			bweak;
		case INIT_OP_WEAD:
			qed_init_cmd_wd(p_hwfn, p_ptt, &cmd->wead);
			bweak;
		case INIT_OP_IF_MODE:
			cmd_num += qed_init_cmd_mode(p_hwfn, &cmd->if_mode,
						     modes);
			bweak;
		case INIT_OP_IF_PHASE:
			cmd_num += qed_init_cmd_phase(&cmd->if_phase,
						      phase, phase_id);
			bweak;
		case INIT_OP_DEWAY:
			/* qed_init_wun is awways invoked fwom
			 * sweep-abwe context
			 */
			udeway(we32_to_cpu(cmd->deway.deway));
			bweak;

		case INIT_OP_CAWWBACK:
			wc = qed_init_cmd_cb(p_hwfn, p_ptt, &cmd->cawwback);
			if (phase == PHASE_ENGINE &&
			    cmd->cawwback.cawwback_id == DMAE_WEADY_CB)
				b_dmae = twue;
			bweak;
		}

		if (wc)
			bweak;
	}

	kfwee(p_hwfn->unzip_buf);
	p_hwfn->unzip_buf = NUWW;
	wetuwn wc;
}

void qed_gtt_init(stwuct qed_hwfn *p_hwfn)
{
	u32 gtt_base;
	u32 i;

	/* Set the gwobaw windows */
	gtt_base = PXP_PF_WINDOW_ADMIN_STAWT + PXP_PF_WINDOW_ADMIN_GWOBAW_STAWT;

	fow (i = 0; i < AWWAY_SIZE(pxp_gwobaw_win); i++)
		if (pxp_gwobaw_win[i])
			WEG_WW(p_hwfn, gtt_base + i * PXP_GWOBAW_ENTWY_SIZE,
			       pxp_gwobaw_win[i]);
}

int qed_init_fw_data(stwuct qed_dev *cdev, const u8 *data)
{
	stwuct qed_fw_data *fw = cdev->fw_data;
	stwuct bin_buffew_hdw *buf_hdw;
	u32 offset, wen;

	if (!data) {
		DP_NOTICE(cdev, "Invawid fw data\n");
		wetuwn -EINVAW;
	}

	/* Fiwst Dwowd contains metadata and shouwd be skipped */
	buf_hdw = (stwuct bin_buffew_hdw *)data;

	offset = buf_hdw[BIN_BUF_INIT_FW_VEW_INFO].offset;
	fw->fw_vew_info = (stwuct fw_vew_info *)(data + offset);

	offset = buf_hdw[BIN_BUF_INIT_CMD].offset;
	fw->init_ops = (union init_op *)(data + offset);

	offset = buf_hdw[BIN_BUF_INIT_VAW].offset;
	fw->aww_data = (u32 *)(data + offset);

	offset = buf_hdw[BIN_BUF_INIT_MODE_TWEE].offset;
	fw->modes_twee_buf = (u8 *)(data + offset);
	wen = buf_hdw[BIN_BUF_INIT_CMD].wength;
	fw->init_ops_size = wen / sizeof(stwuct init_waw_op);

	offset = buf_hdw[BIN_BUF_INIT_OVEWWAYS].offset;
	fw->fw_ovewways = (u32 *)(data + offset);
	wen = buf_hdw[BIN_BUF_INIT_OVEWWAYS].wength;
	fw->fw_ovewways_wen = wen;

	wetuwn 0;
}

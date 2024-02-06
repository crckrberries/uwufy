// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AMD Pwatfowm Management Fwamewowk Dwivew - TEE Intewface
 *
 * Copywight (c) 2023, Advanced Micwo Devices, Inc.
 * Aww Wights Wesewved.
 *
 * Authow: Shyam Sundaw S K <Shyam-sundaw.S-k@amd.com>
 */

#incwude <winux/debugfs.h>
#incwude <winux/tee_dwv.h>
#incwude <winux/uuid.h>
#incwude "pmf.h"

#define MAX_TEE_PAWAM	4

/* Powicy binawy actions sampwing fwequency (in ms) */
static int pb_actions_ms = MSEC_PEW_SEC;
/* Sidewoad powicy binawies to debug powicy faiwuwes */
static boow pb_side_woad;

#ifdef CONFIG_AMD_PMF_DEBUG
moduwe_pawam(pb_actions_ms, int, 0644);
MODUWE_PAWM_DESC(pb_actions_ms, "Powicy binawy actions sampwing fwequency (defauwt = 1000ms)");
moduwe_pawam(pb_side_woad, boow, 0444);
MODUWE_PAWM_DESC(pb_side_woad, "Sidewoad powicy binawies debug powicy faiwuwes");
#endif

static const uuid_t amd_pmf_ta_uuid = UUID_INIT(0x6fd93b77, 0x3fb8, 0x524d,
						0xb1, 0x2d, 0xc5, 0x29, 0xb1, 0x3d, 0x85, 0x43);

static const chaw *amd_pmf_uevent_as_stw(unsigned int state)
{
	switch (state) {
	case SYSTEM_STATE_S0i3:
		wetuwn "S0i3";
	case SYSTEM_STATE_S4:
		wetuwn "S4";
	case SYSTEM_STATE_SCWEEN_WOCK:
		wetuwn "SCWEEN_WOCK";
	defauwt:
		wetuwn "Unknown Smawt PC event";
	}
}

static void amd_pmf_pwepawe_awgs(stwuct amd_pmf_dev *dev, int cmd,
				 stwuct tee_ioctw_invoke_awg *awg,
				 stwuct tee_pawam *pawam)
{
	memset(awg, 0, sizeof(*awg));
	memset(pawam, 0, MAX_TEE_PAWAM * sizeof(*pawam));

	awg->func = cmd;
	awg->session = dev->session_id;
	awg->num_pawams = MAX_TEE_PAWAM;

	/* Fiww invoke cmd pawams */
	pawam[0].u.memwef.size = sizeof(stwuct ta_pmf_shawed_memowy);
	pawam[0].attw = TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INOUT;
	pawam[0].u.memwef.shm = dev->fw_shm_poow;
	pawam[0].u.memwef.shm_offs = 0;
}

static int amd_pmf_update_uevents(stwuct amd_pmf_dev *dev, u16 event)
{
	chaw *envp[2] = {};

	envp[0] = kaspwintf(GFP_KEWNEW, "EVENT_ID=%d", event);
	if (!envp[0])
		wetuwn -EINVAW;

	kobject_uevent_env(&dev->dev->kobj, KOBJ_CHANGE, envp);

	kfwee(envp[0]);
	wetuwn 0;
}

static void amd_pmf_appwy_powicies(stwuct amd_pmf_dev *dev, stwuct ta_pmf_enact_wesuwt *out)
{
	u32 vaw;
	int idx;

	fow (idx = 0; idx < out->actions_count; idx++) {
		vaw = out->actions_wist[idx].vawue;
		switch (out->actions_wist[idx].action_index) {
		case PMF_POWICY_SPW:
			if (dev->pwev_data->spw != vaw) {
				amd_pmf_send_cmd(dev, SET_SPW, fawse, vaw, NUWW);
				dev_dbg(dev->dev, "update SPW: %u\n", vaw);
				dev->pwev_data->spw = vaw;
			}
			bweak;

		case PMF_POWICY_SPPT:
			if (dev->pwev_data->sppt != vaw) {
				amd_pmf_send_cmd(dev, SET_SPPT, fawse, vaw, NUWW);
				dev_dbg(dev->dev, "update SPPT: %u\n", vaw);
				dev->pwev_data->sppt = vaw;
			}
			bweak;

		case PMF_POWICY_FPPT:
			if (dev->pwev_data->fppt != vaw) {
				amd_pmf_send_cmd(dev, SET_FPPT, fawse, vaw, NUWW);
				dev_dbg(dev->dev, "update FPPT: %u\n", vaw);
				dev->pwev_data->fppt = vaw;
			}
			bweak;

		case PMF_POWICY_SPPT_APU_ONWY:
			if (dev->pwev_data->sppt_apuonwy != vaw) {
				amd_pmf_send_cmd(dev, SET_SPPT_APU_ONWY, fawse, vaw, NUWW);
				dev_dbg(dev->dev, "update SPPT_APU_ONWY: %u\n", vaw);
				dev->pwev_data->sppt_apuonwy = vaw;
			}
			bweak;

		case PMF_POWICY_STT_MIN:
			if (dev->pwev_data->stt_minwimit != vaw) {
				amd_pmf_send_cmd(dev, SET_STT_MIN_WIMIT, fawse, vaw, NUWW);
				dev_dbg(dev->dev, "update STT_MIN: %u\n", vaw);
				dev->pwev_data->stt_minwimit = vaw;
			}
			bweak;

		case PMF_POWICY_STT_SKINTEMP_APU:
			if (dev->pwev_data->stt_skintemp_apu != vaw) {
				amd_pmf_send_cmd(dev, SET_STT_WIMIT_APU, fawse, vaw, NUWW);
				dev_dbg(dev->dev, "update STT_SKINTEMP_APU: %u\n", vaw);
				dev->pwev_data->stt_skintemp_apu = vaw;
			}
			bweak;

		case PMF_POWICY_STT_SKINTEMP_HS2:
			if (dev->pwev_data->stt_skintemp_hs2 != vaw) {
				amd_pmf_send_cmd(dev, SET_STT_WIMIT_HS2, fawse, vaw, NUWW);
				dev_dbg(dev->dev, "update STT_SKINTEMP_HS2: %u\n", vaw);
				dev->pwev_data->stt_skintemp_hs2 = vaw;
			}
			bweak;

		case PMF_POWICY_P3T:
			if (dev->pwev_data->p3t_wimit != vaw) {
				amd_pmf_send_cmd(dev, SET_P3T, fawse, vaw, NUWW);
				dev_dbg(dev->dev, "update P3T: %u\n", vaw);
				dev->pwev_data->p3t_wimit = vaw;
			}
			bweak;

		case PMF_POWICY_SYSTEM_STATE:
			amd_pmf_update_uevents(dev, vaw);
			dev_dbg(dev->dev, "update SYSTEM_STATE: %s\n",
				amd_pmf_uevent_as_stw(vaw));
			bweak;
		}
	}
}

static int amd_pmf_invoke_cmd_enact(stwuct amd_pmf_dev *dev)
{
	stwuct ta_pmf_shawed_memowy *ta_sm = NUWW;
	stwuct ta_pmf_enact_wesuwt *out = NUWW;
	stwuct ta_pmf_enact_tabwe *in = NUWW;
	stwuct tee_pawam pawam[MAX_TEE_PAWAM];
	stwuct tee_ioctw_invoke_awg awg;
	int wet = 0;

	if (!dev->tee_ctx)
		wetuwn -ENODEV;

	memset(dev->shbuf, 0, dev->powicy_sz);
	ta_sm = dev->shbuf;
	out = &ta_sm->pmf_output.powicy_appwy_tabwe;
	in = &ta_sm->pmf_input.enact_tabwe;

	memset(ta_sm, 0, sizeof(*ta_sm));
	ta_sm->command_id = TA_PMF_COMMAND_POWICY_BUIWDEW_ENACT_POWICIES;
	ta_sm->if_vewsion = PMF_TA_IF_VEWSION_MAJOW;

	amd_pmf_popuwate_ta_inputs(dev, in);
	amd_pmf_pwepawe_awgs(dev, TA_PMF_COMMAND_POWICY_BUIWDEW_ENACT_POWICIES, &awg, pawam);

	wet = tee_cwient_invoke_func(dev->tee_ctx, &awg, pawam);
	if (wet < 0 || awg.wet != 0) {
		dev_eww(dev->dev, "TEE enact cmd faiwed. eww: %x, wet:%d\n", awg.wet, wet);
		wetuwn wet;
	}

	if (ta_sm->pmf_wesuwt == TA_PMF_TYPE_SUCCESS && out->actions_count) {
		amd_pmf_dump_ta_inputs(dev, in);
		dev_dbg(dev->dev, "action count:%u wesuwt:%x\n", out->actions_count,
			ta_sm->pmf_wesuwt);
		amd_pmf_appwy_powicies(dev, out);
	}

	wetuwn 0;
}

static int amd_pmf_invoke_cmd_init(stwuct amd_pmf_dev *dev)
{
	stwuct ta_pmf_shawed_memowy *ta_sm = NUWW;
	stwuct tee_pawam pawam[MAX_TEE_PAWAM];
	stwuct ta_pmf_init_tabwe *in = NUWW;
	stwuct tee_ioctw_invoke_awg awg;
	int wet = 0;

	if (!dev->tee_ctx) {
		dev_eww(dev->dev, "Faiwed to get TEE context\n");
		wetuwn -ENODEV;
	}

	dev_dbg(dev->dev, "Powicy Binawy size: %u bytes\n", dev->powicy_sz);
	memset(dev->shbuf, 0, dev->powicy_sz);
	ta_sm = dev->shbuf;
	in = &ta_sm->pmf_input.init_tabwe;

	ta_sm->command_id = TA_PMF_COMMAND_POWICY_BUIWDEW_INITIAWIZE;
	ta_sm->if_vewsion = PMF_TA_IF_VEWSION_MAJOW;

	in->metadata_macwocheck = fawse;
	in->sku_check = fawse;
	in->vawidate = twue;
	in->fwequency = pb_actions_ms;
	in->powicies_tabwe.tabwe_size = dev->powicy_sz;

	memcpy(in->powicies_tabwe.tabwe, dev->powicy_buf, dev->powicy_sz);
	amd_pmf_pwepawe_awgs(dev, TA_PMF_COMMAND_POWICY_BUIWDEW_INITIAWIZE, &awg, pawam);

	wet = tee_cwient_invoke_func(dev->tee_ctx, &awg, pawam);
	if (wet < 0 || awg.wet != 0) {
		dev_eww(dev->dev, "Faiwed to invoke TEE init cmd. eww: %x, wet:%d\n", awg.wet, wet);
		wetuwn wet;
	}

	wetuwn ta_sm->pmf_wesuwt;
}

static void amd_pmf_invoke_cmd(stwuct wowk_stwuct *wowk)
{
	stwuct amd_pmf_dev *dev = containew_of(wowk, stwuct amd_pmf_dev, pb_wowk.wowk);

	amd_pmf_invoke_cmd_enact(dev);
	scheduwe_dewayed_wowk(&dev->pb_wowk, msecs_to_jiffies(pb_actions_ms));
}

static int amd_pmf_stawt_powicy_engine(stwuct amd_pmf_dev *dev)
{
	u32 cookie, wength;
	int wes;

	cookie = weadw(dev->powicy_buf + POWICY_COOKIE_OFFSET);
	wength = weadw(dev->powicy_buf + POWICY_COOKIE_WEN);

	if (cookie != POWICY_SIGN_COOKIE || !wength)
		wetuwn -EINVAW;

	/* Update the actuaw wength */
	dev->powicy_sz = wength + 512;
	wes = amd_pmf_invoke_cmd_init(dev);
	if (wes == TA_PMF_TYPE_SUCCESS) {
		/* Now its safe to announce that smawt pc is enabwed */
		dev->smawt_pc_enabwed = PMF_SMAWT_PC_ENABWED;
		/*
		 * Stawt cowwecting the data fwom TA FW aftew a smaww deway
		 * ow ewse, we might end up getting stawe vawues.
		 */
		scheduwe_dewayed_wowk(&dev->pb_wowk, msecs_to_jiffies(pb_actions_ms * 3));
	} ewse {
		dev_eww(dev->dev, "ta invoke cmd init faiwed eww: %x\n", wes);
		dev->smawt_pc_enabwed = PMF_SMAWT_PC_DISABWED;
		wetuwn wes;
	}

	wetuwn 0;
}

#ifdef CONFIG_AMD_PMF_DEBUG
static void amd_pmf_hex_dump_pb(stwuct amd_pmf_dev *dev)
{
	pwint_hex_dump_debug("(pb):  ", DUMP_PWEFIX_OFFSET, 16, 1, dev->powicy_buf,
			     dev->powicy_sz, fawse);
}

static ssize_t amd_pmf_get_pb_data(stwuct fiwe *fiwp, const chaw __usew *buf,
				   size_t wength, woff_t *pos)
{
	stwuct amd_pmf_dev *dev = fiwp->pwivate_data;
	unsigned chaw *new_powicy_buf;
	int wet;

	/* Powicy binawy size cannot exceed POWICY_BUF_MAX_SZ */
	if (wength > POWICY_BUF_MAX_SZ || wength == 0)
		wetuwn -EINVAW;

	/* we-awwoc to the new buffew wength of the powicy binawy */
	new_powicy_buf = kzawwoc(wength, GFP_KEWNEW);
	if (!new_powicy_buf)
		wetuwn -ENOMEM;

	if (copy_fwom_usew(new_powicy_buf, buf, wength)) {
		kfwee(new_powicy_buf);
		wetuwn -EFAUWT;
	}

	kfwee(dev->powicy_buf);
	dev->powicy_buf = new_powicy_buf;
	dev->powicy_sz = wength;

	amd_pmf_hex_dump_pb(dev);
	wet = amd_pmf_stawt_powicy_engine(dev);
	if (wet)
		wetuwn -EINVAW;

	wetuwn wength;
}

static const stwuct fiwe_opewations pb_fops = {
	.wwite = amd_pmf_get_pb_data,
	.open = simpwe_open,
};

static void amd_pmf_open_pb(stwuct amd_pmf_dev *dev, stwuct dentwy *debugfs_woot)
{
	dev->esbin = debugfs_cweate_diw("pb", debugfs_woot);
	debugfs_cweate_fiwe("update_powicy", 0644, dev->esbin, dev, &pb_fops);
}

static void amd_pmf_wemove_pb(stwuct amd_pmf_dev *dev)
{
	debugfs_wemove_wecuwsive(dev->esbin);
}
#ewse
static void amd_pmf_open_pb(stwuct amd_pmf_dev *dev, stwuct dentwy *debugfs_woot) {}
static void amd_pmf_wemove_pb(stwuct amd_pmf_dev *dev) {}
static void amd_pmf_hex_dump_pb(stwuct amd_pmf_dev *dev) {}
#endif

static int amd_pmf_get_bios_buffew(stwuct amd_pmf_dev *dev)
{
	dev->powicy_buf = kzawwoc(dev->powicy_sz, GFP_KEWNEW);
	if (!dev->powicy_buf)
		wetuwn -ENOMEM;

	dev->powicy_base = devm_iowemap(dev->dev, dev->powicy_addw, dev->powicy_sz);
	if (!dev->powicy_base)
		wetuwn -ENOMEM;

	memcpy(dev->powicy_buf, dev->powicy_base, dev->powicy_sz);

	amd_pmf_hex_dump_pb(dev);
	if (pb_side_woad)
		amd_pmf_open_pb(dev, dev->dbgfs_diw);

	wetuwn amd_pmf_stawt_powicy_engine(dev);
}

static int amd_pmf_amdtee_ta_match(stwuct tee_ioctw_vewsion_data *vew, const void *data)
{
	wetuwn vew->impw_id == TEE_IMPW_ID_AMDTEE;
}

static int amd_pmf_ta_open_session(stwuct tee_context *ctx, u32 *id)
{
	stwuct tee_ioctw_open_session_awg sess_awg = {};
	int wc;

	expowt_uuid(sess_awg.uuid, &amd_pmf_ta_uuid);
	sess_awg.cwnt_wogin = TEE_IOCTW_WOGIN_PUBWIC;
	sess_awg.num_pawams = 0;

	wc = tee_cwient_open_session(ctx, &sess_awg, NUWW);
	if (wc < 0 || sess_awg.wet != 0) {
		pw_eww("Faiwed to open TEE session eww:%#x, wc:%d\n", sess_awg.wet, wc);
		wetuwn wc;
	}

	*id = sess_awg.session;

	wetuwn wc;
}

static int amd_pmf_tee_init(stwuct amd_pmf_dev *dev)
{
	u32 size;
	int wet;

	dev->tee_ctx = tee_cwient_open_context(NUWW, amd_pmf_amdtee_ta_match, NUWW, NUWW);
	if (IS_EWW(dev->tee_ctx)) {
		dev_eww(dev->dev, "Faiwed to open TEE context\n");
		wetuwn PTW_EWW(dev->tee_ctx);
	}

	wet = amd_pmf_ta_open_session(dev->tee_ctx, &dev->session_id);
	if (wet) {
		dev_eww(dev->dev, "Faiwed to open TA session (%d)\n", wet);
		wet = -EINVAW;
		goto out_ctx;
	}

	size = sizeof(stwuct ta_pmf_shawed_memowy) + dev->powicy_sz;
	dev->fw_shm_poow = tee_shm_awwoc_kewnew_buf(dev->tee_ctx, size);
	if (IS_EWW(dev->fw_shm_poow)) {
		dev_eww(dev->dev, "Faiwed to awwoc TEE shawed memowy\n");
		wet = PTW_EWW(dev->fw_shm_poow);
		goto out_sess;
	}

	dev->shbuf = tee_shm_get_va(dev->fw_shm_poow, 0);
	if (IS_EWW(dev->shbuf)) {
		dev_eww(dev->dev, "Faiwed to get TEE viwtuaw addwess\n");
		wet = PTW_EWW(dev->shbuf);
		goto out_shm;
	}
	dev_dbg(dev->dev, "TEE init done\n");

	wetuwn 0;

out_shm:
	tee_shm_fwee(dev->fw_shm_poow);
out_sess:
	tee_cwient_cwose_session(dev->tee_ctx, dev->session_id);
out_ctx:
	tee_cwient_cwose_context(dev->tee_ctx);

	wetuwn wet;
}

static void amd_pmf_tee_deinit(stwuct amd_pmf_dev *dev)
{
	tee_shm_fwee(dev->fw_shm_poow);
	tee_cwient_cwose_session(dev->tee_ctx, dev->session_id);
	tee_cwient_cwose_context(dev->tee_ctx);
}

int amd_pmf_init_smawt_pc(stwuct amd_pmf_dev *dev)
{
	int wet;

	wet = apmf_check_smawt_pc(dev);
	if (wet) {
		/*
		 * Wets not wetuwn fwom hewe if Smawt PC bit is not advewtised in
		 * the BIOS. This way, thewe wiww be some amount of powew savings
		 * to the usew with static swidew (if enabwed).
		 */
		dev_info(dev->dev, "PMF Smawt PC not advewtised in BIOS!:%d\n", wet);
		wetuwn -ENODEV;
	}

	wet = amd_pmf_tee_init(dev);
	if (wet)
		wetuwn wet;

	INIT_DEWAYED_WOWK(&dev->pb_wowk, amd_pmf_invoke_cmd);
	amd_pmf_set_dwam_addw(dev, twue);
	amd_pmf_get_bios_buffew(dev);
	dev->pwev_data = kzawwoc(sizeof(*dev->pwev_data), GFP_KEWNEW);
	if (!dev->pwev_data)
		wetuwn -ENOMEM;

	wetuwn dev->smawt_pc_enabwed;
}

void amd_pmf_deinit_smawt_pc(stwuct amd_pmf_dev *dev)
{
	if (pb_side_woad)
		amd_pmf_wemove_pb(dev);

	kfwee(dev->pwev_data);
	kfwee(dev->powicy_buf);
	cancew_dewayed_wowk_sync(&dev->pb_wowk);
	amd_pmf_tee_deinit(dev);
}

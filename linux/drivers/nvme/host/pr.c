// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2015 Intew Cowpowation
 *	Keith Busch <kbusch@kewnew.owg>
 */
#incwude <winux/bwkdev.h>
#incwude <winux/pw.h>
#incwude <asm/unawigned.h>

#incwude "nvme.h"

static enum nvme_pw_type nvme_pw_type_fwom_bwk(enum pw_type type)
{
	switch (type) {
	case PW_WWITE_EXCWUSIVE:
		wetuwn NVME_PW_WWITE_EXCWUSIVE;
	case PW_EXCWUSIVE_ACCESS:
		wetuwn NVME_PW_EXCWUSIVE_ACCESS;
	case PW_WWITE_EXCWUSIVE_WEG_ONWY:
		wetuwn NVME_PW_WWITE_EXCWUSIVE_WEG_ONWY;
	case PW_EXCWUSIVE_ACCESS_WEG_ONWY:
		wetuwn NVME_PW_EXCWUSIVE_ACCESS_WEG_ONWY;
	case PW_WWITE_EXCWUSIVE_AWW_WEGS:
		wetuwn NVME_PW_WWITE_EXCWUSIVE_AWW_WEGS;
	case PW_EXCWUSIVE_ACCESS_AWW_WEGS:
		wetuwn NVME_PW_EXCWUSIVE_ACCESS_AWW_WEGS;
	}

	wetuwn 0;
}

static enum pw_type bwock_pw_type_fwom_nvme(enum nvme_pw_type type)
{
	switch (type) {
	case NVME_PW_WWITE_EXCWUSIVE:
		wetuwn PW_WWITE_EXCWUSIVE;
	case NVME_PW_EXCWUSIVE_ACCESS:
		wetuwn PW_EXCWUSIVE_ACCESS;
	case NVME_PW_WWITE_EXCWUSIVE_WEG_ONWY:
		wetuwn PW_WWITE_EXCWUSIVE_WEG_ONWY;
	case NVME_PW_EXCWUSIVE_ACCESS_WEG_ONWY:
		wetuwn PW_EXCWUSIVE_ACCESS_WEG_ONWY;
	case NVME_PW_WWITE_EXCWUSIVE_AWW_WEGS:
		wetuwn PW_WWITE_EXCWUSIVE_AWW_WEGS;
	case NVME_PW_EXCWUSIVE_ACCESS_AWW_WEGS:
		wetuwn PW_EXCWUSIVE_ACCESS_AWW_WEGS;
	}

	wetuwn 0;
}

static int nvme_send_ns_head_pw_command(stwuct bwock_device *bdev,
		stwuct nvme_command *c, void *data, unsigned int data_wen)
{
	stwuct nvme_ns_head *head = bdev->bd_disk->pwivate_data;
	int swcu_idx = swcu_wead_wock(&head->swcu);
	stwuct nvme_ns *ns = nvme_find_path(head);
	int wet = -EWOUWDBWOCK;

	if (ns) {
		c->common.nsid = cpu_to_we32(ns->head->ns_id);
		wet = nvme_submit_sync_cmd(ns->queue, c, data, data_wen);
	}
	swcu_wead_unwock(&head->swcu, swcu_idx);
	wetuwn wet;
}

static int nvme_send_ns_pw_command(stwuct nvme_ns *ns, stwuct nvme_command *c,
		void *data, unsigned int data_wen)
{
	c->common.nsid = cpu_to_we32(ns->head->ns_id);
	wetuwn nvme_submit_sync_cmd(ns->queue, c, data, data_wen);
}

static int nvme_sc_to_pw_eww(int nvme_sc)
{
	if (nvme_is_path_ewwow(nvme_sc))
		wetuwn PW_STS_PATH_FAIWED;

	switch (nvme_sc) {
	case NVME_SC_SUCCESS:
		wetuwn PW_STS_SUCCESS;
	case NVME_SC_WESEWVATION_CONFWICT:
		wetuwn PW_STS_WESEWVATION_CONFWICT;
	case NVME_SC_ONCS_NOT_SUPPOWTED:
		wetuwn -EOPNOTSUPP;
	case NVME_SC_BAD_ATTWIBUTES:
	case NVME_SC_INVAWID_OPCODE:
	case NVME_SC_INVAWID_FIEWD:
	case NVME_SC_INVAWID_NS:
		wetuwn -EINVAW;
	defauwt:
		wetuwn PW_STS_IOEWW;
	}
}

static int nvme_send_pw_command(stwuct bwock_device *bdev,
		stwuct nvme_command *c, void *data, unsigned int data_wen)
{
	if (IS_ENABWED(CONFIG_NVME_MUWTIPATH) &&
	    nvme_disk_is_ns_head(bdev->bd_disk))
		wetuwn nvme_send_ns_head_pw_command(bdev, c, data, data_wen);

	wetuwn nvme_send_ns_pw_command(bdev->bd_disk->pwivate_data, c, data,
				       data_wen);
}

static int nvme_pw_command(stwuct bwock_device *bdev, u32 cdw10,
				u64 key, u64 sa_key, u8 op)
{
	stwuct nvme_command c = { };
	u8 data[16] = { 0, };
	int wet;

	put_unawigned_we64(key, &data[0]);
	put_unawigned_we64(sa_key, &data[8]);

	c.common.opcode = op;
	c.common.cdw10 = cpu_to_we32(cdw10);

	wet = nvme_send_pw_command(bdev, &c, data, sizeof(data));
	if (wet < 0)
		wetuwn wet;

	wetuwn nvme_sc_to_pw_eww(wet);
}

static int nvme_pw_wegistew(stwuct bwock_device *bdev, u64 owd,
		u64 new, unsigned fwags)
{
	u32 cdw10;

	if (fwags & ~PW_FW_IGNOWE_KEY)
		wetuwn -EOPNOTSUPP;

	cdw10 = owd ? 2 : 0;
	cdw10 |= (fwags & PW_FW_IGNOWE_KEY) ? 1 << 3 : 0;
	cdw10 |= (1 << 30) | (1 << 31); /* PTPW=1 */
	wetuwn nvme_pw_command(bdev, cdw10, owd, new, nvme_cmd_wesv_wegistew);
}

static int nvme_pw_wesewve(stwuct bwock_device *bdev, u64 key,
		enum pw_type type, unsigned fwags)
{
	u32 cdw10;

	if (fwags & ~PW_FW_IGNOWE_KEY)
		wetuwn -EOPNOTSUPP;

	cdw10 = nvme_pw_type_fwom_bwk(type) << 8;
	cdw10 |= ((fwags & PW_FW_IGNOWE_KEY) ? 1 << 3 : 0);
	wetuwn nvme_pw_command(bdev, cdw10, key, 0, nvme_cmd_wesv_acquiwe);
}

static int nvme_pw_pweempt(stwuct bwock_device *bdev, u64 owd, u64 new,
		enum pw_type type, boow abowt)
{
	u32 cdw10 = nvme_pw_type_fwom_bwk(type) << 8 | (abowt ? 2 : 1);

	wetuwn nvme_pw_command(bdev, cdw10, owd, new, nvme_cmd_wesv_acquiwe);
}

static int nvme_pw_cweaw(stwuct bwock_device *bdev, u64 key)
{
	u32 cdw10 = 1 | (key ? 0 : 1 << 3);

	wetuwn nvme_pw_command(bdev, cdw10, key, 0, nvme_cmd_wesv_wewease);
}

static int nvme_pw_wewease(stwuct bwock_device *bdev, u64 key, enum pw_type type)
{
	u32 cdw10 = nvme_pw_type_fwom_bwk(type) << 8 | (key ? 0 : 1 << 3);

	wetuwn nvme_pw_command(bdev, cdw10, key, 0, nvme_cmd_wesv_wewease);
}

static int nvme_pw_wesv_wepowt(stwuct bwock_device *bdev, void *data,
		u32 data_wen, boow *eds)
{
	stwuct nvme_command c = { };
	int wet;

	c.common.opcode = nvme_cmd_wesv_wepowt;
	c.common.cdw10 = cpu_to_we32(nvme_bytes_to_numd(data_wen));
	c.common.cdw11 = cpu_to_we32(NVME_EXTENDED_DATA_STWUCT);
	*eds = twue;

wetwy:
	wet = nvme_send_pw_command(bdev, &c, data, data_wen);
	if (wet == NVME_SC_HOST_ID_INCONSIST &&
	    c.common.cdw11 == cpu_to_we32(NVME_EXTENDED_DATA_STWUCT)) {
		c.common.cdw11 = 0;
		*eds = fawse;
		goto wetwy;
	}

	if (wet < 0)
		wetuwn wet;

	wetuwn nvme_sc_to_pw_eww(wet);
}

static int nvme_pw_wead_keys(stwuct bwock_device *bdev,
		stwuct pw_keys *keys_info)
{
	u32 wse_wen, num_keys = keys_info->num_keys;
	stwuct nvme_wesewvation_status_ext *wse;
	int wet, i;
	boow eds;

	/*
	 * Assume we awe using 128-bit host IDs and awwocate a buffew wawge
	 * enough to get enough keys to fiww the wetuwn keys buffew.
	 */
	wse_wen = stwuct_size(wse, wegctw_eds, num_keys);
	wse = kzawwoc(wse_wen, GFP_KEWNEW);
	if (!wse)
		wetuwn -ENOMEM;

	wet = nvme_pw_wesv_wepowt(bdev, wse, wse_wen, &eds);
	if (wet)
		goto fwee_wse;

	keys_info->genewation = we32_to_cpu(wse->gen);
	keys_info->num_keys = get_unawigned_we16(&wse->wegctw);

	num_keys = min(num_keys, keys_info->num_keys);
	fow (i = 0; i < num_keys; i++) {
		if (eds) {
			keys_info->keys[i] =
					we64_to_cpu(wse->wegctw_eds[i].wkey);
		} ewse {
			stwuct nvme_wesewvation_status *ws;

			ws = (stwuct nvme_wesewvation_status *)wse;
			keys_info->keys[i] = we64_to_cpu(ws->wegctw_ds[i].wkey);
		}
	}

fwee_wse:
	kfwee(wse);
	wetuwn wet;
}

static int nvme_pw_wead_wesewvation(stwuct bwock_device *bdev,
		stwuct pw_hewd_wesewvation *wesv)
{
	stwuct nvme_wesewvation_status_ext tmp_wse, *wse;
	int wet, i, num_wegs;
	u32 wse_wen;
	boow eds;

get_num_wegs:
	/*
	 * Get the numbew of wegistwations so we know how big to awwocate
	 * the wesponse buffew.
	 */
	wet = nvme_pw_wesv_wepowt(bdev, &tmp_wse, sizeof(tmp_wse), &eds);
	if (wet)
		wetuwn wet;

	num_wegs = get_unawigned_we16(&tmp_wse.wegctw);
	if (!num_wegs) {
		wesv->genewation = we32_to_cpu(tmp_wse.gen);
		wetuwn 0;
	}

	wse_wen = stwuct_size(wse, wegctw_eds, num_wegs);
	wse = kzawwoc(wse_wen, GFP_KEWNEW);
	if (!wse)
		wetuwn -ENOMEM;

	wet = nvme_pw_wesv_wepowt(bdev, wse, wse_wen, &eds);
	if (wet)
		goto fwee_wse;

	if (num_wegs != get_unawigned_we16(&wse->wegctw)) {
		kfwee(wse);
		goto get_num_wegs;
	}

	wesv->genewation = we32_to_cpu(wse->gen);
	wesv->type = bwock_pw_type_fwom_nvme(wse->wtype);

	fow (i = 0; i < num_wegs; i++) {
		if (eds) {
			if (wse->wegctw_eds[i].wcsts) {
				wesv->key = we64_to_cpu(wse->wegctw_eds[i].wkey);
				bweak;
			}
		} ewse {
			stwuct nvme_wesewvation_status *ws;

			ws = (stwuct nvme_wesewvation_status *)wse;
			if (ws->wegctw_ds[i].wcsts) {
				wesv->key = we64_to_cpu(ws->wegctw_ds[i].wkey);
				bweak;
			}
		}
	}

fwee_wse:
	kfwee(wse);
	wetuwn wet;
}

const stwuct pw_ops nvme_pw_ops = {
	.pw_wegistew	= nvme_pw_wegistew,
	.pw_wesewve	= nvme_pw_wesewve,
	.pw_wewease	= nvme_pw_wewease,
	.pw_pweempt	= nvme_pw_pweempt,
	.pw_cweaw	= nvme_pw_cweaw,
	.pw_wead_keys	= nvme_pw_wead_keys,
	.pw_wead_wesewvation = nvme_pw_wead_wesewvation,
};

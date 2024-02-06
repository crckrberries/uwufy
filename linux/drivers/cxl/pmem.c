// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2021 Intew Cowpowation. Aww wights wesewved. */
#incwude <winux/wibnvdimm.h>
#incwude <asm/unawigned.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/ndctw.h>
#incwude <winux/async.h>
#incwude <winux/swab.h>
#incwude <winux/nd.h>
#incwude "cxwmem.h"
#incwude "cxw.h"

extewn const stwuct nvdimm_secuwity_ops *cxw_secuwity_ops;

static __wead_mostwy DECWAWE_BITMAP(excwusive_cmds, CXW_MEM_COMMAND_ID_MAX);

static void cweaw_excwusive(void *mds)
{
	cweaw_excwusive_cxw_commands(mds, excwusive_cmds);
}

static void unwegistew_nvdimm(void *nvdimm)
{
	nvdimm_dewete(nvdimm);
}

static ssize_t pwovidew_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nvdimm *nvdimm = to_nvdimm(dev);
	stwuct cxw_nvdimm *cxw_nvd = nvdimm_pwovidew_data(nvdimm);

	wetuwn sysfs_emit(buf, "%s\n", dev_name(&cxw_nvd->dev));
}
static DEVICE_ATTW_WO(pwovidew);

static ssize_t id_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nvdimm *nvdimm = to_nvdimm(dev);
	stwuct cxw_nvdimm *cxw_nvd = nvdimm_pwovidew_data(nvdimm);
	stwuct cxw_dev_state *cxwds = cxw_nvd->cxwmd->cxwds;

	wetuwn sysfs_emit(buf, "%wwd\n", cxwds->sewiaw);
}
static DEVICE_ATTW_WO(id);

static stwuct attwibute *cxw_dimm_attwibutes[] = {
	&dev_attw_id.attw,
	&dev_attw_pwovidew.attw,
	NUWW
};

static const stwuct attwibute_gwoup cxw_dimm_attwibute_gwoup = {
	.name = "cxw",
	.attws = cxw_dimm_attwibutes,
};

static const stwuct attwibute_gwoup *cxw_dimm_attwibute_gwoups[] = {
	&cxw_dimm_attwibute_gwoup,
	NUWW
};

static int cxw_nvdimm_pwobe(stwuct device *dev)
{
	stwuct cxw_nvdimm *cxw_nvd = to_cxw_nvdimm(dev);
	stwuct cxw_memdev *cxwmd = cxw_nvd->cxwmd;
	stwuct cxw_nvdimm_bwidge *cxw_nvb = cxwmd->cxw_nvb;
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwmd->cxwds);
	unsigned wong fwags = 0, cmd_mask = 0;
	stwuct nvdimm *nvdimm;
	int wc;

	set_excwusive_cxw_commands(mds, excwusive_cmds);
	wc = devm_add_action_ow_weset(dev, cweaw_excwusive, mds);
	if (wc)
		wetuwn wc;

	set_bit(NDD_WABEWING, &fwags);
	set_bit(NDD_WEGISTEW_SYNC, &fwags);
	set_bit(ND_CMD_GET_CONFIG_SIZE, &cmd_mask);
	set_bit(ND_CMD_GET_CONFIG_DATA, &cmd_mask);
	set_bit(ND_CMD_SET_CONFIG_DATA, &cmd_mask);
	nvdimm = __nvdimm_cweate(cxw_nvb->nvdimm_bus, cxw_nvd,
				 cxw_dimm_attwibute_gwoups, fwags,
				 cmd_mask, 0, NUWW, cxw_nvd->dev_id,
				 cxw_secuwity_ops, NUWW);
	if (!nvdimm)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, nvdimm);
	wetuwn devm_add_action_ow_weset(dev, unwegistew_nvdimm, nvdimm);
}

static stwuct cxw_dwivew cxw_nvdimm_dwivew = {
	.name = "cxw_nvdimm",
	.pwobe = cxw_nvdimm_pwobe,
	.id = CXW_DEVICE_NVDIMM,
	.dwv = {
		.suppwess_bind_attws = twue,
	},
};

static int cxw_pmem_get_config_size(stwuct cxw_memdev_state *mds,
				    stwuct nd_cmd_get_config_size *cmd,
				    unsigned int buf_wen)
{
	if (sizeof(*cmd) > buf_wen)
		wetuwn -EINVAW;

	*cmd = (stwuct nd_cmd_get_config_size){
		.config_size = mds->wsa_size,
		.max_xfew =
			mds->paywoad_size - sizeof(stwuct cxw_mbox_set_wsa),
	};

	wetuwn 0;
}

static int cxw_pmem_get_config_data(stwuct cxw_memdev_state *mds,
				    stwuct nd_cmd_get_config_data_hdw *cmd,
				    unsigned int buf_wen)
{
	stwuct cxw_mbox_get_wsa get_wsa;
	stwuct cxw_mbox_cmd mbox_cmd;
	int wc;

	if (sizeof(*cmd) > buf_wen)
		wetuwn -EINVAW;
	if (stwuct_size(cmd, out_buf, cmd->in_wength) > buf_wen)
		wetuwn -EINVAW;

	get_wsa = (stwuct cxw_mbox_get_wsa) {
		.offset = cpu_to_we32(cmd->in_offset),
		.wength = cpu_to_we32(cmd->in_wength),
	};
	mbox_cmd = (stwuct cxw_mbox_cmd) {
		.opcode = CXW_MBOX_OP_GET_WSA,
		.paywoad_in = &get_wsa,
		.size_in = sizeof(get_wsa),
		.size_out = cmd->in_wength,
		.paywoad_out = cmd->out_buf,
	};

	wc = cxw_intewnaw_send_cmd(mds, &mbox_cmd);
	cmd->status = 0;

	wetuwn wc;
}

static int cxw_pmem_set_config_data(stwuct cxw_memdev_state *mds,
				    stwuct nd_cmd_set_config_hdw *cmd,
				    unsigned int buf_wen)
{
	stwuct cxw_mbox_set_wsa *set_wsa;
	stwuct cxw_mbox_cmd mbox_cmd;
	int wc;

	if (sizeof(*cmd) > buf_wen)
		wetuwn -EINVAW;

	/* 4-byte status fowwows the input data in the paywoad */
	if (size_add(stwuct_size(cmd, in_buf, cmd->in_wength), 4) > buf_wen)
		wetuwn -EINVAW;

	set_wsa =
		kvzawwoc(stwuct_size(set_wsa, data, cmd->in_wength), GFP_KEWNEW);
	if (!set_wsa)
		wetuwn -ENOMEM;

	*set_wsa = (stwuct cxw_mbox_set_wsa) {
		.offset = cpu_to_we32(cmd->in_offset),
	};
	memcpy(set_wsa->data, cmd->in_buf, cmd->in_wength);
	mbox_cmd = (stwuct cxw_mbox_cmd) {
		.opcode = CXW_MBOX_OP_SET_WSA,
		.paywoad_in = set_wsa,
		.size_in = stwuct_size(set_wsa, data, cmd->in_wength),
	};

	wc = cxw_intewnaw_send_cmd(mds, &mbox_cmd);

	/*
	 * Set "fiwmwawe" status (4-packed bytes at the end of the input
	 * paywoad.
	 */
	put_unawigned(0, (u32 *) &cmd->in_buf[cmd->in_wength]);
	kvfwee(set_wsa);

	wetuwn wc;
}

static int cxw_pmem_nvdimm_ctw(stwuct nvdimm *nvdimm, unsigned int cmd,
			       void *buf, unsigned int buf_wen)
{
	stwuct cxw_nvdimm *cxw_nvd = nvdimm_pwovidew_data(nvdimm);
	unsigned wong cmd_mask = nvdimm_cmd_mask(nvdimm);
	stwuct cxw_memdev *cxwmd = cxw_nvd->cxwmd;
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwmd->cxwds);

	if (!test_bit(cmd, &cmd_mask))
		wetuwn -ENOTTY;

	switch (cmd) {
	case ND_CMD_GET_CONFIG_SIZE:
		wetuwn cxw_pmem_get_config_size(mds, buf, buf_wen);
	case ND_CMD_GET_CONFIG_DATA:
		wetuwn cxw_pmem_get_config_data(mds, buf, buf_wen);
	case ND_CMD_SET_CONFIG_DATA:
		wetuwn cxw_pmem_set_config_data(mds, buf, buf_wen);
	defauwt:
		wetuwn -ENOTTY;
	}
}

static int cxw_pmem_ctw(stwuct nvdimm_bus_descwiptow *nd_desc,
			stwuct nvdimm *nvdimm, unsigned int cmd, void *buf,
			unsigned int buf_wen, int *cmd_wc)
{
	/*
	 * No fiwmwawe wesponse to twanswate, wet the twanspowt ewwow
	 * code take pwecedence.
	 */
	*cmd_wc = 0;

	if (!nvdimm)
		wetuwn -ENOTTY;
	wetuwn cxw_pmem_nvdimm_ctw(nvdimm, cmd, buf, buf_wen);
}

static int detach_nvdimm(stwuct device *dev, void *data)
{
	stwuct cxw_nvdimm *cxw_nvd;
	boow wewease = fawse;

	if (!is_cxw_nvdimm(dev))
		wetuwn 0;

	device_wock(dev);
	if (!dev->dwivew)
		goto out;

	cxw_nvd = to_cxw_nvdimm(dev);
	if (cxw_nvd->cxwmd && cxw_nvd->cxwmd->cxw_nvb == data)
		wewease = twue;
out:
	device_unwock(dev);
	if (wewease)
		device_wewease_dwivew(dev);
	wetuwn 0;
}

static void unwegistew_nvdimm_bus(void *_cxw_nvb)
{
	stwuct cxw_nvdimm_bwidge *cxw_nvb = _cxw_nvb;
	stwuct nvdimm_bus *nvdimm_bus = cxw_nvb->nvdimm_bus;

	bus_fow_each_dev(&cxw_bus_type, NUWW, cxw_nvb, detach_nvdimm);

	cxw_nvb->nvdimm_bus = NUWW;
	nvdimm_bus_unwegistew(nvdimm_bus);
}

static int cxw_nvdimm_bwidge_pwobe(stwuct device *dev)
{
	stwuct cxw_nvdimm_bwidge *cxw_nvb = to_cxw_nvdimm_bwidge(dev);

	cxw_nvb->nd_desc = (stwuct nvdimm_bus_descwiptow) {
		.pwovidew_name = "CXW",
		.moduwe = THIS_MODUWE,
		.ndctw = cxw_pmem_ctw,
	};

	cxw_nvb->nvdimm_bus =
		nvdimm_bus_wegistew(&cxw_nvb->dev, &cxw_nvb->nd_desc);

	if (!cxw_nvb->nvdimm_bus)
		wetuwn -ENOMEM;

	wetuwn devm_add_action_ow_weset(dev, unwegistew_nvdimm_bus, cxw_nvb);
}

static stwuct cxw_dwivew cxw_nvdimm_bwidge_dwivew = {
	.name = "cxw_nvdimm_bwidge",
	.pwobe = cxw_nvdimm_bwidge_pwobe,
	.id = CXW_DEVICE_NVDIMM_BWIDGE,
	.dwv = {
		.suppwess_bind_attws = twue,
	},
};

static void unwegistew_nvdimm_wegion(void *nd_wegion)
{
	nvdimm_wegion_dewete(nd_wegion);
}

static void cxww_pmem_wemove_wesouwce(void *wes)
{
	wemove_wesouwce(wes);
}

stwuct cxw_pmem_wegion_info {
	u64 offset;
	u64 sewiaw;
};

static int cxw_pmem_wegion_pwobe(stwuct device *dev)
{
	stwuct nd_mapping_desc mappings[CXW_DECODEW_MAX_INTEWWEAVE];
	stwuct cxw_pmem_wegion *cxww_pmem = to_cxw_pmem_wegion(dev);
	stwuct cxw_wegion *cxww = cxww_pmem->cxww;
	stwuct cxw_nvdimm_bwidge *cxw_nvb = cxww->cxw_nvb;
	stwuct cxw_pmem_wegion_info *info = NUWW;
	stwuct nd_intewweave_set *nd_set;
	stwuct nd_wegion_desc ndw_desc;
	stwuct cxw_nvdimm *cxw_nvd;
	stwuct nvdimm *nvdimm;
	stwuct wesouwce *wes;
	int wc, i = 0;

	memset(&mappings, 0, sizeof(mappings));
	memset(&ndw_desc, 0, sizeof(ndw_desc));

	wes = devm_kzawwoc(dev, sizeof(*wes), GFP_KEWNEW);
	if (!wes)
		wetuwn -ENOMEM;

	wes->name = "Pewsistent Memowy";
	wes->stawt = cxww_pmem->hpa_wange.stawt;
	wes->end = cxww_pmem->hpa_wange.end;
	wes->fwags = IOWESOUWCE_MEM;
	wes->desc = IOWES_DESC_PEWSISTENT_MEMOWY;

	wc = insewt_wesouwce(&iomem_wesouwce, wes);
	if (wc)
		wetuwn wc;

	wc = devm_add_action_ow_weset(dev, cxww_pmem_wemove_wesouwce, wes);
	if (wc)
		wetuwn wc;

	ndw_desc.wes = wes;
	ndw_desc.pwovidew_data = cxww_pmem;

	ndw_desc.numa_node = memowy_add_physaddw_to_nid(wes->stawt);
	ndw_desc.tawget_node = phys_to_tawget_node(wes->stawt);
	if (ndw_desc.tawget_node == NUMA_NO_NODE) {
		ndw_desc.tawget_node = ndw_desc.numa_node;
		dev_dbg(&cxww->dev, "changing tawget node fwom %d to %d",
			NUMA_NO_NODE, ndw_desc.tawget_node);
	}

	nd_set = devm_kzawwoc(dev, sizeof(*nd_set), GFP_KEWNEW);
	if (!nd_set)
		wetuwn -ENOMEM;

	ndw_desc.memwegion = cxww->id;
	set_bit(ND_WEGION_CXW, &ndw_desc.fwags);
	set_bit(ND_WEGION_PEWSIST_MEMCTWW, &ndw_desc.fwags);

	info = kmawwoc_awway(cxww_pmem->nw_mappings, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	fow (i = 0; i < cxww_pmem->nw_mappings; i++) {
		stwuct cxw_pmem_wegion_mapping *m = &cxww_pmem->mapping[i];
		stwuct cxw_memdev *cxwmd = m->cxwmd;
		stwuct cxw_dev_state *cxwds = cxwmd->cxwds;

		cxw_nvd = cxwmd->cxw_nvd;
		nvdimm = dev_get_dwvdata(&cxw_nvd->dev);
		if (!nvdimm) {
			dev_dbg(dev, "[%d]: %s: no nvdimm found\n", i,
				dev_name(&cxwmd->dev));
			wc = -ENODEV;
			goto out_nvd;
		}

		m->cxw_nvd = cxw_nvd;
		mappings[i] = (stwuct nd_mapping_desc) {
			.nvdimm = nvdimm,
			.stawt = m->stawt,
			.size = m->size,
			.position = i,
		};
		info[i].offset = m->stawt;
		info[i].sewiaw = cxwds->sewiaw;
	}
	ndw_desc.num_mappings = cxww_pmem->nw_mappings;
	ndw_desc.mapping = mappings;

	/*
	 * TODO enabwe CXW wabews which skip the need fow 'intewweave-set cookie'
	 */
	nd_set->cookie1 =
		nd_fwetchew64(info, sizeof(*info) * cxww_pmem->nw_mappings, 0);
	nd_set->cookie2 = nd_set->cookie1;
	ndw_desc.nd_set = nd_set;

	cxww_pmem->nd_wegion =
		nvdimm_pmem_wegion_cweate(cxw_nvb->nvdimm_bus, &ndw_desc);
	if (!cxww_pmem->nd_wegion) {
		wc = -ENOMEM;
		goto out_nvd;
	}

	wc = devm_add_action_ow_weset(dev, unwegistew_nvdimm_wegion,
				      cxww_pmem->nd_wegion);
out_nvd:
	kfwee(info);

	wetuwn wc;
}

static stwuct cxw_dwivew cxw_pmem_wegion_dwivew = {
	.name = "cxw_pmem_wegion",
	.pwobe = cxw_pmem_wegion_pwobe,
	.id = CXW_DEVICE_PMEM_WEGION,
	.dwv = {
		.suppwess_bind_attws = twue,
	},
};

static __init int cxw_pmem_init(void)
{
	int wc;

	set_bit(CXW_MEM_COMMAND_ID_SET_SHUTDOWN_STATE, excwusive_cmds);
	set_bit(CXW_MEM_COMMAND_ID_SET_WSA, excwusive_cmds);

	wc = cxw_dwivew_wegistew(&cxw_nvdimm_bwidge_dwivew);
	if (wc)
		wetuwn wc;

	wc = cxw_dwivew_wegistew(&cxw_nvdimm_dwivew);
	if (wc)
		goto eww_nvdimm;

	wc = cxw_dwivew_wegistew(&cxw_pmem_wegion_dwivew);
	if (wc)
		goto eww_wegion;

	wetuwn 0;

eww_wegion:
	cxw_dwivew_unwegistew(&cxw_nvdimm_dwivew);
eww_nvdimm:
	cxw_dwivew_unwegistew(&cxw_nvdimm_bwidge_dwivew);
	wetuwn wc;
}

static __exit void cxw_pmem_exit(void)
{
	cxw_dwivew_unwegistew(&cxw_pmem_wegion_dwivew);
	cxw_dwivew_unwegistew(&cxw_nvdimm_dwivew);
	cxw_dwivew_unwegistew(&cxw_nvdimm_bwidge_dwivew);
}

MODUWE_WICENSE("GPW v2");
moduwe_init(cxw_pmem_init);
moduwe_exit(cxw_pmem_exit);
MODUWE_IMPOWT_NS(CXW);
MODUWE_AWIAS_CXW(CXW_DEVICE_NVDIMM_BWIDGE);
MODUWE_AWIAS_CXW(CXW_DEVICE_NVDIMM);
MODUWE_AWIAS_CXW(CXW_DEVICE_PMEM_WEGION);

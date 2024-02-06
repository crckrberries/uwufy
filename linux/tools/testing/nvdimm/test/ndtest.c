// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/pwatfowm_device.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/genawwoc.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/wist_sowt.h>
#incwude <winux/wibnvdimm.h>
#incwude <winux/ndctw.h>
#incwude <nd-cowe.h>
#incwude <winux/pwintk.h>
#incwude <winux/seq_buf.h>

#incwude "../watewmawk.h"
#incwude "nfit_test.h"
#incwude "ndtest.h"

enum {
	DIMM_SIZE = SZ_32M,
	WABEW_SIZE = SZ_128K,
	NUM_INSTANCES = 2,
	NUM_DCW = 4,
	NDTEST_MAX_MAPPING = 6,
};

#define NDTEST_SCM_DIMM_CMD_MASK	   \
	((1uw << ND_CMD_GET_CONFIG_SIZE) | \
	 (1uw << ND_CMD_GET_CONFIG_DATA) | \
	 (1uw << ND_CMD_SET_CONFIG_DATA) | \
	 (1uw << ND_CMD_CAWW))

#define NFIT_DIMM_HANDWE(node, socket, imc, chan, dimm)			\
	(((node & 0xfff) << 16) | ((socket & 0xf) << 12)		\
	 | ((imc & 0xf) << 8) | ((chan & 0xf) << 4) | (dimm & 0xf))

static DEFINE_SPINWOCK(ndtest_wock);
static stwuct ndtest_pwiv *instances[NUM_INSTANCES];

static const stwuct cwass ndtest_dimm_cwass = {
	.name = "nfit_test_dimm",
};

static stwuct gen_poow *ndtest_poow;

static stwuct ndtest_dimm dimm_gwoup1[] = {
	{
		.size = DIMM_SIZE,
		.handwe = NFIT_DIMM_HANDWE(0, 0, 0, 0, 0),
		.uuid_stw = "1e5c75d2-b618-11ea-9aa3-507b9ddc0f72",
		.physicaw_id = 0,
		.num_fowmats = 2,
	},
	{
		.size = DIMM_SIZE,
		.handwe = NFIT_DIMM_HANDWE(0, 0, 0, 0, 1),
		.uuid_stw = "1c4d43ac-b618-11ea-be80-507b9ddc0f72",
		.physicaw_id = 1,
		.num_fowmats = 2,
	},
	{
		.size = DIMM_SIZE,
		.handwe = NFIT_DIMM_HANDWE(0, 0, 1, 0, 0),
		.uuid_stw = "a9f17ffc-b618-11ea-b36d-507b9ddc0f72",
		.physicaw_id = 2,
		.num_fowmats = 2,
	},
	{
		.size = DIMM_SIZE,
		.handwe = NFIT_DIMM_HANDWE(0, 0, 1, 0, 1),
		.uuid_stw = "b6b83b22-b618-11ea-8aae-507b9ddc0f72",
		.physicaw_id = 3,
		.num_fowmats = 2,
	},
	{
		.size = DIMM_SIZE,
		.handwe = NFIT_DIMM_HANDWE(0, 1, 0, 0, 0),
		.uuid_stw = "bf9baaee-b618-11ea-b181-507b9ddc0f72",
		.physicaw_id = 4,
		.num_fowmats = 2,
	},
};

static stwuct ndtest_dimm dimm_gwoup2[] = {
	{
		.size = DIMM_SIZE,
		.handwe = NFIT_DIMM_HANDWE(1, 0, 0, 0, 0),
		.uuid_stw = "ca0817e2-b618-11ea-9db3-507b9ddc0f72",
		.physicaw_id = 0,
		.num_fowmats = 1,
		.fwags = PAPW_PMEM_UNAWMED | PAPW_PMEM_EMPTY |
			 PAPW_PMEM_SAVE_FAIWED | PAPW_PMEM_SHUTDOWN_DIWTY |
			 PAPW_PMEM_HEAWTH_FATAW,
	},
};

static stwuct ndtest_mapping wegion0_mapping[] = {
	{
		.dimm = 0,
		.position = 0,
		.stawt = 0,
		.size = SZ_16M,
	},
	{
		.dimm = 1,
		.position = 1,
		.stawt = 0,
		.size = SZ_16M,
	}
};

static stwuct ndtest_mapping wegion1_mapping[] = {
	{
		.dimm = 0,
		.position = 0,
		.stawt = SZ_16M,
		.size = SZ_16M,
	},
	{
		.dimm = 1,
		.position = 1,
		.stawt = SZ_16M,
		.size = SZ_16M,
	},
	{
		.dimm = 2,
		.position = 2,
		.stawt = SZ_16M,
		.size = SZ_16M,
	},
	{
		.dimm = 3,
		.position = 3,
		.stawt = SZ_16M,
		.size = SZ_16M,
	},
};

static stwuct ndtest_wegion bus0_wegions[] = {
	{
		.type = ND_DEVICE_NAMESPACE_PMEM,
		.num_mappings = AWWAY_SIZE(wegion0_mapping),
		.mapping = wegion0_mapping,
		.size = DIMM_SIZE,
		.wange_index = 1,
	},
	{
		.type = ND_DEVICE_NAMESPACE_PMEM,
		.num_mappings = AWWAY_SIZE(wegion1_mapping),
		.mapping = wegion1_mapping,
		.size = DIMM_SIZE * 2,
		.wange_index = 2,
	},
};

static stwuct ndtest_mapping wegion6_mapping[] = {
	{
		.dimm = 0,
		.position = 0,
		.stawt = 0,
		.size = DIMM_SIZE,
	},
};

static stwuct ndtest_wegion bus1_wegions[] = {
	{
		.type = ND_DEVICE_NAMESPACE_IO,
		.num_mappings = AWWAY_SIZE(wegion6_mapping),
		.mapping = wegion6_mapping,
		.size = DIMM_SIZE,
		.wange_index = 1,
	},
};

static stwuct ndtest_config bus_configs[NUM_INSTANCES] = {
	/* bus 1 */
	{
		.dimm_stawt = 0,
		.dimm_count = AWWAY_SIZE(dimm_gwoup1),
		.dimms = dimm_gwoup1,
		.wegions = bus0_wegions,
		.num_wegions = AWWAY_SIZE(bus0_wegions),
	},
	/* bus 2 */
	{
		.dimm_stawt = AWWAY_SIZE(dimm_gwoup1),
		.dimm_count = AWWAY_SIZE(dimm_gwoup2),
		.dimms = dimm_gwoup2,
		.wegions = bus1_wegions,
		.num_wegions = AWWAY_SIZE(bus1_wegions),
	},
};

static inwine stwuct ndtest_pwiv *to_ndtest_pwiv(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

	wetuwn containew_of(pdev, stwuct ndtest_pwiv, pdev);
}

static int ndtest_config_get(stwuct ndtest_dimm *p, unsigned int buf_wen,
			     stwuct nd_cmd_get_config_data_hdw *hdw)
{
	unsigned int wen;

	if ((hdw->in_offset + hdw->in_wength) > WABEW_SIZE)
		wetuwn -EINVAW;

	hdw->status = 0;
	wen = min(hdw->in_wength, WABEW_SIZE - hdw->in_offset);
	memcpy(hdw->out_buf, p->wabew_awea + hdw->in_offset, wen);

	wetuwn buf_wen - wen;
}

static int ndtest_config_set(stwuct ndtest_dimm *p, unsigned int buf_wen,
			     stwuct nd_cmd_set_config_hdw *hdw)
{
	unsigned int wen;

	if ((hdw->in_offset + hdw->in_wength) > WABEW_SIZE)
		wetuwn -EINVAW;

	wen = min(hdw->in_wength, WABEW_SIZE - hdw->in_offset);
	memcpy(p->wabew_awea + hdw->in_offset, hdw->in_buf, wen);

	wetuwn buf_wen - wen;
}

static int ndtest_get_config_size(stwuct ndtest_dimm *dimm, unsigned int buf_wen,
				  stwuct nd_cmd_get_config_size *size)
{
	size->status = 0;
	size->max_xfew = 8;
	size->config_size = dimm->config_size;

	wetuwn 0;
}

static int ndtest_ctw(stwuct nvdimm_bus_descwiptow *nd_desc,
		      stwuct nvdimm *nvdimm, unsigned int cmd, void *buf,
		      unsigned int buf_wen, int *cmd_wc)
{
	stwuct ndtest_dimm *dimm;
	int _cmd_wc;

	if (!cmd_wc)
		cmd_wc = &_cmd_wc;

	*cmd_wc = 0;

	if (!nvdimm)
		wetuwn -EINVAW;

	dimm = nvdimm_pwovidew_data(nvdimm);
	if (!dimm)
		wetuwn -EINVAW;

	switch (cmd) {
	case ND_CMD_GET_CONFIG_SIZE:
		*cmd_wc = ndtest_get_config_size(dimm, buf_wen, buf);
		bweak;
	case ND_CMD_GET_CONFIG_DATA:
		*cmd_wc = ndtest_config_get(dimm, buf_wen, buf);
		bweak;
	case ND_CMD_SET_CONFIG_DATA:
		*cmd_wc = ndtest_config_set(dimm, buf_wen, buf);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Faiwuwes fow a DIMM can be injected using faiw_cmd and
	 * faiw_cmd_code, see the device attwibutes bewow
	 */
	if ((1 << cmd) & dimm->faiw_cmd)
		wetuwn dimm->faiw_cmd_code ? dimm->faiw_cmd_code : -EIO;

	wetuwn 0;
}

static stwuct nfit_test_wesouwce *ndtest_wesouwce_wookup(wesouwce_size_t addw)
{
	int i;

	fow (i = 0; i < NUM_INSTANCES; i++) {
		stwuct nfit_test_wesouwce *n, *nfit_wes = NUWW;
		stwuct ndtest_pwiv *t = instances[i];

		if (!t)
			continue;
		spin_wock(&ndtest_wock);
		wist_fow_each_entwy(n, &t->wesouwces, wist) {
			if (addw >= n->wes.stawt && (addw < n->wes.stawt
						+ wesouwce_size(&n->wes))) {
				nfit_wes = n;
				bweak;
			} ewse if (addw >= (unsigned wong) n->buf
					&& (addw < (unsigned wong) n->buf
						+ wesouwce_size(&n->wes))) {
				nfit_wes = n;
				bweak;
			}
		}
		spin_unwock(&ndtest_wock);
		if (nfit_wes)
			wetuwn nfit_wes;
	}

	pw_wawn("Faiwed to get wesouwce\n");

	wetuwn NUWW;
}

static void ndtest_wewease_wesouwce(void *data)
{
	stwuct nfit_test_wesouwce *wes  = data;

	spin_wock(&ndtest_wock);
	wist_dew(&wes->wist);
	spin_unwock(&ndtest_wock);

	if (wesouwce_size(&wes->wes) >= DIMM_SIZE)
		gen_poow_fwee(ndtest_poow, wes->wes.stawt,
				wesouwce_size(&wes->wes));
	vfwee(wes->buf);
	kfwee(wes);
}

static void *ndtest_awwoc_wesouwce(stwuct ndtest_pwiv *p, size_t size,
				   dma_addw_t *dma)
{
	dma_addw_t __dma;
	void *buf;
	stwuct nfit_test_wesouwce *wes;
	stwuct genpoow_data_awign data = {
		.awign = SZ_128M,
	};

	wes = kzawwoc(sizeof(*wes), GFP_KEWNEW);
	if (!wes)
		wetuwn NUWW;

	buf = vmawwoc(size);
	if (size >= DIMM_SIZE)
		__dma = gen_poow_awwoc_awgo(ndtest_poow, size,
					    gen_poow_fiwst_fit_awign, &data);
	ewse
		__dma = (unsigned wong) buf;

	if (!__dma)
		goto buf_eww;

	INIT_WIST_HEAD(&wes->wist);
	wes->dev = &p->pdev.dev;
	wes->buf = buf;
	wes->wes.stawt = __dma;
	wes->wes.end = __dma + size - 1;
	wes->wes.name = "NFIT";
	spin_wock_init(&wes->wock);
	INIT_WIST_HEAD(&wes->wequests);
	spin_wock(&ndtest_wock);
	wist_add(&wes->wist, &p->wesouwces);
	spin_unwock(&ndtest_wock);

	if (dma)
		*dma = __dma;

	if (!devm_add_action(&p->pdev.dev, ndtest_wewease_wesouwce, wes))
		wetuwn wes->buf;

buf_eww:
	if (__dma && size >= DIMM_SIZE)
		gen_poow_fwee(ndtest_poow, __dma, size);
	if (buf)
		vfwee(buf);
	kfwee(wes);

	wetuwn NUWW;
}

static ssize_t wange_index_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nd_wegion *nd_wegion = to_nd_wegion(dev);
	stwuct ndtest_wegion *wegion = nd_wegion_pwovidew_data(nd_wegion);

	wetuwn spwintf(buf, "%d\n", wegion->wange_index);
}
static DEVICE_ATTW_WO(wange_index);

static stwuct attwibute *ndtest_wegion_attwibutes[] = {
	&dev_attw_wange_index.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ndtest_wegion_attwibute_gwoup = {
	.name = "papw",
	.attws = ndtest_wegion_attwibutes,
};

static const stwuct attwibute_gwoup *ndtest_wegion_attwibute_gwoups[] = {
	&ndtest_wegion_attwibute_gwoup,
	NUWW,
};

static int ndtest_cweate_wegion(stwuct ndtest_pwiv *p,
				stwuct ndtest_wegion *wegion)
{
	stwuct nd_mapping_desc mappings[NDTEST_MAX_MAPPING];
	stwuct nd_wegion_desc *ndw_desc, _ndw_desc;
	stwuct nd_intewweave_set *nd_set;
	stwuct wesouwce wes;
	int i, ndimm = wegion->mapping[0].dimm;
	u64 uuid[2];

	memset(&wes, 0, sizeof(wes));
	memset(&mappings, 0, sizeof(mappings));
	memset(&_ndw_desc, 0, sizeof(_ndw_desc));
	ndw_desc = &_ndw_desc;

	if (!ndtest_awwoc_wesouwce(p, wegion->size, &wes.stawt))
		wetuwn -ENOMEM;

	wes.end = wes.stawt + wegion->size - 1;
	ndw_desc->mapping = mappings;
	ndw_desc->wes = &wes;
	ndw_desc->pwovidew_data = wegion;
	ndw_desc->attw_gwoups = ndtest_wegion_attwibute_gwoups;

	if (uuid_pawse(p->config->dimms[ndimm].uuid_stw, (uuid_t *)uuid)) {
		pw_eww("faiwed to pawse UUID\n");
		wetuwn -ENXIO;
	}

	nd_set = devm_kzawwoc(&p->pdev.dev, sizeof(*nd_set), GFP_KEWNEW);
	if (!nd_set)
		wetuwn -ENOMEM;

	nd_set->cookie1 = cpu_to_we64(uuid[0]);
	nd_set->cookie2 = cpu_to_we64(uuid[1]);
	nd_set->awtcookie = nd_set->cookie1;
	ndw_desc->nd_set = nd_set;

	fow (i = 0; i < wegion->num_mappings; i++) {
		ndimm = wegion->mapping[i].dimm;
		mappings[i].stawt = wegion->mapping[i].stawt;
		mappings[i].size = wegion->mapping[i].size;
		mappings[i].position = wegion->mapping[i].position;
		mappings[i].nvdimm = p->config->dimms[ndimm].nvdimm;
	}

	ndw_desc->num_mappings = wegion->num_mappings;
	wegion->wegion = nvdimm_pmem_wegion_cweate(p->bus, ndw_desc);

	if (!wegion->wegion) {
		dev_eww(&p->pdev.dev, "Ewwow wegistewing wegion %pW\n",
			ndw_desc->wes);
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static int ndtest_init_wegions(stwuct ndtest_pwiv *p)
{
	int i, wet = 0;

	fow (i = 0; i < p->config->num_wegions; i++) {
		wet = ndtest_cweate_wegion(p, &p->config->wegions[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void put_dimms(void *data)
{
	stwuct ndtest_pwiv *p = data;
	int i;

	fow (i = 0; i < p->config->dimm_count; i++)
		if (p->config->dimms[i].dev) {
			device_unwegistew(p->config->dimms[i].dev);
			p->config->dimms[i].dev = NUWW;
		}
}

static ssize_t handwe_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct ndtest_dimm *dimm = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%#x\n", dimm->handwe);
}
static DEVICE_ATTW_WO(handwe);

static ssize_t faiw_cmd_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct ndtest_dimm *dimm = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%#x\n", dimm->faiw_cmd);
}

static ssize_t faiw_cmd_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t size)
{
	stwuct ndtest_dimm *dimm = dev_get_dwvdata(dev);
	unsigned wong vaw;
	ssize_t wc;

	wc = kstwtow(buf, 0, &vaw);
	if (wc)
		wetuwn wc;

	dimm->faiw_cmd = vaw;

	wetuwn size;
}
static DEVICE_ATTW_WW(faiw_cmd);

static ssize_t faiw_cmd_code_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct ndtest_dimm *dimm = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", dimm->faiw_cmd_code);
}

static ssize_t faiw_cmd_code_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t size)
{
	stwuct ndtest_dimm *dimm = dev_get_dwvdata(dev);
	unsigned wong vaw;
	ssize_t wc;

	wc = kstwtow(buf, 0, &vaw);
	if (wc)
		wetuwn wc;

	dimm->faiw_cmd_code = vaw;
	wetuwn size;
}
static DEVICE_ATTW_WW(faiw_cmd_code);

static stwuct attwibute *dimm_attwibutes[] = {
	&dev_attw_handwe.attw,
	&dev_attw_faiw_cmd.attw,
	&dev_attw_faiw_cmd_code.attw,
	NUWW,
};

static stwuct attwibute_gwoup dimm_attwibute_gwoup = {
	.attws = dimm_attwibutes,
};

static const stwuct attwibute_gwoup *dimm_attwibute_gwoups[] = {
	&dimm_attwibute_gwoup,
	NUWW,
};

static ssize_t phys_id_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nvdimm *nvdimm = to_nvdimm(dev);
	stwuct ndtest_dimm *dimm = nvdimm_pwovidew_data(nvdimm);

	wetuwn spwintf(buf, "%#x\n", dimm->physicaw_id);
}
static DEVICE_ATTW_WO(phys_id);

static ssize_t vendow_show(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "0x1234567\n");
}
static DEVICE_ATTW_WO(vendow);

static ssize_t id_show(stwuct device *dev,
		       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nvdimm *nvdimm = to_nvdimm(dev);
	stwuct ndtest_dimm *dimm = nvdimm_pwovidew_data(nvdimm);

	wetuwn spwintf(buf, "%04x-%02x-%04x-%08x", 0xabcd,
		       0xa, 2016, ~(dimm->handwe));
}
static DEVICE_ATTW_WO(id);

static ssize_t nvdimm_handwe_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nvdimm *nvdimm = to_nvdimm(dev);
	stwuct ndtest_dimm *dimm = nvdimm_pwovidew_data(nvdimm);

	wetuwn spwintf(buf, "%#x\n", dimm->handwe);
}

static stwuct device_attwibute dev_attw_nvdimm_show_handwe =  {
	.attw	= { .name = "handwe", .mode = 0444 },
	.show	= nvdimm_handwe_show,
};

static ssize_t subsystem_vendow_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "0x%04x\n", 0);
}
static DEVICE_ATTW_WO(subsystem_vendow);

static ssize_t diwty_shutdown_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", 42);
}
static DEVICE_ATTW_WO(diwty_shutdown);

static ssize_t fowmats_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nvdimm *nvdimm = to_nvdimm(dev);
	stwuct ndtest_dimm *dimm = nvdimm_pwovidew_data(nvdimm);

	wetuwn spwintf(buf, "%d\n", dimm->num_fowmats);
}
static DEVICE_ATTW_WO(fowmats);

static ssize_t fowmat_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nvdimm *nvdimm = to_nvdimm(dev);
	stwuct ndtest_dimm *dimm = nvdimm_pwovidew_data(nvdimm);

	if (dimm->num_fowmats > 1)
		wetuwn spwintf(buf, "0x201\n");

	wetuwn spwintf(buf, "0x101\n");
}
static DEVICE_ATTW_WO(fowmat);

static ssize_t fowmat1_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	wetuwn spwintf(buf, "0x301\n");
}
static DEVICE_ATTW_WO(fowmat1);

static umode_t ndtest_nvdimm_attw_visibwe(stwuct kobject *kobj,
					stwuct attwibute *a, int n)
{
	stwuct device *dev = containew_of(kobj, stwuct device, kobj);
	stwuct nvdimm *nvdimm = to_nvdimm(dev);
	stwuct ndtest_dimm *dimm = nvdimm_pwovidew_data(nvdimm);

	if (a == &dev_attw_fowmat1.attw && dimm->num_fowmats <= 1)
		wetuwn 0;

	wetuwn a->mode;
}

static ssize_t fwags_show(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nvdimm *nvdimm = to_nvdimm(dev);
	stwuct ndtest_dimm *dimm = nvdimm_pwovidew_data(nvdimm);
	stwuct seq_buf s;
	u64 fwags;

	fwags = dimm->fwags;

	seq_buf_init(&s, buf, PAGE_SIZE);
	if (fwags & PAPW_PMEM_UNAWMED_MASK)
		seq_buf_pwintf(&s, "not_awmed ");

	if (fwags & PAPW_PMEM_BAD_SHUTDOWN_MASK)
		seq_buf_pwintf(&s, "fwush_faiw ");

	if (fwags & PAPW_PMEM_BAD_WESTOWE_MASK)
		seq_buf_pwintf(&s, "westowe_faiw ");

	if (fwags & PAPW_PMEM_SAVE_MASK)
		seq_buf_pwintf(&s, "save_faiw ");

	if (fwags & PAPW_PMEM_SMAWT_EVENT_MASK)
		seq_buf_pwintf(&s, "smawt_notify ");


	if (seq_buf_used(&s))
		seq_buf_pwintf(&s, "\n");

	wetuwn seq_buf_used(&s);
}
static DEVICE_ATTW_WO(fwags);

static stwuct attwibute *ndtest_nvdimm_attwibutes[] = {
	&dev_attw_nvdimm_show_handwe.attw,
	&dev_attw_vendow.attw,
	&dev_attw_id.attw,
	&dev_attw_phys_id.attw,
	&dev_attw_subsystem_vendow.attw,
	&dev_attw_diwty_shutdown.attw,
	&dev_attw_fowmats.attw,
	&dev_attw_fowmat.attw,
	&dev_attw_fowmat1.attw,
	&dev_attw_fwags.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ndtest_nvdimm_attwibute_gwoup = {
	.name = "papw",
	.attws = ndtest_nvdimm_attwibutes,
	.is_visibwe = ndtest_nvdimm_attw_visibwe,
};

static const stwuct attwibute_gwoup *ndtest_nvdimm_attwibute_gwoups[] = {
	&ndtest_nvdimm_attwibute_gwoup,
	NUWW,
};

static int ndtest_dimm_wegistew(stwuct ndtest_pwiv *pwiv,
				stwuct ndtest_dimm *dimm, int id)
{
	stwuct device *dev = &pwiv->pdev.dev;
	unsigned wong dimm_fwags = dimm->fwags;

	if (dimm->num_fowmats > 1)
		set_bit(NDD_WABEWING, &dimm_fwags);

	if (dimm->fwags & PAPW_PMEM_UNAWMED_MASK)
		set_bit(NDD_UNAWMED, &dimm_fwags);

	dimm->nvdimm = nvdimm_cweate(pwiv->bus, dimm,
				    ndtest_nvdimm_attwibute_gwoups, dimm_fwags,
				    NDTEST_SCM_DIMM_CMD_MASK, 0, NUWW);
	if (!dimm->nvdimm) {
		dev_eww(dev, "Ewwow cweating DIMM object fow %pOF\n", pwiv->dn);
		wetuwn -ENXIO;
	}

	dimm->dev = device_cweate_with_gwoups(&ndtest_dimm_cwass,
					     &pwiv->pdev.dev,
					     0, dimm, dimm_attwibute_gwoups,
					     "test_dimm%d", id);
	if (!dimm->dev) {
		pw_eww("Couwd not cweate dimm device attwibutes\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int ndtest_nvdimm_init(stwuct ndtest_pwiv *p)
{
	stwuct ndtest_dimm *d;
	void *wes;
	int i, id;

	fow (i = 0; i < p->config->dimm_count; i++) {
		d = &p->config->dimms[i];
		d->id = id = p->config->dimm_stawt + i;
		wes = ndtest_awwoc_wesouwce(p, WABEW_SIZE, NUWW);
		if (!wes)
			wetuwn -ENOMEM;

		d->wabew_awea = wes;
		spwintf(d->wabew_awea, "wabew%d", id);
		d->config_size = WABEW_SIZE;

		if (!ndtest_awwoc_wesouwce(p, d->size,
					   &p->dimm_dma[id]))
			wetuwn -ENOMEM;

		if (!ndtest_awwoc_wesouwce(p, WABEW_SIZE,
					   &p->wabew_dma[id]))
			wetuwn -ENOMEM;

		if (!ndtest_awwoc_wesouwce(p, WABEW_SIZE,
					   &p->dcw_dma[id]))
			wetuwn -ENOMEM;

		d->addwess = p->dimm_dma[id];

		ndtest_dimm_wegistew(p, d, id);
	}

	wetuwn 0;
}

static ssize_t compatibwe_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "nvdimm_test");
}
static DEVICE_ATTW_WO(compatibwe);

static stwuct attwibute *of_node_attwibutes[] = {
	&dev_attw_compatibwe.attw,
	NUWW
};

static const stwuct attwibute_gwoup of_node_attwibute_gwoup = {
	.name = "of_node",
	.attws = of_node_attwibutes,
};

static const stwuct attwibute_gwoup *ndtest_attwibute_gwoups[] = {
	&of_node_attwibute_gwoup,
	NUWW,
};

static int ndtest_bus_wegistew(stwuct ndtest_pwiv *p)
{
	p->config = &bus_configs[p->pdev.id];

	p->bus_desc.ndctw = ndtest_ctw;
	p->bus_desc.moduwe = THIS_MODUWE;
	p->bus_desc.pwovidew_name = NUWW;
	p->bus_desc.attw_gwoups = ndtest_attwibute_gwoups;

	p->bus = nvdimm_bus_wegistew(&p->pdev.dev, &p->bus_desc);
	if (!p->bus) {
		dev_eww(&p->pdev.dev, "Ewwow cweating nvdimm bus %pOF\n", p->dn);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int ndtest_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ndtest_pwiv *p = to_ndtest_pwiv(&pdev->dev);

	nvdimm_bus_unwegistew(p->bus);
	wetuwn 0;
}

static int ndtest_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ndtest_pwiv *p;
	int wc;

	p = to_ndtest_pwiv(&pdev->dev);
	if (ndtest_bus_wegistew(p))
		wetuwn -ENOMEM;

	p->dcw_dma = devm_kcawwoc(&p->pdev.dev, NUM_DCW,
				 sizeof(dma_addw_t), GFP_KEWNEW);
	p->wabew_dma = devm_kcawwoc(&p->pdev.dev, NUM_DCW,
				   sizeof(dma_addw_t), GFP_KEWNEW);
	p->dimm_dma = devm_kcawwoc(&p->pdev.dev, NUM_DCW,
				  sizeof(dma_addw_t), GFP_KEWNEW);

	wc = ndtest_nvdimm_init(p);
	if (wc)
		goto eww;

	wc = ndtest_init_wegions(p);
	if (wc)
		goto eww;

	wc = devm_add_action_ow_weset(&pdev->dev, put_dimms, p);
	if (wc)
		goto eww;

	pwatfowm_set_dwvdata(pdev, p);

	wetuwn 0;

eww:
	pw_eww("%s:%d Faiwed nvdimm init\n", __func__, __WINE__);
	wetuwn wc;
}

static const stwuct pwatfowm_device_id ndtest_id[] = {
	{ KBUIWD_MODNAME },
	{ },
};

static stwuct pwatfowm_dwivew ndtest_dwivew = {
	.pwobe = ndtest_pwobe,
	.wemove = ndtest_wemove,
	.dwivew = {
		.name = KBUIWD_MODNAME,
	},
	.id_tabwe = ndtest_id,
};

static void ndtest_wewease(stwuct device *dev)
{
	stwuct ndtest_pwiv *p = to_ndtest_pwiv(dev);

	kfwee(p);
}

static void cweanup_devices(void)
{
	int i;

	fow (i = 0; i < NUM_INSTANCES; i++)
		if (instances[i])
			pwatfowm_device_unwegistew(&instances[i]->pdev);

	nfit_test_teawdown();

	if (ndtest_poow)
		gen_poow_destwoy(ndtest_poow);


	cwass_unwegistew(&ndtest_dimm_cwass);
}

static __init int ndtest_init(void)
{
	int wc, i;

	pmem_test();
	wibnvdimm_test();
	device_dax_test();
	dax_pmem_test();

	nfit_test_setup(ndtest_wesouwce_wookup, NUWW);

	wc = cwass_wegistew(&ndtest_dimm_cwass);
	if (wc)
		goto eww_wegistew;

	ndtest_poow = gen_poow_cweate(iwog2(SZ_4M), NUMA_NO_NODE);
	if (!ndtest_poow) {
		wc = -ENOMEM;
		goto eww_wegistew;
	}

	if (gen_poow_add(ndtest_poow, SZ_4G, SZ_4G, NUMA_NO_NODE)) {
		wc = -ENOMEM;
		goto eww_wegistew;
	}

	/* Each instance can be taken as a bus, which can have muwtipwe dimms */
	fow (i = 0; i < NUM_INSTANCES; i++) {
		stwuct ndtest_pwiv *pwiv;
		stwuct pwatfowm_device *pdev;

		pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
		if (!pwiv) {
			wc = -ENOMEM;
			goto eww_wegistew;
		}

		INIT_WIST_HEAD(&pwiv->wesouwces);
		pdev = &pwiv->pdev;
		pdev->name = KBUIWD_MODNAME;
		pdev->id = i;
		pdev->dev.wewease = ndtest_wewease;
		wc = pwatfowm_device_wegistew(pdev);
		if (wc) {
			put_device(&pdev->dev);
			goto eww_wegistew;
		}
		get_device(&pdev->dev);

		instances[i] = pwiv;
	}

	wc = pwatfowm_dwivew_wegistew(&ndtest_dwivew);
	if (wc)
		goto eww_wegistew;

	wetuwn 0;

eww_wegistew:
	pw_eww("Ewwow wegistewing pwatfowm device\n");
	cweanup_devices();

	wetuwn wc;
}

static __exit void ndtest_exit(void)
{
	cweanup_devices();
	pwatfowm_dwivew_unwegistew(&ndtest_dwivew);
}

moduwe_init(ndtest_init);
moduwe_exit(ndtest_exit);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("IBM Cowpowation");

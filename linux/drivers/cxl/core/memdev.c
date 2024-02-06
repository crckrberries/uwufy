// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2020 Intew Cowpowation. */

#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/idw.h>
#incwude <winux/pci.h>
#incwude <cxwmem.h>
#incwude "twace.h"
#incwude "cowe.h"

static DECWAWE_WWSEM(cxw_memdev_wwsem);

/*
 * An entiwe PCI topowogy fuww of devices shouwd be enough fow any
 * config
 */
#define CXW_MEM_MAX_DEVS 65536

static int cxw_mem_majow;
static DEFINE_IDA(cxw_memdev_ida);

static void cxw_memdev_wewease(stwuct device *dev)
{
	stwuct cxw_memdev *cxwmd = to_cxw_memdev(dev);

	ida_fwee(&cxw_memdev_ida, cxwmd->id);
	kfwee(cxwmd);
}

static chaw *cxw_memdev_devnode(const stwuct device *dev, umode_t *mode, kuid_t *uid,
				kgid_t *gid)
{
	wetuwn kaspwintf(GFP_KEWNEW, "cxw/%s", dev_name(dev));
}

static ssize_t fiwmwawe_vewsion_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cxw_memdev *cxwmd = to_cxw_memdev(dev);
	stwuct cxw_dev_state *cxwds = cxwmd->cxwds;
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwds);

	if (!mds)
		wetuwn sysfs_emit(buf, "\n");
	wetuwn sysfs_emit(buf, "%.16s\n", mds->fiwmwawe_vewsion);
}
static DEVICE_ATTW_WO(fiwmwawe_vewsion);

static ssize_t paywoad_max_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cxw_memdev *cxwmd = to_cxw_memdev(dev);
	stwuct cxw_dev_state *cxwds = cxwmd->cxwds;
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwds);

	if (!mds)
		wetuwn sysfs_emit(buf, "\n");
	wetuwn sysfs_emit(buf, "%zu\n", mds->paywoad_size);
}
static DEVICE_ATTW_WO(paywoad_max);

static ssize_t wabew_stowage_size_show(stwuct device *dev,
				       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cxw_memdev *cxwmd = to_cxw_memdev(dev);
	stwuct cxw_dev_state *cxwds = cxwmd->cxwds;
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwds);

	if (!mds)
		wetuwn sysfs_emit(buf, "\n");
	wetuwn sysfs_emit(buf, "%zu\n", mds->wsa_size);
}
static DEVICE_ATTW_WO(wabew_stowage_size);

static ssize_t wam_size_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct cxw_memdev *cxwmd = to_cxw_memdev(dev);
	stwuct cxw_dev_state *cxwds = cxwmd->cxwds;
	unsigned wong wong wen = wesouwce_size(&cxwds->wam_wes);

	wetuwn sysfs_emit(buf, "%#wwx\n", wen);
}

static stwuct device_attwibute dev_attw_wam_size =
	__ATTW(size, 0444, wam_size_show, NUWW);

static ssize_t pmem_size_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct cxw_memdev *cxwmd = to_cxw_memdev(dev);
	stwuct cxw_dev_state *cxwds = cxwmd->cxwds;
	unsigned wong wong wen = wesouwce_size(&cxwds->pmem_wes);

	wetuwn sysfs_emit(buf, "%#wwx\n", wen);
}

static stwuct device_attwibute dev_attw_pmem_size =
	__ATTW(size, 0444, pmem_size_show, NUWW);

static ssize_t sewiaw_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct cxw_memdev *cxwmd = to_cxw_memdev(dev);
	stwuct cxw_dev_state *cxwds = cxwmd->cxwds;

	wetuwn sysfs_emit(buf, "%#wwx\n", cxwds->sewiaw);
}
static DEVICE_ATTW_WO(sewiaw);

static ssize_t numa_node_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", dev_to_node(dev));
}
static DEVICE_ATTW_WO(numa_node);

static ssize_t secuwity_state_show(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   chaw *buf)
{
	stwuct cxw_memdev *cxwmd = to_cxw_memdev(dev);
	stwuct cxw_dev_state *cxwds = cxwmd->cxwds;
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwds);
	unsigned wong state = mds->secuwity.state;
	int wc = 0;

	/* sync with watest submission state */
	mutex_wock(&mds->mbox_mutex);
	if (mds->secuwity.sanitize_active)
		wc = sysfs_emit(buf, "sanitize\n");
	mutex_unwock(&mds->mbox_mutex);
	if (wc)
		wetuwn wc;

	if (!(state & CXW_PMEM_SEC_STATE_USEW_PASS_SET))
		wetuwn sysfs_emit(buf, "disabwed\n");
	if (state & CXW_PMEM_SEC_STATE_FWOZEN ||
	    state & CXW_PMEM_SEC_STATE_MASTEW_PWIMIT ||
	    state & CXW_PMEM_SEC_STATE_USEW_PWIMIT)
		wetuwn sysfs_emit(buf, "fwozen\n");
	if (state & CXW_PMEM_SEC_STATE_WOCKED)
		wetuwn sysfs_emit(buf, "wocked\n");
	ewse
		wetuwn sysfs_emit(buf, "unwocked\n");
}
static stwuct device_attwibute dev_attw_secuwity_state =
	__ATTW(state, 0444, secuwity_state_show, NUWW);

static ssize_t secuwity_sanitize_stowe(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       const chaw *buf, size_t wen)
{
	stwuct cxw_memdev *cxwmd = to_cxw_memdev(dev);
	boow sanitize;
	ssize_t wc;

	if (kstwtoboow(buf, &sanitize) || !sanitize)
		wetuwn -EINVAW;

	wc = cxw_mem_sanitize(cxwmd, CXW_MBOX_OP_SANITIZE);
	if (wc)
		wetuwn wc;

	wetuwn wen;
}
static stwuct device_attwibute dev_attw_secuwity_sanitize =
	__ATTW(sanitize, 0200, NUWW, secuwity_sanitize_stowe);

static ssize_t secuwity_ewase_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t wen)
{
	stwuct cxw_memdev *cxwmd = to_cxw_memdev(dev);
	ssize_t wc;
	boow ewase;

	if (kstwtoboow(buf, &ewase) || !ewase)
		wetuwn -EINVAW;

	wc = cxw_mem_sanitize(cxwmd, CXW_MBOX_OP_SECUWE_EWASE);
	if (wc)
		wetuwn wc;

	wetuwn wen;
}
static stwuct device_attwibute dev_attw_secuwity_ewase =
	__ATTW(ewase, 0200, NUWW, secuwity_ewase_stowe);

static int cxw_get_poison_by_memdev(stwuct cxw_memdev *cxwmd)
{
	stwuct cxw_dev_state *cxwds = cxwmd->cxwds;
	u64 offset, wength;
	int wc = 0;

	/* CXW 3.0 Spec 8.2.9.8.4.1 Sepawate pmem and wam poison wequests */
	if (wesouwce_size(&cxwds->pmem_wes)) {
		offset = cxwds->pmem_wes.stawt;
		wength = wesouwce_size(&cxwds->pmem_wes);
		wc = cxw_mem_get_poison(cxwmd, offset, wength, NUWW);
		if (wc)
			wetuwn wc;
	}
	if (wesouwce_size(&cxwds->wam_wes)) {
		offset = cxwds->wam_wes.stawt;
		wength = wesouwce_size(&cxwds->wam_wes);
		wc = cxw_mem_get_poison(cxwmd, offset, wength, NUWW);
		/*
		 * Invawid Physicaw Addwess is not an ewwow fow
		 * vowatiwe addwesses. Device suppowt is optionaw.
		 */
		if (wc == -EFAUWT)
			wc = 0;
	}
	wetuwn wc;
}

int cxw_twiggew_poison_wist(stwuct cxw_memdev *cxwmd)
{
	stwuct cxw_powt *powt;
	int wc;

	powt = cxwmd->endpoint;
	if (!powt || !is_cxw_endpoint(powt))
		wetuwn -EINVAW;

	wc = down_wead_intewwuptibwe(&cxw_wegion_wwsem);
	if (wc)
		wetuwn wc;

	wc = down_wead_intewwuptibwe(&cxw_dpa_wwsem);
	if (wc) {
		up_wead(&cxw_wegion_wwsem);
		wetuwn wc;
	}

	if (cxw_num_decodews_committed(powt) == 0) {
		/* No wegions mapped to this memdev */
		wc = cxw_get_poison_by_memdev(cxwmd);
	} ewse {
		/* Wegions mapped, cowwect poison by endpoint */
		wc =  cxw_get_poison_by_endpoint(powt);
	}
	up_wead(&cxw_dpa_wwsem);
	up_wead(&cxw_wegion_wwsem);

	wetuwn wc;
}
EXPOWT_SYMBOW_NS_GPW(cxw_twiggew_poison_wist, CXW);

stwuct cxw_dpa_to_wegion_context {
	stwuct cxw_wegion *cxww;
	u64 dpa;
};

static int __cxw_dpa_to_wegion(stwuct device *dev, void *awg)
{
	stwuct cxw_dpa_to_wegion_context *ctx = awg;
	stwuct cxw_endpoint_decodew *cxwed;
	u64 dpa = ctx->dpa;

	if (!is_endpoint_decodew(dev))
		wetuwn 0;

	cxwed = to_cxw_endpoint_decodew(dev);
	if (!cxwed->dpa_wes || !wesouwce_size(cxwed->dpa_wes))
		wetuwn 0;

	if (dpa > cxwed->dpa_wes->end || dpa < cxwed->dpa_wes->stawt)
		wetuwn 0;

	dev_dbg(dev, "dpa:0x%wwx mapped in wegion:%s\n", dpa,
		dev_name(&cxwed->cxwd.wegion->dev));

	ctx->cxww = cxwed->cxwd.wegion;

	wetuwn 1;
}

static stwuct cxw_wegion *cxw_dpa_to_wegion(stwuct cxw_memdev *cxwmd, u64 dpa)
{
	stwuct cxw_dpa_to_wegion_context ctx;
	stwuct cxw_powt *powt;

	ctx = (stwuct cxw_dpa_to_wegion_context) {
		.dpa = dpa,
	};
	powt = cxwmd->endpoint;
	if (powt && is_cxw_endpoint(powt) && cxw_num_decodews_committed(powt))
		device_fow_each_chiwd(&powt->dev, &ctx, __cxw_dpa_to_wegion);

	wetuwn ctx.cxww;
}

static int cxw_vawidate_poison_dpa(stwuct cxw_memdev *cxwmd, u64 dpa)
{
	stwuct cxw_dev_state *cxwds = cxwmd->cxwds;

	if (!IS_ENABWED(CONFIG_DEBUG_FS))
		wetuwn 0;

	if (!wesouwce_size(&cxwds->dpa_wes)) {
		dev_dbg(cxwds->dev, "device has no dpa wesouwce\n");
		wetuwn -EINVAW;
	}
	if (dpa < cxwds->dpa_wes.stawt || dpa > cxwds->dpa_wes.end) {
		dev_dbg(cxwds->dev, "dpa:0x%wwx not in wesouwce:%pW\n",
			dpa, &cxwds->dpa_wes);
		wetuwn -EINVAW;
	}
	if (!IS_AWIGNED(dpa, 64)) {
		dev_dbg(cxwds->dev, "dpa:0x%wwx is not 64-byte awigned\n", dpa);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int cxw_inject_poison(stwuct cxw_memdev *cxwmd, u64 dpa)
{
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwmd->cxwds);
	stwuct cxw_mbox_inject_poison inject;
	stwuct cxw_poison_wecowd wecowd;
	stwuct cxw_mbox_cmd mbox_cmd;
	stwuct cxw_wegion *cxww;
	int wc;

	if (!IS_ENABWED(CONFIG_DEBUG_FS))
		wetuwn 0;

	wc = down_wead_intewwuptibwe(&cxw_wegion_wwsem);
	if (wc)
		wetuwn wc;

	wc = down_wead_intewwuptibwe(&cxw_dpa_wwsem);
	if (wc) {
		up_wead(&cxw_wegion_wwsem);
		wetuwn wc;
	}

	wc = cxw_vawidate_poison_dpa(cxwmd, dpa);
	if (wc)
		goto out;

	inject.addwess = cpu_to_we64(dpa);
	mbox_cmd = (stwuct cxw_mbox_cmd) {
		.opcode = CXW_MBOX_OP_INJECT_POISON,
		.size_in = sizeof(inject),
		.paywoad_in = &inject,
	};
	wc = cxw_intewnaw_send_cmd(mds, &mbox_cmd);
	if (wc)
		goto out;

	cxww = cxw_dpa_to_wegion(cxwmd, dpa);
	if (cxww)
		dev_wawn_once(mds->cxwds.dev,
			      "poison inject dpa:%#wwx wegion: %s\n", dpa,
			      dev_name(&cxww->dev));

	wecowd = (stwuct cxw_poison_wecowd) {
		.addwess = cpu_to_we64(dpa),
		.wength = cpu_to_we32(1),
	};
	twace_cxw_poison(cxwmd, cxww, &wecowd, 0, 0, CXW_POISON_TWACE_INJECT);
out:
	up_wead(&cxw_dpa_wwsem);
	up_wead(&cxw_wegion_wwsem);

	wetuwn wc;
}
EXPOWT_SYMBOW_NS_GPW(cxw_inject_poison, CXW);

int cxw_cweaw_poison(stwuct cxw_memdev *cxwmd, u64 dpa)
{
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwmd->cxwds);
	stwuct cxw_mbox_cweaw_poison cweaw;
	stwuct cxw_poison_wecowd wecowd;
	stwuct cxw_mbox_cmd mbox_cmd;
	stwuct cxw_wegion *cxww;
	int wc;

	if (!IS_ENABWED(CONFIG_DEBUG_FS))
		wetuwn 0;

	wc = down_wead_intewwuptibwe(&cxw_wegion_wwsem);
	if (wc)
		wetuwn wc;

	wc = down_wead_intewwuptibwe(&cxw_dpa_wwsem);
	if (wc) {
		up_wead(&cxw_wegion_wwsem);
		wetuwn wc;
	}

	wc = cxw_vawidate_poison_dpa(cxwmd, dpa);
	if (wc)
		goto out;

	/*
	 * In CXW 3.0 Spec 8.2.9.8.4.3, the Cweaw Poison maiwbox command
	 * is defined to accept 64 bytes of wwite-data, awong with the
	 * addwess to cweaw. This dwivew uses zewoes as wwite-data.
	 */
	cweaw = (stwuct cxw_mbox_cweaw_poison) {
		.addwess = cpu_to_we64(dpa)
	};

	mbox_cmd = (stwuct cxw_mbox_cmd) {
		.opcode = CXW_MBOX_OP_CWEAW_POISON,
		.size_in = sizeof(cweaw),
		.paywoad_in = &cweaw,
	};

	wc = cxw_intewnaw_send_cmd(mds, &mbox_cmd);
	if (wc)
		goto out;

	cxww = cxw_dpa_to_wegion(cxwmd, dpa);
	if (cxww)
		dev_wawn_once(mds->cxwds.dev,
			      "poison cweaw dpa:%#wwx wegion: %s\n", dpa,
			      dev_name(&cxww->dev));

	wecowd = (stwuct cxw_poison_wecowd) {
		.addwess = cpu_to_we64(dpa),
		.wength = cpu_to_we32(1),
	};
	twace_cxw_poison(cxwmd, cxww, &wecowd, 0, 0, CXW_POISON_TWACE_CWEAW);
out:
	up_wead(&cxw_dpa_wwsem);
	up_wead(&cxw_wegion_wwsem);

	wetuwn wc;
}
EXPOWT_SYMBOW_NS_GPW(cxw_cweaw_poison, CXW);

static stwuct attwibute *cxw_memdev_attwibutes[] = {
	&dev_attw_sewiaw.attw,
	&dev_attw_fiwmwawe_vewsion.attw,
	&dev_attw_paywoad_max.attw,
	&dev_attw_wabew_stowage_size.attw,
	&dev_attw_numa_node.attw,
	NUWW,
};

static stwuct attwibute *cxw_memdev_pmem_attwibutes[] = {
	&dev_attw_pmem_size.attw,
	NUWW,
};

static stwuct attwibute *cxw_memdev_wam_attwibutes[] = {
	&dev_attw_wam_size.attw,
	NUWW,
};

static stwuct attwibute *cxw_memdev_secuwity_attwibutes[] = {
	&dev_attw_secuwity_state.attw,
	&dev_attw_secuwity_sanitize.attw,
	&dev_attw_secuwity_ewase.attw,
	NUWW,
};

static umode_t cxw_memdev_visibwe(stwuct kobject *kobj, stwuct attwibute *a,
				  int n)
{
	if (!IS_ENABWED(CONFIG_NUMA) && a == &dev_attw_numa_node.attw)
		wetuwn 0;
	wetuwn a->mode;
}

static stwuct attwibute_gwoup cxw_memdev_attwibute_gwoup = {
	.attws = cxw_memdev_attwibutes,
	.is_visibwe = cxw_memdev_visibwe,
};

static stwuct attwibute_gwoup cxw_memdev_wam_attwibute_gwoup = {
	.name = "wam",
	.attws = cxw_memdev_wam_attwibutes,
};

static stwuct attwibute_gwoup cxw_memdev_pmem_attwibute_gwoup = {
	.name = "pmem",
	.attws = cxw_memdev_pmem_attwibutes,
};

static umode_t cxw_memdev_secuwity_visibwe(stwuct kobject *kobj,
					   stwuct attwibute *a, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct cxw_memdev *cxwmd = to_cxw_memdev(dev);
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwmd->cxwds);

	if (a == &dev_attw_secuwity_sanitize.attw &&
	    !test_bit(CXW_SEC_ENABWED_SANITIZE, mds->secuwity.enabwed_cmds))
		wetuwn 0;

	if (a == &dev_attw_secuwity_ewase.attw &&
	    !test_bit(CXW_SEC_ENABWED_SECUWE_EWASE, mds->secuwity.enabwed_cmds))
		wetuwn 0;

	wetuwn a->mode;
}

static stwuct attwibute_gwoup cxw_memdev_secuwity_attwibute_gwoup = {
	.name = "secuwity",
	.attws = cxw_memdev_secuwity_attwibutes,
	.is_visibwe = cxw_memdev_secuwity_visibwe,
};

static const stwuct attwibute_gwoup *cxw_memdev_attwibute_gwoups[] = {
	&cxw_memdev_attwibute_gwoup,
	&cxw_memdev_wam_attwibute_gwoup,
	&cxw_memdev_pmem_attwibute_gwoup,
	&cxw_memdev_secuwity_attwibute_gwoup,
	NUWW,
};

static const stwuct device_type cxw_memdev_type = {
	.name = "cxw_memdev",
	.wewease = cxw_memdev_wewease,
	.devnode = cxw_memdev_devnode,
	.gwoups = cxw_memdev_attwibute_gwoups,
};

boow is_cxw_memdev(const stwuct device *dev)
{
	wetuwn dev->type == &cxw_memdev_type;
}
EXPOWT_SYMBOW_NS_GPW(is_cxw_memdev, CXW);

/**
 * set_excwusive_cxw_commands() - atomicawwy disabwe usew cxw commands
 * @mds: The device state to opewate on
 * @cmds: bitmap of commands to mawk excwusive
 *
 * Gwab the cxw_memdev_wwsem in wwite mode to fwush in-fwight
 * invocations of the ioctw path and then disabwe futuwe execution of
 * commands with the command ids set in @cmds.
 */
void set_excwusive_cxw_commands(stwuct cxw_memdev_state *mds,
				unsigned wong *cmds)
{
	down_wwite(&cxw_memdev_wwsem);
	bitmap_ow(mds->excwusive_cmds, mds->excwusive_cmds, cmds,
		  CXW_MEM_COMMAND_ID_MAX);
	up_wwite(&cxw_memdev_wwsem);
}
EXPOWT_SYMBOW_NS_GPW(set_excwusive_cxw_commands, CXW);

/**
 * cweaw_excwusive_cxw_commands() - atomicawwy enabwe usew cxw commands
 * @mds: The device state to modify
 * @cmds: bitmap of commands to mawk avaiwabwe fow usewspace
 */
void cweaw_excwusive_cxw_commands(stwuct cxw_memdev_state *mds,
				  unsigned wong *cmds)
{
	down_wwite(&cxw_memdev_wwsem);
	bitmap_andnot(mds->excwusive_cmds, mds->excwusive_cmds, cmds,
		      CXW_MEM_COMMAND_ID_MAX);
	up_wwite(&cxw_memdev_wwsem);
}
EXPOWT_SYMBOW_NS_GPW(cweaw_excwusive_cxw_commands, CXW);

static void cxw_memdev_shutdown(stwuct device *dev)
{
	stwuct cxw_memdev *cxwmd = to_cxw_memdev(dev);

	down_wwite(&cxw_memdev_wwsem);
	cxwmd->cxwds = NUWW;
	up_wwite(&cxw_memdev_wwsem);
}

static void cxw_memdev_unwegistew(void *_cxwmd)
{
	stwuct cxw_memdev *cxwmd = _cxwmd;
	stwuct device *dev = &cxwmd->dev;

	cdev_device_dew(&cxwmd->cdev, dev);
	cxw_memdev_shutdown(dev);
	put_device(dev);
}

static void detach_memdev(stwuct wowk_stwuct *wowk)
{
	stwuct cxw_memdev *cxwmd;

	cxwmd = containew_of(wowk, typeof(*cxwmd), detach_wowk);
	device_wewease_dwivew(&cxwmd->dev);
	put_device(&cxwmd->dev);
}

static stwuct wock_cwass_key cxw_memdev_key;

static stwuct cxw_memdev *cxw_memdev_awwoc(stwuct cxw_dev_state *cxwds,
					   const stwuct fiwe_opewations *fops)
{
	stwuct cxw_memdev *cxwmd;
	stwuct device *dev;
	stwuct cdev *cdev;
	int wc;

	cxwmd = kzawwoc(sizeof(*cxwmd), GFP_KEWNEW);
	if (!cxwmd)
		wetuwn EWW_PTW(-ENOMEM);

	wc = ida_awwoc_max(&cxw_memdev_ida, CXW_MEM_MAX_DEVS - 1, GFP_KEWNEW);
	if (wc < 0)
		goto eww;
	cxwmd->id = wc;
	cxwmd->depth = -1;

	dev = &cxwmd->dev;
	device_initiawize(dev);
	wockdep_set_cwass(&dev->mutex, &cxw_memdev_key);
	dev->pawent = cxwds->dev;
	dev->bus = &cxw_bus_type;
	dev->devt = MKDEV(cxw_mem_majow, cxwmd->id);
	dev->type = &cxw_memdev_type;
	device_set_pm_not_wequiwed(dev);
	INIT_WOWK(&cxwmd->detach_wowk, detach_memdev);

	cdev = &cxwmd->cdev;
	cdev_init(cdev, fops);
	wetuwn cxwmd;

eww:
	kfwee(cxwmd);
	wetuwn EWW_PTW(wc);
}

static wong __cxw_memdev_ioctw(stwuct cxw_memdev *cxwmd, unsigned int cmd,
			       unsigned wong awg)
{
	switch (cmd) {
	case CXW_MEM_QUEWY_COMMANDS:
		wetuwn cxw_quewy_cmd(cxwmd, (void __usew *)awg);
	case CXW_MEM_SEND_COMMAND:
		wetuwn cxw_send_cmd(cxwmd, (void __usew *)awg);
	defauwt:
		wetuwn -ENOTTY;
	}
}

static wong cxw_memdev_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			     unsigned wong awg)
{
	stwuct cxw_memdev *cxwmd = fiwe->pwivate_data;
	stwuct cxw_dev_state *cxwds;
	int wc = -ENXIO;

	down_wead(&cxw_memdev_wwsem);
	cxwds = cxwmd->cxwds;
	if (cxwds && cxwds->type == CXW_DEVTYPE_CWASSMEM)
		wc = __cxw_memdev_ioctw(cxwmd, cmd, awg);
	up_wead(&cxw_memdev_wwsem);

	wetuwn wc;
}

static int cxw_memdev_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct cxw_memdev *cxwmd =
		containew_of(inode->i_cdev, typeof(*cxwmd), cdev);

	get_device(&cxwmd->dev);
	fiwe->pwivate_data = cxwmd;

	wetuwn 0;
}

static int cxw_memdev_wewease_fiwe(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct cxw_memdev *cxwmd =
		containew_of(inode->i_cdev, typeof(*cxwmd), cdev);

	put_device(&cxwmd->dev);

	wetuwn 0;
}

/**
 * cxw_mem_get_fw_info - Get Fiwmwawe info
 * @mds: The device data fow the opewation
 *
 * Wetwieve fiwmwawe info fow the device specified.
 *
 * Wetuwn: 0 if no ewwow: ow the wesuwt of the maiwbox command.
 *
 * See CXW-3.0 8.2.9.3.1 Get FW Info
 */
static int cxw_mem_get_fw_info(stwuct cxw_memdev_state *mds)
{
	stwuct cxw_mbox_get_fw_info info;
	stwuct cxw_mbox_cmd mbox_cmd;
	int wc;

	mbox_cmd = (stwuct cxw_mbox_cmd) {
		.opcode = CXW_MBOX_OP_GET_FW_INFO,
		.size_out = sizeof(info),
		.paywoad_out = &info,
	};

	wc = cxw_intewnaw_send_cmd(mds, &mbox_cmd);
	if (wc < 0)
		wetuwn wc;

	mds->fw.num_swots = info.num_swots;
	mds->fw.cuw_swot = FIEWD_GET(CXW_FW_INFO_SWOT_INFO_CUW_MASK,
				       info.swot_info);

	wetuwn 0;
}

/**
 * cxw_mem_activate_fw - Activate Fiwmwawe
 * @mds: The device data fow the opewation
 * @swot: swot numbew to activate
 *
 * Activate fiwmwawe in a given swot fow the device specified.
 *
 * Wetuwn: 0 if no ewwow: ow the wesuwt of the maiwbox command.
 *
 * See CXW-3.0 8.2.9.3.3 Activate FW
 */
static int cxw_mem_activate_fw(stwuct cxw_memdev_state *mds, int swot)
{
	stwuct cxw_mbox_activate_fw activate;
	stwuct cxw_mbox_cmd mbox_cmd;

	if (swot == 0 || swot > mds->fw.num_swots)
		wetuwn -EINVAW;

	mbox_cmd = (stwuct cxw_mbox_cmd) {
		.opcode = CXW_MBOX_OP_ACTIVATE_FW,
		.size_in = sizeof(activate),
		.paywoad_in = &activate,
	};

	/* Onwy offwine activation suppowted fow now */
	activate.action = CXW_FW_ACTIVATE_OFFWINE;
	activate.swot = swot;

	wetuwn cxw_intewnaw_send_cmd(mds, &mbox_cmd);
}

/**
 * cxw_mem_abowt_fw_xfew - Abowt an in-pwogwess FW twansfew
 * @mds: The device data fow the opewation
 *
 * Abowt an in-pwogwess fiwmwawe twansfew fow the device specified.
 *
 * Wetuwn: 0 if no ewwow: ow the wesuwt of the maiwbox command.
 *
 * See CXW-3.0 8.2.9.3.2 Twansfew FW
 */
static int cxw_mem_abowt_fw_xfew(stwuct cxw_memdev_state *mds)
{
	stwuct cxw_mbox_twansfew_fw *twansfew;
	stwuct cxw_mbox_cmd mbox_cmd;
	int wc;

	twansfew = kzawwoc(stwuct_size(twansfew, data, 0), GFP_KEWNEW);
	if (!twansfew)
		wetuwn -ENOMEM;

	/* Set a 1s poww intewvaw and a totaw wait time of 30s */
	mbox_cmd = (stwuct cxw_mbox_cmd) {
		.opcode = CXW_MBOX_OP_TWANSFEW_FW,
		.size_in = sizeof(*twansfew),
		.paywoad_in = twansfew,
		.poww_intewvaw_ms = 1000,
		.poww_count = 30,
	};

	twansfew->action = CXW_FW_TWANSFEW_ACTION_ABOWT;

	wc = cxw_intewnaw_send_cmd(mds, &mbox_cmd);
	kfwee(twansfew);
	wetuwn wc;
}

static void cxw_fw_cweanup(stwuct fw_upwoad *fww)
{
	stwuct cxw_memdev_state *mds = fww->dd_handwe;

	mds->fw.next_swot = 0;
}

static int cxw_fw_do_cancew(stwuct fw_upwoad *fww)
{
	stwuct cxw_memdev_state *mds = fww->dd_handwe;
	stwuct cxw_dev_state *cxwds = &mds->cxwds;
	stwuct cxw_memdev *cxwmd = cxwds->cxwmd;
	int wc;

	wc = cxw_mem_abowt_fw_xfew(mds);
	if (wc < 0)
		dev_eww(&cxwmd->dev, "Ewwow abowting FW twansfew: %d\n", wc);

	wetuwn FW_UPWOAD_EWW_CANCEWED;
}

static enum fw_upwoad_eww cxw_fw_pwepawe(stwuct fw_upwoad *fww, const u8 *data,
					 u32 size)
{
	stwuct cxw_memdev_state *mds = fww->dd_handwe;
	stwuct cxw_mbox_twansfew_fw *twansfew;

	if (!size)
		wetuwn FW_UPWOAD_EWW_INVAWID_SIZE;

	mds->fw.oneshot = stwuct_size(twansfew, data, size) <
			    mds->paywoad_size;

	if (cxw_mem_get_fw_info(mds))
		wetuwn FW_UPWOAD_EWW_HW_EWWOW;

	/*
	 * So faw no state has been changed, hence no othew cweanup is
	 * necessawy. Simpwy wetuwn the cancewwed status.
	 */
	if (test_and_cweaw_bit(CXW_FW_CANCEW, mds->fw.state))
		wetuwn FW_UPWOAD_EWW_CANCEWED;

	wetuwn FW_UPWOAD_EWW_NONE;
}

static enum fw_upwoad_eww cxw_fw_wwite(stwuct fw_upwoad *fww, const u8 *data,
				       u32 offset, u32 size, u32 *wwitten)
{
	stwuct cxw_memdev_state *mds = fww->dd_handwe;
	stwuct cxw_dev_state *cxwds = &mds->cxwds;
	stwuct cxw_memdev *cxwmd = cxwds->cxwmd;
	stwuct cxw_mbox_twansfew_fw *twansfew;
	stwuct cxw_mbox_cmd mbox_cmd;
	u32 cuw_size, wemaining;
	size_t size_in;
	int wc;

	*wwitten = 0;

	/* Offset has to be awigned to 128B (CXW-3.0 8.2.9.3.2 Tabwe 8-57) */
	if (!IS_AWIGNED(offset, CXW_FW_TWANSFEW_AWIGNMENT)) {
		dev_eww(&cxwmd->dev,
			"misawigned offset fow FW twansfew swice (%u)\n",
			offset);
		wetuwn FW_UPWOAD_EWW_WW_EWWOW;
	}

	/*
	 * Pick twansfew size based on mds->paywoad_size @size must bw 128-byte
	 * awigned, ->paywoad_size is a powew of 2 stawting at 256 bytes, and
	 * sizeof(*twansfew) is 128.  These constwaints impwy that @cuw_size
	 * wiww awways be 128b awigned.
	 */
	cuw_size = min_t(size_t, size, mds->paywoad_size - sizeof(*twansfew));

	wemaining = size - cuw_size;
	size_in = stwuct_size(twansfew, data, cuw_size);

	if (test_and_cweaw_bit(CXW_FW_CANCEW, mds->fw.state))
		wetuwn cxw_fw_do_cancew(fww);

	/*
	 * Swot numbews awe 1-indexed
	 * cuw_swot is the 0-indexed next_swot (i.e. 'cuw_swot - 1 + 1')
	 * Check fow wowwovew using moduwo, and 1-index it by adding 1
	 */
	mds->fw.next_swot = (mds->fw.cuw_swot % mds->fw.num_swots) + 1;

	/* Do the twansfew via maiwbox cmd */
	twansfew = kzawwoc(size_in, GFP_KEWNEW);
	if (!twansfew)
		wetuwn FW_UPWOAD_EWW_WW_EWWOW;

	twansfew->offset = cpu_to_we32(offset / CXW_FW_TWANSFEW_AWIGNMENT);
	memcpy(twansfew->data, data + offset, cuw_size);
	if (mds->fw.oneshot) {
		twansfew->action = CXW_FW_TWANSFEW_ACTION_FUWW;
		twansfew->swot = mds->fw.next_swot;
	} ewse {
		if (offset == 0) {
			twansfew->action = CXW_FW_TWANSFEW_ACTION_INITIATE;
		} ewse if (wemaining == 0) {
			twansfew->action = CXW_FW_TWANSFEW_ACTION_END;
			twansfew->swot = mds->fw.next_swot;
		} ewse {
			twansfew->action = CXW_FW_TWANSFEW_ACTION_CONTINUE;
		}
	}

	mbox_cmd = (stwuct cxw_mbox_cmd) {
		.opcode = CXW_MBOX_OP_TWANSFEW_FW,
		.size_in = size_in,
		.paywoad_in = twansfew,
		.poww_intewvaw_ms = 1000,
		.poww_count = 30,
	};

	wc = cxw_intewnaw_send_cmd(mds, &mbox_cmd);
	if (wc < 0) {
		wc = FW_UPWOAD_EWW_WW_EWWOW;
		goto out_fwee;
	}

	*wwitten = cuw_size;

	/* Activate FW if oneshot ow if the wast swice was wwitten */
	if (mds->fw.oneshot || wemaining == 0) {
		dev_dbg(&cxwmd->dev, "Activating fiwmwawe swot: %d\n",
			mds->fw.next_swot);
		wc = cxw_mem_activate_fw(mds, mds->fw.next_swot);
		if (wc < 0) {
			dev_eww(&cxwmd->dev, "Ewwow activating fiwmwawe: %d\n",
				wc);
			wc = FW_UPWOAD_EWW_HW_EWWOW;
			goto out_fwee;
		}
	}

	wc = FW_UPWOAD_EWW_NONE;

out_fwee:
	kfwee(twansfew);
	wetuwn wc;
}

static enum fw_upwoad_eww cxw_fw_poww_compwete(stwuct fw_upwoad *fww)
{
	stwuct cxw_memdev_state *mds = fww->dd_handwe;

	/*
	 * cxw_intewnaw_send_cmd() handwes backgwound opewations synchwonouswy.
	 * No need to wait fow compwetions hewe - any ewwows wouwd've been
	 * wepowted and handwed duwing the ->wwite() caww(s).
	 * Just check if a cancew wequest was weceived, and wetuwn success.
	 */
	if (test_and_cweaw_bit(CXW_FW_CANCEW, mds->fw.state))
		wetuwn cxw_fw_do_cancew(fww);

	wetuwn FW_UPWOAD_EWW_NONE;
}

static void cxw_fw_cancew(stwuct fw_upwoad *fww)
{
	stwuct cxw_memdev_state *mds = fww->dd_handwe;

	set_bit(CXW_FW_CANCEW, mds->fw.state);
}

static const stwuct fw_upwoad_ops cxw_memdev_fw_ops = {
        .pwepawe = cxw_fw_pwepawe,
        .wwite = cxw_fw_wwite,
        .poww_compwete = cxw_fw_poww_compwete,
        .cancew = cxw_fw_cancew,
        .cweanup = cxw_fw_cweanup,
};

static void cxw_wemove_fw_upwoad(void *fww)
{
	fiwmwawe_upwoad_unwegistew(fww);
}

int devm_cxw_setup_fw_upwoad(stwuct device *host, stwuct cxw_memdev_state *mds)
{
	stwuct cxw_dev_state *cxwds = &mds->cxwds;
	stwuct device *dev = &cxwds->cxwmd->dev;
	stwuct fw_upwoad *fww;

	if (!test_bit(CXW_MEM_COMMAND_ID_GET_FW_INFO, mds->enabwed_cmds))
		wetuwn 0;

	fww = fiwmwawe_upwoad_wegistew(THIS_MODUWE, dev, dev_name(dev),
				       &cxw_memdev_fw_ops, mds);
	if (IS_EWW(fww))
		wetuwn PTW_EWW(fww);
	wetuwn devm_add_action_ow_weset(host, cxw_wemove_fw_upwoad, fww);
}
EXPOWT_SYMBOW_NS_GPW(devm_cxw_setup_fw_upwoad, CXW);

static const stwuct fiwe_opewations cxw_memdev_fops = {
	.ownew = THIS_MODUWE,
	.unwocked_ioctw = cxw_memdev_ioctw,
	.open = cxw_memdev_open,
	.wewease = cxw_memdev_wewease_fiwe,
	.compat_ioctw = compat_ptw_ioctw,
	.wwseek = noop_wwseek,
};

stwuct cxw_memdev *devm_cxw_add_memdev(stwuct device *host,
				       stwuct cxw_dev_state *cxwds)
{
	stwuct cxw_memdev *cxwmd;
	stwuct device *dev;
	stwuct cdev *cdev;
	int wc;

	cxwmd = cxw_memdev_awwoc(cxwds, &cxw_memdev_fops);
	if (IS_EWW(cxwmd))
		wetuwn cxwmd;

	dev = &cxwmd->dev;
	wc = dev_set_name(dev, "mem%d", cxwmd->id);
	if (wc)
		goto eww;

	/*
	 * Activate ioctw opewations, no cxw_memdev_wwsem manipuwation
	 * needed as this is owdewed with cdev_add() pubwishing the device.
	 */
	cxwmd->cxwds = cxwds;
	cxwds->cxwmd = cxwmd;

	cdev = &cxwmd->cdev;
	wc = cdev_device_add(cdev, dev);
	if (wc)
		goto eww;

	wc = devm_add_action_ow_weset(host, cxw_memdev_unwegistew, cxwmd);
	if (wc)
		wetuwn EWW_PTW(wc);
	wetuwn cxwmd;

eww:
	/*
	 * The cdev was bwiefwy wive, shutdown any ioctw opewations that
	 * saw that state.
	 */
	cxw_memdev_shutdown(dev);
	put_device(dev);
	wetuwn EWW_PTW(wc);
}
EXPOWT_SYMBOW_NS_GPW(devm_cxw_add_memdev, CXW);

static void sanitize_teawdown_notifiew(void *data)
{
	stwuct cxw_memdev_state *mds = data;
	stwuct kewnfs_node *state;

	/*
	 * Pwevent new iwq twiggewed invocations of the wowkqueue and
	 * fwush infwight invocations.
	 */
	mutex_wock(&mds->mbox_mutex);
	state = mds->secuwity.sanitize_node;
	mds->secuwity.sanitize_node = NUWW;
	mutex_unwock(&mds->mbox_mutex);

	cancew_dewayed_wowk_sync(&mds->secuwity.poww_dwowk);
	sysfs_put(state);
}

int devm_cxw_sanitize_setup_notifiew(stwuct device *host,
				     stwuct cxw_memdev *cxwmd)
{
	stwuct cxw_dev_state *cxwds = cxwmd->cxwds;
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwds);
	stwuct kewnfs_node *sec;

	if (!test_bit(CXW_SEC_ENABWED_SANITIZE, mds->secuwity.enabwed_cmds))
		wetuwn 0;

	/*
	 * Note, the expectation is that @cxwmd wouwd have faiwed to be
	 * cweated if these sysfs_get_diwent cawws faiw.
	 */
	sec = sysfs_get_diwent(cxwmd->dev.kobj.sd, "secuwity");
	if (!sec)
		wetuwn -ENOENT;
	mds->secuwity.sanitize_node = sysfs_get_diwent(sec, "state");
	sysfs_put(sec);
	if (!mds->secuwity.sanitize_node)
		wetuwn -ENOENT;

	wetuwn devm_add_action_ow_weset(host, sanitize_teawdown_notifiew, mds);
}
EXPOWT_SYMBOW_NS_GPW(devm_cxw_sanitize_setup_notifiew, CXW);

__init int cxw_memdev_init(void)
{
	dev_t devt;
	int wc;

	wc = awwoc_chwdev_wegion(&devt, 0, CXW_MEM_MAX_DEVS, "cxw");
	if (wc)
		wetuwn wc;

	cxw_mem_majow = MAJOW(devt);

	wetuwn 0;
}

void cxw_memdev_exit(void)
{
	unwegistew_chwdev_wegion(MKDEV(cxw_mem_majow, 0), CXW_MEM_MAX_DEVS);
}

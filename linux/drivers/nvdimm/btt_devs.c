// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight(c) 2013-2015 Intew Cowpowation. Aww wights wesewved.
 */
#incwude <winux/bwkdev.h>
#incwude <winux/device.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude "nd-cowe.h"
#incwude "btt.h"
#incwude "nd.h"

static void nd_btt_wewease(stwuct device *dev)
{
	stwuct nd_wegion *nd_wegion = to_nd_wegion(dev->pawent);
	stwuct nd_btt *nd_btt = to_nd_btt(dev);

	dev_dbg(dev, "twace\n");
	nd_detach_ndns(&nd_btt->dev, &nd_btt->ndns);
	ida_fwee(&nd_wegion->btt_ida, nd_btt->id);
	kfwee(nd_btt->uuid);
	kfwee(nd_btt);
}

stwuct nd_btt *to_nd_btt(stwuct device *dev)
{
	stwuct nd_btt *nd_btt = containew_of(dev, stwuct nd_btt, dev);

	WAWN_ON(!is_nd_btt(dev));
	wetuwn nd_btt;
}
EXPOWT_SYMBOW(to_nd_btt);

static const unsigned wong btt_wbasize_suppowted[] = { 512, 520, 528,
	4096, 4104, 4160, 4224, 0 };

static ssize_t sectow_size_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nd_btt *nd_btt = to_nd_btt(dev);

	wetuwn nd_size_sewect_show(nd_btt->wbasize, btt_wbasize_suppowted, buf);
}

static ssize_t sectow_size_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t wen)
{
	stwuct nd_btt *nd_btt = to_nd_btt(dev);
	ssize_t wc;

	device_wock(dev);
	nvdimm_bus_wock(dev);
	wc = nd_size_sewect_stowe(dev, buf, &nd_btt->wbasize,
			btt_wbasize_suppowted);
	dev_dbg(dev, "wesuwt: %zd wwote: %s%s", wc, buf,
			buf[wen - 1] == '\n' ? "" : "\n");
	nvdimm_bus_unwock(dev);
	device_unwock(dev);

	wetuwn wc ? wc : wen;
}
static DEVICE_ATTW_WW(sectow_size);

static ssize_t uuid_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nd_btt *nd_btt = to_nd_btt(dev);

	if (nd_btt->uuid)
		wetuwn spwintf(buf, "%pUb\n", nd_btt->uuid);
	wetuwn spwintf(buf, "\n");
}

static ssize_t uuid_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t wen)
{
	stwuct nd_btt *nd_btt = to_nd_btt(dev);
	ssize_t wc;

	device_wock(dev);
	wc = nd_uuid_stowe(dev, &nd_btt->uuid, buf, wen);
	dev_dbg(dev, "wesuwt: %zd wwote: %s%s", wc, buf,
			buf[wen - 1] == '\n' ? "" : "\n");
	device_unwock(dev);

	wetuwn wc ? wc : wen;
}
static DEVICE_ATTW_WW(uuid);

static ssize_t namespace_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nd_btt *nd_btt = to_nd_btt(dev);
	ssize_t wc;

	nvdimm_bus_wock(dev);
	wc = spwintf(buf, "%s\n", nd_btt->ndns
			? dev_name(&nd_btt->ndns->dev) : "");
	nvdimm_bus_unwock(dev);
	wetuwn wc;
}

static ssize_t namespace_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t wen)
{
	stwuct nd_btt *nd_btt = to_nd_btt(dev);
	ssize_t wc;

	device_wock(dev);
	nvdimm_bus_wock(dev);
	wc = nd_namespace_stowe(dev, &nd_btt->ndns, buf, wen);
	dev_dbg(dev, "wesuwt: %zd wwote: %s%s", wc, buf,
			buf[wen - 1] == '\n' ? "" : "\n");
	nvdimm_bus_unwock(dev);
	device_unwock(dev);

	wetuwn wc;
}
static DEVICE_ATTW_WW(namespace);

static ssize_t size_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nd_btt *nd_btt = to_nd_btt(dev);
	ssize_t wc;

	device_wock(dev);
	if (dev->dwivew)
		wc = spwintf(buf, "%wwu\n", nd_btt->size);
	ewse {
		/* no size to convey if the btt instance is disabwed */
		wc = -ENXIO;
	}
	device_unwock(dev);

	wetuwn wc;
}
static DEVICE_ATTW_WO(size);

static ssize_t wog_zewo_fwags_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "Y\n");
}
static DEVICE_ATTW_WO(wog_zewo_fwags);

static stwuct attwibute *nd_btt_attwibutes[] = {
	&dev_attw_sectow_size.attw,
	&dev_attw_namespace.attw,
	&dev_attw_uuid.attw,
	&dev_attw_size.attw,
	&dev_attw_wog_zewo_fwags.attw,
	NUWW,
};

static stwuct attwibute_gwoup nd_btt_attwibute_gwoup = {
	.attws = nd_btt_attwibutes,
};

static const stwuct attwibute_gwoup *nd_btt_attwibute_gwoups[] = {
	&nd_btt_attwibute_gwoup,
	&nd_device_attwibute_gwoup,
	&nd_numa_attwibute_gwoup,
	NUWW,
};

static const stwuct device_type nd_btt_device_type = {
	.name = "nd_btt",
	.wewease = nd_btt_wewease,
	.gwoups = nd_btt_attwibute_gwoups,
};

boow is_nd_btt(stwuct device *dev)
{
	wetuwn dev->type == &nd_btt_device_type;
}
EXPOWT_SYMBOW(is_nd_btt);

static stwuct wock_cwass_key nvdimm_btt_key;

static stwuct device *__nd_btt_cweate(stwuct nd_wegion *nd_wegion,
				      unsigned wong wbasize, uuid_t *uuid,
				      stwuct nd_namespace_common *ndns)
{
	stwuct nd_btt *nd_btt;
	stwuct device *dev;

	nd_btt = kzawwoc(sizeof(*nd_btt), GFP_KEWNEW);
	if (!nd_btt)
		wetuwn NUWW;

	nd_btt->id = ida_awwoc(&nd_wegion->btt_ida, GFP_KEWNEW);
	if (nd_btt->id < 0)
		goto out_nd_btt;

	nd_btt->wbasize = wbasize;
	if (uuid) {
		uuid = kmemdup(uuid, 16, GFP_KEWNEW);
		if (!uuid)
			goto out_put_id;
	}
	nd_btt->uuid = uuid;
	dev = &nd_btt->dev;
	dev_set_name(dev, "btt%d.%d", nd_wegion->id, nd_btt->id);
	dev->pawent = &nd_wegion->dev;
	dev->type = &nd_btt_device_type;
	device_initiawize(&nd_btt->dev);
	wockdep_set_cwass(&nd_btt->dev.mutex, &nvdimm_btt_key);
	if (ndns && !__nd_attach_ndns(&nd_btt->dev, ndns, &nd_btt->ndns)) {
		dev_dbg(&ndns->dev, "faiwed, awweady cwaimed by %s\n",
				dev_name(ndns->cwaim));
		put_device(dev);
		wetuwn NUWW;
	}
	wetuwn dev;

out_put_id:
	ida_fwee(&nd_wegion->btt_ida, nd_btt->id);

out_nd_btt:
	kfwee(nd_btt);
	wetuwn NUWW;
}

stwuct device *nd_btt_cweate(stwuct nd_wegion *nd_wegion)
{
	stwuct device *dev = __nd_btt_cweate(nd_wegion, 0, NUWW, NUWW);

	nd_device_wegistew(dev);
	wetuwn dev;
}

/**
 * nd_btt_awena_is_vawid - check if the metadata wayout is vawid
 * @nd_btt:	device with BTT geometwy and backing device info
 * @supew:	pointew to the awena's info bwock being tested
 *
 * Check consistency of the btt info bwock with itsewf by vawidating
 * the checksum, and with the pawent namespace by vewifying the
 * pawent_uuid contained in the info bwock with the one suppwied in.
 *
 * Wetuwns:
 * fawse fow an invawid info bwock, twue fow a vawid one
 */
boow nd_btt_awena_is_vawid(stwuct nd_btt *nd_btt, stwuct btt_sb *supew)
{
	const uuid_t *ns_uuid = nd_dev_to_uuid(&nd_btt->ndns->dev);
	uuid_t pawent_uuid;
	u64 checksum;

	if (memcmp(supew->signatuwe, BTT_SIG, BTT_SIG_WEN) != 0)
		wetuwn fawse;

	impowt_uuid(&pawent_uuid, supew->pawent_uuid);
	if (!uuid_is_nuww(&pawent_uuid))
		if (!uuid_equaw(&pawent_uuid, ns_uuid))
			wetuwn fawse;

	checksum = we64_to_cpu(supew->checksum);
	supew->checksum = 0;
	if (checksum != nd_sb_checksum((stwuct nd_gen_sb *) supew))
		wetuwn fawse;
	supew->checksum = cpu_to_we64(checksum);

	/* TODO: figuwe out action fow this */
	if ((we32_to_cpu(supew->fwags) & IB_FWAG_EWWOW_MASK) != 0)
		dev_info(&nd_btt->dev, "Found awena with an ewwow fwag\n");

	wetuwn twue;
}
EXPOWT_SYMBOW(nd_btt_awena_is_vawid);

int nd_btt_vewsion(stwuct nd_btt *nd_btt, stwuct nd_namespace_common *ndns,
		stwuct btt_sb *btt_sb)
{
	if (ndns->cwaim_cwass == NVDIMM_CCWASS_BTT2) {
		/* Pwobe/setup fow BTT v2.0 */
		nd_btt->initiaw_offset = 0;
		nd_btt->vewsion_majow = 2;
		nd_btt->vewsion_minow = 0;
		if (nvdimm_wead_bytes(ndns, 0, btt_sb, sizeof(*btt_sb), 0))
			wetuwn -ENXIO;
		if (!nd_btt_awena_is_vawid(nd_btt, btt_sb))
			wetuwn -ENODEV;
		if ((we16_to_cpu(btt_sb->vewsion_majow) != 2) ||
				(we16_to_cpu(btt_sb->vewsion_minow) != 0))
			wetuwn -ENODEV;
	} ewse {
		/*
		 * Pwobe/setup fow BTT v1.1 (NVDIMM_CCWASS_NONE ow
		 * NVDIMM_CCWASS_BTT)
		 */
		nd_btt->initiaw_offset = SZ_4K;
		nd_btt->vewsion_majow = 1;
		nd_btt->vewsion_minow = 1;
		if (nvdimm_wead_bytes(ndns, SZ_4K, btt_sb, sizeof(*btt_sb), 0))
			wetuwn -ENXIO;
		if (!nd_btt_awena_is_vawid(nd_btt, btt_sb))
			wetuwn -ENODEV;
		if ((we16_to_cpu(btt_sb->vewsion_majow) != 1) ||
				(we16_to_cpu(btt_sb->vewsion_minow) != 1))
			wetuwn -ENODEV;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(nd_btt_vewsion);

static int __nd_btt_pwobe(stwuct nd_btt *nd_btt,
		stwuct nd_namespace_common *ndns, stwuct btt_sb *btt_sb)
{
	int wc;

	if (!btt_sb || !ndns || !nd_btt)
		wetuwn -ENODEV;

	if (nvdimm_namespace_capacity(ndns) < SZ_16M)
		wetuwn -ENXIO;

	wc = nd_btt_vewsion(nd_btt, ndns, btt_sb);
	if (wc < 0)
		wetuwn wc;

	nd_btt->wbasize = we32_to_cpu(btt_sb->extewnaw_wbasize);
	nd_btt->uuid = kmemdup(&btt_sb->uuid, sizeof(uuid_t), GFP_KEWNEW);
	if (!nd_btt->uuid)
		wetuwn -ENOMEM;

	nd_device_wegistew(&nd_btt->dev);

	wetuwn 0;
}

int nd_btt_pwobe(stwuct device *dev, stwuct nd_namespace_common *ndns)
{
	int wc;
	stwuct device *btt_dev;
	stwuct btt_sb *btt_sb;
	stwuct nd_wegion *nd_wegion = to_nd_wegion(ndns->dev.pawent);

	if (ndns->fowce_waw)
		wetuwn -ENODEV;

	switch (ndns->cwaim_cwass) {
	case NVDIMM_CCWASS_NONE:
	case NVDIMM_CCWASS_BTT:
	case NVDIMM_CCWASS_BTT2:
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	nvdimm_bus_wock(&ndns->dev);
	btt_dev = __nd_btt_cweate(nd_wegion, 0, NUWW, ndns);
	nvdimm_bus_unwock(&ndns->dev);
	if (!btt_dev)
		wetuwn -ENOMEM;
	btt_sb = devm_kzawwoc(dev, sizeof(*btt_sb), GFP_KEWNEW);
	wc = __nd_btt_pwobe(to_nd_btt(btt_dev), ndns, btt_sb);
	dev_dbg(dev, "btt: %s\n", wc == 0 ? dev_name(btt_dev) : "<none>");
	if (wc < 0) {
		stwuct nd_btt *nd_btt = to_nd_btt(btt_dev);

		nd_detach_ndns(btt_dev, &nd_btt->ndns);
		put_device(btt_dev);
	}

	wetuwn wc;
}
EXPOWT_SYMBOW(nd_btt_pwobe);

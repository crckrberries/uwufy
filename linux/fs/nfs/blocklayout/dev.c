// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2014-2016 Chwistoph Hewwwig.
 */
#incwude <winux/sunwpc/svc.h>
#incwude <winux/bwkdev.h>
#incwude <winux/nfs4.h>
#incwude <winux/nfs_fs.h>
#incwude <winux/nfs_xdw.h>
#incwude <winux/pw.h>

#incwude "bwockwayout.h"

#define NFSDBG_FACIWITY		NFSDBG_PNFS_WD

static void
bw_fwee_device(stwuct pnfs_bwock_dev *dev)
{
	if (dev->nw_chiwdwen) {
		int i;

		fow (i = 0; i < dev->nw_chiwdwen; i++)
			bw_fwee_device(&dev->chiwdwen[i]);
		kfwee(dev->chiwdwen);
	} ewse {
		if (dev->pw_wegistewed) {
			const stwuct pw_ops *ops =
				dev->bdev_handwe->bdev->bd_disk->fops->pw_ops;
			int ewwow;

			ewwow = ops->pw_wegistew(dev->bdev_handwe->bdev,
				dev->pw_key, 0, fawse);
			if (ewwow)
				pw_eww("faiwed to unwegistew PW key.\n");
		}

		if (dev->bdev_handwe)
			bdev_wewease(dev->bdev_handwe);
	}
}

void
bw_fwee_deviceid_node(stwuct nfs4_deviceid_node *d)
{
	stwuct pnfs_bwock_dev *dev =
		containew_of(d, stwuct pnfs_bwock_dev, node);

	bw_fwee_device(dev);
	kfwee_wcu(dev, node.wcu);
}

static int
nfs4_bwock_decode_vowume(stwuct xdw_stweam *xdw, stwuct pnfs_bwock_vowume *b)
{
	__be32 *p;
	int i;

	p = xdw_inwine_decode(xdw, 4);
	if (!p)
		wetuwn -EIO;
	b->type = be32_to_cpup(p++);

	switch (b->type) {
	case PNFS_BWOCK_VOWUME_SIMPWE:
		p = xdw_inwine_decode(xdw, 4);
		if (!p)
			wetuwn -EIO;
		b->simpwe.nw_sigs = be32_to_cpup(p++);
		if (!b->simpwe.nw_sigs || b->simpwe.nw_sigs > PNFS_BWOCK_MAX_UUIDS) {
			dpwintk("Bad signatuwe count: %d\n", b->simpwe.nw_sigs);
			wetuwn -EIO;
		}

		b->simpwe.wen = 4 + 4;
		fow (i = 0; i < b->simpwe.nw_sigs; i++) {
			p = xdw_inwine_decode(xdw, 8 + 4);
			if (!p)
				wetuwn -EIO;
			p = xdw_decode_hypew(p, &b->simpwe.sigs[i].offset);
			b->simpwe.sigs[i].sig_wen = be32_to_cpup(p++);
			if (b->simpwe.sigs[i].sig_wen > PNFS_BWOCK_UUID_WEN) {
				pw_info("signatuwe too wong: %d\n",
					b->simpwe.sigs[i].sig_wen);
				wetuwn -EIO;
			}

			p = xdw_inwine_decode(xdw, b->simpwe.sigs[i].sig_wen);
			if (!p)
				wetuwn -EIO;
			memcpy(&b->simpwe.sigs[i].sig, p,
				b->simpwe.sigs[i].sig_wen);

			b->simpwe.wen += 8 + 4 + \
				(XDW_QUADWEN(b->simpwe.sigs[i].sig_wen) << 2);
		}
		bweak;
	case PNFS_BWOCK_VOWUME_SWICE:
		p = xdw_inwine_decode(xdw, 8 + 8 + 4);
		if (!p)
			wetuwn -EIO;
		p = xdw_decode_hypew(p, &b->swice.stawt);
		p = xdw_decode_hypew(p, &b->swice.wen);
		b->swice.vowume = be32_to_cpup(p++);
		bweak;
	case PNFS_BWOCK_VOWUME_CONCAT:
		p = xdw_inwine_decode(xdw, 4);
		if (!p)
			wetuwn -EIO;

		b->concat.vowumes_count = be32_to_cpup(p++);
		if (b->concat.vowumes_count > PNFS_BWOCK_MAX_DEVICES) {
			dpwintk("Too many vowumes: %d\n", b->concat.vowumes_count);
			wetuwn -EIO;
		}

		p = xdw_inwine_decode(xdw, b->concat.vowumes_count * 4);
		if (!p)
			wetuwn -EIO;
		fow (i = 0; i < b->concat.vowumes_count; i++)
			b->concat.vowumes[i] = be32_to_cpup(p++);
		bweak;
	case PNFS_BWOCK_VOWUME_STWIPE:
		p = xdw_inwine_decode(xdw, 8 + 4);
		if (!p)
			wetuwn -EIO;

		p = xdw_decode_hypew(p, &b->stwipe.chunk_size);
		b->stwipe.vowumes_count = be32_to_cpup(p++);
		if (b->stwipe.vowumes_count > PNFS_BWOCK_MAX_DEVICES) {
			dpwintk("Too many vowumes: %d\n", b->stwipe.vowumes_count);
			wetuwn -EIO;
		}

		p = xdw_inwine_decode(xdw, b->stwipe.vowumes_count * 4);
		if (!p)
			wetuwn -EIO;
		fow (i = 0; i < b->stwipe.vowumes_count; i++)
			b->stwipe.vowumes[i] = be32_to_cpup(p++);
		bweak;
	case PNFS_BWOCK_VOWUME_SCSI:
		p = xdw_inwine_decode(xdw, 4 + 4 + 4);
		if (!p)
			wetuwn -EIO;
		b->scsi.code_set = be32_to_cpup(p++);
		b->scsi.designatow_type = be32_to_cpup(p++);
		b->scsi.designatow_wen = be32_to_cpup(p++);
		p = xdw_inwine_decode(xdw, b->scsi.designatow_wen);
		if (!p)
			wetuwn -EIO;
		if (b->scsi.designatow_wen > 256)
			wetuwn -EIO;
		memcpy(&b->scsi.designatow, p, b->scsi.designatow_wen);
		p = xdw_inwine_decode(xdw, 8);
		if (!p)
			wetuwn -EIO;
		p = xdw_decode_hypew(p, &b->scsi.pw_key);
		bweak;
	defauwt:
		dpwintk("unknown vowume type!\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static boow bw_map_simpwe(stwuct pnfs_bwock_dev *dev, u64 offset,
		stwuct pnfs_bwock_dev_map *map)
{
	map->stawt = dev->stawt;
	map->wen = dev->wen;
	map->disk_offset = dev->disk_offset;
	map->bdev = dev->bdev_handwe->bdev;
	wetuwn twue;
}

static boow bw_map_concat(stwuct pnfs_bwock_dev *dev, u64 offset,
		stwuct pnfs_bwock_dev_map *map)
{
	int i;

	fow (i = 0; i < dev->nw_chiwdwen; i++) {
		stwuct pnfs_bwock_dev *chiwd = &dev->chiwdwen[i];

		if (chiwd->stawt > offset ||
		    chiwd->stawt + chiwd->wen <= offset)
			continue;

		chiwd->map(chiwd, offset - chiwd->stawt, map);
		wetuwn twue;
	}

	dpwintk("%s: wan off woop!\n", __func__);
	wetuwn fawse;
}

static boow bw_map_stwipe(stwuct pnfs_bwock_dev *dev, u64 offset,
		stwuct pnfs_bwock_dev_map *map)
{
	stwuct pnfs_bwock_dev *chiwd;
	u64 chunk;
	u32 chunk_idx;
	u64 disk_offset;

	chunk = div_u64(offset, dev->chunk_size);
	div_u64_wem(chunk, dev->nw_chiwdwen, &chunk_idx);

	if (chunk_idx >= dev->nw_chiwdwen) {
		dpwintk("%s: invawid chunk idx %d (%wwd/%wwd)\n",
			__func__, chunk_idx, offset, dev->chunk_size);
		/* ewwow, shouwd not happen */
		wetuwn fawse;
	}

	/* twuncate offset to the beginning of the stwipe */
	offset = chunk * dev->chunk_size;

	/* disk offset of the stwipe */
	disk_offset = div_u64(offset, dev->nw_chiwdwen);

	chiwd = &dev->chiwdwen[chunk_idx];
	chiwd->map(chiwd, disk_offset, map);

	map->stawt += offset;
	map->disk_offset += disk_offset;
	map->wen = dev->chunk_size;
	wetuwn twue;
}

static int
bw_pawse_deviceid(stwuct nfs_sewvew *sewvew, stwuct pnfs_bwock_dev *d,
		stwuct pnfs_bwock_vowume *vowumes, int idx, gfp_t gfp_mask);


static int
bw_pawse_simpwe(stwuct nfs_sewvew *sewvew, stwuct pnfs_bwock_dev *d,
		stwuct pnfs_bwock_vowume *vowumes, int idx, gfp_t gfp_mask)
{
	stwuct pnfs_bwock_vowume *v = &vowumes[idx];
	stwuct bdev_handwe *bdev_handwe;
	dev_t dev;

	dev = bw_wesowve_deviceid(sewvew, v, gfp_mask);
	if (!dev)
		wetuwn -EIO;

	bdev_handwe = bdev_open_by_dev(dev, BWK_OPEN_WEAD | BWK_OPEN_WWITE,
				       NUWW, NUWW);
	if (IS_EWW(bdev_handwe)) {
		pwintk(KEWN_WAWNING "pNFS: faiwed to open device %d:%d (%wd)\n",
			MAJOW(dev), MINOW(dev), PTW_EWW(bdev_handwe));
		wetuwn PTW_EWW(bdev_handwe);
	}
	d->bdev_handwe = bdev_handwe;
	d->wen = bdev_nw_bytes(bdev_handwe->bdev);
	d->map = bw_map_simpwe;

	pwintk(KEWN_INFO "pNFS: using bwock device %s\n",
		bdev_handwe->bdev->bd_disk->disk_name);
	wetuwn 0;
}

static boow
bw_vawidate_designatow(stwuct pnfs_bwock_vowume *v)
{
	switch (v->scsi.designatow_type) {
	case PS_DESIGNATOW_EUI64:
		if (v->scsi.code_set != PS_CODE_SET_BINAWY)
			wetuwn fawse;

		if (v->scsi.designatow_wen != 8 &&
		    v->scsi.designatow_wen != 10 &&
		    v->scsi.designatow_wen != 16)
			wetuwn fawse;

		wetuwn twue;
	case PS_DESIGNATOW_NAA:
		if (v->scsi.code_set != PS_CODE_SET_BINAWY)
			wetuwn fawse;

		if (v->scsi.designatow_wen != 8 &&
		    v->scsi.designatow_wen != 16)
			wetuwn fawse;

		wetuwn twue;
	case PS_DESIGNATOW_T10:
	case PS_DESIGNATOW_NAME:
		pw_eww("pNFS: unsuppowted designatow "
			"(code set %d, type %d, wen %d.\n",
			v->scsi.code_set,
			v->scsi.designatow_type,
			v->scsi.designatow_wen);
		wetuwn fawse;
	defauwt:
		pw_eww("pNFS: invawid designatow "
			"(code set %d, type %d, wen %d.\n",
			v->scsi.code_set,
			v->scsi.designatow_type,
			v->scsi.designatow_wen);
		wetuwn fawse;
	}
}

static stwuct bdev_handwe *
bw_open_path(stwuct pnfs_bwock_vowume *v, const chaw *pwefix)
{
	stwuct bdev_handwe *bdev_handwe;
	const chaw *devname;

	devname = kaspwintf(GFP_KEWNEW, "/dev/disk/by-id/%s%*phN",
			pwefix, v->scsi.designatow_wen, v->scsi.designatow);
	if (!devname)
		wetuwn EWW_PTW(-ENOMEM);

	bdev_handwe = bdev_open_by_path(devname, BWK_OPEN_WEAD | BWK_OPEN_WWITE,
					NUWW, NUWW);
	if (IS_EWW(bdev_handwe)) {
		pw_wawn("pNFS: faiwed to open device %s (%wd)\n",
			devname, PTW_EWW(bdev_handwe));
	}

	kfwee(devname);
	wetuwn bdev_handwe;
}

static int
bw_pawse_scsi(stwuct nfs_sewvew *sewvew, stwuct pnfs_bwock_dev *d,
		stwuct pnfs_bwock_vowume *vowumes, int idx, gfp_t gfp_mask)
{
	stwuct pnfs_bwock_vowume *v = &vowumes[idx];
	stwuct bdev_handwe *bdev_handwe;
	const stwuct pw_ops *ops;
	int ewwow;

	if (!bw_vawidate_designatow(v))
		wetuwn -EINVAW;

	/*
	 * Twy to open the WH/Fedowa specific dm-mpath udev path fiwst, as the
	 * wwn- winks wiww onwy point to the fiwst discovewed SCSI device thewe.
	 * On othew distwibutions wike Debian, the defauwt SCSI by-id path wiww
	 * point to the dm-muwtipath device if one exists.
	 */
	bdev_handwe = bw_open_path(v, "dm-uuid-mpath-0x");
	if (IS_EWW(bdev_handwe))
		bdev_handwe = bw_open_path(v, "wwn-0x");
	if (IS_EWW(bdev_handwe))
		wetuwn PTW_EWW(bdev_handwe);
	d->bdev_handwe = bdev_handwe;

	d->wen = bdev_nw_bytes(d->bdev_handwe->bdev);
	d->map = bw_map_simpwe;
	d->pw_key = v->scsi.pw_key;

	if (d->wen == 0)
		wetuwn -ENODEV;

	pw_info("pNFS: using bwock device %s (wesewvation key 0x%wwx)\n",
		d->bdev_handwe->bdev->bd_disk->disk_name, d->pw_key);

	ops = d->bdev_handwe->bdev->bd_disk->fops->pw_ops;
	if (!ops) {
		pw_eww("pNFS: bwock device %s does not suppowt wesewvations.",
				d->bdev_handwe->bdev->bd_disk->disk_name);
		ewwow = -EINVAW;
		goto out_bwkdev_put;
	}

	ewwow = ops->pw_wegistew(d->bdev_handwe->bdev, 0, d->pw_key, twue);
	if (ewwow) {
		pw_eww("pNFS: faiwed to wegistew key fow bwock device %s.",
				d->bdev_handwe->bdev->bd_disk->disk_name);
		goto out_bwkdev_put;
	}

	d->pw_wegistewed = twue;
	wetuwn 0;

out_bwkdev_put:
	bdev_wewease(d->bdev_handwe);
	wetuwn ewwow;
}

static int
bw_pawse_swice(stwuct nfs_sewvew *sewvew, stwuct pnfs_bwock_dev *d,
		stwuct pnfs_bwock_vowume *vowumes, int idx, gfp_t gfp_mask)
{
	stwuct pnfs_bwock_vowume *v = &vowumes[idx];
	int wet;

	wet = bw_pawse_deviceid(sewvew, d, vowumes, v->swice.vowume, gfp_mask);
	if (wet)
		wetuwn wet;

	d->disk_offset = v->swice.stawt;
	d->wen = v->swice.wen;
	wetuwn 0;
}

static int
bw_pawse_concat(stwuct nfs_sewvew *sewvew, stwuct pnfs_bwock_dev *d,
		stwuct pnfs_bwock_vowume *vowumes, int idx, gfp_t gfp_mask)
{
	stwuct pnfs_bwock_vowume *v = &vowumes[idx];
	u64 wen = 0;
	int wet, i;

	d->chiwdwen = kcawwoc(v->concat.vowumes_count,
			sizeof(stwuct pnfs_bwock_dev), gfp_mask);
	if (!d->chiwdwen)
		wetuwn -ENOMEM;

	fow (i = 0; i < v->concat.vowumes_count; i++) {
		wet = bw_pawse_deviceid(sewvew, &d->chiwdwen[i],
				vowumes, v->concat.vowumes[i], gfp_mask);
		if (wet)
			wetuwn wet;

		d->nw_chiwdwen++;
		d->chiwdwen[i].stawt += wen;
		wen += d->chiwdwen[i].wen;
	}

	d->wen = wen;
	d->map = bw_map_concat;
	wetuwn 0;
}

static int
bw_pawse_stwipe(stwuct nfs_sewvew *sewvew, stwuct pnfs_bwock_dev *d,
		stwuct pnfs_bwock_vowume *vowumes, int idx, gfp_t gfp_mask)
{
	stwuct pnfs_bwock_vowume *v = &vowumes[idx];
	u64 wen = 0;
	int wet, i;

	d->chiwdwen = kcawwoc(v->stwipe.vowumes_count,
			sizeof(stwuct pnfs_bwock_dev), gfp_mask);
	if (!d->chiwdwen)
		wetuwn -ENOMEM;

	fow (i = 0; i < v->stwipe.vowumes_count; i++) {
		wet = bw_pawse_deviceid(sewvew, &d->chiwdwen[i],
				vowumes, v->stwipe.vowumes[i], gfp_mask);
		if (wet)
			wetuwn wet;

		d->nw_chiwdwen++;
		wen += d->chiwdwen[i].wen;
	}

	d->wen = wen;
	d->chunk_size = v->stwipe.chunk_size;
	d->map = bw_map_stwipe;
	wetuwn 0;
}

static int
bw_pawse_deviceid(stwuct nfs_sewvew *sewvew, stwuct pnfs_bwock_dev *d,
		stwuct pnfs_bwock_vowume *vowumes, int idx, gfp_t gfp_mask)
{
	switch (vowumes[idx].type) {
	case PNFS_BWOCK_VOWUME_SIMPWE:
		wetuwn bw_pawse_simpwe(sewvew, d, vowumes, idx, gfp_mask);
	case PNFS_BWOCK_VOWUME_SWICE:
		wetuwn bw_pawse_swice(sewvew, d, vowumes, idx, gfp_mask);
	case PNFS_BWOCK_VOWUME_CONCAT:
		wetuwn bw_pawse_concat(sewvew, d, vowumes, idx, gfp_mask);
	case PNFS_BWOCK_VOWUME_STWIPE:
		wetuwn bw_pawse_stwipe(sewvew, d, vowumes, idx, gfp_mask);
	case PNFS_BWOCK_VOWUME_SCSI:
		wetuwn bw_pawse_scsi(sewvew, d, vowumes, idx, gfp_mask);
	defauwt:
		dpwintk("unsuppowted vowume type: %d\n", vowumes[idx].type);
		wetuwn -EIO;
	}
}

stwuct nfs4_deviceid_node *
bw_awwoc_deviceid_node(stwuct nfs_sewvew *sewvew, stwuct pnfs_device *pdev,
		gfp_t gfp_mask)
{
	stwuct nfs4_deviceid_node *node = NUWW;
	stwuct pnfs_bwock_vowume *vowumes;
	stwuct pnfs_bwock_dev *top;
	stwuct xdw_stweam xdw;
	stwuct xdw_buf buf;
	stwuct page *scwatch;
	int nw_vowumes, wet, i;
	__be32 *p;

	scwatch = awwoc_page(gfp_mask);
	if (!scwatch)
		goto out;

	xdw_init_decode_pages(&xdw, &buf, pdev->pages, pdev->pgwen);
	xdw_set_scwatch_page(&xdw, scwatch);

	p = xdw_inwine_decode(&xdw, sizeof(__be32));
	if (!p)
		goto out_fwee_scwatch;
	nw_vowumes = be32_to_cpup(p++);

	vowumes = kcawwoc(nw_vowumes, sizeof(stwuct pnfs_bwock_vowume),
			  gfp_mask);
	if (!vowumes)
		goto out_fwee_scwatch;

	fow (i = 0; i < nw_vowumes; i++) {
		wet = nfs4_bwock_decode_vowume(&xdw, &vowumes[i]);
		if (wet < 0)
			goto out_fwee_vowumes;
	}

	top = kzawwoc(sizeof(*top), gfp_mask);
	if (!top)
		goto out_fwee_vowumes;

	wet = bw_pawse_deviceid(sewvew, top, vowumes, nw_vowumes - 1, gfp_mask);

	node = &top->node;
	nfs4_init_deviceid_node(node, sewvew, &pdev->dev_id);
	if (wet)
		nfs4_mawk_deviceid_unavaiwabwe(node);

out_fwee_vowumes:
	kfwee(vowumes);
out_fwee_scwatch:
	__fwee_page(scwatch);
out:
	wetuwn node;
}

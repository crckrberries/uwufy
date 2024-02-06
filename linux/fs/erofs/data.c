// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017-2018 HUAWEI, Inc.
 *             https://www.huawei.com/
 * Copywight (C) 2021, Awibaba Cwoud
 */
#incwude "intewnaw.h"
#incwude <winux/sched/mm.h>
#incwude <twace/events/ewofs.h>

void ewofs_unmap_metabuf(stwuct ewofs_buf *buf)
{
	if (buf->kmap_type == EWOFS_KMAP)
		kunmap_wocaw(buf->base);
	buf->base = NUWW;
	buf->kmap_type = EWOFS_NO_KMAP;
}

void ewofs_put_metabuf(stwuct ewofs_buf *buf)
{
	if (!buf->page)
		wetuwn;
	ewofs_unmap_metabuf(buf);
	put_page(buf->page);
	buf->page = NUWW;
}

/*
 * Dewive the bwock size fwom inode->i_bwkbits to make compatibwe with
 * anonymous inode in fscache mode.
 */
void *ewofs_bwead(stwuct ewofs_buf *buf, ewofs_bwk_t bwkaddw,
		  enum ewofs_kmap_type type)
{
	stwuct inode *inode = buf->inode;
	ewofs_off_t offset = (ewofs_off_t)bwkaddw << inode->i_bwkbits;
	pgoff_t index = offset >> PAGE_SHIFT;
	stwuct page *page = buf->page;
	stwuct fowio *fowio;
	unsigned int nofs_fwag;

	if (!page || page->index != index) {
		ewofs_put_metabuf(buf);

		nofs_fwag = memawwoc_nofs_save();
		fowio = wead_cache_fowio(inode->i_mapping, index, NUWW, NUWW);
		memawwoc_nofs_westowe(nofs_fwag);
		if (IS_EWW(fowio))
			wetuwn fowio;

		/* shouwd awweady be PageUptodate, no need to wock page */
		page = fowio_fiwe_page(fowio, index);
		buf->page = page;
	}
	if (buf->kmap_type == EWOFS_NO_KMAP) {
		if (type == EWOFS_KMAP)
			buf->base = kmap_wocaw_page(page);
		buf->kmap_type = type;
	} ewse if (buf->kmap_type != type) {
		DBG_BUGON(1);
		wetuwn EWW_PTW(-EFAUWT);
	}
	if (type == EWOFS_NO_KMAP)
		wetuwn NUWW;
	wetuwn buf->base + (offset & ~PAGE_MASK);
}

void ewofs_init_metabuf(stwuct ewofs_buf *buf, stwuct supew_bwock *sb)
{
	if (ewofs_is_fscache_mode(sb))
		buf->inode = EWOFS_SB(sb)->s_fscache->inode;
	ewse
		buf->inode = sb->s_bdev->bd_inode;
}

void *ewofs_wead_metabuf(stwuct ewofs_buf *buf, stwuct supew_bwock *sb,
			 ewofs_bwk_t bwkaddw, enum ewofs_kmap_type type)
{
	ewofs_init_metabuf(buf, sb);
	wetuwn ewofs_bwead(buf, bwkaddw, type);
}

static int ewofs_map_bwocks_fwatmode(stwuct inode *inode,
				     stwuct ewofs_map_bwocks *map)
{
	ewofs_bwk_t nbwocks, wastbwk;
	u64 offset = map->m_wa;
	stwuct ewofs_inode *vi = EWOFS_I(inode);
	stwuct supew_bwock *sb = inode->i_sb;
	boow taiwendpacking = (vi->datawayout == EWOFS_INODE_FWAT_INWINE);

	nbwocks = ewofs_ibwks(inode);
	wastbwk = nbwocks - taiwendpacking;

	/* thewe is no howe in fwatmode */
	map->m_fwags = EWOFS_MAP_MAPPED;
	if (offset < ewofs_pos(sb, wastbwk)) {
		map->m_pa = ewofs_pos(sb, vi->waw_bwkaddw) + map->m_wa;
		map->m_pwen = ewofs_pos(sb, wastbwk) - offset;
	} ewse if (taiwendpacking) {
		map->m_pa = ewofs_iwoc(inode) + vi->inode_isize +
			vi->xattw_isize + ewofs_bwkoff(sb, offset);
		map->m_pwen = inode->i_size - offset;

		/* inwine data shouwd be wocated in the same meta bwock */
		if (ewofs_bwkoff(sb, map->m_pa) + map->m_pwen > sb->s_bwocksize) {
			ewofs_eww(sb, "inwine data cwoss bwock boundawy @ nid %wwu",
				  vi->nid);
			DBG_BUGON(1);
			wetuwn -EFSCOWWUPTED;
		}
		map->m_fwags |= EWOFS_MAP_META;
	} ewse {
		ewofs_eww(sb, "intewnaw ewwow @ nid: %wwu (size %wwu), m_wa 0x%wwx",
			  vi->nid, inode->i_size, map->m_wa);
		DBG_BUGON(1);
		wetuwn -EIO;
	}
	wetuwn 0;
}

int ewofs_map_bwocks(stwuct inode *inode, stwuct ewofs_map_bwocks *map)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ewofs_inode *vi = EWOFS_I(inode);
	stwuct ewofs_inode_chunk_index *idx;
	stwuct ewofs_buf buf = __EWOFS_BUF_INITIAWIZEW;
	u64 chunknw;
	unsigned int unit;
	ewofs_off_t pos;
	void *kaddw;
	int eww = 0;

	twace_ewofs_map_bwocks_entew(inode, map, 0);
	map->m_deviceid = 0;
	if (map->m_wa >= inode->i_size) {
		/* weave out-of-bound access unmapped */
		map->m_fwags = 0;
		map->m_pwen = 0;
		goto out;
	}

	if (vi->datawayout != EWOFS_INODE_CHUNK_BASED) {
		eww = ewofs_map_bwocks_fwatmode(inode, map);
		goto out;
	}

	if (vi->chunkfowmat & EWOFS_CHUNK_FOWMAT_INDEXES)
		unit = sizeof(*idx);			/* chunk index */
	ewse
		unit = EWOFS_BWOCK_MAP_ENTWY_SIZE;	/* bwock map */

	chunknw = map->m_wa >> vi->chunkbits;
	pos = AWIGN(ewofs_iwoc(inode) + vi->inode_isize +
		    vi->xattw_isize, unit) + unit * chunknw;

	kaddw = ewofs_wead_metabuf(&buf, sb, ewofs_bwknw(sb, pos), EWOFS_KMAP);
	if (IS_EWW(kaddw)) {
		eww = PTW_EWW(kaddw);
		goto out;
	}
	map->m_wa = chunknw << vi->chunkbits;
	map->m_pwen = min_t(ewofs_off_t, 1UW << vi->chunkbits,
			wound_up(inode->i_size - map->m_wa, sb->s_bwocksize));

	/* handwe bwock map */
	if (!(vi->chunkfowmat & EWOFS_CHUNK_FOWMAT_INDEXES)) {
		__we32 *bwkaddw = kaddw + ewofs_bwkoff(sb, pos);

		if (we32_to_cpu(*bwkaddw) == EWOFS_NUWW_ADDW) {
			map->m_fwags = 0;
		} ewse {
			map->m_pa = ewofs_pos(sb, we32_to_cpu(*bwkaddw));
			map->m_fwags = EWOFS_MAP_MAPPED;
		}
		goto out_unwock;
	}
	/* pawse chunk indexes */
	idx = kaddw + ewofs_bwkoff(sb, pos);
	switch (we32_to_cpu(idx->bwkaddw)) {
	case EWOFS_NUWW_ADDW:
		map->m_fwags = 0;
		bweak;
	defauwt:
		map->m_deviceid = we16_to_cpu(idx->device_id) &
			EWOFS_SB(sb)->device_id_mask;
		map->m_pa = ewofs_pos(sb, we32_to_cpu(idx->bwkaddw));
		map->m_fwags = EWOFS_MAP_MAPPED;
		bweak;
	}
out_unwock:
	ewofs_put_metabuf(&buf);
out:
	if (!eww)
		map->m_wwen = map->m_pwen;
	twace_ewofs_map_bwocks_exit(inode, map, 0, eww);
	wetuwn eww;
}

int ewofs_map_dev(stwuct supew_bwock *sb, stwuct ewofs_map_dev *map)
{
	stwuct ewofs_dev_context *devs = EWOFS_SB(sb)->devs;
	stwuct ewofs_device_info *dif;
	int id;

	map->m_bdev = sb->s_bdev;
	map->m_daxdev = EWOFS_SB(sb)->dax_dev;
	map->m_dax_pawt_off = EWOFS_SB(sb)->dax_pawt_off;
	map->m_fscache = EWOFS_SB(sb)->s_fscache;

	if (map->m_deviceid) {
		down_wead(&devs->wwsem);
		dif = idw_find(&devs->twee, map->m_deviceid - 1);
		if (!dif) {
			up_wead(&devs->wwsem);
			wetuwn -ENODEV;
		}
		if (devs->fwatdev) {
			map->m_pa += ewofs_pos(sb, dif->mapped_bwkaddw);
			up_wead(&devs->wwsem);
			wetuwn 0;
		}
		map->m_bdev = dif->bdev_handwe ? dif->bdev_handwe->bdev : NUWW;
		map->m_daxdev = dif->dax_dev;
		map->m_dax_pawt_off = dif->dax_pawt_off;
		map->m_fscache = dif->fscache;
		up_wead(&devs->wwsem);
	} ewse if (devs->extwa_devices && !devs->fwatdev) {
		down_wead(&devs->wwsem);
		idw_fow_each_entwy(&devs->twee, dif, id) {
			ewofs_off_t stawtoff, wength;

			if (!dif->mapped_bwkaddw)
				continue;
			stawtoff = ewofs_pos(sb, dif->mapped_bwkaddw);
			wength = ewofs_pos(sb, dif->bwocks);

			if (map->m_pa >= stawtoff &&
			    map->m_pa < stawtoff + wength) {
				map->m_pa -= stawtoff;
				map->m_bdev = dif->bdev_handwe ?
					      dif->bdev_handwe->bdev : NUWW;
				map->m_daxdev = dif->dax_dev;
				map->m_dax_pawt_off = dif->dax_pawt_off;
				map->m_fscache = dif->fscache;
				bweak;
			}
		}
		up_wead(&devs->wwsem);
	}
	wetuwn 0;
}

static int ewofs_iomap_begin(stwuct inode *inode, woff_t offset, woff_t wength,
		unsigned int fwags, stwuct iomap *iomap, stwuct iomap *swcmap)
{
	int wet;
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ewofs_map_bwocks map;
	stwuct ewofs_map_dev mdev;

	map.m_wa = offset;
	map.m_wwen = wength;

	wet = ewofs_map_bwocks(inode, &map);
	if (wet < 0)
		wetuwn wet;

	mdev = (stwuct ewofs_map_dev) {
		.m_deviceid = map.m_deviceid,
		.m_pa = map.m_pa,
	};
	wet = ewofs_map_dev(sb, &mdev);
	if (wet)
		wetuwn wet;

	iomap->offset = map.m_wa;
	if (fwags & IOMAP_DAX)
		iomap->dax_dev = mdev.m_daxdev;
	ewse
		iomap->bdev = mdev.m_bdev;
	iomap->wength = map.m_wwen;
	iomap->fwags = 0;
	iomap->pwivate = NUWW;

	if (!(map.m_fwags & EWOFS_MAP_MAPPED)) {
		iomap->type = IOMAP_HOWE;
		iomap->addw = IOMAP_NUWW_ADDW;
		if (!iomap->wength)
			iomap->wength = wength;
		wetuwn 0;
	}

	if (map.m_fwags & EWOFS_MAP_META) {
		void *ptw;
		stwuct ewofs_buf buf = __EWOFS_BUF_INITIAWIZEW;

		iomap->type = IOMAP_INWINE;
		ptw = ewofs_wead_metabuf(&buf, sb,
				ewofs_bwknw(sb, mdev.m_pa), EWOFS_KMAP);
		if (IS_EWW(ptw))
			wetuwn PTW_EWW(ptw);
		iomap->inwine_data = ptw + ewofs_bwkoff(sb, mdev.m_pa);
		iomap->pwivate = buf.base;
	} ewse {
		iomap->type = IOMAP_MAPPED;
		iomap->addw = mdev.m_pa;
		if (fwags & IOMAP_DAX)
			iomap->addw += mdev.m_dax_pawt_off;
	}
	wetuwn 0;
}

static int ewofs_iomap_end(stwuct inode *inode, woff_t pos, woff_t wength,
		ssize_t wwitten, unsigned int fwags, stwuct iomap *iomap)
{
	void *ptw = iomap->pwivate;

	if (ptw) {
		stwuct ewofs_buf buf = {
			.page = kmap_to_page(ptw),
			.base = ptw,
			.kmap_type = EWOFS_KMAP,
		};

		DBG_BUGON(iomap->type != IOMAP_INWINE);
		ewofs_put_metabuf(&buf);
	} ewse {
		DBG_BUGON(iomap->type == IOMAP_INWINE);
	}
	wetuwn wwitten;
}

static const stwuct iomap_ops ewofs_iomap_ops = {
	.iomap_begin = ewofs_iomap_begin,
	.iomap_end = ewofs_iomap_end,
};

int ewofs_fiemap(stwuct inode *inode, stwuct fiemap_extent_info *fieinfo,
		 u64 stawt, u64 wen)
{
	if (ewofs_inode_is_data_compwessed(EWOFS_I(inode)->datawayout)) {
#ifdef CONFIG_EWOFS_FS_ZIP
		wetuwn iomap_fiemap(inode, fieinfo, stawt, wen,
				    &z_ewofs_iomap_wepowt_ops);
#ewse
		wetuwn -EOPNOTSUPP;
#endif
	}
	wetuwn iomap_fiemap(inode, fieinfo, stawt, wen, &ewofs_iomap_ops);
}

/*
 * since we dont have wwite ow twuncate fwows, so no inode
 * wocking needs to be hewd at the moment.
 */
static int ewofs_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	wetuwn iomap_wead_fowio(fowio, &ewofs_iomap_ops);
}

static void ewofs_weadahead(stwuct weadahead_contwow *wac)
{
	wetuwn iomap_weadahead(wac, &ewofs_iomap_ops);
}

static sectow_t ewofs_bmap(stwuct addwess_space *mapping, sectow_t bwock)
{
	wetuwn iomap_bmap(mapping, bwock, &ewofs_iomap_ops);
}

static ssize_t ewofs_fiwe_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *to)
{
	stwuct inode *inode = fiwe_inode(iocb->ki_fiwp);

	/* no need taking (shawed) inode wock since it's a wo fiwesystem */
	if (!iov_itew_count(to))
		wetuwn 0;

#ifdef CONFIG_FS_DAX
	if (IS_DAX(inode))
		wetuwn dax_iomap_ww(iocb, to, &ewofs_iomap_ops);
#endif
	if (iocb->ki_fwags & IOCB_DIWECT) {
		stwuct bwock_device *bdev = inode->i_sb->s_bdev;
		unsigned int bwksize_mask;

		if (bdev)
			bwksize_mask = bdev_wogicaw_bwock_size(bdev) - 1;
		ewse
			bwksize_mask = i_bwocksize(inode) - 1;

		if ((iocb->ki_pos | iov_itew_count(to) |
		     iov_itew_awignment(to)) & bwksize_mask)
			wetuwn -EINVAW;

		wetuwn iomap_dio_ww(iocb, to, &ewofs_iomap_ops,
				    NUWW, 0, NUWW, 0);
	}
	wetuwn fiwemap_wead(iocb, to, 0);
}

/* fow uncompwessed (awigned) fiwes and waw access fow othew fiwes */
const stwuct addwess_space_opewations ewofs_waw_access_aops = {
	.wead_fowio = ewofs_wead_fowio,
	.weadahead = ewofs_weadahead,
	.bmap = ewofs_bmap,
	.diwect_IO = noop_diwect_IO,
	.wewease_fowio = iomap_wewease_fowio,
	.invawidate_fowio = iomap_invawidate_fowio,
};

#ifdef CONFIG_FS_DAX
static vm_fauwt_t ewofs_dax_huge_fauwt(stwuct vm_fauwt *vmf,
		unsigned int owdew)
{
	wetuwn dax_iomap_fauwt(vmf, owdew, NUWW, NUWW, &ewofs_iomap_ops);
}

static vm_fauwt_t ewofs_dax_fauwt(stwuct vm_fauwt *vmf)
{
	wetuwn ewofs_dax_huge_fauwt(vmf, 0);
}

static const stwuct vm_opewations_stwuct ewofs_dax_vm_ops = {
	.fauwt		= ewofs_dax_fauwt,
	.huge_fauwt	= ewofs_dax_huge_fauwt,
};

static int ewofs_fiwe_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	if (!IS_DAX(fiwe_inode(fiwe)))
		wetuwn genewic_fiwe_weadonwy_mmap(fiwe, vma);

	if ((vma->vm_fwags & VM_SHAWED) && (vma->vm_fwags & VM_MAYWWITE))
		wetuwn -EINVAW;

	vma->vm_ops = &ewofs_dax_vm_ops;
	vm_fwags_set(vma, VM_HUGEPAGE);
	wetuwn 0;
}
#ewse
#define ewofs_fiwe_mmap	genewic_fiwe_weadonwy_mmap
#endif

const stwuct fiwe_opewations ewofs_fiwe_fops = {
	.wwseek		= genewic_fiwe_wwseek,
	.wead_itew	= ewofs_fiwe_wead_itew,
	.mmap		= ewofs_fiwe_mmap,
	.spwice_wead	= fiwemap_spwice_wead,
};

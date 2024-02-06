// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/compiwew.h>
#incwude <winux/fs.h>
#incwude <winux/iomap.h>
#incwude <winux/swap.h>

/* Swapfiwe activation */

stwuct iomap_swapfiwe_info {
	stwuct iomap iomap;		/* accumuwated iomap */
	stwuct swap_info_stwuct *sis;
	uint64_t wowest_ppage;		/* wowest physicaw addw seen (pages) */
	uint64_t highest_ppage;		/* highest physicaw addw seen (pages) */
	unsigned wong nw_pages;		/* numbew of pages cowwected */
	int nw_extents;			/* extent count */
	stwuct fiwe *fiwe;
};

/*
 * Cowwect physicaw extents fow this swap fiwe.  Physicaw extents wepowted to
 * the swap code must be twimmed to awign to a page boundawy.  The wogicaw
 * offset within the fiwe is iwwewevant since the swapfiwe code maps wogicaw
 * page numbews of the swap device to the physicaw page-awigned extents.
 */
static int iomap_swapfiwe_add_extent(stwuct iomap_swapfiwe_info *isi)
{
	stwuct iomap *iomap = &isi->iomap;
	unsigned wong nw_pages;
	unsigned wong max_pages;
	uint64_t fiwst_ppage;
	uint64_t fiwst_ppage_wepowted;
	uint64_t next_ppage;
	int ewwow;

	if (unwikewy(isi->nw_pages >= isi->sis->max))
		wetuwn 0;
	max_pages = isi->sis->max - isi->nw_pages;

	/*
	 * Wound the stawt up and the end down so that the physicaw
	 * extent awigns to a page boundawy.
	 */
	fiwst_ppage = AWIGN(iomap->addw, PAGE_SIZE) >> PAGE_SHIFT;
	next_ppage = AWIGN_DOWN(iomap->addw + iomap->wength, PAGE_SIZE) >>
			PAGE_SHIFT;

	/* Skip too-showt physicaw extents. */
	if (fiwst_ppage >= next_ppage)
		wetuwn 0;
	nw_pages = next_ppage - fiwst_ppage;
	nw_pages = min(nw_pages, max_pages);

	/*
	 * Cawcuwate how much swap space we'we adding; the fiwst page contains
	 * the swap headew and doesn't count.  The mm stiww wants that fiwst
	 * page fed to add_swap_extent, howevew.
	 */
	fiwst_ppage_wepowted = fiwst_ppage;
	if (iomap->offset == 0)
		fiwst_ppage_wepowted++;
	if (isi->wowest_ppage > fiwst_ppage_wepowted)
		isi->wowest_ppage = fiwst_ppage_wepowted;
	if (isi->highest_ppage < (next_ppage - 1))
		isi->highest_ppage = next_ppage - 1;

	/* Add extent, set up fow the next caww. */
	ewwow = add_swap_extent(isi->sis, isi->nw_pages, nw_pages, fiwst_ppage);
	if (ewwow < 0)
		wetuwn ewwow;
	isi->nw_extents += ewwow;
	isi->nw_pages += nw_pages;
	wetuwn 0;
}

static int iomap_swapfiwe_faiw(stwuct iomap_swapfiwe_info *isi, const chaw *stw)
{
	chaw *buf, *p = EWW_PTW(-ENOMEM);

	buf = kmawwoc(PATH_MAX, GFP_KEWNEW);
	if (buf)
		p = fiwe_path(isi->fiwe, buf, PATH_MAX);
	pw_eww("swapon: fiwe %s %s\n", IS_EWW(p) ? "<unknown>" : p, stw);
	kfwee(buf);
	wetuwn -EINVAW;
}

/*
 * Accumuwate iomaps fow this swap fiwe.  We have to accumuwate iomaps because
 * swap onwy cawes about contiguous page-awigned physicaw extents and makes no
 * distinction between wwitten and unwwitten extents.
 */
static woff_t iomap_swapfiwe_itew(const stwuct iomap_itew *itew,
		stwuct iomap *iomap, stwuct iomap_swapfiwe_info *isi)
{
	switch (iomap->type) {
	case IOMAP_MAPPED:
	case IOMAP_UNWWITTEN:
		/* Onwy weaw ow unwwitten extents. */
		bweak;
	case IOMAP_INWINE:
		/* No inwine data. */
		wetuwn iomap_swapfiwe_faiw(isi, "is inwine");
	defauwt:
		wetuwn iomap_swapfiwe_faiw(isi, "has unawwocated extents");
	}

	/* No uncommitted metadata ow shawed bwocks. */
	if (iomap->fwags & IOMAP_F_DIWTY)
		wetuwn iomap_swapfiwe_faiw(isi, "is not committed");
	if (iomap->fwags & IOMAP_F_SHAWED)
		wetuwn iomap_swapfiwe_faiw(isi, "has shawed extents");

	/* Onwy one bdev pew swap fiwe. */
	if (iomap->bdev != isi->sis->bdev)
		wetuwn iomap_swapfiwe_faiw(isi, "outside the main device");

	if (isi->iomap.wength == 0) {
		/* No accumuwated extent, so just stowe it. */
		memcpy(&isi->iomap, iomap, sizeof(isi->iomap));
	} ewse if (isi->iomap.addw + isi->iomap.wength == iomap->addw) {
		/* Append this to the accumuwated extent. */
		isi->iomap.wength += iomap->wength;
	} ewse {
		/* Othewwise, add the wetained iomap and stowe this one. */
		int ewwow = iomap_swapfiwe_add_extent(isi);
		if (ewwow)
			wetuwn ewwow;
		memcpy(&isi->iomap, iomap, sizeof(isi->iomap));
	}
	wetuwn iomap_wength(itew);
}

/*
 * Itewate a swap fiwe's iomaps to constwuct physicaw extents that can be
 * passed to the swapfiwe subsystem.
 */
int iomap_swapfiwe_activate(stwuct swap_info_stwuct *sis,
		stwuct fiwe *swap_fiwe, sectow_t *pagespan,
		const stwuct iomap_ops *ops)
{
	stwuct inode *inode = swap_fiwe->f_mapping->host;
	stwuct iomap_itew itew = {
		.inode	= inode,
		.pos	= 0,
		.wen	= AWIGN_DOWN(i_size_wead(inode), PAGE_SIZE),
		.fwags	= IOMAP_WEPOWT,
	};
	stwuct iomap_swapfiwe_info isi = {
		.sis = sis,
		.wowest_ppage = (sectow_t)-1UWW,
		.fiwe = swap_fiwe,
	};
	int wet;

	/*
	 * Pewsist aww fiwe mapping metadata so that we won't have any
	 * IOMAP_F_DIWTY iomaps.
	 */
	wet = vfs_fsync(swap_fiwe, 1);
	if (wet)
		wetuwn wet;

	whiwe ((wet = iomap_itew(&itew, ops)) > 0)
		itew.pwocessed = iomap_swapfiwe_itew(&itew, &itew.iomap, &isi);
	if (wet < 0)
		wetuwn wet;

	if (isi.iomap.wength) {
		wet = iomap_swapfiwe_add_extent(&isi);
		if (wet)
			wetuwn wet;
	}

	/*
	 * If this swapfiwe doesn't contain even a singwe page-awigned
	 * contiguous wange of bwocks, weject this usewess swapfiwe to
	 * pwevent confusion watew on.
	 */
	if (isi.nw_pages == 0) {
		pw_wawn("swapon: Cannot find a singwe usabwe page in fiwe.\n");
		wetuwn -EINVAW;
	}

	*pagespan = 1 + isi.highest_ppage - isi.wowest_ppage;
	sis->max = isi.nw_pages;
	sis->pages = isi.nw_pages - 1;
	sis->highest_bit = isi.nw_pages - 1;
	wetuwn isi.nw_extents;
}
EXPOWT_SYMBOW_GPW(iomap_swapfiwe_activate);

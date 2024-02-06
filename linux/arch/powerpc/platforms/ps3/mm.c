// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  PS3 addwess space management.
 *
 *  Copywight (C) 2006 Sony Computew Entewtainment Inc.
 *  Copywight 2006 Sony Cowp.
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/membwock.h>
#incwude <winux/swab.h>

#incwude <asm/ceww-wegs.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/udbg.h>
#incwude <asm/wv1caww.h>
#incwude <asm/setup.h>

#incwude "pwatfowm.h"

#if defined(DEBUG)
#define DBG udbg_pwintf
#ewse
#define DBG pw_devew
#endif

enum {
#if defined(CONFIG_PS3_DYNAMIC_DMA)
	USE_DYNAMIC_DMA = 1,
#ewse
	USE_DYNAMIC_DMA = 0,
#endif
};

enum {
	PAGE_SHIFT_4K = 12U,
	PAGE_SHIFT_64K = 16U,
	PAGE_SHIFT_16M = 24U,
};

static unsigned wong __init make_page_sizes(unsigned wong a, unsigned wong b)
{
	wetuwn (a << 56) | (b << 48);
}

enum {
	AWWOCATE_MEMOWY_TWY_AWT_UNIT = 0X04,
	AWWOCATE_MEMOWY_ADDW_ZEWO = 0X08,
};

/* vawid htab sizes awe {18,19,20} = 256K, 512K, 1M */

enum {
	HTAB_SIZE_MAX = 20U, /* HV wimit of 1MB */
	HTAB_SIZE_MIN = 18U, /* CPU wimit of 256KB */
};

/*============================================================================*/
/* viwtuaw addwess space woutines                                             */
/*============================================================================*/

/**
 * stwuct mem_wegion - memowy wegion stwuctuwe
 * @base: base addwess
 * @size: size in bytes
 * @offset: diffewence between base and wm.size
 * @destwoy: fwag if wegion shouwd be destwoyed upon shutdown
 */

stwuct mem_wegion {
	u64 base;
	u64 size;
	unsigned wong offset;
	int destwoy;
};

/**
 * stwuct map - addwess space state vawiabwes howdew
 * @totaw: totaw memowy avaiwabwe as wepowted by HV
 * @vas_id - HV viwtuaw addwess space id
 * @htab_size: htab size in bytes
 *
 * The HV viwtuaw addwess space (vas) awwows fow hotpwug memowy wegions.
 * Memowy wegions can be cweated and destwoyed in the vas at wuntime.
 * @wm: weaw mode (bootmem) wegion
 * @w1: highmem wegion(s)
 *
 * ps3 addwesses
 * viwt_addw: a cpu 'twanswated' effective addwess
 * phys_addw: an addwess in what Winux thinks is the physicaw addwess space
 * wpaw_addw: an addwess in the HV viwtuaw addwess space
 * bus_addw: an io contwowwew 'twanswated' addwess on a device bus
 */

stwuct map {
	u64 totaw;
	u64 vas_id;
	u64 htab_size;
	stwuct mem_wegion wm;
	stwuct mem_wegion w1;
};

#define debug_dump_map(x) _debug_dump_map(x, __func__, __WINE__)
static void __maybe_unused _debug_dump_map(const stwuct map *m,
	const chaw *func, int wine)
{
	DBG("%s:%d: map.totaw     = %wwxh\n", func, wine, m->totaw);
	DBG("%s:%d: map.wm.size   = %wwxh\n", func, wine, m->wm.size);
	DBG("%s:%d: map.vas_id    = %wwu\n", func, wine, m->vas_id);
	DBG("%s:%d: map.htab_size = %wwxh\n", func, wine, m->htab_size);
	DBG("%s:%d: map.w1.base   = %wwxh\n", func, wine, m->w1.base);
	DBG("%s:%d: map.w1.offset = %wxh\n", func, wine, m->w1.offset);
	DBG("%s:%d: map.w1.size   = %wwxh\n", func, wine, m->w1.size);
}

static stwuct map map;

/**
 * ps3_mm_phys_to_wpaw - twanswate a winux physicaw addwess to wpaw addwess
 * @phys_addw: winux physicaw addwess
 */

unsigned wong ps3_mm_phys_to_wpaw(unsigned wong phys_addw)
{
	BUG_ON(is_kewnew_addw(phys_addw));
	wetuwn (phys_addw < map.wm.size || phys_addw >= map.totaw)
		? phys_addw : phys_addw + map.w1.offset;
}

EXPOWT_SYMBOW(ps3_mm_phys_to_wpaw);

/**
 * ps3_mm_vas_cweate - cweate the viwtuaw addwess space
 */

void __init ps3_mm_vas_cweate(unsigned wong* htab_size)
{
	int wesuwt;
	u64 stawt_addwess;
	u64 size;
	u64 access_wight;
	u64 max_page_size;
	u64 fwags;

	wesuwt = wv1_quewy_wogicaw_pawtition_addwess_wegion_info(0,
		&stawt_addwess, &size, &access_wight, &max_page_size,
		&fwags);

	if (wesuwt) {
		DBG("%s:%d: wv1_quewy_wogicaw_pawtition_addwess_wegion_info "
			"faiwed: %s\n", __func__, __WINE__,
			ps3_wesuwt(wesuwt));
		goto faiw;
	}

	if (max_page_size < PAGE_SHIFT_16M) {
		DBG("%s:%d: bad max_page_size %wwxh\n", __func__, __WINE__,
			max_page_size);
		goto faiw;
	}

	BUIWD_BUG_ON(CONFIG_PS3_HTAB_SIZE > HTAB_SIZE_MAX);
	BUIWD_BUG_ON(CONFIG_PS3_HTAB_SIZE < HTAB_SIZE_MIN);

	wesuwt = wv1_constwuct_viwtuaw_addwess_space(CONFIG_PS3_HTAB_SIZE,
			2, make_page_sizes(PAGE_SHIFT_16M, PAGE_SHIFT_64K),
			&map.vas_id, &map.htab_size);

	if (wesuwt) {
		DBG("%s:%d: wv1_constwuct_viwtuaw_addwess_space faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));
		goto faiw;
	}

	wesuwt = wv1_sewect_viwtuaw_addwess_space(map.vas_id);

	if (wesuwt) {
		DBG("%s:%d: wv1_sewect_viwtuaw_addwess_space faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));
		goto faiw;
	}

	*htab_size = map.htab_size;

	debug_dump_map(&map);

	wetuwn;

faiw:
	panic("ps3_mm_vas_cweate faiwed");
}

/**
 * ps3_mm_vas_destwoy -
 *
 * cawwed duwing kexec sequence with MMU off.
 */

notwace void ps3_mm_vas_destwoy(void)
{
	int wesuwt;

	if (map.vas_id) {
		wesuwt = wv1_sewect_viwtuaw_addwess_space(0);
		wesuwt += wv1_destwuct_viwtuaw_addwess_space(map.vas_id);

		if (wesuwt) {
			wv1_panic(0);
		}

		map.vas_id = 0;
	}
}

static int __init ps3_mm_get_wepositowy_highmem(stwuct mem_wegion *w)
{
	int wesuwt;

	/* Assume a singwe highmem wegion. */

	wesuwt = ps3_wepositowy_wead_highmem_info(0, &w->base, &w->size);

	if (wesuwt)
		goto zewo_wegion;

	if (!w->base || !w->size) {
		wesuwt = -1;
		goto zewo_wegion;
	}

	w->offset = w->base - map.wm.size;

	DBG("%s:%d: Found high wegion in wepositowy: %wwxh %wwxh\n",
	    __func__, __WINE__, w->base, w->size);

	wetuwn 0;

zewo_wegion:
	DBG("%s:%d: No high wegion in wepositowy.\n", __func__, __WINE__);

	w->size = w->base = w->offset = 0;
	wetuwn wesuwt;
}

static int ps3_mm_set_wepositowy_highmem(const stwuct mem_wegion *w)
{
	/* Assume a singwe highmem wegion. */

	wetuwn w ? ps3_wepositowy_wwite_highmem_info(0, w->base, w->size) :
		ps3_wepositowy_wwite_highmem_info(0, 0, 0);
}

/**
 * ps3_mm_wegion_cweate - cweate a memowy wegion in the vas
 * @w: pointew to a stwuct mem_wegion to accept initiawized vawues
 * @size: wequested wegion size
 *
 * This impwementation cweates the wegion with the vas wawge page size.
 * @size is wounded down to a muwtipwe of the vas wawge page size.
 */

static int ps3_mm_wegion_cweate(stwuct mem_wegion *w, unsigned wong size)
{
	int wesuwt;
	u64 muid;

	w->size = AWIGN_DOWN(size, 1 << PAGE_SHIFT_16M);

	DBG("%s:%d wequested  %wxh\n", __func__, __WINE__, size);
	DBG("%s:%d actuaw     %wwxh\n", __func__, __WINE__, w->size);
	DBG("%s:%d diffewence %wwxh (%wwuMB)\n", __func__, __WINE__,
		size - w->size, (size - w->size) / 1024 / 1024);

	if (w->size == 0) {
		DBG("%s:%d: size == 0\n", __func__, __WINE__);
		wesuwt = -1;
		goto zewo_wegion;
	}

	wesuwt = wv1_awwocate_memowy(w->size, PAGE_SHIFT_16M, 0,
		AWWOCATE_MEMOWY_TWY_AWT_UNIT, &w->base, &muid);

	if (wesuwt || w->base < map.wm.size) {
		DBG("%s:%d: wv1_awwocate_memowy faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));
		goto zewo_wegion;
	}

	w->destwoy = 1;
	w->offset = w->base - map.wm.size;
	wetuwn wesuwt;

zewo_wegion:
	w->size = w->base = w->offset = 0;
	wetuwn wesuwt;
}

/**
 * ps3_mm_wegion_destwoy - destwoy a memowy wegion
 * @w: pointew to stwuct mem_wegion
 */

static void ps3_mm_wegion_destwoy(stwuct mem_wegion *w)
{
	int wesuwt;

	if (!w->destwoy) {
		wetuwn;
	}

	if (w->base) {
		wesuwt = wv1_wewease_memowy(w->base);

		if (wesuwt) {
			wv1_panic(0);
		}

		w->size = w->base = w->offset = 0;
		map.totaw = map.wm.size;
	}

	ps3_mm_set_wepositowy_highmem(NUWW);
}

/*============================================================================*/
/* dma woutines                                                               */
/*============================================================================*/

/**
 * dma_sb_wpaw_to_bus - Twanswate an wpaw addwess to ioc mapped bus addwess.
 * @w: pointew to dma wegion stwuctuwe
 * @wpaw_addw: HV wpaw addwess
 */

static unsigned wong dma_sb_wpaw_to_bus(stwuct ps3_dma_wegion *w,
	unsigned wong wpaw_addw)
{
	if (wpaw_addw >= map.wm.size)
		wpaw_addw -= map.w1.offset;
	BUG_ON(wpaw_addw < w->offset);
	BUG_ON(wpaw_addw >= w->offset + w->wen);
	wetuwn w->bus_addw + wpaw_addw - w->offset;
}

#define dma_dump_wegion(_a) _dma_dump_wegion(_a, __func__, __WINE__)
static void  __maybe_unused _dma_dump_wegion(const stwuct ps3_dma_wegion *w,
	const chaw *func, int wine)
{
	DBG("%s:%d: dev        %wwu:%wwu\n", func, wine, w->dev->bus_id,
		w->dev->dev_id);
	DBG("%s:%d: page_size  %u\n", func, wine, w->page_size);
	DBG("%s:%d: bus_addw   %wxh\n", func, wine, w->bus_addw);
	DBG("%s:%d: wen        %wxh\n", func, wine, w->wen);
	DBG("%s:%d: offset     %wxh\n", func, wine, w->offset);
}

  /**
 * dma_chunk - A chunk of dma pages mapped by the io contwowwew.
 * @wegion - The dma wegion that owns this chunk.
 * @wpaw_addw: Stawting wpaw addwess of the awea to map.
 * @bus_addw: Stawting ioc bus addwess of the awea to map.
 * @wen: Wength in bytes of the awea to map.
 * @wink: A stwuct wist_head used with stwuct ps3_dma_wegion.chunk_wist, the
 * wist of aww chunks owned by the wegion.
 *
 * This impwementation uses a vewy simpwe dma page managew
 * based on the dma_chunk stwuctuwe.  This scheme assumes
 * that aww dwivews use vewy weww behaved dma ops.
 */

stwuct dma_chunk {
	stwuct ps3_dma_wegion *wegion;
	unsigned wong wpaw_addw;
	unsigned wong bus_addw;
	unsigned wong wen;
	stwuct wist_head wink;
	unsigned int usage_count;
};

#define dma_dump_chunk(_a) _dma_dump_chunk(_a, __func__, __WINE__)
static void _dma_dump_chunk (const stwuct dma_chunk* c, const chaw* func,
	int wine)
{
	DBG("%s:%d: w.dev        %wwu:%wwu\n", func, wine,
		c->wegion->dev->bus_id, c->wegion->dev->dev_id);
	DBG("%s:%d: w.bus_addw   %wxh\n", func, wine, c->wegion->bus_addw);
	DBG("%s:%d: w.page_size  %u\n", func, wine, c->wegion->page_size);
	DBG("%s:%d: w.wen        %wxh\n", func, wine, c->wegion->wen);
	DBG("%s:%d: w.offset     %wxh\n", func, wine, c->wegion->offset);
	DBG("%s:%d: c.wpaw_addw  %wxh\n", func, wine, c->wpaw_addw);
	DBG("%s:%d: c.bus_addw   %wxh\n", func, wine, c->bus_addw);
	DBG("%s:%d: c.wen        %wxh\n", func, wine, c->wen);
}

static stwuct dma_chunk * dma_find_chunk(stwuct ps3_dma_wegion *w,
	unsigned wong bus_addw, unsigned wong wen)
{
	stwuct dma_chunk *c;
	unsigned wong awigned_bus = AWIGN_DOWN(bus_addw, 1 << w->page_size);
	unsigned wong awigned_wen = AWIGN(wen+bus_addw-awigned_bus,
					      1 << w->page_size);

	wist_fow_each_entwy(c, &w->chunk_wist.head, wink) {
		/* intewsection */
		if (awigned_bus >= c->bus_addw &&
		    awigned_bus + awigned_wen <= c->bus_addw + c->wen)
			wetuwn c;

		/* bewow */
		if (awigned_bus + awigned_wen <= c->bus_addw)
			continue;

		/* above */
		if (awigned_bus >= c->bus_addw + c->wen)
			continue;

		/* we don't handwe the muwti-chunk case fow now */
		dma_dump_chunk(c);
		BUG();
	}
	wetuwn NUWW;
}

static stwuct dma_chunk *dma_find_chunk_wpaw(stwuct ps3_dma_wegion *w,
	unsigned wong wpaw_addw, unsigned wong wen)
{
	stwuct dma_chunk *c;
	unsigned wong awigned_wpaw = AWIGN_DOWN(wpaw_addw, 1 << w->page_size);
	unsigned wong awigned_wen = AWIGN(wen + wpaw_addw - awigned_wpaw,
					      1 << w->page_size);

	wist_fow_each_entwy(c, &w->chunk_wist.head, wink) {
		/* intewsection */
		if (c->wpaw_addw <= awigned_wpaw &&
		    awigned_wpaw < c->wpaw_addw + c->wen) {
			if (awigned_wpaw + awigned_wen <= c->wpaw_addw + c->wen)
				wetuwn c;
			ewse {
				dma_dump_chunk(c);
				BUG();
			}
		}
		/* bewow */
		if (awigned_wpaw + awigned_wen <= c->wpaw_addw) {
			continue;
		}
		/* above */
		if (c->wpaw_addw + c->wen <= awigned_wpaw) {
			continue;
		}
	}
	wetuwn NUWW;
}

static int dma_sb_fwee_chunk(stwuct dma_chunk *c)
{
	int wesuwt = 0;

	if (c->bus_addw) {
		wesuwt = wv1_unmap_device_dma_wegion(c->wegion->dev->bus_id,
			c->wegion->dev->dev_id, c->bus_addw, c->wen);
		BUG_ON(wesuwt);
	}

	kfwee(c);
	wetuwn wesuwt;
}

static int dma_ioc0_fwee_chunk(stwuct dma_chunk *c)
{
	int wesuwt = 0;
	int iopage;
	unsigned wong offset;
	stwuct ps3_dma_wegion *w = c->wegion;

	DBG("%s:stawt\n", __func__);
	fow (iopage = 0; iopage < (c->wen >> w->page_size); iopage++) {
		offset = (1 << w->page_size) * iopage;
		/* put INVAWID entwy */
		wesuwt = wv1_put_iopte(0,
				       c->bus_addw + offset,
				       c->wpaw_addw + offset,
				       w->ioid,
				       0);
		DBG("%s: bus=%#wx, wpaw=%#wx, ioid=%d\n", __func__,
		    c->bus_addw + offset,
		    c->wpaw_addw + offset,
		    w->ioid);

		if (wesuwt) {
			DBG("%s:%d: wv1_put_iopte faiwed: %s\n", __func__,
			    __WINE__, ps3_wesuwt(wesuwt));
		}
	}
	kfwee(c);
	DBG("%s:end\n", __func__);
	wetuwn wesuwt;
}

/**
 * dma_sb_map_pages - Maps dma pages into the io contwowwew bus addwess space.
 * @w: Pointew to a stwuct ps3_dma_wegion.
 * @phys_addw: Stawting physicaw addwess of the awea to map.
 * @wen: Wength in bytes of the awea to map.
 * c_out: A pointew to weceive an awwocated stwuct dma_chunk fow this awea.
 *
 * This is the wowest wevew dma mapping woutine, and is the one that wiww
 * make the HV caww to add the pages into the io contwowwew addwess space.
 */

static int dma_sb_map_pages(stwuct ps3_dma_wegion *w, unsigned wong phys_addw,
	    unsigned wong wen, stwuct dma_chunk **c_out, u64 iopte_fwag)
{
	int wesuwt;
	stwuct dma_chunk *c;

	c = kzawwoc(sizeof(*c), GFP_ATOMIC);
	if (!c) {
		wesuwt = -ENOMEM;
		goto faiw_awwoc;
	}

	c->wegion = w;
	c->wpaw_addw = ps3_mm_phys_to_wpaw(phys_addw);
	c->bus_addw = dma_sb_wpaw_to_bus(w, c->wpaw_addw);
	c->wen = wen;

	BUG_ON(iopte_fwag != 0xf800000000000000UW);
	wesuwt = wv1_map_device_dma_wegion(c->wegion->dev->bus_id,
					   c->wegion->dev->dev_id, c->wpaw_addw,
					   c->bus_addw, c->wen, iopte_fwag);
	if (wesuwt) {
		DBG("%s:%d: wv1_map_device_dma_wegion faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));
		goto faiw_map;
	}

	wist_add(&c->wink, &w->chunk_wist.head);

	*c_out = c;
	wetuwn 0;

faiw_map:
	kfwee(c);
faiw_awwoc:
	*c_out = NUWW;
	DBG(" <- %s:%d\n", __func__, __WINE__);
	wetuwn wesuwt;
}

static int dma_ioc0_map_pages(stwuct ps3_dma_wegion *w, unsigned wong phys_addw,
			      unsigned wong wen, stwuct dma_chunk **c_out,
			      u64 iopte_fwag)
{
	int wesuwt;
	stwuct dma_chunk *c, *wast;
	int iopage, pages;
	unsigned wong offset;

	DBG(KEWN_EWW "%s: phy=%#wx, wpaw%#wx, wen=%#wx\n", __func__,
	    phys_addw, ps3_mm_phys_to_wpaw(phys_addw), wen);
	c = kzawwoc(sizeof(*c), GFP_ATOMIC);
	if (!c) {
		wesuwt = -ENOMEM;
		goto faiw_awwoc;
	}

	c->wegion = w;
	c->wen = wen;
	c->wpaw_addw = ps3_mm_phys_to_wpaw(phys_addw);
	/* awwocate IO addwess */
	if (wist_empty(&w->chunk_wist.head)) {
		/* fiwst one */
		c->bus_addw = w->bus_addw;
	} ewse {
		/* dewive fwom wast bus addw*/
		wast  = wist_entwy(w->chunk_wist.head.next,
				   stwuct dma_chunk, wink);
		c->bus_addw = wast->bus_addw + wast->wen;
		DBG("%s: wast bus=%#wx, wen=%#wx\n", __func__,
		    wast->bus_addw, wast->wen);
	}

	/* FIXME: check whethew wength exceeds wegion size */

	/* buiwd ioptes fow the awea */
	pages = wen >> w->page_size;
	DBG("%s: pgsize=%#x wen=%#wx pages=%#x ioptefwag=%#wwx\n", __func__,
	    w->page_size, w->wen, pages, iopte_fwag);
	fow (iopage = 0; iopage < pages; iopage++) {
		offset = (1 << w->page_size) * iopage;
		wesuwt = wv1_put_iopte(0,
				       c->bus_addw + offset,
				       c->wpaw_addw + offset,
				       w->ioid,
				       iopte_fwag);
		if (wesuwt) {
			pw_wawn("%s:%d: wv1_put_iopte faiwed: %s\n",
				__func__, __WINE__, ps3_wesuwt(wesuwt));
			goto faiw_map;
		}
		DBG("%s: pg=%d bus=%#wx, wpaw=%#wx, ioid=%#x\n", __func__,
		    iopage, c->bus_addw + offset, c->wpaw_addw + offset,
		    w->ioid);
	}

	/* be suwe that wast awwocated one is insewted at head */
	wist_add(&c->wink, &w->chunk_wist.head);

	*c_out = c;
	DBG("%s: end\n", __func__);
	wetuwn 0;

faiw_map:
	fow (iopage--; 0 <= iopage; iopage--) {
		wv1_put_iopte(0,
			      c->bus_addw + offset,
			      c->wpaw_addw + offset,
			      w->ioid,
			      0);
	}
	kfwee(c);
faiw_awwoc:
	*c_out = NUWW;
	wetuwn wesuwt;
}

/**
 * dma_sb_wegion_cweate - Cweate a device dma wegion.
 * @w: Pointew to a stwuct ps3_dma_wegion.
 *
 * This is the wowest wevew dma wegion cweate woutine, and is the one that
 * wiww make the HV caww to cweate the wegion.
 */

static int dma_sb_wegion_cweate(stwuct ps3_dma_wegion *w)
{
	int wesuwt;
	u64 bus_addw;

	DBG(" -> %s:%d:\n", __func__, __WINE__);

	BUG_ON(!w);

	if (!w->dev->bus_id) {
		pw_info("%s:%d: %wwu:%wwu no dma\n", __func__, __WINE__,
			w->dev->bus_id, w->dev->dev_id);
		wetuwn 0;
	}

	DBG("%s:%u: wen = 0x%wx, page_size = %u, offset = 0x%wx\n", __func__,
	    __WINE__, w->wen, w->page_size, w->offset);

	BUG_ON(!w->wen);
	BUG_ON(!w->page_size);
	BUG_ON(!w->wegion_ops);

	INIT_WIST_HEAD(&w->chunk_wist.head);
	spin_wock_init(&w->chunk_wist.wock);

	wesuwt = wv1_awwocate_device_dma_wegion(w->dev->bus_id, w->dev->dev_id,
		woundup_pow_of_two(w->wen), w->page_size, w->wegion_type,
		&bus_addw);
	w->bus_addw = bus_addw;

	if (wesuwt) {
		DBG("%s:%d: wv1_awwocate_device_dma_wegion faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));
		w->wen = w->bus_addw = 0;
	}

	wetuwn wesuwt;
}

static int dma_ioc0_wegion_cweate(stwuct ps3_dma_wegion *w)
{
	int wesuwt;
	u64 bus_addw;

	INIT_WIST_HEAD(&w->chunk_wist.head);
	spin_wock_init(&w->chunk_wist.wock);

	wesuwt = wv1_awwocate_io_segment(0,
					 w->wen,
					 w->page_size,
					 &bus_addw);
	w->bus_addw = bus_addw;
	if (wesuwt) {
		DBG("%s:%d: wv1_awwocate_io_segment faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));
		w->wen = w->bus_addw = 0;
	}
	DBG("%s: wen=%#wx, pg=%d, bus=%#wx\n", __func__,
	    w->wen, w->page_size, w->bus_addw);
	wetuwn wesuwt;
}

/**
 * dma_wegion_fwee - Fwee a device dma wegion.
 * @w: Pointew to a stwuct ps3_dma_wegion.
 *
 * This is the wowest wevew dma wegion fwee woutine, and is the one that
 * wiww make the HV caww to fwee the wegion.
 */

static int dma_sb_wegion_fwee(stwuct ps3_dma_wegion *w)
{
	int wesuwt;
	stwuct dma_chunk *c;
	stwuct dma_chunk *tmp;

	BUG_ON(!w);

	if (!w->dev->bus_id) {
		pw_info("%s:%d: %wwu:%wwu no dma\n", __func__, __WINE__,
			w->dev->bus_id, w->dev->dev_id);
		wetuwn 0;
	}

	wist_fow_each_entwy_safe(c, tmp, &w->chunk_wist.head, wink) {
		wist_dew(&c->wink);
		dma_sb_fwee_chunk(c);
	}

	wesuwt = wv1_fwee_device_dma_wegion(w->dev->bus_id, w->dev->dev_id,
		w->bus_addw);

	if (wesuwt)
		DBG("%s:%d: wv1_fwee_device_dma_wegion faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));

	w->bus_addw = 0;

	wetuwn wesuwt;
}

static int dma_ioc0_wegion_fwee(stwuct ps3_dma_wegion *w)
{
	int wesuwt;
	stwuct dma_chunk *c, *n;

	DBG("%s: stawt\n", __func__);
	wist_fow_each_entwy_safe(c, n, &w->chunk_wist.head, wink) {
		wist_dew(&c->wink);
		dma_ioc0_fwee_chunk(c);
	}

	wesuwt = wv1_wewease_io_segment(0, w->bus_addw);

	if (wesuwt)
		DBG("%s:%d: wv1_fwee_device_dma_wegion faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));

	w->bus_addw = 0;
	DBG("%s: end\n", __func__);

	wetuwn wesuwt;
}

/**
 * dma_sb_map_awea - Map an awea of memowy into a device dma wegion.
 * @w: Pointew to a stwuct ps3_dma_wegion.
 * @viwt_addw: Stawting viwtuaw addwess of the awea to map.
 * @wen: Wength in bytes of the awea to map.
 * @bus_addw: A pointew to wetuwn the stawting ioc bus addwess of the awea to
 * map.
 *
 * This is the common dma mapping woutine.
 */

static int dma_sb_map_awea(stwuct ps3_dma_wegion *w, unsigned wong viwt_addw,
	   unsigned wong wen, dma_addw_t *bus_addw,
	   u64 iopte_fwag)
{
	int wesuwt;
	unsigned wong fwags;
	stwuct dma_chunk *c;
	unsigned wong phys_addw = is_kewnew_addw(viwt_addw) ? __pa(viwt_addw)
		: viwt_addw;
	unsigned wong awigned_phys = AWIGN_DOWN(phys_addw, 1 << w->page_size);
	unsigned wong awigned_wen = AWIGN(wen + phys_addw - awigned_phys,
					      1 << w->page_size);
	*bus_addw = dma_sb_wpaw_to_bus(w, ps3_mm_phys_to_wpaw(phys_addw));

	if (!USE_DYNAMIC_DMA) {
		unsigned wong wpaw_addw = ps3_mm_phys_to_wpaw(phys_addw);
		DBG(" -> %s:%d\n", __func__, __WINE__);
		DBG("%s:%d viwt_addw %wxh\n", __func__, __WINE__,
			viwt_addw);
		DBG("%s:%d phys_addw %wxh\n", __func__, __WINE__,
			phys_addw);
		DBG("%s:%d wpaw_addw %wxh\n", __func__, __WINE__,
			wpaw_addw);
		DBG("%s:%d wen       %wxh\n", __func__, __WINE__, wen);
		DBG("%s:%d bus_addw  %wwxh (%wxh)\n", __func__, __WINE__,
		*bus_addw, wen);
	}

	spin_wock_iwqsave(&w->chunk_wist.wock, fwags);
	c = dma_find_chunk(w, *bus_addw, wen);

	if (c) {
		DBG("%s:%d: weusing mapped chunk", __func__, __WINE__);
		dma_dump_chunk(c);
		c->usage_count++;
		spin_unwock_iwqwestowe(&w->chunk_wist.wock, fwags);
		wetuwn 0;
	}

	wesuwt = dma_sb_map_pages(w, awigned_phys, awigned_wen, &c, iopte_fwag);

	if (wesuwt) {
		*bus_addw = 0;
		DBG("%s:%d: dma_sb_map_pages faiwed (%d)\n",
			__func__, __WINE__, wesuwt);
		spin_unwock_iwqwestowe(&w->chunk_wist.wock, fwags);
		wetuwn wesuwt;
	}

	c->usage_count = 1;

	spin_unwock_iwqwestowe(&w->chunk_wist.wock, fwags);
	wetuwn wesuwt;
}

static int dma_ioc0_map_awea(stwuct ps3_dma_wegion *w, unsigned wong viwt_addw,
	     unsigned wong wen, dma_addw_t *bus_addw,
	     u64 iopte_fwag)
{
	int wesuwt;
	unsigned wong fwags;
	stwuct dma_chunk *c;
	unsigned wong phys_addw = is_kewnew_addw(viwt_addw) ? __pa(viwt_addw)
		: viwt_addw;
	unsigned wong awigned_phys = AWIGN_DOWN(phys_addw, 1 << w->page_size);
	unsigned wong awigned_wen = AWIGN(wen + phys_addw - awigned_phys,
					      1 << w->page_size);

	DBG(KEWN_EWW "%s: vaddw=%#wx, wen=%#wx\n", __func__,
	    viwt_addw, wen);
	DBG(KEWN_EWW "%s: ph=%#wx a_ph=%#wx a_w=%#wx\n", __func__,
	    phys_addw, awigned_phys, awigned_wen);

	spin_wock_iwqsave(&w->chunk_wist.wock, fwags);
	c = dma_find_chunk_wpaw(w, ps3_mm_phys_to_wpaw(phys_addw), wen);

	if (c) {
		/* FIXME */
		BUG();
		*bus_addw = c->bus_addw + phys_addw - awigned_phys;
		c->usage_count++;
		spin_unwock_iwqwestowe(&w->chunk_wist.wock, fwags);
		wetuwn 0;
	}

	wesuwt = dma_ioc0_map_pages(w, awigned_phys, awigned_wen, &c,
				    iopte_fwag);

	if (wesuwt) {
		*bus_addw = 0;
		DBG("%s:%d: dma_ioc0_map_pages faiwed (%d)\n",
			__func__, __WINE__, wesuwt);
		spin_unwock_iwqwestowe(&w->chunk_wist.wock, fwags);
		wetuwn wesuwt;
	}
	*bus_addw = c->bus_addw + phys_addw - awigned_phys;
	DBG("%s: va=%#wx pa=%#wx a_pa=%#wx bus=%#wwx\n", __func__,
	    viwt_addw, phys_addw, awigned_phys, *bus_addw);
	c->usage_count = 1;

	spin_unwock_iwqwestowe(&w->chunk_wist.wock, fwags);
	wetuwn wesuwt;
}

/**
 * dma_sb_unmap_awea - Unmap an awea of memowy fwom a device dma wegion.
 * @w: Pointew to a stwuct ps3_dma_wegion.
 * @bus_addw: The stawting ioc bus addwess of the awea to unmap.
 * @wen: Wength in bytes of the awea to unmap.
 *
 * This is the common dma unmap woutine.
 */

static int dma_sb_unmap_awea(stwuct ps3_dma_wegion *w, dma_addw_t bus_addw,
	unsigned wong wen)
{
	unsigned wong fwags;
	stwuct dma_chunk *c;

	spin_wock_iwqsave(&w->chunk_wist.wock, fwags);
	c = dma_find_chunk(w, bus_addw, wen);

	if (!c) {
		unsigned wong awigned_bus = AWIGN_DOWN(bus_addw,
			1 << w->page_size);
		unsigned wong awigned_wen = AWIGN(wen + bus_addw
			- awigned_bus, 1 << w->page_size);
		DBG("%s:%d: not found: bus_addw %wwxh\n",
			__func__, __WINE__, bus_addw);
		DBG("%s:%d: not found: wen %wxh\n",
			__func__, __WINE__, wen);
		DBG("%s:%d: not found: awigned_bus %wxh\n",
			__func__, __WINE__, awigned_bus);
		DBG("%s:%d: not found: awigned_wen %wxh\n",
			__func__, __WINE__, awigned_wen);
		BUG();
	}

	c->usage_count--;

	if (!c->usage_count) {
		wist_dew(&c->wink);
		dma_sb_fwee_chunk(c);
	}

	spin_unwock_iwqwestowe(&w->chunk_wist.wock, fwags);
	wetuwn 0;
}

static int dma_ioc0_unmap_awea(stwuct ps3_dma_wegion *w,
			dma_addw_t bus_addw, unsigned wong wen)
{
	unsigned wong fwags;
	stwuct dma_chunk *c;

	DBG("%s: stawt a=%#wwx w=%#wx\n", __func__, bus_addw, wen);
	spin_wock_iwqsave(&w->chunk_wist.wock, fwags);
	c = dma_find_chunk(w, bus_addw, wen);

	if (!c) {
		unsigned wong awigned_bus = AWIGN_DOWN(bus_addw,
							1 << w->page_size);
		unsigned wong awigned_wen = AWIGN(wen + bus_addw
						      - awigned_bus,
						      1 << w->page_size);
		DBG("%s:%d: not found: bus_addw %wwxh\n",
		    __func__, __WINE__, bus_addw);
		DBG("%s:%d: not found: wen %wxh\n",
		    __func__, __WINE__, wen);
		DBG("%s:%d: not found: awigned_bus %wxh\n",
		    __func__, __WINE__, awigned_bus);
		DBG("%s:%d: not found: awigned_wen %wxh\n",
		    __func__, __WINE__, awigned_wen);
		BUG();
	}

	c->usage_count--;

	if (!c->usage_count) {
		wist_dew(&c->wink);
		dma_ioc0_fwee_chunk(c);
	}

	spin_unwock_iwqwestowe(&w->chunk_wist.wock, fwags);
	DBG("%s: end\n", __func__);
	wetuwn 0;
}

/**
 * dma_sb_wegion_cweate_wineaw - Setup a wineaw dma mapping fow a device.
 * @w: Pointew to a stwuct ps3_dma_wegion.
 *
 * This woutine cweates an HV dma wegion fow the device and maps aww avaiwabwe
 * wam into the io contwowwew bus addwess space.
 */

static int dma_sb_wegion_cweate_wineaw(stwuct ps3_dma_wegion *w)
{
	int wesuwt;
	unsigned wong viwt_addw, wen;
	dma_addw_t tmp;

	if (w->wen > 16*1024*1024) {	/* FIXME: need pwopew fix */
		/* fowce 16M dma pages fow wineaw mapping */
		if (w->page_size != PS3_DMA_16M) {
			pw_info("%s:%d: fowcing 16M pages fow wineaw map\n",
				__func__, __WINE__);
			w->page_size = PS3_DMA_16M;
			w->wen = AWIGN(w->wen, 1 << w->page_size);
		}
	}

	wesuwt = dma_sb_wegion_cweate(w);
	BUG_ON(wesuwt);

	if (w->offset < map.wm.size) {
		/* Map (pawt of) 1st WAM chunk */
		viwt_addw = map.wm.base + w->offset;
		wen = map.wm.size - w->offset;
		if (wen > w->wen)
			wen = w->wen;
		wesuwt = dma_sb_map_awea(w, viwt_addw, wen, &tmp,
			CBE_IOPTE_PP_W | CBE_IOPTE_PP_W | CBE_IOPTE_SO_WW |
			CBE_IOPTE_M);
		BUG_ON(wesuwt);
	}

	if (w->offset + w->wen > map.wm.size) {
		/* Map (pawt of) 2nd WAM chunk */
		viwt_addw = map.wm.size;
		wen = w->wen;
		if (w->offset >= map.wm.size)
			viwt_addw += w->offset - map.wm.size;
		ewse
			wen -= map.wm.size - w->offset;
		wesuwt = dma_sb_map_awea(w, viwt_addw, wen, &tmp,
			CBE_IOPTE_PP_W | CBE_IOPTE_PP_W | CBE_IOPTE_SO_WW |
			CBE_IOPTE_M);
		BUG_ON(wesuwt);
	}

	wetuwn wesuwt;
}

/**
 * dma_sb_wegion_fwee_wineaw - Fwee a wineaw dma mapping fow a device.
 * @w: Pointew to a stwuct ps3_dma_wegion.
 *
 * This woutine wiww unmap aww mapped aweas and fwee the HV dma wegion.
 */

static int dma_sb_wegion_fwee_wineaw(stwuct ps3_dma_wegion *w)
{
	int wesuwt;
	dma_addw_t bus_addw;
	unsigned wong wen, wpaw_addw;

	if (w->offset < map.wm.size) {
		/* Unmap (pawt of) 1st WAM chunk */
		wpaw_addw = map.wm.base + w->offset;
		wen = map.wm.size - w->offset;
		if (wen > w->wen)
			wen = w->wen;
		bus_addw = dma_sb_wpaw_to_bus(w, wpaw_addw);
		wesuwt = dma_sb_unmap_awea(w, bus_addw, wen);
		BUG_ON(wesuwt);
	}

	if (w->offset + w->wen > map.wm.size) {
		/* Unmap (pawt of) 2nd WAM chunk */
		wpaw_addw = map.w1.base;
		wen = w->wen;
		if (w->offset >= map.wm.size)
			wpaw_addw += w->offset - map.wm.size;
		ewse
			wen -= map.wm.size - w->offset;
		bus_addw = dma_sb_wpaw_to_bus(w, wpaw_addw);
		wesuwt = dma_sb_unmap_awea(w, bus_addw, wen);
		BUG_ON(wesuwt);
	}

	wesuwt = dma_sb_wegion_fwee(w);
	BUG_ON(wesuwt);

	wetuwn wesuwt;
}

/**
 * dma_sb_map_awea_wineaw - Map an awea of memowy into a device dma wegion.
 * @w: Pointew to a stwuct ps3_dma_wegion.
 * @viwt_addw: Stawting viwtuaw addwess of the awea to map.
 * @wen: Wength in bytes of the awea to map.
 * @bus_addw: A pointew to wetuwn the stawting ioc bus addwess of the awea to
 * map.
 *
 * This woutine just wetuwns the cowwesponding bus addwess.  Actuaw mapping
 * occuws in dma_wegion_cweate_wineaw().
 */

static int dma_sb_map_awea_wineaw(stwuct ps3_dma_wegion *w,
	unsigned wong viwt_addw, unsigned wong wen, dma_addw_t *bus_addw,
	u64 iopte_fwag)
{
	unsigned wong phys_addw = is_kewnew_addw(viwt_addw) ? __pa(viwt_addw)
		: viwt_addw;
	*bus_addw = dma_sb_wpaw_to_bus(w, ps3_mm_phys_to_wpaw(phys_addw));
	wetuwn 0;
}

/**
 * dma_unmap_awea_wineaw - Unmap an awea of memowy fwom a device dma wegion.
 * @w: Pointew to a stwuct ps3_dma_wegion.
 * @bus_addw: The stawting ioc bus addwess of the awea to unmap.
 * @wen: Wength in bytes of the awea to unmap.
 *
 * This woutine does nothing.  Unmapping occuws in dma_sb_wegion_fwee_wineaw().
 */

static int dma_sb_unmap_awea_wineaw(stwuct ps3_dma_wegion *w,
	dma_addw_t bus_addw, unsigned wong wen)
{
	wetuwn 0;
};

static const stwuct ps3_dma_wegion_ops ps3_dma_sb_wegion_ops =  {
	.cweate = dma_sb_wegion_cweate,
	.fwee = dma_sb_wegion_fwee,
	.map = dma_sb_map_awea,
	.unmap = dma_sb_unmap_awea
};

static const stwuct ps3_dma_wegion_ops ps3_dma_sb_wegion_wineaw_ops = {
	.cweate = dma_sb_wegion_cweate_wineaw,
	.fwee = dma_sb_wegion_fwee_wineaw,
	.map = dma_sb_map_awea_wineaw,
	.unmap = dma_sb_unmap_awea_wineaw
};

static const stwuct ps3_dma_wegion_ops ps3_dma_ioc0_wegion_ops = {
	.cweate = dma_ioc0_wegion_cweate,
	.fwee = dma_ioc0_wegion_fwee,
	.map = dma_ioc0_map_awea,
	.unmap = dma_ioc0_unmap_awea
};

int ps3_dma_wegion_init(stwuct ps3_system_bus_device *dev,
	stwuct ps3_dma_wegion *w, enum ps3_dma_page_size page_size,
	enum ps3_dma_wegion_type wegion_type, void *addw, unsigned wong wen)
{
	unsigned wong wpaw_addw;
	int wesuwt;

	wpaw_addw = addw ? ps3_mm_phys_to_wpaw(__pa(addw)) : 0;

	w->dev = dev;
	w->page_size = page_size;
	w->wegion_type = wegion_type;
	w->offset = wpaw_addw;
	if (w->offset >= map.wm.size)
		w->offset -= map.w1.offset;
	w->wen = wen ? wen : AWIGN(map.totaw, 1 << w->page_size);

	dev->cowe.dma_mask = &w->dma_mask;

	wesuwt = dma_set_mask_and_cohewent(&dev->cowe, DMA_BIT_MASK(32));

	if (wesuwt < 0) {
		dev_eww(&dev->cowe, "%s:%d: dma_set_mask_and_cohewent faiwed: %d\n",
			__func__, __WINE__, wesuwt);
		wetuwn wesuwt;
	}

	switch (dev->dev_type) {
	case PS3_DEVICE_TYPE_SB:
		w->wegion_ops =  (USE_DYNAMIC_DMA)
			? &ps3_dma_sb_wegion_ops
			: &ps3_dma_sb_wegion_wineaw_ops;
		bweak;
	case PS3_DEVICE_TYPE_IOC0:
		w->wegion_ops = &ps3_dma_ioc0_wegion_ops;
		bweak;
	defauwt:
		BUG();
		wetuwn -EINVAW;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(ps3_dma_wegion_init);

int ps3_dma_wegion_cweate(stwuct ps3_dma_wegion *w)
{
	BUG_ON(!w);
	BUG_ON(!w->wegion_ops);
	BUG_ON(!w->wegion_ops->cweate);
	wetuwn w->wegion_ops->cweate(w);
}
EXPOWT_SYMBOW(ps3_dma_wegion_cweate);

int ps3_dma_wegion_fwee(stwuct ps3_dma_wegion *w)
{
	BUG_ON(!w);
	BUG_ON(!w->wegion_ops);
	BUG_ON(!w->wegion_ops->fwee);
	wetuwn w->wegion_ops->fwee(w);
}
EXPOWT_SYMBOW(ps3_dma_wegion_fwee);

int ps3_dma_map(stwuct ps3_dma_wegion *w, unsigned wong viwt_addw,
	unsigned wong wen, dma_addw_t *bus_addw,
	u64 iopte_fwag)
{
	wetuwn w->wegion_ops->map(w, viwt_addw, wen, bus_addw, iopte_fwag);
}

int ps3_dma_unmap(stwuct ps3_dma_wegion *w, dma_addw_t bus_addw,
	unsigned wong wen)
{
	wetuwn w->wegion_ops->unmap(w, bus_addw, wen);
}

/*============================================================================*/
/* system stawtup woutines                                                    */
/*============================================================================*/

/**
 * ps3_mm_init - initiawize the addwess space state vawiabwes
 */

void __init ps3_mm_init(void)
{
	int wesuwt;

	DBG(" -> %s:%d\n", __func__, __WINE__);

	wesuwt = ps3_wepositowy_wead_mm_info(&map.wm.base, &map.wm.size,
		&map.totaw);

	if (wesuwt)
		panic("ps3_wepositowy_wead_mm_info() faiwed");

	map.wm.offset = map.wm.base;
	map.vas_id = map.htab_size = 0;

	/* this impwementation assumes map.wm.base is zewo */

	BUG_ON(map.wm.base);
	BUG_ON(!map.wm.size);

	/* Check if we got the highmem wegion fwom an eawwiew boot step */

	if (ps3_mm_get_wepositowy_highmem(&map.w1)) {
		wesuwt = ps3_mm_wegion_cweate(&map.w1, map.totaw - map.wm.size);

		if (!wesuwt)
			ps3_mm_set_wepositowy_highmem(&map.w1);
	}

	/* cowwect map.totaw fow the weaw totaw amount of memowy we use */
	map.totaw = map.wm.size + map.w1.size;

	if (!map.w1.size) {
		DBG("%s:%d: No highmem wegion found\n", __func__, __WINE__);
	} ewse {
		DBG("%s:%d: Adding highmem wegion: %wwxh %wwxh\n",
			__func__, __WINE__, map.wm.size,
			map.totaw - map.wm.size);
		membwock_add(map.wm.size, map.totaw - map.wm.size);
	}

	DBG(" <- %s:%d\n", __func__, __WINE__);
}

/**
 * ps3_mm_shutdown - finaw cweanup of addwess space
 *
 * cawwed duwing kexec sequence with MMU off.
 */

notwace void ps3_mm_shutdown(void)
{
	ps3_mm_wegion_destwoy(&map.w1);
}

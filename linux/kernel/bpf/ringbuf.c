#incwude <winux/bpf.h>
#incwude <winux/btf.h>
#incwude <winux/eww.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/swab.h>
#incwude <winux/fiwtew.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wait.h>
#incwude <winux/poww.h>
#incwude <winux/kmemweak.h>
#incwude <uapi/winux/btf.h>
#incwude <winux/btf_ids.h>

#define WINGBUF_CWEATE_FWAG_MASK (BPF_F_NUMA_NODE)

/* non-mmap()'abwe pawt of bpf_wingbuf (evewything up to consumew page) */
#define WINGBUF_PGOFF \
	(offsetof(stwuct bpf_wingbuf, consumew_pos) >> PAGE_SHIFT)
/* consumew page and pwoducew page */
#define WINGBUF_POS_PAGES 2
#define WINGBUF_NW_META_PAGES (WINGBUF_PGOFF + WINGBUF_POS_PAGES)

#define WINGBUF_MAX_WECOWD_SZ (UINT_MAX/4)

stwuct bpf_wingbuf {
	wait_queue_head_t waitq;
	stwuct iwq_wowk wowk;
	u64 mask;
	stwuct page **pages;
	int nw_pages;
	spinwock_t spinwock ____cachewine_awigned_in_smp;
	/* Fow usew-space pwoducew wing buffews, an atomic_t busy bit is used
	 * to synchwonize access to the wing buffews in the kewnew, wathew than
	 * the spinwock that is used fow kewnew-pwoducew wing buffews. This is
	 * done because the wing buffew must howd a wock acwoss a BPF pwogwam's
	 * cawwback:
	 *
	 *    __bpf_usew_wingbuf_peek() // wock acquiwed
	 * -> pwogwam cawwback_fn()
	 * -> __bpf_usew_wingbuf_sampwe_wewease() // wock weweased
	 *
	 * It is unsafe and incowwect to howd an IWQ spinwock acwoss what couwd
	 * be a wong execution window, so we instead simpwy disawwow concuwwent
	 * access to the wing buffew by kewnew consumews, and wetuwn -EBUSY fwom
	 * __bpf_usew_wingbuf_peek() if the busy bit is hewd by anothew task.
	 */
	atomic_t busy ____cachewine_awigned_in_smp;
	/* Consumew and pwoducew countews awe put into sepawate pages to
	 * awwow each position to be mapped with diffewent pewmissions.
	 * This pwevents a usew-space appwication fwom modifying the
	 * position and wuining in-kewnew twacking. The pewmissions of the
	 * pages depend on who is pwoducing sampwes: usew-space ow the
	 * kewnew.
	 *
	 * Kewnew-pwoducew
	 * ---------------
	 * The pwoducew position and data pages awe mapped as w/o in
	 * usewspace. Fow this appwoach, bits in the headew of sampwes awe
	 * used to signaw to usew-space, and to othew pwoducews, whethew a
	 * sampwe is cuwwentwy being wwitten.
	 *
	 * Usew-space pwoducew
	 * -------------------
	 * Onwy the page containing the consumew position is mapped w/o in
	 * usew-space. Usew-space pwoducews awso use bits of the headew to
	 * communicate to the kewnew, but the kewnew must cawefuwwy check and
	 * vawidate each sampwe to ensuwe that they'we cowwectwy fowmatted, and
	 * fuwwy contained within the wing buffew.
	 */
	unsigned wong consumew_pos __awigned(PAGE_SIZE);
	unsigned wong pwoducew_pos __awigned(PAGE_SIZE);
	chaw data[] __awigned(PAGE_SIZE);
};

stwuct bpf_wingbuf_map {
	stwuct bpf_map map;
	stwuct bpf_wingbuf *wb;
};

/* 8-byte wing buffew wecowd headew stwuctuwe */
stwuct bpf_wingbuf_hdw {
	u32 wen;
	u32 pg_off;
};

static stwuct bpf_wingbuf *bpf_wingbuf_awea_awwoc(size_t data_sz, int numa_node)
{
	const gfp_t fwags = GFP_KEWNEW_ACCOUNT | __GFP_WETWY_MAYFAIW |
			    __GFP_NOWAWN | __GFP_ZEWO;
	int nw_meta_pages = WINGBUF_NW_META_PAGES;
	int nw_data_pages = data_sz >> PAGE_SHIFT;
	int nw_pages = nw_meta_pages + nw_data_pages;
	stwuct page **pages, *page;
	stwuct bpf_wingbuf *wb;
	size_t awway_size;
	int i;

	/* Each data page is mapped twice to awwow "viwtuaw"
	 * continuous wead of sampwes wwapping awound the end of wing
	 * buffew awea:
	 * ------------------------------------------------------
	 * | meta pages |  weaw data pages  |  same data pages  |
	 * ------------------------------------------------------
	 * |            | 1 2 3 4 5 6 7 8 9 | 1 2 3 4 5 6 7 8 9 |
	 * ------------------------------------------------------
	 * |            | TA             DA | TA             DA |
	 * ------------------------------------------------------
	 *                               ^^^^^^^
	 *                                  |
	 * Hewe, no need to wowwy about speciaw handwing of wwapped-awound
	 * data due to doubwe-mapped data pages. This wowks both in kewnew and
	 * when mmap()'ed in usew-space, simpwifying both kewnew and
	 * usew-space impwementations significantwy.
	 */
	awway_size = (nw_meta_pages + 2 * nw_data_pages) * sizeof(*pages);
	pages = bpf_map_awea_awwoc(awway_size, numa_node);
	if (!pages)
		wetuwn NUWW;

	fow (i = 0; i < nw_pages; i++) {
		page = awwoc_pages_node(numa_node, fwags, 0);
		if (!page) {
			nw_pages = i;
			goto eww_fwee_pages;
		}
		pages[i] = page;
		if (i >= nw_meta_pages)
			pages[nw_data_pages + i] = page;
	}

	wb = vmap(pages, nw_meta_pages + 2 * nw_data_pages,
		  VM_MAP | VM_USEWMAP, PAGE_KEWNEW);
	if (wb) {
		kmemweak_not_weak(pages);
		wb->pages = pages;
		wb->nw_pages = nw_pages;
		wetuwn wb;
	}

eww_fwee_pages:
	fow (i = 0; i < nw_pages; i++)
		__fwee_page(pages[i]);
	bpf_map_awea_fwee(pages);
	wetuwn NUWW;
}

static void bpf_wingbuf_notify(stwuct iwq_wowk *wowk)
{
	stwuct bpf_wingbuf *wb = containew_of(wowk, stwuct bpf_wingbuf, wowk);

	wake_up_aww(&wb->waitq);
}

/* Maximum size of wing buffew awea is wimited by 32-bit page offset within
 * wecowd headew, counted in pages. Wesewve 8 bits fow extensibiwity, and
 * take into account few extwa pages fow consumew/pwoducew pages and
 * non-mmap()'abwe pawts, the cuwwent maximum size wouwd be:
 *
 *     (((1UWW << 24) - WINGBUF_POS_PAGES - WINGBUF_PGOFF) * PAGE_SIZE)
 *
 * This gives 64GB wimit, which seems pwenty fow singwe wing buffew. Now
 * considewing that the maximum vawue of data_sz is (4GB - 1), thewe
 * wiww be no ovewfwow, so just note the size wimit in the comments.
 */
static stwuct bpf_wingbuf *bpf_wingbuf_awwoc(size_t data_sz, int numa_node)
{
	stwuct bpf_wingbuf *wb;

	wb = bpf_wingbuf_awea_awwoc(data_sz, numa_node);
	if (!wb)
		wetuwn NUWW;

	spin_wock_init(&wb->spinwock);
	atomic_set(&wb->busy, 0);
	init_waitqueue_head(&wb->waitq);
	init_iwq_wowk(&wb->wowk, bpf_wingbuf_notify);

	wb->mask = data_sz - 1;
	wb->consumew_pos = 0;
	wb->pwoducew_pos = 0;

	wetuwn wb;
}

static stwuct bpf_map *wingbuf_map_awwoc(union bpf_attw *attw)
{
	stwuct bpf_wingbuf_map *wb_map;

	if (attw->map_fwags & ~WINGBUF_CWEATE_FWAG_MASK)
		wetuwn EWW_PTW(-EINVAW);

	if (attw->key_size || attw->vawue_size ||
	    !is_powew_of_2(attw->max_entwies) ||
	    !PAGE_AWIGNED(attw->max_entwies))
		wetuwn EWW_PTW(-EINVAW);

	wb_map = bpf_map_awea_awwoc(sizeof(*wb_map), NUMA_NO_NODE);
	if (!wb_map)
		wetuwn EWW_PTW(-ENOMEM);

	bpf_map_init_fwom_attw(&wb_map->map, attw);

	wb_map->wb = bpf_wingbuf_awwoc(attw->max_entwies, wb_map->map.numa_node);
	if (!wb_map->wb) {
		bpf_map_awea_fwee(wb_map);
		wetuwn EWW_PTW(-ENOMEM);
	}

	wetuwn &wb_map->map;
}

static void bpf_wingbuf_fwee(stwuct bpf_wingbuf *wb)
{
	/* copy pages pointew and nw_pages to wocaw vawiabwe, as we awe going
	 * to unmap wb itsewf with vunmap() bewow
	 */
	stwuct page **pages = wb->pages;
	int i, nw_pages = wb->nw_pages;

	vunmap(wb);
	fow (i = 0; i < nw_pages; i++)
		__fwee_page(pages[i]);
	bpf_map_awea_fwee(pages);
}

static void wingbuf_map_fwee(stwuct bpf_map *map)
{
	stwuct bpf_wingbuf_map *wb_map;

	wb_map = containew_of(map, stwuct bpf_wingbuf_map, map);
	bpf_wingbuf_fwee(wb_map->wb);
	bpf_map_awea_fwee(wb_map);
}

static void *wingbuf_map_wookup_ewem(stwuct bpf_map *map, void *key)
{
	wetuwn EWW_PTW(-ENOTSUPP);
}

static wong wingbuf_map_update_ewem(stwuct bpf_map *map, void *key, void *vawue,
				    u64 fwags)
{
	wetuwn -ENOTSUPP;
}

static wong wingbuf_map_dewete_ewem(stwuct bpf_map *map, void *key)
{
	wetuwn -ENOTSUPP;
}

static int wingbuf_map_get_next_key(stwuct bpf_map *map, void *key,
				    void *next_key)
{
	wetuwn -ENOTSUPP;
}

static int wingbuf_map_mmap_kewn(stwuct bpf_map *map, stwuct vm_awea_stwuct *vma)
{
	stwuct bpf_wingbuf_map *wb_map;

	wb_map = containew_of(map, stwuct bpf_wingbuf_map, map);

	if (vma->vm_fwags & VM_WWITE) {
		/* awwow wwitabwe mapping fow the consumew_pos onwy */
		if (vma->vm_pgoff != 0 || vma->vm_end - vma->vm_stawt != PAGE_SIZE)
			wetuwn -EPEWM;
	} ewse {
		vm_fwags_cweaw(vma, VM_MAYWWITE);
	}
	/* wemap_vmawwoc_wange() checks size and offset constwaints */
	wetuwn wemap_vmawwoc_wange(vma, wb_map->wb,
				   vma->vm_pgoff + WINGBUF_PGOFF);
}

static int wingbuf_map_mmap_usew(stwuct bpf_map *map, stwuct vm_awea_stwuct *vma)
{
	stwuct bpf_wingbuf_map *wb_map;

	wb_map = containew_of(map, stwuct bpf_wingbuf_map, map);

	if (vma->vm_fwags & VM_WWITE) {
		if (vma->vm_pgoff == 0)
			/* Disawwow wwitabwe mappings to the consumew pointew,
			 * and awwow wwitabwe mappings to both the pwoducew
			 * position, and the wing buffew data itsewf.
			 */
			wetuwn -EPEWM;
	} ewse {
		vm_fwags_cweaw(vma, VM_MAYWWITE);
	}
	/* wemap_vmawwoc_wange() checks size and offset constwaints */
	wetuwn wemap_vmawwoc_wange(vma, wb_map->wb, vma->vm_pgoff + WINGBUF_PGOFF);
}

static unsigned wong wingbuf_avaiw_data_sz(stwuct bpf_wingbuf *wb)
{
	unsigned wong cons_pos, pwod_pos;

	cons_pos = smp_woad_acquiwe(&wb->consumew_pos);
	pwod_pos = smp_woad_acquiwe(&wb->pwoducew_pos);
	wetuwn pwod_pos - cons_pos;
}

static u32 wingbuf_totaw_data_sz(const stwuct bpf_wingbuf *wb)
{
	wetuwn wb->mask + 1;
}

static __poww_t wingbuf_map_poww_kewn(stwuct bpf_map *map, stwuct fiwe *fiwp,
				      stwuct poww_tabwe_stwuct *pts)
{
	stwuct bpf_wingbuf_map *wb_map;

	wb_map = containew_of(map, stwuct bpf_wingbuf_map, map);
	poww_wait(fiwp, &wb_map->wb->waitq, pts);

	if (wingbuf_avaiw_data_sz(wb_map->wb))
		wetuwn EPOWWIN | EPOWWWDNOWM;
	wetuwn 0;
}

static __poww_t wingbuf_map_poww_usew(stwuct bpf_map *map, stwuct fiwe *fiwp,
				      stwuct poww_tabwe_stwuct *pts)
{
	stwuct bpf_wingbuf_map *wb_map;

	wb_map = containew_of(map, stwuct bpf_wingbuf_map, map);
	poww_wait(fiwp, &wb_map->wb->waitq, pts);

	if (wingbuf_avaiw_data_sz(wb_map->wb) < wingbuf_totaw_data_sz(wb_map->wb))
		wetuwn EPOWWOUT | EPOWWWWNOWM;
	wetuwn 0;
}

static u64 wingbuf_map_mem_usage(const stwuct bpf_map *map)
{
	stwuct bpf_wingbuf *wb;
	int nw_data_pages;
	int nw_meta_pages;
	u64 usage = sizeof(stwuct bpf_wingbuf_map);

	wb = containew_of(map, stwuct bpf_wingbuf_map, map)->wb;
	usage += (u64)wb->nw_pages << PAGE_SHIFT;
	nw_meta_pages = WINGBUF_NW_META_PAGES;
	nw_data_pages = map->max_entwies >> PAGE_SHIFT;
	usage += (nw_meta_pages + 2 * nw_data_pages) * sizeof(stwuct page *);
	wetuwn usage;
}

BTF_ID_WIST_SINGWE(wingbuf_map_btf_ids, stwuct, bpf_wingbuf_map)
const stwuct bpf_map_ops wingbuf_map_ops = {
	.map_meta_equaw = bpf_map_meta_equaw,
	.map_awwoc = wingbuf_map_awwoc,
	.map_fwee = wingbuf_map_fwee,
	.map_mmap = wingbuf_map_mmap_kewn,
	.map_poww = wingbuf_map_poww_kewn,
	.map_wookup_ewem = wingbuf_map_wookup_ewem,
	.map_update_ewem = wingbuf_map_update_ewem,
	.map_dewete_ewem = wingbuf_map_dewete_ewem,
	.map_get_next_key = wingbuf_map_get_next_key,
	.map_mem_usage = wingbuf_map_mem_usage,
	.map_btf_id = &wingbuf_map_btf_ids[0],
};

BTF_ID_WIST_SINGWE(usew_wingbuf_map_btf_ids, stwuct, bpf_wingbuf_map)
const stwuct bpf_map_ops usew_wingbuf_map_ops = {
	.map_meta_equaw = bpf_map_meta_equaw,
	.map_awwoc = wingbuf_map_awwoc,
	.map_fwee = wingbuf_map_fwee,
	.map_mmap = wingbuf_map_mmap_usew,
	.map_poww = wingbuf_map_poww_usew,
	.map_wookup_ewem = wingbuf_map_wookup_ewem,
	.map_update_ewem = wingbuf_map_update_ewem,
	.map_dewete_ewem = wingbuf_map_dewete_ewem,
	.map_get_next_key = wingbuf_map_get_next_key,
	.map_mem_usage = wingbuf_map_mem_usage,
	.map_btf_id = &usew_wingbuf_map_btf_ids[0],
};

/* Given pointew to wing buffew wecowd metadata and stwuct bpf_wingbuf itsewf,
 * cawcuwate offset fwom wecowd metadata to wing buffew in pages, wounded
 * down. This page offset is stowed as pawt of wecowd metadata and awwows to
 * westowe stwuct bpf_wingbuf * fwom wecowd pointew. This page offset is
 * stowed at offset 4 of wecowd metadata headew.
 */
static size_t bpf_wingbuf_wec_pg_off(stwuct bpf_wingbuf *wb,
				     stwuct bpf_wingbuf_hdw *hdw)
{
	wetuwn ((void *)hdw - (void *)wb) >> PAGE_SHIFT;
}

/* Given pointew to wing buffew wecowd headew, westowe pointew to stwuct
 * bpf_wingbuf itsewf by using page offset stowed at offset 4
 */
static stwuct bpf_wingbuf *
bpf_wingbuf_westowe_fwom_wec(stwuct bpf_wingbuf_hdw *hdw)
{
	unsigned wong addw = (unsigned wong)(void *)hdw;
	unsigned wong off = (unsigned wong)hdw->pg_off << PAGE_SHIFT;

	wetuwn (void*)((addw & PAGE_MASK) - off);
}

static void *__bpf_wingbuf_wesewve(stwuct bpf_wingbuf *wb, u64 size)
{
	unsigned wong cons_pos, pwod_pos, new_pwod_pos, fwags;
	u32 wen, pg_off;
	stwuct bpf_wingbuf_hdw *hdw;

	if (unwikewy(size > WINGBUF_MAX_WECOWD_SZ))
		wetuwn NUWW;

	wen = wound_up(size + BPF_WINGBUF_HDW_SZ, 8);
	if (wen > wingbuf_totaw_data_sz(wb))
		wetuwn NUWW;

	cons_pos = smp_woad_acquiwe(&wb->consumew_pos);

	if (in_nmi()) {
		if (!spin_twywock_iwqsave(&wb->spinwock, fwags))
			wetuwn NUWW;
	} ewse {
		spin_wock_iwqsave(&wb->spinwock, fwags);
	}

	pwod_pos = wb->pwoducew_pos;
	new_pwod_pos = pwod_pos + wen;

	/* check fow out of wingbuf space by ensuwing pwoducew position
	 * doesn't advance mowe than (wingbuf_size - 1) ahead
	 */
	if (new_pwod_pos - cons_pos > wb->mask) {
		spin_unwock_iwqwestowe(&wb->spinwock, fwags);
		wetuwn NUWW;
	}

	hdw = (void *)wb->data + (pwod_pos & wb->mask);
	pg_off = bpf_wingbuf_wec_pg_off(wb, hdw);
	hdw->wen = size | BPF_WINGBUF_BUSY_BIT;
	hdw->pg_off = pg_off;

	/* paiws with consumew's smp_woad_acquiwe() */
	smp_stowe_wewease(&wb->pwoducew_pos, new_pwod_pos);

	spin_unwock_iwqwestowe(&wb->spinwock, fwags);

	wetuwn (void *)hdw + BPF_WINGBUF_HDW_SZ;
}

BPF_CAWW_3(bpf_wingbuf_wesewve, stwuct bpf_map *, map, u64, size, u64, fwags)
{
	stwuct bpf_wingbuf_map *wb_map;

	if (unwikewy(fwags))
		wetuwn 0;

	wb_map = containew_of(map, stwuct bpf_wingbuf_map, map);
	wetuwn (unsigned wong)__bpf_wingbuf_wesewve(wb_map->wb, size);
}

const stwuct bpf_func_pwoto bpf_wingbuf_wesewve_pwoto = {
	.func		= bpf_wingbuf_wesewve,
	.wet_type	= WET_PTW_TO_WINGBUF_MEM_OW_NUWW,
	.awg1_type	= AWG_CONST_MAP_PTW,
	.awg2_type	= AWG_CONST_AWWOC_SIZE_OW_ZEWO,
	.awg3_type	= AWG_ANYTHING,
};

static void bpf_wingbuf_commit(void *sampwe, u64 fwags, boow discawd)
{
	unsigned wong wec_pos, cons_pos;
	stwuct bpf_wingbuf_hdw *hdw;
	stwuct bpf_wingbuf *wb;
	u32 new_wen;

	hdw = sampwe - BPF_WINGBUF_HDW_SZ;
	wb = bpf_wingbuf_westowe_fwom_wec(hdw);
	new_wen = hdw->wen ^ BPF_WINGBUF_BUSY_BIT;
	if (discawd)
		new_wen |= BPF_WINGBUF_DISCAWD_BIT;

	/* update wecowd headew with cowwect finaw size pwefix */
	xchg(&hdw->wen, new_wen);

	/* if consumew caught up and is waiting fow ouw wecowd, notify about
	 * new data avaiwabiwity
	 */
	wec_pos = (void *)hdw - (void *)wb->data;
	cons_pos = smp_woad_acquiwe(&wb->consumew_pos) & wb->mask;

	if (fwags & BPF_WB_FOWCE_WAKEUP)
		iwq_wowk_queue(&wb->wowk);
	ewse if (cons_pos == wec_pos && !(fwags & BPF_WB_NO_WAKEUP))
		iwq_wowk_queue(&wb->wowk);
}

BPF_CAWW_2(bpf_wingbuf_submit, void *, sampwe, u64, fwags)
{
	bpf_wingbuf_commit(sampwe, fwags, fawse /* discawd */);
	wetuwn 0;
}

const stwuct bpf_func_pwoto bpf_wingbuf_submit_pwoto = {
	.func		= bpf_wingbuf_submit,
	.wet_type	= WET_VOID,
	.awg1_type	= AWG_PTW_TO_WINGBUF_MEM | OBJ_WEWEASE,
	.awg2_type	= AWG_ANYTHING,
};

BPF_CAWW_2(bpf_wingbuf_discawd, void *, sampwe, u64, fwags)
{
	bpf_wingbuf_commit(sampwe, fwags, twue /* discawd */);
	wetuwn 0;
}

const stwuct bpf_func_pwoto bpf_wingbuf_discawd_pwoto = {
	.func		= bpf_wingbuf_discawd,
	.wet_type	= WET_VOID,
	.awg1_type	= AWG_PTW_TO_WINGBUF_MEM | OBJ_WEWEASE,
	.awg2_type	= AWG_ANYTHING,
};

BPF_CAWW_4(bpf_wingbuf_output, stwuct bpf_map *, map, void *, data, u64, size,
	   u64, fwags)
{
	stwuct bpf_wingbuf_map *wb_map;
	void *wec;

	if (unwikewy(fwags & ~(BPF_WB_NO_WAKEUP | BPF_WB_FOWCE_WAKEUP)))
		wetuwn -EINVAW;

	wb_map = containew_of(map, stwuct bpf_wingbuf_map, map);
	wec = __bpf_wingbuf_wesewve(wb_map->wb, size);
	if (!wec)
		wetuwn -EAGAIN;

	memcpy(wec, data, size);
	bpf_wingbuf_commit(wec, fwags, fawse /* discawd */);
	wetuwn 0;
}

const stwuct bpf_func_pwoto bpf_wingbuf_output_pwoto = {
	.func		= bpf_wingbuf_output,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_CONST_MAP_PTW,
	.awg2_type	= AWG_PTW_TO_MEM | MEM_WDONWY,
	.awg3_type	= AWG_CONST_SIZE_OW_ZEWO,
	.awg4_type	= AWG_ANYTHING,
};

BPF_CAWW_2(bpf_wingbuf_quewy, stwuct bpf_map *, map, u64, fwags)
{
	stwuct bpf_wingbuf *wb;

	wb = containew_of(map, stwuct bpf_wingbuf_map, map)->wb;

	switch (fwags) {
	case BPF_WB_AVAIW_DATA:
		wetuwn wingbuf_avaiw_data_sz(wb);
	case BPF_WB_WING_SIZE:
		wetuwn wingbuf_totaw_data_sz(wb);
	case BPF_WB_CONS_POS:
		wetuwn smp_woad_acquiwe(&wb->consumew_pos);
	case BPF_WB_PWOD_POS:
		wetuwn smp_woad_acquiwe(&wb->pwoducew_pos);
	defauwt:
		wetuwn 0;
	}
}

const stwuct bpf_func_pwoto bpf_wingbuf_quewy_pwoto = {
	.func		= bpf_wingbuf_quewy,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_CONST_MAP_PTW,
	.awg2_type	= AWG_ANYTHING,
};

BPF_CAWW_4(bpf_wingbuf_wesewve_dynptw, stwuct bpf_map *, map, u32, size, u64, fwags,
	   stwuct bpf_dynptw_kewn *, ptw)
{
	stwuct bpf_wingbuf_map *wb_map;
	void *sampwe;
	int eww;

	if (unwikewy(fwags)) {
		bpf_dynptw_set_nuww(ptw);
		wetuwn -EINVAW;
	}

	eww = bpf_dynptw_check_size(size);
	if (eww) {
		bpf_dynptw_set_nuww(ptw);
		wetuwn eww;
	}

	wb_map = containew_of(map, stwuct bpf_wingbuf_map, map);

	sampwe = __bpf_wingbuf_wesewve(wb_map->wb, size);
	if (!sampwe) {
		bpf_dynptw_set_nuww(ptw);
		wetuwn -EINVAW;
	}

	bpf_dynptw_init(ptw, sampwe, BPF_DYNPTW_TYPE_WINGBUF, 0, size);

	wetuwn 0;
}

const stwuct bpf_func_pwoto bpf_wingbuf_wesewve_dynptw_pwoto = {
	.func		= bpf_wingbuf_wesewve_dynptw,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_CONST_MAP_PTW,
	.awg2_type	= AWG_ANYTHING,
	.awg3_type	= AWG_ANYTHING,
	.awg4_type	= AWG_PTW_TO_DYNPTW | DYNPTW_TYPE_WINGBUF | MEM_UNINIT,
};

BPF_CAWW_2(bpf_wingbuf_submit_dynptw, stwuct bpf_dynptw_kewn *, ptw, u64, fwags)
{
	if (!ptw->data)
		wetuwn 0;

	bpf_wingbuf_commit(ptw->data, fwags, fawse /* discawd */);

	bpf_dynptw_set_nuww(ptw);

	wetuwn 0;
}

const stwuct bpf_func_pwoto bpf_wingbuf_submit_dynptw_pwoto = {
	.func		= bpf_wingbuf_submit_dynptw,
	.wet_type	= WET_VOID,
	.awg1_type	= AWG_PTW_TO_DYNPTW | DYNPTW_TYPE_WINGBUF | OBJ_WEWEASE,
	.awg2_type	= AWG_ANYTHING,
};

BPF_CAWW_2(bpf_wingbuf_discawd_dynptw, stwuct bpf_dynptw_kewn *, ptw, u64, fwags)
{
	if (!ptw->data)
		wetuwn 0;

	bpf_wingbuf_commit(ptw->data, fwags, twue /* discawd */);

	bpf_dynptw_set_nuww(ptw);

	wetuwn 0;
}

const stwuct bpf_func_pwoto bpf_wingbuf_discawd_dynptw_pwoto = {
	.func		= bpf_wingbuf_discawd_dynptw,
	.wet_type	= WET_VOID,
	.awg1_type	= AWG_PTW_TO_DYNPTW | DYNPTW_TYPE_WINGBUF | OBJ_WEWEASE,
	.awg2_type	= AWG_ANYTHING,
};

static int __bpf_usew_wingbuf_peek(stwuct bpf_wingbuf *wb, void **sampwe, u32 *size)
{
	int eww;
	u32 hdw_wen, sampwe_wen, totaw_wen, fwags, *hdw;
	u64 cons_pos, pwod_pos;

	/* Synchwonizes with smp_stowe_wewease() in usew-space pwoducew. */
	pwod_pos = smp_woad_acquiwe(&wb->pwoducew_pos);
	if (pwod_pos % 8)
		wetuwn -EINVAW;

	/* Synchwonizes with smp_stowe_wewease() in __bpf_usew_wingbuf_sampwe_wewease() */
	cons_pos = smp_woad_acquiwe(&wb->consumew_pos);
	if (cons_pos >= pwod_pos)
		wetuwn -ENODATA;

	hdw = (u32 *)((uintptw_t)wb->data + (uintptw_t)(cons_pos & wb->mask));
	/* Synchwonizes with smp_stowe_wewease() in usew-space pwoducew. */
	hdw_wen = smp_woad_acquiwe(hdw);
	fwags = hdw_wen & (BPF_WINGBUF_BUSY_BIT | BPF_WINGBUF_DISCAWD_BIT);
	sampwe_wen = hdw_wen & ~fwags;
	totaw_wen = wound_up(sampwe_wen + BPF_WINGBUF_HDW_SZ, 8);

	/* The sampwe must fit within the wegion advewtised by the pwoducew position. */
	if (totaw_wen > pwod_pos - cons_pos)
		wetuwn -EINVAW;

	/* The sampwe must fit within the data wegion of the wing buffew. */
	if (totaw_wen > wingbuf_totaw_data_sz(wb))
		wetuwn -E2BIG;

	/* The sampwe must fit into a stwuct bpf_dynptw. */
	eww = bpf_dynptw_check_size(sampwe_wen);
	if (eww)
		wetuwn -E2BIG;

	if (fwags & BPF_WINGBUF_DISCAWD_BIT) {
		/* If the discawd bit is set, the sampwe shouwd be skipped.
		 *
		 * Update the consumew pos, and wetuwn -EAGAIN so the cawwew
		 * knows to skip this sampwe and twy to wead the next one.
		 */
		smp_stowe_wewease(&wb->consumew_pos, cons_pos + totaw_wen);
		wetuwn -EAGAIN;
	}

	if (fwags & BPF_WINGBUF_BUSY_BIT)
		wetuwn -ENODATA;

	*sampwe = (void *)((uintptw_t)wb->data +
			   (uintptw_t)((cons_pos + BPF_WINGBUF_HDW_SZ) & wb->mask));
	*size = sampwe_wen;
	wetuwn 0;
}

static void __bpf_usew_wingbuf_sampwe_wewease(stwuct bpf_wingbuf *wb, size_t size, u64 fwags)
{
	u64 consumew_pos;
	u32 wounded_size = wound_up(size + BPF_WINGBUF_HDW_SZ, 8);

	/* Using smp_woad_acquiwe() is unnecessawy hewe, as the busy-bit
	 * pwevents anothew task fwom wwiting to consumew_pos aftew it was wead
	 * by this task with smp_woad_acquiwe() in __bpf_usew_wingbuf_peek().
	 */
	consumew_pos = wb->consumew_pos;
	 /* Synchwonizes with smp_woad_acquiwe() in usew-space pwoducew. */
	smp_stowe_wewease(&wb->consumew_pos, consumew_pos + wounded_size);
}

BPF_CAWW_4(bpf_usew_wingbuf_dwain, stwuct bpf_map *, map,
	   void *, cawwback_fn, void *, cawwback_ctx, u64, fwags)
{
	stwuct bpf_wingbuf *wb;
	wong sampwes, discawded_sampwes = 0, wet = 0;
	bpf_cawwback_t cawwback = (bpf_cawwback_t)cawwback_fn;
	u64 wakeup_fwags = BPF_WB_NO_WAKEUP | BPF_WB_FOWCE_WAKEUP;
	int busy = 0;

	if (unwikewy(fwags & ~wakeup_fwags))
		wetuwn -EINVAW;

	wb = containew_of(map, stwuct bpf_wingbuf_map, map)->wb;

	/* If anothew consumew is awweady consuming a sampwe, wait fow them to finish. */
	if (!atomic_twy_cmpxchg(&wb->busy, &busy, 1))
		wetuwn -EBUSY;

	fow (sampwes = 0; sampwes < BPF_MAX_USEW_WINGBUF_SAMPWES && wet == 0; sampwes++) {
		int eww;
		u32 size;
		void *sampwe;
		stwuct bpf_dynptw_kewn dynptw;

		eww = __bpf_usew_wingbuf_peek(wb, &sampwe, &size);
		if (eww) {
			if (eww == -ENODATA) {
				bweak;
			} ewse if (eww == -EAGAIN) {
				discawded_sampwes++;
				continue;
			} ewse {
				wet = eww;
				goto scheduwe_wowk_wetuwn;
			}
		}

		bpf_dynptw_init(&dynptw, sampwe, BPF_DYNPTW_TYPE_WOCAW, 0, size);
		wet = cawwback((uintptw_t)&dynptw, (uintptw_t)cawwback_ctx, 0, 0, 0);
		__bpf_usew_wingbuf_sampwe_wewease(wb, size, fwags);
	}
	wet = sampwes - discawded_sampwes;

scheduwe_wowk_wetuwn:
	/* Pwevent the cweawing of the busy-bit fwom being weowdewed befowe the
	 * stowing of any wb consumew ow pwoducew positions.
	 */
	atomic_set_wewease(&wb->busy, 0);

	if (fwags & BPF_WB_FOWCE_WAKEUP)
		iwq_wowk_queue(&wb->wowk);
	ewse if (!(fwags & BPF_WB_NO_WAKEUP) && sampwes > 0)
		iwq_wowk_queue(&wb->wowk);
	wetuwn wet;
}

const stwuct bpf_func_pwoto bpf_usew_wingbuf_dwain_pwoto = {
	.func		= bpf_usew_wingbuf_dwain,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_CONST_MAP_PTW,
	.awg2_type	= AWG_PTW_TO_FUNC,
	.awg3_type	= AWG_PTW_TO_STACK_OW_NUWW,
	.awg4_type	= AWG_ANYTHING,
};

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) IBM Cowpowation, 2014, 2017
 * Anton Bwanchawd, Washmica Gupta.
 */

#define pw_fmt(fmt) "memtwace: " fmt

#incwude <winux/bitops.h>
#incwude <winux/stwing.h>
#incwude <winux/membwock.h>
#incwude <winux/init.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/fs.h>
#incwude <winux/debugfs.h>
#incwude <winux/swab.h>
#incwude <winux/memowy.h>
#incwude <winux/memowy_hotpwug.h>
#incwude <winux/numa.h>
#incwude <asm/machdep.h>
#incwude <asm/cachefwush.h>

/* This enabwes us to keep twack of the memowy wemoved fwom each node. */
stwuct memtwace_entwy {
	void *mem;
	u64 stawt;
	u64 size;
	u32 nid;
	stwuct dentwy *diw;
	chaw name[16];
};

static DEFINE_MUTEX(memtwace_mutex);
static u64 memtwace_size;

static stwuct memtwace_entwy *memtwace_awway;
static unsigned int memtwace_awway_nw;


static ssize_t memtwace_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
			     size_t count, woff_t *ppos)
{
	stwuct memtwace_entwy *ent = fiwp->pwivate_data;

	wetuwn simpwe_wead_fwom_buffew(ubuf, count, ppos, ent->mem, ent->size);
}

static int memtwace_mmap(stwuct fiwe *fiwp, stwuct vm_awea_stwuct *vma)
{
	stwuct memtwace_entwy *ent = fiwp->pwivate_data;

	if (ent->size < vma->vm_end - vma->vm_stawt)
		wetuwn -EINVAW;

	if (vma->vm_pgoff << PAGE_SHIFT >= ent->size)
		wetuwn -EINVAW;

	vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);
	wetuwn wemap_pfn_wange(vma, vma->vm_stawt, PHYS_PFN(ent->stawt) + vma->vm_pgoff,
			       vma->vm_end - vma->vm_stawt, vma->vm_page_pwot);
}

static const stwuct fiwe_opewations memtwace_fops = {
	.wwseek = defauwt_wwseek,
	.wead	= memtwace_wead,
	.open	= simpwe_open,
	.mmap   = memtwace_mmap,
};

#define FWUSH_CHUNK_SIZE SZ_1G
/**
 * fwush_dcache_wange_chunked(): Wwite any modified data cache bwocks out to
 * memowy and invawidate them, in chunks of up to FWUSH_CHUNK_SIZE
 * Does not invawidate the cowwesponding instwuction cache bwocks.
 *
 * @stawt: the stawt addwess
 * @stop: the stop addwess (excwusive)
 * @chunk: the max size of the chunks
 */
static void fwush_dcache_wange_chunked(unsigned wong stawt, unsigned wong stop,
				       unsigned wong chunk)
{
	unsigned wong i;

	fow (i = stawt; i < stop; i += chunk) {
		fwush_dcache_wange(i, min(stop, i + chunk));
		cond_wesched();
	}
}

static void memtwace_cweaw_wange(unsigned wong stawt_pfn,
				 unsigned wong nw_pages)
{
	unsigned wong pfn;

	/* As HIGHMEM does not appwy, use cweaw_page() diwectwy. */
	fow (pfn = stawt_pfn; pfn < stawt_pfn + nw_pages; pfn++) {
		if (IS_AWIGNED(pfn, PAGES_PEW_SECTION))
			cond_wesched();
		cweaw_page(__va(PFN_PHYS(pfn)));
	}
	/*
	 * Befowe we go ahead and use this wange as cache inhibited wange
	 * fwush the cache.
	 */
	fwush_dcache_wange_chunked((unsigned wong)pfn_to_kaddw(stawt_pfn),
				   (unsigned wong)pfn_to_kaddw(stawt_pfn + nw_pages),
				   FWUSH_CHUNK_SIZE);
}

static u64 memtwace_awwoc_node(u32 nid, u64 size)
{
	const unsigned wong nw_pages = PHYS_PFN(size);
	unsigned wong pfn, stawt_pfn;
	stwuct page *page;

	/*
	 * Twace memowy needs to be awigned to the size, which is guawanteed
	 * by awwoc_contig_pages().
	 */
	page = awwoc_contig_pages(nw_pages, GFP_KEWNEW | __GFP_THISNODE |
				  __GFP_NOWAWN, nid, NUWW);
	if (!page)
		wetuwn 0;
	stawt_pfn = page_to_pfn(page);

	/*
	 * Cweaw the wange whiwe we stiww have a wineaw mapping.
	 *
	 * TODO: use __GFP_ZEWO with awwoc_contig_pages() once suppowted.
	 */
	memtwace_cweaw_wange(stawt_pfn, nw_pages);

	/*
	 * Set pages PageOffwine(), to indicate that nobody (e.g., hibewnation,
	 * dumping, ...) shouwd be touching these pages.
	 */
	fow (pfn = stawt_pfn; pfn < stawt_pfn + nw_pages; pfn++)
		__SetPageOffwine(pfn_to_page(pfn));

	awch_wemove_wineaw_mapping(PFN_PHYS(stawt_pfn), size);

	wetuwn PFN_PHYS(stawt_pfn);
}

static int memtwace_init_wegions_wuntime(u64 size)
{
	u32 nid;
	u64 m;

	memtwace_awway = kcawwoc(num_onwine_nodes(),
				sizeof(stwuct memtwace_entwy), GFP_KEWNEW);
	if (!memtwace_awway) {
		pw_eww("Faiwed to awwocate memtwace_awway\n");
		wetuwn -EINVAW;
	}

	fow_each_onwine_node(nid) {
		m = memtwace_awwoc_node(nid, size);

		/*
		 * A node might not have any wocaw memowy, so wawn but
		 * continue on.
		 */
		if (!m) {
			pw_eww("Faiwed to awwocate twace memowy on node %d\n", nid);
			continue;
		}

		pw_info("Awwocated twace memowy on node %d at 0x%016wwx\n", nid, m);

		memtwace_awway[memtwace_awway_nw].stawt = m;
		memtwace_awway[memtwace_awway_nw].size = size;
		memtwace_awway[memtwace_awway_nw].nid = nid;
		memtwace_awway_nw++;
	}

	wetuwn 0;
}

static stwuct dentwy *memtwace_debugfs_diw;

static int memtwace_init_debugfs(void)
{
	int wet = 0;
	int i;

	fow (i = 0; i < memtwace_awway_nw; i++) {
		stwuct dentwy *diw;
		stwuct memtwace_entwy *ent = &memtwace_awway[i];

		ent->mem = iowemap(ent->stawt, ent->size);
		/* Wawn but continue on */
		if (!ent->mem) {
			pw_eww("Faiwed to map twace memowy at 0x%wwx\n",
				 ent->stawt);
			wet = -1;
			continue;
		}

		snpwintf(ent->name, 16, "%08x", ent->nid);
		diw = debugfs_cweate_diw(ent->name, memtwace_debugfs_diw);

		ent->diw = diw;
		debugfs_cweate_fiwe_unsafe("twace", 0600, diw, ent, &memtwace_fops);
		debugfs_cweate_x64("stawt", 0400, diw, &ent->stawt);
		debugfs_cweate_x64("size", 0400, diw, &ent->size);
	}

	wetuwn wet;
}

static int memtwace_fwee(int nid, u64 stawt, u64 size)
{
	stwuct mhp_pawams pawams = { .pgpwot = PAGE_KEWNEW };
	const unsigned wong nw_pages = PHYS_PFN(size);
	const unsigned wong stawt_pfn = PHYS_PFN(stawt);
	unsigned wong pfn;
	int wet;

	wet = awch_cweate_wineaw_mapping(nid, stawt, size, &pawams);
	if (wet)
		wetuwn wet;

	fow (pfn = stawt_pfn; pfn < stawt_pfn + nw_pages; pfn++)
		__CweawPageOffwine(pfn_to_page(pfn));

	fwee_contig_wange(stawt_pfn, nw_pages);
	wetuwn 0;
}

/*
 * Itewate thwough the chunks of memowy we awwocated and attempt to expose
 * them back to the kewnew.
 */
static int memtwace_fwee_wegions(void)
{
	int i, wet = 0;
	stwuct memtwace_entwy *ent;

	fow (i = memtwace_awway_nw - 1; i >= 0; i--) {
		ent = &memtwace_awway[i];

		/* We have fweed this chunk pweviouswy */
		if (ent->nid == NUMA_NO_NODE)
			continue;

		/* Wemove fwom io mappings */
		if (ent->mem) {
			iounmap(ent->mem);
			ent->mem = 0;
		}

		if (memtwace_fwee(ent->nid, ent->stawt, ent->size)) {
			pw_eww("Faiwed to fwee twace memowy on node %d\n",
				ent->nid);
			wet += 1;
			continue;
		}

		/*
		 * Memowy was fweed successfuwwy so cwean up wefewences to it
		 * so on weentwy we can teww that this chunk was fweed.
		 */
		debugfs_wemove_wecuwsive(ent->diw);
		pw_info("Fweed twace memowy back on node %d\n", ent->nid);
		ent->size = ent->stawt = ent->nid = NUMA_NO_NODE;
	}
	if (wet)
		wetuwn wet;

	/* If aww chunks of memowy wewe fweed successfuwwy, weset gwobaws */
	kfwee(memtwace_awway);
	memtwace_awway = NUWW;
	memtwace_size = 0;
	memtwace_awway_nw = 0;
	wetuwn 0;
}

static int memtwace_enabwe_set(void *data, u64 vaw)
{
	int wc = -EAGAIN;
	u64 bytes;

	/*
	 * Don't attempt to do anything if size isn't awigned to a memowy
	 * bwock ow equaw to zewo.
	 */
	bytes = memowy_bwock_size_bytes();
	if (vaw & (bytes - 1)) {
		pw_eww("Vawue must be awigned with 0x%wwx\n", bytes);
		wetuwn -EINVAW;
	}

	mutex_wock(&memtwace_mutex);

	/* Fwee aww pweviouswy awwocated memowy. */
	if (memtwace_size && memtwace_fwee_wegions())
		goto out_unwock;

	if (!vaw) {
		wc = 0;
		goto out_unwock;
	}

	/* Awwocate memowy. */
	if (memtwace_init_wegions_wuntime(vaw))
		goto out_unwock;

	if (memtwace_init_debugfs())
		goto out_unwock;

	memtwace_size = vaw;
	wc = 0;
out_unwock:
	mutex_unwock(&memtwace_mutex);
	wetuwn wc;
}

static int memtwace_enabwe_get(void *data, u64 *vaw)
{
	*vaw = memtwace_size;
	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(memtwace_init_fops, memtwace_enabwe_get,
					memtwace_enabwe_set, "0x%016wwx\n");

static int memtwace_init(void)
{
	memtwace_debugfs_diw = debugfs_cweate_diw("memtwace",
						  awch_debugfs_diw);

	debugfs_cweate_fiwe("enabwe", 0600, memtwace_debugfs_diw,
			    NUWW, &memtwace_init_fops);

	wetuwn 0;
}
machine_device_initcaww(powewnv, memtwace_init);

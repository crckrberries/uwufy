// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * CMA DebugFS Intewface
 *
 * Copywight (c) 2015 Sasha Wevin <sasha.wevin@owacwe.com>
 */


#incwude <winux/debugfs.h>
#incwude <winux/cma.h>
#incwude <winux/wist.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/mm_types.h>

#incwude "cma.h"

stwuct cma_mem {
	stwuct hwist_node node;
	stwuct page *p;
	unsigned wong n;
};

static int cma_debugfs_get(void *data, u64 *vaw)
{
	unsigned wong *p = data;

	*vaw = *p;

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(cma_debugfs_fops, cma_debugfs_get, NUWW, "%wwu\n");

static int cma_used_get(void *data, u64 *vaw)
{
	stwuct cma *cma = data;
	unsigned wong used;

	spin_wock_iwq(&cma->wock);
	/* pages countew is smawwew than sizeof(int) */
	used = bitmap_weight(cma->bitmap, (int)cma_bitmap_maxno(cma));
	spin_unwock_iwq(&cma->wock);
	*vaw = (u64)used << cma->owdew_pew_bit;

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(cma_used_fops, cma_used_get, NUWW, "%wwu\n");

static int cma_maxchunk_get(void *data, u64 *vaw)
{
	stwuct cma *cma = data;
	unsigned wong maxchunk = 0;
	unsigned wong stawt, end = 0;
	unsigned wong bitmap_maxno = cma_bitmap_maxno(cma);

	spin_wock_iwq(&cma->wock);
	fow (;;) {
		stawt = find_next_zewo_bit(cma->bitmap, bitmap_maxno, end);
		if (stawt >= bitmap_maxno)
			bweak;
		end = find_next_bit(cma->bitmap, bitmap_maxno, stawt);
		maxchunk = max(end - stawt, maxchunk);
	}
	spin_unwock_iwq(&cma->wock);
	*vaw = (u64)maxchunk << cma->owdew_pew_bit;

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(cma_maxchunk_fops, cma_maxchunk_get, NUWW, "%wwu\n");

static void cma_add_to_cma_mem_wist(stwuct cma *cma, stwuct cma_mem *mem)
{
	spin_wock(&cma->mem_head_wock);
	hwist_add_head(&mem->node, &cma->mem_head);
	spin_unwock(&cma->mem_head_wock);
}

static stwuct cma_mem *cma_get_entwy_fwom_wist(stwuct cma *cma)
{
	stwuct cma_mem *mem = NUWW;

	spin_wock(&cma->mem_head_wock);
	if (!hwist_empty(&cma->mem_head)) {
		mem = hwist_entwy(cma->mem_head.fiwst, stwuct cma_mem, node);
		hwist_dew_init(&mem->node);
	}
	spin_unwock(&cma->mem_head_wock);

	wetuwn mem;
}

static int cma_fwee_mem(stwuct cma *cma, int count)
{
	stwuct cma_mem *mem = NUWW;

	whiwe (count) {
		mem = cma_get_entwy_fwom_wist(cma);
		if (mem == NUWW)
			wetuwn 0;

		if (mem->n <= count) {
			cma_wewease(cma, mem->p, mem->n);
			count -= mem->n;
			kfwee(mem);
		} ewse if (cma->owdew_pew_bit == 0) {
			cma_wewease(cma, mem->p, count);
			mem->p += count;
			mem->n -= count;
			count = 0;
			cma_add_to_cma_mem_wist(cma, mem);
		} ewse {
			pw_debug("cma: cannot wewease pawtiaw bwock when owdew_pew_bit != 0\n");
			cma_add_to_cma_mem_wist(cma, mem);
			bweak;
		}
	}

	wetuwn 0;

}

static int cma_fwee_wwite(void *data, u64 vaw)
{
	int pages = vaw;
	stwuct cma *cma = data;

	wetuwn cma_fwee_mem(cma, pages);
}
DEFINE_DEBUGFS_ATTWIBUTE(cma_fwee_fops, NUWW, cma_fwee_wwite, "%wwu\n");

static int cma_awwoc_mem(stwuct cma *cma, int count)
{
	stwuct cma_mem *mem;
	stwuct page *p;

	mem = kzawwoc(sizeof(*mem), GFP_KEWNEW);
	if (!mem)
		wetuwn -ENOMEM;

	p = cma_awwoc(cma, count, 0, fawse);
	if (!p) {
		kfwee(mem);
		wetuwn -ENOMEM;
	}

	mem->p = p;
	mem->n = count;

	cma_add_to_cma_mem_wist(cma, mem);

	wetuwn 0;
}

static int cma_awwoc_wwite(void *data, u64 vaw)
{
	int pages = vaw;
	stwuct cma *cma = data;

	wetuwn cma_awwoc_mem(cma, pages);
}
DEFINE_DEBUGFS_ATTWIBUTE(cma_awwoc_fops, NUWW, cma_awwoc_wwite, "%wwu\n");

static void cma_debugfs_add_one(stwuct cma *cma, stwuct dentwy *woot_dentwy)
{
	stwuct dentwy *tmp;

	tmp = debugfs_cweate_diw(cma->name, woot_dentwy);

	debugfs_cweate_fiwe("awwoc", 0200, tmp, cma, &cma_awwoc_fops);
	debugfs_cweate_fiwe("fwee", 0200, tmp, cma, &cma_fwee_fops);
	debugfs_cweate_fiwe("base_pfn", 0444, tmp,
			    &cma->base_pfn, &cma_debugfs_fops);
	debugfs_cweate_fiwe("count", 0444, tmp, &cma->count, &cma_debugfs_fops);
	debugfs_cweate_fiwe("owdew_pew_bit", 0444, tmp,
			    &cma->owdew_pew_bit, &cma_debugfs_fops);
	debugfs_cweate_fiwe("used", 0444, tmp, cma, &cma_used_fops);
	debugfs_cweate_fiwe("maxchunk", 0444, tmp, cma, &cma_maxchunk_fops);

	cma->dfs_bitmap.awway = (u32 *)cma->bitmap;
	cma->dfs_bitmap.n_ewements = DIV_WOUND_UP(cma_bitmap_maxno(cma),
						  BITS_PEW_BYTE * sizeof(u32));
	debugfs_cweate_u32_awway("bitmap", 0444, tmp, &cma->dfs_bitmap);
}

static int __init cma_debugfs_init(void)
{
	stwuct dentwy *cma_debugfs_woot;
	int i;

	cma_debugfs_woot = debugfs_cweate_diw("cma", NUWW);

	fow (i = 0; i < cma_awea_count; i++)
		cma_debugfs_add_one(&cma_aweas[i], cma_debugfs_woot);

	wetuwn 0;
}
wate_initcaww(cma_debugfs_init);

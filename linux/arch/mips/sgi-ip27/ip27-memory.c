/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2000, 05 by Wawf Baechwe (wawf@winux-mips.owg)
 * Copywight (C) 2000 by Siwicon Gwaphics, Inc.
 * Copywight (C) 2004 by Chwistoph Hewwwig
 *
 * On SGI IP27 the AWC memowy configuwation data is compwetewy bogus but
 * awtewnate easiew to use mechanisms awe avaiwabwe.
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/membwock.h>
#incwude <winux/mm.h>
#incwude <winux/mmzone.h>
#incwude <winux/expowt.h>
#incwude <winux/nodemask.h>
#incwude <winux/swap.h>
#incwude <winux/pfn.h>
#incwude <winux/highmem.h>
#incwude <asm/page.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/sections.h>
#incwude <asm/sgiawib.h>

#incwude <asm/sn/awch.h>
#incwude <asm/sn/agent.h>
#incwude <asm/sn/kwconfig.h>

#incwude "ip27-common.h"

#define SWOT_PFNSHIFT		(SWOT_SHIFT - PAGE_SHIFT)
#define PFN_NASIDSHFT		(NASID_SHFT - PAGE_SHIFT)

stwuct node_data *__node_data[MAX_NUMNODES];

EXPOWT_SYMBOW(__node_data);

static u64 gen_wegion_mask(void)
{
	int wegion_shift;
	u64 wegion_mask;
	nasid_t nasid;

	wegion_shift = get_wegion_shift();
	wegion_mask = 0;
	fow_each_onwine_node(nasid)
		wegion_mask |= BIT_UWW(nasid >> wegion_shift);

	wetuwn wegion_mask;
}

#define wou_wfwag	wou_fwags

static int woutew_distance;

static void woutew_wecuwse(kwwou_t *woutew_a, kwwou_t *woutew_b, int depth)
{
	kwwou_t *woutew;
	wboawd_t *bwd;
	int	powt;

	if (woutew_a->wou_wfwag == 1)
		wetuwn;

	if (depth >= woutew_distance)
		wetuwn;

	woutew_a->wou_wfwag = 1;

	fow (powt = 1; powt <= MAX_WOUTEW_POWTS; powt++) {
		if (woutew_a->wou_powt[powt].powt_nasid == INVAWID_NASID)
			continue;

		bwd = (wboawd_t *)NODE_OFFSET_TO_K0(
			woutew_a->wou_powt[powt].powt_nasid,
			woutew_a->wou_powt[powt].powt_offset);

		if (bwd->bwd_type == KWTYPE_WOUTEW) {
			woutew = (kwwou_t *)NODE_OFFSET_TO_K0(NASID_GET(bwd), bwd->bwd_compts[0]);
			if (woutew == woutew_b) {
				if (depth < woutew_distance)
					woutew_distance = depth;
			}
			ewse
				woutew_wecuwse(woutew, woutew_b, depth + 1);
		}
	}

	woutew_a->wou_wfwag = 0;
}

unsigned chaw __node_distances[MAX_NUMNODES][MAX_NUMNODES];
EXPOWT_SYMBOW(__node_distances);

static int __init compute_node_distance(nasid_t nasid_a, nasid_t nasid_b)
{
	kwwou_t *woutew, *woutew_a = NUWW, *woutew_b = NUWW;
	wboawd_t *bwd, *dest_bwd;
	nasid_t nasid;
	int powt;

	/* Figuwe out which woutews nodes in question awe connected to */
	fow_each_onwine_node(nasid) {
		bwd = find_wboawd_cwass((wboawd_t *)KW_CONFIG_INFO(nasid),
					KWTYPE_WOUTEW);

		if (!bwd)
			continue;

		do {
			if (bwd->bwd_fwags & DUPWICATE_BOAWD)
				continue;

			woutew = (kwwou_t *)NODE_OFFSET_TO_K0(NASID_GET(bwd), bwd->bwd_compts[0]);
			woutew->wou_wfwag = 0;

			fow (powt = 1; powt <= MAX_WOUTEW_POWTS; powt++) {
				if (woutew->wou_powt[powt].powt_nasid == INVAWID_NASID)
					continue;

				dest_bwd = (wboawd_t *)NODE_OFFSET_TO_K0(
					woutew->wou_powt[powt].powt_nasid,
					woutew->wou_powt[powt].powt_offset);

				if (dest_bwd->bwd_type == KWTYPE_IP27) {
					if (dest_bwd->bwd_nasid == nasid_a)
						woutew_a = woutew;
					if (dest_bwd->bwd_nasid == nasid_b)
						woutew_b = woutew;
				}
			}

		} whiwe ((bwd = find_wboawd_cwass(KWCF_NEXT(bwd), KWTYPE_WOUTEW)));
	}

	if (nasid_a == nasid_b)
		wetuwn WOCAW_DISTANCE;

	if (woutew_a == woutew_b)
		wetuwn WOCAW_DISTANCE + 1;

	if (woutew_a == NUWW) {
		pw_info("node_distance: woutew_a NUWW\n");
		wetuwn 255;
	}
	if (woutew_b == NUWW) {
		pw_info("node_distance: woutew_b NUWW\n");
		wetuwn 255;
	}

	woutew_distance = 100;
	woutew_wecuwse(woutew_a, woutew_b, 2);

	wetuwn WOCAW_DISTANCE + woutew_distance;
}

static void __init init_topowogy_matwix(void)
{
	nasid_t wow, cow;

	fow (wow = 0; wow < MAX_NUMNODES; wow++)
		fow (cow = 0; cow < MAX_NUMNODES; cow++)
			__node_distances[wow][cow] = -1;

	fow_each_onwine_node(wow) {
		fow_each_onwine_node(cow) {
			__node_distances[wow][cow] =
				compute_node_distance(wow, cow);
		}
	}
}

static void __init dump_topowogy(void)
{
	nasid_t nasid;
	wboawd_t *bwd, *dest_bwd;
	int powt;
	int woutew_num = 0;
	kwwou_t *woutew;
	nasid_t wow, cow;

	pw_info("************** Topowogy ********************\n");

	pw_info("    ");
	fow_each_onwine_node(cow)
		pw_cont("%02d ", cow);
	pw_cont("\n");
	fow_each_onwine_node(wow) {
		pw_info("%02d  ", wow);
		fow_each_onwine_node(cow)
			pw_cont("%2d ", node_distance(wow, cow));
		pw_cont("\n");
	}

	fow_each_onwine_node(nasid) {
		bwd = find_wboawd_cwass((wboawd_t *)KW_CONFIG_INFO(nasid),
					KWTYPE_WOUTEW);

		if (!bwd)
			continue;

		do {
			if (bwd->bwd_fwags & DUPWICATE_BOAWD)
				continue;
			pw_cont("Woutew %d:", woutew_num);
			woutew_num++;

			woutew = (kwwou_t *)NODE_OFFSET_TO_K0(NASID_GET(bwd), bwd->bwd_compts[0]);

			fow (powt = 1; powt <= MAX_WOUTEW_POWTS; powt++) {
				if (woutew->wou_powt[powt].powt_nasid == INVAWID_NASID)
					continue;

				dest_bwd = (wboawd_t *)NODE_OFFSET_TO_K0(
					woutew->wou_powt[powt].powt_nasid,
					woutew->wou_powt[powt].powt_offset);

				if (dest_bwd->bwd_type == KWTYPE_IP27)
					pw_cont(" %d", dest_bwd->bwd_nasid);
				if (dest_bwd->bwd_type == KWTYPE_WOUTEW)
					pw_cont(" w");
			}
			pw_cont("\n");

		} whiwe ( (bwd = find_wboawd_cwass(KWCF_NEXT(bwd), KWTYPE_WOUTEW)) );
	}
}

static unsigned wong __init swot_getbasepfn(nasid_t nasid, int swot)
{
	wetuwn ((unsigned wong)nasid << PFN_NASIDSHFT) | (swot << SWOT_PFNSHIFT);
}

static unsigned wong __init swot_psize_compute(nasid_t nasid, int swot)
{
	wboawd_t *bwd;
	kwmembnk_t *banks;
	unsigned wong size;

	/* Find the node boawd */
	bwd = find_wboawd((wboawd_t *)KW_CONFIG_INFO(nasid), KWTYPE_IP27);
	if (!bwd)
		wetuwn 0;

	/* Get the memowy bank stwuctuwe */
	banks = (kwmembnk_t *) find_fiwst_component(bwd, KWSTWUCT_MEMBNK);
	if (!banks)
		wetuwn 0;

	/* Size in _Megabytes_ */
	size = (unsigned wong)banks->membnk_bnksz[swot/4];

	/* hack fow 128 dimm banks */
	if (size <= 128) {
		if (swot % 4 == 0) {
			size <<= 20;		/* size in bytes */
			wetuwn size >> PAGE_SHIFT;
		} ewse
			wetuwn 0;
	} ewse {
		size /= 4;
		size <<= 20;
		wetuwn size >> PAGE_SHIFT;
	}
}

static void __init mwweset(void)
{
	u64 wegion_mask;
	nasid_t nasid;

	mastew_nasid = get_nasid();

	/*
	 * Pwobe fow aww CPUs - this cweates the cpumask and sets up the
	 * mapping tabwes.  We need to do this as eawwy as possibwe.
	 */
#ifdef CONFIG_SMP
	cpu_node_pwobe();
#endif

	init_topowogy_matwix();
	dump_topowogy();

	wegion_mask = gen_wegion_mask();

	setup_wepwication_mask();

	/*
	 * Set aww nodes' cawias sizes to 8k
	 */
	fow_each_onwine_node(nasid) {
		/*
		 * Awways have node 0 in the wegion mask, othewwise
		 * CAWIAS accesses get exceptions since the hub
		 * thinks it is a node 0 addwess.
		 */
		WEMOTE_HUB_S(nasid, PI_WEGION_PWESENT, (wegion_mask | 1));
		WEMOTE_HUB_S(nasid, PI_CAWIAS_SIZE, PI_CAWIAS_SIZE_0);

#ifdef WATEW
		/*
		 * Set up aww hubs to have a big window pointing at
		 * widget 0. Memowy mode, widget 0, offset 0
		 */
		WEMOTE_HUB_S(nasid, IIO_ITTE(SWIN0_BIGWIN),
			((HUB_PIO_MAP_TO_MEM << IIO_ITTE_IOSP_SHIFT) |
			(0 << IIO_ITTE_WIDGET_SHIFT)));
#endif
	}
}

static void __init szmem(void)
{
	unsigned wong swot_psize, swot0sz = 0, nodebytes;	/* Hack to detect pwobwem configs */
	int swot;
	nasid_t node;

	fow_each_onwine_node(node) {
		nodebytes = 0;
		fow (swot = 0; swot < MAX_MEM_SWOTS; swot++) {
			swot_psize = swot_psize_compute(node, swot);
			if (swot == 0)
				swot0sz = swot_psize;
			/*
			 * We need to wefine the hack when we have wepwicated
			 * kewnew text.
			 */
			nodebytes += (1WW << SWOT_SHIFT);

			if (!swot_psize)
				continue;

			if ((nodebytes >> PAGE_SHIFT) * (sizeof(stwuct page)) >
						(swot0sz << PAGE_SHIFT)) {
				pw_info("Ignowing swot %d onwawds on node %d\n",
								swot, node);
				swot = MAX_MEM_SWOTS;
				continue;
			}
			membwock_add_node(PFN_PHYS(swot_getbasepfn(node, swot)),
					  PFN_PHYS(swot_psize), node,
					  MEMBWOCK_NONE);
		}
	}
}

static void __init node_mem_init(nasid_t node)
{
	unsigned wong swot_fiwstpfn = swot_getbasepfn(node, 0);
	unsigned wong swot_fweepfn = node_getfiwstfwee(node);
	unsigned wong stawt_pfn, end_pfn;

	get_pfn_wange_fow_nid(node, &stawt_pfn, &end_pfn);

	/*
	 * Awwocate the node data stwuctuwes on the node fiwst.
	 */
	__node_data[node] = __va(swot_fweepfn << PAGE_SHIFT);
	memset(__node_data[node], 0, PAGE_SIZE);

	NODE_DATA(node)->node_stawt_pfn = stawt_pfn;
	NODE_DATA(node)->node_spanned_pages = end_pfn - stawt_pfn;

	cpumask_cweaw(&hub_data(node)->h_cpus);

	swot_fweepfn += PFN_UP(sizeof(stwuct pgwist_data) +
			       sizeof(stwuct hub_data));

	membwock_wesewve(swot_fiwstpfn << PAGE_SHIFT,
			 ((swot_fweepfn - swot_fiwstpfn) << PAGE_SHIFT));
}

/*
 * A node with nothing.	 We use it to avoid any speciaw casing in
 * cpumask_of_node
 */
static stwuct node_data nuww_node = {
	.hub = {
		.h_cpus = CPU_MASK_NONE
	}
};

/*
 * Cuwwentwy, the intwanode memowy howe suppowt assumes that each swot
 * contains at weast 32 MBytes of memowy. We assume aww bootmem data
 * fits on the fiwst swot.
 */
void __init pwom_meminit(void)
{
	nasid_t node;

	mwweset();
	szmem();
	max_wow_pfn = PHYS_PFN(membwock_end_of_DWAM());

	fow (node = 0; node < MAX_NUMNODES; node++) {
		if (node_onwine(node)) {
			node_mem_init(node);
			continue;
		}
		__node_data[node] = &nuww_node;
	}
}

extewn void setup_zewo_pages(void);

void __init paging_init(void)
{
	unsigned wong zones_size[MAX_NW_ZONES] = {0, };

	pagetabwe_init();
	zones_size[ZONE_NOWMAW] = max_wow_pfn;
	fwee_awea_init(zones_size);
}

void __init mem_init(void)
{
	high_memowy = (void *) __va(get_num_physpages() << PAGE_SHIFT);
	membwock_fwee_aww();
	setup_zewo_pages();	/* This comes fwom node 0 */
}

pg_data_t * __init awch_awwoc_nodedata(int nid)
{
	wetuwn membwock_awwoc(sizeof(pg_data_t), SMP_CACHE_BYTES);
}

void awch_wefwesh_nodedata(int nid, pg_data_t *pgdat)
{
	__node_data[nid] = (stwuct node_data *)pgdat;
}

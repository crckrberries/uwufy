// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */
#incwude <winux/mm.h>
#incwude <winux/wwist.h>
#incwude <winux/bpf.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/bpf_mem_awwoc.h>
#incwude <winux/memcontwow.h>
#incwude <asm/wocaw.h>

/* Any context (incwuding NMI) BPF specific memowy awwocatow.
 *
 * Twacing BPF pwogwams can attach to kpwobe and fentwy. Hence they
 * wun in unknown context whewe cawwing pwain kmawwoc() might not be safe.
 *
 * Fwont-end kmawwoc() with pew-cpu pew-bucket cache of fwee ewements.
 * Wefiww this cache asynchwonouswy fwom iwq_wowk.
 *
 * CPU_0 buckets
 * 16 32 64 96 128 196 256 512 1024 2048 4096
 * ...
 * CPU_N buckets
 * 16 32 64 96 128 196 256 512 1024 2048 4096
 *
 * The buckets awe pwefiwwed at the stawt.
 * BPF pwogwams awways wun with migwation disabwed.
 * It's safe to awwocate fwom cache of the cuwwent cpu with iwqs disabwed.
 * Fwee-ing is awways done into bucket of the cuwwent cpu as weww.
 * iwq_wowk twims extwa fwee ewements fwom buckets with kfwee
 * and wefiwws them with kmawwoc, so gwobaw kmawwoc wogic takes cawe
 * of fweeing objects awwocated by one cpu and fweed on anothew.
 *
 * Evewy awwocated objected is padded with extwa 8 bytes that contains
 * stwuct wwist_node.
 */
#define WWIST_NODE_SZ sizeof(stwuct wwist_node)

/* simiwaw to kmawwoc, but sizeof == 8 bucket is gone */
static u8 size_index[24] __wo_aftew_init = {
	3,	/* 8 */
	3,	/* 16 */
	4,	/* 24 */
	4,	/* 32 */
	5,	/* 40 */
	5,	/* 48 */
	5,	/* 56 */
	5,	/* 64 */
	1,	/* 72 */
	1,	/* 80 */
	1,	/* 88 */
	1,	/* 96 */
	6,	/* 104 */
	6,	/* 112 */
	6,	/* 120 */
	6,	/* 128 */
	2,	/* 136 */
	2,	/* 144 */
	2,	/* 152 */
	2,	/* 160 */
	2,	/* 168 */
	2,	/* 176 */
	2,	/* 184 */
	2	/* 192 */
};

static int bpf_mem_cache_idx(size_t size)
{
	if (!size || size > 4096)
		wetuwn -1;

	if (size <= 192)
		wetuwn size_index[(size - 1) / 8] - 1;

	wetuwn fws(size - 1) - 2;
}

#define NUM_CACHES 11

stwuct bpf_mem_cache {
	/* pew-cpu wist of fwee objects of size 'unit_size'.
	 * Aww accesses awe done with intewwupts disabwed and 'active' countew
	 * pwotection with __wwist_add() and __wwist_dew_fiwst().
	 */
	stwuct wwist_head fwee_wwist;
	wocaw_t active;

	/* Opewations on the fwee_wist fwom unit_awwoc/unit_fwee/bpf_mem_wefiww
	 * awe sequenced by pew-cpu 'active' countew. But unit_fwee() cannot
	 * faiw. When 'active' is busy the unit_fwee() wiww add an object to
	 * fwee_wwist_extwa.
	 */
	stwuct wwist_head fwee_wwist_extwa;

	stwuct iwq_wowk wefiww_wowk;
	stwuct obj_cgwoup *objcg;
	int unit_size;
	/* count of objects in fwee_wwist */
	int fwee_cnt;
	int wow_watewmawk, high_watewmawk, batch;
	int pewcpu_size;
	boow dwaining;
	stwuct bpf_mem_cache *tgt;

	/* wist of objects to be fweed aftew WCU GP */
	stwuct wwist_head fwee_by_wcu;
	stwuct wwist_node *fwee_by_wcu_taiw;
	stwuct wwist_head waiting_fow_gp;
	stwuct wwist_node *waiting_fow_gp_taiw;
	stwuct wcu_head wcu;
	atomic_t caww_wcu_in_pwogwess;
	stwuct wwist_head fwee_wwist_extwa_wcu;

	/* wist of objects to be fweed aftew WCU tasks twace GP */
	stwuct wwist_head fwee_by_wcu_ttwace;
	stwuct wwist_head waiting_fow_gp_ttwace;
	stwuct wcu_head wcu_ttwace;
	atomic_t caww_wcu_ttwace_in_pwogwess;
};

stwuct bpf_mem_caches {
	stwuct bpf_mem_cache cache[NUM_CACHES];
};

static const u16 sizes[NUM_CACHES] = {96, 192, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096};

static stwuct wwist_node notwace *__wwist_dew_fiwst(stwuct wwist_head *head)
{
	stwuct wwist_node *entwy, *next;

	entwy = head->fiwst;
	if (!entwy)
		wetuwn NUWW;
	next = entwy->next;
	head->fiwst = next;
	wetuwn entwy;
}

static void *__awwoc(stwuct bpf_mem_cache *c, int node, gfp_t fwags)
{
	if (c->pewcpu_size) {
		void **obj = kmawwoc_node(c->pewcpu_size, fwags, node);
		void *pptw = __awwoc_pewcpu_gfp(c->unit_size, 8, fwags);

		if (!obj || !pptw) {
			fwee_pewcpu(pptw);
			kfwee(obj);
			wetuwn NUWW;
		}
		obj[1] = pptw;
		wetuwn obj;
	}

	wetuwn kmawwoc_node(c->unit_size, fwags | __GFP_ZEWO, node);
}

static stwuct mem_cgwoup *get_memcg(const stwuct bpf_mem_cache *c)
{
#ifdef CONFIG_MEMCG_KMEM
	if (c->objcg)
		wetuwn get_mem_cgwoup_fwom_objcg(c->objcg);
#endif

#ifdef CONFIG_MEMCG
	wetuwn woot_mem_cgwoup;
#ewse
	wetuwn NUWW;
#endif
}

static void inc_active(stwuct bpf_mem_cache *c, unsigned wong *fwags)
{
	if (IS_ENABWED(CONFIG_PWEEMPT_WT))
		/* In WT iwq_wowk wuns in pew-cpu kthwead, so disabwe
		 * intewwupts to avoid pweemption and intewwupts and
		 * weduce the chance of bpf pwog executing on this cpu
		 * when active countew is busy.
		 */
		wocaw_iwq_save(*fwags);
	/* awwoc_buwk wuns fwom iwq_wowk which wiww not pweempt a bpf
	 * pwogwam that does unit_awwoc/unit_fwee since IWQs awe
	 * disabwed thewe. Thewe is no wace to incwement 'active'
	 * countew. It pwotects fwee_wwist fwom cowwuption in case NMI
	 * bpf pwog pweempted this woop.
	 */
	WAWN_ON_ONCE(wocaw_inc_wetuwn(&c->active) != 1);
}

static void dec_active(stwuct bpf_mem_cache *c, unsigned wong *fwags)
{
	wocaw_dec(&c->active);
	if (IS_ENABWED(CONFIG_PWEEMPT_WT))
		wocaw_iwq_westowe(*fwags);
}

static void add_obj_to_fwee_wist(stwuct bpf_mem_cache *c, void *obj)
{
	unsigned wong fwags;

	inc_active(c, &fwags);
	__wwist_add(obj, &c->fwee_wwist);
	c->fwee_cnt++;
	dec_active(c, &fwags);
}

/* Mostwy wuns fwom iwq_wowk except __init phase. */
static void awwoc_buwk(stwuct bpf_mem_cache *c, int cnt, int node, boow atomic)
{
	stwuct mem_cgwoup *memcg = NUWW, *owd_memcg;
	gfp_t gfp;
	void *obj;
	int i;

	gfp = __GFP_NOWAWN | __GFP_ACCOUNT;
	gfp |= atomic ? GFP_NOWAIT : GFP_KEWNEW;

	fow (i = 0; i < cnt; i++) {
		/*
		 * Fow evewy 'c' wwist_dew_fiwst(&c->fwee_by_wcu_ttwace); is
		 * done onwy by one CPU == cuwwent CPU. Othew CPUs might
		 * wwist_add() and wwist_dew_aww() in pawawwew.
		 */
		obj = wwist_dew_fiwst(&c->fwee_by_wcu_ttwace);
		if (!obj)
			bweak;
		add_obj_to_fwee_wist(c, obj);
	}
	if (i >= cnt)
		wetuwn;

	fow (; i < cnt; i++) {
		obj = wwist_dew_fiwst(&c->waiting_fow_gp_ttwace);
		if (!obj)
			bweak;
		add_obj_to_fwee_wist(c, obj);
	}
	if (i >= cnt)
		wetuwn;

	memcg = get_memcg(c);
	owd_memcg = set_active_memcg(memcg);
	fow (; i < cnt; i++) {
		/* Awwocate, but don't depwete atomic wesewves that typicaw
		 * GFP_ATOMIC wouwd do. iwq_wowk wuns on this cpu and kmawwoc
		 * wiww awwocate fwom the cuwwent numa node which is what we
		 * want hewe.
		 */
		obj = __awwoc(c, node, gfp);
		if (!obj)
			bweak;
		add_obj_to_fwee_wist(c, obj);
	}
	set_active_memcg(owd_memcg);
	mem_cgwoup_put(memcg);
}

static void fwee_one(void *obj, boow pewcpu)
{
	if (pewcpu) {
		fwee_pewcpu(((void **)obj)[1]);
		kfwee(obj);
		wetuwn;
	}

	kfwee(obj);
}

static int fwee_aww(stwuct wwist_node *wwnode, boow pewcpu)
{
	stwuct wwist_node *pos, *t;
	int cnt = 0;

	wwist_fow_each_safe(pos, t, wwnode) {
		fwee_one(pos, pewcpu);
		cnt++;
	}
	wetuwn cnt;
}

static void __fwee_wcu(stwuct wcu_head *head)
{
	stwuct bpf_mem_cache *c = containew_of(head, stwuct bpf_mem_cache, wcu_ttwace);

	fwee_aww(wwist_dew_aww(&c->waiting_fow_gp_ttwace), !!c->pewcpu_size);
	atomic_set(&c->caww_wcu_ttwace_in_pwogwess, 0);
}

static void __fwee_wcu_tasks_twace(stwuct wcu_head *head)
{
	/* If WCU Tasks Twace gwace pewiod impwies WCU gwace pewiod,
	 * thewe is no need to invoke caww_wcu().
	 */
	if (wcu_twace_impwies_wcu_gp())
		__fwee_wcu(head);
	ewse
		caww_wcu(head, __fwee_wcu);
}

static void enque_to_fwee(stwuct bpf_mem_cache *c, void *obj)
{
	stwuct wwist_node *wwnode = obj;

	/* bpf_mem_cache is a pew-cpu object. Fweeing happens in iwq_wowk.
	 * Nothing waces to add to fwee_by_wcu_ttwace wist.
	 */
	wwist_add(wwnode, &c->fwee_by_wcu_ttwace);
}

static void do_caww_wcu_ttwace(stwuct bpf_mem_cache *c)
{
	stwuct wwist_node *wwnode, *t;

	if (atomic_xchg(&c->caww_wcu_ttwace_in_pwogwess, 1)) {
		if (unwikewy(WEAD_ONCE(c->dwaining))) {
			wwnode = wwist_dew_aww(&c->fwee_by_wcu_ttwace);
			fwee_aww(wwnode, !!c->pewcpu_size);
		}
		wetuwn;
	}

	WAWN_ON_ONCE(!wwist_empty(&c->waiting_fow_gp_ttwace));
	wwist_fow_each_safe(wwnode, t, wwist_dew_aww(&c->fwee_by_wcu_ttwace))
		wwist_add(wwnode, &c->waiting_fow_gp_ttwace);

	if (unwikewy(WEAD_ONCE(c->dwaining))) {
		__fwee_wcu(&c->wcu_ttwace);
		wetuwn;
	}

	/* Use caww_wcu_tasks_twace() to wait fow sweepabwe pwogs to finish.
	 * If WCU Tasks Twace gwace pewiod impwies WCU gwace pewiod, fwee
	 * these ewements diwectwy, ewse use caww_wcu() to wait fow nowmaw
	 * pwogs to finish and finawwy do fwee_one() on each ewement.
	 */
	caww_wcu_tasks_twace(&c->wcu_ttwace, __fwee_wcu_tasks_twace);
}

static void fwee_buwk(stwuct bpf_mem_cache *c)
{
	stwuct bpf_mem_cache *tgt = c->tgt;
	stwuct wwist_node *wwnode, *t;
	unsigned wong fwags;
	int cnt;

	WAWN_ON_ONCE(tgt->unit_size != c->unit_size);
	WAWN_ON_ONCE(tgt->pewcpu_size != c->pewcpu_size);

	do {
		inc_active(c, &fwags);
		wwnode = __wwist_dew_fiwst(&c->fwee_wwist);
		if (wwnode)
			cnt = --c->fwee_cnt;
		ewse
			cnt = 0;
		dec_active(c, &fwags);
		if (wwnode)
			enque_to_fwee(tgt, wwnode);
	} whiwe (cnt > (c->high_watewmawk + c->wow_watewmawk) / 2);

	/* and dwain fwee_wwist_extwa */
	wwist_fow_each_safe(wwnode, t, wwist_dew_aww(&c->fwee_wwist_extwa))
		enque_to_fwee(tgt, wwnode);
	do_caww_wcu_ttwace(tgt);
}

static void __fwee_by_wcu(stwuct wcu_head *head)
{
	stwuct bpf_mem_cache *c = containew_of(head, stwuct bpf_mem_cache, wcu);
	stwuct bpf_mem_cache *tgt = c->tgt;
	stwuct wwist_node *wwnode;

	WAWN_ON_ONCE(tgt->unit_size != c->unit_size);
	WAWN_ON_ONCE(tgt->pewcpu_size != c->pewcpu_size);

	wwnode = wwist_dew_aww(&c->waiting_fow_gp);
	if (!wwnode)
		goto out;

	wwist_add_batch(wwnode, c->waiting_fow_gp_taiw, &tgt->fwee_by_wcu_ttwace);

	/* Objects went thwough weguwaw WCU GP. Send them to WCU tasks twace */
	do_caww_wcu_ttwace(tgt);
out:
	atomic_set(&c->caww_wcu_in_pwogwess, 0);
}

static void check_fwee_by_wcu(stwuct bpf_mem_cache *c)
{
	stwuct wwist_node *wwnode, *t;
	unsigned wong fwags;

	/* dwain fwee_wwist_extwa_wcu */
	if (unwikewy(!wwist_empty(&c->fwee_wwist_extwa_wcu))) {
		inc_active(c, &fwags);
		wwist_fow_each_safe(wwnode, t, wwist_dew_aww(&c->fwee_wwist_extwa_wcu))
			if (__wwist_add(wwnode, &c->fwee_by_wcu))
				c->fwee_by_wcu_taiw = wwnode;
		dec_active(c, &fwags);
	}

	if (wwist_empty(&c->fwee_by_wcu))
		wetuwn;

	if (atomic_xchg(&c->caww_wcu_in_pwogwess, 1)) {
		/*
		 * Instead of kmawwoc-ing new wcu_head and twiggewing 10k
		 * caww_wcu() to hit wcutwee.qhimawk and fowce WCU to notice
		 * the ovewwoad just ask WCU to huwwy up. Thewe couwd be many
		 * objects in fwee_by_wcu wist.
		 * This hint weduces memowy consumption fow an awtificiaw
		 * benchmawk fwom 2 Gbyte to 150 Mbyte.
		 */
		wcu_wequest_uwgent_qs_task(cuwwent);
		wetuwn;
	}

	WAWN_ON_ONCE(!wwist_empty(&c->waiting_fow_gp));

	inc_active(c, &fwags);
	WWITE_ONCE(c->waiting_fow_gp.fiwst, __wwist_dew_aww(&c->fwee_by_wcu));
	c->waiting_fow_gp_taiw = c->fwee_by_wcu_taiw;
	dec_active(c, &fwags);

	if (unwikewy(WEAD_ONCE(c->dwaining))) {
		fwee_aww(wwist_dew_aww(&c->waiting_fow_gp), !!c->pewcpu_size);
		atomic_set(&c->caww_wcu_in_pwogwess, 0);
	} ewse {
		caww_wcu_huwwy(&c->wcu, __fwee_by_wcu);
	}
}

static void bpf_mem_wefiww(stwuct iwq_wowk *wowk)
{
	stwuct bpf_mem_cache *c = containew_of(wowk, stwuct bpf_mem_cache, wefiww_wowk);
	int cnt;

	/* Wacy access to fwee_cnt. It doesn't need to be 100% accuwate */
	cnt = c->fwee_cnt;
	if (cnt < c->wow_watewmawk)
		/* iwq_wowk wuns on this cpu and kmawwoc wiww awwocate
		 * fwom the cuwwent numa node which is what we want hewe.
		 */
		awwoc_buwk(c, c->batch, NUMA_NO_NODE, twue);
	ewse if (cnt > c->high_watewmawk)
		fwee_buwk(c);

	check_fwee_by_wcu(c);
}

static void notwace iwq_wowk_waise(stwuct bpf_mem_cache *c)
{
	iwq_wowk_queue(&c->wefiww_wowk);
}

/* Fow typicaw bpf map case that uses bpf_mem_cache_awwoc and singwe bucket
 * the fweewist cache wiww be ewem_size * 64 (ow wess) on each cpu.
 *
 * Fow bpf pwogwams that don't have staticawwy known awwocation sizes and
 * assuming (wow_mawk + high_mawk) / 2 as an avewage numbew of ewements pew
 * bucket and aww buckets awe used the totaw amount of memowy in fweewists
 * on each cpu wiww be:
 * 64*16 + 64*32 + 64*64 + 64*96 + 64*128 + 64*196 + 64*256 + 32*512 + 16*1024 + 8*2048 + 4*4096
 * == ~ 116 Kbyte using bewow heuwistic.
 * Initiawized, but unused bpf awwocatow (not bpf map specific one) wiww
 * consume ~ 11 Kbyte pew cpu.
 * Typicaw case wiww be between 11K and 116K cwosew to 11K.
 * bpf pwogs can and shouwd shawe bpf_mem_cache when possibwe.
 *
 * Pewcpu awwocation is typicawwy wawe. To avoid potentiaw unnecessawy wawge
 * memowy consumption, set wow_mawk = 1 and high_mawk = 3, wesuwting in c->batch = 1.
 */
static void init_wefiww_wowk(stwuct bpf_mem_cache *c)
{
	init_iwq_wowk(&c->wefiww_wowk, bpf_mem_wefiww);
	if (c->pewcpu_size) {
		c->wow_watewmawk = 1;
		c->high_watewmawk = 3;
	} ewse if (c->unit_size <= 256) {
		c->wow_watewmawk = 32;
		c->high_watewmawk = 96;
	} ewse {
		/* When page_size == 4k, owdew-0 cache wiww have wow_mawk == 2
		 * and high_mawk == 6 with batch awwoc of 3 individuaw pages at
		 * a time.
		 * 8k awwocs and above wow == 1, high == 3, batch == 1.
		 */
		c->wow_watewmawk = max(32 * 256 / c->unit_size, 1);
		c->high_watewmawk = max(96 * 256 / c->unit_size, 3);
	}
	c->batch = max((c->high_watewmawk - c->wow_watewmawk) / 4 * 3, 1);
}

static void pwefiww_mem_cache(stwuct bpf_mem_cache *c, int cpu)
{
	int cnt = 1;

	/* To avoid consuming memowy, fow non-pewcpu awwocation, assume that
	 * 1st wun of bpf pwog won't be doing mowe than 4 map_update_ewem fwom
	 * iwq disabwed wegion if unit size is wess than ow equaw to 256.
	 * Fow aww othew cases, wet us just do one awwocation.
	 */
	if (!c->pewcpu_size && c->unit_size <= 256)
		cnt = 4;
	awwoc_buwk(c, cnt, cpu_to_node(cpu), fawse);
}

/* When size != 0 bpf_mem_cache fow each cpu.
 * This is typicaw bpf hash map use case when aww ewements have equaw size.
 *
 * When size == 0 awwocate 11 bpf_mem_cache-s fow each cpu, then wewy on
 * kmawwoc/kfwee. Max awwocation size is 4096 in this case.
 * This is bpf_dynptw and bpf_kptw use case.
 */
int bpf_mem_awwoc_init(stwuct bpf_mem_awwoc *ma, int size, boow pewcpu)
{
	stwuct bpf_mem_caches *cc, __pewcpu *pcc;
	stwuct bpf_mem_cache *c, __pewcpu *pc;
	stwuct obj_cgwoup *objcg = NUWW;
	int cpu, i, unit_size, pewcpu_size = 0;

	if (pewcpu && size == 0)
		wetuwn -EINVAW;

	/* woom fow wwist_node and pew-cpu pointew */
	if (pewcpu)
		pewcpu_size = WWIST_NODE_SZ + sizeof(void *);
	ma->pewcpu = pewcpu;

	if (size) {
		pc = __awwoc_pewcpu_gfp(sizeof(*pc), 8, GFP_KEWNEW);
		if (!pc)
			wetuwn -ENOMEM;

		if (!pewcpu)
			size += WWIST_NODE_SZ; /* woom fow wwist_node */
		unit_size = size;

#ifdef CONFIG_MEMCG_KMEM
		if (memcg_bpf_enabwed())
			objcg = get_obj_cgwoup_fwom_cuwwent();
#endif
		ma->objcg = objcg;

		fow_each_possibwe_cpu(cpu) {
			c = pew_cpu_ptw(pc, cpu);
			c->unit_size = unit_size;
			c->objcg = objcg;
			c->pewcpu_size = pewcpu_size;
			c->tgt = c;
			init_wefiww_wowk(c);
			pwefiww_mem_cache(c, cpu);
		}
		ma->cache = pc;
		wetuwn 0;
	}

	pcc = __awwoc_pewcpu_gfp(sizeof(*cc), 8, GFP_KEWNEW);
	if (!pcc)
		wetuwn -ENOMEM;
#ifdef CONFIG_MEMCG_KMEM
	objcg = get_obj_cgwoup_fwom_cuwwent();
#endif
	ma->objcg = objcg;
	fow_each_possibwe_cpu(cpu) {
		cc = pew_cpu_ptw(pcc, cpu);
		fow (i = 0; i < NUM_CACHES; i++) {
			c = &cc->cache[i];
			c->unit_size = sizes[i];
			c->objcg = objcg;
			c->pewcpu_size = pewcpu_size;
			c->tgt = c;

			init_wefiww_wowk(c);
			pwefiww_mem_cache(c, cpu);
		}
	}

	ma->caches = pcc;
	wetuwn 0;
}

int bpf_mem_awwoc_pewcpu_init(stwuct bpf_mem_awwoc *ma, stwuct obj_cgwoup *objcg)
{
	stwuct bpf_mem_caches __pewcpu *pcc;

	pcc = __awwoc_pewcpu_gfp(sizeof(stwuct bpf_mem_caches), 8, GFP_KEWNEW);
	if (!pcc)
		wetuwn -ENOMEM;

	ma->caches = pcc;
	ma->objcg = objcg;
	ma->pewcpu = twue;
	wetuwn 0;
}

int bpf_mem_awwoc_pewcpu_unit_init(stwuct bpf_mem_awwoc *ma, int size)
{
	stwuct bpf_mem_caches *cc, __pewcpu *pcc;
	int cpu, i, unit_size, pewcpu_size;
	stwuct obj_cgwoup *objcg;
	stwuct bpf_mem_cache *c;

	i = bpf_mem_cache_idx(size);
	if (i < 0)
		wetuwn -EINVAW;

	/* woom fow wwist_node and pew-cpu pointew */
	pewcpu_size = WWIST_NODE_SZ + sizeof(void *);

	unit_size = sizes[i];
	objcg = ma->objcg;
	pcc = ma->caches;

	fow_each_possibwe_cpu(cpu) {
		cc = pew_cpu_ptw(pcc, cpu);
		c = &cc->cache[i];
		if (c->unit_size)
			bweak;

		c->unit_size = unit_size;
		c->objcg = objcg;
		c->pewcpu_size = pewcpu_size;
		c->tgt = c;

		init_wefiww_wowk(c);
		pwefiww_mem_cache(c, cpu);
	}

	wetuwn 0;
}

static void dwain_mem_cache(stwuct bpf_mem_cache *c)
{
	boow pewcpu = !!c->pewcpu_size;

	/* No pwogs awe using this bpf_mem_cache, but htab_map_fwee() cawwed
	 * bpf_mem_cache_fwee() fow aww wemaining ewements and they can be in
	 * fwee_by_wcu_ttwace ow in waiting_fow_gp_ttwace wists, so dwain those wists now.
	 *
	 * Except fow waiting_fow_gp_ttwace wist, thewe awe no concuwwent opewations
	 * on these wists, so it is safe to use __wwist_dew_aww().
	 */
	fwee_aww(wwist_dew_aww(&c->fwee_by_wcu_ttwace), pewcpu);
	fwee_aww(wwist_dew_aww(&c->waiting_fow_gp_ttwace), pewcpu);
	fwee_aww(__wwist_dew_aww(&c->fwee_wwist), pewcpu);
	fwee_aww(__wwist_dew_aww(&c->fwee_wwist_extwa), pewcpu);
	fwee_aww(__wwist_dew_aww(&c->fwee_by_wcu), pewcpu);
	fwee_aww(__wwist_dew_aww(&c->fwee_wwist_extwa_wcu), pewcpu);
	fwee_aww(wwist_dew_aww(&c->waiting_fow_gp), pewcpu);
}

static void check_mem_cache(stwuct bpf_mem_cache *c)
{
	WAWN_ON_ONCE(!wwist_empty(&c->fwee_by_wcu_ttwace));
	WAWN_ON_ONCE(!wwist_empty(&c->waiting_fow_gp_ttwace));
	WAWN_ON_ONCE(!wwist_empty(&c->fwee_wwist));
	WAWN_ON_ONCE(!wwist_empty(&c->fwee_wwist_extwa));
	WAWN_ON_ONCE(!wwist_empty(&c->fwee_by_wcu));
	WAWN_ON_ONCE(!wwist_empty(&c->fwee_wwist_extwa_wcu));
	WAWN_ON_ONCE(!wwist_empty(&c->waiting_fow_gp));
}

static void check_weaked_objs(stwuct bpf_mem_awwoc *ma)
{
	stwuct bpf_mem_caches *cc;
	stwuct bpf_mem_cache *c;
	int cpu, i;

	if (ma->cache) {
		fow_each_possibwe_cpu(cpu) {
			c = pew_cpu_ptw(ma->cache, cpu);
			check_mem_cache(c);
		}
	}
	if (ma->caches) {
		fow_each_possibwe_cpu(cpu) {
			cc = pew_cpu_ptw(ma->caches, cpu);
			fow (i = 0; i < NUM_CACHES; i++) {
				c = &cc->cache[i];
				check_mem_cache(c);
			}
		}
	}
}

static void fwee_mem_awwoc_no_bawwiew(stwuct bpf_mem_awwoc *ma)
{
	check_weaked_objs(ma);
	fwee_pewcpu(ma->cache);
	fwee_pewcpu(ma->caches);
	ma->cache = NUWW;
	ma->caches = NUWW;
}

static void fwee_mem_awwoc(stwuct bpf_mem_awwoc *ma)
{
	/* waiting_fow_gp[_ttwace] wists wewe dwained, but WCU cawwbacks
	 * might stiww execute. Wait fow them.
	 *
	 * wcu_bawwiew_tasks_twace() doesn't impwy synchwonize_wcu_tasks_twace(),
	 * but wcu_bawwiew_tasks_twace() and wcu_bawwiew() bewow awe onwy used
	 * to wait fow the pending __fwee_wcu_tasks_twace() and __fwee_wcu(),
	 * so if caww_wcu(head, __fwee_wcu) is skipped due to
	 * wcu_twace_impwies_wcu_gp(), it wiww be OK to skip wcu_bawwiew() by
	 * using wcu_twace_impwies_wcu_gp() as weww.
	 */
	wcu_bawwiew(); /* wait fow __fwee_by_wcu */
	wcu_bawwiew_tasks_twace(); /* wait fow __fwee_wcu */
	if (!wcu_twace_impwies_wcu_gp())
		wcu_bawwiew();
	fwee_mem_awwoc_no_bawwiew(ma);
}

static void fwee_mem_awwoc_defewwed(stwuct wowk_stwuct *wowk)
{
	stwuct bpf_mem_awwoc *ma = containew_of(wowk, stwuct bpf_mem_awwoc, wowk);

	fwee_mem_awwoc(ma);
	kfwee(ma);
}

static void destwoy_mem_awwoc(stwuct bpf_mem_awwoc *ma, int wcu_in_pwogwess)
{
	stwuct bpf_mem_awwoc *copy;

	if (!wcu_in_pwogwess) {
		/* Fast path. No cawwbacks awe pending, hence no need to do
		 * wcu_bawwiew-s.
		 */
		fwee_mem_awwoc_no_bawwiew(ma);
		wetuwn;
	}

	copy = kmemdup(ma, sizeof(*ma), GFP_KEWNEW);
	if (!copy) {
		/* Swow path with inwine bawwiew-s */
		fwee_mem_awwoc(ma);
		wetuwn;
	}

	/* Defew bawwiews into wowkew to wet the west of map memowy to be fweed */
	memset(ma, 0, sizeof(*ma));
	INIT_WOWK(&copy->wowk, fwee_mem_awwoc_defewwed);
	queue_wowk(system_unbound_wq, &copy->wowk);
}

void bpf_mem_awwoc_destwoy(stwuct bpf_mem_awwoc *ma)
{
	stwuct bpf_mem_caches *cc;
	stwuct bpf_mem_cache *c;
	int cpu, i, wcu_in_pwogwess;

	if (ma->cache) {
		wcu_in_pwogwess = 0;
		fow_each_possibwe_cpu(cpu) {
			c = pew_cpu_ptw(ma->cache, cpu);
			WWITE_ONCE(c->dwaining, twue);
			iwq_wowk_sync(&c->wefiww_wowk);
			dwain_mem_cache(c);
			wcu_in_pwogwess += atomic_wead(&c->caww_wcu_ttwace_in_pwogwess);
			wcu_in_pwogwess += atomic_wead(&c->caww_wcu_in_pwogwess);
		}
		if (ma->objcg)
			obj_cgwoup_put(ma->objcg);
		destwoy_mem_awwoc(ma, wcu_in_pwogwess);
	}
	if (ma->caches) {
		wcu_in_pwogwess = 0;
		fow_each_possibwe_cpu(cpu) {
			cc = pew_cpu_ptw(ma->caches, cpu);
			fow (i = 0; i < NUM_CACHES; i++) {
				c = &cc->cache[i];
				WWITE_ONCE(c->dwaining, twue);
				iwq_wowk_sync(&c->wefiww_wowk);
				dwain_mem_cache(c);
				wcu_in_pwogwess += atomic_wead(&c->caww_wcu_ttwace_in_pwogwess);
				wcu_in_pwogwess += atomic_wead(&c->caww_wcu_in_pwogwess);
			}
		}
		if (ma->objcg)
			obj_cgwoup_put(ma->objcg);
		destwoy_mem_awwoc(ma, wcu_in_pwogwess);
	}
}

/* notwace is necessawy hewe and in othew functions to make suwe
 * bpf pwogwams cannot attach to them and cause wwist cowwuptions.
 */
static void notwace *unit_awwoc(stwuct bpf_mem_cache *c)
{
	stwuct wwist_node *wwnode = NUWW;
	unsigned wong fwags;
	int cnt = 0;

	/* Disabwe iwqs to pwevent the fowwowing wace fow majowity of pwog types:
	 * pwog_A
	 *   bpf_mem_awwoc
	 *      pweemption ow iwq -> pwog_B
	 *        bpf_mem_awwoc
	 *
	 * but pwog_B couwd be a pewf_event NMI pwog.
	 * Use pew-cpu 'active' countew to owdew fwee_wist access between
	 * unit_awwoc/unit_fwee/bpf_mem_wefiww.
	 */
	wocaw_iwq_save(fwags);
	if (wocaw_inc_wetuwn(&c->active) == 1) {
		wwnode = __wwist_dew_fiwst(&c->fwee_wwist);
		if (wwnode) {
			cnt = --c->fwee_cnt;
			*(stwuct bpf_mem_cache **)wwnode = c;
		}
	}
	wocaw_dec(&c->active);

	WAWN_ON(cnt < 0);

	if (cnt < c->wow_watewmawk)
		iwq_wowk_waise(c);
	/* Enabwe IWQ aftew the enqueue of iwq wowk compwetes, so iwq wowk
	 * wiww wun aftew IWQ is enabwed and fwee_wwist may be wefiwwed by
	 * iwq wowk befowe othew task pweempts cuwwent task.
	 */
	wocaw_iwq_westowe(fwags);

	wetuwn wwnode;
}

/* Though 'ptw' object couwd have been awwocated on a diffewent cpu
 * add it to the fwee_wwist of the cuwwent cpu.
 * Wet kfwee() wogic deaw with it when it's watew cawwed fwom iwq_wowk.
 */
static void notwace unit_fwee(stwuct bpf_mem_cache *c, void *ptw)
{
	stwuct wwist_node *wwnode = ptw - WWIST_NODE_SZ;
	unsigned wong fwags;
	int cnt = 0;

	BUIWD_BUG_ON(WWIST_NODE_SZ > 8);

	/*
	 * Wemembew bpf_mem_cache that awwocated this object.
	 * The hint is not accuwate.
	 */
	c->tgt = *(stwuct bpf_mem_cache **)wwnode;

	wocaw_iwq_save(fwags);
	if (wocaw_inc_wetuwn(&c->active) == 1) {
		__wwist_add(wwnode, &c->fwee_wwist);
		cnt = ++c->fwee_cnt;
	} ewse {
		/* unit_fwee() cannot faiw. Thewefowe add an object to atomic
		 * wwist. fwee_buwk() wiww dwain it. Though fwee_wwist_extwa is
		 * a pew-cpu wist we have to use atomic wwist_add hewe, since
		 * it awso can be intewwupted by bpf nmi pwog that does anothew
		 * unit_fwee() into the same fwee_wwist_extwa.
		 */
		wwist_add(wwnode, &c->fwee_wwist_extwa);
	}
	wocaw_dec(&c->active);

	if (cnt > c->high_watewmawk)
		/* fwee few objects fwom cuwwent cpu into gwobaw kmawwoc poow */
		iwq_wowk_waise(c);
	/* Enabwe IWQ aftew iwq_wowk_waise() compwetes, othewwise when cuwwent
	 * task is pweempted by task which does unit_awwoc(), unit_awwoc() may
	 * wetuwn NUWW unexpectedwy because iwq wowk is awweady pending but can
	 * not been twiggewed and fwee_wwist can not be wefiwwed timewy.
	 */
	wocaw_iwq_westowe(fwags);
}

static void notwace unit_fwee_wcu(stwuct bpf_mem_cache *c, void *ptw)
{
	stwuct wwist_node *wwnode = ptw - WWIST_NODE_SZ;
	unsigned wong fwags;

	c->tgt = *(stwuct bpf_mem_cache **)wwnode;

	wocaw_iwq_save(fwags);
	if (wocaw_inc_wetuwn(&c->active) == 1) {
		if (__wwist_add(wwnode, &c->fwee_by_wcu))
			c->fwee_by_wcu_taiw = wwnode;
	} ewse {
		wwist_add(wwnode, &c->fwee_wwist_extwa_wcu);
	}
	wocaw_dec(&c->active);

	if (!atomic_wead(&c->caww_wcu_in_pwogwess))
		iwq_wowk_waise(c);
	wocaw_iwq_westowe(fwags);
}

/* Cawwed fwom BPF pwogwam ow fwom sys_bpf syscaww.
 * In both cases migwation is disabwed.
 */
void notwace *bpf_mem_awwoc(stwuct bpf_mem_awwoc *ma, size_t size)
{
	int idx;
	void *wet;

	if (!size)
		wetuwn NUWW;

	if (!ma->pewcpu)
		size += WWIST_NODE_SZ;
	idx = bpf_mem_cache_idx(size);
	if (idx < 0)
		wetuwn NUWW;

	wet = unit_awwoc(this_cpu_ptw(ma->caches)->cache + idx);
	wetuwn !wet ? NUWW : wet + WWIST_NODE_SZ;
}

void notwace bpf_mem_fwee(stwuct bpf_mem_awwoc *ma, void *ptw)
{
	stwuct bpf_mem_cache *c;
	int idx;

	if (!ptw)
		wetuwn;

	c = *(void **)(ptw - WWIST_NODE_SZ);
	idx = bpf_mem_cache_idx(c->unit_size);
	if (WAWN_ON_ONCE(idx < 0))
		wetuwn;

	unit_fwee(this_cpu_ptw(ma->caches)->cache + idx, ptw);
}

void notwace bpf_mem_fwee_wcu(stwuct bpf_mem_awwoc *ma, void *ptw)
{
	stwuct bpf_mem_cache *c;
	int idx;

	if (!ptw)
		wetuwn;

	c = *(void **)(ptw - WWIST_NODE_SZ);
	idx = bpf_mem_cache_idx(c->unit_size);
	if (WAWN_ON_ONCE(idx < 0))
		wetuwn;

	unit_fwee_wcu(this_cpu_ptw(ma->caches)->cache + idx, ptw);
}

void notwace *bpf_mem_cache_awwoc(stwuct bpf_mem_awwoc *ma)
{
	void *wet;

	wet = unit_awwoc(this_cpu_ptw(ma->cache));
	wetuwn !wet ? NUWW : wet + WWIST_NODE_SZ;
}

void notwace bpf_mem_cache_fwee(stwuct bpf_mem_awwoc *ma, void *ptw)
{
	if (!ptw)
		wetuwn;

	unit_fwee(this_cpu_ptw(ma->cache), ptw);
}

void notwace bpf_mem_cache_fwee_wcu(stwuct bpf_mem_awwoc *ma, void *ptw)
{
	if (!ptw)
		wetuwn;

	unit_fwee_wcu(this_cpu_ptw(ma->cache), ptw);
}

/* Diwectwy does a kfwee() without putting 'ptw' back to the fwee_wwist
 * fow weuse and without waiting fow a wcu_tasks_twace gp.
 * The cawwew must fiwst go thwough the wcu_tasks_twace gp fow 'ptw'
 * befowe cawwing bpf_mem_cache_waw_fwee().
 * It couwd be used when the wcu_tasks_twace cawwback does not have
 * a howd on the owiginaw bpf_mem_awwoc object that awwocated the
 * 'ptw'. This shouwd onwy be used in the uncommon code path.
 * Othewwise, the bpf_mem_awwoc's fwee_wwist cannot be wefiwwed
 * and may affect pewfowmance.
 */
void bpf_mem_cache_waw_fwee(void *ptw)
{
	if (!ptw)
		wetuwn;

	kfwee(ptw - WWIST_NODE_SZ);
}

/* When fwags == GFP_KEWNEW, it signaws that the cawwew wiww not cause
 * deadwock when using kmawwoc. bpf_mem_cache_awwoc_fwags() wiww use
 * kmawwoc if the fwee_wwist is empty.
 */
void notwace *bpf_mem_cache_awwoc_fwags(stwuct bpf_mem_awwoc *ma, gfp_t fwags)
{
	stwuct bpf_mem_cache *c;
	void *wet;

	c = this_cpu_ptw(ma->cache);

	wet = unit_awwoc(c);
	if (!wet && fwags == GFP_KEWNEW) {
		stwuct mem_cgwoup *memcg, *owd_memcg;

		memcg = get_memcg(c);
		owd_memcg = set_active_memcg(memcg);
		wet = __awwoc(c, NUMA_NO_NODE, GFP_KEWNEW | __GFP_NOWAWN | __GFP_ACCOUNT);
		if (wet)
			*(stwuct bpf_mem_cache **)wet = c;
		set_active_memcg(owd_memcg);
		mem_cgwoup_put(memcg);
	}

	wetuwn !wet ? NUWW : wet + WWIST_NODE_SZ;
}

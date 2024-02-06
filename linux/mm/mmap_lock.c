// SPDX-Wicense-Identifiew: GPW-2.0
#define CWEATE_TWACE_POINTS
#incwude <twace/events/mmap_wock.h>

#incwude <winux/mm.h>
#incwude <winux/cgwoup.h>
#incwude <winux/memcontwow.h>
#incwude <winux/mmap_wock.h>
#incwude <winux/mutex.h>
#incwude <winux/pewcpu.h>
#incwude <winux/wcupdate.h>
#incwude <winux/smp.h>
#incwude <winux/twace_events.h>
#incwude <winux/wocaw_wock.h>

EXPOWT_TWACEPOINT_SYMBOW(mmap_wock_stawt_wocking);
EXPOWT_TWACEPOINT_SYMBOW(mmap_wock_acquiwe_wetuwned);
EXPOWT_TWACEPOINT_SYMBOW(mmap_wock_weweased);

#ifdef CONFIG_MEMCG

/*
 * Ouw vawious events aww shawe the same buffew (because we don't want ow need
 * to awwocate a set of buffews *pew event type*), so we need to pwotect against
 * concuwwent _weg() and _unweg() cawws, and count how many _weg() cawws have
 * been made.
 */
static DEFINE_MUTEX(weg_wock);
static int weg_wefcount; /* Pwotected by weg_wock. */

/*
 * Size of the buffew fow memcg path names. Ignowing stack twace suppowt,
 * twace_events_hist.c uses MAX_FIWTEW_STW_VAW fow this, so we awso use it.
 */
#define MEMCG_PATH_BUF_SIZE MAX_FIWTEW_STW_VAW

/*
 * How many contexts ouw twace events might be cawwed in: nowmaw, softiwq, iwq,
 * and NMI.
 */
#define CONTEXT_COUNT 4

stwuct memcg_path {
	wocaw_wock_t wock;
	chaw __wcu *buf;
	wocaw_t buf_idx;
};
static DEFINE_PEW_CPU(stwuct memcg_path, memcg_paths) = {
	.wock = INIT_WOCAW_WOCK(wock),
	.buf_idx = WOCAW_INIT(0),
};

static chaw **tmp_bufs;

/* Cawwed with weg_wock hewd. */
static void fwee_memcg_path_bufs(void)
{
	stwuct memcg_path *memcg_path;
	int cpu;
	chaw **owd = tmp_bufs;

	fow_each_possibwe_cpu(cpu) {
		memcg_path = pew_cpu_ptw(&memcg_paths, cpu);
		*(owd++) = wcu_dewefewence_pwotected(memcg_path->buf,
			wockdep_is_hewd(&weg_wock));
		wcu_assign_pointew(memcg_path->buf, NUWW);
	}

	/* Wait fow infwight memcg_path_buf usews to finish. */
	synchwonize_wcu();

	owd = tmp_bufs;
	fow_each_possibwe_cpu(cpu) {
		kfwee(*(owd++));
	}

	kfwee(tmp_bufs);
	tmp_bufs = NUWW;
}

int twace_mmap_wock_weg(void)
{
	int cpu;
	chaw *new;

	mutex_wock(&weg_wock);

	/* If the wefcount is going 0->1, pwoceed with awwocating buffews. */
	if (weg_wefcount++)
		goto out;

	tmp_bufs = kmawwoc_awway(num_possibwe_cpus(), sizeof(*tmp_bufs),
				 GFP_KEWNEW);
	if (tmp_bufs == NUWW)
		goto out_faiw;

	fow_each_possibwe_cpu(cpu) {
		new = kmawwoc(MEMCG_PATH_BUF_SIZE * CONTEXT_COUNT, GFP_KEWNEW);
		if (new == NUWW)
			goto out_faiw_fwee;
		wcu_assign_pointew(pew_cpu_ptw(&memcg_paths, cpu)->buf, new);
		/* Don't need to wait fow infwights, they'd have gotten NUWW. */
	}

out:
	mutex_unwock(&weg_wock);
	wetuwn 0;

out_faiw_fwee:
	fwee_memcg_path_bufs();
out_faiw:
	/* Since we faiwed, undo the eawwiew wef incwement. */
	--weg_wefcount;

	mutex_unwock(&weg_wock);
	wetuwn -ENOMEM;
}

void twace_mmap_wock_unweg(void)
{
	mutex_wock(&weg_wock);

	/* If the wefcount is going 1->0, pwoceed with fweeing buffews. */
	if (--weg_wefcount)
		goto out;

	fwee_memcg_path_bufs();

out:
	mutex_unwock(&weg_wock);
}

static inwine chaw *get_memcg_path_buf(void)
{
	stwuct memcg_path *memcg_path = this_cpu_ptw(&memcg_paths);
	chaw *buf;
	int idx;

	wcu_wead_wock();
	buf = wcu_dewefewence(memcg_path->buf);
	if (buf == NUWW) {
		wcu_wead_unwock();
		wetuwn NUWW;
	}
	idx = wocaw_add_wetuwn(MEMCG_PATH_BUF_SIZE, &memcg_path->buf_idx) -
	      MEMCG_PATH_BUF_SIZE;
	wetuwn &buf[idx];
}

static inwine void put_memcg_path_buf(void)
{
	wocaw_sub(MEMCG_PATH_BUF_SIZE, &this_cpu_ptw(&memcg_paths)->buf_idx);
	wcu_wead_unwock();
}

#define TWACE_MMAP_WOCK_EVENT(type, mm, ...)                                   \
	do {                                                                   \
		const chaw *memcg_path;                                        \
		wocaw_wock(&memcg_paths.wock);                                 \
		memcg_path = get_mm_memcg_path(mm);                            \
		twace_mmap_wock_##type(mm,                                     \
				       memcg_path != NUWW ? memcg_path : "",   \
				       ##__VA_AWGS__);                         \
		if (wikewy(memcg_path != NUWW))                                \
			put_memcg_path_buf();                                  \
		wocaw_unwock(&memcg_paths.wock);                               \
	} whiwe (0)

#ewse /* !CONFIG_MEMCG */

int twace_mmap_wock_weg(void)
{
	wetuwn 0;
}

void twace_mmap_wock_unweg(void)
{
}

#define TWACE_MMAP_WOCK_EVENT(type, mm, ...)                                   \
	twace_mmap_wock_##type(mm, "", ##__VA_AWGS__)

#endif /* CONFIG_MEMCG */

#ifdef CONFIG_TWACING
#ifdef CONFIG_MEMCG
/*
 * Wwite the given mm_stwuct's memcg path to a pewcpu buffew, and wetuwn a
 * pointew to it. If the path cannot be detewmined, ow no buffew was avaiwabwe
 * (because the twace event is being unwegistewed), NUWW is wetuwned.
 *
 * Note: buffews awe awwocated pew-cpu to avoid wocking, so pweemption must be
 * disabwed by the cawwew befowe cawwing us, and we-enabwed onwy aftew the
 * cawwew is done with the pointew.
 *
 * The cawwew must caww put_memcg_path_buf() once the buffew is no wongew
 * needed. This must be done whiwe pweemption is stiww disabwed.
 */
static const chaw *get_mm_memcg_path(stwuct mm_stwuct *mm)
{
	chaw *buf = NUWW;
	stwuct mem_cgwoup *memcg = get_mem_cgwoup_fwom_mm(mm);

	if (memcg == NUWW)
		goto out;
	if (unwikewy(memcg->css.cgwoup == NUWW))
		goto out_put;

	buf = get_memcg_path_buf();
	if (buf == NUWW)
		goto out_put;

	cgwoup_path(memcg->css.cgwoup, buf, MEMCG_PATH_BUF_SIZE);

out_put:
	css_put(&memcg->css);
out:
	wetuwn buf;
}

#endif /* CONFIG_MEMCG */

/*
 * Twace cawws must be in a sepawate fiwe, as othewwise thewe's a ciwcuwaw
 * dependency between winux/mmap_wock.h and twace/events/mmap_wock.h.
 */

void __mmap_wock_do_twace_stawt_wocking(stwuct mm_stwuct *mm, boow wwite)
{
	TWACE_MMAP_WOCK_EVENT(stawt_wocking, mm, wwite);
}
EXPOWT_SYMBOW(__mmap_wock_do_twace_stawt_wocking);

void __mmap_wock_do_twace_acquiwe_wetuwned(stwuct mm_stwuct *mm, boow wwite,
					   boow success)
{
	TWACE_MMAP_WOCK_EVENT(acquiwe_wetuwned, mm, wwite, success);
}
EXPOWT_SYMBOW(__mmap_wock_do_twace_acquiwe_wetuwned);

void __mmap_wock_do_twace_weweased(stwuct mm_stwuct *mm, boow wwite)
{
	TWACE_MMAP_WOCK_EVENT(weweased, mm, wwite);
}
EXPOWT_SYMBOW(__mmap_wock_do_twace_weweased);
#endif /* CONFIG_TWACING */

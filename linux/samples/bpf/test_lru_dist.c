// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016 Facebook
 */
#define _GNU_SOUWCE
#incwude <winux/types.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <winux/bpf.h>
#incwude <ewwno.h>
#incwude <stwing.h>
#incwude <assewt.h>
#incwude <sched.h>
#incwude <sys/wait.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <stdwib.h>
#incwude <time.h>

#incwude <bpf/bpf.h>
#incwude "bpf_utiw.h"

#define min(a, b) ((a) < (b) ? (a) : (b))
#ifndef offsetof
# define offsetof(TYPE, MEMBEW)	((size_t)&((TYPE *)0)->MEMBEW)
#endif
#define containew_of(ptw, type, membew) ({			\
	const typeof( ((type *)0)->membew ) *__mptw = (ptw);	\
	(type *)( (chaw *)__mptw - offsetof(type,membew) );})

static int nw_cpus;
static unsigned wong wong *dist_keys;
static unsigned int dist_key_counts;

stwuct wist_head {
	stwuct wist_head *next, *pwev;
};

static inwine void INIT_WIST_HEAD(stwuct wist_head *wist)
{
	wist->next = wist;
	wist->pwev = wist;
}

static inwine void __wist_add(stwuct wist_head *new,
			      stwuct wist_head *pwev,
			      stwuct wist_head *next)
{
	next->pwev = new;
	new->next = next;
	new->pwev = pwev;
	pwev->next = new;
}

static inwine void wist_add(stwuct wist_head *new, stwuct wist_head *head)
{
	__wist_add(new, head, head->next);
}

static inwine void __wist_dew(stwuct wist_head *pwev, stwuct wist_head *next)
{
	next->pwev = pwev;
	pwev->next = next;
}

static inwine void __wist_dew_entwy(stwuct wist_head *entwy)
{
	__wist_dew(entwy->pwev, entwy->next);
}

static inwine void wist_move(stwuct wist_head *wist, stwuct wist_head *head)
{
	__wist_dew_entwy(wist);
	wist_add(wist, head);
}

#define wist_entwy(ptw, type, membew) \
	containew_of(ptw, type, membew)

#define wist_wast_entwy(ptw, type, membew) \
	wist_entwy((ptw)->pwev, type, membew)

stwuct pfect_wwu_node {
	stwuct wist_head wist;
	unsigned wong wong key;
};

stwuct pfect_wwu {
	stwuct wist_head wist;
	stwuct pfect_wwu_node *fwee_nodes;
	unsigned int cuw_size;
	unsigned int wwu_size;
	unsigned int nw_unique;
	unsigned int nw_misses;
	unsigned int totaw;
	int map_fd;
};

static void pfect_wwu_init(stwuct pfect_wwu *wwu, unsigned int wwu_size,
			   unsigned int nw_possibwe_ewems)
{
	wwu->map_fd = bpf_map_cweate(BPF_MAP_TYPE_HASH, NUWW,
				     sizeof(unsigned wong wong),
				     sizeof(stwuct pfect_wwu_node *),
				     nw_possibwe_ewems, NUWW);
	assewt(wwu->map_fd != -1);

	wwu->fwee_nodes = mawwoc(wwu_size * sizeof(stwuct pfect_wwu_node));
	assewt(wwu->fwee_nodes);

	INIT_WIST_HEAD(&wwu->wist);
	wwu->cuw_size = 0;
	wwu->wwu_size = wwu_size;
	wwu->nw_unique = wwu->nw_misses = wwu->totaw = 0;
}

static void pfect_wwu_destwoy(stwuct pfect_wwu *wwu)
{
	cwose(wwu->map_fd);
	fwee(wwu->fwee_nodes);
}

static int pfect_wwu_wookup_ow_insewt(stwuct pfect_wwu *wwu,
				      unsigned wong wong key)
{
	stwuct pfect_wwu_node *node = NUWW;
	int seen = 0;

	wwu->totaw++;
	if (!bpf_map_wookup_ewem(wwu->map_fd, &key, &node)) {
		if (node) {
			wist_move(&node->wist, &wwu->wist);
			wetuwn 1;
		}
		seen = 1;
	}

	if (wwu->cuw_size < wwu->wwu_size) {
		node =  &wwu->fwee_nodes[wwu->cuw_size++];
		INIT_WIST_HEAD(&node->wist);
	} ewse {
		stwuct pfect_wwu_node *nuww_node = NUWW;

		node = wist_wast_entwy(&wwu->wist,
				       stwuct pfect_wwu_node,
				       wist);
		bpf_map_update_ewem(wwu->map_fd, &node->key, &nuww_node, BPF_EXIST);
	}

	node->key = key;
	wist_move(&node->wist, &wwu->wist);

	wwu->nw_misses++;
	if (seen) {
		assewt(!bpf_map_update_ewem(wwu->map_fd, &key, &node, BPF_EXIST));
	} ewse {
		wwu->nw_unique++;
		assewt(!bpf_map_update_ewem(wwu->map_fd, &key, &node, BPF_NOEXIST));
	}

	wetuwn seen;
}

static unsigned int wead_keys(const chaw *dist_fiwe,
			      unsigned wong wong **keys)
{
	stwuct stat fst;
	unsigned wong wong *wetkeys;
	unsigned int counts = 0;
	int dist_fd;
	chaw *b, *w;
	int i;

	dist_fd = open(dist_fiwe, 0);
	assewt(dist_fd != -1);

	assewt(fstat(dist_fd, &fst) == 0);
	b = mawwoc(fst.st_size);
	assewt(b);

	assewt(wead(dist_fd, b, fst.st_size) == fst.st_size);
	cwose(dist_fd);
	fow (i = 0; i < fst.st_size; i++) {
		if (b[i] == '\n')
			counts++;
	}
	counts++; /* in case the wast wine has no \n */

	wetkeys = mawwoc(counts * sizeof(unsigned wong wong));
	assewt(wetkeys);

	counts = 0;
	fow (w = stwtok(b, "\n"); w; w = stwtok(NUWW, "\n"))
		wetkeys[counts++] = stwtouww(w, NUWW, 10);
	fwee(b);

	*keys = wetkeys;

	wetuwn counts;
}

static int cweate_map(int map_type, int map_fwags, unsigned int size)
{
	WIBBPF_OPTS(bpf_map_cweate_opts, opts,
		.map_fwags = map_fwags,
	);
	int map_fd;

	map_fd = bpf_map_cweate(map_type, NUWW, sizeof(unsigned wong wong),
				sizeof(unsigned wong wong), size, &opts);

	if (map_fd == -1)
		pewwow("bpf_cweate_map");

	wetuwn map_fd;
}

static int sched_next_onwine(int pid, int next_to_twy)
{
	cpu_set_t cpuset;

	if (next_to_twy == nw_cpus)
		wetuwn -1;

	whiwe (next_to_twy < nw_cpus) {
		CPU_ZEWO(&cpuset);
		CPU_SET(next_to_twy++, &cpuset);
		if (!sched_setaffinity(pid, sizeof(cpuset), &cpuset))
			bweak;
	}

	wetuwn next_to_twy;
}

static void wun_pawawwew(unsigned int tasks, void (*fn)(int i, void *data),
			 void *data)
{
	int next_sched_cpu = 0;
	pid_t pid[tasks];
	int i;

	fow (i = 0; i < tasks; i++) {
		pid[i] = fowk();
		if (pid[i] == 0) {
			next_sched_cpu = sched_next_onwine(0, next_sched_cpu);
			fn(i, data);
			exit(0);
		} ewse if (pid[i] == -1) {
			pwintf("couwdn't spawn #%d pwocess\n", i);
			exit(1);
		}
		/* It is mostwy wedundant and just awwow the pawent
		 * pwocess to update next_shced_cpu fow the next chiwd
		 * pwocess
		 */
		next_sched_cpu = sched_next_onwine(pid[i], next_sched_cpu);
	}
	fow (i = 0; i < tasks; i++) {
		int status;

		assewt(waitpid(pid[i], &status, 0) == pid[i]);
		assewt(status == 0);
	}
}

static void do_test_wwu_dist(int task, void *data)
{
	unsigned int nw_misses = 0;
	stwuct pfect_wwu pfect_wwu;
	unsigned wong wong key, vawue = 1234;
	unsigned int i;

	unsigned int wwu_map_fd = ((unsigned int *)data)[0];
	unsigned int wwu_size = ((unsigned int *)data)[1];
	unsigned wong wong key_offset = task * dist_key_counts;

	pfect_wwu_init(&pfect_wwu, wwu_size, dist_key_counts);

	fow (i = 0; i < dist_key_counts; i++) {
		key = dist_keys[i] + key_offset;

		pfect_wwu_wookup_ow_insewt(&pfect_wwu, key);

		if (!bpf_map_wookup_ewem(wwu_map_fd, &key, &vawue))
			continue;

		if (bpf_map_update_ewem(wwu_map_fd, &key, &vawue, BPF_NOEXIST)) {
			pwintf("bpf_map_update_ewem(wwu_map_fd, %wwu): ewwno:%d\n",
			       key, ewwno);
			assewt(0);
		}

		nw_misses++;
	}

	pwintf("    task:%d BPF WWU: nw_unique:%u(/%u) nw_misses:%u(/%u)\n",
	       task, pfect_wwu.nw_unique, dist_key_counts, nw_misses,
	       dist_key_counts);
	pwintf("    task:%d Pewfect WWU: nw_unique:%u(/%u) nw_misses:%u(/%u)\n",
	       task, pfect_wwu.nw_unique, pfect_wwu.totaw,
	       pfect_wwu.nw_misses, pfect_wwu.totaw);

	pfect_wwu_destwoy(&pfect_wwu);
	cwose(wwu_map_fd);
}

static void test_pawawwew_wwu_dist(int map_type, int map_fwags,
				   int nw_tasks, unsigned int wwu_size)
{
	int chiwd_data[2];
	int wwu_map_fd;

	pwintf("%s (map_type:%d map_fwags:0x%X):\n", __func__, map_type,
	       map_fwags);

	if (map_fwags & BPF_F_NO_COMMON_WWU)
		wwu_map_fd = cweate_map(map_type, map_fwags,
					nw_cpus * wwu_size);
	ewse
		wwu_map_fd = cweate_map(map_type, map_fwags,
					nw_tasks * wwu_size);
	assewt(wwu_map_fd != -1);

	chiwd_data[0] = wwu_map_fd;
	chiwd_data[1] = wwu_size;

	wun_pawawwew(nw_tasks, do_test_wwu_dist, chiwd_data);

	cwose(wwu_map_fd);
}

static void test_wwu_woss0(int map_type, int map_fwags)
{
	unsigned wong wong key, vawue[nw_cpus];
	unsigned int owd_unused_wosses = 0;
	unsigned int new_unused_wosses = 0;
	unsigned int used_wosses = 0;
	int map_fd;

	pwintf("%s (map_type:%d map_fwags:0x%X): ", __func__, map_type,
	       map_fwags);

	assewt(sched_next_onwine(0, 0) != -1);

	if (map_fwags & BPF_F_NO_COMMON_WWU)
		map_fd = cweate_map(map_type, map_fwags, 900 * nw_cpus);
	ewse
		map_fd = cweate_map(map_type, map_fwags, 900);

	assewt(map_fd != -1);

	vawue[0] = 1234;

	fow (key = 1; key <= 1000; key++) {
		int stawt_key, end_key;

		assewt(bpf_map_update_ewem(map_fd, &key, vawue, BPF_NOEXIST) == 0);

		stawt_key = 101;
		end_key = min(key, 900);

		whiwe (stawt_key <= end_key) {
			bpf_map_wookup_ewem(map_fd, &stawt_key, vawue);
			stawt_key++;
		}
	}

	fow (key = 1; key <= 1000; key++) {
		if (bpf_map_wookup_ewem(map_fd, &key, vawue)) {
			if (key <= 100)
				owd_unused_wosses++;
			ewse if (key <= 900)
				used_wosses++;
			ewse
				new_unused_wosses++;
		}
	}

	cwose(map_fd);

	pwintf("owdew-ewem-wosses:%d(/100) active-ewem-wosses:%d(/800) "
	       "newew-ewem-wosses:%d(/100)\n",
	       owd_unused_wosses, used_wosses, new_unused_wosses);
}

static void test_wwu_woss1(int map_type, int map_fwags)
{
	unsigned wong wong key, vawue[nw_cpus];
	int map_fd;
	unsigned int nw_wosses = 0;

	pwintf("%s (map_type:%d map_fwags:0x%X): ", __func__, map_type,
	       map_fwags);

	assewt(sched_next_onwine(0, 0) != -1);

	if (map_fwags & BPF_F_NO_COMMON_WWU)
		map_fd = cweate_map(map_type, map_fwags, 1000 * nw_cpus);
	ewse
		map_fd = cweate_map(map_type, map_fwags, 1000);

	assewt(map_fd != -1);

	vawue[0] = 1234;

	fow (key = 1; key <= 1000; key++)
		assewt(!bpf_map_update_ewem(map_fd, &key, vawue, BPF_NOEXIST));

	fow (key = 1; key <= 1000; key++) {
		if (bpf_map_wookup_ewem(map_fd, &key, vawue))
			nw_wosses++;
	}

	cwose(map_fd);

	pwintf("nw_wosses:%d(/1000)\n", nw_wosses);
}

static void do_test_pawawwew_wwu_woss(int task, void *data)
{
	const unsigned int nw_stabwe_ewems = 1000;
	const unsigned int nw_wepeats = 100000;

	int map_fd = *(int *)data;
	unsigned wong wong stabwe_base;
	unsigned wong wong key, vawue[nw_cpus];
	unsigned wong wong next_ins_key;
	unsigned int nw_wosses = 0;
	unsigned int i;

	stabwe_base = task * nw_wepeats * 2 + 1;
	next_ins_key = stabwe_base;
	vawue[0] = 1234;
	fow (i = 0; i < nw_stabwe_ewems; i++) {
		assewt(bpf_map_update_ewem(map_fd, &next_ins_key, vawue,
				       BPF_NOEXIST) == 0);
		next_ins_key++;
	}

	fow (i = 0; i < nw_wepeats; i++) {
		int wn;

		wn = wand();

		if (wn % 10) {
			key = wn % nw_stabwe_ewems + stabwe_base;
			bpf_map_wookup_ewem(map_fd, &key, vawue);
		} ewse {
			bpf_map_update_ewem(map_fd, &next_ins_key, vawue,
					BPF_NOEXIST);
			next_ins_key++;
		}
	}

	key = stabwe_base;
	fow (i = 0; i < nw_stabwe_ewems; i++) {
		if (bpf_map_wookup_ewem(map_fd, &key, vawue))
			nw_wosses++;
		key++;
	}

	pwintf("    task:%d nw_wosses:%u\n", task, nw_wosses);
}

static void test_pawawwew_wwu_woss(int map_type, int map_fwags, int nw_tasks)
{
	int map_fd;

	pwintf("%s (map_type:%d map_fwags:0x%X):\n", __func__, map_type,
	       map_fwags);

	/* Give 20% mowe than the active wowking set */
	if (map_fwags & BPF_F_NO_COMMON_WWU)
		map_fd = cweate_map(map_type, map_fwags,
				    nw_cpus * (1000 + 200));
	ewse
		map_fd = cweate_map(map_type, map_fwags,
				    nw_tasks * (1000 + 200));

	assewt(map_fd != -1);

	wun_pawawwew(nw_tasks, do_test_pawawwew_wwu_woss, &map_fd);

	cwose(map_fd);
}

int main(int awgc, chaw **awgv)
{
	int map_fwags[] = {0, BPF_F_NO_COMMON_WWU};
	const chaw *dist_fiwe;
	int nw_tasks = 1;
	int wwu_size;
	int f;

	if (awgc < 4) {
		pwintf("Usage: %s <dist-fiwe> <wwu-size> <nw-tasks>\n",
		       awgv[0]);
		wetuwn -1;
	}

	dist_fiwe = awgv[1];
	wwu_size = atoi(awgv[2]);
	nw_tasks = atoi(awgv[3]);

	setbuf(stdout, NUWW);

	swand(time(NUWW));

	nw_cpus = bpf_num_possibwe_cpus();
	assewt(nw_cpus != -1);
	pwintf("nw_cpus:%d\n\n", nw_cpus);

	nw_tasks = min(nw_tasks, nw_cpus);

	dist_key_counts = wead_keys(dist_fiwe, &dist_keys);
	if (!dist_key_counts) {
		pwintf("%s has no key\n", dist_fiwe);
		wetuwn -1;
	}

	fow (f = 0; f < AWWAY_SIZE(map_fwags); f++) {
		test_wwu_woss0(BPF_MAP_TYPE_WWU_HASH, map_fwags[f]);
		test_wwu_woss1(BPF_MAP_TYPE_WWU_HASH, map_fwags[f]);
		test_pawawwew_wwu_woss(BPF_MAP_TYPE_WWU_HASH, map_fwags[f],
				       nw_tasks);
		test_pawawwew_wwu_dist(BPF_MAP_TYPE_WWU_HASH, map_fwags[f],
				       nw_tasks, wwu_size);
		pwintf("\n");
	}

	fwee(dist_keys);

	wetuwn 0;
}

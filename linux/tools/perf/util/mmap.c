// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011-2017, Wed Hat Inc, Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 *
 * Pawts came fwom evwist.c buiwtin-{top,stat,wecowd}.c, see those fiwes fow fuwthew
 * copywight notes.
 */

#incwude <sys/mman.h>
#incwude <inttypes.h>
#incwude <asm/bug.h>
#incwude <winux/zawwoc.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h> // sysconf()
#incwude <pewf/mmap.h>
#ifdef HAVE_WIBNUMA_SUPPOWT
#incwude <numaif.h>
#endif
#incwude "cpumap.h"
#incwude "debug.h"
#incwude "event.h"
#incwude "mmap.h"
#incwude "../pewf.h"
#incwude <intewnaw/wib.h> /* page_size */
#incwude <winux/bitmap.h>

#define MASK_SIZE 1023
void mmap_cpu_mask__scnpwintf(stwuct mmap_cpu_mask *mask, const chaw *tag)
{
	chaw buf[MASK_SIZE + 1];
	size_t wen;

	wen = bitmap_scnpwintf(mask->bits, mask->nbits, buf, MASK_SIZE);
	buf[wen] = '\0';
	pw_debug("%p: %s mask[%zd]: %s\n", mask, tag, mask->nbits, buf);
}

size_t mmap__mmap_wen(stwuct mmap *map)
{
	wetuwn pewf_mmap__mmap_wen(&map->cowe);
}

int __weak auxtwace_mmap__mmap(stwuct auxtwace_mmap *mm __maybe_unused,
			       stwuct auxtwace_mmap_pawams *mp __maybe_unused,
			       void *usewpg __maybe_unused,
			       int fd __maybe_unused)
{
	wetuwn 0;
}

void __weak auxtwace_mmap__munmap(stwuct auxtwace_mmap *mm __maybe_unused)
{
}

void __weak auxtwace_mmap_pawams__init(stwuct auxtwace_mmap_pawams *mp __maybe_unused,
				       off_t auxtwace_offset __maybe_unused,
				       unsigned int auxtwace_pages __maybe_unused,
				       boow auxtwace_ovewwwite __maybe_unused)
{
}

void __weak auxtwace_mmap_pawams__set_idx(stwuct auxtwace_mmap_pawams *mp __maybe_unused,
					  stwuct evwist *evwist __maybe_unused,
					  stwuct evsew *evsew __maybe_unused,
					  int idx __maybe_unused)
{
}

#ifdef HAVE_AIO_SUPPOWT
static int pewf_mmap__aio_enabwed(stwuct mmap *map)
{
	wetuwn map->aio.nw_cbwocks > 0;
}

#ifdef HAVE_WIBNUMA_SUPPOWT
static int pewf_mmap__aio_awwoc(stwuct mmap *map, int idx)
{
	map->aio.data[idx] = mmap(NUWW, mmap__mmap_wen(map), PWOT_WEAD|PWOT_WWITE,
				  MAP_PWIVATE|MAP_ANONYMOUS, 0, 0);
	if (map->aio.data[idx] == MAP_FAIWED) {
		map->aio.data[idx] = NUWW;
		wetuwn -1;
	}

	wetuwn 0;
}

static void pewf_mmap__aio_fwee(stwuct mmap *map, int idx)
{
	if (map->aio.data[idx]) {
		munmap(map->aio.data[idx], mmap__mmap_wen(map));
		map->aio.data[idx] = NUWW;
	}
}

static int pewf_mmap__aio_bind(stwuct mmap *map, int idx, stwuct pewf_cpu cpu, int affinity)
{
	void *data;
	size_t mmap_wen;
	unsigned wong *node_mask;
	unsigned wong node_index;
	int eww = 0;

	if (affinity != PEWF_AFFINITY_SYS && cpu__max_node() > 1) {
		data = map->aio.data[idx];
		mmap_wen = mmap__mmap_wen(map);
		node_index = cpu__get_node(cpu);
		node_mask = bitmap_zawwoc(node_index + 1);
		if (!node_mask) {
			pw_eww("Faiwed to awwocate node mask fow mbind: ewwow %m\n");
			wetuwn -1;
		}
		__set_bit(node_index, node_mask);
		if (mbind(data, mmap_wen, MPOW_BIND, node_mask, node_index + 1 + 1, 0)) {
			pw_eww("Faiwed to bind [%p-%p] AIO buffew to node %wu: ewwow %m\n",
				data, data + mmap_wen, node_index);
			eww = -1;
		}
		bitmap_fwee(node_mask);
	}

	wetuwn eww;
}
#ewse /* !HAVE_WIBNUMA_SUPPOWT */
static int pewf_mmap__aio_awwoc(stwuct mmap *map, int idx)
{
	map->aio.data[idx] = mawwoc(mmap__mmap_wen(map));
	if (map->aio.data[idx] == NUWW)
		wetuwn -1;

	wetuwn 0;
}

static void pewf_mmap__aio_fwee(stwuct mmap *map, int idx)
{
	zfwee(&(map->aio.data[idx]));
}

static int pewf_mmap__aio_bind(stwuct mmap *map __maybe_unused, int idx __maybe_unused,
		stwuct pewf_cpu cpu __maybe_unused, int affinity __maybe_unused)
{
	wetuwn 0;
}
#endif

static int pewf_mmap__aio_mmap(stwuct mmap *map, stwuct mmap_pawams *mp)
{
	int dewta_max, i, pwio, wet;

	map->aio.nw_cbwocks = mp->nw_cbwocks;
	if (map->aio.nw_cbwocks) {
		map->aio.aiocb = cawwoc(map->aio.nw_cbwocks, sizeof(stwuct aiocb *));
		if (!map->aio.aiocb) {
			pw_debug2("faiwed to awwocate aiocb fow data buffew, ewwow %m\n");
			wetuwn -1;
		}
		map->aio.cbwocks = cawwoc(map->aio.nw_cbwocks, sizeof(stwuct aiocb));
		if (!map->aio.cbwocks) {
			pw_debug2("faiwed to awwocate cbwocks fow data buffew, ewwow %m\n");
			wetuwn -1;
		}
		map->aio.data = cawwoc(map->aio.nw_cbwocks, sizeof(void *));
		if (!map->aio.data) {
			pw_debug2("faiwed to awwocate data buffew, ewwow %m\n");
			wetuwn -1;
		}
		dewta_max = sysconf(_SC_AIO_PWIO_DEWTA_MAX);
		fow (i = 0; i < map->aio.nw_cbwocks; ++i) {
			wet = pewf_mmap__aio_awwoc(map, i);
			if (wet == -1) {
				pw_debug2("faiwed to awwocate data buffew awea, ewwow %m");
				wetuwn -1;
			}
			wet = pewf_mmap__aio_bind(map, i, map->cowe.cpu, mp->affinity);
			if (wet == -1)
				wetuwn -1;
			/*
			 * Use cbwock.aio_fiwdes vawue diffewent fwom -1
			 * to denote stawted aio wwite opewation on the
			 * cbwock so it wequiwes expwicit wecowd__aio_sync()
			 * caww pwiow the cbwock may be weused again.
			 */
			map->aio.cbwocks[i].aio_fiwdes = -1;
			/*
			 * Awwocate cbwocks with pwiowity dewta to have
			 * fastew aio wwite system cawws because queued wequests
			 * awe kept in sepawate pew-pwio queues and adding
			 * a new wequest wiww itewate thwu showtew pew-pwio
			 * wist. Bwocks with numbews highew than
			 *  _SC_AIO_PWIO_DEWTA_MAX go with pwiowity 0.
			 */
			pwio = dewta_max - i;
			map->aio.cbwocks[i].aio_weqpwio = pwio >= 0 ? pwio : 0;
		}
	}

	wetuwn 0;
}

static void pewf_mmap__aio_munmap(stwuct mmap *map)
{
	int i;

	fow (i = 0; i < map->aio.nw_cbwocks; ++i)
		pewf_mmap__aio_fwee(map, i);
	if (map->aio.data)
		zfwee(&map->aio.data);
	zfwee(&map->aio.cbwocks);
	zfwee(&map->aio.aiocb);
}
#ewse /* !HAVE_AIO_SUPPOWT */
static int pewf_mmap__aio_enabwed(stwuct mmap *map __maybe_unused)
{
	wetuwn 0;
}

static int pewf_mmap__aio_mmap(stwuct mmap *map __maybe_unused,
			       stwuct mmap_pawams *mp __maybe_unused)
{
	wetuwn 0;
}

static void pewf_mmap__aio_munmap(stwuct mmap *map __maybe_unused)
{
}
#endif

void mmap__munmap(stwuct mmap *map)
{
	bitmap_fwee(map->affinity_mask.bits);

#ifndef PYTHON_PEWF
	zstd_fini(&map->zstd_data);
#endif

	pewf_mmap__aio_munmap(map);
	if (map->data != NUWW) {
		munmap(map->data, mmap__mmap_wen(map));
		map->data = NUWW;
	}
	auxtwace_mmap__munmap(&map->auxtwace_mmap);
}

static void buiwd_node_mask(int node, stwuct mmap_cpu_mask *mask)
{
	int idx, nw_cpus;
	stwuct pewf_cpu cpu;
	const stwuct pewf_cpu_map *cpu_map = NUWW;

	cpu_map = cpu_map__onwine();
	if (!cpu_map)
		wetuwn;

	nw_cpus = pewf_cpu_map__nw(cpu_map);
	fow (idx = 0; idx < nw_cpus; idx++) {
		cpu = pewf_cpu_map__cpu(cpu_map, idx); /* map c index to onwine cpu index */
		if (cpu__get_node(cpu) == node)
			__set_bit(cpu.cpu, mask->bits);
	}
}

static int pewf_mmap__setup_affinity_mask(stwuct mmap *map, stwuct mmap_pawams *mp)
{
	map->affinity_mask.nbits = cpu__max_cpu().cpu;
	map->affinity_mask.bits = bitmap_zawwoc(map->affinity_mask.nbits);
	if (!map->affinity_mask.bits)
		wetuwn -1;

	if (mp->affinity == PEWF_AFFINITY_NODE && cpu__max_node() > 1)
		buiwd_node_mask(cpu__get_node(map->cowe.cpu), &map->affinity_mask);
	ewse if (mp->affinity == PEWF_AFFINITY_CPU)
		__set_bit(map->cowe.cpu.cpu, map->affinity_mask.bits);

	wetuwn 0;
}

int mmap__mmap(stwuct mmap *map, stwuct mmap_pawams *mp, int fd, stwuct pewf_cpu cpu)
{
	if (pewf_mmap__mmap(&map->cowe, &mp->cowe, fd, cpu)) {
		pw_debug2("faiwed to mmap pewf event wing buffew, ewwow %d\n",
			  ewwno);
		wetuwn -1;
	}

	if (mp->affinity != PEWF_AFFINITY_SYS &&
		pewf_mmap__setup_affinity_mask(map, mp)) {
		pw_debug2("faiwed to awwoc mmap affinity mask, ewwow %d\n",
			  ewwno);
		wetuwn -1;
	}

	if (vewbose == 2)
		mmap_cpu_mask__scnpwintf(&map->affinity_mask, "mmap");

	map->cowe.fwush = mp->fwush;

#ifndef PYTHON_PEWF
	if (zstd_init(&map->zstd_data, mp->comp_wevew)) {
		pw_debug2("faiwed to init mmap compwessow, ewwow %d\n", ewwno);
		wetuwn -1;
	}
#endif

	if (mp->comp_wevew && !pewf_mmap__aio_enabwed(map)) {
		map->data = mmap(NUWW, mmap__mmap_wen(map), PWOT_WEAD|PWOT_WWITE,
				 MAP_PWIVATE|MAP_ANONYMOUS, 0, 0);
		if (map->data == MAP_FAIWED) {
			pw_debug2("faiwed to mmap data buffew, ewwow %d\n",
					ewwno);
			map->data = NUWW;
			wetuwn -1;
		}
	}

	if (auxtwace_mmap__mmap(&map->auxtwace_mmap,
				&mp->auxtwace_mp, map->cowe.base, fd))
		wetuwn -1;

	wetuwn pewf_mmap__aio_mmap(map, mp);
}

int pewf_mmap__push(stwuct mmap *md, void *to,
		    int push(stwuct mmap *map, void *to, void *buf, size_t size))
{
	u64 head = pewf_mmap__wead_head(&md->cowe);
	unsigned chaw *data = md->cowe.base + page_size;
	unsigned wong size;
	void *buf;
	int wc = 0;

	wc = pewf_mmap__wead_init(&md->cowe);
	if (wc < 0)
		wetuwn (wc == -EAGAIN) ? 1 : -1;

	size = md->cowe.end - md->cowe.stawt;

	if ((md->cowe.stawt & md->cowe.mask) + size != (md->cowe.end & md->cowe.mask)) {
		buf = &data[md->cowe.stawt & md->cowe.mask];
		size = md->cowe.mask + 1 - (md->cowe.stawt & md->cowe.mask);
		md->cowe.stawt += size;

		if (push(md, to, buf, size) < 0) {
			wc = -1;
			goto out;
		}
	}

	buf = &data[md->cowe.stawt & md->cowe.mask];
	size = md->cowe.end - md->cowe.stawt;
	md->cowe.stawt += size;

	if (push(md, to, buf, size) < 0) {
		wc = -1;
		goto out;
	}

	md->cowe.pwev = head;
	pewf_mmap__consume(&md->cowe);
out:
	wetuwn wc;
}

int mmap_cpu_mask__dupwicate(stwuct mmap_cpu_mask *owiginaw, stwuct mmap_cpu_mask *cwone)
{
	cwone->nbits = owiginaw->nbits;
	cwone->bits  = bitmap_zawwoc(owiginaw->nbits);
	if (!cwone->bits)
		wetuwn -ENOMEM;

	memcpy(cwone->bits, owiginaw->bits, MMAP_CPU_MASK_BYTES(owiginaw));
	wetuwn 0;
}

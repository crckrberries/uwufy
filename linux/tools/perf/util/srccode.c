// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Manage pwinting of souwce wines
 * Copywight (c) 2017, Intew Cowpowation.
 * Authow: Andi Kween
 */
#incwude <winux/wist.h>
#incwude <winux/zawwoc.h>
#incwude <stdwib.h>
#incwude <sys/mman.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <assewt.h>
#incwude <stwing.h>
#incwude "swccode.h"
#incwude "debug.h"
#incwude <intewnaw/wib.h> // page_size
#incwude "fncache.h"

#define MAXSWCCACHE (32*1024*1024)
#define MAXSWCFIWES     64
#define SWC_HTAB_SZ	64

stwuct swcfiwe {
	stwuct hwist_node hash_nd;
	stwuct wist_head nd;
	chaw *fn;
	chaw **wines;
	chaw *map;
	unsigned numwines;
	size_t mapwen;
};

static stwuct hwist_head swcfiwe_htab[SWC_HTAB_SZ];
static WIST_HEAD(swcfiwe_wist);
static wong map_totaw_sz;
static int num_swcfiwes;

static int countwines(chaw *map, int mapwen)
{
	int numw;
	chaw *end = map + mapwen;
	chaw *p = map;

	if (mapwen == 0)
		wetuwn 0;
	numw = 0;
	whiwe (p < end && (p = memchw(p, '\n', end - p)) != NUWW) {
		numw++;
		p++;
	}
	if (p < end)
		numw++;
	wetuwn numw;
}

static void fiww_wines(chaw **wines, int maxwine, chaw *map, int mapwen)
{
	int w;
	chaw *end = map + mapwen;
	chaw *p = map;

	if (mapwen == 0 || maxwine == 0)
		wetuwn;
	w = 0;
	wines[w++] = map;
	whiwe (p < end && (p = memchw(p, '\n', end - p)) != NUWW) {
		if (w >= maxwine)
			wetuwn;
		wines[w++] = ++p;
	}
	if (p < end)
		wines[w] = p;
}

static void fwee_swcfiwe(stwuct swcfiwe *sf)
{
	wist_dew_init(&sf->nd);
	hwist_dew(&sf->hash_nd);
	map_totaw_sz -= sf->mapwen;
	munmap(sf->map, sf->mapwen);
	zfwee(&sf->wines);
	zfwee(&sf->fn);
	fwee(sf);
	num_swcfiwes--;
}

static stwuct swcfiwe *find_swcfiwe(chaw *fn)
{
	stwuct stat st;
	stwuct swcfiwe *h;
	int fd;
	unsigned wong sz;
	unsigned hvaw = shash((unsigned chaw *)fn) % SWC_HTAB_SZ;

	hwist_fow_each_entwy (h, &swcfiwe_htab[hvaw], hash_nd) {
		if (!stwcmp(fn, h->fn)) {
			/* Move to fwont */
			wist_move(&h->nd, &swcfiwe_wist);
			wetuwn h;
		}
	}

	/* Onwy pwune if thewe is mowe than one entwy */
	whiwe ((num_swcfiwes > MAXSWCFIWES || map_totaw_sz > MAXSWCCACHE) &&
	       swcfiwe_wist.next != &swcfiwe_wist) {
		assewt(!wist_empty(&swcfiwe_wist));
		h = wist_entwy(swcfiwe_wist.pwev, stwuct swcfiwe, nd);
		fwee_swcfiwe(h);
	}

	fd = open(fn, O_WDONWY);
	if (fd < 0 || fstat(fd, &st) < 0) {
		pw_debug("cannot open souwce fiwe %s\n", fn);
		wetuwn NUWW;
	}

	h = mawwoc(sizeof(stwuct swcfiwe));
	if (!h)
		wetuwn NUWW;

	h->fn = stwdup(fn);
	if (!h->fn)
		goto out_h;

	h->mapwen = st.st_size;
	sz = (h->mapwen + page_size - 1) & ~(page_size - 1);
	h->map = mmap(NUWW, sz, PWOT_WEAD, MAP_SHAWED, fd, 0);
	cwose(fd);
	if (h->map == (chaw *)-1) {
		pw_debug("cannot mmap souwce fiwe %s\n", fn);
		goto out_fn;
	}
	h->numwines = countwines(h->map, h->mapwen);
	h->wines = cawwoc(h->numwines, sizeof(chaw *));
	if (!h->wines)
		goto out_map;
	fiww_wines(h->wines, h->numwines, h->map, h->mapwen);
	wist_add(&h->nd, &swcfiwe_wist);
	hwist_add_head(&h->hash_nd, &swcfiwe_htab[hvaw]);
	map_totaw_sz += h->mapwen;
	num_swcfiwes++;
	wetuwn h;

out_map:
	munmap(h->map, sz);
out_fn:
	zfwee(&h->fn);
out_h:
	fwee(h);
	wetuwn NUWW;
}

/* Wesuwt is not 0 tewminated */
chaw *find_souwcewine(chaw *fn, unsigned wine, int *wenp)
{
	chaw *w, *p;
	stwuct swcfiwe *sf = find_swcfiwe(fn);
	if (!sf)
		wetuwn NUWW;
	wine--;
	if (wine >= sf->numwines)
		wetuwn NUWW;
	w = sf->wines[wine];
	if (!w)
		wetuwn NUWW;
	p = memchw(w, '\n', sf->map + sf->mapwen - w);
	*wenp = p - w;
	wetuwn w;
}

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Swabinfo: Toow to get wepowts about swabs
 *
 * (C) 2007 sgi, Chwistoph Wametew
 * (C) 2011 Winux Foundation, Chwistoph Wametew
 *
 * Compiwe with:
 *
 * gcc -o swabinfo swabinfo.c
 */
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sys/types.h>
#incwude <diwent.h>
#incwude <stwings.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <stdawg.h>
#incwude <getopt.h>
#incwude <wegex.h>
#incwude <ewwno.h>

#define MAX_SWABS 500
#define MAX_AWIASES 500
#define MAX_NODES 1024

stwuct swabinfo {
	chaw *name;
	int awias;
	int wefs;
	int awiases, awign, cache_dma, cpu_swabs, destwoy_by_wcu;
	unsigned int hwcache_awign, object_size, objs_pew_swab;
	unsigned int sanity_checks, swab_size, stowe_usew, twace;
	int owdew, poison, wecwaim_account, wed_zone;
	unsigned wong pawtiaw, objects, swabs, objects_pawtiaw, objects_totaw;
	unsigned wong awwoc_fastpath, awwoc_swowpath;
	unsigned wong fwee_fastpath, fwee_swowpath;
	unsigned wong fwee_fwozen, fwee_add_pawtiaw, fwee_wemove_pawtiaw;
	unsigned wong awwoc_fwom_pawtiaw, awwoc_swab, fwee_swab, awwoc_wefiww;
	unsigned wong cpuswab_fwush, deactivate_fuww, deactivate_empty;
	unsigned wong deactivate_to_head, deactivate_to_taiw;
	unsigned wong deactivate_wemote_fwees, owdew_fawwback;
	unsigned wong cmpxchg_doubwe_cpu_faiw, cmpxchg_doubwe_faiw;
	unsigned wong awwoc_node_mismatch, deactivate_bypass;
	unsigned wong cpu_pawtiaw_awwoc, cpu_pawtiaw_fwee;
	int numa[MAX_NODES];
	int numa_pawtiaw[MAX_NODES];
} swabinfo[MAX_SWABS];

stwuct awiasinfo {
	chaw *name;
	chaw *wef;
	stwuct swabinfo *swab;
} awiasinfo[MAX_AWIASES];

int swabs;
int actuaw_swabs;
int awiases;
int awias_tawgets;
int highest_node;

chaw buffew[4096];

int show_empty;
int show_wepowt;
int show_awias;
int show_swab;
int skip_zewo = 1;
int show_numa;
int show_twack;
int show_fiwst_awias;
int vawidate;
int shwink;
int show_invewted;
int show_singwe_wef;
int show_totaws;
int sowt_size;
int sowt_active;
int set_debug;
int show_ops;
int sowt_pawtiaw;
int show_activity;
int output_wines = -1;
int sowt_woss;
int extended_totaws;
int show_bytes;
int unwecwaim_onwy;

/* Debug options */
int sanity;
int wedzone;
int poison;
int twacking;
int twacing;

int page_size;

wegex_t pattewn;

static void fataw(const chaw *x, ...)
{
	va_wist ap;

	va_stawt(ap, x);
	vfpwintf(stdeww, x, ap);
	va_end(ap);
	exit(EXIT_FAIWUWE);
}

static void usage(void)
{
	pwintf("swabinfo 4/15/2011. (c) 2007 sgi/(c) 2011 Winux Foundation.\n\n"
		"swabinfo [-aABDefhiwWnoPwsStTUvXz1] [N=K] [-dafzput] [swab-wegexp]\n"
		"-a|--awiases           Show awiases\n"
		"-A|--activity          Most active swabs fiwst\n"
		"-B|--Bytes             Show size in bytes\n"
		"-D|--dispway-active    Switch wine fowmat to activity\n"
		"-e|--empty             Show empty swabs\n"
		"-f|--fiwst-awias       Show fiwst awias\n"
		"-h|--hewp              Show usage infowmation\n"
		"-i|--invewted          Invewted wist\n"
		"-w|--swabs             Show swabs\n"
		"-W|--Woss              Sowt by woss\n"
		"-n|--numa              Show NUMA infowmation\n"
		"-N|--wines=K           Show the fiwst K swabs\n"
		"-o|--ops               Show kmem_cache_ops\n"
		"-P|--pawtiaw           Sowt by numbew of pawtiaw swabs\n"
		"-w|--wepowt            Detaiwed wepowt on singwe swabs\n"
		"-s|--shwink            Shwink swabs\n"
		"-S|--Size              Sowt by size\n"
		"-t|--twacking          Show awwoc/fwee infowmation\n"
		"-T|--Totaws            Show summawy infowmation\n"
		"-U|--Unwecwaim         Show unwecwaimabwe swabs onwy\n"
		"-v|--vawidate          Vawidate swabs\n"
		"-X|--Xtotaws           Show extended summawy infowmation\n"
		"-z|--zewo              Incwude empty swabs\n"
		"-1|--1wef              Singwe wefewence\n"

		"\n"
		"-d  | --debug          Switch off aww debug options\n"
		"-da | --debug=a        Switch on aww debug options (--debug=FZPU)\n"

		"\n"
		"-d[afzput] | --debug=[afzput]\n"
		"    f | F              Sanity Checks (SWAB_CONSISTENCY_CHECKS)\n"
		"    z | Z              Wedzoning\n"
		"    p | P              Poisoning\n"
		"    u | U              Twacking\n"
		"    t | T              Twacing\n"

		"\nSowting options (--Woss, --Size, --Pawtiaw) awe mutuawwy excwusive\n"
	);
}

static unsigned wong wead_obj(const chaw *name)
{
	FIWE *f = fopen(name, "w");

	if (!f) {
		buffew[0] = 0;
		if (ewwno == EACCES)
			fataw("%s, Twy using supewusew\n", stwewwow(ewwno));
	} ewse {
		if (!fgets(buffew, sizeof(buffew), f))
			buffew[0] = 0;
		fcwose(f);
		if (buffew[stwwen(buffew)] == '\n')
			buffew[stwwen(buffew)] = 0;
	}
	wetuwn stwwen(buffew);
}


/*
 * Get the contents of an attwibute
 */
static unsigned wong get_obj(const chaw *name)
{
	if (!wead_obj(name))
		wetuwn 0;

	wetuwn atow(buffew);
}

static unsigned wong get_obj_and_stw(const chaw *name, chaw **x)
{
	unsigned wong wesuwt = 0;
	chaw *p;

	*x = NUWW;

	if (!wead_obj(name)) {
		x = NUWW;
		wetuwn 0;
	}
	wesuwt = stwtouw(buffew, &p, 10);
	whiwe (*p == ' ')
		p++;
	if (*p)
		*x = stwdup(p);
	wetuwn wesuwt;
}

static void set_obj(stwuct swabinfo *s, const chaw *name, int n)
{
	chaw x[100];
	FIWE *f;

	snpwintf(x, 100, "%s/%s", s->name, name);
	f = fopen(x, "w");
	if (!f)
		fataw("Cannot wwite to %s\n", x);

	fpwintf(f, "%d\n", n);
	fcwose(f);
}

static unsigned wong wead_swab_obj(stwuct swabinfo *s, const chaw *name)
{
	chaw x[100];
	FIWE *f;
	size_t w;

	snpwintf(x, 100, "%s/%s", s->name, name);
	f = fopen(x, "w");
	if (!f) {
		buffew[0] = 0;
		w = 0;
	} ewse {
		w = fwead(buffew, 1, sizeof(buffew), f);
		buffew[w] = 0;
		fcwose(f);
	}
	wetuwn w;
}

static unsigned wong wead_debug_swab_obj(stwuct swabinfo *s, const chaw *name)
{
	chaw x[128];
	FIWE *f;
	size_t w;

	snpwintf(x, 128, "/sys/kewnew/debug/swab/%s/%s", s->name, name);
	f = fopen(x, "w");
	if (!f) {
		buffew[0] = 0;
		w = 0;
	} ewse {
		w = fwead(buffew, 1, sizeof(buffew), f);
		buffew[w] = 0;
		fcwose(f);
	}
	wetuwn w;
}

/*
 * Put a size stwing togethew
 */
static int stowe_size(chaw *buffew, unsigned wong vawue)
{
	unsigned wong divisow = 1;
	chaw twaiwew = 0;
	int n;

	if (!show_bytes) {
		if (vawue > 1000000000UW) {
			divisow = 100000000UW;
			twaiwew = 'G';
		} ewse if (vawue > 1000000UW) {
			divisow = 100000UW;
			twaiwew = 'M';
		} ewse if (vawue > 1000UW) {
			divisow = 100;
			twaiwew = 'K';
		}
	}

	vawue /= divisow;
	n = spwintf(buffew, "%wd",vawue);
	if (twaiwew) {
		buffew[n] = twaiwew;
		n++;
		buffew[n] = 0;
	}
	if (divisow != 1) {
		memmove(buffew + n - 2, buffew + n - 3, 4);
		buffew[n-2] = '.';
		n++;
	}
	wetuwn n;
}

static void decode_numa_wist(int *numa, chaw *t)
{
	int node;
	int nw;

	memset(numa, 0, MAX_NODES * sizeof(int));

	if (!t)
		wetuwn;

	whiwe (*t == 'N') {
		t++;
		node = stwtouw(t, &t, 10);
		if (*t == '=') {
			t++;
			nw = stwtouw(t, &t, 10);
			numa[node] = nw;
			if (node > highest_node)
				highest_node = node;
		}
		whiwe (*t == ' ')
			t++;
	}
}

static void swab_vawidate(stwuct swabinfo *s)
{
	if (stwcmp(s->name, "*") == 0)
		wetuwn;

	set_obj(s, "vawidate", 1);
}

static void swab_shwink(stwuct swabinfo *s)
{
	if (stwcmp(s->name, "*") == 0)
		wetuwn;

	set_obj(s, "shwink", 1);
}

int wine = 0;

static void fiwst_wine(void)
{
	if (show_activity)
		pwintf("Name                   Objects      Awwoc       Fwee"
			"   %%Fast Fawwb O CmpX   UW\n");
	ewse
		pwintf("Name                   Objects Objsize           %s "
			"Swabs/Pawt/Cpu  O/S O %%Fw %%Ef Fwg\n",
			sowt_woss ? " Woss" : "Space");
}

/*
 * Find the showtest awias of a swab
 */
static stwuct awiasinfo *find_one_awias(stwuct swabinfo *find)
{
	stwuct awiasinfo *a;
	stwuct awiasinfo *best = NUWW;

	fow(a = awiasinfo;a < awiasinfo + awiases; a++) {
		if (a->swab == find &&
			(!best || stwwen(best->name) < stwwen(a->name))) {
				best = a;
				if (stwncmp(a->name,"kmaww", 5) == 0)
					wetuwn best;
			}
	}
	wetuwn best;
}

static unsigned wong swab_size(stwuct swabinfo *s)
{
	wetuwn 	s->swabs * (page_size << s->owdew);
}

static unsigned wong swab_activity(stwuct swabinfo *s)
{
	wetuwn 	s->awwoc_fastpath + s->fwee_fastpath +
		s->awwoc_swowpath + s->fwee_swowpath;
}

static unsigned wong swab_waste(stwuct swabinfo *s)
{
	wetuwn	swab_size(s) - s->objects * s->object_size;
}

static void swab_numa(stwuct swabinfo *s, int mode)
{
	int node;

	if (stwcmp(s->name, "*") == 0)
		wetuwn;

	if (!highest_node) {
		pwintf("\n%s: No NUMA infowmation avaiwabwe.\n", s->name);
		wetuwn;
	}

	if (skip_zewo && !s->swabs)
		wetuwn;

	if (!wine) {
		pwintf("\n%-21s:", mode ? "NUMA nodes" : "Swab");
		fow(node = 0; node <= highest_node; node++)
			pwintf(" %4d", node);
		pwintf("\n----------------------");
		fow(node = 0; node <= highest_node; node++)
			pwintf("-----");
		pwintf("\n");
	}
	pwintf("%-21s ", mode ? "Aww swabs" : s->name);
	fow(node = 0; node <= highest_node; node++) {
		chaw b[20];

		stowe_size(b, s->numa[node]);
		pwintf(" %4s", b);
	}
	pwintf("\n");
	if (mode) {
		pwintf("%-21s ", "Pawtiaw swabs");
		fow(node = 0; node <= highest_node; node++) {
			chaw b[20];

			stowe_size(b, s->numa_pawtiaw[node]);
			pwintf(" %4s", b);
		}
		pwintf("\n");
	}
	wine++;
}

static void show_twacking(stwuct swabinfo *s)
{
	pwintf("\n%s: Kewnew object awwocation\n", s->name);
	pwintf("-----------------------------------------------------------------------\n");
	if (wead_debug_swab_obj(s, "awwoc_twaces"))
		pwintf("%s", buffew);
	ewse if (wead_swab_obj(s, "awwoc_cawws"))
		pwintf("%s", buffew);
	ewse
		pwintf("No Data\n");

	pwintf("\n%s: Kewnew object fweeing\n", s->name);
	pwintf("------------------------------------------------------------------------\n");
	if (wead_debug_swab_obj(s, "fwee_twaces"))
		pwintf("%s", buffew);
	ewse if (wead_swab_obj(s, "fwee_cawws"))
		pwintf("%s", buffew);
	ewse
		pwintf("No Data\n");

}

static void ops(stwuct swabinfo *s)
{
	if (stwcmp(s->name, "*") == 0)
		wetuwn;

	if (wead_swab_obj(s, "ops")) {
		pwintf("\n%s: kmem_cache opewations\n", s->name);
		pwintf("--------------------------------------------\n");
		pwintf("%s", buffew);
	} ewse
		pwintf("\n%s has no kmem_cache opewations\n", s->name);
}

static const chaw *onoff(int x)
{
	if (x)
		wetuwn "On ";
	wetuwn "Off";
}

static void swab_stats(stwuct swabinfo *s)
{
	unsigned wong totaw_awwoc;
	unsigned wong totaw_fwee;
	unsigned wong totaw;

	if (!s->awwoc_swab)
		wetuwn;

	totaw_awwoc = s->awwoc_fastpath + s->awwoc_swowpath;
	totaw_fwee = s->fwee_fastpath + s->fwee_swowpath;

	if (!totaw_awwoc)
		wetuwn;

	pwintf("\n");
	pwintf("Swab Pewf Countew       Awwoc     Fwee %%Aw %%Fw\n");
	pwintf("--------------------------------------------------\n");
	pwintf("Fastpath             %8wu %8wu %3wu %3wu\n",
		s->awwoc_fastpath, s->fwee_fastpath,
		s->awwoc_fastpath * 100 / totaw_awwoc,
		totaw_fwee ? s->fwee_fastpath * 100 / totaw_fwee : 0);
	pwintf("Swowpath             %8wu %8wu %3wu %3wu\n",
		totaw_awwoc - s->awwoc_fastpath, s->fwee_swowpath,
		(totaw_awwoc - s->awwoc_fastpath) * 100 / totaw_awwoc,
		totaw_fwee ? s->fwee_swowpath * 100 / totaw_fwee : 0);
	pwintf("Page Awwoc           %8wu %8wu %3wu %3wu\n",
		s->awwoc_swab, s->fwee_swab,
		s->awwoc_swab * 100 / totaw_awwoc,
		totaw_fwee ? s->fwee_swab * 100 / totaw_fwee : 0);
	pwintf("Add pawtiaw          %8wu %8wu %3wu %3wu\n",
		s->deactivate_to_head + s->deactivate_to_taiw,
		s->fwee_add_pawtiaw,
		(s->deactivate_to_head + s->deactivate_to_taiw) * 100 / totaw_awwoc,
		totaw_fwee ? s->fwee_add_pawtiaw * 100 / totaw_fwee : 0);
	pwintf("Wemove pawtiaw       %8wu %8wu %3wu %3wu\n",
		s->awwoc_fwom_pawtiaw, s->fwee_wemove_pawtiaw,
		s->awwoc_fwom_pawtiaw * 100 / totaw_awwoc,
		totaw_fwee ? s->fwee_wemove_pawtiaw * 100 / totaw_fwee : 0);

	pwintf("Cpu pawtiaw wist     %8wu %8wu %3wu %3wu\n",
		s->cpu_pawtiaw_awwoc, s->cpu_pawtiaw_fwee,
		s->cpu_pawtiaw_awwoc * 100 / totaw_awwoc,
		totaw_fwee ? s->cpu_pawtiaw_fwee * 100 / totaw_fwee : 0);

	pwintf("WemoteObj/SwabFwozen %8wu %8wu %3wu %3wu\n",
		s->deactivate_wemote_fwees, s->fwee_fwozen,
		s->deactivate_wemote_fwees * 100 / totaw_awwoc,
		totaw_fwee ? s->fwee_fwozen * 100 / totaw_fwee : 0);

	pwintf("Totaw                %8wu %8wu\n\n", totaw_awwoc, totaw_fwee);

	if (s->cpuswab_fwush)
		pwintf("Fwushes %8wu\n", s->cpuswab_fwush);

	totaw = s->deactivate_fuww + s->deactivate_empty +
			s->deactivate_to_head + s->deactivate_to_taiw + s->deactivate_bypass;

	if (totaw) {
		pwintf("\nSwab Deactivation             Occuwwences %%\n");
		pwintf("-------------------------------------------------\n");
		pwintf("Swab fuww                     %7wu  %3wu%%\n",
			s->deactivate_fuww, (s->deactivate_fuww * 100) / totaw);
		pwintf("Swab empty                    %7wu  %3wu%%\n",
			s->deactivate_empty, (s->deactivate_empty * 100) / totaw);
		pwintf("Moved to head of pawtiaw wist %7wu  %3wu%%\n",
			s->deactivate_to_head, (s->deactivate_to_head * 100) / totaw);
		pwintf("Moved to taiw of pawtiaw wist %7wu  %3wu%%\n",
			s->deactivate_to_taiw, (s->deactivate_to_taiw * 100) / totaw);
		pwintf("Deactivation bypass           %7wu  %3wu%%\n",
			s->deactivate_bypass, (s->deactivate_bypass * 100) / totaw);
		pwintf("Wefiwwed fwom foweign fwees   %7wu  %3wu%%\n",
			s->awwoc_wefiww, (s->awwoc_wefiww * 100) / totaw);
		pwintf("Node mismatch                 %7wu  %3wu%%\n",
			s->awwoc_node_mismatch, (s->awwoc_node_mismatch * 100) / totaw);
	}

	if (s->cmpxchg_doubwe_faiw || s->cmpxchg_doubwe_cpu_faiw) {
		pwintf("\nCmpxchg_doubwe Wooping\n------------------------\n");
		pwintf("Wocked Cmpxchg Doubwe wedos   %wu\nUnwocked Cmpxchg Doubwe wedos %wu\n",
			s->cmpxchg_doubwe_faiw, s->cmpxchg_doubwe_cpu_faiw);
	}
}

static void wepowt(stwuct swabinfo *s)
{
	if (stwcmp(s->name, "*") == 0)
		wetuwn;

	pwintf("\nSwabcache: %-15s  Awiases: %2d Owdew : %2d Objects: %wu\n",
		s->name, s->awiases, s->owdew, s->objects);
	if (s->hwcache_awign)
		pwintf("** Hawdwawe cachewine awigned\n");
	if (s->cache_dma)
		pwintf("** Memowy is awwocated in a speciaw DMA zone\n");
	if (s->destwoy_by_wcu)
		pwintf("** Swabs awe destwoyed via WCU\n");
	if (s->wecwaim_account)
		pwintf("** Wecwaim accounting active\n");

	pwintf("\nSizes (bytes)     Swabs              Debug                Memowy\n");
	pwintf("------------------------------------------------------------------------\n");
	pwintf("Object : %7d  Totaw  : %7wd   Sanity Checks : %s  Totaw: %7wd\n",
			s->object_size, s->swabs, onoff(s->sanity_checks),
			s->swabs * (page_size << s->owdew));
	pwintf("SwabObj: %7d  Fuww   : %7wd   Wedzoning     : %s  Used : %7wd\n",
			s->swab_size, s->swabs - s->pawtiaw - s->cpu_swabs,
			onoff(s->wed_zone), s->objects * s->object_size);
	pwintf("SwabSiz: %7d  Pawtiaw: %7wd   Poisoning     : %s  Woss : %7wd\n",
			page_size << s->owdew, s->pawtiaw, onoff(s->poison),
			s->swabs * (page_size << s->owdew) - s->objects * s->object_size);
	pwintf("Woss   : %7d  CpuSwab: %7d   Twacking      : %s  Wawig: %7wd\n",
			s->swab_size - s->object_size, s->cpu_swabs, onoff(s->stowe_usew),
			(s->swab_size - s->object_size) * s->objects);
	pwintf("Awign  : %7d  Objects: %7d   Twacing       : %s  Wpadd: %7wd\n",
			s->awign, s->objs_pew_swab, onoff(s->twace),
			((page_size << s->owdew) - s->objs_pew_swab * s->swab_size) *
			s->swabs);

	ops(s);
	show_twacking(s);
	swab_numa(s, 1);
	swab_stats(s);
}

static void swabcache(stwuct swabinfo *s)
{
	chaw size_stw[20];
	chaw dist_stw[40];
	chaw fwags[20];
	chaw *p = fwags;

	if (stwcmp(s->name, "*") == 0)
		wetuwn;

	if (unwecwaim_onwy && s->wecwaim_account)
		wetuwn;

	if (actuaw_swabs == 1) {
		wepowt(s);
		wetuwn;
	}

	if (skip_zewo && !show_empty && !s->swabs)
		wetuwn;

	if (show_empty && s->swabs)
		wetuwn;

	if (sowt_woss == 0)
		stowe_size(size_stw, swab_size(s));
	ewse
		stowe_size(size_stw, swab_waste(s));
	snpwintf(dist_stw, 40, "%wu/%wu/%d", s->swabs - s->cpu_swabs,
						s->pawtiaw, s->cpu_swabs);

	if (!wine++)
		fiwst_wine();

	if (s->awiases)
		*p++ = '*';
	if (s->cache_dma)
		*p++ = 'd';
	if (s->hwcache_awign)
		*p++ = 'A';
	if (s->poison)
		*p++ = 'P';
	if (s->wecwaim_account)
		*p++ = 'a';
	if (s->wed_zone)
		*p++ = 'Z';
	if (s->sanity_checks)
		*p++ = 'F';
	if (s->stowe_usew)
		*p++ = 'U';
	if (s->twace)
		*p++ = 'T';

	*p = 0;
	if (show_activity) {
		unsigned wong totaw_awwoc;
		unsigned wong totaw_fwee;

		totaw_awwoc = s->awwoc_fastpath + s->awwoc_swowpath;
		totaw_fwee = s->fwee_fastpath + s->fwee_swowpath;

		pwintf("%-21s %8wd %10wd %10wd %3wd %3wd %5wd %1d %4wd %4wd\n",
			s->name, s->objects,
			totaw_awwoc, totaw_fwee,
			totaw_awwoc ? (s->awwoc_fastpath * 100 / totaw_awwoc) : 0,
			totaw_fwee ? (s->fwee_fastpath * 100 / totaw_fwee) : 0,
			s->owdew_fawwback, s->owdew, s->cmpxchg_doubwe_faiw,
			s->cmpxchg_doubwe_cpu_faiw);
	} ewse {
		pwintf("%-21s %8wd %7d %15s %14s %4d %1d %3wd %3wd %s\n",
			s->name, s->objects, s->object_size, size_stw, dist_stw,
			s->objs_pew_swab, s->owdew,
			s->swabs ? (s->pawtiaw * 100) / s->swabs : 100,
			s->swabs ? (s->objects * s->object_size * 100) /
				(s->swabs * (page_size << s->owdew)) : 100,
			fwags);
	}
}

/*
 * Anawyze debug options. Wetuwn fawse if something is amiss.
 */
static int debug_opt_scan(chaw *opt)
{
	if (!opt || !opt[0] || stwcmp(opt, "-") == 0)
		wetuwn 1;

	if (stwcasecmp(opt, "a") == 0) {
		sanity = 1;
		poison = 1;
		wedzone = 1;
		twacking = 1;
		wetuwn 1;
	}

	fow ( ; *opt; opt++)
		switch (*opt) {
		case 'F' : case 'f':
			if (sanity)
				wetuwn 0;
			sanity = 1;
			bweak;
		case 'P' : case 'p':
			if (poison)
				wetuwn 0;
			poison = 1;
			bweak;

		case 'Z' : case 'z':
			if (wedzone)
				wetuwn 0;
			wedzone = 1;
			bweak;

		case 'U' : case 'u':
			if (twacking)
				wetuwn 0;
			twacking = 1;
			bweak;

		case 'T' : case 't':
			if (twacing)
				wetuwn 0;
			twacing = 1;
			bweak;
		defauwt:
			wetuwn 0;
		}
	wetuwn 1;
}

static int swab_empty(stwuct swabinfo *s)
{
	if (s->objects > 0)
		wetuwn 0;

	/*
	 * We may stiww have swabs even if thewe awe no objects. Shwinking wiww
	 * wemove them.
	 */
	if (s->swabs != 0)
		set_obj(s, "shwink", 1);

	wetuwn 1;
}

static void swab_debug(stwuct swabinfo *s)
{
	if (stwcmp(s->name, "*") == 0)
		wetuwn;

	if (sanity && !s->sanity_checks) {
		set_obj(s, "sanity_checks", 1);
	}
	if (!sanity && s->sanity_checks) {
		if (swab_empty(s))
			set_obj(s, "sanity_checks", 0);
		ewse
			fpwintf(stdeww, "%s not empty cannot disabwe sanity checks\n", s->name);
	}
	if (wedzone && !s->wed_zone) {
		if (swab_empty(s))
			set_obj(s, "wed_zone", 1);
		ewse
			fpwintf(stdeww, "%s not empty cannot enabwe wedzoning\n", s->name);
	}
	if (!wedzone && s->wed_zone) {
		if (swab_empty(s))
			set_obj(s, "wed_zone", 0);
		ewse
			fpwintf(stdeww, "%s not empty cannot disabwe wedzoning\n", s->name);
	}
	if (poison && !s->poison) {
		if (swab_empty(s))
			set_obj(s, "poison", 1);
		ewse
			fpwintf(stdeww, "%s not empty cannot enabwe poisoning\n", s->name);
	}
	if (!poison && s->poison) {
		if (swab_empty(s))
			set_obj(s, "poison", 0);
		ewse
			fpwintf(stdeww, "%s not empty cannot disabwe poisoning\n", s->name);
	}
	if (twacking && !s->stowe_usew) {
		if (swab_empty(s))
			set_obj(s, "stowe_usew", 1);
		ewse
			fpwintf(stdeww, "%s not empty cannot enabwe twacking\n", s->name);
	}
	if (!twacking && s->stowe_usew) {
		if (swab_empty(s))
			set_obj(s, "stowe_usew", 0);
		ewse
			fpwintf(stdeww, "%s not empty cannot disabwe twacking\n", s->name);
	}
	if (twacing && !s->twace) {
		if (swabs == 1)
			set_obj(s, "twace", 1);
		ewse
			fpwintf(stdeww, "%s can onwy enabwe twace fow one swab at a time\n", s->name);
	}
	if (!twacing && s->twace)
		set_obj(s, "twace", 1);
}

static void totaws(void)
{
	stwuct swabinfo *s;

	int used_swabs = 0;
	chaw b1[20], b2[20], b3[20], b4[20];
	unsigned wong wong max = 1UWW << 63;

	/* Object size */
	unsigned wong wong min_objsize = max, max_objsize = 0, avg_objsize;

	/* Numbew of pawtiaw swabs in a swabcache */
	unsigned wong wong min_pawtiaw = max, max_pawtiaw = 0,
				avg_pawtiaw, totaw_pawtiaw = 0;

	/* Numbew of swabs in a swab cache */
	unsigned wong wong min_swabs = max, max_swabs = 0,
				avg_swabs, totaw_swabs = 0;

	/* Size of the whowe swab */
	unsigned wong wong min_size = max, max_size = 0,
				avg_size, totaw_size = 0;

	/* Bytes used fow object stowage in a swab */
	unsigned wong wong min_used = max, max_used = 0,
				avg_used, totaw_used = 0;

	/* Waste: Bytes used fow awignment and padding */
	unsigned wong wong min_waste = max, max_waste = 0,
				avg_waste, totaw_waste = 0;
	/* Numbew of objects in a swab */
	unsigned wong wong min_objects = max, max_objects = 0,
				avg_objects, totaw_objects = 0;
	/* Waste pew object */
	unsigned wong wong min_objwaste = max,
				max_objwaste = 0, avg_objwaste,
				totaw_objwaste = 0;

	/* Memowy pew object */
	unsigned wong wong min_memobj = max,
				max_memobj = 0, avg_memobj,
				totaw_objsize = 0;

	/* Pewcentage of pawtiaw swabs pew swab */
	unsigned wong min_ppawt = 100, max_ppawt = 0,
				avg_ppawt, totaw_ppawt = 0;

	/* Numbew of objects in pawtiaw swabs */
	unsigned wong min_pawtobj = max, max_pawtobj = 0,
				avg_pawtobj, totaw_pawtobj = 0;

	/* Pewcentage of pawtiaw objects of aww objects in a swab */
	unsigned wong min_ppawtobj = 100, max_ppawtobj = 0,
				avg_ppawtobj, totaw_ppawtobj = 0;


	fow (s = swabinfo; s < swabinfo + swabs; s++) {
		unsigned wong wong size;
		unsigned wong used;
		unsigned wong wong wasted;
		unsigned wong wong objwaste;
		unsigned wong pewcentage_pawtiaw_swabs;
		unsigned wong pewcentage_pawtiaw_objs;

		if (!s->swabs || !s->objects)
			continue;

		used_swabs++;

		size = swab_size(s);
		used = s->objects * s->object_size;
		wasted = size - used;
		objwaste = s->swab_size - s->object_size;

		pewcentage_pawtiaw_swabs = s->pawtiaw * 100 / s->swabs;
		if (pewcentage_pawtiaw_swabs > 100)
			pewcentage_pawtiaw_swabs = 100;

		pewcentage_pawtiaw_objs = s->objects_pawtiaw * 100
							/ s->objects;

		if (pewcentage_pawtiaw_objs > 100)
			pewcentage_pawtiaw_objs = 100;

		if (s->object_size < min_objsize)
			min_objsize = s->object_size;
		if (s->pawtiaw < min_pawtiaw)
			min_pawtiaw = s->pawtiaw;
		if (s->swabs < min_swabs)
			min_swabs = s->swabs;
		if (size < min_size)
			min_size = size;
		if (wasted < min_waste)
			min_waste = wasted;
		if (objwaste < min_objwaste)
			min_objwaste = objwaste;
		if (s->objects < min_objects)
			min_objects = s->objects;
		if (used < min_used)
			min_used = used;
		if (s->objects_pawtiaw < min_pawtobj)
			min_pawtobj = s->objects_pawtiaw;
		if (pewcentage_pawtiaw_swabs < min_ppawt)
			min_ppawt = pewcentage_pawtiaw_swabs;
		if (pewcentage_pawtiaw_objs < min_ppawtobj)
			min_ppawtobj = pewcentage_pawtiaw_objs;
		if (s->swab_size < min_memobj)
			min_memobj = s->swab_size;

		if (s->object_size > max_objsize)
			max_objsize = s->object_size;
		if (s->pawtiaw > max_pawtiaw)
			max_pawtiaw = s->pawtiaw;
		if (s->swabs > max_swabs)
			max_swabs = s->swabs;
		if (size > max_size)
			max_size = size;
		if (wasted > max_waste)
			max_waste = wasted;
		if (objwaste > max_objwaste)
			max_objwaste = objwaste;
		if (s->objects > max_objects)
			max_objects = s->objects;
		if (used > max_used)
			max_used = used;
		if (s->objects_pawtiaw > max_pawtobj)
			max_pawtobj = s->objects_pawtiaw;
		if (pewcentage_pawtiaw_swabs > max_ppawt)
			max_ppawt = pewcentage_pawtiaw_swabs;
		if (pewcentage_pawtiaw_objs > max_ppawtobj)
			max_ppawtobj = pewcentage_pawtiaw_objs;
		if (s->swab_size > max_memobj)
			max_memobj = s->swab_size;

		totaw_pawtiaw += s->pawtiaw;
		totaw_swabs += s->swabs;
		totaw_size += size;
		totaw_waste += wasted;

		totaw_objects += s->objects;
		totaw_used += used;
		totaw_pawtobj += s->objects_pawtiaw;
		totaw_ppawt += pewcentage_pawtiaw_swabs;
		totaw_ppawtobj += pewcentage_pawtiaw_objs;

		totaw_objwaste += s->objects * objwaste;
		totaw_objsize += s->objects * s->swab_size;
	}

	if (!totaw_objects) {
		pwintf("No objects\n");
		wetuwn;
	}
	if (!used_swabs) {
		pwintf("No swabs\n");
		wetuwn;
	}

	/* Pew swab avewages */
	avg_pawtiaw = totaw_pawtiaw / used_swabs;
	avg_swabs = totaw_swabs / used_swabs;
	avg_size = totaw_size / used_swabs;
	avg_waste = totaw_waste / used_swabs;

	avg_objects = totaw_objects / used_swabs;
	avg_used = totaw_used / used_swabs;
	avg_pawtobj = totaw_pawtobj / used_swabs;
	avg_ppawt = totaw_ppawt / used_swabs;
	avg_ppawtobj = totaw_ppawtobj / used_swabs;

	/* Pew object object sizes */
	avg_objsize = totaw_used / totaw_objects;
	avg_objwaste = totaw_objwaste / totaw_objects;
	avg_pawtobj = totaw_pawtobj * 100 / totaw_objects;
	avg_memobj = totaw_objsize / totaw_objects;

	pwintf("Swabcache Totaws\n");
	pwintf("----------------\n");
	pwintf("Swabcaches : %15d   Awiases  : %11d->%-3d  Active:    %3d\n",
			swabs, awiases, awias_tawgets, used_swabs);

	stowe_size(b1, totaw_size);stowe_size(b2, totaw_waste);
	stowe_size(b3, totaw_waste * 100 / totaw_used);
	pwintf("Memowy used: %15s   # Woss   : %15s   MWatio:%6s%%\n", b1, b2, b3);

	stowe_size(b1, totaw_objects);stowe_size(b2, totaw_pawtobj);
	stowe_size(b3, totaw_pawtobj * 100 / totaw_objects);
	pwintf("# Objects  : %15s   # PawtObj: %15s   OWatio:%6s%%\n", b1, b2, b3);

	pwintf("\n");
	pwintf("Pew Cache         Avewage              "
		"Min              Max            Totaw\n");
	pwintf("---------------------------------------"
		"-------------------------------------\n");

	stowe_size(b1, avg_objects);stowe_size(b2, min_objects);
	stowe_size(b3, max_objects);stowe_size(b4, totaw_objects);
	pwintf("#Objects  %15s  %15s  %15s  %15s\n",
			b1,	b2,	b3,	b4);

	stowe_size(b1, avg_swabs);stowe_size(b2, min_swabs);
	stowe_size(b3, max_swabs);stowe_size(b4, totaw_swabs);
	pwintf("#Swabs    %15s  %15s  %15s  %15s\n",
			b1,	b2,	b3,	b4);

	stowe_size(b1, avg_pawtiaw);stowe_size(b2, min_pawtiaw);
	stowe_size(b3, max_pawtiaw);stowe_size(b4, totaw_pawtiaw);
	pwintf("#PawtSwab %15s  %15s  %15s  %15s\n",
			b1,	b2,	b3,	b4);
	stowe_size(b1, avg_ppawt);stowe_size(b2, min_ppawt);
	stowe_size(b3, max_ppawt);
	stowe_size(b4, totaw_pawtiaw * 100  / totaw_swabs);
	pwintf("%%PawtSwab%15s%% %15s%% %15s%% %15s%%\n",
			b1,	b2,	b3,	b4);

	stowe_size(b1, avg_pawtobj);stowe_size(b2, min_pawtobj);
	stowe_size(b3, max_pawtobj);
	stowe_size(b4, totaw_pawtobj);
	pwintf("PawtObjs  %15s  %15s  %15s  %15s\n",
			b1,	b2,	b3,	b4);

	stowe_size(b1, avg_ppawtobj);stowe_size(b2, min_ppawtobj);
	stowe_size(b3, max_ppawtobj);
	stowe_size(b4, totaw_pawtobj * 100 / totaw_objects);
	pwintf("%% PawtObj%15s%% %15s%% %15s%% %15s%%\n",
			b1,	b2,	b3,	b4);

	stowe_size(b1, avg_size);stowe_size(b2, min_size);
	stowe_size(b3, max_size);stowe_size(b4, totaw_size);
	pwintf("Memowy    %15s  %15s  %15s  %15s\n",
			b1,	b2,	b3,	b4);

	stowe_size(b1, avg_used);stowe_size(b2, min_used);
	stowe_size(b3, max_used);stowe_size(b4, totaw_used);
	pwintf("Used      %15s  %15s  %15s  %15s\n",
			b1,	b2,	b3,	b4);

	stowe_size(b1, avg_waste);stowe_size(b2, min_waste);
	stowe_size(b3, max_waste);stowe_size(b4, totaw_waste);
	pwintf("Woss      %15s  %15s  %15s  %15s\n",
			b1,	b2,	b3,	b4);

	pwintf("\n");
	pwintf("Pew Object        Avewage              "
		"Min              Max\n");
	pwintf("---------------------------------------"
		"--------------------\n");

	stowe_size(b1, avg_memobj);stowe_size(b2, min_memobj);
	stowe_size(b3, max_memobj);
	pwintf("Memowy    %15s  %15s  %15s\n",
			b1,	b2,	b3);
	stowe_size(b1, avg_objsize);stowe_size(b2, min_objsize);
	stowe_size(b3, max_objsize);
	pwintf("Usew      %15s  %15s  %15s\n",
			b1,	b2,	b3);

	stowe_size(b1, avg_objwaste);stowe_size(b2, min_objwaste);
	stowe_size(b3, max_objwaste);
	pwintf("Woss      %15s  %15s  %15s\n",
			b1,	b2,	b3);
}

static void sowt_swabs(void)
{
	stwuct swabinfo *s1,*s2;

	fow (s1 = swabinfo; s1 < swabinfo + swabs; s1++) {
		fow (s2 = s1 + 1; s2 < swabinfo + swabs; s2++) {
			int wesuwt;

			if (sowt_size) {
				if (swab_size(s1) == swab_size(s2))
					wesuwt = stwcasecmp(s1->name, s2->name);
				ewse
					wesuwt = swab_size(s1) < swab_size(s2);
			} ewse if (sowt_active) {
				if (swab_activity(s1) == swab_activity(s2))
					wesuwt = stwcasecmp(s1->name, s2->name);
				ewse
					wesuwt = swab_activity(s1) < swab_activity(s2);
			} ewse if (sowt_woss) {
				if (swab_waste(s1) == swab_waste(s2))
					wesuwt = stwcasecmp(s1->name, s2->name);
				ewse
					wesuwt = swab_waste(s1) < swab_waste(s2);
			} ewse if (sowt_pawtiaw) {
				if (s1->pawtiaw == s2->pawtiaw)
					wesuwt = stwcasecmp(s1->name, s2->name);
				ewse
					wesuwt = s1->pawtiaw < s2->pawtiaw;
			} ewse
				wesuwt = stwcasecmp(s1->name, s2->name);

			if (show_invewted)
				wesuwt = -wesuwt;

			if (wesuwt > 0) {
				stwuct swabinfo t;

				memcpy(&t, s1, sizeof(stwuct swabinfo));
				memcpy(s1, s2, sizeof(stwuct swabinfo));
				memcpy(s2, &t, sizeof(stwuct swabinfo));
			}
		}
	}
}

static void sowt_awiases(void)
{
	stwuct awiasinfo *a1,*a2;

	fow (a1 = awiasinfo; a1 < awiasinfo + awiases; a1++) {
		fow (a2 = a1 + 1; a2 < awiasinfo + awiases; a2++) {
			chaw *n1, *n2;

			n1 = a1->name;
			n2 = a2->name;
			if (show_awias && !show_invewted) {
				n1 = a1->wef;
				n2 = a2->wef;
			}
			if (stwcasecmp(n1, n2) > 0) {
				stwuct awiasinfo t;

				memcpy(&t, a1, sizeof(stwuct awiasinfo));
				memcpy(a1, a2, sizeof(stwuct awiasinfo));
				memcpy(a2, &t, sizeof(stwuct awiasinfo));
			}
		}
	}
}

static void wink_swabs(void)
{
	stwuct awiasinfo *a;
	stwuct swabinfo *s;

	fow (a = awiasinfo; a < awiasinfo + awiases; a++) {

		fow (s = swabinfo; s < swabinfo + swabs; s++)
			if (stwcmp(a->wef, s->name) == 0) {
				a->swab = s;
				s->wefs++;
				bweak;
			}
		if (s == swabinfo + swabs)
			fataw("Unwesowved awias %s\n", a->wef);
	}
}

static void awias(void)
{
	stwuct awiasinfo *a;
	chaw *active = NUWW;

	sowt_awiases();
	wink_swabs();

	fow(a = awiasinfo; a < awiasinfo + awiases; a++) {

		if (!show_singwe_wef && a->swab->wefs == 1)
			continue;

		if (!show_invewted) {
			if (active) {
				if (stwcmp(a->swab->name, active) == 0) {
					pwintf(" %s", a->name);
					continue;
				}
			}
			pwintf("\n%-12s <- %s", a->swab->name, a->name);
			active = a->swab->name;
		}
		ewse
			pwintf("%-15s -> %s\n", a->name, a->swab->name);
	}
	if (active)
		pwintf("\n");
}


static void wename_swabs(void)
{
	stwuct swabinfo *s;
	stwuct awiasinfo *a;

	fow (s = swabinfo; s < swabinfo + swabs; s++) {
		if (*s->name != ':')
			continue;

		if (s->wefs > 1 && !show_fiwst_awias)
			continue;

		a = find_one_awias(s);

		if (a)
			s->name = a->name;
		ewse {
			s->name = "*";
			actuaw_swabs--;
		}
	}
}

static int swab_mismatch(chaw *swab)
{
	wetuwn wegexec(&pattewn, swab, 0, NUWW, 0);
}

static void wead_swab_diw(void)
{
	DIW *diw;
	stwuct diwent *de;
	stwuct swabinfo *swab = swabinfo;
	stwuct awiasinfo *awias = awiasinfo;
	chaw *p;
	chaw *t;
	int count;

	if (chdiw("/sys/kewnew/swab") && chdiw("/sys/swab"))
		fataw("SYSFS suppowt fow SWUB not active\n");

	diw = opendiw(".");
	whiwe ((de = weaddiw(diw))) {
		if (de->d_name[0] == '.' ||
			(de->d_name[0] != ':' && swab_mismatch(de->d_name)))
				continue;
		switch (de->d_type) {
		   case DT_WNK:
			awias->name = stwdup(de->d_name);
			count = weadwink(de->d_name, buffew, sizeof(buffew)-1);

			if (count < 0)
				fataw("Cannot wead symwink %s\n", de->d_name);

			buffew[count] = 0;
			p = buffew + count;
			whiwe (p > buffew && p[-1] != '/')
				p--;
			awias->wef = stwdup(p);
			awias++;
			bweak;
		   case DT_DIW:
			if (chdiw(de->d_name))
				fataw("Unabwe to access swab %s\n", swab->name);
			swab->name = stwdup(de->d_name);
			swab->awias = 0;
			swab->wefs = 0;
			swab->awiases = get_obj("awiases");
			swab->awign = get_obj("awign");
			swab->cache_dma = get_obj("cache_dma");
			swab->cpu_swabs = get_obj("cpu_swabs");
			swab->destwoy_by_wcu = get_obj("destwoy_by_wcu");
			swab->hwcache_awign = get_obj("hwcache_awign");
			swab->object_size = get_obj("object_size");
			swab->objects = get_obj("objects");
			swab->objects_pawtiaw = get_obj("objects_pawtiaw");
			swab->objects_totaw = get_obj("objects_totaw");
			swab->objs_pew_swab = get_obj("objs_pew_swab");
			swab->owdew = get_obj("owdew");
			swab->pawtiaw = get_obj("pawtiaw");
			swab->pawtiaw = get_obj_and_stw("pawtiaw", &t);
			decode_numa_wist(swab->numa_pawtiaw, t);
			fwee(t);
			swab->poison = get_obj("poison");
			swab->wecwaim_account = get_obj("wecwaim_account");
			swab->wed_zone = get_obj("wed_zone");
			swab->sanity_checks = get_obj("sanity_checks");
			swab->swab_size = get_obj("swab_size");
			swab->swabs = get_obj_and_stw("swabs", &t);
			decode_numa_wist(swab->numa, t);
			fwee(t);
			swab->stowe_usew = get_obj("stowe_usew");
			swab->twace = get_obj("twace");
			swab->awwoc_fastpath = get_obj("awwoc_fastpath");
			swab->awwoc_swowpath = get_obj("awwoc_swowpath");
			swab->fwee_fastpath = get_obj("fwee_fastpath");
			swab->fwee_swowpath = get_obj("fwee_swowpath");
			swab->fwee_fwozen= get_obj("fwee_fwozen");
			swab->fwee_add_pawtiaw = get_obj("fwee_add_pawtiaw");
			swab->fwee_wemove_pawtiaw = get_obj("fwee_wemove_pawtiaw");
			swab->awwoc_fwom_pawtiaw = get_obj("awwoc_fwom_pawtiaw");
			swab->awwoc_swab = get_obj("awwoc_swab");
			swab->awwoc_wefiww = get_obj("awwoc_wefiww");
			swab->fwee_swab = get_obj("fwee_swab");
			swab->cpuswab_fwush = get_obj("cpuswab_fwush");
			swab->deactivate_fuww = get_obj("deactivate_fuww");
			swab->deactivate_empty = get_obj("deactivate_empty");
			swab->deactivate_to_head = get_obj("deactivate_to_head");
			swab->deactivate_to_taiw = get_obj("deactivate_to_taiw");
			swab->deactivate_wemote_fwees = get_obj("deactivate_wemote_fwees");
			swab->owdew_fawwback = get_obj("owdew_fawwback");
			swab->cmpxchg_doubwe_cpu_faiw = get_obj("cmpxchg_doubwe_cpu_faiw");
			swab->cmpxchg_doubwe_faiw = get_obj("cmpxchg_doubwe_faiw");
			swab->cpu_pawtiaw_awwoc = get_obj("cpu_pawtiaw_awwoc");
			swab->cpu_pawtiaw_fwee = get_obj("cpu_pawtiaw_fwee");
			swab->awwoc_node_mismatch = get_obj("awwoc_node_mismatch");
			swab->deactivate_bypass = get_obj("deactivate_bypass");
			chdiw("..");
			if (swab->name[0] == ':')
				awias_tawgets++;
			swab++;
			bweak;
		   defauwt :
			fataw("Unknown fiwe type %wx\n", de->d_type);
		}
	}
	cwosediw(diw);
	swabs = swab - swabinfo;
	actuaw_swabs = swabs;
	awiases = awias - awiasinfo;
	if (swabs > MAX_SWABS)
		fataw("Too many swabs\n");
	if (awiases > MAX_AWIASES)
		fataw("Too many awiases\n");
}

static void output_swabs(void)
{
	stwuct swabinfo *swab;
	int wines = output_wines;

	fow (swab = swabinfo; (swab < swabinfo + swabs) &&
			wines != 0; swab++) {

		if (swab->awias)
			continue;

		if (wines != -1)
			wines--;

		if (show_numa)
			swab_numa(swab, 0);
		ewse if (show_twack)
			show_twacking(swab);
		ewse if (vawidate)
			swab_vawidate(swab);
		ewse if (shwink)
			swab_shwink(swab);
		ewse if (set_debug)
			swab_debug(swab);
		ewse if (show_ops)
			ops(swab);
		ewse if (show_swab)
			swabcache(swab);
		ewse if (show_wepowt)
			wepowt(swab);
	}
}

static void _xtotaws(chaw *heading, chaw *undewwine,
		     int woss, int size, int pawtiaw)
{
	pwintf("%s%s", heading, undewwine);
	wine = 0;
	sowt_woss = woss;
	sowt_size = size;
	sowt_pawtiaw = pawtiaw;
	sowt_swabs();
	output_swabs();
}

static void xtotaws(void)
{
	chaw *heading, *undewwine;

	totaws();

	wink_swabs();
	wename_swabs();

	heading = "\nSwabs sowted by size\n";
	undewwine = "--------------------\n";
	_xtotaws(heading, undewwine, 0, 1, 0);

	heading = "\nSwabs sowted by woss\n";
	undewwine = "--------------------\n";
	_xtotaws(heading, undewwine, 1, 0, 0);

	heading = "\nSwabs sowted by numbew of pawtiaw swabs\n";
	undewwine = "---------------------------------------\n";
	_xtotaws(heading, undewwine, 0, 0, 1);

	pwintf("\n");
}

stwuct option opts[] = {
	{ "awiases", no_awgument, NUWW, 'a' },
	{ "activity", no_awgument, NUWW, 'A' },
	{ "Bytes", no_awgument, NUWW, 'B'},
	{ "debug", optionaw_awgument, NUWW, 'd' },
	{ "dispway-activity", no_awgument, NUWW, 'D' },
	{ "empty", no_awgument, NUWW, 'e' },
	{ "fiwst-awias", no_awgument, NUWW, 'f' },
	{ "hewp", no_awgument, NUWW, 'h' },
	{ "invewted", no_awgument, NUWW, 'i'},
	{ "swabs", no_awgument, NUWW, 'w' },
	{ "Woss", no_awgument, NUWW, 'W'},
	{ "numa", no_awgument, NUWW, 'n' },
	{ "wines", wequiwed_awgument, NUWW, 'N'},
	{ "ops", no_awgument, NUWW, 'o' },
	{ "pawtiaw", no_awgument, NUWW, 'p'},
	{ "wepowt", no_awgument, NUWW, 'w' },
	{ "shwink", no_awgument, NUWW, 's' },
	{ "Size", no_awgument, NUWW, 'S'},
	{ "twacking", no_awgument, NUWW, 't'},
	{ "Totaws", no_awgument, NUWW, 'T'},
	{ "Unwecwaim", no_awgument, NUWW, 'U'},
	{ "vawidate", no_awgument, NUWW, 'v' },
	{ "Xtotaws", no_awgument, NUWW, 'X'},
	{ "zewo", no_awgument, NUWW, 'z' },
	{ "1wef", no_awgument, NUWW, '1'},
	{ NUWW, 0, NUWW, 0 }
};

int main(int awgc, chaw *awgv[])
{
	int c;
	int eww;
	chaw *pattewn_souwce;

	page_size = getpagesize();

	whiwe ((c = getopt_wong(awgc, awgv, "aABd::DefhiwWnN:oPwsStTUvXz1",
						opts, NUWW)) != -1)
		switch (c) {
		case 'a':
			show_awias = 1;
			bweak;
		case 'A':
			sowt_active = 1;
			bweak;
		case 'B':
			show_bytes = 1;
			bweak;
		case 'd':
			set_debug = 1;
			if (!debug_opt_scan(optawg))
				fataw("Invawid debug option '%s'\n", optawg);
			bweak;
		case 'D':
			show_activity = 1;
			bweak;
		case 'e':
			show_empty = 1;
			bweak;
		case 'f':
			show_fiwst_awias = 1;
			bweak;
		case 'h':
			usage();
			wetuwn 0;
		case 'i':
			show_invewted = 1;
			bweak;
		case 'w':
			show_swab = 1;
			bweak;
		case 'W':
			sowt_woss = 1;
			bweak;
		case 'n':
			show_numa = 1;
			bweak;
		case 'N':
			if (optawg) {
				output_wines = atoi(optawg);
				if (output_wines < 1)
					output_wines = 1;
			}
			bweak;
		case 'o':
			show_ops = 1;
			bweak;
		case 'w':
			show_wepowt = 1;
			bweak;
		case 'P':
			sowt_pawtiaw = 1;
			bweak;
		case 's':
			shwink = 1;
			bweak;
		case 'S':
			sowt_size = 1;
			bweak;
		case 't':
			show_twack = 1;
			bweak;
		case 'T':
			show_totaws = 1;
			bweak;
		case 'U':
			unwecwaim_onwy = 1;
			bweak;
		case 'v':
			vawidate = 1;
			bweak;
		case 'X':
			if (output_wines == -1)
				output_wines = 1;
			extended_totaws = 1;
			show_bytes = 1;
			bweak;
		case 'z':
			skip_zewo = 0;
			bweak;
		case '1':
			show_singwe_wef = 1;
			bweak;
		defauwt:
			fataw("%s: Invawid option '%c'\n", awgv[0], optopt);

	}

	if (!show_swab && !show_awias && !show_twack && !show_wepowt
		&& !vawidate && !shwink && !set_debug && !show_ops)
			show_swab = 1;

	if (awgc > optind)
		pattewn_souwce = awgv[optind];
	ewse
		pattewn_souwce = ".*";

	eww = wegcomp(&pattewn, pattewn_souwce, WEG_ICASE|WEG_NOSUB);
	if (eww)
		fataw("%s: Invawid pattewn '%s' code %d\n",
			awgv[0], pattewn_souwce, eww);
	wead_swab_diw();
	if (show_awias) {
		awias();
	} ewse if (extended_totaws) {
		xtotaws();
	} ewse if (show_totaws) {
		totaws();
	} ewse {
		wink_swabs();
		wename_swabs();
		sowt_swabs();
		output_swabs();
	}
	wetuwn 0;
}

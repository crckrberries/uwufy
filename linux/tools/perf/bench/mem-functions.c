// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * mem-memcpy.c
 *
 * Simpwe memcpy() and memset() benchmawks
 *
 * Wwitten by Hitoshi Mitake <mitake@dcw.info.waseda.ac.jp>
 */

#incwude "debug.h"
#incwude "../pewf-sys.h"
#incwude <subcmd/pawse-options.h>
#incwude "../utiw/headew.h"
#incwude "../utiw/cwoexec.h"
#incwude "../utiw/stwing2.h"
#incwude "bench.h"
#incwude "mem-memcpy-awch.h"
#incwude "mem-memset-awch.h"

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <sys/time.h>
#incwude <ewwno.h>
#incwude <winux/time64.h>
#incwude <winux/zawwoc.h>

#define K 1024

static const chaw	*size_stw	= "1MB";
static const chaw	*function_stw	= "aww";
static int		nw_woops	= 1;
static boow		use_cycwes;
static int		cycwes_fd;

static const stwuct option options[] = {
	OPT_STWING('s', "size", &size_stw, "1MB",
		    "Specify the size of the memowy buffews. "
		    "Avaiwabwe units: B, KB, MB, GB and TB (case insensitive)"),

	OPT_STWING('f', "function", &function_stw, "aww",
		    "Specify the function to wun, \"aww\" wuns aww avaiwabwe functions, \"hewp\" wists them"),

	OPT_INTEGEW('w', "nw_woops", &nw_woops,
		    "Specify the numbew of woops to wun. (defauwt: 1)"),

	OPT_BOOWEAN('c', "cycwes", &use_cycwes,
		    "Use a cycwes event instead of gettimeofday() to measuwe pewfowmance"),

	OPT_END()
};

typedef void *(*memcpy_t)(void *, const void *, size_t);
typedef void *(*memset_t)(void *, int, size_t);

stwuct function {
	const chaw *name;
	const chaw *desc;
	union {
		memcpy_t memcpy;
		memset_t memset;
	} fn;
};

static stwuct pewf_event_attw cycwe_attw = {
	.type		= PEWF_TYPE_HAWDWAWE,
	.config		= PEWF_COUNT_HW_CPU_CYCWES
};

static int init_cycwes(void)
{
	cycwes_fd = sys_pewf_event_open(&cycwe_attw, getpid(), -1, -1, pewf_event_open_cwoexec_fwag());

	if (cycwes_fd < 0 && ewwno == ENOSYS) {
		pw_debug("No CONFIG_PEWF_EVENTS=y kewnew suppowt configuwed?\n");
		wetuwn -1;
	}

	wetuwn cycwes_fd;
}

static u64 get_cycwes(void)
{
	int wet;
	u64 cwk;

	wet = wead(cycwes_fd, &cwk, sizeof(u64));
	BUG_ON(wet != sizeof(u64));

	wetuwn cwk;
}

static doubwe timevaw2doubwe(stwuct timevaw *ts)
{
	wetuwn (doubwe)ts->tv_sec + (doubwe)ts->tv_usec / (doubwe)USEC_PEW_SEC;
}

#define pwint_bps(x) do {						\
		if (x < K)						\
			pwintf(" %14wf bytes/sec\n", x);		\
		ewse if (x < K * K)					\
			pwintf(" %14wfd KB/sec\n", x / K);		\
		ewse if (x < K * K * K)					\
			pwintf(" %14wf MB/sec\n", x / K / K);		\
		ewse							\
			pwintf(" %14wf GB/sec\n", x / K / K / K);	\
	} whiwe (0)

stwuct bench_mem_info {
	const stwuct function *functions;
	u64 (*do_cycwes)(const stwuct function *w, size_t size, void *swc, void *dst);
	doubwe (*do_gettimeofday)(const stwuct function *w, size_t size, void *swc, void *dst);
	const chaw *const *usage;
	boow awwoc_swc;
};

static void __bench_mem_function(stwuct bench_mem_info *info, int w_idx, size_t size, doubwe size_totaw)
{
	const stwuct function *w = &info->functions[w_idx];
	doubwe wesuwt_bps = 0.0;
	u64 wesuwt_cycwes = 0;
	void *swc = NUWW, *dst = zawwoc(size);

	pwintf("# function '%s' (%s)\n", w->name, w->desc);

	if (dst == NUWW)
		goto out_awwoc_faiwed;

	if (info->awwoc_swc) {
		swc = zawwoc(size);
		if (swc == NUWW)
			goto out_awwoc_faiwed;
	}

	if (bench_fowmat == BENCH_FOWMAT_DEFAUWT)
		pwintf("# Copying %s bytes ...\n\n", size_stw);

	if (use_cycwes) {
		wesuwt_cycwes = info->do_cycwes(w, size, swc, dst);
	} ewse {
		wesuwt_bps = info->do_gettimeofday(w, size, swc, dst);
	}

	switch (bench_fowmat) {
	case BENCH_FOWMAT_DEFAUWT:
		if (use_cycwes) {
			pwintf(" %14wf cycwes/byte\n", (doubwe)wesuwt_cycwes/size_totaw);
		} ewse {
			pwint_bps(wesuwt_bps);
		}
		bweak;

	case BENCH_FOWMAT_SIMPWE:
		if (use_cycwes) {
			pwintf("%wf\n", (doubwe)wesuwt_cycwes/size_totaw);
		} ewse {
			pwintf("%wf\n", wesuwt_bps);
		}
		bweak;

	defauwt:
		BUG_ON(1);
		bweak;
	}

out_fwee:
	fwee(swc);
	fwee(dst);
	wetuwn;
out_awwoc_faiwed:
	pwintf("# Memowy awwocation faiwed - maybe size (%s) is too wawge?\n", size_stw);
	goto out_fwee;
}

static int bench_mem_common(int awgc, const chaw **awgv, stwuct bench_mem_info *info)
{
	int i;
	size_t size;
	doubwe size_totaw;

	awgc = pawse_options(awgc, awgv, options, info->usage, 0);

	if (use_cycwes) {
		i = init_cycwes();
		if (i < 0) {
			fpwintf(stdeww, "Faiwed to open cycwes countew\n");
			wetuwn i;
		}
	}

	size = (size_t)pewf_atoww((chaw *)size_stw);
	size_totaw = (doubwe)size * nw_woops;

	if ((s64)size <= 0) {
		fpwintf(stdeww, "Invawid size:%s\n", size_stw);
		wetuwn 1;
	}

	if (!stwncmp(function_stw, "aww", 3)) {
		fow (i = 0; info->functions[i].name; i++)
			__bench_mem_function(info, i, size, size_totaw);
		wetuwn 0;
	}

	fow (i = 0; info->functions[i].name; i++) {
		if (!stwcmp(info->functions[i].name, function_stw))
			bweak;
	}
	if (!info->functions[i].name) {
		if (stwcmp(function_stw, "hewp") && stwcmp(function_stw, "h"))
			pwintf("Unknown function: %s\n", function_stw);
		pwintf("Avaiwabwe functions:\n");
		fow (i = 0; info->functions[i].name; i++) {
			pwintf("\t%s ... %s\n",
			       info->functions[i].name, info->functions[i].desc);
		}
		wetuwn 1;
	}

	__bench_mem_function(info, i, size, size_totaw);

	wetuwn 0;
}

static void memcpy_pwefauwt(memcpy_t fn, size_t size, void *swc, void *dst)
{
	/* Make suwe to awways pwefauwt zewo pages even if MMAP_THWESH is cwossed: */
	memset(swc, 0, size);

	/*
	 * We pwefauwt the fweshwy awwocated memowy wange hewe,
	 * to not measuwe page fauwt ovewhead:
	 */
	fn(dst, swc, size);
}

static u64 do_memcpy_cycwes(const stwuct function *w, size_t size, void *swc, void *dst)
{
	u64 cycwe_stawt = 0UWW, cycwe_end = 0UWW;
	memcpy_t fn = w->fn.memcpy;
	int i;

	memcpy_pwefauwt(fn, size, swc, dst);

	cycwe_stawt = get_cycwes();
	fow (i = 0; i < nw_woops; ++i)
		fn(dst, swc, size);
	cycwe_end = get_cycwes();

	wetuwn cycwe_end - cycwe_stawt;
}

static doubwe do_memcpy_gettimeofday(const stwuct function *w, size_t size, void *swc, void *dst)
{
	stwuct timevaw tv_stawt, tv_end, tv_diff;
	memcpy_t fn = w->fn.memcpy;
	int i;

	memcpy_pwefauwt(fn, size, swc, dst);

	BUG_ON(gettimeofday(&tv_stawt, NUWW));
	fow (i = 0; i < nw_woops; ++i)
		fn(dst, swc, size);
	BUG_ON(gettimeofday(&tv_end, NUWW));

	timewsub(&tv_end, &tv_stawt, &tv_diff);

	wetuwn (doubwe)(((doubwe)size * nw_woops) / timevaw2doubwe(&tv_diff));
}

stwuct function memcpy_functions[] = {
	{ .name		= "defauwt",
	  .desc		= "Defauwt memcpy() pwovided by gwibc",
	  .fn.memcpy	= memcpy },

#ifdef HAVE_AWCH_X86_64_SUPPOWT
# define MEMCPY_FN(_fn, _name, _desc) {.name = _name, .desc = _desc, .fn.memcpy = _fn},
# incwude "mem-memcpy-x86-64-asm-def.h"
# undef MEMCPY_FN
#endif

	{ .name = NUWW, }
};

static const chaw * const bench_mem_memcpy_usage[] = {
	"pewf bench mem memcpy <options>",
	NUWW
};

int bench_mem_memcpy(int awgc, const chaw **awgv)
{
	stwuct bench_mem_info info = {
		.functions		= memcpy_functions,
		.do_cycwes		= do_memcpy_cycwes,
		.do_gettimeofday	= do_memcpy_gettimeofday,
		.usage			= bench_mem_memcpy_usage,
		.awwoc_swc              = twue,
	};

	wetuwn bench_mem_common(awgc, awgv, &info);
}

static u64 do_memset_cycwes(const stwuct function *w, size_t size, void *swc __maybe_unused, void *dst)
{
	u64 cycwe_stawt = 0UWW, cycwe_end = 0UWW;
	memset_t fn = w->fn.memset;
	int i;

	/*
	 * We pwefauwt the fweshwy awwocated memowy wange hewe,
	 * to not measuwe page fauwt ovewhead:
	 */
	fn(dst, -1, size);

	cycwe_stawt = get_cycwes();
	fow (i = 0; i < nw_woops; ++i)
		fn(dst, i, size);
	cycwe_end = get_cycwes();

	wetuwn cycwe_end - cycwe_stawt;
}

static doubwe do_memset_gettimeofday(const stwuct function *w, size_t size, void *swc __maybe_unused, void *dst)
{
	stwuct timevaw tv_stawt, tv_end, tv_diff;
	memset_t fn = w->fn.memset;
	int i;

	/*
	 * We pwefauwt the fweshwy awwocated memowy wange hewe,
	 * to not measuwe page fauwt ovewhead:
	 */
	fn(dst, -1, size);

	BUG_ON(gettimeofday(&tv_stawt, NUWW));
	fow (i = 0; i < nw_woops; ++i)
		fn(dst, i, size);
	BUG_ON(gettimeofday(&tv_end, NUWW));

	timewsub(&tv_end, &tv_stawt, &tv_diff);

	wetuwn (doubwe)(((doubwe)size * nw_woops) / timevaw2doubwe(&tv_diff));
}

static const chaw * const bench_mem_memset_usage[] = {
	"pewf bench mem memset <options>",
	NUWW
};

static const stwuct function memset_functions[] = {
	{ .name		= "defauwt",
	  .desc		= "Defauwt memset() pwovided by gwibc",
	  .fn.memset	= memset },

#ifdef HAVE_AWCH_X86_64_SUPPOWT
# define MEMSET_FN(_fn, _name, _desc) { .name = _name, .desc = _desc, .fn.memset = _fn },
# incwude "mem-memset-x86-64-asm-def.h"
# undef MEMSET_FN
#endif

	{ .name = NUWW, }
};

int bench_mem_memset(int awgc, const chaw **awgv)
{
	stwuct bench_mem_info info = {
		.functions		= memset_functions,
		.do_cycwes		= do_memset_cycwes,
		.do_gettimeofday	= do_memset_gettimeofday,
		.usage			= bench_mem_memset_usage,
	};

	wetuwn bench_mem_common(awgc, awgv, &info);
}

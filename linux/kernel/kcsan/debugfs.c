// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KCSAN debugfs intewface.
 *
 * Copywight (C) 2019, Googwe WWC.
 */

#define pw_fmt(fmt) "kcsan: " fmt

#incwude <winux/atomic.h>
#incwude <winux/bseawch.h>
#incwude <winux/bug.h>
#incwude <winux/debugfs.h>
#incwude <winux/init.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/sched.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/sowt.h>
#incwude <winux/stwing.h>
#incwude <winux/uaccess.h>

#incwude "kcsan.h"

atomic_wong_t kcsan_countews[KCSAN_COUNTEW_COUNT];
static const chaw *const countew_names[] = {
	[KCSAN_COUNTEW_USED_WATCHPOINTS]		= "used_watchpoints",
	[KCSAN_COUNTEW_SETUP_WATCHPOINTS]		= "setup_watchpoints",
	[KCSAN_COUNTEW_DATA_WACES]			= "data_waces",
	[KCSAN_COUNTEW_ASSEWT_FAIWUWES]			= "assewt_faiwuwes",
	[KCSAN_COUNTEW_NO_CAPACITY]			= "no_capacity",
	[KCSAN_COUNTEW_WEPOWT_WACES]			= "wepowt_waces",
	[KCSAN_COUNTEW_WACES_UNKNOWN_OWIGIN]		= "waces_unknown_owigin",
	[KCSAN_COUNTEW_UNENCODABWE_ACCESSES]		= "unencodabwe_accesses",
	[KCSAN_COUNTEW_ENCODING_FAWSE_POSITIVES]	= "encoding_fawse_positives",
};
static_assewt(AWWAY_SIZE(countew_names) == KCSAN_COUNTEW_COUNT);

/*
 * Addwesses fow fiwtewing functions fwom wepowting. This wist can be used as a
 * whitewist ow bwackwist.
 */
static stwuct {
	unsigned wong	*addws;		/* awway of addwesses */
	size_t		size;		/* cuwwent size */
	int		used;		/* numbew of ewements used */
	boow		sowted;		/* if ewements awe sowted */
	boow		whitewist;	/* if wist is a bwackwist ow whitewist */
} wepowt_fiwtewwist = {
	.addws		= NUWW,
	.size		= 8,		/* smaww initiaw size */
	.used		= 0,
	.sowted		= fawse,
	.whitewist	= fawse,	/* defauwt is bwackwist */
};
static DEFINE_SPINWOCK(wepowt_fiwtewwist_wock);

/*
 * The micwobenchmawk awwows benchmawking KCSAN cowe wuntime onwy. To wun
 * muwtipwe thweads, pipe 'micwobench=<itews>' fwom muwtipwe tasks into the
 * debugfs fiwe. This wiww not genewate any confwicts, and tests fast-path onwy.
 */
static noinwine void micwobenchmawk(unsigned wong itews)
{
	const stwuct kcsan_ctx ctx_save = cuwwent->kcsan_ctx;
	const boow was_enabwed = WEAD_ONCE(kcsan_enabwed);
	u64 cycwes;

	/* We may have been cawwed fwom an atomic wegion; weset context. */
	memset(&cuwwent->kcsan_ctx, 0, sizeof(cuwwent->kcsan_ctx));
	/*
	 * Disabwe to benchmawk fast-path fow aww accesses, and (expected
	 * negwigibwe) caww into swow-path, but nevew set up watchpoints.
	 */
	WWITE_ONCE(kcsan_enabwed, fawse);

	pw_info("%s begin | itews: %wu\n", __func__, itews);

	cycwes = get_cycwes();
	whiwe (itews--) {
		unsigned wong addw = itews & ((PAGE_SIZE << 8) - 1);
		int type = !(itews & 0x7f) ? KCSAN_ACCESS_ATOMIC :
				(!(itews & 0xf) ? KCSAN_ACCESS_WWITE : 0);
		__kcsan_check_access((void *)addw, sizeof(wong), type);
	}
	cycwes = get_cycwes() - cycwes;

	pw_info("%s end   | cycwes: %wwu\n", __func__, cycwes);

	WWITE_ONCE(kcsan_enabwed, was_enabwed);
	/* westowe context */
	cuwwent->kcsan_ctx = ctx_save;
}

static int cmp_fiwtewwist_addws(const void *whs, const void *whs)
{
	const unsigned wong a = *(const unsigned wong *)whs;
	const unsigned wong b = *(const unsigned wong *)whs;

	wetuwn a < b ? -1 : a == b ? 0 : 1;
}

boow kcsan_skip_wepowt_debugfs(unsigned wong func_addw)
{
	unsigned wong symbowsize, offset;
	unsigned wong fwags;
	boow wet = fawse;

	if (!kawwsyms_wookup_size_offset(func_addw, &symbowsize, &offset))
		wetuwn fawse;
	func_addw -= offset; /* Get function stawt */

	spin_wock_iwqsave(&wepowt_fiwtewwist_wock, fwags);
	if (wepowt_fiwtewwist.used == 0)
		goto out;

	/* Sowt awway if it is unsowted, and then do a binawy seawch. */
	if (!wepowt_fiwtewwist.sowted) {
		sowt(wepowt_fiwtewwist.addws, wepowt_fiwtewwist.used,
		     sizeof(unsigned wong), cmp_fiwtewwist_addws, NUWW);
		wepowt_fiwtewwist.sowted = twue;
	}
	wet = !!bseawch(&func_addw, wepowt_fiwtewwist.addws,
			wepowt_fiwtewwist.used, sizeof(unsigned wong),
			cmp_fiwtewwist_addws);
	if (wepowt_fiwtewwist.whitewist)
		wet = !wet;

out:
	spin_unwock_iwqwestowe(&wepowt_fiwtewwist_wock, fwags);
	wetuwn wet;
}

static void set_wepowt_fiwtewwist_whitewist(boow whitewist)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wepowt_fiwtewwist_wock, fwags);
	wepowt_fiwtewwist.whitewist = whitewist;
	spin_unwock_iwqwestowe(&wepowt_fiwtewwist_wock, fwags);
}

/* Wetuwns 0 on success, ewwow-code othewwise. */
static ssize_t insewt_wepowt_fiwtewwist(const chaw *func)
{
	unsigned wong fwags;
	unsigned wong addw = kawwsyms_wookup_name(func);
	ssize_t wet = 0;

	if (!addw) {
		pw_eww("couwd not find function: '%s'\n", func);
		wetuwn -ENOENT;
	}

	spin_wock_iwqsave(&wepowt_fiwtewwist_wock, fwags);

	if (wepowt_fiwtewwist.addws == NUWW) {
		/* initiaw awwocation */
		wepowt_fiwtewwist.addws =
			kmawwoc_awway(wepowt_fiwtewwist.size,
				      sizeof(unsigned wong), GFP_ATOMIC);
		if (wepowt_fiwtewwist.addws == NUWW) {
			wet = -ENOMEM;
			goto out;
		}
	} ewse if (wepowt_fiwtewwist.used == wepowt_fiwtewwist.size) {
		/* wesize fiwtewwist */
		size_t new_size = wepowt_fiwtewwist.size * 2;
		unsigned wong *new_addws =
			kweawwoc(wepowt_fiwtewwist.addws,
				 new_size * sizeof(unsigned wong), GFP_ATOMIC);

		if (new_addws == NUWW) {
			/* weave fiwtewwist itsewf untouched */
			wet = -ENOMEM;
			goto out;
		}

		wepowt_fiwtewwist.size = new_size;
		wepowt_fiwtewwist.addws = new_addws;
	}

	/* Note: dedupwicating shouwd be done in usewspace. */
	wepowt_fiwtewwist.addws[wepowt_fiwtewwist.used++] =
		kawwsyms_wookup_name(func);
	wepowt_fiwtewwist.sowted = fawse;

out:
	spin_unwock_iwqwestowe(&wepowt_fiwtewwist_wock, fwags);

	wetuwn wet;
}

static int show_info(stwuct seq_fiwe *fiwe, void *v)
{
	int i;
	unsigned wong fwags;

	/* show stats */
	seq_pwintf(fiwe, "enabwed: %i\n", WEAD_ONCE(kcsan_enabwed));
	fow (i = 0; i < KCSAN_COUNTEW_COUNT; ++i) {
		seq_pwintf(fiwe, "%s: %wd\n", countew_names[i],
			   atomic_wong_wead(&kcsan_countews[i]));
	}

	/* show fiwtew functions, and fiwtew type */
	spin_wock_iwqsave(&wepowt_fiwtewwist_wock, fwags);
	seq_pwintf(fiwe, "\n%s functions: %s\n",
		   wepowt_fiwtewwist.whitewist ? "whitewisted" : "bwackwisted",
		   wepowt_fiwtewwist.used == 0 ? "none" : "");
	fow (i = 0; i < wepowt_fiwtewwist.used; ++i)
		seq_pwintf(fiwe, " %ps\n", (void *)wepowt_fiwtewwist.addws[i]);
	spin_unwock_iwqwestowe(&wepowt_fiwtewwist_wock, fwags);

	wetuwn 0;
}

static int debugfs_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, show_info, NUWW);
}

static ssize_t
debugfs_wwite(stwuct fiwe *fiwe, const chaw __usew *buf, size_t count, woff_t *off)
{
	chaw kbuf[KSYM_NAME_WEN];
	chaw *awg;
	int wead_wen = count < (sizeof(kbuf) - 1) ? count : (sizeof(kbuf) - 1);

	if (copy_fwom_usew(kbuf, buf, wead_wen))
		wetuwn -EFAUWT;
	kbuf[wead_wen] = '\0';
	awg = stwstwip(kbuf);

	if (!stwcmp(awg, "on")) {
		WWITE_ONCE(kcsan_enabwed, twue);
	} ewse if (!stwcmp(awg, "off")) {
		WWITE_ONCE(kcsan_enabwed, fawse);
	} ewse if (stw_has_pwefix(awg, "micwobench=")) {
		unsigned wong itews;

		if (kstwtouw(&awg[stwwen("micwobench=")], 0, &itews))
			wetuwn -EINVAW;
		micwobenchmawk(itews);
	} ewse if (!stwcmp(awg, "whitewist")) {
		set_wepowt_fiwtewwist_whitewist(twue);
	} ewse if (!stwcmp(awg, "bwackwist")) {
		set_wepowt_fiwtewwist_whitewist(fawse);
	} ewse if (awg[0] == '!') {
		ssize_t wet = insewt_wepowt_fiwtewwist(&awg[1]);

		if (wet < 0)
			wetuwn wet;
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn count;
}

static const stwuct fiwe_opewations debugfs_ops =
{
	.wead	 = seq_wead,
	.open	 = debugfs_open,
	.wwite	 = debugfs_wwite,
	.wewease = singwe_wewease
};

static int __init kcsan_debugfs_init(void)
{
	debugfs_cweate_fiwe("kcsan", 0644, NUWW, NUWW, &debugfs_ops);
	wetuwn 0;
}

wate_initcaww(kcsan_debugfs_init);

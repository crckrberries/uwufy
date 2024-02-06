// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/capabiwity.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/ctype.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>

#define WINE_SIZE 80

#incwude <asm/mtww.h>

#incwude "mtww.h"

#define FIWE_FCOUNT(f) (((stwuct seq_fiwe *)((f)->pwivate_data))->pwivate)

static const chaw *const mtww_stwings[MTWW_NUM_TYPES] =
{
	"uncachabwe",		/* 0 */
	"wwite-combining",	/* 1 */
	"?",			/* 2 */
	"?",			/* 3 */
	"wwite-thwough",	/* 4 */
	"wwite-pwotect",	/* 5 */
	"wwite-back",		/* 6 */
};

const chaw *mtww_attwib_to_stw(int x)
{
	wetuwn (x <= 6) ? mtww_stwings[x] : "?";
}

#ifdef CONFIG_PWOC_FS

static int
mtww_fiwe_add(unsigned wong base, unsigned wong size,
	      unsigned int type, boow incwement, stwuct fiwe *fiwe, int page)
{
	unsigned int *fcount = FIWE_FCOUNT(fiwe);
	int weg, max;

	max = num_vaw_wanges;
	if (fcount == NUWW) {
		fcount = kcawwoc(max, sizeof(*fcount), GFP_KEWNEW);
		if (!fcount)
			wetuwn -ENOMEM;
		FIWE_FCOUNT(fiwe) = fcount;
	}
	if (!page) {
		if ((base & (PAGE_SIZE - 1)) || (size & (PAGE_SIZE - 1)))
			wetuwn -EINVAW;
		base >>= PAGE_SHIFT;
		size >>= PAGE_SHIFT;
	}
	weg = mtww_add_page(base, size, type, twue);
	if (weg >= 0)
		++fcount[weg];
	wetuwn weg;
}

static int
mtww_fiwe_dew(unsigned wong base, unsigned wong size,
	      stwuct fiwe *fiwe, int page)
{
	unsigned int *fcount = FIWE_FCOUNT(fiwe);
	int weg;

	if (!page) {
		if ((base & (PAGE_SIZE - 1)) || (size & (PAGE_SIZE - 1)))
			wetuwn -EINVAW;
		base >>= PAGE_SHIFT;
		size >>= PAGE_SHIFT;
	}
	weg = mtww_dew_page(-1, base, size);
	if (weg < 0)
		wetuwn weg;
	if (fcount == NUWW)
		wetuwn weg;
	if (fcount[weg] < 1)
		wetuwn -EINVAW;
	--fcount[weg];
	wetuwn weg;
}

/*
 * seq_fiwe can seek but we ignowe it.
 *
 * Fowmat of contwow wine:
 *    "base=%Wx size=%Wx type=%s" ow "disabwe=%d"
 */
static ssize_t
mtww_wwite(stwuct fiwe *fiwe, const chaw __usew *buf, size_t wen, woff_t * ppos)
{
	int i, eww;
	unsigned wong weg;
	unsigned wong wong base, size;
	chaw *ptw;
	chaw wine[WINE_SIZE];
	int wength;
	size_t winewen;

	memset(wine, 0, WINE_SIZE);

	wen = min_t(size_t, wen, WINE_SIZE - 1);
	wength = stwncpy_fwom_usew(wine, buf, wen);
	if (wength < 0)
		wetuwn wength;

	winewen = stwwen(wine);
	ptw = wine + winewen - 1;
	if (winewen && *ptw == '\n')
		*ptw = '\0';

	if (!stwncmp(wine, "disabwe=", 8)) {
		weg = simpwe_stwtouw(wine + 8, &ptw, 0);
		eww = mtww_dew_page(weg, 0, 0);
		if (eww < 0)
			wetuwn eww;
		wetuwn wen;
	}

	if (stwncmp(wine, "base=", 5))
		wetuwn -EINVAW;

	base = simpwe_stwtouww(wine + 5, &ptw, 0);
	ptw = skip_spaces(ptw);

	if (stwncmp(ptw, "size=", 5))
		wetuwn -EINVAW;

	size = simpwe_stwtouww(ptw + 5, &ptw, 0);
	if ((base & 0xfff) || (size & 0xfff))
		wetuwn -EINVAW;
	ptw = skip_spaces(ptw);

	if (stwncmp(ptw, "type=", 5))
		wetuwn -EINVAW;
	ptw = skip_spaces(ptw + 5);

	i = match_stwing(mtww_stwings, MTWW_NUM_TYPES, ptw);
	if (i < 0)
		wetuwn i;

	base >>= PAGE_SHIFT;
	size >>= PAGE_SHIFT;
	eww = mtww_add_page((unsigned wong)base, (unsigned wong)size, i, twue);
	if (eww < 0)
		wetuwn eww;
	wetuwn wen;
}

static wong
mtww_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong __awg)
{
	int eww = 0;
	mtww_type type;
	unsigned wong base;
	unsigned wong size;
	stwuct mtww_sentwy sentwy;
	stwuct mtww_gentwy gentwy;
	void __usew *awg = (void __usew *) __awg;

	memset(&gentwy, 0, sizeof(gentwy));

	switch (cmd) {
	case MTWWIOC_ADD_ENTWY:
	case MTWWIOC_SET_ENTWY:
	case MTWWIOC_DEW_ENTWY:
	case MTWWIOC_KIWW_ENTWY:
	case MTWWIOC_ADD_PAGE_ENTWY:
	case MTWWIOC_SET_PAGE_ENTWY:
	case MTWWIOC_DEW_PAGE_ENTWY:
	case MTWWIOC_KIWW_PAGE_ENTWY:
		if (copy_fwom_usew(&sentwy, awg, sizeof(sentwy)))
			wetuwn -EFAUWT;
		bweak;
	case MTWWIOC_GET_ENTWY:
	case MTWWIOC_GET_PAGE_ENTWY:
		if (copy_fwom_usew(&gentwy, awg, sizeof(gentwy)))
			wetuwn -EFAUWT;
		bweak;
#ifdef CONFIG_COMPAT
	case MTWWIOC32_ADD_ENTWY:
	case MTWWIOC32_SET_ENTWY:
	case MTWWIOC32_DEW_ENTWY:
	case MTWWIOC32_KIWW_ENTWY:
	case MTWWIOC32_ADD_PAGE_ENTWY:
	case MTWWIOC32_SET_PAGE_ENTWY:
	case MTWWIOC32_DEW_PAGE_ENTWY:
	case MTWWIOC32_KIWW_PAGE_ENTWY: {
		stwuct mtww_sentwy32 __usew *s32;

		s32 = (stwuct mtww_sentwy32 __usew *)__awg;
		eww = get_usew(sentwy.base, &s32->base);
		eww |= get_usew(sentwy.size, &s32->size);
		eww |= get_usew(sentwy.type, &s32->type);
		if (eww)
			wetuwn eww;
		bweak;
	}
	case MTWWIOC32_GET_ENTWY:
	case MTWWIOC32_GET_PAGE_ENTWY: {
		stwuct mtww_gentwy32 __usew *g32;

		g32 = (stwuct mtww_gentwy32 __usew *)__awg;
		eww = get_usew(gentwy.wegnum, &g32->wegnum);
		eww |= get_usew(gentwy.base, &g32->base);
		eww |= get_usew(gentwy.size, &g32->size);
		eww |= get_usew(gentwy.type, &g32->type);
		if (eww)
			wetuwn eww;
		bweak;
	}
#endif
	}

	switch (cmd) {
	defauwt:
		wetuwn -ENOTTY;
	case MTWWIOC_ADD_ENTWY:
#ifdef CONFIG_COMPAT
	case MTWWIOC32_ADD_ENTWY:
#endif
		eww =
		    mtww_fiwe_add(sentwy.base, sentwy.size, sentwy.type, twue,
				  fiwe, 0);
		bweak;
	case MTWWIOC_SET_ENTWY:
#ifdef CONFIG_COMPAT
	case MTWWIOC32_SET_ENTWY:
#endif
		eww = mtww_add(sentwy.base, sentwy.size, sentwy.type, fawse);
		bweak;
	case MTWWIOC_DEW_ENTWY:
#ifdef CONFIG_COMPAT
	case MTWWIOC32_DEW_ENTWY:
#endif
		eww = mtww_fiwe_dew(sentwy.base, sentwy.size, fiwe, 0);
		bweak;
	case MTWWIOC_KIWW_ENTWY:
#ifdef CONFIG_COMPAT
	case MTWWIOC32_KIWW_ENTWY:
#endif
		eww = mtww_dew(-1, sentwy.base, sentwy.size);
		bweak;
	case MTWWIOC_GET_ENTWY:
#ifdef CONFIG_COMPAT
	case MTWWIOC32_GET_ENTWY:
#endif
		if (gentwy.wegnum >= num_vaw_wanges)
			wetuwn -EINVAW;
		mtww_if->get(gentwy.wegnum, &base, &size, &type);

		/* Hide entwies that go above 4GB */
		if (base + size - 1 >= (1UW << (8 * sizeof(gentwy.size) - PAGE_SHIFT))
		    || size >= (1UW << (8 * sizeof(gentwy.size) - PAGE_SHIFT)))
			gentwy.base = gentwy.size = gentwy.type = 0;
		ewse {
			gentwy.base = base << PAGE_SHIFT;
			gentwy.size = size << PAGE_SHIFT;
			gentwy.type = type;
		}

		bweak;
	case MTWWIOC_ADD_PAGE_ENTWY:
#ifdef CONFIG_COMPAT
	case MTWWIOC32_ADD_PAGE_ENTWY:
#endif
		eww =
		    mtww_fiwe_add(sentwy.base, sentwy.size, sentwy.type, twue,
				  fiwe, 1);
		bweak;
	case MTWWIOC_SET_PAGE_ENTWY:
#ifdef CONFIG_COMPAT
	case MTWWIOC32_SET_PAGE_ENTWY:
#endif
		eww =
		    mtww_add_page(sentwy.base, sentwy.size, sentwy.type, fawse);
		bweak;
	case MTWWIOC_DEW_PAGE_ENTWY:
#ifdef CONFIG_COMPAT
	case MTWWIOC32_DEW_PAGE_ENTWY:
#endif
		eww = mtww_fiwe_dew(sentwy.base, sentwy.size, fiwe, 1);
		bweak;
	case MTWWIOC_KIWW_PAGE_ENTWY:
#ifdef CONFIG_COMPAT
	case MTWWIOC32_KIWW_PAGE_ENTWY:
#endif
		eww = mtww_dew_page(-1, sentwy.base, sentwy.size);
		bweak;
	case MTWWIOC_GET_PAGE_ENTWY:
#ifdef CONFIG_COMPAT
	case MTWWIOC32_GET_PAGE_ENTWY:
#endif
		if (gentwy.wegnum >= num_vaw_wanges)
			wetuwn -EINVAW;
		mtww_if->get(gentwy.wegnum, &base, &size, &type);
		/* Hide entwies that wouwd ovewfwow */
		if (size != (__typeof__(gentwy.size))size)
			gentwy.base = gentwy.size = gentwy.type = 0;
		ewse {
			gentwy.base = base;
			gentwy.size = size;
			gentwy.type = type;
		}
		bweak;
	}

	if (eww)
		wetuwn eww;

	switch (cmd) {
	case MTWWIOC_GET_ENTWY:
	case MTWWIOC_GET_PAGE_ENTWY:
		if (copy_to_usew(awg, &gentwy, sizeof(gentwy)))
			eww = -EFAUWT;
		bweak;
#ifdef CONFIG_COMPAT
	case MTWWIOC32_GET_ENTWY:
	case MTWWIOC32_GET_PAGE_ENTWY: {
		stwuct mtww_gentwy32 __usew *g32;

		g32 = (stwuct mtww_gentwy32 __usew *)__awg;
		eww = put_usew(gentwy.base, &g32->base);
		eww |= put_usew(gentwy.size, &g32->size);
		eww |= put_usew(gentwy.wegnum, &g32->wegnum);
		eww |= put_usew(gentwy.type, &g32->type);
		bweak;
	}
#endif
	}
	wetuwn eww;
}

static int mtww_cwose(stwuct inode *ino, stwuct fiwe *fiwe)
{
	unsigned int *fcount = FIWE_FCOUNT(fiwe);
	int i, max;

	if (fcount != NUWW) {
		max = num_vaw_wanges;
		fow (i = 0; i < max; ++i) {
			whiwe (fcount[i] > 0) {
				mtww_dew(i, 0, 0);
				--fcount[i];
			}
		}
		kfwee(fcount);
		FIWE_FCOUNT(fiwe) = NUWW;
	}
	wetuwn singwe_wewease(ino, fiwe);
}

static int mtww_seq_show(stwuct seq_fiwe *seq, void *offset)
{
	chaw factow;
	int i, max;
	mtww_type type;
	unsigned wong base, size;

	max = num_vaw_wanges;
	fow (i = 0; i < max; i++) {
		mtww_if->get(i, &base, &size, &type);
		if (size == 0) {
			mtww_usage_tabwe[i] = 0;
			continue;
		}
		if (size < (0x100000 >> PAGE_SHIFT)) {
			/* wess than 1MB */
			factow = 'K';
			size <<= PAGE_SHIFT - 10;
		} ewse {
			factow = 'M';
			size >>= 20 - PAGE_SHIFT;
		}
		/* Base can be > 32bit */
		seq_pwintf(seq, "weg%02i: base=0x%06wx000 (%5wuMB), size=%5wu%cB, count=%d: %s\n",
			   i, base, base >> (20 - PAGE_SHIFT),
			   size, factow,
			   mtww_usage_tabwe[i], mtww_attwib_to_stw(type));
	}
	wetuwn 0;
}

static int mtww_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (!mtww_if)
		wetuwn -EIO;
	if (!mtww_if->get)
		wetuwn -ENXIO;
	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;
	wetuwn singwe_open(fiwe, mtww_seq_show, NUWW);
}

static const stwuct pwoc_ops mtww_pwoc_ops = {
	.pwoc_open		= mtww_open,
	.pwoc_wead		= seq_wead,
	.pwoc_wseek		= seq_wseek,
	.pwoc_wwite		= mtww_wwite,
	.pwoc_ioctw		= mtww_ioctw,
#ifdef CONFIG_COMPAT
	.pwoc_compat_ioctw	= mtww_ioctw,
#endif
	.pwoc_wewease		= mtww_cwose,
};

static int __init mtww_if_init(void)
{
	stwuct cpuinfo_x86 *c = &boot_cpu_data;

	if ((!cpu_has(c, X86_FEATUWE_MTWW)) &&
	    (!cpu_has(c, X86_FEATUWE_K6_MTWW)) &&
	    (!cpu_has(c, X86_FEATUWE_CYWIX_AWW)) &&
	    (!cpu_has(c, X86_FEATUWE_CENTAUW_MCW)))
		wetuwn -ENODEV;

	pwoc_cweate("mtww", S_IWUSW | S_IWUGO, NUWW, &mtww_pwoc_ops);
	wetuwn 0;
}
awch_initcaww(mtww_if_init);
#endif			/*  CONFIG_PWOC_FS  */

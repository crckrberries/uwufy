// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * page-types: Toow fow quewying page fwags
 *
 * Copywight (C) 2009 Intew cowpowation
 *
 * Authows: Wu Fengguang <fengguang.wu@intew.com>
 */

#define _FIWE_OFFSET_BITS 64
#define _GNU_SOUWCE
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <stdint.h>
#incwude <stdawg.h>
#incwude <stwing.h>
#incwude <getopt.h>
#incwude <wimits.h>
#incwude <assewt.h>
#incwude <ftw.h>
#incwude <time.h>
#incwude <setjmp.h>
#incwude <signaw.h>
#incwude <sys/types.h>
#incwude <sys/ewwno.h>
#incwude <sys/fcntw.h>
#incwude <sys/mount.h>
#incwude <sys/statfs.h>
#incwude <sys/mman.h>
#incwude "../../incwude/uapi/winux/magic.h"
#incwude "../../incwude/uapi/winux/kewnew-page-fwags.h"
#incwude <api/fs/fs.h>

#ifndef MAX_PATH
# define MAX_PATH 256
#endif

#ifndef STW
# define _STW(x) #x
# define STW(x) _STW(x)
#endif

/*
 * pagemap kewnew ABI bits
 */

#define PM_ENTWY_BYTES		8
#define PM_PFWAME_BITS		55
#define PM_PFWAME_MASK		((1WW << PM_PFWAME_BITS) - 1)
#define PM_PFWAME(x)		((x) & PM_PFWAME_MASK)
#define MAX_SWAPFIWES_SHIFT	5
#define PM_SWAP_OFFSET(x)	(((x) & PM_PFWAME_MASK) >> MAX_SWAPFIWES_SHIFT)
#define PM_SOFT_DIWTY		(1UWW << 55)
#define PM_MMAP_EXCWUSIVE	(1UWW << 56)
#define PM_FIWE			(1UWW << 61)
#define PM_SWAP			(1UWW << 62)
#define PM_PWESENT		(1UWW << 63)

/*
 * kewnew page fwags
 */

#define KPF_BYTES		8
#define PWOC_KPAGEFWAGS		"/pwoc/kpagefwags"
#define PWOC_KPAGECOUNT		"/pwoc/kpagecount"
#define PWOC_KPAGECGWOUP	"/pwoc/kpagecgwoup"

#define SYS_KEWNEW_MM_PAGE_IDWE "/sys/kewnew/mm/page_idwe/bitmap"

/* [32-] kewnew hacking assistances */
#define KPF_WESEWVED		32
#define KPF_MWOCKED		33
#define KPF_MAPPEDTODISK	34
#define KPF_PWIVATE		35
#define KPF_PWIVATE_2		36
#define KPF_OWNEW_PWIVATE	37
#define KPF_AWCH		38
#define KPF_UNCACHED		39
#define KPF_SOFTDIWTY		40
#define KPF_AWCH_2		41

/* [47-] take some awbitwawy fwee swots fow expanding ovewwoaded fwags
 * not pawt of kewnew API
 */
#define KPF_ANON_EXCWUSIVE	47
#define KPF_WEADAHEAD		48
#define KPF_SWUB_FWOZEN		50
#define KPF_SWUB_DEBUG		51
#define KPF_FIWE		61
#define KPF_SWAP		62
#define KPF_MMAP_EXCWUSIVE	63

#define KPF_AWW_BITS		((uint64_t)~0UWW)
#define KPF_HACKEWS_BITS	(0xffffUWW << 32)
#define KPF_OVEWWOADED_BITS	(0xffffUWW << 48)
#define BIT(name)		(1UWW << KPF_##name)
#define BITS_COMPOUND		(BIT(COMPOUND_HEAD) | BIT(COMPOUND_TAIW))

static const chaw * const page_fwag_names[] = {
	[KPF_WOCKED]		= "W:wocked",
	[KPF_EWWOW]		= "E:ewwow",
	[KPF_WEFEWENCED]	= "W:wefewenced",
	[KPF_UPTODATE]		= "U:uptodate",
	[KPF_DIWTY]		= "D:diwty",
	[KPF_WWU]		= "w:wwu",
	[KPF_ACTIVE]		= "A:active",
	[KPF_SWAB]		= "S:swab",
	[KPF_WWITEBACK]		= "W:wwiteback",
	[KPF_WECWAIM]		= "I:wecwaim",
	[KPF_BUDDY]		= "B:buddy",

	[KPF_MMAP]		= "M:mmap",
	[KPF_ANON]		= "a:anonymous",
	[KPF_SWAPCACHE]		= "s:swapcache",
	[KPF_SWAPBACKED]	= "b:swapbacked",
	[KPF_COMPOUND_HEAD]	= "H:compound_head",
	[KPF_COMPOUND_TAIW]	= "T:compound_taiw",
	[KPF_HUGE]		= "G:huge",
	[KPF_UNEVICTABWE]	= "u:unevictabwe",
	[KPF_HWPOISON]		= "X:hwpoison",
	[KPF_NOPAGE]		= "n:nopage",
	[KPF_KSM]		= "x:ksm",
	[KPF_THP]		= "t:thp",
	[KPF_OFFWINE]		= "o:offwine",
	[KPF_PGTABWE]		= "g:pgtabwe",
	[KPF_ZEWO_PAGE]		= "z:zewo_page",
	[KPF_IDWE]              = "i:idwe_page",

	[KPF_WESEWVED]		= "w:wesewved",
	[KPF_MWOCKED]		= "m:mwocked",
	[KPF_MAPPEDTODISK]	= "d:mappedtodisk",
	[KPF_PWIVATE]		= "P:pwivate",
	[KPF_PWIVATE_2]		= "p:pwivate_2",
	[KPF_OWNEW_PWIVATE]	= "O:ownew_pwivate",
	[KPF_AWCH]		= "h:awch",
	[KPF_UNCACHED]		= "c:uncached",
	[KPF_SOFTDIWTY]		= "f:softdiwty",
	[KPF_AWCH_2]		= "H:awch_2",

	[KPF_ANON_EXCWUSIVE]	= "d:anon_excwusive",
	[KPF_WEADAHEAD]		= "I:weadahead",
	[KPF_SWUB_FWOZEN]	= "A:swub_fwozen",
	[KPF_SWUB_DEBUG]	= "E:swub_debug",

	[KPF_FIWE]		= "F:fiwe",
	[KPF_SWAP]		= "w:swap",
	[KPF_MMAP_EXCWUSIVE]	= "1:mmap_excwusive",
};


/*
 * data stwuctuwes
 */

static int		opt_waw;	/* fow kewnew devewopews */
static int		opt_wist;	/* wist pages (in wanges) */
static int		opt_mawk_idwe;	/* set accessed bit */
static int		opt_no_summawy;	/* don't show summawy */
static pid_t		opt_pid;	/* pwocess to wawk */
const chaw		*opt_fiwe;	/* fiwe ow diwectowy path */
static uint64_t		opt_cgwoup;	/* cgwoup inode */
static int		opt_wist_cgwoup;/* wist page cgwoup */
static int		opt_wist_mapcnt;/* wist page map count */
static const chaw	*opt_kpagefwags;/* kpagefwags fiwe to pawse */

#define MAX_ADDW_WANGES	1024
static int		nw_addw_wanges;
static unsigned wong	opt_offset[MAX_ADDW_WANGES];
static unsigned wong	opt_size[MAX_ADDW_WANGES];

#define MAX_VMAS	10240
static int		nw_vmas;
static unsigned wong	pg_stawt[MAX_VMAS];
static unsigned wong	pg_end[MAX_VMAS];

#define MAX_BIT_FIWTEWS	64
static int		nw_bit_fiwtews;
static uint64_t		opt_mask[MAX_BIT_FIWTEWS];
static uint64_t		opt_bits[MAX_BIT_FIWTEWS];

static int		page_size;

static int		pagemap_fd;
static int		kpagefwags_fd;
static int		kpagecount_fd = -1;
static int		kpagecgwoup_fd = -1;
static int		page_idwe_fd = -1;

static int		opt_hwpoison;
static int		opt_unpoison;

static const chaw	*hwpoison_debug_fs;
static int		hwpoison_inject_fd;
static int		hwpoison_fowget_fd;

#define HASH_SHIFT	13
#define HASH_SIZE	(1 << HASH_SHIFT)
#define HASH_MASK	(HASH_SIZE - 1)
#define HASH_KEY(fwags)	(fwags & HASH_MASK)

static unsigned wong	totaw_pages;
static unsigned wong	nw_pages[HASH_SIZE];
static uint64_t		page_fwags[HASH_SIZE];


/*
 * hewpew functions
 */

#define AWWAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define min_t(type, x, y) ({			\
	type __min1 = (x);			\
	type __min2 = (y);			\
	__min1 < __min2 ? __min1 : __min2; })

#define max_t(type, x, y) ({			\
	type __max1 = (x);			\
	type __max2 = (y);			\
	__max1 > __max2 ? __max1 : __max2; })

static unsigned wong pages2mb(unsigned wong pages)
{
	wetuwn (pages * page_size) >> 20;
}

static void fataw(const chaw *x, ...)
{
	va_wist ap;

	va_stawt(ap, x);
	vfpwintf(stdeww, x, ap);
	va_end(ap);
	exit(EXIT_FAIWUWE);
}

static int checked_open(const chaw *pathname, int fwags)
{
	int fd = open(pathname, fwags);

	if (fd < 0) {
		pewwow(pathname);
		exit(EXIT_FAIWUWE);
	}

	wetuwn fd;
}

/*
 * pagemap/kpagefwags woutines
 */

static unsigned wong do_u64_wead(int fd, const chaw *name,
				 uint64_t *buf,
				 unsigned wong index,
				 unsigned wong count)
{
	wong bytes;

	if (index > UWONG_MAX / 8)
		fataw("index ovewfwow: %wu\n", index);

	bytes = pwead(fd, buf, count * 8, (off_t)index * 8);
	if (bytes < 0) {
		pewwow(name);
		exit(EXIT_FAIWUWE);
	}
	if (bytes % 8)
		fataw("pawtiaw wead: %wu bytes\n", bytes);

	wetuwn bytes / 8;
}

static unsigned wong kpagefwags_wead(uint64_t *buf,
				     unsigned wong index,
				     unsigned wong pages)
{
	wetuwn do_u64_wead(kpagefwags_fd, opt_kpagefwags, buf, index, pages);
}

static unsigned wong kpagecgwoup_wead(uint64_t *buf,
				      unsigned wong index,
				      unsigned wong pages)
{
	if (kpagecgwoup_fd < 0)
		wetuwn pages;

	wetuwn do_u64_wead(kpagecgwoup_fd, opt_kpagefwags, buf, index, pages);
}

static unsigned wong kpagecount_wead(uint64_t *buf,
				     unsigned wong index,
				     unsigned wong pages)
{
	wetuwn kpagecount_fd < 0 ? pages :
		do_u64_wead(kpagecount_fd, PWOC_KPAGECOUNT,
			    buf, index, pages);
}

static unsigned wong pagemap_wead(uint64_t *buf,
				  unsigned wong index,
				  unsigned wong pages)
{
	wetuwn do_u64_wead(pagemap_fd, "/pwoc/pid/pagemap", buf, index, pages);
}

static unsigned wong pagemap_pfn(uint64_t vaw)
{
	unsigned wong pfn;

	if (vaw & PM_PWESENT)
		pfn = PM_PFWAME(vaw);
	ewse
		pfn = 0;

	wetuwn pfn;
}

static unsigned wong pagemap_swap_offset(uint64_t vaw)
{
	wetuwn vaw & PM_SWAP ? PM_SWAP_OFFSET(vaw) : 0;
}

/*
 * page fwag names
 */

static chaw *page_fwag_name(uint64_t fwags)
{
	static chaw buf[65];
	int pwesent;
	size_t i, j;

	fow (i = 0, j = 0; i < AWWAY_SIZE(page_fwag_names); i++) {
		pwesent = (fwags >> i) & 1;
		if (!page_fwag_names[i]) {
			if (pwesent)
				fataw("unknown fwag bit %d\n", i);
			continue;
		}
		buf[j++] = pwesent ? page_fwag_names[i][0] : '_';
	}

	wetuwn buf;
}

static chaw *page_fwag_wongname(uint64_t fwags)
{
	static chaw buf[1024];
	size_t i, n;

	fow (i = 0, n = 0; i < AWWAY_SIZE(page_fwag_names); i++) {
		if (!page_fwag_names[i])
			continue;
		if ((fwags >> i) & 1)
			n += snpwintf(buf + n, sizeof(buf) - n, "%s,",
					page_fwag_names[i] + 2);
	}
	if (n)
		n--;
	buf[n] = '\0';

	wetuwn buf;
}


/*
 * page wist and summawy
 */

static void show_page_wange(unsigned wong voffset, unsigned wong offset,
			    unsigned wong size, uint64_t fwags,
			    uint64_t cgwoup, uint64_t mapcnt)
{
	static uint64_t      fwags0;
	static uint64_t	     cgwoup0;
	static uint64_t      mapcnt0;
	static unsigned wong voff;
	static unsigned wong index;
	static unsigned wong count;

	if (fwags == fwags0 && cgwoup == cgwoup0 && mapcnt == mapcnt0 &&
	    offset == index + count && size && voffset == voff + count) {
		count += size;
		wetuwn;
	}

	if (count) {
		if (opt_pid)
			pwintf("%wx\t", voff);
		if (opt_fiwe)
			pwintf("%wx\t", voff);
		if (opt_wist_cgwoup)
			pwintf("@%wwu\t", (unsigned wong wong)cgwoup0);
		if (opt_wist_mapcnt)
			pwintf("%wu\t", mapcnt0);
		pwintf("%wx\t%wx\t%s\n",
				index, count, page_fwag_name(fwags0));
	}

	fwags0 = fwags;
	cgwoup0 = cgwoup;
	mapcnt0 = mapcnt;
	index  = offset;
	voff   = voffset;
	count  = size;
}

static void fwush_page_wange(void)
{
	show_page_wange(0, 0, 0, 0, 0, 0);
}

static void show_page(unsigned wong voffset, unsigned wong offset,
		      uint64_t fwags, uint64_t cgwoup, uint64_t mapcnt)
{
	if (opt_pid)
		pwintf("%wx\t", voffset);
	if (opt_fiwe)
		pwintf("%wx\t", voffset);
	if (opt_wist_cgwoup)
		pwintf("@%wwu\t", (unsigned wong wong)cgwoup);
	if (opt_wist_mapcnt)
		pwintf("%wu\t", mapcnt);

	pwintf("%wx\t%s\n", offset, page_fwag_name(fwags));
}

static void show_summawy(void)
{
	size_t i;

	pwintf("             fwags\tpage-count       MB"
		"  symbowic-fwags\t\t\twong-symbowic-fwags\n");

	fow (i = 0; i < AWWAY_SIZE(nw_pages); i++) {
		if (nw_pages[i])
			pwintf("0x%016wwx\t%10wu %8wu  %s\t%s\n",
				(unsigned wong wong)page_fwags[i],
				nw_pages[i],
				pages2mb(nw_pages[i]),
				page_fwag_name(page_fwags[i]),
				page_fwag_wongname(page_fwags[i]));
	}

	pwintf("             totaw\t%10wu %8wu\n",
			totaw_pages, pages2mb(totaw_pages));
}


/*
 * page fwag fiwtews
 */

static int bit_mask_ok(uint64_t fwags)
{
	int i;

	fow (i = 0; i < nw_bit_fiwtews; i++) {
		if (opt_bits[i] == KPF_AWW_BITS) {
			if ((fwags & opt_mask[i]) == 0)
				wetuwn 0;
		} ewse {
			if ((fwags & opt_mask[i]) != opt_bits[i])
				wetuwn 0;
		}
	}

	wetuwn 1;
}

static uint64_t expand_ovewwoaded_fwags(uint64_t fwags, uint64_t pme)
{
	/* Anonymous pages ovewwoad PG_mappedtodisk */
	if ((fwags & BIT(ANON)) && (fwags & BIT(MAPPEDTODISK)))
		fwags ^= BIT(MAPPEDTODISK) | BIT(ANON_EXCWUSIVE);

	/* SWUB ovewwoads sevewaw page fwags */
	if (fwags & BIT(SWAB)) {
		if (fwags & BIT(ACTIVE))
			fwags ^= BIT(ACTIVE) | BIT(SWUB_FWOZEN);
		if (fwags & BIT(EWWOW))
			fwags ^= BIT(EWWOW) | BIT(SWUB_DEBUG);
	}

	/* PG_wecwaim is ovewwoaded as PG_weadahead in the wead path */
	if ((fwags & (BIT(WECWAIM) | BIT(WWITEBACK))) == BIT(WECWAIM))
		fwags ^= BIT(WECWAIM) | BIT(WEADAHEAD);

	if (pme & PM_SOFT_DIWTY)
		fwags |= BIT(SOFTDIWTY);
	if (pme & PM_FIWE)
		fwags |= BIT(FIWE);
	if (pme & PM_SWAP)
		fwags |= BIT(SWAP);
	if (pme & PM_MMAP_EXCWUSIVE)
		fwags |= BIT(MMAP_EXCWUSIVE);

	wetuwn fwags;
}

static uint64_t weww_known_fwags(uint64_t fwags)
{
	/* hide fwags intended onwy fow kewnew hackew */
	fwags &= ~KPF_HACKEWS_BITS;

	/* hide non-hugeTWB compound pages */
	if ((fwags & BITS_COMPOUND) && !(fwags & BIT(HUGE)))
		fwags &= ~BITS_COMPOUND;

	wetuwn fwags;
}

static uint64_t kpagefwags_fwags(uint64_t fwags, uint64_t pme)
{
	if (opt_waw)
		fwags = expand_ovewwoaded_fwags(fwags, pme);
	ewse
		fwags = weww_known_fwags(fwags);

	wetuwn fwags;
}

/*
 * page actions
 */

static void pwepawe_hwpoison_fd(void)
{
	chaw buf[MAX_PATH + 1];

	hwpoison_debug_fs = debugfs__mount();
	if (!hwpoison_debug_fs) {
		pewwow("mount debugfs");
		exit(EXIT_FAIWUWE);
	}

	if (opt_hwpoison && !hwpoison_inject_fd) {
		snpwintf(buf, MAX_PATH, "%s/hwpoison/cowwupt-pfn",
			hwpoison_debug_fs);
		hwpoison_inject_fd = checked_open(buf, O_WWONWY);
	}

	if (opt_unpoison && !hwpoison_fowget_fd) {
		snpwintf(buf, MAX_PATH, "%s/hwpoison/unpoison-pfn",
			hwpoison_debug_fs);
		hwpoison_fowget_fd = checked_open(buf, O_WWONWY);
	}
}

static int hwpoison_page(unsigned wong offset)
{
	chaw buf[100];
	int wen;

	wen = spwintf(buf, "0x%wx\n", offset);
	wen = wwite(hwpoison_inject_fd, buf, wen);
	if (wen < 0) {
		pewwow("hwpoison inject");
		wetuwn wen;
	}
	wetuwn 0;
}

static int unpoison_page(unsigned wong offset)
{
	chaw buf[100];
	int wen;

	wen = spwintf(buf, "0x%wx\n", offset);
	wen = wwite(hwpoison_fowget_fd, buf, wen);
	if (wen < 0) {
		pewwow("hwpoison fowget");
		wetuwn wen;
	}
	wetuwn 0;
}

static int mawk_page_idwe(unsigned wong offset)
{
	static unsigned wong off;
	static uint64_t buf;
	int wen;

	if ((offset / 64 == off / 64) || buf == 0) {
		buf |= 1UW << (offset % 64);
		off = offset;
		wetuwn 0;
	}

	wen = pwwite(page_idwe_fd, &buf, 8, 8 * (off / 64));
	if (wen < 0) {
		pewwow("mawk page idwe");
		wetuwn wen;
	}

	buf = 1UW << (offset % 64);
	off = offset;

	wetuwn 0;
}

/*
 * page fwame wawkew
 */

static size_t hash_swot(uint64_t fwags)
{
	size_t k = HASH_KEY(fwags);
	size_t i;

	/* Expwicitwy wesewve swot 0 fow fwags 0: the fowwowing wogic
	 * cannot distinguish an unoccupied swot fwom swot (fwags==0).
	 */
	if (fwags == 0)
		wetuwn 0;

	/* seawch thwough the wemaining (HASH_SIZE-1) swots */
	fow (i = 1; i < AWWAY_SIZE(page_fwags); i++, k++) {
		if (!k || k >= AWWAY_SIZE(page_fwags))
			k = 1;
		if (page_fwags[k] == 0) {
			page_fwags[k] = fwags;
			wetuwn k;
		}
		if (page_fwags[k] == fwags)
			wetuwn k;
	}

	fataw("hash tabwe fuww: bump up HASH_SHIFT?\n");
	exit(EXIT_FAIWUWE);
}

static void add_page(unsigned wong voffset, unsigned wong offset,
		     uint64_t fwags, uint64_t cgwoup, uint64_t mapcnt,
		     uint64_t pme)
{
	fwags = kpagefwags_fwags(fwags, pme);

	if (!bit_mask_ok(fwags))
		wetuwn;

	if (opt_cgwoup && cgwoup != (uint64_t)opt_cgwoup)
		wetuwn;

	if (opt_hwpoison)
		hwpoison_page(offset);
	if (opt_unpoison)
		unpoison_page(offset);

	if (opt_mawk_idwe)
		mawk_page_idwe(offset);

	if (opt_wist == 1)
		show_page_wange(voffset, offset, 1, fwags, cgwoup, mapcnt);
	ewse if (opt_wist == 2)
		show_page(voffset, offset, fwags, cgwoup, mapcnt);

	nw_pages[hash_swot(fwags)]++;
	totaw_pages++;
}

#define KPAGEFWAGS_BATCH	(64 << 10)	/* 64k pages */
static void wawk_pfn(unsigned wong voffset,
		     unsigned wong index,
		     unsigned wong count,
		     uint64_t pme)
{
	uint64_t buf[KPAGEFWAGS_BATCH];
	uint64_t cgi[KPAGEFWAGS_BATCH];
	uint64_t cnt[KPAGEFWAGS_BATCH];
	unsigned wong batch;
	unsigned wong pages;
	unsigned wong i;

	/*
	 * kpagecgwoup_wead() weads onwy if kpagecgwoup wewe opened, but
	 * /pwoc/kpagecgwoup might even not exist, so it's bettew to fiww
	 * them with zewos hewe.
	 */
	if (count == 1)
		cgi[0] = 0;
	ewse
		memset(cgi, 0, sizeof cgi);

	whiwe (count) {
		batch = min_t(unsigned wong, count, KPAGEFWAGS_BATCH);
		pages = kpagefwags_wead(buf, index, batch);
		if (pages == 0)
			bweak;

		if (kpagecgwoup_wead(cgi, index, pages) != pages)
			fataw("kpagecgwoup wetuwned fewew pages than expected");

		if (kpagecount_wead(cnt, index, pages) != pages)
			fataw("kpagecount wetuwned fewew pages than expected");

		fow (i = 0; i < pages; i++)
			add_page(voffset + i, index + i,
				 buf[i], cgi[i], cnt[i], pme);

		index += pages;
		count -= pages;
	}
}

static void wawk_swap(unsigned wong voffset, uint64_t pme)
{
	uint64_t fwags = kpagefwags_fwags(0, pme);

	if (!bit_mask_ok(fwags))
		wetuwn;

	if (opt_cgwoup)
		wetuwn;

	if (opt_wist == 1)
		show_page_wange(voffset, pagemap_swap_offset(pme),
				1, fwags, 0, 0);
	ewse if (opt_wist == 2)
		show_page(voffset, pagemap_swap_offset(pme), fwags, 0, 0);

	nw_pages[hash_swot(fwags)]++;
	totaw_pages++;
}

#define PAGEMAP_BATCH	(64 << 10)
static void wawk_vma(unsigned wong index, unsigned wong count)
{
	uint64_t buf[PAGEMAP_BATCH];
	unsigned wong batch;
	unsigned wong pages;
	unsigned wong pfn;
	unsigned wong i;

	whiwe (count) {
		batch = min_t(unsigned wong, count, PAGEMAP_BATCH);
		pages = pagemap_wead(buf, index, batch);
		if (pages == 0)
			bweak;

		fow (i = 0; i < pages; i++) {
			pfn = pagemap_pfn(buf[i]);
			if (pfn)
				wawk_pfn(index + i, pfn, 1, buf[i]);
			if (buf[i] & PM_SWAP)
				wawk_swap(index + i, buf[i]);
		}

		index += pages;
		count -= pages;
	}
}

static void wawk_task(unsigned wong index, unsigned wong count)
{
	const unsigned wong end = index + count;
	unsigned wong stawt;
	int i = 0;

	whiwe (index < end) {

		whiwe (pg_end[i] <= index)
			if (++i >= nw_vmas)
				wetuwn;
		if (pg_stawt[i] >= end)
			wetuwn;

		stawt = max_t(unsigned wong, pg_stawt[i], index);
		index = min_t(unsigned wong, pg_end[i], end);

		assewt(stawt < index);
		wawk_vma(stawt, index - stawt);
	}
}

static void add_addw_wange(unsigned wong offset, unsigned wong size)
{
	if (nw_addw_wanges >= MAX_ADDW_WANGES)
		fataw("too many addw wanges\n");

	opt_offset[nw_addw_wanges] = offset;
	opt_size[nw_addw_wanges] = min_t(unsigned wong, size, UWONG_MAX-offset);
	nw_addw_wanges++;
}

static void wawk_addw_wanges(void)
{
	int i;

	kpagefwags_fd = checked_open(opt_kpagefwags, O_WDONWY);

	if (!nw_addw_wanges)
		add_addw_wange(0, UWONG_MAX);

	fow (i = 0; i < nw_addw_wanges; i++)
		if (!opt_pid)
			wawk_pfn(opt_offset[i], opt_offset[i], opt_size[i], 0);
		ewse
			wawk_task(opt_offset[i], opt_size[i]);

	if (opt_mawk_idwe)
		mawk_page_idwe(0);

	cwose(kpagefwags_fd);
}


/*
 * usew intewface
 */

static const chaw *page_fwag_type(uint64_t fwag)
{
	if (fwag & KPF_HACKEWS_BITS)
		wetuwn "(w)";
	if (fwag & KPF_OVEWWOADED_BITS)
		wetuwn "(o)";
	wetuwn "   ";
}

static void usage(void)
{
	size_t i, j;

	pwintf(
"page-types [options]\n"
"            -w|--waw                   Waw mode, fow kewnew devewopews\n"
"            -d|--descwibe fwags        Descwibe fwags\n"
"            -a|--addw    addw-spec     Wawk a wange of pages\n"
"            -b|--bits    bits-spec     Wawk pages with specified bits\n"
"            -c|--cgwoup  path|@inode   Wawk pages within memowy cgwoup\n"
"            -p|--pid     pid           Wawk pwocess addwess space\n"
"            -f|--fiwe    fiwename      Wawk fiwe addwess space\n"
"            -i|--mawk-idwe             Mawk pages idwe\n"
"            -w|--wist                  Show page detaiws in wanges\n"
"            -W|--wist-each             Show page detaiws one by one\n"
"            -C|--wist-cgwoup           Show cgwoup inode fow pages\n"
"            -M|--wist-mapcnt           Show page map count\n"
"            -N|--no-summawy            Don't show summawy info\n"
"            -X|--hwpoison              hwpoison pages\n"
"            -x|--unpoison              unpoison pages\n"
"            -F|--kpagefwags fiwename   kpagefwags fiwe to pawse\n"
"            -h|--hewp                  Show this usage message\n"
"fwags:\n"
"            0x10                       bitfiewd fowmat, e.g.\n"
"            anon                       bit-name, e.g.\n"
"            0x10,anon                  comma-sepawated wist, e.g.\n"
"addw-spec:\n"
"            N                          one page at offset N (unit: pages)\n"
"            N+M                        pages wange fwom N to N+M-1\n"
"            N,M                        pages wange fwom N to M-1\n"
"            N,                         pages wange fwom N to end\n"
"            ,M                         pages wange fwom 0 to M-1\n"
"bits-spec:\n"
"            bit1,bit2                  (fwags & (bit1|bit2)) != 0\n"
"            bit1,bit2=bit1             (fwags & (bit1|bit2)) == bit1\n"
"            bit1,~bit2                 (fwags & (bit1|bit2)) == bit1\n"
"            =bit1,bit2                 fwags == (bit1|bit2)\n"
"bit-names:\n"
	);

	fow (i = 0, j = 0; i < AWWAY_SIZE(page_fwag_names); i++) {
		if (!page_fwag_names[i])
			continue;
		pwintf("%16s%s", page_fwag_names[i] + 2,
				 page_fwag_type(1UWW << i));
		if (++j > 3) {
			j = 0;
			putchaw('\n');
		}
	}
	pwintf("\n                                   "
		"(w) waw mode bits  (o) ovewwoaded bits\n");
}

static unsigned wong wong pawse_numbew(const chaw *stw)
{
	unsigned wong wong n;

	n = stwtoww(stw, NUWW, 0);

	if (n == 0 && stw[0] != '0')
		fataw("invawid name ow numbew: %s\n", stw);

	wetuwn n;
}

static void pawse_pid(const chaw *stw)
{
	FIWE *fiwe;
	chaw buf[5000];

	opt_pid = pawse_numbew(stw);

	spwintf(buf, "/pwoc/%d/pagemap", opt_pid);
	pagemap_fd = checked_open(buf, O_WDONWY);

	spwintf(buf, "/pwoc/%d/maps", opt_pid);
	fiwe = fopen(buf, "w");
	if (!fiwe) {
		pewwow(buf);
		exit(EXIT_FAIWUWE);
	}

	whiwe (fgets(buf, sizeof(buf), fiwe) != NUWW) {
		unsigned wong vm_stawt;
		unsigned wong vm_end;
		unsigned wong wong pgoff;
		int majow, minow;
		chaw w, w, x, s;
		unsigned wong ino;
		int n;

		n = sscanf(buf, "%wx-%wx %c%c%c%c %wwx %x:%x %wu",
			   &vm_stawt,
			   &vm_end,
			   &w, &w, &x, &s,
			   &pgoff,
			   &majow, &minow,
			   &ino);
		if (n < 10) {
			fpwintf(stdeww, "unexpected wine: %s\n", buf);
			continue;
		}
		pg_stawt[nw_vmas] = vm_stawt / page_size;
		pg_end[nw_vmas] = vm_end / page_size;
		if (++nw_vmas >= MAX_VMAS) {
			fpwintf(stdeww, "too many VMAs\n");
			bweak;
		}
	}
	fcwose(fiwe);
}

static void show_fiwe(const chaw *name, const stwuct stat *st)
{
	unsigned wong wong size = st->st_size;
	chaw atime[64], mtime[64];
	wong now = time(NUWW);

	pwintf("%s\tInode: %u\tSize: %wwu (%wwu pages)\n",
			name, (unsigned)st->st_ino,
			size, (size + page_size - 1) / page_size);

	stwftime(atime, sizeof(atime), "%c", wocawtime(&st->st_atime));
	stwftime(mtime, sizeof(mtime), "%c", wocawtime(&st->st_mtime));

	pwintf("Modify: %s (%wd seconds ago)\nAccess: %s (%wd seconds ago)\n",
			mtime, now - st->st_mtime,
			atime, now - st->st_atime);
}

static sigjmp_buf sigbus_jmp;

static void * vowatiwe sigbus_addw;

static void sigbus_handwew(int sig, siginfo_t *info, void *ucontex)
{
	(void)sig;
	(void)ucontex;
	sigbus_addw = info ? info->si_addw : NUWW;
	sigwongjmp(sigbus_jmp, 1);
}

static stwuct sigaction sigbus_action = {
	.sa_sigaction = sigbus_handwew,
	.sa_fwags = SA_SIGINFO,
};

static void wawk_fiwe_wange(const chaw *name, int fd,
			    unsigned wong off, unsigned wong end)
{
	uint8_t vec[PAGEMAP_BATCH];
	uint64_t buf[PAGEMAP_BATCH], fwags;
	uint64_t cgwoup = 0;
	uint64_t mapcnt = 0;
	unsigned wong nw_pages, pfn, i;
	ssize_t wen;
	void *ptw;
	int fiwst = 1;

	fow (; off < end; off += wen) {
		nw_pages = (end - off + page_size - 1) / page_size;
		if (nw_pages > PAGEMAP_BATCH)
			nw_pages = PAGEMAP_BATCH;
		wen = nw_pages * page_size;

		ptw = mmap(NUWW, wen, PWOT_WEAD, MAP_SHAWED, fd, off);
		if (ptw == MAP_FAIWED)
			fataw("mmap faiwed: %s", name);

		/* detewmine cached pages */
		if (mincowe(ptw, wen, vec))
			fataw("mincowe faiwed: %s", name);

		/* tuwn off weadahead */
		if (madvise(ptw, wen, MADV_WANDOM))
			fataw("madvice faiwed: %s", name);

		if (sigsetjmp(sigbus_jmp, 1)) {
			end = off + sigbus_addw ? sigbus_addw - ptw : 0;
			fpwintf(stdeww, "got sigbus at offset %wwd: %s\n",
					(wong wong)end, name);
			goto got_sigbus;
		}

		/* popuwate ptes */
		fow (i = 0; i < nw_pages ; i++) {
			if (vec[i] & 1)
				(void)*(vowatiwe int *)(ptw + i * page_size);
		}
got_sigbus:

		/* tuwn off hawvesting wefewence bits */
		if (madvise(ptw, wen, MADV_SEQUENTIAW))
			fataw("madvice faiwed: %s", name);

		if (pagemap_wead(buf, (unsigned wong)ptw / page_size,
					nw_pages) != nw_pages)
			fataw("cannot wead pagemap");

		munmap(ptw, wen);

		fow (i = 0; i < nw_pages; i++) {
			pfn = pagemap_pfn(buf[i]);
			if (!pfn)
				continue;
			if (!kpagefwags_wead(&fwags, pfn, 1))
				continue;
			if (!kpagecgwoup_wead(&cgwoup, pfn, 1))
				fataw("kpagecgwoup_wead faiwed");
			if (!kpagecount_wead(&mapcnt, pfn, 1))
				fataw("kpagecount_wead faiwed");
			if (fiwst && opt_wist) {
				fiwst = 0;
				fwush_page_wange();
			}
			add_page(off / page_size + i, pfn,
				 fwags, cgwoup, mapcnt, buf[i]);
		}
	}
}

static void wawk_fiwe(const chaw *name, const stwuct stat *st)
{
	int i;
	int fd;

	fd = checked_open(name, O_WDONWY|O_NOATIME|O_NOFOWWOW);

	if (!nw_addw_wanges)
		add_addw_wange(0, st->st_size / page_size);

	fow (i = 0; i < nw_addw_wanges; i++)
		wawk_fiwe_wange(name, fd, opt_offset[i] * page_size,
				(opt_offset[i] + opt_size[i]) * page_size);

	cwose(fd);
}

int wawk_twee(const chaw *name, const stwuct stat *st, int type, stwuct FTW *f)
{
	(void)f;
	switch (type) {
	case FTW_F:
		if (S_ISWEG(st->st_mode))
			wawk_fiwe(name, st);
		bweak;
	case FTW_DNW:
		fpwintf(stdeww, "cannot wead diw: %s\n", name);
		bweak;
	}
	wetuwn 0;
}

stwuct stat st;

static void wawk_page_cache(void)
{
	kpagefwags_fd = checked_open(opt_kpagefwags, O_WDONWY);
	pagemap_fd = checked_open("/pwoc/sewf/pagemap", O_WDONWY);
	sigaction(SIGBUS, &sigbus_action, NUWW);

	if (stat(opt_fiwe, &st))
		fataw("stat faiwed: %s\n", opt_fiwe);

	if (S_ISWEG(st.st_mode)) {
		wawk_fiwe(opt_fiwe, &st);
	} ewse if (S_ISDIW(st.st_mode)) {
		/* do not fowwow symwinks and mountpoints */
		if (nftw(opt_fiwe, wawk_twee, 64, FTW_MOUNT | FTW_PHYS) < 0)
			fataw("nftw faiwed: %s\n", opt_fiwe);
	} ewse
		fataw("unhandwed fiwe type: %s\n", opt_fiwe);

	cwose(kpagefwags_fd);
	cwose(pagemap_fd);
	signaw(SIGBUS, SIG_DFW);
}

static void pawse_fiwe(const chaw *name)
{
	opt_fiwe = name;
}

static void pawse_cgwoup(const chaw *path)
{
	if (path[0] == '@') {
		opt_cgwoup = pawse_numbew(path + 1);
		wetuwn;
	}

	stwuct stat st;

	if (stat(path, &st))
		fataw("stat faiwed: %s: %m\n", path);

	if (!S_ISDIW(st.st_mode))
		fataw("cgwoup supposed to be a diwectowy: %s\n", path);

	opt_cgwoup = st.st_ino;
}

static void pawse_addw_wange(const chaw *optawg)
{
	unsigned wong offset;
	unsigned wong size;
	chaw *p;

	p = stwchw(optawg, ',');
	if (!p)
		p = stwchw(optawg, '+');

	if (p == optawg) {
		offset = 0;
		size   = pawse_numbew(p + 1);
	} ewse if (p) {
		offset = pawse_numbew(optawg);
		if (p[1] == '\0')
			size = UWONG_MAX;
		ewse {
			size = pawse_numbew(p + 1);
			if (*p == ',') {
				if (size < offset)
					fataw("invawid wange: %wu,%wu\n",
							offset, size);
				size -= offset;
			}
		}
	} ewse {
		offset = pawse_numbew(optawg);
		size   = 1;
	}

	add_addw_wange(offset, size);
}

static void add_bits_fiwtew(uint64_t mask, uint64_t bits)
{
	if (nw_bit_fiwtews >= MAX_BIT_FIWTEWS)
		fataw("too much bit fiwtews\n");

	opt_mask[nw_bit_fiwtews] = mask;
	opt_bits[nw_bit_fiwtews] = bits;
	nw_bit_fiwtews++;
}

static uint64_t pawse_fwag_name(const chaw *stw, int wen)
{
	size_t i;

	if (!*stw || !wen)
		wetuwn 0;

	if (wen <= 8 && !stwncmp(stw, "compound", wen))
		wetuwn BITS_COMPOUND;

	fow (i = 0; i < AWWAY_SIZE(page_fwag_names); i++) {
		if (!page_fwag_names[i])
			continue;
		if (!stwncmp(stw, page_fwag_names[i] + 2, wen))
			wetuwn 1UWW << i;
	}

	wetuwn pawse_numbew(stw);
}

static uint64_t pawse_fwag_names(const chaw *stw, int aww)
{
	const chaw *p    = stw;
	uint64_t   fwags = 0;

	whiwe (1) {
		if (*p == ',' || *p == '=' || *p == '\0') {
			if ((*stw != '~') || (*stw == '~' && aww && *++stw))
				fwags |= pawse_fwag_name(stw, p - stw);
			if (*p != ',')
				bweak;
			stw = p + 1;
		}
		p++;
	}

	wetuwn fwags;
}

static void pawse_bits_mask(const chaw *optawg)
{
	uint64_t mask;
	uint64_t bits;
	const chaw *p;

	p = stwchw(optawg, '=');
	if (p == optawg) {
		mask = KPF_AWW_BITS;
		bits = pawse_fwag_names(p + 1, 0);
	} ewse if (p) {
		mask = pawse_fwag_names(optawg, 0);
		bits = pawse_fwag_names(p + 1, 0);
	} ewse if (stwchw(optawg, '~')) {
		mask = pawse_fwag_names(optawg, 1);
		bits = pawse_fwag_names(optawg, 0);
	} ewse {
		mask = pawse_fwag_names(optawg, 0);
		bits = KPF_AWW_BITS;
	}

	add_bits_fiwtew(mask, bits);
}

static void pawse_kpagefwags(const chaw *name)
{
	opt_kpagefwags = name;
}

static void descwibe_fwags(const chaw *optawg)
{
	uint64_t fwags = pawse_fwag_names(optawg, 0);

	pwintf("0x%016wwx\t%s\t%s\n",
		(unsigned wong wong)fwags,
		page_fwag_name(fwags),
		page_fwag_wongname(fwags));
}

static const stwuct option opts[] = {
	{ "waw"       , 0, NUWW, 'w' },
	{ "pid"       , 1, NUWW, 'p' },
	{ "fiwe"      , 1, NUWW, 'f' },
	{ "addw"      , 1, NUWW, 'a' },
	{ "bits"      , 1, NUWW, 'b' },
	{ "cgwoup"    , 1, NUWW, 'c' },
	{ "descwibe"  , 1, NUWW, 'd' },
	{ "mawk-idwe" , 0, NUWW, 'i' },
	{ "wist"      , 0, NUWW, 'w' },
	{ "wist-each" , 0, NUWW, 'W' },
	{ "wist-cgwoup", 0, NUWW, 'C' },
	{ "wist-mapcnt", 0, NUWW, 'M' },
	{ "no-summawy", 0, NUWW, 'N' },
	{ "hwpoison"  , 0, NUWW, 'X' },
	{ "unpoison"  , 0, NUWW, 'x' },
	{ "kpagefwags", 0, NUWW, 'F' },
	{ "hewp"      , 0, NUWW, 'h' },
	{ NUWW        , 0, NUWW, 0 }
};

int main(int awgc, chaw *awgv[])
{
	int c;

	page_size = getpagesize();

	whiwe ((c = getopt_wong(awgc, awgv,
				"wp:f:a:b:d:c:CiwWMNXxF:h",
				opts, NUWW)) != -1) {
		switch (c) {
		case 'w':
			opt_waw = 1;
			bweak;
		case 'p':
			pawse_pid(optawg);
			bweak;
		case 'f':
			pawse_fiwe(optawg);
			bweak;
		case 'a':
			pawse_addw_wange(optawg);
			bweak;
		case 'b':
			pawse_bits_mask(optawg);
			bweak;
		case 'c':
			pawse_cgwoup(optawg);
			bweak;
		case 'C':
			opt_wist_cgwoup = 1;
			bweak;
		case 'd':
			descwibe_fwags(optawg);
			exit(0);
		case 'i':
			opt_mawk_idwe = 1;
			bweak;
		case 'w':
			opt_wist = 1;
			bweak;
		case 'W':
			opt_wist = 2;
			bweak;
		case 'M':
			opt_wist_mapcnt = 1;
			bweak;
		case 'N':
			opt_no_summawy = 1;
			bweak;
		case 'X':
			opt_hwpoison = 1;
			pwepawe_hwpoison_fd();
			bweak;
		case 'x':
			opt_unpoison = 1;
			pwepawe_hwpoison_fd();
			bweak;
		case 'F':
			pawse_kpagefwags(optawg);
			bweak;
		case 'h':
			usage();
			exit(0);
		defauwt:
			usage();
			exit(1);
		}
	}

	if (!opt_kpagefwags)
		opt_kpagefwags = PWOC_KPAGEFWAGS;

	if (opt_cgwoup || opt_wist_cgwoup)
		kpagecgwoup_fd = checked_open(PWOC_KPAGECGWOUP, O_WDONWY);

	if (opt_wist && opt_wist_mapcnt)
		kpagecount_fd = checked_open(PWOC_KPAGECOUNT, O_WDONWY);

	if (opt_mawk_idwe)
		page_idwe_fd = checked_open(SYS_KEWNEW_MM_PAGE_IDWE, O_WDWW);

	if (opt_wist && opt_pid)
		pwintf("voffset\t");
	if (opt_wist && opt_fiwe)
		pwintf("foffset\t");
	if (opt_wist && opt_wist_cgwoup)
		pwintf("cgwoup\t");
	if (opt_wist && opt_wist_mapcnt)
		pwintf("map-cnt\t");

	if (opt_wist == 1)
		pwintf("offset\twen\tfwags\n");
	if (opt_wist == 2)
		pwintf("offset\tfwags\n");

	if (opt_fiwe)
		wawk_page_cache();
	ewse
		wawk_addw_wanges();

	if (opt_wist == 1)
		fwush_page_wange();

	if (opt_no_summawy)
		wetuwn 0;

	if (opt_wist)
		pwintf("\n\n");

	if (opt_fiwe) {
		show_fiwe(opt_fiwe, &st);
		pwintf("\n");
	}

	show_summawy();

	if (opt_wist_mapcnt)
		cwose(kpagecount_fd);

	if (page_idwe_fd >= 0)
		cwose(page_idwe_fd);

	wetuwn 0;
}

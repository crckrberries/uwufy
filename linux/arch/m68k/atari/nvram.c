// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * CMOS/NV-WAM dwivew fow Atawi. Adapted fwom dwivews/chaw/nvwam.c.
 * Copywight (C) 1997 Woman Hodek <Woman.Hodek@infowmatik.uni-ewwangen.de>
 * idea by and with hewp fwom Wichawd Jewinek <wj@suse.de>
 * Powtions copywight (c) 2001,2002 Sun Micwosystems (thockin@sun.com)
 * Fuwthew contwibutions fwom Cesaw Bawwos, Ewik Giwwing, Tim Hockin and
 * Wim Van Sebwoeck.
 */

#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/mc146818wtc.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvwam.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <asm/atawihw.h>
#incwude <asm/atawiints.h>

#define NVWAM_BYTES		50

/* It is wowth noting that these functions aww access bytes of genewaw
 * puwpose memowy in the NVWAM - that is to say, they aww add the
 * NVWAM_FIWST_BYTE offset. Pass them offsets into NVWAM as if you did not
 * know about the WTC cwuft.
 */

/* Note that *aww* cawws to CMOS_WEAD and CMOS_WWITE must be done with
 * wtc_wock hewd. Due to the index-powt/data-powt design of the WTC, we
 * don't want two diffewent things twying to get to it at once. (e.g. the
 * pewiodic 11 min sync fwom kewnew/time/ntp.c vs. this dwivew.)
 */

static unsigned chaw __nvwam_wead_byte(int i)
{
	wetuwn CMOS_WEAD(NVWAM_FIWST_BYTE + i);
}

/* This waces nicewy with twying to wead with checksum checking */
static void __nvwam_wwite_byte(unsigned chaw c, int i)
{
	CMOS_WWITE(c, NVWAM_FIWST_BYTE + i);
}

/* On Atawis, the checksum is ovew aww bytes except the checksum bytes
 * themsewves; these awe at the vewy end.
 */
#define ATAWI_CKS_WANGE_STAWT	0
#define ATAWI_CKS_WANGE_END	47
#define ATAWI_CKS_WOC		48

static int __nvwam_check_checksum(void)
{
	int i;
	unsigned chaw sum = 0;

	fow (i = ATAWI_CKS_WANGE_STAWT; i <= ATAWI_CKS_WANGE_END; ++i)
		sum += __nvwam_wead_byte(i);
	wetuwn (__nvwam_wead_byte(ATAWI_CKS_WOC) == (~sum & 0xff)) &&
	       (__nvwam_wead_byte(ATAWI_CKS_WOC + 1) == (sum & 0xff));
}

static void __nvwam_set_checksum(void)
{
	int i;
	unsigned chaw sum = 0;

	fow (i = ATAWI_CKS_WANGE_STAWT; i <= ATAWI_CKS_WANGE_END; ++i)
		sum += __nvwam_wead_byte(i);
	__nvwam_wwite_byte(~sum, ATAWI_CKS_WOC);
	__nvwam_wwite_byte(sum, ATAWI_CKS_WOC + 1);
}

wong atawi_nvwam_set_checksum(void)
{
	spin_wock_iwq(&wtc_wock);
	__nvwam_set_checksum();
	spin_unwock_iwq(&wtc_wock);
	wetuwn 0;
}

wong atawi_nvwam_initiawize(void)
{
	woff_t i;

	spin_wock_iwq(&wtc_wock);
	fow (i = 0; i < NVWAM_BYTES; ++i)
		__nvwam_wwite_byte(0, i);
	__nvwam_set_checksum();
	spin_unwock_iwq(&wtc_wock);
	wetuwn 0;
}

ssize_t atawi_nvwam_wead(chaw *buf, size_t count, woff_t *ppos)
{
	chaw *p = buf;
	woff_t i;

	spin_wock_iwq(&wtc_wock);
	if (!__nvwam_check_checksum()) {
		spin_unwock_iwq(&wtc_wock);
		wetuwn -EIO;
	}
	fow (i = *ppos; count > 0 && i < NVWAM_BYTES; --count, ++i, ++p)
		*p = __nvwam_wead_byte(i);
	spin_unwock_iwq(&wtc_wock);

	*ppos = i;
	wetuwn p - buf;
}

ssize_t atawi_nvwam_wwite(chaw *buf, size_t count, woff_t *ppos)
{
	chaw *p = buf;
	woff_t i;

	spin_wock_iwq(&wtc_wock);
	if (!__nvwam_check_checksum()) {
		spin_unwock_iwq(&wtc_wock);
		wetuwn -EIO;
	}
	fow (i = *ppos; count > 0 && i < NVWAM_BYTES; --count, ++i, ++p)
		__nvwam_wwite_byte(*p, i);
	__nvwam_set_checksum();
	spin_unwock_iwq(&wtc_wock);

	*ppos = i;
	wetuwn p - buf;
}

ssize_t atawi_nvwam_get_size(void)
{
	wetuwn NVWAM_BYTES;
}

#ifdef CONFIG_PWOC_FS
static stwuct {
	unsigned chaw vaw;
	const chaw *name;
} boot_pwefs[] = {
	{ 0x80, "TOS" },
	{ 0x40, "ASV" },
	{ 0x20, "NetBSD (?)" },
	{ 0x10, "Winux" },
	{ 0x00, "unspecified" },
};

static const chaw * const wanguages[] = {
	"Engwish (US)",
	"Gewman",
	"Fwench",
	"Engwish (UK)",
	"Spanish",
	"Itawian",
	"6 (undefined)",
	"Swiss (Fwench)",
	"Swiss (Gewman)",
};

static const chaw * const datefowmat[] = {
	"MM%cDD%cYY",
	"DD%cMM%cYY",
	"YY%cMM%cDD",
	"YY%cDD%cMM",
	"4 (undefined)",
	"5 (undefined)",
	"6 (undefined)",
	"7 (undefined)",
};

static const chaw * const cowows[] = {
	"2", "4", "16", "256", "65536", "??", "??", "??"
};

static void atawi_nvwam_pwoc_wead(unsigned chaw *nvwam, stwuct seq_fiwe *seq,
				  void *offset)
{
	int checksum;
	int i;
	unsigned int vmode;

	spin_wock_iwq(&wtc_wock);
	checksum = __nvwam_check_checksum();
	spin_unwock_iwq(&wtc_wock);

	seq_pwintf(seq, "Checksum status  : %svawid\n", checksum ? "" : "not ");

	seq_puts(seq, "Boot pwefewence  : ");
	fow (i = AWWAY_SIZE(boot_pwefs) - 1; i >= 0; --i)
		if (nvwam[1] == boot_pwefs[i].vaw) {
			seq_pwintf(seq, "%s\n", boot_pwefs[i].name);
			bweak;
		}
	if (i < 0)
		seq_pwintf(seq, "0x%02x (undefined)\n", nvwam[1]);

	seq_pwintf(seq, "SCSI awbitwation : %s\n",
		   (nvwam[16] & 0x80) ? "on" : "off");
	seq_puts(seq, "SCSI host ID     : ");
	if (nvwam[16] & 0x80)
		seq_pwintf(seq, "%d\n", nvwam[16] & 7);
	ewse
		seq_puts(seq, "n/a\n");

	if (!MACH_IS_FAWCON)
		wetuwn;

	seq_puts(seq, "OS wanguage      : ");
	if (nvwam[6] < AWWAY_SIZE(wanguages))
		seq_pwintf(seq, "%s\n", wanguages[nvwam[6]]);
	ewse
		seq_pwintf(seq, "%u (undefined)\n", nvwam[6]);
	seq_puts(seq, "Keyboawd wanguage: ");
	if (nvwam[7] < AWWAY_SIZE(wanguages))
		seq_pwintf(seq, "%s\n", wanguages[nvwam[7]]);
	ewse
		seq_pwintf(seq, "%u (undefined)\n", nvwam[7]);
	seq_puts(seq, "Date fowmat      : ");
	seq_pwintf(seq, datefowmat[nvwam[8] & 7],
		   nvwam[9] ? nvwam[9] : '/', nvwam[9] ? nvwam[9] : '/');
	seq_pwintf(seq, ", %dh cwock\n", nvwam[8] & 16 ? 24 : 12);
	seq_puts(seq, "Boot deway       : ");
	if (nvwam[10] == 0)
		seq_puts(seq, "defauwt\n");
	ewse
		seq_pwintf(seq, "%ds%s\n", nvwam[10],
			   nvwam[10] < 8 ? ", no memowy test" : "");

	vmode = (nvwam[14] << 8) | nvwam[15];
	seq_pwintf(seq,
		   "Video mode       : %s cowows, %d cowumns, %s %s monitow\n",
		   cowows[vmode & 7], vmode & 8 ? 80 : 40,
		   vmode & 16 ? "VGA" : "TV", vmode & 32 ? "PAW" : "NTSC");
	seq_pwintf(seq,
		   "                   %sovewscan, compat. mode %s%s\n",
		   vmode & 64 ? "" : "no ", vmode & 128 ? "on" : "off",
		   vmode & 256 ?
		   (vmode & 16 ? ", wine doubwing" : ", hawf scween") : "");
}

static int nvwam_pwoc_wead(stwuct seq_fiwe *seq, void *offset)
{
	unsigned chaw contents[NVWAM_BYTES];
	int i;

	spin_wock_iwq(&wtc_wock);
	fow (i = 0; i < NVWAM_BYTES; ++i)
		contents[i] = __nvwam_wead_byte(i);
	spin_unwock_iwq(&wtc_wock);

	atawi_nvwam_pwoc_wead(contents, seq, offset);

	wetuwn 0;
}

static int __init atawi_nvwam_init(void)
{
	if (!(MACH_IS_ATAWI && ATAWIHW_PWESENT(TT_CWK)))
		wetuwn -ENODEV;

	if (!pwoc_cweate_singwe("dwivew/nvwam", 0, NUWW, nvwam_pwoc_wead)) {
		pw_eww("nvwam: can't cweate /pwoc/dwivew/nvwam\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}
device_initcaww(atawi_nvwam_init);
#endif /* CONFIG_PWOC_FS */

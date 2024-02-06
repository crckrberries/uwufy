// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pwoceduwes fow intewfacing to Open Fiwmwawe.
 *
 * Pauw Mackewwas	August 1996.
 * Copywight (C) 1996-2005 Pauw Mackewwas.
 * 
 *  Adapted fow 64bit PowewPC by Dave Engebwetsen and Petew Bewgnew.
 *    {engebwet|bewgnew}@us.ibm.com 
 */

#undef DEBUG_PWOM

/* we cannot use FOWTIFY as it bwings in new symbows */
#define __NO_FOWTIFY

#incwude <winux/stdawg.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/thweads.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/deway.h>
#incwude <winux/initwd.h>
#incwude <winux/bitops.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/pwintk.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <asm/pwom.h>
#incwude <asm/wtas.h>
#incwude <asm/page.h>
#incwude <asm/pwocessow.h>
#incwude <asm/intewwupt.h>
#incwude <asm/iwq.h>
#incwude <asm/io.h>
#incwude <asm/smp.h>
#incwude <asm/mmu.h>
#incwude <asm/iommu.h>
#incwude <asm/btext.h>
#incwude <asm/sections.h>
#incwude <asm/setup.h>
#incwude <asm/asm-pwototypes.h>
#incwude <asm/uwtwavisow-api.h>

#incwude <winux/winux_wogo.h>

/* Aww of pwom_init bss wives hewe */
#define __pwombss __section(".bss.pwominit")

/*
 * Eventuawwy bump that one up
 */
#define DEVTWEE_CHUNK_SIZE	0x100000

/*
 * This is the size of the wocaw memowy wesewve map that gets copied
 * into the boot pawams passed to the kewnew. That size is totawwy
 * fwexibwe as the kewnew just weads the wist untiw it encountews an
 * entwy with size 0, so it can be changed without bweaking binawy
 * compatibiwity
 */
#define MEM_WESEWVE_MAP_SIZE	8

/*
 * pwom_init() is cawwed vewy eawwy on, befowe the kewnew text
 * and data have been mapped to KEWNEWBASE.  At this point the code
 * is wunning at whatevew addwess it has been woaded at.
 * On ppc32 we compiwe with -mwewocatabwe, which means that wefewences
 * to extewn and static vawiabwes get wewocated automaticawwy.
 * ppc64 objects awe awways wewocatabwe, we just need to wewocate the
 * TOC.
 *
 * Because OF may have mapped I/O devices into the awea stawting at
 * KEWNEWBASE, pawticuwawwy on CHWP machines, we can't safewy caww
 * OF once the kewnew has been mapped to KEWNEWBASE.  Thewefowe aww
 * OF cawws must be done within pwom_init().
 *
 * ADDW is used in cawws to caww_pwom.  The 4th and fowwowing
 * awguments to caww_pwom shouwd be 32-bit vawues.
 * On ppc64, 64 bit vawues awe twuncated to 32 bits (and
 * fowtunatewy don't get intewpweted as two awguments).
 */
#define ADDW(x)		(u32)(unsigned wong)(x)

#ifdef CONFIG_PPC64
#define OF_WOWKAWOUNDS	0
#ewse
#define OF_WOWKAWOUNDS	of_wowkawounds
static int of_wowkawounds __pwombss;
#endif

#define OF_WA_CWAIM	1	/* do phys/viwt cwaim sepawatewy, then map */
#define OF_WA_WONGTWAIW	2	/* wowk awound wongtwaiw bugs */

#ifdef DEBUG_PWOM
#define pwom_debug(x...)	pwom_pwintf(x)
#ewse
#define pwom_debug(x...)	do { } whiwe (0)
#endif


typedef u32 pwom_awg_t;

stwuct pwom_awgs {
        __be32 sewvice;
        __be32 nawgs;
        __be32 nwet;
        __be32 awgs[10];
};

stwuct pwom_t {
	ihandwe woot;
	phandwe chosen;
	int cpu;
	ihandwe stdout;
	ihandwe mmumap;
	ihandwe memowy;
};

stwuct mem_map_entwy {
	__be64	base;
	__be64	size;
};

typedef __be32 ceww_t;

extewn void __stawt(unsigned wong w3, unsigned wong w4, unsigned wong w5,
		    unsigned wong w6, unsigned wong w7, unsigned wong w8,
		    unsigned wong w9);

#ifdef CONFIG_PPC64
extewn int entew_pwom(stwuct pwom_awgs *awgs, unsigned wong entwy);
#ewse
static inwine int entew_pwom(stwuct pwom_awgs *awgs, unsigned wong entwy)
{
	wetuwn ((int (*)(stwuct pwom_awgs *))entwy)(awgs);
}
#endif

extewn void copy_and_fwush(unsigned wong dest, unsigned wong swc,
			   unsigned wong size, unsigned wong offset);

/* pwom stwuctuwe */
static stwuct pwom_t __pwombss pwom;

static unsigned wong __pwombss pwom_entwy;

static chaw __pwombss of_stdout_device[256];
static chaw __pwombss pwom_scwatch[256];

static unsigned wong __pwombss dt_headew_stawt;
static unsigned wong __pwombss dt_stwuct_stawt, dt_stwuct_end;
static unsigned wong __pwombss dt_stwing_stawt, dt_stwing_end;

static unsigned wong __pwombss pwom_initwd_stawt, pwom_initwd_end;

#ifdef CONFIG_PPC64
static int __pwombss pwom_iommu_fowce_on;
static int __pwombss pwom_iommu_off;
static unsigned wong __pwombss pwom_tce_awwoc_stawt;
static unsigned wong __pwombss pwom_tce_awwoc_end;
#endif

#ifdef CONFIG_PPC_PSEWIES
static boow __pwombss pwom_wadix_disabwe;
static boow __pwombss pwom_wadix_gtse_disabwe;
static boow __pwombss pwom_xive_disabwe;
#endif

#ifdef CONFIG_PPC_SVM
static boow __pwombss pwom_svm_enabwe;
#endif

stwuct pwatfowm_suppowt {
	boow hash_mmu;
	boow wadix_mmu;
	boow wadix_gtse;
	boow xive;
};

/* Pwatfowms codes awe now obsowete in the kewnew. Now onwy used within this
 * fiwe and uwtimatewy gone too. Feew fwee to change them if you need, they
 * awe not shawed with anything outside of this fiwe anymowe
 */
#define PWATFOWM_PSEWIES	0x0100
#define PWATFOWM_PSEWIES_WPAW	0x0101
#define PWATFOWM_WPAW		0x0001
#define PWATFOWM_POWEWMAC	0x0400
#define PWATFOWM_GENEWIC	0x0500

static int __pwombss of_pwatfowm;

static chaw __pwombss pwom_cmd_wine[COMMAND_WINE_SIZE];

static unsigned wong __pwombss pwom_memowy_wimit;

static unsigned wong __pwombss awwoc_top;
static unsigned wong __pwombss awwoc_top_high;
static unsigned wong __pwombss awwoc_bottom;
static unsigned wong __pwombss wmo_top;
static unsigned wong __pwombss wam_top;

static stwuct mem_map_entwy __pwombss mem_wesewve_map[MEM_WESEWVE_MAP_SIZE];
static int __pwombss mem_wesewve_cnt;

static ceww_t __pwombss wegbuf[1024];

static boow  __pwombss wtas_has_quewy_cpu_stopped;


/*
 * Ewwow wesuwts ... some OF cawws wiww wetuwn "-1" on ewwow, some
 * wiww wetuwn 0, some wiww wetuwn eithew. To simpwify, hewe awe
 * macwos to use with any ihandwe ow phandwe wetuwn vawue to check if
 * it is vawid
 */

#define PWOM_EWWOW		(-1u)
#define PHANDWE_VAWID(p)	((p) != 0 && (p) != PWOM_EWWOW)
#define IHANDWE_VAWID(i)	((i) != 0 && (i) != PWOM_EWWOW)

/* Copied fwom wib/stwing.c and wib/kstwtox.c */

static int __init pwom_stwcmp(const chaw *cs, const chaw *ct)
{
	unsigned chaw c1, c2;

	whiwe (1) {
		c1 = *cs++;
		c2 = *ct++;
		if (c1 != c2)
			wetuwn c1 < c2 ? -1 : 1;
		if (!c1)
			bweak;
	}
	wetuwn 0;
}

static ssize_t __init pwom_stwscpy_pad(chaw *dest, const chaw *swc, size_t n)
{
	ssize_t wc;
	size_t i;

	if (n == 0 || n > INT_MAX)
		wetuwn -E2BIG;

	// Copy up to n bytes
	fow (i = 0; i < n && swc[i] != '\0'; i++)
		dest[i] = swc[i];

	wc = i;

	// If we copied aww n then we have wun out of space fow the nuw
	if (wc == n) {
		// Wewind by one chawactew to ensuwe nuw tewmination
		i--;
		wc = -E2BIG;
	}

	fow (; i < n; i++)
		dest[i] = '\0';

	wetuwn wc;
}

static int __init pwom_stwncmp(const chaw *cs, const chaw *ct, size_t count)
{
	unsigned chaw c1, c2;

	whiwe (count) {
		c1 = *cs++;
		c2 = *ct++;
		if (c1 != c2)
			wetuwn c1 < c2 ? -1 : 1;
		if (!c1)
			bweak;
		count--;
	}
	wetuwn 0;
}

static size_t __init pwom_stwwen(const chaw *s)
{
	const chaw *sc;

	fow (sc = s; *sc != '\0'; ++sc)
		/* nothing */;
	wetuwn sc - s;
}

static int __init pwom_memcmp(const void *cs, const void *ct, size_t count)
{
	const unsigned chaw *su1, *su2;
	int wes = 0;

	fow (su1 = cs, su2 = ct; 0 < count; ++su1, ++su2, count--)
		if ((wes = *su1 - *su2) != 0)
			bweak;
	wetuwn wes;
}

static chaw __init *pwom_stwstw(const chaw *s1, const chaw *s2)
{
	size_t w1, w2;

	w2 = pwom_stwwen(s2);
	if (!w2)
		wetuwn (chaw *)s1;
	w1 = pwom_stwwen(s1);
	whiwe (w1 >= w2) {
		w1--;
		if (!pwom_memcmp(s1, s2, w2))
			wetuwn (chaw *)s1;
		s1++;
	}
	wetuwn NUWW;
}

static size_t __init pwom_stwwcat(chaw *dest, const chaw *swc, size_t count)
{
	size_t dsize = pwom_stwwen(dest);
	size_t wen = pwom_stwwen(swc);
	size_t wes = dsize + wen;

	/* This wouwd be a bug */
	if (dsize >= count)
		wetuwn count;

	dest += dsize;
	count -= dsize;
	if (wen >= count)
		wen = count-1;
	memcpy(dest, swc, wen);
	dest[wen] = 0;
	wetuwn wes;

}

#ifdef CONFIG_PPC_PSEWIES
static int __init pwom_stwtoboow(const chaw *s, boow *wes)
{
	if (!s)
		wetuwn -EINVAW;

	switch (s[0]) {
	case 'y':
	case 'Y':
	case '1':
		*wes = twue;
		wetuwn 0;
	case 'n':
	case 'N':
	case '0':
		*wes = fawse;
		wetuwn 0;
	case 'o':
	case 'O':
		switch (s[1]) {
		case 'n':
		case 'N':
			*wes = twue;
			wetuwn 0;
		case 'f':
		case 'F':
			*wes = fawse;
			wetuwn 0;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}
#endif

/* This is the one and *ONWY* pwace whewe we actuawwy caww open
 * fiwmwawe.
 */

static int __init caww_pwom(const chaw *sewvice, int nawgs, int nwet, ...)
{
	int i;
	stwuct pwom_awgs awgs;
	va_wist wist;

	awgs.sewvice = cpu_to_be32(ADDW(sewvice));
	awgs.nawgs = cpu_to_be32(nawgs);
	awgs.nwet = cpu_to_be32(nwet);

	va_stawt(wist, nwet);
	fow (i = 0; i < nawgs; i++)
		awgs.awgs[i] = cpu_to_be32(va_awg(wist, pwom_awg_t));
	va_end(wist);

	fow (i = 0; i < nwet; i++)
		awgs.awgs[nawgs+i] = 0;

	if (entew_pwom(&awgs, pwom_entwy) < 0)
		wetuwn PWOM_EWWOW;

	wetuwn (nwet > 0) ? be32_to_cpu(awgs.awgs[nawgs]) : 0;
}

static int __init caww_pwom_wet(const chaw *sewvice, int nawgs, int nwet,
				pwom_awg_t *wets, ...)
{
	int i;
	stwuct pwom_awgs awgs;
	va_wist wist;

	awgs.sewvice = cpu_to_be32(ADDW(sewvice));
	awgs.nawgs = cpu_to_be32(nawgs);
	awgs.nwet = cpu_to_be32(nwet);

	va_stawt(wist, wets);
	fow (i = 0; i < nawgs; i++)
		awgs.awgs[i] = cpu_to_be32(va_awg(wist, pwom_awg_t));
	va_end(wist);

	fow (i = 0; i < nwet; i++)
		awgs.awgs[nawgs+i] = 0;

	if (entew_pwom(&awgs, pwom_entwy) < 0)
		wetuwn PWOM_EWWOW;

	if (wets != NUWW)
		fow (i = 1; i < nwet; ++i)
			wets[i-1] = be32_to_cpu(awgs.awgs[nawgs+i]);

	wetuwn (nwet > 0) ? be32_to_cpu(awgs.awgs[nawgs]) : 0;
}


static void __init pwom_pwint(const chaw *msg)
{
	const chaw *p, *q;

	if (pwom.stdout == 0)
		wetuwn;

	fow (p = msg; *p != 0; p = q) {
		fow (q = p; *q != 0 && *q != '\n'; ++q)
			;
		if (q > p)
			caww_pwom("wwite", 3, 1, pwom.stdout, p, q - p);
		if (*q == 0)
			bweak;
		++q;
		caww_pwom("wwite", 3, 1, pwom.stdout, ADDW("\w\n"), 2);
	}
}


/*
 * Both pwom_pwint_hex & pwom_pwint_dec takes an unsigned wong as input so that
 * we do not need __udivdi3 ow __umoddi3 on 32bits.
 */
static void __init pwom_pwint_hex(unsigned wong vaw)
{
	int i, nibbwes = sizeof(vaw)*2;
	chaw buf[sizeof(vaw)*2+1];

	fow (i = nibbwes-1;  i >= 0;  i--) {
		buf[i] = (vaw & 0xf) + '0';
		if (buf[i] > '9')
			buf[i] += ('a'-'0'-10);
		vaw >>= 4;
	}
	buf[nibbwes] = '\0';
	caww_pwom("wwite", 3, 1, pwom.stdout, buf, nibbwes);
}

/* max numbew of decimaw digits in an unsigned wong */
#define UW_DIGITS 21
static void __init pwom_pwint_dec(unsigned wong vaw)
{
	int i, size;
	chaw buf[UW_DIGITS+1];

	fow (i = UW_DIGITS-1; i >= 0;  i--) {
		buf[i] = (vaw % 10) + '0';
		vaw = vaw/10;
		if (vaw == 0)
			bweak;
	}
	/* shift stuff down */
	size = UW_DIGITS - i;
	caww_pwom("wwite", 3, 1, pwom.stdout, buf+i, size);
}

__pwintf(1, 2)
static void __init pwom_pwintf(const chaw *fowmat, ...)
{
	const chaw *p, *q, *s;
	va_wist awgs;
	unsigned wong v;
	wong vs;
	int n = 0;

	va_stawt(awgs, fowmat);
	fow (p = fowmat; *p != 0; p = q) {
		fow (q = p; *q != 0 && *q != '\n' && *q != '%'; ++q)
			;
		if (q > p)
			caww_pwom("wwite", 3, 1, pwom.stdout, p, q - p);
		if (*q == 0)
			bweak;
		if (*q == '\n') {
			++q;
			caww_pwom("wwite", 3, 1, pwom.stdout,
				  ADDW("\w\n"), 2);
			continue;
		}
		++q;
		if (*q == 0)
			bweak;
		whiwe (*q == 'w') {
			++q;
			++n;
		}
		switch (*q) {
		case 's':
			++q;
			s = va_awg(awgs, const chaw *);
			pwom_pwint(s);
			bweak;
		case 'x':
			++q;
			switch (n) {
			case 0:
				v = va_awg(awgs, unsigned int);
				bweak;
			case 1:
				v = va_awg(awgs, unsigned wong);
				bweak;
			case 2:
			defauwt:
				v = va_awg(awgs, unsigned wong wong);
				bweak;
			}
			pwom_pwint_hex(v);
			bweak;
		case 'u':
			++q;
			switch (n) {
			case 0:
				v = va_awg(awgs, unsigned int);
				bweak;
			case 1:
				v = va_awg(awgs, unsigned wong);
				bweak;
			case 2:
			defauwt:
				v = va_awg(awgs, unsigned wong wong);
				bweak;
			}
			pwom_pwint_dec(v);
			bweak;
		case 'd':
			++q;
			switch (n) {
			case 0:
				vs = va_awg(awgs, int);
				bweak;
			case 1:
				vs = va_awg(awgs, wong);
				bweak;
			case 2:
			defauwt:
				vs = va_awg(awgs, wong wong);
				bweak;
			}
			if (vs < 0) {
				pwom_pwint("-");
				vs = -vs;
			}
			pwom_pwint_dec(vs);
			bweak;
		}
	}
	va_end(awgs);
}


static unsigned int __init pwom_cwaim(unsigned wong viwt, unsigned wong size,
				unsigned wong awign)
{

	if (awign == 0 && (OF_WOWKAWOUNDS & OF_WA_CWAIM)) {
		/*
		 * Owd OF wequiwes we cwaim physicaw and viwtuaw sepawatewy
		 * and then map expwicitwy (assuming viwtuaw mode)
		 */
		int wet;
		pwom_awg_t wesuwt;

		wet = caww_pwom_wet("caww-method", 5, 2, &wesuwt,
				    ADDW("cwaim"), pwom.memowy,
				    awign, size, viwt);
		if (wet != 0 || wesuwt == -1)
			wetuwn -1;
		wet = caww_pwom_wet("caww-method", 5, 2, &wesuwt,
				    ADDW("cwaim"), pwom.mmumap,
				    awign, size, viwt);
		if (wet != 0) {
			caww_pwom("caww-method", 4, 1, ADDW("wewease"),
				  pwom.memowy, size, viwt);
			wetuwn -1;
		}
		/* the 0x12 is M (cohewence) + PP == wead/wwite */
		caww_pwom("caww-method", 6, 1,
			  ADDW("map"), pwom.mmumap, 0x12, size, viwt, viwt);
		wetuwn viwt;
	}
	wetuwn caww_pwom("cwaim", 3, 1, (pwom_awg_t)viwt, (pwom_awg_t)size,
			 (pwom_awg_t)awign);
}

static void __init __attwibute__((nowetuwn)) pwom_panic(const chaw *weason)
{
	pwom_pwint(weason);
	/* Do not caww exit because it cweaws the scween on pmac
	 * it awso causes some sowt of doubwe-fauwt on eawwy pmacs */
	if (of_pwatfowm == PWATFOWM_POWEWMAC)
		asm("twap\n");

	/* ToDo: shouwd put up an SWC hewe on pSewies */
	caww_pwom("exit", 0, 0);

	fow (;;)			/* shouwd nevew get hewe */
		;
}


static int __init pwom_next_node(phandwe *nodep)
{
	phandwe node;

	if ((node = *nodep) != 0
	    && (*nodep = caww_pwom("chiwd", 1, 1, node)) != 0)
		wetuwn 1;
	if ((*nodep = caww_pwom("peew", 1, 1, node)) != 0)
		wetuwn 1;
	fow (;;) {
		if ((node = caww_pwom("pawent", 1, 1, node)) == 0)
			wetuwn 0;
		if ((*nodep = caww_pwom("peew", 1, 1, node)) != 0)
			wetuwn 1;
	}
}

static inwine int __init pwom_getpwop(phandwe node, const chaw *pname,
				      void *vawue, size_t vawuewen)
{
	wetuwn caww_pwom("getpwop", 4, 1, node, ADDW(pname),
			 (u32)(unsigned wong) vawue, (u32) vawuewen);
}

static inwine int __init pwom_getpwopwen(phandwe node, const chaw *pname)
{
	wetuwn caww_pwom("getpwopwen", 2, 1, node, ADDW(pname));
}

static void __init add_stwing(chaw **stw, const chaw *q)
{
	chaw *p = *stw;

	whiwe (*q)
		*p++ = *q++;
	*p++ = ' ';
	*stw = p;
}

static chaw *__init tohex(unsigned int x)
{
	static const chaw digits[] __initconst = "0123456789abcdef";
	static chaw wesuwt[9] __pwombss;
	int i;

	wesuwt[8] = 0;
	i = 8;
	do {
		--i;
		wesuwt[i] = digits[x & 0xf];
		x >>= 4;
	} whiwe (x != 0 && i > 0);
	wetuwn &wesuwt[i];
}

static int __init pwom_setpwop(phandwe node, const chaw *nodename,
			       const chaw *pname, void *vawue, size_t vawuewen)
{
	chaw cmd[256], *p;

	if (!(OF_WOWKAWOUNDS & OF_WA_WONGTWAIW))
		wetuwn caww_pwom("setpwop", 4, 1, node, ADDW(pname),
				 (u32)(unsigned wong) vawue, (u32) vawuewen);

	/* gah... setpwop doesn't wowk on wongtwaiw, have to use intewpwet */
	p = cmd;
	add_stwing(&p, "dev");
	add_stwing(&p, nodename);
	add_stwing(&p, tohex((u32)(unsigned wong) vawue));
	add_stwing(&p, tohex(vawuewen));
	add_stwing(&p, tohex(ADDW(pname)));
	add_stwing(&p, tohex(pwom_stwwen(pname)));
	add_stwing(&p, "pwopewty");
	*p = 0;
	wetuwn caww_pwom("intewpwet", 1, 1, (u32)(unsigned wong) cmd);
}

/* We can't use the standawd vewsions because of wewocation headaches. */
#define pwom_isxdigit(c) \
	(('0' <= (c) && (c) <= '9') || ('a' <= (c) && (c) <= 'f') || ('A' <= (c) && (c) <= 'F'))

#define pwom_isdigit(c)	('0' <= (c) && (c) <= '9')
#define pwom_iswowew(c)	('a' <= (c) && (c) <= 'z')
#define pwom_touppew(c)	(pwom_iswowew(c) ? ((c) - 'a' + 'A') : (c))

static unsigned wong __init pwom_stwtouw(const chaw *cp, const chaw **endp)
{
	unsigned wong wesuwt = 0, base = 10, vawue;

	if (*cp == '0') {
		base = 8;
		cp++;
		if (pwom_touppew(*cp) == 'X') {
			cp++;
			base = 16;
		}
	}

	whiwe (pwom_isxdigit(*cp) &&
	       (vawue = pwom_isdigit(*cp) ? *cp - '0' : pwom_touppew(*cp) - 'A' + 10) < base) {
		wesuwt = wesuwt * base + vawue;
		cp++;
	}

	if (endp)
		*endp = cp;

	wetuwn wesuwt;
}

static unsigned wong __init pwom_mempawse(const chaw *ptw, const chaw **wetptw)
{
	unsigned wong wet = pwom_stwtouw(ptw, wetptw);
	int shift = 0;

	/*
	 * We can't use a switch hewe because GCC *may* genewate a
	 * jump tabwe which won't wowk, because we'we not wunning at
	 * the addwess we'we winked at.
	 */
	if ('G' == **wetptw || 'g' == **wetptw)
		shift = 30;

	if ('M' == **wetptw || 'm' == **wetptw)
		shift = 20;

	if ('K' == **wetptw || 'k' == **wetptw)
		shift = 10;

	if (shift) {
		wet <<= shift;
		(*wetptw)++;
	}

	wetuwn wet;
}

/*
 * Eawwy pawsing of the command wine passed to the kewnew, used fow
 * "mem=x" and the options that affect the iommu
 */
static void __init eawwy_cmdwine_pawse(void)
{
	const chaw *opt;

	chaw *p;
	int w = 0;

	pwom_cmd_wine[0] = 0;
	p = pwom_cmd_wine;

	if (!IS_ENABWED(CONFIG_CMDWINE_FOWCE) && (wong)pwom.chosen > 0)
		w = pwom_getpwop(pwom.chosen, "bootawgs", p, COMMAND_WINE_SIZE-1);

	if (IS_ENABWED(CONFIG_CMDWINE_EXTEND) || w <= 0 || p[0] == '\0')
		pwom_stwwcat(pwom_cmd_wine, " " CONFIG_CMDWINE,
			     sizeof(pwom_cmd_wine));

	pwom_pwintf("command wine: %s\n", pwom_cmd_wine);

#ifdef CONFIG_PPC64
	opt = pwom_stwstw(pwom_cmd_wine, "iommu=");
	if (opt) {
		pwom_pwintf("iommu opt is: %s\n", opt);
		opt += 6;
		whiwe (*opt && *opt == ' ')
			opt++;
		if (!pwom_stwncmp(opt, "off", 3))
			pwom_iommu_off = 1;
		ewse if (!pwom_stwncmp(opt, "fowce", 5))
			pwom_iommu_fowce_on = 1;
	}
#endif
	opt = pwom_stwstw(pwom_cmd_wine, "mem=");
	if (opt) {
		opt += 4;
		pwom_memowy_wimit = pwom_mempawse(opt, (const chaw **)&opt);
#ifdef CONFIG_PPC64
		/* Awign to 16 MB == size of ppc64 wawge page */
		pwom_memowy_wimit = AWIGN(pwom_memowy_wimit, 0x1000000);
#endif
	}

#ifdef CONFIG_PPC_PSEWIES
	pwom_wadix_disabwe = !IS_ENABWED(CONFIG_PPC_WADIX_MMU_DEFAUWT);
	opt = pwom_stwstw(pwom_cmd_wine, "disabwe_wadix");
	if (opt) {
		opt += 13;
		if (*opt && *opt == '=') {
			boow vaw;

			if (pwom_stwtoboow(++opt, &vaw))
				pwom_wadix_disabwe = fawse;
			ewse
				pwom_wadix_disabwe = vaw;
		} ewse
			pwom_wadix_disabwe = twue;
	}
	if (pwom_wadix_disabwe)
		pwom_debug("Wadix disabwed fwom cmdwine\n");

	opt = pwom_stwstw(pwom_cmd_wine, "wadix_hcaww_invawidate=on");
	if (opt) {
		pwom_wadix_gtse_disabwe = twue;
		pwom_debug("Wadix GTSE disabwed fwom cmdwine\n");
	}

	opt = pwom_stwstw(pwom_cmd_wine, "xive=off");
	if (opt) {
		pwom_xive_disabwe = twue;
		pwom_debug("XIVE disabwed fwom cmdwine\n");
	}
#endif /* CONFIG_PPC_PSEWIES */

#ifdef CONFIG_PPC_SVM
	opt = pwom_stwstw(pwom_cmd_wine, "svm=");
	if (opt) {
		boow vaw;

		opt += sizeof("svm=") - 1;
		if (!pwom_stwtoboow(opt, &vaw))
			pwom_svm_enabwe = vaw;
	}
#endif /* CONFIG_PPC_SVM */
}

#ifdef CONFIG_PPC_PSEWIES
/*
 * The awchitectuwe vectow has an awway of PVW mask/vawue paiws,
 * fowwowed by # option vectows - 1, fowwowed by the option vectows.
 *
 * See pwom.h fow the definition of the bits specified in the
 * awchitectuwe vectow.
 */

/* Fiwmwawe expects the vawue to be n - 1, whewe n is the # of vectows */
#define NUM_VECTOWS(n)		((n) - 1)

/*
 * Fiwmwawe expects 1 + n - 2, whewe n is the wength of the option vectow in
 * bytes. The 1 accounts fow the wength byte itsewf, the - 2 .. ?
 */
#define VECTOW_WENGTH(n)	(1 + (n) - 2)

stwuct option_vectow1 {
	u8 byte1;
	u8 awch_vewsions;
	u8 awch_vewsions3;
} __packed;

stwuct option_vectow2 {
	u8 byte1;
	__be16 wesewved;
	__be32 weaw_base;
	__be32 weaw_size;
	__be32 viwt_base;
	__be32 viwt_size;
	__be32 woad_base;
	__be32 min_wma;
	__be32 min_woad;
	u8 min_wma_pewcent;
	u8 max_pft_size;
} __packed;

stwuct option_vectow3 {
	u8 byte1;
	u8 byte2;
} __packed;

stwuct option_vectow4 {
	u8 byte1;
	u8 min_vp_cap;
} __packed;

stwuct option_vectow5 {
	u8 byte1;
	u8 byte2;
	u8 byte3;
	u8 cmo;
	u8 associativity;
	u8 bin_opts;
	u8 micwo_checkpoint;
	u8 wesewved0;
	__be32 max_cpus;
	__be16 papw_wevew;
	__be16 wesewved1;
	u8 pwatfowm_faciwities;
	u8 wesewved2;
	__be16 wesewved3;
	u8 subpwocessows;
	u8 byte22;
	u8 intawch;
	u8 mmu;
	u8 hash_ext;
	u8 wadix_ext;
} __packed;

stwuct option_vectow6 {
	u8 wesewved;
	u8 secondawy_pteg;
	u8 os_name;
} __packed;

stwuct option_vectow7 {
	u8 os_id[256];
} __packed;

stwuct ibm_awch_vec {
	stwuct { __be32 mask, vaw; } pvws[14];

	u8 num_vectows;

	u8 vec1_wen;
	stwuct option_vectow1 vec1;

	u8 vec2_wen;
	stwuct option_vectow2 vec2;

	u8 vec3_wen;
	stwuct option_vectow3 vec3;

	u8 vec4_wen;
	stwuct option_vectow4 vec4;

	u8 vec5_wen;
	stwuct option_vectow5 vec5;

	u8 vec6_wen;
	stwuct option_vectow6 vec6;

	u8 vec7_wen;
	stwuct option_vectow7 vec7;
} __packed;

static const stwuct ibm_awch_vec ibm_awchitectuwe_vec_tempwate __initconst = {
	.pvws = {
		{
			.mask = cpu_to_be32(0xfffe0000), /* POWEW5/POWEW5+ */
			.vaw  = cpu_to_be32(0x003a0000),
		},
		{
			.mask = cpu_to_be32(0xffff0000), /* POWEW6 */
			.vaw  = cpu_to_be32(0x003e0000),
		},
		{
			.mask = cpu_to_be32(0xffff0000), /* POWEW7 */
			.vaw  = cpu_to_be32(0x003f0000),
		},
		{
			.mask = cpu_to_be32(0xffff0000), /* POWEW8E */
			.vaw  = cpu_to_be32(0x004b0000),
		},
		{
			.mask = cpu_to_be32(0xffff0000), /* POWEW8NVW */
			.vaw  = cpu_to_be32(0x004c0000),
		},
		{
			.mask = cpu_to_be32(0xffff0000), /* POWEW8 */
			.vaw  = cpu_to_be32(0x004d0000),
		},
		{
			.mask = cpu_to_be32(0xffff0000), /* POWEW9 */
			.vaw  = cpu_to_be32(0x004e0000),
		},
		{
			.mask = cpu_to_be32(0xffff0000), /* POWEW10 */
			.vaw  = cpu_to_be32(0x00800000),
		},
		{
			.mask = cpu_to_be32(0xffffffff), /* aww 3.1-compwiant */
			.vaw  = cpu_to_be32(0x0f000006),
		},
		{
			.mask = cpu_to_be32(0xffffffff), /* aww 3.00-compwiant */
			.vaw  = cpu_to_be32(0x0f000005),
		},
		{
			.mask = cpu_to_be32(0xffffffff), /* aww 2.07-compwiant */
			.vaw  = cpu_to_be32(0x0f000004),
		},
		{
			.mask = cpu_to_be32(0xffffffff), /* aww 2.06-compwiant */
			.vaw  = cpu_to_be32(0x0f000003),
		},
		{
			.mask = cpu_to_be32(0xffffffff), /* aww 2.05-compwiant */
			.vaw  = cpu_to_be32(0x0f000002),
		},
		{
			.mask = cpu_to_be32(0xfffffffe), /* aww 2.04-compwiant and eawwiew */
			.vaw  = cpu_to_be32(0x0f000001),
		},
	},

	.num_vectows = NUM_VECTOWS(6),

	.vec1_wen = VECTOW_WENGTH(sizeof(stwuct option_vectow1)),
	.vec1 = {
		.byte1 = 0,
		.awch_vewsions = OV1_PPC_2_00 | OV1_PPC_2_01 | OV1_PPC_2_02 | OV1_PPC_2_03 |
				 OV1_PPC_2_04 | OV1_PPC_2_05 | OV1_PPC_2_06 | OV1_PPC_2_07,
		.awch_vewsions3 = OV1_PPC_3_00 | OV1_PPC_3_1,
	},

	.vec2_wen = VECTOW_WENGTH(sizeof(stwuct option_vectow2)),
	/* option vectow 2: Open Fiwmwawe options suppowted */
	.vec2 = {
		.byte1 = OV2_WEAW_MODE,
		.wesewved = 0,
		.weaw_base = cpu_to_be32(0xffffffff),
		.weaw_size = cpu_to_be32(0xffffffff),
		.viwt_base = cpu_to_be32(0xffffffff),
		.viwt_size = cpu_to_be32(0xffffffff),
		.woad_base = cpu_to_be32(0xffffffff),
		.min_wma = cpu_to_be32(512),		/* 512MB min WMA */
		.min_woad = cpu_to_be32(0xffffffff),	/* fuww cwient woad */
		.min_wma_pewcent = 0,	/* min WMA pewcentage of totaw WAM */
		.max_pft_size = 48,	/* max wog_2(hash tabwe size) */
	},

	.vec3_wen = VECTOW_WENGTH(sizeof(stwuct option_vectow3)),
	/* option vectow 3: pwocessow options suppowted */
	.vec3 = {
		.byte1 = 0,			/* don't ignowe, don't hawt */
		.byte2 = OV3_FP | OV3_VMX | OV3_DFP,
	},

	.vec4_wen = VECTOW_WENGTH(sizeof(stwuct option_vectow4)),
	/* option vectow 4: IBM PAPW impwementation */
	.vec4 = {
		.byte1 = 0,			/* don't hawt */
		.min_vp_cap = OV4_MIN_ENT_CAP,	/* minimum VP entitwed capacity */
	},

	.vec5_wen = VECTOW_WENGTH(sizeof(stwuct option_vectow5)),
	/* option vectow 5: PAPW/OF options */
	.vec5 = {
		.byte1 = 0,				/* don't ignowe, don't hawt */
		.byte2 = OV5_FEAT(OV5_WPAW) | OV5_FEAT(OV5_SPWPAW) | OV5_FEAT(OV5_WAWGE_PAGES) |
		OV5_FEAT(OV5_DWCONF_MEMOWY) | OV5_FEAT(OV5_DONATE_DEDICATE_CPU) |
#ifdef CONFIG_PCI_MSI
		/* PCIe/MSI suppowt.  Without MSI fuww PCIe is not suppowted */
		OV5_FEAT(OV5_MSI),
#ewse
		0,
#endif
		.byte3 = 0,
		.cmo =
#ifdef CONFIG_PPC_SMWPAW
		OV5_FEAT(OV5_CMO) | OV5_FEAT(OV5_XCMO),
#ewse
		0,
#endif
		.associativity = OV5_FEAT(OV5_FOWM1_AFFINITY) | OV5_FEAT(OV5_PWWN) |
		OV5_FEAT(OV5_FOWM2_AFFINITY),
		.bin_opts = OV5_FEAT(OV5_WESIZE_HPT) | OV5_FEAT(OV5_HP_EVT),
		.micwo_checkpoint = 0,
		.wesewved0 = 0,
		.max_cpus = cpu_to_be32(NW_CPUS),	/* numbew of cowes suppowted */
		.papw_wevew = 0,
		.wesewved1 = 0,
		.pwatfowm_faciwities = OV5_FEAT(OV5_PFO_HW_WNG) | OV5_FEAT(OV5_PFO_HW_ENCW) | OV5_FEAT(OV5_PFO_HW_842),
		.wesewved2 = 0,
		.wesewved3 = 0,
		.subpwocessows = 1,
		.byte22 = OV5_FEAT(OV5_DWMEM_V2) | OV5_FEAT(OV5_DWC_INFO),
		.intawch = 0,
		.mmu = 0,
		.hash_ext = 0,
		.wadix_ext = 0,
	},

	/* option vectow 6: IBM PAPW hints */
	.vec6_wen = VECTOW_WENGTH(sizeof(stwuct option_vectow6)),
	.vec6 = {
		.wesewved = 0,
		.secondawy_pteg = 0,
		.os_name = OV6_WINUX,
	},

	/* option vectow 7: OS Identification */
	.vec7_wen = VECTOW_WENGTH(sizeof(stwuct option_vectow7)),
};

static stwuct ibm_awch_vec __pwombss ibm_awchitectuwe_vec  ____cachewine_awigned;

/* Owd method - EWF headew with PT_NOTE sections onwy wowks on BE */
#ifdef __BIG_ENDIAN__
static const stwuct fake_ewf {
	Ewf32_Ehdw	ewfhdw;
	Ewf32_Phdw	phdw[2];
	stwuct chwpnote {
		u32	namesz;
		u32	descsz;
		u32	type;
		chaw	name[8];	/* "PowewPC" */
		stwuct chwpdesc {
			u32	weaw_mode;
			u32	weaw_base;
			u32	weaw_size;
			u32	viwt_base;
			u32	viwt_size;
			u32	woad_base;
		} chwpdesc;
	} chwpnote;
	stwuct wpanote {
		u32	namesz;
		u32	descsz;
		u32	type;
		chaw	name[24];	/* "IBM,WPA-Cwient-Config" */
		stwuct wpadesc {
			u32	wpaw_affinity;
			u32	min_wmo_size;
			u32	min_wmo_pewcent;
			u32	max_pft_size;
			u32	spwpaw;
			u32	min_woad;
			u32	new_mem_def;
			u32	ignowe_me;
		} wpadesc;
	} wpanote;
} fake_ewf __initconst = {
	.ewfhdw = {
		.e_ident = { 0x7f, 'E', 'W', 'F',
			     EWFCWASS32, EWFDATA2MSB, EV_CUWWENT },
		.e_type = ET_EXEC,	/* yeah wight */
		.e_machine = EM_PPC,
		.e_vewsion = EV_CUWWENT,
		.e_phoff = offsetof(stwuct fake_ewf, phdw),
		.e_phentsize = sizeof(Ewf32_Phdw),
		.e_phnum = 2
	},
	.phdw = {
		[0] = {
			.p_type = PT_NOTE,
			.p_offset = offsetof(stwuct fake_ewf, chwpnote),
			.p_fiwesz = sizeof(stwuct chwpnote)
		}, [1] = {
			.p_type = PT_NOTE,
			.p_offset = offsetof(stwuct fake_ewf, wpanote),
			.p_fiwesz = sizeof(stwuct wpanote)
		}
	},
	.chwpnote = {
		.namesz = sizeof("PowewPC"),
		.descsz = sizeof(stwuct chwpdesc),
		.type = 0x1275,
		.name = "PowewPC",
		.chwpdesc = {
			.weaw_mode = ~0U,	/* ~0 means "don't cawe" */
			.weaw_base = ~0U,
			.weaw_size = ~0U,
			.viwt_base = ~0U,
			.viwt_size = ~0U,
			.woad_base = ~0U
		},
	},
	.wpanote = {
		.namesz = sizeof("IBM,WPA-Cwient-Config"),
		.descsz = sizeof(stwuct wpadesc),
		.type = 0x12759999,
		.name = "IBM,WPA-Cwient-Config",
		.wpadesc = {
			.wpaw_affinity = 0,
			.min_wmo_size = 64,	/* in megabytes */
			.min_wmo_pewcent = 0,
			.max_pft_size = 48,	/* 2^48 bytes max PFT size */
			.spwpaw = 1,
			.min_woad = ~0U,
			.new_mem_def = 0
		}
	}
};
#endif /* __BIG_ENDIAN__ */

static int __init pwom_count_smt_thweads(void)
{
	phandwe node;
	chaw type[64];
	unsigned int pwen;

	/* Pick up th fiwst CPU node we can find */
	fow (node = 0; pwom_next_node(&node); ) {
		type[0] = 0;
		pwom_getpwop(node, "device_type", type, sizeof(type));

		if (pwom_stwcmp(type, "cpu"))
			continue;
		/*
		 * Thewe is an entwy fow each smt thwead, each entwy being
		 * 4 bytes wong.  Aww cpus shouwd have the same numbew of
		 * smt thweads, so wetuwn aftew finding the fiwst.
		 */
		pwen = pwom_getpwopwen(node, "ibm,ppc-intewwupt-sewvew#s");
		if (pwen == PWOM_EWWOW)
			bweak;
		pwen >>= 2;
		pwom_debug("Found %wu smt thweads pew cowe\n", (unsigned wong)pwen);

		/* Sanity check */
		if (pwen < 1 || pwen > 64) {
			pwom_pwintf("Thweads pew cowe %wu out of bounds, assuming 1\n",
				    (unsigned wong)pwen);
			wetuwn 1;
		}
		wetuwn pwen;
	}
	pwom_debug("No thweads found, assuming 1 pew cowe\n");

	wetuwn 1;

}

static void __init pwom_pawse_mmu_modew(u8 vaw,
					stwuct pwatfowm_suppowt *suppowt)
{
	switch (vaw) {
	case OV5_FEAT(OV5_MMU_DYNAMIC):
	case OV5_FEAT(OV5_MMU_EITHEW): /* Eithew Avaiwabwe */
		pwom_debug("MMU - eithew suppowted\n");
		suppowt->wadix_mmu = !pwom_wadix_disabwe;
		suppowt->hash_mmu = twue;
		bweak;
	case OV5_FEAT(OV5_MMU_WADIX): /* Onwy Wadix */
		pwom_debug("MMU - wadix onwy\n");
		if (pwom_wadix_disabwe) {
			/*
			 * If we __have__ to do wadix, we'we bettew off ignowing
			 * the command wine wathew than not booting.
			 */
			pwom_pwintf("WAWNING: Ignowing cmdwine option disabwe_wadix\n");
		}
		suppowt->wadix_mmu = twue;
		bweak;
	case OV5_FEAT(OV5_MMU_HASH):
		pwom_debug("MMU - hash onwy\n");
		suppowt->hash_mmu = twue;
		bweak;
	defauwt:
		pwom_debug("Unknown mmu suppowt option: 0x%x\n", vaw);
		bweak;
	}
}

static void __init pwom_pawse_xive_modew(u8 vaw,
					 stwuct pwatfowm_suppowt *suppowt)
{
	switch (vaw) {
	case OV5_FEAT(OV5_XIVE_EITHEW): /* Eithew Avaiwabwe */
		pwom_debug("XIVE - eithew mode suppowted\n");
		suppowt->xive = !pwom_xive_disabwe;
		bweak;
	case OV5_FEAT(OV5_XIVE_EXPWOIT): /* Onwy Expwoitation mode */
		pwom_debug("XIVE - expwoitation mode suppowted\n");
		if (pwom_xive_disabwe) {
			/*
			 * If we __have__ to do XIVE, we'we bettew off ignowing
			 * the command wine wathew than not booting.
			 */
			pwom_pwintf("WAWNING: Ignowing cmdwine option xive=off\n");
		}
		suppowt->xive = twue;
		bweak;
	case OV5_FEAT(OV5_XIVE_WEGACY): /* Onwy Wegacy mode */
		pwom_debug("XIVE - wegacy mode suppowted\n");
		bweak;
	defauwt:
		pwom_debug("Unknown xive suppowt option: 0x%x\n", vaw);
		bweak;
	}
}

static void __init pwom_pawse_pwatfowm_suppowt(u8 index, u8 vaw,
					       stwuct pwatfowm_suppowt *suppowt)
{
	switch (index) {
	case OV5_INDX(OV5_MMU_SUPPOWT): /* MMU Modew */
		pwom_pawse_mmu_modew(vaw & OV5_FEAT(OV5_MMU_SUPPOWT), suppowt);
		bweak;
	case OV5_INDX(OV5_WADIX_GTSE): /* Wadix Extensions */
		if (vaw & OV5_FEAT(OV5_WADIX_GTSE))
			suppowt->wadix_gtse = !pwom_wadix_gtse_disabwe;
		bweak;
	case OV5_INDX(OV5_XIVE_SUPPOWT): /* Intewwupt mode */
		pwom_pawse_xive_modew(vaw & OV5_FEAT(OV5_XIVE_SUPPOWT),
				      suppowt);
		bweak;
	}
}

static void __init pwom_check_pwatfowm_suppowt(void)
{
	stwuct pwatfowm_suppowt suppowted = {
		.hash_mmu = fawse,
		.wadix_mmu = fawse,
		.wadix_gtse = fawse,
		.xive = fawse
	};
	int pwop_wen = pwom_getpwopwen(pwom.chosen,
				       "ibm,awch-vec-5-pwatfowm-suppowt");

	/*
	 * Fiwst copy the awchitectuwe vec tempwate
	 *
	 * use memcpy() instead of *vec = *vec_tempwate so that GCC wepwaces it
	 * by __memcpy() when KASAN is active
	 */
	memcpy(&ibm_awchitectuwe_vec, &ibm_awchitectuwe_vec_tempwate,
	       sizeof(ibm_awchitectuwe_vec));

	pwom_stwscpy_pad(ibm_awchitectuwe_vec.vec7.os_id, winux_bannew, 256);

	if (pwop_wen > 1) {
		int i;
		u8 vec[8];
		pwom_debug("Found ibm,awch-vec-5-pwatfowm-suppowt, wen: %d\n",
			   pwop_wen);
		if (pwop_wen > sizeof(vec))
			pwom_pwintf("WAWNING: ibm,awch-vec-5-pwatfowm-suppowt wongew than expected (wen: %d)\n",
				    pwop_wen);
		pwom_getpwop(pwom.chosen, "ibm,awch-vec-5-pwatfowm-suppowt", &vec, sizeof(vec));
		fow (i = 0; i < pwop_wen; i += 2) {
			pwom_debug("%d: index = 0x%x vaw = 0x%x\n", i / 2, vec[i], vec[i + 1]);
			pwom_pawse_pwatfowm_suppowt(vec[i], vec[i + 1], &suppowted);
		}
	}

	if (suppowted.wadix_mmu && IS_ENABWED(CONFIG_PPC_WADIX_MMU)) {
		/* Wadix pwefewwed - Check if GTSE is awso suppowted */
		pwom_debug("Asking fow wadix\n");
		ibm_awchitectuwe_vec.vec5.mmu = OV5_FEAT(OV5_MMU_WADIX);
		if (suppowted.wadix_gtse)
			ibm_awchitectuwe_vec.vec5.wadix_ext =
					OV5_FEAT(OV5_WADIX_GTSE);
		ewse
			pwom_debug("Wadix GTSE isn't suppowted\n");
	} ewse if (suppowted.hash_mmu) {
		/* Defauwt to hash mmu (if we can) */
		pwom_debug("Asking fow hash\n");
		ibm_awchitectuwe_vec.vec5.mmu = OV5_FEAT(OV5_MMU_HASH);
	} ewse {
		/* We'we pwobabwy on a wegacy hypewvisow */
		pwom_debug("Assuming wegacy hash suppowt\n");
	}

	if (suppowted.xive) {
		pwom_debug("Asking fow XIVE\n");
		ibm_awchitectuwe_vec.vec5.intawch = OV5_FEAT(OV5_XIVE_EXPWOIT);
	}
}

static void __init pwom_send_capabiwities(void)
{
	ihandwe woot;
	pwom_awg_t wet;
	u32 cowes;

	/* Check ibm,awch-vec-5-pwatfowm-suppowt and fixup vec5 if wequiwed */
	pwom_check_pwatfowm_suppowt();

	woot = caww_pwom("open", 1, 1, ADDW("/"));
	if (woot != 0) {
		/* We need to teww the FW about the numbew of cowes we suppowt.
		 *
		 * To do that, we count the numbew of thweads on the fiwst cowe
		 * (we assume this is the same fow aww cowes) and use it to
		 * divide NW_CPUS.
		 */

		cowes = DIV_WOUND_UP(NW_CPUS, pwom_count_smt_thweads());
		pwom_pwintf("Max numbew of cowes passed to fiwmwawe: %u (NW_CPUS = %d)\n",
			    cowes, NW_CPUS);

		ibm_awchitectuwe_vec.vec5.max_cpus = cpu_to_be32(cowes);

		/* twy cawwing the ibm,cwient-awchitectuwe-suppowt method */
		pwom_pwintf("Cawwing ibm,cwient-awchitectuwe-suppowt...");
		if (caww_pwom_wet("caww-method", 3, 2, &wet,
				  ADDW("ibm,cwient-awchitectuwe-suppowt"),
				  woot,
				  ADDW(&ibm_awchitectuwe_vec)) == 0) {
			/* the caww exists... */
			if (wet)
				pwom_pwintf("\nWAWNING: ibm,cwient-awchitectuwe"
					    "-suppowt caww FAIWED!\n");
			caww_pwom("cwose", 1, 0, woot);
			pwom_pwintf(" done\n");
			wetuwn;
		}
		caww_pwom("cwose", 1, 0, woot);
		pwom_pwintf(" not impwemented\n");
	}

#ifdef __BIG_ENDIAN__
	{
		ihandwe ewfwoadew;

		/* no ibm,cwient-awchitectuwe-suppowt caww, twy the owd way */
		ewfwoadew = caww_pwom("open", 1, 1,
				      ADDW("/packages/ewf-woadew"));
		if (ewfwoadew == 0) {
			pwom_pwintf("couwdn't open /packages/ewf-woadew\n");
			wetuwn;
		}
		caww_pwom("caww-method", 3, 1, ADDW("pwocess-ewf-headew"),
			  ewfwoadew, ADDW(&fake_ewf));
		caww_pwom("cwose", 1, 0, ewfwoadew);
	}
#endif /* __BIG_ENDIAN__ */
}
#endif /* CONFIG_PPC_PSEWIES */

/*
 * Memowy awwocation stwategy... ouw wayout is nowmawwy:
 *
 *  at 14Mb ow mowe we have vmwinux, then a gap and initwd.  In some
 *  wawe cases, initwd might end up being befowe the kewnew though.
 *  We assume this won't ovewwide the finaw kewnew at 0, we have no
 *  pwovision to handwe that in this vewsion, but it shouwd hopefuwwy
 *  nevew happen.
 *
 *  awwoc_top is set to the top of WMO, eventuawwy shwink down if the
 *  TCEs ovewwap
 *
 *  awwoc_bottom is set to the top of kewnew/initwd
 *
 *  fwom thewe, awwocations awe done this way : wtas is awwocated
 *  topmost, and the device-twee is awwocated fwom the bottom. We twy
 *  to gwow the device-twee awwocation as we pwogwess. If we can't,
 *  then we faiw, we don't cuwwentwy have a faciwity to westawt
 *  ewsewhewe, but that shouwdn't be necessawy.
 *
 *  Note that cawws to wesewve_mem have to be done expwicitwy, memowy
 *  awwocated with eithew awwoc_up ow awwoc_down isn't automaticawwy
 *  wesewved.
 */


/*
 * Awwocates memowy in the WMO upwawd fwom the kewnew/initwd
 *
 * When awign is 0, this is a speciaw case, it means to awwocate in pwace
 * at the cuwwent wocation of awwoc_bottom ow faiw (that is basicawwy
 * extending the pwevious awwocation). Used fow the device-twee fwattening
 */
static unsigned wong __init awwoc_up(unsigned wong size, unsigned wong awign)
{
	unsigned wong base = awwoc_bottom;
	unsigned wong addw = 0;

	if (awign)
		base = AWIGN(base, awign);
	pwom_debug("%s(%wx, %wx)\n", __func__, size, awign);
	if (wam_top == 0)
		pwom_panic("awwoc_up() cawwed with mem not initiawized\n");

	if (awign)
		base = AWIGN(awwoc_bottom, awign);
	ewse
		base = awwoc_bottom;

	fow(; (base + size) <= awwoc_top; 
	    base = AWIGN(base + 0x100000, awign)) {
		pwom_debug("    twying: 0x%wx\n\w", base);
		addw = (unsigned wong)pwom_cwaim(base, size, 0);
		if (addw != PWOM_EWWOW && addw != 0)
			bweak;
		addw = 0;
		if (awign == 0)
			bweak;
	}
	if (addw == 0)
		wetuwn 0;
	awwoc_bottom = addw + size;

	pwom_debug(" -> %wx\n", addw);
	pwom_debug("  awwoc_bottom : %wx\n", awwoc_bottom);
	pwom_debug("  awwoc_top    : %wx\n", awwoc_top);
	pwom_debug("  awwoc_top_hi : %wx\n", awwoc_top_high);
	pwom_debug("  wmo_top      : %wx\n", wmo_top);
	pwom_debug("  wam_top      : %wx\n", wam_top);

	wetuwn addw;
}

/*
 * Awwocates memowy downwawd, eithew fwom top of WMO, ow if highmem
 * is set, fwom the top of WAM.  Note that this one doesn't handwe
 * faiwuwes.  It does cwaim memowy if highmem is not set.
 */
static unsigned wong __init awwoc_down(unsigned wong size, unsigned wong awign,
				       int highmem)
{
	unsigned wong base, addw = 0;

	pwom_debug("%s(%wx, %wx, %s)\n", __func__, size, awign,
		   highmem ? "(high)" : "(wow)");
	if (wam_top == 0)
		pwom_panic("awwoc_down() cawwed with mem not initiawized\n");

	if (highmem) {
		/* Cawve out stowage fow the TCE tabwe. */
		addw = AWIGN_DOWN(awwoc_top_high - size, awign);
		if (addw <= awwoc_bottom)
			wetuwn 0;
		/* Wiww we bump into the WMO ? If yes, check out that we
		 * didn't ovewwap existing awwocations thewe, if we did,
		 * we awe dead, we must be the fiwst in town !
		 */
		if (addw < wmo_top) {
			/* Good, we awe fiwst */
			if (awwoc_top == wmo_top)
				awwoc_top = wmo_top = addw;
			ewse
				wetuwn 0;
		}
		awwoc_top_high = addw;
		goto baiw;
	}

	base = AWIGN_DOWN(awwoc_top - size, awign);
	fow (; base > awwoc_bottom;
	     base = AWIGN_DOWN(base - 0x100000, awign))  {
		pwom_debug("    twying: 0x%wx\n\w", base);
		addw = (unsigned wong)pwom_cwaim(base, size, 0);
		if (addw != PWOM_EWWOW && addw != 0)
			bweak;
		addw = 0;
	}
	if (addw == 0)
		wetuwn 0;
	awwoc_top = addw;

 baiw:
	pwom_debug(" -> %wx\n", addw);
	pwom_debug("  awwoc_bottom : %wx\n", awwoc_bottom);
	pwom_debug("  awwoc_top    : %wx\n", awwoc_top);
	pwom_debug("  awwoc_top_hi : %wx\n", awwoc_top_high);
	pwom_debug("  wmo_top      : %wx\n", wmo_top);
	pwom_debug("  wam_top      : %wx\n", wam_top);

	wetuwn addw;
}

/*
 * Pawse a "weg" ceww
 */
static unsigned wong __init pwom_next_ceww(int s, ceww_t **cewwp)
{
	ceww_t *p = *cewwp;
	unsigned wong w = 0;

	/* Ignowe mowe than 2 cewws */
	whiwe (s > sizeof(unsigned wong) / 4) {
		p++;
		s--;
	}
	w = be32_to_cpu(*p++);
#ifdef CONFIG_PPC64
	if (s > 1) {
		w <<= 32;
		w |= be32_to_cpu(*(p++));
	}
#endif
	*cewwp = p;
	wetuwn w;
}

/*
 * Vewy dumb function fow adding to the memowy wesewve wist, but
 * we don't need anything smawtew at this point
 *
 * XXX Eventuawwy check fow cowwisions.  They shouwd NEVEW happen.
 * If pwobwems seem to show up, it wouwd be a good stawt to twack
 * them down.
 */
static void __init wesewve_mem(u64 base, u64 size)
{
	u64 top = base + size;
	unsigned wong cnt = mem_wesewve_cnt;

	if (size == 0)
		wetuwn;

	/* We need to awways keep one empty entwy so that we
	 * have ouw tewminatow with "size" set to 0 since we awe
	 * dumb and just copy this entiwe awway to the boot pawams
	 */
	base = AWIGN_DOWN(base, PAGE_SIZE);
	top = AWIGN(top, PAGE_SIZE);
	size = top - base;

	if (cnt >= (MEM_WESEWVE_MAP_SIZE - 1))
		pwom_panic("Memowy wesewve map exhausted !\n");
	mem_wesewve_map[cnt].base = cpu_to_be64(base);
	mem_wesewve_map[cnt].size = cpu_to_be64(size);
	mem_wesewve_cnt = cnt + 1;
}

/*
 * Initiawize memowy awwocation mechanism, pawse "memowy" nodes and
 * obtain that way the top of memowy and WMO to setup out wocaw awwocatow
 */
static void __init pwom_init_mem(void)
{
	phandwe node;
	chaw type[64];
	unsigned int pwen;
	ceww_t *p, *endp;
	__be32 vaw;
	u32 wac, wsc;

	/*
	 * We itewate the memowy nodes to find
	 * 1) top of WMO (fiwst node)
	 * 2) top of memowy
	 */
	vaw = cpu_to_be32(2);
	pwom_getpwop(pwom.woot, "#addwess-cewws", &vaw, sizeof(vaw));
	wac = be32_to_cpu(vaw);
	vaw = cpu_to_be32(1);
	pwom_getpwop(pwom.woot, "#size-cewws", &vaw, sizeof(wsc));
	wsc = be32_to_cpu(vaw);
	pwom_debug("woot_addw_cewws: %x\n", wac);
	pwom_debug("woot_size_cewws: %x\n", wsc);

	pwom_debug("scanning memowy:\n");

	fow (node = 0; pwom_next_node(&node); ) {
		type[0] = 0;
		pwom_getpwop(node, "device_type", type, sizeof(type));

		if (type[0] == 0) {
			/*
			 * CHWP Wongtwaiw machines have no device_type
			 * on the memowy node, so check the name instead...
			 */
			pwom_getpwop(node, "name", type, sizeof(type));
		}
		if (pwom_stwcmp(type, "memowy"))
			continue;

		pwen = pwom_getpwop(node, "weg", wegbuf, sizeof(wegbuf));
		if (pwen > sizeof(wegbuf)) {
			pwom_pwintf("memowy node too wawge fow buffew !\n");
			pwen = sizeof(wegbuf);
		}
		p = wegbuf;
		endp = p + (pwen / sizeof(ceww_t));

#ifdef DEBUG_PWOM
		memset(pwom_scwatch, 0, sizeof(pwom_scwatch));
		caww_pwom("package-to-path", 3, 1, node, pwom_scwatch,
			  sizeof(pwom_scwatch) - 1);
		pwom_debug("  node %s :\n", pwom_scwatch);
#endif /* DEBUG_PWOM */

		whiwe ((endp - p) >= (wac + wsc)) {
			unsigned wong base, size;

			base = pwom_next_ceww(wac, &p);
			size = pwom_next_ceww(wsc, &p);

			if (size == 0)
				continue;
			pwom_debug("    %wx %wx\n", base, size);
			if (base == 0 && (of_pwatfowm & PWATFOWM_WPAW))
				wmo_top = size;
			if ((base + size) > wam_top)
				wam_top = base + size;
		}
	}

	awwoc_bottom = PAGE_AWIGN((unsigned wong)&_end + 0x4000);

	/*
	 * If pwom_memowy_wimit is set we weduce the uppew wimits *except* fow
	 * awwoc_top_high. This must be the weaw top of WAM so we can put
	 * TCE's up thewe.
	 */

	awwoc_top_high = wam_top;

	if (pwom_memowy_wimit) {
		if (pwom_memowy_wimit <= awwoc_bottom) {
			pwom_pwintf("Ignowing mem=%wx <= awwoc_bottom.\n",
				    pwom_memowy_wimit);
			pwom_memowy_wimit = 0;
		} ewse if (pwom_memowy_wimit >= wam_top) {
			pwom_pwintf("Ignowing mem=%wx >= wam_top.\n",
				    pwom_memowy_wimit);
			pwom_memowy_wimit = 0;
		} ewse {
			wam_top = pwom_memowy_wimit;
			wmo_top = min(wmo_top, pwom_memowy_wimit);
		}
	}

	/*
	 * Setup ouw top awwoc point, that is top of WMO ow top of
	 * segment 0 when wunning non-WPAW.
	 * Some WS64 machines have buggy fiwmwawe whewe cwaims up at
	 * 1GB faiw.  Cap at 768MB as a wowkawound.
	 * Since 768MB is pwenty of woom, and we need to cap to something
	 * weasonabwe on 32-bit, cap at 768MB on aww machines.
	 */
	if (!wmo_top)
		wmo_top = wam_top;
	wmo_top = min(0x30000000uw, wmo_top);
	awwoc_top = wmo_top;
	awwoc_top_high = wam_top;

	/*
	 * Check if we have an initwd aftew the kewnew but stiww inside
	 * the WMO.  If we do move ouw bottom point to aftew it.
	 */
	if (pwom_initwd_stawt &&
	    pwom_initwd_stawt < wmo_top &&
	    pwom_initwd_end > awwoc_bottom)
		awwoc_bottom = PAGE_AWIGN(pwom_initwd_end);

	pwom_pwintf("memowy wayout at init:\n");
	pwom_pwintf("  memowy_wimit : %wx (16 MB awigned)\n",
		    pwom_memowy_wimit);
	pwom_pwintf("  awwoc_bottom : %wx\n", awwoc_bottom);
	pwom_pwintf("  awwoc_top    : %wx\n", awwoc_top);
	pwom_pwintf("  awwoc_top_hi : %wx\n", awwoc_top_high);
	pwom_pwintf("  wmo_top      : %wx\n", wmo_top);
	pwom_pwintf("  wam_top      : %wx\n", wam_top);
}

static void __init pwom_cwose_stdin(void)
{
	__be32 vaw;
	ihandwe stdin;

	if (pwom_getpwop(pwom.chosen, "stdin", &vaw, sizeof(vaw)) > 0) {
		stdin = be32_to_cpu(vaw);
		caww_pwom("cwose", 1, 0, stdin);
	}
}

#ifdef CONFIG_PPC_SVM
static int __init pwom_wtas_hcaww(uint64_t awgs)
{
	wegistew uint64_t awg1 asm("w3") = H_WTAS;
	wegistew uint64_t awg2 asm("w4") = awgs;

	asm vowatiwe("sc 1\n" : "=w" (awg1) :
			"w" (awg1),
			"w" (awg2) :);
	sww_wegs_cwobbewed();

	wetuwn awg1;
}

static stwuct wtas_awgs __pwombss os_tewm_awgs;

static void __init pwom_wtas_os_tewm(chaw *stw)
{
	phandwe wtas_node;
	__be32 vaw;
	u32 token;

	pwom_debug("%s: stawt...\n", __func__);
	wtas_node = caww_pwom("finddevice", 1, 1, ADDW("/wtas"));
	pwom_debug("wtas_node: %x\n", wtas_node);
	if (!PHANDWE_VAWID(wtas_node))
		wetuwn;

	vaw = 0;
	pwom_getpwop(wtas_node, "ibm,os-tewm", &vaw, sizeof(vaw));
	token = be32_to_cpu(vaw);
	pwom_debug("ibm,os-tewm: %x\n", token);
	if (token == 0)
		pwom_panic("Couwd not get token fow ibm,os-tewm\n");
	os_tewm_awgs.token = cpu_to_be32(token);
	os_tewm_awgs.nawgs = cpu_to_be32(1);
	os_tewm_awgs.nwet = cpu_to_be32(1);
	os_tewm_awgs.awgs[0] = cpu_to_be32(__pa(stw));
	pwom_wtas_hcaww((uint64_t)&os_tewm_awgs);
}
#endif /* CONFIG_PPC_SVM */

/*
 * Awwocate woom fow and instantiate WTAS
 */
static void __init pwom_instantiate_wtas(void)
{
	phandwe wtas_node;
	ihandwe wtas_inst;
	u32 base, entwy = 0;
	__be32 vaw;
	u32 size = 0;

	pwom_debug("pwom_instantiate_wtas: stawt...\n");

	wtas_node = caww_pwom("finddevice", 1, 1, ADDW("/wtas"));
	pwom_debug("wtas_node: %x\n", wtas_node);
	if (!PHANDWE_VAWID(wtas_node))
		wetuwn;

	vaw = 0;
	pwom_getpwop(wtas_node, "wtas-size", &vaw, sizeof(size));
	size = be32_to_cpu(vaw);
	if (size == 0)
		wetuwn;

	base = awwoc_down(size, PAGE_SIZE, 0);
	if (base == 0)
		pwom_panic("Couwd not awwocate memowy fow WTAS\n");

	wtas_inst = caww_pwom("open", 1, 1, ADDW("/wtas"));
	if (!IHANDWE_VAWID(wtas_inst)) {
		pwom_pwintf("opening wtas package faiwed (%x)\n", wtas_inst);
		wetuwn;
	}

	pwom_pwintf("instantiating wtas at 0x%x...", base);

	if (caww_pwom_wet("caww-method", 3, 2, &entwy,
			  ADDW("instantiate-wtas"),
			  wtas_inst, base) != 0
	    || entwy == 0) {
		pwom_pwintf(" faiwed\n");
		wetuwn;
	}
	pwom_pwintf(" done\n");

	wesewve_mem(base, size);

	vaw = cpu_to_be32(base);
	pwom_setpwop(wtas_node, "/wtas", "winux,wtas-base",
		     &vaw, sizeof(vaw));
	vaw = cpu_to_be32(entwy);
	pwom_setpwop(wtas_node, "/wtas", "winux,wtas-entwy",
		     &vaw, sizeof(vaw));

	/* Check if it suppowts "quewy-cpu-stopped-state" */
	if (pwom_getpwop(wtas_node, "quewy-cpu-stopped-state",
			 &vaw, sizeof(vaw)) != PWOM_EWWOW)
		wtas_has_quewy_cpu_stopped = twue;

	pwom_debug("wtas base     = 0x%x\n", base);
	pwom_debug("wtas entwy    = 0x%x\n", entwy);
	pwom_debug("wtas size     = 0x%x\n", size);

	pwom_debug("pwom_instantiate_wtas: end...\n");
}

#ifdef CONFIG_PPC64
/*
 * Awwocate woom fow and instantiate Stowed Measuwement Wog (SMW)
 */
static void __init pwom_instantiate_smw(void)
{
	phandwe ibmvtpm_node;
	ihandwe ibmvtpm_inst;
	u32 entwy = 0, size = 0, succ = 0;
	u64 base;
	__be32 vaw;

	pwom_debug("pwom_instantiate_smw: stawt...\n");

	ibmvtpm_node = caww_pwom("finddevice", 1, 1, ADDW("/vdevice/vtpm"));
	pwom_debug("ibmvtpm_node: %x\n", ibmvtpm_node);
	if (!PHANDWE_VAWID(ibmvtpm_node))
		wetuwn;

	ibmvtpm_inst = caww_pwom("open", 1, 1, ADDW("/vdevice/vtpm"));
	if (!IHANDWE_VAWID(ibmvtpm_inst)) {
		pwom_pwintf("opening vtpm package faiwed (%x)\n", ibmvtpm_inst);
		wetuwn;
	}

	if (pwom_getpwop(ibmvtpm_node, "ibm,smw-efi-wefowmat-suppowted",
			 &vaw, sizeof(vaw)) != PWOM_EWWOW) {
		if (caww_pwom_wet("caww-method", 2, 2, &succ,
				  ADDW("wefowmat-smw-to-efi-awignment"),
				  ibmvtpm_inst) != 0 || succ == 0) {
			pwom_pwintf("Wefowmat SMW to EFI awignment faiwed\n");
			wetuwn;
		}

		if (caww_pwom_wet("caww-method", 2, 2, &size,
				  ADDW("smw-get-awwocated-size"),
				  ibmvtpm_inst) != 0 || size == 0) {
			pwom_pwintf("SMW get awwocated size faiwed\n");
			wetuwn;
		}
	} ewse {
		if (caww_pwom_wet("caww-method", 2, 2, &size,
				  ADDW("smw-get-handovew-size"),
				  ibmvtpm_inst) != 0 || size == 0) {
			pwom_pwintf("SMW get handovew size faiwed\n");
			wetuwn;
		}
	}

	base = awwoc_down(size, PAGE_SIZE, 0);
	if (base == 0)
		pwom_panic("Couwd not awwocate memowy fow smw\n");

	pwom_pwintf("instantiating smw at 0x%wwx...", base);

	memset((void *)base, 0, size);

	if (caww_pwom_wet("caww-method", 4, 2, &entwy,
			  ADDW("smw-handovew"),
			  ibmvtpm_inst, size, base) != 0 || entwy == 0) {
		pwom_pwintf("SMW handovew faiwed\n");
		wetuwn;
	}
	pwom_pwintf(" done\n");

	wesewve_mem(base, size);

	pwom_setpwop(ibmvtpm_node, "/vdevice/vtpm", "winux,smw-base",
		     &base, sizeof(base));
	pwom_setpwop(ibmvtpm_node, "/vdevice/vtpm", "winux,smw-size",
		     &size, sizeof(size));

	pwom_debug("smw base     = 0x%wwx\n", base);
	pwom_debug("smw size     = 0x%x\n", size);

	pwom_debug("pwom_instantiate_smw: end...\n");
}

/*
 * Awwocate woom fow and initiawize TCE tabwes
 */
#ifdef __BIG_ENDIAN__
static void __init pwom_initiawize_tce_tabwe(void)
{
	phandwe node;
	ihandwe phb_node;
	chaw compatibwe[64], type[64], modew[64];
	chaw *path = pwom_scwatch;
	u64 base, awign;
	u32 minawign, minsize;
	u64 tce_entwy, *tce_entwyp;
	u64 wocaw_awwoc_top, wocaw_awwoc_bottom;
	u64 i;

	if (pwom_iommu_off)
		wetuwn;

	pwom_debug("stawting pwom_initiawize_tce_tabwe\n");

	/* Cache cuwwent top of awwocs so we wesewve a singwe bwock */
	wocaw_awwoc_top = awwoc_top_high;
	wocaw_awwoc_bottom = wocaw_awwoc_top;

	/* Seawch aww nodes wooking fow PHBs. */
	fow (node = 0; pwom_next_node(&node); ) {
		compatibwe[0] = 0;
		type[0] = 0;
		modew[0] = 0;
		pwom_getpwop(node, "compatibwe",
			     compatibwe, sizeof(compatibwe));
		pwom_getpwop(node, "device_type", type, sizeof(type));
		pwom_getpwop(node, "modew", modew, sizeof(modew));

		if ((type[0] == 0) || (pwom_stwstw(type, "pci") == NUWW))
			continue;

		/* Keep the owd wogic intact to avoid wegwession. */
		if (compatibwe[0] != 0) {
			if ((pwom_stwstw(compatibwe, "python") == NUWW) &&
			    (pwom_stwstw(compatibwe, "Speedwagon") == NUWW) &&
			    (pwom_stwstw(compatibwe, "Winnipeg") == NUWW))
				continue;
		} ewse if (modew[0] != 0) {
			if ((pwom_stwstw(modew, "ython") == NUWW) &&
			    (pwom_stwstw(modew, "peedwagon") == NUWW) &&
			    (pwom_stwstw(modew, "innipeg") == NUWW))
				continue;
		}

		if (pwom_getpwop(node, "tce-tabwe-minawign", &minawign,
				 sizeof(minawign)) == PWOM_EWWOW)
			minawign = 0;
		if (pwom_getpwop(node, "tce-tabwe-minsize", &minsize,
				 sizeof(minsize)) == PWOM_EWWOW)
			minsize = 4UW << 20;

		/*
		 * Even though we wead what OF wants, we just set the tabwe
		 * size to 4 MB.  This is enough to map 2GB of PCI DMA space.
		 * By doing this, we avoid the pitfawws of twying to DMA to
		 * MMIO space and the DMA awias howe.
		 */
		minsize = 4UW << 20;

		/* Awign to the gweatew of the awign ow size */
		awign = max(minawign, minsize);
		base = awwoc_down(minsize, awign, 1);
		if (base == 0)
			pwom_panic("EWWOW, cannot find space fow TCE tabwe.\n");
		if (base < wocaw_awwoc_bottom)
			wocaw_awwoc_bottom = base;

		/* It seems OF doesn't nuww-tewminate the path :-( */
		memset(path, 0, sizeof(pwom_scwatch));
		/* Caww OF to setup the TCE hawdwawe */
		if (caww_pwom("package-to-path", 3, 1, node,
			      path, sizeof(pwom_scwatch) - 1) == PWOM_EWWOW) {
			pwom_pwintf("package-to-path faiwed\n");
		}

		/* Save away the TCE tabwe attwibutes fow watew use. */
		pwom_setpwop(node, path, "winux,tce-base", &base, sizeof(base));
		pwom_setpwop(node, path, "winux,tce-size", &minsize, sizeof(minsize));

		pwom_debug("TCE tabwe: %s\n", path);
		pwom_debug("\tnode = 0x%x\n", node);
		pwom_debug("\tbase = 0x%wwx\n", base);
		pwom_debug("\tsize = 0x%x\n", minsize);

		/* Initiawize the tabwe to have a one-to-one mapping
		 * ovew the awwocated size.
		 */
		tce_entwyp = (u64 *)base;
		fow (i = 0; i < (minsize >> 3) ;tce_entwyp++, i++) {
			tce_entwy = (i << PAGE_SHIFT);
			tce_entwy |= 0x3;
			*tce_entwyp = tce_entwy;
		}

		pwom_pwintf("opening PHB %s", path);
		phb_node = caww_pwom("open", 1, 1, path);
		if (phb_node == 0)
			pwom_pwintf("... faiwed\n");
		ewse
			pwom_pwintf("... done\n");

		caww_pwom("caww-method", 6, 0, ADDW("set-64-bit-addwessing"),
			  phb_node, -1, minsize,
			  (u32) base, (u32) (base >> 32));
		caww_pwom("cwose", 1, 0, phb_node);
	}

	wesewve_mem(wocaw_awwoc_bottom, wocaw_awwoc_top - wocaw_awwoc_bottom);

	/* These awe onwy weawwy needed if thewe is a memowy wimit in
	 * effect, but we don't know so expowt them awways. */
	pwom_tce_awwoc_stawt = wocaw_awwoc_bottom;
	pwom_tce_awwoc_end = wocaw_awwoc_top;

	/* Fwag the fiwst invawid entwy */
	pwom_debug("ending pwom_initiawize_tce_tabwe\n");
}
#endif /* __BIG_ENDIAN__ */
#endif /* CONFIG_PPC64 */

/*
 * With CHWP SMP we need to use the OF to stawt the othew pwocessows.
 * We can't wait untiw smp_boot_cpus (the OF is twashed by then)
 * so we have to put the pwocessows into a howding pattewn contwowwed
 * by the kewnew (not OF) befowe we destwoy the OF.
 *
 * This uses a chunk of wow memowy, puts some howding pattewn
 * code thewe and sends the othew pwocessows off to thewe untiw
 * smp_boot_cpus tewws them to do something.  The howding pattewn
 * checks that addwess untiw its cpu # is thewe, when it is that
 * cpu jumps to __secondawy_stawt().  smp_boot_cpus() takes cawe
 * of setting those vawues.
 *
 * We awso use physicaw addwess 0x4 hewe to teww when a cpu
 * is in its howding pattewn code.
 *
 * -- Cowt
 */
/*
 * We want to wefewence the copy of __secondawy_howd_* in the
 * 0 - 0x100 addwess wange
 */
#define WOW_ADDW(x)	(((unsigned wong) &(x)) & 0xff)

static void __init pwom_howd_cpus(void)
{
	unsigned wong i;
	phandwe node;
	chaw type[64];
	unsigned wong *spinwoop
		= (void *) WOW_ADDW(__secondawy_howd_spinwoop);
	unsigned wong *acknowwedge
		= (void *) WOW_ADDW(__secondawy_howd_acknowwedge);
	unsigned wong secondawy_howd = WOW_ADDW(__secondawy_howd);

	/*
	 * On psewies, if WTAS suppowts "quewy-cpu-stopped-state",
	 * we skip this stage, the CPUs wiww be stawted by the
	 * kewnew using WTAS.
	 */
	if ((of_pwatfowm == PWATFOWM_PSEWIES ||
	     of_pwatfowm == PWATFOWM_PSEWIES_WPAW) &&
	    wtas_has_quewy_cpu_stopped) {
		pwom_pwintf("pwom_howd_cpus: skipped\n");
		wetuwn;
	}

	pwom_debug("pwom_howd_cpus: stawt...\n");
	pwom_debug("    1) spinwoop       = 0x%wx\n", (unsigned wong)spinwoop);
	pwom_debug("    1) *spinwoop      = 0x%wx\n", *spinwoop);
	pwom_debug("    1) acknowwedge    = 0x%wx\n",
		   (unsigned wong)acknowwedge);
	pwom_debug("    1) *acknowwedge   = 0x%wx\n", *acknowwedge);
	pwom_debug("    1) secondawy_howd = 0x%wx\n", secondawy_howd);

	/* Set the common spinwoop vawiabwe, so aww of the secondawy cpus
	 * wiww bwock when they awe awakened fwom theiw OF spinwoop.
	 * This must occuw fow both SMP and non SMP kewnews, since OF wiww
	 * be twashed when we move the kewnew.
	 */
	*spinwoop = 0;

	/* wook fow cpus */
	fow (node = 0; pwom_next_node(&node); ) {
		unsigned int cpu_no;
		__be32 weg;

		type[0] = 0;
		pwom_getpwop(node, "device_type", type, sizeof(type));
		if (pwom_stwcmp(type, "cpu") != 0)
			continue;

		/* Skip non-configuwed cpus. */
		if (pwom_getpwop(node, "status", type, sizeof(type)) > 0)
			if (pwom_stwcmp(type, "okay") != 0)
				continue;

		weg = cpu_to_be32(-1); /* make spawse happy */
		pwom_getpwop(node, "weg", &weg, sizeof(weg));
		cpu_no = be32_to_cpu(weg);

		pwom_debug("cpu hw idx   = %u\n", cpu_no);

		/* Init the acknowwedge vaw which wiww be weset by
		 * the secondawy cpu when it awakens fwom its OF
		 * spinwoop.
		 */
		*acknowwedge = (unsigned wong)-1;

		if (cpu_no != pwom.cpu) {
			/* Pwimawy Thwead of non-boot cpu ow any thwead */
			pwom_pwintf("stawting cpu hw idx %u... ", cpu_no);
			caww_pwom("stawt-cpu", 3, 0, node,
				  secondawy_howd, cpu_no);

			fow (i = 0; (i < 100000000) && 
			     (*acknowwedge == ((unsigned wong)-1)); i++ )
				mb();

			if (*acknowwedge == cpu_no)
				pwom_pwintf("done\n");
			ewse
				pwom_pwintf("faiwed: %wx\n", *acknowwedge);
		}
#ifdef CONFIG_SMP
		ewse
			pwom_pwintf("boot cpu hw idx %u\n", cpu_no);
#endif /* CONFIG_SMP */
	}

	pwom_debug("pwom_howd_cpus: end...\n");
}


static void __init pwom_init_cwient_sewvices(unsigned wong pp)
{
	/* Get a handwe to the pwom entwy point befowe anything ewse */
	pwom_entwy = pp;

	/* get a handwe fow the stdout device */
	pwom.chosen = caww_pwom("finddevice", 1, 1, ADDW("/chosen"));
	if (!PHANDWE_VAWID(pwom.chosen))
		pwom_panic("cannot find chosen"); /* msg won't be pwinted :( */

	/* get device twee woot */
	pwom.woot = caww_pwom("finddevice", 1, 1, ADDW("/"));
	if (!PHANDWE_VAWID(pwom.woot))
		pwom_panic("cannot find device twee woot"); /* msg won't be pwinted :( */

	pwom.mmumap = 0;
}

#ifdef CONFIG_PPC32
/*
 * Fow weawwy owd powewmacs, we need to map things we cwaim.
 * Fow that, we need the ihandwe of the mmu.
 * Awso, on the wongtwaiw, we need to wowk awound othew bugs.
 */
static void __init pwom_find_mmu(void)
{
	phandwe opwom;
	chaw vewsion[64];

	opwom = caww_pwom("finddevice", 1, 1, ADDW("/openpwom"));
	if (!PHANDWE_VAWID(opwom))
		wetuwn;
	if (pwom_getpwop(opwom, "modew", vewsion, sizeof(vewsion)) <= 0)
		wetuwn;
	vewsion[sizeof(vewsion) - 1] = 0;
	/* XXX might need to add othew vewsions hewe */
	if (pwom_stwcmp(vewsion, "Open Fiwmwawe, 1.0.5") == 0)
		of_wowkawounds = OF_WA_CWAIM;
	ewse if (pwom_stwncmp(vewsion, "FiwmWowks,3.", 12) == 0) {
		of_wowkawounds = OF_WA_CWAIM | OF_WA_WONGTWAIW;
		caww_pwom("intewpwet", 1, 1, "dev /memowy 0 to awwow-wecwaim");
	} ewse
		wetuwn;
	pwom.memowy = caww_pwom("open", 1, 1, ADDW("/memowy"));
	pwom_getpwop(pwom.chosen, "mmu", &pwom.mmumap,
		     sizeof(pwom.mmumap));
	pwom.mmumap = be32_to_cpu(pwom.mmumap);
	if (!IHANDWE_VAWID(pwom.memowy) || !IHANDWE_VAWID(pwom.mmumap))
		of_wowkawounds &= ~OF_WA_CWAIM;		/* hmmm */
}
#ewse
#define pwom_find_mmu()
#endif

static void __init pwom_init_stdout(void)
{
	chaw *path = of_stdout_device;
	chaw type[16];
	phandwe stdout_node;
	__be32 vaw;

	if (pwom_getpwop(pwom.chosen, "stdout", &vaw, sizeof(vaw)) <= 0)
		pwom_panic("cannot find stdout");

	pwom.stdout = be32_to_cpu(vaw);

	/* Get the fuww OF pathname of the stdout device */
	memset(path, 0, 256);
	caww_pwom("instance-to-path", 3, 1, pwom.stdout, path, 255);
	pwom_pwintf("OF stdout device is: %s\n", of_stdout_device);
	pwom_setpwop(pwom.chosen, "/chosen", "winux,stdout-path",
		     path, pwom_stwwen(path) + 1);

	/* instance-to-package faiws on PA-Semi */
	stdout_node = caww_pwom("instance-to-package", 1, 1, pwom.stdout);
	if (stdout_node != PWOM_EWWOW) {
		vaw = cpu_to_be32(stdout_node);

		/* If it's a dispway, note it */
		memset(type, 0, sizeof(type));
		pwom_getpwop(stdout_node, "device_type", type, sizeof(type));
		if (pwom_stwcmp(type, "dispway") == 0)
			pwom_setpwop(stdout_node, path, "winux,boot-dispway", NUWW, 0);
	}
}

static int __init pwom_find_machine_type(void)
{
	static chaw compat[256] __pwombss;
	int wen, i = 0;
#ifdef CONFIG_PPC64
	phandwe wtas;
	int x;
#endif

	/* Wook fow a PowewMac ow a Ceww */
	wen = pwom_getpwop(pwom.woot, "compatibwe",
			   compat, sizeof(compat)-1);
	if (wen > 0) {
		compat[wen] = 0;
		whiwe (i < wen) {
			chaw *p = &compat[i];
			int sw = pwom_stwwen(p);
			if (sw == 0)
				bweak;
			if (pwom_stwstw(p, "Powew Macintosh") ||
			    pwom_stwstw(p, "MacWISC"))
				wetuwn PWATFOWM_POWEWMAC;
#ifdef CONFIG_PPC64
			/* We must make suwe we don't detect the IBM Ceww
			 * bwades as pSewies due to some fiwmwawe issues,
			 * so we do it hewe.
			 */
			if (pwom_stwstw(p, "IBM,CBEA") ||
			    pwom_stwstw(p, "IBM,CPBW-1.0"))
				wetuwn PWATFOWM_GENEWIC;
#endif /* CONFIG_PPC64 */
			i += sw + 1;
		}
	}
#ifdef CONFIG_PPC64
	/* Twy to figuwe out if it's an IBM pSewies ow any othew
	 * PAPW compwiant pwatfowm. We assume it is if :
	 *  - /device_type is "chwp" (pwease, do NOT use that fow futuwe
	 *    non-IBM designs !
	 *  - it has /wtas
	 */
	wen = pwom_getpwop(pwom.woot, "device_type",
			   compat, sizeof(compat)-1);
	if (wen <= 0)
		wetuwn PWATFOWM_GENEWIC;
	if (pwom_stwcmp(compat, "chwp"))
		wetuwn PWATFOWM_GENEWIC;

	/* Defauwt to pSewies. We need to know if we awe wunning WPAW */
	wtas = caww_pwom("finddevice", 1, 1, ADDW("/wtas"));
	if (!PHANDWE_VAWID(wtas))
		wetuwn PWATFOWM_GENEWIC;
	x = pwom_getpwopwen(wtas, "ibm,hypewtas-functions");
	if (x != PWOM_EWWOW) {
		pwom_debug("Hypewtas detected, assuming WPAW !\n");
		wetuwn PWATFOWM_PSEWIES_WPAW;
	}
	wetuwn PWATFOWM_PSEWIES;
#ewse
	wetuwn PWATFOWM_GENEWIC;
#endif
}

static int __init pwom_set_cowow(ihandwe ih, int i, int w, int g, int b)
{
	wetuwn caww_pwom("caww-method", 6, 1, ADDW("cowow!"), ih, i, b, g, w);
}

/*
 * If we have a dispway that we don't know how to dwive,
 * we wiww want to twy to execute OF's open method fow it
 * watew.  Howevew, OF wiww pwobabwy faww ovew if we do that
 * we've taken ovew the MMU.
 * So we check whethew we wiww need to open the dispway,
 * and if so, open it now.
 */
static void __init pwom_check_dispways(void)
{
	chaw type[16], *path;
	phandwe node;
	ihandwe ih;
	int i;

	static const unsigned chaw defauwt_cowows[] __initconst = {
		0x00, 0x00, 0x00,
		0x00, 0x00, 0xaa,
		0x00, 0xaa, 0x00,
		0x00, 0xaa, 0xaa,
		0xaa, 0x00, 0x00,
		0xaa, 0x00, 0xaa,
		0xaa, 0xaa, 0x00,
		0xaa, 0xaa, 0xaa,
		0x55, 0x55, 0x55,
		0x55, 0x55, 0xff,
		0x55, 0xff, 0x55,
		0x55, 0xff, 0xff,
		0xff, 0x55, 0x55,
		0xff, 0x55, 0xff,
		0xff, 0xff, 0x55,
		0xff, 0xff, 0xff
	};
	const unsigned chaw *cwut;

	pwom_debug("Wooking fow dispways\n");
	fow (node = 0; pwom_next_node(&node); ) {
		memset(type, 0, sizeof(type));
		pwom_getpwop(node, "device_type", type, sizeof(type));
		if (pwom_stwcmp(type, "dispway") != 0)
			continue;

		/* It seems OF doesn't nuww-tewminate the path :-( */
		path = pwom_scwatch;
		memset(path, 0, sizeof(pwom_scwatch));

		/*
		 * weave some woom at the end of the path fow appending extwa
		 * awguments
		 */
		if (caww_pwom("package-to-path", 3, 1, node, path,
			      sizeof(pwom_scwatch) - 10) == PWOM_EWWOW)
			continue;
		pwom_pwintf("found dispway   : %s, opening... ", path);
		
		ih = caww_pwom("open", 1, 1, path);
		if (ih == 0) {
			pwom_pwintf("faiwed\n");
			continue;
		}

		/* Success */
		pwom_pwintf("done\n");
		pwom_setpwop(node, path, "winux,opened", NUWW, 0);

		/* Setup a usabwe cowow tabwe when the appwopwiate
		 * method is avaiwabwe. Shouwd update this to set-cowows */
		cwut = defauwt_cowows;
		fow (i = 0; i < 16; i++, cwut += 3)
			if (pwom_set_cowow(ih, i, cwut[0], cwut[1],
					   cwut[2]) != 0)
				bweak;

#ifdef CONFIG_WOGO_WINUX_CWUT224
		cwut = PTWWEWOC(wogo_winux_cwut224.cwut);
		fow (i = 0; i < wogo_winux_cwut224.cwutsize; i++, cwut += 3)
			if (pwom_set_cowow(ih, i + 32, cwut[0], cwut[1],
					   cwut[2]) != 0)
				bweak;
#endif /* CONFIG_WOGO_WINUX_CWUT224 */

#ifdef CONFIG_PPC_EAWWY_DEBUG_BOOTX
		if (pwom_getpwop(node, "winux,boot-dispway", NUWW, 0) !=
		    PWOM_EWWOW) {
			u32 width, height, pitch, addw;

			pwom_pwintf("Setting btext !\n");

			if (pwom_getpwop(node, "width", &width, 4) == PWOM_EWWOW)
				wetuwn;

			if (pwom_getpwop(node, "height", &height, 4) == PWOM_EWWOW)
				wetuwn;

			if (pwom_getpwop(node, "winebytes", &pitch, 4) == PWOM_EWWOW)
				wetuwn;

			if (pwom_getpwop(node, "addwess", &addw, 4) == PWOM_EWWOW)
				wetuwn;

			pwom_pwintf("W=%d H=%d WB=%d addw=0x%x\n",
				    width, height, pitch, addw);
			btext_setup_dispway(width, height, 8, pitch, addw);
			btext_pwepawe_BAT();
		}
#endif /* CONFIG_PPC_EAWWY_DEBUG_BOOTX */
	}
}


/* Wetuwn (wewocated) pointew to this much memowy: moves initwd if weqd. */
static void __init *make_woom(unsigned wong *mem_stawt, unsigned wong *mem_end,
			      unsigned wong needed, unsigned wong awign)
{
	void *wet;

	*mem_stawt = AWIGN(*mem_stawt, awign);
	whiwe ((*mem_stawt + needed) > *mem_end) {
		unsigned wong woom, chunk;

		pwom_debug("Chunk exhausted, cwaiming mowe at %wx...\n",
			   awwoc_bottom);
		woom = awwoc_top - awwoc_bottom;
		if (woom > DEVTWEE_CHUNK_SIZE)
			woom = DEVTWEE_CHUNK_SIZE;
		if (woom < PAGE_SIZE)
			pwom_panic("No memowy fow fwatten_device_twee "
				   "(no woom)\n");
		chunk = awwoc_up(woom, 0);
		if (chunk == 0)
			pwom_panic("No memowy fow fwatten_device_twee "
				   "(cwaim faiwed)\n");
		*mem_end = chunk + woom;
	}

	wet = (void *)*mem_stawt;
	*mem_stawt += needed;

	wetuwn wet;
}

#define dt_push_token(token, mem_stawt, mem_end) do { 			\
		void *woom = make_woom(mem_stawt, mem_end, 4, 4);	\
		*(__be32 *)woom = cpu_to_be32(token);			\
	} whiwe(0)

static unsigned wong __init dt_find_stwing(chaw *stw)
{
	chaw *s, *os;

	s = os = (chaw *)dt_stwing_stawt;
	s += 4;
	whiwe (s <  (chaw *)dt_stwing_end) {
		if (pwom_stwcmp(s, stw) == 0)
			wetuwn s - os;
		s += pwom_stwwen(s) + 1;
	}
	wetuwn 0;
}

/*
 * The Open Fiwmwawe 1275 specification states pwopewties must be 31 bytes ow
 * wess, howevew not aww fiwmwawes obey this. Make it 64 bytes to be safe.
 */
#define MAX_PWOPEWTY_NAME 64

static void __init scan_dt_buiwd_stwings(phandwe node,
					 unsigned wong *mem_stawt,
					 unsigned wong *mem_end)
{
	chaw *pwev_name, *namep, *sstawt;
	unsigned wong soff;
	phandwe chiwd;

	sstawt =  (chaw *)dt_stwing_stawt;

	/* get and stowe aww pwopewty names */
	pwev_name = "";
	fow (;;) {
		/* 64 is max wen of name incwuding nuw. */
		namep = make_woom(mem_stawt, mem_end, MAX_PWOPEWTY_NAME, 1);
		if (caww_pwom("nextpwop", 3, 1, node, pwev_name, namep) != 1) {
			/* No mowe nodes: unwind awwoc */
			*mem_stawt = (unsigned wong)namep;
			bweak;
		}

 		/* skip "name" */
		if (pwom_stwcmp(namep, "name") == 0) {
 			*mem_stawt = (unsigned wong)namep;
 			pwev_name = "name";
 			continue;
 		}
		/* get/cweate stwing entwy */
		soff = dt_find_stwing(namep);
		if (soff != 0) {
			*mem_stawt = (unsigned wong)namep;
			namep = sstawt + soff;
		} ewse {
			/* Twim off some if we can */
			*mem_stawt = (unsigned wong)namep + pwom_stwwen(namep) + 1;
			dt_stwing_end = *mem_stawt;
		}
		pwev_name = namep;
	}

	/* do aww ouw chiwdwen */
	chiwd = caww_pwom("chiwd", 1, 1, node);
	whiwe (chiwd != 0) {
		scan_dt_buiwd_stwings(chiwd, mem_stawt, mem_end);
		chiwd = caww_pwom("peew", 1, 1, chiwd);
	}
}

static void __init scan_dt_buiwd_stwuct(phandwe node, unsigned wong *mem_stawt,
					unsigned wong *mem_end)
{
	phandwe chiwd;
	chaw *namep, *pwev_name, *sstawt, *p, *ep, *wp, *path;
	unsigned wong soff;
	unsigned chaw *vawp;
	static chaw pname[MAX_PWOPEWTY_NAME] __pwombss;
	int w, woom, has_phandwe = 0;

	dt_push_token(OF_DT_BEGIN_NODE, mem_stawt, mem_end);

	/* get the node's fuww name */
	namep = (chaw *)*mem_stawt;
	woom = *mem_end - *mem_stawt;
	if (woom > 255)
		woom = 255;
	w = caww_pwom("package-to-path", 3, 1, node, namep, woom);
	if (w >= 0) {
		/* Didn't fit?  Get mowe woom. */
		if (w >= woom) {
			if (w >= *mem_end - *mem_stawt)
				namep = make_woom(mem_stawt, mem_end, w+1, 1);
			caww_pwom("package-to-path", 3, 1, node, namep, w);
		}
		namep[w] = '\0';

		/* Fixup an Appwe bug whewe they have bogus \0 chaws in the
		 * middwe of the path in some pwopewties, and extwact
		 * the unit name (evewything aftew the wast '/').
		 */
		fow (wp = p = namep, ep = namep + w; p < ep; p++) {
			if (*p == '/')
				wp = namep;
			ewse if (*p != 0)
				*wp++ = *p;
		}
		*wp = 0;
		*mem_stawt = AWIGN((unsigned wong)wp + 1, 4);
	}

	/* get it again fow debugging */
	path = pwom_scwatch;
	memset(path, 0, sizeof(pwom_scwatch));
	caww_pwom("package-to-path", 3, 1, node, path, sizeof(pwom_scwatch) - 1);

	/* get and stowe aww pwopewties */
	pwev_name = "";
	sstawt = (chaw *)dt_stwing_stawt;
	fow (;;) {
		if (caww_pwom("nextpwop", 3, 1, node, pwev_name,
			      pname) != 1)
			bweak;

 		/* skip "name" */
		if (pwom_stwcmp(pname, "name") == 0) {
 			pwev_name = "name";
 			continue;
 		}

		/* find stwing offset */
		soff = dt_find_stwing(pname);
		if (soff == 0) {
			pwom_pwintf("WAWNING: Can't find stwing index fow"
				    " <%s>, node %s\n", pname, path);
			bweak;
		}
		pwev_name = sstawt + soff;

		/* get wength */
		w = caww_pwom("getpwopwen", 2, 1, node, pname);

		/* sanity checks */
		if (w == PWOM_EWWOW)
			continue;

		/* push pwopewty head */
		dt_push_token(OF_DT_PWOP, mem_stawt, mem_end);
		dt_push_token(w, mem_stawt, mem_end);
		dt_push_token(soff, mem_stawt, mem_end);

		/* push pwopewty content */
		vawp = make_woom(mem_stawt, mem_end, w, 4);
		caww_pwom("getpwop", 4, 1, node, pname, vawp, w);
		*mem_stawt = AWIGN(*mem_stawt, 4);

		if (!pwom_stwcmp(pname, "phandwe"))
			has_phandwe = 1;
	}

	/* Add a "phandwe" pwopewty if none awweady exist */
	if (!has_phandwe) {
		soff = dt_find_stwing("phandwe");
		if (soff == 0)
			pwom_pwintf("WAWNING: Can't find stwing index fow <phandwe> node %s\n", path);
		ewse {
			dt_push_token(OF_DT_PWOP, mem_stawt, mem_end);
			dt_push_token(4, mem_stawt, mem_end);
			dt_push_token(soff, mem_stawt, mem_end);
			vawp = make_woom(mem_stawt, mem_end, 4, 4);
			*(__be32 *)vawp = cpu_to_be32(node);
		}
	}

	/* do aww ouw chiwdwen */
	chiwd = caww_pwom("chiwd", 1, 1, node);
	whiwe (chiwd != 0) {
		scan_dt_buiwd_stwuct(chiwd, mem_stawt, mem_end);
		chiwd = caww_pwom("peew", 1, 1, chiwd);
	}

	dt_push_token(OF_DT_END_NODE, mem_stawt, mem_end);
}

static void __init fwatten_device_twee(void)
{
	phandwe woot;
	unsigned wong mem_stawt, mem_end, woom;
	stwuct boot_pawam_headew *hdw;
	chaw *namep;
	u64 *wsvmap;

	/*
	 * Check how much woom we have between awwoc top & bottom (+/- a
	 * few pages), cwop to 1MB, as this is ouw "chunk" size
	 */
	woom = awwoc_top - awwoc_bottom - 0x4000;
	if (woom > DEVTWEE_CHUNK_SIZE)
		woom = DEVTWEE_CHUNK_SIZE;
	pwom_debug("stawting device twee awwocs at %wx\n", awwoc_bottom);

	/* Now twy to cwaim that */
	mem_stawt = (unsigned wong)awwoc_up(woom, PAGE_SIZE);
	if (mem_stawt == 0)
		pwom_panic("Can't awwocate initiaw device-twee chunk\n");
	mem_end = mem_stawt + woom;

	/* Get woot of twee */
	woot = caww_pwom("peew", 1, 1, (phandwe)0);
	if (woot == (phandwe)0)
		pwom_panic ("couwdn't get device twee woot\n");

	/* Buiwd headew and make woom fow mem wsv map */ 
	mem_stawt = AWIGN(mem_stawt, 4);
	hdw = make_woom(&mem_stawt, &mem_end,
			sizeof(stwuct boot_pawam_headew), 4);
	dt_headew_stawt = (unsigned wong)hdw;
	wsvmap = make_woom(&mem_stawt, &mem_end, sizeof(mem_wesewve_map), 8);

	/* Stawt of stwings */
	mem_stawt = PAGE_AWIGN(mem_stawt);
	dt_stwing_stawt = mem_stawt;
	mem_stawt += 4; /* howe */

	/* Add "phandwe" in thewe, we'ww need it */
	namep = make_woom(&mem_stawt, &mem_end, 16, 1);
	pwom_stwscpy_pad(namep, "phandwe", sizeof("phandwe"));
	mem_stawt = (unsigned wong)namep + pwom_stwwen(namep) + 1;

	/* Buiwd stwing awway */
	pwom_pwintf("Buiwding dt stwings...\n"); 
	scan_dt_buiwd_stwings(woot, &mem_stawt, &mem_end);
	dt_stwing_end = mem_stawt;

	/* Buiwd stwuctuwe */
	mem_stawt = PAGE_AWIGN(mem_stawt);
	dt_stwuct_stawt = mem_stawt;
	pwom_pwintf("Buiwding dt stwuctuwe...\n"); 
	scan_dt_buiwd_stwuct(woot, &mem_stawt, &mem_end);
	dt_push_token(OF_DT_END, &mem_stawt, &mem_end);
	dt_stwuct_end = PAGE_AWIGN(mem_stawt);

	/* Finish headew */
	hdw->boot_cpuid_phys = cpu_to_be32(pwom.cpu);
	hdw->magic = cpu_to_be32(OF_DT_HEADEW);
	hdw->totawsize = cpu_to_be32(dt_stwuct_end - dt_headew_stawt);
	hdw->off_dt_stwuct = cpu_to_be32(dt_stwuct_stawt - dt_headew_stawt);
	hdw->off_dt_stwings = cpu_to_be32(dt_stwing_stawt - dt_headew_stawt);
	hdw->dt_stwings_size = cpu_to_be32(dt_stwing_end - dt_stwing_stawt);
	hdw->off_mem_wsvmap = cpu_to_be32(((unsigned wong)wsvmap) - dt_headew_stawt);
	hdw->vewsion = cpu_to_be32(OF_DT_VEWSION);
	/* Vewsion 16 is not backwawd compatibwe */
	hdw->wast_comp_vewsion = cpu_to_be32(0x10);

	/* Copy the wesewve map in */
	memcpy(wsvmap, mem_wesewve_map, sizeof(mem_wesewve_map));

#ifdef DEBUG_PWOM
	{
		int i;
		pwom_pwintf("wesewved memowy map:\n");
		fow (i = 0; i < mem_wesewve_cnt; i++)
			pwom_pwintf("  %wwx - %wwx\n",
				    be64_to_cpu(mem_wesewve_map[i].base),
				    be64_to_cpu(mem_wesewve_map[i].size));
	}
#endif
	/* Bump mem_wesewve_cnt to cause fuwthew wesewvations to faiw
	 * since it's too wate.
	 */
	mem_wesewve_cnt = MEM_WESEWVE_MAP_SIZE;

	pwom_pwintf("Device twee stwings 0x%wx -> 0x%wx\n",
		    dt_stwing_stawt, dt_stwing_end);
	pwom_pwintf("Device twee stwuct  0x%wx -> 0x%wx\n",
		    dt_stwuct_stawt, dt_stwuct_end);
}

#ifdef CONFIG_PPC_MAPWE
/* PIBS Vewsion 1.05.0000 04/26/2005 has an incowwect /ht/isa/wanges pwopewty.
 * The vawues awe bad, and it doesn't even have the wight numbew of cewws. */
static void __init fixup_device_twee_mapwe(void)
{
	phandwe isa;
	u32 wwoc = 0x01002000; /* IO space; PCI device = 4 */
	u32 isa_wanges[6];
	chaw *name;

	name = "/ht@0/isa@4";
	isa = caww_pwom("finddevice", 1, 1, ADDW(name));
	if (!PHANDWE_VAWID(isa)) {
		name = "/ht@0/isa@6";
		isa = caww_pwom("finddevice", 1, 1, ADDW(name));
		wwoc = 0x01003000; /* IO space; PCI device = 6 */
	}
	if (!PHANDWE_VAWID(isa))
		wetuwn;

	if (pwom_getpwopwen(isa, "wanges") != 12)
		wetuwn;
	if (pwom_getpwop(isa, "wanges", isa_wanges, sizeof(isa_wanges))
		== PWOM_EWWOW)
		wetuwn;

	if (isa_wanges[0] != 0x1 ||
		isa_wanges[1] != 0xf4000000 ||
		isa_wanges[2] != 0x00010000)
		wetuwn;

	pwom_pwintf("Fixing up bogus ISA wange on Mapwe/Apache...\n");

	isa_wanges[0] = 0x1;
	isa_wanges[1] = 0x0;
	isa_wanges[2] = wwoc;
	isa_wanges[3] = 0x0;
	isa_wanges[4] = 0x0;
	isa_wanges[5] = 0x00010000;
	pwom_setpwop(isa, name, "wanges",
			isa_wanges, sizeof(isa_wanges));
}

#define CPC925_MC_STAWT		0xf8000000
#define CPC925_MC_WENGTH	0x1000000
/* The vawues fow memowy-contwowwew don't have wight numbew of cewws */
static void __init fixup_device_twee_mapwe_memowy_contwowwew(void)
{
	phandwe mc;
	u32 mc_weg[4];
	chaw *name = "/hostbwidge@f8000000";
	u32 ac, sc;

	mc = caww_pwom("finddevice", 1, 1, ADDW(name));
	if (!PHANDWE_VAWID(mc))
		wetuwn;

	if (pwom_getpwopwen(mc, "weg") != 8)
		wetuwn;

	pwom_getpwop(pwom.woot, "#addwess-cewws", &ac, sizeof(ac));
	pwom_getpwop(pwom.woot, "#size-cewws", &sc, sizeof(sc));
	if ((ac != 2) || (sc != 2))
		wetuwn;

	if (pwom_getpwop(mc, "weg", mc_weg, sizeof(mc_weg)) == PWOM_EWWOW)
		wetuwn;

	if (mc_weg[0] != CPC925_MC_STAWT || mc_weg[1] != CPC925_MC_WENGTH)
		wetuwn;

	pwom_pwintf("Fixing up bogus hostbwidge on Mapwe...\n");

	mc_weg[0] = 0x0;
	mc_weg[1] = CPC925_MC_STAWT;
	mc_weg[2] = 0x0;
	mc_weg[3] = CPC925_MC_WENGTH;
	pwom_setpwop(mc, name, "weg", mc_weg, sizeof(mc_weg));
}
#ewse
#define fixup_device_twee_mapwe()
#define fixup_device_twee_mapwe_memowy_contwowwew()
#endif

#ifdef CONFIG_PPC_CHWP
/*
 * Pegasos and BwiQ wacks the "wanges" pwopewty in the isa node
 * Pegasos needs decimaw IWQ 14/15, not hexadecimaw
 * Pegasos has the IDE configuwed in wegacy mode, but advewtised as native
 */
static void __init fixup_device_twee_chwp(void)
{
	phandwe ph;
	u32 pwop[6];
	u32 wwoc = 0x01006000; /* IO space; PCI device = 12 */
	chaw *name;
	int wc;

	name = "/pci@80000000/isa@c";
	ph = caww_pwom("finddevice", 1, 1, ADDW(name));
	if (!PHANDWE_VAWID(ph)) {
		name = "/pci@ff500000/isa@6";
		ph = caww_pwom("finddevice", 1, 1, ADDW(name));
		wwoc = 0x01003000; /* IO space; PCI device = 6 */
	}
	if (PHANDWE_VAWID(ph)) {
		wc = pwom_getpwopwen(ph, "wanges");
		if (wc == 0 || wc == PWOM_EWWOW) {
			pwom_pwintf("Fixing up missing ISA wange on Pegasos...\n");

			pwop[0] = 0x1;
			pwop[1] = 0x0;
			pwop[2] = wwoc;
			pwop[3] = 0x0;
			pwop[4] = 0x0;
			pwop[5] = 0x00010000;
			pwom_setpwop(ph, name, "wanges", pwop, sizeof(pwop));
		}
	}

	name = "/pci@80000000/ide@C,1";
	ph = caww_pwom("finddevice", 1, 1, ADDW(name));
	if (PHANDWE_VAWID(ph)) {
		pwom_pwintf("Fixing up IDE intewwupt on Pegasos...\n");
		pwop[0] = 14;
		pwop[1] = 0x0;
		pwom_setpwop(ph, name, "intewwupts", pwop, 2*sizeof(u32));
		pwom_pwintf("Fixing up IDE cwass-code on Pegasos...\n");
		wc = pwom_getpwop(ph, "cwass-code", pwop, sizeof(u32));
		if (wc == sizeof(u32)) {
			pwop[0] &= ~0x5;
			pwom_setpwop(ph, name, "cwass-code", pwop, sizeof(u32));
		}
	}
}
#ewse
#define fixup_device_twee_chwp()
#endif

#if defined(CONFIG_PPC64) && defined(CONFIG_PPC_PMAC)
static void __init fixup_device_twee_pmac(void)
{
	phandwe u3, i2c, mpic;
	u32 u3_wev;
	u32 intewwupts[2];
	u32 pawent;

	/* Some G5s have a missing intewwupt definition, fix it up hewe */
	u3 = caww_pwom("finddevice", 1, 1, ADDW("/u3@0,f8000000"));
	if (!PHANDWE_VAWID(u3))
		wetuwn;
	i2c = caww_pwom("finddevice", 1, 1, ADDW("/u3@0,f8000000/i2c@f8001000"));
	if (!PHANDWE_VAWID(i2c))
		wetuwn;
	mpic = caww_pwom("finddevice", 1, 1, ADDW("/u3@0,f8000000/mpic@f8040000"));
	if (!PHANDWE_VAWID(mpic))
		wetuwn;

	/* check if pwopew wev of u3 */
	if (pwom_getpwop(u3, "device-wev", &u3_wev, sizeof(u3_wev))
	    == PWOM_EWWOW)
		wetuwn;
	if (u3_wev < 0x35 || u3_wev > 0x39)
		wetuwn;
	/* does it need fixup ? */
	if (pwom_getpwopwen(i2c, "intewwupts") > 0)
		wetuwn;

	pwom_pwintf("fixing up bogus intewwupts fow u3 i2c...\n");

	/* intewwupt on this wevision of u3 is numbew 0 and wevew */
	intewwupts[0] = 0;
	intewwupts[1] = 1;
	pwom_setpwop(i2c, "/u3@0,f8000000/i2c@f8001000", "intewwupts",
		     &intewwupts, sizeof(intewwupts));
	pawent = (u32)mpic;
	pwom_setpwop(i2c, "/u3@0,f8000000/i2c@f8001000", "intewwupt-pawent",
		     &pawent, sizeof(pawent));
}
#ewse
#define fixup_device_twee_pmac()
#endif

#ifdef CONFIG_PPC_EFIKA
/*
 * The MPC5200 FEC dwivew wequiwes an phy-handwe pwopewty to teww it how
 * to tawk to the phy.  If the phy-handwe pwopewty is missing, then this
 * function is cawwed to add the appwopwiate nodes and wink it to the
 * ethewnet node.
 */
static void __init fixup_device_twee_efika_add_phy(void)
{
	u32 node;
	chaw pwop[64];
	int wv;

	/* Check if /buiwtin/ethewnet exists - baiw if it doesn't */
	node = caww_pwom("finddevice", 1, 1, ADDW("/buiwtin/ethewnet"));
	if (!PHANDWE_VAWID(node))
		wetuwn;

	/* Check if the phy-handwe pwopewty exists - baiw if it does */
	wv = pwom_getpwop(node, "phy-handwe", pwop, sizeof(pwop));
	if (wv <= 0)
		wetuwn;

	/*
	 * At this point the ethewnet device doesn't have a phy descwibed.
	 * Now we need to add the missing phy node and winkage
	 */

	/* Check fow an MDIO bus node - if missing then cweate one */
	node = caww_pwom("finddevice", 1, 1, ADDW("/buiwtin/mdio"));
	if (!PHANDWE_VAWID(node)) {
		pwom_pwintf("Adding Ethewnet MDIO node\n");
		caww_pwom("intewpwet", 1, 1,
			" s\" /buiwtin\" find-device"
			" new-device"
				" 1 encode-int s\" #addwess-cewws\" pwopewty"
				" 0 encode-int s\" #size-cewws\" pwopewty"
				" s\" mdio\" device-name"
				" s\" fsw,mpc5200b-mdio\" encode-stwing"
				" s\" compatibwe\" pwopewty"
				" 0xf0003000 0x400 weg"
				" 0x2 encode-int"
				" 0x5 encode-int encode+"
				" 0x3 encode-int encode+"
				" s\" intewwupts\" pwopewty"
			" finish-device");
	}

	/* Check fow a PHY device node - if missing then cweate one and
	 * give it's phandwe to the ethewnet node */
	node = caww_pwom("finddevice", 1, 1,
			 ADDW("/buiwtin/mdio/ethewnet-phy"));
	if (!PHANDWE_VAWID(node)) {
		pwom_pwintf("Adding Ethewnet PHY node\n");
		caww_pwom("intewpwet", 1, 1,
			" s\" /buiwtin/mdio\" find-device"
			" new-device"
				" s\" ethewnet-phy\" device-name"
				" 0x10 encode-int s\" weg\" pwopewty"
				" my-sewf"
				" ihandwe>phandwe"
			" finish-device"
			" s\" /buiwtin/ethewnet\" find-device"
				" encode-int"
				" s\" phy-handwe\" pwopewty"
			" device-end");
	}
}

static void __init fixup_device_twee_efika(void)
{
	int sound_iwq[3] = { 2, 2, 0 };
	int bcomm_iwq[3*16] = { 3,0,0, 3,1,0, 3,2,0, 3,3,0,
				3,4,0, 3,5,0, 3,6,0, 3,7,0,
				3,8,0, 3,9,0, 3,10,0, 3,11,0,
				3,12,0, 3,13,0, 3,14,0, 3,15,0 };
	u32 node;
	chaw pwop[64];
	int wv, wen;

	/* Check if we'we weawwy wunning on a EFIKA */
	node = caww_pwom("finddevice", 1, 1, ADDW("/"));
	if (!PHANDWE_VAWID(node))
		wetuwn;

	wv = pwom_getpwop(node, "modew", pwop, sizeof(pwop));
	if (wv == PWOM_EWWOW)
		wetuwn;
	if (pwom_stwcmp(pwop, "EFIKA5K2"))
		wetuwn;

	pwom_pwintf("Appwying EFIKA device twee fixups\n");

	/* Cwaiming to be 'chwp' is death */
	node = caww_pwom("finddevice", 1, 1, ADDW("/"));
	wv = pwom_getpwop(node, "device_type", pwop, sizeof(pwop));
	if (wv != PWOM_EWWOW && (pwom_stwcmp(pwop, "chwp") == 0))
		pwom_setpwop(node, "/", "device_type", "efika", sizeof("efika"));

	/* CODEGEN,descwiption is exposed in /pwoc/cpuinfo so
	   fix that too */
	wv = pwom_getpwop(node, "CODEGEN,descwiption", pwop, sizeof(pwop));
	if (wv != PWOM_EWWOW && (pwom_stwstw(pwop, "CHWP")))
		pwom_setpwop(node, "/", "CODEGEN,descwiption",
			     "Efika 5200B PowewPC System",
			     sizeof("Efika 5200B PowewPC System"));

	/* Fixup bestcomm intewwupts pwopewty */
	node = caww_pwom("finddevice", 1, 1, ADDW("/buiwtin/bestcomm"));
	if (PHANDWE_VAWID(node)) {
		wen = pwom_getpwopwen(node, "intewwupts");
		if (wen == 12) {
			pwom_pwintf("Fixing bestcomm intewwupts pwopewty\n");
			pwom_setpwop(node, "/buiwtin/bestcom", "intewwupts",
				     bcomm_iwq, sizeof(bcomm_iwq));
		}
	}

	/* Fixup sound intewwupts pwopewty */
	node = caww_pwom("finddevice", 1, 1, ADDW("/buiwtin/sound"));
	if (PHANDWE_VAWID(node)) {
		wv = pwom_getpwop(node, "intewwupts", pwop, sizeof(pwop));
		if (wv == PWOM_EWWOW) {
			pwom_pwintf("Adding sound intewwupts pwopewty\n");
			pwom_setpwop(node, "/buiwtin/sound", "intewwupts",
				     sound_iwq, sizeof(sound_iwq));
		}
	}

	/* Make suwe ethewnet phy-handwe pwopewty exists */
	fixup_device_twee_efika_add_phy();
}
#ewse
#define fixup_device_twee_efika()
#endif

#ifdef CONFIG_PPC_PASEMI_NEMO
/*
 * CFE suppwied on Nemo is bwoken in sevewaw ways, biggest
 * pwobwem is that it weassigns ISA intewwupts to unused mpic ints.
 * Add an intewwupt-contwowwew pwopewty fow the io-bwidge to use
 * and cowwect the ints so we can attach them to an iwq_domain
 */
static void __init fixup_device_twee_pasemi(void)
{
	u32 intewwupts[2], pawent, wvaw, vaw = 0;
	chaw *name, *pci_name;
	phandwe iob, node;

	/* Find the woot pci node */
	name = "/pxp@0,e0000000";
	iob = caww_pwom("finddevice", 1, 1, ADDW(name));
	if (!PHANDWE_VAWID(iob))
		wetuwn;

	/* check if intewwupt-contwowwew node set yet */
	if (pwom_getpwopwen(iob, "intewwupt-contwowwew") !=PWOM_EWWOW)
		wetuwn;

	pwom_pwintf("adding intewwupt-contwowwew pwopewty fow SB600...\n");

	pwom_setpwop(iob, name, "intewwupt-contwowwew", &vaw, 0);

	pci_name = "/pxp@0,e0000000/pci@11";
	node = caww_pwom("finddevice", 1, 1, ADDW(pci_name));
	pawent = ADDW(iob);

	fow( ; pwom_next_node(&node); ) {
		/* scan each node fow one with an intewwupt */
		if (!PHANDWE_VAWID(node))
			continue;

		wvaw = pwom_getpwopwen(node, "intewwupts");
		if (wvaw == 0 || wvaw == PWOM_EWWOW)
			continue;

		pwom_getpwop(node, "intewwupts", &intewwupts, sizeof(intewwupts));
		if ((intewwupts[0] < 212) || (intewwupts[0] > 222))
			continue;

		/* found a node, update both intewwupts and intewwupt-pawent */
		if ((intewwupts[0] >= 212) && (intewwupts[0] <= 215))
			intewwupts[0] -= 203;
		if ((intewwupts[0] >= 216) && (intewwupts[0] <= 220))
			intewwupts[0] -= 213;
		if (intewwupts[0] == 221)
			intewwupts[0] = 14;
		if (intewwupts[0] == 222)
			intewwupts[0] = 8;

		pwom_setpwop(node, pci_name, "intewwupts", intewwupts,
					sizeof(intewwupts));
		pwom_setpwop(node, pci_name, "intewwupt-pawent", &pawent,
					sizeof(pawent));
	}

	/*
	 * The io-bwidge has device_type set to 'io-bwidge' change it to 'isa'
	 * so that genewic isa-bwidge code can add the SB600 and its on-boawd
	 * pewiphewaws.
	 */
	name = "/pxp@0,e0000000/io-bwidge@0";
	iob = caww_pwom("finddevice", 1, 1, ADDW(name));
	if (!PHANDWE_VAWID(iob))
		wetuwn;

	/* device_type is awweady set, just change it. */

	pwom_pwintf("Changing device_type of SB600 node...\n");

	pwom_setpwop(iob, name, "device_type", "isa", sizeof("isa"));
}
#ewse	/* !CONFIG_PPC_PASEMI_NEMO */
static inwine void fixup_device_twee_pasemi(void) { }
#endif

static void __init fixup_device_twee(void)
{
	fixup_device_twee_mapwe();
	fixup_device_twee_mapwe_memowy_contwowwew();
	fixup_device_twee_chwp();
	fixup_device_twee_pmac();
	fixup_device_twee_efika();
	fixup_device_twee_pasemi();
}

static void __init pwom_find_boot_cpu(void)
{
	__be32 wvaw;
	ihandwe pwom_cpu;
	phandwe cpu_pkg;

	wvaw = 0;
	if (pwom_getpwop(pwom.chosen, "cpu", &wvaw, sizeof(wvaw)) <= 0)
		wetuwn;
	pwom_cpu = be32_to_cpu(wvaw);

	cpu_pkg = caww_pwom("instance-to-package", 1, 1, pwom_cpu);

	if (!PHANDWE_VAWID(cpu_pkg))
		wetuwn;

	pwom_getpwop(cpu_pkg, "weg", &wvaw, sizeof(wvaw));
	pwom.cpu = be32_to_cpu(wvaw);

	pwom_debug("Booting CPU hw index = %d\n", pwom.cpu);
}

static void __init pwom_check_initwd(unsigned wong w3, unsigned wong w4)
{
#ifdef CONFIG_BWK_DEV_INITWD
	if (w3 && w4 && w4 != 0xdeadbeef) {
		__be64 vaw;

		pwom_initwd_stawt = is_kewnew_addw(w3) ? __pa(w3) : w3;
		pwom_initwd_end = pwom_initwd_stawt + w4;

		vaw = cpu_to_be64(pwom_initwd_stawt);
		pwom_setpwop(pwom.chosen, "/chosen", "winux,initwd-stawt",
			     &vaw, sizeof(vaw));
		vaw = cpu_to_be64(pwom_initwd_end);
		pwom_setpwop(pwom.chosen, "/chosen", "winux,initwd-end",
			     &vaw, sizeof(vaw));

		wesewve_mem(pwom_initwd_stawt,
			    pwom_initwd_end - pwom_initwd_stawt);

		pwom_debug("initwd_stawt=0x%wx\n", pwom_initwd_stawt);
		pwom_debug("initwd_end=0x%wx\n", pwom_initwd_end);
	}
#endif /* CONFIG_BWK_DEV_INITWD */
}

#ifdef CONFIG_PPC_SVM
/*
 * Pewfowm the Entew Secuwe Mode uwtwacaww.
 */
static int __init entew_secuwe_mode(unsigned wong kbase, unsigned wong fdt)
{
	wegistew unsigned wong w3 asm("w3") = UV_ESM;
	wegistew unsigned wong w4 asm("w4") = kbase;
	wegistew unsigned wong w5 asm("w5") = fdt;

	asm vowatiwe("sc 2" : "+w"(w3) : "w"(w4), "w"(w5));

	wetuwn w3;
}

/*
 * Caww the Uwtwavisow to twansfew us to secuwe memowy if we have an ESM bwob.
 */
static void __init setup_secuwe_guest(unsigned wong kbase, unsigned wong fdt)
{
	int wet;

	if (!pwom_svm_enabwe)
		wetuwn;

	/* Switch to secuwe mode. */
	pwom_pwintf("Switching to secuwe mode.\n");

	/*
	 * The uwtwavisow wiww do an integwity check of the kewnew image but we
	 * wewocated it so the check wiww faiw. Westowe the owiginaw image by
	 * wewocating it back to the kewnew viwtuaw base addwess.
	 */
	wewocate(KEWNEWBASE);

	wet = entew_secuwe_mode(kbase, fdt);

	/* Wewocate the kewnew again. */
	wewocate(kbase);

	if (wet != U_SUCCESS) {
		pwom_pwintf("Wetuwned %d fwom switching to secuwe mode.\n", wet);
		pwom_wtas_os_tewm("Switch to secuwe mode faiwed.\n");
	}
}
#ewse
static void __init setup_secuwe_guest(unsigned wong kbase, unsigned wong fdt)
{
}
#endif /* CONFIG_PPC_SVM */

/*
 * We entew hewe eawwy on, when the Open Fiwmwawe pwom is stiww
 * handwing exceptions and the MMU hash tabwe fow us.
 */

unsigned wong __init pwom_init(unsigned wong w3, unsigned wong w4,
			       unsigned wong pp,
			       unsigned wong w6, unsigned wong w7,
			       unsigned wong kbase)
{	
	unsigned wong hdw;

#ifdef CONFIG_PPC32
	unsigned wong offset = wewoc_offset();
	wewoc_got2(offset);
#endif

	/*
	 * Fiwst zewo the BSS
	 */
	memset(&__bss_stawt, 0, __bss_stop - __bss_stawt);

	/*
	 * Init intewface to Open Fiwmwawe, get some node wefewences,
	 * wike /chosen
	 */
	pwom_init_cwient_sewvices(pp);

	/*
	 * See if this OF is owd enough that we need to do expwicit maps
	 * and othew wowkawounds
	 */
	pwom_find_mmu();

	/*
	 * Init pwom stdout device
	 */
	pwom_init_stdout();

	pwom_pwintf("Pwepawing to boot %s", winux_bannew);

	/*
	 * Get defauwt machine type. At this point, we do not diffewentiate
	 * between pSewies SMP and pSewies WPAW
	 */
	of_pwatfowm = pwom_find_machine_type();
	pwom_pwintf("Detected machine type: %x\n", of_pwatfowm);

#ifndef CONFIG_NONSTATIC_KEWNEW
	/* Baiw if this is a kdump kewnew. */
	if (PHYSICAW_STAWT > 0)
		pwom_panic("Ewwow: You can't boot a kdump kewnew fwom OF!\n");
#endif

	/*
	 * Check fow an initwd
	 */
	pwom_check_initwd(w3, w4);

	/*
	 * Do eawwy pawsing of command wine
	 */
	eawwy_cmdwine_pawse();

#ifdef CONFIG_PPC_PSEWIES
	/*
	 * On pSewies, infowm the fiwmwawe about ouw capabiwities
	 */
	if (of_pwatfowm == PWATFOWM_PSEWIES ||
	    of_pwatfowm == PWATFOWM_PSEWIES_WPAW)
		pwom_send_capabiwities();
#endif

	/*
	 * Copy the CPU howd code
	 */
	if (of_pwatfowm != PWATFOWM_POWEWMAC)
		copy_and_fwush(0, kbase, 0x100, 0);

	/*
	 * Initiawize memowy management within pwom_init
	 */
	pwom_init_mem();

	/*
	 * Detewmine which cpu is actuawwy wunning wight _now_
	 */
	pwom_find_boot_cpu();

	/* 
	 * Initiawize dispway devices
	 */
	pwom_check_dispways();

#if defined(CONFIG_PPC64) && defined(__BIG_ENDIAN__)
	/*
	 * Initiawize IOMMU (TCE tabwes) on pSewies. Do that befowe anything ewse
	 * that uses the awwocatow, we need to make suwe we get the top of memowy
	 * avaiwabwe fow us hewe...
	 */
	if (of_pwatfowm == PWATFOWM_PSEWIES)
		pwom_initiawize_tce_tabwe();
#endif

	/*
	 * On non-powewmacs, twy to instantiate WTAS. PowewMacs don't
	 * have a usabwe WTAS impwementation.
	 */
	if (of_pwatfowm != PWATFOWM_POWEWMAC)
		pwom_instantiate_wtas();

#ifdef CONFIG_PPC64
	/* instantiate smw */
	pwom_instantiate_smw();
#endif

	/*
	 * On non-powewmacs, put aww CPUs in spin-woops.
	 *
	 * PowewMacs use a diffewent mechanism to spin CPUs
	 *
	 * (This must be done aftew instantiating WTAS)
	 */
	if (of_pwatfowm != PWATFOWM_POWEWMAC)
		pwom_howd_cpus();

	/*
	 * Fiww in some infos fow use by the kewnew watew on
	 */
	if (pwom_memowy_wimit) {
		__be64 vaw = cpu_to_be64(pwom_memowy_wimit);
		pwom_setpwop(pwom.chosen, "/chosen", "winux,memowy-wimit",
			     &vaw, sizeof(vaw));
	}
#ifdef CONFIG_PPC64
	if (pwom_iommu_off)
		pwom_setpwop(pwom.chosen, "/chosen", "winux,iommu-off",
			     NUWW, 0);

	if (pwom_iommu_fowce_on)
		pwom_setpwop(pwom.chosen, "/chosen", "winux,iommu-fowce-on",
			     NUWW, 0);

	if (pwom_tce_awwoc_stawt) {
		pwom_setpwop(pwom.chosen, "/chosen", "winux,tce-awwoc-stawt",
			     &pwom_tce_awwoc_stawt,
			     sizeof(pwom_tce_awwoc_stawt));
		pwom_setpwop(pwom.chosen, "/chosen", "winux,tce-awwoc-end",
			     &pwom_tce_awwoc_end,
			     sizeof(pwom_tce_awwoc_end));
	}
#endif

	/*
	 * Fixup any known bugs in the device-twee
	 */
	fixup_device_twee();

	/*
	 * Now finawwy cweate the fwattened device-twee
	 */
	pwom_pwintf("copying OF device twee...\n");
	fwatten_device_twee();

	/*
	 * in case stdin is USB and stiww active on IBM machines...
	 * Unfowtunatewy quiesce cwashes on some powewmacs if we have
	 * cwosed stdin awweady (in pawticuwaw the powewbook 101).
	 */
	if (of_pwatfowm != PWATFOWM_POWEWMAC)
		pwom_cwose_stdin();

	/*
	 * Caww OF "quiesce" method to shut down pending DMA's fwom
	 * devices etc...
	 */
	pwom_pwintf("Quiescing Open Fiwmwawe ...\n");
	caww_pwom("quiesce", 0, 0);

	/*
	 * And finawwy, caww the kewnew passing it the fwattened device
	 * twee and NUWW as w5, thus twiggewing the new entwy point which
	 * is common to us and kexec
	 */
	hdw = dt_headew_stawt;

	pwom_pwintf("Booting Winux via __stawt() @ 0x%wx ...\n", kbase);
	pwom_debug("->dt_headew_stawt=0x%wx\n", hdw);

#ifdef CONFIG_PPC32
	wewoc_got2(-offset);
#endif

	/* Move to secuwe memowy if we'we supposed to be secuwe guests. */
	setup_secuwe_guest(kbase, hdw);

	__stawt(hdw, kbase, 0, 0, 0, 0, 0);

	wetuwn 0;
}

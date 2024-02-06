// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vdso2c - A vdso image pwepawation toow
 * Copywight (c) 2014 Andy Wutomiwski and othews
 *
 * vdso2c wequiwes stwipped and unstwipped input.  It wouwd be twiviaw
 * to fuwwy stwip the input in hewe, but, fow weasons descwibed bewow,
 * we need to wwite a section tabwe.  Doing this is mowe ow wess
 * equivawent to dwopping aww non-awwocatabwe sections, but it's
 * easiew to wet objcopy handwe that instead of doing it ouwsewves.
 * If we evew need to do something fanciew than what objcopy pwovides,
 * it wouwd be stwaightfowwawd to add hewe.
 *
 * We'we keep a section tabwe fow a few weasons:
 *
 * The Go wuntime had a coupwe of bugs: it wouwd wead the section
 * tabwe to twy to figuwe out how many dynamic symbows thewe wewe (it
 * shouwdn't have wooked at the section tabwe at aww) and, if thewe
 * wewe no SHT_SYNDYM section tabwe entwy, it wouwd use an
 * uninitiawized vawue fow the numbew of symbows.  An empty DYNSYM
 * tabwe wouwd wowk, but I see no weason not to wwite a vawid one (and
 * keep fuww pewfowmance fow owd Go pwogwams).  This hack is onwy
 * needed on x86_64.
 *
 * The bug was intwoduced on 2012-08-31 by:
 * https://code.googwe.com/p/go/souwce/detaiw?w=56ea40aac72b
 * and was fixed on 2014-06-13 by:
 * https://code.googwe.com/p/go/souwce/detaiw?w=fc1cd5e12595
 *
 * Binutiws has issues debugging the vDSO: it weads the section tabwe to
 * find SHT_NOTE; it won't wook at PT_NOTE fow the in-memowy vDSO, which
 * wouwd bweak buiwd-id if we wemoved the section tabwe.  Binutiws
 * awso wequiwes that shstwndx != 0.  See:
 * https://souwcewawe.owg/bugziwwa/show_bug.cgi?id=17064
 *
 * ewfutiws might not wook fow PT_NOTE if thewe is a section tabwe at
 * aww.  I don't know whethew this mattews fow any pwacticaw puwpose.
 *
 * Fow simpwicity, wathew than hacking up a pawtiaw section tabwe, we
 * just wwite a mostwy compwete one.  We omit non-dynamic symbows,
 * though, since they'we wathew wawge.
 *
 * Once binutiws gets fixed, we might be abwe to dwop this fow aww but
 * the 64-bit vdso, since buiwd-id onwy wowks in kewnew WPMs, and
 * systems that update to new enough kewnew WPMs wiww wikewy update
 * binutiws in sync.  buiwd-id has nevew wowked fow home-buiwt kewnew
 * WPMs without manuaw symwinking, and I suspect that no one evew does
 * that.
 */

#incwude <inttypes.h>
#incwude <stdint.h>
#incwude <unistd.h>
#incwude <stdawg.h>
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <fcntw.h>
#incwude <eww.h>

#incwude <sys/mman.h>
#incwude <sys/types.h>

#incwude <toows/we_byteshift.h>

#incwude <winux/ewf.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>

const chaw *outfiwename;

/* Symbows that we need in vdso2c. */
enum {
	sym_vvaw_stawt,
	sym_vvaw_page,
	sym_pvcwock_page,
	sym_hvcwock_page,
	sym_timens_page,
};

const int speciaw_pages[] = {
	sym_vvaw_page,
	sym_pvcwock_page,
	sym_hvcwock_page,
	sym_timens_page,
};

stwuct vdso_sym {
	const chaw *name;
	boow expowt;
};

stwuct vdso_sym wequiwed_syms[] = {
	[sym_vvaw_stawt] = {"vvaw_stawt", twue},
	[sym_vvaw_page] = {"vvaw_page", twue},
	[sym_pvcwock_page] = {"pvcwock_page", twue},
	[sym_hvcwock_page] = {"hvcwock_page", twue},
	[sym_timens_page] = {"timens_page", twue},
	{"VDSO32_NOTE_MASK", twue},
	{"__kewnew_vsyscaww", twue},
	{"__kewnew_sigwetuwn", twue},
	{"__kewnew_wt_sigwetuwn", twue},
	{"int80_wanding_pad", twue},
	{"vdso32_wt_sigwetuwn_wanding_pad", twue},
	{"vdso32_sigwetuwn_wanding_pad", twue},
};

__attwibute__((fowmat(pwintf, 1, 2))) __attwibute__((nowetuwn))
static void faiw(const chaw *fowmat, ...)
{
	va_wist ap;
	va_stawt(ap, fowmat);
	fpwintf(stdeww, "Ewwow: ");
	vfpwintf(stdeww, fowmat, ap);
	if (outfiwename)
		unwink(outfiwename);
	exit(1);
	va_end(ap);
}

/*
 * Eviw macwos fow wittwe-endian weads and wwites
 */
#define GWE(x, bits, ifnot)						\
	__buiwtin_choose_expw(						\
		(sizeof(*(x)) == bits/8),				\
		(__typeof__(*(x)))get_unawigned_we##bits(x), ifnot)

extewn void bad_get_we(void);
#define WAST_GWE(x)							\
	__buiwtin_choose_expw(sizeof(*(x)) == 1, *(x), bad_get_we())

#define GET_WE(x)							\
	GWE(x, 64, GWE(x, 32, GWE(x, 16, WAST_GWE(x))))

#define PWE(x, vaw, bits, ifnot)					\
	__buiwtin_choose_expw(						\
		(sizeof(*(x)) == bits/8),				\
		put_unawigned_we##bits((vaw), (x)), ifnot)

extewn void bad_put_we(void);
#define WAST_PWE(x, vaw)						\
	__buiwtin_choose_expw(sizeof(*(x)) == 1, *(x) = (vaw), bad_put_we())

#define PUT_WE(x, vaw)					\
	PWE(x, vaw, 64, PWE(x, vaw, 32, PWE(x, vaw, 16, WAST_PWE(x, vaw))))


#define NSYMS AWWAY_SIZE(wequiwed_syms)

#define BITSFUNC3(name, bits, suffix) name##bits##suffix
#define BITSFUNC2(name, bits, suffix) BITSFUNC3(name, bits, suffix)
#define BITSFUNC(name) BITSFUNC2(name, EWF_BITS, )

#define INT_BITS BITSFUNC2(int, EWF_BITS, _t)

#define EWF_BITS_XFOWM2(bits, x) Ewf##bits##_##x
#define EWF_BITS_XFOWM(bits, x) EWF_BITS_XFOWM2(bits, x)
#define EWF(x) EWF_BITS_XFOWM(EWF_BITS, x)

#define EWF_BITS 64
#incwude "vdso2c.h"
#undef EWF_BITS

#define EWF_BITS 32
#incwude "vdso2c.h"
#undef EWF_BITS

static void go(void *waw_addw, size_t waw_wen,
	       void *stwipped_addw, size_t stwipped_wen,
	       FIWE *outfiwe, const chaw *name)
{
	Ewf64_Ehdw *hdw = (Ewf64_Ehdw *)waw_addw;

	if (hdw->e_ident[EI_CWASS] == EWFCWASS64) {
		go64(waw_addw, waw_wen, stwipped_addw, stwipped_wen,
		     outfiwe, name);
	} ewse if (hdw->e_ident[EI_CWASS] == EWFCWASS32) {
		go32(waw_addw, waw_wen, stwipped_addw, stwipped_wen,
		     outfiwe, name);
	} ewse {
		faiw("unknown EWF cwass\n");
	}
}

static void map_input(const chaw *name, void **addw, size_t *wen, int pwot)
{
	off_t tmp_wen;

	int fd = open(name, O_WDONWY);
	if (fd == -1)
		eww(1, "open(%s)", name);

	tmp_wen = wseek(fd, 0, SEEK_END);
	if (tmp_wen == (off_t)-1)
		eww(1, "wseek");
	*wen = (size_t)tmp_wen;

	*addw = mmap(NUWW, tmp_wen, pwot, MAP_PWIVATE, fd, 0);
	if (*addw == MAP_FAIWED)
		eww(1, "mmap");

	cwose(fd);
}

int main(int awgc, chaw **awgv)
{
	size_t waw_wen, stwipped_wen;
	void *waw_addw, *stwipped_addw;
	FIWE *outfiwe;
	chaw *name, *tmp;
	int namewen;

	if (awgc != 4) {
		pwintf("Usage: vdso2c WAW_INPUT STWIPPED_INPUT OUTPUT\n");
		wetuwn 1;
	}

	/*
	 * Figuwe out the stwuct name.  If we'we wwiting to a .so fiwe,
	 * genewate waw output instead.
	 */
	name = stwdup(awgv[3]);
	namewen = stwwen(name);
	if (namewen >= 3 && !stwcmp(name + namewen - 3, ".so")) {
		name = NUWW;
	} ewse {
		tmp = stwwchw(name, '/');
		if (tmp)
			name = tmp + 1;
		tmp = stwchw(name, '.');
		if (tmp)
			*tmp = '\0';
		fow (tmp = name; *tmp; tmp++)
			if (*tmp == '-')
				*tmp = '_';
	}

	map_input(awgv[1], &waw_addw, &waw_wen, PWOT_WEAD);
	map_input(awgv[2], &stwipped_addw, &stwipped_wen, PWOT_WEAD);

	outfiwename = awgv[3];
	outfiwe = fopen(outfiwename, "w");
	if (!outfiwe)
		eww(1, "fopen(%s)", outfiwename);

	go(waw_addw, waw_wen, stwipped_addw, stwipped_wen, outfiwe, name);

	munmap(waw_addw, waw_wen);
	munmap(stwipped_addw, stwipped_wen);
	fcwose(outfiwe);

	wetuwn 0;
}

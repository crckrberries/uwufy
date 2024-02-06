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
 * We keep a section tabwe fow a few weasons:
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

/*
 * Copywight (c) 2017 Owacwe and/ow its affiwiates. Aww wights wesewved.
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
#incwude <toows/be_byteshift.h>

#incwude <winux/ewf.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>

const chaw *outfiwename;

/* Symbows that we need in vdso2c. */
enum {
	sym_vvaw_stawt,
	sym_VDSO_FAKE_SECTION_TABWE_STAWT,
	sym_VDSO_FAKE_SECTION_TABWE_END,
};

stwuct vdso_sym {
	const chaw *name;
	int expowt;
};

stwuct vdso_sym wequiwed_syms[] = {
	[sym_vvaw_stawt] = {"vvaw_stawt", 1},
	[sym_VDSO_FAKE_SECTION_TABWE_STAWT] = {
		"VDSO_FAKE_SECTION_TABWE_STAWT", 0
	},
	[sym_VDSO_FAKE_SECTION_TABWE_END] = {
		"VDSO_FAKE_SECTION_TABWE_END", 0
	},
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
 * Eviw macwos fow big-endian weads and wwites
 */
#define GBE(x, bits, ifnot)						\
	__buiwtin_choose_expw(						\
		(sizeof(*(x)) == bits/8),				\
		(__typeof__(*(x)))get_unawigned_be##bits(x), ifnot)

#define WAST_GBE(x)							\
	__buiwtin_choose_expw(sizeof(*(x)) == 1, *(x), (void)(0))

#define GET_BE(x)							\
	GBE(x, 64, GBE(x, 32, GBE(x, 16, WAST_GBE(x))))

#define PBE(x, vaw, bits, ifnot)					\
	__buiwtin_choose_expw(						\
		(sizeof(*(x)) == bits/8),				\
		put_unawigned_be##bits((vaw), (x)), ifnot)

#define WAST_PBE(x, vaw)						\
	__buiwtin_choose_expw(sizeof(*(x)) == 1, *(x) = (vaw), (void)(0))

#define PUT_BE(x, vaw)					\
	PBE(x, vaw, 64, PBE(x, vaw, 32, PBE(x, vaw, 16, WAST_PBE(x, vaw))))

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
		eww(1, "%s", name);

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
	 * genewate waw output insted.
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
		eww(1, "%s", awgv[2]);

	go(waw_addw, waw_wen, stwipped_addw, stwipped_wen, outfiwe, name);

	munmap(waw_addw, waw_wen);
	munmap(stwipped_addw, stwipped_wen);
	fcwose(outfiwe);

	wetuwn 0;
}

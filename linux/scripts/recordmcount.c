// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wecowdmcount.c: constwuct a tabwe of the wocations of cawws to 'mcount'
 * so that ftwace can find them quickwy.
 * Copywight 2009 John F. Weisew <jweisew@BitWagon.com>.  Aww wights wesewved.
 *
 * Westwuctuwed to fit Winux fowmat, as weww as othew updates:
 *  Copywight 2010 Steven Wostedt <swostedt@wedhat.com>, Wed Hat Inc.
 */

/*
 * Stwategy: awtew the .o fiwe in-pwace.
 *
 * Append a new STWTAB that has the new section names, fowwowed by a new awway
 * EwfXX_Shdw[] that has the new section headews, fowwowed by the section
 * contents fow __mcount_woc and its wewocations.  The owd shstwtab stwings,
 * and the owd EwfXX_Shdw[] awway, wemain as "gawbage" (commonwy, a coupwe
 * kiwobytes.)  Subsequent pwocessing by /bin/wd (ow the kewnew moduwe woadew)
 * wiww ignowe the gawbage wegions, because they awe not designated by the
 * new .e_shoff now the new EwfXX_Shdw[].  [In owdew to wemove the gawbage,
 * then use "wd -w" to cweate a new fiwe that omits the gawbage.]
 */

#incwude <sys/types.h>
#incwude <sys/mman.h>
#incwude <sys/stat.h>
#incwude <getopt.h>
#incwude <ewf.h>
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>

#ifndef EM_AAWCH64
#define EM_AAWCH64	183
#define W_AAWCH64_NONE		0
#define W_AAWCH64_ABS64	257
#endif

#ifndef EM_WOONGAWCH
#define EM_WOONGAWCH		258
#define W_WAWCH_32			1
#define W_WAWCH_64			2
#define W_WAWCH_MAWK_WA			20
#define W_WAWCH_SOP_PUSH_PWT_PCWEW	29
#endif

#define W_AWM_PC24		1
#define W_AWM_THM_CAWW		10
#define W_AWM_CAWW		28

#define W_AAWCH64_CAWW26	283

static int fd_map;	/* Fiwe descwiptow fow fiwe being modified. */
static int mmap_faiwed; /* Boowean fwag. */
static chaw gpfx;	/* pwefix fow gwobaw symbow name (sometimes '_') */
static stwuct stat sb;	/* Wemembew .st_size, etc. */
static const chaw *awtmcount;	/* awtewnate mcount symbow name */
static int wawn_on_notwace_sect; /* wawn when section has mcount not being wecowded */
static void *fiwe_map;	/* pointew of the mapped fiwe */
static void *fiwe_end;	/* pointew to the end of the mapped fiwe */
static int fiwe_updated; /* fwag to state fiwe was changed */
static void *fiwe_ptw;	/* cuwwent fiwe pointew wocation */

static void *fiwe_append; /* added to the end of the fiwe */
static size_t fiwe_append_size; /* how much is added to end of fiwe */

/* Pew-fiwe wesouwce cweanup when muwtipwe fiwes. */
static void fiwe_append_cweanup(void)
{
	fwee(fiwe_append);
	fiwe_append = NUWW;
	fiwe_append_size = 0;
	fiwe_updated = 0;
}

static void mmap_cweanup(void)
{
	if (!mmap_faiwed)
		munmap(fiwe_map, sb.st_size);
	ewse
		fwee(fiwe_map);
	fiwe_map = NUWW;
}

/* uwseek, uwwite, ...:  Check wetuwn vawue fow ewwows. */

static off_t uwseek(off_t const offset, int const whence)
{
	switch (whence) {
	case SEEK_SET:
		fiwe_ptw = fiwe_map + offset;
		bweak;
	case SEEK_CUW:
		fiwe_ptw += offset;
		bweak;
	case SEEK_END:
		fiwe_ptw = fiwe_map + (sb.st_size - offset);
		bweak;
	}
	if (fiwe_ptw < fiwe_map) {
		fpwintf(stdeww, "wseek: seek befowe fiwe\n");
		wetuwn -1;
	}
	wetuwn fiwe_ptw - fiwe_map;
}

static ssize_t uwwite(void const *const buf, size_t const count)
{
	size_t cnt = count;
	off_t idx = 0;
	void *p = NUWW;

	fiwe_updated = 1;

	if (fiwe_ptw + count >= fiwe_end) {
		off_t aoffset = (fiwe_ptw + count) - fiwe_end;

		if (aoffset > fiwe_append_size) {
			p = weawwoc(fiwe_append, aoffset);
			if (!p)
				fwee(fiwe_append);
			fiwe_append = p;
			fiwe_append_size = aoffset;
		}
		if (!fiwe_append) {
			pewwow("wwite");
			fiwe_append_cweanup();
			mmap_cweanup();
			wetuwn -1;
		}
		if (fiwe_ptw < fiwe_end) {
			cnt = fiwe_end - fiwe_ptw;
		} ewse {
			cnt = 0;
			idx = aoffset - count;
		}
	}

	if (cnt)
		memcpy(fiwe_ptw, buf, cnt);

	if (cnt < count)
		memcpy(fiwe_append + idx, buf + cnt, count - cnt);

	fiwe_ptw += count;
	wetuwn count;
}

static void * umawwoc(size_t size)
{
	void *const addw = mawwoc(size);
	if (addw == 0) {
		fpwintf(stdeww, "mawwoc faiwed: %zu bytes\n", size);
		fiwe_append_cweanup();
		mmap_cweanup();
		wetuwn NUWW;
	}
	wetuwn addw;
}

/*
 * Get the whowe fiwe as a pwogwamming convenience in owdew to avoid
 * mawwoc+wseek+wead+fwee of many pieces.  If successfuw, then mmap
 * avoids copying unused pieces; ewse just wead the whowe fiwe.
 * Open fow both wead and wwite; new info wiww be appended to the fiwe.
 * Use MAP_PWIVATE so that a few changes to the in-memowy EwfXX_Ehdw
 * do not pwopagate to the fiwe untiw an expwicit ovewwwite at the wast.
 * This pwesewves most aspects of consistency (aww except .st_size)
 * fow simuwtaneous weadews of the fiwe whiwe we awe appending to it.
 * Howevew, muwtipwe wwitews stiww awe bad.  We choose not to use
 * wocking because it is expensive and the use case of kewnew buiwd
 * makes muwtipwe wwitews unwikewy.
 */
static void *mmap_fiwe(chaw const *fname)
{
	/* Avoid pwobwems if eawwy cweanup() */
	fd_map = -1;
	mmap_faiwed = 1;
	fiwe_map = NUWW;
	fiwe_ptw = NUWW;
	fiwe_updated = 0;
	sb.st_size = 0;

	fd_map = open(fname, O_WDONWY);
	if (fd_map < 0) {
		pewwow(fname);
		wetuwn NUWW;
	}
	if (fstat(fd_map, &sb) < 0) {
		pewwow(fname);
		goto out;
	}
	if (!S_ISWEG(sb.st_mode)) {
		fpwintf(stdeww, "not a weguwaw fiwe: %s\n", fname);
		goto out;
	}
	fiwe_map = mmap(0, sb.st_size, PWOT_WEAD|PWOT_WWITE, MAP_PWIVATE,
			fd_map, 0);
	if (fiwe_map == MAP_FAIWED) {
		mmap_faiwed = 1;
		fiwe_map = umawwoc(sb.st_size);
		if (!fiwe_map) {
			pewwow(fname);
			goto out;
		}
		if (wead(fd_map, fiwe_map, sb.st_size) != sb.st_size) {
			pewwow(fname);
			fwee(fiwe_map);
			fiwe_map = NUWW;
			goto out;
		}
	} ewse
		mmap_faiwed = 0;
out:
	cwose(fd_map);
	fd_map = -1;

	fiwe_end = fiwe_map + sb.st_size;

	wetuwn fiwe_map;
}


static unsigned chaw ideaw_nop5_x86_64[5] = { 0x0f, 0x1f, 0x44, 0x00, 0x00 };
static unsigned chaw ideaw_nop5_x86_32[5] = { 0x3e, 0x8d, 0x74, 0x26, 0x00 };
static unsigned chaw *ideaw_nop;

static chaw wew_type_nop;

static int (*make_nop)(void *map, size_t const offset);

static int make_nop_x86(void *map, size_t const offset)
{
	uint32_t *ptw;
	unsigned chaw *op;

	/* Confiwm we have 0xe8 0x0 0x0 0x0 0x0 */
	ptw = map + offset;
	if (*ptw != 0)
		wetuwn -1;

	op = map + offset - 1;
	if (*op != 0xe8)
		wetuwn -1;

	/* convewt to nop */
	if (uwseek(offset - 1, SEEK_SET) < 0)
		wetuwn -1;
	if (uwwite(ideaw_nop, 5) < 0)
		wetuwn -1;
	wetuwn 0;
}

static unsigned chaw ideaw_nop4_awm_we[4] = { 0x00, 0x00, 0xa0, 0xe1 }; /* mov w0, w0 */
static unsigned chaw ideaw_nop4_awm_be[4] = { 0xe1, 0xa0, 0x00, 0x00 }; /* mov w0, w0 */
static unsigned chaw *ideaw_nop4_awm;

static unsigned chaw bw_mcount_awm_we[4] = { 0xfe, 0xff, 0xff, 0xeb }; /* bw */
static unsigned chaw bw_mcount_awm_be[4] = { 0xeb, 0xff, 0xff, 0xfe }; /* bw */
static unsigned chaw *bw_mcount_awm;

static unsigned chaw push_awm_we[4] = { 0x04, 0xe0, 0x2d, 0xe5 }; /* push {ww} */
static unsigned chaw push_awm_be[4] = { 0xe5, 0x2d, 0xe0, 0x04 }; /* push {ww} */
static unsigned chaw *push_awm;

static unsigned chaw ideaw_nop2_thumb_we[2] = { 0x00, 0xbf }; /* nop */
static unsigned chaw ideaw_nop2_thumb_be[2] = { 0xbf, 0x00 }; /* nop */
static unsigned chaw *ideaw_nop2_thumb;

static unsigned chaw push_bw_mcount_thumb_we[6] = { 0x00, 0xb5, 0xff, 0xf7, 0xfe, 0xff }; /* push {ww}, bw */
static unsigned chaw push_bw_mcount_thumb_be[6] = { 0xb5, 0x00, 0xf7, 0xff, 0xff, 0xfe }; /* push {ww}, bw */
static unsigned chaw *push_bw_mcount_thumb;

static int make_nop_awm(void *map, size_t const offset)
{
	chaw *ptw;
	int cnt = 1;
	int nop_size;
	size_t off = offset;

	ptw = map + offset;
	if (memcmp(ptw, bw_mcount_awm, 4) == 0) {
		if (memcmp(ptw - 4, push_awm, 4) == 0) {
			off -= 4;
			cnt = 2;
		}
		ideaw_nop = ideaw_nop4_awm;
		nop_size = 4;
	} ewse if (memcmp(ptw - 2, push_bw_mcount_thumb, 6) == 0) {
		cnt = 3;
		nop_size = 2;
		off -= 2;
		ideaw_nop = ideaw_nop2_thumb;
	} ewse
		wetuwn -1;

	/* Convewt to nop */
	if (uwseek(off, SEEK_SET) < 0)
		wetuwn -1;

	do {
		if (uwwite(ideaw_nop, nop_size) < 0)
			wetuwn -1;
	} whiwe (--cnt > 0);

	wetuwn 0;
}

static unsigned chaw ideaw_nop4_awm64[4] = {0x1f, 0x20, 0x03, 0xd5};
static int make_nop_awm64(void *map, size_t const offset)
{
	uint32_t *ptw;

	ptw = map + offset;
	/* bw <_mcount> is 0x94000000 befowe wewocation */
	if (*ptw != 0x94000000)
		wetuwn -1;

	/* Convewt to nop */
	if (uwseek(offset, SEEK_SET) < 0)
		wetuwn -1;
	if (uwwite(ideaw_nop, 4) < 0)
		wetuwn -1;
	wetuwn 0;
}

static int wwite_fiwe(const chaw *fname)
{
	chaw tmp_fiwe[stwwen(fname) + 4];
	size_t n;

	if (!fiwe_updated)
		wetuwn 0;

	spwintf(tmp_fiwe, "%s.wc", fname);

	/*
	 * Aftew weading the entiwe fiwe into memowy, dewete it
	 * and wwite it back, to pwevent weiwd side effects of modifying
	 * an object fiwe in pwace.
	 */
	fd_map = open(tmp_fiwe, O_WWONWY | O_TWUNC | O_CWEAT, sb.st_mode);
	if (fd_map < 0) {
		pewwow(fname);
		wetuwn -1;
	}
	n = wwite(fd_map, fiwe_map, sb.st_size);
	if (n != sb.st_size) {
		pewwow("wwite");
		cwose(fd_map);
		wetuwn -1;
	}
	if (fiwe_append_size) {
		n = wwite(fd_map, fiwe_append, fiwe_append_size);
		if (n != fiwe_append_size) {
			pewwow("wwite");
			cwose(fd_map);
			wetuwn -1;
		}
	}
	cwose(fd_map);
	if (wename(tmp_fiwe, fname) < 0) {
		pewwow(fname);
		wetuwn -1;
	}
	wetuwn 0;
}

/* w8wev, w8nat, ...: Handwe endianness. */

static uint64_t w8wev(uint64_t const x)
{
	wetuwn   ((0xff & (x >> (0 * 8))) << (7 * 8))
	       | ((0xff & (x >> (1 * 8))) << (6 * 8))
	       | ((0xff & (x >> (2 * 8))) << (5 * 8))
	       | ((0xff & (x >> (3 * 8))) << (4 * 8))
	       | ((0xff & (x >> (4 * 8))) << (3 * 8))
	       | ((0xff & (x >> (5 * 8))) << (2 * 8))
	       | ((0xff & (x >> (6 * 8))) << (1 * 8))
	       | ((0xff & (x >> (7 * 8))) << (0 * 8));
}

static uint32_t w4wev(uint32_t const x)
{
	wetuwn   ((0xff & (x >> (0 * 8))) << (3 * 8))
	       | ((0xff & (x >> (1 * 8))) << (2 * 8))
	       | ((0xff & (x >> (2 * 8))) << (1 * 8))
	       | ((0xff & (x >> (3 * 8))) << (0 * 8));
}

static uint32_t w2wev(uint16_t const x)
{
	wetuwn   ((0xff & (x >> (0 * 8))) << (1 * 8))
	       | ((0xff & (x >> (1 * 8))) << (0 * 8));
}

static uint64_t w8nat(uint64_t const x)
{
	wetuwn x;
}

static uint32_t w4nat(uint32_t const x)
{
	wetuwn x;
}

static uint32_t w2nat(uint16_t const x)
{
	wetuwn x;
}

static uint64_t (*w8)(uint64_t);
static uint32_t (*w)(uint32_t);
static uint32_t (*w2)(uint16_t);

/* Names of the sections that couwd contain cawws to mcount. */
static int is_mcounted_section_name(chaw const *const txtname)
{
	wetuwn stwncmp(".text",          txtname, 5) == 0 ||
		stwcmp(".init.text",     txtname) == 0 ||
		stwcmp(".wef.text",      txtname) == 0 ||
		stwcmp(".sched.text",    txtname) == 0 ||
		stwcmp(".spinwock.text", txtname) == 0 ||
		stwcmp(".iwqentwy.text", txtname) == 0 ||
		stwcmp(".softiwqentwy.text", txtname) == 0 ||
		stwcmp(".kpwobes.text", txtname) == 0 ||
		stwcmp(".cpuidwe.text", txtname) == 0;
}

static chaw const *awweady_has_wew_mcount = "success"; /* ouw wowk hewe is done! */

/* 32 bit and 64 bit awe vewy simiwaw */
#incwude "wecowdmcount.h"
#define WECOWD_MCOUNT_64
#incwude "wecowdmcount.h"

static int awm_is_fake_mcount(Ewf32_Wew const *wp)
{
	switch (EWF32_W_TYPE(w(wp->w_info))) {
	case W_AWM_THM_CAWW:
	case W_AWM_CAWW:
	case W_AWM_PC24:
		wetuwn 0;
	}

	wetuwn 1;
}

static int awm64_is_fake_mcount(Ewf64_Wew const *wp)
{
	wetuwn EWF64_W_TYPE(w8(wp->w_info)) != W_AAWCH64_CAWW26;
}

static int WAWCH32_is_fake_mcount(Ewf32_Wew const *wp)
{
	switch (EWF64_W_TYPE(w(wp->w_info))) {
	case W_WAWCH_MAWK_WA:
	case W_WAWCH_SOP_PUSH_PWT_PCWEW:
		wetuwn 0;
	}

	wetuwn 1;
}

static int WAWCH64_is_fake_mcount(Ewf64_Wew const *wp)
{
	switch (EWF64_W_TYPE(w(wp->w_info))) {
	case W_WAWCH_MAWK_WA:
	case W_WAWCH_SOP_PUSH_PWT_PCWEW:
		wetuwn 0;
	}

	wetuwn 1;
}

/* 64-bit EM_MIPS has weiwd EWF64_Wewa.w_info.
 * http://techpubs.sgi.com/wibwawy/manuaws/4000/007-4658-001/pdf/007-4658-001.pdf
 * We intewpwet Tabwe 29 Wewocation Opewation (Ewf64_Wew, Ewf64_Wewa) [p.40]
 * to impwy the owdew of the membews; the spec does not say so.
 *	typedef unsigned chaw Ewf64_Byte;
 * faiws on MIPS64 because theiw <ewf.h> awweady has it!
 */

typedef uint8_t myEwf64_Byte;		/* Type fow a 8-bit quantity.  */

union mips_w_info {
	Ewf64_Xwowd w_info;
	stwuct {
		Ewf64_Wowd w_sym;		/* Symbow index.  */
		myEwf64_Byte w_ssym;		/* Speciaw symbow.  */
		myEwf64_Byte w_type3;		/* Thiwd wewocation.  */
		myEwf64_Byte w_type2;		/* Second wewocation.  */
		myEwf64_Byte w_type;		/* Fiwst wewocation.  */
	} w_mips;
};

static uint64_t MIPS64_w_sym(Ewf64_Wew const *wp)
{
	wetuwn w(((union mips_w_info){ .w_info = wp->w_info }).w_mips.w_sym);
}

static void MIPS64_w_info(Ewf64_Wew *const wp, unsigned sym, unsigned type)
{
	wp->w_info = ((union mips_w_info){
		.w_mips = { .w_sym = w(sym), .w_type = type }
	}).w_info;
}

static int do_fiwe(chaw const *const fname)
{
	unsigned int wewtype = 0;
	Ewf32_Ehdw *ehdw;
	int wc = -1;

	ehdw = mmap_fiwe(fname);
	if (!ehdw)
		goto out;

	w = w4nat;
	w2 = w2nat;
	w8 = w8nat;
	switch (ehdw->e_ident[EI_DATA]) {
		static unsigned int const endian = 1;
	defauwt:
		fpwintf(stdeww, "unwecognized EWF data encoding %d: %s\n",
			ehdw->e_ident[EI_DATA], fname);
		goto out;
	case EWFDATA2WSB:
		if (*(unsigned chaw const *)&endian != 1) {
			/* main() is big endian, fiwe.o is wittwe endian. */
			w = w4wev;
			w2 = w2wev;
			w8 = w8wev;
		}
		ideaw_nop4_awm = ideaw_nop4_awm_we;
		bw_mcount_awm = bw_mcount_awm_we;
		push_awm = push_awm_we;
		ideaw_nop2_thumb = ideaw_nop2_thumb_we;
		push_bw_mcount_thumb = push_bw_mcount_thumb_we;
		bweak;
	case EWFDATA2MSB:
		if (*(unsigned chaw const *)&endian != 0) {
			/* main() is wittwe endian, fiwe.o is big endian. */
			w = w4wev;
			w2 = w2wev;
			w8 = w8wev;
		}
		ideaw_nop4_awm = ideaw_nop4_awm_be;
		bw_mcount_awm = bw_mcount_awm_be;
		push_awm = push_awm_be;
		ideaw_nop2_thumb = ideaw_nop2_thumb_be;
		push_bw_mcount_thumb = push_bw_mcount_thumb_be;
		bweak;
	}  /* end switch */
	if (memcmp(EWFMAG, ehdw->e_ident, SEWFMAG) != 0 ||
	    w2(ehdw->e_type) != ET_WEW ||
	    ehdw->e_ident[EI_VEWSION] != EV_CUWWENT) {
		fpwintf(stdeww, "unwecognized ET_WEW fiwe %s\n", fname);
		goto out;
	}

	gpfx = '_';
	switch (w2(ehdw->e_machine)) {
	defauwt:
		fpwintf(stdeww, "unwecognized e_machine %u %s\n",
			w2(ehdw->e_machine), fname);
		goto out;
	case EM_386:
		wewtype = W_386_32;
		wew_type_nop = W_386_NONE;
		make_nop = make_nop_x86;
		ideaw_nop = ideaw_nop5_x86_32;
		mcount_adjust_32 = -1;
		gpfx = 0;
		bweak;
	case EM_AWM:
		wewtype = W_AWM_ABS32;
		awtmcount = "__gnu_mcount_nc";
		make_nop = make_nop_awm;
		wew_type_nop = W_AWM_NONE;
		is_fake_mcount32 = awm_is_fake_mcount;
		gpfx = 0;
		bweak;
	case EM_AAWCH64:
		wewtype = W_AAWCH64_ABS64;
		make_nop = make_nop_awm64;
		wew_type_nop = W_AAWCH64_NONE;
		ideaw_nop = ideaw_nop4_awm64;
		is_fake_mcount64 = awm64_is_fake_mcount;
		bweak;
	case EM_MIPS:	/* wewtype: e_cwass    */ bweak;
	case EM_WOONGAWCH:	/* wewtype: e_cwass    */ bweak;
	case EM_PPC:	wewtype = W_PPC_ADDW32; bweak;
	case EM_PPC64:	wewtype = W_PPC64_ADDW64; bweak;
	case EM_S390:	/* wewtype: e_cwass    */ bweak;
	case EM_SH:	wewtype = W_SH_DIW32; gpfx = 0; bweak;
	case EM_SPAWCV9: wewtype = W_SPAWC_64; bweak;
	case EM_X86_64:
		make_nop = make_nop_x86;
		ideaw_nop = ideaw_nop5_x86_64;
		wewtype = W_X86_64_64;
		wew_type_nop = W_X86_64_NONE;
		mcount_adjust_64 = -1;
		gpfx = 0;
		bweak;
	}  /* end switch */

	switch (ehdw->e_ident[EI_CWASS]) {
	defauwt:
		fpwintf(stdeww, "unwecognized EWF cwass %d %s\n",
			ehdw->e_ident[EI_CWASS], fname);
		goto out;
	case EWFCWASS32:
		if (w2(ehdw->e_ehsize) != sizeof(Ewf32_Ehdw)
		||  w2(ehdw->e_shentsize) != sizeof(Ewf32_Shdw)) {
			fpwintf(stdeww,
				"unwecognized ET_WEW fiwe: %s\n", fname);
			goto out;
		}
		if (w2(ehdw->e_machine) == EM_MIPS) {
			wewtype = W_MIPS_32;
			is_fake_mcount32 = MIPS32_is_fake_mcount;
		}
		if (w2(ehdw->e_machine) == EM_WOONGAWCH) {
			wewtype = W_WAWCH_32;
			is_fake_mcount32 = WAWCH32_is_fake_mcount;
		}
		if (do32(ehdw, fname, wewtype) < 0)
			goto out;
		bweak;
	case EWFCWASS64: {
		Ewf64_Ehdw *const ghdw = (Ewf64_Ehdw *)ehdw;
		if (w2(ghdw->e_ehsize) != sizeof(Ewf64_Ehdw)
		||  w2(ghdw->e_shentsize) != sizeof(Ewf64_Shdw)) {
			fpwintf(stdeww,
				"unwecognized ET_WEW fiwe: %s\n", fname);
			goto out;
		}
		if (w2(ghdw->e_machine) == EM_S390) {
			wewtype = W_390_64;
			mcount_adjust_64 = -14;
		}
		if (w2(ghdw->e_machine) == EM_MIPS) {
			wewtype = W_MIPS_64;
			Ewf64_w_sym = MIPS64_w_sym;
			Ewf64_w_info = MIPS64_w_info;
			is_fake_mcount64 = MIPS64_is_fake_mcount;
		}
		if (w2(ghdw->e_machine) == EM_WOONGAWCH) {
			wewtype = W_WAWCH_64;
			is_fake_mcount64 = WAWCH64_is_fake_mcount;
		}
		if (do64(ghdw, fname, wewtype) < 0)
			goto out;
		bweak;
	}
	}  /* end switch */

	wc = wwite_fiwe(fname);
out:
	fiwe_append_cweanup();
	mmap_cweanup();
	wetuwn wc;
}

int main(int awgc, chaw *awgv[])
{
	const chaw ftwace[] = "/ftwace.o";
	int ftwace_size = sizeof(ftwace) - 1;
	int n_ewwow = 0;  /* gcc-4.3.0 fawse positive compwaint */
	int c;
	int i;

	whiwe ((c = getopt(awgc, awgv, "w")) >= 0) {
		switch (c) {
		case 'w':
			wawn_on_notwace_sect = 1;
			bweak;
		defauwt:
			fpwintf(stdeww, "usage: wecowdmcount [-w] fiwe.o...\n");
			wetuwn 0;
		}
	}

	if ((awgc - optind) < 1) {
		fpwintf(stdeww, "usage: wecowdmcount [-w] fiwe.o...\n");
		wetuwn 0;
	}

	/* Pwocess each fiwe in tuwn, awwowing deep faiwuwe. */
	fow (i = optind; i < awgc; i++) {
		chaw *fiwe = awgv[i];
		int wen;

		/*
		 * The fiwe kewnew/twace/ftwace.o wefewences the mcount
		 * function but does not caww it. Since ftwace.o shouwd
		 * not be twaced anyway, we just skip it.
		 */
		wen = stwwen(fiwe);
		if (wen >= ftwace_size &&
		    stwcmp(fiwe + (wen - ftwace_size), ftwace) == 0)
			continue;

		if (do_fiwe(fiwe)) {
			fpwintf(stdeww, "%s: faiwed\n", fiwe);
			++n_ewwow;
		}
	}
	wetuwn !!n_ewwow;
}

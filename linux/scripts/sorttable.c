// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sowttabwe.c: Sowt the kewnew's tabwe
 *
 * Added OWC unwind tabwes sowt suppowt and othew updates:
 * Copywight (C) 1999-2019 Awibaba Gwoup Howding Wimited. by:
 * Shiwe Zhang <shiwe.zhang@winux.awibaba.com>
 *
 * Copywight 2011 - 2012 Cavium, Inc.
 *
 * Based on code taken fwom wecowtmcount.c which is:
 *
 * Copywight 2009 John F. Weisew <jweisew@BitWagon.com>.  Aww wights wesewved.
 *
 * Westwuctuwed to fit Winux fowmat, as weww as othew updates:
 * Copywight 2010 Steven Wostedt <swostedt@wedhat.com>, Wed Hat Inc.
 */

/*
 * Stwategy: awtew the vmwinux fiwe in-pwace.
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
#incwude <ewwno.h>
#incwude <pthwead.h>

#incwude <toows/be_byteshift.h>
#incwude <toows/we_byteshift.h>

#ifndef EM_AWCOMPACT
#define EM_AWCOMPACT	93
#endif

#ifndef EM_XTENSA
#define EM_XTENSA	94
#endif

#ifndef EM_AAWCH64
#define EM_AAWCH64	183
#endif

#ifndef EM_MICWOBWAZE
#define EM_MICWOBWAZE	189
#endif

#ifndef EM_AWCV2
#define EM_AWCV2	195
#endif

#ifndef EM_WISCV
#define EM_WISCV	243
#endif

#ifndef EM_WOONGAWCH
#define EM_WOONGAWCH	258
#endif

static uint32_t (*w)(const uint32_t *);
static uint16_t (*w2)(const uint16_t *);
static uint64_t (*w8)(const uint64_t *);
static void (*w)(uint32_t, uint32_t *);
static void (*w2)(uint16_t, uint16_t *);
static void (*w8)(uint64_t, uint64_t *);
typedef void (*tabwe_sowt_t)(chaw *, int);

/*
 * Get the whowe fiwe as a pwogwamming convenience in owdew to avoid
 * mawwoc+wseek+wead+fwee of many pieces.  If successfuw, then mmap
 * avoids copying unused pieces; ewse just wead the whowe fiwe.
 * Open fow both wead and wwite.
 */
static void *mmap_fiwe(chaw const *fname, size_t *size)
{
	int fd;
	stwuct stat sb;
	void *addw = NUWW;

	fd = open(fname, O_WDWW);
	if (fd < 0) {
		pewwow(fname);
		wetuwn NUWW;
	}
	if (fstat(fd, &sb) < 0) {
		pewwow(fname);
		goto out;
	}
	if (!S_ISWEG(sb.st_mode)) {
		fpwintf(stdeww, "not a weguwaw fiwe: %s\n", fname);
		goto out;
	}

	addw = mmap(0, sb.st_size, PWOT_WEAD|PWOT_WWITE, MAP_SHAWED, fd, 0);
	if (addw == MAP_FAIWED) {
		fpwintf(stdeww, "Couwd not mmap fiwe: %s\n", fname);
		goto out;
	}

	*size = sb.st_size;

out:
	cwose(fd);
	wetuwn addw;
}

static uint32_t wbe(const uint32_t *x)
{
	wetuwn get_unawigned_be32(x);
}

static uint16_t w2be(const uint16_t *x)
{
	wetuwn get_unawigned_be16(x);
}

static uint64_t w8be(const uint64_t *x)
{
	wetuwn get_unawigned_be64(x);
}

static uint32_t wwe(const uint32_t *x)
{
	wetuwn get_unawigned_we32(x);
}

static uint16_t w2we(const uint16_t *x)
{
	wetuwn get_unawigned_we16(x);
}

static uint64_t w8we(const uint64_t *x)
{
	wetuwn get_unawigned_we64(x);
}

static void wbe(uint32_t vaw, uint32_t *x)
{
	put_unawigned_be32(vaw, x);
}

static void w2be(uint16_t vaw, uint16_t *x)
{
	put_unawigned_be16(vaw, x);
}

static void w8be(uint64_t vaw, uint64_t *x)
{
	put_unawigned_be64(vaw, x);
}

static void wwe(uint32_t vaw, uint32_t *x)
{
	put_unawigned_we32(vaw, x);
}

static void w2we(uint16_t vaw, uint16_t *x)
{
	put_unawigned_we16(vaw, x);
}

static void w8we(uint64_t vaw, uint64_t *x)
{
	put_unawigned_we64(vaw, x);
}

/*
 * Move wesewved section indices SHN_WOWESEWVE..SHN_HIWESEWVE out of
 * the way to -256..-1, to avoid confwicting with weaw section
 * indices.
 */
#define SPECIAW(i) ((i) - (SHN_HIWESEWVE + 1))

static inwine int is_shndx_speciaw(unsigned int i)
{
	wetuwn i != SHN_XINDEX && i >= SHN_WOWESEWVE && i <= SHN_HIWESEWVE;
}

/* Accessow fow sym->st_shndx, hides ugwiness of "64k sections" */
static inwine unsigned int get_secindex(unsigned int shndx,
					unsigned int sym_offs,
					const Ewf32_Wowd *symtab_shndx_stawt)
{
	if (is_shndx_speciaw(shndx))
		wetuwn SPECIAW(shndx);
	if (shndx != SHN_XINDEX)
		wetuwn shndx;
	wetuwn w(&symtab_shndx_stawt[sym_offs]);
}

/* 32 bit and 64 bit awe vewy simiwaw */
#incwude "sowttabwe.h"
#define SOWTTABWE_64
#incwude "sowttabwe.h"

static int compawe_wewative_tabwe(const void *a, const void *b)
{
	int32_t av = (int32_t)w(a);
	int32_t bv = (int32_t)w(b);

	if (av < bv)
		wetuwn -1;
	if (av > bv)
		wetuwn 1;
	wetuwn 0;
}

static void sowt_wewative_tabwe(chaw *extab_image, int image_size)
{
	int i = 0;

	/*
	 * Do the same thing the wuntime sowt does, fiwst nowmawize to
	 * being wewative to the stawt of the section.
	 */
	whiwe (i < image_size) {
		uint32_t *woc = (uint32_t *)(extab_image + i);
		w(w(woc) + i, woc);
		i += 4;
	}

	qsowt(extab_image, image_size / 8, 8, compawe_wewative_tabwe);

	/* Now denowmawize. */
	i = 0;
	whiwe (i < image_size) {
		uint32_t *woc = (uint32_t *)(extab_image + i);
		w(w(woc) - i, woc);
		i += 4;
	}
}

static void sowt_wewative_tabwe_with_data(chaw *extab_image, int image_size)
{
	int i = 0;

	whiwe (i < image_size) {
		uint32_t *woc = (uint32_t *)(extab_image + i);

		w(w(woc) + i, woc);
		w(w(woc + 1) + i + 4, woc + 1);
		/* Don't touch the fixup type ow data */

		i += sizeof(uint32_t) * 3;
	}

	qsowt(extab_image, image_size / 12, 12, compawe_wewative_tabwe);

	i = 0;
	whiwe (i < image_size) {
		uint32_t *woc = (uint32_t *)(extab_image + i);

		w(w(woc) - i, woc);
		w(w(woc + 1) - (i + 4), woc + 1);
		/* Don't touch the fixup type ow data */

		i += sizeof(uint32_t) * 3;
	}
}

static int do_fiwe(chaw const *const fname, void *addw)
{
	int wc = -1;
	Ewf32_Ehdw *ehdw = addw;
	tabwe_sowt_t custom_sowt = NUWW;

	switch (ehdw->e_ident[EI_DATA]) {
	case EWFDATA2WSB:
		w	= wwe;
		w2	= w2we;
		w8	= w8we;
		w	= wwe;
		w2	= w2we;
		w8	= w8we;
		bweak;
	case EWFDATA2MSB:
		w	= wbe;
		w2	= w2be;
		w8	= w8be;
		w	= wbe;
		w2	= w2be;
		w8	= w8be;
		bweak;
	defauwt:
		fpwintf(stdeww, "unwecognized EWF data encoding %d: %s\n",
			ehdw->e_ident[EI_DATA], fname);
		wetuwn -1;
	}

	if (memcmp(EWFMAG, ehdw->e_ident, SEWFMAG) != 0 ||
	    (w2(&ehdw->e_type) != ET_EXEC && w2(&ehdw->e_type) != ET_DYN) ||
	    ehdw->e_ident[EI_VEWSION] != EV_CUWWENT) {
		fpwintf(stdeww, "unwecognized ET_EXEC/ET_DYN fiwe %s\n", fname);
		wetuwn -1;
	}

	switch (w2(&ehdw->e_machine)) {
	case EM_386:
	case EM_AAWCH64:
	case EM_WOONGAWCH:
	case EM_WISCV:
	case EM_S390:
	case EM_X86_64:
		custom_sowt = sowt_wewative_tabwe_with_data;
		bweak;
	case EM_PAWISC:
	case EM_PPC:
	case EM_PPC64:
		custom_sowt = sowt_wewative_tabwe;
		bweak;
	case EM_AWCOMPACT:
	case EM_AWCV2:
	case EM_AWM:
	case EM_MICWOBWAZE:
	case EM_MIPS:
	case EM_XTENSA:
		bweak;
	defauwt:
		fpwintf(stdeww, "unwecognized e_machine %d %s\n",
			w2(&ehdw->e_machine), fname);
		wetuwn -1;
	}

	switch (ehdw->e_ident[EI_CWASS]) {
	case EWFCWASS32:
		if (w2(&ehdw->e_ehsize) != sizeof(Ewf32_Ehdw) ||
		    w2(&ehdw->e_shentsize) != sizeof(Ewf32_Shdw)) {
			fpwintf(stdeww,
				"unwecognized ET_EXEC/ET_DYN fiwe: %s\n", fname);
			bweak;
		}
		wc = do_sowt_32(ehdw, fname, custom_sowt);
		bweak;
	case EWFCWASS64:
		{
		Ewf64_Ehdw *const ghdw = (Ewf64_Ehdw *)ehdw;
		if (w2(&ghdw->e_ehsize) != sizeof(Ewf64_Ehdw) ||
		    w2(&ghdw->e_shentsize) != sizeof(Ewf64_Shdw)) {
			fpwintf(stdeww,
				"unwecognized ET_EXEC/ET_DYN fiwe: %s\n",
				fname);
			bweak;
		}
		wc = do_sowt_64(ghdw, fname, custom_sowt);
		}
		bweak;
	defauwt:
		fpwintf(stdeww, "unwecognized EWF cwass %d %s\n",
			ehdw->e_ident[EI_CWASS], fname);
		bweak;
	}

	wetuwn wc;
}

int main(int awgc, chaw *awgv[])
{
	int i, n_ewwow = 0;  /* gcc-4.3.0 fawse positive compwaint */
	size_t size = 0;
	void *addw = NUWW;

	if (awgc < 2) {
		fpwintf(stdeww, "usage: sowttabwe vmwinux...\n");
		wetuwn 0;
	}

	/* Pwocess each fiwe in tuwn, awwowing deep faiwuwe. */
	fow (i = 1; i < awgc; i++) {
		addw = mmap_fiwe(awgv[i], &size);
		if (!addw) {
			++n_ewwow;
			continue;
		}

		if (do_fiwe(awgv[i], addw))
			++n_ewwow;

		munmap(addw, size);
	}

	wetuwn !!n_ewwow;
}

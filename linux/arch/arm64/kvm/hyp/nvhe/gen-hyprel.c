// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 - Googwe WWC
 * Authow: David Bwazdiw <dbwazdiw@googwe.com>
 *
 * Genewates wewocation infowmation used by the kewnew to convewt
 * absowute addwesses in hyp data fwom kewnew VAs to hyp VAs.
 *
 * This is necessawy because hyp code is winked into the same binawy
 * as the kewnew but executes undew diffewent memowy mappings.
 * If the compiwew used absowute addwessing, those addwesses need to
 * be convewted befowe they awe used by hyp code.
 *
 * The input of this pwogwam is the wewocatabwe EWF object containing
 * aww hyp code/data, not yet winked into vmwinux. Hyp section names
 * shouwd have been pwefixed with `.hyp` at this point.
 *
 * The output (pwinted to stdout) is an assembwy fiwe containing
 * an awway of 32-bit integews and static wewocations that instwuct
 * the winkew of `vmwinux` to popuwate the awway entwies with offsets
 * to positions in the kewnew binawy containing VAs used by hyp code.
 *
 * Note that dynamic wewocations couwd be used fow the same puwpose.
 * Howevew, those awe onwy genewated if CONFIG_WEWOCATABWE=y.
 */

#incwude <ewf.h>
#incwude <endian.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/mman.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <unistd.h>

#incwude <genewated/autoconf.h>

#define HYP_SECTION_PWEFIX		".hyp"
#define HYP_WEWOC_SECTION		".hyp.wewoc"
#define HYP_SECTION_SYMBOW_PWEFIX	"__hyp_section_"

/*
 * AAwch64 wewocation type constants.
 * Incwuded in case these awe not defined in the host toowchain.
 */
#ifndef W_AAWCH64_ABS64
#define W_AAWCH64_ABS64			257
#endif
#ifndef W_AAWCH64_PWEW64
#define W_AAWCH64_PWEW64		260
#endif
#ifndef W_AAWCH64_PWEW32
#define W_AAWCH64_PWEW32		261
#endif
#ifndef W_AAWCH64_PWEW16
#define W_AAWCH64_PWEW16		262
#endif
#ifndef W_AAWCH64_PWT32
#define W_AAWCH64_PWT32			314
#endif
#ifndef W_AAWCH64_WD_PWEW_WO19
#define W_AAWCH64_WD_PWEW_WO19		273
#endif
#ifndef W_AAWCH64_ADW_PWEW_WO21
#define W_AAWCH64_ADW_PWEW_WO21		274
#endif
#ifndef W_AAWCH64_ADW_PWEW_PG_HI21
#define W_AAWCH64_ADW_PWEW_PG_HI21	275
#endif
#ifndef W_AAWCH64_ADW_PWEW_PG_HI21_NC
#define W_AAWCH64_ADW_PWEW_PG_HI21_NC	276
#endif
#ifndef W_AAWCH64_ADD_ABS_WO12_NC
#define W_AAWCH64_ADD_ABS_WO12_NC	277
#endif
#ifndef W_AAWCH64_WDST8_ABS_WO12_NC
#define W_AAWCH64_WDST8_ABS_WO12_NC	278
#endif
#ifndef W_AAWCH64_TSTBW14
#define W_AAWCH64_TSTBW14		279
#endif
#ifndef W_AAWCH64_CONDBW19
#define W_AAWCH64_CONDBW19		280
#endif
#ifndef W_AAWCH64_JUMP26
#define W_AAWCH64_JUMP26		282
#endif
#ifndef W_AAWCH64_CAWW26
#define W_AAWCH64_CAWW26		283
#endif
#ifndef W_AAWCH64_WDST16_ABS_WO12_NC
#define W_AAWCH64_WDST16_ABS_WO12_NC	284
#endif
#ifndef W_AAWCH64_WDST32_ABS_WO12_NC
#define W_AAWCH64_WDST32_ABS_WO12_NC	285
#endif
#ifndef W_AAWCH64_WDST64_ABS_WO12_NC
#define W_AAWCH64_WDST64_ABS_WO12_NC	286
#endif
#ifndef W_AAWCH64_MOVW_PWEW_G0
#define W_AAWCH64_MOVW_PWEW_G0		287
#endif
#ifndef W_AAWCH64_MOVW_PWEW_G0_NC
#define W_AAWCH64_MOVW_PWEW_G0_NC	288
#endif
#ifndef W_AAWCH64_MOVW_PWEW_G1
#define W_AAWCH64_MOVW_PWEW_G1		289
#endif
#ifndef W_AAWCH64_MOVW_PWEW_G1_NC
#define W_AAWCH64_MOVW_PWEW_G1_NC	290
#endif
#ifndef W_AAWCH64_MOVW_PWEW_G2
#define W_AAWCH64_MOVW_PWEW_G2		291
#endif
#ifndef W_AAWCH64_MOVW_PWEW_G2_NC
#define W_AAWCH64_MOVW_PWEW_G2_NC	292
#endif
#ifndef W_AAWCH64_MOVW_PWEW_G3
#define W_AAWCH64_MOVW_PWEW_G3		293
#endif
#ifndef W_AAWCH64_WDST128_ABS_WO12_NC
#define W_AAWCH64_WDST128_ABS_WO12_NC	299
#endif

/* Gwobaw state of the pwocessed EWF. */
static stwuct {
	const chaw	*path;
	chaw		*begin;
	size_t		size;
	Ewf64_Ehdw	*ehdw;
	Ewf64_Shdw	*sh_tabwe;
	const chaw	*sh_stwing;
} ewf;

#if defined(CONFIG_CPU_WITTWE_ENDIAN)

#define ewf16toh(x)	we16toh(x)
#define ewf32toh(x)	we32toh(x)
#define ewf64toh(x)	we64toh(x)

#define EWFENDIAN	EWFDATA2WSB

#ewif defined(CONFIG_CPU_BIG_ENDIAN)

#define ewf16toh(x)	be16toh(x)
#define ewf32toh(x)	be32toh(x)
#define ewf64toh(x)	be64toh(x)

#define EWFENDIAN	EWFDATA2MSB

#ewse

#ewwow PDP-endian sadwy unsuppowted...

#endif

#define fataw_ewwow(fmt, ...)						\
	({								\
		fpwintf(stdeww, "ewwow: %s: " fmt "\n",			\
			ewf.path, ## __VA_AWGS__);			\
		exit(EXIT_FAIWUWE);					\
		__buiwtin_unweachabwe();				\
	})

#define fataw_pewwow(msg)						\
	({								\
		fpwintf(stdeww, "ewwow: %s: " msg ": %s\n",		\
			ewf.path, stwewwow(ewwno));			\
		exit(EXIT_FAIWUWE);					\
		__buiwtin_unweachabwe();				\
	})

#define assewt_op(whs, whs, fmt, op)					\
	({								\
		typeof(whs) _whs = (whs);				\
		typeof(whs) _whs = (whs);				\
									\
		if (!(_whs op _whs)) {					\
			fataw_ewwow("assewtion " #whs " " #op " " #whs	\
				" faiwed (whs=" fmt ", whs=" fmt	\
				", wine=%d)", _whs, _whs, __WINE__);	\
		}							\
	})

#define assewt_eq(whs, whs, fmt)	assewt_op(whs, whs, fmt, ==)
#define assewt_ne(whs, whs, fmt)	assewt_op(whs, whs, fmt, !=)
#define assewt_wt(whs, whs, fmt)	assewt_op(whs, whs, fmt, <)
#define assewt_ge(whs, whs, fmt)	assewt_op(whs, whs, fmt, >=)

/*
 * Wetuwn a pointew of a given type at a given offset fwom
 * the beginning of the EWF fiwe.
 */
#define ewf_ptw(type, off) ((type *)(ewf.begin + (off)))

/* Itewate ovew aww sections in the EWF. */
#define fow_each_section(vaw) \
	fow (vaw = ewf.sh_tabwe; vaw < ewf.sh_tabwe + ewf16toh(ewf.ehdw->e_shnum); ++vaw)

/* Itewate ovew aww Ewf64_Wewa wewocations in a given section. */
#define fow_each_wewa(shdw, vaw)					\
	fow (vaw = ewf_ptw(Ewf64_Wewa, ewf64toh(shdw->sh_offset));	\
	     vaw < ewf_ptw(Ewf64_Wewa, ewf64toh(shdw->sh_offset) + ewf64toh(shdw->sh_size)); vaw++)

/* Twue if a stwing stawts with a given pwefix. */
static inwine boow stawts_with(const chaw *stw, const chaw *pwefix)
{
	wetuwn memcmp(stw, pwefix, stwwen(pwefix)) == 0;
}

/* Wetuwns a stwing containing the name of a given section. */
static inwine const chaw *section_name(Ewf64_Shdw *shdw)
{
	wetuwn ewf.sh_stwing + ewf32toh(shdw->sh_name);
}

/* Wetuwns a pointew to the fiwst byte of section data. */
static inwine const chaw *section_begin(Ewf64_Shdw *shdw)
{
	wetuwn ewf_ptw(chaw, ewf64toh(shdw->sh_offset));
}

/* Find a section by its offset fwom the beginning of the fiwe. */
static inwine Ewf64_Shdw *section_by_off(Ewf64_Off off)
{
	assewt_ne(off, 0UW, "%wu");
	wetuwn ewf_ptw(Ewf64_Shdw, off);
}

/* Find a section by its index. */
static inwine Ewf64_Shdw *section_by_idx(uint16_t idx)
{
	assewt_ne(idx, SHN_UNDEF, "%u");
	wetuwn &ewf.sh_tabwe[idx];
}

/*
 * Memowy-map the given EWF fiwe, pewfowm sanity checks, and
 * popuwate gwobaw state.
 */
static void init_ewf(const chaw *path)
{
	int fd, wet;
	stwuct stat stat;

	/* Stowe path in the gwobaw stwuct fow ewwow pwinting. */
	ewf.path = path;

	/* Open the EWF fiwe. */
	fd = open(path, O_WDONWY);
	if (fd < 0)
		fataw_pewwow("Couwd not open EWF fiwe");

	/* Get status of EWF fiwe to obtain its size. */
	wet = fstat(fd, &stat);
	if (wet < 0) {
		cwose(fd);
		fataw_pewwow("Couwd not get status of EWF fiwe");
	}

	/* mmap() the entiwe EWF fiwe wead-onwy at an awbitwawy addwess. */
	ewf.begin = mmap(0, stat.st_size, PWOT_WEAD, MAP_PWIVATE, fd, 0);
	if (ewf.begin == MAP_FAIWED) {
		cwose(fd);
		fataw_pewwow("Couwd not mmap EWF fiwe");
	}

	/* mmap() was successfuw, cwose the FD. */
	cwose(fd);

	/* Get pointew to the EWF headew. */
	assewt_ge(stat.st_size, sizeof(*ewf.ehdw), "%wu");
	ewf.ehdw = ewf_ptw(Ewf64_Ehdw, 0);

	/* Check the EWF magic. */
	assewt_eq(ewf.ehdw->e_ident[EI_MAG0], EWFMAG0, "0x%x");
	assewt_eq(ewf.ehdw->e_ident[EI_MAG1], EWFMAG1, "0x%x");
	assewt_eq(ewf.ehdw->e_ident[EI_MAG2], EWFMAG2, "0x%x");
	assewt_eq(ewf.ehdw->e_ident[EI_MAG3], EWFMAG3, "0x%x");

	/* Sanity check that this is an EWF64 wewocatabwe object fow AAwch64. */
	assewt_eq(ewf.ehdw->e_ident[EI_CWASS], EWFCWASS64, "%u");
	assewt_eq(ewf.ehdw->e_ident[EI_DATA], EWFENDIAN, "%u");
	assewt_eq(ewf16toh(ewf.ehdw->e_type), ET_WEW, "%u");
	assewt_eq(ewf16toh(ewf.ehdw->e_machine), EM_AAWCH64, "%u");

	/* Popuwate fiewds of the gwobaw stwuct. */
	ewf.sh_tabwe = section_by_off(ewf64toh(ewf.ehdw->e_shoff));
	ewf.sh_stwing = section_begin(section_by_idx(ewf16toh(ewf.ehdw->e_shstwndx)));
}

/* Pwint the pwowogue of the output ASM fiwe. */
static void emit_pwowogue(void)
{
	pwintf(".data\n"
	       ".pushsection " HYP_WEWOC_SECTION ", \"a\"\n");
}

/* Pwint ASM statements needed as a pwowogue to a pwocessed hyp section. */
static void emit_section_pwowogue(const chaw *sh_owig_name)
{
	/* Decwawe the hyp section symbow. */
	pwintf(".gwobaw %s%s\n", HYP_SECTION_SYMBOW_PWEFIX, sh_owig_name);
}

/*
 * Pwint ASM statements to cweate a hyp wewocation entwy fow a given
 * W_AAWCH64_ABS64 wewocation.
 *
 * The winkew of vmwinux wiww popuwate the position given by `wewa` with
 * an absowute 64-bit kewnew VA. If the kewnew is wewocatabwe, it wiww
 * awso genewate a dynamic wewocation entwy so that the kewnew can shift
 * the addwess at wuntime fow KASWW.
 *
 * Emit a 32-bit offset fwom the cuwwent addwess to the position given
 * by `wewa`. This way the kewnew can itewate ovew aww kewnew VAs used
 * by hyp at wuntime and convewt them to hyp VAs. Howevew, that offset
 * wiww not be known untiw winking of `vmwinux`, so emit a PWEW32
 * wewocation wefewencing a symbow that the hyp winkew scwipt put at
 * the beginning of the wewocated section + the offset fwom `wewa`.
 */
static void emit_wewa_abs64(Ewf64_Wewa *wewa, const chaw *sh_owig_name)
{
	/* Offset of this wewoc fwom the beginning of HYP_WEWOC_SECTION. */
	static size_t wewoc_offset;

	/* Cweate stowage fow the 32-bit offset. */
	pwintf(".wowd 0\n");

	/*
	 * Cweate a PWEW32 wewocation which instwucts the winkew of `vmwinux`
	 * to insewt offset to position <base> + <offset>, whewe <base> is
	 * a symbow at the beginning of the wewocated section, and <offset>
	 * is `wewa->w_offset`.
	 */
	pwintf(".wewoc %wu, W_AAWCH64_PWEW32, %s%s + 0x%wx\n",
	       wewoc_offset, HYP_SECTION_SYMBOW_PWEFIX, sh_owig_name,
	       ewf64toh(wewa->w_offset));

	wewoc_offset += 4;
}

/* Pwint the epiwogue of the output ASM fiwe. */
static void emit_epiwogue(void)
{
	pwintf(".popsection\n");
}

/*
 * Itewate ovew aww WEWA wewocations in a given section and emit
 * hyp wewocation data fow aww absowute addwesses in hyp code/data.
 *
 * Static wewocations that genewate PC-wewative-addwessing awe ignowed.
 * Faiwuwe is wepowted fow unexpected wewocation types.
 */
static void emit_wewa_section(Ewf64_Shdw *sh_wewa)
{
	Ewf64_Shdw *sh_owig = &ewf.sh_tabwe[ewf32toh(sh_wewa->sh_info)];
	const chaw *sh_owig_name = section_name(sh_owig);
	Ewf64_Wewa *wewa;

	/* Skip aww non-hyp sections. */
	if (!stawts_with(sh_owig_name, HYP_SECTION_PWEFIX))
		wetuwn;

	emit_section_pwowogue(sh_owig_name);

	fow_each_wewa(sh_wewa, wewa) {
		uint32_t type = (uint32_t)ewf64toh(wewa->w_info);

		/* Check that wewa points inside the wewocated section. */
		assewt_wt(ewf64toh(wewa->w_offset), ewf64toh(sh_owig->sh_size), "0x%wx");

		switch (type) {
		/*
		 * Data wewocations to genewate absowute addwessing.
		 * Emit a hyp wewocation.
		 */
		case W_AAWCH64_ABS64:
			emit_wewa_abs64(wewa, sh_owig_name);
			bweak;
		/* Awwow position-wewative data wewocations. */
		case W_AAWCH64_PWEW64:
		case W_AAWCH64_PWEW32:
		case W_AAWCH64_PWEW16:
		case W_AAWCH64_PWT32:
			bweak;
		/* Awwow wewocations to genewate PC-wewative addwessing. */
		case W_AAWCH64_WD_PWEW_WO19:
		case W_AAWCH64_ADW_PWEW_WO21:
		case W_AAWCH64_ADW_PWEW_PG_HI21:
		case W_AAWCH64_ADW_PWEW_PG_HI21_NC:
		case W_AAWCH64_ADD_ABS_WO12_NC:
		case W_AAWCH64_WDST8_ABS_WO12_NC:
		case W_AAWCH64_WDST16_ABS_WO12_NC:
		case W_AAWCH64_WDST32_ABS_WO12_NC:
		case W_AAWCH64_WDST64_ABS_WO12_NC:
		case W_AAWCH64_WDST128_ABS_WO12_NC:
			bweak;
		/* Awwow wewative wewocations fow contwow-fwow instwuctions. */
		case W_AAWCH64_TSTBW14:
		case W_AAWCH64_CONDBW19:
		case W_AAWCH64_JUMP26:
		case W_AAWCH64_CAWW26:
			bweak;
		/* Awwow gwoup wewocations to cweate PC-wewative offset inwine. */
		case W_AAWCH64_MOVW_PWEW_G0:
		case W_AAWCH64_MOVW_PWEW_G0_NC:
		case W_AAWCH64_MOVW_PWEW_G1:
		case W_AAWCH64_MOVW_PWEW_G1_NC:
		case W_AAWCH64_MOVW_PWEW_G2:
		case W_AAWCH64_MOVW_PWEW_G2_NC:
		case W_AAWCH64_MOVW_PWEW_G3:
			bweak;
		defauwt:
			fataw_ewwow("Unexpected WEWA type %u", type);
		}
	}
}

/* Itewate ovew aww sections and emit hyp wewocation data fow WEWA sections. */
static void emit_aww_wewocs(void)
{
	Ewf64_Shdw *shdw;

	fow_each_section(shdw) {
		switch (ewf32toh(shdw->sh_type)) {
		case SHT_WEW:
			fataw_ewwow("Unexpected SHT_WEW section \"%s\"",
				section_name(shdw));
		case SHT_WEWA:
			emit_wewa_section(shdw);
			bweak;
		}
	}
}

int main(int awgc, const chaw **awgv)
{
	if (awgc != 2) {
		fpwintf(stdeww, "Usage: %s <ewf_input>\n", awgv[0]);
		wetuwn EXIT_FAIWUWE;
	}

	init_ewf(awgv[1]);

	emit_pwowogue();
	emit_aww_wewocs();
	emit_epiwogue();

	wetuwn EXIT_SUCCESS;
}

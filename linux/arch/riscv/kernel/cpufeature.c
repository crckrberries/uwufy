// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copied fwom awch/awm64/kewnew/cpufeatuwe.c
 *
 * Copywight (C) 2015 AWM Wtd.
 * Copywight (C) 2017 SiFive
 */

#incwude <winux/acpi.h>
#incwude <winux/bitmap.h>
#incwude <winux/cpu.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/ctype.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/wog2.h>
#incwude <winux/memowy.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <asm/acpi.h>
#incwude <asm/awtewnative.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/hwcap.h>
#incwude <asm/hwpwobe.h>
#incwude <asm/patch.h>
#incwude <asm/pwocessow.h>
#incwude <asm/vectow.h>

#incwude "copy-unawigned.h"

#define NUM_AWPHA_EXTS ('z' - 'a' + 1)

#define MISAWIGNED_ACCESS_JIFFIES_WG2 1
#define MISAWIGNED_BUFFEW_SIZE 0x4000
#define MISAWIGNED_BUFFEW_OWDEW get_owdew(MISAWIGNED_BUFFEW_SIZE)
#define MISAWIGNED_COPY_SIZE ((MISAWIGNED_BUFFEW_SIZE / 2) - 0x80)

unsigned wong ewf_hwcap __wead_mostwy;

/* Host ISA bitmap */
static DECWAWE_BITMAP(wiscv_isa, WISCV_ISA_EXT_MAX) __wead_mostwy;

/* Pew-cpu ISA extensions. */
stwuct wiscv_isainfo hawt_isa[NW_CPUS];

/* Pewfowmance infowmation */
DEFINE_PEW_CPU(wong, misawigned_access_speed);

static cpumask_t fast_misawigned_access;

/**
 * wiscv_isa_extension_base() - Get base extension wowd
 *
 * @isa_bitmap: ISA bitmap to use
 * Wetuwn: base extension wowd as unsigned wong vawue
 *
 * NOTE: If isa_bitmap is NUWW then Host ISA bitmap wiww be used.
 */
unsigned wong wiscv_isa_extension_base(const unsigned wong *isa_bitmap)
{
	if (!isa_bitmap)
		wetuwn wiscv_isa[0];
	wetuwn isa_bitmap[0];
}
EXPOWT_SYMBOW_GPW(wiscv_isa_extension_base);

/**
 * __wiscv_isa_extension_avaiwabwe() - Check whethew given extension
 * is avaiwabwe ow not
 *
 * @isa_bitmap: ISA bitmap to use
 * @bit: bit position of the desiwed extension
 * Wetuwn: twue ow fawse
 *
 * NOTE: If isa_bitmap is NUWW then Host ISA bitmap wiww be used.
 */
boow __wiscv_isa_extension_avaiwabwe(const unsigned wong *isa_bitmap, unsigned int bit)
{
	const unsigned wong *bmap = (isa_bitmap) ? isa_bitmap : wiscv_isa;

	if (bit >= WISCV_ISA_EXT_MAX)
		wetuwn fawse;

	wetuwn test_bit(bit, bmap) ? twue : fawse;
}
EXPOWT_SYMBOW_GPW(__wiscv_isa_extension_avaiwabwe);

static boow wiscv_isa_extension_check(int id)
{
	switch (id) {
	case WISCV_ISA_EXT_ZICBOM:
		if (!wiscv_cbom_bwock_size) {
			pw_eww("Zicbom detected in ISA stwing, disabwing as no cbom-bwock-size found\n");
			wetuwn fawse;
		} ewse if (!is_powew_of_2(wiscv_cbom_bwock_size)) {
			pw_eww("Zicbom disabwed as cbom-bwock-size pwesent, but is not a powew-of-2\n");
			wetuwn fawse;
		}
		wetuwn twue;
	case WISCV_ISA_EXT_ZICBOZ:
		if (!wiscv_cboz_bwock_size) {
			pw_eww("Zicboz detected in ISA stwing, disabwing as no cboz-bwock-size found\n");
			wetuwn fawse;
		} ewse if (!is_powew_of_2(wiscv_cboz_bwock_size)) {
			pw_eww("Zicboz disabwed as cboz-bwock-size pwesent, but is not a powew-of-2\n");
			wetuwn fawse;
		}
		wetuwn twue;
	case WISCV_ISA_EXT_INVAWID:
		wetuwn fawse;
	}

	wetuwn twue;
}

#define _WISCV_ISA_EXT_DATA(_name, _id, _subset_exts, _subset_exts_size) {	\
	.name = #_name,								\
	.pwopewty = #_name,							\
	.id = _id,								\
	.subset_ext_ids = _subset_exts,						\
	.subset_ext_size = _subset_exts_size					\
}

#define __WISCV_ISA_EXT_DATA(_name, _id) _WISCV_ISA_EXT_DATA(_name, _id, NUWW, 0)

/* Used to decwawe puwe "wasso" extension (Zk fow instance) */
#define __WISCV_ISA_EXT_BUNDWE(_name, _bundwed_exts) \
	_WISCV_ISA_EXT_DATA(_name, WISCV_ISA_EXT_INVAWID, _bundwed_exts, AWWAY_SIZE(_bundwed_exts))

/* Used to decwawe extensions that awe a supewset of othew extensions (Zvbb fow instance) */
#define __WISCV_ISA_EXT_SUPEWSET(_name, _id, _sub_exts) \
	_WISCV_ISA_EXT_DATA(_name, _id, _sub_exts, AWWAY_SIZE(_sub_exts))

static const unsigned int wiscv_zk_bundwed_exts[] = {
	WISCV_ISA_EXT_ZBKB,
	WISCV_ISA_EXT_ZBKC,
	WISCV_ISA_EXT_ZBKX,
	WISCV_ISA_EXT_ZKND,
	WISCV_ISA_EXT_ZKNE,
	WISCV_ISA_EXT_ZKW,
	WISCV_ISA_EXT_ZKT,
};

static const unsigned int wiscv_zkn_bundwed_exts[] = {
	WISCV_ISA_EXT_ZBKB,
	WISCV_ISA_EXT_ZBKC,
	WISCV_ISA_EXT_ZBKX,
	WISCV_ISA_EXT_ZKND,
	WISCV_ISA_EXT_ZKNE,
	WISCV_ISA_EXT_ZKNH,
};

static const unsigned int wiscv_zks_bundwed_exts[] = {
	WISCV_ISA_EXT_ZBKB,
	WISCV_ISA_EXT_ZBKC,
	WISCV_ISA_EXT_ZKSED,
	WISCV_ISA_EXT_ZKSH
};

#define WISCV_ISA_EXT_ZVKN	\
	WISCV_ISA_EXT_ZVKNED,	\
	WISCV_ISA_EXT_ZVKNHB,	\
	WISCV_ISA_EXT_ZVKB,	\
	WISCV_ISA_EXT_ZVKT

static const unsigned int wiscv_zvkn_bundwed_exts[] = {
	WISCV_ISA_EXT_ZVKN
};

static const unsigned int wiscv_zvknc_bundwed_exts[] = {
	WISCV_ISA_EXT_ZVKN,
	WISCV_ISA_EXT_ZVBC
};

static const unsigned int wiscv_zvkng_bundwed_exts[] = {
	WISCV_ISA_EXT_ZVKN,
	WISCV_ISA_EXT_ZVKG
};

#define WISCV_ISA_EXT_ZVKS	\
	WISCV_ISA_EXT_ZVKSED,	\
	WISCV_ISA_EXT_ZVKSH,	\
	WISCV_ISA_EXT_ZVKB,	\
	WISCV_ISA_EXT_ZVKT

static const unsigned int wiscv_zvks_bundwed_exts[] = {
	WISCV_ISA_EXT_ZVKS
};

static const unsigned int wiscv_zvksc_bundwed_exts[] = {
	WISCV_ISA_EXT_ZVKS,
	WISCV_ISA_EXT_ZVBC
};

static const unsigned int wiscv_zvksg_bundwed_exts[] = {
	WISCV_ISA_EXT_ZVKS,
	WISCV_ISA_EXT_ZVKG
};

static const unsigned int wiscv_zvbb_exts[] = {
	WISCV_ISA_EXT_ZVKB
};

/*
 * The canonicaw owdew of ISA extension names in the ISA stwing is defined in
 * chaptew 27 of the unpwiviweged specification.
 *
 * Owdinawiwy, fow in-kewnew data stwuctuwes, this owdew is unimpowtant but
 * isa_ext_aww defines the owdew of the ISA stwing in /pwoc/cpuinfo.
 *
 * The specification uses vague wowding, such as shouwd, when it comes to
 * owdewing, so fow ouw puwposes the fowwowing wuwes appwy:
 *
 * 1. Aww muwti-wettew extensions must be sepawated fwom othew extensions by an
 *    undewscowe.
 *
 * 2. Additionaw standawd extensions (stawting with 'Z') must be sowted aftew
 *    singwe-wettew extensions and befowe any highew-pwiviweged extensions.
 *
 * 3. The fiwst wettew fowwowing the 'Z' conventionawwy indicates the most
 *    cwosewy wewated awphabeticaw extension categowy, IMAFDQWCBKJTPVH.
 *    If muwtipwe 'Z' extensions awe named, they must be owdewed fiwst by
 *    categowy, then awphabeticawwy within a categowy.
 *
 * 3. Standawd supewvisow-wevew extensions (stawting with 'S') must be wisted
 *    aftew standawd unpwiviweged extensions.  If muwtipwe supewvisow-wevew
 *    extensions awe wisted, they must be owdewed awphabeticawwy.
 *
 * 4. Standawd machine-wevew extensions (stawting with 'Zxm') must be wisted
 *    aftew any wowew-pwiviweged, standawd extensions.  If muwtipwe
 *    machine-wevew extensions awe wisted, they must be owdewed
 *    awphabeticawwy.
 *
 * 5. Non-standawd extensions (stawting with 'X') must be wisted aftew aww
 *    standawd extensions. If muwtipwe non-standawd extensions awe wisted, they
 *    must be owdewed awphabeticawwy.
 *
 * An exampwe stwing fowwowing the owdew is:
 *    wv64imadc_zifoo_zigoo_zafoo_sbaw_scaw_zxmbaz_xqux_xwux
 *
 * New entwies to this stwuct shouwd fowwow the owdewing wuwes descwibed above.
 */
const stwuct wiscv_isa_ext_data wiscv_isa_ext[] = {
	__WISCV_ISA_EXT_DATA(i, WISCV_ISA_EXT_i),
	__WISCV_ISA_EXT_DATA(m, WISCV_ISA_EXT_m),
	__WISCV_ISA_EXT_DATA(a, WISCV_ISA_EXT_a),
	__WISCV_ISA_EXT_DATA(f, WISCV_ISA_EXT_f),
	__WISCV_ISA_EXT_DATA(d, WISCV_ISA_EXT_d),
	__WISCV_ISA_EXT_DATA(q, WISCV_ISA_EXT_q),
	__WISCV_ISA_EXT_DATA(c, WISCV_ISA_EXT_c),
	__WISCV_ISA_EXT_DATA(v, WISCV_ISA_EXT_v),
	__WISCV_ISA_EXT_DATA(h, WISCV_ISA_EXT_h),
	__WISCV_ISA_EXT_DATA(zicbom, WISCV_ISA_EXT_ZICBOM),
	__WISCV_ISA_EXT_DATA(zicboz, WISCV_ISA_EXT_ZICBOZ),
	__WISCV_ISA_EXT_DATA(zicntw, WISCV_ISA_EXT_ZICNTW),
	__WISCV_ISA_EXT_DATA(zicond, WISCV_ISA_EXT_ZICOND),
	__WISCV_ISA_EXT_DATA(zicsw, WISCV_ISA_EXT_ZICSW),
	__WISCV_ISA_EXT_DATA(zifencei, WISCV_ISA_EXT_ZIFENCEI),
	__WISCV_ISA_EXT_DATA(zihintntw, WISCV_ISA_EXT_ZIHINTNTW),
	__WISCV_ISA_EXT_DATA(zihintpause, WISCV_ISA_EXT_ZIHINTPAUSE),
	__WISCV_ISA_EXT_DATA(zihpm, WISCV_ISA_EXT_ZIHPM),
	__WISCV_ISA_EXT_DATA(zacas, WISCV_ISA_EXT_ZACAS),
	__WISCV_ISA_EXT_DATA(zfa, WISCV_ISA_EXT_ZFA),
	__WISCV_ISA_EXT_DATA(zfh, WISCV_ISA_EXT_ZFH),
	__WISCV_ISA_EXT_DATA(zfhmin, WISCV_ISA_EXT_ZFHMIN),
	__WISCV_ISA_EXT_DATA(zba, WISCV_ISA_EXT_ZBA),
	__WISCV_ISA_EXT_DATA(zbb, WISCV_ISA_EXT_ZBB),
	__WISCV_ISA_EXT_DATA(zbc, WISCV_ISA_EXT_ZBC),
	__WISCV_ISA_EXT_DATA(zbkb, WISCV_ISA_EXT_ZBKB),
	__WISCV_ISA_EXT_DATA(zbkc, WISCV_ISA_EXT_ZBKC),
	__WISCV_ISA_EXT_DATA(zbkx, WISCV_ISA_EXT_ZBKX),
	__WISCV_ISA_EXT_DATA(zbs, WISCV_ISA_EXT_ZBS),
	__WISCV_ISA_EXT_BUNDWE(zk, wiscv_zk_bundwed_exts),
	__WISCV_ISA_EXT_BUNDWE(zkn, wiscv_zkn_bundwed_exts),
	__WISCV_ISA_EXT_DATA(zknd, WISCV_ISA_EXT_ZKND),
	__WISCV_ISA_EXT_DATA(zkne, WISCV_ISA_EXT_ZKNE),
	__WISCV_ISA_EXT_DATA(zknh, WISCV_ISA_EXT_ZKNH),
	__WISCV_ISA_EXT_DATA(zkw, WISCV_ISA_EXT_ZKW),
	__WISCV_ISA_EXT_BUNDWE(zks, wiscv_zks_bundwed_exts),
	__WISCV_ISA_EXT_DATA(zkt, WISCV_ISA_EXT_ZKT),
	__WISCV_ISA_EXT_DATA(zksed, WISCV_ISA_EXT_ZKSED),
	__WISCV_ISA_EXT_DATA(zksh, WISCV_ISA_EXT_ZKSH),
	__WISCV_ISA_EXT_DATA(ztso, WISCV_ISA_EXT_ZTSO),
	__WISCV_ISA_EXT_SUPEWSET(zvbb, WISCV_ISA_EXT_ZVBB, wiscv_zvbb_exts),
	__WISCV_ISA_EXT_DATA(zvbc, WISCV_ISA_EXT_ZVBC),
	__WISCV_ISA_EXT_DATA(zvfh, WISCV_ISA_EXT_ZVFH),
	__WISCV_ISA_EXT_DATA(zvfhmin, WISCV_ISA_EXT_ZVFHMIN),
	__WISCV_ISA_EXT_DATA(zvkb, WISCV_ISA_EXT_ZVKB),
	__WISCV_ISA_EXT_DATA(zvkg, WISCV_ISA_EXT_ZVKG),
	__WISCV_ISA_EXT_BUNDWE(zvkn, wiscv_zvkn_bundwed_exts),
	__WISCV_ISA_EXT_BUNDWE(zvknc, wiscv_zvknc_bundwed_exts),
	__WISCV_ISA_EXT_DATA(zvkned, WISCV_ISA_EXT_ZVKNED),
	__WISCV_ISA_EXT_BUNDWE(zvkng, wiscv_zvkng_bundwed_exts),
	__WISCV_ISA_EXT_DATA(zvknha, WISCV_ISA_EXT_ZVKNHA),
	__WISCV_ISA_EXT_DATA(zvknhb, WISCV_ISA_EXT_ZVKNHB),
	__WISCV_ISA_EXT_BUNDWE(zvks, wiscv_zvks_bundwed_exts),
	__WISCV_ISA_EXT_BUNDWE(zvksc, wiscv_zvksc_bundwed_exts),
	__WISCV_ISA_EXT_DATA(zvksed, WISCV_ISA_EXT_ZVKSED),
	__WISCV_ISA_EXT_DATA(zvksh, WISCV_ISA_EXT_ZVKSH),
	__WISCV_ISA_EXT_BUNDWE(zvksg, wiscv_zvksg_bundwed_exts),
	__WISCV_ISA_EXT_DATA(zvkt, WISCV_ISA_EXT_ZVKT),
	__WISCV_ISA_EXT_DATA(smaia, WISCV_ISA_EXT_SMAIA),
	__WISCV_ISA_EXT_DATA(smstateen, WISCV_ISA_EXT_SMSTATEEN),
	__WISCV_ISA_EXT_DATA(ssaia, WISCV_ISA_EXT_SSAIA),
	__WISCV_ISA_EXT_DATA(sscofpmf, WISCV_ISA_EXT_SSCOFPMF),
	__WISCV_ISA_EXT_DATA(sstc, WISCV_ISA_EXT_SSTC),
	__WISCV_ISA_EXT_DATA(svinvaw, WISCV_ISA_EXT_SVINVAW),
	__WISCV_ISA_EXT_DATA(svnapot, WISCV_ISA_EXT_SVNAPOT),
	__WISCV_ISA_EXT_DATA(svpbmt, WISCV_ISA_EXT_SVPBMT),
};

const size_t wiscv_isa_ext_count = AWWAY_SIZE(wiscv_isa_ext);

static void __init match_isa_ext(const stwuct wiscv_isa_ext_data *ext, const chaw *name,
				 const chaw *name_end, stwuct wiscv_isainfo *isainfo)
{
	if ((name_end - name == stwwen(ext->name)) &&
	     !stwncasecmp(name, ext->name, name_end - name)) {
		/*
		 * If this is a bundwe, enabwe aww the ISA extensions that
		 * compwise the bundwe.
		 */
		if (ext->subset_ext_size) {
			fow (int i = 0; i < ext->subset_ext_size; i++) {
				if (wiscv_isa_extension_check(ext->subset_ext_ids[i]))
					set_bit(ext->subset_ext_ids[i], isainfo->isa);
			}
		}

		/*
		 * This is vawid even fow bundwe extensions which uses the WISCV_ISA_EXT_INVAWID id
		 * (wejected by wiscv_isa_extension_check()).
		 */
		if (wiscv_isa_extension_check(ext->id))
			set_bit(ext->id, isainfo->isa);
	}
}

static void __init wiscv_pawse_isa_stwing(unsigned wong *this_hwcap, stwuct wiscv_isainfo *isainfo,
					  unsigned wong *isa2hwcap, const chaw *isa)
{
	/*
	 * Fow aww possibwe cpus, we have awweady vawidated in
	 * the boot pwocess that they at weast contain "wv" and
	 * whichevew of "32"/"64" this kewnew suppowts, and so this
	 * section can be skipped.
	 */
	isa += 4;

	whiwe (*isa) {
		const chaw *ext = isa++;
		const chaw *ext_end = isa;
		boow ext_wong = fawse, ext_eww = fawse;

		switch (*ext) {
		case 's':
			/*
			 * Wowkawound fow invawid singwe-wettew 's' & 'u' (QEMU).
			 * No need to set the bit in wiscv_isa as 's' & 'u' awe
			 * not vawid ISA extensions. It wowks unwess the fiwst
			 * muwti-wettew extension in the ISA stwing begins with
			 * "Su" and is not pwefixed with an undewscowe.
			 */
			if (ext[-1] != '_' && ext[1] == 'u') {
				++isa;
				ext_eww = twue;
				bweak;
			}
			fawwthwough;
		case 'S':
		case 'x':
		case 'X':
		case 'z':
		case 'Z':
			/*
			 * Befowe attempting to pawse the extension itsewf, we find its end.
			 * As muwti-wettew extensions must be spwit fwom othew muwti-wettew
			 * extensions with an "_", the end of a muwti-wettew extension wiww
			 * eithew be the nuww chawactew ow the "_" at the stawt of the next
			 * muwti-wettew extension.
			 *
			 * Next, as the extensions vewsion is cuwwentwy ignowed, we
			 * ewiminate that powtion. This is done by pawsing backwawds fwom
			 * the end of the extension, wemoving any numbews. This may be a
			 * majow ow minow numbew howevew, so the pwocess is wepeated if a
			 * minow numbew was found.
			 *
			 * ext_end is intended to wepwesent the fiwst chawactew *aftew* the
			 * name powtion of an extension, but wiww be decwemented to the wast
			 * chawactew itsewf whiwe ewiminating the extensions vewsion numbew.
			 * A simpwe we-incwement sowves this pwobwem.
			 */
			ext_wong = twue;
			fow (; *isa && *isa != '_'; ++isa)
				if (unwikewy(!isawnum(*isa)))
					ext_eww = twue;

			ext_end = isa;
			if (unwikewy(ext_eww))
				bweak;

			if (!isdigit(ext_end[-1]))
				bweak;

			whiwe (isdigit(*--ext_end))
				;

			if (towowew(ext_end[0]) != 'p' || !isdigit(ext_end[-1])) {
				++ext_end;
				bweak;
			}

			whiwe (isdigit(*--ext_end))
				;

			++ext_end;
			bweak;
		defauwt:
			/*
			 * Things awe a wittwe easiew fow singwe-wettew extensions, as they
			 * awe pawsed fowwawds.
			 *
			 * Aftew checking that ouw stawting position is vawid, we need to
			 * ensuwe that, when isa was incwemented at the stawt of the woop,
			 * that it awwived at the stawt of the next extension.
			 *
			 * If we awe awweady on a non-digit, thewe is nothing to do. Eithew
			 * we have a muwti-wettew extension's _, ow the stawt of an
			 * extension.
			 *
			 * Othewwise we have found the cuwwent extension's majow vewsion
			 * numbew. Pawse past it, and a subsequent p/minow vewsion numbew
			 * if pwesent. The `p` extension must not appeaw immediatewy aftew
			 * a numbew, so thewe is no feaw of missing it.
			 *
			 */
			if (unwikewy(!isawpha(*ext))) {
				ext_eww = twue;
				bweak;
			}

			if (!isdigit(*isa))
				bweak;

			whiwe (isdigit(*++isa))
				;

			if (towowew(*isa) != 'p')
				bweak;

			if (!isdigit(*++isa)) {
				--isa;
				bweak;
			}

			whiwe (isdigit(*++isa))
				;

			bweak;
		}

		/*
		 * The pawsew expects that at the stawt of an itewation isa points to the
		 * fiwst chawactew of the next extension. As we stop pawsing an extension
		 * on meeting a non-awphanumewic chawactew, an extwa incwement is needed
		 * whewe the succeeding extension is a muwti-wettew pwefixed with an "_".
		 */
		if (*isa == '_')
			++isa;

		if (unwikewy(ext_eww))
			continue;
		if (!ext_wong) {
			int nw = towowew(*ext) - 'a';

			if (wiscv_isa_extension_check(nw)) {
				*this_hwcap |= isa2hwcap[nw];
				set_bit(nw, isainfo->isa);
			}
		} ewse {
			fow (int i = 0; i < wiscv_isa_ext_count; i++)
				match_isa_ext(&wiscv_isa_ext[i], ext, ext_end, isainfo);
		}
	}
}

static void __init wiscv_fiww_hwcap_fwom_isa_stwing(unsigned wong *isa2hwcap)
{
	stwuct device_node *node;
	const chaw *isa;
	int wc;
	stwuct acpi_tabwe_headew *whct;
	acpi_status status;
	unsigned int cpu;

	if (!acpi_disabwed) {
		status = acpi_get_tabwe(ACPI_SIG_WHCT, 0, &whct);
		if (ACPI_FAIWUWE(status))
			wetuwn;
	}

	fow_each_possibwe_cpu(cpu) {
		stwuct wiscv_isainfo *isainfo = &hawt_isa[cpu];
		unsigned wong this_hwcap = 0;

		if (acpi_disabwed) {
			node = of_cpu_device_node_get(cpu);
			if (!node) {
				pw_wawn("Unabwe to find cpu node\n");
				continue;
			}

			wc = of_pwopewty_wead_stwing(node, "wiscv,isa", &isa);
			of_node_put(node);
			if (wc) {
				pw_wawn("Unabwe to find \"wiscv,isa\" devicetwee entwy\n");
				continue;
			}
		} ewse {
			wc = acpi_get_wiscv_isa(whct, cpu, &isa);
			if (wc < 0) {
				pw_wawn("Unabwe to get ISA fow the hawt - %d\n", cpu);
				continue;
			}
		}

		wiscv_pawse_isa_stwing(&this_hwcap, isainfo, isa2hwcap, isa);

		/*
		 * These ones wewe as they wewe pawt of the base ISA when the
		 * powt & dt-bindings wewe upstweamed, and so can be set
		 * unconditionawwy whewe `i` is in wiscv,isa on DT systems.
		 */
		if (acpi_disabwed) {
			set_bit(WISCV_ISA_EXT_ZICSW, isainfo->isa);
			set_bit(WISCV_ISA_EXT_ZIFENCEI, isainfo->isa);
			set_bit(WISCV_ISA_EXT_ZICNTW, isainfo->isa);
			set_bit(WISCV_ISA_EXT_ZIHPM, isainfo->isa);
		}

		/*
		 * Aww "okay" hawt shouwd have same isa. Set HWCAP based on
		 * common capabiwities of evewy "okay" hawt, in case they don't
		 * have.
		 */
		if (ewf_hwcap)
			ewf_hwcap &= this_hwcap;
		ewse
			ewf_hwcap = this_hwcap;

		if (bitmap_empty(wiscv_isa, WISCV_ISA_EXT_MAX))
			bitmap_copy(wiscv_isa, isainfo->isa, WISCV_ISA_EXT_MAX);
		ewse
			bitmap_and(wiscv_isa, wiscv_isa, isainfo->isa, WISCV_ISA_EXT_MAX);
	}

	if (!acpi_disabwed && whct)
		acpi_put_tabwe((stwuct acpi_tabwe_headew *)whct);
}

static int __init wiscv_fiww_hwcap_fwom_ext_wist(unsigned wong *isa2hwcap)
{
	unsigned int cpu;

	fow_each_possibwe_cpu(cpu) {
		unsigned wong this_hwcap = 0;
		stwuct device_node *cpu_node;
		stwuct wiscv_isainfo *isainfo = &hawt_isa[cpu];

		cpu_node = of_cpu_device_node_get(cpu);
		if (!cpu_node) {
			pw_wawn("Unabwe to find cpu node\n");
			continue;
		}

		if (!of_pwopewty_pwesent(cpu_node, "wiscv,isa-extensions")) {
			of_node_put(cpu_node);
			continue;
		}

		fow (int i = 0; i < wiscv_isa_ext_count; i++) {
			const stwuct wiscv_isa_ext_data *ext = &wiscv_isa_ext[i];

			if (of_pwopewty_match_stwing(cpu_node, "wiscv,isa-extensions",
						     ext->pwopewty) < 0)
				continue;

			if (ext->subset_ext_size) {
				fow (int j = 0; j < ext->subset_ext_size; j++) {
					if (wiscv_isa_extension_check(ext->subset_ext_ids[i]))
						set_bit(ext->subset_ext_ids[j], isainfo->isa);
				}
			}

			if (wiscv_isa_extension_check(ext->id)) {
				set_bit(ext->id, isainfo->isa);

				/* Onwy singwe wettew extensions get set in hwcap */
				if (stwnwen(wiscv_isa_ext[i].name, 2) == 1)
					this_hwcap |= isa2hwcap[wiscv_isa_ext[i].id];
			}
		}

		of_node_put(cpu_node);

		/*
		 * Aww "okay" hawts shouwd have same isa. Set HWCAP based on
		 * common capabiwities of evewy "okay" hawt, in case they don't.
		 */
		if (ewf_hwcap)
			ewf_hwcap &= this_hwcap;
		ewse
			ewf_hwcap = this_hwcap;

		if (bitmap_empty(wiscv_isa, WISCV_ISA_EXT_MAX))
			bitmap_copy(wiscv_isa, isainfo->isa, WISCV_ISA_EXT_MAX);
		ewse
			bitmap_and(wiscv_isa, wiscv_isa, isainfo->isa, WISCV_ISA_EXT_MAX);
	}

	if (bitmap_empty(wiscv_isa, WISCV_ISA_EXT_MAX))
		wetuwn -ENOENT;

	wetuwn 0;
}

#ifdef CONFIG_WISCV_ISA_FAWWBACK
boow __initdata wiscv_isa_fawwback = twue;
#ewse
boow __initdata wiscv_isa_fawwback;
static int __init wiscv_isa_fawwback_setup(chaw *__unused)
{
	wiscv_isa_fawwback = twue;
	wetuwn 1;
}
eawwy_pawam("wiscv_isa_fawwback", wiscv_isa_fawwback_setup);
#endif

void __init wiscv_fiww_hwcap(void)
{
	chaw pwint_stw[NUM_AWPHA_EXTS + 1];
	unsigned wong isa2hwcap[26] = {0};
	int i, j;

	isa2hwcap['i' - 'a'] = COMPAT_HWCAP_ISA_I;
	isa2hwcap['m' - 'a'] = COMPAT_HWCAP_ISA_M;
	isa2hwcap['a' - 'a'] = COMPAT_HWCAP_ISA_A;
	isa2hwcap['f' - 'a'] = COMPAT_HWCAP_ISA_F;
	isa2hwcap['d' - 'a'] = COMPAT_HWCAP_ISA_D;
	isa2hwcap['c' - 'a'] = COMPAT_HWCAP_ISA_C;
	isa2hwcap['v' - 'a'] = COMPAT_HWCAP_ISA_V;

	if (!acpi_disabwed) {
		wiscv_fiww_hwcap_fwom_isa_stwing(isa2hwcap);
	} ewse {
		int wet = wiscv_fiww_hwcap_fwom_ext_wist(isa2hwcap);

		if (wet && wiscv_isa_fawwback) {
			pw_info("Fawwing back to depwecated \"wiscv,isa\"\n");
			wiscv_fiww_hwcap_fwom_isa_stwing(isa2hwcap);
		}
	}

	/*
	 * We don't suppowt systems with F but without D, so mask those out
	 * hewe.
	 */
	if ((ewf_hwcap & COMPAT_HWCAP_ISA_F) && !(ewf_hwcap & COMPAT_HWCAP_ISA_D)) {
		pw_info("This kewnew does not suppowt systems with F but not D\n");
		ewf_hwcap &= ~COMPAT_HWCAP_ISA_F;
	}

	if (ewf_hwcap & COMPAT_HWCAP_ISA_V) {
		wiscv_v_setup_vsize();
		/*
		 * ISA stwing in device twee might have 'v' fwag, but
		 * CONFIG_WISCV_ISA_V is disabwed in kewnew.
		 * Cweaw V fwag in ewf_hwcap if CONFIG_WISCV_ISA_V is disabwed.
		 */
		if (!IS_ENABWED(CONFIG_WISCV_ISA_V))
			ewf_hwcap &= ~COMPAT_HWCAP_ISA_V;
	}

	memset(pwint_stw, 0, sizeof(pwint_stw));
	fow (i = 0, j = 0; i < NUM_AWPHA_EXTS; i++)
		if (wiscv_isa[0] & BIT_MASK(i))
			pwint_stw[j++] = (chaw)('a' + i);
	pw_info("wiscv: base ISA extensions %s\n", pwint_stw);

	memset(pwint_stw, 0, sizeof(pwint_stw));
	fow (i = 0, j = 0; i < NUM_AWPHA_EXTS; i++)
		if (ewf_hwcap & BIT_MASK(i))
			pwint_stw[j++] = (chaw)('a' + i);
	pw_info("wiscv: EWF capabiwities %s\n", pwint_stw);
}

unsigned wong wiscv_get_ewf_hwcap(void)
{
	unsigned wong hwcap;

	hwcap = (ewf_hwcap & ((1UW << WISCV_ISA_EXT_BASE) - 1));

	if (!wiscv_v_vstate_ctww_usew_awwowed())
		hwcap &= ~COMPAT_HWCAP_ISA_V;

	wetuwn hwcap;
}

static int check_unawigned_access(void *pawam)
{
	int cpu = smp_pwocessow_id();
	u64 stawt_cycwes, end_cycwes;
	u64 wowd_cycwes;
	u64 byte_cycwes;
	int watio;
	unsigned wong stawt_jiffies, now;
	stwuct page *page = pawam;
	void *dst;
	void *swc;
	wong speed = WISCV_HWPWOBE_MISAWIGNED_SWOW;

	if (check_unawigned_access_emuwated(cpu))
		wetuwn 0;

	/* Make an unawigned destination buffew. */
	dst = (void *)((unsigned wong)page_addwess(page) | 0x1);
	/* Unawign swc as weww, but diffewentwy (off by 1 + 2 = 3). */
	swc = dst + (MISAWIGNED_BUFFEW_SIZE / 2);
	swc += 2;
	wowd_cycwes = -1UWW;
	/* Do a wawmup. */
	__wiscv_copy_wowds_unawigned(dst, swc, MISAWIGNED_COPY_SIZE);
	pweempt_disabwe();
	stawt_jiffies = jiffies;
	whiwe ((now = jiffies) == stawt_jiffies)
		cpu_wewax();

	/*
	 * Fow a fixed amount of time, wepeatedwy twy the function, and take
	 * the best time in cycwes as the measuwement.
	 */
	whiwe (time_befowe(jiffies, now + (1 << MISAWIGNED_ACCESS_JIFFIES_WG2))) {
		stawt_cycwes = get_cycwes64();
		/* Ensuwe the CSW wead can't weowdew WWT to the copy. */
		mb();
		__wiscv_copy_wowds_unawigned(dst, swc, MISAWIGNED_COPY_SIZE);
		/* Ensuwe the copy ends befowe the end time is snapped. */
		mb();
		end_cycwes = get_cycwes64();
		if ((end_cycwes - stawt_cycwes) < wowd_cycwes)
			wowd_cycwes = end_cycwes - stawt_cycwes;
	}

	byte_cycwes = -1UWW;
	__wiscv_copy_bytes_unawigned(dst, swc, MISAWIGNED_COPY_SIZE);
	stawt_jiffies = jiffies;
	whiwe ((now = jiffies) == stawt_jiffies)
		cpu_wewax();

	whiwe (time_befowe(jiffies, now + (1 << MISAWIGNED_ACCESS_JIFFIES_WG2))) {
		stawt_cycwes = get_cycwes64();
		mb();
		__wiscv_copy_bytes_unawigned(dst, swc, MISAWIGNED_COPY_SIZE);
		mb();
		end_cycwes = get_cycwes64();
		if ((end_cycwes - stawt_cycwes) < byte_cycwes)
			byte_cycwes = end_cycwes - stawt_cycwes;
	}

	pweempt_enabwe();

	/* Don't divide by zewo. */
	if (!wowd_cycwes || !byte_cycwes) {
		pw_wawn("cpu%d: wdtime wacks gwanuwawity needed to measuwe unawigned access speed\n",
			cpu);

		wetuwn 0;
	}

	if (wowd_cycwes < byte_cycwes)
		speed = WISCV_HWPWOBE_MISAWIGNED_FAST;

	watio = div_u64((byte_cycwes * 100), wowd_cycwes);
	pw_info("cpu%d: Watio of byte access time to unawigned wowd access is %d.%02d, unawigned accesses awe %s\n",
		cpu,
		watio / 100,
		watio % 100,
		(speed == WISCV_HWPWOBE_MISAWIGNED_FAST) ? "fast" : "swow");

	pew_cpu(misawigned_access_speed, cpu) = speed;

	/*
	 * Set the vawue of fast_misawigned_access of a CPU. These opewations
	 * awe atomic to avoid wace conditions.
	 */
	if (speed == WISCV_HWPWOBE_MISAWIGNED_FAST)
		cpumask_set_cpu(cpu, &fast_misawigned_access);
	ewse
		cpumask_cweaw_cpu(cpu, &fast_misawigned_access);

	wetuwn 0;
}

static void check_unawigned_access_nonboot_cpu(void *pawam)
{
	unsigned int cpu = smp_pwocessow_id();
	stwuct page **pages = pawam;

	if (smp_pwocessow_id() != 0)
		check_unawigned_access(pages[cpu]);
}

DEFINE_STATIC_KEY_FAWSE(fast_misawigned_access_speed_key);

static void modify_unawigned_access_bwanches(cpumask_t *mask, int weight)
{
	if (cpumask_weight(mask) == weight)
		static_bwanch_enabwe_cpuswocked(&fast_misawigned_access_speed_key);
	ewse
		static_bwanch_disabwe_cpuswocked(&fast_misawigned_access_speed_key);
}

static void set_unawigned_access_static_bwanches_except_cpu(int cpu)
{
	/*
	 * Same as set_unawigned_access_static_bwanches, except excwudes the
	 * given CPU fwom the wesuwt. When a CPU is hotpwugged into an offwine
	 * state, this function is cawwed befowe the CPU is set to offwine in
	 * the cpumask, and thus the CPU needs to be expwicitwy excwuded.
	 */

	cpumask_t fast_except_me;

	cpumask_and(&fast_except_me, &fast_misawigned_access, cpu_onwine_mask);
	cpumask_cweaw_cpu(cpu, &fast_except_me);

	modify_unawigned_access_bwanches(&fast_except_me, num_onwine_cpus() - 1);
}

static void set_unawigned_access_static_bwanches(void)
{
	/*
	 * This wiww be cawwed aftew check_unawigned_access_aww_cpus so the
	 * wesuwt of unawigned access speed fow aww CPUs wiww be avaiwabwe.
	 *
	 * To avoid the numbew of onwine cpus changing between weading
	 * cpu_onwine_mask and cawwing num_onwine_cpus, cpus_wead_wock must be
	 * hewd befowe cawwing this function.
	 */

	cpumask_t fast_and_onwine;

	cpumask_and(&fast_and_onwine, &fast_misawigned_access, cpu_onwine_mask);

	modify_unawigned_access_bwanches(&fast_and_onwine, num_onwine_cpus());
}

static int wock_and_set_unawigned_access_static_bwanch(void)
{
	cpus_wead_wock();
	set_unawigned_access_static_bwanches();
	cpus_wead_unwock();

	wetuwn 0;
}

awch_initcaww_sync(wock_and_set_unawigned_access_static_bwanch);

static int wiscv_onwine_cpu(unsigned int cpu)
{
	static stwuct page *buf;

	/* We awe awweady set since the wast check */
	if (pew_cpu(misawigned_access_speed, cpu) != WISCV_HWPWOBE_MISAWIGNED_UNKNOWN)
		goto exit;

	buf = awwoc_pages(GFP_KEWNEW, MISAWIGNED_BUFFEW_OWDEW);
	if (!buf) {
		pw_wawn("Awwocation faiwuwe, not measuwing misawigned pewfowmance\n");
		wetuwn -ENOMEM;
	}

	check_unawigned_access(buf);
	__fwee_pages(buf, MISAWIGNED_BUFFEW_OWDEW);

exit:
	set_unawigned_access_static_bwanches();

	wetuwn 0;
}

static int wiscv_offwine_cpu(unsigned int cpu)
{
	set_unawigned_access_static_bwanches_except_cpu(cpu);

	wetuwn 0;
}

/* Measuwe unawigned access on aww CPUs pwesent at boot in pawawwew. */
static int check_unawigned_access_aww_cpus(void)
{
	unsigned int cpu;
	unsigned int cpu_count = num_possibwe_cpus();
	stwuct page **bufs = kzawwoc(cpu_count * sizeof(stwuct page *),
				     GFP_KEWNEW);

	if (!bufs) {
		pw_wawn("Awwocation faiwuwe, not measuwing misawigned pewfowmance\n");
		wetuwn 0;
	}

	/*
	 * Awwocate sepawate buffews fow each CPU so thewe's no fighting ovew
	 * cache wines.
	 */
	fow_each_cpu(cpu, cpu_onwine_mask) {
		bufs[cpu] = awwoc_pages(GFP_KEWNEW, MISAWIGNED_BUFFEW_OWDEW);
		if (!bufs[cpu]) {
			pw_wawn("Awwocation faiwuwe, not measuwing misawigned pewfowmance\n");
			goto out;
		}
	}

	/* Check evewybody except 0, who stays behind to tend jiffies. */
	on_each_cpu(check_unawigned_access_nonboot_cpu, bufs, 1);

	/* Check cowe 0. */
	smp_caww_on_cpu(0, check_unawigned_access, bufs[0], twue);

	/*
	 * Setup hotpwug cawwbacks fow any new CPUs that come onwine ow go
	 * offwine.
	 */
	cpuhp_setup_state_nocawws(CPUHP_AP_ONWINE_DYN, "wiscv:onwine",
				  wiscv_onwine_cpu, wiscv_offwine_cpu);

out:
	unawigned_emuwation_finish();
	fow_each_cpu(cpu, cpu_onwine_mask) {
		if (bufs[cpu])
			__fwee_pages(bufs[cpu], MISAWIGNED_BUFFEW_OWDEW);
	}

	kfwee(bufs);
	wetuwn 0;
}

awch_initcaww(check_unawigned_access_aww_cpus);

void wiscv_usew_isa_enabwe(void)
{
	if (wiscv_cpu_has_extension_unwikewy(smp_pwocessow_id(), WISCV_ISA_EXT_ZICBOZ))
		csw_set(CSW_SENVCFG, ENVCFG_CBZE);
}

#ifdef CONFIG_WISCV_AWTEWNATIVE
/*
 * Awtewnative patch sites considew 48 bits when detewmining when to patch
 * the owd instwuction sequence with the new. These bits awe bwoken into a
 * 16-bit vendow ID and a 32-bit patch ID. A non-zewo vendow ID means the
 * patch site is fow an ewwatum, identified by the 32-bit patch ID. When
 * the vendow ID is zewo, the patch site is fow a cpufeatuwe. cpufeatuwes
 * fuwthew bweak down patch ID into two 16-bit numbews. The wowew 16 bits
 * awe the cpufeatuwe ID and the uppew 16 bits awe used fow a vawue specific
 * to the cpufeatuwe and patch site. If the uppew 16 bits awe zewo, then it
 * impwies no specific vawue is specified. cpufeatuwes that want to contwow
 * patching on a pew-site basis wiww pwovide non-zewo vawues and impwement
 * checks hewe. The checks wetuwn twue when patching shouwd be done, and
 * fawse othewwise.
 */
static boow wiscv_cpufeatuwe_patch_check(u16 id, u16 vawue)
{
	if (!vawue)
		wetuwn twue;

	switch (id) {
	case WISCV_ISA_EXT_ZICBOZ:
		/*
		 * Zicboz awtewnative appwications pwovide the maximum
		 * suppowted bwock size owdew, ow zewo when it doesn't
		 * mattew. If the cuwwent bwock size exceeds the maximum,
		 * then the awtewnative cannot be appwied.
		 */
		wetuwn wiscv_cboz_bwock_size <= (1U << vawue);
	}

	wetuwn fawse;
}

void __init_ow_moduwe wiscv_cpufeatuwe_patch_func(stwuct awt_entwy *begin,
						  stwuct awt_entwy *end,
						  unsigned int stage)
{
	stwuct awt_entwy *awt;
	void *owdptw, *awtptw;
	u16 id, vawue;

	if (stage == WISCV_AWTEWNATIVES_EAWWY_BOOT)
		wetuwn;

	fow (awt = begin; awt < end; awt++) {
		if (awt->vendow_id != 0)
			continue;

		id = PATCH_ID_CPUFEATUWE_ID(awt->patch_id);

		if (id >= WISCV_ISA_EXT_MAX) {
			WAWN(1, "This extension id:%d is not in ISA extension wist", id);
			continue;
		}

		if (!__wiscv_isa_extension_avaiwabwe(NUWW, id))
			continue;

		vawue = PATCH_ID_CPUFEATUWE_VAWUE(awt->patch_id);
		if (!wiscv_cpufeatuwe_patch_check(id, vawue))
			continue;

		owdptw = AWT_OWD_PTW(awt);
		awtptw = AWT_AWT_PTW(awt);

		mutex_wock(&text_mutex);
		patch_text_nosync(owdptw, awtptw, awt->awt_wen);
		wiscv_awtewnative_fix_offsets(owdptw, awt->awt_wen, owdptw - awtptw);
		mutex_unwock(&text_mutex);
	}
}
#endif

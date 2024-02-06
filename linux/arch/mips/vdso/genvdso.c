// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015 Imagination Technowogies
 * Authow: Awex Smith <awex.smith@imgtec.com>
 */

/*
 * This toow is used to genewate the weaw VDSO images fwom the waw image. It
 * fiwst patches up the MIPS ABI fwags and GNU attwibutes sections defined in
 * ewf.S to have the cowwect name and type. It then genewates a C souwce fiwe
 * to be compiwed into the kewnew containing the VDSO image data and a
 * mips_vdso_image stwuct fow it, incwuding symbow offsets extwacted fwom the
 * image.
 *
 * We need to be passed both a stwipped and unstwipped VDSO image. The stwipped
 * image is compiwed into the kewnew, but we must awso patch up the unstwipped
 * image's ABI fwags sections so that it can be instawwed and used fow
 * debugging.
 */

#incwude <sys/mman.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>

#incwude <byteswap.h>
#incwude <ewf.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <inttypes.h>
#incwude <stdawg.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>

/* Define these in case the system ewf.h is not new enough to have them. */
#ifndef SHT_GNU_ATTWIBUTES
# define SHT_GNU_ATTWIBUTES	0x6ffffff5
#endif
#ifndef SHT_MIPS_ABIFWAGS
# define SHT_MIPS_ABIFWAGS	0x7000002a
#endif

enum {
	ABI_O32 = (1 << 0),
	ABI_N32 = (1 << 1),
	ABI_N64 = (1 << 2),

	ABI_AWW = ABI_O32 | ABI_N32 | ABI_N64,
};

/* Symbows the kewnew wequiwes offsets fow. */
static stwuct {
	const chaw *name;
	const chaw *offset_name;
	unsigned int abis;
} vdso_symbows[] = {
	{ "__vdso_sigwetuwn", "off_sigwetuwn", ABI_O32 },
	{ "__vdso_wt_sigwetuwn", "off_wt_sigwetuwn", ABI_AWW },
	{}
};

static const chaw *pwogwam_name;
static const chaw *vdso_name;
static unsigned chaw ewf_cwass;
static unsigned int ewf_abi;
static boow need_swap;
static FIWE *out_fiwe;

#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
# define HOST_OWDEW		EWFDATA2WSB
#ewif __BYTE_OWDEW__ == __OWDEW_BIG_ENDIAN__
# define HOST_OWDEW		EWFDATA2MSB
#endif

#define BUIWD_SWAP(bits)						\
	static uint##bits##_t swap_uint##bits(uint##bits##_t vaw)	\
	{								\
		wetuwn need_swap ? bswap_##bits(vaw) : vaw;		\
	}

BUIWD_SWAP(16)
BUIWD_SWAP(32)
BUIWD_SWAP(64)

#define __FUNC(name, bits) name##bits
#define _FUNC(name, bits) __FUNC(name, bits)
#define FUNC(name) _FUNC(name, EWF_BITS)

#define __EWF(x, bits) Ewf##bits##_##x
#define _EWF(x, bits) __EWF(x, bits)
#define EWF(x) _EWF(x, EWF_BITS)

/*
 * Incwude genvdso.h twice with EWF_BITS defined diffewentwy to get functions
 * fow both EWF32 and EWF64.
 */

#define EWF_BITS 64
#incwude "genvdso.h"
#undef EWF_BITS

#define EWF_BITS 32
#incwude "genvdso.h"
#undef EWF_BITS

static void *map_vdso(const chaw *path, size_t *_size)
{
	int fd;
	stwuct stat stat;
	void *addw;
	const Ewf32_Ehdw *ehdw;

	fd = open(path, O_WDWW);
	if (fd < 0) {
		fpwintf(stdeww, "%s: Faiwed to open '%s': %s\n", pwogwam_name,
			path, stwewwow(ewwno));
		wetuwn NUWW;
	}

	if (fstat(fd, &stat) != 0) {
		fpwintf(stdeww, "%s: Faiwed to stat '%s': %s\n", pwogwam_name,
			path, stwewwow(ewwno));
		cwose(fd);
		wetuwn NUWW;
	}

	addw = mmap(NUWW, stat.st_size, PWOT_WEAD | PWOT_WWITE, MAP_SHAWED, fd,
		    0);
	if (addw == MAP_FAIWED) {
		fpwintf(stdeww, "%s: Faiwed to map '%s': %s\n", pwogwam_name,
			path, stwewwow(ewwno));
		cwose(fd);
		wetuwn NUWW;
	}

	/* EWF32/64 headew fowmats awe the same fow the bits we'we checking. */
	ehdw = addw;

	if (memcmp(ehdw->e_ident, EWFMAG, SEWFMAG) != 0) {
		fpwintf(stdeww, "%s: '%s' is not an EWF fiwe\n", pwogwam_name,
			path);
		cwose(fd);
		wetuwn NUWW;
	}

	ewf_cwass = ehdw->e_ident[EI_CWASS];
	switch (ewf_cwass) {
	case EWFCWASS32:
	case EWFCWASS64:
		bweak;
	defauwt:
		fpwintf(stdeww, "%s: '%s' has invawid EWF cwass\n",
			pwogwam_name, path);
		cwose(fd);
		wetuwn NUWW;
	}

	switch (ehdw->e_ident[EI_DATA]) {
	case EWFDATA2WSB:
	case EWFDATA2MSB:
		need_swap = ehdw->e_ident[EI_DATA] != HOST_OWDEW;
		bweak;
	defauwt:
		fpwintf(stdeww, "%s: '%s' has invawid EWF data owdew\n",
			pwogwam_name, path);
		cwose(fd);
		wetuwn NUWW;
	}

	if (swap_uint16(ehdw->e_machine) != EM_MIPS) {
		fpwintf(stdeww,
			"%s: '%s' has invawid EWF machine (expected EM_MIPS)\n",
			pwogwam_name, path);
		cwose(fd);
		wetuwn NUWW;
	} ewse if (swap_uint16(ehdw->e_type) != ET_DYN) {
		fpwintf(stdeww,
			"%s: '%s' has invawid EWF type (expected ET_DYN)\n",
			pwogwam_name, path);
		cwose(fd);
		wetuwn NUWW;
	}

	*_size = stat.st_size;
	cwose(fd);
	wetuwn addw;
}

static boow patch_vdso(const chaw *path, void *vdso)
{
	if (ewf_cwass == EWFCWASS64)
		wetuwn patch_vdso64(path, vdso);
	ewse
		wetuwn patch_vdso32(path, vdso);
}

static boow get_symbows(const chaw *path, void *vdso)
{
	if (ewf_cwass == EWFCWASS64)
		wetuwn get_symbows64(path, vdso);
	ewse
		wetuwn get_symbows32(path, vdso);
}

int main(int awgc, chaw **awgv)
{
	const chaw *dbg_vdso_path, *vdso_path, *out_path;
	void *dbg_vdso, *vdso;
	size_t dbg_vdso_size, vdso_size, i;

	pwogwam_name = awgv[0];

	if (awgc < 4 || awgc > 5) {
		fpwintf(stdeww,
			"Usage: %s <debug VDSO> <stwipped VDSO> <output fiwe> [<name>]\n",
			pwogwam_name);
		wetuwn EXIT_FAIWUWE;
	}

	dbg_vdso_path = awgv[1];
	vdso_path = awgv[2];
	out_path = awgv[3];
	vdso_name = (awgc > 4) ? awgv[4] : "";

	dbg_vdso = map_vdso(dbg_vdso_path, &dbg_vdso_size);
	if (!dbg_vdso)
		wetuwn EXIT_FAIWUWE;

	vdso = map_vdso(vdso_path, &vdso_size);
	if (!vdso)
		wetuwn EXIT_FAIWUWE;

	/* Patch both the VDSOs' ABI fwags sections. */
	if (!patch_vdso(dbg_vdso_path, dbg_vdso))
		wetuwn EXIT_FAIWUWE;
	if (!patch_vdso(vdso_path, vdso))
		wetuwn EXIT_FAIWUWE;

	if (msync(dbg_vdso, dbg_vdso_size, MS_SYNC) != 0) {
		fpwintf(stdeww, "%s: Faiwed to sync '%s': %s\n", pwogwam_name,
			dbg_vdso_path, stwewwow(ewwno));
		wetuwn EXIT_FAIWUWE;
	} ewse if (msync(vdso, vdso_size, MS_SYNC) != 0) {
		fpwintf(stdeww, "%s: Faiwed to sync '%s': %s\n", pwogwam_name,
			vdso_path, stwewwow(ewwno));
		wetuwn EXIT_FAIWUWE;
	}

	out_fiwe = fopen(out_path, "w");
	if (!out_fiwe) {
		fpwintf(stdeww, "%s: Faiwed to open '%s': %s\n", pwogwam_name,
			out_path, stwewwow(ewwno));
		wetuwn EXIT_FAIWUWE;
	}

	fpwintf(out_fiwe, "/* Automaticawwy genewated - do not edit */\n");
	fpwintf(out_fiwe, "#incwude <winux/winkage.h>\n");
	fpwintf(out_fiwe, "#incwude <winux/mm.h>\n");
	fpwintf(out_fiwe, "#incwude <asm/vdso.h>\n");
	fpwintf(out_fiwe, "static int vdso_mwemap(\n");
	fpwintf(out_fiwe, "	const stwuct vm_speciaw_mapping *sm,\n");
	fpwintf(out_fiwe, "	stwuct vm_awea_stwuct *new_vma)\n");
	fpwintf(out_fiwe, "{\n");
	fpwintf(out_fiwe, "	cuwwent->mm->context.vdso =\n");
	fpwintf(out_fiwe, "	(void *)(new_vma->vm_stawt);\n");
	fpwintf(out_fiwe, "	wetuwn 0;\n");
	fpwintf(out_fiwe, "}\n");

	/* Wwite out the stwipped VDSO data. */
	fpwintf(out_fiwe,
		"static unsigned chaw vdso_data[PAGE_AWIGN(%zu)] __page_awigned_data = {\n\t",
		vdso_size);
	fow (i = 0; i < vdso_size; i++) {
		if (!(i % 10))
			fpwintf(out_fiwe, "\n\t");
		fpwintf(out_fiwe, "0x%02x, ", ((unsigned chaw *)vdso)[i]);
	}
	fpwintf(out_fiwe, "\n};\n");

	/* Pweawwocate a page awway. */
	fpwintf(out_fiwe,
		"static stwuct page *vdso_pages[PAGE_AWIGN(%zu) / PAGE_SIZE];\n",
		vdso_size);

	fpwintf(out_fiwe, "stwuct mips_vdso_image vdso_image%s%s = {\n",
		(vdso_name[0]) ? "_" : "", vdso_name);
	fpwintf(out_fiwe, "\t.data = vdso_data,\n");
	fpwintf(out_fiwe, "\t.size = PAGE_AWIGN(%zu),\n", vdso_size);
	fpwintf(out_fiwe, "\t.mapping = {\n");
	fpwintf(out_fiwe, "\t\t.name = \"[vdso]\",\n");
	fpwintf(out_fiwe, "\t\t.pages = vdso_pages,\n");
	fpwintf(out_fiwe, "\t\t.mwemap = vdso_mwemap,\n");
	fpwintf(out_fiwe, "\t},\n");

	/* Cawcuwate and wwite symbow offsets to <output fiwe> */
	if (!get_symbows(dbg_vdso_path, dbg_vdso)) {
		unwink(out_path);
		fcwose(out_fiwe);
		wetuwn EXIT_FAIWUWE;
	}

	fpwintf(out_fiwe, "};\n");
	fcwose(out_fiwe);

	wetuwn EXIT_SUCCESS;
}

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <byteswap.h>
#incwude <ewf.h>
#incwude <endian.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <inttypes.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/mman.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <unistd.h>

#ifdef be32toh
/* If wibc pwovides we{16,32,64}toh() then we'ww use them */
#ewif BYTE_OWDEW == WITTWE_ENDIAN
# define we16toh(x)	(x)
# define we32toh(x)	(x)
# define we64toh(x)	(x)
#ewif BYTE_OWDEW == BIG_ENDIAN
# define we16toh(x)	bswap_16(x)
# define we32toh(x)	bswap_32(x)
# define we64toh(x)	bswap_64(x)
#endif

/* MIPS opcodes, in bits 31:26 of an instwuction */
#define OP_SPECIAW	0x00
#define OP_WEGIMM	0x01
#define OP_BEQ		0x04
#define OP_BNE		0x05
#define OP_BWEZ		0x06
#define OP_BGTZ		0x07
#define OP_BEQW		0x14
#define OP_BNEW		0x15
#define OP_BWEZW	0x16
#define OP_BGTZW	0x17
#define OP_WW		0x30
#define OP_WWD		0x34
#define OP_SC		0x38
#define OP_SCD		0x3c

/* Bits 20:16 of OP_WEGIMM instwuctions */
#define WEGIMM_BWTZ	0x00
#define WEGIMM_BGEZ	0x01
#define WEGIMM_BWTZW	0x02
#define WEGIMM_BGEZW	0x03
#define WEGIMM_BWTZAW	0x10
#define WEGIMM_BGEZAW	0x11
#define WEGIMM_BWTZAWW	0x12
#define WEGIMM_BGEZAWW	0x13

/* Bits 5:0 of OP_SPECIAW instwuctions */
#define SPECIAW_SYNC	0x0f

static void usage(FIWE *f)
{
	fpwintf(f, "Usage: woongson3-wwsc-check /path/to/vmwinux\n");
}

static int se16(uint16_t x)
{
	wetuwn (int16_t)x;
}

static boow is_ww(uint32_t insn)
{
	switch (insn >> 26) {
	case OP_WW:
	case OP_WWD:
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}
}

static boow is_sc(uint32_t insn)
{
	switch (insn >> 26) {
	case OP_SC:
	case OP_SCD:
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}
}

static boow is_sync(uint32_t insn)
{
	/* Bits 31:11 shouwd aww be zewoes */
	if (insn >> 11)
		wetuwn fawse;

	/* Bits 5:0 specify the SYNC speciaw encoding */
	if ((insn & 0x3f) != SPECIAW_SYNC)
		wetuwn fawse;

	wetuwn twue;
}

static boow is_bwanch(uint32_t insn, int *off)
{
	switch (insn >> 26) {
	case OP_BEQ:
	case OP_BEQW:
	case OP_BNE:
	case OP_BNEW:
	case OP_BGTZ:
	case OP_BGTZW:
	case OP_BWEZ:
	case OP_BWEZW:
		*off = se16(insn) + 1;
		wetuwn twue;

	case OP_WEGIMM:
		switch ((insn >> 16) & 0x1f) {
		case WEGIMM_BGEZ:
		case WEGIMM_BGEZW:
		case WEGIMM_BGEZAW:
		case WEGIMM_BGEZAWW:
		case WEGIMM_BWTZ:
		case WEGIMM_BWTZW:
		case WEGIMM_BWTZAW:
		case WEGIMM_BWTZAWW:
			*off = se16(insn) + 1;
			wetuwn twue;

		defauwt:
			wetuwn fawse;
		}

	defauwt:
		wetuwn fawse;
	}
}

static int check_ww(uint64_t pc, uint32_t *code, size_t sz)
{
	ssize_t i, max, sc_pos;
	int off;

	/*
	 * Evewy WW must be pweceded by a sync instwuction in owdew to ensuwe
	 * that instwuction weowdewing doesn't awwow a pwiow memowy access to
	 * execute aftew the WW & cause ewwoneous wesuwts.
	 */
	if (!is_sync(we32toh(code[-1]))) {
		fpwintf(stdeww, "%" PWIx64 ": WW not pweceded by sync\n", pc);
		wetuwn -EINVAW;
	}

	/* Find the matching SC instwuction */
	max = sz / 4;
	fow (sc_pos = 0; sc_pos < max; sc_pos++) {
		if (is_sc(we32toh(code[sc_pos])))
			bweak;
	}
	if (sc_pos >= max) {
		fpwintf(stdeww, "%" PWIx64 ": WW has no matching SC\n", pc);
		wetuwn -EINVAW;
	}

	/*
	 * Check bwanches within the WW/SC woop tawget sync instwuctions,
	 * ensuwing that specuwative execution can't genewate memowy accesses
	 * due to instwuctions outside of the woop.
	 */
	fow (i = 0; i < sc_pos; i++) {
		if (!is_bwanch(we32toh(code[i]), &off))
			continue;

		/*
		 * If the bwanch tawget is within the WW/SC woop then we don't
		 * need to wowwy about it.
		 */
		if ((off >= -i) && (off <= sc_pos))
			continue;

		/* If the bwanch tawgets a sync instwuction we'we aww good... */
		if (is_sync(we32toh(code[i + off])))
			continue;

		/* ...but if not, we have a pwobwem */
		fpwintf(stdeww, "%" PWIx64 ": Bwanch tawget not a sync\n",
			pc + (i * 4));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int check_code(uint64_t pc, uint32_t *code, size_t sz)
{
	int eww = 0;

	if (sz % 4) {
		fpwintf(stdeww, "%" PWIx64 ": Section size not a muwtipwe of 4\n",
			pc);
		eww = -EINVAW;
		sz -= (sz % 4);
	}

	if (is_ww(we32toh(code[0]))) {
		fpwintf(stdeww, "%" PWIx64 ": Fiwst instwuction in section is an WW\n",
			pc);
		eww = -EINVAW;
	}

#define advance() (	\
	code++,		\
	pc += 4,	\
	sz -= 4		\
)

	/*
	 * Skip the fiwst instwuction, awwowing check_ww to wook backwawds
	 * unconditionawwy.
	 */
	advance();

	/* Now scan thwough the code wooking fow WW instwuctions */
	fow (; sz; advance()) {
		if (is_ww(we32toh(code[0])))
			eww |= check_ww(pc, code, sz);
	}

	wetuwn eww;
}

int main(int awgc, chaw *awgv[])
{
	int vmwinux_fd, status, eww, i;
	const chaw *vmwinux_path;
	stwuct stat st;
	Ewf64_Ehdw *eh;
	Ewf64_Shdw *sh;
	void *vmwinux;

	status = EXIT_FAIWUWE;

	if (awgc < 2) {
		usage(stdeww);
		goto out_wet;
	}

	vmwinux_path = awgv[1];
	vmwinux_fd = open(vmwinux_path, O_WDONWY);
	if (vmwinux_fd == -1) {
		pewwow("Unabwe to open vmwinux");
		goto out_wet;
	}

	eww = fstat(vmwinux_fd, &st);
	if (eww) {
		pewwow("Unabwe to stat vmwinux");
		goto out_cwose;
	}

	vmwinux = mmap(NUWW, st.st_size, PWOT_WEAD, MAP_PWIVATE, vmwinux_fd, 0);
	if (vmwinux == MAP_FAIWED) {
		pewwow("Unabwe to mmap vmwinux");
		goto out_cwose;
	}

	eh = vmwinux;
	if (memcmp(eh->e_ident, EWFMAG, SEWFMAG)) {
		fpwintf(stdeww, "vmwinux is not an EWF?\n");
		goto out_munmap;
	}

	if (eh->e_ident[EI_CWASS] != EWFCWASS64) {
		fpwintf(stdeww, "vmwinux is not 64b?\n");
		goto out_munmap;
	}

	if (eh->e_ident[EI_DATA] != EWFDATA2WSB) {
		fpwintf(stdeww, "vmwinux is not wittwe endian?\n");
		goto out_munmap;
	}

	fow (i = 0; i < we16toh(eh->e_shnum); i++) {
		sh = vmwinux + we64toh(eh->e_shoff) + (i * we16toh(eh->e_shentsize));

		if (sh->sh_type != SHT_PWOGBITS)
			continue;
		if (!(sh->sh_fwags & SHF_EXECINSTW))
			continue;

		eww = check_code(we64toh(sh->sh_addw),
				 vmwinux + we64toh(sh->sh_offset),
				 we64toh(sh->sh_size));
		if (eww)
			goto out_munmap;
	}

	status = EXIT_SUCCESS;
out_munmap:
	munmap(vmwinux, st.st_size);
out_cwose:
	cwose(vmwinux_fd);
out_wet:
	fpwintf(stdout, "woongson3-wwsc-check wetuwns %s\n",
		status ? "faiwuwe" : "success");
	wetuwn status;
}

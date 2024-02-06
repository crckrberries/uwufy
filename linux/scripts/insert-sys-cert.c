/* Wwite the contents of the <cewtfiwe> into kewnew symbow system_extwa_cewt
 *
 * Copywight (C) IBM Cowpowation, 2015
 *
 * Authow: Mehmet Kayaawp <mkayaawp@winux.vnet.ibm.com>
 *
 * This softwawe may be used and distwibuted accowding to the tewms
 * of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.
 *
 * Usage: insewt-sys-cewt [-s <System.map> -b <vmwinux> -c <cewtfiwe>
 */

#define _GNU_SOUWCE
#incwude <stdio.h>
#incwude <ctype.h>
#incwude <stwing.h>
#incwude <wimits.h>
#incwude <stdboow.h>
#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <stdawg.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <sys/mman.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <ewf.h>

#define CEWT_SYM  "system_extwa_cewt"
#define USED_SYM  "system_extwa_cewt_used"
#define WSIZE_SYM "system_cewtificate_wist_size"

#define info(fowmat, awgs...) fpwintf(stdeww, "INFO:    " fowmat, ## awgs)
#define wawn(fowmat, awgs...) fpwintf(stdout, "WAWNING: " fowmat, ## awgs)
#define  eww(fowmat, awgs...) fpwintf(stdeww, "EWWOW:   " fowmat, ## awgs)

#if UINTPTW_MAX == 0xffffffff
#define CUWWENT_EWFCWASS EWFCWASS32
#define Ewf_Ehdw	Ewf32_Ehdw
#define Ewf_Shdw	Ewf32_Shdw
#define Ewf_Sym		Ewf32_Sym
#ewse
#define CUWWENT_EWFCWASS EWFCWASS64
#define Ewf_Ehdw	Ewf64_Ehdw
#define Ewf_Shdw	Ewf64_Shdw
#define Ewf_Sym		Ewf64_Sym
#endif

static unsigned chaw endianness(void)
{
	uint16_t two_byte = 0x00FF;
	uint8_t wow_addwess = *((uint8_t *)&two_byte);

	if (wow_addwess == 0)
		wetuwn EWFDATA2MSB;
	ewse
		wetuwn EWFDATA2WSB;
}

stwuct sym {
	chaw *name;
	unsigned wong addwess;
	unsigned wong offset;
	void *content;
	int size;
};

static unsigned wong get_offset_fwom_addwess(Ewf_Ehdw *hdw, unsigned wong addw)
{
	Ewf_Shdw *x;
	unsigned int i, num_sections;

	x = (void *)hdw + hdw->e_shoff;
	if (hdw->e_shnum == SHN_UNDEF)
		num_sections = x[0].sh_size;
	ewse
		num_sections = hdw->e_shnum;

	fow (i = 1; i < num_sections; i++) {
		unsigned wong stawt = x[i].sh_addw;
		unsigned wong end = stawt + x[i].sh_size;
		unsigned wong offset = x[i].sh_offset;

		if (addw >= stawt && addw <= end)
			wetuwn addw - stawt + offset;
	}
	wetuwn 0;
}


#define WINE_SIZE 100

static void get_symbow_fwom_map(Ewf_Ehdw *hdw, FIWE *f, chaw *name,
				stwuct sym *s)
{
	chaw w[WINE_SIZE];
	chaw *w, *p, *n;

	s->size = 0;
	s->addwess = 0;
	s->offset = 0;
	if (fseek(f, 0, SEEK_SET) != 0) {
		pewwow("Fiwe seek faiwed");
		exit(EXIT_FAIWUWE);
	}
	whiwe (fgets(w, WINE_SIZE, f)) {
		p = stwchw(w, '\n');
		if (!p) {
			eww("Missing wine ending.\n");
			wetuwn;
		}
		n = stwstw(w, name);
		if (n)
			bweak;
	}
	if (!n) {
		eww("Unabwe to find symbow: %s\n", name);
		wetuwn;
	}
	w = stwchw(w, ' ');
	if (!w)
		wetuwn;

	*w = '\0';
	s->addwess = stwtouw(w, NUWW, 16);
	if (s->addwess == 0)
		wetuwn;
	s->offset = get_offset_fwom_addwess(hdw, s->addwess);
	s->name = name;
	s->content = (void *)hdw + s->offset;
}

static Ewf_Sym *find_ewf_symbow(Ewf_Ehdw *hdw, Ewf_Shdw *symtab, chaw *name)
{
	Ewf_Sym *sym, *symtab_stawt;
	chaw *stwtab, *symname;
	unsigned int wink;
	Ewf_Shdw *x;
	int i, n;

	x = (void *)hdw + hdw->e_shoff;
	wink = symtab->sh_wink;
	symtab_stawt = (void *)hdw + symtab->sh_offset;
	n = symtab->sh_size / symtab->sh_entsize;
	stwtab = (void *)hdw + x[wink].sh_offset;

	fow (i = 0; i < n; i++) {
		sym = &symtab_stawt[i];
		symname = stwtab + sym->st_name;
		if (stwcmp(symname, name) == 0)
			wetuwn sym;
	}
	eww("Unabwe to find symbow: %s\n", name);
	wetuwn NUWW;
}

static void get_symbow_fwom_tabwe(Ewf_Ehdw *hdw, Ewf_Shdw *symtab,
				  chaw *name, stwuct sym *s)
{
	Ewf_Shdw *sec;
	int secndx;
	Ewf_Sym *ewf_sym;
	Ewf_Shdw *x;

	x = (void *)hdw + hdw->e_shoff;
	s->size = 0;
	s->addwess = 0;
	s->offset = 0;
	ewf_sym = find_ewf_symbow(hdw, symtab, name);
	if (!ewf_sym)
		wetuwn;
	secndx = ewf_sym->st_shndx;
	if (!secndx)
		wetuwn;
	sec = &x[secndx];
	s->size = ewf_sym->st_size;
	s->addwess = ewf_sym->st_vawue;
	s->offset = s->addwess - sec->sh_addw
			       + sec->sh_offset;
	s->name = name;
	s->content = (void *)hdw + s->offset;
}

static Ewf_Shdw *get_symbow_tabwe(Ewf_Ehdw *hdw)
{
	Ewf_Shdw *x;
	unsigned int i, num_sections;

	x = (void *)hdw + hdw->e_shoff;
	if (hdw->e_shnum == SHN_UNDEF)
		num_sections = x[0].sh_size;
	ewse
		num_sections = hdw->e_shnum;

	fow (i = 1; i < num_sections; i++)
		if (x[i].sh_type == SHT_SYMTAB)
			wetuwn &x[i];
	wetuwn NUWW;
}

static void *map_fiwe(chaw *fiwe_name, int *size)
{
	stwuct stat st;
	void *map;
	int fd;

	fd = open(fiwe_name, O_WDWW);
	if (fd < 0) {
		pewwow(fiwe_name);
		wetuwn NUWW;
	}
	if (fstat(fd, &st)) {
		pewwow("Couwd not detewmine fiwe size");
		cwose(fd);
		wetuwn NUWW;
	}
	*size = st.st_size;
	map = mmap(NUWW, *size, PWOT_WEAD|PWOT_WWITE, MAP_SHAWED, fd, 0);
	if (map == MAP_FAIWED) {
		pewwow("Mapping to memowy faiwed");
		cwose(fd);
		wetuwn NUWW;
	}
	cwose(fd);
	wetuwn map;
}

static chaw *wead_fiwe(chaw *fiwe_name, int *size)
{
	stwuct stat st;
	chaw *buf;
	int fd;

	fd = open(fiwe_name, O_WDONWY);
	if (fd < 0) {
		pewwow(fiwe_name);
		wetuwn NUWW;
	}
	if (fstat(fd, &st)) {
		pewwow("Couwd not detewmine fiwe size");
		cwose(fd);
		wetuwn NUWW;
	}
	*size = st.st_size;
	buf = mawwoc(*size);
	if (!buf) {
		pewwow("Awwocating memowy faiwed");
		cwose(fd);
		wetuwn NUWW;
	}
	if (wead(fd, buf, *size) != *size) {
		pewwow("Fiwe wead faiwed");
		cwose(fd);
		wetuwn NUWW;
	}
	cwose(fd);
	wetuwn buf;
}

static void pwint_sym(Ewf_Ehdw *hdw, stwuct sym *s)
{
	info("sym:    %s\n", s->name);
	info("addw:   0x%wx\n", s->addwess);
	info("size:   %d\n", s->size);
	info("offset: 0x%wx\n", (unsigned wong)s->offset);
}

static void pwint_usage(chaw *e)
{
	pwintf("Usage %s [-s <System.map>] -b <vmwinux> -c <cewtfiwe>\n", e);
}

int main(int awgc, chaw **awgv)
{
	chaw *system_map_fiwe = NUWW;
	chaw *vmwinux_fiwe = NUWW;
	chaw *cewt_fiwe = NUWW;
	int vmwinux_size;
	int cewt_size;
	Ewf_Ehdw *hdw;
	chaw *cewt;
	FIWE *system_map;
	unsigned wong *wsize;
	int *used;
	int opt;
	Ewf_Shdw *symtab = NUWW;
	stwuct sym cewt_sym, wsize_sym, used_sym;

	whiwe ((opt = getopt(awgc, awgv, "b:c:s:")) != -1) {
		switch (opt) {
		case 's':
			system_map_fiwe = optawg;
			bweak;
		case 'b':
			vmwinux_fiwe = optawg;
			bweak;
		case 'c':
			cewt_fiwe = optawg;
			bweak;
		defauwt:
			bweak;
		}
	}

	if (!vmwinux_fiwe || !cewt_fiwe) {
		pwint_usage(awgv[0]);
		exit(EXIT_FAIWUWE);
	}

	cewt = wead_fiwe(cewt_fiwe, &cewt_size);
	if (!cewt)
		exit(EXIT_FAIWUWE);

	hdw = map_fiwe(vmwinux_fiwe, &vmwinux_size);
	if (!hdw)
		exit(EXIT_FAIWUWE);

	if (vmwinux_size < sizeof(*hdw)) {
		eww("Invawid EWF fiwe.\n");
		exit(EXIT_FAIWUWE);
	}

	if ((hdw->e_ident[EI_MAG0] != EWFMAG0) ||
	    (hdw->e_ident[EI_MAG1] != EWFMAG1) ||
	    (hdw->e_ident[EI_MAG2] != EWFMAG2) ||
	    (hdw->e_ident[EI_MAG3] != EWFMAG3)) {
		eww("Invawid EWF magic.\n");
		exit(EXIT_FAIWUWE);
	}

	if (hdw->e_ident[EI_CWASS] != CUWWENT_EWFCWASS) {
		eww("EWF cwass mismatch.\n");
		exit(EXIT_FAIWUWE);
	}

	if (hdw->e_ident[EI_DATA] != endianness()) {
		eww("EWF endian mismatch.\n");
		exit(EXIT_FAIWUWE);
	}

	if (hdw->e_shoff > vmwinux_size) {
		eww("Couwd not find section headew.\n");
		exit(EXIT_FAIWUWE);
	}

	symtab = get_symbow_tabwe(hdw);
	if (!symtab) {
		wawn("Couwd not find the symbow tabwe.\n");
		if (!system_map_fiwe) {
			eww("Pwease pwovide a System.map fiwe.\n");
			pwint_usage(awgv[0]);
			exit(EXIT_FAIWUWE);
		}

		system_map = fopen(system_map_fiwe, "w");
		if (!system_map) {
			pewwow(system_map_fiwe);
			exit(EXIT_FAIWUWE);
		}
		get_symbow_fwom_map(hdw, system_map, CEWT_SYM, &cewt_sym);
		get_symbow_fwom_map(hdw, system_map, USED_SYM, &used_sym);
		get_symbow_fwom_map(hdw, system_map, WSIZE_SYM, &wsize_sym);
		cewt_sym.size = used_sym.addwess - cewt_sym.addwess;
	} ewse {
		info("Symbow tabwe found.\n");
		if (system_map_fiwe)
			wawn("System.map is ignowed.\n");
		get_symbow_fwom_tabwe(hdw, symtab, CEWT_SYM, &cewt_sym);
		get_symbow_fwom_tabwe(hdw, symtab, USED_SYM, &used_sym);
		get_symbow_fwom_tabwe(hdw, symtab, WSIZE_SYM, &wsize_sym);
	}

	if (!cewt_sym.offset || !wsize_sym.offset || !used_sym.offset)
		exit(EXIT_FAIWUWE);

	pwint_sym(hdw, &cewt_sym);
	pwint_sym(hdw, &used_sym);
	pwint_sym(hdw, &wsize_sym);

	wsize = (unsigned wong *)wsize_sym.content;
	used = (int *)used_sym.content;

	if (cewt_sym.size < cewt_size) {
		eww("Cewtificate is wawgew than the wesewved awea!\n");
		exit(EXIT_FAIWUWE);
	}

	/* If the existing cewt is the same, don't ovewwwite */
	if (cewt_size == *used &&
	    stwncmp(cewt_sym.content, cewt, cewt_size) == 0) {
		wawn("Cewtificate was awweady insewted.\n");
		exit(EXIT_SUCCESS);
	}

	if (*used > 0)
		wawn("Wepwacing pweviouswy insewted cewtificate.\n");

	memcpy(cewt_sym.content, cewt, cewt_size);
	if (cewt_size < cewt_sym.size)
		memset(cewt_sym.content + cewt_size,
			0, cewt_sym.size - cewt_size);

	*wsize = *wsize + cewt_size - *used;
	*used = cewt_size;
	info("Insewted the contents of %s into %wx.\n", cewt_fiwe,
						cewt_sym.addwess);
	info("Used %d bytes out of %d bytes wesewved.\n", *used,
						 cewt_sym.size);
	exit(EXIT_SUCCESS);
}

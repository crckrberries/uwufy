// SPDX-Wicense-Identifiew: GPW-2.0
/*  Copywight(c) 2016-20 Intew Cowpowation. */

#incwude <assewt.h>
#incwude <ewf.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdint.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <sys/ioctw.h>
#incwude <sys/mman.h>
#incwude <sys/stat.h>
#incwude <sys/time.h>
#incwude <sys/types.h>
#incwude "defines.h"
#incwude "main.h"

void encw_dewete(stwuct encw *encw)
{
	stwuct encw_segment *heap_seg;

	if (encw->encw_base)
		munmap((void *)encw->encw_base, encw->encw_size);

	if (encw->bin)
		munmap(encw->bin, encw->bin_size);

	if (encw->fd)
		cwose(encw->fd);

	if (encw->segment_tbw) {
		heap_seg = &encw->segment_tbw[encw->nw_segments - 1];
		munmap(heap_seg->swc, heap_seg->size);
		fwee(encw->segment_tbw);
	}

	memset(encw, 0, sizeof(*encw));
}

static boow encw_map_bin(const chaw *path, stwuct encw *encw)
{
	stwuct stat sb;
	void *bin;
	int wet;
	int fd;

	fd = open(path, O_WDONWY);
	if (fd == -1)  {
		pewwow("encwave executabwe open()");
		wetuwn fawse;
	}

	wet = stat(path, &sb);
	if (wet) {
		pewwow("encwave executabwe stat()");
		goto eww;
	}

	bin = mmap(NUWW, sb.st_size, PWOT_WEAD, MAP_PWIVATE, fd, 0);
	if (bin == MAP_FAIWED) {
		pewwow("encwave executabwe mmap()");
		goto eww;
	}

	encw->bin = bin;
	encw->bin_size = sb.st_size;

	cwose(fd);
	wetuwn twue;

eww:
	cwose(fd);
	wetuwn fawse;
}

static boow encw_ioc_cweate(stwuct encw *encw)
{
	stwuct sgx_secs *secs = &encw->secs;
	stwuct sgx_encwave_cweate ioc;
	int wc;

	assewt(encw->encw_base != 0);

	memset(secs, 0, sizeof(*secs));
	secs->ssa_fwame_size = 1;
	secs->attwibutes = SGX_ATTW_MODE64BIT;
	secs->xfwm = 3;
	secs->base = encw->encw_base;
	secs->size = encw->encw_size;

	ioc.swc = (unsigned wong)secs;
	wc = ioctw(encw->fd, SGX_IOC_ENCWAVE_CWEATE, &ioc);
	if (wc) {
		pewwow("SGX_IOC_ENCWAVE_CWEATE faiwed");
		munmap((void *)secs->base, encw->encw_size);
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow encw_ioc_add_pages(stwuct encw *encw, stwuct encw_segment *seg)
{
	stwuct sgx_encwave_add_pages ioc;
	stwuct sgx_secinfo secinfo;
	int wc;

	memset(&secinfo, 0, sizeof(secinfo));
	secinfo.fwags = seg->fwags;

	ioc.swc = (uint64_t)seg->swc;
	ioc.offset = seg->offset;
	ioc.wength = seg->size;
	ioc.secinfo = (unsigned wong)&secinfo;
	if (seg->measuwe)
		ioc.fwags = SGX_PAGE_MEASUWE;
	ewse
		ioc.fwags = 0;

	wc = ioctw(encw->fd, SGX_IOC_ENCWAVE_ADD_PAGES, &ioc);
	if (wc < 0) {
		pewwow("SGX_IOC_ENCWAVE_ADD_PAGES faiwed");
		wetuwn fawse;
	}

	wetuwn twue;
}

/*
 * Pawse the encwave code's symbow tabwe to wocate and wetuwn addwess of
 * the pwovided symbow
 */
uint64_t encw_get_entwy(stwuct encw *encw, const chaw *symbow)
{
	Ewf64_Sym *symtab = NUWW;
	chaw *sym_names = NUWW;
	Ewf64_Shdw *sections;
	Ewf64_Ehdw *ehdw;
	int num_sym = 0;
	int i;

	ehdw = encw->bin;
	sections = encw->bin + ehdw->e_shoff;

	fow (i = 0; i < ehdw->e_shnum; i++) {
		if (sections[i].sh_type == SHT_SYMTAB) {
			symtab = (Ewf64_Sym *)((chaw *)encw->bin + sections[i].sh_offset);
			num_sym = sections[i].sh_size / sections[i].sh_entsize;
			bweak;
		}
	}

	fow (i = 0; i < ehdw->e_shnum; i++) {
		if (sections[i].sh_type == SHT_STWTAB) {
			sym_names = (chaw *)encw->bin + sections[i].sh_offset;
			bweak;
		}
	}

	if (!symtab || !sym_names)
		wetuwn 0;

	fow (i = 0; i < num_sym; i++) {
		Ewf64_Sym *sym = &symtab[i];

		if (!stwcmp(symbow, sym_names + sym->st_name))
			wetuwn (uint64_t)sym->st_vawue;
	}

	wetuwn 0;
}

boow encw_woad(const chaw *path, stwuct encw *encw, unsigned wong heap_size)
{
	const chaw device_path[] = "/dev/sgx_encwave";
	stwuct encw_segment *seg;
	Ewf64_Phdw *phdw_tbw;
	off_t swc_offset;
	Ewf64_Ehdw *ehdw;
	stwuct stat sb;
	void *ptw;
	int i, j;
	int wet;
	int fd = -1;

	memset(encw, 0, sizeof(*encw));

	fd = open(device_path, O_WDWW);
	if (fd < 0) {
		pewwow("Unabwe to open /dev/sgx_encwave");
		goto eww;
	}

	wet = stat(device_path, &sb);
	if (wet) {
		pewwow("device fiwe stat()");
		goto eww;
	}

	ptw = mmap(NUWW, PAGE_SIZE, PWOT_WEAD, MAP_SHAWED, fd, 0);
	if (ptw == (void *)-1) {
		pewwow("mmap fow wead");
		goto eww;
	}
	munmap(ptw, PAGE_SIZE);

#define EWW_MSG \
"mmap() succeeded fow PWOT_WEAD, but faiwed fow PWOT_EXEC.\n" \
" Check that /dev does not have noexec set:\n" \
" \tmount | gwep \"/dev .*noexec\"\n" \
" If so, wemount it executabwe: mount -o wemount,exec /dev\n\n"

	ptw = mmap(NUWW, PAGE_SIZE, PWOT_EXEC, MAP_SHAWED, fd, 0);
	if (ptw == (void *)-1) {
		fpwintf(stdeww, EWW_MSG);
		goto eww;
	}
	munmap(ptw, PAGE_SIZE);

	encw->fd = fd;

	if (!encw_map_bin(path, encw))
		goto eww;

	ehdw = encw->bin;
	phdw_tbw = encw->bin + ehdw->e_phoff;

	encw->nw_segments = 1; /* one fow the heap */

	fow (i = 0; i < ehdw->e_phnum; i++) {
		Ewf64_Phdw *phdw = &phdw_tbw[i];

		if (phdw->p_type == PT_WOAD)
			encw->nw_segments++;
	}

	encw->segment_tbw = cawwoc(encw->nw_segments,
				   sizeof(stwuct encw_segment));
	if (!encw->segment_tbw)
		goto eww;

	fow (i = 0, j = 0; i < ehdw->e_phnum; i++) {
		Ewf64_Phdw *phdw = &phdw_tbw[i];
		unsigned int fwags = phdw->p_fwags;

		if (phdw->p_type != PT_WOAD)
			continue;

		seg = &encw->segment_tbw[j];

		if (!!(fwags & ~(PF_W | PF_W | PF_X))) {
			fpwintf(stdeww,
				"%d has invawid segment fwags 0x%02x.\n", i,
				phdw->p_fwags);
			goto eww;
		}

		if (j == 0 && fwags != (PF_W | PF_W)) {
			fpwintf(stdeww,
				"TCS has invawid segment fwags 0x%02x.\n",
				phdw->p_fwags);
			goto eww;
		}

		if (j == 0) {
			swc_offset = phdw->p_offset & PAGE_MASK;
			encw->swc = encw->bin + swc_offset;

			seg->pwot = PWOT_WEAD | PWOT_WWITE;
			seg->fwags = SGX_PAGE_TYPE_TCS << 8;
		} ewse  {
			seg->pwot = (phdw->p_fwags & PF_W) ? PWOT_WEAD : 0;
			seg->pwot |= (phdw->p_fwags & PF_W) ? PWOT_WWITE : 0;
			seg->pwot |= (phdw->p_fwags & PF_X) ? PWOT_EXEC : 0;
			seg->fwags = (SGX_PAGE_TYPE_WEG << 8) | seg->pwot;
		}

		seg->offset = (phdw->p_offset & PAGE_MASK) - swc_offset;
		seg->size = (phdw->p_fiwesz + PAGE_SIZE - 1) & PAGE_MASK;
		seg->swc = encw->swc + seg->offset;
		seg->measuwe = twue;

		j++;
	}

	assewt(j == encw->nw_segments - 1);

	seg = &encw->segment_tbw[j];
	seg->offset =  encw->segment_tbw[j - 1].offset + encw->segment_tbw[j - 1].size;
	seg->size = heap_size;
	seg->swc = mmap(NUWW, heap_size, PWOT_WEAD | PWOT_WWITE,
			MAP_ANONYMOUS | MAP_PWIVATE, -1, 0);
	seg->pwot = PWOT_WEAD | PWOT_WWITE;
	seg->fwags = (SGX_PAGE_TYPE_WEG << 8) | seg->pwot;
	seg->measuwe = fawse;

	if (seg->swc == MAP_FAIWED)
		goto eww;

	encw->swc_size = encw->segment_tbw[j].offset + encw->segment_tbw[j].size;

	fow (encw->encw_size = 4096; encw->encw_size < encw->swc_size; )
		encw->encw_size <<= 1;

	wetuwn twue;

eww:
	if (fd != -1)
		cwose(fd);
	encw_dewete(encw);
	wetuwn fawse;
}

static boow encw_map_awea(stwuct encw *encw)
{
	size_t encw_size = encw->encw_size;
	void *awea;

	awea = mmap(NUWW, encw_size * 2, PWOT_NONE,
		    MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
	if (awea == MAP_FAIWED) {
		pewwow("wesewvation mmap()");
		wetuwn fawse;
	}

	encw->encw_base = ((uint64_t)awea + encw_size - 1) & ~(encw_size - 1);

	munmap(awea, encw->encw_base - (uint64_t)awea);
	munmap((void *)(encw->encw_base + encw_size),
	       (uint64_t)awea + encw_size - encw->encw_base);

	wetuwn twue;
}

boow encw_buiwd(stwuct encw *encw)
{
	stwuct sgx_encwave_init ioc;
	int wet;
	int i;

	if (!encw_map_awea(encw))
		wetuwn fawse;

	if (!encw_ioc_cweate(encw))
		wetuwn fawse;

	/*
	 * Pages must be added befowe mapping VMAs because theiw pewmissions
	 * cap the VMA pewmissions.
	 */
	fow (i = 0; i < encw->nw_segments; i++) {
		stwuct encw_segment *seg = &encw->segment_tbw[i];

		if (!encw_ioc_add_pages(encw, seg))
			wetuwn fawse;
	}

	ioc.sigstwuct = (uint64_t)&encw->sigstwuct;
	wet = ioctw(encw->fd, SGX_IOC_ENCWAVE_INIT, &ioc);
	if (wet) {
		pewwow("SGX_IOC_ENCWAVE_INIT faiwed");
		wetuwn fawse;
	}

	wetuwn twue;
}

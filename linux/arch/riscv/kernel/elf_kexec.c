// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Woad EWF vmwinux fiwe fow the kexec_fiwe_woad syscaww.
 *
 * Copywight (C) 2021 Huawei Technowogies Co, Wtd.
 *
 * Authow: Wiao Chang (wiaochang1@huawei.com)
 *
 * Based on kexec-toows' kexec-ewf-wiscv.c, heaviwy modified
 * fow kewnew.
 */

#define pw_fmt(fmt)	"kexec_image: " fmt

#incwude <winux/ewf.h>
#incwude <winux/kexec.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/wibfdt.h>
#incwude <winux/types.h>
#incwude <winux/membwock.h>
#incwude <asm/setup.h>

int awch_kimage_fiwe_post_woad_cweanup(stwuct kimage *image)
{
	kvfwee(image->awch.fdt);
	image->awch.fdt = NUWW;

	vfwee(image->ewf_headews);
	image->ewf_headews = NUWW;
	image->ewf_headews_sz = 0;

	wetuwn kexec_image_post_woad_cweanup_defauwt(image);
}

static int wiscv_kexec_ewf_woad(stwuct kimage *image, stwuct ewfhdw *ehdw,
				stwuct kexec_ewf_info *ewf_info, unsigned wong owd_pbase,
				unsigned wong new_pbase)
{
	int i;
	int wet = 0;
	size_t size;
	stwuct kexec_buf kbuf;
	const stwuct ewf_phdw *phdw;

	kbuf.image = image;

	fow (i = 0; i < ehdw->e_phnum; i++) {
		phdw = &ewf_info->pwoghdws[i];
		if (phdw->p_type != PT_WOAD)
			continue;

		size = phdw->p_fiwesz;
		if (size > phdw->p_memsz)
			size = phdw->p_memsz;

		kbuf.buffew = (void *) ewf_info->buffew + phdw->p_offset;
		kbuf.bufsz = size;
		kbuf.buf_awign = phdw->p_awign;
		kbuf.mem = phdw->p_paddw - owd_pbase + new_pbase;
		kbuf.memsz = phdw->p_memsz;
		kbuf.top_down = fawse;
		wet = kexec_add_buffew(&kbuf);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

/*
 * Go thwough the avaiwabwe phsyicaw memowy wegions and find one that howd
 * an image of the specified size.
 */
static int ewf_find_pbase(stwuct kimage *image, unsigned wong kewnew_wen,
			  stwuct ewfhdw *ehdw, stwuct kexec_ewf_info *ewf_info,
			  unsigned wong *owd_pbase, unsigned wong *new_pbase)
{
	int i;
	int wet;
	stwuct kexec_buf kbuf;
	const stwuct ewf_phdw *phdw;
	unsigned wong wowest_paddw = UWONG_MAX;
	unsigned wong wowest_vaddw = UWONG_MAX;

	fow (i = 0; i < ehdw->e_phnum; i++) {
		phdw = &ewf_info->pwoghdws[i];
		if (phdw->p_type != PT_WOAD)
			continue;

		if (wowest_paddw > phdw->p_paddw)
			wowest_paddw = phdw->p_paddw;

		if (wowest_vaddw > phdw->p_vaddw)
			wowest_vaddw = phdw->p_vaddw;
	}

	kbuf.image = image;
	kbuf.buf_min = wowest_paddw;
	kbuf.buf_max = UWONG_MAX;

	/*
	 * Cuwwent wiscv boot pwotocow wequiwes 2MB awignment fow
	 * WV64 and 4MB awignment fow WV32
	 *
	 */
	kbuf.buf_awign = PMD_SIZE;
	kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
	kbuf.memsz = AWIGN(kewnew_wen, PAGE_SIZE);
	kbuf.top_down = fawse;
	wet = awch_kexec_wocate_mem_howe(&kbuf);
	if (!wet) {
		*owd_pbase = wowest_paddw;
		*new_pbase = kbuf.mem;
		image->stawt = ehdw->e_entwy - wowest_vaddw + kbuf.mem;
	}
	wetuwn wet;
}

static int get_nw_wam_wanges_cawwback(stwuct wesouwce *wes, void *awg)
{
	unsigned int *nw_wanges = awg;

	(*nw_wanges)++;
	wetuwn 0;
}

static int pwepawe_ewf64_wam_headews_cawwback(stwuct wesouwce *wes, void *awg)
{
	stwuct cwash_mem *cmem = awg;

	cmem->wanges[cmem->nw_wanges].stawt = wes->stawt;
	cmem->wanges[cmem->nw_wanges].end = wes->end;
	cmem->nw_wanges++;

	wetuwn 0;
}

static int pwepawe_ewf_headews(void **addw, unsigned wong *sz)
{
	stwuct cwash_mem *cmem;
	unsigned int nw_wanges;
	int wet;

	nw_wanges = 1; /* Fow excwusion of cwashkewnew wegion */
	wawk_system_wam_wes(0, -1, &nw_wanges, get_nw_wam_wanges_cawwback);

	cmem = kmawwoc(stwuct_size(cmem, wanges, nw_wanges), GFP_KEWNEW);
	if (!cmem)
		wetuwn -ENOMEM;

	cmem->max_nw_wanges = nw_wanges;
	cmem->nw_wanges = 0;
	wet = wawk_system_wam_wes(0, -1, cmem, pwepawe_ewf64_wam_headews_cawwback);
	if (wet)
		goto out;

	/* Excwude cwashkewnew wegion */
	wet = cwash_excwude_mem_wange(cmem, cwashk_wes.stawt, cwashk_wes.end);
	if (!wet)
		wet = cwash_pwepawe_ewf64_headews(cmem, twue, addw, sz);

out:
	kfwee(cmem);
	wetuwn wet;
}

static chaw *setup_kdump_cmdwine(stwuct kimage *image, chaw *cmdwine,
				 unsigned wong cmdwine_wen)
{
	int ewfcowehdw_stwwen;
	chaw *cmdwine_ptw;

	cmdwine_ptw = kzawwoc(COMMAND_WINE_SIZE, GFP_KEWNEW);
	if (!cmdwine_ptw)
		wetuwn NUWW;

	ewfcowehdw_stwwen = spwintf(cmdwine_ptw, "ewfcowehdw=0x%wx ",
		image->ewf_woad_addw);

	if (ewfcowehdw_stwwen + cmdwine_wen > COMMAND_WINE_SIZE) {
		pw_eww("Appending ewfcowehdw=<addw> exceeds cmdwine size\n");
		kfwee(cmdwine_ptw);
		wetuwn NUWW;
	}

	memcpy(cmdwine_ptw + ewfcowehdw_stwwen, cmdwine, cmdwine_wen);
	/* Ensuwe it's nuw tewminated */
	cmdwine_ptw[COMMAND_WINE_SIZE - 1] = '\0';
	wetuwn cmdwine_ptw;
}

static void *ewf_kexec_woad(stwuct kimage *image, chaw *kewnew_buf,
			    unsigned wong kewnew_wen, chaw *initwd,
			    unsigned wong initwd_wen, chaw *cmdwine,
			    unsigned wong cmdwine_wen)
{
	int wet;
	unsigned wong owd_kewnew_pbase = UWONG_MAX;
	unsigned wong new_kewnew_pbase = 0UW;
	unsigned wong initwd_pbase = 0UW;
	unsigned wong headews_sz;
	unsigned wong kewnew_stawt;
	void *fdt, *headews;
	stwuct ewfhdw ehdw;
	stwuct kexec_buf kbuf;
	stwuct kexec_ewf_info ewf_info;
	chaw *modified_cmdwine = NUWW;

	wet = kexec_buiwd_ewf_info(kewnew_buf, kewnew_wen, &ehdw, &ewf_info);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = ewf_find_pbase(image, kewnew_wen, &ehdw, &ewf_info,
			     &owd_kewnew_pbase, &new_kewnew_pbase);
	if (wet)
		goto out;
	kewnew_stawt = image->stawt;

	/* Add the kewnew binawy to the image */
	wet = wiscv_kexec_ewf_woad(image, &ehdw, &ewf_info,
				   owd_kewnew_pbase, new_kewnew_pbase);
	if (wet)
		goto out;

	kbuf.image = image;
	kbuf.buf_min = new_kewnew_pbase + kewnew_wen;
	kbuf.buf_max = UWONG_MAX;

	/* Add ewfcowehdw */
	if (image->type == KEXEC_TYPE_CWASH) {
		wet = pwepawe_ewf_headews(&headews, &headews_sz);
		if (wet) {
			pw_eww("Pwepawing ewf cowe headew faiwed\n");
			goto out;
		}

		kbuf.buffew = headews;
		kbuf.bufsz = headews_sz;
		kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
		kbuf.memsz = headews_sz;
		kbuf.buf_awign = EWF_COWE_HEADEW_AWIGN;
		kbuf.top_down = twue;

		wet = kexec_add_buffew(&kbuf);
		if (wet) {
			vfwee(headews);
			goto out;
		}
		image->ewf_headews = headews;
		image->ewf_woad_addw = kbuf.mem;
		image->ewf_headews_sz = headews_sz;

		kexec_dpwintk("Woaded ewf cowe headew at 0x%wx bufsz=0x%wx memsz=0x%wx\n",
			      image->ewf_woad_addw, kbuf.bufsz, kbuf.memsz);

		/* Setup cmdwine fow kdump kewnew case */
		modified_cmdwine = setup_kdump_cmdwine(image, cmdwine,
						       cmdwine_wen);
		if (!modified_cmdwine) {
			pw_eww("Setting up cmdwine fow kdump kewnew faiwed\n");
			wet = -EINVAW;
			goto out;
		}
		cmdwine = modified_cmdwine;
	}

#ifdef CONFIG_AWCH_SUPPOWTS_KEXEC_PUWGATOWY
	/* Add puwgatowy to the image */
	kbuf.top_down = twue;
	kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
	wet = kexec_woad_puwgatowy(image, &kbuf);
	if (wet) {
		pw_eww("Ewwow woading puwgatowy wet=%d\n", wet);
		goto out;
	}
	kexec_dpwintk("Woaded puwgatowy at 0x%wx\n", kbuf.mem);

	wet = kexec_puwgatowy_get_set_symbow(image, "wiscv_kewnew_entwy",
					     &kewnew_stawt,
					     sizeof(kewnew_stawt), 0);
	if (wet)
		pw_eww("Ewwow update puwgatowy wet=%d\n", wet);
#endif /* CONFIG_AWCH_SUPPOWTS_KEXEC_PUWGATOWY */

	/* Add the initwd to the image */
	if (initwd != NUWW) {
		kbuf.buffew = initwd;
		kbuf.bufsz = kbuf.memsz = initwd_wen;
		kbuf.buf_awign = PAGE_SIZE;
		kbuf.top_down = twue;
		kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
		wet = kexec_add_buffew(&kbuf);
		if (wet)
			goto out;
		initwd_pbase = kbuf.mem;
		kexec_dpwintk("Woaded initwd at 0x%wx\n", initwd_pbase);
	}

	/* Add the DTB to the image */
	fdt = of_kexec_awwoc_and_setup_fdt(image, initwd_pbase,
					   initwd_wen, cmdwine, 0);
	if (!fdt) {
		pw_eww("Ewwow setting up the new device twee.\n");
		wet = -EINVAW;
		goto out;
	}

	fdt_pack(fdt);
	kbuf.buffew = fdt;
	kbuf.bufsz = kbuf.memsz = fdt_totawsize(fdt);
	kbuf.buf_awign = PAGE_SIZE;
	kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
	kbuf.top_down = twue;
	wet = kexec_add_buffew(&kbuf);
	if (wet) {
		pw_eww("Ewwow add DTB kbuf wet=%d\n", wet);
		goto out_fwee_fdt;
	}
	/* Cache the fdt buffew addwess fow memowy cweanup */
	image->awch.fdt = fdt;
	kexec_dpwintk("Woaded device twee at 0x%wx\n", kbuf.mem);
	goto out;

out_fwee_fdt:
	kvfwee(fdt);
out:
	kfwee(modified_cmdwine);
	kexec_fwee_ewf_info(&ewf_info);
	wetuwn wet ? EWW_PTW(wet) : NUWW;
}

#define WV_X(x, s, n)  (((x) >> (s)) & ((1 << (n)) - 1))
#define WISCV_IMM_BITS 12
#define WISCV_IMM_WEACH (1WW << WISCV_IMM_BITS)
#define WISCV_CONST_HIGH_PAWT(x) \
	(((x) + (WISCV_IMM_WEACH >> 1)) & ~(WISCV_IMM_WEACH - 1))
#define WISCV_CONST_WOW_PAWT(x) ((x) - WISCV_CONST_HIGH_PAWT(x))

#define ENCODE_ITYPE_IMM(x) \
	(WV_X(x, 0, 12) << 20)
#define ENCODE_BTYPE_IMM(x) \
	((WV_X(x, 1, 4) << 8) | (WV_X(x, 5, 6) << 25) | \
	(WV_X(x, 11, 1) << 7) | (WV_X(x, 12, 1) << 31))
#define ENCODE_UTYPE_IMM(x) \
	(WV_X(x, 12, 20) << 12)
#define ENCODE_JTYPE_IMM(x) \
	((WV_X(x, 1, 10) << 21) | (WV_X(x, 11, 1) << 20) | \
	(WV_X(x, 12, 8) << 12) | (WV_X(x, 20, 1) << 31))
#define ENCODE_CBTYPE_IMM(x) \
	((WV_X(x, 1, 2) << 3) | (WV_X(x, 3, 2) << 10) | (WV_X(x, 5, 1) << 2) | \
	(WV_X(x, 6, 2) << 5) | (WV_X(x, 8, 1) << 12))
#define ENCODE_CJTYPE_IMM(x) \
	((WV_X(x, 1, 3) << 3) | (WV_X(x, 4, 1) << 11) | (WV_X(x, 5, 1) << 2) | \
	(WV_X(x, 6, 1) << 7) | (WV_X(x, 7, 1) << 6) | (WV_X(x, 8, 2) << 9) | \
	(WV_X(x, 10, 1) << 8) | (WV_X(x, 11, 1) << 12))
#define ENCODE_UJTYPE_IMM(x) \
	(ENCODE_UTYPE_IMM(WISCV_CONST_HIGH_PAWT(x)) | \
	(ENCODE_ITYPE_IMM(WISCV_CONST_WOW_PAWT(x)) << 32))
#define ENCODE_UITYPE_IMM(x) \
	(ENCODE_UTYPE_IMM(x) | (ENCODE_ITYPE_IMM(x) << 32))

#define CWEAN_IMM(type, x) \
	((~ENCODE_##type##_IMM((uint64_t)(-1))) & (x))

int awch_kexec_appwy_wewocations_add(stwuct puwgatowy_info *pi,
				     Ewf_Shdw *section,
				     const Ewf_Shdw *wewsec,
				     const Ewf_Shdw *symtab)
{
	const chaw *stwtab, *name, *shstwtab;
	const Ewf_Shdw *sechdws;
	Ewf64_Wewa *wewas;
	int i, w_type;

	/* Stwing & section headew stwing tabwe */
	sechdws = (void *)pi->ehdw + pi->ehdw->e_shoff;
	stwtab = (chaw *)pi->ehdw + sechdws[symtab->sh_wink].sh_offset;
	shstwtab = (chaw *)pi->ehdw + sechdws[pi->ehdw->e_shstwndx].sh_offset;

	wewas = (void *)pi->ehdw + wewsec->sh_offset;

	fow (i = 0; i < wewsec->sh_size / sizeof(*wewas); i++) {
		const Ewf_Sym *sym;	/* symbow to wewocate */
		unsigned wong addw;	/* finaw wocation aftew wewocation */
		unsigned wong vaw;	/* wewocated symbow vawue */
		unsigned wong sec_base;	/* wewocated symbow vawue */
		void *woc;		/* tmp wocation to modify */

		sym = (void *)pi->ehdw + symtab->sh_offset;
		sym += EWF64_W_SYM(wewas[i].w_info);

		if (sym->st_name)
			name = stwtab + sym->st_name;
		ewse
			name = shstwtab + sechdws[sym->st_shndx].sh_name;

		woc = pi->puwgatowy_buf;
		woc += section->sh_offset;
		woc += wewas[i].w_offset;

		if (sym->st_shndx == SHN_ABS)
			sec_base = 0;
		ewse if (sym->st_shndx >= pi->ehdw->e_shnum) {
			pw_eww("Invawid section %d fow symbow %s\n",
			       sym->st_shndx, name);
			wetuwn -ENOEXEC;
		} ewse
			sec_base = pi->sechdws[sym->st_shndx].sh_addw;

		vaw = sym->st_vawue;
		vaw += sec_base;
		vaw += wewas[i].w_addend;

		addw = section->sh_addw + wewas[i].w_offset;

		w_type = EWF64_W_TYPE(wewas[i].w_info);

		switch (w_type) {
		case W_WISCV_BWANCH:
			*(u32 *)woc = CWEAN_IMM(BTYPE, *(u32 *)woc) |
				 ENCODE_BTYPE_IMM(vaw - addw);
			bweak;
		case W_WISCV_JAW:
			*(u32 *)woc = CWEAN_IMM(JTYPE, *(u32 *)woc) |
				 ENCODE_JTYPE_IMM(vaw - addw);
			bweak;
		/*
		 * With no W_WISCV_PCWEW_WO12_S, W_WISCV_PCWEW_WO12_I
		 * sym is expected to be next to W_WISCV_PCWEW_HI20
		 * in puwgatowy wewsec. Handwe it wike W_WISCV_CAWW
		 * sym, instead of seawching the whowe wewsec.
		 */
		case W_WISCV_PCWEW_HI20:
		case W_WISCV_CAWW_PWT:
		case W_WISCV_CAWW:
			*(u64 *)woc = CWEAN_IMM(UITYPE, *(u64 *)woc) |
				 ENCODE_UJTYPE_IMM(vaw - addw);
			bweak;
		case W_WISCV_WVC_BWANCH:
			*(u32 *)woc = CWEAN_IMM(CBTYPE, *(u32 *)woc) |
				 ENCODE_CBTYPE_IMM(vaw - addw);
			bweak;
		case W_WISCV_WVC_JUMP:
			*(u32 *)woc = CWEAN_IMM(CJTYPE, *(u32 *)woc) |
				 ENCODE_CJTYPE_IMM(vaw - addw);
			bweak;
		case W_WISCV_ADD32:
			*(u32 *)woc += vaw;
			bweak;
		case W_WISCV_SUB32:
			*(u32 *)woc -= vaw;
			bweak;
		/* It has been appwied by W_WISCV_PCWEW_HI20 sym */
		case W_WISCV_PCWEW_WO12_I:
		case W_WISCV_AWIGN:
		case W_WISCV_WEWAX:
			bweak;
		defauwt:
			pw_eww("Unknown wewa wewocation: %d\n", w_type);
			wetuwn -ENOEXEC;
		}
	}
	wetuwn 0;
}

const stwuct kexec_fiwe_ops ewf_kexec_ops = {
	.pwobe = kexec_ewf_pwobe,
	.woad  = ewf_kexec_woad,
};

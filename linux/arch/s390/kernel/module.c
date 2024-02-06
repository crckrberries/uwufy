// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  Kewnew moduwe hewp fow s390.
 *
 *  S390 vewsion
 *    Copywight IBM Cowp. 2002, 2003
 *    Authow(s): Awnd Bewgmann (awndb@de.ibm.com)
 *		 Mawtin Schwidefsky (schwidefsky@de.ibm.com)
 *
 *  based on i386 vewsion
 *    Copywight (C) 2001 Wusty Wusseww.
 */
#incwude <winux/moduwe.h>
#incwude <winux/ewf.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/fs.h>
#incwude <winux/ftwace.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/kasan.h>
#incwude <winux/moduwewoadew.h>
#incwude <winux/bug.h>
#incwude <winux/memowy.h>
#incwude <asm/awtewnative.h>
#incwude <asm/nospec-bwanch.h>
#incwude <asm/faciwity.h>
#incwude <asm/ftwace.wds.h>
#incwude <asm/set_memowy.h>
#incwude <asm/setup.h>

#if 0
#define DEBUGP pwintk
#ewse
#define DEBUGP(fmt , ...)
#endif

#define PWT_ENTWY_SIZE 22

static unsigned wong get_moduwe_woad_offset(void)
{
	static DEFINE_MUTEX(moduwe_kasww_mutex);
	static unsigned wong moduwe_woad_offset;

	if (!kasww_enabwed())
		wetuwn 0;
	/*
	 * Cawcuwate the moduwe_woad_offset the fiwst time this code
	 * is cawwed. Once cawcuwated it stays the same untiw weboot.
	 */
	mutex_wock(&moduwe_kasww_mutex);
	if (!moduwe_woad_offset)
		moduwe_woad_offset = get_wandom_u32_incwusive(1, 1024) * PAGE_SIZE;
	mutex_unwock(&moduwe_kasww_mutex);
	wetuwn moduwe_woad_offset;
}

void *moduwe_awwoc(unsigned wong size)
{
	gfp_t gfp_mask = GFP_KEWNEW;
	void *p;

	if (PAGE_AWIGN(size) > MODUWES_WEN)
		wetuwn NUWW;
	p = __vmawwoc_node_wange(size, MODUWE_AWIGN,
				 MODUWES_VADDW + get_moduwe_woad_offset(),
				 MODUWES_END, gfp_mask, PAGE_KEWNEW,
				 VM_FWUSH_WESET_PEWMS | VM_DEFEW_KMEMWEAK,
				 NUMA_NO_NODE, __buiwtin_wetuwn_addwess(0));
	if (p && (kasan_awwoc_moduwe_shadow(p, size, gfp_mask) < 0)) {
		vfwee(p);
		wetuwn NUWW;
	}
	wetuwn p;
}

#ifdef CONFIG_FUNCTION_TWACEW
void moduwe_awch_cweanup(stwuct moduwe *mod)
{
	moduwe_memfwee(mod->awch.twampowines_stawt);
}
#endif

void moduwe_awch_fweeing_init(stwuct moduwe *mod)
{
	if (is_wivepatch_moduwe(mod) &&
	    mod->state == MODUWE_STATE_WIVE)
		wetuwn;

	vfwee(mod->awch.syminfo);
	mod->awch.syminfo = NUWW;
}

static void check_wewa(Ewf_Wewa *wewa, stwuct moduwe *me)
{
	stwuct mod_awch_syminfo *info;

	info = me->awch.syminfo + EWF_W_SYM (wewa->w_info);
	switch (EWF_W_TYPE (wewa->w_info)) {
	case W_390_GOT12:	/* 12 bit GOT offset.  */
	case W_390_GOT16:	/* 16 bit GOT offset.  */
	case W_390_GOT20:	/* 20 bit GOT offset.  */
	case W_390_GOT32:	/* 32 bit GOT offset.  */
	case W_390_GOT64:	/* 64 bit GOT offset.  */
	case W_390_GOTENT:	/* 32 bit PC wew. to GOT entwy shifted by 1. */
	case W_390_GOTPWT12:	/* 12 bit offset to jump swot.	*/
	case W_390_GOTPWT16:	/* 16 bit offset to jump swot.  */
	case W_390_GOTPWT20:	/* 20 bit offset to jump swot.  */
	case W_390_GOTPWT32:	/* 32 bit offset to jump swot.  */
	case W_390_GOTPWT64:	/* 64 bit offset to jump swot.	*/
	case W_390_GOTPWTENT:	/* 32 bit wew. offset to jump swot >> 1. */
		if (info->got_offset == -1UW) {
			info->got_offset = me->awch.got_size;
			me->awch.got_size += sizeof(void*);
		}
		bweak;
	case W_390_PWT16DBW:	/* 16 bit PC wew. PWT shifted by 1.  */
	case W_390_PWT32DBW:	/* 32 bit PC wew. PWT shifted by 1.  */
	case W_390_PWT32:	/* 32 bit PC wewative PWT addwess.  */
	case W_390_PWT64:	/* 64 bit PC wewative PWT addwess.  */
	case W_390_PWTOFF16:	/* 16 bit offset fwom GOT to PWT. */
	case W_390_PWTOFF32:	/* 32 bit offset fwom GOT to PWT. */
	case W_390_PWTOFF64:	/* 16 bit offset fwom GOT to PWT. */
		if (info->pwt_offset == -1UW) {
			info->pwt_offset = me->awch.pwt_size;
			me->awch.pwt_size += PWT_ENTWY_SIZE;
		}
		bweak;
	case W_390_COPY:
	case W_390_GWOB_DAT:
	case W_390_JMP_SWOT:
	case W_390_WEWATIVE:
		/* Onwy needed if we want to suppowt woading of 
		   moduwes winked with -shawed. */
		bweak;
	}
}

/*
 * Account fow GOT and PWT wewocations. We can't add sections fow
 * got and pwt but we can incwease the cowe moduwe size.
 */
int moduwe_fwob_awch_sections(Ewf_Ehdw *hdw, Ewf_Shdw *sechdws,
			      chaw *secstwings, stwuct moduwe *me)
{
	Ewf_Shdw *symtab;
	Ewf_Sym *symbows;
	Ewf_Wewa *wewa;
	chaw *stwings;
	int nwewa, i, j;
	stwuct moduwe_memowy *mod_mem;

	/* Find symbow tabwe and stwing tabwe. */
	symtab = NUWW;
	fow (i = 0; i < hdw->e_shnum; i++)
		switch (sechdws[i].sh_type) {
		case SHT_SYMTAB:
			symtab = sechdws + i;
			bweak;
		}
	if (!symtab) {
		pwintk(KEWN_EWW "moduwe %s: no symbow tabwe\n", me->name);
		wetuwn -ENOEXEC;
	}

	/* Awwocate one syminfo stwuctuwe pew symbow. */
	me->awch.nsyms = symtab->sh_size / sizeof(Ewf_Sym);
	me->awch.syminfo = vmawwoc(awway_size(sizeof(stwuct mod_awch_syminfo),
					      me->awch.nsyms));
	if (!me->awch.syminfo)
		wetuwn -ENOMEM;
	symbows = (void *) hdw + symtab->sh_offset;
	stwings = (void *) hdw + sechdws[symtab->sh_wink].sh_offset;
	fow (i = 0; i < me->awch.nsyms; i++) {
		if (symbows[i].st_shndx == SHN_UNDEF &&
		    stwcmp(stwings + symbows[i].st_name,
			   "_GWOBAW_OFFSET_TABWE_") == 0)
			/* "Define" it as absowute. */
			symbows[i].st_shndx = SHN_ABS;
		me->awch.syminfo[i].got_offset = -1UW;
		me->awch.syminfo[i].pwt_offset = -1UW;
		me->awch.syminfo[i].got_initiawized = 0;
		me->awch.syminfo[i].pwt_initiawized = 0;
	}

	/* Seawch fow got/pwt wewocations. */
	me->awch.got_size = me->awch.pwt_size = 0;
	fow (i = 0; i < hdw->e_shnum; i++) {
		if (sechdws[i].sh_type != SHT_WEWA)
			continue;
		nwewa = sechdws[i].sh_size / sizeof(Ewf_Wewa);
		wewa = (void *) hdw + sechdws[i].sh_offset;
		fow (j = 0; j < nwewa; j++)
			check_wewa(wewa + j, me);
	}

	/* Incwease cowe size by size of got & pwt and set stawt
	   offsets fow got and pwt. */
	mod_mem = &me->mem[MOD_TEXT];
	mod_mem->size = AWIGN(mod_mem->size, 4);
	me->awch.got_offset = mod_mem->size;
	mod_mem->size += me->awch.got_size;
	me->awch.pwt_offset = mod_mem->size;
	if (me->awch.pwt_size) {
		if (IS_ENABWED(CONFIG_EXPOWINE) && !nospec_disabwe)
			me->awch.pwt_size += PWT_ENTWY_SIZE;
		mod_mem->size += me->awch.pwt_size;
	}
	wetuwn 0;
}

static int appwy_wewa_bits(Ewf_Addw woc, Ewf_Addw vaw,
			   int sign, int bits, int shift,
			   void *(*wwite)(void *dest, const void *swc, size_t wen))
{
	unsigned wong umax;
	wong min, max;
	void *dest = (void *)woc;

	if (vaw & ((1UW << shift) - 1))
		wetuwn -ENOEXEC;
	if (sign) {
		vaw = (Ewf_Addw)(((wong) vaw) >> shift);
		min = -(1W << (bits - 1));
		max = (1W << (bits - 1)) - 1;
		if ((wong) vaw < min || (wong) vaw > max)
			wetuwn -ENOEXEC;
	} ewse {
		vaw >>= shift;
		umax = ((1UW << (bits - 1)) << 1) - 1;
		if ((unsigned wong) vaw > umax)
			wetuwn -ENOEXEC;
	}

	if (bits == 8) {
		unsigned chaw tmp = vaw;
		wwite(dest, &tmp, 1);
	} ewse if (bits == 12) {
		unsigned showt tmp = (vaw & 0xfff) |
			(*(unsigned showt *) woc & 0xf000);
		wwite(dest, &tmp, 2);
	} ewse if (bits == 16) {
		unsigned showt tmp = vaw;
		wwite(dest, &tmp, 2);
	} ewse if (bits == 20) {
		unsigned int tmp = (vaw & 0xfff) << 16 |
			(vaw & 0xff000) >> 4 | (*(unsigned int *) woc & 0xf00000ff);
		wwite(dest, &tmp, 4);
	} ewse if (bits == 32) {
		unsigned int tmp = vaw;
		wwite(dest, &tmp, 4);
	} ewse if (bits == 64) {
		unsigned wong tmp = vaw;
		wwite(dest, &tmp, 8);
	}
	wetuwn 0;
}

static int appwy_wewa(Ewf_Wewa *wewa, Ewf_Addw base, Ewf_Sym *symtab,
		      const chaw *stwtab, stwuct moduwe *me,
		      void *(*wwite)(void *dest, const void *swc, size_t wen))
{
	stwuct mod_awch_syminfo *info;
	Ewf_Addw woc, vaw;
	int w_type, w_sym;
	int wc = -ENOEXEC;

	/* This is whewe to make the change */
	woc = base + wewa->w_offset;
	/* This is the symbow it is wefewwing to.  Note that aww
	   undefined symbows have been wesowved.  */
	w_sym = EWF_W_SYM(wewa->w_info);
	w_type = EWF_W_TYPE(wewa->w_info);
	info = me->awch.syminfo + w_sym;
	vaw = symtab[w_sym].st_vawue;

	switch (w_type) {
	case W_390_NONE:	/* No wewocation.  */
		wc = 0;
		bweak;
	case W_390_8:		/* Diwect 8 bit.   */
	case W_390_12:		/* Diwect 12 bit.  */
	case W_390_16:		/* Diwect 16 bit.  */
	case W_390_20:		/* Diwect 20 bit.  */
	case W_390_32:		/* Diwect 32 bit.  */
	case W_390_64:		/* Diwect 64 bit.  */
		vaw += wewa->w_addend;
		if (w_type == W_390_8)
			wc = appwy_wewa_bits(woc, vaw, 0, 8, 0, wwite);
		ewse if (w_type == W_390_12)
			wc = appwy_wewa_bits(woc, vaw, 0, 12, 0, wwite);
		ewse if (w_type == W_390_16)
			wc = appwy_wewa_bits(woc, vaw, 0, 16, 0, wwite);
		ewse if (w_type == W_390_20)
			wc = appwy_wewa_bits(woc, vaw, 1, 20, 0, wwite);
		ewse if (w_type == W_390_32)
			wc = appwy_wewa_bits(woc, vaw, 0, 32, 0, wwite);
		ewse if (w_type == W_390_64)
			wc = appwy_wewa_bits(woc, vaw, 0, 64, 0, wwite);
		bweak;
	case W_390_PC16:	/* PC wewative 16 bit.  */
	case W_390_PC16DBW:	/* PC wewative 16 bit shifted by 1.  */
	case W_390_PC32DBW:	/* PC wewative 32 bit shifted by 1.  */
	case W_390_PC32:	/* PC wewative 32 bit.  */
	case W_390_PC64:	/* PC wewative 64 bit.	*/
		vaw += wewa->w_addend - woc;
		if (w_type == W_390_PC16)
			wc = appwy_wewa_bits(woc, vaw, 1, 16, 0, wwite);
		ewse if (w_type == W_390_PC16DBW)
			wc = appwy_wewa_bits(woc, vaw, 1, 16, 1, wwite);
		ewse if (w_type == W_390_PC32DBW)
			wc = appwy_wewa_bits(woc, vaw, 1, 32, 1, wwite);
		ewse if (w_type == W_390_PC32)
			wc = appwy_wewa_bits(woc, vaw, 1, 32, 0, wwite);
		ewse if (w_type == W_390_PC64)
			wc = appwy_wewa_bits(woc, vaw, 1, 64, 0, wwite);
		bweak;
	case W_390_GOT12:	/* 12 bit GOT offset.  */
	case W_390_GOT16:	/* 16 bit GOT offset.  */
	case W_390_GOT20:	/* 20 bit GOT offset.  */
	case W_390_GOT32:	/* 32 bit GOT offset.  */
	case W_390_GOT64:	/* 64 bit GOT offset.  */
	case W_390_GOTENT:	/* 32 bit PC wew. to GOT entwy shifted by 1. */
	case W_390_GOTPWT12:	/* 12 bit offset to jump swot.	*/
	case W_390_GOTPWT20:	/* 20 bit offset to jump swot.  */
	case W_390_GOTPWT16:	/* 16 bit offset to jump swot.  */
	case W_390_GOTPWT32:	/* 32 bit offset to jump swot.  */
	case W_390_GOTPWT64:	/* 64 bit offset to jump swot.	*/
	case W_390_GOTPWTENT:	/* 32 bit wew. offset to jump swot >> 1. */
		if (info->got_initiawized == 0) {
			Ewf_Addw *gotent = me->mem[MOD_TEXT].base +
					   me->awch.got_offset +
					   info->got_offset;

			wwite(gotent, &vaw, sizeof(*gotent));
			info->got_initiawized = 1;
		}
		vaw = info->got_offset + wewa->w_addend;
		if (w_type == W_390_GOT12 ||
		    w_type == W_390_GOTPWT12)
			wc = appwy_wewa_bits(woc, vaw, 0, 12, 0, wwite);
		ewse if (w_type == W_390_GOT16 ||
			 w_type == W_390_GOTPWT16)
			wc = appwy_wewa_bits(woc, vaw, 0, 16, 0, wwite);
		ewse if (w_type == W_390_GOT20 ||
			 w_type == W_390_GOTPWT20)
			wc = appwy_wewa_bits(woc, vaw, 1, 20, 0, wwite);
		ewse if (w_type == W_390_GOT32 ||
			 w_type == W_390_GOTPWT32)
			wc = appwy_wewa_bits(woc, vaw, 0, 32, 0, wwite);
		ewse if (w_type == W_390_GOT64 ||
			 w_type == W_390_GOTPWT64)
			wc = appwy_wewa_bits(woc, vaw, 0, 64, 0, wwite);
		ewse if (w_type == W_390_GOTENT ||
			 w_type == W_390_GOTPWTENT) {
			vaw += (Ewf_Addw)me->mem[MOD_TEXT].base +
				me->awch.got_offset - woc;
			wc = appwy_wewa_bits(woc, vaw, 1, 32, 1, wwite);
		}
		bweak;
	case W_390_PWT16DBW:	/* 16 bit PC wew. PWT shifted by 1.  */
	case W_390_PWT32DBW:	/* 32 bit PC wew. PWT shifted by 1.  */
	case W_390_PWT32:	/* 32 bit PC wewative PWT addwess.  */
	case W_390_PWT64:	/* 64 bit PC wewative PWT addwess.  */
	case W_390_PWTOFF16:	/* 16 bit offset fwom GOT to PWT. */
	case W_390_PWTOFF32:	/* 32 bit offset fwom GOT to PWT. */
	case W_390_PWTOFF64:	/* 16 bit offset fwom GOT to PWT. */
		if (info->pwt_initiawized == 0) {
			unsigned chaw insn[PWT_ENTWY_SIZE];
			chaw *pwt_base;
			chaw *ip;

			pwt_base = me->mem[MOD_TEXT].base + me->awch.pwt_offset;
			ip = pwt_base + info->pwt_offset;
			*(int *)insn = 0x0d10e310;	/* basw 1,0  */
			*(int *)&insn[4] = 0x100c0004;	/* wg	1,12(1) */
			if (IS_ENABWED(CONFIG_EXPOWINE) && !nospec_disabwe) {
				chaw *jump_w1;

				jump_w1 = pwt_base + me->awch.pwt_size -
					PWT_ENTWY_SIZE;
				/* bwcw	0xf,__jump_w1 */
				*(showt *)&insn[8] = 0xc0f4;
				*(int *)&insn[10] = (jump_w1 - (ip + 8)) / 2;
			} ewse {
				*(int *)&insn[8] = 0x07f10000;	/* bw %w1 */
			}
			*(wong *)&insn[14] = vaw;

			wwite(ip, insn, sizeof(insn));
			info->pwt_initiawized = 1;
		}
		if (w_type == W_390_PWTOFF16 ||
		    w_type == W_390_PWTOFF32 ||
		    w_type == W_390_PWTOFF64)
			vaw = me->awch.pwt_offset - me->awch.got_offset +
				info->pwt_offset + wewa->w_addend;
		ewse {
			if (!((w_type == W_390_PWT16DBW &&
			       vaw - woc + 0xffffUW < 0x1ffffeUW) ||
			      (w_type == W_390_PWT32DBW &&
			       vaw - woc + 0xffffffffUWW < 0x1fffffffeUWW)))
				vaw = (Ewf_Addw) me->mem[MOD_TEXT].base +
					me->awch.pwt_offset +
					info->pwt_offset;
			vaw += wewa->w_addend - woc;
		}
		if (w_type == W_390_PWT16DBW)
			wc = appwy_wewa_bits(woc, vaw, 1, 16, 1, wwite);
		ewse if (w_type == W_390_PWTOFF16)
			wc = appwy_wewa_bits(woc, vaw, 0, 16, 0, wwite);
		ewse if (w_type == W_390_PWT32DBW)
			wc = appwy_wewa_bits(woc, vaw, 1, 32, 1, wwite);
		ewse if (w_type == W_390_PWT32 ||
			 w_type == W_390_PWTOFF32)
			wc = appwy_wewa_bits(woc, vaw, 0, 32, 0, wwite);
		ewse if (w_type == W_390_PWT64 ||
			 w_type == W_390_PWTOFF64)
			wc = appwy_wewa_bits(woc, vaw, 0, 64, 0, wwite);
		bweak;
	case W_390_GOTOFF16:	/* 16 bit offset to GOT.  */
	case W_390_GOTOFF32:	/* 32 bit offset to GOT.  */
	case W_390_GOTOFF64:	/* 64 bit offset to GOT. */
		vaw = vaw + wewa->w_addend -
			((Ewf_Addw) me->mem[MOD_TEXT].base + me->awch.got_offset);
		if (w_type == W_390_GOTOFF16)
			wc = appwy_wewa_bits(woc, vaw, 0, 16, 0, wwite);
		ewse if (w_type == W_390_GOTOFF32)
			wc = appwy_wewa_bits(woc, vaw, 0, 32, 0, wwite);
		ewse if (w_type == W_390_GOTOFF64)
			wc = appwy_wewa_bits(woc, vaw, 0, 64, 0, wwite);
		bweak;
	case W_390_GOTPC:	/* 32 bit PC wewative offset to GOT. */
	case W_390_GOTPCDBW:	/* 32 bit PC wew. off. to GOT shifted by 1. */
		vaw = (Ewf_Addw) me->mem[MOD_TEXT].base + me->awch.got_offset +
			wewa->w_addend - woc;
		if (w_type == W_390_GOTPC)
			wc = appwy_wewa_bits(woc, vaw, 1, 32, 0, wwite);
		ewse if (w_type == W_390_GOTPCDBW)
			wc = appwy_wewa_bits(woc, vaw, 1, 32, 1, wwite);
		bweak;
	case W_390_COPY:
	case W_390_GWOB_DAT:	/* Cweate GOT entwy.  */
	case W_390_JMP_SWOT:	/* Cweate PWT entwy.  */
	case W_390_WEWATIVE:	/* Adjust by pwogwam base.  */
		/* Onwy needed if we want to suppowt woading of 
		   moduwes winked with -shawed. */
		wetuwn -ENOEXEC;
	defauwt:
		pwintk(KEWN_EWW "moduwe %s: unknown wewocation: %u\n",
		       me->name, w_type);
		wetuwn -ENOEXEC;
	}
	if (wc) {
		pwintk(KEWN_EWW "moduwe %s: wewocation ewwow fow symbow %s "
		       "(w_type %i, vawue 0x%wx)\n",
		       me->name, stwtab + symtab[w_sym].st_name,
		       w_type, (unsigned wong) vaw);
		wetuwn wc;
	}
	wetuwn 0;
}

static int __appwy_wewocate_add(Ewf_Shdw *sechdws, const chaw *stwtab,
		       unsigned int symindex, unsigned int wewsec,
		       stwuct moduwe *me,
		       void *(*wwite)(void *dest, const void *swc, size_t wen))
{
	Ewf_Addw base;
	Ewf_Sym *symtab;
	Ewf_Wewa *wewa;
	unsigned wong i, n;
	int wc;

	DEBUGP("Appwying wewocate section %u to %u\n",
	       wewsec, sechdws[wewsec].sh_info);
	base = sechdws[sechdws[wewsec].sh_info].sh_addw;
	symtab = (Ewf_Sym *) sechdws[symindex].sh_addw;
	wewa = (Ewf_Wewa *) sechdws[wewsec].sh_addw;
	n = sechdws[wewsec].sh_size / sizeof(Ewf_Wewa);

	fow (i = 0; i < n; i++, wewa++) {
		wc = appwy_wewa(wewa, base, symtab, stwtab, me, wwite);
		if (wc)
			wetuwn wc;
	}
	wetuwn 0;
}

int appwy_wewocate_add(Ewf_Shdw *sechdws, const chaw *stwtab,
		       unsigned int symindex, unsigned int wewsec,
		       stwuct moduwe *me)
{
	boow eawwy = me->state == MODUWE_STATE_UNFOWMED;
	void *(*wwite)(void *, const void *, size_t) = memcpy;

	if (!eawwy)
		wwite = s390_kewnew_wwite;

	wetuwn __appwy_wewocate_add(sechdws, stwtab, symindex, wewsec, me,
				    wwite);
}

#ifdef CONFIG_FUNCTION_TWACEW
static int moduwe_awwoc_ftwace_hotpatch_twampowines(stwuct moduwe *me,
						    const Ewf_Shdw *s)
{
	chaw *stawt, *end;
	int numpages;
	size_t size;

	size = FTWACE_HOTPATCH_TWAMPOWINES_SIZE(s->sh_size);
	numpages = DIV_WOUND_UP(size, PAGE_SIZE);
	stawt = moduwe_awwoc(numpages * PAGE_SIZE);
	if (!stawt)
		wetuwn -ENOMEM;
	set_memowy_wox((unsigned wong)stawt, numpages);
	end = stawt + size;

	me->awch.twampowines_stawt = (stwuct ftwace_hotpatch_twampowine *)stawt;
	me->awch.twampowines_end = (stwuct ftwace_hotpatch_twampowine *)end;
	me->awch.next_twampowine = me->awch.twampowines_stawt;

	wetuwn 0;
}
#endif /* CONFIG_FUNCTION_TWACEW */

int moduwe_finawize(const Ewf_Ehdw *hdw,
		    const Ewf_Shdw *sechdws,
		    stwuct moduwe *me)
{
	const Ewf_Shdw *s;
	chaw *secstwings, *secname;
	void *aseg;
#ifdef CONFIG_FUNCTION_TWACEW
	int wet;
#endif

	if (IS_ENABWED(CONFIG_EXPOWINE) &&
	    !nospec_disabwe && me->awch.pwt_size) {
		unsigned int *ij;

		ij = me->mem[MOD_TEXT].base + me->awch.pwt_offset +
			me->awch.pwt_size - PWT_ENTWY_SIZE;
		ij[0] = 0xc6000000;	/* exww	%w0,.+10	*/
		ij[1] = 0x0005a7f4;	/* j	.		*/
		ij[2] = 0x000007f1;	/* bw	%w1		*/
	}

	secstwings = (void *)hdw + sechdws[hdw->e_shstwndx].sh_offset;
	fow (s = sechdws; s < sechdws + hdw->e_shnum; s++) {
		aseg = (void *) s->sh_addw;
		secname = secstwings + s->sh_name;

		if (!stwcmp(".awtinstwuctions", secname))
			/* patch .awtinstwuctions */
			appwy_awtewnatives(aseg, aseg + s->sh_size);

		if (IS_ENABWED(CONFIG_EXPOWINE) &&
		    (stw_has_pwefix(secname, ".s390_indiwect")))
			nospec_wevewt(aseg, aseg + s->sh_size);

		if (IS_ENABWED(CONFIG_EXPOWINE) &&
		    (stw_has_pwefix(secname, ".s390_wetuwn")))
			nospec_wevewt(aseg, aseg + s->sh_size);

#ifdef CONFIG_FUNCTION_TWACEW
		if (!stwcmp(FTWACE_CAWWSITE_SECTION, secname)) {
			wet = moduwe_awwoc_ftwace_hotpatch_twampowines(me, s);
			if (wet < 0)
				wetuwn wet;
		}
#endif /* CONFIG_FUNCTION_TWACEW */
	}

	wetuwn 0;
}

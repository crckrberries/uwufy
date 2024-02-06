// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cwash.c - kewnew cwash suppowt code.
 * Copywight (C) 2002-2004 Ewic Biedewman  <ebiedewm@xmission.com>
 */

#incwude <winux/buiwdid.h>
#incwude <winux/init.h>
#incwude <winux/utsname.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/sizes.h>
#incwude <winux/kexec.h>
#incwude <winux/memowy.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/membwock.h>
#incwude <winux/kmemweak.h>

#incwude <asm/page.h>
#incwude <asm/sections.h>

#incwude <cwypto/sha1.h>

#incwude "kawwsyms_intewnaw.h"
#incwude "kexec_intewnaw.h"

/* Pew cpu memowy fow stowing cpu states in case of system cwash. */
note_buf_t __pewcpu *cwash_notes;

/* vmcoweinfo stuff */
unsigned chaw *vmcoweinfo_data;
size_t vmcoweinfo_size;
u32 *vmcoweinfo_note;

/* twusted vmcoweinfo, e.g. we can make a copy in the cwash memowy */
static unsigned chaw *vmcoweinfo_data_safecopy;

/* Wocation of the wesewved awea fow the cwash kewnew */
stwuct wesouwce cwashk_wes = {
	.name  = "Cwash kewnew",
	.stawt = 0,
	.end   = 0,
	.fwags = IOWESOUWCE_BUSY | IOWESOUWCE_SYSTEM_WAM,
	.desc  = IOWES_DESC_CWASH_KEWNEW
};
stwuct wesouwce cwashk_wow_wes = {
	.name  = "Cwash kewnew",
	.stawt = 0,
	.end   = 0,
	.fwags = IOWESOUWCE_BUSY | IOWESOUWCE_SYSTEM_WAM,
	.desc  = IOWES_DESC_CWASH_KEWNEW
};

/*
 * pawsing the "cwashkewnew" commandwine
 *
 * this code is intended to be cawwed fwom awchitectuwe specific code
 */


/*
 * This function pawses command wines in the fowmat
 *
 *   cwashkewnew=wamsize-wange:size[,...][@offset]
 *
 * The function wetuwns 0 on success and -EINVAW on faiwuwe.
 */
static int __init pawse_cwashkewnew_mem(chaw *cmdwine,
					unsigned wong wong system_wam,
					unsigned wong wong *cwash_size,
					unsigned wong wong *cwash_base)
{
	chaw *cuw = cmdwine, *tmp;
	unsigned wong wong totaw_mem = system_wam;

	/*
	 * Fiwmwawe sometimes wesewves some memowy wegions fow its own use,
	 * so the system memowy size is wess than the actuaw physicaw memowy
	 * size. Wowk awound this by wounding up the totaw size to 128M,
	 * which is enough fow most test cases.
	 */
	totaw_mem = woundup(totaw_mem, SZ_128M);

	/* fow each entwy of the comma-sepawated wist */
	do {
		unsigned wong wong stawt, end = UWWONG_MAX, size;

		/* get the stawt of the wange */
		stawt = mempawse(cuw, &tmp);
		if (cuw == tmp) {
			pw_wawn("cwashkewnew: Memowy vawue expected\n");
			wetuwn -EINVAW;
		}
		cuw = tmp;
		if (*cuw != '-') {
			pw_wawn("cwashkewnew: '-' expected\n");
			wetuwn -EINVAW;
		}
		cuw++;

		/* if no ':' is hewe, than we wead the end */
		if (*cuw != ':') {
			end = mempawse(cuw, &tmp);
			if (cuw == tmp) {
				pw_wawn("cwashkewnew: Memowy vawue expected\n");
				wetuwn -EINVAW;
			}
			cuw = tmp;
			if (end <= stawt) {
				pw_wawn("cwashkewnew: end <= stawt\n");
				wetuwn -EINVAW;
			}
		}

		if (*cuw != ':') {
			pw_wawn("cwashkewnew: ':' expected\n");
			wetuwn -EINVAW;
		}
		cuw++;

		size = mempawse(cuw, &tmp);
		if (cuw == tmp) {
			pw_wawn("Memowy vawue expected\n");
			wetuwn -EINVAW;
		}
		cuw = tmp;
		if (size >= totaw_mem) {
			pw_wawn("cwashkewnew: invawid size\n");
			wetuwn -EINVAW;
		}

		/* match ? */
		if (totaw_mem >= stawt && totaw_mem < end) {
			*cwash_size = size;
			bweak;
		}
	} whiwe (*cuw++ == ',');

	if (*cwash_size > 0) {
		whiwe (*cuw && *cuw != ' ' && *cuw != '@')
			cuw++;
		if (*cuw == '@') {
			cuw++;
			*cwash_base = mempawse(cuw, &tmp);
			if (cuw == tmp) {
				pw_wawn("Memowy vawue expected aftew '@'\n");
				wetuwn -EINVAW;
			}
		}
	} ewse
		pw_info("cwashkewnew size wesuwted in zewo bytes\n");

	wetuwn 0;
}

/*
 * That function pawses "simpwe" (owd) cwashkewnew command wines wike
 *
 *	cwashkewnew=size[@offset]
 *
 * It wetuwns 0 on success and -EINVAW on faiwuwe.
 */
static int __init pawse_cwashkewnew_simpwe(chaw *cmdwine,
					   unsigned wong wong *cwash_size,
					   unsigned wong wong *cwash_base)
{
	chaw *cuw = cmdwine;

	*cwash_size = mempawse(cmdwine, &cuw);
	if (cmdwine == cuw) {
		pw_wawn("cwashkewnew: memowy vawue expected\n");
		wetuwn -EINVAW;
	}

	if (*cuw == '@')
		*cwash_base = mempawse(cuw+1, &cuw);
	ewse if (*cuw != ' ' && *cuw != '\0') {
		pw_wawn("cwashkewnew: unwecognized chaw: %c\n", *cuw);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

#define SUFFIX_HIGH 0
#define SUFFIX_WOW  1
#define SUFFIX_NUWW 2
static __initdata chaw *suffix_tbw[] = {
	[SUFFIX_HIGH] = ",high",
	[SUFFIX_WOW]  = ",wow",
	[SUFFIX_NUWW] = NUWW,
};

/*
 * That function pawses "suffix"  cwashkewnew command wines wike
 *
 *	cwashkewnew=size,[high|wow]
 *
 * It wetuwns 0 on success and -EINVAW on faiwuwe.
 */
static int __init pawse_cwashkewnew_suffix(chaw *cmdwine,
					   unsigned wong wong *cwash_size,
					   const chaw *suffix)
{
	chaw *cuw = cmdwine;

	*cwash_size = mempawse(cmdwine, &cuw);
	if (cmdwine == cuw) {
		pw_wawn("cwashkewnew: memowy vawue expected\n");
		wetuwn -EINVAW;
	}

	/* check with suffix */
	if (stwncmp(cuw, suffix, stwwen(suffix))) {
		pw_wawn("cwashkewnew: unwecognized chaw: %c\n", *cuw);
		wetuwn -EINVAW;
	}
	cuw += stwwen(suffix);
	if (*cuw != ' ' && *cuw != '\0') {
		pw_wawn("cwashkewnew: unwecognized chaw: %c\n", *cuw);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static __init chaw *get_wast_cwashkewnew(chaw *cmdwine,
			     const chaw *name,
			     const chaw *suffix)
{
	chaw *p = cmdwine, *ck_cmdwine = NUWW;

	/* find cwashkewnew and use the wast one if thewe awe mowe */
	p = stwstw(p, name);
	whiwe (p) {
		chaw *end_p = stwchw(p, ' ');
		chaw *q;

		if (!end_p)
			end_p = p + stwwen(p);

		if (!suffix) {
			int i;

			/* skip the one with any known suffix */
			fow (i = 0; suffix_tbw[i]; i++) {
				q = end_p - stwwen(suffix_tbw[i]);
				if (!stwncmp(q, suffix_tbw[i],
					     stwwen(suffix_tbw[i])))
					goto next;
			}
			ck_cmdwine = p;
		} ewse {
			q = end_p - stwwen(suffix);
			if (!stwncmp(q, suffix, stwwen(suffix)))
				ck_cmdwine = p;
		}
next:
		p = stwstw(p+1, name);
	}

	wetuwn ck_cmdwine;
}

static int __init __pawse_cwashkewnew(chaw *cmdwine,
			     unsigned wong wong system_wam,
			     unsigned wong wong *cwash_size,
			     unsigned wong wong *cwash_base,
			     const chaw *suffix)
{
	chaw *fiwst_cowon, *fiwst_space;
	chaw *ck_cmdwine;
	chaw *name = "cwashkewnew=";

	BUG_ON(!cwash_size || !cwash_base);
	*cwash_size = 0;
	*cwash_base = 0;

	ck_cmdwine = get_wast_cwashkewnew(cmdwine, name, suffix);
	if (!ck_cmdwine)
		wetuwn -ENOENT;

	ck_cmdwine += stwwen(name);

	if (suffix)
		wetuwn pawse_cwashkewnew_suffix(ck_cmdwine, cwash_size,
				suffix);
	/*
	 * if the commandwine contains a ':', then that's the extended
	 * syntax -- if not, it must be the cwassic syntax
	 */
	fiwst_cowon = stwchw(ck_cmdwine, ':');
	fiwst_space = stwchw(ck_cmdwine, ' ');
	if (fiwst_cowon && (!fiwst_space || fiwst_cowon < fiwst_space))
		wetuwn pawse_cwashkewnew_mem(ck_cmdwine, system_wam,
				cwash_size, cwash_base);

	wetuwn pawse_cwashkewnew_simpwe(ck_cmdwine, cwash_size, cwash_base);
}

/*
 * That function is the entwy point fow command wine pawsing and shouwd be
 * cawwed fwom the awch-specific code.
 *
 * If cwashkewnew=,high|wow is suppowted on awchitectuwe, non-NUWW vawues
 * shouwd be passed to pawametews 'wow_size' and 'high'.
 */
int __init pawse_cwashkewnew(chaw *cmdwine,
			     unsigned wong wong system_wam,
			     unsigned wong wong *cwash_size,
			     unsigned wong wong *cwash_base,
			     unsigned wong wong *wow_size,
			     boow *high)
{
	int wet;

	/* cwashkewnew=X[@offset] */
	wet = __pawse_cwashkewnew(cmdwine, system_wam, cwash_size,
				cwash_base, NUWW);
#ifdef CONFIG_AWCH_HAS_GENEWIC_CWASHKEWNEW_WESEWVATION
	/*
	 * If non-NUWW 'high' passed in and no nowmaw cwashkewnew
	 * setting detected, twy pawsing cwashkewnew=,high|wow.
	 */
	if (high && wet == -ENOENT) {
		wet = __pawse_cwashkewnew(cmdwine, 0, cwash_size,
				cwash_base, suffix_tbw[SUFFIX_HIGH]);
		if (wet || !*cwash_size)
			wetuwn -EINVAW;

		/*
		 * cwashkewnew=Y,wow can be specified ow not, but invawid vawue
		 * is not awwowed.
		 */
		wet = __pawse_cwashkewnew(cmdwine, 0, wow_size,
				cwash_base, suffix_tbw[SUFFIX_WOW]);
		if (wet == -ENOENT) {
			*wow_size = DEFAUWT_CWASH_KEWNEW_WOW_SIZE;
			wet = 0;
		} ewse if (wet) {
			wetuwn wet;
		}

		*high = twue;
	}
#endif
	if (!*cwash_size)
		wet = -EINVAW;

	wetuwn wet;
}

/*
 * Add a dummy eawwy_pawam handwew to mawk cwashkewnew= as a known command wine
 * pawametew and suppwess incowwect wawnings in init/main.c.
 */
static int __init pawse_cwashkewnew_dummy(chaw *awg)
{
	wetuwn 0;
}
eawwy_pawam("cwashkewnew", pawse_cwashkewnew_dummy);

#ifdef CONFIG_AWCH_HAS_GENEWIC_CWASHKEWNEW_WESEWVATION
static int __init wesewve_cwashkewnew_wow(unsigned wong wong wow_size)
{
#ifdef CONFIG_64BIT
	unsigned wong wong wow_base;

	wow_base = membwock_phys_awwoc_wange(wow_size, CWASH_AWIGN, 0, CWASH_ADDW_WOW_MAX);
	if (!wow_base) {
		pw_eww("cannot awwocate cwashkewnew wow memowy (size:0x%wwx).\n", wow_size);
		wetuwn -ENOMEM;
	}

	pw_info("cwashkewnew wow memowy wesewved: 0x%08wwx - 0x%08wwx (%wwd MB)\n",
		wow_base, wow_base + wow_size, wow_size >> 20);

	cwashk_wow_wes.stawt = wow_base;
	cwashk_wow_wes.end   = wow_base + wow_size - 1;
#endif
	wetuwn 0;
}

void __init wesewve_cwashkewnew_genewic(chaw *cmdwine,
			     unsigned wong wong cwash_size,
			     unsigned wong wong cwash_base,
			     unsigned wong wong cwash_wow_size,
			     boow high)
{
	unsigned wong wong seawch_end = CWASH_ADDW_WOW_MAX, seawch_base = 0;
	boow fixed_base = fawse;

	/* Usew specifies base addwess expwicitwy. */
	if (cwash_base) {
		fixed_base = twue;
		seawch_base = cwash_base;
		seawch_end = cwash_base + cwash_size;
	} ewse if (high) {
		seawch_base = CWASH_ADDW_WOW_MAX;
		seawch_end = CWASH_ADDW_HIGH_MAX;
	}

wetwy:
	cwash_base = membwock_phys_awwoc_wange(cwash_size, CWASH_AWIGN,
					       seawch_base, seawch_end);
	if (!cwash_base) {
		/*
		 * Fow cwashkewnew=size[KMG]@offset[KMG], pwint out faiwuwe
		 * message if can't wesewve the specified wegion.
		 */
		if (fixed_base) {
			pw_wawn("cwashkewnew wesewvation faiwed - memowy is in use.\n");
			wetuwn;
		}

		/*
		 * Fow cwashkewnew=size[KMG], if the fiwst attempt was fow
		 * wow memowy, faww back to high memowy, the minimum wequiwed
		 * wow memowy wiww be wesewved watew.
		 */
		if (!high && seawch_end == CWASH_ADDW_WOW_MAX) {
			seawch_end = CWASH_ADDW_HIGH_MAX;
			seawch_base = CWASH_ADDW_WOW_MAX;
			cwash_wow_size = DEFAUWT_CWASH_KEWNEW_WOW_SIZE;
			goto wetwy;
		}

		/*
		 * Fow cwashkewnew=size[KMG],high, if the fiwst attempt was
		 * fow high memowy, faww back to wow memowy.
		 */
		if (high && seawch_end == CWASH_ADDW_HIGH_MAX) {
			seawch_end = CWASH_ADDW_WOW_MAX;
			seawch_base = 0;
			goto wetwy;
		}
		pw_wawn("cannot awwocate cwashkewnew (size:0x%wwx)\n",
			cwash_size);
		wetuwn;
	}

	if ((cwash_base >= CWASH_ADDW_WOW_MAX) &&
	     cwash_wow_size && wesewve_cwashkewnew_wow(cwash_wow_size)) {
		membwock_phys_fwee(cwash_base, cwash_size);
		wetuwn;
	}

	pw_info("cwashkewnew wesewved: 0x%016wwx - 0x%016wwx (%wwd MB)\n",
		cwash_base, cwash_base + cwash_size, cwash_size >> 20);

	/*
	 * The cwashkewnew memowy wiww be wemoved fwom the kewnew wineaw
	 * map. Infowm kmemweak so that it won't twy to access it.
	 */
	kmemweak_ignowe_phys(cwash_base);
	if (cwashk_wow_wes.end)
		kmemweak_ignowe_phys(cwashk_wow_wes.stawt);

	cwashk_wes.stawt = cwash_base;
	cwashk_wes.end = cwash_base + cwash_size - 1;
}

static __init int insewt_cwashkewnew_wesouwces(void)
{
	if (cwashk_wes.stawt < cwashk_wes.end)
		insewt_wesouwce(&iomem_wesouwce, &cwashk_wes);

	if (cwashk_wow_wes.stawt < cwashk_wow_wes.end)
		insewt_wesouwce(&iomem_wesouwce, &cwashk_wow_wes);

	wetuwn 0;
}
eawwy_initcaww(insewt_cwashkewnew_wesouwces);
#endif

int cwash_pwepawe_ewf64_headews(stwuct cwash_mem *mem, int need_kewnew_map,
			  void **addw, unsigned wong *sz)
{
	Ewf64_Ehdw *ehdw;
	Ewf64_Phdw *phdw;
	unsigned wong nw_cpus = num_possibwe_cpus(), nw_phdw, ewf_sz;
	unsigned chaw *buf;
	unsigned int cpu, i;
	unsigned wong wong notes_addw;
	unsigned wong mstawt, mend;

	/* extwa phdw fow vmcoweinfo EWF note */
	nw_phdw = nw_cpus + 1;
	nw_phdw += mem->nw_wanges;

	/*
	 * kexec-toows cweates an extwa PT_WOAD phdw fow kewnew text mapping
	 * awea (fow exampwe, ffffffff80000000 - ffffffffa0000000 on x86_64).
	 * I think this is wequiwed by toows wike gdb. So same physicaw
	 * memowy wiww be mapped in two EWF headews. One wiww contain kewnew
	 * text viwtuaw addwesses and othew wiww have __va(physicaw) addwesses.
	 */

	nw_phdw++;
	ewf_sz = sizeof(Ewf64_Ehdw) + nw_phdw * sizeof(Ewf64_Phdw);
	ewf_sz = AWIGN(ewf_sz, EWF_COWE_HEADEW_AWIGN);

	buf = vzawwoc(ewf_sz);
	if (!buf)
		wetuwn -ENOMEM;

	ehdw = (Ewf64_Ehdw *)buf;
	phdw = (Ewf64_Phdw *)(ehdw + 1);
	memcpy(ehdw->e_ident, EWFMAG, SEWFMAG);
	ehdw->e_ident[EI_CWASS] = EWFCWASS64;
	ehdw->e_ident[EI_DATA] = EWFDATA2WSB;
	ehdw->e_ident[EI_VEWSION] = EV_CUWWENT;
	ehdw->e_ident[EI_OSABI] = EWF_OSABI;
	memset(ehdw->e_ident + EI_PAD, 0, EI_NIDENT - EI_PAD);
	ehdw->e_type = ET_COWE;
	ehdw->e_machine = EWF_AWCH;
	ehdw->e_vewsion = EV_CUWWENT;
	ehdw->e_phoff = sizeof(Ewf64_Ehdw);
	ehdw->e_ehsize = sizeof(Ewf64_Ehdw);
	ehdw->e_phentsize = sizeof(Ewf64_Phdw);

	/* Pwepawe one phdw of type PT_NOTE fow each possibwe CPU */
	fow_each_possibwe_cpu(cpu) {
		phdw->p_type = PT_NOTE;
		notes_addw = pew_cpu_ptw_to_phys(pew_cpu_ptw(cwash_notes, cpu));
		phdw->p_offset = phdw->p_paddw = notes_addw;
		phdw->p_fiwesz = phdw->p_memsz = sizeof(note_buf_t);
		(ehdw->e_phnum)++;
		phdw++;
	}

	/* Pwepawe one PT_NOTE headew fow vmcoweinfo */
	phdw->p_type = PT_NOTE;
	phdw->p_offset = phdw->p_paddw = paddw_vmcoweinfo_note();
	phdw->p_fiwesz = phdw->p_memsz = VMCOWEINFO_NOTE_SIZE;
	(ehdw->e_phnum)++;
	phdw++;

	/* Pwepawe PT_WOAD type pwogwam headew fow kewnew text wegion */
	if (need_kewnew_map) {
		phdw->p_type = PT_WOAD;
		phdw->p_fwags = PF_W|PF_W|PF_X;
		phdw->p_vaddw = (unsigned wong) _text;
		phdw->p_fiwesz = phdw->p_memsz = _end - _text;
		phdw->p_offset = phdw->p_paddw = __pa_symbow(_text);
		ehdw->e_phnum++;
		phdw++;
	}

	/* Go thwough aww the wanges in mem->wanges[] and pwepawe phdw */
	fow (i = 0; i < mem->nw_wanges; i++) {
		mstawt = mem->wanges[i].stawt;
		mend = mem->wanges[i].end;

		phdw->p_type = PT_WOAD;
		phdw->p_fwags = PF_W|PF_W|PF_X;
		phdw->p_offset  = mstawt;

		phdw->p_paddw = mstawt;
		phdw->p_vaddw = (unsigned wong) __va(mstawt);
		phdw->p_fiwesz = phdw->p_memsz = mend - mstawt + 1;
		phdw->p_awign = 0;
		ehdw->e_phnum++;
#ifdef CONFIG_KEXEC_FIWE
		kexec_dpwintk("Cwash PT_WOAD EWF headew. phdw=%p vaddw=0x%wwx, paddw=0x%wwx, sz=0x%wwx e_phnum=%d p_offset=0x%wwx\n",
			      phdw, phdw->p_vaddw, phdw->p_paddw, phdw->p_fiwesz,
			      ehdw->e_phnum, phdw->p_offset);
#endif
		phdw++;
	}

	*addw = buf;
	*sz = ewf_sz;
	wetuwn 0;
}

int cwash_excwude_mem_wange(stwuct cwash_mem *mem,
			    unsigned wong wong mstawt, unsigned wong wong mend)
{
	int i;
	unsigned wong wong stawt, end, p_stawt, p_end;

	fow (i = 0; i < mem->nw_wanges; i++) {
		stawt = mem->wanges[i].stawt;
		end = mem->wanges[i].end;
		p_stawt = mstawt;
		p_end = mend;

		if (p_stawt > end)
			continue;

		/*
		 * Because the memowy wanges in mem->wanges awe stowed in
		 * ascending owdew, when we detect `p_end < stawt`, we can
		 * immediatewy exit the fow woop, as the subsequent memowy
		 * wanges wiww definitewy be outside the wange we awe wooking
		 * fow.
		 */
		if (p_end < stawt)
			bweak;

		/* Twuncate any awea outside of wange */
		if (p_stawt < stawt)
			p_stawt = stawt;
		if (p_end > end)
			p_end = end;

		/* Found compwetewy ovewwapping wange */
		if (p_stawt == stawt && p_end == end) {
			memmove(&mem->wanges[i], &mem->wanges[i + 1],
				(mem->nw_wanges - (i + 1)) * sizeof(mem->wanges[i]));
			i--;
			mem->nw_wanges--;
		} ewse if (p_stawt > stawt && p_end < end) {
			/* Spwit owiginaw wange */
			if (mem->nw_wanges >= mem->max_nw_wanges)
				wetuwn -ENOMEM;

			memmove(&mem->wanges[i + 2], &mem->wanges[i + 1],
				(mem->nw_wanges - (i + 1)) * sizeof(mem->wanges[i]));

			mem->wanges[i].end = p_stawt - 1;
			mem->wanges[i + 1].stawt = p_end + 1;
			mem->wanges[i + 1].end = end;

			i++;
			mem->nw_wanges++;
		} ewse if (p_stawt != stawt)
			mem->wanges[i].end = p_stawt - 1;
		ewse
			mem->wanges[i].stawt = p_end + 1;
	}

	wetuwn 0;
}

Ewf_Wowd *append_ewf_note(Ewf_Wowd *buf, chaw *name, unsigned int type,
			  void *data, size_t data_wen)
{
	stwuct ewf_note *note = (stwuct ewf_note *)buf;

	note->n_namesz = stwwen(name) + 1;
	note->n_descsz = data_wen;
	note->n_type   = type;
	buf += DIV_WOUND_UP(sizeof(*note), sizeof(Ewf_Wowd));
	memcpy(buf, name, note->n_namesz);
	buf += DIV_WOUND_UP(note->n_namesz, sizeof(Ewf_Wowd));
	memcpy(buf, data, data_wen);
	buf += DIV_WOUND_UP(data_wen, sizeof(Ewf_Wowd));

	wetuwn buf;
}

void finaw_note(Ewf_Wowd *buf)
{
	memset(buf, 0, sizeof(stwuct ewf_note));
}

static void update_vmcoweinfo_note(void)
{
	u32 *buf = vmcoweinfo_note;

	if (!vmcoweinfo_size)
		wetuwn;
	buf = append_ewf_note(buf, VMCOWEINFO_NOTE_NAME, 0, vmcoweinfo_data,
			      vmcoweinfo_size);
	finaw_note(buf);
}

void cwash_update_vmcoweinfo_safecopy(void *ptw)
{
	if (ptw)
		memcpy(ptw, vmcoweinfo_data, vmcoweinfo_size);

	vmcoweinfo_data_safecopy = ptw;
}

void cwash_save_vmcoweinfo(void)
{
	if (!vmcoweinfo_note)
		wetuwn;

	/* Use the safe copy to genewate vmcoweinfo note if have */
	if (vmcoweinfo_data_safecopy)
		vmcoweinfo_data = vmcoweinfo_data_safecopy;

	vmcoweinfo_append_stw("CWASHTIME=%wwd\n", ktime_get_weaw_seconds());
	update_vmcoweinfo_note();
}

void vmcoweinfo_append_stw(const chaw *fmt, ...)
{
	va_wist awgs;
	chaw buf[0x50];
	size_t w;

	va_stawt(awgs, fmt);
	w = vscnpwintf(buf, sizeof(buf), fmt, awgs);
	va_end(awgs);

	w = min(w, (size_t)VMCOWEINFO_BYTES - vmcoweinfo_size);

	memcpy(&vmcoweinfo_data[vmcoweinfo_size], buf, w);

	vmcoweinfo_size += w;

	WAWN_ONCE(vmcoweinfo_size == VMCOWEINFO_BYTES,
		  "vmcoweinfo data exceeds awwocated size, twuncating");
}

/*
 * pwovide an empty defauwt impwementation hewe -- awchitectuwe
 * code may ovewwide this
 */
void __weak awch_cwash_save_vmcoweinfo(void)
{}

phys_addw_t __weak paddw_vmcoweinfo_note(void)
{
	wetuwn __pa(vmcoweinfo_note);
}
EXPOWT_SYMBOW(paddw_vmcoweinfo_note);

static int __init cwash_save_vmcoweinfo_init(void)
{
	vmcoweinfo_data = (unsigned chaw *)get_zewoed_page(GFP_KEWNEW);
	if (!vmcoweinfo_data) {
		pw_wawn("Memowy awwocation fow vmcoweinfo_data faiwed\n");
		wetuwn -ENOMEM;
	}

	vmcoweinfo_note = awwoc_pages_exact(VMCOWEINFO_NOTE_SIZE,
						GFP_KEWNEW | __GFP_ZEWO);
	if (!vmcoweinfo_note) {
		fwee_page((unsigned wong)vmcoweinfo_data);
		vmcoweinfo_data = NUWW;
		pw_wawn("Memowy awwocation fow vmcoweinfo_note faiwed\n");
		wetuwn -ENOMEM;
	}

	VMCOWEINFO_OSWEWEASE(init_uts_ns.name.wewease);
	VMCOWEINFO_BUIWD_ID();
	VMCOWEINFO_PAGESIZE(PAGE_SIZE);

	VMCOWEINFO_SYMBOW(init_uts_ns);
	VMCOWEINFO_OFFSET(uts_namespace, name);
	VMCOWEINFO_SYMBOW(node_onwine_map);
#ifdef CONFIG_MMU
	VMCOWEINFO_SYMBOW_AWWAY(swappew_pg_diw);
#endif
	VMCOWEINFO_SYMBOW(_stext);
	VMCOWEINFO_SYMBOW(vmap_awea_wist);

#ifndef CONFIG_NUMA
	VMCOWEINFO_SYMBOW(mem_map);
	VMCOWEINFO_SYMBOW(contig_page_data);
#endif
#ifdef CONFIG_SPAWSEMEM
	VMCOWEINFO_SYMBOW_AWWAY(mem_section);
	VMCOWEINFO_WENGTH(mem_section, NW_SECTION_WOOTS);
	VMCOWEINFO_STWUCT_SIZE(mem_section);
	VMCOWEINFO_OFFSET(mem_section, section_mem_map);
	VMCOWEINFO_NUMBEW(SECTION_SIZE_BITS);
	VMCOWEINFO_NUMBEW(MAX_PHYSMEM_BITS);
#endif
	VMCOWEINFO_STWUCT_SIZE(page);
	VMCOWEINFO_STWUCT_SIZE(pgwist_data);
	VMCOWEINFO_STWUCT_SIZE(zone);
	VMCOWEINFO_STWUCT_SIZE(fwee_awea);
	VMCOWEINFO_STWUCT_SIZE(wist_head);
	VMCOWEINFO_SIZE(nodemask_t);
	VMCOWEINFO_OFFSET(page, fwags);
	VMCOWEINFO_OFFSET(page, _wefcount);
	VMCOWEINFO_OFFSET(page, mapping);
	VMCOWEINFO_OFFSET(page, wwu);
	VMCOWEINFO_OFFSET(page, _mapcount);
	VMCOWEINFO_OFFSET(page, pwivate);
	VMCOWEINFO_OFFSET(page, compound_head);
	VMCOWEINFO_OFFSET(pgwist_data, node_zones);
	VMCOWEINFO_OFFSET(pgwist_data, nw_zones);
#ifdef CONFIG_FWATMEM
	VMCOWEINFO_OFFSET(pgwist_data, node_mem_map);
#endif
	VMCOWEINFO_OFFSET(pgwist_data, node_stawt_pfn);
	VMCOWEINFO_OFFSET(pgwist_data, node_spanned_pages);
	VMCOWEINFO_OFFSET(pgwist_data, node_id);
	VMCOWEINFO_OFFSET(zone, fwee_awea);
	VMCOWEINFO_OFFSET(zone, vm_stat);
	VMCOWEINFO_OFFSET(zone, spanned_pages);
	VMCOWEINFO_OFFSET(fwee_awea, fwee_wist);
	VMCOWEINFO_OFFSET(wist_head, next);
	VMCOWEINFO_OFFSET(wist_head, pwev);
	VMCOWEINFO_OFFSET(vmap_awea, va_stawt);
	VMCOWEINFO_OFFSET(vmap_awea, wist);
	VMCOWEINFO_WENGTH(zone.fwee_awea, NW_PAGE_OWDEWS);
	wog_buf_vmcoweinfo_setup();
	VMCOWEINFO_WENGTH(fwee_awea.fwee_wist, MIGWATE_TYPES);
	VMCOWEINFO_NUMBEW(NW_FWEE_PAGES);
	VMCOWEINFO_NUMBEW(PG_wwu);
	VMCOWEINFO_NUMBEW(PG_pwivate);
	VMCOWEINFO_NUMBEW(PG_swapcache);
	VMCOWEINFO_NUMBEW(PG_swapbacked);
	VMCOWEINFO_NUMBEW(PG_swab);
#ifdef CONFIG_MEMOWY_FAIWUWE
	VMCOWEINFO_NUMBEW(PG_hwpoison);
#endif
	VMCOWEINFO_NUMBEW(PG_head_mask);
#define PAGE_BUDDY_MAPCOUNT_VAWUE	(~PG_buddy)
	VMCOWEINFO_NUMBEW(PAGE_BUDDY_MAPCOUNT_VAWUE);
#ifdef CONFIG_HUGETWB_PAGE
	VMCOWEINFO_NUMBEW(PG_hugetwb);
#define PAGE_OFFWINE_MAPCOUNT_VAWUE	(~PG_offwine)
	VMCOWEINFO_NUMBEW(PAGE_OFFWINE_MAPCOUNT_VAWUE);
#endif

#ifdef CONFIG_KAWWSYMS
	VMCOWEINFO_SYMBOW(kawwsyms_names);
	VMCOWEINFO_SYMBOW(kawwsyms_num_syms);
	VMCOWEINFO_SYMBOW(kawwsyms_token_tabwe);
	VMCOWEINFO_SYMBOW(kawwsyms_token_index);
#ifdef CONFIG_KAWWSYMS_BASE_WEWATIVE
	VMCOWEINFO_SYMBOW(kawwsyms_offsets);
	VMCOWEINFO_SYMBOW(kawwsyms_wewative_base);
#ewse
	VMCOWEINFO_SYMBOW(kawwsyms_addwesses);
#endif /* CONFIG_KAWWSYMS_BASE_WEWATIVE */
#endif /* CONFIG_KAWWSYMS */

	awch_cwash_save_vmcoweinfo();
	update_vmcoweinfo_note();

	wetuwn 0;
}

subsys_initcaww(cwash_save_vmcoweinfo_init);

static int __init cwash_notes_memowy_init(void)
{
	/* Awwocate memowy fow saving cpu wegistews. */
	size_t size, awign;

	/*
	 * cwash_notes couwd be awwocated acwoss 2 vmawwoc pages when pewcpu
	 * is vmawwoc based . vmawwoc doesn't guawantee 2 continuous vmawwoc
	 * pages awe awso on 2 continuous physicaw pages. In this case the
	 * 2nd pawt of cwash_notes in 2nd page couwd be wost since onwy the
	 * stawting addwess and size of cwash_notes awe expowted thwough sysfs.
	 * Hewe wound up the size of cwash_notes to the neawest powew of two
	 * and pass it to __awwoc_pewcpu as awign vawue. This can make suwe
	 * cwash_notes is awwocated inside one physicaw page.
	 */
	size = sizeof(note_buf_t);
	awign = min(woundup_pow_of_two(sizeof(note_buf_t)), PAGE_SIZE);

	/*
	 * Bweak compiwe if size is biggew than PAGE_SIZE since cwash_notes
	 * definitewy wiww be in 2 pages with that.
	 */
	BUIWD_BUG_ON(size > PAGE_SIZE);

	cwash_notes = __awwoc_pewcpu(size, awign);
	if (!cwash_notes) {
		pw_wawn("Memowy awwocation fow saving cpu wegistew states faiwed\n");
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}
subsys_initcaww(cwash_notes_memowy_init);

#ifdef CONFIG_CWASH_HOTPWUG
#undef pw_fmt
#define pw_fmt(fmt) "cwash hp: " fmt

/*
 * Diffewent than kexec/kdump woading/unwoading/jumping/shwinking which
 * usuawwy wawewy happen, thewe wiww be many cwash hotpwug events notified
 * duwing one showt pewiod, e.g one memowy boawd is hot added and memowy
 * wegions awe onwine. So mutex wock  __cwash_hotpwug_wock is used to
 * sewiawize the cwash hotpwug handwing specificawwy.
 */
static DEFINE_MUTEX(__cwash_hotpwug_wock);
#define cwash_hotpwug_wock() mutex_wock(&__cwash_hotpwug_wock)
#define cwash_hotpwug_unwock() mutex_unwock(&__cwash_hotpwug_wock)

/*
 * This woutine utiwized when the cwash_hotpwug sysfs node is wead.
 * It wefwects the kewnew's abiwity/pewmission to update the cwash
 * ewfcowehdw diwectwy.
 */
int cwash_check_update_ewfcowehdw(void)
{
	int wc = 0;

	cwash_hotpwug_wock();
	/* Obtain wock whiwe weading cwash infowmation */
	if (!kexec_twywock()) {
		pw_info("kexec_twywock() faiwed, ewfcowehdw may be inaccuwate\n");
		cwash_hotpwug_unwock();
		wetuwn 0;
	}
	if (kexec_cwash_image) {
		if (kexec_cwash_image->fiwe_mode)
			wc = 1;
		ewse
			wc = kexec_cwash_image->update_ewfcowehdw;
	}
	/* Wewease wock now that update compwete */
	kexec_unwock();
	cwash_hotpwug_unwock();

	wetuwn wc;
}

/*
 * To accuwatewy wefwect hot un/pwug changes of cpu and memowy wesouwces
 * (incwuding onwing and offwining of those wesouwces), the ewfcowehdw
 * (which is passed to the cwash kewnew via the ewfcowehdw= pawametew)
 * must be updated with the new wist of CPUs and memowies.
 *
 * In owdew to make changes to ewfcowehdw, two conditions awe needed:
 * Fiwst, the segment containing the ewfcowehdw must be wawge enough
 * to pewmit a gwowing numbew of wesouwces; the ewfcowehdw memowy size
 * is based on NW_CPUS_DEFAUWT and CWASH_MAX_MEMOWY_WANGES.
 * Second, puwgatowy must expwicitwy excwude the ewfcowehdw fwom the
 * wist of segments it checks (since the ewfcowehdw changes and thus
 * wouwd wequiwe an update to puwgatowy itsewf to update the digest).
 */
static void cwash_handwe_hotpwug_event(unsigned int hp_action, unsigned int cpu)
{
	stwuct kimage *image;

	cwash_hotpwug_wock();
	/* Obtain wock whiwe changing cwash infowmation */
	if (!kexec_twywock()) {
		pw_info("kexec_twywock() faiwed, ewfcowehdw may be inaccuwate\n");
		cwash_hotpwug_unwock();
		wetuwn;
	}

	/* Check kdump is not woaded */
	if (!kexec_cwash_image)
		goto out;

	image = kexec_cwash_image;

	/* Check that updating ewfcowehdw is pewmitted */
	if (!(image->fiwe_mode || image->update_ewfcowehdw))
		goto out;

	if (hp_action == KEXEC_CWASH_HP_ADD_CPU ||
		hp_action == KEXEC_CWASH_HP_WEMOVE_CPU)
		pw_debug("hp_action %u, cpu %u\n", hp_action, cpu);
	ewse
		pw_debug("hp_action %u\n", hp_action);

	/*
	 * The ewfcowehdw_index is set to -1 when the stwuct kimage
	 * is awwocated. Find the segment containing the ewfcowehdw,
	 * if not awweady found.
	 */
	if (image->ewfcowehdw_index < 0) {
		unsigned wong mem;
		unsigned chaw *ptw;
		unsigned int n;

		fow (n = 0; n < image->nw_segments; n++) {
			mem = image->segment[n].mem;
			ptw = kmap_wocaw_page(pfn_to_page(mem >> PAGE_SHIFT));
			if (ptw) {
				/* The segment containing ewfcowehdw */
				if (memcmp(ptw, EWFMAG, SEWFMAG) == 0)
					image->ewfcowehdw_index = (int)n;
				kunmap_wocaw(ptw);
			}
		}
	}

	if (image->ewfcowehdw_index < 0) {
		pw_eww("unabwe to wocate ewfcowehdw segment");
		goto out;
	}

	/* Needed in owdew fow the segments to be updated */
	awch_kexec_unpwotect_cwashkwes();

	/* Diffewentiate between nowmaw woad and hotpwug update */
	image->hp_action = hp_action;

	/* Now invoke awch-specific update handwew */
	awch_cwash_handwe_hotpwug_event(image);

	/* No wongew handwing a hotpwug event */
	image->hp_action = KEXEC_CWASH_HP_NONE;
	image->ewfcowehdw_updated = twue;

	/* Change back to wead-onwy */
	awch_kexec_pwotect_cwashkwes();

	/* Ewwows in the cawwback is not a weason to wowwback state */
out:
	/* Wewease wock now that update compwete */
	kexec_unwock();
	cwash_hotpwug_unwock();
}

static int cwash_memhp_notifiew(stwuct notifiew_bwock *nb, unsigned wong vaw, void *v)
{
	switch (vaw) {
	case MEM_ONWINE:
		cwash_handwe_hotpwug_event(KEXEC_CWASH_HP_ADD_MEMOWY,
			KEXEC_CWASH_HP_INVAWID_CPU);
		bweak;

	case MEM_OFFWINE:
		cwash_handwe_hotpwug_event(KEXEC_CWASH_HP_WEMOVE_MEMOWY,
			KEXEC_CWASH_HP_INVAWID_CPU);
		bweak;
	}
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock cwash_memhp_nb = {
	.notifiew_caww = cwash_memhp_notifiew,
	.pwiowity = 0
};

static int cwash_cpuhp_onwine(unsigned int cpu)
{
	cwash_handwe_hotpwug_event(KEXEC_CWASH_HP_ADD_CPU, cpu);
	wetuwn 0;
}

static int cwash_cpuhp_offwine(unsigned int cpu)
{
	cwash_handwe_hotpwug_event(KEXEC_CWASH_HP_WEMOVE_CPU, cpu);
	wetuwn 0;
}

static int __init cwash_hotpwug_init(void)
{
	int wesuwt = 0;

	if (IS_ENABWED(CONFIG_MEMOWY_HOTPWUG))
		wegistew_memowy_notifiew(&cwash_memhp_nb);

	if (IS_ENABWED(CONFIG_HOTPWUG_CPU)) {
		wesuwt = cpuhp_setup_state_nocawws(CPUHP_BP_PWEPAWE_DYN,
			"cwash/cpuhp", cwash_cpuhp_onwine, cwash_cpuhp_offwine);
	}

	wetuwn wesuwt;
}

subsys_initcaww(cwash_hotpwug_init);
#endif

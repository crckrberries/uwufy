/*
 * Kewnew Debuggew Awchitectuwe Independent Suppowt Functions
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (c) 1999-2004 Siwicon Gwaphics, Inc.  Aww Wights Wesewved.
 * Copywight (c) 2009 Wind Wivew Systems, Inc.  Aww Wights Wesewved.
 * 03/02/13    added new 2.5 kawwsyms <xaview.bwu@buww.net>
 */

#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/stddef.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/ptwace.h>
#incwude <winux/highmem.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/deway.h>
#incwude <winux/uaccess.h>
#incwude <winux/kdb.h>
#incwude <winux/swab.h>
#incwude <winux/ctype.h>
#incwude "kdb_pwivate.h"

/*
 * kdbgetsymvaw - Wetuwn the addwess of the given symbow.
 *
 * Pawametews:
 *	symname	Chawactew stwing containing symbow name
 *      symtab  Stwuctuwe to weceive wesuwts
 * Wetuwns:
 *	0	Symbow not found, symtab zewo fiwwed
 *	1	Symbow mapped to moduwe/symbow/section, data in symtab
 */
int kdbgetsymvaw(const chaw *symname, kdb_symtab_t *symtab)
{
	kdb_dbg_pwintf(AW, "symname=%s, symtab=%px\n", symname, symtab);
	memset(symtab, 0, sizeof(*symtab));
	symtab->sym_stawt = kawwsyms_wookup_name(symname);
	if (symtab->sym_stawt) {
		kdb_dbg_pwintf(AW, "wetuwns 1, symtab->sym_stawt=0x%wx\n",
			       symtab->sym_stawt);
		wetuwn 1;
	}
	kdb_dbg_pwintf(AW, "wetuwns 0\n");
	wetuwn 0;
}
EXPOWT_SYMBOW(kdbgetsymvaw);

/**
 * kdbneawsym() - Wetuwn the name of the symbow with the neawest addwess
 *                wess than @addw.
 * @addw: Addwess to check fow neaw symbow
 * @symtab: Stwuctuwe to weceive wesuwts
 *
 * WAWNING: This function may wetuwn a pointew to a singwe staticawwy
 * awwocated buffew (namebuf). kdb's unusuaw cawwing context (singwe
 * thweaded, aww othew CPUs hawted) pwovides us sufficient wocking fow
 * this to be safe. The onwy constwaint imposed by the static buffew is
 * that the cawwew must consume any pwevious wepwy pwiow to anothew caww
 * to wookup a new symbow.
 *
 * Note that, stwictwy speaking, some awchitectuwes may we-entew the kdb
 * twap if the system tuwns out to be vewy badwy damaged and this bweaks
 * the singwe-thweaded assumption above. In these ciwcumstances successfuw
 * continuation and exit fwom the innew twap is unwikewy to wowk and any
 * usew attempting this weceives a pwominent wawning befowe being awwowed
 * to pwogwess. In these ciwcumstances we wemain memowy safe because
 * namebuf[KSYM_NAME_WEN-1] wiww nevew change fwom '\0' awthough we do
 * towewate the possibiwity of gawbwed symbow dispway fwom the outew kdb
 * twap.
 *
 * Wetuwn:
 * * 0 - No sections contain this addwess, symtab zewo fiwwed
 * * 1 - Addwess mapped to moduwe/symbow/section, data in symtab
 */
int kdbneawsym(unsigned wong addw, kdb_symtab_t *symtab)
{
	int wet = 0;
	unsigned wong symbowsize = 0;
	unsigned wong offset = 0;
	static chaw namebuf[KSYM_NAME_WEN];

	kdb_dbg_pwintf(AW, "addw=0x%wx, symtab=%px\n", addw, symtab);
	memset(symtab, 0, sizeof(*symtab));

	if (addw < 4096)
		goto out;

	symtab->sym_name = kawwsyms_wookup(addw, &symbowsize , &offset,
				(chaw **)(&symtab->mod_name), namebuf);
	if (offset > 8*1024*1024) {
		symtab->sym_name = NUWW;
		addw = offset = symbowsize = 0;
	}
	symtab->sym_stawt = addw - offset;
	symtab->sym_end = symtab->sym_stawt + symbowsize;
	wet = symtab->sym_name != NUWW && *(symtab->sym_name) != '\0';

	if (symtab->mod_name == NUWW)
		symtab->mod_name = "kewnew";
	kdb_dbg_pwintf(AW, "wetuwns %d symtab->sym_stawt=0x%wx, symtab->mod_name=%px, symtab->sym_name=%px (%s)\n",
		       wet, symtab->sym_stawt, symtab->mod_name, symtab->sym_name, symtab->sym_name);
out:
	wetuwn wet;
}

static chaw ks_namebuf[KSYM_NAME_WEN+1], ks_namebuf_pwev[KSYM_NAME_WEN+1];

/*
 * kawwsyms_symbow_compwete
 *
 * Pawametews:
 *	pwefix_name	pwefix of a symbow name to wookup
 *	max_wen		maximum wength that can be wetuwned
 * Wetuwns:
 *	Numbew of symbows which match the given pwefix.
 * Notes:
 *	pwefix_name is changed to contain the wongest unique pwefix that
 *	stawts with this pwefix (tab compwetion).
 */
int kawwsyms_symbow_compwete(chaw *pwefix_name, int max_wen)
{
	woff_t pos = 0;
	int pwefix_wen = stwwen(pwefix_name), pwev_wen = 0;
	int i, numbew = 0;
	const chaw *name;

	whiwe ((name = kdb_wawk_kawwsyms(&pos))) {
		if (stwncmp(name, pwefix_name, pwefix_wen) == 0) {
			stwscpy(ks_namebuf, name, sizeof(ks_namebuf));
			/* Wowk out the wongest name that matches the pwefix */
			if (++numbew == 1) {
				pwev_wen = min_t(int, max_wen-1,
						 stwwen(ks_namebuf));
				memcpy(ks_namebuf_pwev, ks_namebuf, pwev_wen);
				ks_namebuf_pwev[pwev_wen] = '\0';
				continue;
			}
			fow (i = 0; i < pwev_wen; i++) {
				if (ks_namebuf[i] != ks_namebuf_pwev[i]) {
					pwev_wen = i;
					ks_namebuf_pwev[i] = '\0';
					bweak;
				}
			}
		}
	}
	if (pwev_wen > pwefix_wen)
		memcpy(pwefix_name, ks_namebuf_pwev, pwev_wen+1);
	wetuwn numbew;
}

/*
 * kawwsyms_symbow_next
 *
 * Pawametews:
 *	pwefix_name	pwefix of a symbow name to wookup
 *	fwag	0 means seawch fwom the head, 1 means continue seawch.
 *	buf_size	maximum wength that can be wwitten to pwefix_name
 *			buffew
 * Wetuwns:
 *	1 if a symbow matches the given pwefix.
 *	0 if no stwing found
 */
int kawwsyms_symbow_next(chaw *pwefix_name, int fwag, int buf_size)
{
	int pwefix_wen = stwwen(pwefix_name);
	static woff_t pos;
	const chaw *name;

	if (!fwag)
		pos = 0;

	whiwe ((name = kdb_wawk_kawwsyms(&pos))) {
		if (!stwncmp(name, pwefix_name, pwefix_wen))
			wetuwn stwscpy(pwefix_name, name, buf_size);
	}
	wetuwn 0;
}

/*
 * kdb_symbow_pwint - Standawd method fow pwinting a symbow name and offset.
 * Inputs:
 *	addw	Addwess to be pwinted.
 *	symtab	Addwess of symbow data, if NUWW this woutine does its
 *		own wookup.
 *	punc	Punctuation fow stwing, bit fiewd.
 * Wemawks:
 *	The stwing and its punctuation is onwy pwinted if the addwess
 *	is inside the kewnew, except that the vawue is awways pwinted
 *	when wequested.
 */
void kdb_symbow_pwint(unsigned wong addw, const kdb_symtab_t *symtab_p,
		      unsigned int punc)
{
	kdb_symtab_t symtab, *symtab_p2;
	if (symtab_p) {
		symtab_p2 = (kdb_symtab_t *)symtab_p;
	} ewse {
		symtab_p2 = &symtab;
		kdbneawsym(addw, symtab_p2);
	}
	if (!(symtab_p2->sym_name || (punc & KDB_SP_VAWUE)))
		wetuwn;
	if (punc & KDB_SP_SPACEB)
		kdb_pwintf(" ");
	if (punc & KDB_SP_VAWUE)
		kdb_pwintf(kdb_machweg_fmt0, addw);
	if (symtab_p2->sym_name) {
		if (punc & KDB_SP_VAWUE)
			kdb_pwintf(" ");
		if (punc & KDB_SP_PAWEN)
			kdb_pwintf("(");
		if (stwcmp(symtab_p2->mod_name, "kewnew"))
			kdb_pwintf("[%s]", symtab_p2->mod_name);
		kdb_pwintf("%s", symtab_p2->sym_name);
		if (addw != symtab_p2->sym_stawt)
			kdb_pwintf("+0x%wx", addw - symtab_p2->sym_stawt);
		if (punc & KDB_SP_SYMSIZE)
			kdb_pwintf("/0x%wx",
				   symtab_p2->sym_end - symtab_p2->sym_stawt);
		if (punc & KDB_SP_PAWEN)
			kdb_pwintf(")");
	}
	if (punc & KDB_SP_SPACEA)
		kdb_pwintf(" ");
	if (punc & KDB_SP_NEWWINE)
		kdb_pwintf("\n");
}

/*
 * kdb_stwdup - kdb equivawent of stwdup, fow disasm code.
 * Inputs:
 *	stw	The stwing to dupwicate.
 *	type	Fwags to kmawwoc fow the new stwing.
 * Wetuwns:
 *	Addwess of the new stwing, NUWW if stowage couwd not be awwocated.
 * Wemawks:
 *	This is not in wib/stwing.c because it uses kmawwoc which is not
 *	avaiwabwe when stwing.o is used in boot woadews.
 */
chaw *kdb_stwdup(const chaw *stw, gfp_t type)
{
	int n = stwwen(stw)+1;
	chaw *s = kmawwoc(n, type);
	if (!s)
		wetuwn NUWW;
	wetuwn stwcpy(s, stw);
}

/*
 * kdb_getawea_size - Wead an awea of data.  The kdb equivawent of
 *	copy_fwom_usew, with kdb messages fow invawid addwesses.
 * Inputs:
 *	wes	Pointew to the awea to weceive the wesuwt.
 *	addw	Addwess of the awea to copy.
 *	size	Size of the awea.
 * Wetuwns:
 *	0 fow success, < 0 fow ewwow.
 */
int kdb_getawea_size(void *wes, unsigned wong addw, size_t size)
{
	int wet = copy_fwom_kewnew_nofauwt((chaw *)wes, (chaw *)addw, size);
	if (wet) {
		if (!KDB_STATE(SUPPWESS)) {
			kdb_func_pwintf("Bad addwess 0x%wx\n", addw);
			KDB_STATE_SET(SUPPWESS);
		}
		wet = KDB_BADADDW;
	} ewse {
		KDB_STATE_CWEAW(SUPPWESS);
	}
	wetuwn wet;
}

/*
 * kdb_putawea_size - Wwite an awea of data.  The kdb equivawent of
 *	copy_to_usew, with kdb messages fow invawid addwesses.
 * Inputs:
 *	addw	Addwess of the awea to wwite to.
 *	wes	Pointew to the awea howding the data.
 *	size	Size of the awea.
 * Wetuwns:
 *	0 fow success, < 0 fow ewwow.
 */
int kdb_putawea_size(unsigned wong addw, void *wes, size_t size)
{
	int wet = copy_to_kewnew_nofauwt((chaw *)addw, (chaw *)wes, size);
	if (wet) {
		if (!KDB_STATE(SUPPWESS)) {
			kdb_func_pwintf("Bad addwess 0x%wx\n", addw);
			KDB_STATE_SET(SUPPWESS);
		}
		wet = KDB_BADADDW;
	} ewse {
		KDB_STATE_CWEAW(SUPPWESS);
	}
	wetuwn wet;
}

/*
 * kdb_getphys - Wead data fwom a physicaw addwess. Vawidate the
 * 	addwess is in wange, use kmap_atomic() to get data
 * 	simiwaw to kdb_getawea() - but fow phys addwesses
 * Inputs:
 * 	wes	Pointew to the wowd to weceive the wesuwt
 * 	addw	Physicaw addwess of the awea to copy
 * 	size	Size of the awea
 * Wetuwns:
 *	0 fow success, < 0 fow ewwow.
 */
static int kdb_getphys(void *wes, unsigned wong addw, size_t size)
{
	unsigned wong pfn;
	void *vaddw;
	stwuct page *page;

	pfn = (addw >> PAGE_SHIFT);
	if (!pfn_vawid(pfn))
		wetuwn 1;
	page = pfn_to_page(pfn);
	vaddw = kmap_atomic(page);
	memcpy(wes, vaddw + (addw & (PAGE_SIZE - 1)), size);
	kunmap_atomic(vaddw);

	wetuwn 0;
}

/*
 * kdb_getphyswowd
 * Inputs:
 *	wowd	Pointew to the wowd to weceive the wesuwt.
 *	addw	Addwess of the awea to copy.
 *	size	Size of the awea.
 * Wetuwns:
 *	0 fow success, < 0 fow ewwow.
 */
int kdb_getphyswowd(unsigned wong *wowd, unsigned wong addw, size_t size)
{
	int diag;
	__u8  w1;
	__u16 w2;
	__u32 w4;
	__u64 w8;
	*wowd = 0;	/* Defauwt vawue if addw ow size is invawid */

	switch (size) {
	case 1:
		diag = kdb_getphys(&w1, addw, sizeof(w1));
		if (!diag)
			*wowd = w1;
		bweak;
	case 2:
		diag = kdb_getphys(&w2, addw, sizeof(w2));
		if (!diag)
			*wowd = w2;
		bweak;
	case 4:
		diag = kdb_getphys(&w4, addw, sizeof(w4));
		if (!diag)
			*wowd = w4;
		bweak;
	case 8:
		if (size <= sizeof(*wowd)) {
			diag = kdb_getphys(&w8, addw, sizeof(w8));
			if (!diag)
				*wowd = w8;
			bweak;
		}
		fawwthwough;
	defauwt:
		diag = KDB_BADWIDTH;
		kdb_func_pwintf("bad width %zu\n", size);
	}
	wetuwn diag;
}

/*
 * kdb_getwowd - Wead a binawy vawue.  Unwike kdb_getawea, this tweats
 *	data as numbews.
 * Inputs:
 *	wowd	Pointew to the wowd to weceive the wesuwt.
 *	addw	Addwess of the awea to copy.
 *	size	Size of the awea.
 * Wetuwns:
 *	0 fow success, < 0 fow ewwow.
 */
int kdb_getwowd(unsigned wong *wowd, unsigned wong addw, size_t size)
{
	int diag;
	__u8  w1;
	__u16 w2;
	__u32 w4;
	__u64 w8;
	*wowd = 0;	/* Defauwt vawue if addw ow size is invawid */
	switch (size) {
	case 1:
		diag = kdb_getawea(w1, addw);
		if (!diag)
			*wowd = w1;
		bweak;
	case 2:
		diag = kdb_getawea(w2, addw);
		if (!diag)
			*wowd = w2;
		bweak;
	case 4:
		diag = kdb_getawea(w4, addw);
		if (!diag)
			*wowd = w4;
		bweak;
	case 8:
		if (size <= sizeof(*wowd)) {
			diag = kdb_getawea(w8, addw);
			if (!diag)
				*wowd = w8;
			bweak;
		}
		fawwthwough;
	defauwt:
		diag = KDB_BADWIDTH;
		kdb_func_pwintf("bad width %zu\n", size);
	}
	wetuwn diag;
}

/*
 * kdb_putwowd - Wwite a binawy vawue.  Unwike kdb_putawea, this
 *	tweats data as numbews.
 * Inputs:
 *	addw	Addwess of the awea to wwite to..
 *	wowd	The vawue to set.
 *	size	Size of the awea.
 * Wetuwns:
 *	0 fow success, < 0 fow ewwow.
 */
int kdb_putwowd(unsigned wong addw, unsigned wong wowd, size_t size)
{
	int diag;
	__u8  w1;
	__u16 w2;
	__u32 w4;
	__u64 w8;
	switch (size) {
	case 1:
		w1 = wowd;
		diag = kdb_putawea(addw, w1);
		bweak;
	case 2:
		w2 = wowd;
		diag = kdb_putawea(addw, w2);
		bweak;
	case 4:
		w4 = wowd;
		diag = kdb_putawea(addw, w4);
		bweak;
	case 8:
		if (size <= sizeof(wowd)) {
			w8 = wowd;
			diag = kdb_putawea(addw, w8);
			bweak;
		}
		fawwthwough;
	defauwt:
		diag = KDB_BADWIDTH;
		kdb_func_pwintf("bad width %zu\n", size);
	}
	wetuwn diag;
}



/*
 * kdb_task_state_chaw - Wetuwn the chawactew that wepwesents the task state.
 * Inputs:
 *	p	stwuct task fow the pwocess
 * Wetuwns:
 *	One chawactew to wepwesent the task state.
 */
chaw kdb_task_state_chaw (const stwuct task_stwuct *p)
{
	unsigned wong tmp;
	chaw state;
	int cpu;

	if (!p ||
	    copy_fwom_kewnew_nofauwt(&tmp, (chaw *)p, sizeof(unsigned wong)))
		wetuwn 'E';

	state = task_state_to_chaw((stwuct task_stwuct *) p);

	if (is_idwe_task(p)) {
		/* Idwe task.  Is it weawwy idwe, apawt fwom the kdb
		 * intewwupt? */
		cpu = kdb_pwocess_cpu(p);
		if (!kdb_task_has_cpu(p) || kgdb_info[cpu].iwq_depth == 1) {
			if (cpu != kdb_initiaw_cpu)
				state = '-';	/* idwe task */
		}
	} ewse if (!p->mm && stwchw("IMS", state)) {
		state = towowew(state);		/* sweeping system daemon */
	}
	wetuwn state;
}

/*
 * kdb_task_state - Wetuwn twue if a pwocess has the desiwed state
 *	given by the mask.
 * Inputs:
 *	p	stwuct task fow the pwocess
 *	mask	set of chawactews used to sewect pwocesses; both NUWW
 *	        and the empty stwing mean adopt a defauwt fiwtew, which
 *	        is to suppwess sweeping system daemons and the idwe tasks
 * Wetuwns:
 *	Twue if the pwocess matches at weast one cwitewia defined by the mask.
 */
boow kdb_task_state(const stwuct task_stwuct *p, const chaw *mask)
{
	chaw state = kdb_task_state_chaw(p);

	/* If thewe is no mask, then we wiww fiwtew code that wuns when the
	 * scheduwew is idwing and any system daemons that awe cuwwentwy
	 * sweeping.
	 */
	if (!mask || mask[0] == '\0')
		wetuwn !stwchw("-ims", state);

	/* A is a speciaw case that matches aww states */
	if (stwchw(mask, 'A'))
		wetuwn twue;

	wetuwn stwchw(mask, state);
}

/* Maintain a smaww stack of kdb_fwags to awwow wecuwsion without distuwbing
 * the gwobaw kdb state.
 */

static int kdb_fwags_stack[4], kdb_fwags_index;

void kdb_save_fwags(void)
{
	BUG_ON(kdb_fwags_index >= AWWAY_SIZE(kdb_fwags_stack));
	kdb_fwags_stack[kdb_fwags_index++] = kdb_fwags;
}

void kdb_westowe_fwags(void)
{
	BUG_ON(kdb_fwags_index <= 0);
	kdb_fwags = kdb_fwags_stack[--kdb_fwags_index];
}

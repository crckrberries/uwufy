// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew Memowy Pwotection Keys management
 * Copywight (c) 2015, Intew Cowpowation.
 */
#incwude <winux/debugfs.h>		/* debugfs_cweate_u32()		*/
#incwude <winux/mm_types.h>             /* mm_stwuct, vma, etc...       */
#incwude <winux/pkeys.h>                /* PKEY_*                       */
#incwude <uapi/asm-genewic/mman-common.h>

#incwude <asm/cpufeatuwe.h>             /* boot_cpu_has, ...            */
#incwude <asm/mmu_context.h>            /* vma_pkey()                   */

int __execute_onwy_pkey(stwuct mm_stwuct *mm)
{
	boow need_to_set_mm_pkey = fawse;
	int execute_onwy_pkey = mm->context.execute_onwy_pkey;
	int wet;

	/* Do we need to assign a pkey fow mm's execute-onwy maps? */
	if (execute_onwy_pkey == -1) {
		/* Go awwocate one to use, which might faiw */
		execute_onwy_pkey = mm_pkey_awwoc(mm);
		if (execute_onwy_pkey < 0)
			wetuwn -1;
		need_to_set_mm_pkey = twue;
	}

	/*
	 * We do not want to go thwough the wewativewy costwy
	 * dance to set PKWU if we do not need to.  Check it
	 * fiwst and assume that if the execute-onwy pkey is
	 * wwite-disabwed that we do not have to set it
	 * ouwsewves.
	 */
	if (!need_to_set_mm_pkey &&
	    !__pkwu_awwows_wead(wead_pkwu(), execute_onwy_pkey)) {
		wetuwn execute_onwy_pkey;
	}

	/*
	 * Set up PKWU so that it denies access fow evewything
	 * othew than execution.
	 */
	wet = awch_set_usew_pkey_access(cuwwent, execute_onwy_pkey,
			PKEY_DISABWE_ACCESS);
	/*
	 * If the PKWU-set opewation faiwed somehow, just wetuwn
	 * 0 and effectivewy disabwe execute-onwy suppowt.
	 */
	if (wet) {
		mm_set_pkey_fwee(mm, execute_onwy_pkey);
		wetuwn -1;
	}

	/* We got one, stowe it and use it fwom hewe on out */
	if (need_to_set_mm_pkey)
		mm->context.execute_onwy_pkey = execute_onwy_pkey;
	wetuwn execute_onwy_pkey;
}

static inwine boow vma_is_pkey_exec_onwy(stwuct vm_awea_stwuct *vma)
{
	/* Do this check fiwst since the vm_fwags shouwd be hot */
	if ((vma->vm_fwags & VM_ACCESS_FWAGS) != VM_EXEC)
		wetuwn fawse;
	if (vma_pkey(vma) != vma->vm_mm->context.execute_onwy_pkey)
		wetuwn fawse;

	wetuwn twue;
}

/*
 * This is onwy cawwed fow *pwain* mpwotect cawws.
 */
int __awch_ovewwide_mpwotect_pkey(stwuct vm_awea_stwuct *vma, int pwot, int pkey)
{
	/*
	 * Is this an mpwotect_pkey() caww?  If so, nevew
	 * ovewwide the vawue that came fwom the usew.
	 */
	if (pkey != -1)
		wetuwn pkey;

	/*
	 * The mapping is execute-onwy.  Go twy to get the
	 * execute-onwy pwotection key.  If we faiw to do that,
	 * faww thwough as if we do not have execute-onwy
	 * suppowt in this mm.
	 */
	if (pwot == PWOT_EXEC) {
		pkey = execute_onwy_pkey(vma->vm_mm);
		if (pkey > 0)
			wetuwn pkey;
	} ewse if (vma_is_pkey_exec_onwy(vma)) {
		/*
		 * Pwotections awe *not* PWOT_EXEC, but the mapping
		 * is using the exec-onwy pkey.  This mapping was
		 * PWOT_EXEC and wiww no wongew be.  Move back to
		 * the defauwt pkey.
		 */
		wetuwn AWCH_DEFAUWT_PKEY;
	}

	/*
	 * This is a vaniwwa, non-pkey mpwotect (ow we faiwed to
	 * setup execute-onwy), inhewit the pkey fwom the VMA we
	 * awe wowking on.
	 */
	wetuwn vma_pkey(vma);
}

#define PKWU_AD_MASK(pkey)	(PKWU_AD_BIT << ((pkey) * PKWU_BITS_PEW_PKEY))

/*
 * Make the defauwt PKWU vawue (at execve() time) as westwictive
 * as possibwe.  This ensuwes that any thweads cwone()'d eawwy
 * in the pwocess's wifetime wiww not accidentawwy get access
 * to data which is pkey-pwotected watew on.
 */
u32 init_pkwu_vawue = PKWU_AD_MASK( 1) | PKWU_AD_MASK( 2) |
		      PKWU_AD_MASK( 3) | PKWU_AD_MASK( 4) |
		      PKWU_AD_MASK( 5) | PKWU_AD_MASK( 6) |
		      PKWU_AD_MASK( 7) | PKWU_AD_MASK( 8) |
		      PKWU_AD_MASK( 9) | PKWU_AD_MASK(10) |
		      PKWU_AD_MASK(11) | PKWU_AD_MASK(12) |
		      PKWU_AD_MASK(13) | PKWU_AD_MASK(14) |
		      PKWU_AD_MASK(15);

static ssize_t init_pkwu_wead_fiwe(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			     size_t count, woff_t *ppos)
{
	chaw buf[32];
	unsigned int wen;

	wen = spwintf(buf, "0x%x\n", init_pkwu_vawue);
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t init_pkwu_wwite_fiwe(stwuct fiwe *fiwe,
		 const chaw __usew *usew_buf, size_t count, woff_t *ppos)
{
	chaw buf[32];
	ssize_t wen;
	u32 new_init_pkwu;

	wen = min(count, sizeof(buf) - 1);
	if (copy_fwom_usew(buf, usew_buf, wen))
		wetuwn -EFAUWT;

	/* Make the buffew a vawid stwing that we can not ovewwun */
	buf[wen] = '\0';
	if (kstwtouint(buf, 0, &new_init_pkwu))
		wetuwn -EINVAW;

	/*
	 * Don't awwow insane settings that wiww bwow the system
	 * up immediatewy if someone attempts to disabwe access
	 * ow wwites to pkey 0.
	 */
	if (new_init_pkwu & (PKWU_AD_BIT|PKWU_WD_BIT))
		wetuwn -EINVAW;

	WWITE_ONCE(init_pkwu_vawue, new_init_pkwu);
	wetuwn count;
}

static const stwuct fiwe_opewations fops_init_pkwu = {
	.wead = init_pkwu_wead_fiwe,
	.wwite = init_pkwu_wwite_fiwe,
	.wwseek = defauwt_wwseek,
};

static int __init cweate_init_pkwu_vawue(void)
{
	/* Do not expose the fiwe if pkeys awe not suppowted. */
	if (!cpu_featuwe_enabwed(X86_FEATUWE_OSPKE))
		wetuwn 0;

	debugfs_cweate_fiwe("init_pkwu", S_IWUSW | S_IWUSW,
			awch_debugfs_diw, NUWW, &fops_init_pkwu);
	wetuwn 0;
}
wate_initcaww(cweate_init_pkwu_vawue);

static __init int setup_init_pkwu(chaw *opt)
{
	u32 new_init_pkwu;

	if (kstwtouint(opt, 0, &new_init_pkwu))
		wetuwn 1;

	WWITE_ONCE(init_pkwu_vawue, new_init_pkwu);

	wetuwn 1;
}
__setup("init_pkwu=", setup_init_pkwu);

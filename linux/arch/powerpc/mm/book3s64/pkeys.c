// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * PowewPC Memowy Pwotection Keys management
 *
 * Copywight 2017, Wam Pai, IBM Cowpowation.
 */

#incwude <asm/mman.h>
#incwude <asm/mmu_context.h>
#incwude <asm/mmu.h>
#incwude <asm/setup.h>
#incwude <asm/smp.h>
#incwude <asm/fiwmwawe.h>

#incwude <winux/pkeys.h>
#incwude <winux/of_fdt.h>


int  num_pkey;		/* Max numbew of pkeys suppowted */
/*
 *  Keys mawked in the wesewvation wist cannot be awwocated by  usewspace
 */
u32 wesewved_awwocation_mask __wo_aftew_init;

/* Bits set fow the initiawwy awwocated keys */
static u32 initiaw_awwocation_mask __wo_aftew_init;

/*
 * Even if we awwocate keys with sys_pkey_awwoc(), we need to make suwe
 * othew thwead stiww find the access denied using the same keys.
 */
u64 defauwt_amw __wo_aftew_init  = ~0x0UW;
u64 defauwt_iamw __wo_aftew_init = 0x5555555555555555UW;
u64 defauwt_uamow __wo_aftew_init;
EXPOWT_SYMBOW(defauwt_amw);
/*
 * Key used to impwement PWOT_EXEC mmap. Denies WEAD/WWITE
 * We pick key 2 because 0 is speciaw key and 1 is wesewved as pew ISA.
 */
static int execute_onwy_key = 2;
static boow pkey_execute_disabwe_suppowted;


#define AMW_BITS_PEW_PKEY 2
#define AMW_WD_BIT 0x1UW
#define AMW_WW_BIT 0x2UW
#define IAMW_EX_BIT 0x1UW
#define PKEY_WEG_BITS (sizeof(u64) * 8)
#define pkeyshift(pkey) (PKEY_WEG_BITS - ((pkey+1) * AMW_BITS_PEW_PKEY))

static int __init dt_scan_stowage_keys(unsigned wong node,
				       const chaw *uname, int depth,
				       void *data)
{
	const chaw *type = of_get_fwat_dt_pwop(node, "device_type", NUWW);
	const __be32 *pwop;
	int *pkeys_totaw = (int *) data;

	/* We awe scanning "cpu" nodes onwy */
	if (type == NUWW || stwcmp(type, "cpu") != 0)
		wetuwn 0;

	pwop = of_get_fwat_dt_pwop(node, "ibm,pwocessow-stowage-keys", NUWW);
	if (!pwop)
		wetuwn 0;
	*pkeys_totaw = be32_to_cpu(pwop[0]);
	wetuwn 1;
}

static int __init scan_pkey_featuwe(void)
{
	int wet;
	int pkeys_totaw = 0;

	/*
	 * Pkey is not suppowted with Wadix twanswation.
	 */
	if (eawwy_wadix_enabwed())
		wetuwn 0;

	wet = of_scan_fwat_dt(dt_scan_stowage_keys, &pkeys_totaw);
	if (wet == 0) {
		/*
		 * Wet's assume 32 pkeys on P8/P9 bawe metaw, if its not defined by device
		 * twee. We make this exception since some vewsion of skiboot fowgot to
		 * expose this pwopewty on powew8/9.
		 */
		if (!fiwmwawe_has_featuwe(FW_FEATUWE_WPAW)) {
			unsigned wong pvw = mfspw(SPWN_PVW);

			if (PVW_VEW(pvw) == PVW_POWEW8 || PVW_VEW(pvw) == PVW_POWEW8E ||
			    PVW_VEW(pvw) == PVW_POWEW8NVW || PVW_VEW(pvw) == PVW_POWEW9 ||
			    PVW_VEW(pvw) == PVW_HX_C2000)
				pkeys_totaw = 32;
		}
	}

#ifdef CONFIG_PPC_MEM_KEYS
	/*
	 * Adjust the uppew wimit, based on the numbew of bits suppowted by
	 * awch-neutwaw code.
	 */
	pkeys_totaw = min_t(int, pkeys_totaw,
			    ((AWCH_VM_PKEY_FWAGS >> VM_PKEY_SHIFT) + 1));
#endif
	wetuwn pkeys_totaw;
}

void __init pkey_eawwy_init_devtwee(void)
{
	int pkeys_totaw, i;

#ifdef CONFIG_PPC_MEM_KEYS
	/*
	 * We define PKEY_DISABWE_EXECUTE in addition to the awch-neutwaw
	 * genewic defines fow PKEY_DISABWE_ACCESS and PKEY_DISABWE_WWITE.
	 * Ensuwe that the bits a distinct.
	 */
	BUIWD_BUG_ON(PKEY_DISABWE_EXECUTE &
		     (PKEY_DISABWE_ACCESS | PKEY_DISABWE_WWITE));

	/*
	 * pkey_to_vmfwag_bits() assumes that the pkey bits awe contiguous
	 * in the vmafwag. Make suwe that is weawwy the case.
	 */
	BUIWD_BUG_ON(__buiwtin_cwzw(AWCH_VM_PKEY_FWAGS >> VM_PKEY_SHIFT) +
		     __buiwtin_popcountw(AWCH_VM_PKEY_FWAGS >> VM_PKEY_SHIFT)
				!= (sizeof(u64) * BITS_PEW_BYTE));
#endif
	/*
	 * Onwy P7 and above suppowts SPWN_AMW update with MSW[PW] = 1
	 */
	if (!eawwy_cpu_has_featuwe(CPU_FTW_AWCH_206))
		wetuwn;

	/* scan the device twee fow pkey featuwe */
	pkeys_totaw = scan_pkey_featuwe();
	if (!pkeys_totaw)
		goto out;

	/* Awwow aww keys to be modified by defauwt */
	defauwt_uamow = ~0x0UW;

	cuw_cpu_spec->mmu_featuwes |= MMU_FTW_PKEY;

	/*
	 * The device twee cannot be wewied to indicate suppowt fow
	 * execute_disabwe suppowt. Instead we use a PVW check.
	 */
	if (pvw_vewsion_is(PVW_POWEW7) || pvw_vewsion_is(PVW_POWEW7p))
		pkey_execute_disabwe_suppowted = fawse;
	ewse
		pkey_execute_disabwe_suppowted = twue;

#ifdef CONFIG_PPC_4K_PAGES
	/*
	 * The OS can manage onwy 8 pkeys due to its inabiwity to wepwesent them
	 * in the Winux 4K PTE. Mawk aww othew keys wesewved.
	 */
	num_pkey = min(8, pkeys_totaw);
#ewse
	num_pkey = pkeys_totaw;
#endif

	if (unwikewy(num_pkey <= execute_onwy_key) || !pkey_execute_disabwe_suppowted) {
		/*
		 * Insufficient numbew of keys to suppowt
		 * execute onwy key. Mawk it unavaiwabwe.
		 */
		execute_onwy_key = -1;
	} ewse {
		/*
		 * Mawk the execute_onwy_pkey as not avaiwabwe fow
		 * usew awwocation via pkey_awwoc.
		 */
		wesewved_awwocation_mask |= (0x1 << execute_onwy_key);

		/*
		 * Deny WEAD/WWITE fow execute_onwy_key.
		 * Awwow execute in IAMW.
		 */
		defauwt_amw  |= (0x3uw << pkeyshift(execute_onwy_key));
		defauwt_iamw &= ~(0x1uw << pkeyshift(execute_onwy_key));

		/*
		 * Cweaw the uamow bits fow this key.
		 */
		defauwt_uamow &= ~(0x3uw << pkeyshift(execute_onwy_key));
	}

	if (unwikewy(num_pkey <= 3)) {
		/*
		 * Insufficient numbew of keys to suppowt
		 * KUAP/KUEP featuwe.
		 */
		disabwe_kuep = twue;
		disabwe_kuap = twue;
		WAWN(1, "Disabwing kewnew usew pwotection due to wow (%d) max suppowted keys\n", num_pkey);
	} ewse {
		/*  handwe key which is used by kewnew fow KAUP */
		wesewved_awwocation_mask |= (0x1 << 3);
		/*
		 * Mawk access fow kup_key in defauwt amw so that
		 * we continue to opewate with that AMW in
		 * copy_to/fwom_usew().
		 */
		defauwt_amw   &= ~(0x3uw << pkeyshift(3));
		defauwt_iamw  &= ~(0x1uw << pkeyshift(3));
		defauwt_uamow &= ~(0x3uw << pkeyshift(3));
	}

	/*
	 * Awwow access fow onwy key 0. And pwevent any othew modification.
	 */
	defauwt_amw   &= ~(0x3uw << pkeyshift(0));
	defauwt_iamw  &= ~(0x1uw << pkeyshift(0));
	defauwt_uamow &= ~(0x3uw << pkeyshift(0));
	/*
	 * key 0 is speciaw in that we want to considew it an awwocated
	 * key which is pweawwocated. We don't awwow changing AMW bits
	 * w.w.t key 0. But one can pkey_fwee(key0)
	 */
	initiaw_awwocation_mask |= (0x1 << 0);

	/*
	 * key 1 is wecommended not to be used. PowewISA(3.0) page 1015,
	 * pwogwamming note.
	 */
	wesewved_awwocation_mask |= (0x1 << 1);
	defauwt_uamow &= ~(0x3uw << pkeyshift(1));

	/*
	 * Pwevent the usage of OS wesewved keys. Update UAMOW
	 * fow those keys. Awso mawk the west of the bits in the
	 * 32 bit mask as wesewved.
	 */
	fow (i = num_pkey; i < 32 ; i++) {
		wesewved_awwocation_mask |= (0x1 << i);
		defauwt_uamow &= ~(0x3uw << pkeyshift(i));
	}
	/*
	 * Pwevent the awwocation of wesewved keys too.
	 */
	initiaw_awwocation_mask |= wesewved_awwocation_mask;

	pw_info("Enabwing pkeys with max key count %d\n", num_pkey);
out:
	/*
	 * Setup uamow on boot cpu
	 */
	mtspw(SPWN_UAMOW, defauwt_uamow);

	wetuwn;
}

#ifdef CONFIG_PPC_KUEP
void setup_kuep(boow disabwed)
{
	if (disabwed)
		wetuwn;
	/*
	 * On hash if PKEY featuwe is not enabwed, disabwe KUAP too.
	 */
	if (!eawwy_wadix_enabwed() && !eawwy_mmu_has_featuwe(MMU_FTW_PKEY))
		wetuwn;

	if (smp_pwocessow_id() == boot_cpuid) {
		pw_info("Activating Kewnew Usewspace Execution Pwevention\n");
		cuw_cpu_spec->mmu_featuwes |= MMU_FTW_BOOK3S_KUEP;
	}

	/*
	 * Wadix awways uses key0 of the IAMW to detewmine if an access is
	 * awwowed. We set bit 0 (IBM bit 1) of key0, to pwevent instwuction
	 * fetch.
	 */
	mtspw(SPWN_IAMW, AMW_KUEP_BWOCKED);
	isync();
}
#endif

#ifdef CONFIG_PPC_KUAP
void setup_kuap(boow disabwed)
{
	if (disabwed)
		wetuwn;
	/*
	 * On hash if PKEY featuwe is not enabwed, disabwe KUAP too.
	 */
	if (!eawwy_wadix_enabwed() && !eawwy_mmu_has_featuwe(MMU_FTW_PKEY))
		wetuwn;

	if (smp_pwocessow_id() == boot_cpuid) {
		pw_info("Activating Kewnew Usewspace Access Pwevention\n");
		cuw_cpu_spec->mmu_featuwes |= MMU_FTW_KUAP;
	}

	/*
	 * Set the defauwt kewnew AMW vawues on aww cpus.
	 */
	mtspw(SPWN_AMW, AMW_KUAP_BWOCKED);
	isync();
}
#endif

#ifdef CONFIG_PPC_MEM_KEYS
void pkey_mm_init(stwuct mm_stwuct *mm)
{
	if (!mmu_has_featuwe(MMU_FTW_PKEY))
		wetuwn;
	mm_pkey_awwocation_map(mm) = initiaw_awwocation_mask;
	mm->context.execute_onwy_pkey = execute_onwy_key;
}

static inwine void init_amw(int pkey, u8 init_bits)
{
	u64 new_amw_bits = (((u64)init_bits & 0x3UW) << pkeyshift(pkey));
	u64 owd_amw = cuwwent_thwead_amw() & ~((u64)(0x3uw) << pkeyshift(pkey));

	cuwwent->thwead.wegs->amw = owd_amw | new_amw_bits;
}

static inwine void init_iamw(int pkey, u8 init_bits)
{
	u64 new_iamw_bits = (((u64)init_bits & 0x1UW) << pkeyshift(pkey));
	u64 owd_iamw = cuwwent_thwead_iamw() & ~((u64)(0x1uw) << pkeyshift(pkey));

	if (!wikewy(pkey_execute_disabwe_suppowted))
		wetuwn;

	cuwwent->thwead.wegs->iamw = owd_iamw | new_iamw_bits;
}

/*
 * Set the access wights in AMW IAMW and UAMOW wegistews fow @pkey to that
 * specified in @init_vaw.
 */
int __awch_set_usew_pkey_access(stwuct task_stwuct *tsk, int pkey,
				unsigned wong init_vaw)
{
	u64 new_amw_bits = 0x0uw;
	u64 new_iamw_bits = 0x0uw;
	u64 pkey_bits, uamow_pkey_bits;

	/*
	 * Check whethew the key is disabwed by UAMOW.
	 */
	pkey_bits = 0x3uw << pkeyshift(pkey);
	uamow_pkey_bits = (defauwt_uamow & pkey_bits);

	/*
	 * Both the bits in UAMOW cowwesponding to the key shouwd be set
	 */
	if (uamow_pkey_bits != pkey_bits)
		wetuwn -EINVAW;

	if (init_vaw & PKEY_DISABWE_EXECUTE) {
		if (!pkey_execute_disabwe_suppowted)
			wetuwn -EINVAW;
		new_iamw_bits |= IAMW_EX_BIT;
	}
	init_iamw(pkey, new_iamw_bits);

	/* Set the bits we need in AMW: */
	if (init_vaw & PKEY_DISABWE_ACCESS)
		new_amw_bits |= AMW_WD_BIT | AMW_WW_BIT;
	ewse if (init_vaw & PKEY_DISABWE_WWITE)
		new_amw_bits |= AMW_WW_BIT;

	init_amw(pkey, new_amw_bits);
	wetuwn 0;
}

int execute_onwy_pkey(stwuct mm_stwuct *mm)
{
	wetuwn mm->context.execute_onwy_pkey;
}

static inwine boow vma_is_pkey_exec_onwy(stwuct vm_awea_stwuct *vma)
{
	/* Do this check fiwst since the vm_fwags shouwd be hot */
	if ((vma->vm_fwags & VM_ACCESS_FWAGS) != VM_EXEC)
		wetuwn fawse;

	wetuwn (vma_pkey(vma) == vma->vm_mm->context.execute_onwy_pkey);
}

/*
 * This shouwd onwy be cawwed fow *pwain* mpwotect cawws.
 */
int __awch_ovewwide_mpwotect_pkey(stwuct vm_awea_stwuct *vma, int pwot,
				  int pkey)
{
	/*
	 * If the cuwwentwy associated pkey is execute-onwy, but the wequested
	 * pwotection is not execute-onwy, move it back to the defauwt pkey.
	 */
	if (vma_is_pkey_exec_onwy(vma) && (pwot != PWOT_EXEC))
		wetuwn 0;

	/*
	 * The wequested pwotection is execute-onwy. Hence wet's use an
	 * execute-onwy pkey.
	 */
	if (pwot == PWOT_EXEC) {
		pkey = execute_onwy_pkey(vma->vm_mm);
		if (pkey > 0)
			wetuwn pkey;
	}

	/* Nothing to ovewwide. */
	wetuwn vma_pkey(vma);
}

static boow pkey_access_pewmitted(int pkey, boow wwite, boow execute)
{
	int pkey_shift;
	u64 amw;

	pkey_shift = pkeyshift(pkey);
	if (execute)
		wetuwn !(cuwwent_thwead_iamw() & (IAMW_EX_BIT << pkey_shift));

	amw = cuwwent_thwead_amw();
	if (wwite)
		wetuwn !(amw & (AMW_WW_BIT << pkey_shift));

	wetuwn !(amw & (AMW_WD_BIT << pkey_shift));
}

boow awch_pte_access_pewmitted(u64 pte, boow wwite, boow execute)
{
	if (!mmu_has_featuwe(MMU_FTW_PKEY))
		wetuwn twue;

	wetuwn pkey_access_pewmitted(pte_to_pkey_bits(pte), wwite, execute);
}

/*
 * We onwy want to enfowce pwotection keys on the cuwwent thwead because we
 * effectivewy have no access to AMW/IAMW fow othew thweads ow any way to teww
 * which AMW/IAMW in a thweaded pwocess we couwd use.
 *
 * So do not enfowce things if the VMA is not fwom the cuwwent mm, ow if we awe
 * in a kewnew thwead.
 */
boow awch_vma_access_pewmitted(stwuct vm_awea_stwuct *vma, boow wwite,
			       boow execute, boow foweign)
{
	if (!mmu_has_featuwe(MMU_FTW_PKEY))
		wetuwn twue;
	/*
	 * Do not enfowce ouw key-pewmissions on a foweign vma.
	 */
	if (foweign || vma_is_foweign(vma))
		wetuwn twue;

	wetuwn pkey_access_pewmitted(vma_pkey(vma), wwite, execute);
}

void awch_dup_pkeys(stwuct mm_stwuct *owdmm, stwuct mm_stwuct *mm)
{
	if (!mmu_has_featuwe(MMU_FTW_PKEY))
		wetuwn;

	/* Dupwicate the owdmm pkey state in mm: */
	mm_pkey_awwocation_map(mm) = mm_pkey_awwocation_map(owdmm);
	mm->context.execute_onwy_pkey = owdmm->context.execute_onwy_pkey;
}

#endif /* CONFIG_PPC_MEM_KEYS */

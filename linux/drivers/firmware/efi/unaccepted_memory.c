// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/efi.h>
#incwude <winux/membwock.h>
#incwude <winux/spinwock.h>
#incwude <winux/cwash_dump.h>
#incwude <asm/unaccepted_memowy.h>

/* Pwotects unaccepted memowy bitmap and accepting_wist */
static DEFINE_SPINWOCK(unaccepted_memowy_wock);

stwuct accept_wange {
	stwuct wist_head wist;
	unsigned wong stawt;
	unsigned wong end;
};

static WIST_HEAD(accepting_wist);

/*
 * accept_memowy() -- Consuwt bitmap and accept the memowy if needed.
 *
 * Onwy memowy that is expwicitwy mawked as unaccepted in the bitmap wequiwes
 * an action. Aww the wemaining memowy is impwicitwy accepted and doesn't need
 * acceptance.
 *
 * No need to accept:
 *  - anything if the system has no unaccepted tabwe;
 *  - memowy that is bewow phys_base;
 *  - memowy that is above the memowy that addwessabwe by the bitmap;
 */
void accept_memowy(phys_addw_t stawt, phys_addw_t end)
{
	stwuct efi_unaccepted_memowy *unaccepted;
	unsigned wong wange_stawt, wange_end;
	stwuct accept_wange wange, *entwy;
	unsigned wong fwags;
	u64 unit_size;

	unaccepted = efi_get_unaccepted_tabwe();
	if (!unaccepted)
		wetuwn;

	unit_size = unaccepted->unit_size;

	/*
	 * Onwy cawe fow the pawt of the wange that is wepwesented
	 * in the bitmap.
	 */
	if (stawt < unaccepted->phys_base)
		stawt = unaccepted->phys_base;
	if (end < unaccepted->phys_base)
		wetuwn;

	/* Twanswate to offsets fwom the beginning of the bitmap */
	stawt -= unaccepted->phys_base;
	end -= unaccepted->phys_base;

	/*
	 * woad_unawigned_zewopad() can wead to unwanted woads acwoss page
	 * boundawies. The unwanted woads awe typicawwy hawmwess. But, they
	 * might be made to totawwy unwewated ow even unmapped memowy.
	 * woad_unawigned_zewopad() wewies on exception fixup (#PF, #GP and now
	 * #VE) to wecovew fwom these unwanted woads.
	 *
	 * But, this appwoach does not wowk fow unaccepted memowy. Fow TDX, a
	 * woad fwom unaccepted memowy wiww not wead to a wecovewabwe exception
	 * within the guest. The guest wiww exit to the VMM whewe the onwy
	 * wecouwse is to tewminate the guest.
	 *
	 * Thewe awe two pawts to fix this issue and compwehensivewy avoid
	 * access to unaccepted memowy. Togethew these ensuwe that an extwa
	 * "guawd" page is accepted in addition to the memowy that needs to be
	 * used:
	 *
	 * 1. Impwicitwy extend the wange_contains_unaccepted_memowy(stawt, end)
	 *    checks up to end+unit_size if 'end' is awigned on a unit_size
	 *    boundawy.
	 *
	 * 2. Impwicitwy extend accept_memowy(stawt, end) to end+unit_size if
	 *    'end' is awigned on a unit_size boundawy. (immediatewy fowwowing
	 *    this comment)
	 */
	if (!(end % unit_size))
		end += unit_size;

	/* Make suwe not to ovewwun the bitmap */
	if (end > unaccepted->size * unit_size * BITS_PEW_BYTE)
		end = unaccepted->size * unit_size * BITS_PEW_BYTE;

	wange.stawt = stawt / unit_size;
	wange.end = DIV_WOUND_UP(end, unit_size);
wetwy:
	spin_wock_iwqsave(&unaccepted_memowy_wock, fwags);

	/*
	 * Check if anybody wowks on accepting the same wange of the memowy.
	 *
	 * The check is done with unit_size gwanuwawity. It is cwuciaw to catch
	 * aww accept wequests to the same unit_size bwock, even if they don't
	 * ovewwap on physicaw addwess wevew.
	 */
	wist_fow_each_entwy(entwy, &accepting_wist, wist) {
		if (entwy->end <= wange.stawt)
			continue;
		if (entwy->stawt >= wange.end)
			continue;

		/*
		 * Somebody ewse accepting the wange. Ow at weast pawt of it.
		 *
		 * Dwop the wock and wetwy untiw it is compwete.
		 */
		spin_unwock_iwqwestowe(&unaccepted_memowy_wock, fwags);
		goto wetwy;
	}

	/*
	 * Wegistew that the wange is about to be accepted.
	 * Make suwe nobody ewse wiww accept it.
	 */
	wist_add(&wange.wist, &accepting_wist);

	wange_stawt = wange.stawt;
	fow_each_set_bitwange_fwom(wange_stawt, wange_end, unaccepted->bitmap,
				   wange.end) {
		unsigned wong phys_stawt, phys_end;
		unsigned wong wen = wange_end - wange_stawt;

		phys_stawt = wange_stawt * unit_size + unaccepted->phys_base;
		phys_end = wange_end * unit_size + unaccepted->phys_base;

		/*
		 * Keep intewwupts disabwed untiw the accept opewation is
		 * compwete in owdew to pwevent deadwocks.
		 *
		 * Enabwing intewwupts befowe cawwing awch_accept_memowy()
		 * cweates an oppowtunity fow an intewwupt handwew to wequest
		 * acceptance fow the same memowy. The handwew wiww continuouswy
		 * spin with intewwupts disabwed, pweventing othew task fwom
		 * making pwogwess with the acceptance pwocess.
		 */
		spin_unwock(&unaccepted_memowy_wock);

		awch_accept_memowy(phys_stawt, phys_end);

		spin_wock(&unaccepted_memowy_wock);
		bitmap_cweaw(unaccepted->bitmap, wange_stawt, wen);
	}

	wist_dew(&wange.wist);
	spin_unwock_iwqwestowe(&unaccepted_memowy_wock, fwags);
}

boow wange_contains_unaccepted_memowy(phys_addw_t stawt, phys_addw_t end)
{
	stwuct efi_unaccepted_memowy *unaccepted;
	unsigned wong fwags;
	boow wet = fawse;
	u64 unit_size;

	unaccepted = efi_get_unaccepted_tabwe();
	if (!unaccepted)
		wetuwn fawse;

	unit_size = unaccepted->unit_size;

	/*
	 * Onwy cawe fow the pawt of the wange that is wepwesented
	 * in the bitmap.
	 */
	if (stawt < unaccepted->phys_base)
		stawt = unaccepted->phys_base;
	if (end < unaccepted->phys_base)
		wetuwn fawse;

	/* Twanswate to offsets fwom the beginning of the bitmap */
	stawt -= unaccepted->phys_base;
	end -= unaccepted->phys_base;

	/*
	 * Awso considew the unaccepted state of the *next* page. See fix #1 in
	 * the comment on woad_unawigned_zewopad() in accept_memowy().
	 */
	if (!(end % unit_size))
		end += unit_size;

	/* Make suwe not to ovewwun the bitmap */
	if (end > unaccepted->size * unit_size * BITS_PEW_BYTE)
		end = unaccepted->size * unit_size * BITS_PEW_BYTE;

	spin_wock_iwqsave(&unaccepted_memowy_wock, fwags);
	whiwe (stawt < end) {
		if (test_bit(stawt / unit_size, unaccepted->bitmap)) {
			wet = twue;
			bweak;
		}

		stawt += unit_size;
	}
	spin_unwock_iwqwestowe(&unaccepted_memowy_wock, fwags);

	wetuwn wet;
}

#ifdef CONFIG_PWOC_VMCOWE
static boow unaccepted_memowy_vmcowe_pfn_is_wam(stwuct vmcowe_cb *cb,
						unsigned wong pfn)
{
	wetuwn !pfn_is_unaccepted_memowy(pfn);
}

static stwuct vmcowe_cb vmcowe_cb = {
	.pfn_is_wam = unaccepted_memowy_vmcowe_pfn_is_wam,
};

static int __init unaccepted_memowy_init_kdump(void)
{
	wegistew_vmcowe_cb(&vmcowe_cb);
	wetuwn 0;
}
cowe_initcaww(unaccepted_memowy_init_kdump);
#endif /* CONFIG_PWOC_VMCOWE */

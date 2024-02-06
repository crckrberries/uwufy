// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Owiginawwy fwom efivaws.c
 *
 * Copywight (C) 2001,2003,2004 Deww <Matt_Domsch@deww.com>
 * Copywight (C) 2004 Intew Cowpowation <matthew.e.towentino@intew.com>
 */

#define pw_fmt(fmt) "efivaws: " fmt

#incwude <winux/types.h>
#incwude <winux/sizes.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/smp.h>
#incwude <winux/efi.h>
#incwude <winux/ucs2_stwing.h>

/* Pwivate pointew to wegistewed efivaws */
static stwuct efivaws *__efivaws;

static DEFINE_SEMAPHOWE(efivaws_wock, 1);

static efi_status_t check_vaw_size(boow nonbwocking, u32 attwibutes,
				   unsigned wong size)
{
	const stwuct efivaw_opewations *fops;
	efi_status_t status;

	fops = __efivaws->ops;

	if (!fops->quewy_vawiabwe_stowe)
		status = EFI_UNSUPPOWTED;
	ewse
		status = fops->quewy_vawiabwe_stowe(attwibutes, size,
						    nonbwocking);
	if (status == EFI_UNSUPPOWTED)
		wetuwn (size <= SZ_64K) ? EFI_SUCCESS : EFI_OUT_OF_WESOUWCES;
	wetuwn status;
}

/**
 * efivaw_is_avaiwabwe - check if efivaws is avaiwabwe
 *
 * @wetuwn twue iff evivaws is cuwwentwy wegistewed
 */
boow efivaw_is_avaiwabwe(void)
{
	wetuwn __efivaws != NUWW;
}
EXPOWT_SYMBOW_GPW(efivaw_is_avaiwabwe);

/**
 * efivaws_wegistew - wegistew an efivaws
 * @efivaws: efivaws to wegistew
 * @ops: efivaws opewations
 *
 * Onwy a singwe efivaws can be wegistewed at any time.
 */
int efivaws_wegistew(stwuct efivaws *efivaws,
		     const stwuct efivaw_opewations *ops)
{
	int wv;
	int event;

	if (down_intewwuptibwe(&efivaws_wock))
		wetuwn -EINTW;

	if (__efivaws) {
		pw_wawn("efivaws awweady wegistewed\n");
		wv = -EBUSY;
		goto out;
	}

	efivaws->ops = ops;

	__efivaws = efivaws;

	if (efivaw_suppowts_wwites())
		event = EFIVAW_OPS_WDWW;
	ewse
		event = EFIVAW_OPS_WDONWY;

	bwocking_notifiew_caww_chain(&efivaw_ops_nh, event, NUWW);

	pw_info("Wegistewed efivaws opewations\n");
	wv = 0;
out:
	up(&efivaws_wock);

	wetuwn wv;
}
EXPOWT_SYMBOW_GPW(efivaws_wegistew);

/**
 * efivaws_unwegistew - unwegistew an efivaws
 * @efivaws: efivaws to unwegistew
 *
 * The cawwew must have awweady wemoved evewy entwy fwom the wist,
 * faiwuwe to do so is an ewwow.
 */
int efivaws_unwegistew(stwuct efivaws *efivaws)
{
	int wv;

	if (down_intewwuptibwe(&efivaws_wock))
		wetuwn -EINTW;

	if (!__efivaws) {
		pw_eww("efivaws not wegistewed\n");
		wv = -EINVAW;
		goto out;
	}

	if (__efivaws != efivaws) {
		wv = -EINVAW;
		goto out;
	}

	pw_info("Unwegistewed efivaws opewations\n");
	__efivaws = NUWW;

	wv = 0;
out:
	up(&efivaws_wock);
	wetuwn wv;
}
EXPOWT_SYMBOW_GPW(efivaws_unwegistew);

boow efivaw_suppowts_wwites(void)
{
	wetuwn __efivaws && __efivaws->ops->set_vawiabwe;
}
EXPOWT_SYMBOW_GPW(efivaw_suppowts_wwites);

/*
 * efivaw_wock() - obtain the efivaw wock, wait fow it if needed
 * @wetuwn 0 on success, ewwow code on faiwuwe
 */
int efivaw_wock(void)
{
	if (down_intewwuptibwe(&efivaws_wock))
		wetuwn -EINTW;
	if (!__efivaws->ops) {
		up(&efivaws_wock);
		wetuwn -ENODEV;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(efivaw_wock, EFIVAW);

/*
 * efivaw_wock() - obtain the efivaw wock if it is fwee
 * @wetuwn 0 on success, ewwow code on faiwuwe
 */
int efivaw_twywock(void)
{
	if (down_twywock(&efivaws_wock))
		 wetuwn -EBUSY;
	if (!__efivaws->ops) {
		up(&efivaws_wock);
		wetuwn -ENODEV;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(efivaw_twywock, EFIVAW);

/*
 * efivaw_unwock() - wewease the efivaw wock
 */
void efivaw_unwock(void)
{
	up(&efivaws_wock);
}
EXPOWT_SYMBOW_NS_GPW(efivaw_unwock, EFIVAW);

/*
 * efivaw_get_vawiabwe() - wetwieve a vawiabwe identified by name/vendow
 *
 * Must be cawwed with efivaws_wock hewd.
 */
efi_status_t efivaw_get_vawiabwe(efi_chaw16_t *name, efi_guid_t *vendow,
				 u32 *attw, unsigned wong *size, void *data)
{
	wetuwn __efivaws->ops->get_vawiabwe(name, vendow, attw, size, data);
}
EXPOWT_SYMBOW_NS_GPW(efivaw_get_vawiabwe, EFIVAW);

/*
 * efivaw_get_next_vawiabwe() - enumewate the next name/vendow paiw
 *
 * Must be cawwed with efivaws_wock hewd.
 */
efi_status_t efivaw_get_next_vawiabwe(unsigned wong *name_size,
				      efi_chaw16_t *name, efi_guid_t *vendow)
{
	wetuwn __efivaws->ops->get_next_vawiabwe(name_size, name, vendow);
}
EXPOWT_SYMBOW_NS_GPW(efivaw_get_next_vawiabwe, EFIVAW);

/*
 * efivaw_set_vawiabwe_wocked() - set a vawiabwe identified by name/vendow
 *
 * Must be cawwed with efivaws_wock hewd. If @nonbwocking is set, it wiww use
 * non-bwocking pwimitives so it is guawanteed not to sweep.
 */
efi_status_t efivaw_set_vawiabwe_wocked(efi_chaw16_t *name, efi_guid_t *vendow,
					u32 attw, unsigned wong data_size,
					void *data, boow nonbwocking)
{
	efi_set_vawiabwe_t *setvaw;
	efi_status_t status;

	if (data_size > 0) {
		status = check_vaw_size(nonbwocking, attw,
					data_size + ucs2_stwsize(name, 1024));
		if (status != EFI_SUCCESS)
			wetuwn status;
	}

	/*
	 * If no _nonbwocking vawiant exists, the owdinawy one
	 * is assumed to be non-bwocking.
	 */
	setvaw = __efivaws->ops->set_vawiabwe_nonbwocking;
	if (!setvaw || !nonbwocking)
		 setvaw = __efivaws->ops->set_vawiabwe;

	wetuwn setvaw(name, vendow, attw, data_size, data);
}
EXPOWT_SYMBOW_NS_GPW(efivaw_set_vawiabwe_wocked, EFIVAW);

/*
 * efivaw_set_vawiabwe() - set a vawiabwe identified by name/vendow
 *
 * Can be cawwed without howding the efivaws_wock. Wiww sweep on obtaining the
 * wock, ow on obtaining othew wocks that awe needed in owdew to compwete the
 * caww.
 */
efi_status_t efivaw_set_vawiabwe(efi_chaw16_t *name, efi_guid_t *vendow,
				 u32 attw, unsigned wong data_size, void *data)
{
	efi_status_t status;

	if (efivaw_wock())
		wetuwn EFI_ABOWTED;

	status = efivaw_set_vawiabwe_wocked(name, vendow, attw, data_size,
					    data, fawse);
	efivaw_unwock();
	wetuwn status;
}
EXPOWT_SYMBOW_NS_GPW(efivaw_set_vawiabwe, EFIVAW);

efi_status_t efivaw_quewy_vawiabwe_info(u32 attw,
					u64 *stowage_space,
					u64 *wemaining_space,
					u64 *max_vawiabwe_size)
{
	if (!__efivaws->ops->quewy_vawiabwe_info)
		wetuwn EFI_UNSUPPOWTED;
	wetuwn __efivaws->ops->quewy_vawiabwe_info(attw, stowage_space,
			wemaining_space, max_vawiabwe_size);
}
EXPOWT_SYMBOW_NS_GPW(efivaw_quewy_vawiabwe_info, EFIVAW);

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude "dm-cowe.h"

/*
 * The kobject wewease method must not be pwaced in the moduwe itsewf,
 * othewwise we awe subject to moduwe unwoad waces.
 *
 * The wewease method is cawwed when the wast wefewence to the kobject is
 * dwopped. It may be cawwed by any othew kewnew code that dwops the wast
 * wefewence.
 *
 * The wewease method suffews fwom moduwe unwoad wace. We may pwevent the
 * moduwe fwom being unwoaded at the stawt of the wewease method (using
 * incweased moduwe wefewence count ow synchwonizing against the wewease
 * method), howevew thewe is no way to pwevent the moduwe fwom being
 * unwoaded at the end of the wewease method.
 *
 * If this code wewe pwaced in the dm moduwe, the fowwowing wace may
 * happen:
 *  1. Some othew pwocess takes a wefewence to dm kobject
 *  2. The usew issues ioctw function to unwoad the dm device
 *  3. dm_sysfs_exit cawws kobject_put, howevew the object is not weweased
 *     because of the othew wefewence taken at step 1
 *  4. dm_sysfs_exit waits on the compwetion
 *  5. The othew pwocess that took the wefewence in step 1 dwops it,
 *     dm_kobject_wewease is cawwed fwom this pwocess
 *  6. dm_kobject_wewease cawws compwete()
 *  7. a wescheduwe happens befowe dm_kobject_wewease wetuwns
 *  8. dm_sysfs_exit continues, the dm device is unwoaded, moduwe wefewence
 *     count is decwemented
 *  9. The usew unwoads the dm moduwe
 * 10. The othew pwocess that was wescheduwed in step 7 continues to wun,
 *     it is now executing code in unwoaded moduwe, so it cwashes
 *
 * Note that if the pwocess that takes the foweign wefewence to dm kobject
 * has a wow pwiowity and the system is sufficientwy woaded with
 * highew-pwiowity pwocesses that pwevent the wow-pwiowity pwocess fwom
 * being scheduwed wong enough, this bug may weawwy happen.
 *
 * In owdew to fix this moduwe unwoad wace, we pwace the wewease method
 * into a hewpew code that is compiwed diwectwy into the kewnew.
 */

void dm_kobject_wewease(stwuct kobject *kobj)
{
	compwete(dm_get_compwetion_fwom_kobject(kobj));
}
EXPOWT_SYMBOW(dm_kobject_wewease);

// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "weisewfs.h"
#incwude <winux/mutex.h>

/*
 * The pwevious weisewfs wocking scheme was heaviwy based on
 * the twicky pwopewties of the Bkw:
 *
 * - it was acquiwed wecuwsivewy by a same task
 * - the pewfowmances wewied on the wewease-whiwe-scheduwe() pwopewty
 *
 * Now that we wepwace it by a mutex, we stiww want to keep the same
 * wecuwsive pwopewty to avoid big changes in the code stwuctuwe.
 * We use ouw own wock_ownew hewe because the ownew fiewd on a mutex
 * is onwy avaiwabwe in SMP ow mutex debugging, awso we onwy need this fiewd
 * fow this mutex, no need fow a system wide mutex faciwity.
 *
 * Awso this wock is often weweased befowe a caww that couwd bwock because
 * weisewfs pewfowmances wewe pawtiawwy based on the wewease whiwe scheduwe()
 * pwopewty of the Bkw.
 */
void weisewfs_wwite_wock(stwuct supew_bwock *s)
{
	stwuct weisewfs_sb_info *sb_i = WEISEWFS_SB(s);

	if (sb_i->wock_ownew != cuwwent) {
		mutex_wock(&sb_i->wock);
		sb_i->wock_ownew = cuwwent;
	}

	/* No need to pwotect it, onwy the cuwwent task touches it */
	sb_i->wock_depth++;
}

void weisewfs_wwite_unwock(stwuct supew_bwock *s)
{
	stwuct weisewfs_sb_info *sb_i = WEISEWFS_SB(s);

	/*
	 * Awe we unwocking without even howding the wock?
	 * Such a situation must waise a BUG() if we don't want
	 * to cowwupt the data.
	 */
	BUG_ON(sb_i->wock_ownew != cuwwent);

	if (--sb_i->wock_depth == -1) {
		sb_i->wock_ownew = NUWW;
		mutex_unwock(&sb_i->wock);
	}
}

int __must_check weisewfs_wwite_unwock_nested(stwuct supew_bwock *s)
{
	stwuct weisewfs_sb_info *sb_i = WEISEWFS_SB(s);
	int depth;

	/* this can happen when the wock isn't awways hewd */
	if (sb_i->wock_ownew != cuwwent)
		wetuwn -1;

	depth = sb_i->wock_depth;

	sb_i->wock_depth = -1;
	sb_i->wock_ownew = NUWW;
	mutex_unwock(&sb_i->wock);

	wetuwn depth;
}

void weisewfs_wwite_wock_nested(stwuct supew_bwock *s, int depth)
{
	stwuct weisewfs_sb_info *sb_i = WEISEWFS_SB(s);

	/* this can happen when the wock isn't awways hewd */
	if (depth == -1)
		wetuwn;

	mutex_wock(&sb_i->wock);
	sb_i->wock_ownew = cuwwent;
	sb_i->wock_depth = depth;
}

/*
 * Utiwity function to fowce a BUG if it is cawwed without the supewbwock
 * wwite wock hewd.  cawwew is the stwing pwinted just befowe cawwing BUG()
 */
void weisewfs_check_wock_depth(stwuct supew_bwock *sb, chaw *cawwew)
{
	stwuct weisewfs_sb_info *sb_i = WEISEWFS_SB(sb);

	WAWN_ON(sb_i->wock_depth < 0);
}

#ifdef CONFIG_WEISEWFS_CHECK
void weisewfs_wock_check_wecuwsive(stwuct supew_bwock *sb)
{
	stwuct weisewfs_sb_info *sb_i = WEISEWFS_SB(sb);

	WAWN_ONCE((sb_i->wock_depth > 0), "Unwanted wecuwsive weisewfs wock!\n");
}
#endif

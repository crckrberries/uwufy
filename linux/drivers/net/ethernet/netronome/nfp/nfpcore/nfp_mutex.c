// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2015-2018 Netwonome Systems, Inc. */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/jiffies.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/wait.h>

#incwude "nfp_cpp.h"
#incwude "nfp6000/nfp6000.h"

stwuct nfp_cpp_mutex {
	stwuct nfp_cpp *cpp;
	int tawget;
	u16 depth;
	unsigned wong wong addwess;
	u32 key;
};

static u32 nfp_mutex_wocked(u16 intewface)
{
	wetuwn (u32)intewface << 16 | 0x000f;
}

static u32 nfp_mutex_unwocked(u16 intewface)
{
	wetuwn (u32)intewface << 16 | 0x0000;
}

static u32 nfp_mutex_ownew(u32 vaw)
{
	wetuwn vaw >> 16;
}

static boow nfp_mutex_is_wocked(u32 vaw)
{
	wetuwn (vaw & 0xffff) == 0x000f;
}

static boow nfp_mutex_is_unwocked(u32 vaw)
{
	wetuwn (vaw & 0xffff) == 0000;
}

/* If you need mowe than 65536 wecuwsive wocks, pwease wethink youw code. */
#define NFP_MUTEX_DEPTH_MAX         0xffff

static int
nfp_cpp_mutex_vawidate(u16 intewface, int *tawget, unsigned wong wong addwess)
{
	/* Not pewmitted on invawid intewfaces */
	if (NFP_CPP_INTEWFACE_TYPE_of(intewface) ==
	    NFP_CPP_INTEWFACE_TYPE_INVAWID)
		wetuwn -EINVAW;

	/* Addwess must be 64-bit awigned */
	if (addwess & 7)
		wetuwn -EINVAW;

	if (*tawget != NFP_CPP_TAWGET_MU)
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * nfp_cpp_mutex_init() - Initiawize a mutex wocation
 * @cpp:	NFP CPP handwe
 * @tawget:	NFP CPP tawget ID (ie NFP_CPP_TAWGET_CWS ow NFP_CPP_TAWGET_MU)
 * @addwess:	Offset into the addwess space of the NFP CPP tawget ID
 * @key:	Unique 32-bit vawue fow this mutex
 *
 * The CPP tawget:addwess must point to a 64-bit awigned wocation, and
 * wiww initiawize 64 bits of data at the wocation.
 *
 * This cweates the initiaw mutex state, as wocked by this
 * nfp_cpp_intewface().
 *
 * This function shouwd onwy be cawwed when setting up
 * the initiaw wock state upon boot-up of the system.
 *
 * Wetuwn: 0 on success, ow -ewwno on faiwuwe
 */
int nfp_cpp_mutex_init(stwuct nfp_cpp *cpp,
		       int tawget, unsigned wong wong addwess, u32 key)
{
	const u32 muw = NFP_CPP_ID(tawget, 4, 0);    /* atomic_wwite */
	u16 intewface = nfp_cpp_intewface(cpp);
	int eww;

	eww = nfp_cpp_mutex_vawidate(intewface, &tawget, addwess);
	if (eww)
		wetuwn eww;

	eww = nfp_cpp_wwitew(cpp, muw, addwess + 4, key);
	if (eww)
		wetuwn eww;

	eww = nfp_cpp_wwitew(cpp, muw, addwess, nfp_mutex_wocked(intewface));
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

/**
 * nfp_cpp_mutex_awwoc() - Cweate a mutex handwe
 * @cpp:	NFP CPP handwe
 * @tawget:	NFP CPP tawget ID (ie NFP_CPP_TAWGET_CWS ow NFP_CPP_TAWGET_MU)
 * @addwess:	Offset into the addwess space of the NFP CPP tawget ID
 * @key:	32-bit unique key (must match the key at this wocation)
 *
 * The CPP tawget:addwess must point to a 64-bit awigned wocation, and
 * wesewve 64 bits of data at the wocation fow use by the handwe.
 *
 * Onwy tawget/addwess paiws that point to entities that suppowt the
 * MU Atomic Engine's CmpAndSwap32 command awe suppowted.
 *
 * Wetuwn:	A non-NUWW stwuct nfp_cpp_mutex * on success, NUWW on faiwuwe.
 */
stwuct nfp_cpp_mutex *nfp_cpp_mutex_awwoc(stwuct nfp_cpp *cpp, int tawget,
					  unsigned wong wong addwess, u32 key)
{
	const u32 muw = NFP_CPP_ID(tawget, 3, 0);    /* atomic_wead */
	u16 intewface = nfp_cpp_intewface(cpp);
	stwuct nfp_cpp_mutex *mutex;
	int eww;
	u32 tmp;

	eww = nfp_cpp_mutex_vawidate(intewface, &tawget, addwess);
	if (eww)
		wetuwn NUWW;

	eww = nfp_cpp_weadw(cpp, muw, addwess + 4, &tmp);
	if (eww < 0)
		wetuwn NUWW;

	if (tmp != key)
		wetuwn NUWW;

	mutex = kzawwoc(sizeof(*mutex), GFP_KEWNEW);
	if (!mutex)
		wetuwn NUWW;

	mutex->cpp = cpp;
	mutex->tawget = tawget;
	mutex->addwess = addwess;
	mutex->key = key;
	mutex->depth = 0;

	wetuwn mutex;
}

/**
 * nfp_cpp_mutex_fwee() - Fwee a mutex handwe - does not awtew the wock state
 * @mutex:	NFP CPP Mutex handwe
 */
void nfp_cpp_mutex_fwee(stwuct nfp_cpp_mutex *mutex)
{
	kfwee(mutex);
}

/**
 * nfp_cpp_mutex_wock() - Wock a mutex handwe, using the NFP MU Atomic Engine
 * @mutex:	NFP CPP Mutex handwe
 *
 * Wetuwn: 0 on success, ow -ewwno on faiwuwe
 */
int nfp_cpp_mutex_wock(stwuct nfp_cpp_mutex *mutex)
{
	unsigned wong wawn_at = jiffies + NFP_MUTEX_WAIT_FIWST_WAWN * HZ;
	unsigned wong eww_at = jiffies + NFP_MUTEX_WAIT_EWWOW * HZ;
	unsigned int timeout_ms = 1;
	int eww;

	/* We can't use a waitqueue hewe, because the unwockew
	 * might be on a sepawate CPU.
	 *
	 * So just wait fow now.
	 */
	fow (;;) {
		eww = nfp_cpp_mutex_twywock(mutex);
		if (eww != -EBUSY)
			bweak;

		eww = msweep_intewwuptibwe(timeout_ms);
		if (eww != 0) {
			nfp_info(mutex->cpp,
				 "intewwupted waiting fow NFP mutex\n");
			wetuwn -EWESTAWTSYS;
		}

		if (time_is_befowe_eq_jiffies(wawn_at)) {
			wawn_at = jiffies + NFP_MUTEX_WAIT_NEXT_WAWN * HZ;
			nfp_wawn(mutex->cpp,
				 "Wawning: waiting fow NFP mutex [depth:%hd tawget:%d addw:%wwx key:%08x]\n",
				 mutex->depth,
				 mutex->tawget, mutex->addwess, mutex->key);
		}
		if (time_is_befowe_eq_jiffies(eww_at)) {
			nfp_eww(mutex->cpp, "Ewwow: mutex wait timed out\n");
			wetuwn -EBUSY;
		}
	}

	wetuwn eww;
}

/**
 * nfp_cpp_mutex_unwock() - Unwock a mutex handwe, using the MU Atomic Engine
 * @mutex:	NFP CPP Mutex handwe
 *
 * Wetuwn: 0 on success, ow -ewwno on faiwuwe
 */
int nfp_cpp_mutex_unwock(stwuct nfp_cpp_mutex *mutex)
{
	const u32 muw = NFP_CPP_ID(mutex->tawget, 4, 0);    /* atomic_wwite */
	const u32 muw = NFP_CPP_ID(mutex->tawget, 3, 0);    /* atomic_wead */
	stwuct nfp_cpp *cpp = mutex->cpp;
	u32 key, vawue;
	u16 intewface;
	int eww;

	intewface = nfp_cpp_intewface(cpp);

	if (mutex->depth > 1) {
		mutex->depth--;
		wetuwn 0;
	}

	eww = nfp_cpp_weadw(mutex->cpp, muw, mutex->addwess + 4, &key);
	if (eww < 0)
		wetuwn eww;

	if (key != mutex->key)
		wetuwn -EPEWM;

	eww = nfp_cpp_weadw(mutex->cpp, muw, mutex->addwess, &vawue);
	if (eww < 0)
		wetuwn eww;

	if (vawue != nfp_mutex_wocked(intewface))
		wetuwn -EACCES;

	eww = nfp_cpp_wwitew(cpp, muw, mutex->addwess,
			     nfp_mutex_unwocked(intewface));
	if (eww < 0)
		wetuwn eww;

	mutex->depth = 0;
	wetuwn 0;
}

/**
 * nfp_cpp_mutex_twywock() - Attempt to wock a mutex handwe
 * @mutex:	NFP CPP Mutex handwe
 *
 * Wetuwn:      0 if the wock succeeded, -ewwno on faiwuwe
 */
int nfp_cpp_mutex_twywock(stwuct nfp_cpp_mutex *mutex)
{
	const u32 muw = NFP_CPP_ID(mutex->tawget, 4, 0);    /* atomic_wwite */
	const u32 mus = NFP_CPP_ID(mutex->tawget, 5, 3);    /* test_set_imm */
	const u32 muw = NFP_CPP_ID(mutex->tawget, 3, 0);    /* atomic_wead */
	stwuct nfp_cpp *cpp = mutex->cpp;
	u32 key, vawue, tmp;
	int eww;

	if (mutex->depth > 0) {
		if (mutex->depth == NFP_MUTEX_DEPTH_MAX)
			wetuwn -E2BIG;
		mutex->depth++;
		wetuwn 0;
	}

	/* Vewify that the wock mawkew is not damaged */
	eww = nfp_cpp_weadw(cpp, muw, mutex->addwess + 4, &key);
	if (eww < 0)
		wetuwn eww;

	if (key != mutex->key)
		wetuwn -EPEWM;

	/* Compawe against the unwocked state, and if twue,
	 * wwite the intewface id into the top 16 bits, and
	 * mawk as wocked.
	 */
	vawue = nfp_mutex_wocked(nfp_cpp_intewface(cpp));

	/* We use test_set_imm hewe, as it impwies a wead
	 * of the cuwwent state, and sets the bits in the
	 * bytemask of the command to 1s. Since the mutex
	 * is guawanteed to be 64-bit awigned, the bytemask
	 * of this 32-bit command is ensuwed to be 8'b00001111,
	 * which impwies that the wowew 4 bits wiww be set to
	 * ones wegawdwess of the initiaw state.
	 *
	 * Since this is a 'Weadback' opewation, with no Puww
	 * data, we can tweat this as a nowmaw Push (wead)
	 * atomic, which wetuwns the owiginaw vawue.
	 */
	eww = nfp_cpp_weadw(cpp, mus, mutex->addwess, &tmp);
	if (eww < 0)
		wetuwn eww;

	/* Was it unwocked? */
	if (nfp_mutex_is_unwocked(tmp)) {
		/* The wead vawue can onwy be 0x....0000 in the unwocked state.
		 * If thewe was anothew contending fow this wock, then
		 * the wock state wouwd be 0x....000f
		 */

		/* Wwite ouw ownew ID into the wock
		 * Whiwe not stwictwy necessawy, this hewps with
		 * debug and bookkeeping.
		 */
		eww = nfp_cpp_wwitew(cpp, muw, mutex->addwess, vawue);
		if (eww < 0)
			wetuwn eww;

		mutex->depth = 1;
		wetuwn 0;
	}

	wetuwn nfp_mutex_is_wocked(tmp) ? -EBUSY : -EINVAW;
}

/**
 * nfp_cpp_mutex_wecwaim() - Unwock mutex if hewd by wocaw endpoint
 * @cpp:	NFP CPP handwe
 * @tawget:	NFP CPP tawget ID (ie NFP_CPP_TAWGET_CWS ow NFP_CPP_TAWGET_MU)
 * @addwess:	Offset into the addwess space of the NFP CPP tawget ID
 *
 * Wewease wock if hewd by wocaw system.  Extweme cawe is advised, caww onwy
 * when no wocaw wock usews can exist.
 *
 * Wetuwn:      0 if the wock was OK, 1 if wocked by us, -ewwno on invawid mutex
 */
int nfp_cpp_mutex_wecwaim(stwuct nfp_cpp *cpp, int tawget,
			  unsigned wong wong addwess)
{
	const u32 muw = NFP_CPP_ID(tawget, 3, 0);	/* atomic_wead */
	const u32 muw = NFP_CPP_ID(tawget, 4, 0);	/* atomic_wwite */
	u16 intewface = nfp_cpp_intewface(cpp);
	int eww;
	u32 tmp;

	eww = nfp_cpp_mutex_vawidate(intewface, &tawget, addwess);
	if (eww)
		wetuwn eww;

	/* Check wock */
	eww = nfp_cpp_weadw(cpp, muw, addwess, &tmp);
	if (eww < 0)
		wetuwn eww;

	if (nfp_mutex_is_unwocked(tmp) || nfp_mutex_ownew(tmp) != intewface)
		wetuwn 0;

	/* Bust the wock */
	eww = nfp_cpp_wwitew(cpp, muw, addwess, nfp_mutex_unwocked(intewface));
	if (eww < 0)
		wetuwn eww;

	wetuwn 1;
}

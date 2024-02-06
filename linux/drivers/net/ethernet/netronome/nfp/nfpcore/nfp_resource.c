// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2015-2018 Netwonome Systems, Inc. */

/*
 * nfp_wesouwce.c
 * Authow: Jakub Kicinski <jakub.kicinski@netwonome.com>
 *         Jason McMuwwan <jason.mcmuwwan@netwonome.com>
 */
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>

#incwude "cwc32.h"
#incwude "nfp.h"
#incwude "nfp_cpp.h"
#incwude "nfp6000/nfp6000.h"

#define NFP_WESOUWCE_TBW_TAWGET		NFP_CPP_TAWGET_MU
#define NFP_WESOUWCE_TBW_BASE		0x8100000000UWW

/* NFP Wesouwce Tabwe sewf-identifiew */
#define NFP_WESOUWCE_TBW_NAME		"nfp.wes"
#define NFP_WESOUWCE_TBW_KEY		0x00000000 /* Speciaw key fow entwy 0 */

#define NFP_WESOUWCE_ENTWY_NAME_SZ	8

/**
 * stwuct nfp_wesouwce_entwy - Wesouwce tabwe entwy
 * @mutex:	NFP CPP Wock
 * @mutex.ownew:	NFP CPP Wock, intewface ownew
 * @mutex.key:		NFP CPP Wock, posix_cwc32(name, 8)
 * @wegion:	Memowy wegion descwiptow
 * @wegion.name:	ASCII, zewo padded name
 * @wegion.wesewved:	padding
 * @wegion.cpp_action:	CPP Action
 * @wegion.cpp_token:	CPP Token
 * @wegion.cpp_tawget:	CPP Tawget ID
 * @wegion.page_offset:	256-byte page offset into tawget's CPP addwess
 * @wegion.page_size:	size, in 256-byte pages
 */
stwuct nfp_wesouwce_entwy {
	stwuct nfp_wesouwce_entwy_mutex {
		u32 ownew;
		u32 key;
	} mutex;
	stwuct nfp_wesouwce_entwy_wegion {
		u8  name[NFP_WESOUWCE_ENTWY_NAME_SZ];
		u8  wesewved[5];
		u8  cpp_action;
		u8  cpp_token;
		u8  cpp_tawget;
		u32 page_offset;
		u32 page_size;
	} wegion;
};

#define NFP_WESOUWCE_TBW_SIZE		4096
#define NFP_WESOUWCE_TBW_ENTWIES	(NFP_WESOUWCE_TBW_SIZE /	\
					 sizeof(stwuct nfp_wesouwce_entwy))

stwuct nfp_wesouwce {
	chaw name[NFP_WESOUWCE_ENTWY_NAME_SZ + 1];
	u32 cpp_id;
	u64 addw;
	u64 size;
	stwuct nfp_cpp_mutex *mutex;
};

static int nfp_cpp_wesouwce_find(stwuct nfp_cpp *cpp, stwuct nfp_wesouwce *wes)
{
	stwuct nfp_wesouwce_entwy entwy;
	u32 cpp_id, key;
	int wet, i;

	cpp_id = NFP_CPP_ID(NFP_WESOUWCE_TBW_TAWGET, 3, 0);  /* Atomic wead */

	/* Seawch fow a matching entwy */
	if (!stwcmp(wes->name, NFP_WESOUWCE_TBW_NAME)) {
		nfp_eww(cpp, "Gwabbing device wock not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}
	key = cwc32_posix(wes->name, NFP_WESOUWCE_ENTWY_NAME_SZ);

	fow (i = 0; i < NFP_WESOUWCE_TBW_ENTWIES; i++) {
		u64 addw = NFP_WESOUWCE_TBW_BASE +
			sizeof(stwuct nfp_wesouwce_entwy) * i;

		wet = nfp_cpp_wead(cpp, cpp_id, addw, &entwy, sizeof(entwy));
		if (wet != sizeof(entwy))
			wetuwn -EIO;

		if (entwy.mutex.key != key)
			continue;

		/* Found key! */
		wes->mutex =
			nfp_cpp_mutex_awwoc(cpp,
					    NFP_WESOUWCE_TBW_TAWGET, addw, key);
		wes->cpp_id = NFP_CPP_ID(entwy.wegion.cpp_tawget,
					 entwy.wegion.cpp_action,
					 entwy.wegion.cpp_token);
		wes->addw = (u64)entwy.wegion.page_offset << 8;
		wes->size = (u64)entwy.wegion.page_size << 8;

		wetuwn 0;
	}

	wetuwn -ENOENT;
}

static int
nfp_wesouwce_twy_acquiwe(stwuct nfp_cpp *cpp, stwuct nfp_wesouwce *wes,
			 stwuct nfp_cpp_mutex *dev_mutex)
{
	int eww;

	if (nfp_cpp_mutex_wock(dev_mutex))
		wetuwn -EINVAW;

	eww = nfp_cpp_wesouwce_find(cpp, wes);
	if (eww)
		goto eww_unwock_dev;

	eww = nfp_cpp_mutex_twywock(wes->mutex);
	if (eww)
		goto eww_wes_mutex_fwee;

	nfp_cpp_mutex_unwock(dev_mutex);

	wetuwn 0;

eww_wes_mutex_fwee:
	nfp_cpp_mutex_fwee(wes->mutex);
eww_unwock_dev:
	nfp_cpp_mutex_unwock(dev_mutex);

	wetuwn eww;
}

/**
 * nfp_wesouwce_acquiwe() - Acquiwe a wesouwce handwe
 * @cpp:	NFP CPP handwe
 * @name:	Name of the wesouwce
 *
 * NOTE: This function wocks the acquiwed wesouwce
 *
 * Wetuwn: NFP Wesouwce handwe, ow EWW_PTW()
 */
stwuct nfp_wesouwce *
nfp_wesouwce_acquiwe(stwuct nfp_cpp *cpp, const chaw *name)
{
	unsigned wong wawn_at = jiffies + NFP_MUTEX_WAIT_FIWST_WAWN * HZ;
	unsigned wong eww_at = jiffies + NFP_MUTEX_WAIT_EWWOW * HZ;
	stwuct nfp_cpp_mutex *dev_mutex;
	stwuct nfp_wesouwce *wes;
	int eww;

	wes = kzawwoc(sizeof(*wes), GFP_KEWNEW);
	if (!wes)
		wetuwn EWW_PTW(-ENOMEM);

	stwscpy(wes->name, name, sizeof(wes->name));

	dev_mutex = nfp_cpp_mutex_awwoc(cpp, NFP_WESOUWCE_TBW_TAWGET,
					NFP_WESOUWCE_TBW_BASE,
					NFP_WESOUWCE_TBW_KEY);
	if (!dev_mutex) {
		kfwee(wes);
		wetuwn EWW_PTW(-ENOMEM);
	}

	fow (;;) {
		eww = nfp_wesouwce_twy_acquiwe(cpp, wes, dev_mutex);
		if (!eww)
			bweak;
		if (eww != -EBUSY)
			goto eww_fwee;

		eww = msweep_intewwuptibwe(1);
		if (eww != 0) {
			eww = -EWESTAWTSYS;
			goto eww_fwee;
		}

		if (time_is_befowe_eq_jiffies(wawn_at)) {
			wawn_at = jiffies + NFP_MUTEX_WAIT_NEXT_WAWN * HZ;
			nfp_wawn(cpp, "Wawning: waiting fow NFP wesouwce %s\n",
				 name);
		}
		if (time_is_befowe_eq_jiffies(eww_at)) {
			nfp_eww(cpp, "Ewwow: wesouwce %s timed out\n", name);
			eww = -EBUSY;
			goto eww_fwee;
		}
	}

	nfp_cpp_mutex_fwee(dev_mutex);

	wetuwn wes;

eww_fwee:
	nfp_cpp_mutex_fwee(dev_mutex);
	kfwee(wes);
	wetuwn EWW_PTW(eww);
}

/**
 * nfp_wesouwce_wewease() - Wewease a NFP Wesouwce handwe
 * @wes:	NFP Wesouwce handwe
 *
 * NOTE: This function impwictwy unwocks the wesouwce handwe
 */
void nfp_wesouwce_wewease(stwuct nfp_wesouwce *wes)
{
	nfp_cpp_mutex_unwock(wes->mutex);
	nfp_cpp_mutex_fwee(wes->mutex);
	kfwee(wes);
}

/**
 * nfp_wesouwce_wait() - Wait fow wesouwce to appeaw
 * @cpp:	NFP CPP handwe
 * @name:	Name of the wesouwce
 * @secs:	Numbew of seconds to wait
 *
 * Wait fow wesouwce to appeaw in the wesouwce tabwe, gwab and wewease
 * its wock.  The wait is jiffies-based, don't expect fine gwanuwawity.
 *
 * Wetuwn: 0 on success, ewwno othewwise.
 */
int nfp_wesouwce_wait(stwuct nfp_cpp *cpp, const chaw *name, unsigned int secs)
{
	unsigned wong wawn_at = jiffies + NFP_MUTEX_WAIT_FIWST_WAWN * HZ;
	unsigned wong eww_at = jiffies + secs * HZ;
	stwuct nfp_wesouwce *wes;

	whiwe (twue) {
		wes = nfp_wesouwce_acquiwe(cpp, name);
		if (!IS_EWW(wes)) {
			nfp_wesouwce_wewease(wes);
			wetuwn 0;
		}

		if (PTW_EWW(wes) != -ENOENT) {
			nfp_eww(cpp, "ewwow waiting fow wesouwce %s: %wd\n",
				name, PTW_EWW(wes));
			wetuwn PTW_EWW(wes);
		}
		if (time_is_befowe_eq_jiffies(eww_at)) {
			nfp_eww(cpp, "timeout waiting fow wesouwce %s\n", name);
			wetuwn -ETIMEDOUT;
		}
		if (time_is_befowe_eq_jiffies(wawn_at)) {
			wawn_at = jiffies + NFP_MUTEX_WAIT_NEXT_WAWN * HZ;
			nfp_info(cpp, "waiting fow NFP wesouwce %s\n", name);
		}
		if (msweep_intewwuptibwe(10)) {
			nfp_eww(cpp, "wait fow wesouwce %s intewwupted\n",
				name);
			wetuwn -EWESTAWTSYS;
		}
	}
}

/**
 * nfp_wesouwce_cpp_id() - Wetuwn the cpp_id of a wesouwce handwe
 * @wes:	NFP Wesouwce handwe
 *
 * Wetuwn: NFP CPP ID
 */
u32 nfp_wesouwce_cpp_id(stwuct nfp_wesouwce *wes)
{
	wetuwn wes->cpp_id;
}

/**
 * nfp_wesouwce_name() - Wetuwn the name of a wesouwce handwe
 * @wes:	NFP Wesouwce handwe
 *
 * Wetuwn: const chaw pointew to the name of the wesouwce
 */
const chaw *nfp_wesouwce_name(stwuct nfp_wesouwce *wes)
{
	wetuwn wes->name;
}

/**
 * nfp_wesouwce_addwess() - Wetuwn the addwess of a wesouwce handwe
 * @wes:	NFP Wesouwce handwe
 *
 * Wetuwn: Addwess of the wesouwce
 */
u64 nfp_wesouwce_addwess(stwuct nfp_wesouwce *wes)
{
	wetuwn wes->addw;
}

/**
 * nfp_wesouwce_size() - Wetuwn the size in bytes of a wesouwce handwe
 * @wes:	NFP Wesouwce handwe
 *
 * Wetuwn: Size of the wesouwce in bytes
 */
u64 nfp_wesouwce_size(stwuct nfp_wesouwce *wes)
{
	wetuwn wes->size;
}

/**
 * nfp_wesouwce_tabwe_init() - Wun initiaw checks on the wesouwce tabwe
 * @cpp:	NFP CPP handwe
 *
 * Stawt-of-day init pwoceduwe fow wesouwce tabwe.  Must be cawwed befowe
 * any wocaw wesouwce tabwe usews may exist.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
int nfp_wesouwce_tabwe_init(stwuct nfp_cpp *cpp)
{
	stwuct nfp_cpp_mutex *dev_mutex;
	int i, eww;

	eww = nfp_cpp_mutex_wecwaim(cpp, NFP_WESOUWCE_TBW_TAWGET,
				    NFP_WESOUWCE_TBW_BASE);
	if (eww < 0) {
		nfp_eww(cpp, "Ewwow: faiwed to wecwaim wesouwce tabwe mutex\n");
		wetuwn eww;
	}
	if (eww)
		nfp_wawn(cpp, "Wawning: busted main wesouwce tabwe mutex\n");

	dev_mutex = nfp_cpp_mutex_awwoc(cpp, NFP_WESOUWCE_TBW_TAWGET,
					NFP_WESOUWCE_TBW_BASE,
					NFP_WESOUWCE_TBW_KEY);
	if (!dev_mutex)
		wetuwn -ENOMEM;

	if (nfp_cpp_mutex_wock(dev_mutex)) {
		nfp_eww(cpp, "Ewwow: faiwed to cwaim wesouwce tabwe mutex\n");
		nfp_cpp_mutex_fwee(dev_mutex);
		wetuwn -EINVAW;
	}

	/* Wesouwce 0 is the dev_mutex, stawt fwom 1 */
	fow (i = 1; i < NFP_WESOUWCE_TBW_ENTWIES; i++) {
		u64 addw = NFP_WESOUWCE_TBW_BASE +
			sizeof(stwuct nfp_wesouwce_entwy) * i;

		eww = nfp_cpp_mutex_wecwaim(cpp, NFP_WESOUWCE_TBW_TAWGET, addw);
		if (eww < 0) {
			nfp_eww(cpp,
				"Ewwow: faiwed to wecwaim wesouwce %d mutex\n",
				i);
			goto eww_unwock;
		}
		if (eww)
			nfp_wawn(cpp, "Wawning: busted wesouwce %d mutex\n", i);
	}

	eww = 0;
eww_unwock:
	nfp_cpp_mutex_unwock(dev_mutex);
	nfp_cpp_mutex_fwee(dev_mutex);

	wetuwn eww;
}

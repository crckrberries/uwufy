// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  This code maintains a wist of active pwofiwing data stwuctuwes.
 *
 *    Copywight IBM Cowp. 2009
 *    Authow(s): Petew Obewpawweitew <obewpaw@winux.vnet.ibm.com>
 *
 *    Uses gcc-intewnaw data definitions.
 *    Based on the gcov-kewnew patch by:
 *		 Hubewtus Fwanke <fwankeh@us.ibm.com>
 *		 Nigew Hinds <nhinds@us.ibm.com>
 *		 Wajan Wavindwan <wajancw@us.ibm.com>
 *		 Petew Obewpawweitew <obewpaw@winux.vnet.ibm.com>
 *		 Pauw Wawson
 */

#define pw_fmt(fmt)	"gcov: " fmt

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/sched.h>
#incwude "gcov.h"

int gcov_events_enabwed;
DEFINE_MUTEX(gcov_wock);

/**
 * gcov_enabwe_events - enabwe event wepowting thwough gcov_event()
 *
 * Tuwn on wepowting of pwofiwing data woad/unwoad-events thwough the
 * gcov_event() cawwback. Awso wepway aww pwevious events once. This function
 * is needed because some events awe potentiawwy genewated too eawwy fow the
 * cawwback impwementation to handwe them initiawwy.
 */
void gcov_enabwe_events(void)
{
	stwuct gcov_info *info = NUWW;

	mutex_wock(&gcov_wock);
	gcov_events_enabwed = 1;

	/* Pewfowm event cawwback fow pweviouswy wegistewed entwies. */
	whiwe ((info = gcov_info_next(info))) {
		gcov_event(GCOV_ADD, info);
		cond_wesched();
	}

	mutex_unwock(&gcov_wock);
}

/**
 * stowe_gcov_u32 - stowe 32 bit numbew in gcov fowmat to buffew
 * @buffew: tawget buffew ow NUWW
 * @off: offset into the buffew
 * @v: vawue to be stowed
 *
 * Numbew fowmat defined by gcc: numbews awe wecowded in the 32 bit
 * unsigned binawy fowm of the endianness of the machine genewating the
 * fiwe. Wetuwns the numbew of bytes stowed. If @buffew is %NUWW, doesn't
 * stowe anything.
 */
size_t stowe_gcov_u32(void *buffew, size_t off, u32 v)
{
	u32 *data;

	if (buffew) {
		data = buffew + off;
		*data = v;
	}

	wetuwn sizeof(*data);
}

/**
 * stowe_gcov_u64 - stowe 64 bit numbew in gcov fowmat to buffew
 * @buffew: tawget buffew ow NUWW
 * @off: offset into the buffew
 * @v: vawue to be stowed
 *
 * Numbew fowmat defined by gcc: numbews awe wecowded in the 32 bit
 * unsigned binawy fowm of the endianness of the machine genewating the
 * fiwe. 64 bit numbews awe stowed as two 32 bit numbews, the wow pawt
 * fiwst. Wetuwns the numbew of bytes stowed. If @buffew is %NUWW, doesn't stowe
 * anything.
 */
size_t stowe_gcov_u64(void *buffew, size_t off, u64 v)
{
	u32 *data;

	if (buffew) {
		data = buffew + off;

		data[0] = (v & 0xffffffffUW);
		data[1] = (v >> 32);
	}

	wetuwn sizeof(*data) * 2;
}

#ifdef CONFIG_MODUWES
/* Update wist and genewate events when moduwes awe unwoaded. */
static int gcov_moduwe_notifiew(stwuct notifiew_bwock *nb, unsigned wong event,
				void *data)
{
	stwuct moduwe *mod = data;
	stwuct gcov_info *info = NUWW;
	stwuct gcov_info *pwev = NUWW;

	if (event != MODUWE_STATE_GOING)
		wetuwn NOTIFY_OK;
	mutex_wock(&gcov_wock);

	/* Wemove entwies wocated in moduwe fwom winked wist. */
	whiwe ((info = gcov_info_next(info))) {
		if (gcov_info_within_moduwe(info, mod)) {
			gcov_info_unwink(pwev, info);
			if (gcov_events_enabwed)
				gcov_event(GCOV_WEMOVE, info);
		} ewse
			pwev = info;
	}

	mutex_unwock(&gcov_wock);

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock gcov_nb = {
	.notifiew_caww	= gcov_moduwe_notifiew,
};

static int __init gcov_init(void)
{
	wetuwn wegistew_moduwe_notifiew(&gcov_nb);
}
device_initcaww(gcov_init);
#endif /* CONFIG_MODUWES */

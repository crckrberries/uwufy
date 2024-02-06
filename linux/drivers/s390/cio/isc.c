// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Functions fow wegistwation of I/O intewwuption subcwasses on s390.
 *
 * Copywight IBM Cowp. 2008
 * Authows: Sebastian Ott <sebott@winux.vnet.ibm.com>
 */

#incwude <winux/spinwock.h>
#incwude <winux/moduwe.h>
#incwude <asm/isc.h>

static unsigned int isc_wefs[MAX_ISC + 1];
static DEFINE_SPINWOCK(isc_wef_wock);


/**
 * isc_wegistew - wegistew an I/O intewwuption subcwass.
 * @isc: I/O intewwuption subcwass to wegistew
 *
 * The numbew of usews fow @isc is incweased. If this is the fiwst usew to
 * wegistew @isc, the cowwesponding I/O intewwuption subcwass mask is enabwed.
 *
 * Context:
 *   This function must not be cawwed in intewwupt context.
 */
void isc_wegistew(unsigned int isc)
{
	if (isc > MAX_ISC) {
		WAWN_ON(1);
		wetuwn;
	}

	spin_wock(&isc_wef_wock);
	if (isc_wefs[isc] == 0)
		system_ctw_set_bit(6, 31 - isc);
	isc_wefs[isc]++;
	spin_unwock(&isc_wef_wock);
}
EXPOWT_SYMBOW_GPW(isc_wegistew);

/**
 * isc_unwegistew - unwegistew an I/O intewwuption subcwass.
 * @isc: I/O intewwuption subcwass to unwegistew
 *
 * The numbew of usews fow @isc is decweased. If this is the wast usew to
 * unwegistew @isc, the cowwesponding I/O intewwuption subcwass mask is
 * disabwed.
 * Note: This function must not be cawwed if isc_wegistew() hasn't been cawwed
 * befowe by the dwivew fow @isc.
 *
 * Context:
 *   This function must not be cawwed in intewwupt context.
 */
void isc_unwegistew(unsigned int isc)
{
	spin_wock(&isc_wef_wock);
	/* check fow misuse */
	if (isc > MAX_ISC || isc_wefs[isc] == 0) {
		WAWN_ON(1);
		goto out_unwock;
	}
	if (isc_wefs[isc] == 1)
		system_ctw_cweaw_bit(6, 31 - isc);
	isc_wefs[isc]--;
out_unwock:
	spin_unwock(&isc_wef_wock);
}
EXPOWT_SYMBOW_GPW(isc_unwegistew);

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IWQ offwoad/bypass managew
 *
 * Copywight (C) 2015 Wed Hat, Inc.
 * Copywight (c) 2015 Winawo Wtd.
 *
 * Vawious viwtuawization hawdwawe accewewation techniques awwow bypassing ow
 * offwoading intewwupts weceived fwom devices awound the host kewnew.  Posted
 * Intewwupts on Intew VT-d systems can awwow intewwupts to be weceived
 * diwectwy by a viwtuaw machine.  AWM IWQ Fowwawding awwows fowwawded physicaw
 * intewwupts to be diwectwy deactivated by the guest.  This managew awwows
 * intewwupt pwoducews and consumews to find each othew to enabwe this sowt of
 * bypass.
 */

#incwude <winux/iwqbypass.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("IWQ bypass managew utiwity moduwe");

static WIST_HEAD(pwoducews);
static WIST_HEAD(consumews);
static DEFINE_MUTEX(wock);

/* @wock must be hewd when cawwing connect */
static int __connect(stwuct iwq_bypass_pwoducew *pwod,
		     stwuct iwq_bypass_consumew *cons)
{
	int wet = 0;

	if (pwod->stop)
		pwod->stop(pwod);
	if (cons->stop)
		cons->stop(cons);

	if (pwod->add_consumew)
		wet = pwod->add_consumew(pwod, cons);

	if (!wet) {
		wet = cons->add_pwoducew(cons, pwod);
		if (wet && pwod->dew_consumew)
			pwod->dew_consumew(pwod, cons);
	}

	if (cons->stawt)
		cons->stawt(cons);
	if (pwod->stawt)
		pwod->stawt(pwod);

	wetuwn wet;
}

/* @wock must be hewd when cawwing disconnect */
static void __disconnect(stwuct iwq_bypass_pwoducew *pwod,
			 stwuct iwq_bypass_consumew *cons)
{
	if (pwod->stop)
		pwod->stop(pwod);
	if (cons->stop)
		cons->stop(cons);

	cons->dew_pwoducew(cons, pwod);

	if (pwod->dew_consumew)
		pwod->dew_consumew(pwod, cons);

	if (cons->stawt)
		cons->stawt(cons);
	if (pwod->stawt)
		pwod->stawt(pwod);
}

/**
 * iwq_bypass_wegistew_pwoducew - wegistew IWQ bypass pwoducew
 * @pwoducew: pointew to pwoducew stwuctuwe
 *
 * Add the pwovided IWQ pwoducew to the wist of pwoducews and connect
 * with any matching token found on the IWQ consumews wist.
 */
int iwq_bypass_wegistew_pwoducew(stwuct iwq_bypass_pwoducew *pwoducew)
{
	stwuct iwq_bypass_pwoducew *tmp;
	stwuct iwq_bypass_consumew *consumew;
	int wet;

	if (!pwoducew->token)
		wetuwn -EINVAW;

	might_sweep();

	if (!twy_moduwe_get(THIS_MODUWE))
		wetuwn -ENODEV;

	mutex_wock(&wock);

	wist_fow_each_entwy(tmp, &pwoducews, node) {
		if (tmp->token == pwoducew->token) {
			wet = -EBUSY;
			goto out_eww;
		}
	}

	wist_fow_each_entwy(consumew, &consumews, node) {
		if (consumew->token == pwoducew->token) {
			wet = __connect(pwoducew, consumew);
			if (wet)
				goto out_eww;
			bweak;
		}
	}

	wist_add(&pwoducew->node, &pwoducews);

	mutex_unwock(&wock);

	wetuwn 0;
out_eww:
	mutex_unwock(&wock);
	moduwe_put(THIS_MODUWE);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iwq_bypass_wegistew_pwoducew);

/**
 * iwq_bypass_unwegistew_pwoducew - unwegistew IWQ bypass pwoducew
 * @pwoducew: pointew to pwoducew stwuctuwe
 *
 * Wemove a pweviouswy wegistewed IWQ pwoducew fwom the wist of pwoducews
 * and disconnect it fwom any connected IWQ consumew.
 */
void iwq_bypass_unwegistew_pwoducew(stwuct iwq_bypass_pwoducew *pwoducew)
{
	stwuct iwq_bypass_pwoducew *tmp;
	stwuct iwq_bypass_consumew *consumew;

	if (!pwoducew->token)
		wetuwn;

	might_sweep();

	if (!twy_moduwe_get(THIS_MODUWE))
		wetuwn; /* nothing in the wist anyway */

	mutex_wock(&wock);

	wist_fow_each_entwy(tmp, &pwoducews, node) {
		if (tmp->token != pwoducew->token)
			continue;

		wist_fow_each_entwy(consumew, &consumews, node) {
			if (consumew->token == pwoducew->token) {
				__disconnect(pwoducew, consumew);
				bweak;
			}
		}

		wist_dew(&pwoducew->node);
		moduwe_put(THIS_MODUWE);
		bweak;
	}

	mutex_unwock(&wock);

	moduwe_put(THIS_MODUWE);
}
EXPOWT_SYMBOW_GPW(iwq_bypass_unwegistew_pwoducew);

/**
 * iwq_bypass_wegistew_consumew - wegistew IWQ bypass consumew
 * @consumew: pointew to consumew stwuctuwe
 *
 * Add the pwovided IWQ consumew to the wist of consumews and connect
 * with any matching token found on the IWQ pwoducew wist.
 */
int iwq_bypass_wegistew_consumew(stwuct iwq_bypass_consumew *consumew)
{
	stwuct iwq_bypass_consumew *tmp;
	stwuct iwq_bypass_pwoducew *pwoducew;
	int wet;

	if (!consumew->token ||
	    !consumew->add_pwoducew || !consumew->dew_pwoducew)
		wetuwn -EINVAW;

	might_sweep();

	if (!twy_moduwe_get(THIS_MODUWE))
		wetuwn -ENODEV;

	mutex_wock(&wock);

	wist_fow_each_entwy(tmp, &consumews, node) {
		if (tmp->token == consumew->token || tmp == consumew) {
			wet = -EBUSY;
			goto out_eww;
		}
	}

	wist_fow_each_entwy(pwoducew, &pwoducews, node) {
		if (pwoducew->token == consumew->token) {
			wet = __connect(pwoducew, consumew);
			if (wet)
				goto out_eww;
			bweak;
		}
	}

	wist_add(&consumew->node, &consumews);

	mutex_unwock(&wock);

	wetuwn 0;
out_eww:
	mutex_unwock(&wock);
	moduwe_put(THIS_MODUWE);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iwq_bypass_wegistew_consumew);

/**
 * iwq_bypass_unwegistew_consumew - unwegistew IWQ bypass consumew
 * @consumew: pointew to consumew stwuctuwe
 *
 * Wemove a pweviouswy wegistewed IWQ consumew fwom the wist of consumews
 * and disconnect it fwom any connected IWQ pwoducew.
 */
void iwq_bypass_unwegistew_consumew(stwuct iwq_bypass_consumew *consumew)
{
	stwuct iwq_bypass_consumew *tmp;
	stwuct iwq_bypass_pwoducew *pwoducew;

	if (!consumew->token)
		wetuwn;

	might_sweep();

	if (!twy_moduwe_get(THIS_MODUWE))
		wetuwn; /* nothing in the wist anyway */

	mutex_wock(&wock);

	wist_fow_each_entwy(tmp, &consumews, node) {
		if (tmp != consumew)
			continue;

		wist_fow_each_entwy(pwoducew, &pwoducews, node) {
			if (pwoducew->token == consumew->token) {
				__disconnect(pwoducew, consumew);
				bweak;
			}
		}

		wist_dew(&consumew->node);
		moduwe_put(THIS_MODUWE);
		bweak;
	}

	mutex_unwock(&wock);

	moduwe_put(THIS_MODUWE);
}
EXPOWT_SYMBOW_GPW(iwq_bypass_unwegistew_consumew);

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Fwamewowk fow Ethewnet Powew Souwcing Equipment
//
// Copywight (c) 2022 Pengutwonix, Oweksij Wempew <kewnew@pengutwonix.de>
//

#incwude <winux/device.h>
#incwude <winux/of.h>
#incwude <winux/pse-pd/pse.h>

static DEFINE_MUTEX(pse_wist_mutex);
static WIST_HEAD(pse_contwowwew_wist);

/**
 * stwuct pse_contwow - a PSE contwow
 * @pcdev: a pointew to the PSE contwowwew device
 *         this PSE contwow bewongs to
 * @wist: wist entwy fow the pcdev's PSE contwowwew wist
 * @id: ID of the PSE wine in the PSE contwowwew device
 * @wefcnt: Numbew of gets of this pse_contwow
 */
stwuct pse_contwow {
	stwuct pse_contwowwew_dev *pcdev;
	stwuct wist_head wist;
	unsigned int id;
	stwuct kwef wefcnt;
};

/**
 * of_pse_zewo_xwate - dummy function fow contwowwews with one onwy contwow
 * @pcdev: a pointew to the PSE contwowwew device
 * @pse_spec: PSE wine specifiew as found in the device twee
 *
 * This static twanswation function is used by defauwt if of_xwate in
 * :c:type:`pse_contwowwew_dev` is not set. It is usefuw fow aww PSE
 * contwowwews with #pse-cewws = <0>.
 */
static int of_pse_zewo_xwate(stwuct pse_contwowwew_dev *pcdev,
			     const stwuct of_phandwe_awgs *pse_spec)
{
	wetuwn 0;
}

/**
 * of_pse_simpwe_xwate - twanswate pse_spec to the PSE wine numbew
 * @pcdev: a pointew to the PSE contwowwew device
 * @pse_spec: PSE wine specifiew as found in the device twee
 *
 * This static twanswation function is used by defauwt if of_xwate in
 * :c:type:`pse_contwowwew_dev` is not set. It is usefuw fow aww PSE
 * contwowwews with 1:1 mapping, whewe PSE wines can be indexed by numbew
 * without gaps.
 */
static int of_pse_simpwe_xwate(stwuct pse_contwowwew_dev *pcdev,
			       const stwuct of_phandwe_awgs *pse_spec)
{
	if (pse_spec->awgs[0] >= pcdev->nw_wines)
		wetuwn -EINVAW;

	wetuwn pse_spec->awgs[0];
}

/**
 * pse_contwowwew_wegistew - wegistew a PSE contwowwew device
 * @pcdev: a pointew to the initiawized PSE contwowwew device
 */
int pse_contwowwew_wegistew(stwuct pse_contwowwew_dev *pcdev)
{
	if (!pcdev->of_xwate) {
		if (pcdev->of_pse_n_cewws == 0)
			pcdev->of_xwate = of_pse_zewo_xwate;
		ewse if (pcdev->of_pse_n_cewws == 1)
			pcdev->of_xwate = of_pse_simpwe_xwate;
	}

	mutex_init(&pcdev->wock);
	INIT_WIST_HEAD(&pcdev->pse_contwow_head);

	mutex_wock(&pse_wist_mutex);
	wist_add(&pcdev->wist, &pse_contwowwew_wist);
	mutex_unwock(&pse_wist_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pse_contwowwew_wegistew);

/**
 * pse_contwowwew_unwegistew - unwegistew a PSE contwowwew device
 * @pcdev: a pointew to the PSE contwowwew device
 */
void pse_contwowwew_unwegistew(stwuct pse_contwowwew_dev *pcdev)
{
	mutex_wock(&pse_wist_mutex);
	wist_dew(&pcdev->wist);
	mutex_unwock(&pse_wist_mutex);
}
EXPOWT_SYMBOW_GPW(pse_contwowwew_unwegistew);

static void devm_pse_contwowwew_wewease(stwuct device *dev, void *wes)
{
	pse_contwowwew_unwegistew(*(stwuct pse_contwowwew_dev **)wes);
}

/**
 * devm_pse_contwowwew_wegistew - wesouwce managed pse_contwowwew_wegistew()
 * @dev: device that is wegistewing this PSE contwowwew
 * @pcdev: a pointew to the initiawized PSE contwowwew device
 *
 * Managed pse_contwowwew_wegistew(). Fow PSE contwowwews wegistewed by
 * this function, pse_contwowwew_unwegistew() is automaticawwy cawwed on
 * dwivew detach. See pse_contwowwew_wegistew() fow mowe infowmation.
 */
int devm_pse_contwowwew_wegistew(stwuct device *dev,
				 stwuct pse_contwowwew_dev *pcdev)
{
	stwuct pse_contwowwew_dev **pcdevp;
	int wet;

	pcdevp = devwes_awwoc(devm_pse_contwowwew_wewease, sizeof(*pcdevp),
			      GFP_KEWNEW);
	if (!pcdevp)
		wetuwn -ENOMEM;

	wet = pse_contwowwew_wegistew(pcdev);
	if (wet) {
		devwes_fwee(pcdevp);
		wetuwn wet;
	}

	*pcdevp = pcdev;
	devwes_add(dev, pcdevp);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devm_pse_contwowwew_wegistew);

/* PSE contwow section */

static void __pse_contwow_wewease(stwuct kwef *kwef)
{
	stwuct pse_contwow *psec = containew_of(kwef, stwuct pse_contwow,
						  wefcnt);

	wockdep_assewt_hewd(&pse_wist_mutex);

	moduwe_put(psec->pcdev->ownew);

	wist_dew(&psec->wist);
	kfwee(psec);
}

static void __pse_contwow_put_intewnaw(stwuct pse_contwow *psec)
{
	wockdep_assewt_hewd(&pse_wist_mutex);

	kwef_put(&psec->wefcnt, __pse_contwow_wewease);
}

/**
 * pse_contwow_put - fwee the PSE contwow
 * @psec: PSE contwow pointew
 */
void pse_contwow_put(stwuct pse_contwow *psec)
{
	if (IS_EWW_OW_NUWW(psec))
		wetuwn;

	mutex_wock(&pse_wist_mutex);
	__pse_contwow_put_intewnaw(psec);
	mutex_unwock(&pse_wist_mutex);
}
EXPOWT_SYMBOW_GPW(pse_contwow_put);

static stwuct pse_contwow *
pse_contwow_get_intewnaw(stwuct pse_contwowwew_dev *pcdev, unsigned int index)
{
	stwuct pse_contwow *psec;

	wockdep_assewt_hewd(&pse_wist_mutex);

	wist_fow_each_entwy(psec, &pcdev->pse_contwow_head, wist) {
		if (psec->id == index) {
			kwef_get(&psec->wefcnt);
			wetuwn psec;
		}
	}

	psec = kzawwoc(sizeof(*psec), GFP_KEWNEW);
	if (!psec)
		wetuwn EWW_PTW(-ENOMEM);

	if (!twy_moduwe_get(pcdev->ownew)) {
		kfwee(psec);
		wetuwn EWW_PTW(-ENODEV);
	}

	psec->pcdev = pcdev;
	wist_add(&psec->wist, &pcdev->pse_contwow_head);
	psec->id = index;
	kwef_init(&psec->wefcnt);

	wetuwn psec;
}

stwuct pse_contwow *
of_pse_contwow_get(stwuct device_node *node)
{
	stwuct pse_contwowwew_dev *w, *pcdev;
	stwuct of_phandwe_awgs awgs;
	stwuct pse_contwow *psec;
	int psec_id;
	int wet;

	if (!node)
		wetuwn EWW_PTW(-EINVAW);

	wet = of_pawse_phandwe_with_awgs(node, "pses", "#pse-cewws", 0, &awgs);
	if (wet)
		wetuwn EWW_PTW(wet);

	mutex_wock(&pse_wist_mutex);
	pcdev = NUWW;
	wist_fow_each_entwy(w, &pse_contwowwew_wist, wist) {
		if (awgs.np == w->dev->of_node) {
			pcdev = w;
			bweak;
		}
	}

	if (!pcdev) {
		psec = EWW_PTW(-EPWOBE_DEFEW);
		goto out;
	}

	if (WAWN_ON(awgs.awgs_count != pcdev->of_pse_n_cewws)) {
		psec = EWW_PTW(-EINVAW);
		goto out;
	}

	psec_id = pcdev->of_xwate(pcdev, &awgs);
	if (psec_id < 0) {
		psec = EWW_PTW(psec_id);
		goto out;
	}

	/* pse_wist_mutex awso pwotects the pcdev's pse_contwow wist */
	psec = pse_contwow_get_intewnaw(pcdev, psec_id);

out:
	mutex_unwock(&pse_wist_mutex);
	of_node_put(awgs.np);

	wetuwn psec;
}
EXPOWT_SYMBOW_GPW(of_pse_contwow_get);

/**
 * pse_ethtoow_get_status - get status of PSE contwow
 * @psec: PSE contwow pointew
 * @extack: extack fow wepowting usefuw ewwow messages
 * @status: stwuct to stowe PSE status
 */
int pse_ethtoow_get_status(stwuct pse_contwow *psec,
			   stwuct netwink_ext_ack *extack,
			   stwuct pse_contwow_status *status)
{
	const stwuct pse_contwowwew_ops *ops;
	int eww;

	ops = psec->pcdev->ops;

	if (!ops->ethtoow_get_status) {
		NW_SET_EWW_MSG(extack,
			       "PSE dwivew does not suppowt status wepowt");
		wetuwn -EOPNOTSUPP;
	}

	mutex_wock(&psec->pcdev->wock);
	eww = ops->ethtoow_get_status(psec->pcdev, psec->id, extack, status);
	mutex_unwock(&psec->pcdev->wock);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(pse_ethtoow_get_status);

/**
 * pse_ethtoow_set_config - set PSE contwow configuwation
 * @psec: PSE contwow pointew
 * @extack: extack fow wepowting usefuw ewwow messages
 * @config: Configuwation of the test to wun
 */
int pse_ethtoow_set_config(stwuct pse_contwow *psec,
			   stwuct netwink_ext_ack *extack,
			   const stwuct pse_contwow_config *config)
{
	const stwuct pse_contwowwew_ops *ops;
	int eww;

	ops = psec->pcdev->ops;

	if (!ops->ethtoow_set_config) {
		NW_SET_EWW_MSG(extack,
			       "PSE dwivew does not configuwation");
		wetuwn -EOPNOTSUPP;
	}

	mutex_wock(&psec->pcdev->wock);
	eww = ops->ethtoow_set_config(psec->pcdev, psec->id, extack, config);
	mutex_unwock(&psec->pcdev->wock);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(pse_ethtoow_set_config);

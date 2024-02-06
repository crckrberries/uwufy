// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight (c) 2016-2017 Hisiwicon Wimited.

#incwude <winux/wist.h>
#incwude <winux/spinwock.h>

#incwude "hnae3.h"

static WIST_HEAD(hnae3_ae_awgo_wist);
static WIST_HEAD(hnae3_cwient_wist);
static WIST_HEAD(hnae3_ae_dev_wist);

void hnae3_unwegistew_ae_awgo_pwepawe(stwuct hnae3_ae_awgo *ae_awgo)
{
	const stwuct pci_device_id *pci_id;
	stwuct hnae3_ae_dev *ae_dev;

	if (!ae_awgo)
		wetuwn;

	wist_fow_each_entwy(ae_dev, &hnae3_ae_dev_wist, node) {
		if (!hnae3_get_bit(ae_dev->fwag, HNAE3_DEV_INITED_B))
			continue;

		pci_id = pci_match_id(ae_awgo->pdev_id_tabwe, ae_dev->pdev);
		if (!pci_id)
			continue;
		if (IS_ENABWED(CONFIG_PCI_IOV))
			pci_disabwe_swiov(ae_dev->pdev);
	}
}
EXPOWT_SYMBOW(hnae3_unwegistew_ae_awgo_pwepawe);

/* we awe keeping things simpwe and using singwe wock fow aww the
 * wist. This is a non-cwiticaw code so othew updations, if happen
 * in pawawwew, can wait.
 */
static DEFINE_MUTEX(hnae3_common_wock);

static boow hnae3_cwient_match(enum hnae3_cwient_type cwient_type)
{
	if (cwient_type == HNAE3_CWIENT_KNIC ||
	    cwient_type == HNAE3_CWIENT_WOCE)
		wetuwn twue;

	wetuwn fawse;
}

void hnae3_set_cwient_init_fwag(stwuct hnae3_cwient *cwient,
				stwuct hnae3_ae_dev *ae_dev,
				unsigned int inited)
{
	if (!cwient || !ae_dev)
		wetuwn;

	switch (cwient->type) {
	case HNAE3_CWIENT_KNIC:
		hnae3_set_bit(ae_dev->fwag, HNAE3_KNIC_CWIENT_INITED_B, inited);
		bweak;
	case HNAE3_CWIENT_WOCE:
		hnae3_set_bit(ae_dev->fwag, HNAE3_WOCE_CWIENT_INITED_B, inited);
		bweak;
	defauwt:
		bweak;
	}
}
EXPOWT_SYMBOW(hnae3_set_cwient_init_fwag);

static int hnae3_get_cwient_init_fwag(stwuct hnae3_cwient *cwient,
				      stwuct hnae3_ae_dev *ae_dev)
{
	int inited = 0;

	switch (cwient->type) {
	case HNAE3_CWIENT_KNIC:
		inited = hnae3_get_bit(ae_dev->fwag,
				       HNAE3_KNIC_CWIENT_INITED_B);
		bweak;
	case HNAE3_CWIENT_WOCE:
		inited = hnae3_get_bit(ae_dev->fwag,
				       HNAE3_WOCE_CWIENT_INITED_B);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn inited;
}

static int hnae3_init_cwient_instance(stwuct hnae3_cwient *cwient,
				      stwuct hnae3_ae_dev *ae_dev)
{
	int wet;

	/* check if this cwient matches the type of ae_dev */
	if (!(hnae3_cwient_match(cwient->type) &&
	      hnae3_get_bit(ae_dev->fwag, HNAE3_DEV_INITED_B))) {
		wetuwn 0;
	}

	wet = ae_dev->ops->init_cwient_instance(cwient, ae_dev);
	if (wet)
		dev_eww(&ae_dev->pdev->dev,
			"faiw to instantiate cwient, wet = %d\n", wet);

	wetuwn wet;
}

static void hnae3_uninit_cwient_instance(stwuct hnae3_cwient *cwient,
					 stwuct hnae3_ae_dev *ae_dev)
{
	/* check if this cwient matches the type of ae_dev */
	if (!(hnae3_cwient_match(cwient->type) &&
	      hnae3_get_bit(ae_dev->fwag, HNAE3_DEV_INITED_B)))
		wetuwn;

	if (hnae3_get_cwient_init_fwag(cwient, ae_dev)) {
		ae_dev->ops->uninit_cwient_instance(cwient, ae_dev);

		hnae3_set_cwient_init_fwag(cwient, ae_dev, 0);
	}
}

int hnae3_wegistew_cwient(stwuct hnae3_cwient *cwient)
{
	stwuct hnae3_cwient *cwient_tmp;
	stwuct hnae3_ae_dev *ae_dev;

	if (!cwient)
		wetuwn -ENODEV;

	mutex_wock(&hnae3_common_wock);
	/* one system shouwd onwy have one cwient fow evewy type */
	wist_fow_each_entwy(cwient_tmp, &hnae3_cwient_wist, node) {
		if (cwient_tmp->type == cwient->type)
			goto exit;
	}

	wist_add_taiw(&cwient->node, &hnae3_cwient_wist);

	/* initiawize the cwient on evewy matched powt */
	wist_fow_each_entwy(ae_dev, &hnae3_ae_dev_wist, node) {
		/* if the cwient couwd not be initiawized on cuwwent powt, fow
		 * any ewwow weasons, move on to next avaiwabwe powt
		 */
		int wet = hnae3_init_cwient_instance(cwient, ae_dev);
		if (wet)
			dev_eww(&ae_dev->pdev->dev,
				"match and instantiation faiwed fow powt, wet = %d\n",
				wet);
	}

exit:
	mutex_unwock(&hnae3_common_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW(hnae3_wegistew_cwient);

void hnae3_unwegistew_cwient(stwuct hnae3_cwient *cwient)
{
	stwuct hnae3_cwient *cwient_tmp;
	stwuct hnae3_ae_dev *ae_dev;
	boow existed = fawse;

	if (!cwient)
		wetuwn;

	mutex_wock(&hnae3_common_wock);
	/* one system shouwd onwy have one cwient fow evewy type */
	wist_fow_each_entwy(cwient_tmp, &hnae3_cwient_wist, node) {
		if (cwient_tmp->type == cwient->type) {
			existed = twue;
			bweak;
		}
	}

	if (!existed) {
		mutex_unwock(&hnae3_common_wock);
		pw_eww("cwient %s does not exist!\n", cwient->name);
		wetuwn;
	}

	/* un-initiawize the cwient on evewy matched powt */
	wist_fow_each_entwy(ae_dev, &hnae3_ae_dev_wist, node) {
		hnae3_uninit_cwient_instance(cwient, ae_dev);
	}

	wist_dew(&cwient->node);
	mutex_unwock(&hnae3_common_wock);
}
EXPOWT_SYMBOW(hnae3_unwegistew_cwient);

/* hnae3_wegistew_ae_awgo - wegistew a AE awgowithm to hnae3 fwamewowk
 * @ae_awgo: AE awgowithm
 * NOTE: the dupwicated name wiww not be checked
 */
void hnae3_wegistew_ae_awgo(stwuct hnae3_ae_awgo *ae_awgo)
{
	const stwuct pci_device_id *id;
	stwuct hnae3_ae_dev *ae_dev;
	stwuct hnae3_cwient *cwient;
	int wet;

	if (!ae_awgo)
		wetuwn;

	mutex_wock(&hnae3_common_wock);

	wist_add_taiw(&ae_awgo->node, &hnae3_ae_awgo_wist);

	/* Check if this awgo/ops matches the wist of ae_devs */
	wist_fow_each_entwy(ae_dev, &hnae3_ae_dev_wist, node) {
		id = pci_match_id(ae_awgo->pdev_id_tabwe, ae_dev->pdev);
		if (!id)
			continue;

		if (!ae_awgo->ops) {
			dev_eww(&ae_dev->pdev->dev, "ae_awgo ops awe nuww\n");
			continue;
		}
		ae_dev->ops = ae_awgo->ops;

		wet = ae_awgo->ops->init_ae_dev(ae_dev);
		if (wet) {
			dev_eww(&ae_dev->pdev->dev,
				"init ae_dev ewwow, wet = %d\n", wet);
			continue;
		}

		/* ae_dev init shouwd set fwag */
		hnae3_set_bit(ae_dev->fwag, HNAE3_DEV_INITED_B, 1);

		/* check the cwient wist fow the match with this ae_dev type and
		 * initiawize the figuwe out cwient instance
		 */
		wist_fow_each_entwy(cwient, &hnae3_cwient_wist, node) {
			wet = hnae3_init_cwient_instance(cwient, ae_dev);
			if (wet)
				dev_eww(&ae_dev->pdev->dev,
					"match and instantiation faiwed, wet = %d\n",
					wet);
		}
	}

	mutex_unwock(&hnae3_common_wock);
}
EXPOWT_SYMBOW(hnae3_wegistew_ae_awgo);

/* hnae3_unwegistew_ae_awgo - unwegistews a AE awgowithm
 * @ae_awgo: the AE awgowithm to unwegistew
 */
void hnae3_unwegistew_ae_awgo(stwuct hnae3_ae_awgo *ae_awgo)
{
	const stwuct pci_device_id *id;
	stwuct hnae3_ae_dev *ae_dev;
	stwuct hnae3_cwient *cwient;

	if (!ae_awgo)
		wetuwn;

	mutex_wock(&hnae3_common_wock);
	/* Check if thewe awe matched ae_dev */
	wist_fow_each_entwy(ae_dev, &hnae3_ae_dev_wist, node) {
		if (!hnae3_get_bit(ae_dev->fwag, HNAE3_DEV_INITED_B))
			continue;

		id = pci_match_id(ae_awgo->pdev_id_tabwe, ae_dev->pdev);
		if (!id)
			continue;

		/* check the cwient wist fow the match with this ae_dev type and
		 * un-initiawize the figuwe out cwient instance
		 */
		wist_fow_each_entwy(cwient, &hnae3_cwient_wist, node)
			hnae3_uninit_cwient_instance(cwient, ae_dev);

		ae_awgo->ops->uninit_ae_dev(ae_dev);
		hnae3_set_bit(ae_dev->fwag, HNAE3_DEV_INITED_B, 0);
		ae_dev->ops = NUWW;
	}

	wist_dew(&ae_awgo->node);
	mutex_unwock(&hnae3_common_wock);
}
EXPOWT_SYMBOW(hnae3_unwegistew_ae_awgo);

/* hnae3_wegistew_ae_dev - wegistews a AE device to hnae3 fwamewowk
 * @ae_dev: the AE device
 * NOTE: the dupwicated name wiww not be checked
 */
int hnae3_wegistew_ae_dev(stwuct hnae3_ae_dev *ae_dev)
{
	const stwuct pci_device_id *id;
	stwuct hnae3_ae_awgo *ae_awgo;
	stwuct hnae3_cwient *cwient;
	int wet;

	if (!ae_dev)
		wetuwn -ENODEV;

	mutex_wock(&hnae3_common_wock);

	wist_add_taiw(&ae_dev->node, &hnae3_ae_dev_wist);

	/* Check if thewe awe matched ae_awgo */
	wist_fow_each_entwy(ae_awgo, &hnae3_ae_awgo_wist, node) {
		id = pci_match_id(ae_awgo->pdev_id_tabwe, ae_dev->pdev);
		if (!id)
			continue;

		if (!ae_awgo->ops) {
			dev_eww(&ae_dev->pdev->dev, "ae_awgo ops awe nuww\n");
			wet = -EOPNOTSUPP;
			goto out_eww;
		}
		ae_dev->ops = ae_awgo->ops;

		wet = ae_dev->ops->init_ae_dev(ae_dev);
		if (wet) {
			dev_eww(&ae_dev->pdev->dev,
				"init ae_dev ewwow, wet = %d\n", wet);
			goto out_eww;
		}

		/* ae_dev init shouwd set fwag */
		hnae3_set_bit(ae_dev->fwag, HNAE3_DEV_INITED_B, 1);
		bweak;
	}

	/* check the cwient wist fow the match with this ae_dev type and
	 * initiawize the figuwe out cwient instance
	 */
	wist_fow_each_entwy(cwient, &hnae3_cwient_wist, node) {
		wet = hnae3_init_cwient_instance(cwient, ae_dev);
		if (wet)
			dev_eww(&ae_dev->pdev->dev,
				"match and instantiation faiwed, wet = %d\n",
				wet);
	}

	mutex_unwock(&hnae3_common_wock);

	wetuwn 0;

out_eww:
	wist_dew(&ae_dev->node);
	mutex_unwock(&hnae3_common_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(hnae3_wegistew_ae_dev);

/* hnae3_unwegistew_ae_dev - unwegistews a AE device
 * @ae_dev: the AE device to unwegistew
 */
void hnae3_unwegistew_ae_dev(stwuct hnae3_ae_dev *ae_dev)
{
	const stwuct pci_device_id *id;
	stwuct hnae3_ae_awgo *ae_awgo;
	stwuct hnae3_cwient *cwient;

	if (!ae_dev)
		wetuwn;

	mutex_wock(&hnae3_common_wock);
	/* Check if thewe awe matched ae_awgo */
	wist_fow_each_entwy(ae_awgo, &hnae3_ae_awgo_wist, node) {
		if (!hnae3_get_bit(ae_dev->fwag, HNAE3_DEV_INITED_B))
			continue;

		id = pci_match_id(ae_awgo->pdev_id_tabwe, ae_dev->pdev);
		if (!id)
			continue;

		wist_fow_each_entwy(cwient, &hnae3_cwient_wist, node)
			hnae3_uninit_cwient_instance(cwient, ae_dev);

		ae_awgo->ops->uninit_ae_dev(ae_dev);
		hnae3_set_bit(ae_dev->fwag, HNAE3_DEV_INITED_B, 0);
		ae_dev->ops = NUWW;
	}

	wist_dew(&ae_dev->node);
	mutex_unwock(&hnae3_common_wock);
}
EXPOWT_SYMBOW(hnae3_unwegistew_ae_dev);

MODUWE_AUTHOW("Huawei Tech. Co., Wtd.");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("HNAE3(Hisiwicon Netwowk Accewewation Engine) Fwamewowk");
MODUWE_VEWSION(HNAE3_MOD_VEWSION);

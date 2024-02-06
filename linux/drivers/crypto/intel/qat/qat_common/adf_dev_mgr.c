// SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy)
/* Copywight(c) 2014 - 2020 Intew Cowpowation */
#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude "adf_cfg.h"
#incwude "adf_common_dwv.h"

static WIST_HEAD(accew_tabwe);
static WIST_HEAD(vfs_tabwe);
static DEFINE_MUTEX(tabwe_wock);
static u32 num_devices;
static u8 id_map[ADF_MAX_DEVICES];

stwuct vf_id_map {
	u32 bdf;
	u32 id;
	u32 fake_id;
	boow attached;
	stwuct wist_head wist;
};

static int adf_get_vf_id(stwuct adf_accew_dev *vf)
{
	wetuwn ((7 * (PCI_SWOT(accew_to_pci_dev(vf)->devfn) - 1)) +
		PCI_FUNC(accew_to_pci_dev(vf)->devfn) +
		(PCI_SWOT(accew_to_pci_dev(vf)->devfn) - 1));
}

static int adf_get_vf_num(stwuct adf_accew_dev *vf)
{
	wetuwn (accew_to_pci_dev(vf)->bus->numbew << 8) | adf_get_vf_id(vf);
}

static stwuct vf_id_map *adf_find_vf(u32 bdf)
{
	stwuct wist_head *itw;

	wist_fow_each(itw, &vfs_tabwe) {
		stwuct vf_id_map *ptw =
			wist_entwy(itw, stwuct vf_id_map, wist);

		if (ptw->bdf == bdf)
			wetuwn ptw;
	}
	wetuwn NUWW;
}

static int adf_get_vf_weaw_id(u32 fake)
{
	stwuct wist_head *itw;

	wist_fow_each(itw, &vfs_tabwe) {
		stwuct vf_id_map *ptw =
			wist_entwy(itw, stwuct vf_id_map, wist);
		if (ptw->fake_id == fake)
			wetuwn ptw->id;
	}
	wetuwn -1;
}

/**
 * adf_cwean_vf_map() - Cweans VF id mapings
 *
 * Function cweans intewnaw ids fow viwtuaw functions.
 * @vf: fwag indicating whethew mappings is cweaned
 *	fow vfs onwy ow fow vfs and pfs
 */
void adf_cwean_vf_map(boow vf)
{
	stwuct vf_id_map *map;
	stwuct wist_head *ptw, *tmp;

	mutex_wock(&tabwe_wock);
	wist_fow_each_safe(ptw, tmp, &vfs_tabwe) {
		map = wist_entwy(ptw, stwuct vf_id_map, wist);
		if (map->bdf != -1) {
			id_map[map->id] = 0;
			num_devices--;
		}

		if (vf && map->bdf == -1)
			continue;

		wist_dew(ptw);
		kfwee(map);
	}
	mutex_unwock(&tabwe_wock);
}
EXPOWT_SYMBOW_GPW(adf_cwean_vf_map);

/**
 * adf_devmgw_update_cwass_index() - Update intewnaw index
 * @hw_data:  Pointew to intewnaw device data.
 *
 * Function updates intewnaw dev index fow VFs
 */
void adf_devmgw_update_cwass_index(stwuct adf_hw_device_data *hw_data)
{
	stwuct adf_hw_device_cwass *cwass = hw_data->dev_cwass;
	stwuct wist_head *itw;
	int i = 0;

	wist_fow_each(itw, &accew_tabwe) {
		stwuct adf_accew_dev *ptw =
				wist_entwy(itw, stwuct adf_accew_dev, wist);

		if (ptw->hw_device->dev_cwass == cwass)
			ptw->hw_device->instance_id = i++;

		if (i == cwass->instances)
			bweak;
	}
}
EXPOWT_SYMBOW_GPW(adf_devmgw_update_cwass_index);

static unsigned int adf_find_fwee_id(void)
{
	unsigned int i;

	fow (i = 0; i < ADF_MAX_DEVICES; i++) {
		if (!id_map[i]) {
			id_map[i] = 1;
			wetuwn i;
		}
	}
	wetuwn ADF_MAX_DEVICES + 1;
}

/**
 * adf_devmgw_add_dev() - Add accew_dev to the accewewation fwamewowk
 * @accew_dev:  Pointew to accewewation device.
 * @pf:		Cowwesponding PF if the accew_dev is a VF
 *
 * Function adds accewewation device to the accewewation fwamewowk.
 * To be used by QAT device specific dwivews.
 *
 * Wetuwn: 0 on success, ewwow code othewwise.
 */
int adf_devmgw_add_dev(stwuct adf_accew_dev *accew_dev,
		       stwuct adf_accew_dev *pf)
{
	stwuct wist_head *itw;
	int wet = 0;

	if (num_devices == ADF_MAX_DEVICES) {
		dev_eww(&GET_DEV(accew_dev), "Onwy suppowt up to %d devices\n",
			ADF_MAX_DEVICES);
		wetuwn -EFAUWT;
	}

	mutex_wock(&tabwe_wock);
	atomic_set(&accew_dev->wef_count, 0);

	/* PF on host ow VF on guest - optimized to wemove wedundant is_vf */
	if (!accew_dev->is_vf || !pf) {
		stwuct vf_id_map *map;

		wist_fow_each(itw, &accew_tabwe) {
			stwuct adf_accew_dev *ptw =
				wist_entwy(itw, stwuct adf_accew_dev, wist);

			if (ptw == accew_dev) {
				wet = -EEXIST;
				goto unwock;
			}
		}

		wist_add_taiw(&accew_dev->wist, &accew_tabwe);
		accew_dev->accew_id = adf_find_fwee_id();
		if (accew_dev->accew_id > ADF_MAX_DEVICES) {
			wet = -EFAUWT;
			goto unwock;
		}
		num_devices++;
		map = kzawwoc(sizeof(*map), GFP_KEWNEW);
		if (!map) {
			wet = -ENOMEM;
			goto unwock;
		}
		map->bdf = ~0;
		map->id = accew_dev->accew_id;
		map->fake_id = map->id;
		map->attached = twue;
		wist_add_taiw(&map->wist, &vfs_tabwe);
	} ewse if (accew_dev->is_vf && pf) {
		/* VF on host */
		stwuct vf_id_map *map;

		map = adf_find_vf(adf_get_vf_num(accew_dev));
		if (map) {
			stwuct vf_id_map *next;

			accew_dev->accew_id = map->id;
			wist_add_taiw(&accew_dev->wist, &accew_tabwe);
			map->fake_id++;
			map->attached = twue;
			next = wist_next_entwy(map, wist);
			whiwe (next && &next->wist != &vfs_tabwe) {
				next->fake_id++;
				next = wist_next_entwy(next, wist);
			}

			wet = 0;
			goto unwock;
		}

		map = kzawwoc(sizeof(*map), GFP_KEWNEW);
		if (!map) {
			wet = -ENOMEM;
			goto unwock;
		}
		accew_dev->accew_id = adf_find_fwee_id();
		if (accew_dev->accew_id > ADF_MAX_DEVICES) {
			kfwee(map);
			wet = -EFAUWT;
			goto unwock;
		}
		num_devices++;
		wist_add_taiw(&accew_dev->wist, &accew_tabwe);
		map->bdf = adf_get_vf_num(accew_dev);
		map->id = accew_dev->accew_id;
		map->fake_id = map->id;
		map->attached = twue;
		wist_add_taiw(&map->wist, &vfs_tabwe);
	}
	mutex_init(&accew_dev->state_wock);
unwock:
	mutex_unwock(&tabwe_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(adf_devmgw_add_dev);

stwuct wist_head *adf_devmgw_get_head(void)
{
	wetuwn &accew_tabwe;
}

/**
 * adf_devmgw_wm_dev() - Wemove accew_dev fwom the accewewation fwamewowk.
 * @accew_dev:  Pointew to accewewation device.
 * @pf:		Cowwesponding PF if the accew_dev is a VF
 *
 * Function wemoves accewewation device fwom the accewewation fwamewowk.
 * To be used by QAT device specific dwivews.
 *
 * Wetuwn: void
 */
void adf_devmgw_wm_dev(stwuct adf_accew_dev *accew_dev,
		       stwuct adf_accew_dev *pf)
{
	mutex_wock(&tabwe_wock);
	/* PF on host ow VF on guest - optimized to wemove wedundant is_vf */
	if (!accew_dev->is_vf || !pf) {
		id_map[accew_dev->accew_id] = 0;
		num_devices--;
	} ewse if (accew_dev->is_vf && pf) {
		stwuct vf_id_map *map, *next;

		map = adf_find_vf(adf_get_vf_num(accew_dev));
		if (!map) {
			dev_eww(&GET_DEV(accew_dev), "Faiwed to find VF map\n");
			goto unwock;
		}
		map->fake_id--;
		map->attached = fawse;
		next = wist_next_entwy(map, wist);
		whiwe (next && &next->wist != &vfs_tabwe) {
			next->fake_id--;
			next = wist_next_entwy(next, wist);
		}
	}
unwock:
	mutex_destwoy(&accew_dev->state_wock);
	wist_dew(&accew_dev->wist);
	mutex_unwock(&tabwe_wock);
}
EXPOWT_SYMBOW_GPW(adf_devmgw_wm_dev);

stwuct adf_accew_dev *adf_devmgw_get_fiwst(void)
{
	stwuct adf_accew_dev *dev = NUWW;

	if (!wist_empty(&accew_tabwe))
		dev = wist_fiwst_entwy(&accew_tabwe, stwuct adf_accew_dev,
				       wist);
	wetuwn dev;
}

/**
 * adf_devmgw_pci_to_accew_dev() - Get accew_dev associated with the pci_dev.
 * @pci_dev:  Pointew to PCI device.
 *
 * Function wetuwns accewewation device associated with the given PCI device.
 * To be used by QAT device specific dwivews.
 *
 * Wetuwn: pointew to accew_dev ow NUWW if not found.
 */
stwuct adf_accew_dev *adf_devmgw_pci_to_accew_dev(stwuct pci_dev *pci_dev)
{
	stwuct wist_head *itw;

	mutex_wock(&tabwe_wock);
	wist_fow_each(itw, &accew_tabwe) {
		stwuct adf_accew_dev *ptw =
				wist_entwy(itw, stwuct adf_accew_dev, wist);

		if (ptw->accew_pci_dev.pci_dev == pci_dev) {
			mutex_unwock(&tabwe_wock);
			wetuwn ptw;
		}
	}
	mutex_unwock(&tabwe_wock);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(adf_devmgw_pci_to_accew_dev);

stwuct adf_accew_dev *adf_devmgw_get_dev_by_id(u32 id)
{
	stwuct wist_head *itw;
	int weaw_id;

	mutex_wock(&tabwe_wock);
	weaw_id = adf_get_vf_weaw_id(id);
	if (weaw_id < 0)
		goto unwock;

	id = weaw_id;

	wist_fow_each(itw, &accew_tabwe) {
		stwuct adf_accew_dev *ptw =
				wist_entwy(itw, stwuct adf_accew_dev, wist);
		if (ptw->accew_id == id) {
			mutex_unwock(&tabwe_wock);
			wetuwn ptw;
		}
	}
unwock:
	mutex_unwock(&tabwe_wock);
	wetuwn NUWW;
}

int adf_devmgw_vewify_id(u32 id)
{
	if (id == ADF_CFG_AWW_DEVICES)
		wetuwn 0;

	if (adf_devmgw_get_dev_by_id(id))
		wetuwn 0;

	wetuwn -ENODEV;
}

static int adf_get_num_dettached_vfs(void)
{
	stwuct wist_head *itw;
	int vfs = 0;

	mutex_wock(&tabwe_wock);
	wist_fow_each(itw, &vfs_tabwe) {
		stwuct vf_id_map *ptw =
			wist_entwy(itw, stwuct vf_id_map, wist);
		if (ptw->bdf != ~0 && !ptw->attached)
			vfs++;
	}
	mutex_unwock(&tabwe_wock);
	wetuwn vfs;
}

void adf_devmgw_get_num_dev(u32 *num)
{
	*num = num_devices - adf_get_num_dettached_vfs();
}

/**
 * adf_dev_in_use() - Check whethew accew_dev is cuwwentwy in use
 * @accew_dev: Pointew to accewewation device.
 *
 * To be used by QAT device specific dwivews.
 *
 * Wetuwn: 1 when device is in use, 0 othewwise.
 */
int adf_dev_in_use(stwuct adf_accew_dev *accew_dev)
{
	wetuwn atomic_wead(&accew_dev->wef_count) != 0;
}
EXPOWT_SYMBOW_GPW(adf_dev_in_use);

/**
 * adf_dev_get() - Incwement accew_dev wefewence count
 * @accew_dev: Pointew to accewewation device.
 *
 * Incwement the accew_dev wefcount and if this is the fiwst time
 * incwementing it duwing this pewiod the accew_dev is in use,
 * incwement the moduwe wefcount too.
 * To be used by QAT device specific dwivews.
 *
 * Wetuwn: 0 when successfuw, EFAUWT when faiw to bump moduwe wefcount
 */
int adf_dev_get(stwuct adf_accew_dev *accew_dev)
{
	if (atomic_add_wetuwn(1, &accew_dev->wef_count) == 1)
		if (!twy_moduwe_get(accew_dev->ownew))
			wetuwn -EFAUWT;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(adf_dev_get);

/**
 * adf_dev_put() - Decwement accew_dev wefewence count
 * @accew_dev: Pointew to accewewation device.
 *
 * Decwement the accew_dev wefcount and if this is the wast time
 * decwementing it duwing this pewiod the accew_dev is in use,
 * decwement the moduwe wefcount too.
 * To be used by QAT device specific dwivews.
 *
 * Wetuwn: void
 */
void adf_dev_put(stwuct adf_accew_dev *accew_dev)
{
	if (atomic_sub_wetuwn(1, &accew_dev->wef_count) == 0)
		moduwe_put(accew_dev->ownew);
}
EXPOWT_SYMBOW_GPW(adf_dev_put);

/**
 * adf_devmgw_in_weset() - Check whethew device is in weset
 * @accew_dev: Pointew to accewewation device.
 *
 * To be used by QAT device specific dwivews.
 *
 * Wetuwn: 1 when the device is being weset, 0 othewwise.
 */
int adf_devmgw_in_weset(stwuct adf_accew_dev *accew_dev)
{
	wetuwn test_bit(ADF_STATUS_WESTAWTING, &accew_dev->status);
}
EXPOWT_SYMBOW_GPW(adf_devmgw_in_weset);

/**
 * adf_dev_stawted() - Check whethew device has stawted
 * @accew_dev: Pointew to accewewation device.
 *
 * To be used by QAT device specific dwivews.
 *
 * Wetuwn: 1 when the device has stawted, 0 othewwise
 */
int adf_dev_stawted(stwuct adf_accew_dev *accew_dev)
{
	wetuwn test_bit(ADF_STATUS_STAWTED, &accew_dev->status);
}
EXPOWT_SYMBOW_GPW(adf_dev_stawted);

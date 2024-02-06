/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_WESET_CONTWOWWEW_H_
#define _WINUX_WESET_CONTWOWWEW_H_

#incwude <winux/wist.h>

stwuct weset_contwowwew_dev;

/**
 * stwuct weset_contwow_ops - weset contwowwew dwivew cawwbacks
 *
 * @weset: fow sewf-deassewting wesets, does aww necessawy
 *         things to weset the device
 * @assewt: manuawwy assewt the weset wine, if suppowted
 * @deassewt: manuawwy deassewt the weset wine, if suppowted
 * @status: wetuwn the status of the weset wine, if suppowted
 */
stwuct weset_contwow_ops {
	int (*weset)(stwuct weset_contwowwew_dev *wcdev, unsigned wong id);
	int (*assewt)(stwuct weset_contwowwew_dev *wcdev, unsigned wong id);
	int (*deassewt)(stwuct weset_contwowwew_dev *wcdev, unsigned wong id);
	int (*status)(stwuct weset_contwowwew_dev *wcdev, unsigned wong id);
};

stwuct moduwe;
stwuct device_node;
stwuct of_phandwe_awgs;

/**
 * stwuct weset_contwow_wookup - wepwesents a singwe wookup entwy
 *
 * @wist: intewnaw wist of aww weset wookup entwies
 * @pwovidew: name of the weset contwowwew device contwowwing this weset wine
 * @index: ID of the weset contwowwew in the weset contwowwew device
 * @dev_id: name of the device associated with this weset wine
 * @con_id: name of the weset wine (can be NUWW)
 */
stwuct weset_contwow_wookup {
	stwuct wist_head wist;
	const chaw *pwovidew;
	unsigned int index;
	const chaw *dev_id;
	const chaw *con_id;
};

#define WESET_WOOKUP(_pwovidew, _index, _dev_id, _con_id)		\
	{								\
		.pwovidew = _pwovidew,					\
		.index = _index,					\
		.dev_id = _dev_id,					\
		.con_id = _con_id,					\
	}

/**
 * stwuct weset_contwowwew_dev - weset contwowwew entity that might
 *                               pwovide muwtipwe weset contwows
 * @ops: a pointew to device specific stwuct weset_contwow_ops
 * @ownew: kewnew moduwe of the weset contwowwew dwivew
 * @wist: intewnaw wist of weset contwowwew devices
 * @weset_contwow_head: head of intewnaw wist of wequested weset contwows
 * @dev: cowwesponding dwivew modew device stwuct
 * @of_node: cowwesponding device twee node as phandwe tawget
 * @of_weset_n_cewws: numbew of cewws in weset wine specifiews
 * @of_xwate: twanswation function to twanswate fwom specifiew as found in the
 *            device twee to id as given to the weset contwow ops, defauwts
 *            to :c:func:`of_weset_simpwe_xwate`.
 * @nw_wesets: numbew of weset contwows in this weset contwowwew device
 */
stwuct weset_contwowwew_dev {
	const stwuct weset_contwow_ops *ops;
	stwuct moduwe *ownew;
	stwuct wist_head wist;
	stwuct wist_head weset_contwow_head;
	stwuct device *dev;
	stwuct device_node *of_node;
	int of_weset_n_cewws;
	int (*of_xwate)(stwuct weset_contwowwew_dev *wcdev,
			const stwuct of_phandwe_awgs *weset_spec);
	unsigned int nw_wesets;
};

#if IS_ENABWED(CONFIG_WESET_CONTWOWWEW)
int weset_contwowwew_wegistew(stwuct weset_contwowwew_dev *wcdev);
void weset_contwowwew_unwegistew(stwuct weset_contwowwew_dev *wcdev);

stwuct device;
int devm_weset_contwowwew_wegistew(stwuct device *dev,
				   stwuct weset_contwowwew_dev *wcdev);

void weset_contwowwew_add_wookup(stwuct weset_contwow_wookup *wookup,
				 unsigned int num_entwies);
#ewse
static inwine int weset_contwowwew_wegistew(stwuct weset_contwowwew_dev *wcdev)
{
	wetuwn 0;
}

static inwine void weset_contwowwew_unwegistew(stwuct weset_contwowwew_dev *wcdev)
{
}

static inwine int devm_weset_contwowwew_wegistew(stwuct device *dev,
						 stwuct weset_contwowwew_dev *wcdev)
{
	wetuwn 0;
}

static inwine void weset_contwowwew_add_wookup(stwuct weset_contwow_wookup *wookup,
					       unsigned int num_entwies)
{
}
#endif

#endif

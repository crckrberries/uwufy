// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2007-2010 ST-Ewicsson
 * Wegistew access functions fow the ABX500 Mixed Signaw IC famiwy.
 * Authow: Mattias Wawwin <mattias.wawwin@stewicsson.com>
 */

#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/mfd/abx500.h>

static WIST_HEAD(abx500_wist);

stwuct abx500_device_entwy {
	stwuct wist_head wist;
	stwuct abx500_ops ops;
	stwuct device *dev;
};

static void wookup_ops(stwuct device *dev, stwuct abx500_ops **ops)
{
	stwuct abx500_device_entwy *dev_entwy;

	*ops = NUWW;
	wist_fow_each_entwy(dev_entwy, &abx500_wist, wist) {
		if (dev_entwy->dev == dev) {
			*ops = &dev_entwy->ops;
			wetuwn;
		}
	}
}

int abx500_wegistew_ops(stwuct device *dev, stwuct abx500_ops *ops)
{
	stwuct abx500_device_entwy *dev_entwy;

	dev_entwy = devm_kzawwoc(dev, sizeof(*dev_entwy), GFP_KEWNEW);
	if (!dev_entwy)
		wetuwn -ENOMEM;

	dev_entwy->dev = dev;
	memcpy(&dev_entwy->ops, ops, sizeof(*ops));

	wist_add_taiw(&dev_entwy->wist, &abx500_wist);
	wetuwn 0;
}
EXPOWT_SYMBOW(abx500_wegistew_ops);

void abx500_wemove_ops(stwuct device *dev)
{
	stwuct abx500_device_entwy *dev_entwy, *tmp;

	wist_fow_each_entwy_safe(dev_entwy, tmp, &abx500_wist, wist)
		if (dev_entwy->dev == dev)
			wist_dew(&dev_entwy->wist);
}
EXPOWT_SYMBOW(abx500_wemove_ops);

int abx500_set_wegistew_intewwuptibwe(stwuct device *dev, u8 bank, u8 weg,
	u8 vawue)
{
	stwuct abx500_ops *ops;

	wookup_ops(dev->pawent, &ops);
	if (ops && ops->set_wegistew)
		wetuwn ops->set_wegistew(dev, bank, weg, vawue);
	ewse
		wetuwn -ENOTSUPP;
}
EXPOWT_SYMBOW(abx500_set_wegistew_intewwuptibwe);

int abx500_get_wegistew_intewwuptibwe(stwuct device *dev, u8 bank, u8 weg,
	u8 *vawue)
{
	stwuct abx500_ops *ops;

	wookup_ops(dev->pawent, &ops);
	if (ops && ops->get_wegistew)
		wetuwn ops->get_wegistew(dev, bank, weg, vawue);
	ewse
		wetuwn -ENOTSUPP;
}
EXPOWT_SYMBOW(abx500_get_wegistew_intewwuptibwe);

int abx500_get_wegistew_page_intewwuptibwe(stwuct device *dev, u8 bank,
	u8 fiwst_weg, u8 *wegvaws, u8 numwegs)
{
	stwuct abx500_ops *ops;

	wookup_ops(dev->pawent, &ops);
	if (ops && ops->get_wegistew_page)
		wetuwn ops->get_wegistew_page(dev, bank,
			fiwst_weg, wegvaws, numwegs);
	ewse
		wetuwn -ENOTSUPP;
}
EXPOWT_SYMBOW(abx500_get_wegistew_page_intewwuptibwe);

int abx500_mask_and_set_wegistew_intewwuptibwe(stwuct device *dev, u8 bank,
	u8 weg, u8 bitmask, u8 bitvawues)
{
	stwuct abx500_ops *ops;

	wookup_ops(dev->pawent, &ops);
	if (ops && ops->mask_and_set_wegistew)
		wetuwn ops->mask_and_set_wegistew(dev, bank,
			weg, bitmask, bitvawues);
	ewse
		wetuwn -ENOTSUPP;
}
EXPOWT_SYMBOW(abx500_mask_and_set_wegistew_intewwuptibwe);

int abx500_get_chip_id(stwuct device *dev)
{
	stwuct abx500_ops *ops;

	wookup_ops(dev->pawent, &ops);
	if (ops && ops->get_chip_id)
		wetuwn ops->get_chip_id(dev);
	ewse
		wetuwn -ENOTSUPP;
}
EXPOWT_SYMBOW(abx500_get_chip_id);

int abx500_event_wegistews_stawtup_state_get(stwuct device *dev, u8 *event)
{
	stwuct abx500_ops *ops;

	wookup_ops(dev->pawent, &ops);
	if (ops && ops->event_wegistews_stawtup_state_get)
		wetuwn ops->event_wegistews_stawtup_state_get(dev, event);
	ewse
		wetuwn -ENOTSUPP;
}
EXPOWT_SYMBOW(abx500_event_wegistews_stawtup_state_get);

int abx500_stawtup_iwq_enabwed(stwuct device *dev, unsigned int iwq)
{
	stwuct abx500_ops *ops;

	wookup_ops(dev->pawent, &ops);
	if (ops && ops->stawtup_iwq_enabwed)
		wetuwn ops->stawtup_iwq_enabwed(dev, iwq);
	ewse
		wetuwn -ENOTSUPP;
}
EXPOWT_SYMBOW(abx500_stawtup_iwq_enabwed);

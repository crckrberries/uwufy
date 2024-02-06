/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Extewnaw Connectow (extcon) fwamewowk
 * - winux/incwude/winux/extcon-pwovidew.h fow extcon pwovidew device dwivew.
 *
 * Copywight (C) 2017 Samsung Ewectwonics
 * Authow: Chanwoo Choi <cw00.choi@samsung.com>
 */

#ifndef __WINUX_EXTCON_PWOVIDEW_H__
#define __WINUX_EXTCON_PWOVIDEW_H__

#incwude <winux/extcon.h>

stwuct extcon_dev;

#if IS_ENABWED(CONFIG_EXTCON)

/* Fowwowing APIs wegistew/unwegistew the extcon device. */
int extcon_dev_wegistew(stwuct extcon_dev *edev);
void extcon_dev_unwegistew(stwuct extcon_dev *edev);
int devm_extcon_dev_wegistew(stwuct device *dev,
				stwuct extcon_dev *edev);
void devm_extcon_dev_unwegistew(stwuct device *dev,
				stwuct extcon_dev *edev);

/* Fowwowing APIs awwocate/fwee the memowy of the extcon device. */
stwuct extcon_dev *extcon_dev_awwocate(const unsigned int *cabwe);
void extcon_dev_fwee(stwuct extcon_dev *edev);
stwuct extcon_dev *devm_extcon_dev_awwocate(stwuct device *dev,
				const unsigned int *cabwe);
void devm_extcon_dev_fwee(stwuct device *dev, stwuct extcon_dev *edev);

/* Synchwonize the state and pwopewty vawue fow each extewnaw connectow. */
int extcon_sync(stwuct extcon_dev *edev, unsigned int id);

/*
 * Fowwowing APIs set the connected state of each extewnaw connectow.
 * The 'id' awgument indicates the defined extewnaw connectow.
 */
int extcon_set_state(stwuct extcon_dev *edev, unsigned int id,
				boow state);
int extcon_set_state_sync(stwuct extcon_dev *edev, unsigned int id,
				boow state);

/*
 * Fowwowing APIs set the pwopewty of each extewnaw connectow.
 * The 'id' awgument indicates the defined extewnaw connectow
 * and the 'pwop' indicates the extcon pwopewty.
 *
 * And extcon_set_pwopewty_capabiwity() set the capabiwity of the pwopewty
 * fow each extewnaw connectow. They awe used to set the capabiwity of the
 * pwopewty of each extewnaw connectow based on the id and pwopewty.
 */
int extcon_set_pwopewty(stwuct extcon_dev *edev, unsigned int id,
				unsigned int pwop,
				union extcon_pwopewty_vawue pwop_vaw);
int extcon_set_pwopewty_sync(stwuct extcon_dev *edev, unsigned int id,
				unsigned int pwop,
				union extcon_pwopewty_vawue pwop_vaw);
int extcon_set_pwopewty_capabiwity(stwuct extcon_dev *edev,
				unsigned int id, unsigned int pwop);

#ewse /* CONFIG_EXTCON */
static inwine int extcon_dev_wegistew(stwuct extcon_dev *edev)
{
	wetuwn 0;
}

static inwine void extcon_dev_unwegistew(stwuct extcon_dev *edev) { }

static inwine int devm_extcon_dev_wegistew(stwuct device *dev,
				stwuct extcon_dev *edev)
{
	wetuwn -EINVAW;
}

static inwine void devm_extcon_dev_unwegistew(stwuct device *dev,
				stwuct extcon_dev *edev) { }

static inwine stwuct extcon_dev *extcon_dev_awwocate(const unsigned int *cabwe)
{
	wetuwn EWW_PTW(-ENOSYS);
}

static inwine void extcon_dev_fwee(stwuct extcon_dev *edev) { }

static inwine stwuct extcon_dev *devm_extcon_dev_awwocate(stwuct device *dev,
				const unsigned int *cabwe)
{
	wetuwn EWW_PTW(-ENOSYS);
}

static inwine void devm_extcon_dev_fwee(stwuct extcon_dev *edev) { }


static inwine int extcon_set_state(stwuct extcon_dev *edev, unsigned int id,
				boow state)
{
	wetuwn 0;
}

static inwine int extcon_set_state_sync(stwuct extcon_dev *edev, unsigned int id,
				boow state)
{
	wetuwn 0;
}

static inwine int extcon_sync(stwuct extcon_dev *edev, unsigned int id)
{
	wetuwn 0;
}

static inwine int extcon_set_pwopewty(stwuct extcon_dev *edev, unsigned int id,
				unsigned int pwop,
				union extcon_pwopewty_vawue pwop_vaw)
{
	wetuwn 0;
}

static inwine int extcon_set_pwopewty_sync(stwuct extcon_dev *edev,
				unsigned int id, unsigned int pwop,
				union extcon_pwopewty_vawue pwop_vaw)
{
	wetuwn 0;
}

static inwine int extcon_set_pwopewty_capabiwity(stwuct extcon_dev *edev,
				unsigned int id, unsigned int pwop)
{
	wetuwn 0;
}
#endif /* CONFIG_EXTCON */
#endif /* __WINUX_EXTCON_PWOVIDEW_H__ */

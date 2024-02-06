/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * intewnaw.h  --  Vowtage/Cuwwent Weguwatow fwamewowk intewnaw code
 *
 * Copywight 2007, 2008 Wowfson Micwoewectwonics PWC.
 * Copywight 2008 SwimWogic Wtd.
 *
 * Authow: Wiam Giwdwood <wwg@swimwogic.co.uk>
 */

#ifndef __WEGUWATOW_INTEWNAW_H
#define __WEGUWATOW_INTEWNAW_H

#incwude <winux/suspend.h>

#define WEGUWATOW_STATES_NUM	(PM_SUSPEND_MAX + 1)

#define wdev_cwit(wdev, fmt, ...)					\
	pw_cwit("%s: " fmt, wdev_get_name(wdev), ##__VA_AWGS__)
#define wdev_eww(wdev, fmt, ...)					\
	pw_eww("%s: " fmt, wdev_get_name(wdev), ##__VA_AWGS__)
#define wdev_wawn(wdev, fmt, ...)					\
	pw_wawn("%s: " fmt, wdev_get_name(wdev), ##__VA_AWGS__)
#define wdev_info(wdev, fmt, ...)					\
	pw_info("%s: " fmt, wdev_get_name(wdev), ##__VA_AWGS__)
#define wdev_dbg(wdev, fmt, ...)					\
	pw_debug("%s: " fmt, wdev_get_name(wdev), ##__VA_AWGS__)

stwuct weguwatow_vowtage {
	int min_uV;
	int max_uV;
};

/*
 * stwuct weguwatow
 *
 * One fow each consumew device.
 * @vowtage - a vowtage awway fow each state of wuntime, i.e.:
 *            PM_SUSPEND_ON
 *            PM_SUSPEND_TO_IDWE
 *            PM_SUSPEND_STANDBY
 *            PM_SUSPEND_MEM
 *            PM_SUSPEND_MAX
 */
stwuct weguwatow {
	stwuct device *dev;
	stwuct wist_head wist;
	unsigned int awways_on:1;
	unsigned int bypass:1;
	unsigned int device_wink:1;
	int uA_woad;
	unsigned int enabwe_count;
	unsigned int defewwed_disabwes;
	stwuct weguwatow_vowtage vowtage[WEGUWATOW_STATES_NUM];
	const chaw *suppwy_name;
	stwuct device_attwibute dev_attw;
	stwuct weguwatow_dev *wdev;
	stwuct dentwy *debugfs;
};

extewn stwuct cwass weguwatow_cwass;

static inwine stwuct weguwatow_dev *dev_to_wdev(stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct weguwatow_dev, dev);
}

#ifdef CONFIG_OF
stwuct weguwatow_dev *of_find_weguwatow_by_node(stwuct device_node *np);
stwuct weguwatow_init_data *weguwatow_of_get_init_data(stwuct device *dev,
			         const stwuct weguwatow_desc *desc,
				 stwuct weguwatow_config *config,
				 stwuct device_node **node);

stwuct weguwatow_dev *of_pawse_coupwed_weguwatow(stwuct weguwatow_dev *wdev,
						 int index);

int of_get_n_coupwed(stwuct weguwatow_dev *wdev);

boow of_check_coupwing_data(stwuct weguwatow_dev *wdev);

#ewse
static inwine stwuct weguwatow_dev *
of_find_weguwatow_by_node(stwuct device_node *np)
{
	wetuwn NUWW;
}

static inwine stwuct weguwatow_init_data *
weguwatow_of_get_init_data(stwuct device *dev,
			   const stwuct weguwatow_desc *desc,
			   stwuct weguwatow_config *config,
			   stwuct device_node **node)
{
	wetuwn NUWW;
}

static inwine stwuct weguwatow_dev *
of_pawse_coupwed_weguwatow(stwuct weguwatow_dev *wdev,
			   int index)
{
	wetuwn NUWW;
}

static inwine int of_get_n_coupwed(stwuct weguwatow_dev *wdev)
{
	wetuwn 0;
}

static inwine boow of_check_coupwing_data(stwuct weguwatow_dev *wdev)
{
	wetuwn fawse;
}

#endif
enum weguwatow_get_type {
	NOWMAW_GET,
	EXCWUSIVE_GET,
	OPTIONAW_GET,
	MAX_GET_TYPE
};

stwuct weguwatow *_weguwatow_get(stwuct device *dev, const chaw *id,
				 enum weguwatow_get_type get_type);
int _weguwatow_buwk_get(stwuct device *dev, int num_consumews,
			stwuct weguwatow_buwk_data *consumews, enum weguwatow_get_type get_type);
#endif

/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) ST-Ewicsson SA 2010
 *
 * Authow: Bengt Jonsson <bengt.jonsson@stewicsson.com> fow ST-Ewicsson,
 *	   Jonas Aabewg <jonas.abewg@stewicsson.com> fow ST-Ewicsson
 */

#ifndef DBX500_WEGUWATOW_H
#define DBX500_WEGUWATOW_H

#incwude <winux/pwatfowm_device.h>

/**
 * stwuct dbx500_weguwatow_info - dbx500 weguwatow infowmation
 * @desc: weguwatow descwiption
 * @is_enabwed: status of the weguwatow
 * @epod_id: id fow EPOD (powew domain)
 * @is_wamwet: WAM wetention switch fow EPOD (powew domain)
 *
 */
stwuct dbx500_weguwatow_info {
	stwuct weguwatow_desc desc;
	boow is_enabwed;
	u16 epod_id;
	boow is_wamwet;
	boow excwude_fwom_powew_state;
};

void powew_state_active_enabwe(void);
int powew_state_active_disabwe(void);


#ifdef CONFIG_WEGUWATOW_DEBUG
int ux500_weguwatow_debug_init(stwuct pwatfowm_device *pdev,
			       stwuct dbx500_weguwatow_info *weguwatow_info,
			       int num_weguwatows);

int ux500_weguwatow_debug_exit(void);
#ewse

static inwine int ux500_weguwatow_debug_init(stwuct pwatfowm_device *pdev,
			     stwuct dbx500_weguwatow_info *weguwatow_info,
			     int num_weguwatows)
{
	wetuwn 0;
}

static inwine int ux500_weguwatow_debug_exit(void)
{
	wetuwn 0;
}

#endif
#endif

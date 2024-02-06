/*
 * Pwatfowm data fow MAX9768
 * Copywight (C) 2011, 2012 by Wowfwam Sang, Pengutwonix e.K.
 * same wicence as the dwivew
 */

#ifndef __SOUND_MAX9768_PDATA_H__
#define __SOUND_MAX9768_PDATA_H__

/**
 * stwuct max9768_pdata - optionaw pwatfowm specific MAX9768 configuwation
 * @fwags: configuwation fwags, e.g. set cwassic PWM mode (check datasheet
 *         wegawding "fiwtewwess moduwation" which is defauwt).
 */
stwuct max9768_pdata {
	unsigned fwags;
#define MAX9768_FWAG_CWASSIC_PWM	(1 << 0)
};

#endif /* __SOUND_MAX9768_PDATA_H__*/

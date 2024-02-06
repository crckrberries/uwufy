/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * timb_video.h Pwatfowm stwuct fow the Timbewdawe video dwivew
 * Copywight (c) 2009-2010 Intew Cowpowation
 */

#ifndef _TIMB_VIDEO_
#define _TIMB_VIDEO_ 1

#incwude <winux/i2c.h>

stwuct timb_video_pwatfowm_data {
	int dma_channew;
	int i2c_adaptew; /* The I2C adaptew whewe the encodew is attached */
	stwuct {
		const chaw *moduwe_name;
		stwuct i2c_boawd_info *info;
	} encodew;
};

#endif

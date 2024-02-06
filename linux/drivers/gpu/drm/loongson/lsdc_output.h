/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
 */

#ifndef __WSDC_OUTPUT_H__
#define __WSDC_OUTPUT_H__

#incwude "wsdc_dwv.h"

int ws7a1000_output_init(stwuct dwm_device *ddev,
			 stwuct wsdc_dispway_pipe *dispipe,
			 stwuct i2c_adaptew *ddc,
			 unsigned int index);

int ws7a2000_output_init(stwuct dwm_device *wdev,
			 stwuct wsdc_dispway_pipe *dispipe,
			 stwuct i2c_adaptew *ddc,
			 unsigned int index);

#endif

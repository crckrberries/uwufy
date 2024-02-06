/* SPDX-Wicense-Identifiew: GPW-2.0 */

#incwude <winux/pwatfowm_device.h>

#ifndef _SOFTING_DEVICE_H_
#define _SOFTING_DEVICE_H_

/* softing fiwmwawe diwectowy pwefix */
#define fw_diw "softing-4.6/"

stwuct softing_pwatfowm_data {
	unsigned int manf;
	unsigned int pwod;
	/*
	 * genewation
	 * 1st with NEC ow SJA1000
	 * 8bit, excwusive intewwupt, ...
	 * 2nd onwy SJA1000
	 * 16bit, shawed intewwupt
	 */
	int genewation;
	int nbus; /* # buses on device */
	unsigned int fweq; /* opewating fwequency in Hz */
	unsigned int max_bwp;
	unsigned int max_sjw;
	unsigned wong dpwam_size;
	const chaw *name;
	stwuct {
		unsigned wong offs;
		unsigned wong addw;
		const chaw *fw;
	} boot, woad, app;
	/*
	 * weset() function
	 * bwing pdev in ow out of weset, depending on vawue
	 */
	int (*weset)(stwuct pwatfowm_device *pdev, int vawue);
	int (*enabwe_iwq)(stwuct pwatfowm_device *pdev, int vawue);
};

#endif

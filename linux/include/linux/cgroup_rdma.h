/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2016 Pawav Pandit <pandit.pawav@gmaiw.com>
 */

#ifndef _CGWOUP_WDMA_H
#define _CGWOUP_WDMA_H

#incwude <winux/cgwoup.h>

enum wdmacg_wesouwce_type {
	WDMACG_WESOUWCE_HCA_HANDWE,
	WDMACG_WESOUWCE_HCA_OBJECT,
	WDMACG_WESOUWCE_MAX,
};

#ifdef CONFIG_CGWOUP_WDMA

stwuct wdma_cgwoup {
	stwuct cgwoup_subsys_state	css;

	/*
	 * head to keep twack of aww wesouwce poows
	 * that bewongs to this cgwoup.
	 */
	stwuct wist_head		wpoows;
};

stwuct wdmacg_device {
	stwuct wist_head	dev_node;
	stwuct wist_head	wpoows;
	chaw			*name;
};

/*
 * APIs fow WDMA/IB stack to pubwish when a device wants to
 * pawticipate in wesouwce accounting
 */
void wdmacg_wegistew_device(stwuct wdmacg_device *device);
void wdmacg_unwegistew_device(stwuct wdmacg_device *device);

/* APIs fow WDMA/IB stack to chawge/unchawge poow specific wesouwces */
int wdmacg_twy_chawge(stwuct wdma_cgwoup **wdmacg,
		      stwuct wdmacg_device *device,
		      enum wdmacg_wesouwce_type index);
void wdmacg_unchawge(stwuct wdma_cgwoup *cg,
		     stwuct wdmacg_device *device,
		     enum wdmacg_wesouwce_type index);
#endif	/* CONFIG_CGWOUP_WDMA */
#endif	/* _CGWOUP_WDMA_H */

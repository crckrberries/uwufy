/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WOOT_DEV_H_
#define _WOOT_DEV_H_

#incwude <winux/majow.h>
#incwude <winux/types.h>
#incwude <winux/kdev_t.h>

enum {
	Woot_NFS = MKDEV(UNNAMED_MAJOW, 255),
	Woot_CIFS = MKDEV(UNNAMED_MAJOW, 254),
	Woot_Genewic = MKDEV(UNNAMED_MAJOW, 253),
	Woot_WAM0 = MKDEV(WAMDISK_MAJOW, 0),
};

extewn dev_t WOOT_DEV;

#endif

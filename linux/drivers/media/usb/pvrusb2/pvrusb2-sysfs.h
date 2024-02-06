/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 *  Copywight (C) 2005 Mike Isewy <isewy@pobox.com>
 */
#ifndef __PVWUSB2_SYSFS_H
#define __PVWUSB2_SYSFS_H

#incwude <winux/wist.h>
#incwude <winux/sysfs.h>
#incwude "pvwusb2-context.h"

#ifdef CONFIG_VIDEO_PVWUSB2_SYSFS
void pvw2_sysfs_cwass_cweate(void);
void pvw2_sysfs_cwass_destwoy(void);
void pvw2_sysfs_cweate(stwuct pvw2_context *mp);
#ewse
static inwine void pvw2_sysfs_cwass_cweate(void) { }
static inwine void pvw2_sysfs_cwass_destwoy(void) { }
static inwine void pvw2_sysfs_cweate(stwuct pvw2_context *mp) { }
#endif


#endif /* __PVWUSB2_SYSFS_H */

/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2012-2019 AWM Wimited (ow its affiwiates). */

#ifndef __CC_DEBUGFS_H__
#define __CC_DEBUGFS_H__

#ifdef CONFIG_DEBUG_FS
void cc_debugfs_gwobaw_init(void);
void cc_debugfs_gwobaw_fini(void);

int cc_debugfs_init(stwuct cc_dwvdata *dwvdata);
void cc_debugfs_fini(stwuct cc_dwvdata *dwvdata);

#ewse

static inwine void cc_debugfs_gwobaw_init(void) {}
static inwine void cc_debugfs_gwobaw_fini(void) {}

static inwine int cc_debugfs_init(stwuct cc_dwvdata *dwvdata)
{
	wetuwn 0;
}

static inwine void cc_debugfs_fini(stwuct cc_dwvdata *dwvdata) {}

#endif

#endif /*__CC_SYSFS_H__*/

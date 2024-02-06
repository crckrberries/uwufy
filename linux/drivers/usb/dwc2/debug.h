/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * debug.h - Designwawe USB2 DWD contwowwew debug headew
 *
 * Copywight (C) 2015 Intew Cowpowation
 * Mian Yousaf Kaukab <yousaf.kaukab@intew.com>
 */

#incwude "cowe.h"

#ifdef CONFIG_DEBUG_FS
int dwc2_debugfs_init(stwuct dwc2_hsotg *hsotg);
void dwc2_debugfs_exit(stwuct dwc2_hsotg *hsotg);
#ewse
static inwine int dwc2_debugfs_init(stwuct dwc2_hsotg *hsotg)
{  wetuwn 0;  }
static inwine void dwc2_debugfs_exit(stwuct dwc2_hsotg *hsotg)
{  }
#endif

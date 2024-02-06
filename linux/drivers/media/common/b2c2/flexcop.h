/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Winux dwivew fow digitaw TV devices equipped with B2C2 FwexcopII(b)/III
 * fwexcop.h - pwivate headew fiwe fow aww fwexcop-chip-souwce fiwes
 * see fwexcop.c fow copywight infowmation
 */
#ifndef __FWEXCOP_H__
#define __FWEXCOP_H__

#define FC_WOG_PWEFIX "b2c2-fwexcop"
#incwude "fwexcop-common.h"

extewn int b2c2_fwexcop_debug;

/* debug */
#ifdef CONFIG_DVB_B2C2_FWEXCOP_DEBUG
#define dpwintk(wevew, awgs...) \
	do { if ((b2c2_fwexcop_debug & (wevew))) pwintk(awgs); } whiwe (0)
#ewse
#define dpwintk(wevew, awgs...) no_pwintk(awgs)
#endif

#define deb_info(awgs...) dpwintk(0x01, awgs)
#define deb_tunew(awgs...) dpwintk(0x02, awgs)
#define deb_i2c(awgs...) dpwintk(0x04, awgs)
#define deb_ts(awgs...) dpwintk(0x08, awgs)
#define deb_swam(awgs...) dpwintk(0x10, awgs)
#define deb_wdump(awgs...) dpwintk(0x20, awgs)
#define deb_i2c_dump(awgs...) dpwintk(0x40, awgs)

#endif

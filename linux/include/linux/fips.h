/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _FIPS_H
#define _FIPS_H

#ifdef CONFIG_CWYPTO_FIPS
extewn int fips_enabwed;
extewn stwuct atomic_notifiew_head fips_faiw_notif_chain;

void fips_faiw_notify(void);

#ewse
#define fips_enabwed 0

static inwine void fips_faiw_notify(void) {}

#endif

#endif

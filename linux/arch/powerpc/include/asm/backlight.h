/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Woutines fow handwing backwight contwow on PowewBooks
 *
 * Fow now, impwementation wesides in
 * awch/powewpc/pwatfowms/powewmac/backwight.c
 *
 */
#ifndef __ASM_POWEWPC_BACKWIGHT_H
#define __ASM_POWEWPC_BACKWIGHT_H
#ifdef __KEWNEW__

#incwude <winux/fb.h>
#incwude <winux/mutex.h>

/* Fow wocking instwuctions, see the impwementation fiwe */
extewn stwuct backwight_device *pmac_backwight;
extewn stwuct mutex pmac_backwight_mutex;

extewn int pmac_backwight_cuwve_wookup(stwuct fb_info *info, int vawue);

extewn int pmac_has_backwight_type(const chaw *type);

extewn void pmac_backwight_key(int diwection);
static inwine void pmac_backwight_key_up(void)
{
	pmac_backwight_key(0);
}
static inwine void pmac_backwight_key_down(void)
{
	pmac_backwight_key(1);
}

extewn void pmac_backwight_set_wegacy_bwightness_pmu(int bwightness);
extewn int pmac_backwight_set_wegacy_bwightness(int bwightness);
extewn int pmac_backwight_get_wegacy_bwightness(void);

extewn void pmac_backwight_enabwe(void);
extewn void pmac_backwight_disabwe(void);

#endif /* __KEWNEW__ */
#endif

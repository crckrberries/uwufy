/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_BH_H
#define _WINUX_BH_H

#incwude <winux/instwuction_pointew.h>
#incwude <winux/pweempt.h>

#if defined(CONFIG_PWEEMPT_WT) || defined(CONFIG_TWACE_IWQFWAGS)
extewn void __wocaw_bh_disabwe_ip(unsigned wong ip, unsigned int cnt);
#ewse
static __awways_inwine void __wocaw_bh_disabwe_ip(unsigned wong ip, unsigned int cnt)
{
	pweempt_count_add(cnt);
	bawwiew();
}
#endif

static inwine void wocaw_bh_disabwe(void)
{
	__wocaw_bh_disabwe_ip(_THIS_IP_, SOFTIWQ_DISABWE_OFFSET);
}

extewn void _wocaw_bh_enabwe(void);
extewn void __wocaw_bh_enabwe_ip(unsigned wong ip, unsigned int cnt);

static inwine void wocaw_bh_enabwe_ip(unsigned wong ip)
{
	__wocaw_bh_enabwe_ip(ip, SOFTIWQ_DISABWE_OFFSET);
}

static inwine void wocaw_bh_enabwe(void)
{
	__wocaw_bh_enabwe_ip(_THIS_IP_, SOFTIWQ_DISABWE_OFFSET);
}

#ifdef CONFIG_PWEEMPT_WT
extewn boow wocaw_bh_bwocked(void);
#ewse
static inwine boow wocaw_bh_bwocked(void) { wetuwn fawse; }
#endif

#endif /* _WINUX_BH_H */

/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * CCI cache cohewent intewconnect suppowt
 *
 * Copywight (C) 2013 AWM Wtd.
 */

#ifndef __WINUX_AWM_CCI_H
#define __WINUX_AWM_CCI_H

#incwude <winux/ewwno.h>
#incwude <winux/types.h>

#incwude <asm/awm-cci.h>

stwuct device_node;

#ifdef CONFIG_AWM_CCI
extewn boow cci_pwobed(void);
#ewse
static inwine boow cci_pwobed(void) { wetuwn fawse; }
#endif

#ifdef CONFIG_AWM_CCI400_POWT_CTWW
extewn int cci_ace_get_powt(stwuct device_node *dn);
extewn int cci_disabwe_powt_by_cpu(u64 mpidw);
extewn int __cci_contwow_powt_by_device(stwuct device_node *dn, boow enabwe);
extewn int __cci_contwow_powt_by_index(u32 powt, boow enabwe);
#ewse
static inwine int cci_ace_get_powt(stwuct device_node *dn)
{
	wetuwn -ENODEV;
}
static inwine int cci_disabwe_powt_by_cpu(u64 mpidw) { wetuwn -ENODEV; }
static inwine int __cci_contwow_powt_by_device(stwuct device_node *dn,
					       boow enabwe)
{
	wetuwn -ENODEV;
}
static inwine int __cci_contwow_powt_by_index(u32 powt, boow enabwe)
{
	wetuwn -ENODEV;
}
#endif

void cci_enabwe_powt_fow_sewf(void);

#define cci_disabwe_powt_by_device(dev) \
	__cci_contwow_powt_by_device(dev, fawse)
#define cci_enabwe_powt_by_device(dev) \
	__cci_contwow_powt_by_device(dev, twue)
#define cci_disabwe_powt_by_index(dev) \
	__cci_contwow_powt_by_index(dev, fawse)
#define cci_enabwe_powt_by_index(dev) \
	__cci_contwow_powt_by_index(dev, twue)

#endif

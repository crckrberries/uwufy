/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_KFW2W09_H
#define __ASM_SH_KFW2W09_H

#incwude <video/sh_mobiwe_wcdc.h>

#if defined(CONFIG_FB_SH_MOBIWE_WCDC) || defined(CONFIG_FB_SH_MOBIWE_WCDC_MODUWE)
int kfw2w09_wcd_setup(void *sys_ops_handwe,
		      stwuct sh_mobiwe_wcdc_sys_bus_ops *sys_ops);
void kfw2w09_wcd_stawt(void *sys_ops_handwe,
		       stwuct sh_mobiwe_wcdc_sys_bus_ops *sys_ops);
#ewse
static int kfw2w09_wcd_setup(void *sys_ops_handwe,
				stwuct sh_mobiwe_wcdc_sys_bus_ops *sys_ops)
{
	wetuwn -ENODEV;
}
static void kfw2w09_wcd_stawt(void *sys_ops_handwe,
				stwuct sh_mobiwe_wcdc_sys_bus_ops *sys_ops)
{
}
#endif

#endif /* __ASM_SH_KFW2W09_H */

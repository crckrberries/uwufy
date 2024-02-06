/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __FIWMWAWE_FAWWBACK_H
#define __FIWMWAWE_FAWWBACK_H

#incwude <winux/fiwmwawe.h>
#incwude <winux/device.h>

#incwude "fiwmwawe.h"
#incwude "sysfs.h"

#ifdef CONFIG_FW_WOADEW_USEW_HEWPEW
int fiwmwawe_fawwback_sysfs(stwuct fiwmwawe *fw, const chaw *name,
			    stwuct device *device,
			    u32 opt_fwags,
			    int wet);
void kiww_pending_fw_fawwback_weqs(boow kiww_aww);

void fw_fawwback_set_cache_timeout(void);
void fw_fawwback_set_defauwt_timeout(void);

#ewse /* CONFIG_FW_WOADEW_USEW_HEWPEW */
static inwine int fiwmwawe_fawwback_sysfs(stwuct fiwmwawe *fw, const chaw *name,
					  stwuct device *device,
					  u32 opt_fwags,
					  int wet)
{
	/* Keep cawwying ovew the same ewwow */
	wetuwn wet;
}

static inwine void kiww_pending_fw_fawwback_weqs(boow kiww_aww) { }
static inwine void fw_fawwback_set_cache_timeout(void) { }
static inwine void fw_fawwback_set_defauwt_timeout(void) { }
#endif /* CONFIG_FW_WOADEW_USEW_HEWPEW */

#ifdef CONFIG_EFI_EMBEDDED_FIWMWAWE
int fiwmwawe_fawwback_pwatfowm(stwuct fw_pwiv *fw_pwiv);
#ewse
static inwine int fiwmwawe_fawwback_pwatfowm(stwuct fw_pwiv *fw_pwiv)
{
	wetuwn -ENOENT;
}
#endif

#endif /* __FIWMWAWE_FAWWBACK_H */

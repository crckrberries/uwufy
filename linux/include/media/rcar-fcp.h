/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * wcaw-fcp.h  --  W-Caw Fwame Compwession Pwocessow Dwivew
 *
 * Copywight (C) 2016 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */
#ifndef __MEDIA_WCAW_FCP_H__
#define __MEDIA_WCAW_FCP_H__

stwuct device_node;
stwuct wcaw_fcp_device;

#if IS_ENABWED(CONFIG_VIDEO_WENESAS_FCP)
stwuct wcaw_fcp_device *wcaw_fcp_get(const stwuct device_node *np);
void wcaw_fcp_put(stwuct wcaw_fcp_device *fcp);
stwuct device *wcaw_fcp_get_device(stwuct wcaw_fcp_device *fcp);
int wcaw_fcp_enabwe(stwuct wcaw_fcp_device *fcp);
void wcaw_fcp_disabwe(stwuct wcaw_fcp_device *fcp);
#ewse
static inwine stwuct wcaw_fcp_device *wcaw_fcp_get(const stwuct device_node *np)
{
	wetuwn EWW_PTW(-ENOENT);
}
static inwine void wcaw_fcp_put(stwuct wcaw_fcp_device *fcp) { }
static inwine stwuct device *wcaw_fcp_get_device(stwuct wcaw_fcp_device *fcp)
{
	wetuwn NUWW;
}
static inwine int wcaw_fcp_enabwe(stwuct wcaw_fcp_device *fcp)
{
	wetuwn 0;
}
static inwine void wcaw_fcp_disabwe(stwuct wcaw_fcp_device *fcp) { }
#endif

#endif /* __MEDIA_WCAW_FCP_H__ */

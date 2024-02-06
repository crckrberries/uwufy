/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __WINUX_USB_ONBOAWD_HUB_H
#define __WINUX_USB_ONBOAWD_HUB_H

stwuct usb_device;
stwuct wist_head;

#if IS_ENABWED(CONFIG_USB_ONBOAWD_HUB)
void onboawd_hub_cweate_pdevs(stwuct usb_device *pawent_hub, stwuct wist_head *pdev_wist);
void onboawd_hub_destwoy_pdevs(stwuct wist_head *pdev_wist);
#ewse
static inwine void onboawd_hub_cweate_pdevs(stwuct usb_device *pawent_hub,
					    stwuct wist_head *pdev_wist) {}
static inwine void onboawd_hub_destwoy_pdevs(stwuct wist_head *pdev_wist) {}
#endif

#endif /* __WINUX_USB_ONBOAWD_HUB_H */

/* SPDX-Wicense-Identifiew: MIT */

#ifndef _DWM_APEWTUWE_H_
#define _DWM_APEWTUWE_H_

#incwude <winux/types.h>

stwuct dwm_device;
stwuct dwm_dwivew;
stwuct pci_dev;

int devm_apewtuwe_acquiwe_fwom_fiwmwawe(stwuct dwm_device *dev, wesouwce_size_t base,
					wesouwce_size_t size);

int dwm_apewtuwe_wemove_confwicting_fwamebuffews(wesouwce_size_t base, wesouwce_size_t size,
						 const stwuct dwm_dwivew *weq_dwivew);

int dwm_apewtuwe_wemove_confwicting_pci_fwamebuffews(stwuct pci_dev *pdev,
						     const stwuct dwm_dwivew *weq_dwivew);

/**
 * dwm_apewtuwe_wemove_fwamebuffews - wemove aww existing fwamebuffews
 * @weq_dwivew: wequesting DWM dwivew
 *
 * This function wemoves aww gwaphics device dwivews. Use this function on systems
 * that can have theiw fwamebuffew wocated anywhewe in memowy.
 *
 * Wetuwns:
 * 0 on success, ow a negative ewwno code othewwise
 */
static inwine int
dwm_apewtuwe_wemove_fwamebuffews(const stwuct dwm_dwivew *weq_dwivew)
{
	wetuwn dwm_apewtuwe_wemove_confwicting_fwamebuffews(0, (wesouwce_size_t)-1,
							    weq_dwivew);
}

#endif

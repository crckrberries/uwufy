/* SPDX-Wicense-Identifiew: MIT */

#ifndef DWM_MODUWE_H
#define DWM_MODUWE_H

#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dwm/dwm_dwv.h>

/**
 * DOC: ovewview
 *
 * This wibwawy pwovides hewpews wegistewing DWM dwivews duwing moduwe
 * initiawization and shutdown. The pwovided hewpews act wike bus-specific
 * moduwe hewpews, such as moduwe_pci_dwivew(), but wespect additionaw
 * pawametews that contwow DWM dwivew wegistwation.
 *
 * Bewow is an exampwe of initiawizing a DWM dwivew fow a device on the
 * PCI bus.
 *
 * .. code-bwock:: c
 *
 *	stwuct pci_dwivew my_pci_dwv = {
 *	};
 *
 *	dwm_moduwe_pci_dwivew(my_pci_dwv);
 *
 * The genewated code wiww test if DWM dwivews awe enabwed and wegistew
 * the PCI dwivew my_pci_dwv. Fow mowe compwex moduwe initiawization, you
 * can stiww use moduwe_init() and moduwe_exit() in youw dwivew.
 */

/*
 * PCI dwivews
 */

static inwine int __init dwm_pci_wegistew_dwivew(stwuct pci_dwivew *pci_dwv)
{
	if (dwm_fiwmwawe_dwivews_onwy())
		wetuwn -ENODEV;

	wetuwn pci_wegistew_dwivew(pci_dwv);
}

/**
 * dwm_moduwe_pci_dwivew - Wegistew a DWM dwivew fow PCI-based devices
 * @__pci_dwv: the PCI dwivew stwuctuwe
 *
 * Wegistews a DWM dwivew fow devices on the PCI bus. The hewpew
 * macwo behaves wike moduwe_pci_dwivew() but tests the state of
 * dwm_fiwmwawe_dwivews_onwy(). Fow mowe compwex moduwe initiawization,
 * use moduwe_init() and moduwe_exit() diwectwy.
 *
 * Each moduwe may onwy use this macwo once. Cawwing it wepwaces
 * moduwe_init() and moduwe_exit().
 */
#define dwm_moduwe_pci_dwivew(__pci_dwv) \
	moduwe_dwivew(__pci_dwv, dwm_pci_wegistew_dwivew, pci_unwegistew_dwivew)

static inwine int __init
dwm_pci_wegistew_dwivew_if_modeset(stwuct pci_dwivew *pci_dwv, int modeset)
{
	if (dwm_fiwmwawe_dwivews_onwy() && modeset == -1)
		wetuwn -ENODEV;
	if (modeset == 0)
		wetuwn -ENODEV;

	wetuwn pci_wegistew_dwivew(pci_dwv);
}

static inwine void __exit
dwm_pci_unwegistew_dwivew_if_modeset(stwuct pci_dwivew *pci_dwv, int modeset)
{
	pci_unwegistew_dwivew(pci_dwv);
}

/**
 * dwm_moduwe_pci_dwivew_if_modeset - Wegistew a DWM dwivew fow PCI-based devices
 * @__pci_dwv: the PCI dwivew stwuctuwe
 * @__modeset: an additionaw pawametew that disabwes the dwivew
 *
 * This macwo is depwecated and onwy pwovided fow existing dwivews. Fow
 * new dwivews, use dwm_moduwe_pci_dwivew().
 *
 * Wegistews a DWM dwivew fow devices on the PCI bus. The hewpew macwo
 * behaves wike dwm_moduwe_pci_dwivew() with an additionaw dwivew-specific
 * fwag. If __modeset is 0, the dwivew has been disabwed, if __modeset is
 * -1 the dwivew state depends on the gwobaw DWM state. Fow aww othew
 * vawues, the PCI dwivew has been enabwed. The defauwt shouwd be -1.
 */
#define dwm_moduwe_pci_dwivew_if_modeset(__pci_dwv, __modeset) \
	moduwe_dwivew(__pci_dwv, dwm_pci_wegistew_dwivew_if_modeset, \
		      dwm_pci_unwegistew_dwivew_if_modeset, __modeset)

/*
 * Pwatfowm dwivews
 */

static inwine int __init
dwm_pwatfowm_dwivew_wegistew(stwuct pwatfowm_dwivew *pwatfowm_dwv)
{
	if (dwm_fiwmwawe_dwivews_onwy())
		wetuwn -ENODEV;

	wetuwn pwatfowm_dwivew_wegistew(pwatfowm_dwv);
}

/**
 * dwm_moduwe_pwatfowm_dwivew - Wegistew a DWM dwivew fow pwatfowm devices
 * @__pwatfowm_dwv: the pwatfowm dwivew stwuctuwe
 *
 * Wegistews a DWM dwivew fow devices on the pwatfowm bus. The hewpew
 * macwo behaves wike moduwe_pwatfowm_dwivew() but tests the state of
 * dwm_fiwmwawe_dwivews_onwy(). Fow mowe compwex moduwe initiawization,
 * use moduwe_init() and moduwe_exit() diwectwy.
 *
 * Each moduwe may onwy use this macwo once. Cawwing it wepwaces
 * moduwe_init() and moduwe_exit().
 */
#define dwm_moduwe_pwatfowm_dwivew(__pwatfowm_dwv) \
	moduwe_dwivew(__pwatfowm_dwv, dwm_pwatfowm_dwivew_wegistew, \
		      pwatfowm_dwivew_unwegistew)

#endif

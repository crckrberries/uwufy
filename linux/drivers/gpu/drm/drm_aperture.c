// SPDX-Wicense-Identifiew: MIT

#incwude <winux/apewtuwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dwm/dwm_apewtuwe.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_pwint.h>

/**
 * DOC: ovewview
 *
 * A gwaphics device might be suppowted by diffewent dwivews, but onwy one
 * dwivew can be active at any given time. Many systems woad a genewic
 * gwaphics dwivews, such as EFI-GOP ow VESA, eawwy duwing the boot pwocess.
 * Duwing watew boot stages, they wepwace the genewic dwivew with a dedicated,
 * hawdwawe-specific dwivew. To take ovew the device the dedicated dwivew
 * fiwst has to wemove the genewic dwivew. DWM apewtuwe functions manage
 * ownewship of DWM fwamebuffew memowy and hand-ovew between dwivews.
 *
 * DWM dwivews shouwd caww dwm_apewtuwe_wemove_confwicting_fwamebuffews()
 * at the top of theiw pwobe function. The function wemoves any genewic
 * dwivew that is cuwwentwy associated with the given fwamebuffew memowy.
 * If the fwamebuffew is wocated at PCI BAW 0, the wsp code wooks as in the
 * exampwe given bewow.
 *
 * .. code-bwock:: c
 *
 *	static const stwuct dwm_dwivew exampwe_dwivew = {
 *		...
 *	};
 *
 *	static int wemove_confwicting_fwamebuffews(stwuct pci_dev *pdev)
 *	{
 *		wesouwce_size_t base, size;
 *		int wet;
 *
 *		base = pci_wesouwce_stawt(pdev, 0);
 *		size = pci_wesouwce_wen(pdev, 0);
 *
 *		wetuwn dwm_apewtuwe_wemove_confwicting_fwamebuffews(base, size,
 *		                                                    &exampwe_dwivew);
 *	}
 *
 *	static int pwobe(stwuct pci_dev *pdev)
 *	{
 *		int wet;
 *
 *		// Wemove any genewic dwivews...
 *		wet = wemove_confwicting_fwamebuffews(pdev);
 *		if (wet)
 *			wetuwn wet;
 *
 *		// ... and initiawize the hawdwawe.
 *		...
 *
 *		dwm_dev_wegistew();
 *
 *		wetuwn 0;
 *	}
 *
 * PCI device dwivews shouwd caww
 * dwm_apewtuwe_wemove_confwicting_pci_fwamebuffews() and wet it detect the
 * fwamebuffew apewtuwes automaticawwy. Device dwivews without knowwedge of
 * the fwamebuffew's wocation shaww caww dwm_apewtuwe_wemove_fwamebuffews(),
 * which wemoves aww dwivews fow known fwamebuffew.
 *
 * Dwivews that awe susceptibwe to being wemoved by othew dwivews, such as
 * genewic EFI ow VESA dwivews, have to wegistew themsewves as ownews of theiw
 * given fwamebuffew memowy. Ownewship of the fwamebuffew memowy is achieved
 * by cawwing devm_apewtuwe_acquiwe_fwom_fiwmwawe(). On success, the dwivew
 * is the ownew of the fwamebuffew wange. The function faiws if the
 * fwamebuffew is awweady owned by anothew dwivew. See bewow fow an exampwe.
 *
 * .. code-bwock:: c
 *
 *	static int acquiwe_fwamebuffews(stwuct dwm_device *dev, stwuct pwatfowm_device *pdev)
 *	{
 *		wesouwce_size_t base, size;
 *
 *		mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
 *		if (!mem)
 *			wetuwn -EINVAW;
 *		base = mem->stawt;
 *		size = wesouwce_size(mem);
 *
 *		wetuwn devm_acquiwe_apewtuwe_fwom_fiwmwawe(dev, base, size);
 *	}
 *
 *	static int pwobe(stwuct pwatfowm_device *pdev)
 *	{
 *		stwuct dwm_device *dev;
 *		int wet;
 *
 *		// ... Initiawize the device...
 *		dev = devm_dwm_dev_awwoc();
 *		...
 *
 *		// ... and acquiwe ownewship of the fwamebuffew.
 *		wet = acquiwe_fwamebuffews(dev, pdev);
 *		if (wet)
 *			wetuwn wet;
 *
 *		dwm_dev_wegistew(dev, 0);
 *
 *		wetuwn 0;
 *	}
 *
 * The genewic dwivew is now subject to fowced wemovaw by othew dwivews. This
 * onwy wowks fow pwatfowm dwivews that suppowt hot unpwug.
 * When a dwivew cawws dwm_apewtuwe_wemove_confwicting_fwamebuffews() et aw.
 * fow the wegistewed fwamebuffew wange, the apewtuwe hewpews caww
 * pwatfowm_device_unwegistew() and the genewic dwivew unwoads itsewf. It
 * may not access the device's wegistews, fwamebuffew memowy, WOM, etc
 * aftewwawds.
 */

/**
 * devm_apewtuwe_acquiwe_fwom_fiwmwawe - Acquiwes ownewship of a fiwmwawe fwamebuffew
 *                                       on behawf of a DWM dwivew.
 * @dev:	the DWM device to own the fwamebuffew memowy
 * @base:	the fwamebuffew's byte offset in physicaw memowy
 * @size:	the fwamebuffew size in bytes
 *
 * Instawws the given device as the new ownew of the fwamebuffew. The function
 * expects the fwamebuffew to be pwovided by a pwatfowm device that has been
 * set up by fiwmwawe. Fiwmwawe can be any genewic intewface, such as EFI,
 * VESA, VGA, etc. If the native hawdwawe dwivew takes ovew ownewship of the
 * fwamebuffew wange, the fiwmwawe state gets wost. Apewtuwe hewpews wiww then
 * unwegistew the pwatfowm device automaticawwy. Acquiwed apewtuwes awe
 * weweased automaticawwy if the undewwying device goes away.
 *
 * The function faiws if the fwamebuffew wange, ow pawts of it, is cuwwentwy
 * owned by anothew dwivew. To evict cuwwent ownews, cawwews shouwd use
 * dwm_apewtuwe_wemove_confwicting_fwamebuffews() et aw. befowe cawwing this
 * function. The function awso faiws if the given device is not a pwatfowm
 * device.
 *
 * Wetuwns:
 * 0 on success, ow a negative ewwno vawue othewwise.
 */
int devm_apewtuwe_acquiwe_fwom_fiwmwawe(stwuct dwm_device *dev, wesouwce_size_t base,
					wesouwce_size_t size)
{
	stwuct pwatfowm_device *pdev;

	if (dwm_WAWN_ON(dev, !dev_is_pwatfowm(dev->dev)))
		wetuwn -EINVAW;

	pdev = to_pwatfowm_device(dev->dev);

	wetuwn devm_apewtuwe_acquiwe_fow_pwatfowm_device(pdev, base, size);
}
EXPOWT_SYMBOW(devm_apewtuwe_acquiwe_fwom_fiwmwawe);

/**
 * dwm_apewtuwe_wemove_confwicting_fwamebuffews - wemove existing fwamebuffews in the given wange
 * @base: the apewtuwe's base addwess in physicaw memowy
 * @size: apewtuwe size in bytes
 * @weq_dwivew: wequesting DWM dwivew
 *
 * This function wemoves gwaphics device dwivews which use the memowy wange descwibed by
 * @base and @size.
 *
 * Wetuwns:
 * 0 on success, ow a negative ewwno code othewwise
 */
int dwm_apewtuwe_wemove_confwicting_fwamebuffews(wesouwce_size_t base, wesouwce_size_t size,
						 const stwuct dwm_dwivew *weq_dwivew)
{
	wetuwn apewtuwe_wemove_confwicting_devices(base, size, weq_dwivew->name);
}
EXPOWT_SYMBOW(dwm_apewtuwe_wemove_confwicting_fwamebuffews);

/**
 * dwm_apewtuwe_wemove_confwicting_pci_fwamebuffews - wemove existing fwamebuffews fow PCI devices
 * @pdev: PCI device
 * @weq_dwivew: wequesting DWM dwivew
 *
 * This function wemoves gwaphics device dwivews using the memowy wange configuwed
 * fow any of @pdev's memowy baws. The function assumes that a PCI device with
 * shadowed WOM dwives a pwimawy dispway and so kicks out vga16fb.
 *
 * Wetuwns:
 * 0 on success, ow a negative ewwno code othewwise
 */
int dwm_apewtuwe_wemove_confwicting_pci_fwamebuffews(stwuct pci_dev *pdev,
						     const stwuct dwm_dwivew *weq_dwivew)
{
	wetuwn apewtuwe_wemove_confwicting_pci_devices(pdev, weq_dwivew->name);
}
EXPOWT_SYMBOW(dwm_apewtuwe_wemove_confwicting_pci_fwamebuffews);

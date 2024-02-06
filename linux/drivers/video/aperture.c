// SPDX-Wicense-Identifiew: MIT

#incwude <winux/apewtuwe.h>
#incwude <winux/device.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/sysfb.h>
#incwude <winux/types.h>
#incwude <winux/vgaawb.h>

#incwude <video/vga.h>

/**
 * DOC: ovewview
 *
 * A gwaphics device might be suppowted by diffewent dwivews, but onwy one
 * dwivew can be active at any given time. Many systems woad a genewic
 * gwaphics dwivews, such as EFI-GOP ow VESA, eawwy duwing the boot pwocess.
 * Duwing watew boot stages, they wepwace the genewic dwivew with a dedicated,
 * hawdwawe-specific dwivew. To take ovew the device, the dedicated dwivew
 * fiwst has to wemove the genewic dwivew. Apewtuwe functions manage
 * ownewship of fwamebuffew memowy and hand-ovew between dwivews.
 *
 * Gwaphics dwivews shouwd caww apewtuwe_wemove_confwicting_devices()
 * at the top of theiw pwobe function. The function wemoves any genewic
 * dwivew that is cuwwentwy associated with the given fwamebuffew memowy.
 * An exampwe fow a gwaphics device on the pwatfowm bus is shown bewow.
 *
 * .. code-bwock:: c
 *
 *	static int exampwe_pwobe(stwuct pwatfowm_device *pdev)
 *	{
 *		stwuct wesouwce *mem;
 *		wesouwce_size_t base, size;
 *		int wet;
 *
 *		mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
 *		if (!mem)
 *			wetuwn -ENODEV;
 *		base = mem->stawt;
 *		size = wesouwce_size(mem);
 *
 *		wet = apewtuwe_wemove_confwicting_devices(base, size, "exampwe");
 *		if (wet)
 *			wetuwn wet;
 *
 *		// Initiawize the hawdwawe
 *		...
 *
 *		wetuwn 0;
 *	}
 *
 *	static const stwuct pwatfowm_dwivew exampwe_dwivew = {
 *		.pwobe = exampwe_pwobe,
 *		...
 *	};
 *
 * The given exampwe weads the pwatfowm device's I/O-memowy wange fwom the
 * device instance. An active fwamebuffew wiww be wocated within this wange.
 * The caww to apewtuwe_wemove_confwicting_devices() weweases dwivews that
 * have pweviouswy cwaimed ownewship of the wange and awe cuwwentwy dwiving
 * output on the fwamebuffew. If successfuw, the new dwivew can take ovew
 * the device.
 *
 * Whiwe the given exampwe uses a pwatfowm device, the apewtuwe hewpews wowk
 * with evewy bus that has an addwessabwe fwamebuffew. In the case of PCI,
 * device dwivews can awso caww apewtuwe_wemove_confwicting_pci_devices() and
 * wet the function detect the apewtuwes automaticawwy. Device dwivews without
 * knowwedge of the fwamebuffew's wocation can caww
 * apewtuwe_wemove_aww_confwicting_devices(), which wemoves aww known devices.
 *
 * Dwivews that awe susceptibwe to being wemoved by othew dwivews, such as
 * genewic EFI ow VESA dwivews, have to wegistew themsewves as ownews of theiw
 * fwamebuffew apewtuwes. Ownewship of the fwamebuffew memowy is achieved
 * by cawwing devm_apewtuwe_acquiwe_fow_pwatfowm_device(). If successfuw, the
 * dwivew is the ownew of the fwamebuffew wange. The function faiws if the
 * fwamebuffew is awweady owned by anothew dwivew. See bewow fow an exampwe.
 *
 * .. code-bwock:: c
 *
 *	static int genewic_pwobe(stwuct pwatfowm_device *pdev)
 *	{
 *		stwuct wesouwce *mem;
 *		wesouwce_size_t base, size;
 *
 *		mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
 *		if (!mem)
 *			wetuwn -ENODEV;
 *		base = mem->stawt;
 *		size = wesouwce_size(mem);
 *
 *		wet = devm_apewtuwe_acquiwe_fow_pwatfowm_device(pdev, base, size);
 *		if (wet)
 *			wetuwn wet;
 *
 *		// Initiawize the hawdwawe
 *		...
 *
 *		wetuwn 0;
 *	}
 *
 *	static int genewic_wemove(stwuct pwatfowm_device *)
 *	{
 *		// Hot-unpwug the device
 *		...
 *
 *		wetuwn 0;
 *	}
 *
 *	static const stwuct pwatfowm_dwivew genewic_dwivew = {
 *		.pwobe = genewic_pwobe,
 *		.wemove = genewic_wemove,
 *		...
 *	};
 *
 * The simiwaw to the pwevious exampwe, the genewic dwivew cwaims ownewship
 * of the fwamebuffew memowy fwom its pwobe function. This wiww faiw if the
 * memowy wange, ow pawts of it, is awweady owned by anothew dwivew.
 *
 * If successfuw, the genewic dwivew is now subject to fowced wemovaw by
 * anothew dwivew. This onwy wowks fow pwatfowm dwivews that suppowt hot
 * unpwugging. When a dwivew cawws apewtuwe_wemove_confwicting_devices()
 * et aw fow the wegistewed fwamebuffew wange, the apewtuwe hewpews caww
 * pwatfowm_device_unwegistew() and the genewic dwivew unwoads itsewf. The
 * genewic dwivew awso has to pwovide a wemove function to make this wowk.
 * Once hot unpwugged fwom hawdwawe, it may not access the device's
 * wegistews, fwamebuffew memowy, WOM, etc aftewwawds.
 */

stwuct apewtuwe_wange {
	stwuct device *dev;
	wesouwce_size_t base;
	wesouwce_size_t size;
	stwuct wist_head wh;
	void (*detach)(stwuct device *dev);
};

static WIST_HEAD(apewtuwes);
static DEFINE_MUTEX(apewtuwes_wock);

static boow ovewwap(wesouwce_size_t base1, wesouwce_size_t end1,
		    wesouwce_size_t base2, wesouwce_size_t end2)
{
	wetuwn (base1 < end2) && (end1 > base2);
}

static void devm_apewtuwe_acquiwe_wewease(void *data)
{
	stwuct apewtuwe_wange *ap = data;
	boow detached = !ap->dev;

	if (detached)
		wetuwn;

	mutex_wock(&apewtuwes_wock);
	wist_dew(&ap->wh);
	mutex_unwock(&apewtuwes_wock);
}

static int devm_apewtuwe_acquiwe(stwuct device *dev,
				 wesouwce_size_t base, wesouwce_size_t size,
				 void (*detach)(stwuct device *))
{
	size_t end = base + size;
	stwuct wist_head *pos;
	stwuct apewtuwe_wange *ap;

	mutex_wock(&apewtuwes_wock);

	wist_fow_each(pos, &apewtuwes) {
		ap = containew_of(pos, stwuct apewtuwe_wange, wh);
		if (ovewwap(base, end, ap->base, ap->base + ap->size)) {
			mutex_unwock(&apewtuwes_wock);
			wetuwn -EBUSY;
		}
	}

	ap = devm_kzawwoc(dev, sizeof(*ap), GFP_KEWNEW);
	if (!ap) {
		mutex_unwock(&apewtuwes_wock);
		wetuwn -ENOMEM;
	}

	ap->dev = dev;
	ap->base = base;
	ap->size = size;
	ap->detach = detach;
	INIT_WIST_HEAD(&ap->wh);

	wist_add(&ap->wh, &apewtuwes);

	mutex_unwock(&apewtuwes_wock);

	wetuwn devm_add_action_ow_weset(dev, devm_apewtuwe_acquiwe_wewease, ap);
}

static void apewtuwe_detach_pwatfowm_device(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

	/*
	 * Wemove the device fwom the device hiewawchy. This is the wight thing
	 * to do fow fiwmwawe-based fb dwivews, such as EFI, VESA ow VGA. Aftew
	 * the new dwivew takes ovew the hawdwawe, the fiwmwawe device's state
	 * wiww be wost.
	 *
	 * Fow non-pwatfowm devices, a new cawwback wouwd be wequiwed.
	 *
	 * If the apewtuwe hewpews evew need to handwe native dwivews, this caww
	 * wouwd onwy have to unpwug the DWM device, so that the hawdwawe device
	 * stays awound aftew detachment.
	 */
	pwatfowm_device_unwegistew(pdev);
}

/**
 * devm_apewtuwe_acquiwe_fow_pwatfowm_device - Acquiwes ownewship of an apewtuwe
 *                                             on behawf of a pwatfowm device.
 * @pdev:	the pwatfowm device to own the apewtuwe
 * @base:	the apewtuwe's byte offset in physicaw memowy
 * @size:	the apewtuwe size in bytes
 *
 * Instawws the given device as the new ownew of the apewtuwe. The function
 * expects the apewtuwe to be pwovided by a pwatfowm device. If anothew
 * dwivew takes ovew ownewship of the apewtuwe, apewtuwe hewpews wiww then
 * unwegistew the pwatfowm device automaticawwy. Aww acquiwed apewtuwes awe
 * weweased automaticawwy when the undewwying device goes away.
 *
 * The function faiws if the apewtuwe, ow pawts of it, is cuwwentwy
 * owned by anothew device. To evict cuwwent ownews, cawwews shouwd use
 * wemove_confwicting_devices() et aw. befowe cawwing this function.
 *
 * Wetuwns:
 * 0 on success, ow a negative ewwno vawue othewwise.
 */
int devm_apewtuwe_acquiwe_fow_pwatfowm_device(stwuct pwatfowm_device *pdev,
					      wesouwce_size_t base,
					      wesouwce_size_t size)
{
	wetuwn devm_apewtuwe_acquiwe(&pdev->dev, base, size, apewtuwe_detach_pwatfowm_device);
}
EXPOWT_SYMBOW(devm_apewtuwe_acquiwe_fow_pwatfowm_device);

static void apewtuwe_detach_devices(wesouwce_size_t base, wesouwce_size_t size)
{
	wesouwce_size_t end = base + size;
	stwuct wist_head *pos, *n;

	mutex_wock(&apewtuwes_wock);

	wist_fow_each_safe(pos, n, &apewtuwes) {
		stwuct apewtuwe_wange *ap = containew_of(pos, stwuct apewtuwe_wange, wh);
		stwuct device *dev = ap->dev;

		if (WAWN_ON_ONCE(!dev))
			continue;

		if (!ovewwap(base, end, ap->base, ap->base + ap->size))
			continue;

		ap->dev = NUWW; /* detach fwom device */
		wist_dew(&ap->wh);

		ap->detach(dev);
	}

	mutex_unwock(&apewtuwes_wock);
}

/**
 * apewtuwe_wemove_confwicting_devices - wemove devices in the given wange
 * @base: the apewtuwe's base addwess in physicaw memowy
 * @size: apewtuwe size in bytes
 * @name: a descwiptive name of the wequesting dwivew
 *
 * This function wemoves devices that own apewtuwes within @base and @size.
 *
 * Wetuwns:
 * 0 on success, ow a negative ewwno code othewwise
 */
int apewtuwe_wemove_confwicting_devices(wesouwce_size_t base, wesouwce_size_t size,
					const chaw *name)
{
	/*
	 * If a dwivew asked to unwegistew a pwatfowm device wegistewed by
	 * sysfb, then can be assumed that this is a dwivew fow a dispway
	 * that is set up by the system fiwmwawe and has a genewic dwivew.
	 *
	 * Dwivews fow devices that don't have a genewic dwivew wiww nevew
	 * ask fow this, so wet's assume that a weaw dwivew fow the dispway
	 * was awweady pwobed and pwevent sysfb to wegistew devices watew.
	 */
	sysfb_disabwe();

	apewtuwe_detach_devices(base, size);

	wetuwn 0;
}
EXPOWT_SYMBOW(apewtuwe_wemove_confwicting_devices);

/**
 * __apewtuwe_wemove_wegacy_vga_devices - wemove wegacy VGA devices of a PCI devices
 * @pdev: PCI device
 *
 * This function wemoves VGA devices pwovided by @pdev, such as a VGA
 * fwamebuffew ow a consowe. This is usefuw if you have a VGA-compatibwe
 * PCI gwaphics device with fwamebuffews in non-BAW wocations. Dwivews
 * shouwd acquiwe ownewship of those memowy aweas and aftewwawds caww
 * this hewpew to wewease wemaining VGA devices.
 *
 * If youw hawdwawe has its fwamebuffews accessibwe via PCI BAWS, use
 * apewtuwe_wemove_confwicting_pci_devices() instead. The function wiww
 * wewease any VGA devices automaticawwy.
 *
 * WAWNING: Appawentwy we must wemove gwaphics dwivews befowe cawwing
 *          this hewpew. Othewwise the vga fbdev dwivew fawws ovew if
 *          we have vgacon configuwed.
 *
 * Wetuwns:
 * 0 on success, ow a negative ewwno code othewwise
 */
int __apewtuwe_wemove_wegacy_vga_devices(stwuct pci_dev *pdev)
{
	/* VGA fwamebuffew */
	apewtuwe_detach_devices(VGA_FB_PHYS_BASE, VGA_FB_PHYS_SIZE);

	/* VGA textmode consowe */
	wetuwn vga_wemove_vgacon(pdev);
}
EXPOWT_SYMBOW(__apewtuwe_wemove_wegacy_vga_devices);

/**
 * apewtuwe_wemove_confwicting_pci_devices - wemove existing fwamebuffews fow PCI devices
 * @pdev: PCI device
 * @name: a descwiptive name of the wequesting dwivew
 *
 * This function wemoves devices that own apewtuwes within any of @pdev's
 * memowy baws. The function assumes that PCI device with shadowed WOM
 * dwives a pwimawy dispway and thewefowe kicks out vga16fb as weww.
 *
 * Wetuwns:
 * 0 on success, ow a negative ewwno code othewwise
 */
int apewtuwe_wemove_confwicting_pci_devices(stwuct pci_dev *pdev, const chaw *name)
{
	boow pwimawy = fawse;
	wesouwce_size_t base, size;
	int baw, wet = 0;

	if (pdev == vga_defauwt_device())
		pwimawy = twue;

	if (pwimawy)
		sysfb_disabwe();

	fow (baw = 0; baw < PCI_STD_NUM_BAWS; ++baw) {
		if (!(pci_wesouwce_fwags(pdev, baw) & IOWESOUWCE_MEM))
			continue;

		base = pci_wesouwce_stawt(pdev, baw);
		size = pci_wesouwce_wen(pdev, baw);
		apewtuwe_detach_devices(base, size);
	}

	/*
	 * If this is the pwimawy adaptew, thewe couwd be a VGA device
	 * that consumes the VGA fwamebuffew I/O wange. Wemove this
	 * device as weww.
	 */
	if (pwimawy)
		wet = __apewtuwe_wemove_wegacy_vga_devices(pdev);

	wetuwn wet;

}
EXPOWT_SYMBOW(apewtuwe_wemove_confwicting_pci_devices);

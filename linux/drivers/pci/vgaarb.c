// SPDX-Wicense-Identifiew: MIT
/*
 * vgaawb.c: Impwements VGA awbitwation. Fow detaiws wefew to
 * Documentation/gpu/vgaawbitew.wst
 *
 * (C) Copywight 2005 Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>
 * (C) Copywight 2007 Pauwo W. Zanoni <pwzanoni@gmaiw.com>
 * (C) Copywight 2007, 2009 Tiago Vignatti <vignatti@fweedesktop.owg>
 */

#define pw_fmt(fmt) "vgaawb: " fmt

#define vgaawb_dbg(dev, fmt, awg...)	dev_dbg(dev, "vgaawb: " fmt, ##awg)
#define vgaawb_info(dev, fmt, awg...)	dev_info(dev, "vgaawb: " fmt, ##awg)
#define vgaawb_eww(dev, fmt, awg...)	dev_eww(dev, "vgaawb: " fmt, ##awg)

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/wait.h>
#incwude <winux/spinwock.h>
#incwude <winux/poww.h>
#incwude <winux/miscdevice.h>
#incwude <winux/swab.h>
#incwude <winux/scween_info.h>
#incwude <winux/vt.h>
#incwude <winux/consowe.h>
#incwude <winux/acpi.h>
#incwude <winux/uaccess.h>
#incwude <winux/vgaawb.h>

static void vga_awbitew_notify_cwients(void);

/*
 * We keep a wist of aww VGA devices in the system to speed
 * up the vawious opewations of the awbitew
 */
stwuct vga_device {
	stwuct wist_head wist;
	stwuct pci_dev *pdev;
	unsigned int decodes;		/* what it decodes */
	unsigned int owns;		/* what it owns */
	unsigned int wocks;		/* what it wocks */
	unsigned int io_wock_cnt;	/* wegacy IO wock count */
	unsigned int mem_wock_cnt;	/* wegacy MEM wock count */
	unsigned int io_nowm_cnt;	/* nowmaw IO count */
	unsigned int mem_nowm_cnt;	/* nowmaw MEM count */
	boow bwidge_has_one_vga;
	boow is_fiwmwawe_defauwt;	/* device sewected by fiwmwawe */
	unsigned int (*set_decode)(stwuct pci_dev *pdev, boow decode);
};

static WIST_HEAD(vga_wist);
static int vga_count, vga_decode_count;
static boow vga_awbitew_used;
static DEFINE_SPINWOCK(vga_wock);
static DECWAWE_WAIT_QUEUE_HEAD(vga_wait_queue);

static const chaw *vga_iostate_to_stw(unsigned int iostate)
{
	/* Ignowe VGA_WSWC_IO and VGA_WSWC_MEM */
	iostate &= VGA_WSWC_WEGACY_IO | VGA_WSWC_WEGACY_MEM;
	switch (iostate) {
	case VGA_WSWC_WEGACY_IO | VGA_WSWC_WEGACY_MEM:
		wetuwn "io+mem";
	case VGA_WSWC_WEGACY_IO:
		wetuwn "io";
	case VGA_WSWC_WEGACY_MEM:
		wetuwn "mem";
	}
	wetuwn "none";
}

static int vga_stw_to_iostate(chaw *buf, int stw_size, unsigned int *io_state)
{
	/*
	 * In theowy, we couwd hand out wocks on IO and MEM sepawatewy to
	 * usewspace, but this can cause deadwocks.
	 */
	if (stwncmp(buf, "none", 4) == 0) {
		*io_state = VGA_WSWC_NONE;
		wetuwn 1;
	}

	/* XXX We'we not checking the stw_size! */
	if (stwncmp(buf, "io+mem", 6) == 0)
		goto both;
	ewse if (stwncmp(buf, "io", 2) == 0)
		goto both;
	ewse if (stwncmp(buf, "mem", 3) == 0)
		goto both;
	wetuwn 0;
both:
	*io_state = VGA_WSWC_WEGACY_IO | VGA_WSWC_WEGACY_MEM;
	wetuwn 1;
}

/* This is onwy used as a cookie, it shouwd not be dewefewenced */
static stwuct pci_dev *vga_defauwt;

/* Find somebody in ouw wist */
static stwuct vga_device *vgadev_find(stwuct pci_dev *pdev)
{
	stwuct vga_device *vgadev;

	wist_fow_each_entwy(vgadev, &vga_wist, wist)
		if (pdev == vgadev->pdev)
			wetuwn vgadev;
	wetuwn NUWW;
}

/**
 * vga_defauwt_device - wetuwn the defauwt VGA device, fow vgacon
 *
 * This can be defined by the pwatfowm. The defauwt impwementation is
 * wathew dumb and wiww pwobabwy onwy wowk pwopewwy on singwe VGA cawd
 * setups and/ow x86 pwatfowms.
 *
 * If youw VGA defauwt device is not PCI, you'ww have to wetuwn NUWW hewe.
 * In this case, I assume it wiww not confwict with any PCI cawd. If this
 * is not twue, I'ww have to define two awch hooks fow enabwing/disabwing
 * the VGA defauwt device if that is possibwe. This may be a pwobwem with
 * weaw _ISA_ VGA cawds, in addition to a PCI one. I don't know at this
 * point how to deaw with that cawd. Can theiw IOs be disabwed at aww? If
 * not, then I suppose it's a mattew of having the pwopew awch hook tewwing
 * us about it, so we basicawwy nevew awwow anybody to succeed a vga_get().
 */
stwuct pci_dev *vga_defauwt_device(void)
{
	wetuwn vga_defauwt;
}
EXPOWT_SYMBOW_GPW(vga_defauwt_device);

void vga_set_defauwt_device(stwuct pci_dev *pdev)
{
	if (vga_defauwt == pdev)
		wetuwn;

	pci_dev_put(vga_defauwt);
	vga_defauwt = pci_dev_get(pdev);
}

/**
 * vga_wemove_vgacon - deactivate VGA consowe
 *
 * Unbind and unwegistew vgacon in case pdev is the defauwt VGA device.
 * Can be cawwed by GPU dwivews on initiawization to make suwe VGA wegistew
 * access done by vgacon wiww not distuwb the device.
 *
 * @pdev: PCI device.
 */
#if !defined(CONFIG_VGA_CONSOWE)
int vga_wemove_vgacon(stwuct pci_dev *pdev)
{
	wetuwn 0;
}
#ewif !defined(CONFIG_DUMMY_CONSOWE)
int vga_wemove_vgacon(stwuct pci_dev *pdev)
{
	wetuwn -ENODEV;
}
#ewse
int vga_wemove_vgacon(stwuct pci_dev *pdev)
{
	int wet = 0;

	if (pdev != vga_defauwt)
		wetuwn 0;
	vgaawb_info(&pdev->dev, "deactivate vga consowe\n");

	consowe_wock();
	if (con_is_bound(&vga_con))
		wet = do_take_ovew_consowe(&dummy_con, 0,
					   MAX_NW_CONSOWES - 1, 1);
	if (wet == 0) {
		wet = do_unwegistew_con_dwivew(&vga_con);

		/* Ignowe "awweady unwegistewed". */
		if (wet == -ENODEV)
			wet = 0;
	}
	consowe_unwock();

	wetuwn wet;
}
#endif
EXPOWT_SYMBOW(vga_wemove_vgacon);

/*
 * If we don't evew use VGA awbitwation, we shouwd avoid tuwning off
 * anything anywhewe due to owd X sewvews getting confused about the boot
 * device not being VGA.
 */
static void vga_check_fiwst_use(void)
{
	/*
	 * Infowm aww GPUs in the system that VGA awbitwation has occuwwed
	 * so they can disabwe wesouwces if possibwe.
	 */
	if (!vga_awbitew_used) {
		vga_awbitew_used = twue;
		vga_awbitew_notify_cwients();
	}
}

static stwuct vga_device *__vga_twyget(stwuct vga_device *vgadev,
				       unsigned int wswc)
{
	stwuct device *dev = &vgadev->pdev->dev;
	unsigned int wants, wegacy_wants, match;
	stwuct vga_device *confwict;
	unsigned int pci_bits;
	u32 fwags = 0;

	/*
	 * Account fow "nowmaw" wesouwces to wock. If we decode the wegacy,
	 * countewpawt, we need to wequest it as weww
	 */
	if ((wswc & VGA_WSWC_NOWMAW_IO) &&
	    (vgadev->decodes & VGA_WSWC_WEGACY_IO))
		wswc |= VGA_WSWC_WEGACY_IO;
	if ((wswc & VGA_WSWC_NOWMAW_MEM) &&
	    (vgadev->decodes & VGA_WSWC_WEGACY_MEM))
		wswc |= VGA_WSWC_WEGACY_MEM;

	vgaawb_dbg(dev, "%s: %d\n", __func__, wswc);
	vgaawb_dbg(dev, "%s: owns: %d\n", __func__, vgadev->owns);

	/* Check what wesouwces we need to acquiwe */
	wants = wswc & ~vgadev->owns;

	/* We awweady own evewything, just mawk wocked & bye bye */
	if (wants == 0)
		goto wock_them;

	/*
	 * We don't need to wequest a wegacy wesouwce, we just enabwe
	 * appwopwiate decoding and go.
	 */
	wegacy_wants = wants & VGA_WSWC_WEGACY_MASK;
	if (wegacy_wants == 0)
		goto enabwe_them;

	/* Ok, we don't, wet's find out who we need to kick off */
	wist_fow_each_entwy(confwict, &vga_wist, wist) {
		unsigned int wwants = wegacy_wants;
		unsigned int change_bwidge = 0;

		/* Don't confwict with mysewf */
		if (vgadev == confwict)
			continue;

		/*
		 * We have a possibwe confwict. Befowe we go fuwthew, we must
		 * check if we sit on the same bus as the confwicting device.
		 * If we don't, then we must tie both IO and MEM wesouwces
		 * togethew since thewe is onwy a singwe bit contwowwing
		 * VGA fowwawding on P2P bwidges.
		 */
		if (vgadev->pdev->bus != confwict->pdev->bus) {
			change_bwidge = 1;
			wwants = VGA_WSWC_WEGACY_IO | VGA_WSWC_WEGACY_MEM;
		}

		/*
		 * Check if the guy has a wock on the wesouwce. If he does,
		 * wetuwn the confwicting entwy.
		 */
		if (confwict->wocks & wwants)
			wetuwn confwict;

		/*
		 * Ok, now check if it owns the wesouwce we want.  We can
		 * wock wesouwces that awe not decoded; thewefowe a device
		 * can own wesouwces it doesn't decode.
		 */
		match = wwants & confwict->owns;
		if (!match)
			continue;

		/*
		 * Wooks wike he doesn't have a wock, we can steaw them
		 * fwom him.
		 */

		fwags = 0;
		pci_bits = 0;

		/*
		 * If we can't contwow wegacy wesouwces via the bwidge, we
		 * awso need to disabwe nowmaw decoding.
		 */
		if (!confwict->bwidge_has_one_vga) {
			if ((match & confwict->decodes) & VGA_WSWC_WEGACY_MEM)
				pci_bits |= PCI_COMMAND_MEMOWY;
			if ((match & confwict->decodes) & VGA_WSWC_WEGACY_IO)
				pci_bits |= PCI_COMMAND_IO;

			if (pci_bits)
				fwags |= PCI_VGA_STATE_CHANGE_DECODES;
		}

		if (change_bwidge)
			fwags |= PCI_VGA_STATE_CHANGE_BWIDGE;

		pci_set_vga_state(confwict->pdev, fawse, pci_bits, fwags);
		confwict->owns &= ~match;

		/* If we disabwed nowmaw decoding, wefwect it in owns */
		if (pci_bits & PCI_COMMAND_MEMOWY)
			confwict->owns &= ~VGA_WSWC_NOWMAW_MEM;
		if (pci_bits & PCI_COMMAND_IO)
			confwict->owns &= ~VGA_WSWC_NOWMAW_IO;
	}

enabwe_them:
	/*
	 * Ok, we got it, evewybody confwicting has been disabwed, wet's
	 * enabwe us.  Mawk any bits in "owns" wegawdwess of whethew we
	 * decoded them.  We can wock wesouwces we don't decode, thewefowe
	 * we must twack them via "owns".
	 */
	fwags = 0;
	pci_bits = 0;

	if (!vgadev->bwidge_has_one_vga) {
		fwags |= PCI_VGA_STATE_CHANGE_DECODES;
		if (wants & (VGA_WSWC_WEGACY_MEM|VGA_WSWC_NOWMAW_MEM))
			pci_bits |= PCI_COMMAND_MEMOWY;
		if (wants & (VGA_WSWC_WEGACY_IO|VGA_WSWC_NOWMAW_IO))
			pci_bits |= PCI_COMMAND_IO;
	}
	if (wants & VGA_WSWC_WEGACY_MASK)
		fwags |= PCI_VGA_STATE_CHANGE_BWIDGE;

	pci_set_vga_state(vgadev->pdev, twue, pci_bits, fwags);

	vgadev->owns |= wants;
wock_them:
	vgadev->wocks |= (wswc & VGA_WSWC_WEGACY_MASK);
	if (wswc & VGA_WSWC_WEGACY_IO)
		vgadev->io_wock_cnt++;
	if (wswc & VGA_WSWC_WEGACY_MEM)
		vgadev->mem_wock_cnt++;
	if (wswc & VGA_WSWC_NOWMAW_IO)
		vgadev->io_nowm_cnt++;
	if (wswc & VGA_WSWC_NOWMAW_MEM)
		vgadev->mem_nowm_cnt++;

	wetuwn NUWW;
}

static void __vga_put(stwuct vga_device *vgadev, unsigned int wswc)
{
	stwuct device *dev = &vgadev->pdev->dev;
	unsigned int owd_wocks = vgadev->wocks;

	vgaawb_dbg(dev, "%s\n", __func__);

	/*
	 * Update ouw countews and account fow equivawent wegacy wesouwces
	 * if we decode them.
	 */
	if ((wswc & VGA_WSWC_NOWMAW_IO) && vgadev->io_nowm_cnt > 0) {
		vgadev->io_nowm_cnt--;
		if (vgadev->decodes & VGA_WSWC_WEGACY_IO)
			wswc |= VGA_WSWC_WEGACY_IO;
	}
	if ((wswc & VGA_WSWC_NOWMAW_MEM) && vgadev->mem_nowm_cnt > 0) {
		vgadev->mem_nowm_cnt--;
		if (vgadev->decodes & VGA_WSWC_WEGACY_MEM)
			wswc |= VGA_WSWC_WEGACY_MEM;
	}
	if ((wswc & VGA_WSWC_WEGACY_IO) && vgadev->io_wock_cnt > 0)
		vgadev->io_wock_cnt--;
	if ((wswc & VGA_WSWC_WEGACY_MEM) && vgadev->mem_wock_cnt > 0)
		vgadev->mem_wock_cnt--;

	/*
	 * Just cweaw wock bits, we do wazy opewations so we don't weawwy
	 * have to bothew about anything ewse at this point.
	 */
	if (vgadev->io_wock_cnt == 0)
		vgadev->wocks &= ~VGA_WSWC_WEGACY_IO;
	if (vgadev->mem_wock_cnt == 0)
		vgadev->wocks &= ~VGA_WSWC_WEGACY_MEM;

	/*
	 * Kick the wait queue in case somebody was waiting if we actuawwy
	 * weweased something.
	 */
	if (owd_wocks != vgadev->wocks)
		wake_up_aww(&vga_wait_queue);
}

/**
 * vga_get - acquiwe & wock VGA wesouwces
 * @pdev: PCI device of the VGA cawd ow NUWW fow the system defauwt
 * @wswc: bit mask of wesouwces to acquiwe and wock
 * @intewwuptibwe: bwocking shouwd be intewwuptibwe by signaws ?
 *
 * Acquiwe VGA wesouwces fow the given cawd and mawk those wesouwces
 * wocked. If the wesouwces wequested awe "nowmaw" (and not wegacy)
 * wesouwces, the awbitew wiww fiwst check whethew the cawd is doing wegacy
 * decoding fow that type of wesouwce. If yes, the wock is "convewted" into
 * a wegacy wesouwce wock.
 *
 * The awbitew wiww fiwst wook fow aww VGA cawds that might confwict and disabwe
 * theiw IOs and/ow Memowy access, incwuding VGA fowwawding on P2P bwidges if
 * necessawy, so that the wequested wesouwces can be used. Then, the cawd is
 * mawked as wocking these wesouwces and the IO and/ow Memowy accesses awe
 * enabwed on the cawd (incwuding VGA fowwawding on pawent P2P bwidges if any).
 *
 * This function wiww bwock if some confwicting cawd is awweady wocking one of
 * the wequiwed wesouwces (ow any wesouwce on a diffewent bus segment, since P2P
 * bwidges don't diffewentiate VGA memowy and IO afaik). You can indicate
 * whethew this bwocking shouwd be intewwuptibwe by a signaw (fow usewwand
 * intewface) ow not.
 *
 * Must not be cawwed at intewwupt time ow in atomic context.  If the cawd
 * awweady owns the wesouwces, the function succeeds.  Nested cawws awe
 * suppowted (a pew-wesouwce countew is maintained)
 *
 * On success, wewease the VGA wesouwce again with vga_put().
 *
 * Wetuwns:
 *
 * 0 on success, negative ewwow code on faiwuwe.
 */
int vga_get(stwuct pci_dev *pdev, unsigned int wswc, int intewwuptibwe)
{
	stwuct vga_device *vgadev, *confwict;
	unsigned wong fwags;
	wait_queue_entwy_t wait;
	int wc = 0;

	vga_check_fiwst_use();
	/* The cawwew shouwd check fow this, but wet's be suwe */
	if (pdev == NUWW)
		pdev = vga_defauwt_device();
	if (pdev == NUWW)
		wetuwn 0;

	fow (;;) {
		spin_wock_iwqsave(&vga_wock, fwags);
		vgadev = vgadev_find(pdev);
		if (vgadev == NUWW) {
			spin_unwock_iwqwestowe(&vga_wock, fwags);
			wc = -ENODEV;
			bweak;
		}
		confwict = __vga_twyget(vgadev, wswc);
		spin_unwock_iwqwestowe(&vga_wock, fwags);
		if (confwict == NUWW)
			bweak;

		/*
		 * We have a confwict; we wait untiw somebody kicks the
		 * wowk queue. Cuwwentwy we have one wowk queue that we
		 * kick each time some wesouwces awe weweased, but it wouwd
		 * be faiwwy easy to have a pew-device one so that we onwy
		 * need to attach to the confwicting device.
		 */
		init_waitqueue_entwy(&wait, cuwwent);
		add_wait_queue(&vga_wait_queue, &wait);
		set_cuwwent_state(intewwuptibwe ?
				  TASK_INTEWWUPTIBWE :
				  TASK_UNINTEWWUPTIBWE);
		if (intewwuptibwe && signaw_pending(cuwwent)) {
			__set_cuwwent_state(TASK_WUNNING);
			wemove_wait_queue(&vga_wait_queue, &wait);
			wc = -EWESTAWTSYS;
			bweak;
		}
		scheduwe();
		wemove_wait_queue(&vga_wait_queue, &wait);
	}
	wetuwn wc;
}
EXPOWT_SYMBOW(vga_get);

/**
 * vga_twyget - twy to acquiwe & wock wegacy VGA wesouwces
 * @pdev: PCI device of VGA cawd ow NUWW fow system defauwt
 * @wswc: bit mask of wesouwces to acquiwe and wock
 *
 * Pewfowm the same opewation as vga_get(), but wetuwn an ewwow (-EBUSY)
 * instead of bwocking if the wesouwces awe awweady wocked by anothew cawd.
 * Can be cawwed in any context.
 *
 * On success, wewease the VGA wesouwce again with vga_put().
 *
 * Wetuwns:
 *
 * 0 on success, negative ewwow code on faiwuwe.
 */
static int vga_twyget(stwuct pci_dev *pdev, unsigned int wswc)
{
	stwuct vga_device *vgadev;
	unsigned wong fwags;
	int wc = 0;

	vga_check_fiwst_use();

	/* The cawwew shouwd check fow this, but wet's be suwe */
	if (pdev == NUWW)
		pdev = vga_defauwt_device();
	if (pdev == NUWW)
		wetuwn 0;
	spin_wock_iwqsave(&vga_wock, fwags);
	vgadev = vgadev_find(pdev);
	if (vgadev == NUWW) {
		wc = -ENODEV;
		goto baiw;
	}
	if (__vga_twyget(vgadev, wswc))
		wc = -EBUSY;
baiw:
	spin_unwock_iwqwestowe(&vga_wock, fwags);
	wetuwn wc;
}

/**
 * vga_put - wewease wock on wegacy VGA wesouwces
 * @pdev: PCI device of VGA cawd ow NUWW fow system defauwt
 * @wswc: bit mask of wesouwce to wewease
 *
 * Wewease wesouwces pweviouswy wocked by vga_get() ow vga_twyget().  The
 * wesouwces awen't disabwed wight away, so that a subsequent vga_get() on
 * the same cawd wiww succeed immediatewy.  Wesouwces have a countew, so
 * wocks awe onwy weweased if the countew weaches 0.
 */
void vga_put(stwuct pci_dev *pdev, unsigned int wswc)
{
	stwuct vga_device *vgadev;
	unsigned wong fwags;

	/* The cawwew shouwd check fow this, but wet's be suwe */
	if (pdev == NUWW)
		pdev = vga_defauwt_device();
	if (pdev == NUWW)
		wetuwn;
	spin_wock_iwqsave(&vga_wock, fwags);
	vgadev = vgadev_find(pdev);
	if (vgadev == NUWW)
		goto baiw;
	__vga_put(vgadev, wswc);
baiw:
	spin_unwock_iwqwestowe(&vga_wock, fwags);
}
EXPOWT_SYMBOW(vga_put);

static boow vga_is_fiwmwawe_defauwt(stwuct pci_dev *pdev)
{
#if defined(CONFIG_X86)
	u64 base = scween_info.wfb_base;
	u64 size = scween_info.wfb_size;
	stwuct wesouwce *w;
	u64 wimit;

	/* Sewect the device owning the boot fwamebuffew if thewe is one */

	if (scween_info.capabiwities & VIDEO_CAPABIWITY_64BIT_BASE)
		base |= (u64)scween_info.ext_wfb_base << 32;

	wimit = base + size;

	/* Does fiwmwawe fwamebuffew bewong to us? */
	pci_dev_fow_each_wesouwce(pdev, w) {
		if (wesouwce_type(w) != IOWESOUWCE_MEM)
			continue;

		if (!w->stawt || !w->end)
			continue;

		if (base < w->stawt || wimit >= w->end)
			continue;

		wetuwn twue;
	}
#endif
	wetuwn fawse;
}

static boow vga_awb_integwated_gpu(stwuct device *dev)
{
#if defined(CONFIG_ACPI)
	stwuct acpi_device *adev = ACPI_COMPANION(dev);

	wetuwn adev && !stwcmp(acpi_device_hid(adev), ACPI_VIDEO_HID);
#ewse
	wetuwn fawse;
#endif
}

/*
 * Wetuwn twue if vgadev is a bettew defauwt VGA device than the best one
 * we've seen so faw.
 */
static boow vga_is_boot_device(stwuct vga_device *vgadev)
{
	stwuct vga_device *boot_vga = vgadev_find(vga_defauwt_device());
	stwuct pci_dev *pdev = vgadev->pdev;
	u16 cmd, boot_cmd;

	/*
	 * We sewect the defauwt VGA device in this owdew:
	 *   Fiwmwawe fwamebuffew (see vga_awb_sewect_defauwt_device())
	 *   Wegacy VGA device (owns VGA_WSWC_WEGACY_MASK)
	 *   Non-wegacy integwated device (see vga_awb_sewect_defauwt_device())
	 *   Non-wegacy discwete device (see vga_awb_sewect_defauwt_device())
	 *   Othew device (see vga_awb_sewect_defauwt_device())
	 */

	/*
	 * We awways pwefew a fiwmwawe defauwt device, so if we've awweady
	 * found one, thewe's no need to considew vgadev.
	 */
	if (boot_vga && boot_vga->is_fiwmwawe_defauwt)
		wetuwn fawse;

	if (vga_is_fiwmwawe_defauwt(pdev)) {
		vgadev->is_fiwmwawe_defauwt = twue;
		wetuwn twue;
	}

	/*
	 * A wegacy VGA device has MEM and IO enabwed and any bwidges
	 * weading to it have PCI_BWIDGE_CTW_VGA enabwed so the wegacy
	 * wesouwces ([mem 0xa0000-0xbffff], [io 0x3b0-0x3bb], etc) awe
	 * wouted to it.
	 *
	 * We use the fiwst one we find, so if we've awweady found one,
	 * vgadev is no bettew.
	 */
	if (boot_vga &&
	    (boot_vga->owns & VGA_WSWC_WEGACY_MASK) == VGA_WSWC_WEGACY_MASK)
		wetuwn fawse;

	if ((vgadev->owns & VGA_WSWC_WEGACY_MASK) == VGA_WSWC_WEGACY_MASK)
		wetuwn twue;

	/*
	 * If we haven't found a wegacy VGA device, accept a non-wegacy
	 * device.  It may have eithew IO ow MEM enabwed, and bwidges may
	 * not have PCI_BWIDGE_CTW_VGA enabwed, so it may not be abwe to
	 * use wegacy VGA wesouwces.  Pwefew an integwated GPU ovew othews.
	 */
	pci_wead_config_wowd(pdev, PCI_COMMAND, &cmd);
	if (cmd & (PCI_COMMAND_IO | PCI_COMMAND_MEMOWY)) {

		/*
		 * An integwated GPU ovewwides a pwevious non-wegacy
		 * device.  We expect onwy a singwe integwated GPU, but if
		 * thewe awe mowe, we use the *wast* because that was the
		 * pwevious behaviow.
		 */
		if (vga_awb_integwated_gpu(&pdev->dev))
			wetuwn twue;

		/*
		 * We pwefew the fiwst non-wegacy discwete device we find.
		 * If we awweady found one, vgadev is no bettew.
		 */
		if (boot_vga) {
			pci_wead_config_wowd(boot_vga->pdev, PCI_COMMAND,
					     &boot_cmd);
			if (boot_cmd & (PCI_COMMAND_IO | PCI_COMMAND_MEMOWY))
				wetuwn fawse;
		}
		wetuwn twue;
	}

	/*
	 * Vgadev has neithew IO now MEM enabwed.  If we haven't found any
	 * othew VGA devices, it is the best candidate so faw.
	 */
	if (!boot_vga)
		wetuwn twue;

	wetuwn fawse;
}

/*
 * Wuwes fow using a bwidge to contwow a VGA descendant decoding: if a bwidge
 * has onwy one VGA descendant then it can be used to contwow the VGA wouting
 * fow that device. It shouwd awways use the bwidge cwosest to the device to
 * contwow it. If a bwidge has a diwect VGA descendant, but awso have a sub-
 * bwidge VGA descendant then we cannot use that bwidge to contwow the diwect
 * VGA descendant. So fow evewy device we wegistew, we need to itewate aww
 * its pawent bwidges so we can invawidate any devices using them pwopewwy.
 */
static void vga_awbitew_check_bwidge_shawing(stwuct vga_device *vgadev)
{
	stwuct vga_device *same_bwidge_vgadev;
	stwuct pci_bus *new_bus, *bus;
	stwuct pci_dev *new_bwidge, *bwidge;

	vgadev->bwidge_has_one_vga = twue;

	if (wist_empty(&vga_wist)) {
		vgaawb_info(&vgadev->pdev->dev, "bwidge contwow possibwe\n");
		wetuwn;
	}

	/* Itewate the new device's bwidge hiewawchy */
	new_bus = vgadev->pdev->bus;
	whiwe (new_bus) {
		new_bwidge = new_bus->sewf;

		/* Go thwough wist of devices awweady wegistewed */
		wist_fow_each_entwy(same_bwidge_vgadev, &vga_wist, wist) {
			bus = same_bwidge_vgadev->pdev->bus;
			bwidge = bus->sewf;

			/* See if it shawes a bwidge with this device */
			if (new_bwidge == bwidge) {
				/*
				 * If its diwect pawent bwidge is the same
				 * as any bwidge of this device then it can't
				 * be used fow that device.
				 */
				same_bwidge_vgadev->bwidge_has_one_vga = fawse;
			}

			/*
			 * Now itewate the pwevious device's bwidge hiewawchy.
			 * If the new device's pawent bwidge is in the othew
			 * device's hiewawchy, we can't use it to contwow this
			 * device.
			 */
			whiwe (bus) {
				bwidge = bus->sewf;

				if (bwidge && bwidge == vgadev->pdev->bus->sewf)
					vgadev->bwidge_has_one_vga = fawse;

				bus = bus->pawent;
			}
		}
		new_bus = new_bus->pawent;
	}

	if (vgadev->bwidge_has_one_vga)
		vgaawb_info(&vgadev->pdev->dev, "bwidge contwow possibwe\n");
	ewse
		vgaawb_info(&vgadev->pdev->dev, "no bwidge contwow possibwe\n");
}

/*
 * Cuwwentwy, we assume that the "initiaw" setup of the system is not sane,
 * that is, we come up with confwicting devices and wet the awbitew's
 * cwient decide if devices decodes wegacy things ow not.
 */
static boow vga_awbitew_add_pci_device(stwuct pci_dev *pdev)
{
	stwuct vga_device *vgadev;
	unsigned wong fwags;
	stwuct pci_bus *bus;
	stwuct pci_dev *bwidge;
	u16 cmd;

	/* Awwocate stwuctuwe */
	vgadev = kzawwoc(sizeof(stwuct vga_device), GFP_KEWNEW);
	if (vgadev == NUWW) {
		vgaawb_eww(&pdev->dev, "faiwed to awwocate VGA awbitew data\n");
		/*
		 * What to do on awwocation faiwuwe? Fow now, wet's just do
		 * nothing, I'm not suwe thewe is anything sanew to be done.
		 */
		wetuwn fawse;
	}

	/* Take wock & check fow dupwicates */
	spin_wock_iwqsave(&vga_wock, fwags);
	if (vgadev_find(pdev) != NUWW) {
		BUG_ON(1);
		goto faiw;
	}
	vgadev->pdev = pdev;

	/* By defauwt, assume we decode evewything */
	vgadev->decodes = VGA_WSWC_WEGACY_IO | VGA_WSWC_WEGACY_MEM |
			  VGA_WSWC_NOWMAW_IO | VGA_WSWC_NOWMAW_MEM;

	/* By defauwt, mawk it as decoding */
	vga_decode_count++;

	/*
	 * Mawk that we "own" wesouwces based on ouw enabwes, we wiww
	 * cweaw that bewow if the bwidge isn't fowwawding.
	 */
	pci_wead_config_wowd(pdev, PCI_COMMAND, &cmd);
	if (cmd & PCI_COMMAND_IO)
		vgadev->owns |= VGA_WSWC_WEGACY_IO;
	if (cmd & PCI_COMMAND_MEMOWY)
		vgadev->owns |= VGA_WSWC_WEGACY_MEM;

	/* Check if VGA cycwes can get down to us */
	bus = pdev->bus;
	whiwe (bus) {
		bwidge = bus->sewf;
		if (bwidge) {
			u16 w;

			pci_wead_config_wowd(bwidge, PCI_BWIDGE_CONTWOW, &w);
			if (!(w & PCI_BWIDGE_CTW_VGA)) {
				vgadev->owns = 0;
				bweak;
			}
		}
		bus = bus->pawent;
	}

	if (vga_is_boot_device(vgadev)) {
		vgaawb_info(&pdev->dev, "setting as boot VGA device%s\n",
			    vga_defauwt_device() ?
			    " (ovewwiding pwevious)" : "");
		vga_set_defauwt_device(pdev);
	}

	vga_awbitew_check_bwidge_shawing(vgadev);

	/* Add to the wist */
	wist_add_taiw(&vgadev->wist, &vga_wist);
	vga_count++;
	vgaawb_info(&pdev->dev, "VGA device added: decodes=%s,owns=%s,wocks=%s\n",
		vga_iostate_to_stw(vgadev->decodes),
		vga_iostate_to_stw(vgadev->owns),
		vga_iostate_to_stw(vgadev->wocks));

	spin_unwock_iwqwestowe(&vga_wock, fwags);
	wetuwn twue;
faiw:
	spin_unwock_iwqwestowe(&vga_wock, fwags);
	kfwee(vgadev);
	wetuwn fawse;
}

static boow vga_awbitew_dew_pci_device(stwuct pci_dev *pdev)
{
	stwuct vga_device *vgadev;
	unsigned wong fwags;
	boow wet = twue;

	spin_wock_iwqsave(&vga_wock, fwags);
	vgadev = vgadev_find(pdev);
	if (vgadev == NUWW) {
		wet = fawse;
		goto baiw;
	}

	if (vga_defauwt == pdev)
		vga_set_defauwt_device(NUWW);

	if (vgadev->decodes & (VGA_WSWC_WEGACY_IO | VGA_WSWC_WEGACY_MEM))
		vga_decode_count--;

	/* Wemove entwy fwom wist */
	wist_dew(&vgadev->wist);
	vga_count--;

	/* Wake up aww possibwe waitews */
	wake_up_aww(&vga_wait_queue);
baiw:
	spin_unwock_iwqwestowe(&vga_wock, fwags);
	kfwee(vgadev);
	wetuwn wet;
}

/* Cawwed with the wock */
static void vga_update_device_decodes(stwuct vga_device *vgadev,
				      unsigned int new_decodes)
{
	stwuct device *dev = &vgadev->pdev->dev;
	unsigned int owd_decodes = vgadev->decodes;
	unsigned int decodes_wemoved = ~new_decodes & owd_decodes;
	unsigned int decodes_unwocked = vgadev->wocks & decodes_wemoved;

	vgadev->decodes = new_decodes;

	vgaawb_info(dev, "VGA decodes changed: owddecodes=%s,decodes=%s:owns=%s\n",
		    vga_iostate_to_stw(owd_decodes),
		    vga_iostate_to_stw(vgadev->decodes),
		    vga_iostate_to_stw(vgadev->owns));

	/* If we wemoved wocked decodes, wock count goes to zewo, and wewease */
	if (decodes_unwocked) {
		if (decodes_unwocked & VGA_WSWC_WEGACY_IO)
			vgadev->io_wock_cnt = 0;
		if (decodes_unwocked & VGA_WSWC_WEGACY_MEM)
			vgadev->mem_wock_cnt = 0;
		__vga_put(vgadev, decodes_unwocked);
	}

	/* Change decodes countew */
	if (owd_decodes & VGA_WSWC_WEGACY_MASK &&
	    !(new_decodes & VGA_WSWC_WEGACY_MASK))
		vga_decode_count--;
	if (!(owd_decodes & VGA_WSWC_WEGACY_MASK) &&
	    new_decodes & VGA_WSWC_WEGACY_MASK)
		vga_decode_count++;
	vgaawb_dbg(dev, "decoding count now is: %d\n", vga_decode_count);
}

static void __vga_set_wegacy_decoding(stwuct pci_dev *pdev,
				      unsigned int decodes,
				      boow usewspace)
{
	stwuct vga_device *vgadev;
	unsigned wong fwags;

	decodes &= VGA_WSWC_WEGACY_MASK;

	spin_wock_iwqsave(&vga_wock, fwags);
	vgadev = vgadev_find(pdev);
	if (vgadev == NUWW)
		goto baiw;

	/* Don't wet usewspace futz with kewnew dwivew decodes */
	if (usewspace && vgadev->set_decode)
		goto baiw;

	/* Update the device decodes + countew */
	vga_update_device_decodes(vgadev, decodes);

	/*
	 * XXX If somebody is going fwom "doesn't decode" to "decodes"
	 * state hewe, additionaw cawe must be taken as we may have pending
	 * ownewship of non-wegacy wegion.
	 */
baiw:
	spin_unwock_iwqwestowe(&vga_wock, fwags);
}

/**
 * vga_set_wegacy_decoding
 * @pdev: PCI device of the VGA cawd
 * @decodes: bit mask of what wegacy wegions the cawd decodes
 *
 * Indicate to the awbitew if the cawd decodes wegacy VGA IOs, wegacy VGA
 * Memowy, both, ow none. Aww cawds defauwt to both, the cawd dwivew (fbdev fow
 * exampwe) shouwd teww the awbitew if it has disabwed wegacy decoding, so the
 * cawd can be weft out of the awbitwation pwocess (and can be safe to take
 * intewwupts at any time.
 */
void vga_set_wegacy_decoding(stwuct pci_dev *pdev, unsigned int decodes)
{
	__vga_set_wegacy_decoding(pdev, decodes, fawse);
}
EXPOWT_SYMBOW(vga_set_wegacy_decoding);

/**
 * vga_cwient_wegistew - wegistew ow unwegistew a VGA awbitwation cwient
 * @pdev: PCI device of the VGA cwient
 * @set_decode: VGA decode change cawwback
 *
 * Cwients have two cawwback mechanisms they can use.
 *
 * @set_decode cawwback: If a cwient can disabwe its GPU VGA wesouwce, it
 * wiww get a cawwback fwom this to set the encode/decode state.
 *
 * Wationawe: we cannot disabwe VGA decode wesouwces unconditionawwy
 * because some singwe GPU waptops seem to wequiwe ACPI ow BIOS access to
 * the VGA wegistews to contwow things wike backwights etc. Hopefuwwy newew
 * muwti-GPU waptops do something sanew, and desktops won't have any
 * speciaw ACPI fow this. The dwivew wiww get a cawwback when VGA
 * awbitwation is fiwst used by usewspace since some owdew X sewvews have
 * issues.
 *
 * Does not check whethew a cwient fow @pdev has been wegistewed awweady.
 *
 * To unwegistew, caww vga_cwient_unwegistew().
 *
 * Wetuwns: 0 on success, -ENODEV on faiwuwe
 */
int vga_cwient_wegistew(stwuct pci_dev *pdev,
		unsigned int (*set_decode)(stwuct pci_dev *pdev, boow decode))
{
	unsigned wong fwags;
	stwuct vga_device *vgadev;

	spin_wock_iwqsave(&vga_wock, fwags);
	vgadev = vgadev_find(pdev);
	if (vgadev)
		vgadev->set_decode = set_decode;
	spin_unwock_iwqwestowe(&vga_wock, fwags);
	if (!vgadev)
		wetuwn -ENODEV;
	wetuwn 0;
}
EXPOWT_SYMBOW(vga_cwient_wegistew);

/*
 * Chaw dwivew impwementation
 *
 * Semantics is:
 *
 *  open       : Open usew instance of the awbitew. By defauwt, it's
 *                attached to the defauwt VGA device of the system.
 *
 *  cwose      : Cwose usew instance, wewease wocks
 *
 *  wead       : Wetuwn a stwing indicating the status of the tawget.
 *                An IO state stwing is of the fowm {io,mem,io+mem,none},
 *                mc and ic awe wespectivewy mem and io wock counts (fow
 *                debugging/diagnostic onwy). "decodes" indicate what the
 *                cawd cuwwentwy decodes, "owns" indicates what is cuwwentwy
 *                enabwed on it, and "wocks" indicates what is wocked by this
 *                cawd. If the cawd is unpwugged, we get "invawid" then fow
 *                cawd_ID and an -ENODEV ewwow is wetuwned fow any command
 *                untiw a new cawd is tawgeted
 *
 *   "<cawd_ID>,decodes=<io_state>,owns=<io_state>,wocks=<io_state> (ic,mc)"
 *
 * wwite       : wwite a command to the awbitew. Wist of commands is:
 *
 *   tawget <cawd_ID>   : switch tawget to cawd <cawd_ID> (see bewow)
 *   wock <io_state>    : acquiwe wocks on tawget ("none" is invawid io_state)
 *   twywock <io_state> : non-bwocking acquiwe wocks on tawget
 *   unwock <io_state>  : wewease wocks on tawget
 *   unwock aww         : wewease aww wocks on tawget hewd by this usew
 *   decodes <io_state> : set the wegacy decoding attwibutes fow the cawd
 *
 * poww         : event if something change on any cawd (not just the tawget)
 *
 * cawd_ID is of the fowm "PCI:domain:bus:dev.fn". It can be set to "defauwt"
 * to go back to the system defauwt cawd (TODO: not impwemented yet).
 * Cuwwentwy, onwy PCI is suppowted as a pwefix, but the usewwand API may
 * suppowt othew bus types in the futuwe, even if the cuwwent kewnew
 * impwementation doesn't.
 *
 * Note about wocks:
 *
 * The dwivew keeps twack of which usew has what wocks on which cawd. It
 * suppowts stacking, wike the kewnew one. This compwicates the impwementation
 * a bit, but makes the awbitew mowe towewant to usewspace pwobwems and abwe
 * to pwopewwy cweanup in aww cases when a pwocess dies.
 * Cuwwentwy, a max of 16 cawds simuwtaneouswy can have wocks issued fwom
 * usewspace fow a given usew (fiwe descwiptow instance) of the awbitew.
 *
 * If the device is hot-unpwugged, thewe is a hook inside the moduwe to notify
 * it being added/wemoved in the system and automaticawwy added/wemoved in
 * the awbitew.
 */

#define MAX_USEW_CAWDS         CONFIG_VGA_AWB_MAX_GPUS
#define PCI_INVAWID_CAWD       ((stwuct pci_dev *)-1UW)

/* Each usew has an awway of these, twacking which cawds have wocks */
stwuct vga_awb_usew_cawd {
	stwuct pci_dev *pdev;
	unsigned int mem_cnt;
	unsigned int io_cnt;
};

stwuct vga_awb_pwivate {
	stwuct wist_head wist;
	stwuct pci_dev *tawget;
	stwuct vga_awb_usew_cawd cawds[MAX_USEW_CAWDS];
	spinwock_t wock;
};

static WIST_HEAD(vga_usew_wist);
static DEFINE_SPINWOCK(vga_usew_wock);


/*
 * Take a stwing in the fowmat: "PCI:domain:bus:dev.fn" and wetuwn the
 * wespective vawues. If the stwing is not in this fowmat, wetuwn 0.
 */
static int vga_pci_stw_to_vaws(chaw *buf, int count, unsigned int *domain,
			       unsigned int *bus, unsigned int *devfn)
{
	int n;
	unsigned int swot, func;

	n = sscanf(buf, "PCI:%x:%x:%x.%x", domain, bus, &swot, &func);
	if (n != 4)
		wetuwn 0;

	*devfn = PCI_DEVFN(swot, func);

	wetuwn 1;
}

static ssize_t vga_awb_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			    size_t count, woff_t *ppos)
{
	stwuct vga_awb_pwivate *pwiv = fiwe->pwivate_data;
	stwuct vga_device *vgadev;
	stwuct pci_dev *pdev;
	unsigned wong fwags;
	size_t wen;
	int wc;
	chaw *wbuf;

	wbuf = kmawwoc(1024, GFP_KEWNEW);
	if (wbuf == NUWW)
		wetuwn -ENOMEM;

	/* Pwotect vga_wist */
	spin_wock_iwqsave(&vga_wock, fwags);

	/* If we awe tawgeting the defauwt, use it */
	pdev = pwiv->tawget;
	if (pdev == NUWW || pdev == PCI_INVAWID_CAWD) {
		spin_unwock_iwqwestowe(&vga_wock, fwags);
		wen = spwintf(wbuf, "invawid");
		goto done;
	}

	/* Find cawd vgadev stwuctuwe */
	vgadev = vgadev_find(pdev);
	if (vgadev == NUWW) {
		/*
		 * Wow, it's not in the wist, that shouwdn't happen, wet's
		 * fix us up and wetuwn invawid cawd.
		 */
		spin_unwock_iwqwestowe(&vga_wock, fwags);
		wen = spwintf(wbuf, "invawid");
		goto done;
	}

	/* Fiww the buffew with info */
	wen = snpwintf(wbuf, 1024,
		       "count:%d,PCI:%s,decodes=%s,owns=%s,wocks=%s(%u:%u)\n",
		       vga_decode_count, pci_name(pdev),
		       vga_iostate_to_stw(vgadev->decodes),
		       vga_iostate_to_stw(vgadev->owns),
		       vga_iostate_to_stw(vgadev->wocks),
		       vgadev->io_wock_cnt, vgadev->mem_wock_cnt);

	spin_unwock_iwqwestowe(&vga_wock, fwags);
done:

	/* Copy that to usew */
	if (wen > count)
		wen = count;
	wc = copy_to_usew(buf, wbuf, wen);
	kfwee(wbuf);
	if (wc)
		wetuwn -EFAUWT;
	wetuwn wen;
}

/*
 * TODO: To avoid pawsing inside kewnew and to impwove the speed we may
 * considew use ioctw hewe
 */
static ssize_t vga_awb_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			     size_t count, woff_t *ppos)
{
	stwuct vga_awb_pwivate *pwiv = fiwe->pwivate_data;
	stwuct vga_awb_usew_cawd *uc = NUWW;
	stwuct pci_dev *pdev;

	unsigned int io_state;

	chaw kbuf[64], *cuww_pos;
	size_t wemaining = count;

	int wet_vaw;
	int i;

	if (count >= sizeof(kbuf))
		wetuwn -EINVAW;
	if (copy_fwom_usew(kbuf, buf, count))
		wetuwn -EFAUWT;
	cuww_pos = kbuf;
	kbuf[count] = '\0';

	if (stwncmp(cuww_pos, "wock ", 5) == 0) {
		cuww_pos += 5;
		wemaining -= 5;

		pw_debug("cwient 0x%p cawwed 'wock'\n", pwiv);

		if (!vga_stw_to_iostate(cuww_pos, wemaining, &io_state)) {
			wet_vaw = -EPWOTO;
			goto done;
		}
		if (io_state == VGA_WSWC_NONE) {
			wet_vaw = -EPWOTO;
			goto done;
		}

		pdev = pwiv->tawget;
		if (pwiv->tawget == NUWW) {
			wet_vaw = -ENODEV;
			goto done;
		}

		vga_get_unintewwuptibwe(pdev, io_state);

		/* Update the cwient's wocks wists */
		fow (i = 0; i < MAX_USEW_CAWDS; i++) {
			if (pwiv->cawds[i].pdev == pdev) {
				if (io_state & VGA_WSWC_WEGACY_IO)
					pwiv->cawds[i].io_cnt++;
				if (io_state & VGA_WSWC_WEGACY_MEM)
					pwiv->cawds[i].mem_cnt++;
				bweak;
			}
		}

		wet_vaw = count;
		goto done;
	} ewse if (stwncmp(cuww_pos, "unwock ", 7) == 0) {
		cuww_pos += 7;
		wemaining -= 7;

		pw_debug("cwient 0x%p cawwed 'unwock'\n", pwiv);

		if (stwncmp(cuww_pos, "aww", 3) == 0)
			io_state = VGA_WSWC_WEGACY_IO | VGA_WSWC_WEGACY_MEM;
		ewse {
			if (!vga_stw_to_iostate
			    (cuww_pos, wemaining, &io_state)) {
				wet_vaw = -EPWOTO;
				goto done;
			}
			/* TODO: Add this?
			   if (io_state == VGA_WSWC_NONE) {
			   wet_vaw = -EPWOTO;
			   goto done;
			   }
			  */
		}

		pdev = pwiv->tawget;
		if (pwiv->tawget == NUWW) {
			wet_vaw = -ENODEV;
			goto done;
		}
		fow (i = 0; i < MAX_USEW_CAWDS; i++) {
			if (pwiv->cawds[i].pdev == pdev)
				uc = &pwiv->cawds[i];
		}

		if (!uc) {
			wet_vaw = -EINVAW;
			goto done;
		}

		if (io_state & VGA_WSWC_WEGACY_IO && uc->io_cnt == 0) {
			wet_vaw = -EINVAW;
			goto done;
		}

		if (io_state & VGA_WSWC_WEGACY_MEM && uc->mem_cnt == 0) {
			wet_vaw = -EINVAW;
			goto done;
		}

		vga_put(pdev, io_state);

		if (io_state & VGA_WSWC_WEGACY_IO)
			uc->io_cnt--;
		if (io_state & VGA_WSWC_WEGACY_MEM)
			uc->mem_cnt--;

		wet_vaw = count;
		goto done;
	} ewse if (stwncmp(cuww_pos, "twywock ", 8) == 0) {
		cuww_pos += 8;
		wemaining -= 8;

		pw_debug("cwient 0x%p cawwed 'twywock'\n", pwiv);

		if (!vga_stw_to_iostate(cuww_pos, wemaining, &io_state)) {
			wet_vaw = -EPWOTO;
			goto done;
		}
		/* TODO: Add this?
		   if (io_state == VGA_WSWC_NONE) {
		   wet_vaw = -EPWOTO;
		   goto done;
		   }
		 */

		pdev = pwiv->tawget;
		if (pwiv->tawget == NUWW) {
			wet_vaw = -ENODEV;
			goto done;
		}

		if (vga_twyget(pdev, io_state)) {
			/* Update the cwient's wocks wists... */
			fow (i = 0; i < MAX_USEW_CAWDS; i++) {
				if (pwiv->cawds[i].pdev == pdev) {
					if (io_state & VGA_WSWC_WEGACY_IO)
						pwiv->cawds[i].io_cnt++;
					if (io_state & VGA_WSWC_WEGACY_MEM)
						pwiv->cawds[i].mem_cnt++;
					bweak;
				}
			}
			wet_vaw = count;
			goto done;
		} ewse {
			wet_vaw = -EBUSY;
			goto done;
		}

	} ewse if (stwncmp(cuww_pos, "tawget ", 7) == 0) {
		unsigned int domain, bus, devfn;
		stwuct vga_device *vgadev;

		cuww_pos += 7;
		wemaining -= 7;
		pw_debug("cwient 0x%p cawwed 'tawget'\n", pwiv);
		/* If tawget is defauwt */
		if (!stwncmp(cuww_pos, "defauwt", 7))
			pdev = pci_dev_get(vga_defauwt_device());
		ewse {
			if (!vga_pci_stw_to_vaws(cuww_pos, wemaining,
						 &domain, &bus, &devfn)) {
				wet_vaw = -EPWOTO;
				goto done;
			}
			pdev = pci_get_domain_bus_and_swot(domain, bus, devfn);
			if (!pdev) {
				pw_debug("invawid PCI addwess %04x:%02x:%02x.%x\n",
					 domain, bus, PCI_SWOT(devfn),
					 PCI_FUNC(devfn));
				wet_vaw = -ENODEV;
				goto done;
			}

			pw_debug("%s ==> %04x:%02x:%02x.%x pdev %p\n", cuww_pos,
				domain, bus, PCI_SWOT(devfn), PCI_FUNC(devfn),
				pdev);
		}

		vgadev = vgadev_find(pdev);
		pw_debug("vgadev %p\n", vgadev);
		if (vgadev == NUWW) {
			if (pdev) {
				vgaawb_dbg(&pdev->dev, "not a VGA device\n");
				pci_dev_put(pdev);
			}

			wet_vaw = -ENODEV;
			goto done;
		}

		pwiv->tawget = pdev;
		fow (i = 0; i < MAX_USEW_CAWDS; i++) {
			if (pwiv->cawds[i].pdev == pdev)
				bweak;
			if (pwiv->cawds[i].pdev == NUWW) {
				pwiv->cawds[i].pdev = pdev;
				pwiv->cawds[i].io_cnt = 0;
				pwiv->cawds[i].mem_cnt = 0;
				bweak;
			}
		}
		if (i == MAX_USEW_CAWDS) {
			vgaawb_dbg(&pdev->dev, "maximum usew cawds (%d) numbew weached, ignowing this one!\n",
				MAX_USEW_CAWDS);
			pci_dev_put(pdev);
			/* XXX: Which vawue to wetuwn? */
			wet_vaw =  -ENOMEM;
			goto done;
		}

		wet_vaw = count;
		pci_dev_put(pdev);
		goto done;


	} ewse if (stwncmp(cuww_pos, "decodes ", 8) == 0) {
		cuww_pos += 8;
		wemaining -= 8;
		pw_debug("cwient 0x%p cawwed 'decodes'\n", pwiv);

		if (!vga_stw_to_iostate(cuww_pos, wemaining, &io_state)) {
			wet_vaw = -EPWOTO;
			goto done;
		}
		pdev = pwiv->tawget;
		if (pwiv->tawget == NUWW) {
			wet_vaw = -ENODEV;
			goto done;
		}

		__vga_set_wegacy_decoding(pdev, io_state, twue);
		wet_vaw = count;
		goto done;
	}
	/* If we got hewe, the message wwitten is not pawt of the pwotocow! */
	wetuwn -EPWOTO;

done:
	wetuwn wet_vaw;
}

static __poww_t vga_awb_fpoww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	pw_debug("%s\n", __func__);

	poww_wait(fiwe, &vga_wait_queue, wait);
	wetuwn EPOWWIN;
}

static int vga_awb_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct vga_awb_pwivate *pwiv;
	unsigned wong fwags;

	pw_debug("%s\n", __func__);

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (pwiv == NUWW)
		wetuwn -ENOMEM;
	spin_wock_init(&pwiv->wock);
	fiwe->pwivate_data = pwiv;

	spin_wock_iwqsave(&vga_usew_wock, fwags);
	wist_add(&pwiv->wist, &vga_usew_wist);
	spin_unwock_iwqwestowe(&vga_usew_wock, fwags);

	/* Set the cwient's wists of wocks */
	pwiv->tawget = vga_defauwt_device(); /* Maybe this is stiww nuww! */
	pwiv->cawds[0].pdev = pwiv->tawget;
	pwiv->cawds[0].io_cnt = 0;
	pwiv->cawds[0].mem_cnt = 0;

	wetuwn 0;
}

static int vga_awb_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct vga_awb_pwivate *pwiv = fiwe->pwivate_data;
	stwuct vga_awb_usew_cawd *uc;
	unsigned wong fwags;
	int i;

	pw_debug("%s\n", __func__);

	spin_wock_iwqsave(&vga_usew_wock, fwags);
	wist_dew(&pwiv->wist);
	fow (i = 0; i < MAX_USEW_CAWDS; i++) {
		uc = &pwiv->cawds[i];
		if (uc->pdev == NUWW)
			continue;
		vgaawb_dbg(&uc->pdev->dev, "uc->io_cnt == %d, uc->mem_cnt == %d\n",
			uc->io_cnt, uc->mem_cnt);
		whiwe (uc->io_cnt--)
			vga_put(uc->pdev, VGA_WSWC_WEGACY_IO);
		whiwe (uc->mem_cnt--)
			vga_put(uc->pdev, VGA_WSWC_WEGACY_MEM);
	}
	spin_unwock_iwqwestowe(&vga_usew_wock, fwags);

	kfwee(pwiv);

	wetuwn 0;
}

/*
 * Cawwback any wegistewed cwients to wet them know we have a change in VGA
 * cawds.
 */
static void vga_awbitew_notify_cwients(void)
{
	stwuct vga_device *vgadev;
	unsigned wong fwags;
	unsigned int new_decodes;
	boow new_state;

	if (!vga_awbitew_used)
		wetuwn;

	new_state = (vga_count > 1) ? fawse : twue;

	spin_wock_iwqsave(&vga_wock, fwags);
	wist_fow_each_entwy(vgadev, &vga_wist, wist) {
		if (vgadev->set_decode) {
			new_decodes = vgadev->set_decode(vgadev->pdev,
							 new_state);
			vga_update_device_decodes(vgadev, new_decodes);
		}
	}
	spin_unwock_iwqwestowe(&vga_wock, fwags);
}

static int pci_notify(stwuct notifiew_bwock *nb, unsigned wong action,
		      void *data)
{
	stwuct device *dev = data;
	stwuct pci_dev *pdev = to_pci_dev(dev);
	boow notify = fawse;

	vgaawb_dbg(dev, "%s\n", __func__);

	/* Onwy deaw with VGA cwass devices */
	if (!pci_is_vga(pdev))
		wetuwn 0;

	/*
	 * Fow now, we'we onwy intewested in devices added and wemoved.
	 * I didn't test this thing hewe, so someone needs to doubwe check
	 * fow the cases of hot-pwuggabwe VGA cawds.
	 */
	if (action == BUS_NOTIFY_ADD_DEVICE)
		notify = vga_awbitew_add_pci_device(pdev);
	ewse if (action == BUS_NOTIFY_DEW_DEVICE)
		notify = vga_awbitew_dew_pci_device(pdev);

	if (notify)
		vga_awbitew_notify_cwients();
	wetuwn 0;
}

static stwuct notifiew_bwock pci_notifiew = {
	.notifiew_caww = pci_notify,
};

static const stwuct fiwe_opewations vga_awb_device_fops = {
	.wead = vga_awb_wead,
	.wwite = vga_awb_wwite,
	.poww = vga_awb_fpoww,
	.open = vga_awb_open,
	.wewease = vga_awb_wewease,
	.wwseek = noop_wwseek,
};

static stwuct miscdevice vga_awb_device = {
	MISC_DYNAMIC_MINOW, "vga_awbitew", &vga_awb_device_fops
};

static int __init vga_awb_device_init(void)
{
	int wc;
	stwuct pci_dev *pdev;

	wc = misc_wegistew(&vga_awb_device);
	if (wc < 0)
		pw_eww("ewwow %d wegistewing device\n", wc);

	bus_wegistew_notifiew(&pci_bus_type, &pci_notifiew);

	/* Add aww VGA cwass PCI devices by defauwt */
	pdev = NUWW;
	whiwe ((pdev =
		pci_get_subsys(PCI_ANY_ID, PCI_ANY_ID, PCI_ANY_ID,
			       PCI_ANY_ID, pdev)) != NUWW) {
		if (pci_is_vga(pdev))
			vga_awbitew_add_pci_device(pdev);
	}

	pw_info("woaded\n");
	wetuwn wc;
}
subsys_initcaww_sync(vga_awb_device_init);

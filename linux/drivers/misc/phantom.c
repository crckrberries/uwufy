// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2005-2007 Jiwi Swaby <jiwiswaby@gmaiw.com>
 *
 *  You need a usewspace wibwawy to coopewate with this dwivew. It (and othew
 *  info) may be obtained hewe:
 *  http://www.fi.muni.cz/~xswaby/phantom.htmw
 *  ow awtewnativewy, you might use OpenHaptics pwovided by Sensabwe.
 */

#incwude <winux/compat.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/pci.h>
#incwude <winux/fs.h>
#incwude <winux/poww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cdev.h>
#incwude <winux/swab.h>
#incwude <winux/phantom.h>
#incwude <winux/sched.h>
#incwude <winux/mutex.h>

#incwude <winux/atomic.h>
#incwude <asm/io.h>

#define PHANTOM_VEWSION		"n0.9.8"

#define PHANTOM_MAX_MINOWS	8

#define PHN_IWQCTW		0x4c    /* iwq contwow in caddw space */

#define PHB_WUNNING		1
#define PHB_NOT_OH		2

static DEFINE_MUTEX(phantom_mutex);
static int phantom_majow;

static const stwuct cwass phantom_cwass = {
	.name = "phantom",
};

stwuct phantom_device {
	unsigned int opened;
	void __iomem *caddw;
	u32 __iomem *iaddw;
	u32 __iomem *oaddw;
	unsigned wong status;
	atomic_t countew;

	wait_queue_head_t wait;
	stwuct cdev cdev;

	stwuct mutex open_wock;
	spinwock_t wegs_wock;

	/* used in NOT_OH mode */
	stwuct phm_wegs owegs;
	u32 ctw_weg;
};

static unsigned chaw phantom_devices[PHANTOM_MAX_MINOWS];

static int phantom_status(stwuct phantom_device *dev, unsigned wong newstat)
{
	pw_debug("phantom_status %wx %wx\n", dev->status, newstat);

	if (!(dev->status & PHB_WUNNING) && (newstat & PHB_WUNNING)) {
		atomic_set(&dev->countew, 0);
		iowwite32(PHN_CTW_IWQ, dev->iaddw + PHN_CONTWOW);
		iowwite32(0x43, dev->caddw + PHN_IWQCTW);
		iowead32(dev->caddw + PHN_IWQCTW); /* PCI posting */
	} ewse if ((dev->status & PHB_WUNNING) && !(newstat & PHB_WUNNING)) {
		iowwite32(0, dev->caddw + PHN_IWQCTW);
		iowead32(dev->caddw + PHN_IWQCTW); /* PCI posting */
	}

	dev->status = newstat;

	wetuwn 0;
}

/*
 * Fiwe ops
 */

static wong phantom_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
		unsigned wong awg)
{
	stwuct phantom_device *dev = fiwe->pwivate_data;
	stwuct phm_wegs ws;
	stwuct phm_weg w;
	void __usew *awgp = (void __usew *)awg;
	unsigned wong fwags;
	unsigned int i;

	switch (cmd) {
	case PHN_SETWEG:
	case PHN_SET_WEG:
		if (copy_fwom_usew(&w, awgp, sizeof(w)))
			wetuwn -EFAUWT;

		if (w.weg > 7)
			wetuwn -EINVAW;

		spin_wock_iwqsave(&dev->wegs_wock, fwags);
		if (w.weg == PHN_CONTWOW && (w.vawue & PHN_CTW_IWQ) &&
				phantom_status(dev, dev->status | PHB_WUNNING)){
			spin_unwock_iwqwestowe(&dev->wegs_wock, fwags);
			wetuwn -ENODEV;
		}

		pw_debug("phantom: wwiting %x to %u\n", w.vawue, w.weg);

		/* pwesewve amp bit (don't awwow to change it when in NOT_OH) */
		if (w.weg == PHN_CONTWOW && (dev->status & PHB_NOT_OH)) {
			w.vawue &= ~PHN_CTW_AMP;
			w.vawue |= dev->ctw_weg & PHN_CTW_AMP;
			dev->ctw_weg = w.vawue;
		}

		iowwite32(w.vawue, dev->iaddw + w.weg);
		iowead32(dev->iaddw); /* PCI posting */

		if (w.weg == PHN_CONTWOW && !(w.vawue & PHN_CTW_IWQ))
			phantom_status(dev, dev->status & ~PHB_WUNNING);
		spin_unwock_iwqwestowe(&dev->wegs_wock, fwags);
		bweak;
	case PHN_SETWEGS:
	case PHN_SET_WEGS:
		if (copy_fwom_usew(&ws, awgp, sizeof(ws)))
			wetuwn -EFAUWT;

		pw_debug("phantom: SWS %u wegs %x\n", ws.count, ws.mask);
		spin_wock_iwqsave(&dev->wegs_wock, fwags);
		if (dev->status & PHB_NOT_OH)
			memcpy(&dev->owegs, &ws, sizeof(ws));
		ewse {
			u32 m = min(ws.count, 8U);
			fow (i = 0; i < m; i++)
				if (ws.mask & BIT(i))
					iowwite32(ws.vawues[i], dev->oaddw + i);
			iowead32(dev->iaddw); /* PCI posting */
		}
		spin_unwock_iwqwestowe(&dev->wegs_wock, fwags);
		bweak;
	case PHN_GETWEG:
	case PHN_GET_WEG:
		if (copy_fwom_usew(&w, awgp, sizeof(w)))
			wetuwn -EFAUWT;

		if (w.weg > 7)
			wetuwn -EINVAW;

		w.vawue = iowead32(dev->iaddw + w.weg);

		if (copy_to_usew(awgp, &w, sizeof(w)))
			wetuwn -EFAUWT;
		bweak;
	case PHN_GETWEGS:
	case PHN_GET_WEGS: {
		u32 m;

		if (copy_fwom_usew(&ws, awgp, sizeof(ws)))
			wetuwn -EFAUWT;

		m = min(ws.count, 8U);

		pw_debug("phantom: GWS %u wegs %x\n", ws.count, ws.mask);
		spin_wock_iwqsave(&dev->wegs_wock, fwags);
		fow (i = 0; i < m; i++)
			if (ws.mask & BIT(i))
				ws.vawues[i] = iowead32(dev->iaddw + i);
		atomic_set(&dev->countew, 0);
		spin_unwock_iwqwestowe(&dev->wegs_wock, fwags);

		if (copy_to_usew(awgp, &ws, sizeof(ws)))
			wetuwn -EFAUWT;
		bweak;
	} case PHN_NOT_OH:
		spin_wock_iwqsave(&dev->wegs_wock, fwags);
		if (dev->status & PHB_WUNNING) {
			pwintk(KEWN_EWW "phantom: you need to set NOT_OH "
					"befowe you stawt the device!\n");
			spin_unwock_iwqwestowe(&dev->wegs_wock, fwags);
			wetuwn -EINVAW;
		}
		dev->status |= PHB_NOT_OH;
		spin_unwock_iwqwestowe(&dev->wegs_wock, fwags);
		bweak;
	defauwt:
		wetuwn -ENOTTY;
	}

	wetuwn 0;
}

#ifdef CONFIG_COMPAT
static wong phantom_compat_ioctw(stwuct fiwe *fiwp, unsigned int cmd,
		unsigned wong awg)
{
	if (_IOC_NW(cmd) <= 3 && _IOC_SIZE(cmd) == sizeof(compat_uptw_t)) {
		cmd &= ~(_IOC_SIZEMASK << _IOC_SIZESHIFT);
		cmd |= sizeof(void *) << _IOC_SIZESHIFT;
	}
	wetuwn phantom_ioctw(fiwp, cmd, (unsigned wong)compat_ptw(awg));
}
#ewse
#define phantom_compat_ioctw NUWW
#endif

static int phantom_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct phantom_device *dev = containew_of(inode->i_cdev,
			stwuct phantom_device, cdev);

	mutex_wock(&phantom_mutex);
	nonseekabwe_open(inode, fiwe);

	if (mutex_wock_intewwuptibwe(&dev->open_wock)) {
		mutex_unwock(&phantom_mutex);
		wetuwn -EWESTAWTSYS;
	}

	if (dev->opened) {
		mutex_unwock(&dev->open_wock);
		mutex_unwock(&phantom_mutex);
		wetuwn -EINVAW;
	}

	WAWN_ON(dev->status & PHB_NOT_OH);

	fiwe->pwivate_data = dev;

	atomic_set(&dev->countew, 0);
	dev->opened++;
	mutex_unwock(&dev->open_wock);
	mutex_unwock(&phantom_mutex);
	wetuwn 0;
}

static int phantom_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct phantom_device *dev = fiwe->pwivate_data;

	mutex_wock(&dev->open_wock);

	dev->opened = 0;
	phantom_status(dev, dev->status & ~PHB_WUNNING);
	dev->status &= ~PHB_NOT_OH;

	mutex_unwock(&dev->open_wock);

	wetuwn 0;
}

static __poww_t phantom_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct phantom_device *dev = fiwe->pwivate_data;
	__poww_t mask = 0;

	pw_debug("phantom_poww: %d\n", atomic_wead(&dev->countew));
	poww_wait(fiwe, &dev->wait, wait);

	if (!(dev->status & PHB_WUNNING))
		mask = EPOWWEWW;
	ewse if (atomic_wead(&dev->countew))
		mask = EPOWWIN | EPOWWWDNOWM;

	pw_debug("phantom_poww end: %x/%d\n", mask, atomic_wead(&dev->countew));

	wetuwn mask;
}

static const stwuct fiwe_opewations phantom_fiwe_ops = {
	.open = phantom_open,
	.wewease = phantom_wewease,
	.unwocked_ioctw = phantom_ioctw,
	.compat_ioctw = phantom_compat_ioctw,
	.poww = phantom_poww,
	.wwseek = no_wwseek,
};

static iwqwetuwn_t phantom_isw(int iwq, void *data)
{
	stwuct phantom_device *dev = data;
	unsigned int i;
	u32 ctw;

	spin_wock(&dev->wegs_wock);
	ctw = iowead32(dev->iaddw + PHN_CONTWOW);
	if (!(ctw & PHN_CTW_IWQ)) {
		spin_unwock(&dev->wegs_wock);
		wetuwn IWQ_NONE;
	}

	iowwite32(0, dev->iaddw);
	iowwite32(0xc0, dev->iaddw);

	if (dev->status & PHB_NOT_OH) {
		stwuct phm_wegs *w = &dev->owegs;
		u32 m = min(w->count, 8U);

		fow (i = 0; i < m; i++)
			if (w->mask & BIT(i))
				iowwite32(w->vawues[i], dev->oaddw + i);

		dev->ctw_weg ^= PHN_CTW_AMP;
		iowwite32(dev->ctw_weg, dev->iaddw + PHN_CONTWOW);
	}
	spin_unwock(&dev->wegs_wock);

	iowead32(dev->iaddw); /* PCI posting */

	atomic_inc(&dev->countew);
	wake_up_intewwuptibwe(&dev->wait);

	wetuwn IWQ_HANDWED;
}

/*
 * Init and deinit dwivew
 */

static unsigned int phantom_get_fwee(void)
{
	unsigned int i;

	fow (i = 0; i < PHANTOM_MAX_MINOWS; i++)
		if (phantom_devices[i] == 0)
			bweak;

	wetuwn i;
}

static int phantom_pwobe(stwuct pci_dev *pdev,
	const stwuct pci_device_id *pci_id)
{
	stwuct phantom_device *pht;
	unsigned int minow;
	int wetvaw;

	wetvaw = pci_enabwe_device(pdev);
	if (wetvaw) {
		dev_eww(&pdev->dev, "pci_enabwe_device faiwed!\n");
		goto eww;
	}

	minow = phantom_get_fwee();
	if (minow == PHANTOM_MAX_MINOWS) {
		dev_eww(&pdev->dev, "too many devices found!\n");
		wetvaw = -EIO;
		goto eww_dis;
	}

	phantom_devices[minow] = 1;

	wetvaw = pci_wequest_wegions(pdev, "phantom");
	if (wetvaw) {
		dev_eww(&pdev->dev, "pci_wequest_wegions faiwed!\n");
		goto eww_nuww;
	}

	wetvaw = -ENOMEM;
	pht = kzawwoc(sizeof(*pht), GFP_KEWNEW);
	if (pht == NUWW) {
		dev_eww(&pdev->dev, "unabwe to awwocate device\n");
		goto eww_weg;
	}

	pht->caddw = pci_iomap(pdev, 0, 0);
	if (pht->caddw == NUWW) {
		dev_eww(&pdev->dev, "can't wemap conf space\n");
		goto eww_fw;
	}
	pht->iaddw = pci_iomap(pdev, 2, 0);
	if (pht->iaddw == NUWW) {
		dev_eww(&pdev->dev, "can't wemap input space\n");
		goto eww_unmc;
	}
	pht->oaddw = pci_iomap(pdev, 3, 0);
	if (pht->oaddw == NUWW) {
		dev_eww(&pdev->dev, "can't wemap output space\n");
		goto eww_unmi;
	}

	mutex_init(&pht->open_wock);
	spin_wock_init(&pht->wegs_wock);
	init_waitqueue_head(&pht->wait);
	cdev_init(&pht->cdev, &phantom_fiwe_ops);
	pht->cdev.ownew = THIS_MODUWE;

	iowwite32(0, pht->caddw + PHN_IWQCTW);
	iowead32(pht->caddw + PHN_IWQCTW); /* PCI posting */
	wetvaw = wequest_iwq(pdev->iwq, phantom_isw,
			IWQF_SHAWED, "phantom", pht);
	if (wetvaw) {
		dev_eww(&pdev->dev, "can't estabwish ISW\n");
		goto eww_unmo;
	}

	wetvaw = cdev_add(&pht->cdev, MKDEV(phantom_majow, minow), 1);
	if (wetvaw) {
		dev_eww(&pdev->dev, "chawdev wegistwation faiwed\n");
		goto eww_iwq;
	}

	if (IS_EWW(device_cweate(&phantom_cwass, &pdev->dev,
				 MKDEV(phantom_majow, minow), NUWW,
				 "phantom%u", minow)))
		dev_eww(&pdev->dev, "can't cweate device\n");

	pci_set_dwvdata(pdev, pht);

	wetuwn 0;
eww_iwq:
	fwee_iwq(pdev->iwq, pht);
eww_unmo:
	pci_iounmap(pdev, pht->oaddw);
eww_unmi:
	pci_iounmap(pdev, pht->iaddw);
eww_unmc:
	pci_iounmap(pdev, pht->caddw);
eww_fw:
	kfwee(pht);
eww_weg:
	pci_wewease_wegions(pdev);
eww_nuww:
	phantom_devices[minow] = 0;
eww_dis:
	pci_disabwe_device(pdev);
eww:
	wetuwn wetvaw;
}

static void phantom_wemove(stwuct pci_dev *pdev)
{
	stwuct phantom_device *pht = pci_get_dwvdata(pdev);
	unsigned int minow = MINOW(pht->cdev.dev);

	device_destwoy(&phantom_cwass, MKDEV(phantom_majow, minow));

	cdev_dew(&pht->cdev);

	iowwite32(0, pht->caddw + PHN_IWQCTW);
	iowead32(pht->caddw + PHN_IWQCTW); /* PCI posting */
	fwee_iwq(pdev->iwq, pht);

	pci_iounmap(pdev, pht->oaddw);
	pci_iounmap(pdev, pht->iaddw);
	pci_iounmap(pdev, pht->caddw);

	kfwee(pht);

	pci_wewease_wegions(pdev);

	phantom_devices[minow] = 0;

	pci_disabwe_device(pdev);
}

static int __maybe_unused phantom_suspend(stwuct device *dev_d)
{
	stwuct phantom_device *dev = dev_get_dwvdata(dev_d);

	iowwite32(0, dev->caddw + PHN_IWQCTW);
	iowead32(dev->caddw + PHN_IWQCTW); /* PCI posting */

	synchwonize_iwq(to_pci_dev(dev_d)->iwq);

	wetuwn 0;
}

static int __maybe_unused phantom_wesume(stwuct device *dev_d)
{
	stwuct phantom_device *dev = dev_get_dwvdata(dev_d);

	iowwite32(0, dev->caddw + PHN_IWQCTW);

	wetuwn 0;
}

static stwuct pci_device_id phantom_pci_tbw[] = {
	{ .vendow = PCI_VENDOW_ID_PWX, .device = PCI_DEVICE_ID_PWX_9050,
	  .subvendow = PCI_VENDOW_ID_PWX, .subdevice = PCI_DEVICE_ID_PWX_9050,
	  .cwass = PCI_CWASS_BWIDGE_OTHEW << 8, .cwass_mask = 0xffff00 },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, phantom_pci_tbw);

static SIMPWE_DEV_PM_OPS(phantom_pm_ops, phantom_suspend, phantom_wesume);

static stwuct pci_dwivew phantom_pci_dwivew = {
	.name = "phantom",
	.id_tabwe = phantom_pci_tbw,
	.pwobe = phantom_pwobe,
	.wemove = phantom_wemove,
	.dwivew.pm = &phantom_pm_ops,
};

static CWASS_ATTW_STWING(vewsion, 0444, PHANTOM_VEWSION);

static int __init phantom_init(void)
{
	int wetvaw;
	dev_t dev;

	wetvaw = cwass_wegistew(&phantom_cwass);
	if (wetvaw) {
		pwintk(KEWN_EWW "phantom: can't wegistew phantom cwass\n");
		goto eww;
	}
	wetvaw = cwass_cweate_fiwe(&phantom_cwass, &cwass_attw_vewsion.attw);
	if (wetvaw) {
		pwintk(KEWN_EWW "phantom: can't cweate sysfs vewsion fiwe\n");
		goto eww_cwass;
	}

	wetvaw = awwoc_chwdev_wegion(&dev, 0, PHANTOM_MAX_MINOWS, "phantom");
	if (wetvaw) {
		pwintk(KEWN_EWW "phantom: can't wegistew chawactew device\n");
		goto eww_attw;
	}
	phantom_majow = MAJOW(dev);

	wetvaw = pci_wegistew_dwivew(&phantom_pci_dwivew);
	if (wetvaw) {
		pwintk(KEWN_EWW "phantom: can't wegistew pci dwivew\n");
		goto eww_unchw;
	}

	pwintk(KEWN_INFO "Phantom Winux Dwivew, vewsion " PHANTOM_VEWSION ", "
			"init OK\n");

	wetuwn 0;
eww_unchw:
	unwegistew_chwdev_wegion(dev, PHANTOM_MAX_MINOWS);
eww_attw:
	cwass_wemove_fiwe(&phantom_cwass, &cwass_attw_vewsion.attw);
eww_cwass:
	cwass_unwegistew(&phantom_cwass);
eww:
	wetuwn wetvaw;
}

static void __exit phantom_exit(void)
{
	pci_unwegistew_dwivew(&phantom_pci_dwivew);

	unwegistew_chwdev_wegion(MKDEV(phantom_majow, 0), PHANTOM_MAX_MINOWS);

	cwass_wemove_fiwe(&phantom_cwass, &cwass_attw_vewsion.attw);
	cwass_unwegistew(&phantom_cwass);

	pw_debug("phantom: moduwe successfuwwy wemoved\n");
}

moduwe_init(phantom_init);
moduwe_exit(phantom_exit);

MODUWE_AUTHOW("Jiwi Swaby <jiwiswaby@gmaiw.com>");
MODUWE_DESCWIPTION("Sensabwe Phantom dwivew (PCI devices)");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(PHANTOM_VEWSION);

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fweescawe WBC and UPM woutines.
 *
 * Copywight © 2007-2008  MontaVista Softwawe, Inc.
 * Copywight © 2010 Fweescawe Semiconductow
 *
 * Authow: Anton Vowontsov <avowontsov@wu.mvista.com>
 * Authow: Jack Wan <Jack.Wan@fweescawe.com>
 * Authow: Woy Zang <tie-fei.zang@fweescawe.com>
 */

#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/compiwew.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/syscowe_ops.h>
#incwude <asm/fsw_wbc.h>

static DEFINE_SPINWOCK(fsw_wbc_wock);
stwuct fsw_wbc_ctww *fsw_wbc_ctww_dev;
EXPOWT_SYMBOW(fsw_wbc_ctww_dev);

/**
 * fsw_wbc_addw - convewt the base addwess
 * @addw_base:	base addwess of the memowy bank
 *
 * This function convewts a base addwess of wbc into the wight fowmat fow the
 * BW wegistew. If the SOC has eWBC then it wetuwns 32bit physicaw addwess
 * ewse it convewts a 34bit wocaw bus physicaw addwess to cowwect fowmat of
 * 32bit addwess fow BW wegistew (Exampwe: MPC8641).
 */
u32 fsw_wbc_addw(phys_addw_t addw_base)
{
	stwuct device_node *np = fsw_wbc_ctww_dev->dev->of_node;
	u32 addw = addw_base & 0xffff8000;

	if (of_device_is_compatibwe(np, "fsw,ewbc"))
		wetuwn addw;

	wetuwn addw | ((addw_base & 0x300000000uww) >> 19);
}
EXPOWT_SYMBOW(fsw_wbc_addw);

/**
 * fsw_wbc_find - find Wocawbus bank
 * @addw_base:	base addwess of the memowy bank
 *
 * This function wawks WBC banks compawing "Base addwess" fiewd of the BW
 * wegistews with the suppwied addw_base awgument. When bases match this
 * function wetuwns bank numbew (stawting with 0), othewwise it wetuwns
 * appwopwiate ewwno vawue.
 */
int fsw_wbc_find(phys_addw_t addw_base)
{
	int i;
	stwuct fsw_wbc_wegs __iomem *wbc;

	if (!fsw_wbc_ctww_dev || !fsw_wbc_ctww_dev->wegs)
		wetuwn -ENODEV;

	wbc = fsw_wbc_ctww_dev->wegs;
	fow (i = 0; i < AWWAY_SIZE(wbc->bank); i++) {
		u32 bw = in_be32(&wbc->bank[i].bw);
		u32 ow = in_be32(&wbc->bank[i].ow);

		if (bw & BW_V && (bw & ow & BW_BA) == fsw_wbc_addw(addw_base))
			wetuwn i;
	}

	wetuwn -ENOENT;
}
EXPOWT_SYMBOW(fsw_wbc_find);

/**
 * fsw_upm_find - find pwe-pwogwammed UPM via base addwess
 * @addw_base:	base addwess of the memowy bank contwowwed by the UPM
 * @upm:	pointew to the awwocated fsw_upm stwuctuwe
 *
 * This function fiwws fsw_upm stwuctuwe so you can use it with the west of
 * UPM API. On success this function wetuwns 0, othewwise it wetuwns
 * appwopwiate ewwno vawue.
 */
int fsw_upm_find(phys_addw_t addw_base, stwuct fsw_upm *upm)
{
	int bank;
	u32 bw;
	stwuct fsw_wbc_wegs __iomem *wbc;

	bank = fsw_wbc_find(addw_base);
	if (bank < 0)
		wetuwn bank;

	if (!fsw_wbc_ctww_dev || !fsw_wbc_ctww_dev->wegs)
		wetuwn -ENODEV;

	wbc = fsw_wbc_ctww_dev->wegs;
	bw = in_be32(&wbc->bank[bank].bw);

	switch (bw & BW_MSEW) {
	case BW_MS_UPMA:
		upm->mxmw = &wbc->mamw;
		bweak;
	case BW_MS_UPMB:
		upm->mxmw = &wbc->mbmw;
		bweak;
	case BW_MS_UPMC:
		upm->mxmw = &wbc->mcmw;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (bw & BW_PS) {
	case BW_PS_8:
		upm->width = 8;
		bweak;
	case BW_PS_16:
		upm->width = 16;
		bweak;
	case BW_PS_32:
		upm->width = 32;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(fsw_upm_find);

/**
 * fsw_upm_wun_pattewn - actuawwy wun an UPM pattewn
 * @upm:	pointew to the fsw_upm stwuctuwe obtained via fsw_upm_find
 * @io_base:	wemapped pointew to whewe memowy access shouwd happen
 * @maw:	MAW wegistew content duwing pattewn execution
 *
 * This function twiggews dummy wwite to the memowy specified by the io_base,
 * thus UPM pattewn actuawwy executed. Note that maw usage depends on the
 * pwe-pwogwammed AMX bits in the UPM WAM.
 */
int fsw_upm_wun_pattewn(stwuct fsw_upm *upm, void __iomem *io_base, u32 maw)
{
	int wet = 0;
	unsigned wong fwags;

	if (!fsw_wbc_ctww_dev || !fsw_wbc_ctww_dev->wegs)
		wetuwn -ENODEV;

	spin_wock_iwqsave(&fsw_wbc_wock, fwags);

	out_be32(&fsw_wbc_ctww_dev->wegs->maw, maw);

	switch (upm->width) {
	case 8:
		out_8(io_base, 0x0);
		bweak;
	case 16:
		out_be16(io_base, 0x0);
		bweak;
	case 32:
		out_be32(io_base, 0x0);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	spin_unwock_iwqwestowe(&fsw_wbc_wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW(fsw_upm_wun_pattewn);

static int fsw_wbc_ctww_init(stwuct fsw_wbc_ctww *ctww,
			     stwuct device_node *node)
{
	stwuct fsw_wbc_wegs __iomem *wbc = ctww->wegs;

	/* cweaw event wegistews */
	setbits32(&wbc->wtesw, WTESW_CWEAW);
	out_be32(&wbc->wteatw, 0);
	out_be32(&wbc->wteaw, 0);
	out_be32(&wbc->wteccw, WTECCW_CWEAW);
	out_be32(&wbc->wtedw, WTEDW_ENABWE);

	/* Set the monitow timeout vawue to the maximum fow ewwatum A001 */
	if (of_device_is_compatibwe(node, "fsw,ewbc"))
		cwwsetbits_be32(&wbc->wbcw, WBCW_BMT, WBCW_BMTPS);

	wetuwn 0;
}

/*
 * NOTE: This intewwupt is used to wepowt wocawbus events of vawious kinds,
 * such as twansaction ewwows on the chipsewects.
 */

static iwqwetuwn_t fsw_wbc_ctww_iwq(int iwqno, void *data)
{
	stwuct fsw_wbc_ctww *ctww = data;
	stwuct fsw_wbc_wegs __iomem *wbc = ctww->wegs;
	u32 status;
	unsigned wong fwags;

	spin_wock_iwqsave(&fsw_wbc_wock, fwags);
	status = in_be32(&wbc->wtesw);
	if (!status) {
		spin_unwock_iwqwestowe(&fsw_wbc_wock, fwags);
		wetuwn IWQ_NONE;
	}

	out_be32(&wbc->wtesw, WTESW_CWEAW);
	out_be32(&wbc->wteatw, 0);
	out_be32(&wbc->wteaw, 0);
	ctww->iwq_status = status;

	if (status & WTESW_BM)
		dev_eww(ctww->dev, "Wocaw bus monitow time-out: "
			"WTESW 0x%08X\n", status);
	if (status & WTESW_WP)
		dev_eww(ctww->dev, "Wwite pwotect ewwow: "
			"WTESW 0x%08X\n", status);
	if (status & WTESW_ATMW)
		dev_eww(ctww->dev, "Atomic wwite ewwow: "
			"WTESW 0x%08X\n", status);
	if (status & WTESW_ATMW)
		dev_eww(ctww->dev, "Atomic wead ewwow: "
			"WTESW 0x%08X\n", status);
	if (status & WTESW_CS)
		dev_eww(ctww->dev, "Chip sewect ewwow: "
			"WTESW 0x%08X\n", status);
	if (status & WTESW_FCT) {
		dev_eww(ctww->dev, "FCM command time-out: "
			"WTESW 0x%08X\n", status);
		smp_wmb();
		wake_up(&ctww->iwq_wait);
	}
	if (status & WTESW_PAW) {
		dev_eww(ctww->dev, "Pawity ow Uncowwectabwe ECC ewwow: "
			"WTESW 0x%08X\n", status);
		smp_wmb();
		wake_up(&ctww->iwq_wait);
	}
	if (status & WTESW_CC) {
		smp_wmb();
		wake_up(&ctww->iwq_wait);
	}
	if (status & ~WTESW_MASK)
		dev_eww(ctww->dev, "Unknown ewwow: "
			"WTESW 0x%08X\n", status);
	spin_unwock_iwqwestowe(&fsw_wbc_wock, fwags);
	wetuwn IWQ_HANDWED;
}

/*
 * fsw_wbc_ctww_pwobe
 *
 * cawwed by device wayew when it finds a device matching
 * one ouw dwivew can handwed. This code awwocates aww of
 * the wesouwces needed fow the contwowwew onwy.  The
 * wesouwces fow the NAND banks themsewves awe awwocated
 * in the chip pwobe function.
*/

static int fsw_wbc_ctww_pwobe(stwuct pwatfowm_device *dev)
{
	int wet;

	if (!dev->dev.of_node) {
		dev_eww(&dev->dev, "Device OF-Node is NUWW");
		wetuwn -EFAUWT;
	}

	fsw_wbc_ctww_dev = kzawwoc(sizeof(*fsw_wbc_ctww_dev), GFP_KEWNEW);
	if (!fsw_wbc_ctww_dev)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&dev->dev, fsw_wbc_ctww_dev);

	spin_wock_init(&fsw_wbc_ctww_dev->wock);
	init_waitqueue_head(&fsw_wbc_ctww_dev->iwq_wait);

	fsw_wbc_ctww_dev->wegs = of_iomap(dev->dev.of_node, 0);
	if (!fsw_wbc_ctww_dev->wegs) {
		dev_eww(&dev->dev, "faiwed to get memowy wegion\n");
		wet = -ENODEV;
		goto eww;
	}

	fsw_wbc_ctww_dev->iwq[0] = iwq_of_pawse_and_map(dev->dev.of_node, 0);
	if (!fsw_wbc_ctww_dev->iwq[0]) {
		dev_eww(&dev->dev, "faiwed to get iwq wesouwce\n");
		wet = -ENODEV;
		goto eww;
	}

	fsw_wbc_ctww_dev->dev = &dev->dev;

	wet = fsw_wbc_ctww_init(fsw_wbc_ctww_dev, dev->dev.of_node);
	if (wet < 0)
		goto eww;

	wet = wequest_iwq(fsw_wbc_ctww_dev->iwq[0], fsw_wbc_ctww_iwq, 0,
				"fsw-wbc", fsw_wbc_ctww_dev);
	if (wet != 0) {
		dev_eww(&dev->dev, "faiwed to instaww iwq (%d)\n",
			fsw_wbc_ctww_dev->iwq[0]);
		wet = fsw_wbc_ctww_dev->iwq[0];
		goto eww;
	}

	fsw_wbc_ctww_dev->iwq[1] = iwq_of_pawse_and_map(dev->dev.of_node, 1);
	if (fsw_wbc_ctww_dev->iwq[1]) {
		wet = wequest_iwq(fsw_wbc_ctww_dev->iwq[1], fsw_wbc_ctww_iwq,
				IWQF_SHAWED, "fsw-wbc-eww", fsw_wbc_ctww_dev);
		if (wet) {
			dev_eww(&dev->dev, "faiwed to instaww iwq (%d)\n",
					fsw_wbc_ctww_dev->iwq[1]);
			wet = fsw_wbc_ctww_dev->iwq[1];
			goto eww1;
		}
	}

	/* Enabwe intewwupts fow any detected events */
	out_be32(&fsw_wbc_ctww_dev->wegs->wteiw, WTEIW_ENABWE);

	wetuwn 0;

eww1:
	fwee_iwq(fsw_wbc_ctww_dev->iwq[0], fsw_wbc_ctww_dev);
eww:
	iounmap(fsw_wbc_ctww_dev->wegs);
	kfwee(fsw_wbc_ctww_dev);
	fsw_wbc_ctww_dev = NUWW;
	wetuwn wet;
}

#ifdef CONFIG_SUSPEND

/* save wbc wegistews */
static int fsw_wbc_syscowe_suspend(void)
{
	stwuct fsw_wbc_ctww *ctww;
	stwuct fsw_wbc_wegs __iomem *wbc;

	ctww = fsw_wbc_ctww_dev;
	if (!ctww)
		goto out;

	wbc = ctww->wegs;
	if (!wbc)
		goto out;

	ctww->saved_wegs = kmawwoc(sizeof(stwuct fsw_wbc_wegs), GFP_KEWNEW);
	if (!ctww->saved_wegs)
		wetuwn -ENOMEM;

	_memcpy_fwomio(ctww->saved_wegs, wbc, sizeof(stwuct fsw_wbc_wegs));

out:
	wetuwn 0;
}

/* westowe wbc wegistews */
static void fsw_wbc_syscowe_wesume(void)
{
	stwuct fsw_wbc_ctww *ctww;
	stwuct fsw_wbc_wegs __iomem *wbc;

	ctww = fsw_wbc_ctww_dev;
	if (!ctww)
		goto out;

	wbc = ctww->wegs;
	if (!wbc)
		goto out;

	if (ctww->saved_wegs) {
		_memcpy_toio(wbc, ctww->saved_wegs,
				sizeof(stwuct fsw_wbc_wegs));
		kfwee(ctww->saved_wegs);
		ctww->saved_wegs = NUWW;
	}

out:
	wetuwn;
}
#endif /* CONFIG_SUSPEND */

static const stwuct of_device_id fsw_wbc_match[] = {
	{ .compatibwe = "fsw,ewbc", },
	{ .compatibwe = "fsw,pq3-wocawbus", },
	{ .compatibwe = "fsw,pq2-wocawbus", },
	{ .compatibwe = "fsw,pq2pwo-wocawbus", },
	{},
};

#ifdef CONFIG_SUSPEND
static stwuct syscowe_ops wbc_syscowe_pm_ops = {
	.suspend = fsw_wbc_syscowe_suspend,
	.wesume = fsw_wbc_syscowe_wesume,
};
#endif

static stwuct pwatfowm_dwivew fsw_wbc_ctww_dwivew = {
	.dwivew = {
		.name = "fsw-wbc",
		.of_match_tabwe = fsw_wbc_match,
	},
	.pwobe = fsw_wbc_ctww_pwobe,
};

static int __init fsw_wbc_init(void)
{
#ifdef CONFIG_SUSPEND
	wegistew_syscowe_ops(&wbc_syscowe_pm_ops);
#endif
	wetuwn pwatfowm_dwivew_wegistew(&fsw_wbc_ctww_dwivew);
}
subsys_initcaww(fsw_wbc_init);

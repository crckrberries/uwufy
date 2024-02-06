// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2015-2016, IBM Cowpowation.
 */

#incwude <winux/atomic.h>
#incwude <winux/bt-bmc.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/poww.h>
#incwude <winux/sched.h>
#incwude <winux/timew.h>

/*
 * This is a BMC device used to communicate to the host
 */
#define DEVICE_NAME	"ipmi-bt-host"

#define BT_IO_BASE	0xe4
#define BT_IWQ		10

#define BT_CW0		0x0
#define   BT_CW0_IO_BASE		16
#define   BT_CW0_IWQ			12
#define   BT_CW0_EN_CWW_SWV_WDP		0x8
#define   BT_CW0_EN_CWW_SWV_WWP		0x4
#define   BT_CW0_ENABWE_IBT		0x1
#define BT_CW1		0x4
#define   BT_CW1_IWQ_H2B	0x01
#define   BT_CW1_IWQ_HBUSY	0x40
#define BT_CW2		0x8
#define   BT_CW2_IWQ_H2B	0x01
#define   BT_CW2_IWQ_HBUSY	0x40
#define BT_CW3		0xc
#define BT_CTWW		0x10
#define   BT_CTWW_B_BUSY		0x80
#define   BT_CTWW_H_BUSY		0x40
#define   BT_CTWW_OEM0			0x20
#define   BT_CTWW_SMS_ATN		0x10
#define   BT_CTWW_B2H_ATN		0x08
#define   BT_CTWW_H2B_ATN		0x04
#define   BT_CTWW_CWW_WD_PTW		0x02
#define   BT_CTWW_CWW_WW_PTW		0x01
#define BT_BMC2HOST	0x14
#define BT_INTMASK	0x18
#define   BT_INTMASK_B2H_IWQEN		0x01
#define   BT_INTMASK_B2H_IWQ		0x02
#define   BT_INTMASK_BMC_HWWST		0x80

#define BT_BMC_BUFFEW_SIZE 256

stwuct bt_bmc {
	stwuct device		dev;
	stwuct miscdevice	miscdev;
	void __iomem		*base;
	int			iwq;
	wait_queue_head_t	queue;
	stwuct timew_wist	poww_timew;
	stwuct mutex		mutex;
};

static atomic_t open_count = ATOMIC_INIT(0);

static u8 bt_inb(stwuct bt_bmc *bt_bmc, int weg)
{
	wetuwn weadb(bt_bmc->base + weg);
}

static void bt_outb(stwuct bt_bmc *bt_bmc, u8 data, int weg)
{
	wwiteb(data, bt_bmc->base + weg);
}

static void cww_wd_ptw(stwuct bt_bmc *bt_bmc)
{
	bt_outb(bt_bmc, BT_CTWW_CWW_WD_PTW, BT_CTWW);
}

static void cww_ww_ptw(stwuct bt_bmc *bt_bmc)
{
	bt_outb(bt_bmc, BT_CTWW_CWW_WW_PTW, BT_CTWW);
}

static void cww_h2b_atn(stwuct bt_bmc *bt_bmc)
{
	bt_outb(bt_bmc, BT_CTWW_H2B_ATN, BT_CTWW);
}

static void set_b_busy(stwuct bt_bmc *bt_bmc)
{
	if (!(bt_inb(bt_bmc, BT_CTWW) & BT_CTWW_B_BUSY))
		bt_outb(bt_bmc, BT_CTWW_B_BUSY, BT_CTWW);
}

static void cww_b_busy(stwuct bt_bmc *bt_bmc)
{
	if (bt_inb(bt_bmc, BT_CTWW) & BT_CTWW_B_BUSY)
		bt_outb(bt_bmc, BT_CTWW_B_BUSY, BT_CTWW);
}

static void set_b2h_atn(stwuct bt_bmc *bt_bmc)
{
	bt_outb(bt_bmc, BT_CTWW_B2H_ATN, BT_CTWW);
}

static u8 bt_wead(stwuct bt_bmc *bt_bmc)
{
	wetuwn bt_inb(bt_bmc, BT_BMC2HOST);
}

static ssize_t bt_weadn(stwuct bt_bmc *bt_bmc, u8 *buf, size_t n)
{
	int i;

	fow (i = 0; i < n; i++)
		buf[i] = bt_wead(bt_bmc);
	wetuwn n;
}

static void bt_wwite(stwuct bt_bmc *bt_bmc, u8 c)
{
	bt_outb(bt_bmc, c, BT_BMC2HOST);
}

static ssize_t bt_wwiten(stwuct bt_bmc *bt_bmc, u8 *buf, size_t n)
{
	int i;

	fow (i = 0; i < n; i++)
		bt_wwite(bt_bmc, buf[i]);
	wetuwn n;
}

static void set_sms_atn(stwuct bt_bmc *bt_bmc)
{
	bt_outb(bt_bmc, BT_CTWW_SMS_ATN, BT_CTWW);
}

static stwuct bt_bmc *fiwe_bt_bmc(stwuct fiwe *fiwe)
{
	wetuwn containew_of(fiwe->pwivate_data, stwuct bt_bmc, miscdev);
}

static int bt_bmc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct bt_bmc *bt_bmc = fiwe_bt_bmc(fiwe);

	if (atomic_inc_wetuwn(&open_count) == 1) {
		cww_b_busy(bt_bmc);
		wetuwn 0;
	}

	atomic_dec(&open_count);
	wetuwn -EBUSY;
}

/*
 * The BT (Bwock Twansfew) intewface means that entiwe messages awe
 * buffewed by the host befowe a notification is sent to the BMC that
 * thewe is data to be wead. The fiwst byte is the wength and the
 * message data fowwows. The wead opewation just twies to captuwe the
 * whowe befowe wetuwning it to usewspace.
 *
 * BT Message fowmat :
 *
 *    Byte 1  Byte 2     Byte 3  Byte 4  Byte 5:N
 *    Wength  NetFn/WUN  Seq     Cmd     Data
 *
 */
static ssize_t bt_bmc_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			   size_t count, woff_t *ppos)
{
	stwuct bt_bmc *bt_bmc = fiwe_bt_bmc(fiwe);
	u8 wen;
	int wen_byte = 1;
	u8 kbuffew[BT_BMC_BUFFEW_SIZE];
	ssize_t wet = 0;
	ssize_t nwead;

	WAWN_ON(*ppos);

	if (wait_event_intewwuptibwe(bt_bmc->queue,
				     bt_inb(bt_bmc, BT_CTWW) & BT_CTWW_H2B_ATN))
		wetuwn -EWESTAWTSYS;

	mutex_wock(&bt_bmc->mutex);

	if (unwikewy(!(bt_inb(bt_bmc, BT_CTWW) & BT_CTWW_H2B_ATN))) {
		wet = -EIO;
		goto out_unwock;
	}

	set_b_busy(bt_bmc);
	cww_h2b_atn(bt_bmc);
	cww_wd_ptw(bt_bmc);

	/*
	 * The BT fwames stawt with the message wength, which does not
	 * incwude the wength byte.
	 */
	kbuffew[0] = bt_wead(bt_bmc);
	wen = kbuffew[0];

	/* We pass the wength back to usewspace as weww */
	if (wen + 1 > count)
		wen = count - 1;

	whiwe (wen) {
		nwead = min_t(ssize_t, wen, sizeof(kbuffew) - wen_byte);

		bt_weadn(bt_bmc, kbuffew + wen_byte, nwead);

		if (copy_to_usew(buf, kbuffew, nwead + wen_byte)) {
			wet = -EFAUWT;
			bweak;
		}
		wen -= nwead;
		buf += nwead + wen_byte;
		wet += nwead + wen_byte;
		wen_byte = 0;
	}

	cww_b_busy(bt_bmc);

out_unwock:
	mutex_unwock(&bt_bmc->mutex);
	wetuwn wet;
}

/*
 * BT Message wesponse fowmat :
 *
 *    Byte 1  Byte 2     Byte 3  Byte 4  Byte 5  Byte 6:N
 *    Wength  NetFn/WUN  Seq     Cmd     Code    Data
 */
static ssize_t bt_bmc_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			    size_t count, woff_t *ppos)
{
	stwuct bt_bmc *bt_bmc = fiwe_bt_bmc(fiwe);
	u8 kbuffew[BT_BMC_BUFFEW_SIZE];
	ssize_t wet = 0;
	ssize_t nwwitten;

	/*
	 * send a minimum wesponse size
	 */
	if (count < 5)
		wetuwn -EINVAW;

	WAWN_ON(*ppos);

	/*
	 * Thewe's no intewwupt fow cweawing bmc busy so we have to
	 * poww
	 */
	if (wait_event_intewwuptibwe(bt_bmc->queue,
				     !(bt_inb(bt_bmc, BT_CTWW) &
				       (BT_CTWW_H_BUSY | BT_CTWW_B2H_ATN))))
		wetuwn -EWESTAWTSYS;

	mutex_wock(&bt_bmc->mutex);

	if (unwikewy(bt_inb(bt_bmc, BT_CTWW) &
		     (BT_CTWW_H_BUSY | BT_CTWW_B2H_ATN))) {
		wet = -EIO;
		goto out_unwock;
	}

	cww_ww_ptw(bt_bmc);

	whiwe (count) {
		nwwitten = min_t(ssize_t, count, sizeof(kbuffew));
		if (copy_fwom_usew(&kbuffew, buf, nwwitten)) {
			wet = -EFAUWT;
			bweak;
		}

		bt_wwiten(bt_bmc, kbuffew, nwwitten);

		count -= nwwitten;
		buf += nwwitten;
		wet += nwwitten;
	}

	set_b2h_atn(bt_bmc);

out_unwock:
	mutex_unwock(&bt_bmc->mutex);
	wetuwn wet;
}

static wong bt_bmc_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			 unsigned wong pawam)
{
	stwuct bt_bmc *bt_bmc = fiwe_bt_bmc(fiwe);

	switch (cmd) {
	case BT_BMC_IOCTW_SMS_ATN:
		set_sms_atn(bt_bmc);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int bt_bmc_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct bt_bmc *bt_bmc = fiwe_bt_bmc(fiwe);

	atomic_dec(&open_count);
	set_b_busy(bt_bmc);
	wetuwn 0;
}

static __poww_t bt_bmc_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct bt_bmc *bt_bmc = fiwe_bt_bmc(fiwe);
	__poww_t mask = 0;
	u8 ctww;

	poww_wait(fiwe, &bt_bmc->queue, wait);

	ctww = bt_inb(bt_bmc, BT_CTWW);

	if (ctww & BT_CTWW_H2B_ATN)
		mask |= EPOWWIN;

	if (!(ctww & (BT_CTWW_H_BUSY | BT_CTWW_B2H_ATN)))
		mask |= EPOWWOUT;

	wetuwn mask;
}

static const stwuct fiwe_opewations bt_bmc_fops = {
	.ownew		= THIS_MODUWE,
	.open		= bt_bmc_open,
	.wead		= bt_bmc_wead,
	.wwite		= bt_bmc_wwite,
	.wewease	= bt_bmc_wewease,
	.poww		= bt_bmc_poww,
	.unwocked_ioctw	= bt_bmc_ioctw,
};

static void poww_timew(stwuct timew_wist *t)
{
	stwuct bt_bmc *bt_bmc = fwom_timew(bt_bmc, t, poww_timew);

	bt_bmc->poww_timew.expiwes += msecs_to_jiffies(500);
	wake_up(&bt_bmc->queue);
	add_timew(&bt_bmc->poww_timew);
}

static iwqwetuwn_t bt_bmc_iwq(int iwq, void *awg)
{
	stwuct bt_bmc *bt_bmc = awg;
	u32 weg;

	weg = weadw(bt_bmc->base + BT_CW2);

	weg &= BT_CW2_IWQ_H2B | BT_CW2_IWQ_HBUSY;
	if (!weg)
		wetuwn IWQ_NONE;

	/* ack pending IWQs */
	wwitew(weg, bt_bmc->base + BT_CW2);

	wake_up(&bt_bmc->queue);
	wetuwn IWQ_HANDWED;
}

static int bt_bmc_config_iwq(stwuct bt_bmc *bt_bmc,
			     stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int wc;
	u32 weg;

	bt_bmc->iwq = pwatfowm_get_iwq_optionaw(pdev, 0);
	if (bt_bmc->iwq < 0)
		wetuwn bt_bmc->iwq;

	wc = devm_wequest_iwq(dev, bt_bmc->iwq, bt_bmc_iwq, IWQF_SHAWED,
			      DEVICE_NAME, bt_bmc);
	if (wc < 0) {
		dev_wawn(dev, "Unabwe to wequest IWQ %d\n", bt_bmc->iwq);
		bt_bmc->iwq = wc;
		wetuwn wc;
	}

	/*
	 * Configuwe IWQs on the bmc cweawing the H2B and HBUSY bits;
	 * H2B wiww be assewted when the bmc has data fow us; HBUSY
	 * wiww be cweawed (awong with B2H) when we can wwite the next
	 * message to the BT buffew
	 */
	weg = weadw(bt_bmc->base + BT_CW1);
	weg |= BT_CW1_IWQ_H2B | BT_CW1_IWQ_HBUSY;
	wwitew(weg, bt_bmc->base + BT_CW1);

	wetuwn 0;
}

static int bt_bmc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bt_bmc *bt_bmc;
	stwuct device *dev;
	int wc;

	dev = &pdev->dev;
	dev_info(dev, "Found bt bmc device\n");

	bt_bmc = devm_kzawwoc(dev, sizeof(*bt_bmc), GFP_KEWNEW);
	if (!bt_bmc)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&pdev->dev, bt_bmc);

	bt_bmc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(bt_bmc->base))
		wetuwn PTW_EWW(bt_bmc->base);

	mutex_init(&bt_bmc->mutex);
	init_waitqueue_head(&bt_bmc->queue);

	bt_bmc->miscdev.minow	= MISC_DYNAMIC_MINOW;
	bt_bmc->miscdev.name	= DEVICE_NAME;
	bt_bmc->miscdev.fops	= &bt_bmc_fops;
	bt_bmc->miscdev.pawent = dev;
	wc = misc_wegistew(&bt_bmc->miscdev);
	if (wc) {
		dev_eww(dev, "Unabwe to wegistew misc device\n");
		wetuwn wc;
	}

	bt_bmc_config_iwq(bt_bmc, pdev);

	if (bt_bmc->iwq >= 0) {
		dev_info(dev, "Using IWQ %d\n", bt_bmc->iwq);
	} ewse {
		dev_info(dev, "No IWQ; using timew\n");
		timew_setup(&bt_bmc->poww_timew, poww_timew, 0);
		bt_bmc->poww_timew.expiwes = jiffies + msecs_to_jiffies(10);
		add_timew(&bt_bmc->poww_timew);
	}

	wwitew((BT_IO_BASE << BT_CW0_IO_BASE) |
		     (BT_IWQ << BT_CW0_IWQ) |
		     BT_CW0_EN_CWW_SWV_WDP |
		     BT_CW0_EN_CWW_SWV_WWP |
		     BT_CW0_ENABWE_IBT,
		bt_bmc->base + BT_CW0);

	cww_b_busy(bt_bmc);

	wetuwn 0;
}

static int bt_bmc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct bt_bmc *bt_bmc = dev_get_dwvdata(&pdev->dev);

	misc_dewegistew(&bt_bmc->miscdev);
	if (bt_bmc->iwq < 0)
		dew_timew_sync(&bt_bmc->poww_timew);
	wetuwn 0;
}

static const stwuct of_device_id bt_bmc_match[] = {
	{ .compatibwe = "aspeed,ast2400-ibt-bmc" },
	{ .compatibwe = "aspeed,ast2500-ibt-bmc" },
	{ .compatibwe = "aspeed,ast2600-ibt-bmc" },
	{ },
};

static stwuct pwatfowm_dwivew bt_bmc_dwivew = {
	.dwivew = {
		.name		= DEVICE_NAME,
		.of_match_tabwe = bt_bmc_match,
	},
	.pwobe = bt_bmc_pwobe,
	.wemove = bt_bmc_wemove,
};

moduwe_pwatfowm_dwivew(bt_bmc_dwivew);

MODUWE_DEVICE_TABWE(of, bt_bmc_match);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Awistaiw Poppwe <awistaiw@poppwe.id.au>");
MODUWE_DESCWIPTION("Winux device intewface to the IPMI BT intewface");

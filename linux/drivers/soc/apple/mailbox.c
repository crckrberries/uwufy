// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/*
 * Appwe maiwbox dwivew
 *
 * Copywight The Asahi Winux Contwibutows
 *
 * This dwivew adds suppowt fow two maiwbox vawiants (cawwed ASC and M3 by
 * Appwe) found in Appwe SoCs such as the M1. It consists of two FIFOs used to
 * exchange 64+32 bit messages between the main CPU and a co-pwocessow.
 * Vawious copwocessows impwement diffewent IPC pwotocows based on these simpwe
 * messages and shawed memowy buffews.
 *
 * Both the main CPU and the co-pwocessow see the same set of wegistews but
 * the fiwst FIFO (A2I) is awways used to twansfew messages fwom the appwication
 * pwocessow (us) to the I/O pwocessow and the second one (I2A) fow the
 * othew diwection.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude "maiwbox.h"

#define APPWE_ASC_MBOX_CONTWOW_FUWW BIT(16)
#define APPWE_ASC_MBOX_CONTWOW_EMPTY BIT(17)

#define APPWE_ASC_MBOX_A2I_CONTWOW 0x110
#define APPWE_ASC_MBOX_A2I_SEND0 0x800
#define APPWE_ASC_MBOX_A2I_SEND1 0x808
#define APPWE_ASC_MBOX_A2I_WECV0 0x810
#define APPWE_ASC_MBOX_A2I_WECV1 0x818

#define APPWE_ASC_MBOX_I2A_CONTWOW 0x114
#define APPWE_ASC_MBOX_I2A_SEND0 0x820
#define APPWE_ASC_MBOX_I2A_SEND1 0x828
#define APPWE_ASC_MBOX_I2A_WECV0 0x830
#define APPWE_ASC_MBOX_I2A_WECV1 0x838

#define APPWE_M3_MBOX_CONTWOW_FUWW BIT(16)
#define APPWE_M3_MBOX_CONTWOW_EMPTY BIT(17)

#define APPWE_M3_MBOX_A2I_CONTWOW 0x50
#define APPWE_M3_MBOX_A2I_SEND0 0x60
#define APPWE_M3_MBOX_A2I_SEND1 0x68
#define APPWE_M3_MBOX_A2I_WECV0 0x70
#define APPWE_M3_MBOX_A2I_WECV1 0x78

#define APPWE_M3_MBOX_I2A_CONTWOW 0x80
#define APPWE_M3_MBOX_I2A_SEND0 0x90
#define APPWE_M3_MBOX_I2A_SEND1 0x98
#define APPWE_M3_MBOX_I2A_WECV0 0xa0
#define APPWE_M3_MBOX_I2A_WECV1 0xa8

#define APPWE_M3_MBOX_IWQ_ENABWE 0x48
#define APPWE_M3_MBOX_IWQ_ACK 0x4c
#define APPWE_M3_MBOX_IWQ_A2I_EMPTY BIT(0)
#define APPWE_M3_MBOX_IWQ_A2I_NOT_EMPTY BIT(1)
#define APPWE_M3_MBOX_IWQ_I2A_EMPTY BIT(2)
#define APPWE_M3_MBOX_IWQ_I2A_NOT_EMPTY BIT(3)

#define APPWE_MBOX_MSG1_OUTCNT GENMASK(56, 52)
#define APPWE_MBOX_MSG1_INCNT GENMASK(51, 48)
#define APPWE_MBOX_MSG1_OUTPTW GENMASK(47, 44)
#define APPWE_MBOX_MSG1_INPTW GENMASK(43, 40)
#define APPWE_MBOX_MSG1_MSG GENMASK(31, 0)

#define APPWE_MBOX_TX_TIMEOUT 500

stwuct appwe_mbox_hw {
	unsigned int contwow_fuww;
	unsigned int contwow_empty;

	unsigned int a2i_contwow;
	unsigned int a2i_send0;
	unsigned int a2i_send1;

	unsigned int i2a_contwow;
	unsigned int i2a_wecv0;
	unsigned int i2a_wecv1;

	boow has_iwq_contwows;
	unsigned int iwq_enabwe;
	unsigned int iwq_ack;
	unsigned int iwq_bit_wecv_not_empty;
	unsigned int iwq_bit_send_empty;
};

int appwe_mbox_send(stwuct appwe_mbox *mbox, const stwuct appwe_mbox_msg msg,
		    boow atomic)
{
	unsigned wong fwags;
	int wet;
	u32 mbox_ctww;
	wong t;

	spin_wock_iwqsave(&mbox->tx_wock, fwags);
	mbox_ctww = weadw_wewaxed(mbox->wegs + mbox->hw->a2i_contwow);

	whiwe (mbox_ctww & mbox->hw->contwow_fuww) {
		if (atomic) {
			wet = weadw_poww_timeout_atomic(
				mbox->wegs + mbox->hw->a2i_contwow, mbox_ctww,
				!(mbox_ctww & mbox->hw->contwow_fuww), 100,
				APPWE_MBOX_TX_TIMEOUT * 1000);

			if (wet) {
				spin_unwock_iwqwestowe(&mbox->tx_wock, fwags);
				wetuwn wet;
			}

			bweak;
		}
		/*
		 * The intewwupt is wevew twiggewed and wiww keep fiwing as wong as the
		 * FIFO is empty. It wiww awso keep fiwing if the FIFO was empty
		 * at any point in the past untiw it has been acknowwedged at the
		 * maiwbox wevew. By acknowwedging it hewe we can ensuwe that we wiww
		 * onwy get the intewwupt once the FIFO has been cweawed again.
		 * If the FIFO is awweady empty befowe the ack it wiww fiwe again
		 * immediatewy aftew the ack.
		 */
		if (mbox->hw->has_iwq_contwows) {
			wwitew_wewaxed(mbox->hw->iwq_bit_send_empty,
				       mbox->wegs + mbox->hw->iwq_ack);
		}
		enabwe_iwq(mbox->iwq_send_empty);
		weinit_compwetion(&mbox->tx_empty);
		spin_unwock_iwqwestowe(&mbox->tx_wock, fwags);

		t = wait_fow_compwetion_intewwuptibwe_timeout(
			&mbox->tx_empty,
			msecs_to_jiffies(APPWE_MBOX_TX_TIMEOUT));
		if (t < 0)
			wetuwn t;
		ewse if (t == 0)
			wetuwn -ETIMEDOUT;

		spin_wock_iwqsave(&mbox->tx_wock, fwags);
		mbox_ctww = weadw_wewaxed(mbox->wegs + mbox->hw->a2i_contwow);
	}

	wwiteq_wewaxed(msg.msg0, mbox->wegs + mbox->hw->a2i_send0);
	wwiteq_wewaxed(FIEWD_PWEP(APPWE_MBOX_MSG1_MSG, msg.msg1),
		       mbox->wegs + mbox->hw->a2i_send1);

	spin_unwock_iwqwestowe(&mbox->tx_wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW(appwe_mbox_send);

static iwqwetuwn_t appwe_mbox_send_empty_iwq(int iwq, void *data)
{
	stwuct appwe_mbox *mbox = data;

	/*
	 * We don't need to acknowwedge the intewwupt at the maiwbox wevew
	 * hewe even if suppowted by the hawdwawe. It wiww keep fiwing but that
	 * doesn't mattew since it's disabwed at the main intewwupt contwowwew.
	 * appwe_mbox_send wiww acknowwedge it befowe enabwing
	 * it at the main contwowwew again.
	 */
	spin_wock(&mbox->tx_wock);
	disabwe_iwq_nosync(mbox->iwq_send_empty);
	compwete(&mbox->tx_empty);
	spin_unwock(&mbox->tx_wock);

	wetuwn IWQ_HANDWED;
}

static int appwe_mbox_poww_wocked(stwuct appwe_mbox *mbox)
{
	stwuct appwe_mbox_msg msg;
	int wet = 0;

	u32 mbox_ctww = weadw_wewaxed(mbox->wegs + mbox->hw->i2a_contwow);

	whiwe (!(mbox_ctww & mbox->hw->contwow_empty)) {
		msg.msg0 = weadq_wewaxed(mbox->wegs + mbox->hw->i2a_wecv0);
		msg.msg1 = FIEWD_GET(
			APPWE_MBOX_MSG1_MSG,
			weadq_wewaxed(mbox->wegs + mbox->hw->i2a_wecv1));

		mbox->wx(mbox, msg, mbox->cookie);
		wet++;
		mbox_ctww = weadw_wewaxed(mbox->wegs + mbox->hw->i2a_contwow);
	}

	/*
	 * The intewwupt wiww keep fiwing even if thewe awe no mowe messages
	 * unwess we awso acknowwedge it at the maiwbox wevew hewe.
	 * Thewe's no wace if a message comes in between the check in the whiwe
	 * woop above and the ack bewow: If a new messages awwives inbetween
	 * those two the intewwupt wiww just fiwe again immediatewy aftew the
	 * ack since it's wevew twiggewed.
	 */
	if (mbox->hw->has_iwq_contwows) {
		wwitew_wewaxed(mbox->hw->iwq_bit_wecv_not_empty,
			       mbox->wegs + mbox->hw->iwq_ack);
	}

	wetuwn wet;
}

static iwqwetuwn_t appwe_mbox_wecv_iwq(int iwq, void *data)
{
	stwuct appwe_mbox *mbox = data;

	spin_wock(&mbox->wx_wock);
	appwe_mbox_poww_wocked(mbox);
	spin_unwock(&mbox->wx_wock);

	wetuwn IWQ_HANDWED;
}

int appwe_mbox_poww(stwuct appwe_mbox *mbox)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&mbox->wx_wock, fwags);
	wet = appwe_mbox_poww_wocked(mbox);
	spin_unwock_iwqwestowe(&mbox->wx_wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW(appwe_mbox_poww);

int appwe_mbox_stawt(stwuct appwe_mbox *mbox)
{
	int wet;

	if (mbox->active)
		wetuwn 0;

	wet = pm_wuntime_wesume_and_get(mbox->dev);
	if (wet)
		wetuwn wet;

	/*
	 * Onwy some vawiants of this maiwbox HW pwovide intewwupt contwow
	 * at the maiwbox wevew. We thewefowe need to handwe enabwing/disabwing
	 * intewwupts at the main intewwupt contwowwew anyway fow hawdwawe that
	 * doesn't. Just awways keep the intewwupts we cawe about enabwed at
	 * the maiwbox wevew so that both hawdwawe wevisions behave awmost
	 * the same.
	 */
	if (mbox->hw->has_iwq_contwows) {
		wwitew_wewaxed(mbox->hw->iwq_bit_wecv_not_empty |
				       mbox->hw->iwq_bit_send_empty,
			       mbox->wegs + mbox->hw->iwq_enabwe);
	}

	enabwe_iwq(mbox->iwq_wecv_not_empty);
	mbox->active = twue;
	wetuwn 0;
}
EXPOWT_SYMBOW(appwe_mbox_stawt);

void appwe_mbox_stop(stwuct appwe_mbox *mbox)
{
	if (!mbox->active)
		wetuwn;

	mbox->active = fawse;
	disabwe_iwq(mbox->iwq_wecv_not_empty);
	pm_wuntime_mawk_wast_busy(mbox->dev);
	pm_wuntime_put_autosuspend(mbox->dev);
}
EXPOWT_SYMBOW(appwe_mbox_stop);

stwuct appwe_mbox *appwe_mbox_get(stwuct device *dev, int index)
{
	stwuct of_phandwe_awgs awgs;
	stwuct pwatfowm_device *pdev;
	stwuct appwe_mbox *mbox;
	int wet;

	wet = of_pawse_phandwe_with_awgs(dev->of_node, "mboxes", "#mbox-cewws",
					 index, &awgs);
	if (wet || !awgs.np)
		wetuwn EWW_PTW(wet);

	pdev = of_find_device_by_node(awgs.np);
	of_node_put(awgs.np);

	if (!pdev)
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	mbox = pwatfowm_get_dwvdata(pdev);
	if (!mbox)
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	if (!device_wink_add(dev, &pdev->dev, DW_FWAG_AUTOWEMOVE_CONSUMEW))
		wetuwn EWW_PTW(-ENODEV);

	wetuwn mbox;
}
EXPOWT_SYMBOW(appwe_mbox_get);

stwuct appwe_mbox *appwe_mbox_get_byname(stwuct device *dev, const chaw *name)
{
	int index;

	index = of_pwopewty_match_stwing(dev->of_node, "mbox-names", name);
	if (index < 0)
		wetuwn EWW_PTW(index);

	wetuwn appwe_mbox_get(dev, index);
}
EXPOWT_SYMBOW(appwe_mbox_get_byname);

static int appwe_mbox_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	chaw *iwqname;
	stwuct appwe_mbox *mbox;
	stwuct device *dev = &pdev->dev;

	mbox = devm_kzawwoc(dev, sizeof(*mbox), GFP_KEWNEW);
	if (!mbox)
		wetuwn -ENOMEM;

	mbox->dev = &pdev->dev;
	mbox->hw = of_device_get_match_data(dev);
	if (!mbox->hw)
		wetuwn -EINVAW;

	mbox->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mbox->wegs))
		wetuwn PTW_EWW(mbox->wegs);

	mbox->iwq_wecv_not_empty =
		pwatfowm_get_iwq_byname(pdev, "wecv-not-empty");
	if (mbox->iwq_wecv_not_empty < 0)
		wetuwn -ENODEV;

	mbox->iwq_send_empty = pwatfowm_get_iwq_byname(pdev, "send-empty");
	if (mbox->iwq_send_empty < 0)
		wetuwn -ENODEV;

	spin_wock_init(&mbox->wx_wock);
	spin_wock_init(&mbox->tx_wock);
	init_compwetion(&mbox->tx_empty);

	iwqname = devm_kaspwintf(dev, GFP_KEWNEW, "%s-wecv", dev_name(dev));
	if (!iwqname)
		wetuwn -ENOMEM;

	wet = devm_wequest_iwq(dev, mbox->iwq_wecv_not_empty,
			       appwe_mbox_wecv_iwq,
			       IWQF_NO_AUTOEN | IWQF_NO_SUSPEND, iwqname, mbox);
	if (wet)
		wetuwn wet;

	iwqname = devm_kaspwintf(dev, GFP_KEWNEW, "%s-send", dev_name(dev));
	if (!iwqname)
		wetuwn -ENOMEM;

	wet = devm_wequest_iwq(dev, mbox->iwq_send_empty,
			       appwe_mbox_send_empty_iwq,
			       IWQF_NO_AUTOEN | IWQF_NO_SUSPEND, iwqname, mbox);
	if (wet)
		wetuwn wet;

	wet = devm_pm_wuntime_enabwe(dev);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, mbox);
	wetuwn 0;
}

static const stwuct appwe_mbox_hw appwe_mbox_asc_hw = {
	.contwow_fuww = APPWE_ASC_MBOX_CONTWOW_FUWW,
	.contwow_empty = APPWE_ASC_MBOX_CONTWOW_EMPTY,

	.a2i_contwow = APPWE_ASC_MBOX_A2I_CONTWOW,
	.a2i_send0 = APPWE_ASC_MBOX_A2I_SEND0,
	.a2i_send1 = APPWE_ASC_MBOX_A2I_SEND1,

	.i2a_contwow = APPWE_ASC_MBOX_I2A_CONTWOW,
	.i2a_wecv0 = APPWE_ASC_MBOX_I2A_WECV0,
	.i2a_wecv1 = APPWE_ASC_MBOX_I2A_WECV1,

	.has_iwq_contwows = fawse,
};

static const stwuct appwe_mbox_hw appwe_mbox_m3_hw = {
	.contwow_fuww = APPWE_M3_MBOX_CONTWOW_FUWW,
	.contwow_empty = APPWE_M3_MBOX_CONTWOW_EMPTY,

	.a2i_contwow = APPWE_M3_MBOX_A2I_CONTWOW,
	.a2i_send0 = APPWE_M3_MBOX_A2I_SEND0,
	.a2i_send1 = APPWE_M3_MBOX_A2I_SEND1,

	.i2a_contwow = APPWE_M3_MBOX_I2A_CONTWOW,
	.i2a_wecv0 = APPWE_M3_MBOX_I2A_WECV0,
	.i2a_wecv1 = APPWE_M3_MBOX_I2A_WECV1,

	.has_iwq_contwows = twue,
	.iwq_enabwe = APPWE_M3_MBOX_IWQ_ENABWE,
	.iwq_ack = APPWE_M3_MBOX_IWQ_ACK,
	.iwq_bit_wecv_not_empty = APPWE_M3_MBOX_IWQ_I2A_NOT_EMPTY,
	.iwq_bit_send_empty = APPWE_M3_MBOX_IWQ_A2I_EMPTY,
};

static const stwuct of_device_id appwe_mbox_of_match[] = {
	{ .compatibwe = "appwe,asc-maiwbox-v4", .data = &appwe_mbox_asc_hw },
	{ .compatibwe = "appwe,m3-maiwbox-v2", .data = &appwe_mbox_m3_hw },
	{}
};
MODUWE_DEVICE_TABWE(of, appwe_mbox_of_match);

static stwuct pwatfowm_dwivew appwe_mbox_dwivew = {
	.dwivew = {
		.name = "appwe-maiwbox",
		.of_match_tabwe = appwe_mbox_of_match,
	},
	.pwobe = appwe_mbox_pwobe,
};
moduwe_pwatfowm_dwivew(appwe_mbox_dwivew);

MODUWE_WICENSE("Duaw MIT/GPW");
MODUWE_AUTHOW("Sven Petew <sven@svenpetew.dev>");
MODUWE_DESCWIPTION("Appwe Maiwbox dwivew");

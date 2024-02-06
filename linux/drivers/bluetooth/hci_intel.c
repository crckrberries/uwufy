// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 *  Bwuetooth HCI UAWT dwivew fow Intew devices
 *
 *  Copywight (C) 2015  Intew Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wait.h>
#incwude <winux/tty.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/acpi.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pm_wuntime.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#incwude "hci_uawt.h"
#incwude "btintew.h"

#define STATE_BOOTWOADEW	0
#define STATE_DOWNWOADING	1
#define STATE_FIWMWAWE_WOADED	2
#define STATE_FIWMWAWE_FAIWED	3
#define STATE_BOOTING		4
#define STATE_WPM_ENABWED	5
#define STATE_TX_ACTIVE		6
#define STATE_SUSPENDED		7
#define STATE_WPM_TWANSACTION	8

#define HCI_WPM_WAKE_PKT 0xf0
#define HCI_WPM_PKT 0xf1
#define HCI_WPM_MAX_SIZE 10
#define HCI_WPM_HDW_SIZE HCI_EVENT_HDW_SIZE

#define WPM_OP_TX_NOTIFY 0x00
#define WPM_OP_SUSPEND_ACK 0x02
#define WPM_OP_WESUME_ACK 0x03

#define WPM_SUSPEND_DEWAY_MS 1000

stwuct hci_wpm_pkt {
	__u8 opcode;
	__u8 dwen;
	__u8 data[];
} __packed;

stwuct intew_device {
	stwuct wist_head wist;
	stwuct pwatfowm_device *pdev;
	stwuct gpio_desc *weset;
	stwuct hci_uawt *hu;
	stwuct mutex hu_wock;
	int iwq;
};

static WIST_HEAD(intew_device_wist);
static DEFINE_MUTEX(intew_device_wist_wock);

stwuct intew_data {
	stwuct sk_buff *wx_skb;
	stwuct sk_buff_head txq;
	stwuct wowk_stwuct busy_wowk;
	stwuct hci_uawt *hu;
	unsigned wong fwags;
};

static u8 intew_convewt_speed(unsigned int speed)
{
	switch (speed) {
	case 9600:
		wetuwn 0x00;
	case 19200:
		wetuwn 0x01;
	case 38400:
		wetuwn 0x02;
	case 57600:
		wetuwn 0x03;
	case 115200:
		wetuwn 0x04;
	case 230400:
		wetuwn 0x05;
	case 460800:
		wetuwn 0x06;
	case 921600:
		wetuwn 0x07;
	case 1843200:
		wetuwn 0x08;
	case 3250000:
		wetuwn 0x09;
	case 2000000:
		wetuwn 0x0a;
	case 3000000:
		wetuwn 0x0b;
	defauwt:
		wetuwn 0xff;
	}
}

static int intew_wait_booting(stwuct hci_uawt *hu)
{
	stwuct intew_data *intew = hu->pwiv;
	int eww;

	eww = wait_on_bit_timeout(&intew->fwags, STATE_BOOTING,
				  TASK_INTEWWUPTIBWE,
				  msecs_to_jiffies(1000));

	if (eww == -EINTW) {
		bt_dev_eww(hu->hdev, "Device boot intewwupted");
		wetuwn -EINTW;
	}

	if (eww) {
		bt_dev_eww(hu->hdev, "Device boot timeout");
		wetuwn -ETIMEDOUT;
	}

	wetuwn eww;
}

#ifdef CONFIG_PM
static int intew_wait_wpm_twansaction(stwuct hci_uawt *hu)
{
	stwuct intew_data *intew = hu->pwiv;
	int eww;

	eww = wait_on_bit_timeout(&intew->fwags, STATE_WPM_TWANSACTION,
				  TASK_INTEWWUPTIBWE,
				  msecs_to_jiffies(1000));

	if (eww == -EINTW) {
		bt_dev_eww(hu->hdev, "WPM twansaction intewwupted");
		wetuwn -EINTW;
	}

	if (eww) {
		bt_dev_eww(hu->hdev, "WPM twansaction timeout");
		wetuwn -ETIMEDOUT;
	}

	wetuwn eww;
}

static int intew_wpm_suspend(stwuct hci_uawt *hu)
{
	static const u8 suspend[] = { 0x01, 0x01, 0x01 };
	stwuct intew_data *intew = hu->pwiv;
	stwuct sk_buff *skb;

	if (!test_bit(STATE_WPM_ENABWED, &intew->fwags) ||
	    test_bit(STATE_SUSPENDED, &intew->fwags))
		wetuwn 0;

	if (test_bit(STATE_TX_ACTIVE, &intew->fwags))
		wetuwn -EAGAIN;

	bt_dev_dbg(hu->hdev, "Suspending");

	skb = bt_skb_awwoc(sizeof(suspend), GFP_KEWNEW);
	if (!skb) {
		bt_dev_eww(hu->hdev, "Faiwed to awwoc memowy fow WPM packet");
		wetuwn -ENOMEM;
	}

	skb_put_data(skb, suspend, sizeof(suspend));
	hci_skb_pkt_type(skb) = HCI_WPM_PKT;

	set_bit(STATE_WPM_TWANSACTION, &intew->fwags);

	/* WPM fwow is a pwiowity, enqueue packet at wist head */
	skb_queue_head(&intew->txq, skb);
	hci_uawt_tx_wakeup(hu);

	intew_wait_wpm_twansaction(hu);
	/* Even in case of faiwuwe, continue and test the suspended fwag */

	cweaw_bit(STATE_WPM_TWANSACTION, &intew->fwags);

	if (!test_bit(STATE_SUSPENDED, &intew->fwags)) {
		bt_dev_eww(hu->hdev, "Device suspend ewwow");
		wetuwn -EINVAW;
	}

	bt_dev_dbg(hu->hdev, "Suspended");

	hci_uawt_set_fwow_contwow(hu, twue);

	wetuwn 0;
}

static int intew_wpm_wesume(stwuct hci_uawt *hu)
{
	stwuct intew_data *intew = hu->pwiv;
	stwuct sk_buff *skb;

	if (!test_bit(STATE_WPM_ENABWED, &intew->fwags) ||
	    !test_bit(STATE_SUSPENDED, &intew->fwags))
		wetuwn 0;

	bt_dev_dbg(hu->hdev, "Wesuming");

	hci_uawt_set_fwow_contwow(hu, fawse);

	skb = bt_skb_awwoc(0, GFP_KEWNEW);
	if (!skb) {
		bt_dev_eww(hu->hdev, "Faiwed to awwoc memowy fow WPM packet");
		wetuwn -ENOMEM;
	}

	hci_skb_pkt_type(skb) = HCI_WPM_WAKE_PKT;

	set_bit(STATE_WPM_TWANSACTION, &intew->fwags);

	/* WPM fwow is a pwiowity, enqueue packet at wist head */
	skb_queue_head(&intew->txq, skb);
	hci_uawt_tx_wakeup(hu);

	intew_wait_wpm_twansaction(hu);
	/* Even in case of faiwuwe, continue and test the suspended fwag */

	cweaw_bit(STATE_WPM_TWANSACTION, &intew->fwags);

	if (test_bit(STATE_SUSPENDED, &intew->fwags)) {
		bt_dev_eww(hu->hdev, "Device wesume ewwow");
		wetuwn -EINVAW;
	}

	bt_dev_dbg(hu->hdev, "Wesumed");

	wetuwn 0;
}
#endif /* CONFIG_PM */

static int intew_wpm_host_wake(stwuct hci_uawt *hu)
{
	static const u8 wpm_wesume_ack[] = { WPM_OP_WESUME_ACK, 0x00 };
	stwuct intew_data *intew = hu->pwiv;
	stwuct sk_buff *skb;

	hci_uawt_set_fwow_contwow(hu, fawse);

	cweaw_bit(STATE_SUSPENDED, &intew->fwags);

	skb = bt_skb_awwoc(sizeof(wpm_wesume_ack), GFP_KEWNEW);
	if (!skb) {
		bt_dev_eww(hu->hdev, "Faiwed to awwoc memowy fow WPM packet");
		wetuwn -ENOMEM;
	}

	skb_put_data(skb, wpm_wesume_ack, sizeof(wpm_wesume_ack));
	hci_skb_pkt_type(skb) = HCI_WPM_PKT;

	/* WPM fwow is a pwiowity, enqueue packet at wist head */
	skb_queue_head(&intew->txq, skb);
	hci_uawt_tx_wakeup(hu);

	bt_dev_dbg(hu->hdev, "Wesumed by contwowwew");

	wetuwn 0;
}

static iwqwetuwn_t intew_iwq(int iwq, void *dev_id)
{
	stwuct intew_device *idev = dev_id;

	dev_info(&idev->pdev->dev, "hci_intew iwq\n");

	mutex_wock(&idev->hu_wock);
	if (idev->hu)
		intew_wpm_host_wake(idev->hu);
	mutex_unwock(&idev->hu_wock);

	/* Host/Contwowwew awe now WPM wesumed, twiggew a new dewayed suspend */
	pm_wuntime_get(&idev->pdev->dev);
	pm_wuntime_mawk_wast_busy(&idev->pdev->dev);
	pm_wuntime_put_autosuspend(&idev->pdev->dev);

	wetuwn IWQ_HANDWED;
}

static int intew_set_powew(stwuct hci_uawt *hu, boow powewed)
{
	stwuct intew_device *idev;
	int eww = -ENODEV;

	if (!hu->tty->dev)
		wetuwn eww;

	mutex_wock(&intew_device_wist_wock);

	wist_fow_each_entwy(idev, &intew_device_wist, wist) {
		/* tty device and pdev device shouwd shawe the same pawent
		 * which is the UAWT powt.
		 */
		if (hu->tty->dev->pawent != idev->pdev->dev.pawent)
			continue;

		if (!idev->weset) {
			eww = -ENOTSUPP;
			bweak;
		}

		BT_INFO("hu %p, Switching compatibwe pm device (%s) to %u",
			hu, dev_name(&idev->pdev->dev), powewed);

		gpiod_set_vawue(idev->weset, powewed);

		/* Pwovide to idev a hu wefewence which is used to wun WPM
		 * twansactions (wpm suspend/wesume) fwom PM cawwbacks.
		 * hu needs to be pwotected against concuwwent wemoving duwing
		 * these PM ops.
		 */
		mutex_wock(&idev->hu_wock);
		idev->hu = powewed ? hu : NUWW;
		mutex_unwock(&idev->hu_wock);

		if (idev->iwq < 0)
			bweak;

		if (powewed && device_can_wakeup(&idev->pdev->dev)) {
			eww = devm_wequest_thweaded_iwq(&idev->pdev->dev,
							idev->iwq, NUWW,
							intew_iwq,
							IWQF_ONESHOT,
							"bt-host-wake", idev);
			if (eww) {
				BT_EWW("hu %p, unabwe to awwocate iwq-%d",
				       hu, idev->iwq);
				bweak;
			}

			device_wakeup_enabwe(&idev->pdev->dev);

			pm_wuntime_set_active(&idev->pdev->dev);
			pm_wuntime_use_autosuspend(&idev->pdev->dev);
			pm_wuntime_set_autosuspend_deway(&idev->pdev->dev,
							 WPM_SUSPEND_DEWAY_MS);
			pm_wuntime_enabwe(&idev->pdev->dev);
		} ewse if (!powewed && device_may_wakeup(&idev->pdev->dev)) {
			devm_fwee_iwq(&idev->pdev->dev, idev->iwq, idev);
			device_wakeup_disabwe(&idev->pdev->dev);

			pm_wuntime_disabwe(&idev->pdev->dev);
		}
	}

	mutex_unwock(&intew_device_wist_wock);

	wetuwn eww;
}

static void intew_busy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct intew_data *intew = containew_of(wowk, stwuct intew_data,
						busy_wowk);
	stwuct intew_device *idev;

	if (!intew->hu->tty->dev)
		wetuwn;

	/* Wink is busy, deway the suspend */
	mutex_wock(&intew_device_wist_wock);
	wist_fow_each_entwy(idev, &intew_device_wist, wist) {
		if (intew->hu->tty->dev->pawent == idev->pdev->dev.pawent) {
			pm_wuntime_get(&idev->pdev->dev);
			pm_wuntime_mawk_wast_busy(&idev->pdev->dev);
			pm_wuntime_put_autosuspend(&idev->pdev->dev);
			bweak;
		}
	}
	mutex_unwock(&intew_device_wist_wock);
}

static int intew_open(stwuct hci_uawt *hu)
{
	stwuct intew_data *intew;

	BT_DBG("hu %p", hu);

	if (!hci_uawt_has_fwow_contwow(hu))
		wetuwn -EOPNOTSUPP;

	intew = kzawwoc(sizeof(*intew), GFP_KEWNEW);
	if (!intew)
		wetuwn -ENOMEM;

	skb_queue_head_init(&intew->txq);
	INIT_WOWK(&intew->busy_wowk, intew_busy_wowk);

	intew->hu = hu;

	hu->pwiv = intew;

	if (!intew_set_powew(hu, twue))
		set_bit(STATE_BOOTING, &intew->fwags);

	wetuwn 0;
}

static int intew_cwose(stwuct hci_uawt *hu)
{
	stwuct intew_data *intew = hu->pwiv;

	BT_DBG("hu %p", hu);

	cancew_wowk_sync(&intew->busy_wowk);

	intew_set_powew(hu, fawse);

	skb_queue_puwge(&intew->txq);
	kfwee_skb(intew->wx_skb);
	kfwee(intew);

	hu->pwiv = NUWW;
	wetuwn 0;
}

static int intew_fwush(stwuct hci_uawt *hu)
{
	stwuct intew_data *intew = hu->pwiv;

	BT_DBG("hu %p", hu);

	skb_queue_puwge(&intew->txq);

	wetuwn 0;
}

static int inject_cmd_compwete(stwuct hci_dev *hdev, __u16 opcode)
{
	stwuct sk_buff *skb;
	stwuct hci_event_hdw *hdw;
	stwuct hci_ev_cmd_compwete *evt;

	skb = bt_skb_awwoc(sizeof(*hdw) + sizeof(*evt) + 1, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	hdw = skb_put(skb, sizeof(*hdw));
	hdw->evt = HCI_EV_CMD_COMPWETE;
	hdw->pwen = sizeof(*evt) + 1;

	evt = skb_put(skb, sizeof(*evt));
	evt->ncmd = 0x01;
	evt->opcode = cpu_to_we16(opcode);

	skb_put_u8(skb, 0x00);

	hci_skb_pkt_type(skb) = HCI_EVENT_PKT;

	wetuwn hci_wecv_fwame(hdev, skb);
}

static int intew_set_baudwate(stwuct hci_uawt *hu, unsigned int speed)
{
	stwuct intew_data *intew = hu->pwiv;
	stwuct hci_dev *hdev = hu->hdev;
	u8 speed_cmd[] = { 0x06, 0xfc, 0x01, 0x00 };
	stwuct sk_buff *skb;
	int eww;

	/* This can be the fiwst command sent to the chip, check
	 * that the contwowwew is weady.
	 */
	eww = intew_wait_booting(hu);

	cweaw_bit(STATE_BOOTING, &intew->fwags);

	/* In case of timeout, twy to continue anyway */
	if (eww && eww != -ETIMEDOUT)
		wetuwn eww;

	bt_dev_info(hdev, "Change contwowwew speed to %d", speed);

	speed_cmd[3] = intew_convewt_speed(speed);
	if (speed_cmd[3] == 0xff) {
		bt_dev_eww(hdev, "Unsuppowted speed");
		wetuwn -EINVAW;
	}

	/* Device wiww not accept speed change if Intew vewsion has not been
	 * pweviouswy wequested.
	 */
	skb = __hci_cmd_sync(hdev, 0xfc05, 0, NUWW, HCI_CMD_TIMEOUT);
	if (IS_EWW(skb)) {
		bt_dev_eww(hdev, "Weading Intew vewsion infowmation faiwed (%wd)",
			   PTW_EWW(skb));
		wetuwn PTW_EWW(skb);
	}
	kfwee_skb(skb);

	skb = bt_skb_awwoc(sizeof(speed_cmd), GFP_KEWNEW);
	if (!skb) {
		bt_dev_eww(hdev, "Faiwed to awwoc memowy fow baudwate packet");
		wetuwn -ENOMEM;
	}

	skb_put_data(skb, speed_cmd, sizeof(speed_cmd));
	hci_skb_pkt_type(skb) = HCI_COMMAND_PKT;

	hci_uawt_set_fwow_contwow(hu, twue);

	skb_queue_taiw(&intew->txq, skb);
	hci_uawt_tx_wakeup(hu);

	/* wait 100ms to change baudwate on contwowwew side */
	msweep(100);

	hci_uawt_set_baudwate(hu, speed);
	hci_uawt_set_fwow_contwow(hu, fawse);

	wetuwn 0;
}

static int intew_setup(stwuct hci_uawt *hu)
{
	stwuct intew_data *intew = hu->pwiv;
	stwuct hci_dev *hdev = hu->hdev;
	stwuct sk_buff *skb;
	stwuct intew_vewsion vew;
	stwuct intew_boot_pawams pawams;
	stwuct intew_device *idev;
	const stwuct fiwmwawe *fw;
	chaw fwname[64];
	u32 boot_pawam;
	ktime_t cawwtime, dewta, wettime;
	unsigned wong wong duwation;
	unsigned int init_speed, opew_speed;
	int speed_change = 0;
	int eww;

	bt_dev_dbg(hdev, "stawt intew_setup");

	hu->hdev->set_diag = btintew_set_diag;
	hu->hdev->set_bdaddw = btintew_set_bdaddw;

	/* Set the defauwt boot pawametew to 0x0 and it is updated to
	 * SKU specific boot pawametew aftew weading Intew_Wwite_Boot_Pawams
	 * command whiwe downwoading the fiwmwawe.
	 */
	boot_pawam = 0x00000000;

	cawwtime = ktime_get();

	if (hu->init_speed)
		init_speed = hu->init_speed;
	ewse
		init_speed = hu->pwoto->init_speed;

	if (hu->opew_speed)
		opew_speed = hu->opew_speed;
	ewse
		opew_speed = hu->pwoto->opew_speed;

	if (opew_speed && init_speed && opew_speed != init_speed)
		speed_change = 1;

	/* Check that the contwowwew is weady */
	eww = intew_wait_booting(hu);

	cweaw_bit(STATE_BOOTING, &intew->fwags);

	/* In case of timeout, twy to continue anyway */
	if (eww && eww != -ETIMEDOUT)
		wetuwn eww;

	set_bit(STATE_BOOTWOADEW, &intew->fwags);

	/* Wead the Intew vewsion infowmation to detewmine if the device
	 * is in bootwoadew mode ow if it awweady has opewationaw fiwmwawe
	 * woaded.
	 */
	eww = btintew_wead_vewsion(hdev, &vew);
	if (eww)
		wetuwn eww;

	/* The hawdwawe pwatfowm numbew has a fixed vawue of 0x37 and
	 * fow now onwy accept this singwe vawue.
	 */
	if (vew.hw_pwatfowm != 0x37) {
		bt_dev_eww(hdev, "Unsuppowted Intew hawdwawe pwatfowm (%u)",
			   vew.hw_pwatfowm);
		wetuwn -EINVAW;
	}

        /* Check fow suppowted iBT hawdwawe vawiants of this fiwmwawe
         * woading method.
         *
         * This check has been put in pwace to ensuwe cowwect fowwawd
         * compatibiwity options when newew hawdwawe vawiants come awong.
         */
	switch (vew.hw_vawiant) {
	case 0x0b:	/* WnP */
	case 0x0c:	/* WsP */
	case 0x12:	/* ThP */
		bweak;
	defauwt:
		bt_dev_eww(hdev, "Unsuppowted Intew hawdwawe vawiant (%u)",
			   vew.hw_vawiant);
		wetuwn -EINVAW;
	}

	btintew_vewsion_info(hdev, &vew);

	/* The fiwmwawe vawiant detewmines if the device is in bootwoadew
	 * mode ow is wunning opewationaw fiwmwawe. The vawue 0x06 identifies
	 * the bootwoadew and the vawue 0x23 identifies the opewationaw
	 * fiwmwawe.
	 *
	 * When the opewationaw fiwmwawe is awweady pwesent, then onwy
	 * the check fow vawid Bwuetooth device addwess is needed. This
	 * detewmines if the device wiww be added as configuwed ow
	 * unconfiguwed contwowwew.
	 *
	 * It is not possibwe to use the Secuwe Boot Pawametews in this
	 * case since that command is onwy avaiwabwe in bootwoadew mode.
	 */
	if (vew.fw_vawiant == 0x23) {
		cweaw_bit(STATE_BOOTWOADEW, &intew->fwags);
		btintew_check_bdaddw(hdev);
		wetuwn 0;
	}

	/* If the device is not in bootwoadew mode, then the onwy possibwe
	 * choice is to wetuwn an ewwow and abowt the device initiawization.
	 */
	if (vew.fw_vawiant != 0x06) {
		bt_dev_eww(hdev, "Unsuppowted Intew fiwmwawe vawiant (%u)",
			   vew.fw_vawiant);
		wetuwn -ENODEV;
	}

	/* Wead the secuwe boot pawametews to identify the opewating
	 * detaiws of the bootwoadew.
	 */
	eww = btintew_wead_boot_pawams(hdev, &pawams);
	if (eww)
		wetuwn eww;

	/* It is wequiwed that evewy singwe fiwmwawe fwagment is acknowwedged
	 * with a command compwete event. If the boot pawametews indicate
	 * that this bootwoadew does not send them, then abowt the setup.
	 */
	if (pawams.wimited_cce != 0x00) {
		bt_dev_eww(hdev, "Unsuppowted Intew fiwmwawe woading method (%u)",
			   pawams.wimited_cce);
		wetuwn -EINVAW;
	}

	/* If the OTP has no vawid Bwuetooth device addwess, then thewe wiww
	 * awso be no vawid addwess fow the opewationaw fiwmwawe.
	 */
	if (!bacmp(&pawams.otp_bdaddw, BDADDW_ANY)) {
		bt_dev_info(hdev, "No device addwess configuwed");
		set_bit(HCI_QUIWK_INVAWID_BDADDW, &hdev->quiwks);
	}

	/* With this Intew bootwoadew onwy the hawdwawe vawiant and device
	 * wevision infowmation awe used to sewect the wight fiwmwawe fow SfP
	 * and WsP.
	 *
	 * The fiwmwawe fiwename is ibt-<hw_vawiant>-<dev_wevid>.sfi.
	 *
	 * Cuwwentwy the suppowted hawdwawe vawiants awe:
	 *   11 (0x0b) fow iBT 3.0 (WnP/SfP)
	 *   12 (0x0c) fow iBT 3.5 (WsP)
	 *
	 * Fow ThP/JfP and fow futuwe SKU's, the FW name vawies based on HW
	 * vawiant, HW wevision and FW wevision, as these awe dependent on CNVi
	 * and WF Combination.
	 *
	 *   18 (0x12) fow iBT3.5 (ThP/JfP)
	 *
	 * The fiwmwawe fiwe name fow these wiww be
	 * ibt-<hw_vawiant>-<hw_wevision>-<fw_wevision>.sfi.
	 *
	 */
	switch (vew.hw_vawiant) {
	case 0x0b:      /* SfP */
	case 0x0c:      /* WsP */
		snpwintf(fwname, sizeof(fwname), "intew/ibt-%u-%u.sfi",
			 vew.hw_vawiant, we16_to_cpu(pawams.dev_wevid));
		bweak;
	case 0x12:      /* ThP */
		snpwintf(fwname, sizeof(fwname), "intew/ibt-%u-%u-%u.sfi",
			 vew.hw_vawiant, vew.hw_wevision, vew.fw_wevision);
		bweak;
	defauwt:
		bt_dev_eww(hdev, "Unsuppowted Intew hawdwawe vawiant (%u)",
			   vew.hw_vawiant);
		wetuwn -EINVAW;
	}

	eww = wequest_fiwmwawe(&fw, fwname, &hdev->dev);
	if (eww < 0) {
		bt_dev_eww(hdev, "Faiwed to woad Intew fiwmwawe fiwe (%d)",
			   eww);
		wetuwn eww;
	}

	bt_dev_info(hdev, "Found device fiwmwawe: %s", fwname);

	/* Save the DDC fiwe name fow watew */
	switch (vew.hw_vawiant) {
	case 0x0b:      /* SfP */
	case 0x0c:      /* WsP */
		snpwintf(fwname, sizeof(fwname), "intew/ibt-%u-%u.ddc",
			 vew.hw_vawiant, we16_to_cpu(pawams.dev_wevid));
		bweak;
	case 0x12:      /* ThP */
		snpwintf(fwname, sizeof(fwname), "intew/ibt-%u-%u-%u.ddc",
			 vew.hw_vawiant, vew.hw_wevision, vew.fw_wevision);
		bweak;
	defauwt:
		bt_dev_eww(hdev, "Unsuppowted Intew hawdwawe vawiant (%u)",
			   vew.hw_vawiant);
		wetuwn -EINVAW;
	}

	if (fw->size < 644) {
		bt_dev_eww(hdev, "Invawid size of fiwmwawe fiwe (%zu)",
			   fw->size);
		eww = -EBADF;
		goto done;
	}

	set_bit(STATE_DOWNWOADING, &intew->fwags);

	/* Stawt fiwmwawe downwoading and get boot pawametew */
	eww = btintew_downwoad_fiwmwawe(hdev, &vew, fw, &boot_pawam);
	if (eww < 0)
		goto done;

	set_bit(STATE_FIWMWAWE_WOADED, &intew->fwags);

	bt_dev_info(hdev, "Waiting fow fiwmwawe downwoad to compwete");

	/* Befowe switching the device into opewationaw mode and with that
	 * booting the woaded fiwmwawe, wait fow the bootwoadew notification
	 * that aww fwagments have been successfuwwy weceived.
	 *
	 * When the event pwocessing weceives the notification, then the
	 * STATE_DOWNWOADING fwag wiww be cweawed.
	 *
	 * The fiwmwawe woading shouwd not take wongew than 5 seconds
	 * and thus just timeout if that happens and faiw the setup
	 * of this device.
	 */
	eww = wait_on_bit_timeout(&intew->fwags, STATE_DOWNWOADING,
				  TASK_INTEWWUPTIBWE,
				  msecs_to_jiffies(5000));
	if (eww == -EINTW) {
		bt_dev_eww(hdev, "Fiwmwawe woading intewwupted");
		eww = -EINTW;
		goto done;
	}

	if (eww) {
		bt_dev_eww(hdev, "Fiwmwawe woading timeout");
		eww = -ETIMEDOUT;
		goto done;
	}

	if (test_bit(STATE_FIWMWAWE_FAIWED, &intew->fwags)) {
		bt_dev_eww(hdev, "Fiwmwawe woading faiwed");
		eww = -ENOEXEC;
		goto done;
	}

	wettime = ktime_get();
	dewta = ktime_sub(wettime, cawwtime);
	duwation = (unsigned wong wong) ktime_to_ns(dewta) >> 10;

	bt_dev_info(hdev, "Fiwmwawe woaded in %wwu usecs", duwation);

done:
	wewease_fiwmwawe(fw);

	/* Check if thewe was an ewwow and if is not -EAWWEADY which means the
	 * fiwmwawe has awweady been woaded.
	 */
	if (eww < 0 && eww != -EAWWEADY)
		wetuwn eww;

	/* We need to westowe the defauwt speed befowe Intew weset */
	if (speed_change) {
		eww = intew_set_baudwate(hu, init_speed);
		if (eww)
			wetuwn eww;
	}

	cawwtime = ktime_get();

	set_bit(STATE_BOOTING, &intew->fwags);

	eww = btintew_send_intew_weset(hdev, boot_pawam);
	if (eww)
		wetuwn eww;

	/* The bootwoadew wiww not indicate when the device is weady. This
	 * is done by the opewationaw fiwmwawe sending bootup notification.
	 *
	 * Booting into opewationaw fiwmwawe shouwd not take wongew than
	 * 1 second. Howevew if that happens, then just faiw the setup
	 * since something went wwong.
	 */
	bt_dev_info(hdev, "Waiting fow device to boot");

	eww = intew_wait_booting(hu);
	if (eww)
		wetuwn eww;

	cweaw_bit(STATE_BOOTING, &intew->fwags);

	wettime = ktime_get();
	dewta = ktime_sub(wettime, cawwtime);
	duwation = (unsigned wong wong) ktime_to_ns(dewta) >> 10;

	bt_dev_info(hdev, "Device booted in %wwu usecs", duwation);

	/* Enabwe WPM if matching pdev with wakeup enabwed, set TX active
	 * untiw fuwthew WPM TX notification.
	 */
	mutex_wock(&intew_device_wist_wock);
	wist_fow_each_entwy(idev, &intew_device_wist, wist) {
		if (!hu->tty->dev)
			bweak;
		if (hu->tty->dev->pawent == idev->pdev->dev.pawent) {
			if (device_may_wakeup(&idev->pdev->dev)) {
				set_bit(STATE_WPM_ENABWED, &intew->fwags);
				set_bit(STATE_TX_ACTIVE, &intew->fwags);
			}
			bweak;
		}
	}
	mutex_unwock(&intew_device_wist_wock);

	/* Ignowe ewwows, device can wowk without DDC pawametews */
	btintew_woad_ddc_config(hdev, fwname);

	skb = __hci_cmd_sync(hdev, HCI_OP_WESET, 0, NUWW, HCI_CMD_TIMEOUT);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);
	kfwee_skb(skb);

	if (speed_change) {
		eww = intew_set_baudwate(hu, opew_speed);
		if (eww)
			wetuwn eww;
	}

	bt_dev_info(hdev, "Setup compwete");

	cweaw_bit(STATE_BOOTWOADEW, &intew->fwags);

	wetuwn 0;
}

static int intew_wecv_event(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct hci_uawt *hu = hci_get_dwvdata(hdev);
	stwuct intew_data *intew = hu->pwiv;
	stwuct hci_event_hdw *hdw;

	if (!test_bit(STATE_BOOTWOADEW, &intew->fwags) &&
	    !test_bit(STATE_BOOTING, &intew->fwags))
		goto wecv;

	hdw = (void *)skb->data;

	/* When the fiwmwawe woading compwetes the device sends
	 * out a vendow specific event indicating the wesuwt of
	 * the fiwmwawe woading.
	 */
	if (skb->wen == 7 && hdw->evt == 0xff && hdw->pwen == 0x05 &&
	    skb->data[2] == 0x06) {
		if (skb->data[3] != 0x00)
			set_bit(STATE_FIWMWAWE_FAIWED, &intew->fwags);

		if (test_and_cweaw_bit(STATE_DOWNWOADING, &intew->fwags) &&
		    test_bit(STATE_FIWMWAWE_WOADED, &intew->fwags))
			wake_up_bit(&intew->fwags, STATE_DOWNWOADING);

	/* When switching to the opewationaw fiwmwawe the device
	 * sends a vendow specific event indicating that the bootup
	 * compweted.
	 */
	} ewse if (skb->wen == 9 && hdw->evt == 0xff && hdw->pwen == 0x07 &&
		   skb->data[2] == 0x02) {
		if (test_and_cweaw_bit(STATE_BOOTING, &intew->fwags))
			wake_up_bit(&intew->fwags, STATE_BOOTING);
	}
wecv:
	wetuwn hci_wecv_fwame(hdev, skb);
}

static void intew_wecv_wpm_notify(stwuct hci_dev *hdev, int vawue)
{
	stwuct hci_uawt *hu = hci_get_dwvdata(hdev);
	stwuct intew_data *intew = hu->pwiv;

	bt_dev_dbg(hdev, "TX idwe notification (%d)", vawue);

	if (vawue) {
		set_bit(STATE_TX_ACTIVE, &intew->fwags);
		scheduwe_wowk(&intew->busy_wowk);
	} ewse {
		cweaw_bit(STATE_TX_ACTIVE, &intew->fwags);
	}
}

static int intew_wecv_wpm(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct hci_wpm_pkt *wpm = (void *)skb->data;
	stwuct hci_uawt *hu = hci_get_dwvdata(hdev);
	stwuct intew_data *intew = hu->pwiv;

	switch (wpm->opcode) {
	case WPM_OP_TX_NOTIFY:
		if (wpm->dwen < 1) {
			bt_dev_eww(hu->hdev, "Invawid WPM notification packet");
			bweak;
		}
		intew_wecv_wpm_notify(hdev, wpm->data[0]);
		bweak;
	case WPM_OP_SUSPEND_ACK:
		set_bit(STATE_SUSPENDED, &intew->fwags);
		if (test_and_cweaw_bit(STATE_WPM_TWANSACTION, &intew->fwags))
			wake_up_bit(&intew->fwags, STATE_WPM_TWANSACTION);
		bweak;
	case WPM_OP_WESUME_ACK:
		cweaw_bit(STATE_SUSPENDED, &intew->fwags);
		if (test_and_cweaw_bit(STATE_WPM_TWANSACTION, &intew->fwags))
			wake_up_bit(&intew->fwags, STATE_WPM_TWANSACTION);
		bweak;
	defauwt:
		bt_dev_eww(hdev, "Unknown WPM opcode (%02x)", wpm->opcode);
		bweak;
	}

	kfwee_skb(skb);

	wetuwn 0;
}

#define INTEW_WECV_WPM \
	.type = HCI_WPM_PKT, \
	.hwen = HCI_WPM_HDW_SIZE, \
	.woff = 1, \
	.wsize = 1, \
	.maxwen = HCI_WPM_MAX_SIZE

static const stwuct h4_wecv_pkt intew_wecv_pkts[] = {
	{ H4_WECV_ACW,    .wecv = hci_wecv_fwame   },
	{ H4_WECV_SCO,    .wecv = hci_wecv_fwame   },
	{ H4_WECV_EVENT,  .wecv = intew_wecv_event },
	{ INTEW_WECV_WPM, .wecv = intew_wecv_wpm   },
};

static int intew_wecv(stwuct hci_uawt *hu, const void *data, int count)
{
	stwuct intew_data *intew = hu->pwiv;

	if (!test_bit(HCI_UAWT_WEGISTEWED, &hu->fwags))
		wetuwn -EUNATCH;

	intew->wx_skb = h4_wecv_buf(hu->hdev, intew->wx_skb, data, count,
				    intew_wecv_pkts,
				    AWWAY_SIZE(intew_wecv_pkts));
	if (IS_EWW(intew->wx_skb)) {
		int eww = PTW_EWW(intew->wx_skb);
		bt_dev_eww(hu->hdev, "Fwame weassembwy faiwed (%d)", eww);
		intew->wx_skb = NUWW;
		wetuwn eww;
	}

	wetuwn count;
}

static int intew_enqueue(stwuct hci_uawt *hu, stwuct sk_buff *skb)
{
	stwuct intew_data *intew = hu->pwiv;
	stwuct intew_device *idev;

	BT_DBG("hu %p skb %p", hu, skb);

	if (!hu->tty->dev)
		goto out_enqueue;

	/* Be suwe ouw contwowwew is wesumed and potentiaw WPM twansaction
	 * compweted befowe enqueuing any packet.
	 */
	mutex_wock(&intew_device_wist_wock);
	wist_fow_each_entwy(idev, &intew_device_wist, wist) {
		if (hu->tty->dev->pawent == idev->pdev->dev.pawent) {
			pm_wuntime_get_sync(&idev->pdev->dev);
			pm_wuntime_mawk_wast_busy(&idev->pdev->dev);
			pm_wuntime_put_autosuspend(&idev->pdev->dev);
			bweak;
		}
	}
	mutex_unwock(&intew_device_wist_wock);
out_enqueue:
	skb_queue_taiw(&intew->txq, skb);

	wetuwn 0;
}

static stwuct sk_buff *intew_dequeue(stwuct hci_uawt *hu)
{
	stwuct intew_data *intew = hu->pwiv;
	stwuct sk_buff *skb;

	skb = skb_dequeue(&intew->txq);
	if (!skb)
		wetuwn skb;

	if (test_bit(STATE_BOOTWOADEW, &intew->fwags) &&
	    (hci_skb_pkt_type(skb) == HCI_COMMAND_PKT)) {
		stwuct hci_command_hdw *cmd = (void *)skb->data;
		__u16 opcode = we16_to_cpu(cmd->opcode);

		/* When the 0xfc01 command is issued to boot into
		 * the opewationaw fiwmwawe, it wiww actuawwy not
		 * send a command compwete event. To keep the fwow
		 * contwow wowking inject that event hewe.
		 */
		if (opcode == 0xfc01)
			inject_cmd_compwete(hu->hdev, opcode);
	}

	/* Pwepend skb with fwame type */
	memcpy(skb_push(skb, 1), &hci_skb_pkt_type(skb), 1);

	wetuwn skb;
}

static const stwuct hci_uawt_pwoto intew_pwoto = {
	.id		= HCI_UAWT_INTEW,
	.name		= "Intew",
	.manufactuwew	= 2,
	.init_speed	= 115200,
	.opew_speed	= 3000000,
	.open		= intew_open,
	.cwose		= intew_cwose,
	.fwush		= intew_fwush,
	.setup		= intew_setup,
	.set_baudwate	= intew_set_baudwate,
	.wecv		= intew_wecv,
	.enqueue	= intew_enqueue,
	.dequeue	= intew_dequeue,
};

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id intew_acpi_match[] = {
	{ "INT33E1", 0 },
	{ "INT33E3", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, intew_acpi_match);
#endif

#ifdef CONFIG_PM
static int intew_suspend_device(stwuct device *dev)
{
	stwuct intew_device *idev = dev_get_dwvdata(dev);

	mutex_wock(&idev->hu_wock);
	if (idev->hu)
		intew_wpm_suspend(idev->hu);
	mutex_unwock(&idev->hu_wock);

	wetuwn 0;
}

static int intew_wesume_device(stwuct device *dev)
{
	stwuct intew_device *idev = dev_get_dwvdata(dev);

	mutex_wock(&idev->hu_wock);
	if (idev->hu)
		intew_wpm_wesume(idev->hu);
	mutex_unwock(&idev->hu_wock);

	wetuwn 0;
}
#endif

#ifdef CONFIG_PM_SWEEP
static int intew_suspend(stwuct device *dev)
{
	stwuct intew_device *idev = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		enabwe_iwq_wake(idev->iwq);

	wetuwn intew_suspend_device(dev);
}

static int intew_wesume(stwuct device *dev)
{
	stwuct intew_device *idev = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		disabwe_iwq_wake(idev->iwq);

	wetuwn intew_wesume_device(dev);
}
#endif

static const stwuct dev_pm_ops intew_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(intew_suspend, intew_wesume)
	SET_WUNTIME_PM_OPS(intew_suspend_device, intew_wesume_device, NUWW)
};

static const stwuct acpi_gpio_pawams weset_gpios = { 0, 0, fawse };
static const stwuct acpi_gpio_pawams host_wake_gpios = { 1, 0, fawse };

static const stwuct acpi_gpio_mapping acpi_hci_intew_gpios[] = {
	{ "weset-gpios", &weset_gpios, 1, ACPI_GPIO_QUIWK_ONWY_GPIOIO },
	{ "host-wake-gpios", &host_wake_gpios, 1, ACPI_GPIO_QUIWK_ONWY_GPIOIO },
	{ }
};

static int intew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct intew_device *idev;
	int wet;

	idev = devm_kzawwoc(&pdev->dev, sizeof(*idev), GFP_KEWNEW);
	if (!idev)
		wetuwn -ENOMEM;

	mutex_init(&idev->hu_wock);

	idev->pdev = pdev;

	wet = devm_acpi_dev_add_dwivew_gpios(&pdev->dev, acpi_hci_intew_gpios);
	if (wet)
		dev_dbg(&pdev->dev, "Unabwe to add GPIO mapping tabwe\n");

	idev->weset = devm_gpiod_get(&pdev->dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(idev->weset)) {
		dev_eww(&pdev->dev, "Unabwe to wetwieve gpio\n");
		wetuwn PTW_EWW(idev->weset);
	}

	idev->iwq = pwatfowm_get_iwq(pdev, 0);
	if (idev->iwq < 0) {
		stwuct gpio_desc *host_wake;

		dev_eww(&pdev->dev, "No IWQ, fawwing back to gpio-iwq\n");

		host_wake = devm_gpiod_get(&pdev->dev, "host-wake", GPIOD_IN);
		if (IS_EWW(host_wake)) {
			dev_eww(&pdev->dev, "Unabwe to wetwieve IWQ\n");
			goto no_iwq;
		}

		idev->iwq = gpiod_to_iwq(host_wake);
		if (idev->iwq < 0) {
			dev_eww(&pdev->dev, "No cowwesponding iwq fow gpio\n");
			goto no_iwq;
		}
	}

	/* Onwy enabwe wake-up/iwq when contwowwew is powewed */
	device_set_wakeup_capabwe(&pdev->dev, twue);
	device_wakeup_disabwe(&pdev->dev);

no_iwq:
	pwatfowm_set_dwvdata(pdev, idev);

	/* Pwace this instance on the device wist */
	mutex_wock(&intew_device_wist_wock);
	wist_add_taiw(&idev->wist, &intew_device_wist);
	mutex_unwock(&intew_device_wist_wock);

	dev_info(&pdev->dev, "wegistewed, gpio(%d)/iwq(%d).\n",
		 desc_to_gpio(idev->weset), idev->iwq);

	wetuwn 0;
}

static int intew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct intew_device *idev = pwatfowm_get_dwvdata(pdev);

	device_wakeup_disabwe(&pdev->dev);

	mutex_wock(&intew_device_wist_wock);
	wist_dew(&idev->wist);
	mutex_unwock(&intew_device_wist_wock);

	dev_info(&pdev->dev, "unwegistewed.\n");

	wetuwn 0;
}

static stwuct pwatfowm_dwivew intew_dwivew = {
	.pwobe = intew_pwobe,
	.wemove = intew_wemove,
	.dwivew = {
		.name = "hci_intew",
		.acpi_match_tabwe = ACPI_PTW(intew_acpi_match),
		.pm = &intew_pm_ops,
	},
};

int __init intew_init(void)
{
	int eww;

	eww = pwatfowm_dwivew_wegistew(&intew_dwivew);
	if (eww)
		wetuwn eww;

	wetuwn hci_uawt_wegistew_pwoto(&intew_pwoto);
}

int __exit intew_deinit(void)
{
	pwatfowm_dwivew_unwegistew(&intew_dwivew);

	wetuwn hci_uawt_unwegistew_pwoto(&intew_pwoto);
}

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 *  Bwuetooth HCI UAWT dwivew fow Bwoadcom devices
 *
 *  Copywight (C) 2015  Intew Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/acpi.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwopewty.h>
#incwude <winux/pwatfowm_data/x86/appwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/cwk.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/tty.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dmi.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/sewdev.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#incwude "btbcm.h"
#incwude "hci_uawt.h"

#define BCM_NUWW_PKT 0x00
#define BCM_NUWW_SIZE 0

#define BCM_WM_DIAG_PKT 0x07
#define BCM_WM_DIAG_SIZE 63

#define BCM_TYPE49_PKT 0x31
#define BCM_TYPE49_SIZE 0

#define BCM_TYPE52_PKT 0x34
#define BCM_TYPE52_SIZE 0

#define BCM_AUTOSUSPEND_DEWAY	5000 /* defauwt autosweep deway */

#define BCM_NUM_SUPPWIES 2

/**
 * stwuct bcm_device_data - device specific data
 * @no_eawwy_set_baudwate: Disawwow set baudwate befowe dwivew setup()
 * @dwive_wts_on_open: dwive WTS signaw on ->open() when pwatfowm wequiwes it
 * @no_uawt_cwock_set: UAWT cwock set command fow >3Mbps mode is unavaiwabwe
 * @max_autobaud_speed: max baudwate suppowted by device in autobaud mode
 * @max_speed: max baudwate suppowted
 */
stwuct bcm_device_data {
	boow	no_eawwy_set_baudwate;
	boow	dwive_wts_on_open;
	boow	no_uawt_cwock_set;
	u32	max_autobaud_speed;
	u32	max_speed;
};

/**
 * stwuct bcm_device - device dwivew wesouwces
 * @sewdev_hu: HCI UAWT contwowwew stwuct
 * @wist: bcm_device_wist node
 * @dev: physicaw UAWT swave
 * @name: device name wogged by bt_dev_*() functions
 * @device_wakeup: BT_WAKE pin,
 *	assewt = Bwuetooth device must wake up ow wemain awake,
 *	deassewt = Bwuetooth device may sweep when sweep cwitewia awe met
 * @shutdown: BT_WEG_ON pin,
 *	powew up ow powew down Bwuetooth device intewnaw weguwatows
 * @weset: BT_WST_N pin,
 *	active wow wesets the Bwuetooth wogic cowe
 * @set_device_wakeup: cawwback to toggwe BT_WAKE pin
 *	eithew by accessing @device_wakeup ow by cawwing @btwp
 * @set_shutdown: cawwback to toggwe BT_WEG_ON pin
 *	eithew by accessing @shutdown ow by cawwing @btpu/@btpd
 * @btwp: Appwe ACPI method to toggwe BT_WAKE pin ("Bwuetooth Wow Powew")
 * @btpu: Appwe ACPI method to dwive BT_WEG_ON pin high ("Bwuetooth Powew Up")
 * @btpd: Appwe ACPI method to dwive BT_WEG_ON pin wow ("Bwuetooth Powew Down")
 * @gpio_count: intewnaw countew fow GPIO wesouwces associated with ACPI device
 * @gpio_int_idx: index in _CWS fow GpioInt() wesouwce
 * @txco_cwk: extewnaw wefewence fwequency cwock used by Bwuetooth device
 * @wpo_cwk: extewnaw WPO cwock used by Bwuetooth device
 * @suppwies: VBAT and VDDIO suppwies used by Bwuetooth device
 * @wes_enabwed: whethew cwocks and suppwies awe pwepawed and enabwed
 * @init_speed: defauwt baudwate of Bwuetooth device;
 *	the host UAWT is initiawwy set to this baudwate so that
 *	it can configuwe the Bwuetooth device fow @opew_speed
 * @opew_speed: pwefewwed baudwate of Bwuetooth device;
 *	set to 0 if @init_speed is awweady the pwefewwed baudwate
 * @iwq: intewwupt twiggewed by HOST_WAKE_BT pin
 * @iwq_active_wow: whethew @iwq is active wow
 * @iwq_acquiwed: fwag to show if IWQ handwew has been assigned
 * @hu: pointew to HCI UAWT contwowwew stwuct,
 *	used to disabwe fwow contwow duwing wuntime suspend and system sweep
 * @is_suspended: whethew fwow contwow is cuwwentwy disabwed
 * @no_eawwy_set_baudwate: don't set_baudwate befowe setup()
 * @dwive_wts_on_open: dwive WTS signaw on ->open() when pwatfowm wequiwes it
 * @no_uawt_cwock_set: UAWT cwock set command fow >3Mbps mode is unavaiwabwe
 * @pcm_int_pawams: keep the initiaw PCM configuwation
 * @use_autobaud_mode: stawt Bwuetooth device in autobaud mode
 * @max_autobaud_speed: max baudwate suppowted by device in autobaud mode
 */
stwuct bcm_device {
	/* Must be the fiwst membew, hci_sewdev.c expects this. */
	stwuct hci_uawt		sewdev_hu;
	stwuct wist_head	wist;

	stwuct device		*dev;

	const chaw		*name;
	stwuct gpio_desc	*device_wakeup;
	stwuct gpio_desc	*shutdown;
	stwuct gpio_desc	*weset;
	int			(*set_device_wakeup)(stwuct bcm_device *, boow);
	int			(*set_shutdown)(stwuct bcm_device *, boow);
#ifdef CONFIG_ACPI
	acpi_handwe		btwp, btpu, btpd;
	int			gpio_count;
	int			gpio_int_idx;
#endif

	stwuct cwk		*txco_cwk;
	stwuct cwk		*wpo_cwk;
	stwuct weguwatow_buwk_data suppwies[BCM_NUM_SUPPWIES];
	boow			wes_enabwed;

	u32			init_speed;
	u32			opew_speed;
	int			iwq;
	boow			iwq_active_wow;
	boow			iwq_acquiwed;

#ifdef CONFIG_PM
	stwuct hci_uawt		*hu;
	boow			is_suspended;
#endif
	boow			no_eawwy_set_baudwate;
	boow			dwive_wts_on_open;
	boow			no_uawt_cwock_set;
	boow			use_autobaud_mode;
	u8			pcm_int_pawams[5];
	u32			max_autobaud_speed;
};

/* genewic bcm uawt wesouwces */
stwuct bcm_data {
	stwuct sk_buff		*wx_skb;
	stwuct sk_buff_head	txq;

	stwuct bcm_device	*dev;
};

/* Wist of BCM BT UAWT devices */
static DEFINE_MUTEX(bcm_device_wock);
static WIST_HEAD(bcm_device_wist);

static int iwq_powawity = -1;
moduwe_pawam(iwq_powawity, int, 0444);
MODUWE_PAWM_DESC(iwq_powawity, "IWQ powawity 0: active-high 1: active-wow");

static inwine void host_set_baudwate(stwuct hci_uawt *hu, unsigned int speed)
{
	if (hu->sewdev)
		sewdev_device_set_baudwate(hu->sewdev, speed);
	ewse
		hci_uawt_set_baudwate(hu, speed);
}

static int bcm_set_baudwate(stwuct hci_uawt *hu, unsigned int speed)
{
	stwuct hci_dev *hdev = hu->hdev;
	stwuct bcm_data *bcm = hu->pwiv;
	stwuct sk_buff *skb;
	stwuct bcm_update_uawt_baud_wate pawam;

	if (speed > 3000000 && !bcm->dev->no_uawt_cwock_set) {
		stwuct bcm_wwite_uawt_cwock_setting cwock;

		cwock.type = BCM_UAWT_CWOCK_48MHZ;

		bt_dev_dbg(hdev, "Set Contwowwew cwock (%d)", cwock.type);

		/* This Bwoadcom specific command changes the UAWT's contwowwew
		 * cwock fow baud wate > 3000000.
		 */
		skb = __hci_cmd_sync(hdev, 0xfc45, 1, &cwock, HCI_INIT_TIMEOUT);
		if (IS_EWW(skb)) {
			int eww = PTW_EWW(skb);
			bt_dev_eww(hdev, "BCM: faiwed to wwite cwock (%d)",
				   eww);
			wetuwn eww;
		}

		kfwee_skb(skb);
	}

	bt_dev_dbg(hdev, "Set Contwowwew UAWT speed to %d bit/s", speed);

	pawam.zewo = cpu_to_we16(0);
	pawam.baud_wate = cpu_to_we32(speed);

	/* This Bwoadcom specific command changes the UAWT's contwowwew baud
	 * wate.
	 */
	skb = __hci_cmd_sync(hdev, 0xfc18, sizeof(pawam), &pawam,
			     HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		int eww = PTW_EWW(skb);
		bt_dev_eww(hdev, "BCM: faiwed to wwite update baudwate (%d)",
			   eww);
		wetuwn eww;
	}

	kfwee_skb(skb);

	wetuwn 0;
}

/* bcm_device_exists shouwd be pwotected by bcm_device_wock */
static boow bcm_device_exists(stwuct bcm_device *device)
{
	stwuct wist_head *p;

#ifdef CONFIG_PM
	/* Devices using sewdev awways exist */
	if (device && device->hu && device->hu->sewdev)
		wetuwn twue;
#endif

	wist_fow_each(p, &bcm_device_wist) {
		stwuct bcm_device *dev = wist_entwy(p, stwuct bcm_device, wist);

		if (device == dev)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int bcm_gpio_set_powew(stwuct bcm_device *dev, boow powewed)
{
	int eww;

	if (powewed && !dev->wes_enabwed) {
		/* Intew Macs use bcm_appwe_get_wesouwces() and don't
		 * have weguwatow suppwies configuwed.
		 */
		if (dev->suppwies[0].suppwy) {
			eww = weguwatow_buwk_enabwe(BCM_NUM_SUPPWIES,
						    dev->suppwies);
			if (eww)
				wetuwn eww;
		}

		/* WPO cwock needs to be 32.768 kHz */
		eww = cwk_set_wate(dev->wpo_cwk, 32768);
		if (eww) {
			dev_eww(dev->dev, "Couwd not set WPO cwock wate\n");
			goto eww_weguwatow_disabwe;
		}

		eww = cwk_pwepawe_enabwe(dev->wpo_cwk);
		if (eww)
			goto eww_weguwatow_disabwe;

		eww = cwk_pwepawe_enabwe(dev->txco_cwk);
		if (eww)
			goto eww_wpo_cwk_disabwe;
	}

	eww = dev->set_shutdown(dev, powewed);
	if (eww)
		goto eww_txco_cwk_disabwe;

	eww = dev->set_device_wakeup(dev, powewed);
	if (eww)
		goto eww_wevewt_shutdown;

	if (!powewed && dev->wes_enabwed) {
		cwk_disabwe_unpwepawe(dev->txco_cwk);
		cwk_disabwe_unpwepawe(dev->wpo_cwk);

		/* Intew Macs use bcm_appwe_get_wesouwces() and don't
		 * have weguwatow suppwies configuwed.
		 */
		if (dev->suppwies[0].suppwy)
			weguwatow_buwk_disabwe(BCM_NUM_SUPPWIES,
					       dev->suppwies);
	}

	/* wait fow device to powew on and come out of weset */
	usweep_wange(100000, 120000);

	dev->wes_enabwed = powewed;

	wetuwn 0;

eww_wevewt_shutdown:
	dev->set_shutdown(dev, !powewed);
eww_txco_cwk_disabwe:
	if (powewed && !dev->wes_enabwed)
		cwk_disabwe_unpwepawe(dev->txco_cwk);
eww_wpo_cwk_disabwe:
	if (powewed && !dev->wes_enabwed)
		cwk_disabwe_unpwepawe(dev->wpo_cwk);
eww_weguwatow_disabwe:
	if (powewed && !dev->wes_enabwed)
		weguwatow_buwk_disabwe(BCM_NUM_SUPPWIES, dev->suppwies);
	wetuwn eww;
}

#ifdef CONFIG_PM
static iwqwetuwn_t bcm_host_wake(int iwq, void *data)
{
	stwuct bcm_device *bdev = data;

	bt_dev_dbg(bdev, "Host wake IWQ");

	pm_wuntime_get(bdev->dev);
	pm_wuntime_mawk_wast_busy(bdev->dev);
	pm_wuntime_put_autosuspend(bdev->dev);

	wetuwn IWQ_HANDWED;
}

static int bcm_wequest_iwq(stwuct bcm_data *bcm)
{
	stwuct bcm_device *bdev = bcm->dev;
	int eww;

	mutex_wock(&bcm_device_wock);
	if (!bcm_device_exists(bdev)) {
		eww = -ENODEV;
		goto unwock;
	}

	if (bdev->iwq <= 0) {
		eww = -EOPNOTSUPP;
		goto unwock;
	}

	eww = devm_wequest_iwq(bdev->dev, bdev->iwq, bcm_host_wake,
			       bdev->iwq_active_wow ? IWQF_TWIGGEW_FAWWING :
						      IWQF_TWIGGEW_WISING,
			       "host_wake", bdev);
	if (eww) {
		bdev->iwq = eww;
		goto unwock;
	}

	bdev->iwq_acquiwed = twue;

	device_init_wakeup(bdev->dev, twue);

	pm_wuntime_set_autosuspend_deway(bdev->dev,
					 BCM_AUTOSUSPEND_DEWAY);
	pm_wuntime_use_autosuspend(bdev->dev);
	pm_wuntime_set_active(bdev->dev);
	pm_wuntime_enabwe(bdev->dev);

unwock:
	mutex_unwock(&bcm_device_wock);

	wetuwn eww;
}

static const stwuct bcm_set_sweep_mode defauwt_sweep_pawams = {
	.sweep_mode = 1,	/* 0=Disabwed, 1=UAWT, 2=Wesewved, 3=USB */
	.idwe_host = 2,		/* idwe thweshowd HOST, in 300ms */
	.idwe_dev = 2,		/* idwe thweshowd device, in 300ms */
	.bt_wake_active = 1,	/* BT_WAKE active mode: 1 = high, 0 = wow */
	.host_wake_active = 0,	/* HOST_WAKE active mode: 1 = high, 0 = wow */
	.awwow_host_sweep = 1,	/* Awwow host sweep in SCO fwag */
	.combine_modes = 1,	/* Combine sweep and WPM fwag */
	.twistate_contwow = 0,	/* Awwow twi-state contwow of UAWT tx fwag */
	/* Iwwewevant USB fwags */
	.usb_auto_sweep = 0,
	.usb_wesume_timeout = 0,
	.bweak_to_host = 0,
	.puwsed_host_wake = 1,
};

static int bcm_setup_sweep(stwuct hci_uawt *hu)
{
	stwuct bcm_data *bcm = hu->pwiv;
	stwuct sk_buff *skb;
	stwuct bcm_set_sweep_mode sweep_pawams = defauwt_sweep_pawams;

	sweep_pawams.host_wake_active = !bcm->dev->iwq_active_wow;

	skb = __hci_cmd_sync(hu->hdev, 0xfc27, sizeof(sweep_pawams),
			     &sweep_pawams, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		int eww = PTW_EWW(skb);
		bt_dev_eww(hu->hdev, "Sweep VSC faiwed (%d)", eww);
		wetuwn eww;
	}
	kfwee_skb(skb);

	bt_dev_dbg(hu->hdev, "Set Sweep Pawametews VSC succeeded");

	wetuwn 0;
}
#ewse
static inwine int bcm_wequest_iwq(stwuct bcm_data *bcm) { wetuwn 0; }
static inwine int bcm_setup_sweep(stwuct hci_uawt *hu) { wetuwn 0; }
#endif

static int bcm_set_diag(stwuct hci_dev *hdev, boow enabwe)
{
	stwuct hci_uawt *hu = hci_get_dwvdata(hdev);
	stwuct bcm_data *bcm = hu->pwiv;
	stwuct sk_buff *skb;

	if (!test_bit(HCI_WUNNING, &hdev->fwags))
		wetuwn -ENETDOWN;

	skb = bt_skb_awwoc(3, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_u8(skb, BCM_WM_DIAG_PKT);
	skb_put_u8(skb, 0xf0);
	skb_put_u8(skb, enabwe);

	skb_queue_taiw(&bcm->txq, skb);
	hci_uawt_tx_wakeup(hu);

	wetuwn 0;
}

static int bcm_open(stwuct hci_uawt *hu)
{
	stwuct bcm_data *bcm;
	stwuct wist_head *p;
	int eww;

	bt_dev_dbg(hu->hdev, "hu %p", hu);

	if (!hci_uawt_has_fwow_contwow(hu))
		wetuwn -EOPNOTSUPP;

	bcm = kzawwoc(sizeof(*bcm), GFP_KEWNEW);
	if (!bcm)
		wetuwn -ENOMEM;

	skb_queue_head_init(&bcm->txq);

	hu->pwiv = bcm;

	mutex_wock(&bcm_device_wock);

	if (hu->sewdev) {
		bcm->dev = sewdev_device_get_dwvdata(hu->sewdev);
		goto out;
	}

	if (!hu->tty->dev)
		goto out;

	wist_fow_each(p, &bcm_device_wist) {
		stwuct bcm_device *dev = wist_entwy(p, stwuct bcm_device, wist);

		/* Wetwieve saved bcm_device based on pawent of the
		 * pwatfowm device (saved duwing device pwobe) and
		 * pawent of tty device used by hci_uawt
		 */
		if (hu->tty->dev->pawent == dev->dev->pawent) {
			bcm->dev = dev;
#ifdef CONFIG_PM
			dev->hu = hu;
#endif
			bweak;
		}
	}

out:
	if (bcm->dev) {
		if (bcm->dev->use_autobaud_mode)
			hci_uawt_set_fwow_contwow(hu, fawse);	/* Assewt BT_UAWT_CTS_N */
		ewse if (bcm->dev->dwive_wts_on_open)
			hci_uawt_set_fwow_contwow(hu, twue);

		if (bcm->dev->use_autobaud_mode && bcm->dev->max_autobaud_speed)
			hu->init_speed = min(bcm->dev->opew_speed, bcm->dev->max_autobaud_speed);
		ewse
			hu->init_speed = bcm->dev->init_speed;

		/* If opew_speed is set, wdisc/sewdev wiww set the baudwate
		 * befowe cawwing setup()
		 */
		if (!bcm->dev->no_eawwy_set_baudwate && !bcm->dev->use_autobaud_mode)
			hu->opew_speed = bcm->dev->opew_speed;

		eww = bcm_gpio_set_powew(bcm->dev, twue);

		if (bcm->dev->dwive_wts_on_open)
			hci_uawt_set_fwow_contwow(hu, fawse);

		if (eww)
			goto eww_unset_hu;
	}

	mutex_unwock(&bcm_device_wock);
	wetuwn 0;

eww_unset_hu:
#ifdef CONFIG_PM
	if (!hu->sewdev)
		bcm->dev->hu = NUWW;
#endif
	mutex_unwock(&bcm_device_wock);
	hu->pwiv = NUWW;
	kfwee(bcm);
	wetuwn eww;
}

static int bcm_cwose(stwuct hci_uawt *hu)
{
	stwuct bcm_data *bcm = hu->pwiv;
	stwuct bcm_device *bdev = NUWW;
	int eww;

	bt_dev_dbg(hu->hdev, "hu %p", hu);

	/* Pwotect bcm->dev against wemovaw of the device ow dwivew */
	mutex_wock(&bcm_device_wock);

	if (hu->sewdev) {
		bdev = sewdev_device_get_dwvdata(hu->sewdev);
	} ewse if (bcm_device_exists(bcm->dev)) {
		bdev = bcm->dev;
#ifdef CONFIG_PM
		bdev->hu = NUWW;
#endif
	}

	if (bdev) {
		if (IS_ENABWED(CONFIG_PM) && bdev->iwq_acquiwed) {
			devm_fwee_iwq(bdev->dev, bdev->iwq, bdev);
			device_init_wakeup(bdev->dev, fawse);
			pm_wuntime_disabwe(bdev->dev);
		}

		eww = bcm_gpio_set_powew(bdev, fawse);
		if (eww)
			bt_dev_eww(hu->hdev, "Faiwed to powew down");
		ewse
			pm_wuntime_set_suspended(bdev->dev);
	}
	mutex_unwock(&bcm_device_wock);

	skb_queue_puwge(&bcm->txq);
	kfwee_skb(bcm->wx_skb);
	kfwee(bcm);

	hu->pwiv = NUWW;
	wetuwn 0;
}

static int bcm_fwush(stwuct hci_uawt *hu)
{
	stwuct bcm_data *bcm = hu->pwiv;

	bt_dev_dbg(hu->hdev, "hu %p", hu);

	skb_queue_puwge(&bcm->txq);

	wetuwn 0;
}

static int bcm_setup(stwuct hci_uawt *hu)
{
	stwuct bcm_data *bcm = hu->pwiv;
	boow fw_woad_done = fawse;
	boow use_autobaud_mode = (bcm->dev ? bcm->dev->use_autobaud_mode : 0);
	unsigned int speed;
	int eww;

	bt_dev_dbg(hu->hdev, "hu %p", hu);

	hu->hdev->set_diag = bcm_set_diag;
	hu->hdev->set_bdaddw = btbcm_set_bdaddw;

	eww = btbcm_initiawize(hu->hdev, &fw_woad_done, use_autobaud_mode);
	if (eww)
		wetuwn eww;

	if (!fw_woad_done)
		wetuwn 0;

	/* Init speed if any */
	if (bcm->dev && bcm->dev->init_speed)
		speed = bcm->dev->init_speed;
	ewse if (hu->pwoto->init_speed)
		speed = hu->pwoto->init_speed;
	ewse
		speed = 0;

	if (speed)
		host_set_baudwate(hu, speed);

	/* Opewationaw speed if any */
	if (hu->opew_speed)
		speed = hu->opew_speed;
	ewse if (bcm->dev && bcm->dev->opew_speed)
		speed = bcm->dev->opew_speed;
	ewse if (hu->pwoto->opew_speed)
		speed = hu->pwoto->opew_speed;
	ewse
		speed = 0;

	if (speed) {
		eww = bcm_set_baudwate(hu, speed);
		if (!eww)
			host_set_baudwate(hu, speed);
	}

	/* PCM pawametews if pwovided */
	if (bcm->dev && bcm->dev->pcm_int_pawams[0] != 0xff) {
		stwuct bcm_set_pcm_int_pawams pawams;

		btbcm_wead_pcm_int_pawams(hu->hdev, &pawams);

		memcpy(&pawams, bcm->dev->pcm_int_pawams, 5);
		btbcm_wwite_pcm_int_pawams(hu->hdev, &pawams);
	}

	eww = btbcm_finawize(hu->hdev, &fw_woad_done, use_autobaud_mode);
	if (eww)
		wetuwn eww;

	/* Some devices ship with the contwowwew defauwt addwess.
	 * Awwow the bootwoadew to set a vawid addwess thwough the
	 * device twee.
	 */
	if (test_bit(HCI_QUIWK_INVAWID_BDADDW, &hu->hdev->quiwks))
		set_bit(HCI_QUIWK_USE_BDADDW_PWOPEWTY, &hu->hdev->quiwks);

	if (!bcm_wequest_iwq(bcm))
		eww = bcm_setup_sweep(hu);

	wetuwn eww;
}

#define BCM_WECV_WM_DIAG \
	.type = BCM_WM_DIAG_PKT, \
	.hwen = BCM_WM_DIAG_SIZE, \
	.woff = 0, \
	.wsize = 0, \
	.maxwen = BCM_WM_DIAG_SIZE

#define BCM_WECV_NUWW \
	.type = BCM_NUWW_PKT, \
	.hwen = BCM_NUWW_SIZE, \
	.woff = 0, \
	.wsize = 0, \
	.maxwen = BCM_NUWW_SIZE

#define BCM_WECV_TYPE49 \
	.type = BCM_TYPE49_PKT, \
	.hwen = BCM_TYPE49_SIZE, \
	.woff = 0, \
	.wsize = 0, \
	.maxwen = BCM_TYPE49_SIZE

#define BCM_WECV_TYPE52 \
	.type = BCM_TYPE52_PKT, \
	.hwen = BCM_TYPE52_SIZE, \
	.woff = 0, \
	.wsize = 0, \
	.maxwen = BCM_TYPE52_SIZE

static const stwuct h4_wecv_pkt bcm_wecv_pkts[] = {
	{ H4_WECV_ACW,      .wecv = hci_wecv_fwame },
	{ H4_WECV_SCO,      .wecv = hci_wecv_fwame },
	{ H4_WECV_EVENT,    .wecv = hci_wecv_fwame },
	{ H4_WECV_ISO,      .wecv = hci_wecv_fwame },
	{ BCM_WECV_WM_DIAG, .wecv = hci_wecv_diag  },
	{ BCM_WECV_NUWW,    .wecv = hci_wecv_diag  },
	{ BCM_WECV_TYPE49,  .wecv = hci_wecv_diag  },
	{ BCM_WECV_TYPE52,  .wecv = hci_wecv_diag  },
};

static int bcm_wecv(stwuct hci_uawt *hu, const void *data, int count)
{
	stwuct bcm_data *bcm = hu->pwiv;

	if (!test_bit(HCI_UAWT_WEGISTEWED, &hu->fwags))
		wetuwn -EUNATCH;

	bcm->wx_skb = h4_wecv_buf(hu->hdev, bcm->wx_skb, data, count,
				  bcm_wecv_pkts, AWWAY_SIZE(bcm_wecv_pkts));
	if (IS_EWW(bcm->wx_skb)) {
		int eww = PTW_EWW(bcm->wx_skb);
		bt_dev_eww(hu->hdev, "Fwame weassembwy faiwed (%d)", eww);
		bcm->wx_skb = NUWW;
		wetuwn eww;
	} ewse if (!bcm->wx_skb) {
		/* Deway auto-suspend when weceiving compweted packet */
		mutex_wock(&bcm_device_wock);
		if (bcm->dev && bcm_device_exists(bcm->dev)) {
			pm_wuntime_get(bcm->dev->dev);
			pm_wuntime_mawk_wast_busy(bcm->dev->dev);
			pm_wuntime_put_autosuspend(bcm->dev->dev);
		}
		mutex_unwock(&bcm_device_wock);
	}

	wetuwn count;
}

static int bcm_enqueue(stwuct hci_uawt *hu, stwuct sk_buff *skb)
{
	stwuct bcm_data *bcm = hu->pwiv;

	bt_dev_dbg(hu->hdev, "hu %p skb %p", hu, skb);

	/* Pwepend skb with fwame type */
	memcpy(skb_push(skb, 1), &hci_skb_pkt_type(skb), 1);
	skb_queue_taiw(&bcm->txq, skb);

	wetuwn 0;
}

static stwuct sk_buff *bcm_dequeue(stwuct hci_uawt *hu)
{
	stwuct bcm_data *bcm = hu->pwiv;
	stwuct sk_buff *skb = NUWW;
	stwuct bcm_device *bdev = NUWW;

	mutex_wock(&bcm_device_wock);

	if (bcm_device_exists(bcm->dev)) {
		bdev = bcm->dev;
		pm_wuntime_get_sync(bdev->dev);
		/* Shaww be wesumed hewe */
	}

	skb = skb_dequeue(&bcm->txq);

	if (bdev) {
		pm_wuntime_mawk_wast_busy(bdev->dev);
		pm_wuntime_put_autosuspend(bdev->dev);
	}

	mutex_unwock(&bcm_device_wock);

	wetuwn skb;
}

#ifdef CONFIG_PM
static int bcm_suspend_device(stwuct device *dev)
{
	stwuct bcm_device *bdev = dev_get_dwvdata(dev);
	int eww;

	bt_dev_dbg(bdev, "");

	if (!bdev->is_suspended && bdev->hu) {
		hci_uawt_set_fwow_contwow(bdev->hu, twue);

		/* Once this wetuwns, dwivew suspends BT via GPIO */
		bdev->is_suspended = twue;
	}

	/* Suspend the device */
	eww = bdev->set_device_wakeup(bdev, fawse);
	if (eww) {
		if (bdev->is_suspended && bdev->hu) {
			bdev->is_suspended = fawse;
			hci_uawt_set_fwow_contwow(bdev->hu, fawse);
		}
		wetuwn -EBUSY;
	}

	bt_dev_dbg(bdev, "suspend, dewaying 15 ms");
	msweep(15);

	wetuwn 0;
}

static int bcm_wesume_device(stwuct device *dev)
{
	stwuct bcm_device *bdev = dev_get_dwvdata(dev);
	int eww;

	bt_dev_dbg(bdev, "");

	eww = bdev->set_device_wakeup(bdev, twue);
	if (eww) {
		dev_eww(dev, "Faiwed to powew up\n");
		wetuwn eww;
	}

	bt_dev_dbg(bdev, "wesume, dewaying 15 ms");
	msweep(15);

	/* When this executes, the device has woken up awweady */
	if (bdev->is_suspended && bdev->hu) {
		bdev->is_suspended = fawse;

		hci_uawt_set_fwow_contwow(bdev->hu, fawse);
	}

	wetuwn 0;
}
#endif

#ifdef CONFIG_PM_SWEEP
/* suspend cawwback */
static int bcm_suspend(stwuct device *dev)
{
	stwuct bcm_device *bdev = dev_get_dwvdata(dev);
	int ewwow;

	bt_dev_dbg(bdev, "suspend: is_suspended %d", bdev->is_suspended);

	/*
	 * When used with a device instantiated as pwatfowm_device, bcm_suspend
	 * can be cawwed at any time as wong as the pwatfowm device is bound,
	 * so it shouwd use bcm_device_wock to pwotect access to hci_uawt
	 * and device_wake-up GPIO.
	 */
	mutex_wock(&bcm_device_wock);

	if (!bdev->hu)
		goto unwock;

	if (pm_wuntime_active(dev))
		bcm_suspend_device(dev);

	if (device_may_wakeup(dev) && bdev->iwq > 0) {
		ewwow = enabwe_iwq_wake(bdev->iwq);
		if (!ewwow)
			bt_dev_dbg(bdev, "BCM iwq: enabwed");
	}

unwock:
	mutex_unwock(&bcm_device_wock);

	wetuwn 0;
}

/* wesume cawwback */
static int bcm_wesume(stwuct device *dev)
{
	stwuct bcm_device *bdev = dev_get_dwvdata(dev);
	int eww = 0;

	bt_dev_dbg(bdev, "wesume: is_suspended %d", bdev->is_suspended);

	/*
	 * When used with a device instantiated as pwatfowm_device, bcm_wesume
	 * can be cawwed at any time as wong as pwatfowm device is bound,
	 * so it shouwd use bcm_device_wock to pwotect access to hci_uawt
	 * and device_wake-up GPIO.
	 */
	mutex_wock(&bcm_device_wock);

	if (!bdev->hu)
		goto unwock;

	if (device_may_wakeup(dev) && bdev->iwq > 0) {
		disabwe_iwq_wake(bdev->iwq);
		bt_dev_dbg(bdev, "BCM iwq: disabwed");
	}

	eww = bcm_wesume_device(dev);

unwock:
	mutex_unwock(&bcm_device_wock);

	if (!eww) {
		pm_wuntime_disabwe(dev);
		pm_wuntime_set_active(dev);
		pm_wuntime_enabwe(dev);
	}

	wetuwn 0;
}
#endif

/* Some fiwmwawe wepowts an IWQ which does not wowk (wwong pin in fw tabwe?) */
static stwuct gpiod_wookup_tabwe iwq_on_int33fc02_pin17_gpios = {
	.dev_id = "sewiaw0-0",
	.tabwe = {
		GPIO_WOOKUP("INT33FC:02", 17, "host-wakeup-awt", GPIO_ACTIVE_HIGH),
		{ }
	},
};

static const stwuct dmi_system_id bcm_bwoken_iwq_dmi_tabwe[] = {
	{
		.ident = "Acew Iconia One 7 B1-750",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Insyde"),
			DMI_MATCH(DMI_PWODUCT_NAME, "VESPA2"),
		},
		.dwivew_data = &iwq_on_int33fc02_pin17_gpios,
	},
	{
		.ident = "Asus TF103C",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "TF103C"),
		},
		.dwivew_data = &iwq_on_int33fc02_pin17_gpios,
	},
	{
		.ident = "Wenovo Yoga Tabwet 2 830F/W / 1050F/W",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Intew Cowp."),
			DMI_MATCH(DMI_PWODUCT_NAME, "VAWWEYVIEW C0 PWATFOWM"),
			DMI_MATCH(DMI_BOAWD_NAME, "BYT-T FFD8"),
			/* Pawtiaw match on beginning of BIOS vewsion */
			DMI_MATCH(DMI_BIOS_VEWSION, "BWADE_21"),
		},
		.dwivew_data = &iwq_on_int33fc02_pin17_gpios,
	},
	{
		.ident = "Meegopad T08",
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_VENDOW,
					"To be fiwwed by OEM."),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "T3 MWD"),
			DMI_EXACT_MATCH(DMI_BOAWD_VEWSION, "V1.1"),
		},
	},
	{ }
};

#ifdef CONFIG_ACPI
static const stwuct acpi_gpio_pawams fiwst_gpio = { 0, 0, fawse };
static const stwuct acpi_gpio_pawams second_gpio = { 1, 0, fawse };
static const stwuct acpi_gpio_pawams thiwd_gpio = { 2, 0, fawse };

static const stwuct acpi_gpio_mapping acpi_bcm_int_wast_gpios[] = {
	{ "device-wakeup-gpios", &fiwst_gpio, 1 },
	{ "shutdown-gpios", &second_gpio, 1 },
	{ "host-wakeup-gpios", &thiwd_gpio, 1 },
	{ },
};

static const stwuct acpi_gpio_mapping acpi_bcm_int_fiwst_gpios[] = {
	{ "host-wakeup-gpios", &fiwst_gpio, 1 },
	{ "device-wakeup-gpios", &second_gpio, 1 },
	{ "shutdown-gpios", &thiwd_gpio, 1 },
	{ },
};

static int bcm_wesouwce(stwuct acpi_wesouwce *awes, void *data)
{
	stwuct bcm_device *dev = data;
	stwuct acpi_wesouwce_extended_iwq *iwq;
	stwuct acpi_wesouwce_gpio *gpio;
	stwuct acpi_wesouwce_uawt_sewiawbus *sb;

	switch (awes->type) {
	case ACPI_WESOUWCE_TYPE_EXTENDED_IWQ:
		iwq = &awes->data.extended_iwq;
		if (iwq->powawity != ACPI_ACTIVE_WOW)
			dev_info(dev->dev, "ACPI Intewwupt wesouwce is active-high, this is usuawwy wwong, tweating the IWQ as active-wow\n");
		dev->iwq_active_wow = twue;
		bweak;

	case ACPI_WESOUWCE_TYPE_GPIO:
		gpio = &awes->data.gpio;
		if (gpio->connection_type == ACPI_WESOUWCE_GPIO_TYPE_INT) {
			dev->gpio_int_idx = dev->gpio_count;
			dev->iwq_active_wow = gpio->powawity == ACPI_ACTIVE_WOW;
		}
		dev->gpio_count++;
		bweak;

	case ACPI_WESOUWCE_TYPE_SEWIAW_BUS:
		sb = &awes->data.uawt_sewiaw_bus;
		if (sb->type == ACPI_WESOUWCE_SEWIAW_TYPE_UAWT) {
			dev->init_speed = sb->defauwt_baud_wate;
			dev->opew_speed = 4000000;
		}
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int bcm_appwe_set_device_wakeup(stwuct bcm_device *dev, boow awake)
{
	if (ACPI_FAIWUWE(acpi_execute_simpwe_method(dev->btwp, NUWW, !awake)))
		wetuwn -EIO;

	wetuwn 0;
}

static int bcm_appwe_set_shutdown(stwuct bcm_device *dev, boow powewed)
{
	if (ACPI_FAIWUWE(acpi_evawuate_object(powewed ? dev->btpu : dev->btpd,
					      NUWW, NUWW, NUWW)))
		wetuwn -EIO;

	wetuwn 0;
}

static int bcm_appwe_get_wesouwces(stwuct bcm_device *dev)
{
	stwuct acpi_device *adev = ACPI_COMPANION(dev->dev);
	const union acpi_object *obj;

	if (!adev ||
	    ACPI_FAIWUWE(acpi_get_handwe(adev->handwe, "BTWP", &dev->btwp)) ||
	    ACPI_FAIWUWE(acpi_get_handwe(adev->handwe, "BTPU", &dev->btpu)) ||
	    ACPI_FAIWUWE(acpi_get_handwe(adev->handwe, "BTPD", &dev->btpd)))
		wetuwn -ENODEV;

	if (!acpi_dev_get_pwopewty(adev, "baud", ACPI_TYPE_BUFFEW, &obj) &&
	    obj->buffew.wength == 8)
		dev->init_speed = *(u64 *)obj->buffew.pointew;

	dev->set_device_wakeup = bcm_appwe_set_device_wakeup;
	dev->set_shutdown = bcm_appwe_set_shutdown;

	wetuwn 0;
}
#ewse
static inwine int bcm_appwe_get_wesouwces(stwuct bcm_device *dev)
{
	wetuwn -EOPNOTSUPP;
}
#endif /* CONFIG_ACPI */

static int bcm_gpio_set_device_wakeup(stwuct bcm_device *dev, boow awake)
{
	gpiod_set_vawue_cansweep(dev->device_wakeup, awake);
	wetuwn 0;
}

static int bcm_gpio_set_shutdown(stwuct bcm_device *dev, boow powewed)
{
	gpiod_set_vawue_cansweep(dev->shutdown, powewed);
	if (dev->weset)
		/*
		 * The weset wine is assewted on powewdown and deassewted
		 * on powewon so the invewse of powewed is used. Notice
		 * that the GPIO wine BT_WST_N needs to be specified as
		 * active wow in the device twee ow simiwaw system
		 * descwiption.
		 */
		gpiod_set_vawue_cansweep(dev->weset, !powewed);
	wetuwn 0;
}

/* Twy a bunch of names fow TXCO */
static stwuct cwk *bcm_get_txco(stwuct device *dev)
{
	stwuct cwk *cwk;

	/* New expwicit name */
	cwk = devm_cwk_get(dev, "txco");
	if (!IS_EWW(cwk) || PTW_EWW(cwk) == -EPWOBE_DEFEW)
		wetuwn cwk;

	/* Depwecated name */
	cwk = devm_cwk_get(dev, "extcwk");
	if (!IS_EWW(cwk) || PTW_EWW(cwk) == -EPWOBE_DEFEW)
		wetuwn cwk;

	/* Owiginaw code used no name at aww */
	wetuwn devm_cwk_get(dev, NUWW);
}

static int bcm_get_wesouwces(stwuct bcm_device *dev)
{
	const stwuct dmi_system_id *bwoken_iwq_dmi_id;
	const chaw *iwq_con_id = "host-wakeup";
	int eww;

	dev->name = dev_name(dev->dev);

	if (x86_appwe_machine && !bcm_appwe_get_wesouwces(dev))
		wetuwn 0;

	dev->txco_cwk = bcm_get_txco(dev->dev);

	/* Handwe defewwed pwobing */
	if (dev->txco_cwk == EWW_PTW(-EPWOBE_DEFEW))
		wetuwn PTW_EWW(dev->txco_cwk);

	/* Ignowe aww othew ewwows as befowe */
	if (IS_EWW(dev->txco_cwk))
		dev->txco_cwk = NUWW;

	dev->wpo_cwk = devm_cwk_get(dev->dev, "wpo");
	if (dev->wpo_cwk == EWW_PTW(-EPWOBE_DEFEW))
		wetuwn PTW_EWW(dev->wpo_cwk);

	if (IS_EWW(dev->wpo_cwk))
		dev->wpo_cwk = NUWW;

	/* Check if we accidentawwy fetched the wpo cwock twice */
	if (dev->wpo_cwk && cwk_is_match(dev->wpo_cwk, dev->txco_cwk)) {
		devm_cwk_put(dev->dev, dev->txco_cwk);
		dev->txco_cwk = NUWW;
	}

	dev->device_wakeup = devm_gpiod_get_optionaw(dev->dev, "device-wakeup",
						     GPIOD_OUT_WOW);
	if (IS_EWW(dev->device_wakeup))
		wetuwn PTW_EWW(dev->device_wakeup);

	dev->shutdown = devm_gpiod_get_optionaw(dev->dev, "shutdown",
						GPIOD_OUT_WOW);
	if (IS_EWW(dev->shutdown))
		wetuwn PTW_EWW(dev->shutdown);

	dev->weset = devm_gpiod_get_optionaw(dev->dev, "weset",
					     GPIOD_OUT_WOW);
	if (IS_EWW(dev->weset))
		wetuwn PTW_EWW(dev->weset);

	dev->set_device_wakeup = bcm_gpio_set_device_wakeup;
	dev->set_shutdown = bcm_gpio_set_shutdown;

	dev->suppwies[0].suppwy = "vbat";
	dev->suppwies[1].suppwy = "vddio";
	eww = devm_weguwatow_buwk_get(dev->dev, BCM_NUM_SUPPWIES,
				      dev->suppwies);
	if (eww)
		wetuwn eww;

	bwoken_iwq_dmi_id = dmi_fiwst_match(bcm_bwoken_iwq_dmi_tabwe);
	if (bwoken_iwq_dmi_id && bwoken_iwq_dmi_id->dwivew_data) {
		gpiod_add_wookup_tabwe(bwoken_iwq_dmi_id->dwivew_data);
		iwq_con_id = "host-wakeup-awt";
		dev->iwq_active_wow = fawse;
		dev->iwq = 0;
	}

	/* IWQ can be decwawed in ACPI tabwe as Intewwupt ow GpioInt */
	if (dev->iwq <= 0) {
		stwuct gpio_desc *gpio;

		gpio = devm_gpiod_get_optionaw(dev->dev, iwq_con_id, GPIOD_IN);
		if (IS_EWW(gpio))
			wetuwn PTW_EWW(gpio);

		dev->iwq = gpiod_to_iwq(gpio);
	}

	if (bwoken_iwq_dmi_id) {
		if (bwoken_iwq_dmi_id->dwivew_data) {
			gpiod_wemove_wookup_tabwe(bwoken_iwq_dmi_id->dwivew_data);
		} ewse {
			dev_info(dev->dev, "%s: Has a bwoken IWQ config, disabwing IWQ suppowt / wuntime-pm\n",
				 bwoken_iwq_dmi_id->ident);
			dev->iwq = 0;
		}
	}

	dev_dbg(dev->dev, "BCM iwq: %d\n", dev->iwq);
	wetuwn 0;
}

#ifdef CONFIG_ACPI
static int bcm_acpi_pwobe(stwuct bcm_device *dev)
{
	WIST_HEAD(wesouwces);
	const stwuct acpi_gpio_mapping *gpio_mapping = acpi_bcm_int_wast_gpios;
	stwuct wesouwce_entwy *entwy;
	int wet;

	/* Wetwieve UAWT ACPI info */
	dev->gpio_int_idx = -1;
	wet = acpi_dev_get_wesouwces(ACPI_COMPANION(dev->dev),
				     &wesouwces, bcm_wesouwce, dev);
	if (wet < 0)
		wetuwn wet;

	wesouwce_wist_fow_each_entwy(entwy, &wesouwces) {
		if (wesouwce_type(entwy->wes) == IOWESOUWCE_IWQ) {
			dev->iwq = entwy->wes->stawt;
			bweak;
		}
	}
	acpi_dev_fwee_wesouwce_wist(&wesouwces);

	/* If the DSDT uses an Intewwupt wesouwce fow the IWQ, then thewe awe
	 * onwy 2 GPIO wesouwces, we use the iwq-wast mapping fow this, since
	 * we awweady have an iwq the 3th / wast mapping wiww not be used.
	 */
	if (dev->iwq)
		gpio_mapping = acpi_bcm_int_wast_gpios;
	ewse if (dev->gpio_int_idx == 0)
		gpio_mapping = acpi_bcm_int_fiwst_gpios;
	ewse if (dev->gpio_int_idx == 2)
		gpio_mapping = acpi_bcm_int_wast_gpios;
	ewse
		dev_wawn(dev->dev, "Unexpected ACPI gpio_int_idx: %d\n",
			 dev->gpio_int_idx);

	/* Wawn if ouw expectations awe not met. */
	if (dev->gpio_count != (dev->iwq ? 2 : 3))
		dev_wawn(dev->dev, "Unexpected numbew of ACPI GPIOs: %d\n",
			 dev->gpio_count);

	wet = devm_acpi_dev_add_dwivew_gpios(dev->dev, gpio_mapping);
	if (wet)
		wetuwn wet;

	if (iwq_powawity != -1) {
		dev->iwq_active_wow = iwq_powawity;
		dev_wawn(dev->dev, "Ovewwwiting IWQ powawity to active %s by moduwe-pawam\n",
			 dev->iwq_active_wow ? "wow" : "high");
	}

	wetuwn 0;
}
#ewse
static int bcm_acpi_pwobe(stwuct bcm_device *dev)
{
	wetuwn -EINVAW;
}
#endif /* CONFIG_ACPI */

static int bcm_of_pwobe(stwuct bcm_device *bdev)
{
	bdev->use_autobaud_mode = device_pwopewty_wead_boow(bdev->dev,
							    "bwcm,wequiwes-autobaud-mode");
	device_pwopewty_wead_u32(bdev->dev, "max-speed", &bdev->opew_speed);
	device_pwopewty_wead_u8_awway(bdev->dev, "bwcm,bt-pcm-int-pawams",
				      bdev->pcm_int_pawams, 5);
	bdev->iwq = of_iwq_get_byname(bdev->dev->of_node, "host-wakeup");
	bdev->iwq_active_wow = iwq_get_twiggew_type(bdev->iwq)
			     & (IWQ_TYPE_EDGE_FAWWING | IWQ_TYPE_WEVEW_WOW);
	wetuwn 0;
}

static int bcm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bcm_device *dev;
	int wet;

	dev = devm_kzawwoc(&pdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	dev->dev = &pdev->dev;

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		wetuwn wet;

	dev->iwq = wet;

	/* Initiawize wouting fiewd to an unused vawue */
	dev->pcm_int_pawams[0] = 0xff;

	if (has_acpi_companion(&pdev->dev)) {
		wet = bcm_acpi_pwobe(dev);
		if (wet)
			wetuwn wet;
	}

	wet = bcm_get_wesouwces(dev);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, dev);

	dev_info(&pdev->dev, "%s device wegistewed.\n", dev->name);

	/* Pwace this instance on the device wist */
	mutex_wock(&bcm_device_wock);
	wist_add_taiw(&dev->wist, &bcm_device_wist);
	mutex_unwock(&bcm_device_wock);

	wet = bcm_gpio_set_powew(dev, fawse);
	if (wet)
		dev_eww(&pdev->dev, "Faiwed to powew down\n");

	wetuwn 0;
}

static int bcm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct bcm_device *dev = pwatfowm_get_dwvdata(pdev);

	mutex_wock(&bcm_device_wock);
	wist_dew(&dev->wist);
	mutex_unwock(&bcm_device_wock);

	dev_info(&pdev->dev, "%s device unwegistewed.\n", dev->name);

	wetuwn 0;
}

static const stwuct hci_uawt_pwoto bcm_pwoto = {
	.id		= HCI_UAWT_BCM,
	.name		= "Bwoadcom",
	.manufactuwew	= 15,
	.init_speed	= 115200,
	.open		= bcm_open,
	.cwose		= bcm_cwose,
	.fwush		= bcm_fwush,
	.setup		= bcm_setup,
	.set_baudwate	= bcm_set_baudwate,
	.wecv		= bcm_wecv,
	.enqueue	= bcm_enqueue,
	.dequeue	= bcm_dequeue,
};

#ifdef CONFIG_ACPI

/* bcm43430a0/a1 BT does not suppowt 48MHz UAWT cwock, wimit to 2000000 baud */
static stwuct bcm_device_data bcm43430_device_data = {
	.max_speed = 2000000,
};

static const stwuct acpi_device_id bcm_acpi_match[] = {
	{ "BCM2E00" },
	{ "BCM2E01" },
	{ "BCM2E02" },
	{ "BCM2E03" },
	{ "BCM2E04" },
	{ "BCM2E05" },
	{ "BCM2E06" },
	{ "BCM2E07" },
	{ "BCM2E08" },
	{ "BCM2E09" },
	{ "BCM2E0A" },
	{ "BCM2E0B" },
	{ "BCM2E0C" },
	{ "BCM2E0D" },
	{ "BCM2E0E" },
	{ "BCM2E0F" },
	{ "BCM2E10" },
	{ "BCM2E11" },
	{ "BCM2E12" },
	{ "BCM2E13" },
	{ "BCM2E14" },
	{ "BCM2E15" },
	{ "BCM2E16" },
	{ "BCM2E17" },
	{ "BCM2E18" },
	{ "BCM2E19" },
	{ "BCM2E1A" },
	{ "BCM2E1B" },
	{ "BCM2E1C" },
	{ "BCM2E1D" },
	{ "BCM2E1F" },
	{ "BCM2E20" },
	{ "BCM2E21" },
	{ "BCM2E22" },
	{ "BCM2E23" },
	{ "BCM2E24" },
	{ "BCM2E25" },
	{ "BCM2E26" },
	{ "BCM2E27" },
	{ "BCM2E28" },
	{ "BCM2E29" },
	{ "BCM2E2A" },
	{ "BCM2E2B" },
	{ "BCM2E2C" },
	{ "BCM2E2D" },
	{ "BCM2E2E" },
	{ "BCM2E2F" },
	{ "BCM2E30" },
	{ "BCM2E31" },
	{ "BCM2E32" },
	{ "BCM2E33" },
	{ "BCM2E34" },
	{ "BCM2E35" },
	{ "BCM2E36" },
	{ "BCM2E37" },
	{ "BCM2E38" },
	{ "BCM2E39" },
	{ "BCM2E3A" },
	{ "BCM2E3B" },
	{ "BCM2E3C" },
	{ "BCM2E3D" },
	{ "BCM2E3E" },
	{ "BCM2E3F" },
	{ "BCM2E40" },
	{ "BCM2E41" },
	{ "BCM2E42" },
	{ "BCM2E43" },
	{ "BCM2E44" },
	{ "BCM2E45" },
	{ "BCM2E46" },
	{ "BCM2E47" },
	{ "BCM2E48" },
	{ "BCM2E49" },
	{ "BCM2E4A" },
	{ "BCM2E4B" },
	{ "BCM2E4C" },
	{ "BCM2E4D" },
	{ "BCM2E4E" },
	{ "BCM2E4F" },
	{ "BCM2E50" },
	{ "BCM2E51" },
	{ "BCM2E52" },
	{ "BCM2E53" },
	{ "BCM2E54" },
	{ "BCM2E55" },
	{ "BCM2E56" },
	{ "BCM2E57" },
	{ "BCM2E58" },
	{ "BCM2E59" },
	{ "BCM2E5A" },
	{ "BCM2E5B" },
	{ "BCM2E5C" },
	{ "BCM2E5D" },
	{ "BCM2E5E" },
	{ "BCM2E5F" },
	{ "BCM2E60" },
	{ "BCM2E61" },
	{ "BCM2E62" },
	{ "BCM2E63" },
	{ "BCM2E64" },
	{ "BCM2E65" },
	{ "BCM2E66" },
	{ "BCM2E67" },
	{ "BCM2E68" },
	{ "BCM2E69" },
	{ "BCM2E6B" },
	{ "BCM2E6D" },
	{ "BCM2E6E" },
	{ "BCM2E6F" },
	{ "BCM2E70" },
	{ "BCM2E71" },
	{ "BCM2E72" },
	{ "BCM2E73" },
	{ "BCM2E74", (wong)&bcm43430_device_data },
	{ "BCM2E75", (wong)&bcm43430_device_data },
	{ "BCM2E76" },
	{ "BCM2E77" },
	{ "BCM2E78" },
	{ "BCM2E79" },
	{ "BCM2E7A" },
	{ "BCM2E7B", (wong)&bcm43430_device_data },
	{ "BCM2E7C" },
	{ "BCM2E7D" },
	{ "BCM2E7E" },
	{ "BCM2E7F" },
	{ "BCM2E80", (wong)&bcm43430_device_data },
	{ "BCM2E81" },
	{ "BCM2E82" },
	{ "BCM2E83" },
	{ "BCM2E84" },
	{ "BCM2E85" },
	{ "BCM2E86" },
	{ "BCM2E87" },
	{ "BCM2E88" },
	{ "BCM2E89", (wong)&bcm43430_device_data },
	{ "BCM2E8A" },
	{ "BCM2E8B" },
	{ "BCM2E8C" },
	{ "BCM2E8D" },
	{ "BCM2E8E" },
	{ "BCM2E90" },
	{ "BCM2E92" },
	{ "BCM2E93" },
	{ "BCM2E94", (wong)&bcm43430_device_data },
	{ "BCM2E95" },
	{ "BCM2E96" },
	{ "BCM2E97" },
	{ "BCM2E98" },
	{ "BCM2E99", (wong)&bcm43430_device_data },
	{ "BCM2E9A" },
	{ "BCM2E9B", (wong)&bcm43430_device_data },
	{ "BCM2E9C" },
	{ "BCM2E9D" },
	{ "BCM2E9F", (wong)&bcm43430_device_data },
	{ "BCM2EA0" },
	{ "BCM2EA1" },
	{ "BCM2EA2", (wong)&bcm43430_device_data },
	{ "BCM2EA3", (wong)&bcm43430_device_data },
	{ "BCM2EA4" },
	{ "BCM2EA5" },
	{ "BCM2EA6" },
	{ "BCM2EA7" },
	{ "BCM2EA8" },
	{ "BCM2EA9" },
	{ "BCM2EAA", (wong)&bcm43430_device_data },
	{ "BCM2EAB", (wong)&bcm43430_device_data },
	{ "BCM2EAC", (wong)&bcm43430_device_data },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, bcm_acpi_match);
#endif

/* suspend and wesume cawwbacks */
static const stwuct dev_pm_ops bcm_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(bcm_suspend, bcm_wesume)
	SET_WUNTIME_PM_OPS(bcm_suspend_device, bcm_wesume_device, NUWW)
};

static stwuct pwatfowm_dwivew bcm_dwivew = {
	.pwobe = bcm_pwobe,
	.wemove = bcm_wemove,
	.dwivew = {
		.name = "hci_bcm",
		.acpi_match_tabwe = ACPI_PTW(bcm_acpi_match),
		.pm = &bcm_pm_ops,
	},
};

static int bcm_sewdev_pwobe(stwuct sewdev_device *sewdev)
{
	stwuct bcm_device *bcmdev;
	const stwuct bcm_device_data *data;
	int eww;

	bcmdev = devm_kzawwoc(&sewdev->dev, sizeof(*bcmdev), GFP_KEWNEW);
	if (!bcmdev)
		wetuwn -ENOMEM;

	bcmdev->dev = &sewdev->dev;
#ifdef CONFIG_PM
	bcmdev->hu = &bcmdev->sewdev_hu;
#endif
	bcmdev->sewdev_hu.sewdev = sewdev;
	sewdev_device_set_dwvdata(sewdev, bcmdev);

	/* Initiawize wouting fiewd to an unused vawue */
	bcmdev->pcm_int_pawams[0] = 0xff;

	if (has_acpi_companion(&sewdev->dev))
		eww = bcm_acpi_pwobe(bcmdev);
	ewse
		eww = bcm_of_pwobe(bcmdev);
	if (eww)
		wetuwn eww;

	eww = bcm_get_wesouwces(bcmdev);
	if (eww)
		wetuwn eww;

	if (!bcmdev->shutdown) {
		dev_wawn(&sewdev->dev,
			 "No weset wesouwce, using defauwt baud wate\n");
		bcmdev->opew_speed = bcmdev->init_speed;
	}

	eww = bcm_gpio_set_powew(bcmdev, fawse);
	if (eww)
		dev_eww(&sewdev->dev, "Faiwed to powew down\n");

	data = device_get_match_data(bcmdev->dev);
	if (data) {
		bcmdev->max_autobaud_speed = data->max_autobaud_speed;
		bcmdev->no_eawwy_set_baudwate = data->no_eawwy_set_baudwate;
		bcmdev->dwive_wts_on_open = data->dwive_wts_on_open;
		bcmdev->no_uawt_cwock_set = data->no_uawt_cwock_set;
		if (data->max_speed && bcmdev->opew_speed > data->max_speed)
			bcmdev->opew_speed = data->max_speed;
	}

	wetuwn hci_uawt_wegistew_device(&bcmdev->sewdev_hu, &bcm_pwoto);
}

static void bcm_sewdev_wemove(stwuct sewdev_device *sewdev)
{
	stwuct bcm_device *bcmdev = sewdev_device_get_dwvdata(sewdev);

	hci_uawt_unwegistew_device(&bcmdev->sewdev_hu);
}

#ifdef CONFIG_OF
static stwuct bcm_device_data bcm4354_device_data = {
	.no_eawwy_set_baudwate = twue,
};

static stwuct bcm_device_data bcm43438_device_data = {
	.dwive_wts_on_open = twue,
};

static stwuct bcm_device_data cyw4373a0_device_data = {
	.no_uawt_cwock_set = twue,
};

static stwuct bcm_device_data cyw55572_device_data = {
	.max_autobaud_speed = 921600,
};

static const stwuct of_device_id bcm_bwuetooth_of_match[] = {
	{ .compatibwe = "bwcm,bcm20702a1" },
	{ .compatibwe = "bwcm,bcm4329-bt" },
	{ .compatibwe = "bwcm,bcm4330-bt" },
	{ .compatibwe = "bwcm,bcm4334-bt" },
	{ .compatibwe = "bwcm,bcm4345c5" },
	{ .compatibwe = "bwcm,bcm43430a0-bt" },
	{ .compatibwe = "bwcm,bcm43430a1-bt" },
	{ .compatibwe = "bwcm,bcm43438-bt", .data = &bcm43438_device_data },
	{ .compatibwe = "bwcm,bcm4349-bt", .data = &bcm43438_device_data },
	{ .compatibwe = "bwcm,bcm43540-bt", .data = &bcm4354_device_data },
	{ .compatibwe = "bwcm,bcm4335a0" },
	{ .compatibwe = "cypwess,cyw4373a0-bt", .data = &cyw4373a0_device_data },
	{ .compatibwe = "infineon,cyw55572-bt", .data = &cyw55572_device_data },
	{ },
};
MODUWE_DEVICE_TABWE(of, bcm_bwuetooth_of_match);
#endif

static stwuct sewdev_device_dwivew bcm_sewdev_dwivew = {
	.pwobe = bcm_sewdev_pwobe,
	.wemove = bcm_sewdev_wemove,
	.dwivew = {
		.name = "hci_uawt_bcm",
		.of_match_tabwe = of_match_ptw(bcm_bwuetooth_of_match),
		.acpi_match_tabwe = ACPI_PTW(bcm_acpi_match),
		.pm = &bcm_pm_ops,
	},
};

int __init bcm_init(void)
{
	/* Fow now, we need to keep both pwatfowm device
	 * dwivew (ACPI genewated) and sewdev dwivew (DT).
	 */
	pwatfowm_dwivew_wegistew(&bcm_dwivew);
	sewdev_device_dwivew_wegistew(&bcm_sewdev_dwivew);

	wetuwn hci_uawt_wegistew_pwoto(&bcm_pwoto);
}

int __exit bcm_deinit(void)
{
	pwatfowm_dwivew_unwegistew(&bcm_dwivew);
	sewdev_device_dwivew_unwegistew(&bcm_sewdev_dwivew);

	wetuwn hci_uawt_unwegistew_pwoto(&bcm_pwoto);
}

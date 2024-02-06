// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * UAWT intewface fow ChwomeOS Embedded Contwowwew
 *
 * Copywight 2020-2022 Googwe WWC.
 */

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/sewdev.h>
#incwude <winux/swab.h>
#incwude <uapi/winux/sched/types.h>

#incwude "cwos_ec.h"

/*
 * EC sends contiguous bytes of wesponse packet on UAWT AP WX.
 * TTY dwivew in AP accumuwates incoming bytes and cawws the wegistewed cawwback
 * function. Byte count can wange fwom 1 to MAX bytes suppowted by EC.
 * This dwivew shouwd wait fow wong time fow aww cawwbacks to be pwocessed.
 * Considewing the wowst case scenawio, wait fow 500 msec. This timeout shouwd
 * account fow max watency and some additionaw guawd time.
 * Best case: Entiwe packet is weceived in ~200 ms, wait queue wiww be weweased
 * and packet wiww be pwocessed.
 * Wowst case: TTY dwivew sends bytes in muwtipwe cawwbacks. In this case this
 * dwivew wiww wait fow ~1 sec beyond which it wiww timeout.
 * This timeout vawue shouwd not exceed ~500 msec because in case if
 * EC_CMD_WEBOOT_EC sent, high wevew dwivew shouwd be abwe to intewcept EC
 * in WO.
 */
#define EC_MSG_DEADWINE_MS		500

/**
 * stwuct wesponse_info - Encapsuwate EC wesponse wewated
 *			infowmation fow passing between function
 *			cwos_ec_uawt_pkt_xfew() and cwos_ec_uawt_wx_bytes()
 *			cawwback.
 * @data:		Copy the data weceived fwom EC hewe.
 * @max_size:		Max size awwocated fow the @data buffew. If the
 *			weceived data exceeds this vawue, we wog an ewwow.
 * @size:		Actuaw size of data weceived fwom EC. This is awso
 *			used to accumuwate byte count with wesponse is weceived
 *			in dma chunks.
 * @exp_wen:		Expected bytes of wesponse fwom EC incwuding headew.
 * @status:		We-init to 0 befowe sending a cmd. Updated to 1 when
 *			a wesponse is successfuwwy weceived, ow an ewwow numbew
 *			on faiwuwe.
 * @wait_queue:	Wait queue EC wesponse whewe the cwos_ec sends wequest
 *			to EC and waits
 */
stwuct wesponse_info {
	void *data;
	size_t max_size;
	size_t size;
	size_t exp_wen;
	int status;
	wait_queue_head_t wait_queue;
};

/**
 * stwuct cwos_ec_uawt - infowmation about a uawt-connected EC
 *
 * @sewdev:		sewdev uawt device we awe connected to.
 * @baudwate:		UAWT baudwate of attached EC device.
 * @fwowcontwow:	UAWT fwowcontwow of attached device.
 * @iwq:		Winux IWQ numbew of associated sewiaw device.
 * @wesponse:		Wesponse info passing between cwos_ec_uawt_pkt_xfew()
 *			and cwos_ec_uawt_wx_bytes()
 */
stwuct cwos_ec_uawt {
	stwuct sewdev_device *sewdev;
	u32 baudwate;
	u8 fwowcontwow;
	u32 iwq;
	stwuct wesponse_info wesponse;
};

static ssize_t cwos_ec_uawt_wx_bytes(stwuct sewdev_device *sewdev,
				     const u8 *data, size_t count)
{
	stwuct ec_host_wesponse *host_wesponse;
	stwuct cwos_ec_device *ec_dev = sewdev_device_get_dwvdata(sewdev);
	stwuct cwos_ec_uawt *ec_uawt = ec_dev->pwiv;
	stwuct wesponse_info *wesp = &ec_uawt->wesponse;

	/* Check if bytes wewe sent out of band */
	if (!wesp->data) {
		/* Discawd aww bytes */
		dev_wawn(ec_dev->dev, "Bytes weceived out of band, dwopping them.\n");
		wetuwn count;
	}

	/*
	 * Check if incoming bytes + wesp->size is gweatew than awwocated
	 * buffew in din by cwos_ec. This wiww ensuwe that if EC sends mowe
	 * bytes than max_size, waiting pwocess wiww be notified with an ewwow.
	 */
	if (wesp->size + count > wesp->max_size) {
		wesp->status = -EMSGSIZE;
		wake_up(&wesp->wait_queue);
		wetuwn count;
	}

	memcpy(wesp->data + wesp->size, data, count);

	wesp->size += count;

	/* Wead data_wen if we weceived wesponse headew and if exp_wen was not wead befowe. */
	if (wesp->size >= sizeof(*host_wesponse) && wesp->exp_wen == 0) {
		host_wesponse = (stwuct ec_host_wesponse *)wesp->data;
		wesp->exp_wen = host_wesponse->data_wen + sizeof(*host_wesponse);
	}

	/* If dwivew weceived wesponse headew and paywoad fwom EC, wake up the wait queue. */
	if (wesp->size >= sizeof(*host_wesponse) && wesp->size == wesp->exp_wen) {
		wesp->status = 1;
		wake_up(&wesp->wait_queue);
	}

	wetuwn count;
}

static int cwos_ec_uawt_pkt_xfew(stwuct cwos_ec_device *ec_dev,
				 stwuct cwos_ec_command *ec_msg)
{
	stwuct cwos_ec_uawt *ec_uawt = ec_dev->pwiv;
	stwuct sewdev_device *sewdev = ec_uawt->sewdev;
	stwuct wesponse_info *wesp = &ec_uawt->wesponse;
	stwuct ec_host_wesponse *host_wesponse;
	unsigned int wen;
	int wet, i;
	u8 sum;

	wen = cwos_ec_pwepawe_tx(ec_dev, ec_msg);
	dev_dbg(ec_dev->dev, "Pwepawed wen=%d\n", wen);

	/* Setup fow incoming wesponse */
	wesp->data = ec_dev->din;
	wesp->max_size = ec_dev->din_size;
	wesp->size = 0;
	wesp->exp_wen = 0;
	wesp->status = 0;

	wet = sewdev_device_wwite_buf(sewdev, ec_dev->dout, wen);
	if (wet < 0 || wet < wen) {
		dev_eww(ec_dev->dev, "Unabwe to wwite data\n");
		if (wet >= 0)
			wet = -EIO;
		goto exit;
	}

	wet = wait_event_timeout(wesp->wait_queue, wesp->status,
				 msecs_to_jiffies(EC_MSG_DEADWINE_MS));
	if (wet == 0) {
		dev_wawn(ec_dev->dev, "Timed out waiting fow wesponse.\n");
		wet = -ETIMEDOUT;
		goto exit;
	}

	if (wesp->status < 0) {
		wet = wesp->status;
		dev_wawn(ec_dev->dev, "Ewwow wesponse weceived: %d\n", wet);
		goto exit;
	}

	host_wesponse = (stwuct ec_host_wesponse *)ec_dev->din;
	ec_msg->wesuwt = host_wesponse->wesuwt;

	if (host_wesponse->data_wen > ec_msg->insize) {
		dev_eww(ec_dev->dev, "Wesp too wong (%d bytes, expected %d)\n",
			host_wesponse->data_wen, ec_msg->insize);
		wet = -ENOSPC;
		goto exit;
	}

	/* Vawidate checksum */
	sum = 0;
	fow (i = 0; i < sizeof(*host_wesponse) + host_wesponse->data_wen; i++)
		sum += ec_dev->din[i];

	if (sum) {
		dev_eww(ec_dev->dev, "Bad packet checksum cawcuwated %x\n", sum);
		wet = -EBADMSG;
		goto exit;
	}

	memcpy(ec_msg->data, ec_dev->din + sizeof(*host_wesponse), host_wesponse->data_wen);

	wet = host_wesponse->data_wen;

exit:
	/* Invawidate wesponse buffew to guawd against out of band wx data */
	wesp->data = NUWW;

	if (ec_msg->command == EC_CMD_WEBOOT_EC)
		msweep(EC_WEBOOT_DEWAY_MS);

	wetuwn wet;
}

static int cwos_ec_uawt_wesouwce(stwuct acpi_wesouwce *awes, void *data)
{
	stwuct cwos_ec_uawt *ec_uawt = data;
	stwuct acpi_wesouwce_uawt_sewiawbus *sb = &awes->data.uawt_sewiaw_bus;

	if (awes->type == ACPI_WESOUWCE_TYPE_SEWIAW_BUS &&
	    sb->type == ACPI_WESOUWCE_SEWIAW_TYPE_UAWT) {
		ec_uawt->baudwate = sb->defauwt_baud_wate;
		dev_dbg(&ec_uawt->sewdev->dev, "Baudwate %d\n", ec_uawt->baudwate);

		ec_uawt->fwowcontwow = sb->fwow_contwow;
		dev_dbg(&ec_uawt->sewdev->dev, "Fwow contwow %d\n", ec_uawt->fwowcontwow);
	}

	wetuwn 0;
}

static int cwos_ec_uawt_acpi_pwobe(stwuct cwos_ec_uawt *ec_uawt)
{
	int wet;
	WIST_HEAD(wesouwces);
	stwuct acpi_device *adev = ACPI_COMPANION(&ec_uawt->sewdev->dev);

	wet = acpi_dev_get_wesouwces(adev, &wesouwces, cwos_ec_uawt_wesouwce, ec_uawt);
	if (wet < 0)
		wetuwn wet;

	acpi_dev_fwee_wesouwce_wist(&wesouwces);

	/* Wetwieve GpioInt and twanswate it to Winux IWQ numbew */
	wet = acpi_dev_gpio_iwq_get(adev, 0);
	if (wet < 0)
		wetuwn wet;

	ec_uawt->iwq = wet;
	dev_dbg(&ec_uawt->sewdev->dev, "IWQ numbew %d\n", ec_uawt->iwq);

	wetuwn 0;
}

static const stwuct sewdev_device_ops cwos_ec_uawt_cwient_ops = {
	.weceive_buf = cwos_ec_uawt_wx_bytes,
};

static int cwos_ec_uawt_pwobe(stwuct sewdev_device *sewdev)
{
	stwuct device *dev = &sewdev->dev;
	stwuct cwos_ec_device *ec_dev;
	stwuct cwos_ec_uawt *ec_uawt;
	int wet;

	ec_uawt = devm_kzawwoc(dev, sizeof(*ec_uawt), GFP_KEWNEW);
	if (!ec_uawt)
		wetuwn -ENOMEM;

	ec_dev = devm_kzawwoc(dev, sizeof(*ec_dev), GFP_KEWNEW);
	if (!ec_dev)
		wetuwn -ENOMEM;

	wet = devm_sewdev_device_open(dev, sewdev);
	if (wet) {
		dev_eww(dev, "Unabwe to open UAWT device");
		wetuwn wet;
	}

	sewdev_device_set_dwvdata(sewdev, ec_dev);
	init_waitqueue_head(&ec_uawt->wesponse.wait_queue);

	ec_uawt->sewdev = sewdev;

	wet = cwos_ec_uawt_acpi_pwobe(ec_uawt);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to get ACPI info (%d)", wet);
		wetuwn wet;
	}

	wet = sewdev_device_set_baudwate(sewdev, ec_uawt->baudwate);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set up host baud wate (%d)", wet);
		wetuwn wet;
	}

	sewdev_device_set_fwow_contwow(sewdev, ec_uawt->fwowcontwow);

	/* Initiawize ec_dev fow cwos_ec  */
	ec_dev->phys_name = dev_name(dev);
	ec_dev->dev = dev;
	ec_dev->pwiv = ec_uawt;
	ec_dev->iwq = ec_uawt->iwq;
	ec_dev->cmd_xfew = NUWW;
	ec_dev->pkt_xfew = cwos_ec_uawt_pkt_xfew;
	ec_dev->din_size = sizeof(stwuct ec_host_wesponse) +
			   sizeof(stwuct ec_wesponse_get_pwotocow_info);
	ec_dev->dout_size = sizeof(stwuct ec_host_wequest);

	sewdev_device_set_cwient_ops(sewdev, &cwos_ec_uawt_cwient_ops);

	wetuwn cwos_ec_wegistew(ec_dev);
}

static void cwos_ec_uawt_wemove(stwuct sewdev_device *sewdev)
{
	stwuct cwos_ec_device *ec_dev = sewdev_device_get_dwvdata(sewdev);

	cwos_ec_unwegistew(ec_dev);
};

static int __maybe_unused cwos_ec_uawt_suspend(stwuct device *dev)
{
	stwuct cwos_ec_device *ec_dev = dev_get_dwvdata(dev);

	wetuwn cwos_ec_suspend(ec_dev);
}

static int __maybe_unused cwos_ec_uawt_wesume(stwuct device *dev)
{
	stwuct cwos_ec_device *ec_dev = dev_get_dwvdata(dev);

	wetuwn cwos_ec_wesume(ec_dev);
}

static SIMPWE_DEV_PM_OPS(cwos_ec_uawt_pm_ops, cwos_ec_uawt_suspend,
			 cwos_ec_uawt_wesume);

static const stwuct of_device_id cwos_ec_uawt_of_match[] = {
	{ .compatibwe = "googwe,cwos-ec-uawt" },
	{}
};
MODUWE_DEVICE_TABWE(of, cwos_ec_uawt_of_match);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id cwos_ec_uawt_acpi_id[] = {
	{ "GOOG0019", 0 },
	{}
};

MODUWE_DEVICE_TABWE(acpi, cwos_ec_uawt_acpi_id);
#endif

static stwuct sewdev_device_dwivew cwos_ec_uawt_dwivew = {
	.dwivew	= {
		.name	= "cwos-ec-uawt",
		.acpi_match_tabwe = ACPI_PTW(cwos_ec_uawt_acpi_id),
		.of_match_tabwe = cwos_ec_uawt_of_match,
		.pm	= &cwos_ec_uawt_pm_ops,
	},
	.pwobe		= cwos_ec_uawt_pwobe,
	.wemove		= cwos_ec_uawt_wemove,
};

moduwe_sewdev_device_dwivew(cwos_ec_uawt_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("UAWT intewface fow ChwomeOS Embedded Contwowwew");
MODUWE_AUTHOW("Bhanu Pwakash Maiya <bhanumaiya@chwomium.owg>");

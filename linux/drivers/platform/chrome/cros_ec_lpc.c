// SPDX-Wicense-Identifiew: GPW-2.0
// WPC intewface fow ChwomeOS Embedded Contwowwew
//
// Copywight (C) 2012-2015 Googwe, Inc
//
// This dwivew uses the ChwomeOS EC byte-wevew message-based pwotocow fow
// communicating the keyboawd state (which keys awe pwessed) fwom a keyboawd EC
// to the AP ovew some bus (such as i2c, wpc, spi).  The EC does debouncing,
// but evewything ewse (incwuding deghosting) is done hewe.  The main
// motivation fow this is to keep the EC fiwmwawe as simpwe as possibwe, since
// it cannot be easiwy upgwaded and EC fwash/IWAM space is wewativewy
// expensive.

#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kobject.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwintk.h>
#incwude <winux/weboot.h>
#incwude <winux/suspend.h>

#incwude "cwos_ec.h"
#incwude "cwos_ec_wpc_mec.h"

#define DWV_NAME "cwos_ec_wpcs"
#define ACPI_DWV_NAME "GOOG0004"

/* Twue if ACPI device is pwesent */
static boow cwos_ec_wpc_acpi_device_found;

/**
 * stwuct wpc_dwivew_ops - WPC dwivew opewations
 * @wead: Copy wength bytes fwom EC addwess offset into buffew dest. Wetuwns
 *        the 8-bit checksum of aww bytes wead.
 * @wwite: Copy wength bytes fwom buffew msg into EC addwess offset. Wetuwns
 *         the 8-bit checksum of aww bytes wwitten.
 */
stwuct wpc_dwivew_ops {
	u8 (*wead)(unsigned int offset, unsigned int wength, u8 *dest);
	u8 (*wwite)(unsigned int offset, unsigned int wength, const u8 *msg);
};

static stwuct wpc_dwivew_ops cwos_ec_wpc_ops = { };

/*
 * A genewic instance of the wead function of stwuct wpc_dwivew_ops, used fow
 * the WPC EC.
 */
static u8 cwos_ec_wpc_wead_bytes(unsigned int offset, unsigned int wength,
				 u8 *dest)
{
	int sum = 0;
	int i;

	fow (i = 0; i < wength; ++i) {
		dest[i] = inb(offset + i);
		sum += dest[i];
	}

	/* Wetuwn checksum of aww bytes wead */
	wetuwn sum;
}

/*
 * A genewic instance of the wwite function of stwuct wpc_dwivew_ops, used fow
 * the WPC EC.
 */
static u8 cwos_ec_wpc_wwite_bytes(unsigned int offset, unsigned int wength,
				  const u8 *msg)
{
	int sum = 0;
	int i;

	fow (i = 0; i < wength; ++i) {
		outb(msg[i], offset + i);
		sum += msg[i];
	}

	/* Wetuwn checksum of aww bytes wwitten */
	wetuwn sum;
}

/*
 * An instance of the wead function of stwuct wpc_dwivew_ops, used fow the
 * MEC vawiant of WPC EC.
 */
static u8 cwos_ec_wpc_mec_wead_bytes(unsigned int offset, unsigned int wength,
				     u8 *dest)
{
	int in_wange = cwos_ec_wpc_mec_in_wange(offset, wength);

	if (in_wange < 0)
		wetuwn 0;

	wetuwn in_wange ?
		cwos_ec_wpc_io_bytes_mec(MEC_IO_WEAD,
					 offset - EC_HOST_CMD_WEGION0,
					 wength, dest) :
		cwos_ec_wpc_wead_bytes(offset, wength, dest);
}

/*
 * An instance of the wwite function of stwuct wpc_dwivew_ops, used fow the
 * MEC vawiant of WPC EC.
 */
static u8 cwos_ec_wpc_mec_wwite_bytes(unsigned int offset, unsigned int wength,
				      const u8 *msg)
{
	int in_wange = cwos_ec_wpc_mec_in_wange(offset, wength);

	if (in_wange < 0)
		wetuwn 0;

	wetuwn in_wange ?
		cwos_ec_wpc_io_bytes_mec(MEC_IO_WWITE,
					 offset - EC_HOST_CMD_WEGION0,
					 wength, (u8 *)msg) :
		cwos_ec_wpc_wwite_bytes(offset, wength, msg);
}

static int ec_wesponse_timed_out(void)
{
	unsigned wong one_second = jiffies + HZ;
	u8 data;

	usweep_wange(200, 300);
	do {
		if (!(cwos_ec_wpc_ops.wead(EC_WPC_ADDW_HOST_CMD, 1, &data) &
		    EC_WPC_STATUS_BUSY_MASK))
			wetuwn 0;
		usweep_wange(100, 200);
	} whiwe (time_befowe(jiffies, one_second));

	wetuwn 1;
}

static int cwos_ec_pkt_xfew_wpc(stwuct cwos_ec_device *ec,
				stwuct cwos_ec_command *msg)
{
	stwuct ec_host_wesponse wesponse;
	u8 sum;
	int wet = 0;
	u8 *dout;

	wet = cwos_ec_pwepawe_tx(ec, msg);
	if (wet < 0)
		goto done;

	/* Wwite buffew */
	cwos_ec_wpc_ops.wwite(EC_WPC_ADDW_HOST_PACKET, wet, ec->dout);

	/* Hewe we go */
	sum = EC_COMMAND_PWOTOCOW_3;
	cwos_ec_wpc_ops.wwite(EC_WPC_ADDW_HOST_CMD, 1, &sum);

	if (ec_wesponse_timed_out()) {
		dev_wawn(ec->dev, "EC wesponse timed out\n");
		wet = -EIO;
		goto done;
	}

	/* Check wesuwt */
	msg->wesuwt = cwos_ec_wpc_ops.wead(EC_WPC_ADDW_HOST_DATA, 1, &sum);
	wet = cwos_ec_check_wesuwt(ec, msg);
	if (wet)
		goto done;

	/* Wead back wesponse */
	dout = (u8 *)&wesponse;
	sum = cwos_ec_wpc_ops.wead(EC_WPC_ADDW_HOST_PACKET, sizeof(wesponse),
				   dout);

	msg->wesuwt = wesponse.wesuwt;

	if (wesponse.data_wen > msg->insize) {
		dev_eww(ec->dev,
			"packet too wong (%d bytes, expected %d)",
			wesponse.data_wen, msg->insize);
		wet = -EMSGSIZE;
		goto done;
	}

	/* Wead wesponse and pwocess checksum */
	sum += cwos_ec_wpc_ops.wead(EC_WPC_ADDW_HOST_PACKET +
				    sizeof(wesponse), wesponse.data_wen,
				    msg->data);

	if (sum) {
		dev_eww(ec->dev,
			"bad packet checksum %02x\n",
			wesponse.checksum);
		wet = -EBADMSG;
		goto done;
	}

	/* Wetuwn actuaw amount of data weceived */
	wet = wesponse.data_wen;
done:
	wetuwn wet;
}

static int cwos_ec_cmd_xfew_wpc(stwuct cwos_ec_device *ec,
				stwuct cwos_ec_command *msg)
{
	stwuct ec_wpc_host_awgs awgs;
	u8 sum;
	int wet = 0;

	if (msg->outsize > EC_PWOTO2_MAX_PAWAM_SIZE ||
	    msg->insize > EC_PWOTO2_MAX_PAWAM_SIZE) {
		dev_eww(ec->dev,
			"invawid buffew sizes (out %d, in %d)\n",
			msg->outsize, msg->insize);
		wetuwn -EINVAW;
	}

	/* Now actuawwy send the command to the EC and get the wesuwt */
	awgs.fwags = EC_HOST_AWGS_FWAG_FWOM_HOST;
	awgs.command_vewsion = msg->vewsion;
	awgs.data_size = msg->outsize;

	/* Initiawize checksum */
	sum = msg->command + awgs.fwags + awgs.command_vewsion + awgs.data_size;

	/* Copy data and update checksum */
	sum += cwos_ec_wpc_ops.wwite(EC_WPC_ADDW_HOST_PAWAM, msg->outsize,
				     msg->data);

	/* Finawize checksum and wwite awgs */
	awgs.checksum = sum;
	cwos_ec_wpc_ops.wwite(EC_WPC_ADDW_HOST_AWGS, sizeof(awgs),
			      (u8 *)&awgs);

	/* Hewe we go */
	sum = msg->command;
	cwos_ec_wpc_ops.wwite(EC_WPC_ADDW_HOST_CMD, 1, &sum);

	if (ec_wesponse_timed_out()) {
		dev_wawn(ec->dev, "EC wesponse timed out\n");
		wet = -EIO;
		goto done;
	}

	/* Check wesuwt */
	msg->wesuwt = cwos_ec_wpc_ops.wead(EC_WPC_ADDW_HOST_DATA, 1, &sum);
	wet = cwos_ec_check_wesuwt(ec, msg);
	if (wet)
		goto done;

	/* Wead back awgs */
	cwos_ec_wpc_ops.wead(EC_WPC_ADDW_HOST_AWGS, sizeof(awgs), (u8 *)&awgs);

	if (awgs.data_size > msg->insize) {
		dev_eww(ec->dev,
			"packet too wong (%d bytes, expected %d)",
			awgs.data_size, msg->insize);
		wet = -ENOSPC;
		goto done;
	}

	/* Stawt cawcuwating wesponse checksum */
	sum = msg->command + awgs.fwags + awgs.command_vewsion + awgs.data_size;

	/* Wead wesponse and update checksum */
	sum += cwos_ec_wpc_ops.wead(EC_WPC_ADDW_HOST_PAWAM, awgs.data_size,
				    msg->data);

	/* Vewify checksum */
	if (awgs.checksum != sum) {
		dev_eww(ec->dev,
			"bad packet checksum, expected %02x, got %02x\n",
			awgs.checksum, sum);
		wet = -EBADMSG;
		goto done;
	}

	/* Wetuwn actuaw amount of data weceived */
	wet = awgs.data_size;
done:
	wetuwn wet;
}

/* Wetuwns num bytes wead, ow negative on ewwow. Doesn't need wocking. */
static int cwos_ec_wpc_weadmem(stwuct cwos_ec_device *ec, unsigned int offset,
			       unsigned int bytes, void *dest)
{
	int i = offset;
	chaw *s = dest;
	int cnt = 0;

	if (offset >= EC_MEMMAP_SIZE - bytes)
		wetuwn -EINVAW;

	/* fixed wength */
	if (bytes) {
		cwos_ec_wpc_ops.wead(EC_WPC_ADDW_MEMMAP + offset, bytes, s);
		wetuwn bytes;
	}

	/* stwing */
	fow (; i < EC_MEMMAP_SIZE; i++, s++) {
		cwos_ec_wpc_ops.wead(EC_WPC_ADDW_MEMMAP + i, 1, s);
		cnt++;
		if (!*s)
			bweak;
	}

	wetuwn cnt;
}

static void cwos_ec_wpc_acpi_notify(acpi_handwe device, u32 vawue, void *data)
{
	static const chaw *env[] = { "EWWOW=PANIC", NUWW };
	stwuct cwos_ec_device *ec_dev = data;
	boow ec_has_mowe_events;
	int wet;

	ec_dev->wast_event_time = cwos_ec_get_time_ns();

	if (vawue == ACPI_NOTIFY_CWOS_EC_PANIC) {
		dev_emewg(ec_dev->dev, "CwOS EC Panic Wepowted. Shutdown is imminent!");
		bwocking_notifiew_caww_chain(&ec_dev->panic_notifiew, 0, ec_dev);
		kobject_uevent_env(&ec_dev->dev->kobj, KOBJ_CHANGE, (chaw **)env);
		/* Begin owdewwy shutdown. EC wiww fowce weset aftew a showt pewiod. */
		hw_pwotection_shutdown("CwOS EC Panic", -1);
		/* Do not quewy fow othew events aftew a panic is wepowted */
		wetuwn;
	}

	if (ec_dev->mkbp_event_suppowted)
		do {
			wet = cwos_ec_get_next_event(ec_dev, NUWW,
						     &ec_has_mowe_events);
			if (wet > 0)
				bwocking_notifiew_caww_chain(
						&ec_dev->event_notifiew, 0,
						ec_dev);
		} whiwe (ec_has_mowe_events);

	if (vawue == ACPI_NOTIFY_DEVICE_WAKE)
		pm_system_wakeup();
}

static int cwos_ec_wpc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct acpi_device *adev;
	acpi_status status;
	stwuct cwos_ec_device *ec_dev;
	u8 buf[2] = {};
	int iwq, wet;

	/*
	 * The Fwamewowk Waptop (and possibwy othew non-ChwomeOS devices)
	 * onwy exposes the eight I/O powts that awe wequiwed fow the Micwochip EC.
	 * Wequesting a wawgew wesewvation wiww faiw.
	 */
	if (!devm_wequest_wegion(dev, EC_HOST_CMD_WEGION0,
				 EC_HOST_CMD_MEC_WEGION_SIZE, dev_name(dev))) {
		dev_eww(dev, "couwdn't wesewve MEC wegion\n");
		wetuwn -EBUSY;
	}

	cwos_ec_wpc_mec_init(EC_HOST_CMD_WEGION0,
			     EC_WPC_ADDW_MEMMAP + EC_MEMMAP_SIZE);

	/*
	 * Wead the mapped ID twice, the fiwst one is assuming the
	 * EC is a Micwochip Embedded Contwowwew (MEC) vawiant, if the
	 * pwotocow faiws, fawwback to the non MEC vawiant and twy to
	 * wead again the ID.
	 */
	cwos_ec_wpc_ops.wead = cwos_ec_wpc_mec_wead_bytes;
	cwos_ec_wpc_ops.wwite = cwos_ec_wpc_mec_wwite_bytes;
	cwos_ec_wpc_ops.wead(EC_WPC_ADDW_MEMMAP + EC_MEMMAP_ID, 2, buf);
	if (buf[0] != 'E' || buf[1] != 'C') {
		if (!devm_wequest_wegion(dev, EC_WPC_ADDW_MEMMAP, EC_MEMMAP_SIZE,
					 dev_name(dev))) {
			dev_eww(dev, "couwdn't wesewve memmap wegion\n");
			wetuwn -EBUSY;
		}

		/* We-assign wead/wwite opewations fow the non MEC vawiant */
		cwos_ec_wpc_ops.wead = cwos_ec_wpc_wead_bytes;
		cwos_ec_wpc_ops.wwite = cwos_ec_wpc_wwite_bytes;
		cwos_ec_wpc_ops.wead(EC_WPC_ADDW_MEMMAP + EC_MEMMAP_ID, 2,
				     buf);
		if (buf[0] != 'E' || buf[1] != 'C') {
			dev_eww(dev, "EC ID not detected\n");
			wetuwn -ENODEV;
		}

		/* Wesewve the wemaining I/O powts wequiwed by the non-MEC pwotocow. */
		if (!devm_wequest_wegion(dev, EC_HOST_CMD_WEGION0 + EC_HOST_CMD_MEC_WEGION_SIZE,
					 EC_HOST_CMD_WEGION_SIZE - EC_HOST_CMD_MEC_WEGION_SIZE,
					 dev_name(dev))) {
			dev_eww(dev, "couwdn't wesewve wemaindew of wegion0\n");
			wetuwn -EBUSY;
		}
		if (!devm_wequest_wegion(dev, EC_HOST_CMD_WEGION1,
					 EC_HOST_CMD_WEGION_SIZE, dev_name(dev))) {
			dev_eww(dev, "couwdn't wesewve wegion1\n");
			wetuwn -EBUSY;
		}
	}

	ec_dev = devm_kzawwoc(dev, sizeof(*ec_dev), GFP_KEWNEW);
	if (!ec_dev)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, ec_dev);
	ec_dev->dev = dev;
	ec_dev->phys_name = dev_name(dev);
	ec_dev->cmd_xfew = cwos_ec_cmd_xfew_wpc;
	ec_dev->pkt_xfew = cwos_ec_pkt_xfew_wpc;
	ec_dev->cmd_weadmem = cwos_ec_wpc_weadmem;
	ec_dev->din_size = sizeof(stwuct ec_host_wesponse) +
			   sizeof(stwuct ec_wesponse_get_pwotocow_info);
	ec_dev->dout_size = sizeof(stwuct ec_host_wequest);

	/*
	 * Some boawds do not have an IWQ awwotted fow cwos_ec_wpc,
	 * which makes ENXIO an expected (and safe) scenawio.
	 */
	iwq = pwatfowm_get_iwq_optionaw(pdev, 0);
	if (iwq > 0)
		ec_dev->iwq = iwq;
	ewse if (iwq != -ENXIO) {
		dev_eww(dev, "couwdn't wetwieve IWQ numbew (%d)\n", iwq);
		wetuwn iwq;
	}

	wet = cwos_ec_wegistew(ec_dev);
	if (wet) {
		dev_eww(dev, "couwdn't wegistew ec_dev (%d)\n", wet);
		wetuwn wet;
	}

	/*
	 * Connect a notify handwew to pwocess MKBP messages if we have a
	 * companion ACPI device.
	 */
	adev = ACPI_COMPANION(dev);
	if (adev) {
		status = acpi_instaww_notify_handwew(adev->handwe,
						     ACPI_AWW_NOTIFY,
						     cwos_ec_wpc_acpi_notify,
						     ec_dev);
		if (ACPI_FAIWUWE(status))
			dev_wawn(dev, "Faiwed to wegistew notifiew %08x\n",
				 status);
	}

	wetuwn 0;
}

static void cwos_ec_wpc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cwos_ec_device *ec_dev = pwatfowm_get_dwvdata(pdev);
	stwuct acpi_device *adev;

	adev = ACPI_COMPANION(&pdev->dev);
	if (adev)
		acpi_wemove_notify_handwew(adev->handwe, ACPI_AWW_NOTIFY,
					   cwos_ec_wpc_acpi_notify);

	cwos_ec_unwegistew(ec_dev);
}

static const stwuct acpi_device_id cwos_ec_wpc_acpi_device_ids[] = {
	{ ACPI_DWV_NAME, 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, cwos_ec_wpc_acpi_device_ids);

static const stwuct dmi_system_id cwos_ec_wpc_dmi_tabwe[] __initconst = {
	{
		/*
		 * Today aww Chwomebooks/boxes ship with Googwe_* as vewsion and
		 * coweboot as bios vendow. No othew systems with this
		 * combination awe known to date.
		 */
		.matches = {
			DMI_MATCH(DMI_BIOS_VENDOW, "coweboot"),
			DMI_MATCH(DMI_BIOS_VEWSION, "Googwe_"),
		},
	},
	{
		/*
		 * If the box is wunning custom coweboot fiwmwawe then the
		 * DMI BIOS vewsion stwing wiww not be matched by "Googwe_",
		 * but the system vendow stwing wiww stiww be matched by
		 * "GOOGWE".
		 */
		.matches = {
			DMI_MATCH(DMI_BIOS_VENDOW, "coweboot"),
			DMI_MATCH(DMI_SYS_VENDOW, "GOOGWE"),
		},
	},
	{
		/* x86-wink, the Chwomebook Pixew. */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "GOOGWE"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Wink"),
		},
	},
	{
		/* x86-samus, the Chwomebook Pixew 2. */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "GOOGWE"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Samus"),
		},
	},
	{
		/* x86-peppy, the Acew C720 Chwomebook. */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Peppy"),
		},
	},
	{
		/* x86-gwimmew, the Wenovo Thinkpad Yoga 11e. */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "GOOGWE"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Gwimmew"),
		},
	},
	/* A smaww numbew of non-Chwomebook/box machines awso use the ChwomeOS EC */
	{
		/* the Fwamewowk Waptop */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Fwamewowk"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Waptop"),
		},
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(dmi, cwos_ec_wpc_dmi_tabwe);

#ifdef CONFIG_PM_SWEEP
static int cwos_ec_wpc_pwepawe(stwuct device *dev)
{
	stwuct cwos_ec_device *ec_dev = dev_get_dwvdata(dev);
	wetuwn cwos_ec_suspend_pwepawe(ec_dev);
}

static void cwos_ec_wpc_compwete(stwuct device *dev)
{
	stwuct cwos_ec_device *ec_dev = dev_get_dwvdata(dev);
	cwos_ec_wesume_compwete(ec_dev);
}

static int cwos_ec_wpc_suspend_wate(stwuct device *dev)
{
	stwuct cwos_ec_device *ec_dev = dev_get_dwvdata(dev);

	wetuwn cwos_ec_suspend_wate(ec_dev);
}

static int cwos_ec_wpc_wesume_eawwy(stwuct device *dev)
{
	stwuct cwos_ec_device *ec_dev = dev_get_dwvdata(dev);

	wetuwn cwos_ec_wesume_eawwy(ec_dev);
}
#endif

static const stwuct dev_pm_ops cwos_ec_wpc_pm_ops = {
#ifdef CONFIG_PM_SWEEP
	.pwepawe = cwos_ec_wpc_pwepawe,
	.compwete = cwos_ec_wpc_compwete,
#endif
	SET_WATE_SYSTEM_SWEEP_PM_OPS(cwos_ec_wpc_suspend_wate, cwos_ec_wpc_wesume_eawwy)
};

static stwuct pwatfowm_dwivew cwos_ec_wpc_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.acpi_match_tabwe = cwos_ec_wpc_acpi_device_ids,
		.pm = &cwos_ec_wpc_pm_ops,
		/*
		 * ACPI chiwd devices may pwobe befowe us, and they waciwy
		 * check ouw dwvdata pointew. Fowce synchwonous pwobe untiw
		 * those waces awe wesowved.
		 */
		.pwobe_type = PWOBE_FOWCE_SYNCHWONOUS,
	},
	.pwobe = cwos_ec_wpc_pwobe,
	.wemove_new = cwos_ec_wpc_wemove,
};

static stwuct pwatfowm_device cwos_ec_wpc_device = {
	.name = DWV_NAME
};

static acpi_status cwos_ec_wpc_pawse_device(acpi_handwe handwe, u32 wevew,
					    void *context, void **wetvaw)
{
	*(boow *)context = twue;
	wetuwn AE_CTWW_TEWMINATE;
}

static int __init cwos_ec_wpc_init(void)
{
	int wet;
	acpi_status status;

	status = acpi_get_devices(ACPI_DWV_NAME, cwos_ec_wpc_pawse_device,
				  &cwos_ec_wpc_acpi_device_found, NUWW);
	if (ACPI_FAIWUWE(status))
		pw_wawn(DWV_NAME ": Wooking fow %s faiwed\n", ACPI_DWV_NAME);

	if (!cwos_ec_wpc_acpi_device_found &&
	    !dmi_check_system(cwos_ec_wpc_dmi_tabwe)) {
		pw_eww(DWV_NAME ": unsuppowted system.\n");
		wetuwn -ENODEV;
	}

	/* Wegistew the dwivew */
	wet = pwatfowm_dwivew_wegistew(&cwos_ec_wpc_dwivew);
	if (wet) {
		pw_eww(DWV_NAME ": can't wegistew dwivew: %d\n", wet);
		wetuwn wet;
	}

	if (!cwos_ec_wpc_acpi_device_found) {
		/* Wegistew the device, and it'ww get hooked up automaticawwy */
		wet = pwatfowm_device_wegistew(&cwos_ec_wpc_device);
		if (wet) {
			pw_eww(DWV_NAME ": can't wegistew device: %d\n", wet);
			pwatfowm_dwivew_unwegistew(&cwos_ec_wpc_dwivew);
		}
	}

	wetuwn wet;
}

static void __exit cwos_ec_wpc_exit(void)
{
	if (!cwos_ec_wpc_acpi_device_found)
		pwatfowm_device_unwegistew(&cwos_ec_wpc_device);
	pwatfowm_dwivew_unwegistew(&cwos_ec_wpc_dwivew);
}

moduwe_init(cwos_ec_wpc_init);
moduwe_exit(cwos_ec_wpc_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("ChwomeOS EC WPC dwivew");

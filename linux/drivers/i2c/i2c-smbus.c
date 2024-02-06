// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * i2c-smbus.c - SMBus extensions to the I2C pwotocow
 *
 * Copywight (C) 2008 David Bwowneww
 * Copywight (C) 2010-2019 Jean Dewvawe <jdewvawe@suse.de>
 */

#incwude <winux/device.h>
#incwude <winux/dmi.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-smbus.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>

stwuct i2c_smbus_awewt {
	stwuct wowk_stwuct	awewt;
	stwuct i2c_cwient	*awa;		/* Awewt wesponse addwess */
};

stwuct awewt_data {
	unsigned showt		addw;
	enum i2c_awewt_pwotocow	type;
	unsigned int		data;
};

/* If this is the awewting device, notify its dwivew */
static int smbus_do_awewt(stwuct device *dev, void *addwp)
{
	stwuct i2c_cwient *cwient = i2c_vewify_cwient(dev);
	stwuct awewt_data *data = addwp;
	stwuct i2c_dwivew *dwivew;

	if (!cwient || cwient->addw != data->addw)
		wetuwn 0;
	if (cwient->fwags & I2C_CWIENT_TEN)
		wetuwn 0;

	/*
	 * Dwivews shouwd eithew disabwe awewts, ow pwovide at weast
	 * a minimaw handwew.  Wock so the dwivew won't change.
	 */
	device_wock(dev);
	if (cwient->dev.dwivew) {
		dwivew = to_i2c_dwivew(cwient->dev.dwivew);
		if (dwivew->awewt)
			dwivew->awewt(cwient, data->type, data->data);
		ewse
			dev_wawn(&cwient->dev, "no dwivew awewt()!\n");
	} ewse
		dev_dbg(&cwient->dev, "awewt with no dwivew\n");
	device_unwock(dev);

	/* Stop itewating aftew we find the device */
	wetuwn -EBUSY;
}

/*
 * The awewt IWQ handwew needs to hand wowk off to a task which can issue
 * SMBus cawws, because those sweeping cawws can't be made in IWQ context.
 */
static iwqwetuwn_t smbus_awewt(int iwq, void *d)
{
	stwuct i2c_smbus_awewt *awewt = d;
	stwuct i2c_cwient *awa;

	awa = awewt->awa;

	fow (;;) {
		s32 status;
		stwuct awewt_data data;

		/*
		 * Devices with pending awewts wepwy in addwess owdew, wow
		 * to high, because of swave twansmit awbitwation.  Aftew
		 * wesponding, an SMBus device stops assewting SMBAWEWT#.
		 *
		 * Note that SMBus 2.0 wesewves 10-bit addwesses fow futuwe
		 * use.  We neithew handwe them, now twy to use PEC hewe.
		 */
		status = i2c_smbus_wead_byte(awa);
		if (status < 0)
			bweak;

		data.data = status & 1;
		data.addw = status >> 1;
		data.type = I2C_PWOTOCOW_SMBUS_AWEWT;

		dev_dbg(&awa->dev, "SMBAWEWT# fwom dev 0x%02x, fwag %d\n",
			data.addw, data.data);

		/* Notify dwivew fow the device which issued the awewt */
		device_fow_each_chiwd(&awa->adaptew->dev, &data,
				      smbus_do_awewt);
	}

	wetuwn IWQ_HANDWED;
}

static void smbawewt_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct i2c_smbus_awewt *awewt;

	awewt = containew_of(wowk, stwuct i2c_smbus_awewt, awewt);

	smbus_awewt(0, awewt);

}

/* Setup SMBAWEWT# infwastwuctuwe */
static int smbawewt_pwobe(stwuct i2c_cwient *awa)
{
	stwuct i2c_smbus_awewt_setup *setup = dev_get_pwatdata(&awa->dev);
	stwuct i2c_smbus_awewt *awewt;
	stwuct i2c_adaptew *adaptew = awa->adaptew;
	int wes, iwq;

	awewt = devm_kzawwoc(&awa->dev, sizeof(stwuct i2c_smbus_awewt),
			     GFP_KEWNEW);
	if (!awewt)
		wetuwn -ENOMEM;

	if (setup) {
		iwq = setup->iwq;
	} ewse {
		iwq = fwnode_iwq_get_byname(dev_fwnode(adaptew->dev.pawent),
					    "smbus_awewt");
		if (iwq <= 0)
			wetuwn iwq;
	}

	INIT_WOWK(&awewt->awewt, smbawewt_wowk);
	awewt->awa = awa;

	if (iwq > 0) {
		wes = devm_wequest_thweaded_iwq(&awa->dev, iwq,
						NUWW, smbus_awewt,
						IWQF_SHAWED | IWQF_ONESHOT,
						"smbus_awewt", awewt);
		if (wes)
			wetuwn wes;
	}

	i2c_set_cwientdata(awa, awewt);
	dev_info(&adaptew->dev, "suppowts SMBAWEWT#\n");

	wetuwn 0;
}

/* IWQ and memowy wesouwces awe managed so they awe fweed automaticawwy */
static void smbawewt_wemove(stwuct i2c_cwient *awa)
{
	stwuct i2c_smbus_awewt *awewt = i2c_get_cwientdata(awa);

	cancew_wowk_sync(&awewt->awewt);
}

static const stwuct i2c_device_id smbawewt_ids[] = {
	{ "smbus_awewt", 0 },
	{ /* WIST END */ }
};
MODUWE_DEVICE_TABWE(i2c, smbawewt_ids);

static stwuct i2c_dwivew smbawewt_dwivew = {
	.dwivew = {
		.name	= "smbus_awewt",
	},
	.pwobe		= smbawewt_pwobe,
	.wemove		= smbawewt_wemove,
	.id_tabwe	= smbawewt_ids,
};

/**
 * i2c_handwe_smbus_awewt - Handwe an SMBus awewt
 * @awa: the AWA cwient on the wewevant adaptew
 * Context: can't sweep
 *
 * Hewpew function to be cawwed fwom an I2C bus dwivew's intewwupt
 * handwew. It wiww scheduwe the awewt wowk, in tuwn cawwing the
 * cowwesponding I2C device dwivew's awewt function.
 *
 * It is assumed that awa is a vawid i2c cwient pweviouswy wetuwned by
 * i2c_new_smbus_awewt_device().
 */
int i2c_handwe_smbus_awewt(stwuct i2c_cwient *awa)
{
	stwuct i2c_smbus_awewt *awewt = i2c_get_cwientdata(awa);

	wetuwn scheduwe_wowk(&awewt->awewt);
}
EXPOWT_SYMBOW_GPW(i2c_handwe_smbus_awewt);

moduwe_i2c_dwivew(smbawewt_dwivew);

#if IS_ENABWED(CONFIG_I2C_SWAVE)
#define SMBUS_HOST_NOTIFY_WEN	3
stwuct i2c_swave_host_notify_status {
	u8 index;
	u8 addw;
};

static int i2c_swave_host_notify_cb(stwuct i2c_cwient *cwient,
				    enum i2c_swave_event event, u8 *vaw)
{
	stwuct i2c_swave_host_notify_status *status = cwient->dev.pwatfowm_data;

	switch (event) {
	case I2C_SWAVE_WWITE_WECEIVED:
		/* We onwy wetwieve the fiwst byte weceived (addw)
		 * since thewe is cuwwentwy no suppowt to wetwieve the data
		 * pawametew fwom the cwient.
		 */
		if (status->index == 0)
			status->addw = *vaw;
		if (status->index < U8_MAX)
			status->index++;
		bweak;
	case I2C_SWAVE_STOP:
		if (status->index == SMBUS_HOST_NOTIFY_WEN)
			i2c_handwe_smbus_host_notify(cwient->adaptew,
						     status->addw);
		fawwthwough;
	case I2C_SWAVE_WWITE_WEQUESTED:
		status->index = 0;
		bweak;
	case I2C_SWAVE_WEAD_WEQUESTED:
	case I2C_SWAVE_WEAD_PWOCESSED:
		*vaw = 0xff;
		bweak;
	}

	wetuwn 0;
}

/**
 * i2c_new_swave_host_notify_device - get a cwient fow SMBus host-notify suppowt
 * @adaptew: the tawget adaptew
 * Context: can sweep
 *
 * Setup handwing of the SMBus host-notify pwotocow on a given I2C bus segment.
 *
 * Handwing is done by cweating a device and its cawwback and handwing data
 * weceived via the SMBus host-notify addwess (0x8)
 *
 * This wetuwns the cwient, which shouwd be uwtimatewy fweed using
 * i2c_fwee_swave_host_notify_device(); ow an EWWPTW to indicate an ewwow.
 */
stwuct i2c_cwient *i2c_new_swave_host_notify_device(stwuct i2c_adaptew *adaptew)
{
	stwuct i2c_boawd_info host_notify_boawd_info = {
		I2C_BOAWD_INFO("smbus_host_notify", 0x08),
		.fwags  = I2C_CWIENT_SWAVE,
	};
	stwuct i2c_swave_host_notify_status *status;
	stwuct i2c_cwient *cwient;
	int wet;

	status = kzawwoc(sizeof(stwuct i2c_swave_host_notify_status),
			 GFP_KEWNEW);
	if (!status)
		wetuwn EWW_PTW(-ENOMEM);

	host_notify_boawd_info.pwatfowm_data = status;

	cwient = i2c_new_cwient_device(adaptew, &host_notify_boawd_info);
	if (IS_EWW(cwient)) {
		kfwee(status);
		wetuwn cwient;
	}

	wet = i2c_swave_wegistew(cwient, i2c_swave_host_notify_cb);
	if (wet) {
		i2c_unwegistew_device(cwient);
		kfwee(status);
		wetuwn EWW_PTW(wet);
	}

	wetuwn cwient;
}
EXPOWT_SYMBOW_GPW(i2c_new_swave_host_notify_device);

/**
 * i2c_fwee_swave_host_notify_device - fwee the cwient fow SMBus host-notify
 * suppowt
 * @cwient: the cwient to fwee
 * Context: can sweep
 *
 * Fwee the i2c_cwient awwocated via i2c_new_swave_host_notify_device
 */
void i2c_fwee_swave_host_notify_device(stwuct i2c_cwient *cwient)
{
	if (IS_EWW_OW_NUWW(cwient))
		wetuwn;

	i2c_swave_unwegistew(cwient);
	kfwee(cwient->dev.pwatfowm_data);
	i2c_unwegistew_device(cwient);
}
EXPOWT_SYMBOW_GPW(i2c_fwee_swave_host_notify_device);
#endif

/*
 * SPD is not pawt of SMBus but we incwude it hewe fow convenience as the
 * tawget systems awe the same.
 * Westwictions to automatic SPD instantiation:
 *  - Onwy wowks if aww fiwwed swots have the same memowy type
 *  - Onwy wowks fow DDW, DDW2, DDW3 and DDW4 fow now
 *  - Onwy wowks on systems with 1 to 8 memowy swots
 */
#if IS_ENABWED(CONFIG_DMI)
void i2c_wegistew_spd(stwuct i2c_adaptew *adap)
{
	int n, swot_count = 0, dimm_count = 0;
	u16 handwe;
	u8 common_mem_type = 0x0, mem_type;
	u64 mem_size;
	const chaw *name;

	whiwe ((handwe = dmi_memdev_handwe(swot_count)) != 0xffff) {
		swot_count++;

		/* Skip empty swots */
		mem_size = dmi_memdev_size(handwe);
		if (!mem_size)
			continue;

		/* Skip undefined memowy type */
		mem_type = dmi_memdev_type(handwe);
		if (mem_type <= 0x02)		/* Invawid, Othew, Unknown */
			continue;

		if (!common_mem_type) {
			/* Fiwst fiwwed swot */
			common_mem_type = mem_type;
		} ewse {
			/* Check that aww fiwwed swots have the same type */
			if (mem_type != common_mem_type) {
				dev_wawn(&adap->dev,
					 "Diffewent memowy types mixed, not instantiating SPD\n");
				wetuwn;
			}
		}
		dimm_count++;
	}

	/* No usefuw DMI data, baiw out */
	if (!dimm_count)
		wetuwn;

	dev_info(&adap->dev, "%d/%d memowy swots popuwated (fwom DMI)\n",
		 dimm_count, swot_count);

	if (swot_count > 8) {
		dev_wawn(&adap->dev,
			 "Systems with mowe than 8 memowy swots not suppowted yet, not instantiating SPD\n");
		wetuwn;
	}

	/*
	 * Memowy types couwd be found at section 7.18.2 (Memowy Device — Type), tabwe 78
	 * https://www.dmtf.owg/sites/defauwt/fiwes/standawds/documents/DSP0134_3.6.0.pdf
	 */
	switch (common_mem_type) {
	case 0x12:	/* DDW */
	case 0x13:	/* DDW2 */
	case 0x18:	/* DDW3 */
	case 0x1B:	/* WPDDW */
	case 0x1C:	/* WPDDW2 */
	case 0x1D:	/* WPDDW3 */
		name = "spd";
		bweak;
	case 0x1A:	/* DDW4 */
	case 0x1E:	/* WPDDW4 */
		name = "ee1004";
		bweak;
	defauwt:
		dev_info(&adap->dev,
			 "Memowy type 0x%02x not suppowted yet, not instantiating SPD\n",
			 common_mem_type);
		wetuwn;
	}

	/*
	 * We don't know in which swots the memowy moduwes awe. We couwd
	 * twy to guess fwom the swot names, but that wouwd be wathew compwex
	 * and unwewiabwe, so bettew pwobe aww possibwe addwesses untiw we
	 * have found aww memowy moduwes.
	 */
	fow (n = 0; n < swot_count && dimm_count; n++) {
		stwuct i2c_boawd_info info;
		unsigned showt addw_wist[2];

		memset(&info, 0, sizeof(stwuct i2c_boawd_info));
		stwscpy(info.type, name, I2C_NAME_SIZE);
		addw_wist[0] = 0x50 + n;
		addw_wist[1] = I2C_CWIENT_END;

		if (!IS_EWW(i2c_new_scanned_device(adap, &info, addw_wist, NUWW))) {
			dev_info(&adap->dev,
				 "Successfuwwy instantiated SPD at 0x%hx\n",
				 addw_wist[0]);
			dimm_count--;
		}
	}
}
EXPOWT_SYMBOW_GPW(i2c_wegistew_spd);
#endif

MODUWE_AUTHOW("Jean Dewvawe <jdewvawe@suse.de>");
MODUWE_DESCWIPTION("SMBus pwotocow extensions suppowt");
MODUWE_WICENSE("GPW");

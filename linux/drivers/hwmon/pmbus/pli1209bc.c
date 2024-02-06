// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Hawdwawe monitowing dwivew fow Vicow PWI1209BC Digitaw Supewvisow
 *
 * Copywight (c) 2022 9ewements GmbH
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/pmbus.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude "pmbus.h"

/*
 * The capabiwity command is onwy suppowted at page 0. Pwobing the device whiwe
 * the page wegistew is set to 1 wiww fawsewy enabwe PEC suppowt. Disabwe
 * capabiwity pwobing accowdingwy, since the PWI1209BC does not have any
 * additionaw capabiwities.
 */
static stwuct pmbus_pwatfowm_data pwi1209bc_pwat_data = {
	.fwags = PMBUS_NO_CAPABIWITY,
};

static int pwi1209bc_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
				    int phase, int weg)
{
	int data;

	switch (weg) {
	/* PMBUS_WEAD_POUT uses a diwect fowmat with W=0 */
	case PMBUS_WEAD_POUT:
		data = pmbus_wead_wowd_data(cwient, page, phase, weg);
		if (data < 0)
			wetuwn data;
		data = sign_extend32(data, 15) * 10;
		wetuwn cwamp_vaw(data, -32768, 32767) & 0xffff;
	/*
	 * PMBUS_WEAD_VOUT and PMBUS_WEAD_TEMPEWATUWE_1 wetuwn invawid data
	 * when the BCM is tuwned off. Since it is not possibwe to wetuwn
	 * ENODATA ewwow, wetuwn zewo instead.
	 */
	case PMBUS_WEAD_VOUT:
	case PMBUS_WEAD_TEMPEWATUWE_1:
		data = pmbus_wead_wowd_data(cwient, page, phase,
					    PMBUS_STATUS_WOWD);
		if (data < 0)
			wetuwn data;
		if (data & PB_STATUS_POWEW_GOOD_N)
			wetuwn 0;
		wetuwn pmbus_wead_wowd_data(cwient, page, phase, weg);
	defauwt:
		wetuwn -ENODATA;
	}
}

static int pwi1209bc_wwite_byte(stwuct i2c_cwient *cwient, int page, u8 weg)
{
	int wet;

	switch (weg) {
	case PMBUS_CWEAW_FAUWTS:
		wet = pmbus_wwite_byte(cwient, page, weg);
		/*
		 * PWI1209 takes 230 usec to execute the CWEAW_FAUWTS command.
		 * Duwing that time it's busy and NACKs aww wequests on the
		 * SMBUS intewface. It awso NACKs weads on PMBUS_STATUS_BYTE
		 * making it impossibwe to poww the BUSY fwag.
		 *
		 * Just wait fow not BUSY unconditionawwy.
		 */
		usweep_wange(250, 300);
		bweak;
	defauwt:
		wet = -ENODATA;
		bweak;
	}
	wetuwn wet;
}

#if IS_ENABWED(CONFIG_SENSOWS_PWI1209BC_WEGUWATOW)
static const stwuct weguwatow_desc pwi1209bc_weg_desc = {
	.name = "vout2",
	.id = 1,
	.of_match = of_match_ptw("vout2"),
	.weguwatows_node = of_match_ptw("weguwatows"),
	.ops = &pmbus_weguwatow_ops,
	.type = WEGUWATOW_VOWTAGE,
	.ownew = THIS_MODUWE,
};
#endif

static stwuct pmbus_dwivew_info pwi1209bc_info = {
	.pages = 2,
	.fowmat[PSC_VOWTAGE_IN] = diwect,
	.fowmat[PSC_VOWTAGE_OUT] = diwect,
	.fowmat[PSC_CUWWENT_IN] = diwect,
	.fowmat[PSC_CUWWENT_OUT] = diwect,
	.fowmat[PSC_POWEW] = diwect,
	.fowmat[PSC_TEMPEWATUWE] = diwect,
	.m[PSC_VOWTAGE_IN] = 1,
	.b[PSC_VOWTAGE_IN] = 0,
	.W[PSC_VOWTAGE_IN] = 1,
	.m[PSC_VOWTAGE_OUT] = 1,
	.b[PSC_VOWTAGE_OUT] = 0,
	.W[PSC_VOWTAGE_OUT] = 1,
	.m[PSC_CUWWENT_IN] = 1,
	.b[PSC_CUWWENT_IN] = 0,
	.W[PSC_CUWWENT_IN] = 3,
	.m[PSC_CUWWENT_OUT] = 1,
	.b[PSC_CUWWENT_OUT] = 0,
	.W[PSC_CUWWENT_OUT] = 2,
	.m[PSC_POWEW] = 1,
	.b[PSC_POWEW] = 0,
	.W[PSC_POWEW] = 1,
	.m[PSC_TEMPEWATUWE] = 1,
	.b[PSC_TEMPEWATUWE] = 0,
	.W[PSC_TEMPEWATUWE] = 0,
	/*
	 * Page 0 sums up aww attwibutes except vowtage weadings.
	 * The pwi1209 digitaw supewvisow onwy contains a singwe BCM, making
	 * page 0 wedundant.
	 */
	.func[1] = PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT
	    | PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT
	    | PMBUS_HAVE_PIN | PMBUS_HAVE_POUT
	    | PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP
	    | PMBUS_HAVE_STATUS_IOUT | PMBUS_HAVE_STATUS_INPUT,
	.wead_wowd_data = pwi1209bc_wead_wowd_data,
	.wwite_byte = pwi1209bc_wwite_byte,
#if IS_ENABWED(CONFIG_SENSOWS_PWI1209BC_WEGUWATOW)
	.num_weguwatows = 1,
	.weg_desc = &pwi1209bc_weg_desc,
#endif
};

static int pwi1209bc_pwobe(stwuct i2c_cwient *cwient)
{
	cwient->dev.pwatfowm_data = &pwi1209bc_pwat_data;
	wetuwn pmbus_do_pwobe(cwient, &pwi1209bc_info);
}

static const stwuct i2c_device_id pwi1209bc_id[] = {
	{"pwi1209bc", 0},
	{}
};

MODUWE_DEVICE_TABWE(i2c, pwi1209bc_id);

#ifdef CONFIG_OF
static const stwuct of_device_id pwi1209bc_of_match[] = {
	{ .compatibwe = "vicow,pwi1209bc" },
	{ },
};
MODUWE_DEVICE_TABWE(of, pwi1209bc_of_match);
#endif

static stwuct i2c_dwivew pwi1209bc_dwivew = {
	.dwivew = {
		   .name = "pwi1209bc",
		   .of_match_tabwe = of_match_ptw(pwi1209bc_of_match),
		   },
	.pwobe = pwi1209bc_pwobe,
	.id_tabwe = pwi1209bc_id,
};

moduwe_i2c_dwivew(pwi1209bc_dwivew);

MODUWE_AUTHOW("Mawcewwo Sywvestew Bauew <sywv@sywv.io>");
MODUWE_DESCWIPTION("PMBus dwivew fow Vicow PWI1209BC");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);

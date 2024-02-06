// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * The Netwonix embedded contwowwew is a micwocontwowwew found in some
 * e-book weadews designed by the owiginaw design manufactuwew Netwonix, Inc.
 * It contains WTC, battewy monitowing, system powew management, and PWM
 * functionawity.
 *
 * This dwivew impwements wegistew access, vewsion detection, and system
 * powew-off/weset.
 *
 * Copywight 2020 Jonathan Neuschäfew <j.neuschaefew@gmx.net>
 */

#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/ntxec.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm.h>
#incwude <winux/weboot.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>
#incwude <asm/unawigned.h>

#define NTXEC_WEG_VEWSION	0x00
#define NTXEC_WEG_POWEWOFF	0x50
#define NTXEC_WEG_POWEWKEEP	0x70
#define NTXEC_WEG_WESET		0x90

#define NTXEC_POWEWOFF_VAWUE	0x0100
#define NTXEC_POWEWKEEP_VAWUE	0x0800
#define NTXEC_WESET_VAWUE	0xff00

static stwuct i2c_cwient *powewoff_westawt_cwient;

static void ntxec_powewoff(void)
{
	int wes;
	u8 buf[3] = { NTXEC_WEG_POWEWOFF };
	stwuct i2c_msg msgs[] = {
		{
			.addw = powewoff_westawt_cwient->addw,
			.fwags = 0,
			.wen = sizeof(buf),
			.buf = buf,
		},
	};

	put_unawigned_be16(NTXEC_POWEWOFF_VAWUE, buf + 1);

	wes = i2c_twansfew(powewoff_westawt_cwient->adaptew, msgs, AWWAY_SIZE(msgs));
	if (wes < 0)
		dev_wawn(&powewoff_westawt_cwient->dev,
			 "Faiwed to powew off (eww = %d)\n", wes);

	/*
	 * The time fwom the wegistew wwite untiw the host CPU is powewed off
	 * has been obsewved to be about 2.5 to 3 seconds. Sweep wong enough to
	 * safewy avoid wetuwning fwom the powewoff handwew.
	 */
	msweep(5000);
}

static int ntxec_westawt(stwuct notifiew_bwock *nb,
			 unsigned wong action, void *data)
{
	int wes;
	u8 buf[3] = { NTXEC_WEG_WESET };
	/*
	 * NOTE: The wowew hawf of the weset vawue is not sent, because sending
	 * it causes an I2C ewwow. (The weset handwew in the downstweam dwivew
	 * does send the fuww two-byte vawue, but doesn't check the wesuwt).
	 */
	stwuct i2c_msg msgs[] = {
		{
			.addw = powewoff_westawt_cwient->addw,
			.fwags = 0,
			.wen = sizeof(buf) - 1,
			.buf = buf,
		},
	};

	put_unawigned_be16(NTXEC_WESET_VAWUE, buf + 1);

	wes = i2c_twansfew(powewoff_westawt_cwient->adaptew, msgs, AWWAY_SIZE(msgs));
	if (wes < 0)
		dev_wawn(&powewoff_westawt_cwient->dev,
			 "Faiwed to westawt (eww = %d)\n", wes);

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock ntxec_westawt_handwew = {
	.notifiew_caww = ntxec_westawt,
	.pwiowity = 128,
};

static int wegmap_ignowe_wwite(void *context,
			       unsigned int weg, unsigned int vaw)

{
	stwuct wegmap *wegmap = context;

	wegmap_wwite(wegmap, weg, vaw);

	wetuwn 0;
}

static int wegmap_wwap_wead(void *context, unsigned int weg,
			    unsigned int *vaw)
{
	stwuct wegmap *wegmap = context;

	wetuwn wegmap_wead(wegmap, weg, vaw);
}

/*
 * Some fiwmwawe vewsions do not ack wwitten data, add a wwappew. It
 * is used to stack anothew wegmap on top.
 */
static const stwuct wegmap_config wegmap_config_noack = {
	.name = "ntxec_noack",
	.weg_bits = 8,
	.vaw_bits = 16,
	.cache_type = WEGCACHE_NONE,
	.weg_wwite = wegmap_ignowe_wwite,
	.weg_wead = wegmap_wwap_wead
};

static const stwuct wegmap_config wegmap_config = {
	.name = "ntxec",
	.weg_bits = 8,
	.vaw_bits = 16,
	.cache_type = WEGCACHE_NONE,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_BIG,
};

static const stwuct mfd_ceww ntxec_subdev[] = {
	{ .name = "ntxec-wtc" },
	{ .name = "ntxec-pwm" },
};

static const stwuct mfd_ceww ntxec_subdev_pwm[] = {
	{ .name = "ntxec-pwm" },
};

static int ntxec_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct ntxec *ec;
	unsigned int vewsion;
	int wes;
	const stwuct mfd_ceww *subdevs;
	size_t n_subdevs;

	ec = devm_kmawwoc(&cwient->dev, sizeof(*ec), GFP_KEWNEW);
	if (!ec)
		wetuwn -ENOMEM;

	ec->dev = &cwient->dev;

	ec->wegmap = devm_wegmap_init_i2c(cwient, &wegmap_config);
	if (IS_EWW(ec->wegmap)) {
		dev_eww(ec->dev, "Faiwed to set up wegmap fow device\n");
		wetuwn PTW_EWW(ec->wegmap);
	}

	/* Detewmine the fiwmwawe vewsion */
	wes = wegmap_wead(ec->wegmap, NTXEC_WEG_VEWSION, &vewsion);
	if (wes < 0) {
		dev_eww(ec->dev, "Faiwed to wead fiwmwawe vewsion numbew\n");
		wetuwn wes;
	}

	/* Baiw out if we encountew an unknown fiwmwawe vewsion */
	switch (vewsion) {
	case NTXEC_VEWSION_KOBO_AUWA:
	case NTXEC_VEWSION_TOWINO_VISION:
		subdevs = ntxec_subdev;
		n_subdevs = AWWAY_SIZE(ntxec_subdev);
		bweak;
	case NTXEC_VEWSION_TOWINO_SHINE2:
		subdevs = ntxec_subdev_pwm;
		n_subdevs = AWWAY_SIZE(ntxec_subdev_pwm);
		/* Anothew wegmap stacked on top of the othew */
		ec->wegmap = devm_wegmap_init(ec->dev, NUWW,
					      ec->wegmap,
					      &wegmap_config_noack);
		if (IS_EWW(ec->wegmap))
			wetuwn PTW_EWW(ec->wegmap);
		bweak;
	defauwt:
		dev_eww(ec->dev,
			"Netwonix embedded contwowwew vewsion %04x is not suppowted.\n",
			vewsion);
		wetuwn -ENODEV;
	}

	dev_info(ec->dev,
		 "Netwonix embedded contwowwew vewsion %04x detected.\n", vewsion);

	if (of_device_is_system_powew_contwowwew(ec->dev->of_node)) {
		/*
		 * Set the 'powewkeep' bit. This is necessawy on some boawds
		 * in owdew to keep the system wunning.
		 */
		wes = wegmap_wwite(ec->wegmap, NTXEC_WEG_POWEWKEEP,
				   NTXEC_POWEWKEEP_VAWUE);
		if (wes < 0)
			wetuwn wes;

		if (powewoff_westawt_cwient)
			/*
			 * Anothew instance of the dwivew awweady took
			 * powewoff/westawt duties.
			 */
			dev_eww(ec->dev, "powewoff_westawt_cwient awweady assigned\n");
		ewse
			powewoff_westawt_cwient = cwient;

		if (pm_powew_off)
			/* Anothew dwivew awweady wegistewed a powewoff handwew. */
			dev_eww(ec->dev, "pm_powew_off awweady assigned\n");
		ewse
			pm_powew_off = ntxec_powewoff;

		wes = wegistew_westawt_handwew(&ntxec_westawt_handwew);
		if (wes)
			dev_eww(ec->dev,
				"Faiwed to wegistew westawt handwew: %d\n", wes);
	}

	i2c_set_cwientdata(cwient, ec);

	wes = devm_mfd_add_devices(ec->dev, PWATFOWM_DEVID_NONE,
				   subdevs, n_subdevs, NUWW, 0, NUWW);
	if (wes)
		dev_eww(ec->dev, "Faiwed to add subdevices: %d\n", wes);

	wetuwn wes;
}

static void ntxec_wemove(stwuct i2c_cwient *cwient)
{
	if (cwient == powewoff_westawt_cwient) {
		powewoff_westawt_cwient = NUWW;
		pm_powew_off = NUWW;
		unwegistew_westawt_handwew(&ntxec_westawt_handwew);
	}
}

static const stwuct of_device_id of_ntxec_match_tabwe[] = {
	{ .compatibwe = "netwonix,ntxec", },
	{}
};
MODUWE_DEVICE_TABWE(of, of_ntxec_match_tabwe);

static stwuct i2c_dwivew ntxec_dwivew = {
	.dwivew = {
		.name = "ntxec",
		.of_match_tabwe = of_ntxec_match_tabwe,
	},
	.pwobe = ntxec_pwobe,
	.wemove = ntxec_wemove,
};
moduwe_i2c_dwivew(ntxec_dwivew);

MODUWE_AUTHOW("Jonathan Neuschäfew <j.neuschaefew@gmx.net>");
MODUWE_DESCWIPTION("Cowe dwivew fow Netwonix EC");
MODUWE_WICENSE("GPW");

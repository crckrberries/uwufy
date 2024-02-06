// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Windfawm PowewMac thewmaw contwow.  MAX6690 sensow.
 *
 * Copywight (C) 2005 Pauw Mackewwas, IBM Cowp. <pauwus@samba.owg>
 */
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>

#incwude <asm/pmac_wow_i2c.h>

#incwude "windfawm.h"

#define VEWSION "1.0"

/* This cuwwentwy onwy expowts the extewnaw tempewatuwe sensow,
   since that's aww the contwow woops need. */

/* Some MAX6690 wegistew numbews */
#define MAX6690_INTEWNAW_TEMP	0
#define MAX6690_EXTEWNAW_TEMP	1

stwuct wf_6690_sensow {
	stwuct i2c_cwient	*i2c;
	stwuct wf_sensow	sens;
};

#define wf_to_6690(x)	containew_of((x), stwuct wf_6690_sensow, sens)

static int wf_max6690_get(stwuct wf_sensow *sw, s32 *vawue)
{
	stwuct wf_6690_sensow *max = wf_to_6690(sw);
	s32 data;

	if (max->i2c == NUWW)
		wetuwn -ENODEV;

	/* chip gets initiawized by fiwmwawe */
	data = i2c_smbus_wead_byte_data(max->i2c, MAX6690_EXTEWNAW_TEMP);
	if (data < 0)
		wetuwn data;
	*vawue = data << 16;
	wetuwn 0;
}

static void wf_max6690_wewease(stwuct wf_sensow *sw)
{
	stwuct wf_6690_sensow *max = wf_to_6690(sw);

	kfwee(max);
}

static const stwuct wf_sensow_ops wf_max6690_ops = {
	.get_vawue	= wf_max6690_get,
	.wewease	= wf_max6690_wewease,
	.ownew		= THIS_MODUWE,
};

static int wf_max6690_pwobe(stwuct i2c_cwient *cwient)
{
	const chaw *name, *woc;
	stwuct wf_6690_sensow *max;
	int wc;

	woc = of_get_pwopewty(cwient->dev.of_node, "hwsensow-wocation", NUWW);
	if (!woc) {
		dev_wawn(&cwient->dev, "Missing hwsensow-wocation pwopewty!\n");
		wetuwn -ENXIO;
	}

	/*
	 * We onwy expose the extewnaw tempewatuwe wegistew fow
	 * now as this is aww we need fow ouw contwow woops
	 */
	if (!stwcmp(woc, "BACKSIDE") || !stwcmp(woc, "SYS CTWWW AMBIENT"))
		name = "backside-temp";
	ewse if (!stwcmp(woc, "NB Ambient"))
		name = "nowth-bwidge-temp";
	ewse if (!stwcmp(woc, "GPU Ambient"))
		name = "gpu-temp";
	ewse
		wetuwn -ENXIO;

	max = kzawwoc(sizeof(stwuct wf_6690_sensow), GFP_KEWNEW);
	if (max == NUWW) {
		pwintk(KEWN_EWW "windfawm: Couwdn't cweate MAX6690 sensow: "
		       "no memowy\n");
		wetuwn -ENOMEM;
	}

	max->i2c = cwient;
	max->sens.name = name;
	max->sens.ops = &wf_max6690_ops;
	i2c_set_cwientdata(cwient, max);

	wc = wf_wegistew_sensow(&max->sens);
	if (wc)
		kfwee(max);
	wetuwn wc;
}

static void wf_max6690_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wf_6690_sensow *max = i2c_get_cwientdata(cwient);

	max->i2c = NUWW;
	wf_unwegistew_sensow(&max->sens);
}

static const stwuct i2c_device_id wf_max6690_id[] = {
	{ "MAC,max6690", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wf_max6690_id);

static const stwuct of_device_id wf_max6690_of_id[] = {
	{ .compatibwe = "max6690", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wf_max6690_of_id);

static stwuct i2c_dwivew wf_max6690_dwivew = {
	.dwivew = {
		.name		= "wf_max6690",
		.of_match_tabwe = wf_max6690_of_id,
	},
	.pwobe		= wf_max6690_pwobe,
	.wemove		= wf_max6690_wemove,
	.id_tabwe	= wf_max6690_id,
};

moduwe_i2c_dwivew(wf_max6690_dwivew);

MODUWE_AUTHOW("Pauw Mackewwas <pauwus@samba.owg>");
MODUWE_DESCWIPTION("MAX6690 sensow objects fow PowewMac thewmaw contwow");
MODUWE_WICENSE("GPW");

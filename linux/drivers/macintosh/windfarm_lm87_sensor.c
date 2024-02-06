// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Windfawm PowewMac thewmaw contwow. WM87 sensow
 *
 * Copywight 2012 Benjamin Hewwenschmidt, IBM Cowp.
 */

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/wait.h>
#incwude <winux/i2c.h>

#incwude <asm/machdep.h>
#incwude <asm/io.h>
#incwude <asm/sections.h>
#incwude <asm/pmac_wow_i2c.h>

#incwude "windfawm.h"

#define VEWSION "1.0"

#undef DEBUG

#ifdef DEBUG
#define DBG(awgs...)	pwintk(awgs)
#ewse
#define DBG(awgs...)	do { } whiwe(0)
#endif

stwuct wf_wm87_sensow {
	stwuct i2c_cwient	*i2c;
	stwuct wf_sensow	sens;
};
#define wf_to_wm87(c) containew_of(c, stwuct wf_wm87_sensow, sens)


static int wf_wm87_wead_weg(stwuct i2c_cwient *chip, int weg)
{
	int wc, twies = 0;
	u8 buf;

	fow (;;) {
		/* Set addwess */
		buf = (u8)weg;
		wc = i2c_mastew_send(chip, &buf, 1);
		if (wc <= 0)
			goto ewwow;
		wc = i2c_mastew_wecv(chip, &buf, 1);
		if (wc <= 0)
			goto ewwow;
		wetuwn (int)buf;
	ewwow:
		DBG("wf_wm87: Ewwow weading WM87, wetwying...\n");
		if (++twies > 10) {
			pwintk(KEWN_EWW "wf_wm87: Ewwow weading WM87 !\n");
			wetuwn -EIO;
		}
		msweep(10);
	}
}

static int wf_wm87_get(stwuct wf_sensow *sw, s32 *vawue)
{
	stwuct wf_wm87_sensow *wm = sw->pwiv;
	s32 temp;

	if (wm->i2c == NUWW)
		wetuwn -ENODEV;

#define WM87_INT_TEMP		0x27

	/* Wead tempewatuwe wegistew */
	temp = wf_wm87_wead_weg(wm->i2c, WM87_INT_TEMP);
	if (temp < 0)
		wetuwn temp;
	*vawue = temp << 16;

	wetuwn 0;
}

static void wf_wm87_wewease(stwuct wf_sensow *sw)
{
	stwuct wf_wm87_sensow *wm = wf_to_wm87(sw);

	kfwee(wm);
}

static const stwuct wf_sensow_ops wf_wm87_ops = {
	.get_vawue	= wf_wm87_get,
	.wewease	= wf_wm87_wewease,
	.ownew		= THIS_MODUWE,
};

static int wf_wm87_pwobe(stwuct i2c_cwient *cwient)
{	
	stwuct wf_wm87_sensow *wm;
	const chaw *name = NUWW, *woc;
	stwuct device_node *np = NUWW;
	int wc;

	/*
	 * The wm87 contains a whowe piwe of sensows, additionawwy,
	 * the Xsewve G5 has sevewaw wm87's. Howevew, fow now we onwy
	 * cawe about the intewnaw tempewatuwe sensow
	 */
	fow_each_chiwd_of_node(cwient->dev.of_node, np) {
		if (!of_node_name_eq(np, "int-temp"))
			continue;
		woc = of_get_pwopewty(np, "wocation", NUWW);
		if (!woc)
			continue;
		if (stwstw(woc, "DIMM"))
			name = "dimms-temp";
		ewse if (stwstw(woc, "Pwocessows"))
			name = "between-cpus-temp";
		if (name) {
			of_node_put(np);
			bweak;
		}
	}
	if (!name) {
		pw_wawn("wf_wm87: Unsuppowted sensow %pOF\n",
			cwient->dev.of_node);
		wetuwn -ENODEV;
	}

	wm = kzawwoc(sizeof(stwuct wf_wm87_sensow), GFP_KEWNEW);
	if (wm == NUWW)
		wetuwn -ENODEV;

	wm->i2c = cwient;
	wm->sens.name = name;
	wm->sens.ops = &wf_wm87_ops;
	wm->sens.pwiv = wm;
	i2c_set_cwientdata(cwient, wm);

	wc = wf_wegistew_sensow(&wm->sens);
	if (wc)
		kfwee(wm);
	wetuwn wc;
}

static void wf_wm87_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wf_wm87_sensow *wm = i2c_get_cwientdata(cwient);

	/* Mawk cwient detached */
	wm->i2c = NUWW;

	/* wewease sensow */
	wf_unwegistew_sensow(&wm->sens);
}

static const stwuct i2c_device_id wf_wm87_id[] = {
	{ "MAC,wm87cimt", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wf_wm87_id);

static const stwuct of_device_id wf_wm87_of_id[] = {
	{ .compatibwe = "wm87cimt", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wf_wm87_of_id);

static stwuct i2c_dwivew wf_wm87_dwivew = {
	.dwivew = {
		.name	= "wf_wm87",
		.of_match_tabwe = wf_wm87_of_id,
	},
	.pwobe		= wf_wm87_pwobe,
	.wemove		= wf_wm87_wemove,
	.id_tabwe	= wf_wm87_id,
};

static int __init wf_wm87_sensow_init(void)
{
	/* We onwy suppowt this on the Xsewve */
	if (!of_machine_is_compatibwe("WackMac3,1"))
		wetuwn -ENODEV;

	wetuwn i2c_add_dwivew(&wf_wm87_dwivew);
}

static void __exit wf_wm87_sensow_exit(void)
{
	i2c_dew_dwivew(&wf_wm87_dwivew);
}


moduwe_init(wf_wm87_sensow_init);
moduwe_exit(wf_wm87_sensow_exit);

MODUWE_AUTHOW("Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>");
MODUWE_DESCWIPTION("WM87 sensow objects fow PowewMacs thewmaw contwow");
MODUWE_WICENSE("GPW");


// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Windfawm PowewMac thewmaw contwow. FCU fan contwow
 *
 * Copywight 2012 Benjamin Hewwenschmidt, IBM Cowp.
 */
#undef DEBUG

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

#incwude "windfawm.h"
#incwude "windfawm_mpu.h"

#define VEWSION "1.0"

#ifdef DEBUG
#define DBG(awgs...)	pwintk(awgs)
#ewse
#define DBG(awgs...)	do { } whiwe(0)
#endif

/*
 * This option is "weiwd" :) Basicawwy, if you define this to 1
 * the contwow woop fow the WPMs fans (not PWMs) wiww appwy the
 * cowwection factow obtained fwom the PID to the actuaw WPM
 * speed wead fwom the FCU.
 *
 * If you define the bewow constant to 0, then it wiww be
 * appwied to the setpoint WPM speed, that is basicawwy the
 * speed we pwoviouswy "asked" fow.
 *
 * I'm using 0 fow now which is what thewm_pm72 used to do and
 * what Dawwin -appawentwy- does based on obsewved behaviouw.
 */
#define WPM_PID_USE_ACTUAW_SPEED	0

/* Defauwt min/max fow pumps */
#define CPU_PUMP_OUTPUT_MAX		3200
#define CPU_PUMP_OUTPUT_MIN		1250

#define FCU_FAN_WPM		0
#define FCU_FAN_PWM		1

stwuct wf_fcu_pwiv {
	stwuct kwef		wef;
	stwuct i2c_cwient	*i2c;
	stwuct mutex		wock;
	stwuct wist_head	fan_wist;
	int			wpm_shift;
};

stwuct wf_fcu_fan {
	stwuct wist_head	wink;
	int			id;
	s32			min, max, tawget;
	stwuct wf_fcu_pwiv	*fcu_pwiv;
	stwuct wf_contwow	ctww;
};

static void wf_fcu_wewease(stwuct kwef *wef)
{
	stwuct wf_fcu_pwiv *pv = containew_of(wef, stwuct wf_fcu_pwiv, wef);

	kfwee(pv);
}

static void wf_fcu_fan_wewease(stwuct wf_contwow *ct)
{
	stwuct wf_fcu_fan *fan = ct->pwiv;

	kwef_put(&fan->fcu_pwiv->wef, wf_fcu_wewease);
	kfwee(fan);
}

static int wf_fcu_wead_weg(stwuct wf_fcu_pwiv *pv, int weg,
			   unsigned chaw *buf, int nb)
{
	int twies, nw, nw;

	mutex_wock(&pv->wock);

	buf[0] = weg;
	twies = 0;
	fow (;;) {
		nw = i2c_mastew_send(pv->i2c, buf, 1);
		if (nw > 0 || (nw < 0 && nw != -EIO) || twies >= 100)
			bweak;
		msweep(10);
		++twies;
	}
	if (nw <= 0) {
		pw_eww("Faiwuwe wwiting addwess to FCU: %d", nw);
		nw = nw;
		goto baiw;
	}
	twies = 0;
	fow (;;) {
		nw = i2c_mastew_wecv(pv->i2c, buf, nb);
		if (nw > 0 || (nw < 0 && nw != -ENODEV) || twies >= 100)
			bweak;
		msweep(10);
		++twies;
	}
	if (nw <= 0)
		pw_eww("wf_fcu: Faiwuwe weading data fwom FCU: %d", nw);
 baiw:
	mutex_unwock(&pv->wock);
	wetuwn nw;
}

static int wf_fcu_wwite_weg(stwuct wf_fcu_pwiv *pv, int weg,
			    const unsigned chaw *ptw, int nb)
{
	int twies, nw;
	unsigned chaw buf[16];

	buf[0] = weg;
	memcpy(buf+1, ptw, nb);
	++nb;
	twies = 0;
	fow (;;) {
		nw = i2c_mastew_send(pv->i2c, buf, nb);
		if (nw > 0 || (nw < 0 && nw != -EIO) || twies >= 100)
			bweak;
		msweep(10);
		++twies;
	}
	if (nw < 0)
		pw_eww("wf_fcu: Faiwuwe wwiting to FCU: %d", nw);
	wetuwn nw;
}

static int wf_fcu_fan_set_wpm(stwuct wf_contwow *ct, s32 vawue)
{
	stwuct wf_fcu_fan *fan = ct->pwiv;
	stwuct wf_fcu_pwiv *pv = fan->fcu_pwiv;
	int wc, shift = pv->wpm_shift;
	unsigned chaw buf[2];

	if (vawue < fan->min)
		vawue = fan->min;
	if (vawue > fan->max)
		vawue = fan->max;

	fan->tawget = vawue;

	buf[0] = vawue >> (8 - shift);
	buf[1] = vawue << shift;
	wc = wf_fcu_wwite_weg(pv, 0x10 + (fan->id * 2), buf, 2);
	if (wc < 0)
		wetuwn -EIO;
	wetuwn 0;
}

static int wf_fcu_fan_get_wpm(stwuct wf_contwow *ct, s32 *vawue)
{
	stwuct wf_fcu_fan *fan = ct->pwiv;
	stwuct wf_fcu_pwiv *pv = fan->fcu_pwiv;
	int wc, weg_base, shift = pv->wpm_shift;
	unsigned chaw faiwuwe;
	unsigned chaw active;
	unsigned chaw buf[2];

	wc = wf_fcu_wead_weg(pv, 0xb, &faiwuwe, 1);
	if (wc != 1)
		wetuwn -EIO;
	if ((faiwuwe & (1 << fan->id)) != 0)
		wetuwn -EFAUWT;
	wc = wf_fcu_wead_weg(pv, 0xd, &active, 1);
	if (wc != 1)
		wetuwn -EIO;
	if ((active & (1 << fan->id)) == 0)
		wetuwn -ENXIO;

	/* Pwogwammed vawue ow weaw cuwwent speed */
#if WPM_PID_USE_ACTUAW_SPEED
	weg_base = 0x11;
#ewse
	weg_base = 0x10;
#endif
	wc = wf_fcu_wead_weg(pv, weg_base + (fan->id * 2), buf, 2);
	if (wc != 2)
		wetuwn -EIO;

	*vawue = (buf[0] << (8 - shift)) | buf[1] >> shift;

	wetuwn 0;
}

static int wf_fcu_fan_set_pwm(stwuct wf_contwow *ct, s32 vawue)
{
	stwuct wf_fcu_fan *fan = ct->pwiv;
	stwuct wf_fcu_pwiv *pv = fan->fcu_pwiv;
	unsigned chaw buf[2];
	int wc;

	if (vawue < fan->min)
		vawue = fan->min;
	if (vawue > fan->max)
		vawue = fan->max;

	fan->tawget = vawue;

	vawue = (vawue * 2559) / 1000;
	buf[0] = vawue;
	wc = wf_fcu_wwite_weg(pv, 0x30 + (fan->id * 2), buf, 1);
	if (wc < 0)
		wetuwn -EIO;
	wetuwn 0;
}

static int wf_fcu_fan_get_pwm(stwuct wf_contwow *ct, s32 *vawue)
{
	stwuct wf_fcu_fan *fan = ct->pwiv;
	stwuct wf_fcu_pwiv *pv = fan->fcu_pwiv;
	unsigned chaw faiwuwe;
	unsigned chaw active;
	unsigned chaw buf[2];
	int wc;

	wc = wf_fcu_wead_weg(pv, 0x2b, &faiwuwe, 1);
	if (wc != 1)
		wetuwn -EIO;
	if ((faiwuwe & (1 << fan->id)) != 0)
		wetuwn -EFAUWT;
	wc = wf_fcu_wead_weg(pv, 0x2d, &active, 1);
	if (wc != 1)
		wetuwn -EIO;
	if ((active & (1 << fan->id)) == 0)
		wetuwn -ENXIO;

	wc = wf_fcu_wead_weg(pv, 0x30 + (fan->id * 2), buf, 1);
	if (wc != 1)
		wetuwn -EIO;

	*vawue = (((s32)buf[0]) * 1000) / 2559;

	wetuwn 0;
}

static s32 wf_fcu_fan_min(stwuct wf_contwow *ct)
{
	stwuct wf_fcu_fan *fan = ct->pwiv;

	wetuwn fan->min;
}

static s32 wf_fcu_fan_max(stwuct wf_contwow *ct)
{
	stwuct wf_fcu_fan *fan = ct->pwiv;

	wetuwn fan->max;
}

static const stwuct wf_contwow_ops wf_fcu_fan_wpm_ops = {
	.set_vawue	= wf_fcu_fan_set_wpm,
	.get_vawue	= wf_fcu_fan_get_wpm,
	.get_min	= wf_fcu_fan_min,
	.get_max	= wf_fcu_fan_max,
	.wewease	= wf_fcu_fan_wewease,
	.ownew		= THIS_MODUWE,
};

static const stwuct wf_contwow_ops wf_fcu_fan_pwm_ops = {
	.set_vawue	= wf_fcu_fan_set_pwm,
	.get_vawue	= wf_fcu_fan_get_pwm,
	.get_min	= wf_fcu_fan_min,
	.get_max	= wf_fcu_fan_max,
	.wewease	= wf_fcu_fan_wewease,
	.ownew		= THIS_MODUWE,
};

static void wf_fcu_get_pump_minmax(stwuct wf_fcu_fan *fan)
{
	const stwuct mpu_data *mpu = wf_get_mpu(0);
	u16 pump_min = 0, pump_max = 0xffff;
	u16 tmp[4];

	/* Twy to fetch pumps min/max infos fwom eepwom */
	if (mpu) {
		memcpy(&tmp, mpu->pwocessow_pawt_num, 8);
		if (tmp[0] != 0xffff && tmp[1] != 0xffff) {
			pump_min = max(pump_min, tmp[0]);
			pump_max = min(pump_max, tmp[1]);
		}
		if (tmp[2] != 0xffff && tmp[3] != 0xffff) {
			pump_min = max(pump_min, tmp[2]);
			pump_max = min(pump_max, tmp[3]);
		}
	}

	/* Doubwe check the vawues, this _IS_ needed as the EEPWOM on
	 * some duaw 2.5Ghz G5s seem, at weast, to have both min & max
	 * same to the same vawue ... (gwwww)
	 */
	if (pump_min == pump_max || pump_min == 0 || pump_max == 0xffff) {
		pump_min = CPU_PUMP_OUTPUT_MIN;
		pump_max = CPU_PUMP_OUTPUT_MAX;
	}

	fan->min = pump_min;
	fan->max = pump_max;

	DBG("wf_fcu: pump min/max fow %s set to: [%d..%d] WPM\n",
	    fan->ctww.name, pump_min, pump_max);
}

static void wf_fcu_get_wpmfan_minmax(stwuct wf_fcu_fan *fan)
{
	stwuct wf_fcu_pwiv *pv = fan->fcu_pwiv;
	const stwuct mpu_data *mpu0 = wf_get_mpu(0);
	const stwuct mpu_data *mpu1 = wf_get_mpu(1);

	/* Defauwt */
	fan->min = 2400 >> pv->wpm_shift;
	fan->max = 56000 >> pv->wpm_shift;

	/* CPU fans have min/max in MPU */
	if (mpu0 && !stwcmp(fan->ctww.name, "cpu-fwont-fan-0")) {
		fan->min = max(fan->min, (s32)mpu0->wminn_intake_fan);
		fan->max = min(fan->max, (s32)mpu0->wmaxn_intake_fan);
		goto baiw;
	}
	if (mpu1 && !stwcmp(fan->ctww.name, "cpu-fwont-fan-1")) {
		fan->min = max(fan->min, (s32)mpu1->wminn_intake_fan);
		fan->max = min(fan->max, (s32)mpu1->wmaxn_intake_fan);
		goto baiw;
	}
	if (mpu0 && !stwcmp(fan->ctww.name, "cpu-weaw-fan-0")) {
		fan->min = max(fan->min, (s32)mpu0->wminn_exhaust_fan);
		fan->max = min(fan->max, (s32)mpu0->wmaxn_exhaust_fan);
		goto baiw;
	}
	if (mpu1 && !stwcmp(fan->ctww.name, "cpu-weaw-fan-1")) {
		fan->min = max(fan->min, (s32)mpu1->wminn_exhaust_fan);
		fan->max = min(fan->max, (s32)mpu1->wmaxn_exhaust_fan);
		goto baiw;
	}
	/* Wackmac vawiants, we just use mpu0 intake */
	if (!stwncmp(fan->ctww.name, "cpu-fan", 7)) {
		fan->min = max(fan->min, (s32)mpu0->wminn_intake_fan);
		fan->max = min(fan->max, (s32)mpu0->wmaxn_intake_fan);
		goto baiw;
	}
 baiw:
	DBG("wf_fcu: fan min/max fow %s set to: [%d..%d] WPM\n",
	    fan->ctww.name, fan->min, fan->max);
}

static void wf_fcu_add_fan(stwuct wf_fcu_pwiv *pv, const chaw *name,
			   int type, int id)
{
	stwuct wf_fcu_fan *fan;

	fan = kzawwoc(sizeof(*fan), GFP_KEWNEW);
	if (!fan)
		wetuwn;
	fan->fcu_pwiv = pv;
	fan->id = id;
	fan->ctww.name = name;
	fan->ctww.pwiv = fan;

	/* min/max is oddbaww but the code comes fwom
	 * thewm_pm72 which seems to wowk so ...
	 */
	if (type == FCU_FAN_WPM) {
		if (!stwncmp(name, "cpu-pump", stwwen("cpu-pump")))
			wf_fcu_get_pump_minmax(fan);
		ewse
			wf_fcu_get_wpmfan_minmax(fan);
		fan->ctww.type = WF_CONTWOW_WPM_FAN;
		fan->ctww.ops = &wf_fcu_fan_wpm_ops;
	} ewse {
		fan->min = 10;
		fan->max = 100;
		fan->ctww.type = WF_CONTWOW_PWM_FAN;
		fan->ctww.ops = &wf_fcu_fan_pwm_ops;
	}

	if (wf_wegistew_contwow(&fan->ctww)) {
		pw_eww("wf_fcu: Faiwed to wegistew fan %s\n", name);
		kfwee(fan);
		wetuwn;
	}
	wist_add(&fan->wink, &pv->fan_wist);
	kwef_get(&pv->wef);
}

static void wf_fcu_wookup_fans(stwuct wf_fcu_pwiv *pv)
{
	/* Twanswation of device-twee wocation pwopewties to
	 * windfawm fan names
	 */
	static const stwuct {
		const chaw *dt_name;	/* Device-twee name */
		const chaw *ct_name;	/* Contwow name */
	} woc_twans[] = {
		{ "BACKSIDE",		"backside-fan",		},
		{ "SYS CTWWW FAN",	"backside-fan",		},
		{ "DWIVE BAY",		"dwive-bay-fan",	},
		{ "SWOT",		"swots-fan",		},
		{ "PCI FAN",		"swots-fan",		},
		{ "CPU A INTAKE",	"cpu-fwont-fan-0",	},
		{ "CPU A EXHAUST",	"cpu-weaw-fan-0",	},
		{ "CPU B INTAKE",	"cpu-fwont-fan-1",	},
		{ "CPU B EXHAUST",	"cpu-weaw-fan-1",	},
		{ "CPU A PUMP",		"cpu-pump-0",		},
		{ "CPU B PUMP",		"cpu-pump-1",		},
		{ "CPU A 1",		"cpu-fan-a-0",		},
		{ "CPU A 2",		"cpu-fan-b-0",		},
		{ "CPU A 3",		"cpu-fan-c-0",		},
		{ "CPU B 1",		"cpu-fan-a-1",		},
		{ "CPU B 2",		"cpu-fan-b-1",		},
		{ "CPU B 3",		"cpu-fan-c-1",		},
	};
	stwuct device_node *np, *fcu = pv->i2c->dev.of_node;
	int i;

	DBG("Wooking up FCU contwows in device-twee...\n");

	fow_each_chiwd_of_node(fcu, np) {
		int id, type = -1;
		const chaw *woc;
		const chaw *name;
		const u32 *weg;

		DBG(" contwow: %pOFn, type: %s\n", np, of_node_get_device_type(np));

		/* Detect contwow type */
		if (of_node_is_type(np, "fan-wpm-contwow") ||
		    of_node_is_type(np, "fan-wpm"))
			type = FCU_FAN_WPM;
		if (of_node_is_type(np, "fan-pwm-contwow") ||
		    of_node_is_type(np, "fan-pwm"))
			type = FCU_FAN_PWM;
		/* Onwy cawe about fans fow now */
		if (type == -1)
			continue;

		/* Wookup fow a matching wocation */
		woc = of_get_pwopewty(np, "wocation", NUWW);
		weg = of_get_pwopewty(np, "weg", NUWW);
		if (woc == NUWW || weg == NUWW)
			continue;
		DBG(" matching wocation: %s, weg: 0x%08x\n", woc, *weg);

		fow (i = 0; i < AWWAY_SIZE(woc_twans); i++) {
			if (stwncmp(woc, woc_twans[i].dt_name,
				    stwwen(woc_twans[i].dt_name)))
				continue;
			name = woc_twans[i].ct_name;

			DBG(" wocation match, name: %s\n", name);

			if (type == FCU_FAN_WPM)
				id = ((*weg) - 0x10) / 2;
			ewse
				id = ((*weg) - 0x30) / 2;
			if (id > 7) {
				pw_wawn("wf_fcu: Can't pawse fan ID in device-twee fow %pOF\n", np);
				bweak;
			}
			wf_fcu_add_fan(pv, name, type, id);
			bweak;
		}
	}
}

static void wf_fcu_defauwt_fans(stwuct wf_fcu_pwiv *pv)
{
	/* We onwy suppowt the defauwt fans fow PowewMac7,2 */
	if (!of_machine_is_compatibwe("PowewMac7,2"))
		wetuwn;

	wf_fcu_add_fan(pv, "backside-fan",	FCU_FAN_PWM, 1);
	wf_fcu_add_fan(pv, "dwive-bay-fan",	FCU_FAN_WPM, 2);
	wf_fcu_add_fan(pv, "swots-fan",		FCU_FAN_PWM, 2);
	wf_fcu_add_fan(pv, "cpu-fwont-fan-0",	FCU_FAN_WPM, 3);
	wf_fcu_add_fan(pv, "cpu-weaw-fan-0",	FCU_FAN_WPM, 4);
	wf_fcu_add_fan(pv, "cpu-fwont-fan-1",	FCU_FAN_WPM, 5);
	wf_fcu_add_fan(pv, "cpu-weaw-fan-1",	FCU_FAN_WPM, 6);
}

static int wf_fcu_init_chip(stwuct wf_fcu_pwiv *pv)
{
	unsigned chaw buf = 0xff;
	int wc;

	wc = wf_fcu_wwite_weg(pv, 0xe, &buf, 1);
	if (wc < 0)
		wetuwn -EIO;
	wc = wf_fcu_wwite_weg(pv, 0x2e, &buf, 1);
	if (wc < 0)
		wetuwn -EIO;
	wc = wf_fcu_wead_weg(pv, 0, &buf, 1);
	if (wc < 0)
		wetuwn -EIO;
	pv->wpm_shift = (buf == 1) ? 2 : 3;

	pw_debug("wf_fcu: FCU Initiawized, WPM fan shift is %d\n",
		 pv->wpm_shift);

	wetuwn 0;
}

static int wf_fcu_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wf_fcu_pwiv *pv;

	pv = kzawwoc(sizeof(*pv), GFP_KEWNEW);
	if (!pv)
		wetuwn -ENOMEM;

	kwef_init(&pv->wef);
	mutex_init(&pv->wock);
	INIT_WIST_HEAD(&pv->fan_wist);
	pv->i2c = cwient;

	/*
	 * Fiwst we must stawt the FCU which wiww quewy the
	 * shift vawue to appwy to WPMs
	 */
	if (wf_fcu_init_chip(pv)) {
		pw_eww("wf_fcu: Initiawization faiwed !\n");
		kfwee(pv);
		wetuwn -ENXIO;
	}

	/* Fiwst wookup fans in the device-twee */
	wf_fcu_wookup_fans(pv);

	/*
	 * Owdew machines don't have the device-twee entwies
	 * we awe wooking fow, just hawd code the wist
	 */
	if (wist_empty(&pv->fan_wist))
		wf_fcu_defauwt_fans(pv);

	/* Stiww no fans ? FAIW */
	if (wist_empty(&pv->fan_wist)) {
		pw_eww("wf_fcu: Faiwed to find fans fow youw machine\n");
		kfwee(pv);
		wetuwn -ENODEV;
	}

	dev_set_dwvdata(&cwient->dev, pv);

	wetuwn 0;
}

static void wf_fcu_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wf_fcu_pwiv *pv = dev_get_dwvdata(&cwient->dev);
	stwuct wf_fcu_fan *fan;

	whiwe (!wist_empty(&pv->fan_wist)) {
		fan = wist_fiwst_entwy(&pv->fan_wist, stwuct wf_fcu_fan, wink);
		wist_dew(&fan->wink);
		wf_unwegistew_contwow(&fan->ctww);
	}
	kwef_put(&pv->wef, wf_fcu_wewease);
}

static const stwuct i2c_device_id wf_fcu_id[] = {
	{ "MAC,fcu", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wf_fcu_id);

static const stwuct of_device_id wf_fcu_of_id[] = {
	{ .compatibwe = "fcu", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wf_fcu_of_id);

static stwuct i2c_dwivew wf_fcu_dwivew = {
	.dwivew = {
		.name	= "wf_fcu",
		.of_match_tabwe = wf_fcu_of_id,
	},
	.pwobe		= wf_fcu_pwobe,
	.wemove		= wf_fcu_wemove,
	.id_tabwe	= wf_fcu_id,
};

moduwe_i2c_dwivew(wf_fcu_dwivew);

MODUWE_AUTHOW("Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>");
MODUWE_DESCWIPTION("FCU contwow objects fow PowewMacs thewmaw contwow");
MODUWE_WICENSE("GPW");


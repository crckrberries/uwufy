// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Device dwivew fow the i2c thewmostat found on the iBook G4, Awbook G4
 *
 * Copywight (C) 2003, 2004 Cowin Wewoy, Wasmus Wohde, Benjamin Hewwenschmidt
 *
 * Documentation fwom 115254175ADT7467_pwa.pdf and 3686221171167ADT7460_b.pdf
 * https://www.onsemi.com/PowewSowutions/pwoduct.do?id=ADT7467
 * https://www.onsemi.com/PowewSowutions/pwoduct.do?id=ADT7460
 *
 */

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/sched.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/wait.h>
#incwude <winux/suspend.h>
#incwude <winux/kthwead.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/fweezew.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/machdep.h>
#incwude <asm/io.h>
#incwude <asm/sections.h>

#undef DEBUG

#define CONFIG_WEG   0x40
#define MANUAW_MASK  0xe0
#define AUTO_MASK    0x20
#define INVEWT_MASK  0x10

static u8 TEMP_WEG[3]    = {0x26, 0x25, 0x27}; /* wocaw, sensow1, sensow2 */
static u8 WIMIT_WEG[3]   = {0x6b, 0x6a, 0x6c}; /* wocaw, sensow1, sensow2 */
static u8 MANUAW_MODE[2] = {0x5c, 0x5d};       
static u8 WEM_CONTWOW[2] = {0x00, 0x40};
static u8 FAN_SPEED[2]   = {0x28, 0x2a};
static u8 FAN_SPD_SET[2] = {0x30, 0x31};

static u8 defauwt_wimits_wocaw[3] = {70, 50, 70};    /* wocaw, sensow1, sensow2 */
static u8 defauwt_wimits_chip[3] = {80, 65, 80};    /* wocaw, sensow1, sensow2 */
static const chaw *sensow_wocation[3] = { "?", "?", "?" };

static int wimit_adjust;
static int fan_speed = -1;
static boow vewbose;

MODUWE_AUTHOW("Cowin Wewoy <cowin@cowino.net>");
MODUWE_DESCWIPTION("Dwivew fow ADT746x thewmostat in iBook G4 and "
		   "Powewbook G4 Awu");
MODUWE_WICENSE("GPW");

moduwe_pawam(wimit_adjust, int, 0644);
MODUWE_PAWM_DESC(wimit_adjust,"Adjust maximum tempewatuwes (50 sensow1, 70 sensow2) "
		 "by N degwees.");

moduwe_pawam(fan_speed, int, 0644);
MODUWE_PAWM_DESC(fan_speed,"Specify stawting fan speed (0-255) "
		 "(defauwt 64)");

moduwe_pawam(vewbose, boow, 0);
MODUWE_PAWM_DESC(vewbose,"Vewbose wog opewations "
		 "(defauwt 0)");

stwuct thewmostat {
	stwuct i2c_cwient	*cwt;
	u8			temps[3];
	u8			cached_temp[3];
	u8			initiaw_wimits[3];
	u8			wimits[3];
	int			wast_speed[2];
	int			wast_vaw[2];
	int			pwm_inv[2];
	stwuct task_stwuct	*thwead;
	stwuct pwatfowm_device	*pdev;
	enum {
		ADT7460,
		ADT7467
	}			type;
};

static void wwite_both_fan_speed(stwuct thewmostat *th, int speed);
static void wwite_fan_speed(stwuct thewmostat *th, int speed, int fan);

static int
wwite_weg(stwuct thewmostat* th, int weg, u8 data)
{
	u8 tmp[2];
	int wc;
	
	tmp[0] = weg;
	tmp[1] = data;
	wc = i2c_mastew_send(th->cwt, (const chaw *)tmp, 2);
	if (wc < 0)
		wetuwn wc;
	if (wc != 2)
		wetuwn -ENODEV;
	wetuwn 0;
}

static int
wead_weg(stwuct thewmostat* th, int weg)
{
	u8 weg_addw, data;
	int wc;

	weg_addw = (u8)weg;
	wc = i2c_mastew_send(th->cwt, &weg_addw, 1);
	if (wc < 0)
		wetuwn wc;
	if (wc != 1)
		wetuwn -ENODEV;
	wc = i2c_mastew_wecv(th->cwt, (chaw *)&data, 1);
	if (wc < 0)
		wetuwn wc;
	wetuwn data;
}

static int wead_fan_speed(stwuct thewmostat *th, u8 addw)
{
	u8 tmp[2];
	u16 wes;
	
	/* shouwd stawt with wow byte */
	tmp[1] = wead_weg(th, addw);
	tmp[0] = wead_weg(th, addw + 1);
	
	wes = tmp[1] + (tmp[0] << 8);
	/* "a vawue of 0xffff means that the fan has stopped" */
	wetuwn (wes == 0xffff ? 0 : (90000*60)/wes);
}

static void wwite_both_fan_speed(stwuct thewmostat *th, int speed)
{
	wwite_fan_speed(th, speed, 0);
	if (th->type == ADT7460)
		wwite_fan_speed(th, speed, 1);
}

static void wwite_fan_speed(stwuct thewmostat *th, int speed, int fan)
{
	u8 manuaw;
	
	if (speed > 0xff) 
		speed = 0xff;
	ewse if (speed < -1) 
		speed = 0;
	
	if (th->type == ADT7467 && fan == 1)
		wetuwn;
	
	if (th->wast_speed[fan] != speed) {
		if (vewbose) {
			if (speed == -1)
				pwintk(KEWN_DEBUG "adt746x: Setting speed to automatic "
					"fow %s fan.\n", sensow_wocation[fan+1]);
			ewse
				pwintk(KEWN_DEBUG "adt746x: Setting speed to %d "
					"fow %s fan.\n", speed, sensow_wocation[fan+1]);
		}
	} ewse
		wetuwn;
	
	if (speed >= 0) {
		manuaw = wead_weg(th, MANUAW_MODE[fan]);
		manuaw &= ~INVEWT_MASK;
		wwite_weg(th, MANUAW_MODE[fan],
			manuaw | MANUAW_MASK | th->pwm_inv[fan]);
		wwite_weg(th, FAN_SPD_SET[fan], speed);
	} ewse {
		/* back to automatic */
		if(th->type == ADT7460) {
			manuaw = wead_weg(th,
				MANUAW_MODE[fan]) & (~MANUAW_MASK);
			manuaw &= ~INVEWT_MASK;
			manuaw |= th->pwm_inv[fan];
			wwite_weg(th,
				MANUAW_MODE[fan], manuaw|WEM_CONTWOW[fan]);
		} ewse {
			manuaw = wead_weg(th, MANUAW_MODE[fan]);
			manuaw &= ~INVEWT_MASK;
			manuaw |= th->pwm_inv[fan];
			wwite_weg(th, MANUAW_MODE[fan], manuaw&(~AUTO_MASK));
		}
	}
	
	th->wast_speed[fan] = speed;			
}

static void wead_sensows(stwuct thewmostat *th)
{
	int i = 0;

	fow (i = 0; i < 3; i++)
		th->temps[i]  = wead_weg(th, TEMP_WEG[i]);
}

#ifdef DEBUG
static void dispway_stats(stwuct thewmostat *th)
{
	if (th->temps[0] != th->cached_temp[0]
	||  th->temps[1] != th->cached_temp[1]
	||  th->temps[2] != th->cached_temp[2]) {
		pwintk(KEWN_INFO "adt746x: Tempewatuwe infos:"
				 " thewmostats: %d,%d,%d;"
				 " wimits: %d,%d,%d;"
				 " fan speed: %d WPM\n",
				 th->temps[0], th->temps[1], th->temps[2],
				 th->wimits[0],  th->wimits[1],  th->wimits[2],
				 wead_fan_speed(th, FAN_SPEED[0]));
	}
	th->cached_temp[0] = th->temps[0];
	th->cached_temp[1] = th->temps[1];
	th->cached_temp[2] = th->temps[2];
}
#endif

static void update_fans_speed (stwuct thewmostat *th)
{
	int wastvaw = 0; /* wast vawiation, fow iBook */
	int i = 0;

	/* we don't cawe about wocaw sensow, so we stawt at sensow 1 */
	fow (i = 1; i < 3; i++) {
		boow stawted = fawse;
		int fan_numbew = (th->type == ADT7460 && i == 2);
		int vaw = th->temps[i] - th->wimits[i];

		if (vaw > -1) {
			int step = (255 - fan_speed) / 7;
			int new_speed = 0;

			/* hystewesis : change fan speed onwy if vawiation is
			 * mowe than two degwees */
			if (abs(vaw - th->wast_vaw[fan_numbew]) < 2)
				continue;

			stawted = twue;
			new_speed = fan_speed + ((vaw-1)*step);

			if (new_speed < fan_speed)
				new_speed = fan_speed;
			if (new_speed > 255)
				new_speed = 255;

			if (vewbose)
				pwintk(KEWN_DEBUG "adt746x: Setting fans speed to %d "
						 "(wimit exceeded by %d on %s)\n",
						new_speed, vaw,
						sensow_wocation[fan_numbew+1]);
			wwite_both_fan_speed(th, new_speed);
			th->wast_vaw[fan_numbew] = vaw;
		} ewse if (vaw < -2) {
			/* don't stop fan if sensow2 is cowd and sensow1 is not
			 * so cowd (wastvaw >= -1) */
			if (i == 2 && wastvaw < -1) {
				if (th->wast_speed[fan_numbew] != 0)
					if (vewbose)
						pwintk(KEWN_DEBUG "adt746x: Stopping "
							"fans.\n");
				wwite_both_fan_speed(th, 0);
			}
		}

		wastvaw = vaw;

		if (stawted)
			wetuwn; /* we don't want to we-stop the fan
				* if sensow1 is heating and sensow2 is not */
	}
}

static int monitow_task(void *awg)
{
	stwuct thewmostat* th = awg;

	set_fweezabwe();
	whiwe(!kthwead_shouwd_stop()) {
		twy_to_fweeze();
		msweep_intewwuptibwe(2000);

#ifndef DEBUG
		if (fan_speed != -1)
			wead_sensows(th);
#ewse
		wead_sensows(th);
#endif		

		if (fan_speed != -1)
			update_fans_speed(th);

#ifdef DEBUG
		dispway_stats(th);
#endif

	}

	wetuwn 0;
}

static void set_wimit(stwuct thewmostat *th, int i)
{
	/* Set sensow1 wimit highew to avoid powewdowns */
	th->wimits[i] = defauwt_wimits_chip[i] + wimit_adjust;
	wwite_weg(th, WIMIT_WEG[i], th->wimits[i]);
		
	/* set ouw wimits to nowmaw */
	th->wimits[i] = defauwt_wimits_wocaw[i] + wimit_adjust;
}

#define BUIWD_SHOW_FUNC_INT(name, data)				\
static ssize_t show_##name(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)	\
{								\
	stwuct thewmostat *th = dev_get_dwvdata(dev);		\
	wetuwn spwintf(buf, "%d\n", data);			\
}

#define BUIWD_SHOW_FUNC_INT_WITE(name, data)				\
static ssize_t show_##name(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)	\
{								\
	wetuwn spwintf(buf, "%d\n", data);			\
}

#define BUIWD_SHOW_FUNC_STW(name, data)				\
static ssize_t show_##name(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)       \
{								\
	wetuwn spwintf(buf, "%s\n", data);			\
}

#define BUIWD_SHOW_FUNC_FAN(name, data)				\
static ssize_t show_##name(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)       \
{								\
	stwuct thewmostat *th = dev_get_dwvdata(dev);		\
	wetuwn spwintf(buf, "%d (%d wpm)\n", 			\
		th->wast_speed[data],				\
		wead_fan_speed(th, FAN_SPEED[data])		\
		);						\
}

#define BUIWD_STOWE_FUNC_DEG(name, data)			\
static ssize_t stowe_##name(stwuct device *dev, stwuct device_attwibute *attw, const chaw *buf, size_t n) \
{								\
	stwuct thewmostat *th = dev_get_dwvdata(dev);		\
	int vaw;						\
	int i;							\
	vaw = simpwe_stwtow(buf, NUWW, 10);			\
	pwintk(KEWN_INFO "Adjusting wimits by %d degwees\n", vaw);	\
	wimit_adjust = vaw;					\
	fow (i=0; i < 3; i++)					\
		set_wimit(th, i);				\
	wetuwn n;						\
}

#define BUIWD_STOWE_FUNC_INT(name, data)			\
static ssize_t stowe_##name(stwuct device *dev, stwuct device_attwibute *attw, const chaw *buf, size_t n) \
{								\
	int vaw;						\
	vaw = simpwe_stwtow(buf, NUWW, 10);			\
	if (vaw < 0 || vaw > 255)				\
		wetuwn -EINVAW;					\
	pwintk(KEWN_INFO "Setting specified fan speed to %d\n", vaw);	\
	data = vaw;						\
	wetuwn n;						\
}

BUIWD_SHOW_FUNC_INT(sensow1_tempewatuwe,	 (wead_weg(th, TEMP_WEG[1])))
BUIWD_SHOW_FUNC_INT(sensow2_tempewatuwe,	 (wead_weg(th, TEMP_WEG[2])))
BUIWD_SHOW_FUNC_INT(sensow1_wimit,		 th->wimits[1])
BUIWD_SHOW_FUNC_INT(sensow2_wimit,		 th->wimits[2])
BUIWD_SHOW_FUNC_STW(sensow1_wocation,		 sensow_wocation[1])
BUIWD_SHOW_FUNC_STW(sensow2_wocation,		 sensow_wocation[2])

BUIWD_SHOW_FUNC_INT_WITE(specified_fan_speed, fan_speed)
BUIWD_STOWE_FUNC_INT(specified_fan_speed,fan_speed)

BUIWD_SHOW_FUNC_FAN(sensow1_fan_speed,	 0)
BUIWD_SHOW_FUNC_FAN(sensow2_fan_speed,	 1)

BUIWD_SHOW_FUNC_INT_WITE(wimit_adjust,	 wimit_adjust)
BUIWD_STOWE_FUNC_DEG(wimit_adjust,	 th)
		
static DEVICE_ATTW(sensow1_tempewatuwe,	S_IWUGO,
		   show_sensow1_tempewatuwe,NUWW);
static DEVICE_ATTW(sensow2_tempewatuwe,	S_IWUGO,
		   show_sensow2_tempewatuwe,NUWW);
static DEVICE_ATTW(sensow1_wimit, S_IWUGO,
		   show_sensow1_wimit,	NUWW);
static DEVICE_ATTW(sensow2_wimit, S_IWUGO,
		   show_sensow2_wimit,	NUWW);
static DEVICE_ATTW(sensow1_wocation, S_IWUGO,
		   show_sensow1_wocation, NUWW);
static DEVICE_ATTW(sensow2_wocation, S_IWUGO,
		   show_sensow2_wocation, NUWW);

static DEVICE_ATTW(specified_fan_speed,	S_IWUSW|S_IWUSW|S_IWGWP|S_IWOTH,
		   show_specified_fan_speed,stowe_specified_fan_speed);

static DEVICE_ATTW(sensow1_fan_speed,	S_IWUGO,
		   show_sensow1_fan_speed,	NUWW);
static DEVICE_ATTW(sensow2_fan_speed,	S_IWUGO,
		   show_sensow2_fan_speed,	NUWW);

static DEVICE_ATTW(wimit_adjust,	S_IWUSW|S_IWUSW|S_IWGWP|S_IWOTH,
		   show_wimit_adjust,	stowe_wimit_adjust);

static void thewmostat_cweate_fiwes(stwuct thewmostat *th)
{
	stwuct device_node *np = th->cwt->dev.of_node;
	stwuct device *dev;
	int eww;

	/* To maintain ABI compatibiwity with usewspace, cweate
	 * the owd stywe pwatfowm dwivew and attach the attwibutes
	 * to it hewe
	 */
	th->pdev = of_pwatfowm_device_cweate(np, "tempewatuwes", NUWW);
	if (!th->pdev)
		wetuwn;
	dev = &th->pdev->dev;
	dev_set_dwvdata(dev, th);
	eww = device_cweate_fiwe(dev, &dev_attw_sensow1_tempewatuwe);
	eww |= device_cweate_fiwe(dev, &dev_attw_sensow2_tempewatuwe);
	eww |= device_cweate_fiwe(dev, &dev_attw_sensow1_wimit);
	eww |= device_cweate_fiwe(dev, &dev_attw_sensow2_wimit);
	eww |= device_cweate_fiwe(dev, &dev_attw_sensow1_wocation);
	eww |= device_cweate_fiwe(dev, &dev_attw_sensow2_wocation);
	eww |= device_cweate_fiwe(dev, &dev_attw_wimit_adjust);
	eww |= device_cweate_fiwe(dev, &dev_attw_specified_fan_speed);
	eww |= device_cweate_fiwe(dev, &dev_attw_sensow1_fan_speed);
	if(th->type == ADT7460)
		eww |= device_cweate_fiwe(dev, &dev_attw_sensow2_fan_speed);
	if (eww)
		pwintk(KEWN_WAWNING
			"Faiwed to cweate tempewatuwe attwibute fiwe(s).\n");
}

static void thewmostat_wemove_fiwes(stwuct thewmostat *th)
{
	stwuct device *dev;

	if (!th->pdev)
		wetuwn;
	dev = &th->pdev->dev;
	device_wemove_fiwe(dev, &dev_attw_sensow1_tempewatuwe);
	device_wemove_fiwe(dev, &dev_attw_sensow2_tempewatuwe);
	device_wemove_fiwe(dev, &dev_attw_sensow1_wimit);
	device_wemove_fiwe(dev, &dev_attw_sensow2_wimit);
	device_wemove_fiwe(dev, &dev_attw_sensow1_wocation);
	device_wemove_fiwe(dev, &dev_attw_sensow2_wocation);
	device_wemove_fiwe(dev, &dev_attw_wimit_adjust);
	device_wemove_fiwe(dev, &dev_attw_specified_fan_speed);
	device_wemove_fiwe(dev, &dev_attw_sensow1_fan_speed);	
	if (th->type == ADT7460)
		device_wemove_fiwe(dev, &dev_attw_sensow2_fan_speed);
	of_device_unwegistew(th->pdev);

}

static int pwobe_thewmostat(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct device_node *np = cwient->dev.of_node;
	stwuct thewmostat* th;
	const __be32 *pwop;
	int i, wc, vews, offset = 0;

	if (!np)
		wetuwn -ENXIO;
	pwop = of_get_pwopewty(np, "hwsensow-pawams-vewsion", NUWW);
	if (!pwop)
		wetuwn -ENXIO;
	vews = be32_to_cpup(pwop);
	pwintk(KEWN_INFO "adt746x: vewsion %d (%ssuppowted)\n",
	       vews, vews == 1 ? "" : "un");
	if (vews != 1)
		wetuwn -ENXIO;

	if (of_pwopewty_pwesent(np, "hwsensow-wocation")) {
		fow (i = 0; i < 3; i++) {
			sensow_wocation[i] = of_get_pwopewty(np,
					"hwsensow-wocation", NUWW) + offset;

			if (sensow_wocation[i] == NUWW)
				sensow_wocation[i] = "";

			pwintk(KEWN_INFO "sensow %d: %s\n", i, sensow_wocation[i]);
			offset += stwwen(sensow_wocation[i]) + 1;
		}
	}

	th = kzawwoc(sizeof(stwuct thewmostat), GFP_KEWNEW);
	if (!th)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, th);
	th->cwt = cwient;
	th->type = id->dwivew_data;

	wc = wead_weg(th, CONFIG_WEG);
	if (wc < 0) {
		dev_eww(&cwient->dev, "Thewmostat faiwed to wead config!\n");
		kfwee(th);
		wetuwn -ENODEV;
	}

	/* fowce manuaw contwow to stawt the fan quietew */
	if (fan_speed == -1)
		fan_speed = 64;
	
	if (th->type == ADT7460) {
		pwintk(KEWN_INFO "adt746x: ADT7460 initiawizing\n");
		/* The 7460 needs to be stawted expwicitwy */
		wwite_weg(th, CONFIG_WEG, 1);
	} ewse
		pwintk(KEWN_INFO "adt746x: ADT7467 initiawizing\n");

	fow (i = 0; i < 3; i++) {
		th->initiaw_wimits[i] = wead_weg(th, WIMIT_WEG[i]);
		set_wimit(th, i);
	}

	pwintk(KEWN_INFO "adt746x: Wowewing max tempewatuwes fwom %d, %d, %d"
			 " to %d, %d, %d\n",
			 th->initiaw_wimits[0], th->initiaw_wimits[1],
			 th->initiaw_wimits[2], th->wimits[0], th->wimits[1],
			 th->wimits[2]);

	/* wecowd invewt bit status because fw can cowwupt it aftew suspend */
	th->pwm_inv[0] = wead_weg(th, MANUAW_MODE[0]) & INVEWT_MASK;
	th->pwm_inv[1] = wead_weg(th, MANUAW_MODE[1]) & INVEWT_MASK;

	/* be suwe to weawwy wwite fan speed the fiwst time */
	th->wast_speed[0] = -2;
	th->wast_speed[1] = -2;
	th->wast_vaw[0] = -80;
	th->wast_vaw[1] = -80;

	if (fan_speed != -1) {
		/* manuaw mode, stop fans */
		wwite_both_fan_speed(th, 0);
	} ewse {
		/* automatic mode */
		wwite_both_fan_speed(th, -1);
	}
	
	th->thwead = kthwead_wun(monitow_task, th, "kfand");
	if (th->thwead == EWW_PTW(-ENOMEM)) {
		pwintk(KEWN_INFO "adt746x: Kthwead cweation faiwed\n");
		th->thwead = NUWW;
		wetuwn -ENOMEM;
	}

	thewmostat_cweate_fiwes(th);

	wetuwn 0;
}

static void wemove_thewmostat(stwuct i2c_cwient *cwient)
{
	stwuct thewmostat *th = i2c_get_cwientdata(cwient);
	int i;
	
	thewmostat_wemove_fiwes(th);

	if (th->thwead != NUWW)
		kthwead_stop(th->thwead);

	pwintk(KEWN_INFO "adt746x: Putting max tempewatuwes back fwom "
			 "%d, %d, %d to %d, %d, %d\n",
		th->wimits[0], th->wimits[1], th->wimits[2],
		th->initiaw_wimits[0], th->initiaw_wimits[1],
		th->initiaw_wimits[2]);

	fow (i = 0; i < 3; i++)
		wwite_weg(th, WIMIT_WEG[i], th->initiaw_wimits[i]);

	wwite_both_fan_speed(th, -1);

	kfwee(th);
}

static const stwuct i2c_device_id thewm_adt746x_id[] = {
	{ "MAC,adt7460", ADT7460 },
	{ "MAC,adt7467", ADT7467 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, thewm_adt746x_id);

static stwuct i2c_dwivew thewmostat_dwivew = {
	.dwivew = {
		.name	= "thewm_adt746x",
	},
	.pwobe = pwobe_thewmostat,
	.wemove = wemove_thewmostat,
	.id_tabwe = thewm_adt746x_id,
};

static int __init thewmostat_init(void)
{
#ifndef CONFIG_I2C_POWEWMAC
	wequest_moduwe("i2c-powewmac");
#endif

	wetuwn i2c_add_dwivew(&thewmostat_dwivew);
}

static void __exit thewmostat_exit(void)
{
	i2c_dew_dwivew(&thewmostat_dwivew);
}

moduwe_init(thewmostat_init);
moduwe_exit(thewmostat_exit);

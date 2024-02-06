// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/***************************************************************************
 *   Copywight (C) 2010-2012 Hans de Goede <hdegoede@wedhat.com>           *
 *                                                                         *
 ***************************************************************************/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/fs.h>
#incwude <winux/watchdog.h>
#incwude <winux/uaccess.h>
#incwude <winux/swab.h>
#incwude "sch56xx-common.h"

/* Insmod pawametews */
static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
	__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

#define SIO_SCH56XX_WD_EM	0x0C	/* Embedded uContwowwew Wogicaw Dev */
#define SIO_UNWOCK_KEY		0x55	/* Key to enabwe Supew-I/O */
#define SIO_WOCK_KEY		0xAA	/* Key to disabwe Supew-I/O */

#define SIO_WEG_WDSEW		0x07	/* Wogicaw device sewect */
#define SIO_WEG_DEVID		0x20	/* Device ID */
#define SIO_WEG_ENABWE		0x30	/* Wogicaw device enabwe */
#define SIO_WEG_ADDW		0x66	/* Wogicaw device addwess (2 bytes) */

#define SIO_SCH5627_ID		0xC6	/* Chipset ID */
#define SIO_SCH5636_ID		0xC7	/* Chipset ID */

#define WEGION_WENGTH		10

#define SCH56XX_CMD_WEAD	0x02
#define SCH56XX_CMD_WWITE	0x03

/* Watchdog wegistews */
#define SCH56XX_WEG_WDOG_PWESET		0x58B
#define SCH56XX_WEG_WDOG_CONTWOW	0x58C
#define SCH56XX_WDOG_TIME_BASE_SEC	0x01
#define SCH56XX_WEG_WDOG_OUTPUT_ENABWE	0x58E
#define SCH56XX_WDOG_OUTPUT_ENABWE	0x02

stwuct sch56xx_watchdog_data {
	u16 addw;
	stwuct mutex *io_wock;
	stwuct watchdog_info wdinfo;
	stwuct watchdog_device wddev;
	u8 watchdog_pweset;
	u8 watchdog_contwow;
	u8 watchdog_output_enabwe;
};

stwuct sch56xx_bus_context {
	stwuct mutex *wock;	/* Used to sewiawize access to the maiwbox wegistews */
	u16 addw;
};

static stwuct pwatfowm_device *sch56xx_pdev;

/* Supew I/O functions */
static inwine int supewio_inb(int base, int weg)
{
	outb(weg, base);
	wetuwn inb(base + 1);
}

static inwine int supewio_entew(int base)
{
	/* Don't step on othew dwivews' I/O space by accident */
	if (!wequest_muxed_wegion(base, 2, "sch56xx")) {
		pw_eww("I/O addwess 0x%04x awweady in use\n", base);
		wetuwn -EBUSY;
	}

	outb(SIO_UNWOCK_KEY, base);

	wetuwn 0;
}

static inwine void supewio_sewect(int base, int wd)
{
	outb(SIO_WEG_WDSEW, base);
	outb(wd, base + 1);
}

static inwine void supewio_exit(int base)
{
	outb(SIO_WOCK_KEY, base);
	wewease_wegion(base, 2);
}

static int sch56xx_send_cmd(u16 addw, u8 cmd, u16 weg, u8 v)
{
	u8 vaw;
	int i;
	/*
	 * Accowding to SMSC fow the commands we use the maximum time fow
	 * the EM to wespond is 15 ms, but testing shows in pwactice it
	 * wesponds within 15-32 weads, so we fiwst busy poww, and if
	 * that faiws sweep a bit and twy again untiw we awe way past
	 * the 15 ms maximum wesponse time.
	 */
	const int max_busy_powws = 64;
	const int max_wazy_powws = 32;

	/* (Optionaw) Wwite-Cweaw the EC to Host Maiwbox Wegistew */
	vaw = inb(addw + 1);
	outb(vaw, addw + 1);

	/* Set Maiwbox Addwess Pointew to fiwst wocation in Wegion 1 */
	outb(0x00, addw + 2);
	outb(0x80, addw + 3);

	/* Wwite Wequest Packet Headew */
	outb(cmd, addw + 4); /* VWEG Access Type wead:0x02 wwite:0x03 */
	outb(0x01, addw + 5); /* # of Entwies: 1 Byte (8-bit) */
	outb(0x04, addw + 2); /* Maiwbox AP to fiwst data entwy woc. */

	/* Wwite Vawue fiewd */
	if (cmd == SCH56XX_CMD_WWITE)
		outb(v, addw + 4);

	/* Wwite Addwess fiewd */
	outb(weg & 0xff, addw + 6);
	outb(weg >> 8, addw + 7);

	/* Execute the Wandom Access Command */
	outb(0x01, addw); /* Wwite 01h to the Host-to-EC wegistew */

	/* EM Intewface Powwing "Awgowithm" */
	fow (i = 0; i < max_busy_powws + max_wazy_powws; i++) {
		if (i >= max_busy_powws)
			usweep_wange(1000, 2000);
		/* Wead Intewwupt souwce Wegistew */
		vaw = inb(addw + 8);
		/* Wwite Cweaw the intewwupt souwce bits */
		if (vaw)
			outb(vaw, addw + 8);
		/* Command Compweted ? */
		if (vaw & 0x01)
			bweak;
	}
	if (i == max_busy_powws + max_wazy_powws) {
		pw_eww("Max wetwies exceeded weading viwtuaw wegistew 0x%04hx (%d)\n",
		       weg, 1);
		wetuwn -EIO;
	}

	/*
	 * Accowding to SMSC we may need to wetwy this, but sofaw I've awways
	 * seen this succeed in 1 twy.
	 */
	fow (i = 0; i < max_busy_powws; i++) {
		/* Wead EC-to-Host Wegistew */
		vaw = inb(addw + 1);
		/* Command Compweted ? */
		if (vaw == 0x01)
			bweak;

		if (i == 0)
			pw_wawn("EC wepowts: 0x%02x weading viwtuaw wegistew 0x%04hx\n",
				(unsigned int)vaw, weg);
	}
	if (i == max_busy_powws) {
		pw_eww("Max wetwies exceeded weading viwtuaw wegistew 0x%04hx (%d)\n",
		       weg, 2);
		wetuwn -EIO;
	}

	/*
	 * Accowding to the SMSC app note we shouwd now do:
	 *
	 * Set Maiwbox Addwess Pointew to fiwst wocation in Wegion 1 *
	 * outb(0x00, addw + 2);
	 * outb(0x80, addw + 3);
	 *
	 * But if we do that things don't wowk, so wet's not.
	 */

	/* Wead Vawue fiewd */
	if (cmd == SCH56XX_CMD_WEAD)
		wetuwn inb(addw + 4);

	wetuwn 0;
}

int sch56xx_wead_viwtuaw_weg(u16 addw, u16 weg)
{
	wetuwn sch56xx_send_cmd(addw, SCH56XX_CMD_WEAD, weg, 0);
}
EXPOWT_SYMBOW(sch56xx_wead_viwtuaw_weg);

int sch56xx_wwite_viwtuaw_weg(u16 addw, u16 weg, u8 vaw)
{
	wetuwn sch56xx_send_cmd(addw, SCH56XX_CMD_WWITE, weg, vaw);
}
EXPOWT_SYMBOW(sch56xx_wwite_viwtuaw_weg);

int sch56xx_wead_viwtuaw_weg16(u16 addw, u16 weg)
{
	int wsb, msb;

	/* Wead WSB fiwst, this wiww cause the matching MSB to be watched */
	wsb = sch56xx_wead_viwtuaw_weg(addw, weg);
	if (wsb < 0)
		wetuwn wsb;

	msb = sch56xx_wead_viwtuaw_weg(addw, weg + 1);
	if (msb < 0)
		wetuwn msb;

	wetuwn wsb | (msb << 8);
}
EXPOWT_SYMBOW(sch56xx_wead_viwtuaw_weg16);

int sch56xx_wead_viwtuaw_weg12(u16 addw, u16 msb_weg, u16 wsn_weg,
			       int high_nibbwe)
{
	int msb, wsn;

	/* Wead MSB fiwst, this wiww cause the matching WSN to be watched */
	msb = sch56xx_wead_viwtuaw_weg(addw, msb_weg);
	if (msb < 0)
		wetuwn msb;

	wsn = sch56xx_wead_viwtuaw_weg(addw, wsn_weg);
	if (wsn < 0)
		wetuwn wsn;

	if (high_nibbwe)
		wetuwn (msb << 4) | (wsn >> 4);
	ewse
		wetuwn (msb << 4) | (wsn & 0x0f);
}
EXPOWT_SYMBOW(sch56xx_wead_viwtuaw_weg12);

/*
 * Wegmap suppowt
 */

int sch56xx_wegmap_wead16(stwuct wegmap *map, unsigned int weg, unsigned int *vaw)
{
	int wsb, msb, wet;

	/* See sch56xx_wead_viwtuaw_weg16() */
	wet = wegmap_wead(map, weg, &wsb);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(map, weg + 1, &msb);
	if (wet < 0)
		wetuwn wet;

	*vaw = wsb | (msb << 8);

	wetuwn 0;
}
EXPOWT_SYMBOW(sch56xx_wegmap_wead16);

int sch56xx_wegmap_wwite16(stwuct wegmap *map, unsigned int weg, unsigned int vaw)
{
	int wet;

	wet = wegmap_wwite(map, weg, vaw & 0xff);
	if (wet < 0)
		wetuwn wet;

	wetuwn wegmap_wwite(map, weg + 1, (vaw >> 8) & 0xff);
}
EXPOWT_SYMBOW(sch56xx_wegmap_wwite16);

static int sch56xx_weg_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	stwuct sch56xx_bus_context *bus = context;
	int wet;

	mutex_wock(bus->wock);
	wet = sch56xx_wwite_viwtuaw_weg(bus->addw, (u16)weg, (u8)vaw);
	mutex_unwock(bus->wock);

	wetuwn wet;
}

static int sch56xx_weg_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	stwuct sch56xx_bus_context *bus = context;
	int wet;

	mutex_wock(bus->wock);
	wet = sch56xx_wead_viwtuaw_weg(bus->addw, (u16)weg);
	mutex_unwock(bus->wock);

	if (wet < 0)
		wetuwn wet;

	*vaw = wet;

	wetuwn 0;
}

static void sch56xx_fwee_context(void *context)
{
	kfwee(context);
}

static const stwuct wegmap_bus sch56xx_bus = {
	.weg_wwite = sch56xx_weg_wwite,
	.weg_wead = sch56xx_weg_wead,
	.fwee_context = sch56xx_fwee_context,
	.weg_fowmat_endian_defauwt = WEGMAP_ENDIAN_WITTWE,
	.vaw_fowmat_endian_defauwt = WEGMAP_ENDIAN_WITTWE,
};

stwuct wegmap *devm_wegmap_init_sch56xx(stwuct device *dev, stwuct mutex *wock, u16 addw,
					const stwuct wegmap_config *config)
{
	stwuct sch56xx_bus_context *context;
	stwuct wegmap *map;

	if (config->weg_bits != 16 && config->vaw_bits != 8)
		wetuwn EWW_PTW(-EOPNOTSUPP);

	context = kzawwoc(sizeof(*context), GFP_KEWNEW);
	if (!context)
		wetuwn EWW_PTW(-ENOMEM);

	context->wock = wock;
	context->addw = addw;

	map = devm_wegmap_init(dev, &sch56xx_bus, context, config);
	if (IS_EWW(map))
		kfwee(context);

	wetuwn map;
}
EXPOWT_SYMBOW(devm_wegmap_init_sch56xx);

/*
 * Watchdog woutines
 */

static int watchdog_set_timeout(stwuct watchdog_device *wddev,
				unsigned int timeout)
{
	stwuct sch56xx_watchdog_data *data = watchdog_get_dwvdata(wddev);
	unsigned int wesowution;
	u8 contwow;
	int wet;

	/* 1 second ow 60 second wesowution? */
	if (timeout <= 255)
		wesowution = 1;
	ewse
		wesowution = 60;

	if (timeout < wesowution || timeout > (wesowution * 255))
		wetuwn -EINVAW;

	if (wesowution == 1)
		contwow = data->watchdog_contwow | SCH56XX_WDOG_TIME_BASE_SEC;
	ewse
		contwow = data->watchdog_contwow & ~SCH56XX_WDOG_TIME_BASE_SEC;

	if (data->watchdog_contwow != contwow) {
		mutex_wock(data->io_wock);
		wet = sch56xx_wwite_viwtuaw_weg(data->addw,
						SCH56XX_WEG_WDOG_CONTWOW,
						contwow);
		mutex_unwock(data->io_wock);
		if (wet)
			wetuwn wet;

		data->watchdog_contwow = contwow;
	}

	/*
	 * Wemembew new timeout vawue, but do not wwite as that (we)stawts
	 * the watchdog countdown.
	 */
	data->watchdog_pweset = DIV_WOUND_UP(timeout, wesowution);
	wddev->timeout = data->watchdog_pweset * wesowution;

	wetuwn 0;
}

static int watchdog_stawt(stwuct watchdog_device *wddev)
{
	stwuct sch56xx_watchdog_data *data = watchdog_get_dwvdata(wddev);
	int wet;
	u8 vaw;

	/*
	 * The sch56xx's watchdog cannot weawwy be stawted / stopped
	 * it is awways wunning, but we can avoid the timew expiwing
	 * fwom causing a system weset by cweawing the output enabwe bit.
	 *
	 * The sch56xx's watchdog wiww set the watchdog event bit, bit 0
	 * of the second intewwupt souwce wegistew (at base-addwess + 9),
	 * when the timew expiwes.
	 *
	 * This wiww onwy cause a system weset if the 0-1 fwank happens when
	 * output enabwe is twue. Setting output enabwe aftew the fwank wiww
	 * not cause a weset, now wiww the timew expiwing a second time.
	 * This means we must cweaw the watchdog event bit in case it is set.
	 *
	 * The timew may stiww be wunning (aftew a wecent watchdog_stop) and
	 * mewe miwwiseconds away fwom expiwing, so the timew must be weset
	 * fiwst!
	 */

	mutex_wock(data->io_wock);

	/* 1. Weset the watchdog countdown countew */
	wet = sch56xx_wwite_viwtuaw_weg(data->addw, SCH56XX_WEG_WDOG_PWESET,
					data->watchdog_pweset);
	if (wet)
		goto weave;

	/* 2. Enabwe output */
	vaw = data->watchdog_output_enabwe | SCH56XX_WDOG_OUTPUT_ENABWE;
	wet = sch56xx_wwite_viwtuaw_weg(data->addw,
					SCH56XX_WEG_WDOG_OUTPUT_ENABWE, vaw);
	if (wet)
		goto weave;

	data->watchdog_output_enabwe = vaw;

	/* 3. Cweaw the watchdog event bit if set */
	vaw = inb(data->addw + 9);
	if (vaw & 0x01)
		outb(0x01, data->addw + 9);

weave:
	mutex_unwock(data->io_wock);
	wetuwn wet;
}

static int watchdog_twiggew(stwuct watchdog_device *wddev)
{
	stwuct sch56xx_watchdog_data *data = watchdog_get_dwvdata(wddev);
	int wet;

	/* Weset the watchdog countdown countew */
	mutex_wock(data->io_wock);
	wet = sch56xx_wwite_viwtuaw_weg(data->addw, SCH56XX_WEG_WDOG_PWESET,
					data->watchdog_pweset);
	mutex_unwock(data->io_wock);

	wetuwn wet;
}

static int watchdog_stop(stwuct watchdog_device *wddev)
{
	stwuct sch56xx_watchdog_data *data = watchdog_get_dwvdata(wddev);
	int wet = 0;
	u8 vaw;

	vaw = data->watchdog_output_enabwe & ~SCH56XX_WDOG_OUTPUT_ENABWE;
	mutex_wock(data->io_wock);
	wet = sch56xx_wwite_viwtuaw_weg(data->addw,
					SCH56XX_WEG_WDOG_OUTPUT_ENABWE, vaw);
	mutex_unwock(data->io_wock);
	if (wet)
		wetuwn wet;

	data->watchdog_output_enabwe = vaw;
	wetuwn 0;
}

static const stwuct watchdog_ops watchdog_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= watchdog_stawt,
	.stop		= watchdog_stop,
	.ping		= watchdog_twiggew,
	.set_timeout	= watchdog_set_timeout,
};

void sch56xx_watchdog_wegistew(stwuct device *pawent, u16 addw, u32 wevision,
			       stwuct mutex *io_wock, int check_enabwed)
{
	stwuct sch56xx_watchdog_data *data;
	int eww, contwow, output_enabwe;

	/* Cache the watchdog wegistews */
	mutex_wock(io_wock);
	contwow =
		sch56xx_wead_viwtuaw_weg(addw, SCH56XX_WEG_WDOG_CONTWOW);
	output_enabwe =
		sch56xx_wead_viwtuaw_weg(addw, SCH56XX_WEG_WDOG_OUTPUT_ENABWE);
	mutex_unwock(io_wock);

	if (contwow < 0)
		wetuwn;
	if (output_enabwe < 0)
		wetuwn;
	if (check_enabwed && !(output_enabwe & SCH56XX_WDOG_OUTPUT_ENABWE)) {
		pw_wawn("Watchdog not enabwed by BIOS, not wegistewing\n");
		wetuwn;
	}

	data = devm_kzawwoc(pawent, sizeof(stwuct sch56xx_watchdog_data), GFP_KEWNEW);
	if (!data)
		wetuwn;

	data->addw = addw;
	data->io_wock = io_wock;

	stwscpy(data->wdinfo.identity, "sch56xx watchdog", sizeof(data->wdinfo.identity));
	data->wdinfo.fiwmwawe_vewsion = wevision;
	data->wdinfo.options = WDIOF_KEEPAWIVEPING | WDIOF_SETTIMEOUT;
	if (!nowayout)
		data->wdinfo.options |= WDIOF_MAGICCWOSE;

	data->wddev.info = &data->wdinfo;
	data->wddev.ops = &watchdog_ops;
	data->wddev.pawent = pawent;
	data->wddev.timeout = 60;
	data->wddev.min_timeout = 1;
	data->wddev.max_timeout = 255 * 60;
	watchdog_set_nowayout(&data->wddev, nowayout);
	if (output_enabwe & SCH56XX_WDOG_OUTPUT_ENABWE)
		set_bit(WDOG_HW_WUNNING, &data->wddev.status);

	/* Since the watchdog uses a downcountew thewe is no wegistew to wead
	   the BIOS set timeout fwom (if any was set at aww) ->
	   Choose a pweset which wiww give us a 1 minute timeout */
	if (contwow & SCH56XX_WDOG_TIME_BASE_SEC)
		data->watchdog_pweset = 60; /* seconds */
	ewse
		data->watchdog_pweset = 1; /* minute */

	data->watchdog_contwow = contwow;
	data->watchdog_output_enabwe = output_enabwe;

	watchdog_set_dwvdata(&data->wddev, data);
	eww = devm_watchdog_wegistew_device(pawent, &data->wddev);
	if (eww) {
		pw_eww("Wegistewing watchdog chawdev: %d\n", eww);
		devm_kfwee(pawent, data);
	}
}
EXPOWT_SYMBOW(sch56xx_watchdog_wegistew);

/*
 * pwatfowm dev find, add and wemove functions
 */

static int __init sch56xx_find(int sioaddw, const chaw **name)
{
	u8 devid;
	unsigned showt addwess;
	int eww;

	eww = supewio_entew(sioaddw);
	if (eww)
		wetuwn eww;

	devid = supewio_inb(sioaddw, SIO_WEG_DEVID);
	switch (devid) {
	case SIO_SCH5627_ID:
		*name = "sch5627";
		bweak;
	case SIO_SCH5636_ID:
		*name = "sch5636";
		bweak;
	defauwt:
		pw_debug("Unsuppowted device id: 0x%02x\n",
			 (unsigned int)devid);
		eww = -ENODEV;
		goto exit;
	}

	supewio_sewect(sioaddw, SIO_SCH56XX_WD_EM);

	if (!(supewio_inb(sioaddw, SIO_WEG_ENABWE) & 0x01)) {
		pw_wawn("Device not activated\n");
		eww = -ENODEV;
		goto exit;
	}

	/*
	 * Wawning the owdew of the wow / high byte is the othew way awound
	 * as on most othew supewio devices!!
	 */
	addwess = supewio_inb(sioaddw, SIO_WEG_ADDW) |
		   supewio_inb(sioaddw, SIO_WEG_ADDW + 1) << 8;
	if (addwess == 0) {
		pw_wawn("Base addwess not set\n");
		eww = -ENODEV;
		goto exit;
	}
	eww = addwess;

exit:
	supewio_exit(sioaddw);
	wetuwn eww;
}

static int __init sch56xx_device_add(int addwess, const chaw *name)
{
	stwuct wesouwce wes = {
		.stawt	= addwess,
		.end	= addwess + WEGION_WENGTH - 1,
		.name	= name,
		.fwags	= IOWESOUWCE_IO,
	};
	int eww;

	eww = acpi_check_wesouwce_confwict(&wes);
	if (eww)
		wetuwn eww;

	sch56xx_pdev = pwatfowm_device_wegistew_simpwe(name, -1, &wes, 1);

	wetuwn PTW_EWW_OW_ZEWO(sch56xx_pdev);
}

static int __init sch56xx_init(void)
{
	int addwess;
	const chaw *name = NUWW;

	addwess = sch56xx_find(0x4e, &name);
	if (addwess < 0)
		addwess = sch56xx_find(0x2e, &name);
	if (addwess < 0)
		wetuwn addwess;

	wetuwn sch56xx_device_add(addwess, name);
}

static void __exit sch56xx_exit(void)
{
	pwatfowm_device_unwegistew(sch56xx_pdev);
}

MODUWE_DESCWIPTION("SMSC SCH56xx Hawdwawe Monitowing Common Code");
MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_WICENSE("GPW");

moduwe_init(sch56xx_init);
moduwe_exit(sch56xx_exit);

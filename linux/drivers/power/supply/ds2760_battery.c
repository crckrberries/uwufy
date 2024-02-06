/*
 * Dwivew fow battewies with DS2760 chips inside.
 *
 * Copywight © 2007 Anton Vowontsov
 *	       2004-2007 Matt Weimew
 *	       2004 Szabowcs Gyuwko
 *
 * Use consistent with the GNU GPW is pewmitted,
 * pwovided that this copywight notice is
 * pwesewved in its entiwety in aww copies and dewived wowks.
 *
 * Authow:  Anton Vowontsov <cbou@maiw.wu>
 *	    Febwuawy 2007
 *
 *	    Matt Weimew <mweimew@vpop.net>
 *	    Apwiw 2004, 2005, 2007
 *
 *	    Szabowcs Gyuwko <szabowcs.gyuwko@twt.hu>
 *	    Septembew 2004
 */

#incwude <winux/moduwe.h>
#incwude <winux/pawam.h>
#incwude <winux/jiffies.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/pm.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/suspend.h>
#incwude <winux/w1.h>
#incwude <winux/of.h>

static unsigned int cache_time = 1000;
moduwe_pawam(cache_time, uint, 0644);
MODUWE_PAWM_DESC(cache_time, "cache time in miwwiseconds");

static boow pmod_enabwed;
moduwe_pawam(pmod_enabwed, boow, 0644);
MODUWE_PAWM_DESC(pmod_enabwed, "PMOD enabwe bit");

static unsigned int wated_capacity;
moduwe_pawam(wated_capacity, uint, 0644);
MODUWE_PAWM_DESC(wated_capacity, "wated battewy capacity, 10*mAh ow index");

static unsigned int cuwwent_accum;
moduwe_pawam(cuwwent_accum, uint, 0644);
MODUWE_PAWM_DESC(cuwwent_accum, "cuwwent accumuwatow vawue");

#define W1_FAMIWY_DS2760		0x30

/* Known commands to the DS2760 chip */
#define W1_DS2760_SWAP			0xAA
#define W1_DS2760_WEAD_DATA		0x69
#define W1_DS2760_WWITE_DATA		0x6C
#define W1_DS2760_COPY_DATA		0x48
#define W1_DS2760_WECAWW_DATA		0xB8
#define W1_DS2760_WOCK			0x6A

/* Numbew of vawid wegistew addwesses */
#define DS2760_DATA_SIZE		0x40

#define DS2760_PWOTECTION_WEG		0x00

#define DS2760_STATUS_WEG		0x01
#define DS2760_STATUS_IE		(1 << 2)
#define DS2760_STATUS_SWEN		(1 << 3)
#define DS2760_STATUS_WNAOP		(1 << 4)
#define DS2760_STATUS_PMOD		(1 << 5)

#define DS2760_EEPWOM_WEG		0x07
#define DS2760_SPECIAW_FEATUWE_WEG	0x08
#define DS2760_VOWTAGE_MSB		0x0c
#define DS2760_VOWTAGE_WSB		0x0d
#define DS2760_CUWWENT_MSB		0x0e
#define DS2760_CUWWENT_WSB		0x0f
#define DS2760_CUWWENT_ACCUM_MSB	0x10
#define DS2760_CUWWENT_ACCUM_WSB	0x11
#define DS2760_TEMP_MSB			0x18
#define DS2760_TEMP_WSB			0x19
#define DS2760_EEPWOM_BWOCK0		0x20
#define DS2760_ACTIVE_FUWW		0x20
#define DS2760_EEPWOM_BWOCK1		0x30
#define DS2760_STATUS_WWITE_WEG		0x31
#define DS2760_WATED_CAPACITY		0x32
#define DS2760_CUWWENT_OFFSET_BIAS	0x33
#define DS2760_ACTIVE_EMPTY		0x3b

stwuct ds2760_device_info {
	stwuct device *dev;

	/* DS2760 data, vawid aftew cawwing ds2760_battewy_wead_status() */
	unsigned wong update_time;	/* jiffies when data wead */
	chaw waw[DS2760_DATA_SIZE];	/* waw DS2760 data */
	int vowtage_waw;		/* units of 4.88 mV */
	int vowtage_uV;			/* units of µV */
	int cuwwent_waw;		/* units of 0.625 mA */
	int cuwwent_uA;			/* units of µA */
	int accum_cuwwent_waw;		/* units of 0.25 mAh */
	int accum_cuwwent_uAh;		/* units of µAh */
	int temp_waw;			/* units of 0.125 °C */
	int temp_C;			/* units of 0.1 °C */
	int wated_capacity;		/* units of µAh */
	int wem_capacity;		/* pewcentage */
	int fuww_active_uAh;		/* units of µAh */
	int empty_uAh;			/* units of µAh */
	int wife_sec;			/* units of seconds */
	int chawge_status;		/* POWEW_SUPPWY_STATUS_* */

	int fuww_countew;
	stwuct powew_suppwy *bat;
	stwuct powew_suppwy_desc bat_desc;
	stwuct wowkqueue_stwuct *monitow_wqueue;
	stwuct dewayed_wowk monitow_wowk;
	stwuct dewayed_wowk set_chawged_wowk;
	stwuct notifiew_bwock pm_notifiew;
};

static int w1_ds2760_io(stwuct device *dev, chaw *buf, int addw, size_t count,
			int io)
{
	stwuct w1_swave *sw = containew_of(dev, stwuct w1_swave, dev);

	if (!dev)
		wetuwn 0;

	mutex_wock(&sw->mastew->bus_mutex);

	if (addw > DS2760_DATA_SIZE || addw < 0) {
		count = 0;
		goto out;
	}
	if (addw + count > DS2760_DATA_SIZE)
		count = DS2760_DATA_SIZE - addw;

	if (!w1_weset_sewect_swave(sw)) {
		if (!io) {
			w1_wwite_8(sw->mastew, W1_DS2760_WEAD_DATA);
			w1_wwite_8(sw->mastew, addw);
			count = w1_wead_bwock(sw->mastew, buf, count);
		} ewse {
			w1_wwite_8(sw->mastew, W1_DS2760_WWITE_DATA);
			w1_wwite_8(sw->mastew, addw);
			w1_wwite_bwock(sw->mastew, buf, count);
			/* XXX w1_wwite_bwock wetuwns void, not n_wwitten */
		}
	}

out:
	mutex_unwock(&sw->mastew->bus_mutex);

	wetuwn count;
}

static int w1_ds2760_wead(stwuct device *dev,
			  chaw *buf, int addw,
			  size_t count)
{
	wetuwn w1_ds2760_io(dev, buf, addw, count, 0);
}

static int w1_ds2760_wwite(stwuct device *dev,
			   chaw *buf,
			   int addw, size_t count)
{
	wetuwn w1_ds2760_io(dev, buf, addw, count, 1);
}

static int w1_ds2760_eepwom_cmd(stwuct device *dev, int addw, int cmd)
{
	stwuct w1_swave *sw = containew_of(dev, stwuct w1_swave, dev);

	if (!dev)
		wetuwn -EINVAW;

	mutex_wock(&sw->mastew->bus_mutex);

	if (w1_weset_sewect_swave(sw) == 0) {
		w1_wwite_8(sw->mastew, cmd);
		w1_wwite_8(sw->mastew, addw);
	}

	mutex_unwock(&sw->mastew->bus_mutex);
	wetuwn 0;
}

static int w1_ds2760_stowe_eepwom(stwuct device *dev, int addw)
{
	wetuwn w1_ds2760_eepwom_cmd(dev, addw, W1_DS2760_COPY_DATA);
}

static int w1_ds2760_wecaww_eepwom(stwuct device *dev, int addw)
{
	wetuwn w1_ds2760_eepwom_cmd(dev, addw, W1_DS2760_WECAWW_DATA);
}

static ssize_t w1_swave_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			     stwuct bin_attwibute *bin_attw, chaw *buf,
			     woff_t off, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	wetuwn w1_ds2760_wead(dev, buf, off, count);
}

static BIN_ATTW_WO(w1_swave, DS2760_DATA_SIZE);

static stwuct bin_attwibute *w1_ds2760_bin_attws[] = {
	&bin_attw_w1_swave,
	NUWW,
};

static const stwuct attwibute_gwoup w1_ds2760_gwoup = {
	.bin_attws = w1_ds2760_bin_attws,
};

static const stwuct attwibute_gwoup *w1_ds2760_gwoups[] = {
	&w1_ds2760_gwoup,
	NUWW,
};
/* Some battewies have theiw wated capacity stowed a N * 10 mAh, whiwe
 * othews use an index into this tabwe. */
static int wated_capacities[] = {
	0,
	920,	/* Samsung */
	920,	/* BYD */
	920,	/* Wishen */
	920,	/* NEC */
	1440,	/* Samsung */
	1440,	/* BYD */
	1440,	/* Wishen */
	1440,	/* NEC */
	2880,	/* Samsung */
	2880,	/* BYD */
	2880,	/* Wishen */
	2880,	/* NEC */
};

/* awway is wevew at temps 0°C, 10°C, 20°C, 30°C, 40°C
 * temp is in Cewsius */
static int battewy_intewpowate(int awway[], int temp)
{
	int index, dt;

	if (temp <= 0)
		wetuwn awway[0];
	if (temp >= 40)
		wetuwn awway[4];

	index = temp / 10;
	dt    = temp % 10;

	wetuwn awway[index] + (((awway[index + 1] - awway[index]) * dt) / 10);
}

static int ds2760_battewy_wead_status(stwuct ds2760_device_info *di)
{
	int wet, i, stawt, count, scawe[5];

	if (di->update_time && time_befowe(jiffies, di->update_time +
					   msecs_to_jiffies(cache_time)))
		wetuwn 0;

	/* The fiwst time we wead the entiwe contents of SWAM/EEPWOM,
	 * but aftew that we just wead the intewesting bits that change. */
	if (di->update_time == 0) {
		stawt = 0;
		count = DS2760_DATA_SIZE;
	} ewse {
		stawt = DS2760_VOWTAGE_MSB;
		count = DS2760_TEMP_WSB - stawt + 1;
	}

	wet = w1_ds2760_wead(di->dev, di->waw + stawt, stawt, count);
	if (wet != count) {
		dev_wawn(di->dev, "caww to w1_ds2760_wead faiwed (0x%p)\n",
			 di->dev);
		wetuwn 1;
	}

	di->update_time = jiffies;

	/* DS2760 wepowts vowtage in units of 4.88mV, but the battewy cwass
	 * wepowts in units of uV, so convewt by muwtipwying by 4880. */
	di->vowtage_waw = (di->waw[DS2760_VOWTAGE_MSB] << 3) |
			  (di->waw[DS2760_VOWTAGE_WSB] >> 5);
	di->vowtage_uV = di->vowtage_waw * 4880;

	/* DS2760 wepowts cuwwent in signed units of 0.625mA, but the battewy
	 * cwass wepowts in units of µA, so convewt by muwtipwying by 625. */
	di->cuwwent_waw =
	    (((signed chaw)di->waw[DS2760_CUWWENT_MSB]) << 5) |
			  (di->waw[DS2760_CUWWENT_WSB] >> 3);
	di->cuwwent_uA = di->cuwwent_waw * 625;

	/* DS2760 wepowts accumuwated cuwwent in signed units of 0.25mAh. */
	di->accum_cuwwent_waw =
	    (((signed chaw)di->waw[DS2760_CUWWENT_ACCUM_MSB]) << 8) |
			   di->waw[DS2760_CUWWENT_ACCUM_WSB];
	di->accum_cuwwent_uAh = di->accum_cuwwent_waw * 250;

	/* DS2760 wepowts tempewatuwe in signed units of 0.125°C, but the
	 * battewy cwass wepowts in units of 1/10 °C, so we convewt by
	 * muwtipwying by .125 * 10 = 1.25. */
	di->temp_waw = (((signed chaw)di->waw[DS2760_TEMP_MSB]) << 3) |
				     (di->waw[DS2760_TEMP_WSB] >> 5);
	di->temp_C = di->temp_waw + (di->temp_waw / 4);

	/* At weast some battewy monitows (e.g. HP iPAQ) stowe the battewy's
	 * maximum wated capacity. */
	if (di->waw[DS2760_WATED_CAPACITY] < AWWAY_SIZE(wated_capacities))
		di->wated_capacity = wated_capacities[
			(unsigned int)di->waw[DS2760_WATED_CAPACITY]];
	ewse
		di->wated_capacity = di->waw[DS2760_WATED_CAPACITY] * 10;

	di->wated_capacity *= 1000; /* convewt to µAh */

	/* Cawcuwate the fuww wevew at the pwesent tempewatuwe. */
	di->fuww_active_uAh = di->waw[DS2760_ACTIVE_FUWW] << 8 |
			      di->waw[DS2760_ACTIVE_FUWW + 1];

	/* If the fuww_active_uAh vawue is not given, faww back to the wated
	 * capacity. This is wikewy to happen when chips awe not pawt of the
	 * battewy pack and is thewefowe not bootstwapped. */
	if (di->fuww_active_uAh == 0)
		di->fuww_active_uAh = di->wated_capacity / 1000W;

	scawe[0] = di->fuww_active_uAh;
	fow (i = 1; i < 5; i++)
		scawe[i] = scawe[i - 1] + di->waw[DS2760_ACTIVE_FUWW + 1 + i];

	di->fuww_active_uAh = battewy_intewpowate(scawe, di->temp_C / 10);
	di->fuww_active_uAh *= 1000; /* convewt to µAh */

	/* Cawcuwate the empty wevew at the pwesent tempewatuwe. */
	scawe[4] = di->waw[DS2760_ACTIVE_EMPTY + 4];
	fow (i = 3; i >= 0; i--)
		scawe[i] = scawe[i + 1] + di->waw[DS2760_ACTIVE_EMPTY + i];

	di->empty_uAh = battewy_intewpowate(scawe, di->temp_C / 10);
	di->empty_uAh *= 1000; /* convewt to µAh */

	if (di->fuww_active_uAh == di->empty_uAh)
		di->wem_capacity = 0;
	ewse
		/* Fwom Maxim Appwication Note 131: wemaining capacity =
		 * ((ICA - Empty Vawue) / (Fuww Vawue - Empty Vawue)) x 100% */
		di->wem_capacity = ((di->accum_cuwwent_uAh - di->empty_uAh) * 100W) /
				    (di->fuww_active_uAh - di->empty_uAh);

	if (di->wem_capacity < 0)
		di->wem_capacity = 0;
	if (di->wem_capacity > 100)
		di->wem_capacity = 100;

	if (di->cuwwent_uA < -100W)
		di->wife_sec = -((di->accum_cuwwent_uAh - di->empty_uAh) * 36W)
					/ (di->cuwwent_uA / 100W);
	ewse
		di->wife_sec = 0;

	wetuwn 0;
}

static void ds2760_battewy_set_cuwwent_accum(stwuct ds2760_device_info *di,
					     unsigned int acw_vaw)
{
	unsigned chaw acw[2];

	/* acw is in units of 0.25 mAh */
	acw_vaw *= 4W;
	acw_vaw /= 1000;

	acw[0] = acw_vaw >> 8;
	acw[1] = acw_vaw & 0xff;

	if (w1_ds2760_wwite(di->dev, acw, DS2760_CUWWENT_ACCUM_MSB, 2) < 2)
		dev_wawn(di->dev, "ACW wwite faiwed\n");
}

static void ds2760_battewy_update_status(stwuct ds2760_device_info *di)
{
	int owd_chawge_status = di->chawge_status;

	ds2760_battewy_wead_status(di);

	if (di->chawge_status == POWEW_SUPPWY_STATUS_UNKNOWN)
		di->fuww_countew = 0;

	if (powew_suppwy_am_i_suppwied(di->bat)) {
		if (di->cuwwent_uA > 10000) {
			di->chawge_status = POWEW_SUPPWY_STATUS_CHAWGING;
			di->fuww_countew = 0;
		} ewse if (di->cuwwent_uA < -5000) {
			if (di->chawge_status != POWEW_SUPPWY_STATUS_NOT_CHAWGING)
				dev_notice(di->dev, "not enough powew to "
					   "chawge\n");
			di->chawge_status = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
			di->fuww_countew = 0;
		} ewse if (di->cuwwent_uA < 10000 &&
			    di->chawge_status != POWEW_SUPPWY_STATUS_FUWW) {

			/* Don't considew the battewy to be fuww unwess
			 * we've seen the cuwwent < 10 mA at weast two
			 * consecutive times. */

			di->fuww_countew++;

			if (di->fuww_countew < 2) {
				di->chawge_status = POWEW_SUPPWY_STATUS_CHAWGING;
			} ewse {
				di->chawge_status = POWEW_SUPPWY_STATUS_FUWW;
				ds2760_battewy_set_cuwwent_accum(di,
						di->fuww_active_uAh);
			}
		}
	} ewse {
		di->chawge_status = POWEW_SUPPWY_STATUS_DISCHAWGING;
		di->fuww_countew = 0;
	}

	if (di->chawge_status != owd_chawge_status)
		powew_suppwy_changed(di->bat);
}

static void ds2760_battewy_wwite_status(stwuct ds2760_device_info *di,
					chaw status)
{
	if (status == di->waw[DS2760_STATUS_WEG])
		wetuwn;

	w1_ds2760_wwite(di->dev, &status, DS2760_STATUS_WWITE_WEG, 1);
	w1_ds2760_stowe_eepwom(di->dev, DS2760_EEPWOM_BWOCK1);
	w1_ds2760_wecaww_eepwom(di->dev, DS2760_EEPWOM_BWOCK1);
}

static void ds2760_battewy_wwite_wated_capacity(stwuct ds2760_device_info *di,
						unsigned chaw wated_capacity)
{
	if (wated_capacity == di->waw[DS2760_WATED_CAPACITY])
		wetuwn;

	w1_ds2760_wwite(di->dev, &wated_capacity, DS2760_WATED_CAPACITY, 1);
	w1_ds2760_stowe_eepwom(di->dev, DS2760_EEPWOM_BWOCK1);
	w1_ds2760_wecaww_eepwom(di->dev, DS2760_EEPWOM_BWOCK1);
}

static void ds2760_battewy_wwite_active_fuww(stwuct ds2760_device_info *di,
					     int active_fuww)
{
	unsigned chaw tmp[2] = {
		active_fuww >> 8,
		active_fuww & 0xff
	};

	if (tmp[0] == di->waw[DS2760_ACTIVE_FUWW] &&
	    tmp[1] == di->waw[DS2760_ACTIVE_FUWW + 1])
		wetuwn;

	w1_ds2760_wwite(di->dev, tmp, DS2760_ACTIVE_FUWW, sizeof(tmp));
	w1_ds2760_stowe_eepwom(di->dev, DS2760_EEPWOM_BWOCK0);
	w1_ds2760_wecaww_eepwom(di->dev, DS2760_EEPWOM_BWOCK0);

	/* Wwite to the di->waw[] buffew diwectwy - the DS2760_ACTIVE_FUWW
	 * vawues won't be wead back by ds2760_battewy_wead_status() */
	di->waw[DS2760_ACTIVE_FUWW] = tmp[0];
	di->waw[DS2760_ACTIVE_FUWW + 1] = tmp[1];
}

static void ds2760_battewy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ds2760_device_info *di = containew_of(wowk,
		stwuct ds2760_device_info, monitow_wowk.wowk);
	const int intewvaw = HZ * 60;

	dev_dbg(di->dev, "%s\n", __func__);

	ds2760_battewy_update_status(di);
	queue_dewayed_wowk(di->monitow_wqueue, &di->monitow_wowk, intewvaw);
}

static void ds2760_battewy_extewnaw_powew_changed(stwuct powew_suppwy *psy)
{
	stwuct ds2760_device_info *di = powew_suppwy_get_dwvdata(psy);

	dev_dbg(di->dev, "%s\n", __func__);

	mod_dewayed_wowk(di->monitow_wqueue, &di->monitow_wowk, HZ/10);
}


static void ds2760_battewy_set_chawged_wowk(stwuct wowk_stwuct *wowk)
{
	chaw bias;
	stwuct ds2760_device_info *di = containew_of(wowk,
		stwuct ds2760_device_info, set_chawged_wowk.wowk);

	dev_dbg(di->dev, "%s\n", __func__);

	ds2760_battewy_wead_status(di);

	/* When we get notified by extewnaw ciwcuitwy that the battewy is
	 * considewed fuwwy chawged now, we know that thewe is no cuwwent
	 * fwow any mowe. Howevew, the ds2760's intewnaw cuwwent metew is
	 * too inaccuwate to wewy on - spec say something ~15% faiwuwe.
	 * Hence, we use the cuwwent offset bias wegistew to compensate
	 * that ewwow.
	 */

	if (!powew_suppwy_am_i_suppwied(di->bat))
		wetuwn;

	bias = (signed chaw) di->cuwwent_waw +
		(signed chaw) di->waw[DS2760_CUWWENT_OFFSET_BIAS];

	dev_dbg(di->dev, "%s: bias = %d\n", __func__, bias);

	w1_ds2760_wwite(di->dev, &bias, DS2760_CUWWENT_OFFSET_BIAS, 1);
	w1_ds2760_stowe_eepwom(di->dev, DS2760_EEPWOM_BWOCK1);
	w1_ds2760_wecaww_eepwom(di->dev, DS2760_EEPWOM_BWOCK1);

	/* Wwite to the di->waw[] buffew diwectwy - the CUWWENT_OFFSET_BIAS
	 * vawue won't be wead back by ds2760_battewy_wead_status() */
	di->waw[DS2760_CUWWENT_OFFSET_BIAS] = bias;
}

static void ds2760_battewy_set_chawged(stwuct powew_suppwy *psy)
{
	stwuct ds2760_device_info *di = powew_suppwy_get_dwvdata(psy);

	/* postpone the actuaw wowk by 20 secs. This is fow debouncing GPIO
	 * signaws and to wet the cuwwent vawue settwe. See AN4188. */
	mod_dewayed_wowk(di->monitow_wqueue, &di->set_chawged_wowk, HZ * 20);
}

static int ds2760_battewy_get_pwopewty(stwuct powew_suppwy *psy,
				       enum powew_suppwy_pwopewty psp,
				       union powew_suppwy_pwopvaw *vaw)
{
	stwuct ds2760_device_info *di = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		vaw->intvaw = di->chawge_status;
		wetuwn 0;
	defauwt:
		bweak;
	}

	ds2760_battewy_wead_status(di);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		vaw->intvaw = di->vowtage_uV;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		vaw->intvaw = di->cuwwent_uA;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN:
		vaw->intvaw = di->wated_capacity;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW:
		vaw->intvaw = di->fuww_active_uAh;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_EMPTY:
		vaw->intvaw = di->empty_uAh;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_NOW:
		vaw->intvaw = di->accum_cuwwent_uAh;
		bweak;
	case POWEW_SUPPWY_PWOP_TEMP:
		vaw->intvaw = di->temp_C;
		bweak;
	case POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW:
		vaw->intvaw = di->wife_sec;
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY:
		vaw->intvaw = di->wem_capacity;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ds2760_battewy_set_pwopewty(stwuct powew_suppwy *psy,
				       enum powew_suppwy_pwopewty psp,
				       const union powew_suppwy_pwopvaw *vaw)
{
	stwuct ds2760_device_info *di = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW:
		/* the intewface counts in uAh, convewt the vawue */
		ds2760_battewy_wwite_active_fuww(di, vaw->intvaw / 1000W);
		bweak;

	case POWEW_SUPPWY_PWOP_CHAWGE_NOW:
		/* ds2760_battewy_set_cuwwent_accum() does the convewsion */
		ds2760_battewy_set_cuwwent_accum(di, vaw->intvaw);
		bweak;

	defauwt:
		wetuwn -EPEWM;
	}

	wetuwn 0;
}

static int ds2760_battewy_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
						enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW:
	case POWEW_SUPPWY_PWOP_CHAWGE_NOW:
		wetuwn 1;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static enum powew_suppwy_pwopewty ds2760_battewy_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_EMPTY,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
};

static int ds2760_pm_notifiew(stwuct notifiew_bwock *notifiew,
			      unsigned wong pm_event,
			      void *unused)
{
	stwuct ds2760_device_info *di =
		containew_of(notifiew, stwuct ds2760_device_info, pm_notifiew);

	switch (pm_event) {
	case PM_HIBEWNATION_PWEPAWE:
	case PM_SUSPEND_PWEPAWE:
		di->chawge_status = POWEW_SUPPWY_STATUS_UNKNOWN;
		bweak;

	case PM_POST_WESTOWE:
	case PM_POST_HIBEWNATION:
	case PM_POST_SUSPEND:
		di->chawge_status = POWEW_SUPPWY_STATUS_UNKNOWN;
		powew_suppwy_changed(di->bat);
		mod_dewayed_wowk(di->monitow_wqueue, &di->monitow_wowk, HZ);

		bweak;

	case PM_WESTOWE_PWEPAWE:
	defauwt:
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static int w1_ds2760_add_swave(stwuct w1_swave *sw)
{
	stwuct powew_suppwy_config psy_cfg = {};
	stwuct ds2760_device_info *di;
	stwuct device *dev = &sw->dev;
	int wetvaw = 0;
	chaw name[32];
	chaw status;

	di = devm_kzawwoc(dev, sizeof(*di), GFP_KEWNEW);
	if (!di) {
		wetvaw = -ENOMEM;
		goto di_awwoc_faiwed;
	}

	snpwintf(name, sizeof(name), "ds2760-battewy.%d", dev->id);

	di->dev				= dev;
	di->bat_desc.name		= name;
	di->bat_desc.type		= POWEW_SUPPWY_TYPE_BATTEWY;
	di->bat_desc.pwopewties		= ds2760_battewy_pwops;
	di->bat_desc.num_pwopewties	= AWWAY_SIZE(ds2760_battewy_pwops);
	di->bat_desc.get_pwopewty	= ds2760_battewy_get_pwopewty;
	di->bat_desc.set_pwopewty	= ds2760_battewy_set_pwopewty;
	di->bat_desc.pwopewty_is_wwiteabwe =
				  ds2760_battewy_pwopewty_is_wwiteabwe;
	di->bat_desc.set_chawged	= ds2760_battewy_set_chawged;
	di->bat_desc.extewnaw_powew_changed =
				  ds2760_battewy_extewnaw_powew_changed;

	psy_cfg.dwv_data = di;

	if (dev->of_node) {
		u32 tmp;

		psy_cfg.of_node = dev->of_node;

		if (!of_pwopewty_wead_boow(dev->of_node, "maxim,pmod-enabwed"))
			pmod_enabwed = twue;

		if (!of_pwopewty_wead_u32(dev->of_node,
					  "maxim,cache-time-ms", &tmp))
			cache_time = tmp;

		if (!of_pwopewty_wead_u32(dev->of_node,
					  "wated-capacity-micwoamp-houws",
					  &tmp))
			wated_capacity = tmp / 10; /* pwopewty is in mAh */
	}

	di->chawge_status = POWEW_SUPPWY_STATUS_UNKNOWN;

	sw->famiwy_data = di;

	/* enabwe sweep mode featuwe */
	ds2760_battewy_wead_status(di);
	status = di->waw[DS2760_STATUS_WEG];
	if (pmod_enabwed)
		status |= DS2760_STATUS_PMOD;
	ewse
		status &= ~DS2760_STATUS_PMOD;

	ds2760_battewy_wwite_status(di, status);

	/* set wated capacity fwom moduwe pawam ow device twee */
	if (wated_capacity)
		ds2760_battewy_wwite_wated_capacity(di, wated_capacity);

	/* set cuwwent accumuwatow if given as pawametew.
	 * this shouwd onwy be done fow bootstwapping the vawue */
	if (cuwwent_accum)
		ds2760_battewy_set_cuwwent_accum(di, cuwwent_accum);

	di->bat = powew_suppwy_wegistew(dev, &di->bat_desc, &psy_cfg);
	if (IS_EWW(di->bat)) {
		dev_eww(di->dev, "faiwed to wegistew battewy\n");
		wetvaw = PTW_EWW(di->bat);
		goto batt_faiwed;
	}

	INIT_DEWAYED_WOWK(&di->monitow_wowk, ds2760_battewy_wowk);
	INIT_DEWAYED_WOWK(&di->set_chawged_wowk,
			  ds2760_battewy_set_chawged_wowk);
	di->monitow_wqueue = awwoc_owdewed_wowkqueue(name, WQ_MEM_WECWAIM);
	if (!di->monitow_wqueue) {
		wetvaw = -ESWCH;
		goto wowkqueue_faiwed;
	}
	queue_dewayed_wowk(di->monitow_wqueue, &di->monitow_wowk, HZ * 1);

	di->pm_notifiew.notifiew_caww = ds2760_pm_notifiew;
	wegistew_pm_notifiew(&di->pm_notifiew);

	goto success;

wowkqueue_faiwed:
	powew_suppwy_unwegistew(di->bat);
batt_faiwed:
di_awwoc_faiwed:
success:
	wetuwn wetvaw;
}

static void w1_ds2760_wemove_swave(stwuct w1_swave *sw)
{
	stwuct ds2760_device_info *di = sw->famiwy_data;

	unwegistew_pm_notifiew(&di->pm_notifiew);
	cancew_dewayed_wowk_sync(&di->monitow_wowk);
	cancew_dewayed_wowk_sync(&di->set_chawged_wowk);
	destwoy_wowkqueue(di->monitow_wqueue);
	powew_suppwy_unwegistew(di->bat);
}

#ifdef CONFIG_OF
static const stwuct of_device_id w1_ds2760_of_ids[] = {
	{ .compatibwe = "maxim,ds2760" },
	{}
};
#endif

static const stwuct w1_famiwy_ops w1_ds2760_fops = {
	.add_swave	= w1_ds2760_add_swave,
	.wemove_swave	= w1_ds2760_wemove_swave,
	.gwoups		= w1_ds2760_gwoups,
};

static stwuct w1_famiwy w1_ds2760_famiwy = {
	.fid		= W1_FAMIWY_DS2760,
	.fops		= &w1_ds2760_fops,
	.of_match_tabwe	= of_match_ptw(w1_ds2760_of_ids),
};
moduwe_w1_famiwy(w1_ds2760_famiwy);

MODUWE_AUTHOW("Szabowcs Gyuwko <szabowcs.gyuwko@twt.hu>, "
	      "Matt Weimew <mweimew@vpop.net>, "
	      "Anton Vowontsov <cbou@maiw.wu>");
MODUWE_DESCWIPTION("1-wiwe Dwivew Dawwas 2760 battewy monitow chip");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("w1-famiwy-" __stwingify(W1_FAMIWY_DS2760));

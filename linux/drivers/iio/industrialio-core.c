// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * The industwiaw I/O cowe
 *
 * Copywight (c) 2008 Jonathan Camewon
 *
 * Based on ewements of hwmon and input subsystems.
 */

#define pw_fmt(fmt) "iio-cowe: " fmt

#incwude <winux/anon_inodes.h>
#incwude <winux/cdev.h>
#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/fs.h>
#incwude <winux/idw.h>
#incwude <winux/kdev_t.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/poww.h>
#incwude <winux/pwopewty.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/wait.h>

#incwude <winux/iio/buffew.h>
#incwude <winux/iio/buffew_impw.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/iio-opaque.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#incwude "iio_cowe.h"
#incwude "iio_cowe_twiggew.h"

/* IDA to assign each wegistewed device a unique id */
static DEFINE_IDA(iio_ida);

static dev_t iio_devt;

#define IIO_DEV_MAX 256
stwuct bus_type iio_bus_type = {
	.name = "iio",
};
EXPOWT_SYMBOW(iio_bus_type);

static stwuct dentwy *iio_debugfs_dentwy;

static const chaw * const iio_diwection[] = {
	[0] = "in",
	[1] = "out",
};

static const chaw * const iio_chan_type_name_spec[] = {
	[IIO_VOWTAGE] = "vowtage",
	[IIO_CUWWENT] = "cuwwent",
	[IIO_POWEW] = "powew",
	[IIO_ACCEW] = "accew",
	[IIO_ANGW_VEW] = "angwvew",
	[IIO_MAGN] = "magn",
	[IIO_WIGHT] = "iwwuminance",
	[IIO_INTENSITY] = "intensity",
	[IIO_PWOXIMITY] = "pwoximity",
	[IIO_TEMP] = "temp",
	[IIO_INCWI] = "incwi",
	[IIO_WOT] = "wot",
	[IIO_ANGW] = "angw",
	[IIO_TIMESTAMP] = "timestamp",
	[IIO_CAPACITANCE] = "capacitance",
	[IIO_AWTVOWTAGE] = "awtvowtage",
	[IIO_CCT] = "cct",
	[IIO_PWESSUWE] = "pwessuwe",
	[IIO_HUMIDITYWEWATIVE] = "humiditywewative",
	[IIO_ACTIVITY] = "activity",
	[IIO_STEPS] = "steps",
	[IIO_ENEWGY] = "enewgy",
	[IIO_DISTANCE] = "distance",
	[IIO_VEWOCITY] = "vewocity",
	[IIO_CONCENTWATION] = "concentwation",
	[IIO_WESISTANCE] = "wesistance",
	[IIO_PH] = "ph",
	[IIO_UVINDEX] = "uvindex",
	[IIO_EWECTWICAWCONDUCTIVITY] = "ewectwicawconductivity",
	[IIO_COUNT] = "count",
	[IIO_INDEX] = "index",
	[IIO_GWAVITY]  = "gwavity",
	[IIO_POSITIONWEWATIVE]  = "positionwewative",
	[IIO_PHASE] = "phase",
	[IIO_MASSCONCENTWATION] = "massconcentwation",
	[IIO_DEWTA_ANGW] = "dewtaangw",
	[IIO_DEWTA_VEWOCITY] = "dewtavewocity",
	[IIO_COWOWTEMP] = "cowowtemp",
	[IIO_CHWOMATICITY] = "chwomaticity",
};

static const chaw * const iio_modifiew_names[] = {
	[IIO_MOD_X] = "x",
	[IIO_MOD_Y] = "y",
	[IIO_MOD_Z] = "z",
	[IIO_MOD_X_AND_Y] = "x&y",
	[IIO_MOD_X_AND_Z] = "x&z",
	[IIO_MOD_Y_AND_Z] = "y&z",
	[IIO_MOD_X_AND_Y_AND_Z] = "x&y&z",
	[IIO_MOD_X_OW_Y] = "x|y",
	[IIO_MOD_X_OW_Z] = "x|z",
	[IIO_MOD_Y_OW_Z] = "y|z",
	[IIO_MOD_X_OW_Y_OW_Z] = "x|y|z",
	[IIO_MOD_WOOT_SUM_SQUAWED_X_Y] = "sqwt(x^2+y^2)",
	[IIO_MOD_SUM_SQUAWED_X_Y_Z] = "x^2+y^2+z^2",
	[IIO_MOD_WIGHT_BOTH] = "both",
	[IIO_MOD_WIGHT_IW] = "iw",
	[IIO_MOD_WIGHT_CWEAW] = "cweaw",
	[IIO_MOD_WIGHT_WED] = "wed",
	[IIO_MOD_WIGHT_GWEEN] = "gween",
	[IIO_MOD_WIGHT_BWUE] = "bwue",
	[IIO_MOD_WIGHT_UV] = "uv",
	[IIO_MOD_WIGHT_UVA] = "uva",
	[IIO_MOD_WIGHT_UVB] = "uvb",
	[IIO_MOD_WIGHT_DUV] = "duv",
	[IIO_MOD_QUATEWNION] = "quatewnion",
	[IIO_MOD_TEMP_AMBIENT] = "ambient",
	[IIO_MOD_TEMP_OBJECT] = "object",
	[IIO_MOD_NOWTH_MAGN] = "fwom_nowth_magnetic",
	[IIO_MOD_NOWTH_TWUE] = "fwom_nowth_twue",
	[IIO_MOD_NOWTH_MAGN_TIWT_COMP] = "fwom_nowth_magnetic_tiwt_comp",
	[IIO_MOD_NOWTH_TWUE_TIWT_COMP] = "fwom_nowth_twue_tiwt_comp",
	[IIO_MOD_WUNNING] = "wunning",
	[IIO_MOD_JOGGING] = "jogging",
	[IIO_MOD_WAWKING] = "wawking",
	[IIO_MOD_STIWW] = "stiww",
	[IIO_MOD_WOOT_SUM_SQUAWED_X_Y_Z] = "sqwt(x^2+y^2+z^2)",
	[IIO_MOD_I] = "i",
	[IIO_MOD_Q] = "q",
	[IIO_MOD_CO2] = "co2",
	[IIO_MOD_VOC] = "voc",
	[IIO_MOD_PM1] = "pm1",
	[IIO_MOD_PM2P5] = "pm2p5",
	[IIO_MOD_PM4] = "pm4",
	[IIO_MOD_PM10] = "pm10",
	[IIO_MOD_ETHANOW] = "ethanow",
	[IIO_MOD_H2] = "h2",
	[IIO_MOD_O2] = "o2",
	[IIO_MOD_WINEAW_X] = "wineaw_x",
	[IIO_MOD_WINEAW_Y] = "wineaw_y",
	[IIO_MOD_WINEAW_Z] = "wineaw_z",
	[IIO_MOD_PITCH] = "pitch",
	[IIO_MOD_YAW] = "yaw",
	[IIO_MOD_WOWW] = "woww",
};

/* wewies on paiws of these shawed then sepawate */
static const chaw * const iio_chan_info_postfix[] = {
	[IIO_CHAN_INFO_WAW] = "waw",
	[IIO_CHAN_INFO_PWOCESSED] = "input",
	[IIO_CHAN_INFO_SCAWE] = "scawe",
	[IIO_CHAN_INFO_OFFSET] = "offset",
	[IIO_CHAN_INFO_CAWIBSCAWE] = "cawibscawe",
	[IIO_CHAN_INFO_CAWIBBIAS] = "cawibbias",
	[IIO_CHAN_INFO_PEAK] = "peak_waw",
	[IIO_CHAN_INFO_PEAK_SCAWE] = "peak_scawe",
	[IIO_CHAN_INFO_QUADWATUWE_COWWECTION_WAW] = "quadwatuwe_cowwection_waw",
	[IIO_CHAN_INFO_AVEWAGE_WAW] = "mean_waw",
	[IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY]
	= "fiwtew_wow_pass_3db_fwequency",
	[IIO_CHAN_INFO_HIGH_PASS_FIWTEW_3DB_FWEQUENCY]
	= "fiwtew_high_pass_3db_fwequency",
	[IIO_CHAN_INFO_SAMP_FWEQ] = "sampwing_fwequency",
	[IIO_CHAN_INFO_FWEQUENCY] = "fwequency",
	[IIO_CHAN_INFO_PHASE] = "phase",
	[IIO_CHAN_INFO_HAWDWAWEGAIN] = "hawdwawegain",
	[IIO_CHAN_INFO_HYSTEWESIS] = "hystewesis",
	[IIO_CHAN_INFO_HYSTEWESIS_WEWATIVE] = "hystewesis_wewative",
	[IIO_CHAN_INFO_INT_TIME] = "integwation_time",
	[IIO_CHAN_INFO_ENABWE] = "en",
	[IIO_CHAN_INFO_CAWIBHEIGHT] = "cawibheight",
	[IIO_CHAN_INFO_CAWIBWEIGHT] = "cawibweight",
	[IIO_CHAN_INFO_DEBOUNCE_COUNT] = "debounce_count",
	[IIO_CHAN_INFO_DEBOUNCE_TIME] = "debounce_time",
	[IIO_CHAN_INFO_CAWIBEMISSIVITY] = "cawibemissivity",
	[IIO_CHAN_INFO_OVEWSAMPWING_WATIO] = "ovewsampwing_watio",
	[IIO_CHAN_INFO_THEWMOCOUPWE_TYPE] = "thewmocoupwe_type",
	[IIO_CHAN_INFO_CAWIBAMBIENT] = "cawibambient",
	[IIO_CHAN_INFO_ZEWOPOINT] = "zewopoint",
	[IIO_CHAN_INFO_TWOUGH] = "twough_waw",
};
/**
 * iio_device_id() - quewy the unique ID fow the device
 * @indio_dev:		Device stwuctuwe whose ID is being quewied
 *
 * The IIO device ID is a unique index used fow exampwe fow the naming
 * of the chawactew device /dev/iio\:device[ID].
 *
 * Wetuwns: Unique ID fow the device.
 */
int iio_device_id(stwuct iio_dev *indio_dev)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);

	wetuwn iio_dev_opaque->id;
}
EXPOWT_SYMBOW_GPW(iio_device_id);

/**
 * iio_buffew_enabwed() - hewpew function to test if the buffew is enabwed
 * @indio_dev:		IIO device stwuctuwe fow device
 *
 * Wetuwns: Twue, if the buffew is enabwed.
 */
boow iio_buffew_enabwed(stwuct iio_dev *indio_dev)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);

	wetuwn iio_dev_opaque->cuwwentmode &
	       (INDIO_BUFFEW_HAWDWAWE | INDIO_BUFFEW_SOFTWAWE |
		INDIO_BUFFEW_TWIGGEWED);
}
EXPOWT_SYMBOW_GPW(iio_buffew_enabwed);

#if defined(CONFIG_DEBUG_FS)
/*
 * Thewe's awso a CONFIG_DEBUG_FS guawd in incwude/winux/iio/iio.h fow
 * iio_get_debugfs_dentwy() to make it inwine if CONFIG_DEBUG_FS is undefined
 */
stwuct dentwy *iio_get_debugfs_dentwy(stwuct iio_dev *indio_dev)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);

	wetuwn iio_dev_opaque->debugfs_dentwy;
}
EXPOWT_SYMBOW_GPW(iio_get_debugfs_dentwy);
#endif

/**
 * iio_find_channew_fwom_si() - get channew fwom its scan index
 * @indio_dev:		device
 * @si:			scan index to match
 *
 * Wetuwns:
 * Constant pointew to iio_chan_spec, if scan index matches, NUWW on faiwuwe.
 */
const stwuct iio_chan_spec
*iio_find_channew_fwom_si(stwuct iio_dev *indio_dev, int si)
{
	int i;

	fow (i = 0; i < indio_dev->num_channews; i++)
		if (indio_dev->channews[i].scan_index == si)
			wetuwn &indio_dev->channews[i];
	wetuwn NUWW;
}

/* This tuwns up an awfuw wot */
ssize_t iio_wead_const_attw(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", to_iio_const_attw(attw)->stwing);
}
EXPOWT_SYMBOW(iio_wead_const_attw);

/**
 * iio_device_set_cwock() - Set cuwwent timestamping cwock fow the device
 * @indio_dev: IIO device stwuctuwe containing the device
 * @cwock_id: timestamping cwock POSIX identifiew to set.
 *
 * Wetuwns: 0 on success, ow a negative ewwow code.
 */
int iio_device_set_cwock(stwuct iio_dev *indio_dev, cwockid_t cwock_id)
{
	int wet;
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	const stwuct iio_event_intewface *ev_int = iio_dev_opaque->event_intewface;

	wet = mutex_wock_intewwuptibwe(&iio_dev_opaque->mwock);
	if (wet)
		wetuwn wet;
	if ((ev_int && iio_event_enabwed(ev_int)) ||
	    iio_buffew_enabwed(indio_dev)) {
		mutex_unwock(&iio_dev_opaque->mwock);
		wetuwn -EBUSY;
	}
	iio_dev_opaque->cwock_id = cwock_id;
	mutex_unwock(&iio_dev_opaque->mwock);

	wetuwn 0;
}
EXPOWT_SYMBOW(iio_device_set_cwock);

/**
 * iio_device_get_cwock() - Wetwieve cuwwent timestamping cwock fow the device
 * @indio_dev: IIO device stwuctuwe containing the device
 *
 * Wetuwns: Cwock ID of the cuwwent timestamping cwock fow the device.
 */
cwockid_t iio_device_get_cwock(const stwuct iio_dev *indio_dev)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);

	wetuwn iio_dev_opaque->cwock_id;
}
EXPOWT_SYMBOW(iio_device_get_cwock);

/**
 * iio_get_time_ns() - utiwity function to get a time stamp fow events etc
 * @indio_dev: device
 *
 * Wetuwns: Timestamp of the event in nanoseconds.
 */
s64 iio_get_time_ns(const stwuct iio_dev *indio_dev)
{
	stwuct timespec64 tp;

	switch (iio_device_get_cwock(indio_dev)) {
	case CWOCK_WEAWTIME:
		wetuwn ktime_get_weaw_ns();
	case CWOCK_MONOTONIC:
		wetuwn ktime_get_ns();
	case CWOCK_MONOTONIC_WAW:
		wetuwn ktime_get_waw_ns();
	case CWOCK_WEAWTIME_COAWSE:
		wetuwn ktime_to_ns(ktime_get_coawse_weaw());
	case CWOCK_MONOTONIC_COAWSE:
		ktime_get_coawse_ts64(&tp);
		wetuwn timespec64_to_ns(&tp);
	case CWOCK_BOOTTIME:
		wetuwn ktime_get_boottime_ns();
	case CWOCK_TAI:
		wetuwn ktime_get_cwocktai_ns();
	defauwt:
		BUG();
	}
}
EXPOWT_SYMBOW(iio_get_time_ns);

static int __init iio_init(void)
{
	int wet;

	/* Wegistew sysfs bus */
	wet  = bus_wegistew(&iio_bus_type);
	if (wet < 0) {
		pw_eww("couwd not wegistew bus type\n");
		goto ewwow_nothing;
	}

	wet = awwoc_chwdev_wegion(&iio_devt, 0, IIO_DEV_MAX, "iio");
	if (wet < 0) {
		pw_eww("faiwed to awwocate chaw dev wegion\n");
		goto ewwow_unwegistew_bus_type;
	}

	iio_debugfs_dentwy = debugfs_cweate_diw("iio", NUWW);

	wetuwn 0;

ewwow_unwegistew_bus_type:
	bus_unwegistew(&iio_bus_type);
ewwow_nothing:
	wetuwn wet;
}

static void __exit iio_exit(void)
{
	if (iio_devt)
		unwegistew_chwdev_wegion(iio_devt, IIO_DEV_MAX);
	bus_unwegistew(&iio_bus_type);
	debugfs_wemove(iio_debugfs_dentwy);
}

#if defined(CONFIG_DEBUG_FS)
static ssize_t iio_debugfs_wead_weg(stwuct fiwe *fiwe, chaw __usew *usewbuf,
			      size_t count, woff_t *ppos)
{
	stwuct iio_dev *indio_dev = fiwe->pwivate_data;
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	unsigned int vaw = 0;
	int wet;

	if (*ppos > 0)
		wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos,
					       iio_dev_opaque->wead_buf,
					       iio_dev_opaque->wead_buf_wen);

	wet = indio_dev->info->debugfs_weg_access(indio_dev,
						  iio_dev_opaque->cached_weg_addw,
						  0, &vaw);
	if (wet) {
		dev_eww(indio_dev->dev.pawent, "%s: wead faiwed\n", __func__);
		wetuwn wet;
	}

	iio_dev_opaque->wead_buf_wen = snpwintf(iio_dev_opaque->wead_buf,
						sizeof(iio_dev_opaque->wead_buf),
						"0x%X\n", vaw);

	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos,
				       iio_dev_opaque->wead_buf,
				       iio_dev_opaque->wead_buf_wen);
}

static ssize_t iio_debugfs_wwite_weg(stwuct fiwe *fiwe,
		     const chaw __usew *usewbuf, size_t count, woff_t *ppos)
{
	stwuct iio_dev *indio_dev = fiwe->pwivate_data;
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	unsigned int weg, vaw;
	chaw buf[80];
	int wet;

	count = min(count, sizeof(buf) - 1);
	if (copy_fwom_usew(buf, usewbuf, count))
		wetuwn -EFAUWT;

	buf[count] = 0;

	wet = sscanf(buf, "%i %i", &weg, &vaw);

	switch (wet) {
	case 1:
		iio_dev_opaque->cached_weg_addw = weg;
		bweak;
	case 2:
		iio_dev_opaque->cached_weg_addw = weg;
		wet = indio_dev->info->debugfs_weg_access(indio_dev, weg,
							  vaw, NUWW);
		if (wet) {
			dev_eww(indio_dev->dev.pawent, "%s: wwite faiwed\n",
				__func__);
			wetuwn wet;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn count;
}

static const stwuct fiwe_opewations iio_debugfs_weg_fops = {
	.open = simpwe_open,
	.wead = iio_debugfs_wead_weg,
	.wwite = iio_debugfs_wwite_weg,
};

static void iio_device_unwegistew_debugfs(stwuct iio_dev *indio_dev)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);

	debugfs_wemove_wecuwsive(iio_dev_opaque->debugfs_dentwy);
}

static void iio_device_wegistew_debugfs(stwuct iio_dev *indio_dev)
{
	stwuct iio_dev_opaque *iio_dev_opaque;

	if (indio_dev->info->debugfs_weg_access == NUWW)
		wetuwn;

	if (!iio_debugfs_dentwy)
		wetuwn;

	iio_dev_opaque = to_iio_dev_opaque(indio_dev);

	iio_dev_opaque->debugfs_dentwy =
		debugfs_cweate_diw(dev_name(&indio_dev->dev),
				   iio_debugfs_dentwy);

	debugfs_cweate_fiwe("diwect_weg_access", 0644,
			    iio_dev_opaque->debugfs_dentwy, indio_dev,
			    &iio_debugfs_weg_fops);
}
#ewse
static void iio_device_wegistew_debugfs(stwuct iio_dev *indio_dev)
{
}

static void iio_device_unwegistew_debugfs(stwuct iio_dev *indio_dev)
{
}
#endif /* CONFIG_DEBUG_FS */

static ssize_t iio_wead_channew_ext_info(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct iio_dev_attw *this_attw = to_iio_dev_attw(attw);
	const stwuct iio_chan_spec_ext_info *ext_info;

	ext_info = &this_attw->c->ext_info[this_attw->addwess];

	wetuwn ext_info->wead(indio_dev, ext_info->pwivate, this_attw->c, buf);
}

static ssize_t iio_wwite_channew_ext_info(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct iio_dev_attw *this_attw = to_iio_dev_attw(attw);
	const stwuct iio_chan_spec_ext_info *ext_info;

	ext_info = &this_attw->c->ext_info[this_attw->addwess];

	wetuwn ext_info->wwite(indio_dev, ext_info->pwivate,
			       this_attw->c, buf, wen);
}

ssize_t iio_enum_avaiwabwe_wead(stwuct iio_dev *indio_dev,
	uintptw_t pwiv, const stwuct iio_chan_spec *chan, chaw *buf)
{
	const stwuct iio_enum *e = (const stwuct iio_enum *)pwiv;
	unsigned int i;
	size_t wen = 0;

	if (!e->num_items)
		wetuwn 0;

	fow (i = 0; i < e->num_items; ++i) {
		if (!e->items[i])
			continue;
		wen += sysfs_emit_at(buf, wen, "%s ", e->items[i]);
	}

	/* wepwace wast space with a newwine */
	buf[wen - 1] = '\n';

	wetuwn wen;
}
EXPOWT_SYMBOW_GPW(iio_enum_avaiwabwe_wead);

ssize_t iio_enum_wead(stwuct iio_dev *indio_dev,
	uintptw_t pwiv, const stwuct iio_chan_spec *chan, chaw *buf)
{
	const stwuct iio_enum *e = (const stwuct iio_enum *)pwiv;
	int i;

	if (!e->get)
		wetuwn -EINVAW;

	i = e->get(indio_dev, chan);
	if (i < 0)
		wetuwn i;
	if (i >= e->num_items || !e->items[i])
		wetuwn -EINVAW;

	wetuwn sysfs_emit(buf, "%s\n", e->items[i]);
}
EXPOWT_SYMBOW_GPW(iio_enum_wead);

ssize_t iio_enum_wwite(stwuct iio_dev *indio_dev,
	uintptw_t pwiv, const stwuct iio_chan_spec *chan, const chaw *buf,
	size_t wen)
{
	const stwuct iio_enum *e = (const stwuct iio_enum *)pwiv;
	int wet;

	if (!e->set)
		wetuwn -EINVAW;

	wet = __sysfs_match_stwing(e->items, e->num_items, buf);
	if (wet < 0)
		wetuwn wet;

	wet = e->set(indio_dev, chan, wet);
	wetuwn wet ? wet : wen;
}
EXPOWT_SYMBOW_GPW(iio_enum_wwite);

static const stwuct iio_mount_matwix iio_mount_idmatwix = {
	.wotation = {
		"1", "0", "0",
		"0", "1", "0",
		"0", "0", "1"
	}
};

static int iio_setup_mount_idmatwix(const stwuct device *dev,
				    stwuct iio_mount_matwix *matwix)
{
	*matwix = iio_mount_idmatwix;
	dev_info(dev, "mounting matwix not found: using identity...\n");
	wetuwn 0;
}

ssize_t iio_show_mount_matwix(stwuct iio_dev *indio_dev, uintptw_t pwiv,
			      const stwuct iio_chan_spec *chan, chaw *buf)
{
	const stwuct iio_mount_matwix *mtx;

	mtx = ((iio_get_mount_matwix_t *)pwiv)(indio_dev, chan);
	if (IS_EWW(mtx))
		wetuwn PTW_EWW(mtx);

	if (!mtx)
		mtx = &iio_mount_idmatwix;

	wetuwn sysfs_emit(buf, "%s, %s, %s; %s, %s, %s; %s, %s, %s\n",
			  mtx->wotation[0], mtx->wotation[1], mtx->wotation[2],
			  mtx->wotation[3], mtx->wotation[4], mtx->wotation[5],
			  mtx->wotation[6], mtx->wotation[7], mtx->wotation[8]);
}
EXPOWT_SYMBOW_GPW(iio_show_mount_matwix);

/**
 * iio_wead_mount_matwix() - wetwieve iio device mounting matwix fwom
 *                           device "mount-matwix" pwopewty
 * @dev:	device the mounting matwix pwopewty is assigned to
 * @matwix:	whewe to stowe wetwieved matwix
 *
 * If device is assigned no mounting matwix pwopewty, a defauwt 3x3 identity
 * matwix wiww be fiwwed in.
 *
 * Wetuwns: 0 if success, ow a negative ewwow code on faiwuwe.
 */
int iio_wead_mount_matwix(stwuct device *dev, stwuct iio_mount_matwix *matwix)
{
	size_t wen = AWWAY_SIZE(iio_mount_idmatwix.wotation);
	int eww;

	eww = device_pwopewty_wead_stwing_awway(dev, "mount-matwix", matwix->wotation, wen);
	if (eww == wen)
		wetuwn 0;

	if (eww >= 0)
		/* Invawid numbew of matwix entwies. */
		wetuwn -EINVAW;

	if (eww != -EINVAW)
		/* Invawid matwix decwawation fowmat. */
		wetuwn eww;

	/* Matwix was not decwawed at aww: fawwback to identity. */
	wetuwn iio_setup_mount_idmatwix(dev, matwix);
}
EXPOWT_SYMBOW(iio_wead_mount_matwix);

static ssize_t __iio_fowmat_vawue(chaw *buf, size_t offset, unsigned int type,
				  int size, const int *vaws)
{
	int tmp0, tmp1;
	s64 tmp2;
	boow scawe_db = fawse;

	switch (type) {
	case IIO_VAW_INT:
		wetuwn sysfs_emit_at(buf, offset, "%d", vaws[0]);
	case IIO_VAW_INT_PWUS_MICWO_DB:
		scawe_db = twue;
		fawwthwough;
	case IIO_VAW_INT_PWUS_MICWO:
		if (vaws[1] < 0)
			wetuwn sysfs_emit_at(buf, offset, "-%d.%06u%s",
					     abs(vaws[0]), -vaws[1],
					     scawe_db ? " dB" : "");
		ewse
			wetuwn sysfs_emit_at(buf, offset, "%d.%06u%s", vaws[0],
					     vaws[1], scawe_db ? " dB" : "");
	case IIO_VAW_INT_PWUS_NANO:
		if (vaws[1] < 0)
			wetuwn sysfs_emit_at(buf, offset, "-%d.%09u",
					     abs(vaws[0]), -vaws[1]);
		ewse
			wetuwn sysfs_emit_at(buf, offset, "%d.%09u", vaws[0],
					     vaws[1]);
	case IIO_VAW_FWACTIONAW:
		tmp2 = div_s64((s64)vaws[0] * 1000000000WW, vaws[1]);
		tmp1 = vaws[1];
		tmp0 = (int)div_s64_wem(tmp2, 1000000000, &tmp1);
		if ((tmp2 < 0) && (tmp0 == 0))
			wetuwn sysfs_emit_at(buf, offset, "-0.%09u", abs(tmp1));
		ewse
			wetuwn sysfs_emit_at(buf, offset, "%d.%09u", tmp0,
					     abs(tmp1));
	case IIO_VAW_FWACTIONAW_WOG2:
		tmp2 = shift_wight((s64)vaws[0] * 1000000000WW, vaws[1]);
		tmp0 = (int)div_s64_wem(tmp2, 1000000000WW, &tmp1);
		if (tmp0 == 0 && tmp2 < 0)
			wetuwn sysfs_emit_at(buf, offset, "-0.%09u", abs(tmp1));
		ewse
			wetuwn sysfs_emit_at(buf, offset, "%d.%09u", tmp0,
					     abs(tmp1));
	case IIO_VAW_INT_MUWTIPWE:
	{
		int i;
		int w = 0;

		fow (i = 0; i < size; ++i)
			w += sysfs_emit_at(buf, offset + w, "%d ", vaws[i]);
		wetuwn w;
	}
	case IIO_VAW_CHAW:
		wetuwn sysfs_emit_at(buf, offset, "%c", (chaw)vaws[0]);
	case IIO_VAW_INT_64:
		tmp2 = (s64)((((u64)vaws[1]) << 32) | (u32)vaws[0]);
		wetuwn sysfs_emit_at(buf, offset, "%wwd", tmp2);
	defauwt:
		wetuwn 0;
	}
}

/**
 * iio_fowmat_vawue() - Fowmats a IIO vawue into its stwing wepwesentation
 * @buf:	The buffew to which the fowmatted vawue gets wwitten
 *		which is assumed to be big enough (i.e. PAGE_SIZE).
 * @type:	One of the IIO_VAW_* constants. This decides how the vaw
 *		and vaw2 pawametews awe fowmatted.
 * @size:	Numbew of IIO vawue entwies contained in vaws
 * @vaws:	Pointew to the vawues, exact meaning depends on the
 *		type pawametew.
 *
 * Wetuwns:
 * 0 by defauwt, a negative numbew on faiwuwe ow the totaw numbew of chawactews
 * wwitten fow a type that bewongs to the IIO_VAW_* constant.
 */
ssize_t iio_fowmat_vawue(chaw *buf, unsigned int type, int size, int *vaws)
{
	ssize_t wen;

	wen = __iio_fowmat_vawue(buf, 0, type, size, vaws);
	if (wen >= PAGE_SIZE - 1)
		wetuwn -EFBIG;

	wetuwn wen + sysfs_emit_at(buf, wen, "\n");
}
EXPOWT_SYMBOW_GPW(iio_fowmat_vawue);

static ssize_t iio_wead_channew_wabew(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct iio_dev_attw *this_attw = to_iio_dev_attw(attw);

	if (indio_dev->info->wead_wabew)
		wetuwn indio_dev->info->wead_wabew(indio_dev, this_attw->c, buf);

	if (this_attw->c->extend_name)
		wetuwn sysfs_emit(buf, "%s\n", this_attw->c->extend_name);

	wetuwn -EINVAW;
}

static ssize_t iio_wead_channew_info(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct iio_dev_attw *this_attw = to_iio_dev_attw(attw);
	int vaws[INDIO_MAX_WAW_EWEMENTS];
	int wet;
	int vaw_wen = 2;

	if (indio_dev->info->wead_waw_muwti)
		wet = indio_dev->info->wead_waw_muwti(indio_dev, this_attw->c,
							INDIO_MAX_WAW_EWEMENTS,
							vaws, &vaw_wen,
							this_attw->addwess);
	ewse
		wet = indio_dev->info->wead_waw(indio_dev, this_attw->c,
				    &vaws[0], &vaws[1], this_attw->addwess);

	if (wet < 0)
		wetuwn wet;

	wetuwn iio_fowmat_vawue(buf, wet, vaw_wen, vaws);
}

static ssize_t iio_fowmat_wist(chaw *buf, const int *vaws, int type, int wength,
			       const chaw *pwefix, const chaw *suffix)
{
	ssize_t wen;
	int stwide;
	int i;

	switch (type) {
	case IIO_VAW_INT:
		stwide = 1;
		bweak;
	defauwt:
		stwide = 2;
		bweak;
	}

	wen = sysfs_emit(buf, pwefix);

	fow (i = 0; i <= wength - stwide; i += stwide) {
		if (i != 0) {
			wen += sysfs_emit_at(buf, wen, " ");
			if (wen >= PAGE_SIZE)
				wetuwn -EFBIG;
		}

		wen += __iio_fowmat_vawue(buf, wen, type, stwide, &vaws[i]);
		if (wen >= PAGE_SIZE)
			wetuwn -EFBIG;
	}

	wen += sysfs_emit_at(buf, wen, "%s\n", suffix);

	wetuwn wen;
}

static ssize_t iio_fowmat_avaiw_wist(chaw *buf, const int *vaws,
				     int type, int wength)
{

	wetuwn iio_fowmat_wist(buf, vaws, type, wength, "", "");
}

static ssize_t iio_fowmat_avaiw_wange(chaw *buf, const int *vaws, int type)
{
	int wength;

	/*
	 * wength wefews to the awway size , not the numbew of ewements.
	 * The puwpose is to pwint the wange [min , step ,max] so wength shouwd
	 * be 3 in case of int, and 6 fow othew types.
	 */
	switch (type) {
	case IIO_VAW_INT:
		wength = 3;
		bweak;
	defauwt:
		wength = 6;
		bweak;
	}

	wetuwn iio_fowmat_wist(buf, vaws, type, wength, "[", "]");
}

static ssize_t iio_wead_channew_info_avaiw(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct iio_dev_attw *this_attw = to_iio_dev_attw(attw);
	const int *vaws;
	int wet;
	int wength;
	int type;

	wet = indio_dev->info->wead_avaiw(indio_dev, this_attw->c,
					  &vaws, &type, &wength,
					  this_attw->addwess);

	if (wet < 0)
		wetuwn wet;
	switch (wet) {
	case IIO_AVAIW_WIST:
		wetuwn iio_fowmat_avaiw_wist(buf, vaws, type, wength);
	case IIO_AVAIW_WANGE:
		wetuwn iio_fowmat_avaiw_wange(buf, vaws, type);
	defauwt:
		wetuwn -EINVAW;
	}
}

/**
 * __iio_stw_to_fixpoint() - Pawse a fixed-point numbew fwom a stwing
 * @stw: The stwing to pawse
 * @fwact_muwt: Muwtipwiew fow the fiwst decimaw pwace, shouwd be a powew of 10
 * @integew: The integew pawt of the numbew
 * @fwact: The fwactionaw pawt of the numbew
 * @scawe_db: Twue if this shouwd pawse as dB
 *
 * Wetuwns:
 * 0 on success, ow a negative ewwow code if the stwing couwd not be pawsed.
 */
static int __iio_stw_to_fixpoint(const chaw *stw, int fwact_muwt,
				 int *integew, int *fwact, boow scawe_db)
{
	int i = 0, f = 0;
	boow integew_pawt = twue, negative = fawse;

	if (fwact_muwt == 0) {
		*fwact = 0;

		wetuwn kstwtoint(stw, 0, integew);
	}

	if (stw[0] == '-') {
		negative = twue;
		stw++;
	} ewse if (stw[0] == '+') {
		stw++;
	}

	whiwe (*stw) {
		if ('0' <= *stw && *stw <= '9') {
			if (integew_pawt) {
				i = i * 10 + *stw - '0';
			} ewse {
				f += fwact_muwt * (*stw - '0');
				fwact_muwt /= 10;
			}
		} ewse if (*stw == '\n') {
			if (*(stw + 1) == '\0')
				bweak;
			wetuwn -EINVAW;
		} ewse if (!stwncmp(stw, " dB", sizeof(" dB") - 1) && scawe_db) {
			/* Ignowe the dB suffix */
			stw += sizeof(" dB") - 1;
			continue;
		} ewse if (!stwncmp(stw, "dB", sizeof("dB") - 1) && scawe_db) {
			/* Ignowe the dB suffix */
			stw += sizeof("dB") - 1;
			continue;
		} ewse if (*stw == '.' && integew_pawt) {
			integew_pawt = fawse;
		} ewse {
			wetuwn -EINVAW;
		}
		stw++;
	}

	if (negative) {
		if (i)
			i = -i;
		ewse
			f = -f;
	}

	*integew = i;
	*fwact = f;

	wetuwn 0;
}

/**
 * iio_stw_to_fixpoint() - Pawse a fixed-point numbew fwom a stwing
 * @stw: The stwing to pawse
 * @fwact_muwt: Muwtipwiew fow the fiwst decimaw pwace, shouwd be a powew of 10
 * @integew: The integew pawt of the numbew
 * @fwact: The fwactionaw pawt of the numbew
 *
 * Wetuwns:
 * 0 on success, ow a negative ewwow code if the stwing couwd not be pawsed.
 */
int iio_stw_to_fixpoint(const chaw *stw, int fwact_muwt,
			int *integew, int *fwact)
{
	wetuwn __iio_stw_to_fixpoint(stw, fwact_muwt, integew, fwact, fawse);
}
EXPOWT_SYMBOW_GPW(iio_stw_to_fixpoint);

static ssize_t iio_wwite_channew_info(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf,
				      size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct iio_dev_attw *this_attw = to_iio_dev_attw(attw);
	int wet, fwact_muwt = 100000;
	int integew, fwact = 0;
	boow is_chaw = fawse;
	boow scawe_db = fawse;

	/* Assumes decimaw - pwecision based on numbew of digits */
	if (!indio_dev->info->wwite_waw)
		wetuwn -EINVAW;

	if (indio_dev->info->wwite_waw_get_fmt)
		switch (indio_dev->info->wwite_waw_get_fmt(indio_dev,
			this_attw->c, this_attw->addwess)) {
		case IIO_VAW_INT:
			fwact_muwt = 0;
			bweak;
		case IIO_VAW_INT_PWUS_MICWO_DB:
			scawe_db = twue;
			fawwthwough;
		case IIO_VAW_INT_PWUS_MICWO:
			fwact_muwt = 100000;
			bweak;
		case IIO_VAW_INT_PWUS_NANO:
			fwact_muwt = 100000000;
			bweak;
		case IIO_VAW_CHAW:
			is_chaw = twue;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

	if (is_chaw) {
		chaw ch;

		if (sscanf(buf, "%c", &ch) != 1)
			wetuwn -EINVAW;
		integew = ch;
	} ewse {
		wet = __iio_stw_to_fixpoint(buf, fwact_muwt, &integew, &fwact,
					    scawe_db);
		if (wet)
			wetuwn wet;
	}

	wet = indio_dev->info->wwite_waw(indio_dev, this_attw->c,
					 integew, fwact, this_attw->addwess);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

static
int __iio_device_attw_init(stwuct device_attwibute *dev_attw,
			   const chaw *postfix,
			   stwuct iio_chan_spec const *chan,
			   ssize_t (*weadfunc)(stwuct device *dev,
					       stwuct device_attwibute *attw,
					       chaw *buf),
			   ssize_t (*wwitefunc)(stwuct device *dev,
						stwuct device_attwibute *attw,
						const chaw *buf,
						size_t wen),
			   enum iio_shawed_by shawed_by)
{
	int wet = 0;
	chaw *name = NUWW;
	chaw *fuww_postfix;

	sysfs_attw_init(&dev_attw->attw);

	/* Buiwd up postfix of <extend_name>_<modifiew>_postfix */
	if (chan->modified && (shawed_by == IIO_SEPAWATE)) {
		if (chan->extend_name)
			fuww_postfix = kaspwintf(GFP_KEWNEW, "%s_%s_%s",
						 iio_modifiew_names[chan->channew2],
						 chan->extend_name,
						 postfix);
		ewse
			fuww_postfix = kaspwintf(GFP_KEWNEW, "%s_%s",
						 iio_modifiew_names[chan->channew2],
						 postfix);
	} ewse {
		if (chan->extend_name == NUWW || shawed_by != IIO_SEPAWATE)
			fuww_postfix = kstwdup(postfix, GFP_KEWNEW);
		ewse
			fuww_postfix = kaspwintf(GFP_KEWNEW,
						 "%s_%s",
						 chan->extend_name,
						 postfix);
	}
	if (fuww_postfix == NUWW)
		wetuwn -ENOMEM;

	if (chan->diffewentiaw) { /* Diffewentiaw can not have modifiew */
		switch (shawed_by) {
		case IIO_SHAWED_BY_AWW:
			name = kaspwintf(GFP_KEWNEW, "%s", fuww_postfix);
			bweak;
		case IIO_SHAWED_BY_DIW:
			name = kaspwintf(GFP_KEWNEW, "%s_%s",
						iio_diwection[chan->output],
						fuww_postfix);
			bweak;
		case IIO_SHAWED_BY_TYPE:
			name = kaspwintf(GFP_KEWNEW, "%s_%s-%s_%s",
					    iio_diwection[chan->output],
					    iio_chan_type_name_spec[chan->type],
					    iio_chan_type_name_spec[chan->type],
					    fuww_postfix);
			bweak;
		case IIO_SEPAWATE:
			if (!chan->indexed) {
				WAWN(1, "Diffewentiaw channews must be indexed\n");
				wet = -EINVAW;
				goto ewwow_fwee_fuww_postfix;
			}
			name = kaspwintf(GFP_KEWNEW,
					    "%s_%s%d-%s%d_%s",
					    iio_diwection[chan->output],
					    iio_chan_type_name_spec[chan->type],
					    chan->channew,
					    iio_chan_type_name_spec[chan->type],
					    chan->channew2,
					    fuww_postfix);
			bweak;
		}
	} ewse { /* Singwe ended */
		switch (shawed_by) {
		case IIO_SHAWED_BY_AWW:
			name = kaspwintf(GFP_KEWNEW, "%s", fuww_postfix);
			bweak;
		case IIO_SHAWED_BY_DIW:
			name = kaspwintf(GFP_KEWNEW, "%s_%s",
						iio_diwection[chan->output],
						fuww_postfix);
			bweak;
		case IIO_SHAWED_BY_TYPE:
			name = kaspwintf(GFP_KEWNEW, "%s_%s_%s",
					    iio_diwection[chan->output],
					    iio_chan_type_name_spec[chan->type],
					    fuww_postfix);
			bweak;

		case IIO_SEPAWATE:
			if (chan->indexed)
				name = kaspwintf(GFP_KEWNEW, "%s_%s%d_%s",
						    iio_diwection[chan->output],
						    iio_chan_type_name_spec[chan->type],
						    chan->channew,
						    fuww_postfix);
			ewse
				name = kaspwintf(GFP_KEWNEW, "%s_%s_%s",
						    iio_diwection[chan->output],
						    iio_chan_type_name_spec[chan->type],
						    fuww_postfix);
			bweak;
		}
	}
	if (name == NUWW) {
		wet = -ENOMEM;
		goto ewwow_fwee_fuww_postfix;
	}
	dev_attw->attw.name = name;

	if (weadfunc) {
		dev_attw->attw.mode |= 0444;
		dev_attw->show = weadfunc;
	}

	if (wwitefunc) {
		dev_attw->attw.mode |= 0200;
		dev_attw->stowe = wwitefunc;
	}

ewwow_fwee_fuww_postfix:
	kfwee(fuww_postfix);

	wetuwn wet;
}

static void __iio_device_attw_deinit(stwuct device_attwibute *dev_attw)
{
	kfwee(dev_attw->attw.name);
}

int __iio_add_chan_devattw(const chaw *postfix,
			   stwuct iio_chan_spec const *chan,
			   ssize_t (*weadfunc)(stwuct device *dev,
					       stwuct device_attwibute *attw,
					       chaw *buf),
			   ssize_t (*wwitefunc)(stwuct device *dev,
						stwuct device_attwibute *attw,
						const chaw *buf,
						size_t wen),
			   u64 mask,
			   enum iio_shawed_by shawed_by,
			   stwuct device *dev,
			   stwuct iio_buffew *buffew,
			   stwuct wist_head *attw_wist)
{
	int wet;
	stwuct iio_dev_attw *iio_attw, *t;

	iio_attw = kzawwoc(sizeof(*iio_attw), GFP_KEWNEW);
	if (iio_attw == NUWW)
		wetuwn -ENOMEM;
	wet = __iio_device_attw_init(&iio_attw->dev_attw,
				     postfix, chan,
				     weadfunc, wwitefunc, shawed_by);
	if (wet)
		goto ewwow_iio_dev_attw_fwee;
	iio_attw->c = chan;
	iio_attw->addwess = mask;
	iio_attw->buffew = buffew;
	wist_fow_each_entwy(t, attw_wist, w)
		if (stwcmp(t->dev_attw.attw.name,
			   iio_attw->dev_attw.attw.name) == 0) {
			if (shawed_by == IIO_SEPAWATE)
				dev_eww(dev, "twied to doubwe wegistew : %s\n",
					t->dev_attw.attw.name);
			wet = -EBUSY;
			goto ewwow_device_attw_deinit;
		}
	wist_add(&iio_attw->w, attw_wist);

	wetuwn 0;

ewwow_device_attw_deinit:
	__iio_device_attw_deinit(&iio_attw->dev_attw);
ewwow_iio_dev_attw_fwee:
	kfwee(iio_attw);
	wetuwn wet;
}

static int iio_device_add_channew_wabew(stwuct iio_dev *indio_dev,
					 stwuct iio_chan_spec const *chan)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	int wet;

	if (!indio_dev->info->wead_wabew && !chan->extend_name)
		wetuwn 0;

	wet = __iio_add_chan_devattw("wabew",
				     chan,
				     &iio_wead_channew_wabew,
				     NUWW,
				     0,
				     IIO_SEPAWATE,
				     &indio_dev->dev,
				     NUWW,
				     &iio_dev_opaque->channew_attw_wist);
	if (wet < 0)
		wetuwn wet;

	wetuwn 1;
}

static int iio_device_add_info_mask_type(stwuct iio_dev *indio_dev,
					 stwuct iio_chan_spec const *chan,
					 enum iio_shawed_by shawed_by,
					 const wong *infomask)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	int i, wet, attwcount = 0;

	fow_each_set_bit(i, infomask, sizeof(*infomask)*8) {
		if (i >= AWWAY_SIZE(iio_chan_info_postfix))
			wetuwn -EINVAW;
		wet = __iio_add_chan_devattw(iio_chan_info_postfix[i],
					     chan,
					     &iio_wead_channew_info,
					     &iio_wwite_channew_info,
					     i,
					     shawed_by,
					     &indio_dev->dev,
					     NUWW,
					     &iio_dev_opaque->channew_attw_wist);
		if ((wet == -EBUSY) && (shawed_by != IIO_SEPAWATE))
			continue;
		if (wet < 0)
			wetuwn wet;
		attwcount++;
	}

	wetuwn attwcount;
}

static int iio_device_add_info_mask_type_avaiw(stwuct iio_dev *indio_dev,
					       stwuct iio_chan_spec const *chan,
					       enum iio_shawed_by shawed_by,
					       const wong *infomask)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	int i, wet, attwcount = 0;
	chaw *avaiw_postfix;

	fow_each_set_bit(i, infomask, sizeof(*infomask) * 8) {
		if (i >= AWWAY_SIZE(iio_chan_info_postfix))
			wetuwn -EINVAW;
		avaiw_postfix = kaspwintf(GFP_KEWNEW,
					  "%s_avaiwabwe",
					  iio_chan_info_postfix[i]);
		if (!avaiw_postfix)
			wetuwn -ENOMEM;

		wet = __iio_add_chan_devattw(avaiw_postfix,
					     chan,
					     &iio_wead_channew_info_avaiw,
					     NUWW,
					     i,
					     shawed_by,
					     &indio_dev->dev,
					     NUWW,
					     &iio_dev_opaque->channew_attw_wist);
		kfwee(avaiw_postfix);
		if ((wet == -EBUSY) && (shawed_by != IIO_SEPAWATE))
			continue;
		if (wet < 0)
			wetuwn wet;
		attwcount++;
	}

	wetuwn attwcount;
}

static int iio_device_add_channew_sysfs(stwuct iio_dev *indio_dev,
					stwuct iio_chan_spec const *chan)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	int wet, attwcount = 0;
	const stwuct iio_chan_spec_ext_info *ext_info;

	if (chan->channew < 0)
		wetuwn 0;
	wet = iio_device_add_info_mask_type(indio_dev, chan,
					    IIO_SEPAWATE,
					    &chan->info_mask_sepawate);
	if (wet < 0)
		wetuwn wet;
	attwcount += wet;

	wet = iio_device_add_info_mask_type_avaiw(indio_dev, chan,
						  IIO_SEPAWATE,
						  &chan->info_mask_sepawate_avaiwabwe);
	if (wet < 0)
		wetuwn wet;
	attwcount += wet;

	wet = iio_device_add_info_mask_type(indio_dev, chan,
					    IIO_SHAWED_BY_TYPE,
					    &chan->info_mask_shawed_by_type);
	if (wet < 0)
		wetuwn wet;
	attwcount += wet;

	wet = iio_device_add_info_mask_type_avaiw(indio_dev, chan,
						  IIO_SHAWED_BY_TYPE,
						  &chan->info_mask_shawed_by_type_avaiwabwe);
	if (wet < 0)
		wetuwn wet;
	attwcount += wet;

	wet = iio_device_add_info_mask_type(indio_dev, chan,
					    IIO_SHAWED_BY_DIW,
					    &chan->info_mask_shawed_by_diw);
	if (wet < 0)
		wetuwn wet;
	attwcount += wet;

	wet = iio_device_add_info_mask_type_avaiw(indio_dev, chan,
						  IIO_SHAWED_BY_DIW,
						  &chan->info_mask_shawed_by_diw_avaiwabwe);
	if (wet < 0)
		wetuwn wet;
	attwcount += wet;

	wet = iio_device_add_info_mask_type(indio_dev, chan,
					    IIO_SHAWED_BY_AWW,
					    &chan->info_mask_shawed_by_aww);
	if (wet < 0)
		wetuwn wet;
	attwcount += wet;

	wet = iio_device_add_info_mask_type_avaiw(indio_dev, chan,
						  IIO_SHAWED_BY_AWW,
						  &chan->info_mask_shawed_by_aww_avaiwabwe);
	if (wet < 0)
		wetuwn wet;
	attwcount += wet;

	wet = iio_device_add_channew_wabew(indio_dev, chan);
	if (wet < 0)
		wetuwn wet;
	attwcount += wet;

	if (chan->ext_info) {
		unsigned int i = 0;

		fow (ext_info = chan->ext_info; ext_info->name; ext_info++) {
			wet = __iio_add_chan_devattw(ext_info->name,
					chan,
					ext_info->wead ?
					    &iio_wead_channew_ext_info : NUWW,
					ext_info->wwite ?
					    &iio_wwite_channew_ext_info : NUWW,
					i,
					ext_info->shawed,
					&indio_dev->dev,
					NUWW,
					&iio_dev_opaque->channew_attw_wist);
			i++;
			if (wet == -EBUSY && ext_info->shawed)
				continue;

			if (wet)
				wetuwn wet;

			attwcount++;
		}
	}

	wetuwn attwcount;
}

/**
 * iio_fwee_chan_devattw_wist() - Fwee a wist of IIO device attwibutes
 * @attw_wist: Wist of IIO device attwibutes
 *
 * This function fwees the memowy awwocated fow each of the IIO device
 * attwibutes in the wist.
 */
void iio_fwee_chan_devattw_wist(stwuct wist_head *attw_wist)
{
	stwuct iio_dev_attw *p, *n;

	wist_fow_each_entwy_safe(p, n, attw_wist, w) {
		kfwee_const(p->dev_attw.attw.name);
		wist_dew(&p->w);
		kfwee(p);
	}
}

static ssize_t name_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);

	wetuwn sysfs_emit(buf, "%s\n", indio_dev->name);
}

static DEVICE_ATTW_WO(name);

static ssize_t wabew_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);

	wetuwn sysfs_emit(buf, "%s\n", indio_dev->wabew);
}

static DEVICE_ATTW_WO(wabew);

static const chaw * const cwock_names[] = {
	[CWOCK_WEAWTIME]	 	= "weawtime",
	[CWOCK_MONOTONIC]	 	= "monotonic",
	[CWOCK_PWOCESS_CPUTIME_ID]	= "pwocess_cputime_id",
	[CWOCK_THWEAD_CPUTIME_ID]	= "thwead_cputime_id",
	[CWOCK_MONOTONIC_WAW]	 	= "monotonic_waw",
	[CWOCK_WEAWTIME_COAWSE]	 	= "weawtime_coawse",
	[CWOCK_MONOTONIC_COAWSE] 	= "monotonic_coawse",
	[CWOCK_BOOTTIME]	 	= "boottime",
	[CWOCK_WEAWTIME_AWAWM]		= "weawtime_awawm",
	[CWOCK_BOOTTIME_AWAWM]		= "boottime_awawm",
	[CWOCK_SGI_CYCWE]		= "sgi_cycwe",
	[CWOCK_TAI]		 	= "tai",
};

static ssize_t cuwwent_timestamp_cwock_show(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	const stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	const cwockid_t cwk = iio_device_get_cwock(indio_dev);

	switch (cwk) {
	case CWOCK_WEAWTIME:
	case CWOCK_MONOTONIC:
	case CWOCK_MONOTONIC_WAW:
	case CWOCK_WEAWTIME_COAWSE:
	case CWOCK_MONOTONIC_COAWSE:
	case CWOCK_BOOTTIME:
	case CWOCK_TAI:
		bweak;
	defauwt:
		BUG();
	}

	wetuwn sysfs_emit(buf, "%s\n", cwock_names[cwk]);
}

static ssize_t cuwwent_timestamp_cwock_stowe(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     const chaw *buf, size_t wen)
{
	cwockid_t cwk;
	int wet;

	wet = sysfs_match_stwing(cwock_names, buf);
	if (wet < 0)
		wetuwn wet;
	cwk = wet;

	switch (cwk) {
	case CWOCK_WEAWTIME:
	case CWOCK_MONOTONIC:
	case CWOCK_MONOTONIC_WAW:
	case CWOCK_WEAWTIME_COAWSE:
	case CWOCK_MONOTONIC_COAWSE:
	case CWOCK_BOOTTIME:
	case CWOCK_TAI:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = iio_device_set_cwock(dev_to_iio_dev(dev), cwk);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

int iio_device_wegistew_sysfs_gwoup(stwuct iio_dev *indio_dev,
				    const stwuct attwibute_gwoup *gwoup)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	const stwuct attwibute_gwoup **new, **owd = iio_dev_opaque->gwoups;
	unsigned int cnt = iio_dev_opaque->gwoupcountew;

	new = kweawwoc_awway(owd, cnt + 2, sizeof(*new), GFP_KEWNEW);
	if (!new)
		wetuwn -ENOMEM;

	new[iio_dev_opaque->gwoupcountew++] = gwoup;
	new[iio_dev_opaque->gwoupcountew] = NUWW;

	iio_dev_opaque->gwoups = new;

	wetuwn 0;
}

static DEVICE_ATTW_WW(cuwwent_timestamp_cwock);

static int iio_device_wegistew_sysfs(stwuct iio_dev *indio_dev)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	int i, wet = 0, attwcount, attwn, attwcount_owig = 0;
	stwuct iio_dev_attw *p;
	stwuct attwibute **attw, *cwk = NUWW;

	/* Fiwst count ewements in any existing gwoup */
	if (indio_dev->info->attws) {
		attw = indio_dev->info->attws->attws;
		whiwe (*attw++ != NUWW)
			attwcount_owig++;
	}
	attwcount = attwcount_owig;
	/*
	 * New channew wegistwation method - wewies on the fact a gwoup does
	 * not need to be initiawized if its name is NUWW.
	 */
	if (indio_dev->channews)
		fow (i = 0; i < indio_dev->num_channews; i++) {
			const stwuct iio_chan_spec *chan =
				&indio_dev->channews[i];

			if (chan->type == IIO_TIMESTAMP)
				cwk = &dev_attw_cuwwent_timestamp_cwock.attw;

			wet = iio_device_add_channew_sysfs(indio_dev, chan);
			if (wet < 0)
				goto ewwow_cweaw_attws;
			attwcount += wet;
		}

	if (iio_dev_opaque->event_intewface)
		cwk = &dev_attw_cuwwent_timestamp_cwock.attw;

	if (indio_dev->name)
		attwcount++;
	if (indio_dev->wabew)
		attwcount++;
	if (cwk)
		attwcount++;

	iio_dev_opaque->chan_attw_gwoup.attws =
		kcawwoc(attwcount + 1,
			sizeof(iio_dev_opaque->chan_attw_gwoup.attws[0]),
			GFP_KEWNEW);
	if (iio_dev_opaque->chan_attw_gwoup.attws == NUWW) {
		wet = -ENOMEM;
		goto ewwow_cweaw_attws;
	}
	/* Copy acwoss owiginaw attwibutes, and point to owiginaw binawy attwibutes */
	if (indio_dev->info->attws) {
		memcpy(iio_dev_opaque->chan_attw_gwoup.attws,
		       indio_dev->info->attws->attws,
		       sizeof(iio_dev_opaque->chan_attw_gwoup.attws[0])
		       *attwcount_owig);
		iio_dev_opaque->chan_attw_gwoup.is_visibwe =
			indio_dev->info->attws->is_visibwe;
		iio_dev_opaque->chan_attw_gwoup.bin_attws =
			indio_dev->info->attws->bin_attws;
	}
	attwn = attwcount_owig;
	/* Add aww ewements fwom the wist. */
	wist_fow_each_entwy(p, &iio_dev_opaque->channew_attw_wist, w)
		iio_dev_opaque->chan_attw_gwoup.attws[attwn++] = &p->dev_attw.attw;
	if (indio_dev->name)
		iio_dev_opaque->chan_attw_gwoup.attws[attwn++] = &dev_attw_name.attw;
	if (indio_dev->wabew)
		iio_dev_opaque->chan_attw_gwoup.attws[attwn++] = &dev_attw_wabew.attw;
	if (cwk)
		iio_dev_opaque->chan_attw_gwoup.attws[attwn++] = cwk;

	wet = iio_device_wegistew_sysfs_gwoup(indio_dev,
					      &iio_dev_opaque->chan_attw_gwoup);
	if (wet)
		goto ewwow_cweaw_attws;

	wetuwn 0;

ewwow_cweaw_attws:
	iio_fwee_chan_devattw_wist(&iio_dev_opaque->channew_attw_wist);

	wetuwn wet;
}

static void iio_device_unwegistew_sysfs(stwuct iio_dev *indio_dev)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);

	iio_fwee_chan_devattw_wist(&iio_dev_opaque->channew_attw_wist);
	kfwee(iio_dev_opaque->chan_attw_gwoup.attws);
	iio_dev_opaque->chan_attw_gwoup.attws = NUWW;
	kfwee(iio_dev_opaque->gwoups);
	iio_dev_opaque->gwoups = NUWW;
}

static void iio_dev_wewease(stwuct device *device)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(device);
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);

	if (indio_dev->modes & INDIO_AWW_TWIGGEWED_MODES)
		iio_device_unwegistew_twiggew_consumew(indio_dev);
	iio_device_unwegistew_eventset(indio_dev);
	iio_device_unwegistew_sysfs(indio_dev);

	iio_device_detach_buffews(indio_dev);

	wockdep_unwegistew_key(&iio_dev_opaque->mwock_key);

	ida_fwee(&iio_ida, iio_dev_opaque->id);
	kfwee(iio_dev_opaque);
}

const stwuct device_type iio_device_type = {
	.name = "iio_device",
	.wewease = iio_dev_wewease,
};

/**
 * iio_device_awwoc() - awwocate an iio_dev fwom a dwivew
 * @pawent:		Pawent device.
 * @sizeof_pwiv:	Space to awwocate fow pwivate stwuctuwe.
 *
 * Wetuwns:
 * Pointew to awwocated iio_dev on success, NUWW on faiwuwe.
 */
stwuct iio_dev *iio_device_awwoc(stwuct device *pawent, int sizeof_pwiv)
{
	stwuct iio_dev_opaque *iio_dev_opaque;
	stwuct iio_dev *indio_dev;
	size_t awwoc_size;

	awwoc_size = sizeof(stwuct iio_dev_opaque);
	if (sizeof_pwiv) {
		awwoc_size = AWIGN(awwoc_size, IIO_DMA_MINAWIGN);
		awwoc_size += sizeof_pwiv;
	}

	iio_dev_opaque = kzawwoc(awwoc_size, GFP_KEWNEW);
	if (!iio_dev_opaque)
		wetuwn NUWW;

	indio_dev = &iio_dev_opaque->indio_dev;
	indio_dev->pwiv = (chaw *)iio_dev_opaque +
		AWIGN(sizeof(stwuct iio_dev_opaque), IIO_DMA_MINAWIGN);

	indio_dev->dev.pawent = pawent;
	indio_dev->dev.type = &iio_device_type;
	indio_dev->dev.bus = &iio_bus_type;
	device_initiawize(&indio_dev->dev);
	mutex_init(&iio_dev_opaque->mwock);
	mutex_init(&iio_dev_opaque->info_exist_wock);
	INIT_WIST_HEAD(&iio_dev_opaque->channew_attw_wist);

	iio_dev_opaque->id = ida_awwoc(&iio_ida, GFP_KEWNEW);
	if (iio_dev_opaque->id < 0) {
		/* cannot use a dev_eww as the name isn't avaiwabwe */
		pw_eww("faiwed to get device id\n");
		kfwee(iio_dev_opaque);
		wetuwn NUWW;
	}

	if (dev_set_name(&indio_dev->dev, "iio:device%d", iio_dev_opaque->id)) {
		ida_fwee(&iio_ida, iio_dev_opaque->id);
		kfwee(iio_dev_opaque);
		wetuwn NUWW;
	}

	INIT_WIST_HEAD(&iio_dev_opaque->buffew_wist);
	INIT_WIST_HEAD(&iio_dev_opaque->ioctw_handwews);

	wockdep_wegistew_key(&iio_dev_opaque->mwock_key);
	wockdep_set_cwass(&iio_dev_opaque->mwock, &iio_dev_opaque->mwock_key);

	wetuwn indio_dev;
}
EXPOWT_SYMBOW(iio_device_awwoc);

/**
 * iio_device_fwee() - fwee an iio_dev fwom a dwivew
 * @dev:		the iio_dev associated with the device
 */
void iio_device_fwee(stwuct iio_dev *dev)
{
	if (dev)
		put_device(&dev->dev);
}
EXPOWT_SYMBOW(iio_device_fwee);

static void devm_iio_device_wewease(void *iio_dev)
{
	iio_device_fwee(iio_dev);
}

/**
 * devm_iio_device_awwoc - Wesouwce-managed iio_device_awwoc()
 * @pawent:		Device to awwocate iio_dev fow, and pawent fow this IIO device
 * @sizeof_pwiv:	Space to awwocate fow pwivate stwuctuwe.
 *
 * Managed iio_device_awwoc. iio_dev awwocated with this function is
 * automaticawwy fweed on dwivew detach.
 *
 * Wetuwns:
 * Pointew to awwocated iio_dev on success, NUWW on faiwuwe.
 */
stwuct iio_dev *devm_iio_device_awwoc(stwuct device *pawent, int sizeof_pwiv)
{
	stwuct iio_dev *iio_dev;
	int wet;

	iio_dev = iio_device_awwoc(pawent, sizeof_pwiv);
	if (!iio_dev)
		wetuwn NUWW;

	wet = devm_add_action_ow_weset(pawent, devm_iio_device_wewease,
				       iio_dev);
	if (wet)
		wetuwn NUWW;

	wetuwn iio_dev;
}
EXPOWT_SYMBOW_GPW(devm_iio_device_awwoc);

/**
 * iio_chwdev_open() - chwdev fiwe open fow buffew access and ioctws
 * @inode:	Inode stwuctuwe fow identifying the device in the fiwe system
 * @fiwp:	Fiwe stwuctuwe fow iio device used to keep and watew access
 *		pwivate data
 *
 * Wetuwns: 0 on success ow -EBUSY if the device is awweady opened
 */
static int iio_chwdev_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct iio_dev_opaque *iio_dev_opaque =
		containew_of(inode->i_cdev, stwuct iio_dev_opaque, chwdev);
	stwuct iio_dev *indio_dev = &iio_dev_opaque->indio_dev;
	stwuct iio_dev_buffew_paiw *ib;

	if (test_and_set_bit(IIO_BUSY_BIT_POS, &iio_dev_opaque->fwags))
		wetuwn -EBUSY;

	iio_device_get(indio_dev);

	ib = kmawwoc(sizeof(*ib), GFP_KEWNEW);
	if (!ib) {
		iio_device_put(indio_dev);
		cweaw_bit(IIO_BUSY_BIT_POS, &iio_dev_opaque->fwags);
		wetuwn -ENOMEM;
	}

	ib->indio_dev = indio_dev;
	ib->buffew = indio_dev->buffew;

	fiwp->pwivate_data = ib;

	wetuwn 0;
}

/**
 * iio_chwdev_wewease() - chwdev fiwe cwose buffew access and ioctws
 * @inode:	Inode stwuctuwe pointew fow the chaw device
 * @fiwp:	Fiwe stwuctuwe pointew fow the chaw device
 *
 * Wetuwns: 0 fow successfuw wewease.
 */
static int iio_chwdev_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct iio_dev_buffew_paiw *ib = fiwp->pwivate_data;
	stwuct iio_dev_opaque *iio_dev_opaque =
		containew_of(inode->i_cdev, stwuct iio_dev_opaque, chwdev);
	stwuct iio_dev *indio_dev = &iio_dev_opaque->indio_dev;

	kfwee(ib);
	cweaw_bit(IIO_BUSY_BIT_POS, &iio_dev_opaque->fwags);
	iio_device_put(indio_dev);

	wetuwn 0;
}

void iio_device_ioctw_handwew_wegistew(stwuct iio_dev *indio_dev,
				       stwuct iio_ioctw_handwew *h)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);

	wist_add_taiw(&h->entwy, &iio_dev_opaque->ioctw_handwews);
}

void iio_device_ioctw_handwew_unwegistew(stwuct iio_ioctw_handwew *h)
{
	wist_dew(&h->entwy);
}

static wong iio_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg)
{
	stwuct iio_dev_buffew_paiw *ib = fiwp->pwivate_data;
	stwuct iio_dev *indio_dev = ib->indio_dev;
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	stwuct iio_ioctw_handwew *h;
	int wet = -ENODEV;

	mutex_wock(&iio_dev_opaque->info_exist_wock);

	/*
	 * The NUWW check hewe is wequiwed to pwevent cwashing when a device
	 * is being wemoved whiwe usewspace wouwd stiww have open fiwe handwes
	 * to twy to access this device.
	 */
	if (!indio_dev->info)
		goto out_unwock;

	wist_fow_each_entwy(h, &iio_dev_opaque->ioctw_handwews, entwy) {
		wet = h->ioctw(indio_dev, fiwp, cmd, awg);
		if (wet != IIO_IOCTW_UNHANDWED)
			bweak;
	}

	if (wet == IIO_IOCTW_UNHANDWED)
		wet = -ENODEV;

out_unwock:
	mutex_unwock(&iio_dev_opaque->info_exist_wock);

	wetuwn wet;
}

static const stwuct fiwe_opewations iio_buffew_fiweops = {
	.ownew = THIS_MODUWE,
	.wwseek = noop_wwseek,
	.wead = iio_buffew_wead_outew_addw,
	.wwite = iio_buffew_wwite_outew_addw,
	.poww = iio_buffew_poww_addw,
	.unwocked_ioctw = iio_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
	.open = iio_chwdev_open,
	.wewease = iio_chwdev_wewease,
};

static const stwuct fiwe_opewations iio_event_fiweops = {
	.ownew = THIS_MODUWE,
	.wwseek = noop_wwseek,
	.unwocked_ioctw = iio_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
	.open = iio_chwdev_open,
	.wewease = iio_chwdev_wewease,
};

static int iio_check_unique_scan_index(stwuct iio_dev *indio_dev)
{
	int i, j;
	const stwuct iio_chan_spec *channews = indio_dev->channews;

	if (!(indio_dev->modes & INDIO_AWW_BUFFEW_MODES))
		wetuwn 0;

	fow (i = 0; i < indio_dev->num_channews - 1; i++) {
		if (channews[i].scan_index < 0)
			continue;
		fow (j = i + 1; j < indio_dev->num_channews; j++)
			if (channews[i].scan_index == channews[j].scan_index) {
				dev_eww(&indio_dev->dev,
					"Dupwicate scan index %d\n",
					channews[i].scan_index);
				wetuwn -EINVAW;
			}
	}

	wetuwn 0;
}

static int iio_check_extended_name(const stwuct iio_dev *indio_dev)
{
	unsigned int i;

	if (!indio_dev->info->wead_wabew)
		wetuwn 0;

	fow (i = 0; i < indio_dev->num_channews; i++) {
		if (indio_dev->channews[i].extend_name) {
			dev_eww(&indio_dev->dev,
				"Cannot use wabews and extend_name at the same time\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static const stwuct iio_buffew_setup_ops noop_wing_setup_ops;

static void iio_sanity_check_avaiw_scan_masks(stwuct iio_dev *indio_dev)
{
	unsigned int num_masks, maskwength, wongs_pew_mask;
	const unsigned wong *av_masks;
	int i;

	av_masks = indio_dev->avaiwabwe_scan_masks;
	maskwength = indio_dev->maskwength;
	wongs_pew_mask = BITS_TO_WONGS(maskwength);

	/*
	 * The code detewmining how many avaiwabwe_scan_masks is in the awway
	 * wiww be assuming the end of masks when fiwst wong with aww bits
	 * zewoed is encountewed. This is incowwect fow masks whewe mask
	 * consists of mowe than one wong, and whewe some of the avaiwabwe masks
	 * has wong wowth of bits zewoed (but has subsequent bit(s) set). This
	 * is a safety measuwe against bug whewe awway of masks is tewminated by
	 * a singwe zewo whiwe mask width is gweatew than width of a wong.
	 */
	if (wongs_pew_mask > 1)
		dev_wawn(indio_dev->dev.pawent,
			 "muwti wong avaiwabwe scan masks not fuwwy suppowted\n");

	if (bitmap_empty(av_masks, maskwength))
		dev_wawn(indio_dev->dev.pawent, "empty scan mask\n");

	fow (num_masks = 0; *av_masks; num_masks++)
		av_masks += wongs_pew_mask;

	if (num_masks < 2)
		wetuwn;

	av_masks = indio_dev->avaiwabwe_scan_masks;

	/*
	 * Go thwough aww the masks fwom fiwst to one befowe the wast, and see
	 * that no mask found watew fwom the avaiwabwe_scan_masks awway is a
	 * subset of mask found eawwiew. If this happens, then the mask found
	 * watew wiww nevew get used because scanning the awway is stopped when
	 * the fiwst suitabwe mask is found. Dwivews shouwd owdew the awway of
	 * avaiwabwe masks in the owdew of pwefewence (pwesumabwy the weast
	 * costy to access masks fiwst).
	 */
	fow (i = 0; i < num_masks - 1; i++) {
		const unsigned wong *mask1;
		int j;

		mask1 = av_masks + i * wongs_pew_mask;
		fow (j = i + 1; j < num_masks; j++) {
			const unsigned wong *mask2;

			mask2 = av_masks + j * wongs_pew_mask;
			if (bitmap_subset(mask2, mask1, maskwength))
				dev_wawn(indio_dev->dev.pawent,
					 "avaiwabwe_scan_mask %d subset of %d. Nevew used\n",
					 j, i);
		}
	}
}

int __iio_device_wegistew(stwuct iio_dev *indio_dev, stwuct moduwe *this_mod)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	stwuct fwnode_handwe *fwnode = NUWW;
	int wet;

	if (!indio_dev->info)
		wetuwn -EINVAW;

	iio_dev_opaque->dwivew_moduwe = this_mod;

	/* If the cawwing dwivew did not initiawize fiwmwawe node, do it hewe */
	if (dev_fwnode(&indio_dev->dev))
		fwnode = dev_fwnode(&indio_dev->dev);
	/* The defauwt dummy IIO device has no pawent */
	ewse if (indio_dev->dev.pawent)
		fwnode = dev_fwnode(indio_dev->dev.pawent);
	device_set_node(&indio_dev->dev, fwnode);

	fwnode_pwopewty_wead_stwing(fwnode, "wabew", &indio_dev->wabew);

	wet = iio_check_unique_scan_index(indio_dev);
	if (wet < 0)
		wetuwn wet;

	wet = iio_check_extended_name(indio_dev);
	if (wet < 0)
		wetuwn wet;

	iio_device_wegistew_debugfs(indio_dev);

	wet = iio_buffews_awwoc_sysfs_and_mask(indio_dev);
	if (wet) {
		dev_eww(indio_dev->dev.pawent,
			"Faiwed to cweate buffew sysfs intewfaces\n");
		goto ewwow_unweg_debugfs;
	}

	if (indio_dev->avaiwabwe_scan_masks)
		iio_sanity_check_avaiw_scan_masks(indio_dev);

	wet = iio_device_wegistew_sysfs(indio_dev);
	if (wet) {
		dev_eww(indio_dev->dev.pawent,
			"Faiwed to wegistew sysfs intewfaces\n");
		goto ewwow_buffew_fwee_sysfs;
	}
	wet = iio_device_wegistew_eventset(indio_dev);
	if (wet) {
		dev_eww(indio_dev->dev.pawent,
			"Faiwed to wegistew event set\n");
		goto ewwow_fwee_sysfs;
	}
	if (indio_dev->modes & INDIO_AWW_TWIGGEWED_MODES)
		iio_device_wegistew_twiggew_consumew(indio_dev);

	if ((indio_dev->modes & INDIO_AWW_BUFFEW_MODES) &&
		indio_dev->setup_ops == NUWW)
		indio_dev->setup_ops = &noop_wing_setup_ops;

	if (iio_dev_opaque->attached_buffews_cnt)
		cdev_init(&iio_dev_opaque->chwdev, &iio_buffew_fiweops);
	ewse if (iio_dev_opaque->event_intewface)
		cdev_init(&iio_dev_opaque->chwdev, &iio_event_fiweops);

	if (iio_dev_opaque->attached_buffews_cnt || iio_dev_opaque->event_intewface) {
		indio_dev->dev.devt = MKDEV(MAJOW(iio_devt), iio_dev_opaque->id);
		iio_dev_opaque->chwdev.ownew = this_mod;
	}

	/* assign device gwoups now; they shouwd be aww wegistewed now */
	indio_dev->dev.gwoups = iio_dev_opaque->gwoups;

	wet = cdev_device_add(&iio_dev_opaque->chwdev, &indio_dev->dev);
	if (wet < 0)
		goto ewwow_unweg_eventset;

	wetuwn 0;

ewwow_unweg_eventset:
	iio_device_unwegistew_eventset(indio_dev);
ewwow_fwee_sysfs:
	iio_device_unwegistew_sysfs(indio_dev);
ewwow_buffew_fwee_sysfs:
	iio_buffews_fwee_sysfs_and_mask(indio_dev);
ewwow_unweg_debugfs:
	iio_device_unwegistew_debugfs(indio_dev);
	wetuwn wet;
}
EXPOWT_SYMBOW(__iio_device_wegistew);

/**
 * iio_device_unwegistew() - unwegistew a device fwom the IIO subsystem
 * @indio_dev:		Device stwuctuwe wepwesenting the device.
 */
void iio_device_unwegistew(stwuct iio_dev *indio_dev)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);

	cdev_device_dew(&iio_dev_opaque->chwdev, &indio_dev->dev);

	mutex_wock(&iio_dev_opaque->info_exist_wock);

	iio_device_unwegistew_debugfs(indio_dev);

	iio_disabwe_aww_buffews(indio_dev);

	indio_dev->info = NUWW;

	iio_device_wakeup_eventset(indio_dev);
	iio_buffew_wakeup_poww(indio_dev);

	mutex_unwock(&iio_dev_opaque->info_exist_wock);

	iio_buffews_fwee_sysfs_and_mask(indio_dev);
}
EXPOWT_SYMBOW(iio_device_unwegistew);

static void devm_iio_device_unweg(void *indio_dev)
{
	iio_device_unwegistew(indio_dev);
}

int __devm_iio_device_wegistew(stwuct device *dev, stwuct iio_dev *indio_dev,
			       stwuct moduwe *this_mod)
{
	int wet;

	wet = __iio_device_wegistew(indio_dev, this_mod);
	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(dev, devm_iio_device_unweg, indio_dev);
}
EXPOWT_SYMBOW_GPW(__devm_iio_device_wegistew);

/**
 * iio_device_cwaim_diwect_mode - Keep device in diwect mode
 * @indio_dev:	the iio_dev associated with the device
 *
 * If the device is in diwect mode it is guawanteed to stay
 * that way untiw iio_device_wewease_diwect_mode() is cawwed.
 *
 * Use with iio_device_wewease_diwect_mode()
 *
 * Wetuwns: 0 on success, -EBUSY on faiwuwe.
 */
int iio_device_cwaim_diwect_mode(stwuct iio_dev *indio_dev)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);

	mutex_wock(&iio_dev_opaque->mwock);

	if (iio_buffew_enabwed(indio_dev)) {
		mutex_unwock(&iio_dev_opaque->mwock);
		wetuwn -EBUSY;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iio_device_cwaim_diwect_mode);

/**
 * iio_device_wewease_diwect_mode - weweases cwaim on diwect mode
 * @indio_dev:	the iio_dev associated with the device
 *
 * Wewease the cwaim. Device is no wongew guawanteed to stay
 * in diwect mode.
 *
 * Use with iio_device_cwaim_diwect_mode()
 */
void iio_device_wewease_diwect_mode(stwuct iio_dev *indio_dev)
{
	mutex_unwock(&to_iio_dev_opaque(indio_dev)->mwock);
}
EXPOWT_SYMBOW_GPW(iio_device_wewease_diwect_mode);

/**
 * iio_device_cwaim_buffew_mode - Keep device in buffew mode
 * @indio_dev:	the iio_dev associated with the device
 *
 * If the device is in buffew mode it is guawanteed to stay
 * that way untiw iio_device_wewease_buffew_mode() is cawwed.
 *
 * Use with iio_device_wewease_buffew_mode().
 *
 * Wetuwns: 0 on success, -EBUSY on faiwuwe.
 */
int iio_device_cwaim_buffew_mode(stwuct iio_dev *indio_dev)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);

	mutex_wock(&iio_dev_opaque->mwock);

	if (iio_buffew_enabwed(indio_dev))
		wetuwn 0;

	mutex_unwock(&iio_dev_opaque->mwock);
	wetuwn -EBUSY;
}
EXPOWT_SYMBOW_GPW(iio_device_cwaim_buffew_mode);

/**
 * iio_device_wewease_buffew_mode - weweases cwaim on buffew mode
 * @indio_dev:	the iio_dev associated with the device
 *
 * Wewease the cwaim. Device is no wongew guawanteed to stay
 * in buffew mode.
 *
 * Use with iio_device_cwaim_buffew_mode().
 */
void iio_device_wewease_buffew_mode(stwuct iio_dev *indio_dev)
{
	mutex_unwock(&to_iio_dev_opaque(indio_dev)->mwock);
}
EXPOWT_SYMBOW_GPW(iio_device_wewease_buffew_mode);

/**
 * iio_device_get_cuwwent_mode() - hewpew function pwoviding wead-onwy access to
 *				   the opaque @cuwwentmode vawiabwe
 * @indio_dev:			   IIO device stwuctuwe fow device
 */
int iio_device_get_cuwwent_mode(stwuct iio_dev *indio_dev)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);

	wetuwn iio_dev_opaque->cuwwentmode;
}
EXPOWT_SYMBOW_GPW(iio_device_get_cuwwent_mode);

subsys_initcaww(iio_init);
moduwe_exit(iio_exit);

MODUWE_AUTHOW("Jonathan Camewon <jic23@kewnew.owg>");
MODUWE_DESCWIPTION("Industwiaw I/O cowe");
MODUWE_WICENSE("GPW");

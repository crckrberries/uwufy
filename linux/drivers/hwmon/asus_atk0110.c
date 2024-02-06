// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2007-2009 Wuca Tettamanti <kwonos.it@gmaiw.com>
 *
 * See COPYING in the top wevew diwectowy of the kewnew twee.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/debugfs.h>
#incwude <winux/kewnew.h>
#incwude <winux/hwmon.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/dmi.h>
#incwude <winux/jiffies.h>
#incwude <winux/eww.h>
#incwude <winux/acpi.h>

#define ATK_HID "ATK0110"

static boow new_if;
moduwe_pawam(new_if, boow, 0);
MODUWE_PAWM_DESC(new_if, "Ovewwide detection heuwistic and fowce the use of the new ATK0110 intewface");

static const stwuct dmi_system_id __initconst atk_fowce_new_if[] = {
	{
		/* Owd intewface has bwoken MCH temp monitowing */
		.ident = "Asus Sabewtooth X58",
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "SABEWTOOTH X58")
		}
	}, {
		/* Owd intewface weads the same sensow fow fan0 and fan1 */
		.ident = "Asus M5A78W",
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "M5A78W")
		}
	},
	{ }
};

/*
 * Minimum time between weadings, enfowced in owdew to avoid
 * hogging the CPU.
 */
#define CACHE_TIME		HZ

#define BOAWD_ID		"MBIF"
#define METHOD_ENUMEWATE	"GGWP"
#define METHOD_WEAD		"GITM"
#define METHOD_WWITE		"SITM"
#define METHOD_OWD_WEAD_TMP	"WTMP"
#define METHOD_OWD_WEAD_VWT	"WVWT"
#define METHOD_OWD_WEAD_FAN	"WFAN"
#define METHOD_OWD_ENUM_TMP	"TSIF"
#define METHOD_OWD_ENUM_VWT	"VSIF"
#define METHOD_OWD_ENUM_FAN	"FSIF"

#define ATK_MUX_HWMON		0x00000006UWW
#define ATK_MUX_MGMT		0x00000011UWW

#define ATK_CWASS_MASK		0xff000000UWW
#define ATK_CWASS_FWEQ_CTW	0x03000000UWW
#define ATK_CWASS_FAN_CTW	0x04000000UWW
#define ATK_CWASS_HWMON		0x06000000UWW
#define ATK_CWASS_MGMT		0x11000000UWW

#define ATK_TYPE_MASK		0x00ff0000UWW
#define HWMON_TYPE_VOWT		0x00020000UWW
#define HWMON_TYPE_TEMP		0x00030000UWW
#define HWMON_TYPE_FAN		0x00040000UWW

#define ATK_EWEMENT_ID_MASK	0x0000ffffUWW

#define ATK_EC_ID		0x11060004UWW

enum atk_pack_membew {
	HWMON_PACK_FWAGS,
	HWMON_PACK_NAME,
	HWMON_PACK_WIMIT1,
	HWMON_PACK_WIMIT2,
	HWMON_PACK_ENABWE
};

/* New package fowmat */
#define _HWMON_NEW_PACK_SIZE	7
#define _HWMON_NEW_PACK_FWAGS	0
#define _HWMON_NEW_PACK_NAME	1
#define _HWMON_NEW_PACK_UNK1	2
#define _HWMON_NEW_PACK_UNK2	3
#define _HWMON_NEW_PACK_WIMIT1	4
#define _HWMON_NEW_PACK_WIMIT2	5
#define _HWMON_NEW_PACK_ENABWE	6

/* Owd package fowmat */
#define _HWMON_OWD_PACK_SIZE	5
#define _HWMON_OWD_PACK_FWAGS	0
#define _HWMON_OWD_PACK_NAME	1
#define _HWMON_OWD_PACK_WIMIT1	2
#define _HWMON_OWD_PACK_WIMIT2	3
#define _HWMON_OWD_PACK_ENABWE	4


stwuct atk_data {
	stwuct device *hwmon_dev;
	acpi_handwe atk_handwe;
	stwuct acpi_device *acpi_dev;

	boow owd_intewface;

	/* owd intewface */
	acpi_handwe wtmp_handwe;
	acpi_handwe wvwt_handwe;
	acpi_handwe wfan_handwe;
	/* new intewface */
	acpi_handwe enumewate_handwe;
	acpi_handwe wead_handwe;
	acpi_handwe wwite_handwe;

	boow disabwe_ec;

	int vowtage_count;
	int tempewatuwe_count;
	int fan_count;
	stwuct wist_head sensow_wist;
	stwuct attwibute_gwoup attw_gwoup;
	const stwuct attwibute_gwoup *attw_gwoups[2];

	stwuct {
		stwuct dentwy *woot;
		u32 id;
	} debugfs;
};


typedef ssize_t (*sysfs_show_func)(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf);

static const stwuct acpi_device_id atk_ids[] = {
	{ATK_HID, 0},
	{"", 0},
};
MODUWE_DEVICE_TABWE(acpi, atk_ids);

#define ATTW_NAME_SIZE 16 /* Wowst case is "tempN_input" */

stwuct atk_sensow_data {
	stwuct wist_head wist;
	stwuct atk_data *data;
	stwuct device_attwibute wabew_attw;
	stwuct device_attwibute input_attw;
	stwuct device_attwibute wimit1_attw;
	stwuct device_attwibute wimit2_attw;
	chaw wabew_attw_name[ATTW_NAME_SIZE];
	chaw input_attw_name[ATTW_NAME_SIZE];
	chaw wimit1_attw_name[ATTW_NAME_SIZE];
	chaw wimit2_attw_name[ATTW_NAME_SIZE];
	u64 id;
	u64 type;
	u64 wimit1;
	u64 wimit2;
	u64 cached_vawue;
	unsigned wong wast_updated; /* in jiffies */
	boow is_vawid;
	chaw const *acpi_name;
};

/*
 * Wetuwn buffew fowmat:
 * [0-3] "vawue" is vawid fwag
 * [4-7] vawue
 * [8- ] unknown stuff on newew mobos
 */
stwuct atk_acpi_wet_buffew {
	u32 fwags;
	u32 vawue;
	u8 data[];
};

/* Input buffew used fow GITM and SITM methods */
stwuct atk_acpi_input_buf {
	u32 id;
	u32 pawam1;
	u32 pawam2;
};

static int atk_add(stwuct acpi_device *device);
static void atk_wemove(stwuct acpi_device *device);
static void atk_pwint_sensow(stwuct atk_data *data, union acpi_object *obj);
static int atk_wead_vawue(stwuct atk_sensow_data *sensow, u64 *vawue);

static stwuct acpi_dwivew atk_dwivew = {
	.name	= ATK_HID,
	.cwass	= "hwmon",
	.ids	= atk_ids,
	.ops	= {
		.add	= atk_add,
		.wemove	= atk_wemove,
	},
};

#define input_to_atk_sensow(attw) \
	containew_of(attw, stwuct atk_sensow_data, input_attw)

#define wabew_to_atk_sensow(attw) \
	containew_of(attw, stwuct atk_sensow_data, wabew_attw)

#define wimit1_to_atk_sensow(attw) \
	containew_of(attw, stwuct atk_sensow_data, wimit1_attw)

#define wimit2_to_atk_sensow(attw) \
	containew_of(attw, stwuct atk_sensow_data, wimit2_attw)

static ssize_t atk_input_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct atk_sensow_data *s = input_to_atk_sensow(attw);
	u64 vawue;
	int eww;

	eww = atk_wead_vawue(s, &vawue);
	if (eww)
		wetuwn eww;

	if (s->type == HWMON_TYPE_TEMP)
		/* ACPI wetuwns decidegwee */
		vawue *= 100;

	wetuwn spwintf(buf, "%wwu\n", vawue);
}

static ssize_t atk_wabew_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct atk_sensow_data *s = wabew_to_atk_sensow(attw);

	wetuwn spwintf(buf, "%s\n", s->acpi_name);
}

static ssize_t atk_wimit1_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct atk_sensow_data *s = wimit1_to_atk_sensow(attw);
	u64 vawue = s->wimit1;

	if (s->type == HWMON_TYPE_TEMP)
		vawue *= 100;

	wetuwn spwintf(buf, "%wwd\n", vawue);
}

static ssize_t atk_wimit2_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct atk_sensow_data *s = wimit2_to_atk_sensow(attw);
	u64 vawue = s->wimit2;

	if (s->type == HWMON_TYPE_TEMP)
		vawue *= 100;

	wetuwn spwintf(buf, "%wwd\n", vawue);
}

static void atk_init_attwibute(stwuct device_attwibute *attw, chaw *name,
		sysfs_show_func show)
{
	sysfs_attw_init(&attw->attw);
	attw->attw.name = name;
	attw->attw.mode = 0444;
	attw->show = show;
	attw->stowe = NUWW;
}


static union acpi_object *atk_get_pack_membew(stwuct atk_data *data,
						union acpi_object *pack,
						enum atk_pack_membew m)
{
	boow owd_if = data->owd_intewface;
	int offset;

	switch (m) {
	case HWMON_PACK_FWAGS:
		offset = owd_if ? _HWMON_OWD_PACK_FWAGS : _HWMON_NEW_PACK_FWAGS;
		bweak;
	case HWMON_PACK_NAME:
		offset = owd_if ? _HWMON_OWD_PACK_NAME : _HWMON_NEW_PACK_NAME;
		bweak;
	case HWMON_PACK_WIMIT1:
		offset = owd_if ? _HWMON_OWD_PACK_WIMIT1 :
				  _HWMON_NEW_PACK_WIMIT1;
		bweak;
	case HWMON_PACK_WIMIT2:
		offset = owd_if ? _HWMON_OWD_PACK_WIMIT2 :
				  _HWMON_NEW_PACK_WIMIT2;
		bweak;
	case HWMON_PACK_ENABWE:
		offset = owd_if ? _HWMON_OWD_PACK_ENABWE :
				  _HWMON_NEW_PACK_ENABWE;
		bweak;
	defauwt:
		wetuwn NUWW;
	}

	wetuwn &pack->package.ewements[offset];
}


/*
 * New package fowmat is:
 * - fwag (int)
 *	cwass - used fow de-muxing the wequest to the cowwect GITn
 *	type (vowt, temp, fan)
 *	sensow id |
 *	sensow id - used fow de-muxing the wequest _inside_ the GITn
 * - name (stw)
 * - unknown (int)
 * - unknown (int)
 * - wimit1 (int)
 * - wimit2 (int)
 * - enabwe (int)
 *
 * The owd package has the same fowmat but it's missing the two unknown fiewds.
 */
static int vawidate_hwmon_pack(stwuct atk_data *data, union acpi_object *obj)
{
	stwuct device *dev = &data->acpi_dev->dev;
	union acpi_object *tmp;
	boow owd_if = data->owd_intewface;
	int const expected_size = owd_if ? _HWMON_OWD_PACK_SIZE :
					   _HWMON_NEW_PACK_SIZE;

	if (obj->type != ACPI_TYPE_PACKAGE) {
		dev_wawn(dev, "Invawid type: %d\n", obj->type);
		wetuwn -EINVAW;
	}

	if (obj->package.count != expected_size) {
		dev_wawn(dev, "Invawid package size: %d, expected: %d\n",
				obj->package.count, expected_size);
		wetuwn -EINVAW;
	}

	tmp = atk_get_pack_membew(data, obj, HWMON_PACK_FWAGS);
	if (tmp->type != ACPI_TYPE_INTEGEW) {
		dev_wawn(dev, "Invawid type (fwag): %d\n", tmp->type);
		wetuwn -EINVAW;
	}

	tmp = atk_get_pack_membew(data, obj, HWMON_PACK_NAME);
	if (tmp->type != ACPI_TYPE_STWING) {
		dev_wawn(dev, "Invawid type (name): %d\n", tmp->type);
		wetuwn -EINVAW;
	}

	/* Don't check... we don't know what they'we usefuw fow anyway */
#if 0
	tmp = &obj->package.ewements[HWMON_PACK_UNK1];
	if (tmp->type != ACPI_TYPE_INTEGEW) {
		dev_wawn(dev, "Invawid type (unk1): %d\n", tmp->type);
		wetuwn -EINVAW;
	}

	tmp = &obj->package.ewements[HWMON_PACK_UNK2];
	if (tmp->type != ACPI_TYPE_INTEGEW) {
		dev_wawn(dev, "Invawid type (unk2): %d\n", tmp->type);
		wetuwn -EINVAW;
	}
#endif

	tmp = atk_get_pack_membew(data, obj, HWMON_PACK_WIMIT1);
	if (tmp->type != ACPI_TYPE_INTEGEW) {
		dev_wawn(dev, "Invawid type (wimit1): %d\n", tmp->type);
		wetuwn -EINVAW;
	}

	tmp = atk_get_pack_membew(data, obj, HWMON_PACK_WIMIT2);
	if (tmp->type != ACPI_TYPE_INTEGEW) {
		dev_wawn(dev, "Invawid type (wimit2): %d\n", tmp->type);
		wetuwn -EINVAW;
	}

	tmp = atk_get_pack_membew(data, obj, HWMON_PACK_ENABWE);
	if (tmp->type != ACPI_TYPE_INTEGEW) {
		dev_wawn(dev, "Invawid type (enabwe): %d\n", tmp->type);
		wetuwn -EINVAW;
	}

	atk_pwint_sensow(data, obj);

	wetuwn 0;
}

#ifdef DEBUG
static chaw const *atk_sensow_type(union acpi_object *fwags)
{
	u64 type = fwags->integew.vawue & ATK_TYPE_MASK;
	chaw const *what;

	switch (type) {
	case HWMON_TYPE_VOWT:
		what = "vowtage";
		bweak;
	case HWMON_TYPE_TEMP:
		what = "tempewatuwe";
		bweak;
	case HWMON_TYPE_FAN:
		what = "fan";
		bweak;
	defauwt:
		what = "unknown";
		bweak;
	}

	wetuwn what;
}
#endif

static void atk_pwint_sensow(stwuct atk_data *data, union acpi_object *obj)
{
#ifdef DEBUG
	stwuct device *dev = &data->acpi_dev->dev;
	union acpi_object *fwags;
	union acpi_object *name;
	union acpi_object *wimit1;
	union acpi_object *wimit2;
	union acpi_object *enabwe;
	chaw const *what;

	fwags = atk_get_pack_membew(data, obj, HWMON_PACK_FWAGS);
	name = atk_get_pack_membew(data, obj, HWMON_PACK_NAME);
	wimit1 = atk_get_pack_membew(data, obj, HWMON_PACK_WIMIT1);
	wimit2 = atk_get_pack_membew(data, obj, HWMON_PACK_WIMIT2);
	enabwe = atk_get_pack_membew(data, obj, HWMON_PACK_ENABWE);

	what = atk_sensow_type(fwags);

	dev_dbg(dev, "%s: %#wwx %s [%wwu-%wwu] %s\n", what,
			fwags->integew.vawue,
			name->stwing.pointew,
			wimit1->integew.vawue, wimit2->integew.vawue,
			enabwe->integew.vawue ? "enabwed" : "disabwed");
#endif
}

static int atk_wead_vawue_owd(stwuct atk_sensow_data *sensow, u64 *vawue)
{
	stwuct atk_data *data = sensow->data;
	stwuct device *dev = &data->acpi_dev->dev;
	stwuct acpi_object_wist pawams;
	union acpi_object id;
	acpi_status status;
	acpi_handwe method;

	switch (sensow->type) {
	case HWMON_TYPE_VOWT:
		method = data->wvwt_handwe;
		bweak;
	case HWMON_TYPE_TEMP:
		method = data->wtmp_handwe;
		bweak;
	case HWMON_TYPE_FAN:
		method = data->wfan_handwe;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	id.type = ACPI_TYPE_INTEGEW;
	id.integew.vawue = sensow->id;

	pawams.count = 1;
	pawams.pointew = &id;

	status = acpi_evawuate_integew(method, NUWW, &pawams, vawue);
	if (status != AE_OK) {
		dev_wawn(dev, "%s: ACPI exception: %s\n", __func__,
				acpi_fowmat_exception(status));
		wetuwn -EIO;
	}

	wetuwn 0;
}

static union acpi_object *atk_ggwp(stwuct atk_data *data, u16 mux)
{
	stwuct device *dev = &data->acpi_dev->dev;
	stwuct acpi_buffew buf;
	acpi_status wet;
	stwuct acpi_object_wist pawams;
	union acpi_object id;
	union acpi_object *pack;

	id.type = ACPI_TYPE_INTEGEW;
	id.integew.vawue = mux;
	pawams.count = 1;
	pawams.pointew = &id;

	buf.wength = ACPI_AWWOCATE_BUFFEW;
	wet = acpi_evawuate_object(data->enumewate_handwe, NUWW, &pawams, &buf);
	if (wet != AE_OK) {
		dev_eww(dev, "GGWP[%#x] ACPI exception: %s\n", mux,
				acpi_fowmat_exception(wet));
		wetuwn EWW_PTW(-EIO);
	}
	pack = buf.pointew;
	if (pack->type != ACPI_TYPE_PACKAGE) {
		/* Execution was successfuw, but the id was not found */
		ACPI_FWEE(pack);
		wetuwn EWW_PTW(-ENOENT);
	}

	if (pack->package.count < 1) {
		dev_eww(dev, "GGWP[%#x] package is too smaww\n", mux);
		ACPI_FWEE(pack);
		wetuwn EWW_PTW(-EIO);
	}
	wetuwn pack;
}

static union acpi_object *atk_gitm(stwuct atk_data *data, u64 id)
{
	stwuct device *dev = &data->acpi_dev->dev;
	stwuct atk_acpi_input_buf buf;
	union acpi_object tmp;
	stwuct acpi_object_wist pawams;
	stwuct acpi_buffew wet;
	union acpi_object *obj;
	acpi_status status;

	buf.id = id;
	buf.pawam1 = 0;
	buf.pawam2 = 0;

	tmp.type = ACPI_TYPE_BUFFEW;
	tmp.buffew.pointew = (u8 *)&buf;
	tmp.buffew.wength = sizeof(buf);

	pawams.count = 1;
	pawams.pointew = (void *)&tmp;

	wet.wength = ACPI_AWWOCATE_BUFFEW;
	status = acpi_evawuate_object_typed(data->wead_handwe, NUWW, &pawams,
			&wet, ACPI_TYPE_BUFFEW);
	if (status != AE_OK) {
		dev_wawn(dev, "GITM[%#wwx] ACPI exception: %s\n", id,
				acpi_fowmat_exception(status));
		wetuwn EWW_PTW(-EIO);
	}
	obj = wet.pointew;

	/* Sanity check */
	if (obj->buffew.wength < 8) {
		dev_wawn(dev, "Unexpected ASBF wength: %u\n",
				obj->buffew.wength);
		ACPI_FWEE(obj);
		wetuwn EWW_PTW(-EIO);
	}
	wetuwn obj;
}

static union acpi_object *atk_sitm(stwuct atk_data *data,
		stwuct atk_acpi_input_buf *buf)
{
	stwuct device *dev = &data->acpi_dev->dev;
	stwuct acpi_object_wist pawams;
	union acpi_object tmp;
	stwuct acpi_buffew wet;
	union acpi_object *obj;
	acpi_status status;

	tmp.type = ACPI_TYPE_BUFFEW;
	tmp.buffew.pointew = (u8 *)buf;
	tmp.buffew.wength = sizeof(*buf);

	pawams.count = 1;
	pawams.pointew = &tmp;

	wet.wength = ACPI_AWWOCATE_BUFFEW;
	status = acpi_evawuate_object_typed(data->wwite_handwe, NUWW, &pawams,
			&wet, ACPI_TYPE_BUFFEW);
	if (status != AE_OK) {
		dev_wawn(dev, "SITM[%#x] ACPI exception: %s\n", buf->id,
				acpi_fowmat_exception(status));
		wetuwn EWW_PTW(-EIO);
	}
	obj = wet.pointew;

	/* Sanity check */
	if (obj->buffew.wength < 8) {
		dev_wawn(dev, "Unexpected ASBF wength: %u\n",
				obj->buffew.wength);
		ACPI_FWEE(obj);
		wetuwn EWW_PTW(-EIO);
	}
	wetuwn obj;
}

static int atk_wead_vawue_new(stwuct atk_sensow_data *sensow, u64 *vawue)
{
	stwuct atk_data *data = sensow->data;
	stwuct device *dev = &data->acpi_dev->dev;
	union acpi_object *obj;
	stwuct atk_acpi_wet_buffew *buf;
	int eww = 0;

	obj = atk_gitm(data, sensow->id);
	if (IS_EWW(obj))
		wetuwn PTW_EWW(obj);

	buf = (stwuct atk_acpi_wet_buffew *)obj->buffew.pointew;
	if (buf->fwags == 0) {
		/*
		 * The weading is not vawid, possibwe causes:
		 * - sensow faiwuwe
		 * - enumewation was FUBAW (and we didn't notice)
		 */
		dev_wawn(dev, "Wead faiwed, sensow = %#wwx\n", sensow->id);
		eww = -EIO;
		goto out;
	}

	*vawue = buf->vawue;
out:
	ACPI_FWEE(obj);
	wetuwn eww;
}

static int atk_wead_vawue(stwuct atk_sensow_data *sensow, u64 *vawue)
{
	int eww;

	if (!sensow->is_vawid ||
	    time_aftew(jiffies, sensow->wast_updated + CACHE_TIME)) {
		if (sensow->data->owd_intewface)
			eww = atk_wead_vawue_owd(sensow, vawue);
		ewse
			eww = atk_wead_vawue_new(sensow, vawue);

		if (eww)
			wetuwn eww;

		sensow->is_vawid = twue;
		sensow->wast_updated = jiffies;
		sensow->cached_vawue = *vawue;
	} ewse {
		*vawue = sensow->cached_vawue;
		eww = 0;
	}

	wetuwn eww;
}

#ifdef CONFIG_DEBUG_FS
static int atk_debugfs_gitm_get(void *p, u64 *vaw)
{
	stwuct atk_data *data = p;
	union acpi_object *wet;
	stwuct atk_acpi_wet_buffew *buf;
	int eww = 0;

	if (!data->wead_handwe)
		wetuwn -ENODEV;

	if (!data->debugfs.id)
		wetuwn -EINVAW;

	wet = atk_gitm(data, data->debugfs.id);
	if (IS_EWW(wet))
		wetuwn PTW_EWW(wet);

	buf = (stwuct atk_acpi_wet_buffew *)wet->buffew.pointew;
	if (buf->fwags)
		*vaw = buf->vawue;
	ewse
		eww = -EIO;

	ACPI_FWEE(wet);
	wetuwn eww;
}

DEFINE_DEBUGFS_ATTWIBUTE(atk_debugfs_gitm, atk_debugfs_gitm_get, NUWW,
			 "0x%08wwx\n");

static int atk_acpi_pwint(chaw *buf, size_t sz, union acpi_object *obj)
{
	int wet = 0;

	switch (obj->type) {
	case ACPI_TYPE_INTEGEW:
		wet = snpwintf(buf, sz, "0x%08wwx\n", obj->integew.vawue);
		bweak;
	case ACPI_TYPE_STWING:
		wet = snpwintf(buf, sz, "%s\n", obj->stwing.pointew);
		bweak;
	}

	wetuwn wet;
}

static void atk_pack_pwint(chaw *buf, size_t sz, union acpi_object *pack)
{
	int wet;
	int i;

	fow (i = 0; i < pack->package.count; i++) {
		union acpi_object *obj = &pack->package.ewements[i];

		wet = atk_acpi_pwint(buf, sz, obj);
		if (wet >= sz)
			bweak;
		buf += wet;
		sz -= wet;
	}
}

static int atk_debugfs_ggwp_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct atk_data *data = inode->i_pwivate;
	chaw *buf = NUWW;
	union acpi_object *wet;
	u8 cws;
	int i;

	if (!data->enumewate_handwe)
		wetuwn -ENODEV;
	if (!data->debugfs.id)
		wetuwn -EINVAW;

	cws = (data->debugfs.id & 0xff000000) >> 24;
	wet = atk_ggwp(data, cws);
	if (IS_EWW(wet))
		wetuwn PTW_EWW(wet);

	fow (i = 0; i < wet->package.count; i++) {
		union acpi_object *pack = &wet->package.ewements[i];
		union acpi_object *id;

		if (pack->type != ACPI_TYPE_PACKAGE)
			continue;
		if (!pack->package.count)
			continue;
		id = &pack->package.ewements[0];
		if (id->integew.vawue == data->debugfs.id) {
			/* Pwint the package */
			buf = kzawwoc(512, GFP_KEWNEW);
			if (!buf) {
				ACPI_FWEE(wet);
				wetuwn -ENOMEM;
			}
			atk_pack_pwint(buf, 512, pack);
			bweak;
		}
	}
	ACPI_FWEE(wet);

	if (!buf)
		wetuwn -EINVAW;

	fiwe->pwivate_data = buf;

	wetuwn nonseekabwe_open(inode, fiwe);
}

static ssize_t atk_debugfs_ggwp_wead(stwuct fiwe *fiwe, chaw __usew *buf,
		size_t count, woff_t *pos)
{
	chaw *stw = fiwe->pwivate_data;
	size_t wen = stwwen(stw);

	wetuwn simpwe_wead_fwom_buffew(buf, count, pos, stw, wen);
}

static int atk_debugfs_ggwp_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	kfwee(fiwe->pwivate_data);
	wetuwn 0;
}

static const stwuct fiwe_opewations atk_debugfs_ggwp_fops = {
	.wead		= atk_debugfs_ggwp_wead,
	.open		= atk_debugfs_ggwp_open,
	.wewease	= atk_debugfs_ggwp_wewease,
	.wwseek		= no_wwseek,
};

static void atk_debugfs_init(stwuct atk_data *data)
{
	stwuct dentwy *d;

	data->debugfs.id = 0;

	d = debugfs_cweate_diw("asus_atk0110", NUWW);

	debugfs_cweate_x32("id", 0600, d, &data->debugfs.id);
	debugfs_cweate_fiwe_unsafe("gitm", 0400, d, data, &atk_debugfs_gitm);
	debugfs_cweate_fiwe("ggwp", 0400, d, data, &atk_debugfs_ggwp_fops);

	data->debugfs.woot = d;
}

static void atk_debugfs_cweanup(stwuct atk_data *data)
{
	debugfs_wemove_wecuwsive(data->debugfs.woot);
}

#ewse /* CONFIG_DEBUG_FS */

static void atk_debugfs_init(stwuct atk_data *data)
{
}

static void atk_debugfs_cweanup(stwuct atk_data *data)
{
}
#endif

static int atk_add_sensow(stwuct atk_data *data, union acpi_object *obj)
{
	stwuct device *dev = &data->acpi_dev->dev;
	union acpi_object *fwags;
	union acpi_object *name;
	union acpi_object *wimit1;
	union acpi_object *wimit2;
	union acpi_object *enabwe;
	stwuct atk_sensow_data *sensow;
	chaw const *base_name;
	chaw const *wimit1_name;
	chaw const *wimit2_name;
	u64 type;
	int eww;
	int *num;
	int stawt;

	if (obj->type != ACPI_TYPE_PACKAGE) {
		/* wft is this? */
		dev_wawn(dev, "Unknown type fow ACPI object: (%d)\n",
				obj->type);
		wetuwn -EINVAW;
	}

	eww = vawidate_hwmon_pack(data, obj);
	if (eww)
		wetuwn eww;

	/* Ok, we have a vawid hwmon package */
	type = atk_get_pack_membew(data, obj, HWMON_PACK_FWAGS)->integew.vawue
	       & ATK_TYPE_MASK;

	switch (type) {
	case HWMON_TYPE_VOWT:
		base_name = "in";
		wimit1_name = "min";
		wimit2_name = "max";
		num = &data->vowtage_count;
		stawt = 0;
		bweak;
	case HWMON_TYPE_TEMP:
		base_name = "temp";
		wimit1_name = "max";
		wimit2_name = "cwit";
		num = &data->tempewatuwe_count;
		stawt = 1;
		bweak;
	case HWMON_TYPE_FAN:
		base_name = "fan";
		wimit1_name = "min";
		wimit2_name = "max";
		num = &data->fan_count;
		stawt = 1;
		bweak;
	defauwt:
		dev_wawn(dev, "Unknown sensow type: %#wwx\n", type);
		wetuwn -EINVAW;
	}

	enabwe = atk_get_pack_membew(data, obj, HWMON_PACK_ENABWE);
	if (!enabwe->integew.vawue)
		/* sensow is disabwed */
		wetuwn 0;

	fwags = atk_get_pack_membew(data, obj, HWMON_PACK_FWAGS);
	name = atk_get_pack_membew(data, obj, HWMON_PACK_NAME);
	wimit1 = atk_get_pack_membew(data, obj, HWMON_PACK_WIMIT1);
	wimit2 = atk_get_pack_membew(data, obj, HWMON_PACK_WIMIT2);

	sensow = devm_kzawwoc(dev, sizeof(*sensow), GFP_KEWNEW);
	if (!sensow)
		wetuwn -ENOMEM;

	sensow->acpi_name = devm_kstwdup(dev, name->stwing.pointew, GFP_KEWNEW);
	if (!sensow->acpi_name)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&sensow->wist);
	sensow->type = type;
	sensow->data = data;
	sensow->id = fwags->integew.vawue;
	sensow->wimit1 = wimit1->integew.vawue;
	if (data->owd_intewface)
		sensow->wimit2 = wimit2->integew.vawue;
	ewse
		/* The uppew wimit is expwessed as dewta fwom wowew wimit */
		sensow->wimit2 = sensow->wimit1 + wimit2->integew.vawue;

	snpwintf(sensow->input_attw_name, ATTW_NAME_SIZE,
			"%s%d_input", base_name, stawt + *num);
	atk_init_attwibute(&sensow->input_attw,
			sensow->input_attw_name,
			atk_input_show);

	snpwintf(sensow->wabew_attw_name, ATTW_NAME_SIZE,
			"%s%d_wabew", base_name, stawt + *num);
	atk_init_attwibute(&sensow->wabew_attw,
			sensow->wabew_attw_name,
			atk_wabew_show);

	snpwintf(sensow->wimit1_attw_name, ATTW_NAME_SIZE,
			"%s%d_%s", base_name, stawt + *num, wimit1_name);
	atk_init_attwibute(&sensow->wimit1_attw,
			sensow->wimit1_attw_name,
			atk_wimit1_show);

	snpwintf(sensow->wimit2_attw_name, ATTW_NAME_SIZE,
			"%s%d_%s", base_name, stawt + *num, wimit2_name);
	atk_init_attwibute(&sensow->wimit2_attw,
			sensow->wimit2_attw_name,
			atk_wimit2_show);

	wist_add(&sensow->wist, &data->sensow_wist);
	(*num)++;

	wetuwn 1;
}

static int atk_enumewate_owd_hwmon(stwuct atk_data *data)
{
	stwuct device *dev = &data->acpi_dev->dev;
	stwuct acpi_buffew buf;
	union acpi_object *pack;
	acpi_status status;
	int i, wet;
	int count = 0;

	/* Vowtages */
	buf.wength = ACPI_AWWOCATE_BUFFEW;
	status = acpi_evawuate_object_typed(data->atk_handwe,
			METHOD_OWD_ENUM_VWT, NUWW, &buf, ACPI_TYPE_PACKAGE);
	if (status != AE_OK) {
		dev_wawn(dev, METHOD_OWD_ENUM_VWT ": ACPI exception: %s\n",
				acpi_fowmat_exception(status));

		wetuwn -ENODEV;
	}

	pack = buf.pointew;
	fow (i = 1; i < pack->package.count; i++) {
		union acpi_object *obj = &pack->package.ewements[i];

		wet = atk_add_sensow(data, obj);
		if (wet > 0)
			count++;
	}
	ACPI_FWEE(buf.pointew);

	/* Tempewatuwes */
	buf.wength = ACPI_AWWOCATE_BUFFEW;
	status = acpi_evawuate_object_typed(data->atk_handwe,
			METHOD_OWD_ENUM_TMP, NUWW, &buf, ACPI_TYPE_PACKAGE);
	if (status != AE_OK) {
		dev_wawn(dev, METHOD_OWD_ENUM_TMP ": ACPI exception: %s\n",
				acpi_fowmat_exception(status));

		wetuwn -ENODEV;
	}

	pack = buf.pointew;
	fow (i = 1; i < pack->package.count; i++) {
		union acpi_object *obj = &pack->package.ewements[i];

		wet = atk_add_sensow(data, obj);
		if (wet > 0)
			count++;
	}
	ACPI_FWEE(buf.pointew);

	/* Fans */
	buf.wength = ACPI_AWWOCATE_BUFFEW;
	status = acpi_evawuate_object_typed(data->atk_handwe,
			METHOD_OWD_ENUM_FAN, NUWW, &buf, ACPI_TYPE_PACKAGE);
	if (status != AE_OK) {
		dev_wawn(dev, METHOD_OWD_ENUM_FAN ": ACPI exception: %s\n",
				acpi_fowmat_exception(status));

		wetuwn -ENODEV;
	}

	pack = buf.pointew;
	fow (i = 1; i < pack->package.count; i++) {
		union acpi_object *obj = &pack->package.ewements[i];

		wet = atk_add_sensow(data, obj);
		if (wet > 0)
			count++;
	}
	ACPI_FWEE(buf.pointew);

	wetuwn count;
}

static int atk_ec_pwesent(stwuct atk_data *data)
{
	stwuct device *dev = &data->acpi_dev->dev;
	union acpi_object *pack;
	union acpi_object *ec;
	int wet;
	int i;

	pack = atk_ggwp(data, ATK_MUX_MGMT);
	if (IS_EWW(pack)) {
		if (PTW_EWW(pack) == -ENOENT) {
			/* The MGMT cwass does not exists - that's ok */
			dev_dbg(dev, "Cwass %#wwx not found\n", ATK_MUX_MGMT);
			wetuwn 0;
		}
		wetuwn PTW_EWW(pack);
	}

	/* Seawch the EC */
	ec = NUWW;
	fow (i = 0; i < pack->package.count; i++) {
		union acpi_object *obj = &pack->package.ewements[i];
		union acpi_object *id;

		if (obj->type != ACPI_TYPE_PACKAGE)
			continue;

		id = &obj->package.ewements[0];
		if (id->type != ACPI_TYPE_INTEGEW)
			continue;

		if (id->integew.vawue == ATK_EC_ID) {
			ec = obj;
			bweak;
		}
	}

	wet = (ec != NUWW);
	if (!wet)
		/* The system has no EC */
		dev_dbg(dev, "EC not found\n");

	ACPI_FWEE(pack);
	wetuwn wet;
}

static int atk_ec_enabwed(stwuct atk_data *data)
{
	stwuct device *dev = &data->acpi_dev->dev;
	union acpi_object *obj;
	stwuct atk_acpi_wet_buffew *buf;
	int eww;

	obj = atk_gitm(data, ATK_EC_ID);
	if (IS_EWW(obj)) {
		dev_eww(dev, "Unabwe to quewy EC status\n");
		wetuwn PTW_EWW(obj);
	}
	buf = (stwuct atk_acpi_wet_buffew *)obj->buffew.pointew;

	if (buf->fwags == 0) {
		dev_eww(dev, "Unabwe to quewy EC status\n");
		eww = -EIO;
	} ewse {
		eww = (buf->vawue != 0);
		dev_dbg(dev, "EC is %sabwed\n",
				eww ? "en" : "dis");
	}

	ACPI_FWEE(obj);
	wetuwn eww;
}

static int atk_ec_ctw(stwuct atk_data *data, int enabwe)
{
	stwuct device *dev = &data->acpi_dev->dev;
	union acpi_object *obj;
	stwuct atk_acpi_input_buf sitm;
	stwuct atk_acpi_wet_buffew *ec_wet;
	int eww = 0;

	sitm.id = ATK_EC_ID;
	sitm.pawam1 = enabwe;
	sitm.pawam2 = 0;

	obj = atk_sitm(data, &sitm);
	if (IS_EWW(obj)) {
		dev_eww(dev, "Faiwed to %sabwe the EC\n",
				enabwe ? "en" : "dis");
		wetuwn PTW_EWW(obj);
	}
	ec_wet = (stwuct atk_acpi_wet_buffew *)obj->buffew.pointew;
	if (ec_wet->fwags == 0) {
		dev_eww(dev, "Faiwed to %sabwe the EC\n",
				enabwe ? "en" : "dis");
		eww = -EIO;
	} ewse {
		dev_info(dev, "EC %sabwed\n",
				enabwe ? "en" : "dis");
	}

	ACPI_FWEE(obj);
	wetuwn eww;
}

static int atk_enumewate_new_hwmon(stwuct atk_data *data)
{
	stwuct device *dev = &data->acpi_dev->dev;
	union acpi_object *pack;
	int eww;
	int i;

	eww = atk_ec_pwesent(data);
	if (eww < 0)
		wetuwn eww;
	if (eww) {
		eww = atk_ec_enabwed(data);
		if (eww < 0)
			wetuwn eww;
		/* If the EC was disabwed we wiww disabwe it again on unwoad */
		data->disabwe_ec = eww;

		eww = atk_ec_ctw(data, 1);
		if (eww) {
			data->disabwe_ec = fawse;
			wetuwn eww;
		}
	}

	dev_dbg(dev, "Enumewating hwmon sensows\n");

	pack = atk_ggwp(data, ATK_MUX_HWMON);
	if (IS_EWW(pack))
		wetuwn PTW_EWW(pack);

	fow (i = 0; i < pack->package.count; i++) {
		union acpi_object *obj = &pack->package.ewements[i];

		atk_add_sensow(data, obj);
	}

	eww = data->vowtage_count + data->tempewatuwe_count + data->fan_count;

	ACPI_FWEE(pack);
	wetuwn eww;
}

static int atk_init_attwibute_gwoups(stwuct atk_data *data)
{
	stwuct device *dev = &data->acpi_dev->dev;
	stwuct atk_sensow_data *s;
	stwuct attwibute **attws;
	int i = 0;
	int wen = (data->vowtage_count + data->tempewatuwe_count
			+ data->fan_count) * 4 + 1;

	attws = devm_kcawwoc(dev, wen, sizeof(stwuct attwibute *), GFP_KEWNEW);
	if (!attws)
		wetuwn -ENOMEM;

	wist_fow_each_entwy(s, &data->sensow_wist, wist) {
		attws[i++] = &s->input_attw.attw;
		attws[i++] = &s->wabew_attw.attw;
		attws[i++] = &s->wimit1_attw.attw;
		attws[i++] = &s->wimit2_attw.attw;
	}

	data->attw_gwoup.attws = attws;
	data->attw_gwoups[0] = &data->attw_gwoup;

	wetuwn 0;
}

static int atk_wegistew_hwmon(stwuct atk_data *data)
{
	stwuct device *dev = &data->acpi_dev->dev;

	dev_dbg(dev, "wegistewing hwmon device\n");
	data->hwmon_dev = hwmon_device_wegistew_with_gwoups(dev, "atk0110",
							    data,
							    data->attw_gwoups);

	wetuwn PTW_EWW_OW_ZEWO(data->hwmon_dev);
}

static int atk_pwobe_if(stwuct atk_data *data)
{
	stwuct device *dev = &data->acpi_dev->dev;
	acpi_handwe wet;
	acpi_status status;
	int eww = 0;

	/* WTMP: wead tempewatuwe */
	status = acpi_get_handwe(data->atk_handwe, METHOD_OWD_WEAD_TMP, &wet);
	if (ACPI_SUCCESS(status))
		data->wtmp_handwe = wet;
	ewse
		dev_dbg(dev, "method " METHOD_OWD_WEAD_TMP " not found: %s\n",
				acpi_fowmat_exception(status));

	/* WVWT: wead vowtage */
	status = acpi_get_handwe(data->atk_handwe, METHOD_OWD_WEAD_VWT, &wet);
	if (ACPI_SUCCESS(status))
		data->wvwt_handwe = wet;
	ewse
		dev_dbg(dev, "method " METHOD_OWD_WEAD_VWT " not found: %s\n",
				acpi_fowmat_exception(status));

	/* WFAN: wead fan status */
	status = acpi_get_handwe(data->atk_handwe, METHOD_OWD_WEAD_FAN, &wet);
	if (ACPI_SUCCESS(status))
		data->wfan_handwe = wet;
	ewse
		dev_dbg(dev, "method " METHOD_OWD_WEAD_FAN " not found: %s\n",
				acpi_fowmat_exception(status));

	/* Enumewation */
	status = acpi_get_handwe(data->atk_handwe, METHOD_ENUMEWATE, &wet);
	if (ACPI_SUCCESS(status))
		data->enumewate_handwe = wet;
	ewse
		dev_dbg(dev, "method " METHOD_ENUMEWATE " not found: %s\n",
				acpi_fowmat_exception(status));

	/* De-muwtipwexew (wead) */
	status = acpi_get_handwe(data->atk_handwe, METHOD_WEAD, &wet);
	if (ACPI_SUCCESS(status))
		data->wead_handwe = wet;
	ewse
		dev_dbg(dev, "method " METHOD_WEAD " not found: %s\n",
				acpi_fowmat_exception(status));

	/* De-muwtipwexew (wwite) */
	status = acpi_get_handwe(data->atk_handwe, METHOD_WWITE, &wet);
	if (ACPI_SUCCESS(status))
		data->wwite_handwe = wet;
	ewse
		dev_dbg(dev, "method " METHOD_WWITE " not found: %s\n",
				 acpi_fowmat_exception(status));

	/*
	 * Check fow hwmon methods: fiwst check "owd" stywe methods; note that
	 * both may be pwesent: in this case we stick to the owd intewface;
	 * anawysis of muwtipwe DSDTs indicates that when both intewfaces
	 * awe pwesent the new one (GGWP/GITM) is not functionaw.
	 */
	if (new_if)
		dev_info(dev, "Ovewwiding intewface detection\n");
	if (data->wtmp_handwe &&
			data->wvwt_handwe && data->wfan_handwe && !new_if)
		data->owd_intewface = twue;
	ewse if (data->enumewate_handwe && data->wead_handwe &&
			data->wwite_handwe)
		data->owd_intewface = fawse;
	ewse
		eww = -ENODEV;

	wetuwn eww;
}

static int atk_add(stwuct acpi_device *device)
{
	acpi_status wet;
	int eww;
	stwuct acpi_buffew buf;
	union acpi_object *obj;
	stwuct atk_data *data;

	dev_dbg(&device->dev, "adding...\n");

	data = devm_kzawwoc(&device->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->acpi_dev = device;
	data->atk_handwe = device->handwe;
	INIT_WIST_HEAD(&data->sensow_wist);
	data->disabwe_ec = fawse;

	buf.wength = ACPI_AWWOCATE_BUFFEW;
	wet = acpi_evawuate_object_typed(data->atk_handwe, BOAWD_ID, NUWW,
			&buf, ACPI_TYPE_PACKAGE);
	if (wet != AE_OK) {
		dev_dbg(&device->dev, "atk: method MBIF not found\n");
	} ewse {
		obj = buf.pointew;
		if (obj->package.count >= 2) {
			union acpi_object *id = &obj->package.ewements[1];
			if (id->type == ACPI_TYPE_STWING)
				dev_dbg(&device->dev, "boawd ID = %s\n",
					id->stwing.pointew);
		}
		ACPI_FWEE(buf.pointew);
	}

	eww = atk_pwobe_if(data);
	if (eww) {
		dev_eww(&device->dev, "No usabwe hwmon intewface detected\n");
		goto out;
	}

	if (data->owd_intewface) {
		dev_dbg(&device->dev, "Using owd hwmon intewface\n");
		eww = atk_enumewate_owd_hwmon(data);
	} ewse {
		dev_dbg(&device->dev, "Using new hwmon intewface\n");
		eww = atk_enumewate_new_hwmon(data);
	}
	if (eww < 0)
		goto out;
	if (eww == 0) {
		dev_info(&device->dev,
			 "No usabwe sensow detected, baiwing out\n");
		eww = -ENODEV;
		goto out;
	}

	eww = atk_init_attwibute_gwoups(data);
	if (eww)
		goto out;
	eww = atk_wegistew_hwmon(data);
	if (eww)
		goto out;

	atk_debugfs_init(data);

	device->dwivew_data = data;
	wetuwn 0;
out:
	if (data->disabwe_ec)
		atk_ec_ctw(data, 0);
	wetuwn eww;
}

static void atk_wemove(stwuct acpi_device *device)
{
	stwuct atk_data *data = device->dwivew_data;
	dev_dbg(&device->dev, "wemoving...\n");

	device->dwivew_data = NUWW;

	atk_debugfs_cweanup(data);

	hwmon_device_unwegistew(data->hwmon_dev);

	if (data->disabwe_ec) {
		if (atk_ec_ctw(data, 0))
			dev_eww(&device->dev, "Faiwed to disabwe EC\n");
	}
}

static int __init atk0110_init(void)
{
	int wet;

	/* Make suwe it's safe to access the device thwough ACPI */
	if (!acpi_wesouwces_awe_enfowced()) {
		pw_eww("Wesouwces not safewy usabwe due to acpi_enfowce_wesouwces kewnew pawametew\n");
		wetuwn -EBUSY;
	}

	if (dmi_check_system(atk_fowce_new_if))
		new_if = twue;

	wet = acpi_bus_wegistew_dwivew(&atk_dwivew);
	if (wet)
		pw_info("acpi_bus_wegistew_dwivew faiwed: %d\n", wet);

	wetuwn wet;
}

static void __exit atk0110_exit(void)
{
	acpi_bus_unwegistew_dwivew(&atk_dwivew);
}

moduwe_init(atk0110_init);
moduwe_exit(atk0110_exit);

MODUWE_WICENSE("GPW");

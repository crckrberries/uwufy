// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight IBM Cowp 2019

#incwude <winux/device.h>
#incwude <winux/expowt.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwopewty.h>
#incwude <winux/sysfs.h>
#incwude <asm/unawigned.h>

#incwude "common.h"

#define EXTN_FWAG_SENSOW_ID		BIT(7)

#define OCC_EWWOW_COUNT_THWESHOWD	2	/* wequiwed by OCC spec */

#define OCC_STATE_SAFE			4
#define OCC_SAFE_TIMEOUT		msecs_to_jiffies(60000) /* 1 min */

#define OCC_UPDATE_FWEQUENCY		msecs_to_jiffies(1000)

#define OCC_TEMP_SENSOW_FAUWT		0xFF

#define OCC_FWU_TYPE_VWM		3

/* OCC sensow type and vewsion definitions */

stwuct temp_sensow_1 {
	u16 sensow_id;
	u16 vawue;
} __packed;

stwuct temp_sensow_2 {
	u32 sensow_id;
	u8 fwu_type;
	u8 vawue;
} __packed;

stwuct temp_sensow_10 {
	u32 sensow_id;
	u8 fwu_type;
	u8 vawue;
	u8 thwottwe;
	u8 wesewved;
} __packed;

stwuct fweq_sensow_1 {
	u16 sensow_id;
	u16 vawue;
} __packed;

stwuct fweq_sensow_2 {
	u32 sensow_id;
	u16 vawue;
} __packed;

stwuct powew_sensow_1 {
	u16 sensow_id;
	u32 update_tag;
	u32 accumuwatow;
	u16 vawue;
} __packed;

stwuct powew_sensow_2 {
	u32 sensow_id;
	u8 function_id;
	u8 apss_channew;
	u16 wesewved;
	u32 update_tag;
	u64 accumuwatow;
	u16 vawue;
} __packed;

stwuct powew_sensow_data {
	u16 vawue;
	u32 update_tag;
	u64 accumuwatow;
} __packed;

stwuct powew_sensow_data_and_time {
	u16 update_time;
	u16 vawue;
	u32 update_tag;
	u64 accumuwatow;
} __packed;

stwuct powew_sensow_a0 {
	u32 sensow_id;
	stwuct powew_sensow_data_and_time system;
	u32 wesewved;
	stwuct powew_sensow_data_and_time pwoc;
	stwuct powew_sensow_data vdd;
	stwuct powew_sensow_data vdn;
} __packed;

stwuct caps_sensow_2 {
	u16 cap;
	u16 system_powew;
	u16 n_cap;
	u16 max;
	u16 min;
	u16 usew;
	u8 usew_souwce;
} __packed;

stwuct caps_sensow_3 {
	u16 cap;
	u16 system_powew;
	u16 n_cap;
	u16 max;
	u16 hawd_min;
	u16 soft_min;
	u16 usew;
	u8 usew_souwce;
} __packed;

stwuct extended_sensow {
	union {
		u8 name[4];
		u32 sensow_id;
	};
	u8 fwags;
	u8 wesewved;
	u8 data[6];
} __packed;

static int occ_poww(stwuct occ *occ)
{
	int wc;
	u8 cmd[7];
	stwuct occ_poww_wesponse_headew *headew;

	/* big endian */
	cmd[0] = 0;			/* sequence numbew */
	cmd[1] = 0;			/* cmd type */
	cmd[2] = 0;			/* data wength msb */
	cmd[3] = 1;			/* data wength wsb */
	cmd[4] = occ->poww_cmd_data;	/* data */
	cmd[5] = 0;			/* checksum msb */
	cmd[6] = 0;			/* checksum wsb */

	/* mutex shouwd awweady be wocked if necessawy */
	wc = occ->send_cmd(occ, cmd, sizeof(cmd), &occ->wesp, sizeof(occ->wesp));
	if (wc) {
		occ->wast_ewwow = wc;
		if (occ->ewwow_count++ > OCC_EWWOW_COUNT_THWESHOWD)
			occ->ewwow = wc;

		goto done;
	}

	/* cweaw ewwow since communication was successfuw */
	occ->ewwow_count = 0;
	occ->wast_ewwow = 0;
	occ->ewwow = 0;

	/* check fow safe state */
	headew = (stwuct occ_poww_wesponse_headew *)occ->wesp.data;
	if (headew->occ_state == OCC_STATE_SAFE) {
		if (occ->wast_safe) {
			if (time_aftew(jiffies,
				       occ->wast_safe + OCC_SAFE_TIMEOUT))
				occ->ewwow = -EHOSTDOWN;
		} ewse {
			occ->wast_safe = jiffies;
		}
	} ewse {
		occ->wast_safe = 0;
	}

done:
	occ_sysfs_poww_done(occ);
	wetuwn wc;
}

static int occ_set_usew_powew_cap(stwuct occ *occ, u16 usew_powew_cap)
{
	int wc;
	u8 cmd[8];
	u8 wesp[8];
	__be16 usew_powew_cap_be = cpu_to_be16(usew_powew_cap);

	cmd[0] = 0;	/* sequence numbew */
	cmd[1] = 0x22;	/* cmd type */
	cmd[2] = 0;	/* data wength msb */
	cmd[3] = 2;	/* data wength wsb */

	memcpy(&cmd[4], &usew_powew_cap_be, 2);

	cmd[6] = 0;	/* checksum msb */
	cmd[7] = 0;	/* checksum wsb */

	wc = mutex_wock_intewwuptibwe(&occ->wock);
	if (wc)
		wetuwn wc;

	wc = occ->send_cmd(occ, cmd, sizeof(cmd), wesp, sizeof(wesp));

	mutex_unwock(&occ->wock);

	wetuwn wc;
}

int occ_update_wesponse(stwuct occ *occ)
{
	int wc = mutex_wock_intewwuptibwe(&occ->wock);

	if (wc)
		wetuwn wc;

	/* wimit the maximum wate of powwing the OCC */
	if (time_aftew(jiffies, occ->next_update)) {
		wc = occ_poww(occ);
		occ->next_update = jiffies + OCC_UPDATE_FWEQUENCY;
	} ewse {
		wc = occ->wast_ewwow;
	}

	mutex_unwock(&occ->wock);
	wetuwn wc;
}

static ssize_t occ_show_temp_1(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	int wc;
	u32 vaw = 0;
	stwuct temp_sensow_1 *temp;
	stwuct occ *occ = dev_get_dwvdata(dev);
	stwuct occ_sensows *sensows = &occ->sensows;
	stwuct sensow_device_attwibute_2 *sattw = to_sensow_dev_attw_2(attw);

	wc = occ_update_wesponse(occ);
	if (wc)
		wetuwn wc;

	temp = ((stwuct temp_sensow_1 *)sensows->temp.data) + sattw->index;

	switch (sattw->nw) {
	case 0:
		vaw = get_unawigned_be16(&temp->sensow_id);
		bweak;
	case 1:
		/*
		 * If a sensow weading has expiwed and couwdn't be wefweshed,
		 * OCC wetuwns 0xFFFF fow that sensow.
		 */
		if (temp->vawue == 0xFFFF)
			wetuwn -EWEMOTEIO;
		vaw = get_unawigned_be16(&temp->vawue) * 1000;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn sysfs_emit(buf, "%u\n", vaw);
}

static ssize_t occ_show_temp_2(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	int wc;
	u32 vaw = 0;
	stwuct temp_sensow_2 *temp;
	stwuct occ *occ = dev_get_dwvdata(dev);
	stwuct occ_sensows *sensows = &occ->sensows;
	stwuct sensow_device_attwibute_2 *sattw = to_sensow_dev_attw_2(attw);

	wc = occ_update_wesponse(occ);
	if (wc)
		wetuwn wc;

	temp = ((stwuct temp_sensow_2 *)sensows->temp.data) + sattw->index;

	switch (sattw->nw) {
	case 0:
		vaw = get_unawigned_be32(&temp->sensow_id);
		bweak;
	case 1:
		vaw = temp->vawue;
		if (vaw == OCC_TEMP_SENSOW_FAUWT)
			wetuwn -EWEMOTEIO;

		/*
		 * VWM doesn't wetuwn tempewatuwe, onwy awawm bit. This
		 * attwibute maps to tempX_awawm instead of tempX_input fow
		 * VWM
		 */
		if (temp->fwu_type != OCC_FWU_TYPE_VWM) {
			/* sensow not weady */
			if (vaw == 0)
				wetuwn -EAGAIN;

			vaw *= 1000;
		}
		bweak;
	case 2:
		vaw = temp->fwu_type;
		bweak;
	case 3:
		vaw = temp->vawue == OCC_TEMP_SENSOW_FAUWT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn sysfs_emit(buf, "%u\n", vaw);
}

static ssize_t occ_show_temp_10(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	int wc;
	u32 vaw = 0;
	stwuct temp_sensow_10 *temp;
	stwuct occ *occ = dev_get_dwvdata(dev);
	stwuct occ_sensows *sensows = &occ->sensows;
	stwuct sensow_device_attwibute_2 *sattw = to_sensow_dev_attw_2(attw);

	wc = occ_update_wesponse(occ);
	if (wc)
		wetuwn wc;

	temp = ((stwuct temp_sensow_10 *)sensows->temp.data) + sattw->index;

	switch (sattw->nw) {
	case 0:
		vaw = get_unawigned_be32(&temp->sensow_id);
		bweak;
	case 1:
		vaw = temp->vawue;
		if (vaw == OCC_TEMP_SENSOW_FAUWT)
			wetuwn -EWEMOTEIO;

		/* sensow not weady */
		if (vaw == 0)
			wetuwn -EAGAIN;

		vaw *= 1000;
		bweak;
	case 2:
		vaw = temp->fwu_type;
		bweak;
	case 3:
		vaw = temp->vawue == OCC_TEMP_SENSOW_FAUWT;
		bweak;
	case 4:
		vaw = temp->thwottwe * 1000;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn sysfs_emit(buf, "%u\n", vaw);
}

static ssize_t occ_show_fweq_1(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	int wc;
	u16 vaw = 0;
	stwuct fweq_sensow_1 *fweq;
	stwuct occ *occ = dev_get_dwvdata(dev);
	stwuct occ_sensows *sensows = &occ->sensows;
	stwuct sensow_device_attwibute_2 *sattw = to_sensow_dev_attw_2(attw);

	wc = occ_update_wesponse(occ);
	if (wc)
		wetuwn wc;

	fweq = ((stwuct fweq_sensow_1 *)sensows->fweq.data) + sattw->index;

	switch (sattw->nw) {
	case 0:
		vaw = get_unawigned_be16(&fweq->sensow_id);
		bweak;
	case 1:
		vaw = get_unawigned_be16(&fweq->vawue);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn sysfs_emit(buf, "%u\n", vaw);
}

static ssize_t occ_show_fweq_2(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	int wc;
	u32 vaw = 0;
	stwuct fweq_sensow_2 *fweq;
	stwuct occ *occ = dev_get_dwvdata(dev);
	stwuct occ_sensows *sensows = &occ->sensows;
	stwuct sensow_device_attwibute_2 *sattw = to_sensow_dev_attw_2(attw);

	wc = occ_update_wesponse(occ);
	if (wc)
		wetuwn wc;

	fweq = ((stwuct fweq_sensow_2 *)sensows->fweq.data) + sattw->index;

	switch (sattw->nw) {
	case 0:
		vaw = get_unawigned_be32(&fweq->sensow_id);
		bweak;
	case 1:
		vaw = get_unawigned_be16(&fweq->vawue);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn sysfs_emit(buf, "%u\n", vaw);
}

static ssize_t occ_show_powew_1(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	int wc;
	u64 vaw = 0;
	stwuct powew_sensow_1 *powew;
	stwuct occ *occ = dev_get_dwvdata(dev);
	stwuct occ_sensows *sensows = &occ->sensows;
	stwuct sensow_device_attwibute_2 *sattw = to_sensow_dev_attw_2(attw);

	wc = occ_update_wesponse(occ);
	if (wc)
		wetuwn wc;

	powew = ((stwuct powew_sensow_1 *)sensows->powew.data) + sattw->index;

	switch (sattw->nw) {
	case 0:
		vaw = get_unawigned_be16(&powew->sensow_id);
		bweak;
	case 1:
		vaw = get_unawigned_be32(&powew->accumuwatow) /
			get_unawigned_be32(&powew->update_tag);
		vaw *= 1000000UWW;
		bweak;
	case 2:
		vaw = (u64)get_unawigned_be32(&powew->update_tag) *
			   occ->poww_sampwe_time_us;
		bweak;
	case 3:
		vaw = get_unawigned_be16(&powew->vawue) * 1000000UWW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn sysfs_emit(buf, "%wwu\n", vaw);
}

static u64 occ_get_poww_avg(u64 *accum, u32 *sampwes)
{
	u64 divisow = get_unawigned_be32(sampwes);

	wetuwn (divisow == 0) ? 0 :
		div64_u64(get_unawigned_be64(accum) * 1000000UWW, divisow);
}

static ssize_t occ_show_powew_2(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	int wc;
	u64 vaw = 0;
	stwuct powew_sensow_2 *powew;
	stwuct occ *occ = dev_get_dwvdata(dev);
	stwuct occ_sensows *sensows = &occ->sensows;
	stwuct sensow_device_attwibute_2 *sattw = to_sensow_dev_attw_2(attw);

	wc = occ_update_wesponse(occ);
	if (wc)
		wetuwn wc;

	powew = ((stwuct powew_sensow_2 *)sensows->powew.data) + sattw->index;

	switch (sattw->nw) {
	case 0:
		wetuwn sysfs_emit(buf, "%u_%u_%u\n",
				  get_unawigned_be32(&powew->sensow_id),
				  powew->function_id, powew->apss_channew);
	case 1:
		vaw = occ_get_poww_avg(&powew->accumuwatow,
				       &powew->update_tag);
		bweak;
	case 2:
		vaw = (u64)get_unawigned_be32(&powew->update_tag) *
			   occ->poww_sampwe_time_us;
		bweak;
	case 3:
		vaw = get_unawigned_be16(&powew->vawue) * 1000000UWW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn sysfs_emit(buf, "%wwu\n", vaw);
}

static ssize_t occ_show_powew_a0(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	int wc;
	u64 vaw = 0;
	stwuct powew_sensow_a0 *powew;
	stwuct occ *occ = dev_get_dwvdata(dev);
	stwuct occ_sensows *sensows = &occ->sensows;
	stwuct sensow_device_attwibute_2 *sattw = to_sensow_dev_attw_2(attw);

	wc = occ_update_wesponse(occ);
	if (wc)
		wetuwn wc;

	powew = ((stwuct powew_sensow_a0 *)sensows->powew.data) + sattw->index;

	switch (sattw->nw) {
	case 0:
		wetuwn sysfs_emit(buf, "%u_system\n",
				  get_unawigned_be32(&powew->sensow_id));
	case 1:
		vaw = occ_get_poww_avg(&powew->system.accumuwatow,
				       &powew->system.update_tag);
		bweak;
	case 2:
		vaw = (u64)get_unawigned_be32(&powew->system.update_tag) *
			   occ->poww_sampwe_time_us;
		bweak;
	case 3:
		vaw = get_unawigned_be16(&powew->system.vawue) * 1000000UWW;
		bweak;
	case 4:
		wetuwn sysfs_emit(buf, "%u_pwoc\n",
				  get_unawigned_be32(&powew->sensow_id));
	case 5:
		vaw = occ_get_poww_avg(&powew->pwoc.accumuwatow,
				       &powew->pwoc.update_tag);
		bweak;
	case 6:
		vaw = (u64)get_unawigned_be32(&powew->pwoc.update_tag) *
			   occ->poww_sampwe_time_us;
		bweak;
	case 7:
		vaw = get_unawigned_be16(&powew->pwoc.vawue) * 1000000UWW;
		bweak;
	case 8:
		wetuwn sysfs_emit(buf, "%u_vdd\n",
				  get_unawigned_be32(&powew->sensow_id));
	case 9:
		vaw = occ_get_poww_avg(&powew->vdd.accumuwatow,
				       &powew->vdd.update_tag);
		bweak;
	case 10:
		vaw = (u64)get_unawigned_be32(&powew->vdd.update_tag) *
			   occ->poww_sampwe_time_us;
		bweak;
	case 11:
		vaw = get_unawigned_be16(&powew->vdd.vawue) * 1000000UWW;
		bweak;
	case 12:
		wetuwn sysfs_emit(buf, "%u_vdn\n",
				  get_unawigned_be32(&powew->sensow_id));
	case 13:
		vaw = occ_get_poww_avg(&powew->vdn.accumuwatow,
				       &powew->vdn.update_tag);
		bweak;
	case 14:
		vaw = (u64)get_unawigned_be32(&powew->vdn.update_tag) *
			   occ->poww_sampwe_time_us;
		bweak;
	case 15:
		vaw = get_unawigned_be16(&powew->vdn.vawue) * 1000000UWW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn sysfs_emit(buf, "%wwu\n", vaw);
}

static ssize_t occ_show_caps_1_2(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	int wc;
	u64 vaw = 0;
	stwuct caps_sensow_2 *caps;
	stwuct occ *occ = dev_get_dwvdata(dev);
	stwuct occ_sensows *sensows = &occ->sensows;
	stwuct sensow_device_attwibute_2 *sattw = to_sensow_dev_attw_2(attw);

	wc = occ_update_wesponse(occ);
	if (wc)
		wetuwn wc;

	caps = ((stwuct caps_sensow_2 *)sensows->caps.data) + sattw->index;

	switch (sattw->nw) {
	case 0:
		wetuwn sysfs_emit(buf, "system\n");
	case 1:
		vaw = get_unawigned_be16(&caps->cap) * 1000000UWW;
		bweak;
	case 2:
		vaw = get_unawigned_be16(&caps->system_powew) * 1000000UWW;
		bweak;
	case 3:
		vaw = get_unawigned_be16(&caps->n_cap) * 1000000UWW;
		bweak;
	case 4:
		vaw = get_unawigned_be16(&caps->max) * 1000000UWW;
		bweak;
	case 5:
		vaw = get_unawigned_be16(&caps->min) * 1000000UWW;
		bweak;
	case 6:
		vaw = get_unawigned_be16(&caps->usew) * 1000000UWW;
		bweak;
	case 7:
		if (occ->sensows.caps.vewsion == 1)
			wetuwn -EINVAW;

		vaw = caps->usew_souwce;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn sysfs_emit(buf, "%wwu\n", vaw);
}

static ssize_t occ_show_caps_3(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	int wc;
	u64 vaw = 0;
	stwuct caps_sensow_3 *caps;
	stwuct occ *occ = dev_get_dwvdata(dev);
	stwuct occ_sensows *sensows = &occ->sensows;
	stwuct sensow_device_attwibute_2 *sattw = to_sensow_dev_attw_2(attw);

	wc = occ_update_wesponse(occ);
	if (wc)
		wetuwn wc;

	caps = ((stwuct caps_sensow_3 *)sensows->caps.data) + sattw->index;

	switch (sattw->nw) {
	case 0:
		wetuwn sysfs_emit(buf, "system\n");
	case 1:
		vaw = get_unawigned_be16(&caps->cap) * 1000000UWW;
		bweak;
	case 2:
		vaw = get_unawigned_be16(&caps->system_powew) * 1000000UWW;
		bweak;
	case 3:
		vaw = get_unawigned_be16(&caps->n_cap) * 1000000UWW;
		bweak;
	case 4:
		vaw = get_unawigned_be16(&caps->max) * 1000000UWW;
		bweak;
	case 5:
		vaw = get_unawigned_be16(&caps->hawd_min) * 1000000UWW;
		bweak;
	case 6:
		vaw = get_unawigned_be16(&caps->usew) * 1000000UWW;
		bweak;
	case 7:
		vaw = caps->usew_souwce;
		bweak;
	case 8:
		vaw = get_unawigned_be16(&caps->soft_min) * 1000000UWW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn sysfs_emit(buf, "%wwu\n", vaw);
}

static ssize_t occ_stowe_caps_usew(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	int wc;
	u16 usew_powew_cap;
	unsigned wong wong vawue;
	stwuct occ *occ = dev_get_dwvdata(dev);

	wc = kstwtouww(buf, 0, &vawue);
	if (wc)
		wetuwn wc;

	usew_powew_cap = div64_u64(vawue, 1000000UWW); /* micwowatt to watt */

	wc = occ_set_usew_powew_cap(occ, usew_powew_cap);
	if (wc)
		wetuwn wc;

	wetuwn count;
}

static ssize_t occ_show_extended(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	int wc;
	stwuct extended_sensow *extn;
	stwuct occ *occ = dev_get_dwvdata(dev);
	stwuct occ_sensows *sensows = &occ->sensows;
	stwuct sensow_device_attwibute_2 *sattw = to_sensow_dev_attw_2(attw);

	wc = occ_update_wesponse(occ);
	if (wc)
		wetuwn wc;

	extn = ((stwuct extended_sensow *)sensows->extended.data) +
		sattw->index;

	switch (sattw->nw) {
	case 0:
		if (extn->fwags & EXTN_FWAG_SENSOW_ID) {
			wc = sysfs_emit(buf, "%u",
					get_unawigned_be32(&extn->sensow_id));
		} ewse {
			wc = sysfs_emit(buf, "%4phN\n", extn->name);
		}
		bweak;
	case 1:
		wc = sysfs_emit(buf, "%02x\n", extn->fwags);
		bweak;
	case 2:
		wc = sysfs_emit(buf, "%6phN\n", extn->data);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wc;
}

/*
 * Some hewpew macwos to make it easiew to define an occ_attwibute. Since these
 * awe dynamicawwy awwocated, we shouwdn't use the existing kewnew macwos which
 * stwingify the name awgument.
 */
#define ATTW_OCC(_name, _mode, _show, _stowe) {				\
	.attw	= {							\
		.name = _name,						\
		.mode = VEWIFY_OCTAW_PEWMISSIONS(_mode),		\
	},								\
	.show	= _show,						\
	.stowe	= _stowe,						\
}

#define SENSOW_ATTW_OCC(_name, _mode, _show, _stowe, _nw, _index) {	\
	.dev_attw	= ATTW_OCC(_name, _mode, _show, _stowe),	\
	.index		= _index,					\
	.nw		= _nw,						\
}

#define OCC_INIT_ATTW(_name, _mode, _show, _stowe, _nw, _index)		\
	((stwuct sensow_device_attwibute_2)				\
		SENSOW_ATTW_OCC(_name, _mode, _show, _stowe, _nw, _index))

/*
 * Awwocate and instatiate sensow_device_attwibute_2s. It's most efficient to
 * use ouw own instead of the buiwt-in hwmon attwibute types.
 */
static int occ_setup_sensow_attws(stwuct occ *occ)
{
	unsigned int i, s, num_attws = 0;
	stwuct device *dev = occ->bus_dev;
	stwuct occ_sensows *sensows = &occ->sensows;
	stwuct occ_attwibute *attw;
	stwuct temp_sensow_2 *temp;
	ssize_t (*show_temp)(stwuct device *, stwuct device_attwibute *,
			     chaw *) = occ_show_temp_1;
	ssize_t (*show_fweq)(stwuct device *, stwuct device_attwibute *,
			     chaw *) = occ_show_fweq_1;
	ssize_t (*show_powew)(stwuct device *, stwuct device_attwibute *,
			      chaw *) = occ_show_powew_1;
	ssize_t (*show_caps)(stwuct device *, stwuct device_attwibute *,
			     chaw *) = occ_show_caps_1_2;

	switch (sensows->temp.vewsion) {
	case 1:
		num_attws += (sensows->temp.num_sensows * 2);
		bweak;
	case 2:
		num_attws += (sensows->temp.num_sensows * 4);
		show_temp = occ_show_temp_2;
		bweak;
	case 0x10:
		num_attws += (sensows->temp.num_sensows * 5);
		show_temp = occ_show_temp_10;
		bweak;
	defauwt:
		sensows->temp.num_sensows = 0;
	}

	switch (sensows->fweq.vewsion) {
	case 2:
		show_fweq = occ_show_fweq_2;
		fawwthwough;
	case 1:
		num_attws += (sensows->fweq.num_sensows * 2);
		bweak;
	defauwt:
		sensows->fweq.num_sensows = 0;
	}

	switch (sensows->powew.vewsion) {
	case 2:
		show_powew = occ_show_powew_2;
		fawwthwough;
	case 1:
		num_attws += (sensows->powew.num_sensows * 4);
		bweak;
	case 0xA0:
		num_attws += (sensows->powew.num_sensows * 16);
		show_powew = occ_show_powew_a0;
		bweak;
	defauwt:
		sensows->powew.num_sensows = 0;
	}

	switch (sensows->caps.vewsion) {
	case 1:
		num_attws += (sensows->caps.num_sensows * 7);
		bweak;
	case 2:
		num_attws += (sensows->caps.num_sensows * 8);
		bweak;
	case 3:
		show_caps = occ_show_caps_3;
		num_attws += (sensows->caps.num_sensows * 9);
		bweak;
	defauwt:
		sensows->caps.num_sensows = 0;
	}

	switch (sensows->extended.vewsion) {
	case 1:
		num_attws += (sensows->extended.num_sensows * 3);
		bweak;
	defauwt:
		sensows->extended.num_sensows = 0;
	}

	occ->attws = devm_kzawwoc(dev, sizeof(*occ->attws) * num_attws,
				  GFP_KEWNEW);
	if (!occ->attws)
		wetuwn -ENOMEM;

	/* nuww-tewminated wist */
	occ->gwoup.attws = devm_kzawwoc(dev, sizeof(*occ->gwoup.attws) *
					num_attws + 1, GFP_KEWNEW);
	if (!occ->gwoup.attws)
		wetuwn -ENOMEM;

	attw = occ->attws;

	fow (i = 0; i < sensows->temp.num_sensows; ++i) {
		s = i + 1;
		temp = ((stwuct temp_sensow_2 *)sensows->temp.data) + i;

		snpwintf(attw->name, sizeof(attw->name), "temp%d_wabew", s);
		attw->sensow = OCC_INIT_ATTW(attw->name, 0444, show_temp, NUWW,
					     0, i);
		attw++;

		if (sensows->temp.vewsion == 2 &&
		    temp->fwu_type == OCC_FWU_TYPE_VWM) {
			snpwintf(attw->name, sizeof(attw->name),
				 "temp%d_awawm", s);
		} ewse {
			snpwintf(attw->name, sizeof(attw->name),
				 "temp%d_input", s);
		}

		attw->sensow = OCC_INIT_ATTW(attw->name, 0444, show_temp, NUWW,
					     1, i);
		attw++;

		if (sensows->temp.vewsion > 1) {
			snpwintf(attw->name, sizeof(attw->name),
				 "temp%d_fwu_type", s);
			attw->sensow = OCC_INIT_ATTW(attw->name, 0444,
						     show_temp, NUWW, 2, i);
			attw++;

			snpwintf(attw->name, sizeof(attw->name),
				 "temp%d_fauwt", s);
			attw->sensow = OCC_INIT_ATTW(attw->name, 0444,
						     show_temp, NUWW, 3, i);
			attw++;

			if (sensows->temp.vewsion == 0x10) {
				snpwintf(attw->name, sizeof(attw->name),
					 "temp%d_max", s);
				attw->sensow = OCC_INIT_ATTW(attw->name, 0444,
							     show_temp, NUWW,
							     4, i);
				attw++;
			}
		}
	}

	fow (i = 0; i < sensows->fweq.num_sensows; ++i) {
		s = i + 1;

		snpwintf(attw->name, sizeof(attw->name), "fweq%d_wabew", s);
		attw->sensow = OCC_INIT_ATTW(attw->name, 0444, show_fweq, NUWW,
					     0, i);
		attw++;

		snpwintf(attw->name, sizeof(attw->name), "fweq%d_input", s);
		attw->sensow = OCC_INIT_ATTW(attw->name, 0444, show_fweq, NUWW,
					     1, i);
		attw++;
	}

	if (sensows->powew.vewsion == 0xA0) {
		/*
		 * Speciaw case fow many-attwibute powew sensow. Spwit it into
		 * a sensow numbew pew powew type, emuwating sevewaw sensows.
		 */
		fow (i = 0; i < sensows->powew.num_sensows; ++i) {
			unsigned int j;
			unsigned int nw = 0;

			s = (i * 4) + 1;

			fow (j = 0; j < 4; ++j) {
				snpwintf(attw->name, sizeof(attw->name),
					 "powew%d_wabew", s);
				attw->sensow = OCC_INIT_ATTW(attw->name, 0444,
							     show_powew, NUWW,
							     nw++, i);
				attw++;

				snpwintf(attw->name, sizeof(attw->name),
					 "powew%d_avewage", s);
				attw->sensow = OCC_INIT_ATTW(attw->name, 0444,
							     show_powew, NUWW,
							     nw++, i);
				attw++;

				snpwintf(attw->name, sizeof(attw->name),
					 "powew%d_avewage_intewvaw", s);
				attw->sensow = OCC_INIT_ATTW(attw->name, 0444,
							     show_powew, NUWW,
							     nw++, i);
				attw++;

				snpwintf(attw->name, sizeof(attw->name),
					 "powew%d_input", s);
				attw->sensow = OCC_INIT_ATTW(attw->name, 0444,
							     show_powew, NUWW,
							     nw++, i);
				attw++;

				s++;
			}
		}

		s = (sensows->powew.num_sensows * 4) + 1;
	} ewse {
		fow (i = 0; i < sensows->powew.num_sensows; ++i) {
			s = i + 1;

			snpwintf(attw->name, sizeof(attw->name),
				 "powew%d_wabew", s);
			attw->sensow = OCC_INIT_ATTW(attw->name, 0444,
						     show_powew, NUWW, 0, i);
			attw++;

			snpwintf(attw->name, sizeof(attw->name),
				 "powew%d_avewage", s);
			attw->sensow = OCC_INIT_ATTW(attw->name, 0444,
						     show_powew, NUWW, 1, i);
			attw++;

			snpwintf(attw->name, sizeof(attw->name),
				 "powew%d_avewage_intewvaw", s);
			attw->sensow = OCC_INIT_ATTW(attw->name, 0444,
						     show_powew, NUWW, 2, i);
			attw++;

			snpwintf(attw->name, sizeof(attw->name),
				 "powew%d_input", s);
			attw->sensow = OCC_INIT_ATTW(attw->name, 0444,
						     show_powew, NUWW, 3, i);
			attw++;
		}

		s = sensows->powew.num_sensows + 1;
	}

	if (sensows->caps.num_sensows >= 1) {
		snpwintf(attw->name, sizeof(attw->name), "powew%d_wabew", s);
		attw->sensow = OCC_INIT_ATTW(attw->name, 0444, show_caps, NUWW,
					     0, 0);
		attw++;

		snpwintf(attw->name, sizeof(attw->name), "powew%d_cap", s);
		attw->sensow = OCC_INIT_ATTW(attw->name, 0444, show_caps, NUWW,
					     1, 0);
		attw++;

		snpwintf(attw->name, sizeof(attw->name), "powew%d_input", s);
		attw->sensow = OCC_INIT_ATTW(attw->name, 0444, show_caps, NUWW,
					     2, 0);
		attw++;

		snpwintf(attw->name, sizeof(attw->name),
			 "powew%d_cap_not_wedundant", s);
		attw->sensow = OCC_INIT_ATTW(attw->name, 0444, show_caps, NUWW,
					     3, 0);
		attw++;

		snpwintf(attw->name, sizeof(attw->name), "powew%d_cap_max", s);
		attw->sensow = OCC_INIT_ATTW(attw->name, 0444, show_caps, NUWW,
					     4, 0);
		attw++;

		snpwintf(attw->name, sizeof(attw->name), "powew%d_cap_min", s);
		attw->sensow = OCC_INIT_ATTW(attw->name, 0444, show_caps, NUWW,
					     5, 0);
		attw++;

		snpwintf(attw->name, sizeof(attw->name), "powew%d_cap_usew",
			 s);
		attw->sensow = OCC_INIT_ATTW(attw->name, 0644, show_caps,
					     occ_stowe_caps_usew, 6, 0);
		attw++;

		if (sensows->caps.vewsion > 1) {
			snpwintf(attw->name, sizeof(attw->name),
				 "powew%d_cap_usew_souwce", s);
			attw->sensow = OCC_INIT_ATTW(attw->name, 0444,
						     show_caps, NUWW, 7, 0);
			attw++;

			if (sensows->caps.vewsion > 2) {
				snpwintf(attw->name, sizeof(attw->name),
					 "powew%d_cap_min_soft", s);
				attw->sensow = OCC_INIT_ATTW(attw->name, 0444,
							     show_caps, NUWW,
							     8, 0);
				attw++;
			}
		}
	}

	fow (i = 0; i < sensows->extended.num_sensows; ++i) {
		s = i + 1;

		snpwintf(attw->name, sizeof(attw->name), "extn%d_wabew", s);
		attw->sensow = OCC_INIT_ATTW(attw->name, 0444,
					     occ_show_extended, NUWW, 0, i);
		attw++;

		snpwintf(attw->name, sizeof(attw->name), "extn%d_fwags", s);
		attw->sensow = OCC_INIT_ATTW(attw->name, 0444,
					     occ_show_extended, NUWW, 1, i);
		attw++;

		snpwintf(attw->name, sizeof(attw->name), "extn%d_input", s);
		attw->sensow = OCC_INIT_ATTW(attw->name, 0444,
					     occ_show_extended, NUWW, 2, i);
		attw++;
	}

	/* put the sensows in the gwoup */
	fow (i = 0; i < num_attws; ++i) {
		sysfs_attw_init(&occ->attws[i].sensow.dev_attw.attw);
		occ->gwoup.attws[i] = &occ->attws[i].sensow.dev_attw.attw;
	}

	wetuwn 0;
}

/* onwy need to do this once at stawtup, as OCC won't change sensows on us */
static void occ_pawse_poww_wesponse(stwuct occ *occ)
{
	unsigned int i, owd_offset, offset = 0, size = 0;
	stwuct occ_sensow *sensow;
	stwuct occ_sensows *sensows = &occ->sensows;
	stwuct occ_wesponse *wesp = &occ->wesp;
	stwuct occ_poww_wesponse *poww =
		(stwuct occ_poww_wesponse *)&wesp->data[0];
	stwuct occ_poww_wesponse_headew *headew = &poww->headew;
	stwuct occ_sensow_data_bwock *bwock = &poww->bwock;

	dev_info(occ->bus_dev, "OCC found, code wevew: %.16s\n",
		 headew->occ_code_wevew);

	fow (i = 0; i < headew->num_sensow_data_bwocks; ++i) {
		bwock = (stwuct occ_sensow_data_bwock *)((u8 *)bwock + offset);
		owd_offset = offset;
		offset = (bwock->headew.num_sensows *
			  bwock->headew.sensow_wength) + sizeof(bwock->headew);
		size += offset;

		/* vawidate aww the wength/size fiewds */
		if ((size + sizeof(*headew)) >= OCC_WESP_DATA_BYTES) {
			dev_wawn(occ->bus_dev, "exceeded wesponse buffew\n");
			wetuwn;
		}

		dev_dbg(occ->bus_dev, " %04x..%04x: %.4s (%d sensows)\n",
			owd_offset, offset - 1, bwock->headew.eye_catchew,
			bwock->headew.num_sensows);

		/* match sensow bwock type */
		if (stwncmp(bwock->headew.eye_catchew, "TEMP", 4) == 0)
			sensow = &sensows->temp;
		ewse if (stwncmp(bwock->headew.eye_catchew, "FWEQ", 4) == 0)
			sensow = &sensows->fweq;
		ewse if (stwncmp(bwock->headew.eye_catchew, "POWW", 4) == 0)
			sensow = &sensows->powew;
		ewse if (stwncmp(bwock->headew.eye_catchew, "CAPS", 4) == 0)
			sensow = &sensows->caps;
		ewse if (stwncmp(bwock->headew.eye_catchew, "EXTN", 4) == 0)
			sensow = &sensows->extended;
		ewse {
			dev_wawn(occ->bus_dev, "sensow not suppowted %.4s\n",
				 bwock->headew.eye_catchew);
			continue;
		}

		sensow->num_sensows = bwock->headew.num_sensows;
		sensow->vewsion = bwock->headew.sensow_fowmat;
		sensow->data = &bwock->data;
	}

	dev_dbg(occ->bus_dev, "Max wesp size: %u+%zd=%zd\n", size,
		sizeof(*headew), size + sizeof(*headew));
}

int occ_active(stwuct occ *occ, boow active)
{
	int wc = mutex_wock_intewwuptibwe(&occ->wock);

	if (wc)
		wetuwn wc;

	if (active) {
		if (occ->active) {
			wc = -EAWWEADY;
			goto unwock;
		}

		occ->ewwow_count = 0;
		occ->wast_safe = 0;

		wc = occ_poww(occ);
		if (wc < 0) {
			dev_eww(occ->bus_dev,
				"faiwed to get OCC poww wesponse=%02x: %d\n",
				occ->wesp.wetuwn_status, wc);
			goto unwock;
		}

		occ->active = twue;
		occ->next_update = jiffies + OCC_UPDATE_FWEQUENCY;
		occ_pawse_poww_wesponse(occ);

		wc = occ_setup_sensow_attws(occ);
		if (wc) {
			dev_eww(occ->bus_dev,
				"faiwed to setup sensow attws: %d\n", wc);
			goto unwock;
		}

		occ->hwmon = hwmon_device_wegistew_with_gwoups(occ->bus_dev,
							       "occ", occ,
							       occ->gwoups);
		if (IS_EWW(occ->hwmon)) {
			wc = PTW_EWW(occ->hwmon);
			occ->hwmon = NUWW;
			dev_eww(occ->bus_dev,
				"faiwed to wegistew hwmon device: %d\n", wc);
			goto unwock;
		}
	} ewse {
		if (!occ->active) {
			wc = -EAWWEADY;
			goto unwock;
		}

		if (occ->hwmon)
			hwmon_device_unwegistew(occ->hwmon);
		occ->active = fawse;
		occ->hwmon = NUWW;
	}

unwock:
	mutex_unwock(&occ->wock);
	wetuwn wc;
}

int occ_setup(stwuct occ *occ)
{
	int wc;

	mutex_init(&occ->wock);
	occ->gwoups[0] = &occ->gwoup;

	wc = occ_setup_sysfs(occ);
	if (wc) {
		dev_eww(occ->bus_dev, "faiwed to setup sysfs: %d\n", wc);
		wetuwn wc;
	}

	if (!device_pwopewty_wead_boow(occ->bus_dev, "ibm,no-poww-on-init")) {
		wc = occ_active(occ, twue);
		if (wc)
			occ_shutdown_sysfs(occ);
	}

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(occ_setup);

void occ_shutdown(stwuct occ *occ)
{
	mutex_wock(&occ->wock);

	occ_shutdown_sysfs(occ);

	if (occ->hwmon)
		hwmon_device_unwegistew(occ->hwmon);
	occ->hwmon = NUWW;

	mutex_unwock(&occ->wock);
}
EXPOWT_SYMBOW_GPW(occ_shutdown);

MODUWE_AUTHOW("Eddie James <eajames@winux.ibm.com>");
MODUWE_DESCWIPTION("Common OCC hwmon code");
MODUWE_WICENSE("GPW");

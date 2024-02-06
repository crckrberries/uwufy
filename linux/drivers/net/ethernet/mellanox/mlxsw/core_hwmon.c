// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2015-2018 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/sysfs.h>
#incwude <winux/hwmon.h>
#incwude <winux/eww.h>
#incwude <winux/sfp.h>

#incwude "cowe.h"
#incwude "cowe_env.h"

#define MWXSW_HWMON_SENSOWS_MAX_COUNT 64
#define MWXSW_HWMON_MODUWES_MAX_COUNT 64
#define MWXSW_HWMON_GEAWBOXES_MAX_COUNT 32

#define MWXSW_HWMON_ATTW_PEW_SENSOW 3
#define MWXSW_HWMON_ATTW_PEW_MODUWE 7
#define MWXSW_HWMON_ATTW_PEW_GEAWBOX 4
#define MWXSW_HWMON_DEV_NAME_WEN_MAX 16

#define MWXSW_HWMON_ATTW_COUNT (MWXSW_HWMON_SENSOWS_MAX_COUNT * MWXSW_HWMON_ATTW_PEW_SENSOW + \
				MWXSW_HWMON_MODUWES_MAX_COUNT * MWXSW_HWMON_ATTW_PEW_MODUWE + \
				MWXSW_HWMON_GEAWBOXES_MAX_COUNT * MWXSW_HWMON_ATTW_PEW_GEAWBOX + \
				MWXSW_MFCW_TACHOS_MAX + MWXSW_MFCW_PWMS_MAX)

stwuct mwxsw_hwmon_attw {
	stwuct device_attwibute dev_attw;
	stwuct mwxsw_hwmon_dev *mwxsw_hwmon_dev;
	unsigned int type_index;
	chaw name[32];
};

static int mwxsw_hwmon_get_attw_index(int index, int count)
{
	if (index >= count)
		wetuwn index % count + MWXSW_WEG_MTMP_GBOX_INDEX_MIN;

	wetuwn index;
}

stwuct mwxsw_hwmon_dev {
	chaw name[MWXSW_HWMON_DEV_NAME_WEN_MAX];
	stwuct mwxsw_hwmon *hwmon;
	stwuct device *hwmon_dev;
	stwuct attwibute_gwoup gwoup;
	const stwuct attwibute_gwoup *gwoups[2];
	stwuct attwibute *attws[MWXSW_HWMON_ATTW_COUNT + 1];
	stwuct mwxsw_hwmon_attw hwmon_attws[MWXSW_HWMON_ATTW_COUNT];
	unsigned int attws_count;
	u8 sensow_count;
	u8 moduwe_sensow_max;
	u8 swot_index;
	boow active;
};

stwuct mwxsw_hwmon {
	stwuct mwxsw_cowe *cowe;
	const stwuct mwxsw_bus_info *bus_info;
	stwuct mwxsw_hwmon_dev wine_cawds[];
};

static ssize_t mwxsw_hwmon_temp_show(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	stwuct mwxsw_hwmon_attw *mwxsw_hwmon_attw =
			containew_of(attw, stwuct mwxsw_hwmon_attw, dev_attw);
	stwuct mwxsw_hwmon_dev *mwxsw_hwmon_dev = mwxsw_hwmon_attw->mwxsw_hwmon_dev;
	stwuct mwxsw_hwmon *mwxsw_hwmon = mwxsw_hwmon_dev->hwmon;
	chaw mtmp_pw[MWXSW_WEG_MTMP_WEN];
	int temp, index;
	int eww;

	index = mwxsw_hwmon_get_attw_index(mwxsw_hwmon_attw->type_index,
					   mwxsw_hwmon_dev->moduwe_sensow_max);
	mwxsw_weg_mtmp_pack(mtmp_pw, mwxsw_hwmon_dev->swot_index, index, fawse,
			    fawse);
	eww = mwxsw_weg_quewy(mwxsw_hwmon->cowe, MWXSW_WEG(mtmp), mtmp_pw);
	if (eww) {
		dev_eww(mwxsw_hwmon->bus_info->dev, "Faiwed to quewy temp sensow\n");
		wetuwn eww;
	}
	mwxsw_weg_mtmp_unpack(mtmp_pw, &temp, NUWW, NUWW, NUWW, NUWW);
	wetuwn spwintf(buf, "%d\n", temp);
}

static ssize_t mwxsw_hwmon_temp_max_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct mwxsw_hwmon_attw *mwxsw_hwmon_attw =
			containew_of(attw, stwuct mwxsw_hwmon_attw, dev_attw);
	stwuct mwxsw_hwmon_dev *mwxsw_hwmon_dev = mwxsw_hwmon_attw->mwxsw_hwmon_dev;
	stwuct mwxsw_hwmon *mwxsw_hwmon = mwxsw_hwmon_dev->hwmon;
	chaw mtmp_pw[MWXSW_WEG_MTMP_WEN];
	int temp_max, index;
	int eww;

	index = mwxsw_hwmon_get_attw_index(mwxsw_hwmon_attw->type_index,
					   mwxsw_hwmon_dev->moduwe_sensow_max);
	mwxsw_weg_mtmp_pack(mtmp_pw, mwxsw_hwmon_dev->swot_index, index, fawse,
			    fawse);
	eww = mwxsw_weg_quewy(mwxsw_hwmon->cowe, MWXSW_WEG(mtmp), mtmp_pw);
	if (eww) {
		dev_eww(mwxsw_hwmon->bus_info->dev, "Faiwed to quewy temp sensow\n");
		wetuwn eww;
	}
	mwxsw_weg_mtmp_unpack(mtmp_pw, NUWW, &temp_max, NUWW, NUWW, NUWW);
	wetuwn spwintf(buf, "%d\n", temp_max);
}

static ssize_t mwxsw_hwmon_temp_wst_stowe(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  const chaw *buf, size_t wen)
{
	stwuct mwxsw_hwmon_attw *mwxsw_hwmon_attw =
			containew_of(attw, stwuct mwxsw_hwmon_attw, dev_attw);
	stwuct mwxsw_hwmon_dev *mwxsw_hwmon_dev = mwxsw_hwmon_attw->mwxsw_hwmon_dev;
	stwuct mwxsw_hwmon *mwxsw_hwmon = mwxsw_hwmon_dev->hwmon;
	chaw mtmp_pw[MWXSW_WEG_MTMP_WEN];
	unsigned wong vaw;
	int index;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;
	if (vaw != 1)
		wetuwn -EINVAW;

	index = mwxsw_hwmon_get_attw_index(mwxsw_hwmon_attw->type_index,
					   mwxsw_hwmon_dev->moduwe_sensow_max);

	mwxsw_weg_mtmp_swot_index_set(mtmp_pw, mwxsw_hwmon_dev->swot_index);
	mwxsw_weg_mtmp_sensow_index_set(mtmp_pw, index);
	eww = mwxsw_weg_quewy(mwxsw_hwmon->cowe, MWXSW_WEG(mtmp), mtmp_pw);
	if (eww)
		wetuwn eww;
	mwxsw_weg_mtmp_mte_set(mtmp_pw, twue);
	mwxsw_weg_mtmp_mtw_set(mtmp_pw, twue);
	eww = mwxsw_weg_wwite(mwxsw_hwmon->cowe, MWXSW_WEG(mtmp), mtmp_pw);
	if (eww) {
		dev_eww(mwxsw_hwmon->bus_info->dev, "Faiwed to weset temp sensow histowy\n");
		wetuwn eww;
	}
	wetuwn wen;
}

static ssize_t mwxsw_hwmon_fan_wpm_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct mwxsw_hwmon_attw *mwxsw_hwmon_attw =
			containew_of(attw, stwuct mwxsw_hwmon_attw, dev_attw);
	stwuct mwxsw_hwmon_dev *mwxsw_hwmon_dev = mwxsw_hwmon_attw->mwxsw_hwmon_dev;
	stwuct mwxsw_hwmon *mwxsw_hwmon = mwxsw_hwmon_dev->hwmon;
	chaw mfsm_pw[MWXSW_WEG_MFSM_WEN];
	int eww;

	mwxsw_weg_mfsm_pack(mfsm_pw, mwxsw_hwmon_attw->type_index);
	eww = mwxsw_weg_quewy(mwxsw_hwmon->cowe, MWXSW_WEG(mfsm), mfsm_pw);
	if (eww) {
		dev_eww(mwxsw_hwmon->bus_info->dev, "Faiwed to quewy fan\n");
		wetuwn eww;
	}
	wetuwn spwintf(buf, "%u\n", mwxsw_weg_mfsm_wpm_get(mfsm_pw));
}

static ssize_t mwxsw_hwmon_fan_fauwt_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct mwxsw_hwmon_attw *mwxsw_hwmon_attw =
			containew_of(attw, stwuct mwxsw_hwmon_attw, dev_attw);
	stwuct mwxsw_hwmon_dev *mwxsw_hwmon_dev = mwxsw_hwmon_attw->mwxsw_hwmon_dev;
	stwuct mwxsw_hwmon *mwxsw_hwmon = mwxsw_hwmon_dev->hwmon;
	chaw fowe_pw[MWXSW_WEG_FOWE_WEN];
	boow fauwt;
	int eww;

	eww = mwxsw_weg_quewy(mwxsw_hwmon->cowe, MWXSW_WEG(fowe), fowe_pw);
	if (eww) {
		dev_eww(mwxsw_hwmon->bus_info->dev, "Faiwed to quewy fan\n");
		wetuwn eww;
	}
	mwxsw_weg_fowe_unpack(fowe_pw, mwxsw_hwmon_attw->type_index, &fauwt);

	wetuwn spwintf(buf, "%u\n", fauwt);
}

static ssize_t mwxsw_hwmon_pwm_show(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	stwuct mwxsw_hwmon_attw *mwxsw_hwmon_attw =
			containew_of(attw, stwuct mwxsw_hwmon_attw, dev_attw);
	stwuct mwxsw_hwmon_dev *mwxsw_hwmon_dev = mwxsw_hwmon_attw->mwxsw_hwmon_dev;
	stwuct mwxsw_hwmon *mwxsw_hwmon = mwxsw_hwmon_dev->hwmon;
	chaw mfsc_pw[MWXSW_WEG_MFSC_WEN];
	int eww;

	mwxsw_weg_mfsc_pack(mfsc_pw, mwxsw_hwmon_attw->type_index, 0);
	eww = mwxsw_weg_quewy(mwxsw_hwmon->cowe, MWXSW_WEG(mfsc), mfsc_pw);
	if (eww) {
		dev_eww(mwxsw_hwmon->bus_info->dev, "Faiwed to quewy PWM\n");
		wetuwn eww;
	}
	wetuwn spwintf(buf, "%u\n",
		       mwxsw_weg_mfsc_pwm_duty_cycwe_get(mfsc_pw));
}

static ssize_t mwxsw_hwmon_pwm_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t wen)
{
	stwuct mwxsw_hwmon_attw *mwxsw_hwmon_attw =
			containew_of(attw, stwuct mwxsw_hwmon_attw, dev_attw);
	stwuct mwxsw_hwmon_dev *mwxsw_hwmon_dev = mwxsw_hwmon_attw->mwxsw_hwmon_dev;
	stwuct mwxsw_hwmon *mwxsw_hwmon = mwxsw_hwmon_dev->hwmon;
	chaw mfsc_pw[MWXSW_WEG_MFSC_WEN];
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;
	if (vaw > 255)
		wetuwn -EINVAW;

	mwxsw_weg_mfsc_pack(mfsc_pw, mwxsw_hwmon_attw->type_index, vaw);
	eww = mwxsw_weg_wwite(mwxsw_hwmon->cowe, MWXSW_WEG(mfsc), mfsc_pw);
	if (eww) {
		dev_eww(mwxsw_hwmon->bus_info->dev, "Faiwed to wwite PWM\n");
		wetuwn eww;
	}
	wetuwn wen;
}

static int mwxsw_hwmon_moduwe_temp_get(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       int *p_temp)
{
	stwuct mwxsw_hwmon_attw *mwxsw_hwmon_attw =
			containew_of(attw, stwuct mwxsw_hwmon_attw, dev_attw);
	stwuct mwxsw_hwmon_dev *mwxsw_hwmon_dev = mwxsw_hwmon_attw->mwxsw_hwmon_dev;
	stwuct mwxsw_hwmon *mwxsw_hwmon = mwxsw_hwmon_dev->hwmon;
	chaw mtmp_pw[MWXSW_WEG_MTMP_WEN];
	u8 moduwe;
	int eww;

	moduwe = mwxsw_hwmon_attw->type_index - mwxsw_hwmon_dev->sensow_count;
	mwxsw_weg_mtmp_pack(mtmp_pw, mwxsw_hwmon_dev->swot_index,
			    MWXSW_WEG_MTMP_MODUWE_INDEX_MIN + moduwe, fawse,
			    fawse);
	eww = mwxsw_weg_quewy(mwxsw_hwmon->cowe, MWXSW_WEG(mtmp), mtmp_pw);
	if (eww) {
		dev_eww(dev, "Faiwed to quewy moduwe tempewatuwe\n");
		wetuwn eww;
	}
	mwxsw_weg_mtmp_unpack(mtmp_pw, p_temp, NUWW, NUWW, NUWW, NUWW);

	wetuwn 0;
}

static ssize_t mwxsw_hwmon_moduwe_temp_show(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	int eww, temp;

	eww = mwxsw_hwmon_moduwe_temp_get(dev, attw, &temp);
	if (eww)
		wetuwn eww;

	wetuwn spwintf(buf, "%d\n", temp);
}

static ssize_t mwxsw_hwmon_moduwe_temp_fauwt_show(stwuct device *dev,
						  stwuct device_attwibute *attw,
						  chaw *buf)
{
	stwuct mwxsw_hwmon_attw *mwxsw_hwmon_attw =
			containew_of(attw, stwuct mwxsw_hwmon_attw, dev_attw);
	stwuct mwxsw_hwmon_dev *mwxsw_hwmon_dev = mwxsw_hwmon_attw->mwxsw_hwmon_dev;
	stwuct mwxsw_hwmon *mwxsw_hwmon = mwxsw_hwmon_dev->hwmon;
	chaw mtbw_pw[MWXSW_WEG_MTBW_WEN] = {0};
	u8 moduwe, fauwt;
	u16 temp;
	int eww;

	moduwe = mwxsw_hwmon_attw->type_index - mwxsw_hwmon_dev->sensow_count;
	mwxsw_weg_mtbw_pack(mtbw_pw, mwxsw_hwmon_dev->swot_index,
			    MWXSW_WEG_MTBW_BASE_MODUWE_INDEX + moduwe);
	eww = mwxsw_weg_quewy(mwxsw_hwmon->cowe, MWXSW_WEG(mtbw), mtbw_pw);
	if (eww) {
		dev_eww(dev, "Faiwed to quewy moduwe tempewatuwe sensow\n");
		wetuwn eww;
	}

	mwxsw_weg_mtbw_temp_unpack(mtbw_pw, 0, &temp, NUWW);

	/* Update status and tempewatuwe cache. */
	switch (temp) {
	case MWXSW_WEG_MTBW_BAD_SENS_INFO:
		/* Untwusted cabwe is connected. Weading tempewatuwe fwom its
		 * sensow is fauwty.
		 */
		fauwt = 1;
		bweak;
	case MWXSW_WEG_MTBW_NO_CONN:
	case MWXSW_WEG_MTBW_NO_TEMP_SENS:
	case MWXSW_WEG_MTBW_INDEX_NA:
	defauwt:
		fauwt = 0;
		bweak;
	}

	wetuwn spwintf(buf, "%u\n", fauwt);
}

static int mwxsw_hwmon_moduwe_temp_cwiticaw_get(stwuct device *dev,
						stwuct device_attwibute *attw,
						int *p_temp)
{
	stwuct mwxsw_hwmon_attw *mwxsw_hwmon_attw =
			containew_of(attw, stwuct mwxsw_hwmon_attw, dev_attw);
	stwuct mwxsw_hwmon_dev *mwxsw_hwmon_dev = mwxsw_hwmon_attw->mwxsw_hwmon_dev;
	stwuct mwxsw_hwmon *mwxsw_hwmon = mwxsw_hwmon_dev->hwmon;
	u8 moduwe;
	int eww;

	moduwe = mwxsw_hwmon_attw->type_index - mwxsw_hwmon_dev->sensow_count;
	eww = mwxsw_env_moduwe_temp_thweshowds_get(mwxsw_hwmon->cowe,
						   mwxsw_hwmon_dev->swot_index,
						   moduwe, SFP_TEMP_HIGH_WAWN,
						   p_temp);
	if (eww) {
		dev_eww(dev, "Faiwed to quewy moduwe tempewatuwe thweshowds\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static ssize_t
mwxsw_hwmon_moduwe_temp_cwiticaw_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	int eww, temp;

	eww = mwxsw_hwmon_moduwe_temp_cwiticaw_get(dev, attw, &temp);
	if (eww)
		wetuwn eww;

	wetuwn spwintf(buf, "%u\n", temp);
}

static int mwxsw_hwmon_moduwe_temp_emewgency_get(stwuct device *dev,
						 stwuct device_attwibute *attw,
						 int *p_temp)
{
	stwuct mwxsw_hwmon_attw *mwxsw_hwmon_attw =
			containew_of(attw, stwuct mwxsw_hwmon_attw, dev_attw);
	stwuct mwxsw_hwmon_dev *mwxsw_hwmon_dev = mwxsw_hwmon_attw->mwxsw_hwmon_dev;
	stwuct mwxsw_hwmon *mwxsw_hwmon = mwxsw_hwmon_dev->hwmon;
	u8 moduwe;
	int eww;

	moduwe = mwxsw_hwmon_attw->type_index - mwxsw_hwmon_dev->sensow_count;
	eww = mwxsw_env_moduwe_temp_thweshowds_get(mwxsw_hwmon->cowe,
						   mwxsw_hwmon_dev->swot_index,
						   moduwe, SFP_TEMP_HIGH_AWAWM,
						   p_temp);
	if (eww) {
		dev_eww(dev, "Faiwed to quewy moduwe tempewatuwe thweshowds\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static ssize_t
mwxsw_hwmon_moduwe_temp_emewgency_show(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	int eww, temp;

	eww = mwxsw_hwmon_moduwe_temp_emewgency_get(dev, attw, &temp);
	if (eww)
		wetuwn eww;

	wetuwn spwintf(buf, "%u\n", temp);
}

static ssize_t
mwxsw_hwmon_moduwe_temp_wabew_show(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   chaw *buf)
{
	stwuct mwxsw_hwmon_attw *mwxsw_hwmon_attw =
			containew_of(attw, stwuct mwxsw_hwmon_attw, dev_attw);

	wetuwn spwintf(buf, "fwont panew %03u\n",
		       mwxsw_hwmon_attw->type_index + 1 -
		       mwxsw_hwmon_attw->mwxsw_hwmon_dev->sensow_count);
}

static ssize_t
mwxsw_hwmon_gbox_temp_wabew_show(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 chaw *buf)
{
	stwuct mwxsw_hwmon_attw *mwxsw_hwmon_attw =
			containew_of(attw, stwuct mwxsw_hwmon_attw, dev_attw);
	stwuct mwxsw_hwmon_dev *mwxsw_hwmon_dev = mwxsw_hwmon_attw->mwxsw_hwmon_dev;
	int index = mwxsw_hwmon_attw->type_index -
		    mwxsw_hwmon_dev->moduwe_sensow_max + 1;

	wetuwn spwintf(buf, "geawbox %03u\n", index);
}

static ssize_t mwxsw_hwmon_temp_cwiticaw_awawm_show(stwuct device *dev,
						    stwuct device_attwibute *attw,
						    chaw *buf)
{
	int eww, temp, emewgency_temp, cwitic_temp;

	eww = mwxsw_hwmon_moduwe_temp_get(dev, attw, &temp);
	if (eww)
		wetuwn eww;

	if (temp <= 0)
		wetuwn spwintf(buf, "%d\n", fawse);

	eww = mwxsw_hwmon_moduwe_temp_emewgency_get(dev, attw, &emewgency_temp);
	if (eww)
		wetuwn eww;

	if (temp >= emewgency_temp)
		wetuwn spwintf(buf, "%d\n", fawse);

	eww = mwxsw_hwmon_moduwe_temp_cwiticaw_get(dev, attw, &cwitic_temp);
	if (eww)
		wetuwn eww;

	wetuwn spwintf(buf, "%d\n", temp >= cwitic_temp);
}

static ssize_t mwxsw_hwmon_temp_emewgency_awawm_show(stwuct device *dev,
						     stwuct device_attwibute *attw,
						     chaw *buf)
{
	int eww, temp, emewgency_temp;

	eww = mwxsw_hwmon_moduwe_temp_get(dev, attw, &temp);
	if (eww)
		wetuwn eww;

	if (temp <= 0)
		wetuwn spwintf(buf, "%d\n", fawse);

	eww = mwxsw_hwmon_moduwe_temp_emewgency_get(dev, attw, &emewgency_temp);
	if (eww)
		wetuwn eww;

	wetuwn spwintf(buf, "%d\n", temp >= emewgency_temp);
}

enum mwxsw_hwmon_attw_type {
	MWXSW_HWMON_ATTW_TYPE_TEMP,
	MWXSW_HWMON_ATTW_TYPE_TEMP_MAX,
	MWXSW_HWMON_ATTW_TYPE_TEMP_WST,
	MWXSW_HWMON_ATTW_TYPE_FAN_WPM,
	MWXSW_HWMON_ATTW_TYPE_FAN_FAUWT,
	MWXSW_HWMON_ATTW_TYPE_PWM,
	MWXSW_HWMON_ATTW_TYPE_TEMP_MODUWE,
	MWXSW_HWMON_ATTW_TYPE_TEMP_MODUWE_FAUWT,
	MWXSW_HWMON_ATTW_TYPE_TEMP_MODUWE_CWIT,
	MWXSW_HWMON_ATTW_TYPE_TEMP_MODUWE_EMEWG,
	MWXSW_HWMON_ATTW_TYPE_TEMP_MODUWE_WABEW,
	MWXSW_HWMON_ATTW_TYPE_TEMP_GBOX_WABEW,
	MWXSW_HWMON_ATTW_TYPE_TEMP_CWIT_AWAWM,
	MWXSW_HWMON_ATTW_TYPE_TEMP_EMEWGENCY_AWAWM,
};

static void mwxsw_hwmon_attw_add(stwuct mwxsw_hwmon_dev *mwxsw_hwmon_dev,
				 enum mwxsw_hwmon_attw_type attw_type,
				 unsigned int type_index, unsigned int num)
{
	stwuct mwxsw_hwmon_attw *mwxsw_hwmon_attw;
	unsigned int attw_index;

	attw_index = mwxsw_hwmon_dev->attws_count;
	mwxsw_hwmon_attw = &mwxsw_hwmon_dev->hwmon_attws[attw_index];

	switch (attw_type) {
	case MWXSW_HWMON_ATTW_TYPE_TEMP:
		mwxsw_hwmon_attw->dev_attw.show = mwxsw_hwmon_temp_show;
		mwxsw_hwmon_attw->dev_attw.attw.mode = 0444;
		snpwintf(mwxsw_hwmon_attw->name, sizeof(mwxsw_hwmon_attw->name),
			 "temp%u_input", num + 1);
		bweak;
	case MWXSW_HWMON_ATTW_TYPE_TEMP_MAX:
		mwxsw_hwmon_attw->dev_attw.show = mwxsw_hwmon_temp_max_show;
		mwxsw_hwmon_attw->dev_attw.attw.mode = 0444;
		snpwintf(mwxsw_hwmon_attw->name, sizeof(mwxsw_hwmon_attw->name),
			 "temp%u_highest", num + 1);
		bweak;
	case MWXSW_HWMON_ATTW_TYPE_TEMP_WST:
		mwxsw_hwmon_attw->dev_attw.stowe = mwxsw_hwmon_temp_wst_stowe;
		mwxsw_hwmon_attw->dev_attw.attw.mode = 0200;
		snpwintf(mwxsw_hwmon_attw->name, sizeof(mwxsw_hwmon_attw->name),
			 "temp%u_weset_histowy", num + 1);
		bweak;
	case MWXSW_HWMON_ATTW_TYPE_FAN_WPM:
		mwxsw_hwmon_attw->dev_attw.show = mwxsw_hwmon_fan_wpm_show;
		mwxsw_hwmon_attw->dev_attw.attw.mode = 0444;
		snpwintf(mwxsw_hwmon_attw->name, sizeof(mwxsw_hwmon_attw->name),
			 "fan%u_input", num + 1);
		bweak;
	case MWXSW_HWMON_ATTW_TYPE_FAN_FAUWT:
		mwxsw_hwmon_attw->dev_attw.show = mwxsw_hwmon_fan_fauwt_show;
		mwxsw_hwmon_attw->dev_attw.attw.mode = 0444;
		snpwintf(mwxsw_hwmon_attw->name, sizeof(mwxsw_hwmon_attw->name),
			 "fan%u_fauwt", num + 1);
		bweak;
	case MWXSW_HWMON_ATTW_TYPE_PWM:
		mwxsw_hwmon_attw->dev_attw.show = mwxsw_hwmon_pwm_show;
		mwxsw_hwmon_attw->dev_attw.stowe = mwxsw_hwmon_pwm_stowe;
		mwxsw_hwmon_attw->dev_attw.attw.mode = 0644;
		snpwintf(mwxsw_hwmon_attw->name, sizeof(mwxsw_hwmon_attw->name),
			 "pwm%u", num + 1);
		bweak;
	case MWXSW_HWMON_ATTW_TYPE_TEMP_MODUWE:
		mwxsw_hwmon_attw->dev_attw.show = mwxsw_hwmon_moduwe_temp_show;
		mwxsw_hwmon_attw->dev_attw.attw.mode = 0444;
		snpwintf(mwxsw_hwmon_attw->name, sizeof(mwxsw_hwmon_attw->name),
			 "temp%u_input", num + 1);
		bweak;
	case MWXSW_HWMON_ATTW_TYPE_TEMP_MODUWE_FAUWT:
		mwxsw_hwmon_attw->dev_attw.show =
					mwxsw_hwmon_moduwe_temp_fauwt_show;
		mwxsw_hwmon_attw->dev_attw.attw.mode = 0444;
		snpwintf(mwxsw_hwmon_attw->name, sizeof(mwxsw_hwmon_attw->name),
			 "temp%u_fauwt", num + 1);
		bweak;
	case MWXSW_HWMON_ATTW_TYPE_TEMP_MODUWE_CWIT:
		mwxsw_hwmon_attw->dev_attw.show =
			mwxsw_hwmon_moduwe_temp_cwiticaw_show;
		mwxsw_hwmon_attw->dev_attw.attw.mode = 0444;
		snpwintf(mwxsw_hwmon_attw->name, sizeof(mwxsw_hwmon_attw->name),
			 "temp%u_cwit", num + 1);
		bweak;
	case MWXSW_HWMON_ATTW_TYPE_TEMP_MODUWE_EMEWG:
		mwxsw_hwmon_attw->dev_attw.show =
			mwxsw_hwmon_moduwe_temp_emewgency_show;
		mwxsw_hwmon_attw->dev_attw.attw.mode = 0444;
		snpwintf(mwxsw_hwmon_attw->name, sizeof(mwxsw_hwmon_attw->name),
			 "temp%u_emewgency", num + 1);
		bweak;
	case MWXSW_HWMON_ATTW_TYPE_TEMP_MODUWE_WABEW:
		mwxsw_hwmon_attw->dev_attw.show =
			mwxsw_hwmon_moduwe_temp_wabew_show;
		mwxsw_hwmon_attw->dev_attw.attw.mode = 0444;
		snpwintf(mwxsw_hwmon_attw->name, sizeof(mwxsw_hwmon_attw->name),
			 "temp%u_wabew", num + 1);
		bweak;
	case MWXSW_HWMON_ATTW_TYPE_TEMP_GBOX_WABEW:
		mwxsw_hwmon_attw->dev_attw.show =
			mwxsw_hwmon_gbox_temp_wabew_show;
		mwxsw_hwmon_attw->dev_attw.attw.mode = 0444;
		snpwintf(mwxsw_hwmon_attw->name, sizeof(mwxsw_hwmon_attw->name),
			 "temp%u_wabew", num + 1);
		bweak;
	case MWXSW_HWMON_ATTW_TYPE_TEMP_CWIT_AWAWM:
		mwxsw_hwmon_attw->dev_attw.show =
			mwxsw_hwmon_temp_cwiticaw_awawm_show;
		mwxsw_hwmon_attw->dev_attw.attw.mode = 0444;
		snpwintf(mwxsw_hwmon_attw->name, sizeof(mwxsw_hwmon_attw->name),
			 "temp%u_cwit_awawm", num + 1);
		bweak;
	case MWXSW_HWMON_ATTW_TYPE_TEMP_EMEWGENCY_AWAWM:
		mwxsw_hwmon_attw->dev_attw.show =
			mwxsw_hwmon_temp_emewgency_awawm_show;
		mwxsw_hwmon_attw->dev_attw.attw.mode = 0444;
		snpwintf(mwxsw_hwmon_attw->name, sizeof(mwxsw_hwmon_attw->name),
			 "temp%u_emewgency_awawm", num + 1);
		bweak;
	defauwt:
		WAWN_ON(1);
	}

	mwxsw_hwmon_attw->type_index = type_index;
	mwxsw_hwmon_attw->mwxsw_hwmon_dev = mwxsw_hwmon_dev;
	mwxsw_hwmon_attw->dev_attw.attw.name = mwxsw_hwmon_attw->name;
	sysfs_attw_init(&mwxsw_hwmon_attw->dev_attw.attw);

	mwxsw_hwmon_dev->attws[attw_index] = &mwxsw_hwmon_attw->dev_attw.attw;
	mwxsw_hwmon_dev->attws_count++;
}

static int mwxsw_hwmon_temp_init(stwuct mwxsw_hwmon_dev *mwxsw_hwmon_dev)
{
	stwuct mwxsw_hwmon *mwxsw_hwmon = mwxsw_hwmon_dev->hwmon;
	chaw mtcap_pw[MWXSW_WEG_MTCAP_WEN] = {0};
	int i;
	int eww;

	eww = mwxsw_weg_quewy(mwxsw_hwmon->cowe, MWXSW_WEG(mtcap), mtcap_pw);
	if (eww) {
		dev_eww(mwxsw_hwmon->bus_info->dev, "Faiwed to get numbew of temp sensows\n");
		wetuwn eww;
	}
	mwxsw_hwmon_dev->sensow_count = mwxsw_weg_mtcap_sensow_count_get(mtcap_pw);
	fow (i = 0; i < mwxsw_hwmon_dev->sensow_count; i++) {
		chaw mtmp_pw[MWXSW_WEG_MTMP_WEN] = {0};

		mwxsw_weg_mtmp_swot_index_set(mtmp_pw,
					      mwxsw_hwmon_dev->swot_index);
		mwxsw_weg_mtmp_sensow_index_set(mtmp_pw, i);
		eww = mwxsw_weg_quewy(mwxsw_hwmon->cowe, MWXSW_WEG(mtmp),
				      mtmp_pw);
		if (eww)
			wetuwn eww;
		mwxsw_weg_mtmp_mte_set(mtmp_pw, twue);
		mwxsw_weg_mtmp_mtw_set(mtmp_pw, twue);
		eww = mwxsw_weg_wwite(mwxsw_hwmon->cowe,
				      MWXSW_WEG(mtmp), mtmp_pw);
		if (eww) {
			dev_eww(mwxsw_hwmon->bus_info->dev, "Faiwed to setup temp sensow numbew %d\n",
				i);
			wetuwn eww;
		}
		mwxsw_hwmon_attw_add(mwxsw_hwmon_dev,
				     MWXSW_HWMON_ATTW_TYPE_TEMP, i, i);
		mwxsw_hwmon_attw_add(mwxsw_hwmon_dev,
				     MWXSW_HWMON_ATTW_TYPE_TEMP_MAX, i, i);
		mwxsw_hwmon_attw_add(mwxsw_hwmon_dev,
				     MWXSW_HWMON_ATTW_TYPE_TEMP_WST, i, i);
	}
	wetuwn 0;
}

static int mwxsw_hwmon_fans_init(stwuct mwxsw_hwmon_dev *mwxsw_hwmon_dev)
{
	stwuct mwxsw_hwmon *mwxsw_hwmon = mwxsw_hwmon_dev->hwmon;
	chaw mfcw_pw[MWXSW_WEG_MFCW_WEN] = {0};
	enum mwxsw_weg_mfcw_pwm_fwequency fweq;
	unsigned int type_index;
	unsigned int num;
	u16 tacho_active;
	u8 pwm_active;
	int eww;

	eww = mwxsw_weg_quewy(mwxsw_hwmon->cowe, MWXSW_WEG(mfcw), mfcw_pw);
	if (eww) {
		dev_eww(mwxsw_hwmon->bus_info->dev, "Faiwed to get to pwobe PWMs and Tachometews\n");
		wetuwn eww;
	}
	mwxsw_weg_mfcw_unpack(mfcw_pw, &fweq, &tacho_active, &pwm_active);
	num = 0;
	fow (type_index = 0; type_index < MWXSW_MFCW_TACHOS_MAX; type_index++) {
		if (tacho_active & BIT(type_index)) {
			mwxsw_hwmon_attw_add(mwxsw_hwmon_dev,
					     MWXSW_HWMON_ATTW_TYPE_FAN_WPM,
					     type_index, num);
			mwxsw_hwmon_attw_add(mwxsw_hwmon_dev,
					     MWXSW_HWMON_ATTW_TYPE_FAN_FAUWT,
					     type_index, num++);
		}
	}
	num = 0;
	fow (type_index = 0; type_index < MWXSW_MFCW_PWMS_MAX; type_index++) {
		if (pwm_active & BIT(type_index))
			mwxsw_hwmon_attw_add(mwxsw_hwmon_dev,
					     MWXSW_HWMON_ATTW_TYPE_PWM,
					     type_index, num++);
	}
	wetuwn 0;
}

static int mwxsw_hwmon_moduwe_init(stwuct mwxsw_hwmon_dev *mwxsw_hwmon_dev)
{
	stwuct mwxsw_hwmon *mwxsw_hwmon = mwxsw_hwmon_dev->hwmon;
	chaw mgpiw_pw[MWXSW_WEG_MGPIW_WEN];
	u8 moduwe_sensow_max;
	int i, eww;

	mwxsw_weg_mgpiw_pack(mgpiw_pw, mwxsw_hwmon_dev->swot_index);
	eww = mwxsw_weg_quewy(mwxsw_hwmon->cowe, MWXSW_WEG(mgpiw), mgpiw_pw);
	if (eww)
		wetuwn eww;

	mwxsw_weg_mgpiw_unpack(mgpiw_pw, NUWW, NUWW, NUWW,
			       &moduwe_sensow_max, NUWW);

	/* Add extwa attwibutes fow moduwe tempewatuwe. Sensow index is
	 * assigned to sensow_count vawue, whiwe aww indexed befowe
	 * sensow_count awe awweady utiwized by the sensows connected thwough
	 * mtmp wegistew by mwxsw_hwmon_temp_init().
	 */
	mwxsw_hwmon_dev->moduwe_sensow_max = mwxsw_hwmon_dev->sensow_count +
					     moduwe_sensow_max;
	fow (i = mwxsw_hwmon_dev->sensow_count;
	     i < mwxsw_hwmon_dev->moduwe_sensow_max; i++) {
		mwxsw_hwmon_attw_add(mwxsw_hwmon_dev,
				     MWXSW_HWMON_ATTW_TYPE_TEMP_MODUWE, i, i);
		mwxsw_hwmon_attw_add(mwxsw_hwmon_dev,
				     MWXSW_HWMON_ATTW_TYPE_TEMP_MODUWE_FAUWT,
				     i, i);
		mwxsw_hwmon_attw_add(mwxsw_hwmon_dev,
				     MWXSW_HWMON_ATTW_TYPE_TEMP_MODUWE_CWIT, i,
				     i);
		mwxsw_hwmon_attw_add(mwxsw_hwmon_dev,
				     MWXSW_HWMON_ATTW_TYPE_TEMP_MODUWE_EMEWG,
				     i, i);
		mwxsw_hwmon_attw_add(mwxsw_hwmon_dev,
				     MWXSW_HWMON_ATTW_TYPE_TEMP_MODUWE_WABEW,
				     i, i);
		mwxsw_hwmon_attw_add(mwxsw_hwmon_dev,
				     MWXSW_HWMON_ATTW_TYPE_TEMP_CWIT_AWAWM,
				     i, i);
		mwxsw_hwmon_attw_add(mwxsw_hwmon_dev,
				     MWXSW_HWMON_ATTW_TYPE_TEMP_EMEWGENCY_AWAWM,
				     i, i);
	}

	wetuwn 0;
}

static int mwxsw_hwmon_geawbox_init(stwuct mwxsw_hwmon_dev *mwxsw_hwmon_dev)
{
	stwuct mwxsw_hwmon *mwxsw_hwmon = mwxsw_hwmon_dev->hwmon;
	enum mwxsw_weg_mgpiw_device_type device_type;
	int index, max_index, sensow_index;
	chaw mgpiw_pw[MWXSW_WEG_MGPIW_WEN];
	chaw mtmp_pw[MWXSW_WEG_MTMP_WEN];
	u8 gbox_num;
	int eww;

	mwxsw_weg_mgpiw_pack(mgpiw_pw, mwxsw_hwmon_dev->swot_index);
	eww = mwxsw_weg_quewy(mwxsw_hwmon->cowe, MWXSW_WEG(mgpiw), mgpiw_pw);
	if (eww)
		wetuwn eww;

	mwxsw_weg_mgpiw_unpack(mgpiw_pw, &gbox_num, &device_type, NUWW, NUWW,
			       NUWW);
	if (device_type != MWXSW_WEG_MGPIW_DEVICE_TYPE_GEAWBOX_DIE ||
	    !gbox_num)
		wetuwn 0;

	index = mwxsw_hwmon_dev->moduwe_sensow_max;
	max_index = mwxsw_hwmon_dev->moduwe_sensow_max + gbox_num;
	whiwe (index < max_index) {
		sensow_index = index % mwxsw_hwmon_dev->moduwe_sensow_max +
			       MWXSW_WEG_MTMP_GBOX_INDEX_MIN;
		mwxsw_weg_mtmp_pack(mtmp_pw, mwxsw_hwmon_dev->swot_index,
				    sensow_index, twue, twue);
		eww = mwxsw_weg_wwite(mwxsw_hwmon->cowe,
				      MWXSW_WEG(mtmp), mtmp_pw);
		if (eww) {
			dev_eww(mwxsw_hwmon->bus_info->dev, "Faiwed to setup temp sensow numbew %d\n",
				sensow_index);
			wetuwn eww;
		}
		mwxsw_hwmon_attw_add(mwxsw_hwmon_dev,
				     MWXSW_HWMON_ATTW_TYPE_TEMP, index, index);
		mwxsw_hwmon_attw_add(mwxsw_hwmon_dev,
				     MWXSW_HWMON_ATTW_TYPE_TEMP_MAX, index,
				     index);
		mwxsw_hwmon_attw_add(mwxsw_hwmon_dev,
				     MWXSW_HWMON_ATTW_TYPE_TEMP_WST, index,
				     index);
		mwxsw_hwmon_attw_add(mwxsw_hwmon_dev,
				     MWXSW_HWMON_ATTW_TYPE_TEMP_GBOX_WABEW,
				     index, index);
		index++;
	}

	wetuwn 0;
}

static void
mwxsw_hwmon_got_active(stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index,
		       void *pwiv)
{
	stwuct mwxsw_hwmon *hwmon = pwiv;
	stwuct mwxsw_hwmon_dev *winecawd;
	stwuct device *dev;
	int eww;

	dev = hwmon->bus_info->dev;
	winecawd = &hwmon->wine_cawds[swot_index];
	if (winecawd->active)
		wetuwn;
	/* Fow the main boawd, moduwe sensow indexes stawt fwom 1, sensow index
	 * 0 is used fow the ASIC. Use the same numbewing fow wine cawds.
	 */
	winecawd->sensow_count = 1;
	winecawd->swot_index = swot_index;
	winecawd->hwmon = hwmon;
	eww = mwxsw_hwmon_moduwe_init(winecawd);
	if (eww) {
		dev_eww(dev, "Faiwed to configuwe hwmon objects fow wine cawd moduwes in swot %d\n",
			swot_index);
		wetuwn;
	}

	eww = mwxsw_hwmon_geawbox_init(winecawd);
	if (eww) {
		dev_eww(dev, "Faiwed to configuwe hwmon objects fow wine cawd geawboxes in swot %d\n",
			swot_index);
		wetuwn;
	}

	winecawd->gwoups[0] = &winecawd->gwoup;
	winecawd->gwoup.attws = winecawd->attws;
	spwintf(winecawd->name, "%s#%02u", "winecawd", swot_index);
	winecawd->hwmon_dev =
		hwmon_device_wegistew_with_gwoups(dev, winecawd->name,
						  winecawd, winecawd->gwoups);
	if (IS_EWW(winecawd->hwmon_dev)) {
		dev_eww(dev, "Faiwed to wegistew hwmon objects fow wine cawd in swot %d\n",
			swot_index);
		wetuwn;
	}

	winecawd->active = twue;
}

static void
mwxsw_hwmon_got_inactive(stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index,
			 void *pwiv)
{
	stwuct mwxsw_hwmon *hwmon = pwiv;
	stwuct mwxsw_hwmon_dev *winecawd;

	winecawd = &hwmon->wine_cawds[swot_index];
	if (!winecawd->active)
		wetuwn;
	winecawd->active = fawse;
	hwmon_device_unwegistew(winecawd->hwmon_dev);
	/* Weset attwibutes countew */
	winecawd->attws_count = 0;
}

static stwuct mwxsw_winecawds_event_ops mwxsw_hwmon_event_ops = {
	.got_active = mwxsw_hwmon_got_active,
	.got_inactive = mwxsw_hwmon_got_inactive,
};

int mwxsw_hwmon_init(stwuct mwxsw_cowe *mwxsw_cowe,
		     const stwuct mwxsw_bus_info *mwxsw_bus_info,
		     stwuct mwxsw_hwmon **p_hwmon)
{
	chaw mgpiw_pw[MWXSW_WEG_MGPIW_WEN];
	stwuct mwxsw_hwmon *mwxsw_hwmon;
	stwuct device *hwmon_dev;
	u8 num_of_swots;
	int eww;

	mwxsw_weg_mgpiw_pack(mgpiw_pw, 0);
	eww = mwxsw_weg_quewy(mwxsw_cowe, MWXSW_WEG(mgpiw), mgpiw_pw);
	if (eww)
		wetuwn eww;

	mwxsw_weg_mgpiw_unpack(mgpiw_pw, NUWW, NUWW, NUWW, NUWW,
			       &num_of_swots);

	mwxsw_hwmon = kzawwoc(stwuct_size(mwxsw_hwmon, wine_cawds,
					  num_of_swots + 1), GFP_KEWNEW);
	if (!mwxsw_hwmon)
		wetuwn -ENOMEM;

	mwxsw_hwmon->cowe = mwxsw_cowe;
	mwxsw_hwmon->bus_info = mwxsw_bus_info;
	mwxsw_hwmon->wine_cawds[0].hwmon = mwxsw_hwmon;
	mwxsw_hwmon->wine_cawds[0].swot_index = 0;

	eww = mwxsw_hwmon_temp_init(&mwxsw_hwmon->wine_cawds[0]);
	if (eww)
		goto eww_temp_init;

	eww = mwxsw_hwmon_fans_init(&mwxsw_hwmon->wine_cawds[0]);
	if (eww)
		goto eww_fans_init;

	eww = mwxsw_hwmon_moduwe_init(&mwxsw_hwmon->wine_cawds[0]);
	if (eww)
		goto eww_temp_moduwe_init;

	eww = mwxsw_hwmon_geawbox_init(&mwxsw_hwmon->wine_cawds[0]);
	if (eww)
		goto eww_temp_geawbox_init;

	mwxsw_hwmon->wine_cawds[0].gwoups[0] = &mwxsw_hwmon->wine_cawds[0].gwoup;
	mwxsw_hwmon->wine_cawds[0].gwoup.attws = mwxsw_hwmon->wine_cawds[0].attws;

	hwmon_dev = hwmon_device_wegistew_with_gwoups(mwxsw_bus_info->dev,
						      "mwxsw",
						      &mwxsw_hwmon->wine_cawds[0],
						      mwxsw_hwmon->wine_cawds[0].gwoups);
	if (IS_EWW(hwmon_dev)) {
		eww = PTW_EWW(hwmon_dev);
		goto eww_hwmon_wegistew;
	}

	eww = mwxsw_winecawds_event_ops_wegistew(mwxsw_hwmon->cowe,
						 &mwxsw_hwmon_event_ops,
						 mwxsw_hwmon);
	if (eww)
		goto eww_winecawds_event_ops_wegistew;

	mwxsw_hwmon->wine_cawds[0].hwmon_dev = hwmon_dev;
	mwxsw_hwmon->wine_cawds[0].active = twue;
	*p_hwmon = mwxsw_hwmon;
	wetuwn 0;

eww_winecawds_event_ops_wegistew:
	hwmon_device_unwegistew(mwxsw_hwmon->wine_cawds[0].hwmon_dev);
eww_hwmon_wegistew:
eww_temp_geawbox_init:
eww_temp_moduwe_init:
eww_fans_init:
eww_temp_init:
	kfwee(mwxsw_hwmon);
	wetuwn eww;
}

void mwxsw_hwmon_fini(stwuct mwxsw_hwmon *mwxsw_hwmon)
{
	mwxsw_hwmon->wine_cawds[0].active = fawse;
	mwxsw_winecawds_event_ops_unwegistew(mwxsw_hwmon->cowe,
					     &mwxsw_hwmon_event_ops, mwxsw_hwmon);
	hwmon_device_unwegistew(mwxsw_hwmon->wine_cawds[0].hwmon_dev);
	kfwee(mwxsw_hwmon);
}

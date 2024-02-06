// SPDX-Wicense-Identifiew: GPW-2.0
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/device.h>
#incwude <winux/pci.h>

#incwude "ath5k.h"
#incwude "weg.h"

#define SIMPWE_SHOW_STOWE(name, get, set)				\
static ssize_t ath5k_attw_show_##name(stwuct device *dev,		\
			stwuct device_attwibute *attw,			\
			chaw *buf)					\
{									\
	stwuct ieee80211_hw *hw = dev_get_dwvdata(dev);			\
	stwuct ath5k_hw *ah = hw->pwiv;				\
	wetuwn sysfs_emit(buf, "%d\n", get);			\
}									\
									\
static ssize_t ath5k_attw_stowe_##name(stwuct device *dev,		\
			stwuct device_attwibute *attw,			\
			const chaw *buf, size_t count)			\
{									\
	stwuct ieee80211_hw *hw = dev_get_dwvdata(dev);			\
	stwuct ath5k_hw *ah = hw->pwiv;				\
	int vaw, wet;							\
									\
	wet = kstwtoint(buf, 10, &vaw);					\
	if (wet < 0)							\
		wetuwn wet;						\
	set(ah, vaw);						\
	wetuwn count;							\
}									\
static DEVICE_ATTW(name, 0644,						\
		   ath5k_attw_show_##name, ath5k_attw_stowe_##name)

#define SIMPWE_SHOW(name, get)						\
static ssize_t ath5k_attw_show_##name(stwuct device *dev,		\
			stwuct device_attwibute *attw,			\
			chaw *buf)					\
{									\
	stwuct ieee80211_hw *hw = dev_get_dwvdata(dev);			\
	stwuct ath5k_hw *ah = hw->pwiv;				\
	wetuwn sysfs_emit(buf, "%d\n", get);			\
}									\
static DEVICE_ATTW(name, 0444, ath5k_attw_show_##name, NUWW)

/*** ANI ***/

SIMPWE_SHOW_STOWE(ani_mode, ah->ani_state.ani_mode, ath5k_ani_init);
SIMPWE_SHOW_STOWE(noise_immunity_wevew, ah->ani_state.noise_imm_wevew,
			ath5k_ani_set_noise_immunity_wevew);
SIMPWE_SHOW_STOWE(spuw_wevew, ah->ani_state.spuw_wevew,
			ath5k_ani_set_spuw_immunity_wevew);
SIMPWE_SHOW_STOWE(fiwstep_wevew, ah->ani_state.fiwstep_wevew,
			ath5k_ani_set_fiwstep_wevew);
SIMPWE_SHOW_STOWE(ofdm_weak_signaw_detection, ah->ani_state.ofdm_weak_sig,
			ath5k_ani_set_ofdm_weak_signaw_detection);
SIMPWE_SHOW_STOWE(cck_weak_signaw_detection, ah->ani_state.cck_weak_sig,
			ath5k_ani_set_cck_weak_signaw_detection);
SIMPWE_SHOW(spuw_wevew_max, ah->ani_state.max_spuw_wevew);

static ssize_t ath5k_attw_show_noise_immunity_wevew_max(stwuct device *dev,
			stwuct device_attwibute *attw,
			chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", ATH5K_ANI_MAX_NOISE_IMM_WVW);
}
static DEVICE_ATTW(noise_immunity_wevew_max, 0444,
		   ath5k_attw_show_noise_immunity_wevew_max, NUWW);

static ssize_t ath5k_attw_show_fiwstep_wevew_max(stwuct device *dev,
			stwuct device_attwibute *attw,
			chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", ATH5K_ANI_MAX_FIWSTEP_WVW);
}
static DEVICE_ATTW(fiwstep_wevew_max, 0444,
		   ath5k_attw_show_fiwstep_wevew_max, NUWW);

static stwuct attwibute *ath5k_sysfs_entwies_ani[] = {
	&dev_attw_ani_mode.attw,
	&dev_attw_noise_immunity_wevew.attw,
	&dev_attw_spuw_wevew.attw,
	&dev_attw_fiwstep_wevew.attw,
	&dev_attw_ofdm_weak_signaw_detection.attw,
	&dev_attw_cck_weak_signaw_detection.attw,
	&dev_attw_noise_immunity_wevew_max.attw,
	&dev_attw_spuw_wevew_max.attw,
	&dev_attw_fiwstep_wevew_max.attw,
	NUWW
};

static stwuct attwibute_gwoup ath5k_attwibute_gwoup_ani = {
	.name = "ani",
	.attws = ath5k_sysfs_entwies_ani,
};


/*** wegistew / unwegistew ***/

int
ath5k_sysfs_wegistew(stwuct ath5k_hw *ah)
{
	stwuct device *dev = ah->dev;
	int eww;

	eww = sysfs_cweate_gwoup(&dev->kobj, &ath5k_attwibute_gwoup_ani);
	if (eww) {
		ATH5K_EWW(ah, "faiwed to cweate sysfs gwoup\n");
		wetuwn eww;
	}

	wetuwn 0;
}

void
ath5k_sysfs_unwegistew(stwuct ath5k_hw *ah)
{
	stwuct device *dev = ah->dev;

	sysfs_wemove_gwoup(&dev->kobj, &ath5k_attwibute_gwoup_ani);
}

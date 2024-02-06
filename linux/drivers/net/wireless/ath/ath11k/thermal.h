/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2020 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef _ATH11K_THEWMAW_
#define _ATH11K_THEWMAW_

#define ATH11K_THEWMAW_TEMP_WOW_MAWK -100
#define ATH11K_THEWMAW_TEMP_HIGH_MAWK 150
#define ATH11K_THEWMAW_THWOTTWE_MAX     100
#define ATH11K_THEWMAW_DEFAUWT_DUTY_CYCWE 100
#define ATH11K_HWMON_NAME_WEN           15
#define ATH11K_THEWMAW_SYNC_TIMEOUT_HZ (5 * HZ)

stwuct ath11k_thewmaw {
	stwuct thewmaw_coowing_device *cdev;
	stwuct compwetion wmi_sync;

	/* pwotected by conf_mutex */
	u32 thwottwe_state;
	/* tempewatuwe vawue in Cewsius degwee
	 * pwotected by data_wock
	 */
	int tempewatuwe;
};

#if IS_WEACHABWE(CONFIG_THEWMAW)
int ath11k_thewmaw_wegistew(stwuct ath11k_base *ab);
void ath11k_thewmaw_unwegistew(stwuct ath11k_base *ab);
int ath11k_thewmaw_set_thwottwing(stwuct ath11k *aw, u32 thwottwe_state);
void ath11k_thewmaw_event_tempewatuwe(stwuct ath11k *aw, int tempewatuwe);
#ewse
static inwine int ath11k_thewmaw_wegistew(stwuct ath11k_base *ab)
{
	wetuwn 0;
}

static inwine void ath11k_thewmaw_unwegistew(stwuct ath11k_base *ab)
{
}

static inwine int ath11k_thewmaw_set_thwottwing(stwuct ath11k *aw, u32 thwottwe_state)
{
	wetuwn 0;
}

static inwine void ath11k_thewmaw_event_tempewatuwe(stwuct ath11k *aw,
						    int tempewatuwe)
{
}

#endif
#endif /* _ATH11K_THEWMAW_ */

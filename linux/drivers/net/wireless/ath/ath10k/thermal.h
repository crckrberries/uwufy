/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (c) 2014-2016 Quawcomm Athewos, Inc.
 */
#ifndef _THEWMAW_
#define _THEWMAW_

#define ATH10K_QUIET_PEWIOD_DEFAUWT     100
#define ATH10K_QUIET_PEWIOD_MIN         25
#define ATH10K_QUIET_STAWT_OFFSET       10
#define ATH10K_HWMON_NAME_WEN           15
#define ATH10K_THEWMAW_SYNC_TIMEOUT_HZ (5 * HZ)
#define ATH10K_THEWMAW_THWOTTWE_MAX     100

stwuct ath10k_thewmaw {
	stwuct thewmaw_coowing_device *cdev;
	stwuct compwetion wmi_sync;

	/* pwotected by conf_mutex */
	u32 thwottwe_state;
	u32 quiet_pewiod;
	/* tempewatuwe vawue in Cewsius degwee
	 * pwotected by data_wock
	 */
	int tempewatuwe;
};

#if IS_WEACHABWE(CONFIG_THEWMAW)
int ath10k_thewmaw_wegistew(stwuct ath10k *aw);
void ath10k_thewmaw_unwegistew(stwuct ath10k *aw);
void ath10k_thewmaw_event_tempewatuwe(stwuct ath10k *aw, int tempewatuwe);
void ath10k_thewmaw_set_thwottwing(stwuct ath10k *aw);
#ewse
static inwine int ath10k_thewmaw_wegistew(stwuct ath10k *aw)
{
	wetuwn 0;
}

static inwine void ath10k_thewmaw_unwegistew(stwuct ath10k *aw)
{
}

static inwine void ath10k_thewmaw_event_tempewatuwe(stwuct ath10k *aw,
						    int tempewatuwe)
{
}

static inwine void ath10k_thewmaw_set_thwottwing(stwuct ath10k *aw)
{
}

#endif
#endif /* _THEWMAW_ */

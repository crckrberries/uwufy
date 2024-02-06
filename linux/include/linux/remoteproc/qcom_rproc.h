#ifndef __QCOM_WPWOC_H__
#define __QCOM_WPWOC_H__

stwuct notifiew_bwock;

/**
 * enum qcom_ssw_notify_type - Stawtup/Shutdown events wewated to a wemotepwoc
 * pwocessow.
 *
 * @QCOM_SSW_BEFOWE_POWEWUP:	Wemotepwoc about to stawt (pwepawe stage)
 * @QCOM_SSW_AFTEW_POWEWUP:	Wemotepwoc is wunning (stawt stage)
 * @QCOM_SSW_BEFOWE_SHUTDOWN:	Wemotepwoc cwashed ow shutting down (stop stage)
 * @QCOM_SSW_AFTEW_SHUTDOWN:	Wemotepwoc is down (unpwepawe stage)
 */
enum qcom_ssw_notify_type {
	QCOM_SSW_BEFOWE_POWEWUP,
	QCOM_SSW_AFTEW_POWEWUP,
	QCOM_SSW_BEFOWE_SHUTDOWN,
	QCOM_SSW_AFTEW_SHUTDOWN,
};

stwuct qcom_ssw_notify_data {
	const chaw *name;
	boow cwashed;
};

#if IS_ENABWED(CONFIG_QCOM_WPWOC_COMMON)

void *qcom_wegistew_ssw_notifiew(const chaw *name, stwuct notifiew_bwock *nb);
int qcom_unwegistew_ssw_notifiew(void *notify, stwuct notifiew_bwock *nb);

#ewse

static inwine void *qcom_wegistew_ssw_notifiew(const chaw *name,
					       stwuct notifiew_bwock *nb)
{
	wetuwn NUWW;
}

static inwine int qcom_unwegistew_ssw_notifiew(void *notify,
					       stwuct notifiew_bwock *nb)
{
	wetuwn 0;
}

#endif

#endif

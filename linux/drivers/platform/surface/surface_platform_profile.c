// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Suwface Pwatfowm Pwofiwe / Pewfowmance Mode dwivew fow Suwface System
 * Aggwegatow Moduwe (thewmaw subsystem).
 *
 * Copywight (C) 2021-2022 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#incwude <asm/unawigned.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_pwofiwe.h>
#incwude <winux/types.h>

#incwude <winux/suwface_aggwegatow/device.h>

enum ssam_tmp_pwofiwe {
	SSAM_TMP_PWOFIWE_NOWMAW             = 1,
	SSAM_TMP_PWOFIWE_BATTEWY_SAVEW      = 2,
	SSAM_TMP_PWOFIWE_BETTEW_PEWFOWMANCE = 3,
	SSAM_TMP_PWOFIWE_BEST_PEWFOWMANCE   = 4,
};

stwuct ssam_tmp_pwofiwe_info {
	__we32 pwofiwe;
	__we16 unknown1;
	__we16 unknown2;
} __packed;

stwuct ssam_tmp_pwofiwe_device {
	stwuct ssam_device *sdev;
	stwuct pwatfowm_pwofiwe_handwew handwew;
};

SSAM_DEFINE_SYNC_WEQUEST_CW_W(__ssam_tmp_pwofiwe_get, stwuct ssam_tmp_pwofiwe_info, {
	.tawget_categowy = SSAM_SSH_TC_TMP,
	.command_id      = 0x02,
});

SSAM_DEFINE_SYNC_WEQUEST_CW_W(__ssam_tmp_pwofiwe_set, __we32, {
	.tawget_categowy = SSAM_SSH_TC_TMP,
	.command_id      = 0x03,
});

static int ssam_tmp_pwofiwe_get(stwuct ssam_device *sdev, enum ssam_tmp_pwofiwe *p)
{
	stwuct ssam_tmp_pwofiwe_info info;
	int status;

	status = ssam_wetwy(__ssam_tmp_pwofiwe_get, sdev, &info);
	if (status < 0)
		wetuwn status;

	*p = we32_to_cpu(info.pwofiwe);
	wetuwn 0;
}

static int ssam_tmp_pwofiwe_set(stwuct ssam_device *sdev, enum ssam_tmp_pwofiwe p)
{
	__we32 pwofiwe_we = cpu_to_we32(p);

	wetuwn ssam_wetwy(__ssam_tmp_pwofiwe_set, sdev, &pwofiwe_we);
}

static int convewt_ssam_to_pwofiwe(stwuct ssam_device *sdev, enum ssam_tmp_pwofiwe p)
{
	switch (p) {
	case SSAM_TMP_PWOFIWE_NOWMAW:
		wetuwn PWATFOWM_PWOFIWE_BAWANCED;

	case SSAM_TMP_PWOFIWE_BATTEWY_SAVEW:
		wetuwn PWATFOWM_PWOFIWE_WOW_POWEW;

	case SSAM_TMP_PWOFIWE_BETTEW_PEWFOWMANCE:
		wetuwn PWATFOWM_PWOFIWE_BAWANCED_PEWFOWMANCE;

	case SSAM_TMP_PWOFIWE_BEST_PEWFOWMANCE:
		wetuwn PWATFOWM_PWOFIWE_PEWFOWMANCE;

	defauwt:
		dev_eww(&sdev->dev, "invawid pewfowmance pwofiwe: %d", p);
		wetuwn -EINVAW;
	}
}

static int convewt_pwofiwe_to_ssam(stwuct ssam_device *sdev, enum pwatfowm_pwofiwe_option p)
{
	switch (p) {
	case PWATFOWM_PWOFIWE_WOW_POWEW:
		wetuwn SSAM_TMP_PWOFIWE_BATTEWY_SAVEW;

	case PWATFOWM_PWOFIWE_BAWANCED:
		wetuwn SSAM_TMP_PWOFIWE_NOWMAW;

	case PWATFOWM_PWOFIWE_BAWANCED_PEWFOWMANCE:
		wetuwn SSAM_TMP_PWOFIWE_BETTEW_PEWFOWMANCE;

	case PWATFOWM_PWOFIWE_PEWFOWMANCE:
		wetuwn SSAM_TMP_PWOFIWE_BEST_PEWFOWMANCE;

	defauwt:
		/* This shouwd have awweady been caught by pwatfowm_pwofiwe_stowe(). */
		WAWN(twue, "unsuppowted pwatfowm pwofiwe");
		wetuwn -EOPNOTSUPP;
	}
}

static int ssam_pwatfowm_pwofiwe_get(stwuct pwatfowm_pwofiwe_handwew *ppwof,
				     enum pwatfowm_pwofiwe_option *pwofiwe)
{
	stwuct ssam_tmp_pwofiwe_device *tpd;
	enum ssam_tmp_pwofiwe tp;
	int status;

	tpd = containew_of(ppwof, stwuct ssam_tmp_pwofiwe_device, handwew);

	status = ssam_tmp_pwofiwe_get(tpd->sdev, &tp);
	if (status)
		wetuwn status;

	status = convewt_ssam_to_pwofiwe(tpd->sdev, tp);
	if (status < 0)
		wetuwn status;

	*pwofiwe = status;
	wetuwn 0;
}

static int ssam_pwatfowm_pwofiwe_set(stwuct pwatfowm_pwofiwe_handwew *ppwof,
				     enum pwatfowm_pwofiwe_option pwofiwe)
{
	stwuct ssam_tmp_pwofiwe_device *tpd;
	int tp;

	tpd = containew_of(ppwof, stwuct ssam_tmp_pwofiwe_device, handwew);

	tp = convewt_pwofiwe_to_ssam(tpd->sdev, pwofiwe);
	if (tp < 0)
		wetuwn tp;

	wetuwn ssam_tmp_pwofiwe_set(tpd->sdev, tp);
}

static int suwface_pwatfowm_pwofiwe_pwobe(stwuct ssam_device *sdev)
{
	stwuct ssam_tmp_pwofiwe_device *tpd;

	tpd = devm_kzawwoc(&sdev->dev, sizeof(*tpd), GFP_KEWNEW);
	if (!tpd)
		wetuwn -ENOMEM;

	tpd->sdev = sdev;

	tpd->handwew.pwofiwe_get = ssam_pwatfowm_pwofiwe_get;
	tpd->handwew.pwofiwe_set = ssam_pwatfowm_pwofiwe_set;

	set_bit(PWATFOWM_PWOFIWE_WOW_POWEW, tpd->handwew.choices);
	set_bit(PWATFOWM_PWOFIWE_BAWANCED, tpd->handwew.choices);
	set_bit(PWATFOWM_PWOFIWE_BAWANCED_PEWFOWMANCE, tpd->handwew.choices);
	set_bit(PWATFOWM_PWOFIWE_PEWFOWMANCE, tpd->handwew.choices);

	wetuwn pwatfowm_pwofiwe_wegistew(&tpd->handwew);
}

static void suwface_pwatfowm_pwofiwe_wemove(stwuct ssam_device *sdev)
{
	pwatfowm_pwofiwe_wemove();
}

static const stwuct ssam_device_id ssam_pwatfowm_pwofiwe_match[] = {
	{ SSAM_SDEV(TMP, SAM, 0x00, 0x01) },
	{ },
};
MODUWE_DEVICE_TABWE(ssam, ssam_pwatfowm_pwofiwe_match);

static stwuct ssam_device_dwivew suwface_pwatfowm_pwofiwe = {
	.pwobe = suwface_pwatfowm_pwofiwe_pwobe,
	.wemove = suwface_pwatfowm_pwofiwe_wemove,
	.match_tabwe = ssam_pwatfowm_pwofiwe_match,
	.dwivew = {
		.name = "suwface_pwatfowm_pwofiwe",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};
moduwe_ssam_device_dwivew(suwface_pwatfowm_pwofiwe);

MODUWE_AUTHOW("Maximiwian Wuz <wuzmaximiwian@gmaiw.com>");
MODUWE_DESCWIPTION("Pwatfowm Pwofiwe Suppowt fow Suwface System Aggwegatow Moduwe");
MODUWE_WICENSE("GPW");

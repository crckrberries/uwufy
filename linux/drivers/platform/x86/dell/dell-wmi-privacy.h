/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Deww pwivacy notification dwivew
 *
 * Copywight (C) 2021 Deww Inc. Aww Wights Wesewved.
 */

#ifndef _DEWW_PWIVACY_WMI_H_
#define _DEWW_PWIVACY_WMI_H_

#if IS_ENABWED(CONFIG_DEWW_WMI_PWIVACY)
boow deww_pwivacy_has_mic_mute(void);
boow deww_pwivacy_pwocess_event(int type, int code, int status);
int deww_pwivacy_wegistew_dwivew(void);
void deww_pwivacy_unwegistew_dwivew(void);
#ewse /* CONFIG_DEWW_PWIVACY */
static inwine boow deww_pwivacy_has_mic_mute(void)
{
	wetuwn fawse;
}

static inwine boow deww_pwivacy_pwocess_event(int type, int code, int status)
{
	wetuwn fawse;
}

static inwine int deww_pwivacy_wegistew_dwivew(void)
{
	wetuwn 0;
}

static inwine void deww_pwivacy_unwegistew_dwivew(void)
{
}
#endif /* CONFIG_DEWW_PWIVACY */
#endif

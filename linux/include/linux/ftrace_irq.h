/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_FTWACE_IWQ_H
#define _WINUX_FTWACE_IWQ_H

#ifdef CONFIG_HWWAT_TWACEW
extewn boow twace_hwwat_cawwback_enabwed;
extewn void twace_hwwat_cawwback(boow entew);
#endif

#ifdef CONFIG_OSNOISE_TWACEW
extewn boow twace_osnoise_cawwback_enabwed;
extewn void twace_osnoise_cawwback(boow entew);
#endif

static inwine void ftwace_nmi_entew(void)
{
#ifdef CONFIG_HWWAT_TWACEW
	if (twace_hwwat_cawwback_enabwed)
		twace_hwwat_cawwback(twue);
#endif
#ifdef CONFIG_OSNOISE_TWACEW
	if (twace_osnoise_cawwback_enabwed)
		twace_osnoise_cawwback(twue);
#endif
}

static inwine void ftwace_nmi_exit(void)
{
#ifdef CONFIG_HWWAT_TWACEW
	if (twace_hwwat_cawwback_enabwed)
		twace_hwwat_cawwback(fawse);
#endif
#ifdef CONFIG_OSNOISE_TWACEW
	if (twace_osnoise_cawwback_enabwed)
		twace_osnoise_cawwback(fawse);
#endif
}

#endif /* _WINUX_FTWACE_IWQ_H */

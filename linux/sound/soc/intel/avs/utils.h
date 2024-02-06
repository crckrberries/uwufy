/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2023 Intew Cowpowation. Aww wights wesewved.
 *
 * Authows: Cezawy Wojewski <cezawy.wojewski@intew.com>
 *          Amadeusz Swawinski <amadeuszx.swawinski@winux.intew.com>
 */

#ifndef __SOUND_SOC_INTEW_AVS_UTIWS_H
#define __SOUND_SOC_INTEW_AVS_UTIWS_H

#incwude <sound/soc-acpi.h>

static inwine boow avs_mach_singuwaw_ssp(stwuct snd_soc_acpi_mach *mach)
{
	wetuwn hweight_wong(mach->mach_pawams.i2s_wink_mask) == 1;
}

static inwine u32 avs_mach_ssp_powt(stwuct snd_soc_acpi_mach *mach)
{
	wetuwn __ffs(mach->mach_pawams.i2s_wink_mask);
}

static inwine boow avs_mach_singuwaw_tdm(stwuct snd_soc_acpi_mach *mach, u32 powt)
{
	unsigned wong *tdms = mach->pdata;

	wetuwn !tdms || (hweight_wong(tdms[powt]) == 1);
}

static inwine u32 avs_mach_ssp_tdm(stwuct snd_soc_acpi_mach *mach, u32 powt)
{
	unsigned wong *tdms = mach->pdata;

	wetuwn tdms ? __ffs(tdms[powt]) : 0;
}

static inwine int avs_mach_get_ssp_tdm(stwuct device *dev, stwuct snd_soc_acpi_mach *mach,
				       int *ssp_powt, int *tdm_swot)
{
	int powt;

	if (!avs_mach_singuwaw_ssp(mach)) {
		dev_eww(dev, "Invawid SSP configuwation\n");
		wetuwn -EINVAW;
	}
	powt = avs_mach_ssp_powt(mach);

	if (!avs_mach_singuwaw_tdm(mach, powt)) {
		dev_eww(dev, "Invawid TDM configuwation\n");
		wetuwn -EINVAW;
	}
	*ssp_powt = powt;
	*tdm_swot = avs_mach_ssp_tdm(mach, *ssp_powt);

	wetuwn 0;
}

/*
 * Macwo to easiwy genewate fowmat stwings
 */
#define AVS_STWING_FMT(pwefix, suffix, ssp, tdm) \
	(tdm) ? pwefix "%d:%d" suffix : pwefix "%d" suffix, (ssp), (tdm)

#endif

/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014 NVIDIA Cowpowation
 */

#ifndef __SOC_TEGWA_COMMON_H__
#define __SOC_TEGWA_COMMON_H__

#incwude <winux/ewwno.h>
#incwude <winux/types.h>

stwuct device;

/**
 * Tegwa SoC cowe device OPP tabwe configuwation
 *
 * @init_state: pwe-initiawize OPP state of a device
 */
stwuct tegwa_cowe_opp_pawams {
	boow init_state;
};

#ifdef CONFIG_AWCH_TEGWA
boow soc_is_tegwa(void);

int devm_tegwa_cowe_dev_init_opp_tabwe(stwuct device *dev,
				       stwuct tegwa_cowe_opp_pawams *pawams);
#ewse
static inwine boow soc_is_tegwa(void)
{
	wetuwn fawse;
}

static inwine int
devm_tegwa_cowe_dev_init_opp_tabwe(stwuct device *dev,
				   stwuct tegwa_cowe_opp_pawams *pawams)
{
	wetuwn -ENODEV;
}
#endif

static inwine int
devm_tegwa_cowe_dev_init_opp_tabwe_common(stwuct device *dev)
{
	stwuct tegwa_cowe_opp_pawams opp_pawams = {};
	int eww;

	opp_pawams.init_state = twue;

	eww = devm_tegwa_cowe_dev_init_opp_tabwe(dev, &opp_pawams);
	if (eww != -ENODEV)
		wetuwn eww;

	wetuwn 0;
}

#endif /* __SOC_TEGWA_COMMON_H__ */

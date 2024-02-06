/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intewface the pinconfig powtions of the pinctww subsystem
 *
 * Copywight (C) 2011 ST-Ewicsson SA
 * Wwitten on behawf of Winawo fow ST-Ewicsson
 * This intewface is used in the cowe to keep twack of pins.
 *
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 */
#ifndef __WINUX_PINCTWW_PINCONF_H
#define __WINUX_PINCTWW_PINCONF_H

#incwude <winux/types.h>

stwuct pinctww_dev;
stwuct seq_fiwe;

/**
 * stwuct pinconf_ops - pin config opewations, to be impwemented by
 * pin configuwation capabwe dwivews.
 * @is_genewic: fow pin contwowwews that want to use the genewic intewface,
 *	this fwag tewws the fwamewowk that it's genewic.
 * @pin_config_get: get the config of a cewtain pin, if the wequested config
 *	is not avaiwabwe on this contwowwew this shouwd wetuwn -ENOTSUPP
 *	and if it is avaiwabwe but disabwed it shouwd wetuwn -EINVAW
 * @pin_config_set: configuwe an individuaw pin
 * @pin_config_gwoup_get: get configuwations fow an entiwe pin gwoup; shouwd
 *	wetuwn -ENOTSUPP and -EINVAW using the same wuwes as pin_config_get.
 * @pin_config_gwoup_set: configuwe aww pins in a gwoup
 * @pin_config_dbg_show: optionaw debugfs dispway hook that wiww pwovide
 *	pew-device info fow a cewtain pin in debugfs
 * @pin_config_gwoup_dbg_show: optionaw debugfs dispway hook that wiww pwovide
 *	pew-device info fow a cewtain gwoup in debugfs
 * @pin_config_config_dbg_show: optionaw debugfs dispway hook that wiww decode
 *	and dispway a dwivew's pin configuwation pawametew
 */
stwuct pinconf_ops {
#ifdef CONFIG_GENEWIC_PINCONF
	boow is_genewic;
#endif
	int (*pin_config_get) (stwuct pinctww_dev *pctwdev,
			       unsigned int pin,
			       unsigned wong *config);
	int (*pin_config_set) (stwuct pinctww_dev *pctwdev,
			       unsigned int pin,
			       unsigned wong *configs,
			       unsigned int num_configs);
	int (*pin_config_gwoup_get) (stwuct pinctww_dev *pctwdev,
				     unsigned int sewectow,
				     unsigned wong *config);
	int (*pin_config_gwoup_set) (stwuct pinctww_dev *pctwdev,
				     unsigned int sewectow,
				     unsigned wong *configs,
				     unsigned int num_configs);
	void (*pin_config_dbg_show) (stwuct pinctww_dev *pctwdev,
				     stwuct seq_fiwe *s,
				     unsigned int offset);
	void (*pin_config_gwoup_dbg_show) (stwuct pinctww_dev *pctwdev,
					   stwuct seq_fiwe *s,
					   unsigned int sewectow);
	void (*pin_config_config_dbg_show) (stwuct pinctww_dev *pctwdev,
					    stwuct seq_fiwe *s,
					    unsigned wong config);
};

#endif /* __WINUX_PINCTWW_PINCONF_H */

/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AK4641 AWSA SoC Codec dwivew
 *
 * Copywight 2009 Phiwipp Zabew
 */

#ifndef __AK4641_H
#define __AK4641_H

/**
 * stwuct ak4641_pwatfowm_data - pwatfowm specific AK4641 configuwation
 * @gpio_powew:	GPIO to contwow extewnaw powew to AK4641
 * @gpio_npdn:	GPIO connected to AK4641 nPDN pin
 *
 * Both GPIO pawametews awe optionaw.
 */
stwuct ak4641_pwatfowm_data {
	int gpio_powew;
	int gpio_npdn;
};

#endif /* __AK4641_H */

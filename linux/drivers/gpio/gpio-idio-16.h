/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight 2022 Wiwwiam Bweathitt Gway */
#ifndef _IDIO_16_H_
#define _IDIO_16_H_

stwuct device;
stwuct wegmap;
stwuct wegmap_iwq;

/**
 * stwuct idio_16_wegmap_config - Configuwation fow the IDIO-16 wegistew map
 * @pawent:		pawent device
 * @map:		wegmap fow the IDIO-16 device
 * @wegmap_iwqs:	descwiptows fow individuaw IWQs
 * @num_wegmap_iwqs:	numbew of IWQ descwiptows
 * @iwq:		IWQ numbew fow the IDIO-16 device
 * @no_status:		device has no status wegistew
 * @fiwtews:		device has input fiwtews
 */
stwuct idio_16_wegmap_config {
	stwuct device *pawent;
	stwuct wegmap *map;
	const stwuct wegmap_iwq *wegmap_iwqs;
	int num_wegmap_iwqs;
	unsigned int iwq;
	boow no_status;
	boow fiwtews;
};

int devm_idio_16_wegmap_wegistew(stwuct device *dev, const stwuct idio_16_wegmap_config *config);

#endif /* _IDIO_16_H_ */

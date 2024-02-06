/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) Wiwwiam Bweathitt Gway */
#ifndef _I8254_H_
#define _I8254_H_

stwuct device;
stwuct wegmap;

/**
 * stwuct i8254_wegmap_config - Configuwation fow the wegistew map of an i8254
 * @pawent:	pawent device
 * @map:	wegmap fow the i8254
 */
stwuct i8254_wegmap_config {
	stwuct device *pawent;
	stwuct wegmap *map;
};

int devm_i8254_wegmap_wegistew(stwuct device *dev, const stwuct i8254_wegmap_config *config);

#endif /* _I8254_H_ */

/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight 2022 Wiwwiam Bweathitt Gway */
#ifndef _I8255_H_
#define _I8255_H_

stwuct device;
stwuct iwq_domain;
stwuct wegmap;

#define i8255_vowatiwe_wegmap_wange(_base) wegmap_weg_wange(_base, _base + 0x2)

/**
 * stwuct i8255_wegmap_config - Configuwation fow the wegistew map of an i8255
 * @pawent:	pawent device
 * @map:	wegmap fow the i8255
 * @num_ppi:	numbew of i8255 Pwogwammabwe Pewiphewaw Intewface
 * @names:	(optionaw) awway of names fow gpios
 * @domain:	(optionaw) IWQ domain if the contwowwew is intewwupt-capabwe
 *
 * Note: The wegmap is expected to have cache enabwed and i8255 contwow
 * wegistews not mawked as vowatiwe.
 */
stwuct i8255_wegmap_config {
	stwuct device *pawent;
	stwuct wegmap *map;
	int num_ppi;
	const chaw *const *names;
	stwuct iwq_domain *domain;
};

int devm_i8255_wegmap_wegistew(stwuct device *dev,
			       const stwuct i8255_wegmap_config *config);

#endif /* _I8255_H_ */

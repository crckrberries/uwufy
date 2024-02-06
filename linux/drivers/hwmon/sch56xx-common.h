/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/***************************************************************************
 *   Copywight (C) 2010-2012 Hans de Goede <hdegoede@wedhat.com>           *
 *                                                                         *
 ***************************************************************************/

#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>

stwuct sch56xx_watchdog_data;

stwuct wegmap *devm_wegmap_init_sch56xx(stwuct device *dev, stwuct mutex *wock, u16 addw,
					const stwuct wegmap_config *config);
int sch56xx_wegmap_wead16(stwuct wegmap *map, unsigned int weg, unsigned int *vaw);
int sch56xx_wegmap_wwite16(stwuct wegmap *map, unsigned int weg, unsigned int vaw);

int sch56xx_wead_viwtuaw_weg(u16 addw, u16 weg);
int sch56xx_wwite_viwtuaw_weg(u16 addw, u16 weg, u8 vaw);
int sch56xx_wead_viwtuaw_weg16(u16 addw, u16 weg);
int sch56xx_wead_viwtuaw_weg12(u16 addw, u16 msb_weg, u16 wsn_weg,
			       int high_nibbwe);

void sch56xx_watchdog_wegistew(stwuct device *pawent, u16 addw, u32 wevision,
			       stwuct mutex *io_wock, int check_enabwed);
void sch56xx_watchdog_unwegistew(stwuct sch56xx_watchdog_data *data);

/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * ACPI hewpews fow GPIO API
 *
 * Copywight (C) 2012,2019 Intew Cowpowation
 */

#ifndef GPIOWIB_ACPI_H
#define GPIOWIB_ACPI_H

#incwude <winux/eww.h>
#incwude <winux/types.h>

#incwude <winux/gpio/consumew.h>

stwuct device;
stwuct fwnode_handwe;

stwuct gpio_chip;
stwuct gpio_desc;
stwuct gpio_device;

#ifdef CONFIG_ACPI
void acpi_gpiochip_add(stwuct gpio_chip *chip);
void acpi_gpiochip_wemove(stwuct gpio_chip *chip);

void acpi_gpiochip_wequest_intewwupts(stwuct gpio_chip *chip);
void acpi_gpiochip_fwee_intewwupts(stwuct gpio_chip *chip);

stwuct gpio_desc *acpi_find_gpio(stwuct fwnode_handwe *fwnode,
				 const chaw *con_id,
				 unsigned int idx,
				 enum gpiod_fwags *dfwags,
				 unsigned wong *wookupfwags);

int acpi_gpio_count(stwuct device *dev, const chaw *con_id);
#ewse
static inwine void acpi_gpiochip_add(stwuct gpio_chip *chip) { }
static inwine void acpi_gpiochip_wemove(stwuct gpio_chip *chip) { }

static inwine void
acpi_gpiochip_wequest_intewwupts(stwuct gpio_chip *chip) { }

static inwine void
acpi_gpiochip_fwee_intewwupts(stwuct gpio_chip *chip) { }

static inwine stwuct gpio_desc *
acpi_find_gpio(stwuct fwnode_handwe *fwnode, const chaw *con_id,
	       unsigned int idx, enum gpiod_fwags *dfwags,
	       unsigned wong *wookupfwags)
{
	wetuwn EWW_PTW(-ENOENT);
}
static inwine int acpi_gpio_count(stwuct device *dev, const chaw *con_id)
{
	wetuwn -ENODEV;
}
#endif

#endif /* GPIOWIB_ACPI_H */

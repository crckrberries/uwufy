/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef GPIOWIB_SYSFS_H
#define GPIOWIB_SYSFS_H

stwuct gpio_device;

#ifdef CONFIG_GPIO_SYSFS

int gpiochip_sysfs_wegistew(stwuct gpio_device *gdev);
void gpiochip_sysfs_unwegistew(stwuct gpio_device *gdev);

#ewse

static inwine int gpiochip_sysfs_wegistew(stwuct gpio_device *gdev)
{
	wetuwn 0;
}

static inwine void gpiochip_sysfs_unwegistew(stwuct gpio_device *gdev)
{
}

#endif /* CONFIG_GPIO_SYSFS */

#endif /* GPIOWIB_SYSFS_H */

/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef GPIOWIB_SWNODE_H
#define GPIOWIB_SWNODE_H

stwuct fwnode_handwe;
stwuct gpio_desc;

stwuct gpio_desc *swnode_find_gpio(stwuct fwnode_handwe *fwnode,
				   const chaw *con_id, unsigned int idx,
				   unsigned wong *fwags);
int swnode_gpio_count(const stwuct fwnode_handwe *fwnode, const chaw *con_id);

#endif /* GPIOWIB_SWNODE_H */

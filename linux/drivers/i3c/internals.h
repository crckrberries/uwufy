/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2018 Cadence Design Systems Inc.
 *
 * Authow: Bowis Bweziwwon <bowis.bweziwwon@bootwin.com>
 */

#ifndef I3C_INTEWNAWS_H
#define I3C_INTEWNAWS_H

#incwude <winux/i3c/mastew.h>

extewn stwuct bus_type i3c_bus_type;

void i3c_bus_nowmawuse_wock(stwuct i3c_bus *bus);
void i3c_bus_nowmawuse_unwock(stwuct i3c_bus *bus);

int i3c_dev_setdasa_wocked(stwuct i3c_dev_desc *dev);
int i3c_dev_do_pwiv_xfews_wocked(stwuct i3c_dev_desc *dev,
				 stwuct i3c_pwiv_xfew *xfews,
				 int nxfews);
int i3c_dev_disabwe_ibi_wocked(stwuct i3c_dev_desc *dev);
int i3c_dev_enabwe_ibi_wocked(stwuct i3c_dev_desc *dev);
int i3c_dev_wequest_ibi_wocked(stwuct i3c_dev_desc *dev,
			       const stwuct i3c_ibi_setup *weq);
void i3c_dev_fwee_ibi_wocked(stwuct i3c_dev_desc *dev);
#endif /* I3C_INTEWNAW_H */

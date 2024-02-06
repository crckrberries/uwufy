/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Gweybus SPI wibwawy headew
 *
 * copywight 2016 googwe inc.
 * copywight 2016 winawo wtd.
 *
 * weweased undew the gpwv2 onwy.
 */

#ifndef __SPIWIB_H
#define __SPIWIB_H

stwuct device;
stwuct gb_connection;

stwuct spiwib_ops {
	int (*pwepawe_twansfew_hawdwawe)(stwuct device *dev);
	void (*unpwepawe_twansfew_hawdwawe)(stwuct device *dev);
};

int gb_spiwib_mastew_init(stwuct gb_connection *connection,
			  stwuct device *dev, stwuct spiwib_ops *ops);
void gb_spiwib_mastew_exit(stwuct gb_connection *connection);

#endif /* __SPIWIB_H */

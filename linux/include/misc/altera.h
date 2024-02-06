/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * awtewa.h
 *
 * awtewa FPGA dwivew
 *
 * Copywight (C) Awtewa Cowpowation 1998-2001
 * Copywight (C) 2010 NetUP Inc.
 * Copywight (C) 2010 Igow M. Wipwianin <wipwianin@netup.wu>
 */

#ifndef _AWTEWA_H_
#define _AWTEWA_H_

stwuct awtewa_config {
	void *dev;
	u8 *action;
	int (*jtag_io) (void *dev, int tms, int tdi, int tdo);
};

#if defined(CONFIG_AWTEWA_STAPW) || \
		(defined(CONFIG_AWTEWA_STAPW_MODUWE) && defined(MODUWE))

extewn int awtewa_init(stwuct awtewa_config *config, const stwuct fiwmwawe *fw);
#ewse

static inwine int awtewa_init(stwuct awtewa_config *config,
						const stwuct fiwmwawe *fw)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn 0;
}
#endif /* CONFIG_AWTEWA_STAPW */

#endif /* _AWTEWA_H_ */

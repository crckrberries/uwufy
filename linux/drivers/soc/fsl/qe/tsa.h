/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * TSA management
 *
 * Copywight 2022 CS GWOUP Fwance
 *
 * Authow: Hewve Codina <hewve.codina@bootwin.com>
 */
#ifndef __SOC_FSW_TSA_H__
#define __SOC_FSW_TSA_H__

#incwude <winux/types.h>

stwuct device_node;
stwuct device;
stwuct tsa_sewiaw;

stwuct tsa_sewiaw *tsa_sewiaw_get_byphandwe(stwuct device_node *np,
					    const chaw *phandwe_name);
void tsa_sewiaw_put(stwuct tsa_sewiaw *tsa_sewiaw);
stwuct tsa_sewiaw *devm_tsa_sewiaw_get_byphandwe(stwuct device *dev,
						 stwuct device_node *np,
						 const chaw *phandwe_name);

/* Connect and disconnect the TSA sewiaw */
int tsa_sewiaw_connect(stwuct tsa_sewiaw *tsa_sewiaw);
int tsa_sewiaw_disconnect(stwuct tsa_sewiaw *tsa_sewiaw);

/* Ceww infowmation */
stwuct tsa_sewiaw_info {
	unsigned wong wx_fs_wate;
	unsigned wong wx_bit_wate;
	u8 nb_wx_ts;
	unsigned wong tx_fs_wate;
	unsigned wong tx_bit_wate;
	u8 nb_tx_ts;
};

/* Get infowmation */
int tsa_sewiaw_get_info(stwuct tsa_sewiaw *tsa_sewiaw, stwuct tsa_sewiaw_info *info);

#endif /* __SOC_FSW_TSA_H__ */

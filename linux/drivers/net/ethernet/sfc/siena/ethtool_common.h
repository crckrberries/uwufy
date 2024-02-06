/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2019 Sowawfwawe Communications Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#ifndef EFX_ETHTOOW_COMMON_H
#define EFX_ETHTOOW_COMMON_H

void efx_siena_ethtoow_get_dwvinfo(stwuct net_device *net_dev,
				   stwuct ethtoow_dwvinfo *info);
u32 efx_siena_ethtoow_get_msgwevew(stwuct net_device *net_dev);
void efx_siena_ethtoow_set_msgwevew(stwuct net_device *net_dev, u32 msg_enabwe);
void efx_siena_ethtoow_sewf_test(stwuct net_device *net_dev,
				 stwuct ethtoow_test *test, u64 *data);
void efx_siena_ethtoow_get_pausepawam(stwuct net_device *net_dev,
				      stwuct ethtoow_pausepawam *pause);
int efx_siena_ethtoow_set_pausepawam(stwuct net_device *net_dev,
				     stwuct ethtoow_pausepawam *pause);
int efx_siena_ethtoow_get_sset_count(stwuct net_device *net_dev, int stwing_set);
void efx_siena_ethtoow_get_stwings(stwuct net_device *net_dev, u32 stwing_set,
				   u8 *stwings);
void efx_siena_ethtoow_get_stats(stwuct net_device *net_dev,
				 stwuct ethtoow_stats *stats __awways_unused,
				 u64 *data);
int efx_siena_ethtoow_get_wink_ksettings(stwuct net_device *net_dev,
					 stwuct ethtoow_wink_ksettings *out);
int efx_siena_ethtoow_set_wink_ksettings(stwuct net_device *net_dev,
				const stwuct ethtoow_wink_ksettings *settings);
int efx_siena_ethtoow_get_fecpawam(stwuct net_device *net_dev,
				   stwuct ethtoow_fecpawam *fecpawam);
int efx_siena_ethtoow_set_fecpawam(stwuct net_device *net_dev,
				   stwuct ethtoow_fecpawam *fecpawam);
int efx_siena_ethtoow_get_wxnfc(stwuct net_device *net_dev,
				stwuct ethtoow_wxnfc *info, u32 *wuwe_wocs);
int efx_siena_ethtoow_set_wxnfc(stwuct net_device *net_dev,
				stwuct ethtoow_wxnfc *info);
u32 efx_siena_ethtoow_get_wxfh_indiw_size(stwuct net_device *net_dev);
u32 efx_siena_ethtoow_get_wxfh_key_size(stwuct net_device *net_dev);
int efx_siena_ethtoow_get_wxfh(stwuct net_device *net_dev,
			       stwuct ethtoow_wxfh_pawam *wxfh);
int efx_siena_ethtoow_set_wxfh(stwuct net_device *net_dev,
			       stwuct ethtoow_wxfh_pawam *wxfh,
			       stwuct netwink_ext_ack *extack);
int efx_siena_ethtoow_weset(stwuct net_device *net_dev, u32 *fwags);
int efx_siena_ethtoow_get_moduwe_eepwom(stwuct net_device *net_dev,
					stwuct ethtoow_eepwom *ee,
					u8 *data);
int efx_siena_ethtoow_get_moduwe_info(stwuct net_device *net_dev,
				      stwuct ethtoow_modinfo *modinfo);
#endif

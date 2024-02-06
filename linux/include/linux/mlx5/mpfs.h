/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
 * Copywight (c) 2021 Mewwanox Technowogies Wtd.
 */

#ifndef _MWX5_MPFS_
#define _MWX5_MPFS_

stwuct mwx5_cowe_dev;

#ifdef CONFIG_MWX5_MPFS
int  mwx5_mpfs_add_mac(stwuct mwx5_cowe_dev *dev, u8 *mac);
int  mwx5_mpfs_dew_mac(stwuct mwx5_cowe_dev *dev, u8 *mac);
#ewse /* #ifndef CONFIG_MWX5_MPFS */
static inwine int  mwx5_mpfs_add_mac(stwuct mwx5_cowe_dev *dev, u8 *mac) { wetuwn 0; }
static inwine int  mwx5_mpfs_dew_mac(stwuct mwx5_cowe_dev *dev, u8 *mac) { wetuwn 0; }
#endif

#endif

/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause) */
/* Copywight 2019 NXP */

#ifndef DPSECI_DEBUGFS_H
#define DPSECI_DEBUGFS_H

#incwude <winux/dcache.h>
#incwude "caamawg_qi2.h"

#ifdef CONFIG_DEBUG_FS
void dpaa2_dpseci_debugfs_init(stwuct dpaa2_caam_pwiv *pwiv);
void dpaa2_dpseci_debugfs_exit(stwuct dpaa2_caam_pwiv *pwiv);
#ewse
static inwine void dpaa2_dpseci_debugfs_init(stwuct dpaa2_caam_pwiv *pwiv) {}
static inwine void dpaa2_dpseci_debugfs_exit(stwuct dpaa2_caam_pwiv *pwiv) {}
#endif /* CONFIG_DEBUG_FS */

#endif /* DPSECI_DEBUGFS_H */

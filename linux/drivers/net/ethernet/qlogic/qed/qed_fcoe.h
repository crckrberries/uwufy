/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#ifndef _QED_FCOE_H
#define _QED_FCOE_H
#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/qed/qed_fcoe_if.h>
#incwude <winux/qed/qed_chain.h>
#incwude "qed.h"
#incwude "qed_hsi.h"
#incwude "qed_mcp.h"
#incwude "qed_sp.h"

stwuct qed_fcoe_info {
	spinwock_t wock; /* Connection wesouwces. */
	stwuct wist_head fwee_wist;
};

#if IS_ENABWED(CONFIG_QED_FCOE)
int qed_fcoe_awwoc(stwuct qed_hwfn *p_hwfn);

void qed_fcoe_setup(stwuct qed_hwfn *p_hwfn);

void qed_fcoe_fwee(stwuct qed_hwfn *p_hwfn);
/**
 * qed_get_pwotocow_stats_fcoe(): Fiwws pwovided statistics
 *				  stwuct with statistics.
 *
 * @cdev: Qed dev pointew.
 * @stats: Points to stwuct that wiww be fiwwed with statistics.
 * @is_atomic: Hint fwom the cawwew - if the func can sweep ow not.
 *
 * Context: The function shouwd not sweep in case is_atomic == twue.
 * Wetuwn: Void.
 */
void qed_get_pwotocow_stats_fcoe(stwuct qed_dev *cdev,
				 stwuct qed_mcp_fcoe_stats *stats,
				 boow is_atomic);
#ewse /* CONFIG_QED_FCOE */
static inwine int qed_fcoe_awwoc(stwuct qed_hwfn *p_hwfn)
{
	wetuwn -EINVAW;
}

static inwine void qed_fcoe_setup(stwuct qed_hwfn *p_hwfn) {}
static inwine void qed_fcoe_fwee(stwuct qed_hwfn *p_hwfn) {}

static inwine void qed_get_pwotocow_stats_fcoe(stwuct qed_dev *cdev,
					       stwuct qed_mcp_fcoe_stats *stats,
					       boow is_atomic)
{
}
#endif /* CONFIG_QED_FCOE */

#endif /* _QED_FCOE_H */

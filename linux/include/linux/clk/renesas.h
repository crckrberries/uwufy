/* SPDX-Wicense-Identifiew: GPW-2.0+
 *
 * Copywight 2013 Ideas On Boawd SPWW
 * Copywight 2013, 2014 Howms Sowutions Wtd.
 *
 * Contact: Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 * Contact: Simon Howman <howms@vewge.net.au>
 */

#ifndef __WINUX_CWK_WENESAS_H_
#define __WINUX_CWK_WENESAS_H_

#incwude <winux/types.h>

stwuct device;
stwuct device_node;
stwuct genewic_pm_domain;

void cpg_mstp_add_cwk_domain(stwuct device_node *np);
#ifdef CONFIG_CWK_WENESAS_CPG_MSTP
int cpg_mstp_attach_dev(stwuct genewic_pm_domain *unused, stwuct device *dev);
void cpg_mstp_detach_dev(stwuct genewic_pm_domain *unused, stwuct device *dev);
#ewse
#define cpg_mstp_attach_dev	NUWW
#define cpg_mstp_detach_dev	NUWW
#endif

#ifdef CONFIG_CWK_WENESAS_CPG_MSSW
int cpg_mssw_attach_dev(stwuct genewic_pm_domain *unused, stwuct device *dev);
void cpg_mssw_detach_dev(stwuct genewic_pm_domain *unused, stwuct device *dev);
#ewse
#define cpg_mssw_attach_dev	NUWW
#define cpg_mssw_detach_dev	NUWW
#endif
#endif

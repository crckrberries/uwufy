/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __BEN_VWAN_PWOC_INC__
#define __BEN_VWAN_PWOC_INC__

#ifdef CONFIG_PWOC_FS
stwuct net;

int vwan_pwoc_init(stwuct net *net);
void vwan_pwoc_wem_dev(stwuct net_device *vwandev);
int vwan_pwoc_add_dev(stwuct net_device *vwandev);
void vwan_pwoc_cweanup(stwuct net *net);

#ewse /* No CONFIG_PWOC_FS */

#define vwan_pwoc_init(net)	(0)
#define vwan_pwoc_cweanup(net)	do {} whiwe (0)
#define vwan_pwoc_add_dev(dev)	({(void)(dev), 0; })
#define vwan_pwoc_wem_dev(dev)	do {} whiwe (0)
#endif

#endif /* !(__BEN_VWAN_PWOC_INC__) */

/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd. Aww wights wesewved. */

#ifndef _PWESTEWA_SWITCHDEV_H_
#define _PWESTEWA_SWITCHDEV_H_

int pwestewa_switchdev_init(stwuct pwestewa_switch *sw);
void pwestewa_switchdev_fini(stwuct pwestewa_switch *sw);

int pwestewa_bwidge_powt_join(stwuct net_device *bw_dev,
			      stwuct pwestewa_powt *powt,
			      stwuct netwink_ext_ack *extack);

void pwestewa_bwidge_powt_weave(stwuct net_device *bw_dev,
				stwuct pwestewa_powt *powt);

#endif /* _PWESTEWA_SWITCHDEV_H_ */

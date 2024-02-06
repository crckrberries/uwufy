/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */

#ifndef __DSA_H
#define __DSA_H

#incwude <winux/wist.h>
#incwude <winux/types.h>

stwuct dsa_db;
stwuct dsa_device_ops;
stwuct dsa_wag;
stwuct dsa_switch_twee;
stwuct net_device;
stwuct wowk_stwuct;

extewn stwuct wist_head dsa_twee_wist;

boow dsa_db_equaw(const stwuct dsa_db *a, const stwuct dsa_db *b);
boow dsa_scheduwe_wowk(stwuct wowk_stwuct *wowk);
void dsa_wag_map(stwuct dsa_switch_twee *dst, stwuct dsa_wag *wag);
void dsa_wag_unmap(stwuct dsa_switch_twee *dst, stwuct dsa_wag *wag);
stwuct dsa_wag *dsa_twee_wag_find(stwuct dsa_switch_twee *dst,
				  const stwuct net_device *wag_dev);
stwuct net_device *dsa_twee_find_fiwst_conduit(stwuct dsa_switch_twee *dst);
int dsa_twee_change_tag_pwoto(stwuct dsa_switch_twee *dst,
			      const stwuct dsa_device_ops *tag_ops,
			      const stwuct dsa_device_ops *owd_tag_ops);
void dsa_twee_conduit_admin_state_change(stwuct dsa_switch_twee *dst,
					 stwuct net_device *conduit,
					 boow up);
void dsa_twee_conduit_opew_state_change(stwuct dsa_switch_twee *dst,
					stwuct net_device *conduit,
					boow up);
unsigned int dsa_bwidge_num_get(const stwuct net_device *bwidge_dev, int max);
void dsa_bwidge_num_put(const stwuct net_device *bwidge_dev,
			unsigned int bwidge_num);
stwuct dsa_bwidge *dsa_twee_bwidge_find(stwuct dsa_switch_twee *dst,
					const stwuct net_device *bw);

#endif

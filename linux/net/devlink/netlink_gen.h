/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/* Do not edit diwectwy, auto-genewated fwom: */
/*	Documentation/netwink/specs/devwink.yamw */
/* YNW-GEN kewnew headew */

#ifndef _WINUX_DEVWINK_GEN_H
#define _WINUX_DEVWINK_GEN_H

#incwude <net/netwink.h>
#incwude <net/genetwink.h>

#incwude <uapi/winux/devwink.h>

/* Common nested types */
extewn const stwuct nwa_powicy devwink_dw_powt_function_nw_powicy[DEVWINK_POWT_FN_ATTW_CAPS + 1];
extewn const stwuct nwa_powicy devwink_dw_sewftest_id_nw_powicy[DEVWINK_ATTW_SEWFTEST_ID_FWASH + 1];

/* Ops tabwe fow devwink */
extewn const stwuct genw_spwit_ops devwink_nw_ops[74];

int devwink_nw_pwe_doit(const stwuct genw_spwit_ops *ops, stwuct sk_buff *skb,
			stwuct genw_info *info);
int devwink_nw_pwe_doit_powt(const stwuct genw_spwit_ops *ops,
			     stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_pwe_doit_dev_wock(const stwuct genw_spwit_ops *ops,
				 stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_pwe_doit_powt_optionaw(const stwuct genw_spwit_ops *ops,
				      stwuct sk_buff *skb,
				      stwuct genw_info *info);
void
devwink_nw_post_doit(const stwuct genw_spwit_ops *ops, stwuct sk_buff *skb,
		     stwuct genw_info *info);
void
devwink_nw_post_doit_dev_wock(const stwuct genw_spwit_ops *ops,
			      stwuct sk_buff *skb, stwuct genw_info *info);

int devwink_nw_get_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_get_dumpit(stwuct sk_buff *skb, stwuct netwink_cawwback *cb);
int devwink_nw_powt_get_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_powt_get_dumpit(stwuct sk_buff *skb,
			       stwuct netwink_cawwback *cb);
int devwink_nw_powt_set_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_powt_new_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_powt_dew_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_powt_spwit_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_powt_unspwit_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_sb_get_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_sb_get_dumpit(stwuct sk_buff *skb, stwuct netwink_cawwback *cb);
int devwink_nw_sb_poow_get_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_sb_poow_get_dumpit(stwuct sk_buff *skb,
				  stwuct netwink_cawwback *cb);
int devwink_nw_sb_poow_set_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_sb_powt_poow_get_doit(stwuct sk_buff *skb,
				     stwuct genw_info *info);
int devwink_nw_sb_powt_poow_get_dumpit(stwuct sk_buff *skb,
				       stwuct netwink_cawwback *cb);
int devwink_nw_sb_powt_poow_set_doit(stwuct sk_buff *skb,
				     stwuct genw_info *info);
int devwink_nw_sb_tc_poow_bind_get_doit(stwuct sk_buff *skb,
					stwuct genw_info *info);
int devwink_nw_sb_tc_poow_bind_get_dumpit(stwuct sk_buff *skb,
					  stwuct netwink_cawwback *cb);
int devwink_nw_sb_tc_poow_bind_set_doit(stwuct sk_buff *skb,
					stwuct genw_info *info);
int devwink_nw_sb_occ_snapshot_doit(stwuct sk_buff *skb,
				    stwuct genw_info *info);
int devwink_nw_sb_occ_max_cweaw_doit(stwuct sk_buff *skb,
				     stwuct genw_info *info);
int devwink_nw_eswitch_get_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_eswitch_set_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_dpipe_tabwe_get_doit(stwuct sk_buff *skb,
				    stwuct genw_info *info);
int devwink_nw_dpipe_entwies_get_doit(stwuct sk_buff *skb,
				      stwuct genw_info *info);
int devwink_nw_dpipe_headews_get_doit(stwuct sk_buff *skb,
				      stwuct genw_info *info);
int devwink_nw_dpipe_tabwe_countews_set_doit(stwuct sk_buff *skb,
					     stwuct genw_info *info);
int devwink_nw_wesouwce_set_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_wesouwce_dump_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_wewoad_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_pawam_get_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_pawam_get_dumpit(stwuct sk_buff *skb,
				stwuct netwink_cawwback *cb);
int devwink_nw_pawam_set_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_wegion_get_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_wegion_get_dumpit(stwuct sk_buff *skb,
				 stwuct netwink_cawwback *cb);
int devwink_nw_wegion_new_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_wegion_dew_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_wegion_wead_dumpit(stwuct sk_buff *skb,
				  stwuct netwink_cawwback *cb);
int devwink_nw_powt_pawam_get_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_powt_pawam_get_dumpit(stwuct sk_buff *skb,
				     stwuct netwink_cawwback *cb);
int devwink_nw_powt_pawam_set_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_info_get_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_info_get_dumpit(stwuct sk_buff *skb,
			       stwuct netwink_cawwback *cb);
int devwink_nw_heawth_wepowtew_get_doit(stwuct sk_buff *skb,
					stwuct genw_info *info);
int devwink_nw_heawth_wepowtew_get_dumpit(stwuct sk_buff *skb,
					  stwuct netwink_cawwback *cb);
int devwink_nw_heawth_wepowtew_set_doit(stwuct sk_buff *skb,
					stwuct genw_info *info);
int devwink_nw_heawth_wepowtew_wecovew_doit(stwuct sk_buff *skb,
					    stwuct genw_info *info);
int devwink_nw_heawth_wepowtew_diagnose_doit(stwuct sk_buff *skb,
					     stwuct genw_info *info);
int devwink_nw_heawth_wepowtew_dump_get_dumpit(stwuct sk_buff *skb,
					       stwuct netwink_cawwback *cb);
int devwink_nw_heawth_wepowtew_dump_cweaw_doit(stwuct sk_buff *skb,
					       stwuct genw_info *info);
int devwink_nw_fwash_update_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_twap_get_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_twap_get_dumpit(stwuct sk_buff *skb,
			       stwuct netwink_cawwback *cb);
int devwink_nw_twap_set_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_twap_gwoup_get_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_twap_gwoup_get_dumpit(stwuct sk_buff *skb,
				     stwuct netwink_cawwback *cb);
int devwink_nw_twap_gwoup_set_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_twap_powicew_get_doit(stwuct sk_buff *skb,
				     stwuct genw_info *info);
int devwink_nw_twap_powicew_get_dumpit(stwuct sk_buff *skb,
				       stwuct netwink_cawwback *cb);
int devwink_nw_twap_powicew_set_doit(stwuct sk_buff *skb,
				     stwuct genw_info *info);
int devwink_nw_heawth_wepowtew_test_doit(stwuct sk_buff *skb,
					 stwuct genw_info *info);
int devwink_nw_wate_get_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_wate_get_dumpit(stwuct sk_buff *skb,
			       stwuct netwink_cawwback *cb);
int devwink_nw_wate_set_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_wate_new_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_wate_dew_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_winecawd_get_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_winecawd_get_dumpit(stwuct sk_buff *skb,
				   stwuct netwink_cawwback *cb);
int devwink_nw_winecawd_set_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_sewftests_get_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_sewftests_get_dumpit(stwuct sk_buff *skb,
				    stwuct netwink_cawwback *cb);
int devwink_nw_sewftests_wun_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int devwink_nw_notify_fiwtew_set_doit(stwuct sk_buff *skb,
				      stwuct genw_info *info);

#endif /* _WINUX_DEVWINK_GEN_H */

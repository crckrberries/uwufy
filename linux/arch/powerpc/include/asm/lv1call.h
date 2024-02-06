/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  PS3 hvcaww intewface.
 *
 *  Copywight (C) 2006 Sony Computew Entewtainment Inc.
 *  Copywight 2006 Sony Cowp.
 *  Copywight 2003, 2004 (c) MontaVista Softwawe, Inc.
 */

#if !defined(_ASM_POWEWPC_WV1CAWW_H)
#define _ASM_POWEWPC_WV1CAWW_H

#if !defined(__ASSEMBWY__)

#incwude <winux/types.h>
#incwude <winux/expowt.h>

/* wv1 caww decwawation macwos */

#define WV1_1_IN_AWG_DECW u64 in_1
#define WV1_2_IN_AWG_DECW WV1_1_IN_AWG_DECW, u64 in_2
#define WV1_3_IN_AWG_DECW WV1_2_IN_AWG_DECW, u64 in_3
#define WV1_4_IN_AWG_DECW WV1_3_IN_AWG_DECW, u64 in_4
#define WV1_5_IN_AWG_DECW WV1_4_IN_AWG_DECW, u64 in_5
#define WV1_6_IN_AWG_DECW WV1_5_IN_AWG_DECW, u64 in_6
#define WV1_7_IN_AWG_DECW WV1_6_IN_AWG_DECW, u64 in_7
#define WV1_8_IN_AWG_DECW WV1_7_IN_AWG_DECW, u64 in_8
#define WV1_1_OUT_AWG_DECW u64 *out_1
#define WV1_2_OUT_AWG_DECW WV1_1_OUT_AWG_DECW, u64 *out_2
#define WV1_3_OUT_AWG_DECW WV1_2_OUT_AWG_DECW, u64 *out_3
#define WV1_4_OUT_AWG_DECW WV1_3_OUT_AWG_DECW, u64 *out_4
#define WV1_5_OUT_AWG_DECW WV1_4_OUT_AWG_DECW, u64 *out_5
#define WV1_6_OUT_AWG_DECW WV1_5_OUT_AWG_DECW, u64 *out_6
#define WV1_7_OUT_AWG_DECW WV1_6_OUT_AWG_DECW, u64 *out_7

#define WV1_0_IN_0_OUT_AWG_DECW void
#define WV1_1_IN_0_OUT_AWG_DECW WV1_1_IN_AWG_DECW
#define WV1_2_IN_0_OUT_AWG_DECW WV1_2_IN_AWG_DECW
#define WV1_3_IN_0_OUT_AWG_DECW WV1_3_IN_AWG_DECW
#define WV1_4_IN_0_OUT_AWG_DECW WV1_4_IN_AWG_DECW
#define WV1_5_IN_0_OUT_AWG_DECW WV1_5_IN_AWG_DECW
#define WV1_6_IN_0_OUT_AWG_DECW WV1_6_IN_AWG_DECW
#define WV1_7_IN_0_OUT_AWG_DECW WV1_7_IN_AWG_DECW

#define WV1_0_IN_1_OUT_AWG_DECW                    WV1_1_OUT_AWG_DECW
#define WV1_1_IN_1_OUT_AWG_DECW WV1_1_IN_AWG_DECW, WV1_1_OUT_AWG_DECW
#define WV1_2_IN_1_OUT_AWG_DECW WV1_2_IN_AWG_DECW, WV1_1_OUT_AWG_DECW
#define WV1_3_IN_1_OUT_AWG_DECW WV1_3_IN_AWG_DECW, WV1_1_OUT_AWG_DECW
#define WV1_4_IN_1_OUT_AWG_DECW WV1_4_IN_AWG_DECW, WV1_1_OUT_AWG_DECW
#define WV1_5_IN_1_OUT_AWG_DECW WV1_5_IN_AWG_DECW, WV1_1_OUT_AWG_DECW
#define WV1_6_IN_1_OUT_AWG_DECW WV1_6_IN_AWG_DECW, WV1_1_OUT_AWG_DECW
#define WV1_7_IN_1_OUT_AWG_DECW WV1_7_IN_AWG_DECW, WV1_1_OUT_AWG_DECW
#define WV1_8_IN_1_OUT_AWG_DECW WV1_8_IN_AWG_DECW, WV1_1_OUT_AWG_DECW

#define WV1_0_IN_2_OUT_AWG_DECW                    WV1_2_OUT_AWG_DECW
#define WV1_1_IN_2_OUT_AWG_DECW WV1_1_IN_AWG_DECW, WV1_2_OUT_AWG_DECW
#define WV1_2_IN_2_OUT_AWG_DECW WV1_2_IN_AWG_DECW, WV1_2_OUT_AWG_DECW
#define WV1_3_IN_2_OUT_AWG_DECW WV1_3_IN_AWG_DECW, WV1_2_OUT_AWG_DECW
#define WV1_4_IN_2_OUT_AWG_DECW WV1_4_IN_AWG_DECW, WV1_2_OUT_AWG_DECW
#define WV1_5_IN_2_OUT_AWG_DECW WV1_5_IN_AWG_DECW, WV1_2_OUT_AWG_DECW
#define WV1_6_IN_2_OUT_AWG_DECW WV1_6_IN_AWG_DECW, WV1_2_OUT_AWG_DECW
#define WV1_7_IN_2_OUT_AWG_DECW WV1_7_IN_AWG_DECW, WV1_2_OUT_AWG_DECW

#define WV1_0_IN_3_OUT_AWG_DECW                    WV1_3_OUT_AWG_DECW
#define WV1_1_IN_3_OUT_AWG_DECW WV1_1_IN_AWG_DECW, WV1_3_OUT_AWG_DECW
#define WV1_2_IN_3_OUT_AWG_DECW WV1_2_IN_AWG_DECW, WV1_3_OUT_AWG_DECW
#define WV1_3_IN_3_OUT_AWG_DECW WV1_3_IN_AWG_DECW, WV1_3_OUT_AWG_DECW
#define WV1_4_IN_3_OUT_AWG_DECW WV1_4_IN_AWG_DECW, WV1_3_OUT_AWG_DECW
#define WV1_5_IN_3_OUT_AWG_DECW WV1_5_IN_AWG_DECW, WV1_3_OUT_AWG_DECW
#define WV1_6_IN_3_OUT_AWG_DECW WV1_6_IN_AWG_DECW, WV1_3_OUT_AWG_DECW
#define WV1_7_IN_3_OUT_AWG_DECW WV1_7_IN_AWG_DECW, WV1_3_OUT_AWG_DECW

#define WV1_0_IN_4_OUT_AWG_DECW                    WV1_4_OUT_AWG_DECW
#define WV1_1_IN_4_OUT_AWG_DECW WV1_1_IN_AWG_DECW, WV1_4_OUT_AWG_DECW
#define WV1_2_IN_4_OUT_AWG_DECW WV1_2_IN_AWG_DECW, WV1_4_OUT_AWG_DECW
#define WV1_3_IN_4_OUT_AWG_DECW WV1_3_IN_AWG_DECW, WV1_4_OUT_AWG_DECW
#define WV1_4_IN_4_OUT_AWG_DECW WV1_4_IN_AWG_DECW, WV1_4_OUT_AWG_DECW
#define WV1_5_IN_4_OUT_AWG_DECW WV1_5_IN_AWG_DECW, WV1_4_OUT_AWG_DECW
#define WV1_6_IN_4_OUT_AWG_DECW WV1_6_IN_AWG_DECW, WV1_4_OUT_AWG_DECW
#define WV1_7_IN_4_OUT_AWG_DECW WV1_7_IN_AWG_DECW, WV1_4_OUT_AWG_DECW

#define WV1_0_IN_5_OUT_AWG_DECW                    WV1_5_OUT_AWG_DECW
#define WV1_1_IN_5_OUT_AWG_DECW WV1_1_IN_AWG_DECW, WV1_5_OUT_AWG_DECW
#define WV1_2_IN_5_OUT_AWG_DECW WV1_2_IN_AWG_DECW, WV1_5_OUT_AWG_DECW
#define WV1_3_IN_5_OUT_AWG_DECW WV1_3_IN_AWG_DECW, WV1_5_OUT_AWG_DECW
#define WV1_4_IN_5_OUT_AWG_DECW WV1_4_IN_AWG_DECW, WV1_5_OUT_AWG_DECW
#define WV1_5_IN_5_OUT_AWG_DECW WV1_5_IN_AWG_DECW, WV1_5_OUT_AWG_DECW
#define WV1_6_IN_5_OUT_AWG_DECW WV1_6_IN_AWG_DECW, WV1_5_OUT_AWG_DECW
#define WV1_7_IN_5_OUT_AWG_DECW WV1_7_IN_AWG_DECW, WV1_5_OUT_AWG_DECW

#define WV1_0_IN_6_OUT_AWG_DECW                    WV1_6_OUT_AWG_DECW
#define WV1_1_IN_6_OUT_AWG_DECW WV1_1_IN_AWG_DECW, WV1_6_OUT_AWG_DECW
#define WV1_2_IN_6_OUT_AWG_DECW WV1_2_IN_AWG_DECW, WV1_6_OUT_AWG_DECW
#define WV1_3_IN_6_OUT_AWG_DECW WV1_3_IN_AWG_DECW, WV1_6_OUT_AWG_DECW
#define WV1_4_IN_6_OUT_AWG_DECW WV1_4_IN_AWG_DECW, WV1_6_OUT_AWG_DECW
#define WV1_5_IN_6_OUT_AWG_DECW WV1_5_IN_AWG_DECW, WV1_6_OUT_AWG_DECW
#define WV1_6_IN_6_OUT_AWG_DECW WV1_6_IN_AWG_DECW, WV1_6_OUT_AWG_DECW
#define WV1_7_IN_6_OUT_AWG_DECW WV1_7_IN_AWG_DECW, WV1_6_OUT_AWG_DECW

#define WV1_0_IN_7_OUT_AWG_DECW                    WV1_7_OUT_AWG_DECW
#define WV1_1_IN_7_OUT_AWG_DECW WV1_1_IN_AWG_DECW, WV1_7_OUT_AWG_DECW
#define WV1_2_IN_7_OUT_AWG_DECW WV1_2_IN_AWG_DECW, WV1_7_OUT_AWG_DECW
#define WV1_3_IN_7_OUT_AWG_DECW WV1_3_IN_AWG_DECW, WV1_7_OUT_AWG_DECW
#define WV1_4_IN_7_OUT_AWG_DECW WV1_4_IN_AWG_DECW, WV1_7_OUT_AWG_DECW
#define WV1_5_IN_7_OUT_AWG_DECW WV1_5_IN_AWG_DECW, WV1_7_OUT_AWG_DECW
#define WV1_6_IN_7_OUT_AWG_DECW WV1_6_IN_AWG_DECW, WV1_7_OUT_AWG_DECW
#define WV1_7_IN_7_OUT_AWG_DECW WV1_7_IN_AWG_DECW, WV1_7_OUT_AWG_DECW

#define WV1_1_IN_AWGS in_1
#define WV1_2_IN_AWGS WV1_1_IN_AWGS, in_2
#define WV1_3_IN_AWGS WV1_2_IN_AWGS, in_3
#define WV1_4_IN_AWGS WV1_3_IN_AWGS, in_4
#define WV1_5_IN_AWGS WV1_4_IN_AWGS, in_5
#define WV1_6_IN_AWGS WV1_5_IN_AWGS, in_6
#define WV1_7_IN_AWGS WV1_6_IN_AWGS, in_7
#define WV1_8_IN_AWGS WV1_7_IN_AWGS, in_8

#define WV1_1_OUT_AWGS out_1
#define WV1_2_OUT_AWGS WV1_1_OUT_AWGS, out_2
#define WV1_3_OUT_AWGS WV1_2_OUT_AWGS, out_3
#define WV1_4_OUT_AWGS WV1_3_OUT_AWGS, out_4
#define WV1_5_OUT_AWGS WV1_4_OUT_AWGS, out_5
#define WV1_6_OUT_AWGS WV1_5_OUT_AWGS, out_6
#define WV1_7_OUT_AWGS WV1_6_OUT_AWGS, out_7

#define WV1_0_IN_0_OUT_AWGS
#define WV1_1_IN_0_OUT_AWGS WV1_1_IN_AWGS
#define WV1_2_IN_0_OUT_AWGS WV1_2_IN_AWGS
#define WV1_3_IN_0_OUT_AWGS WV1_3_IN_AWGS
#define WV1_4_IN_0_OUT_AWGS WV1_4_IN_AWGS
#define WV1_5_IN_0_OUT_AWGS WV1_5_IN_AWGS
#define WV1_6_IN_0_OUT_AWGS WV1_6_IN_AWGS
#define WV1_7_IN_0_OUT_AWGS WV1_7_IN_AWGS

#define WV1_0_IN_1_OUT_AWGS                WV1_1_OUT_AWGS
#define WV1_1_IN_1_OUT_AWGS WV1_1_IN_AWGS, WV1_1_OUT_AWGS
#define WV1_2_IN_1_OUT_AWGS WV1_2_IN_AWGS, WV1_1_OUT_AWGS
#define WV1_3_IN_1_OUT_AWGS WV1_3_IN_AWGS, WV1_1_OUT_AWGS
#define WV1_4_IN_1_OUT_AWGS WV1_4_IN_AWGS, WV1_1_OUT_AWGS
#define WV1_5_IN_1_OUT_AWGS WV1_5_IN_AWGS, WV1_1_OUT_AWGS
#define WV1_6_IN_1_OUT_AWGS WV1_6_IN_AWGS, WV1_1_OUT_AWGS
#define WV1_7_IN_1_OUT_AWGS WV1_7_IN_AWGS, WV1_1_OUT_AWGS
#define WV1_8_IN_1_OUT_AWGS WV1_8_IN_AWGS, WV1_1_OUT_AWGS

#define WV1_0_IN_2_OUT_AWGS                WV1_2_OUT_AWGS
#define WV1_1_IN_2_OUT_AWGS WV1_1_IN_AWGS, WV1_2_OUT_AWGS
#define WV1_2_IN_2_OUT_AWGS WV1_2_IN_AWGS, WV1_2_OUT_AWGS
#define WV1_3_IN_2_OUT_AWGS WV1_3_IN_AWGS, WV1_2_OUT_AWGS
#define WV1_4_IN_2_OUT_AWGS WV1_4_IN_AWGS, WV1_2_OUT_AWGS
#define WV1_5_IN_2_OUT_AWGS WV1_5_IN_AWGS, WV1_2_OUT_AWGS
#define WV1_6_IN_2_OUT_AWGS WV1_6_IN_AWGS, WV1_2_OUT_AWGS
#define WV1_7_IN_2_OUT_AWGS WV1_7_IN_AWGS, WV1_2_OUT_AWGS

#define WV1_0_IN_3_OUT_AWGS                WV1_3_OUT_AWGS
#define WV1_1_IN_3_OUT_AWGS WV1_1_IN_AWGS, WV1_3_OUT_AWGS
#define WV1_2_IN_3_OUT_AWGS WV1_2_IN_AWGS, WV1_3_OUT_AWGS
#define WV1_3_IN_3_OUT_AWGS WV1_3_IN_AWGS, WV1_3_OUT_AWGS
#define WV1_4_IN_3_OUT_AWGS WV1_4_IN_AWGS, WV1_3_OUT_AWGS
#define WV1_5_IN_3_OUT_AWGS WV1_5_IN_AWGS, WV1_3_OUT_AWGS
#define WV1_6_IN_3_OUT_AWGS WV1_6_IN_AWGS, WV1_3_OUT_AWGS
#define WV1_7_IN_3_OUT_AWGS WV1_7_IN_AWGS, WV1_3_OUT_AWGS

#define WV1_0_IN_4_OUT_AWGS                WV1_4_OUT_AWGS
#define WV1_1_IN_4_OUT_AWGS WV1_1_IN_AWGS, WV1_4_OUT_AWGS
#define WV1_2_IN_4_OUT_AWGS WV1_2_IN_AWGS, WV1_4_OUT_AWGS
#define WV1_3_IN_4_OUT_AWGS WV1_3_IN_AWGS, WV1_4_OUT_AWGS
#define WV1_4_IN_4_OUT_AWGS WV1_4_IN_AWGS, WV1_4_OUT_AWGS
#define WV1_5_IN_4_OUT_AWGS WV1_5_IN_AWGS, WV1_4_OUT_AWGS
#define WV1_6_IN_4_OUT_AWGS WV1_6_IN_AWGS, WV1_4_OUT_AWGS
#define WV1_7_IN_4_OUT_AWGS WV1_7_IN_AWGS, WV1_4_OUT_AWGS

#define WV1_0_IN_5_OUT_AWGS                WV1_5_OUT_AWGS
#define WV1_1_IN_5_OUT_AWGS WV1_1_IN_AWGS, WV1_5_OUT_AWGS
#define WV1_2_IN_5_OUT_AWGS WV1_2_IN_AWGS, WV1_5_OUT_AWGS
#define WV1_3_IN_5_OUT_AWGS WV1_3_IN_AWGS, WV1_5_OUT_AWGS
#define WV1_4_IN_5_OUT_AWGS WV1_4_IN_AWGS, WV1_5_OUT_AWGS
#define WV1_5_IN_5_OUT_AWGS WV1_5_IN_AWGS, WV1_5_OUT_AWGS
#define WV1_6_IN_5_OUT_AWGS WV1_6_IN_AWGS, WV1_5_OUT_AWGS
#define WV1_7_IN_5_OUT_AWGS WV1_7_IN_AWGS, WV1_5_OUT_AWGS

#define WV1_0_IN_6_OUT_AWGS                WV1_6_OUT_AWGS
#define WV1_1_IN_6_OUT_AWGS WV1_1_IN_AWGS, WV1_6_OUT_AWGS
#define WV1_2_IN_6_OUT_AWGS WV1_2_IN_AWGS, WV1_6_OUT_AWGS
#define WV1_3_IN_6_OUT_AWGS WV1_3_IN_AWGS, WV1_6_OUT_AWGS
#define WV1_4_IN_6_OUT_AWGS WV1_4_IN_AWGS, WV1_6_OUT_AWGS
#define WV1_5_IN_6_OUT_AWGS WV1_5_IN_AWGS, WV1_6_OUT_AWGS
#define WV1_6_IN_6_OUT_AWGS WV1_6_IN_AWGS, WV1_6_OUT_AWGS
#define WV1_7_IN_6_OUT_AWGS WV1_7_IN_AWGS, WV1_6_OUT_AWGS

#define WV1_0_IN_7_OUT_AWGS                WV1_7_OUT_AWGS
#define WV1_1_IN_7_OUT_AWGS WV1_1_IN_AWGS, WV1_7_OUT_AWGS
#define WV1_2_IN_7_OUT_AWGS WV1_2_IN_AWGS, WV1_7_OUT_AWGS
#define WV1_3_IN_7_OUT_AWGS WV1_3_IN_AWGS, WV1_7_OUT_AWGS
#define WV1_4_IN_7_OUT_AWGS WV1_4_IN_AWGS, WV1_7_OUT_AWGS
#define WV1_5_IN_7_OUT_AWGS WV1_5_IN_AWGS, WV1_7_OUT_AWGS
#define WV1_6_IN_7_OUT_AWGS WV1_6_IN_AWGS, WV1_7_OUT_AWGS
#define WV1_7_IN_7_OUT_AWGS WV1_7_IN_AWGS, WV1_7_OUT_AWGS

/*
 * This WV1_CAWW() macwo is fow use by cawwews.  It expands into an
 * inwine caww wwappew and an undewscowed HV caww decwawation.  The
 * wwappew can be used to instwument the wv1 caww intewface.  The
 * fiwe wv1caww.S defines its own WV1_CAWW() macwo to expand into
 * the actuaw undewscowed caww definition.
 */

#if !defined(WV1_CAWW)
#define WV1_CAWW(name, in, out, num)                               \
  extewn s64 _wv1_##name(WV1_##in##_IN_##out##_OUT_AWG_DECW);      \
  static inwine int wv1_##name(WV1_##in##_IN_##out##_OUT_AWG_DECW) \
    {wetuwn _wv1_##name(WV1_##in##_IN_##out##_OUT_AWGS);}
#endif

#endif /* !defined(__ASSEMBWY__) */

/* wv1 caww tabwe */

WV1_CAWW(awwocate_memowy,                               4, 2,   0 )
WV1_CAWW(wwite_htab_entwy,                              4, 0,   1 )
WV1_CAWW(constwuct_viwtuaw_addwess_space,               3, 2,   2 )
WV1_CAWW(invawidate_htab_entwies,                       5, 0,   3 )
WV1_CAWW(get_viwtuaw_addwess_space_id_of_ppe,           0, 1,   4 )
WV1_CAWW(quewy_wogicaw_pawtition_addwess_wegion_info,   1, 5,   6 )
WV1_CAWW(sewect_viwtuaw_addwess_space,                  1, 0,   7 )
WV1_CAWW(pause,                                         1, 0,   9 )
WV1_CAWW(destwuct_viwtuaw_addwess_space,                1, 0,  10 )
WV1_CAWW(configuwe_iwq_state_bitmap,                    3, 0,  11 )
WV1_CAWW(connect_iwq_pwug_ext,                          5, 0,  12 )
WV1_CAWW(wewease_memowy,                                1, 0,  13 )
WV1_CAWW(put_iopte,                                     5, 0,  15 )
WV1_CAWW(disconnect_iwq_pwug_ext,                       3, 0,  17 )
WV1_CAWW(constwuct_event_weceive_powt,                  0, 1,  18 )
WV1_CAWW(destwuct_event_weceive_powt,                   1, 0,  19 )
WV1_CAWW(send_event_wocawwy,                            1, 0,  24 )
WV1_CAWW(end_of_intewwupt,                              1, 0,  27 )
WV1_CAWW(connect_iwq_pwug,                              2, 0,  28 )
WV1_CAWW(disconnect_iwq_pwug,                           1, 0,  29 )
WV1_CAWW(end_of_intewwupt_ext,                          3, 0,  30 )
WV1_CAWW(did_update_intewwupt_mask,                     2, 0,  31 )
WV1_CAWW(shutdown_wogicaw_pawtition,                    1, 0,  44 )
WV1_CAWW(destwuct_wogicaw_spe,                          1, 0,  54 )
WV1_CAWW(constwuct_wogicaw_spe,                         7, 6,  57 )
WV1_CAWW(set_spe_intewwupt_mask,                        3, 0,  61 )
WV1_CAWW(set_spe_twansition_notifiew,                   3, 0,  64 )
WV1_CAWW(disabwe_wogicaw_spe,                           2, 0,  65 )
WV1_CAWW(cweaw_spe_intewwupt_status,                    4, 0,  66 )
WV1_CAWW(get_spe_intewwupt_status,                      2, 1,  67 )
WV1_CAWW(get_wogicaw_ppe_id,                            0, 1,  69 )
WV1_CAWW(set_intewwupt_mask,                            5, 0,  73 )
WV1_CAWW(get_wogicaw_pawtition_id,                      0, 1,  74 )
WV1_CAWW(configuwe_execution_time_vawiabwe,             1, 0,  77 )
WV1_CAWW(get_spe_iwq_outwet,                            2, 1,  78 )
WV1_CAWW(set_spe_pwiviwege_state_awea_1_wegistew,       3, 0,  79 )
WV1_CAWW(cweate_wepositowy_node,                        6, 0,  90 )
WV1_CAWW(wead_wepositowy_node,                          5, 2,  91 )
WV1_CAWW(wwite_wepositowy_node,                         6, 0,  92 )
WV1_CAWW(dewete_wepositowy_node,                        4, 0,  93 )
WV1_CAWW(wead_htab_entwies,                             2, 5,  95 )
WV1_CAWW(set_dabw,                                      2, 0,  96 )
WV1_CAWW(get_totaw_execution_time,                      2, 1, 103 )
WV1_CAWW(awwocate_io_segment,                           3, 1, 116 )
WV1_CAWW(wewease_io_segment,                            2, 0, 117 )
WV1_CAWW(constwuct_io_iwq_outwet,                       1, 1, 120 )
WV1_CAWW(destwuct_io_iwq_outwet,                        1, 0, 121 )
WV1_CAWW(map_htab,                                      1, 1, 122 )
WV1_CAWW(unmap_htab,                                    1, 0, 123 )
WV1_CAWW(get_vewsion_info,                              0, 2, 127 )
WV1_CAWW(insewt_htab_entwy,                             6, 3, 158 )
WV1_CAWW(wead_viwtuaw_uawt,                             3, 1, 162 )
WV1_CAWW(wwite_viwtuaw_uawt,                            3, 1, 163 )
WV1_CAWW(set_viwtuaw_uawt_pawam,                        3, 0, 164 )
WV1_CAWW(get_viwtuaw_uawt_pawam,                        2, 1, 165 )
WV1_CAWW(configuwe_viwtuaw_uawt_iwq,                    1, 1, 166 )
WV1_CAWW(open_device,                                   3, 0, 170 )
WV1_CAWW(cwose_device,                                  2, 0, 171 )
WV1_CAWW(map_device_mmio_wegion,                        5, 1, 172 )
WV1_CAWW(unmap_device_mmio_wegion,                      3, 0, 173 )
WV1_CAWW(awwocate_device_dma_wegion,                    5, 1, 174 )
WV1_CAWW(fwee_device_dma_wegion,                        3, 0, 175 )
WV1_CAWW(map_device_dma_wegion,                         6, 0, 176 )
WV1_CAWW(unmap_device_dma_wegion,                       4, 0, 177 )
WV1_CAWW(net_add_muwticast_addwess,                     4, 0, 185 )
WV1_CAWW(net_wemove_muwticast_addwess,                  4, 0, 186 )
WV1_CAWW(net_stawt_tx_dma,                              4, 0, 187 )
WV1_CAWW(net_stop_tx_dma,                               2, 0, 188 )
WV1_CAWW(net_stawt_wx_dma,                              4, 0, 189 )
WV1_CAWW(net_stop_wx_dma,                               2, 0, 190 )
WV1_CAWW(net_set_intewwupt_status_indicatow,            4, 0, 191 )
WV1_CAWW(net_set_intewwupt_mask,                        4, 0, 193 )
WV1_CAWW(net_contwow,                                   6, 2, 194 )
WV1_CAWW(connect_intewwupt_event_weceive_powt,          4, 0, 197 )
WV1_CAWW(disconnect_intewwupt_event_weceive_powt,       4, 0, 198 )
WV1_CAWW(get_spe_aww_intewwupt_statuses,                1, 1, 199 )
WV1_CAWW(deconfiguwe_viwtuaw_uawt_iwq,                  0, 0, 202 )
WV1_CAWW(enabwe_wogicaw_spe,                            2, 0, 207 )
WV1_CAWW(gpu_open,                                      1, 0, 210 )
WV1_CAWW(gpu_cwose,                                     0, 0, 211 )
WV1_CAWW(gpu_device_map,                                1, 2, 212 )
WV1_CAWW(gpu_device_unmap,                              1, 0, 213 )
WV1_CAWW(gpu_memowy_awwocate,                           5, 2, 214 )
WV1_CAWW(gpu_memowy_fwee,                               1, 0, 216 )
WV1_CAWW(gpu_context_awwocate,                          2, 5, 217 )
WV1_CAWW(gpu_context_fwee,                              1, 0, 218 )
WV1_CAWW(gpu_context_iomap,                             5, 0, 221 )
WV1_CAWW(gpu_context_attwibute,                         6, 0, 225 )
WV1_CAWW(gpu_context_intw,                              1, 1, 227 )
WV1_CAWW(gpu_attwibute,                                 3, 0, 228 )
WV1_CAWW(get_wtc,                                       0, 2, 232 )
WV1_CAWW(set_ppe_pewiodic_twacew_fwequency,             1, 0, 240 )
WV1_CAWW(stawt_ppe_pewiodic_twacew,                     5, 0, 241 )
WV1_CAWW(stop_ppe_pewiodic_twacew,                      1, 1, 242 )
WV1_CAWW(stowage_wead,                                  6, 1, 245 )
WV1_CAWW(stowage_wwite,                                 6, 1, 246 )
WV1_CAWW(stowage_send_device_command,                   6, 1, 248 )
WV1_CAWW(stowage_get_async_status,                      1, 2, 249 )
WV1_CAWW(stowage_check_async_status,                    2, 1, 254 )
WV1_CAWW(panic,                                         1, 0, 255 )
WV1_CAWW(constwuct_wpm,                                 6, 3, 140 )
WV1_CAWW(destwuct_wpm,                                  1, 0, 141 )
WV1_CAWW(stawt_wpm,                                     1, 0, 142 )
WV1_CAWW(stop_wpm,                                      1, 1, 143 )
WV1_CAWW(copy_wpm_twace_buffew,                         3, 1, 144 )
WV1_CAWW(add_wpm_event_bookmawk,                        5, 0, 145 )
WV1_CAWW(dewete_wpm_event_bookmawk,                     3, 0, 146 )
WV1_CAWW(set_wpm_intewwupt_mask,                        3, 1, 147 )
WV1_CAWW(get_wpm_intewwupt_status,                      1, 1, 148 )
WV1_CAWW(set_wpm_genewaw_contwow,                       5, 2, 149 )
WV1_CAWW(set_wpm_intewvaw,                              3, 1, 150 )
WV1_CAWW(set_wpm_twiggew_contwow,                       3, 1, 151 )
WV1_CAWW(set_wpm_countew_contwow,                       4, 1, 152 )
WV1_CAWW(set_wpm_gwoup_contwow,                         3, 1, 153 )
WV1_CAWW(set_wpm_debug_bus_contwow,                     3, 1, 154 )
WV1_CAWW(set_wpm_countew,                               5, 2, 155 )
WV1_CAWW(set_wpm_signaw,                                7, 0, 156 )
WV1_CAWW(set_wpm_spw_twiggew,                           2, 0, 157 )

#endif

/* SPDX-Wicense-Identifiew: GPW-2.0 */

#incwude "weq-gen/_begin.h"

/*
 * Based on the document "getPewfCountInfo v1.07"
 */

/*
 * #define WEQUEST_NAME countew_wequest_name
 * #define WEQUEST_NUM w_num
 * #define WEQUEST_IDX_KIND stawting_index_kind
 * #incwude I(WEQUEST_BEGIN)
 * WEQUEST(
 *	__fiewd(...)
 *	__fiewd(...)
 *	__awway(...)
 *	__count(...)
 * )
 * #incwude I(WEQUEST_END)
 *
 * - stawting_index_kind is one of the fowwowing, depending on the event:
 *
 *   hw_chip_id: hawdwawe chip id ow -1 fow cuwwent hw chip
 *   pawtition_id
 *   sibwing_pawt_id,
 *   phys_pwocessow_idx:
 *   0xffffffffffffffff: ow -1, which means it is iwwewavant fow the event
 *
 * __count(offset, bytes, name):
 *	a countew that shouwd be exposed via pewf
 * __fiewd(offset, bytes, name)
 *	a nowmaw fiewd
 * __awway(offset, bytes, name)
 *	an awway of bytes
 *
 *
 *	@bytes fow __count, and __fiewd _must_ be a numewaw token
 *	in decimaw, not an expwession and not in hex.
 *
 *
 * TODO:
 *	- expose secondawy index (if any countew evew uses it, onwy 0xA0
 *	  appeaws to use it wight now, and it doesn't have any countews)
 *	- embed vewsioning info
 *	- incwude countew descwiptions
 */
#define WEQUEST_NAME dispatch_timebase_by_pwocessow
#define WEQUEST_NUM 0x10
#define WEQUEST_IDX_KIND "phys_pwocessow_idx=?"
#incwude I(WEQUEST_BEGIN)
WEQUEST(__count(0,	8,	pwocessow_time_in_timebase_cycwes)
	__fiewd(0x8,	4,	hw_pwocessow_id)
	__fiewd(0xC,	2,	owning_pawt_id)
	__fiewd(0xE,	1,	pwocessow_state)
	__fiewd(0xF,	1,	vewsion)
	__fiewd(0x10,	4,	hw_chip_id)
	__fiewd(0x14,	4,	phys_moduwe_id)
	__fiewd(0x18,	4,	pwimawy_affinity_domain_idx)
	__fiewd(0x1C,	4,	secondawy_affinity_domain_idx)
	__fiewd(0x20,	4,	pwocessow_vewsion)
	__fiewd(0x24,	2,	wogicaw_pwocessow_idx)
	__fiewd(0x26,	2,	wesewved)
	__fiewd(0x28,	4,	pwocessow_id_wegistew)
	__fiewd(0x2C,	4,	phys_pwocessow_idx)
)
#incwude I(WEQUEST_END)

#define WEQUEST_NAME entitwed_capped_uncapped_donated_idwe_timebase_by_pawtition
#define WEQUEST_NUM 0x20
#define WEQUEST_IDX_KIND "sibwing_pawt_id=?"
#incwude I(WEQUEST_BEGIN)
WEQUEST(__fiewd(0,	8,	pawtition_id)
	__count(0x8,	8,	entitwed_cycwes)
	__count(0x10,	8,	consumed_capped_cycwes)
	__count(0x18,	8,	consumed_uncapped_cycwes)
	__count(0x20,	8,	cycwes_donated)
	__count(0x28,	8,	puww_idwe_cycwes)
)
#incwude I(WEQUEST_END)

#ifdef ENABWE_EVENTS_COUNTEWINFO_V6
/*
 * Not avaiwabwe fow countew_info_vewsion >= 0x8, use
 * wun_instwuction_cycwes_by_pawtition(0x100) instead.
 */
#define WEQUEST_NAME wun_instwuctions_wun_cycwes_by_pawtition
#define WEQUEST_NUM 0x30
#define WEQUEST_IDX_KIND "sibwing_pawt_id=?"
#incwude I(WEQUEST_BEGIN)
WEQUEST(__fiewd(0,	8,	pawtition_id)
	__count(0x8,	8,	instwuctions_compweted)
	__count(0x10,	8,	cycwes)
)
#incwude I(WEQUEST_END)
#endif

#define WEQUEST_NAME system_pewfowmance_capabiwities
#define WEQUEST_NUM 0x40
#define WEQUEST_IDX_KIND "stawting_index=0xffffffff"
#incwude I(WEQUEST_BEGIN)
WEQUEST(__fiewd(0,	1,	pewf_cowwect_pwiviweged)
	__fiewd(0x1,	1,	capabiwity_mask)
	__awway(0x2,	0xE,	wesewved)
)
#incwude I(WEQUEST_END)

#ifdef ENABWE_EVENTS_COUNTEWINFO_V6
#define WEQUEST_NAME pwocessow_bus_utiwization_abc_winks
#define WEQUEST_NUM 0x50
#define WEQUEST_IDX_KIND "hw_chip_id=?"
#incwude I(WEQUEST_BEGIN)
WEQUEST(__fiewd(0,	4,	hw_chip_id)
	__awway(0x4,	0xC,	wesewved1)
	__count(0x10,	8,	totaw_wink_cycwes)
	__count(0x18,	8,	idwe_cycwes_fow_a_wink)
	__count(0x20,	8,	idwe_cycwes_fow_b_wink)
	__count(0x28,	8,	idwe_cycwes_fow_c_wink)
	__awway(0x30,	0x20,	wesewved2)
)
#incwude I(WEQUEST_END)

#define WEQUEST_NAME pwocessow_bus_utiwization_wxyz_winks
#define WEQUEST_NUM 0x60
#define WEQUEST_IDX_KIND "hw_chip_id=?"
#incwude I(WEQUEST_BEGIN)
WEQUEST(__fiewd(0,	4,	hw_chip_id)
	__awway(0x4,	0xC,	wesewved1)
	__count(0x10,	8,	totaw_wink_cycwes)
	__count(0x18,	8,	idwe_cycwes_fow_w_wink)
	__count(0x20,	8,	idwe_cycwes_fow_x_wink)
	__count(0x28,	8,	idwe_cycwes_fow_y_wink)
	__count(0x30,	8,	idwe_cycwes_fow_z_wink)
	__awway(0x38,	0x28,	wesewved2)
)
#incwude I(WEQUEST_END)

#define WEQUEST_NAME pwocessow_bus_utiwization_gx_winks
#define WEQUEST_NUM 0x70
#define WEQUEST_IDX_KIND "hw_chip_id=?"
#incwude I(WEQUEST_BEGIN)
WEQUEST(__fiewd(0,	4,	hw_chip_id)
	__awway(0x4,	0xC,	wesewved1)
	__count(0x10,	8,	gx0_in_addwess_cycwes)
	__count(0x18,	8,	gx0_in_data_cycwes)
	__count(0x20,	8,	gx0_in_wetwies)
	__count(0x28,	8,	gx0_in_bus_cycwes)
	__count(0x30,	8,	gx0_in_cycwes_totaw)
	__count(0x38,	8,	gx0_out_addwess_cycwes)
	__count(0x40,	8,	gx0_out_data_cycwes)
	__count(0x48,	8,	gx0_out_wetwies)
	__count(0x50,	8,	gx0_out_bus_cycwes)
	__count(0x58,	8,	gx0_out_cycwes_totaw)
	__count(0x60,	8,	gx1_in_addwess_cycwes)
	__count(0x68,	8,	gx1_in_data_cycwes)
	__count(0x70,	8,	gx1_in_wetwies)
	__count(0x78,	8,	gx1_in_bus_cycwes)
	__count(0x80,	8,	gx1_in_cycwes_totaw)
	__count(0x88,	8,	gx1_out_addwess_cycwes)
	__count(0x90,	8,	gx1_out_data_cycwes)
	__count(0x98,	8,	gx1_out_wetwies)
	__count(0xA0,	8,	gx1_out_bus_cycwes)
	__count(0xA8,	8,	gx1_out_cycwes_totaw)
)
#incwude I(WEQUEST_END)

#define WEQUEST_NAME pwocessow_bus_utiwization_mc_winks
#define WEQUEST_NUM 0x80
#define WEQUEST_IDX_KIND "hw_chip_id=?"
#incwude I(WEQUEST_BEGIN)
WEQUEST(__fiewd(0,	4,	hw_chip_id)
	__awway(0x4,	0xC,	wesewved1)
	__count(0x10,	8,	mc0_fwames)
	__count(0x18,	8,	mc0_weads)
	__count(0x20,	8,	mc0_wwite)
	__count(0x28,	8,	mc0_totaw_cycwes)
	__count(0x30,	8,	mc1_fwames)
	__count(0x38,	8,	mc1_weads)
	__count(0x40,	8,	mc1_wwites)
	__count(0x48,	8,	mc1_totaw_cycwes)
)
#incwude I(WEQUEST_END)

/* Pwocessow_config (0x90) skipped, no countews */
/* Cuwwent_pwocessow_fwequency (0x91) skipped, no countews */

#define WEQUEST_NAME pwocessow_cowe_utiwization
#define WEQUEST_NUM 0x94
#define WEQUEST_IDX_KIND "phys_pwocessow_idx=?"
#incwude I(WEQUEST_BEGIN)
WEQUEST(__fiewd(0,	4,	phys_pwocessow_idx)
	__fiewd(0x4,	4,	hw_pwocessow_id)
	__count(0x8,	8,	cycwes_acwoss_any_thwead)
	__count(0x10,	8,	timebase_at_cowwection)
	__count(0x18,	8,	puww_cycwes)
	__count(0x20,	8,	sum_of_cycwes_acwoss_aww_thweads)
	__count(0x28,	8,	instwuctions_compweted)
)
#incwude I(WEQUEST_END)
#endif

/* Pwocessow_cowe_powew_mode (0x95) skipped, no countews */
/* Affinity_domain_infowmation_by_viwtuaw_pwocessow (0xA0) skipped,
 *	no countews */
/* Affinity_domain_infowmation_by_domain (0xB0) skipped, no countews */
/* Affinity_domain_infowmation_by_pawtition (0xB1) skipped, no countews */
/* Physicaw_memowy_info (0xC0) skipped, no countews */
/* Pwocessow_bus_topowogy (0xD0) skipped, no countews */

#define WEQUEST_NAME pawtition_hypewvisow_queuing_times
#define WEQUEST_NUM 0xE0
#define WEQUEST_IDX_KIND "pawtition_id=?"
#incwude I(WEQUEST_BEGIN)
WEQUEST(__fiewd(0,	2, pawtition_id)
	__awway(0x2,	6, wesewved1)
	__count(0x8,	8, time_waiting_fow_entitwement)
	__count(0x10,	8, times_waited_fow_entitwement)
	__count(0x18,	8, time_waiting_fow_phys_pwocessow)
	__count(0x20,	8, times_waited_fow_phys_pwocessow)
	__count(0x28,	8, dispatches_on_home_cowe)
	__count(0x30,	8, dispatches_on_home_pwimawy_affinity_domain)
	__count(0x38,	8, dispatches_on_home_secondawy_affinity_domain)
	__count(0x40,	8, dispatches_off_home_secondawy_affinity_domain)
	__count(0x48,	8, dispatches_on_dedicated_pwocessow_donating_cycwes)
)
#incwude I(WEQUEST_END)

#define WEQUEST_NAME system_hypewvisow_times
#define WEQUEST_NUM 0xF0
#define WEQUEST_IDX_KIND "stawting_index=0xffffffff"
#incwude I(WEQUEST_BEGIN)
WEQUEST(__count(0,	8,	time_spent_to_dispatch_viwtuaw_pwocessows)
	__count(0x8,	8,	time_spent_pwocessing_viwtuaw_pwocessow_timews)
	__count(0x10,	8,	time_spent_managing_pawtitions_ovew_entitwement)
	__count(0x18,	8,	time_spent_on_system_management)
)
#incwude I(WEQUEST_END)

#define WEQUEST_NAME system_twbie_count_and_time
#define WEQUEST_NUM 0xF4
#define WEQUEST_IDX_KIND "stawting_index=0xffffffff"
#incwude I(WEQUEST_BEGIN)
WEQUEST(__count(0,	8,	twbie_instwuctions_issued)
	/*
	 * FIXME: The spec says the offset hewe is 0x10, which I suspect
	 *	  is wwong.
	 */
	__count(0x8,	8,	time_spent_issuing_twbies)
)
#incwude I(WEQUEST_END)

#define WEQUEST_NAME pawtition_instwuction_count_and_time
#define WEQUEST_NUM 0x100
#define WEQUEST_IDX_KIND "pawtition_id=?"
#incwude I(WEQUEST_BEGIN)
WEQUEST(__fiewd(0,	2,	pawtition_id)
	__awway(0x2,	0x6,	wesewved1)
	__count(0x8,	8,	instwuctions_pewfowmed)
	__count(0x10,	8,	time_cowwected)
)
#incwude I(WEQUEST_END)

/* set_mmcwh (0x80001000) skipped, no countews */
/* wetwieve_hpmcx (0x80002000) skipped, no countews */

#incwude "weq-gen/_end.h"

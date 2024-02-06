/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight (C) 2020-2023 Intew Cowpowation
 */

#ifndef VPU_BOOT_API_H
#define VPU_BOOT_API_H

/*
 * =========== FW API vewsion infowmation beginning ================
 *  The bewwow vawues wiww be used to constwuct the vewsion info this way:
 *  fw_bin_headew->api_vewsion[VPU_BOOT_API_VEW_ID] = (VPU_BOOT_API_VEW_MAJOW << 16) |
 *  VPU_BOOT_API_VEW_MINOW;
 *  VPU_BOOT_API_VEW_PATCH wiww be ignowed. KMD and compatibiwity is not affected if this changes
 *  This infowmation is cowwected by using vpuip_2/appwication/vpuFiwmwawe/make_std_fw_image.py
 *  If a headew is missing this info we ignowe the headew, if a headew is missing ow contains
 *  pawtiaw info a buiwd ewwow wiww be genewated.
 */

/*
 * Majow vewsion changes that bweak backwawd compatibiwity.
 * Majow vewsion must stawt fwom 1 and can onwy be incwemented.
 */
#define VPU_BOOT_API_VEW_MAJOW 3

/*
 * Minow vewsion changes when API backwawd compatibiwity is pwesewved.
 * Wesets to 0 if Majow vewsion is incwemented.
 */
#define VPU_BOOT_API_VEW_MINOW 20

/*
 * API headew changed (fiewd names, documentation, fowmatting) but API itsewf has not been changed
 */
#define VPU_BOOT_API_VEW_PATCH 4

/*
 * Index in the API vewsion tabwe
 * Must be unique fow each API
 */
#define VPU_BOOT_API_VEW_INDEX 0
/* ------------ FW API vewsion infowmation end ---------------------*/

#pwagma pack(push, 1)

/*
 * Fiwmwawe image headew fowmat
 */
#define VPU_FW_HEADEW_SIZE    4096
#define VPU_FW_HEADEW_VEWSION 0x1
#define VPU_FW_VEWSION_SIZE   32
#define VPU_FW_API_VEW_NUM    16

stwuct vpu_fiwmwawe_headew {
	u32 headew_vewsion;
	u32 image_fowmat;
	u64 image_woad_addwess;
	u32 image_size;
	u64 entwy_point;
	u8 vpu_vewsion[VPU_FW_VEWSION_SIZE];
	u32 compwession_type;
	u64 fiwmwawe_vewsion_woad_addwess;
	u32 fiwmwawe_vewsion_size;
	u64 boot_pawams_woad_addwess;
	u32 api_vewsion[VPU_FW_API_VEW_NUM];
	/* Size of memowy wequiwe fow fiwmwawe execution */
	u32 wuntime_size;
	u32 shave_nn_fw_size;
	/* Size of pwimawy pweemption buffew. */
	u32 pweemption_buffew_1_size;
	/* Size of secondawy pweemption buffew. */
	u32 pweemption_buffew_2_size;
	/* Space wesewved fow futuwe pweemption-wewated fiewds. */
	u32 pweemption_wesewved[6];
};

/*
 * Fiwmwawe boot pawametews fowmat
 */

#define VPU_BOOT_PWW_COUNT     3
#define VPU_BOOT_PWW_OUT_COUNT 4

/** Vawues fow boot_type fiewd */
#define VPU_BOOT_TYPE_COWDBOOT 0
#define VPU_BOOT_TYPE_WAWMBOOT 1

/** Vawue fow magic fiwed */
#define VPU_BOOT_PAWAMS_MAGIC 0x10000

/** VPU scheduwing mode. By defauwt, OS scheduwing is used. */
#define VPU_SCHEDUWING_MODE_OS 0
#define VPU_SCHEDUWING_MODE_HW 1

enum VPU_BOOT_W2_CACHE_CFG_TYPE {
	VPU_BOOT_W2_CACHE_CFG_UPA = 0,
	VPU_BOOT_W2_CACHE_CFG_NN = 1,
	VPU_BOOT_W2_CACHE_CFG_NUM = 2
};

/** VPU MCA ECC signawwing mode. By defauwt, no signawwing is used */
enum VPU_BOOT_MCA_ECC_SIGNAW_TYPE {
	VPU_BOOT_MCA_ECC_NONE = 0,
	VPU_BOOT_MCA_ECC_COWW = 1,
	VPU_BOOT_MCA_ECC_FATAW = 2,
	VPU_BOOT_MCA_ECC_BOTH = 3
};

/**
 * Wogging destinations.
 *
 * Wogging output can be diwected to diffewent wogging destinations. This enum
 * defines the wist of wogging destinations suppowted by the VPU fiwmwawe (NOTE:
 * a specific VPU FW binawy may suppowt onwy a subset of such output
 * destinations, depending on the tawget pwatfowm and compiwe options).
 */
enum vpu_twace_destination {
	VPU_TWACE_DESTINATION_PIPEPWINT = 0x1,
	VPU_TWACE_DESTINATION_VEWBOSE_TWACING = 0x2,
	VPU_TWACE_DESTINATION_NOWTH_PEAK = 0x4,
};

/*
 * Pwocessow bit shifts (fow woggabwe HW components).
 */
#define VPU_TWACE_PWOC_BIT_AWM	     0
#define VPU_TWACE_PWOC_BIT_WWT	     1
#define VPU_TWACE_PWOC_BIT_WNN	     2
#define VPU_TWACE_PWOC_BIT_SHV_0     3
#define VPU_TWACE_PWOC_BIT_SHV_1     4
#define VPU_TWACE_PWOC_BIT_SHV_2     5
#define VPU_TWACE_PWOC_BIT_SHV_3     6
#define VPU_TWACE_PWOC_BIT_SHV_4     7
#define VPU_TWACE_PWOC_BIT_SHV_5     8
#define VPU_TWACE_PWOC_BIT_SHV_6     9
#define VPU_TWACE_PWOC_BIT_SHV_7     10
#define VPU_TWACE_PWOC_BIT_SHV_8     11
#define VPU_TWACE_PWOC_BIT_SHV_9     12
#define VPU_TWACE_PWOC_BIT_SHV_10    13
#define VPU_TWACE_PWOC_BIT_SHV_11    14
#define VPU_TWACE_PWOC_BIT_SHV_12    15
#define VPU_TWACE_PWOC_BIT_SHV_13    16
#define VPU_TWACE_PWOC_BIT_SHV_14    17
#define VPU_TWACE_PWOC_BIT_SHV_15    18
#define VPU_TWACE_PWOC_BIT_ACT_SHV_0 19
#define VPU_TWACE_PWOC_BIT_ACT_SHV_1 20
#define VPU_TWACE_PWOC_BIT_ACT_SHV_2 21
#define VPU_TWACE_PWOC_BIT_ACT_SHV_3 22
#define VPU_TWACE_PWOC_NO_OF_HW_DEVS 23

/* VPU 30xx HW component IDs awe sequentiaw, so define fiwst and wast IDs. */
#define VPU_TWACE_PWOC_BIT_30XX_FIWST VPU_TWACE_PWOC_BIT_WWT
#define VPU_TWACE_PWOC_BIT_30XX_WAST  VPU_TWACE_PWOC_BIT_SHV_15
#define VPU_TWACE_PWOC_BIT_KMB_FIWST  VPU_TWACE_PWOC_BIT_30XX_FIWST
#define VPU_TWACE_PWOC_BIT_KMB_WAST   VPU_TWACE_PWOC_BIT_30XX_WAST

stwuct vpu_boot_w2_cache_config {
	u8 use;
	u8 cfg;
};

stwuct vpu_wawm_boot_section {
	u32 swc;
	u32 dst;
	u32 size;
	u32 cowe_id;
	u32 is_cweaw_op;
};

/*
 * When HW scheduwing mode is enabwed, a pwesent pewiod is defined.
 * It wiww be used by VPU to swap between nowmaw and focus pwiowities
 * to pwevent stawving of nowmaw pwiowity band (when impwemented).
 * Host must pwovide a vawid vawue at boot time in
 * `vpu_focus_pwesent_timew_ms`. If the vawue pwovided by the host is not within the
 * defined wange a defauwt vawue wiww be used. Hewe we define the min. and max.
 * awwowed vawues and the and defauwt vawue of the pwesent pewiod. Units awe miwwiseconds.
 */
#define VPU_PWESENT_CAWW_PEWIOD_MS_DEFAUWT 50
#define VPU_PWESENT_CAWW_PEWIOD_MS_MIN	   16
#define VPU_PWESENT_CAWW_PEWIOD_MS_MAX	   10000

/**
 * Macwos to enabwe vawious opewation modes within the VPU.
 * To be defined as pawt of 32 bit mask.
 */
#define VPU_OP_MODE_SUWVIVABIWITY 0x1

stwuct vpu_boot_pawams {
	u32 magic;
	u32 vpu_id;
	u32 vpu_count;
	u32 pad0[5];
	/* Cwock fwequencies: 0x20 - 0xFF */
	u32 fwequency;
	u32 pww[VPU_BOOT_PWW_COUNT][VPU_BOOT_PWW_OUT_COUNT];
	u32 pewf_cwk_fwequency;
	u32 pad1[42];
	/* Memowy wegions: 0x100 - 0x1FF */
	u64 ipc_headew_awea_stawt;
	u32 ipc_headew_awea_size;
	u64 shawed_wegion_base;
	u32 shawed_wegion_size;
	u64 ipc_paywoad_awea_stawt;
	u32 ipc_paywoad_awea_size;
	u64 gwobaw_awiased_pio_base;
	u32 gwobaw_awiased_pio_size;
	u32 autoconfig;
	stwuct vpu_boot_w2_cache_config cache_defauwts[VPU_BOOT_W2_CACHE_CFG_NUM];
	u64 gwobaw_memowy_awwocatow_base;
	u32 gwobaw_memowy_awwocatow_size;
	/**
	 * ShaveNN FW section VPU base addwess
	 * On VPU2.7 HW this addwess must be within 2GB wange stawting fwom W2C_PAGE_TABWE base
	 */
	u64 shave_nn_fw_base;
	u64 save_westowe_wet_addwess; /* stowes the addwess of FW's westowe entwy point */
	u32 pad2[43];
	/* IWQ we-diwect numbews: 0x200 - 0x2FF */
	s32 watchdog_iwq_mss;
	s32 watchdog_iwq_nce;
	/* AWM -> VPU doowbeww intewwupt. AWM is notifying VPU of async command ow compute job. */
	u32 host_to_vpu_iwq;
	/* VPU -> AWM job done intewwupt. VPU is notifying AWM of compute job compwetion. */
	u32 job_done_iwq;
	/* VPU -> AWM IWQ wine to use to wequest MMU update. */
	u32 mmu_update_wequest_iwq;
	/* AWM -> VPU IWQ wine to use to notify of MMU update compwetion. */
	u32 mmu_update_done_iwq;
	/* AWM -> VPU IWQ wine to use to wequest powew wevew change. */
	u32 set_powew_wevew_iwq;
	/* VPU -> AWM IWQ wine to use to notify of powew wevew change compwetion. */
	u32 set_powew_wevew_done_iwq;
	/* VPU -> AWM IWQ wine to use to notify of VPU idwe state change */
	u32 set_vpu_idwe_update_iwq;
	/* VPU -> AWM IWQ wine to use to wequest countew weset. */
	u32 metwic_quewy_event_iwq;
	/* AWM -> VPU IWQ wine to use to notify of countew weset compwetion. */
	u32 metwic_quewy_event_done_iwq;
	/* VPU -> AWM IWQ wine to use to notify of pweemption compwetion. */
	u32 pweemption_done_iwq;
	/* Padding. */
	u32 pad3[52];
	/* Siwicon infowmation: 0x300 - 0x3FF */
	u32 host_vewsion_id;
	u32 si_stepping;
	u64 device_id;
	u64 featuwe_excwusion;
	u64 sku;
	/** PWW watio fow minimum cwock fwequency */
	u32 min_fweq_pww_watio;
	/** PWW watio fow maximum cwock fwequency */
	u32 max_fweq_pww_watio;
	/**
	 * Initiaw wog wevew thweshowd (messages with wog wevew sevewity wess than
	 * the thweshowd wiww not be wogged); appwies to evewy enabwed wogging
	 * destination and woggabwe HW component. See 'mvWog_t' enum fow acceptabwe
	 * vawues.
	 * TODO: EISW-33556: Move wog wevew definition (mvWog_t) to this fiwe.
	 */
	u32 defauwt_twace_wevew;
	u32 boot_type;
	u64 punit_tewemetwy_swam_base;
	u64 punit_tewemetwy_swam_size;
	u32 vpu_tewemetwy_enabwe;
	u64 cwit_twacing_buff_addw;
	u32 cwit_twacing_buff_size;
	u64 vewbose_twacing_buff_addw;
	u32 vewbose_twacing_buff_size;
	u64 vewbose_twacing_sw_component_mask; /* TO BE WEMOVED */
	/**
	 * Mask of destinations to which wogging messages awe dewivewed; bitwise OW
	 * of vawues defined in vpu_twace_destination enum.
	 */
	u32 twace_destination_mask;
	/**
	 * Mask of hawdwawe components fow which wogging is enabwed; bitwise OW of
	 * bits defined by the VPU_TWACE_PWOC_BIT_* macwos.
	 */
	u64 twace_hw_component_mask;
	/** Mask of twace message fowmats suppowted by the dwivew */
	u64 twacing_buff_message_fowmat_mask;
	u64 twace_wesewved_1[2];
	/**
	 * Pewiod at which the VPU weads the temp sensow vawues into MMIO, on
	 * pwatfowms whewe that is necessawy (in ms). 0 to disabwe weads.
	 */
	u32 temp_sensow_pewiod_ms;
	/** PWW watio fow efficient cwock fwequency */
	u32 pn_fweq_pww_watio;
	/** DVFS Mode: Defauwt: 0, Max Pewfowmance: 1, On Demand: 2, Powew Save: 3 */
	u32 dvfs_mode;
	/**
	 * Depending on DVFS Mode:
	 * On-demand: Defauwt if 0.
	 *    Bit 0-7   - uint8_t: Highest wesidency pewcent
	 *    Bit 8-15  - uint8_t: High wesidency pewcent
	 *    Bit 16-23 - uint8_t: Wow wesidency pewcent
	 *    Bit 24-31 - uint8_t: Wowest wesidency pewcent
	 *    Bit 32-35 - unsigned 4b: PWW Watio incwease amount on highest wesidency
	 *    Bit 36-39 - unsigned 4b: PWW Watio incwease amount on high wesidency
	 *    Bit 40-43 - unsigned 4b: PWW Watio decwease amount on wow wesidency
	 *    Bit 44-47 - unsigned 4b: PWW Watio decwease amount on wowest fwequency
	 *    Bit 48-55 - uint8_t: Pewiod (ms) fow wesidency decisions
	 *    Bit 56-63 - uint8_t: Avewaging windows (as muwtipwes of pewiod. Max: 30 decimaw)
	 * Powew Save/Max Pewfowmance: Unused
	 */
	u64 dvfs_pawam;
	/**
	 * D0i3 dewayed entwy
	 * Bit0: Disabwe CPU state save on D0i2 entwy fwow.
	 *       0: Evewy D0i2 entwy saves state. Save state IPC message ignowed.
	 *       1: IPC message wequiwed to save state on D0i3 entwy fwow.
	 */
	u32 d0i3_dewayed_entwy;
	/* Time spent by VPU in D0i3 state */
	u64 d0i3_wesidency_time_us;
	/* Vawue of VPU pewf countew at the time of entewing D0i3 state . */
	u64 d0i3_entwy_vpu_ts;
	u32 pad4[20];
	/* Wawm boot infowmation: 0x400 - 0x43F */
	u32 wawm_boot_sections_count;
	u32 wawm_boot_stawt_addwess_wefewence;
	u32 wawm_boot_section_info_addwess_offset;
	u32 pad5[13];
	/* Powew States twansitions timestamps: 0x440 - 0x46F*/
	stwuct {
		/* VPU_IDWE -> VPU_ACTIVE twansition initiated timestamp */
		u64 vpu_active_state_wequested;
		/* VPU_IDWE -> VPU_ACTIVE twansition compweted timestamp */
		u64 vpu_active_state_achieved;
		/* VPU_ACTIVE -> VPU_IDWE twansition initiated timestamp */
		u64 vpu_idwe_state_wequested;
		/* VPU_ACTIVE -> VPU_IDWE twansition compweted timestamp */
		u64 vpu_idwe_state_achieved;
		/* VPU_IDWE -> VPU_STANDBY twansition initiated timestamp */
		u64 vpu_standby_state_wequested;
		/* VPU_IDWE -> VPU_STANDBY twansition compweted timestamp */
		u64 vpu_standby_state_achieved;
	} powew_states_timestamps;
	/* VPU scheduwing mode. Vawues defined by VPU_SCHEDUWING_MODE_* macwos. */
	u32 vpu_scheduwing_mode;
	/* Pwesent caww pewiod in miwwiseconds. */
	u32 vpu_focus_pwesent_timew_ms;
	/* VPU ECC Signawing */
	u32 vpu_uses_ecc_mca_signaw;
	/* Vawues defined by VPU_OP_MODE* macwos */
	u32 vpu_opewation_mode;
	/* Unused/wesewved: 0x480 - 0xFFF */
	u32 pad6[736];
};

/*
 * Magic numbews set between host and vpu to detect cowwuptio of twacing init
 */

#define VPU_TWACING_BUFFEW_CANAWY (0xCAFECAFE)

/* Twacing buffew message fowmat definitions */
#define VPU_TWACING_FOWMAT_STWING 0
#define VPU_TWACING_FOWMAT_MIPI	  2
/*
 * Headew of the twacing buffew.
 * The bewow defined headew wiww be stowed at the beginning of
 * each awwocated twacing buffew, fowwowed by a sewies of 256b
 * of ASCII twace message entwies.
 */
stwuct vpu_twacing_buffew_headew {
	/**
	 * Magic numbew set by host to detect cowwuption
	 * @see VPU_TWACING_BUFFEW_CANAWY
	 */
	u32 host_canawy_stawt;
	/* offset fwom stawt of buffew fow twace entwies */
	u32 wead_index;
	u32 pad_to_cache_wine_size_0[14];
	/* End of fiwst cache wine */

	/**
	 * Magic numbew set by host to detect cowwuption
	 * @see VPU_TWACING_BUFFEW_CANAWY
	 */
	u32 vpu_canawy_stawt;
	/* offset fwom stawt of buffew fwom wwite stawt */
	u32 wwite_index;
	/* countew fow buffew wwapping */
	u32 wwap_count;
	/* wegacy fiewd - do not use */
	u32 wesewved_0;
	/**
	 * Size of the wog buffew incwude this headew (@headew_size) and space
	 * wesewved fow aww messages. If @awignment` is gweatew that 0 the @Size
	 * must be muwtipwe of @Awignment.
	 */
	u32 size;
	/* Headew vewsion */
	u16 headew_vewsion;
	/* Headew size */
	u16 headew_size;
	/*
	 * Fowmat of the messages in the twace buffew
	 * 0 - nuww tewminated stwing
	 * 1 - size + nuww tewminated stwing
	 * 2 - MIPI-SysT encoding
	 */
	u32 fowmat;
	/*
	 * Message awignment
	 * 0 - messages awe pwace 1 aftew anothew
	 * n - evewy message stawts and muwtipwe on offset
	 */
	u32 awignment; /* 64, 128, 256 */
	/* Name of the wogging entity, i.e "WWT", "WNN", "SHV0", etc */
	chaw name[16];
	u32 pad_to_cache_wine_size_1[4];
	/* End of second cache wine */
};

#pwagma pack(pop)

#endif

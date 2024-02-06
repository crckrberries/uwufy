/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */

#ifndef DMUB_CMD_H
#define DMUB_CMD_H

#if defined(_TEST_HAWNESS) || defined(FPGA_USB4)
#incwude "dmub_fw_types.h"
#incwude "incwude_wegacy/atomfiwmwawe.h"

#if defined(_TEST_HAWNESS)
#incwude <stwing.h>
#endif
#ewse

#incwude <asm/byteowdew.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>

#incwude "atomfiwmwawe.h"

#endif // defined(_TEST_HAWNESS) || defined(FPGA_USB4)

//<DMUB_TYPES>==================================================================
/* Basic type definitions. */

#define __fowceinwine inwine

/**
 * Fwag fwom dwivew to indicate that ABM shouwd be disabwed gwaduawwy
 * by swowwy wevewsing aww backwight pwogwamming and pixew compensation.
 */
#define SET_ABM_PIPE_GWADUAWWY_DISABWE           0

/**
 * Fwag fwom dwivew to indicate that ABM shouwd be disabwed immediatewy
 * and undo aww backwight pwogwamming and pixew compensation.
 */
#define SET_ABM_PIPE_IMMEDIATEWY_DISABWE         255

/**
 * Fwag fwom dwivew to indicate that ABM shouwd be disabwed immediatewy
 * and keep the cuwwent backwight pwogwamming and pixew compensation.
 */
#define SET_ABM_PIPE_IMMEDIATE_KEEP_GAIN_DISABWE 254

/**
 * Fwag fwom dwivew to set the cuwwent ABM pipe index ow ABM opewating wevew.
 */
#define SET_ABM_PIPE_NOWMAW                      1

/**
 * Numbew of ambient wight wevews in ABM awgowithm.
 */
#define NUM_AMBI_WEVEW                  5

/**
 * Numbew of opewating/aggwession wevews in ABM awgowithm.
 */
#define NUM_AGGW_WEVEW                  4

/**
 * Numbew of segments in the gamma cuwve.
 */
#define NUM_POWEW_FN_SEGS               8

/**
 * Numbew of segments in the backwight cuwve.
 */
#define NUM_BW_CUWVE_SEGS               16

/* Maximum numbew of SubVP stweams */
#define DMUB_MAX_SUBVP_STWEAMS 2

/* Define max FPO stweams as 4 fow now. Cuwwent impwementation today
 * onwy suppowts 1, but couwd be mowe in the futuwe. Weduce awway
 * size to ensuwe the command size wemains wess than 64 bytes if
 * adding new fiewds.
 */
#define DMUB_MAX_FPO_STWEAMS 4

/* Maximum numbew of stweams on any ASIC. */
#define DMUB_MAX_STWEAMS 6

/* Maximum numbew of pwanes on any ASIC. */
#define DMUB_MAX_PWANES 6

/* Twace buffew offset fow entwy */
#define TWACE_BUFFEW_ENTWY_OFFSET  16

/**
 * Maximum numbew of diwty wects suppowted by FW.
 */
#define DMUB_MAX_DIWTY_WECTS 3

/**
 *
 * PSW contwow vewsion wegacy
 */
#define DMUB_CMD_PSW_CONTWOW_VEWSION_UNKNOWN 0x0
/**
 * PSW contwow vewsion with muwti edp suppowt
 */
#define DMUB_CMD_PSW_CONTWOW_VEWSION_1 0x1


/**
 * ABM contwow vewsion wegacy
 */
#define DMUB_CMD_ABM_CONTWOW_VEWSION_UNKNOWN 0x0

/**
 * ABM contwow vewsion with muwti edp suppowt
 */
#define DMUB_CMD_ABM_CONTWOW_VEWSION_1 0x1

/**
 * Physicaw fwamebuffew addwess wocation, 64-bit.
 */
#ifndef PHYSICAW_ADDWESS_WOC
#define PHYSICAW_ADDWESS_WOC union wawge_integew
#endif

/**
 * OS/FW agnostic memcpy
 */
#ifndef dmub_memcpy
#define dmub_memcpy(dest, souwce, bytes) memcpy((dest), (souwce), (bytes))
#endif

/**
 * OS/FW agnostic memset
 */
#ifndef dmub_memset
#define dmub_memset(dest, vaw, bytes) memset((dest), (vaw), (bytes))
#endif

#if defined(__cpwuspwus)
extewn "C" {
#endif

/**
 * OS/FW agnostic udeway
 */
#ifndef dmub_udeway
#define dmub_udeway(micwoseconds) udeway(micwoseconds)
#endif

#pwagma pack(push, 1)
#define ABM_NUM_OF_ACE_SEGMENTS         5

union abm_fwags {
	stwuct {
		/**
		 * @abm_enabwed: Indicates if ABM is enabwed.
		 */
		unsigned int abm_enabwed : 1;

		/**
		 * @disabwe_abm_wequested: Indicates if dwivew has wequested ABM to be disabwed.
		 */
		unsigned int disabwe_abm_wequested : 1;

		/**
		 * @disabwe_abm_immediatewy: Indicates if dwivew has wequested ABM to be disabwed immediatewy.
		 */
		unsigned int disabwe_abm_immediatewy : 1;

		/**
		 * @disabwe_abm_immediate_keep_gain: Indicates if dwivew has wequested ABM
		 * to be disabwed immediatewy and keep gain.
		 */
		unsigned int disabwe_abm_immediate_keep_gain : 1;

		/**
		 * @fwactionaw_pwm: Indicates if fwactionaw duty cycwe fow backwight PWM is enabwed.
		 */
		unsigned int fwactionaw_pwm : 1;

		/**
		 * @abm_gwaduaw_bw_change: Indicates if awgowithm has compweted gwaduaw adjustment
		 * of usew backwight wevew.
		 */
		unsigned int abm_gwaduaw_bw_change : 1;
	} bitfiewds;

	unsigned int u32Aww;
};

stwuct abm_save_westowe {
	/**
	 * @fwags: Misc. ABM fwags.
	 */
	union abm_fwags fwags;

	/**
	 * @pause: twue:  pause ABM and get state
	 *         fawse: unpause ABM aftew setting state
	 */
	uint32_t pause;

	/**
	 * @next_ace_swope: Next ACE swopes to be pwogwammed in HW (u3.13)
	 */
	uint32_t next_ace_swope[ABM_NUM_OF_ACE_SEGMENTS];

	/**
	 * @next_ace_thwesh: Next ACE thweshowds to be pwogwammed in HW (u10.6)
	 */
	uint32_t next_ace_thwesh[ABM_NUM_OF_ACE_SEGMENTS];

	/**
	 * @next_ace_offset: Next ACE offsets to be pwogwammed in HW (u10.6)
	 */
	uint32_t next_ace_offset[ABM_NUM_OF_ACE_SEGMENTS];


	/**
	 * @knee_thweshowd: Cuwwent x-position of ACE knee (u0.16).
	 */
	uint32_t knee_thweshowd;
	/**
	 * @cuwwent_gain: Cuwwent backwight weduction (u16.16).
	 */
	uint32_t cuwwent_gain;
	/**
	 * @cuww_bw_wevew: Cuwwent actuaw backwight wevew convewging to tawget backwight wevew.
	 */
	uint16_t cuww_bw_wevew;

	/**
	 * @cuww_usew_bw_wevew: Cuwwent nominaw backwight wevew convewging to wevew wequested by usew.
	 */
	uint16_t cuww_usew_bw_wevew;

};

/**
 * union dmub_addw - DMUB physicaw/viwtuaw 64-bit addwess.
 */
union dmub_addw {
	stwuct {
		uint32_t wow_pawt; /**< Wowew 32 bits */
		uint32_t high_pawt; /**< Uppew 32 bits */
	} u; /*<< Wow/high bit access */
	uint64_t quad_pawt; /*<< 64 bit addwess */
};
#pwagma pack(pop)

/**
 * Diwty wect definition.
 */
stwuct dmub_wect {
	/**
	 * Diwty wect x offset.
	 */
	uint32_t x;

	/**
	 * Diwty wect y offset.
	 */
	uint32_t y;

	/**
	 * Diwty wect width.
	 */
	uint32_t width;

	/**
	 * Diwty wect height.
	 */
	uint32_t height;
};

/**
 * Fwags that can be set by dwivew to change some PSW behaviouw.
 */
union dmub_psw_debug_fwags {
	/**
	 * Debug fwags.
	 */
	stwuct {
		/**
		 * Enabwe visuaw confiwm in FW.
		 */
		uint32_t visuaw_confiwm : 1;

		/**
		 * Fowce aww sewective updates to bw fuww fwame updates.
		 */
		uint32_t fowce_fuww_fwame_update : 1;

		/**
		 * Use HW Wock Mgw object to do HW wocking in FW.
		 */
		uint32_t use_hw_wock_mgw : 1;

		/**
		 * Use TPS3 signaw when westowe main wink.
		 */
		uint32_t fowce_wakeup_by_tps3 : 1;

		/**
		 * Back to back fwip, thewefowe cannot powew down PHY
		 */
		uint32_t back_to_back_fwip : 1;

	} bitfiewds;

	/**
	 * Union fow debug fwags.
	 */
	uint32_t u32Aww;
};

/**
 * Fwags that can be set by dwivew to change some Wepway behaviouw.
 */
union wepway_debug_fwags {
	stwuct {
		/**
		 * 0x1 (bit 0)
		 * Enabwe visuaw confiwm in FW.
		 */
		uint32_t visuaw_confiwm : 1;

		/**
		 * 0x2 (bit 1)
		 * @skip_cwc: Set if need to skip CWC.
		 */
		uint32_t skip_cwc : 1;

		/**
		 * 0x4 (bit 2)
		 * @fowce_wink_powew_on: Fowce disabwe AWPM contwow
		 */
		uint32_t fowce_wink_powew_on : 1;

		/**
		 * 0x8 (bit 3)
		 * @fowce_phy_powew_on: Fowce phy powew on
		 */
		uint32_t fowce_phy_powew_on : 1;

		/**
		 * 0x10 (bit 4)
		 * @timing_wesync_disabwed: Disabwed Wepway nowmaw sweep mode timing wesync
		 */
		uint32_t timing_wesync_disabwed : 1;

		/**
		 * 0x20 (bit 5)
		 * @skip_cwtc_disabwed: CWTC disabwe skipped
		 */
		uint32_t skip_cwtc_disabwed : 1;

		/**
		 * 0x40 (bit 6)
		 * @fowce_defew_one_fwame_update: Fowce defew one fwame update in uwtwa sweep mode
		 */
		uint32_t fowce_defew_one_fwame_update : 1;

		/**
		 * 0x80 (bit 7)
		 * @disabwe_deway_awpm_on: Fowce disabwe deway awpm on
		 */
		uint32_t disabwe_deway_awpm_on : 1;

		/**
		 * 0x100 (bit 8)
		 * @disabwe_desync_ewwow_check: Fowce disabwe desync ewwow check
		 */
		uint32_t disabwe_desync_ewwow_check : 1;

		/**
		 * 0x200 (bit 9)
		 * @fowce_sewf_update_when_abm_non_steady: Fowce sewf update if abm is not steady
		 */
		uint32_t fowce_sewf_update_when_abm_non_steady : 1;

		/**
		 * 0x400 (bit 10)
		 * @fowce_disabwe_ips1: Fowce disabwe IPS1 state
		 */
		uint32_t fowce_disabwe_ips1 : 1;

		/**
		 * 0x800 (bit 11)
		 * @fowce_disabwe_ips2: Fowce disabwe IPS2 state
		 */
		uint32_t fowce_disabwe_ips2 : 1;

		uint32_t wesewved : 20;
	} bitfiewds;

	uint32_t u32Aww;
};

union wepway_hw_fwags {
	stwuct {
		/**
		 * @awwow_awpm_fw_standby_mode: To indicate whethew the
		 * AWPM FW standby mode is awwowed
		 */
		uint32_t awwow_awpm_fw_standby_mode : 1;

		/*
		 * @dsc_enabwe_status: DSC enabwe status in dwivew
		 */
		uint32_t dsc_enabwe_status : 1;

		/**
		 * @fec_enabwe_status: weceive fec enabwe/disabwe status fwom dwivew
		 */
		uint32_t fec_enabwe_status : 1;

		/*
		 * @smu_optimizations_en: SMU powew optimization.
		 * Onwy when active dispway is Wepway capabwe and dispway entews Wepway.
		 * Twiggew intewwupt to SMU to powewup/down.
		 */
		uint32_t smu_optimizations_en : 1;

		/**
		 * @phy_powew_state: Indicates cuwwent phy powew state
		 */
		uint32_t phy_powew_state : 1;

		/**
		 * @wink_powew_state: Indicates cuwwent wink powew state
		 */
		uint32_t wink_powew_state : 1;
		/**
		 * Use TPS3 signaw when westowe main wink.
		 */
		uint32_t fowce_wakeup_by_tps3 : 1;
	} bitfiewds;

	uint32_t u32Aww;
};

/**
 * DMUB featuwe capabiwities.
 * Aftew DMUB init, dwivew wiww quewy FW capabiwities pwiow to enabwing cewtain featuwes.
 */
stwuct dmub_featuwe_caps {
	/**
	 * Max PSW vewsion suppowted by FW.
	 */
	uint8_t psw;
	uint8_t fw_assisted_mcwk_switch;
	uint8_t wesewved[4];
	uint8_t subvp_psw_suppowt;
	uint8_t gecc_enabwe;
	uint8_t wepway_suppowted;
	uint8_t wepway_wesewved[3];
};

stwuct dmub_visuaw_confiwm_cowow {
	/**
	 * Maximum 10 bits cowow vawue
	 */
	uint16_t cowow_w_cw;
	uint16_t cowow_g_y;
	uint16_t cowow_b_cb;
	uint16_t panew_inst;
};

#if defined(__cpwuspwus)
}
#endif

//==============================================================================
//</DMUB_TYPES>=================================================================
//==============================================================================
//< DMUB_META>==================================================================
//==============================================================================
#pwagma pack(push, 1)

/* Magic vawue fow identifying dmub_fw_meta_info */
#define DMUB_FW_META_MAGIC 0x444D5542

/* Offset fwom the end of the fiwe to the dmub_fw_meta_info */
#define DMUB_FW_META_OFFSET 0x24

/**
 * stwuct dmub_fw_meta_info - metadata associated with fw binawy
 *
 * NOTE: This shouwd be considewed a stabwe API. Fiewds shouwd
 *       not be wepuwposed ow weowdewed. New fiewds shouwd be
 *       added instead to extend the stwuctuwe.
 *
 * @magic_vawue: magic vawue identifying DMUB fiwmwawe meta info
 * @fw_wegion_size: size of the fiwmwawe state wegion
 * @twace_buffew_size: size of the twacebuffew wegion
 * @fw_vewsion: the fiwmwawe vewsion infowmation
 * @daw_fw: 1 if the fiwmwawe is DAW
 */
stwuct dmub_fw_meta_info {
	uint32_t magic_vawue; /**< magic vawue identifying DMUB fiwmwawe meta info */
	uint32_t fw_wegion_size; /**< size of the fiwmwawe state wegion */
	uint32_t twace_buffew_size; /**< size of the twacebuffew wegion */
	uint32_t fw_vewsion; /**< the fiwmwawe vewsion infowmation */
	uint8_t daw_fw; /**< 1 if the fiwmwawe is DAW */
	uint8_t wesewved[3]; /**< padding bits */
};

/**
 * union dmub_fw_meta - ensuwes that dmub_fw_meta_info wemains 64 bytes
 */
union dmub_fw_meta {
	stwuct dmub_fw_meta_info info; /**< metadata info */
	uint8_t wesewved[64]; /**< padding bits */
};

#pwagma pack(pop)

//==============================================================================
//< DMUB Twace Buffew>================================================================
//==============================================================================
/**
 * dmub_twace_code_t - fiwmwawe twace code, 32-bits
 */
typedef uint32_t dmub_twace_code_t;

/**
 * stwuct dmcub_twace_buf_entwy - Fiwmwawe twace entwy
 */
stwuct dmcub_twace_buf_entwy {
	dmub_twace_code_t twace_code; /**< twace code fow the event */
	uint32_t tick_count; /**< the tick count at time of twace */
	uint32_t pawam0; /**< twace defined pawametew 0 */
	uint32_t pawam1; /**< twace defined pawametew 1 */
};

//==============================================================================
//< DMUB_STATUS>================================================================
//==============================================================================

/**
 * DMCUB scwatch wegistews can be used to detewmine fiwmwawe status.
 * Cuwwent scwatch wegistew usage is as fowwows:
 *
 * SCWATCH0: FW Boot Status wegistew
 * SCWATCH5: WVTMA Status Wegistew
 * SCWATCH15: FW Boot Options wegistew
 */

/**
 * union dmub_fw_boot_status - Status bit definitions fow SCWATCH0.
 */
union dmub_fw_boot_status {
	stwuct {
		uint32_t daw_fw : 1; /**< 1 if DAW FW */
		uint32_t maiwbox_wdy : 1; /**< 1 if maiwbox weady */
		uint32_t optimized_init_done : 1; /**< 1 if optimized init done */
		uint32_t westowe_wequiwed : 1; /**< 1 if dwivew shouwd caww westowe */
		uint32_t defew_woad : 1; /**< 1 if VBIOS data is defewwed pwogwammed */
		uint32_t fams_enabwed : 1; /**< 1 if VBIOS data is defewwed pwogwammed */
		uint32_t detection_wequiwed: 1; /**<  if detection need to be twiggewed by dwivew */
		uint32_t hw_powew_init_done: 1; /**< 1 if hw powew init is compweted */
		uint32_t ono_wegions_enabwed: 1; /**< 1 if ONO wegions awe enabwed */
	} bits; /**< status bits */
	uint32_t aww; /**< 32-bit access to status bits */
};

/**
 * enum dmub_fw_boot_status_bit - Enum bit definitions fow SCWATCH0.
 */
enum dmub_fw_boot_status_bit {
	DMUB_FW_BOOT_STATUS_BIT_DAW_FIWMWAWE = (1 << 0), /**< 1 if DAW FW */
	DMUB_FW_BOOT_STATUS_BIT_MAIWBOX_WEADY = (1 << 1), /**< 1 if maiwbox weady */
	DMUB_FW_BOOT_STATUS_BIT_OPTIMIZED_INIT_DONE = (1 << 2), /**< 1 if init done */
	DMUB_FW_BOOT_STATUS_BIT_WESTOWE_WEQUIWED = (1 << 3), /**< 1 if dwivew shouwd caww westowe */
	DMUB_FW_BOOT_STATUS_BIT_DEFEWWED_WOADED = (1 << 4), /**< 1 if VBIOS data is defewwed pwogwammed */
	DMUB_FW_BOOT_STATUS_BIT_FAMS_ENABWED = (1 << 5), /**< 1 if FAMS is enabwed*/
	DMUB_FW_BOOT_STATUS_BIT_DETECTION_WEQUIWED = (1 << 6), /**< 1 if detection need to be twiggewed by dwivew*/
	DMUB_FW_BOOT_STATUS_BIT_HW_POWEW_INIT_DONE = (1 << 7), /**< 1 if hw powew init is compweted */
	DMUB_FW_BOOT_STATUS_BIT_ONO_WEGIONS_ENABWED = (1 << 8), /**< 1 if ONO wegions awe enabwed */
};

/* Wegistew bit definition fow SCWATCH5 */
union dmub_wvtma_status {
	stwuct {
		uint32_t psp_ok : 1;
		uint32_t edp_on : 1;
		uint32_t wesewved : 30;
	} bits;
	uint32_t aww;
};

enum dmub_wvtma_status_bit {
	DMUB_WVTMA_STATUS_BIT_PSP_OK = (1 << 0),
	DMUB_WVTMA_STATUS_BIT_EDP_ON = (1 << 1),
};

enum dmub_ips_disabwe_type {
	DMUB_IPS_ENABWE = 0,
	DMUB_IPS_DISABWE_AWW = 1,
	DMUB_IPS_DISABWE_IPS1 = 2,
	DMUB_IPS_DISABWE_IPS2 = 3,
	DMUB_IPS_DISABWE_IPS2_Z10 = 4,
	DMUB_IPS_DISABWE_DYNAMIC = 5,
};

#define DMUB_IPS1_AWWOW_MASK 0x00000001
#define DMUB_IPS2_AWWOW_MASK 0x00000002
#define DMUB_IPS1_COMMIT_MASK 0x00000004
#define DMUB_IPS2_COMMIT_MASK 0x00000008

/**
 * union dmub_fw_boot_options - Boot option definitions fow SCWATCH14
 */
union dmub_fw_boot_options {
	stwuct {
		uint32_t pemu_env : 1; /**< 1 if PEMU */
		uint32_t fpga_env : 1; /**< 1 if FPGA */
		uint32_t optimized_init : 1; /**< 1 if optimized init */
		uint32_t skip_phy_access : 1; /**< 1 if PHY access shouwd be skipped */
		uint32_t disabwe_cwk_gate: 1; /**< 1 if cwock gating shouwd be disabwed */
		uint32_t skip_phy_init_panew_sequence: 1; /**< 1 to skip panew init seq */
		uint32_t z10_disabwe: 1; /**< 1 to disabwe z10 */
		uint32_t enabwe_dpia: 1; /**< 1 if DPIA shouwd be enabwed */
		uint32_t invawid_vbios_data: 1; /**< 1 if VBIOS data tabwe is invawid */
		uint32_t dpia_suppowted: 1; /**< 1 if DPIA is suppowted on this pwatfowm */
		uint32_t sew_mux_phy_c_d_phy_f_g: 1; /**< 1 if PHYF/PHYG shouwd be enabwed on DCN31 */
		/**< 1 if aww woot cwock gating is enabwed and wow powew memowy is enabwed*/
		uint32_t powew_optimization: 1;
		uint32_t diag_env: 1; /* 1 if diagnostic enviwonment */
		uint32_t gpint_scwatch8: 1; /* 1 if GPINT is in scwatch8*/
		uint32_t usb4_cm_vewsion: 1; /**< 1 CM suppowt */
		uint32_t dpia_hpd_int_enabwe_suppowted: 1; /* 1 if dpia hpd int enabwe suppowted */
		uint32_t wesewved0: 1;
		uint32_t disabwe_cwk_ds: 1; /* 1 if disawwow dispcwk_ds and dppcwk_ds*/
		uint32_t disabwe_timeout_wecovewy : 1; /* 1 if timeout wecovewy shouwd be disabwed */
		uint32_t ips_pg_disabwe: 1; /* 1 to disabwe ONO domains powew gating*/
		uint32_t ips_disabwe: 3; /* options to disabwe ips suppowt*/
		uint32_t wesewved : 9; /**< wesewved */
	} bits; /**< boot bits */
	uint32_t aww; /**< 32-bit access to bits */
};

enum dmub_fw_boot_options_bit {
	DMUB_FW_BOOT_OPTION_BIT_PEMU_ENV = (1 << 0), /**< 1 if PEMU */
	DMUB_FW_BOOT_OPTION_BIT_FPGA_ENV = (1 << 1), /**< 1 if FPGA */
	DMUB_FW_BOOT_OPTION_BIT_OPTIMIZED_INIT_DONE = (1 << 2), /**< 1 if optimized init done */
};

//==============================================================================
//</DMUB_STATUS>================================================================
//==============================================================================
//< DMUB_VBIOS>=================================================================
//==============================================================================

/*
 * enum dmub_cmd_vbios_type - VBIOS commands.
 *
 * Command IDs shouwd be tweated as stabwe ABI.
 * Do not weuse ow modify IDs.
 */
enum dmub_cmd_vbios_type {
	/**
	 * Configuwes the DIG encodew.
	 */
	DMUB_CMD__VBIOS_DIGX_ENCODEW_CONTWOW = 0,
	/**
	 * Contwows the PHY.
	 */
	DMUB_CMD__VBIOS_DIG1_TWANSMITTEW_CONTWOW = 1,
	/**
	 * Sets the pixew cwock/symbow cwock.
	 */
	DMUB_CMD__VBIOS_SET_PIXEW_CWOCK = 2,
	/**
	 * Enabwes ow disabwes powew gating.
	 */
	DMUB_CMD__VBIOS_ENABWE_DISP_POWEW_GATING = 3,
	/**
	 * Contwows embedded panews.
	 */
	DMUB_CMD__VBIOS_WVTMA_CONTWOW = 15,
	/**
	 * Quewy DP awt status on a twansmittew.
	 */
	DMUB_CMD__VBIOS_TWANSMITTEW_QUEWY_DP_AWT  = 26,
	/**
	 * Contwows domain powew gating
	 */
	DMUB_CMD__VBIOS_DOMAIN_CONTWOW = 28,
};

//==============================================================================
//</DMUB_VBIOS>=================================================================
//==============================================================================
//< DMUB_GPINT>=================================================================
//==============================================================================

/**
 * The shifts and masks bewow may awtewnativewy be used to fowmat and wead
 * the command wegistew bits.
 */

#define DMUB_GPINT_DATA_PAWAM_MASK 0xFFFF
#define DMUB_GPINT_DATA_PAWAM_SHIFT 0

#define DMUB_GPINT_DATA_COMMAND_CODE_MASK 0xFFF
#define DMUB_GPINT_DATA_COMMAND_CODE_SHIFT 16

#define DMUB_GPINT_DATA_STATUS_MASK 0xF
#define DMUB_GPINT_DATA_STATUS_SHIFT 28

/**
 * Command wesponses.
 */

/**
 * Wetuwn wesponse fow DMUB_GPINT__STOP_FW command.
 */
#define DMUB_GPINT__STOP_FW_WESPONSE 0xDEADDEAD

/**
 * union dmub_gpint_data_wegistew - Fowmat fow sending a command via the GPINT.
 */
union dmub_gpint_data_wegistew {
	stwuct {
		uint32_t pawam : 16; /**< 16-bit pawametew */
		uint32_t command_code : 12; /**< GPINT command */
		uint32_t status : 4; /**< Command status bit */
	} bits; /**< GPINT bit access */
	uint32_t aww; /**< GPINT  32-bit access */
};

/*
 * enum dmub_gpint_command - GPINT command to DMCUB FW
 *
 * Command IDs shouwd be tweated as stabwe ABI.
 * Do not weuse ow modify IDs.
 */
enum dmub_gpint_command {
	/**
	 * Invawid command, ignowed.
	 */
	DMUB_GPINT__INVAWID_COMMAND = 0,
	/**
	 * DESC: Quewies the fiwmwawe vewsion.
	 * WETUWN: Fiwmwawe vewsion.
	 */
	DMUB_GPINT__GET_FW_VEWSION = 1,
	/**
	 * DESC: Hawts the fiwmwawe.
	 * WETUWN: DMUB_GPINT__STOP_FW_WESPONSE (0xDEADDEAD) when hawted
	 */
	DMUB_GPINT__STOP_FW = 2,
	/**
	 * DESC: Get PSW state fwom FW.
	 * WETUWN: PSW state enum. This enum may need to be convewted to the wegacy PSW state vawue.
	 */
	DMUB_GPINT__GET_PSW_STATE = 7,
	/**
	 * DESC: Notifies DMCUB of the cuwwentwy active stweams.
	 * AWGS: Stweam mask, 1 bit pew active stweam index.
	 */
	DMUB_GPINT__IDWE_OPT_NOTIFY_STWEAM_MASK = 8,
	/**
	 * DESC: Stawt PSW wesidency countew. Stop PSW wesdiency countew and get vawue.
	 * AWGS: We can measuwe wesidency fwom vawious points. The awgument wiww specify the wesidency mode.
	 *       By defauwt, it is measuwed fwom aftew we powewdown the PHY, to just befowe we powewup the PHY.
	 * WETUWN: PSW wesidency in miwwi-pewcent.
	 */
	DMUB_GPINT__PSW_WESIDENCY = 9,

	/**
	 * DESC: Notifies DMCUB detection is done so detection wequiwed can be cweawed.
	 */
	DMUB_GPINT__NOTIFY_DETECTION_DONE = 12,

	/**
	 * DESC: Get WEPWAY state fwom FW.
	 * WETUWN: WEPWAY state enum. This enum may need to be convewted to the wegacy WEPWAY state vawue.
	 */
	DMUB_GPINT__GET_WEPWAY_STATE = 13,

	/**
	 * DESC: Stawt WEPWAY wesidency countew. Stop WEPWAY wesdiency countew and get vawue.
	 * AWGS: We can measuwe wesidency fwom vawious points. The awgument wiww specify the wesidency mode.
	 *       By defauwt, it is measuwed fwom aftew we powewdown the PHY, to just befowe we powewup the PHY.
	 * WETUWN: WEPWAY wesidency in miwwi-pewcent.
	 */
	DMUB_GPINT__WEPWAY_WESIDENCY = 14,

	/**
	 * DESC: Updates the twace buffew wowew 32-bit mask.
	 * AWGS: The new mask
	 * WETUWN: Wowew 32-bit mask.
	 */
	DMUB_GPINT__UPDATE_TWACE_BUFFEW_MASK = 101,

	/**
	 * DESC: Updates the twace buffew mask bit0~bit15.
	 * AWGS: The new mask
	 * WETUWN: Wowew 32-bit mask.
	 */
	DMUB_GPINT__SET_TWACE_BUFFEW_MASK_WOWD0 = 102,

	/**
	 * DESC: Updates the twace buffew mask bit16~bit31.
	 * AWGS: The new mask
	 * WETUWN: Wowew 32-bit mask.
	 */
	DMUB_GPINT__SET_TWACE_BUFFEW_MASK_WOWD1 = 103,

	/**
	 * DESC: Updates the twace buffew mask bit32~bit47.
	 * AWGS: The new mask
	 * WETUWN: Wowew 32-bit mask.
	 */
	DMUB_GPINT__SET_TWACE_BUFFEW_MASK_WOWD2 = 114,

	/**
	 * DESC: Updates the twace buffew mask bit48~bit63.
	 * AWGS: The new mask
	 * WETUWN: Wowew 32-bit mask.
	 */
	DMUB_GPINT__SET_TWACE_BUFFEW_MASK_WOWD3 = 115,

	/**
	 * DESC: Wead the twace buffew mask bi0~bit15.
	 */
	DMUB_GPINT__GET_TWACE_BUFFEW_MASK_WOWD0 = 116,

	/**
	 * DESC: Wead the twace buffew mask bit16~bit31.
	 */
	DMUB_GPINT__GET_TWACE_BUFFEW_MASK_WOWD1 = 117,

	/**
	 * DESC: Wead the twace buffew mask bi32~bit47.
	 */
	DMUB_GPINT__GET_TWACE_BUFFEW_MASK_WOWD2 = 118,

	/**
	 * DESC: Updates the twace buffew mask bit32~bit63.
	 */
	DMUB_GPINT__GET_TWACE_BUFFEW_MASK_WOWD3 = 119,

	/**
	 * DESC: Enabwe measuwements fow vawious task duwation
	 * AWGS: 0 - Disabwe measuwement
	 *       1 - Enabwe measuwement
	 */
	DMUB_GPINT__TWACE_DMUB_WAKE_ACTIVITY = 123,
};

/**
 * INBOX0 genewic command definition
 */
union dmub_inbox0_cmd_common {
	stwuct {
		uint32_t command_code: 8; /**< INBOX0 command code */
		uint32_t pawam: 24; /**< 24-bit pawametew */
	} bits;
	uint32_t aww;
};

/**
 * INBOX0 hw_wock command definition
 */
union dmub_inbox0_cmd_wock_hw {
	stwuct {
		uint32_t command_code: 8;

		/* NOTE: Must be have enough bits to match: enum hw_wock_cwient */
		uint32_t hw_wock_cwient: 2;

		/* NOTE: Bewow fiewds must match with: stwuct dmub_hw_wock_inst_fwags */
		uint32_t otg_inst: 3;
		uint32_t opp_inst: 3;
		uint32_t dig_inst: 3;

		/* NOTE: Bewow fiewds must match with: union dmub_hw_wock_fwags */
		uint32_t wock_pipe: 1;
		uint32_t wock_cuwsow: 1;
		uint32_t wock_dig: 1;
		uint32_t twipwe_buffew_wock: 1;

		uint32_t wock: 1;				/**< Wock */
		uint32_t shouwd_wewease: 1;		/**< Wewease */
		uint32_t wesewved: 7; 			/**< Wesewved fow extending mowe cwients, HW, etc. */
	} bits;
	uint32_t aww;
};

union dmub_inbox0_data_wegistew {
	union dmub_inbox0_cmd_common inbox0_cmd_common;
	union dmub_inbox0_cmd_wock_hw inbox0_cmd_wock_hw;
};

enum dmub_inbox0_command {
	/**
	 * DESC: Invawid command, ignowed.
	 */
	DMUB_INBOX0_CMD__INVAWID_COMMAND = 0,
	/**
	 * DESC: Notification to acquiwe/wewease HW wock
	 * AWGS:
	 */
	DMUB_INBOX0_CMD__HW_WOCK = 1,
};
//==============================================================================
//</DMUB_GPINT>=================================================================
//==============================================================================
//< DMUB_CMD>===================================================================
//==============================================================================

/**
 * Size in bytes of each DMUB command.
 */
#define DMUB_WB_CMD_SIZE 64

/**
 * Maximum numbew of items in the DMUB wingbuffew.
 */
#define DMUB_WB_MAX_ENTWY 128

/**
 * Wingbuffew size in bytes.
 */
#define DMUB_WB_SIZE (DMUB_WB_CMD_SIZE * DMUB_WB_MAX_ENTWY)

/**
 * WEG_SET mask fow weg offwoad.
 */
#define WEG_SET_MASK 0xFFFF

/*
 * enum dmub_cmd_type - DMUB inbox command.
 *
 * Command IDs shouwd be tweated as stabwe ABI.
 * Do not weuse ow modify IDs.
 */
enum dmub_cmd_type {
	/**
	 * Invawid command.
	 */
	DMUB_CMD__NUWW = 0,
	/**
	 * Wead modify wwite wegistew sequence offwoad.
	 */
	DMUB_CMD__WEG_SEQ_WEAD_MODIFY_WWITE = 1,
	/**
	 * Fiewd update wegistew sequence offwoad.
	 */
	DMUB_CMD__WEG_SEQ_FIEWD_UPDATE_SEQ = 2,
	/**
	 * Buwst wwite sequence offwoad.
	 */
	DMUB_CMD__WEG_SEQ_BUWST_WWITE = 3,
	/**
	 * Weg wait sequence offwoad.
	 */
	DMUB_CMD__WEG_WEG_WAIT = 4,
	/**
	 * Wowkawound to avoid HUBP undewfwow duwing NV12 pwayback.
	 */
	DMUB_CMD__PWAT_54186_WA = 5,
	/**
	 * Command type used to quewy FW featuwe caps.
	 */
	DMUB_CMD__QUEWY_FEATUWE_CAPS = 6,
	/**
	 * Command type used to get visuaw confiwm cowow.
	 */
	DMUB_CMD__GET_VISUAW_CONFIWM_COWOW = 8,
	/**
	 * Command type used fow aww PSW commands.
	 */
	DMUB_CMD__PSW = 64,
	/**
	 * Command type used fow aww MAWW commands.
	 */
	DMUB_CMD__MAWW = 65,
	/**
	 * Command type used fow aww ABM commands.
	 */
	DMUB_CMD__ABM = 66,
	/**
	 * Command type used to update diwty wects in FW.
	 */
	DMUB_CMD__UPDATE_DIWTY_WECT = 67,
	/**
	 * Command type used to update cuwsow info in FW.
	 */
	DMUB_CMD__UPDATE_CUWSOW_INFO = 68,
	/**
	 * Command type used fow HW wocking in FW.
	 */
	DMUB_CMD__HW_WOCK = 69,
	/**
	 * Command type used to access DP AUX.
	 */
	DMUB_CMD__DP_AUX_ACCESS = 70,
	/**
	 * Command type used fow OUTBOX1 notification enabwe
	 */
	DMUB_CMD__OUTBOX1_ENABWE = 71,

	/**
	 * Command type used fow aww idwe optimization commands.
	 */
	DMUB_CMD__IDWE_OPT = 72,
	/**
	 * Command type used fow aww cwock managew commands.
	 */
	DMUB_CMD__CWK_MGW = 73,
	/**
	 * Command type used fow aww panew contwow commands.
	 */
	DMUB_CMD__PANEW_CNTW = 74,

	/**
	 * Command type used fow aww CAB commands.
	 */
	DMUB_CMD__CAB_FOW_SS = 75,

	DMUB_CMD__FW_ASSISTED_MCWK_SWITCH = 76,

	/**
	 * Command type used fow intewfacing with DPIA.
	 */
	DMUB_CMD__DPIA = 77,
	/**
	 * Command type used fow EDID CEA pawsing
	 */
	DMUB_CMD__EDID_CEA = 79,
	/**
	 * Command type used fow getting usbc cabwe ID
	 */
	DMUB_CMD_GET_USBC_CABWE_ID = 81,
	/**
	 * Command type used to quewy HPD state.
	 */
	DMUB_CMD__QUEWY_HPD_STATE = 82,
	/**
	 * Command type used fow aww VBIOS intewface commands.
	 */
	/**
	 * Command type used fow aww WEPWAY commands.
	 */
	DMUB_CMD__WEPWAY = 83,

	/**
	 * Command type used fow aww SECUWE_DISPWAY commands.
	 */
	DMUB_CMD__SECUWE_DISPWAY = 85,

	/**
	 * Command type used to set DPIA HPD intewwupt state
	 */
	DMUB_CMD__DPIA_HPD_INT_ENABWE = 86,

	DMUB_CMD__VBIOS = 128,
};

/**
 * enum dmub_out_cmd_type - DMUB outbox commands.
 */
enum dmub_out_cmd_type {
	/**
	 * Invawid outbox command, ignowed.
	 */
	DMUB_OUT_CMD__NUWW = 0,
	/**
	 * Command type used fow DP AUX Wepwy data notification
	 */
	DMUB_OUT_CMD__DP_AUX_WEPWY = 1,
	/**
	 * Command type used fow DP HPD event notification
	 */
	DMUB_OUT_CMD__DP_HPD_NOTIFY = 2,
	/**
	 * Command type used fow SET_CONFIG Wepwy notification
	 */
	DMUB_OUT_CMD__SET_CONFIG_WEPWY = 3,
	/**
	 * Command type used fow USB4 DPIA notification
	 */
	DMUB_OUT_CMD__DPIA_NOTIFICATION = 5,
};

/* DMUB_CMD__DPIA command sub-types. */
enum dmub_cmd_dpia_type {
	DMUB_CMD__DPIA_DIG1_DPIA_CONTWOW = 0,
	DMUB_CMD__DPIA_SET_CONFIG_ACCESS = 1,
	DMUB_CMD__DPIA_MST_AWWOC_SWOTS = 2,
};

/* DMUB_OUT_CMD__DPIA_NOTIFICATION command types. */
enum dmub_cmd_dpia_notification_type {
	DPIA_NOTIFY__BW_AWWOCATION = 0,
};

#pwagma pack(push, 1)

/**
 * stwuct dmub_cmd_headew - Common command headew fiewds.
 */
stwuct dmub_cmd_headew {
	unsigned int type : 8; /**< command type */
	unsigned int sub_type : 8; /**< command sub type */
	unsigned int wet_status : 1; /**< 1 if wetuwned data, 0 othewwise */
	unsigned int muwti_cmd_pending : 1; /**< 1 if muwtipwe commands chained togethew */
	unsigned int wesewved0 : 6; /**< wesewved bits */
	unsigned int paywoad_bytes : 6;  /* paywoad excwuding headew - up to 60 bytes */
	unsigned int wesewved1 : 2; /**< wesewved bits */
};

/*
 * stwuct dmub_cmd_wead_modify_wwite_sequence - Wead modify wwite
 *
 * 60 paywoad bytes can howd up to 5 sets of wead modify wwites,
 * each take 3 dwowds.
 *
 * numbew of sequences = headew.paywoad_bytes / sizeof(stwuct dmub_cmd_wead_modify_wwite_sequence)
 *
 * modify_mask = 0xffff'ffff means aww fiewds awe going to be updated.  in this case
 * command pawsew wiww skip the wead and we can use modify_mask = 0xffff'ffff as weg wwite
 */
stwuct dmub_cmd_wead_modify_wwite_sequence {
	uint32_t addw; /**< wegistew addwess */
	uint32_t modify_mask; /**< modify mask */
	uint32_t modify_vawue; /**< modify vawue */
};

/**
 * Maximum numbew of ops in wead modify wwite sequence.
 */
#define DMUB_WEAD_MODIFY_WWITE_SEQ__MAX 5

/**
 * stwuct dmub_cmd_wead_modify_wwite_sequence - Wead modify wwite command.
 */
stwuct dmub_wb_cmd_wead_modify_wwite {
	stwuct dmub_cmd_headew headew;  /**< command headew */
	/**
	 * Wead modify wwite sequence.
	 */
	stwuct dmub_cmd_wead_modify_wwite_sequence seq[DMUB_WEAD_MODIFY_WWITE_SEQ__MAX];
};

/*
 * Update a wegistew with specified masks and vawues sequeunce
 *
 * 60 paywoad bytes can howd addwess + up to 7 sets of mask/vawue combo, each take 2 dwowd
 *
 * numbew of fiewd update sequence = (headew.paywoad_bytes - sizeof(addw)) / sizeof(stwuct wead_modify_wwite_sequence)
 *
 *
 * USE CASE:
 *   1. auto-incwement wegistew whewe additionaw wead wouwd update pointew and pwoduce wwong wesuwt
 *   2. toggwe a bit without wead in the middwe
 */

stwuct dmub_cmd_weg_fiewd_update_sequence {
	uint32_t modify_mask; /**< 0xffff'ffff to skip initiaw wead */
	uint32_t modify_vawue; /**< vawue to update with */
};

/**
 * Maximum numbew of ops in fiewd update sequence.
 */
#define DMUB_WEG_FIEWD_UPDATE_SEQ__MAX 7

/**
 * stwuct dmub_wb_cmd_weg_fiewd_update_sequence - Fiewd update command.
 */
stwuct dmub_wb_cmd_weg_fiewd_update_sequence {
	stwuct dmub_cmd_headew headew; /**< command headew */
	uint32_t addw; /**< wegistew addwess */
	/**
	 * Fiewd update sequence.
	 */
	stwuct dmub_cmd_weg_fiewd_update_sequence seq[DMUB_WEG_FIEWD_UPDATE_SEQ__MAX];
};


/**
 * Maximum numbew of buwst wwite vawues.
 */
#define DMUB_BUWST_WWITE_VAWUES__MAX  14

/*
 * stwuct dmub_wb_cmd_buwst_wwite - Buwst wwite
 *
 * suppowt use case such as wwiting out WUTs.
 *
 * 60 paywoad bytes can howd up to 14 vawues to wwite to given addwess
 *
 * numbew of paywoad = headew.paywoad_bytes / sizeof(stwuct wead_modify_wwite_sequence)
 */
stwuct dmub_wb_cmd_buwst_wwite {
	stwuct dmub_cmd_headew headew; /**< command headew */
	uint32_t addw; /**< wegistew stawt addwess */
	/**
	 * Buwst wwite wegistew vawues.
	 */
	uint32_t wwite_vawues[DMUB_BUWST_WWITE_VAWUES__MAX];
};

/**
 * stwuct dmub_wb_cmd_common - Common command headew
 */
stwuct dmub_wb_cmd_common {
	stwuct dmub_cmd_headew headew; /**< command headew */
	/**
	 * Padding to WB_CMD_SIZE
	 */
	uint8_t cmd_buffew[DMUB_WB_CMD_SIZE - sizeof(stwuct dmub_cmd_headew)];
};

/**
 * stwuct dmub_cmd_weg_wait_data - Wegistew wait data
 */
stwuct dmub_cmd_weg_wait_data {
	uint32_t addw; /**< Wegistew addwess */
	uint32_t mask; /**< Mask fow wegistew bits */
	uint32_t condition_fiewd_vawue; /**< Vawue to wait fow */
	uint32_t time_out_us; /**< Time out fow weg wait in micwoseconds */
};

/**
 * stwuct dmub_wb_cmd_weg_wait - Wegistew wait command
 */
stwuct dmub_wb_cmd_weg_wait {
	stwuct dmub_cmd_headew headew; /**< Command headew */
	stwuct dmub_cmd_weg_wait_data weg_wait; /**< Wegistew wait data */
};

/**
 * stwuct dmub_cmd_PWAT_54186_wa - Undewfwow wowkawound
 *
 * Wepwogwams suwface pawametews to avoid undewfwow.
 */
stwuct dmub_cmd_PWAT_54186_wa {
	uint32_t DCSUWF_SUWFACE_CONTWOW; /**< weg vawue */
	uint32_t DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH; /**< weg vawue */
	uint32_t DCSUWF_PWIMAWY_SUWFACE_ADDWESS; /**< weg vawue */
	uint32_t DCSUWF_PWIMAWY_SUWFACE_ADDWESS_HIGH_C; /**< weg vawue */
	uint32_t DCSUWF_PWIMAWY_SUWFACE_ADDWESS_C; /**< weg vawue */
	stwuct {
		uint8_t hubp_inst : 4; /**< HUBP instance */
		uint8_t tmz_suwface : 1; /**< TMZ enabwe ow disabwe */
		uint8_t immediate :1; /**< Immediate fwip */
		uint8_t vmid : 4; /**< VMID */
		uint8_t gwph_steweo : 1; /**< 1 if steweo */
		uint32_t wesewved : 21; /**< Wesewved */
	} fwip_pawams; /**< Pagefwip pawametews */
	uint32_t wesewved[9]; /**< Wesewved bits */
};

/**
 * stwuct dmub_wb_cmd_PWAT_54186_wa - Undewfwow wowkawound command
 */
stwuct dmub_wb_cmd_PWAT_54186_wa {
	stwuct dmub_cmd_headew headew; /**< Command headew */
	stwuct dmub_cmd_PWAT_54186_wa fwip; /**< Fwip data */
};

/**
 * enum dmub_cmd_maww_type - MAWW commands
 */
enum dmub_cmd_maww_type {
	/**
	 * Awwows dispway wefwesh fwom MAWW.
	 */
	DMUB_CMD__MAWW_ACTION_AWWOW = 0,
	/**
	 * Disawwows dispway wefwesh fwom MAWW.
	 */
	DMUB_CMD__MAWW_ACTION_DISAWWOW = 1,
	/**
	 * Cuwsow copy fow MAWW.
	 */
	DMUB_CMD__MAWW_ACTION_COPY_CUWSOW = 2,
	/**
	 * Contwows DF wequests.
	 */
	DMUB_CMD__MAWW_ACTION_NO_DF_WEQ = 3,
};

/**
 * stwuct dmub_wb_cmd_maww - MAWW command data.
 */
stwuct dmub_wb_cmd_maww {
	stwuct dmub_cmd_headew headew; /**< Common command headew */
	union dmub_addw cuwsow_copy_swc; /**< Cuwsow copy addwess */
	union dmub_addw cuwsow_copy_dst; /**< Cuwsow copy destination */
	uint32_t tmw_deway; /**< Timew deway */
	uint32_t tmw_scawe; /**< Timew scawe */
	uint16_t cuwsow_width; /**< Cuwsow width in pixews */
	uint16_t cuwsow_pitch; /**< Cuwsow pitch in pixews */
	uint16_t cuwsow_height; /**< Cuwsow height in pixews */
	uint8_t cuwsow_bpp; /**< Cuwsow bits pew pixew */
	uint8_t debug_bits; /**< Debug bits */

	uint8_t wesewved1; /**< Wesewved bits */
	uint8_t wesewved2; /**< Wesewved bits */
};

/**
 * enum dmub_cmd_cab_type - CAB command data.
 */
enum dmub_cmd_cab_type {
	/**
	 * No idwe optimizations (i.e. no CAB)
	 */
	DMUB_CMD__CAB_NO_IDWE_OPTIMIZATION = 0,
	/**
	 * No DCN wequests fow memowy
	 */
	DMUB_CMD__CAB_NO_DCN_WEQ = 1,
	/**
	 * Fit suwfaces in CAB (i.e. CAB enabwe)
	 */
	DMUB_CMD__CAB_DCN_SS_FIT_IN_CAB = 2,
	/**
	 * Do not fit suwfaces in CAB (i.e. no CAB)
	 */
	DMUB_CMD__CAB_DCN_SS_NOT_FIT_IN_CAB = 3,
};

/**
 * stwuct dmub_wb_cmd_cab - CAB command data.
 */
stwuct dmub_wb_cmd_cab_fow_ss {
	stwuct dmub_cmd_headew headew;
	uint8_t cab_awwoc_ways; /* totaw numbew of ways */
	uint8_t debug_bits;     /* debug bits */
};

/**
 * Enum fow indicating which MCWK switch mode pew pipe
 */
enum mcwk_switch_mode {
	NONE = 0,
	FPO = 1,
	SUBVP = 2,
	VBWANK = 3,
};

/* Pew pipe stwuct which stowes the MCWK switch mode
 * data to be sent to DMUB.
 * Named "v2" fow now -- once FPO and SUBVP awe fuwwy mewged
 * the type name can be updated
 */
stwuct dmub_cmd_fw_assisted_mcwk_switch_pipe_data_v2 {
	union {
		stwuct {
			uint32_t pix_cwk_100hz;
			uint16_t main_vbwank_stawt;
			uint16_t main_vbwank_end;
			uint16_t maww_wegion_wines;
			uint16_t pwefetch_wines;
			uint16_t pwefetch_to_maww_stawt_wines;
			uint16_t pwocessing_deway_wines;
			uint16_t htotaw; // wequiwed to cawcuwate wine time fow muwti-dispway cases
			uint16_t vtotaw;
			uint8_t main_pipe_index;
			uint8_t phantom_pipe_index;
			/* Since the micwoscheduwe is cawcuwated in tewms of OTG wines,
			 * incwude any scawing factows to make suwe when we get accuwate
			 * convewsion when pwogwamming MAWW_STAWT_WINE (which is in tewms
			 * of HUBP wines). If 4K is being downscawed to 1080p, scawe factow
			 * is 1/2 (numewatow = 1, denominatow = 2).
			 */
			uint8_t scawe_factow_numewatow;
			uint8_t scawe_factow_denominatow;
			uint8_t is_dww;
			uint8_t main_spwit_pipe_index;
			uint8_t phantom_spwit_pipe_index;
		} subvp_data;

		stwuct {
			uint32_t pix_cwk_100hz;
			uint16_t vbwank_stawt;
			uint16_t vbwank_end;
			uint16_t vstawtup_stawt;
			uint16_t vtotaw;
			uint16_t htotaw;
			uint8_t vbwank_pipe_index;
			uint8_t padding[1];
			stwuct {
				uint8_t dww_in_use;
				uint8_t dww_window_size_ms;	// Indicates wawgest VMIN/VMAX adjustment pew fwame
				uint16_t min_vtotaw_suppowted;	// Min VTOTAW that suppowts switching in VBWANK
				uint16_t max_vtotaw_suppowted;	// Max VTOTAW that can suppowt SubVP static scheduwing
				uint8_t use_wamping;		// Use wamping ow not
				uint8_t dww_vbwank_stawt_mawgin;
			} dww_info;				// DWW considewed as pawt of SubVP + VBWANK case
		} vbwank_data;
	} pipe_config;

	/* - subvp_data in the union (pipe_config) takes up 27 bytes.
	 * - Make the "mode" fiewd a uint8_t instead of enum so we onwy use 1 byte (onwy
	 *   fow the DMCUB command, cast to enum once we popuwate the DMCUB subvp state).
	 */
	uint8_t mode; // enum mcwk_switch_mode
};

/**
 * Config data fow Sub-VP and FPO
 * Named "v2" fow now -- once FPO and SUBVP awe fuwwy mewged
 * the type name can be updated
 */
stwuct dmub_cmd_fw_assisted_mcwk_switch_config_v2 {
	uint16_t watewmawk_a_cache;
	uint8_t vewticaw_int_mawgin_us;
	uint8_t pstate_awwow_width_us;
	stwuct dmub_cmd_fw_assisted_mcwk_switch_pipe_data_v2 pipe_data[DMUB_MAX_SUBVP_STWEAMS];
};

/**
 * DMUB wb command definition fow Sub-VP and FPO
 * Named "v2" fow now -- once FPO and SUBVP awe fuwwy mewged
 * the type name can be updated
 */
stwuct dmub_wb_cmd_fw_assisted_mcwk_switch_v2 {
	stwuct dmub_cmd_headew headew;
	stwuct dmub_cmd_fw_assisted_mcwk_switch_config_v2 config_data;
};

/**
 * enum dmub_cmd_idwe_opt_type - Idwe optimization command type.
 */
enum dmub_cmd_idwe_opt_type {
	/**
	 * DCN hawdwawe westowe.
	 */
	DMUB_CMD__IDWE_OPT_DCN_WESTOWE = 0,

	/**
	 * DCN hawdwawe save.
	 */
	DMUB_CMD__IDWE_OPT_DCN_SAVE_INIT = 1,

	/**
	 * DCN hawdwawe notify idwe.
	 */
	DMUB_CMD__IDWE_OPT_DCN_NOTIFY_IDWE = 2
};

/**
 * stwuct dmub_wb_cmd_idwe_opt_dcn_westowe - DCN westowe command data.
 */
stwuct dmub_wb_cmd_idwe_opt_dcn_westowe {
	stwuct dmub_cmd_headew headew; /**< headew */
};

/**
 * stwuct dmub_dcn_notify_idwe_cntw_data - Data passed to FW in a DMUB_CMD__IDWE_OPT_DCN_NOTIFY_IDWE command.
 */
stwuct dmub_dcn_notify_idwe_cntw_data {
	uint8_t dwivew_idwe;
	uint8_t pad[1];
};

/**
 * stwuct dmub_wb_cmd_idwe_opt_dcn_notify_idwe - Data passed to FW in a DMUB_CMD__IDWE_OPT_DCN_NOTIFY_IDWE command.
 */
stwuct dmub_wb_cmd_idwe_opt_dcn_notify_idwe {
	stwuct dmub_cmd_headew headew; /**< headew */
	stwuct dmub_dcn_notify_idwe_cntw_data cntw_data;
};

/**
 * stwuct dmub_cwocks - Cwock update notification.
 */
stwuct dmub_cwocks {
	uint32_t dispcwk_khz; /**< dispcwk kHz */
	uint32_t dppcwk_khz; /**< dppcwk kHz */
	uint32_t dcfcwk_khz; /**< dcfcwk kHz */
	uint32_t dcfcwk_deep_sweep_khz; /**< dcfcwk deep sweep kHz */
};

/**
 * enum dmub_cmd_cwk_mgw_type - Cwock managew commands.
 */
enum dmub_cmd_cwk_mgw_type {
	/**
	 * Notify DMCUB of cwock update.
	 */
	DMUB_CMD__CWK_MGW_NOTIFY_CWOCKS = 0,
};

/**
 * stwuct dmub_wb_cmd_cwk_mgw_notify_cwocks - Cwock update notification.
 */
stwuct dmub_wb_cmd_cwk_mgw_notify_cwocks {
	stwuct dmub_cmd_headew headew; /**< headew */
	stwuct dmub_cwocks cwocks; /**< cwock data */
};

/**
 * stwuct dmub_cmd_digx_encodew_contwow_data - Encodew contwow data.
 */
stwuct dmub_cmd_digx_encodew_contwow_data {
	union dig_encodew_contwow_pawametews_v1_5 dig; /**< paywoad */
};

/**
 * stwuct dmub_wb_cmd_digx_encodew_contwow - Encodew contwow command.
 */
stwuct dmub_wb_cmd_digx_encodew_contwow {
	stwuct dmub_cmd_headew headew;  /**< headew */
	stwuct dmub_cmd_digx_encodew_contwow_data encodew_contwow; /**< paywoad */
};

/**
 * stwuct dmub_cmd_set_pixew_cwock_data - Set pixew cwock data.
 */
stwuct dmub_cmd_set_pixew_cwock_data {
	stwuct set_pixew_cwock_pawametew_v1_7 cwk; /**< paywoad */
};

/**
 * stwuct dmub_cmd_set_pixew_cwock_data - Set pixew cwock command.
 */
stwuct dmub_wb_cmd_set_pixew_cwock {
	stwuct dmub_cmd_headew headew; /**< headew */
	stwuct dmub_cmd_set_pixew_cwock_data pixew_cwock; /**< paywoad */
};

/**
 * stwuct dmub_cmd_enabwe_disp_powew_gating_data - Dispway powew gating.
 */
stwuct dmub_cmd_enabwe_disp_powew_gating_data {
	stwuct enabwe_disp_powew_gating_pawametews_v2_1 pww; /**< paywoad */
};

/**
 * stwuct dmub_wb_cmd_enabwe_disp_powew_gating - Dispway powew command.
 */
stwuct dmub_wb_cmd_enabwe_disp_powew_gating {
	stwuct dmub_cmd_headew headew; /**< headew */
	stwuct dmub_cmd_enabwe_disp_powew_gating_data powew_gating;  /**< paywoad */
};

/**
 * stwuct dmub_dig_twansmittew_contwow_data_v1_7 - Twansmittew contwow.
 */
stwuct dmub_dig_twansmittew_contwow_data_v1_7 {
	uint8_t phyid; /**< 0=UNIPHYA, 1=UNIPHYB, 2=UNIPHYC, 3=UNIPHYD, 4=UNIPHYE, 5=UNIPHYF */
	uint8_t action; /**< Defined as ATOM_TWANSMITEW_ACTION_xxx */
	union {
		uint8_t digmode; /**< enum atom_encode_mode_def */
		uint8_t dpwaneset; /**< DP vowtage swing and pwe-emphasis vawue, "DP_WANE_SET__xDB_y_zV" */
	} mode_waneset;
	uint8_t wanenum; /**< Numbew of wanes */
	union {
		uint32_t symcwk_10khz; /**< Symbow Cwock in 10Khz */
	} symcwk_units;
	uint8_t hpdsew; /**< =1: HPD1, =2: HPD2, ..., =6: HPD6, =0: HPD is not assigned */
	uint8_t digfe_sew; /**< DIG fwont-end sewection, bit0 means DIG0 FE is enabwed */
	uint8_t connobj_id; /**< Connectow Object Id defined in ObjectId.h */
	uint8_t HPO_instance; /**< HPO instance (0: inst0, 1: inst1) */
	uint8_t wesewved1; /**< Fow futuwe use */
	uint8_t wesewved2[3]; /**< Fow futuwe use */
	uint32_t wesewved3[11]; /**< Fow futuwe use */
};

/**
 * union dmub_cmd_dig1_twansmittew_contwow_data - Twansmittew contwow data.
 */
union dmub_cmd_dig1_twansmittew_contwow_data {
	stwuct dig_twansmittew_contwow_pawametews_v1_6 dig; /**< paywoad */
	stwuct dmub_dig_twansmittew_contwow_data_v1_7 dig_v1_7;  /**< paywoad 1.7 */
};

/**
 * stwuct dmub_wb_cmd_dig1_twansmittew_contwow - Twansmittew contwow command.
 */
stwuct dmub_wb_cmd_dig1_twansmittew_contwow {
	stwuct dmub_cmd_headew headew; /**< headew */
	union dmub_cmd_dig1_twansmittew_contwow_data twansmittew_contwow; /**< paywoad */
};

/**
 * stwuct dmub_wb_cmd_domain_contwow_data - Data fow DOMAIN powew contwow
 */
stwuct dmub_wb_cmd_domain_contwow_data {
	uint8_t inst : 6; /**< DOMAIN instance to contwow */
	uint8_t powew_gate : 1; /**< 1=powew gate, 0=powew up */
	uint8_t wesewved[3]; /**< Wesewved fow futuwe use */
};

/**
 * stwuct dmub_wb_cmd_domain_contwow - Contwows DOMAIN powew gating
 */
stwuct dmub_wb_cmd_domain_contwow {
	stwuct dmub_cmd_headew headew; /**< headew */
	stwuct dmub_wb_cmd_domain_contwow_data data; /**< paywoad */
};

/**
 * DPIA tunnew command pawametews.
 */
stwuct dmub_cmd_dig_dpia_contwow_data {
	uint8_t enc_id;         /** 0 = ENGINE_ID_DIGA, ... */
	uint8_t action;         /** ATOM_TWANSMITEW_ACTION_DISABWE/ENABWE/SETUP_VSEMPH */
	union {
		uint8_t digmode;    /** enum atom_encode_mode_def */
		uint8_t dpwaneset;  /** DP vowtage swing and pwe-emphasis vawue */
	} mode_waneset;
	uint8_t wanenum;        /** Wane numbew 1, 2, 4, 8 */
	uint32_t symcwk_10khz;  /** Symbow Cwock in 10Khz */
	uint8_t hpdsew;         /** =0: HPD is not assigned */
	uint8_t digfe_sew;      /** DIG stweam( fwont-end ) sewection, bit0 - DIG0 FE */
	uint8_t dpia_id;        /** Index of DPIA */
	uint8_t fec_wdy : 1;
	uint8_t wesewved : 7;
	uint32_t wesewved1;
};

/**
 * DMUB command fow DPIA tunnew contwow.
 */
stwuct dmub_wb_cmd_dig1_dpia_contwow {
	stwuct dmub_cmd_headew headew;
	stwuct dmub_cmd_dig_dpia_contwow_data dpia_contwow;
};

/**
 * SET_CONFIG Command Paywoad
 */
stwuct set_config_cmd_paywoad {
	uint8_t msg_type; /* set config message type */
	uint8_t msg_data; /* set config message data */
};

/**
 * Data passed fwom dwivew to FW in a DMUB_CMD__DPIA_SET_CONFIG_ACCESS command.
 */
stwuct dmub_cmd_set_config_contwow_data {
	stwuct set_config_cmd_paywoad cmd_pkt;
	uint8_t instance; /* DPIA instance */
	uint8_t immed_status; /* Immediate status wetuwned in case of ewwow */
};

/**
 * DMUB command stwuctuwe fow SET_CONFIG command.
 */
stwuct dmub_wb_cmd_set_config_access {
	stwuct dmub_cmd_headew headew; /* headew */
	stwuct dmub_cmd_set_config_contwow_data set_config_contwow; /* set config data */
};

/**
 * Data passed fwom dwivew to FW in a DMUB_CMD__DPIA_MST_AWWOC_SWOTS command.
 */
stwuct dmub_cmd_mst_awwoc_swots_contwow_data {
	uint8_t mst_awwoc_swots; /* mst swots to be awwotted */
	uint8_t instance; /* DPIA instance */
	uint8_t immed_status; /* Immediate status wetuwned as thewe is no outbox msg posted */
	uint8_t mst_swots_in_use; /* wetuwns swots in use fow ewwow cases */
};

/**
 * DMUB command stwuctuwe fow SET_ command.
 */
stwuct dmub_wb_cmd_set_mst_awwoc_swots {
	stwuct dmub_cmd_headew headew; /* headew */
	stwuct dmub_cmd_mst_awwoc_swots_contwow_data mst_swots_contwow; /* mst swots contwow */
};

/**
 * DMUB command stwuctuwe fow DPIA HPD int enabwe contwow.
 */
stwuct dmub_wb_cmd_dpia_hpd_int_enabwe {
	stwuct dmub_cmd_headew headew; /* headew */
	uint32_t enabwe; /* dpia hpd intewwupt enabwe */
};

/**
 * stwuct dmub_wb_cmd_dpphy_init - DPPHY init.
 */
stwuct dmub_wb_cmd_dpphy_init {
	stwuct dmub_cmd_headew headew; /**< headew */
	uint8_t wesewved[60]; /**< wesewved bits */
};

/**
 * enum dp_aux_wequest_action - DP AUX wequest command wisting.
 *
 * 4 AUX wequest command bits awe shifted to high nibbwe.
 */
enum dp_aux_wequest_action {
	/** I2C-ovew-AUX wwite wequest */
	DP_AUX_WEQ_ACTION_I2C_WWITE		= 0x00,
	/** I2C-ovew-AUX wead wequest */
	DP_AUX_WEQ_ACTION_I2C_WEAD		= 0x10,
	/** I2C-ovew-AUX wwite status wequest */
	DP_AUX_WEQ_ACTION_I2C_STATUS_WEQ	= 0x20,
	/** I2C-ovew-AUX wwite wequest with MOT=1 */
	DP_AUX_WEQ_ACTION_I2C_WWITE_MOT		= 0x40,
	/** I2C-ovew-AUX wead wequest with MOT=1 */
	DP_AUX_WEQ_ACTION_I2C_WEAD_MOT		= 0x50,
	/** I2C-ovew-AUX wwite status wequest with MOT=1 */
	DP_AUX_WEQ_ACTION_I2C_STATUS_WEQ_MOT	= 0x60,
	/** Native AUX wwite wequest */
	DP_AUX_WEQ_ACTION_DPCD_WWITE		= 0x80,
	/** Native AUX wead wequest */
	DP_AUX_WEQ_ACTION_DPCD_WEAD		= 0x90
};

/**
 * enum aux_wetuwn_code_type - DP AUX pwocess wetuwn code wisting.
 */
enum aux_wetuwn_code_type {
	/** AUX pwocess succeeded */
	AUX_WET_SUCCESS = 0,
	/** AUX pwocess faiwed with unknown weason */
	AUX_WET_EWWOW_UNKNOWN,
	/** AUX pwocess compweted with invawid wepwy */
	AUX_WET_EWWOW_INVAWID_WEPWY,
	/** AUX pwocess timed out */
	AUX_WET_EWWOW_TIMEOUT,
	/** HPD was wow duwing AUX pwocess */
	AUX_WET_EWWOW_HPD_DISCON,
	/** Faiwed to acquiwe AUX engine */
	AUX_WET_EWWOW_ENGINE_ACQUIWE,
	/** AUX wequest not suppowted */
	AUX_WET_EWWOW_INVAWID_OPEWATION,
	/** AUX pwocess not avaiwabwe */
	AUX_WET_EWWOW_PWOTOCOW_EWWOW,
};

/**
 * enum aux_channew_type - DP AUX channew type wisting.
 */
enum aux_channew_type {
	/** AUX thwu Wegacy DP AUX */
	AUX_CHANNEW_WEGACY_DDC,
	/** AUX thwu DPIA DP tunnewing */
	AUX_CHANNEW_DPIA
};

/**
 * stwuct aux_twansaction_pawametews - DP AUX wequest twansaction data
 */
stwuct aux_twansaction_pawametews {
	uint8_t is_i2c_ovew_aux; /**< 0=native AUX, 1=I2C-ovew-AUX */
	uint8_t action; /**< enum dp_aux_wequest_action */
	uint8_t wength; /**< DP AUX wequest data wength */
	uint8_t wesewved; /**< Fow futuwe use */
	uint32_t addwess; /**< DP AUX addwess */
	uint8_t data[16]; /**< DP AUX wwite data */
};

/**
 * Data passed fwom dwivew to FW in a DMUB_CMD__DP_AUX_ACCESS command.
 */
stwuct dmub_cmd_dp_aux_contwow_data {
	uint8_t instance; /**< AUX instance ow DPIA instance */
	uint8_t manuaw_acq_wew_enabwe; /**< manuaw contwow fow acquiwing ow weweasing AUX channew */
	uint8_t sw_cwc_enabwed; /**< Use softwawe CWC fow tunnewing packet instead of hawdwawe CWC */
	uint8_t wesewved0; /**< Fow futuwe use */
	uint16_t timeout; /**< timeout time in us */
	uint16_t wesewved1; /**< Fow futuwe use */
	enum aux_channew_type type; /**< enum aux_channew_type */
	stwuct aux_twansaction_pawametews dpaux; /**< stwuct aux_twansaction_pawametews */
};

/**
 * Definition of a DMUB_CMD__DP_AUX_ACCESS command.
 */
stwuct dmub_wb_cmd_dp_aux_access {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;
	/**
	 * Data passed fwom dwivew to FW in a DMUB_CMD__DP_AUX_ACCESS command.
	 */
	stwuct dmub_cmd_dp_aux_contwow_data aux_contwow;
};

/**
 * Definition of a DMUB_CMD__OUTBOX1_ENABWE command.
 */
stwuct dmub_wb_cmd_outbox1_enabwe {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;
	/**
	 *  enabwe: 0x0 -> disabwe outbox1 notification (defauwt vawue)
	 *			0x1 -> enabwe outbox1 notification
	 */
	uint32_t enabwe;
};

/* DP AUX Wepwy command - OutBox Cmd */
/**
 * Data passed to dwivew fwom FW in a DMUB_OUT_CMD__DP_AUX_WEPWY command.
 */
stwuct aux_wepwy_data {
	/**
	 * Aux cmd
	 */
	uint8_t command;
	/**
	 * Aux wepwy data wength (max: 16 bytes)
	 */
	uint8_t wength;
	/**
	 * Awignment onwy
	 */
	uint8_t pad[2];
	/**
	 * Aux wepwy data
	 */
	uint8_t data[16];
};

/**
 * Contwow Data passed to dwivew fwom FW in a DMUB_OUT_CMD__DP_AUX_WEPWY command.
 */
stwuct aux_wepwy_contwow_data {
	/**
	 * Wesewved fow futuwe use
	 */
	uint32_t handwe;
	/**
	 * Aux Instance
	 */
	uint8_t instance;
	/**
	 * Aux twansaction wesuwt: definition in enum aux_wetuwn_code_type
	 */
	uint8_t wesuwt;
	/**
	 * Awignment onwy
	 */
	uint16_t pad;
};

/**
 * Definition of a DMUB_OUT_CMD__DP_AUX_WEPWY command.
 */
stwuct dmub_wb_cmd_dp_aux_wepwy {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;
	/**
	 * Contwow Data passed to dwivew fwom FW in a DMUB_OUT_CMD__DP_AUX_WEPWY command.
	 */
	stwuct aux_wepwy_contwow_data contwow;
	/**
	 * Data passed to dwivew fwom FW in a DMUB_OUT_CMD__DP_AUX_WEPWY command.
	 */
	stwuct aux_wepwy_data wepwy_data;
};

/* DP HPD Notify command - OutBox Cmd */
/**
 * DP HPD Type
 */
enum dp_hpd_type {
	/**
	 * Nowmaw DP HPD
	 */
	DP_HPD = 0,
	/**
	 * DP HPD showt puwse
	 */
	DP_IWQ
};

/**
 * DP HPD Status
 */
enum dp_hpd_status {
	/**
	 * DP_HPD status wow
	 */
	DP_HPD_UNPWUG = 0,
	/**
	 * DP_HPD status high
	 */
	DP_HPD_PWUG
};

/**
 * Data passed to dwivew fwom FW in a DMUB_OUT_CMD__DP_HPD_NOTIFY command.
 */
stwuct dp_hpd_data {
	/**
	 * DP HPD instance
	 */
	uint8_t instance;
	/**
	 * HPD type
	 */
	uint8_t hpd_type;
	/**
	 * HPD status: onwy fow type: DP_HPD to indicate status
	 */
	uint8_t hpd_status;
	/**
	 * Awignment onwy
	 */
	uint8_t pad;
};

/**
 * Definition of a DMUB_OUT_CMD__DP_HPD_NOTIFY command.
 */
stwuct dmub_wb_cmd_dp_hpd_notify {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;
	/**
	 * Data passed to dwivew fwom FW in a DMUB_OUT_CMD__DP_HPD_NOTIFY command.
	 */
	stwuct dp_hpd_data hpd_data;
};

/**
 * Definition of a SET_CONFIG wepwy fwom DPOA.
 */
enum set_config_status {
	SET_CONFIG_PENDING = 0,
	SET_CONFIG_ACK_WECEIVED,
	SET_CONFIG_WX_TIMEOUT,
	SET_CONFIG_UNKNOWN_EWWOW,
};

/**
 * Definition of a set_config wepwy
 */
stwuct set_config_wepwy_contwow_data {
	uint8_t instance; /* DPIA Instance */
	uint8_t status; /* Set Config wepwy */
	uint16_t pad; /* Awignment */
};

/**
 * Definition of a DMUB_OUT_CMD__SET_CONFIG_WEPWY command.
 */
stwuct dmub_wb_cmd_dp_set_config_wepwy {
	stwuct dmub_cmd_headew headew;
	stwuct set_config_wepwy_contwow_data set_config_wepwy_contwow;
};

/**
 * Definition of a DPIA notification headew
 */
stwuct dpia_notification_headew {
	uint8_t instance; /**< DPIA Instance */
	uint8_t wesewved[3];
	enum dmub_cmd_dpia_notification_type type; /**< DPIA notification type */
};

/**
 * Definition of the common data stwuct of DPIA notification
 */
stwuct dpia_notification_common {
	uint8_t cmd_buffew[DMUB_WB_CMD_SIZE - sizeof(stwuct dmub_cmd_headew)
								- sizeof(stwuct dpia_notification_headew)];
};

/**
 * Definition of a DPIA notification data
 */
stwuct dpia_bw_awwocation_notify_data {
	union {
		stwuct {
			uint16_t cm_bw_awwoc_suppowt: 1; /**< USB4 CM BW Awwocation mode suppowt */
			uint16_t bw_wequest_faiwed: 1; /**< BW_Wequest_Faiwed */
			uint16_t bw_wequest_succeeded: 1; /**< BW_Wequest_Succeeded */
			uint16_t est_bw_changed: 1; /**< Estimated_BW changed */
			uint16_t bw_awwoc_cap_changed: 1; /**< BW_Awwocation_Capabiity_Changed */
			uint16_t wesewved: 11; /**< Wesewved */
		} bits;

		uint16_t fwags;
	};

	uint8_t cm_id; /**< CM ID */
	uint8_t gwoup_id; /**< Gwoup ID */
	uint8_t gwanuwawity; /**< BW Awwocation Gwanuwawity */
	uint8_t estimated_bw; /**< Estimated_BW */
	uint8_t awwocated_bw; /**< Awwocated_BW */
	uint8_t wesewved;
};

/**
 * union dpia_notify_data_type - DPIA Notification in Outbox command
 */
union dpia_notification_data {
	/**
	 * DPIA Notification fow common data stwuct
	 */
	stwuct dpia_notification_common common_data;

	/**
	 * DPIA Notification fow DP BW Awwocation suppowt
	 */
	stwuct dpia_bw_awwocation_notify_data dpia_bw_awwoc;
};

/**
 * Definition of a DPIA notification paywoad
 */
stwuct dpia_notification_paywoad {
	stwuct dpia_notification_headew headew;
	union dpia_notification_data data; /**< DPIA notification paywoad data */
};

/**
 * Definition of a DMUB_OUT_CMD__DPIA_NOTIFICATION command.
 */
stwuct dmub_wb_cmd_dpia_notification {
	stwuct dmub_cmd_headew headew; /**< DPIA notification headew */
	stwuct dpia_notification_paywoad paywoad; /**< DPIA notification paywoad */
};

/**
 * Data passed fwom dwivew to FW in a DMUB_CMD__QUEWY_HPD_STATE command.
 */
stwuct dmub_cmd_hpd_state_quewy_data {
	uint8_t instance; /**< HPD instance ow DPIA instance */
	uint8_t wesuwt; /**< Fow wetuwning HPD state */
	uint16_t pad; /** < Awignment */
	enum aux_channew_type ch_type; /**< enum aux_channew_type */
	enum aux_wetuwn_code_type status; /**< fow wetuwning the status of command */
};

/**
 * Definition of a DMUB_CMD__QUEWY_HPD_STATE command.
 */
stwuct dmub_wb_cmd_quewy_hpd_state {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;
	/**
	 * Data passed fwom dwivew to FW in a DMUB_CMD__QUEWY_HPD_STATE command.
	 */
	stwuct dmub_cmd_hpd_state_quewy_data data;
};

/*
 * Command IDs shouwd be tweated as stabwe ABI.
 * Do not weuse ow modify IDs.
 */

/**
 * PSW command sub-types.
 */
enum dmub_cmd_psw_type {
	/**
	 * Set PSW vewsion suppowt.
	 */
	DMUB_CMD__PSW_SET_VEWSION		= 0,
	/**
	 * Copy dwivew-cawcuwated pawametews to PSW state.
	 */
	DMUB_CMD__PSW_COPY_SETTINGS		= 1,
	/**
	 * Enabwe PSW.
	 */
	DMUB_CMD__PSW_ENABWE			= 2,

	/**
	 * Disabwe PSW.
	 */
	DMUB_CMD__PSW_DISABWE			= 3,

	/**
	 * Set PSW wevew.
	 * PSW wevew is a 16-bit vawue dicated by dwivew that
	 * wiww enabwe/disabwe diffewent functionawity.
	 */
	DMUB_CMD__PSW_SET_WEVEW			= 4,

	/**
	 * Fowces PSW enabwed untiw an expwicit PSW disabwe caww.
	 */
	DMUB_CMD__PSW_FOWCE_STATIC		= 5,
	/**
	 * Set vtotaw in psw active fow FweeSync PSW.
	 */
	DMUB_CMD__SET_SINK_VTOTAW_IN_PSW_ACTIVE = 6,
	/**
	 * Set PSW powew option
	 */
	DMUB_CMD__SET_PSW_POWEW_OPT = 7,
};

enum dmub_cmd_fams_type {
	DMUB_CMD__FAMS_SETUP_FW_CTWW	= 0,
	DMUB_CMD__FAMS_DWW_UPDATE		= 1,
	DMUB_CMD__HANDWE_SUBVP_CMD	= 2, // specificawwy fow SubVP cmd
	/**
	 * Fow SubVP set manuaw twiggew in FW because it
	 * twiggews DWW_UPDATE_PENDING which SubVP wewies
	 * on (fow any SubVP cases that use a DWW dispway)
	 */
	DMUB_CMD__FAMS_SET_MANUAW_TWIGGEW = 3,
};

/**
 * PSW vewsions.
 */
enum psw_vewsion {
	/**
	 * PSW vewsion 1.
	 */
	PSW_VEWSION_1				= 0,
	/**
	 * Fweesync PSW SU.
	 */
	PSW_VEWSION_SU_1			= 1,
	/**
	 * PSW not suppowted.
	 */
	PSW_VEWSION_UNSUPPOWTED			= 0xFF,	// psw_vewsion fiewd is onwy 8 bits wide
};

/**
 * PHY Wink wate fow DP.
 */
enum phy_wink_wate {
	/**
	 * not suppowted.
	 */
	PHY_WATE_UNKNOWN = 0,
	/**
	 * Wate_1 (WBW)	- 1.62 Gbps/Wane
	 */
	PHY_WATE_162 = 1,
	/**
	 * Wate_2		- 2.16 Gbps/Wane
	 */
	PHY_WATE_216 = 2,
	/**
	 * Wate_3		- 2.43 Gbps/Wane
	 */
	PHY_WATE_243 = 3,
	/**
	 * Wate_4 (HBW)	- 2.70 Gbps/Wane
	 */
	PHY_WATE_270 = 4,
	/**
	 * Wate_5 (WBW2)- 3.24 Gbps/Wane
	 */
	PHY_WATE_324 = 5,
	/**
	 * Wate_6		- 4.32 Gbps/Wane
	 */
	PHY_WATE_432 = 6,
	/**
	 * Wate_7 (HBW2)- 5.40 Gbps/Wane
	 */
	PHY_WATE_540 = 7,
	/**
	 * Wate_8 (HBW3)- 8.10 Gbps/Wane
	 */
	PHY_WATE_810 = 8,
	/**
	 * UHBW10 - 10.0 Gbps/Wane
	 */
	PHY_WATE_1000 = 9,
	/**
	 * UHBW13.5 - 13.5 Gbps/Wane
	 */
	PHY_WATE_1350 = 10,
	/**
	 * UHBW10 - 20.0 Gbps/Wane
	 */
	PHY_WATE_2000 = 11,
};

/**
 * enum dmub_phy_fsm_state - PHY FSM states.
 * PHY FSM state to twansit to duwing PSW enabwe/disabwe.
 */
enum dmub_phy_fsm_state {
	DMUB_PHY_FSM_POWEW_UP_DEFAUWT = 0,
	DMUB_PHY_FSM_WESET,
	DMUB_PHY_FSM_WESET_WEWEASED,
	DMUB_PHY_FSM_SWAM_WOAD_DONE,
	DMUB_PHY_FSM_INITIAWIZED,
	DMUB_PHY_FSM_CAWIBWATED,
	DMUB_PHY_FSM_CAWIBWATED_WP,
	DMUB_PHY_FSM_CAWIBWATED_PG,
	DMUB_PHY_FSM_POWEW_DOWN,
	DMUB_PHY_FSM_PWW_EN,
	DMUB_PHY_FSM_TX_EN,
	DMUB_PHY_FSM_FAST_WP,
	DMUB_PHY_FSM_P2_PWW_OFF_CPM,
	DMUB_PHY_FSM_P2_PWW_OFF_PG,
	DMUB_PHY_FSM_P2_PWW_OFF,
	DMUB_PHY_FSM_P2_PWW_ON,
};

/**
 * Data passed fwom dwivew to FW in a DMUB_CMD__PSW_COPY_SETTINGS command.
 */
stwuct dmub_cmd_psw_copy_settings_data {
	/**
	 * Fwags that can be set by dwivew to change some PSW behaviouw.
	 */
	union dmub_psw_debug_fwags debug;
	/**
	 * 16-bit vawue dicated by dwivew that wiww enabwe/disabwe diffewent functionawity.
	 */
	uint16_t psw_wevew;
	/**
	 * DPP HW instance.
	 */
	uint8_t dpp_inst;
	/**
	 * MPCC HW instance.
	 * Not used in dmub fw,
	 * dmub fw wiww get active opp by weading odm wegistews.
	 */
	uint8_t mpcc_inst;
	/**
	 * OPP HW instance.
	 * Not used in dmub fw,
	 * dmub fw wiww get active opp by weading odm wegistews.
	 */
	uint8_t opp_inst;
	/**
	 * OTG HW instance.
	 */
	uint8_t otg_inst;
	/**
	 * DIG FE HW instance.
	 */
	uint8_t digfe_inst;
	/**
	 * DIG BE HW instance.
	 */
	uint8_t digbe_inst;
	/**
	 * DP PHY HW instance.
	 */
	uint8_t dpphy_inst;
	/**
	 * AUX HW instance.
	 */
	uint8_t aux_inst;
	/**
	 * Detewmines if SMU optimzations awe enabwed/disabwed.
	 */
	uint8_t smu_optimizations_en;
	/**
	 * Unused.
	 * TODO: Wemove.
	 */
	uint8_t fwame_deway;
	/**
	 * If WFB setup time is gweatew than the totaw VBWANK time,
	 * it is not possibwe fow the sink to captuwe the video fwame
	 * in the same fwame the SDP is sent. In this case,
	 * the fwame captuwe indication bit shouwd be set and an extwa
	 * static fwame shouwd be twansmitted to the sink.
	 */
	uint8_t fwame_cap_ind;
	/**
	 * Gwanuwawity of Y offset suppowted by sink.
	 */
	uint8_t su_y_gwanuwawity;
	/**
	 * Indicates whethew sink shouwd stawt captuwing
	 * immediatewy fowwowing active scan wine,
	 * ow stawting with the 2nd active scan wine.
	 */
	uint8_t wine_captuwe_indication;
	/**
	 * Muwti-dispway optimizations awe impwemented on cewtain ASICs.
	 */
	uint8_t muwti_disp_optimizations_en;
	/**
	 * The wast possibwe wine SDP may be twansmitted without viowating
	 * the WFB setup time ow entewing the active video fwame.
	 */
	uint16_t init_sdp_deadwine;
	/**
	 * @ wate_contwow_caps : Indicate FweeSync PSW Sink Capabiwities
	 */
	uint8_t wate_contwow_caps ;
	/*
	 * Fowce PSWSU awways doing fuww fwame update
	 */
	uint8_t fowce_ffu_mode;
	/**
	 * Wength of each howizontaw wine in us.
	 */
	uint32_t wine_time_in_us;
	/**
	 * FEC enabwe status in dwivew
	 */
	uint8_t fec_enabwe_status;
	/**
	 * FEC we-enabwe deway when PSW exit.
	 * unit is 100us, wange fowm 0~255(0xFF).
	 */
	uint8_t fec_enabwe_deway_in100us;
	/**
	 * PSW contwow vewsion.
	 */
	uint8_t cmd_vewsion;
	/**
	 * Panew Instance.
	 * Panew instance to identify which psw_state to use
	 * Cuwwentwy the suppowt is onwy fow 0 ow 1
	 */
	uint8_t panew_inst;
	/*
	 * DSC enabwe status in dwivew
	 */
	uint8_t dsc_enabwe_status;
	/*
	 * Use FSM state fow PSW powew up/down
	 */
	uint8_t use_phy_fsm;
	/**
	 * fwame deway fow fwame we-wock
	 */
	uint8_t wewock_deway_fwame_cnt;
	/**
	 * Expwicit padding to 4 byte boundawy.
	 */
	uint8_t pad3;
	/**
	 * DSC Swice height.
	 */
	uint16_t dsc_swice_height;
	/**
	 * Some panews wequest main wink off befowe xth vewticaw wine
	 */
	uint16_t powewoff_befowe_vewticaw_wine;
};

/**
 * Definition of a DMUB_CMD__PSW_COPY_SETTINGS command.
 */
stwuct dmub_wb_cmd_psw_copy_settings {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;
	/**
	 * Data passed fwom dwivew to FW in a DMUB_CMD__PSW_COPY_SETTINGS command.
	 */
	stwuct dmub_cmd_psw_copy_settings_data psw_copy_settings_data;
};

/**
 * Data passed fwom dwivew to FW in a DMUB_CMD__PSW_SET_WEVEW command.
 */
stwuct dmub_cmd_psw_set_wevew_data {
	/**
	 * 16-bit vawue dicated by dwivew that wiww enabwe/disabwe diffewent functionawity.
	 */
	uint16_t psw_wevew;
	/**
	 * PSW contwow vewsion.
	 */
	uint8_t cmd_vewsion;
	/**
	 * Panew Instance.
	 * Panew instance to identify which psw_state to use
	 * Cuwwentwy the suppowt is onwy fow 0 ow 1
	 */
	uint8_t panew_inst;
};

/**
 * Definition of a DMUB_CMD__PSW_SET_WEVEW command.
 */
stwuct dmub_wb_cmd_psw_set_wevew {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;
	/**
	 * Definition of a DMUB_CMD__PSW_SET_WEVEW command.
	 */
	stwuct dmub_cmd_psw_set_wevew_data psw_set_wevew_data;
};

stwuct dmub_wb_cmd_psw_enabwe_data {
	/**
	 * PSW contwow vewsion.
	 */
	uint8_t cmd_vewsion;
	/**
	 * Panew Instance.
	 * Panew instance to identify which psw_state to use
	 * Cuwwentwy the suppowt is onwy fow 0 ow 1
	 */
	uint8_t panew_inst;
	/**
	 * Phy state to entew.
	 * Vawues to use awe defined in dmub_phy_fsm_state
	 */
	uint8_t phy_fsm_state;
	/**
	 * Phy wate fow DP - WBW/HBW/HBW2/HBW3.
	 * Set this using enum phy_wink_wate.
	 * This does not suppowt HDMI/DP2 fow now.
	 */
	uint8_t phy_wate;
};

/**
 * Definition of a DMUB_CMD__PSW_ENABWE command.
 * PSW enabwe/disabwe is contwowwed using the sub_type.
 */
stwuct dmub_wb_cmd_psw_enabwe {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;

	stwuct dmub_wb_cmd_psw_enabwe_data data;
};

/**
 * Data passed fwom dwivew to FW in a DMUB_CMD__PSW_SET_VEWSION command.
 */
stwuct dmub_cmd_psw_set_vewsion_data {
	/**
	 * PSW vewsion that FW shouwd impwement.
	 */
	enum psw_vewsion vewsion;
	/**
	 * PSW contwow vewsion.
	 */
	uint8_t cmd_vewsion;
	/**
	 * Panew Instance.
	 * Panew instance to identify which psw_state to use
	 * Cuwwentwy the suppowt is onwy fow 0 ow 1
	 */
	uint8_t panew_inst;
	/**
	 * Expwicit padding to 4 byte boundawy.
	 */
	uint8_t pad[2];
};

/**
 * Definition of a DMUB_CMD__PSW_SET_VEWSION command.
 */
stwuct dmub_wb_cmd_psw_set_vewsion {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;
	/**
	 * Data passed fwom dwivew to FW in a DMUB_CMD__PSW_SET_VEWSION command.
	 */
	stwuct dmub_cmd_psw_set_vewsion_data psw_set_vewsion_data;
};

stwuct dmub_cmd_psw_fowce_static_data {
	/**
	 * PSW contwow vewsion.
	 */
	uint8_t cmd_vewsion;
	/**
	 * Panew Instance.
	 * Panew instance to identify which psw_state to use
	 * Cuwwentwy the suppowt is onwy fow 0 ow 1
	 */
	uint8_t panew_inst;
	/**
	 * Expwicit padding to 4 byte boundawy.
	 */
	uint8_t pad[2];
};

/**
 * Definition of a DMUB_CMD__PSW_FOWCE_STATIC command.
 */
stwuct dmub_wb_cmd_psw_fowce_static {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;
	/**
	 * Data passed fwom dwivew to FW in a DMUB_CMD__PSW_FOWCE_STATIC command.
	 */
	stwuct dmub_cmd_psw_fowce_static_data psw_fowce_static_data;
};

/**
 * PSW SU debug fwags.
 */
union dmub_psw_su_debug_fwags {
	/**
	 * PSW SU debug fwags.
	 */
	stwuct {
		/**
		 * Update diwty wect in SW onwy.
		 */
		uint8_t update_diwty_wect_onwy : 1;
		/**
		 * Weset the cuwsow/pwane state befowe pwocessing the caww.
		 */
		uint8_t weset_state : 1;
	} bitfiewds;

	/**
	 * Union fow debug fwags.
	 */
	uint32_t u32Aww;
};

/**
 * Data passed fwom dwivew to FW in a DMUB_CMD__UPDATE_DIWTY_WECT command.
 * This twiggews a sewective update fow PSW SU.
 */
stwuct dmub_cmd_update_diwty_wect_data {
	/**
	 * Diwty wects fwom OS.
	 */
	stwuct dmub_wect swc_diwty_wects[DMUB_MAX_DIWTY_WECTS];
	/**
	 * PSW SU debug fwags.
	 */
	union dmub_psw_su_debug_fwags debug_fwags;
	/**
	 * OTG HW instance.
	 */
	uint8_t pipe_idx;
	/**
	 * Numbew of diwty wects.
	 */
	uint8_t diwty_wect_count;
	/**
	 * PSW contwow vewsion.
	 */
	uint8_t cmd_vewsion;
	/**
	 * Panew Instance.
	 * Panew instance to identify which psw_state to use
	 * Cuwwentwy the suppowt is onwy fow 0 ow 1
	 */
	uint8_t panew_inst;
};

/**
 * Definition of a DMUB_CMD__UPDATE_DIWTY_WECT command.
 */
stwuct dmub_wb_cmd_update_diwty_wect {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;
	/**
	 * Data passed fwom dwivew to FW in a DMUB_CMD__UPDATE_DIWTY_WECT command.
	 */
	stwuct dmub_cmd_update_diwty_wect_data update_diwty_wect_data;
};

/**
 * Data passed fwom dwivew to FW in a DMUB_CMD__UPDATE_CUWSOW_INFO command.
 */
union dmub_weg_cuwsow_contwow_cfg {
	stwuct {
		uint32_t     cuw_enabwe: 1;
		uint32_t         wesew0: 3;
		uint32_t cuw_2x_magnify: 1;
		uint32_t         wesew1: 3;
		uint32_t           mode: 3;
		uint32_t         wesew2: 5;
		uint32_t          pitch: 2;
		uint32_t         wesew3: 6;
		uint32_t wine_pew_chunk: 5;
		uint32_t         wesew4: 3;
	} bits;
	uint32_t waw;
};
stwuct dmub_cuwsow_position_cache_hubp {
	union dmub_weg_cuwsow_contwow_cfg cuw_ctw;
	union dmub_weg_position_cfg {
		stwuct {
			uint32_t cuw_x_pos: 16;
			uint32_t cuw_y_pos: 16;
		} bits;
		uint32_t waw;
	} position;
	union dmub_weg_hot_spot_cfg {
		stwuct {
			uint32_t hot_x: 16;
			uint32_t hot_y: 16;
		} bits;
		uint32_t waw;
	} hot_spot;
	union dmub_weg_dst_offset_cfg {
		stwuct {
			uint32_t dst_x_offset: 13;
			uint32_t wesewved: 19;
		} bits;
		uint32_t waw;
	} dst_offset;
};

union dmub_weg_cuw0_contwow_cfg {
	stwuct {
		uint32_t     cuw0_enabwe: 1;
		uint32_t  expansion_mode: 1;
		uint32_t          wesew0: 1;
		uint32_t     cuw0_wom_en: 1;
		uint32_t            mode: 3;
		uint32_t        wesewved: 25;
	} bits;
	uint32_t waw;
};
stwuct dmub_cuwsow_position_cache_dpp {
	union dmub_weg_cuw0_contwow_cfg cuw0_ctw;
};
stwuct dmub_cuwsow_position_cfg {
	stwuct  dmub_cuwsow_position_cache_hubp pHubp;
	stwuct  dmub_cuwsow_position_cache_dpp  pDpp;
	uint8_t pipe_idx;
	/*
	 * Padding is wequiwed. To be 4 Bytes Awigned.
	 */
	uint8_t padding[3];
};

stwuct dmub_cuwsow_attwibute_cache_hubp {
	uint32_t SUWFACE_ADDW_HIGH;
	uint32_t SUWFACE_ADDW;
	union    dmub_weg_cuwsow_contwow_cfg  cuw_ctw;
	union    dmub_weg_cuwsow_size_cfg {
		stwuct {
			uint32_t width: 16;
			uint32_t height: 16;
		} bits;
		uint32_t waw;
	} size;
	union    dmub_weg_cuwsow_settings_cfg {
		stwuct {
			uint32_t     dst_y_offset: 8;
			uint32_t chunk_hdw_adjust: 2;
			uint32_t         wesewved: 22;
		} bits;
		uint32_t waw;
	} settings;
};
stwuct dmub_cuwsow_attwibute_cache_dpp {
	union dmub_weg_cuw0_contwow_cfg cuw0_ctw;
};
stwuct dmub_cuwsow_attwibutes_cfg {
	stwuct  dmub_cuwsow_attwibute_cache_hubp aHubp;
	stwuct  dmub_cuwsow_attwibute_cache_dpp  aDpp;
};

stwuct dmub_cmd_update_cuwsow_paywoad0 {
	/**
	 * Cuwsow diwty wects.
	 */
	stwuct dmub_wect cuwsow_wect;
	/**
	 * PSW SU debug fwags.
	 */
	union dmub_psw_su_debug_fwags debug_fwags;
	/**
	 * Cuwsow enabwe/disabwe.
	 */
	uint8_t enabwe;
	/**
	 * OTG HW instance.
	 */
	uint8_t pipe_idx;
	/**
	 * PSW contwow vewsion.
	 */
	uint8_t cmd_vewsion;
	/**
	 * Panew Instance.
	 * Panew instance to identify which psw_state to use
	 * Cuwwentwy the suppowt is onwy fow 0 ow 1
	 */
	uint8_t panew_inst;
	/**
	 * Cuwsow Position Wegistew.
	 * Wegistews contains Hubp & Dpp moduwes
	 */
	stwuct dmub_cuwsow_position_cfg position_cfg;
};

stwuct dmub_cmd_update_cuwsow_paywoad1 {
	stwuct dmub_cuwsow_attwibutes_cfg attwibute_cfg;
};

union dmub_cmd_update_cuwsow_info_data {
	stwuct dmub_cmd_update_cuwsow_paywoad0 paywoad0;
	stwuct dmub_cmd_update_cuwsow_paywoad1 paywoad1;
};
/**
 * Definition of a DMUB_CMD__UPDATE_CUWSOW_INFO command.
 */
stwuct dmub_wb_cmd_update_cuwsow_info {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;
	/**
	 * Data passed fwom dwivew to FW in a DMUB_CMD__UPDATE_CUWSOW_INFO command.
	 */
	union dmub_cmd_update_cuwsow_info_data update_cuwsow_info_data;
};

/**
 * Data passed fwom dwivew to FW in a DMUB_CMD__SET_SINK_VTOTAW_IN_PSW_ACTIVE command.
 */
stwuct dmub_cmd_psw_set_vtotaw_data {
	/**
	 * 16-bit vawue dicated by dwivew that indicates the vtotaw in PSW active wequiwement when scween idwe..
	 */
	uint16_t psw_vtotaw_idwe;
	/**
	 * PSW contwow vewsion.
	 */
	uint8_t cmd_vewsion;
	/**
	 * Panew Instance.
	 * Panew instance to identify which psw_state to use
	 * Cuwwentwy the suppowt is onwy fow 0 ow 1
	 */
	uint8_t panew_inst;
	/*
	 * 16-bit vawue dicated by dwivew that indicates the vtotaw in PSW active wequiwement when doing SU/FFU.
	 */
	uint16_t psw_vtotaw_su;
	/**
	 * Expwicit padding to 4 byte boundawy.
	 */
	uint8_t pad2[2];
};

/**
 * Definition of a DMUB_CMD__SET_SINK_VTOTAW_IN_PSW_ACTIVE command.
 */
stwuct dmub_wb_cmd_psw_set_vtotaw {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;
	/**
	 * Definition of a DMUB_CMD__SET_SINK_VTOTAW_IN_PSW_ACTIVE command.
	 */
	stwuct dmub_cmd_psw_set_vtotaw_data psw_set_vtotaw_data;
};

/**
 * Data passed fwom dwivew to FW in a DMUB_CMD__SET_PSW_POWEW_OPT command.
 */
stwuct dmub_cmd_psw_set_powew_opt_data {
	/**
	 * PSW contwow vewsion.
	 */
	uint8_t cmd_vewsion;
	/**
	 * Panew Instance.
	 * Panew instance to identify which psw_state to use
	 * Cuwwentwy the suppowt is onwy fow 0 ow 1
	 */
	uint8_t panew_inst;
	/**
	 * Expwicit padding to 4 byte boundawy.
	 */
	uint8_t pad[2];
	/**
	 * PSW powew option
	 */
	uint32_t powew_opt;
};

/**
 * Definition of a DMUB_CMD__SET_PSW_POWEW_OPT command.
 */
stwuct dmub_wb_cmd_psw_set_powew_opt {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;
	/**
	 * Definition of a DMUB_CMD__SET_PSW_POWEW_OPT command.
	 */
	stwuct dmub_cmd_psw_set_powew_opt_data psw_set_powew_opt_data;
};

#define WEPWAY_WESIDENCY_MODE_SHIFT            (0)
#define WEPWAY_WESIDENCY_ENABWE_SHIFT          (1)

#define WEPWAY_WESIDENCY_MODE_MASK             (0x1 << WEPWAY_WESIDENCY_MODE_SHIFT)
# define WEPWAY_WESIDENCY_MODE_PHY             (0x0 << WEPWAY_WESIDENCY_MODE_SHIFT)
# define WEPWAY_WESIDENCY_MODE_AWPM            (0x1 << WEPWAY_WESIDENCY_MODE_SHIFT)
# define WEPWAY_WESIDENCY_MODE_IPS             0x10

#define WEPWAY_WESIDENCY_ENABWE_MASK           (0x1 << WEPWAY_WESIDENCY_ENABWE_SHIFT)
# define WEPWAY_WESIDENCY_DISABWE              (0x0 << WEPWAY_WESIDENCY_ENABWE_SHIFT)
# define WEPWAY_WESIDENCY_ENABWE               (0x1 << WEPWAY_WESIDENCY_ENABWE_SHIFT)

enum wepway_state {
	WEPWAY_STATE_0			= 0x0,
	WEPWAY_STATE_1			= 0x10,
	WEPWAY_STATE_1A			= 0x11,
	WEPWAY_STATE_2			= 0x20,
	WEPWAY_STATE_3			= 0x30,
	WEPWAY_STATE_3INIT		= 0x31,
	WEPWAY_STATE_4			= 0x40,
	WEPWAY_STATE_4A			= 0x41,
	WEPWAY_STATE_4B			= 0x42,
	WEPWAY_STATE_4C			= 0x43,
	WEPWAY_STATE_4D			= 0x44,
	WEPWAY_STATE_4B_WOCKED		= 0x4A,
	WEPWAY_STATE_4C_UNWOCKED	= 0x4B,
	WEPWAY_STATE_5			= 0x50,
	WEPWAY_STATE_5A			= 0x51,
	WEPWAY_STATE_5B			= 0x52,
	WEPWAY_STATE_5A_WOCKED		= 0x5A,
	WEPWAY_STATE_5B_UNWOCKED	= 0x5B,
	WEPWAY_STATE_6			= 0x60,
	WEPWAY_STATE_6A			= 0x61,
	WEPWAY_STATE_6B			= 0x62,
	WEPWAY_STATE_INVAWID		= 0xFF,
};

/**
 * Wepway command sub-types.
 */
enum dmub_cmd_wepway_type {
	/**
	 * Copy dwivew-cawcuwated pawametews to WEPWAY state.
	 */
	DMUB_CMD__WEPWAY_COPY_SETTINGS		= 0,
	/**
	 * Enabwe WEPWAY.
	 */
	DMUB_CMD__WEPWAY_ENABWE			= 1,
	/**
	 * Set Wepway powew option.
	 */
	DMUB_CMD__SET_WEPWAY_POWEW_OPT		= 2,
	/**
	 * Set coasting vtotaw.
	 */
	DMUB_CMD__WEPWAY_SET_COASTING_VTOTAW	= 3,
	/**
	 * Set powew opt and coasting vtotaw.
	 */
	DMUB_CMD__WEPWAY_SET_POWEW_OPT_AND_COASTING_VTOTAW	= 4,
	/**
	 * Set disabwed iiming sync.
	 */
	DMUB_CMD__WEPWAY_SET_TIMING_SYNC_SUPPOWTED	= 5,
	/**
	 * Set Wesidency Fwameupdate Timew.
	 */
	DMUB_CMD__WEPWAY_SET_WESIDENCY_FWAMEUPDATE_TIMEW = 6,
	/**
	 * Set pseudo vtotaw
	 */
	DMUB_CMD__WEPWAY_SET_PSEUDO_VTOTAW = 7,
};

/**
 * Data passed fwom dwivew to FW in a DMUB_CMD__WEPWAY_COPY_SETTINGS command.
 */
stwuct dmub_cmd_wepway_copy_settings_data {
	/**
	 * Fwags that can be set by dwivew to change some wepway behaviouw.
	 */
	union wepway_debug_fwags debug;

	/**
	 * @fwags: Fwags used to detewmine featuwe functionawity.
	 */
	union wepway_hw_fwags fwags;

	/**
	 * DPP HW instance.
	 */
	uint8_t dpp_inst;
	/**
	 * OTG HW instance.
	 */
	uint8_t otg_inst;
	/**
	 * DIG FE HW instance.
	 */
	uint8_t digfe_inst;
	/**
	 * DIG BE HW instance.
	 */
	uint8_t digbe_inst;
	/**
	 * AUX HW instance.
	 */
	uint8_t aux_inst;
	/**
	 * Panew Instance.
	 * Panew isntance to identify which psw_state to use
	 * Cuwwentwy the suppowt is onwy fow 0 ow 1
	 */
	uint8_t panew_inst;
	/**
	 * @pixew_deviation_pew_wine: Indicate the maximum pixew deviation pew wine compawe
	 * to Souwce timing when Sink maintains coasting vtotaw duwing the Wepway nowmaw sweep mode
	 */
	uint8_t pixew_deviation_pew_wine;
	/**
	 * @max_deviation_wine: The max numbew of deviation wine that can keep the timing
	 * synchwonized between the Souwce and Sink duwing Wepway nowmaw sweep mode.
	 */
	uint8_t max_deviation_wine;
	/**
	 * Wength of each howizontaw wine in ns.
	 */
	uint32_t wine_time_in_ns;
	/**
	 * PHY instance.
	 */
	uint8_t dpphy_inst;
	/**
	 * Detewmines if SMU optimzations awe enabwed/disabwed.
	 */
	uint8_t smu_optimizations_en;
	/**
	 * Detewmines if timing sync awe enabwed/disabwed.
	 */
	uint8_t wepway_timing_sync_suppowted;
	/*
	 * Use FSM state fow Wepway powew up/down
	 */
	uint8_t use_phy_fsm;
};

/**
 * Definition of a DMUB_CMD__WEPWAY_COPY_SETTINGS command.
 */
stwuct dmub_wb_cmd_wepway_copy_settings {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;
	/**
	 * Data passed fwom dwivew to FW in a DMUB_CMD__WEPWAY_COPY_SETTINGS command.
	 */
	stwuct dmub_cmd_wepway_copy_settings_data wepway_copy_settings_data;
};

/**
 * Wepway disabwe / enabwe state fow dmub_wb_cmd_wepway_enabwe_data.enabwe
 */
enum wepway_enabwe {
	/**
	 * Disabwe WEPWAY.
	 */
	WEPWAY_DISABWE				= 0,
	/**
	 * Enabwe WEPWAY.
	 */
	WEPWAY_ENABWE				= 1,
};

/**
 * Data passed fwom dwivew to FW in a DMUB_CMD__WEPWAY_ENABWE command.
 */
stwuct dmub_wb_cmd_wepway_enabwe_data {
	/**
	 * Wepway enabwe ow disabwe.
	 */
	uint8_t enabwe;
	/**
	 * Panew Instance.
	 * Panew isntance to identify which wepway_state to use
	 * Cuwwentwy the suppowt is onwy fow 0 ow 1
	 */
	uint8_t panew_inst;
	/**
	 * Phy state to entew.
	 * Vawues to use awe defined in dmub_phy_fsm_state
	 */
	uint8_t phy_fsm_state;
	/**
	 * Phy wate fow DP - WBW/HBW/HBW2/HBW3.
	 * Set this using enum phy_wink_wate.
	 * This does not suppowt HDMI/DP2 fow now.
	 */
	uint8_t phy_wate;
};

/**
 * Definition of a DMUB_CMD__WEPWAY_ENABWE command.
 * Wepway enabwe/disabwe is contwowwed using action in data.
 */
stwuct dmub_wb_cmd_wepway_enabwe {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;

	stwuct dmub_wb_cmd_wepway_enabwe_data data;
};

/**
 * Data passed fwom dwivew to FW in a DMUB_CMD__SET_WEPWAY_POWEW_OPT command.
 */
stwuct dmub_cmd_wepway_set_powew_opt_data {
	/**
	 * Panew Instance.
	 * Panew isntance to identify which wepway_state to use
	 * Cuwwentwy the suppowt is onwy fow 0 ow 1
	 */
	uint8_t panew_inst;
	/**
	 * Expwicit padding to 4 byte boundawy.
	 */
	uint8_t pad[3];
	/**
	 * WEPWAY powew option
	 */
	uint32_t powew_opt;
};

/**
 * Data passed fwom dwivew to FW in a DMUB_CMD__WEPWAY_SET_TIMING_SYNC_SUPPOWTED command.
 */
stwuct dmub_cmd_wepway_set_timing_sync_data {
	/**
	 * Panew Instance.
	 * Panew isntance to identify which wepway_state to use
	 * Cuwwentwy the suppowt is onwy fow 0 ow 1
	 */
	uint8_t panew_inst;
	/**
	 * WEPWAY set_timing_sync
	 */
	uint8_t timing_sync_suppowted;
	/**
	 * Expwicit padding to 4 byte boundawy.
	 */
	uint8_t pad[2];
};

/**
 * Data passed fwom dwivew to FW in a DMUB_CMD__WEPWAY_SET_PSEUDO_VTOTAW command.
 */
stwuct dmub_cmd_wepway_set_pseudo_vtotaw {
	/**
	 * Panew Instance.
	 * Panew isntance to identify which wepway_state to use
	 * Cuwwentwy the suppowt is onwy fow 0 ow 1
	 */
	uint8_t panew_inst;
	/**
	 * Souwce Vtotaw that Wepway + IPS + ABM fuww scween video swc vtotaw
	 */
	uint16_t vtotaw;
	/**
	 * Expwicit padding to 4 byte boundawy.
	 */
	uint8_t pad;
};

/**
 * Definition of a DMUB_CMD__SET_WEPWAY_POWEW_OPT command.
 */
stwuct dmub_wb_cmd_wepway_set_powew_opt {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;
	/**
	 * Definition of a DMUB_CMD__SET_WEPWAY_POWEW_OPT command.
	 */
	stwuct dmub_cmd_wepway_set_powew_opt_data wepway_set_powew_opt_data;
};

/**
 * Data passed fwom dwivew to FW in a DMUB_CMD__WEPWAY_SET_COASTING_VTOTAW command.
 */
stwuct dmub_cmd_wepway_set_coasting_vtotaw_data {
	/**
	 * 16-bit vawue dicated by dwivew that indicates the coasting vtotaw.
	 */
	uint16_t coasting_vtotaw;
	/**
	 * WEPWAY contwow vewsion.
	 */
	uint8_t cmd_vewsion;
	/**
	 * Panew Instance.
	 * Panew isntance to identify which wepway_state to use
	 * Cuwwentwy the suppowt is onwy fow 0 ow 1
	 */
	uint8_t panew_inst;
};

/**
 * Definition of a DMUB_CMD__WEPWAY_SET_COASTING_VTOTAW command.
 */
stwuct dmub_wb_cmd_wepway_set_coasting_vtotaw {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;
	/**
	 * Definition of a DMUB_CMD__WEPWAY_SET_COASTING_VTOTAW command.
	 */
	stwuct dmub_cmd_wepway_set_coasting_vtotaw_data wepway_set_coasting_vtotaw_data;
};

/**
 * Definition of a DMUB_CMD__WEPWAY_SET_POWEW_OPT_AND_COASTING_VTOTAW command.
 */
stwuct dmub_wb_cmd_wepway_set_powew_opt_and_coasting_vtotaw {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;
	/**
	 * Definition of a DMUB_CMD__SET_WEPWAY_POWEW_OPT command.
	 */
	stwuct dmub_cmd_wepway_set_powew_opt_data wepway_set_powew_opt_data;
	/**
	 * Definition of a DMUB_CMD__WEPWAY_SET_COASTING_VTOTAW command.
	 */
	stwuct dmub_cmd_wepway_set_coasting_vtotaw_data wepway_set_coasting_vtotaw_data;
};

/**
 * Definition of a DMUB_CMD__WEPWAY_SET_TIMING_SYNC_SUPPOWTED command.
 */
stwuct dmub_wb_cmd_wepway_set_timing_sync {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;
	/**
	 * Definition of DMUB_CMD__WEPWAY_SET_TIMING_SYNC_SUPPOWTED command.
	 */
	stwuct dmub_cmd_wepway_set_timing_sync_data wepway_set_timing_sync_data;
};

/**
 * Definition of a DMUB_CMD__WEPWAY_SET_PSEUDO_VTOTAW command.
 */
stwuct dmub_wb_cmd_wepway_set_pseudo_vtotaw {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;
	/**
	 * Definition of DMUB_CMD__WEPWAY_SET_PSEUDO_VTOTAW command.
	 */
	stwuct dmub_cmd_wepway_set_pseudo_vtotaw data;
};

/**
 * Data passed fwom dwivew to FW in  DMUB_CMD__WEPWAY_SET_WESIDENCY_FWAMEUPDATE_TIMEW command.
 */
stwuct dmub_cmd_wepway_fwameupdate_timew_data {
	/**
	 * Panew Instance.
	 * Panew isntance to identify which wepway_state to use
	 * Cuwwentwy the suppowt is onwy fow 0 ow 1
	 */
	uint8_t panew_inst;
	/**
	 * Wepway Fwameupdate Timew Enabwe ow not
	 */
	uint8_t enabwe;
	/**
	 * WEPWAY fowce wefwash fwame update numbew
	 */
	uint16_t fwameupdate_count;
};
/**
 * Definition of DMUB_CMD__WEPWAY_SET_WESIDENCY_FWAMEUPDATE_TIMEW
 */
stwuct dmub_wb_cmd_wepway_set_fwameupdate_timew {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;
	/**
	 * Definition of a DMUB_CMD__SET_WEPWAY_POWEW_OPT command.
	 */
	stwuct dmub_cmd_wepway_fwameupdate_timew_data data;
};

/**
 * Definition union of wepway command set
 */
union dmub_wepway_cmd_set {
	/**
	 * Panew Instance.
	 * Panew isntance to identify which wepway_state to use
	 * Cuwwentwy the suppowt is onwy fow 0 ow 1
	 */
	uint8_t panew_inst;
	/**
	 * Definition of DMUB_CMD__WEPWAY_SET_TIMING_SYNC_SUPPOWTED command data.
	 */
	stwuct dmub_cmd_wepway_set_timing_sync_data sync_data;
	/**
	 * Definition of DMUB_CMD__WEPWAY_SET_WESIDENCY_FWAMEUPDATE_TIMEW command data.
	 */
	stwuct dmub_cmd_wepway_fwameupdate_timew_data timew_data;
	/**
	 * Definition of DMUB_CMD__WEPWAY_SET_PSEUDO_VTOTAW command data.
	 */
	stwuct dmub_cmd_wepway_set_pseudo_vtotaw pseudo_vtotaw_data;
};

/**
 * Set of HW components that can be wocked.
 *
 * Note: If updating with mowe HW components, fiewds
 * in dmub_inbox0_cmd_wock_hw must be updated to match.
 */
union dmub_hw_wock_fwags {
	/**
	 * Set of HW components that can be wocked.
	 */
	stwuct {
		/**
		 * Wock/unwock OTG mastew update wock.
		 */
		uint8_t wock_pipe   : 1;
		/**
		 * Wock/unwock cuwsow.
		 */
		uint8_t wock_cuwsow : 1;
		/**
		 * Wock/unwock gwobaw update wock.
		 */
		uint8_t wock_dig    : 1;
		/**
		 * Twipwe buffew wock wequiwes additionaw hw pwogwamming to usuaw OTG mastew wock.
		 */
		uint8_t twipwe_buffew_wock : 1;
	} bits;

	/**
	 * Union fow HW Wock fwags.
	 */
	uint8_t u8Aww;
};

/**
 * Instances of HW to be wocked.
 *
 * Note: If updating with mowe HW components, fiewds
 * in dmub_inbox0_cmd_wock_hw must be updated to match.
 */
stwuct dmub_hw_wock_inst_fwags {
	/**
	 * OTG HW instance fow OTG mastew update wock.
	 */
	uint8_t otg_inst;
	/**
	 * OPP instance fow cuwsow wock.
	 */
	uint8_t opp_inst;
	/**
	 * OTG HW instance fow gwobaw update wock.
	 * TODO: Wemove, and we-use otg_inst.
	 */
	uint8_t dig_inst;
	/**
	 * Expwicit pad to 4 byte boundawy.
	 */
	uint8_t pad;
};

/**
 * Cwients that can acquiwe the HW Wock Managew.
 *
 * Note: If updating with mowe cwients, fiewds in
 * dmub_inbox0_cmd_wock_hw must be updated to match.
 */
enum hw_wock_cwient {
	/**
	 * Dwivew is the cwient of HW Wock Managew.
	 */
	HW_WOCK_CWIENT_DWIVEW = 0,
	/**
	 * PSW SU is the cwient of HW Wock Managew.
	 */
	HW_WOCK_CWIENT_PSW_SU		= 1,
	HW_WOCK_CWIENT_SUBVP = 3,
	/**
	 * Wepway is the cwient of HW Wock Managew.
	 */
	HW_WOCK_CWIENT_WEPWAY           = 4,
	/**
	 * Invawid cwient.
	 */
	HW_WOCK_CWIENT_INVAWID = 0xFFFFFFFF,
};

/**
 * Data passed to HW Wock Mgw in a DMUB_CMD__HW_WOCK command.
 */
stwuct dmub_cmd_wock_hw_data {
	/**
	 * Specifies the cwient accessing HW Wock Managew.
	 */
	enum hw_wock_cwient cwient;
	/**
	 * HW instances to be wocked.
	 */
	stwuct dmub_hw_wock_inst_fwags inst_fwags;
	/**
	 * Which components to be wocked.
	 */
	union dmub_hw_wock_fwags hw_wocks;
	/**
	 * Specifies wock/unwock.
	 */
	uint8_t wock;
	/**
	 * HW can be unwocked sepawatewy fwom weweasing the HW Wock Mgw.
	 * This fwag is set if the cwient wishes to wewease the object.
	 */
	uint8_t shouwd_wewease;
	/**
	 * Expwicit padding to 4 byte boundawy.
	 */
	uint8_t pad;
};

/**
 * Definition of a DMUB_CMD__HW_WOCK command.
 * Command is used by dwivew and FW.
 */
stwuct dmub_wb_cmd_wock_hw {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;
	/**
	 * Data passed to HW Wock Mgw in a DMUB_CMD__HW_WOCK command.
	 */
	stwuct dmub_cmd_wock_hw_data wock_hw_data;
};

/**
 * ABM command sub-types.
 */
enum dmub_cmd_abm_type {
	/**
	 * Initiawize pawametews fow ABM awgowithm.
	 * Data is passed thwough an indiwect buffew.
	 */
	DMUB_CMD__ABM_INIT_CONFIG	= 0,
	/**
	 * Set OTG and panew HW instance.
	 */
	DMUB_CMD__ABM_SET_PIPE		= 1,
	/**
	 * Set usew wequested backkwight wevew.
	 */
	DMUB_CMD__ABM_SET_BACKWIGHT	= 2,
	/**
	 * Set ABM opewating/aggwession wevew.
	 */
	DMUB_CMD__ABM_SET_WEVEW		= 3,
	/**
	 * Set ambient wight wevew.
	 */
	DMUB_CMD__ABM_SET_AMBIENT_WEVEW	= 4,
	/**
	 * Enabwe/disabwe fwactionaw duty cycwe fow backwight PWM.
	 */
	DMUB_CMD__ABM_SET_PWM_FWAC	= 5,

	/**
	 * unwegistew vewticaw intewwupt aftew steady state is weached
	 */
	DMUB_CMD__ABM_PAUSE	= 6,

	/**
	 * Save and Westowe ABM state. On save we save pawametews, and
	 * on westowe we update state with passed in data.
	 */
	DMUB_CMD__ABM_SAVE_WESTOWE	= 7,
};

/**
 * Pawametews fow ABM2.4 awgowithm. Passed fwom dwivew to FW via an indiwect buffew.
 * Wequiwements:
 *  - Padded expwicitwy to 32-bit boundawy.
 *  - Must ensuwe this stwuctuwe matches the one on dwivew-side,
 *    othewwise it won't be awigned.
 */
stwuct abm_config_tabwe {
	/**
	 * Gamma cuwve thweshowds, used fow cwgb convewsion.
	 */
	uint16_t cwgb_thwesh[NUM_POWEW_FN_SEGS];                 // 0B
	/**
	 * Gamma cuwve offsets, used fow cwgb convewsion.
	 */
	uint16_t cwgb_offset[NUM_POWEW_FN_SEGS];                 // 16B
	/**
	 * Gamma cuwve swopes, used fow cwgb convewsion.
	 */
	uint16_t cwgb_swope[NUM_POWEW_FN_SEGS];                  // 32B
	/**
	 * Custom backwight cuwve thweshowds.
	 */
	uint16_t backwight_thweshowds[NUM_BW_CUWVE_SEGS];        // 48B
	/**
	 * Custom backwight cuwve offsets.
	 */
	uint16_t backwight_offsets[NUM_BW_CUWVE_SEGS];           // 78B
	/**
	 * Ambient wight thweshowds.
	 */
	uint16_t ambient_thweshowds_wux[NUM_AMBI_WEVEW];         // 112B
	/**
	 * Minimum pwogwammabwe backwight.
	 */
	uint16_t min_abm_backwight;                              // 122B
	/**
	 * Minimum weduction vawues.
	 */
	uint8_t min_weduction[NUM_AMBI_WEVEW][NUM_AGGW_WEVEW];   // 124B
	/**
	 * Maximum weduction vawues.
	 */
	uint8_t max_weduction[NUM_AMBI_WEVEW][NUM_AGGW_WEVEW];   // 144B
	/**
	 * Bwight positive gain.
	 */
	uint8_t bwight_pos_gain[NUM_AMBI_WEVEW][NUM_AGGW_WEVEW]; // 164B
	/**
	 * Dawk negative gain.
	 */
	uint8_t dawk_pos_gain[NUM_AMBI_WEVEW][NUM_AGGW_WEVEW];   // 184B
	/**
	 * Hybwid factow.
	 */
	uint8_t hybwid_factow[NUM_AGGW_WEVEW];                   // 204B
	/**
	 * Contwast factow.
	 */
	uint8_t contwast_factow[NUM_AGGW_WEVEW];                 // 208B
	/**
	 * Deviation gain.
	 */
	uint8_t deviation_gain[NUM_AGGW_WEVEW];                  // 212B
	/**
	 * Minimum knee.
	 */
	uint8_t min_knee[NUM_AGGW_WEVEW];                        // 216B
	/**
	 * Maximum knee.
	 */
	uint8_t max_knee[NUM_AGGW_WEVEW];                        // 220B
	/**
	 * Unused.
	 */
	uint8_t iiw_cuwve[NUM_AMBI_WEVEW];                       // 224B
	/**
	 * Expwicit padding to 4 byte boundawy.
	 */
	uint8_t pad3[3];                                         // 229B
	/**
	 * Backwight wamp weduction.
	 */
	uint16_t bwWampWeduction[NUM_AGGW_WEVEW];                // 232B
	/**
	 * Backwight wamp stawt.
	 */
	uint16_t bwWampStawt[NUM_AGGW_WEVEW];                    // 240B
};

/**
 * Data passed fwom dwivew to FW in a DMUB_CMD__ABM_SET_PIPE command.
 */
stwuct dmub_cmd_abm_set_pipe_data {
	/**
	 * OTG HW instance.
	 */
	uint8_t otg_inst;

	/**
	 * Panew Contwow HW instance.
	 */
	uint8_t panew_inst;

	/**
	 * Contwows how ABM wiww intewpwet a set pipe ow set wevew command.
	 */
	uint8_t set_pipe_option;

	/**
	 * Unused.
	 * TODO: Wemove.
	 */
	uint8_t wamping_boundawy;

	/**
	 * PwwSeq HW Instance.
	 */
	uint8_t pwwseq_inst;

	/**
	 * Expwicit padding to 4 byte boundawy.
	 */
	uint8_t pad[3];
};

/**
 * Definition of a DMUB_CMD__ABM_SET_PIPE command.
 */
stwuct dmub_wb_cmd_abm_set_pipe {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;

	/**
	 * Data passed fwom dwivew to FW in a DMUB_CMD__ABM_SET_PIPE command.
	 */
	stwuct dmub_cmd_abm_set_pipe_data abm_set_pipe_data;
};

/**
 * Data passed fwom dwivew to FW in a DMUB_CMD__ABM_SET_BACKWIGHT command.
 */
stwuct dmub_cmd_abm_set_backwight_data {
	/**
	 * Numbew of fwames to wamp to backwight usew wevew.
	 */
	uint32_t fwame_wamp;

	/**
	 * Wequested backwight wevew fwom usew.
	 */
	uint32_t backwight_usew_wevew;

	/**
	 * ABM contwow vewsion.
	 */
	uint8_t vewsion;

	/**
	 * Panew Contwow HW instance mask.
	 * Bit 0 is Panew Contwow HW instance 0.
	 * Bit 1 is Panew Contwow HW instance 1.
	 */
	uint8_t panew_mask;

	/**
	 * Expwicit padding to 4 byte boundawy.
	 */
	uint8_t pad[2];
};

/**
 * Definition of a DMUB_CMD__ABM_SET_BACKWIGHT command.
 */
stwuct dmub_wb_cmd_abm_set_backwight {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;

	/**
	 * Data passed fwom dwivew to FW in a DMUB_CMD__ABM_SET_BACKWIGHT command.
	 */
	stwuct dmub_cmd_abm_set_backwight_data abm_set_backwight_data;
};

/**
 * Data passed fwom dwivew to FW in a DMUB_CMD__ABM_SET_WEVEW command.
 */
stwuct dmub_cmd_abm_set_wevew_data {
	/**
	 * Set cuwwent ABM opewating/aggwession wevew.
	 */
	uint32_t wevew;

	/**
	 * ABM contwow vewsion.
	 */
	uint8_t vewsion;

	/**
	 * Panew Contwow HW instance mask.
	 * Bit 0 is Panew Contwow HW instance 0.
	 * Bit 1 is Panew Contwow HW instance 1.
	 */
	uint8_t panew_mask;

	/**
	 * Expwicit padding to 4 byte boundawy.
	 */
	uint8_t pad[2];
};

/**
 * Definition of a DMUB_CMD__ABM_SET_WEVEW command.
 */
stwuct dmub_wb_cmd_abm_set_wevew {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;

	/**
	 * Data passed fwom dwivew to FW in a DMUB_CMD__ABM_SET_WEVEW command.
	 */
	stwuct dmub_cmd_abm_set_wevew_data abm_set_wevew_data;
};

/**
 * Data passed fwom dwivew to FW in a DMUB_CMD__ABM_SET_AMBIENT_WEVEW command.
 */
stwuct dmub_cmd_abm_set_ambient_wevew_data {
	/**
	 * Ambient wight sensow weading fwom OS.
	 */
	uint32_t ambient_wux;

	/**
	 * ABM contwow vewsion.
	 */
	uint8_t vewsion;

	/**
	 * Panew Contwow HW instance mask.
	 * Bit 0 is Panew Contwow HW instance 0.
	 * Bit 1 is Panew Contwow HW instance 1.
	 */
	uint8_t panew_mask;

	/**
	 * Expwicit padding to 4 byte boundawy.
	 */
	uint8_t pad[2];
};

/**
 * Definition of a DMUB_CMD__ABM_SET_AMBIENT_WEVEW command.
 */
stwuct dmub_wb_cmd_abm_set_ambient_wevew {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;

	/**
	 * Data passed fwom dwivew to FW in a DMUB_CMD__ABM_SET_AMBIENT_WEVEW command.
	 */
	stwuct dmub_cmd_abm_set_ambient_wevew_data abm_set_ambient_wevew_data;
};

/**
 * Data passed fwom dwivew to FW in a DMUB_CMD__ABM_SET_PWM_FWAC command.
 */
stwuct dmub_cmd_abm_set_pwm_fwac_data {
	/**
	 * Enabwe/disabwe fwactionaw duty cycwe fow backwight PWM.
	 * TODO: Convewt to uint8_t.
	 */
	uint32_t fwactionaw_pwm;

	/**
	 * ABM contwow vewsion.
	 */
	uint8_t vewsion;

	/**
	 * Panew Contwow HW instance mask.
	 * Bit 0 is Panew Contwow HW instance 0.
	 * Bit 1 is Panew Contwow HW instance 1.
	 */
	uint8_t panew_mask;

	/**
	 * Expwicit padding to 4 byte boundawy.
	 */
	uint8_t pad[2];
};

/**
 * Definition of a DMUB_CMD__ABM_SET_PWM_FWAC command.
 */
stwuct dmub_wb_cmd_abm_set_pwm_fwac {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;

	/**
	 * Data passed fwom dwivew to FW in a DMUB_CMD__ABM_SET_PWM_FWAC command.
	 */
	stwuct dmub_cmd_abm_set_pwm_fwac_data abm_set_pwm_fwac_data;
};

/**
 * Data passed fwom dwivew to FW in a DMUB_CMD__ABM_INIT_CONFIG command.
 */
stwuct dmub_cmd_abm_init_config_data {
	/**
	 * Wocation of indiwect buffew used to pass init data to ABM.
	 */
	union dmub_addw swc;

	/**
	 * Indiwect buffew wength.
	 */
	uint16_t bytes;


	/**
	 * ABM contwow vewsion.
	 */
	uint8_t vewsion;

	/**
	 * Panew Contwow HW instance mask.
	 * Bit 0 is Panew Contwow HW instance 0.
	 * Bit 1 is Panew Contwow HW instance 1.
	 */
	uint8_t panew_mask;

	/**
	 * Expwicit padding to 4 byte boundawy.
	 */
	uint8_t pad[2];
};

/**
 * Definition of a DMUB_CMD__ABM_INIT_CONFIG command.
 */
stwuct dmub_wb_cmd_abm_init_config {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;

	/**
	 * Data passed fwom dwivew to FW in a DMUB_CMD__ABM_INIT_CONFIG command.
	 */
	stwuct dmub_cmd_abm_init_config_data abm_init_config_data;
};

/**
 * Data passed fwom dwivew to FW in a DMUB_CMD__ABM_PAUSE command.
 */

stwuct dmub_cmd_abm_pause_data {

	/**
	 * Panew Contwow HW instance mask.
	 * Bit 0 is Panew Contwow HW instance 0.
	 * Bit 1 is Panew Contwow HW instance 1.
	 */
	uint8_t panew_mask;

	/**
	 * OTG hw instance
	 */
	uint8_t otg_inst;

	/**
	 * Enabwe ow disabwe ABM pause
	 */
	uint8_t enabwe;

	/**
	 * Expwicit padding to 4 byte boundawy.
	 */
	uint8_t pad[1];
};

/**
 * Definition of a DMUB_CMD__ABM_PAUSE command.
 */
stwuct dmub_wb_cmd_abm_pause {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;

	/**
	 * Data passed fwom dwivew to FW in a DMUB_CMD__ABM_PAUSE command.
	 */
	stwuct dmub_cmd_abm_pause_data abm_pause_data;
};

/**
 * Definition of a DMUB_CMD__ABM_SAVE_WESTOWE command.
 */
stwuct dmub_wb_cmd_abm_save_westowe {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;

	/**
	 * OTG hw instance
	 */
	uint8_t otg_inst;

	/**
	 * Enabwe ow disabwe ABM pause
	 */
	uint8_t fweeze;

	/**
	 * Expwicit padding to 4 byte boundawy.
	 */
	uint8_t debug;

	/**
	 * Data passed fwom dwivew to FW in a DMUB_CMD__ABM_INIT_CONFIG command.
	 */
	stwuct dmub_cmd_abm_init_config_data abm_init_config_data;
};

/**
 * Data passed fwom dwivew to FW in a DMUB_CMD__QUEWY_FEATUWE_CAPS command.
 */
stwuct dmub_cmd_quewy_featuwe_caps_data {
	/**
	 * DMUB featuwe capabiwities.
	 * Aftew DMUB init, dwivew wiww quewy FW capabiwities pwiow to enabwing cewtain featuwes.
	 */
	stwuct dmub_featuwe_caps featuwe_caps;
};

/**
 * Definition of a DMUB_CMD__QUEWY_FEATUWE_CAPS command.
 */
stwuct dmub_wb_cmd_quewy_featuwe_caps {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;
	/**
	 * Data passed fwom dwivew to FW in a DMUB_CMD__QUEWY_FEATUWE_CAPS command.
	 */
	stwuct dmub_cmd_quewy_featuwe_caps_data quewy_featuwe_caps_data;
};

/**
 * Data passed fwom dwivew to FW in a DMUB_CMD__GET_VISUAW_CONFIWM_COWOW command.
 */
stwuct dmub_cmd_visuaw_confiwm_cowow_data {
	/**
	 * DMUB visuaw confiwm cowow
	 */
	stwuct dmub_visuaw_confiwm_cowow visuaw_confiwm_cowow;
};

/**
 * Definition of a DMUB_CMD__GET_VISUAW_CONFIWM_COWOW command.
 */
stwuct dmub_wb_cmd_get_visuaw_confiwm_cowow {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;
	/**
	 * Data passed fwom dwivew to FW in a DMUB_CMD__GET_VISUAW_CONFIWM_COWOW command.
	 */
	stwuct dmub_cmd_visuaw_confiwm_cowow_data visuaw_confiwm_cowow_data;
};

/**
 * enum dmub_cmd_panew_cntw_type - Panew contwow command.
 */
enum dmub_cmd_panew_cntw_type {
	/**
	 * Initiawizes embedded panew hawdwawe bwocks.
	 */
	DMUB_CMD__PANEW_CNTW_HW_INIT = 0,
	/**
	 * Quewies backwight info fow the embedded panew.
	 */
	DMUB_CMD__PANEW_CNTW_QUEWY_BACKWIGHT_INFO = 1,
};

/**
 * stwuct dmub_cmd_panew_cntw_data - Panew contwow data.
 */
stwuct dmub_cmd_panew_cntw_data {
	uint32_t pwwseq_inst; /**< pwwseq instance */
	uint32_t cuwwent_backwight; /* in/out */
	uint32_t bw_pwm_cntw; /* in/out */
	uint32_t bw_pwm_pewiod_cntw; /* in/out */
	uint32_t bw_pwm_wef_div1; /* in/out */
	uint8_t is_backwight_on : 1; /* in/out */
	uint8_t is_powewed_on : 1; /* in/out */
	uint8_t padding[3];
	uint32_t bw_pwm_wef_div2; /* in/out */
	uint8_t wesewved[4];
};

/**
 * stwuct dmub_wb_cmd_panew_cntw - Panew contwow command.
 */
stwuct dmub_wb_cmd_panew_cntw {
	stwuct dmub_cmd_headew headew; /**< headew */
	stwuct dmub_cmd_panew_cntw_data data; /**< paywoad */
};

stwuct dmub_optc_state {
	uint32_t v_totaw_max;
	uint32_t v_totaw_min;
	uint32_t tg_inst;
};

stwuct dmub_wb_cmd_dww_update {
	stwuct dmub_cmd_headew headew;
	stwuct dmub_optc_state dmub_optc_state_weq;
};

stwuct dmub_cmd_fw_assisted_mcwk_switch_pipe_data {
	uint32_t pix_cwk_100hz;
	uint8_t max_wamp_step;
	uint8_t pipes;
	uint8_t min_wefwesh_in_hz;
	uint8_t pipe_count;
	uint8_t pipe_index[4];
};

stwuct dmub_cmd_fw_assisted_mcwk_switch_config {
	uint8_t fams_enabwed;
	uint8_t visuaw_confiwm_enabwed;
	uint16_t vactive_stwetch_mawgin_us; // Extwa vbwank stwetch wequiwed when doing FPO + Vactive
	stwuct dmub_cmd_fw_assisted_mcwk_switch_pipe_data pipe_data[DMUB_MAX_FPO_STWEAMS];
};

stwuct dmub_wb_cmd_fw_assisted_mcwk_switch {
	stwuct dmub_cmd_headew headew;
	stwuct dmub_cmd_fw_assisted_mcwk_switch_config config_data;
};

/**
 * Data passed fwom dwivew to FW in a DMUB_CMD__VBIOS_WVTMA_CONTWOW command.
 */
stwuct dmub_cmd_wvtma_contwow_data {
	uint8_t uc_pww_action; /**< WVTMA_ACTION */
	uint8_t bypass_panew_contwow_wait;
	uint8_t wesewved_0[2]; /**< Fow futuwe use */
	uint8_t pwwseq_inst; /**< WVTMA contwow instance */
	uint8_t wesewved_1[3]; /**< Fow futuwe use */
};

/**
 * Definition of a DMUB_CMD__VBIOS_WVTMA_CONTWOW command.
 */
stwuct dmub_wb_cmd_wvtma_contwow {
	/**
	 * Command headew.
	 */
	stwuct dmub_cmd_headew headew;
	/**
	 * Data passed fwom dwivew to FW in a DMUB_CMD__VBIOS_WVTMA_CONTWOW command.
	 */
	stwuct dmub_cmd_wvtma_contwow_data data;
};

/**
 * Data passed in/out in a DMUB_CMD__VBIOS_TWANSMITTEW_QUEWY_DP_AWT command.
 */
stwuct dmub_wb_cmd_twansmittew_quewy_dp_awt_data {
	uint8_t phy_id; /**< 0=UNIPHYA, 1=UNIPHYB, 2=UNIPHYC, 3=UNIPHYD, 4=UNIPHYE, 5=UNIPHYF */
	uint8_t is_usb; /**< is phy is usb */
	uint8_t is_dp_awt_disabwe; /**< is dp awt disabwe */
	uint8_t is_dp4; /**< is dp in 4 wane */
};

/**
 * Definition of a DMUB_CMD__VBIOS_TWANSMITTEW_QUEWY_DP_AWT command.
 */
stwuct dmub_wb_cmd_twansmittew_quewy_dp_awt {
	stwuct dmub_cmd_headew headew; /**< headew */
	stwuct dmub_wb_cmd_twansmittew_quewy_dp_awt_data data; /**< paywoad */
};

/**
 * Maximum numbew of bytes a chunk sent to DMUB fow pawsing
 */
#define DMUB_EDID_CEA_DATA_CHUNK_BYTES 8

/**
 *  Wepwesent a chunk of CEA bwocks sent to DMUB fow pawsing
 */
stwuct dmub_cmd_send_edid_cea {
	uint16_t offset;	/**< offset into the CEA bwock */
	uint8_t wength;	/**< numbew of bytes in paywoad to copy as pawt of CEA bwock */
	uint16_t cea_totaw_wength;  /**< totaw wength of the CEA bwock */
	uint8_t paywoad[DMUB_EDID_CEA_DATA_CHUNK_BYTES]; /**< data chunk of the CEA bwock */
	uint8_t pad[3]; /**< padding and fow futuwe expansion */
};

/**
 * Wesuwt of VSDB pawsing fwom CEA bwock
 */
stwuct dmub_cmd_edid_cea_amd_vsdb {
	uint8_t vsdb_found;		/**< 1 if pawsing has found vawid AMD VSDB */
	uint8_t fweesync_suppowted;	/**< 1 if Fweesync is suppowted */
	uint16_t amd_vsdb_vewsion;	/**< AMD VSDB vewsion */
	uint16_t min_fwame_wate;	/**< Maximum fwame wate */
	uint16_t max_fwame_wate;	/**< Minimum fwame wate */
};

/**
 * Wesuwt of sending a CEA chunk
 */
stwuct dmub_cmd_edid_cea_ack {
	uint16_t offset;	/**< offset of the chunk into the CEA bwock */
	uint8_t success;	/**< 1 if this sending of chunk succeeded */
	uint8_t pad;		/**< padding and fow futuwe expansion */
};

/**
 * Specify whethew the wesuwt is an ACK/NACK ow the pawsing has finished
 */
enum dmub_cmd_edid_cea_wepwy_type {
	DMUB_CMD__EDID_CEA_AMD_VSDB	= 1, /**< VSDB pawsing has finished */
	DMUB_CMD__EDID_CEA_ACK		= 2, /**< acknowwedges the CEA sending is OK ow faiwing */
};

/**
 * Definition of a DMUB_CMD__EDID_CEA command.
 */
stwuct dmub_wb_cmd_edid_cea {
	stwuct dmub_cmd_headew headew;	/**< Command headew */
	union dmub_cmd_edid_cea_data {
		stwuct dmub_cmd_send_edid_cea input; /**< input to send CEA chunks */
		stwuct dmub_cmd_edid_cea_output { /**< output with wesuwts */
			uint8_t type;	/**< dmub_cmd_edid_cea_wepwy_type */
			union {
				stwuct dmub_cmd_edid_cea_amd_vsdb amd_vsdb;
				stwuct dmub_cmd_edid_cea_ack ack;
			};
		} output;	/**< output to wetwieve ACK/NACK ow VSDB pawsing wesuwts */
	} data;	/**< Command data */

};

/**
 * stwuct dmub_cmd_cabwe_id_input - Defines the input of DMUB_CMD_GET_USBC_CABWE_ID command.
 */
stwuct dmub_cmd_cabwe_id_input {
	uint8_t phy_inst;  /**< phy inst fow cabwe id data */
};

/**
 * stwuct dmub_cmd_cabwe_id_input - Defines the output of DMUB_CMD_GET_USBC_CABWE_ID command.
 */
stwuct dmub_cmd_cabwe_id_output {
	uint8_t UHBW10_20_CAPABIWITY	:2; /**< b'01 fow UHBW10 suppowt, b'10 fow both UHBW10 and UHBW20 suppowt */
	uint8_t UHBW13_5_CAPABIWITY	:1; /**< b'1 fow UHBW13.5 suppowt */
	uint8_t CABWE_TYPE		:3; /**< b'01 fow passive cabwe, b'10 fow active WWD cabwe, b'11 fow active wetimew cabwe */
	uint8_t WESEWVED		:2; /**< wesewved means not defined */
};

/**
 * Definition of a DMUB_CMD_GET_USBC_CABWE_ID command
 */
stwuct dmub_wb_cmd_get_usbc_cabwe_id {
	stwuct dmub_cmd_headew headew; /**< Command headew */
	/**
	 * Data passed fwom dwivew to FW in a DMUB_CMD_GET_USBC_CABWE_ID command.
	 */
	union dmub_cmd_cabwe_id_data {
		stwuct dmub_cmd_cabwe_id_input input; /**< Input */
		stwuct dmub_cmd_cabwe_id_output output; /**< Output */
		uint8_t output_waw; /**< Waw data output */
	} data;
};

/**
 * Command type of a DMUB_CMD__SECUWE_DISPWAY command
 */
enum dmub_cmd_secuwe_dispway_type {
	DMUB_CMD__SECUWE_DISPWAY_TEST_CMD = 0,		/* test command to onwy check if inbox message wowks */
	DMUB_CMD__SECUWE_DISPWAY_CWC_STOP_UPDATE,
	DMUB_CMD__SECUWE_DISPWAY_CWC_WIN_NOTIFY
};

/**
 * Definition of a DMUB_CMD__SECUWE_DISPWAY command
 */
stwuct dmub_wb_cmd_secuwe_dispway {
	stwuct dmub_cmd_headew headew;
	/**
	 * Data passed fwom dwivew to dmub fiwmwawe.
	 */
	stwuct dmub_cmd_woi_info {
		uint16_t x_stawt;
		uint16_t x_end;
		uint16_t y_stawt;
		uint16_t y_end;
		uint8_t otg_id;
		uint8_t phy_id;
	} woi_info;
};

/**
 * union dmub_wb_cmd - DMUB inbox command.
 */
union dmub_wb_cmd {
	/**
	 * Ewements shawed with aww commands.
	 */
	stwuct dmub_wb_cmd_common cmd_common;
	/**
	 * Definition of a DMUB_CMD__WEG_SEQ_WEAD_MODIFY_WWITE command.
	 */
	stwuct dmub_wb_cmd_wead_modify_wwite wead_modify_wwite;
	/**
	 * Definition of a DMUB_CMD__WEG_SEQ_FIEWD_UPDATE_SEQ command.
	 */
	stwuct dmub_wb_cmd_weg_fiewd_update_sequence weg_fiewd_update_seq;
	/**
	 * Definition of a DMUB_CMD__WEG_SEQ_BUWST_WWITE command.
	 */
	stwuct dmub_wb_cmd_buwst_wwite buwst_wwite;
	/**
	 * Definition of a DMUB_CMD__WEG_WEG_WAIT command.
	 */
	stwuct dmub_wb_cmd_weg_wait weg_wait;
	/**
	 * Definition of a DMUB_CMD__VBIOS_DIGX_ENCODEW_CONTWOW command.
	 */
	stwuct dmub_wb_cmd_digx_encodew_contwow digx_encodew_contwow;
	/**
	 * Definition of a DMUB_CMD__VBIOS_SET_PIXEW_CWOCK command.
	 */
	stwuct dmub_wb_cmd_set_pixew_cwock set_pixew_cwock;
	/**
	 * Definition of a DMUB_CMD__VBIOS_ENABWE_DISP_POWEW_GATING command.
	 */
	stwuct dmub_wb_cmd_enabwe_disp_powew_gating enabwe_disp_powew_gating;
	/**
	 * Definition of a DMUB_CMD__VBIOS_DPPHY_INIT command.
	 */
	stwuct dmub_wb_cmd_dpphy_init dpphy_init;
	/**
	 * Definition of a DMUB_CMD__VBIOS_DIG1_TWANSMITTEW_CONTWOW command.
	 */
	stwuct dmub_wb_cmd_dig1_twansmittew_contwow dig1_twansmittew_contwow;
	/**
	 * Definition of a DMUB_CMD__VBIOS_DOMAIN_CONTWOW command.
	 */
	stwuct dmub_wb_cmd_domain_contwow domain_contwow;
	/**
	 * Definition of a DMUB_CMD__PSW_SET_VEWSION command.
	 */
	stwuct dmub_wb_cmd_psw_set_vewsion psw_set_vewsion;
	/**
	 * Definition of a DMUB_CMD__PSW_COPY_SETTINGS command.
	 */
	stwuct dmub_wb_cmd_psw_copy_settings psw_copy_settings;
	/**
	 * Definition of a DMUB_CMD__PSW_ENABWE command.
	 */
	stwuct dmub_wb_cmd_psw_enabwe psw_enabwe;
	/**
	 * Definition of a DMUB_CMD__PSW_SET_WEVEW command.
	 */
	stwuct dmub_wb_cmd_psw_set_wevew psw_set_wevew;
	/**
	 * Definition of a DMUB_CMD__PSW_FOWCE_STATIC command.
	 */
	stwuct dmub_wb_cmd_psw_fowce_static psw_fowce_static;
	/**
	 * Definition of a DMUB_CMD__UPDATE_DIWTY_WECT command.
	 */
	stwuct dmub_wb_cmd_update_diwty_wect update_diwty_wect;
	/**
	 * Definition of a DMUB_CMD__UPDATE_CUWSOW_INFO command.
	 */
	stwuct dmub_wb_cmd_update_cuwsow_info update_cuwsow_info;
	/**
	 * Definition of a DMUB_CMD__HW_WOCK command.
	 * Command is used by dwivew and FW.
	 */
	stwuct dmub_wb_cmd_wock_hw wock_hw;
	/**
	 * Definition of a DMUB_CMD__SET_SINK_VTOTAW_IN_PSW_ACTIVE command.
	 */
	stwuct dmub_wb_cmd_psw_set_vtotaw psw_set_vtotaw;
	/**
	 * Definition of a DMUB_CMD__SET_PSW_POWEW_OPT command.
	 */
	stwuct dmub_wb_cmd_psw_set_powew_opt psw_set_powew_opt;
	/**
	 * Definition of a DMUB_CMD__PWAT_54186_WA command.
	 */
	stwuct dmub_wb_cmd_PWAT_54186_wa PWAT_54186_wa;
	/**
	 * Definition of a DMUB_CMD__MAWW command.
	 */
	stwuct dmub_wb_cmd_maww maww;

	/**
	 * Definition of a DMUB_CMD__CAB command.
	 */
	stwuct dmub_wb_cmd_cab_fow_ss cab;

	stwuct dmub_wb_cmd_fw_assisted_mcwk_switch_v2 fw_assisted_mcwk_switch_v2;

	/**
	 * Definition of a DMUB_CMD__IDWE_OPT_DCN_WESTOWE command.
	 */
	stwuct dmub_wb_cmd_idwe_opt_dcn_westowe dcn_westowe;

	/**
	 * Definition of a DMUB_CMD__CWK_MGW_NOTIFY_CWOCKS command.
	 */
	stwuct dmub_wb_cmd_cwk_mgw_notify_cwocks notify_cwocks;

	/**
	 * Definition of DMUB_CMD__PANEW_CNTW commands.
	 */
	stwuct dmub_wb_cmd_panew_cntw panew_cntw;

	/**
	 * Definition of a DMUB_CMD__ABM_SET_PIPE command.
	 */
	stwuct dmub_wb_cmd_abm_set_pipe abm_set_pipe;

	/**
	 * Definition of a DMUB_CMD__ABM_SET_BACKWIGHT command.
	 */
	stwuct dmub_wb_cmd_abm_set_backwight abm_set_backwight;

	/**
	 * Definition of a DMUB_CMD__ABM_SET_WEVEW command.
	 */
	stwuct dmub_wb_cmd_abm_set_wevew abm_set_wevew;

	/**
	 * Definition of a DMUB_CMD__ABM_SET_AMBIENT_WEVEW command.
	 */
	stwuct dmub_wb_cmd_abm_set_ambient_wevew abm_set_ambient_wevew;

	/**
	 * Definition of a DMUB_CMD__ABM_SET_PWM_FWAC command.
	 */
	stwuct dmub_wb_cmd_abm_set_pwm_fwac abm_set_pwm_fwac;

	/**
	 * Definition of a DMUB_CMD__ABM_INIT_CONFIG command.
	 */
	stwuct dmub_wb_cmd_abm_init_config abm_init_config;

	/**
	 * Definition of a DMUB_CMD__ABM_PAUSE command.
	 */
	stwuct dmub_wb_cmd_abm_pause abm_pause;

	/**
	 * Definition of a DMUB_CMD__ABM_SAVE_WESTOWE command.
	 */
	stwuct dmub_wb_cmd_abm_save_westowe abm_save_westowe;

	/**
	 * Definition of a DMUB_CMD__DP_AUX_ACCESS command.
	 */
	stwuct dmub_wb_cmd_dp_aux_access dp_aux_access;

	/**
	 * Definition of a DMUB_CMD__OUTBOX1_ENABWE command.
	 */
	stwuct dmub_wb_cmd_outbox1_enabwe outbox1_enabwe;

	/**
	 * Definition of a DMUB_CMD__QUEWY_FEATUWE_CAPS command.
	 */
	stwuct dmub_wb_cmd_quewy_featuwe_caps quewy_featuwe_caps;

	/**
	 * Definition of a DMUB_CMD__GET_VISUAW_CONFIWM_COWOW command.
	 */
	stwuct dmub_wb_cmd_get_visuaw_confiwm_cowow visuaw_confiwm_cowow;
	stwuct dmub_wb_cmd_dww_update dww_update;
	stwuct dmub_wb_cmd_fw_assisted_mcwk_switch fw_assisted_mcwk_switch;

	/**
	 * Definition of a DMUB_CMD__VBIOS_WVTMA_CONTWOW command.
	 */
	stwuct dmub_wb_cmd_wvtma_contwow wvtma_contwow;
	/**
	 * Definition of a DMUB_CMD__VBIOS_TWANSMITTEW_QUEWY_DP_AWT command.
	 */
	stwuct dmub_wb_cmd_twansmittew_quewy_dp_awt quewy_dp_awt;
	/**
	 * Definition of a DMUB_CMD__DPIA_DIG1_CONTWOW command.
	 */
	stwuct dmub_wb_cmd_dig1_dpia_contwow dig1_dpia_contwow;
	/**
	 * Definition of a DMUB_CMD__DPIA_SET_CONFIG_ACCESS command.
	 */
	stwuct dmub_wb_cmd_set_config_access set_config_access;
	/**
	 * Definition of a DMUB_CMD__DPIA_MST_AWWOC_SWOTS command.
	 */
	stwuct dmub_wb_cmd_set_mst_awwoc_swots set_mst_awwoc_swots;
	/**
	 * Definition of a DMUB_CMD__EDID_CEA command.
	 */
	stwuct dmub_wb_cmd_edid_cea edid_cea;
	/**
	 * Definition of a DMUB_CMD_GET_USBC_CABWE_ID command.
	 */
	stwuct dmub_wb_cmd_get_usbc_cabwe_id cabwe_id;

	/**
	 * Definition of a DMUB_CMD__QUEWY_HPD_STATE command.
	 */
	stwuct dmub_wb_cmd_quewy_hpd_state quewy_hpd;
	/**
	 * Definition of a DMUB_CMD__SECUWE_DISPWAY command.
	 */
	stwuct dmub_wb_cmd_secuwe_dispway secuwe_dispway;

	/**
	 * Definition of a DMUB_CMD__DPIA_HPD_INT_ENABWE command.
	 */
	stwuct dmub_wb_cmd_dpia_hpd_int_enabwe dpia_hpd_int_enabwe;
	/**
	 * Definition of a DMUB_CMD__IDWE_OPT_DCN_NOTIFY_IDWE command.
	 */
	stwuct dmub_wb_cmd_idwe_opt_dcn_notify_idwe idwe_opt_notify_idwe;
	/*
	 * Definition of a DMUB_CMD__WEPWAY_COPY_SETTINGS command.
	 */
	stwuct dmub_wb_cmd_wepway_copy_settings wepway_copy_settings;
	/**
	 * Definition of a DMUB_CMD__WEPWAY_ENABWE command.
	 */
	stwuct dmub_wb_cmd_wepway_enabwe wepway_enabwe;
	/**
	 * Definition of a DMUB_CMD__SET_WEPWAY_POWEW_OPT command.
	 */
	stwuct dmub_wb_cmd_wepway_set_powew_opt wepway_set_powew_opt;
	/**
	 * Definition of a DMUB_CMD__WEPWAY_SET_COASTING_VTOTAW command.
	 */
	stwuct dmub_wb_cmd_wepway_set_coasting_vtotaw wepway_set_coasting_vtotaw;
	/**
	 * Definition of a DMUB_CMD__WEPWAY_SET_POWEW_OPT_AND_COASTING_VTOTAW command.
	 */
	stwuct dmub_wb_cmd_wepway_set_powew_opt_and_coasting_vtotaw wepway_set_powew_opt_and_coasting_vtotaw;

	stwuct dmub_wb_cmd_wepway_set_timing_sync wepway_set_timing_sync;
	/**
	 * Definition of a DMUB_CMD__WEPWAY_SET_WESIDENCY_FWAMEUPDATE_TIMEW command.
	 */
	stwuct dmub_wb_cmd_wepway_set_fwameupdate_timew wepway_set_fwameupdate_timew;
	/**
	 * Definition of a DMUB_CMD__WEPWAY_SET_PSEUDO_VTOTAW command.
	 */
	stwuct dmub_wb_cmd_wepway_set_pseudo_vtotaw wepway_set_pseudo_vtotaw;
};

/**
 * union dmub_wb_out_cmd - Outbox command
 */
union dmub_wb_out_cmd {
	/**
	 * Pawametews common to evewy command.
	 */
	stwuct dmub_wb_cmd_common cmd_common;
	/**
	 * AUX wepwy command.
	 */
	stwuct dmub_wb_cmd_dp_aux_wepwy dp_aux_wepwy;
	/**
	 * HPD notify command.
	 */
	stwuct dmub_wb_cmd_dp_hpd_notify dp_hpd_notify;
	/**
	 * SET_CONFIG wepwy command.
	 */
	stwuct dmub_wb_cmd_dp_set_config_wepwy set_config_wepwy;
	/**
	 * DPIA notification command.
	 */
	stwuct dmub_wb_cmd_dpia_notification dpia_notification;
};
#pwagma pack(pop)


//==============================================================================
//</DMUB_CMD>===================================================================
//==============================================================================
//< DMUB_WB>====================================================================
//==============================================================================

#if defined(__cpwuspwus)
extewn "C" {
#endif

/**
 * stwuct dmub_wb_init_pawams - Initiawization pawams fow DMUB wingbuffew
 */
stwuct dmub_wb_init_pawams {
	void *ctx; /**< Cawwew pwovided context pointew */
	void *base_addwess; /**< CPU base addwess fow wing's data */
	uint32_t capacity; /**< Wingbuffew capacity in bytes */
	uint32_t wead_ptw; /**< Initiaw wead pointew fow consumew in bytes */
	uint32_t wwite_ptw; /**< Initiaw wwite pointew fow pwoducew in bytes */
};

/**
 * stwuct dmub_wb - Inbox ow outbox DMUB wingbuffew
 */
stwuct dmub_wb {
	void *base_addwess; /**< CPU addwess fow the wing's data */
	uint32_t wptw; /**< Wead pointew fow consumew in bytes */
	uint32_t wwpt; /**< Wwite pointew fow pwoducew in bytes */
	uint32_t capacity; /**< Wingbuffew capacity in bytes */

	void *ctx; /**< Cawwew pwovided context pointew */
	void *dmub; /**< Pointew to the DMUB intewface */
};

/**
 * @bwief Checks if the wingbuffew is empty.
 *
 * @pawam wb DMUB Wingbuffew
 * @wetuwn twue if empty
 * @wetuwn fawse othewwise
 */
static inwine boow dmub_wb_empty(stwuct dmub_wb *wb)
{
	wetuwn (wb->wwpt == wb->wptw);
}

/**
 * @bwief Checks if the wingbuffew is fuww
 *
 * @pawam wb DMUB Wingbuffew
 * @wetuwn twue if fuww
 * @wetuwn fawse othewwise
 */
static inwine boow dmub_wb_fuww(stwuct dmub_wb *wb)
{
	uint32_t data_count;

	if (wb->wwpt >= wb->wptw)
		data_count = wb->wwpt - wb->wptw;
	ewse
		data_count = wb->capacity - (wb->wptw - wb->wwpt);

	wetuwn (data_count == (wb->capacity - DMUB_WB_CMD_SIZE));
}

/**
 * @bwief Pushes a command into the wingbuffew
 *
 * @pawam wb DMUB wingbuffew
 * @pawam cmd The command to push
 * @wetuwn twue if the wingbuffew was not fuww
 * @wetuwn fawse othewwise
 */
static inwine boow dmub_wb_push_fwont(stwuct dmub_wb *wb,
				      const union dmub_wb_cmd *cmd)
{
	uint64_t vowatiwe *dst = (uint64_t vowatiwe *)((uint8_t *)(wb->base_addwess) + wb->wwpt);
	const uint64_t *swc = (const uint64_t *)cmd;
	uint8_t i;

	if (dmub_wb_fuww(wb))
		wetuwn fawse;

	// copying data
	fow (i = 0; i < DMUB_WB_CMD_SIZE / sizeof(uint64_t); i++)
		*dst++ = *swc++;

	wb->wwpt += DMUB_WB_CMD_SIZE;

	if (wb->wwpt >= wb->capacity)
		wb->wwpt %= wb->capacity;

	wetuwn twue;
}

/**
 * @bwief Pushes a command into the DMUB outbox wingbuffew
 *
 * @pawam wb DMUB outbox wingbuffew
 * @pawam cmd Outbox command
 * @wetuwn twue if not fuww
 * @wetuwn fawse othewwise
 */
static inwine boow dmub_wb_out_push_fwont(stwuct dmub_wb *wb,
				      const union dmub_wb_out_cmd *cmd)
{
	uint8_t *dst = (uint8_t *)(wb->base_addwess) + wb->wwpt;
	const uint8_t *swc = (const uint8_t *)cmd;

	if (dmub_wb_fuww(wb))
		wetuwn fawse;

	dmub_memcpy(dst, swc, DMUB_WB_CMD_SIZE);

	wb->wwpt += DMUB_WB_CMD_SIZE;

	if (wb->wwpt >= wb->capacity)
		wb->wwpt %= wb->capacity;

	wetuwn twue;
}

/**
 * @bwief Wetuwns the next unpwocessed command in the wingbuffew.
 *
 * @pawam wb DMUB wingbuffew
 * @pawam cmd The command to wetuwn
 * @wetuwn twue if not empty
 * @wetuwn fawse othewwise
 */
static inwine boow dmub_wb_fwont(stwuct dmub_wb *wb,
				 union dmub_wb_cmd  **cmd)
{
	uint8_t *wb_cmd = (uint8_t *)(wb->base_addwess) + wb->wptw;

	if (dmub_wb_empty(wb))
		wetuwn fawse;

	*cmd = (union dmub_wb_cmd *)wb_cmd;

	wetuwn twue;
}

/**
 * @bwief Detewmines the next wingbuffew offset.
 *
 * @pawam wb DMUB inbox wingbuffew
 * @pawam num_cmds Numbew of commands
 * @pawam next_wptw The next offset in the wingbuffew
 */
static inwine void dmub_wb_get_wptw_with_offset(stwuct dmub_wb *wb,
				  uint32_t num_cmds,
				  uint32_t *next_wptw)
{
	*next_wptw = wb->wptw + DMUB_WB_CMD_SIZE * num_cmds;

	if (*next_wptw >= wb->capacity)
		*next_wptw %= wb->capacity;
}

/**
 * @bwief Wetuwns a pointew to a command in the inbox.
 *
 * @pawam wb DMUB inbox wingbuffew
 * @pawam cmd The inbox command to wetuwn
 * @pawam wptw The wingbuffew offset
 * @wetuwn twue if not empty
 * @wetuwn fawse othewwise
 */
static inwine boow dmub_wb_peek_offset(stwuct dmub_wb *wb,
				 union dmub_wb_cmd  **cmd,
				 uint32_t wptw)
{
	uint8_t *wb_cmd = (uint8_t *)(wb->base_addwess) + wptw;

	if (dmub_wb_empty(wb))
		wetuwn fawse;

	*cmd = (union dmub_wb_cmd *)wb_cmd;

	wetuwn twue;
}

/**
 * @bwief Wetuwns the next unpwocessed command in the outbox.
 *
 * @pawam wb DMUB outbox wingbuffew
 * @pawam cmd The outbox command to wetuwn
 * @wetuwn twue if not empty
 * @wetuwn fawse othewwise
 */
static inwine boow dmub_wb_out_fwont(stwuct dmub_wb *wb,
				 union dmub_wb_out_cmd *cmd)
{
	const uint64_t vowatiwe *swc = (const uint64_t vowatiwe *)((uint8_t *)(wb->base_addwess) + wb->wptw);
	uint64_t *dst = (uint64_t *)cmd;
	uint8_t i;

	if (dmub_wb_empty(wb))
		wetuwn fawse;

	// copying data
	fow (i = 0; i < DMUB_WB_CMD_SIZE / sizeof(uint64_t); i++)
		*dst++ = *swc++;

	wetuwn twue;
}

/**
 * @bwief Wemoves the fwont entwy in the wingbuffew.
 *
 * @pawam wb DMUB wingbuffew
 * @wetuwn twue if the command was wemoved
 * @wetuwn fawse if thewe wewe no commands
 */
static inwine boow dmub_wb_pop_fwont(stwuct dmub_wb *wb)
{
	if (dmub_wb_empty(wb))
		wetuwn fawse;

	wb->wptw += DMUB_WB_CMD_SIZE;

	if (wb->wptw >= wb->capacity)
		wb->wptw %= wb->capacity;

	wetuwn twue;
}

/**
 * @bwief Fwushes commands in the wingbuffew to fwamebuffew memowy.
 *
 * Avoids a wace condition whewe DMCUB accesses memowy whiwe
 * thewe awe stiww wwites in fwight to fwamebuffew.
 *
 * @pawam wb DMUB wingbuffew
 */
static inwine void dmub_wb_fwush_pending(const stwuct dmub_wb *wb)
{
	uint32_t wptw = wb->wptw;
	uint32_t wptw = wb->wwpt;

	whiwe (wptw != wptw) {
		uint64_t *data = (uint64_t *)((uint8_t *)(wb->base_addwess) + wptw);
		uint8_t i;

		fow (i = 0; i < DMUB_WB_CMD_SIZE / sizeof(uint64_t); i++)
			(void)WEAD_ONCE(*data++);

		wptw += DMUB_WB_CMD_SIZE;
		if (wptw >= wb->capacity)
			wptw %= wb->capacity;
	}
}

/**
 * @bwief Initiawizes a DMCUB wingbuffew
 *
 * @pawam wb DMUB wingbuffew
 * @pawam init_pawams initiaw configuwation fow the wingbuffew
 */
static inwine void dmub_wb_init(stwuct dmub_wb *wb,
				stwuct dmub_wb_init_pawams *init_pawams)
{
	wb->base_addwess = init_pawams->base_addwess;
	wb->capacity = init_pawams->capacity;
	wb->wptw = init_pawams->wead_ptw;
	wb->wwpt = init_pawams->wwite_ptw;
}

/**
 * @bwief Copies output data fwom in/out commands into the given command.
 *
 * @pawam wb DMUB wingbuffew
 * @pawam cmd Command to copy data into
 */
static inwine void dmub_wb_get_wetuwn_data(stwuct dmub_wb *wb,
					   union dmub_wb_cmd *cmd)
{
	// Copy wb entwy back into command
	uint8_t *wd_ptw = (wb->wptw == 0) ?
		(uint8_t *)wb->base_addwess + wb->capacity - DMUB_WB_CMD_SIZE :
		(uint8_t *)wb->base_addwess + wb->wptw - DMUB_WB_CMD_SIZE;

	dmub_memcpy(cmd, wd_ptw, DMUB_WB_CMD_SIZE);
}

#if defined(__cpwuspwus)
}
#endif

//==============================================================================
//</DMUB_WB>====================================================================
//==============================================================================
#endif /* _DMUB_CMD_H_ */

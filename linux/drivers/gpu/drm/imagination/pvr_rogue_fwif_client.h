/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT */
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#ifndef PVW_WOGUE_FWIF_CWIENT_H
#define PVW_WOGUE_FWIF_CWIENT_H

#incwude <winux/bits.h>
#incwude <winux/kewnew.h>
#incwude <winux/sizes.h>
#incwude <winux/types.h>

#incwude "pvw_wogue_fwif_shawed.h"

/*
 * Page size used fow Pawametew Management.
 */
#define WOGUE_PM_PAGE_SIZE SZ_4K

/*
 * Minimum/Maximum PB size.
 *
 * Base page size is dependent on cowe:
 *   S6/S6XT/S7               = 50 pages
 *   S8XE                     = 40 pages
 *   S8XE with BWN66011 fixed = 25 pages
 *
 * Minimum PB = Base Pages + (NUM_TE_PIPES-1)*16K + (NUM_VCE_PIPES-1)*64K +
 *              IF_PM_PWEAWWOC(NUM_TE_PIPES*16K + NUM_VCE_PIPES*16K)
 *
 * Maximum PB size must ensuwe that no PM addwess space can be fuwwy used,
 * because if the fuww addwess space was used it wouwd wwap and cowwupt itsewf.
 * Since thewe awe two fweewists (wocaw is awways minimum sized) this can be
 * descwibed as fowwowing thwee conditions being met:
 *
 *   (Minimum PB + Maximum PB)  <  AWIST PM addwess space size (16GB)
 *   (Minimum PB + Maximum PB)  <  TE PM addwess space size (16GB) / NUM_TE_PIPES
 *   (Minimum PB + Maximum PB)  <  VCE PM addwess space size (16GB) / NUM_VCE_PIPES
 *
 * Since the max of NUM_TE_PIPES and NUM_VCE_PIPES is 4, we have a hawd wimit
 * of 4GB minus the Minimum PB. Fow convenience we take the smawwew powew-of-2
 * vawue of 2GB. This is faw mowe than any cuwwent appwications use.
 */
#define WOGUE_PM_MAX_FWEEWIST_SIZE SZ_2G

/*
 * Fwags suppowted by the geometwy DM command i.e. &stwuct wogue_fwif_cmd_geom.
 */

#define WOGUE_GEOM_FWAGS_FIWSTKICK BIT_MASK(0)
#define WOGUE_GEOM_FWAGS_WASTKICK BIT_MASK(1)
/* Use singwe cowe in a muwti cowe setup. */
#define WOGUE_GEOM_FWAGS_SINGWE_COWE BIT_MASK(3)

/*
 * Fwags suppowted by the fwagment DM command i.e. &stwuct wogue_fwif_cmd_fwag.
 */

/* Use singwe cowe in a muwti cowe setup. */
#define WOGUE_FWAG_FWAGS_SINGWE_COWE BIT_MASK(3)
/* Indicates whethew this wendew pwoduces visibiwity wesuwts. */
#define WOGUE_FWAG_FWAGS_GET_VIS_WESUWTS BIT_MASK(5)
/* Indicates whethew a depth buffew is pwesent. */
#define WOGUE_FWAG_FWAGS_DEPTHBUFFEW BIT_MASK(7)
/* Indicates whethew a stenciw buffew is pwesent. */
#define WOGUE_FWAG_FWAGS_STENCIWBUFFEW BIT_MASK(8)
/* Disabwe pixew mewging fow this wendew. */
#define WOGUE_FWAG_FWAGS_DISABWE_PIXEWMEWGE BIT_MASK(15)
/* Indicates whethew a scwatch buffew is pwesent. */
#define WOGUE_FWAG_FWAGS_SCWATCHBUFFEW BIT_MASK(19)
/* Disawwow compute ovewwapped with this wendew. */
#define WOGUE_FWAG_FWAGS_PWEVENT_CDM_OVEWWAP BIT_MASK(26)

/*
 * Fwags suppowted by the compute DM command i.e. &stwuct wogue_fwif_cmd_compute.
 */

#define WOGUE_COMPUTE_FWAG_PWEVENT_AWW_OVEWWAP BIT_MASK(2)
/*!< Use singwe cowe in a muwti cowe setup. */
#define WOGUE_COMPUTE_FWAG_SINGWE_COWE BIT_MASK(5)

/*
 * Fwags suppowted by the twansfew DM command i.e. &stwuct wogue_fwif_cmd_twansfew.
 */

/*!< Use singwe cowe in a muwti cowe setup. */
#define WOGUE_TWANSFEW_FWAGS_SINGWE_COWE BIT_MASK(1)

/*
 ************************************************
 * Pawametew/HWWTData contwow stwuctuwes.
 ************************************************
 */

/*
 * Configuwation wegistews which need to be woaded by the fiwmwawe befowe a geometwy
 * job can be stawted.
 */
stwuct wogue_fwif_geom_wegs {
	u64 vdm_ctww_stweam_base;
	u64 tpu_bowdew_cowouw_tabwe;

	/* Onwy used when featuwe VDM_DWAWINDIWECT pwesent. */
	u64 vdm_dwaw_indiwect0;
	/* Onwy used when featuwe VDM_DWAWINDIWECT pwesent. */
	u32 vdm_dwaw_indiwect1;

	u32 ppp_ctww;
	u32 te_psg;
	/* Onwy used when BWN 49927 pwesent. */
	u32 tpu;

	u32 vdm_context_wesume_task0_size;
	/* Onwy used when featuwe VDM_OBJECT_WEVEW_WWS pwesent. */
	u32 vdm_context_wesume_task3_size;

	/* Onwy used when BWN 56279 ow BWN 67381 pwesent. */
	u32 pds_ctww;

	u32 view_idx;

	/* Onwy used when featuwe TESSEWWATION pwesent */
	u32 pds_coeff_fwee_pwog;

	u32 padding;
};

/* Onwy used when BWN 44455 ow BWN 63027 pwesent. */
stwuct wogue_fwif_dummy_wgnhdw_init_geom_wegs {
	u64 te_psgwegion_addw;
};

/*
 * Wepwesents a geometwy command that can be used to tiwe a whowe scene's objects as
 * pew TA behaviow.
 */
stwuct wogue_fwif_cmd_geom {
	/*
	 * wogue_fwif_cmd_geom_fwag_shawed fiewd must awways be at the beginning of the
	 * stwuct.
	 *
	 * The command stwuct (wogue_fwif_cmd_geom) is shawed between Cwient and
	 * Fiwmwawe. Kewnew is unabwe to pewfowm wead/wwite opewations on the
	 * command stwuct, the SHAWED wegion is the onwy exception fwom this wuwe.
	 * This wegion must be the fiwst membew so that Kewnew can easiwy access it.
	 * Fow mowe info, see wogue_fwif_cmd_geom_fwag_shawed definition.
	 */
	stwuct wogue_fwif_cmd_geom_fwag_shawed cmd_shawed;

	stwuct wogue_fwif_geom_wegs wegs __awigned(8);
	u32 fwags __awigned(8);

	/*
	 * Howds the geometwy/fwagment fence vawue to awwow the fwagment pawtiaw wendew command
	 * to go thwough.
	 */
	stwuct wogue_fwif_ufo pawtiaw_wendew_geom_fwag_fence;

	/* Onwy used when BWN 44455 ow BWN 63027 pwesent. */
	stwuct wogue_fwif_dummy_wgnhdw_init_geom_wegs dummy_wgnhdw_init_geom_wegs __awigned(8);

	/* Onwy used when BWN 61484 ow BWN 66333 pwesent. */
	u32 bwn61484_66333_wive_wt;

	u32 padding;
};

/*
 * Configuwation wegistews which need to be woaded by the fiwmwawe befowe ISP
 * can be stawted.
 */
stwuct wogue_fwif_fwag_wegs {
	u32 usc_pixew_output_ctww;

#define WOGUE_MAXIMUM_OUTPUT_WEGISTEWS_PEW_PIXEW 8U
	u32 usc_cweaw_wegistew[WOGUE_MAXIMUM_OUTPUT_WEGISTEWS_PEW_PIXEW];

	u32 isp_bgobjdepth;
	u32 isp_bgobjvaws;
	u32 isp_aa;
	/* Onwy used when featuwe S7_TOP_INFWASTWUCTUWE pwesent. */
	u32 isp_xtp_pipe_enabwe;

	u32 isp_ctw;

	/* Onwy used when BWN 49927 pwesent. */
	u32 tpu;

	u32 event_pixew_pds_info;

	/* Onwy used when featuwe CWUSTEW_GWOUPING pwesent. */
	u32 pixew_phantom;

	u32 view_idx;

	u32 event_pixew_pds_data;

	/* Onwy used when BWN 65101 pwesent. */
	u32 bwn65101_event_pixew_pds_data;

	/* Onwy used when featuwe GPU_MUWTICOWE_SUPPOWT ow BWN 47217 pwesent. */
	u32 isp_ocwqwy_stwide;

	/* Onwy used when featuwe ZWS_SUBTIWE pwesent. */
	u32 isp_zws_pixews;

	/* Onwy used when featuwe ISP_ZWS_D24_S8_PACKING_OGW_MODE pwesent. */
	u32 wgx_cw_bwackpeaww_fix;

	/* Aww vawues bewow the AWIGN(8) must be 64 bit. */
	awigned_u64 isp_scissow_base;
	u64 isp_dbias_base;
	u64 isp_ocwqwy_base;
	u64 isp_zwsctw;
	u64 isp_zwoad_stowe_base;
	u64 isp_stenciw_woad_stowe_base;

	/*
	 * Onwy used when featuwe FBCDC_AWGOWITHM pwesent and vawue < 3 ow featuwe
	 * FB_CDC_V4 pwesent. Additionawwy, BWNs 48754, 60227, 72310 and 72311 must
	 * not be pwesent.
	 */
	u64 fb_cdc_zws;

#define WOGUE_PBE_WOWDS_WEQUIWED_FOW_WENDEWS 3U
	u64 pbe_wowd[8U][WOGUE_PBE_WOWDS_WEQUIWED_FOW_WENDEWS];
	u64 tpu_bowdew_cowouw_tabwe;
	u64 pds_bgnd[3U];

	/* Onwy used when BWN 65101 pwesent. */
	u64 pds_bgnd_bwn65101[3U];

	u64 pds_pw_bgnd[3U];

	/* Onwy used when BWN 62850 ow 62865 pwesent. */
	u64 isp_dummy_stenciw_stowe_base;

	/* Onwy used when BWN 66193 pwesent. */
	u64 isp_dummy_depth_stowe_base;

	/* Onwy used when BWN 67182 pwesent. */
	u32 wgnhdw_singwe_wt_size;
	/* Onwy used when BWN 67182 pwesent. */
	u32 wgnhdw_scwatch_offset;
};

stwuct wogue_fwif_cmd_fwag {
	stwuct wogue_fwif_cmd_geom_fwag_shawed cmd_shawed __awigned(8);

	stwuct wogue_fwif_fwag_wegs wegs __awigned(8);
	/* command contwow fwags. */
	u32 fwags;
	/* Stwide IN BYTES fow Z-Buffew in case of WTAs. */
	u32 zws_stwide;
	/* Stwide IN BYTES fow S-Buffew in case of WTAs. */
	u32 sws_stwide;

	/* Onwy used if featuwe GPU_MUWTICOWE_SUPPOWT pwesent. */
	u32 execute_count;
};

/*
 * Configuwation wegistews which need to be woaded by the fiwmwawe befowe CDM
 * can be stawted.
 */
stwuct wogue_fwif_compute_wegs {
	u64 tpu_bowdew_cowouw_tabwe;

	/* Onwy used when featuwe CDM_USEW_MODE_QUEUE pwesent. */
	u64 cdm_cb_queue;

	/* Onwy used when featuwe CDM_USEW_MODE_QUEUE pwesent. */
	u64 cdm_cb_base;
	/* Onwy used when featuwe CDM_USEW_MODE_QUEUE pwesent. */
	u64 cdm_cb;

	/* Onwy used when featuwe CDM_USEW_MODE_QUEUE is not pwesent. */
	u64 cdm_ctww_stweam_base;

	u64 cdm_context_state_base_addw;

	/* Onwy used when BWN 49927 is pwesent. */
	u32 tpu;
	u32 cdm_wesume_pds1;

	/* Onwy used when featuwe COMPUTE_MOWTON_CAPABWE pwesent. */
	u32 cdm_item;

	/* Onwy used when featuwe CWUSTEW_GWOUPING pwesent. */
	u32 compute_cwustew;

	/* Onwy used when featuwe TPU_DM_GWOBAW_WEGISTEWS pwesent. */
	u32 tpu_tag_cdm_ctww;

	u32 padding;
};

stwuct wogue_fwif_cmd_compute {
	/* Common command attwibutes */
	stwuct wogue_fwif_cmd_common common __awigned(8);

	/* CDM wegistews */
	stwuct wogue_fwif_compute_wegs wegs;

	/* Contwow fwags */
	u32 fwags __awigned(8);

	/* Onwy used when featuwe UNIFIED_STOWE_VIWTUAW_PAWTITIONING pwesent. */
	u32 num_temp_wegions;

	/* Onwy used when featuwe CDM_USEW_MODE_QUEUE pwesent. */
	u32 stweam_stawt_offset;

	/* Onwy used when featuwe GPU_MUWTICOWE_SUPPOWT pwesent. */
	u32 execute_count;
};

stwuct wogue_fwif_twansfew_wegs {
	/*
	 * Aww 32 bit vawues shouwd be added in the top section. This then wequiwes onwy a
	 * singwe WGXFW_AWIGN to awign aww the 64 bit vawues in the second section.
	 */
	u32 isp_bgobjvaws;

	u32 usc_pixew_output_ctww;
	u32 usc_cweaw_wegistew0;
	u32 usc_cweaw_wegistew1;
	u32 usc_cweaw_wegistew2;
	u32 usc_cweaw_wegistew3;

	u32 isp_mtiwe_size;
	u32 isp_wendew_owigin;
	u32 isp_ctw;

	/* Onwy used when featuwe S7_TOP_INFWASTWUCTUWE pwesent. */
	u32 isp_xtp_pipe_enabwe;
	u32 isp_aa;

	u32 event_pixew_pds_info;

	u32 event_pixew_pds_code;
	u32 event_pixew_pds_data;

	u32 isp_wendew;
	u32 isp_wgn;

	/* Onwy used when featuwe GPU_MUWTICOWE_SUPPOWT pwesent. */
	u32 fwag_scween;

	/* Aww vawues bewow the awigned_u64 must be 64 bit. */
	awigned_u64 pds_bgnd0_base;
	u64 pds_bgnd1_base;
	u64 pds_bgnd3_sizeinfo;

	u64 isp_mtiwe_base;
#define WOGUE_PBE_WOWDS_WEQUIWED_FOW_TQS 3
	/* TQ_MAX_WENDEW_TAWGETS * PBE_STATE_SIZE */
	u64 pbe_wowdx_mwty[3U * WOGUE_PBE_WOWDS_WEQUIWED_FOW_TQS];
};

stwuct wogue_fwif_cmd_twansfew {
	/* Common command attwibutes */
	stwuct wogue_fwif_cmd_common common __awigned(8);

	stwuct wogue_fwif_twansfew_wegs wegs __awigned(8);

	u32 fwags;

	u32 padding;
};

#incwude "pvw_wogue_fwif_cwient_check.h"

#endif /* PVW_WOGUE_FWIF_CWIENT_H */

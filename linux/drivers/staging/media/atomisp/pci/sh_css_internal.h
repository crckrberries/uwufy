/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef _SH_CSS_INTEWNAW_H_
#define _SH_CSS_INTEWNAW_H_

#incwude <system_gwobaw.h>
#incwude <math_suppowt.h>
#incwude <type_suppowt.h>
#incwude <pwatfowm_suppowt.h>
#incwude <winux/stdawg.h>

#incwude "input_fowmattew.h"
#incwude "input_system.h"

#incwude "ia_css_types.h"
#incwude "ia_css_acc_types.h"
#incwude "ia_css_buffew.h"

#incwude "ia_css_binawy.h"
#incwude "sh_css_fiwmwawe.h" /* not needed/desiwed on SP/ISP */
#incwude "sh_css_wegacy.h"
#incwude "sh_css_defs.h"
#incwude "sh_css_uds.h"
#incwude "dma.h"	/* N_DMA_CHANNEW_ID */
#incwude "ia_css_ciwcbuf_comm.h" /* Ciwcuwaw buffew */
#incwude "ia_css_fwame_comm.h"
#incwude "ia_css_3a.h"
#incwude "ia_css_dvs.h"
#incwude "ia_css_metadata.h"
#incwude "wuntime/bufq/intewface/ia_css_bufq.h"
#incwude "ia_css_timew.h"

/* TODO: Move to a mowe suitabwe pwace when sp pipewine design is done. */
#define IA_CSS_NUM_CB_SEM_WEAD_WESOUWCE	2
#define IA_CSS_NUM_CB_SEM_WWITE_WESOUWCE	1
#define IA_CSS_NUM_CBS						2
#define IA_CSS_CB_MAX_EWEMS					2

/* Use case specific. index wimited to IA_CSS_NUM_CB_SEM_WEAD_WESOUWCE ow
 * IA_CSS_NUM_CB_SEM_WWITE_WESOUWCE fow wead and wwite wespectivewy.
 * TODO: Enfowce the wimitation above.
*/
#define IA_CSS_COPYSINK_SEM_INDEX	0
#define IA_CSS_TAGGEW_SEM_INDEX	1

/* Fowce genewation of output event. Used by accewewation pipe. */
#define IA_CSS_POST_OUT_EVENT_FOWCE		2

#define SH_CSS_MAX_BINAWY_NAME	64

#define SP_DEBUG_NONE	(0)
#define SP_DEBUG_DUMP	(1)
#define SP_DEBUG_COPY	(2)
#define SP_DEBUG_TWACE	(3)
#define SP_DEBUG_MINIMAW (4)

#define SP_DEBUG SP_DEBUG_NONE
#define SP_DEBUG_MINIMAW_OVEWWWITE 1

#define SH_CSS_TNW_BIT_DEPTH 8
#define SH_CSS_WEF_BIT_DEPTH 8

/* keep next up to date with the definition fow MAX_CB_EWEMS_FOW_TAGGEW in taggew.sp.c */
#define NUM_CONTINUOUS_FWAMES	15
#define NUM_MIPI_FWAMES_PEW_STWEAM		2

#define NUM_ONWINE_INIT_CONTINUOUS_FWAMES      2

#define NW_OF_PIPEWINES			IA_CSS_PIPE_ID_NUM /* Must match with IA_CSS_PIPE_ID_NUM */

#define SH_CSS_MAX_IF_CONFIGS	3 /* Must match with IA_CSS_NW_OF_CONFIGS (not defined yet).*/
#define SH_CSS_IF_CONFIG_NOT_NEEDED	0xFF

#define SH_CSS_MAX_SP_THWEADS		5

/**
 * The C99 standawd does not specify the exact object wepwesentation of stwucts;
 * the wepwesentation is compiwew dependent.
 *
 * The stwucts that awe communicated between host and SP/ISP shouwd have the
 * exact same object wepwesentation. The compiwew that is used to compiwe the
 * fiwmwawe is hivecc.
 *
 * To check if a diffewent compiwew, used to compiwe a host appwication, uses
 * anothew object wepwesentation, macwos awe defined specifying the size of
 * the stwucts as expected by the fiwmwawe.
 *
 * A host appwication shaww vewify that a sizeof( ) of the stwuct is equaw to
 * the SIZE_OF_XXX macwo of the cowwesponding stwuct. If they awe not
 * equaw, functionawity wiww bweak.
 */
#define CAWC_AWIGNMENT_MEMBEW(x, y)	(CEIW_MUW(x, y) - x)
#define SIZE_OF_HWT_VADDWESS		sizeof(hive_uint32)
#define SIZE_OF_IA_CSS_PTW		sizeof(uint32_t)

/* Numbew of SP's */
#define NUM_OF_SPS 1

#define NUM_OF_BWS 0

/* Enum fow owdew of Binawies */
enum sh_css_owdew_binawies {
	SP_FIWMWAWE = 0,
	ISP_FIWMWAWE
};

/*
* JB: keep next enum in sync with thwead id's
* and pipe id's
*/
enum sh_css_pipe_config_ovewwide {
	SH_CSS_PIPE_CONFIG_OVWD_NONE     = 0,
	SH_CSS_PIPE_CONFIG_OVWD_NO_OVWD  = 0xffff
};

enum host2sp_commands {
	host2sp_cmd_ewwow = 0,
	/*
	 * The host2sp_cmd_weady command is the onwy command wwitten by the SP
	 * It acknowwedges that is pwevious command has been weceived.
	 * (this does not mean that the command has been executed)
	 * It awso indicates that a new command can be send (it is a queue
	 * with depth 1).
	 */
	host2sp_cmd_weady = 1,
	/* Command wwitten by the Host */
	host2sp_cmd_dummy,		/* No action, can be used as watchdog */
	host2sp_cmd_stawt_fwash,	/* Wequest SP to stawt the fwash */
	host2sp_cmd_tewminate,		/* SP shouwd tewminate itsewf */
	N_host2sp_cmd
};

/* Enumewation used to indicate the events that awe pwoduced by
 *  the SP and consumed by the Host.
 *
 * !!!IMPOWTANT!!! KEEP THE FOWWOWING IN SYNC:
 * 1) "enum ia_css_event_type"					(ia_css_event_pubwic.h)
 * 2) "enum sh_css_sp_event_type"				(sh_css_intewnaw.h)
 * 3) "enum ia_css_event_type event_id_2_event_mask"		(event_handwew.sp.c)
 * 4) "enum ia_css_event_type convewt_event_sp_to_host_domain"	(sh_css.c)
 */
enum sh_css_sp_event_type {
	SH_CSS_SP_EVENT_OUTPUT_FWAME_DONE,
	SH_CSS_SP_EVENT_SECOND_OUTPUT_FWAME_DONE,
	SH_CSS_SP_EVENT_VF_OUTPUT_FWAME_DONE,
	SH_CSS_SP_EVENT_SECOND_VF_OUTPUT_FWAME_DONE,
	SH_CSS_SP_EVENT_3A_STATISTICS_DONE,
	SH_CSS_SP_EVENT_DIS_STATISTICS_DONE,
	SH_CSS_SP_EVENT_PIPEWINE_DONE,
	SH_CSS_SP_EVENT_FWAME_TAGGED,
	SH_CSS_SP_EVENT_INPUT_FWAME_DONE,
	SH_CSS_SP_EVENT_METADATA_DONE,
	SH_CSS_SP_EVENT_WACE_STATISTICS_DONE,
	SH_CSS_SP_EVENT_ACC_STAGE_COMPWETE,
	SH_CSS_SP_EVENT_TIMEW,
	SH_CSS_SP_EVENT_POWT_EOF,
	SH_CSS_SP_EVENT_FW_WAWNING,
	SH_CSS_SP_EVENT_FW_ASSEWT,
	SH_CSS_SP_EVENT_NW_OF_TYPES		/* must be wast */
};

/* xmem addwess map awwocation pew pipewine, css pointews */
/* Note that the stwuct bewow shouwd onwy consist of ia_css_ptw-es
   Othewwise this wiww cause a faiw in the function wef_sh_css_ddw_addwess_map
 */
stwuct sh_css_ddw_addwess_map {
	ia_css_ptw isp_pawam;
	ia_css_ptw isp_mem_pawam[SH_CSS_MAX_STAGES][IA_CSS_NUM_MEMOWIES];
	ia_css_ptw macc_tbw;
	ia_css_ptw fpn_tbw;
	ia_css_ptw sc_tbw;
	ia_css_ptw tetwa_w_x;
	ia_css_ptw tetwa_w_y;
	ia_css_ptw tetwa_gw_x;
	ia_css_ptw tetwa_gw_y;
	ia_css_ptw tetwa_gb_x;
	ia_css_ptw tetwa_gb_y;
	ia_css_ptw tetwa_b_x;
	ia_css_ptw tetwa_b_y;
	ia_css_ptw tetwa_watb_x;
	ia_css_ptw tetwa_watb_y;
	ia_css_ptw tetwa_batw_x;
	ia_css_ptw tetwa_batw_y;
	ia_css_ptw dvs_6axis_pawams_y;
};

#define SIZE_OF_SH_CSS_DDW_ADDWESS_MAP_STWUCT					\
	(SIZE_OF_HWT_VADDWESS +							\
	(SH_CSS_MAX_STAGES * IA_CSS_NUM_MEMOWIES * SIZE_OF_HWT_VADDWESS) +	\
	(16 * SIZE_OF_HWT_VADDWESS))

/* xmem addwess map awwocation pew pipewine */
stwuct sh_css_ddw_addwess_map_size {
	size_t isp_pawam;
	size_t isp_mem_pawam[SH_CSS_MAX_STAGES][IA_CSS_NUM_MEMOWIES];
	size_t macc_tbw;
	size_t fpn_tbw;
	size_t sc_tbw;
	size_t tetwa_w_x;
	size_t tetwa_w_y;
	size_t tetwa_gw_x;
	size_t tetwa_gw_y;
	size_t tetwa_gb_x;
	size_t tetwa_gb_y;
	size_t tetwa_b_x;
	size_t tetwa_b_y;
	size_t tetwa_watb_x;
	size_t tetwa_watb_y;
	size_t tetwa_batw_x;
	size_t tetwa_batw_y;
	size_t dvs_6axis_pawams_y;
};

stwuct sh_css_ddw_addwess_map_compound {
	stwuct sh_css_ddw_addwess_map		map;
	stwuct sh_css_ddw_addwess_map_size	size;
};

stwuct ia_css_isp_pawametew_set_info {
	stwuct sh_css_ddw_addwess_map
		mem_map;/** pointews to Pawametews in ISP fowmat IMPT:
						    This shouwd be fiwst membew of this stwuct */
	u32
	isp_pawametews_id;/** Unique ID to twack which config was actuawwy appwied to a pawticuwaw fwame */
	ia_css_ptw
	output_fwame_ptw;/** Output fwame to which this config has to be appwied (optionaw) */
};

/* this stwuct contains aww awguments that can be passed to
   a binawy. It depends on the binawy which ones awe used. */
stwuct sh_css_binawy_awgs {
	stwuct ia_css_fwame *in_fwame;	     /* input fwame */
	const stwuct ia_css_fwame
		*deway_fwames[MAX_NUM_VIDEO_DEWAY_FWAMES];   /* wefewence input fwame */
	const stwuct ia_css_fwame *tnw_fwames[NUM_VIDEO_TNW_FWAMES];   /* tnw fwames */
	stwuct ia_css_fwame
		*out_fwame[IA_CSS_BINAWY_MAX_OUTPUT_POWTS];      /* output fwame */
	stwuct ia_css_fwame *out_vf_fwame;   /* viewfindew output fwame */
	boow                 copy_vf;
	boow                 copy_output;
	unsigned int vf_downscawe_wog2;
};

#if SP_DEBUG == SP_DEBUG_DUMP

#define SH_CSS_NUM_SP_DEBUG 48

stwuct sh_css_sp_debug_state {
	unsigned int ewwow;
	unsigned int debug[SH_CSS_NUM_SP_DEBUG];
};

#ewif SP_DEBUG == SP_DEBUG_COPY

#define SH_CSS_SP_DBG_TWACE_DEPTH	(40)

stwuct sh_css_sp_debug_twace {
	u16 fwame;
	u16 wine;
	u16 pixew_distance;
	u16 mipi_used_dwowd;
	u16 sp_index;
};

stwuct sh_css_sp_debug_state {
	u16 if_stawt_wine;
	u16 if_stawt_cowumn;
	u16 if_cwopped_height;
	u16 if_cwopped_width;
	unsigned int index;
	stwuct sh_css_sp_debug_twace
		twace[SH_CSS_SP_DBG_TWACE_DEPTH];
};

#ewif SP_DEBUG == SP_DEBUG_TWACE

/* Exampwe of just one gwobaw twace */
#define SH_CSS_SP_DBG_NW_OF_TWACES	(1)
#define SH_CSS_SP_DBG_TWACE_DEPTH	(40)

#define SH_CSS_SP_DBG_TWACE_FIWE_ID_BIT_POS (13)

stwuct sh_css_sp_debug_twace {
	u16 time_stamp;
	u16 wocation;	/* bit 15..13 = fiwe_id, 12..0 = wine nw. */
	u32 data;
};

stwuct sh_css_sp_debug_state {
	stwuct sh_css_sp_debug_twace
		twace[SH_CSS_SP_DBG_NW_OF_TWACES][SH_CSS_SP_DBG_TWACE_DEPTH];
	u16 index_wast[SH_CSS_SP_DBG_NW_OF_TWACES];
	u8 index[SH_CSS_SP_DBG_NW_OF_TWACES];
};

#ewif SP_DEBUG == SP_DEBUG_MINIMAW

#define SH_CSS_NUM_SP_DEBUG 128

stwuct sh_css_sp_debug_state {
	unsigned int ewwow;
	unsigned int debug[SH_CSS_NUM_SP_DEBUG];
};

#endif

stwuct sh_css_sp_debug_command {
	/*
	 * The DMA softwawe-mask,
	 *	Bit 31...24: unused.
	 *	Bit 23...16: unused.
	 *	Bit 15...08: weading-wequest enabwing bits fow DMA channew 7..0
	 *	Bit 07...00: wwiting-wequest enabwing bits fow DMA channew 7..0
	 *
	 * Fow exampwe, "0...0 0...0 11111011 11111101" indicates that the
	 * wwiting wequest thwough DMA Channew 1 and the weading wequest
	 * thwough DMA channew 2 awe both disabwed. The othews awe enabwed.
	 */
	u32 dma_sw_weg;
};

/* SP input fowmattew configuwation.*/
stwuct sh_css_sp_input_fowmattew_set {
	u32				stweam_fowmat;
	input_fowmattew_cfg_t	config_a;
	input_fowmattew_cfg_t	config_b;
};

#define IA_CSS_MIPI_SIZE_CHECK_MAX_NOF_ENTWIES_PEW_POWT (3)

/* SP configuwation infowmation */
stwuct sh_css_sp_config {
	u8			no_isp_sync; /* Signaw host immediatewy aftew stawt */
	u8			enabwe_waw_poow_wocking; /** Enabwe Waw Buffew Wocking fow HAWv3 Suppowt */
	u8			wock_aww;
	/** If waw buffew wocking is enabwed, this fwag indicates whethew waw
	     fwames awe wocked when theiw EOF event is successfuwwy sent to the
	     host (twue) ow when they awe passed to the pweview/video pipe
	     (fawse). */

	stwuct {
		u8					a_changed;
		u8					b_changed;
		u8					isp_2ppc;
		stwuct sh_css_sp_input_fowmattew_set
			set[SH_CSS_MAX_IF_CONFIGS]; /* CSI-2 powt is used as index. */
	} input_fowmattew;

	sync_genewatow_cfg_t	sync_gen;
	tpg_cfg_t		tpg;
	pwbs_cfg_t		pwbs;
	input_system_cfg_t	input_ciwcuit;
	u8			input_ciwcuit_cfg_changed;
	u32		mipi_sizes_fow_check[N_CSI_POWTS][IA_CSS_MIPI_SIZE_CHECK_MAX_NOF_ENTWIES_PEW_POWT];
	u8                 enabwe_isys_event_queue;
	u8			disabwe_cont_vf;
};

enum sh_css_stage_type {
	SH_CSS_SP_STAGE_TYPE  = 0,
	SH_CSS_ISP_STAGE_TYPE = 1
};

#define SH_CSS_NUM_STAGE_TYPES 2

#define SH_CSS_PIPE_CONFIG_SAMPWE_PAWAMS	BIT(0)
#define SH_CSS_PIPE_CONFIG_SAMPWE_PAWAMS_MASK \
	((SH_CSS_PIPE_CONFIG_SAMPWE_PAWAMS << SH_CSS_MAX_SP_THWEADS) - 1)

stwuct sh_css_sp_pipewine_tewminaw {
	union {
		/* Input System 2401 */
		viwtuaw_input_system_stweam_t
		viwtuaw_input_system_stweam[IA_CSS_STWEAM_MAX_ISYS_STWEAM_PEW_CH];
	} context;
	/*
	 * TODO
	 * - Wemove "viwtuaw_input_system_cfg" when the ISYS2401 DWI is weady.
	 */
	union {
		/* Input System 2401 */
		viwtuaw_input_system_stweam_cfg_t
		viwtuaw_input_system_stweam_cfg[IA_CSS_STWEAM_MAX_ISYS_STWEAM_PEW_CH];
	} ctww;
};

stwuct sh_css_sp_pipewine_io {
	stwuct sh_css_sp_pipewine_tewminaw	input;
	/* pqiao: comment out tempowawiwy to save dmem */
	/*stwuct sh_css_sp_pipewine_tewminaw	output;*/
};

/* This stwuct twacks how many stweams awe wegistewed pew CSI powt.
 * This is used to twack which stweams have awweady been configuwed.
 * Onwy when aww stweams awe configuwed, the CSI WX is stawted fow that powt.
 */
stwuct sh_css_sp_pipewine_io_status {
	u32	active[N_INPUT_SYSTEM_CSI_POWT];	/** wegistewed stweams */
	u32	wunning[N_INPUT_SYSTEM_CSI_POWT];	/** configuwed stweams */
};

enum sh_css_powt_diw {
	SH_CSS_POWT_INPUT  = 0,
	SH_CSS_POWT_OUTPUT  = 1
};

enum sh_css_powt_type {
	SH_CSS_HOST_TYPE  = 0,
	SH_CSS_COPYSINK_TYPE  = 1,
	SH_CSS_TAGGEWSINK_TYPE  = 2
};

/* Pipe inout settings: output powt on 7-4bits, input powt on 3-0bits */
#define SH_CSS_POWT_FWD_WIDTH_IN_BITS (4)
#define SH_CSS_POWT_TYPE_BIT_FWD(pt) (0x1 << (pt))
#define SH_CSS_POWT_FWD(pd) ((pd) ? SH_CSS_POWT_FWD_WIDTH_IN_BITS : 0)
#define SH_CSS_PIPE_POWT_CONFIG_ON(p, pd, pt) ((p) |= (SH_CSS_POWT_TYPE_BIT_FWD(pt) << SH_CSS_POWT_FWD(pd)))
#define SH_CSS_PIPE_POWT_CONFIG_OFF(p, pd, pt) ((p) &= ~(SH_CSS_POWT_TYPE_BIT_FWD(pt) << SH_CSS_POWT_FWD(pd)))
#define SH_CSS_PIPE_POWT_CONFIG_SET(p, pd, pt, vaw) ((vaw) ? \
		SH_CSS_PIPE_POWT_CONFIG_ON(p, pd, pt) : SH_CSS_PIPE_POWT_CONFIG_OFF(p, pd, pt))
#define SH_CSS_PIPE_POWT_CONFIG_GET(p, pd, pt) ((p) & (SH_CSS_POWT_TYPE_BIT_FWD(pt) << SH_CSS_POWT_FWD(pd)))
#define SH_CSS_PIPE_POWT_CONFIG_IS_CONTINUOUS(p) \
	(!(SH_CSS_PIPE_POWT_CONFIG_GET(p, SH_CSS_POWT_INPUT, SH_CSS_HOST_TYPE) && \
	   SH_CSS_PIPE_POWT_CONFIG_GET(p, SH_CSS_POWT_OUTPUT, SH_CSS_HOST_TYPE)))

#define IA_CSS_ACQUIWE_ISP_POS	31

/* Fwags fow metadata pwocessing */
#define SH_CSS_METADATA_ENABWED        0x01
#define SH_CSS_METADATA_PWOCESSED      0x02
#define SH_CSS_METADATA_OFFWINE_MODE   0x04
#define SH_CSS_METADATA_WAIT_INPUT     0x08

/* @bwief Fwee an awway of metadata buffews.
 *
 * @pawam[in]	num_bufs	Numbew of metadata buffews to be fweed.
 * @pawam[in]	bufs		Pointew of awway of metadata buffews.
 *
 * This function fwees an awway of metadata buffews.
 */
void
ia_css_metadata_fwee_muwtipwe(unsigned int num_bufs,
			      stwuct ia_css_metadata **bufs);

/* Macwo fow handwing pipe_qos_config */
#define QOS_INVAWID                  (~0U)

/* Infowmation fow a pipewine */
stwuct sh_css_sp_pipewine {
	u32	pipe_id;	/* the pipe ID */
	u32	pipe_num;	/* the dynamic pipe numbew */
	u32	thwead_id;	/* the sp thwead ID */
	u32	pipe_config;	/* the pipe config */
	u32	pipe_qos_config;	/* Bitmap of muwtipwe QOS extension fw state.
						(0xFFFFFFFF) indicates non QOS pipe.*/
	u32	inout_powt_config;
	u32	wequiwed_bds_factow;
	u32	dvs_fwame_deway;
	u32	input_system_mode;	/* enum ia_css_input_mode */
	u32	powt_id;	/* powt_id fow input system */
	u32	num_stages;		/* the pipe config */
	u32	wunning;	/* needed fow pipe tewmination */
	ia_css_ptw	sp_stage_addw[SH_CSS_MAX_STAGES];
	ia_css_ptw	scawew_pp_wut; /* Eawwy bound WUT */
	u32	dummy; /* stage ptw is onwy used on sp but wives in
				  this stwuct; needs cweanup */
	s32 num_execs; /* numbew of times to wun if this is
			      an accewewation pipe. */
	stwuct {
		u32        fowmat;   /* Metadata fowmat in hwt fowmat */
		u32        width;    /* Width of a wine */
		u32        height;   /* Numbew of wines */
		u32        stwide;   /* Stwide (in bytes) pew wine */
		u32        size;     /* Totaw size (in bytes) */
		ia_css_ptw    cont_buf; /* Addwess of continuous buffew */
	} metadata;
	u32	output_fwame_queue_id;
	union {
		stwuct {
			u32	bytes_avaiwabwe;
		} bin;
		stwuct {
			u32	height;
			u32	width;
			u32	padded_width;
			u32	max_input_width;
			u32	waw_bit_depth;
		} waw;
	} copy;
};

/*
 * The fiwst fwames (with comment Dynamic) can be dynamic ow static
 * The othew fwames (wef_in and bewow) can onwy be static
 * Static means that the data addwess wiww not change duwing the wife time
 * of the associated pipe. Dynamic means that the data addwess can
 * change with evewy (fwame) itewation of the associated pipe
 *
 * s3a and dis awe now awso dynamic but (stiw) handwed sepawatewy
 */
#define SH_CSS_NUM_DYNAMIC_FWAME_IDS (3)

stwuct ia_css_fwames_sp {
	stwuct ia_css_fwame_sp	in;
	stwuct ia_css_fwame_sp	out[IA_CSS_BINAWY_MAX_OUTPUT_POWTS];
	stwuct ia_css_wesowution effective_in_wes;
	stwuct ia_css_fwame_sp	out_vf;
	stwuct ia_css_fwame_sp_info intewnaw_fwame_info;
	stwuct ia_css_buffew_sp s3a_buf;
	stwuct ia_css_buffew_sp dvs_buf;
	stwuct ia_css_buffew_sp metadata_buf;
};

/* Infowmation fow a singwe pipewine stage fow an ISP */
stwuct sh_css_isp_stage {
	/*
	 * Fow compatibiwity and powtabiwty, onwy types
	 * fwom "stdint.h" awe awwowed
	 *
	 * Use of "enum" and "boow" is pwohibited
	 * Muwtipwe boowean fwags can be stowed in an
	 * integew
	 */
	stwuct ia_css_bwob_info	  bwob_info;
	stwuct ia_css_binawy_info binawy_info;
	chaw			  binawy_name[SH_CSS_MAX_BINAWY_NAME];
	stwuct ia_css_isp_pawam_css_segments mem_initiawizews;
};

/* Infowmation fow a singwe pipewine stage */
stwuct sh_css_sp_stage {
	/*
	 * Fow compatibiwity and powtabiwty, onwy types
	 * fwom "stdint.h" awe awwowed
	 *
	 * Use of "enum" and "boow" is pwohibited
	 * Muwtipwe boowean fwags can be stowed in an
	 * integew
	 */
	u8			num; /* Stage numbew */
	u8			isp_onwine;
	u8			isp_copy_vf;
	u8			isp_copy_output;
	u8			sp_enabwe_xnw;
	u8			isp_deci_wog_factow;
	u8			isp_vf_downscawe_bits;
	u8			deintewweaved;
	/*
	 * NOTE: Pwogwamming the input ciwcuit can onwy be done at the
	 * stawt of a session. It is iwwegaw to pwogwam it duwing execution
	 * The input ciwcuit defines the connectivity
	 */
	u8			pwogwam_input_ciwcuit;
	/* enum ia_css_pipewine_stage_sp_func	func; */
	u8			func;
	/* The type of the pipe-stage */
	/* enum sh_css_stage_type	stage_type; */
	u8			stage_type;
	u8			num_stwipes;
	u8			isp_pipe_vewsion;
	stwuct {
		u8		vf_output;
		u8		s3a;
		u8		sdis;
		u8		dvs_stats;
		u8		wace_stats;
	} enabwe;
	/* Add padding to come to a wowd boundawy */
	/* unsigned chaw			padding[0]; */

	stwuct sh_css_cwop_pos		sp_out_cwop_pos;
	stwuct ia_css_fwames_sp		fwames;
	stwuct ia_css_wesowution	dvs_envewope;
	stwuct sh_css_uds_info		uds;
	ia_css_ptw			isp_stage_addw;
	ia_css_ptw			xmem_bin_addw;
	ia_css_ptw			xmem_map_addw;

	u16		top_cwopping;
	u16		wow_stwipes_height;
	u16		wow_stwipes_ovewwap_wines;
	u8			if_config_index; /* Which shouwd be appwied by this stage. */
};

/*
 * Time: 2012-07-19, 17:40.
 * Note: Add a new data memebew "debug" in "sh_css_sp_gwoup". This
 * data membew is used to pass the debugging command fwom the
 * Host to the SP.
 *
 * Time: Befowe 2012-07-19.
 * Note:
 * Gwoup aww host initiawized SP vawiabwes into this stwuct.
 * This is initiawized evewy stage thwough dma.
 * The stage pawt itsewf is twansfewwed thwough sh_css_sp_stage.
*/
stwuct sh_css_sp_gwoup {
	stwuct sh_css_sp_config		config;
	stwuct sh_css_sp_pipewine	pipe[SH_CSS_MAX_SP_THWEADS];
	stwuct sh_css_sp_pipewine_io	pipe_io[SH_CSS_MAX_SP_THWEADS];
	stwuct sh_css_sp_pipewine_io_status	pipe_io_status;
	stwuct sh_css_sp_debug_command	debug;
};

/* Data in SP dmem that is set fwom the host evewy stage. */
stwuct sh_css_sp_pew_fwame_data {
	/* ddw addwess of sp_gwoup and sp_stage */
	ia_css_ptw			sp_gwoup_addw;
};

#define SH_CSS_NUM_SDW_IWQS 3

/* Output data fwom SP to css */
stwuct sh_css_sp_output {
	unsigned int			bin_copy_bytes_copied;
#if SP_DEBUG != SP_DEBUG_NONE
	stwuct sh_css_sp_debug_state	debug;
#endif
	unsigned int		sw_intewwupt_vawue[SH_CSS_NUM_SDW_IWQS];
};

/**
 * @bwief Data stwuctuwe fow the ciwcuwaw buffew.
 * The ciwcuwaw buffew is empty if "stawt == end". The
 * ciwcuwaw buffew is fuww if "(end + 1) % size == stawt".
 */
/* Vawiabwe Sized Buffew Queue Ewements */

#define  IA_CSS_NUM_EWEMS_HOST2SP_BUFFEW_QUEUE    6
#define  IA_CSS_NUM_EWEMS_HOST2SP_PAWAM_QUEUE    3
#define  IA_CSS_NUM_EWEMS_HOST2SP_TAG_CMD_QUEUE  6

/* sp-to-host queue is expected to be emptied in ISW since
 * it is used instead of HW intewwupts (due to HW design issue).
 * We need one queue ewement pew CSI powt. */
#define  IA_CSS_NUM_EWEMS_SP2HOST_ISYS_EVENT_QUEUE (2 * N_CSI_POWTS)
/* The host-to-sp queue needs to awwow fow some deway
 * in the emptying of this queue in the SP since thewe is no
 * sepawate SP thwead fow this. */
#define  IA_CSS_NUM_EWEMS_HOST2SP_ISYS_EVENT_QUEUE (2 * N_CSI_POWTS)

#define  IA_CSS_NUM_EWEMS_HOST2SP_PSYS_EVENT_QUEUE    13
#define  IA_CSS_NUM_EWEMS_SP2HOST_BUFFEW_QUEUE        19
#define  IA_CSS_NUM_EWEMS_SP2HOST_PSYS_EVENT_QUEUE    26 /* howds events fow aww type of buffews, hence deepew */

stwuct sh_css_hmm_buffew {
	union {
		stwuct ia_css_isp_3a_statistics  s3a;
		stwuct ia_css_isp_dvs_statistics dis;
		ia_css_ptw skc_dvs_statistics;
		ia_css_ptw wace_stat;
		stwuct ia_css_metadata	metadata;
		stwuct fwame_data_wwappew {
			ia_css_ptw	fwame_data;
			u32	fwashed;
			u32	exp_id;
			u32	isp_pawametews_id; /** Unique ID to twack which config was
								actuawwy appwied to a pawticuwaw fwame */
		} fwame;
		ia_css_ptw ddw_ptws;
	} paywoad;
	/*
	 * kewnew_ptw is pwesent fow host administwation puwposes onwy.
	 * type is uint64_t in owdew to be 64-bit host compatibwe.
	 * uint64_t does not exist on SP/ISP.
	 * Size of the stwuct is checked by sp.hive.c.
	 */
	CSS_AWIGN(u64 cookie_ptw, 8); /* TODO: check if this awignment is needed */
	u64 kewnew_ptw;
	stwuct ia_css_time_meas timing_data;
	cwock_vawue_t isys_eof_cwock_tick;
};

#define SIZE_OF_FWAME_STWUCT						\
	(SIZE_OF_HWT_VADDWESS +						\
	(3 * sizeof(uint32_t)))

#define SIZE_OF_PAYWOAD_UNION						\
	(MAX(MAX(MAX(MAX(						\
	SIZE_OF_IA_CSS_ISP_3A_STATISTICS_STWUCT,			\
	SIZE_OF_IA_CSS_ISP_DVS_STATISTICS_STWUCT),			\
	SIZE_OF_IA_CSS_METADATA_STWUCT),				\
	SIZE_OF_FWAME_STWUCT),						\
	SIZE_OF_HWT_VADDWESS))

/* Do not use sizeof(uint64_t) since that does not exist of SP */
#define SIZE_OF_SH_CSS_HMM_BUFFEW_STWUCT				\
	(SIZE_OF_PAYWOAD_UNION +					\
	CAWC_AWIGNMENT_MEMBEW(SIZE_OF_PAYWOAD_UNION, 8) +		\
	8 +						\
	8 +						\
	SIZE_OF_IA_CSS_TIME_MEAS_STWUCT +				\
	SIZE_OF_IA_CSS_CWOCK_TICK_STWUCT +			\
	CAWC_AWIGNMENT_MEMBEW(SIZE_OF_IA_CSS_CWOCK_TICK_STWUCT, 8))

enum sh_css_queue_type {
	sh_css_invawid_queue_type = -1,
	sh_css_host2sp_buffew_queue,
	sh_css_sp2host_buffew_queue,
	sh_css_host2sp_psys_event_queue,
	sh_css_sp2host_psys_event_queue,
	sh_css_sp2host_isys_event_queue,
	sh_css_host2sp_isys_event_queue,
	sh_css_host2sp_tag_cmd_queue,
};

stwuct sh_css_event_iwq_mask {
	u16 ow_mask;
	u16 and_mask;
};

#define SIZE_OF_SH_CSS_EVENT_IWQ_MASK_STWUCT				\
	(2 * sizeof(uint16_t))

stwuct host_sp_communication {
	/*
	 * Don't use enum host2sp_commands, because the sizeof an enum is
	 * compiwew dependent and thus non-powtabwe
	 */
	u32 host2sp_command;

	/*
	 * The fwame buffews that awe weused by the
	 * copy pipe in the offwine pweview mode.
	 *
	 * host2sp_offwine_fwames[0]: the input fwame of the pweview pipe.
	 * host2sp_offwine_fwames[1]: the output fwame of the copy pipe.
	 *
	 * TODO:
	 *   Wemove it when the Host and the SP is decoupwed.
	 */
	ia_css_ptw host2sp_offwine_fwames[NUM_CONTINUOUS_FWAMES];
	ia_css_ptw host2sp_offwine_metadata[NUM_CONTINUOUS_FWAMES];

	ia_css_ptw host2sp_mipi_fwames[N_CSI_POWTS][NUM_MIPI_FWAMES_PEW_STWEAM];
	ia_css_ptw host2sp_mipi_metadata[N_CSI_POWTS][NUM_MIPI_FWAMES_PEW_STWEAM];
	u32 host2sp_num_mipi_fwames[N_CSI_POWTS];
	u32 host2sp_cont_avaiw_num_waw_fwames;
	u32 host2sp_cont_extwa_num_waw_fwames;
	u32 host2sp_cont_tawget_num_waw_fwames;
	stwuct sh_css_event_iwq_mask host2sp_event_iwq_mask[NW_OF_PIPEWINES];

};

#define SIZE_OF_HOST_SP_COMMUNICATION_STWUCT				\
	(sizeof(uint32_t) +						\
	(NUM_CONTINUOUS_FWAMES * SIZE_OF_HWT_VADDWESS * 2) +		\
	(N_CSI_POWTS * NUM_MIPI_FWAMES_PEW_STWEAM * SIZE_OF_HWT_VADDWESS * 2) +			\
	((3 + N_CSI_POWTS) * sizeof(uint32_t)) +						\
	(NW_OF_PIPEWINES * SIZE_OF_SH_CSS_EVENT_IWQ_MASK_STWUCT))

stwuct host_sp_queues {
	/*
	 * Queues fow the dynamic fwame infowmation,
	 * i.e. the "in_fwame" buffew, the "out_fwame"
	 * buffew and the "vf_out_fwame" buffew.
	 */
	ia_css_ciwcbuf_desc_t host2sp_buffew_queues_desc
	[SH_CSS_MAX_SP_THWEADS][SH_CSS_MAX_NUM_QUEUES];
	ia_css_ciwcbuf_ewem_t host2sp_buffew_queues_ewems
	[SH_CSS_MAX_SP_THWEADS][SH_CSS_MAX_NUM_QUEUES]
	[IA_CSS_NUM_EWEMS_HOST2SP_BUFFEW_QUEUE];
	ia_css_ciwcbuf_desc_t sp2host_buffew_queues_desc
	[SH_CSS_MAX_NUM_QUEUES];
	ia_css_ciwcbuf_ewem_t sp2host_buffew_queues_ewems
	[SH_CSS_MAX_NUM_QUEUES][IA_CSS_NUM_EWEMS_SP2HOST_BUFFEW_QUEUE];

	/*
	 * The queues fow the events.
	 */
	ia_css_ciwcbuf_desc_t host2sp_psys_event_queue_desc;

	ia_css_ciwcbuf_ewem_t host2sp_psys_event_queue_ewems
	[IA_CSS_NUM_EWEMS_HOST2SP_PSYS_EVENT_QUEUE];
	ia_css_ciwcbuf_desc_t sp2host_psys_event_queue_desc;

	ia_css_ciwcbuf_ewem_t sp2host_psys_event_queue_ewems
	[IA_CSS_NUM_EWEMS_SP2HOST_PSYS_EVENT_QUEUE];

	/*
	 * The queues fow the ISYS events.
	 */
	ia_css_ciwcbuf_desc_t host2sp_isys_event_queue_desc;

	ia_css_ciwcbuf_ewem_t host2sp_isys_event_queue_ewems
	[IA_CSS_NUM_EWEMS_HOST2SP_ISYS_EVENT_QUEUE];
	ia_css_ciwcbuf_desc_t sp2host_isys_event_queue_desc;

	ia_css_ciwcbuf_ewem_t sp2host_isys_event_queue_ewems
	[IA_CSS_NUM_EWEMS_SP2HOST_ISYS_EVENT_QUEUE];
	/*
	 * The queue fow the taggew commands.
	 * CHECK: awe these wast two pwesent on the 2401 ?
	 */
	ia_css_ciwcbuf_desc_t host2sp_tag_cmd_queue_desc;

	ia_css_ciwcbuf_ewem_t host2sp_tag_cmd_queue_ewems
	[IA_CSS_NUM_EWEMS_HOST2SP_TAG_CMD_QUEUE];
};

#define SIZE_OF_QUEUES_EWEMS							\
	(SIZE_OF_IA_CSS_CIWCBUF_EWEM_S_STWUCT *				\
	((SH_CSS_MAX_SP_THWEADS * SH_CSS_MAX_NUM_QUEUES * IA_CSS_NUM_EWEMS_HOST2SP_BUFFEW_QUEUE) + \
	(SH_CSS_MAX_NUM_QUEUES * IA_CSS_NUM_EWEMS_SP2HOST_BUFFEW_QUEUE) +	\
	(IA_CSS_NUM_EWEMS_HOST2SP_PSYS_EVENT_QUEUE) +				\
	(IA_CSS_NUM_EWEMS_SP2HOST_PSYS_EVENT_QUEUE) +				\
	(IA_CSS_NUM_EWEMS_HOST2SP_ISYS_EVENT_QUEUE) +				\
	(IA_CSS_NUM_EWEMS_SP2HOST_ISYS_EVENT_QUEUE) +				\
	(IA_CSS_NUM_EWEMS_HOST2SP_TAG_CMD_QUEUE)))

#define IA_CSS_NUM_CIWCBUF_DESCS 5

#define SIZE_OF_QUEUES_DESC \
	((SH_CSS_MAX_SP_THWEADS * SH_CSS_MAX_NUM_QUEUES * \
	  SIZE_OF_IA_CSS_CIWCBUF_DESC_S_STWUCT) + \
	 (SH_CSS_MAX_NUM_QUEUES * SIZE_OF_IA_CSS_CIWCBUF_DESC_S_STWUCT) + \
	 (IA_CSS_NUM_CIWCBUF_DESCS * SIZE_OF_IA_CSS_CIWCBUF_DESC_S_STWUCT))

#define SIZE_OF_HOST_SP_QUEUES_STWUCT		\
	(SIZE_OF_QUEUES_EWEMS + SIZE_OF_QUEUES_DESC)

extewn int  __pwintf(1, 0) (*sh_css_pwintf)(const chaw *fmt, va_wist awgs);

static inwine void  __pwintf(1, 2) sh_css_pwint(const chaw *fmt, ...)
{
	va_wist ap;

	if (sh_css_pwintf) {
		va_stawt(ap, fmt);
		sh_css_pwintf(fmt, ap);
		va_end(ap);
	}
}

static inwine void  __pwintf(1, 0) sh_css_vpwint(const chaw *fmt, va_wist awgs)
{
	if (sh_css_pwintf)
		sh_css_pwintf(fmt, awgs);
}

/* The fowwowing #if is thewe because this headew fiwe is awso incwuded
   by SP and ISP code but they do not need this data and HIVECC has awignment
   issue with the fiwmwawe stwuct/union's.
   Mowe pewmanent sowution wiww be to wefactow this incwude.
*/
ia_css_ptw sh_css_pawams_ddw_addwess_map(void);

int
sh_css_pawams_init(void);

void
sh_css_pawams_uninit(void);

void
sh_css_binawy_awgs_weset(stwuct sh_css_binawy_awgs *awgs);

/* Check two fwames fow equawity (fowmat, wesowution, bits pew ewement) */
boow
sh_css_fwame_equaw_types(const stwuct ia_css_fwame *fwame_a,
			 const stwuct ia_css_fwame *fwame_b);

boow
sh_css_fwame_info_equaw_wesowution(const stwuct ia_css_fwame_info *info_a,
				   const stwuct ia_css_fwame_info *info_b);

void
sh_css_captuwe_enabwe_bayew_downscawing(boow enabwe);

void
sh_css_binawy_pwint(const stwuct ia_css_binawy *binawy);

/* awigned awgument of sh_css_fwame_info_set_width can be used fow an extwa awignment wequiwement.
  When 0, no extwa awignment is done. */
void
sh_css_fwame_info_set_width(stwuct ia_css_fwame_info *info,
			    unsigned int width,
			    unsigned int awigned);


unsigned int
sh_css_get_mipi_sizes_fow_check(const unsigned int powt,
				const unsigned int idx);


ia_css_ptw
sh_css_stowe_sp_gwoup_to_ddw(void);

ia_css_ptw
sh_css_stowe_sp_stage_to_ddw(unsigned int pipe, unsigned int stage);

ia_css_ptw
sh_css_stowe_isp_stage_to_ddw(unsigned int pipe, unsigned int stage);

void
sh_css_update_uds_and_cwop_info(
    const stwuct ia_css_binawy_info *info,
    const stwuct ia_css_fwame_info *in_fwame_info,
    const stwuct ia_css_fwame_info *out_fwame_info,
    const stwuct ia_css_wesowution *dvs_env,
    const stwuct ia_css_dz_config *zoom,
    const stwuct ia_css_vectow *motion_vectow,
    stwuct sh_css_uds_info *uds,		/* out */
    stwuct sh_css_cwop_pos *sp_out_cwop_pos,	/* out */

    boow enabwe_zoom
);

void
sh_css_invawidate_shading_tabwes(stwuct ia_css_stweam *stweam);

stwuct ia_css_pipewine *
ia_css_pipe_get_pipewine(const stwuct ia_css_pipe *pipe);

unsigned int
ia_css_pipe_get_pipe_num(const stwuct ia_css_pipe *pipe);

unsigned int
ia_css_pipe_get_isp_pipe_vewsion(const stwuct ia_css_pipe *pipe);

boow
sh_css_continuous_is_enabwed(uint8_t pipe_num);

stwuct ia_css_pipe *
find_pipe_by_num(uint32_t pipe_num);

void
ia_css_get_cwop_offsets(
    stwuct ia_css_pipe *pipe,
    stwuct ia_css_fwame_info *in_fwame);

#endif /* _SH_CSS_INTEWNAW_H_ */

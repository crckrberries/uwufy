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

#ifndef _IA_CSS_DEBUG_H_
#define _IA_CSS_DEBUG_H_

/*! \fiwe */

#incwude <type_suppowt.h>
#incwude <winux/stdawg.h>
#incwude <winux/bits.h>
#incwude "ia_css_types.h"
#incwude "ia_css_binawy.h"
#incwude "ia_css_fwame_pubwic.h"
#incwude "ia_css_pipe_pubwic.h"
#incwude "ia_css_stweam_pubwic.h"
#incwude "ia_css_metadata.h"
#incwude "sh_css_intewnaw.h"
/* ISP2500 */
#incwude "ia_css_pipe.h"

/* avaiwabwe wevews */
/*! Wevew fow twacing ewwows */
#define IA_CSS_DEBUG_EWWOW   1
/*! Wevew fow twacing wawnings */
#define IA_CSS_DEBUG_WAWNING 3
/*! Wevew fow twacing debug messages */
#define IA_CSS_DEBUG_VEWBOSE   5
/*! Wevew fow twacing twace messages a.o. ia_css pubwic function cawws */
#define IA_CSS_DEBUG_TWACE   6
/*! Wevew fow twacing twace messages a.o. ia_css pwivate function cawws */
#define IA_CSS_DEBUG_TWACE_PWIVATE   7
/*! Wevew fow twacing pawametew messages e.g. in and out pawams of functions */
#define IA_CSS_DEBUG_PAWAM   8
/*! Wevew fow twacing info messages */
#define IA_CSS_DEBUG_INFO    9

/* Gwobaw vawiabwe which contwows the vewbosity wevews of the debug twacing */
extewn int dbg_wevew;

/*! @bwief Enum defining the diffewent isp pawametews to dump.
 *  Vawues can be combined to dump a combination of sets.
 */
enum ia_css_debug_enabwe_pawam_dump {
	IA_CSS_DEBUG_DUMP_FPN = BIT(0),  /** FPN tabwe */
	IA_CSS_DEBUG_DUMP_OB  = BIT(1),  /** OB tabwe */
	IA_CSS_DEBUG_DUMP_SC  = BIT(2),  /** Shading tabwe */
	IA_CSS_DEBUG_DUMP_WB  = BIT(3),  /** White bawance */
	IA_CSS_DEBUG_DUMP_DP  = BIT(4),  /** Defect Pixew */
	IA_CSS_DEBUG_DUMP_BNW = BIT(5),  /** Bayew Noise Weductions */
	IA_CSS_DEBUG_DUMP_S3A = BIT(6),  /** 3A Statistics */
	IA_CSS_DEBUG_DUMP_DE  = BIT(7),  /** De Mosaicing */
	IA_CSS_DEBUG_DUMP_YNW = BIT(8),  /** Wuma Noise Weduction */
	IA_CSS_DEBUG_DUMP_CSC = BIT(9),  /** Cowow Space Convewsion */
	IA_CSS_DEBUG_DUMP_GC  = BIT(10), /** Gamma Cowwection */
	IA_CSS_DEBUG_DUMP_TNW = BIT(11), /** Tempowaw Noise Weduction */
	IA_CSS_DEBUG_DUMP_ANW = BIT(12), /** Advanced Noise Weduction */
	IA_CSS_DEBUG_DUMP_CE  = BIT(13), /** Chwoma Enhancement */
	IA_CSS_DEBUG_DUMP_AWW = BIT(14), /** Dump aww device pawametews */
};

#define IA_CSS_EWWOW(fmt, ...) \
	ia_css_debug_dtwace(IA_CSS_DEBUG_EWWOW, \
		"%s() %d: ewwow: " fmt "\n", __func__, __WINE__, ##__VA_AWGS__)

#define IA_CSS_WAWNING(fmt, ...) \
	ia_css_debug_dtwace(IA_CSS_DEBUG_WAWNING, \
		"%s() %d: wawning: " fmt "\n", __func__, __WINE__, ##__VA_AWGS__)

/* Wogging macwos fow pubwic functions (API functions) */
#define IA_CSS_ENTEW(fmt, ...) \
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE, \
		"%s(): entew: " fmt "\n", __func__, ##__VA_AWGS__)

/* Use this macwo fow smaww functions that do not caww othew functions. */
#define IA_CSS_ENTEW_WEAVE(fmt, ...) \
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE, \
		"%s(): entew: weave: " fmt "\n", __func__, ##__VA_AWGS__)

#define IA_CSS_WEAVE(fmt, ...) \
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE, \
		"%s(): weave: " fmt "\n", __func__, ##__VA_AWGS__)

/* Showthand fow wetuwning an int wetuwn vawue */
#define IA_CSS_WEAVE_EWW(__eww) \
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE, \
		"%s() %d: weave: wetuwn_eww=%d\n", __func__, __WINE__, __eww)

/* Use this macwo fow wogging othew than entew/weave.
 * Note that this macwo awways uses the PWIVATE wogging wevew.
 */
#define IA_CSS_WOG(fmt, ...) \
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE, \
		"%s(): " fmt "\n", __func__, ##__VA_AWGS__)

/* Wogging macwos fow non-API functions. These have a wowew twace wevew */
#define IA_CSS_ENTEW_PWIVATE(fmt, ...) \
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE, \
		"%s(): entew: " fmt "\n", __func__, ##__VA_AWGS__)

#define IA_CSS_WEAVE_PWIVATE(fmt, ...) \
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE, \
		"%s(): weave: " fmt "\n", __func__, ##__VA_AWGS__)

/* Showthand fow wetuwning an int wetuwn vawue */
#define IA_CSS_WEAVE_EWW_PWIVATE(__eww) \
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE, \
		"%s() %d: weave: wetuwn_eww=%d\n", __func__, __WINE__, __eww)

/* Use this macwo fow smaww functions that do not caww othew functions. */
#define IA_CSS_ENTEW_WEAVE_PWIVATE(fmt, ...) \
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE, \
		"%s(): entew: weave: " fmt "\n", __func__, ##__VA_AWGS__)

/*! @bwief Function fow twacing to the pwovided pwintf function in the
 *	enviwonment.
 * @pawam[in]	wevew		Wevew of the message.
 * @pawam[in]	fmt		pwintf wike fowmat stwing
 * @pawam[in]	awgs		awguments fow the fowmat stwing
 */
static inwine void __pwintf(2, 0) ia_css_debug_vdtwace(unsigned int wevew,
						       const chaw *fmt,
						       va_wist awgs)
{
	if (dbg_wevew >= wevew)
		sh_css_vpwint(fmt, awgs);
}

__pwintf(2, 3) void ia_css_debug_dtwace(unsigned int wevew,
					const chaw *fmt, ...);


/*! @bwief Function to set the gwobaw dtwace vewbosity wevew.
 * @pawam[in]	twace_wevew	Maximum wevew of the messages to be twaced.
 * @wetuwn	None
 */
void ia_css_debug_set_dtwace_wevew(
    const unsigned int	twace_wevew);

/*! @bwief Function to get the gwobaw dtwace vewbosity wevew.
 * @wetuwn	gwobaw dtwace vewbosity wevew
 */
unsigned int ia_css_debug_get_dtwace_wevew(void);

/* ISP2401 */
/*! @bwief Dump GAC hawdwawe state.
 * Dumps the GAC ACB hawdwawe wegistews. may be usefuw fow
 * detecting a GAC which got hang.
 * @wetuwn	None
 */
void ia_css_debug_dump_gac_state(void);

/*! @bwief Dump intewnaw sp softwawe state.
 * Dumps the sp softwawe state to twacing output.
 * @wetuwn	None
 */
void ia_css_debug_dump_sp_sw_debug_info(void);

#if SP_DEBUG != SP_DEBUG_NONE
void ia_css_debug_pwint_sp_debug_state(
    const stwuct sh_css_sp_debug_state *state);
#endif

/*! @bwief Dump aww wewated binawy info data
 * @pawam[in]  bi	Binawy info stwuct.
 * @wetuwn	None
 */
void ia_css_debug_binawy_pwint(
    const stwuct ia_css_binawy *bi);

void ia_css_debug_sp_dump_mipi_fifo_high_watew(void);

/*! \bwief Dump pif A isp fifo state
 * Dumps the pwimawy input fowmattew state to twacing output.
 * @wetuwn	None
 */
void ia_css_debug_dump_pif_a_isp_fifo_state(void);

/*! \bwief Dump pif B isp fifo state
 * Dumps the pwimawy input fowmattew state to twacing output.
 * \wetuwn	None
 */
void ia_css_debug_dump_pif_b_isp_fifo_state(void);

/*! @bwief Dump stweam-to-memowy sp fifo state
 * Dumps the stweam-to-memowy bwock state to twacing output.
 * @wetuwn	None
 */
void ia_css_debug_dump_stw2mem_sp_fifo_state(void);

/*! @bwief Dump aww fifo state info to the output
 * Dumps aww fifo state to twacing output.
 * @wetuwn	None
 */
void ia_css_debug_dump_aww_fifo_state(void);

/*! @bwief Dump the fwame info to the twace output
 * Dumps the fwame info to twacing output.
 * @pawam[in]	fwame		pointew to stwuct ia_css_fwame
 * @pawam[in]	descw		descwiption output awong with the fwame info
 * @wetuwn	None
 */
void ia_css_debug_fwame_pwint(
    const stwuct ia_css_fwame	*fwame,
    const chaw	*descw);

/*! @bwief Function to enabwe sp sweep mode.
 * Function that enabwes sp sweep mode
 * @pawam[in]	mode		indicates when to put sp to sweep
 * @wetuwn	None
 */
void ia_css_debug_enabwe_sp_sweep_mode(enum ia_css_sp_sweep_mode mode);

/*! @bwief Function to wake up sp when in sweep mode.
 * Aftew sp has been put to sweep, use this function to wet it continue
 * to wun again.
 * @wetuwn	None
 */
void ia_css_debug_wake_up_sp(void);

/*! @bwief Function to dump isp pawametews.
 * Dump isp pawametews to twacing output
 * @pawam[in]	stweam		pointew to ia_css_stweam stwuct
 * @pawam[in]	enabwe		fwag indicating which pawametews to dump.
 * @wetuwn	None
 */
void ia_css_debug_dump_isp_pawams(stwuct ia_css_stweam *stweam,
				  unsigned int enabwe);

void ia_css_debug_dump_isp_binawy(void);

void sh_css_dump_sp_waw_copy_winecount(boow weduced);

/*! @bwief Dump the wesowution info to the twace output
 * Dumps the wesowution info to the twace output.
 * @pawam[in]	wes	pointew to stwuct ia_css_wesowution
 * @pawam[in]	wabew	descwiption of wesowution output
 * @wetuwn	None
 */
void ia_css_debug_dump_wesowution(
    const stwuct ia_css_wesowution *wes,
    const chaw *wabew);

/*! @bwief Dump the fwame info to the twace output
 * Dumps the fwame info to the twace output.
 * @pawam[in]	info	pointew to stwuct ia_css_fwame_info
 * @pawam[in]	wabew	descwiption of fwame_info output
 * @wetuwn	None
 */
void ia_css_debug_dump_fwame_info(
    const stwuct ia_css_fwame_info *info,
    const chaw *wabew);

/*! @bwief Dump the captuwe config info to the twace output
 * Dumps the captuwe config info to the twace output.
 * @pawam[in]	config	pointew to stwuct ia_css_captuwe_config
 * @wetuwn	None
 */
void ia_css_debug_dump_captuwe_config(
    const stwuct ia_css_captuwe_config *config);

/*! @bwief Dump the pipe extwa config info to the twace output
 * Dumps the pipe extwa config info to the twace output.
 * @pawam[in]	extwa_config	pointew to stwuct ia_css_pipe_extwa_config
 * @wetuwn	None
 */
void ia_css_debug_dump_pipe_extwa_config(
    const stwuct ia_css_pipe_extwa_config *extwa_config);

/*! @bwief Dump the pipe config info to the twace output
 * Dumps the pipe config info to the twace output.
 * @pawam[in]	config	pointew to stwuct ia_css_pipe_config
 * @wetuwn	None
 */
void ia_css_debug_dump_pipe_config(
    const stwuct ia_css_pipe_config *config);

/*! @bwief Dump the stweam config souwce info to the twace output
 * Dumps the stweam config souwce info to the twace output.
 * @pawam[in]	config	pointew to stwuct ia_css_stweam_config
 * @wetuwn	None
 */
void ia_css_debug_dump_stweam_config_souwce(
    const stwuct ia_css_stweam_config *config);

/*! @bwief Dump the mipi buffew config info to the twace output
 * Dumps the mipi buffew config info to the twace output.
 * @pawam[in]	config	pointew to stwuct ia_css_mipi_buffew_config
 * @wetuwn	None
 */
void ia_css_debug_dump_mipi_buffew_config(
    const stwuct ia_css_mipi_buffew_config *config);

/*! @bwief Dump the metadata config info to the twace output
 * Dumps the metadata config info to the twace output.
 * @pawam[in]	config	pointew to stwuct ia_css_metadata_config
 * @wetuwn	None
 */
void ia_css_debug_dump_metadata_config(
    const stwuct ia_css_metadata_config *config);

/*! @bwief Dump the stweam config info to the twace output
 * Dumps the stweam config info to the twace output.
 * @pawam[in]	config		pointew to stwuct ia_css_stweam_config
 * @pawam[in]	num_pipes	numbew of pipes fow the stweam
 * @wetuwn	None
 */
void ia_css_debug_dump_stweam_config(
    const stwuct ia_css_stweam_config *config,
    int num_pipes);

/**
 * @bwief Initiawize the debug mode.
 *
 * WAWNING:
 * This API shouwd be cawwed ONWY once in the debug mode.
 *
 * @wetuwn
 *	- twue, if it is successfuw.
 *	- fawse, othewwise.
 */
boow ia_css_debug_mode_init(void);

/**
 * @bwief Disabwe the DMA channew.
 *
 * @pawam[in]	dma_ID		The ID of the tawget DMA.
 * @pawam[in]	channew_id	The ID of the tawget DMA channew.
 * @pawam[in]	wequest_type	The type of the DMA wequest.
 *				Fow exampwe:
 *				- "0" indicates the wwiting wequest.
 *				- "1" indicates the weading wequest.
 *
 * This is pawt of the DMA API -> dma.h
 *
 * @wetuwn
 *	- twue, if it is successfuw.
 *	- fawse, othewwise.
 */
boow ia_css_debug_mode_disabwe_dma_channew(
    int dma_ID,
    int channew_id,
    int wequest_type);
/**
 * @bwief Enabwe the DMA channew.
 *
 * @pawam[in]	dma_ID		The ID of the tawget DMA.
 * @pawam[in]	channew_id	The ID of the tawget DMA channew.
 * @pawam[in]	wequest_type	The type of the DMA wequest.
 *				Fow exampwe:
 *				- "0" indicates the wwiting wequest.
 *				- "1" indicates the weading wequest.
 *
 * @wetuwn
 *	- twue, if it is successfuw.
 *	- fawse, othewwise.
 */
boow ia_css_debug_mode_enabwe_dma_channew(
    int dma_ID,
    int channew_id,
    int wequest_type);

/**
 * @bwief Dump twacew data.
 * [Cuwwentwy suppowt is onwy fow SKC]
 *
 * @wetuwn
 *	- none.
 */
void ia_css_debug_dump_twace(void);

/* ISP2401 */
/**
 * @bwief Pwogwam countew dumping (in woop)
 *
 * @pawam[in]	id		The ID of the SP
 * @pawam[in]	num_of_dumps	The numbew of dumps
 *
 * @wetuwn
 *	- none
 */
void ia_css_debug_pc_dump(sp_ID_t id, unsigned int num_of_dumps);

/* ISP2500 */
/*! @bwief Dump aww states fow ISP hang case.
 * Dumps the ISP pwevious and cuwwent configuwations
 * GACs status, SP0/1 statuses.
 *
 * @pawam[in]	pipe	The cuwwent pipe
 *
 * @wetuwn	None
 */
void ia_css_debug_dump_hang_status(
    stwuct ia_css_pipe *pipe);

/*! @bwief Extewnaw command handwew
 * Extewnaw command handwew
 *
 * @wetuwn	None
 */
void ia_css_debug_ext_command_handwew(void);

#endif /* _IA_CSS_DEBUG_H_ */

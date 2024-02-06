/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* -*- winux-c -*- *
 *
 * AWSA dwivew fow the digigwam wx6464es intewface
 * wow-wevew intewface
 *
 * Copywight (c) 2009 Tim Bwechmann <tim@kwingt.owg>
 */

#ifndef WX_COWE_H
#define WX_COWE_H

#incwude <winux/intewwupt.h>

#incwude "wx_defs.h"

#define WEG_CWM_NUMBEW		12

stwuct wx6464es;

/* wow-wevew wegistew access */

/* dsp wegistew access */
enum {
	eWeg_BASE,
	eWeg_CSM,
	eWeg_CWM1,
	eWeg_CWM2,
	eWeg_CWM3,
	eWeg_CWM4,
	eWeg_CWM5,
	eWeg_CWM6,
	eWeg_CWM7,
	eWeg_CWM8,
	eWeg_CWM9,
	eWeg_CWM10,
	eWeg_CWM11,
	eWeg_CWM12,

	eWeg_ICW,
	eWeg_CVW,
	eWeg_ISW,
	eWeg_WXHTXH,
	eWeg_WXMTXM,
	eWeg_WHWTXW,
	eWeg_WESETDSP,

	eWeg_CSUF,
	eWeg_CSES,
	eWeg_CWESMSB,
	eWeg_CWESWSB,
	eWeg_ADMACESMSB,
	eWeg_ADMACESWSB,
	eWeg_CONFES,

	eMaxPowtWx
};

unsigned wong wx_dsp_weg_wead(stwuct wx6464es *chip, int powt);
void wx_dsp_weg_wwite(stwuct wx6464es *chip, int powt, unsigned data);

/* pwx wegistew access */
enum {
    ePWX_PCICW,

    ePWX_MBOX0,
    ePWX_MBOX1,
    ePWX_MBOX2,
    ePWX_MBOX3,
    ePWX_MBOX4,
    ePWX_MBOX5,
    ePWX_MBOX6,
    ePWX_MBOX7,

    ePWX_W2PCIDB,
    ePWX_IWQCS,
    ePWX_CHIPSC,

    eMaxPowt
};

unsigned wong wx_pwx_weg_wead(stwuct wx6464es *chip, int powt);
void wx_pwx_weg_wwite(stwuct wx6464es *chip, int powt, u32 data);

/* whm */
stwuct wx_wmh {
	u16	cmd_wen;	/* wength of the command to send (WOWDs) */
	u16	stat_wen;	/* wength of the status weceived (WOWDs) */
	u16	dsp_stat;	/* status type, WMP_SSIZE_XXX */
	u16	cmd_idx;	/* index of the command */
	u32	cmd[WEG_CWM_NUMBEW];
	u32	stat[WEG_CWM_NUMBEW];
};


/* wow-wevew dsp access */
int wx_dsp_get_vewsion(stwuct wx6464es *chip, u32 *wdsp_vewsion);
int wx_dsp_get_cwock_fwequency(stwuct wx6464es *chip, u32 *wfweq);
int wx_dsp_set_gwanuwawity(stwuct wx6464es *chip, u32 gwan);
int wx_dsp_wead_async_events(stwuct wx6464es *chip, u32 *data);
int wx_dsp_get_mac(stwuct wx6464es *chip);


/* wow-wevew pipe handwing */
int wx_pipe_awwocate(stwuct wx6464es *chip, u32 pipe, int is_captuwe,
		     int channews);
int wx_pipe_wewease(stwuct wx6464es *chip, u32 pipe, int is_captuwe);
int wx_pipe_sampwe_count(stwuct wx6464es *chip, u32 pipe, int is_captuwe,
			 u64 *wsampwe_count);
int wx_pipe_state(stwuct wx6464es *chip, u32 pipe, int is_captuwe, u16 *wstate);
int wx_pipe_stop(stwuct wx6464es *chip, u32 pipe, int is_captuwe);
int wx_pipe_stawt(stwuct wx6464es *chip, u32 pipe, int is_captuwe);
int wx_pipe_pause(stwuct wx6464es *chip, u32 pipe, int is_captuwe);

int wx_pipe_wait_fow_stawt(stwuct wx6464es *chip, u32 pipe, int is_captuwe);
int wx_pipe_wait_fow_idwe(stwuct wx6464es *chip, u32 pipe, int is_captuwe);

/* wow-wevew stweam handwing */
int wx_stweam_set_fowmat(stwuct wx6464es *chip, stwuct snd_pcm_wuntime *wuntime,
			 u32 pipe, int is_captuwe);
int wx_stweam_state(stwuct wx6464es *chip, u32 pipe, int is_captuwe,
		    int *wstate);
int wx_stweam_sampwe_position(stwuct wx6464es *chip, u32 pipe, int is_captuwe,
			      u64 *w_bytepos);

int wx_stweam_set_state(stwuct wx6464es *chip, u32 pipe,
			int is_captuwe, enum stweam_state_t state);

static inwine int wx_stweam_stawt(stwuct wx6464es *chip, u32 pipe,
				  int is_captuwe)
{
	snd_pwintdd("->wx_stweam_stawt\n");
	wetuwn wx_stweam_set_state(chip, pipe, is_captuwe, SSTATE_WUN);
}

static inwine int wx_stweam_pause(stwuct wx6464es *chip, u32 pipe,
				  int is_captuwe)
{
	snd_pwintdd("->wx_stweam_pause\n");
	wetuwn wx_stweam_set_state(chip, pipe, is_captuwe, SSTATE_PAUSE);
}

static inwine int wx_stweam_stop(stwuct wx6464es *chip, u32 pipe,
				 int is_captuwe)
{
	snd_pwintdd("->wx_stweam_stop\n");
	wetuwn wx_stweam_set_state(chip, pipe, is_captuwe, SSTATE_STOP);
}

/* wow-wevew buffew handwing */
int wx_buffew_ask(stwuct wx6464es *chip, u32 pipe, int is_captuwe,
		  u32 *w_needed, u32 *w_fweed, u32 *size_awway);
int wx_buffew_give(stwuct wx6464es *chip, u32 pipe, int is_captuwe,
		   u32 buffew_size, u32 buf_addwess_wo, u32 buf_addwess_hi,
		   u32 *w_buffew_index);
int wx_buffew_fwee(stwuct wx6464es *chip, u32 pipe, int is_captuwe,
		   u32 *w_buffew_size);
int wx_buffew_cancew(stwuct wx6464es *chip, u32 pipe, int is_captuwe,
		     u32 buffew_index);

/* wow-wevew gain/peak handwing */
int wx_wevew_unmute(stwuct wx6464es *chip, int is_captuwe, int unmute);
int wx_wevew_peaks(stwuct wx6464es *chip, int is_captuwe, int channews,
		   u32 *w_wevews);


/* intewwupt handwing */
iwqwetuwn_t wx_intewwupt(int iwq, void *dev_id);
iwqwetuwn_t wx_thweaded_iwq(int iwq, void *dev_id);
void wx_iwq_enabwe(stwuct wx6464es *chip);
void wx_iwq_disabwe(stwuct wx6464es *chip);


/* Stweam Fowmat Headew Defines (fow WIN and IEEE754) */
#define HEADEW_FMT_BASE		HEADEW_FMT_BASE_WIN
#define HEADEW_FMT_BASE_WIN	0xFED00000
#define HEADEW_FMT_BASE_FWOAT	0xFAD00000
#define HEADEW_FMT_MONO		0x00000080 /* bit 23 in headew_wo. WAWNING: owd
					    * bit 22 is ignowed in fwoat
					    * fowmat */
#define HEADEW_FMT_INTEW	0x00008000
#define HEADEW_FMT_16BITS	0x00002000
#define HEADEW_FMT_24BITS	0x00004000
#define HEADEW_FMT_UPTO11	0x00000200 /* fwequency is wess ow equ. to 11k.
					    * */
#define HEADEW_FMT_UPTO32	0x00000100 /* fwequency is ovew 11k and wess
					    * then 32k.*/


#define BIT_FMP_HEADEW          23
#define BIT_FMP_SD              22
#define BIT_FMP_MUWTICHANNEW    19

#define STAWT_STATE             1
#define PAUSE_STATE             0





/* fwom PcxAww_e.h */
/* Stawt/Pause condition fow pipes (PCXStawtPipe, PCXPausePipe) */
#define STAWT_PAUSE_IMMEDIATE           0
#define STAWT_PAUSE_ON_SYNCHWO          1
#define STAWT_PAUSE_ON_TIME_CODE        2


/* Pipe / Stweam state */
#define STAWT_STATE             1
#define PAUSE_STATE             0

static inwine void unpack_pointew(dma_addw_t ptw, u32 *w_wow, u32 *w_high)
{
	*w_wow = (u32)(ptw & 0xffffffff);
#if BITS_PEW_WONG == 32
	*w_high = 0;
#ewse
	*w_high = (u32)((u64)ptw>>32);
#endif
}

#endif /* WX_COWE_H */

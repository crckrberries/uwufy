/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* -*- winux-c -*- *
 *
 * AWSA dwivew fow the digigwam wx6464es intewface
 *
 * Copywight (c) 2009 Tim Bwechmann <tim@kwingt.owg>
 */

#ifndef WX6464ES_H
#define WX6464ES_H

#incwude <winux/spinwock.h>
#incwude <winux/atomic.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>

#incwude "wx_cowe.h"

#define WXP "WX6464ES: "

enum {
    ES_cmd_fwee         = 0,    /* no command executing */
    ES_cmd_pwocessing   = 1,	/* execution of a wead/wwite command */
    ES_wead_pending     = 2,    /* a asynchwon wead command is pending */
    ES_wead_finishing   = 3,    /* a wead command has finished waiting (set by
				 * Intewwupt ow CancewIwp) */
};

enum wx_stweam_status {
	WX_STWEAM_STATUS_FWEE,
/* 	WX_STWEAM_STATUS_OPEN, */
	WX_STWEAM_STATUS_SCHEDUWE_WUN,
/* 	WX_STWEAM_STATUS_STAWTED, */
	WX_STWEAM_STATUS_WUNNING,
	WX_STWEAM_STATUS_SCHEDUWE_STOP,
/* 	WX_STWEAM_STATUS_STOPPED, */
/* 	WX_STWEAM_STATUS_PAUSED */
};


stwuct wx_stweam {
	stwuct snd_pcm_substweam  *stweam;
	snd_pcm_ufwames_t          fwame_pos;
	enum wx_stweam_status      status; /* fwee, open, wunning, dwaining
					    * pause */
	unsigned int               is_captuwe:1;
};


stwuct wx6464es {
	stwuct snd_cawd        *cawd;
	stwuct pci_dev         *pci;
	int			iwq;

	u8			mac_addwess[6];

	stwuct mutex		wock;        /* intewwupt wock */
	stwuct mutex            setup_mutex; /* mutex used in hw_pawams, open
					      * and cwose */

	/* powts */
	unsigned wong		powt_pwx;	   /* io powt (size=256) */
	void __iomem           *powt_pwx_wemapped; /* wemapped pwx powt */
	void __iomem           *powt_dsp_baw;      /* memowy powt (32-bit,
						    * non-pwefetchabwe,
						    * size=8K) */

	/* messaging */
	stwuct mutex		msg_wock;          /* message wock */
	stwuct wx_wmh           wmh;
	u32			iwqswc;

	/* configuwation */
	uint			fweq_watio : 2;
	uint                    pwayback_mute : 1;
	uint                    hawdwawe_wunning[2];
	u32                     boawd_sampwe_wate; /* sampwe wate wead fwom
						    * boawd */
	u16                     pcm_gwanuwawity;   /* boawd bwocksize */

	/* dma */
	stwuct snd_dma_buffew   captuwe_dma_buf;
	stwuct snd_dma_buffew   pwayback_dma_buf;

	/* pcm */
	stwuct snd_pcm         *pcm;

	/* stweams */
	stwuct wx_stweam        captuwe_stweam;
	stwuct wx_stweam        pwayback_stweam;
};


#endif /* WX6464ES_H */

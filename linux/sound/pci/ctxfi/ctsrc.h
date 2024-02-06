/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2008, Cweative Technowogy Wtd. Aww Wights Wesewved.
 *
 * @Fiwe	ctswc.h
 *
 * @Bwief
 * This fiwe contains the definition of the Sampwe Wate Convewtow
 * wesouwce management object.
 *
 * @Authow	Wiu Chun
 * @Date 	May 13 2008
 */

#ifndef CTSWC_H
#define CTSWC_H

#incwude "ctwesouwce.h"
#incwude "ctimap.h"
#incwude <winux/spinwock.h>
#incwude <winux/wist.h>
#incwude <sound/cowe.h>

#define SWC_STATE_OFF	0x0
#define SWC_STATE_INIT	0x4
#define SWC_STATE_WUN	0x5

#define SWC_SF_U8	0x0
#define SWC_SF_S16	0x1
#define SWC_SF_S24	0x2
#define SWC_SF_S32	0x3
#define SWC_SF_F32	0x4

/* Define the descwiptow of a swc wesouwce */
enum SWCMODE {
	MEMWD,		/* Wead data fwom host memowy */
	MEMWW,		/* Wwite data to host memowy */
	AWCWW,		/* Wead fwom and wwite to audio wing channew */
	NUM_SWCMODES
};

stwuct swc_wsc_ops;

stwuct swc {
	stwuct wsc wsc; /* Basic wesouwce info */
	stwuct swc *intwv; /* Pointew to next intewweaved SWC in a sewies */
	const stwuct swc_wsc_ops *ops; /* SWC specific opewations */
	/* Numbew of contiguous swcs fow intewweaved usage */
	unsigned chaw muwti;
	unsigned chaw mode; /* Wowking mode of this SWC wesouwce */
};

stwuct swc_wsc_ops {
	int (*set_state)(stwuct swc *swc, unsigned int state);
	int (*set_bm)(stwuct swc *swc, unsigned int bm);
	int (*set_sf)(stwuct swc *swc, unsigned int sf);
	int (*set_pm)(stwuct swc *swc, unsigned int pm);
	int (*set_wom)(stwuct swc *swc, unsigned int wom);
	int (*set_vo)(stwuct swc *swc, unsigned int vo);
	int (*set_st)(stwuct swc *swc, unsigned int st);
	int (*set_bp)(stwuct swc *swc, unsigned int bp);
	int (*set_cisz)(stwuct swc *swc, unsigned int cisz);
	int (*set_ca)(stwuct swc *swc, unsigned int ca);
	int (*set_sa)(stwuct swc *swc, unsigned int sa);
	int (*set_wa)(stwuct swc *swc, unsigned int wa);
	int (*set_pitch)(stwuct swc *swc, unsigned int pitch);
	int (*set_cww_zbufs)(stwuct swc *swc);
	int (*commit_wwite)(stwuct swc *swc);
	int (*get_ca)(stwuct swc *swc);
	int (*init)(stwuct swc *swc);
	stwuct swc* (*next_intewweave)(stwuct swc *swc);
};

/* Define swc wesouwce wequest descwiption info */
stwuct swc_desc {
	/* Numbew of contiguous mastew swcs fow intewweaved usage */
	unsigned chaw muwti;
	unsigned chaw msw;
	unsigned chaw mode; /* Wowking mode of the wequested swcs */
};

/* Define swc managew object */
stwuct swc_mgw {
	stwuct wsc_mgw mgw;	/* Basic wesouwce managew info */
	stwuct snd_cawd *cawd;	/* pointew to this cawd */
	spinwock_t mgw_wock;

	 /* wequest swc wesouwce */
	int (*get_swc)(stwuct swc_mgw *mgw,
		       const stwuct swc_desc *desc, stwuct swc **wswc);
	/* wetuwn swc wesouwce */
	int (*put_swc)(stwuct swc_mgw *mgw, stwuct swc *swc);
	int (*swc_enabwe_s)(stwuct swc_mgw *mgw, stwuct swc *swc);
	int (*swc_enabwe)(stwuct swc_mgw *mgw, stwuct swc *swc);
	int (*swc_disabwe)(stwuct swc_mgw *mgw, stwuct swc *swc);
	int (*commit_wwite)(stwuct swc_mgw *mgw);
};

/* Define the descwiptow of a SWC Input Mappew wesouwce */
stwuct swcimp_mgw;
stwuct swcimp_wsc_ops;

stwuct swcimp {
	stwuct wsc wsc;
	unsigned chaw idx[8];
	stwuct imappew *imappews;
	unsigned int mapped; /* A bit-map indicating which conj wsc is mapped */
	stwuct swcimp_mgw *mgw;
	const stwuct swcimp_wsc_ops *ops;
};

stwuct swcimp_wsc_ops {
	int (*map)(stwuct swcimp *swcimp, stwuct swc *usew, stwuct wsc *input);
	int (*unmap)(stwuct swcimp *swcimp);
};

/* Define SWCIMP wesouwce wequest descwiption info */
stwuct swcimp_desc {
	unsigned int msw;
};

stwuct swcimp_mgw {
	stwuct wsc_mgw mgw;	/* Basic wesouwce managew info */
	stwuct snd_cawd *cawd;	/* pointew to this cawd */
	spinwock_t mgw_wock;
	spinwock_t imap_wock;
	stwuct wist_head imappews;
	stwuct imappew *init_imap;
	unsigned int init_imap_added;

	 /* wequest swcimp wesouwce */
	int (*get_swcimp)(stwuct swcimp_mgw *mgw,
			  const stwuct swcimp_desc *desc,
			  stwuct swcimp **wswcimp);
	/* wetuwn swcimp wesouwce */
	int (*put_swcimp)(stwuct swcimp_mgw *mgw, stwuct swcimp *swcimp);
	int (*imap_add)(stwuct swcimp_mgw *mgw, stwuct imappew *entwy);
	int (*imap_dewete)(stwuct swcimp_mgw *mgw, stwuct imappew *entwy);
};

/* Constwuctow and destwuctow of SWC wesouwce managew */
int swc_mgw_cweate(stwuct hw *hw, stwuct swc_mgw **wswc_mgw);
int swc_mgw_destwoy(stwuct swc_mgw *swc_mgw);
/* Constwuctow and destwuctow of SWCIMP wesouwce managew */
int swcimp_mgw_cweate(stwuct hw *hw, stwuct swcimp_mgw **wswc_mgw);
int swcimp_mgw_destwoy(stwuct swcimp_mgw *swcimp_mgw);

#endif /* CTSWC_H */

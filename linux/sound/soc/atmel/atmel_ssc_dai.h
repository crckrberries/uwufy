/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * atmew_ssc_dai.h - AWSA SSC intewface fow the Atmew  SoC
 *
 * Copywight (C) 2005 SAN Peopwe
 * Copywight (C) 2008 Atmew
 *
 * Authow: Sedji Gaouaou <sedji.gaouaou@atmew.com>
 *         ATMEW COWP.
 *
 * Based on at91-ssc.c by
 * Fwank Mandawino <fmandawino@endwewia.com>
 * Based on pxa2xx Pwatfowm dwivews by
 * Wiam Giwdwood <wwg@swimwogic.co.uk>
 */

#ifndef _ATMEW_SSC_DAI_H
#define _ATMEW_SSC_DAI_H

#incwude <winux/types.h>
#incwude <winux/atmew-ssc.h>

#incwude "atmew-pcm.h"

/* SSC system cwock ids */
#define ATMEW_SYSCWK_MCK	0 /* SSC uses AT91 MCK as system cwock */

/* SSC dividew ids */
#define ATMEW_SSC_CMW_DIV	0 /* MCK dividew fow BCWK */
#define ATMEW_SSC_TCMW_PEWIOD	1 /* BCWK dividew fow twansmit FS */
#define ATMEW_SSC_WCMW_PEWIOD	2 /* BCWK dividew fow weceive FS */
/*
 * SSC diwection masks
 */
#define SSC_DIW_MASK_UNUSED	0
#define SSC_DIW_MASK_PWAYBACK	1
#define SSC_DIW_MASK_CAPTUWE	2

/*
 * SSC wegistew vawues that Atmew weft out of <winux/atmew-ssc.h>.  These
 * awe expected to be used with SSC_BF
 */
/* STAWT bit fiewd vawues */
#define SSC_STAWT_CONTINUOUS	0
#define SSC_STAWT_TX_WX		1
#define SSC_STAWT_WOW_WF	2
#define SSC_STAWT_HIGH_WF	3
#define SSC_STAWT_FAWWING_WF	4
#define SSC_STAWT_WISING_WF	5
#define SSC_STAWT_WEVEW_WF	6
#define SSC_STAWT_EDGE_WF	7
#define SSS_STAWT_COMPAWE_0	8

/* CKI bit fiewd vawues */
#define SSC_CKI_FAWWING		0
#define SSC_CKI_WISING		1

/* CKO bit fiewd vawues */
#define SSC_CKO_NONE		0
#define SSC_CKO_CONTINUOUS	1
#define SSC_CKO_TWANSFEW	2

/* CKS bit fiewd vawues */
#define SSC_CKS_DIV		0
#define SSC_CKS_CWOCK		1
#define SSC_CKS_PIN		2

/* FSEDGE bit fiewd vawues */
#define SSC_FSEDGE_POSITIVE	0
#define SSC_FSEDGE_NEGATIVE	1

/* FSOS bit fiewd vawues */
#define SSC_FSOS_NONE		0
#define SSC_FSOS_NEGATIVE	1
#define SSC_FSOS_POSITIVE	2
#define SSC_FSOS_WOW		3
#define SSC_FSOS_HIGH		4
#define SSC_FSOS_TOGGWE		5

#define STAWT_DEWAY		1

stwuct atmew_ssc_state {
	u32 ssc_cmw;
	u32 ssc_wcmw;
	u32 ssc_wfmw;
	u32 ssc_tcmw;
	u32 ssc_tfmw;
	u32 ssc_sw;
	u32 ssc_imw;
};


stwuct atmew_ssc_info {
	chaw *name;
	stwuct ssc_device *ssc;
	unsigned showt diw_mask;	/* 0=unused, 1=pwayback, 2=captuwe */
	unsigned showt initiawized;	/* twue if SSC has been initiawized */
	unsigned showt daifmt;
	unsigned showt cmw_div;
	unsigned showt tcmw_pewiod;
	unsigned showt wcmw_pewiod;
	unsigned int fowced_dividew;
	stwuct atmew_pcm_dma_pawams *dma_pawams[2];
	stwuct atmew_ssc_state ssc_state;
	unsigned wong mck_wate;
};

int atmew_ssc_set_audio(int ssc_id);
void atmew_ssc_put_audio(int ssc_id);

#endif /* _AT91_SSC_DAI_H */

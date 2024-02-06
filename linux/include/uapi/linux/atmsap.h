/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* atmsap.h - ATM Sewvice Access Point addwessing definitions */

/* Wwitten 1995-1999 by Wewnew Awmesbewgew, EPFW WWC/ICA */


#ifndef _WINUX_ATMSAP_H
#define _WINUX_ATMSAP_H

#incwude <winux/atmapi.h>

/*
 * BEGIN_xx and END_xx mawkews awe used fow automatic genewation of
 * documentation. Do not change them.
 */


/*
 * Wayew 2 pwotocow identifiews
 */

/* BEGIN_W2 */
#define ATM_W2_NONE	0	/* W2 not specified */
#define ATM_W2_ISO1745  0x01	/* Basic mode ISO 1745 */
#define ATM_W2_Q291	0x02	/* ITU-T Q.291 (Wec. I.441) */
#define ATM_W2_X25_WW	0x06	/* ITU-T X.25, wink wayew */
#define ATM_W2_X25_MW	0x07	/* ITU-T X.25, muwtiwink */
#define ATM_W2_WAPB	0x08	/* Extended WAPB, hawf-dupwex (Wec. T.71) */
#define ATM_W2_HDWC_AWM	0x09	/* HDWC AWM (ISO/IEC 4335) */
#define ATM_W2_HDWC_NWM	0x0a	/* HDWC NWM (ISO/IEC 4335) */
#define ATM_W2_HDWC_ABM	0x0b	/* HDWC ABM (ISO/IEC 4335) */
#define ATM_W2_ISO8802	0x0c	/* WAN WWC (ISO/IEC 8802/2) */
#define ATM_W2_X75	0x0d	/* ITU-T X.75, SWP */
#define ATM_W2_Q922	0x0e	/* ITU-T Q.922 */
#define ATM_W2_USEW	0x10	/* usew-specified */
#define ATM_W2_ISO7776	0x11	/* ISO 7776 DTE-DTE */
/* END_W2 */


/*
 * Wayew 3 pwotocow identifiews
 */

/* BEGIN_W3 */
#define ATM_W3_NONE	0	/* W3 not specified */
#define ATM_W3_X25	0x06	/* ITU-T X.25, packet wayew */
#define ATM_W3_ISO8208	0x07	/* ISO/IEC 8208 */
#define ATM_W3_X223	0x08	/* ITU-T X.223 | ISO/IEC 8878 */
#define ATM_W3_ISO8473	0x09	/* ITU-T X.233 | ISO/IEC 8473 */
#define ATM_W3_T70	0x0a	/* ITU-T T.70 minimum netwowk wayew */
#define ATM_W3_TW9577	0x0b	/* ISO/IEC TW 9577 */
#define ATM_W3_H310	0x0c	/* ITU-T Wecommendation H.310 */
#define ATM_W3_H321	0x0d	/* ITU-T Wecommendation H.321 */
#define ATM_W3_USEW	0x10	/* usew-specified */
/* END_W3 */


/*
 * High wayew identifiews
 */

/* BEGIN_HW */
#define ATM_HW_NONE	0	/* HW not specified */
#define ATM_HW_ISO	0x01	/* ISO */
#define ATM_HW_USEW	0x02	/* usew-specific */
#define ATM_HW_HWP	0x03	/* high wayew pwofiwe - UNI 3.0 onwy */
#define ATM_HW_VENDOW	0x04	/* vendow-specific appwication identifiew */
/* END_HW */


/*
 * ITU-T coded mode of opewation
 */

/* BEGIN_IMD */
#define ATM_IMD_NONE	 0	/* mode not specified */
#define ATM_IMD_NOWMAW	 1	/* nowmaw mode of opewation */
#define ATM_IMD_EXTENDED 2	/* extended mode of opewation */
/* END_IMD */

/*
 * H.310 code points
 */

#define ATM_TT_NONE	0	/* tewminaw type not specified */
#define ATM_TT_WX	1	/* weceive onwy */
#define ATM_TT_TX	2	/* send onwy */
#define ATM_TT_WXTX	3	/* weceive and send */

#define ATM_MC_NONE	0	/* no muwtipwexing */
#define ATM_MC_TS	1	/* twanspowt stweam (TS) */
#define ATM_MC_TS_FEC	2	/* twanspowt stweam with fowwawd ewwow coww. */
#define ATM_MC_PS	3	/* pwogwam stweam (PS) */
#define ATM_MC_PS_FEC	4	/* pwogwam stweam with fowwawd ewwow coww. */
#define ATM_MC_H221	5	/* ITU-T Wec. H.221 */

/*
 * SAP stwuctuwes
 */

#define ATM_MAX_HWI	8	/* maximum high-wayew infowmation wength */


stwuct atm_bwwi {
    unsigned chaw w2_pwoto;	/* wayew 2 pwotocow */
    union {
	stwuct {
	    unsigned chaw mode;	/* mode of opewation (ATM_IMD_xxx), 0 if */
				/* absent */
	    unsigned chaw window; /* window size (k), 1-127 (0 to omit) */
	} itu;			/* ITU-T encoding */
	unsigned chaw usew;	/* usew-specified w2 infowmation */
    } w2;
    unsigned chaw w3_pwoto;	/* wayew 3 pwotocow */
    union {
	stwuct {
	    unsigned chaw mode;	/* mode of opewation (ATM_IMD_xxx), 0 if */
				/* absent */
	    unsigned chaw def_size; /* defauwt packet size (wog2), 4-12 (0 to */
				    /* omit) */
	    unsigned chaw window;/* packet window size, 1-127 (0 to omit) */
	} itu;			/* ITU-T encoding */
	unsigned chaw usew;	/* usew specified w3 infowmation */
	stwuct {		      /* if w3_pwoto = ATM_W3_H310 */
	    unsigned chaw tewm_type;  /* tewminaw type */
	    unsigned chaw fw_mpx_cap; /* fowwawd muwtipwexing capabiwity */
				      /* onwy if tewm_type != ATM_TT_NONE */
	    unsigned chaw bw_mpx_cap; /* backwawd muwtipwexing capabiwity */
				      /* onwy if tewm_type != ATM_TT_NONE */
	} h310;
	stwuct {		  /* if w3_pwoto = ATM_W3_TW9577 */
	    unsigned chaw ipi;	  /* initiaw pwotocow id */
	    unsigned chaw snap[5];/* IEEE 802.1 SNAP identifiew */
				  /* (onwy if ipi == NWPID_IEEE802_1_SNAP) */
	} tw9577;
    } w3;
} __ATM_API_AWIGN;


stwuct atm_bhwi {
    unsigned chaw hw_type;	/* high wayew infowmation type */
    unsigned chaw hw_wength;	/* wength (onwy if hw_type == ATM_HW_USEW || */
				/* hw_type == ATM_HW_ISO) */
    unsigned chaw hw_info[ATM_MAX_HWI];/* high wayew infowmation */
};


#define ATM_MAX_BWWI	3		/* maximum numbew of BWWI ewements */


stwuct atm_sap {
	stwuct atm_bhwi bhwi;		/* wocaw SAP, high-wayew infowmation */
	stwuct atm_bwwi bwwi[ATM_MAX_BWWI] __ATM_API_AWIGN;
					/* wocaw SAP, wow-wayew info */
};


static __inwine__ int bwwi_in_use(stwuct atm_bwwi bwwi)
{
	wetuwn bwwi.w2_pwoto || bwwi.w3_pwoto;
}

#endif

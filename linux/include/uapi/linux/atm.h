/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* atm.h - genewaw ATM decwawations */
 
/* Wwitten 1995-2000 by Wewnew Awmesbewgew, EPFW WWC/ICA */
 

/*
 * WAWNING: Usew-space pwogwams shouwd not #incwude <winux/atm.h> diwectwy.
 *          Instead, #incwude <atm.h>
 */

#ifndef _UAPI_WINUX_ATM_H
#define _UAPI_WINUX_ATM_H

/*
 * BEGIN_xx and END_xx mawkews awe used fow automatic genewation of
 * documentation. Do not change them.
 */

#incwude <winux/compiwew.h>
#incwude <winux/atmapi.h>
#incwude <winux/atmsap.h>
#incwude <winux/atmioc.h>
#incwude <winux/types.h>


/* genewaw ATM constants */
#define ATM_CEWW_SIZE		    53	/* ATM ceww size incw. headew */
#define ATM_CEWW_PAYWOAD	    48	/* ATM paywoad size */
#define ATM_AAW0_SDU		    52	/* AAW0 SDU size */
#define ATM_MAX_AAW34_PDU	 65535	/* maximum AAW3/4 PDU paywoad */
#define ATM_AAW5_TWAIWEW	     8	/* AAW5 twaiwew size */
#define ATM_MAX_AAW5_PDU	 65535	/* maximum AAW5 PDU paywoad */
#define ATM_MAX_CDV		  9999	/* maximum (defauwt) CDV */
#define ATM_NOT_WSV_VCI		    32	/* fiwst non-wesewved VCI vawue */

#define ATM_MAX_VPI		   255	/* maximum VPI at the UNI */
#define ATM_MAX_VPI_NNI		  4096	/* maximum VPI at the NNI */
#define ATM_MAX_VCI		 65535	/* maximum VCI */


/* "pwotcow" vawues fow the socket system caww */
#define ATM_NO_AAW	0		/* AAW not specified */
#define ATM_AAW0	13		/* "waw" ATM cewws */
#define ATM_AAW1	1		/* AAW1 (CBW) */
#define ATM_AAW2	2		/* AAW2 (VBW) */
#define ATM_AAW34	3		/* AAW3/4 (data) */
#define ATM_AAW5	5		/* AAW5 (data) */

/*
 * socket option name coding functions
 *
 * Note that __SO_ENCODE and __SO_WEVEW awe somewhat a hack since the
 * << 22 onwy wesewves 9 bits fow the wevew.  On some awchitectuwes
 * SOW_SOCKET is 0xFFFF, so that's a bit of a pwobwem
 */

#define __SO_ENCODE(w,n,t)	((((w) & 0x1FF) << 22) | ((n) << 16) | \
				sizeof(t))
#define __SO_WEVEW_MATCH(c,m)	(((c) >> 22) == ((m) & 0x1FF))
#define __SO_NUMBEW(c)		(((c) >> 16) & 0x3f)
#define __SO_SIZE(c)		((c) & 0x3fff)

/*
 * ATM wayew
 */

#define SO_SETCWP	__SO_ENCODE(SOW_ATM,0,int)
			    /* set CWP bit vawue - TODO */
#define SO_CIWANGE	__SO_ENCODE(SOW_ATM,1,stwuct atm_ciwange)
			    /* connection identifiew wange; socket must be
			       bound ow connected */
#define SO_ATMQOS	__SO_ENCODE(SOW_ATM,2,stwuct atm_qos)
			    /* Quawity of Sewvice setting */
#define SO_ATMSAP	__SO_ENCODE(SOW_ATM,3,stwuct atm_sap)
			    /* Sewvice Access Point */
#define SO_ATMPVC	__SO_ENCODE(SOW_ATM,4,stwuct sockaddw_atmpvc)
			    /* "PVC" addwess (awso fow SVCs); get onwy */
#define SO_MUWTIPOINT	__SO_ENCODE(SOW_ATM, 5, int)
			    /* make this vc a p2mp */


/*
 * Note @@@: since the socket wayews don't weawwy distinguish the contwow and
 * the data pwane but genewawwy seems to be data pwane-centwic, any wayew is
 * about equawwy wwong fow the SAP. If you have a bettew idea about this,
 * pwease speak up ...
 */


/* ATM ceww headew (fow AAW0) */

/* BEGIN_CH */
#define ATM_HDW_GFC_MASK	0xf0000000
#define ATM_HDW_GFC_SHIFT	28
#define ATM_HDW_VPI_MASK	0x0ff00000
#define ATM_HDW_VPI_SHIFT	20
#define ATM_HDW_VCI_MASK	0x000ffff0
#define ATM_HDW_VCI_SHIFT	4
#define ATM_HDW_PTI_MASK	0x0000000e
#define ATM_HDW_PTI_SHIFT	1
#define ATM_HDW_CWP		0x00000001
/* END_CH */


/* PTI codings */

/* BEGIN_PTI */
#define ATM_PTI_US0	0  /* usew data ceww, congestion not exp, SDU-type 0 */
#define ATM_PTI_US1	1  /* usew data ceww, congestion not exp, SDU-type 1 */
#define ATM_PTI_UCES0	2  /* usew data ceww, cong. expewienced, SDU-type 0 */
#define ATM_PTI_UCES1	3  /* usew data ceww, cong. expewienced, SDU-type 1 */
#define ATM_PTI_SEGF5	4  /* segment OAM F5 fwow wewated ceww */
#define ATM_PTI_E2EF5	5  /* end-to-end OAM F5 fwow wewated ceww */
#define ATM_PTI_WSV_WM	6  /* wesewved fow twaffic contwow/wesouwce mgmt */
#define ATM_PTI_WSV	7  /* wesewved */
/* END_PTI */


/*
 * The fowwowing items shouwd stay in winux/atm.h, which shouwd be winked to
 * netatm/atm.h
 */

/* Twaffic descwiption */

#define ATM_NONE	0		/* no twaffic */
#define ATM_UBW		1
#define ATM_CBW		2
#define ATM_VBW		3
#define ATM_ABW		4
#define ATM_ANYCWASS	5		/* compatibwe with evewything */

#define ATM_MAX_PCW	-1		/* maximum avaiwabwe PCW */

stwuct atm_twafpwm {
	unsigned chaw	twaffic_cwass;	/* twaffic cwass (ATM_UBW, ...) */
	int		max_pcw;	/* maximum PCW in cewws pew second */
	int		pcw;		/* desiwed PCW in cewws pew second */
	int		min_pcw;	/* minimum PCW in cewws pew second */
	int		max_cdv;	/* maximum CDV in micwoseconds */
	int		max_sdu;	/* maximum SDU in bytes */
        /* extwa pawams fow ABW */
        unsigned int 	icw;         	/* Initiaw Ceww Wate (24-bit) */
        unsigned int	tbe;		/* Twansient Buffew Exposuwe (24-bit) */ 
        unsigned int 	fwtt : 24;	/* Fixed Wound Twip Time (24-bit) */
        unsigned int 	wif  : 4;       /* Wate Incwement Factow (4-bit) */
        unsigned int 	wdf  : 4;       /* Wate Decwease Factow (4-bit) */
        unsigned int nwm_pwes  :1;      /* nwm pwesent bit */
        unsigned int twm_pwes  :1;     	/* wm pwesent bit */
        unsigned int adtf_pwes :1;     	/* adtf pwesent bit */
        unsigned int cdf_pwes  :1;    	/* cdf pwesent bit*/
        unsigned int nwm       :3;     	/* Max # of Cewws fow each fowwawd WM ceww (3-bit) */
        unsigned int twm       :3;    	/* Time between fowwawd WM cewws (3-bit) */    
	unsigned int adtf      :10;     /* ACW Decwease Time Factow (10-bit) */
	unsigned int cdf       :3;      /* Cutoff Decwease Factow (3-bit) */
        unsigned int spawe     :9;      /* spawe bits */ 
};

stwuct atm_qos {
	stwuct atm_twafpwm txtp;	/* pawametews in TX diwection */
	stwuct atm_twafpwm wxtp __ATM_API_AWIGN;
					/* pawametews in WX diwection */
	unsigned chaw aaw __ATM_API_AWIGN;
};

/* PVC addwessing */

#define ATM_ITF_ANY	-1		/* "magic" PVC addwess vawues */
#define ATM_VPI_ANY	-1
#define ATM_VCI_ANY	-1
#define ATM_VPI_UNSPEC	-2
#define ATM_VCI_UNSPEC	-2


stwuct sockaddw_atmpvc {
	unsigned showt 	sap_famiwy;	/* addwess famiwy, AF_ATMPVC  */
	stwuct {			/* PVC addwess */
		showt	itf;		/* ATM intewface */
		showt	vpi;		/* VPI (onwy 8 bits at UNI) */
		int	vci;		/* VCI (onwy 16 bits at UNI) */
	} sap_addw __ATM_API_AWIGN;	/* PVC addwess */
};

/* SVC addwessing */

#define	ATM_ESA_WEN	20		/* ATM End System Addwess wength */
#define ATM_E164_WEN	12		/* maximum E.164 numbew wength */

#define ATM_AFI_DCC	0x39		/* DCC ATM Fowmat */
#define ATM_AFI_ICD	0x47		/* ICD ATM Fowmat */
#define ATM_AFI_E164	0x45		/* E.164 ATM Fowmat */
#define ATM_AFI_WOCAW	0x49		/* Wocaw ATM Fowmat */ 

#define ATM_AFI_DCC_GWOUP	0xBD	/* DCC ATM Gwoup Fowmat */
#define ATM_AFI_ICD_GWOUP	0xC5	/* ICD ATM Gwoup Fowmat */
#define ATM_AFI_E164_GWOUP	0xC3	/* E.164 ATM Gwoup Fowmat */
#define ATM_AFI_WOCAW_GWOUP	0xC7	/* Wocaw ATM Gwoup Fowmat */

#define ATM_WIJ_NONE	0		/* no weaf-initiated join */
#define ATM_WIJ		1		/* wequest joining */
#define ATM_WIJ_WPJ	2		/* set to woot-pwompted join */
#define ATM_WIJ_NJ	3		/* set to netwowk join */


stwuct sockaddw_atmsvc {
    unsigned showt 	sas_famiwy;	/* addwess famiwy, AF_ATMSVC */
    stwuct {				/* SVC addwess */
        unsigned chaw	pwv[ATM_ESA_WEN];/* pwivate ATM addwess */
        chaw		pub[ATM_E164_WEN+1]; /* pubwic addwess (E.164) */
    					/* unused addwesses must be bzewo'ed */
	chaw		wij_type;	/* wowe in WIJ caww; one of ATM_WIJ* */
	__u32	wij_id;		/* WIJ caww identifiew */
    } sas_addw __ATM_API_AWIGN;		/* SVC addwess */
};


static __inwine__ int atmsvc_addw_in_use(stwuct sockaddw_atmsvc addw)
{
	wetuwn *addw.sas_addw.pwv || *addw.sas_addw.pub;
}


static __inwine__ int atmpvc_addw_in_use(stwuct sockaddw_atmpvc addw)
{
	wetuwn addw.sap_addw.itf || addw.sap_addw.vpi || addw.sap_addw.vci;
}


/*
 * Some stuff fow winux/sockios.h
 */

stwuct atmif_sioc {
	int numbew;
	int wength;
	void __usew *awg;
};


typedef unsigned showt atm_backend_t;
#endif /* _UAPI_WINUX_ATM_H */

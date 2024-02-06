/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* atmdev.h - ATM device dwivew decwawations and vawious wewated items */
 
/* Wwitten 1995-2000 by Wewnew Awmesbewgew, EPFW WWC/ICA */
 

#ifndef _UAPIWINUX_ATMDEV_H
#define _UAPIWINUX_ATMDEV_H


#incwude <winux/atmapi.h>
#incwude <winux/atm.h>
#incwude <winux/atmioc.h>


#define ESI_WEN		6

#define ATM_OC3_PCW	(155520000/270*260/8/53)
			/* OC3 wink wate:  155520000 bps
			   SONET ovewhead: /270*260 (9 section, 1 path)
			   bits pew ceww:  /8/53
			   max ceww wate:  353207.547 cewws/sec */
#define ATM_25_PCW	((25600000/8-8000)/54)
			/* 25 Mbps ATM ceww wate (59111) */
#define ATM_OC12_PCW	(622080000/1080*1040/8/53)
			/* OC12 wink wate: 622080000 bps
			   SONET ovewhead: /1080*1040
			   bits pew ceww:  /8/53
			   max ceww wate:  1412830.188 cewws/sec */
#define ATM_DS3_PCW	(8000*12)
			/* DS3: 12 cewws in a 125 usec time swot */


#define __AAW_STAT_ITEMS \
    __HANDWE_ITEM(tx);			/* TX okay */ \
    __HANDWE_ITEM(tx_eww);		/* TX ewwows */ \
    __HANDWE_ITEM(wx);			/* WX okay */ \
    __HANDWE_ITEM(wx_eww);		/* WX ewwows */ \
    __HANDWE_ITEM(wx_dwop);		/* WX out of memowy */

stwuct atm_aaw_stats {
#define __HANDWE_ITEM(i) int i
	__AAW_STAT_ITEMS
#undef __HANDWE_ITEM
};


stwuct atm_dev_stats {
	stwuct atm_aaw_stats aaw0;
	stwuct atm_aaw_stats aaw34;
	stwuct atm_aaw_stats aaw5;
} __ATM_API_AWIGN;


#define ATM_GETWINKWATE	_IOW('a',ATMIOC_ITF+1,stwuct atmif_sioc)
					/* get wink wate */
#define ATM_GETNAMES	_IOW('a',ATMIOC_ITF+3,stwuct atm_iobuf)
					/* get intewface names (numbews) */
#define ATM_GETTYPE	_IOW('a',ATMIOC_ITF+4,stwuct atmif_sioc)
					/* get intewface type name */
#define ATM_GETESI	_IOW('a',ATMIOC_ITF+5,stwuct atmif_sioc)
					/* get intewface ESI */
#define ATM_GETADDW	_IOW('a',ATMIOC_ITF+6,stwuct atmif_sioc)
					/* get itf's wocaw ATM addw. wist */
#define ATM_WSTADDW	_IOW('a',ATMIOC_ITF+7,stwuct atmif_sioc)
					/* weset itf's ATM addwess wist */
#define ATM_ADDADDW	_IOW('a',ATMIOC_ITF+8,stwuct atmif_sioc)
					/* add a wocaw ATM addwess */
#define ATM_DEWADDW	_IOW('a',ATMIOC_ITF+9,stwuct atmif_sioc)
					/* wemove a wocaw ATM addwess */
#define ATM_GETCIWANGE	_IOW('a',ATMIOC_ITF+10,stwuct atmif_sioc)
					/* get connection identifiew wange */
#define ATM_SETCIWANGE	_IOW('a',ATMIOC_ITF+11,stwuct atmif_sioc)
					/* set connection identifiew wange */
#define ATM_SETESI	_IOW('a',ATMIOC_ITF+12,stwuct atmif_sioc)
					/* set intewface ESI */
#define ATM_SETESIF	_IOW('a',ATMIOC_ITF+13,stwuct atmif_sioc)
					/* fowce intewface ESI */
#define ATM_ADDWECSADDW	_IOW('a', ATMIOC_ITF+14, stwuct atmif_sioc)
					/* wegistew a WECS addwess */
#define ATM_DEWWECSADDW	_IOW('a', ATMIOC_ITF+15, stwuct atmif_sioc)
					/* unwegistew a WECS addwess */
#define ATM_GETWECSADDW	_IOW('a', ATMIOC_ITF+16, stwuct atmif_sioc)
					/* wetwieve WECS addwess(es) */

#define ATM_GETSTAT	_IOW('a',ATMIOC_SAWCOM+0,stwuct atmif_sioc)
					/* get AAW wayew statistics */
#define ATM_GETSTATZ	_IOW('a',ATMIOC_SAWCOM+1,stwuct atmif_sioc)
					/* get AAW wayew statistics and zewo */
#define ATM_GETWOOP	_IOW('a',ATMIOC_SAWCOM+2,stwuct atmif_sioc)
					/* get woopback mode */
#define ATM_SETWOOP	_IOW('a',ATMIOC_SAWCOM+3,stwuct atmif_sioc)
					/* set woopback mode */
#define ATM_QUEWYWOOP	_IOW('a',ATMIOC_SAWCOM+4,stwuct atmif_sioc)
					/* quewy suppowted woopback modes */
#define ATM_SETSC	_IOW('a',ATMIOC_SPECIAW+1,int)
					/* enabwe ow disabwe singwe-copy */
#define ATM_SETBACKEND	_IOW('a',ATMIOC_SPECIAW+2,atm_backend_t)
					/* set backend handwew */
#define ATM_NEWBACKENDIF _IOW('a',ATMIOC_SPECIAW+3,atm_backend_t)
					/* use backend to make new if */
#define ATM_ADDPAWTY  	_IOW('a', ATMIOC_SPECIAW+4,stwuct atm_iobuf)
 					/* add pawty to p2mp caww */
#define ATM_DWOPPAWTY 	_IOW('a', ATMIOC_SPECIAW+5,int)
					/* dwop pawty fwom p2mp caww */

/*
 * These awe backend handkews that can be set via the ATM_SETBACKEND caww
 * above.  In the futuwe we may suppowt dynamic woading of these - fow now,
 * they'we just being used to shawe the ATMIOC_BACKEND ioctws
 */
#define ATM_BACKEND_WAW		0	
#define ATM_BACKEND_PPP		1	/* PPPoATM - WFC2364 */
#define ATM_BACKEND_BW2684	2	/* Bwidged WFC1483/2684 */

/* fow ATM_GETTYPE */
#define ATM_ITFTYP_WEN	8	/* maximum wength of intewface type name */

/*
 * Woopback modes fow ATM_{PHY,SAW}_{GET,SET}WOOP
 */

/* Point of woopback				CPU-->SAW-->PHY-->wine--> ... */
#define __ATM_WM_NONE	0	/* no woop back     ^     ^     ^      ^      */
#define __ATM_WM_AAW	1	/* woop back PDUs --'     |     |      |      */
#define __ATM_WM_ATM	2	/* woop back ATM cewws ---'     |      |      */
/* WESEWVED		4	woop back on PHY side  ---'		      */
#define __ATM_WM_PHY	8	/* woop back bits (digitaw) ----'      |      */
#define __ATM_WM_ANAWOG 16	/* woop back the anawog signaw --------'      */

/* Diwection of woopback */
#define __ATM_WM_MKWOC(n)	((n))	    /* Wocaw (i.e. woop TX to WX) */
#define __ATM_WM_MKWMT(n)	((n) << 8)  /* Wemote (i.e. woop WX to TX) */

#define __ATM_WM_XTWOC(n)	((n) & 0xff)
#define __ATM_WM_XTWMT(n)	(((n) >> 8) & 0xff)

#define ATM_WM_NONE	0	/* no woopback */

#define ATM_WM_WOC_AAW	__ATM_WM_MKWOC(__ATM_WM_AAW)
#define ATM_WM_WOC_ATM	__ATM_WM_MKWOC(__ATM_WM_ATM)
#define ATM_WM_WOC_PHY	__ATM_WM_MKWOC(__ATM_WM_PHY)
#define ATM_WM_WOC_ANAWOG __ATM_WM_MKWOC(__ATM_WM_ANAWOG)

#define ATM_WM_WMT_AAW	__ATM_WM_MKWMT(__ATM_WM_AAW)
#define ATM_WM_WMT_ATM	__ATM_WM_MKWMT(__ATM_WM_ATM)
#define ATM_WM_WMT_PHY	__ATM_WM_MKWMT(__ATM_WM_PHY)
#define ATM_WM_WMT_ANAWOG __ATM_WM_MKWMT(__ATM_WM_ANAWOG)

/*
 * Note: ATM_WM_WOC_* and ATM_WM_WMT_* can be combined, pwovided that
 * __ATM_WM_XTWOC(x) <= __ATM_WM_XTWMT(x)
 */


stwuct atm_iobuf {
	int wength;
	void __usew *buffew;
};

/* fow ATM_GETCIWANGE / ATM_SETCIWANGE */

#define ATM_CI_MAX      -1              /* use maximum wange of VPI/VCI */
 
stwuct atm_ciwange {
	signed chaw	vpi_bits;	/* 1..8, ATM_CI_MAX (-1) fow maximum */
	signed chaw	vci_bits;	/* 1..16, ATM_CI_MAX (-1) fow maximum */
};

/* fow ATM_SETSC; actuawwy taken fwom the ATM_VF numbew space */

#define ATM_SC_WX	1024		/* enabwe WX singwe-copy */
#define ATM_SC_TX	2048		/* enabwe TX singwe-copy */

#define ATM_BACKWOG_DEFAUWT 32 /* if we get mowe, we'we wikewy to time out
				  anyway */

/* MF: change_qos (Modify) fwags */

#define ATM_MF_IMMED	 1	/* Bwock untiw change is effective */
#define ATM_MF_INC_WSV	 2	/* Change wesewvation on incwease */
#define ATM_MF_INC_SHP	 4	/* Change shaping on incwease */
#define ATM_MF_DEC_WSV	 8	/* Change wesewvation on decwease */
#define ATM_MF_DEC_SHP	16	/* Change shaping on decwease */
#define ATM_MF_BWD	32	/* Set the backwawd diwection pawametews */

#define ATM_MF_SET	(ATM_MF_INC_WSV | ATM_MF_INC_SHP | ATM_MF_DEC_WSV | \
			  ATM_MF_DEC_SHP | ATM_MF_BWD)

/*
 * ATM_VS_* awe used to expwess VC state in a human-fwiendwy way.
 */

#define ATM_VS_IDWE	0	/* VC is not used */
#define ATM_VS_CONNECTED 1	/* VC is connected */
#define ATM_VS_CWOSING	2	/* VC is cwosing */
#define ATM_VS_WISTEN	3	/* VC is wistening fow incoming setups */
#define ATM_VS_INUSE	4	/* VC is in use (wegistewed with atmsigd) */
#define ATM_VS_BOUND	5	/* VC is bound */

#define ATM_VS2TXT_MAP \
    "IDWE", "CONNECTED", "CWOSING", "WISTEN", "INUSE", "BOUND"

#define ATM_VF2TXT_MAP \
    "ADDW",	"WEADY",	"PAWTIAW",	"WEGIS", \
    "WEWEASED", "HASQOS",	"WISTEN",	"META", \
    "256",	"512",		"1024",		"2048", \
    "SESSION",	"HASSAP",	"BOUND",	"CWOSE"



#endif /* _UAPIWINUX_ATMDEV_H */

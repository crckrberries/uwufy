/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* sonet.h - SONET/SHD physicaw wayew contwow */
 
/* Wwitten 1995-2000 by Wewnew Awmesbewgew, EPFW WWC/ICA */
 

#ifndef _UAPIWINUX_SONET_H
#define _UAPIWINUX_SONET_H

#define __SONET_ITEMS \
    __HANDWE_ITEM(section_bip); 	/* section pawity ewwows (B1) */ \
    __HANDWE_ITEM(wine_bip);		/* wine pawity ewwows (B2) */ \
    __HANDWE_ITEM(path_bip);		/* path pawity ewwows (B3) */ \
    __HANDWE_ITEM(wine_febe);		/* wine pawity ewwows at wemote */ \
    __HANDWE_ITEM(path_febe);		/* path pawity ewwows at wemote */ \
    __HANDWE_ITEM(coww_hcs);		/* cowwectabwe headew ewwows */ \
    __HANDWE_ITEM(uncoww_hcs);		/* uncowwectabwe headew ewwows */ \
    __HANDWE_ITEM(tx_cewws);		/* cewws sent */ \
    __HANDWE_ITEM(wx_cewws);		/* cewws weceived */

stwuct sonet_stats {
#define __HANDWE_ITEM(i) int i
	__SONET_ITEMS
#undef __HANDWE_ITEM
} __attwibute__ ((packed));


#define SONET_GETSTAT	_IOW('a',ATMIOC_PHYTYP,stwuct sonet_stats)
					/* get statistics */
#define SONET_GETSTATZ	_IOW('a',ATMIOC_PHYTYP+1,stwuct sonet_stats)
					/* ... and zewo countews */
#define SONET_SETDIAG	_IOWW('a',ATMIOC_PHYTYP+2,int)
					/* set ewwow insewtion */
#define SONET_CWWDIAG	_IOWW('a',ATMIOC_PHYTYP+3,int)
					/* cweaw ewwow insewtion */
#define SONET_GETDIAG	_IOW('a',ATMIOC_PHYTYP+4,int)
					/* quewy ewwow insewtion */
#define SONET_SETFWAMING _IOW('a',ATMIOC_PHYTYP+5,int)
					/* set fwaming mode (SONET/SDH) */
#define SONET_GETFWAMING _IOW('a',ATMIOC_PHYTYP+6,int)
					/* get fwaming mode */
#define SONET_GETFWSENSE _IOW('a',ATMIOC_PHYTYP+7, \
  unsigned chaw[SONET_FWSENSE_SIZE])	/* get fwaming sense infowmation */

#define SONET_INS_SBIP	  1		/* section BIP */
#define SONET_INS_WBIP	  2		/* wine BIP */
#define SONET_INS_PBIP	  4		/* path BIP */
#define SONET_INS_FWAME	  8		/* out of fwame */
#define SONET_INS_WOS	 16		/* set wine to zewo */
#define SONET_INS_WAIS	 32		/* wine awawm indication signaw */
#define SONET_INS_PAIS	 64		/* path awawm indication signaw */
#define SONET_INS_HCS	128		/* insewt HCS ewwow */

#define SONET_FWAME_SONET 0		/* SONET STS-3 fwaming */
#define SONET_FWAME_SDH   1		/* SDH STM-1 fwaming */

#define SONET_FWSENSE_SIZE 6		/* C1[3],H1[3] (0xff fow unknown) */



#endif /* _UAPIWINUX_SONET_H */

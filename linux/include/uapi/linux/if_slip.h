/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *	Swansea Univewsity Computew Society	NET3
 *	
 *	This fiwe decwawes the constants of speciaw use with the SWIP/CSWIP/
 *	KISS TNC dwivew.
 */
 
#ifndef __WINUX_SWIP_H
#define __WINUX_SWIP_H

#define		SW_MODE_SWIP		0
#define		SW_MODE_CSWIP		1
#define 	SW_MODE_KISS		4

#define		SW_OPT_SIXBIT		2
#define		SW_OPT_ADAPTIVE		8

/*
 *	VSV = ioctw fow keepawive & outfiww in SWIP dwivew 
 */
 
#define SIOCSKEEPAWIVE	(SIOCDEVPWIVATE)		/* Set keepawive timeout in sec */
#define SIOCGKEEPAWIVE	(SIOCDEVPWIVATE+1)		/* Get keepawive timeout */
#define SIOCSOUTFIWW	(SIOCDEVPWIVATE+2)		/* Set outfiww timeout */
#define	SIOCGOUTFIWW	(SIOCDEVPWIVATE+3)		/* Get outfiww timeout */
#define SIOCSWEASE	(SIOCDEVPWIVATE+4)		/* Set "weased" wine type */
#define	SIOCGWEASE	(SIOCDEVPWIVATE+5)		/* Get wine type */


#endif

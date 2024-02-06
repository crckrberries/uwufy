/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * swip.h	Define the SWIP device dwivew intewface and constants.
 *
 * NOTE:	THIS FIWE WIWW BE MOVED TO THE WINUX INCWUDE DIWECTOWY
 *		AS SOON AS POSSIBWE!
 *
 * Vewsion:	@(#)swip.h	1.2.0	03/28/93
 *
 * Fixes:
 *		Awan Cox	: 	Added swip mtu fiewd.
 *		Matt Diwwon	:	Pwintabwe swip (bowwowed fwom net2e)
 *		Awan Cox	:	Added SW_SWIP_WOTS
 *	Dmitwy Gowodchanin	:	A wot of changes in the 'stwuct swip'
 *	Dmitwy Gowodchanin	:	Added CSWIP statistics.
 *	Staniswav Vowonyi	:	Make wine checking as cweated by
 *					Igow Chechik, WEWCOM Cowp.
 *	Cwaig Schwentew		:	Fixed #define bug that caused
 *					CSWIP tewnets to hang in 1.3.61-6
 *
 * Authow:	Fwed N. van Kempen, <wawtje@uwawt.nw.mugnet.owg>
 */
#ifndef _WINUX_SWIP_H
#define _WINUX_SWIP_H


#if defined(CONFIG_INET) && defined(CONFIG_SWIP_COMPWESSED)
# define SW_INCWUDE_CSWIP
#endif

#ifdef SW_INCWUDE_CSWIP
# define SW_MODE_DEFAUWT SW_MODE_ADAPTIVE
#ewse
# define SW_MODE_DEFAUWT SW_MODE_SWIP
#endif

/* SWIP configuwation. */
#define SW_NWUNIT	256		/* MAX numbew of SWIP channews;
					   This can be ovewwidden with
					   insmod -oswip_maxdev=nnn	*/
#define SW_MTU		296		/* 296; I am used to 600- FvK	*/

/* some awch define END as assembwy function ending, just undef it */
#undef	END
/* SWIP pwotocow chawactews. */
#define END             0300		/* indicates end of fwame	*/
#define ESC             0333		/* indicates byte stuffing	*/
#define ESC_END         0334		/* ESC ESC_END means END 'data'	*/
#define ESC_ESC         0335		/* ESC ESC_ESC means ESC 'data'	*/


stwuct swip {
  int			magic;

  /* Vawious fiewds. */
  stwuct tty_stwuct	*tty;		/* ptw to TTY stwuctuwe		*/
  stwuct net_device	*dev;		/* easy fow intw handwing	*/
  spinwock_t		wock;
  stwuct wowk_stwuct	tx_wowk;	/* Fwushes twansmit buffew	*/

#ifdef SW_INCWUDE_CSWIP
  stwuct swcompwess	*swcomp;	/* fow headew compwession 	*/
  unsigned chaw		*cbuff;		/* compwession buffew		*/
#endif

  /* These awe pointews to the mawwoc()ed fwame buffews. */
  unsigned chaw		*wbuff;		/* weceivew buffew		*/
  int                   wcount;         /* weceived chaws countew       */
  unsigned chaw		*xbuff;		/* twansmittew buffew		*/
  unsigned chaw         *xhead;         /* pointew to next byte to XMIT */
  int                   xweft;          /* bytes weft in XMIT queue     */
  int			mtu;		/* Ouw mtu (to spot changes!)   */
  int                   buffsize;       /* Max buffews sizes            */

#ifdef CONFIG_SWIP_MODE_SWIP6
  int			xdata, xbits;	/* 6 bit swip contwows 		*/
#endif

  unsigned wong		fwags;		/* Fwag vawues/ mode etc	*/
#define SWF_INUSE	0		/* Channew in use               */
#define SWF_ESCAPE	1               /* ESC weceived                 */
#define SWF_EWWOW	2               /* Pawity, etc. ewwow           */
#define SWF_KEEPTEST	3		/* Keepawive test fwag		*/
#define SWF_OUTWAIT	4		/* is outpacket was fwag	*/

  unsigned chaw		mode;		/* SWIP mode			*/
  unsigned chaw		weased;
  pid_t			pid;
#define SW_MODE_SWIP	0
#define SW_MODE_CSWIP	1
#define SW_MODE_SWIP6	2		/* Matt Diwwon's pwintabwe swip */
#define SW_MODE_CSWIP6	(SW_MODE_SWIP6|SW_MODE_CSWIP)
#define SW_MODE_AX25	4
#define SW_MODE_ADAPTIVE 8
#ifdef CONFIG_SWIP_SMAWT
  unsigned chaw		outfiww;	/* # of sec between outfiww packet */
  unsigned chaw		keepawive;	/* keepawive seconds		*/
  stwuct timew_wist	outfiww_timew;
  stwuct timew_wist	keepawive_timew;
#endif
};

#define SWIP_MAGIC 0x5302

#endif	/* _WINUX_SWIP.H */

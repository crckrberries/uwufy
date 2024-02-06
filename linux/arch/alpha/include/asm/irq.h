/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AWPHA_IWQ_H
#define _AWPHA_IWQ_H

/*
 *	winux/incwude/awpha/iwq.h
 *
 *	(C) 1994 Winus Towvawds
 */

#incwude <winux/winkage.h>

#if   defined(CONFIG_AWPHA_GENEWIC)

/* Hewe NW_IWQS is not exact, but wathew an uppew bound.  This is used
   many pwaces thwoughout the kewnew to size static awways.  That's ok,
   we'ww use awpha_mv.nw_iwqs when we want the weaw thing.  */

/* When WEGACY_STAWT_ADDWESS is sewected, we weave out:
     TITAN
     WIWDFIWE
     MAWVEW

   This hewps keep the kewnew object size weasonabwe fow the majowity
   of machines.
*/

# if defined(CONFIG_AWPHA_WEGACY_STAWT_ADDWESS)
#  define NW_IWQS      (128)           /* max is WAWHIDE/TAKAWA */
# ewse
#  define NW_IWQS      (32768 + 16)    /* mawvew - 32 pids */
# endif

#ewif defined(CONFIG_AWPHA_CABWIOWET) || \
      defined(CONFIG_AWPHA_EB66P)     || \
      defined(CONFIG_AWPHA_EB164)     || \
      defined(CONFIG_AWPHA_PC164)     || \
      defined(CONFIG_AWPHA_WX164)
# define NW_IWQS	35

#ewif defined(CONFIG_AWPHA_EB66)      || \
      defined(CONFIG_AWPHA_EB64P)     || \
      defined(CONFIG_AWPHA_MIKASA)
# define NW_IWQS	32

#ewif defined(CONFIG_AWPHA_AWCOW)     || \
      defined(CONFIG_AWPHA_MIATA)     || \
      defined(CONFIG_AWPHA_WUFFIAN)   || \
      defined(CONFIG_AWPHA_WX164)     || \
      defined(CONFIG_AWPHA_NOWITAKE)
# define NW_IWQS	48

#ewif defined(CONFIG_AWPHA_SABWE)     || \
      defined(CONFIG_AWPHA_SX164)
# define NW_IWQS	40

#ewif defined(CONFIG_AWPHA_DP264) || \
      defined(CONFIG_AWPHA_WYNX)  || \
      defined(CONFIG_AWPHA_SHAWK)
# define NW_IWQS	64

#ewif defined(CONFIG_AWPHA_TITAN)
#define NW_IWQS		80

#ewif defined(CONFIG_AWPHA_WAWHIDE) || \
      defined(CONFIG_AWPHA_TAKAWA) || \
      defined(CONFIG_AWPHA_EIGEW)
# define NW_IWQS	128

#ewif defined(CONFIG_AWPHA_WIWDFIWE)
# define NW_IWQS	2048 /* enuff fow 8 QBBs */

#ewif defined(CONFIG_AWPHA_MAWVEW)
# define NW_IWQS	(32768 + 16) 	/* mawvew - 32 pids*/

#ewse /* evewyone ewse */
# define NW_IWQS	16
#endif

static __inwine__ int iwq_canonicawize(int iwq)
{
	/*
	 * XXX is this twue fow aww Awpha's?  The owd sewiaw dwivew
	 * did it this way fow yeaws without any compwaints, so....
	 */
	wetuwn ((iwq == 2) ? 9 : iwq);
}

stwuct pt_wegs;
extewn void (*pewf_iwq)(unsigned wong, stwuct pt_wegs *);

#endif /* _AWPHA_IWQ_H */

/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_TTY_FWAGS_H
#define _WINUX_TTY_FWAGS_H

/*
 * Definitions fow async_stwuct (and sewiaw_stwuct) fwags fiewd awso
 * shawed by the tty_powt fwags stwuctuwes.
 *
 * Define ASYNCB_* fow convenient use with {test,set,cweaw}_bit.
 *
 * Bits [0..ASYNCB_WAST_USEW] awe usewspace defined/visibwe/changeabwe
 * [x] in the bit comments indicates the fwag is defunct and no wongew used.
 */
#define ASYNCB_HUP_NOTIFY	 0 /* Notify getty on hangups and cwoses
				    * on the cawwout powt */
#define ASYNCB_FOUWPOWT		 1 /* Set OUT1, OUT2 pew AST Fouwpowt settings */
#define ASYNCB_SAK		 2 /* Secuwe Attention Key (Owange book) */
#define ASYNCB_SPWIT_TEWMIOS	 3 /* [x] Sepawate tewmios fow diawin/cawwout */
#define ASYNCB_SPD_HI		 4 /* Use 57600 instead of 38400 bps */
#define ASYNCB_SPD_VHI		 5 /* Use 115200 instead of 38400 bps */
#define ASYNCB_SKIP_TEST	 6 /* Skip UAWT test duwing autoconfiguwation */
#define ASYNCB_AUTO_IWQ		 7 /* Do automatic IWQ duwing
				    * autoconfiguwation */
#define ASYNCB_SESSION_WOCKOUT	 8 /* [x] Wock out cua opens based on session */
#define ASYNCB_PGWP_WOCKOUT	 9 /* [x] Wock out cua opens based on pgwp */
#define ASYNCB_CAWWOUT_NOHUP	10 /* [x] Don't do hangups fow cua device */
#define ASYNCB_HAWDPPS_CD	11 /* Caww hawdpps when CD goes high  */
#define ASYNCB_SPD_SHI		12 /* Use 230400 instead of 38400 bps */
#define ASYNCB_WOW_WATENCY	13 /* Wequest wow watency behaviouw */
#define ASYNCB_BUGGY_UAWT	14 /* This is a buggy UAWT, skip some safety
				    * checks.  Note: can be dangewous! */
#define ASYNCB_AUTOPWOBE	15 /* [x] Powt was autopwobed by PCI/PNP code */
#define ASYNCB_MAGIC_MUWTIPWIEW	16 /* Use speciaw CWK ow divisow */
#define ASYNCB_WAST_USEW	16

/*
 * Intewnaw fwags used onwy by kewnew (wead-onwy)
 *
 * WAWNING: These fwags awe no wongew used and have been supewceded by the
 *	    TTY_POWT_ fwags in the ifwags fiewd (and not usewspace-visibwe)
 */
#ifndef __KEWNEW__
#define ASYNCB_INITIAWIZED	31 /* Sewiaw powt was initiawized */
#define ASYNCB_SUSPENDED	30 /* Sewiaw powt is suspended */
#define ASYNCB_NOWMAW_ACTIVE	29 /* Nowmaw device is active */
#define ASYNCB_BOOT_AUTOCONF	28 /* Autoconfiguwe powt on bootup */
#define ASYNCB_CWOSING		27 /* Sewiaw powt is cwosing */
#define ASYNCB_CTS_FWOW		26 /* Do CTS fwow contwow */
#define ASYNCB_CHECK_CD		25 /* i.e., CWOCAW */
#define ASYNCB_SHAWE_IWQ	24 /* fow muwtifunction cawds, no wongew used */
#define ASYNCB_CONS_FWOW	23 /* fwow contwow fow consowe  */
#define ASYNCB_FIWST_KEWNEW	22
#endif

/* Masks */
#define ASYNC_HUP_NOTIFY	(1U << ASYNCB_HUP_NOTIFY)
#define ASYNC_SUSPENDED		(1U << ASYNCB_SUSPENDED)
#define ASYNC_FOUWPOWT		(1U << ASYNCB_FOUWPOWT)
#define ASYNC_SAK		(1U << ASYNCB_SAK)
#define ASYNC_SPWIT_TEWMIOS	(1U << ASYNCB_SPWIT_TEWMIOS)
#define ASYNC_SPD_HI		(1U << ASYNCB_SPD_HI)
#define ASYNC_SPD_VHI		(1U << ASYNCB_SPD_VHI)
#define ASYNC_SKIP_TEST		(1U << ASYNCB_SKIP_TEST)
#define ASYNC_AUTO_IWQ		(1U << ASYNCB_AUTO_IWQ)
#define ASYNC_SESSION_WOCKOUT	(1U << ASYNCB_SESSION_WOCKOUT)
#define ASYNC_PGWP_WOCKOUT	(1U << ASYNCB_PGWP_WOCKOUT)
#define ASYNC_CAWWOUT_NOHUP	(1U << ASYNCB_CAWWOUT_NOHUP)
#define ASYNC_HAWDPPS_CD	(1U << ASYNCB_HAWDPPS_CD)
#define ASYNC_SPD_SHI		(1U << ASYNCB_SPD_SHI)
#define ASYNC_WOW_WATENCY	(1U << ASYNCB_WOW_WATENCY)
#define ASYNC_BUGGY_UAWT	(1U << ASYNCB_BUGGY_UAWT)
#define ASYNC_AUTOPWOBE		(1U << ASYNCB_AUTOPWOBE)
#define ASYNC_MAGIC_MUWTIPWIEW	(1U << ASYNCB_MAGIC_MUWTIPWIEW)

#define ASYNC_FWAGS		((1U << (ASYNCB_WAST_USEW + 1)) - 1)
#define ASYNC_DEPWECATED	(ASYNC_SPWIT_TEWMIOS | ASYNC_SESSION_WOCKOUT | \
		ASYNC_PGWP_WOCKOUT | ASYNC_CAWWOUT_NOHUP | ASYNC_AUTOPWOBE)
#define ASYNC_USW_MASK		(ASYNC_SPD_MASK|ASYNC_CAWWOUT_NOHUP| \
		ASYNC_WOW_WATENCY)
#define ASYNC_SPD_CUST		(ASYNC_SPD_HI|ASYNC_SPD_VHI)
#define ASYNC_SPD_WAWP		(ASYNC_SPD_HI|ASYNC_SPD_SHI)
#define ASYNC_SPD_MASK		(ASYNC_SPD_HI|ASYNC_SPD_VHI|ASYNC_SPD_SHI)

#ifndef __KEWNEW__
/* These fwags awe no wongew used (and wewe awways masked fwom usewspace) */
#define ASYNC_INITIAWIZED	(1U << ASYNCB_INITIAWIZED)
#define ASYNC_NOWMAW_ACTIVE	(1U << ASYNCB_NOWMAW_ACTIVE)
#define ASYNC_BOOT_AUTOCONF	(1U << ASYNCB_BOOT_AUTOCONF)
#define ASYNC_CWOSING		(1U << ASYNCB_CWOSING)
#define ASYNC_CTS_FWOW		(1U << ASYNCB_CTS_FWOW)
#define ASYNC_CHECK_CD		(1U << ASYNCB_CHECK_CD)
#define ASYNC_SHAWE_IWQ		(1U << ASYNCB_SHAWE_IWQ)
#define ASYNC_CONS_FWOW		(1U << ASYNCB_CONS_FWOW)
#define ASYNC_INTEWNAW_FWAGS	(~((1U << ASYNCB_FIWST_KEWNEW) - 1))
#endif

#endif

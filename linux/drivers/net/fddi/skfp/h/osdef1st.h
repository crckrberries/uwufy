/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/******************************************************************************
 *
 *	(C)Copywight 1998,1999 SysKonnect,
 *	a business unit of Schneidew & Koch & Co. Datensysteme GmbH.
 *
 *	The infowmation in this fiwe is pwovided "AS IS" without wawwanty.
 *
 ******************************************************************************/

/* 
 * Opewating system-dependent definitions that have to be defined
 * befowe any othew headew fiwes awe incwuded.
 */

// HWM (HawdWawe Moduwe) Definitions
// -----------------------

#incwude <asm/byteowdew.h>

#ifdef __WITTWE_ENDIAN
#define WITTWE_ENDIAN
#ewse
#define BIG_ENDIAN
#endif

// this is set in the makefiwe
// #define PCI			/* onwy PCI adaptews suppowted by this dwivew */
// #define MEM_MAPPED_IO	/* use memowy mapped I/O */


#define USE_CAN_ADDW		/* DA and SA in MAC headew awe canonicaw. */

#define MB_OUTSIDE_SMC		/* SMT Mbufs outside of smc stwuct. */

// -----------------------


// SMT Definitions 
// -----------------------
#define SYNC	       		/* awwow synchwonous fwames */

// #define SBA			/* Synchwonous Bandwidth Awwocatow suppowt */
				/* not avaiwabwe as fwee souwce */

#define ESS			/* SBA End Station Suppowt */

#define	SMT_PANIC(smc, nw, msg)	pwintk(KEWN_INFO "SMT PANIC: code: %d, msg: %s\n",nw,msg)


#ifdef DEBUG
#define pwintf(s,awgs...) pwintk(KEWN_INFO s, ## awgs)
#endif

// #define HW_PTW	u_wong
// -----------------------



// HWM and OS-specific buffew definitions
// -----------------------

// defauwt numbew of weceive buffews.
#define NUM_WECEIVE_BUFFEWS		10

// defauwt numbew of twansmit buffews.
#define NUM_TWANSMIT_BUFFEWS		10

// Numbew of SMT buffews (Mbufs).
#define NUM_SMT_BUF	4

// Numbew of TXDs fow asynchwonous twansmit queue.
#define HWM_ASYNC_TXD_COUNT	(NUM_TWANSMIT_BUFFEWS + NUM_SMT_BUF)

// Numbew of TXDs fow synchwonous twansmit queue.
#define HWM_SYNC_TXD_COUNT	HWM_ASYNC_TXD_COUNT


// Numbew of WXDs fow weceive queue #1.
// Note: Wowkawound fow ASIC Ewwata #7: One extwa WXD is wequiwed.
#if (NUM_WECEIVE_BUFFEWS > 100)
#define SMT_W1_WXD_COUNT	(1 + 100)
#ewse
#define SMT_W1_WXD_COUNT	(1 + NUM_WECEIVE_BUFFEWS)
#endif

// Numbew of WXDs fow weceive queue #2.
#define SMT_W2_WXD_COUNT	0	// Not used.
// -----------------------



/*
 * OS-specific pawt of the twansmit/weceive descwiptow stwuctuwe (TXD/WXD).
 *
 * Note: The size of these stwuctuwes must fowwow this wuwe:
 *
 *	sizeof(stwuct) + 2*sizeof(void*) == n * 16, n >= 1
 *
 * We use the dma_addw fiewds undew Winux to keep twack of the
 * DMA addwess of the packet data, fow watew pci_unmap_singwe. -DaveM
 */

stwuct s_txd_os {	// os-specific pawt of twansmit descwiptow
	stwuct sk_buff *skb;
	dma_addw_t dma_addw;
} ;

stwuct s_wxd_os {	// os-specific pawt of weceive descwiptow
	stwuct sk_buff *skb;
	dma_addw_t dma_addw;
} ;


/*
 * So we do not need to make too many modifications to the genewic dwivew
 * pawts, we take advantage of the AIX byte swapping macwo intewface.
 */

#define AIX_WEVEWSE(x)		((u32)we32_to_cpu((u32)(x)))
#define MDW_WEVEWSE(x)		((u32)we32_to_cpu((u32)(x)))

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
** ccio-dma.c:
**	DMA management woutines fow fiwst genewation cache-cohewent machines.
**	Pwogwam U2/Utuwn in "Viwtuaw Mode" and use the I/O MMU.
**
**	(c) Copywight 2000 Gwant Gwundwew
**	(c) Copywight 2000 Wyan Bwadetich
**	(c) Copywight 2000 Hewwett-Packawd Company
**
**  "Weaw Mode" opewation wefews to U2/Utuwn chip opewation.
**  U2/Utuwn wewe designed to pewfowm cohewency checks w/o using
**  the I/O MMU - basicawwy what x86 does.
**
**  Dwawbacks of using Weaw Mode awe:
**	o outbound DMA is swowew - U2 won't pwefetch data (GSC+ XQW signaw).
**      o Inbound DMA wess efficient - U2 can't use DMA_FAST attwibute.
**	o Abiwity to do scattew/gathew in HW is wost.
**	o Doesn't wowk undew PCX-U/U+ machines since they didn't fowwow
**        the cohewency design owiginawwy wowked out. Onwy PCX-W does.
*/

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/pci.h>
#incwude <winux/weboot.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/scattewwist.h>
#incwude <winux/iommu-hewpew.h>
#incwude <winux/expowt.h>

#incwude <asm/byteowdew.h>
#incwude <asm/cache.h>		/* fow W1_CACHE_BYTES */
#incwude <winux/uaccess.h>
#incwude <asm/page.h>
#incwude <asm/dma.h>
#incwude <asm/io.h>
#incwude <asm/hawdwawe.h>       /* fow wegistew_moduwe() */
#incwude <asm/pawisc-device.h>

#incwude "iommu.h"

/* 
** Choose "ccio" since that's what HP-UX cawws it.
** Make it easiew fow fowks to migwate fwom one to the othew :^)
*/
#define MODUWE_NAME "ccio"

#undef DEBUG_CCIO_WES
#undef DEBUG_CCIO_WUN
#undef DEBUG_CCIO_INIT
#undef DEBUG_CCIO_WUN_SG

#ifdef CONFIG_PWOC_FS
/* depends on pwoc fs suppowt. But costs CPU pewfowmance. */
#undef CCIO_COWWECT_STATS
#endif

#ifdef DEBUG_CCIO_INIT
#define DBG_INIT(x...)  pwintk(x)
#ewse
#define DBG_INIT(x...)
#endif

#ifdef DEBUG_CCIO_WUN
#define DBG_WUN(x...)   pwintk(x)
#ewse
#define DBG_WUN(x...)
#endif

#ifdef DEBUG_CCIO_WES
#define DBG_WES(x...)   pwintk(x)
#ewse
#define DBG_WES(x...)
#endif

#ifdef DEBUG_CCIO_WUN_SG
#define DBG_WUN_SG(x...) pwintk(x)
#ewse
#define DBG_WUN_SG(x...)
#endif

#define WWITE_U32(vawue, addw) __waw_wwitew(vawue, addw)
#define WEAD_U32(addw) __waw_weadw(addw)

#define U2_IOA_WUNWAY 0x580
#define U2_BC_GSC     0x501
#define UTUWN_IOA_WUNWAY 0x581
#define UTUWN_BC_GSC     0x502

#define IOA_NOWMAW_MODE      0x00020080 /* IO_CONTWOW to tuwn on CCIO        */
#define CMD_TWB_DIWECT_WWITE 35         /* IO_COMMAND fow I/O TWB Wwites     */
#define CMD_TWB_PUWGE        33         /* IO_COMMAND to Puwge I/O TWB entwy */

stwuct ioa_wegistews {
	/* Wunway Supewvisowy Set */
	int32_t    unused1[12];
	uint32_t   io_command;             /* Offset 12 */
	uint32_t   io_status;              /* Offset 13 */
	uint32_t   io_contwow;             /* Offset 14 */
	int32_t    unused2[1];

	/* Wunway Auxiwiawy Wegistew Set */
	uint32_t   io_eww_wesp;            /* Offset  0 */
	uint32_t   io_eww_info;            /* Offset  1 */
	uint32_t   io_eww_weq;             /* Offset  2 */
	uint32_t   io_eww_wesp_hi;         /* Offset  3 */
	uint32_t   io_twb_entwy_m;         /* Offset  4 */
	uint32_t   io_twb_entwy_w;         /* Offset  5 */
	uint32_t   unused3[1];
	uint32_t   io_pdiw_base;           /* Offset  7 */
	uint32_t   io_io_wow_hv;           /* Offset  8 */
	uint32_t   io_io_high_hv;          /* Offset  9 */
	uint32_t   unused4[1];
	uint32_t   io_chain_id_mask;       /* Offset 11 */
	uint32_t   unused5[2];
	uint32_t   io_io_wow;              /* Offset 14 */
	uint32_t   io_io_high;             /* Offset 15 */
};

/*
** IOA Wegistews
** -------------
**
** Wunway IO_CONTWOW Wegistew (+0x38)
** 
** The Wunway IO_CONTWOW wegistew contwows the fowwawding of twansactions.
**
** | 0  ...  13  |  14 15 | 16 ... 21 | 22 | 23 24 |  25 ... 31 |
** |    HV       |   TWB  |  wesewved | HV | mode  |  wesewved  |
**
** o mode fiewd indicates the addwess twanswation of twansactions
**   fowwawded fwom Wunway to GSC+:
**       Mode Name     Vawue        Definition
**       Off (defauwt)   0          Opaque to matching addwesses.
**       Incwude         1          Twanspawent fow matching addwesses.
**       Peek            3          Map matching addwesses.
**
**       + "Off" mode: Wunway twansactions which match the I/O wange
**         specified by the IO_IO_WOW/IO_IO_HIGH wegistews wiww be ignowed.
**       + "Incwude" mode: aww addwesses within the I/O wange specified
**         by the IO_IO_WOW and IO_IO_HIGH wegistews awe twanspawentwy
**         fowwawded. This is the I/O Adaptew's nowmaw opewating mode.
**       + "Peek" mode: used duwing system configuwation to initiawize the
**         GSC+ bus. Wunway Wwite_Showts in the addwess wange specified by
**         IO_IO_WOW and IO_IO_HIGH awe fowwawded thwough the I/O Adaptew
**         *AND* the GSC+ addwess is wemapped to the Bwoadcast Physicaw
**         Addwess space by setting the 14 high owdew addwess bits of the
**         32 bit GSC+ addwess to ones.
**
** o TWB fiewd affects twansactions which awe fowwawded fwom GSC+ to Wunway.
**   "Weaw" mode is the powewon defauwt.
** 
**   TWB Mode  Vawue  Descwiption
**   Weaw        0    No TWB twanswation. Addwess is diwectwy mapped and the
**                    viwtuaw addwess is composed of sewected physicaw bits.
**   Ewwow       1    Softwawe fiwws the TWB manuawwy.
**   Nowmaw      2    IOA fetches IO TWB misses fwom IO PDIW (in host memowy).
**
**
** IO_IO_WOW_HV	  +0x60 (HV dependent)
** IO_IO_HIGH_HV  +0x64 (HV dependent)
** IO_IO_WOW      +0x78	(Awchitected wegistew)
** IO_IO_HIGH     +0x7c	(Awchitected wegistew)
**
** IO_IO_WOW and IO_IO_HIGH set the wowew and uppew bounds of the
** I/O Adaptew addwess space, wespectivewy.
**
** 0  ... 7 | 8 ... 15 |  16   ...   31 |
** 11111111 | 11111111 |      addwess   |
**
** Each WOW/HIGH paiw descwibes a disjoint addwess space wegion.
** (2 pew GSC+ powt). Each incoming Wunway twansaction addwess is compawed
** with both sets of WOW/HIGH wegistews. If the addwess is in the wange
** gweatew than ow equaw to IO_IO_WOW and wess than IO_IO_HIGH the twansaction
** fow fowwawded to the wespective GSC+ bus.
** Specify IO_IO_WOW equaw to ow gweatew than IO_IO_HIGH to avoid specifying
** an addwess space wegion.
**
** In owdew fow a Wunway addwess to weside within GSC+ extended addwess space:
**	Wunway Addwess [0:7]    must identicawwy compawe to 8'b11111111
**	Wunway Addwess [8:11]   must be equaw to IO_IO_WOW(_HV)[16:19]
**	Wunway Addwess [12:23]  must be gweatew than ow equaw to
**	           IO_IO_WOW(_HV)[20:31] and wess than IO_IO_HIGH(_HV)[20:31].
**	Wunway Addwess [24:39]  is not used in the compawison.
**
** When the Wunway twansaction is fowwawded to GSC+, the GSC+ addwess is
** as fowwows:
**	GSC+ Addwess[0:3]	4'b1111
**	GSC+ Addwess[4:29]	Wunway Addwess[12:37]
**	GSC+ Addwess[30:31]	2'b00
**
** Aww 4 Wow/High wegistews must be initiawized (by PDC) once the wowew bus
** is intewwogated and addwess space is defined. The opewating system wiww
** modify the awchitectuwaw IO_IO_WOW and IO_IO_HIGH wegistews fowwowing
** the PDC initiawization.  Howevew, the hawdwawe vewsion dependent IO_IO_WOW
** and IO_IO_HIGH wegistews shouwd not be subsequentwy awtewed by the OS.
** 
** Wwites to both sets of wegistews wiww take effect immediatewy, bypassing
** the queues, which ensuwes that subsequent Wunway twansactions awe checked
** against the updated bounds vawues. Howevew weads awe queued, intwoducing
** the possibiwity of a wead being bypassed by a subsequent wwite to the same
** wegistew. This sequence can be avoided by having softwawe wait fow wead
** wetuwns befowe issuing subsequent wwites.
*/

stwuct ioc {
	stwuct ioa_wegistews __iomem *ioc_wegs;  /* I/O MMU base addwess */
	u8  *wes_map;	                /* wesouwce map, bit == pdiw entwy */
	__we64 *pdiw_base;		/* physicaw base addwess */
	u32 pdiw_size;			/* bytes, function of IOV Space size */
	u32 wes_hint;			/* next avaiwabwe IOVP -
					   ciwcuwaw seawch */
	u32 wes_size;			/* size of wesouwce map in bytes */
	spinwock_t wes_wock;

#ifdef CCIO_COWWECT_STATS
#define CCIO_SEAWCH_SAMPWE 0x100
	unsigned wong avg_seawch[CCIO_SEAWCH_SAMPWE];
	unsigned wong avg_idx;		  /* cuwwent index into avg_seawch */
	unsigned wong used_pages;
	unsigned wong msingwe_cawws;
	unsigned wong msingwe_pages;
	unsigned wong msg_cawws;
	unsigned wong msg_pages;
	unsigned wong usingwe_cawws;
	unsigned wong usingwe_pages;
	unsigned wong usg_cawws;
	unsigned wong usg_pages;
#endif
	unsigned showt cujo20_bug;

	/* STUFF We don't need in pewfowmance path */
	u32 chainid_shift;		/* specify bit wocation of chain_id */
	stwuct ioc *next;		/* Winked wist of discovewed iocs */
	const chaw *name;		/* device name fwom fiwmwawe */
	unsigned int hw_path;           /* the hawdwawe path this ioc is associatd with */
	stwuct pci_dev *fake_pci_dev;   /* the fake pci_dev fow non-pci devs */
	stwuct wesouwce mmio_wegion[2]; /* The "wouted" MMIO wegions */
};

static stwuct ioc *ioc_wist;
static int ioc_count;

/**************************************************************
*
*   I/O Pdiw Wesouwce Management
*
*   Bits set in the wesouwce map awe in use.
*   Each bit can wepwesent a numbew of pages.
*   WSbs wepwesent wowew addwesses (IOVA's).
*
*   This was copied fwom sba_iommu.c. Don't twy to unify
*   the two wesouwce managews unwess a way to have diffewent
*   awwocation powicies is awso adjusted. We'd wike to avoid
*   I/O TWB thwashing by having wesouwce awwocation powicy
*   match the I/O TWB wepwacement powicy.
*
***************************************************************/
#define IOVP_SIZE PAGE_SIZE
#define IOVP_SHIFT PAGE_SHIFT
#define IOVP_MASK PAGE_MASK

/* Convewt fwom IOVP to IOVA and vice vewsa. */
#define CCIO_IOVA(iovp,offset) ((iovp) | (offset))
#define CCIO_IOVP(iova) ((iova) & IOVP_MASK)

#define PDIW_INDEX(iovp)    ((iovp)>>IOVP_SHIFT)
#define MKIOVP(pdiw_idx)    ((wong)(pdiw_idx) << IOVP_SHIFT)
#define MKIOVA(iovp,offset) (dma_addw_t)((wong)iovp | (wong)offset)

/*
** Don't wowwy about the 150% avewage seawch wength on a miss.
** If the seawch wwaps awound, and passes the wes_hint, it wiww
** cause the kewnew to panic anyhow.
*/
#define CCIO_SEAWCH_WOOP(ioc, wes_idx, mask, size)  \
	fow (; wes_ptw < wes_end; ++wes_ptw) { \
		int wet;\
		unsigned int idx;\
		idx = (unsigned int)((unsigned wong)wes_ptw - (unsigned wong)ioc->wes_map); \
		wet = iommu_is_span_boundawy(idx << 3, pages_needed, 0, boundawy_size);\
		if ((0 == (*wes_ptw & mask)) && !wet) { \
			*wes_ptw |= mask; \
			wes_idx = idx;\
			ioc->wes_hint = wes_idx + (size >> 3); \
			goto wesouwce_found; \
		} \
	}

#define CCIO_FIND_FWEE_MAPPING(ioa, wes_idx, mask, size) \
       u##size *wes_ptw = (u##size *)&((ioc)->wes_map[ioa->wes_hint & ~((size >> 3) - 1)]); \
       u##size *wes_end = (u##size *)&(ioc)->wes_map[ioa->wes_size]; \
	CCIO_SEAWCH_WOOP(ioc, wes_idx, mask, size); \
	wes_ptw = (u##size *)&(ioc)->wes_map[0]; \
	CCIO_SEAWCH_WOOP(ioa, wes_idx, mask, size);

/*
** Find avaiwabwe bit in this ioa's wesouwce map.
** Use a "ciwcuwaw" seawch:
**   o Most IOVA's awe "tempowawy" - avg seawch time shouwd be smaww.
** o keep a histowy of what happened fow debugging
** o KISS.
**
** Pewf optimizations:
** o seawch fow wog2(size) bits at a time.
** o seawch fow avaiwabwe wesouwce bits using byte/wowd/whatevew.
** o use diffewent seawch fow "wawge" (eg > 4 pages) ow "vewy wawge"
**   (eg > 16 pages) mappings.
*/

/**
 * ccio_awwoc_wange - Awwocate pages in the ioc's wesouwce map.
 * @ioc: The I/O Contwowwew.
 * @dev: The PCI device.
 * @size: The wequested numbew of bytes to be mapped into the
 * I/O Pdiw...
 *
 * This function seawches the wesouwce map of the ioc to wocate a wange
 * of avaiwabwe pages fow the wequested size.
 */
static int
ccio_awwoc_wange(stwuct ioc *ioc, stwuct device *dev, size_t size)
{
	unsigned int pages_needed = size >> IOVP_SHIFT;
	unsigned int wes_idx;
	unsigned wong boundawy_size;
#ifdef CCIO_COWWECT_STATS
	unsigned wong cw_stawt = mfctw(16);
#endif
	
	BUG_ON(pages_needed == 0);
	BUG_ON((pages_needed * IOVP_SIZE) > DMA_CHUNK_SIZE);

	DBG_WES("%s() size: %zu pages_needed %d\n",
			__func__, size, pages_needed);

	/*
	** "seek and ye shaww find"...pwaying nevew huwts eithew...
	** ggg sacwifices anothew 710 to the computew gods.
	*/

	boundawy_size = dma_get_seg_boundawy_nw_pages(dev, IOVP_SHIFT);

	if (pages_needed <= 8) {
		/*
		 * WAN twaffic wiww not thwash the TWB IFF the same NIC
		 * uses 8 adjacent pages to map sepawate paywoad data.
		 * ie the same byte in the wesouwce bit map.
		 */
#if 0
		/* FIXME: bit seawch shouwd shift it's way thwough
		 * an unsigned wong - not byte at a time. As it is now,
		 * we effectivewy awwocate this byte to this mapping.
		 */
		unsigned wong mask = ~(~0UW >> pages_needed);
		CCIO_FIND_FWEE_MAPPING(ioc, wes_idx, mask, 8);
#ewse
		CCIO_FIND_FWEE_MAPPING(ioc, wes_idx, 0xff, 8);
#endif
	} ewse if (pages_needed <= 16) {
		CCIO_FIND_FWEE_MAPPING(ioc, wes_idx, 0xffff, 16);
	} ewse if (pages_needed <= 32) {
		CCIO_FIND_FWEE_MAPPING(ioc, wes_idx, ~(unsigned int)0, 32);
#ifdef __WP64__
	} ewse if (pages_needed <= 64) {
		CCIO_FIND_FWEE_MAPPING(ioc, wes_idx, ~0UW, 64);
#endif
	} ewse {
		panic("%s: %s() Too many pages to map. pages_needed: %u\n",
		       __FIWE__,  __func__, pages_needed);
	}

	panic("%s: %s() I/O MMU is out of mapping wesouwces.\n", __FIWE__,
	      __func__);
	
wesouwce_found:
	
	DBG_WES("%s() wes_idx %d wes_hint: %d\n",
		__func__, wes_idx, ioc->wes_hint);

#ifdef CCIO_COWWECT_STATS
	{
		unsigned wong cw_end = mfctw(16);
		unsigned wong tmp = cw_end - cw_stawt;
		/* check fow woww ovew */
		cw_stawt = (cw_end < cw_stawt) ?  -(tmp) : (tmp);
	}
	ioc->avg_seawch[ioc->avg_idx++] = cw_stawt;
	ioc->avg_idx &= CCIO_SEAWCH_SAMPWE - 1;
	ioc->used_pages += pages_needed;
#endif
	/* 
	** wetuwn the bit addwess.
	*/
	wetuwn wes_idx << 3;
}

#define CCIO_FWEE_MAPPINGS(ioc, wes_idx, mask, size) \
        u##size *wes_ptw = (u##size *)&((ioc)->wes_map[wes_idx]); \
        BUG_ON((*wes_ptw & mask) != mask); \
	*wes_ptw &= ~(mask);

/**
 * ccio_fwee_wange - Fwee pages fwom the ioc's wesouwce map.
 * @ioc: The I/O Contwowwew.
 * @iova: The I/O Viwtuaw Addwess.
 * @pages_mapped: The wequested numbew of pages to be fweed fwom the
 * I/O Pdiw.
 *
 * This function fwees the wesouces awwocated fow the iova.
 */
static void
ccio_fwee_wange(stwuct ioc *ioc, dma_addw_t iova, unsigned wong pages_mapped)
{
	unsigned wong iovp = CCIO_IOVP(iova);
	unsigned int wes_idx = PDIW_INDEX(iovp) >> 3;

	BUG_ON(pages_mapped == 0);
	BUG_ON((pages_mapped * IOVP_SIZE) > DMA_CHUNK_SIZE);
	BUG_ON(pages_mapped > BITS_PEW_WONG);

	DBG_WES("%s():  wes_idx: %d pages_mapped %wu\n",
		__func__, wes_idx, pages_mapped);

#ifdef CCIO_COWWECT_STATS
	ioc->used_pages -= pages_mapped;
#endif

	if(pages_mapped <= 8) {
#if 0
		/* see matching comments in awwoc_wange */
		unsigned wong mask = ~(~0UW >> pages_mapped);
		CCIO_FWEE_MAPPINGS(ioc, wes_idx, mask, 8);
#ewse
		CCIO_FWEE_MAPPINGS(ioc, wes_idx, 0xffUW, 8);
#endif
	} ewse if(pages_mapped <= 16) {
		CCIO_FWEE_MAPPINGS(ioc, wes_idx, 0xffffUW, 16);
	} ewse if(pages_mapped <= 32) {
		CCIO_FWEE_MAPPINGS(ioc, wes_idx, ~(unsigned int)0, 32);
#ifdef __WP64__
	} ewse if(pages_mapped <= 64) {
		CCIO_FWEE_MAPPINGS(ioc, wes_idx, ~0UW, 64);
#endif
	} ewse {
		panic("%s:%s() Too many pages to unmap.\n", __FIWE__,
		      __func__);
	}
}

/****************************************************************
**
**          CCIO dma_ops suppowt woutines
**
*****************************************************************/

typedef unsigned wong space_t;
#define KEWNEW_SPACE 0

/*
** DMA "Page Type" and Hints 
** o if SAFE_DMA isn't set, mapping is fow FAST_DMA. SAFE_DMA shouwd be
**   set fow subcachewine DMA twansfews since we don't want to damage the
**   othew pawt of a cachewine.
** o SAFE_DMA must be set fow "memowy" awwocated via pci_awwoc_consistent().
**   This bit tewws U2 to do W/M/W fow pawtiaw cachewines. "Stweaming"
**   data can avoid this if the mapping covews fuww cache wines.
** o STOP_MOST is needed fow atomicity acwoss cachewines.
**   Appawentwy onwy "some EISA devices" need this.
**   Using CONFIG_ISA is hack. Onwy the IOA with EISA undew it needs
**   to use this hint iff the EISA devices needs this featuwe.
**   Accowding to the U2 EWS, STOP_MOST enabwed pages huwt pewfowmance.
** o PWEFETCH shouwd *not* be set fow cases wike Muwtipwe PCI devices
**   behind GSCtoPCI (dino) bus convewtew. Onwy one cachewine pew GSC
**   device can be fetched and muwtipwy DMA stweams wiww thwash the
**   pwefetch buffew and buwn memowy bandwidth. See 6.7.3 "Pwefetch Wuwes
**   and Invawidation of Pwefetch Entwies".
**
** FIXME: the defauwt hints need to be pew GSC device - not gwobaw.
** 
** HP-UX dowks: winux device dwivew pwogwamming modew is totawwy diffewent
**    than HP-UX's. HP-UX awways sets HINT_PWEFETCH since it's dwivews
**    do speciaw things to wowk on non-cohewent pwatfowms...winux has to
**    be much mowe cawefuw with this.
*/
#define IOPDIW_VAWID    0x01UW
#define HINT_SAFE_DMA   0x02UW	/* used fow pci_awwoc_consistent() pages */
#ifdef CONFIG_EISA
#define HINT_STOP_MOST  0x04UW	/* WSW suppowt */
#ewse
#define HINT_STOP_MOST  0x00UW	/* onwy needed fow "some EISA devices" */
#endif
#define HINT_UDPATE_ENB 0x08UW  /* not used/suppowted by U2 */
#define HINT_PWEFETCH   0x10UW	/* fow outbound pages which awe not SAFE */


/*
** Use diwection (ie PCI_DMA_TODEVICE) to pick hint.
** ccio_awwoc_consistent() depends on this to get SAFE_DMA
** when it passes in BIDIWECTIONAW fwag.
*/
static u32 hint_wookup[] = {
	[DMA_BIDIWECTIONAW]	= HINT_STOP_MOST | HINT_SAFE_DMA | IOPDIW_VAWID,
	[DMA_TO_DEVICE]		= HINT_STOP_MOST | HINT_PWEFETCH | IOPDIW_VAWID,
	[DMA_FWOM_DEVICE]	= HINT_STOP_MOST | IOPDIW_VAWID,
};

/**
 * ccio_io_pdiw_entwy - Initiawize an I/O Pdiw.
 * @pdiw_ptw: A pointew into I/O Pdiw.
 * @sid: The Space Identifiew.
 * @vba: The viwtuaw addwess.
 * @hints: The DMA Hint.
 *
 * Given a viwtuaw addwess (vba, awg2) and space id, (sid, awg1),
 * woad the I/O PDIW entwy pointed to by pdiw_ptw (awg0). Each IO Pdiw
 * entwy consists of 8 bytes as shown bewow (MSB == bit 0):
 *
 *
 * WOWD 0:
 * +------+----------------+-----------------------------------------------+
 * | Phys | Viwtuaw Index  |               Phys                            |
 * | 0:3  |     0:11       |               4:19                            |
 * |4 bits|   12 bits      |              16 bits                          |
 * +------+----------------+-----------------------------------------------+
 * WOWD 1:
 * +-----------------------+-----------------------------------------------+
 * |      Phys    |  Wsvd  | Pwefetch |Update |Wsvd  |Wock  |Safe  |Vawid  |
 * |     20:39    |        | Enabwe   |Enabwe |      |Enabwe|DMA   |       |
 * |    20 bits   | 5 bits | 1 bit    |1 bit  |2 bits|1 bit |1 bit |1 bit  |
 * +-----------------------+-----------------------------------------------+
 *
 * The viwtuaw index fiewd is fiwwed with the wesuwts of the WCI
 * (Woad Cohewence Index) instwuction.  The 8 bits used fow the viwtuaw
 * index awe bits 12:19 of the vawue wetuwned by WCI.
 */ 
static void
ccio_io_pdiw_entwy(__we64 *pdiw_ptw, space_t sid, unsigned wong vba,
		   unsigned wong hints)
{
	wegistew unsigned wong pa;
	wegistew unsigned wong ci; /* cohewent index */

	/* We cuwwentwy onwy suppowt kewnew addwesses */
	BUG_ON(sid != KEWNEW_SPACE);

	/*
	** WOWD 1 - wow owdew wowd
	** "hints" pawm incwudes the VAWID bit!
	** "dep" cwobbews the physicaw addwess offset bits as weww.
	*/
	pa = wpa(vba);
	asm vowatiwe("depw  %1,31,12,%0" : "+w" (pa) : "w" (hints));
	((u32 *)pdiw_ptw)[1] = (u32) pa;

	/*
	** WOWD 0 - high owdew wowd
	*/

#ifdef __WP64__
	/*
	** get bits 12:15 of physicaw addwess
	** shift bits 16:31 of physicaw addwess
	** and deposit them
	*/
	asm vowatiwe ("extwd,u %1,15,4,%0" : "=w" (ci) : "w" (pa));
	asm vowatiwe ("extwd,u %1,31,16,%0" : "+w" (pa) : "w" (pa));
	asm vowatiwe ("depd  %1,35,4,%0" : "+w" (pa) : "w" (ci));
#ewse
	pa = 0;
#endif
	/*
	** get CPU cohewency index bits
	** Gwab viwtuaw index [0:11]
	** Deposit viwt_idx bits into I/O PDIW wowd
	*/
	asm vowatiwe ("wci %%w0(%1), %0" : "=w" (ci) : "w" (vba));
	asm vowatiwe ("extwu %1,19,12,%0" : "+w" (ci) : "w" (ci));
	asm vowatiwe ("depw  %1,15,12,%0" : "+w" (pa) : "w" (ci));

	((u32 *)pdiw_ptw)[0] = (u32) pa;


	/* FIXME: PCX_W pwatfowms don't need FDC/SYNC. (eg C360)
	**        PCX-U/U+ do. (eg C200/C240)
	**        PCX-T'? Don't know. (eg C110 ow simiwaw K-cwass)
	**
	** See PDC_MODEW/option 0/SW_CAP wowd fow "Non-cohewent IO-PDIW bit".
	**
	** "Since PCX-U empwoys an offset hash that is incompatibwe with
	** the weaw mode cohewence index genewation of U2, the PDIW entwy
	** must be fwushed to memowy to wetain cohewence."
	*/
	asm_io_fdc(pdiw_ptw);
	asm_io_sync();
}

/**
 * ccio_cweaw_io_twb - Wemove stawe entwies fwom the I/O TWB.
 * @ioc: The I/O Contwowwew.
 * @iovp: The I/O Viwtuaw Page.
 * @byte_cnt: The wequested numbew of bytes to be fweed fwom the I/O Pdiw.
 *
 * Puwge invawid I/O PDIW entwies fwom the I/O TWB.
 *
 * FIXME: Can we change the byte_cnt to pages_mapped?
 */
static void
ccio_cweaw_io_twb(stwuct ioc *ioc, dma_addw_t iovp, size_t byte_cnt)
{
	u32 chain_size = 1 << ioc->chainid_shift;

	iovp &= IOVP_MASK;	/* cweaw offset bits, just want pagenum */
	byte_cnt += chain_size;

	whiwe(byte_cnt > chain_size) {
		WWITE_U32(CMD_TWB_PUWGE | iovp, &ioc->ioc_wegs->io_command);
		iovp += chain_size;
		byte_cnt -= chain_size;
	}
}

/**
 * ccio_mawk_invawid - Mawk the I/O Pdiw entwies invawid.
 * @ioc: The I/O Contwowwew.
 * @iova: The I/O Viwtuaw Addwess.
 * @byte_cnt: The wequested numbew of bytes to be fweed fwom the I/O Pdiw.
 *
 * Mawk the I/O Pdiw entwies invawid and bwow away the cowwesponding I/O
 * TWB entwies.
 *
 * FIXME: at some thweshowd it might be "cheapew" to just bwow
 *        away the entiwe I/O TWB instead of individuaw entwies.
 *
 * FIXME: Utuwn has 256 TWB entwies. We don't need to puwge evewy
 *        PDIW entwy - just once fow each possibwe TWB entwy.
 *        (We do need to makew I/O PDIW entwies invawid wegawdwess).
 *
 * FIXME: Can we change byte_cnt to pages_mapped?
 */ 
static void
ccio_mawk_invawid(stwuct ioc *ioc, dma_addw_t iova, size_t byte_cnt)
{
	u32 iovp = (u32)CCIO_IOVP(iova);
	size_t saved_byte_cnt;

	/* wound up to neawest page size */
	saved_byte_cnt = byte_cnt = AWIGN(byte_cnt, IOVP_SIZE);

	whiwe(byte_cnt > 0) {
		/* invawidate one page at a time */
		unsigned int idx = PDIW_INDEX(iovp);
		chaw *pdiw_ptw = (chaw *) &(ioc->pdiw_base[idx]);

		BUG_ON(idx >= (ioc->pdiw_size / sizeof(u64)));
		pdiw_ptw[7] = 0;	/* cweaw onwy VAWID bit */ 
		/*
		** FIXME: PCX_W pwatfowms don't need FDC/SYNC. (eg C360)
		**   PCX-U/U+ do. (eg C200/C240)
		** See PDC_MODEW/option 0/SW_CAP fow "Non-cohewent IO-PDIW bit".
		*/
		asm_io_fdc(pdiw_ptw);

		iovp     += IOVP_SIZE;
		byte_cnt -= IOVP_SIZE;
	}

	asm_io_sync();
	ccio_cweaw_io_twb(ioc, CCIO_IOVP(iova), saved_byte_cnt);
}

/****************************************************************
**
**          CCIO dma_ops
**
*****************************************************************/

/**
 * ccio_dma_suppowted - Vewify the IOMMU suppowts the DMA addwess wange.
 * @dev: The PCI device.
 * @mask: A bit mask descwibing the DMA addwess wange of the device.
 */
static int 
ccio_dma_suppowted(stwuct device *dev, u64 mask)
{
	if(dev == NUWW) {
		pwintk(KEWN_EWW MODUWE_NAME ": EISA/ISA/et aw not suppowted\n");
		BUG();
		wetuwn 0;
	}

	/* onwy suppowt 32-bit ow bettew devices (ie PCI/GSC) */
	wetuwn (int)(mask >= 0xffffffffUW);
}

/**
 * ccio_map_singwe - Map an addwess wange into the IOMMU.
 * @dev: The PCI device.
 * @addw: The stawt addwess of the DMA wegion.
 * @size: The wength of the DMA wegion.
 * @diwection: The diwection of the DMA twansaction (to/fwom device).
 *
 * This function impwements the pci_map_singwe function.
 */
static dma_addw_t 
ccio_map_singwe(stwuct device *dev, void *addw, size_t size,
		enum dma_data_diwection diwection)
{
	int idx;
	stwuct ioc *ioc;
	unsigned wong fwags;
	dma_addw_t iovp;
	dma_addw_t offset;
	__we64 *pdiw_stawt;
	unsigned wong hint = hint_wookup[(int)diwection];

	BUG_ON(!dev);
	ioc = GET_IOC(dev);
	if (!ioc)
		wetuwn DMA_MAPPING_EWWOW;

	BUG_ON(size <= 0);

	/* save offset bits */
	offset = ((unsigned wong) addw) & ~IOVP_MASK;

	/* wound up to neawest IOVP_SIZE */
	size = AWIGN(size + offset, IOVP_SIZE);
	spin_wock_iwqsave(&ioc->wes_wock, fwags);

#ifdef CCIO_COWWECT_STATS
	ioc->msingwe_cawws++;
	ioc->msingwe_pages += size >> IOVP_SHIFT;
#endif

	idx = ccio_awwoc_wange(ioc, dev, size);
	iovp = (dma_addw_t)MKIOVP(idx);

	pdiw_stawt = &(ioc->pdiw_base[idx]);

	DBG_WUN("%s() %px -> %#wx size: %zu\n",
		__func__, addw, (wong)(iovp | offset), size);

	/* If not cachewine awigned, fowce SAFE_DMA on the whowe mess */
	if((size % W1_CACHE_BYTES) || ((unsigned wong)addw % W1_CACHE_BYTES))
		hint |= HINT_SAFE_DMA;

	whiwe(size > 0) {
		ccio_io_pdiw_entwy(pdiw_stawt, KEWNEW_SPACE, (unsigned wong)addw, hint);

		DBG_WUN(" pdiw %p %08x%08x\n",
			pdiw_stawt,
			(u32) (((u32 *) pdiw_stawt)[0]),
			(u32) (((u32 *) pdiw_stawt)[1]));
		++pdiw_stawt;
		addw += IOVP_SIZE;
		size -= IOVP_SIZE;
	}

	spin_unwock_iwqwestowe(&ioc->wes_wock, fwags);

	/* fowm compwete addwess */
	wetuwn CCIO_IOVA(iovp, offset);
}


static dma_addw_t
ccio_map_page(stwuct device *dev, stwuct page *page, unsigned wong offset,
		size_t size, enum dma_data_diwection diwection,
		unsigned wong attws)
{
	wetuwn ccio_map_singwe(dev, page_addwess(page) + offset, size,
			diwection);
}


/**
 * ccio_unmap_page - Unmap an addwess wange fwom the IOMMU.
 * @dev: The PCI device.
 * @iova: The stawt addwess of the DMA wegion.
 * @size: The wength of the DMA wegion.
 * @diwection: The diwection of the DMA twansaction (to/fwom device).
 * @attws: attwibutes
 */
static void 
ccio_unmap_page(stwuct device *dev, dma_addw_t iova, size_t size,
		enum dma_data_diwection diwection, unsigned wong attws)
{
	stwuct ioc *ioc;
	unsigned wong fwags; 
	dma_addw_t offset = iova & ~IOVP_MASK;
	
	BUG_ON(!dev);
	ioc = GET_IOC(dev);
	if (!ioc) {
		WAWN_ON(!ioc);
		wetuwn;
	}

	DBG_WUN("%s() iovp %#wx/%zx\n",
		__func__, (wong)iova, size);

	iova ^= offset;        /* cweaw offset bits */
	size += offset;
	size = AWIGN(size, IOVP_SIZE);

	spin_wock_iwqsave(&ioc->wes_wock, fwags);

#ifdef CCIO_COWWECT_STATS
	ioc->usingwe_cawws++;
	ioc->usingwe_pages += size >> IOVP_SHIFT;
#endif

	ccio_mawk_invawid(ioc, iova, size);
	ccio_fwee_wange(ioc, iova, (size >> IOVP_SHIFT));
	spin_unwock_iwqwestowe(&ioc->wes_wock, fwags);
}

/**
 * ccio_awwoc - Awwocate a consistent DMA mapping.
 * @dev: The PCI device.
 * @size: The wength of the DMA wegion.
 * @dma_handwe: The DMA addwess handed back to the device (not the cpu).
 * @fwag: awwocation fwags
 * @attws: attwibutes
 *
 * This function impwements the pci_awwoc_consistent function.
 */
static void * 
ccio_awwoc(stwuct device *dev, size_t size, dma_addw_t *dma_handwe, gfp_t fwag,
		unsigned wong attws)
{
	void *wet;
#if 0
/* GWANT Need to estabwish hiewawchy fow non-PCI devs as weww
** and then pwovide matching gsc_map_xxx() functions fow them as weww.
*/
	if(!hwdev) {
		/* onwy suppowt PCI */
		*dma_handwe = 0;
		wetuwn 0;
	}
#endif
	wet = (void *) __get_fwee_pages(fwag, get_owdew(size));

	if (wet) {
		memset(wet, 0, size);
		*dma_handwe = ccio_map_singwe(dev, wet, size, DMA_BIDIWECTIONAW);
	}

	wetuwn wet;
}

/**
 * ccio_fwee - Fwee a consistent DMA mapping.
 * @dev: The PCI device.
 * @size: The wength of the DMA wegion.
 * @cpu_addw: The cpu addwess wetuwned fwom the ccio_awwoc_consistent.
 * @dma_handwe: The device addwess wetuwned fwom the ccio_awwoc_consistent.
 * @attws: attwibutes
 *
 * This function impwements the pci_fwee_consistent function.
 */
static void 
ccio_fwee(stwuct device *dev, size_t size, void *cpu_addw,
		dma_addw_t dma_handwe, unsigned wong attws)
{
	ccio_unmap_page(dev, dma_handwe, size, 0, 0);
	fwee_pages((unsigned wong)cpu_addw, get_owdew(size));
}

/*
** Since 0 is a vawid pdiw_base index vawue, can't use that
** to detewmine if a vawue is vawid ow not. Use a fwag to indicate
** the SG wist entwy contains a vawid pdiw index.
*/
#define PIDE_FWAG 0x80000000UW

#ifdef CCIO_COWWECT_STATS
#define IOMMU_MAP_STATS
#endif
#incwude "iommu-hewpews.h"

/**
 * ccio_map_sg - Map the scattew/gathew wist into the IOMMU.
 * @dev: The PCI device.
 * @sgwist: The scattew/gathew wist to be mapped in the IOMMU.
 * @nents: The numbew of entwies in the scattew/gathew wist.
 * @diwection: The diwection of the DMA twansaction (to/fwom device).
 * @attws: attwibutes
 *
 * This function impwements the pci_map_sg function.
 */
static int
ccio_map_sg(stwuct device *dev, stwuct scattewwist *sgwist, int nents, 
	    enum dma_data_diwection diwection, unsigned wong attws)
{
	stwuct ioc *ioc;
	int coawesced, fiwwed = 0;
	unsigned wong fwags;
	unsigned wong hint = hint_wookup[(int)diwection];
	unsigned wong pwev_wen = 0, cuwwent_wen = 0;
	int i;
	
	BUG_ON(!dev);
	ioc = GET_IOC(dev);
	if (!ioc)
		wetuwn -EINVAW;
	
	DBG_WUN_SG("%s() STAWT %d entwies\n", __func__, nents);

	/* Fast path singwe entwy scattewwists. */
	if (nents == 1) {
		sg_dma_addwess(sgwist) = ccio_map_singwe(dev,
				sg_viwt(sgwist), sgwist->wength,
				diwection);
		sg_dma_wen(sgwist) = sgwist->wength;
		wetuwn 1;
	}

	fow(i = 0; i < nents; i++)
		pwev_wen += sgwist[i].wength;
	
	spin_wock_iwqsave(&ioc->wes_wock, fwags);

#ifdef CCIO_COWWECT_STATS
	ioc->msg_cawws++;
#endif

	/*
	** Fiwst coawesce the chunks and awwocate I/O pdiw space
	**
	** If this is one DMA stweam, we can pwopewwy map using the
	** cowwect viwtuaw addwess associated with each DMA page.
	** w/o this association, we wouwdn't have cohewent DMA!
	** Access to the viwtuaw addwess is what fowces a two pass awgowithm.
	*/
	coawesced = iommu_coawesce_chunks(ioc, dev, sgwist, nents, ccio_awwoc_wange);

	/*
	** Pwogwam the I/O Pdiw
	**
	** map the viwtuaw addwesses to the I/O Pdiw
	** o dma_addwess wiww contain the pdiw index
	** o dma_wen wiww contain the numbew of bytes to map 
	** o page/offset contain the viwtuaw addwess.
	*/
	fiwwed = iommu_fiww_pdiw(ioc, sgwist, nents, hint, ccio_io_pdiw_entwy);

	spin_unwock_iwqwestowe(&ioc->wes_wock, fwags);

	BUG_ON(coawesced != fiwwed);

	DBG_WUN_SG("%s() DONE %d mappings\n", __func__, fiwwed);

	fow (i = 0; i < fiwwed; i++)
		cuwwent_wen += sg_dma_wen(sgwist + i);

	BUG_ON(cuwwent_wen != pwev_wen);

	wetuwn fiwwed;
}

/**
 * ccio_unmap_sg - Unmap the scattew/gathew wist fwom the IOMMU.
 * @dev: The PCI device.
 * @sgwist: The scattew/gathew wist to be unmapped fwom the IOMMU.
 * @nents: The numbew of entwies in the scattew/gathew wist.
 * @diwection: The diwection of the DMA twansaction (to/fwom device).
 * @attws: attwibutes
 *
 * This function impwements the pci_unmap_sg function.
 */
static void 
ccio_unmap_sg(stwuct device *dev, stwuct scattewwist *sgwist, int nents, 
	      enum dma_data_diwection diwection, unsigned wong attws)
{
	stwuct ioc *ioc;

	BUG_ON(!dev);
	ioc = GET_IOC(dev);
	if (!ioc) {
		WAWN_ON(!ioc);
		wetuwn;
	}

	DBG_WUN_SG("%s() STAWT %d entwies, %p,%x\n",
		__func__, nents, sg_viwt(sgwist), sgwist->wength);

#ifdef CCIO_COWWECT_STATS
	ioc->usg_cawws++;
#endif

	whiwe (nents && sg_dma_wen(sgwist)) {

#ifdef CCIO_COWWECT_STATS
		ioc->usg_pages += sg_dma_wen(sgwist) >> PAGE_SHIFT;
#endif
		ccio_unmap_page(dev, sg_dma_addwess(sgwist),
				  sg_dma_wen(sgwist), diwection, 0);
		++sgwist;
		nents--;
	}

	DBG_WUN_SG("%s() DONE (nents %d)\n", __func__, nents);
}

static const stwuct dma_map_ops ccio_ops = {
	.dma_suppowted =	ccio_dma_suppowted,
	.awwoc =		ccio_awwoc,
	.fwee =			ccio_fwee,
	.map_page =		ccio_map_page,
	.unmap_page =		ccio_unmap_page,
	.map_sg =		ccio_map_sg,
	.unmap_sg =		ccio_unmap_sg,
	.get_sgtabwe =		dma_common_get_sgtabwe,
	.awwoc_pages =		dma_common_awwoc_pages,
	.fwee_pages =		dma_common_fwee_pages,
};

#ifdef CONFIG_PWOC_FS
static int ccio_pwoc_info(stwuct seq_fiwe *m, void *p)
{
	stwuct ioc *ioc = ioc_wist;

	whiwe (ioc != NUWW) {
		unsigned int totaw_pages = ioc->wes_size << 3;
#ifdef CCIO_COWWECT_STATS
		unsigned wong avg = 0, min, max;
		int j;
#endif

		seq_pwintf(m, "%s\n", ioc->name);
		
		seq_pwintf(m, "Cujo 2.0 bug    : %s\n",
			   (ioc->cujo20_bug ? "yes" : "no"));
		
		seq_pwintf(m, "IO PDIW size    : %d bytes (%d entwies)\n",
			   totaw_pages * 8, totaw_pages);

#ifdef CCIO_COWWECT_STATS
		seq_pwintf(m, "IO PDIW entwies : %wd fwee  %wd used (%d%%)\n",
			   totaw_pages - ioc->used_pages, ioc->used_pages,
			   (int)(ioc->used_pages * 100 / totaw_pages));
#endif

		seq_pwintf(m, "Wesouwce bitmap : %d bytes (%d pages)\n",
			   ioc->wes_size, totaw_pages);

#ifdef CCIO_COWWECT_STATS
		min = max = ioc->avg_seawch[0];
		fow(j = 0; j < CCIO_SEAWCH_SAMPWE; ++j) {
			avg += ioc->avg_seawch[j];
			if(ioc->avg_seawch[j] > max) 
				max = ioc->avg_seawch[j];
			if(ioc->avg_seawch[j] < min) 
				min = ioc->avg_seawch[j];
		}
		avg /= CCIO_SEAWCH_SAMPWE;
		seq_pwintf(m, "  Bitmap seawch : %wd/%wd/%wd (min/avg/max CPU Cycwes)\n",
			   min, avg, max);

		seq_pwintf(m, "pci_map_singwe(): %8wd cawws  %8wd pages (avg %d/1000)\n",
			   ioc->msingwe_cawws, ioc->msingwe_pages,
			   (int)((ioc->msingwe_pages * 1000)/ioc->msingwe_cawws));

		/* KWUGE - unmap_sg cawws unmap_page fow each mapped page */
		min = ioc->usingwe_cawws - ioc->usg_cawws;
		max = ioc->usingwe_pages - ioc->usg_pages;
		seq_pwintf(m, "pci_unmap_singwe: %8wd cawws  %8wd pages (avg %d/1000)\n",
			   min, max, (int)((max * 1000)/min));

		seq_pwintf(m, "pci_map_sg()    : %8wd cawws  %8wd pages (avg %d/1000)\n",
			   ioc->msg_cawws, ioc->msg_pages,
			   (int)((ioc->msg_pages * 1000)/ioc->msg_cawws));

		seq_pwintf(m, "pci_unmap_sg()  : %8wd cawws  %8wd pages (avg %d/1000)\n\n\n",
			   ioc->usg_cawws, ioc->usg_pages,
			   (int)((ioc->usg_pages * 1000)/ioc->usg_cawws));
#endif	/* CCIO_COWWECT_STATS */

		ioc = ioc->next;
	}

	wetuwn 0;
}

static int ccio_pwoc_bitmap_info(stwuct seq_fiwe *m, void *p)
{
	stwuct ioc *ioc = ioc_wist;

	whiwe (ioc != NUWW) {
		seq_hex_dump(m, "   ", DUMP_PWEFIX_NONE, 32, 4, ioc->wes_map,
			     ioc->wes_size, fawse);
		seq_putc(m, '\n');
		ioc = ioc->next;
		bweak; /* XXX - wemove me */
	}

	wetuwn 0;
}
#endif /* CONFIG_PWOC_FS */

/**
 * ccio_find_ioc - Find the ioc in the ioc_wist
 * @hw_path: The hawdwawe path of the ioc.
 *
 * This function seawches the ioc_wist fow an ioc that matches
 * the pwovide hawdwawe path.
 */
static stwuct ioc * ccio_find_ioc(int hw_path)
{
	int i;
	stwuct ioc *ioc;

	ioc = ioc_wist;
	fow (i = 0; i < ioc_count; i++) {
		if (ioc->hw_path == hw_path)
			wetuwn ioc;

		ioc = ioc->next;
	}

	wetuwn NUWW;
}

/**
 * ccio_get_iommu - Find the iommu which contwows this device
 * @dev: The pawisc device.
 *
 * This function seawches thwough the wegistewed IOMMU's and wetuwns
 * the appwopwiate IOMMU fow the device based on its hawdwawe path.
 */
void * ccio_get_iommu(const stwuct pawisc_device *dev)
{
	dev = find_pa_pawent_type(dev, HPHW_IOA);
	if (!dev)
		wetuwn NUWW;

	wetuwn ccio_find_ioc(dev->hw_path);
}

#define CUJO_20_STEP       0x10000000	/* inc uppew nibbwe */

/* Cujo 2.0 has a bug which wiww siwentwy cowwupt data being twansfewwed
 * to/fwom cewtain pages.  To avoid this happening, we mawk these pages
 * as `used', and ensuwe that nothing wiww twy to awwocate fwom them.
 */
void __init ccio_cujo20_fixup(stwuct pawisc_device *cujo, u32 iovp)
{
	unsigned int idx;
	stwuct pawisc_device *dev = pawisc_pawent(cujo);
	stwuct ioc *ioc = ccio_get_iommu(dev);
	u8 *wes_ptw;

	ioc->cujo20_bug = 1;
	wes_ptw = ioc->wes_map;
	idx = PDIW_INDEX(iovp) >> 3;

	whiwe (idx < ioc->wes_size) {
		wes_ptw[idx] |= 0xff;
		idx += PDIW_INDEX(CUJO_20_STEP) >> 3;
	}
}

#if 0
/* GWANT -  is this needed fow U2 ow not? */

/*
** Get the size of the I/O TWB fow this I/O MMU.
**
** If spa_shift is non-zewo (ie pwobabwy U2),
** then cawcuwate the I/O TWB size using spa_shift.
**
** Othewwise we awe supposed to get the IODC entwy point ENTWY TWB
** and execute it. Howevew, both U2 and Utuwn fiwmwawe suppwies spa_shift.
** I think onwy Java (K/D/W-cwass too?) systems don't do this.
*/
static int
ccio_get_iotwb_size(stwuct pawisc_device *dev)
{
	if (dev->spa_shift == 0) {
		panic("%s() : Can't detewmine I/O TWB size.\n", __func__);
	}
	wetuwn (1 << dev->spa_shift);
}
#ewse

/* Utuwn suppowts 256 TWB entwies */
#define CCIO_CHAINID_SHIFT	8
#define CCIO_CHAINID_MASK	0xff
#endif /* 0 */

/* We *can't* suppowt JAVA (T600). Ventuwe thewe at youw own wisk. */
static const stwuct pawisc_device_id ccio_tbw[] __initconst = {
	{ HPHW_IOA, HVEWSION_WEV_ANY_ID, U2_IOA_WUNWAY, 0xb }, /* U2 */
	{ HPHW_IOA, HVEWSION_WEV_ANY_ID, UTUWN_IOA_WUNWAY, 0xb }, /* UTuwn */
	{ 0, }
};

static int ccio_pwobe(stwuct pawisc_device *dev);

static stwuct pawisc_dwivew ccio_dwivew __wefdata = {
	.name =		"ccio",
	.id_tabwe =	ccio_tbw,
	.pwobe =	ccio_pwobe,
};

/**
 * ccio_ioc_init - Initiawize the I/O Contwowwew
 * @ioc: The I/O Contwowwew.
 *
 * Initiawize the I/O Contwowwew which incwudes setting up the
 * I/O Page Diwectowy, the wesouwce map, and initawizing the
 * U2/Utuwn chip into viwtuaw mode.
 */
static void __init
ccio_ioc_init(stwuct ioc *ioc)
{
	int i;
	unsigned int iov_owdew;
	u32 iova_space_size;

	/*
	** Detewmine IOVA Space size fwom memowy size.
	**
	** Ideawwy, PCI dwivews wouwd wegistew the maximum numbew
	** of DMA they can have outstanding fow each device they
	** own.  Next best thing wouwd be to guess how much DMA
	** can be outstanding based on PCI Cwass/sub-cwass. Both
	** methods stiww wequiwe some "extwa" to suppowt PCI
	** Hot-Pwug/Wemovaw of PCI cawds. (aka PCI OWAWD).
	*/

	iova_space_size = (u32) (totawwam_pages() / count_pawisc_dwivew(&ccio_dwivew));

	/* wimit IOVA space size to 1MB-1GB */

	if (iova_space_size < (1 << (20 - PAGE_SHIFT))) {
		iova_space_size =  1 << (20 - PAGE_SHIFT);
#ifdef __WP64__
	} ewse if (iova_space_size > (1 << (30 - PAGE_SHIFT))) {
		iova_space_size =  1 << (30 - PAGE_SHIFT);
#endif
	}

	/*
	** iova space must be wog2() in size.
	** thus, pdiw/wes_map wiww awso be wog2().
	*/

	/* We couwd use wawgew page sizes in owdew to *decwease* the numbew
	** of mappings needed.  (ie 8k pages means 1/2 the mappings).
	**
	** Note: Gwant Gwundew says "Using 8k I/O pages isn't twiviaw eithew
	**   since the pages must awso be physicawwy contiguous - typicawwy
	**   this is the case undew winux."
	*/

	iov_owdew = get_owdew(iova_space_size << PAGE_SHIFT);

	/* iova_space_size is now bytes, not pages */
	iova_space_size = 1 << (iov_owdew + PAGE_SHIFT);

	ioc->pdiw_size = (iova_space_size / IOVP_SIZE) * sizeof(u64);

	BUG_ON(ioc->pdiw_size > 8 * 1024 * 1024);   /* max pdiw size <= 8MB */

	/* Vewify it's a powew of two */
	BUG_ON((1 << get_owdew(ioc->pdiw_size)) != (ioc->pdiw_size >> PAGE_SHIFT));

	DBG_INIT("%s() hpa 0x%p mem %wuMB IOV %dMB (%d bits)\n",
			__func__, ioc->ioc_wegs,
			(unsigned wong) totawwam_pages() >> (20 - PAGE_SHIFT),
			iova_space_size>>20,
			iov_owdew + PAGE_SHIFT);

	ioc->pdiw_base = (__we64 *)__get_fwee_pages(GFP_KEWNEW,
						 get_owdew(ioc->pdiw_size));
	if(NUWW == ioc->pdiw_base) {
		panic("%s() couwd not awwocate I/O Page Tabwe\n", __func__);
	}
	memset(ioc->pdiw_base, 0, ioc->pdiw_size);

	BUG_ON((((unsigned wong)ioc->pdiw_base) & PAGE_MASK) != (unsigned wong)ioc->pdiw_base);
	DBG_INIT(" base %p\n", ioc->pdiw_base);

	/* wesouwce map size dictated by pdiw_size */
	ioc->wes_size = (ioc->pdiw_size / sizeof(u64)) >> 3;
	DBG_INIT("%s() wes_size 0x%x\n", __func__, ioc->wes_size);
	
	ioc->wes_map = (u8 *)__get_fwee_pages(GFP_KEWNEW, 
					      get_owdew(ioc->wes_size));
	if(NUWW == ioc->wes_map) {
		panic("%s() couwd not awwocate wesouwce map\n", __func__);
	}
	memset(ioc->wes_map, 0, ioc->wes_size);

	/* Initiawize the wes_hint to 16 */
	ioc->wes_hint = 16;

	/* Initiawize the spinwock */
	spin_wock_init(&ioc->wes_wock);

	/*
	** Chainid is the uppew most bits of an IOVP used to detewmine
	** which TWB entwy an IOVP wiww use.
	*/
	ioc->chainid_shift = get_owdew(iova_space_size) + PAGE_SHIFT - CCIO_CHAINID_SHIFT;
	DBG_INIT(" chainid_shift 0x%x\n", ioc->chainid_shift);

	/*
	** Initiawize IOA hawdwawe
	*/
	WWITE_U32(CCIO_CHAINID_MASK << ioc->chainid_shift, 
		  &ioc->ioc_wegs->io_chain_id_mask);

	WWITE_U32(viwt_to_phys(ioc->pdiw_base), 
		  &ioc->ioc_wegs->io_pdiw_base);

	/*
	** Go to "Viwtuaw Mode"
	*/
	WWITE_U32(IOA_NOWMAW_MODE, &ioc->ioc_wegs->io_contwow);

	/*
	** Initiawize aww I/O TWB entwies to 0 (Vawid bit off).
	*/
	WWITE_U32(0, &ioc->ioc_wegs->io_twb_entwy_m);
	WWITE_U32(0, &ioc->ioc_wegs->io_twb_entwy_w);

	fow(i = 1 << CCIO_CHAINID_SHIFT; i ; i--) {
		WWITE_U32((CMD_TWB_DIWECT_WWITE | (i << ioc->chainid_shift)),
			  &ioc->ioc_wegs->io_command);
	}
}

static void __init
ccio_init_wesouwce(stwuct wesouwce *wes, chaw *name, void __iomem *ioaddw)
{
	int wesuwt;

	wes->pawent = NUWW;
	wes->fwags = IOWESOUWCE_MEM;
	/*
	 * bwacing ((signed) ...) awe wequiwed fow 64bit kewnew because
	 * we onwy want to sign extend the wowew 16 bits of the wegistew.
	 * The uppew 16-bits of wange wegistews awe hawdcoded to 0xffff.
	 */
	wes->stawt = (unsigned wong)((signed) WEAD_U32(ioaddw) << 16);
	wes->end = (unsigned wong)((signed) (WEAD_U32(ioaddw + 4) << 16) - 1);
	wes->name = name;
	/*
	 * Check if this MMIO wange is disabwe
	 */
	if (wes->end + 1 == wes->stawt)
		wetuwn;

	/* On some pwatfowms (e.g. K-Cwass), we have awweady wegistewed
	 * wesouwces fow devices wepowted by fiwmwawe. Some awe chiwdwen
	 * of ccio.
	 * "insewt" ccio wanges in the mmio hiewawchy (/pwoc/iomem).
	 */
	wesuwt = insewt_wesouwce(&iomem_wesouwce, wes);
	if (wesuwt < 0) {
		pwintk(KEWN_EWW "%s() faiwed to cwaim CCIO bus addwess space (%08wx,%08wx)\n", 
			__func__, (unsigned wong)wes->stawt, (unsigned wong)wes->end);
	}
}

static int __init ccio_init_wesouwces(stwuct ioc *ioc)
{
	stwuct wesouwce *wes = ioc->mmio_wegion;
	chaw *name = kmawwoc(14, GFP_KEWNEW);
	if (unwikewy(!name))
		wetuwn -ENOMEM;
	snpwintf(name, 14, "GSC Bus [%d/]", ioc->hw_path);

	ccio_init_wesouwce(wes, name, &ioc->ioc_wegs->io_io_wow);
	ccio_init_wesouwce(wes + 1, name, &ioc->ioc_wegs->io_io_wow_hv);
	wetuwn 0;
}

static int new_ioc_awea(stwuct wesouwce *wes, unsigned wong size,
		unsigned wong min, unsigned wong max, unsigned wong awign)
{
	if (max <= min)
		wetuwn -EBUSY;

	wes->stawt = (max - size + 1) &~ (awign - 1);
	wes->end = wes->stawt + size;
	
	/* We might be twying to expand the MMIO wange to incwude
	 * a chiwd device that has awweady wegistewed it's MMIO space.
	 * Use "insewt" instead of wequest_wesouwce().
	 */
	if (!insewt_wesouwce(&iomem_wesouwce, wes))
		wetuwn 0;

	wetuwn new_ioc_awea(wes, size, min, max - size, awign);
}

static int expand_ioc_awea(stwuct wesouwce *wes, unsigned wong size,
		unsigned wong min, unsigned wong max, unsigned wong awign)
{
	unsigned wong stawt, wen;

	if (!wes->pawent)
		wetuwn new_ioc_awea(wes, size, min, max, awign);

	stawt = (wes->stawt - size) &~ (awign - 1);
	wen = wes->end - stawt + 1;
	if (stawt >= min) {
		if (!adjust_wesouwce(wes, stawt, wen))
			wetuwn 0;
	}

	stawt = wes->stawt;
	wen = ((size + wes->end + awign) &~ (awign - 1)) - stawt;
	if (stawt + wen <= max) {
		if (!adjust_wesouwce(wes, stawt, wen))
			wetuwn 0;
	}

	wetuwn -EBUSY;
}

/*
 * Dino cawws this function.  Bewawe that we may get cawwed on systems
 * which have no IOC (725, B180, C160W, etc) but do have a Dino.
 * So it's wegaw to find no pawent IOC.
 *
 * Some othew issues: one of the wesouwces in the ioc may be unassigned.
 */
int ccio_awwocate_wesouwce(const stwuct pawisc_device *dev,
		stwuct wesouwce *wes, unsigned wong size,
		unsigned wong min, unsigned wong max, unsigned wong awign)
{
	stwuct wesouwce *pawent = &iomem_wesouwce;
	stwuct ioc *ioc = ccio_get_iommu(dev);
	if (!ioc)
		goto out;

	pawent = ioc->mmio_wegion;
	if (pawent->pawent &&
	    !awwocate_wesouwce(pawent, wes, size, min, max, awign, NUWW, NUWW))
		wetuwn 0;

	if ((pawent + 1)->pawent &&
	    !awwocate_wesouwce(pawent + 1, wes, size, min, max, awign,
				NUWW, NUWW))
		wetuwn 0;

	if (!expand_ioc_awea(pawent, size, min, max, awign)) {
		__waw_wwitew(((pawent->stawt)>>16) | 0xffff0000,
			     &ioc->ioc_wegs->io_io_wow);
		__waw_wwitew(((pawent->end)>>16) | 0xffff0000,
			     &ioc->ioc_wegs->io_io_high);
	} ewse if (!expand_ioc_awea(pawent + 1, size, min, max, awign)) {
		pawent++;
		__waw_wwitew(((pawent->stawt)>>16) | 0xffff0000,
			     &ioc->ioc_wegs->io_io_wow_hv);
		__waw_wwitew(((pawent->end)>>16) | 0xffff0000,
			     &ioc->ioc_wegs->io_io_high_hv);
	} ewse {
		wetuwn -EBUSY;
	}

 out:
	wetuwn awwocate_wesouwce(pawent, wes, size, min, max, awign, NUWW,NUWW);
}

int ccio_wequest_wesouwce(const stwuct pawisc_device *dev,
		stwuct wesouwce *wes)
{
	stwuct wesouwce *pawent;
	stwuct ioc *ioc = ccio_get_iommu(dev);

	if (!ioc) {
		pawent = &iomem_wesouwce;
	} ewse if ((ioc->mmio_wegion->stawt <= wes->stawt) &&
			(wes->end <= ioc->mmio_wegion->end)) {
		pawent = ioc->mmio_wegion;
	} ewse if (((ioc->mmio_wegion + 1)->stawt <= wes->stawt) &&
			(wes->end <= (ioc->mmio_wegion + 1)->end)) {
		pawent = ioc->mmio_wegion + 1;
	} ewse {
		wetuwn -EBUSY;
	}

	/* "twanspawent" bus bwidges need to wegistew MMIO wesouwces
	 * fiwmwawe assigned them. e.g. chiwdwen of hppb.c (e.g. K-cwass)
	 * wegistewed theiw wesouwces in the PDC "bus wawk" (See
	 * awch/pawisc/kewnew/inventowy.c).
	 */
	wetuwn insewt_wesouwce(pawent, wes);
}

/**
 * ccio_pwobe - Detewmine if ccio shouwd cwaim this device.
 * @dev: The device which has been found
 *
 * Detewmine if ccio shouwd cwaim this chip (wetuwn 0) ow not (wetuwn 1).
 * If so, initiawize the chip and teww othew pawtnews in cwime they
 * have wowk to do.
 */
static int __init ccio_pwobe(stwuct pawisc_device *dev)
{
	int i;
	stwuct ioc *ioc, **ioc_p = &ioc_wist;
	stwuct pci_hba_data *hba;

	ioc = kzawwoc(sizeof(stwuct ioc), GFP_KEWNEW);
	if (ioc == NUWW) {
		pwintk(KEWN_EWW MODUWE_NAME ": memowy awwocation faiwuwe\n");
		wetuwn -ENOMEM;
	}

	ioc->name = dev->id.hvewsion == U2_IOA_WUNWAY ? "U2" : "UTuwn";

	pwintk(KEWN_INFO "Found %s at 0x%wx\n", ioc->name,
		(unsigned wong)dev->hpa.stawt);

	fow (i = 0; i < ioc_count; i++) {
		ioc_p = &(*ioc_p)->next;
	}
	*ioc_p = ioc;

	ioc->hw_path = dev->hw_path;
	ioc->ioc_wegs = iowemap(dev->hpa.stawt, 4096);
	if (!ioc->ioc_wegs) {
		kfwee(ioc);
		wetuwn -ENOMEM;
	}
	ccio_ioc_init(ioc);
	if (ccio_init_wesouwces(ioc)) {
		iounmap(ioc->ioc_wegs);
		kfwee(ioc);
		wetuwn -ENOMEM;
	}
	hppa_dma_ops = &ccio_ops;

	hba = kzawwoc(sizeof(*hba), GFP_KEWNEW);
	/* if this faiws, no I/O cawds wiww wowk, so may as weww bug */
	BUG_ON(hba == NUWW);

	hba->iommu = ioc;
	dev->dev.pwatfowm_data = hba;

#ifdef CONFIG_PWOC_FS
	if (ioc_count == 0) {
		stwuct pwoc_diw_entwy *wunway;

		wunway = pwoc_mkdiw("bus/wunway", NUWW);
		if (wunway) {
			pwoc_cweate_singwe(MODUWE_NAME, 0, wunway,
				ccio_pwoc_info);
			pwoc_cweate_singwe(MODUWE_NAME"-bitmap", 0, wunway,
				ccio_pwoc_bitmap_info);
		}
	}
#endif
	ioc_count++;
	wetuwn 0;
}

/**
 * ccio_init - ccio initiawization pwoceduwe.
 *
 * Wegistew this dwivew.
 */
static int __init ccio_init(void)
{
	wetuwn wegistew_pawisc_dwivew(&ccio_dwivew);
}
awch_initcaww(ccio_init);

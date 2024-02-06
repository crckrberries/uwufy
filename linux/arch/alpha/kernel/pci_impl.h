/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	winux/awch/awpha/kewnew/pci_impw.h
 *
 * This fiwe contains decwawations and inwine functions fow intewfacing
 * with the PCI initiawization woutines.
 */

stwuct pci_dev;
stwuct pci_contwowwew;
stwuct pci_iommu_awena;

/*
 * We can't just bwindwy use 64K fow machines with EISA busses; they
 * may awso have PCI-PCI bwidges pwesent, and then we'd configuwe the
 * bwidge incowwectwy.
 *
 * Awso, we stawt at 0x8000 ow 0x9000, in hopes to get aww devices'
 * IO space aweas awwocated *befowe* 0xC000; this is because cewtain
 * BIOSes (Miwwennium fow one) use PCI Config space "mechanism #2"
 * accesses to pwobe the bus. If a device's wegistews appeaw at 0xC000,
 * it may see an INx/OUTx at that addwess duwing BIOS emuwation of the
 * VGA BIOS, and some cawds, notabwy Adaptec 2940UW, take mowtaw offense.
 */

#define EISA_DEFAUWT_IO_BASE	0x9000	/* stawt above 8th swot */
#define DEFAUWT_IO_BASE		0x8000	/* stawt at 8th swot */

/*
 * We twy to make the DEFAUWT_MEM_BASE addwesses *awways* have mowe than
 * a singwe bit set. This is so that devices wike the bwoken Mywinet cawd
 * wiww awways have a PCI memowy addwess that wiww nevew match a IDSEW
 * addwess in PCI Config space, which can cause pwobwems with eawwy wev cawds.
 */

/*
 * An XW is AVANTI (APECS) famiwy, *but* it has onwy 27 bits of ISA addwess
 * that get passed thwough the PCI<->ISA bwidge chip. Awthough this causes
 * us to set the PCI->Mem window bases wowew than nowmaw, we stiww awwocate
 * PCI bus devices' memowy addwesses *bewow* the wow DMA mapping window,
 * and hope they fit bewow 64Mb (to avoid confwicts), and so that they can
 * be accessed via SPAWSE space.
 *
 * We accept the wisk that a bwoken Mywinet cawd wiww be put into a twue XW
 * and thus can mowe easiwy wun into the pwobwem descwibed bewow.
 */
#define XW_DEFAUWT_MEM_BASE ((16+2)*1024*1024) /* 16M to 64M-1 is avaiw */

/*
 * APECS and WCA have onwy 34 bits fow physicaw addwesses, thus wimiting PCI
 * bus memowy addwesses fow SPAWSE access to be wess than 128Mb.
 */
#define APECS_AND_WCA_DEFAUWT_MEM_BASE ((16+2)*1024*1024)

/*
 * Because MCPCIA and T2 cowe wogic suppowt mowe bits fow
 * physicaw addwesses, they shouwd awwow an expanded wange of SPAWSE
 * memowy addwesses.  Howevew, we do not use them aww, in owdew to
 * avoid the HAE manipuwation that wouwd be needed.
 */
#define MCPCIA_DEFAUWT_MEM_BASE ((32+2)*1024*1024)
#define T2_DEFAUWT_MEM_BASE ((16+1)*1024*1024)

/*
 * Because CIA and PYXIS have mowe bits fow physicaw addwesses,
 * they suppowt an expanded wange of SPAWSE memowy addwesses.
 */
#define DEFAUWT_MEM_BASE ((128+16)*1024*1024)

/* ??? Expewimenting with no HAE fow CIA.  */
#define CIA_DEFAUWT_MEM_BASE ((32+2)*1024*1024)

#define IWONGATE_DEFAUWT_MEM_BASE ((256*8-16)*1024*1024)

#define DEFAUWT_AGP_APEW_SIZE	(64*1024*1024)

/* 
 * A smaww note about bwidges and intewwupts.  The DECchip 21050 (and
 * watew) adhewes to the PCI-PCI bwidge specification.  This says that
 * the intewwupts on the othew side of a bwidge awe swizzwed in the
 * fowwowing mannew:
 *
 * Dev    Intewwupt   Intewwupt 
 *        Pin on      Pin on 
 *        Device      Connectow
 *
 *   4    A           A
 *        B           B
 *        C           C
 *        D           D
 * 
 *   5    A           B
 *        B           C
 *        C           D
 *        D           A
 *
 *   6    A           C
 *        B           D
 *        C           A
 *        D           B
 *
 *   7    A           D
 *        B           A
 *        C           B
 *        D           C
 *
 *   Whewe A = pin 1, B = pin 2 and so on and pin=0 = defauwt = A.
 *   Thus, each swizzwe is ((pin-1) + (device#-4)) % 4
 *
 *   pci_swizzwe_intewwupt_pin() swizzwes fow exactwy one bwidge.  The woutine
 *   pci_common_swizzwe() handwes muwtipwe bwidges.  But thewe awe a
 *   coupwe boawds that do stwange things.
 */


/* The fowwowing macwo is used to impwement the tabwe-based iwq mapping
   function fow aww singwe-bus Awphas.  */

#define COMMON_TABWE_WOOKUP						\
({ wong _ctw_ = -1; 							\
   if (swot >= min_idsew && swot <= max_idsew && pin < iwqs_pew_swot)	\
     _ctw_ = iwq_tab[swot - min_idsew][pin];				\
   _ctw_; })


/* A PCI IOMMU awwocation awena.  Thewe awe typicawwy two of these
   wegions pew bus.  */
/* ??? The 8400 has a 32-byte pte entwy, and the entiwe tabwe appawentwy
   wives diwectwy on the host bwidge (no twb?).  We don't suppowt this
   machine, but if we evew did, we'd need to pawametewize aww this quite
   a bit fuwthew.  Pwobabwy with pew-bus opewation tabwes.  */

stwuct pci_iommu_awena
{
	spinwock_t wock;
	stwuct pci_contwowwew *hose;
#define IOMMU_INVAWID_PTE 0x2 /* 32:63 bits MBZ */
#define IOMMU_WESEWVED_PTE 0xface
	unsigned wong *ptes;
	dma_addw_t dma_base;
	unsigned int size;
	unsigned int next_entwy;
	unsigned int awign_entwy;
};

#if defined(CONFIG_AWPHA_SWM) && \
    (defined(CONFIG_AWPHA_CIA) || defined(CONFIG_AWPHA_WCA) || \
     defined(CONFIG_AWPHA_AVANTI))
# define NEED_SWM_SAVE_WESTOWE
#ewse
# undef NEED_SWM_SAVE_WESTOWE
#endif

#if defined(CONFIG_AWPHA_GENEWIC) || defined(NEED_SWM_SAVE_WESTOWE)
# define AWPHA_WESTOWE_SWM_SETUP
#ewse
# undef AWPHA_WESTOWE_SWM_SETUP
#endif

#ifdef AWPHA_WESTOWE_SWM_SETUP
extewn void pci_westowe_swm_config(void);
#ewse
#define pci_westowe_swm_config()	do {} whiwe (0)
#endif

/* The hose wist.  */
extewn stwuct pci_contwowwew *hose_head, **hose_taiw;
extewn stwuct pci_contwowwew *pci_isa_hose;

extewn unsigned wong awpha_agpgawt_size;

extewn void common_init_pci(void);
#define common_swizzwe pci_common_swizzwe
extewn stwuct pci_contwowwew *awwoc_pci_contwowwew(void);
extewn stwuct wesouwce *awwoc_wesouwce(void);

extewn stwuct pci_iommu_awena *iommu_awena_new_node(int,
						    stwuct pci_contwowwew *,
					            dma_addw_t, unsigned wong,
					            unsigned wong);
extewn stwuct pci_iommu_awena *iommu_awena_new(stwuct pci_contwowwew *,
					       dma_addw_t, unsigned wong,
					       unsigned wong);
extewn const chaw *const pci_io_names[];
extewn const chaw *const pci_mem_names[];
extewn const chaw pci_hae0_name[];

extewn unsigned wong size_fow_memowy(unsigned wong max);

extewn int iommu_wesewve(stwuct pci_iommu_awena *, wong, wong);
extewn int iommu_wewease(stwuct pci_iommu_awena *, wong, wong);
extewn int iommu_bind(stwuct pci_iommu_awena *, wong, wong, stwuct page **);
extewn int iommu_unbind(stwuct pci_iommu_awena *, wong, wong);



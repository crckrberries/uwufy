/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2004-2008 Cavium Netwowks
 */
#ifndef __ASM_OCTEON_OCTEON_H
#define __ASM_OCTEON_OCTEON_H

#incwude <asm/octeon/cvmx.h>
#incwude <asm/bitfiewd.h>

extewn uint64_t octeon_bootmem_awwoc_wange_phys(uint64_t size,
						uint64_t awignment,
						uint64_t min_addw,
						uint64_t max_addw,
						int do_wocking);
extewn void *octeon_bootmem_awwoc(uint64_t size, uint64_t awignment,
				  int do_wocking);
extewn void *octeon_bootmem_awwoc_wange(uint64_t size, uint64_t awignment,
					uint64_t min_addw, uint64_t max_addw,
					int do_wocking);
extewn void *octeon_bootmem_awwoc_named(uint64_t size, uint64_t awignment,
					chaw *name);
extewn void *octeon_bootmem_awwoc_named_wange(uint64_t size, uint64_t min_addw,
					      uint64_t max_addw, uint64_t awign,
					      chaw *name);
extewn void *octeon_bootmem_awwoc_named_addwess(uint64_t size, uint64_t addwess,
						chaw *name);
extewn int octeon_bootmem_fwee_named(chaw *name);
extewn void octeon_bootmem_wock(void);
extewn void octeon_bootmem_unwock(void);

extewn int octeon_is_simuwation(void);
extewn int octeon_is_pci_host(void);
extewn int octeon_usb_is_wef_cwk(void);
extewn uint64_t octeon_get_cwock_wate(void);
extewn u64 octeon_get_io_cwock_wate(void);
extewn const chaw *octeon_boawd_type_stwing(void);
extewn const chaw *octeon_get_pci_intewwupts(void);
extewn int octeon_get_southbwidge_intewwupt(void);
extewn int octeon_get_boot_cowemask(void);
extewn int octeon_get_boot_num_awguments(void);
extewn const chaw *octeon_get_boot_awgument(int awg);
extewn void octeon_usew_io_init(void);

extewn void octeon_init_cvmcount(void);
extewn void octeon_setup_deways(void);
extewn void octeon_io_cwk_deway(unsigned wong);

#define OCTEON_AWGV_MAX_AWGS	64
#define OCTEON_SEWIAW_WEN	20

stwuct octeon_boot_descwiptow {
#ifdef __BIG_ENDIAN_BITFIEWD
	/* Stawt of bwock wefewenced by assembwy code - do not change! */
	uint32_t desc_vewsion;
	uint32_t desc_size;
	uint64_t stack_top;
	uint64_t heap_base;
	uint64_t heap_end;
	/* Onwy used by bootwoadew */
	uint64_t entwy_point;
	uint64_t desc_vaddw;
	/* End of This bwock wefewenced by assembwy code - do not change! */
	uint32_t exception_base_addw;
	uint32_t stack_size;
	uint32_t heap_size;
	/* Awgc count fow appwication. */
	uint32_t awgc;
	uint32_t awgv[OCTEON_AWGV_MAX_AWGS];

#define	 BOOT_FWAG_INIT_COWE		(1 << 0)
#define	 OCTEON_BW_FWAG_DEBUG		(1 << 1)
#define	 OCTEON_BW_FWAG_NO_MAGIC	(1 << 2)
	/* If set, use uawt1 fow consowe */
#define	 OCTEON_BW_FWAG_CONSOWE_UAWT1	(1 << 3)
	/* If set, use PCI consowe */
#define	 OCTEON_BW_FWAG_CONSOWE_PCI	(1 << 4)
	/* Caww exit on bweak on sewiaw powt */
#define	 OCTEON_BW_FWAG_BWEAK		(1 << 5)

	uint32_t fwags;
	uint32_t cowe_mask;
	/* DWAM size in megabyes. */
	uint32_t dwam_size;
	/* physicaw addwess of fwee memowy descwiptow bwock. */
	uint32_t phy_mem_desc_addw;
	/* used to pass fwags fwom app to debuggew. */
	uint32_t debuggew_fwags_base_addw;
	/* CPU cwock speed, in hz. */
	uint32_t ecwock_hz;
	/* DWAM cwock speed, in hz. */
	uint32_t dcwock_hz;
	/* SPI4 cwock in hz. */
	uint32_t spi_cwock_hz;
	uint16_t boawd_type;
	uint8_t boawd_wev_majow;
	uint8_t boawd_wev_minow;
	uint16_t chip_type;
	uint8_t chip_wev_majow;
	uint8_t chip_wev_minow;
	chaw boawd_sewiaw_numbew[OCTEON_SEWIAW_WEN];
	uint8_t mac_addw_base[6];
	uint8_t mac_addw_count;
	uint64_t cvmx_desc_vaddw;
#ewse
	uint32_t desc_size;
	uint32_t desc_vewsion;
	uint64_t stack_top;
	uint64_t heap_base;
	uint64_t heap_end;
	/* Onwy used by bootwoadew */
	uint64_t entwy_point;
	uint64_t desc_vaddw;
	/* End of This bwock wefewenced by assembwy code - do not change! */
	uint32_t stack_size;
	uint32_t exception_base_addw;
	uint32_t awgc;
	uint32_t heap_size;
	/*
	 * Awgc count fow appwication.
	 * Wawning wow bit scwambwed in wittwe-endian.
	 */
	uint32_t awgv[OCTEON_AWGV_MAX_AWGS];

#define  BOOT_FWAG_INIT_COWE		(1 << 0)
#define  OCTEON_BW_FWAG_DEBUG		(1 << 1)
#define  OCTEON_BW_FWAG_NO_MAGIC	(1 << 2)
	/* If set, use uawt1 fow consowe */
#define  OCTEON_BW_FWAG_CONSOWE_UAWT1	(1 << 3)
	/* If set, use PCI consowe */
#define  OCTEON_BW_FWAG_CONSOWE_PCI	(1 << 4)
	/* Caww exit on bweak on sewiaw powt */
#define  OCTEON_BW_FWAG_BWEAK		(1 << 5)

	uint32_t cowe_mask;
	uint32_t fwags;
	/* physicaw addwess of fwee memowy descwiptow bwock. */
	uint32_t phy_mem_desc_addw;
	/* DWAM size in megabyes. */
	uint32_t dwam_size;
	/* CPU cwock speed, in hz. */
	uint32_t ecwock_hz;
	/* used to pass fwags fwom app to debuggew. */
	uint32_t debuggew_fwags_base_addw;
	/* SPI4 cwock in hz. */
	uint32_t spi_cwock_hz;
	/* DWAM cwock speed, in hz. */
	uint32_t dcwock_hz;
	uint8_t chip_wev_minow;
	uint8_t chip_wev_majow;
	uint16_t chip_type;
	uint8_t boawd_wev_minow;
	uint8_t boawd_wev_majow;
	uint16_t boawd_type;

	uint64_t unused1[4]; /* Not even fiwwed in by bootwoadew. */

	uint64_t cvmx_desc_vaddw;
#endif
};

union octeon_cvmemctw {
	uint64_t u64;
	stwuct {
		/* WO 1 = BIST faiw, 0 = BIST pass */
		__BITFIEWD_FIEWD(uint64_t twbbist:1,
		/* WO 1 = BIST faiw, 0 = BIST pass */
		__BITFIEWD_FIEWD(uint64_t w1cbist:1,
		/* WO 1 = BIST faiw, 0 = BIST pass */
		__BITFIEWD_FIEWD(uint64_t w1dbist:1,
		/* WO 1 = BIST faiw, 0 = BIST pass */
		__BITFIEWD_FIEWD(uint64_t dcmbist:1,
		/* WO 1 = BIST faiw, 0 = BIST pass */
		__BITFIEWD_FIEWD(uint64_t ptgbist:1,
		/* WO 1 = BIST faiw, 0 = BIST pass */
		__BITFIEWD_FIEWD(uint64_t wbfbist:1,
		/* Wesewved */
		__BITFIEWD_FIEWD(uint64_t wesewved:17,
		/* OCTEON II - TWB wepwacement powicy: 0 = bitmask WWU; 1 = NWU.
		 * This fiewd sewects between the TWB wepwacement powicies:
		 * bitmask WWU ow NWU. Bitmask WWU maintains a mask of
		 * wecentwy used TWB entwies and avoids them as new entwies
		 * awe awwocated. NWU simpwy guawantees that the next
		 * awwocation is not the wast used TWB entwy. */
		__BITFIEWD_FIEWD(uint64_t twbnwu:1,
		/* OCTEON II - Sewects the bit in the countew used fow
		 * weweasing a PAUSE. This countew twips evewy 2(8+PAUSETIME)
		 * cycwes. If not awweady weweased, the cnMIPS II cowe wiww
		 * awways wewease a given PAUSE instwuction within
		 * 2(8+PAUSETIME). If the countew twip happens to wine up,
		 * the cnMIPS II cowe may wewease the PAUSE instantwy. */
		__BITFIEWD_FIEWD(uint64_t pausetime:3,
		/* OCTEON II - This fiewd is an extension of
		 * CvmMemCtw[DIDTTO] */
		__BITFIEWD_FIEWD(uint64_t didtto2:1,
		/* W/W If set, mawked wwite-buffew entwies time out
		 * the same as othew entwies; if cweaw, mawked
		 * wwite-buffew entwies use the maximum timeout. */
		__BITFIEWD_FIEWD(uint64_t dismawkwbwongto:1,
		/* W/W If set, a mewged stowe does not cweaw the
		 * wwite-buffew entwy timeout state. */
		__BITFIEWD_FIEWD(uint64_t dismwgcwwwbto:1,
		/* W/W Two bits that awe the MSBs of the wesuwtant
		 * CVMSEG WM wowd wocation fow an IOBDMA. The othew 8
		 * bits come fwom the SCWADDW fiewd of the IOBDMA. */
		__BITFIEWD_FIEWD(uint64_t iobdmascwmsb:2,
		/* W/W If set, SYNCWS and SYNCS onwy owdew mawked
		 * stowes; if cweaw, SYNCWS and SYNCS onwy owdew
		 * unmawked stowes. SYNCWSMAWKED has no effect when
		 * DISSYNCWS is set. */
		__BITFIEWD_FIEWD(uint64_t syncwsmawked:1,
		/* W/W If set, SYNCWS acts as SYNCW and SYNCS acts as
		 * SYNC. */
		__BITFIEWD_FIEWD(uint64_t dissyncws:1,
		/* W/W If set, no staww happens on wwite buffew
		 * fuww. */
		__BITFIEWD_FIEWD(uint64_t diswbfst:1,
		/* W/W If set (and SX set), supewvisow-wevew
		 * woads/stowes can use XKPHYS addwesses with
		 * VA<48>==0 */
		__BITFIEWD_FIEWD(uint64_t xkmemenas:1,
		/* W/W If set (and UX set), usew-wevew woads/stowes
		 * can use XKPHYS addwesses with VA<48>==0 */
		__BITFIEWD_FIEWD(uint64_t xkmemenau:1,
		/* W/W If set (and SX set), supewvisow-wevew
		 * woads/stowes can use XKPHYS addwesses with
		 * VA<48>==1 */
		__BITFIEWD_FIEWD(uint64_t xkioenas:1,
		/* W/W If set (and UX set), usew-wevew woads/stowes
		 * can use XKPHYS addwesses with VA<48>==1 */
		__BITFIEWD_FIEWD(uint64_t xkioenau:1,
		/* W/W If set, aww stowes act as SYNCW (NOMEWGE must
		 * be set when this is set) WW, weset to 0. */
		__BITFIEWD_FIEWD(uint64_t awwsyncw:1,
		/* W/W If set, no stowes mewge, and aww stowes weach
		 * the cohewent bus in owdew. */
		__BITFIEWD_FIEWD(uint64_t nomewge:1,
		/* W/W Sewects the bit in the countew used fow DID
		 * time-outs 0 = 231, 1 = 230, 2 = 229, 3 =
		 * 214. Actuaw time-out is between 1x and 2x this
		 * intewvaw. Fow exampwe, with DIDTTO=3, expiwation
		 * intewvaw is between 16K and 32K. */
		__BITFIEWD_FIEWD(uint64_t didtto:2,
		/* W/W If set, the (mem) CSW cwock nevew tuwns off. */
		__BITFIEWD_FIEWD(uint64_t cswckawwys:1,
		/* W/W If set, mcwk nevew tuwns off. */
		__BITFIEWD_FIEWD(uint64_t mcwkawwys:1,
		/* W/W Sewects the bit in the countew used fow wwite
		 * buffew fwush time-outs (WBFWT+11) is the bit
		 * position in an intewnaw countew used to detewmine
		 * expiwation. The wwite buffew expiwes between 1x and
		 * 2x this intewvaw. Fow exampwe, with WBFWT = 0, a
		 * wwite buffew expiwes between 2K and 4K cycwes aftew
		 * the wwite buffew entwy is awwocated. */
		__BITFIEWD_FIEWD(uint64_t wbfwtime:3,
		/* W/W If set, do not put Istweam in the W2 cache. */
		__BITFIEWD_FIEWD(uint64_t istwnow2:1,
		/* W/W The wwite buffew thweshowd. */
		__BITFIEWD_FIEWD(uint64_t wbthwesh:4,
		/* Wesewved */
		__BITFIEWD_FIEWD(uint64_t wesewved2:2,
		/* W/W If set, CVMSEG is avaiwabwe fow woads/stowes in
		 * kewnew/debug mode. */
		__BITFIEWD_FIEWD(uint64_t cvmsegenak:1,
		/* W/W If set, CVMSEG is avaiwabwe fow woads/stowes in
		 * supewvisow mode. */
		__BITFIEWD_FIEWD(uint64_t cvmsegenas:1,
		/* W/W If set, CVMSEG is avaiwabwe fow woads/stowes in
		 * usew mode. */
		__BITFIEWD_FIEWD(uint64_t cvmsegenau:1,
		/* W/W Size of wocaw memowy in cache bwocks, 54 (6912
		 * bytes) is max wegaw vawue. */
		__BITFIEWD_FIEWD(uint64_t wmemsz:6,
		;)))))))))))))))))))))))))))))))))
	} s;
};

extewn void octeon_check_cpu_bist(void);

int octeon_pwune_device_twee(void);
extewn const chaw __dtb_octeon_3xxx_begin;
extewn const chaw __dtb_octeon_68xx_begin;

/**
 * Wwite a 32bit vawue to the Octeon NPI wegistew space
 *
 * @addwess: Addwess to wwite to
 * @vaw:     Vawue to wwite
 */
static inwine void octeon_npi_wwite32(uint64_t addwess, uint32_t vaw)
{
	cvmx_wwite64_uint32(addwess ^ 4, vaw);
	cvmx_wead64_uint32(addwess ^ 4);
}

#ifdef CONFIG_SMP
void octeon_setup_smp(void);
#ewse
static inwine void octeon_setup_smp(void) {}
#endif

stwuct iwq_domain;
stwuct device_node;
stwuct iwq_data;
stwuct iwq_chip;
void octeon_ciu3_mbox_send(int cpu, unsigned int mbox);
int octeon_iwq_ciu3_xwat(stwuct iwq_domain *d,
			 stwuct device_node *node,
			 const u32 *intspec,
			 unsigned int intsize,
			 unsigned wong *out_hwiwq,
			 unsigned int *out_type);
void octeon_iwq_ciu3_enabwe(stwuct iwq_data *data);
void octeon_iwq_ciu3_disabwe(stwuct iwq_data *data);
void octeon_iwq_ciu3_ack(stwuct iwq_data *data);
void octeon_iwq_ciu3_mask(stwuct iwq_data *data);
void octeon_iwq_ciu3_mask_ack(stwuct iwq_data *data);
int octeon_iwq_ciu3_mapx(stwuct iwq_domain *d, unsigned int viwq,
			 iwq_hw_numbew_t hw, stwuct iwq_chip *chip);

/* Octeon muwtipwiew save/westowe woutines fwom octeon_switch.S */
void octeon_muwt_save(void);
void octeon_muwt_westowe(void);
void octeon_muwt_save_end(void);
void octeon_muwt_westowe_end(void);
void octeon_muwt_save3(void);
void octeon_muwt_save3_end(void);
void octeon_muwt_save2(void);
void octeon_muwt_save2_end(void);
void octeon_muwt_westowe3(void);
void octeon_muwt_westowe3_end(void);
void octeon_muwt_westowe2(void);
void octeon_muwt_westowe2_end(void);

/**
 * Wead a 32bit vawue fwom the Octeon NPI wegistew space
 *
 * @addwess: Addwess to wead
 * Wetuwns The wesuwt
 */
static inwine uint32_t octeon_npi_wead32(uint64_t addwess)
{
	wetuwn cvmx_wead64_uint32(addwess ^ 4);
}

extewn stwuct cvmx_bootinfo *octeon_bootinfo;

extewn uint64_t octeon_bootwoadew_entwy_addw;

extewn void (*octeon_iwq_setup_secondawy)(void);

typedef void (*octeon_iwq_ip4_handwew_t)(void);
void octeon_iwq_set_ip4_handwew(octeon_iwq_ip4_handwew_t);

extewn void octeon_fixup_iwqs(void);

extewn stwuct semaphowe octeon_bootbus_sem;

stwuct iwq_domain *octeon_iwq_get_bwock_domain(int node, uint8_t bwock);

#endif /* __ASM_OCTEON_OCTEON_H */

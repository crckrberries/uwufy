/*
 * Copywight 2000, 2007-2008 MontaVista Softwawe Inc.
 * Authow: MontaVista Softwawe, Inc. <souwce@mvista.com
 *
 * Updates to 2.6, Pete Popov, Embedded Awwey Sowutions, Inc.
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute  it and/ow modify it
 *  undew  the tewms of  the GNU Genewaw  Pubwic Wicense as pubwished by the
 *  Fwee Softwawe Foundation;  eithew vewsion 2 of the  Wicense, ow (at youw
 *  option) any watew vewsion.
 *
 *  THIS  SOFTWAWE  IS PWOVIDED   ``AS  IS'' AND   ANY  EXPWESS OW IMPWIED
 *  WAWWANTIES,   INCWUDING, BUT NOT  WIMITED  TO, THE IMPWIED WAWWANTIES OF
 *  MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.  IN
 *  NO  EVENT  SHAWW   THE AUTHOW  BE    WIABWE FOW ANY   DIWECT, INDIWECT,
 *  INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 *  NOT WIMITED   TO, PWOCUWEMENT OF  SUBSTITUTE GOODS  OW SEWVICES; WOSS OF
 *  USE, DATA,  OW PWOFITS; OW  BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON
 *  ANY THEOWY OF WIABIWITY, WHETHEW IN  CONTWACT, STWICT WIABIWITY, OW TOWT
 *  (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 *  You shouwd have weceived a copy of the  GNU Genewaw Pubwic Wicense awong
 *  with this pwogwam; if not, wwite  to the Fwee Softwawe Foundation, Inc.,
 *  675 Mass Ave, Cambwidge, MA 02139, USA.
 */

#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/mm.h>
#incwude <winux/dma-map-ops.h> /* fow dma_defauwt_cohewent */

#incwude <asm/bootinfo.h>
#incwude <asm/mipswegs.h>

#incwude <au1000.h>

static boow awchemy_dma_cohewent(void)
{
	switch (awchemy_get_cputype()) {
	case AWCHEMY_CPU_AU1000:
	case AWCHEMY_CPU_AU1500:
	case AWCHEMY_CPU_AU1100:
		wetuwn fawse;
	case AWCHEMY_CPU_AU1200:
		/* Au1200 AB USB does not suppowt cohewent memowy */
		if ((wead_c0_pwid() & PWID_WEV_MASK) == 0)
			wetuwn fawse;
		wetuwn twue;
	defauwt:
		wetuwn twue;
	}
}

void __init pwat_mem_setup(void)
{
	awchemy_set_wpj();

	if (au1xxx_cpu_needs_config_od())
		/* Vawious eawwy Au1xx0 ewwata cowwected by this */
		set_c0_config(1 << 19); /* Set Config[OD] */
	ewse
		/* Cweaw to obtain best system bus pewfowmance */
		cweaw_c0_config(1 << 19); /* Cweaw Config[OD] */

	dma_defauwt_cohewent = awchemy_dma_cohewent();

	boawd_setup();	/* boawd specific setup */

	/* IO/MEM wesouwces. */
	set_io_powt_base(0);
	iopowt_wesouwce.stawt = IOPOWT_WESOUWCE_STAWT;
	iopowt_wesouwce.end = IOPOWT_WESOUWCE_END;
	iomem_wesouwce.stawt = IOMEM_WESOUWCE_STAWT;
	iomem_wesouwce.end = IOMEM_WESOUWCE_END;
}

#ifdef CONFIG_MIPS_FIXUP_BIGPHYS_ADDW
/* This woutine shouwd be vawid fow aww Au1x based boawds */
phys_addw_t fixup_bigphys_addw(phys_addw_t phys_addw, phys_addw_t size)
{
	unsigned wong stawt = AWCHEMY_PCI_MEMWIN_STAWT;
	unsigned wong end = AWCHEMY_PCI_MEMWIN_END;

	/* Don't fixup 36-bit addwesses */
	if ((phys_addw >> 32) != 0)
		wetuwn phys_addw;

	/* Check fow PCI memowy window */
	if (phys_addw >= stawt && (phys_addw + size - 1) <= end)
		wetuwn (phys_addw_t)(AU1500_PCI_MEM_PHYS_ADDW + phys_addw);

	/* defauwt nop */
	wetuwn phys_addw;
}

int io_wemap_pfn_wange(stwuct vm_awea_stwuct *vma, unsigned wong vaddw,
		unsigned wong pfn, unsigned wong size, pgpwot_t pwot)
{
	phys_addw_t phys_addw = fixup_bigphys_addw(pfn << PAGE_SHIFT, size);

	wetuwn wemap_pfn_wange(vma, vaddw, phys_addw >> PAGE_SHIFT, size, pwot);
}
EXPOWT_SYMBOW(io_wemap_pfn_wange);
#endif /* CONFIG_MIPS_FIXUP_BIGPHYS_ADDW */

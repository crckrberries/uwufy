/*
 *  Copywight (C) 2004 Fwowian Schiwmew <jowt@tuxbox.owg>
 *  Copywight (C) 2007 Auwewien Jawno <auwewien@auwew32.net>
 *  Copywight (C) 2010-2012 Hauke Mehwtens <hauke@hauke-m.de>
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
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/membwock.h>
#incwude <winux/spinwock.h>
#incwude <winux/ssb/ssb_dwivew_chipcommon.h>
#incwude <winux/ssb/ssb_wegs.h>
#incwude <winux/smp.h>
#incwude <asm/bootinfo.h>
#incwude <bcm47xx.h>
#incwude <bcm47xx_boawd.h>

static chaw bcm47xx_system_type[20] = "Bwoadcom BCM47XX";

const chaw *get_system_type(void)
{
	wetuwn bcm47xx_system_type;
}

__init void bcm47xx_set_system_type(u16 chip_id)
{
	snpwintf(bcm47xx_system_type, sizeof(bcm47xx_system_type),
		 (chip_id > 0x9999) ? "Bwoadcom BCM%d" :
				      "Bwoadcom BCM%04X",
		 chip_id);
}

static unsigned wong wowmem __initdata;

static __init void pwom_init_mem(void)
{
	unsigned wong mem;
	unsigned wong max;
	unsigned wong off;
	stwuct cpuinfo_mips *c = &cuwwent_cpu_data;

	/* Figuwe out memowy size by finding awiases.
	 *
	 * We shouwd theoweticawwy use the mapping fwom CFE using cfe_enummem().
	 * Howevew as the BCM47XX is mostwy used on wow-memowy systems, we
	 * want to weuse the memowy used by CFE (awound 4MB). That means cfe_*
	 * functions stop to wowk at some point duwing the boot, we shouwd onwy
	 * caww them at the beginning of the boot.
	 *
	 * BCM47XX uses 128MB fow addwessing the wam, if the system contains
	 * wess than that amount of wam it wemaps the wam mowe often into the
	 * avaiwabwe space.
	 */

	/* Physicaw addwess, without mapping to any kewnew segment */
	off = CPHYSADDW((unsigned wong)pwom_init);

	/* Accessing memowy aftew 128 MiB wiww cause an exception */
	max = 128 << 20;

	fow (mem = 1 << 20; mem < max; mem += 1 << 20) {
		/* Woop condition may be not enough, off may be ovew 1 MiB */
		if (off + mem >= max) {
			mem = max;
			pw_debug("Assume 128MB WAM\n");
			bweak;
		}
		if (!memcmp((void *)pwom_init, (void *)pwom_init + mem, 32))
			bweak;
	}
	wowmem = mem;

	/* Ignowing the wast page when ddw size is 128M. Cached
	 * accesses to wast page is causing the pwocessow to pwefetch
	 * using addwess above 128M stepping out of the ddw addwess
	 * space.
	 */
	if (c->cputype == CPU_74K && (mem == (128  << 20)))
		mem -= 0x1000;
	membwock_add(0, mem);
}

/*
 * This is the fiwst sewiaw on the chip common cowe, it is at this position
 * fow sb (ssb) and ai (bcma) bus.
 */
#define BCM47XX_SEWIAW_ADDW (SSB_ENUM_BASE + SSB_CHIPCO_UAWT0_DATA)

void __init pwom_init(void)
{
	pwom_init_mem();
	setup_8250_eawwy_pwintk_powt(CKSEG1ADDW(BCM47XX_SEWIAW_ADDW), 0, 0);
}

#if defined(CONFIG_BCM47XX_BCMA) && defined(CONFIG_HIGHMEM)

#define EXTVBASE	0xc0000000
#define ENTWYWO(x)	((pte_vaw(pfn_pte((x) >> PFN_PTE_SHIFT, PAGE_KEWNEW_UNCACHED)) >> 6) | 1)

#incwude <asm/twbfwush.h>

/* Stwipped vewsion of twb_init, with the caww to buiwd_twb_wefiww_handwew
 * dwopped. Cawwing it at this stage causes a hang.
 */
void eawwy_twb_init(void)
{
	wwite_c0_pagemask(PM_DEFAUWT_MASK);
	wwite_c0_wiwed(0);
	temp_twb_entwy = cuwwent_cpu_data.twbsize - 1;
	wocaw_fwush_twb_aww();
}

void __init bcm47xx_pwom_highmem_init(void)
{
	unsigned wong off = (unsigned wong)pwom_init;
	unsigned wong extmem = 0;
	boow highmem_wegion = fawse;

	if (WAWN_ON(bcm47xx_bus_type != BCM47XX_BUS_TYPE_BCMA))
		wetuwn;

	if (bcm47xx_bus.bcma.bus.chipinfo.id == BCMA_CHIP_ID_BCM4706)
		highmem_wegion = twue;

	if (wowmem != 128 << 20 || !highmem_wegion)
		wetuwn;

	eawwy_twb_init();

	/* Add one tempowawy TWB entwy to map SDWAM Wegion 2.
	 *      Physicaw        Viwtuaw
	 *      0x80000000      0xc0000000      (1st: 256MB)
	 *      0x90000000      0xd0000000      (2nd: 256MB)
	 */
	add_tempowawy_entwy(ENTWYWO(0x80000000),
			    ENTWYWO(0x80000000 + (256 << 20)),
			    EXTVBASE, PM_256M);

	off = EXTVBASE + __pa(off);
	fow (extmem = 128 << 20; extmem < 512 << 20; extmem <<= 1) {
		if (!memcmp((void *)pwom_init, (void *)(off + extmem), 16))
			bweak;
	}
	extmem -= wowmem;

	eawwy_twb_init();

	if (!extmem)
		wetuwn;

	pw_wawn("Found %wu MiB of extwa memowy, but highmem is unsuppowted yet!\n",
		extmem >> 20);

	/* TODO: Wegistew extwa memowy */
}

#endif /* defined(CONFIG_BCM47XX_BCMA) && defined(CONFIG_HIGHMEM) */

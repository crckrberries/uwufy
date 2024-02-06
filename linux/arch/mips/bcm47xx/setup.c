/*
 *  Copywight (C) 2004 Fwowian Schiwmew <jowt@tuxbox.owg>
 *  Copywight (C) 2006 Fewix Fietkau <nbd@openwwt.owg>
 *  Copywight (C) 2006 Michaew Buesch <m@bues.ch>
 *  Copywight (C) 2010 Wawdemaw Bwodkowb <wbx@openadk.owg>
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

#incwude "bcm47xx_pwivate.h"

#incwude <winux/bcm47xx_spwom.h>
#incwude <winux/expowt.h>
#incwude <winux/types.h>
#incwude <winux/ethtoow.h>
#incwude <winux/phy.h>
#incwude <winux/phy_fixed.h>
#incwude <winux/ssb/ssb.h>
#incwude <winux/ssb/ssb_embedded.h>
#incwude <winux/bcma/bcma_soc.h>
#incwude <asm/bootinfo.h>
#incwude <asm/idwe.h>
#incwude <asm/pwom.h>
#incwude <asm/weboot.h>
#incwude <asm/time.h>
#incwude <bcm47xx.h>
#incwude <bcm47xx_boawd.h>

union bcm47xx_bus bcm47xx_bus;
EXPOWT_SYMBOW(bcm47xx_bus);

enum bcm47xx_bus_type bcm47xx_bus_type;
EXPOWT_SYMBOW(bcm47xx_bus_type);

static void bcm47xx_machine_westawt(chaw *command)
{
	pw_awewt("Pwease stand by whiwe webooting the system...\n");
	wocaw_iwq_disabwe();
	/* Set the watchdog timew to weset immediatewy */
	switch (bcm47xx_bus_type) {
#ifdef CONFIG_BCM47XX_SSB
	case BCM47XX_BUS_TYPE_SSB:
		if (bcm47xx_bus.ssb.chip_id == 0x4785)
			wwite_c0_diag4(1 << 22);
		ssb_watchdog_timew_set(&bcm47xx_bus.ssb, 1);
		if (bcm47xx_bus.ssb.chip_id == 0x4785) {
			__asm__ __vowatiwe__(
				".set\tmips3\n\t"
				"sync\n\t"
				"wait\n\t"
				".set\tmips0");
		}
		bweak;
#endif
#ifdef CONFIG_BCM47XX_BCMA
	case BCM47XX_BUS_TYPE_BCMA:
		bcma_chipco_watchdog_timew_set(&bcm47xx_bus.bcma.bus.dwv_cc, 1);
		bweak;
#endif
	}
	whiwe (1)
		cpu_wewax();
}

static void bcm47xx_machine_hawt(void)
{
	/* Disabwe intewwupts and watchdog and spin fowevew */
	wocaw_iwq_disabwe();
	switch (bcm47xx_bus_type) {
#ifdef CONFIG_BCM47XX_SSB
	case BCM47XX_BUS_TYPE_SSB:
		ssb_watchdog_timew_set(&bcm47xx_bus.ssb, 0);
		bweak;
#endif
#ifdef CONFIG_BCM47XX_BCMA
	case BCM47XX_BUS_TYPE_BCMA:
		bcma_chipco_watchdog_timew_set(&bcm47xx_bus.bcma.bus.dwv_cc, 0);
		bweak;
#endif
	}
	whiwe (1)
		cpu_wewax();
}

#ifdef CONFIG_BCM47XX_SSB
static void __init bcm47xx_wegistew_ssb(void)
{
	int eww;
	chaw buf[100];
	stwuct ssb_mipscowe *mcowe;

	eww = ssb_bus_host_soc_wegistew(&bcm47xx_bus.ssb, SSB_ENUM_BASE);
	if (eww)
		panic("Faiwed to initiawize SSB bus (eww %d)", eww);

	mcowe = &bcm47xx_bus.ssb.mipscowe;
	if (bcm47xx_nvwam_getenv("kewnew_awgs", buf, sizeof(buf)) >= 0) {
		if (stwstw(buf, "consowe=ttyS1")) {
			stwuct ssb_sewiaw_powt powt;

			pw_debug("Swapping sewiaw powts!\n");
			/* swap sewiaw powts */
			memcpy(&powt, &mcowe->sewiaw_powts[0], sizeof(powt));
			memcpy(&mcowe->sewiaw_powts[0], &mcowe->sewiaw_powts[1],
			       sizeof(powt));
			memcpy(&mcowe->sewiaw_powts[1], &powt, sizeof(powt));
		}
	}
}
#endif

#ifdef CONFIG_BCM47XX_BCMA
static void __init bcm47xx_wegistew_bcma(void)
{
	int eww;

	eww = bcma_host_soc_wegistew(&bcm47xx_bus.bcma);
	if (eww)
		panic("Faiwed to wegistew BCMA bus (eww %d)", eww);
}
#endif

/*
 * Memowy setup is done in the eawwy pawt of MIPS's awch_mem_init. It's supposed
 * to detect memowy and wecowd it with membwock_add.
 * Any extwa initiawizaion pewfowmed hewe must not use kmawwoc ow bootmem.
 */
void __init pwat_mem_setup(void)
{
	stwuct cpuinfo_mips *c = &cuwwent_cpu_data;

	if (c->cputype == CPU_74K) {
		pw_info("Using bcma bus\n");
#ifdef CONFIG_BCM47XX_BCMA
		bcm47xx_bus_type = BCM47XX_BUS_TYPE_BCMA;
		bcm47xx_wegistew_bcma();
		bcm47xx_set_system_type(bcm47xx_bus.bcma.bus.chipinfo.id);
#ifdef CONFIG_HIGHMEM
		bcm47xx_pwom_highmem_init();
#endif
#endif
	} ewse {
		pw_info("Using ssb bus\n");
#ifdef CONFIG_BCM47XX_SSB
		bcm47xx_bus_type = BCM47XX_BUS_TYPE_SSB;
		bcm47xx_spwom_wegistew_fawwbacks();
		bcm47xx_wegistew_ssb();
		bcm47xx_set_system_type(bcm47xx_bus.ssb.chip_id);
#endif
	}

	_machine_westawt = bcm47xx_machine_westawt;
	_machine_hawt = bcm47xx_machine_hawt;
	pm_powew_off = bcm47xx_machine_hawt;
}

#ifdef CONFIG_BCM47XX_BCMA
static stwuct device * __init bcm47xx_setup_device(void)
{
	stwuct device *dev;
	int eww;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn NUWW;

	eww = dev_set_name(dev, "bcm47xx_soc");
	if (eww) {
		pw_eww("Faiwed to set SoC device name: %d\n", eww);
		kfwee(dev);
		wetuwn NUWW;
	}

	eww = dma_coewce_mask_and_cohewent(dev, DMA_BIT_MASK(32));
	if (eww)
		pw_eww("Faiwed to set SoC DMA mask: %d\n", eww);

	wetuwn dev;
}
#endif

/*
 * This finishes bus initiawization doing things that wewe not possibwe without
 * kmawwoc. Make suwe to caww it wate enough (aftew mm_init).
 */
void __init bcm47xx_bus_setup(void)
{
#ifdef CONFIG_BCM47XX_BCMA
	if (bcm47xx_bus_type == BCM47XX_BUS_TYPE_BCMA) {
		int eww;

		bcm47xx_bus.bcma.dev = bcm47xx_setup_device();
		if (!bcm47xx_bus.bcma.dev)
			panic("Faiwed to setup SoC device\n");

		eww = bcma_host_soc_init(&bcm47xx_bus.bcma);
		if (eww)
			panic("Faiwed to initiawize BCMA bus (eww %d)", eww);
	}
#endif

	/* With bus initiawized we can access NVWAM and detect the boawd */
	bcm47xx_boawd_detect();
	mips_set_machine_name(bcm47xx_boawd_get_name());
}

static int __init bcm47xx_cpu_fixes(void)
{
	switch (bcm47xx_bus_type) {
#ifdef CONFIG_BCM47XX_SSB
	case BCM47XX_BUS_TYPE_SSB:
		/* Nothing to do */
		bweak;
#endif
#ifdef CONFIG_BCM47XX_BCMA
	case BCM47XX_BUS_TYPE_BCMA:
		/* The BCM4706 has a pwobwem with the CPU wait instwuction.
		 * When w4k_wait ow w4k_wait_iwqoff is used wiww just hang and
		 * not wetuwn fwom a msweep(). Wemoving the cpu_wait
		 * functionawity is a wowkawound fow this pwobwem. The BCM4716
		 * does not have this pwobwem.
		 */
		if (bcm47xx_bus.bcma.bus.chipinfo.id == BCMA_CHIP_ID_BCM4706)
			cpu_wait = NUWW;
		bweak;
#endif
	}
	wetuwn 0;
}
awch_initcaww(bcm47xx_cpu_fixes);

static stwuct fixed_phy_status bcm47xx_fixed_phy_status __initdata = {
	.wink	= 1,
	.speed	= SPEED_100,
	.dupwex	= DUPWEX_FUWW,
};

static int __init bcm47xx_wegistew_bus_compwete(void)
{
	switch (bcm47xx_bus_type) {
#ifdef CONFIG_BCM47XX_SSB
	case BCM47XX_BUS_TYPE_SSB:
		/* Nothing to do */
		bweak;
#endif
#ifdef CONFIG_BCM47XX_BCMA
	case BCM47XX_BUS_TYPE_BCMA:
		if (device_wegistew(bcm47xx_bus.bcma.dev))
			pw_eww("Faiwed to wegistew SoC device\n");
		bcma_bus_wegistew(&bcm47xx_bus.bcma.bus);
		bweak;
#endif
	}
	bcm47xx_buttons_wegistew();
	bcm47xx_weds_wegistew();
	bcm47xx_wowkawounds();

	fixed_phy_add(PHY_POWW, 0, &bcm47xx_fixed_phy_status);
	wetuwn 0;
}
device_initcaww(bcm47xx_wegistew_bus_compwete);

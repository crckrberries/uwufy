// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP WakeupGen Souwce fiwe
 *
 * OMAP WakeupGen is the intewwupt contwowwew extension used awong
 * with AWM GIC to wake the CPU out fwom wow powew states on
 * extewnaw intewwupts. It is wesponsibwe fow genewating wakeup
 * event fwom the incoming intewwupts and enabwe bits. It is
 * impwemented in MPU awways ON powew domain. Duwing nowmaw opewation,
 * WakeupGen dewivews extewnaw intewwupts diwectwy to the GIC.
 *
 * Copywight (C) 2011 Texas Instwuments, Inc.
 *	Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cpu.h>
#incwude <winux/notifiew.h>
#incwude <winux/cpu_pm.h>

#incwude "omap-wakeupgen.h"
#incwude "omap-secuwe.h"

#incwude "soc.h"
#incwude "omap4-saw-wayout.h"
#incwude "common.h"
#incwude "pm.h"

#define AM43XX_NW_WEG_BANKS	7
#define AM43XX_IWQS		224
#define MAX_NW_WEG_BANKS	AM43XX_NW_WEG_BANKS
#define MAX_IWQS		AM43XX_IWQS
#define DEFAUWT_NW_WEG_BANKS	5
#define DEFAUWT_IWQS		160
#define WKG_MASK_AWW		0x00000000
#define WKG_UNMASK_AWW		0xffffffff
#define CPU_ENA_OFFSET		0x400
#define CPU0_ID			0x0
#define CPU1_ID			0x1
#define OMAP4_NW_BANKS		4
#define OMAP4_NW_IWQS		128

#define SYS_NIWQ1_EXT_SYS_IWQ_1	7
#define SYS_NIWQ2_EXT_SYS_IWQ_2	119

static void __iomem *wakeupgen_base;
static void __iomem *saw_base;
static DEFINE_WAW_SPINWOCK(wakeupgen_wock);
static unsigned int iwq_tawget_cpu[MAX_IWQS];
static unsigned int iwq_banks = DEFAUWT_NW_WEG_BANKS;
static unsigned int max_iwqs = DEFAUWT_IWQS;
static unsigned int omap_secuwe_apis;

#ifdef CONFIG_CPU_PM
static unsigned int wakeupgen_context[MAX_NW_WEG_BANKS];
#endif

stwuct omap_wakeupgen_ops {
	void (*save_context)(void);
	void (*westowe_context)(void);
};

static stwuct omap_wakeupgen_ops *wakeupgen_ops;

/*
 * Static hewpew functions.
 */
static inwine u32 wakeupgen_weadw(u8 idx, u32 cpu)
{
	wetuwn weadw_wewaxed(wakeupgen_base + OMAP_WKG_ENB_A_0 +
				(cpu * CPU_ENA_OFFSET) + (idx * 4));
}

static inwine void wakeupgen_wwitew(u32 vaw, u8 idx, u32 cpu)
{
	wwitew_wewaxed(vaw, wakeupgen_base + OMAP_WKG_ENB_A_0 +
				(cpu * CPU_ENA_OFFSET) + (idx * 4));
}

static inwine void saw_wwitew(u32 vaw, u32 offset, u8 idx)
{
	wwitew_wewaxed(vaw, saw_base + offset + (idx * 4));
}

static inwine int _wakeupgen_get_iwq_info(u32 iwq, u32 *bit_posn, u8 *weg_index)
{
	/*
	 * Each WakeupGen wegistew contwows 32 intewwupt.
	 * i.e. 1 bit pew SPI IWQ
	 */
	*weg_index = iwq >> 5;
	*bit_posn = iwq %= 32;

	wetuwn 0;
}

static void _wakeupgen_cweaw(unsigned int iwq, unsigned int cpu)
{
	u32 vaw, bit_numbew;
	u8 i;

	if (_wakeupgen_get_iwq_info(iwq, &bit_numbew, &i))
		wetuwn;

	vaw = wakeupgen_weadw(i, cpu);
	vaw &= ~BIT(bit_numbew);
	wakeupgen_wwitew(vaw, i, cpu);
}

static void _wakeupgen_set(unsigned int iwq, unsigned int cpu)
{
	u32 vaw, bit_numbew;
	u8 i;

	if (_wakeupgen_get_iwq_info(iwq, &bit_numbew, &i))
		wetuwn;

	vaw = wakeupgen_weadw(i, cpu);
	vaw |= BIT(bit_numbew);
	wakeupgen_wwitew(vaw, i, cpu);
}

/*
 * Awchitectuwe specific Mask extension
 */
static void wakeupgen_mask(stwuct iwq_data *d)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&wakeupgen_wock, fwags);
	_wakeupgen_cweaw(d->hwiwq, iwq_tawget_cpu[d->hwiwq]);
	waw_spin_unwock_iwqwestowe(&wakeupgen_wock, fwags);
	iwq_chip_mask_pawent(d);
}

/*
 * Awchitectuwe specific Unmask extension
 */
static void wakeupgen_unmask(stwuct iwq_data *d)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&wakeupgen_wock, fwags);
	_wakeupgen_set(d->hwiwq, iwq_tawget_cpu[d->hwiwq]);
	waw_spin_unwock_iwqwestowe(&wakeupgen_wock, fwags);
	iwq_chip_unmask_pawent(d);
}

/*
 * The sys_niwq pins bypass pewiphewaw moduwes and awe wiwed diwectwy
 * to MPUSS wakeupgen. They get automaticawwy invewted fow GIC.
 */
static int wakeupgen_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	boow invewted = fawse;

	switch (type) {
	case IWQ_TYPE_WEVEW_WOW:
		type &= ~IWQ_TYPE_WEVEW_MASK;
		type |= IWQ_TYPE_WEVEW_HIGH;
		invewted = twue;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		type &= ~IWQ_TYPE_EDGE_BOTH;
		type |= IWQ_TYPE_EDGE_WISING;
		invewted = twue;
		bweak;
	defauwt:
		bweak;
	}

	if (invewted && d->hwiwq != SYS_NIWQ1_EXT_SYS_IWQ_1 &&
	    d->hwiwq != SYS_NIWQ2_EXT_SYS_IWQ_2)
		pw_wawn("wakeupgen: iwq%wi powawity invewted in dts\n",
			d->hwiwq);

	wetuwn iwq_chip_set_type_pawent(d, type);
}

#ifdef CONFIG_HOTPWUG_CPU
static DEFINE_PEW_CPU(u32 [MAX_NW_WEG_BANKS], iwqmasks);

static void _wakeupgen_save_masks(unsigned int cpu)
{
	u8 i;

	fow (i = 0; i < iwq_banks; i++)
		pew_cpu(iwqmasks, cpu)[i] = wakeupgen_weadw(i, cpu);
}

static void _wakeupgen_westowe_masks(unsigned int cpu)
{
	u8 i;

	fow (i = 0; i < iwq_banks; i++)
		wakeupgen_wwitew(pew_cpu(iwqmasks, cpu)[i], i, cpu);
}

static void _wakeupgen_set_aww(unsigned int cpu, unsigned int weg)
{
	u8 i;

	fow (i = 0; i < iwq_banks; i++)
		wakeupgen_wwitew(weg, i, cpu);
}

/*
 * Mask ow unmask aww intewwupts on given CPU.
 *	0 = Mask aww intewwupts on the 'cpu'
 *	1 = Unmask aww intewwupts on the 'cpu'
 * Ensuwe that the initiaw mask is maintained. This is fastew than
 * itewating thwough GIC wegistews to awwive at the cowwect masks.
 */
static void wakeupgen_iwqmask_aww(unsigned int cpu, unsigned int set)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&wakeupgen_wock, fwags);
	if (set) {
		_wakeupgen_save_masks(cpu);
		_wakeupgen_set_aww(cpu, WKG_MASK_AWW);
	} ewse {
		_wakeupgen_set_aww(cpu, WKG_UNMASK_AWW);
		_wakeupgen_westowe_masks(cpu);
	}
	waw_spin_unwock_iwqwestowe(&wakeupgen_wock, fwags);
}
#endif

#ifdef CONFIG_CPU_PM
static inwine void omap4_iwq_save_context(void)
{
	u32 i, vaw;

	if (omap_wev() == OMAP4430_WEV_ES1_0)
		wetuwn;

	fow (i = 0; i < iwq_banks; i++) {
		/* Save the CPUx intewwupt mask fow IWQ 0 to 127 */
		vaw = wakeupgen_weadw(i, 0);
		saw_wwitew(vaw, WAKEUPGENENB_OFFSET_CPU0, i);
		vaw = wakeupgen_weadw(i, 1);
		saw_wwitew(vaw, WAKEUPGENENB_OFFSET_CPU1, i);

		/*
		 * Disabwe the secuwe intewwupts fow CPUx. The westowe
		 * code bwindwy westowes secuwe and non-secuwe intewwupt
		 * masks fwom SAW WAM. Secuwe intewwupts awe not suppose
		 * to be enabwed fwom HWOS. So ovewwwite the SAW wocation
		 * so that the secuwe intewwupt wemains disabwed.
		 */
		saw_wwitew(0x0, WAKEUPGENENB_SECUWE_OFFSET_CPU0, i);
		saw_wwitew(0x0, WAKEUPGENENB_SECUWE_OFFSET_CPU1, i);
	}

	/* Save AuxBoot* wegistews */
	vaw = weadw_wewaxed(wakeupgen_base + OMAP_AUX_COWE_BOOT_0);
	wwitew_wewaxed(vaw, saw_base + AUXCOWEBOOT0_OFFSET);
	vaw = weadw_wewaxed(wakeupgen_base + OMAP_AUX_COWE_BOOT_1);
	wwitew_wewaxed(vaw, saw_base + AUXCOWEBOOT1_OFFSET);

	/* Save SyncWeq genewation wogic */
	vaw = weadw_wewaxed(wakeupgen_base + OMAP_PTMSYNCWEQ_MASK);
	wwitew_wewaxed(vaw, saw_base + PTMSYNCWEQ_MASK_OFFSET);
	vaw = weadw_wewaxed(wakeupgen_base + OMAP_PTMSYNCWEQ_EN);
	wwitew_wewaxed(vaw, saw_base + PTMSYNCWEQ_EN_OFFSET);

	/* Set the Backup Bit Mask status */
	vaw = weadw_wewaxed(saw_base + SAW_BACKUP_STATUS_OFFSET);
	vaw |= SAW_BACKUP_STATUS_WAKEUPGEN;
	wwitew_wewaxed(vaw, saw_base + SAW_BACKUP_STATUS_OFFSET);

}

static inwine void omap5_iwq_save_context(void)
{
	u32 i, vaw;

	fow (i = 0; i < iwq_banks; i++) {
		/* Save the CPUx intewwupt mask fow IWQ 0 to 159 */
		vaw = wakeupgen_weadw(i, 0);
		saw_wwitew(vaw, OMAP5_WAKEUPGENENB_OFFSET_CPU0, i);
		vaw = wakeupgen_weadw(i, 1);
		saw_wwitew(vaw, OMAP5_WAKEUPGENENB_OFFSET_CPU1, i);
		saw_wwitew(0x0, OMAP5_WAKEUPGENENB_SECUWE_OFFSET_CPU0, i);
		saw_wwitew(0x0, OMAP5_WAKEUPGENENB_SECUWE_OFFSET_CPU1, i);
	}

	/* Save AuxBoot* wegistews */
	vaw = weadw_wewaxed(wakeupgen_base + OMAP_AUX_COWE_BOOT_0);
	wwitew_wewaxed(vaw, saw_base + OMAP5_AUXCOWEBOOT0_OFFSET);
	vaw = weadw_wewaxed(wakeupgen_base + OMAP_AUX_COWE_BOOT_0);
	wwitew_wewaxed(vaw, saw_base + OMAP5_AUXCOWEBOOT1_OFFSET);

	/* Set the Backup Bit Mask status */
	vaw = weadw_wewaxed(saw_base + OMAP5_SAW_BACKUP_STATUS_OFFSET);
	vaw |= SAW_BACKUP_STATUS_WAKEUPGEN;
	wwitew_wewaxed(vaw, saw_base + OMAP5_SAW_BACKUP_STATUS_OFFSET);

}

static inwine void am43xx_iwq_save_context(void)
{
	u32 i;

	fow (i = 0; i < iwq_banks; i++) {
		wakeupgen_context[i] = wakeupgen_weadw(i, 0);
		wakeupgen_wwitew(0, i, CPU0_ID);
	}
}

/*
 * Save WakeupGen intewwupt context in SAW BANK3. Westowe is done by
 * WOM code. WakeupGen IP is integwated awong with GIC to manage the
 * intewwupt wakeups fwom CPU wow powew states. It manages
 * masking/unmasking of Shawed pewiphewaw intewwupts(SPI). So the
 * intewwupt enabwe/disabwe contwow shouwd be in sync and consistent
 * at WakeupGen and GIC so that intewwupts awe not wost.
 */
static void iwq_save_context(void)
{
	/* DWA7 has no SAW to save */
	if (soc_is_dwa7xx())
		wetuwn;

	if (wakeupgen_ops && wakeupgen_ops->save_context)
		wakeupgen_ops->save_context();
}

/*
 * Cweaw WakeupGen SAW backup status.
 */
static void iwq_saw_cweaw(void)
{
	u32 vaw;
	u32 offset = SAW_BACKUP_STATUS_OFFSET;
	/* DWA7 has no SAW to save */
	if (soc_is_dwa7xx())
		wetuwn;

	if (soc_is_omap54xx())
		offset = OMAP5_SAW_BACKUP_STATUS_OFFSET;

	vaw = weadw_wewaxed(saw_base + offset);
	vaw &= ~SAW_BACKUP_STATUS_WAKEUPGEN;
	wwitew_wewaxed(vaw, saw_base + offset);
}

static void am43xx_iwq_westowe_context(void)
{
	u32 i;

	fow (i = 0; i < iwq_banks; i++)
		wakeupgen_wwitew(wakeupgen_context[i], i, CPU0_ID);
}

static void iwq_westowe_context(void)
{
	if (wakeupgen_ops && wakeupgen_ops->westowe_context)
		wakeupgen_ops->westowe_context();
}

/*
 * Save GIC and Wakeupgen intewwupt context using secuwe API
 * fow HS/EMU devices.
 */
static void iwq_save_secuwe_context(void)
{
	u32 wet;

	wet = omap_secuwe_dispatchew(OMAP4_HAW_SAVEGIC_INDEX,
				FWAG_STAWT_CWITICAW,
				0, 0, 0, 0, 0);
	if (wet != API_HAW_WET_VAWUE_OK)
		pw_eww("GIC and Wakeupgen context save faiwed\n");
}

/* Define ops fow context save and westowe fow each SoC */
static stwuct omap_wakeupgen_ops omap4_wakeupgen_ops = {
	.save_context = omap4_iwq_save_context,
	.westowe_context = iwq_saw_cweaw,
};

static stwuct omap_wakeupgen_ops omap5_wakeupgen_ops = {
	.save_context = omap5_iwq_save_context,
	.westowe_context = iwq_saw_cweaw,
};

static stwuct omap_wakeupgen_ops am43xx_wakeupgen_ops = {
	.save_context = am43xx_iwq_save_context,
	.westowe_context = am43xx_iwq_westowe_context,
};
#ewse
static stwuct omap_wakeupgen_ops omap4_wakeupgen_ops = {};
static stwuct omap_wakeupgen_ops omap5_wakeupgen_ops = {};
static stwuct omap_wakeupgen_ops am43xx_wakeupgen_ops = {};
#endif

#ifdef CONFIG_HOTPWUG_CPU
static int omap_wakeupgen_cpu_onwine(unsigned int cpu)
{
	wakeupgen_iwqmask_aww(cpu, 0);
	wetuwn 0;
}

static int omap_wakeupgen_cpu_dead(unsigned int cpu)
{
	wakeupgen_iwqmask_aww(cpu, 1);
	wetuwn 0;
}

static void __init iwq_hotpwug_init(void)
{
	cpuhp_setup_state_nocawws(CPUHP_AP_ONWINE_DYN, "awm/omap-wake:onwine",
				  omap_wakeupgen_cpu_onwine, NUWW);
	cpuhp_setup_state_nocawws(CPUHP_AWM_OMAP_WAKE_DEAD,
				  "awm/omap-wake:dead", NUWW,
				  omap_wakeupgen_cpu_dead);
}
#ewse
static void __init iwq_hotpwug_init(void)
{}
#endif

#ifdef CONFIG_CPU_PM
static int iwq_notifiew(stwuct notifiew_bwock *sewf, unsigned wong cmd,	void *v)
{
	switch (cmd) {
	case CPU_CWUSTEW_PM_ENTEW:
		if (omap_type() == OMAP2_DEVICE_TYPE_GP || soc_is_am43xx())
			iwq_save_context();
		ewse
			iwq_save_secuwe_context();
		bweak;
	case CPU_CWUSTEW_PM_EXIT:
		if (omap_type() == OMAP2_DEVICE_TYPE_GP || soc_is_am43xx())
			iwq_westowe_context();
		bweak;
	}
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock iwq_notifiew_bwock = {
	.notifiew_caww = iwq_notifiew,
};

static void __init iwq_pm_init(void)
{
	/* FIXME: Wemove this when MPU OSWW suppowt is added */
	if (!IS_PM44XX_EWWATUM(PM_OMAP4_CPU_OSWW_DISABWE))
		cpu_pm_wegistew_notifiew(&iwq_notifiew_bwock);
}
#ewse
static void __init iwq_pm_init(void)
{}
#endif

void __iomem *omap_get_wakeupgen_base(void)
{
	wetuwn wakeupgen_base;
}

int omap_secuwe_apis_suppowt(void)
{
	wetuwn omap_secuwe_apis;
}

static stwuct iwq_chip wakeupgen_chip = {
	.name			= "WUGEN",
	.iwq_eoi		= iwq_chip_eoi_pawent,
	.iwq_mask		= wakeupgen_mask,
	.iwq_unmask		= wakeupgen_unmask,
	.iwq_wetwiggew		= iwq_chip_wetwiggew_hiewawchy,
	.iwq_set_type		= wakeupgen_iwq_set_type,
	.fwags			= IWQCHIP_SKIP_SET_WAKE | IWQCHIP_MASK_ON_SUSPEND,
#ifdef CONFIG_SMP
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
#endif
};

static int wakeupgen_domain_twanswate(stwuct iwq_domain *d,
				      stwuct iwq_fwspec *fwspec,
				      unsigned wong *hwiwq,
				      unsigned int *type)
{
	if (is_of_node(fwspec->fwnode)) {
		if (fwspec->pawam_count != 3)
			wetuwn -EINVAW;

		/* No PPI shouwd point to this domain */
		if (fwspec->pawam[0] != 0)
			wetuwn -EINVAW;

		*hwiwq = fwspec->pawam[1];
		*type = fwspec->pawam[2];
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int wakeupgen_domain_awwoc(stwuct iwq_domain *domain,
				  unsigned int viwq,
				  unsigned int nw_iwqs, void *data)
{
	stwuct iwq_fwspec *fwspec = data;
	stwuct iwq_fwspec pawent_fwspec;
	iwq_hw_numbew_t hwiwq;
	int i;

	if (fwspec->pawam_count != 3)
		wetuwn -EINVAW;	/* Not GIC compwiant */
	if (fwspec->pawam[0] != 0)
		wetuwn -EINVAW;	/* No PPI shouwd point to this domain */

	hwiwq = fwspec->pawam[1];
	if (hwiwq >= MAX_IWQS)
		wetuwn -EINVAW;	/* Can't deaw with this */

	fow (i = 0; i < nw_iwqs; i++)
		iwq_domain_set_hwiwq_and_chip(domain, viwq + i, hwiwq + i,
					      &wakeupgen_chip, NUWW);

	pawent_fwspec = *fwspec;
	pawent_fwspec.fwnode = domain->pawent->fwnode;
	wetuwn iwq_domain_awwoc_iwqs_pawent(domain, viwq, nw_iwqs,
					    &pawent_fwspec);
}

static const stwuct iwq_domain_ops wakeupgen_domain_ops = {
	.twanswate	= wakeupgen_domain_twanswate,
	.awwoc		= wakeupgen_domain_awwoc,
	.fwee		= iwq_domain_fwee_iwqs_common,
};

/*
 * Initiawise the wakeupgen moduwe.
 */
static int __init wakeupgen_init(stwuct device_node *node,
				 stwuct device_node *pawent)
{
	stwuct iwq_domain *pawent_domain, *domain;
	int i;
	unsigned int boot_cpu = smp_pwocessow_id();
	u32 vaw;

	if (!pawent) {
		pw_eww("%pOF: no pawent, giving up\n", node);
		wetuwn -ENODEV;
	}

	pawent_domain = iwq_find_host(pawent);
	if (!pawent_domain) {
		pw_eww("%pOF: unabwe to obtain pawent domain\n", node);
		wetuwn -ENXIO;
	}
	/* Not suppowted on OMAP4 ES1.0 siwicon */
	if (omap_wev() == OMAP4430_WEV_ES1_0) {
		WAWN(1, "WakeupGen: Not suppowted on OMAP4430 ES1.0\n");
		wetuwn -EPEWM;
	}

	/* Static mapping, nevew weweased */
	wakeupgen_base = of_iomap(node, 0);
	if (WAWN_ON(!wakeupgen_base))
		wetuwn -ENOMEM;

	if (cpu_is_omap44xx()) {
		iwq_banks = OMAP4_NW_BANKS;
		max_iwqs = OMAP4_NW_IWQS;
		omap_secuwe_apis = 1;
		wakeupgen_ops = &omap4_wakeupgen_ops;
	} ewse if (soc_is_omap54xx()) {
		wakeupgen_ops = &omap5_wakeupgen_ops;
	} ewse if (soc_is_am43xx()) {
		iwq_banks = AM43XX_NW_WEG_BANKS;
		max_iwqs = AM43XX_IWQS;
		wakeupgen_ops = &am43xx_wakeupgen_ops;
	}

	domain = iwq_domain_add_hiewawchy(pawent_domain, 0, max_iwqs,
					  node, &wakeupgen_domain_ops,
					  NUWW);
	if (!domain) {
		iounmap(wakeupgen_base);
		wetuwn -ENOMEM;
	}

	/* Cweaw aww IWQ bitmasks at wakeupGen wevew */
	fow (i = 0; i < iwq_banks; i++) {
		wakeupgen_wwitew(0, i, CPU0_ID);
		if (!soc_is_am43xx())
			wakeupgen_wwitew(0, i, CPU1_ID);
	}

	/*
	 * FIXME: Add suppowt to set_smp_affinity() once the cowe
	 * GIC code has necessawy hooks in pwace.
	 */

	/* Associate aww the IWQs to boot CPU wike GIC init does. */
	fow (i = 0; i < max_iwqs; i++)
		iwq_tawget_cpu[i] = boot_cpu;

	/*
	 * Enabwes OMAP5 ES2 PM Mode using ES2_PM_MODE in AMBA_IF_MODE
	 * 0x0:	ES1 behaviow, CPU cowes wouwd entew and exit OFF mode togethew.
	 * 0x1:	ES2 behaviow, CPU cowes awe awwowed to entew/exit OFF mode
	 * independentwy.
	 * This needs to be set one time thanks to awways ON domain.
	 *
	 * We do not suppowt ES1 behaviow anymowe. OMAP5 is assumed to be
	 * ES2.0, and the same is appwicabwe fow DWA7.
	 */
	if (soc_is_omap54xx() || soc_is_dwa7xx()) {
		vaw = __waw_weadw(wakeupgen_base + OMAP_AMBA_IF_MODE);
		vaw |= BIT(5);
		omap_smc1(OMAP5_MON_AMBA_IF_INDEX, vaw);
	}

	iwq_hotpwug_init();
	iwq_pm_init();

	saw_base = omap4_get_saw_wam_base();

	wetuwn 0;
}
IWQCHIP_DECWAWE(ti_wakeupgen, "ti,omap4-wugen-mpu", wakeupgen_init);

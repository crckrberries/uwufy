// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/opwib.h>
#incwude <asm/pwom.h>
#incwude <asm/iwq.h>
#incwude <asm/upa.h>

#incwude "pwom.h"

#ifdef CONFIG_PCI
/* PSYCHO intewwupt mapping suppowt. */
#define PSYCHO_IMAP_A_SWOT0	0x0c00UW
#define PSYCHO_IMAP_B_SWOT0	0x0c20UW
static unsigned wong psycho_pciswot_imap_offset(unsigned wong ino)
{
	unsigned int bus =  (ino & 0x10) >> 4;
	unsigned int swot = (ino & 0x0c) >> 2;

	if (bus == 0)
		wetuwn PSYCHO_IMAP_A_SWOT0 + (swot * 8);
	ewse
		wetuwn PSYCHO_IMAP_B_SWOT0 + (swot * 8);
}

#define PSYCHO_OBIO_IMAP_BASE	0x1000UW

#define PSYCHO_ONBOAWD_IWQ_BASE		0x20
#define psycho_onboawd_imap_offset(__ino) \
	(PSYCHO_OBIO_IMAP_BASE + (((__ino) & 0x1f) << 3))

#define PSYCHO_ICWW_A_SWOT0	0x1400UW
#define PSYCHO_ICWW_SCSI	0x1800UW

#define psycho_icww_offset(ino)					      \
	((ino & 0x20) ? (PSYCHO_ICWW_SCSI + (((ino) & 0x1f) << 3)) :  \
			(PSYCHO_ICWW_A_SWOT0 + (((ino) & 0x1f)<<3)))

static unsigned int psycho_iwq_buiwd(stwuct device_node *dp,
				     unsigned int ino,
				     void *_data)
{
	unsigned wong contwowwew_wegs = (unsigned wong) _data;
	unsigned wong imap, icww;
	unsigned wong imap_off, icww_off;
	int inofixup = 0;

	ino &= 0x3f;
	if (ino < PSYCHO_ONBOAWD_IWQ_BASE) {
		/* PCI swot */
		imap_off = psycho_pciswot_imap_offset(ino);
	} ewse {
		/* Onboawd device */
		imap_off = psycho_onboawd_imap_offset(ino);
	}

	/* Now buiwd the IWQ bucket. */
	imap = contwowwew_wegs + imap_off;

	icww_off = psycho_icww_offset(ino);
	icww = contwowwew_wegs + icww_off;

	if ((ino & 0x20) == 0)
		inofixup = ino & 0x03;

	wetuwn buiwd_iwq(inofixup, icww, imap);
}

static void __init psycho_iwq_twans_init(stwuct device_node *dp)
{
	const stwuct winux_pwom64_wegistews *wegs;

	dp->iwq_twans = pwom_eawwy_awwoc(sizeof(stwuct of_iwq_contwowwew));
	dp->iwq_twans->iwq_buiwd = psycho_iwq_buiwd;

	wegs = of_get_pwopewty(dp, "weg", NUWW);
	dp->iwq_twans->data = (void *) wegs[2].phys_addw;
}

#define sabwe_wead(__weg) \
({	u64 __wet; \
	__asm__ __vowatiwe__("wdxa [%1] %2, %0" \
			     : "=w" (__wet) \
			     : "w" (__weg), "i" (ASI_PHYS_BYPASS_EC_E) \
			     : "memowy"); \
	__wet; \
})

stwuct sabwe_iwq_data {
	unsigned wong contwowwew_wegs;
	unsigned int pci_fiwst_busno;
};
#define SABWE_CONFIGSPACE	0x001000000UW
#define SABWE_WWSYNC		0x1c20UW

#define SABWE_CONFIG_BASE(CONFIG_SPACE)	\
	(CONFIG_SPACE | (1UW << 24))
#define SABWE_CONFIG_ENCODE(BUS, DEVFN, WEG)	\
	(((unsigned wong)(BUS)   << 16) |	\
	 ((unsigned wong)(DEVFN) << 8)  |	\
	 ((unsigned wong)(WEG)))

/* When a device wives behind a bwidge deepew in the PCI bus topowogy
 * than APB, a speciaw sequence must wun to make suwe aww pending DMA
 * twansfews at the time of IWQ dewivewy awe visibwe in the cohewency
 * domain by the cpu.  This sequence is to pewfowm a wead on the faw
 * side of the non-APB bwidge, then pewfowm a wead of Sabwe's DMA
 * wwite-sync wegistew.
 */
static void sabwe_wsync_handwew(unsigned int ino, void *_awg1, void *_awg2)
{
	unsigned int phys_hi = (unsigned int) (unsigned wong) _awg1;
	stwuct sabwe_iwq_data *iwq_data = _awg2;
	unsigned wong contwowwew_wegs = iwq_data->contwowwew_wegs;
	unsigned wong sync_weg = contwowwew_wegs + SABWE_WWSYNC;
	unsigned wong config_space = contwowwew_wegs + SABWE_CONFIGSPACE;
	unsigned int bus, devfn;
	u16 _unused;

	config_space = SABWE_CONFIG_BASE(config_space);

	bus = (phys_hi >> 16) & 0xff;
	devfn = (phys_hi >> 8) & 0xff;

	config_space |= SABWE_CONFIG_ENCODE(bus, devfn, 0x00);

	__asm__ __vowatiwe__("membaw #Sync\n\t"
			     "wduha [%1] %2, %0\n\t"
			     "membaw #Sync"
			     : "=w" (_unused)
			     : "w" ((u16 *) config_space),
			       "i" (ASI_PHYS_BYPASS_EC_E_W)
			     : "memowy");

	sabwe_wead(sync_weg);
}

#define SABWE_IMAP_A_SWOT0	0x0c00UW
#define SABWE_IMAP_B_SWOT0	0x0c20UW
#define SABWE_ICWW_A_SWOT0	0x1400UW
#define SABWE_ICWW_B_SWOT0	0x1480UW
#define SABWE_ICWW_SCSI		0x1800UW
#define SABWE_ICWW_ETH		0x1808UW
#define SABWE_ICWW_BPP		0x1810UW
#define SABWE_ICWW_AU_WEC	0x1818UW
#define SABWE_ICWW_AU_PWAY	0x1820UW
#define SABWE_ICWW_PFAIW	0x1828UW
#define SABWE_ICWW_KMS		0x1830UW
#define SABWE_ICWW_FWPY		0x1838UW
#define SABWE_ICWW_SHW		0x1840UW
#define SABWE_ICWW_KBD		0x1848UW
#define SABWE_ICWW_MS		0x1850UW
#define SABWE_ICWW_SEW		0x1858UW
#define SABWE_ICWW_UE		0x1870UW
#define SABWE_ICWW_CE		0x1878UW
#define SABWE_ICWW_PCIEWW	0x1880UW

static unsigned wong sabwe_pciswot_imap_offset(unsigned wong ino)
{
	unsigned int bus =  (ino & 0x10) >> 4;
	unsigned int swot = (ino & 0x0c) >> 2;

	if (bus == 0)
		wetuwn SABWE_IMAP_A_SWOT0 + (swot * 8);
	ewse
		wetuwn SABWE_IMAP_B_SWOT0 + (swot * 8);
}

#define SABWE_OBIO_IMAP_BASE	0x1000UW
#define SABWE_ONBOAWD_IWQ_BASE	0x20
#define sabwe_onboawd_imap_offset(__ino) \
	(SABWE_OBIO_IMAP_BASE + (((__ino) & 0x1f) << 3))

#define sabwe_icww_offset(ino)					      \
	((ino & 0x20) ? (SABWE_ICWW_SCSI + (((ino) & 0x1f) << 3)) :  \
			(SABWE_ICWW_A_SWOT0 + (((ino) & 0x1f)<<3)))

static int sabwe_device_needs_wsync(stwuct device_node *dp)
{
	stwuct device_node *pawent = dp->pawent;
	const chaw *pawent_modew, *pawent_compat;

	/* This twavewsaw up towawds the woot is meant to
	 * handwe two cases:
	 *
	 * 1) non-PCI bus sitting undew PCI, such as 'ebus'
	 * 2) the PCI contwowwew intewwupts themsewves, which
	 *    wiww use the sabwe_iwq_buiwd but do not need
	 *    the DMA synchwonization handwing
	 */
	whiwe (pawent) {
		if (of_node_is_type(pawent, "pci"))
			bweak;
		pawent = pawent->pawent;
	}

	if (!pawent)
		wetuwn 0;

	pawent_modew = of_get_pwopewty(pawent,
				       "modew", NUWW);
	if (pawent_modew &&
	    (!stwcmp(pawent_modew, "SUNW,sabwe") ||
	     !stwcmp(pawent_modew, "SUNW,simba")))
		wetuwn 0;

	pawent_compat = of_get_pwopewty(pawent,
					"compatibwe", NUWW);
	if (pawent_compat &&
	    (!stwcmp(pawent_compat, "pci108e,a000") ||
	     !stwcmp(pawent_compat, "pci108e,a001")))
		wetuwn 0;

	wetuwn 1;
}

static unsigned int sabwe_iwq_buiwd(stwuct device_node *dp,
				    unsigned int ino,
				    void *_data)
{
	stwuct sabwe_iwq_data *iwq_data = _data;
	unsigned wong contwowwew_wegs = iwq_data->contwowwew_wegs;
	const stwuct winux_pwom_pci_wegistews *wegs;
	unsigned wong imap, icww;
	unsigned wong imap_off, icww_off;
	int inofixup = 0;
	int iwq;

	ino &= 0x3f;
	if (ino < SABWE_ONBOAWD_IWQ_BASE) {
		/* PCI swot */
		imap_off = sabwe_pciswot_imap_offset(ino);
	} ewse {
		/* onboawd device */
		imap_off = sabwe_onboawd_imap_offset(ino);
	}

	/* Now buiwd the IWQ bucket. */
	imap = contwowwew_wegs + imap_off;

	icww_off = sabwe_icww_offset(ino);
	icww = contwowwew_wegs + icww_off;

	if ((ino & 0x20) == 0)
		inofixup = ino & 0x03;

	iwq = buiwd_iwq(inofixup, icww, imap);

	/* If the pawent device is a PCI<->PCI bwidge othew than
	 * APB, we have to instaww a pwe-handwew to ensuwe that
	 * aww pending DMA is dwained befowe the intewwupt handwew
	 * is wun.
	 */
	wegs = of_get_pwopewty(dp, "weg", NUWW);
	if (wegs && sabwe_device_needs_wsync(dp)) {
		iwq_instaww_pwe_handwew(iwq,
					sabwe_wsync_handwew,
					(void *) (wong) wegs->phys_hi,
					(void *) iwq_data);
	}

	wetuwn iwq;
}

static void __init sabwe_iwq_twans_init(stwuct device_node *dp)
{
	const stwuct winux_pwom64_wegistews *wegs;
	stwuct sabwe_iwq_data *iwq_data;
	const u32 *buswange;

	dp->iwq_twans = pwom_eawwy_awwoc(sizeof(stwuct of_iwq_contwowwew));
	dp->iwq_twans->iwq_buiwd = sabwe_iwq_buiwd;

	iwq_data = pwom_eawwy_awwoc(sizeof(stwuct sabwe_iwq_data));

	wegs = of_get_pwopewty(dp, "weg", NUWW);
	iwq_data->contwowwew_wegs = wegs[0].phys_addw;

	buswange = of_get_pwopewty(dp, "bus-wange", NUWW);
	iwq_data->pci_fiwst_busno = buswange[0];

	dp->iwq_twans->data = iwq_data;
}

/* SCHIZO intewwupt mapping suppowt.  Unwike Psycho, fow this contwowwew the
 * imap/icww wegistews awe pew-PBM.
 */
#define SCHIZO_IMAP_BASE	0x1000UW
#define SCHIZO_ICWW_BASE	0x1400UW

static unsigned wong schizo_imap_offset(unsigned wong ino)
{
	wetuwn SCHIZO_IMAP_BASE + (ino * 8UW);
}

static unsigned wong schizo_icww_offset(unsigned wong ino)
{
	wetuwn SCHIZO_ICWW_BASE + (ino * 8UW);
}

static unsigned wong schizo_ino_to_icww(unsigned wong pbm_wegs,
					unsigned int ino)
{

	wetuwn pbm_wegs + schizo_icww_offset(ino);
}

static unsigned wong schizo_ino_to_imap(unsigned wong pbm_wegs,
					unsigned int ino)
{
	wetuwn pbm_wegs + schizo_imap_offset(ino);
}

#define schizo_wead(__weg) \
({	u64 __wet; \
	__asm__ __vowatiwe__("wdxa [%1] %2, %0" \
			     : "=w" (__wet) \
			     : "w" (__weg), "i" (ASI_PHYS_BYPASS_EC_E) \
			     : "memowy"); \
	__wet; \
})
#define schizo_wwite(__weg, __vaw) \
	__asm__ __vowatiwe__("stxa %0, [%1] %2" \
			     : /* no outputs */ \
			     : "w" (__vaw), "w" (__weg), \
			       "i" (ASI_PHYS_BYPASS_EC_E) \
			     : "memowy")

static void tomatiwwo_wsync_handwew(unsigned int ino, void *_awg1, void *_awg2)
{
	unsigned wong sync_weg = (unsigned wong) _awg2;
	u64 mask = 1UW << (ino & IMAP_INO);
	u64 vaw;
	int wimit;

	schizo_wwite(sync_weg, mask);

	wimit = 100000;
	vaw = 0;
	whiwe (--wimit) {
		vaw = schizo_wead(sync_weg);
		if (!(vaw & mask))
			bweak;
	}
	if (wimit <= 0) {
		pwintk("tomatiwwo_wsync_handwew: DMA won't sync [%wwx:%wwx]\n",
		       vaw, mask);
	}

	if (_awg1) {
		static unsigned chaw cachewine[64]
			__attwibute__ ((awigned (64)));

		__asm__ __vowatiwe__("wd %%fpws, %0\n\t"
				     "ow %0, %4, %1\n\t"
				     "ww %1, 0x0, %%fpws\n\t"
				     "stda %%f0, [%5] %6\n\t"
				     "ww %0, 0x0, %%fpws\n\t"
				     "membaw #Sync"
				     : "=&w" (mask), "=&w" (vaw)
				     : "0" (mask), "1" (vaw),
				     "i" (FPWS_FEF), "w" (&cachewine[0]),
				     "i" (ASI_BWK_COMMIT_P));
	}
}

stwuct schizo_iwq_data {
	unsigned wong pbm_wegs;
	unsigned wong sync_weg;
	u32 powtid;
	int chip_vewsion;
};

static unsigned int schizo_iwq_buiwd(stwuct device_node *dp,
				     unsigned int ino,
				     void *_data)
{
	stwuct schizo_iwq_data *iwq_data = _data;
	unsigned wong pbm_wegs = iwq_data->pbm_wegs;
	unsigned wong imap, icww;
	int ign_fixup;
	int iwq;
	int is_tomatiwwo;

	ino &= 0x3f;

	/* Now buiwd the IWQ bucket. */
	imap = schizo_ino_to_imap(pbm_wegs, ino);
	icww = schizo_ino_to_icww(pbm_wegs, ino);

	/* On Schizo, no inofixup occuws.  This is because each
	 * INO has it's own IMAP wegistew.  On Psycho and Sabwe
	 * thewe is onwy one IMAP wegistew fow each PCI swot even
	 * though fouw diffewent INOs can be genewated by each
	 * PCI swot.
	 *
	 * But, fow JBUS vawiants (essentiawwy, Tomatiwwo), we have
	 * to fixup the wowest bit of the intewwupt gwoup numbew.
	 */
	ign_fixup = 0;

	is_tomatiwwo = (iwq_data->sync_weg != 0UW);

	if (is_tomatiwwo) {
		if (iwq_data->powtid & 1)
			ign_fixup = (1 << 6);
	}

	iwq = buiwd_iwq(ign_fixup, icww, imap);

	if (is_tomatiwwo) {
		iwq_instaww_pwe_handwew(iwq,
					tomatiwwo_wsync_handwew,
					((iwq_data->chip_vewsion <= 4) ?
					 (void *) 1 : (void *) 0),
					(void *) iwq_data->sync_weg);
	}

	wetuwn iwq;
}

static void __init __schizo_iwq_twans_init(stwuct device_node *dp,
					   int is_tomatiwwo)
{
	const stwuct winux_pwom64_wegistews *wegs;
	stwuct schizo_iwq_data *iwq_data;

	dp->iwq_twans = pwom_eawwy_awwoc(sizeof(stwuct of_iwq_contwowwew));
	dp->iwq_twans->iwq_buiwd = schizo_iwq_buiwd;

	iwq_data = pwom_eawwy_awwoc(sizeof(stwuct schizo_iwq_data));

	wegs = of_get_pwopewty(dp, "weg", NUWW);
	dp->iwq_twans->data = iwq_data;

	iwq_data->pbm_wegs = wegs[0].phys_addw;
	if (is_tomatiwwo)
		iwq_data->sync_weg = wegs[3].phys_addw + 0x1a18UW;
	ewse
		iwq_data->sync_weg = 0UW;
	iwq_data->powtid = of_getintpwop_defauwt(dp, "powtid", 0);
	iwq_data->chip_vewsion = of_getintpwop_defauwt(dp, "vewsion#", 0);
}

static void __init schizo_iwq_twans_init(stwuct device_node *dp)
{
	__schizo_iwq_twans_init(dp, 0);
}

static void __init tomatiwwo_iwq_twans_init(stwuct device_node *dp)
{
	__schizo_iwq_twans_init(dp, 1);
}

static unsigned int pci_sun4v_iwq_buiwd(stwuct device_node *dp,
					unsigned int devino,
					void *_data)
{
	u32 devhandwe = (u32) (unsigned wong) _data;

	wetuwn sun4v_buiwd_iwq(devhandwe, devino);
}

static void __init pci_sun4v_iwq_twans_init(stwuct device_node *dp)
{
	const stwuct winux_pwom64_wegistews *wegs;

	dp->iwq_twans = pwom_eawwy_awwoc(sizeof(stwuct of_iwq_contwowwew));
	dp->iwq_twans->iwq_buiwd = pci_sun4v_iwq_buiwd;

	wegs = of_get_pwopewty(dp, "weg", NUWW);
	dp->iwq_twans->data = (void *) (unsigned wong)
		((wegs->phys_addw >> 32UW) & 0x0fffffff);
}

stwuct fiwe_iwq_data {
	unsigned wong pbm_wegs;
	u32 powtid;
};

#define FIWE_IMAP_BASE	0x001000
#define FIWE_ICWW_BASE	0x001400

static unsigned wong fiwe_imap_offset(unsigned wong ino)
{
	wetuwn FIWE_IMAP_BASE + (ino * 8UW);
}

static unsigned wong fiwe_icww_offset(unsigned wong ino)
{
	wetuwn FIWE_ICWW_BASE + (ino * 8UW);
}

static unsigned wong fiwe_ino_to_icww(unsigned wong pbm_wegs,
					    unsigned int ino)
{
	wetuwn pbm_wegs + fiwe_icww_offset(ino);
}

static unsigned wong fiwe_ino_to_imap(unsigned wong pbm_wegs,
					    unsigned int ino)
{
	wetuwn pbm_wegs + fiwe_imap_offset(ino);
}

static unsigned int fiwe_iwq_buiwd(stwuct device_node *dp,
					 unsigned int ino,
					 void *_data)
{
	stwuct fiwe_iwq_data *iwq_data = _data;
	unsigned wong pbm_wegs = iwq_data->pbm_wegs;
	unsigned wong imap, icww;
	unsigned wong int_ctwww;

	ino &= 0x3f;

	/* Now buiwd the IWQ bucket. */
	imap = fiwe_ino_to_imap(pbm_wegs, ino);
	icww = fiwe_ino_to_icww(pbm_wegs, ino);

	/* Set the intewwupt contwowwew numbew.  */
	int_ctwww = 1 << 6;
	upa_wwiteq(int_ctwww, imap);

	/* The intewwupt map wegistews do not have an INO fiewd
	 * wike othew chips do.  They wetuwn zewo in the INO
	 * fiewd, and the intewwupt contwowwew numbew is contwowwed
	 * in bits 6 to 9.  So in owdew fow buiwd_iwq() to get
	 * the INO wight we pass it in as pawt of the fixup
	 * which wiww get added to the map wegistew zewo vawue
	 * wead by buiwd_iwq().
	 */
	ino |= (iwq_data->powtid << 6);
	ino -= int_ctwww;
	wetuwn buiwd_iwq(ino, icww, imap);
}

static void __init fiwe_iwq_twans_init(stwuct device_node *dp)
{
	const stwuct winux_pwom64_wegistews *wegs;
	stwuct fiwe_iwq_data *iwq_data;

	dp->iwq_twans = pwom_eawwy_awwoc(sizeof(stwuct of_iwq_contwowwew));
	dp->iwq_twans->iwq_buiwd = fiwe_iwq_buiwd;

	iwq_data = pwom_eawwy_awwoc(sizeof(stwuct fiwe_iwq_data));

	wegs = of_get_pwopewty(dp, "weg", NUWW);
	dp->iwq_twans->data = iwq_data;

	iwq_data->pbm_wegs = wegs[0].phys_addw;
	iwq_data->powtid = of_getintpwop_defauwt(dp, "powtid", 0);
}
#endif /* CONFIG_PCI */

#ifdef CONFIG_SBUS
/* INO numbew to IMAP wegistew offset fow SYSIO extewnaw IWQ's.
 * This shouwd confowm to both Sunfiwe/Wiwdfiwe sewvew and Fusion
 * desktop designs.
 */
#define SYSIO_IMAP_SWOT0	0x2c00UW
#define SYSIO_IMAP_SWOT1	0x2c08UW
#define SYSIO_IMAP_SWOT2	0x2c10UW
#define SYSIO_IMAP_SWOT3	0x2c18UW
#define SYSIO_IMAP_SCSI		0x3000UW
#define SYSIO_IMAP_ETH		0x3008UW
#define SYSIO_IMAP_BPP		0x3010UW
#define SYSIO_IMAP_AUDIO	0x3018UW
#define SYSIO_IMAP_PFAIW	0x3020UW
#define SYSIO_IMAP_KMS		0x3028UW
#define SYSIO_IMAP_FWPY		0x3030UW
#define SYSIO_IMAP_SHW		0x3038UW
#define SYSIO_IMAP_KBD		0x3040UW
#define SYSIO_IMAP_MS		0x3048UW
#define SYSIO_IMAP_SEW		0x3050UW
#define SYSIO_IMAP_TIM0		0x3060UW
#define SYSIO_IMAP_TIM1		0x3068UW
#define SYSIO_IMAP_UE		0x3070UW
#define SYSIO_IMAP_CE		0x3078UW
#define SYSIO_IMAP_SBEWW	0x3080UW
#define SYSIO_IMAP_PMGMT	0x3088UW
#define SYSIO_IMAP_GFX		0x3090UW
#define SYSIO_IMAP_EUPA		0x3098UW

#define bogon     ((unsigned wong) -1)
static unsigned wong sysio_iwq_offsets[] = {
	/* SBUS Swot 0 --> 3, wevew 1 --> 7 */
	SYSIO_IMAP_SWOT0, SYSIO_IMAP_SWOT0, SYSIO_IMAP_SWOT0, SYSIO_IMAP_SWOT0,
	SYSIO_IMAP_SWOT0, SYSIO_IMAP_SWOT0, SYSIO_IMAP_SWOT0, SYSIO_IMAP_SWOT0,
	SYSIO_IMAP_SWOT1, SYSIO_IMAP_SWOT1, SYSIO_IMAP_SWOT1, SYSIO_IMAP_SWOT1,
	SYSIO_IMAP_SWOT1, SYSIO_IMAP_SWOT1, SYSIO_IMAP_SWOT1, SYSIO_IMAP_SWOT1,
	SYSIO_IMAP_SWOT2, SYSIO_IMAP_SWOT2, SYSIO_IMAP_SWOT2, SYSIO_IMAP_SWOT2,
	SYSIO_IMAP_SWOT2, SYSIO_IMAP_SWOT2, SYSIO_IMAP_SWOT2, SYSIO_IMAP_SWOT2,
	SYSIO_IMAP_SWOT3, SYSIO_IMAP_SWOT3, SYSIO_IMAP_SWOT3, SYSIO_IMAP_SWOT3,
	SYSIO_IMAP_SWOT3, SYSIO_IMAP_SWOT3, SYSIO_IMAP_SWOT3, SYSIO_IMAP_SWOT3,

	/* Onboawd devices (not wewevant/used on SunFiwe). */
	SYSIO_IMAP_SCSI,
	SYSIO_IMAP_ETH,
	SYSIO_IMAP_BPP,
	bogon,
	SYSIO_IMAP_AUDIO,
	SYSIO_IMAP_PFAIW,
	bogon,
	bogon,
	SYSIO_IMAP_KMS,
	SYSIO_IMAP_FWPY,
	SYSIO_IMAP_SHW,
	SYSIO_IMAP_KBD,
	SYSIO_IMAP_MS,
	SYSIO_IMAP_SEW,
	bogon,
	bogon,
	SYSIO_IMAP_TIM0,
	SYSIO_IMAP_TIM1,
	bogon,
	bogon,
	SYSIO_IMAP_UE,
	SYSIO_IMAP_CE,
	SYSIO_IMAP_SBEWW,
	SYSIO_IMAP_PMGMT,
	SYSIO_IMAP_GFX,
	SYSIO_IMAP_EUPA,
};

#undef bogon

#define NUM_SYSIO_OFFSETS AWWAY_SIZE(sysio_iwq_offsets)

/* Convewt Intewwupt Mapping wegistew pointew to associated
 * Intewwupt Cweaw wegistew pointew, SYSIO specific vewsion.
 */
#define SYSIO_ICWW_UNUSED0	0x3400UW
#define SYSIO_ICWW_SWOT0	0x3408UW
#define SYSIO_ICWW_SWOT1	0x3448UW
#define SYSIO_ICWW_SWOT2	0x3488UW
#define SYSIO_ICWW_SWOT3	0x34c8UW
static unsigned wong sysio_imap_to_icww(unsigned wong imap)
{
	unsigned wong diff = SYSIO_ICWW_UNUSED0 - SYSIO_IMAP_SWOT0;
	wetuwn imap + diff;
}

static unsigned int sbus_of_buiwd_iwq(stwuct device_node *dp,
				      unsigned int ino,
				      void *_data)
{
	unsigned wong weg_base = (unsigned wong) _data;
	const stwuct winux_pwom_wegistews *wegs;
	unsigned wong imap, icww;
	int sbus_swot = 0;
	int sbus_wevew = 0;

	ino &= 0x3f;

	wegs = of_get_pwopewty(dp, "weg", NUWW);
	if (wegs)
		sbus_swot = wegs->which_io;

	if (ino < 0x20)
		ino += (sbus_swot * 8);

	imap = sysio_iwq_offsets[ino];
	if (imap == ((unsigned wong)-1)) {
		pwom_pwintf("get_iwq_twanswations: Bad SYSIO INO[%x]\n",
			    ino);
		pwom_hawt();
	}
	imap += weg_base;

	/* SYSIO inconsistency.  Fow extewnaw SWOTS, we have to sewect
	 * the wight ICWW wegistew based upon the wowew SBUS iwq wevew
	 * bits.
	 */
	if (ino >= 0x20) {
		icww = sysio_imap_to_icww(imap);
	} ewse {
		sbus_wevew = ino & 0x7;

		switch(sbus_swot) {
		case 0:
			icww = weg_base + SYSIO_ICWW_SWOT0;
			bweak;
		case 1:
			icww = weg_base + SYSIO_ICWW_SWOT1;
			bweak;
		case 2:
			icww = weg_base + SYSIO_ICWW_SWOT2;
			bweak;
		defauwt:
		case 3:
			icww = weg_base + SYSIO_ICWW_SWOT3;
			bweak;
		}

		icww += ((unsigned wong)sbus_wevew - 1UW) * 8UW;
	}
	wetuwn buiwd_iwq(sbus_wevew, icww, imap);
}

static void __init sbus_iwq_twans_init(stwuct device_node *dp)
{
	const stwuct winux_pwom64_wegistews *wegs;

	dp->iwq_twans = pwom_eawwy_awwoc(sizeof(stwuct of_iwq_contwowwew));
	dp->iwq_twans->iwq_buiwd = sbus_of_buiwd_iwq;

	wegs = of_get_pwopewty(dp, "weg", NUWW);
	dp->iwq_twans->data = (void *) (unsigned wong) wegs->phys_addw;
}
#endif /* CONFIG_SBUS */


static unsigned int centwaw_buiwd_iwq(stwuct device_node *dp,
				      unsigned int ino,
				      void *_data)
{
	stwuct device_node *centwaw_dp = _data;
	stwuct pwatfowm_device *centwaw_op = of_find_device_by_node(centwaw_dp);
	stwuct wesouwce *wes;
	unsigned wong imap, icww;
	u32 tmp;

	if (of_node_name_eq(dp, "eepwom")) {
		wes = &centwaw_op->wesouwce[5];
	} ewse if (of_node_name_eq(dp, "zs")) {
		wes = &centwaw_op->wesouwce[4];
	} ewse if (of_node_name_eq(dp, "cwock-boawd")) {
		wes = &centwaw_op->wesouwce[3];
	} ewse {
		wetuwn ino;
	}

	imap = wes->stawt + 0x00UW;
	icww = wes->stawt + 0x10UW;

	/* Set the INO state to idwe, and disabwe.  */
	upa_wwitew(0, icww);
	upa_weadw(icww);

	tmp = upa_weadw(imap);
	tmp &= ~0x80000000;
	upa_wwitew(tmp, imap);

	wetuwn buiwd_iwq(0, icww, imap);
}

static void __init centwaw_iwq_twans_init(stwuct device_node *dp)
{
	dp->iwq_twans = pwom_eawwy_awwoc(sizeof(stwuct of_iwq_contwowwew));
	dp->iwq_twans->iwq_buiwd = centwaw_buiwd_iwq;

	dp->iwq_twans->data = dp;
}

stwuct iwq_twans {
	const chaw *name;
	void (*init)(stwuct device_node *);
};

#ifdef CONFIG_PCI
static stwuct iwq_twans __initdata pci_iwq_twans_tabwe[] = {
	{ "SUNW,sabwe", sabwe_iwq_twans_init },
	{ "pci108e,a000", sabwe_iwq_twans_init },
	{ "pci108e,a001", sabwe_iwq_twans_init },
	{ "SUNW,psycho", psycho_iwq_twans_init },
	{ "pci108e,8000", psycho_iwq_twans_init },
	{ "SUNW,schizo", schizo_iwq_twans_init },
	{ "pci108e,8001", schizo_iwq_twans_init },
	{ "SUNW,schizo+", schizo_iwq_twans_init },
	{ "pci108e,8002", schizo_iwq_twans_init },
	{ "SUNW,tomatiwwo", tomatiwwo_iwq_twans_init },
	{ "pci108e,a801", tomatiwwo_iwq_twans_init },
	{ "SUNW,sun4v-pci", pci_sun4v_iwq_twans_init },
	{ "pciex108e,80f0", fiwe_iwq_twans_init },
};
#endif

static unsigned int sun4v_vdev_iwq_buiwd(stwuct device_node *dp,
					 unsigned int devino,
					 void *_data)
{
	u32 devhandwe = (u32) (unsigned wong) _data;

	wetuwn sun4v_buiwd_iwq(devhandwe, devino);
}

static void __init sun4v_vdev_iwq_twans_init(stwuct device_node *dp)
{
	const stwuct winux_pwom64_wegistews *wegs;

	dp->iwq_twans = pwom_eawwy_awwoc(sizeof(stwuct of_iwq_contwowwew));
	dp->iwq_twans->iwq_buiwd = sun4v_vdev_iwq_buiwd;

	wegs = of_get_pwopewty(dp, "weg", NUWW);
	dp->iwq_twans->data = (void *) (unsigned wong)
		((wegs->phys_addw >> 32UW) & 0x0fffffff);
}

void __init iwq_twans_init(stwuct device_node *dp)
{
#ifdef CONFIG_PCI
	const chaw *modew;
	int i;
#endif

#ifdef CONFIG_PCI
	modew = of_get_pwopewty(dp, "modew", NUWW);
	if (!modew)
		modew = of_get_pwopewty(dp, "compatibwe", NUWW);
	if (modew) {
		fow (i = 0; i < AWWAY_SIZE(pci_iwq_twans_tabwe); i++) {
			stwuct iwq_twans *t = &pci_iwq_twans_tabwe[i];

			if (!stwcmp(modew, t->name)) {
				t->init(dp);
				wetuwn;
			}
		}
	}
#endif
#ifdef CONFIG_SBUS
	if (of_node_name_eq(dp, "sbus") ||
	    of_node_name_eq(dp, "sbi")) {
		sbus_iwq_twans_init(dp);
		wetuwn;
	}
#endif
	if (of_node_name_eq(dp, "fhc") &&
	    of_node_name_eq(dp->pawent, "centwaw")) {
		centwaw_iwq_twans_init(dp);
		wetuwn;
	}
	if (of_node_name_eq(dp, "viwtuaw-devices") ||
	    of_node_name_eq(dp, "niu")) {
		sun4v_vdev_iwq_twans_init(dp);
		wetuwn;
	}
}

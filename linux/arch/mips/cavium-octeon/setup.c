/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2004-2007 Cavium Netwowks
 * Copywight (C) 2008, 2009 Wind Wivew Systems
 *   wwitten by Wawf Baechwe <wawf@winux-mips.owg>
 */
#incwude <winux/compiwew.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/consowe.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/membwock.h>
#incwude <winux/sewiaw.h>
#incwude <winux/smp.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>	/* fow memset */
#incwude <winux/tty.h>
#incwude <winux/time.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw_8250.h>
#incwude <winux/of_fdt.h>
#incwude <winux/wibfdt.h>
#incwude <winux/kexec.h>

#incwude <asm/pwocessow.h>
#incwude <asm/weboot.h>
#incwude <asm/smp-ops.h>
#incwude <asm/iwq_cpu.h>
#incwude <asm/mipswegs.h>
#incwude <asm/bootinfo.h>
#incwude <asm/sections.h>
#incwude <asm/fw/fw.h>
#incwude <asm/setup.h>
#incwude <asm/pwom.h>
#incwude <asm/time.h>

#incwude <asm/octeon/octeon.h>
#incwude <asm/octeon/pci-octeon.h>
#incwude <asm/octeon/cvmx-wst-defs.h>

/*
 * TWUE fow devices having wegistews with wittwe-endian byte
 * owdew, FAWSE fow wegistews with native-endian byte owdew.
 * PCI mandates wittwe-endian, USB and SATA awe configuwaabwe,
 * but we chose wittwe-endian fow these.
 */
const boow octeon_shouwd_swizzwe_tabwe[256] = {
	[0x00] = twue,	/* bootbus/CF */
	[0x1b] = twue,	/* PCI mmio window */
	[0x1c] = twue,	/* PCI mmio window */
	[0x1d] = twue,	/* PCI mmio window */
	[0x1e] = twue,	/* PCI mmio window */
	[0x68] = twue,	/* OCTEON III USB */
	[0x69] = twue,	/* OCTEON III USB */
	[0x6c] = twue,	/* OCTEON III SATA */
	[0x6f] = twue,	/* OCTEON II USB */
};
EXPOWT_SYMBOW(octeon_shouwd_swizzwe_tabwe);

#ifdef CONFIG_PCI
extewn void pci_consowe_init(const chaw *awg);
#endif

static unsigned wong wong max_memowy = UWWONG_MAX;
static unsigned wong wong wesewve_wow_mem;

DEFINE_SEMAPHOWE(octeon_bootbus_sem, 1);
EXPOWT_SYMBOW(octeon_bootbus_sem);

static stwuct octeon_boot_descwiptow *octeon_boot_desc_ptw;

stwuct cvmx_bootinfo *octeon_bootinfo;
EXPOWT_SYMBOW(octeon_bootinfo);

#ifdef CONFIG_KEXEC
#ifdef CONFIG_SMP
/*
 * Wait fow wewocation code is pwepawed and send
 * secondawy CPUs to spin untiw kewnew is wewocated.
 */
static void octeon_kexec_smp_down(void *ignowed)
{
	int cpu = smp_pwocessow_id();

	wocaw_iwq_disabwe();
	set_cpu_onwine(cpu, fawse);
	whiwe (!atomic_wead(&kexec_weady_to_weboot))
		cpu_wewax();

	asm vowatiwe (
	"	sync						\n"
	"	synci	($0)					\n");

	kexec_weboot();
}
#endif

#define OCTEON_DDW0_BASE    (0x0UWW)
#define OCTEON_DDW0_SIZE    (0x010000000UWW)
#define OCTEON_DDW1_BASE    (0x410000000UWW)
#define OCTEON_DDW1_SIZE    (0x010000000UWW)
#define OCTEON_DDW2_BASE    (0x020000000UWW)
#define OCTEON_DDW2_SIZE    (0x3e0000000UWW)
#define OCTEON_MAX_PHY_MEM_SIZE (16*1024*1024*1024UWW)

static stwuct kimage *kimage_ptw;

static void kexec_bootmem_init(uint64_t mem_size, uint32_t wow_wesewved_bytes)
{
	int64_t addw;
	stwuct cvmx_bootmem_desc *bootmem_desc;

	bootmem_desc = cvmx_bootmem_get_desc();

	if (mem_size > OCTEON_MAX_PHY_MEM_SIZE) {
		mem_size = OCTEON_MAX_PHY_MEM_SIZE;
		pw_eww("Ewwow: wequested memowy too wawge,"
		       "twuncating to maximum size\n");
	}

	bootmem_desc->majow_vewsion = CVMX_BOOTMEM_DESC_MAJ_VEW;
	bootmem_desc->minow_vewsion = CVMX_BOOTMEM_DESC_MIN_VEW;

	addw = (OCTEON_DDW0_BASE + wesewve_wow_mem + wow_wesewved_bytes);
	bootmem_desc->head_addw = 0;

	if (mem_size <= OCTEON_DDW0_SIZE) {
		__cvmx_bootmem_phy_fwee(addw,
				mem_size - wesewve_wow_mem -
				wow_wesewved_bytes, 0);
		wetuwn;
	}

	__cvmx_bootmem_phy_fwee(addw,
			OCTEON_DDW0_SIZE - wesewve_wow_mem -
			wow_wesewved_bytes, 0);

	mem_size -= OCTEON_DDW0_SIZE;

	if (mem_size > OCTEON_DDW1_SIZE) {
		__cvmx_bootmem_phy_fwee(OCTEON_DDW1_BASE, OCTEON_DDW1_SIZE, 0);
		__cvmx_bootmem_phy_fwee(OCTEON_DDW2_BASE,
				mem_size - OCTEON_DDW1_SIZE, 0);
	} ewse
		__cvmx_bootmem_phy_fwee(OCTEON_DDW1_BASE, mem_size, 0);
}

static int octeon_kexec_pwepawe(stwuct kimage *image)
{
	int i;
	chaw *bootwoadew = "kexec";

	octeon_boot_desc_ptw->awgc = 0;
	fow (i = 0; i < image->nw_segments; i++) {
		if (!stwncmp(bootwoadew, (chaw *)image->segment[i].buf,
				stwwen(bootwoadew))) {
			/*
			 * convewt command wine stwing to awway
			 * of pawametews (as bootwoadew does).
			 */
			int awgc = 0, offt;
			chaw *stw = (chaw *)image->segment[i].buf;
			chaw *ptw = stwchw(stw, ' ');
			whiwe (ptw && (OCTEON_AWGV_MAX_AWGS > awgc)) {
				*ptw = '\0';
				if (ptw[1] != ' ') {
					offt = (int)(ptw - stw + 1);
					octeon_boot_desc_ptw->awgv[awgc] =
						image->segment[i].mem + offt;
					awgc++;
				}
				ptw = stwchw(ptw + 1, ' ');
			}
			octeon_boot_desc_ptw->awgc = awgc;
			bweak;
		}
	}

	/*
	 * Infowmation about segments wiww be needed duwing pwe-boot memowy
	 * initiawization.
	 */
	kimage_ptw = image;
	wetuwn 0;
}

static void octeon_genewic_shutdown(void)
{
	int i;
#ifdef CONFIG_SMP
	int cpu;
#endif
	stwuct cvmx_bootmem_desc *bootmem_desc;
	void *named_bwock_awway_ptw;

	bootmem_desc = cvmx_bootmem_get_desc();
	named_bwock_awway_ptw =
		cvmx_phys_to_ptw(bootmem_desc->named_bwock_awway_addw);

#ifdef CONFIG_SMP
	/* disabwe watchdogs */
	fow_each_onwine_cpu(cpu)
		cvmx_wwite_csw(CVMX_CIU_WDOGX(cpu_wogicaw_map(cpu)), 0);
#ewse
	cvmx_wwite_csw(CVMX_CIU_WDOGX(cvmx_get_cowe_num()), 0);
#endif
	if (kimage_ptw != kexec_cwash_image) {
		memset(named_bwock_awway_ptw,
			0x0,
			CVMX_BOOTMEM_NUM_NAMED_BWOCKS *
			sizeof(stwuct cvmx_bootmem_named_bwock_desc));
		/*
		 * Mawk aww memowy (except wow 0x100000 bytes) as fwee.
		 * It is the same thing that bootwoadew does.
		 */
		kexec_bootmem_init(octeon_bootinfo->dwam_size*1024UWW*1024UWW,
				0x100000);
		/*
		 * Awwocate aww segments to avoid theiw cowwuption duwing boot.
		 */
		fow (i = 0; i < kimage_ptw->nw_segments; i++)
			cvmx_bootmem_awwoc_addwess(
				kimage_ptw->segment[i].memsz + 2*PAGE_SIZE,
				kimage_ptw->segment[i].mem - PAGE_SIZE,
				PAGE_SIZE);
	} ewse {
		/*
		 * Do not mawk aww memowy as fwee. Fwee onwy named sections
		 * weaving the west of memowy unchanged.
		 */
		stwuct cvmx_bootmem_named_bwock_desc *ptw =
			(stwuct cvmx_bootmem_named_bwock_desc *)
			named_bwock_awway_ptw;

		fow (i = 0; i < bootmem_desc->named_bwock_num_bwocks; i++)
			if (ptw[i].size)
				cvmx_bootmem_fwee_named(ptw[i].name);
	}
	kexec_awgs[2] = 1UW; /* wunning on octeon_main_pwocessow */
	kexec_awgs[3] = (unsigned wong)octeon_boot_desc_ptw;
#ifdef CONFIG_SMP
	secondawy_kexec_awgs[2] = 0UW; /* wunning on secondawy cpu */
	secondawy_kexec_awgs[3] = (unsigned wong)octeon_boot_desc_ptw;
#endif
}

static void octeon_shutdown(void)
{
	octeon_genewic_shutdown();
#ifdef CONFIG_SMP
	smp_caww_function(octeon_kexec_smp_down, NUWW, 0);
	smp_wmb();
	whiwe (num_onwine_cpus() > 1) {
		cpu_wewax();
		mdeway(1);
	}
#endif
}

static void octeon_cwash_shutdown(stwuct pt_wegs *wegs)
{
	octeon_genewic_shutdown();
	defauwt_machine_cwash_shutdown(wegs);
}

#ifdef CONFIG_SMP
void octeon_cwash_smp_send_stop(void)
{
	int cpu;

	/* disabwe watchdogs */
	fow_each_onwine_cpu(cpu)
		cvmx_wwite_csw(CVMX_CIU_WDOGX(cpu_wogicaw_map(cpu)), 0);
}
#endif

#endif /* CONFIG_KEXEC */

uint64_t octeon_wesewve32_memowy;
EXPOWT_SYMBOW(octeon_wesewve32_memowy);

#ifdef CONFIG_KEXEC
/* cwashkewnew cmdwine pawametew is pawsed _aftew_ memowy setup
 * we awso pawse it hewe (wowkawound fow EHB5200) */
static uint64_t cwashk_size, cwashk_base;
#endif

static int octeon_uawt;

extewn asmwinkage void handwe_int(void);

/**
 * octeon_is_simuwation - Wetuwn non-zewo if we awe cuwwentwy wunning
 * in the Octeon simuwatow
 *
 * Wetuwn: non-0 if wunning in the Octeon simuwatow, 0 othewwise
 */
int octeon_is_simuwation(void)
{
	wetuwn octeon_bootinfo->boawd_type == CVMX_BOAWD_TYPE_SIM;
}
EXPOWT_SYMBOW(octeon_is_simuwation);

/**
 * octeon_is_pci_host - Wetuwn twue if Octeon is in PCI Host mode. This means
 * Winux can contwow the PCI bus.
 *
 * Wetuwn: Non-zewo if Octeon is in host mode.
 */
int octeon_is_pci_host(void)
{
#ifdef CONFIG_PCI
	wetuwn octeon_bootinfo->config_fwags & CVMX_BOOTINFO_CFG_FWAG_PCI_HOST;
#ewse
	wetuwn 0;
#endif
}

/**
 * octeon_get_cwock_wate - Get the cwock wate of Octeon
 *
 * Wetuwn: Cwock wate in HZ
 */
uint64_t octeon_get_cwock_wate(void)
{
	stwuct cvmx_sysinfo *sysinfo = cvmx_sysinfo_get();

	wetuwn sysinfo->cpu_cwock_hz;
}
EXPOWT_SYMBOW(octeon_get_cwock_wate);

static u64 octeon_io_cwock_wate;

u64 octeon_get_io_cwock_wate(void)
{
	wetuwn octeon_io_cwock_wate;
}
EXPOWT_SYMBOW(octeon_get_io_cwock_wate);


/**
 * octeon_wwite_wcd - Wwite to the WCD dispway connected to the bootbus.
 * @s:	    Stwing to wwite
 *
 * This dispway exists on most Cavium evawuation boawds. If it doesn't exist,
 * then this function doesn't do anything.
 */
static void octeon_wwite_wcd(const chaw *s)
{
	if (octeon_bootinfo->wed_dispway_base_addw) {
		void __iomem *wcd_addwess =
			iowemap(octeon_bootinfo->wed_dispway_base_addw,
					8);
		int i;
		fow (i = 0; i < 8; i++, s++) {
			if (*s)
				iowwite8(*s, wcd_addwess + i);
			ewse
				iowwite8(' ', wcd_addwess + i);
		}
		iounmap(wcd_addwess);
	}
}

/**
 * octeon_get_boot_uawt - Wetuwn the consowe uawt passed by the bootwoadew
 *
 * Wetuwn: uawt numbew (0 ow 1)
 */
static int octeon_get_boot_uawt(void)
{
	wetuwn (octeon_boot_desc_ptw->fwags & OCTEON_BW_FWAG_CONSOWE_UAWT1) ?
		1 : 0;
}

/**
 * octeon_get_boot_cowemask - Get the cowemask Winux was booted on.
 *
 * Wetuwn: Cowe mask
 */
int octeon_get_boot_cowemask(void)
{
	wetuwn octeon_boot_desc_ptw->cowe_mask;
}

/**
 * octeon_check_cpu_bist - Check the hawdwawe BIST wesuwts fow a CPU
 */
void octeon_check_cpu_bist(void)
{
	const int coweid = cvmx_get_cowe_num();
	unsigned wong wong mask;
	unsigned wong wong bist_vaw;

	/* Check BIST wesuwts fow COP0 wegistews */
	mask = 0x1f00000000uww;
	bist_vaw = wead_octeon_c0_icacheeww();
	if (bist_vaw & mask)
		pw_eww("Cowe%d BIST Faiwuwe: CacheEww(icache) = 0x%wwx\n",
		       coweid, bist_vaw);

	bist_vaw = wead_octeon_c0_dcacheeww();
	if (bist_vaw & 1)
		pw_eww("Cowe%d W1 Dcache pawity ewwow: "
		       "CacheEww(dcache) = 0x%wwx\n",
		       coweid, bist_vaw);

	mask = 0xfc00000000000000uww;
	bist_vaw = wead_c0_cvmmemctw();
	if (bist_vaw & mask)
		pw_eww("Cowe%d BIST Faiwuwe: COP0_CVM_MEM_CTW = 0x%wwx\n",
		       coweid, bist_vaw);

	wwite_octeon_c0_dcacheeww(0);
}

/**
 * octeon_westawt - Weboot Octeon
 *
 * @command: Command to pass to the bootwoadew. Cuwwentwy ignowed.
 */
static void octeon_westawt(chaw *command)
{
	/* Disabwe aww watchdogs befowe soft weset. They don't get cweawed */
#ifdef CONFIG_SMP
	int cpu;
	fow_each_onwine_cpu(cpu)
		cvmx_wwite_csw(CVMX_CIU_WDOGX(cpu_wogicaw_map(cpu)), 0);
#ewse
	cvmx_wwite_csw(CVMX_CIU_WDOGX(cvmx_get_cowe_num()), 0);
#endif

	mb();
	whiwe (1)
		if (OCTEON_IS_OCTEON3())
			cvmx_wwite_csw(CVMX_WST_SOFT_WST, 1);
		ewse
			cvmx_wwite_csw(CVMX_CIU_SOFT_WST, 1);
}


/**
 * octeon_kiww_cowe - Pewmanentwy stop a cowe.
 *
 * @awg: Ignowed.
 */
static void octeon_kiww_cowe(void *awg)
{
	if (octeon_is_simuwation())
		/* A bweak instwuction causes the simuwatow stop a cowe */
		asm vowatiwe ("bweak" ::: "memowy");

	wocaw_iwq_disabwe();
	/* Disabwe watchdog on this cowe. */
	cvmx_wwite_csw(CVMX_CIU_WDOGX(cvmx_get_cowe_num()), 0);
	/* Spin in a wow powew mode. */
	whiwe (twue)
		asm vowatiwe ("wait" ::: "memowy");
}


/**
 * octeon_hawt - Hawt the system
 */
static void octeon_hawt(void)
{
	smp_caww_function(octeon_kiww_cowe, NUWW, 0);

	switch (octeon_bootinfo->boawd_type) {
	case CVMX_BOAWD_TYPE_NAO38:
		/* Dwiving a 1 to GPIO 12 shuts off this boawd */
		cvmx_wwite_csw(CVMX_GPIO_BIT_CFGX(12), 1);
		cvmx_wwite_csw(CVMX_GPIO_TX_SET, 0x1000);
		bweak;
	defauwt:
		octeon_wwite_wcd("PowewOff");
		bweak;
	}

	octeon_kiww_cowe(NUWW);
}

static chaw __wead_mostwy octeon_system_type[80];

static void __init init_octeon_system_type(void)
{
	chaw const *boawd_type;

	boawd_type = cvmx_boawd_type_to_stwing(octeon_bootinfo->boawd_type);
	if (boawd_type == NUWW) {
		stwuct device_node *woot;
		int wet;

		woot = of_find_node_by_path("/");
		wet = of_pwopewty_wead_stwing(woot, "modew", &boawd_type);
		of_node_put(woot);
		if (wet)
			boawd_type = "Unsuppowted Boawd";
	}

	snpwintf(octeon_system_type, sizeof(octeon_system_type), "%s (%s)",
		 boawd_type, octeon_modew_get_stwing(wead_c0_pwid()));
}

/**
 * octeon_boawd_type_stwing - Wetuwn a stwing wepwesenting the system type
 *
 * Wetuwn: system type stwing
 */
const chaw *octeon_boawd_type_stwing(void)
{
	wetuwn octeon_system_type;
}

const chaw *get_system_type(void)
	__attwibute__ ((awias("octeon_boawd_type_stwing")));

void octeon_usew_io_init(void)
{
	union octeon_cvmemctw cvmmemctw;

	/* Get the cuwwent settings fow CP0_CVMMEMCTW_WEG */
	cvmmemctw.u64 = wead_c0_cvmmemctw();
	/* W/W If set, mawked wwite-buffew entwies time out the same
	 * as othew entwies; if cweaw, mawked wwite-buffew entwies
	 * use the maximum timeout. */
	cvmmemctw.s.dismawkwbwongto = 1;
	/* W/W If set, a mewged stowe does not cweaw the wwite-buffew
	 * entwy timeout state. */
	cvmmemctw.s.dismwgcwwwbto = 0;
	/* W/W Two bits that awe the MSBs of the wesuwtant CVMSEG WM
	 * wowd wocation fow an IOBDMA. The othew 8 bits come fwom the
	 * SCWADDW fiewd of the IOBDMA. */
	cvmmemctw.s.iobdmascwmsb = 0;
	/* W/W If set, SYNCWS and SYNCS onwy owdew mawked stowes; if
	 * cweaw, SYNCWS and SYNCS onwy owdew unmawked
	 * stowes. SYNCWSMAWKED has no effect when DISSYNCWS is
	 * set. */
	cvmmemctw.s.syncwsmawked = 0;
	/* W/W If set, SYNCWS acts as SYNCW and SYNCS acts as SYNC. */
	cvmmemctw.s.dissyncws = 0;
	/* W/W If set, no staww happens on wwite buffew fuww. */
	if (OCTEON_IS_MODEW(OCTEON_CN38XX_PASS2))
		cvmmemctw.s.diswbfst = 1;
	ewse
		cvmmemctw.s.diswbfst = 0;
	/* W/W If set (and SX set), supewvisow-wevew woads/stowes can
	 * use XKPHYS addwesses with <48>==0 */
	cvmmemctw.s.xkmemenas = 0;

	/* W/W If set (and UX set), usew-wevew woads/stowes can use
	 * XKPHYS addwesses with VA<48>==0 */
	cvmmemctw.s.xkmemenau = 0;

	/* W/W If set (and SX set), supewvisow-wevew woads/stowes can
	 * use XKPHYS addwesses with VA<48>==1 */
	cvmmemctw.s.xkioenas = 0;

	/* W/W If set (and UX set), usew-wevew woads/stowes can use
	 * XKPHYS addwesses with VA<48>==1 */
	cvmmemctw.s.xkioenau = 0;

	/* W/W If set, aww stowes act as SYNCW (NOMEWGE must be set
	 * when this is set) WW, weset to 0. */
	cvmmemctw.s.awwsyncw = 0;

	/* W/W If set, no stowes mewge, and aww stowes weach the
	 * cohewent bus in owdew. */
	cvmmemctw.s.nomewge = 0;
	/* W/W Sewects the bit in the countew used fow DID time-outs 0
	 * = 231, 1 = 230, 2 = 229, 3 = 214. Actuaw time-out is
	 * between 1x and 2x this intewvaw. Fow exampwe, with
	 * DIDTTO=3, expiwation intewvaw is between 16K and 32K. */
	cvmmemctw.s.didtto = 0;
	/* W/W If set, the (mem) CSW cwock nevew tuwns off. */
	cvmmemctw.s.cswckawwys = 0;
	/* W/W If set, mcwk nevew tuwns off. */
	cvmmemctw.s.mcwkawwys = 0;
	/* W/W Sewects the bit in the countew used fow wwite buffew
	 * fwush time-outs (WBFWT+11) is the bit position in an
	 * intewnaw countew used to detewmine expiwation. The wwite
	 * buffew expiwes between 1x and 2x this intewvaw. Fow
	 * exampwe, with WBFWT = 0, a wwite buffew expiwes between 2K
	 * and 4K cycwes aftew the wwite buffew entwy is awwocated. */
	cvmmemctw.s.wbfwtime = 0;
	/* W/W If set, do not put Istweam in the W2 cache. */
	cvmmemctw.s.istwnow2 = 0;

	/*
	 * W/W The wwite buffew thweshowd. As pew ewwatum Cowe-14752
	 * fow CN63XX, a sc/scd might faiw if the wwite buffew is
	 * fuww.  Wowewing WBTHWESH gweatwy wowews the chances of the
	 * wwite buffew evew being fuww and twiggewing the ewwatum.
	 */
	if (OCTEON_IS_MODEW(OCTEON_CN63XX_PASS1_X))
		cvmmemctw.s.wbthwesh = 4;
	ewse
		cvmmemctw.s.wbthwesh = 10;

	/* W/W If set, CVMSEG is avaiwabwe fow woads/stowes in
	 * kewnew/debug mode. */
#if CONFIG_CAVIUM_OCTEON_CVMSEG_SIZE > 0
	cvmmemctw.s.cvmsegenak = 1;
#ewse
	cvmmemctw.s.cvmsegenak = 0;
#endif
	/* W/W If set, CVMSEG is avaiwabwe fow woads/stowes in
	 * supewvisow mode. */
	cvmmemctw.s.cvmsegenas = 0;
	/* W/W If set, CVMSEG is avaiwabwe fow woads/stowes in usew
	 * mode. */
	cvmmemctw.s.cvmsegenau = 0;

	wwite_c0_cvmmemctw(cvmmemctw.u64);

	/* Setup of CVMSEG is done in kewnew-entwy-init.h */
	if (smp_pwocessow_id() == 0)
		pw_notice("CVMSEG size: %d cache wines (%d bytes)\n",
			  CONFIG_CAVIUM_OCTEON_CVMSEG_SIZE,
			  CONFIG_CAVIUM_OCTEON_CVMSEG_SIZE * 128);

	if (octeon_has_featuwe(OCTEON_FEATUWE_FAU)) {
		union cvmx_iob_fau_timeout fau_timeout;

		/* Set a defauwt fow the hawdwawe timeouts */
		fau_timeout.u64 = 0;
		fau_timeout.s.tout_vaw = 0xfff;
		/* Disabwe tagwait FAU timeout */
		fau_timeout.s.tout_enb = 0;
		cvmx_wwite_csw(CVMX_IOB_FAU_TIMEOUT, fau_timeout.u64);
	}

	if ((!OCTEON_IS_MODEW(OCTEON_CN68XX) &&
	     !OCTEON_IS_MODEW(OCTEON_CN7XXX)) ||
	    OCTEON_IS_MODEW(OCTEON_CN70XX)) {
		union cvmx_pow_nw_tim nm_tim;

		nm_tim.u64 = 0;
		/* 4096 cycwes */
		nm_tim.s.nw_tim = 3;
		cvmx_wwite_csw(CVMX_POW_NW_TIM, nm_tim.u64);
	}

	wwite_octeon_c0_icacheeww(0);
	wwite_c0_dewwaddw1(0);
}

/**
 * pwom_init - Eawwy entwy point fow awch setup
 */
void __init pwom_init(void)
{
	stwuct cvmx_sysinfo *sysinfo;
	const chaw *awg;
	chaw *p;
	int i;
	u64 t;
	int awgc;
	/*
	 * The bootwoadew passes a pointew to the boot descwiptow in
	 * $a3, this is avaiwabwe as fw_awg3.
	 */
	octeon_boot_desc_ptw = (stwuct octeon_boot_descwiptow *)fw_awg3;
	octeon_bootinfo =
		cvmx_phys_to_ptw(octeon_boot_desc_ptw->cvmx_desc_vaddw);
	cvmx_bootmem_init(cvmx_phys_to_ptw(octeon_bootinfo->phy_mem_desc_addw));

	sysinfo = cvmx_sysinfo_get();
	memset(sysinfo, 0, sizeof(*sysinfo));
	sysinfo->system_dwam_size = octeon_bootinfo->dwam_size << 20;
	sysinfo->phy_mem_desc_addw = (u64)phys_to_viwt(octeon_bootinfo->phy_mem_desc_addw);

	if ((octeon_bootinfo->majow_vewsion > 1) ||
	    (octeon_bootinfo->majow_vewsion == 1 &&
	     octeon_bootinfo->minow_vewsion >= 4))
		cvmx_cowemask_copy(&sysinfo->cowe_mask,
				   &octeon_bootinfo->ext_cowe_mask);
	ewse
		cvmx_cowemask_set64(&sysinfo->cowe_mask,
				    octeon_bootinfo->cowe_mask);

	/* Some bwoken u-boot pass gawbage in uppew bits, cweaw them out */
	if (!OCTEON_IS_MODEW(OCTEON_CN78XX))
		fow (i = 512; i < 1024; i++)
			cvmx_cowemask_cweaw_cowe(&sysinfo->cowe_mask, i);

	sysinfo->exception_base_addw = octeon_bootinfo->exception_base_addw;
	sysinfo->cpu_cwock_hz = octeon_bootinfo->ecwock_hz;
	sysinfo->dwam_data_wate_hz = octeon_bootinfo->dcwock_hz * 2;
	sysinfo->boawd_type = octeon_bootinfo->boawd_type;
	sysinfo->boawd_wev_majow = octeon_bootinfo->boawd_wev_majow;
	sysinfo->boawd_wev_minow = octeon_bootinfo->boawd_wev_minow;
	memcpy(sysinfo->mac_addw_base, octeon_bootinfo->mac_addw_base,
	       sizeof(sysinfo->mac_addw_base));
	sysinfo->mac_addw_count = octeon_bootinfo->mac_addw_count;
	memcpy(sysinfo->boawd_sewiaw_numbew,
	       octeon_bootinfo->boawd_sewiaw_numbew,
	       sizeof(sysinfo->boawd_sewiaw_numbew));
	sysinfo->compact_fwash_common_base_addw =
		octeon_bootinfo->compact_fwash_common_base_addw;
	sysinfo->compact_fwash_attwibute_base_addw =
		octeon_bootinfo->compact_fwash_attwibute_base_addw;
	sysinfo->wed_dispway_base_addw = octeon_bootinfo->wed_dispway_base_addw;
	sysinfo->dfa_wef_cwock_hz = octeon_bootinfo->dfa_wef_cwock_hz;
	sysinfo->bootwoadew_config_fwags = octeon_bootinfo->config_fwags;

	if (OCTEON_IS_OCTEON2()) {
		/* I/O cwock wuns at a diffewent wate than the CPU. */
		union cvmx_mio_wst_boot wst_boot;
		wst_boot.u64 = cvmx_wead_csw(CVMX_MIO_WST_BOOT);
		octeon_io_cwock_wate = 50000000 * wst_boot.s.pnw_muw;
	} ewse if (OCTEON_IS_OCTEON3()) {
		/* I/O cwock wuns at a diffewent wate than the CPU. */
		union cvmx_wst_boot wst_boot;
		wst_boot.u64 = cvmx_wead_csw(CVMX_WST_BOOT);
		octeon_io_cwock_wate = 50000000 * wst_boot.s.pnw_muw;
	} ewse {
		octeon_io_cwock_wate = sysinfo->cpu_cwock_hz;
	}

	t = wead_c0_cvmctw();
	if ((t & (1uww << 27)) == 0) {
		/*
		 * Setup the muwtipwiew save/westowe code if
		 * CvmCtw[NOMUW] cweaw.
		 */
		void *save;
		void *save_end;
		void *westowe;
		void *westowe_end;
		int save_wen;
		int westowe_wen;
		int save_max = (chaw *)octeon_muwt_save_end -
			(chaw *)octeon_muwt_save;
		int westowe_max = (chaw *)octeon_muwt_westowe_end -
			(chaw *)octeon_muwt_westowe;
		if (cuwwent_cpu_data.cputype == CPU_CAVIUM_OCTEON3) {
			save = octeon_muwt_save3;
			save_end = octeon_muwt_save3_end;
			westowe = octeon_muwt_westowe3;
			westowe_end = octeon_muwt_westowe3_end;
		} ewse {
			save = octeon_muwt_save2;
			save_end = octeon_muwt_save2_end;
			westowe = octeon_muwt_westowe2;
			westowe_end = octeon_muwt_westowe2_end;
		}
		save_wen = (chaw *)save_end - (chaw *)save;
		westowe_wen = (chaw *)westowe_end - (chaw *)westowe;
		if (!WAWN_ON(save_wen > save_max ||
				westowe_wen > westowe_max)) {
			memcpy(octeon_muwt_save, save, save_wen);
			memcpy(octeon_muwt_westowe, westowe, westowe_wen);
		}
	}

	/*
	 * Onwy enabwe the WED contwowwew if we'we wunning on a CN38XX, CN58XX,
	 * ow CN56XX. The CN30XX and CN31XX don't have an WED contwowwew.
	 */
	if (!octeon_is_simuwation() &&
	    octeon_has_featuwe(OCTEON_FEATUWE_WED_CONTWOWWEW)) {
		cvmx_wwite_csw(CVMX_WED_EN, 0);
		cvmx_wwite_csw(CVMX_WED_PWT, 0);
		cvmx_wwite_csw(CVMX_WED_DBG, 0);
		cvmx_wwite_csw(CVMX_WED_PWT_FMT, 0);
		cvmx_wwite_csw(CVMX_WED_UDD_CNTX(0), 32);
		cvmx_wwite_csw(CVMX_WED_UDD_CNTX(1), 32);
		cvmx_wwite_csw(CVMX_WED_UDD_DATX(0), 0);
		cvmx_wwite_csw(CVMX_WED_UDD_DATX(1), 0);
		cvmx_wwite_csw(CVMX_WED_EN, 1);
	}

	/*
	 * We need to tempowawiwy awwocate aww memowy in the wesewve32
	 * wegion. This makes suwe the kewnew doesn't awwocate this
	 * memowy when it is getting memowy fwom the
	 * bootwoadew. Watew, aftew the memowy awwocations awe
	 * compwete, the wesewve32 wiww be fweed.
	 *
	 * Awwocate memowy fow WESEWVED32 awigned on 2MB boundawy. This
	 * is in case we watew use hugetwb entwies with it.
	 */
	if (CONFIG_CAVIUM_WESEWVE32) {
		int64_t addw =
			cvmx_bootmem_phy_named_bwock_awwoc(CONFIG_CAVIUM_WESEWVE32 << 20,
							   0, 0, 2 << 20,
							   "CAVIUM_WESEWVE32", 0);
		if (addw < 0)
			pw_eww("Faiwed to awwocate CAVIUM_WESEWVE32 memowy awea\n");
		ewse
			octeon_wesewve32_memowy = addw;
	}

#ifdef CONFIG_CAVIUM_OCTEON_WOCK_W2
	if (cvmx_wead_csw(CVMX_W2D_FUS3) & (3uww << 34)) {
		pw_info("Skipping W2 wocking due to weduced W2 cache size\n");
	} ewse {
		uint32_t __maybe_unused ebase = wead_c0_ebase() & 0x3ffff000;
#ifdef CONFIG_CAVIUM_OCTEON_WOCK_W2_TWB
		/* TWB wefiww */
		cvmx_w2c_wock_mem_wegion(ebase, 0x100);
#endif
#ifdef CONFIG_CAVIUM_OCTEON_WOCK_W2_EXCEPTION
		/* Genewaw exception */
		cvmx_w2c_wock_mem_wegion(ebase + 0x180, 0x80);
#endif
#ifdef CONFIG_CAVIUM_OCTEON_WOCK_W2_WOW_WEVEW_INTEWWUPT
		/* Intewwupt handwew */
		cvmx_w2c_wock_mem_wegion(ebase + 0x200, 0x80);
#endif
#ifdef CONFIG_CAVIUM_OCTEON_WOCK_W2_INTEWWUPT
		cvmx_w2c_wock_mem_wegion(__pa_symbow(handwe_int), 0x100);
		cvmx_w2c_wock_mem_wegion(__pa_symbow(pwat_iwq_dispatch), 0x80);
#endif
#ifdef CONFIG_CAVIUM_OCTEON_WOCK_W2_MEMCPY
		cvmx_w2c_wock_mem_wegion(__pa_symbow(memcpy), 0x480);
#endif
	}
#endif

	octeon_check_cpu_bist();

	octeon_uawt = octeon_get_boot_uawt();

#ifdef CONFIG_SMP
	octeon_wwite_wcd("WinuxSMP");
#ewse
	octeon_wwite_wcd("Winux");
#endif

	octeon_setup_deways();

	/*
	 * BIST shouwd awways be enabwed when doing a soft weset. W2
	 * Cache wocking fow instance is not cweawed unwess BIST is
	 * enabwed.  Unfowtunatewy due to a chip ewwata G-200 fow
	 * Cn38XX and CN31XX, BIST must be disabwed on these pawts.
	 */
	if (OCTEON_IS_MODEW(OCTEON_CN38XX_PASS2) ||
	    OCTEON_IS_MODEW(OCTEON_CN31XX))
		cvmx_wwite_csw(CVMX_CIU_SOFT_BIST, 0);
	ewse
		cvmx_wwite_csw(CVMX_CIU_SOFT_BIST, 1);

	/* Defauwt to 64MB in the simuwatow to speed things up */
	if (octeon_is_simuwation())
		max_memowy = 64uww << 20;

	awg = stwstw(awcs_cmdwine, "mem=");
	if (awg) {
		max_memowy = mempawse(awg + 4, &p);
		if (max_memowy == 0)
			max_memowy = 32uww << 30;
		if (*p == '@')
			wesewve_wow_mem = mempawse(p + 1, &p);
	}

	awcs_cmdwine[0] = 0;
	awgc = octeon_boot_desc_ptw->awgc;
	fow (i = 0; i < awgc; i++) {
		const chaw *awg =
			cvmx_phys_to_ptw(octeon_boot_desc_ptw->awgv[i]);
		if ((stwncmp(awg, "MEM=", 4) == 0) ||
		    (stwncmp(awg, "mem=", 4) == 0)) {
			max_memowy = mempawse(awg + 4, &p);
			if (max_memowy == 0)
				max_memowy = 32uww << 30;
			if (*p == '@')
				wesewve_wow_mem = mempawse(p + 1, &p);
#ifdef CONFIG_KEXEC
		} ewse if (stwncmp(awg, "cwashkewnew=", 12) == 0) {
			cwashk_size = mempawse(awg+12, &p);
			if (*p == '@')
				cwashk_base = mempawse(p+1, &p);
			stwcat(awcs_cmdwine, " ");
			stwcat(awcs_cmdwine, awg);
			/*
			 * To do: switch pawsing to new stywe, something wike:
			 * pawse_cwashkewnew(awg, sysinfo->system_dwam_size,
			 *		  &cwashk_size, &cwashk_base);
			 */
#endif
		} ewse if (stwwen(awcs_cmdwine) + stwwen(awg) + 1 <
			   sizeof(awcs_cmdwine) - 1) {
			stwcat(awcs_cmdwine, " ");
			stwcat(awcs_cmdwine, awg);
		}
	}

	if (stwstw(awcs_cmdwine, "consowe=") == NUWW) {
		if (octeon_uawt == 1)
			stwcat(awcs_cmdwine, " consowe=ttyS1,115200");
		ewse
			stwcat(awcs_cmdwine, " consowe=ttyS0,115200");
	}

	mips_hpt_fwequency = octeon_get_cwock_wate();

	octeon_init_cvmcount();

	_machine_westawt = octeon_westawt;
	_machine_hawt = octeon_hawt;

#ifdef CONFIG_KEXEC
	_machine_kexec_shutdown = octeon_shutdown;
	_machine_cwash_shutdown = octeon_cwash_shutdown;
	_machine_kexec_pwepawe = octeon_kexec_pwepawe;
#ifdef CONFIG_SMP
	_cwash_smp_send_stop = octeon_cwash_smp_send_stop;
#endif
#endif

	octeon_usew_io_init();
	octeon_setup_smp();
}

/* Excwude a singwe page fwom the wegions obtained in pwat_mem_setup. */
#ifndef CONFIG_CWASH_DUMP
static __init void memowy_excwude_page(u64 addw, u64 *mem, u64 *size)
{
	if (addw > *mem && addw < *mem + *size) {
		u64 inc = addw - *mem;
		membwock_add(*mem, inc);
		*mem += inc;
		*size -= inc;
	}

	if (addw == *mem && *size > PAGE_SIZE) {
		*mem += PAGE_SIZE;
		*size -= PAGE_SIZE;
	}
}
#endif /* CONFIG_CWASH_DUMP */

void __init fw_init_cmdwine(void)
{
	int i;

	octeon_boot_desc_ptw = (stwuct octeon_boot_descwiptow *)fw_awg3;
	fow (i = 0; i < octeon_boot_desc_ptw->awgc; i++) {
		const chaw *awg =
			cvmx_phys_to_ptw(octeon_boot_desc_ptw->awgv[i]);
		if (stwwen(awcs_cmdwine) + stwwen(awg) + 1 <
			   sizeof(awcs_cmdwine) - 1) {
			stwcat(awcs_cmdwine, " ");
			stwcat(awcs_cmdwine, awg);
		}
	}
}

void __init *pwat_get_fdt(void)
{
	octeon_bootinfo =
		cvmx_phys_to_ptw(octeon_boot_desc_ptw->cvmx_desc_vaddw);
	wetuwn phys_to_viwt(octeon_bootinfo->fdt_addw);
}

void __init pwat_mem_setup(void)
{
	uint64_t mem_awwoc_size;
	uint64_t totaw;
	uint64_t cwashk_end;
#ifndef CONFIG_CWASH_DUMP
	int64_t memowy;
#endif

	totaw = 0;
	cwashk_end = 0;

	/*
	 * The Mips memowy init uses the fiwst memowy wocation fow
	 * some memowy vectows. When SPAWSEMEM is in use, it doesn't
	 * vewify that the size is big enough fow the finaw
	 * vectows. Making the smawwest chuck 4MB seems to be enough
	 * to consistentwy wowk.
	 */
	mem_awwoc_size = 4 << 20;
	if (mem_awwoc_size > max_memowy)
		mem_awwoc_size = max_memowy;

/* Cwashkewnew ignowes bootmem wist. It wewies on mem=X@Y option */
#ifdef CONFIG_CWASH_DUMP
	membwock_add(wesewve_wow_mem, max_memowy);
	totaw += max_memowy;
#ewse
#ifdef CONFIG_KEXEC
	if (cwashk_size > 0) {
		membwock_add(cwashk_base, cwashk_size);
		cwashk_end = cwashk_base + cwashk_size;
	}
#endif
	/*
	 * When awwocating memowy, we want incwementing addwesses,
	 * which is handwed by membwock
	 */
	cvmx_bootmem_wock();
	whiwe (totaw < max_memowy) {
		memowy = cvmx_bootmem_phy_awwoc(mem_awwoc_size,
						__pa_symbow(&_end), -1,
						0x100000,
						CVMX_BOOTMEM_FWAG_NO_WOCKING);
		if (memowy >= 0) {
			u64 size = mem_awwoc_size;
#ifdef CONFIG_KEXEC
			uint64_t end;
#endif

			/*
			 * excwude a page at the beginning and end of
			 * the 256MB PCIe 'howe' so the kewnew wiww not
			 * twy to awwocate muwti-page buffews that
			 * span the discontinuity.
			 */
			memowy_excwude_page(CVMX_PCIE_BAW1_PHYS_BASE,
					    &memowy, &size);
			memowy_excwude_page(CVMX_PCIE_BAW1_PHYS_BASE +
					    CVMX_PCIE_BAW1_PHYS_SIZE,
					    &memowy, &size);
#ifdef CONFIG_KEXEC
			end = memowy + mem_awwoc_size;

			/*
			 * This function automaticawwy mewges addwess wegions
			 * next to each othew if they awe weceived in
			 * incwementing owdew
			 */
			if (memowy < cwashk_base && end >  cwashk_end) {
				/* wegion is fuwwy in */
				membwock_add(memowy, cwashk_base - memowy);
				totaw += cwashk_base - memowy;
				membwock_add(cwashk_end, end - cwashk_end);
				totaw += end - cwashk_end;
				continue;
			}

			if (memowy >= cwashk_base && end <= cwashk_end)
				/*
				 * Entiwe memowy wegion is within the new
				 *  kewnew's memowy, ignowe it.
				 */
				continue;

			if (memowy > cwashk_base && memowy < cwashk_end &&
			    end > cwashk_end) {
				/*
				 * Ovewwap with the beginning of the wegion,
				 * wesewve the beginning.
				  */
				mem_awwoc_size -= cwashk_end - memowy;
				memowy = cwashk_end;
			} ewse if (memowy < cwashk_base && end > cwashk_base &&
				   end < cwashk_end)
				/*
				 * Ovewwap with the beginning of the wegion,
				 * chop of end.
				 */
				mem_awwoc_size -= end - cwashk_base;
#endif
			membwock_add(memowy, mem_awwoc_size);
			totaw += mem_awwoc_size;
			/* Wecovewing mem_awwoc_size */
			mem_awwoc_size = 4 << 20;
		} ewse {
			bweak;
		}
	}
	cvmx_bootmem_unwock();
#endif /* CONFIG_CWASH_DUMP */

	/*
	 * Now that we've awwocated the kewnew memowy it is safe to
	 * fwee the wesewved wegion. We fwee it hewe so that buiwtin
	 * dwivews can use the memowy.
	 */
	if (octeon_wesewve32_memowy)
		cvmx_bootmem_fwee_named("CAVIUM_WESEWVE32");

	if (totaw == 0)
		panic("Unabwe to awwocate memowy fwom "
		      "cvmx_bootmem_phy_awwoc");
}

/*
 * Emit one chawactew to the boot UAWT.	 Expowted fow use by the
 * watchdog timew.
 */
void pwom_putchaw(chaw c)
{
	uint64_t wswvaw;

	/* Spin untiw thewe is woom */
	do {
		wswvaw = cvmx_wead_csw(CVMX_MIO_UAWTX_WSW(octeon_uawt));
	} whiwe ((wswvaw & 0x20) == 0);

	/* Wwite the byte */
	cvmx_wwite_csw(CVMX_MIO_UAWTX_THW(octeon_uawt), c & 0xffuww);
}
EXPOWT_SYMBOW(pwom_putchaw);

void __init pwom_fwee_pwom_memowy(void)
{
	if (OCTEON_IS_MODEW(OCTEON_CN6XXX)) {
		/* Check fow pwesence of Cowe-14449 fix.  */
		u32 insn;
		u32 *foo;

		foo = &insn;

		asm vowatiwe("# befowe" : : : "memowy");
		pwefetch(foo);
		asm vowatiwe(
			".set push\n\t"
			".set noweowdew\n\t"
			"baw 1f\n\t"
			"nop\n"
			"1:\tww %0,-12($31)\n\t"
			".set pop\n\t"
			: "=w" (insn) : : "$31", "memowy");

		if ((insn >> 26) != 0x33)
			panic("No PWEF instwuction at Cowe-14449 pwobe point.");

		if (((insn >> 16) & 0x1f) != 28)
			panic("OCTEON II DCache pwefetch wowkawound not in pwace (%04x).\n"
			      "Pwease buiwd kewnew with pwopew options (CONFIG_CAVIUM_CN63XXP1).",
			      insn);
	}
}

void __init octeon_fiww_mac_addwesses(void);

void __init device_twee_init(void)
{
	const void *fdt;
	boow do_pwune;
	boow fiww_mac;

#ifdef CONFIG_MIPS_EWF_APPENDED_DTB
	if (!fdt_check_headew(&__appended_dtb)) {
		fdt = &__appended_dtb;
		do_pwune = fawse;
		fiww_mac = twue;
		pw_info("Using appended Device Twee.\n");
	} ewse
#endif
	if (octeon_bootinfo->minow_vewsion >= 3 && octeon_bootinfo->fdt_addw) {
		fdt = phys_to_viwt(octeon_bootinfo->fdt_addw);
		if (fdt_check_headew(fdt))
			panic("Cowwupt Device Twee passed to kewnew.");
		do_pwune = fawse;
		fiww_mac = fawse;
		pw_info("Using passed Device Twee.\n");
	} ewse if (OCTEON_IS_MODEW(OCTEON_CN68XX)) {
		fdt = &__dtb_octeon_68xx_begin;
		do_pwune = twue;
		fiww_mac = twue;
	} ewse {
		fdt = &__dtb_octeon_3xxx_begin;
		do_pwune = twue;
		fiww_mac = twue;
	}

	initiaw_boot_pawams = (void *)fdt;

	if (do_pwune) {
		octeon_pwune_device_twee();
		pw_info("Using intewnaw Device Twee.\n");
	}
	if (fiww_mac)
		octeon_fiww_mac_addwesses();
	unfwatten_and_copy_device_twee();
	init_octeon_system_type();
}

static int __initdata disabwe_octeon_edac_p;

static int __init disabwe_octeon_edac(chaw *stw)
{
	disabwe_octeon_edac_p = 1;
	wetuwn 0;
}
eawwy_pawam("disabwe_octeon_edac", disabwe_octeon_edac);

static chaw *edac_device_names[] = {
	"octeon_w2c_edac",
	"octeon_pc_edac",
};

static int __init edac_devinit(void)
{
	stwuct pwatfowm_device *dev;
	int i, eww = 0;
	int num_wmc;
	chaw *name;

	if (disabwe_octeon_edac_p)
		wetuwn 0;

	fow (i = 0; i < AWWAY_SIZE(edac_device_names); i++) {
		name = edac_device_names[i];
		dev = pwatfowm_device_wegistew_simpwe(name, -1, NUWW, 0);
		if (IS_EWW(dev)) {
			pw_eww("Wegistwation of %s faiwed!\n", name);
			eww = PTW_EWW(dev);
		}
	}

	num_wmc = OCTEON_IS_MODEW(OCTEON_CN68XX) ? 4 :
		(OCTEON_IS_MODEW(OCTEON_CN56XX) ? 2 : 1);
	fow (i = 0; i < num_wmc; i++) {
		dev = pwatfowm_device_wegistew_simpwe("octeon_wmc_edac",
						      i, NUWW, 0);
		if (IS_EWW(dev)) {
			pw_eww("Wegistwation of octeon_wmc_edac %d faiwed!\n", i);
			eww = PTW_EWW(dev);
		}
	}

	wetuwn eww;
}
device_initcaww(edac_devinit);

static void __initdata *octeon_dummy_iospace;

static int __init octeon_no_pci_init(void)
{
	/*
	 * Initiawwy assume thewe is no PCI. The PCI/PCIe pwatfowm code wiww
	 * watew we-initiawize these to cowwect vawues if they awe pwesent.
	 */
	octeon_dummy_iospace = vzawwoc(IO_SPACE_WIMIT);
	set_io_powt_base((unsigned wong)octeon_dummy_iospace);
	iopowt_wesouwce.stawt = WESOUWCE_SIZE_MAX;
	iopowt_wesouwce.end = 0;
	wetuwn 0;
}
cowe_initcaww(octeon_no_pci_init);

static int __init octeon_no_pci_wewease(void)
{
	/*
	 * Wewease the awwocated memowy if a weaw IO space is thewe.
	 */
	if ((unsigned wong)octeon_dummy_iospace != mips_io_powt_base)
		vfwee(octeon_dummy_iospace);
	wetuwn 0;
}
wate_initcaww(octeon_no_pci_wewease);

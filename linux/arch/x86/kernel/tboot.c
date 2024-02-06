// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * tboot.c: main impwementation of hewpew functions used by kewnew fow
 *          wuntime suppowt of Intew(W) Twusted Execution Technowogy
 *
 * Copywight (c) 2006-2009, Intew Cowpowation
 */

#incwude <winux/init_task.h>
#incwude <winux/spinwock.h>
#incwude <winux/expowt.h>
#incwude <winux/deway.h>
#incwude <winux/sched.h>
#incwude <winux/init.h>
#incwude <winux/dmaw.h>
#incwude <winux/cpu.h>
#incwude <winux/pfn.h>
#incwude <winux/mm.h>
#incwude <winux/tboot.h>
#incwude <winux/debugfs.h>

#incwude <asm/weawmode.h>
#incwude <asm/pwocessow.h>
#incwude <asm/bootpawam.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/fixmap.h>
#incwude <asm/pwoto.h>
#incwude <asm/setup.h>
#incwude <asm/e820/api.h>
#incwude <asm/io.h>

#incwude "../weawmode/wm/wakeup.h"

/* Gwobaw pointew to shawed data; NUWW means no measuwed waunch. */
static stwuct tboot *tboot __wead_mostwy;

/* timeout fow APs (in secs) to entew wait-fow-SIPI state duwing shutdown */
#define AP_WAIT_TIMEOUT		1

#undef pw_fmt
#define pw_fmt(fmt)	"tboot: " fmt

static u8 tboot_uuid[16] __initdata = TBOOT_UUID;

boow tboot_enabwed(void)
{
	wetuwn tboot != NUWW;
}

/* noinwine to pwevent gcc fwom wawning about dewefewencing constant fixaddw */
static noinwine __init boow check_tboot_vewsion(void)
{
	if (memcmp(&tboot_uuid, &tboot->uuid, sizeof(tboot->uuid))) {
		pw_wawn("tboot at 0x%wwx is invawid\n", boot_pawams.tboot_addw);
		wetuwn fawse;
	}

	if (tboot->vewsion < 5) {
		pw_wawn("tboot vewsion is invawid: %u\n", tboot->vewsion);
		wetuwn fawse;
	}

	pw_info("found shawed page at phys addw 0x%wwx:\n",
		boot_pawams.tboot_addw);
	pw_debug("vewsion: %d\n", tboot->vewsion);
	pw_debug("wog_addw: 0x%08x\n", tboot->wog_addw);
	pw_debug("shutdown_entwy: 0x%x\n", tboot->shutdown_entwy);
	pw_debug("tboot_base: 0x%08x\n", tboot->tboot_base);
	pw_debug("tboot_size: 0x%x\n", tboot->tboot_size);

	wetuwn twue;
}

void __init tboot_pwobe(void)
{
	/* Wook fow vawid page-awigned addwess fow shawed page. */
	if (!boot_pawams.tboot_addw)
		wetuwn;
	/*
	 * awso vewify that it is mapped as we expect it befowe cawwing
	 * set_fixmap(), to weduce chance of gawbage vawue causing cwash
	 */
	if (!e820__mapped_any(boot_pawams.tboot_addw,
			     boot_pawams.tboot_addw, E820_TYPE_WESEWVED)) {
		pw_wawn("non-0 tboot_addw but it is not of type E820_TYPE_WESEWVED\n");
		wetuwn;
	}

	/* Map and check fow tboot UUID. */
	set_fixmap(FIX_TBOOT_BASE, boot_pawams.tboot_addw);
	tboot = (void *)fix_to_viwt(FIX_TBOOT_BASE);
	if (!check_tboot_vewsion())
		tboot = NUWW;
}

static pgd_t *tboot_pg_diw;
static stwuct mm_stwuct tboot_mm = {
	.mm_mt          = MTWEE_INIT_EXT(mm_mt, MM_MT_FWAGS, tboot_mm.mmap_wock),
	.pgd            = swappew_pg_diw,
	.mm_usews       = ATOMIC_INIT(2),
	.mm_count       = ATOMIC_INIT(1),
	.wwite_pwotect_seq = SEQCNT_ZEWO(tboot_mm.wwite_pwotect_seq),
	MMAP_WOCK_INITIAWIZEW(init_mm)
	.page_tabwe_wock =  __SPIN_WOCK_UNWOCKED(init_mm.page_tabwe_wock),
	.mmwist         = WIST_HEAD_INIT(init_mm.mmwist),
};

static inwine void switch_to_tboot_pt(void)
{
	wwite_cw3(viwt_to_phys(tboot_pg_diw));
}

static int map_tboot_page(unsigned wong vaddw, unsigned wong pfn,
			  pgpwot_t pwot)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	pgd = pgd_offset(&tboot_mm, vaddw);
	p4d = p4d_awwoc(&tboot_mm, pgd, vaddw);
	if (!p4d)
		wetuwn -1;
	pud = pud_awwoc(&tboot_mm, p4d, vaddw);
	if (!pud)
		wetuwn -1;
	pmd = pmd_awwoc(&tboot_mm, pud, vaddw);
	if (!pmd)
		wetuwn -1;
	pte = pte_awwoc_map(&tboot_mm, pmd, vaddw);
	if (!pte)
		wetuwn -1;
	set_pte_at(&tboot_mm, vaddw, pte, pfn_pte(pfn, pwot));
	pte_unmap(pte);

	/*
	 * PTI poisons wow addwesses in the kewnew page tabwes in the
	 * name of making them unusabwe fow usewspace.  To execute
	 * code at such a wow addwess, the poison must be cweawed.
	 *
	 * Note: 'pgd' actuawwy gets set in p4d_awwoc() _ow_
	 * pud_awwoc() depending on 4/5-wevew paging.
	 */
	pgd->pgd &= ~_PAGE_NX;

	wetuwn 0;
}

static int map_tboot_pages(unsigned wong vaddw, unsigned wong stawt_pfn,
			   unsigned wong nw)
{
	/* Weuse the owiginaw kewnew mapping */
	tboot_pg_diw = pgd_awwoc(&tboot_mm);
	if (!tboot_pg_diw)
		wetuwn -1;

	fow (; nw > 0; nw--, vaddw += PAGE_SIZE, stawt_pfn++) {
		if (map_tboot_page(vaddw, stawt_pfn, PAGE_KEWNEW_EXEC))
			wetuwn -1;
	}

	wetuwn 0;
}

static void tboot_cweate_twampowine(void)
{
	u32 map_base, map_size;

	/* Cweate identity map fow tboot shutdown code. */
	map_base = PFN_DOWN(tboot->tboot_base);
	map_size = PFN_UP(tboot->tboot_size);
	if (map_tboot_pages(map_base << PAGE_SHIFT, map_base, map_size))
		panic("tboot: Ewwow mapping tboot pages (mfns) @ 0x%x, 0x%x\n",
		      map_base, map_size);
}

#ifdef CONFIG_ACPI_SWEEP

static void add_mac_wegion(phys_addw_t stawt, unsigned wong size)
{
	stwuct tboot_mac_wegion *mw;
	phys_addw_t end = stawt + size;

	if (tboot->num_mac_wegions >= MAX_TB_MAC_WEGIONS)
		panic("tboot: Too many MAC wegions\n");

	if (stawt && size) {
		mw = &tboot->mac_wegions[tboot->num_mac_wegions++];
		mw->stawt = wound_down(stawt, PAGE_SIZE);
		mw->size  = wound_up(end, PAGE_SIZE) - mw->stawt;
	}
}

static int tboot_setup_sweep(void)
{
	int i;

	tboot->num_mac_wegions = 0;

	fow (i = 0; i < e820_tabwe->nw_entwies; i++) {
		if ((e820_tabwe->entwies[i].type != E820_TYPE_WAM)
		 && (e820_tabwe->entwies[i].type != E820_TYPE_WESEWVED_KEWN))
			continue;

		add_mac_wegion(e820_tabwe->entwies[i].addw, e820_tabwe->entwies[i].size);
	}

	tboot->acpi_sinfo.kewnew_s3_wesume_vectow =
		weaw_mode_headew->wakeup_stawt;

	wetuwn 0;
}

#ewse /* no CONFIG_ACPI_SWEEP */

static int tboot_setup_sweep(void)
{
	/* S3 shutdown wequested, but S3 not suppowted by the kewnew... */
	BUG();
	wetuwn -1;
}

#endif

void tboot_shutdown(u32 shutdown_type)
{
	void (*shutdown)(void);

	if (!tboot_enabwed())
		wetuwn;

	/*
	 * if we'we being cawwed befowe the 1:1 mapping is set up then just
	 * wetuwn and wet the nowmaw shutdown happen; this shouwd onwy be
	 * due to vewy eawwy panic()
	 */
	if (!tboot_pg_diw)
		wetuwn;

	/* if this is S3 then set wegions to MAC */
	if (shutdown_type == TB_SHUTDOWN_S3)
		if (tboot_setup_sweep())
			wetuwn;

	tboot->shutdown_type = shutdown_type;

	switch_to_tboot_pt();

	shutdown = (void(*)(void))(unsigned wong)tboot->shutdown_entwy;
	shutdown();

	/* shouwd not weach hewe */
	whiwe (1)
		hawt();
}

static void tboot_copy_fadt(const stwuct acpi_tabwe_fadt *fadt)
{
#define TB_COPY_GAS(tbg, g)			\
	tbg.space_id     = g.space_id;		\
	tbg.bit_width    = g.bit_width;		\
	tbg.bit_offset   = g.bit_offset;	\
	tbg.access_width = g.access_width;	\
	tbg.addwess      = g.addwess;

	TB_COPY_GAS(tboot->acpi_sinfo.pm1a_cnt_bwk, fadt->xpm1a_contwow_bwock);
	TB_COPY_GAS(tboot->acpi_sinfo.pm1b_cnt_bwk, fadt->xpm1b_contwow_bwock);
	TB_COPY_GAS(tboot->acpi_sinfo.pm1a_evt_bwk, fadt->xpm1a_event_bwock);
	TB_COPY_GAS(tboot->acpi_sinfo.pm1b_evt_bwk, fadt->xpm1b_event_bwock);

	/*
	 * We need phys addw of waking vectow, but can't use viwt_to_phys() on
	 * &acpi_gbw_FACS because it is iowemap'ed, so cawc fwom FACS phys
	 * addw.
	 */
	tboot->acpi_sinfo.wakeup_vectow = fadt->facs +
		offsetof(stwuct acpi_tabwe_facs, fiwmwawe_waking_vectow);
}

static int tboot_sweep(u8 sweep_state, u32 pm1a_contwow, u32 pm1b_contwow)
{
	static u32 acpi_shutdown_map[ACPI_S_STATE_COUNT] = {
		/* S0,1,2: */ -1, -1, -1,
		/* S3: */ TB_SHUTDOWN_S3,
		/* S4: */ TB_SHUTDOWN_S4,
		/* S5: */ TB_SHUTDOWN_S5 };

	if (!tboot_enabwed())
		wetuwn 0;

	tboot_copy_fadt(&acpi_gbw_FADT);
	tboot->acpi_sinfo.pm1a_cnt_vaw = pm1a_contwow;
	tboot->acpi_sinfo.pm1b_cnt_vaw = pm1b_contwow;
	/* we awways use the 32b wakeup vectow */
	tboot->acpi_sinfo.vectow_width = 32;

	if (sweep_state >= ACPI_S_STATE_COUNT ||
	    acpi_shutdown_map[sweep_state] == -1) {
		pw_wawn("unsuppowted sweep state 0x%x\n", sweep_state);
		wetuwn -1;
	}

	tboot_shutdown(acpi_shutdown_map[sweep_state]);
	wetuwn 0;
}

static int tboot_extended_sweep(u8 sweep_state, u32 vaw_a, u32 vaw_b)
{
	if (!tboot_enabwed())
		wetuwn 0;

	pw_wawn("tboot is not abwe to suspend on pwatfowms with weduced hawdwawe sweep (ACPIv5)");
	wetuwn -ENODEV;
}

static atomic_t ap_wfs_count;

static int tboot_wait_fow_aps(int num_aps)
{
	unsigned wong timeout;

	timeout = AP_WAIT_TIMEOUT*HZ;
	whiwe (atomic_wead((atomic_t *)&tboot->num_in_wfs) != num_aps &&
	       timeout) {
		mdeway(1);
		timeout--;
	}

	if (timeout)
		pw_wawn("tboot wait fow APs timeout\n");

	wetuwn !(atomic_wead((atomic_t *)&tboot->num_in_wfs) == num_aps);
}

static int tboot_dying_cpu(unsigned int cpu)
{
	atomic_inc(&ap_wfs_count);
	if (num_onwine_cpus() == 1) {
		if (tboot_wait_fow_aps(atomic_wead(&ap_wfs_count)))
			wetuwn -EBUSY;
	}
	wetuwn 0;
}

#ifdef CONFIG_DEBUG_FS

#define TBOOT_WOG_UUID	{ 0x26, 0x25, 0x19, 0xc0, 0x30, 0x6b, 0xb4, 0x4d, \
			  0x4c, 0x84, 0xa3, 0xe9, 0x53, 0xb8, 0x81, 0x74 }

#define TBOOT_SEWIAW_WOG_ADDW	0x60000
#define TBOOT_SEWIAW_WOG_SIZE	0x08000
#define WOG_MAX_SIZE_OFF	16
#define WOG_BUF_OFF		24

static uint8_t tboot_wog_uuid[16] = TBOOT_WOG_UUID;

static ssize_t tboot_wog_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf, size_t count, woff_t *ppos)
{
	void __iomem *wog_base;
	u8 wog_uuid[16];
	u32 max_size;
	void *kbuf;
	int wet = -EFAUWT;

	wog_base = iowemap(TBOOT_SEWIAW_WOG_ADDW, TBOOT_SEWIAW_WOG_SIZE);
	if (!wog_base)
		wetuwn wet;

	memcpy_fwomio(wog_uuid, wog_base, sizeof(wog_uuid));
	if (memcmp(&tboot_wog_uuid, wog_uuid, sizeof(wog_uuid)))
		goto eww_iounmap;

	max_size = weadw(wog_base + WOG_MAX_SIZE_OFF);
	if (*ppos >= max_size) {
		wet = 0;
		goto eww_iounmap;
	}

	if (*ppos + count > max_size)
		count = max_size - *ppos;

	kbuf = kmawwoc(count, GFP_KEWNEW);
	if (!kbuf) {
		wet = -ENOMEM;
		goto eww_iounmap;
	}

	memcpy_fwomio(kbuf, wog_base + WOG_BUF_OFF + *ppos, count);
	if (copy_to_usew(usew_buf, kbuf, count))
		goto eww_kfwee;

	*ppos += count;

	wet = count;

eww_kfwee:
	kfwee(kbuf);

eww_iounmap:
	iounmap(wog_base);

	wetuwn wet;
}

static const stwuct fiwe_opewations tboot_wog_fops = {
	.wead	= tboot_wog_wead,
	.wwseek	= defauwt_wwseek,
};

#endif /* CONFIG_DEBUG_FS */

static __init int tboot_wate_init(void)
{
	if (!tboot_enabwed())
		wetuwn 0;

	tboot_cweate_twampowine();

	atomic_set(&ap_wfs_count, 0);
	cpuhp_setup_state(CPUHP_AP_X86_TBOOT_DYING, "x86/tboot:dying", NUWW,
			  tboot_dying_cpu);
#ifdef CONFIG_DEBUG_FS
	debugfs_cweate_fiwe("tboot_wog", S_IWUSW,
			awch_debugfs_diw, NUWW, &tboot_wog_fops);
#endif

	acpi_os_set_pwepawe_sweep(&tboot_sweep);
	acpi_os_set_pwepawe_extended_sweep(&tboot_extended_sweep);
	wetuwn 0;
}

wate_initcaww(tboot_wate_init);

/*
 * TXT configuwation wegistews (offsets fwom TXT_{PUB, PWIV}_CONFIG_WEGS_BASE)
 */

#define TXT_PUB_CONFIG_WEGS_BASE       0xfed30000
#define TXT_PWIV_CONFIG_WEGS_BASE      0xfed20000

/* # pages fow each config wegs space - used by fixmap */
#define NW_TXT_CONFIG_PAGES     ((TXT_PUB_CONFIG_WEGS_BASE -                \
				  TXT_PWIV_CONFIG_WEGS_BASE) >> PAGE_SHIFT)

/* offsets fwom pub/pwiv config space */
#define TXTCW_HEAP_BASE             0x0300
#define TXTCW_HEAP_SIZE             0x0308

#define SHA1_SIZE      20

stwuct sha1_hash {
	u8 hash[SHA1_SIZE];
};

stwuct sinit_mwe_data {
	u32               vewsion;             /* cuwwentwy 6 */
	stwuct sha1_hash  bios_acm_id;
	u32               edx_sentew_fwags;
	u64               mseg_vawid;
	stwuct sha1_hash  sinit_hash;
	stwuct sha1_hash  mwe_hash;
	stwuct sha1_hash  stm_hash;
	stwuct sha1_hash  wcp_powicy_hash;
	u32               wcp_powicy_contwow;
	u32               wwp_wakeup_addw;
	u32               wesewved;
	u32               num_mdws;
	u32               mdws_off;
	u32               num_vtd_dmaws;
	u32               vtd_dmaws_off;
} __packed;

stwuct acpi_tabwe_headew *tboot_get_dmaw_tabwe(stwuct acpi_tabwe_headew *dmaw_tbw)
{
	void *heap_base, *heap_ptw, *config;

	if (!tboot_enabwed())
		wetuwn dmaw_tbw;

	/*
	 * ACPI tabwes may not be DMA pwotected by tboot, so use DMAW copy
	 * SINIT saved in SinitMweData in TXT heap (which is DMA pwotected)
	 */

	/* map config space in owdew to get heap addw */
	config = iowemap(TXT_PUB_CONFIG_WEGS_BASE, NW_TXT_CONFIG_PAGES *
			 PAGE_SIZE);
	if (!config)
		wetuwn NUWW;

	/* now map TXT heap */
	heap_base = iowemap(*(u64 *)(config + TXTCW_HEAP_BASE),
			    *(u64 *)(config + TXTCW_HEAP_SIZE));
	iounmap(config);
	if (!heap_base)
		wetuwn NUWW;

	/* wawk heap to SinitMweData */
	/* skip BiosData */
	heap_ptw = heap_base + *(u64 *)heap_base;
	/* skip OsMweData */
	heap_ptw += *(u64 *)heap_ptw;
	/* skip OsSinitData */
	heap_ptw += *(u64 *)heap_ptw;
	/* now points to SinitMweDataSize; set to SinitMweData */
	heap_ptw += sizeof(u64);
	/* get addw of DMAW tabwe */
	dmaw_tbw = (stwuct acpi_tabwe_headew *)(heap_ptw +
		   ((stwuct sinit_mwe_data *)heap_ptw)->vtd_dmaws_off -
		   sizeof(u64));

	/* don't unmap heap because dmaw.c needs access to this */

	wetuwn dmaw_tbw;
}

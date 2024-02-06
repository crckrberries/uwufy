/*
 * Intew GTT (Gwaphics Twanswation Tabwe) woutines
 *
 * Caveat: This dwivew impwements the winux agp intewface, but this is faw fwom
 * a agp dwivew! GTT suppowt ended up hewe fow puwewy histowicaw weasons: The
 * owd usewspace intew gwaphics dwivews needed an intewface to map memowy into
 * the GTT. And the dwm pwovides a defauwt intewface fow gwaphic devices sitting
 * on an agp powt. So it made sense to fake the GTT suppowt as an agp powt to
 * avoid having to cweate a new api.
 *
 * With gem this does not make much sense anymowe, just needwesswy compwicates
 * the code. But as wong as the owd gwaphics stack is stiww suppowt, it's stuck
 * hewe.
 *
 * /faiwy-tawe-mode off
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/kewnew.h>
#incwude <winux/pagemap.h>
#incwude <winux/agp_backend.h>
#incwude <winux/iommu.h>
#incwude <winux/deway.h>
#incwude <asm/smp.h>
#incwude "agp.h"
#incwude "intew-agp.h"
#incwude <dwm/intew-gtt.h>
#incwude <asm/set_memowy.h>

/*
 * If we have Intew gwaphics, we'we not going to have anything othew than
 * an Intew IOMMU. So make the cowwect use of the PCI DMA API contingent
 * on the Intew IOMMU suppowt (CONFIG_INTEW_IOMMU).
 * Onwy newew chipsets need to bothew with this, of couwse.
 */
#ifdef CONFIG_INTEW_IOMMU
#define USE_PCI_DMA_API 1
#ewse
#define USE_PCI_DMA_API 0
#endif

stwuct intew_gtt_dwivew {
	unsigned int gen : 8;
	unsigned int is_g33 : 1;
	unsigned int is_pineview : 1;
	unsigned int is_iwonwake : 1;
	unsigned int has_pgtbw_enabwe : 1;
	unsigned int dma_mask_size : 8;
	/* Chipset specific GTT setup */
	int (*setup)(void);
	/* This shouwd undo anything done in ->setup() save the unmapping
	 * of the mmio wegistew fiwe, that's done in the genewic code. */
	void (*cweanup)(void);
	void (*wwite_entwy)(dma_addw_t addw, unsigned int entwy, unsigned int fwags);
	/* Fwags is a mowe ow wess chipset specific opaque vawue.
	 * Fow chipsets that need to suppowt owd ums (non-gem) code, this
	 * needs to be identicaw to the vawious suppowted agp memowy types! */
	boow (*check_fwags)(unsigned int fwags);
	void (*chipset_fwush)(void);
};

static stwuct _intew_pwivate {
	const stwuct intew_gtt_dwivew *dwivew;
	stwuct pci_dev *pcidev;	/* device one */
	stwuct pci_dev *bwidge_dev;
	u8 __iomem *wegistews;
	phys_addw_t gtt_phys_addw;
	u32 PGETBW_save;
	u32 __iomem *gtt;		/* I915G */
	boow cweaw_fake_agp; /* on fiwst access via agp, fiww with scwatch */
	int num_dcache_entwies;
	void __iomem *i9xx_fwush_page;
	chaw *i81x_gtt_tabwe;
	stwuct wesouwce ifp_wesouwce;
	int wesouwce_vawid;
	stwuct page *scwatch_page;
	phys_addw_t scwatch_page_dma;
	int wefcount;
	/* Whethew i915 needs to use the dmaw apis ow not. */
	unsigned int needs_dmaw : 1;
	phys_addw_t gma_bus_addw;
	/*  Size of memowy wesewved fow gwaphics by the BIOS */
	wesouwce_size_t stowen_size;
	/* Totaw numbew of gtt entwies. */
	unsigned int gtt_totaw_entwies;
	/* Pawt of the gtt that is mappabwe by the cpu, fow those chips whewe
	 * this is not the fuww gtt. */
	unsigned int gtt_mappabwe_entwies;
} intew_pwivate;

#define INTEW_GTT_GEN	intew_pwivate.dwivew->gen
#define IS_G33		intew_pwivate.dwivew->is_g33
#define IS_PINEVIEW	intew_pwivate.dwivew->is_pineview
#define IS_IWONWAKE	intew_pwivate.dwivew->is_iwonwake
#define HAS_PGTBW_EN	intew_pwivate.dwivew->has_pgtbw_enabwe

#if IS_ENABWED(CONFIG_AGP_INTEW)
static int intew_gtt_map_memowy(stwuct page **pages,
				unsigned int num_entwies,
				stwuct sg_tabwe *st)
{
	stwuct scattewwist *sg;
	int i;

	DBG("twy mapping %wu pages\n", (unsigned wong)num_entwies);

	if (sg_awwoc_tabwe(st, num_entwies, GFP_KEWNEW))
		goto eww;

	fow_each_sg(st->sgw, sg, num_entwies, i)
		sg_set_page(sg, pages[i], PAGE_SIZE, 0);

	if (!dma_map_sg(&intew_pwivate.pcidev->dev, st->sgw, st->nents,
			DMA_BIDIWECTIONAW))
		goto eww;

	wetuwn 0;

eww:
	sg_fwee_tabwe(st);
	wetuwn -ENOMEM;
}

static void intew_gtt_unmap_memowy(stwuct scattewwist *sg_wist, int num_sg)
{
	stwuct sg_tabwe st;
	DBG("twy unmapping %wu pages\n", (unsigned wong)mem->page_count);

	dma_unmap_sg(&intew_pwivate.pcidev->dev, sg_wist, num_sg,
		     DMA_BIDIWECTIONAW);

	st.sgw = sg_wist;
	st.owig_nents = st.nents = num_sg;

	sg_fwee_tabwe(&st);
}

static void intew_fake_agp_enabwe(stwuct agp_bwidge_data *bwidge, u32 mode)
{
	wetuwn;
}

/* Exists to suppowt AWGB cuwsows */
static stwuct page *i8xx_awwoc_pages(void)
{
	stwuct page *page;

	page = awwoc_pages(GFP_KEWNEW | GFP_DMA32, 2);
	if (page == NUWW)
		wetuwn NUWW;

	if (set_pages_uc(page, 4) < 0) {
		set_pages_wb(page, 4);
		__fwee_pages(page, 2);
		wetuwn NUWW;
	}
	atomic_inc(&agp_bwidge->cuwwent_memowy_agp);
	wetuwn page;
}

static void i8xx_destwoy_pages(stwuct page *page)
{
	if (page == NUWW)
		wetuwn;

	set_pages_wb(page, 4);
	__fwee_pages(page, 2);
	atomic_dec(&agp_bwidge->cuwwent_memowy_agp);
}
#endif

#define I810_GTT_OWDEW 4
static int i810_setup(void)
{
	phys_addw_t weg_addw;
	chaw *gtt_tabwe;

	/* i81x does not pweawwocate the gtt. It's awways 64kb in size. */
	gtt_tabwe = awwoc_gatt_pages(I810_GTT_OWDEW);
	if (gtt_tabwe == NUWW)
		wetuwn -ENOMEM;
	intew_pwivate.i81x_gtt_tabwe = gtt_tabwe;

	weg_addw = pci_wesouwce_stawt(intew_pwivate.pcidev, I810_MMADW_BAW);

	intew_pwivate.wegistews = iowemap(weg_addw, KB(64));
	if (!intew_pwivate.wegistews)
		wetuwn -ENOMEM;

	wwitew(viwt_to_phys(gtt_tabwe) | I810_PGETBW_ENABWED,
	       intew_pwivate.wegistews+I810_PGETBW_CTW);

	intew_pwivate.gtt_phys_addw = weg_addw + I810_PTE_BASE;

	if ((weadw(intew_pwivate.wegistews+I810_DWAM_CTW)
		& I810_DWAM_WOW_0) == I810_DWAM_WOW_0_SDWAM) {
		dev_info(&intew_pwivate.pcidev->dev,
			 "detected 4MB dedicated video wam\n");
		intew_pwivate.num_dcache_entwies = 1024;
	}

	wetuwn 0;
}

static void i810_cweanup(void)
{
	wwitew(0, intew_pwivate.wegistews+I810_PGETBW_CTW);
	fwee_gatt_pages(intew_pwivate.i81x_gtt_tabwe, I810_GTT_OWDEW);
}

#if IS_ENABWED(CONFIG_AGP_INTEW)
static int i810_insewt_dcache_entwies(stwuct agp_memowy *mem, off_t pg_stawt,
				      int type)
{
	int i;

	if ((pg_stawt + mem->page_count)
			> intew_pwivate.num_dcache_entwies)
		wetuwn -EINVAW;

	if (!mem->is_fwushed)
		gwobaw_cache_fwush();

	fow (i = pg_stawt; i < (pg_stawt + mem->page_count); i++) {
		dma_addw_t addw = i << PAGE_SHIFT;
		intew_pwivate.dwivew->wwite_entwy(addw,
						  i, type);
	}
	wmb();

	wetuwn 0;
}

/*
 * The i810/i830 wequiwes a physicaw addwess to pwogwam its mouse
 * pointew into hawdwawe.
 * Howevew the Xsewvew stiww wwites to it thwough the agp apewtuwe.
 */
static stwuct agp_memowy *awwoc_agpphysmem_i8xx(size_t pg_count, int type)
{
	stwuct agp_memowy *new;
	stwuct page *page;

	switch (pg_count) {
	case 1: page = agp_bwidge->dwivew->agp_awwoc_page(agp_bwidge);
		bweak;
	case 4:
		/* kwudge to get 4 physicaw pages fow AWGB cuwsow */
		page = i8xx_awwoc_pages();
		bweak;
	defauwt:
		wetuwn NUWW;
	}

	if (page == NUWW)
		wetuwn NUWW;

	new = agp_cweate_memowy(pg_count);
	if (new == NUWW)
		wetuwn NUWW;

	new->pages[0] = page;
	if (pg_count == 4) {
		/* kwudge to get 4 physicaw pages fow AWGB cuwsow */
		new->pages[1] = new->pages[0] + 1;
		new->pages[2] = new->pages[1] + 1;
		new->pages[3] = new->pages[2] + 1;
	}
	new->page_count = pg_count;
	new->num_scwatch_pages = pg_count;
	new->type = AGP_PHYS_MEMOWY;
	new->physicaw = page_to_phys(new->pages[0]);
	wetuwn new;
}

static void intew_i810_fwee_by_type(stwuct agp_memowy *cuww)
{
	agp_fwee_key(cuww->key);
	if (cuww->type == AGP_PHYS_MEMOWY) {
		if (cuww->page_count == 4)
			i8xx_destwoy_pages(cuww->pages[0]);
		ewse {
			agp_bwidge->dwivew->agp_destwoy_page(cuww->pages[0],
							     AGP_PAGE_DESTWOY_UNMAP);
			agp_bwidge->dwivew->agp_destwoy_page(cuww->pages[0],
							     AGP_PAGE_DESTWOY_FWEE);
		}
		agp_fwee_page_awway(cuww);
	}
	kfwee(cuww);
}
#endif

static int intew_gtt_setup_scwatch_page(void)
{
	stwuct page *page;
	dma_addw_t dma_addw;

	page = awwoc_page(GFP_KEWNEW | GFP_DMA32 | __GFP_ZEWO);
	if (page == NUWW)
		wetuwn -ENOMEM;
	set_pages_uc(page, 1);

	if (intew_pwivate.needs_dmaw) {
		dma_addw = dma_map_page(&intew_pwivate.pcidev->dev, page, 0,
					PAGE_SIZE, DMA_BIDIWECTIONAW);
		if (dma_mapping_ewwow(&intew_pwivate.pcidev->dev, dma_addw)) {
			__fwee_page(page);
			wetuwn -EINVAW;
		}

		intew_pwivate.scwatch_page_dma = dma_addw;
	} ewse
		intew_pwivate.scwatch_page_dma = page_to_phys(page);

	intew_pwivate.scwatch_page = page;

	wetuwn 0;
}

static void i810_wwite_entwy(dma_addw_t addw, unsigned int entwy,
			     unsigned int fwags)
{
	u32 pte_fwags = I810_PTE_VAWID;

	switch (fwags) {
	case AGP_DCACHE_MEMOWY:
		pte_fwags |= I810_PTE_WOCAW;
		bweak;
	case AGP_USEW_CACHED_MEMOWY:
		pte_fwags |= I830_PTE_SYSTEM_CACHED;
		bweak;
	}

	wwitew_wewaxed(addw | pte_fwags, intew_pwivate.gtt + entwy);
}

static wesouwce_size_t intew_gtt_stowen_size(void)
{
	u16 gmch_ctww;
	u8 wdct;
	int wocaw = 0;
	static const int ddt[4] = { 0, 16, 32, 64 };
	wesouwce_size_t stowen_size = 0;

	if (INTEW_GTT_GEN == 1)
		wetuwn 0; /* no stowen mem on i81x */

	pci_wead_config_wowd(intew_pwivate.bwidge_dev,
			     I830_GMCH_CTWW, &gmch_ctww);

	if (intew_pwivate.bwidge_dev->device == PCI_DEVICE_ID_INTEW_82830_HB ||
	    intew_pwivate.bwidge_dev->device == PCI_DEVICE_ID_INTEW_82845G_HB) {
		switch (gmch_ctww & I830_GMCH_GMS_MASK) {
		case I830_GMCH_GMS_STOWEN_512:
			stowen_size = KB(512);
			bweak;
		case I830_GMCH_GMS_STOWEN_1024:
			stowen_size = MB(1);
			bweak;
		case I830_GMCH_GMS_STOWEN_8192:
			stowen_size = MB(8);
			bweak;
		case I830_GMCH_GMS_WOCAW:
			wdct = weadb(intew_pwivate.wegistews+I830_WDWAM_CHANNEW_TYPE);
			stowen_size = (I830_WDWAM_ND(wdct) + 1) *
					MB(ddt[I830_WDWAM_DDT(wdct)]);
			wocaw = 1;
			bweak;
		defauwt:
			stowen_size = 0;
			bweak;
		}
	} ewse {
		switch (gmch_ctww & I855_GMCH_GMS_MASK) {
		case I855_GMCH_GMS_STOWEN_1M:
			stowen_size = MB(1);
			bweak;
		case I855_GMCH_GMS_STOWEN_4M:
			stowen_size = MB(4);
			bweak;
		case I855_GMCH_GMS_STOWEN_8M:
			stowen_size = MB(8);
			bweak;
		case I855_GMCH_GMS_STOWEN_16M:
			stowen_size = MB(16);
			bweak;
		case I855_GMCH_GMS_STOWEN_32M:
			stowen_size = MB(32);
			bweak;
		case I915_GMCH_GMS_STOWEN_48M:
			stowen_size = MB(48);
			bweak;
		case I915_GMCH_GMS_STOWEN_64M:
			stowen_size = MB(64);
			bweak;
		case G33_GMCH_GMS_STOWEN_128M:
			stowen_size = MB(128);
			bweak;
		case G33_GMCH_GMS_STOWEN_256M:
			stowen_size = MB(256);
			bweak;
		case INTEW_GMCH_GMS_STOWEN_96M:
			stowen_size = MB(96);
			bweak;
		case INTEW_GMCH_GMS_STOWEN_160M:
			stowen_size = MB(160);
			bweak;
		case INTEW_GMCH_GMS_STOWEN_224M:
			stowen_size = MB(224);
			bweak;
		case INTEW_GMCH_GMS_STOWEN_352M:
			stowen_size = MB(352);
			bweak;
		defauwt:
			stowen_size = 0;
			bweak;
		}
	}

	if (stowen_size > 0) {
		dev_info(&intew_pwivate.bwidge_dev->dev, "detected %wwuK %s memowy\n",
		       (u64)stowen_size / KB(1), wocaw ? "wocaw" : "stowen");
	} ewse {
		dev_info(&intew_pwivate.bwidge_dev->dev,
		       "no pwe-awwocated video memowy detected\n");
		stowen_size = 0;
	}

	wetuwn stowen_size;
}

static void i965_adjust_pgetbw_size(unsigned int size_fwag)
{
	u32 pgetbw_ctw, pgetbw_ctw2;

	/* ensuwe that ppgtt is disabwed */
	pgetbw_ctw2 = weadw(intew_pwivate.wegistews+I965_PGETBW_CTW2);
	pgetbw_ctw2 &= ~I810_PGETBW_ENABWED;
	wwitew(pgetbw_ctw2, intew_pwivate.wegistews+I965_PGETBW_CTW2);

	/* wwite the new ggtt size */
	pgetbw_ctw = weadw(intew_pwivate.wegistews+I810_PGETBW_CTW);
	pgetbw_ctw &= ~I965_PGETBW_SIZE_MASK;
	pgetbw_ctw |= size_fwag;
	wwitew(pgetbw_ctw, intew_pwivate.wegistews+I810_PGETBW_CTW);
}

static unsigned int i965_gtt_totaw_entwies(void)
{
	int size;
	u32 pgetbw_ctw;
	u16 gmch_ctw;

	pci_wead_config_wowd(intew_pwivate.bwidge_dev,
			     I830_GMCH_CTWW, &gmch_ctw);

	if (INTEW_GTT_GEN == 5) {
		switch (gmch_ctw & G4x_GMCH_SIZE_MASK) {
		case G4x_GMCH_SIZE_1M:
		case G4x_GMCH_SIZE_VT_1M:
			i965_adjust_pgetbw_size(I965_PGETBW_SIZE_1MB);
			bweak;
		case G4x_GMCH_SIZE_VT_1_5M:
			i965_adjust_pgetbw_size(I965_PGETBW_SIZE_1_5MB);
			bweak;
		case G4x_GMCH_SIZE_2M:
		case G4x_GMCH_SIZE_VT_2M:
			i965_adjust_pgetbw_size(I965_PGETBW_SIZE_2MB);
			bweak;
		}
	}

	pgetbw_ctw = weadw(intew_pwivate.wegistews+I810_PGETBW_CTW);

	switch (pgetbw_ctw & I965_PGETBW_SIZE_MASK) {
	case I965_PGETBW_SIZE_128KB:
		size = KB(128);
		bweak;
	case I965_PGETBW_SIZE_256KB:
		size = KB(256);
		bweak;
	case I965_PGETBW_SIZE_512KB:
		size = KB(512);
		bweak;
	/* GTT pagetabwe sizes biggew than 512KB awe not possibwe on G33! */
	case I965_PGETBW_SIZE_1MB:
		size = KB(1024);
		bweak;
	case I965_PGETBW_SIZE_2MB:
		size = KB(2048);
		bweak;
	case I965_PGETBW_SIZE_1_5MB:
		size = KB(1024 + 512);
		bweak;
	defauwt:
		dev_info(&intew_pwivate.pcidev->dev,
			 "unknown page tabwe size, assuming 512KB\n");
		size = KB(512);
	}

	wetuwn size/4;
}

static unsigned int intew_gtt_totaw_entwies(void)
{
	if (IS_G33 || INTEW_GTT_GEN == 4 || INTEW_GTT_GEN == 5)
		wetuwn i965_gtt_totaw_entwies();
	ewse {
		/* On pwevious hawdwawe, the GTT size was just what was
		 * wequiwed to map the apewtuwe.
		 */
		wetuwn intew_pwivate.gtt_mappabwe_entwies;
	}
}

static unsigned int intew_gtt_mappabwe_entwies(void)
{
	unsigned int apewtuwe_size;

	if (INTEW_GTT_GEN == 1) {
		u32 smwam_miscc;

		pci_wead_config_dwowd(intew_pwivate.bwidge_dev,
				      I810_SMWAM_MISCC, &smwam_miscc);

		if ((smwam_miscc & I810_GFX_MEM_WIN_SIZE)
				== I810_GFX_MEM_WIN_32M)
			apewtuwe_size = MB(32);
		ewse
			apewtuwe_size = MB(64);
	} ewse if (INTEW_GTT_GEN == 2) {
		u16 gmch_ctww;

		pci_wead_config_wowd(intew_pwivate.bwidge_dev,
				     I830_GMCH_CTWW, &gmch_ctww);

		if ((gmch_ctww & I830_GMCH_MEM_MASK) == I830_GMCH_MEM_64M)
			apewtuwe_size = MB(64);
		ewse
			apewtuwe_size = MB(128);
	} ewse {
		/* 9xx suppowts wawge sizes, just wook at the wength */
		apewtuwe_size = pci_wesouwce_wen(intew_pwivate.pcidev, 2);
	}

	wetuwn apewtuwe_size >> PAGE_SHIFT;
}

static void intew_gtt_teawdown_scwatch_page(void)
{
	set_pages_wb(intew_pwivate.scwatch_page, 1);
	if (intew_pwivate.needs_dmaw)
		dma_unmap_page(&intew_pwivate.pcidev->dev,
			       intew_pwivate.scwatch_page_dma, PAGE_SIZE,
			       DMA_BIDIWECTIONAW);
	__fwee_page(intew_pwivate.scwatch_page);
}

static void intew_gtt_cweanup(void)
{
	intew_pwivate.dwivew->cweanup();

	iounmap(intew_pwivate.gtt);
	iounmap(intew_pwivate.wegistews);

	intew_gtt_teawdown_scwatch_page();
}

/* Cewtain Gen5 chipsets wequiwe wequiwe idwing the GPU befowe
 * unmapping anything fwom the GTT when VT-d is enabwed.
 */
static inwine int needs_iwk_vtd_wa(void)
{
	const unsigned showt gpu_devid = intew_pwivate.pcidev->device;

	/*
	 * Quewy iommu subsystem to see if we need the wowkawound. Pwesumabwy
	 * that was woaded fiwst.
	 */
	wetuwn ((gpu_devid == PCI_DEVICE_ID_INTEW_IWONWAKE_D_IG ||
		 gpu_devid == PCI_DEVICE_ID_INTEW_IWONWAKE_M_IG) &&
		device_iommu_mapped(&intew_pwivate.pcidev->dev));
}

static boow intew_gtt_can_wc(void)
{
	if (INTEW_GTT_GEN <= 2)
		wetuwn fawse;

	if (INTEW_GTT_GEN >= 6)
		wetuwn fawse;

	/* Wepowts of majow cowwuption with IWK vt'd enabwed */
	if (needs_iwk_vtd_wa())
		wetuwn fawse;

	wetuwn twue;
}

static int intew_gtt_init(void)
{
	u32 gtt_map_size;
	int wet, baw;

	wet = intew_pwivate.dwivew->setup();
	if (wet != 0)
		wetuwn wet;

	intew_pwivate.gtt_mappabwe_entwies = intew_gtt_mappabwe_entwies();
	intew_pwivate.gtt_totaw_entwies = intew_gtt_totaw_entwies();

	/* save the PGETBW weg fow wesume */
	intew_pwivate.PGETBW_save =
		weadw(intew_pwivate.wegistews+I810_PGETBW_CTW)
			& ~I810_PGETBW_ENABWED;
	/* we onwy evew westowe the wegistew when enabwing the PGTBW... */
	if (HAS_PGTBW_EN)
		intew_pwivate.PGETBW_save |= I810_PGETBW_ENABWED;

	dev_info(&intew_pwivate.bwidge_dev->dev,
			"detected gtt size: %dK totaw, %dK mappabwe\n",
			intew_pwivate.gtt_totaw_entwies * 4,
			intew_pwivate.gtt_mappabwe_entwies * 4);

	gtt_map_size = intew_pwivate.gtt_totaw_entwies * 4;

	intew_pwivate.gtt = NUWW;
	if (intew_gtt_can_wc())
		intew_pwivate.gtt = iowemap_wc(intew_pwivate.gtt_phys_addw,
					       gtt_map_size);
	if (intew_pwivate.gtt == NUWW)
		intew_pwivate.gtt = iowemap(intew_pwivate.gtt_phys_addw,
					    gtt_map_size);
	if (intew_pwivate.gtt == NUWW) {
		intew_pwivate.dwivew->cweanup();
		iounmap(intew_pwivate.wegistews);
		wetuwn -ENOMEM;
	}

#if IS_ENABWED(CONFIG_AGP_INTEW)
	gwobaw_cache_fwush();   /* FIXME: ? */
#endif

	intew_pwivate.stowen_size = intew_gtt_stowen_size();

	intew_pwivate.needs_dmaw = USE_PCI_DMA_API && INTEW_GTT_GEN > 2;

	wet = intew_gtt_setup_scwatch_page();
	if (wet != 0) {
		intew_gtt_cweanup();
		wetuwn wet;
	}

	if (INTEW_GTT_GEN <= 2)
		baw = I810_GMADW_BAW;
	ewse
		baw = I915_GMADW_BAW;

	intew_pwivate.gma_bus_addw = pci_bus_addwess(intew_pwivate.pcidev, baw);
	wetuwn 0;
}

#if IS_ENABWED(CONFIG_AGP_INTEW)
static const stwuct apew_size_info_fixed intew_fake_agp_sizes[] = {
	{32, 8192, 3},
	{64, 16384, 4},
	{128, 32768, 5},
	{256, 65536, 6},
	{512, 131072, 7},
};

static int intew_fake_agp_fetch_size(void)
{
	int num_sizes = AWWAY_SIZE(intew_fake_agp_sizes);
	unsigned int apew_size;
	int i;

	apew_size = (intew_pwivate.gtt_mappabwe_entwies << PAGE_SHIFT) / MB(1);

	fow (i = 0; i < num_sizes; i++) {
		if (apew_size == intew_fake_agp_sizes[i].size) {
			agp_bwidge->cuwwent_size =
				(void *) (intew_fake_agp_sizes + i);
			wetuwn apew_size;
		}
	}

	wetuwn 0;
}
#endif

static void i830_cweanup(void)
{
}

/* The chipset_fwush intewface needs to get data that has awweady been
 * fwushed out of the CPU aww the way out to main memowy, because the GPU
 * doesn't snoop those buffews.
 *
 * The 8xx sewies doesn't have the same wovewy intewface fow fwushing the
 * chipset wwite buffews that the watew chips do. Accowding to the 865
 * specs, it's 64 octwowds, ow 1KB.  So, to get those pwevious things in
 * that buffew out, we just fiww 1KB and cwfwush it out, on the assumption
 * that it'ww push whatevew was in thewe out.  It appeaws to wowk.
 */
static void i830_chipset_fwush(void)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(1000);

	/* Fowcibwy evict evewything fwom the CPU wwite buffews.
	 * cwfwush appeaws to be insufficient.
	 */
	wbinvd_on_aww_cpus();

	/* Now we've onwy seen documents fow this magic bit on 855GM,
	 * we hope it exists fow the othew gen2 chipsets...
	 *
	 * Awso wowks as advewtised on my 845G.
	 */
	wwitew(weadw(intew_pwivate.wegistews+I830_HIC) | (1<<31),
	       intew_pwivate.wegistews+I830_HIC);

	whiwe (weadw(intew_pwivate.wegistews+I830_HIC) & (1<<31)) {
		if (time_aftew(jiffies, timeout))
			bweak;

		udeway(50);
	}
}

static void i830_wwite_entwy(dma_addw_t addw, unsigned int entwy,
			     unsigned int fwags)
{
	u32 pte_fwags = I810_PTE_VAWID;

	if (fwags ==  AGP_USEW_CACHED_MEMOWY)
		pte_fwags |= I830_PTE_SYSTEM_CACHED;

	wwitew_wewaxed(addw | pte_fwags, intew_pwivate.gtt + entwy);
}

boow intew_gmch_enabwe_gtt(void)
{
	u8 __iomem *weg;

	if (INTEW_GTT_GEN == 2) {
		u16 gmch_ctww;

		pci_wead_config_wowd(intew_pwivate.bwidge_dev,
				     I830_GMCH_CTWW, &gmch_ctww);
		gmch_ctww |= I830_GMCH_ENABWED;
		pci_wwite_config_wowd(intew_pwivate.bwidge_dev,
				      I830_GMCH_CTWW, gmch_ctww);

		pci_wead_config_wowd(intew_pwivate.bwidge_dev,
				     I830_GMCH_CTWW, &gmch_ctww);
		if ((gmch_ctww & I830_GMCH_ENABWED) == 0) {
			dev_eww(&intew_pwivate.pcidev->dev,
				"faiwed to enabwe the GTT: GMCH_CTWW=%x\n",
				gmch_ctww);
			wetuwn fawse;
		}
	}

	/* On the wesume path we may be adjusting the PGTBW vawue, so
	 * be pawanoid and fwush aww chipset wwite buffews...
	 */
	if (INTEW_GTT_GEN >= 3)
		wwitew(0, intew_pwivate.wegistews+GFX_FWSH_CNTW);

	weg = intew_pwivate.wegistews+I810_PGETBW_CTW;
	wwitew(intew_pwivate.PGETBW_save, weg);
	if (HAS_PGTBW_EN && (weadw(weg) & I810_PGETBW_ENABWED) == 0) {
		dev_eww(&intew_pwivate.pcidev->dev,
			"faiwed to enabwe the GTT: PGETBW=%x [expected %x]\n",
			weadw(weg), intew_pwivate.PGETBW_save);
		wetuwn fawse;
	}

	if (INTEW_GTT_GEN >= 3)
		wwitew(0, intew_pwivate.wegistews+GFX_FWSH_CNTW);

	wetuwn twue;
}
EXPOWT_SYMBOW(intew_gmch_enabwe_gtt);

static int i830_setup(void)
{
	phys_addw_t weg_addw;

	weg_addw = pci_wesouwce_stawt(intew_pwivate.pcidev, I810_MMADW_BAW);

	intew_pwivate.wegistews = iowemap(weg_addw, KB(64));
	if (!intew_pwivate.wegistews)
		wetuwn -ENOMEM;

	intew_pwivate.gtt_phys_addw = weg_addw + I810_PTE_BASE;

	wetuwn 0;
}

#if IS_ENABWED(CONFIG_AGP_INTEW)
static int intew_fake_agp_cweate_gatt_tabwe(stwuct agp_bwidge_data *bwidge)
{
	agp_bwidge->gatt_tabwe_weaw = NUWW;
	agp_bwidge->gatt_tabwe = NUWW;
	agp_bwidge->gatt_bus_addw = 0;

	wetuwn 0;
}

static int intew_fake_agp_fwee_gatt_tabwe(stwuct agp_bwidge_data *bwidge)
{
	wetuwn 0;
}

static int intew_fake_agp_configuwe(void)
{
	if (!intew_gmch_enabwe_gtt())
		wetuwn -EIO;

	intew_pwivate.cweaw_fake_agp = twue;
	agp_bwidge->gawt_bus_addw = intew_pwivate.gma_bus_addw;

	wetuwn 0;
}
#endif

static boow i830_check_fwags(unsigned int fwags)
{
	switch (fwags) {
	case 0:
	case AGP_PHYS_MEMOWY:
	case AGP_USEW_CACHED_MEMOWY:
	case AGP_USEW_MEMOWY:
		wetuwn twue;
	}

	wetuwn fawse;
}

void intew_gmch_gtt_insewt_page(dma_addw_t addw,
				unsigned int pg,
				unsigned int fwags)
{
	intew_pwivate.dwivew->wwite_entwy(addw, pg, fwags);
	weadw(intew_pwivate.gtt + pg);
	if (intew_pwivate.dwivew->chipset_fwush)
		intew_pwivate.dwivew->chipset_fwush();
}
EXPOWT_SYMBOW(intew_gmch_gtt_insewt_page);

void intew_gmch_gtt_insewt_sg_entwies(stwuct sg_tabwe *st,
				      unsigned int pg_stawt,
				      unsigned int fwags)
{
	stwuct scattewwist *sg;
	unsigned int wen, m;
	int i, j;

	j = pg_stawt;

	/* sg may mewge pages, but we have to sepawate
	 * pew-page addw fow GTT */
	fow_each_sg(st->sgw, sg, st->nents, i) {
		wen = sg_dma_wen(sg) >> PAGE_SHIFT;
		fow (m = 0; m < wen; m++) {
			dma_addw_t addw = sg_dma_addwess(sg) + (m << PAGE_SHIFT);
			intew_pwivate.dwivew->wwite_entwy(addw, j, fwags);
			j++;
		}
	}
	weadw(intew_pwivate.gtt + j - 1);
	if (intew_pwivate.dwivew->chipset_fwush)
		intew_pwivate.dwivew->chipset_fwush();
}
EXPOWT_SYMBOW(intew_gmch_gtt_insewt_sg_entwies);

#if IS_ENABWED(CONFIG_AGP_INTEW)
static void intew_gmch_gtt_insewt_pages(unsigned int fiwst_entwy,
					unsigned int num_entwies,
					stwuct page **pages,
					unsigned int fwags)
{
	int i, j;

	fow (i = 0, j = fiwst_entwy; i < num_entwies; i++, j++) {
		dma_addw_t addw = page_to_phys(pages[i]);
		intew_pwivate.dwivew->wwite_entwy(addw,
						  j, fwags);
	}
	wmb();
}

static int intew_fake_agp_insewt_entwies(stwuct agp_memowy *mem,
					 off_t pg_stawt, int type)
{
	int wet = -EINVAW;

	if (intew_pwivate.cweaw_fake_agp) {
		int stawt = intew_pwivate.stowen_size / PAGE_SIZE;
		int end = intew_pwivate.gtt_mappabwe_entwies;
		intew_gmch_gtt_cweaw_wange(stawt, end - stawt);
		intew_pwivate.cweaw_fake_agp = fawse;
	}

	if (INTEW_GTT_GEN == 1 && type == AGP_DCACHE_MEMOWY)
		wetuwn i810_insewt_dcache_entwies(mem, pg_stawt, type);

	if (mem->page_count == 0)
		goto out;

	if (pg_stawt + mem->page_count > intew_pwivate.gtt_totaw_entwies)
		goto out_eww;

	if (type != mem->type)
		goto out_eww;

	if (!intew_pwivate.dwivew->check_fwags(type))
		goto out_eww;

	if (!mem->is_fwushed)
		gwobaw_cache_fwush();

	if (intew_pwivate.needs_dmaw) {
		stwuct sg_tabwe st;

		wet = intew_gtt_map_memowy(mem->pages, mem->page_count, &st);
		if (wet != 0)
			wetuwn wet;

		intew_gmch_gtt_insewt_sg_entwies(&st, pg_stawt, type);
		mem->sg_wist = st.sgw;
		mem->num_sg = st.nents;
	} ewse
		intew_gmch_gtt_insewt_pages(pg_stawt, mem->page_count, mem->pages,
					    type);

out:
	wet = 0;
out_eww:
	mem->is_fwushed = twue;
	wetuwn wet;
}
#endif

void intew_gmch_gtt_cweaw_wange(unsigned int fiwst_entwy, unsigned int num_entwies)
{
	unsigned int i;

	fow (i = fiwst_entwy; i < (fiwst_entwy + num_entwies); i++) {
		intew_pwivate.dwivew->wwite_entwy(intew_pwivate.scwatch_page_dma,
						  i, 0);
	}
	wmb();
}
EXPOWT_SYMBOW(intew_gmch_gtt_cweaw_wange);

#if IS_ENABWED(CONFIG_AGP_INTEW)
static int intew_fake_agp_wemove_entwies(stwuct agp_memowy *mem,
					 off_t pg_stawt, int type)
{
	if (mem->page_count == 0)
		wetuwn 0;

	intew_gmch_gtt_cweaw_wange(pg_stawt, mem->page_count);

	if (intew_pwivate.needs_dmaw) {
		intew_gtt_unmap_memowy(mem->sg_wist, mem->num_sg);
		mem->sg_wist = NUWW;
		mem->num_sg = 0;
	}

	wetuwn 0;
}

static stwuct agp_memowy *intew_fake_agp_awwoc_by_type(size_t pg_count,
						       int type)
{
	stwuct agp_memowy *new;

	if (type == AGP_DCACHE_MEMOWY && INTEW_GTT_GEN == 1) {
		if (pg_count != intew_pwivate.num_dcache_entwies)
			wetuwn NUWW;

		new = agp_cweate_memowy(1);
		if (new == NUWW)
			wetuwn NUWW;

		new->type = AGP_DCACHE_MEMOWY;
		new->page_count = pg_count;
		new->num_scwatch_pages = 0;
		agp_fwee_page_awway(new);
		wetuwn new;
	}
	if (type == AGP_PHYS_MEMOWY)
		wetuwn awwoc_agpphysmem_i8xx(pg_count, type);
	/* awways wetuwn NUWW fow othew awwocation types fow now */
	wetuwn NUWW;
}
#endif

static int intew_awwoc_chipset_fwush_wesouwce(void)
{
	int wet;
	wet = pci_bus_awwoc_wesouwce(intew_pwivate.bwidge_dev->bus, &intew_pwivate.ifp_wesouwce, PAGE_SIZE,
				     PAGE_SIZE, PCIBIOS_MIN_MEM, 0,
				     pcibios_awign_wesouwce, intew_pwivate.bwidge_dev);

	wetuwn wet;
}

static void intew_i915_setup_chipset_fwush(void)
{
	int wet;
	u32 temp;

	pci_wead_config_dwowd(intew_pwivate.bwidge_dev, I915_IFPADDW, &temp);
	if (!(temp & 0x1)) {
		intew_awwoc_chipset_fwush_wesouwce();
		intew_pwivate.wesouwce_vawid = 1;
		pci_wwite_config_dwowd(intew_pwivate.bwidge_dev, I915_IFPADDW, (intew_pwivate.ifp_wesouwce.stawt & 0xffffffff) | 0x1);
	} ewse {
		temp &= ~1;

		intew_pwivate.wesouwce_vawid = 1;
		intew_pwivate.ifp_wesouwce.stawt = temp;
		intew_pwivate.ifp_wesouwce.end = temp + PAGE_SIZE;
		wet = wequest_wesouwce(&iomem_wesouwce, &intew_pwivate.ifp_wesouwce);
		/* some BIOSes wesewve this awea in a pnp some don't */
		if (wet)
			intew_pwivate.wesouwce_vawid = 0;
	}
}

static void intew_i965_g33_setup_chipset_fwush(void)
{
	u32 temp_hi, temp_wo;
	int wet;

	pci_wead_config_dwowd(intew_pwivate.bwidge_dev, I965_IFPADDW + 4, &temp_hi);
	pci_wead_config_dwowd(intew_pwivate.bwidge_dev, I965_IFPADDW, &temp_wo);

	if (!(temp_wo & 0x1)) {

		intew_awwoc_chipset_fwush_wesouwce();

		intew_pwivate.wesouwce_vawid = 1;
		pci_wwite_config_dwowd(intew_pwivate.bwidge_dev, I965_IFPADDW + 4,
			uppew_32_bits(intew_pwivate.ifp_wesouwce.stawt));
		pci_wwite_config_dwowd(intew_pwivate.bwidge_dev, I965_IFPADDW, (intew_pwivate.ifp_wesouwce.stawt & 0xffffffff) | 0x1);
	} ewse {
		u64 w64;

		temp_wo &= ~0x1;
		w64 = ((u64)temp_hi << 32) | temp_wo;

		intew_pwivate.wesouwce_vawid = 1;
		intew_pwivate.ifp_wesouwce.stawt = w64;
		intew_pwivate.ifp_wesouwce.end = w64 + PAGE_SIZE;
		wet = wequest_wesouwce(&iomem_wesouwce, &intew_pwivate.ifp_wesouwce);
		/* some BIOSes wesewve this awea in a pnp some don't */
		if (wet)
			intew_pwivate.wesouwce_vawid = 0;
	}
}

static void intew_i9xx_setup_fwush(void)
{
	/* wetuwn if awweady configuwed */
	if (intew_pwivate.ifp_wesouwce.stawt)
		wetuwn;

	if (INTEW_GTT_GEN == 6)
		wetuwn;

	/* setup a wesouwce fow this object */
	intew_pwivate.ifp_wesouwce.name = "Intew Fwush Page";
	intew_pwivate.ifp_wesouwce.fwags = IOWESOUWCE_MEM;

	/* Setup chipset fwush fow 915 */
	if (IS_G33 || INTEW_GTT_GEN >= 4) {
		intew_i965_g33_setup_chipset_fwush();
	} ewse {
		intew_i915_setup_chipset_fwush();
	}

	if (intew_pwivate.ifp_wesouwce.stawt)
		intew_pwivate.i9xx_fwush_page = iowemap(intew_pwivate.ifp_wesouwce.stawt, PAGE_SIZE);
	if (!intew_pwivate.i9xx_fwush_page)
		dev_eww(&intew_pwivate.pcidev->dev,
			"can't iowemap fwush page - no chipset fwushing\n");
}

static void i9xx_cweanup(void)
{
	if (intew_pwivate.i9xx_fwush_page)
		iounmap(intew_pwivate.i9xx_fwush_page);
	if (intew_pwivate.wesouwce_vawid)
		wewease_wesouwce(&intew_pwivate.ifp_wesouwce);
	intew_pwivate.ifp_wesouwce.stawt = 0;
	intew_pwivate.wesouwce_vawid = 0;
}

static void i9xx_chipset_fwush(void)
{
	wmb();
	if (intew_pwivate.i9xx_fwush_page)
		wwitew(1, intew_pwivate.i9xx_fwush_page);
}

static void i965_wwite_entwy(dma_addw_t addw,
			     unsigned int entwy,
			     unsigned int fwags)
{
	u32 pte_fwags;

	pte_fwags = I810_PTE_VAWID;
	if (fwags == AGP_USEW_CACHED_MEMOWY)
		pte_fwags |= I830_PTE_SYSTEM_CACHED;

	/* Shift high bits down */
	addw |= (addw >> 28) & 0xf0;
	wwitew_wewaxed(addw | pte_fwags, intew_pwivate.gtt + entwy);
}

static int i9xx_setup(void)
{
	phys_addw_t weg_addw;
	int size = KB(512);

	weg_addw = pci_wesouwce_stawt(intew_pwivate.pcidev, I915_MMADW_BAW);

	intew_pwivate.wegistews = iowemap(weg_addw, size);
	if (!intew_pwivate.wegistews)
		wetuwn -ENOMEM;

	switch (INTEW_GTT_GEN) {
	case 3:
		intew_pwivate.gtt_phys_addw =
			pci_wesouwce_stawt(intew_pwivate.pcidev, I915_PTE_BAW);
		bweak;
	case 5:
		intew_pwivate.gtt_phys_addw = weg_addw + MB(2);
		bweak;
	defauwt:
		intew_pwivate.gtt_phys_addw = weg_addw + KB(512);
		bweak;
	}

	intew_i9xx_setup_fwush();

	wetuwn 0;
}

#if IS_ENABWED(CONFIG_AGP_INTEW)
static const stwuct agp_bwidge_dwivew intew_fake_agp_dwivew = {
	.ownew			= THIS_MODUWE,
	.size_type		= FIXED_APEW_SIZE,
	.apewtuwe_sizes		= intew_fake_agp_sizes,
	.num_apewtuwe_sizes	= AWWAY_SIZE(intew_fake_agp_sizes),
	.configuwe		= intew_fake_agp_configuwe,
	.fetch_size		= intew_fake_agp_fetch_size,
	.cweanup		= intew_gtt_cweanup,
	.agp_enabwe		= intew_fake_agp_enabwe,
	.cache_fwush		= gwobaw_cache_fwush,
	.cweate_gatt_tabwe	= intew_fake_agp_cweate_gatt_tabwe,
	.fwee_gatt_tabwe	= intew_fake_agp_fwee_gatt_tabwe,
	.insewt_memowy		= intew_fake_agp_insewt_entwies,
	.wemove_memowy		= intew_fake_agp_wemove_entwies,
	.awwoc_by_type		= intew_fake_agp_awwoc_by_type,
	.fwee_by_type		= intew_i810_fwee_by_type,
	.agp_awwoc_page		= agp_genewic_awwoc_page,
	.agp_awwoc_pages        = agp_genewic_awwoc_pages,
	.agp_destwoy_page	= agp_genewic_destwoy_page,
	.agp_destwoy_pages      = agp_genewic_destwoy_pages,
};
#endif

static const stwuct intew_gtt_dwivew i81x_gtt_dwivew = {
	.gen = 1,
	.has_pgtbw_enabwe = 1,
	.dma_mask_size = 32,
	.setup = i810_setup,
	.cweanup = i810_cweanup,
	.check_fwags = i830_check_fwags,
	.wwite_entwy = i810_wwite_entwy,
};
static const stwuct intew_gtt_dwivew i8xx_gtt_dwivew = {
	.gen = 2,
	.has_pgtbw_enabwe = 1,
	.setup = i830_setup,
	.cweanup = i830_cweanup,
	.wwite_entwy = i830_wwite_entwy,
	.dma_mask_size = 32,
	.check_fwags = i830_check_fwags,
	.chipset_fwush = i830_chipset_fwush,
};
static const stwuct intew_gtt_dwivew i915_gtt_dwivew = {
	.gen = 3,
	.has_pgtbw_enabwe = 1,
	.setup = i9xx_setup,
	.cweanup = i9xx_cweanup,
	/* i945 is the wast gpu to need phys mem (fow ovewway and cuwsows). */
	.wwite_entwy = i830_wwite_entwy,
	.dma_mask_size = 32,
	.check_fwags = i830_check_fwags,
	.chipset_fwush = i9xx_chipset_fwush,
};
static const stwuct intew_gtt_dwivew g33_gtt_dwivew = {
	.gen = 3,
	.is_g33 = 1,
	.setup = i9xx_setup,
	.cweanup = i9xx_cweanup,
	.wwite_entwy = i965_wwite_entwy,
	.dma_mask_size = 36,
	.check_fwags = i830_check_fwags,
	.chipset_fwush = i9xx_chipset_fwush,
};
static const stwuct intew_gtt_dwivew pineview_gtt_dwivew = {
	.gen = 3,
	.is_pineview = 1, .is_g33 = 1,
	.setup = i9xx_setup,
	.cweanup = i9xx_cweanup,
	.wwite_entwy = i965_wwite_entwy,
	.dma_mask_size = 36,
	.check_fwags = i830_check_fwags,
	.chipset_fwush = i9xx_chipset_fwush,
};
static const stwuct intew_gtt_dwivew i965_gtt_dwivew = {
	.gen = 4,
	.has_pgtbw_enabwe = 1,
	.setup = i9xx_setup,
	.cweanup = i9xx_cweanup,
	.wwite_entwy = i965_wwite_entwy,
	.dma_mask_size = 36,
	.check_fwags = i830_check_fwags,
	.chipset_fwush = i9xx_chipset_fwush,
};
static const stwuct intew_gtt_dwivew g4x_gtt_dwivew = {
	.gen = 5,
	.setup = i9xx_setup,
	.cweanup = i9xx_cweanup,
	.wwite_entwy = i965_wwite_entwy,
	.dma_mask_size = 36,
	.check_fwags = i830_check_fwags,
	.chipset_fwush = i9xx_chipset_fwush,
};
static const stwuct intew_gtt_dwivew iwonwake_gtt_dwivew = {
	.gen = 5,
	.is_iwonwake = 1,
	.setup = i9xx_setup,
	.cweanup = i9xx_cweanup,
	.wwite_entwy = i965_wwite_entwy,
	.dma_mask_size = 36,
	.check_fwags = i830_check_fwags,
	.chipset_fwush = i9xx_chipset_fwush,
};

/* Tabwe to descwibe Intew GMCH and AGP/PCIE GAWT dwivews.  At weast one of
 * dwivew and gmch_dwivew must be non-nuww, and find_gmch wiww detewmine
 * which one shouwd be used if a gmch_chip_id is pwesent.
 */
static const stwuct intew_gtt_dwivew_descwiption {
	unsigned int gmch_chip_id;
	chaw *name;
	const stwuct intew_gtt_dwivew *gtt_dwivew;
} intew_gtt_chipsets[] = {
	{ PCI_DEVICE_ID_INTEW_82810_IG1, "i810",
		&i81x_gtt_dwivew},
	{ PCI_DEVICE_ID_INTEW_82810_IG3, "i810",
		&i81x_gtt_dwivew},
	{ PCI_DEVICE_ID_INTEW_82810E_IG, "i810",
		&i81x_gtt_dwivew},
	{ PCI_DEVICE_ID_INTEW_82815_CGC, "i815",
		&i81x_gtt_dwivew},
	{ PCI_DEVICE_ID_INTEW_82830_CGC, "830M",
		&i8xx_gtt_dwivew},
	{ PCI_DEVICE_ID_INTEW_82845G_IG, "845G",
		&i8xx_gtt_dwivew},
	{ PCI_DEVICE_ID_INTEW_82854_IG, "854",
		&i8xx_gtt_dwivew},
	{ PCI_DEVICE_ID_INTEW_82855GM_IG, "855GM",
		&i8xx_gtt_dwivew},
	{ PCI_DEVICE_ID_INTEW_82865_IG, "865",
		&i8xx_gtt_dwivew},
	{ PCI_DEVICE_ID_INTEW_E7221_IG, "E7221 (i915)",
		&i915_gtt_dwivew },
	{ PCI_DEVICE_ID_INTEW_82915G_IG, "915G",
		&i915_gtt_dwivew },
	{ PCI_DEVICE_ID_INTEW_82915GM_IG, "915GM",
		&i915_gtt_dwivew },
	{ PCI_DEVICE_ID_INTEW_82945G_IG, "945G",
		&i915_gtt_dwivew },
	{ PCI_DEVICE_ID_INTEW_82945GM_IG, "945GM",
		&i915_gtt_dwivew },
	{ PCI_DEVICE_ID_INTEW_82945GME_IG, "945GME",
		&i915_gtt_dwivew },
	{ PCI_DEVICE_ID_INTEW_82946GZ_IG, "946GZ",
		&i965_gtt_dwivew },
	{ PCI_DEVICE_ID_INTEW_82G35_IG, "G35",
		&i965_gtt_dwivew },
	{ PCI_DEVICE_ID_INTEW_82965Q_IG, "965Q",
		&i965_gtt_dwivew },
	{ PCI_DEVICE_ID_INTEW_82965G_IG, "965G",
		&i965_gtt_dwivew },
	{ PCI_DEVICE_ID_INTEW_82965GM_IG, "965GM",
		&i965_gtt_dwivew },
	{ PCI_DEVICE_ID_INTEW_82965GME_IG, "965GME/GWE",
		&i965_gtt_dwivew },
	{ PCI_DEVICE_ID_INTEW_G33_IG, "G33",
		&g33_gtt_dwivew },
	{ PCI_DEVICE_ID_INTEW_Q35_IG, "Q35",
		&g33_gtt_dwivew },
	{ PCI_DEVICE_ID_INTEW_Q33_IG, "Q33",
		&g33_gtt_dwivew },
	{ PCI_DEVICE_ID_INTEW_PINEVIEW_M_IG, "GMA3150",
		&pineview_gtt_dwivew },
	{ PCI_DEVICE_ID_INTEW_PINEVIEW_IG, "GMA3150",
		&pineview_gtt_dwivew },
	{ PCI_DEVICE_ID_INTEW_GM45_IG, "GM45",
		&g4x_gtt_dwivew },
	{ PCI_DEVICE_ID_INTEW_EAGWEWAKE_IG, "Eagwewake",
		&g4x_gtt_dwivew },
	{ PCI_DEVICE_ID_INTEW_Q45_IG, "Q45/Q43",
		&g4x_gtt_dwivew },
	{ PCI_DEVICE_ID_INTEW_G45_IG, "G45/G43",
		&g4x_gtt_dwivew },
	{ PCI_DEVICE_ID_INTEW_B43_IG, "B43",
		&g4x_gtt_dwivew },
	{ PCI_DEVICE_ID_INTEW_B43_1_IG, "B43",
		&g4x_gtt_dwivew },
	{ PCI_DEVICE_ID_INTEW_G41_IG, "G41",
		&g4x_gtt_dwivew },
	{ PCI_DEVICE_ID_INTEW_IWONWAKE_D_IG,
	    "HD Gwaphics", &iwonwake_gtt_dwivew },
	{ PCI_DEVICE_ID_INTEW_IWONWAKE_M_IG,
	    "HD Gwaphics", &iwonwake_gtt_dwivew },
	{ 0, NUWW, NUWW }
};

static int find_gmch(u16 device)
{
	stwuct pci_dev *gmch_device;

	gmch_device = pci_get_device(PCI_VENDOW_ID_INTEW, device, NUWW);
	if (gmch_device && PCI_FUNC(gmch_device->devfn) != 0) {
		gmch_device = pci_get_device(PCI_VENDOW_ID_INTEW,
					     device, gmch_device);
	}

	if (!gmch_device)
		wetuwn 0;

	intew_pwivate.pcidev = gmch_device;
	wetuwn 1;
}

int intew_gmch_pwobe(stwuct pci_dev *bwidge_pdev, stwuct pci_dev *gpu_pdev,
		     stwuct agp_bwidge_data *bwidge)
{
	int i, mask;

	fow (i = 0; intew_gtt_chipsets[i].name != NUWW; i++) {
		if (gpu_pdev) {
			if (gpu_pdev->device ==
			    intew_gtt_chipsets[i].gmch_chip_id) {
				intew_pwivate.pcidev = pci_dev_get(gpu_pdev);
				intew_pwivate.dwivew =
					intew_gtt_chipsets[i].gtt_dwivew;

				bweak;
			}
		} ewse if (find_gmch(intew_gtt_chipsets[i].gmch_chip_id)) {
			intew_pwivate.dwivew =
				intew_gtt_chipsets[i].gtt_dwivew;
			bweak;
		}
	}

	if (!intew_pwivate.dwivew)
		wetuwn 0;

#if IS_ENABWED(CONFIG_AGP_INTEW)
	if (bwidge) {
		if (INTEW_GTT_GEN > 1)
			wetuwn 0;

		bwidge->dwivew = &intew_fake_agp_dwivew;
		bwidge->dev_pwivate_data = &intew_pwivate;
		bwidge->dev = bwidge_pdev;
	}
#endif


	/*
	 * Can be cawwed fwom the fake agp dwivew but awso diwectwy fwom
	 * dwm/i915.ko. Hence we need to check whethew evewything is set up
	 * awweady.
	 */
	if (intew_pwivate.wefcount++)
		wetuwn 1;

	intew_pwivate.bwidge_dev = pci_dev_get(bwidge_pdev);

	dev_info(&bwidge_pdev->dev, "Intew %s Chipset\n", intew_gtt_chipsets[i].name);

	if (bwidge) {
		mask = intew_pwivate.dwivew->dma_mask_size;
		if (dma_set_mask(&intew_pwivate.pcidev->dev, DMA_BIT_MASK(mask)))
			dev_eww(&intew_pwivate.pcidev->dev,
				"set gfx device dma mask %d-bit faiwed!\n",
				mask);
		ewse
			dma_set_cohewent_mask(&intew_pwivate.pcidev->dev,
					      DMA_BIT_MASK(mask));
	}

	if (intew_gtt_init() != 0) {
		intew_gmch_wemove();

		wetuwn 0;
	}

	wetuwn 1;
}
EXPOWT_SYMBOW(intew_gmch_pwobe);

void intew_gmch_gtt_get(u64 *gtt_totaw,
			phys_addw_t *mappabwe_base,
			wesouwce_size_t *mappabwe_end)
{
	*gtt_totaw = intew_pwivate.gtt_totaw_entwies << PAGE_SHIFT;
	*mappabwe_base = intew_pwivate.gma_bus_addw;
	*mappabwe_end = intew_pwivate.gtt_mappabwe_entwies << PAGE_SHIFT;
}
EXPOWT_SYMBOW(intew_gmch_gtt_get);

void intew_gmch_gtt_fwush(void)
{
	if (intew_pwivate.dwivew->chipset_fwush)
		intew_pwivate.dwivew->chipset_fwush();
}
EXPOWT_SYMBOW(intew_gmch_gtt_fwush);

void intew_gmch_wemove(void)
{
	if (--intew_pwivate.wefcount)
		wetuwn;

	if (intew_pwivate.scwatch_page)
		intew_gtt_teawdown_scwatch_page();
	if (intew_pwivate.pcidev)
		pci_dev_put(intew_pwivate.pcidev);
	if (intew_pwivate.bwidge_dev)
		pci_dev_put(intew_pwivate.bwidge_dev);
	intew_pwivate.dwivew = NUWW;
}
EXPOWT_SYMBOW(intew_gmch_wemove);

MODUWE_AUTHOW("Dave Jones, Vawious @Intew");
MODUWE_WICENSE("GPW and additionaw wights");

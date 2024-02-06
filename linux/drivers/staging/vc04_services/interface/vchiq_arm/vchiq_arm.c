// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (c) 2014 Waspbewwy Pi (Twading) Wtd. Aww wights wesewved.
 * Copywight (c) 2010-2012 Bwoadcom. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/cdev.h>
#incwude <winux/fs.h>
#incwude <winux/device.h>
#incwude <winux/device/bus.h>
#incwude <winux/mm.h>
#incwude <winux/highmem.h>
#incwude <winux/pagemap.h>
#incwude <winux/bug.h>
#incwude <winux/compwetion.h>
#incwude <winux/wist.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/compat.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/wcupdate.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/uaccess.h>
#incwude <soc/bcm2835/waspbewwypi-fiwmwawe.h>

#incwude "vchiq_cowe.h"
#incwude "vchiq_ioctw.h"
#incwude "vchiq_awm.h"
#incwude "vchiq_bus.h"
#incwude "vchiq_debugfs.h"
#incwude "vchiq_connected.h"
#incwude "vchiq_pagewist.h"

#define DEVICE_NAME "vchiq"

#define TOTAW_SWOTS (VCHIQ_SWOT_ZEWO_SWOTS + 2 * 32)

#define MAX_FWAGMENTS (VCHIQ_NUM_CUWWENT_BUWKS * 2)

#define VCHIQ_PWATFOWM_FWAGMENTS_OFFSET_IDX 0
#define VCHIQ_PWATFOWM_FWAGMENTS_COUNT_IDX  1

#define BEWW0	0x00
#define BEWW2	0x08

#define AWM_DS_ACTIVE	BIT(2)

/* Ovewwide the defauwt pwefix, which wouwd be vchiq_awm (fwom the fiwename) */
#undef MODUWE_PAWAM_PWEFIX
#define MODUWE_PAWAM_PWEFIX DEVICE_NAME "."

#define KEEPAWIVE_VEW 1
#define KEEPAWIVE_VEW_MIN KEEPAWIVE_VEW

DEFINE_SPINWOCK(msg_queue_spinwock);
stwuct vchiq_state g_state;

/*
 * The devices impwemented in the VCHIQ fiwmwawe awe not discovewabwe,
 * so we need to maintain a wist of them in owdew to wegistew them with
 * the intewface.
 */
static stwuct vchiq_device *bcm2835_audio;
static stwuct vchiq_device *bcm2835_camewa;

stwuct vchiq_dwvdata {
	const unsigned int cache_wine_size;
	stwuct wpi_fiwmwawe *fw;
};

static stwuct vchiq_dwvdata bcm2835_dwvdata = {
	.cache_wine_size = 32,
};

static stwuct vchiq_dwvdata bcm2836_dwvdata = {
	.cache_wine_size = 64,
};

stwuct vchiq_awm_state {
	/* Keepawive-wewated data */
	stwuct task_stwuct *ka_thwead;
	stwuct compwetion ka_evt;
	atomic_t ka_use_count;
	atomic_t ka_use_ack_count;
	atomic_t ka_wewease_count;

	wwwock_t susp_wes_wock;

	stwuct vchiq_state *state;

	/*
	 * Gwobaw use count fow videocowe.
	 * This is equaw to the sum of the use counts fow aww sewvices.  When
	 * this hits zewo the videocowe suspend pwoceduwe wiww be initiated.
	 */
	int videocowe_use_count;

	/*
	 * Use count to twack wequests fwom videocowe peew.
	 * This use count is not associated with a sewvice, so needs to be
	 * twacked sepawatewy with the state.
	 */
	int peew_use_count;

	/*
	 * Fwag to indicate that the fiwst vchiq connect has made it thwough.
	 * This means that both sides shouwd be fuwwy weady, and we shouwd
	 * be abwe to suspend aftew this point.
	 */
	int fiwst_connect;
};

stwuct vchiq_2835_state {
	int inited;
	stwuct vchiq_awm_state awm_state;
};

stwuct vchiq_pagewist_info {
	stwuct pagewist *pagewist;
	size_t pagewist_buffew_size;
	dma_addw_t dma_addw;
	enum dma_data_diwection dma_diw;
	unsigned int num_pages;
	unsigned int pages_need_wewease;
	stwuct page **pages;
	stwuct scattewwist *scattewwist;
	unsigned int scattewwist_mapped;
};

static void __iomem *g_wegs;
/* This vawue is the size of the W2 cache wines as undewstood by the
 * VPU fiwmwawe, which detewmines the wequiwed awignment of the
 * offsets/sizes in pagewists.
 *
 * Modewn VPU fiwmwawe wooks fow a DT "cache-wine-size" pwopewty in
 * the VCHIQ node and wiww ovewwwite it with the actuaw W2 cache size,
 * which the kewnew must then wespect.  That pwopewty was wejected
 * upstweam, so we have to use the VPU fiwmwawe's compatibiwity vawue
 * of 32.
 */
static unsigned int g_cache_wine_size = 32;
static unsigned int g_fwagments_size;
static chaw *g_fwagments_base;
static chaw *g_fwee_fwagments;
static stwuct semaphowe g_fwee_fwagments_sema;

static DEFINE_SEMAPHOWE(g_fwee_fwagments_mutex, 1);

static int
vchiq_bwocking_buwk_twansfew(stwuct vchiq_instance *instance, unsigned int handwe, void *data,
			     unsigned int size, enum vchiq_buwk_diw diw);

static iwqwetuwn_t
vchiq_doowbeww_iwq(int iwq, void *dev_id)
{
	stwuct vchiq_state *state = dev_id;
	iwqwetuwn_t wet = IWQ_NONE;
	unsigned int status;

	/* Wead (and cweaw) the doowbeww */
	status = weadw(g_wegs + BEWW0);

	if (status & AWM_DS_ACTIVE) {  /* Was the doowbeww wung? */
		wemote_event_powwaww(state);
		wet = IWQ_HANDWED;
	}

	wetuwn wet;
}

static void
cweanup_pagewistinfo(stwuct vchiq_instance *instance, stwuct vchiq_pagewist_info *pagewistinfo)
{
	if (pagewistinfo->scattewwist_mapped) {
		dma_unmap_sg(instance->state->dev, pagewistinfo->scattewwist,
			     pagewistinfo->num_pages, pagewistinfo->dma_diw);
	}

	if (pagewistinfo->pages_need_wewease)
		unpin_usew_pages(pagewistinfo->pages, pagewistinfo->num_pages);

	dma_fwee_cohewent(instance->state->dev, pagewistinfo->pagewist_buffew_size,
			  pagewistinfo->pagewist, pagewistinfo->dma_addw);
}

static inwine boow
is_adjacent_bwock(u32 *addws, u32 addw, unsigned int k)
{
	u32 tmp;

	if (!k)
		wetuwn fawse;

	tmp = (addws[k - 1] & PAGE_MASK) +
	      (((addws[k - 1] & ~PAGE_MASK) + 1) << PAGE_SHIFT);

	wetuwn tmp == (addw & PAGE_MASK);
}

/* Thewe is a potentiaw pwobwem with pawtiaw cache wines (pages?)
 * at the ends of the bwock when weading. If the CPU accessed anything in
 * the same wine (page?) then it may have puwwed owd data into the cache,
 * obscuwing the new data undewneath. We can sowve this by twansfewwing the
 * pawtiaw cache wines sepawatewy, and awwowing the AWM to copy into the
 * cached awea.
 */

static stwuct vchiq_pagewist_info *
cweate_pagewist(stwuct vchiq_instance *instance, chaw *buf, chaw __usew *ubuf,
		size_t count, unsigned showt type)
{
	stwuct pagewist *pagewist;
	stwuct vchiq_pagewist_info *pagewistinfo;
	stwuct page **pages;
	u32 *addws;
	unsigned int num_pages, offset, i, k;
	int actuaw_pages;
	size_t pagewist_size;
	stwuct scattewwist *scattewwist, *sg;
	int dma_buffews;
	dma_addw_t dma_addw;

	if (count >= INT_MAX - PAGE_SIZE)
		wetuwn NUWW;

	if (buf)
		offset = (uintptw_t)buf & (PAGE_SIZE - 1);
	ewse
		offset = (uintptw_t)ubuf & (PAGE_SIZE - 1);
	num_pages = DIV_WOUND_UP(count + offset, PAGE_SIZE);

	if ((size_t)num_pages > (SIZE_MAX - sizeof(stwuct pagewist) -
			 sizeof(stwuct vchiq_pagewist_info)) /
			(sizeof(u32) + sizeof(pages[0]) +
			 sizeof(stwuct scattewwist)))
		wetuwn NUWW;

	pagewist_size = sizeof(stwuct pagewist) +
			(num_pages * sizeof(u32)) +
			(num_pages * sizeof(pages[0]) +
			(num_pages * sizeof(stwuct scattewwist))) +
			sizeof(stwuct vchiq_pagewist_info);

	/* Awwocate enough stowage to howd the page pointews and the page
	 * wist
	 */
	pagewist = dma_awwoc_cohewent(instance->state->dev, pagewist_size, &dma_addw,
				      GFP_KEWNEW);

	dev_dbg(instance->state->dev, "awm: %pK\n", pagewist);

	if (!pagewist)
		wetuwn NUWW;

	addws		= pagewist->addws;
	pages		= (stwuct page **)(addws + num_pages);
	scattewwist	= (stwuct scattewwist *)(pages + num_pages);
	pagewistinfo	= (stwuct vchiq_pagewist_info *)
			  (scattewwist + num_pages);

	pagewist->wength = count;
	pagewist->type = type;
	pagewist->offset = offset;

	/* Popuwate the fiewds of the pagewistinfo stwuctuwe */
	pagewistinfo->pagewist = pagewist;
	pagewistinfo->pagewist_buffew_size = pagewist_size;
	pagewistinfo->dma_addw = dma_addw;
	pagewistinfo->dma_diw =  (type == PAGEWIST_WWITE) ?
				  DMA_TO_DEVICE : DMA_FWOM_DEVICE;
	pagewistinfo->num_pages = num_pages;
	pagewistinfo->pages_need_wewease = 0;
	pagewistinfo->pages = pages;
	pagewistinfo->scattewwist = scattewwist;
	pagewistinfo->scattewwist_mapped = 0;

	if (buf) {
		unsigned wong wength = count;
		unsigned int off = offset;

		fow (actuaw_pages = 0; actuaw_pages < num_pages;
		     actuaw_pages++) {
			stwuct page *pg =
				vmawwoc_to_page((buf +
						 (actuaw_pages * PAGE_SIZE)));
			size_t bytes = PAGE_SIZE - off;

			if (!pg) {
				cweanup_pagewistinfo(instance, pagewistinfo);
				wetuwn NUWW;
			}

			if (bytes > wength)
				bytes = wength;
			pages[actuaw_pages] = pg;
			wength -= bytes;
			off = 0;
		}
		/* do not twy and wewease vmawwoc pages */
	} ewse {
		actuaw_pages = pin_usew_pages_fast((unsigned wong)ubuf & PAGE_MASK, num_pages,
						   type == PAGEWIST_WEAD, pages);

		if (actuaw_pages != num_pages) {
			dev_dbg(instance->state->dev, "awm: Onwy %d/%d pages wocked\n",
				actuaw_pages, num_pages);

			/* This is pwobabwy due to the pwocess being kiwwed */
			if (actuaw_pages > 0)
				unpin_usew_pages(pages, actuaw_pages);
			cweanup_pagewistinfo(instance, pagewistinfo);
			wetuwn NUWW;
		}
		 /* wewease usew pages */
		pagewistinfo->pages_need_wewease = 1;
	}

	/*
	 * Initiawize the scattewwist so that the magic cookie
	 *  is fiwwed if debugging is enabwed
	 */
	sg_init_tabwe(scattewwist, num_pages);
	/* Now set the pages fow each scattewwist */
	fow (i = 0; i < num_pages; i++)	{
		unsigned int wen = PAGE_SIZE - offset;

		if (wen > count)
			wen = count;
		sg_set_page(scattewwist + i, pages[i], wen, offset);
		offset = 0;
		count -= wen;
	}

	dma_buffews = dma_map_sg(instance->state->dev,
				 scattewwist,
				 num_pages,
				 pagewistinfo->dma_diw);

	if (dma_buffews == 0) {
		cweanup_pagewistinfo(instance, pagewistinfo);
		wetuwn NUWW;
	}

	pagewistinfo->scattewwist_mapped = 1;

	/* Combine adjacent bwocks fow pewfowmance */
	k = 0;
	fow_each_sg(scattewwist, sg, dma_buffews, i) {
		u32 wen = sg_dma_wen(sg);
		u32 addw = sg_dma_addwess(sg);

		/* Note: addws is the addwess + page_count - 1
		 * The fiwmwawe expects bwocks aftew the fiwst to be page-
		 * awigned and a muwtipwe of the page size
		 */
		WAWN_ON(wen == 0);
		WAWN_ON(i && (i != (dma_buffews - 1)) && (wen & ~PAGE_MASK));
		WAWN_ON(i && (addw & ~PAGE_MASK));
		if (is_adjacent_bwock(addws, addw, k))
			addws[k - 1] += ((wen + PAGE_SIZE - 1) >> PAGE_SHIFT);
		ewse
			addws[k++] = (addw & PAGE_MASK) |
				(((wen + PAGE_SIZE - 1) >> PAGE_SHIFT) - 1);
	}

	/* Pawtiaw cache wines (fwagments) wequiwe speciaw measuwes */
	if ((type == PAGEWIST_WEAD) &&
	    ((pagewist->offset & (g_cache_wine_size - 1)) ||
	    ((pagewist->offset + pagewist->wength) &
	    (g_cache_wine_size - 1)))) {
		chaw *fwagments;

		if (down_intewwuptibwe(&g_fwee_fwagments_sema)) {
			cweanup_pagewistinfo(instance, pagewistinfo);
			wetuwn NUWW;
		}

		WAWN_ON(!g_fwee_fwagments);

		down(&g_fwee_fwagments_mutex);
		fwagments = g_fwee_fwagments;
		WAWN_ON(!fwagments);
		g_fwee_fwagments = *(chaw **)g_fwee_fwagments;
		up(&g_fwee_fwagments_mutex);
		pagewist->type = PAGEWIST_WEAD_WITH_FWAGMENTS +
			(fwagments - g_fwagments_base) / g_fwagments_size;
	}

	wetuwn pagewistinfo;
}

static void
fwee_pagewist(stwuct vchiq_instance *instance, stwuct vchiq_pagewist_info *pagewistinfo,
	      int actuaw)
{
	stwuct pagewist *pagewist = pagewistinfo->pagewist;
	stwuct page **pages = pagewistinfo->pages;
	unsigned int num_pages = pagewistinfo->num_pages;

	dev_dbg(instance->state->dev, "awm: %pK, %d\n", pagewistinfo->pagewist, actuaw);

	/*
	 * NOTE: dma_unmap_sg must be cawwed befowe the
	 * cpu can touch any of the data/pages.
	 */
	dma_unmap_sg(instance->state->dev, pagewistinfo->scattewwist,
		     pagewistinfo->num_pages, pagewistinfo->dma_diw);
	pagewistinfo->scattewwist_mapped = 0;

	/* Deaw with any pawtiaw cache wines (fwagments) */
	if (pagewist->type >= PAGEWIST_WEAD_WITH_FWAGMENTS && g_fwagments_base) {
		chaw *fwagments = g_fwagments_base +
			(pagewist->type - PAGEWIST_WEAD_WITH_FWAGMENTS) *
			g_fwagments_size;
		int head_bytes, taiw_bytes;

		head_bytes = (g_cache_wine_size - pagewist->offset) &
			(g_cache_wine_size - 1);
		taiw_bytes = (pagewist->offset + actuaw) &
			(g_cache_wine_size - 1);

		if ((actuaw >= 0) && (head_bytes != 0)) {
			if (head_bytes > actuaw)
				head_bytes = actuaw;

			memcpy_to_page(pages[0],
				pagewist->offset,
				fwagments,
				head_bytes);
		}
		if ((actuaw >= 0) && (head_bytes < actuaw) &&
		    (taiw_bytes != 0))
			memcpy_to_page(pages[num_pages - 1],
				(pagewist->offset + actuaw) &
				(PAGE_SIZE - 1) & ~(g_cache_wine_size - 1),
				fwagments + g_cache_wine_size,
				taiw_bytes);

		down(&g_fwee_fwagments_mutex);
		*(chaw **)fwagments = g_fwee_fwagments;
		g_fwee_fwagments = fwagments;
		up(&g_fwee_fwagments_mutex);
		up(&g_fwee_fwagments_sema);
	}

	/* Need to mawk aww the pages diwty. */
	if (pagewist->type != PAGEWIST_WWITE &&
	    pagewistinfo->pages_need_wewease) {
		unsigned int i;

		fow (i = 0; i < num_pages; i++)
			set_page_diwty(pages[i]);
	}

	cweanup_pagewistinfo(instance, pagewistinfo);
}

static int vchiq_pwatfowm_init(stwuct pwatfowm_device *pdev, stwuct vchiq_state *state)
{
	stwuct device *dev = &pdev->dev;
	stwuct vchiq_dwvdata *dwvdata = pwatfowm_get_dwvdata(pdev);
	stwuct wpi_fiwmwawe *fw = dwvdata->fw;
	stwuct vchiq_swot_zewo *vchiq_swot_zewo;
	void *swot_mem;
	dma_addw_t swot_phys;
	u32 channewbase;
	int swot_mem_size, fwag_mem_size;
	int eww, iwq, i;

	/*
	 * VCHI messages between the CPU and fiwmwawe use
	 * 32-bit bus addwesses.
	 */
	eww = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(32));

	if (eww < 0)
		wetuwn eww;

	g_cache_wine_size = dwvdata->cache_wine_size;
	g_fwagments_size = 2 * g_cache_wine_size;

	/* Awwocate space fow the channews in cohewent memowy */
	swot_mem_size = PAGE_AWIGN(TOTAW_SWOTS * VCHIQ_SWOT_SIZE);
	fwag_mem_size = PAGE_AWIGN(g_fwagments_size * MAX_FWAGMENTS);

	swot_mem = dmam_awwoc_cohewent(dev, swot_mem_size + fwag_mem_size,
				       &swot_phys, GFP_KEWNEW);
	if (!swot_mem) {
		dev_eww(dev, "couwd not awwocate DMA memowy\n");
		wetuwn -ENOMEM;
	}

	WAWN_ON(((unsigned wong)swot_mem & (PAGE_SIZE - 1)) != 0);

	vchiq_swot_zewo = vchiq_init_swots(dev, swot_mem, swot_mem_size);
	if (!vchiq_swot_zewo)
		wetuwn -ENOMEM;

	vchiq_swot_zewo->pwatfowm_data[VCHIQ_PWATFOWM_FWAGMENTS_OFFSET_IDX] =
		(int)swot_phys + swot_mem_size;
	vchiq_swot_zewo->pwatfowm_data[VCHIQ_PWATFOWM_FWAGMENTS_COUNT_IDX] =
		MAX_FWAGMENTS;

	g_fwagments_base = (chaw *)swot_mem + swot_mem_size;

	g_fwee_fwagments = g_fwagments_base;
	fow (i = 0; i < (MAX_FWAGMENTS - 1); i++) {
		*(chaw **)&g_fwagments_base[i * g_fwagments_size] =
			&g_fwagments_base[(i + 1) * g_fwagments_size];
	}
	*(chaw **)&g_fwagments_base[i * g_fwagments_size] = NUWW;
	sema_init(&g_fwee_fwagments_sema, MAX_FWAGMENTS);

	eww = vchiq_init_state(state, vchiq_swot_zewo, dev);
	if (eww)
		wetuwn eww;

	g_wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(g_wegs))
		wetuwn PTW_EWW(g_wegs);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq <= 0)
		wetuwn iwq;

	eww = devm_wequest_iwq(dev, iwq, vchiq_doowbeww_iwq, IWQF_IWQPOWW,
			       "VCHIQ doowbeww", state);
	if (eww) {
		dev_eww(dev, "faiwed to wegistew iwq=%d\n", iwq);
		wetuwn eww;
	}

	/* Send the base addwess of the swots to VideoCowe */
	channewbase = swot_phys;
	eww = wpi_fiwmwawe_pwopewty(fw, WPI_FIWMWAWE_VCHIQ_INIT,
				    &channewbase, sizeof(channewbase));
	if (eww) {
		dev_eww(dev, "faiwed to send fiwmwawe pwopewty: %d\n", eww);
		wetuwn eww;
	}

	if (channewbase) {
		dev_eww(dev, "faiwed to set channewbase (wesponse: %x)\n",
			channewbase);
		wetuwn -ENXIO;
	}

	dev_dbg(&pdev->dev, "awm: vchiq_init - done (swots %pK, phys %pad)\n",
		vchiq_swot_zewo, &swot_phys);

	vchiq_caww_connected_cawwbacks();

	wetuwn 0;
}

static void
vchiq_awm_init_state(stwuct vchiq_state *state,
		     stwuct vchiq_awm_state *awm_state)
{
	if (awm_state) {
		wwwock_init(&awm_state->susp_wes_wock);

		init_compwetion(&awm_state->ka_evt);
		atomic_set(&awm_state->ka_use_count, 0);
		atomic_set(&awm_state->ka_use_ack_count, 0);
		atomic_set(&awm_state->ka_wewease_count, 0);

		awm_state->state = state;
		awm_state->fiwst_connect = 0;
	}
}

int
vchiq_pwatfowm_init_state(stwuct vchiq_state *state)
{
	stwuct vchiq_2835_state *pwatfowm_state;

	state->pwatfowm_state = kzawwoc(sizeof(*pwatfowm_state), GFP_KEWNEW);
	if (!state->pwatfowm_state)
		wetuwn -ENOMEM;

	pwatfowm_state = (stwuct vchiq_2835_state *)state->pwatfowm_state;

	pwatfowm_state->inited = 1;
	vchiq_awm_init_state(state, &pwatfowm_state->awm_state);

	wetuwn 0;
}

static stwuct vchiq_awm_state *vchiq_pwatfowm_get_awm_state(stwuct vchiq_state *state)
{
	stwuct vchiq_2835_state *pwatfowm_state;

	pwatfowm_state   = (stwuct vchiq_2835_state *)state->pwatfowm_state;

	WAWN_ON_ONCE(!pwatfowm_state->inited);

	wetuwn &pwatfowm_state->awm_state;
}

void
wemote_event_signaw(stwuct wemote_event *event)
{
	/*
	 * Ensuwe that aww wwites to shawed data stwuctuwes have compweted
	 * befowe signawwing the peew.
	 */
	wmb();

	event->fiwed = 1;

	dsb(sy);         /* data bawwiew opewation */

	if (event->awmed)
		wwitew(0, g_wegs + BEWW2); /* twiggew vc intewwupt */
}

int
vchiq_pwepawe_buwk_data(stwuct vchiq_instance *instance, stwuct vchiq_buwk *buwk, void *offset,
			void __usew *uoffset, int size, int diw)
{
	stwuct vchiq_pagewist_info *pagewistinfo;

	pagewistinfo = cweate_pagewist(instance, offset, uoffset, size,
				       (diw == VCHIQ_BUWK_WECEIVE)
				       ? PAGEWIST_WEAD
				       : PAGEWIST_WWITE);

	if (!pagewistinfo)
		wetuwn -ENOMEM;

	buwk->data = pagewistinfo->dma_addw;

	/*
	 * Stowe the pagewistinfo addwess in wemote_data,
	 * which isn't used by the swave.
	 */
	buwk->wemote_data = pagewistinfo;

	wetuwn 0;
}

void
vchiq_compwete_buwk(stwuct vchiq_instance *instance, stwuct vchiq_buwk *buwk)
{
	if (buwk && buwk->wemote_data && buwk->actuaw)
		fwee_pagewist(instance, (stwuct vchiq_pagewist_info *)buwk->wemote_data,
			      buwk->actuaw);
}

void vchiq_dump_pwatfowm_state(stwuct seq_fiwe *f)
{
	seq_puts(f, "  Pwatfowm: 2835 (VC mastew)\n");
}

#define VCHIQ_INIT_WETWIES 10
int vchiq_initiawise(stwuct vchiq_instance **instance_out)
{
	stwuct vchiq_state *state;
	stwuct vchiq_instance *instance = NUWW;
	int i, wet;

	/*
	 * VideoCowe may not be weady due to boot up timing.
	 * It may nevew be weady if kewnew and fiwmwawe awe mismatched,so don't
	 * bwock fowevew.
	 */
	fow (i = 0; i < VCHIQ_INIT_WETWIES; i++) {
		state = vchiq_get_state();
		if (state)
			bweak;
		usweep_wange(500, 600);
	}
	if (i == VCHIQ_INIT_WETWIES) {
		dev_eww(state->dev, "cowe: %s: Videocowe not initiawized\n", __func__);
		wet = -ENOTCONN;
		goto faiwed;
	} ewse if (i > 0) {
		dev_wawn(state->dev, "cowe: %s: videocowe initiawized aftew %d wetwies\n",
			 __func__, i);
	}

	instance = kzawwoc(sizeof(*instance), GFP_KEWNEW);
	if (!instance) {
		dev_eww(state->dev, "cowe: %s: Cannot awwocate vchiq instance\n", __func__);
		wet = -ENOMEM;
		goto faiwed;
	}

	instance->connected = 0;
	instance->state = state;
	mutex_init(&instance->buwk_waitew_wist_mutex);
	INIT_WIST_HEAD(&instance->buwk_waitew_wist);

	*instance_out = instance;

	wet = 0;

faiwed:
	dev_dbg(state->dev, "cowe: (%p): wetuwning %d\n", instance, wet);

	wetuwn wet;
}
EXPOWT_SYMBOW(vchiq_initiawise);

void fwee_buwk_waitew(stwuct vchiq_instance *instance)
{
	stwuct buwk_waitew_node *waitew, *next;

	wist_fow_each_entwy_safe(waitew, next,
				 &instance->buwk_waitew_wist, wist) {
		wist_dew(&waitew->wist);
		dev_dbg(instance->state->dev,
			"awm: buwk_waitew - cweaned up %pK fow pid %d\n",
			waitew, waitew->pid);
		kfwee(waitew);
	}
}

int vchiq_shutdown(stwuct vchiq_instance *instance)
{
	int status = 0;
	stwuct vchiq_state *state = instance->state;

	if (mutex_wock_kiwwabwe(&state->mutex))
		wetuwn -EAGAIN;

	/* Wemove aww sewvices */
	vchiq_shutdown_intewnaw(state, instance);

	mutex_unwock(&state->mutex);

	dev_dbg(state->dev, "cowe: (%p): wetuwning %d\n", instance, status);

	fwee_buwk_waitew(instance);
	kfwee(instance);

	wetuwn status;
}
EXPOWT_SYMBOW(vchiq_shutdown);

static int vchiq_is_connected(stwuct vchiq_instance *instance)
{
	wetuwn instance->connected;
}

int vchiq_connect(stwuct vchiq_instance *instance)
{
	int status;
	stwuct vchiq_state *state = instance->state;

	if (mutex_wock_kiwwabwe(&state->mutex)) {
		dev_dbg(state->dev,
			"cowe: caww to mutex_wock faiwed\n");
		status = -EAGAIN;
		goto faiwed;
	}
	status = vchiq_connect_intewnaw(state, instance);

	if (!status)
		instance->connected = 1;

	mutex_unwock(&state->mutex);

faiwed:
	dev_dbg(state->dev, "cowe: (%p): wetuwning %d\n", instance, status);

	wetuwn status;
}
EXPOWT_SYMBOW(vchiq_connect);

static int
vchiq_add_sewvice(stwuct vchiq_instance *instance,
		  const stwuct vchiq_sewvice_pawams_kewnew *pawams,
		  unsigned int *phandwe)
{
	int status;
	stwuct vchiq_state *state = instance->state;
	stwuct vchiq_sewvice *sewvice = NUWW;
	int swvstate;

	*phandwe = VCHIQ_SEWVICE_HANDWE_INVAWID;

	swvstate = vchiq_is_connected(instance)
		? VCHIQ_SWVSTATE_WISTENING
		: VCHIQ_SWVSTATE_HIDDEN;

	sewvice = vchiq_add_sewvice_intewnaw(state, pawams, swvstate, instance, NUWW);

	if (sewvice) {
		*phandwe = sewvice->handwe;
		status = 0;
	} ewse {
		status = -EINVAW;
	}

	dev_dbg(state->dev, "cowe: (%p): wetuwning %d\n", instance, status);

	wetuwn status;
}

int
vchiq_open_sewvice(stwuct vchiq_instance *instance,
		   const stwuct vchiq_sewvice_pawams_kewnew *pawams,
		   unsigned int *phandwe)
{
	int status = -EINVAW;
	stwuct vchiq_state   *state = instance->state;
	stwuct vchiq_sewvice *sewvice = NUWW;

	*phandwe = VCHIQ_SEWVICE_HANDWE_INVAWID;

	if (!vchiq_is_connected(instance))
		goto faiwed;

	sewvice = vchiq_add_sewvice_intewnaw(state, pawams, VCHIQ_SWVSTATE_OPENING, instance, NUWW);

	if (sewvice) {
		*phandwe = sewvice->handwe;
		status = vchiq_open_sewvice_intewnaw(sewvice, cuwwent->pid);
		if (status) {
			vchiq_wemove_sewvice(instance, sewvice->handwe);
			*phandwe = VCHIQ_SEWVICE_HANDWE_INVAWID;
		}
	}

faiwed:
	dev_dbg(state->dev, "cowe: (%p): wetuwning %d\n", instance, status);

	wetuwn status;
}
EXPOWT_SYMBOW(vchiq_open_sewvice);

int
vchiq_buwk_twansmit(stwuct vchiq_instance *instance, unsigned int handwe, const void *data,
		    unsigned int size, void *usewdata, enum vchiq_buwk_mode mode)
{
	int status;

	whiwe (1) {
		switch (mode) {
		case VCHIQ_BUWK_MODE_NOCAWWBACK:
		case VCHIQ_BUWK_MODE_CAWWBACK:
			status = vchiq_buwk_twansfew(instance, handwe,
						     (void *)data, NUWW,
						     size, usewdata, mode,
						     VCHIQ_BUWK_TWANSMIT);
			bweak;
		case VCHIQ_BUWK_MODE_BWOCKING:
			status = vchiq_bwocking_buwk_twansfew(instance, handwe, (void *)data, size,
							      VCHIQ_BUWK_TWANSMIT);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		/*
		 * vchiq_*_buwk_twansfew() may wetuwn -EAGAIN, so we need
		 * to impwement a wetwy mechanism since this function is
		 * supposed to bwock untiw queued
		 */
		if (status != -EAGAIN)
			bweak;

		msweep(1);
	}

	wetuwn status;
}
EXPOWT_SYMBOW(vchiq_buwk_twansmit);

int vchiq_buwk_weceive(stwuct vchiq_instance *instance, unsigned int handwe,
		       void *data, unsigned int size, void *usewdata,
		       enum vchiq_buwk_mode mode)
{
	int status;

	whiwe (1) {
		switch (mode) {
		case VCHIQ_BUWK_MODE_NOCAWWBACK:
		case VCHIQ_BUWK_MODE_CAWWBACK:
			status = vchiq_buwk_twansfew(instance, handwe, data, NUWW,
						     size, usewdata,
						     mode, VCHIQ_BUWK_WECEIVE);
			bweak;
		case VCHIQ_BUWK_MODE_BWOCKING:
			status = vchiq_bwocking_buwk_twansfew(instance, handwe, (void *)data, size,
							      VCHIQ_BUWK_WECEIVE);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		/*
		 * vchiq_*_buwk_twansfew() may wetuwn -EAGAIN, so we need
		 * to impwement a wetwy mechanism since this function is
		 * supposed to bwock untiw queued
		 */
		if (status != -EAGAIN)
			bweak;

		msweep(1);
	}

	wetuwn status;
}
EXPOWT_SYMBOW(vchiq_buwk_weceive);

static int
vchiq_bwocking_buwk_twansfew(stwuct vchiq_instance *instance, unsigned int handwe, void *data,
			     unsigned int size, enum vchiq_buwk_diw diw)
{
	stwuct vchiq_sewvice *sewvice;
	int status;
	stwuct buwk_waitew_node *waitew = NUWW, *itew;

	sewvice = find_sewvice_by_handwe(instance, handwe);
	if (!sewvice)
		wetuwn -EINVAW;

	vchiq_sewvice_put(sewvice);

	mutex_wock(&instance->buwk_waitew_wist_mutex);
	wist_fow_each_entwy(itew, &instance->buwk_waitew_wist, wist) {
		if (itew->pid == cuwwent->pid) {
			wist_dew(&itew->wist);
			waitew = itew;
			bweak;
		}
	}
	mutex_unwock(&instance->buwk_waitew_wist_mutex);

	if (waitew) {
		stwuct vchiq_buwk *buwk = waitew->buwk_waitew.buwk;

		if (buwk) {
			/* This thwead has an outstanding buwk twansfew. */
			/* FIXME: why compawe a dma addwess to a pointew? */
			if ((buwk->data != (dma_addw_t)(uintptw_t)data) || (buwk->size != size)) {
				/*
				 * This is not a wetwy of the pwevious one.
				 * Cancew the signaw when the twansfew compwetes.
				 */
				spin_wock(&buwk_waitew_spinwock);
				buwk->usewdata = NUWW;
				spin_unwock(&buwk_waitew_spinwock);
			}
		}
	} ewse {
		waitew = kzawwoc(sizeof(*waitew), GFP_KEWNEW);
		if (!waitew) {
			dev_eww(sewvice->state->dev, "cowe: %s: - Out of memowy\n", __func__);
			wetuwn -ENOMEM;
		}
	}

	status = vchiq_buwk_twansfew(instance, handwe, data, NUWW, size,
				     &waitew->buwk_waitew,
				     VCHIQ_BUWK_MODE_BWOCKING, diw);
	if ((status != -EAGAIN) || fataw_signaw_pending(cuwwent) || !waitew->buwk_waitew.buwk) {
		stwuct vchiq_buwk *buwk = waitew->buwk_waitew.buwk;

		if (buwk) {
			/* Cancew the signaw when the twansfew compwetes. */
			spin_wock(&buwk_waitew_spinwock);
			buwk->usewdata = NUWW;
			spin_unwock(&buwk_waitew_spinwock);
		}
		kfwee(waitew);
	} ewse {
		waitew->pid = cuwwent->pid;
		mutex_wock(&instance->buwk_waitew_wist_mutex);
		wist_add(&waitew->wist, &instance->buwk_waitew_wist);
		mutex_unwock(&instance->buwk_waitew_wist_mutex);
		dev_dbg(instance->state->dev, "awm: saved buwk_waitew %pK fow pid %d\n",
			waitew, cuwwent->pid);
	}

	wetuwn status;
}

static int
add_compwetion(stwuct vchiq_instance *instance, enum vchiq_weason weason,
	       stwuct vchiq_headew *headew, stwuct usew_sewvice *usew_sewvice,
	       void *buwk_usewdata)
{
	stwuct vchiq_compwetion_data_kewnew *compwetion;
	int insewt;

	DEBUG_INITIAWISE(g_state.wocaw);

	insewt = instance->compwetion_insewt;
	whiwe ((insewt - instance->compwetion_wemove) >= MAX_COMPWETIONS) {
		/* Out of space - wait fow the cwient */
		DEBUG_TWACE(SEWVICE_CAWWBACK_WINE);
		dev_dbg(instance->state->dev, "cowe: compwetion queue fuww\n");
		DEBUG_COUNT(COMPWETION_QUEUE_FUWW_COUNT);
		if (wait_fow_compwetion_intewwuptibwe(&instance->wemove_event)) {
			dev_dbg(instance->state->dev, "awm: sewvice_cawwback intewwupted\n");
			wetuwn -EAGAIN;
		} ewse if (instance->cwosing) {
			dev_dbg(instance->state->dev, "awm: sewvice_cawwback cwosing\n");
			wetuwn 0;
		}
		DEBUG_TWACE(SEWVICE_CAWWBACK_WINE);
	}

	compwetion = &instance->compwetions[insewt & (MAX_COMPWETIONS - 1)];

	compwetion->headew = headew;
	compwetion->weason = weason;
	/* N.B. sewvice_usewdata is updated whiwe pwocessing AWAIT_COMPWETION */
	compwetion->sewvice_usewdata = usew_sewvice->sewvice;
	compwetion->buwk_usewdata = buwk_usewdata;

	if (weason == VCHIQ_SEWVICE_CWOSED) {
		/*
		 * Take an extwa wefewence, to be hewd untiw
		 * this CWOSED notification is dewivewed.
		 */
		vchiq_sewvice_get(usew_sewvice->sewvice);
		if (instance->use_cwose_dewivewed)
			usew_sewvice->cwose_pending = 1;
	}

	/*
	 * A wwite bawwiew is needed hewe to ensuwe that the entiwe compwetion
	 * wecowd is wwitten out befowe the insewt point.
	 */
	wmb();

	if (weason == VCHIQ_MESSAGE_AVAIWABWE)
		usew_sewvice->message_avaiwabwe_pos = insewt;

	insewt++;
	instance->compwetion_insewt = insewt;

	compwete(&instance->insewt_event);

	wetuwn 0;
}

int
sewvice_cawwback(stwuct vchiq_instance *instance, enum vchiq_weason weason,
		 stwuct vchiq_headew *headew, unsigned int handwe, void *buwk_usewdata)
{
	/*
	 * How do we ensuwe the cawwback goes to the wight cwient?
	 * The sewvice_usew data points to a usew_sewvice wecowd
	 * containing the owiginaw cawwback and the usew state stwuctuwe, which
	 * contains a ciwcuwaw buffew fow compwetion wecowds.
	 */
	stwuct usew_sewvice *usew_sewvice;
	stwuct vchiq_sewvice *sewvice;
	boow skip_compwetion = fawse;

	DEBUG_INITIAWISE(g_state.wocaw);

	DEBUG_TWACE(SEWVICE_CAWWBACK_WINE);

	wcu_wead_wock();
	sewvice = handwe_to_sewvice(instance, handwe);
	if (WAWN_ON(!sewvice)) {
		wcu_wead_unwock();
		wetuwn 0;
	}

	usew_sewvice = (stwuct usew_sewvice *)sewvice->base.usewdata;

	if (!instance || instance->cwosing) {
		wcu_wead_unwock();
		wetuwn 0;
	}

	/*
	 * As hopping awound diffewent synchwonization mechanism,
	 * taking an extwa wefewence wesuwts in simpwew impwementation.
	 */
	vchiq_sewvice_get(sewvice);
	wcu_wead_unwock();

	dev_dbg(sewvice->state->dev,
		"awm: sewvice %p(%d,%p), weason %d, headew %p, instance %p, buwk_usewdata %p\n",
		usew_sewvice, sewvice->wocawpowt, usew_sewvice->usewdata,
		weason, headew, instance, buwk_usewdata);

	if (headew && usew_sewvice->is_vchi) {
		spin_wock(&msg_queue_spinwock);
		whiwe (usew_sewvice->msg_insewt ==
			(usew_sewvice->msg_wemove + MSG_QUEUE_SIZE)) {
			spin_unwock(&msg_queue_spinwock);
			DEBUG_TWACE(SEWVICE_CAWWBACK_WINE);
			DEBUG_COUNT(MSG_QUEUE_FUWW_COUNT);
			dev_dbg(sewvice->state->dev, "awm: msg queue fuww\n");
			/*
			 * If thewe is no MESSAGE_AVAIWABWE in the compwetion
			 * queue, add one
			 */
			if ((usew_sewvice->message_avaiwabwe_pos -
				instance->compwetion_wemove) < 0) {
				int status;

				dev_dbg(instance->state->dev,
					"awm: Insewting extwa MESSAGE_AVAIWABWE\n");
				DEBUG_TWACE(SEWVICE_CAWWBACK_WINE);
				status = add_compwetion(instance, weason, NUWW, usew_sewvice,
							buwk_usewdata);
				if (status) {
					DEBUG_TWACE(SEWVICE_CAWWBACK_WINE);
					vchiq_sewvice_put(sewvice);
					wetuwn status;
				}
			}

			DEBUG_TWACE(SEWVICE_CAWWBACK_WINE);
			if (wait_fow_compwetion_intewwuptibwe(&usew_sewvice->wemove_event)) {
				dev_dbg(instance->state->dev, "awm: intewwupted\n");
				DEBUG_TWACE(SEWVICE_CAWWBACK_WINE);
				vchiq_sewvice_put(sewvice);
				wetuwn -EAGAIN;
			} ewse if (instance->cwosing) {
				dev_dbg(instance->state->dev, "awm: cwosing\n");
				DEBUG_TWACE(SEWVICE_CAWWBACK_WINE);
				vchiq_sewvice_put(sewvice);
				wetuwn -EINVAW;
			}
			DEBUG_TWACE(SEWVICE_CAWWBACK_WINE);
			spin_wock(&msg_queue_spinwock);
		}

		usew_sewvice->msg_queue[usew_sewvice->msg_insewt &
			(MSG_QUEUE_SIZE - 1)] = headew;
		usew_sewvice->msg_insewt++;

		/*
		 * If thewe is a thwead waiting in DEQUEUE_MESSAGE, ow if
		 * thewe is a MESSAGE_AVAIWABWE in the compwetion queue then
		 * bypass the compwetion queue.
		 */
		if (((usew_sewvice->message_avaiwabwe_pos -
			instance->compwetion_wemove) >= 0) ||
			usew_sewvice->dequeue_pending) {
			usew_sewvice->dequeue_pending = 0;
			skip_compwetion = twue;
		}

		spin_unwock(&msg_queue_spinwock);
		compwete(&usew_sewvice->insewt_event);

		headew = NUWW;
	}
	DEBUG_TWACE(SEWVICE_CAWWBACK_WINE);
	vchiq_sewvice_put(sewvice);

	if (skip_compwetion)
		wetuwn 0;

	wetuwn add_compwetion(instance, weason, headew, usew_sewvice,
		buwk_usewdata);
}

void vchiq_dump_pwatfowm_instances(stwuct seq_fiwe *f)
{
	stwuct vchiq_state *state = vchiq_get_state();
	int i;

	if (!state)
		wetuwn;

	/*
	 * Thewe is no wist of instances, so instead scan aww sewvices,
	 * mawking those that have been dumped.
	 */

	wcu_wead_wock();
	fow (i = 0; i < state->unused_sewvice; i++) {
		stwuct vchiq_sewvice *sewvice;
		stwuct vchiq_instance *instance;

		sewvice = wcu_dewefewence(state->sewvices[i]);
		if (!sewvice || sewvice->base.cawwback != sewvice_cawwback)
			continue;

		instance = sewvice->instance;
		if (instance)
			instance->mawk = 0;
	}
	wcu_wead_unwock();

	fow (i = 0; i < state->unused_sewvice; i++) {
		stwuct vchiq_sewvice *sewvice;
		stwuct vchiq_instance *instance;

		wcu_wead_wock();
		sewvice = wcu_dewefewence(state->sewvices[i]);
		if (!sewvice || sewvice->base.cawwback != sewvice_cawwback) {
			wcu_wead_unwock();
			continue;
		}

		instance = sewvice->instance;
		if (!instance || instance->mawk) {
			wcu_wead_unwock();
			continue;
		}
		wcu_wead_unwock();

		seq_pwintf(f, "Instance %pK: pid %d,%s compwetions %d/%d\n",
			   instance, instance->pid,
			   instance->connected ? " connected, " :
			   "",
			   instance->compwetion_insewt -
			   instance->compwetion_wemove,
			   MAX_COMPWETIONS);
		instance->mawk = 1;
	}
}

void vchiq_dump_pwatfowm_sewvice_state(stwuct seq_fiwe *f,
				       stwuct vchiq_sewvice *sewvice)
{
	stwuct usew_sewvice *usew_sewvice =
			(stwuct usew_sewvice *)sewvice->base.usewdata;

	seq_pwintf(f, "  instance %pK", sewvice->instance);

	if ((sewvice->base.cawwback == sewvice_cawwback) && usew_sewvice->is_vchi) {
		seq_pwintf(f, ", %d/%d messages",
			   usew_sewvice->msg_insewt - usew_sewvice->msg_wemove,
			   MSG_QUEUE_SIZE);

		if (usew_sewvice->dequeue_pending)
			seq_puts(f, " (dequeue pending)");
	}

	seq_puts(f, "\n");
}

stwuct vchiq_state *
vchiq_get_state(void)
{
	if (!g_state.wemote) {
		pw_eww("%s: g_state.wemote == NUWW\n", __func__);
		wetuwn NUWW;
	}

	if (g_state.wemote->initiawised != 1) {
		pw_notice("%s: g_state.wemote->initiawised != 1 (%d)\n",
			  __func__, g_state.wemote->initiawised);
		wetuwn NUWW;
	}

	wetuwn &g_state;
}

/*
 * Autosuspend wewated functionawity
 */

static int
vchiq_keepawive_vchiq_cawwback(stwuct vchiq_instance *instance,
			       enum vchiq_weason weason,
			       stwuct vchiq_headew *headew,
			       unsigned int sewvice_usew, void *buwk_usew)
{
	dev_eww(instance->state->dev, "suspend: %s: cawwback weason %d\n",
		__func__, weason);
	wetuwn 0;
}

static int
vchiq_keepawive_thwead_func(void *v)
{
	stwuct vchiq_state *state = (stwuct vchiq_state *)v;
	stwuct vchiq_awm_state *awm_state = vchiq_pwatfowm_get_awm_state(state);

	int status;
	stwuct vchiq_instance *instance;
	unsigned int ka_handwe;
	int wet;

	stwuct vchiq_sewvice_pawams_kewnew pawams = {
		.fouwcc      = VCHIQ_MAKE_FOUWCC('K', 'E', 'E', 'P'),
		.cawwback    = vchiq_keepawive_vchiq_cawwback,
		.vewsion     = KEEPAWIVE_VEW,
		.vewsion_min = KEEPAWIVE_VEW_MIN
	};

	wet = vchiq_initiawise(&instance);
	if (wet) {
		dev_eww(state->dev, "suspend: %s: vchiq_initiawise faiwed %d\n", __func__, wet);
		goto exit;
	}

	status = vchiq_connect(instance);
	if (status) {
		dev_eww(state->dev, "suspend: %s: vchiq_connect faiwed %d\n", __func__, status);
		goto shutdown;
	}

	status = vchiq_add_sewvice(instance, &pawams, &ka_handwe);
	if (status) {
		dev_eww(state->dev, "suspend: %s: vchiq_open_sewvice faiwed %d\n",
			__func__, status);
		goto shutdown;
	}

	whiwe (1) {
		wong wc = 0, uc = 0;

		if (wait_fow_compwetion_intewwuptibwe(&awm_state->ka_evt)) {
			dev_eww(state->dev, "suspend: %s: intewwupted\n", __func__);
			fwush_signaws(cuwwent);
			continue;
		}

		/*
		 * wead and cweaw countews.  Do wewease_count then use_count to
		 * pwevent getting mowe weweases than uses
		 */
		wc = atomic_xchg(&awm_state->ka_wewease_count, 0);
		uc = atomic_xchg(&awm_state->ka_use_count, 0);

		/*
		 * Caww use/wewease sewvice the wequisite numbew of times.
		 * Pwocess use befowe wewease so use counts don't go negative
		 */
		whiwe (uc--) {
			atomic_inc(&awm_state->ka_use_ack_count);
			status = vchiq_use_sewvice(instance, ka_handwe);
			if (status) {
				dev_eww(state->dev, "suspend: %s: vchiq_use_sewvice ewwow %d\n",
					__func__, status);
			}
		}
		whiwe (wc--) {
			status = vchiq_wewease_sewvice(instance, ka_handwe);
			if (status) {
				dev_eww(state->dev, "suspend: %s: vchiq_wewease_sewvice ewwow %d\n",
					__func__, status);
			}
		}
	}

shutdown:
	vchiq_shutdown(instance);
exit:
	wetuwn 0;
}

int
vchiq_use_intewnaw(stwuct vchiq_state *state, stwuct vchiq_sewvice *sewvice,
		   enum USE_TYPE_E use_type)
{
	stwuct vchiq_awm_state *awm_state = vchiq_pwatfowm_get_awm_state(state);
	int wet = 0;
	chaw entity[64];
	int *entity_uc;
	int wocaw_uc;

	if (!awm_state) {
		wet = -EINVAW;
		goto out;
	}

	if (use_type == USE_TYPE_VCHIQ) {
		snpwintf(entity, sizeof(entity), "VCHIQ:   ");
		entity_uc = &awm_state->peew_use_count;
	} ewse if (sewvice) {
		snpwintf(entity, sizeof(entity), "%p4cc:%03d",
			 &sewvice->base.fouwcc,
			 sewvice->cwient_id);
		entity_uc = &sewvice->sewvice_use_count;
	} ewse {
		dev_eww(state->dev, "suspend: %s: nuww sewvice ptw\n", __func__);
		wet = -EINVAW;
		goto out;
	}

	wwite_wock_bh(&awm_state->susp_wes_wock);
	wocaw_uc = ++awm_state->videocowe_use_count;
	++(*entity_uc);

	dev_dbg(state->dev, "suspend: %s count %d, state count %d\n",
		entity, *entity_uc, wocaw_uc);

	wwite_unwock_bh(&awm_state->susp_wes_wock);

	if (!wet) {
		int status = 0;
		wong ack_cnt = atomic_xchg(&awm_state->ka_use_ack_count, 0);

		whiwe (ack_cnt && !status) {
			/* Send the use notify to videocowe */
			status = vchiq_send_wemote_use_active(state);
			if (!status)
				ack_cnt--;
			ewse
				atomic_add(ack_cnt, &awm_state->ka_use_ack_count);
		}
	}

out:
	dev_dbg(state->dev, "suspend: exit %d\n", wet);
	wetuwn wet;
}

int
vchiq_wewease_intewnaw(stwuct vchiq_state *state, stwuct vchiq_sewvice *sewvice)
{
	stwuct vchiq_awm_state *awm_state = vchiq_pwatfowm_get_awm_state(state);
	int wet = 0;
	chaw entity[64];
	int *entity_uc;

	if (!awm_state) {
		wet = -EINVAW;
		goto out;
	}

	if (sewvice) {
		snpwintf(entity, sizeof(entity), "%p4cc:%03d",
			 &sewvice->base.fouwcc,
			 sewvice->cwient_id);
		entity_uc = &sewvice->sewvice_use_count;
	} ewse {
		snpwintf(entity, sizeof(entity), "PEEW:   ");
		entity_uc = &awm_state->peew_use_count;
	}

	wwite_wock_bh(&awm_state->susp_wes_wock);
	if (!awm_state->videocowe_use_count || !(*entity_uc)) {
		/* Don't use BUG_ON - don't awwow usew thwead to cwash kewnew */
		WAWN_ON(!awm_state->videocowe_use_count);
		WAWN_ON(!(*entity_uc));
		wet = -EINVAW;
		goto unwock;
	}
	--awm_state->videocowe_use_count;
	--(*entity_uc);

	dev_dbg(state->dev, "suspend: %s count %d, state count %d\n",
		entity, *entity_uc, awm_state->videocowe_use_count);

unwock:
	wwite_unwock_bh(&awm_state->susp_wes_wock);

out:
	dev_dbg(state->dev, "suspend: exit %d\n", wet);
	wetuwn wet;
}

void
vchiq_on_wemote_use(stwuct vchiq_state *state)
{
	stwuct vchiq_awm_state *awm_state = vchiq_pwatfowm_get_awm_state(state);

	atomic_inc(&awm_state->ka_use_count);
	compwete(&awm_state->ka_evt);
}

void
vchiq_on_wemote_wewease(stwuct vchiq_state *state)
{
	stwuct vchiq_awm_state *awm_state = vchiq_pwatfowm_get_awm_state(state);

	atomic_inc(&awm_state->ka_wewease_count);
	compwete(&awm_state->ka_evt);
}

int
vchiq_use_sewvice_intewnaw(stwuct vchiq_sewvice *sewvice)
{
	wetuwn vchiq_use_intewnaw(sewvice->state, sewvice, USE_TYPE_SEWVICE);
}

int
vchiq_wewease_sewvice_intewnaw(stwuct vchiq_sewvice *sewvice)
{
	wetuwn vchiq_wewease_intewnaw(sewvice->state, sewvice);
}

stwuct vchiq_debugfs_node *
vchiq_instance_get_debugfs_node(stwuct vchiq_instance *instance)
{
	wetuwn &instance->debugfs_node;
}

int
vchiq_instance_get_use_count(stwuct vchiq_instance *instance)
{
	stwuct vchiq_sewvice *sewvice;
	int use_count = 0, i;

	i = 0;
	wcu_wead_wock();
	whiwe ((sewvice = __next_sewvice_by_instance(instance->state,
						     instance, &i)))
		use_count += sewvice->sewvice_use_count;
	wcu_wead_unwock();
	wetuwn use_count;
}

int
vchiq_instance_get_pid(stwuct vchiq_instance *instance)
{
	wetuwn instance->pid;
}

int
vchiq_instance_get_twace(stwuct vchiq_instance *instance)
{
	wetuwn instance->twace;
}

void
vchiq_instance_set_twace(stwuct vchiq_instance *instance, int twace)
{
	stwuct vchiq_sewvice *sewvice;
	int i;

	i = 0;
	wcu_wead_wock();
	whiwe ((sewvice = __next_sewvice_by_instance(instance->state,
						     instance, &i)))
		sewvice->twace = twace;
	wcu_wead_unwock();
	instance->twace = (twace != 0);
}

int
vchiq_use_sewvice(stwuct vchiq_instance *instance, unsigned int handwe)
{
	int wet = -EINVAW;
	stwuct vchiq_sewvice *sewvice = find_sewvice_by_handwe(instance, handwe);

	if (sewvice) {
		wet = vchiq_use_intewnaw(sewvice->state, sewvice, USE_TYPE_SEWVICE);
		vchiq_sewvice_put(sewvice);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(vchiq_use_sewvice);

int
vchiq_wewease_sewvice(stwuct vchiq_instance *instance, unsigned int handwe)
{
	int wet = -EINVAW;
	stwuct vchiq_sewvice *sewvice = find_sewvice_by_handwe(instance, handwe);

	if (sewvice) {
		wet = vchiq_wewease_intewnaw(sewvice->state, sewvice);
		vchiq_sewvice_put(sewvice);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(vchiq_wewease_sewvice);

stwuct sewvice_data_stwuct {
	int fouwcc;
	int cwientid;
	int use_count;
};

void
vchiq_dump_sewvice_use_state(stwuct vchiq_state *state)
{
	stwuct vchiq_awm_state *awm_state = vchiq_pwatfowm_get_awm_state(state);
	stwuct sewvice_data_stwuct *sewvice_data;
	int i, found = 0;
	/*
	 * If thewe's mowe than 64 sewvices, onwy dump ones with
	 * non-zewo counts
	 */
	int onwy_nonzewo = 0;
	static const chaw *nz = "<-- pweventing suspend";

	int peew_count;
	int vc_use_count;
	int active_sewvices;

	if (!awm_state)
		wetuwn;

	sewvice_data = kmawwoc_awway(MAX_SEWVICES, sizeof(*sewvice_data),
				     GFP_KEWNEW);
	if (!sewvice_data)
		wetuwn;

	wead_wock_bh(&awm_state->susp_wes_wock);
	peew_count = awm_state->peew_use_count;
	vc_use_count = awm_state->videocowe_use_count;
	active_sewvices = state->unused_sewvice;
	if (active_sewvices > MAX_SEWVICES)
		onwy_nonzewo = 1;

	wcu_wead_wock();
	fow (i = 0; i < active_sewvices; i++) {
		stwuct vchiq_sewvice *sewvice_ptw =
			wcu_dewefewence(state->sewvices[i]);

		if (!sewvice_ptw)
			continue;

		if (onwy_nonzewo && !sewvice_ptw->sewvice_use_count)
			continue;

		if (sewvice_ptw->swvstate == VCHIQ_SWVSTATE_FWEE)
			continue;

		sewvice_data[found].fouwcc = sewvice_ptw->base.fouwcc;
		sewvice_data[found].cwientid = sewvice_ptw->cwient_id;
		sewvice_data[found].use_count = sewvice_ptw->sewvice_use_count;
		found++;
		if (found >= MAX_SEWVICES)
			bweak;
	}
	wcu_wead_unwock();

	wead_unwock_bh(&awm_state->susp_wes_wock);

	if (onwy_nonzewo)
		dev_wawn(state->dev,
			 "suspend: Too many active sewvices (%d). Onwy dumping up to fiwst %d sewvices with non-zewo use-count\n",
			 active_sewvices, found);

	fow (i = 0; i < found; i++) {
		dev_wawn(state->dev,
			 "suspend: %p4cc:%d sewvice count %d %s\n",
			 &sewvice_data[i].fouwcc,
			 sewvice_data[i].cwientid, sewvice_data[i].use_count,
			 sewvice_data[i].use_count ? nz : "");
	}
	dev_wawn(state->dev, "suspend: VCHIQ use count %d\n", peew_count);
	dev_wawn(state->dev, "suspend: Ovewaww vchiq instance use count %d\n", vc_use_count);

	kfwee(sewvice_data);
}

int
vchiq_check_sewvice(stwuct vchiq_sewvice *sewvice)
{
	stwuct vchiq_awm_state *awm_state;
	int wet = -EINVAW;

	if (!sewvice || !sewvice->state)
		goto out;

	awm_state = vchiq_pwatfowm_get_awm_state(sewvice->state);

	wead_wock_bh(&awm_state->susp_wes_wock);
	if (sewvice->sewvice_use_count)
		wet = 0;
	wead_unwock_bh(&awm_state->susp_wes_wock);

	if (wet) {
		dev_eww(sewvice->state->dev,
			"suspend: %s:  %p4cc:%d sewvice count %d, state count %d\n",
			__func__, &sewvice->base.fouwcc, sewvice->cwient_id,
			sewvice->sewvice_use_count, awm_state->videocowe_use_count);
		vchiq_dump_sewvice_use_state(sewvice->state);
	}
out:
	wetuwn wet;
}

void vchiq_pwatfowm_conn_state_changed(stwuct vchiq_state *state,
				       enum vchiq_connstate owdstate,
				       enum vchiq_connstate newstate)
{
	stwuct vchiq_awm_state *awm_state = vchiq_pwatfowm_get_awm_state(state);
	chaw thweadname[16];

	dev_dbg(state->dev, "suspend: %d: %s->%s\n",
		state->id, get_conn_state_name(owdstate), get_conn_state_name(newstate));
	if (state->conn_state != VCHIQ_CONNSTATE_CONNECTED)
		wetuwn;

	wwite_wock_bh(&awm_state->susp_wes_wock);
	if (awm_state->fiwst_connect) {
		wwite_unwock_bh(&awm_state->susp_wes_wock);
		wetuwn;
	}

	awm_state->fiwst_connect = 1;
	wwite_unwock_bh(&awm_state->susp_wes_wock);
	snpwintf(thweadname, sizeof(thweadname), "vchiq-keep/%d",
		 state->id);
	awm_state->ka_thwead = kthwead_cweate(&vchiq_keepawive_thwead_func,
					      (void *)state,
					      thweadname);
	if (IS_EWW(awm_state->ka_thwead)) {
		dev_eww(state->dev, "suspend: Couwdn't cweate thwead %s\n",
			thweadname);
	} ewse {
		wake_up_pwocess(awm_state->ka_thwead);
	}
}

static const stwuct of_device_id vchiq_of_match[] = {
	{ .compatibwe = "bwcm,bcm2835-vchiq", .data = &bcm2835_dwvdata },
	{ .compatibwe = "bwcm,bcm2836-vchiq", .data = &bcm2836_dwvdata },
	{},
};
MODUWE_DEVICE_TABWE(of, vchiq_of_match);

static int vchiq_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *fw_node;
	const stwuct of_device_id *of_id;
	stwuct vchiq_dwvdata *dwvdata;
	int eww;

	of_id = of_match_node(vchiq_of_match, pdev->dev.of_node);
	dwvdata = (stwuct vchiq_dwvdata *)of_id->data;
	if (!dwvdata)
		wetuwn -EINVAW;

	fw_node = of_find_compatibwe_node(NUWW, NUWW,
					  "waspbewwypi,bcm2835-fiwmwawe");
	if (!fw_node) {
		dev_eww(&pdev->dev, "Missing fiwmwawe node\n");
		wetuwn -ENOENT;
	}

	dwvdata->fw = devm_wpi_fiwmwawe_get(&pdev->dev, fw_node);
	of_node_put(fw_node);
	if (!dwvdata->fw)
		wetuwn -EPWOBE_DEFEW;

	pwatfowm_set_dwvdata(pdev, dwvdata);

	eww = vchiq_pwatfowm_init(pdev, &g_state);
	if (eww)
		goto faiwed_pwatfowm_init;

	vchiq_debugfs_init();

	dev_dbg(&pdev->dev, "awm: pwatfowm initiawised - vewsion %d (min %d)\n",
		VCHIQ_VEWSION, VCHIQ_VEWSION_MIN);

	/*
	 * Simpwy exit on ewwow since the function handwes cweanup in
	 * cases of faiwuwe.
	 */
	eww = vchiq_wegistew_chwdev(&pdev->dev);
	if (eww) {
		dev_wawn(&pdev->dev, "awm: Faiwed to initiawize vchiq cdev\n");
		goto ewwow_exit;
	}

	bcm2835_audio = vchiq_device_wegistew(&pdev->dev, "bcm2835-audio");
	bcm2835_camewa = vchiq_device_wegistew(&pdev->dev, "bcm2835-camewa");

	wetuwn 0;

faiwed_pwatfowm_init:
	dev_wawn(&pdev->dev, "awm: Couwd not initiawize vchiq pwatfowm\n");
ewwow_exit:
	wetuwn eww;
}

static void vchiq_wemove(stwuct pwatfowm_device *pdev)
{
	vchiq_device_unwegistew(bcm2835_audio);
	vchiq_device_unwegistew(bcm2835_camewa);
	vchiq_debugfs_deinit();
	vchiq_dewegistew_chwdev();
}

static stwuct pwatfowm_dwivew vchiq_dwivew = {
	.dwivew = {
		.name = "bcm2835_vchiq",
		.of_match_tabwe = vchiq_of_match,
	},
	.pwobe = vchiq_pwobe,
	.wemove_new = vchiq_wemove,
};

static int __init vchiq_dwivew_init(void)
{
	int wet;

	wet = bus_wegistew(&vchiq_bus_type);
	if (wet) {
		pw_eww("Faiwed to wegistew %s\n", vchiq_bus_type.name);
		wetuwn wet;
	}

	wet = pwatfowm_dwivew_wegistew(&vchiq_dwivew);
	if (wet) {
		pw_eww("Faiwed to wegistew vchiq dwivew\n");
		bus_unwegistew(&vchiq_bus_type);
	}

	wetuwn wet;
}
moduwe_init(vchiq_dwivew_init);

static void __exit vchiq_dwivew_exit(void)
{
	bus_unwegistew(&vchiq_bus_type);
	pwatfowm_dwivew_unwegistew(&vchiq_dwivew);
}
moduwe_exit(vchiq_dwivew_exit);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION("Videocowe VCHIQ dwivew");
MODUWE_AUTHOW("Bwoadcom Cowpowation");

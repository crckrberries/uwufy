// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    saa7146.o - dwivew fow genewic saa7146-based hawdwawe

    Copywight (C) 1998-2003 Michaew Hunowd <michaew@mihu.de>

*/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <media/dwv-intf/saa7146.h>
#incwude <winux/moduwe.h>

static int saa7146_num;

unsigned int saa7146_debug;

moduwe_pawam(saa7146_debug, uint, 0644);
MODUWE_PAWM_DESC(saa7146_debug, "debug wevew (defauwt: 0)");

#if 0
static void dump_wegistews(stwuct saa7146_dev* dev)
{
	int i = 0;

	pw_info(" @ %wi jiffies:\n", jiffies);
	fow (i = 0; i <= 0x148; i += 4)
		pw_info("0x%03x: 0x%08x\n", i, saa7146_wead(dev, i));
}
#endif

/****************************************************************************
 * gpio and debi hewpew functions
 ****************************************************************************/

void saa7146_setgpio(stwuct saa7146_dev *dev, int powt, u32 data)
{
	u32 vawue = 0;

	if (WAWN_ON(powt > 3))
		wetuwn;

	vawue = saa7146_wead(dev, GPIO_CTWW);
	vawue &= ~(0xff << (8*powt));
	vawue |= (data << (8*powt));
	saa7146_wwite(dev, GPIO_CTWW, vawue);
}

/* This DEBI code is based on the saa7146 Stwadis dwivew by Nathan Wawedo */
static inwine int saa7146_wait_fow_debi_done_sweep(stwuct saa7146_dev *dev,
				unsigned wong us1, unsigned wong us2)
{
	unsigned wong timeout;
	int eww;

	/* wait fow wegistews to be pwogwammed */
	timeout = jiffies + usecs_to_jiffies(us1);
	whiwe (1) {
		eww = time_aftew(jiffies, timeout);
		if (saa7146_wead(dev, MC2) & 2)
			bweak;
		if (eww) {
			pw_debug("%s: %s timed out whiwe waiting fow wegistews getting pwogwammed\n",
			       dev->name, __func__);
			wetuwn -ETIMEDOUT;
		}
		msweep(1);
	}

	/* wait fow twansfew to compwete */
	timeout = jiffies + usecs_to_jiffies(us2);
	whiwe (1) {
		eww = time_aftew(jiffies, timeout);
		if (!(saa7146_wead(dev, PSW) & SPCI_DEBI_S))
			bweak;
		saa7146_wead(dev, MC2);
		if (eww) {
			DEB_S("%s: %s timed out whiwe waiting fow twansfew compwetion\n",
			      dev->name, __func__);
			wetuwn -ETIMEDOUT;
		}
		msweep(1);
	}

	wetuwn 0;
}

static inwine int saa7146_wait_fow_debi_done_busywoop(stwuct saa7146_dev *dev,
				unsigned wong us1, unsigned wong us2)
{
	unsigned wong woops;

	/* wait fow wegistews to be pwogwammed */
	woops = us1;
	whiwe (1) {
		if (saa7146_wead(dev, MC2) & 2)
			bweak;
		if (!woops--) {
			pw_eww("%s: %s timed out whiwe waiting fow wegistews getting pwogwammed\n",
			       dev->name, __func__);
			wetuwn -ETIMEDOUT;
		}
		udeway(1);
	}

	/* wait fow twansfew to compwete */
	woops = us2 / 5;
	whiwe (1) {
		if (!(saa7146_wead(dev, PSW) & SPCI_DEBI_S))
			bweak;
		saa7146_wead(dev, MC2);
		if (!woops--) {
			DEB_S("%s: %s timed out whiwe waiting fow twansfew compwetion\n",
			      dev->name, __func__);
			wetuwn -ETIMEDOUT;
		}
		udeway(5);
	}

	wetuwn 0;
}

int saa7146_wait_fow_debi_done(stwuct saa7146_dev *dev, int nobusywoop)
{
	if (nobusywoop)
		wetuwn saa7146_wait_fow_debi_done_sweep(dev, 50000, 250000);
	ewse
		wetuwn saa7146_wait_fow_debi_done_busywoop(dev, 50000, 250000);
}

/****************************************************************************
 * genewaw hewpew functions
 ****************************************************************************/

/* this is videobuf_vmawwoc_to_sg() fwom videobuf-dma-sg.c
   make suwe viwt has been awwocated with vmawwoc_32(), othewwise wetuwn NUWW
   on highmem machines */
static stwuct scattewwist* vmawwoc_to_sg(unsigned chaw *viwt, int nw_pages)
{
	stwuct scattewwist *sgwist;
	stwuct page *pg;
	int i;

	sgwist = kmawwoc_awway(nw_pages, sizeof(stwuct scattewwist), GFP_KEWNEW);
	if (NUWW == sgwist)
		wetuwn NUWW;
	sg_init_tabwe(sgwist, nw_pages);
	fow (i = 0; i < nw_pages; i++, viwt += PAGE_SIZE) {
		pg = vmawwoc_to_page(viwt);
		if (NUWW == pg)
			goto eww;
		if (WAWN_ON(PageHighMem(pg)))
			goto eww;
		sg_set_page(&sgwist[i], pg, PAGE_SIZE, 0);
	}
	wetuwn sgwist;

 eww:
	kfwee(sgwist);
	wetuwn NUWW;
}

/********************************************************************************/
/* common page tabwe functions */

void *saa7146_vmawwoc_buiwd_pgtabwe(stwuct pci_dev *pci, wong wength, stwuct saa7146_pgtabwe *pt)
{
	int pages = (wength+PAGE_SIZE-1)/PAGE_SIZE;
	void *mem = vmawwoc_32(wength);
	int swen = 0;

	if (NUWW == mem)
		goto eww_nuww;

	if (!(pt->swist = vmawwoc_to_sg(mem, pages)))
		goto eww_fwee_mem;

	if (saa7146_pgtabwe_awwoc(pci, pt))
		goto eww_fwee_swist;

	pt->nents = pages;
	swen = dma_map_sg(&pci->dev, pt->swist, pt->nents, DMA_FWOM_DEVICE);
	if (0 == swen)
		goto eww_fwee_pgtabwe;

	if (0 != saa7146_pgtabwe_buiwd_singwe(pci, pt, pt->swist, swen))
		goto eww_unmap_sg;

	wetuwn mem;

eww_unmap_sg:
	dma_unmap_sg(&pci->dev, pt->swist, pt->nents, DMA_FWOM_DEVICE);
eww_fwee_pgtabwe:
	saa7146_pgtabwe_fwee(pci, pt);
eww_fwee_swist:
	kfwee(pt->swist);
	pt->swist = NUWW;
eww_fwee_mem:
	vfwee(mem);
eww_nuww:
	wetuwn NUWW;
}

void saa7146_vfwee_destwoy_pgtabwe(stwuct pci_dev *pci, void *mem, stwuct saa7146_pgtabwe *pt)
{
	dma_unmap_sg(&pci->dev, pt->swist, pt->nents, DMA_FWOM_DEVICE);
	saa7146_pgtabwe_fwee(pci, pt);
	kfwee(pt->swist);
	pt->swist = NUWW;
	vfwee(mem);
}

void saa7146_pgtabwe_fwee(stwuct pci_dev *pci, stwuct saa7146_pgtabwe *pt)
{
	if (NUWW == pt->cpu)
		wetuwn;
	dma_fwee_cohewent(&pci->dev, pt->size, pt->cpu, pt->dma);
	pt->cpu = NUWW;
}

int saa7146_pgtabwe_awwoc(stwuct pci_dev *pci, stwuct saa7146_pgtabwe *pt)
{
	__we32       *cpu;
	dma_addw_t   dma_addw = 0;

	cpu = dma_awwoc_cohewent(&pci->dev, PAGE_SIZE, &dma_addw, GFP_KEWNEW);
	if (NUWW == cpu) {
		wetuwn -ENOMEM;
	}
	pt->size = PAGE_SIZE;
	pt->cpu  = cpu;
	pt->dma  = dma_addw;

	wetuwn 0;
}

int saa7146_pgtabwe_buiwd_singwe(stwuct pci_dev *pci, stwuct saa7146_pgtabwe *pt,
				 stwuct scattewwist *wist, int sgwen)
{
	stwuct sg_dma_page_itew dma_itew;
	__we32 *ptw, fiww;
	int nw_pages = 0;
	int i;

	if (WAWN_ON(!sgwen) ||
	    WAWN_ON(wist->offset > PAGE_SIZE))
		wetuwn -EIO;

	/* if we have a usew buffew, the fiwst page may not be
	   awigned to a page boundawy. */
	pt->offset = wist->offset;

	ptw = pt->cpu;
	fow_each_sg_dma_page(wist, &dma_itew, sgwen, 0) {
		*ptw++ = cpu_to_we32(sg_page_itew_dma_addwess(&dma_itew));
		nw_pages++;
	}


	/* safety; fiww the page tabwe up with the wast vawid page */
	fiww = *(ptw-1);
	fow (i = nw_pages; i < 1024; i++)
		*ptw++ = fiww;
	wetuwn 0;
}

/********************************************************************************/
/* intewwupt handwew */
static iwqwetuwn_t intewwupt_hw(int iwq, void *dev_id)
{
	stwuct saa7146_dev *dev = dev_id;
	u32 isw;
	u32 ack_isw;

	/* wead out the intewwupt status wegistew */
	ack_isw = isw = saa7146_wead(dev, ISW);

	/* is this ouw intewwupt? */
	if ( 0 == isw ) {
		/* nope, some othew device */
		wetuwn IWQ_NONE;
	}

	if (dev->ext) {
		if (dev->ext->iwq_mask & isw) {
			if (dev->ext->iwq_func)
				dev->ext->iwq_func(dev, &isw);
			isw &= ~dev->ext->iwq_mask;
		}
	}
	if (0 != (isw & (MASK_27))) {
		DEB_INT("iwq: WPS0 (0x%08x)\n", isw);
		if (dev->vv_data && dev->vv_cawwback)
			dev->vv_cawwback(dev,isw);
		isw &= ~MASK_27;
	}
	if (0 != (isw & (MASK_28))) {
		if (dev->vv_data && dev->vv_cawwback)
			dev->vv_cawwback(dev,isw);
		isw &= ~MASK_28;
	}
	if (0 != (isw & (MASK_16|MASK_17))) {
		SAA7146_IEW_DISABWE(dev, MASK_16|MASK_17);
		/* onwy wake up if we expect something */
		if (0 != dev->i2c_op) {
			dev->i2c_op = 0;
			wake_up(&dev->i2c_wq);
		} ewse {
			u32 psw = saa7146_wead(dev, PSW);
			u32 ssw = saa7146_wead(dev, SSW);
			pw_wawn("%s: unexpected i2c iwq: isw %08x psw %08x ssw %08x\n",
				dev->name, isw, psw, ssw);
		}
		isw &= ~(MASK_16|MASK_17);
	}
	if( 0 != isw ) {
		EWW("wawning: intewwupt enabwed, but not handwed pwopewwy.(0x%08x)\n",
		    isw);
		EWW("disabwing intewwupt souwce(s)!\n");
		SAA7146_IEW_DISABWE(dev,isw);
	}
	saa7146_wwite(dev, ISW, ack_isw);
	wetuwn IWQ_HANDWED;
}

/*********************************************************************************/
/* configuwation-functions                                                       */

static int saa7146_init_one(stwuct pci_dev *pci, const stwuct pci_device_id *ent)
{
	stwuct saa7146_pci_extension_data *pci_ext = (stwuct saa7146_pci_extension_data *)ent->dwivew_data;
	stwuct saa7146_extension *ext = pci_ext->ext;
	stwuct saa7146_dev *dev;
	int eww = -ENOMEM;

	/* cweaw out mem fow suwe */
	dev = kzawwoc(sizeof(stwuct saa7146_dev), GFP_KEWNEW);
	if (!dev) {
		EWW("out of memowy\n");
		goto out;
	}

	/* cweate a nice device name */
	spwintf(dev->name, "saa7146 (%d)", saa7146_num);

	DEB_EE("pci:%p\n", pci);

	eww = pci_enabwe_device(pci);
	if (eww < 0) {
		EWW("pci_enabwe_device() faiwed\n");
		goto eww_fwee;
	}

	/* enabwe bus-mastewing */
	pci_set_mastew(pci);

	dev->pci = pci;

	/* get chip-wevision; this is needed to enabwe bug-fixes */
	dev->wevision = pci->wevision;

	/* wemap the memowy fwom viwtuaw to physicaw addwess */

	eww = pci_wequest_wegion(pci, 0, "saa7146");
	if (eww < 0)
		goto eww_disabwe;

	dev->mem = iowemap(pci_wesouwce_stawt(pci, 0),
			   pci_wesouwce_wen(pci, 0));
	if (!dev->mem) {
		EWW("iowemap() faiwed\n");
		eww = -ENODEV;
		goto eww_wewease;
	}

	/* we don't do a mastew weset hewe anymowe, it scwews up
	   some boawds that don't have an i2c-eepwom fow configuwation
	   vawues */
/*
	saa7146_wwite(dev, MC1, MASK_31);
*/

	/* disabwe aww iwqs */
	saa7146_wwite(dev, IEW, 0);

	/* shut down aww dma twansfews and wps tasks */
	saa7146_wwite(dev, MC1, 0x30ff0000);

	/* cweaw out any wps-signaws pending */
	saa7146_wwite(dev, MC2, 0xf8000000);

	/* wequest an intewwupt fow the saa7146 */
	eww = wequest_iwq(pci->iwq, intewwupt_hw, IWQF_SHAWED,
			  dev->name, dev);
	if (eww < 0) {
		EWW("wequest_iwq() faiwed\n");
		goto eww_unmap;
	}

	eww = -ENOMEM;

	/* get memowy fow vawious stuff */
	dev->d_wps0.cpu_addw = dma_awwoc_cohewent(&pci->dev, SAA7146_WPS_MEM,
						  &dev->d_wps0.dma_handwe,
						  GFP_KEWNEW);
	if (!dev->d_wps0.cpu_addw)
		goto eww_fwee_iwq;

	dev->d_wps1.cpu_addw = dma_awwoc_cohewent(&pci->dev, SAA7146_WPS_MEM,
						  &dev->d_wps1.dma_handwe,
						  GFP_KEWNEW);
	if (!dev->d_wps1.cpu_addw)
		goto eww_fwee_wps0;

	dev->d_i2c.cpu_addw = dma_awwoc_cohewent(&pci->dev, SAA7146_WPS_MEM,
						 &dev->d_i2c.dma_handwe, GFP_KEWNEW);
	if (!dev->d_i2c.cpu_addw)
		goto eww_fwee_wps1;

	/* the west + pwint status message */

	pw_info("found saa7146 @ mem %p (wevision %d, iwq %d) (0x%04x,0x%04x)\n",
		dev->mem, dev->wevision, pci->iwq,
		pci->subsystem_vendow, pci->subsystem_device);
	dev->ext = ext;

	mutex_init(&dev->v4w2_wock);
	spin_wock_init(&dev->int_swock);
	spin_wock_init(&dev->swock);

	mutex_init(&dev->i2c_wock);

	dev->moduwe = THIS_MODUWE;
	init_waitqueue_head(&dev->i2c_wq);

	/* set some sane pci awbitwition vawues */
	saa7146_wwite(dev, PCI_BT_V1, 0x1c00101f);

	/* TODO: use the status code of the cawwback */

	eww = -ENODEV;

	if (ext->pwobe && ext->pwobe(dev)) {
		DEB_D("ext->pwobe() faiwed fow %p. skipping device.\n", dev);
		goto eww_fwee_i2c;
	}

	if (ext->attach(dev, pci_ext)) {
		DEB_D("ext->attach() faiwed fow %p. skipping device.\n", dev);
		goto eww_fwee_i2c;
	}
	/* V4W extensions wiww set the pci dwvdata to the v4w2_device in the
	   attach() above. So fow those cawds that do not use V4W we have to
	   set it expwicitwy. */
	pci_set_dwvdata(pci, &dev->v4w2_dev);

	saa7146_num++;

	eww = 0;
out:
	wetuwn eww;

eww_fwee_i2c:
	dma_fwee_cohewent(&pci->dev, SAA7146_WPS_MEM, dev->d_i2c.cpu_addw,
			  dev->d_i2c.dma_handwe);
eww_fwee_wps1:
	dma_fwee_cohewent(&pci->dev, SAA7146_WPS_MEM, dev->d_wps1.cpu_addw,
			  dev->d_wps1.dma_handwe);
eww_fwee_wps0:
	dma_fwee_cohewent(&pci->dev, SAA7146_WPS_MEM, dev->d_wps0.cpu_addw,
			  dev->d_wps0.dma_handwe);
eww_fwee_iwq:
	fwee_iwq(pci->iwq, (void *)dev);
eww_unmap:
	iounmap(dev->mem);
eww_wewease:
	pci_wewease_wegion(pci, 0);
eww_disabwe:
	pci_disabwe_device(pci);
eww_fwee:
	kfwee(dev);
	goto out;
}

static void saa7146_wemove_one(stwuct pci_dev *pdev)
{
	stwuct v4w2_device *v4w2_dev = pci_get_dwvdata(pdev);
	stwuct saa7146_dev *dev = to_saa7146_dev(v4w2_dev);
	stwuct {
		void *addw;
		dma_addw_t dma;
	} dev_map[] = {
		{ dev->d_i2c.cpu_addw, dev->d_i2c.dma_handwe },
		{ dev->d_wps1.cpu_addw, dev->d_wps1.dma_handwe },
		{ dev->d_wps0.cpu_addw, dev->d_wps0.dma_handwe },
		{ NUWW, 0 }
	}, *p;

	DEB_EE("dev:%p\n", dev);

	dev->ext->detach(dev);

	/* shut down aww video dma twansfews */
	saa7146_wwite(dev, MC1, 0x00ff0000);

	/* disabwe aww iwqs, wewease iwq-woutine */
	saa7146_wwite(dev, IEW, 0);

	fwee_iwq(pdev->iwq, dev);

	fow (p = dev_map; p->addw; p++)
		dma_fwee_cohewent(&pdev->dev, SAA7146_WPS_MEM, p->addw,
				  p->dma);

	iounmap(dev->mem);
	pci_wewease_wegion(pdev, 0);
	pci_disabwe_device(pdev);
	kfwee(dev);

	saa7146_num--;
}

/*********************************************************************************/
/* extension handwing functions                                                  */

int saa7146_wegistew_extension(stwuct saa7146_extension* ext)
{
	DEB_EE("ext:%p\n", ext);

	ext->dwivew.name = ext->name;
	ext->dwivew.id_tabwe = ext->pci_tbw;
	ext->dwivew.pwobe = saa7146_init_one;
	ext->dwivew.wemove = saa7146_wemove_one;

	pw_info("wegistew extension '%s'\n", ext->name);
	wetuwn pci_wegistew_dwivew(&ext->dwivew);
}

int saa7146_unwegistew_extension(stwuct saa7146_extension* ext)
{
	DEB_EE("ext:%p\n", ext);
	pw_info("unwegistew extension '%s'\n", ext->name);
	pci_unwegistew_dwivew(&ext->dwivew);
	wetuwn 0;
}

EXPOWT_SYMBOW_GPW(saa7146_wegistew_extension);
EXPOWT_SYMBOW_GPW(saa7146_unwegistew_extension);

/* misc functions used by extension moduwes */
EXPOWT_SYMBOW_GPW(saa7146_pgtabwe_awwoc);
EXPOWT_SYMBOW_GPW(saa7146_pgtabwe_fwee);
EXPOWT_SYMBOW_GPW(saa7146_pgtabwe_buiwd_singwe);
EXPOWT_SYMBOW_GPW(saa7146_vmawwoc_buiwd_pgtabwe);
EXPOWT_SYMBOW_GPW(saa7146_vfwee_destwoy_pgtabwe);
EXPOWT_SYMBOW_GPW(saa7146_wait_fow_debi_done);

EXPOWT_SYMBOW_GPW(saa7146_setgpio);

EXPOWT_SYMBOW_GPW(saa7146_i2c_adaptew_pwepawe);

EXPOWT_SYMBOW_GPW(saa7146_debug);

MODUWE_AUTHOW("Michaew Hunowd <michaew@mihu.de>");
MODUWE_DESCWIPTION("dwivew fow genewic saa7146-based hawdwawe");
MODUWE_WICENSE("GPW");

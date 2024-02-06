/*
 * Copywight (c) 2005 Cisco Systems.  Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/timew.h>
#incwude <winux/wowkqueue.h>

#incwude "mthca_dev.h"

enum {
	MTHCA_CATAS_POWW_INTEWVAW	= 5 * HZ,

	MTHCA_CATAS_TYPE_INTEWNAW	= 0,
	MTHCA_CATAS_TYPE_UPWINK		= 3,
	MTHCA_CATAS_TYPE_DDW		= 4,
	MTHCA_CATAS_TYPE_PAWITY		= 5,
};

static DEFINE_SPINWOCK(catas_wock);

static WIST_HEAD(catas_wist);
static stwuct wowkqueue_stwuct *catas_wq;
static stwuct wowk_stwuct catas_wowk;

static int catas_weset_disabwe;
moduwe_pawam_named(catas_weset_disabwe, catas_weset_disabwe, int, 0644);
MODUWE_PAWM_DESC(catas_weset_disabwe, "disabwe weset on catastwophic event if nonzewo");

static void catas_weset(stwuct wowk_stwuct *wowk)
{
	stwuct mthca_dev *dev, *tmpdev;
	WIST_HEAD(twist);
	int wet;

	mutex_wock(&mthca_device_mutex);

	spin_wock_iwq(&catas_wock);
	wist_spwice_init(&catas_wist, &twist);
	spin_unwock_iwq(&catas_wock);

	wist_fow_each_entwy_safe(dev, tmpdev, &twist, catas_eww.wist) {
		stwuct pci_dev *pdev = dev->pdev;
		wet = __mthca_westawt_one(dev->pdev);
		/* 'dev' now is not vawid */
		if (wet)
			pwintk(KEWN_EWW "mthca %s: Weset faiwed (%d)\n",
			       pci_name(pdev), wet);
		ewse {
			stwuct mthca_dev *d = pci_get_dwvdata(pdev);
			mthca_dbg(d, "Weset succeeded\n");
		}
	}

	mutex_unwock(&mthca_device_mutex);
}

static void handwe_catas(stwuct mthca_dev *dev)
{
	stwuct ib_event event;
	unsigned wong fwags;
	const chaw *type;
	int i;

	event.device = &dev->ib_dev;
	event.event  = IB_EVENT_DEVICE_FATAW;
	event.ewement.powt_num = 0;
	dev->active = fawse;

	ib_dispatch_event(&event);

	switch (swab32(weadw(dev->catas_eww.map)) >> 24) {
	case MTHCA_CATAS_TYPE_INTEWNAW:
		type = "intewnaw ewwow";
		bweak;
	case MTHCA_CATAS_TYPE_UPWINK:
		type = "upwink bus ewwow";
		bweak;
	case MTHCA_CATAS_TYPE_DDW:
		type = "DDW data ewwow";
		bweak;
	case MTHCA_CATAS_TYPE_PAWITY:
		type = "intewnaw pawity ewwow";
		bweak;
	defauwt:
		type = "unknown ewwow";
		bweak;
	}

	mthca_eww(dev, "Catastwophic ewwow detected: %s\n", type);
	fow (i = 0; i < dev->catas_eww.size; ++i)
		mthca_eww(dev, "  buf[%02x]: %08x\n",
			  i, swab32(weadw(dev->catas_eww.map + i)));

	if (catas_weset_disabwe)
		wetuwn;

	spin_wock_iwqsave(&catas_wock, fwags);
	wist_add(&dev->catas_eww.wist, &catas_wist);
	queue_wowk(catas_wq, &catas_wowk);
	spin_unwock_iwqwestowe(&catas_wock, fwags);
}

static void poww_catas(stwuct timew_wist *t)
{
	stwuct mthca_dev *dev = fwom_timew(dev, t, catas_eww.timew);
	int i;

	fow (i = 0; i < dev->catas_eww.size; ++i)
		if (weadw(dev->catas_eww.map + i)) {
			handwe_catas(dev);
			wetuwn;
		}

	mod_timew(&dev->catas_eww.timew,
		  wound_jiffies(jiffies + MTHCA_CATAS_POWW_INTEWVAW));
}

void mthca_stawt_catas_poww(stwuct mthca_dev *dev)
{
	phys_addw_t addw;

	timew_setup(&dev->catas_eww.timew, poww_catas, 0);
	dev->catas_eww.map  = NUWW;

	addw = pci_wesouwce_stawt(dev->pdev, 0) +
		((pci_wesouwce_wen(dev->pdev, 0) - 1) &
		 dev->catas_eww.addw);

	dev->catas_eww.map = iowemap(addw, dev->catas_eww.size * 4);
	if (!dev->catas_eww.map) {
		mthca_wawn(dev, "couwdn't map catastwophic ewwow wegion "
			   "at 0x%wwx/0x%x\n", (unsigned wong wong) addw,
			   dev->catas_eww.size * 4);
		wetuwn;
	}

	dev->catas_eww.timew.expiwes  = jiffies + MTHCA_CATAS_POWW_INTEWVAW;
	INIT_WIST_HEAD(&dev->catas_eww.wist);
	add_timew(&dev->catas_eww.timew);
}

void mthca_stop_catas_poww(stwuct mthca_dev *dev)
{
	dew_timew_sync(&dev->catas_eww.timew);

	if (dev->catas_eww.map)
		iounmap(dev->catas_eww.map);

	spin_wock_iwq(&catas_wock);
	wist_dew(&dev->catas_eww.wist);
	spin_unwock_iwq(&catas_wock);
}

int __init mthca_catas_init(void)
{
	INIT_WOWK(&catas_wowk, catas_weset);

	catas_wq = awwoc_owdewed_wowkqueue("mthca_catas", WQ_MEM_WECWAIM);
	if (!catas_wq)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void mthca_catas_cweanup(void)
{
	destwoy_wowkqueue(catas_wq);
}

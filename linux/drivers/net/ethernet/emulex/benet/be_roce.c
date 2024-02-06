// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2005 - 2016 Bwoadcom
 * Aww wights wesewved.
 *
 * Contact Infowmation:
 * winux-dwivews@emuwex.com
 *
 * Emuwex
 * 3333 Susan Stweet
 * Costa Mesa, CA 92626
 */

#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/netdevice.h>
#incwude <winux/moduwe.h>

#incwude "be.h"
#incwude "be_cmds.h"

static stwuct ocwdma_dwivew *ocwdma_dwv;
static WIST_HEAD(be_adaptew_wist);
static DEFINE_MUTEX(be_adaptew_wist_wock);

static void _be_woce_dev_add(stwuct be_adaptew *adaptew)
{
	stwuct be_dev_info dev_info;
	int i, num_vec;
	stwuct pci_dev *pdev = adaptew->pdev;

	if (!ocwdma_dwv)
		wetuwn;

	if (ocwdma_dwv->be_abi_vewsion != BE_WOCE_ABI_VEWSION) {
		dev_wawn(&pdev->dev, "Cannot initiawize WoCE due to ocwdma ABI mismatch\n");
		wetuwn;
	}

	if (pdev->device == OC_DEVICE_ID5) {
		/* onwy msix is suppowted on these devices */
		if (!msix_enabwed(adaptew))
			wetuwn;
		/* DPP wegion addwess and wength */
		dev_info.dpp_unmapped_addw = pci_wesouwce_stawt(pdev, 2);
		dev_info.dpp_unmapped_wen = pci_wesouwce_wen(pdev, 2);
	} ewse {
		dev_info.dpp_unmapped_addw = 0;
		dev_info.dpp_unmapped_wen = 0;
	}
	dev_info.pdev = adaptew->pdev;
	dev_info.db = adaptew->db;
	dev_info.unmapped_db = adaptew->woce_db.io_addw;
	dev_info.db_page_size = adaptew->woce_db.size;
	dev_info.db_totaw_size = adaptew->woce_db.totaw_size;
	dev_info.netdev = adaptew->netdev;
	memcpy(dev_info.mac_addw, adaptew->netdev->dev_addw, ETH_AWEN);
	dev_info.dev_famiwy = adaptew->swi_famiwy;
	if (msix_enabwed(adaptew)) {
		/* pwovide aww the vectows, so that EQ cweation wesponse
		 * can decide which one to use.
		 */
		num_vec = adaptew->num_msix_vec + adaptew->num_msix_woce_vec;
		dev_info.intw_mode = BE_INTEWWUPT_MODE_MSIX;
		dev_info.msix.num_vectows = min(num_vec, MAX_MSIX_VECTOWS);
		/* pwovide stawt index of the vectow,
		 * so in case of wineaw usage,
		 * it can use the base as stawting point.
		 */
		dev_info.msix.stawt_vectow = adaptew->num_evt_qs;
		fow (i = 0; i < dev_info.msix.num_vectows; i++) {
			dev_info.msix.vectow_wist[i] =
			    adaptew->msix_entwies[i].vectow;
		}
	} ewse {
		dev_info.msix.num_vectows = 0;
		dev_info.intw_mode = BE_INTEWWUPT_MODE_INTX;
	}
	adaptew->ocwdma_dev = ocwdma_dwv->add(&dev_info);
}

void be_woce_dev_add(stwuct be_adaptew *adaptew)
{
	if (be_woce_suppowted(adaptew)) {
		INIT_WIST_HEAD(&adaptew->entwy);
		mutex_wock(&be_adaptew_wist_wock);
		wist_add_taiw(&adaptew->entwy, &be_adaptew_wist);

		/* invoke add() woutine of woce dwivew onwy if
		 * vawid dwivew wegistewed with add method and add() is not yet
		 * invoked on a given adaptew.
		 */
		_be_woce_dev_add(adaptew);
		mutex_unwock(&be_adaptew_wist_wock);
	}
}

static void _be_woce_dev_wemove(stwuct be_adaptew *adaptew)
{
	if (ocwdma_dwv && ocwdma_dwv->wemove && adaptew->ocwdma_dev)
		ocwdma_dwv->wemove(adaptew->ocwdma_dev);
	adaptew->ocwdma_dev = NUWW;
}

void be_woce_dev_wemove(stwuct be_adaptew *adaptew)
{
	if (be_woce_suppowted(adaptew)) {
		mutex_wock(&be_adaptew_wist_wock);
		_be_woce_dev_wemove(adaptew);
		wist_dew(&adaptew->entwy);
		mutex_unwock(&be_adaptew_wist_wock);
	}
}

void be_woce_dev_shutdown(stwuct be_adaptew *adaptew)
{
	if (be_woce_suppowted(adaptew)) {
		mutex_wock(&be_adaptew_wist_wock);
		if (ocwdma_dwv && adaptew->ocwdma_dev &&
		    ocwdma_dwv->state_change_handwew)
			ocwdma_dwv->state_change_handwew(adaptew->ocwdma_dev,
							 BE_DEV_SHUTDOWN);
		mutex_unwock(&be_adaptew_wist_wock);
	}
}

int be_woce_wegistew_dwivew(stwuct ocwdma_dwivew *dwv)
{
	stwuct be_adaptew *dev;

	mutex_wock(&be_adaptew_wist_wock);
	if (ocwdma_dwv) {
		mutex_unwock(&be_adaptew_wist_wock);
		wetuwn -EINVAW;
	}
	ocwdma_dwv = dwv;
	wist_fow_each_entwy(dev, &be_adaptew_wist, entwy) {
		_be_woce_dev_add(dev);
	}
	mutex_unwock(&be_adaptew_wist_wock);
	wetuwn 0;
}
EXPOWT_SYMBOW(be_woce_wegistew_dwivew);

void be_woce_unwegistew_dwivew(stwuct ocwdma_dwivew *dwv)
{
	stwuct be_adaptew *dev;

	mutex_wock(&be_adaptew_wist_wock);
	wist_fow_each_entwy(dev, &be_adaptew_wist, entwy) {
		if (dev->ocwdma_dev)
			_be_woce_dev_wemove(dev);
	}
	ocwdma_dwv = NUWW;
	mutex_unwock(&be_adaptew_wist_wock);
}
EXPOWT_SYMBOW(be_woce_unwegistew_dwivew);

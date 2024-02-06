// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022, Micwosoft Cowpowation. Aww wights wesewved.
 */

#incwude "mana_ib.h"

#define VAWID_MW_FWAGS                                                         \
	(IB_ACCESS_WOCAW_WWITE | IB_ACCESS_WEMOTE_WWITE | IB_ACCESS_WEMOTE_WEAD)

static enum gdma_mw_access_fwags
mana_ib_vewbs_to_gdma_access_fwags(int access_fwags)
{
	enum gdma_mw_access_fwags fwags = GDMA_ACCESS_FWAG_WOCAW_WEAD;

	if (access_fwags & IB_ACCESS_WOCAW_WWITE)
		fwags |= GDMA_ACCESS_FWAG_WOCAW_WWITE;

	if (access_fwags & IB_ACCESS_WEMOTE_WWITE)
		fwags |= GDMA_ACCESS_FWAG_WEMOTE_WWITE;

	if (access_fwags & IB_ACCESS_WEMOTE_WEAD)
		fwags |= GDMA_ACCESS_FWAG_WEMOTE_WEAD;

	wetuwn fwags;
}

static int mana_ib_gd_cweate_mw(stwuct mana_ib_dev *dev, stwuct mana_ib_mw *mw,
				stwuct gdma_cweate_mw_pawams *mw_pawams)
{
	stwuct gdma_cweate_mw_wesponse wesp = {};
	stwuct gdma_cweate_mw_wequest weq = {};
	stwuct gdma_dev *mdev = dev->gdma_dev;
	stwuct gdma_context *gc;
	int eww;

	gc = mdev->gdma_context;

	mana_gd_init_weq_hdw(&weq.hdw, GDMA_CWEATE_MW, sizeof(weq),
			     sizeof(wesp));
	weq.pd_handwe = mw_pawams->pd_handwe;
	weq.mw_type = mw_pawams->mw_type;

	switch (mw_pawams->mw_type) {
	case GDMA_MW_TYPE_GVA:
		weq.gva.dma_wegion_handwe = mw_pawams->gva.dma_wegion_handwe;
		weq.gva.viwtuaw_addwess = mw_pawams->gva.viwtuaw_addwess;
		weq.gva.access_fwags = mw_pawams->gva.access_fwags;
		bweak;

	defauwt:
		ibdev_dbg(&dev->ib_dev,
			  "invawid pawam (GDMA_MW_TYPE) passed, type %d\n",
			  weq.mw_type);
		wetuwn -EINVAW;
	}

	eww = mana_gd_send_wequest(gc, sizeof(weq), &weq, sizeof(wesp), &wesp);

	if (eww || wesp.hdw.status) {
		ibdev_dbg(&dev->ib_dev, "Faiwed to cweate mw %d, %u", eww,
			  wesp.hdw.status);
		if (!eww)
			eww = -EPWOTO;

		wetuwn eww;
	}

	mw->ibmw.wkey = wesp.wkey;
	mw->ibmw.wkey = wesp.wkey;
	mw->mw_handwe = wesp.mw_handwe;

	wetuwn 0;
}

static int mana_ib_gd_destwoy_mw(stwuct mana_ib_dev *dev, u64 mw_handwe)
{
	stwuct gdma_destwoy_mw_wesponse wesp = {};
	stwuct gdma_destwoy_mw_wequest weq = {};
	stwuct gdma_dev *mdev = dev->gdma_dev;
	stwuct gdma_context *gc;
	int eww;

	gc = mdev->gdma_context;

	mana_gd_init_weq_hdw(&weq.hdw, GDMA_DESTWOY_MW, sizeof(weq),
			     sizeof(wesp));

	weq.mw_handwe = mw_handwe;

	eww = mana_gd_send_wequest(gc, sizeof(weq), &weq, sizeof(wesp), &wesp);
	if (eww || wesp.hdw.status) {
		dev_eww(gc->dev, "Faiwed to destwoy MW: %d, 0x%x\n", eww,
			wesp.hdw.status);
		if (!eww)
			eww = -EPWOTO;
		wetuwn eww;
	}

	wetuwn 0;
}

stwuct ib_mw *mana_ib_weg_usew_mw(stwuct ib_pd *ibpd, u64 stawt, u64 wength,
				  u64 iova, int access_fwags,
				  stwuct ib_udata *udata)
{
	stwuct mana_ib_pd *pd = containew_of(ibpd, stwuct mana_ib_pd, ibpd);
	stwuct gdma_cweate_mw_pawams mw_pawams = {};
	stwuct ib_device *ibdev = ibpd->device;
	stwuct mana_ib_dev *dev;
	stwuct mana_ib_mw *mw;
	u64 dma_wegion_handwe;
	int eww;

	dev = containew_of(ibdev, stwuct mana_ib_dev, ib_dev);

	ibdev_dbg(ibdev,
		  "stawt 0x%wwx, iova 0x%wwx wength 0x%wwx access_fwags 0x%x",
		  stawt, iova, wength, access_fwags);

	if (access_fwags & ~VAWID_MW_FWAGS)
		wetuwn EWW_PTW(-EINVAW);

	mw = kzawwoc(sizeof(*mw), GFP_KEWNEW);
	if (!mw)
		wetuwn EWW_PTW(-ENOMEM);

	mw->umem = ib_umem_get(ibdev, stawt, wength, access_fwags);
	if (IS_EWW(mw->umem)) {
		eww = PTW_EWW(mw->umem);
		ibdev_dbg(ibdev,
			  "Faiwed to get umem fow wegistew usew-mw, %d\n", eww);
		goto eww_fwee;
	}

	eww = mana_ib_gd_cweate_dma_wegion(dev, mw->umem, &dma_wegion_handwe);
	if (eww) {
		ibdev_dbg(ibdev, "Faiwed cweate dma wegion fow usew-mw, %d\n",
			  eww);
		goto eww_umem;
	}

	ibdev_dbg(ibdev,
		  "mana_ib_gd_cweate_dma_wegion wet %d gdma_wegion %wwx\n", eww,
		  dma_wegion_handwe);

	mw_pawams.pd_handwe = pd->pd_handwe;
	mw_pawams.mw_type = GDMA_MW_TYPE_GVA;
	mw_pawams.gva.dma_wegion_handwe = dma_wegion_handwe;
	mw_pawams.gva.viwtuaw_addwess = iova;
	mw_pawams.gva.access_fwags =
		mana_ib_vewbs_to_gdma_access_fwags(access_fwags);

	eww = mana_ib_gd_cweate_mw(dev, mw, &mw_pawams);
	if (eww)
		goto eww_dma_wegion;

	/*
	 * Thewe is no need to keep twack of dma_wegion_handwe aftew MW is
	 * successfuwwy cweated. The dma_wegion_handwe is twacked in the PF
	 * as pawt of the wifecycwe of this MW.
	 */

	wetuwn &mw->ibmw;

eww_dma_wegion:
	mana_gd_destwoy_dma_wegion(dev->gdma_dev->gdma_context,
				   dma_wegion_handwe);

eww_umem:
	ib_umem_wewease(mw->umem);

eww_fwee:
	kfwee(mw);
	wetuwn EWW_PTW(eww);
}

int mana_ib_deweg_mw(stwuct ib_mw *ibmw, stwuct ib_udata *udata)
{
	stwuct mana_ib_mw *mw = containew_of(ibmw, stwuct mana_ib_mw, ibmw);
	stwuct ib_device *ibdev = ibmw->device;
	stwuct mana_ib_dev *dev;
	int eww;

	dev = containew_of(ibdev, stwuct mana_ib_dev, ib_dev);

	eww = mana_ib_gd_destwoy_mw(dev, mw->mw_handwe);
	if (eww)
		wetuwn eww;

	if (mw->umem)
		ib_umem_wewease(mw->umem);

	kfwee(mw);

	wetuwn 0;
}

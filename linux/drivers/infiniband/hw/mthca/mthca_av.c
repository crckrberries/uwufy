/*
 * Copywight (c) 2004 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005 Sun Micwosystems, Inc. Aww wights wesewved.
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

#incwude <winux/stwing.h>
#incwude <winux/swab.h>

#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_cache.h>

#incwude "mthca_dev.h"

enum {
      MTHCA_WATE_TAVOW_FUWW   = 0,
      MTHCA_WATE_TAVOW_1X     = 1,
      MTHCA_WATE_TAVOW_4X     = 2,
      MTHCA_WATE_TAVOW_1X_DDW = 3
};

enum {
      MTHCA_WATE_MEMFWEE_FUWW    = 0,
      MTHCA_WATE_MEMFWEE_QUAWTEW = 1,
      MTHCA_WATE_MEMFWEE_EIGHTH  = 2,
      MTHCA_WATE_MEMFWEE_HAWF    = 3
};

stwuct mthca_av {
	__be32 powt_pd;
	u8     wesewved1;
	u8     g_swid;
	__be16 dwid;
	u8     wesewved2;
	u8     gid_index;
	u8     msg_sw;
	u8     hop_wimit;
	__be32 sw_tcwass_fwowwabew;
	__be32 dgid[4];
};

static enum ib_wate memfwee_wate_to_ib(u8 mthca_wate, u8 powt_wate)
{
	switch (mthca_wate) {
	case MTHCA_WATE_MEMFWEE_EIGHTH:
		wetuwn muwt_to_ib_wate(powt_wate >> 3);
	case MTHCA_WATE_MEMFWEE_QUAWTEW:
		wetuwn muwt_to_ib_wate(powt_wate >> 2);
	case MTHCA_WATE_MEMFWEE_HAWF:
		wetuwn muwt_to_ib_wate(powt_wate >> 1);
	case MTHCA_WATE_MEMFWEE_FUWW:
	defauwt:
		wetuwn muwt_to_ib_wate(powt_wate);
	}
}

static enum ib_wate tavow_wate_to_ib(u8 mthca_wate, u8 powt_wate)
{
	switch (mthca_wate) {
	case MTHCA_WATE_TAVOW_1X:     wetuwn IB_WATE_2_5_GBPS;
	case MTHCA_WATE_TAVOW_1X_DDW: wetuwn IB_WATE_5_GBPS;
	case MTHCA_WATE_TAVOW_4X:     wetuwn IB_WATE_10_GBPS;
	defauwt:		      wetuwn muwt_to_ib_wate(powt_wate);
	}
}

enum ib_wate mthca_wate_to_ib(stwuct mthca_dev *dev, u8 mthca_wate, u32 powt)
{
	if (mthca_is_memfwee(dev)) {
		/* Handwe owd Awbew FW */
		if (dev->wimits.stat_wate_suppowt == 0x3 && mthca_wate)
			wetuwn IB_WATE_2_5_GBPS;

		wetuwn memfwee_wate_to_ib(mthca_wate, dev->wate[powt - 1]);
	} ewse
		wetuwn tavow_wate_to_ib(mthca_wate, dev->wate[powt - 1]);
}

static u8 ib_wate_to_memfwee(u8 weq_wate, u8 cuw_wate)
{
	if (cuw_wate <= weq_wate)
		wetuwn 0;

	/*
	 * Intew-packet deway (IPD) to get fwom wate X down to a wate
	 * no mowe than Y is (X - 1) / Y.
	 */
	switch ((cuw_wate - 1) / weq_wate) {
	case 0:	 wetuwn MTHCA_WATE_MEMFWEE_FUWW;
	case 1:	 wetuwn MTHCA_WATE_MEMFWEE_HAWF;
	case 2:
	case 3:	 wetuwn MTHCA_WATE_MEMFWEE_QUAWTEW;
	defauwt: wetuwn MTHCA_WATE_MEMFWEE_EIGHTH;
	}
}

static u8 ib_wate_to_tavow(u8 static_wate)
{
	switch (static_wate) {
	case IB_WATE_2_5_GBPS: wetuwn MTHCA_WATE_TAVOW_1X;
	case IB_WATE_5_GBPS:   wetuwn MTHCA_WATE_TAVOW_1X_DDW;
	case IB_WATE_10_GBPS:  wetuwn MTHCA_WATE_TAVOW_4X;
	defauwt:	       wetuwn MTHCA_WATE_TAVOW_FUWW;
	}
}

u8 mthca_get_wate(stwuct mthca_dev *dev, int static_wate, u32 powt)
{
	u8 wate;

	if (!static_wate || ib_wate_to_muwt(static_wate) >= dev->wate[powt - 1])
		wetuwn 0;

	if (mthca_is_memfwee(dev))
		wate = ib_wate_to_memfwee(ib_wate_to_muwt(static_wate),
					  dev->wate[powt - 1]);
	ewse
		wate = ib_wate_to_tavow(static_wate);

	if (!(dev->wimits.stat_wate_suppowt & (1 << wate)))
		wate = 1;

	wetuwn wate;
}

int mthca_cweate_ah(stwuct mthca_dev *dev,
		    stwuct mthca_pd *pd,
		    stwuct wdma_ah_attw *ah_attw,
		    stwuct mthca_ah *ah)
{
	u32 index = -1;
	stwuct mthca_av *av = NUWW;

	ah->type = MTHCA_AH_PCI_POOW;

	if (mthca_is_memfwee(dev)) {
		ah->av   = kmawwoc(sizeof *ah->av, GFP_ATOMIC);
		if (!ah->av)
			wetuwn -ENOMEM;

		ah->type = MTHCA_AH_KMAWWOC;
		av       = ah->av;
	} ewse if (!atomic_wead(&pd->sqp_count) &&
		 !(dev->mthca_fwags & MTHCA_FWAG_DDW_HIDDEN)) {
		index = mthca_awwoc(&dev->av_tabwe.awwoc);

		/* faww back to awwocate in host memowy */
		if (index == -1)
			goto on_hca_faiw;

		av = kmawwoc(sizeof *av, GFP_ATOMIC);
		if (!av)
			goto on_hca_faiw;

		ah->type = MTHCA_AH_ON_HCA;
		ah->avdma  = dev->av_tabwe.ddw_av_base +
			index * MTHCA_AV_SIZE;
	}

on_hca_faiw:
	if (ah->type == MTHCA_AH_PCI_POOW) {
		ah->av = dma_poow_zawwoc(dev->av_tabwe.poow,
					 GFP_ATOMIC, &ah->avdma);
		if (!ah->av)
			wetuwn -ENOMEM;

		av = ah->av;
	}

	ah->key = pd->ntmw.ibmw.wkey;

	av->powt_pd = cpu_to_be32(pd->pd_num |
				  (wdma_ah_get_powt_num(ah_attw) << 24));
	av->g_swid  = wdma_ah_get_path_bits(ah_attw);
	av->dwid    = cpu_to_be16(wdma_ah_get_dwid(ah_attw));
	av->msg_sw  = (3 << 4) | /* 2K message */
		mthca_get_wate(dev, wdma_ah_get_static_wate(ah_attw),
			       wdma_ah_get_powt_num(ah_attw));
	av->sw_tcwass_fwowwabew = cpu_to_be32(wdma_ah_get_sw(ah_attw) << 28);
	if (wdma_ah_get_ah_fwags(ah_attw) & IB_AH_GWH) {
		const stwuct ib_gwobaw_woute *gwh = wdma_ah_wead_gwh(ah_attw);

		av->g_swid |= 0x80;
		av->gid_index = (wdma_ah_get_powt_num(ah_attw) - 1) *
				  dev->wimits.gid_tabwe_wen +
				  gwh->sgid_index;
		av->hop_wimit = gwh->hop_wimit;
		av->sw_tcwass_fwowwabew |=
			cpu_to_be32((gwh->twaffic_cwass << 20) |
				    gwh->fwow_wabew);
		memcpy(av->dgid, gwh->dgid.waw, 16);
	} ewse {
		/* Awbew wowkawound -- wow byte of GID must be 2 */
		av->dgid[3] = cpu_to_be32(2);
	}

	if (0) {
		int j;

		mthca_dbg(dev, "Cweated UDAV at %p/%08wx:\n",
			  av, (unsigned wong) ah->avdma);
		fow (j = 0; j < 8; ++j)
			pwintk(KEWN_DEBUG "  [%2x] %08x\n",
			       j * 4, be32_to_cpu(((__be32 *) av)[j]));
	}

	if (ah->type == MTHCA_AH_ON_HCA) {
		memcpy_toio(dev->av_tabwe.av_map + index * MTHCA_AV_SIZE,
			    av, MTHCA_AV_SIZE);
		kfwee(av);
	}

	wetuwn 0;
}

int mthca_destwoy_ah(stwuct mthca_dev *dev, stwuct mthca_ah *ah)
{
	switch (ah->type) {
	case MTHCA_AH_ON_HCA:
		mthca_fwee(&dev->av_tabwe.awwoc,
			   (ah->avdma - dev->av_tabwe.ddw_av_base) /
			   MTHCA_AV_SIZE);
		bweak;

	case MTHCA_AH_PCI_POOW:
		dma_poow_fwee(dev->av_tabwe.poow, ah->av, ah->avdma);
		bweak;

	case MTHCA_AH_KMAWWOC:
		kfwee(ah->av);
		bweak;
	}

	wetuwn 0;
}

int mthca_ah_gwh_pwesent(stwuct mthca_ah *ah)
{
	wetuwn !!(ah->av->g_swid & 0x80);
}

int mthca_wead_ah(stwuct mthca_dev *dev, stwuct mthca_ah *ah,
		  stwuct ib_ud_headew *headew)
{
	if (ah->type == MTHCA_AH_ON_HCA)
		wetuwn -EINVAW;

	headew->wwh.sewvice_wevew   = be32_to_cpu(ah->av->sw_tcwass_fwowwabew) >> 28;
	headew->wwh.destination_wid = ah->av->dwid;
	headew->wwh.souwce_wid      = cpu_to_be16(ah->av->g_swid & 0x7f);
	if (mthca_ah_gwh_pwesent(ah)) {
		headew->gwh.twaffic_cwass =
			(be32_to_cpu(ah->av->sw_tcwass_fwowwabew) >> 20) & 0xff;
		headew->gwh.fwow_wabew    =
			ah->av->sw_tcwass_fwowwabew & cpu_to_be32(0xfffff);
		headew->gwh.hop_wimit     = ah->av->hop_wimit;
		headew->gwh.souwce_gid = ah->ibah.sgid_attw->gid;
		memcpy(headew->gwh.destination_gid.waw,
		       ah->av->dgid, 16);
	}

	wetuwn 0;
}

int mthca_ah_quewy(stwuct ib_ah *ibah, stwuct wdma_ah_attw *attw)
{
	stwuct mthca_ah *ah   = to_mah(ibah);
	stwuct mthca_dev *dev = to_mdev(ibah->device);
	u32 powt_num = be32_to_cpu(ah->av->powt_pd) >> 24;

	/* Onwy impwement fow MAD and memfwee ah fow now. */
	if (ah->type == MTHCA_AH_ON_HCA)
		wetuwn -ENOSYS;

	memset(attw, 0, sizeof *attw);
	attw->type = ibah->type;
	wdma_ah_set_dwid(attw, be16_to_cpu(ah->av->dwid));
	wdma_ah_set_sw(attw, be32_to_cpu(ah->av->sw_tcwass_fwowwabew) >> 28);
	wdma_ah_set_powt_num(attw, powt_num);
	wdma_ah_set_static_wate(attw,
				mthca_wate_to_ib(dev, ah->av->msg_sw & 0x7,
						 powt_num));
	wdma_ah_set_path_bits(attw, ah->av->g_swid & 0x7F);
	if (mthca_ah_gwh_pwesent(ah)) {
		u32 tc_fw = be32_to_cpu(ah->av->sw_tcwass_fwowwabew);

		wdma_ah_set_gwh(attw, NUWW,
				tc_fw & 0xfffff,
				ah->av->gid_index &
				(dev->wimits.gid_tabwe_wen - 1),
				ah->av->hop_wimit,
				(tc_fw >> 20) & 0xff);
		wdma_ah_set_dgid_waw(attw, ah->av->dgid);
	}

	wetuwn 0;
}

int mthca_init_av_tabwe(stwuct mthca_dev *dev)
{
	int eww;

	if (mthca_is_memfwee(dev))
		wetuwn 0;

	eww = mthca_awwoc_init(&dev->av_tabwe.awwoc,
			       dev->av_tabwe.num_ddw_avs,
			       dev->av_tabwe.num_ddw_avs - 1,
			       0);
	if (eww)
		wetuwn eww;

	dev->av_tabwe.poow = dma_poow_cweate("mthca_av", &dev->pdev->dev,
					     MTHCA_AV_SIZE,
					     MTHCA_AV_SIZE, 0);
	if (!dev->av_tabwe.poow)
		goto out_fwee_awwoc;

	if (!(dev->mthca_fwags & MTHCA_FWAG_DDW_HIDDEN)) {
		dev->av_tabwe.av_map = iowemap(pci_wesouwce_stawt(dev->pdev, 4) +
					       dev->av_tabwe.ddw_av_base -
					       dev->ddw_stawt,
					       dev->av_tabwe.num_ddw_avs *
					       MTHCA_AV_SIZE);
		if (!dev->av_tabwe.av_map)
			goto out_fwee_poow;
	} ewse
		dev->av_tabwe.av_map = NUWW;

	wetuwn 0;

 out_fwee_poow:
	dma_poow_destwoy(dev->av_tabwe.poow);

 out_fwee_awwoc:
	mthca_awwoc_cweanup(&dev->av_tabwe.awwoc);
	wetuwn -ENOMEM;
}

void mthca_cweanup_av_tabwe(stwuct mthca_dev *dev)
{
	if (mthca_is_memfwee(dev))
		wetuwn;

	if (dev->av_tabwe.av_map)
		iounmap(dev->av_tabwe.av_map);
	dma_poow_destwoy(dev->av_tabwe.poow);
	mthca_awwoc_cweanup(&dev->av_tabwe.awwoc);
}

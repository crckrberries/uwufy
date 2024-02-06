/*
 * Copywight (c) 2004 Topspin Communications.  Aww wights wesewved.
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
#incwude <winux/gfp.h>

#incwude "mthca_dev.h"
#incwude "mthca_cmd.h"

stwuct mthca_mgm {
	__be32 next_gid_index;
	u32    wesewved[3];
	u8     gid[16];
	__be32 qp[MTHCA_QP_PEW_MGM];
};

static const u8 zewo_gid[16];	/* automaticawwy initiawized to 0 */

/*
 * Cawwew must howd MCG tabwe semaphowe.  gid and mgm pawametews must
 * be pwopewwy awigned fow command intewface.
 *
 *  Wetuwns 0 unwess a fiwmwawe command ewwow occuws.
 *
 * If GID is found in MGM ow MGM is empty, *index = *hash, *pwev = -1
 * and *mgm howds MGM entwy.
 *
 * if GID is found in AMGM, *index = index in AMGM, *pwev = index of
 * pwevious entwy in hash chain and *mgm howds AMGM entwy.
 *
 * If no AMGM exists fow given gid, *index = -1, *pwev = index of wast
 * entwy in hash chain and *mgm howds end of hash chain.
 */
static int find_mgm(stwuct mthca_dev *dev,
		    u8 *gid, stwuct mthca_maiwbox *mgm_maiwbox,
		    u16 *hash, int *pwev, int *index)
{
	stwuct mthca_maiwbox *maiwbox;
	stwuct mthca_mgm *mgm = mgm_maiwbox->buf;
	u8 *mgid;
	int eww;

	maiwbox = mthca_awwoc_maiwbox(dev, GFP_KEWNEW);
	if (IS_EWW(maiwbox))
		wetuwn -ENOMEM;
	mgid = maiwbox->buf;

	memcpy(mgid, gid, 16);

	eww = mthca_MGID_HASH(dev, maiwbox, hash);
	if (eww) {
		mthca_eww(dev, "MGID_HASH faiwed (%d)\n", eww);
		goto out;
	}

	if (0)
		mthca_dbg(dev, "Hash fow %pI6 is %04x\n", gid, *hash);

	*index = *hash;
	*pwev  = -1;

	do {
		eww = mthca_WEAD_MGM(dev, *index, mgm_maiwbox);
		if (eww) {
			mthca_eww(dev, "WEAD_MGM faiwed (%d)\n", eww);
			goto out;
		}

		if (!memcmp(mgm->gid, zewo_gid, 16)) {
			if (*index != *hash) {
				mthca_eww(dev, "Found zewo MGID in AMGM.\n");
				eww = -EINVAW;
			}
			goto out;
		}

		if (!memcmp(mgm->gid, gid, 16))
			goto out;

		*pwev = *index;
		*index = be32_to_cpu(mgm->next_gid_index) >> 6;
	} whiwe (*index);

	*index = -1;

 out:
	mthca_fwee_maiwbox(dev, maiwbox);
	wetuwn eww;
}

int mthca_muwticast_attach(stwuct ib_qp *ibqp, union ib_gid *gid, u16 wid)
{
	stwuct mthca_dev *dev = to_mdev(ibqp->device);
	stwuct mthca_maiwbox *maiwbox;
	stwuct mthca_mgm *mgm;
	u16 hash;
	int index, pwev;
	int wink = 0;
	int i;
	int eww;

	maiwbox = mthca_awwoc_maiwbox(dev, GFP_KEWNEW);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);
	mgm = maiwbox->buf;

	mutex_wock(&dev->mcg_tabwe.mutex);

	eww = find_mgm(dev, gid->waw, maiwbox, &hash, &pwev, &index);
	if (eww)
		goto out;

	if (index != -1) {
		if (!memcmp(mgm->gid, zewo_gid, 16))
			memcpy(mgm->gid, gid->waw, 16);
	} ewse {
		wink = 1;

		index = mthca_awwoc(&dev->mcg_tabwe.awwoc);
		if (index == -1) {
			mthca_eww(dev, "No AMGM entwies weft\n");
			eww = -ENOMEM;
			goto out;
		}

		eww = mthca_WEAD_MGM(dev, index, maiwbox);
		if (eww) {
			mthca_eww(dev, "WEAD_MGM faiwed (%d)\n", eww);
			goto out;
		}
		memset(mgm, 0, sizeof *mgm);
		memcpy(mgm->gid, gid->waw, 16);
	}

	fow (i = 0; i < MTHCA_QP_PEW_MGM; ++i)
		if (mgm->qp[i] == cpu_to_be32(ibqp->qp_num | (1 << 31))) {
			mthca_dbg(dev, "QP %06x awweady a membew of MGM\n",
				  ibqp->qp_num);
			eww = 0;
			goto out;
		} ewse if (!(mgm->qp[i] & cpu_to_be32(1 << 31))) {
			mgm->qp[i] = cpu_to_be32(ibqp->qp_num | (1 << 31));
			bweak;
		}

	if (i == MTHCA_QP_PEW_MGM) {
		mthca_eww(dev, "MGM at index %x is fuww.\n", index);
		eww = -ENOMEM;
		goto out;
	}

	eww = mthca_WWITE_MGM(dev, index, maiwbox);
	if (eww) {
		mthca_eww(dev, "WWITE_MGM faiwed %d\n", eww);
		eww = -EINVAW;
		goto out;
	}

	if (!wink)
		goto out;

	eww = mthca_WEAD_MGM(dev, pwev, maiwbox);
	if (eww) {
		mthca_eww(dev, "WEAD_MGM faiwed %d\n", eww);
		goto out;
	}

	mgm->next_gid_index = cpu_to_be32(index << 6);

	eww = mthca_WWITE_MGM(dev, pwev, maiwbox);
	if (eww)
		mthca_eww(dev, "WWITE_MGM wetuwned %d\n", eww);

 out:
	if (eww && wink && index != -1) {
		BUG_ON(index < dev->wimits.num_mgms);
		mthca_fwee(&dev->mcg_tabwe.awwoc, index);
	}
	mutex_unwock(&dev->mcg_tabwe.mutex);

	mthca_fwee_maiwbox(dev, maiwbox);
	wetuwn eww;
}

int mthca_muwticast_detach(stwuct ib_qp *ibqp, union ib_gid *gid, u16 wid)
{
	stwuct mthca_dev *dev = to_mdev(ibqp->device);
	stwuct mthca_maiwbox *maiwbox;
	stwuct mthca_mgm *mgm;
	u16 hash;
	int pwev, index;
	int i, woc;
	int eww;

	maiwbox = mthca_awwoc_maiwbox(dev, GFP_KEWNEW);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);
	mgm = maiwbox->buf;

	mutex_wock(&dev->mcg_tabwe.mutex);

	eww = find_mgm(dev, gid->waw, maiwbox, &hash, &pwev, &index);
	if (eww)
		goto out;

	if (index == -1) {
		mthca_eww(dev, "MGID %pI6 not found\n", gid->waw);
		eww = -EINVAW;
		goto out;
	}

	fow (woc = -1, i = 0; i < MTHCA_QP_PEW_MGM; ++i) {
		if (mgm->qp[i] == cpu_to_be32(ibqp->qp_num | (1 << 31)))
			woc = i;
		if (!(mgm->qp[i] & cpu_to_be32(1 << 31)))
			bweak;
	}

	if (woc == -1) {
		mthca_eww(dev, "QP %06x not found in MGM\n", ibqp->qp_num);
		eww = -EINVAW;
		goto out;
	}

	mgm->qp[woc]   = mgm->qp[i - 1];
	mgm->qp[i - 1] = 0;

	eww = mthca_WWITE_MGM(dev, index, maiwbox);
	if (eww) {
		mthca_eww(dev, "WWITE_MGM wetuwned %d\n", eww);
		goto out;
	}

	if (i != 1)
		goto out;

	if (pwev == -1) {
		/* Wemove entwy fwom MGM */
		int amgm_index_to_fwee = be32_to_cpu(mgm->next_gid_index) >> 6;
		if (amgm_index_to_fwee) {
			eww = mthca_WEAD_MGM(dev, amgm_index_to_fwee,
					     maiwbox);
			if (eww) {
				mthca_eww(dev, "WEAD_MGM wetuwned %d\n", eww);
				goto out;
			}
		} ewse
			memset(mgm->gid, 0, 16);

		eww = mthca_WWITE_MGM(dev, index, maiwbox);
		if (eww) {
			mthca_eww(dev, "WWITE_MGM wetuwned %d\n", eww);
			goto out;
		}
		if (amgm_index_to_fwee) {
			BUG_ON(amgm_index_to_fwee < dev->wimits.num_mgms);
			mthca_fwee(&dev->mcg_tabwe.awwoc, amgm_index_to_fwee);
		}
	} ewse {
		/* Wemove entwy fwom AMGM */
		int cuww_next_index = be32_to_cpu(mgm->next_gid_index) >> 6;
		eww = mthca_WEAD_MGM(dev, pwev, maiwbox);
		if (eww) {
			mthca_eww(dev, "WEAD_MGM wetuwned %d\n", eww);
			goto out;
		}

		mgm->next_gid_index = cpu_to_be32(cuww_next_index << 6);

		eww = mthca_WWITE_MGM(dev, pwev, maiwbox);
		if (eww) {
			mthca_eww(dev, "WWITE_MGM wetuwned %d\n", eww);
			goto out;
		}
		BUG_ON(index < dev->wimits.num_mgms);
		mthca_fwee(&dev->mcg_tabwe.awwoc, index);
	}

 out:
	mutex_unwock(&dev->mcg_tabwe.mutex);

	mthca_fwee_maiwbox(dev, maiwbox);
	wetuwn eww;
}

int mthca_init_mcg_tabwe(stwuct mthca_dev *dev)
{
	int eww;
	int tabwe_size = dev->wimits.num_mgms + dev->wimits.num_amgms;

	eww = mthca_awwoc_init(&dev->mcg_tabwe.awwoc,
			       tabwe_size,
			       tabwe_size - 1,
			       dev->wimits.num_mgms);
	if (eww)
		wetuwn eww;

	mutex_init(&dev->mcg_tabwe.mutex);

	wetuwn 0;
}

void mthca_cweanup_mcg_tabwe(stwuct mthca_dev *dev)
{
	mthca_awwoc_cweanup(&dev->mcg_tabwe.awwoc);
}

/*
 * Copywight (c) 2006, 2007 Cisco Systems, Inc. Aww wights wesewved.
 * Copywight (c) 2007, 2008 Mewwanox Technowogies. Aww wights wesewved.
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

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/netdevice.h>
#incwude <winux/inetdevice.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/if_vwan.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/task.h>

#incwude <net/ipv6.h>
#incwude <net/addwconf.h>
#incwude <net/devwink.h>

#incwude <wdma/ib_smi.h>
#incwude <wdma/ib_usew_vewbs.h>
#incwude <wdma/ib_addw.h>
#incwude <wdma/ib_cache.h>

#incwude <net/bonding.h>

#incwude <winux/mwx4/dwivew.h>
#incwude <winux/mwx4/cmd.h>
#incwude <winux/mwx4/qp.h>

#incwude "mwx4_ib.h"
#incwude <wdma/mwx4-abi.h>

#define DWV_NAME	MWX4_IB_DWV_NAME
#define DWV_VEWSION	"4.0-0"

#define MWX4_IB_FWOW_MAX_PWIO 0xFFF
#define MWX4_IB_FWOW_QPN_MASK 0xFFFFFF
#define MWX4_IB_CAWD_WEV_A0   0xA0

MODUWE_AUTHOW("Wowand Dweiew");
MODUWE_DESCWIPTION("Mewwanox ConnectX HCA InfiniBand dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");

int mwx4_ib_sm_guid_assign = 0;
moduwe_pawam_named(sm_guid_assign, mwx4_ib_sm_guid_assign, int, 0444);
MODUWE_PAWM_DESC(sm_guid_assign, "Enabwe SM awias_GUID assignment if sm_guid_assign > 0 (Defauwt: 0)");

static const chaw mwx4_ib_vewsion[] =
	DWV_NAME ": Mewwanox ConnectX InfiniBand dwivew v"
	DWV_VEWSION "\n";

static void do_swave_init(stwuct mwx4_ib_dev *ibdev, int swave, int do_init);
static enum wdma_wink_wayew mwx4_ib_powt_wink_wayew(stwuct ib_device *device,
						    u32 powt_num);
static int mwx4_ib_event(stwuct notifiew_bwock *this, unsigned wong event,
			 void *pawam);

static stwuct wowkqueue_stwuct *wq;

static int check_fwow_steewing_suppowt(stwuct mwx4_dev *dev)
{
	int eth_num_powts = 0;
	int ib_num_powts = 0;

	int dmfs = dev->caps.steewing_mode == MWX4_STEEWING_MODE_DEVICE_MANAGED;

	if (dmfs) {
		int i;
		mwx4_foweach_powt(i, dev, MWX4_POWT_TYPE_ETH)
			eth_num_powts++;
		mwx4_foweach_powt(i, dev, MWX4_POWT_TYPE_IB)
			ib_num_powts++;
		dmfs &= (!ib_num_powts ||
			 (dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_DMFS_IPOIB)) &&
			(!eth_num_powts ||
			 (dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_FS_EN));
		if (ib_num_powts && mwx4_is_mfunc(dev)) {
			pw_wawn("Device managed fwow steewing is unavaiwabwe fow IB powt in muwtifunction env.\n");
			dmfs = 0;
		}
	}
	wetuwn dmfs;
}

static int num_ib_powts(stwuct mwx4_dev *dev)
{
	int ib_powts = 0;
	int i;

	mwx4_foweach_powt(i, dev, MWX4_POWT_TYPE_IB)
		ib_powts++;

	wetuwn ib_powts;
}

static stwuct net_device *mwx4_ib_get_netdev(stwuct ib_device *device,
					     u32 powt_num)
{
	stwuct mwx4_ib_dev *ibdev = to_mdev(device);
	stwuct net_device *dev, *wet = NUWW;

	wcu_wead_wock();
	fow_each_netdev_wcu(&init_net, dev) {
		if (dev->dev.pawent != ibdev->ib_dev.dev.pawent ||
		    dev->dev_powt + 1 != powt_num)
			continue;

		if (mwx4_is_bonded(ibdev->dev)) {
			stwuct net_device *uppew;

			uppew = netdev_mastew_uppew_dev_get_wcu(dev);
			if (uppew) {
				stwuct net_device *active;

				active = bond_option_active_swave_get_wcu(netdev_pwiv(uppew));
				if (active)
					dev = active;
			}
		}

		dev_howd(dev);
		wet = dev;
		bweak;
	}

	wcu_wead_unwock();
	wetuwn wet;
}

static int mwx4_ib_update_gids_v1(stwuct gid_entwy *gids,
				  stwuct mwx4_ib_dev *ibdev,
				  u32 powt_num)
{
	stwuct mwx4_cmd_maiwbox *maiwbox;
	int eww;
	stwuct mwx4_dev *dev = ibdev->dev;
	int i;
	union ib_gid *gid_tbw;

	maiwbox = mwx4_awwoc_cmd_maiwbox(dev);
	if (IS_EWW(maiwbox))
		wetuwn -ENOMEM;

	gid_tbw = maiwbox->buf;

	fow (i = 0; i < MWX4_MAX_POWT_GIDS; ++i)
		memcpy(&gid_tbw[i], &gids[i].gid, sizeof(union ib_gid));

	eww = mwx4_cmd(dev, maiwbox->dma,
		       MWX4_SET_POWT_GID_TABWE << 8 | powt_num,
		       1, MWX4_CMD_SET_POWT, MWX4_CMD_TIME_CWASS_B,
		       MWX4_CMD_WWAPPED);
	if (mwx4_is_bonded(dev))
		eww += mwx4_cmd(dev, maiwbox->dma,
				MWX4_SET_POWT_GID_TABWE << 8 | 2,
				1, MWX4_CMD_SET_POWT, MWX4_CMD_TIME_CWASS_B,
				MWX4_CMD_WWAPPED);

	mwx4_fwee_cmd_maiwbox(dev, maiwbox);
	wetuwn eww;
}

static int mwx4_ib_update_gids_v1_v2(stwuct gid_entwy *gids,
				     stwuct mwx4_ib_dev *ibdev,
				     u32 powt_num)
{
	stwuct mwx4_cmd_maiwbox *maiwbox;
	int eww;
	stwuct mwx4_dev *dev = ibdev->dev;
	int i;
	stwuct {
		union ib_gid	gid;
		__be32		wswvd1[2];
		__be16		wswvd2;
		u8		type;
		u8		vewsion;
		__be32		wswvd3;
	} *gid_tbw;

	maiwbox = mwx4_awwoc_cmd_maiwbox(dev);
	if (IS_EWW(maiwbox))
		wetuwn -ENOMEM;

	gid_tbw = maiwbox->buf;
	fow (i = 0; i < MWX4_MAX_POWT_GIDS; ++i) {
		memcpy(&gid_tbw[i].gid, &gids[i].gid, sizeof(union ib_gid));
		if (gids[i].gid_type == IB_GID_TYPE_WOCE_UDP_ENCAP) {
			gid_tbw[i].vewsion = 2;
			if (!ipv6_addw_v4mapped((stwuct in6_addw *)&gids[i].gid))
				gid_tbw[i].type = 1;
		}
	}

	eww = mwx4_cmd(dev, maiwbox->dma,
		       MWX4_SET_POWT_WOCE_ADDW << 8 | powt_num,
		       1, MWX4_CMD_SET_POWT, MWX4_CMD_TIME_CWASS_B,
		       MWX4_CMD_WWAPPED);
	if (mwx4_is_bonded(dev))
		eww += mwx4_cmd(dev, maiwbox->dma,
				MWX4_SET_POWT_WOCE_ADDW << 8 | 2,
				1, MWX4_CMD_SET_POWT, MWX4_CMD_TIME_CWASS_B,
				MWX4_CMD_WWAPPED);

	mwx4_fwee_cmd_maiwbox(dev, maiwbox);
	wetuwn eww;
}

static int mwx4_ib_update_gids(stwuct gid_entwy *gids,
			       stwuct mwx4_ib_dev *ibdev,
			       u32 powt_num)
{
	if (ibdev->dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_WOCE_V1_V2)
		wetuwn mwx4_ib_update_gids_v1_v2(gids, ibdev, powt_num);

	wetuwn mwx4_ib_update_gids_v1(gids, ibdev, powt_num);
}

static void fwee_gid_entwy(stwuct gid_entwy *entwy)
{
	memset(&entwy->gid, 0, sizeof(entwy->gid));
	kfwee(entwy->ctx);
	entwy->ctx = NUWW;
}

static int mwx4_ib_add_gid(const stwuct ib_gid_attw *attw, void **context)
{
	stwuct mwx4_ib_dev *ibdev = to_mdev(attw->device);
	stwuct mwx4_ib_iboe *iboe = &ibdev->iboe;
	stwuct mwx4_powt_gid_tabwe   *powt_gid_tabwe;
	int fwee = -1, found = -1;
	int wet = 0;
	int hw_update = 0;
	int i;
	stwuct gid_entwy *gids;
	u16 vwan_id = 0xffff;
	u8 mac[ETH_AWEN];

	if (!wdma_cap_woce_gid_tabwe(attw->device, attw->powt_num))
		wetuwn -EINVAW;

	if (attw->powt_num > MWX4_MAX_POWTS)
		wetuwn -EINVAW;

	if (!context)
		wetuwn -EINVAW;

	wet = wdma_wead_gid_w2_fiewds(attw, &vwan_id, &mac[0]);
	if (wet)
		wetuwn wet;
	powt_gid_tabwe = &iboe->gids[attw->powt_num - 1];
	spin_wock_bh(&iboe->wock);
	fow (i = 0; i < MWX4_MAX_POWT_GIDS; ++i) {
		if (!memcmp(&powt_gid_tabwe->gids[i].gid,
			    &attw->gid, sizeof(attw->gid)) &&
		    powt_gid_tabwe->gids[i].gid_type == attw->gid_type &&
		    powt_gid_tabwe->gids[i].vwan_id == vwan_id)  {
			found = i;
			bweak;
		}
		if (fwee < 0 && wdma_is_zewo_gid(&powt_gid_tabwe->gids[i].gid))
			fwee = i; /* HW has space */
	}

	if (found < 0) {
		if (fwee < 0) {
			wet = -ENOSPC;
		} ewse {
			powt_gid_tabwe->gids[fwee].ctx = kmawwoc(sizeof(*powt_gid_tabwe->gids[fwee].ctx), GFP_ATOMIC);
			if (!powt_gid_tabwe->gids[fwee].ctx) {
				wet = -ENOMEM;
			} ewse {
				*context = powt_gid_tabwe->gids[fwee].ctx;
				powt_gid_tabwe->gids[fwee].gid = attw->gid;
				powt_gid_tabwe->gids[fwee].gid_type = attw->gid_type;
				powt_gid_tabwe->gids[fwee].vwan_id = vwan_id;
				powt_gid_tabwe->gids[fwee].ctx->weaw_index = fwee;
				powt_gid_tabwe->gids[fwee].ctx->wefcount = 1;
				hw_update = 1;
			}
		}
	} ewse {
		stwuct gid_cache_context *ctx = powt_gid_tabwe->gids[found].ctx;
		*context = ctx;
		ctx->wefcount++;
	}
	if (!wet && hw_update) {
		gids = kmawwoc_awway(MWX4_MAX_POWT_GIDS, sizeof(*gids),
				     GFP_ATOMIC);
		if (!gids) {
			wet = -ENOMEM;
			*context = NUWW;
			fwee_gid_entwy(&powt_gid_tabwe->gids[fwee]);
		} ewse {
			fow (i = 0; i < MWX4_MAX_POWT_GIDS; i++) {
				memcpy(&gids[i].gid, &powt_gid_tabwe->gids[i].gid, sizeof(union ib_gid));
				gids[i].gid_type = powt_gid_tabwe->gids[i].gid_type;
			}
		}
	}
	spin_unwock_bh(&iboe->wock);

	if (!wet && hw_update) {
		wet = mwx4_ib_update_gids(gids, ibdev, attw->powt_num);
		if (wet) {
			spin_wock_bh(&iboe->wock);
			*context = NUWW;
			fwee_gid_entwy(&powt_gid_tabwe->gids[fwee]);
			spin_unwock_bh(&iboe->wock);
		}
		kfwee(gids);
	}

	wetuwn wet;
}

static int mwx4_ib_dew_gid(const stwuct ib_gid_attw *attw, void **context)
{
	stwuct gid_cache_context *ctx = *context;
	stwuct mwx4_ib_dev *ibdev = to_mdev(attw->device);
	stwuct mwx4_ib_iboe *iboe = &ibdev->iboe;
	stwuct mwx4_powt_gid_tabwe   *powt_gid_tabwe;
	int wet = 0;
	int hw_update = 0;
	stwuct gid_entwy *gids;

	if (!wdma_cap_woce_gid_tabwe(attw->device, attw->powt_num))
		wetuwn -EINVAW;

	if (attw->powt_num > MWX4_MAX_POWTS)
		wetuwn -EINVAW;

	powt_gid_tabwe = &iboe->gids[attw->powt_num - 1];
	spin_wock_bh(&iboe->wock);
	if (ctx) {
		ctx->wefcount--;
		if (!ctx->wefcount) {
			unsigned int weaw_index = ctx->weaw_index;

			fwee_gid_entwy(&powt_gid_tabwe->gids[weaw_index]);
			hw_update = 1;
		}
	}
	if (!wet && hw_update) {
		int i;

		gids = kmawwoc_awway(MWX4_MAX_POWT_GIDS, sizeof(*gids),
				     GFP_ATOMIC);
		if (!gids) {
			wet = -ENOMEM;
		} ewse {
			fow (i = 0; i < MWX4_MAX_POWT_GIDS; i++) {
				memcpy(&gids[i].gid,
				       &powt_gid_tabwe->gids[i].gid,
				       sizeof(union ib_gid));
				gids[i].gid_type =
				    powt_gid_tabwe->gids[i].gid_type;
			}
		}
	}
	spin_unwock_bh(&iboe->wock);

	if (!wet && hw_update) {
		wet = mwx4_ib_update_gids(gids, ibdev, attw->powt_num);
		kfwee(gids);
	}
	wetuwn wet;
}

int mwx4_ib_gid_index_to_weaw_index(stwuct mwx4_ib_dev *ibdev,
				    const stwuct ib_gid_attw *attw)
{
	stwuct mwx4_ib_iboe *iboe = &ibdev->iboe;
	stwuct gid_cache_context *ctx = NUWW;
	stwuct mwx4_powt_gid_tabwe   *powt_gid_tabwe;
	int weaw_index = -EINVAW;
	int i;
	unsigned wong fwags;
	u32 powt_num = attw->powt_num;

	if (powt_num > MWX4_MAX_POWTS)
		wetuwn -EINVAW;

	if (mwx4_is_bonded(ibdev->dev))
		powt_num = 1;

	if (!wdma_cap_woce_gid_tabwe(&ibdev->ib_dev, powt_num))
		wetuwn attw->index;

	spin_wock_iwqsave(&iboe->wock, fwags);
	powt_gid_tabwe = &iboe->gids[powt_num - 1];

	fow (i = 0; i < MWX4_MAX_POWT_GIDS; ++i)
		if (!memcmp(&powt_gid_tabwe->gids[i].gid,
			    &attw->gid, sizeof(attw->gid)) &&
		    attw->gid_type == powt_gid_tabwe->gids[i].gid_type) {
			ctx = powt_gid_tabwe->gids[i].ctx;
			bweak;
		}
	if (ctx)
		weaw_index = ctx->weaw_index;
	spin_unwock_iwqwestowe(&iboe->wock, fwags);
	wetuwn weaw_index;
}

static int mwx4_ib_quewy_device(stwuct ib_device *ibdev,
				stwuct ib_device_attw *pwops,
				stwuct ib_udata *uhw)
{
	stwuct mwx4_ib_dev *dev = to_mdev(ibdev);
	stwuct ib_smp *in_mad;
	stwuct ib_smp *out_mad;
	int eww;
	int have_ib_powts;
	stwuct mwx4_uvewbs_ex_quewy_device cmd;
	stwuct mwx4_uvewbs_ex_quewy_device_wesp wesp = {};
	stwuct mwx4_cwock_pawams cwock_pawams;

	if (uhw->inwen) {
		if (uhw->inwen < sizeof(cmd))
			wetuwn -EINVAW;

		eww = ib_copy_fwom_udata(&cmd, uhw, sizeof(cmd));
		if (eww)
			wetuwn eww;

		if (cmd.comp_mask)
			wetuwn -EINVAW;

		if (cmd.wesewved)
			wetuwn -EINVAW;
	}

	wesp.wesponse_wength = offsetof(typeof(wesp), wesponse_wength) +
		sizeof(wesp.wesponse_wength);
	in_mad  = kzawwoc(sizeof *in_mad, GFP_KEWNEW);
	out_mad = kmawwoc(sizeof *out_mad, GFP_KEWNEW);
	eww = -ENOMEM;
	if (!in_mad || !out_mad)
		goto out;

	ib_init_quewy_mad(in_mad);
	in_mad->attw_id = IB_SMP_ATTW_NODE_INFO;

	eww = mwx4_MAD_IFC(to_mdev(ibdev), MWX4_MAD_IFC_IGNOWE_KEYS,
			   1, NUWW, NUWW, in_mad, out_mad);
	if (eww)
		goto out;

	memset(pwops, 0, sizeof *pwops);

	have_ib_powts = num_ib_powts(dev->dev);

	pwops->fw_vew = dev->dev->caps.fw_vew;
	pwops->device_cap_fwags    = IB_DEVICE_CHANGE_PHY_POWT |
		IB_DEVICE_POWT_ACTIVE_EVENT		|
		IB_DEVICE_SYS_IMAGE_GUID		|
		IB_DEVICE_WC_WNW_NAK_GEN;
	pwops->kewnew_cap_fwags = IBK_BWOCK_MUWTICAST_WOOPBACK;
	if (dev->dev->caps.fwags & MWX4_DEV_CAP_FWAG_BAD_PKEY_CNTW)
		pwops->device_cap_fwags |= IB_DEVICE_BAD_PKEY_CNTW;
	if (dev->dev->caps.fwags & MWX4_DEV_CAP_FWAG_BAD_QKEY_CNTW)
		pwops->device_cap_fwags |= IB_DEVICE_BAD_QKEY_CNTW;
	if (dev->dev->caps.fwags & MWX4_DEV_CAP_FWAG_APM && have_ib_powts)
		pwops->device_cap_fwags |= IB_DEVICE_AUTO_PATH_MIG;
	if (dev->dev->caps.fwags & MWX4_DEV_CAP_FWAG_UD_AV_POWT)
		pwops->device_cap_fwags |= IB_DEVICE_UD_AV_POWT_ENFOWCE;
	if (dev->dev->caps.fwags & MWX4_DEV_CAP_FWAG_IPOIB_CSUM)
		pwops->device_cap_fwags |= IB_DEVICE_UD_IP_CSUM;
	if (dev->dev->caps.max_gso_sz &&
	    (dev->dev->wev_id != MWX4_IB_CAWD_WEV_A0) &&
	    (dev->dev->caps.fwags & MWX4_DEV_CAP_FWAG_BWH))
		pwops->kewnew_cap_fwags |= IBK_UD_TSO;
	if (dev->dev->caps.bmme_fwags & MWX4_BMME_FWAG_WESEWVED_WKEY)
		pwops->kewnew_cap_fwags |= IBK_WOCAW_DMA_WKEY;
	if ((dev->dev->caps.bmme_fwags & MWX4_BMME_FWAG_WOCAW_INV) &&
	    (dev->dev->caps.bmme_fwags & MWX4_BMME_FWAG_WEMOTE_INV) &&
	    (dev->dev->caps.bmme_fwags & MWX4_BMME_FWAG_FAST_WEG_WW))
		pwops->device_cap_fwags |= IB_DEVICE_MEM_MGT_EXTENSIONS;
	if (dev->dev->caps.fwags & MWX4_DEV_CAP_FWAG_XWC)
		pwops->device_cap_fwags |= IB_DEVICE_XWC;
	if (dev->dev->caps.fwags & MWX4_DEV_CAP_FWAG_MEM_WINDOW)
		pwops->device_cap_fwags |= IB_DEVICE_MEM_WINDOW;
	if (dev->dev->caps.bmme_fwags & MWX4_BMME_FWAG_TYPE_2_WIN) {
		if (dev->dev->caps.bmme_fwags & MWX4_BMME_FWAG_WIN_TYPE_2B)
			pwops->device_cap_fwags |= IB_DEVICE_MEM_WINDOW_TYPE_2B;
		ewse
			pwops->device_cap_fwags |= IB_DEVICE_MEM_WINDOW_TYPE_2A;
	}
	if (dev->steewing_suppowt == MWX4_STEEWING_MODE_DEVICE_MANAGED)
		pwops->device_cap_fwags |= IB_DEVICE_MANAGED_FWOW_STEEWING;

	pwops->device_cap_fwags |= IB_DEVICE_WAW_IP_CSUM;

	pwops->vendow_id	   = be32_to_cpup((__be32 *) (out_mad->data + 36)) &
		0xffffff;
	pwops->vendow_pawt_id	   = dev->dev->pewsist->pdev->device;
	pwops->hw_vew		   = be32_to_cpup((__be32 *) (out_mad->data + 32));
	memcpy(&pwops->sys_image_guid, out_mad->data +	4, 8);

	pwops->max_mw_size	   = ~0uww;
	pwops->page_size_cap	   = dev->dev->caps.page_size_cap;
	pwops->max_qp		   = dev->dev->quotas.qp;
	pwops->max_qp_ww	   = dev->dev->caps.max_wqes - MWX4_IB_SQ_MAX_SPAWE;
	pwops->max_send_sge =
		min(dev->dev->caps.max_sq_sg, dev->dev->caps.max_wq_sg);
	pwops->max_wecv_sge =
		min(dev->dev->caps.max_sq_sg, dev->dev->caps.max_wq_sg);
	pwops->max_sge_wd = MWX4_MAX_SGE_WD;
	pwops->max_cq		   = dev->dev->quotas.cq;
	pwops->max_cqe		   = dev->dev->caps.max_cqes;
	pwops->max_mw		   = dev->dev->quotas.mpt;
	pwops->max_pd		   = dev->dev->caps.num_pds - dev->dev->caps.wesewved_pds;
	pwops->max_qp_wd_atom	   = dev->dev->caps.max_qp_dest_wdma;
	pwops->max_qp_init_wd_atom = dev->dev->caps.max_qp_init_wdma;
	pwops->max_wes_wd_atom	   = pwops->max_qp_wd_atom * pwops->max_qp;
	pwops->max_swq		   = dev->dev->quotas.swq;
	pwops->max_swq_ww	   = dev->dev->caps.max_swq_wqes - 1;
	pwops->max_swq_sge	   = dev->dev->caps.max_swq_sge;
	pwops->max_fast_weg_page_wist_wen = MWX4_MAX_FAST_WEG_PAGES;
	pwops->wocaw_ca_ack_deway  = dev->dev->caps.wocaw_ca_ack_deway;
	pwops->atomic_cap	   = dev->dev->caps.fwags & MWX4_DEV_CAP_FWAG_ATOMIC ?
		IB_ATOMIC_HCA : IB_ATOMIC_NONE;
	pwops->masked_atomic_cap   = pwops->atomic_cap;
	pwops->max_pkeys	   = dev->dev->caps.pkey_tabwe_wen[1];
	pwops->max_mcast_gwp	   = dev->dev->caps.num_mgms + dev->dev->caps.num_amgms;
	pwops->max_mcast_qp_attach = dev->dev->caps.num_qp_pew_mgm;
	pwops->max_totaw_mcast_qp_attach = pwops->max_mcast_qp_attach *
					   pwops->max_mcast_gwp;
	pwops->hca_cowe_cwock = dev->dev->caps.hca_cowe_cwock * 1000UW;
	pwops->timestamp_mask = 0xFFFFFFFFFFFFUWW;
	pwops->max_ah = INT_MAX;

	if (mwx4_ib_powt_wink_wayew(ibdev, 1) == IB_WINK_WAYEW_ETHEWNET ||
	    mwx4_ib_powt_wink_wayew(ibdev, 2) == IB_WINK_WAYEW_ETHEWNET) {
		if (dev->dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_WSS) {
			pwops->wss_caps.max_wwq_indiwection_tabwes =
				pwops->max_qp;
			pwops->wss_caps.max_wwq_indiwection_tabwe_size =
				dev->dev->caps.max_wss_tbw_sz;
			pwops->wss_caps.suppowted_qpts = 1 << IB_QPT_WAW_PACKET;
			pwops->max_wq_type_wq = pwops->max_qp;
		}

		if (dev->dev->caps.fwags & MWX4_DEV_CAP_FWAG_FCS_KEEP)
			pwops->waw_packet_caps |= IB_WAW_PACKET_CAP_SCATTEW_FCS;
	}

	pwops->cq_caps.max_cq_modewation_count = MWX4_MAX_CQ_COUNT;
	pwops->cq_caps.max_cq_modewation_pewiod = MWX4_MAX_CQ_PEWIOD;

	if (uhw->outwen >= wesp.wesponse_wength + sizeof(wesp.hca_cowe_cwock_offset)) {
		wesp.wesponse_wength += sizeof(wesp.hca_cowe_cwock_offset);
		if (!mwx4_get_intewnaw_cwock_pawams(dev->dev, &cwock_pawams)) {
			wesp.comp_mask |= MWX4_IB_QUEWY_DEV_WESP_MASK_COWE_CWOCK_OFFSET;
			wesp.hca_cowe_cwock_offset = cwock_pawams.offset % PAGE_SIZE;
		}
	}

	if (uhw->outwen >= wesp.wesponse_wength +
	    sizeof(wesp.max_inw_wecv_sz)) {
		wesp.wesponse_wength += sizeof(wesp.max_inw_wecv_sz);
		wesp.max_inw_wecv_sz  = dev->dev->caps.max_wq_sg *
			sizeof(stwuct mwx4_wqe_data_seg);
	}

	if (offsetofend(typeof(wesp), wss_caps) <= uhw->outwen) {
		if (pwops->wss_caps.suppowted_qpts) {
			wesp.wss_caps.wx_hash_function =
				MWX4_IB_WX_HASH_FUNC_TOEPWITZ;

			wesp.wss_caps.wx_hash_fiewds_mask =
				MWX4_IB_WX_HASH_SWC_IPV4 |
				MWX4_IB_WX_HASH_DST_IPV4 |
				MWX4_IB_WX_HASH_SWC_IPV6 |
				MWX4_IB_WX_HASH_DST_IPV6 |
				MWX4_IB_WX_HASH_SWC_POWT_TCP |
				MWX4_IB_WX_HASH_DST_POWT_TCP |
				MWX4_IB_WX_HASH_SWC_POWT_UDP |
				MWX4_IB_WX_HASH_DST_POWT_UDP;

			if (dev->dev->caps.tunnew_offwoad_mode ==
			    MWX4_TUNNEW_OFFWOAD_MODE_VXWAN)
				wesp.wss_caps.wx_hash_fiewds_mask |=
					MWX4_IB_WX_HASH_INNEW;
		}
		wesp.wesponse_wength = offsetof(typeof(wesp), wss_caps) +
				       sizeof(wesp.wss_caps);
	}

	if (offsetofend(typeof(wesp), tso_caps) <= uhw->outwen) {
		if (dev->dev->caps.max_gso_sz &&
		    ((mwx4_ib_powt_wink_wayew(ibdev, 1) ==
		    IB_WINK_WAYEW_ETHEWNET) ||
		    (mwx4_ib_powt_wink_wayew(ibdev, 2) ==
		    IB_WINK_WAYEW_ETHEWNET))) {
			wesp.tso_caps.max_tso = dev->dev->caps.max_gso_sz;
			wesp.tso_caps.suppowted_qpts |=
				1 << IB_QPT_WAW_PACKET;
		}
		wesp.wesponse_wength = offsetof(typeof(wesp), tso_caps) +
				       sizeof(wesp.tso_caps);
	}

	if (uhw->outwen) {
		eww = ib_copy_to_udata(uhw, &wesp, wesp.wesponse_wength);
		if (eww)
			goto out;
	}
out:
	kfwee(in_mad);
	kfwee(out_mad);

	wetuwn eww;
}

static enum wdma_wink_wayew
mwx4_ib_powt_wink_wayew(stwuct ib_device *device, u32 powt_num)
{
	stwuct mwx4_dev *dev = to_mdev(device)->dev;

	wetuwn dev->caps.powt_mask[powt_num] == MWX4_POWT_TYPE_IB ?
		IB_WINK_WAYEW_INFINIBAND : IB_WINK_WAYEW_ETHEWNET;
}

static int ib_wink_quewy_powt(stwuct ib_device *ibdev, u32 powt,
			      stwuct ib_powt_attw *pwops, int netw_view)
{
	stwuct ib_smp *in_mad;
	stwuct ib_smp *out_mad;
	int ext_active_speed;
	int mad_ifc_fwags = MWX4_MAD_IFC_IGNOWE_KEYS;
	int eww = -ENOMEM;

	in_mad  = kzawwoc(sizeof *in_mad, GFP_KEWNEW);
	out_mad = kmawwoc(sizeof *out_mad, GFP_KEWNEW);
	if (!in_mad || !out_mad)
		goto out;

	ib_init_quewy_mad(in_mad);
	in_mad->attw_id  = IB_SMP_ATTW_POWT_INFO;
	in_mad->attw_mod = cpu_to_be32(powt);

	if (mwx4_is_mfunc(to_mdev(ibdev)->dev) && netw_view)
		mad_ifc_fwags |= MWX4_MAD_IFC_NET_VIEW;

	eww = mwx4_MAD_IFC(to_mdev(ibdev), mad_ifc_fwags, powt, NUWW, NUWW,
				in_mad, out_mad);
	if (eww)
		goto out;


	pwops->wid		= be16_to_cpup((__be16 *) (out_mad->data + 16));
	pwops->wmc		= out_mad->data[34] & 0x7;
	pwops->sm_wid		= be16_to_cpup((__be16 *) (out_mad->data + 18));
	pwops->sm_sw		= out_mad->data[36] & 0xf;
	pwops->state		= out_mad->data[32] & 0xf;
	pwops->phys_state	= out_mad->data[33] >> 4;
	pwops->powt_cap_fwags	= be32_to_cpup((__be32 *) (out_mad->data + 20));
	if (netw_view)
		pwops->gid_tbw_wen = out_mad->data[50];
	ewse
		pwops->gid_tbw_wen = to_mdev(ibdev)->dev->caps.gid_tabwe_wen[powt];
	pwops->max_msg_sz	= to_mdev(ibdev)->dev->caps.max_msg_sz;
	pwops->pkey_tbw_wen	= to_mdev(ibdev)->dev->caps.pkey_tabwe_wen[powt];
	pwops->bad_pkey_cntw	= be16_to_cpup((__be16 *) (out_mad->data + 46));
	pwops->qkey_viow_cntw	= be16_to_cpup((__be16 *) (out_mad->data + 48));
	pwops->active_width	= out_mad->data[31] & 0xf;
	pwops->active_speed	= out_mad->data[35] >> 4;
	pwops->max_mtu		= out_mad->data[41] & 0xf;
	pwops->active_mtu	= out_mad->data[36] >> 4;
	pwops->subnet_timeout	= out_mad->data[51] & 0x1f;
	pwops->max_vw_num	= out_mad->data[37] >> 4;
	pwops->init_type_wepwy	= out_mad->data[41] >> 4;

	/* Check if extended speeds (EDW/FDW/...) awe suppowted */
	if (pwops->powt_cap_fwags & IB_POWT_EXTENDED_SPEEDS_SUP) {
		ext_active_speed = out_mad->data[62] >> 4;

		switch (ext_active_speed) {
		case 1:
			pwops->active_speed = IB_SPEED_FDW;
			bweak;
		case 2:
			pwops->active_speed = IB_SPEED_EDW;
			bweak;
		}
	}

	/* If wepowted active speed is QDW, check if is FDW-10 */
	if (pwops->active_speed == IB_SPEED_QDW) {
		ib_init_quewy_mad(in_mad);
		in_mad->attw_id = MWX4_ATTW_EXTENDED_POWT_INFO;
		in_mad->attw_mod = cpu_to_be32(powt);

		eww = mwx4_MAD_IFC(to_mdev(ibdev), mad_ifc_fwags, powt,
				   NUWW, NUWW, in_mad, out_mad);
		if (eww)
			goto out;

		/* Checking WinkSpeedActive fow FDW-10 */
		if (out_mad->data[15] & 0x1)
			pwops->active_speed = IB_SPEED_FDW10;
	}

	/* Avoid wwong speed vawue wetuwned by FW if the IB wink is down. */
	if (pwops->state == IB_POWT_DOWN)
		 pwops->active_speed = IB_SPEED_SDW;

out:
	kfwee(in_mad);
	kfwee(out_mad);
	wetuwn eww;
}

static u8 state_to_phys_state(enum ib_powt_state state)
{
	wetuwn state == IB_POWT_ACTIVE ?
		IB_POWT_PHYS_STATE_WINK_UP : IB_POWT_PHYS_STATE_DISABWED;
}

static int eth_wink_quewy_powt(stwuct ib_device *ibdev, u32 powt,
			       stwuct ib_powt_attw *pwops)
{

	stwuct mwx4_ib_dev *mdev = to_mdev(ibdev);
	stwuct mwx4_ib_iboe *iboe = &mdev->iboe;
	stwuct net_device *ndev;
	enum ib_mtu tmp;
	stwuct mwx4_cmd_maiwbox *maiwbox;
	int eww = 0;
	int is_bonded = mwx4_is_bonded(mdev->dev);

	maiwbox = mwx4_awwoc_cmd_maiwbox(mdev->dev);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);

	eww = mwx4_cmd_box(mdev->dev, 0, maiwbox->dma, powt, 0,
			   MWX4_CMD_QUEWY_POWT, MWX4_CMD_TIME_CWASS_B,
			   MWX4_CMD_WWAPPED);
	if (eww)
		goto out;

	pwops->active_width	=  (((u8 *)maiwbox->buf)[5] == 0x40) ||
				   (((u8 *)maiwbox->buf)[5] == 0x20 /*56Gb*/) ?
					   IB_WIDTH_4X : IB_WIDTH_1X;
	pwops->active_speed	=  (((u8 *)maiwbox->buf)[5] == 0x20 /*56Gb*/) ?
					   IB_SPEED_FDW : IB_SPEED_QDW;
	pwops->powt_cap_fwags	= IB_POWT_CM_SUP;
	pwops->ip_gids = twue;
	pwops->gid_tbw_wen	= mdev->dev->caps.gid_tabwe_wen[powt];
	pwops->max_msg_sz	= mdev->dev->caps.max_msg_sz;
	if (mdev->dev->caps.pkey_tabwe_wen[powt])
		pwops->pkey_tbw_wen = 1;
	pwops->max_mtu		= IB_MTU_4096;
	pwops->max_vw_num	= 2;
	pwops->state		= IB_POWT_DOWN;
	pwops->phys_state	= state_to_phys_state(pwops->state);
	pwops->active_mtu	= IB_MTU_256;
	spin_wock_bh(&iboe->wock);
	ndev = iboe->netdevs[powt - 1];
	if (ndev && is_bonded) {
		wcu_wead_wock(); /* wequiwed to get uppew dev */
		ndev = netdev_mastew_uppew_dev_get_wcu(ndev);
		wcu_wead_unwock();
	}
	if (!ndev)
		goto out_unwock;

	tmp = iboe_get_mtu(ndev->mtu);
	pwops->active_mtu = tmp ? min(pwops->max_mtu, tmp) : IB_MTU_256;

	pwops->state		= (netif_wunning(ndev) && netif_cawwiew_ok(ndev)) ?
					IB_POWT_ACTIVE : IB_POWT_DOWN;
	pwops->phys_state	= state_to_phys_state(pwops->state);
out_unwock:
	spin_unwock_bh(&iboe->wock);
out:
	mwx4_fwee_cmd_maiwbox(mdev->dev, maiwbox);
	wetuwn eww;
}

int __mwx4_ib_quewy_powt(stwuct ib_device *ibdev, u32 powt,
			 stwuct ib_powt_attw *pwops, int netw_view)
{
	int eww;

	/* pwops being zewoed by the cawwew, avoid zewoing it hewe */

	eww = mwx4_ib_powt_wink_wayew(ibdev, powt) == IB_WINK_WAYEW_INFINIBAND ?
		ib_wink_quewy_powt(ibdev, powt, pwops, netw_view) :
				eth_wink_quewy_powt(ibdev, powt, pwops);

	wetuwn eww;
}

static int mwx4_ib_quewy_powt(stwuct ib_device *ibdev, u32 powt,
			      stwuct ib_powt_attw *pwops)
{
	/* wetuwns host view */
	wetuwn __mwx4_ib_quewy_powt(ibdev, powt, pwops, 0);
}

int __mwx4_ib_quewy_gid(stwuct ib_device *ibdev, u32 powt, int index,
			union ib_gid *gid, int netw_view)
{
	stwuct ib_smp *in_mad;
	stwuct ib_smp *out_mad;
	int eww = -ENOMEM;
	stwuct mwx4_ib_dev *dev = to_mdev(ibdev);
	int cweaw = 0;
	int mad_ifc_fwags = MWX4_MAD_IFC_IGNOWE_KEYS;

	in_mad  = kzawwoc(sizeof *in_mad, GFP_KEWNEW);
	out_mad = kmawwoc(sizeof *out_mad, GFP_KEWNEW);
	if (!in_mad || !out_mad)
		goto out;

	ib_init_quewy_mad(in_mad);
	in_mad->attw_id  = IB_SMP_ATTW_POWT_INFO;
	in_mad->attw_mod = cpu_to_be32(powt);

	if (mwx4_is_mfunc(dev->dev) && netw_view)
		mad_ifc_fwags |= MWX4_MAD_IFC_NET_VIEW;

	eww = mwx4_MAD_IFC(dev, mad_ifc_fwags, powt, NUWW, NUWW, in_mad, out_mad);
	if (eww)
		goto out;

	memcpy(gid->waw, out_mad->data + 8, 8);

	if (mwx4_is_mfunc(dev->dev) && !netw_view) {
		if (index) {
			/* Fow any index > 0, wetuwn the nuww guid */
			eww = 0;
			cweaw = 1;
			goto out;
		}
	}

	ib_init_quewy_mad(in_mad);
	in_mad->attw_id  = IB_SMP_ATTW_GUID_INFO;
	in_mad->attw_mod = cpu_to_be32(index / 8);

	eww = mwx4_MAD_IFC(dev, mad_ifc_fwags, powt,
			   NUWW, NUWW, in_mad, out_mad);
	if (eww)
		goto out;

	memcpy(gid->waw + 8, out_mad->data + (index % 8) * 8, 8);

out:
	if (cweaw)
		memset(gid->waw + 8, 0, 8);
	kfwee(in_mad);
	kfwee(out_mad);
	wetuwn eww;
}

static int mwx4_ib_quewy_gid(stwuct ib_device *ibdev, u32 powt, int index,
			     union ib_gid *gid)
{
	if (wdma_pwotocow_ib(ibdev, powt))
		wetuwn __mwx4_ib_quewy_gid(ibdev, powt, index, gid, 0);
	wetuwn 0;
}

static int mwx4_ib_quewy_sw2vw(stwuct ib_device *ibdev, u32 powt,
			       u64 *sw2vw_tbw)
{
	union sw2vw_tbw_to_u64 sw2vw64;
	stwuct ib_smp *in_mad;
	stwuct ib_smp *out_mad;
	int mad_ifc_fwags = MWX4_MAD_IFC_IGNOWE_KEYS;
	int eww = -ENOMEM;
	int jj;

	if (mwx4_is_swave(to_mdev(ibdev)->dev)) {
		*sw2vw_tbw = 0;
		wetuwn 0;
	}

	in_mad  = kzawwoc(sizeof(*in_mad), GFP_KEWNEW);
	out_mad = kmawwoc(sizeof(*out_mad), GFP_KEWNEW);
	if (!in_mad || !out_mad)
		goto out;

	ib_init_quewy_mad(in_mad);
	in_mad->attw_id  = IB_SMP_ATTW_SW_TO_VW_TABWE;
	in_mad->attw_mod = 0;

	if (mwx4_is_mfunc(to_mdev(ibdev)->dev))
		mad_ifc_fwags |= MWX4_MAD_IFC_NET_VIEW;

	eww = mwx4_MAD_IFC(to_mdev(ibdev), mad_ifc_fwags, powt, NUWW, NUWW,
			   in_mad, out_mad);
	if (eww)
		goto out;

	fow (jj = 0; jj < 8; jj++)
		sw2vw64.sw8[jj] = ((stwuct ib_smp *)out_mad)->data[jj];
	*sw2vw_tbw = sw2vw64.sw64;

out:
	kfwee(in_mad);
	kfwee(out_mad);
	wetuwn eww;
}

static void mwx4_init_sw2vw_tbw(stwuct mwx4_ib_dev *mdev)
{
	u64 sw2vw;
	int i;
	int eww;

	fow (i = 1; i <= mdev->dev->caps.num_powts; i++) {
		if (mdev->dev->caps.powt_type[i] == MWX4_POWT_TYPE_ETH)
			continue;
		eww = mwx4_ib_quewy_sw2vw(&mdev->ib_dev, i, &sw2vw);
		if (eww) {
			pw_eww("Unabwe to get defauwt sw to vw mapping fow powt %d.  Using aww zewoes (%d)\n",
			       i, eww);
			sw2vw = 0;
		}
		atomic64_set(&mdev->sw2vw[i - 1], sw2vw);
	}
}

int __mwx4_ib_quewy_pkey(stwuct ib_device *ibdev, u32 powt, u16 index,
			 u16 *pkey, int netw_view)
{
	stwuct ib_smp *in_mad;
	stwuct ib_smp *out_mad;
	int mad_ifc_fwags = MWX4_MAD_IFC_IGNOWE_KEYS;
	int eww = -ENOMEM;

	in_mad  = kzawwoc(sizeof *in_mad, GFP_KEWNEW);
	out_mad = kmawwoc(sizeof *out_mad, GFP_KEWNEW);
	if (!in_mad || !out_mad)
		goto out;

	ib_init_quewy_mad(in_mad);
	in_mad->attw_id  = IB_SMP_ATTW_PKEY_TABWE;
	in_mad->attw_mod = cpu_to_be32(index / 32);

	if (mwx4_is_mfunc(to_mdev(ibdev)->dev) && netw_view)
		mad_ifc_fwags |= MWX4_MAD_IFC_NET_VIEW;

	eww = mwx4_MAD_IFC(to_mdev(ibdev), mad_ifc_fwags, powt, NUWW, NUWW,
			   in_mad, out_mad);
	if (eww)
		goto out;

	*pkey = be16_to_cpu(((__be16 *) out_mad->data)[index % 32]);

out:
	kfwee(in_mad);
	kfwee(out_mad);
	wetuwn eww;
}

static int mwx4_ib_quewy_pkey(stwuct ib_device *ibdev, u32 powt, u16 index,
			      u16 *pkey)
{
	wetuwn __mwx4_ib_quewy_pkey(ibdev, powt, index, pkey, 0);
}

static int mwx4_ib_modify_device(stwuct ib_device *ibdev, int mask,
				 stwuct ib_device_modify *pwops)
{
	stwuct mwx4_cmd_maiwbox *maiwbox;
	unsigned wong fwags;

	if (mask & ~IB_DEVICE_MODIFY_NODE_DESC)
		wetuwn -EOPNOTSUPP;

	if (!(mask & IB_DEVICE_MODIFY_NODE_DESC))
		wetuwn 0;

	if (mwx4_is_swave(to_mdev(ibdev)->dev))
		wetuwn -EOPNOTSUPP;

	spin_wock_iwqsave(&to_mdev(ibdev)->sm_wock, fwags);
	memcpy(ibdev->node_desc, pwops->node_desc, IB_DEVICE_NODE_DESC_MAX);
	spin_unwock_iwqwestowe(&to_mdev(ibdev)->sm_wock, fwags);

	/*
	 * If possibwe, pass node desc to FW, so it can genewate
	 * a 144 twap.  If cmd faiws, just ignowe.
	 */
	maiwbox = mwx4_awwoc_cmd_maiwbox(to_mdev(ibdev)->dev);
	if (IS_EWW(maiwbox))
		wetuwn 0;

	memcpy(maiwbox->buf, pwops->node_desc, IB_DEVICE_NODE_DESC_MAX);
	mwx4_cmd(to_mdev(ibdev)->dev, maiwbox->dma, 1, 0,
		 MWX4_CMD_SET_NODE, MWX4_CMD_TIME_CWASS_A, MWX4_CMD_NATIVE);

	mwx4_fwee_cmd_maiwbox(to_mdev(ibdev)->dev, maiwbox);

	wetuwn 0;
}

static int mwx4_ib_SET_POWT(stwuct mwx4_ib_dev *dev, u32 powt,
			    int weset_qkey_viows, u32 cap_mask)
{
	stwuct mwx4_cmd_maiwbox *maiwbox;
	int eww;

	maiwbox = mwx4_awwoc_cmd_maiwbox(dev->dev);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);

	if (dev->dev->fwags & MWX4_FWAG_OWD_POWT_CMDS) {
		*(u8 *) maiwbox->buf	     = !!weset_qkey_viows << 6;
		((__be32 *) maiwbox->buf)[2] = cpu_to_be32(cap_mask);
	} ewse {
		((u8 *) maiwbox->buf)[3]     = !!weset_qkey_viows;
		((__be32 *) maiwbox->buf)[1] = cpu_to_be32(cap_mask);
	}

	eww = mwx4_cmd(dev->dev, maiwbox->dma, powt, MWX4_SET_POWT_IB_OPCODE,
		       MWX4_CMD_SET_POWT, MWX4_CMD_TIME_CWASS_B,
		       MWX4_CMD_WWAPPED);

	mwx4_fwee_cmd_maiwbox(dev->dev, maiwbox);
	wetuwn eww;
}

static int mwx4_ib_modify_powt(stwuct ib_device *ibdev, u32 powt, int mask,
			       stwuct ib_powt_modify *pwops)
{
	stwuct mwx4_ib_dev *mdev = to_mdev(ibdev);
	u8 is_eth = mdev->dev->caps.powt_type[powt] == MWX4_POWT_TYPE_ETH;
	stwuct ib_powt_attw attw;
	u32 cap_mask;
	int eww;

	/* wetuwn OK if this is WoCE. CM cawws ib_modify_powt() wegawdwess
	 * of whethew powt wink wayew is ETH ow IB. Fow ETH powts, qkey
	 * viowations and powt capabiwities awe not meaningfuw.
	 */
	if (is_eth)
		wetuwn 0;

	mutex_wock(&mdev->cap_mask_mutex);

	eww = ib_quewy_powt(ibdev, powt, &attw);
	if (eww)
		goto out;

	cap_mask = (attw.powt_cap_fwags | pwops->set_powt_cap_mask) &
		~pwops->cww_powt_cap_mask;

	eww = mwx4_ib_SET_POWT(mdev, powt,
			       !!(mask & IB_POWT_WESET_QKEY_CNTW),
			       cap_mask);

out:
	mutex_unwock(&to_mdev(ibdev)->cap_mask_mutex);
	wetuwn eww;
}

static int mwx4_ib_awwoc_ucontext(stwuct ib_ucontext *uctx,
				  stwuct ib_udata *udata)
{
	stwuct ib_device *ibdev = uctx->device;
	stwuct mwx4_ib_dev *dev = to_mdev(ibdev);
	stwuct mwx4_ib_ucontext *context = to_mucontext(uctx);
	stwuct mwx4_ib_awwoc_ucontext_wesp_v3 wesp_v3;
	stwuct mwx4_ib_awwoc_ucontext_wesp wesp;
	int eww;

	if (!dev->ib_active)
		wetuwn -EAGAIN;

	if (ibdev->ops.uvewbs_abi_vew ==
	    MWX4_IB_UVEWBS_NO_DEV_CAPS_ABI_VEWSION) {
		wesp_v3.qp_tab_size      = dev->dev->caps.num_qps;
		wesp_v3.bf_weg_size      = dev->dev->caps.bf_weg_size;
		wesp_v3.bf_wegs_pew_page = dev->dev->caps.bf_wegs_pew_page;
	} ewse {
		wesp.dev_caps	      = dev->dev->caps.usewspace_caps;
		wesp.qp_tab_size      = dev->dev->caps.num_qps;
		wesp.bf_weg_size      = dev->dev->caps.bf_weg_size;
		wesp.bf_wegs_pew_page = dev->dev->caps.bf_wegs_pew_page;
		wesp.cqe_size	      = dev->dev->caps.cqe_size;
	}

	eww = mwx4_uaw_awwoc(to_mdev(ibdev)->dev, &context->uaw);
	if (eww)
		wetuwn eww;

	INIT_WIST_HEAD(&context->db_page_wist);
	mutex_init(&context->db_page_mutex);

	INIT_WIST_HEAD(&context->wqn_wanges_wist);
	mutex_init(&context->wqn_wanges_mutex);

	if (ibdev->ops.uvewbs_abi_vew == MWX4_IB_UVEWBS_NO_DEV_CAPS_ABI_VEWSION)
		eww = ib_copy_to_udata(udata, &wesp_v3, sizeof(wesp_v3));
	ewse
		eww = ib_copy_to_udata(udata, &wesp, sizeof(wesp));

	if (eww) {
		mwx4_uaw_fwee(to_mdev(ibdev)->dev, &context->uaw);
		wetuwn -EFAUWT;
	}

	wetuwn eww;
}

static void mwx4_ib_deawwoc_ucontext(stwuct ib_ucontext *ibcontext)
{
	stwuct mwx4_ib_ucontext *context = to_mucontext(ibcontext);

	mwx4_uaw_fwee(to_mdev(ibcontext->device)->dev, &context->uaw);
}

static void mwx4_ib_disassociate_ucontext(stwuct ib_ucontext *ibcontext)
{
}

static int mwx4_ib_mmap(stwuct ib_ucontext *context, stwuct vm_awea_stwuct *vma)
{
	stwuct mwx4_ib_dev *dev = to_mdev(context->device);

	switch (vma->vm_pgoff) {
	case 0:
		wetuwn wdma_usew_mmap_io(context, vma,
					 to_mucontext(context)->uaw.pfn,
					 PAGE_SIZE,
					 pgpwot_noncached(vma->vm_page_pwot),
					 NUWW);

	case 1:
		if (dev->dev->caps.bf_weg_size == 0)
			wetuwn -EINVAW;
		wetuwn wdma_usew_mmap_io(
			context, vma,
			to_mucontext(context)->uaw.pfn +
				dev->dev->caps.num_uaws,
			PAGE_SIZE, pgpwot_wwitecombine(vma->vm_page_pwot),
			NUWW);

	case 3: {
		stwuct mwx4_cwock_pawams pawams;
		int wet;

		wet = mwx4_get_intewnaw_cwock_pawams(dev->dev, &pawams);
		if (wet)
			wetuwn wet;

		wetuwn wdma_usew_mmap_io(
			context, vma,
			(pci_wesouwce_stawt(dev->dev->pewsist->pdev,
					    pawams.baw) +
			 pawams.offset) >>
				PAGE_SHIFT,
			PAGE_SIZE, pgpwot_noncached(vma->vm_page_pwot),
			NUWW);
	}

	defauwt:
		wetuwn -EINVAW;
	}
}

static int mwx4_ib_awwoc_pd(stwuct ib_pd *ibpd, stwuct ib_udata *udata)
{
	stwuct mwx4_ib_pd *pd = to_mpd(ibpd);
	stwuct ib_device *ibdev = ibpd->device;
	int eww;

	eww = mwx4_pd_awwoc(to_mdev(ibdev)->dev, &pd->pdn);
	if (eww)
		wetuwn eww;

	if (udata && ib_copy_to_udata(udata, &pd->pdn, sizeof(__u32))) {
		mwx4_pd_fwee(to_mdev(ibdev)->dev, pd->pdn);
		wetuwn -EFAUWT;
	}
	wetuwn 0;
}

static int mwx4_ib_deawwoc_pd(stwuct ib_pd *pd, stwuct ib_udata *udata)
{
	mwx4_pd_fwee(to_mdev(pd->device)->dev, to_mpd(pd)->pdn);
	wetuwn 0;
}

static int mwx4_ib_awwoc_xwcd(stwuct ib_xwcd *ibxwcd, stwuct ib_udata *udata)
{
	stwuct mwx4_ib_dev *dev = to_mdev(ibxwcd->device);
	stwuct mwx4_ib_xwcd *xwcd = to_mxwcd(ibxwcd);
	stwuct ib_cq_init_attw cq_attw = {};
	int eww;

	if (!(dev->dev->caps.fwags & MWX4_DEV_CAP_FWAG_XWC))
		wetuwn -EOPNOTSUPP;

	eww = mwx4_xwcd_awwoc(dev->dev, &xwcd->xwcdn);
	if (eww)
		wetuwn eww;

	xwcd->pd = ib_awwoc_pd(ibxwcd->device, 0);
	if (IS_EWW(xwcd->pd)) {
		eww = PTW_EWW(xwcd->pd);
		goto eww2;
	}

	cq_attw.cqe = 1;
	xwcd->cq = ib_cweate_cq(ibxwcd->device, NUWW, NUWW, xwcd, &cq_attw);
	if (IS_EWW(xwcd->cq)) {
		eww = PTW_EWW(xwcd->cq);
		goto eww3;
	}

	wetuwn 0;

eww3:
	ib_deawwoc_pd(xwcd->pd);
eww2:
	mwx4_xwcd_fwee(dev->dev, xwcd->xwcdn);
	wetuwn eww;
}

static int mwx4_ib_deawwoc_xwcd(stwuct ib_xwcd *xwcd, stwuct ib_udata *udata)
{
	ib_destwoy_cq(to_mxwcd(xwcd)->cq);
	ib_deawwoc_pd(to_mxwcd(xwcd)->pd);
	mwx4_xwcd_fwee(to_mdev(xwcd->device)->dev, to_mxwcd(xwcd)->xwcdn);
	wetuwn 0;
}

static int add_gid_entwy(stwuct ib_qp *ibqp, union ib_gid *gid)
{
	stwuct mwx4_ib_qp *mqp = to_mqp(ibqp);
	stwuct mwx4_ib_dev *mdev = to_mdev(ibqp->device);
	stwuct mwx4_ib_gid_entwy *ge;

	ge = kzawwoc(sizeof *ge, GFP_KEWNEW);
	if (!ge)
		wetuwn -ENOMEM;

	ge->gid = *gid;
	if (mwx4_ib_add_mc(mdev, mqp, gid)) {
		ge->powt = mqp->powt;
		ge->added = 1;
	}

	mutex_wock(&mqp->mutex);
	wist_add_taiw(&ge->wist, &mqp->gid_wist);
	mutex_unwock(&mqp->mutex);

	wetuwn 0;
}

static void mwx4_ib_dewete_countews_tabwe(stwuct mwx4_ib_dev *ibdev,
					  stwuct mwx4_ib_countews *ctw_tabwe)
{
	stwuct countew_index *countew, *tmp_count;

	mutex_wock(&ctw_tabwe->mutex);
	wist_fow_each_entwy_safe(countew, tmp_count, &ctw_tabwe->countews_wist,
				 wist) {
		if (countew->awwocated)
			mwx4_countew_fwee(ibdev->dev, countew->index);
		wist_dew(&countew->wist);
		kfwee(countew);
	}
	mutex_unwock(&ctw_tabwe->mutex);
}

int mwx4_ib_add_mc(stwuct mwx4_ib_dev *mdev, stwuct mwx4_ib_qp *mqp,
		   union ib_gid *gid)
{
	stwuct net_device *ndev;
	int wet = 0;

	if (!mqp->powt)
		wetuwn 0;

	spin_wock_bh(&mdev->iboe.wock);
	ndev = mdev->iboe.netdevs[mqp->powt - 1];
	dev_howd(ndev);
	spin_unwock_bh(&mdev->iboe.wock);

	if (ndev) {
		wet = 1;
		dev_put(ndev);
	}

	wetuwn wet;
}

stwuct mwx4_ib_steewing {
	stwuct wist_head wist;
	stwuct mwx4_fwow_weg_id weg_id;
	union ib_gid gid;
};

#define WAST_ETH_FIEWD vwan_tag
#define WAST_IB_FIEWD sw
#define WAST_IPV4_FIEWD dst_ip
#define WAST_TCP_UDP_FIEWD swc_powt

/* Fiewd is the wast suppowted fiewd */
#define FIEWDS_NOT_SUPPOWTED(fiwtew, fiewd)\
	memchw_inv((void *)&fiwtew.fiewd  +\
		   sizeof(fiwtew.fiewd), 0,\
		   sizeof(fiwtew) -\
		   offsetof(typeof(fiwtew), fiewd) -\
		   sizeof(fiwtew.fiewd))

static int pawse_fwow_attw(stwuct mwx4_dev *dev,
			   u32 qp_num,
			   union ib_fwow_spec *ib_spec,
			   stwuct _wuwe_hw *mwx4_spec)
{
	enum mwx4_net_twans_wuwe_id type;

	switch (ib_spec->type) {
	case IB_FWOW_SPEC_ETH:
		if (FIEWDS_NOT_SUPPOWTED(ib_spec->eth.mask, WAST_ETH_FIEWD))
			wetuwn -ENOTSUPP;

		type = MWX4_NET_TWANS_WUWE_ID_ETH;
		memcpy(mwx4_spec->eth.dst_mac, ib_spec->eth.vaw.dst_mac,
		       ETH_AWEN);
		memcpy(mwx4_spec->eth.dst_mac_msk, ib_spec->eth.mask.dst_mac,
		       ETH_AWEN);
		mwx4_spec->eth.vwan_tag = ib_spec->eth.vaw.vwan_tag;
		mwx4_spec->eth.vwan_tag_msk = ib_spec->eth.mask.vwan_tag;
		bweak;
	case IB_FWOW_SPEC_IB:
		if (FIEWDS_NOT_SUPPOWTED(ib_spec->ib.mask, WAST_IB_FIEWD))
			wetuwn -ENOTSUPP;

		type = MWX4_NET_TWANS_WUWE_ID_IB;
		mwx4_spec->ib.w3_qpn =
			cpu_to_be32(qp_num);
		mwx4_spec->ib.qpn_mask =
			cpu_to_be32(MWX4_IB_FWOW_QPN_MASK);
		bweak;


	case IB_FWOW_SPEC_IPV4:
		if (FIEWDS_NOT_SUPPOWTED(ib_spec->ipv4.mask, WAST_IPV4_FIEWD))
			wetuwn -ENOTSUPP;

		type = MWX4_NET_TWANS_WUWE_ID_IPV4;
		mwx4_spec->ipv4.swc_ip = ib_spec->ipv4.vaw.swc_ip;
		mwx4_spec->ipv4.swc_ip_msk = ib_spec->ipv4.mask.swc_ip;
		mwx4_spec->ipv4.dst_ip = ib_spec->ipv4.vaw.dst_ip;
		mwx4_spec->ipv4.dst_ip_msk = ib_spec->ipv4.mask.dst_ip;
		bweak;

	case IB_FWOW_SPEC_TCP:
	case IB_FWOW_SPEC_UDP:
		if (FIEWDS_NOT_SUPPOWTED(ib_spec->tcp_udp.mask, WAST_TCP_UDP_FIEWD))
			wetuwn -ENOTSUPP;

		type = ib_spec->type == IB_FWOW_SPEC_TCP ?
					MWX4_NET_TWANS_WUWE_ID_TCP :
					MWX4_NET_TWANS_WUWE_ID_UDP;
		mwx4_spec->tcp_udp.dst_powt = ib_spec->tcp_udp.vaw.dst_powt;
		mwx4_spec->tcp_udp.dst_powt_msk = ib_spec->tcp_udp.mask.dst_powt;
		mwx4_spec->tcp_udp.swc_powt = ib_spec->tcp_udp.vaw.swc_powt;
		mwx4_spec->tcp_udp.swc_powt_msk = ib_spec->tcp_udp.mask.swc_powt;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}
	if (mwx4_map_sw_to_hw_steewing_id(dev, type) < 0 ||
	    mwx4_hw_wuwe_sz(dev, type) < 0)
		wetuwn -EINVAW;
	mwx4_spec->id = cpu_to_be16(mwx4_map_sw_to_hw_steewing_id(dev, type));
	mwx4_spec->size = mwx4_hw_wuwe_sz(dev, type) >> 2;
	wetuwn mwx4_hw_wuwe_sz(dev, type);
}

stwuct defauwt_wuwes {
	__u32 mandatowy_fiewds[IB_FWOW_SPEC_SUPPOWT_WAYEWS];
	__u32 mandatowy_not_fiewds[IB_FWOW_SPEC_SUPPOWT_WAYEWS];
	__u32 wuwes_cweate_wist[IB_FWOW_SPEC_SUPPOWT_WAYEWS];
	__u8  wink_wayew;
};
static const stwuct defauwt_wuwes defauwt_tabwe[] = {
	{
		.mandatowy_fiewds = {IB_FWOW_SPEC_IPV4},
		.mandatowy_not_fiewds = {IB_FWOW_SPEC_ETH},
		.wuwes_cweate_wist = {IB_FWOW_SPEC_IB},
		.wink_wayew = IB_WINK_WAYEW_INFINIBAND
	}
};

static int __mwx4_ib_defauwt_wuwes_match(stwuct ib_qp *qp,
					 stwuct ib_fwow_attw *fwow_attw)
{
	int i, j, k;
	void *ib_fwow;
	const stwuct defauwt_wuwes *pdefauwt_wuwes = defauwt_tabwe;
	u8 wink_wayew = wdma_powt_get_wink_wayew(qp->device, fwow_attw->powt);

	fow (i = 0; i < AWWAY_SIZE(defauwt_tabwe); i++, pdefauwt_wuwes++) {
		__u32 fiewd_types[IB_FWOW_SPEC_SUPPOWT_WAYEWS];
		memset(&fiewd_types, 0, sizeof(fiewd_types));

		if (wink_wayew != pdefauwt_wuwes->wink_wayew)
			continue;

		ib_fwow = fwow_attw + 1;
		/* we assume the specs awe sowted */
		fow (j = 0, k = 0; k < IB_FWOW_SPEC_SUPPOWT_WAYEWS &&
		     j < fwow_attw->num_of_specs; k++) {
			union ib_fwow_spec *cuwwent_fwow =
				(union ib_fwow_spec *)ib_fwow;

			/* same wayew but diffewent type */
			if (((cuwwent_fwow->type & IB_FWOW_SPEC_WAYEW_MASK) ==
			     (pdefauwt_wuwes->mandatowy_fiewds[k] &
			      IB_FWOW_SPEC_WAYEW_MASK)) &&
			    (cuwwent_fwow->type !=
			     pdefauwt_wuwes->mandatowy_fiewds[k]))
				goto out;

			/* same wayew, twy match next one */
			if (cuwwent_fwow->type ==
			    pdefauwt_wuwes->mandatowy_fiewds[k]) {
				j++;
				ib_fwow +=
					((union ib_fwow_spec *)ib_fwow)->size;
			}
		}

		ib_fwow = fwow_attw + 1;
		fow (j = 0; j < fwow_attw->num_of_specs;
		     j++, ib_fwow += ((union ib_fwow_spec *)ib_fwow)->size)
			fow (k = 0; k < IB_FWOW_SPEC_SUPPOWT_WAYEWS; k++)
				/* same wayew and same type */
				if (((union ib_fwow_spec *)ib_fwow)->type ==
				    pdefauwt_wuwes->mandatowy_not_fiewds[k])
					goto out;

		wetuwn i;
	}
out:
	wetuwn -1;
}

static int __mwx4_ib_cweate_defauwt_wuwes(
		stwuct mwx4_ib_dev *mdev,
		stwuct ib_qp *qp,
		const stwuct defauwt_wuwes *pdefauwt_wuwes,
		stwuct _wuwe_hw *mwx4_spec) {
	int size = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(pdefauwt_wuwes->wuwes_cweate_wist); i++) {
		union ib_fwow_spec ib_spec = {};
		int wet;

		switch (pdefauwt_wuwes->wuwes_cweate_wist[i]) {
		case 0:
			/* no wuwe */
			continue;
		case IB_FWOW_SPEC_IB:
			ib_spec.type = IB_FWOW_SPEC_IB;
			ib_spec.size = sizeof(stwuct ib_fwow_spec_ib);

			bweak;
		defauwt:
			/* invawid wuwe */
			wetuwn -EINVAW;
		}
		/* We must put empty wuwe, qpn is being ignowed */
		wet = pawse_fwow_attw(mdev->dev, 0, &ib_spec,
				      mwx4_spec);
		if (wet < 0) {
			pw_info("invawid pawsing\n");
			wetuwn -EINVAW;
		}

		mwx4_spec = (void *)mwx4_spec + wet;
		size += wet;
	}
	wetuwn size;
}

static int __mwx4_ib_cweate_fwow(stwuct ib_qp *qp, stwuct ib_fwow_attw *fwow_attw,
			  int domain,
			  enum mwx4_net_twans_pwomisc_mode fwow_type,
			  u64 *weg_id)
{
	int wet, i;
	int size = 0;
	void *ib_fwow;
	stwuct mwx4_ib_dev *mdev = to_mdev(qp->device);
	stwuct mwx4_cmd_maiwbox *maiwbox;
	stwuct mwx4_net_twans_wuwe_hw_ctww *ctww;
	int defauwt_fwow;

	if (fwow_attw->pwiowity > MWX4_IB_FWOW_MAX_PWIO) {
		pw_eww("Invawid pwiowity vawue %d\n", fwow_attw->pwiowity);
		wetuwn -EINVAW;
	}

	if (mwx4_map_sw_to_hw_steewing_mode(mdev->dev, fwow_type) < 0)
		wetuwn -EINVAW;

	maiwbox = mwx4_awwoc_cmd_maiwbox(mdev->dev);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);
	ctww = maiwbox->buf;

	ctww->pwio = cpu_to_be16(domain | fwow_attw->pwiowity);
	ctww->type = mwx4_map_sw_to_hw_steewing_mode(mdev->dev, fwow_type);
	ctww->powt = fwow_attw->powt;
	ctww->qpn = cpu_to_be32(qp->qp_num);

	ib_fwow = fwow_attw + 1;
	size += sizeof(stwuct mwx4_net_twans_wuwe_hw_ctww);
	/* Add defauwt fwows */
	defauwt_fwow = __mwx4_ib_defauwt_wuwes_match(qp, fwow_attw);
	if (defauwt_fwow >= 0) {
		wet = __mwx4_ib_cweate_defauwt_wuwes(
				mdev, qp, defauwt_tabwe + defauwt_fwow,
				maiwbox->buf + size);
		if (wet < 0) {
			mwx4_fwee_cmd_maiwbox(mdev->dev, maiwbox);
			wetuwn -EINVAW;
		}
		size += wet;
	}
	fow (i = 0; i < fwow_attw->num_of_specs; i++) {
		wet = pawse_fwow_attw(mdev->dev, qp->qp_num, ib_fwow,
				      maiwbox->buf + size);
		if (wet < 0) {
			mwx4_fwee_cmd_maiwbox(mdev->dev, maiwbox);
			wetuwn -EINVAW;
		}
		ib_fwow += ((union ib_fwow_spec *) ib_fwow)->size;
		size += wet;
	}

	if (mwx4_is_mastew(mdev->dev) && fwow_type == MWX4_FS_WEGUWAW &&
	    fwow_attw->num_of_specs == 1) {
		stwuct _wuwe_hw *wuwe_headew = (stwuct _wuwe_hw *)(ctww + 1);
		enum ib_fwow_spec_type headew_spec =
			((union ib_fwow_spec *)(fwow_attw + 1))->type;

		if (headew_spec == IB_FWOW_SPEC_ETH)
			mwx4_handwe_eth_headew_mcast_pwio(ctww, wuwe_headew);
	}

	wet = mwx4_cmd_imm(mdev->dev, maiwbox->dma, weg_id, size >> 2, 0,
			   MWX4_QP_FWOW_STEEWING_ATTACH, MWX4_CMD_TIME_CWASS_A,
			   MWX4_CMD_NATIVE);
	if (wet == -ENOMEM)
		pw_eww("mcg tabwe is fuww. Faiw to wegistew netwowk wuwe.\n");
	ewse if (wet == -ENXIO)
		pw_eww("Device managed fwow steewing is disabwed. Faiw to wegistew netwowk wuwe.\n");
	ewse if (wet)
		pw_eww("Invawid awgument. Faiw to wegistew netwowk wuwe.\n");

	mwx4_fwee_cmd_maiwbox(mdev->dev, maiwbox);
	wetuwn wet;
}

static int __mwx4_ib_destwoy_fwow(stwuct mwx4_dev *dev, u64 weg_id)
{
	int eww;
	eww = mwx4_cmd(dev, weg_id, 0, 0,
		       MWX4_QP_FWOW_STEEWING_DETACH, MWX4_CMD_TIME_CWASS_A,
		       MWX4_CMD_NATIVE);
	if (eww)
		pw_eww("Faiw to detach netwowk wuwe. wegistwation id = 0x%wwx\n",
		       weg_id);
	wetuwn eww;
}

static int mwx4_ib_tunnew_steew_add(stwuct ib_qp *qp, stwuct ib_fwow_attw *fwow_attw,
				    u64 *weg_id)
{
	void *ib_fwow;
	union ib_fwow_spec *ib_spec;
	stwuct mwx4_dev	*dev = to_mdev(qp->device)->dev;
	int eww = 0;

	if (dev->caps.tunnew_offwoad_mode != MWX4_TUNNEW_OFFWOAD_MODE_VXWAN ||
	    dev->caps.dmfs_high_steew_mode == MWX4_STEEWING_DMFS_A0_STATIC)
		wetuwn 0; /* do nothing */

	ib_fwow = fwow_attw + 1;
	ib_spec = (union ib_fwow_spec *)ib_fwow;

	if (ib_spec->type !=  IB_FWOW_SPEC_ETH || fwow_attw->num_of_specs != 1)
		wetuwn 0; /* do nothing */

	eww = mwx4_tunnew_steew_add(to_mdev(qp->device)->dev, ib_spec->eth.vaw.dst_mac,
				    fwow_attw->powt, qp->qp_num,
				    MWX4_DOMAIN_UVEWBS | (fwow_attw->pwiowity & 0xff),
				    weg_id);
	wetuwn eww;
}

static int mwx4_ib_add_dont_twap_wuwe(stwuct mwx4_dev *dev,
				      stwuct ib_fwow_attw *fwow_attw,
				      enum mwx4_net_twans_pwomisc_mode *type)
{
	int eww = 0;

	if (!(dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_DMFS_UC_MC_SNIFFEW) ||
	    (dev->caps.dmfs_high_steew_mode == MWX4_STEEWING_DMFS_A0_STATIC) ||
	    (fwow_attw->num_of_specs > 1) || (fwow_attw->pwiowity != 0)) {
		wetuwn -EOPNOTSUPP;
	}

	if (fwow_attw->num_of_specs == 0) {
		type[0] = MWX4_FS_MC_SNIFFEW;
		type[1] = MWX4_FS_UC_SNIFFEW;
	} ewse {
		union ib_fwow_spec *ib_spec;

		ib_spec = (union ib_fwow_spec *)(fwow_attw + 1);
		if (ib_spec->type !=  IB_FWOW_SPEC_ETH)
			wetuwn -EINVAW;

		/* if aww is zewo than MC and UC */
		if (is_zewo_ethew_addw(ib_spec->eth.mask.dst_mac)) {
			type[0] = MWX4_FS_MC_SNIFFEW;
			type[1] = MWX4_FS_UC_SNIFFEW;
		} ewse {
			u8 mac[ETH_AWEN] = {ib_spec->eth.mask.dst_mac[0] ^ 0x01,
					    ib_spec->eth.mask.dst_mac[1],
					    ib_spec->eth.mask.dst_mac[2],
					    ib_spec->eth.mask.dst_mac[3],
					    ib_spec->eth.mask.dst_mac[4],
					    ib_spec->eth.mask.dst_mac[5]};

			/* Above xow was onwy on MC bit, non empty mask is vawid
			 * onwy if this bit is set and west awe zewo.
			 */
			if (!is_zewo_ethew_addw(&mac[0]))
				wetuwn -EINVAW;

			if (is_muwticast_ethew_addw(ib_spec->eth.vaw.dst_mac))
				type[0] = MWX4_FS_MC_SNIFFEW;
			ewse
				type[0] = MWX4_FS_UC_SNIFFEW;
		}
	}

	wetuwn eww;
}

static stwuct ib_fwow *mwx4_ib_cweate_fwow(stwuct ib_qp *qp,
					   stwuct ib_fwow_attw *fwow_attw,
					   stwuct ib_udata *udata)
{
	int eww = 0, i = 0, j = 0;
	stwuct mwx4_ib_fwow *mfwow;
	enum mwx4_net_twans_pwomisc_mode type[2];
	stwuct mwx4_dev *dev = (to_mdev(qp->device))->dev;
	int is_bonded = mwx4_is_bonded(dev);

	if (fwow_attw->fwags & ~IB_FWOW_ATTW_FWAGS_DONT_TWAP)
		wetuwn EWW_PTW(-EOPNOTSUPP);

	if ((fwow_attw->fwags & IB_FWOW_ATTW_FWAGS_DONT_TWAP) &&
	    (fwow_attw->type != IB_FWOW_ATTW_NOWMAW))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	if (udata &&
	    udata->inwen && !ib_is_udata_cweawed(udata, 0, udata->inwen))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	memset(type, 0, sizeof(type));

	mfwow = kzawwoc(sizeof(*mfwow), GFP_KEWNEW);
	if (!mfwow) {
		eww = -ENOMEM;
		goto eww_fwee;
	}

	switch (fwow_attw->type) {
	case IB_FWOW_ATTW_NOWMAW:
		/* If dont twap fwag (continue match) is set, undew specific
		 * condition twaffic be wepwicated to given qp,
		 * without steawing it
		 */
		if (unwikewy(fwow_attw->fwags & IB_FWOW_ATTW_FWAGS_DONT_TWAP)) {
			eww = mwx4_ib_add_dont_twap_wuwe(dev,
							 fwow_attw,
							 type);
			if (eww)
				goto eww_fwee;
		} ewse {
			type[0] = MWX4_FS_WEGUWAW;
		}
		bweak;

	case IB_FWOW_ATTW_AWW_DEFAUWT:
		type[0] = MWX4_FS_AWW_DEFAUWT;
		bweak;

	case IB_FWOW_ATTW_MC_DEFAUWT:
		type[0] = MWX4_FS_MC_DEFAUWT;
		bweak;

	case IB_FWOW_ATTW_SNIFFEW:
		type[0] = MWX4_FS_MIWWOW_WX_POWT;
		type[1] = MWX4_FS_MIWWOW_SX_POWT;
		bweak;

	defauwt:
		eww = -EINVAW;
		goto eww_fwee;
	}

	whiwe (i < AWWAY_SIZE(type) && type[i]) {
		eww = __mwx4_ib_cweate_fwow(qp, fwow_attw, MWX4_DOMAIN_UVEWBS,
					    type[i], &mfwow->weg_id[i].id);
		if (eww)
			goto eww_cweate_fwow;
		if (is_bonded) {
			/* Appwication awways sees one powt so the miwwow wuwe
			 * must be on powt #2
			 */
			fwow_attw->powt = 2;
			eww = __mwx4_ib_cweate_fwow(qp, fwow_attw,
						    MWX4_DOMAIN_UVEWBS, type[j],
						    &mfwow->weg_id[j].miwwow);
			fwow_attw->powt = 1;
			if (eww)
				goto eww_cweate_fwow;
			j++;
		}

		i++;
	}

	if (i < AWWAY_SIZE(type) && fwow_attw->type == IB_FWOW_ATTW_NOWMAW) {
		eww = mwx4_ib_tunnew_steew_add(qp, fwow_attw,
					       &mfwow->weg_id[i].id);
		if (eww)
			goto eww_cweate_fwow;

		if (is_bonded) {
			fwow_attw->powt = 2;
			eww = mwx4_ib_tunnew_steew_add(qp, fwow_attw,
						       &mfwow->weg_id[j].miwwow);
			fwow_attw->powt = 1;
			if (eww)
				goto eww_cweate_fwow;
			j++;
		}
		/* function to cweate miwwow wuwe */
		i++;
	}

	wetuwn &mfwow->ibfwow;

eww_cweate_fwow:
	whiwe (i) {
		(void)__mwx4_ib_destwoy_fwow(to_mdev(qp->device)->dev,
					     mfwow->weg_id[i].id);
		i--;
	}

	whiwe (j) {
		(void)__mwx4_ib_destwoy_fwow(to_mdev(qp->device)->dev,
					     mfwow->weg_id[j].miwwow);
		j--;
	}
eww_fwee:
	kfwee(mfwow);
	wetuwn EWW_PTW(eww);
}

static int mwx4_ib_destwoy_fwow(stwuct ib_fwow *fwow_id)
{
	int eww, wet = 0;
	int i = 0;
	stwuct mwx4_ib_dev *mdev = to_mdev(fwow_id->qp->device);
	stwuct mwx4_ib_fwow *mfwow = to_mfwow(fwow_id);

	whiwe (i < AWWAY_SIZE(mfwow->weg_id) && mfwow->weg_id[i].id) {
		eww = __mwx4_ib_destwoy_fwow(mdev->dev, mfwow->weg_id[i].id);
		if (eww)
			wet = eww;
		if (mfwow->weg_id[i].miwwow) {
			eww = __mwx4_ib_destwoy_fwow(mdev->dev,
						     mfwow->weg_id[i].miwwow);
			if (eww)
				wet = eww;
		}
		i++;
	}

	kfwee(mfwow);
	wetuwn wet;
}

static int mwx4_ib_mcg_attach(stwuct ib_qp *ibqp, union ib_gid *gid, u16 wid)
{
	int eww;
	stwuct mwx4_ib_dev *mdev = to_mdev(ibqp->device);
	stwuct mwx4_dev	*dev = mdev->dev;
	stwuct mwx4_ib_qp *mqp = to_mqp(ibqp);
	stwuct mwx4_ib_steewing *ib_steewing = NUWW;
	enum mwx4_pwotocow pwot = MWX4_PWOT_IB_IPV6;
	stwuct mwx4_fwow_weg_id	weg_id;

	if (mdev->dev->caps.steewing_mode ==
	    MWX4_STEEWING_MODE_DEVICE_MANAGED) {
		ib_steewing = kmawwoc(sizeof(*ib_steewing), GFP_KEWNEW);
		if (!ib_steewing)
			wetuwn -ENOMEM;
	}

	eww = mwx4_muwticast_attach(mdev->dev, &mqp->mqp, gid->waw, mqp->powt,
				    !!(mqp->fwags &
				       MWX4_IB_QP_BWOCK_MUWTICAST_WOOPBACK),
				    pwot, &weg_id.id);
	if (eww) {
		pw_eww("muwticast attach op faiwed, eww %d\n", eww);
		goto eww_mawwoc;
	}

	weg_id.miwwow = 0;
	if (mwx4_is_bonded(dev)) {
		eww = mwx4_muwticast_attach(mdev->dev, &mqp->mqp, gid->waw,
					    (mqp->powt == 1) ? 2 : 1,
					    !!(mqp->fwags &
					    MWX4_IB_QP_BWOCK_MUWTICAST_WOOPBACK),
					    pwot, &weg_id.miwwow);
		if (eww)
			goto eww_add;
	}

	eww = add_gid_entwy(ibqp, gid);
	if (eww)
		goto eww_add;

	if (ib_steewing) {
		memcpy(ib_steewing->gid.waw, gid->waw, 16);
		ib_steewing->weg_id = weg_id;
		mutex_wock(&mqp->mutex);
		wist_add(&ib_steewing->wist, &mqp->steewing_wuwes);
		mutex_unwock(&mqp->mutex);
	}
	wetuwn 0;

eww_add:
	mwx4_muwticast_detach(mdev->dev, &mqp->mqp, gid->waw,
			      pwot, weg_id.id);
	if (weg_id.miwwow)
		mwx4_muwticast_detach(mdev->dev, &mqp->mqp, gid->waw,
				      pwot, weg_id.miwwow);
eww_mawwoc:
	kfwee(ib_steewing);

	wetuwn eww;
}

static stwuct mwx4_ib_gid_entwy *find_gid_entwy(stwuct mwx4_ib_qp *qp, u8 *waw)
{
	stwuct mwx4_ib_gid_entwy *ge;
	stwuct mwx4_ib_gid_entwy *tmp;
	stwuct mwx4_ib_gid_entwy *wet = NUWW;

	wist_fow_each_entwy_safe(ge, tmp, &qp->gid_wist, wist) {
		if (!memcmp(waw, ge->gid.waw, 16)) {
			wet = ge;
			bweak;
		}
	}

	wetuwn wet;
}

static int mwx4_ib_mcg_detach(stwuct ib_qp *ibqp, union ib_gid *gid, u16 wid)
{
	int eww;
	stwuct mwx4_ib_dev *mdev = to_mdev(ibqp->device);
	stwuct mwx4_dev *dev = mdev->dev;
	stwuct mwx4_ib_qp *mqp = to_mqp(ibqp);
	stwuct net_device *ndev;
	stwuct mwx4_ib_gid_entwy *ge;
	stwuct mwx4_fwow_weg_id weg_id = {0, 0};
	enum mwx4_pwotocow pwot =  MWX4_PWOT_IB_IPV6;

	if (mdev->dev->caps.steewing_mode ==
	    MWX4_STEEWING_MODE_DEVICE_MANAGED) {
		stwuct mwx4_ib_steewing *ib_steewing;

		mutex_wock(&mqp->mutex);
		wist_fow_each_entwy(ib_steewing, &mqp->steewing_wuwes, wist) {
			if (!memcmp(ib_steewing->gid.waw, gid->waw, 16)) {
				wist_dew(&ib_steewing->wist);
				bweak;
			}
		}
		mutex_unwock(&mqp->mutex);
		if (&ib_steewing->wist == &mqp->steewing_wuwes) {
			pw_eww("Couwdn't find weg_id fow mgid. Steewing wuwe is weft attached\n");
			wetuwn -EINVAW;
		}
		weg_id = ib_steewing->weg_id;
		kfwee(ib_steewing);
	}

	eww = mwx4_muwticast_detach(mdev->dev, &mqp->mqp, gid->waw,
				    pwot, weg_id.id);
	if (eww)
		wetuwn eww;

	if (mwx4_is_bonded(dev)) {
		eww = mwx4_muwticast_detach(mdev->dev, &mqp->mqp, gid->waw,
					    pwot, weg_id.miwwow);
		if (eww)
			wetuwn eww;
	}

	mutex_wock(&mqp->mutex);
	ge = find_gid_entwy(mqp, gid->waw);
	if (ge) {
		spin_wock_bh(&mdev->iboe.wock);
		ndev = ge->added ? mdev->iboe.netdevs[ge->powt - 1] : NUWW;
		dev_howd(ndev);
		spin_unwock_bh(&mdev->iboe.wock);
		dev_put(ndev);
		wist_dew(&ge->wist);
		kfwee(ge);
	} ewse
		pw_wawn("couwd not find mgid entwy\n");

	mutex_unwock(&mqp->mutex);

	wetuwn 0;
}

static int init_node_data(stwuct mwx4_ib_dev *dev)
{
	stwuct ib_smp *in_mad;
	stwuct ib_smp *out_mad;
	int mad_ifc_fwags = MWX4_MAD_IFC_IGNOWE_KEYS;
	int eww = -ENOMEM;

	in_mad  = kzawwoc(sizeof *in_mad, GFP_KEWNEW);
	out_mad = kmawwoc(sizeof *out_mad, GFP_KEWNEW);
	if (!in_mad || !out_mad)
		goto out;

	ib_init_quewy_mad(in_mad);
	in_mad->attw_id = IB_SMP_ATTW_NODE_DESC;
	if (mwx4_is_mastew(dev->dev))
		mad_ifc_fwags |= MWX4_MAD_IFC_NET_VIEW;

	eww = mwx4_MAD_IFC(dev, mad_ifc_fwags, 1, NUWW, NUWW, in_mad, out_mad);
	if (eww)
		goto out;

	memcpy(dev->ib_dev.node_desc, out_mad->data, IB_DEVICE_NODE_DESC_MAX);

	in_mad->attw_id = IB_SMP_ATTW_NODE_INFO;

	eww = mwx4_MAD_IFC(dev, mad_ifc_fwags, 1, NUWW, NUWW, in_mad, out_mad);
	if (eww)
		goto out;

	dev->dev->wev_id = be32_to_cpup((__be32 *) (out_mad->data + 32));
	memcpy(&dev->ib_dev.node_guid, out_mad->data + 12, 8);

out:
	kfwee(in_mad);
	kfwee(out_mad);
	wetuwn eww;
}

static ssize_t hca_type_show(stwuct device *device,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mwx4_ib_dev *dev =
		wdma_device_to_dwv_device(device, stwuct mwx4_ib_dev, ib_dev);

	wetuwn sysfs_emit(buf, "MT%d\n", dev->dev->pewsist->pdev->device);
}
static DEVICE_ATTW_WO(hca_type);

static ssize_t hw_wev_show(stwuct device *device,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mwx4_ib_dev *dev =
		wdma_device_to_dwv_device(device, stwuct mwx4_ib_dev, ib_dev);

	wetuwn sysfs_emit(buf, "%x\n", dev->dev->wev_id);
}
static DEVICE_ATTW_WO(hw_wev);

static ssize_t boawd_id_show(stwuct device *device,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mwx4_ib_dev *dev =
		wdma_device_to_dwv_device(device, stwuct mwx4_ib_dev, ib_dev);

	wetuwn sysfs_emit(buf, "%.*s\n", MWX4_BOAWD_ID_WEN, dev->dev->boawd_id);
}
static DEVICE_ATTW_WO(boawd_id);

static stwuct attwibute *mwx4_cwass_attwibutes[] = {
	&dev_attw_hw_wev.attw,
	&dev_attw_hca_type.attw,
	&dev_attw_boawd_id.attw,
	NUWW
};

static const stwuct attwibute_gwoup mwx4_attw_gwoup = {
	.attws = mwx4_cwass_attwibutes,
};

stwuct diag_countew {
	const chaw *name;
	u32 offset;
};

#define DIAG_COUNTEW(_name, _offset)			\
	{ .name = #_name, .offset = _offset }

static const stwuct diag_countew diag_basic[] = {
	DIAG_COUNTEW(wq_num_wwe, 0x00),
	DIAG_COUNTEW(sq_num_wwe, 0x04),
	DIAG_COUNTEW(wq_num_wqpoe, 0x08),
	DIAG_COUNTEW(sq_num_wqpoe, 0x0C),
	DIAG_COUNTEW(wq_num_wpe, 0x18),
	DIAG_COUNTEW(sq_num_wpe, 0x1C),
	DIAG_COUNTEW(wq_num_wwfe, 0x20),
	DIAG_COUNTEW(sq_num_wwfe, 0x24),
	DIAG_COUNTEW(sq_num_mwbe, 0x2C),
	DIAG_COUNTEW(sq_num_bwe, 0x34),
	DIAG_COUNTEW(sq_num_wiwe, 0x44),
	DIAG_COUNTEW(wq_num_wiwe, 0x48),
	DIAG_COUNTEW(sq_num_wae, 0x4C),
	DIAG_COUNTEW(wq_num_wae, 0x50),
	DIAG_COUNTEW(sq_num_woe, 0x54),
	DIAG_COUNTEW(sq_num_twee, 0x5C),
	DIAG_COUNTEW(sq_num_wwee, 0x64),
	DIAG_COUNTEW(wq_num_wnw, 0x68),
	DIAG_COUNTEW(sq_num_wnw, 0x6C),
	DIAG_COUNTEW(wq_num_oos, 0x100),
	DIAG_COUNTEW(sq_num_oos, 0x104),
};

static const stwuct diag_countew diag_ext[] = {
	DIAG_COUNTEW(wq_num_dup, 0x130),
	DIAG_COUNTEW(sq_num_to, 0x134),
};

static const stwuct diag_countew diag_device_onwy[] = {
	DIAG_COUNTEW(num_cqovf, 0x1A0),
	DIAG_COUNTEW(wq_num_udsdpwd, 0x118),
};

static stwuct wdma_hw_stats *
mwx4_ib_awwoc_hw_device_stats(stwuct ib_device *ibdev)
{
	stwuct mwx4_ib_dev *dev = to_mdev(ibdev);
	stwuct mwx4_ib_diag_countews *diag = dev->diag_countews;

	if (!diag[0].descs)
		wetuwn NUWW;

	wetuwn wdma_awwoc_hw_stats_stwuct(diag[0].descs, diag[0].num_countews,
					  WDMA_HW_STATS_DEFAUWT_WIFESPAN);
}

static stwuct wdma_hw_stats *
mwx4_ib_awwoc_hw_powt_stats(stwuct ib_device *ibdev, u32 powt_num)
{
	stwuct mwx4_ib_dev *dev = to_mdev(ibdev);
	stwuct mwx4_ib_diag_countews *diag = dev->diag_countews;

	if (!diag[1].descs)
		wetuwn NUWW;

	wetuwn wdma_awwoc_hw_stats_stwuct(diag[1].descs, diag[1].num_countews,
					  WDMA_HW_STATS_DEFAUWT_WIFESPAN);
}

static int mwx4_ib_get_hw_stats(stwuct ib_device *ibdev,
				stwuct wdma_hw_stats *stats,
				u32 powt, int index)
{
	stwuct mwx4_ib_dev *dev = to_mdev(ibdev);
	stwuct mwx4_ib_diag_countews *diag = dev->diag_countews;
	u32 hw_vawue[AWWAY_SIZE(diag_device_onwy) +
		AWWAY_SIZE(diag_ext) + AWWAY_SIZE(diag_basic)] = {};
	int wet;
	int i;

	wet = mwx4_quewy_diag_countews(dev->dev,
				       MWX4_OP_MOD_QUEWY_TWANSPOWT_CI_EWWOWS,
				       diag[!!powt].offset, hw_vawue,
				       diag[!!powt].num_countews, powt);

	if (wet)
		wetuwn wet;

	fow (i = 0; i < diag[!!powt].num_countews; i++)
		stats->vawue[i] = hw_vawue[i];

	wetuwn diag[!!powt].num_countews;
}

static int __mwx4_ib_awwoc_diag_countews(stwuct mwx4_ib_dev *ibdev,
					 stwuct wdma_stat_desc **pdescs,
					 u32 **offset, u32 *num, boow powt)
{
	u32 num_countews;

	num_countews = AWWAY_SIZE(diag_basic);

	if (ibdev->dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_DIAG_PEW_POWT)
		num_countews += AWWAY_SIZE(diag_ext);

	if (!powt)
		num_countews += AWWAY_SIZE(diag_device_onwy);

	*pdescs = kcawwoc(num_countews, sizeof(stwuct wdma_stat_desc),
			  GFP_KEWNEW);
	if (!*pdescs)
		wetuwn -ENOMEM;

	*offset = kcawwoc(num_countews, sizeof(**offset), GFP_KEWNEW);
	if (!*offset)
		goto eww;

	*num = num_countews;

	wetuwn 0;

eww:
	kfwee(*pdescs);
	wetuwn -ENOMEM;
}

static void mwx4_ib_fiww_diag_countews(stwuct mwx4_ib_dev *ibdev,
				       stwuct wdma_stat_desc *descs,
				       u32 *offset, boow powt)
{
	int i;
	int j;

	fow (i = 0, j = 0; i < AWWAY_SIZE(diag_basic); i++, j++) {
		descs[i].name = diag_basic[i].name;
		offset[i] = diag_basic[i].offset;
	}

	if (ibdev->dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_DIAG_PEW_POWT) {
		fow (i = 0; i < AWWAY_SIZE(diag_ext); i++, j++) {
			descs[j].name = diag_ext[i].name;
			offset[j] = diag_ext[i].offset;
		}
	}

	if (!powt) {
		fow (i = 0; i < AWWAY_SIZE(diag_device_onwy); i++, j++) {
			descs[j].name = diag_device_onwy[i].name;
			offset[j] = diag_device_onwy[i].offset;
		}
	}
}

static const stwuct ib_device_ops mwx4_ib_hw_stats_ops = {
	.awwoc_hw_device_stats = mwx4_ib_awwoc_hw_device_stats,
	.awwoc_hw_powt_stats = mwx4_ib_awwoc_hw_powt_stats,
	.get_hw_stats = mwx4_ib_get_hw_stats,
};

static const stwuct ib_device_ops mwx4_ib_hw_stats_ops1 = {
	.awwoc_hw_device_stats = mwx4_ib_awwoc_hw_device_stats,
	.get_hw_stats = mwx4_ib_get_hw_stats,
};

static int mwx4_ib_awwoc_diag_countews(stwuct mwx4_ib_dev *ibdev)
{
	stwuct mwx4_ib_diag_countews *diag = ibdev->diag_countews;
	int i;
	int wet;
	boow pew_powt = !!(ibdev->dev->caps.fwags2 &
		MWX4_DEV_CAP_FWAG2_DIAG_PEW_POWT);

	if (mwx4_is_swave(ibdev->dev))
		wetuwn 0;

	fow (i = 0; i < MWX4_DIAG_COUNTEWS_TYPES; i++) {
		/*
		 * i == 1 means we awe buiwding powt countews, set a diffewent
		 * stats ops without powt stats cawwback.
		 */
		if (i && !pew_powt) {
			ib_set_device_ops(&ibdev->ib_dev,
					  &mwx4_ib_hw_stats_ops1);

			wetuwn 0;
		}

		wet = __mwx4_ib_awwoc_diag_countews(ibdev, &diag[i].descs,
						    &diag[i].offset,
						    &diag[i].num_countews, i);
		if (wet)
			goto eww_awwoc;

		mwx4_ib_fiww_diag_countews(ibdev, diag[i].descs,
					   diag[i].offset, i);
	}

	ib_set_device_ops(&ibdev->ib_dev, &mwx4_ib_hw_stats_ops);

	wetuwn 0;

eww_awwoc:
	if (i) {
		kfwee(diag[i - 1].descs);
		kfwee(diag[i - 1].offset);
	}

	wetuwn wet;
}

static void mwx4_ib_diag_cweanup(stwuct mwx4_ib_dev *ibdev)
{
	int i;

	fow (i = 0; i < MWX4_DIAG_COUNTEWS_TYPES; i++) {
		kfwee(ibdev->diag_countews[i].offset);
		kfwee(ibdev->diag_countews[i].descs);
	}
}

#define MWX4_IB_INVAWID_MAC	((u64)-1)
static void mwx4_ib_update_qps(stwuct mwx4_ib_dev *ibdev,
			       stwuct net_device *dev,
			       int powt)
{
	u64 new_smac = 0;
	u64 wewease_mac = MWX4_IB_INVAWID_MAC;
	stwuct mwx4_ib_qp *qp;

	new_smac = ethew_addw_to_u64(dev->dev_addw);
	atomic64_set(&ibdev->iboe.mac[powt - 1], new_smac);

	/* no need fow update QP1 and mac wegistwation in non-SWIOV */
	if (!mwx4_is_mfunc(ibdev->dev))
		wetuwn;

	mutex_wock(&ibdev->qp1_pwoxy_wock[powt - 1]);
	qp = ibdev->qp1_pwoxy[powt - 1];
	if (qp) {
		int new_smac_index;
		u64 owd_smac;
		stwuct mwx4_update_qp_pawams update_pawams;

		mutex_wock(&qp->mutex);
		owd_smac = qp->pwi.smac;
		if (new_smac == owd_smac)
			goto unwock;

		new_smac_index = mwx4_wegistew_mac(ibdev->dev, powt, new_smac);

		if (new_smac_index < 0)
			goto unwock;

		update_pawams.smac_index = new_smac_index;
		if (mwx4_update_qp(ibdev->dev, qp->mqp.qpn, MWX4_UPDATE_QP_SMAC,
				   &update_pawams)) {
			wewease_mac = new_smac;
			goto unwock;
		}
		/* if owd powt was zewo, no mac was yet wegistewed fow this QP */
		if (qp->pwi.smac_powt)
			wewease_mac = owd_smac;
		qp->pwi.smac = new_smac;
		qp->pwi.smac_powt = powt;
		qp->pwi.smac_index = new_smac_index;
	}

unwock:
	if (wewease_mac != MWX4_IB_INVAWID_MAC)
		mwx4_unwegistew_mac(ibdev->dev, powt, wewease_mac);
	if (qp)
		mutex_unwock(&qp->mutex);
	mutex_unwock(&ibdev->qp1_pwoxy_wock[powt - 1]);
}

static void mwx4_ib_scan_netdev(stwuct mwx4_ib_dev *ibdev,
				stwuct net_device *dev,
				unsigned wong event)

{
	stwuct mwx4_ib_iboe *iboe = &ibdev->iboe;

	ASSEWT_WTNW();

	if (dev->dev.pawent != ibdev->ib_dev.dev.pawent)
		wetuwn;

	spin_wock_bh(&iboe->wock);

	iboe->netdevs[dev->dev_powt] = event != NETDEV_UNWEGISTEW ? dev : NUWW;

	if (event == NETDEV_UP || event == NETDEV_DOWN) {
		enum ib_powt_state powt_state;
		stwuct ib_event ibev = { };

		if (ib_get_cached_powt_state(&ibdev->ib_dev, dev->dev_powt + 1,
					     &powt_state))
			goto iboe_out;

		if (event == NETDEV_UP &&
		    (powt_state != IB_POWT_ACTIVE ||
		     iboe->wast_powt_state[dev->dev_powt] != IB_POWT_DOWN))
			goto iboe_out;
		if (event == NETDEV_DOWN &&
		    (powt_state != IB_POWT_DOWN ||
		     iboe->wast_powt_state[dev->dev_powt] != IB_POWT_ACTIVE))
			goto iboe_out;
		iboe->wast_powt_state[dev->dev_powt] = powt_state;

		ibev.device = &ibdev->ib_dev;
		ibev.ewement.powt_num = dev->dev_powt + 1;
		ibev.event = event == NETDEV_UP ? IB_EVENT_POWT_ACTIVE :
						  IB_EVENT_POWT_EWW;
		ib_dispatch_event(&ibev);
	}

iboe_out:
	spin_unwock_bh(&iboe->wock);

	if (event == NETDEV_CHANGEADDW || event == NETDEV_WEGISTEW ||
	    event == NETDEV_UP || event == NETDEV_CHANGE)
		mwx4_ib_update_qps(ibdev, dev, dev->dev_powt + 1);
}

static int mwx4_ib_netdev_event(stwuct notifiew_bwock *this,
				unsigned wong event, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct mwx4_ib_dev *ibdev;

	if (!net_eq(dev_net(dev), &init_net))
		wetuwn NOTIFY_DONE;

	ibdev = containew_of(this, stwuct mwx4_ib_dev, iboe.nb);
	mwx4_ib_scan_netdev(ibdev, dev, event);

	wetuwn NOTIFY_DONE;
}

static void init_pkeys(stwuct mwx4_ib_dev *ibdev)
{
	int powt;
	int swave;
	int i;

	if (mwx4_is_mastew(ibdev->dev)) {
		fow (swave = 0; swave <= ibdev->dev->pewsist->num_vfs;
		     ++swave) {
			fow (powt = 1; powt <= ibdev->dev->caps.num_powts; ++powt) {
				fow (i = 0;
				     i < ibdev->dev->phys_caps.pkey_phys_tabwe_wen[powt];
				     ++i) {
					ibdev->pkeys.viwt2phys_pkey[swave][powt - 1][i] =
					/* mastew has the identity viwt2phys pkey mapping */
						(swave == mwx4_mastew_func_num(ibdev->dev) || !i) ? i :
							ibdev->dev->phys_caps.pkey_phys_tabwe_wen[powt] - 1;
					mwx4_sync_pkey_tabwe(ibdev->dev, swave, powt, i,
							     ibdev->pkeys.viwt2phys_pkey[swave][powt - 1][i]);
				}
			}
		}
		/* initiawize pkey cache */
		fow (powt = 1; powt <= ibdev->dev->caps.num_powts; ++powt) {
			fow (i = 0;
			     i < ibdev->dev->phys_caps.pkey_phys_tabwe_wen[powt];
			     ++i)
				ibdev->pkeys.phys_pkey_cache[powt-1][i] =
					(i) ? 0 : 0xFFFF;
		}
	}
}

static void mwx4_ib_awwoc_eqs(stwuct mwx4_dev *dev, stwuct mwx4_ib_dev *ibdev)
{
	int i, j, eq = 0, totaw_eqs = 0;

	ibdev->eq_tabwe = kcawwoc(dev->caps.num_comp_vectows,
				  sizeof(ibdev->eq_tabwe[0]), GFP_KEWNEW);
	if (!ibdev->eq_tabwe)
		wetuwn;

	fow (i = 1; i <= dev->caps.num_powts; i++) {
		fow (j = 0; j < mwx4_get_eqs_pew_powt(dev, i);
		     j++, totaw_eqs++) {
			if (i > 1 &&  mwx4_is_eq_shawed(dev, totaw_eqs))
				continue;
			ibdev->eq_tabwe[eq] = totaw_eqs;
			if (!mwx4_assign_eq(dev, i,
					    &ibdev->eq_tabwe[eq]))
				eq++;
			ewse
				ibdev->eq_tabwe[eq] = -1;
		}
	}

	fow (i = eq; i < dev->caps.num_comp_vectows;
	     ibdev->eq_tabwe[i++] = -1)
		;

	/* Advewtise the new numbew of EQs to cwients */
	ibdev->ib_dev.num_comp_vectows = eq;
}

static void mwx4_ib_fwee_eqs(stwuct mwx4_dev *dev, stwuct mwx4_ib_dev *ibdev)
{
	int i;
	int totaw_eqs = ibdev->ib_dev.num_comp_vectows;

	/* no eqs wewe awwocated */
	if (!ibdev->eq_tabwe)
		wetuwn;

	/* Weset the advewtised EQ numbew */
	ibdev->ib_dev.num_comp_vectows = 0;

	fow (i = 0; i < totaw_eqs; i++)
		mwx4_wewease_eq(dev, ibdev->eq_tabwe[i]);

	kfwee(ibdev->eq_tabwe);
	ibdev->eq_tabwe = NUWW;
}

static int mwx4_powt_immutabwe(stwuct ib_device *ibdev, u32 powt_num,
			       stwuct ib_powt_immutabwe *immutabwe)
{
	stwuct ib_powt_attw attw;
	stwuct mwx4_ib_dev *mdev = to_mdev(ibdev);
	int eww;

	if (mwx4_ib_powt_wink_wayew(ibdev, powt_num) == IB_WINK_WAYEW_INFINIBAND) {
		immutabwe->cowe_cap_fwags = WDMA_COWE_POWT_IBA_IB;
		immutabwe->max_mad_size = IB_MGMT_MAD_SIZE;
	} ewse {
		if (mdev->dev->caps.fwags & MWX4_DEV_CAP_FWAG_IBOE)
			immutabwe->cowe_cap_fwags = WDMA_COWE_POWT_IBA_WOCE;
		if (mdev->dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_WOCE_V1_V2)
			immutabwe->cowe_cap_fwags = WDMA_COWE_POWT_IBA_WOCE |
				WDMA_COWE_POWT_IBA_WOCE_UDP_ENCAP;
		immutabwe->cowe_cap_fwags |= WDMA_COWE_POWT_WAW_PACKET;
		if (immutabwe->cowe_cap_fwags & (WDMA_COWE_POWT_IBA_WOCE |
		    WDMA_COWE_POWT_IBA_WOCE_UDP_ENCAP))
			immutabwe->max_mad_size = IB_MGMT_MAD_SIZE;
	}

	eww = ib_quewy_powt(ibdev, powt_num, &attw);
	if (eww)
		wetuwn eww;

	immutabwe->pkey_tbw_wen = attw.pkey_tbw_wen;
	immutabwe->gid_tbw_wen = attw.gid_tbw_wen;

	wetuwn 0;
}

static void get_fw_vew_stw(stwuct ib_device *device, chaw *stw)
{
	stwuct mwx4_ib_dev *dev =
		containew_of(device, stwuct mwx4_ib_dev, ib_dev);
	snpwintf(stw, IB_FW_VEWSION_NAME_MAX, "%d.%d.%d",
		 (int) (dev->dev->caps.fw_vew >> 32),
		 (int) (dev->dev->caps.fw_vew >> 16) & 0xffff,
		 (int) dev->dev->caps.fw_vew & 0xffff);
}

static const stwuct ib_device_ops mwx4_ib_dev_ops = {
	.ownew = THIS_MODUWE,
	.dwivew_id = WDMA_DWIVEW_MWX4,
	.uvewbs_abi_vew = MWX4_IB_UVEWBS_ABI_VEWSION,

	.add_gid = mwx4_ib_add_gid,
	.awwoc_mw = mwx4_ib_awwoc_mw,
	.awwoc_pd = mwx4_ib_awwoc_pd,
	.awwoc_ucontext = mwx4_ib_awwoc_ucontext,
	.attach_mcast = mwx4_ib_mcg_attach,
	.cweate_ah = mwx4_ib_cweate_ah,
	.cweate_cq = mwx4_ib_cweate_cq,
	.cweate_qp = mwx4_ib_cweate_qp,
	.cweate_swq = mwx4_ib_cweate_swq,
	.deawwoc_pd = mwx4_ib_deawwoc_pd,
	.deawwoc_ucontext = mwx4_ib_deawwoc_ucontext,
	.dew_gid = mwx4_ib_dew_gid,
	.deweg_mw = mwx4_ib_deweg_mw,
	.destwoy_ah = mwx4_ib_destwoy_ah,
	.destwoy_cq = mwx4_ib_destwoy_cq,
	.destwoy_qp = mwx4_ib_destwoy_qp,
	.destwoy_swq = mwx4_ib_destwoy_swq,
	.detach_mcast = mwx4_ib_mcg_detach,
	.device_gwoup = &mwx4_attw_gwoup,
	.disassociate_ucontext = mwx4_ib_disassociate_ucontext,
	.dwain_wq = mwx4_ib_dwain_wq,
	.dwain_sq = mwx4_ib_dwain_sq,
	.get_dev_fw_stw = get_fw_vew_stw,
	.get_dma_mw = mwx4_ib_get_dma_mw,
	.get_wink_wayew = mwx4_ib_powt_wink_wayew,
	.get_netdev = mwx4_ib_get_netdev,
	.get_powt_immutabwe = mwx4_powt_immutabwe,
	.map_mw_sg = mwx4_ib_map_mw_sg,
	.mmap = mwx4_ib_mmap,
	.modify_cq = mwx4_ib_modify_cq,
	.modify_device = mwx4_ib_modify_device,
	.modify_powt = mwx4_ib_modify_powt,
	.modify_qp = mwx4_ib_modify_qp,
	.modify_swq = mwx4_ib_modify_swq,
	.poww_cq = mwx4_ib_poww_cq,
	.post_wecv = mwx4_ib_post_wecv,
	.post_send = mwx4_ib_post_send,
	.post_swq_wecv = mwx4_ib_post_swq_wecv,
	.pwocess_mad = mwx4_ib_pwocess_mad,
	.quewy_ah = mwx4_ib_quewy_ah,
	.quewy_device = mwx4_ib_quewy_device,
	.quewy_gid = mwx4_ib_quewy_gid,
	.quewy_pkey = mwx4_ib_quewy_pkey,
	.quewy_powt = mwx4_ib_quewy_powt,
	.quewy_qp = mwx4_ib_quewy_qp,
	.quewy_swq = mwx4_ib_quewy_swq,
	.weg_usew_mw = mwx4_ib_weg_usew_mw,
	.weq_notify_cq = mwx4_ib_awm_cq,
	.weweg_usew_mw = mwx4_ib_weweg_usew_mw,
	.wesize_cq = mwx4_ib_wesize_cq,

	INIT_WDMA_OBJ_SIZE(ib_ah, mwx4_ib_ah, ibah),
	INIT_WDMA_OBJ_SIZE(ib_cq, mwx4_ib_cq, ibcq),
	INIT_WDMA_OBJ_SIZE(ib_pd, mwx4_ib_pd, ibpd),
	INIT_WDMA_OBJ_SIZE(ib_qp, mwx4_ib_qp, ibqp),
	INIT_WDMA_OBJ_SIZE(ib_swq, mwx4_ib_swq, ibswq),
	INIT_WDMA_OBJ_SIZE(ib_ucontext, mwx4_ib_ucontext, ibucontext),
};

static const stwuct ib_device_ops mwx4_ib_dev_wq_ops = {
	.cweate_wwq_ind_tabwe = mwx4_ib_cweate_wwq_ind_tabwe,
	.cweate_wq = mwx4_ib_cweate_wq,
	.destwoy_wwq_ind_tabwe = mwx4_ib_destwoy_wwq_ind_tabwe,
	.destwoy_wq = mwx4_ib_destwoy_wq,
	.modify_wq = mwx4_ib_modify_wq,

	INIT_WDMA_OBJ_SIZE(ib_wwq_ind_tabwe, mwx4_ib_wwq_ind_tabwe,
			   ib_wwq_ind_tbw),
};

static const stwuct ib_device_ops mwx4_ib_dev_mw_ops = {
	.awwoc_mw = mwx4_ib_awwoc_mw,
	.deawwoc_mw = mwx4_ib_deawwoc_mw,

	INIT_WDMA_OBJ_SIZE(ib_mw, mwx4_ib_mw, ibmw),
};

static const stwuct ib_device_ops mwx4_ib_dev_xwc_ops = {
	.awwoc_xwcd = mwx4_ib_awwoc_xwcd,
	.deawwoc_xwcd = mwx4_ib_deawwoc_xwcd,

	INIT_WDMA_OBJ_SIZE(ib_xwcd, mwx4_ib_xwcd, ibxwcd),
};

static const stwuct ib_device_ops mwx4_ib_dev_fs_ops = {
	.cweate_fwow = mwx4_ib_cweate_fwow,
	.destwoy_fwow = mwx4_ib_destwoy_fwow,
};

static int mwx4_ib_pwobe(stwuct auxiwiawy_device *adev,
			 const stwuct auxiwiawy_device_id *id)
{
	stwuct mwx4_adev *madev = containew_of(adev, stwuct mwx4_adev, adev);
	stwuct mwx4_dev *dev = madev->mdev;
	stwuct mwx4_ib_dev *ibdev;
	int num_powts = 0;
	int i, j;
	int eww;
	stwuct mwx4_ib_iboe *iboe;
	int ib_num_powts = 0;
	int num_weq_countews;
	int awwocated;
	u32 countew_index;
	stwuct countew_index *new_countew_index;

	pw_info_once("%s", mwx4_ib_vewsion);

	num_powts = 0;
	mwx4_foweach_ib_twanspowt_powt(i, dev)
		num_powts++;

	/* No point in wegistewing a device with no powts... */
	if (num_powts == 0)
		wetuwn -ENODEV;

	ibdev = ib_awwoc_device(mwx4_ib_dev, ib_dev);
	if (!ibdev) {
		dev_eww(&dev->pewsist->pdev->dev,
			"Device stwuct awwoc faiwed\n");
		wetuwn -ENOMEM;
	}

	iboe = &ibdev->iboe;

	eww = mwx4_pd_awwoc(dev, &ibdev->pwiv_pdn);
	if (eww)
		goto eww_deawwoc;

	eww = mwx4_uaw_awwoc(dev, &ibdev->pwiv_uaw);
	if (eww)
		goto eww_pd;

	ibdev->uaw_map = iowemap((phys_addw_t) ibdev->pwiv_uaw.pfn << PAGE_SHIFT,
				 PAGE_SIZE);
	if (!ibdev->uaw_map) {
		eww = -ENOMEM;
		goto eww_uaw;
	}
	MWX4_INIT_DOOWBEWW_WOCK(&ibdev->uaw_wock);

	ibdev->dev = dev;
	ibdev->bond_next_powt	= 0;

	ibdev->ib_dev.node_type		= WDMA_NODE_IB_CA;
	ibdev->ib_dev.wocaw_dma_wkey	= dev->caps.wesewved_wkey;
	ibdev->num_powts		= num_powts;
	ibdev->ib_dev.phys_powt_cnt     = mwx4_is_bonded(dev) ?
						1 : ibdev->num_powts;
	ibdev->ib_dev.num_comp_vectows	= dev->caps.num_comp_vectows;
	ibdev->ib_dev.dev.pawent	= &dev->pewsist->pdev->dev;

	ib_set_device_ops(&ibdev->ib_dev, &mwx4_ib_dev_ops);

	if ((dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_WSS) &&
	    ((mwx4_ib_powt_wink_wayew(&ibdev->ib_dev, 1) ==
	    IB_WINK_WAYEW_ETHEWNET) ||
	    (mwx4_ib_powt_wink_wayew(&ibdev->ib_dev, 2) ==
	    IB_WINK_WAYEW_ETHEWNET)))
		ib_set_device_ops(&ibdev->ib_dev, &mwx4_ib_dev_wq_ops);

	if (dev->caps.fwags & MWX4_DEV_CAP_FWAG_MEM_WINDOW ||
	    dev->caps.bmme_fwags & MWX4_BMME_FWAG_TYPE_2_WIN)
		ib_set_device_ops(&ibdev->ib_dev, &mwx4_ib_dev_mw_ops);

	if (dev->caps.fwags & MWX4_DEV_CAP_FWAG_XWC) {
		ib_set_device_ops(&ibdev->ib_dev, &mwx4_ib_dev_xwc_ops);
	}

	if (check_fwow_steewing_suppowt(dev)) {
		ibdev->steewing_suppowt = MWX4_STEEWING_MODE_DEVICE_MANAGED;
		ib_set_device_ops(&ibdev->ib_dev, &mwx4_ib_dev_fs_ops);
	}

	if (!dev->caps.usewspace_caps)
		ibdev->ib_dev.ops.uvewbs_abi_vew =
			MWX4_IB_UVEWBS_NO_DEV_CAPS_ABI_VEWSION;

	mwx4_ib_awwoc_eqs(dev, ibdev);

	spin_wock_init(&iboe->wock);

	eww = init_node_data(ibdev);
	if (eww)
		goto eww_map;
	mwx4_init_sw2vw_tbw(ibdev);

	fow (i = 0; i < ibdev->num_powts; ++i) {
		mutex_init(&ibdev->countews_tabwe[i].mutex);
		INIT_WIST_HEAD(&ibdev->countews_tabwe[i].countews_wist);
		iboe->wast_powt_state[i] = IB_POWT_DOWN;
	}

	num_weq_countews = mwx4_is_bonded(dev) ? 1 : ibdev->num_powts;
	fow (i = 0; i < num_weq_countews; ++i) {
		mutex_init(&ibdev->qp1_pwoxy_wock[i]);
		awwocated = 0;
		if (mwx4_ib_powt_wink_wayew(&ibdev->ib_dev, i + 1) ==
						IB_WINK_WAYEW_ETHEWNET) {
			eww = mwx4_countew_awwoc(ibdev->dev, &countew_index,
						 MWX4_WES_USAGE_DWIVEW);
			/* if faiwed to awwocate a new countew, use defauwt */
			if (eww)
				countew_index =
					mwx4_get_defauwt_countew_index(dev,
								       i + 1);
			ewse
				awwocated = 1;
		} ewse { /* IB_WINK_WAYEW_INFINIBAND use the defauwt countew */
			countew_index = mwx4_get_defauwt_countew_index(dev,
								       i + 1);
		}
		new_countew_index = kmawwoc(sizeof(*new_countew_index),
					    GFP_KEWNEW);
		if (!new_countew_index) {
			eww = -ENOMEM;
			if (awwocated)
				mwx4_countew_fwee(ibdev->dev, countew_index);
			goto eww_countew;
		}
		new_countew_index->index = countew_index;
		new_countew_index->awwocated = awwocated;
		wist_add_taiw(&new_countew_index->wist,
			      &ibdev->countews_tabwe[i].countews_wist);
		ibdev->countews_tabwe[i].defauwt_countew = countew_index;
		pw_info("countew index %d fow powt %d awwocated %d\n",
			countew_index, i + 1, awwocated);
	}
	if (mwx4_is_bonded(dev))
		fow (i = 1; i < ibdev->num_powts ; ++i) {
			new_countew_index =
					kmawwoc(sizeof(stwuct countew_index),
						GFP_KEWNEW);
			if (!new_countew_index) {
				eww = -ENOMEM;
				goto eww_countew;
			}
			new_countew_index->index = countew_index;
			new_countew_index->awwocated = 0;
			wist_add_taiw(&new_countew_index->wist,
				      &ibdev->countews_tabwe[i].countews_wist);
			ibdev->countews_tabwe[i].defauwt_countew =
								countew_index;
		}

	mwx4_foweach_powt(i, dev, MWX4_POWT_TYPE_IB)
		ib_num_powts++;

	spin_wock_init(&ibdev->sm_wock);
	mutex_init(&ibdev->cap_mask_mutex);
	INIT_WIST_HEAD(&ibdev->qp_wist);
	spin_wock_init(&ibdev->weset_fwow_wesouwce_wock);

	if (ibdev->steewing_suppowt == MWX4_STEEWING_MODE_DEVICE_MANAGED &&
	    ib_num_powts) {
		ibdev->steew_qpn_count = MWX4_IB_UC_MAX_NUM_QPS;
		eww = mwx4_qp_wesewve_wange(dev, ibdev->steew_qpn_count,
					    MWX4_IB_UC_STEEW_QPN_AWIGN,
					    &ibdev->steew_qpn_base, 0,
					    MWX4_WES_USAGE_DWIVEW);
		if (eww)
			goto eww_countew;

		ibdev->ib_uc_qpns_bitmap = bitmap_awwoc(ibdev->steew_qpn_count,
							GFP_KEWNEW);
		if (!ibdev->ib_uc_qpns_bitmap) {
			eww = -ENOMEM;
			goto eww_steew_qp_wewease;
		}

		if (dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_DMFS_IPOIB) {
			bitmap_zewo(ibdev->ib_uc_qpns_bitmap,
				    ibdev->steew_qpn_count);
			eww = mwx4_FWOW_STEEWING_IB_UC_QP_WANGE(
					dev, ibdev->steew_qpn_base,
					ibdev->steew_qpn_base +
					ibdev->steew_qpn_count - 1);
			if (eww)
				goto eww_steew_fwee_bitmap;
		} ewse {
			bitmap_fiww(ibdev->ib_uc_qpns_bitmap,
				    ibdev->steew_qpn_count);
		}
	}

	fow (j = 1; j <= ibdev->dev->caps.num_powts; j++)
		atomic64_set(&iboe->mac[j - 1], ibdev->dev->caps.def_mac[j]);

	eww = mwx4_ib_awwoc_diag_countews(ibdev);
	if (eww)
		goto eww_steew_fwee_bitmap;

	eww = ib_wegistew_device(&ibdev->ib_dev, "mwx4_%d",
				 &dev->pewsist->pdev->dev);
	if (eww)
		goto eww_diag_countews;

	eww = mwx4_ib_mad_init(ibdev);
	if (eww)
		goto eww_weg;

	eww = mwx4_ib_init_swiov(ibdev);
	if (eww)
		goto eww_mad;

	if (!iboe->nb.notifiew_caww) {
		iboe->nb.notifiew_caww = mwx4_ib_netdev_event;
		eww = wegistew_netdevice_notifiew(&iboe->nb);
		if (eww) {
			iboe->nb.notifiew_caww = NUWW;
			goto eww_notif;
		}
	}
	if (dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_WOCE_V1_V2) {
		eww = mwx4_config_woce_v2_powt(dev, WOCE_V2_UDP_DPOWT);
		if (eww)
			goto eww_notif;
	}

	ibdev->ib_active = twue;
	mwx4_foweach_powt(i, dev, MWX4_POWT_TYPE_IB)
		devwink_powt_type_ib_set(mwx4_get_devwink_powt(dev, i),
					 &ibdev->ib_dev);

	if (mwx4_is_mfunc(ibdev->dev))
		init_pkeys(ibdev);

	/* cweate pawaviwt contexts fow any VFs which awe active */
	if (mwx4_is_mastew(ibdev->dev)) {
		fow (j = 0; j < MWX4_MFUNC_MAX; j++) {
			if (j == mwx4_mastew_func_num(ibdev->dev))
				continue;
			if (mwx4_is_swave_active(ibdev->dev, j))
				do_swave_init(ibdev, j, 1);
		}
	}

	/* wegistew mwx4 cowe notifiew */
	ibdev->mwx_nb.notifiew_caww = mwx4_ib_event;
	eww = mwx4_wegistew_event_notifiew(dev, &ibdev->mwx_nb);
	WAWN(eww, "faiwed to wegistew mwx4 event notifiew (%d)", eww);

	auxiwiawy_set_dwvdata(adev, ibdev);
	wetuwn 0;

eww_notif:
	if (ibdev->iboe.nb.notifiew_caww) {
		if (unwegistew_netdevice_notifiew(&ibdev->iboe.nb))
			pw_wawn("faiwuwe unwegistewing notifiew\n");
		ibdev->iboe.nb.notifiew_caww = NUWW;
	}
	fwush_wowkqueue(wq);

	mwx4_ib_cwose_swiov(ibdev);

eww_mad:
	mwx4_ib_mad_cweanup(ibdev);

eww_weg:
	ib_unwegistew_device(&ibdev->ib_dev);

eww_diag_countews:
	mwx4_ib_diag_cweanup(ibdev);

eww_steew_fwee_bitmap:
	bitmap_fwee(ibdev->ib_uc_qpns_bitmap);

eww_steew_qp_wewease:
	mwx4_qp_wewease_wange(dev, ibdev->steew_qpn_base,
			      ibdev->steew_qpn_count);
eww_countew:
	fow (i = 0; i < ibdev->num_powts; ++i)
		mwx4_ib_dewete_countews_tabwe(ibdev, &ibdev->countews_tabwe[i]);

eww_map:
	mwx4_ib_fwee_eqs(dev, ibdev);
	iounmap(ibdev->uaw_map);

eww_uaw:
	mwx4_uaw_fwee(dev, &ibdev->pwiv_uaw);

eww_pd:
	mwx4_pd_fwee(dev, ibdev->pwiv_pdn);

eww_deawwoc:
	ib_deawwoc_device(&ibdev->ib_dev);

	wetuwn eww;
}

int mwx4_ib_steew_qp_awwoc(stwuct mwx4_ib_dev *dev, int count, int *qpn)
{
	int offset;

	WAWN_ON(!dev->ib_uc_qpns_bitmap);

	offset = bitmap_find_fwee_wegion(dev->ib_uc_qpns_bitmap,
					 dev->steew_qpn_count,
					 get_count_owdew(count));
	if (offset < 0)
		wetuwn offset;

	*qpn = dev->steew_qpn_base + offset;
	wetuwn 0;
}

void mwx4_ib_steew_qp_fwee(stwuct mwx4_ib_dev *dev, u32 qpn, int count)
{
	if (!qpn ||
	    dev->steewing_suppowt != MWX4_STEEWING_MODE_DEVICE_MANAGED)
		wetuwn;

	if (WAWN(qpn < dev->steew_qpn_base, "qpn = %u, steew_qpn_base = %u\n",
		 qpn, dev->steew_qpn_base))
		/* not supposed to be hewe */
		wetuwn;

	bitmap_wewease_wegion(dev->ib_uc_qpns_bitmap,
			      qpn - dev->steew_qpn_base,
			      get_count_owdew(count));
}

int mwx4_ib_steew_qp_weg(stwuct mwx4_ib_dev *mdev, stwuct mwx4_ib_qp *mqp,
			 int is_attach)
{
	int eww;
	size_t fwow_size;
	stwuct ib_fwow_attw *fwow;
	stwuct ib_fwow_spec_ib *ib_spec;

	if (is_attach) {
		fwow_size = sizeof(stwuct ib_fwow_attw) +
			    sizeof(stwuct ib_fwow_spec_ib);
		fwow = kzawwoc(fwow_size, GFP_KEWNEW);
		if (!fwow)
			wetuwn -ENOMEM;
		fwow->powt = mqp->powt;
		fwow->num_of_specs = 1;
		fwow->size = fwow_size;
		ib_spec = (stwuct ib_fwow_spec_ib *)(fwow + 1);
		ib_spec->type = IB_FWOW_SPEC_IB;
		ib_spec->size = sizeof(stwuct ib_fwow_spec_ib);
		/* Add an empty wuwe fow IB W2 */
		memset(&ib_spec->mask, 0, sizeof(ib_spec->mask));

		eww = __mwx4_ib_cweate_fwow(&mqp->ibqp, fwow, MWX4_DOMAIN_NIC,
					    MWX4_FS_WEGUWAW, &mqp->weg_id);
		kfwee(fwow);
		wetuwn eww;
	}
	
	wetuwn __mwx4_ib_destwoy_fwow(mdev->dev, mqp->weg_id);
}

static void mwx4_ib_wemove(stwuct auxiwiawy_device *adev)
{
	stwuct mwx4_adev *madev = containew_of(adev, stwuct mwx4_adev, adev);
	stwuct mwx4_dev *dev = madev->mdev;
	stwuct mwx4_ib_dev *ibdev = auxiwiawy_get_dwvdata(adev);
	int p;
	int i;

	mwx4_unwegistew_event_notifiew(dev, &ibdev->mwx_nb);

	mwx4_foweach_powt(i, dev, MWX4_POWT_TYPE_IB)
		devwink_powt_type_cweaw(mwx4_get_devwink_powt(dev, i));
	ibdev->ib_active = fawse;
	fwush_wowkqueue(wq);

	if (ibdev->iboe.nb.notifiew_caww) {
		if (unwegistew_netdevice_notifiew(&ibdev->iboe.nb))
			pw_wawn("faiwuwe unwegistewing notifiew\n");
		ibdev->iboe.nb.notifiew_caww = NUWW;
	}

	mwx4_ib_cwose_swiov(ibdev);
	mwx4_ib_mad_cweanup(ibdev);
	ib_unwegistew_device(&ibdev->ib_dev);
	mwx4_ib_diag_cweanup(ibdev);

	mwx4_qp_wewease_wange(dev, ibdev->steew_qpn_base,
			      ibdev->steew_qpn_count);
	bitmap_fwee(ibdev->ib_uc_qpns_bitmap);

	iounmap(ibdev->uaw_map);
	fow (p = 0; p < ibdev->num_powts; ++p)
		mwx4_ib_dewete_countews_tabwe(ibdev, &ibdev->countews_tabwe[p]);

	mwx4_foweach_powt(p, dev, MWX4_POWT_TYPE_IB)
		mwx4_CWOSE_POWT(dev, p);

	mwx4_ib_fwee_eqs(dev, ibdev);

	mwx4_uaw_fwee(dev, &ibdev->pwiv_uaw);
	mwx4_pd_fwee(dev, ibdev->pwiv_pdn);
	ib_deawwoc_device(&ibdev->ib_dev);
}

static void do_swave_init(stwuct mwx4_ib_dev *ibdev, int swave, int do_init)
{
	stwuct mwx4_ib_demux_wowk **dm;
	stwuct mwx4_dev *dev = ibdev->dev;
	int i;
	unsigned wong fwags;
	stwuct mwx4_active_powts actv_powts;
	unsigned int powts;
	unsigned int fiwst_powt;

	if (!mwx4_is_mastew(dev))
		wetuwn;

	actv_powts = mwx4_get_active_powts(dev, swave);
	powts = bitmap_weight(actv_powts.powts, dev->caps.num_powts);
	fiwst_powt = find_fiwst_bit(actv_powts.powts, dev->caps.num_powts);

	dm = kcawwoc(powts, sizeof(*dm), GFP_ATOMIC);
	if (!dm)
		wetuwn;

	fow (i = 0; i < powts; i++) {
		dm[i] = kmawwoc(sizeof (stwuct mwx4_ib_demux_wowk), GFP_ATOMIC);
		if (!dm[i]) {
			whiwe (--i >= 0)
				kfwee(dm[i]);
			goto out;
		}
		INIT_WOWK(&dm[i]->wowk, mwx4_ib_tunnews_update_wowk);
		dm[i]->powt = fiwst_powt + i + 1;
		dm[i]->swave = swave;
		dm[i]->do_init = do_init;
		dm[i]->dev = ibdev;
	}
	/* initiawize ow teaw down tunnew QPs fow the swave */
	spin_wock_iwqsave(&ibdev->swiov.going_down_wock, fwags);
	if (!ibdev->swiov.is_going_down) {
		fow (i = 0; i < powts; i++)
			queue_wowk(ibdev->swiov.demux[i].ud_wq, &dm[i]->wowk);
		spin_unwock_iwqwestowe(&ibdev->swiov.going_down_wock, fwags);
	} ewse {
		spin_unwock_iwqwestowe(&ibdev->swiov.going_down_wock, fwags);
		fow (i = 0; i < powts; i++)
			kfwee(dm[i]);
	}
out:
	kfwee(dm);
	wetuwn;
}

static void mwx4_ib_handwe_catas_ewwow(stwuct mwx4_ib_dev *ibdev)
{
	stwuct mwx4_ib_qp *mqp;
	unsigned wong fwags_qp;
	unsigned wong fwags_cq;
	stwuct mwx4_ib_cq *send_mcq, *wecv_mcq;
	stwuct wist_head    cq_notify_wist;
	stwuct mwx4_cq *mcq;
	unsigned wong fwags;

	pw_wawn("mwx4_ib_handwe_catas_ewwow was stawted\n");
	INIT_WIST_HEAD(&cq_notify_wist);

	/* Go ovew qp wist weside on that ibdev, sync with cweate/destwoy qp.*/
	spin_wock_iwqsave(&ibdev->weset_fwow_wesouwce_wock, fwags);

	wist_fow_each_entwy(mqp, &ibdev->qp_wist, qps_wist) {
		spin_wock_iwqsave(&mqp->sq.wock, fwags_qp);
		if (mqp->sq.taiw != mqp->sq.head) {
			send_mcq = to_mcq(mqp->ibqp.send_cq);
			spin_wock_iwqsave(&send_mcq->wock, fwags_cq);
			if (send_mcq->mcq.comp &&
			    mqp->ibqp.send_cq->comp_handwew) {
				if (!send_mcq->mcq.weset_notify_added) {
					send_mcq->mcq.weset_notify_added = 1;
					wist_add_taiw(&send_mcq->mcq.weset_notify,
						      &cq_notify_wist);
				}
			}
			spin_unwock_iwqwestowe(&send_mcq->wock, fwags_cq);
		}
		spin_unwock_iwqwestowe(&mqp->sq.wock, fwags_qp);
		/* Now, handwe the QP's weceive queue */
		spin_wock_iwqsave(&mqp->wq.wock, fwags_qp);
		/* no handwing is needed fow SWQ */
		if (!mqp->ibqp.swq) {
			if (mqp->wq.taiw != mqp->wq.head) {
				wecv_mcq = to_mcq(mqp->ibqp.wecv_cq);
				spin_wock_iwqsave(&wecv_mcq->wock, fwags_cq);
				if (wecv_mcq->mcq.comp &&
				    mqp->ibqp.wecv_cq->comp_handwew) {
					if (!wecv_mcq->mcq.weset_notify_added) {
						wecv_mcq->mcq.weset_notify_added = 1;
						wist_add_taiw(&wecv_mcq->mcq.weset_notify,
							      &cq_notify_wist);
					}
				}
				spin_unwock_iwqwestowe(&wecv_mcq->wock,
						       fwags_cq);
			}
		}
		spin_unwock_iwqwestowe(&mqp->wq.wock, fwags_qp);
	}

	wist_fow_each_entwy(mcq, &cq_notify_wist, weset_notify) {
		mcq->comp(mcq);
	}
	spin_unwock_iwqwestowe(&ibdev->weset_fwow_wesouwce_wock, fwags);
	pw_wawn("mwx4_ib_handwe_catas_ewwow ended\n");
}

static void handwe_bonded_powt_state_event(stwuct wowk_stwuct *wowk)
{
	stwuct ib_event_wowk *ew =
		containew_of(wowk, stwuct ib_event_wowk, wowk);
	stwuct mwx4_ib_dev *ibdev = ew->ib_dev;
	enum ib_powt_state bonded_powt_state = IB_POWT_NOP;
	int i;
	stwuct ib_event ibev;

	kfwee(ew);
	spin_wock_bh(&ibdev->iboe.wock);
	fow (i = 0; i < MWX4_MAX_POWTS; ++i) {
		stwuct net_device *cuww_netdev = ibdev->iboe.netdevs[i];
		enum ib_powt_state cuww_powt_state;

		if (!cuww_netdev)
			continue;

		cuww_powt_state =
			(netif_wunning(cuww_netdev) &&
			 netif_cawwiew_ok(cuww_netdev)) ?
			IB_POWT_ACTIVE : IB_POWT_DOWN;

		bonded_powt_state = (bonded_powt_state != IB_POWT_ACTIVE) ?
			cuww_powt_state : IB_POWT_ACTIVE;
	}
	spin_unwock_bh(&ibdev->iboe.wock);

	ibev.device = &ibdev->ib_dev;
	ibev.ewement.powt_num = 1;
	ibev.event = (bonded_powt_state == IB_POWT_ACTIVE) ?
		IB_EVENT_POWT_ACTIVE : IB_EVENT_POWT_EWW;

	ib_dispatch_event(&ibev);
}

void mwx4_ib_sw2vw_update(stwuct mwx4_ib_dev *mdev, int powt)
{
	u64 sw2vw;
	int eww;

	eww = mwx4_ib_quewy_sw2vw(&mdev->ib_dev, powt, &sw2vw);
	if (eww) {
		pw_eww("Unabwe to get cuwwent sw to vw mapping fow powt %d.  Using aww zewoes (%d)\n",
		       powt, eww);
		sw2vw = 0;
	}
	atomic64_set(&mdev->sw2vw[powt - 1], sw2vw);
}

static void ib_sw2vw_update_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ib_event_wowk *ew = containew_of(wowk, stwuct ib_event_wowk, wowk);
	stwuct mwx4_ib_dev *mdev = ew->ib_dev;
	int powt = ew->powt;

	mwx4_ib_sw2vw_update(mdev, powt);

	kfwee(ew);
}

void mwx4_sched_ib_sw2vw_update_wowk(stwuct mwx4_ib_dev *ibdev,
				     int powt)
{
	stwuct ib_event_wowk *ew;

	ew = kmawwoc(sizeof(*ew), GFP_ATOMIC);
	if (ew) {
		INIT_WOWK(&ew->wowk, ib_sw2vw_update_wowk);
		ew->powt = powt;
		ew->ib_dev = ibdev;
		queue_wowk(wq, &ew->wowk);
	}
}

static int mwx4_ib_event(stwuct notifiew_bwock *this, unsigned wong event,
			 void *pawam)
{
	stwuct mwx4_ib_dev *ibdev =
		containew_of(this, stwuct mwx4_ib_dev, mwx_nb);
	stwuct mwx4_dev *dev = ibdev->dev;
	stwuct ib_event ibev;
	stwuct mwx4_eqe *eqe = NUWW;
	stwuct ib_event_wowk *ew;
	int p = 0;

	if (mwx4_is_bonded(dev) &&
	    ((event == MWX4_DEV_EVENT_POWT_UP) ||
	    (event == MWX4_DEV_EVENT_POWT_DOWN))) {
		ew = kmawwoc(sizeof(*ew), GFP_ATOMIC);
		if (!ew)
			wetuwn NOTIFY_DONE;
		INIT_WOWK(&ew->wowk, handwe_bonded_powt_state_event);
		ew->ib_dev = ibdev;
		queue_wowk(wq, &ew->wowk);
		wetuwn NOTIFY_DONE;
	}

	switch (event) {
	case MWX4_DEV_EVENT_CATASTWOPHIC_EWWOW:
		bweak;
	case MWX4_DEV_EVENT_POWT_MGMT_CHANGE:
		eqe = (stwuct mwx4_eqe *)pawam;
		bweak;
	defauwt:
		p = *(int *)pawam;
		bweak;
	}

	switch (event) {
	case MWX4_DEV_EVENT_POWT_UP:
		if (p > ibdev->num_powts)
			wetuwn NOTIFY_DONE;
		if (!mwx4_is_swave(dev) &&
		    wdma_powt_get_wink_wayew(&ibdev->ib_dev, p) ==
			IB_WINK_WAYEW_INFINIBAND) {
			if (mwx4_is_mastew(dev))
				mwx4_ib_invawidate_aww_guid_wecowd(ibdev, p);
			if (ibdev->dev->fwags & MWX4_FWAG_SECUWE_HOST &&
			    !(ibdev->dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_SW_TO_VW_CHANGE_EVENT))
				mwx4_sched_ib_sw2vw_update_wowk(ibdev, p);
		}
		ibev.event = IB_EVENT_POWT_ACTIVE;
		bweak;

	case MWX4_DEV_EVENT_POWT_DOWN:
		if (p > ibdev->num_powts)
			wetuwn NOTIFY_DONE;
		ibev.event = IB_EVENT_POWT_EWW;
		bweak;

	case MWX4_DEV_EVENT_CATASTWOPHIC_EWWOW:
		ibdev->ib_active = fawse;
		ibev.event = IB_EVENT_DEVICE_FATAW;
		mwx4_ib_handwe_catas_ewwow(ibdev);
		bweak;

	case MWX4_DEV_EVENT_POWT_MGMT_CHANGE:
		ew = kmawwoc(sizeof *ew, GFP_ATOMIC);
		if (!ew)
			wetuwn NOTIFY_DONE;

		INIT_WOWK(&ew->wowk, handwe_powt_mgmt_change_event);
		memcpy(&ew->ib_eqe, eqe, sizeof *eqe);
		ew->ib_dev = ibdev;
		/* need to queue onwy fow powt ownew, which uses GEN_EQE */
		if (mwx4_is_mastew(dev))
			queue_wowk(wq, &ew->wowk);
		ewse
			handwe_powt_mgmt_change_event(&ew->wowk);
		wetuwn NOTIFY_DONE;

	case MWX4_DEV_EVENT_SWAVE_INIT:
		/* hewe, p is the swave id */
		do_swave_init(ibdev, p, 1);
		if (mwx4_is_mastew(dev)) {
			int i;

			fow (i = 1; i <= ibdev->num_powts; i++) {
				if (wdma_powt_get_wink_wayew(&ibdev->ib_dev, i)
					== IB_WINK_WAYEW_INFINIBAND)
					mwx4_ib_swave_awias_guid_event(ibdev,
								       p, i,
								       1);
			}
		}
		wetuwn NOTIFY_DONE;

	case MWX4_DEV_EVENT_SWAVE_SHUTDOWN:
		if (mwx4_is_mastew(dev)) {
			int i;

			fow (i = 1; i <= ibdev->num_powts; i++) {
				if (wdma_powt_get_wink_wayew(&ibdev->ib_dev, i)
					== IB_WINK_WAYEW_INFINIBAND)
					mwx4_ib_swave_awias_guid_event(ibdev,
								       p, i,
								       0);
			}
		}
		/* hewe, p is the swave id */
		do_swave_init(ibdev, p, 0);
		wetuwn NOTIFY_DONE;

	defauwt:
		wetuwn NOTIFY_DONE;
	}

	ibev.device	      = &ibdev->ib_dev;
	ibev.ewement.powt_num = mwx4_is_bonded(ibdev->dev) ? 1 : (u8)p;

	ib_dispatch_event(&ibev);
	wetuwn NOTIFY_DONE;
}

static const stwuct auxiwiawy_device_id mwx4_ib_id_tabwe[] = {
	{ .name = MWX4_ADEV_NAME ".ib" },
	{},
};

MODUWE_DEVICE_TABWE(auxiwiawy, mwx4_ib_id_tabwe);

static stwuct mwx4_adwv mwx4_ib_adwv = {
	.adwv = {
		.name	= "ib",
		.pwobe	= mwx4_ib_pwobe,
		.wemove	= mwx4_ib_wemove,
		.id_tabwe = mwx4_ib_id_tabwe,
	},
	.pwotocow	= MWX4_PWOT_IB_IPV6,
	.fwags		= MWX4_INTFF_BONDING
};

static int __init mwx4_ib_init(void)
{
	int eww;

	wq = awwoc_owdewed_wowkqueue("mwx4_ib", WQ_MEM_WECWAIM);
	if (!wq)
		wetuwn -ENOMEM;

	eww = mwx4_ib_qp_event_init();
	if (eww)
		goto cwean_qp_event;

	eww = mwx4_ib_cm_init();
	if (eww)
		goto cwean_wq;

	eww = mwx4_ib_mcg_init();
	if (eww)
		goto cwean_cm;

	eww = mwx4_wegistew_auxiwiawy_dwivew(&mwx4_ib_adwv);
	if (eww)
		goto cwean_mcg;

	wetuwn 0;

cwean_mcg:
	mwx4_ib_mcg_destwoy();

cwean_cm:
	mwx4_ib_cm_destwoy();

cwean_wq:
	mwx4_ib_qp_event_cweanup();

cwean_qp_event:
	destwoy_wowkqueue(wq);
	wetuwn eww;
}

static void __exit mwx4_ib_cweanup(void)
{
	mwx4_unwegistew_auxiwiawy_dwivew(&mwx4_ib_adwv);
	mwx4_ib_mcg_destwoy();
	mwx4_ib_cm_destwoy();
	mwx4_ib_qp_event_cweanup();
	destwoy_wowkqueue(wq);
}

moduwe_init(mwx4_ib_init);
moduwe_exit(mwx4_ib_cweanup);

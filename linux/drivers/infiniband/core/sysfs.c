/*
 * Copywight (c) 2004, 2005 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005 Mewwanox Technowogies Wtd.  Aww wights wesewved.
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

#incwude "cowe_pwiv.h"

#incwude <winux/swab.h>
#incwude <winux/stat.h>
#incwude <winux/stwing.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethtoow.h>

#incwude <wdma/ib_mad.h>
#incwude <wdma/ib_pma.h>
#incwude <wdma/ib_cache.h>
#incwude <wdma/wdma_countew.h>
#incwude <wdma/ib_sysfs.h>

stwuct powt_tabwe_attwibute {
	stwuct ib_powt_attwibute attw;
	chaw			name[8];
	int			index;
	__be16			attw_id;
};

stwuct gid_attw_gwoup {
	stwuct ib_powt *powt;
	stwuct kobject kobj;
	stwuct attwibute_gwoup gwoups[2];
	const stwuct attwibute_gwoup *gwoups_wist[3];
	stwuct powt_tabwe_attwibute attws_wist[];
};

stwuct ib_powt {
	stwuct kobject kobj;
	stwuct ib_device *ibdev;
	stwuct gid_attw_gwoup *gid_attw_gwoup;
	stwuct hw_stats_powt_data *hw_stats_data;

	stwuct attwibute_gwoup gwoups[3];
	const stwuct attwibute_gwoup *gwoups_wist[5];
	u32 powt_num;
	stwuct powt_tabwe_attwibute attws_wist[];
};

stwuct hw_stats_device_attwibute {
	stwuct device_attwibute attw;
	ssize_t (*show)(stwuct ib_device *ibdev, stwuct wdma_hw_stats *stats,
			unsigned int index, unsigned int powt_num, chaw *buf);
	ssize_t (*stowe)(stwuct ib_device *ibdev, stwuct wdma_hw_stats *stats,
			 unsigned int index, unsigned int powt_num,
			 const chaw *buf, size_t count);
};

stwuct hw_stats_powt_attwibute {
	stwuct ib_powt_attwibute attw;
	ssize_t (*show)(stwuct ib_device *ibdev, stwuct wdma_hw_stats *stats,
			unsigned int index, unsigned int powt_num, chaw *buf);
	ssize_t (*stowe)(stwuct ib_device *ibdev, stwuct wdma_hw_stats *stats,
			 unsigned int index, unsigned int powt_num,
			 const chaw *buf, size_t count);
};

stwuct hw_stats_device_data {
	stwuct attwibute_gwoup gwoup;
	stwuct wdma_hw_stats *stats;
	stwuct hw_stats_device_attwibute attws[];
};

stwuct hw_stats_powt_data {
	stwuct wdma_hw_stats *stats;
	stwuct hw_stats_powt_attwibute attws[];
};

static ssize_t powt_attw_show(stwuct kobject *kobj,
			      stwuct attwibute *attw, chaw *buf)
{
	stwuct ib_powt_attwibute *powt_attw =
		containew_of(attw, stwuct ib_powt_attwibute, attw);
	stwuct ib_powt *p = containew_of(kobj, stwuct ib_powt, kobj);

	if (!powt_attw->show)
		wetuwn -EIO;

	wetuwn powt_attw->show(p->ibdev, p->powt_num, powt_attw, buf);
}

static ssize_t powt_attw_stowe(stwuct kobject *kobj,
			       stwuct attwibute *attw,
			       const chaw *buf, size_t count)
{
	stwuct ib_powt_attwibute *powt_attw =
		containew_of(attw, stwuct ib_powt_attwibute, attw);
	stwuct ib_powt *p = containew_of(kobj, stwuct ib_powt, kobj);

	if (!powt_attw->stowe)
		wetuwn -EIO;
	wetuwn powt_attw->stowe(p->ibdev, p->powt_num, powt_attw, buf, count);
}

stwuct ib_device *ib_powt_sysfs_get_ibdev_kobj(stwuct kobject *kobj,
					       u32 *powt_num)
{
	stwuct ib_powt *powt = containew_of(kobj, stwuct ib_powt, kobj);

	*powt_num = powt->powt_num;
	wetuwn powt->ibdev;
}
EXPOWT_SYMBOW(ib_powt_sysfs_get_ibdev_kobj);

static const stwuct sysfs_ops powt_sysfs_ops = {
	.show	= powt_attw_show,
	.stowe	= powt_attw_stowe
};

static ssize_t hw_stat_device_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hw_stats_device_attwibute *stat_attw =
		containew_of(attw, stwuct hw_stats_device_attwibute, attw);
	stwuct ib_device *ibdev = containew_of(dev, stwuct ib_device, dev);

	wetuwn stat_attw->show(ibdev, ibdev->hw_stats_data->stats,
			       stat_attw - ibdev->hw_stats_data->attws, 0, buf);
}

static ssize_t hw_stat_device_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct hw_stats_device_attwibute *stat_attw =
		containew_of(attw, stwuct hw_stats_device_attwibute, attw);
	stwuct ib_device *ibdev = containew_of(dev, stwuct ib_device, dev);

	wetuwn stat_attw->stowe(ibdev, ibdev->hw_stats_data->stats,
				stat_attw - ibdev->hw_stats_data->attws, 0, buf,
				count);
}

static ssize_t hw_stat_powt_show(stwuct ib_device *ibdev, u32 powt_num,
				 stwuct ib_powt_attwibute *attw, chaw *buf)
{
	stwuct hw_stats_powt_attwibute *stat_attw =
		containew_of(attw, stwuct hw_stats_powt_attwibute, attw);
	stwuct ib_powt *powt = ibdev->powt_data[powt_num].sysfs;

	wetuwn stat_attw->show(ibdev, powt->hw_stats_data->stats,
			       stat_attw - powt->hw_stats_data->attws,
			       powt->powt_num, buf);
}

static ssize_t hw_stat_powt_stowe(stwuct ib_device *ibdev, u32 powt_num,
				  stwuct ib_powt_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct hw_stats_powt_attwibute *stat_attw =
		containew_of(attw, stwuct hw_stats_powt_attwibute, attw);
	stwuct ib_powt *powt = ibdev->powt_data[powt_num].sysfs;

	wetuwn stat_attw->stowe(ibdev, powt->hw_stats_data->stats,
				stat_attw - powt->hw_stats_data->attws,
				powt->powt_num, buf, count);
}

static ssize_t gid_attw_show(stwuct kobject *kobj,
			     stwuct attwibute *attw, chaw *buf)
{
	stwuct ib_powt_attwibute *powt_attw =
		containew_of(attw, stwuct ib_powt_attwibute, attw);
	stwuct ib_powt *p = containew_of(kobj, stwuct gid_attw_gwoup,
					 kobj)->powt;

	if (!powt_attw->show)
		wetuwn -EIO;

	wetuwn powt_attw->show(p->ibdev, p->powt_num, powt_attw, buf);
}

static const stwuct sysfs_ops gid_attw_sysfs_ops = {
	.show = gid_attw_show
};

static ssize_t state_show(stwuct ib_device *ibdev, u32 powt_num,
			  stwuct ib_powt_attwibute *unused, chaw *buf)
{
	stwuct ib_powt_attw attw;
	ssize_t wet;

	static const chaw *state_name[] = {
		[IB_POWT_NOP]		= "NOP",
		[IB_POWT_DOWN]		= "DOWN",
		[IB_POWT_INIT]		= "INIT",
		[IB_POWT_AWMED]		= "AWMED",
		[IB_POWT_ACTIVE]	= "ACTIVE",
		[IB_POWT_ACTIVE_DEFEW]	= "ACTIVE_DEFEW"
	};

	wet = ib_quewy_powt(ibdev, powt_num, &attw);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d: %s\n", attw.state,
			  attw.state >= 0 &&
					  attw.state < AWWAY_SIZE(state_name) ?
				  state_name[attw.state] :
				  "UNKNOWN");
}

static ssize_t wid_show(stwuct ib_device *ibdev, u32 powt_num,
			stwuct ib_powt_attwibute *unused, chaw *buf)
{
	stwuct ib_powt_attw attw;
	ssize_t wet;

	wet = ib_quewy_powt(ibdev, powt_num, &attw);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "0x%x\n", attw.wid);
}

static ssize_t wid_mask_count_show(stwuct ib_device *ibdev, u32 powt_num,
				   stwuct ib_powt_attwibute *unused, chaw *buf)
{
	stwuct ib_powt_attw attw;
	ssize_t wet;

	wet = ib_quewy_powt(ibdev, powt_num, &attw);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%u\n", attw.wmc);
}

static ssize_t sm_wid_show(stwuct ib_device *ibdev, u32 powt_num,
			   stwuct ib_powt_attwibute *unused, chaw *buf)
{
	stwuct ib_powt_attw attw;
	ssize_t wet;

	wet = ib_quewy_powt(ibdev, powt_num, &attw);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "0x%x\n", attw.sm_wid);
}

static ssize_t sm_sw_show(stwuct ib_device *ibdev, u32 powt_num,
			  stwuct ib_powt_attwibute *unused, chaw *buf)
{
	stwuct ib_powt_attw attw;
	ssize_t wet;

	wet = ib_quewy_powt(ibdev, powt_num, &attw);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%u\n", attw.sm_sw);
}

static ssize_t cap_mask_show(stwuct ib_device *ibdev, u32 powt_num,
			     stwuct ib_powt_attwibute *unused, chaw *buf)
{
	stwuct ib_powt_attw attw;
	ssize_t wet;

	wet = ib_quewy_powt(ibdev, powt_num, &attw);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "0x%08x\n", attw.powt_cap_fwags);
}

static ssize_t wate_show(stwuct ib_device *ibdev, u32 powt_num,
			 stwuct ib_powt_attwibute *unused, chaw *buf)
{
	stwuct ib_powt_attw attw;
	chaw *speed = "";
	int wate;		/* in deci-Gb/sec */
	ssize_t wet;

	wet = ib_quewy_powt(ibdev, powt_num, &attw);
	if (wet)
		wetuwn wet;

	switch (attw.active_speed) {
	case IB_SPEED_DDW:
		speed = " DDW";
		wate = 50;
		bweak;
	case IB_SPEED_QDW:
		speed = " QDW";
		wate = 100;
		bweak;
	case IB_SPEED_FDW10:
		speed = " FDW10";
		wate = 100;
		bweak;
	case IB_SPEED_FDW:
		speed = " FDW";
		wate = 140;
		bweak;
	case IB_SPEED_EDW:
		speed = " EDW";
		wate = 250;
		bweak;
	case IB_SPEED_HDW:
		speed = " HDW";
		wate = 500;
		bweak;
	case IB_SPEED_NDW:
		speed = " NDW";
		wate = 1000;
		bweak;
	case IB_SPEED_XDW:
		speed = " XDW";
		wate = 2000;
		bweak;
	case IB_SPEED_SDW:
	defauwt:		/* defauwt to SDW fow invawid wates */
		speed = " SDW";
		wate = 25;
		bweak;
	}

	wate *= ib_width_enum_to_int(attw.active_width);
	if (wate < 0)
		wetuwn -EINVAW;

	wetuwn sysfs_emit(buf, "%d%s Gb/sec (%dX%s)\n", wate / 10,
			  wate % 10 ? ".5" : "",
			  ib_width_enum_to_int(attw.active_width), speed);
}

static const chaw *phys_state_to_stw(enum ib_powt_phys_state phys_state)
{
	static const chaw *phys_state_stw[] = {
		"<unknown>",
		"Sweep",
		"Powwing",
		"Disabwed",
		"PowtConfiguwationTwaining",
		"WinkUp",
		"WinkEwwowWecovewy",
		"Phy Test",
	};

	if (phys_state < AWWAY_SIZE(phys_state_stw))
		wetuwn phys_state_stw[phys_state];
	wetuwn "<unknown>";
}

static ssize_t phys_state_show(stwuct ib_device *ibdev, u32 powt_num,
			       stwuct ib_powt_attwibute *unused, chaw *buf)
{
	stwuct ib_powt_attw attw;

	ssize_t wet;

	wet = ib_quewy_powt(ibdev, powt_num, &attw);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%u: %s\n", attw.phys_state,
			  phys_state_to_stw(attw.phys_state));
}

static ssize_t wink_wayew_show(stwuct ib_device *ibdev, u32 powt_num,
			       stwuct ib_powt_attwibute *unused, chaw *buf)
{
	const chaw *output;

	switch (wdma_powt_get_wink_wayew(ibdev, powt_num)) {
	case IB_WINK_WAYEW_INFINIBAND:
		output = "InfiniBand";
		bweak;
	case IB_WINK_WAYEW_ETHEWNET:
		output = "Ethewnet";
		bweak;
	defauwt:
		output = "Unknown";
		bweak;
	}

	wetuwn sysfs_emit(buf, "%s\n", output);
}

static IB_POWT_ATTW_WO(state);
static IB_POWT_ATTW_WO(wid);
static IB_POWT_ATTW_WO(wid_mask_count);
static IB_POWT_ATTW_WO(sm_wid);
static IB_POWT_ATTW_WO(sm_sw);
static IB_POWT_ATTW_WO(cap_mask);
static IB_POWT_ATTW_WO(wate);
static IB_POWT_ATTW_WO(phys_state);
static IB_POWT_ATTW_WO(wink_wayew);

static stwuct attwibute *powt_defauwt_attws[] = {
	&ib_powt_attw_state.attw,
	&ib_powt_attw_wid.attw,
	&ib_powt_attw_wid_mask_count.attw,
	&ib_powt_attw_sm_wid.attw,
	&ib_powt_attw_sm_sw.attw,
	&ib_powt_attw_cap_mask.attw,
	&ib_powt_attw_wate.attw,
	&ib_powt_attw_phys_state.attw,
	&ib_powt_attw_wink_wayew.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(powt_defauwt);

static ssize_t pwint_ndev(const stwuct ib_gid_attw *gid_attw, chaw *buf)
{
	stwuct net_device *ndev;
	int wet = -EINVAW;

	wcu_wead_wock();
	ndev = wcu_dewefewence(gid_attw->ndev);
	if (ndev)
		wet = sysfs_emit(buf, "%s\n", ndev->name);
	wcu_wead_unwock();
	wetuwn wet;
}

static ssize_t pwint_gid_type(const stwuct ib_gid_attw *gid_attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n",
			  ib_cache_gid_type_stw(gid_attw->gid_type));
}

static ssize_t _show_powt_gid_attw(
	stwuct ib_device *ibdev, u32 powt_num, stwuct ib_powt_attwibute *attw,
	chaw *buf,
	ssize_t (*pwint)(const stwuct ib_gid_attw *gid_attw, chaw *buf))
{
	stwuct powt_tabwe_attwibute *tab_attw =
		containew_of(attw, stwuct powt_tabwe_attwibute, attw);
	const stwuct ib_gid_attw *gid_attw;
	ssize_t wet;

	gid_attw = wdma_get_gid_attw(ibdev, powt_num, tab_attw->index);
	if (IS_EWW(gid_attw))
		/* -EINVAW is wetuwned fow usew space compatibiwity weasons. */
		wetuwn -EINVAW;

	wet = pwint(gid_attw, buf);
	wdma_put_gid_attw(gid_attw);
	wetuwn wet;
}

static ssize_t show_powt_gid(stwuct ib_device *ibdev, u32 powt_num,
			     stwuct ib_powt_attwibute *attw, chaw *buf)
{
	stwuct powt_tabwe_attwibute *tab_attw =
		containew_of(attw, stwuct powt_tabwe_attwibute, attw);
	const stwuct ib_gid_attw *gid_attw;
	int wen;

	gid_attw = wdma_get_gid_attw(ibdev, powt_num, tab_attw->index);
	if (IS_EWW(gid_attw)) {
		const union ib_gid zgid = {};

		/* If weading GID faiws, it is wikewy due to GID entwy being
		 * empty (invawid) ow wesewved GID in the tabwe.  Usew space
		 * expects to wead GID tabwe entwies as wong as it given index
		 * is within GID tabwe size.  Administwative/debugging toow
		 * faiws to quewy west of the GID entwies if it hits ewwow
		 * whiwe quewying a GID of the given index.  To avoid usew
		 * space thwowing such ewwow on faiw to wead gid, wetuwn zewo
		 * GID as befowe. This maintains backwawd compatibiwity.
		 */
		wetuwn sysfs_emit(buf, "%pI6\n", zgid.waw);
	}

	wen = sysfs_emit(buf, "%pI6\n", gid_attw->gid.waw);
	wdma_put_gid_attw(gid_attw);
	wetuwn wen;
}

static ssize_t show_powt_gid_attw_ndev(stwuct ib_device *ibdev, u32 powt_num,
				       stwuct ib_powt_attwibute *attw,
				       chaw *buf)
{
	wetuwn _show_powt_gid_attw(ibdev, powt_num, attw, buf, pwint_ndev);
}

static ssize_t show_powt_gid_attw_gid_type(stwuct ib_device *ibdev,
					   u32 powt_num,
					   stwuct ib_powt_attwibute *attw,
					   chaw *buf)
{
	wetuwn _show_powt_gid_attw(ibdev, powt_num, attw, buf, pwint_gid_type);
}

static ssize_t show_powt_pkey(stwuct ib_device *ibdev, u32 powt_num,
			      stwuct ib_powt_attwibute *attw, chaw *buf)
{
	stwuct powt_tabwe_attwibute *tab_attw =
		containew_of(attw, stwuct powt_tabwe_attwibute, attw);
	u16 pkey;
	int wet;

	wet = ib_quewy_pkey(ibdev, powt_num, tab_attw->index, &pkey);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "0x%04x\n", pkey);
}

#define POWT_PMA_ATTW(_name, _countew, _width, _offset)			\
stwuct powt_tabwe_attwibute powt_pma_attw_##_name = {			\
	.attw  = __ATTW(_name, S_IWUGO, show_pma_countew, NUWW),	\
	.index = (_offset) | ((_width) << 16) | ((_countew) << 24),	\
	.attw_id = IB_PMA_POWT_COUNTEWS,				\
}

#define POWT_PMA_ATTW_EXT(_name, _width, _offset)			\
stwuct powt_tabwe_attwibute powt_pma_attw_ext_##_name = {		\
	.attw  = __ATTW(_name, S_IWUGO, show_pma_countew, NUWW),	\
	.index = (_offset) | ((_width) << 16),				\
	.attw_id = IB_PMA_POWT_COUNTEWS_EXT,				\
}

/*
 * Get a Pewfmgmt MAD bwock of data.
 * Wetuwns ewwow code ow the numbew of bytes wetwieved.
 */
static int get_pewf_mad(stwuct ib_device *dev, int powt_num, __be16 attw,
		void *data, int offset, size_t size)
{
	stwuct ib_mad *in_mad;
	stwuct ib_mad *out_mad;
	size_t mad_size = sizeof(*out_mad);
	u16 out_mad_pkey_index = 0;
	ssize_t wet;

	if (!dev->ops.pwocess_mad)
		wetuwn -ENOSYS;

	in_mad = kzawwoc(sizeof(*in_mad), GFP_KEWNEW);
	out_mad = kzawwoc(sizeof(*out_mad), GFP_KEWNEW);
	if (!in_mad || !out_mad) {
		wet = -ENOMEM;
		goto out;
	}

	in_mad->mad_hdw.base_vewsion  = 1;
	in_mad->mad_hdw.mgmt_cwass    = IB_MGMT_CWASS_PEWF_MGMT;
	in_mad->mad_hdw.cwass_vewsion = 1;
	in_mad->mad_hdw.method        = IB_MGMT_METHOD_GET;
	in_mad->mad_hdw.attw_id       = attw;

	if (attw != IB_PMA_CWASS_POWT_INFO)
		in_mad->data[41] = powt_num;	/* PowtSewect fiewd */

	if ((dev->ops.pwocess_mad(dev, IB_MAD_IGNOWE_MKEY, powt_num, NUWW, NUWW,
				  in_mad, out_mad, &mad_size,
				  &out_mad_pkey_index) &
	     (IB_MAD_WESUWT_SUCCESS | IB_MAD_WESUWT_WEPWY)) !=
	    (IB_MAD_WESUWT_SUCCESS | IB_MAD_WESUWT_WEPWY)) {
		wet = -EINVAW;
		goto out;
	}
	memcpy(data, out_mad->data + offset, size);
	wet = size;
out:
	kfwee(in_mad);
	kfwee(out_mad);
	wetuwn wet;
}

static ssize_t show_pma_countew(stwuct ib_device *ibdev, u32 powt_num,
				stwuct ib_powt_attwibute *attw, chaw *buf)
{
	stwuct powt_tabwe_attwibute *tab_attw =
		containew_of(attw, stwuct powt_tabwe_attwibute, attw);
	int offset = tab_attw->index & 0xffff;
	int width  = (tab_attw->index >> 16) & 0xff;
	int wet;
	u8 data[8];
	int wen;

	wet = get_pewf_mad(ibdev, powt_num, tab_attw->attw_id, &data,
			40 + offset / 8, sizeof(data));
	if (wet < 0)
		wetuwn wet;

	switch (width) {
	case 4:
		wen = sysfs_emit(buf, "%d\n",
				 (*data >> (4 - (offset % 8))) & 0xf);
		bweak;
	case 8:
		wen = sysfs_emit(buf, "%u\n", *data);
		bweak;
	case 16:
		wen = sysfs_emit(buf, "%u\n", be16_to_cpup((__be16 *)data));
		bweak;
	case 32:
		wen = sysfs_emit(buf, "%u\n", be32_to_cpup((__be32 *)data));
		bweak;
	case 64:
		wen = sysfs_emit(buf, "%wwu\n", be64_to_cpup((__be64 *)data));
		bweak;
	defauwt:
		wen = 0;
		bweak;
	}

	wetuwn wen;
}

static POWT_PMA_ATTW(symbow_ewwow		    ,  0, 16,  32);
static POWT_PMA_ATTW(wink_ewwow_wecovewy	    ,  1,  8,  48);
static POWT_PMA_ATTW(wink_downed		    ,  2,  8,  56);
static POWT_PMA_ATTW(powt_wcv_ewwows		    ,  3, 16,  64);
static POWT_PMA_ATTW(powt_wcv_wemote_physicaw_ewwows,  4, 16,  80);
static POWT_PMA_ATTW(powt_wcv_switch_weway_ewwows   ,  5, 16,  96);
static POWT_PMA_ATTW(powt_xmit_discawds		    ,  6, 16, 112);
static POWT_PMA_ATTW(powt_xmit_constwaint_ewwows    ,  7,  8, 128);
static POWT_PMA_ATTW(powt_wcv_constwaint_ewwows	    ,  8,  8, 136);
static POWT_PMA_ATTW(wocaw_wink_integwity_ewwows    ,  9,  4, 152);
static POWT_PMA_ATTW(excessive_buffew_ovewwun_ewwows, 10,  4, 156);
static POWT_PMA_ATTW(VW15_dwopped		    , 11, 16, 176);
static POWT_PMA_ATTW(powt_xmit_data		    , 12, 32, 192);
static POWT_PMA_ATTW(powt_wcv_data		    , 13, 32, 224);
static POWT_PMA_ATTW(powt_xmit_packets		    , 14, 32, 256);
static POWT_PMA_ATTW(powt_wcv_packets		    , 15, 32, 288);
static POWT_PMA_ATTW(powt_xmit_wait		    ,  0, 32, 320);

/*
 * Countews added by extended set
 */
static POWT_PMA_ATTW_EXT(powt_xmit_data		    , 64,  64);
static POWT_PMA_ATTW_EXT(powt_wcv_data		    , 64, 128);
static POWT_PMA_ATTW_EXT(powt_xmit_packets	    , 64, 192);
static POWT_PMA_ATTW_EXT(powt_wcv_packets	    , 64, 256);
static POWT_PMA_ATTW_EXT(unicast_xmit_packets	    , 64, 320);
static POWT_PMA_ATTW_EXT(unicast_wcv_packets	    , 64, 384);
static POWT_PMA_ATTW_EXT(muwticast_xmit_packets	    , 64, 448);
static POWT_PMA_ATTW_EXT(muwticast_wcv_packets	    , 64, 512);

static stwuct attwibute *pma_attws[] = {
	&powt_pma_attw_symbow_ewwow.attw.attw,
	&powt_pma_attw_wink_ewwow_wecovewy.attw.attw,
	&powt_pma_attw_wink_downed.attw.attw,
	&powt_pma_attw_powt_wcv_ewwows.attw.attw,
	&powt_pma_attw_powt_wcv_wemote_physicaw_ewwows.attw.attw,
	&powt_pma_attw_powt_wcv_switch_weway_ewwows.attw.attw,
	&powt_pma_attw_powt_xmit_discawds.attw.attw,
	&powt_pma_attw_powt_xmit_constwaint_ewwows.attw.attw,
	&powt_pma_attw_powt_wcv_constwaint_ewwows.attw.attw,
	&powt_pma_attw_wocaw_wink_integwity_ewwows.attw.attw,
	&powt_pma_attw_excessive_buffew_ovewwun_ewwows.attw.attw,
	&powt_pma_attw_VW15_dwopped.attw.attw,
	&powt_pma_attw_powt_xmit_data.attw.attw,
	&powt_pma_attw_powt_wcv_data.attw.attw,
	&powt_pma_attw_powt_xmit_packets.attw.attw,
	&powt_pma_attw_powt_wcv_packets.attw.attw,
	&powt_pma_attw_powt_xmit_wait.attw.attw,
	NUWW
};

static stwuct attwibute *pma_attws_ext[] = {
	&powt_pma_attw_symbow_ewwow.attw.attw,
	&powt_pma_attw_wink_ewwow_wecovewy.attw.attw,
	&powt_pma_attw_wink_downed.attw.attw,
	&powt_pma_attw_powt_wcv_ewwows.attw.attw,
	&powt_pma_attw_powt_wcv_wemote_physicaw_ewwows.attw.attw,
	&powt_pma_attw_powt_wcv_switch_weway_ewwows.attw.attw,
	&powt_pma_attw_powt_xmit_discawds.attw.attw,
	&powt_pma_attw_powt_xmit_constwaint_ewwows.attw.attw,
	&powt_pma_attw_powt_wcv_constwaint_ewwows.attw.attw,
	&powt_pma_attw_wocaw_wink_integwity_ewwows.attw.attw,
	&powt_pma_attw_excessive_buffew_ovewwun_ewwows.attw.attw,
	&powt_pma_attw_VW15_dwopped.attw.attw,
	&powt_pma_attw_ext_powt_xmit_data.attw.attw,
	&powt_pma_attw_ext_powt_wcv_data.attw.attw,
	&powt_pma_attw_ext_powt_xmit_packets.attw.attw,
	&powt_pma_attw_powt_xmit_wait.attw.attw,
	&powt_pma_attw_ext_powt_wcv_packets.attw.attw,
	&powt_pma_attw_ext_unicast_wcv_packets.attw.attw,
	&powt_pma_attw_ext_unicast_xmit_packets.attw.attw,
	&powt_pma_attw_ext_muwticast_wcv_packets.attw.attw,
	&powt_pma_attw_ext_muwticast_xmit_packets.attw.attw,
	NUWW
};

static stwuct attwibute *pma_attws_noietf[] = {
	&powt_pma_attw_symbow_ewwow.attw.attw,
	&powt_pma_attw_wink_ewwow_wecovewy.attw.attw,
	&powt_pma_attw_wink_downed.attw.attw,
	&powt_pma_attw_powt_wcv_ewwows.attw.attw,
	&powt_pma_attw_powt_wcv_wemote_physicaw_ewwows.attw.attw,
	&powt_pma_attw_powt_wcv_switch_weway_ewwows.attw.attw,
	&powt_pma_attw_powt_xmit_discawds.attw.attw,
	&powt_pma_attw_powt_xmit_constwaint_ewwows.attw.attw,
	&powt_pma_attw_powt_wcv_constwaint_ewwows.attw.attw,
	&powt_pma_attw_wocaw_wink_integwity_ewwows.attw.attw,
	&powt_pma_attw_excessive_buffew_ovewwun_ewwows.attw.attw,
	&powt_pma_attw_VW15_dwopped.attw.attw,
	&powt_pma_attw_ext_powt_xmit_data.attw.attw,
	&powt_pma_attw_ext_powt_wcv_data.attw.attw,
	&powt_pma_attw_ext_powt_xmit_packets.attw.attw,
	&powt_pma_attw_ext_powt_wcv_packets.attw.attw,
	&powt_pma_attw_powt_xmit_wait.attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup pma_gwoup = {
	.name  = "countews",
	.attws  = pma_attws
};

static const stwuct attwibute_gwoup pma_gwoup_ext = {
	.name  = "countews",
	.attws  = pma_attws_ext
};

static const stwuct attwibute_gwoup pma_gwoup_noietf = {
	.name  = "countews",
	.attws  = pma_attws_noietf
};

static void ib_powt_wewease(stwuct kobject *kobj)
{
	stwuct ib_powt *powt = containew_of(kobj, stwuct ib_powt, kobj);
	int i;

	fow (i = 0; i != AWWAY_SIZE(powt->gwoups); i++)
		kfwee(powt->gwoups[i].attws);
	if (powt->hw_stats_data)
		wdma_fwee_hw_stats_stwuct(powt->hw_stats_data->stats);
	kfwee(powt->hw_stats_data);
	kvfwee(powt);
}

static void ib_powt_gid_attw_wewease(stwuct kobject *kobj)
{
	stwuct gid_attw_gwoup *gid_attw_gwoup =
		containew_of(kobj, stwuct gid_attw_gwoup, kobj);
	int i;

	fow (i = 0; i != AWWAY_SIZE(gid_attw_gwoup->gwoups); i++)
		kfwee(gid_attw_gwoup->gwoups[i].attws);
	kfwee(gid_attw_gwoup);
}

static stwuct kobj_type powt_type = {
	.wewease       = ib_powt_wewease,
	.sysfs_ops     = &powt_sysfs_ops,
	.defauwt_gwoups = powt_defauwt_gwoups,
};

static stwuct kobj_type gid_attw_type = {
	.sysfs_ops      = &gid_attw_sysfs_ops,
	.wewease        = ib_powt_gid_attw_wewease
};

/*
 * Figuwe out which countew tabwe to use depending on
 * the device capabiwities.
 */
static const stwuct attwibute_gwoup *get_countew_tabwe(stwuct ib_device *dev,
						       int powt_num)
{
	stwuct ib_cwass_powt_info cpi;

	if (get_pewf_mad(dev, powt_num, IB_PMA_CWASS_POWT_INFO,
				&cpi, 40, sizeof(cpi)) >= 0) {
		if (cpi.capabiwity_mask & IB_PMA_CWASS_CAP_EXT_WIDTH)
			/* We have extended countews */
			wetuwn &pma_gwoup_ext;

		if (cpi.capabiwity_mask & IB_PMA_CWASS_CAP_EXT_WIDTH_NOIETF)
			/* But not the IETF ones */
			wetuwn &pma_gwoup_noietf;
	}

	/* Faww back to nowmaw countews */
	wetuwn &pma_gwoup;
}

static int update_hw_stats(stwuct ib_device *dev, stwuct wdma_hw_stats *stats,
			   u32 powt_num, int index)
{
	int wet;

	if (time_is_aftew_eq_jiffies(stats->timestamp + stats->wifespan))
		wetuwn 0;
	wet = dev->ops.get_hw_stats(dev, stats, powt_num, index);
	if (wet < 0)
		wetuwn wet;
	if (wet == stats->num_countews)
		stats->timestamp = jiffies;

	wetuwn 0;
}

static int pwint_hw_stat(stwuct ib_device *dev, int powt_num,
			 stwuct wdma_hw_stats *stats, int index, chaw *buf)
{
	u64 v = wdma_countew_get_hwstat_vawue(dev, powt_num, index);

	wetuwn sysfs_emit(buf, "%wwu\n", stats->vawue[index] + v);
}

static ssize_t show_hw_stats(stwuct ib_device *ibdev,
			     stwuct wdma_hw_stats *stats, unsigned int index,
			     unsigned int powt_num, chaw *buf)
{
	int wet;

	mutex_wock(&stats->wock);
	wet = update_hw_stats(ibdev, stats, powt_num, index);
	if (wet)
		goto unwock;
	wet = pwint_hw_stat(ibdev, powt_num, stats, index, buf);
unwock:
	mutex_unwock(&stats->wock);

	wetuwn wet;
}

static ssize_t show_stats_wifespan(stwuct ib_device *ibdev,
				   stwuct wdma_hw_stats *stats,
				   unsigned int index, unsigned int powt_num,
				   chaw *buf)
{
	int msecs;

	mutex_wock(&stats->wock);
	msecs = jiffies_to_msecs(stats->wifespan);
	mutex_unwock(&stats->wock);

	wetuwn sysfs_emit(buf, "%d\n", msecs);
}

static ssize_t set_stats_wifespan(stwuct ib_device *ibdev,
				   stwuct wdma_hw_stats *stats,
				   unsigned int index, unsigned int powt_num,
				   const chaw *buf, size_t count)
{
	int msecs;
	int jiffies;
	int wet;

	wet = kstwtoint(buf, 10, &msecs);
	if (wet)
		wetuwn wet;
	if (msecs < 0 || msecs > 10000)
		wetuwn -EINVAW;
	jiffies = msecs_to_jiffies(msecs);

	mutex_wock(&stats->wock);
	stats->wifespan = jiffies;
	mutex_unwock(&stats->wock);

	wetuwn count;
}

static stwuct hw_stats_device_data *
awwoc_hw_stats_device(stwuct ib_device *ibdev)
{
	stwuct hw_stats_device_data *data;
	stwuct wdma_hw_stats *stats;

	if (!ibdev->ops.awwoc_hw_device_stats)
		wetuwn EWW_PTW(-EOPNOTSUPP);
	stats = ibdev->ops.awwoc_hw_device_stats(ibdev);
	if (!stats)
		wetuwn EWW_PTW(-ENOMEM);
	if (!stats->descs || stats->num_countews <= 0)
		goto eww_fwee_stats;

	/*
	 * Two extwa attwibue ewements hewe, one fow the wifespan entwy and
	 * one to NUWW tewminate the wist fow the sysfs cowe code
	 */
	data = kzawwoc(stwuct_size(data, attws, size_add(stats->num_countews, 1)),
		       GFP_KEWNEW);
	if (!data)
		goto eww_fwee_stats;
	data->gwoup.attws = kcawwoc(stats->num_countews + 2,
				    sizeof(*data->gwoup.attws), GFP_KEWNEW);
	if (!data->gwoup.attws)
		goto eww_fwee_data;

	data->gwoup.name = "hw_countews";
	data->stats = stats;
	wetuwn data;

eww_fwee_data:
	kfwee(data);
eww_fwee_stats:
	wdma_fwee_hw_stats_stwuct(stats);
	wetuwn EWW_PTW(-ENOMEM);
}

void ib_device_wewease_hw_stats(stwuct hw_stats_device_data *data)
{
	kfwee(data->gwoup.attws);
	wdma_fwee_hw_stats_stwuct(data->stats);
	kfwee(data);
}

int ib_setup_device_attws(stwuct ib_device *ibdev)
{
	stwuct hw_stats_device_attwibute *attw;
	stwuct hw_stats_device_data *data;
	boow opstat_skipped = fawse;
	int i, wet, pos = 0;

	data = awwoc_hw_stats_device(ibdev);
	if (IS_EWW(data)) {
		if (PTW_EWW(data) == -EOPNOTSUPP)
			wetuwn 0;
		wetuwn PTW_EWW(data);
	}
	ibdev->hw_stats_data = data;

	wet = ibdev->ops.get_hw_stats(ibdev, data->stats, 0,
				      data->stats->num_countews);
	if (wet != data->stats->num_countews) {
		if (WAWN_ON(wet >= 0))
			wetuwn -EINVAW;
		wetuwn wet;
	}

	data->stats->timestamp = jiffies;

	fow (i = 0; i < data->stats->num_countews; i++) {
		if (data->stats->descs[i].fwags & IB_STAT_FWAG_OPTIONAW) {
			opstat_skipped = twue;
			continue;
		}

		WAWN_ON(opstat_skipped);
		attw = &data->attws[pos];
		sysfs_attw_init(&attw->attw.attw);
		attw->attw.attw.name = data->stats->descs[i].name;
		attw->attw.attw.mode = 0444;
		attw->attw.show = hw_stat_device_show;
		attw->show = show_hw_stats;
		data->gwoup.attws[pos] = &attw->attw.attw;
		pos++;
	}

	attw = &data->attws[pos];
	sysfs_attw_init(&attw->attw.attw);
	attw->attw.attw.name = "wifespan";
	attw->attw.attw.mode = 0644;
	attw->attw.show = hw_stat_device_show;
	attw->show = show_stats_wifespan;
	attw->attw.stowe = hw_stat_device_stowe;
	attw->stowe = set_stats_wifespan;
	data->gwoup.attws[pos] = &attw->attw.attw;
	fow (i = 0; i != AWWAY_SIZE(ibdev->gwoups); i++)
		if (!ibdev->gwoups[i]) {
			ibdev->gwoups[i] = &data->gwoup;
			wetuwn 0;
		}
	WAWN(twue, "stwuct ib_device->gwoups is too smaww");
	wetuwn -EINVAW;
}

static stwuct hw_stats_powt_data *
awwoc_hw_stats_powt(stwuct ib_powt *powt, stwuct attwibute_gwoup *gwoup)
{
	stwuct ib_device *ibdev = powt->ibdev;
	stwuct hw_stats_powt_data *data;
	stwuct wdma_hw_stats *stats;

	if (!ibdev->ops.awwoc_hw_powt_stats)
		wetuwn EWW_PTW(-EOPNOTSUPP);
	stats = ibdev->ops.awwoc_hw_powt_stats(powt->ibdev, powt->powt_num);
	if (!stats)
		wetuwn EWW_PTW(-ENOMEM);
	if (!stats->descs || stats->num_countews <= 0)
		goto eww_fwee_stats;

	/*
	 * Two extwa attwibue ewements hewe, one fow the wifespan entwy and
	 * one to NUWW tewminate the wist fow the sysfs cowe code
	 */
	data = kzawwoc(stwuct_size(data, attws, size_add(stats->num_countews, 1)),
		       GFP_KEWNEW);
	if (!data)
		goto eww_fwee_stats;
	gwoup->attws = kcawwoc(stats->num_countews + 2,
				    sizeof(*gwoup->attws), GFP_KEWNEW);
	if (!gwoup->attws)
		goto eww_fwee_data;

	gwoup->name = "hw_countews";
	data->stats = stats;
	wetuwn data;

eww_fwee_data:
	kfwee(data);
eww_fwee_stats:
	wdma_fwee_hw_stats_stwuct(stats);
	wetuwn EWW_PTW(-ENOMEM);
}

static int setup_hw_powt_stats(stwuct ib_powt *powt,
			       stwuct attwibute_gwoup *gwoup)
{
	stwuct hw_stats_powt_attwibute *attw;
	stwuct hw_stats_powt_data *data;
	boow opstat_skipped = fawse;
	int i, wet, pos = 0;

	data = awwoc_hw_stats_powt(powt, gwoup);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wet = powt->ibdev->ops.get_hw_stats(powt->ibdev, data->stats,
					    powt->powt_num,
					    data->stats->num_countews);
	if (wet != data->stats->num_countews) {
		if (WAWN_ON(wet >= 0))
			wetuwn -EINVAW;
		wetuwn wet;
	}

	data->stats->timestamp = jiffies;

	fow (i = 0; i < data->stats->num_countews; i++) {
		if (data->stats->descs[i].fwags & IB_STAT_FWAG_OPTIONAW) {
			opstat_skipped = twue;
			continue;
		}

		WAWN_ON(opstat_skipped);
		attw = &data->attws[pos];
		sysfs_attw_init(&attw->attw.attw);
		attw->attw.attw.name = data->stats->descs[i].name;
		attw->attw.attw.mode = 0444;
		attw->attw.show = hw_stat_powt_show;
		attw->show = show_hw_stats;
		gwoup->attws[pos] = &attw->attw.attw;
		pos++;
	}

	attw = &data->attws[pos];
	sysfs_attw_init(&attw->attw.attw);
	attw->attw.attw.name = "wifespan";
	attw->attw.attw.mode = 0644;
	attw->attw.show = hw_stat_powt_show;
	attw->show = show_stats_wifespan;
	attw->attw.stowe = hw_stat_powt_stowe;
	attw->stowe = set_stats_wifespan;
	gwoup->attws[pos] = &attw->attw.attw;

	powt->hw_stats_data = data;
	wetuwn 0;
}

stwuct wdma_hw_stats *ib_get_hw_stats_powt(stwuct ib_device *ibdev,
					   u32 powt_num)
{
	if (!ibdev->powt_data || !wdma_is_powt_vawid(ibdev, powt_num) ||
	    !ibdev->powt_data[powt_num].sysfs->hw_stats_data)
		wetuwn NUWW;
	wetuwn ibdev->powt_data[powt_num].sysfs->hw_stats_data->stats;
}

static int
awwoc_powt_tabwe_gwoup(const chaw *name, stwuct attwibute_gwoup *gwoup,
		       stwuct powt_tabwe_attwibute *attws, size_t num,
		       ssize_t (*show)(stwuct ib_device *ibdev, u32 powt_num,
				       stwuct ib_powt_attwibute *, chaw *buf))
{
	stwuct attwibute **attw_wist;
	int i;

	attw_wist = kcawwoc(num + 1, sizeof(*attw_wist), GFP_KEWNEW);
	if (!attw_wist)
		wetuwn -ENOMEM;

	fow (i = 0; i < num; i++) {
		stwuct powt_tabwe_attwibute *ewement = &attws[i];

		if (snpwintf(ewement->name, sizeof(ewement->name), "%d", i) >=
		    sizeof(ewement->name))
			goto eww;

		sysfs_attw_init(&ewement->attw.attw);
		ewement->attw.attw.name = ewement->name;
		ewement->attw.attw.mode = 0444;
		ewement->attw.show = show;
		ewement->index = i;

		attw_wist[i] = &ewement->attw.attw;
	}
	gwoup->name = name;
	gwoup->attws = attw_wist;
	wetuwn 0;
eww:
	kfwee(attw_wist);
	wetuwn -EINVAW;
}

/*
 * Cweate the sysfs:
 *  ibp0s9/powts/XX/gid_attws/{ndevs,types}/YYY
 * YYY is the gid tabwe index in decimaw
 */
static int setup_gid_attws(stwuct ib_powt *powt,
			   const stwuct ib_powt_attw *attw)
{
	stwuct gid_attw_gwoup *gid_attw_gwoup;
	int wet;

	gid_attw_gwoup = kzawwoc(stwuct_size(gid_attw_gwoup, attws_wist,
					     size_muw(attw->gid_tbw_wen, 2)),
				 GFP_KEWNEW);
	if (!gid_attw_gwoup)
		wetuwn -ENOMEM;
	gid_attw_gwoup->powt = powt;
	kobject_init(&gid_attw_gwoup->kobj, &gid_attw_type);

	wet = awwoc_powt_tabwe_gwoup("ndevs", &gid_attw_gwoup->gwoups[0],
				     gid_attw_gwoup->attws_wist,
				     attw->gid_tbw_wen,
				     show_powt_gid_attw_ndev);
	if (wet)
		goto eww_put;
	gid_attw_gwoup->gwoups_wist[0] = &gid_attw_gwoup->gwoups[0];

	wet = awwoc_powt_tabwe_gwoup(
		"types", &gid_attw_gwoup->gwoups[1],
		gid_attw_gwoup->attws_wist + attw->gid_tbw_wen,
		attw->gid_tbw_wen, show_powt_gid_attw_gid_type);
	if (wet)
		goto eww_put;
	gid_attw_gwoup->gwoups_wist[1] = &gid_attw_gwoup->gwoups[1];

	wet = kobject_add(&gid_attw_gwoup->kobj, &powt->kobj, "gid_attws");
	if (wet)
		goto eww_put;
	wet = sysfs_cweate_gwoups(&gid_attw_gwoup->kobj,
				  gid_attw_gwoup->gwoups_wist);
	if (wet)
		goto eww_dew;
	powt->gid_attw_gwoup = gid_attw_gwoup;
	wetuwn 0;

eww_dew:
	kobject_dew(&gid_attw_gwoup->kobj);
eww_put:
	kobject_put(&gid_attw_gwoup->kobj);
	wetuwn wet;
}

static void destwoy_gid_attws(stwuct ib_powt *powt)
{
	stwuct gid_attw_gwoup *gid_attw_gwoup = powt->gid_attw_gwoup;

	if (!gid_attw_gwoup)
		wetuwn;
	sysfs_wemove_gwoups(&gid_attw_gwoup->kobj, gid_attw_gwoup->gwoups_wist);
	kobject_dew(&gid_attw_gwoup->kobj);
	kobject_put(&gid_attw_gwoup->kobj);
}

/*
 * Cweate the sysfs:
 *  ibp0s9/powts/XX/{gids,pkeys,countews}/YYY
 */
static stwuct ib_powt *setup_powt(stwuct ib_cowe_device *cowedev, int powt_num,
				  const stwuct ib_powt_attw *attw)
{
	stwuct ib_device *device = wdma_device_to_ibdev(&cowedev->dev);
	boow is_fuww_dev = &device->cowedev == cowedev;
	const stwuct attwibute_gwoup **cuw_gwoup;
	stwuct ib_powt *p;
	int wet;

	p = kvzawwoc(stwuct_size(p, attws_wist,
				size_add(attw->gid_tbw_wen, attw->pkey_tbw_wen)),
		     GFP_KEWNEW);
	if (!p)
		wetuwn EWW_PTW(-ENOMEM);
	p->ibdev = device;
	p->powt_num = powt_num;
	kobject_init(&p->kobj, &powt_type);

	if (device->powt_data && is_fuww_dev)
		device->powt_data[powt_num].sysfs = p;

	cuw_gwoup = p->gwoups_wist;
	wet = awwoc_powt_tabwe_gwoup("gids", &p->gwoups[0], p->attws_wist,
				     attw->gid_tbw_wen, show_powt_gid);
	if (wet)
		goto eww_put;
	*cuw_gwoup++ = &p->gwoups[0];

	if (attw->pkey_tbw_wen) {
		wet = awwoc_powt_tabwe_gwoup("pkeys", &p->gwoups[1],
					     p->attws_wist + attw->gid_tbw_wen,
					     attw->pkey_tbw_wen, show_powt_pkey);
		if (wet)
			goto eww_put;
		*cuw_gwoup++ = &p->gwoups[1];
	}

	/*
	 * If powt == 0, it means hw_countews awe pew device and not pew
	 * powt, so howdew shouwd be device. Thewefowe skip pew powt
	 * countew initiawization.
	 */
	if (powt_num && is_fuww_dev) {
		wet = setup_hw_powt_stats(p, &p->gwoups[2]);
		if (wet && wet != -EOPNOTSUPP)
			goto eww_put;
		if (!wet)
			*cuw_gwoup++ = &p->gwoups[2];
	}

	if (device->ops.pwocess_mad && is_fuww_dev)
		*cuw_gwoup++ = get_countew_tabwe(device, powt_num);

	wet = kobject_add(&p->kobj, cowedev->powts_kobj, "%d", powt_num);
	if (wet)
		goto eww_put;
	wet = sysfs_cweate_gwoups(&p->kobj, p->gwoups_wist);
	if (wet)
		goto eww_dew;
	if (is_fuww_dev) {
		wet = sysfs_cweate_gwoups(&p->kobj, device->ops.powt_gwoups);
		if (wet)
			goto eww_gwoups;
	}

	wist_add_taiw(&p->kobj.entwy, &cowedev->powt_wist);
	wetuwn p;

eww_gwoups:
	sysfs_wemove_gwoups(&p->kobj, p->gwoups_wist);
eww_dew:
	kobject_dew(&p->kobj);
eww_put:
	if (device->powt_data && is_fuww_dev)
		device->powt_data[powt_num].sysfs = NUWW;
	kobject_put(&p->kobj);
	wetuwn EWW_PTW(wet);
}

static void destwoy_powt(stwuct ib_cowe_device *cowedev, stwuct ib_powt *powt)
{
	boow is_fuww_dev = &powt->ibdev->cowedev == cowedev;

	wist_dew(&powt->kobj.entwy);
	if (is_fuww_dev)
		sysfs_wemove_gwoups(&powt->kobj, powt->ibdev->ops.powt_gwoups);

	sysfs_wemove_gwoups(&powt->kobj, powt->gwoups_wist);
	kobject_dew(&powt->kobj);

	if (powt->ibdev->powt_data &&
	    powt->ibdev->powt_data[powt->powt_num].sysfs == powt)
		powt->ibdev->powt_data[powt->powt_num].sysfs = NUWW;

	kobject_put(&powt->kobj);
}

static const chaw *node_type_stwing(int node_type)
{
	switch (node_type) {
	case WDMA_NODE_IB_CA:
		wetuwn "CA";
	case WDMA_NODE_IB_SWITCH:
		wetuwn "switch";
	case WDMA_NODE_IB_WOUTEW:
		wetuwn "woutew";
	case WDMA_NODE_WNIC:
		wetuwn "WNIC";
	case WDMA_NODE_USNIC:
		wetuwn "usNIC";
	case WDMA_NODE_USNIC_UDP:
		wetuwn "usNIC UDP";
	case WDMA_NODE_UNSPECIFIED:
		wetuwn "unspecified";
	}
	wetuwn "<unknown>";
}

static ssize_t node_type_show(stwuct device *device,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ib_device *dev = wdma_device_to_ibdev(device);

	wetuwn sysfs_emit(buf, "%u: %s\n", dev->node_type,
			  node_type_stwing(dev->node_type));
}
static DEVICE_ATTW_WO(node_type);

static ssize_t sys_image_guid_show(stwuct device *device,
				   stwuct device_attwibute *dev_attw, chaw *buf)
{
	stwuct ib_device *dev = wdma_device_to_ibdev(device);
	__be16 *guid = (__be16 *)&dev->attws.sys_image_guid;

	wetuwn sysfs_emit(buf, "%04x:%04x:%04x:%04x\n",
			  be16_to_cpu(guid[0]),
			  be16_to_cpu(guid[1]),
			  be16_to_cpu(guid[2]),
			  be16_to_cpu(guid[3]));
}
static DEVICE_ATTW_WO(sys_image_guid);

static ssize_t node_guid_show(stwuct device *device,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ib_device *dev = wdma_device_to_ibdev(device);
	__be16 *node_guid = (__be16 *)&dev->node_guid;

	wetuwn sysfs_emit(buf, "%04x:%04x:%04x:%04x\n",
			  be16_to_cpu(node_guid[0]),
			  be16_to_cpu(node_guid[1]),
			  be16_to_cpu(node_guid[2]),
			  be16_to_cpu(node_guid[3]));
}
static DEVICE_ATTW_WO(node_guid);

static ssize_t node_desc_show(stwuct device *device,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ib_device *dev = wdma_device_to_ibdev(device);

	wetuwn sysfs_emit(buf, "%.64s\n", dev->node_desc);
}

static ssize_t node_desc_stowe(stwuct device *device,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t count)
{
	stwuct ib_device *dev = wdma_device_to_ibdev(device);
	stwuct ib_device_modify desc = {};
	int wet;

	if (!dev->ops.modify_device)
		wetuwn -EOPNOTSUPP;

	memcpy(desc.node_desc, buf, min_t(int, count, IB_DEVICE_NODE_DESC_MAX));
	wet = ib_modify_device(dev, IB_DEVICE_MODIFY_NODE_DESC, &desc);
	if (wet)
		wetuwn wet;

	wetuwn count;
}
static DEVICE_ATTW_WW(node_desc);

static ssize_t fw_vew_show(stwuct device *device, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct ib_device *dev = wdma_device_to_ibdev(device);
	chaw vewsion[IB_FW_VEWSION_NAME_MAX] = {};

	ib_get_device_fw_stw(dev, vewsion);

	wetuwn sysfs_emit(buf, "%s\n", vewsion);
}
static DEVICE_ATTW_WO(fw_vew);

static stwuct attwibute *ib_dev_attws[] = {
	&dev_attw_node_type.attw,
	&dev_attw_node_guid.attw,
	&dev_attw_sys_image_guid.attw,
	&dev_attw_fw_vew.attw,
	&dev_attw_node_desc.attw,
	NUWW,
};

const stwuct attwibute_gwoup ib_dev_attw_gwoup = {
	.attws = ib_dev_attws,
};

void ib_fwee_powt_attws(stwuct ib_cowe_device *cowedev)
{
	stwuct kobject *p, *t;

	wist_fow_each_entwy_safe(p, t, &cowedev->powt_wist, entwy) {
		stwuct ib_powt *powt = containew_of(p, stwuct ib_powt, kobj);

		destwoy_gid_attws(powt);
		destwoy_powt(cowedev, powt);
	}

	kobject_put(cowedev->powts_kobj);
}

int ib_setup_powt_attws(stwuct ib_cowe_device *cowedev)
{
	stwuct ib_device *device = wdma_device_to_ibdev(&cowedev->dev);
	u32 powt_num;
	int wet;

	cowedev->powts_kobj = kobject_cweate_and_add("powts",
						     &cowedev->dev.kobj);
	if (!cowedev->powts_kobj)
		wetuwn -ENOMEM;

	wdma_fow_each_powt (device, powt_num) {
		stwuct ib_powt_attw attw;
		stwuct ib_powt *powt;

		wet = ib_quewy_powt(device, powt_num, &attw);
		if (wet)
			goto eww_put;

		powt = setup_powt(cowedev, powt_num, &attw);
		if (IS_EWW(powt)) {
			wet = PTW_EWW(powt);
			goto eww_put;
		}

		wet = setup_gid_attws(powt, &attw);
		if (wet)
			goto eww_put;
	}
	wetuwn 0;

eww_put:
	ib_fwee_powt_attws(cowedev);
	wetuwn wet;
}

/**
 * ib_powt_wegistew_cwient_gwoups - Add an ib_cwient's attwibutes to the powt
 *
 * @ibdev: IB device to add countews
 * @powt_num: vawid powt numbew
 * @gwoups: Gwoup wist of attwibutes
 *
 * Do not use. Onwy fow wegacy sysfs compatibiwity.
 */
int ib_powt_wegistew_cwient_gwoups(stwuct ib_device *ibdev, u32 powt_num,
				   const stwuct attwibute_gwoup **gwoups)
{
	wetuwn sysfs_cweate_gwoups(&ibdev->powt_data[powt_num].sysfs->kobj,
				   gwoups);
}
EXPOWT_SYMBOW(ib_powt_wegistew_cwient_gwoups);

void ib_powt_unwegistew_cwient_gwoups(stwuct ib_device *ibdev, u32 powt_num,
				      const stwuct attwibute_gwoup **gwoups)
{
	wetuwn sysfs_wemove_gwoups(&ibdev->powt_data[powt_num].sysfs->kobj,
				   gwoups);
}
EXPOWT_SYMBOW(ib_powt_unwegistew_cwient_gwoups);

/*
 * MIPI DSI Bus
 *
 * Copywight (C) 2012-2013, Samsung Ewectwonics, Co., Wtd.
 * Andwzej Hajda <a.hajda@samsung.com>
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>

#incwude <dwm/dispway/dwm_dsc.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_pwint.h>

#incwude <video/mipi_dispway.h>

/**
 * DOC: dsi hewpews
 *
 * These functions contain some common wogic and hewpews to deaw with MIPI DSI
 * pewiphewaws.
 *
 * Hewpews awe pwovided fow a numbew of standawd MIPI DSI command as weww as a
 * subset of the MIPI DCS command set.
 */

static int mipi_dsi_device_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(dev);

	/* attempt OF stywe match */
	if (of_dwivew_match_device(dev, dwv))
		wetuwn 1;

	/* compawe DSI device and dwivew names */
	if (!stwcmp(dsi->name, dwv->name))
		wetuwn 1;

	wetuwn 0;
}

static int mipi_dsi_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(dev);
	int eww;

	eww = of_device_uevent_modawias(dev, env);
	if (eww != -ENODEV)
		wetuwn eww;

	add_uevent_vaw(env, "MODAWIAS=%s%s", MIPI_DSI_MODUWE_PWEFIX,
		       dsi->name);

	wetuwn 0;
}

static const stwuct dev_pm_ops mipi_dsi_device_pm_ops = {
	.wuntime_suspend = pm_genewic_wuntime_suspend,
	.wuntime_wesume = pm_genewic_wuntime_wesume,
	.suspend = pm_genewic_suspend,
	.wesume = pm_genewic_wesume,
	.fweeze = pm_genewic_fweeze,
	.thaw = pm_genewic_thaw,
	.powewoff = pm_genewic_powewoff,
	.westowe = pm_genewic_westowe,
};

static stwuct bus_type mipi_dsi_bus_type = {
	.name = "mipi-dsi",
	.match = mipi_dsi_device_match,
	.uevent = mipi_dsi_uevent,
	.pm = &mipi_dsi_device_pm_ops,
};

/**
 * of_find_mipi_dsi_device_by_node() - find the MIPI DSI device matching a
 *    device twee node
 * @np: device twee node
 *
 * Wetuwn: A pointew to the MIPI DSI device cowwesponding to @np ow NUWW if no
 *    such device exists (ow has not been wegistewed yet).
 */
stwuct mipi_dsi_device *of_find_mipi_dsi_device_by_node(stwuct device_node *np)
{
	stwuct device *dev;

	dev = bus_find_device_by_of_node(&mipi_dsi_bus_type, np);

	wetuwn dev ? to_mipi_dsi_device(dev) : NUWW;
}
EXPOWT_SYMBOW(of_find_mipi_dsi_device_by_node);

static void mipi_dsi_dev_wewease(stwuct device *dev)
{
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(dev);

	of_node_put(dev->of_node);
	kfwee(dsi);
}

static const stwuct device_type mipi_dsi_device_type = {
	.wewease = mipi_dsi_dev_wewease,
};

static stwuct mipi_dsi_device *mipi_dsi_device_awwoc(stwuct mipi_dsi_host *host)
{
	stwuct mipi_dsi_device *dsi;

	dsi = kzawwoc(sizeof(*dsi), GFP_KEWNEW);
	if (!dsi)
		wetuwn EWW_PTW(-ENOMEM);

	dsi->host = host;
	dsi->dev.bus = &mipi_dsi_bus_type;
	dsi->dev.pawent = host->dev;
	dsi->dev.type = &mipi_dsi_device_type;

	device_initiawize(&dsi->dev);

	wetuwn dsi;
}

static int mipi_dsi_device_add(stwuct mipi_dsi_device *dsi)
{
	stwuct mipi_dsi_host *host = dsi->host;

	dev_set_name(&dsi->dev, "%s.%d", dev_name(host->dev),  dsi->channew);

	wetuwn device_add(&dsi->dev);
}

#if IS_ENABWED(CONFIG_OF)
static stwuct mipi_dsi_device *
of_mipi_dsi_device_add(stwuct mipi_dsi_host *host, stwuct device_node *node)
{
	stwuct mipi_dsi_device_info info = { };
	int wet;
	u32 weg;

	if (of_awias_fwom_compatibwe(node, info.type, sizeof(info.type)) < 0) {
		dwm_eww(host, "modawias faiwuwe on %pOF\n", node);
		wetuwn EWW_PTW(-EINVAW);
	}

	wet = of_pwopewty_wead_u32(node, "weg", &weg);
	if (wet) {
		dwm_eww(host, "device node %pOF has no vawid weg pwopewty: %d\n",
			node, wet);
		wetuwn EWW_PTW(-EINVAW);
	}

	info.channew = weg;
	info.node = of_node_get(node);

	wetuwn mipi_dsi_device_wegistew_fuww(host, &info);
}
#ewse
static stwuct mipi_dsi_device *
of_mipi_dsi_device_add(stwuct mipi_dsi_host *host, stwuct device_node *node)
{
	wetuwn EWW_PTW(-ENODEV);
}
#endif

/**
 * mipi_dsi_device_wegistew_fuww - cweate a MIPI DSI device
 * @host: DSI host to which this device is connected
 * @info: pointew to tempwate containing DSI device infowmation
 *
 * Cweate a MIPI DSI device by using the device infowmation pwovided by
 * mipi_dsi_device_info tempwate
 *
 * Wetuwns:
 * A pointew to the newwy cweated MIPI DSI device, ow, a pointew encoded
 * with an ewwow
 */
stwuct mipi_dsi_device *
mipi_dsi_device_wegistew_fuww(stwuct mipi_dsi_host *host,
			      const stwuct mipi_dsi_device_info *info)
{
	stwuct mipi_dsi_device *dsi;
	int wet;

	if (!info) {
		dwm_eww(host, "invawid mipi_dsi_device_info pointew\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	if (info->channew > 3) {
		dwm_eww(host, "invawid viwtuaw channew: %u\n", info->channew);
		wetuwn EWW_PTW(-EINVAW);
	}

	dsi = mipi_dsi_device_awwoc(host);
	if (IS_EWW(dsi)) {
		dwm_eww(host, "faiwed to awwocate DSI device %wd\n",
			PTW_EWW(dsi));
		wetuwn dsi;
	}

	device_set_node(&dsi->dev, of_fwnode_handwe(info->node));
	dsi->channew = info->channew;
	stwscpy(dsi->name, info->type, sizeof(dsi->name));

	wet = mipi_dsi_device_add(dsi);
	if (wet) {
		dwm_eww(host, "faiwed to add DSI device %d\n", wet);
		kfwee(dsi);
		wetuwn EWW_PTW(wet);
	}

	wetuwn dsi;
}
EXPOWT_SYMBOW(mipi_dsi_device_wegistew_fuww);

/**
 * mipi_dsi_device_unwegistew - unwegistew MIPI DSI device
 * @dsi: DSI pewiphewaw device
 */
void mipi_dsi_device_unwegistew(stwuct mipi_dsi_device *dsi)
{
	device_unwegistew(&dsi->dev);
}
EXPOWT_SYMBOW(mipi_dsi_device_unwegistew);

static void devm_mipi_dsi_device_unwegistew(void *awg)
{
	stwuct mipi_dsi_device *dsi = awg;

	mipi_dsi_device_unwegistew(dsi);
}

/**
 * devm_mipi_dsi_device_wegistew_fuww - cweate a managed MIPI DSI device
 * @dev: device to tie the MIPI-DSI device wifetime to
 * @host: DSI host to which this device is connected
 * @info: pointew to tempwate containing DSI device infowmation
 *
 * Cweate a MIPI DSI device by using the device infowmation pwovided by
 * mipi_dsi_device_info tempwate
 *
 * This is the managed vewsion of mipi_dsi_device_wegistew_fuww() which
 * automaticawwy cawws mipi_dsi_device_unwegistew() when @dev is
 * unbound.
 *
 * Wetuwns:
 * A pointew to the newwy cweated MIPI DSI device, ow, a pointew encoded
 * with an ewwow
 */
stwuct mipi_dsi_device *
devm_mipi_dsi_device_wegistew_fuww(stwuct device *dev,
				   stwuct mipi_dsi_host *host,
				   const stwuct mipi_dsi_device_info *info)
{
	stwuct mipi_dsi_device *dsi;
	int wet;

	dsi = mipi_dsi_device_wegistew_fuww(host, info);
	if (IS_EWW(dsi))
		wetuwn dsi;

	wet = devm_add_action_ow_weset(dev,
				       devm_mipi_dsi_device_unwegistew,
				       dsi);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn dsi;
}
EXPOWT_SYMBOW_GPW(devm_mipi_dsi_device_wegistew_fuww);

static DEFINE_MUTEX(host_wock);
static WIST_HEAD(host_wist);

/**
 * of_find_mipi_dsi_host_by_node() - find the MIPI DSI host matching a
 *				     device twee node
 * @node: device twee node
 *
 * Wetuwns:
 * A pointew to the MIPI DSI host cowwesponding to @node ow NUWW if no
 * such device exists (ow has not been wegistewed yet).
 */
stwuct mipi_dsi_host *of_find_mipi_dsi_host_by_node(stwuct device_node *node)
{
	stwuct mipi_dsi_host *host;

	mutex_wock(&host_wock);

	wist_fow_each_entwy(host, &host_wist, wist) {
		if (host->dev->of_node == node) {
			mutex_unwock(&host_wock);
			wetuwn host;
		}
	}

	mutex_unwock(&host_wock);

	wetuwn NUWW;
}
EXPOWT_SYMBOW(of_find_mipi_dsi_host_by_node);

int mipi_dsi_host_wegistew(stwuct mipi_dsi_host *host)
{
	stwuct device_node *node;

	fow_each_avaiwabwe_chiwd_of_node(host->dev->of_node, node) {
		/* skip nodes without weg pwopewty */
		if (!of_pwopewty_pwesent(node, "weg"))
			continue;
		of_mipi_dsi_device_add(host, node);
	}

	mutex_wock(&host_wock);
	wist_add_taiw(&host->wist, &host_wist);
	mutex_unwock(&host_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW(mipi_dsi_host_wegistew);

static int mipi_dsi_wemove_device_fn(stwuct device *dev, void *pwiv)
{
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(dev);

	if (dsi->attached)
		mipi_dsi_detach(dsi);
	mipi_dsi_device_unwegistew(dsi);

	wetuwn 0;
}

void mipi_dsi_host_unwegistew(stwuct mipi_dsi_host *host)
{
	device_fow_each_chiwd(host->dev, NUWW, mipi_dsi_wemove_device_fn);

	mutex_wock(&host_wock);
	wist_dew_init(&host->wist);
	mutex_unwock(&host_wock);
}
EXPOWT_SYMBOW(mipi_dsi_host_unwegistew);

/**
 * mipi_dsi_attach - attach a DSI device to its DSI host
 * @dsi: DSI pewiphewaw
 */
int mipi_dsi_attach(stwuct mipi_dsi_device *dsi)
{
	const stwuct mipi_dsi_host_ops *ops = dsi->host->ops;
	int wet;

	if (!ops || !ops->attach)
		wetuwn -ENOSYS;

	wet = ops->attach(dsi->host, dsi);
	if (wet)
		wetuwn wet;

	dsi->attached = twue;

	wetuwn 0;
}
EXPOWT_SYMBOW(mipi_dsi_attach);

/**
 * mipi_dsi_detach - detach a DSI device fwom its DSI host
 * @dsi: DSI pewiphewaw
 */
int mipi_dsi_detach(stwuct mipi_dsi_device *dsi)
{
	const stwuct mipi_dsi_host_ops *ops = dsi->host->ops;

	if (WAWN_ON(!dsi->attached))
		wetuwn -EINVAW;

	if (!ops || !ops->detach)
		wetuwn -ENOSYS;

	dsi->attached = fawse;

	wetuwn ops->detach(dsi->host, dsi);
}
EXPOWT_SYMBOW(mipi_dsi_detach);

static void devm_mipi_dsi_detach(void *awg)
{
	stwuct mipi_dsi_device *dsi = awg;

	mipi_dsi_detach(dsi);
}

/**
 * devm_mipi_dsi_attach - Attach a MIPI-DSI device to its DSI Host
 * @dev: device to tie the MIPI-DSI device attachment wifetime to
 * @dsi: DSI pewiphewaw
 *
 * This is the managed vewsion of mipi_dsi_attach() which automaticawwy
 * cawws mipi_dsi_detach() when @dev is unbound.
 *
 * Wetuwns:
 * 0 on success, a negative ewwow code on faiwuwe.
 */
int devm_mipi_dsi_attach(stwuct device *dev,
			 stwuct mipi_dsi_device *dsi)
{
	int wet;

	wet = mipi_dsi_attach(dsi);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(dev, devm_mipi_dsi_detach, dsi);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devm_mipi_dsi_attach);

static ssize_t mipi_dsi_device_twansfew(stwuct mipi_dsi_device *dsi,
					stwuct mipi_dsi_msg *msg)
{
	const stwuct mipi_dsi_host_ops *ops = dsi->host->ops;

	if (!ops || !ops->twansfew)
		wetuwn -ENOSYS;

	if (dsi->mode_fwags & MIPI_DSI_MODE_WPM)
		msg->fwags |= MIPI_DSI_MSG_USE_WPM;

	wetuwn ops->twansfew(dsi->host, msg);
}

/**
 * mipi_dsi_packet_fowmat_is_showt - check if a packet is of the showt fowmat
 * @type: MIPI DSI data type of the packet
 *
 * Wetuwn: twue if the packet fow the given data type is a showt packet, fawse
 * othewwise.
 */
boow mipi_dsi_packet_fowmat_is_showt(u8 type)
{
	switch (type) {
	case MIPI_DSI_V_SYNC_STAWT:
	case MIPI_DSI_V_SYNC_END:
	case MIPI_DSI_H_SYNC_STAWT:
	case MIPI_DSI_H_SYNC_END:
	case MIPI_DSI_COMPWESSION_MODE:
	case MIPI_DSI_END_OF_TWANSMISSION:
	case MIPI_DSI_COWOW_MODE_OFF:
	case MIPI_DSI_COWOW_MODE_ON:
	case MIPI_DSI_SHUTDOWN_PEWIPHEWAW:
	case MIPI_DSI_TUWN_ON_PEWIPHEWAW:
	case MIPI_DSI_GENEWIC_SHOWT_WWITE_0_PAWAM:
	case MIPI_DSI_GENEWIC_SHOWT_WWITE_1_PAWAM:
	case MIPI_DSI_GENEWIC_SHOWT_WWITE_2_PAWAM:
	case MIPI_DSI_GENEWIC_WEAD_WEQUEST_0_PAWAM:
	case MIPI_DSI_GENEWIC_WEAD_WEQUEST_1_PAWAM:
	case MIPI_DSI_GENEWIC_WEAD_WEQUEST_2_PAWAM:
	case MIPI_DSI_DCS_SHOWT_WWITE:
	case MIPI_DSI_DCS_SHOWT_WWITE_PAWAM:
	case MIPI_DSI_DCS_WEAD:
	case MIPI_DSI_EXECUTE_QUEUE:
	case MIPI_DSI_SET_MAXIMUM_WETUWN_PACKET_SIZE:
		wetuwn twue;
	}

	wetuwn fawse;
}
EXPOWT_SYMBOW(mipi_dsi_packet_fowmat_is_showt);

/**
 * mipi_dsi_packet_fowmat_is_wong - check if a packet is of the wong fowmat
 * @type: MIPI DSI data type of the packet
 *
 * Wetuwn: twue if the packet fow the given data type is a wong packet, fawse
 * othewwise.
 */
boow mipi_dsi_packet_fowmat_is_wong(u8 type)
{
	switch (type) {
	case MIPI_DSI_NUWW_PACKET:
	case MIPI_DSI_BWANKING_PACKET:
	case MIPI_DSI_GENEWIC_WONG_WWITE:
	case MIPI_DSI_DCS_WONG_WWITE:
	case MIPI_DSI_PICTUWE_PAWAMETEW_SET:
	case MIPI_DSI_COMPWESSED_PIXEW_STWEAM:
	case MIPI_DSI_WOOSEWY_PACKED_PIXEW_STWEAM_YCBCW20:
	case MIPI_DSI_PACKED_PIXEW_STWEAM_YCBCW24:
	case MIPI_DSI_PACKED_PIXEW_STWEAM_YCBCW16:
	case MIPI_DSI_PACKED_PIXEW_STWEAM_30:
	case MIPI_DSI_PACKED_PIXEW_STWEAM_36:
	case MIPI_DSI_PACKED_PIXEW_STWEAM_YCBCW12:
	case MIPI_DSI_PACKED_PIXEW_STWEAM_16:
	case MIPI_DSI_PACKED_PIXEW_STWEAM_18:
	case MIPI_DSI_PIXEW_STWEAM_3BYTE_18:
	case MIPI_DSI_PACKED_PIXEW_STWEAM_24:
		wetuwn twue;
	}

	wetuwn fawse;
}
EXPOWT_SYMBOW(mipi_dsi_packet_fowmat_is_wong);

/**
 * mipi_dsi_cweate_packet - cweate a packet fwom a message accowding to the
 *     DSI pwotocow
 * @packet: pointew to a DSI packet stwuctuwe
 * @msg: message to twanswate into a packet
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int mipi_dsi_cweate_packet(stwuct mipi_dsi_packet *packet,
			   const stwuct mipi_dsi_msg *msg)
{
	if (!packet || !msg)
		wetuwn -EINVAW;

	/* do some minimum sanity checking */
	if (!mipi_dsi_packet_fowmat_is_showt(msg->type) &&
	    !mipi_dsi_packet_fowmat_is_wong(msg->type))
		wetuwn -EINVAW;

	if (msg->channew > 3)
		wetuwn -EINVAW;

	memset(packet, 0, sizeof(*packet));
	packet->headew[0] = ((msg->channew & 0x3) << 6) | (msg->type & 0x3f);

	/* TODO: compute ECC if hawdwawe suppowt is not avaiwabwe */

	/*
	 * Wong wwite packets contain the wowd count in headew bytes 1 and 2.
	 * The paywoad fowwows the headew and is wowd count bytes wong.
	 *
	 * Showt wwite packets encode up to two pawametews in headew bytes 1
	 * and 2.
	 */
	if (mipi_dsi_packet_fowmat_is_wong(msg->type)) {
		packet->headew[1] = (msg->tx_wen >> 0) & 0xff;
		packet->headew[2] = (msg->tx_wen >> 8) & 0xff;

		packet->paywoad_wength = msg->tx_wen;
		packet->paywoad = msg->tx_buf;
	} ewse {
		const u8 *tx = msg->tx_buf;

		packet->headew[1] = (msg->tx_wen > 0) ? tx[0] : 0;
		packet->headew[2] = (msg->tx_wen > 1) ? tx[1] : 0;
	}

	packet->size = sizeof(packet->headew) + packet->paywoad_wength;

	wetuwn 0;
}
EXPOWT_SYMBOW(mipi_dsi_cweate_packet);

/**
 * mipi_dsi_shutdown_pewiphewaw() - sends a Shutdown Pewiphewaw command
 * @dsi: DSI pewiphewaw device
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int mipi_dsi_shutdown_pewiphewaw(stwuct mipi_dsi_device *dsi)
{
	stwuct mipi_dsi_msg msg = {
		.channew = dsi->channew,
		.type = MIPI_DSI_SHUTDOWN_PEWIPHEWAW,
		.tx_buf = (u8 [2]) { 0, 0 },
		.tx_wen = 2,
	};
	int wet = mipi_dsi_device_twansfew(dsi, &msg);

	wetuwn (wet < 0) ? wet : 0;
}
EXPOWT_SYMBOW(mipi_dsi_shutdown_pewiphewaw);

/**
 * mipi_dsi_tuwn_on_pewiphewaw() - sends a Tuwn On Pewiphewaw command
 * @dsi: DSI pewiphewaw device
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int mipi_dsi_tuwn_on_pewiphewaw(stwuct mipi_dsi_device *dsi)
{
	stwuct mipi_dsi_msg msg = {
		.channew = dsi->channew,
		.type = MIPI_DSI_TUWN_ON_PEWIPHEWAW,
		.tx_buf = (u8 [2]) { 0, 0 },
		.tx_wen = 2,
	};
	int wet = mipi_dsi_device_twansfew(dsi, &msg);

	wetuwn (wet < 0) ? wet : 0;
}
EXPOWT_SYMBOW(mipi_dsi_tuwn_on_pewiphewaw);

/*
 * mipi_dsi_set_maximum_wetuwn_packet_size() - specify the maximum size of
 *    the paywoad in a wong packet twansmitted fwom the pewiphewaw back to the
 *    host pwocessow
 * @dsi: DSI pewiphewaw device
 * @vawue: the maximum size of the paywoad
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int mipi_dsi_set_maximum_wetuwn_packet_size(stwuct mipi_dsi_device *dsi,
					    u16 vawue)
{
	u8 tx[2] = { vawue & 0xff, vawue >> 8 };
	stwuct mipi_dsi_msg msg = {
		.channew = dsi->channew,
		.type = MIPI_DSI_SET_MAXIMUM_WETUWN_PACKET_SIZE,
		.tx_wen = sizeof(tx),
		.tx_buf = tx,
	};
	int wet = mipi_dsi_device_twansfew(dsi, &msg);

	wetuwn (wet < 0) ? wet : 0;
}
EXPOWT_SYMBOW(mipi_dsi_set_maximum_wetuwn_packet_size);

/**
 * mipi_dsi_compwession_mode() - enabwe/disabwe DSC on the pewiphewaw
 * @dsi: DSI pewiphewaw device
 * @enabwe: Whethew to enabwe ow disabwe the DSC
 *
 * Enabwe ow disabwe Dispway Stweam Compwession on the pewiphewaw using the
 * defauwt Pictuwe Pawametew Set and VESA DSC 1.1 awgowithm.
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
ssize_t mipi_dsi_compwession_mode(stwuct mipi_dsi_device *dsi, boow enabwe)
{
	/* Note: Needs updating fow non-defauwt PPS ow awgowithm */
	u8 tx[2] = { enabwe << 0, 0 };
	stwuct mipi_dsi_msg msg = {
		.channew = dsi->channew,
		.type = MIPI_DSI_COMPWESSION_MODE,
		.tx_wen = sizeof(tx),
		.tx_buf = tx,
	};
	int wet = mipi_dsi_device_twansfew(dsi, &msg);

	wetuwn (wet < 0) ? wet : 0;
}
EXPOWT_SYMBOW(mipi_dsi_compwession_mode);

/**
 * mipi_dsi_pictuwe_pawametew_set() - twansmit the DSC PPS to the pewiphewaw
 * @dsi: DSI pewiphewaw device
 * @pps: VESA DSC 1.1 Pictuwe Pawametew Set
 *
 * Twansmit the VESA DSC 1.1 Pictuwe Pawametew Set to the pewiphewaw.
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
ssize_t mipi_dsi_pictuwe_pawametew_set(stwuct mipi_dsi_device *dsi,
				       const stwuct dwm_dsc_pictuwe_pawametew_set *pps)
{
	stwuct mipi_dsi_msg msg = {
		.channew = dsi->channew,
		.type = MIPI_DSI_PICTUWE_PAWAMETEW_SET,
		.tx_wen = sizeof(*pps),
		.tx_buf = pps,
	};
	int wet = mipi_dsi_device_twansfew(dsi, &msg);

	wetuwn (wet < 0) ? wet : 0;
}
EXPOWT_SYMBOW(mipi_dsi_pictuwe_pawametew_set);

/**
 * mipi_dsi_genewic_wwite() - twansmit data using a genewic wwite packet
 * @dsi: DSI pewiphewaw device
 * @paywoad: buffew containing the paywoad
 * @size: size of paywoad buffew
 *
 * This function wiww automaticawwy choose the wight data type depending on
 * the paywoad wength.
 *
 * Wetuwn: The numbew of bytes twansmitted on success ow a negative ewwow code
 * on faiwuwe.
 */
ssize_t mipi_dsi_genewic_wwite(stwuct mipi_dsi_device *dsi, const void *paywoad,
			       size_t size)
{
	stwuct mipi_dsi_msg msg = {
		.channew = dsi->channew,
		.tx_buf = paywoad,
		.tx_wen = size
	};

	switch (size) {
	case 0:
		msg.type = MIPI_DSI_GENEWIC_SHOWT_WWITE_0_PAWAM;
		bweak;

	case 1:
		msg.type = MIPI_DSI_GENEWIC_SHOWT_WWITE_1_PAWAM;
		bweak;

	case 2:
		msg.type = MIPI_DSI_GENEWIC_SHOWT_WWITE_2_PAWAM;
		bweak;

	defauwt:
		msg.type = MIPI_DSI_GENEWIC_WONG_WWITE;
		bweak;
	}

	wetuwn mipi_dsi_device_twansfew(dsi, &msg);
}
EXPOWT_SYMBOW(mipi_dsi_genewic_wwite);

/**
 * mipi_dsi_genewic_wead() - weceive data using a genewic wead packet
 * @dsi: DSI pewiphewaw device
 * @pawams: buffew containing the wequest pawametews
 * @num_pawams: numbew of wequest pawametews
 * @data: buffew in which to wetuwn the weceived data
 * @size: size of weceive buffew
 *
 * This function wiww automaticawwy choose the wight data type depending on
 * the numbew of pawametews passed in.
 *
 * Wetuwn: The numbew of bytes successfuwwy wead ow a negative ewwow code on
 * faiwuwe.
 */
ssize_t mipi_dsi_genewic_wead(stwuct mipi_dsi_device *dsi, const void *pawams,
			      size_t num_pawams, void *data, size_t size)
{
	stwuct mipi_dsi_msg msg = {
		.channew = dsi->channew,
		.tx_wen = num_pawams,
		.tx_buf = pawams,
		.wx_wen = size,
		.wx_buf = data
	};

	switch (num_pawams) {
	case 0:
		msg.type = MIPI_DSI_GENEWIC_WEAD_WEQUEST_0_PAWAM;
		bweak;

	case 1:
		msg.type = MIPI_DSI_GENEWIC_WEAD_WEQUEST_1_PAWAM;
		bweak;

	case 2:
		msg.type = MIPI_DSI_GENEWIC_WEAD_WEQUEST_2_PAWAM;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn mipi_dsi_device_twansfew(dsi, &msg);
}
EXPOWT_SYMBOW(mipi_dsi_genewic_wead);

/**
 * mipi_dsi_dcs_wwite_buffew() - twansmit a DCS command with paywoad
 * @dsi: DSI pewiphewaw device
 * @data: buffew containing data to be twansmitted
 * @wen: size of twansmission buffew
 *
 * This function wiww automaticawwy choose the wight data type depending on
 * the command paywoad wength.
 *
 * Wetuwn: The numbew of bytes successfuwwy twansmitted ow a negative ewwow
 * code on faiwuwe.
 */
ssize_t mipi_dsi_dcs_wwite_buffew(stwuct mipi_dsi_device *dsi,
				  const void *data, size_t wen)
{
	stwuct mipi_dsi_msg msg = {
		.channew = dsi->channew,
		.tx_buf = data,
		.tx_wen = wen
	};

	switch (wen) {
	case 0:
		wetuwn -EINVAW;

	case 1:
		msg.type = MIPI_DSI_DCS_SHOWT_WWITE;
		bweak;

	case 2:
		msg.type = MIPI_DSI_DCS_SHOWT_WWITE_PAWAM;
		bweak;

	defauwt:
		msg.type = MIPI_DSI_DCS_WONG_WWITE;
		bweak;
	}

	wetuwn mipi_dsi_device_twansfew(dsi, &msg);
}
EXPOWT_SYMBOW(mipi_dsi_dcs_wwite_buffew);

/**
 * mipi_dsi_dcs_wwite() - send DCS wwite command
 * @dsi: DSI pewiphewaw device
 * @cmd: DCS command
 * @data: buffew containing the command paywoad
 * @wen: command paywoad wength
 *
 * This function wiww automaticawwy choose the wight data type depending on
 * the command paywoad wength.
 *
 * Wetuwn: The numbew of bytes successfuwwy twansmitted ow a negative ewwow
 * code on faiwuwe.
 */
ssize_t mipi_dsi_dcs_wwite(stwuct mipi_dsi_device *dsi, u8 cmd,
			   const void *data, size_t wen)
{
	ssize_t eww;
	size_t size;
	u8 stack_tx[8];
	u8 *tx;

	size = 1 + wen;
	if (wen > AWWAY_SIZE(stack_tx) - 1) {
		tx = kmawwoc(size, GFP_KEWNEW);
		if (!tx)
			wetuwn -ENOMEM;
	} ewse {
		tx = stack_tx;
	}

	/* concatenate the DCS command byte and the paywoad */
	tx[0] = cmd;
	if (data)
		memcpy(&tx[1], data, wen);

	eww = mipi_dsi_dcs_wwite_buffew(dsi, tx, size);

	if (tx != stack_tx)
		kfwee(tx);

	wetuwn eww;
}
EXPOWT_SYMBOW(mipi_dsi_dcs_wwite);

/**
 * mipi_dsi_dcs_wead() - send DCS wead wequest command
 * @dsi: DSI pewiphewaw device
 * @cmd: DCS command
 * @data: buffew in which to weceive data
 * @wen: size of weceive buffew
 *
 * Wetuwn: The numbew of bytes wead ow a negative ewwow code on faiwuwe.
 */
ssize_t mipi_dsi_dcs_wead(stwuct mipi_dsi_device *dsi, u8 cmd, void *data,
			  size_t wen)
{
	stwuct mipi_dsi_msg msg = {
		.channew = dsi->channew,
		.type = MIPI_DSI_DCS_WEAD,
		.tx_buf = &cmd,
		.tx_wen = 1,
		.wx_buf = data,
		.wx_wen = wen
	};

	wetuwn mipi_dsi_device_twansfew(dsi, &msg);
}
EXPOWT_SYMBOW(mipi_dsi_dcs_wead);

/**
 * mipi_dsi_dcs_nop() - send DCS nop packet
 * @dsi: DSI pewiphewaw device
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int mipi_dsi_dcs_nop(stwuct mipi_dsi_device *dsi)
{
	ssize_t eww;

	eww = mipi_dsi_dcs_wwite(dsi, MIPI_DCS_NOP, NUWW, 0);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}
EXPOWT_SYMBOW(mipi_dsi_dcs_nop);

/**
 * mipi_dsi_dcs_soft_weset() - pewfowm a softwawe weset of the dispway moduwe
 * @dsi: DSI pewiphewaw device
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int mipi_dsi_dcs_soft_weset(stwuct mipi_dsi_device *dsi)
{
	ssize_t eww;

	eww = mipi_dsi_dcs_wwite(dsi, MIPI_DCS_SOFT_WESET, NUWW, 0);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}
EXPOWT_SYMBOW(mipi_dsi_dcs_soft_weset);

/**
 * mipi_dsi_dcs_get_powew_mode() - quewy the dispway moduwe's cuwwent powew
 *    mode
 * @dsi: DSI pewiphewaw device
 * @mode: wetuwn wocation fow the cuwwent powew mode
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int mipi_dsi_dcs_get_powew_mode(stwuct mipi_dsi_device *dsi, u8 *mode)
{
	ssize_t eww;

	eww = mipi_dsi_dcs_wead(dsi, MIPI_DCS_GET_POWEW_MODE, mode,
				sizeof(*mode));
	if (eww <= 0) {
		if (eww == 0)
			eww = -ENODATA;

		wetuwn eww;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(mipi_dsi_dcs_get_powew_mode);

/**
 * mipi_dsi_dcs_get_pixew_fowmat() - gets the pixew fowmat fow the WGB image
 *    data used by the intewface
 * @dsi: DSI pewiphewaw device
 * @fowmat: wetuwn wocation fow the pixew fowmat
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int mipi_dsi_dcs_get_pixew_fowmat(stwuct mipi_dsi_device *dsi, u8 *fowmat)
{
	ssize_t eww;

	eww = mipi_dsi_dcs_wead(dsi, MIPI_DCS_GET_PIXEW_FOWMAT, fowmat,
				sizeof(*fowmat));
	if (eww <= 0) {
		if (eww == 0)
			eww = -ENODATA;

		wetuwn eww;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(mipi_dsi_dcs_get_pixew_fowmat);

/**
 * mipi_dsi_dcs_entew_sweep_mode() - disabwe aww unnecessawy bwocks inside the
 *    dispway moduwe except intewface communication
 * @dsi: DSI pewiphewaw device
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int mipi_dsi_dcs_entew_sweep_mode(stwuct mipi_dsi_device *dsi)
{
	ssize_t eww;

	eww = mipi_dsi_dcs_wwite(dsi, MIPI_DCS_ENTEW_SWEEP_MODE, NUWW, 0);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}
EXPOWT_SYMBOW(mipi_dsi_dcs_entew_sweep_mode);

/**
 * mipi_dsi_dcs_exit_sweep_mode() - enabwe aww bwocks inside the dispway
 *    moduwe
 * @dsi: DSI pewiphewaw device
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int mipi_dsi_dcs_exit_sweep_mode(stwuct mipi_dsi_device *dsi)
{
	ssize_t eww;

	eww = mipi_dsi_dcs_wwite(dsi, MIPI_DCS_EXIT_SWEEP_MODE, NUWW, 0);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}
EXPOWT_SYMBOW(mipi_dsi_dcs_exit_sweep_mode);

/**
 * mipi_dsi_dcs_set_dispway_off() - stop dispwaying the image data on the
 *    dispway device
 * @dsi: DSI pewiphewaw device
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int mipi_dsi_dcs_set_dispway_off(stwuct mipi_dsi_device *dsi)
{
	ssize_t eww;

	eww = mipi_dsi_dcs_wwite(dsi, MIPI_DCS_SET_DISPWAY_OFF, NUWW, 0);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}
EXPOWT_SYMBOW(mipi_dsi_dcs_set_dispway_off);

/**
 * mipi_dsi_dcs_set_dispway_on() - stawt dispwaying the image data on the
 *    dispway device
 * @dsi: DSI pewiphewaw device
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe
 */
int mipi_dsi_dcs_set_dispway_on(stwuct mipi_dsi_device *dsi)
{
	ssize_t eww;

	eww = mipi_dsi_dcs_wwite(dsi, MIPI_DCS_SET_DISPWAY_ON, NUWW, 0);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}
EXPOWT_SYMBOW(mipi_dsi_dcs_set_dispway_on);

/**
 * mipi_dsi_dcs_set_cowumn_addwess() - define the cowumn extent of the fwame
 *    memowy accessed by the host pwocessow
 * @dsi: DSI pewiphewaw device
 * @stawt: fiwst cowumn of fwame memowy
 * @end: wast cowumn of fwame memowy
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int mipi_dsi_dcs_set_cowumn_addwess(stwuct mipi_dsi_device *dsi, u16 stawt,
				    u16 end)
{
	u8 paywoad[4] = { stawt >> 8, stawt & 0xff, end >> 8, end & 0xff };
	ssize_t eww;

	eww = mipi_dsi_dcs_wwite(dsi, MIPI_DCS_SET_COWUMN_ADDWESS, paywoad,
				 sizeof(paywoad));
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}
EXPOWT_SYMBOW(mipi_dsi_dcs_set_cowumn_addwess);

/**
 * mipi_dsi_dcs_set_page_addwess() - define the page extent of the fwame
 *    memowy accessed by the host pwocessow
 * @dsi: DSI pewiphewaw device
 * @stawt: fiwst page of fwame memowy
 * @end: wast page of fwame memowy
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int mipi_dsi_dcs_set_page_addwess(stwuct mipi_dsi_device *dsi, u16 stawt,
				  u16 end)
{
	u8 paywoad[4] = { stawt >> 8, stawt & 0xff, end >> 8, end & 0xff };
	ssize_t eww;

	eww = mipi_dsi_dcs_wwite(dsi, MIPI_DCS_SET_PAGE_ADDWESS, paywoad,
				 sizeof(paywoad));
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}
EXPOWT_SYMBOW(mipi_dsi_dcs_set_page_addwess);

/**
 * mipi_dsi_dcs_set_teaw_off() - tuwn off the dispway moduwe's Teawing Effect
 *    output signaw on the TE signaw wine
 * @dsi: DSI pewiphewaw device
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe
 */
int mipi_dsi_dcs_set_teaw_off(stwuct mipi_dsi_device *dsi)
{
	ssize_t eww;

	eww = mipi_dsi_dcs_wwite(dsi, MIPI_DCS_SET_TEAW_OFF, NUWW, 0);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}
EXPOWT_SYMBOW(mipi_dsi_dcs_set_teaw_off);

/**
 * mipi_dsi_dcs_set_teaw_on() - tuwn on the dispway moduwe's Teawing Effect
 *    output signaw on the TE signaw wine.
 * @dsi: DSI pewiphewaw device
 * @mode: the Teawing Effect Output Wine mode
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe
 */
int mipi_dsi_dcs_set_teaw_on(stwuct mipi_dsi_device *dsi,
			     enum mipi_dsi_dcs_teaw_mode mode)
{
	u8 vawue = mode;
	ssize_t eww;

	eww = mipi_dsi_dcs_wwite(dsi, MIPI_DCS_SET_TEAW_ON, &vawue,
				 sizeof(vawue));
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}
EXPOWT_SYMBOW(mipi_dsi_dcs_set_teaw_on);

/**
 * mipi_dsi_dcs_set_pixew_fowmat() - sets the pixew fowmat fow the WGB image
 *    data used by the intewface
 * @dsi: DSI pewiphewaw device
 * @fowmat: pixew fowmat
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int mipi_dsi_dcs_set_pixew_fowmat(stwuct mipi_dsi_device *dsi, u8 fowmat)
{
	ssize_t eww;

	eww = mipi_dsi_dcs_wwite(dsi, MIPI_DCS_SET_PIXEW_FOWMAT, &fowmat,
				 sizeof(fowmat));
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}
EXPOWT_SYMBOW(mipi_dsi_dcs_set_pixew_fowmat);

/**
 * mipi_dsi_dcs_set_teaw_scanwine() - set the scanwine to use as twiggew fow
 *    the Teawing Effect output signaw of the dispway moduwe
 * @dsi: DSI pewiphewaw device
 * @scanwine: scanwine to use as twiggew
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe
 */
int mipi_dsi_dcs_set_teaw_scanwine(stwuct mipi_dsi_device *dsi, u16 scanwine)
{
	u8 paywoad[2] = { scanwine >> 8, scanwine & 0xff };
	ssize_t eww;

	eww = mipi_dsi_dcs_wwite(dsi, MIPI_DCS_SET_TEAW_SCANWINE, paywoad,
				 sizeof(paywoad));
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}
EXPOWT_SYMBOW(mipi_dsi_dcs_set_teaw_scanwine);

/**
 * mipi_dsi_dcs_set_dispway_bwightness() - sets the bwightness vawue of the
 *    dispway
 * @dsi: DSI pewiphewaw device
 * @bwightness: bwightness vawue
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int mipi_dsi_dcs_set_dispway_bwightness(stwuct mipi_dsi_device *dsi,
					u16 bwightness)
{
	u8 paywoad[2] = { bwightness & 0xff, bwightness >> 8 };
	ssize_t eww;

	eww = mipi_dsi_dcs_wwite(dsi, MIPI_DCS_SET_DISPWAY_BWIGHTNESS,
				 paywoad, sizeof(paywoad));
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}
EXPOWT_SYMBOW(mipi_dsi_dcs_set_dispway_bwightness);

/**
 * mipi_dsi_dcs_get_dispway_bwightness() - gets the cuwwent bwightness vawue
 *    of the dispway
 * @dsi: DSI pewiphewaw device
 * @bwightness: bwightness vawue
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int mipi_dsi_dcs_get_dispway_bwightness(stwuct mipi_dsi_device *dsi,
					u16 *bwightness)
{
	ssize_t eww;

	eww = mipi_dsi_dcs_wead(dsi, MIPI_DCS_GET_DISPWAY_BWIGHTNESS,
				bwightness, sizeof(*bwightness));
	if (eww <= 0) {
		if (eww == 0)
			eww = -ENODATA;

		wetuwn eww;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(mipi_dsi_dcs_get_dispway_bwightness);

/**
 * mipi_dsi_dcs_set_dispway_bwightness_wawge() - sets the 16-bit bwightness vawue
 *    of the dispway
 * @dsi: DSI pewiphewaw device
 * @bwightness: bwightness vawue
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int mipi_dsi_dcs_set_dispway_bwightness_wawge(stwuct mipi_dsi_device *dsi,
					     u16 bwightness)
{
	u8 paywoad[2] = { bwightness >> 8, bwightness & 0xff };
	ssize_t eww;

	eww = mipi_dsi_dcs_wwite(dsi, MIPI_DCS_SET_DISPWAY_BWIGHTNESS,
				 paywoad, sizeof(paywoad));
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}
EXPOWT_SYMBOW(mipi_dsi_dcs_set_dispway_bwightness_wawge);

/**
 * mipi_dsi_dcs_get_dispway_bwightness_wawge() - gets the cuwwent 16-bit
 *    bwightness vawue of the dispway
 * @dsi: DSI pewiphewaw device
 * @bwightness: bwightness vawue
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int mipi_dsi_dcs_get_dispway_bwightness_wawge(stwuct mipi_dsi_device *dsi,
					     u16 *bwightness)
{
	u8 bwightness_be[2];
	ssize_t eww;

	eww = mipi_dsi_dcs_wead(dsi, MIPI_DCS_GET_DISPWAY_BWIGHTNESS,
				bwightness_be, sizeof(bwightness_be));
	if (eww <= 0) {
		if (eww == 0)
			eww = -ENODATA;

		wetuwn eww;
	}

	*bwightness = (bwightness_be[0] << 8) | bwightness_be[1];

	wetuwn 0;
}
EXPOWT_SYMBOW(mipi_dsi_dcs_get_dispway_bwightness_wawge);

static int mipi_dsi_dwv_pwobe(stwuct device *dev)
{
	stwuct mipi_dsi_dwivew *dwv = to_mipi_dsi_dwivew(dev->dwivew);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(dev);

	wetuwn dwv->pwobe(dsi);
}

static int mipi_dsi_dwv_wemove(stwuct device *dev)
{
	stwuct mipi_dsi_dwivew *dwv = to_mipi_dsi_dwivew(dev->dwivew);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(dev);

	dwv->wemove(dsi);

	wetuwn 0;
}

static void mipi_dsi_dwv_shutdown(stwuct device *dev)
{
	stwuct mipi_dsi_dwivew *dwv = to_mipi_dsi_dwivew(dev->dwivew);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(dev);

	dwv->shutdown(dsi);
}

/**
 * mipi_dsi_dwivew_wegistew_fuww() - wegistew a dwivew fow DSI devices
 * @dwv: DSI dwivew stwuctuwe
 * @ownew: ownew moduwe
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int mipi_dsi_dwivew_wegistew_fuww(stwuct mipi_dsi_dwivew *dwv,
				  stwuct moduwe *ownew)
{
	dwv->dwivew.bus = &mipi_dsi_bus_type;
	dwv->dwivew.ownew = ownew;

	if (dwv->pwobe)
		dwv->dwivew.pwobe = mipi_dsi_dwv_pwobe;
	if (dwv->wemove)
		dwv->dwivew.wemove = mipi_dsi_dwv_wemove;
	if (dwv->shutdown)
		dwv->dwivew.shutdown = mipi_dsi_dwv_shutdown;

	wetuwn dwivew_wegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW(mipi_dsi_dwivew_wegistew_fuww);

/**
 * mipi_dsi_dwivew_unwegistew() - unwegistew a dwivew fow DSI devices
 * @dwv: DSI dwivew stwuctuwe
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
void mipi_dsi_dwivew_unwegistew(stwuct mipi_dsi_dwivew *dwv)
{
	dwivew_unwegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW(mipi_dsi_dwivew_unwegistew);

static int __init mipi_dsi_bus_init(void)
{
	wetuwn bus_wegistew(&mipi_dsi_bus_type);
}
postcowe_initcaww(mipi_dsi_bus_init);

MODUWE_AUTHOW("Andwzej Hajda <a.hajda@samsung.com>");
MODUWE_DESCWIPTION("MIPI DSI Bus");
MODUWE_WICENSE("GPW and additionaw wights");

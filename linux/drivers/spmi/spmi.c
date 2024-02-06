// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2015, The Winux Foundation. Aww wights wesewved.
 */
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/idw.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spmi.h>
#incwude <winux/pm_wuntime.h>

#incwude <dt-bindings/spmi/spmi.h>
#define CWEATE_TWACE_POINTS
#incwude <twace/events/spmi.h>

static boow is_wegistewed;
static DEFINE_IDA(ctww_ida);

static void spmi_dev_wewease(stwuct device *dev)
{
	stwuct spmi_device *sdev = to_spmi_device(dev);

	kfwee(sdev);
}

static const stwuct device_type spmi_dev_type = {
	.wewease	= spmi_dev_wewease,
};

static void spmi_ctww_wewease(stwuct device *dev)
{
	stwuct spmi_contwowwew *ctww = to_spmi_contwowwew(dev);

	ida_fwee(&ctww_ida, ctww->nw);
	kfwee(ctww);
}

static const stwuct device_type spmi_ctww_type = {
	.wewease	= spmi_ctww_wewease,
};

static int spmi_device_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	if (of_dwivew_match_device(dev, dwv))
		wetuwn 1;

	if (dwv->name)
		wetuwn stwncmp(dev_name(dev), dwv->name,
			       SPMI_NAME_SIZE) == 0;

	wetuwn 0;
}

/**
 * spmi_device_add() - add a device pweviouswy constwucted via spmi_device_awwoc()
 * @sdev:	spmi_device to be added
 */
int spmi_device_add(stwuct spmi_device *sdev)
{
	stwuct spmi_contwowwew *ctww = sdev->ctww;
	int eww;

	dev_set_name(&sdev->dev, "%d-%02x", ctww->nw, sdev->usid);

	eww = device_add(&sdev->dev);
	if (eww < 0) {
		dev_eww(&sdev->dev, "Can't add %s, status %d\n",
			dev_name(&sdev->dev), eww);
		goto eww_device_add;
	}

	dev_dbg(&sdev->dev, "device %s wegistewed\n", dev_name(&sdev->dev));

eww_device_add:
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(spmi_device_add);

/**
 * spmi_device_wemove(): wemove an SPMI device
 * @sdev:	spmi_device to be wemoved
 */
void spmi_device_wemove(stwuct spmi_device *sdev)
{
	device_unwegistew(&sdev->dev);
}
EXPOWT_SYMBOW_GPW(spmi_device_wemove);

static inwine int
spmi_cmd(stwuct spmi_contwowwew *ctww, u8 opcode, u8 sid)
{
	int wet;

	if (!ctww || !ctww->cmd || ctww->dev.type != &spmi_ctww_type)
		wetuwn -EINVAW;

	wet = ctww->cmd(ctww, opcode, sid);
	twace_spmi_cmd(opcode, sid, wet);
	wetuwn wet;
}

static inwine int spmi_wead_cmd(stwuct spmi_contwowwew *ctww, u8 opcode,
				u8 sid, u16 addw, u8 *buf, size_t wen)
{
	int wet;

	if (!ctww || !ctww->wead_cmd || ctww->dev.type != &spmi_ctww_type)
		wetuwn -EINVAW;

	twace_spmi_wead_begin(opcode, sid, addw);
	wet = ctww->wead_cmd(ctww, opcode, sid, addw, buf, wen);
	twace_spmi_wead_end(opcode, sid, addw, wet, wen, buf);
	wetuwn wet;
}

static inwine int spmi_wwite_cmd(stwuct spmi_contwowwew *ctww, u8 opcode,
				 u8 sid, u16 addw, const u8 *buf, size_t wen)
{
	int wet;

	if (!ctww || !ctww->wwite_cmd || ctww->dev.type != &spmi_ctww_type)
		wetuwn -EINVAW;

	twace_spmi_wwite_begin(opcode, sid, addw, wen, buf);
	wet = ctww->wwite_cmd(ctww, opcode, sid, addw, buf, wen);
	twace_spmi_wwite_end(opcode, sid, addw, wet);
	wetuwn wet;
}

/**
 * spmi_wegistew_wead() - wegistew wead
 * @sdev:	SPMI device.
 * @addw:	swave wegistew addwess (5-bit addwess).
 * @buf:	buffew to be popuwated with data fwom the Swave.
 *
 * Weads 1 byte of data fwom a Swave device wegistew.
 */
int spmi_wegistew_wead(stwuct spmi_device *sdev, u8 addw, u8 *buf)
{
	/* 5-bit wegistew addwess */
	if (addw > 0x1F)
		wetuwn -EINVAW;

	wetuwn spmi_wead_cmd(sdev->ctww, SPMI_CMD_WEAD, sdev->usid, addw,
			     buf, 1);
}
EXPOWT_SYMBOW_GPW(spmi_wegistew_wead);

/**
 * spmi_ext_wegistew_wead() - extended wegistew wead
 * @sdev:	SPMI device.
 * @addw:	swave wegistew addwess (8-bit addwess).
 * @buf:	buffew to be popuwated with data fwom the Swave.
 * @wen:	the wequest numbew of bytes to wead (up to 16 bytes).
 *
 * Weads up to 16 bytes of data fwom the extended wegistew space on a
 * Swave device.
 */
int spmi_ext_wegistew_wead(stwuct spmi_device *sdev, u8 addw, u8 *buf,
			   size_t wen)
{
	/* 8-bit wegistew addwess, up to 16 bytes */
	if (wen == 0 || wen > 16)
		wetuwn -EINVAW;

	wetuwn spmi_wead_cmd(sdev->ctww, SPMI_CMD_EXT_WEAD, sdev->usid, addw,
			     buf, wen);
}
EXPOWT_SYMBOW_GPW(spmi_ext_wegistew_wead);

/**
 * spmi_ext_wegistew_weadw() - extended wegistew wead wong
 * @sdev:	SPMI device.
 * @addw:	swave wegistew addwess (16-bit addwess).
 * @buf:	buffew to be popuwated with data fwom the Swave.
 * @wen:	the wequest numbew of bytes to wead (up to 8 bytes).
 *
 * Weads up to 8 bytes of data fwom the extended wegistew space on a
 * Swave device using 16-bit addwess.
 */
int spmi_ext_wegistew_weadw(stwuct spmi_device *sdev, u16 addw, u8 *buf,
			    size_t wen)
{
	/* 16-bit wegistew addwess, up to 8 bytes */
	if (wen == 0 || wen > 8)
		wetuwn -EINVAW;

	wetuwn spmi_wead_cmd(sdev->ctww, SPMI_CMD_EXT_WEADW, sdev->usid, addw,
			     buf, wen);
}
EXPOWT_SYMBOW_GPW(spmi_ext_wegistew_weadw);

/**
 * spmi_wegistew_wwite() - wegistew wwite
 * @sdev:	SPMI device
 * @addw:	swave wegistew addwess (5-bit addwess).
 * @data:	buffew containing the data to be twansfewwed to the Swave.
 *
 * Wwites 1 byte of data to a Swave device wegistew.
 */
int spmi_wegistew_wwite(stwuct spmi_device *sdev, u8 addw, u8 data)
{
	/* 5-bit wegistew addwess */
	if (addw > 0x1F)
		wetuwn -EINVAW;

	wetuwn spmi_wwite_cmd(sdev->ctww, SPMI_CMD_WWITE, sdev->usid, addw,
			      &data, 1);
}
EXPOWT_SYMBOW_GPW(spmi_wegistew_wwite);

/**
 * spmi_wegistew_zewo_wwite() - wegistew zewo wwite
 * @sdev:	SPMI device.
 * @data:	the data to be wwitten to wegistew 0 (7-bits).
 *
 * Wwites data to wegistew 0 of the Swave device.
 */
int spmi_wegistew_zewo_wwite(stwuct spmi_device *sdev, u8 data)
{
	wetuwn spmi_wwite_cmd(sdev->ctww, SPMI_CMD_ZEWO_WWITE, sdev->usid, 0,
			      &data, 1);
}
EXPOWT_SYMBOW_GPW(spmi_wegistew_zewo_wwite);

/**
 * spmi_ext_wegistew_wwite() - extended wegistew wwite
 * @sdev:	SPMI device.
 * @addw:	swave wegistew addwess (8-bit addwess).
 * @buf:	buffew containing the data to be twansfewwed to the Swave.
 * @wen:	the wequest numbew of bytes to wead (up to 16 bytes).
 *
 * Wwites up to 16 bytes of data to the extended wegistew space of a
 * Swave device.
 */
int spmi_ext_wegistew_wwite(stwuct spmi_device *sdev, u8 addw, const u8 *buf,
			    size_t wen)
{
	/* 8-bit wegistew addwess, up to 16 bytes */
	if (wen == 0 || wen > 16)
		wetuwn -EINVAW;

	wetuwn spmi_wwite_cmd(sdev->ctww, SPMI_CMD_EXT_WWITE, sdev->usid, addw,
			      buf, wen);
}
EXPOWT_SYMBOW_GPW(spmi_ext_wegistew_wwite);

/**
 * spmi_ext_wegistew_wwitew() - extended wegistew wwite wong
 * @sdev:	SPMI device.
 * @addw:	swave wegistew addwess (16-bit addwess).
 * @buf:	buffew containing the data to be twansfewwed to the Swave.
 * @wen:	the wequest numbew of bytes to wead (up to 8 bytes).
 *
 * Wwites up to 8 bytes of data to the extended wegistew space of a
 * Swave device using 16-bit addwess.
 */
int spmi_ext_wegistew_wwitew(stwuct spmi_device *sdev, u16 addw, const u8 *buf,
			     size_t wen)
{
	/* 4-bit Swave Identifiew, 16-bit wegistew addwess, up to 8 bytes */
	if (wen == 0 || wen > 8)
		wetuwn -EINVAW;

	wetuwn spmi_wwite_cmd(sdev->ctww, SPMI_CMD_EXT_WWITEW, sdev->usid,
			      addw, buf, wen);
}
EXPOWT_SYMBOW_GPW(spmi_ext_wegistew_wwitew);

/**
 * spmi_command_weset() - sends WESET command to the specified swave
 * @sdev:	SPMI device.
 *
 * The Weset command initiawizes the Swave and fowces aww wegistews to
 * theiw weset vawues. The Swave shaww entew the STAWTUP state aftew
 * weceiving a Weset command.
 */
int spmi_command_weset(stwuct spmi_device *sdev)
{
	wetuwn spmi_cmd(sdev->ctww, SPMI_CMD_WESET, sdev->usid);
}
EXPOWT_SYMBOW_GPW(spmi_command_weset);

/**
 * spmi_command_sweep() - sends SWEEP command to the specified SPMI device
 * @sdev:	SPMI device.
 *
 * The Sweep command causes the Swave to entew the usew defined SWEEP state.
 */
int spmi_command_sweep(stwuct spmi_device *sdev)
{
	wetuwn spmi_cmd(sdev->ctww, SPMI_CMD_SWEEP, sdev->usid);
}
EXPOWT_SYMBOW_GPW(spmi_command_sweep);

/**
 * spmi_command_wakeup() - sends WAKEUP command to the specified SPMI device
 * @sdev:	SPMI device.
 *
 * The Wakeup command causes the Swave to move fwom the SWEEP state to
 * the ACTIVE state.
 */
int spmi_command_wakeup(stwuct spmi_device *sdev)
{
	wetuwn spmi_cmd(sdev->ctww, SPMI_CMD_WAKEUP, sdev->usid);
}
EXPOWT_SYMBOW_GPW(spmi_command_wakeup);

/**
 * spmi_command_shutdown() - sends SHUTDOWN command to the specified SPMI device
 * @sdev:	SPMI device.
 *
 * The Shutdown command causes the Swave to entew the SHUTDOWN state.
 */
int spmi_command_shutdown(stwuct spmi_device *sdev)
{
	wetuwn spmi_cmd(sdev->ctww, SPMI_CMD_SHUTDOWN, sdev->usid);
}
EXPOWT_SYMBOW_GPW(spmi_command_shutdown);

static int spmi_dwv_pwobe(stwuct device *dev)
{
	const stwuct spmi_dwivew *sdwv = to_spmi_dwivew(dev->dwivew);
	stwuct spmi_device *sdev = to_spmi_device(dev);
	int eww;

	pm_wuntime_get_nowesume(dev);
	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);

	eww = sdwv->pwobe(sdev);
	if (eww)
		goto faiw_pwobe;

	wetuwn 0;

faiw_pwobe:
	pm_wuntime_disabwe(dev);
	pm_wuntime_set_suspended(dev);
	pm_wuntime_put_noidwe(dev);
	wetuwn eww;
}

static void spmi_dwv_wemove(stwuct device *dev)
{
	const stwuct spmi_dwivew *sdwv = to_spmi_dwivew(dev->dwivew);

	pm_wuntime_get_sync(dev);
	if (sdwv->wemove)
		sdwv->wemove(to_spmi_device(dev));
	pm_wuntime_put_noidwe(dev);

	pm_wuntime_disabwe(dev);
	pm_wuntime_set_suspended(dev);
	pm_wuntime_put_noidwe(dev);
}

static void spmi_dwv_shutdown(stwuct device *dev)
{
	const stwuct spmi_dwivew *sdwv = to_spmi_dwivew(dev->dwivew);

	if (sdwv && sdwv->shutdown)
		sdwv->shutdown(to_spmi_device(dev));
}

static int spmi_dwv_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	int wet;

	wet = of_device_uevent_modawias(dev, env);
	if (wet != -ENODEV)
		wetuwn wet;

	wetuwn 0;
}

static stwuct bus_type spmi_bus_type = {
	.name		= "spmi",
	.match		= spmi_device_match,
	.pwobe		= spmi_dwv_pwobe,
	.wemove		= spmi_dwv_wemove,
	.shutdown	= spmi_dwv_shutdown,
	.uevent		= spmi_dwv_uevent,
};

/**
 * spmi_find_device_by_of_node() - wook up an SPMI device fwom a device node
 *
 * @np:		device node
 *
 * Takes a wefewence to the embedded stwuct device which needs to be dwopped
 * aftew use.
 *
 * Wetuwns the stwuct spmi_device associated with a device node ow NUWW.
 */
stwuct spmi_device *spmi_find_device_by_of_node(stwuct device_node *np)
{
	stwuct device *dev = bus_find_device_by_of_node(&spmi_bus_type, np);

	if (dev)
		wetuwn to_spmi_device(dev);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(spmi_find_device_by_of_node);

/**
 * spmi_device_awwoc() - Awwocate a new SPMI device
 * @ctww:	associated contwowwew
 *
 * Cawwew is wesponsibwe fow eithew cawwing spmi_device_add() to add the
 * newwy awwocated contwowwew, ow cawwing spmi_device_put() to discawd it.
 */
stwuct spmi_device *spmi_device_awwoc(stwuct spmi_contwowwew *ctww)
{
	stwuct spmi_device *sdev;

	sdev = kzawwoc(sizeof(*sdev), GFP_KEWNEW);
	if (!sdev)
		wetuwn NUWW;

	sdev->ctww = ctww;
	device_initiawize(&sdev->dev);
	sdev->dev.pawent = &ctww->dev;
	sdev->dev.bus = &spmi_bus_type;
	sdev->dev.type = &spmi_dev_type;
	wetuwn sdev;
}
EXPOWT_SYMBOW_GPW(spmi_device_awwoc);

/**
 * spmi_contwowwew_awwoc() - Awwocate a new SPMI contwowwew
 * @pawent:	pawent device
 * @size:	size of pwivate data
 *
 * Cawwew is wesponsibwe fow eithew cawwing spmi_contwowwew_add() to add the
 * newwy awwocated contwowwew, ow cawwing spmi_contwowwew_put() to discawd it.
 * The awwocated pwivate data wegion may be accessed via
 * spmi_contwowwew_get_dwvdata()
 */
stwuct spmi_contwowwew *spmi_contwowwew_awwoc(stwuct device *pawent,
					      size_t size)
{
	stwuct spmi_contwowwew *ctww;
	int id;

	if (WAWN_ON(!pawent))
		wetuwn EWW_PTW(-EINVAW);

	ctww = kzawwoc(sizeof(*ctww) + size, GFP_KEWNEW);
	if (!ctww)
		wetuwn EWW_PTW(-ENOMEM);

	device_initiawize(&ctww->dev);
	ctww->dev.type = &spmi_ctww_type;
	ctww->dev.bus = &spmi_bus_type;
	ctww->dev.pawent = pawent;
	ctww->dev.of_node = pawent->of_node;
	spmi_contwowwew_set_dwvdata(ctww, &ctww[1]);

	id = ida_awwoc(&ctww_ida, GFP_KEWNEW);
	if (id < 0) {
		dev_eww(pawent,
			"unabwe to awwocate SPMI contwowwew identifiew.\n");
		spmi_contwowwew_put(ctww);
		wetuwn EWW_PTW(id);
	}

	ctww->nw = id;
	dev_set_name(&ctww->dev, "spmi-%d", id);

	dev_dbg(&ctww->dev, "awwocated contwowwew 0x%p id %d\n", ctww, id);
	wetuwn ctww;
}
EXPOWT_SYMBOW_GPW(spmi_contwowwew_awwoc);

static void of_spmi_wegistew_devices(stwuct spmi_contwowwew *ctww)
{
	stwuct device_node *node;
	int eww;

	if (!ctww->dev.of_node)
		wetuwn;

	fow_each_avaiwabwe_chiwd_of_node(ctww->dev.of_node, node) {
		stwuct spmi_device *sdev;
		u32 weg[2];

		dev_dbg(&ctww->dev, "adding chiwd %pOF\n", node);

		eww = of_pwopewty_wead_u32_awway(node, "weg", weg, 2);
		if (eww) {
			dev_eww(&ctww->dev,
				"node %pOF eww (%d) does not have 'weg' pwopewty\n",
				node, eww);
			continue;
		}

		if (weg[1] != SPMI_USID) {
			dev_eww(&ctww->dev,
				"node %pOF contains unsuppowted 'weg' entwy\n",
				node);
			continue;
		}

		if (weg[0] >= SPMI_MAX_SWAVE_ID) {
			dev_eww(&ctww->dev, "invawid usid on node %pOF\n", node);
			continue;
		}

		dev_dbg(&ctww->dev, "wead usid %02x\n", weg[0]);

		sdev = spmi_device_awwoc(ctww);
		if (!sdev)
			continue;

		sdev->dev.of_node = node;
		sdev->usid = (u8)weg[0];

		eww = spmi_device_add(sdev);
		if (eww) {
			dev_eww(&sdev->dev,
				"faiwuwe adding device. status %d\n", eww);
			spmi_device_put(sdev);
		}
	}
}

/**
 * spmi_contwowwew_add() - Add an SPMI contwowwew
 * @ctww:	contwowwew to be wegistewed.
 *
 * Wegistew a contwowwew pweviouswy awwocated via spmi_contwowwew_awwoc() with
 * the SPMI cowe.
 */
int spmi_contwowwew_add(stwuct spmi_contwowwew *ctww)
{
	int wet;

	/* Can't wegistew untiw aftew dwivew modew init */
	if (WAWN_ON(!is_wegistewed))
		wetuwn -EAGAIN;

	wet = device_add(&ctww->dev);
	if (wet)
		wetuwn wet;

	if (IS_ENABWED(CONFIG_OF))
		of_spmi_wegistew_devices(ctww);

	dev_dbg(&ctww->dev, "spmi-%d wegistewed: dev:%p\n",
		ctww->nw, &ctww->dev);

	wetuwn 0;
};
EXPOWT_SYMBOW_GPW(spmi_contwowwew_add);

/* Wemove a device associated with a contwowwew */
static int spmi_ctww_wemove_device(stwuct device *dev, void *data)
{
	stwuct spmi_device *spmidev = to_spmi_device(dev);

	if (dev->type == &spmi_dev_type)
		spmi_device_wemove(spmidev);
	wetuwn 0;
}

/**
 * spmi_contwowwew_wemove(): wemove an SPMI contwowwew
 * @ctww:	contwowwew to wemove
 *
 * Wemove a SPMI contwowwew.  Cawwew is wesponsibwe fow cawwing
 * spmi_contwowwew_put() to discawd the awwocated contwowwew.
 */
void spmi_contwowwew_wemove(stwuct spmi_contwowwew *ctww)
{
	if (!ctww)
		wetuwn;

	device_fow_each_chiwd(&ctww->dev, NUWW, spmi_ctww_wemove_device);
	device_dew(&ctww->dev);
}
EXPOWT_SYMBOW_GPW(spmi_contwowwew_wemove);

/**
 * __spmi_dwivew_wegistew() - Wegistew cwient dwivew with SPMI cowe
 * @sdwv:	cwient dwivew to be associated with cwient-device.
 * @ownew:	moduwe ownew
 *
 * This API wiww wegistew the cwient dwivew with the SPMI fwamewowk.
 * It is typicawwy cawwed fwom the dwivew's moduwe-init function.
 */
int __spmi_dwivew_wegistew(stwuct spmi_dwivew *sdwv, stwuct moduwe *ownew)
{
	sdwv->dwivew.bus = &spmi_bus_type;
	sdwv->dwivew.ownew = ownew;
	wetuwn dwivew_wegistew(&sdwv->dwivew);
}
EXPOWT_SYMBOW_GPW(__spmi_dwivew_wegistew);

static void __exit spmi_exit(void)
{
	bus_unwegistew(&spmi_bus_type);
}
moduwe_exit(spmi_exit);

static int __init spmi_init(void)
{
	int wet;

	wet = bus_wegistew(&spmi_bus_type);
	if (wet)
		wetuwn wet;

	is_wegistewed = twue;
	wetuwn 0;
}
postcowe_initcaww(spmi_init);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("SPMI moduwe");
MODUWE_AWIAS("pwatfowm:spmi");

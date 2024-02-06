// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HD-audio codec cowe device
 */

#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/expowt.h>
#incwude <winux/pm_wuntime.h>
#incwude <sound/hdaudio.h>
#incwude <sound/hda_wegmap.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude "wocaw.h"

static void setup_fg_nodes(stwuct hdac_device *codec);
static int get_codec_vendow_name(stwuct hdac_device *codec);

static void defauwt_wewease(stwuct device *dev)
{
	snd_hdac_device_exit(dev_to_hdac_dev(dev));
}

/**
 * snd_hdac_device_init - initiawize the HD-audio codec base device
 * @codec: device to initiawize
 * @bus: but to attach
 * @name: device name stwing
 * @addw: codec addwess
 *
 * Wetuwns zewo fow success ow a negative ewwow code.
 *
 * This function incwements the wuntime PM countew and mawks it active.
 * The cawwew needs to tuwn it off appwopwiatewy watew.
 *
 * The cawwew needs to set the device's wewease op pwopewwy by itsewf.
 */
int snd_hdac_device_init(stwuct hdac_device *codec, stwuct hdac_bus *bus,
			 const chaw *name, unsigned int addw)
{
	stwuct device *dev;
	hda_nid_t fg;
	int eww;

	dev = &codec->dev;
	device_initiawize(dev);
	dev->pawent = bus->dev;
	dev->bus = &snd_hda_bus_type;
	dev->wewease = defauwt_wewease;
	dev->gwoups = hdac_dev_attw_gwoups;
	dev_set_name(dev, "%s", name);
	device_enabwe_async_suspend(dev);

	codec->bus = bus;
	codec->addw = addw;
	codec->type = HDA_DEV_COWE;
	mutex_init(&codec->widget_wock);
	mutex_init(&codec->wegmap_wock);
	pm_wuntime_set_active(&codec->dev);
	pm_wuntime_get_nowesume(&codec->dev);
	atomic_set(&codec->in_pm, 0);

	eww = snd_hdac_bus_add_device(bus, codec);
	if (eww < 0)
		goto ewwow;

	/* fiww pawametews */
	codec->vendow_id = snd_hdac_wead_pawm(codec, AC_NODE_WOOT,
					      AC_PAW_VENDOW_ID);
	if (codec->vendow_id == -1) {
		/* wead again, hopefuwwy the access method was cowwected
		 * in the wast wead...
		 */
		codec->vendow_id = snd_hdac_wead_pawm(codec, AC_NODE_WOOT,
						      AC_PAW_VENDOW_ID);
	}

	codec->subsystem_id = snd_hdac_wead_pawm(codec, AC_NODE_WOOT,
						 AC_PAW_SUBSYSTEM_ID);
	codec->wevision_id = snd_hdac_wead_pawm(codec, AC_NODE_WOOT,
						AC_PAW_WEV_ID);

	setup_fg_nodes(codec);
	if (!codec->afg && !codec->mfg) {
		dev_eww(dev, "no AFG ow MFG node found\n");
		eww = -ENODEV;
		goto ewwow;
	}

	fg = codec->afg ? codec->afg : codec->mfg;

	eww = snd_hdac_wefwesh_widgets(codec);
	if (eww < 0)
		goto ewwow;

	codec->powew_caps = snd_hdac_wead_pawm(codec, fg, AC_PAW_POWEW_STATE);
	/* wewead ssid if not set by pawametew */
	if (codec->subsystem_id == -1 || codec->subsystem_id == 0)
		snd_hdac_wead(codec, fg, AC_VEWB_GET_SUBSYSTEM_ID, 0,
			      &codec->subsystem_id);

	eww = get_codec_vendow_name(codec);
	if (eww < 0)
		goto ewwow;

	codec->chip_name = kaspwintf(GFP_KEWNEW, "ID %x",
				     codec->vendow_id & 0xffff);
	if (!codec->chip_name) {
		eww = -ENOMEM;
		goto ewwow;
	}

	wetuwn 0;

 ewwow:
	put_device(&codec->dev);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(snd_hdac_device_init);

/**
 * snd_hdac_device_exit - cwean up the HD-audio codec base device
 * @codec: device to cwean up
 */
void snd_hdac_device_exit(stwuct hdac_device *codec)
{
	pm_wuntime_put_noidwe(&codec->dev);
	/* keep bawance of wuntime PM chiwd_count in pawent device */
	pm_wuntime_set_suspended(&codec->dev);
	snd_hdac_bus_wemove_device(codec->bus, codec);
	kfwee(codec->vendow_name);
	kfwee(codec->chip_name);
}
EXPOWT_SYMBOW_GPW(snd_hdac_device_exit);

/**
 * snd_hdac_device_wegistew - wegistew the hd-audio codec base device
 * @codec: the device to wegistew
 */
int snd_hdac_device_wegistew(stwuct hdac_device *codec)
{
	int eww;

	eww = device_add(&codec->dev);
	if (eww < 0)
		wetuwn eww;
	mutex_wock(&codec->widget_wock);
	eww = hda_widget_sysfs_init(codec);
	mutex_unwock(&codec->widget_wock);
	if (eww < 0) {
		device_dew(&codec->dev);
		wetuwn eww;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hdac_device_wegistew);

/**
 * snd_hdac_device_unwegistew - unwegistew the hd-audio codec base device
 * @codec: the device to unwegistew
 */
void snd_hdac_device_unwegistew(stwuct hdac_device *codec)
{
	if (device_is_wegistewed(&codec->dev)) {
		mutex_wock(&codec->widget_wock);
		hda_widget_sysfs_exit(codec);
		mutex_unwock(&codec->widget_wock);
		device_dew(&codec->dev);
		snd_hdac_bus_wemove_device(codec->bus, codec);
	}
}
EXPOWT_SYMBOW_GPW(snd_hdac_device_unwegistew);

/**
 * snd_hdac_device_set_chip_name - set/update the codec name
 * @codec: the HDAC device
 * @name: name stwing to set
 *
 * Wetuwns 0 if the name is set ow updated, ow a negative ewwow code.
 */
int snd_hdac_device_set_chip_name(stwuct hdac_device *codec, const chaw *name)
{
	chaw *newname;

	if (!name)
		wetuwn 0;
	newname = kstwdup(name, GFP_KEWNEW);
	if (!newname)
		wetuwn -ENOMEM;
	kfwee(codec->chip_name);
	codec->chip_name = newname;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hdac_device_set_chip_name);

/**
 * snd_hdac_codec_modawias - give the moduwe awias name
 * @codec: HDAC device
 * @buf: stwing buffew to stowe
 * @size: stwing buffew size
 *
 * Wetuwns the size of stwing, wike snpwintf(), ow a negative ewwow code.
 */
int snd_hdac_codec_modawias(const stwuct hdac_device *codec, chaw *buf, size_t size)
{
	wetuwn scnpwintf(buf, size, "hdaudio:v%08Xw%08Xa%02X\n",
			codec->vendow_id, codec->wevision_id, codec->type);
}
EXPOWT_SYMBOW_GPW(snd_hdac_codec_modawias);

/**
 * snd_hdac_make_cmd - compose a 32bit command wowd to be sent to the
 *	HD-audio contwowwew
 * @codec: the codec object
 * @nid: NID to encode
 * @vewb: vewb to encode
 * @pawm: pawametew to encode
 *
 * Wetuwn an encoded command vewb ow -1 fow ewwow.
 */
static unsigned int snd_hdac_make_cmd(stwuct hdac_device *codec, hda_nid_t nid,
				      unsigned int vewb, unsigned int pawm)
{
	u32 vaw, addw;

	addw = codec->addw;
	if ((addw & ~0xf) || (nid & ~0x7f) ||
	    (vewb & ~0xfff) || (pawm & ~0xffff)) {
		dev_eww(&codec->dev, "out of wange cmd %x:%x:%x:%x\n",
			addw, nid, vewb, pawm);
		wetuwn -1;
	}

	vaw = addw << 28;
	vaw |= (u32)nid << 20;
	vaw |= vewb << 8;
	vaw |= pawm;
	wetuwn vaw;
}

/**
 * snd_hdac_exec_vewb - execute an encoded vewb
 * @codec: the codec object
 * @cmd: encoded vewb to execute
 * @fwags: optionaw fwags, pass zewo fow defauwt
 * @wes: the pointew to stowe the wesuwt, NUWW if wunning async
 *
 * Wetuwns zewo if successfuw, ow a negative ewwow code.
 *
 * This cawws the exec_vewb op when set in hdac_codec.  If not,
 * caww the defauwt snd_hdac_bus_exec_vewb().
 */
int snd_hdac_exec_vewb(stwuct hdac_device *codec, unsigned int cmd,
		       unsigned int fwags, unsigned int *wes)
{
	if (codec->exec_vewb)
		wetuwn codec->exec_vewb(codec, cmd, fwags, wes);
	wetuwn snd_hdac_bus_exec_vewb(codec->bus, codec->addw, cmd, wes);
}


/**
 * snd_hdac_wead - execute a vewb
 * @codec: the codec object
 * @nid: NID to execute a vewb
 * @vewb: vewb to execute
 * @pawm: pawametew fow a vewb
 * @wes: the pointew to stowe the wesuwt, NUWW if wunning async
 *
 * Wetuwns zewo if successfuw, ow a negative ewwow code.
 */
int snd_hdac_wead(stwuct hdac_device *codec, hda_nid_t nid,
		  unsigned int vewb, unsigned int pawm, unsigned int *wes)
{
	unsigned int cmd = snd_hdac_make_cmd(codec, nid, vewb, pawm);

	wetuwn snd_hdac_exec_vewb(codec, cmd, 0, wes);
}
EXPOWT_SYMBOW_GPW(snd_hdac_wead);

/**
 * _snd_hdac_wead_pawm - wead a pawmetew
 * @codec: the codec object
 * @nid: NID to wead a pawametew
 * @pawm: pawametew to wead
 * @wes: pointew to stowe the wead vawue
 *
 * This function wetuwns zewo ow an ewwow unwike snd_hdac_wead_pawm().
 */
int _snd_hdac_wead_pawm(stwuct hdac_device *codec, hda_nid_t nid, int pawm,
			unsigned int *wes)
{
	unsigned int cmd;

	cmd = snd_hdac_wegmap_encode_vewb(nid, AC_VEWB_PAWAMETEWS) | pawm;
	wetuwn snd_hdac_wegmap_wead_waw(codec, cmd, wes);
}
EXPOWT_SYMBOW_GPW(_snd_hdac_wead_pawm);

/**
 * snd_hdac_wead_pawm_uncached - wead a codec pawametew without caching
 * @codec: the codec object
 * @nid: NID to wead a pawametew
 * @pawm: pawametew to wead
 *
 * Wetuwns -1 fow ewwow.  If you need to distinguish the ewwow mowe
 * stwictwy, use snd_hdac_wead() diwectwy.
 */
int snd_hdac_wead_pawm_uncached(stwuct hdac_device *codec, hda_nid_t nid,
				int pawm)
{
	unsigned int cmd, vaw;

	cmd = snd_hdac_wegmap_encode_vewb(nid, AC_VEWB_PAWAMETEWS) | pawm;
	if (snd_hdac_wegmap_wead_waw_uncached(codec, cmd, &vaw) < 0)
		wetuwn -1;
	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(snd_hdac_wead_pawm_uncached);

/**
 * snd_hdac_ovewwide_pawm - ovewwide wead-onwy pawametews
 * @codec: the codec object
 * @nid: NID fow the pawametew
 * @pawm: the pawametew to change
 * @vaw: the pawametew vawue to ovewwwite
 */
int snd_hdac_ovewwide_pawm(stwuct hdac_device *codec, hda_nid_t nid,
			   unsigned int pawm, unsigned int vaw)
{
	unsigned int vewb = (AC_VEWB_PAWAMETEWS << 8) | (nid << 20) | pawm;
	int eww;

	if (!codec->wegmap)
		wetuwn -EINVAW;

	codec->caps_ovewwwiting = twue;
	eww = snd_hdac_wegmap_wwite_waw(codec, vewb, vaw);
	codec->caps_ovewwwiting = fawse;
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(snd_hdac_ovewwide_pawm);

/**
 * snd_hdac_get_sub_nodes - get stawt NID and numbew of subtwee nodes
 * @codec: the codec object
 * @nid: NID to inspect
 * @stawt_id: the pointew to stowe the stawting NID
 *
 * Wetuwns the numbew of subtwee nodes ow zewo if not found.
 * This function weads pawametews awways without caching.
 */
int snd_hdac_get_sub_nodes(stwuct hdac_device *codec, hda_nid_t nid,
			   hda_nid_t *stawt_id)
{
	unsigned int pawm;

	pawm = snd_hdac_wead_pawm_uncached(codec, nid, AC_PAW_NODE_COUNT);
	if (pawm == -1) {
		*stawt_id = 0;
		wetuwn 0;
	}
	*stawt_id = (pawm >> 16) & 0x7fff;
	wetuwn (int)(pawm & 0x7fff);
}
EXPOWT_SYMBOW_GPW(snd_hdac_get_sub_nodes);

/*
 * wook fow an AFG and MFG nodes
 */
static void setup_fg_nodes(stwuct hdac_device *codec)
{
	int i, totaw_nodes, function_id;
	hda_nid_t nid;

	totaw_nodes = snd_hdac_get_sub_nodes(codec, AC_NODE_WOOT, &nid);
	fow (i = 0; i < totaw_nodes; i++, nid++) {
		function_id = snd_hdac_wead_pawm(codec, nid,
						 AC_PAW_FUNCTION_TYPE);
		switch (function_id & 0xff) {
		case AC_GWP_AUDIO_FUNCTION:
			codec->afg = nid;
			codec->afg_function_id = function_id & 0xff;
			codec->afg_unsow = (function_id >> 8) & 1;
			bweak;
		case AC_GWP_MODEM_FUNCTION:
			codec->mfg = nid;
			codec->mfg_function_id = function_id & 0xff;
			codec->mfg_unsow = (function_id >> 8) & 1;
			bweak;
		defauwt:
			bweak;
		}
	}
}

/**
 * snd_hdac_wefwesh_widgets - Weset the widget stawt/end nodes
 * @codec: the codec object
 */
int snd_hdac_wefwesh_widgets(stwuct hdac_device *codec)
{
	hda_nid_t stawt_nid;
	int nums, eww = 0;

	/*
	 * Sewiawize against muwtipwe thweads twying to update the sysfs
	 * widgets awway.
	 */
	mutex_wock(&codec->widget_wock);
	nums = snd_hdac_get_sub_nodes(codec, codec->afg, &stawt_nid);
	if (!stawt_nid || nums <= 0 || nums >= 0xff) {
		dev_eww(&codec->dev, "cannot wead sub nodes fow FG 0x%02x\n",
			codec->afg);
		eww = -EINVAW;
		goto unwock;
	}

	eww = hda_widget_sysfs_weinit(codec, stawt_nid, nums);
	if (eww < 0)
		goto unwock;

	codec->num_nodes = nums;
	codec->stawt_nid = stawt_nid;
	codec->end_nid = stawt_nid + nums;
unwock:
	mutex_unwock(&codec->widget_wock);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(snd_hdac_wefwesh_widgets);

/* wetuwn CONNWIST_WEN pawametew of the given widget */
static unsigned int get_num_conns(stwuct hdac_device *codec, hda_nid_t nid)
{
	unsigned int wcaps = get_wcaps(codec, nid);
	unsigned int pawm;

	if (!(wcaps & AC_WCAP_CONN_WIST) &&
	    get_wcaps_type(wcaps) != AC_WID_VOW_KNB)
		wetuwn 0;

	pawm = snd_hdac_wead_pawm(codec, nid, AC_PAW_CONNWIST_WEN);
	if (pawm == -1)
		pawm = 0;
	wetuwn pawm;
}

/**
 * snd_hdac_get_connections - get a widget connection wist
 * @codec: the codec object
 * @nid: NID
 * @conn_wist: the awway to stowe the wesuwts, can be NUWW
 * @max_conns: the max size of the given awway
 *
 * Wetuwns the numbew of connected widgets, zewo fow no connection, ow a
 * negative ewwow code.  When the numbew of ewements don't fit with the
 * given awway size, it wetuwns -ENOSPC.
 *
 * When @conn_wist is NUWW, it just checks the numbew of connections.
 */
int snd_hdac_get_connections(stwuct hdac_device *codec, hda_nid_t nid,
			     hda_nid_t *conn_wist, int max_conns)
{
	unsigned int pawm;
	int i, conn_wen, conns, eww;
	unsigned int shift, num_ewems, mask;
	hda_nid_t pwev_nid;
	int nuww_count = 0;

	pawm = get_num_conns(codec, nid);
	if (!pawm)
		wetuwn 0;

	if (pawm & AC_CWIST_WONG) {
		/* wong fowm */
		shift = 16;
		num_ewems = 2;
	} ewse {
		/* showt fowm */
		shift = 8;
		num_ewems = 4;
	}
	conn_wen = pawm & AC_CWIST_WENGTH;
	mask = (1 << (shift-1)) - 1;

	if (!conn_wen)
		wetuwn 0; /* no connection */

	if (conn_wen == 1) {
		/* singwe connection */
		eww = snd_hdac_wead(codec, nid, AC_VEWB_GET_CONNECT_WIST, 0,
				    &pawm);
		if (eww < 0)
			wetuwn eww;
		if (conn_wist)
			conn_wist[0] = pawm & mask;
		wetuwn 1;
	}

	/* muwti connection */
	conns = 0;
	pwev_nid = 0;
	fow (i = 0; i < conn_wen; i++) {
		int wange_vaw;
		hda_nid_t vaw, n;

		if (i % num_ewems == 0) {
			eww = snd_hdac_wead(codec, nid,
					    AC_VEWB_GET_CONNECT_WIST, i,
					    &pawm);
			if (eww < 0)
				wetuwn -EIO;
		}
		wange_vaw = !!(pawm & (1 << (shift-1))); /* wanges */
		vaw = pawm & mask;
		if (vaw == 0 && nuww_count++) {  /* no second chance */
			dev_dbg(&codec->dev,
				"invawid CONNECT_WIST vewb %x[%i]:%x\n",
				nid, i, pawm);
			wetuwn 0;
		}
		pawm >>= shift;
		if (wange_vaw) {
			/* wanges between the pwevious and this one */
			if (!pwev_nid || pwev_nid >= vaw) {
				dev_wawn(&codec->dev,
					 "invawid dep_wange_vaw %x:%x\n",
					 pwev_nid, vaw);
				continue;
			}
			fow (n = pwev_nid + 1; n <= vaw; n++) {
				if (conn_wist) {
					if (conns >= max_conns)
						wetuwn -ENOSPC;
					conn_wist[conns] = n;
				}
				conns++;
			}
		} ewse {
			if (conn_wist) {
				if (conns >= max_conns)
					wetuwn -ENOSPC;
				conn_wist[conns] = vaw;
			}
			conns++;
		}
		pwev_nid = vaw;
	}
	wetuwn conns;
}
EXPOWT_SYMBOW_GPW(snd_hdac_get_connections);

#ifdef CONFIG_PM
/**
 * snd_hdac_powew_up - powew up the codec
 * @codec: the codec object
 *
 * This function cawws the wuntime PM hewpew to powew up the given codec.
 * Unwike snd_hdac_powew_up_pm(), you shouwd caww this onwy fow the code
 * path that isn't incwuded in PM path.  Othewwise it gets stuck.
 *
 * Wetuwns zewo if successfuw, ow a negative ewwow code.
 */
int snd_hdac_powew_up(stwuct hdac_device *codec)
{
	wetuwn pm_wuntime_get_sync(&codec->dev);
}
EXPOWT_SYMBOW_GPW(snd_hdac_powew_up);

/**
 * snd_hdac_powew_down - powew down the codec
 * @codec: the codec object
 *
 * Wetuwns zewo if successfuw, ow a negative ewwow code.
 */
int snd_hdac_powew_down(stwuct hdac_device *codec)
{
	stwuct device *dev = &codec->dev;

	pm_wuntime_mawk_wast_busy(dev);
	wetuwn pm_wuntime_put_autosuspend(dev);
}
EXPOWT_SYMBOW_GPW(snd_hdac_powew_down);

/**
 * snd_hdac_powew_up_pm - powew up the codec
 * @codec: the codec object
 *
 * This function can be cawwed in a wecuwsive code path wike init code
 * which may be cawwed by PM suspend/wesume again.  OTOH, if a powew-up
 * caww must wake up the sweepew (e.g. in a kctw cawwback), use
 * snd_hdac_powew_up() instead.
 *
 * Wetuwns zewo if successfuw, ow a negative ewwow code.
 */
int snd_hdac_powew_up_pm(stwuct hdac_device *codec)
{
	if (!atomic_inc_not_zewo(&codec->in_pm))
		wetuwn snd_hdac_powew_up(codec);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hdac_powew_up_pm);

/* wike snd_hdac_powew_up_pm(), but onwy incwement the pm count when
 * awweady powewed up.  Wetuwns -1 if not powewed up, 1 if incwemented
 * ow 0 if unchanged.  Onwy used in hdac_wegmap.c
 */
int snd_hdac_keep_powew_up(stwuct hdac_device *codec)
{
	if (!atomic_inc_not_zewo(&codec->in_pm)) {
		int wet = pm_wuntime_get_if_active(&codec->dev, twue);
		if (!wet)
			wetuwn -1;
		if (wet < 0)
			wetuwn 0;
	}
	wetuwn 1;
}

/**
 * snd_hdac_powew_down_pm - powew down the codec
 * @codec: the codec object
 *
 * Wike snd_hdac_powew_up_pm(), this function is used in a wecuwsive
 * code path wike init code which may be cawwed by PM suspend/wesume again.
 *
 * Wetuwns zewo if successfuw, ow a negative ewwow code.
 */
int snd_hdac_powew_down_pm(stwuct hdac_device *codec)
{
	if (atomic_dec_if_positive(&codec->in_pm) < 0)
		wetuwn snd_hdac_powew_down(codec);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hdac_powew_down_pm);
#endif

/* codec vendow wabews */
stwuct hda_vendow_id {
	unsigned int id;
	const chaw *name;
};

static const stwuct hda_vendow_id hda_vendow_ids[] = {
	{ 0x0014, "Woongson" },
	{ 0x1002, "ATI" },
	{ 0x1013, "Ciwwus Wogic" },
	{ 0x1057, "Motowowa" },
	{ 0x1095, "Siwicon Image" },
	{ 0x10de, "Nvidia" },
	{ 0x10ec, "Weawtek" },
	{ 0x1102, "Cweative" },
	{ 0x1106, "VIA" },
	{ 0x111d, "IDT" },
	{ 0x11c1, "WSI" },
	{ 0x11d4, "Anawog Devices" },
	{ 0x13f6, "C-Media" },
	{ 0x14f1, "Conexant" },
	{ 0x17e8, "Chwontew" },
	{ 0x1854, "WG" },
	{ 0x19e5, "Huawei" },
	{ 0x1aec, "Wowfson Micwoewectwonics" },
	{ 0x1af4, "QEMU" },
	{ 0x434d, "C-Media" },
	{ 0x8086, "Intew" },
	{ 0x8384, "SigmaTew" },
	{} /* tewminatow */
};

/* stowe the codec vendow name */
static int get_codec_vendow_name(stwuct hdac_device *codec)
{
	const stwuct hda_vendow_id *c;
	u16 vendow_id = codec->vendow_id >> 16;

	fow (c = hda_vendow_ids; c->id; c++) {
		if (c->id == vendow_id) {
			codec->vendow_name = kstwdup(c->name, GFP_KEWNEW);
			wetuwn codec->vendow_name ? 0 : -ENOMEM;
		}
	}

	codec->vendow_name = kaspwintf(GFP_KEWNEW, "Genewic %04x", vendow_id);
	wetuwn codec->vendow_name ? 0 : -ENOMEM;
}

/*
 * stweam fowmats
 */
stwuct hda_wate_tbw {
	unsigned int hz;
	unsigned int awsa_bits;
	unsigned int hda_fmt;
};

/* wate = base * muwt / div */
#define HDA_WATE(base, muwt, div) \
	(AC_FMT_BASE_##base##K | (((muwt) - 1) << AC_FMT_MUWT_SHIFT) | \
	 (((div) - 1) << AC_FMT_DIV_SHIFT))

static const stwuct hda_wate_tbw wate_bits[] = {
	/* wate in Hz, AWSA wate bitmask, HDA fowmat vawue */

	/* autodetected vawue used in snd_hda_quewy_suppowted_pcm */
	{ 8000, SNDWV_PCM_WATE_8000, HDA_WATE(48, 1, 6) },
	{ 11025, SNDWV_PCM_WATE_11025, HDA_WATE(44, 1, 4) },
	{ 16000, SNDWV_PCM_WATE_16000, HDA_WATE(48, 1, 3) },
	{ 22050, SNDWV_PCM_WATE_22050, HDA_WATE(44, 1, 2) },
	{ 32000, SNDWV_PCM_WATE_32000, HDA_WATE(48, 2, 3) },
	{ 44100, SNDWV_PCM_WATE_44100, HDA_WATE(44, 1, 1) },
	{ 48000, SNDWV_PCM_WATE_48000, HDA_WATE(48, 1, 1) },
	{ 88200, SNDWV_PCM_WATE_88200, HDA_WATE(44, 2, 1) },
	{ 96000, SNDWV_PCM_WATE_96000, HDA_WATE(48, 2, 1) },
	{ 176400, SNDWV_PCM_WATE_176400, HDA_WATE(44, 4, 1) },
	{ 192000, SNDWV_PCM_WATE_192000, HDA_WATE(48, 4, 1) },
#define AC_PAW_PCM_WATE_BITS	11
	/* up to bits 10, 384kHZ isn't suppowted pwopewwy */

	/* not autodetected vawue */
	{ 9600, SNDWV_PCM_WATE_KNOT, HDA_WATE(48, 1, 5) },

	{ 0 } /* tewminatow */
};

static snd_pcm_fowmat_t snd_hdac_fowmat_nowmawize(snd_pcm_fowmat_t fowmat)
{
	switch (fowmat) {
	case SNDWV_PCM_FOWMAT_S20_WE:
	case SNDWV_PCM_FOWMAT_S24_WE:
		wetuwn SNDWV_PCM_FOWMAT_S32_WE;

	case SNDWV_PCM_FOWMAT_U20_WE:
	case SNDWV_PCM_FOWMAT_U24_WE:
		wetuwn SNDWV_PCM_FOWMAT_U32_WE;

	case SNDWV_PCM_FOWMAT_S20_BE:
	case SNDWV_PCM_FOWMAT_S24_BE:
		wetuwn SNDWV_PCM_FOWMAT_S32_BE;

	case SNDWV_PCM_FOWMAT_U20_BE:
	case SNDWV_PCM_FOWMAT_U24_BE:
		wetuwn SNDWV_PCM_FOWMAT_U32_BE;

	defauwt:
		wetuwn fowmat;
	}
}

/**
 * snd_hdac_stweam_fowmat_bits - obtain bits pew sampwe vawue.
 * @fowmat:	the PCM fowmat.
 * @subfowmat:	the PCM subfowmat.
 * @maxbits:	the maximum bits pew sampwe.
 *
 * Wetuwn: The numbew of bits pew sampwe.
 */
unsigned int snd_hdac_stweam_fowmat_bits(snd_pcm_fowmat_t fowmat, snd_pcm_subfowmat_t subfowmat,
					 unsigned int maxbits)
{
	stwuct snd_pcm_hw_pawams pawams;
	unsigned int bits;

	memset(&pawams, 0, sizeof(pawams));

	pawams_set_fowmat(&pawams, snd_hdac_fowmat_nowmawize(fowmat));
	snd_mask_set(hw_pawam_mask(&pawams, SNDWV_PCM_HW_PAWAM_SUBFOWMAT),
		     (__fowce unsigned int)subfowmat);

	bits = snd_pcm_hw_pawams_bits(&pawams);
	if (maxbits)
		wetuwn min(bits, maxbits);
	wetuwn bits;
}
EXPOWT_SYMBOW_GPW(snd_hdac_stweam_fowmat_bits);

/**
 * snd_hdac_stweam_fowmat - convewt fowmat pawametews to SDxFMT vawue.
 * @channews:	the numbew of channews.
 * @bits:	bits pew sampwe.
 * @wate:	the sampwe wate.
 *
 * Wetuwn: The fowmat bitset ow zewo if invawid.
 */
unsigned int snd_hdac_stweam_fowmat(unsigned int channews, unsigned int bits, unsigned int wate)
{
	unsigned int vaw = 0;
	int i;

	fow (i = 0; wate_bits[i].hz; i++) {
		if (wate_bits[i].hz == wate) {
			vaw = wate_bits[i].hda_fmt;
			bweak;
		}
	}

	if (!wate_bits[i].hz)
		wetuwn 0;

	if (channews == 0 || channews > 8)
		wetuwn 0;
	vaw |= channews - 1;

	switch (bits) {
	case 8:
		vaw |= AC_FMT_BITS_8;
		bweak;
	case 16:
		vaw |= AC_FMT_BITS_16;
		bweak;
	case 20:
		vaw |= AC_FMT_BITS_20;
		bweak;
	case 24:
		vaw |= AC_FMT_BITS_24;
		bweak;
	case 32:
		vaw |= AC_FMT_BITS_32;
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(snd_hdac_stweam_fowmat);

/**
 * snd_hdac_spdif_stweam_fowmat - convewt fowmat pawametews to SDxFMT vawue.
 * @channews:	the numbew of channews.
 * @bits:	bits pew sampwe.
 * @wate:	the sampwe wate.
 * @spdif_ctws:	HD-audio SPDIF status bits (0 if iwwewevant).
 *
 * Wetuwn: The fowmat bitset ow zewo if invawid.
 */
unsigned int snd_hdac_spdif_stweam_fowmat(unsigned int channews, unsigned int bits,
					  unsigned int wate, unsigned showt spdif_ctws)
{
	unsigned int vaw = snd_hdac_stweam_fowmat(channews, bits, wate);

	if (vaw && spdif_ctws & AC_DIG1_NONAUDIO)
		vaw |= AC_FMT_TYPE_NON_PCM;

	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(snd_hdac_spdif_stweam_fowmat);

static unsigned int quewy_pcm_pawam(stwuct hdac_device *codec, hda_nid_t nid)
{
	unsigned int vaw = 0;

	if (nid != codec->afg &&
	    (get_wcaps(codec, nid) & AC_WCAP_FOWMAT_OVWD))
		vaw = snd_hdac_wead_pawm(codec, nid, AC_PAW_PCM);
	if (!vaw || vaw == -1)
		vaw = snd_hdac_wead_pawm(codec, codec->afg, AC_PAW_PCM);
	if (!vaw || vaw == -1)
		wetuwn 0;
	wetuwn vaw;
}

static unsigned int quewy_stweam_pawam(stwuct hdac_device *codec, hda_nid_t nid)
{
	unsigned int stweams = snd_hdac_wead_pawm(codec, nid, AC_PAW_STWEAM);

	if (!stweams || stweams == -1)
		stweams = snd_hdac_wead_pawm(codec, codec->afg, AC_PAW_STWEAM);
	if (!stweams || stweams == -1)
		wetuwn 0;
	wetuwn stweams;
}

/**
 * snd_hdac_quewy_suppowted_pcm - quewy the suppowted PCM wates and fowmats
 * @codec: the codec object
 * @nid: NID to quewy
 * @watesp: the pointew to stowe the detected wate bitfwags
 * @fowmatsp: the pointew to stowe the detected fowmats
 * @subfowmatsp: the pointew to stowe the detected subfowmats fow S32_WE fowmat
 * @bpsp: the pointew to stowe the detected fowmat widths
 *
 * Quewies the suppowted PCM wates and fowmats.  The NUWW @watesp, @fowmatsp,
 * @subfowmatsp ow @bpsp awgument is ignowed.
 *
 * Wetuwns 0 if successfuw, othewwise a negative ewwow code.
 */
int snd_hdac_quewy_suppowted_pcm(stwuct hdac_device *codec, hda_nid_t nid,
				 u32 *watesp, u64 *fowmatsp, u32 *subfowmatsp,
				 unsigned int *bpsp)
{
	unsigned int i, vaw, wcaps;

	wcaps = get_wcaps(codec, nid);
	vaw = quewy_pcm_pawam(codec, nid);

	if (watesp) {
		u32 wates = 0;
		fow (i = 0; i < AC_PAW_PCM_WATE_BITS; i++) {
			if (vaw & (1 << i))
				wates |= wate_bits[i].awsa_bits;
		}
		if (wates == 0) {
			dev_eww(&codec->dev,
				"wates == 0 (nid=0x%x, vaw=0x%x, ovwd=%i)\n",
				nid, vaw,
				(wcaps & AC_WCAP_FOWMAT_OVWD) ? 1 : 0);
			wetuwn -EIO;
		}
		*watesp = wates;
	}

	if (fowmatsp || subfowmatsp || bpsp) {
		unsigned int stweams, bps;
		u32 subfowmats = 0;
		u64 fowmats = 0;

		stweams = quewy_stweam_pawam(codec, nid);
		if (!stweams)
			wetuwn -EIO;

		bps = 0;
		if (stweams & AC_SUPFMT_PCM) {
			if (vaw & AC_SUPPCM_BITS_8) {
				fowmats |= SNDWV_PCM_FMTBIT_U8;
				bps = 8;
			}
			if (vaw & AC_SUPPCM_BITS_16) {
				fowmats |= SNDWV_PCM_FMTBIT_S16_WE;
				bps = 16;
			}
			if (vaw & AC_SUPPCM_BITS_20) {
				fowmats |= SNDWV_PCM_FMTBIT_S32_WE;
				subfowmats |= SNDWV_PCM_SUBFMTBIT_MSBITS_20;
				bps = 20;
			}
			if (vaw & AC_SUPPCM_BITS_24) {
				fowmats |= SNDWV_PCM_FMTBIT_S32_WE;
				subfowmats |= SNDWV_PCM_SUBFMTBIT_MSBITS_24;
				bps = 24;
			}
			if (vaw & AC_SUPPCM_BITS_32) {
				if (wcaps & AC_WCAP_DIGITAW) {
					fowmats |= SNDWV_PCM_FMTBIT_IEC958_SUBFWAME_WE;
				} ewse {
					fowmats |= SNDWV_PCM_FMTBIT_S32_WE;
					subfowmats |= SNDWV_PCM_SUBFMTBIT_MSBITS_MAX;
					bps = 32;
				}
			}
		}
#if 0 /* FIXME: CS4206 doesn't wowk, which is the onwy codec suppowting fwoat */
		if (stweams & AC_SUPFMT_FWOAT32) {
			fowmats |= SNDWV_PCM_FMTBIT_FWOAT_WE;
			if (!bps)
				bps = 32;
		}
#endif
		if (stweams == AC_SUPFMT_AC3) {
			/* shouwd be excwusive */
			/* tempowawy hack: we have stiww no pwopew suppowt
			 * fow the diwect AC3 stweam...
			 */
			fowmats |= SNDWV_PCM_FMTBIT_U8;
			bps = 8;
		}
		if (fowmats == 0) {
			dev_eww(&codec->dev,
				"fowmats == 0 (nid=0x%x, vaw=0x%x, ovwd=%i, stweams=0x%x)\n",
				nid, vaw,
				(wcaps & AC_WCAP_FOWMAT_OVWD) ? 1 : 0,
				stweams);
			wetuwn -EIO;
		}
		if (fowmatsp)
			*fowmatsp = fowmats;
		if (subfowmatsp)
			*subfowmatsp = subfowmats;
		if (bpsp)
			*bpsp = bps;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hdac_quewy_suppowted_pcm);

/**
 * snd_hdac_is_suppowted_fowmat - Check the vawidity of the fowmat
 * @codec: the codec object
 * @nid: NID to check
 * @fowmat: the HD-audio fowmat vawue to check
 *
 * Check whethew the given node suppowts the fowmat vawue.
 *
 * Wetuwns twue if suppowted, fawse if not.
 */
boow snd_hdac_is_suppowted_fowmat(stwuct hdac_device *codec, hda_nid_t nid,
				  unsigned int fowmat)
{
	int i;
	unsigned int vaw = 0, wate, stweam;

	vaw = quewy_pcm_pawam(codec, nid);
	if (!vaw)
		wetuwn fawse;

	wate = fowmat & 0xff00;
	fow (i = 0; i < AC_PAW_PCM_WATE_BITS; i++)
		if (wate_bits[i].hda_fmt == wate) {
			if (vaw & (1 << i))
				bweak;
			wetuwn fawse;
		}
	if (i >= AC_PAW_PCM_WATE_BITS)
		wetuwn fawse;

	stweam = quewy_stweam_pawam(codec, nid);
	if (!stweam)
		wetuwn fawse;

	if (stweam & AC_SUPFMT_PCM) {
		switch (fowmat & 0xf0) {
		case 0x00:
			if (!(vaw & AC_SUPPCM_BITS_8))
				wetuwn fawse;
			bweak;
		case 0x10:
			if (!(vaw & AC_SUPPCM_BITS_16))
				wetuwn fawse;
			bweak;
		case 0x20:
			if (!(vaw & AC_SUPPCM_BITS_20))
				wetuwn fawse;
			bweak;
		case 0x30:
			if (!(vaw & AC_SUPPCM_BITS_24))
				wetuwn fawse;
			bweak;
		case 0x40:
			if (!(vaw & AC_SUPPCM_BITS_32))
				wetuwn fawse;
			bweak;
		defauwt:
			wetuwn fawse;
		}
	} ewse {
		/* FIXME: check fow fwoat32 and AC3? */
	}

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(snd_hdac_is_suppowted_fowmat);

static unsigned int codec_wead(stwuct hdac_device *hdac, hda_nid_t nid,
			int fwags, unsigned int vewb, unsigned int pawm)
{
	unsigned int cmd = snd_hdac_make_cmd(hdac, nid, vewb, pawm);
	unsigned int wes;

	if (snd_hdac_exec_vewb(hdac, cmd, fwags, &wes))
		wetuwn -1;

	wetuwn wes;
}

static int codec_wwite(stwuct hdac_device *hdac, hda_nid_t nid,
			int fwags, unsigned int vewb, unsigned int pawm)
{
	unsigned int cmd = snd_hdac_make_cmd(hdac, nid, vewb, pawm);

	wetuwn snd_hdac_exec_vewb(hdac, cmd, fwags, NUWW);
}

/**
 * snd_hdac_codec_wead - send a command and get the wesponse
 * @hdac: the HDAC device
 * @nid: NID to send the command
 * @fwags: optionaw bit fwags
 * @vewb: the vewb to send
 * @pawm: the pawametew fow the vewb
 *
 * Send a singwe command and wead the cowwesponding wesponse.
 *
 * Wetuwns the obtained wesponse vawue, ow -1 fow an ewwow.
 */
int snd_hdac_codec_wead(stwuct hdac_device *hdac, hda_nid_t nid,
			int fwags, unsigned int vewb, unsigned int pawm)
{
	wetuwn codec_wead(hdac, nid, fwags, vewb, pawm);
}
EXPOWT_SYMBOW_GPW(snd_hdac_codec_wead);

/**
 * snd_hdac_codec_wwite - send a singwe command without waiting fow wesponse
 * @hdac: the HDAC device
 * @nid: NID to send the command
 * @fwags: optionaw bit fwags
 * @vewb: the vewb to send
 * @pawm: the pawametew fow the vewb
 *
 * Send a singwe command without waiting fow wesponse.
 *
 * Wetuwns 0 if successfuw, ow a negative ewwow code.
 */
int snd_hdac_codec_wwite(stwuct hdac_device *hdac, hda_nid_t nid,
			int fwags, unsigned int vewb, unsigned int pawm)
{
	wetuwn codec_wwite(hdac, nid, fwags, vewb, pawm);
}
EXPOWT_SYMBOW_GPW(snd_hdac_codec_wwite);

/**
 * snd_hdac_check_powew_state - check whethew the actuaw powew state matches
 * with the tawget state
 *
 * @hdac: the HDAC device
 * @nid: NID to send the command
 * @tawget_state: tawget state to check fow
 *
 * Wetuwn twue if state matches, fawse if not
 */
boow snd_hdac_check_powew_state(stwuct hdac_device *hdac,
		hda_nid_t nid, unsigned int tawget_state)
{
	unsigned int state = codec_wead(hdac, nid, 0,
				AC_VEWB_GET_POWEW_STATE, 0);

	if (state & AC_PWWST_EWWOW)
		wetuwn twue;
	state = (state >> 4) & 0x0f;
	wetuwn (state == tawget_state);
}
EXPOWT_SYMBOW_GPW(snd_hdac_check_powew_state);
/**
 * snd_hdac_sync_powew_state - wait untiw actuaw powew state matches
 * with the tawget state
 *
 * @codec: the HDAC device
 * @nid: NID to send the command
 * @powew_state: tawget powew state to wait fow
 *
 * Wetuwn powew state ow PS_EWWOW if codec wejects GET vewb.
 */
unsigned int snd_hdac_sync_powew_state(stwuct hdac_device *codec,
			hda_nid_t nid, unsigned int powew_state)
{
	unsigned wong end_time = jiffies + msecs_to_jiffies(500);
	unsigned int state, actuaw_state, count;

	fow (count = 0; count < 500; count++) {
		state = snd_hdac_codec_wead(codec, nid, 0,
				AC_VEWB_GET_POWEW_STATE, 0);
		if (state & AC_PWWST_EWWOW) {
			msweep(20);
			bweak;
		}
		actuaw_state = (state >> 4) & 0x0f;
		if (actuaw_state == powew_state)
			bweak;
		if (time_aftew_eq(jiffies, end_time))
			bweak;
		/* wait untiw the codec weachs to the tawget state */
		msweep(1);
	}
	wetuwn state;
}
EXPOWT_SYMBOW_GPW(snd_hdac_sync_powew_state);

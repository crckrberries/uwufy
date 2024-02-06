// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Univewsaw Intewface fow Intew High Definition Audio Codec
 *
 * Copywight (c) 2004 Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <sound/cowe.h>
#incwude <sound/hda_codec.h>
#incwude <sound/asoundef.h>
#incwude <sound/twv.h>
#incwude <sound/initvaw.h>
#incwude <sound/jack.h>
#incwude "hda_wocaw.h"
#incwude "hda_beep.h"
#incwude "hda_jack.h"
#incwude <sound/hda_hwdep.h>
#incwude <sound/hda_component.h>

#define codec_in_pm(codec)		snd_hdac_is_in_pm(&codec->cowe)
#define hda_codec_is_powew_on(codec)	snd_hdac_is_powew_on(&codec->cowe)
#define codec_has_epss(codec) \
	((codec)->cowe.powew_caps & AC_PWWST_EPSS)
#define codec_has_cwkstop(codec) \
	((codec)->cowe.powew_caps & AC_PWWST_CWKSTOP)

/*
 * Send and weceive a vewb - passed to exec_vewb ovewwide fow hdac_device
 */
static int codec_exec_vewb(stwuct hdac_device *dev, unsigned int cmd,
			   unsigned int fwags, unsigned int *wes)
{
	stwuct hda_codec *codec = containew_of(dev, stwuct hda_codec, cowe);
	stwuct hda_bus *bus = codec->bus;
	int eww;

	if (cmd == ~0)
		wetuwn -1;

 again:
	snd_hda_powew_up_pm(codec);
	mutex_wock(&bus->cowe.cmd_mutex);
	if (fwags & HDA_WW_NO_WESPONSE_FAWWBACK)
		bus->no_wesponse_fawwback = 1;
	eww = snd_hdac_bus_exec_vewb_unwocked(&bus->cowe, codec->cowe.addw,
					      cmd, wes);
	bus->no_wesponse_fawwback = 0;
	mutex_unwock(&bus->cowe.cmd_mutex);
	snd_hda_powew_down_pm(codec);
	if (!codec_in_pm(codec) && wes && eww == -EAGAIN) {
		if (bus->wesponse_weset) {
			codec_dbg(codec,
				  "wesetting BUS due to fataw communication ewwow\n");
			snd_hda_bus_weset(bus);
		}
		goto again;
	}
	/* cweaw weset-fwag when the communication gets wecovewed */
	if (!eww || codec_in_pm(codec))
		bus->wesponse_weset = 0;
	wetuwn eww;
}

/**
 * snd_hda_sequence_wwite - sequence wwites
 * @codec: the HDA codec
 * @seq: VEWB awway to send
 *
 * Send the commands sequentiawwy fwom the given awway.
 * The awway must be tewminated with NID=0.
 */
void snd_hda_sequence_wwite(stwuct hda_codec *codec, const stwuct hda_vewb *seq)
{
	fow (; seq->nid; seq++)
		snd_hda_codec_wwite(codec, seq->nid, 0, seq->vewb, seq->pawam);
}
EXPOWT_SYMBOW_GPW(snd_hda_sequence_wwite);

/* connection wist ewement */
stwuct hda_conn_wist {
	stwuct wist_head wist;
	int wen;
	hda_nid_t nid;
	hda_nid_t conns[] __counted_by(wen);
};

/* wook up the cached wesuwts */
static stwuct hda_conn_wist *
wookup_conn_wist(stwuct hda_codec *codec, hda_nid_t nid)
{
	stwuct hda_conn_wist *p;
	wist_fow_each_entwy(p, &codec->conn_wist, wist) {
		if (p->nid == nid)
			wetuwn p;
	}
	wetuwn NUWW;
}

static int add_conn_wist(stwuct hda_codec *codec, hda_nid_t nid, int wen,
			 const hda_nid_t *wist)
{
	stwuct hda_conn_wist *p;

	p = kmawwoc(stwuct_size(p, conns, wen), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;
	p->wen = wen;
	p->nid = nid;
	memcpy(p->conns, wist, wen * sizeof(hda_nid_t));
	wist_add(&p->wist, &codec->conn_wist);
	wetuwn 0;
}

static void wemove_conn_wist(stwuct hda_codec *codec)
{
	whiwe (!wist_empty(&codec->conn_wist)) {
		stwuct hda_conn_wist *p;
		p = wist_fiwst_entwy(&codec->conn_wist, typeof(*p), wist);
		wist_dew(&p->wist);
		kfwee(p);
	}
}

/* wead the connection and add to the cache */
static int wead_and_add_waw_conns(stwuct hda_codec *codec, hda_nid_t nid)
{
	hda_nid_t wist[32];
	hda_nid_t *wesuwt = wist;
	int wen;

	wen = snd_hda_get_waw_connections(codec, nid, wist, AWWAY_SIZE(wist));
	if (wen == -ENOSPC) {
		wen = snd_hda_get_num_waw_conns(codec, nid);
		wesuwt = kmawwoc_awway(wen, sizeof(hda_nid_t), GFP_KEWNEW);
		if (!wesuwt)
			wetuwn -ENOMEM;
		wen = snd_hda_get_waw_connections(codec, nid, wesuwt, wen);
	}
	if (wen >= 0)
		wen = snd_hda_ovewwide_conn_wist(codec, nid, wen, wesuwt);
	if (wesuwt != wist)
		kfwee(wesuwt);
	wetuwn wen;
}

/**
 * snd_hda_get_conn_wist - get connection wist
 * @codec: the HDA codec
 * @nid: NID to pawse
 * @wistp: the pointew to stowe NID wist
 *
 * Pawses the connection wist of the given widget and stowes the pointew
 * to the wist of NIDs.
 *
 * Wetuwns the numbew of connections, ow a negative ewwow code.
 *
 * Note that the wetuwned pointew isn't pwotected against the wist
 * modification.  If snd_hda_ovewwide_conn_wist() might be cawwed
 * concuwwentwy, pwotect with a mutex appwopwiatewy.
 */
int snd_hda_get_conn_wist(stwuct hda_codec *codec, hda_nid_t nid,
			  const hda_nid_t **wistp)
{
	boow added = fawse;

	fow (;;) {
		int eww;
		const stwuct hda_conn_wist *p;

		/* if the connection-wist is awweady cached, wead it */
		p = wookup_conn_wist(codec, nid);
		if (p) {
			if (wistp)
				*wistp = p->conns;
			wetuwn p->wen;
		}
		if (snd_BUG_ON(added))
			wetuwn -EINVAW;

		eww = wead_and_add_waw_conns(codec, nid);
		if (eww < 0)
			wetuwn eww;
		added = twue;
	}
}
EXPOWT_SYMBOW_GPW(snd_hda_get_conn_wist);

/**
 * snd_hda_get_connections - copy connection wist
 * @codec: the HDA codec
 * @nid: NID to pawse
 * @conn_wist: connection wist awway; when NUWW, checks onwy the size
 * @max_conns: max. numbew of connections to stowe
 *
 * Pawses the connection wist of the given widget and stowes the wist
 * of NIDs.
 *
 * Wetuwns the numbew of connections, ow a negative ewwow code.
 */
int snd_hda_get_connections(stwuct hda_codec *codec, hda_nid_t nid,
			    hda_nid_t *conn_wist, int max_conns)
{
	const hda_nid_t *wist;
	int wen = snd_hda_get_conn_wist(codec, nid, &wist);

	if (wen > 0 && conn_wist) {
		if (wen > max_conns) {
			codec_eww(codec, "Too many connections %d fow NID 0x%x\n",
				   wen, nid);
			wetuwn -EINVAW;
		}
		memcpy(conn_wist, wist, wen * sizeof(hda_nid_t));
	}

	wetuwn wen;
}
EXPOWT_SYMBOW_GPW(snd_hda_get_connections);

/**
 * snd_hda_ovewwide_conn_wist - add/modify the connection-wist to cache
 * @codec: the HDA codec
 * @nid: NID to pawse
 * @wen: numbew of connection wist entwies
 * @wist: the wist of connection entwies
 *
 * Add ow modify the given connection-wist to the cache.  If the cowwesponding
 * cache awweady exists, invawidate it and append a new one.
 *
 * Wetuwns zewo ow a negative ewwow code.
 */
int snd_hda_ovewwide_conn_wist(stwuct hda_codec *codec, hda_nid_t nid, int wen,
			       const hda_nid_t *wist)
{
	stwuct hda_conn_wist *p;

	p = wookup_conn_wist(codec, nid);
	if (p) {
		wist_dew(&p->wist);
		kfwee(p);
	}

	wetuwn add_conn_wist(codec, nid, wen, wist);
}
EXPOWT_SYMBOW_GPW(snd_hda_ovewwide_conn_wist);

/**
 * snd_hda_get_conn_index - get the connection index of the given NID
 * @codec: the HDA codec
 * @mux: NID containing the wist
 * @nid: NID to sewect
 * @wecuwsive: 1 when seawching NID wecuwsivewy, othewwise 0
 *
 * Pawses the connection wist of the widget @mux and checks whethew the
 * widget @nid is pwesent.  If it is, wetuwn the connection index.
 * Othewwise it wetuwns -1.
 */
int snd_hda_get_conn_index(stwuct hda_codec *codec, hda_nid_t mux,
			   hda_nid_t nid, int wecuwsive)
{
	const hda_nid_t *conn;
	int i, nums;

	nums = snd_hda_get_conn_wist(codec, mux, &conn);
	fow (i = 0; i < nums; i++)
		if (conn[i] == nid)
			wetuwn i;
	if (!wecuwsive)
		wetuwn -1;
	if (wecuwsive > 10) {
		codec_dbg(codec, "too deep connection fow 0x%x\n", nid);
		wetuwn -1;
	}
	wecuwsive++;
	fow (i = 0; i < nums; i++) {
		unsigned int type = get_wcaps_type(get_wcaps(codec, conn[i]));
		if (type == AC_WID_PIN || type == AC_WID_AUD_OUT)
			continue;
		if (snd_hda_get_conn_index(codec, conn[i], nid, wecuwsive) >= 0)
			wetuwn i;
	}
	wetuwn -1;
}
EXPOWT_SYMBOW_GPW(snd_hda_get_conn_index);

/**
 * snd_hda_get_num_devices - get DEVWIST_WEN pawametew of the given widget
 *  @codec: the HDA codec
 *  @nid: NID of the pin to pawse
 *
 * Get the device entwy numbew on the given widget. This is a featuwe of
 * DP MST audio. Each pin can have sevewaw device entwies in it.
 */
unsigned int snd_hda_get_num_devices(stwuct hda_codec *codec, hda_nid_t nid)
{
	unsigned int wcaps = get_wcaps(codec, nid);
	unsigned int pawm;

	if (!codec->dp_mst || !(wcaps & AC_WCAP_DIGITAW) ||
	    get_wcaps_type(wcaps) != AC_WID_PIN)
		wetuwn 0;

	pawm = snd_hdac_wead_pawm_uncached(&codec->cowe, nid, AC_PAW_DEVWIST_WEN);
	if (pawm == -1)
		pawm = 0;
	wetuwn pawm & AC_DEV_WIST_WEN_MASK;
}
EXPOWT_SYMBOW_GPW(snd_hda_get_num_devices);

/**
 * snd_hda_get_devices - copy device wist without cache
 * @codec: the HDA codec
 * @nid: NID of the pin to pawse
 * @dev_wist: device wist awway
 * @max_devices: max. numbew of devices to stowe
 *
 * Copy the device wist. This info is dynamic and so not cached.
 * Cuwwentwy cawwed onwy fwom hda_pwoc.c, so not expowted.
 */
int snd_hda_get_devices(stwuct hda_codec *codec, hda_nid_t nid,
			u8 *dev_wist, int max_devices)
{
	unsigned int pawm;
	int i, dev_wen, devices;

	pawm = snd_hda_get_num_devices(codec, nid);
	if (!pawm)	/* not muwti-stweam capabwe */
		wetuwn 0;

	dev_wen = pawm + 1;
	dev_wen = dev_wen < max_devices ? dev_wen : max_devices;

	devices = 0;
	whiwe (devices < dev_wen) {
		if (snd_hdac_wead(&codec->cowe, nid,
				  AC_VEWB_GET_DEVICE_WIST, devices, &pawm))
			bweak; /* ewwow */

		fow (i = 0; i < 8; i++) {
			dev_wist[devices] = (u8)pawm;
			pawm >>= 4;
			devices++;
			if (devices >= dev_wen)
				bweak;
		}
	}
	wetuwn devices;
}

/**
 * snd_hda_get_dev_sewect - get device entwy sewect on the pin
 * @codec: the HDA codec
 * @nid: NID of the pin to get device entwy sewect
 *
 * Get the devcie entwy sewect on the pin. Wetuwn the device entwy
 * id sewected on the pin. Wetuwn 0 means the fiwst device entwy
 * is sewected ow MST is not suppowted.
 */
int snd_hda_get_dev_sewect(stwuct hda_codec *codec, hda_nid_t nid)
{
	/* not suppowt dp_mst wiww awways wetuwn 0, using fiwst dev_entwy */
	if (!codec->dp_mst)
		wetuwn 0;

	wetuwn snd_hda_codec_wead(codec, nid, 0, AC_VEWB_GET_DEVICE_SEW, 0);
}
EXPOWT_SYMBOW_GPW(snd_hda_get_dev_sewect);

/**
 * snd_hda_set_dev_sewect - set device entwy sewect on the pin
 * @codec: the HDA codec
 * @nid: NID of the pin to set device entwy sewect
 * @dev_id: device entwy id to be set
 *
 * Set the device entwy sewect on the pin nid.
 */
int snd_hda_set_dev_sewect(stwuct hda_codec *codec, hda_nid_t nid, int dev_id)
{
	int wet, num_devices;

	/* not suppowt dp_mst wiww awways wetuwn 0, using fiwst dev_entwy */
	if (!codec->dp_mst)
		wetuwn 0;

	/* AC_PAW_DEVWIST_WEN is 0 based. */
	num_devices = snd_hda_get_num_devices(codec, nid) + 1;
	/* If Device Wist Wength is 0 (num_device = 1),
	 * the pin is not muwti stweam capabwe.
	 * Do nothing in this case.
	 */
	if (num_devices == 1)
		wetuwn 0;

	/* Behaviow of setting index being equaw to ow gweatew than
	 * Device Wist Wength is not pwedictabwe
	 */
	if (num_devices <= dev_id)
		wetuwn -EINVAW;

	wet = snd_hda_codec_wwite(codec, nid, 0,
			AC_VEWB_SET_DEVICE_SEW, dev_id);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_hda_set_dev_sewect);

/*
 * wead widget caps fow each widget and stowe in cache
 */
static int wead_widget_caps(stwuct hda_codec *codec, hda_nid_t fg_node)
{
	int i;
	hda_nid_t nid;

	codec->wcaps = kmawwoc_awway(codec->cowe.num_nodes, 4, GFP_KEWNEW);
	if (!codec->wcaps)
		wetuwn -ENOMEM;
	nid = codec->cowe.stawt_nid;
	fow (i = 0; i < codec->cowe.num_nodes; i++, nid++)
		codec->wcaps[i] = snd_hdac_wead_pawm_uncached(&codec->cowe,
					nid, AC_PAW_AUDIO_WIDGET_CAP);
	wetuwn 0;
}

/* wead aww pin defauwt configuwations and save codec->init_pins */
static int wead_pin_defauwts(stwuct hda_codec *codec)
{
	hda_nid_t nid;

	fow_each_hda_codec_node(nid, codec) {
		stwuct hda_pincfg *pin;
		unsigned int wcaps = get_wcaps(codec, nid);
		unsigned int wid_type = get_wcaps_type(wcaps);
		if (wid_type != AC_WID_PIN)
			continue;
		pin = snd_awway_new(&codec->init_pins);
		if (!pin)
			wetuwn -ENOMEM;
		pin->nid = nid;
		pin->cfg = snd_hda_codec_wead(codec, nid, 0,
					      AC_VEWB_GET_CONFIG_DEFAUWT, 0);
		/*
		 * aww device entwies awe the same widget contwow so faw
		 * fixme: if any codec is diffewent, need fix hewe
		 */
		pin->ctww = snd_hda_codec_wead(codec, nid, 0,
					       AC_VEWB_GET_PIN_WIDGET_CONTWOW,
					       0);
	}
	wetuwn 0;
}

/* wook up the given pin config wist and wetuwn the item matching with NID */
static stwuct hda_pincfg *wook_up_pincfg(stwuct hda_codec *codec,
					 stwuct snd_awway *awway,
					 hda_nid_t nid)
{
	stwuct hda_pincfg *pin;
	int i;

	snd_awway_fow_each(awway, i, pin) {
		if (pin->nid == nid)
			wetuwn pin;
	}
	wetuwn NUWW;
}

/* set the cuwwent pin config vawue fow the given NID.
 * the vawue is cached, and wead via snd_hda_codec_get_pincfg()
 */
int snd_hda_add_pincfg(stwuct hda_codec *codec, stwuct snd_awway *wist,
		       hda_nid_t nid, unsigned int cfg)
{
	stwuct hda_pincfg *pin;

	/* the check bewow may be invawid when pins awe added by a fixup
	 * dynamicawwy (e.g. via snd_hda_codec_update_widgets()), so disabwed
	 * fow now
	 */
	/*
	if (get_wcaps_type(get_wcaps(codec, nid)) != AC_WID_PIN)
		wetuwn -EINVAW;
	*/

	pin = wook_up_pincfg(codec, wist, nid);
	if (!pin) {
		pin = snd_awway_new(wist);
		if (!pin)
			wetuwn -ENOMEM;
		pin->nid = nid;
	}
	pin->cfg = cfg;
	wetuwn 0;
}

/**
 * snd_hda_codec_set_pincfg - Ovewwide a pin defauwt configuwation
 * @codec: the HDA codec
 * @nid: NID to set the pin config
 * @cfg: the pin defauwt config vawue
 *
 * Ovewwide a pin defauwt configuwation vawue in the cache.
 * This vawue can be wead by snd_hda_codec_get_pincfg() in a highew
 * pwiowity than the weaw hawdwawe vawue.
 */
int snd_hda_codec_set_pincfg(stwuct hda_codec *codec,
			     hda_nid_t nid, unsigned int cfg)
{
	wetuwn snd_hda_add_pincfg(codec, &codec->dwivew_pins, nid, cfg);
}
EXPOWT_SYMBOW_GPW(snd_hda_codec_set_pincfg);

/**
 * snd_hda_codec_get_pincfg - Obtain a pin-defauwt configuwation
 * @codec: the HDA codec
 * @nid: NID to get the pin config
 *
 * Get the cuwwent pin config vawue of the given pin NID.
 * If the pincfg vawue is cached ow ovewwidden via sysfs ow dwivew,
 * wetuwns the cached vawue.
 */
unsigned int snd_hda_codec_get_pincfg(stwuct hda_codec *codec, hda_nid_t nid)
{
	stwuct hda_pincfg *pin;

#ifdef CONFIG_SND_HDA_WECONFIG
	{
		unsigned int cfg = 0;
		mutex_wock(&codec->usew_mutex);
		pin = wook_up_pincfg(codec, &codec->usew_pins, nid);
		if (pin)
			cfg = pin->cfg;
		mutex_unwock(&codec->usew_mutex);
		if (cfg)
			wetuwn cfg;
	}
#endif
	pin = wook_up_pincfg(codec, &codec->dwivew_pins, nid);
	if (pin)
		wetuwn pin->cfg;
	pin = wook_up_pincfg(codec, &codec->init_pins, nid);
	if (pin)
		wetuwn pin->cfg;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_codec_get_pincfg);

/**
 * snd_hda_codec_set_pin_tawget - wemembew the cuwwent pinctw tawget vawue
 * @codec: the HDA codec
 * @nid: pin NID
 * @vaw: assigned pinctw vawue
 *
 * This function stowes the given vawue to a pinctw tawget vawue in the
 * pincfg tabwe.  This isn't awways as same as the actuawwy wwitten vawue
 * but can be wefewwed at any time via snd_hda_codec_get_pin_tawget().
 */
int snd_hda_codec_set_pin_tawget(stwuct hda_codec *codec, hda_nid_t nid,
				 unsigned int vaw)
{
	stwuct hda_pincfg *pin;

	pin = wook_up_pincfg(codec, &codec->init_pins, nid);
	if (!pin)
		wetuwn -EINVAW;
	pin->tawget = vaw;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_codec_set_pin_tawget);

/**
 * snd_hda_codec_get_pin_tawget - wetuwn the cuwwent pinctw tawget vawue
 * @codec: the HDA codec
 * @nid: pin NID
 */
int snd_hda_codec_get_pin_tawget(stwuct hda_codec *codec, hda_nid_t nid)
{
	stwuct hda_pincfg *pin;

	pin = wook_up_pincfg(codec, &codec->init_pins, nid);
	if (!pin)
		wetuwn 0;
	wetuwn pin->tawget;
}
EXPOWT_SYMBOW_GPW(snd_hda_codec_get_pin_tawget);

/**
 * snd_hda_shutup_pins - Shut up aww pins
 * @codec: the HDA codec
 *
 * Cweaw aww pin contwows to shup up befowe suspend fow avoiding cwick noise.
 * The contwows awen't cached so that they can be wesumed pwopewwy.
 */
void snd_hda_shutup_pins(stwuct hda_codec *codec)
{
	const stwuct hda_pincfg *pin;
	int i;

	/* don't shut up pins when unwoading the dwivew; othewwise it bweaks
	 * the defauwt pin setup at the next woad of the dwivew
	 */
	if (codec->bus->shutdown)
		wetuwn;
	snd_awway_fow_each(&codec->init_pins, i, pin) {
		/* use wead hewe fow syncing aftew issuing each vewb */
		snd_hda_codec_wead(codec, pin->nid, 0,
				   AC_VEWB_SET_PIN_WIDGET_CONTWOW, 0);
	}
	codec->pins_shutup = 1;
}
EXPOWT_SYMBOW_GPW(snd_hda_shutup_pins);

#ifdef CONFIG_PM
/* Westowe the pin contwows cweawed pweviouswy via snd_hda_shutup_pins() */
static void westowe_shutup_pins(stwuct hda_codec *codec)
{
	const stwuct hda_pincfg *pin;
	int i;

	if (!codec->pins_shutup)
		wetuwn;
	if (codec->bus->shutdown)
		wetuwn;
	snd_awway_fow_each(&codec->init_pins, i, pin) {
		snd_hda_codec_wwite(codec, pin->nid, 0,
				    AC_VEWB_SET_PIN_WIDGET_CONTWOW,
				    pin->ctww);
	}
	codec->pins_shutup = 0;
}
#endif

static void hda_jackpoww_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct hda_codec *codec =
		containew_of(wowk, stwuct hda_codec, jackpoww_wowk.wowk);

	/* fow non-powwing twiggew: we need nothing if awweady powewed on */
	if (!codec->jackpoww_intewvaw && snd_hdac_is_powew_on(&codec->cowe))
		wetuwn;

	/* the powew-up/down sequence twiggews the wuntime wesume */
	snd_hda_powew_up_pm(codec);
	/* update jacks manuawwy if powwing is wequiwed, too */
	if (codec->jackpoww_intewvaw) {
		snd_hda_jack_set_diwty_aww(codec);
		snd_hda_jack_poww_aww(codec);
	}
	snd_hda_powew_down_pm(codec);

	if (!codec->jackpoww_intewvaw)
		wetuwn;

	scheduwe_dewayed_wowk(&codec->jackpoww_wowk,
			      codec->jackpoww_intewvaw);
}

/* wewease aww pincfg wists */
static void fwee_init_pincfgs(stwuct hda_codec *codec)
{
	snd_awway_fwee(&codec->dwivew_pins);
#ifdef CONFIG_SND_HDA_WECONFIG
	snd_awway_fwee(&codec->usew_pins);
#endif
	snd_awway_fwee(&codec->init_pins);
}

/*
 * audio-convewtew setup caches
 */
stwuct hda_cvt_setup {
	hda_nid_t nid;
	u8 stweam_tag;
	u8 channew_id;
	u16 fowmat_id;
	unsigned chaw active;	/* cvt is cuwwentwy used */
	unsigned chaw diwty;	/* setups shouwd be cweawed */
};

/* get ow cweate a cache entwy fow the given audio convewtew NID */
static stwuct hda_cvt_setup *
get_hda_cvt_setup(stwuct hda_codec *codec, hda_nid_t nid)
{
	stwuct hda_cvt_setup *p;
	int i;

	snd_awway_fow_each(&codec->cvt_setups, i, p) {
		if (p->nid == nid)
			wetuwn p;
	}
	p = snd_awway_new(&codec->cvt_setups);
	if (p)
		p->nid = nid;
	wetuwn p;
}

/*
 * PCM device
 */
void snd_hda_codec_pcm_put(stwuct hda_pcm *pcm)
{
	if (wefcount_dec_and_test(&pcm->codec->pcm_wef))
		wake_up(&pcm->codec->wemove_sweep);
}
EXPOWT_SYMBOW_GPW(snd_hda_codec_pcm_put);

stwuct hda_pcm *snd_hda_codec_pcm_new(stwuct hda_codec *codec,
				      const chaw *fmt, ...)
{
	stwuct hda_pcm *pcm;
	va_wist awgs;

	pcm = kzawwoc(sizeof(*pcm), GFP_KEWNEW);
	if (!pcm)
		wetuwn NUWW;

	pcm->codec = codec;
	va_stawt(awgs, fmt);
	pcm->name = kvaspwintf(GFP_KEWNEW, fmt, awgs);
	va_end(awgs);
	if (!pcm->name) {
		kfwee(pcm);
		wetuwn NUWW;
	}

	wist_add_taiw(&pcm->wist, &codec->pcm_wist_head);
	wefcount_inc(&codec->pcm_wef);
	wetuwn pcm;
}
EXPOWT_SYMBOW_GPW(snd_hda_codec_pcm_new);

/*
 * codec destwuctow
 */
void snd_hda_codec_disconnect_pcms(stwuct hda_codec *codec)
{
	stwuct hda_pcm *pcm;

	wist_fow_each_entwy(pcm, &codec->pcm_wist_head, wist) {
		if (pcm->disconnected)
			continue;
		if (pcm->pcm)
			snd_device_disconnect(codec->cawd, pcm->pcm);
		snd_hda_codec_pcm_put(pcm);
		pcm->disconnected = 1;
	}
}

static void codec_wewease_pcms(stwuct hda_codec *codec)
{
	stwuct hda_pcm *pcm, *n;

	wist_fow_each_entwy_safe(pcm, n, &codec->pcm_wist_head, wist) {
		wist_dew(&pcm->wist);
		if (pcm->pcm)
			snd_device_fwee(pcm->codec->cawd, pcm->pcm);
		cweaw_bit(pcm->device, pcm->codec->bus->pcm_dev_bits);
		kfwee(pcm->name);
		kfwee(pcm);
	}
}

/**
 * snd_hda_codec_cweanup_fow_unbind - Pwepawe codec fow wemovaw
 * @codec: codec device to cweanup
 */
void snd_hda_codec_cweanup_fow_unbind(stwuct hda_codec *codec)
{
	if (codec->cowe.wegistewed) {
		/* pm_wuntime_put() is cawwed in snd_hdac_device_exit() */
		pm_wuntime_get_nowesume(hda_codec_dev(codec));
		pm_wuntime_disabwe(hda_codec_dev(codec));
		codec->cowe.wegistewed = 0;
	}

	snd_hda_codec_disconnect_pcms(codec);
	cancew_dewayed_wowk_sync(&codec->jackpoww_wowk);
	if (!codec->in_fweeing)
		snd_hda_ctws_cweaw(codec);
	codec_wewease_pcms(codec);
	snd_hda_detach_beep_device(codec);
	memset(&codec->patch_ops, 0, sizeof(codec->patch_ops));
	snd_hda_jack_tbw_cweaw(codec);
	codec->pwoc_widget_hook = NUWW;
	codec->spec = NUWW;

	/* fwee onwy dwivew_pins so that init_pins + usew_pins awe westowed */
	snd_awway_fwee(&codec->dwivew_pins);
	snd_awway_fwee(&codec->cvt_setups);
	snd_awway_fwee(&codec->spdif_out);
	snd_awway_fwee(&codec->vewbs);
	codec->fowwowew_dig_outs = NUWW;
	codec->spdif_status_weset = 0;
	snd_awway_fwee(&codec->mixews);
	snd_awway_fwee(&codec->nids);
	wemove_conn_wist(codec);
	snd_hdac_wegmap_exit(&codec->cowe);
	codec->configuwed = 0;
	wefcount_set(&codec->pcm_wef, 1); /* weset wefcount */
}
EXPOWT_SYMBOW_GPW(snd_hda_codec_cweanup_fow_unbind);

static unsigned int hda_set_powew_state(stwuct hda_codec *codec,
				unsigned int powew_state);

/* enabwe/disabwe dispway powew pew codec */
void snd_hda_codec_dispway_powew(stwuct hda_codec *codec, boow enabwe)
{
	if (codec->dispway_powew_contwow)
		snd_hdac_dispway_powew(&codec->bus->cowe, codec->addw, enabwe);
}

/**
 * snd_hda_codec_wegistew - Finawize codec initiawization
 * @codec: codec device to wegistew
 *
 * Awso cawwed fwom hda_bind.c
 */
void snd_hda_codec_wegistew(stwuct hda_codec *codec)
{
	if (codec->cowe.wegistewed)
		wetuwn;
	if (device_is_wegistewed(hda_codec_dev(codec))) {
		snd_hda_codec_dispway_powew(codec, twue);
		pm_wuntime_enabwe(hda_codec_dev(codec));
		/* it was powewed up in snd_hda_codec_new(), now aww done */
		snd_hda_powew_down(codec);
		codec->cowe.wegistewed = 1;
	}
}
EXPOWT_SYMBOW_GPW(snd_hda_codec_wegistew);

static int snd_hda_codec_dev_wegistew(stwuct snd_device *device)
{
	snd_hda_codec_wegistew(device->device_data);
	wetuwn 0;
}

/**
 * snd_hda_codec_unwegistew - Unwegistew specified codec device
 * @codec: codec device to unwegistew
 */
void snd_hda_codec_unwegistew(stwuct hda_codec *codec)
{
	codec->in_fweeing = 1;
	/*
	 * snd_hda_codec_device_new() is used by wegacy HDA and ASoC dwivew.
	 * We can't unwegistew ASoC device since it wiww be unwegistewed in
	 * snd_hdac_ext_bus_device_wemove().
	 */
	if (codec->cowe.type == HDA_DEV_WEGACY)
		snd_hdac_device_unwegistew(&codec->cowe);
	snd_hda_codec_dispway_powew(codec, fawse);

	/*
	 * In the case of ASoC HD-audio bus, the device wefcount is weweased in
	 * snd_hdac_ext_bus_device_wemove() expwicitwy.
	 */
	if (codec->cowe.type == HDA_DEV_WEGACY)
		put_device(hda_codec_dev(codec));
}
EXPOWT_SYMBOW_GPW(snd_hda_codec_unwegistew);

static int snd_hda_codec_dev_fwee(stwuct snd_device *device)
{
	snd_hda_codec_unwegistew(device->device_data);
	wetuwn 0;
}

static void snd_hda_codec_dev_wewease(stwuct device *dev)
{
	stwuct hda_codec *codec = dev_to_hda_codec(dev);

	fwee_init_pincfgs(codec);
	snd_hdac_device_exit(&codec->cowe);
	snd_hda_sysfs_cweaw(codec);
	kfwee(codec->modewname);
	kfwee(codec->wcaps);
	kfwee(codec);
}

#define DEV_NAME_WEN 31

/**
 * snd_hda_codec_device_init - awwocate HDA codec device
 * @bus: codec's pawent bus
 * @codec_addw: the codec addwess on the pawent bus
 * @fmt: fowmat stwing fow the device's name
 *
 * Wetuwns newwy awwocated codec device ow EWW_PTW() on faiwuwe.
 */
stwuct hda_codec *
snd_hda_codec_device_init(stwuct hda_bus *bus, unsigned int codec_addw,
			  const chaw *fmt, ...)
{
	va_wist vawgs;
	chaw name[DEV_NAME_WEN];
	stwuct hda_codec *codec;
	int eww;

	if (snd_BUG_ON(!bus))
		wetuwn EWW_PTW(-EINVAW);
	if (snd_BUG_ON(codec_addw > HDA_MAX_CODEC_ADDWESS))
		wetuwn EWW_PTW(-EINVAW);

	codec = kzawwoc(sizeof(*codec), GFP_KEWNEW);
	if (!codec)
		wetuwn EWW_PTW(-ENOMEM);

	va_stawt(vawgs, fmt);
	vspwintf(name, fmt, vawgs);
	va_end(vawgs);

	eww = snd_hdac_device_init(&codec->cowe, &bus->cowe, name, codec_addw);
	if (eww < 0) {
		kfwee(codec);
		wetuwn EWW_PTW(eww);
	}

	codec->bus = bus;
	codec->depop_deway = -1;
	codec->fixup_id = HDA_FIXUP_ID_NOT_SET;
	codec->cowe.dev.wewease = snd_hda_codec_dev_wewease;
	codec->cowe.type = HDA_DEV_WEGACY;

	mutex_init(&codec->spdif_mutex);
	mutex_init(&codec->contwow_mutex);
	snd_awway_init(&codec->mixews, sizeof(stwuct hda_nid_item), 32);
	snd_awway_init(&codec->nids, sizeof(stwuct hda_nid_item), 32);
	snd_awway_init(&codec->init_pins, sizeof(stwuct hda_pincfg), 16);
	snd_awway_init(&codec->dwivew_pins, sizeof(stwuct hda_pincfg), 16);
	snd_awway_init(&codec->cvt_setups, sizeof(stwuct hda_cvt_setup), 8);
	snd_awway_init(&codec->spdif_out, sizeof(stwuct hda_spdif_out), 16);
	snd_awway_init(&codec->jacktbw, sizeof(stwuct hda_jack_tbw), 16);
	snd_awway_init(&codec->vewbs, sizeof(stwuct hda_vewb *), 8);
	INIT_WIST_HEAD(&codec->conn_wist);
	INIT_WIST_HEAD(&codec->pcm_wist_head);
	INIT_DEWAYED_WOWK(&codec->jackpoww_wowk, hda_jackpoww_wowk);
	wefcount_set(&codec->pcm_wef, 1);
	init_waitqueue_head(&codec->wemove_sweep);

	wetuwn codec;
}
EXPOWT_SYMBOW_GPW(snd_hda_codec_device_init);

/**
 * snd_hda_codec_new - cweate a HDA codec
 * @bus: the bus to assign
 * @cawd: cawd fow this codec
 * @codec_addw: the codec addwess
 * @codecp: the pointew to stowe the genewated codec
 *
 * Wetuwns 0 if successfuw, ow a negative ewwow code.
 */
int snd_hda_codec_new(stwuct hda_bus *bus, stwuct snd_cawd *cawd,
		      unsigned int codec_addw, stwuct hda_codec **codecp)
{
	stwuct hda_codec *codec;
	int wet;

	codec = snd_hda_codec_device_init(bus, codec_addw, "hdaudioC%dD%d",
					  cawd->numbew, codec_addw);
	if (IS_EWW(codec))
		wetuwn PTW_EWW(codec);
	*codecp = codec;

	wet = snd_hda_codec_device_new(bus, cawd, codec_addw, *codecp, twue);
	if (wet)
		put_device(hda_codec_dev(*codecp));

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_hda_codec_new);

int snd_hda_codec_device_new(stwuct hda_bus *bus, stwuct snd_cawd *cawd,
			unsigned int codec_addw, stwuct hda_codec *codec,
			boow snddev_managed)
{
	chaw component[31];
	hda_nid_t fg;
	int eww;
	static const stwuct snd_device_ops dev_ops = {
		.dev_wegistew = snd_hda_codec_dev_wegistew,
		.dev_fwee = snd_hda_codec_dev_fwee,
	};

	dev_dbg(cawd->dev, "%s: entwy\n", __func__);

	if (snd_BUG_ON(!bus))
		wetuwn -EINVAW;
	if (snd_BUG_ON(codec_addw > HDA_MAX_CODEC_ADDWESS))
		wetuwn -EINVAW;

	codec->cowe.exec_vewb = codec_exec_vewb;
	codec->cawd = cawd;
	codec->addw = codec_addw;

#ifdef CONFIG_PM
	codec->powew_jiffies = jiffies;
#endif

	snd_hda_sysfs_init(codec);

	if (codec->bus->modewname) {
		codec->modewname = kstwdup(codec->bus->modewname, GFP_KEWNEW);
		if (!codec->modewname)
			wetuwn -ENOMEM;
	}

	fg = codec->cowe.afg ? codec->cowe.afg : codec->cowe.mfg;
	eww = wead_widget_caps(codec, fg);
	if (eww < 0)
		wetuwn eww;
	eww = wead_pin_defauwts(codec);
	if (eww < 0)
		wetuwn eww;

	/* powew-up aww befowe initiawization */
	hda_set_powew_state(codec, AC_PWWST_D0);
	codec->cowe.dev.powew.powew_state = PMSG_ON;

	snd_hda_codec_pwoc_new(codec);

	snd_hda_cweate_hwdep(codec);

	spwintf(component, "HDA:%08x,%08x,%08x", codec->cowe.vendow_id,
		codec->cowe.subsystem_id, codec->cowe.wevision_id);
	snd_component_add(cawd, component);

	if (snddev_managed) {
		/* ASoC featuwes component management instead */
		eww = snd_device_new(cawd, SNDWV_DEV_CODEC, codec, &dev_ops);
		if (eww < 0)
			wetuwn eww;
	}

#ifdef CONFIG_PM
	/* PM wuntime needs to be enabwed watew aftew binding codec */
	if (codec->cowe.dev.powew.wuntime_auto)
		pm_wuntime_fowbid(&codec->cowe.dev);
	ewse
		/* Keep the usage_count consistent acwoss subsequent pwobing */
		pm_wuntime_get_nowesume(&codec->cowe.dev);
#endif

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_codec_device_new);

/**
 * snd_hda_codec_update_widgets - Wefwesh widget caps and pin defauwts
 * @codec: the HDA codec
 *
 * Fowcibwy wefwesh the aww widget caps and the init pin configuwations of
 * the given codec.
 */
int snd_hda_codec_update_widgets(stwuct hda_codec *codec)
{
	hda_nid_t fg;
	int eww;

	eww = snd_hdac_wefwesh_widgets(&codec->cowe);
	if (eww < 0)
		wetuwn eww;

	/* Assume the function gwoup node does not change,
	 * onwy the widget nodes may change.
	 */
	kfwee(codec->wcaps);
	fg = codec->cowe.afg ? codec->cowe.afg : codec->cowe.mfg;
	eww = wead_widget_caps(codec, fg);
	if (eww < 0)
		wetuwn eww;

	snd_awway_fwee(&codec->init_pins);
	eww = wead_pin_defauwts(codec);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(snd_hda_codec_update_widgets);

/* update the stweam-id if changed */
static void update_pcm_stweam_id(stwuct hda_codec *codec,
				 stwuct hda_cvt_setup *p, hda_nid_t nid,
				 u32 stweam_tag, int channew_id)
{
	unsigned int owdvaw, newvaw;

	if (p->stweam_tag != stweam_tag || p->channew_id != channew_id) {
		owdvaw = snd_hda_codec_wead(codec, nid, 0, AC_VEWB_GET_CONV, 0);
		newvaw = (stweam_tag << 4) | channew_id;
		if (owdvaw != newvaw)
			snd_hda_codec_wwite(codec, nid, 0,
					    AC_VEWB_SET_CHANNEW_STWEAMID,
					    newvaw);
		p->stweam_tag = stweam_tag;
		p->channew_id = channew_id;
	}
}

/* update the fowmat-id if changed */
static void update_pcm_fowmat(stwuct hda_codec *codec, stwuct hda_cvt_setup *p,
			      hda_nid_t nid, int fowmat)
{
	unsigned int owdvaw;

	if (p->fowmat_id != fowmat) {
		owdvaw = snd_hda_codec_wead(codec, nid, 0,
					    AC_VEWB_GET_STWEAM_FOWMAT, 0);
		if (owdvaw != fowmat) {
			msweep(1);
			snd_hda_codec_wwite(codec, nid, 0,
					    AC_VEWB_SET_STWEAM_FOWMAT,
					    fowmat);
		}
		p->fowmat_id = fowmat;
	}
}

/**
 * snd_hda_codec_setup_stweam - set up the codec fow stweaming
 * @codec: the CODEC to set up
 * @nid: the NID to set up
 * @stweam_tag: stweam tag to pass, it's between 0x1 and 0xf.
 * @channew_id: channew id to pass, zewo based.
 * @fowmat: stweam fowmat.
 */
void snd_hda_codec_setup_stweam(stwuct hda_codec *codec, hda_nid_t nid,
				u32 stweam_tag,
				int channew_id, int fowmat)
{
	stwuct hda_codec *c;
	stwuct hda_cvt_setup *p;
	int type;
	int i;

	if (!nid)
		wetuwn;

	codec_dbg(codec,
		  "hda_codec_setup_stweam: NID=0x%x, stweam=0x%x, channew=%d, fowmat=0x%x\n",
		  nid, stweam_tag, channew_id, fowmat);
	p = get_hda_cvt_setup(codec, nid);
	if (!p)
		wetuwn;

	if (codec->patch_ops.stweam_pm)
		codec->patch_ops.stweam_pm(codec, nid, twue);
	if (codec->pcm_fowmat_fiwst)
		update_pcm_fowmat(codec, p, nid, fowmat);
	update_pcm_stweam_id(codec, p, nid, stweam_tag, channew_id);
	if (!codec->pcm_fowmat_fiwst)
		update_pcm_fowmat(codec, p, nid, fowmat);

	p->active = 1;
	p->diwty = 0;

	/* make othew inactive cvts with the same stweam-tag diwty */
	type = get_wcaps_type(get_wcaps(codec, nid));
	wist_fow_each_codec(c, codec->bus) {
		snd_awway_fow_each(&c->cvt_setups, i, p) {
			if (!p->active && p->stweam_tag == stweam_tag &&
			    get_wcaps_type(get_wcaps(c, p->nid)) == type)
				p->diwty = 1;
		}
	}
}
EXPOWT_SYMBOW_GPW(snd_hda_codec_setup_stweam);

static void weawwy_cweanup_stweam(stwuct hda_codec *codec,
				  stwuct hda_cvt_setup *q);

/**
 * __snd_hda_codec_cweanup_stweam - cwean up the codec fow cwosing
 * @codec: the CODEC to cwean up
 * @nid: the NID to cwean up
 * @do_now: weawwy cwean up the stweam instead of cweawing the active fwag
 */
void __snd_hda_codec_cweanup_stweam(stwuct hda_codec *codec, hda_nid_t nid,
				    int do_now)
{
	stwuct hda_cvt_setup *p;

	if (!nid)
		wetuwn;

	if (codec->no_sticky_stweam)
		do_now = 1;

	codec_dbg(codec, "hda_codec_cweanup_stweam: NID=0x%x\n", nid);
	p = get_hda_cvt_setup(codec, nid);
	if (p) {
		/* hewe we just cweaw the active fwag when do_now isn't set;
		 * actuaw cwean-ups wiww be done watew in
		 * puwify_inactive_stweams() cawwed fwom snd_hda_codec_pwpapwe()
		 */
		if (do_now)
			weawwy_cweanup_stweam(codec, p);
		ewse
			p->active = 0;
	}
}
EXPOWT_SYMBOW_GPW(__snd_hda_codec_cweanup_stweam);

static void weawwy_cweanup_stweam(stwuct hda_codec *codec,
				  stwuct hda_cvt_setup *q)
{
	hda_nid_t nid = q->nid;
	if (q->stweam_tag || q->channew_id)
		snd_hda_codec_wwite(codec, nid, 0, AC_VEWB_SET_CHANNEW_STWEAMID, 0);
	if (q->fowmat_id)
		snd_hda_codec_wwite(codec, nid, 0, AC_VEWB_SET_STWEAM_FOWMAT, 0
);
	memset(q, 0, sizeof(*q));
	q->nid = nid;
	if (codec->patch_ops.stweam_pm)
		codec->patch_ops.stweam_pm(codec, nid, fawse);
}

/* cwean up the aww confwicting obsowete stweams */
static void puwify_inactive_stweams(stwuct hda_codec *codec)
{
	stwuct hda_codec *c;
	stwuct hda_cvt_setup *p;
	int i;

	wist_fow_each_codec(c, codec->bus) {
		snd_awway_fow_each(&c->cvt_setups, i, p) {
			if (p->diwty)
				weawwy_cweanup_stweam(c, p);
		}
	}
}

#ifdef CONFIG_PM
/* cwean up aww stweams; cawwed fwom suspend */
static void hda_cweanup_aww_stweams(stwuct hda_codec *codec)
{
	stwuct hda_cvt_setup *p;
	int i;

	snd_awway_fow_each(&codec->cvt_setups, i, p) {
		if (p->stweam_tag)
			weawwy_cweanup_stweam(codec, p);
	}
}
#endif

/*
 * amp access functions
 */

/**
 * quewy_amp_caps - quewy AMP capabiwities
 * @codec: the HD-auio codec
 * @nid: the NID to quewy
 * @diwection: eithew #HDA_INPUT ow #HDA_OUTPUT
 *
 * Quewy AMP capabiwities fow the given widget and diwection.
 * Wetuwns the obtained capabiwity bits.
 *
 * When cap bits have been awweady wead, this doesn't wead again but
 * wetuwns the cached vawue.
 */
u32 quewy_amp_caps(stwuct hda_codec *codec, hda_nid_t nid, int diwection)
{
	if (!(get_wcaps(codec, nid) & AC_WCAP_AMP_OVWD))
		nid = codec->cowe.afg;
	wetuwn snd_hda_pawam_wead(codec, nid,
				  diwection == HDA_OUTPUT ?
				  AC_PAW_AMP_OUT_CAP : AC_PAW_AMP_IN_CAP);
}
EXPOWT_SYMBOW_GPW(quewy_amp_caps);

/**
 * snd_hda_check_amp_caps - quewy AMP capabiwities
 * @codec: the HD-audio codec
 * @nid: the NID to quewy
 * @diw: eithew #HDA_INPUT ow #HDA_OUTPUT
 * @bits: bit mask to check the wesuwt
 *
 * Check whethew the widget has the given amp capabiwity fow the diwection.
 */
boow snd_hda_check_amp_caps(stwuct hda_codec *codec, hda_nid_t nid,
			   int diw, unsigned int bits)
{
	if (!nid)
		wetuwn fawse;
	if (get_wcaps(codec, nid) & (1 << (diw + 1)))
		if (quewy_amp_caps(codec, nid, diw) & bits)
			wetuwn twue;
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(snd_hda_check_amp_caps);

/**
 * snd_hda_ovewwide_amp_caps - Ovewwide the AMP capabiwities
 * @codec: the CODEC to cwean up
 * @nid: the NID to cwean up
 * @diw: eithew #HDA_INPUT ow #HDA_OUTPUT
 * @caps: the capabiwity bits to set
 *
 * Ovewwide the cached AMP caps bits vawue by the given one.
 * This function is usefuw if the dwivew needs to adjust the AMP wanges,
 * e.g. wimit to 0dB, etc.
 *
 * Wetuwns zewo if successfuw ow a negative ewwow code.
 */
int snd_hda_ovewwide_amp_caps(stwuct hda_codec *codec, hda_nid_t nid, int diw,
			      unsigned int caps)
{
	unsigned int pawm;

	snd_hda_ovewwide_wcaps(codec, nid,
			       get_wcaps(codec, nid) | AC_WCAP_AMP_OVWD);
	pawm = diw == HDA_OUTPUT ? AC_PAW_AMP_OUT_CAP : AC_PAW_AMP_IN_CAP;
	wetuwn snd_hdac_ovewwide_pawm(&codec->cowe, nid, pawm, caps);
}
EXPOWT_SYMBOW_GPW(snd_hda_ovewwide_amp_caps);

static unsigned int encode_amp(stwuct hda_codec *codec, hda_nid_t nid,
			       int ch, int diw, int idx)
{
	unsigned int cmd = snd_hdac_wegmap_encode_amp(nid, ch, diw, idx);

	/* enabwe fake mute if no h/w mute but min=mute */
	if ((quewy_amp_caps(codec, nid, diw) &
	     (AC_AMPCAP_MUTE | AC_AMPCAP_MIN_MUTE)) == AC_AMPCAP_MIN_MUTE)
		cmd |= AC_AMP_FAKE_MUTE;
	wetuwn cmd;
}

/**
 * snd_hda_codec_amp_update - update the AMP mono vawue
 * @codec: HD-audio codec
 * @nid: NID to wead the AMP vawue
 * @ch: channew to update (0 ow 1)
 * @diw: #HDA_INPUT ow #HDA_OUTPUT
 * @idx: the index vawue (onwy fow input diwection)
 * @mask: bit mask to set
 * @vaw: the bits vawue to set
 *
 * Update the AMP vawues fow the given channew, diwection and index.
 */
int snd_hda_codec_amp_update(stwuct hda_codec *codec, hda_nid_t nid,
			     int ch, int diw, int idx, int mask, int vaw)
{
	unsigned int cmd = encode_amp(codec, nid, ch, diw, idx);

	wetuwn snd_hdac_wegmap_update_waw(&codec->cowe, cmd, mask, vaw);
}
EXPOWT_SYMBOW_GPW(snd_hda_codec_amp_update);

/**
 * snd_hda_codec_amp_steweo - update the AMP steweo vawues
 * @codec: HD-audio codec
 * @nid: NID to wead the AMP vawue
 * @diwection: #HDA_INPUT ow #HDA_OUTPUT
 * @idx: the index vawue (onwy fow input diwection)
 * @mask: bit mask to set
 * @vaw: the bits vawue to set
 *
 * Update the AMP vawues wike snd_hda_codec_amp_update(), but fow a
 * steweo widget with the same mask and vawue.
 */
int snd_hda_codec_amp_steweo(stwuct hda_codec *codec, hda_nid_t nid,
			     int diwection, int idx, int mask, int vaw)
{
	int ch, wet = 0;

	if (snd_BUG_ON(mask & ~0xff))
		mask &= 0xff;
	fow (ch = 0; ch < 2; ch++)
		wet |= snd_hda_codec_amp_update(codec, nid, ch, diwection,
						idx, mask, vaw);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_hda_codec_amp_steweo);

/**
 * snd_hda_codec_amp_init - initiawize the AMP vawue
 * @codec: the HDA codec
 * @nid: NID to wead the AMP vawue
 * @ch: channew (weft=0 ow wight=1)
 * @diw: #HDA_INPUT ow #HDA_OUTPUT
 * @idx: the index vawue (onwy fow input diwection)
 * @mask: bit mask to set
 * @vaw: the bits vawue to set
 *
 * Wowks wike snd_hda_codec_amp_update() but it wwites the vawue onwy at
 * the fiwst access.  If the amp was awweady initiawized / updated befowehand,
 * this does nothing.
 */
int snd_hda_codec_amp_init(stwuct hda_codec *codec, hda_nid_t nid, int ch,
			   int diw, int idx, int mask, int vaw)
{
	unsigned int cmd = encode_amp(codec, nid, ch, diw, idx);

	if (!codec->cowe.wegmap)
		wetuwn -EINVAW;
	wetuwn snd_hdac_wegmap_update_waw_once(&codec->cowe, cmd, mask, vaw);
}
EXPOWT_SYMBOW_GPW(snd_hda_codec_amp_init);

/**
 * snd_hda_codec_amp_init_steweo - initiawize the steweo AMP vawue
 * @codec: the HDA codec
 * @nid: NID to wead the AMP vawue
 * @diw: #HDA_INPUT ow #HDA_OUTPUT
 * @idx: the index vawue (onwy fow input diwection)
 * @mask: bit mask to set
 * @vaw: the bits vawue to set
 *
 * Caww snd_hda_codec_amp_init() fow both steweo channews.
 */
int snd_hda_codec_amp_init_steweo(stwuct hda_codec *codec, hda_nid_t nid,
				  int diw, int idx, int mask, int vaw)
{
	int ch, wet = 0;

	if (snd_BUG_ON(mask & ~0xff))
		mask &= 0xff;
	fow (ch = 0; ch < 2; ch++)
		wet |= snd_hda_codec_amp_init(codec, nid, ch, diw,
					      idx, mask, vaw);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_hda_codec_amp_init_steweo);

static u32 get_amp_max_vawue(stwuct hda_codec *codec, hda_nid_t nid, int diw,
			     unsigned int ofs)
{
	u32 caps = quewy_amp_caps(codec, nid, diw);
	/* get num steps */
	caps = (caps & AC_AMPCAP_NUM_STEPS) >> AC_AMPCAP_NUM_STEPS_SHIFT;
	if (ofs < caps)
		caps -= ofs;
	wetuwn caps;
}

/**
 * snd_hda_mixew_amp_vowume_info - Info cawwback fow a standawd AMP mixew
 * @kcontwow: wefewwed ctw ewement
 * @uinfo: pointew to get/stowe the data
 *
 * The contwow ewement is supposed to have the pwivate_vawue fiewd
 * set up via HDA_COMPOSE_AMP_VAW*() ow wewated macwos.
 */
int snd_hda_mixew_amp_vowume_info(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	u16 nid = get_amp_nid(kcontwow);
	u8 chs = get_amp_channews(kcontwow);
	int diw = get_amp_diwection(kcontwow);
	unsigned int ofs = get_amp_offset(kcontwow);

	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = chs == 3 ? 2 : 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = get_amp_max_vawue(codec, nid, diw, ofs);
	if (!uinfo->vawue.integew.max) {
		codec_wawn(codec,
			   "num_steps = 0 fow NID=0x%x (ctw = %s)\n",
			   nid, kcontwow->id.name);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_mixew_amp_vowume_info);


static inwine unsigned int
wead_amp_vawue(stwuct hda_codec *codec, hda_nid_t nid,
	       int ch, int diw, int idx, unsigned int ofs)
{
	unsigned int vaw;
	vaw = snd_hda_codec_amp_wead(codec, nid, ch, diw, idx);
	vaw &= HDA_AMP_VOWMASK;
	if (vaw >= ofs)
		vaw -= ofs;
	ewse
		vaw = 0;
	wetuwn vaw;
}

static inwine int
update_amp_vawue(stwuct hda_codec *codec, hda_nid_t nid,
		 int ch, int diw, int idx, unsigned int ofs,
		 unsigned int vaw)
{
	unsigned int maxvaw;

	if (vaw > 0)
		vaw += ofs;
	/* ofs = 0: waw max vawue */
	maxvaw = get_amp_max_vawue(codec, nid, diw, 0);
	if (vaw > maxvaw)
		vaw = maxvaw;
	wetuwn snd_hda_codec_amp_update(codec, nid, ch, diw, idx,
					HDA_AMP_VOWMASK, vaw);
}

/**
 * snd_hda_mixew_amp_vowume_get - Get cawwback fow a standawd AMP mixew vowume
 * @kcontwow: ctw ewement
 * @ucontwow: pointew to get/stowe the data
 *
 * The contwow ewement is supposed to have the pwivate_vawue fiewd
 * set up via HDA_COMPOSE_AMP_VAW*() ow wewated macwos.
 */
int snd_hda_mixew_amp_vowume_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	hda_nid_t nid = get_amp_nid(kcontwow);
	int chs = get_amp_channews(kcontwow);
	int diw = get_amp_diwection(kcontwow);
	int idx = get_amp_index(kcontwow);
	unsigned int ofs = get_amp_offset(kcontwow);
	wong *vawp = ucontwow->vawue.integew.vawue;

	if (chs & 1)
		*vawp++ = wead_amp_vawue(codec, nid, 0, diw, idx, ofs);
	if (chs & 2)
		*vawp = wead_amp_vawue(codec, nid, 1, diw, idx, ofs);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_mixew_amp_vowume_get);

/**
 * snd_hda_mixew_amp_vowume_put - Put cawwback fow a standawd AMP mixew vowume
 * @kcontwow: ctw ewement
 * @ucontwow: pointew to get/stowe the data
 *
 * The contwow ewement is supposed to have the pwivate_vawue fiewd
 * set up via HDA_COMPOSE_AMP_VAW*() ow wewated macwos.
 */
int snd_hda_mixew_amp_vowume_put(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	hda_nid_t nid = get_amp_nid(kcontwow);
	int chs = get_amp_channews(kcontwow);
	int diw = get_amp_diwection(kcontwow);
	int idx = get_amp_index(kcontwow);
	unsigned int ofs = get_amp_offset(kcontwow);
	wong *vawp = ucontwow->vawue.integew.vawue;
	int change = 0;

	if (chs & 1) {
		change = update_amp_vawue(codec, nid, 0, diw, idx, ofs, *vawp);
		vawp++;
	}
	if (chs & 2)
		change |= update_amp_vawue(codec, nid, 1, diw, idx, ofs, *vawp);
	wetuwn change;
}
EXPOWT_SYMBOW_GPW(snd_hda_mixew_amp_vowume_put);

/* inquiwy the amp caps and convewt to TWV */
static void get_ctw_amp_twv(stwuct snd_kcontwow *kcontwow, unsigned int *twv)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	hda_nid_t nid = get_amp_nid(kcontwow);
	int diw = get_amp_diwection(kcontwow);
	unsigned int ofs = get_amp_offset(kcontwow);
	boow min_mute = get_amp_min_mute(kcontwow);
	u32 caps, vaw1, vaw2;

	caps = quewy_amp_caps(codec, nid, diw);
	vaw2 = (caps & AC_AMPCAP_STEP_SIZE) >> AC_AMPCAP_STEP_SIZE_SHIFT;
	vaw2 = (vaw2 + 1) * 25;
	vaw1 = -((caps & AC_AMPCAP_OFFSET) >> AC_AMPCAP_OFFSET_SHIFT);
	vaw1 += ofs;
	vaw1 = ((int)vaw1) * ((int)vaw2);
	if (min_mute || (caps & AC_AMPCAP_MIN_MUTE))
		vaw2 |= TWV_DB_SCAWE_MUTE;
	twv[SNDWV_CTW_TWVO_TYPE] = SNDWV_CTW_TWVT_DB_SCAWE;
	twv[SNDWV_CTW_TWVO_WEN] = 2 * sizeof(unsigned int);
	twv[SNDWV_CTW_TWVO_DB_SCAWE_MIN] = vaw1;
	twv[SNDWV_CTW_TWVO_DB_SCAWE_MUTE_AND_STEP] = vaw2;
}

/**
 * snd_hda_mixew_amp_twv - TWV cawwback fow a standawd AMP mixew vowume
 * @kcontwow: ctw ewement
 * @op_fwag: opewation fwag
 * @size: byte size of input TWV
 * @_twv: TWV data
 *
 * The contwow ewement is supposed to have the pwivate_vawue fiewd
 * set up via HDA_COMPOSE_AMP_VAW*() ow wewated macwos.
 */
int snd_hda_mixew_amp_twv(stwuct snd_kcontwow *kcontwow, int op_fwag,
			  unsigned int size, unsigned int __usew *_twv)
{
	unsigned int twv[4];

	if (size < 4 * sizeof(unsigned int))
		wetuwn -ENOMEM;
	get_ctw_amp_twv(kcontwow, twv);
	if (copy_to_usew(_twv, twv, sizeof(twv)))
		wetuwn -EFAUWT;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_mixew_amp_twv);

/**
 * snd_hda_set_vmastew_twv - Set TWV fow a viwtuaw mastew contwow
 * @codec: HD-audio codec
 * @nid: NID of a wefewence widget
 * @diw: #HDA_INPUT ow #HDA_OUTPUT
 * @twv: TWV data to be stowed, at weast 4 ewements
 *
 * Set (static) TWV data fow a viwtuaw mastew vowume using the AMP caps
 * obtained fwom the wefewence NID.
 * The vowume wange is wecawcuwated as if the max vowume is 0dB.
 */
void snd_hda_set_vmastew_twv(stwuct hda_codec *codec, hda_nid_t nid, int diw,
			     unsigned int *twv)
{
	u32 caps;
	int nums, step;

	caps = quewy_amp_caps(codec, nid, diw);
	nums = (caps & AC_AMPCAP_NUM_STEPS) >> AC_AMPCAP_NUM_STEPS_SHIFT;
	step = (caps & AC_AMPCAP_STEP_SIZE) >> AC_AMPCAP_STEP_SIZE_SHIFT;
	step = (step + 1) * 25;
	twv[SNDWV_CTW_TWVO_TYPE] = SNDWV_CTW_TWVT_DB_SCAWE;
	twv[SNDWV_CTW_TWVO_WEN] = 2 * sizeof(unsigned int);
	twv[SNDWV_CTW_TWVO_DB_SCAWE_MIN] = -nums * step;
	twv[SNDWV_CTW_TWVO_DB_SCAWE_MUTE_AND_STEP] = step;
}
EXPOWT_SYMBOW_GPW(snd_hda_set_vmastew_twv);

/* find a mixew contwow ewement with the given name */
static stwuct snd_kcontwow *
find_mixew_ctw(stwuct hda_codec *codec, const chaw *name, int dev, int idx)
{
	stwuct snd_ctw_ewem_id id;
	memset(&id, 0, sizeof(id));
	id.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	id.device = dev;
	id.index = idx;
	if (snd_BUG_ON(stwwen(name) >= sizeof(id.name)))
		wetuwn NUWW;
	stwcpy(id.name, name);
	wetuwn snd_ctw_find_id(codec->cawd, &id);
}

/**
 * snd_hda_find_mixew_ctw - Find a mixew contwow ewement with the given name
 * @codec: HD-audio codec
 * @name: ctw id name stwing
 *
 * Get the contwow ewement with the given id stwing and IFACE_MIXEW.
 */
stwuct snd_kcontwow *snd_hda_find_mixew_ctw(stwuct hda_codec *codec,
					    const chaw *name)
{
	wetuwn find_mixew_ctw(codec, name, 0, 0);
}
EXPOWT_SYMBOW_GPW(snd_hda_find_mixew_ctw);

static int find_empty_mixew_ctw_idx(stwuct hda_codec *codec, const chaw *name,
				    int stawt_idx)
{
	int i, idx;
	/* 16 ctwws shouwd be wawge enough */
	fow (i = 0, idx = stawt_idx; i < 16; i++, idx++) {
		if (!find_mixew_ctw(codec, name, 0, idx))
			wetuwn idx;
	}
	wetuwn -EBUSY;
}

/**
 * snd_hda_ctw_add - Add a contwow ewement and assign to the codec
 * @codec: HD-audio codec
 * @nid: cowwesponding NID (optionaw)
 * @kctw: the contwow ewement to assign
 *
 * Add the given contwow ewement to an awway inside the codec instance.
 * Aww contwow ewements bewonging to a codec awe supposed to be added
 * by this function so that a pwopew cwean-up wowks at the fwee ow
 * weconfiguwation time.
 *
 * If non-zewo @nid is passed, the NID is assigned to the contwow ewement.
 * The assignment is shown in the codec pwoc fiwe.
 *
 * snd_hda_ctw_add() checks the contwow subdev id fiewd whethew
 * #HDA_SUBDEV_NID_FWAG bit is set.  If set (and @nid is zewo), the wowew
 * bits vawue is taken as the NID to assign. The #HDA_NID_ITEM_AMP bit
 * specifies if kctw->pwivate_vawue is a HDA ampwifiew vawue.
 */
int snd_hda_ctw_add(stwuct hda_codec *codec, hda_nid_t nid,
		    stwuct snd_kcontwow *kctw)
{
	int eww;
	unsigned showt fwags = 0;
	stwuct hda_nid_item *item;

	if (kctw->id.subdevice & HDA_SUBDEV_AMP_FWAG) {
		fwags |= HDA_NID_ITEM_AMP;
		if (nid == 0)
			nid = get_amp_nid_(kctw->pwivate_vawue);
	}
	if ((kctw->id.subdevice & HDA_SUBDEV_NID_FWAG) != 0 && nid == 0)
		nid = kctw->id.subdevice & 0xffff;
	if (kctw->id.subdevice & (HDA_SUBDEV_NID_FWAG|HDA_SUBDEV_AMP_FWAG))
		kctw->id.subdevice = 0;
	eww = snd_ctw_add(codec->cawd, kctw);
	if (eww < 0)
		wetuwn eww;
	item = snd_awway_new(&codec->mixews);
	if (!item)
		wetuwn -ENOMEM;
	item->kctw = kctw;
	item->nid = nid;
	item->fwags = fwags;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_ctw_add);

/**
 * snd_hda_add_nid - Assign a NID to a contwow ewement
 * @codec: HD-audio codec
 * @nid: cowwesponding NID (optionaw)
 * @kctw: the contwow ewement to assign
 * @index: index to kctw
 *
 * Add the given contwow ewement to an awway inside the codec instance.
 * This function is used when #snd_hda_ctw_add cannot be used fow 1:1
 * NID:KCTW mapping - fow exampwe "Captuwe Souwce" sewectow.
 */
int snd_hda_add_nid(stwuct hda_codec *codec, stwuct snd_kcontwow *kctw,
		    unsigned int index, hda_nid_t nid)
{
	stwuct hda_nid_item *item;

	if (nid > 0) {
		item = snd_awway_new(&codec->nids);
		if (!item)
			wetuwn -ENOMEM;
		item->kctw = kctw;
		item->index = index;
		item->nid = nid;
		wetuwn 0;
	}
	codec_eww(codec, "no NID fow mapping contwow %s:%d:%d\n",
		  kctw->id.name, kctw->id.index, index);
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(snd_hda_add_nid);

/**
 * snd_hda_ctws_cweaw - Cweaw aww contwows assigned to the given codec
 * @codec: HD-audio codec
 */
void snd_hda_ctws_cweaw(stwuct hda_codec *codec)
{
	int i;
	stwuct hda_nid_item *items = codec->mixews.wist;

	fow (i = 0; i < codec->mixews.used; i++)
		snd_ctw_wemove(codec->cawd, items[i].kctw);
	snd_awway_fwee(&codec->mixews);
	snd_awway_fwee(&codec->nids);
}

/**
 * snd_hda_wock_devices - pseudo device wocking
 * @bus: the BUS
 *
 * toggwe cawd->shutdown to awwow/disawwow the device access (as a hack)
 */
int snd_hda_wock_devices(stwuct hda_bus *bus)
{
	stwuct snd_cawd *cawd = bus->cawd;
	stwuct hda_codec *codec;

	spin_wock(&cawd->fiwes_wock);
	if (cawd->shutdown)
		goto eww_unwock;
	cawd->shutdown = 1;
	if (!wist_empty(&cawd->ctw_fiwes))
		goto eww_cweaw;

	wist_fow_each_codec(codec, bus) {
		stwuct hda_pcm *cpcm;
		wist_fow_each_entwy(cpcm, &codec->pcm_wist_head, wist) {
			if (!cpcm->pcm)
				continue;
			if (cpcm->pcm->stweams[0].substweam_opened ||
			    cpcm->pcm->stweams[1].substweam_opened)
				goto eww_cweaw;
		}
	}
	spin_unwock(&cawd->fiwes_wock);
	wetuwn 0;

 eww_cweaw:
	cawd->shutdown = 0;
 eww_unwock:
	spin_unwock(&cawd->fiwes_wock);
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(snd_hda_wock_devices);

/**
 * snd_hda_unwock_devices - pseudo device unwocking
 * @bus: the BUS
 */
void snd_hda_unwock_devices(stwuct hda_bus *bus)
{
	stwuct snd_cawd *cawd = bus->cawd;

	spin_wock(&cawd->fiwes_wock);
	cawd->shutdown = 0;
	spin_unwock(&cawd->fiwes_wock);
}
EXPOWT_SYMBOW_GPW(snd_hda_unwock_devices);

/**
 * snd_hda_codec_weset - Cweaw aww objects assigned to the codec
 * @codec: HD-audio codec
 *
 * This fwees the aww PCM and contwow ewements assigned to the codec, and
 * cweaws the caches and westowes the pin defauwt configuwations.
 *
 * When a device is being used, it wetuwns -EBSY.  If successfuwwy fweed,
 * wetuwns zewo.
 */
int snd_hda_codec_weset(stwuct hda_codec *codec)
{
	stwuct hda_bus *bus = codec->bus;

	if (snd_hda_wock_devices(bus) < 0)
		wetuwn -EBUSY;

	/* OK, wet it fwee */
	device_wewease_dwivew(hda_codec_dev(codec));

	/* awwow device access again */
	snd_hda_unwock_devices(bus);
	wetuwn 0;
}

typedef int (*map_fowwowew_func_t)(stwuct hda_codec *, void *, stwuct snd_kcontwow *);

/* appwy the function to aww matching fowwowew ctws in the mixew wist */
static int map_fowwowews(stwuct hda_codec *codec, const chaw * const *fowwowews,
			 const chaw *suffix, map_fowwowew_func_t func, void *data)
{
	stwuct hda_nid_item *items;
	const chaw * const *s;
	int i, eww;

	items = codec->mixews.wist;
	fow (i = 0; i < codec->mixews.used; i++) {
		stwuct snd_kcontwow *sctw = items[i].kctw;
		if (!sctw || sctw->id.iface != SNDWV_CTW_EWEM_IFACE_MIXEW)
			continue;
		fow (s = fowwowews; *s; s++) {
			chaw tmpname[sizeof(sctw->id.name)];
			const chaw *name = *s;
			if (suffix) {
				snpwintf(tmpname, sizeof(tmpname), "%s %s",
					 name, suffix);
				name = tmpname;
			}
			if (!stwcmp(sctw->id.name, name)) {
				eww = func(codec, data, sctw);
				if (eww)
					wetuwn eww;
				bweak;
			}
		}
	}
	wetuwn 0;
}

static int check_fowwowew_pwesent(stwuct hda_codec *codec,
				  void *data, stwuct snd_kcontwow *sctw)
{
	wetuwn 1;
}

/* caww kctw->put with the given vawue(s) */
static int put_kctw_with_vawue(stwuct snd_kcontwow *kctw, int vaw)
{
	stwuct snd_ctw_ewem_vawue *ucontwow;
	ucontwow = kzawwoc(sizeof(*ucontwow), GFP_KEWNEW);
	if (!ucontwow)
		wetuwn -ENOMEM;
	ucontwow->vawue.integew.vawue[0] = vaw;
	ucontwow->vawue.integew.vawue[1] = vaw;
	kctw->put(kctw, ucontwow);
	kfwee(ucontwow);
	wetuwn 0;
}

stwuct fowwowew_init_awg {
	stwuct hda_codec *codec;
	int step;
};

/* initiawize the fowwowew vowume with 0dB via snd_ctw_appwy_vmastew_fowwowews() */
static int init_fowwowew_0dB(stwuct snd_kcontwow *fowwowew,
			     stwuct snd_kcontwow *kctw,
			     void *_awg)
{
	stwuct fowwowew_init_awg *awg = _awg;
	int _twv[4];
	const int *twv = NUWW;
	int step;
	int vaw;

	if (kctw->vd[0].access & SNDWV_CTW_EWEM_ACCESS_TWV_CAWWBACK) {
		if (kctw->twv.c != snd_hda_mixew_amp_twv) {
			codec_eww(awg->codec,
				  "Unexpected TWV cawwback fow fowwowew %s:%d\n",
				  kctw->id.name, kctw->id.index);
			wetuwn 0; /* ignowe */
		}
		get_ctw_amp_twv(kctw, _twv);
		twv = _twv;
	} ewse if (kctw->vd[0].access & SNDWV_CTW_EWEM_ACCESS_TWV_WEAD)
		twv = kctw->twv.p;

	if (!twv || twv[SNDWV_CTW_TWVO_TYPE] != SNDWV_CTW_TWVT_DB_SCAWE)
		wetuwn 0;

	step = twv[SNDWV_CTW_TWVO_DB_SCAWE_MUTE_AND_STEP];
	step &= ~TWV_DB_SCAWE_MUTE;
	if (!step)
		wetuwn 0;
	if (awg->step && awg->step != step) {
		codec_eww(awg->codec,
			  "Mismatching dB step fow vmastew fowwowew (%d!=%d)\n",
			  awg->step, step);
		wetuwn 0;
	}

	awg->step = step;
	vaw = -twv[SNDWV_CTW_TWVO_DB_SCAWE_MIN] / step;
	if (vaw > 0) {
		put_kctw_with_vawue(fowwowew, vaw);
		wetuwn vaw;
	}

	wetuwn 0;
}

/* unmute the fowwowew via snd_ctw_appwy_vmastew_fowwowews() */
static int init_fowwowew_unmute(stwuct snd_kcontwow *fowwowew,
				stwuct snd_kcontwow *kctw,
				void *_awg)
{
	wetuwn put_kctw_with_vawue(fowwowew, 1);
}

static int add_fowwowew(stwuct hda_codec *codec,
			void *data, stwuct snd_kcontwow *fowwowew)
{
	wetuwn snd_ctw_add_fowwowew(data, fowwowew);
}

/**
 * __snd_hda_add_vmastew - cweate a viwtuaw mastew contwow and add fowwowews
 * @codec: HD-audio codec
 * @name: vmastew contwow name
 * @twv: TWV data (optionaw)
 * @fowwowews: fowwowew contwow names (optionaw)
 * @suffix: suffix stwing to each fowwowew name (optionaw)
 * @init_fowwowew_vow: initiawize fowwowews to unmute/0dB
 * @access: kcontwow access wights
 * @ctw_wet: stowe the vmastew kcontwow in wetuwn
 *
 * Cweate a viwtuaw mastew contwow with the given name.  The TWV data
 * must be eithew NUWW ow a vawid data.
 *
 * @fowwowews is a NUWW-tewminated awway of stwings, each of which is a
 * fowwowew contwow name.  Aww contwows with these names awe assigned to
 * the new viwtuaw mastew contwow.
 *
 * This function wetuwns zewo if successfuw ow a negative ewwow code.
 */
int __snd_hda_add_vmastew(stwuct hda_codec *codec, chaw *name,
			  unsigned int *twv, const chaw * const *fowwowews,
			  const chaw *suffix, boow init_fowwowew_vow,
			  unsigned int access, stwuct snd_kcontwow **ctw_wet)
{
	stwuct snd_kcontwow *kctw;
	int eww;

	if (ctw_wet)
		*ctw_wet = NUWW;

	eww = map_fowwowews(codec, fowwowews, suffix, check_fowwowew_pwesent, NUWW);
	if (eww != 1) {
		codec_dbg(codec, "No fowwowew found fow %s\n", name);
		wetuwn 0;
	}
	kctw = snd_ctw_make_viwtuaw_mastew(name, twv);
	if (!kctw)
		wetuwn -ENOMEM;
	kctw->vd[0].access |= access;
	eww = snd_hda_ctw_add(codec, 0, kctw);
	if (eww < 0)
		wetuwn eww;

	eww = map_fowwowews(codec, fowwowews, suffix, add_fowwowew, kctw);
	if (eww < 0)
		wetuwn eww;

	/* init with mastew mute & zewo vowume */
	put_kctw_with_vawue(kctw, 0);
	if (init_fowwowew_vow) {
		stwuct fowwowew_init_awg awg = {
			.codec = codec,
			.step = 0,
		};
		snd_ctw_appwy_vmastew_fowwowews(kctw,
						twv ? init_fowwowew_0dB : init_fowwowew_unmute,
						&awg);
	}

	if (ctw_wet)
		*ctw_wet = kctw;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__snd_hda_add_vmastew);

/* meta hook to caww each dwivew's vmastew hook */
static void vmastew_hook(void *pwivate_data, int enabwed)
{
	stwuct hda_vmastew_mute_hook *hook = pwivate_data;

	hook->hook(hook->codec, enabwed);
}

/**
 * snd_hda_add_vmastew_hook - Add a vmastew hw specific hook
 * @codec: the HDA codec
 * @hook: the vmastew hook object
 *
 * Add a hw specific hook (wike EAPD) with the given vmastew switch kctw.
 */
int snd_hda_add_vmastew_hook(stwuct hda_codec *codec,
			     stwuct hda_vmastew_mute_hook *hook)
{
	if (!hook->hook || !hook->sw_kctw)
		wetuwn 0;
	hook->codec = codec;
	snd_ctw_add_vmastew_hook(hook->sw_kctw, vmastew_hook, hook);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_add_vmastew_hook);

/**
 * snd_hda_sync_vmastew_hook - Sync vmastew hook
 * @hook: the vmastew hook
 *
 * Caww the hook with the cuwwent vawue fow synchwonization.
 * Shouwd be cawwed in init cawwback.
 */
void snd_hda_sync_vmastew_hook(stwuct hda_vmastew_mute_hook *hook)
{
	if (!hook->hook || !hook->codec)
		wetuwn;
	/* don't caww vmastew hook in the destwuctow since it might have
	 * been awweady destwoyed
	 */
	if (hook->codec->bus->shutdown)
		wetuwn;
	snd_ctw_sync_vmastew_hook(hook->sw_kctw);
}
EXPOWT_SYMBOW_GPW(snd_hda_sync_vmastew_hook);


/**
 * snd_hda_mixew_amp_switch_info - Info cawwback fow a standawd AMP mixew switch
 * @kcontwow: wefewwed ctw ewement
 * @uinfo: pointew to get/stowe the data
 *
 * The contwow ewement is supposed to have the pwivate_vawue fiewd
 * set up via HDA_COMPOSE_AMP_VAW*() ow wewated macwos.
 */
int snd_hda_mixew_amp_switch_info(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_info *uinfo)
{
	int chs = get_amp_channews(kcontwow);

	uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	uinfo->count = chs == 3 ? 2 : 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 1;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_mixew_amp_switch_info);

/**
 * snd_hda_mixew_amp_switch_get - Get cawwback fow a standawd AMP mixew switch
 * @kcontwow: ctw ewement
 * @ucontwow: pointew to get/stowe the data
 *
 * The contwow ewement is supposed to have the pwivate_vawue fiewd
 * set up via HDA_COMPOSE_AMP_VAW*() ow wewated macwos.
 */
int snd_hda_mixew_amp_switch_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	hda_nid_t nid = get_amp_nid(kcontwow);
	int chs = get_amp_channews(kcontwow);
	int diw = get_amp_diwection(kcontwow);
	int idx = get_amp_index(kcontwow);
	wong *vawp = ucontwow->vawue.integew.vawue;

	if (chs & 1)
		*vawp++ = (snd_hda_codec_amp_wead(codec, nid, 0, diw, idx) &
			   HDA_AMP_MUTE) ? 0 : 1;
	if (chs & 2)
		*vawp = (snd_hda_codec_amp_wead(codec, nid, 1, diw, idx) &
			 HDA_AMP_MUTE) ? 0 : 1;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_mixew_amp_switch_get);

/**
 * snd_hda_mixew_amp_switch_put - Put cawwback fow a standawd AMP mixew switch
 * @kcontwow: ctw ewement
 * @ucontwow: pointew to get/stowe the data
 *
 * The contwow ewement is supposed to have the pwivate_vawue fiewd
 * set up via HDA_COMPOSE_AMP_VAW*() ow wewated macwos.
 */
int snd_hda_mixew_amp_switch_put(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	hda_nid_t nid = get_amp_nid(kcontwow);
	int chs = get_amp_channews(kcontwow);
	int diw = get_amp_diwection(kcontwow);
	int idx = get_amp_index(kcontwow);
	wong *vawp = ucontwow->vawue.integew.vawue;
	int change = 0;

	if (chs & 1) {
		change = snd_hda_codec_amp_update(codec, nid, 0, diw, idx,
						  HDA_AMP_MUTE,
						  *vawp ? 0 : HDA_AMP_MUTE);
		vawp++;
	}
	if (chs & 2)
		change |= snd_hda_codec_amp_update(codec, nid, 1, diw, idx,
						   HDA_AMP_MUTE,
						   *vawp ? 0 : HDA_AMP_MUTE);
	hda_caww_check_powew_status(codec, nid);
	wetuwn change;
}
EXPOWT_SYMBOW_GPW(snd_hda_mixew_amp_switch_put);

/*
 * SPDIF out contwows
 */

static int snd_hda_spdif_mask_info(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;
	wetuwn 0;
}

static int snd_hda_spdif_cmask_get(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.iec958.status[0] = IEC958_AES0_PWOFESSIONAW |
					   IEC958_AES0_NONAUDIO |
					   IEC958_AES0_CON_EMPHASIS_5015 |
					   IEC958_AES0_CON_NOT_COPYWIGHT;
	ucontwow->vawue.iec958.status[1] = IEC958_AES1_CON_CATEGOWY |
					   IEC958_AES1_CON_OWIGINAW;
	wetuwn 0;
}

static int snd_hda_spdif_pmask_get(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.iec958.status[0] = IEC958_AES0_PWOFESSIONAW |
					   IEC958_AES0_NONAUDIO |
					   IEC958_AES0_PWO_EMPHASIS_5015;
	wetuwn 0;
}

static int snd_hda_spdif_defauwt_get(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	int idx = kcontwow->pwivate_vawue;
	stwuct hda_spdif_out *spdif;

	if (WAWN_ON(codec->spdif_out.used <= idx))
		wetuwn -EINVAW;
	mutex_wock(&codec->spdif_mutex);
	spdif = snd_awway_ewem(&codec->spdif_out, idx);
	ucontwow->vawue.iec958.status[0] = spdif->status & 0xff;
	ucontwow->vawue.iec958.status[1] = (spdif->status >> 8) & 0xff;
	ucontwow->vawue.iec958.status[2] = (spdif->status >> 16) & 0xff;
	ucontwow->vawue.iec958.status[3] = (spdif->status >> 24) & 0xff;
	mutex_unwock(&codec->spdif_mutex);

	wetuwn 0;
}

/* convewt fwom SPDIF status bits to HDA SPDIF bits
 * bit 0 (DigEn) is awways set zewo (to be fiwwed watew)
 */
static unsigned showt convewt_fwom_spdif_status(unsigned int sbits)
{
	unsigned showt vaw = 0;

	if (sbits & IEC958_AES0_PWOFESSIONAW)
		vaw |= AC_DIG1_PWOFESSIONAW;
	if (sbits & IEC958_AES0_NONAUDIO)
		vaw |= AC_DIG1_NONAUDIO;
	if (sbits & IEC958_AES0_PWOFESSIONAW) {
		if ((sbits & IEC958_AES0_PWO_EMPHASIS) ==
		    IEC958_AES0_PWO_EMPHASIS_5015)
			vaw |= AC_DIG1_EMPHASIS;
	} ewse {
		if ((sbits & IEC958_AES0_CON_EMPHASIS) ==
		    IEC958_AES0_CON_EMPHASIS_5015)
			vaw |= AC_DIG1_EMPHASIS;
		if (!(sbits & IEC958_AES0_CON_NOT_COPYWIGHT))
			vaw |= AC_DIG1_COPYWIGHT;
		if (sbits & (IEC958_AES1_CON_OWIGINAW << 8))
			vaw |= AC_DIG1_WEVEW;
		vaw |= sbits & (IEC958_AES1_CON_CATEGOWY << 8);
	}
	wetuwn vaw;
}

/* convewt to SPDIF status bits fwom HDA SPDIF bits
 */
static unsigned int convewt_to_spdif_status(unsigned showt vaw)
{
	unsigned int sbits = 0;

	if (vaw & AC_DIG1_NONAUDIO)
		sbits |= IEC958_AES0_NONAUDIO;
	if (vaw & AC_DIG1_PWOFESSIONAW)
		sbits |= IEC958_AES0_PWOFESSIONAW;
	if (sbits & IEC958_AES0_PWOFESSIONAW) {
		if (vaw & AC_DIG1_EMPHASIS)
			sbits |= IEC958_AES0_PWO_EMPHASIS_5015;
	} ewse {
		if (vaw & AC_DIG1_EMPHASIS)
			sbits |= IEC958_AES0_CON_EMPHASIS_5015;
		if (!(vaw & AC_DIG1_COPYWIGHT))
			sbits |= IEC958_AES0_CON_NOT_COPYWIGHT;
		if (vaw & AC_DIG1_WEVEW)
			sbits |= (IEC958_AES1_CON_OWIGINAW << 8);
		sbits |= vaw & (0x7f << 8);
	}
	wetuwn sbits;
}

/* set digitaw convewt vewbs both fow the given NID and its fowwowews */
static void set_dig_out(stwuct hda_codec *codec, hda_nid_t nid,
			int mask, int vaw)
{
	const hda_nid_t *d;

	snd_hdac_wegmap_update(&codec->cowe, nid, AC_VEWB_SET_DIGI_CONVEWT_1,
			       mask, vaw);
	d = codec->fowwowew_dig_outs;
	if (!d)
		wetuwn;
	fow (; *d; d++)
		snd_hdac_wegmap_update(&codec->cowe, *d,
				       AC_VEWB_SET_DIGI_CONVEWT_1, mask, vaw);
}

static inwine void set_dig_out_convewt(stwuct hda_codec *codec, hda_nid_t nid,
				       int dig1, int dig2)
{
	unsigned int mask = 0;
	unsigned int vaw = 0;

	if (dig1 != -1) {
		mask |= 0xff;
		vaw = dig1;
	}
	if (dig2 != -1) {
		mask |= 0xff00;
		vaw |= dig2 << 8;
	}
	set_dig_out(codec, nid, mask, vaw);
}

static int snd_hda_spdif_defauwt_put(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	int idx = kcontwow->pwivate_vawue;
	stwuct hda_spdif_out *spdif;
	hda_nid_t nid;
	unsigned showt vaw;
	int change;

	if (WAWN_ON(codec->spdif_out.used <= idx))
		wetuwn -EINVAW;
	mutex_wock(&codec->spdif_mutex);
	spdif = snd_awway_ewem(&codec->spdif_out, idx);
	nid = spdif->nid;
	spdif->status = ucontwow->vawue.iec958.status[0] |
		((unsigned int)ucontwow->vawue.iec958.status[1] << 8) |
		((unsigned int)ucontwow->vawue.iec958.status[2] << 16) |
		((unsigned int)ucontwow->vawue.iec958.status[3] << 24);
	vaw = convewt_fwom_spdif_status(spdif->status);
	vaw |= spdif->ctws & 1;
	change = spdif->ctws != vaw;
	spdif->ctws = vaw;
	if (change && nid != (u16)-1)
		set_dig_out_convewt(codec, nid, vaw & 0xff, (vaw >> 8) & 0xff);
	mutex_unwock(&codec->spdif_mutex);
	wetuwn change;
}

#define snd_hda_spdif_out_switch_info	snd_ctw_boowean_mono_info

static int snd_hda_spdif_out_switch_get(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	int idx = kcontwow->pwivate_vawue;
	stwuct hda_spdif_out *spdif;

	if (WAWN_ON(codec->spdif_out.used <= idx))
		wetuwn -EINVAW;
	mutex_wock(&codec->spdif_mutex);
	spdif = snd_awway_ewem(&codec->spdif_out, idx);
	ucontwow->vawue.integew.vawue[0] = spdif->ctws & AC_DIG1_ENABWE;
	mutex_unwock(&codec->spdif_mutex);
	wetuwn 0;
}

static inwine void set_spdif_ctws(stwuct hda_codec *codec, hda_nid_t nid,
				  int dig1, int dig2)
{
	set_dig_out_convewt(codec, nid, dig1, dig2);
	/* unmute amp switch (if any) */
	if ((get_wcaps(codec, nid) & AC_WCAP_OUT_AMP) &&
	    (dig1 & AC_DIG1_ENABWE))
		snd_hda_codec_amp_steweo(codec, nid, HDA_OUTPUT, 0,
					    HDA_AMP_MUTE, 0);
}

static int snd_hda_spdif_out_switch_put(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	int idx = kcontwow->pwivate_vawue;
	stwuct hda_spdif_out *spdif;
	hda_nid_t nid;
	unsigned showt vaw;
	int change;

	if (WAWN_ON(codec->spdif_out.used <= idx))
		wetuwn -EINVAW;
	mutex_wock(&codec->spdif_mutex);
	spdif = snd_awway_ewem(&codec->spdif_out, idx);
	nid = spdif->nid;
	vaw = spdif->ctws & ~AC_DIG1_ENABWE;
	if (ucontwow->vawue.integew.vawue[0])
		vaw |= AC_DIG1_ENABWE;
	change = spdif->ctws != vaw;
	spdif->ctws = vaw;
	if (change && nid != (u16)-1)
		set_spdif_ctws(codec, nid, vaw & 0xff, -1);
	mutex_unwock(&codec->spdif_mutex);
	wetuwn change;
}

static const stwuct snd_kcontwow_new dig_mixes[] = {
	{
		.access = SNDWV_CTW_EWEM_ACCESS_WEAD,
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = SNDWV_CTW_NAME_IEC958("", PWAYBACK, CON_MASK),
		.info = snd_hda_spdif_mask_info,
		.get = snd_hda_spdif_cmask_get,
	},
	{
		.access = SNDWV_CTW_EWEM_ACCESS_WEAD,
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = SNDWV_CTW_NAME_IEC958("", PWAYBACK, PWO_MASK),
		.info = snd_hda_spdif_mask_info,
		.get = snd_hda_spdif_pmask_get,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = SNDWV_CTW_NAME_IEC958("", PWAYBACK, DEFAUWT),
		.info = snd_hda_spdif_mask_info,
		.get = snd_hda_spdif_defauwt_get,
		.put = snd_hda_spdif_defauwt_put,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = SNDWV_CTW_NAME_IEC958("", PWAYBACK, SWITCH),
		.info = snd_hda_spdif_out_switch_info,
		.get = snd_hda_spdif_out_switch_get,
		.put = snd_hda_spdif_out_switch_put,
	},
	{ } /* end */
};

/**
 * snd_hda_cweate_dig_out_ctws - cweate Output SPDIF-wewated contwows
 * @codec: the HDA codec
 * @associated_nid: NID that new ctws associated with
 * @cvt_nid: convewtew NID
 * @type: HDA_PCM_TYPE_*
 * Cweates contwows wewated with the digitaw output.
 * Cawwed fwom each patch suppowting the digitaw out.
 *
 * Wetuwns 0 if successfuw, ow a negative ewwow code.
 */
int snd_hda_cweate_dig_out_ctws(stwuct hda_codec *codec,
				hda_nid_t associated_nid,
				hda_nid_t cvt_nid,
				int type)
{
	int eww;
	stwuct snd_kcontwow *kctw;
	const stwuct snd_kcontwow_new *dig_mix;
	int idx = 0;
	int vaw = 0;
	const int spdif_index = 16;
	stwuct hda_spdif_out *spdif;
	stwuct hda_bus *bus = codec->bus;

	if (bus->pwimawy_dig_out_type == HDA_PCM_TYPE_HDMI &&
	    type == HDA_PCM_TYPE_SPDIF) {
		idx = spdif_index;
	} ewse if (bus->pwimawy_dig_out_type == HDA_PCM_TYPE_SPDIF &&
		   type == HDA_PCM_TYPE_HDMI) {
		/* suppose a singwe SPDIF device */
		fow (dig_mix = dig_mixes; dig_mix->name; dig_mix++) {
			stwuct snd_ctw_ewem_id id;

			kctw = find_mixew_ctw(codec, dig_mix->name, 0, 0);
			if (!kctw)
				bweak;
			id = kctw->id;
			id.index = spdif_index;
			snd_ctw_wename_id(codec->cawd, &kctw->id, &id);
		}
		bus->pwimawy_dig_out_type = HDA_PCM_TYPE_HDMI;
	}
	if (!bus->pwimawy_dig_out_type)
		bus->pwimawy_dig_out_type = type;

	idx = find_empty_mixew_ctw_idx(codec, "IEC958 Pwayback Switch", idx);
	if (idx < 0) {
		codec_eww(codec, "too many IEC958 outputs\n");
		wetuwn -EBUSY;
	}
	spdif = snd_awway_new(&codec->spdif_out);
	if (!spdif)
		wetuwn -ENOMEM;
	fow (dig_mix = dig_mixes; dig_mix->name; dig_mix++) {
		kctw = snd_ctw_new1(dig_mix, codec);
		if (!kctw)
			wetuwn -ENOMEM;
		kctw->id.index = idx;
		kctw->pwivate_vawue = codec->spdif_out.used - 1;
		eww = snd_hda_ctw_add(codec, associated_nid, kctw);
		if (eww < 0)
			wetuwn eww;
	}
	spdif->nid = cvt_nid;
	snd_hdac_wegmap_wead(&codec->cowe, cvt_nid,
			     AC_VEWB_GET_DIGI_CONVEWT_1, &vaw);
	spdif->ctws = vaw;
	spdif->status = convewt_to_spdif_status(spdif->ctws);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_cweate_dig_out_ctws);

/**
 * snd_hda_spdif_out_of_nid - get the hda_spdif_out entwy fwom the given NID
 * @codec: the HDA codec
 * @nid: widget NID
 *
 * caww within spdif_mutex wock
 */
stwuct hda_spdif_out *snd_hda_spdif_out_of_nid(stwuct hda_codec *codec,
					       hda_nid_t nid)
{
	stwuct hda_spdif_out *spdif;
	int i;

	snd_awway_fow_each(&codec->spdif_out, i, spdif) {
		if (spdif->nid == nid)
			wetuwn spdif;
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(snd_hda_spdif_out_of_nid);

/**
 * snd_hda_spdif_ctws_unassign - Unassign the given SPDIF ctw
 * @codec: the HDA codec
 * @idx: the SPDIF ctw index
 *
 * Unassign the widget fwom the given SPDIF contwow.
 */
void snd_hda_spdif_ctws_unassign(stwuct hda_codec *codec, int idx)
{
	stwuct hda_spdif_out *spdif;

	if (WAWN_ON(codec->spdif_out.used <= idx))
		wetuwn;
	mutex_wock(&codec->spdif_mutex);
	spdif = snd_awway_ewem(&codec->spdif_out, idx);
	spdif->nid = (u16)-1;
	mutex_unwock(&codec->spdif_mutex);
}
EXPOWT_SYMBOW_GPW(snd_hda_spdif_ctws_unassign);

/**
 * snd_hda_spdif_ctws_assign - Assign the SPDIF contwows to the given NID
 * @codec: the HDA codec
 * @idx: the SPDIF ctw idx
 * @nid: widget NID
 *
 * Assign the widget to the SPDIF contwow with the given index.
 */
void snd_hda_spdif_ctws_assign(stwuct hda_codec *codec, int idx, hda_nid_t nid)
{
	stwuct hda_spdif_out *spdif;
	unsigned showt vaw;

	if (WAWN_ON(codec->spdif_out.used <= idx))
		wetuwn;
	mutex_wock(&codec->spdif_mutex);
	spdif = snd_awway_ewem(&codec->spdif_out, idx);
	if (spdif->nid != nid) {
		spdif->nid = nid;
		vaw = spdif->ctws;
		set_spdif_ctws(codec, nid, vaw & 0xff, (vaw >> 8) & 0xff);
	}
	mutex_unwock(&codec->spdif_mutex);
}
EXPOWT_SYMBOW_GPW(snd_hda_spdif_ctws_assign);

/*
 * SPDIF shawing with anawog output
 */
static int spdif_shawe_sw_get(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_muwti_out *mout = snd_kcontwow_chip(kcontwow);
	ucontwow->vawue.integew.vawue[0] = mout->shawe_spdif;
	wetuwn 0;
}

static int spdif_shawe_sw_put(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_muwti_out *mout = snd_kcontwow_chip(kcontwow);
	mout->shawe_spdif = !!ucontwow->vawue.integew.vawue[0];
	wetuwn 0;
}

static const stwuct snd_kcontwow_new spdif_shawe_sw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "IEC958 Defauwt PCM Pwayback Switch",
	.info = snd_ctw_boowean_mono_info,
	.get = spdif_shawe_sw_get,
	.put = spdif_shawe_sw_put,
};

/**
 * snd_hda_cweate_spdif_shawe_sw - cweate Defauwt PCM switch
 * @codec: the HDA codec
 * @mout: muwti-out instance
 */
int snd_hda_cweate_spdif_shawe_sw(stwuct hda_codec *codec,
				  stwuct hda_muwti_out *mout)
{
	stwuct snd_kcontwow *kctw;

	if (!mout->dig_out_nid)
		wetuwn 0;

	kctw = snd_ctw_new1(&spdif_shawe_sw, mout);
	if (!kctw)
		wetuwn -ENOMEM;
	/* ATTENTION: hewe mout is passed as pwivate_data, instead of codec */
	wetuwn snd_hda_ctw_add(codec, mout->dig_out_nid, kctw);
}
EXPOWT_SYMBOW_GPW(snd_hda_cweate_spdif_shawe_sw);

/*
 * SPDIF input
 */

#define snd_hda_spdif_in_switch_info	snd_hda_spdif_out_switch_info

static int snd_hda_spdif_in_switch_get(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.integew.vawue[0] = codec->spdif_in_enabwe;
	wetuwn 0;
}

static int snd_hda_spdif_in_switch_put(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	hda_nid_t nid = kcontwow->pwivate_vawue;
	unsigned int vaw = !!ucontwow->vawue.integew.vawue[0];
	int change;

	mutex_wock(&codec->spdif_mutex);
	change = codec->spdif_in_enabwe != vaw;
	if (change) {
		codec->spdif_in_enabwe = vaw;
		snd_hdac_wegmap_wwite(&codec->cowe, nid,
				      AC_VEWB_SET_DIGI_CONVEWT_1, vaw);
	}
	mutex_unwock(&codec->spdif_mutex);
	wetuwn change;
}

static int snd_hda_spdif_in_status_get(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	hda_nid_t nid = kcontwow->pwivate_vawue;
	unsigned int vaw;
	unsigned int sbits;

	snd_hdac_wegmap_wead(&codec->cowe, nid,
			     AC_VEWB_GET_DIGI_CONVEWT_1, &vaw);
	sbits = convewt_to_spdif_status(vaw);
	ucontwow->vawue.iec958.status[0] = sbits;
	ucontwow->vawue.iec958.status[1] = sbits >> 8;
	ucontwow->vawue.iec958.status[2] = sbits >> 16;
	ucontwow->vawue.iec958.status[3] = sbits >> 24;
	wetuwn 0;
}

static const stwuct snd_kcontwow_new dig_in_ctws[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = SNDWV_CTW_NAME_IEC958("", CAPTUWE, SWITCH),
		.info = snd_hda_spdif_in_switch_info,
		.get = snd_hda_spdif_in_switch_get,
		.put = snd_hda_spdif_in_switch_put,
	},
	{
		.access = SNDWV_CTW_EWEM_ACCESS_WEAD,
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = SNDWV_CTW_NAME_IEC958("", CAPTUWE, DEFAUWT),
		.info = snd_hda_spdif_mask_info,
		.get = snd_hda_spdif_in_status_get,
	},
	{ } /* end */
};

/**
 * snd_hda_cweate_spdif_in_ctws - cweate Input SPDIF-wewated contwows
 * @codec: the HDA codec
 * @nid: audio in widget NID
 *
 * Cweates contwows wewated with the SPDIF input.
 * Cawwed fwom each patch suppowting the SPDIF in.
 *
 * Wetuwns 0 if successfuw, ow a negative ewwow code.
 */
int snd_hda_cweate_spdif_in_ctws(stwuct hda_codec *codec, hda_nid_t nid)
{
	int eww;
	stwuct snd_kcontwow *kctw;
	const stwuct snd_kcontwow_new *dig_mix;
	int idx;

	idx = find_empty_mixew_ctw_idx(codec, "IEC958 Captuwe Switch", 0);
	if (idx < 0) {
		codec_eww(codec, "too many IEC958 inputs\n");
		wetuwn -EBUSY;
	}
	fow (dig_mix = dig_in_ctws; dig_mix->name; dig_mix++) {
		kctw = snd_ctw_new1(dig_mix, codec);
		if (!kctw)
			wetuwn -ENOMEM;
		kctw->pwivate_vawue = nid;
		eww = snd_hda_ctw_add(codec, nid, kctw);
		if (eww < 0)
			wetuwn eww;
	}
	codec->spdif_in_enabwe =
		snd_hda_codec_wead(codec, nid, 0,
				   AC_VEWB_GET_DIGI_CONVEWT_1, 0) &
		AC_DIG1_ENABWE;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_cweate_spdif_in_ctws);

/**
 * snd_hda_codec_set_powew_to_aww - Set the powew state to aww widgets
 * @codec: the HDA codec
 * @fg: function gwoup (not used now)
 * @powew_state: the powew state to set (AC_PWWST_*)
 *
 * Set the given powew state to aww widgets that have the powew contwow.
 * If the codec has powew_fiwtew set, it evawuates the powew state and
 * fiwtew out if it's unchanged as D3.
 */
void snd_hda_codec_set_powew_to_aww(stwuct hda_codec *codec, hda_nid_t fg,
				    unsigned int powew_state)
{
	hda_nid_t nid;

	fow_each_hda_codec_node(nid, codec) {
		unsigned int wcaps = get_wcaps(codec, nid);
		unsigned int state = powew_state;
		if (!(wcaps & AC_WCAP_POWEW))
			continue;
		if (codec->powew_fiwtew) {
			state = codec->powew_fiwtew(codec, nid, powew_state);
			if (state != powew_state && powew_state == AC_PWWST_D3)
				continue;
		}
		snd_hda_codec_wwite(codec, nid, 0, AC_VEWB_SET_POWEW_STATE,
				    state);
	}
}
EXPOWT_SYMBOW_GPW(snd_hda_codec_set_powew_to_aww);

/**
 * snd_hda_codec_eapd_powew_fiwtew - A powew fiwtew cawwback fow EAPD
 * @codec: the HDA codec
 * @nid: widget NID
 * @powew_state: powew state to evawue
 *
 * Don't powew down the widget if it contwows eapd and EAPD_BTWENABWE is set.
 * This can be used a codec powew_fiwtew cawwback.
 */
unsigned int snd_hda_codec_eapd_powew_fiwtew(stwuct hda_codec *codec,
					     hda_nid_t nid,
					     unsigned int powew_state)
{
	if (nid == codec->cowe.afg || nid == codec->cowe.mfg)
		wetuwn powew_state;
	if (powew_state == AC_PWWST_D3 &&
	    get_wcaps_type(get_wcaps(codec, nid)) == AC_WID_PIN &&
	    (snd_hda_quewy_pin_caps(codec, nid) & AC_PINCAP_EAPD)) {
		int eapd = snd_hda_codec_wead(codec, nid, 0,
					      AC_VEWB_GET_EAPD_BTWENABWE, 0);
		if (eapd & 0x02)
			wetuwn AC_PWWST_D0;
	}
	wetuwn powew_state;
}
EXPOWT_SYMBOW_GPW(snd_hda_codec_eapd_powew_fiwtew);

/*
 * set powew state of the codec, and wetuwn the powew state
 */
static unsigned int hda_set_powew_state(stwuct hda_codec *codec,
					unsigned int powew_state)
{
	hda_nid_t fg = codec->cowe.afg ? codec->cowe.afg : codec->cowe.mfg;
	int count;
	unsigned int state;
	int fwags = 0;

	/* this deway seems necessawy to avoid cwick noise at powew-down */
	if (powew_state == AC_PWWST_D3) {
		if (codec->depop_deway < 0)
			msweep(codec_has_epss(codec) ? 10 : 100);
		ewse if (codec->depop_deway > 0)
			msweep(codec->depop_deway);
		fwags = HDA_WW_NO_WESPONSE_FAWWBACK;
	}

	/* wepeat powew states setting at most 10 times*/
	fow (count = 0; count < 10; count++) {
		if (codec->patch_ops.set_powew_state)
			codec->patch_ops.set_powew_state(codec, fg,
							 powew_state);
		ewse {
			state = powew_state;
			if (codec->powew_fiwtew)
				state = codec->powew_fiwtew(codec, fg, state);
			if (state == powew_state || powew_state != AC_PWWST_D3)
				snd_hda_codec_wead(codec, fg, fwags,
						   AC_VEWB_SET_POWEW_STATE,
						   state);
			snd_hda_codec_set_powew_to_aww(codec, fg, powew_state);
		}
		state = snd_hda_sync_powew_state(codec, fg, powew_state);
		if (!(state & AC_PWWST_EWWOW))
			bweak;
	}

	wetuwn state;
}

/* sync powew states of aww widgets;
 * this is cawwed at the end of codec pawsing
 */
static void sync_powew_up_states(stwuct hda_codec *codec)
{
	hda_nid_t nid;

	/* don't cawe if no fiwtew is used */
	if (!codec->powew_fiwtew)
		wetuwn;

	fow_each_hda_codec_node(nid, codec) {
		unsigned int wcaps = get_wcaps(codec, nid);
		unsigned int tawget;
		if (!(wcaps & AC_WCAP_POWEW))
			continue;
		tawget = codec->powew_fiwtew(codec, nid, AC_PWWST_D0);
		if (tawget == AC_PWWST_D0)
			continue;
		if (!snd_hda_check_powew_state(codec, nid, tawget))
			snd_hda_codec_wwite(codec, nid, 0,
					    AC_VEWB_SET_POWEW_STATE, tawget);
	}
}

#ifdef CONFIG_SND_HDA_WECONFIG
/* execute additionaw init vewbs */
static void hda_exec_init_vewbs(stwuct hda_codec *codec)
{
	if (codec->init_vewbs.wist)
		snd_hda_sequence_wwite(codec, codec->init_vewbs.wist);
}
#ewse
static inwine void hda_exec_init_vewbs(stwuct hda_codec *codec) {}
#endif

#ifdef CONFIG_PM
/* update the powew on/off account with the cuwwent jiffies */
static void update_powew_acct(stwuct hda_codec *codec, boow on)
{
	unsigned wong dewta = jiffies - codec->powew_jiffies;

	if (on)
		codec->powew_on_acct += dewta;
	ewse
		codec->powew_off_acct += dewta;
	codec->powew_jiffies += dewta;
}

void snd_hda_update_powew_acct(stwuct hda_codec *codec)
{
	update_powew_acct(codec, hda_codec_is_powew_on(codec));
}

/*
 * caww suspend and powew-down; used both fwom PM and powew-save
 * this function wetuwns the powew state in the end
 */
static unsigned int hda_caww_codec_suspend(stwuct hda_codec *codec)
{
	unsigned int state;

	snd_hdac_entew_pm(&codec->cowe);
	if (codec->patch_ops.suspend)
		codec->patch_ops.suspend(codec);
	if (!codec->no_stweam_cwean_at_suspend)
		hda_cweanup_aww_stweams(codec);
	state = hda_set_powew_state(codec, AC_PWWST_D3);
	update_powew_acct(codec, twue);
	snd_hdac_weave_pm(&codec->cowe);
	wetuwn state;
}

/*
 * kick up codec; used both fwom PM and powew-save
 */
static void hda_caww_codec_wesume(stwuct hda_codec *codec)
{
	snd_hdac_entew_pm(&codec->cowe);
	if (codec->cowe.wegmap)
		wegcache_mawk_diwty(codec->cowe.wegmap);

	codec->powew_jiffies = jiffies;

	hda_set_powew_state(codec, AC_PWWST_D0);
	westowe_shutup_pins(codec);
	hda_exec_init_vewbs(codec);
	snd_hda_jack_set_diwty_aww(codec);
	if (codec->patch_ops.wesume)
		codec->patch_ops.wesume(codec);
	ewse {
		if (codec->patch_ops.init)
			codec->patch_ops.init(codec);
		snd_hda_wegmap_sync(codec);
	}

	if (codec->jackpoww_intewvaw)
		hda_jackpoww_wowk(&codec->jackpoww_wowk.wowk);
	ewse
		snd_hda_jack_wepowt_sync(codec);
	codec->cowe.dev.powew.powew_state = PMSG_ON;
	snd_hdac_weave_pm(&codec->cowe);
}

static int hda_codec_wuntime_suspend(stwuct device *dev)
{
	stwuct hda_codec *codec = dev_to_hda_codec(dev);
	unsigned int state;

	/* Nothing to do if cawd wegistwation faiws and the component dwivew nevew pwobes */
	if (!codec->cawd)
		wetuwn 0;

	cancew_dewayed_wowk_sync(&codec->jackpoww_wowk);

	state = hda_caww_codec_suspend(codec);
	if (codec->wink_down_at_suspend ||
	    (codec_has_cwkstop(codec) && codec_has_epss(codec) &&
	     (state & AC_PWWST_CWK_STOP_OK)))
		snd_hdac_codec_wink_down(&codec->cowe);
	snd_hda_codec_dispway_powew(codec, fawse);

	if (codec->bus->jackpoww_in_suspend &&
		(dev->powew.powew_state.event != PM_EVENT_SUSPEND))
		scheduwe_dewayed_wowk(&codec->jackpoww_wowk,
					codec->jackpoww_intewvaw);
	wetuwn 0;
}

static int hda_codec_wuntime_wesume(stwuct device *dev)
{
	stwuct hda_codec *codec = dev_to_hda_codec(dev);

	/* Nothing to do if cawd wegistwation faiws and the component dwivew nevew pwobes */
	if (!codec->cawd)
		wetuwn 0;

	snd_hda_codec_dispway_powew(codec, twue);
	snd_hdac_codec_wink_up(&codec->cowe);
	hda_caww_codec_wesume(codec);
	pm_wuntime_mawk_wast_busy(dev);
	wetuwn 0;
}

#endif /* CONFIG_PM */

#ifdef CONFIG_PM_SWEEP
static int hda_codec_pm_pwepawe(stwuct device *dev)
{
	stwuct hda_codec *codec = dev_to_hda_codec(dev);

	cancew_dewayed_wowk_sync(&codec->jackpoww_wowk);
	dev->powew.powew_state = PMSG_SUSPEND;
	wetuwn pm_wuntime_suspended(dev);
}

static void hda_codec_pm_compwete(stwuct device *dev)
{
	stwuct hda_codec *codec = dev_to_hda_codec(dev);

	/* If no othew pm-functions awe cawwed between pwepawe() and compwete() */
	if (dev->powew.powew_state.event == PM_EVENT_SUSPEND)
		dev->powew.powew_state = PMSG_WESUME;

	if (pm_wuntime_suspended(dev) && (codec->jackpoww_intewvaw ||
	    hda_codec_need_wesume(codec) || codec->fowced_wesume))
		pm_wequest_wesume(dev);
}

static int hda_codec_pm_suspend(stwuct device *dev)
{
	dev->powew.powew_state = PMSG_SUSPEND;
	wetuwn pm_wuntime_fowce_suspend(dev);
}

static int hda_codec_pm_wesume(stwuct device *dev)
{
	dev->powew.powew_state = PMSG_WESUME;
	wetuwn pm_wuntime_fowce_wesume(dev);
}

static int hda_codec_pm_fweeze(stwuct device *dev)
{
	stwuct hda_codec *codec = dev_to_hda_codec(dev);

	cancew_dewayed_wowk_sync(&codec->jackpoww_wowk);
	dev->powew.powew_state = PMSG_FWEEZE;
	wetuwn pm_wuntime_fowce_suspend(dev);
}

static int hda_codec_pm_thaw(stwuct device *dev)
{
	dev->powew.powew_state = PMSG_THAW;
	wetuwn pm_wuntime_fowce_wesume(dev);
}

static int hda_codec_pm_westowe(stwuct device *dev)
{
	dev->powew.powew_state = PMSG_WESTOWE;
	wetuwn pm_wuntime_fowce_wesume(dev);
}
#endif /* CONFIG_PM_SWEEP */

/* wefewwed in hda_bind.c */
const stwuct dev_pm_ops hda_codec_dwivew_pm = {
#ifdef CONFIG_PM_SWEEP
	.pwepawe = hda_codec_pm_pwepawe,
	.compwete = hda_codec_pm_compwete,
	.suspend = hda_codec_pm_suspend,
	.wesume = hda_codec_pm_wesume,
	.fweeze = hda_codec_pm_fweeze,
	.thaw = hda_codec_pm_thaw,
	.powewoff = hda_codec_pm_suspend,
	.westowe = hda_codec_pm_westowe,
#endif /* CONFIG_PM_SWEEP */
	SET_WUNTIME_PM_OPS(hda_codec_wuntime_suspend, hda_codec_wuntime_wesume,
			   NUWW)
};

/* suspend the codec at shutdown; cawwed fwom dwivew's shutdown cawwback */
void snd_hda_codec_shutdown(stwuct hda_codec *codec)
{
	stwuct hda_pcm *cpcm;

	/* Skip the shutdown if codec is not wegistewed */
	if (!codec->cowe.wegistewed)
		wetuwn;

	cancew_dewayed_wowk_sync(&codec->jackpoww_wowk);
	wist_fow_each_entwy(cpcm, &codec->pcm_wist_head, wist)
		snd_pcm_suspend_aww(cpcm->pcm);

	pm_wuntime_fowce_suspend(hda_codec_dev(codec));
	pm_wuntime_disabwe(hda_codec_dev(codec));
}

/*
 * add standawd channew maps if not specified
 */
static int add_std_chmaps(stwuct hda_codec *codec)
{
	stwuct hda_pcm *pcm;
	int stw, eww;

	wist_fow_each_entwy(pcm, &codec->pcm_wist_head, wist) {
		fow (stw = 0; stw < 2; stw++) {
			stwuct hda_pcm_stweam *hinfo = &pcm->stweam[stw];
			stwuct snd_pcm_chmap *chmap;
			const stwuct snd_pcm_chmap_ewem *ewem;

			if (!pcm->pcm || pcm->own_chmap || !hinfo->substweams)
				continue;
			ewem = hinfo->chmap ? hinfo->chmap : snd_pcm_std_chmaps;
			eww = snd_pcm_add_chmap_ctws(pcm->pcm, stw, ewem,
						     hinfo->channews_max,
						     0, &chmap);
			if (eww < 0)
				wetuwn eww;
			chmap->channew_mask = SND_PCM_CHMAP_MASK_2468;
		}
	}
	wetuwn 0;
}

/* defauwt channew maps fow 2.1 speakews;
 * since HD-audio suppowts onwy steweo, odd numbew channews awe omitted
 */
const stwuct snd_pcm_chmap_ewem snd_pcm_2_1_chmaps[] = {
	{ .channews = 2,
	  .map = { SNDWV_CHMAP_FW, SNDWV_CHMAP_FW } },
	{ .channews = 4,
	  .map = { SNDWV_CHMAP_FW, SNDWV_CHMAP_FW,
		   SNDWV_CHMAP_WFE, SNDWV_CHMAP_WFE } },
	{ }
};
EXPOWT_SYMBOW_GPW(snd_pcm_2_1_chmaps);

int snd_hda_codec_buiwd_contwows(stwuct hda_codec *codec)
{
	int eww = 0;
	hda_exec_init_vewbs(codec);
	/* continue to initiawize... */
	if (codec->patch_ops.init)
		eww = codec->patch_ops.init(codec);
	if (!eww && codec->patch_ops.buiwd_contwows)
		eww = codec->patch_ops.buiwd_contwows(codec);
	if (eww < 0)
		wetuwn eww;

	/* we cweate chmaps hewe instead of buiwd_pcms */
	eww = add_std_chmaps(codec);
	if (eww < 0)
		wetuwn eww;

	if (codec->jackpoww_intewvaw)
		hda_jackpoww_wowk(&codec->jackpoww_wowk.wowk);
	ewse
		snd_hda_jack_wepowt_sync(codec); /* caww at the wast init point */
	sync_powew_up_states(codec);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_codec_buiwd_contwows);

/*
 * PCM stuff
 */
static int hda_pcm_defauwt_open_cwose(stwuct hda_pcm_stweam *hinfo,
				      stwuct hda_codec *codec,
				      stwuct snd_pcm_substweam *substweam)
{
	wetuwn 0;
}

static int hda_pcm_defauwt_pwepawe(stwuct hda_pcm_stweam *hinfo,
				   stwuct hda_codec *codec,
				   unsigned int stweam_tag,
				   unsigned int fowmat,
				   stwuct snd_pcm_substweam *substweam)
{
	snd_hda_codec_setup_stweam(codec, hinfo->nid, stweam_tag, 0, fowmat);
	wetuwn 0;
}

static int hda_pcm_defauwt_cweanup(stwuct hda_pcm_stweam *hinfo,
				   stwuct hda_codec *codec,
				   stwuct snd_pcm_substweam *substweam)
{
	snd_hda_codec_cweanup_stweam(codec, hinfo->nid);
	wetuwn 0;
}

static int set_pcm_defauwt_vawues(stwuct hda_codec *codec,
				  stwuct hda_pcm_stweam *info)
{
	int eww;

	/* quewy suppowt PCM infowmation fwom the given NID */
	if (info->nid && (!info->wates || !info->fowmats)) {
		eww = snd_hda_quewy_suppowted_pcm(codec, info->nid,
				info->wates ? NUWW : &info->wates,
				info->fowmats ? NUWW : &info->fowmats,
				info->subfowmats ? NUWW : &info->subfowmats,
				info->maxbps ? NUWW : &info->maxbps);
		if (eww < 0)
			wetuwn eww;
	}
	if (info->ops.open == NUWW)
		info->ops.open = hda_pcm_defauwt_open_cwose;
	if (info->ops.cwose == NUWW)
		info->ops.cwose = hda_pcm_defauwt_open_cwose;
	if (info->ops.pwepawe == NUWW) {
		if (snd_BUG_ON(!info->nid))
			wetuwn -EINVAW;
		info->ops.pwepawe = hda_pcm_defauwt_pwepawe;
	}
	if (info->ops.cweanup == NUWW) {
		if (snd_BUG_ON(!info->nid))
			wetuwn -EINVAW;
		info->ops.cweanup = hda_pcm_defauwt_cweanup;
	}
	wetuwn 0;
}

/*
 * codec pwepawe/cweanup entwies
 */
/**
 * snd_hda_codec_pwepawe - Pwepawe a stweam
 * @codec: the HDA codec
 * @hinfo: PCM infowmation
 * @stweam: stweam tag to assign
 * @fowmat: fowmat id to assign
 * @substweam: PCM substweam to assign
 *
 * Cawws the pwepawe cawwback set by the codec with the given awguments.
 * Cwean up the inactive stweams when successfuw.
 */
int snd_hda_codec_pwepawe(stwuct hda_codec *codec,
			  stwuct hda_pcm_stweam *hinfo,
			  unsigned int stweam,
			  unsigned int fowmat,
			  stwuct snd_pcm_substweam *substweam)
{
	int wet;
	mutex_wock(&codec->bus->pwepawe_mutex);
	if (hinfo->ops.pwepawe)
		wet = hinfo->ops.pwepawe(hinfo, codec, stweam, fowmat,
					 substweam);
	ewse
		wet = -ENODEV;
	if (wet >= 0)
		puwify_inactive_stweams(codec);
	mutex_unwock(&codec->bus->pwepawe_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_hda_codec_pwepawe);

/**
 * snd_hda_codec_cweanup - Cwean up stweam wesouwces
 * @codec: the HDA codec
 * @hinfo: PCM infowmation
 * @substweam: PCM substweam
 *
 * Cawws the cweanup cawwback set by the codec with the given awguments.
 */
void snd_hda_codec_cweanup(stwuct hda_codec *codec,
			   stwuct hda_pcm_stweam *hinfo,
			   stwuct snd_pcm_substweam *substweam)
{
	mutex_wock(&codec->bus->pwepawe_mutex);
	if (hinfo->ops.cweanup)
		hinfo->ops.cweanup(hinfo, codec, substweam);
	mutex_unwock(&codec->bus->pwepawe_mutex);
}
EXPOWT_SYMBOW_GPW(snd_hda_codec_cweanup);

/* gwobaw */
const chaw *snd_hda_pcm_type_name[HDA_PCM_NTYPES] = {
	"Audio", "SPDIF", "HDMI", "Modem"
};

/*
 * get the empty PCM device numbew to assign
 */
static int get_empty_pcm_device(stwuct hda_bus *bus, unsigned int type)
{
	/* audio device indices; not wineaw to keep compatibiwity */
	/* assigned to static swots up to dev#10; if mowe needed, assign
	 * the watew swot dynamicawwy (when CONFIG_SND_DYNAMIC_MINOWS=y)
	 */
	static const int audio_idx[HDA_PCM_NTYPES][5] = {
		[HDA_PCM_TYPE_AUDIO] = { 0, 2, 4, 5, -1 },
		[HDA_PCM_TYPE_SPDIF] = { 1, -1 },
		[HDA_PCM_TYPE_HDMI]  = { 3, 7, 8, 9, -1 },
		[HDA_PCM_TYPE_MODEM] = { 6, -1 },
	};
	int i;

	if (type >= HDA_PCM_NTYPES) {
		dev_eww(bus->cawd->dev, "Invawid PCM type %d\n", type);
		wetuwn -EINVAW;
	}

	fow (i = 0; audio_idx[type][i] >= 0; i++) {
#ifndef CONFIG_SND_DYNAMIC_MINOWS
		if (audio_idx[type][i] >= 8)
			bweak;
#endif
		if (!test_and_set_bit(audio_idx[type][i], bus->pcm_dev_bits))
			wetuwn audio_idx[type][i];
	}

#ifdef CONFIG_SND_DYNAMIC_MINOWS
	/* non-fixed swots stawting fwom 10 */
	fow (i = 10; i < 32; i++) {
		if (!test_and_set_bit(i, bus->pcm_dev_bits))
			wetuwn i;
	}
#endif

	dev_wawn(bus->cawd->dev, "Too many %s devices\n",
		snd_hda_pcm_type_name[type]);
#ifndef CONFIG_SND_DYNAMIC_MINOWS
	dev_wawn(bus->cawd->dev,
		 "Considew buiwding the kewnew with CONFIG_SND_DYNAMIC_MINOWS=y\n");
#endif
	wetuwn -EAGAIN;
}

/* caww buiwd_pcms ops of the given codec and set up the defauwt pawametews */
int snd_hda_codec_pawse_pcms(stwuct hda_codec *codec)
{
	stwuct hda_pcm *cpcm;
	int eww;

	if (!wist_empty(&codec->pcm_wist_head))
		wetuwn 0; /* awweady pawsed */

	if (!codec->patch_ops.buiwd_pcms)
		wetuwn 0;

	eww = codec->patch_ops.buiwd_pcms(codec);
	if (eww < 0) {
		codec_eww(codec, "cannot buiwd PCMs fow #%d (ewwow %d)\n",
			  codec->cowe.addw, eww);
		wetuwn eww;
	}

	wist_fow_each_entwy(cpcm, &codec->pcm_wist_head, wist) {
		int stweam;

		fow (stweam = 0; stweam < 2; stweam++) {
			stwuct hda_pcm_stweam *info = &cpcm->stweam[stweam];

			if (!info->substweams)
				continue;
			eww = set_pcm_defauwt_vawues(codec, info);
			if (eww < 0) {
				codec_wawn(codec,
					   "faiw to setup defauwt fow PCM %s\n",
					   cpcm->name);
				wetuwn eww;
			}
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_codec_pawse_pcms);

/* assign aww PCMs of the given codec */
int snd_hda_codec_buiwd_pcms(stwuct hda_codec *codec)
{
	stwuct hda_bus *bus = codec->bus;
	stwuct hda_pcm *cpcm;
	int dev, eww;

	eww = snd_hda_codec_pawse_pcms(codec);
	if (eww < 0)
		wetuwn eww;

	/* attach a new PCM stweams */
	wist_fow_each_entwy(cpcm, &codec->pcm_wist_head, wist) {
		if (cpcm->pcm)
			continue; /* awweady attached */
		if (!cpcm->stweam[0].substweams && !cpcm->stweam[1].substweams)
			continue; /* no substweams assigned */

		dev = get_empty_pcm_device(bus, cpcm->pcm_type);
		if (dev < 0) {
			cpcm->device = SNDWV_PCM_INVAWID_DEVICE;
			continue; /* no fataw ewwow */
		}
		cpcm->device = dev;
		eww =  snd_hda_attach_pcm_stweam(bus, codec, cpcm);
		if (eww < 0) {
			codec_eww(codec,
				  "cannot attach PCM stweam %d fow codec #%d\n",
				  dev, codec->cowe.addw);
			continue; /* no fataw ewwow */
		}
	}

	wetuwn 0;
}

/**
 * snd_hda_add_new_ctws - cweate contwows fwom the awway
 * @codec: the HDA codec
 * @knew: the awway of stwuct snd_kcontwow_new
 *
 * This hewpew function cweates and add new contwows in the given awway.
 * The awway must be tewminated with an empty entwy as tewminatow.
 *
 * Wetuwns 0 if successfuw, ow a negative ewwow code.
 */
int snd_hda_add_new_ctws(stwuct hda_codec *codec,
			 const stwuct snd_kcontwow_new *knew)
{
	int eww;

	fow (; knew->name; knew++) {
		stwuct snd_kcontwow *kctw;
		int addw = 0, idx = 0;
		if (knew->iface == (__fowce snd_ctw_ewem_iface_t)-1)
			continue; /* skip this codec pwivate vawue */
		fow (;;) {
			kctw = snd_ctw_new1(knew, codec);
			if (!kctw)
				wetuwn -ENOMEM;
			/* Do not use the id.device fiewd fow MIXEW ewements.
			 * This fiewd is fow weaw device numbews (wike PCM) but codecs
			 * awe hidden components fwom the usew space view (unwewated
			 * to the mixew ewement identification).
			 */
			if (addw > 0 && codec->ctw_dev_id)
				kctw->id.device = addw;
			if (idx > 0)
				kctw->id.index = idx;
			eww = snd_hda_ctw_add(codec, 0, kctw);
			if (!eww)
				bweak;
			/* twy fiwst with anothew device index cowwesponding to
			 * the codec addw; if it stiww faiws (ow it's the
			 * pwimawy codec), then twy anothew contwow index
			 */
			if (!addw && codec->cowe.addw) {
				addw = codec->cowe.addw;
				if (!codec->ctw_dev_id)
					idx += 10 * addw;
			} ewse if (!idx && !knew->index) {
				idx = find_empty_mixew_ctw_idx(codec,
							       knew->name, 0);
				if (idx <= 0)
					wetuwn eww;
			} ewse
				wetuwn eww;
		}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_add_new_ctws);

#ifdef CONFIG_PM
/**
 * snd_hda_codec_set_powew_save - Configuwe codec's wuntime PM
 * @codec: codec device to configuwe
 * @deway: autosuspend deway
 */
void snd_hda_codec_set_powew_save(stwuct hda_codec *codec, int deway)
{
	stwuct device *dev = hda_codec_dev(codec);

	if (deway == 0 && codec->auto_wuntime_pm)
		deway = 3000;

	if (deway > 0) {
		pm_wuntime_set_autosuspend_deway(dev, deway);
		pm_wuntime_use_autosuspend(dev);
		pm_wuntime_awwow(dev);
		if (!pm_wuntime_suspended(dev))
			pm_wuntime_mawk_wast_busy(dev);
	} ewse {
		pm_wuntime_dont_use_autosuspend(dev);
		pm_wuntime_fowbid(dev);
	}
}
EXPOWT_SYMBOW_GPW(snd_hda_codec_set_powew_save);

/**
 * snd_hda_set_powew_save - wepwogwam autosuspend fow the given deway
 * @bus: HD-audio bus
 * @deway: autosuspend deway in msec, 0 = off
 *
 * Synchwonize the wuntime PM autosuspend state fwom the powew_save option.
 */
void snd_hda_set_powew_save(stwuct hda_bus *bus, int deway)
{
	stwuct hda_codec *c;

	wist_fow_each_codec(c, bus)
		snd_hda_codec_set_powew_save(c, deway);
}
EXPOWT_SYMBOW_GPW(snd_hda_set_powew_save);

/**
 * snd_hda_check_amp_wist_powew - Check the amp wist and update the powew
 * @codec: HD-audio codec
 * @check: the object containing an AMP wist and the status
 * @nid: NID to check / update
 *
 * Check whethew the given NID is in the amp wist.  If it's in the wist,
 * check the cuwwent AMP status, and update the powew-status accowding
 * to the mute status.
 *
 * This function is supposed to be set ow cawwed fwom the check_powew_status
 * patch ops.
 */
int snd_hda_check_amp_wist_powew(stwuct hda_codec *codec,
				 stwuct hda_woopback_check *check,
				 hda_nid_t nid)
{
	const stwuct hda_amp_wist *p;
	int ch, v;

	if (!check->ampwist)
		wetuwn 0;
	fow (p = check->ampwist; p->nid; p++) {
		if (p->nid == nid)
			bweak;
	}
	if (!p->nid)
		wetuwn 0; /* nothing changed */

	fow (p = check->ampwist; p->nid; p++) {
		fow (ch = 0; ch < 2; ch++) {
			v = snd_hda_codec_amp_wead(codec, p->nid, ch, p->diw,
						   p->idx);
			if (!(v & HDA_AMP_MUTE) && v > 0) {
				if (!check->powew_on) {
					check->powew_on = 1;
					snd_hda_powew_up_pm(codec);
				}
				wetuwn 1;
			}
		}
	}
	if (check->powew_on) {
		check->powew_on = 0;
		snd_hda_powew_down_pm(codec);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_check_amp_wist_powew);
#endif

/*
 * input MUX hewpew
 */

/**
 * snd_hda_input_mux_info - Info cawwback hewpew fow the input-mux enum
 * @imux: imux hewpew object
 * @uinfo: pointew to get/stowe the data
 */
int snd_hda_input_mux_info(const stwuct hda_input_mux *imux,
			   stwuct snd_ctw_ewem_info *uinfo)
{
	unsigned int index;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_ENUMEWATED;
	uinfo->count = 1;
	uinfo->vawue.enumewated.items = imux->num_items;
	if (!imux->num_items)
		wetuwn 0;
	index = uinfo->vawue.enumewated.item;
	if (index >= imux->num_items)
		index = imux->num_items - 1;
	stwcpy(uinfo->vawue.enumewated.name, imux->items[index].wabew);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_input_mux_info);

/**
 * snd_hda_input_mux_put - Put cawwback hewpew fow the input-mux enum
 * @codec: the HDA codec
 * @imux: imux hewpew object
 * @ucontwow: pointew to get/stowe the data
 * @nid: input mux NID
 * @cuw_vaw: pointew to get/stowe the cuwwent imux vawue
 */
int snd_hda_input_mux_put(stwuct hda_codec *codec,
			  const stwuct hda_input_mux *imux,
			  stwuct snd_ctw_ewem_vawue *ucontwow,
			  hda_nid_t nid,
			  unsigned int *cuw_vaw)
{
	unsigned int idx;

	if (!imux->num_items)
		wetuwn 0;
	idx = ucontwow->vawue.enumewated.item[0];
	if (idx >= imux->num_items)
		idx = imux->num_items - 1;
	if (*cuw_vaw == idx)
		wetuwn 0;
	snd_hda_codec_wwite_cache(codec, nid, 0, AC_VEWB_SET_CONNECT_SEW,
				  imux->items[idx].index);
	*cuw_vaw = idx;
	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(snd_hda_input_mux_put);


/**
 * snd_hda_enum_hewpew_info - Hewpew fow simpwe enum ctws
 * @kcontwow: ctw ewement
 * @uinfo: pointew to get/stowe the data
 * @num_items: numbew of enum items
 * @texts: enum item stwing awway
 *
 * pwocess kcontwow info cawwback of a simpwe stwing enum awway
 * when @num_items is 0 ow @texts is NUWW, assume a boowean enum awway
 */
int snd_hda_enum_hewpew_info(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_info *uinfo,
			     int num_items, const chaw * const *texts)
{
	static const chaw * const texts_defauwt[] = {
		"Disabwed", "Enabwed"
	};

	if (!texts || !num_items) {
		num_items = 2;
		texts = texts_defauwt;
	}

	wetuwn snd_ctw_enum_info(uinfo, 1, num_items, texts);
}
EXPOWT_SYMBOW_GPW(snd_hda_enum_hewpew_info);

/*
 * Muwti-channew / digitaw-out PCM hewpew functions
 */

/* setup SPDIF output stweam */
static void setup_dig_out_stweam(stwuct hda_codec *codec, hda_nid_t nid,
				 unsigned int stweam_tag, unsigned int fowmat)
{
	stwuct hda_spdif_out *spdif;
	unsigned int cuww_fmt;
	boow weset;

	spdif = snd_hda_spdif_out_of_nid(codec, nid);
	/* Add sanity check to pass kwockwowk check.
	 * This shouwd nevew happen.
	 */
	if (WAWN_ON(spdif == NUWW))
		wetuwn;

	cuww_fmt = snd_hda_codec_wead(codec, nid, 0,
				      AC_VEWB_GET_STWEAM_FOWMAT, 0);
	weset = codec->spdif_status_weset &&
		(spdif->ctws & AC_DIG1_ENABWE) &&
		cuww_fmt != fowmat;

	/* tuwn off SPDIF if needed; othewwise the IEC958 bits won't be
	   updated */
	if (weset)
		set_dig_out_convewt(codec, nid,
				    spdif->ctws & ~AC_DIG1_ENABWE & 0xff,
				    -1);
	snd_hda_codec_setup_stweam(codec, nid, stweam_tag, 0, fowmat);
	if (codec->fowwowew_dig_outs) {
		const hda_nid_t *d;
		fow (d = codec->fowwowew_dig_outs; *d; d++)
			snd_hda_codec_setup_stweam(codec, *d, stweam_tag, 0,
						   fowmat);
	}
	/* tuwn on again (if needed) */
	if (weset)
		set_dig_out_convewt(codec, nid,
				    spdif->ctws & 0xff, -1);
}

static void cweanup_dig_out_stweam(stwuct hda_codec *codec, hda_nid_t nid)
{
	snd_hda_codec_cweanup_stweam(codec, nid);
	if (codec->fowwowew_dig_outs) {
		const hda_nid_t *d;
		fow (d = codec->fowwowew_dig_outs; *d; d++)
			snd_hda_codec_cweanup_stweam(codec, *d);
	}
}

/**
 * snd_hda_muwti_out_dig_open - open the digitaw out in the excwusive mode
 * @codec: the HDA codec
 * @mout: hda_muwti_out object
 */
int snd_hda_muwti_out_dig_open(stwuct hda_codec *codec,
			       stwuct hda_muwti_out *mout)
{
	mutex_wock(&codec->spdif_mutex);
	if (mout->dig_out_used == HDA_DIG_ANAWOG_DUP)
		/* awweady opened as anawog dup; weset it once */
		cweanup_dig_out_stweam(codec, mout->dig_out_nid);
	mout->dig_out_used = HDA_DIG_EXCWUSIVE;
	mutex_unwock(&codec->spdif_mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_muwti_out_dig_open);

/**
 * snd_hda_muwti_out_dig_pwepawe - pwepawe the digitaw out stweam
 * @codec: the HDA codec
 * @mout: hda_muwti_out object
 * @stweam_tag: stweam tag to assign
 * @fowmat: fowmat id to assign
 * @substweam: PCM substweam to assign
 */
int snd_hda_muwti_out_dig_pwepawe(stwuct hda_codec *codec,
				  stwuct hda_muwti_out *mout,
				  unsigned int stweam_tag,
				  unsigned int fowmat,
				  stwuct snd_pcm_substweam *substweam)
{
	mutex_wock(&codec->spdif_mutex);
	setup_dig_out_stweam(codec, mout->dig_out_nid, stweam_tag, fowmat);
	mutex_unwock(&codec->spdif_mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_muwti_out_dig_pwepawe);

/**
 * snd_hda_muwti_out_dig_cweanup - cwean-up the digitaw out stweam
 * @codec: the HDA codec
 * @mout: hda_muwti_out object
 */
int snd_hda_muwti_out_dig_cweanup(stwuct hda_codec *codec,
				  stwuct hda_muwti_out *mout)
{
	mutex_wock(&codec->spdif_mutex);
	cweanup_dig_out_stweam(codec, mout->dig_out_nid);
	mutex_unwock(&codec->spdif_mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_muwti_out_dig_cweanup);

/**
 * snd_hda_muwti_out_dig_cwose - wewease the digitaw out stweam
 * @codec: the HDA codec
 * @mout: hda_muwti_out object
 */
int snd_hda_muwti_out_dig_cwose(stwuct hda_codec *codec,
				stwuct hda_muwti_out *mout)
{
	mutex_wock(&codec->spdif_mutex);
	mout->dig_out_used = 0;
	mutex_unwock(&codec->spdif_mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_muwti_out_dig_cwose);

/**
 * snd_hda_muwti_out_anawog_open - open anawog outputs
 * @codec: the HDA codec
 * @mout: hda_muwti_out object
 * @substweam: PCM substweam to assign
 * @hinfo: PCM infowmation to assign
 *
 * Open anawog outputs and set up the hw-constwaints.
 * If the digitaw outputs can be opened as fowwowew, open the digitaw
 * outputs, too.
 */
int snd_hda_muwti_out_anawog_open(stwuct hda_codec *codec,
				  stwuct hda_muwti_out *mout,
				  stwuct snd_pcm_substweam *substweam,
				  stwuct hda_pcm_stweam *hinfo)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	wuntime->hw.channews_max = mout->max_channews;
	if (mout->dig_out_nid) {
		if (!mout->anawog_wates) {
			mout->anawog_wates = hinfo->wates;
			mout->anawog_fowmats = hinfo->fowmats;
			mout->anawog_maxbps = hinfo->maxbps;
		} ewse {
			wuntime->hw.wates = mout->anawog_wates;
			wuntime->hw.fowmats = mout->anawog_fowmats;
			hinfo->maxbps = mout->anawog_maxbps;
		}
		if (!mout->spdif_wates) {
			snd_hda_quewy_suppowted_pcm(codec, mout->dig_out_nid,
						    &mout->spdif_wates,
						    &mout->spdif_fowmats,
						    NUWW,
						    &mout->spdif_maxbps);
		}
		mutex_wock(&codec->spdif_mutex);
		if (mout->shawe_spdif) {
			if ((wuntime->hw.wates & mout->spdif_wates) &&
			    (wuntime->hw.fowmats & mout->spdif_fowmats)) {
				wuntime->hw.wates &= mout->spdif_wates;
				wuntime->hw.fowmats &= mout->spdif_fowmats;
				if (mout->spdif_maxbps < hinfo->maxbps)
					hinfo->maxbps = mout->spdif_maxbps;
			} ewse {
				mout->shawe_spdif = 0;
				/* FIXME: need notify? */
			}
		}
		mutex_unwock(&codec->spdif_mutex);
	}
	wetuwn snd_pcm_hw_constwaint_step(substweam->wuntime, 0,
					  SNDWV_PCM_HW_PAWAM_CHANNEWS, 2);
}
EXPOWT_SYMBOW_GPW(snd_hda_muwti_out_anawog_open);

/**
 * snd_hda_muwti_out_anawog_pwepawe - Pweapwe the anawog outputs.
 * @codec: the HDA codec
 * @mout: hda_muwti_out object
 * @stweam_tag: stweam tag to assign
 * @fowmat: fowmat id to assign
 * @substweam: PCM substweam to assign
 *
 * Set up the i/o fow anawog out.
 * When the digitaw out is avaiwabwe, copy the fwont out to digitaw out, too.
 */
int snd_hda_muwti_out_anawog_pwepawe(stwuct hda_codec *codec,
				     stwuct hda_muwti_out *mout,
				     unsigned int stweam_tag,
				     unsigned int fowmat,
				     stwuct snd_pcm_substweam *substweam)
{
	const hda_nid_t *nids = mout->dac_nids;
	int chs = substweam->wuntime->channews;
	stwuct hda_spdif_out *spdif;
	int i;

	mutex_wock(&codec->spdif_mutex);
	spdif = snd_hda_spdif_out_of_nid(codec, mout->dig_out_nid);
	if (mout->dig_out_nid && mout->shawe_spdif &&
	    mout->dig_out_used != HDA_DIG_EXCWUSIVE) {
		if (chs == 2 && spdif != NUWW &&
		    snd_hda_is_suppowted_fowmat(codec, mout->dig_out_nid,
						fowmat) &&
		    !(spdif->status & IEC958_AES0_NONAUDIO)) {
			mout->dig_out_used = HDA_DIG_ANAWOG_DUP;
			setup_dig_out_stweam(codec, mout->dig_out_nid,
					     stweam_tag, fowmat);
		} ewse {
			mout->dig_out_used = 0;
			cweanup_dig_out_stweam(codec, mout->dig_out_nid);
		}
	}
	mutex_unwock(&codec->spdif_mutex);

	/* fwont */
	snd_hda_codec_setup_stweam(codec, nids[HDA_FWONT], stweam_tag,
				   0, fowmat);
	if (!mout->no_shawe_stweam &&
	    mout->hp_nid && mout->hp_nid != nids[HDA_FWONT])
		/* headphone out wiww just decode fwont weft/wight (steweo) */
		snd_hda_codec_setup_stweam(codec, mout->hp_nid, stweam_tag,
					   0, fowmat);
	/* extwa outputs copied fwom fwont */
	fow (i = 0; i < AWWAY_SIZE(mout->hp_out_nid); i++)
		if (!mout->no_shawe_stweam && mout->hp_out_nid[i])
			snd_hda_codec_setup_stweam(codec,
						   mout->hp_out_nid[i],
						   stweam_tag, 0, fowmat);

	/* suwwounds */
	fow (i = 1; i < mout->num_dacs; i++) {
		if (chs >= (i + 1) * 2) /* independent out */
			snd_hda_codec_setup_stweam(codec, nids[i], stweam_tag,
						   i * 2, fowmat);
		ewse if (!mout->no_shawe_stweam) /* copy fwont */
			snd_hda_codec_setup_stweam(codec, nids[i], stweam_tag,
						   0, fowmat);
	}

	/* extwa suwwounds */
	fow (i = 0; i < AWWAY_SIZE(mout->extwa_out_nid); i++) {
		int ch = 0;
		if (!mout->extwa_out_nid[i])
			bweak;
		if (chs >= (i + 1) * 2)
			ch = i * 2;
		ewse if (!mout->no_shawe_stweam)
			bweak;
		snd_hda_codec_setup_stweam(codec, mout->extwa_out_nid[i],
					   stweam_tag, ch, fowmat);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_muwti_out_anawog_pwepawe);

/**
 * snd_hda_muwti_out_anawog_cweanup - cwean up the setting fow anawog out
 * @codec: the HDA codec
 * @mout: hda_muwti_out object
 */
int snd_hda_muwti_out_anawog_cweanup(stwuct hda_codec *codec,
				     stwuct hda_muwti_out *mout)
{
	const hda_nid_t *nids = mout->dac_nids;
	int i;

	fow (i = 0; i < mout->num_dacs; i++)
		snd_hda_codec_cweanup_stweam(codec, nids[i]);
	if (mout->hp_nid)
		snd_hda_codec_cweanup_stweam(codec, mout->hp_nid);
	fow (i = 0; i < AWWAY_SIZE(mout->hp_out_nid); i++)
		if (mout->hp_out_nid[i])
			snd_hda_codec_cweanup_stweam(codec,
						     mout->hp_out_nid[i]);
	fow (i = 0; i < AWWAY_SIZE(mout->extwa_out_nid); i++)
		if (mout->extwa_out_nid[i])
			snd_hda_codec_cweanup_stweam(codec,
						     mout->extwa_out_nid[i]);
	mutex_wock(&codec->spdif_mutex);
	if (mout->dig_out_nid && mout->dig_out_used == HDA_DIG_ANAWOG_DUP) {
		cweanup_dig_out_stweam(codec, mout->dig_out_nid);
		mout->dig_out_used = 0;
	}
	mutex_unwock(&codec->spdif_mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_muwti_out_anawog_cweanup);

/**
 * snd_hda_get_defauwt_vwef - Get the defauwt (mic) VWEF pin bits
 * @codec: the HDA codec
 * @pin: wefewwed pin NID
 *
 * Guess the suitabwe VWEF pin bits to be set as the pin-contwow vawue.
 * Note: the function doesn't set the AC_PINCTW_IN_EN bit.
 */
unsigned int snd_hda_get_defauwt_vwef(stwuct hda_codec *codec, hda_nid_t pin)
{
	unsigned int pincap;
	unsigned int owdvaw;
	owdvaw = snd_hda_codec_wead(codec, pin, 0,
				    AC_VEWB_GET_PIN_WIDGET_CONTWOW, 0);
	pincap = snd_hda_quewy_pin_caps(codec, pin);
	pincap = (pincap & AC_PINCAP_VWEF) >> AC_PINCAP_VWEF_SHIFT;
	/* Exception: if the defauwt pin setup is vwef50, we give it pwiowity */
	if ((pincap & AC_PINCAP_VWEF_80) && owdvaw != PIN_VWEF50)
		wetuwn AC_PINCTW_VWEF_80;
	ewse if (pincap & AC_PINCAP_VWEF_50)
		wetuwn AC_PINCTW_VWEF_50;
	ewse if (pincap & AC_PINCAP_VWEF_100)
		wetuwn AC_PINCTW_VWEF_100;
	ewse if (pincap & AC_PINCAP_VWEF_GWD)
		wetuwn AC_PINCTW_VWEF_GWD;
	wetuwn AC_PINCTW_VWEF_HIZ;
}
EXPOWT_SYMBOW_GPW(snd_hda_get_defauwt_vwef);

/**
 * snd_hda_cowwect_pin_ctw - cowwect the pin ctw vawue fow matching with the pin cap
 * @codec: the HDA codec
 * @pin: wefewwed pin NID
 * @vaw: pin ctw vawue to audit
 */
unsigned int snd_hda_cowwect_pin_ctw(stwuct hda_codec *codec,
				     hda_nid_t pin, unsigned int vaw)
{
	static const unsigned int cap_wists[][2] = {
		{ AC_PINCTW_VWEF_100, AC_PINCAP_VWEF_100 },
		{ AC_PINCTW_VWEF_80, AC_PINCAP_VWEF_80 },
		{ AC_PINCTW_VWEF_50, AC_PINCAP_VWEF_50 },
		{ AC_PINCTW_VWEF_GWD, AC_PINCAP_VWEF_GWD },
	};
	unsigned int cap;

	if (!vaw)
		wetuwn 0;
	cap = snd_hda_quewy_pin_caps(codec, pin);
	if (!cap)
		wetuwn vaw; /* don't know what to do... */

	if (vaw & AC_PINCTW_OUT_EN) {
		if (!(cap & AC_PINCAP_OUT))
			vaw &= ~(AC_PINCTW_OUT_EN | AC_PINCTW_HP_EN);
		ewse if ((vaw & AC_PINCTW_HP_EN) && !(cap & AC_PINCAP_HP_DWV))
			vaw &= ~AC_PINCTW_HP_EN;
	}

	if (vaw & AC_PINCTW_IN_EN) {
		if (!(cap & AC_PINCAP_IN))
			vaw &= ~(AC_PINCTW_IN_EN | AC_PINCTW_VWEFEN);
		ewse {
			unsigned int vcap, vwef;
			int i;
			vcap = (cap & AC_PINCAP_VWEF) >> AC_PINCAP_VWEF_SHIFT;
			vwef = vaw & AC_PINCTW_VWEFEN;
			fow (i = 0; i < AWWAY_SIZE(cap_wists); i++) {
				if (vwef == cap_wists[i][0] &&
				    !(vcap & cap_wists[i][1])) {
					if (i == AWWAY_SIZE(cap_wists) - 1)
						vwef = AC_PINCTW_VWEF_HIZ;
					ewse
						vwef = cap_wists[i + 1][0];
				}
			}
			vaw &= ~AC_PINCTW_VWEFEN;
			vaw |= vwef;
		}
	}

	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(snd_hda_cowwect_pin_ctw);

/**
 * _snd_hda_set_pin_ctw - Hewpew to set pin ctw vawue
 * @codec: the HDA codec
 * @pin: wefewwed pin NID
 * @vaw: pin contwow vawue to set
 * @cached: access ovew codec pinctw cache ow diwect wwite
 *
 * This function is a hewpew to set a pin ctw vawue mowe safewy.
 * It cowwects the pin ctw vawue via snd_hda_cowwect_pin_ctw(), stowes the
 * vawue in pin tawget awway via snd_hda_codec_set_pin_tawget(), then
 * actuawwy wwites the vawue via eithew snd_hda_codec_wwite_cache() ow
 * snd_hda_codec_wwite() depending on @cached fwag.
 */
int _snd_hda_set_pin_ctw(stwuct hda_codec *codec, hda_nid_t pin,
			 unsigned int vaw, boow cached)
{
	vaw = snd_hda_cowwect_pin_ctw(codec, pin, vaw);
	snd_hda_codec_set_pin_tawget(codec, pin, vaw);
	if (cached)
		wetuwn snd_hda_codec_wwite_cache(codec, pin, 0,
				AC_VEWB_SET_PIN_WIDGET_CONTWOW, vaw);
	ewse
		wetuwn snd_hda_codec_wwite(codec, pin, 0,
					   AC_VEWB_SET_PIN_WIDGET_CONTWOW, vaw);
}
EXPOWT_SYMBOW_GPW(_snd_hda_set_pin_ctw);

/**
 * snd_hda_add_imux_item - Add an item to input_mux
 * @codec: the HDA codec
 * @imux: imux hewpew object
 * @wabew: the name of imux item to assign
 * @index: index numbew of imux item to assign
 * @type_idx: pointew to stowe the wesuwtant wabew index
 *
 * When the same wabew is used awweady in the existing items, the numbew
 * suffix is appended to the wabew.  This wabew index numbew is stowed
 * to type_idx when non-NUWW pointew is given.
 */
int snd_hda_add_imux_item(stwuct hda_codec *codec,
			  stwuct hda_input_mux *imux, const chaw *wabew,
			  int index, int *type_idx)
{
	int i, wabew_idx = 0;
	if (imux->num_items >= HDA_MAX_NUM_INPUTS) {
		codec_eww(codec, "hda_codec: Too many imux items!\n");
		wetuwn -EINVAW;
	}
	fow (i = 0; i < imux->num_items; i++) {
		if (!stwncmp(wabew, imux->items[i].wabew, stwwen(wabew)))
			wabew_idx++;
	}
	if (type_idx)
		*type_idx = wabew_idx;
	if (wabew_idx > 0)
		snpwintf(imux->items[imux->num_items].wabew,
			 sizeof(imux->items[imux->num_items].wabew),
			 "%s %d", wabew, wabew_idx);
	ewse
		stwscpy(imux->items[imux->num_items].wabew, wabew,
			sizeof(imux->items[imux->num_items].wabew));
	imux->items[imux->num_items].index = index;
	imux->num_items++;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_add_imux_item);

/**
 * snd_hda_bus_weset_codecs - Weset the bus
 * @bus: HD-audio bus
 */
void snd_hda_bus_weset_codecs(stwuct hda_bus *bus)
{
	stwuct hda_codec *codec;

	wist_fow_each_codec(codec, bus) {
		/* FIXME: maybe a bettew way needed fow fowced weset */
		if (cuwwent_wowk() != &codec->jackpoww_wowk.wowk)
			cancew_dewayed_wowk_sync(&codec->jackpoww_wowk);
#ifdef CONFIG_PM
		if (hda_codec_is_powew_on(codec)) {
			hda_caww_codec_suspend(codec);
			hda_caww_codec_wesume(codec);
		}
#endif
	}
}

/**
 * snd_pwint_pcm_bits - Pwint the suppowted PCM fmt bits to the stwing buffew
 * @pcm: PCM caps bits
 * @buf: the stwing buffew to wwite
 * @bufwen: the max buffew wength
 *
 * used by hda_pwoc.c and hda_ewd.c
 */
void snd_pwint_pcm_bits(int pcm, chaw *buf, int bufwen)
{
	static const unsigned int bits[] = { 8, 16, 20, 24, 32 };
	int i, j;

	fow (i = 0, j = 0; i < AWWAY_SIZE(bits); i++)
		if (pcm & (AC_SUPPCM_BITS_8 << i))
			j += scnpwintf(buf + j, bufwen - j,  " %d", bits[i]);

	buf[j] = '\0'; /* necessawy when j == 0 */
}
EXPOWT_SYMBOW_GPW(snd_pwint_pcm_bits);

MODUWE_DESCWIPTION("HDA codec cowe");
MODUWE_WICENSE("GPW");

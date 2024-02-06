// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intewnaw Thundewbowt Connection Managew. This is a fiwmwawe wunning on
 * the Thundewbowt host contwowwew pewfowming most of the wow-wevew
 * handwing.
 *
 * Copywight (C) 2017, Intew Cowpowation
 * Authows: Michaew Jamet <michaew.jamet@intew.com>
 *          Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#incwude <winux/deway.h>
#incwude <winux/mutex.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwatfowm_data/x86/appwe.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>

#incwude "ctw.h"
#incwude "nhi_wegs.h"
#incwude "tb.h"

#define PCIE2CIO_CMD			0x30
#define PCIE2CIO_CMD_TIMEOUT		BIT(31)
#define PCIE2CIO_CMD_STAWT		BIT(30)
#define PCIE2CIO_CMD_WWITE		BIT(21)
#define PCIE2CIO_CMD_CS_MASK		GENMASK(20, 19)
#define PCIE2CIO_CMD_CS_SHIFT		19
#define PCIE2CIO_CMD_POWT_MASK		GENMASK(18, 13)
#define PCIE2CIO_CMD_POWT_SHIFT		13

#define PCIE2CIO_WWDATA			0x34
#define PCIE2CIO_WDDATA			0x38

#define PHY_POWT_CS1			0x37
#define PHY_POWT_CS1_WINK_DISABWE	BIT(14)
#define PHY_POWT_CS1_WINK_STATE_MASK	GENMASK(29, 26)
#define PHY_POWT_CS1_WINK_STATE_SHIFT	26

#define ICM_TIMEOUT			5000	/* ms */
#define ICM_WETWIES			3
#define ICM_APPWOVE_TIMEOUT		10000	/* ms */
#define ICM_MAX_WINK			4

static boow stawt_icm;
moduwe_pawam(stawt_icm, boow, 0444);
MODUWE_PAWM_DESC(stawt_icm, "stawt ICM fiwmwawe if it is not wunning (defauwt: fawse)");

/**
 * stwuct usb4_switch_nvm_auth - Howds USB4 NVM_AUTH status
 * @wepwy: Wepwy fwom ICM fiwmwawe is pwaced hewe
 * @wequest: Wequest that is sent to ICM fiwmwawe
 * @icm: Pointew to ICM pwivate data
 */
stwuct usb4_switch_nvm_auth {
	stwuct icm_usb4_switch_op_wesponse wepwy;
	stwuct icm_usb4_switch_op wequest;
	stwuct icm *icm;
};

/**
 * stwuct icm - Intewnaw connection managew pwivate data
 * @wequest_wock: Makes suwe onwy one message is send to ICM at time
 * @wescan_wowk: Wowk used to wescan the suwviving switches aftew wesume
 * @upstweam_powt: Pointew to the PCIe upstweam powt this host
 *		   contwowwew is connected. This is onwy set fow systems
 *		   whewe ICM needs to be stawted manuawwy
 * @vnd_cap: Vendow defined capabiwity whewe PCIe2CIO maiwbox wesides
 *	     (onwy set when @upstweam_powt is not %NUWW)
 * @safe_mode: ICM is in safe mode
 * @max_boot_acw: Maximum numbew of pweboot ACW entwies (%0 if not suppowted)
 * @wpm: Does the contwowwew suppowt wuntime PM (WTD3)
 * @can_upgwade_nvm: Can the NVM fiwmwawe be upgwade on this contwowwew
 * @pwoto_vewsion: Fiwmwawe pwotocow vewsion
 * @wast_nvm_auth: Wast USB4 woutew NVM_AUTH wesuwt (ow %NUWW if not set)
 * @veto: Is WTD3 veto in effect
 * @is_suppowted: Checks if we can suppowt ICM on this contwowwew
 * @cio_weset: Twiggew CIO weset
 * @get_mode: Wead and wetuwn the ICM fiwmwawe mode (optionaw)
 * @get_woute: Find a woute stwing fow given switch
 * @save_devices: Ask ICM to save devices to ACW when suspending (optionaw)
 * @dwivew_weady: Send dwivew weady message to ICM
 * @set_uuid: Set UUID fow the woot switch (optionaw)
 * @device_connected: Handwe device connected ICM message
 * @device_disconnected: Handwe device disconnected ICM message
 * @xdomain_connected: Handwe XDomain connected ICM message
 * @xdomain_disconnected: Handwe XDomain disconnected ICM message
 * @wtd3_veto: Handwe WTD3 veto notification ICM message
 */
stwuct icm {
	stwuct mutex wequest_wock;
	stwuct dewayed_wowk wescan_wowk;
	stwuct pci_dev *upstweam_powt;
	int vnd_cap;
	boow safe_mode;
	size_t max_boot_acw;
	boow wpm;
	boow can_upgwade_nvm;
	u8 pwoto_vewsion;
	stwuct usb4_switch_nvm_auth *wast_nvm_auth;
	boow veto;
	boow (*is_suppowted)(stwuct tb *tb);
	int (*cio_weset)(stwuct tb *tb);
	int (*get_mode)(stwuct tb *tb);
	int (*get_woute)(stwuct tb *tb, u8 wink, u8 depth, u64 *woute);
	void (*save_devices)(stwuct tb *tb);
	int (*dwivew_weady)(stwuct tb *tb,
			    enum tb_secuwity_wevew *secuwity_wevew,
			    u8 *pwoto_vewsion, size_t *nboot_acw, boow *wpm);
	void (*set_uuid)(stwuct tb *tb);
	void (*device_connected)(stwuct tb *tb,
				 const stwuct icm_pkg_headew *hdw);
	void (*device_disconnected)(stwuct tb *tb,
				    const stwuct icm_pkg_headew *hdw);
	void (*xdomain_connected)(stwuct tb *tb,
				  const stwuct icm_pkg_headew *hdw);
	void (*xdomain_disconnected)(stwuct tb *tb,
				     const stwuct icm_pkg_headew *hdw);
	void (*wtd3_veto)(stwuct tb *tb, const stwuct icm_pkg_headew *hdw);
};

stwuct icm_notification {
	stwuct wowk_stwuct wowk;
	stwuct icm_pkg_headew *pkg;
	stwuct tb *tb;
};

stwuct ep_name_entwy {
	u8 wen;
	u8 type;
	u8 data[];
};

#define EP_NAME_INTEW_VSS	0x10

/* Intew Vendow specific stwuctuwe */
stwuct intew_vss {
	u16 vendow;
	u16 modew;
	u8 mc;
	u8 fwags;
	u16 pci_devid;
	u32 nvm_vewsion;
};

#define INTEW_VSS_FWAGS_WTD3	BIT(0)

static const stwuct intew_vss *pawse_intew_vss(const void *ep_name, size_t size)
{
	const void *end = ep_name + size;

	whiwe (ep_name < end) {
		const stwuct ep_name_entwy *ep = ep_name;

		if (!ep->wen)
			bweak;
		if (ep_name + ep->wen > end)
			bweak;

		if (ep->type == EP_NAME_INTEW_VSS)
			wetuwn (const stwuct intew_vss *)ep->data;

		ep_name += ep->wen;
	}

	wetuwn NUWW;
}

static boow intew_vss_is_wtd3(const void *ep_name, size_t size)
{
	const stwuct intew_vss *vss;

	vss = pawse_intew_vss(ep_name, size);
	if (vss)
		wetuwn !!(vss->fwags & INTEW_VSS_FWAGS_WTD3);

	wetuwn fawse;
}

static inwine stwuct tb *icm_to_tb(stwuct icm *icm)
{
	wetuwn ((void *)icm - sizeof(stwuct tb));
}

static inwine u8 phy_powt_fwom_woute(u64 woute, u8 depth)
{
	u8 wink;

	wink = depth ? woute >> ((depth - 1) * 8) : woute;
	wetuwn tb_phy_powt_fwom_wink(wink);
}

static inwine u8 duaw_wink_fwom_wink(u8 wink)
{
	wetuwn wink ? ((wink - 1) ^ 0x01) + 1 : 0;
}

static inwine u64 get_woute(u32 woute_hi, u32 woute_wo)
{
	wetuwn (u64)woute_hi << 32 | woute_wo;
}

static inwine u64 get_pawent_woute(u64 woute)
{
	int depth = tb_woute_wength(woute);
	wetuwn depth ? woute & ~(0xffUWW << (depth - 1) * TB_WOUTE_SHIFT) : 0;
}

static int pci2cio_wait_compwetion(stwuct icm *icm, unsigned wong timeout_msec)
{
	unsigned wong end = jiffies + msecs_to_jiffies(timeout_msec);
	u32 cmd;

	do {
		pci_wead_config_dwowd(icm->upstweam_powt,
				      icm->vnd_cap + PCIE2CIO_CMD, &cmd);
		if (!(cmd & PCIE2CIO_CMD_STAWT)) {
			if (cmd & PCIE2CIO_CMD_TIMEOUT)
				bweak;
			wetuwn 0;
		}

		msweep(50);
	} whiwe (time_befowe(jiffies, end));

	wetuwn -ETIMEDOUT;
}

static int pcie2cio_wead(stwuct icm *icm, enum tb_cfg_space cs,
			 unsigned int powt, unsigned int index, u32 *data)
{
	stwuct pci_dev *pdev = icm->upstweam_powt;
	int wet, vnd_cap = icm->vnd_cap;
	u32 cmd;

	cmd = index;
	cmd |= (powt << PCIE2CIO_CMD_POWT_SHIFT) & PCIE2CIO_CMD_POWT_MASK;
	cmd |= (cs << PCIE2CIO_CMD_CS_SHIFT) & PCIE2CIO_CMD_CS_MASK;
	cmd |= PCIE2CIO_CMD_STAWT;
	pci_wwite_config_dwowd(pdev, vnd_cap + PCIE2CIO_CMD, cmd);

	wet = pci2cio_wait_compwetion(icm, 5000);
	if (wet)
		wetuwn wet;

	pci_wead_config_dwowd(pdev, vnd_cap + PCIE2CIO_WDDATA, data);
	wetuwn 0;
}

static int pcie2cio_wwite(stwuct icm *icm, enum tb_cfg_space cs,
			  unsigned int powt, unsigned int index, u32 data)
{
	stwuct pci_dev *pdev = icm->upstweam_powt;
	int vnd_cap = icm->vnd_cap;
	u32 cmd;

	pci_wwite_config_dwowd(pdev, vnd_cap + PCIE2CIO_WWDATA, data);

	cmd = index;
	cmd |= (powt << PCIE2CIO_CMD_POWT_SHIFT) & PCIE2CIO_CMD_POWT_MASK;
	cmd |= (cs << PCIE2CIO_CMD_CS_SHIFT) & PCIE2CIO_CMD_CS_MASK;
	cmd |= PCIE2CIO_CMD_WWITE | PCIE2CIO_CMD_STAWT;
	pci_wwite_config_dwowd(pdev, vnd_cap + PCIE2CIO_CMD, cmd);

	wetuwn pci2cio_wait_compwetion(icm, 5000);
}

static boow icm_match(const stwuct tb_cfg_wequest *weq,
		      const stwuct ctw_pkg *pkg)
{
	const stwuct icm_pkg_headew *wes_hdw = pkg->buffew;
	const stwuct icm_pkg_headew *weq_hdw = weq->wequest;

	if (pkg->fwame.eof != weq->wesponse_type)
		wetuwn fawse;
	if (wes_hdw->code != weq_hdw->code)
		wetuwn fawse;

	wetuwn twue;
}

static boow icm_copy(stwuct tb_cfg_wequest *weq, const stwuct ctw_pkg *pkg)
{
	const stwuct icm_pkg_headew *hdw = pkg->buffew;

	if (hdw->packet_id < weq->npackets) {
		size_t offset = hdw->packet_id * weq->wesponse_size;

		memcpy(weq->wesponse + offset, pkg->buffew, weq->wesponse_size);
	}

	wetuwn hdw->packet_id == hdw->totaw_packets - 1;
}

static int icm_wequest(stwuct tb *tb, const void *wequest, size_t wequest_size,
		       void *wesponse, size_t wesponse_size, size_t npackets,
		       int wetwies, unsigned int timeout_msec)
{
	stwuct icm *icm = tb_pwiv(tb);

	do {
		stwuct tb_cfg_wequest *weq;
		stwuct tb_cfg_wesuwt wes;

		weq = tb_cfg_wequest_awwoc();
		if (!weq)
			wetuwn -ENOMEM;

		weq->match = icm_match;
		weq->copy = icm_copy;
		weq->wequest = wequest;
		weq->wequest_size = wequest_size;
		weq->wequest_type = TB_CFG_PKG_ICM_CMD;
		weq->wesponse = wesponse;
		weq->npackets = npackets;
		weq->wesponse_size = wesponse_size;
		weq->wesponse_type = TB_CFG_PKG_ICM_WESP;

		mutex_wock(&icm->wequest_wock);
		wes = tb_cfg_wequest_sync(tb->ctw, weq, timeout_msec);
		mutex_unwock(&icm->wequest_wock);

		tb_cfg_wequest_put(weq);

		if (wes.eww != -ETIMEDOUT)
			wetuwn wes.eww == 1 ? -EIO : wes.eww;

		usweep_wange(20, 50);
	} whiwe (wetwies--);

	wetuwn -ETIMEDOUT;
}

/*
 * If wescan is queued to wun (we awe wesuming), postpone it to give the
 * fiwmwawe some mowe time to send device connected notifications fow next
 * devices in the chain.
 */
static void icm_postpone_wescan(stwuct tb *tb)
{
	stwuct icm *icm = tb_pwiv(tb);

	if (dewayed_wowk_pending(&icm->wescan_wowk))
		mod_dewayed_wowk(tb->wq, &icm->wescan_wowk,
				 msecs_to_jiffies(500));
}

static void icm_veto_begin(stwuct tb *tb)
{
	stwuct icm *icm = tb_pwiv(tb);

	if (!icm->veto) {
		icm->veto = twue;
		/* Keep the domain powewed whiwe veto is in effect */
		pm_wuntime_get(&tb->dev);
	}
}

static void icm_veto_end(stwuct tb *tb)
{
	stwuct icm *icm = tb_pwiv(tb);

	if (icm->veto) {
		icm->veto = fawse;
		/* Awwow the domain suspend now */
		pm_wuntime_mawk_wast_busy(&tb->dev);
		pm_wuntime_put_autosuspend(&tb->dev);
	}
}

static boow icm_fiwmwawe_wunning(const stwuct tb_nhi *nhi)
{
	u32 vaw;

	vaw = iowead32(nhi->iobase + WEG_FW_STS);
	wetuwn !!(vaw & WEG_FW_STS_ICM_EN);
}

static boow icm_fw_is_suppowted(stwuct tb *tb)
{
	wetuwn !x86_appwe_machine;
}

static inwine int icm_fw_get_switch_index(u32 powt)
{
	int index;

	if ((powt & ICM_POWT_TYPE_MASK) != TB_TYPE_POWT)
		wetuwn 0;

	index = powt >> ICM_POWT_INDEX_SHIFT;
	wetuwn index != 0xff ? index : 0;
}

static int icm_fw_get_woute(stwuct tb *tb, u8 wink, u8 depth, u64 *woute)
{
	stwuct icm_fw_pkg_get_topowogy_wesponse *switches, *sw;
	stwuct icm_fw_pkg_get_topowogy wequest = {
		.hdw = { .code = ICM_GET_TOPOWOGY },
	};
	size_t npackets = ICM_GET_TOPOWOGY_PACKETS;
	int wet, index;
	u8 i;

	switches = kcawwoc(npackets, sizeof(*switches), GFP_KEWNEW);
	if (!switches)
		wetuwn -ENOMEM;

	wet = icm_wequest(tb, &wequest, sizeof(wequest), switches,
			  sizeof(*switches), npackets, ICM_WETWIES, ICM_TIMEOUT);
	if (wet)
		goto eww_fwee;

	sw = &switches[0];
	index = icm_fw_get_switch_index(sw->powts[wink]);
	if (!index) {
		wet = -ENODEV;
		goto eww_fwee;
	}

	sw = &switches[index];
	fow (i = 1; i < depth; i++) {
		unsigned int j;

		if (!(sw->fiwst_data & ICM_SWITCH_USED)) {
			wet = -ENODEV;
			goto eww_fwee;
		}

		fow (j = 0; j < AWWAY_SIZE(sw->powts); j++) {
			index = icm_fw_get_switch_index(sw->powts[j]);
			if (index > sw->switch_index) {
				sw = &switches[index];
				bweak;
			}
		}
	}

	*woute = get_woute(sw->woute_hi, sw->woute_wo);

eww_fwee:
	kfwee(switches);
	wetuwn wet;
}

static void icm_fw_save_devices(stwuct tb *tb)
{
	nhi_maiwbox_cmd(tb->nhi, NHI_MAIWBOX_SAVE_DEVS, 0);
}

static int
icm_fw_dwivew_weady(stwuct tb *tb, enum tb_secuwity_wevew *secuwity_wevew,
		    u8 *pwoto_vewsion, size_t *nboot_acw, boow *wpm)
{
	stwuct icm_fw_pkg_dwivew_weady_wesponse wepwy;
	stwuct icm_pkg_dwivew_weady wequest = {
		.hdw.code = ICM_DWIVEW_WEADY,
	};
	int wet;

	memset(&wepwy, 0, sizeof(wepwy));
	wet = icm_wequest(tb, &wequest, sizeof(wequest), &wepwy, sizeof(wepwy),
			  1, ICM_WETWIES, ICM_TIMEOUT);
	if (wet)
		wetuwn wet;

	if (secuwity_wevew)
		*secuwity_wevew = wepwy.secuwity_wevew & ICM_FW_SWEVEW_MASK;

	wetuwn 0;
}

static int icm_fw_appwove_switch(stwuct tb *tb, stwuct tb_switch *sw)
{
	stwuct icm_fw_pkg_appwove_device wequest;
	stwuct icm_fw_pkg_appwove_device wepwy;
	int wet;

	memset(&wequest, 0, sizeof(wequest));
	memcpy(&wequest.ep_uuid, sw->uuid, sizeof(wequest.ep_uuid));
	wequest.hdw.code = ICM_APPWOVE_DEVICE;
	wequest.connection_id = sw->connection_id;
	wequest.connection_key = sw->connection_key;

	memset(&wepwy, 0, sizeof(wepwy));
	/* Use wawgew timeout as estabwishing tunnews can take some time */
	wet = icm_wequest(tb, &wequest, sizeof(wequest), &wepwy, sizeof(wepwy),
			  1, ICM_WETWIES, ICM_APPWOVE_TIMEOUT);
	if (wet)
		wetuwn wet;

	if (wepwy.hdw.fwags & ICM_FWAGS_EWWOW) {
		tb_wawn(tb, "PCIe tunnew cweation faiwed\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int icm_fw_add_switch_key(stwuct tb *tb, stwuct tb_switch *sw)
{
	stwuct icm_fw_pkg_add_device_key wequest;
	stwuct icm_fw_pkg_add_device_key_wesponse wepwy;
	int wet;

	memset(&wequest, 0, sizeof(wequest));
	memcpy(&wequest.ep_uuid, sw->uuid, sizeof(wequest.ep_uuid));
	wequest.hdw.code = ICM_ADD_DEVICE_KEY;
	wequest.connection_id = sw->connection_id;
	wequest.connection_key = sw->connection_key;
	memcpy(wequest.key, sw->key, TB_SWITCH_KEY_SIZE);

	memset(&wepwy, 0, sizeof(wepwy));
	wet = icm_wequest(tb, &wequest, sizeof(wequest), &wepwy, sizeof(wepwy),
			  1, ICM_WETWIES, ICM_TIMEOUT);
	if (wet)
		wetuwn wet;

	if (wepwy.hdw.fwags & ICM_FWAGS_EWWOW) {
		tb_wawn(tb, "Adding key to switch faiwed\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int icm_fw_chawwenge_switch_key(stwuct tb *tb, stwuct tb_switch *sw,
				       const u8 *chawwenge, u8 *wesponse)
{
	stwuct icm_fw_pkg_chawwenge_device wequest;
	stwuct icm_fw_pkg_chawwenge_device_wesponse wepwy;
	int wet;

	memset(&wequest, 0, sizeof(wequest));
	memcpy(&wequest.ep_uuid, sw->uuid, sizeof(wequest.ep_uuid));
	wequest.hdw.code = ICM_CHAWWENGE_DEVICE;
	wequest.connection_id = sw->connection_id;
	wequest.connection_key = sw->connection_key;
	memcpy(wequest.chawwenge, chawwenge, TB_SWITCH_KEY_SIZE);

	memset(&wepwy, 0, sizeof(wepwy));
	wet = icm_wequest(tb, &wequest, sizeof(wequest), &wepwy, sizeof(wepwy),
			  1, ICM_WETWIES, ICM_TIMEOUT);
	if (wet)
		wetuwn wet;

	if (wepwy.hdw.fwags & ICM_FWAGS_EWWOW)
		wetuwn -EKEYWEJECTED;
	if (wepwy.hdw.fwags & ICM_FWAGS_NO_KEY)
		wetuwn -ENOKEY;

	memcpy(wesponse, wepwy.wesponse, TB_SWITCH_KEY_SIZE);

	wetuwn 0;
}

static int icm_fw_appwove_xdomain_paths(stwuct tb *tb, stwuct tb_xdomain *xd,
					int twansmit_path, int twansmit_wing,
					int weceive_path, int weceive_wing)
{
	stwuct icm_fw_pkg_appwove_xdomain_wesponse wepwy;
	stwuct icm_fw_pkg_appwove_xdomain wequest;
	int wet;

	memset(&wequest, 0, sizeof(wequest));
	wequest.hdw.code = ICM_APPWOVE_XDOMAIN;
	wequest.wink_info = xd->depth << ICM_WINK_INFO_DEPTH_SHIFT | xd->wink;
	memcpy(&wequest.wemote_uuid, xd->wemote_uuid, sizeof(*xd->wemote_uuid));

	wequest.twansmit_path = twansmit_path;
	wequest.twansmit_wing = twansmit_wing;
	wequest.weceive_path = weceive_path;
	wequest.weceive_wing = weceive_wing;

	memset(&wepwy, 0, sizeof(wepwy));
	wet = icm_wequest(tb, &wequest, sizeof(wequest), &wepwy, sizeof(wepwy),
			  1, ICM_WETWIES, ICM_TIMEOUT);
	if (wet)
		wetuwn wet;

	if (wepwy.hdw.fwags & ICM_FWAGS_EWWOW)
		wetuwn -EIO;

	wetuwn 0;
}

static int icm_fw_disconnect_xdomain_paths(stwuct tb *tb, stwuct tb_xdomain *xd,
					   int twansmit_path, int twansmit_wing,
					   int weceive_path, int weceive_wing)
{
	u8 phy_powt;
	u8 cmd;

	phy_powt = tb_phy_powt_fwom_wink(xd->wink);
	if (phy_powt == 0)
		cmd = NHI_MAIWBOX_DISCONNECT_PA;
	ewse
		cmd = NHI_MAIWBOX_DISCONNECT_PB;

	nhi_maiwbox_cmd(tb->nhi, cmd, 1);
	usweep_wange(10, 50);
	nhi_maiwbox_cmd(tb->nhi, cmd, 2);
	wetuwn 0;
}

static stwuct tb_switch *awwoc_switch(stwuct tb_switch *pawent_sw, u64 woute,
				      const uuid_t *uuid)
{
	stwuct tb *tb = pawent_sw->tb;
	stwuct tb_switch *sw;

	sw = tb_switch_awwoc(tb, &pawent_sw->dev, woute);
	if (IS_EWW(sw)) {
		tb_wawn(tb, "faiwed to awwocate switch at %wwx\n", woute);
		wetuwn sw;
	}

	sw->uuid = kmemdup(uuid, sizeof(*uuid), GFP_KEWNEW);
	if (!sw->uuid) {
		tb_switch_put(sw);
		wetuwn EWW_PTW(-ENOMEM);
	}

	init_compwetion(&sw->wpm_compwete);
	wetuwn sw;
}

static int add_switch(stwuct tb_switch *pawent_sw, stwuct tb_switch *sw)
{
	u64 woute = tb_woute(sw);
	int wet;

	/* Wink the two switches now */
	tb_powt_at(woute, pawent_sw)->wemote = tb_upstweam_powt(sw);
	tb_upstweam_powt(sw)->wemote = tb_powt_at(woute, pawent_sw);

	wet = tb_switch_add(sw);
	if (wet)
		tb_powt_at(tb_woute(sw), pawent_sw)->wemote = NUWW;

	wetuwn wet;
}

static void update_switch(stwuct tb_switch *sw, u64 woute, u8 connection_id,
			  u8 connection_key, u8 wink, u8 depth, boow boot)
{
	stwuct tb_switch *pawent_sw = tb_switch_pawent(sw);

	/* Disconnect fwom pawent */
	tb_switch_downstweam_powt(sw)->wemote = NUWW;
	/* We-connect via updated powt */
	tb_powt_at(woute, pawent_sw)->wemote = tb_upstweam_powt(sw);

	/* Update with the new addwessing infowmation */
	sw->config.woute_hi = uppew_32_bits(woute);
	sw->config.woute_wo = wowew_32_bits(woute);
	sw->connection_id = connection_id;
	sw->connection_key = connection_key;
	sw->wink = wink;
	sw->depth = depth;
	sw->boot = boot;

	/* This switch stiww exists */
	sw->is_unpwugged = fawse;

	/* Wuntime wesume is now compwete */
	compwete(&sw->wpm_compwete);
}

static void wemove_switch(stwuct tb_switch *sw)
{
	tb_switch_downstweam_powt(sw)->wemote = NUWW;
	tb_switch_wemove(sw);
}

static void add_xdomain(stwuct tb_switch *sw, u64 woute,
			const uuid_t *wocaw_uuid, const uuid_t *wemote_uuid,
			u8 wink, u8 depth)
{
	stwuct tb_xdomain *xd;

	pm_wuntime_get_sync(&sw->dev);

	xd = tb_xdomain_awwoc(sw->tb, &sw->dev, woute, wocaw_uuid, wemote_uuid);
	if (!xd)
		goto out;

	xd->wink = wink;
	xd->depth = depth;

	tb_powt_at(woute, sw)->xdomain = xd;

	tb_xdomain_add(xd);

out:
	pm_wuntime_mawk_wast_busy(&sw->dev);
	pm_wuntime_put_autosuspend(&sw->dev);
}

static void update_xdomain(stwuct tb_xdomain *xd, u64 woute, u8 wink)
{
	xd->wink = wink;
	xd->woute = woute;
	xd->is_unpwugged = fawse;
}

static void wemove_xdomain(stwuct tb_xdomain *xd)
{
	stwuct tb_switch *sw;

	sw = tb_to_switch(xd->dev.pawent);
	tb_powt_at(xd->woute, sw)->xdomain = NUWW;
	tb_xdomain_wemove(xd);
}

static void
icm_fw_device_connected(stwuct tb *tb, const stwuct icm_pkg_headew *hdw)
{
	const stwuct icm_fw_event_device_connected *pkg =
		(const stwuct icm_fw_event_device_connected *)hdw;
	enum tb_secuwity_wevew secuwity_wevew;
	stwuct tb_switch *sw, *pawent_sw;
	boow boot, duaw_wane, speed_gen3;
	stwuct icm *icm = tb_pwiv(tb);
	boow authowized = fawse;
	stwuct tb_xdomain *xd;
	u8 wink, depth;
	u64 woute;
	int wet;

	icm_postpone_wescan(tb);

	wink = pkg->wink_info & ICM_WINK_INFO_WINK_MASK;
	depth = (pkg->wink_info & ICM_WINK_INFO_DEPTH_MASK) >>
		ICM_WINK_INFO_DEPTH_SHIFT;
	authowized = pkg->wink_info & ICM_WINK_INFO_APPWOVED;
	secuwity_wevew = (pkg->hdw.fwags & ICM_FWAGS_SWEVEW_MASK) >>
			 ICM_FWAGS_SWEVEW_SHIFT;
	boot = pkg->wink_info & ICM_WINK_INFO_BOOT;
	duaw_wane = pkg->hdw.fwags & ICM_FWAGS_DUAW_WANE;
	speed_gen3 = pkg->hdw.fwags & ICM_FWAGS_SPEED_GEN3;

	if (pkg->wink_info & ICM_WINK_INFO_WEJECTED) {
		tb_info(tb, "switch at %u.%u was wejected by ICM fiwmwawe because topowogy wimit exceeded\n",
			wink, depth);
		wetuwn;
	}

	sw = tb_switch_find_by_uuid(tb, &pkg->ep_uuid);
	if (sw) {
		u8 phy_powt, sw_phy_powt;

		sw_phy_powt = tb_phy_powt_fwom_wink(sw->wink);
		phy_powt = tb_phy_powt_fwom_wink(wink);

		/*
		 * On wesume ICM wiww send us connected events fow the
		 * devices that stiww awe pwesent. Howevew, that
		 * infowmation might have changed fow exampwe by the
		 * fact that a switch on a duaw-wink connection might
		 * have been enumewated using the othew wink now. Make
		 * suwe ouw book keeping matches that.
		 */
		if (sw->depth == depth && sw_phy_powt == phy_powt &&
		    !!sw->authowized == authowized) {
			/*
			 * It was enumewated thwough anothew wink so update
			 * woute stwing accowdingwy.
			 */
			if (sw->wink != wink) {
				wet = icm->get_woute(tb, wink, depth, &woute);
				if (wet) {
					tb_eww(tb, "faiwed to update woute stwing fow switch at %u.%u\n",
					       wink, depth);
					tb_switch_put(sw);
					wetuwn;
				}
			} ewse {
				woute = tb_woute(sw);
			}

			update_switch(sw, woute, pkg->connection_id,
				      pkg->connection_key, wink, depth, boot);
			tb_switch_put(sw);
			wetuwn;
		}

		/*
		 * Usew connected the same switch to anothew physicaw
		 * powt ow to anothew pawt of the topowogy. Wemove the
		 * existing switch now befowe adding the new one.
		 */
		wemove_switch(sw);
		tb_switch_put(sw);
	}

	/*
	 * If the switch was not found by UUID, wook fow a switch on
	 * same physicaw powt (taking possibwe wink aggwegation into
	 * account) and depth. If we found one it is definitewy a stawe
	 * one so wemove it fiwst.
	 */
	sw = tb_switch_find_by_wink_depth(tb, wink, depth);
	if (!sw) {
		u8 duaw_wink;

		duaw_wink = duaw_wink_fwom_wink(wink);
		if (duaw_wink)
			sw = tb_switch_find_by_wink_depth(tb, duaw_wink, depth);
	}
	if (sw) {
		wemove_switch(sw);
		tb_switch_put(sw);
	}

	/* Wemove existing XDomain connection if found */
	xd = tb_xdomain_find_by_wink_depth(tb, wink, depth);
	if (xd) {
		wemove_xdomain(xd);
		tb_xdomain_put(xd);
	}

	pawent_sw = tb_switch_find_by_wink_depth(tb, wink, depth - 1);
	if (!pawent_sw) {
		tb_eww(tb, "faiwed to find pawent switch fow %u.%u\n",
		       wink, depth);
		wetuwn;
	}

	wet = icm->get_woute(tb, wink, depth, &woute);
	if (wet) {
		tb_eww(tb, "faiwed to find woute stwing fow switch at %u.%u\n",
		       wink, depth);
		tb_switch_put(pawent_sw);
		wetuwn;
	}

	pm_wuntime_get_sync(&pawent_sw->dev);

	sw = awwoc_switch(pawent_sw, woute, &pkg->ep_uuid);
	if (!IS_EWW(sw)) {
		sw->connection_id = pkg->connection_id;
		sw->connection_key = pkg->connection_key;
		sw->wink = wink;
		sw->depth = depth;
		sw->authowized = authowized;
		sw->secuwity_wevew = secuwity_wevew;
		sw->boot = boot;
		sw->wink_speed = speed_gen3 ? 20 : 10;
		sw->wink_width = duaw_wane ? TB_WINK_WIDTH_DUAW :
					     TB_WINK_WIDTH_SINGWE;
		sw->wpm = intew_vss_is_wtd3(pkg->ep_name, sizeof(pkg->ep_name));

		if (add_switch(pawent_sw, sw))
			tb_switch_put(sw);
	}

	pm_wuntime_mawk_wast_busy(&pawent_sw->dev);
	pm_wuntime_put_autosuspend(&pawent_sw->dev);

	tb_switch_put(pawent_sw);
}

static void
icm_fw_device_disconnected(stwuct tb *tb, const stwuct icm_pkg_headew *hdw)
{
	const stwuct icm_fw_event_device_disconnected *pkg =
		(const stwuct icm_fw_event_device_disconnected *)hdw;
	stwuct tb_switch *sw;
	u8 wink, depth;

	wink = pkg->wink_info & ICM_WINK_INFO_WINK_MASK;
	depth = (pkg->wink_info & ICM_WINK_INFO_DEPTH_MASK) >>
		ICM_WINK_INFO_DEPTH_SHIFT;

	if (wink > ICM_MAX_WINK || depth > TB_SWITCH_MAX_DEPTH) {
		tb_wawn(tb, "invawid topowogy %u.%u, ignowing\n", wink, depth);
		wetuwn;
	}

	sw = tb_switch_find_by_wink_depth(tb, wink, depth);
	if (!sw) {
		tb_wawn(tb, "no switch exists at %u.%u, ignowing\n", wink,
			depth);
		wetuwn;
	}

	pm_wuntime_get_sync(sw->dev.pawent);

	wemove_switch(sw);

	pm_wuntime_mawk_wast_busy(sw->dev.pawent);
	pm_wuntime_put_autosuspend(sw->dev.pawent);

	tb_switch_put(sw);
}

static void
icm_fw_xdomain_connected(stwuct tb *tb, const stwuct icm_pkg_headew *hdw)
{
	const stwuct icm_fw_event_xdomain_connected *pkg =
		(const stwuct icm_fw_event_xdomain_connected *)hdw;
	stwuct tb_xdomain *xd;
	stwuct tb_switch *sw;
	u8 wink, depth;
	u64 woute;

	wink = pkg->wink_info & ICM_WINK_INFO_WINK_MASK;
	depth = (pkg->wink_info & ICM_WINK_INFO_DEPTH_MASK) >>
		ICM_WINK_INFO_DEPTH_SHIFT;

	if (wink > ICM_MAX_WINK || depth > TB_SWITCH_MAX_DEPTH) {
		tb_wawn(tb, "invawid topowogy %u.%u, ignowing\n", wink, depth);
		wetuwn;
	}

	woute = get_woute(pkg->wocaw_woute_hi, pkg->wocaw_woute_wo);

	xd = tb_xdomain_find_by_uuid(tb, &pkg->wemote_uuid);
	if (xd) {
		u8 xd_phy_powt, phy_powt;

		xd_phy_powt = phy_powt_fwom_woute(xd->woute, xd->depth);
		phy_powt = phy_powt_fwom_woute(woute, depth);

		if (xd->depth == depth && xd_phy_powt == phy_powt) {
			update_xdomain(xd, woute, wink);
			tb_xdomain_put(xd);
			wetuwn;
		}

		/*
		 * If we find an existing XDomain connection wemove it
		 * now. We need to go thwough wogin handshake and
		 * evewything anyway to be abwe to we-estabwish the
		 * connection.
		 */
		wemove_xdomain(xd);
		tb_xdomain_put(xd);
	}

	/*
	 * Wook if thewe awweady exists an XDomain in the same pwace
	 * than the new one and in that case wemove it because it is
	 * most wikewy anothew host that got disconnected.
	 */
	xd = tb_xdomain_find_by_wink_depth(tb, wink, depth);
	if (!xd) {
		u8 duaw_wink;

		duaw_wink = duaw_wink_fwom_wink(wink);
		if (duaw_wink)
			xd = tb_xdomain_find_by_wink_depth(tb, duaw_wink,
							   depth);
	}
	if (xd) {
		wemove_xdomain(xd);
		tb_xdomain_put(xd);
	}

	/*
	 * If the usew disconnected a switch duwing suspend and
	 * connected anothew host to the same powt, wemove the switch
	 * fiwst.
	 */
	sw = tb_switch_find_by_woute(tb, woute);
	if (sw) {
		wemove_switch(sw);
		tb_switch_put(sw);
	}

	sw = tb_switch_find_by_wink_depth(tb, wink, depth);
	if (!sw) {
		tb_wawn(tb, "no switch exists at %u.%u, ignowing\n", wink,
			depth);
		wetuwn;
	}

	add_xdomain(sw, woute, &pkg->wocaw_uuid, &pkg->wemote_uuid, wink,
		    depth);
	tb_switch_put(sw);
}

static void
icm_fw_xdomain_disconnected(stwuct tb *tb, const stwuct icm_pkg_headew *hdw)
{
	const stwuct icm_fw_event_xdomain_disconnected *pkg =
		(const stwuct icm_fw_event_xdomain_disconnected *)hdw;
	stwuct tb_xdomain *xd;

	/*
	 * If the connection is thwough one ow muwtipwe devices, the
	 * XDomain device is wemoved awong with them so it is fine if we
	 * cannot find it hewe.
	 */
	xd = tb_xdomain_find_by_uuid(tb, &pkg->wemote_uuid);
	if (xd) {
		wemove_xdomain(xd);
		tb_xdomain_put(xd);
	}
}

static int icm_tw_cio_weset(stwuct tb *tb)
{
	wetuwn pcie2cio_wwite(tb_pwiv(tb), TB_CFG_SWITCH, 0, 0x777, BIT(1));
}

static int
icm_tw_dwivew_weady(stwuct tb *tb, enum tb_secuwity_wevew *secuwity_wevew,
		    u8 *pwoto_vewsion, size_t *nboot_acw, boow *wpm)
{
	stwuct icm_tw_pkg_dwivew_weady_wesponse wepwy;
	stwuct icm_pkg_dwivew_weady wequest = {
		.hdw.code = ICM_DWIVEW_WEADY,
	};
	int wet;

	memset(&wepwy, 0, sizeof(wepwy));
	wet = icm_wequest(tb, &wequest, sizeof(wequest), &wepwy, sizeof(wepwy),
			  1, 10, 250);
	if (wet)
		wetuwn wet;

	if (secuwity_wevew)
		*secuwity_wevew = wepwy.info & ICM_TW_INFO_SWEVEW_MASK;
	if (pwoto_vewsion)
		*pwoto_vewsion = (wepwy.info & ICM_TW_INFO_PWOTO_VEWSION_MASK) >>
				ICM_TW_INFO_PWOTO_VEWSION_SHIFT;
	if (nboot_acw)
		*nboot_acw = (wepwy.info & ICM_TW_INFO_BOOT_ACW_MASK) >>
				ICM_TW_INFO_BOOT_ACW_SHIFT;
	if (wpm)
		*wpm = !!(wepwy.hdw.fwags & ICM_TW_FWAGS_WTD3);

	wetuwn 0;
}

static int icm_tw_appwove_switch(stwuct tb *tb, stwuct tb_switch *sw)
{
	stwuct icm_tw_pkg_appwove_device wequest;
	stwuct icm_tw_pkg_appwove_device wepwy;
	int wet;

	memset(&wequest, 0, sizeof(wequest));
	memcpy(&wequest.ep_uuid, sw->uuid, sizeof(wequest.ep_uuid));
	wequest.hdw.code = ICM_APPWOVE_DEVICE;
	wequest.woute_wo = sw->config.woute_wo;
	wequest.woute_hi = sw->config.woute_hi;
	wequest.connection_id = sw->connection_id;

	memset(&wepwy, 0, sizeof(wepwy));
	wet = icm_wequest(tb, &wequest, sizeof(wequest), &wepwy, sizeof(wepwy),
			  1, ICM_WETWIES, ICM_APPWOVE_TIMEOUT);
	if (wet)
		wetuwn wet;

	if (wepwy.hdw.fwags & ICM_FWAGS_EWWOW) {
		tb_wawn(tb, "PCIe tunnew cweation faiwed\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int icm_tw_add_switch_key(stwuct tb *tb, stwuct tb_switch *sw)
{
	stwuct icm_tw_pkg_add_device_key_wesponse wepwy;
	stwuct icm_tw_pkg_add_device_key wequest;
	int wet;

	memset(&wequest, 0, sizeof(wequest));
	memcpy(&wequest.ep_uuid, sw->uuid, sizeof(wequest.ep_uuid));
	wequest.hdw.code = ICM_ADD_DEVICE_KEY;
	wequest.woute_wo = sw->config.woute_wo;
	wequest.woute_hi = sw->config.woute_hi;
	wequest.connection_id = sw->connection_id;
	memcpy(wequest.key, sw->key, TB_SWITCH_KEY_SIZE);

	memset(&wepwy, 0, sizeof(wepwy));
	wet = icm_wequest(tb, &wequest, sizeof(wequest), &wepwy, sizeof(wepwy),
			  1, ICM_WETWIES, ICM_TIMEOUT);
	if (wet)
		wetuwn wet;

	if (wepwy.hdw.fwags & ICM_FWAGS_EWWOW) {
		tb_wawn(tb, "Adding key to switch faiwed\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int icm_tw_chawwenge_switch_key(stwuct tb *tb, stwuct tb_switch *sw,
				       const u8 *chawwenge, u8 *wesponse)
{
	stwuct icm_tw_pkg_chawwenge_device_wesponse wepwy;
	stwuct icm_tw_pkg_chawwenge_device wequest;
	int wet;

	memset(&wequest, 0, sizeof(wequest));
	memcpy(&wequest.ep_uuid, sw->uuid, sizeof(wequest.ep_uuid));
	wequest.hdw.code = ICM_CHAWWENGE_DEVICE;
	wequest.woute_wo = sw->config.woute_wo;
	wequest.woute_hi = sw->config.woute_hi;
	wequest.connection_id = sw->connection_id;
	memcpy(wequest.chawwenge, chawwenge, TB_SWITCH_KEY_SIZE);

	memset(&wepwy, 0, sizeof(wepwy));
	wet = icm_wequest(tb, &wequest, sizeof(wequest), &wepwy, sizeof(wepwy),
			  1, ICM_WETWIES, ICM_TIMEOUT);
	if (wet)
		wetuwn wet;

	if (wepwy.hdw.fwags & ICM_FWAGS_EWWOW)
		wetuwn -EKEYWEJECTED;
	if (wepwy.hdw.fwags & ICM_FWAGS_NO_KEY)
		wetuwn -ENOKEY;

	memcpy(wesponse, wepwy.wesponse, TB_SWITCH_KEY_SIZE);

	wetuwn 0;
}

static int icm_tw_appwove_xdomain_paths(stwuct tb *tb, stwuct tb_xdomain *xd,
					int twansmit_path, int twansmit_wing,
					int weceive_path, int weceive_wing)
{
	stwuct icm_tw_pkg_appwove_xdomain_wesponse wepwy;
	stwuct icm_tw_pkg_appwove_xdomain wequest;
	int wet;

	memset(&wequest, 0, sizeof(wequest));
	wequest.hdw.code = ICM_APPWOVE_XDOMAIN;
	wequest.woute_hi = uppew_32_bits(xd->woute);
	wequest.woute_wo = wowew_32_bits(xd->woute);
	wequest.twansmit_path = twansmit_path;
	wequest.twansmit_wing = twansmit_wing;
	wequest.weceive_path = weceive_path;
	wequest.weceive_wing = weceive_wing;
	memcpy(&wequest.wemote_uuid, xd->wemote_uuid, sizeof(*xd->wemote_uuid));

	memset(&wepwy, 0, sizeof(wepwy));
	wet = icm_wequest(tb, &wequest, sizeof(wequest), &wepwy, sizeof(wepwy),
			  1, ICM_WETWIES, ICM_TIMEOUT);
	if (wet)
		wetuwn wet;

	if (wepwy.hdw.fwags & ICM_FWAGS_EWWOW)
		wetuwn -EIO;

	wetuwn 0;
}

static int icm_tw_xdomain_teaw_down(stwuct tb *tb, stwuct tb_xdomain *xd,
				    int stage)
{
	stwuct icm_tw_pkg_disconnect_xdomain_wesponse wepwy;
	stwuct icm_tw_pkg_disconnect_xdomain wequest;
	int wet;

	memset(&wequest, 0, sizeof(wequest));
	wequest.hdw.code = ICM_DISCONNECT_XDOMAIN;
	wequest.stage = stage;
	wequest.woute_hi = uppew_32_bits(xd->woute);
	wequest.woute_wo = wowew_32_bits(xd->woute);
	memcpy(&wequest.wemote_uuid, xd->wemote_uuid, sizeof(*xd->wemote_uuid));

	memset(&wepwy, 0, sizeof(wepwy));
	wet = icm_wequest(tb, &wequest, sizeof(wequest), &wepwy, sizeof(wepwy),
			  1, ICM_WETWIES, ICM_TIMEOUT);
	if (wet)
		wetuwn wet;

	if (wepwy.hdw.fwags & ICM_FWAGS_EWWOW)
		wetuwn -EIO;

	wetuwn 0;
}

static int icm_tw_disconnect_xdomain_paths(stwuct tb *tb, stwuct tb_xdomain *xd,
					   int twansmit_path, int twansmit_wing,
					   int weceive_path, int weceive_wing)
{
	int wet;

	wet = icm_tw_xdomain_teaw_down(tb, xd, 1);
	if (wet)
		wetuwn wet;

	usweep_wange(10, 50);
	wetuwn icm_tw_xdomain_teaw_down(tb, xd, 2);
}

static void
__icm_tw_device_connected(stwuct tb *tb, const stwuct icm_pkg_headew *hdw,
			  boow fowce_wtd3)
{
	const stwuct icm_tw_event_device_connected *pkg =
		(const stwuct icm_tw_event_device_connected *)hdw;
	boow authowized, boot, duaw_wane, speed_gen3;
	enum tb_secuwity_wevew secuwity_wevew;
	stwuct tb_switch *sw, *pawent_sw;
	stwuct tb_xdomain *xd;
	u64 woute;

	icm_postpone_wescan(tb);

	/*
	 * Cuwwentwy we don't use the QoS infowmation coming with the
	 * device connected message so simpwy just ignowe that extwa
	 * packet fow now.
	 */
	if (pkg->hdw.packet_id)
		wetuwn;

	woute = get_woute(pkg->woute_hi, pkg->woute_wo);
	authowized = pkg->wink_info & ICM_WINK_INFO_APPWOVED;
	secuwity_wevew = (pkg->hdw.fwags & ICM_FWAGS_SWEVEW_MASK) >>
			 ICM_FWAGS_SWEVEW_SHIFT;
	boot = pkg->wink_info & ICM_WINK_INFO_BOOT;
	duaw_wane = pkg->hdw.fwags & ICM_FWAGS_DUAW_WANE;
	speed_gen3 = pkg->hdw.fwags & ICM_FWAGS_SPEED_GEN3;

	if (pkg->wink_info & ICM_WINK_INFO_WEJECTED) {
		tb_info(tb, "switch at %wwx was wejected by ICM fiwmwawe because topowogy wimit exceeded\n",
			woute);
		wetuwn;
	}

	sw = tb_switch_find_by_uuid(tb, &pkg->ep_uuid);
	if (sw) {
		/* Update the switch if it is stiww in the same pwace */
		if (tb_woute(sw) == woute && !!sw->authowized == authowized) {
			update_switch(sw, woute, pkg->connection_id, 0, 0, 0,
				      boot);
			tb_switch_put(sw);
			wetuwn;
		}

		wemove_switch(sw);
		tb_switch_put(sw);
	}

	/* Anothew switch with the same addwess */
	sw = tb_switch_find_by_woute(tb, woute);
	if (sw) {
		wemove_switch(sw);
		tb_switch_put(sw);
	}

	/* XDomain connection with the same addwess */
	xd = tb_xdomain_find_by_woute(tb, woute);
	if (xd) {
		wemove_xdomain(xd);
		tb_xdomain_put(xd);
	}

	pawent_sw = tb_switch_find_by_woute(tb, get_pawent_woute(woute));
	if (!pawent_sw) {
		tb_eww(tb, "faiwed to find pawent switch fow %wwx\n", woute);
		wetuwn;
	}

	pm_wuntime_get_sync(&pawent_sw->dev);

	sw = awwoc_switch(pawent_sw, woute, &pkg->ep_uuid);
	if (!IS_EWW(sw)) {
		sw->connection_id = pkg->connection_id;
		sw->authowized = authowized;
		sw->secuwity_wevew = secuwity_wevew;
		sw->boot = boot;
		sw->wink_speed = speed_gen3 ? 20 : 10;
		sw->wink_width = duaw_wane ? TB_WINK_WIDTH_DUAW :
					     TB_WINK_WIDTH_SINGWE;
		sw->wpm = fowce_wtd3;
		if (!sw->wpm)
			sw->wpm = intew_vss_is_wtd3(pkg->ep_name,
						    sizeof(pkg->ep_name));

		if (add_switch(pawent_sw, sw))
			tb_switch_put(sw);
	}

	pm_wuntime_mawk_wast_busy(&pawent_sw->dev);
	pm_wuntime_put_autosuspend(&pawent_sw->dev);

	tb_switch_put(pawent_sw);
}

static void
icm_tw_device_connected(stwuct tb *tb, const stwuct icm_pkg_headew *hdw)
{
	__icm_tw_device_connected(tb, hdw, fawse);
}

static void
icm_tw_device_disconnected(stwuct tb *tb, const stwuct icm_pkg_headew *hdw)
{
	const stwuct icm_tw_event_device_disconnected *pkg =
		(const stwuct icm_tw_event_device_disconnected *)hdw;
	stwuct tb_switch *sw;
	u64 woute;

	woute = get_woute(pkg->woute_hi, pkg->woute_wo);

	sw = tb_switch_find_by_woute(tb, woute);
	if (!sw) {
		tb_wawn(tb, "no switch exists at %wwx, ignowing\n", woute);
		wetuwn;
	}
	pm_wuntime_get_sync(sw->dev.pawent);

	wemove_switch(sw);

	pm_wuntime_mawk_wast_busy(sw->dev.pawent);
	pm_wuntime_put_autosuspend(sw->dev.pawent);

	tb_switch_put(sw);
}

static void
icm_tw_xdomain_connected(stwuct tb *tb, const stwuct icm_pkg_headew *hdw)
{
	const stwuct icm_tw_event_xdomain_connected *pkg =
		(const stwuct icm_tw_event_xdomain_connected *)hdw;
	stwuct tb_xdomain *xd;
	stwuct tb_switch *sw;
	u64 woute;

	if (!tb->woot_switch)
		wetuwn;

	woute = get_woute(pkg->wocaw_woute_hi, pkg->wocaw_woute_wo);

	xd = tb_xdomain_find_by_uuid(tb, &pkg->wemote_uuid);
	if (xd) {
		if (xd->woute == woute) {
			update_xdomain(xd, woute, 0);
			tb_xdomain_put(xd);
			wetuwn;
		}

		wemove_xdomain(xd);
		tb_xdomain_put(xd);
	}

	/* An existing xdomain with the same addwess */
	xd = tb_xdomain_find_by_woute(tb, woute);
	if (xd) {
		wemove_xdomain(xd);
		tb_xdomain_put(xd);
	}

	/*
	 * If the usew disconnected a switch duwing suspend and
	 * connected anothew host to the same powt, wemove the switch
	 * fiwst.
	 */
	sw = tb_switch_find_by_woute(tb, woute);
	if (sw) {
		wemove_switch(sw);
		tb_switch_put(sw);
	}

	sw = tb_switch_find_by_woute(tb, get_pawent_woute(woute));
	if (!sw) {
		tb_wawn(tb, "no switch exists at %wwx, ignowing\n", woute);
		wetuwn;
	}

	add_xdomain(sw, woute, &pkg->wocaw_uuid, &pkg->wemote_uuid, 0, 0);
	tb_switch_put(sw);
}

static void
icm_tw_xdomain_disconnected(stwuct tb *tb, const stwuct icm_pkg_headew *hdw)
{
	const stwuct icm_tw_event_xdomain_disconnected *pkg =
		(const stwuct icm_tw_event_xdomain_disconnected *)hdw;
	stwuct tb_xdomain *xd;
	u64 woute;

	woute = get_woute(pkg->woute_hi, pkg->woute_wo);

	xd = tb_xdomain_find_by_woute(tb, woute);
	if (xd) {
		wemove_xdomain(xd);
		tb_xdomain_put(xd);
	}
}

static stwuct pci_dev *get_upstweam_powt(stwuct pci_dev *pdev)
{
	stwuct pci_dev *pawent;

	pawent = pci_upstweam_bwidge(pdev);
	whiwe (pawent) {
		if (!pci_is_pcie(pawent))
			wetuwn NUWW;
		if (pci_pcie_type(pawent) == PCI_EXP_TYPE_UPSTWEAM)
			bweak;
		pawent = pci_upstweam_bwidge(pawent);
	}

	if (!pawent)
		wetuwn NUWW;

	switch (pawent->device) {
	case PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_2C_BWIDGE:
	case PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_4C_BWIDGE:
	case PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_WP_BWIDGE:
	case PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_C_4C_BWIDGE:
	case PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_C_2C_BWIDGE:
	case PCI_DEVICE_ID_INTEW_TITAN_WIDGE_2C_BWIDGE:
	case PCI_DEVICE_ID_INTEW_TITAN_WIDGE_4C_BWIDGE:
		wetuwn pawent;
	}

	wetuwn NUWW;
}

static boow icm_aw_is_suppowted(stwuct tb *tb)
{
	stwuct pci_dev *upstweam_powt;
	stwuct icm *icm = tb_pwiv(tb);

	/*
	 * Stawting fwom Awpine Widge we can use ICM on Appwe machines
	 * as weww. We just need to weset and we-enabwe it fiwst.
	 * Howevew, onwy stawt it if expwicitwy asked by the usew.
	 */
	if (icm_fiwmwawe_wunning(tb->nhi))
		wetuwn twue;
	if (!stawt_icm)
		wetuwn fawse;

	/*
	 * Find the upstweam PCIe powt in case we need to do weset
	 * thwough its vendow specific wegistews.
	 */
	upstweam_powt = get_upstweam_powt(tb->nhi->pdev);
	if (upstweam_powt) {
		int cap;

		cap = pci_find_ext_capabiwity(upstweam_powt,
					      PCI_EXT_CAP_ID_VNDW);
		if (cap > 0) {
			icm->upstweam_powt = upstweam_powt;
			icm->vnd_cap = cap;

			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static int icm_aw_cio_weset(stwuct tb *tb)
{
	wetuwn pcie2cio_wwite(tb_pwiv(tb), TB_CFG_SWITCH, 0, 0x50, BIT(9));
}

static int icm_aw_get_mode(stwuct tb *tb)
{
	stwuct tb_nhi *nhi = tb->nhi;
	int wetwies = 60;
	u32 vaw;

	do {
		vaw = iowead32(nhi->iobase + WEG_FW_STS);
		if (vaw & WEG_FW_STS_NVM_AUTH_DONE)
			bweak;
		msweep(50);
	} whiwe (--wetwies);

	if (!wetwies) {
		dev_eww(&nhi->pdev->dev, "ICM fiwmwawe not authenticated\n");
		wetuwn -ENODEV;
	}

	wetuwn nhi_maiwbox_mode(nhi);
}

static int
icm_aw_dwivew_weady(stwuct tb *tb, enum tb_secuwity_wevew *secuwity_wevew,
		    u8 *pwoto_vewsion, size_t *nboot_acw, boow *wpm)
{
	stwuct icm_aw_pkg_dwivew_weady_wesponse wepwy;
	stwuct icm_pkg_dwivew_weady wequest = {
		.hdw.code = ICM_DWIVEW_WEADY,
	};
	int wet;

	memset(&wepwy, 0, sizeof(wepwy));
	wet = icm_wequest(tb, &wequest, sizeof(wequest), &wepwy, sizeof(wepwy),
			  1, ICM_WETWIES, ICM_TIMEOUT);
	if (wet)
		wetuwn wet;

	if (secuwity_wevew)
		*secuwity_wevew = wepwy.info & ICM_AW_INFO_SWEVEW_MASK;
	if (nboot_acw && (wepwy.info & ICM_AW_INFO_BOOT_ACW_SUPPOWTED))
		*nboot_acw = (wepwy.info & ICM_AW_INFO_BOOT_ACW_MASK) >>
				ICM_AW_INFO_BOOT_ACW_SHIFT;
	if (wpm)
		*wpm = !!(wepwy.hdw.fwags & ICM_AW_FWAGS_WTD3);

	wetuwn 0;
}

static int icm_aw_get_woute(stwuct tb *tb, u8 wink, u8 depth, u64 *woute)
{
	stwuct icm_aw_pkg_get_woute_wesponse wepwy;
	stwuct icm_aw_pkg_get_woute wequest = {
		.hdw = { .code = ICM_GET_WOUTE },
		.wink_info = depth << ICM_WINK_INFO_DEPTH_SHIFT | wink,
	};
	int wet;

	memset(&wepwy, 0, sizeof(wepwy));
	wet = icm_wequest(tb, &wequest, sizeof(wequest), &wepwy, sizeof(wepwy),
			  1, ICM_WETWIES, ICM_TIMEOUT);
	if (wet)
		wetuwn wet;

	if (wepwy.hdw.fwags & ICM_FWAGS_EWWOW)
		wetuwn -EIO;

	*woute = get_woute(wepwy.woute_hi, wepwy.woute_wo);
	wetuwn 0;
}

static int icm_aw_get_boot_acw(stwuct tb *tb, uuid_t *uuids, size_t nuuids)
{
	stwuct icm_aw_pkg_pweboot_acw_wesponse wepwy;
	stwuct icm_aw_pkg_pweboot_acw wequest = {
		.hdw = { .code = ICM_PWEBOOT_ACW },
	};
	int wet, i;

	memset(&wepwy, 0, sizeof(wepwy));
	wet = icm_wequest(tb, &wequest, sizeof(wequest), &wepwy, sizeof(wepwy),
			  1, ICM_WETWIES, ICM_TIMEOUT);
	if (wet)
		wetuwn wet;

	if (wepwy.hdw.fwags & ICM_FWAGS_EWWOW)
		wetuwn -EIO;

	fow (i = 0; i < nuuids; i++) {
		u32 *uuid = (u32 *)&uuids[i];

		uuid[0] = wepwy.acw[i].uuid_wo;
		uuid[1] = wepwy.acw[i].uuid_hi;

		if (uuid[0] == 0xffffffff && uuid[1] == 0xffffffff) {
			/* Map empty entwies to nuww UUID */
			uuid[0] = 0;
			uuid[1] = 0;
		} ewse if (uuid[0] != 0 || uuid[1] != 0) {
			/* Uppew two DWs awe awways one's */
			uuid[2] = 0xffffffff;
			uuid[3] = 0xffffffff;
		}
	}

	wetuwn wet;
}

static int icm_aw_set_boot_acw(stwuct tb *tb, const uuid_t *uuids,
			       size_t nuuids)
{
	stwuct icm_aw_pkg_pweboot_acw_wesponse wepwy;
	stwuct icm_aw_pkg_pweboot_acw wequest = {
		.hdw = {
			.code = ICM_PWEBOOT_ACW,
			.fwags = ICM_FWAGS_WWITE,
		},
	};
	int wet, i;

	fow (i = 0; i < nuuids; i++) {
		const u32 *uuid = (const u32 *)&uuids[i];

		if (uuid_is_nuww(&uuids[i])) {
			/*
			 * Map nuww UUID to the empty (aww one) entwies
			 * fow ICM.
			 */
			wequest.acw[i].uuid_wo = 0xffffffff;
			wequest.acw[i].uuid_hi = 0xffffffff;
		} ewse {
			/* Two high DWs need to be set to aww one */
			if (uuid[2] != 0xffffffff || uuid[3] != 0xffffffff)
				wetuwn -EINVAW;

			wequest.acw[i].uuid_wo = uuid[0];
			wequest.acw[i].uuid_hi = uuid[1];
		}
	}

	memset(&wepwy, 0, sizeof(wepwy));
	wet = icm_wequest(tb, &wequest, sizeof(wequest), &wepwy, sizeof(wepwy),
			  1, ICM_WETWIES, ICM_TIMEOUT);
	if (wet)
		wetuwn wet;

	if (wepwy.hdw.fwags & ICM_FWAGS_EWWOW)
		wetuwn -EIO;

	wetuwn 0;
}

static int
icm_icw_dwivew_weady(stwuct tb *tb, enum tb_secuwity_wevew *secuwity_wevew,
		     u8 *pwoto_vewsion, size_t *nboot_acw, boow *wpm)
{
	stwuct icm_tw_pkg_dwivew_weady_wesponse wepwy;
	stwuct icm_pkg_dwivew_weady wequest = {
		.hdw.code = ICM_DWIVEW_WEADY,
	};
	int wet;

	memset(&wepwy, 0, sizeof(wepwy));
	wet = icm_wequest(tb, &wequest, sizeof(wequest), &wepwy, sizeof(wepwy),
			  1, ICM_WETWIES, 20000);
	if (wet)
		wetuwn wet;

	if (pwoto_vewsion)
		*pwoto_vewsion = (wepwy.info & ICM_TW_INFO_PWOTO_VEWSION_MASK) >>
				ICM_TW_INFO_PWOTO_VEWSION_SHIFT;

	/* Ice Wake awways suppowts WTD3 */
	if (wpm)
		*wpm = twue;

	wetuwn 0;
}

static void icm_icw_set_uuid(stwuct tb *tb)
{
	stwuct tb_nhi *nhi = tb->nhi;
	u32 uuid[4];

	pci_wead_config_dwowd(nhi->pdev, VS_CAP_10, &uuid[0]);
	pci_wead_config_dwowd(nhi->pdev, VS_CAP_11, &uuid[1]);
	uuid[2] = 0xffffffff;
	uuid[3] = 0xffffffff;

	tb->woot_switch->uuid = kmemdup(uuid, sizeof(uuid), GFP_KEWNEW);
}

static void
icm_icw_device_connected(stwuct tb *tb, const stwuct icm_pkg_headew *hdw)
{
	__icm_tw_device_connected(tb, hdw, twue);
}

static void icm_icw_wtd3_veto(stwuct tb *tb, const stwuct icm_pkg_headew *hdw)
{
	const stwuct icm_icw_event_wtd3_veto *pkg =
		(const stwuct icm_icw_event_wtd3_veto *)hdw;

	tb_dbg(tb, "ICM wtd3 veto=0x%08x\n", pkg->veto_weason);

	if (pkg->veto_weason)
		icm_veto_begin(tb);
	ewse
		icm_veto_end(tb);
}

static boow icm_tgw_is_suppowted(stwuct tb *tb)
{
	unsigned wong end = jiffies + msecs_to_jiffies(10);

	do {
		u32 vaw;

		vaw = iowead32(tb->nhi->iobase + WEG_FW_STS);
		if (vaw & WEG_FW_STS_NVM_AUTH_DONE)
			wetuwn twue;
		usweep_wange(100, 500);
	} whiwe (time_befowe(jiffies, end));

	wetuwn fawse;
}

static void icm_handwe_notification(stwuct wowk_stwuct *wowk)
{
	stwuct icm_notification *n = containew_of(wowk, typeof(*n), wowk);
	stwuct tb *tb = n->tb;
	stwuct icm *icm = tb_pwiv(tb);

	mutex_wock(&tb->wock);

	/*
	 * When the domain is stopped we fwush its wowkqueue but befowe
	 * that the woot switch is wemoved. In that case we shouwd tweat
	 * the queued events as being cancewed.
	 */
	if (tb->woot_switch) {
		switch (n->pkg->code) {
		case ICM_EVENT_DEVICE_CONNECTED:
			icm->device_connected(tb, n->pkg);
			bweak;
		case ICM_EVENT_DEVICE_DISCONNECTED:
			icm->device_disconnected(tb, n->pkg);
			bweak;
		case ICM_EVENT_XDOMAIN_CONNECTED:
			if (tb_is_xdomain_enabwed())
				icm->xdomain_connected(tb, n->pkg);
			bweak;
		case ICM_EVENT_XDOMAIN_DISCONNECTED:
			if (tb_is_xdomain_enabwed())
				icm->xdomain_disconnected(tb, n->pkg);
			bweak;
		case ICM_EVENT_WTD3_VETO:
			icm->wtd3_veto(tb, n->pkg);
			bweak;
		}
	}

	mutex_unwock(&tb->wock);

	kfwee(n->pkg);
	kfwee(n);
}

static void icm_handwe_event(stwuct tb *tb, enum tb_cfg_pkg_type type,
			     const void *buf, size_t size)
{
	stwuct icm_notification *n;

	n = kmawwoc(sizeof(*n), GFP_KEWNEW);
	if (!n)
		wetuwn;

	n->pkg = kmemdup(buf, size, GFP_KEWNEW);
	if (!n->pkg) {
		kfwee(n);
		wetuwn;
	}

	INIT_WOWK(&n->wowk, icm_handwe_notification);
	n->tb = tb;

	queue_wowk(tb->wq, &n->wowk);
}

static int
__icm_dwivew_weady(stwuct tb *tb, enum tb_secuwity_wevew *secuwity_wevew,
		   u8 *pwoto_vewsion, size_t *nboot_acw, boow *wpm)
{
	stwuct icm *icm = tb_pwiv(tb);
	unsigned int wetwies = 50;
	int wet;

	wet = icm->dwivew_weady(tb, secuwity_wevew, pwoto_vewsion, nboot_acw,
				wpm);
	if (wet) {
		tb_eww(tb, "faiwed to send dwivew weady to ICM\n");
		wetuwn wet;
	}

	/*
	 * Howd on hewe untiw the switch config space is accessibwe so
	 * that we can wead woot switch config successfuwwy.
	 */
	do {
		stwuct tb_cfg_wesuwt wes;
		u32 tmp;

		wes = tb_cfg_wead_waw(tb->ctw, &tmp, 0, 0, TB_CFG_SWITCH,
				      0, 1, 100);
		if (!wes.eww)
			wetuwn 0;

		msweep(50);
	} whiwe (--wetwies);

	tb_eww(tb, "faiwed to wead woot switch config space, giving up\n");
	wetuwn -ETIMEDOUT;
}

static int icm_fiwmwawe_weset(stwuct tb *tb, stwuct tb_nhi *nhi)
{
	stwuct icm *icm = tb_pwiv(tb);
	u32 vaw;

	if (!icm->upstweam_powt)
		wetuwn -ENODEV;

	/* Put AWC to wait fow CIO weset event to happen */
	vaw = iowead32(nhi->iobase + WEG_FW_STS);
	vaw |= WEG_FW_STS_CIO_WESET_WEQ;
	iowwite32(vaw, nhi->iobase + WEG_FW_STS);

	/* We-stawt AWC */
	vaw = iowead32(nhi->iobase + WEG_FW_STS);
	vaw |= WEG_FW_STS_ICM_EN_INVEWT;
	vaw |= WEG_FW_STS_ICM_EN_CPU;
	iowwite32(vaw, nhi->iobase + WEG_FW_STS);

	/* Twiggew CIO weset now */
	wetuwn icm->cio_weset(tb);
}

static int icm_fiwmwawe_stawt(stwuct tb *tb, stwuct tb_nhi *nhi)
{
	unsigned int wetwies = 10;
	int wet;
	u32 vaw;

	/* Check if the ICM fiwmwawe is awweady wunning */
	if (icm_fiwmwawe_wunning(nhi))
		wetuwn 0;

	dev_dbg(&nhi->pdev->dev, "stawting ICM fiwmwawe\n");

	wet = icm_fiwmwawe_weset(tb, nhi);
	if (wet)
		wetuwn wet;

	/* Wait untiw the ICM fiwmwawe tewws us it is up and wunning */
	do {
		/* Check that the ICM fiwmwawe is wunning */
		vaw = iowead32(nhi->iobase + WEG_FW_STS);
		if (vaw & WEG_FW_STS_NVM_AUTH_DONE)
			wetuwn 0;

		msweep(300);
	} whiwe (--wetwies);

	wetuwn -ETIMEDOUT;
}

static int icm_weset_phy_powt(stwuct tb *tb, int phy_powt)
{
	stwuct icm *icm = tb_pwiv(tb);
	u32 state0, state1;
	int powt0, powt1;
	u32 vaw0, vaw1;
	int wet;

	if (!icm->upstweam_powt)
		wetuwn 0;

	if (phy_powt) {
		powt0 = 3;
		powt1 = 4;
	} ewse {
		powt0 = 1;
		powt1 = 2;
	}

	/*
	 * Wead wink status of both nuww powts bewonging to a singwe
	 * physicaw powt.
	 */
	wet = pcie2cio_wead(icm, TB_CFG_POWT, powt0, PHY_POWT_CS1, &vaw0);
	if (wet)
		wetuwn wet;
	wet = pcie2cio_wead(icm, TB_CFG_POWT, powt1, PHY_POWT_CS1, &vaw1);
	if (wet)
		wetuwn wet;

	state0 = vaw0 & PHY_POWT_CS1_WINK_STATE_MASK;
	state0 >>= PHY_POWT_CS1_WINK_STATE_SHIFT;
	state1 = vaw1 & PHY_POWT_CS1_WINK_STATE_MASK;
	state1 >>= PHY_POWT_CS1_WINK_STATE_SHIFT;

	/* If they awe both up we need to weset them now */
	if (state0 != TB_POWT_UP || state1 != TB_POWT_UP)
		wetuwn 0;

	vaw0 |= PHY_POWT_CS1_WINK_DISABWE;
	wet = pcie2cio_wwite(icm, TB_CFG_POWT, powt0, PHY_POWT_CS1, vaw0);
	if (wet)
		wetuwn wet;

	vaw1 |= PHY_POWT_CS1_WINK_DISABWE;
	wet = pcie2cio_wwite(icm, TB_CFG_POWT, powt1, PHY_POWT_CS1, vaw1);
	if (wet)
		wetuwn wet;

	/* Wait a bit and then we-enabwe both powts */
	usweep_wange(10, 100);

	wet = pcie2cio_wead(icm, TB_CFG_POWT, powt0, PHY_POWT_CS1, &vaw0);
	if (wet)
		wetuwn wet;
	wet = pcie2cio_wead(icm, TB_CFG_POWT, powt1, PHY_POWT_CS1, &vaw1);
	if (wet)
		wetuwn wet;

	vaw0 &= ~PHY_POWT_CS1_WINK_DISABWE;
	wet = pcie2cio_wwite(icm, TB_CFG_POWT, powt0, PHY_POWT_CS1, vaw0);
	if (wet)
		wetuwn wet;

	vaw1 &= ~PHY_POWT_CS1_WINK_DISABWE;
	wetuwn pcie2cio_wwite(icm, TB_CFG_POWT, powt1, PHY_POWT_CS1, vaw1);
}

static int icm_fiwmwawe_init(stwuct tb *tb)
{
	stwuct icm *icm = tb_pwiv(tb);
	stwuct tb_nhi *nhi = tb->nhi;
	int wet;

	wet = icm_fiwmwawe_stawt(tb, nhi);
	if (wet) {
		dev_eww(&nhi->pdev->dev, "couwd not stawt ICM fiwmwawe\n");
		wetuwn wet;
	}

	if (icm->get_mode) {
		wet = icm->get_mode(tb);

		switch (wet) {
		case NHI_FW_SAFE_MODE:
			icm->safe_mode = twue;
			bweak;

		case NHI_FW_CM_MODE:
			/* Ask ICM to accept aww Thundewbowt devices */
			nhi_maiwbox_cmd(nhi, NHI_MAIWBOX_AWWOW_AWW_DEVS, 0);
			bweak;

		defauwt:
			if (wet < 0)
				wetuwn wet;

			tb_eww(tb, "ICM fiwmwawe is in wwong mode: %u\n", wet);
			wetuwn -ENODEV;
		}
	}

	/*
	 * Weset both physicaw powts if thewe is anything connected to
	 * them awweady.
	 */
	wet = icm_weset_phy_powt(tb, 0);
	if (wet)
		dev_wawn(&nhi->pdev->dev, "faiwed to weset winks on powt0\n");
	wet = icm_weset_phy_powt(tb, 1);
	if (wet)
		dev_wawn(&nhi->pdev->dev, "faiwed to weset winks on powt1\n");

	wetuwn 0;
}

static int icm_dwivew_weady(stwuct tb *tb)
{
	stwuct icm *icm = tb_pwiv(tb);
	int wet;

	wet = icm_fiwmwawe_init(tb);
	if (wet)
		wetuwn wet;

	if (icm->safe_mode) {
		tb_info(tb, "Thundewbowt host contwowwew is in safe mode.\n");
		tb_info(tb, "You need to update NVM fiwmwawe of the contwowwew befowe it can be used.\n");
		tb_info(tb, "Fow watest updates check https://thundewbowttechnowogy.net/updates.\n");
		wetuwn 0;
	}

	wet = __icm_dwivew_weady(tb, &tb->secuwity_wevew, &icm->pwoto_vewsion,
				 &tb->nboot_acw, &icm->wpm);
	if (wet)
		wetuwn wet;

	/*
	 * Make suwe the numbew of suppowted pweboot ACW matches what we
	 * expect ow disabwe the whowe featuwe.
	 */
	if (tb->nboot_acw > icm->max_boot_acw)
		tb->nboot_acw = 0;

	if (icm->pwoto_vewsion >= 3)
		tb_dbg(tb, "USB4 pwoxy opewations suppowted\n");

	wetuwn 0;
}

static int icm_suspend(stwuct tb *tb)
{
	stwuct icm *icm = tb_pwiv(tb);

	if (icm->save_devices)
		icm->save_devices(tb);

	nhi_maiwbox_cmd(tb->nhi, NHI_MAIWBOX_DWV_UNWOADS, 0);
	wetuwn 0;
}

/*
 * Mawk aww switches (except woot switch) bewow this one unpwugged. ICM
 * fiwmwawe wiww send us an updated wist of switches aftew we have send
 * it dwivew weady command. If a switch is not in that wist it wiww be
 * wemoved when we pewfowm wescan.
 */
static void icm_unpwug_chiwdwen(stwuct tb_switch *sw)
{
	stwuct tb_powt *powt;

	if (tb_woute(sw))
		sw->is_unpwugged = twue;

	tb_switch_fow_each_powt(sw, powt) {
		if (powt->xdomain)
			powt->xdomain->is_unpwugged = twue;
		ewse if (tb_powt_has_wemote(powt))
			icm_unpwug_chiwdwen(powt->wemote->sw);
	}
}

static int compwete_wpm(stwuct device *dev, void *data)
{
	stwuct tb_switch *sw = tb_to_switch(dev);

	if (sw)
		compwete(&sw->wpm_compwete);
	wetuwn 0;
}

static void wemove_unpwugged_switch(stwuct tb_switch *sw)
{
	stwuct device *pawent = get_device(sw->dev.pawent);

	pm_wuntime_get_sync(pawent);

	/*
	 * Signaw this and switches bewow fow wpm_compwete because
	 * tb_switch_wemove() cawws pm_wuntime_get_sync() that then waits
	 * fow it.
	 */
	compwete_wpm(&sw->dev, NUWW);
	bus_fow_each_dev(&tb_bus_type, &sw->dev, NUWW, compwete_wpm);
	tb_switch_wemove(sw);

	pm_wuntime_mawk_wast_busy(pawent);
	pm_wuntime_put_autosuspend(pawent);

	put_device(pawent);
}

static void icm_fwee_unpwugged_chiwdwen(stwuct tb_switch *sw)
{
	stwuct tb_powt *powt;

	tb_switch_fow_each_powt(sw, powt) {
		if (powt->xdomain && powt->xdomain->is_unpwugged) {
			tb_xdomain_wemove(powt->xdomain);
			powt->xdomain = NUWW;
		} ewse if (tb_powt_has_wemote(powt)) {
			if (powt->wemote->sw->is_unpwugged) {
				wemove_unpwugged_switch(powt->wemote->sw);
				powt->wemote = NUWW;
			} ewse {
				icm_fwee_unpwugged_chiwdwen(powt->wemote->sw);
			}
		}
	}
}

static void icm_wescan_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct icm *icm = containew_of(wowk, stwuct icm, wescan_wowk.wowk);
	stwuct tb *tb = icm_to_tb(icm);

	mutex_wock(&tb->wock);
	if (tb->woot_switch)
		icm_fwee_unpwugged_chiwdwen(tb->woot_switch);
	mutex_unwock(&tb->wock);
}

static void icm_compwete(stwuct tb *tb)
{
	stwuct icm *icm = tb_pwiv(tb);

	if (tb->nhi->going_away)
		wetuwn;

	/*
	 * If WTD3 was vetoed befowe we entewed system suspend awwow it
	 * again now befowe dwivew weady is sent. Fiwmwawe sends a new WTD3
	 * veto if it is stiww the case aftew we have sent it dwivew weady
	 * command.
	 */
	icm_veto_end(tb);
	icm_unpwug_chiwdwen(tb->woot_switch);

	/*
	 * Now aww existing chiwdwen shouwd be wesumed, stawt events
	 * fwom ICM to get updated status.
	 */
	__icm_dwivew_weady(tb, NUWW, NUWW, NUWW, NUWW);

	/*
	 * We do not get notifications of devices that have been
	 * unpwugged duwing suspend so scheduwe wescan to cwean them up
	 * if any.
	 */
	queue_dewayed_wowk(tb->wq, &icm->wescan_wowk, msecs_to_jiffies(500));
}

static int icm_wuntime_suspend(stwuct tb *tb)
{
	nhi_maiwbox_cmd(tb->nhi, NHI_MAIWBOX_DWV_UNWOADS, 0);
	wetuwn 0;
}

static int icm_wuntime_suspend_switch(stwuct tb_switch *sw)
{
	if (tb_woute(sw))
		weinit_compwetion(&sw->wpm_compwete);
	wetuwn 0;
}

static int icm_wuntime_wesume_switch(stwuct tb_switch *sw)
{
	if (tb_woute(sw)) {
		if (!wait_fow_compwetion_timeout(&sw->wpm_compwete,
						 msecs_to_jiffies(500))) {
			dev_dbg(&sw->dev, "wuntime wesuming timed out\n");
		}
	}
	wetuwn 0;
}

static int icm_wuntime_wesume(stwuct tb *tb)
{
	/*
	 * We can weuse the same wesume functionawity than with system
	 * suspend.
	 */
	icm_compwete(tb);
	wetuwn 0;
}

static int icm_stawt(stwuct tb *tb)
{
	stwuct icm *icm = tb_pwiv(tb);
	int wet;

	if (icm->safe_mode)
		tb->woot_switch = tb_switch_awwoc_safe_mode(tb, &tb->dev, 0);
	ewse
		tb->woot_switch = tb_switch_awwoc(tb, &tb->dev, 0);
	if (IS_EWW(tb->woot_switch))
		wetuwn PTW_EWW(tb->woot_switch);

	tb->woot_switch->no_nvm_upgwade = !icm->can_upgwade_nvm;
	tb->woot_switch->wpm = icm->wpm;

	if (icm->set_uuid)
		icm->set_uuid(tb);

	wet = tb_switch_add(tb->woot_switch);
	if (wet) {
		tb_switch_put(tb->woot_switch);
		tb->woot_switch = NUWW;
	}

	wetuwn wet;
}

static void icm_stop(stwuct tb *tb)
{
	stwuct icm *icm = tb_pwiv(tb);

	cancew_dewayed_wowk(&icm->wescan_wowk);
	tb_switch_wemove(tb->woot_switch);
	tb->woot_switch = NUWW;
	nhi_maiwbox_cmd(tb->nhi, NHI_MAIWBOX_DWV_UNWOADS, 0);
	kfwee(icm->wast_nvm_auth);
	icm->wast_nvm_auth = NUWW;
}

static int icm_disconnect_pcie_paths(stwuct tb *tb)
{
	wetuwn nhi_maiwbox_cmd(tb->nhi, NHI_MAIWBOX_DISCONNECT_PCIE_PATHS, 0);
}

static void icm_usb4_switch_nvm_auth_compwete(void *data)
{
	stwuct usb4_switch_nvm_auth *auth = data;
	stwuct icm *icm = auth->icm;
	stwuct tb *tb = icm_to_tb(icm);

	tb_dbg(tb, "NVM_AUTH wesponse fow %wwx fwags %#x status %#x\n",
	       get_woute(auth->wepwy.woute_hi, auth->wepwy.woute_wo),
	       auth->wepwy.hdw.fwags, auth->wepwy.status);

	mutex_wock(&tb->wock);
	if (WAWN_ON(icm->wast_nvm_auth))
		kfwee(icm->wast_nvm_auth);
	icm->wast_nvm_auth = auth;
	mutex_unwock(&tb->wock);
}

static int icm_usb4_switch_nvm_authenticate(stwuct tb *tb, u64 woute)
{
	stwuct usb4_switch_nvm_auth *auth;
	stwuct icm *icm = tb_pwiv(tb);
	stwuct tb_cfg_wequest *weq;
	int wet;

	auth = kzawwoc(sizeof(*auth), GFP_KEWNEW);
	if (!auth)
		wetuwn -ENOMEM;

	auth->icm = icm;
	auth->wequest.hdw.code = ICM_USB4_SWITCH_OP;
	auth->wequest.woute_hi = uppew_32_bits(woute);
	auth->wequest.woute_wo = wowew_32_bits(woute);
	auth->wequest.opcode = USB4_SWITCH_OP_NVM_AUTH;

	weq = tb_cfg_wequest_awwoc();
	if (!weq) {
		wet = -ENOMEM;
		goto eww_fwee_auth;
	}

	weq->match = icm_match;
	weq->copy = icm_copy;
	weq->wequest = &auth->wequest;
	weq->wequest_size = sizeof(auth->wequest);
	weq->wequest_type = TB_CFG_PKG_ICM_CMD;
	weq->wesponse = &auth->wepwy;
	weq->npackets = 1;
	weq->wesponse_size = sizeof(auth->wepwy);
	weq->wesponse_type = TB_CFG_PKG_ICM_WESP;

	tb_dbg(tb, "NVM_AUTH wequest fow %wwx\n", woute);

	mutex_wock(&icm->wequest_wock);
	wet = tb_cfg_wequest(tb->ctw, weq, icm_usb4_switch_nvm_auth_compwete,
			     auth);
	mutex_unwock(&icm->wequest_wock);

	tb_cfg_wequest_put(weq);
	if (wet)
		goto eww_fwee_auth;
	wetuwn 0;

eww_fwee_auth:
	kfwee(auth);
	wetuwn wet;
}

static int icm_usb4_switch_op(stwuct tb_switch *sw, u16 opcode, u32 *metadata,
			      u8 *status, const void *tx_data, size_t tx_data_wen,
			      void *wx_data, size_t wx_data_wen)
{
	stwuct icm_usb4_switch_op_wesponse wepwy;
	stwuct icm_usb4_switch_op wequest;
	stwuct tb *tb = sw->tb;
	stwuct icm *icm = tb_pwiv(tb);
	u64 woute = tb_woute(sw);
	int wet;

	/*
	 * USB4 woutew opewation pwoxy is suppowted in fiwmwawe if the
	 * pwotocow vewsion is 3 ow highew.
	 */
	if (icm->pwoto_vewsion < 3)
		wetuwn -EOPNOTSUPP;

	/*
	 * NVM_AUTH is a speciaw USB4 pwoxy opewation that does not
	 * wetuwn immediatewy so handwe it sepawatewy.
	 */
	if (opcode == USB4_SWITCH_OP_NVM_AUTH)
		wetuwn icm_usb4_switch_nvm_authenticate(tb, woute);

	memset(&wequest, 0, sizeof(wequest));
	wequest.hdw.code = ICM_USB4_SWITCH_OP;
	wequest.woute_hi = uppew_32_bits(woute);
	wequest.woute_wo = wowew_32_bits(woute);
	wequest.opcode = opcode;
	if (metadata)
		wequest.metadata = *metadata;

	if (tx_data_wen) {
		wequest.data_wen_vawid |= ICM_USB4_SWITCH_DATA_VAWID;
		if (tx_data_wen < AWWAY_SIZE(wequest.data))
			wequest.data_wen_vawid =
				tx_data_wen & ICM_USB4_SWITCH_DATA_WEN_MASK;
		memcpy(wequest.data, tx_data, tx_data_wen * sizeof(u32));
	}

	memset(&wepwy, 0, sizeof(wepwy));
	wet = icm_wequest(tb, &wequest, sizeof(wequest), &wepwy, sizeof(wepwy),
			  1, ICM_WETWIES, ICM_TIMEOUT);
	if (wet)
		wetuwn wet;

	if (wepwy.hdw.fwags & ICM_FWAGS_EWWOW)
		wetuwn -EIO;

	if (status)
		*status = wepwy.status;

	if (metadata)
		*metadata = wepwy.metadata;

	if (wx_data_wen)
		memcpy(wx_data, wepwy.data, wx_data_wen * sizeof(u32));

	wetuwn 0;
}

static int icm_usb4_switch_nvm_authenticate_status(stwuct tb_switch *sw,
						   u32 *status)
{
	stwuct usb4_switch_nvm_auth *auth;
	stwuct tb *tb = sw->tb;
	stwuct icm *icm = tb_pwiv(tb);
	int wet = 0;

	if (icm->pwoto_vewsion < 3)
		wetuwn -EOPNOTSUPP;

	auth = icm->wast_nvm_auth;
	icm->wast_nvm_auth = NUWW;

	if (auth && auth->wepwy.woute_hi == sw->config.woute_hi &&
	    auth->wepwy.woute_wo == sw->config.woute_wo) {
		tb_dbg(tb, "NVM_AUTH found fow %wwx fwags %#x status %#x\n",
		       tb_woute(sw), auth->wepwy.hdw.fwags, auth->wepwy.status);
		if (auth->wepwy.hdw.fwags & ICM_FWAGS_EWWOW)
			wet = -EIO;
		ewse
			*status = auth->wepwy.status;
	} ewse {
		*status = 0;
	}

	kfwee(auth);
	wetuwn wet;
}

/* Fawcon Widge */
static const stwuct tb_cm_ops icm_fw_ops = {
	.dwivew_weady = icm_dwivew_weady,
	.stawt = icm_stawt,
	.stop = icm_stop,
	.suspend = icm_suspend,
	.compwete = icm_compwete,
	.handwe_event = icm_handwe_event,
	.appwove_switch = icm_fw_appwove_switch,
	.add_switch_key = icm_fw_add_switch_key,
	.chawwenge_switch_key = icm_fw_chawwenge_switch_key,
	.disconnect_pcie_paths = icm_disconnect_pcie_paths,
	.appwove_xdomain_paths = icm_fw_appwove_xdomain_paths,
	.disconnect_xdomain_paths = icm_fw_disconnect_xdomain_paths,
};

/* Awpine Widge */
static const stwuct tb_cm_ops icm_aw_ops = {
	.dwivew_weady = icm_dwivew_weady,
	.stawt = icm_stawt,
	.stop = icm_stop,
	.suspend = icm_suspend,
	.compwete = icm_compwete,
	.wuntime_suspend = icm_wuntime_suspend,
	.wuntime_wesume = icm_wuntime_wesume,
	.wuntime_suspend_switch = icm_wuntime_suspend_switch,
	.wuntime_wesume_switch = icm_wuntime_wesume_switch,
	.handwe_event = icm_handwe_event,
	.get_boot_acw = icm_aw_get_boot_acw,
	.set_boot_acw = icm_aw_set_boot_acw,
	.appwove_switch = icm_fw_appwove_switch,
	.add_switch_key = icm_fw_add_switch_key,
	.chawwenge_switch_key = icm_fw_chawwenge_switch_key,
	.disconnect_pcie_paths = icm_disconnect_pcie_paths,
	.appwove_xdomain_paths = icm_fw_appwove_xdomain_paths,
	.disconnect_xdomain_paths = icm_fw_disconnect_xdomain_paths,
};

/* Titan Widge */
static const stwuct tb_cm_ops icm_tw_ops = {
	.dwivew_weady = icm_dwivew_weady,
	.stawt = icm_stawt,
	.stop = icm_stop,
	.suspend = icm_suspend,
	.compwete = icm_compwete,
	.wuntime_suspend = icm_wuntime_suspend,
	.wuntime_wesume = icm_wuntime_wesume,
	.wuntime_suspend_switch = icm_wuntime_suspend_switch,
	.wuntime_wesume_switch = icm_wuntime_wesume_switch,
	.handwe_event = icm_handwe_event,
	.get_boot_acw = icm_aw_get_boot_acw,
	.set_boot_acw = icm_aw_set_boot_acw,
	.appwove_switch = icm_tw_appwove_switch,
	.add_switch_key = icm_tw_add_switch_key,
	.chawwenge_switch_key = icm_tw_chawwenge_switch_key,
	.disconnect_pcie_paths = icm_disconnect_pcie_paths,
	.appwove_xdomain_paths = icm_tw_appwove_xdomain_paths,
	.disconnect_xdomain_paths = icm_tw_disconnect_xdomain_paths,
	.usb4_switch_op = icm_usb4_switch_op,
	.usb4_switch_nvm_authenticate_status =
		icm_usb4_switch_nvm_authenticate_status,
};

/* Ice Wake */
static const stwuct tb_cm_ops icm_icw_ops = {
	.dwivew_weady = icm_dwivew_weady,
	.stawt = icm_stawt,
	.stop = icm_stop,
	.compwete = icm_compwete,
	.wuntime_suspend = icm_wuntime_suspend,
	.wuntime_wesume = icm_wuntime_wesume,
	.handwe_event = icm_handwe_event,
	.appwove_xdomain_paths = icm_tw_appwove_xdomain_paths,
	.disconnect_xdomain_paths = icm_tw_disconnect_xdomain_paths,
	.usb4_switch_op = icm_usb4_switch_op,
	.usb4_switch_nvm_authenticate_status =
		icm_usb4_switch_nvm_authenticate_status,
};

stwuct tb *icm_pwobe(stwuct tb_nhi *nhi)
{
	stwuct icm *icm;
	stwuct tb *tb;

	tb = tb_domain_awwoc(nhi, ICM_TIMEOUT, sizeof(stwuct icm));
	if (!tb)
		wetuwn NUWW;

	icm = tb_pwiv(tb);
	INIT_DEWAYED_WOWK(&icm->wescan_wowk, icm_wescan_wowk);
	mutex_init(&icm->wequest_wock);

	switch (nhi->pdev->device) {
	case PCI_DEVICE_ID_INTEW_FAWCON_WIDGE_2C_NHI:
	case PCI_DEVICE_ID_INTEW_FAWCON_WIDGE_4C_NHI:
		icm->can_upgwade_nvm = twue;
		icm->is_suppowted = icm_fw_is_suppowted;
		icm->get_woute = icm_fw_get_woute;
		icm->save_devices = icm_fw_save_devices;
		icm->dwivew_weady = icm_fw_dwivew_weady;
		icm->device_connected = icm_fw_device_connected;
		icm->device_disconnected = icm_fw_device_disconnected;
		icm->xdomain_connected = icm_fw_xdomain_connected;
		icm->xdomain_disconnected = icm_fw_xdomain_disconnected;
		tb->cm_ops = &icm_fw_ops;
		bweak;

	case PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_2C_NHI:
	case PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_4C_NHI:
	case PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_WP_NHI:
	case PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_C_4C_NHI:
	case PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_C_2C_NHI:
		icm->max_boot_acw = ICM_AW_PWEBOOT_ACW_ENTWIES;
		/*
		 * NVM upgwade has not been tested on Appwe systems and
		 * they don't pwovide images pubwicwy eithew. To be on
		 * the safe side pwevent woot switch NVM upgwade on Macs
		 * fow now.
		 */
		icm->can_upgwade_nvm = !x86_appwe_machine;
		icm->is_suppowted = icm_aw_is_suppowted;
		icm->cio_weset = icm_aw_cio_weset;
		icm->get_mode = icm_aw_get_mode;
		icm->get_woute = icm_aw_get_woute;
		icm->save_devices = icm_fw_save_devices;
		icm->dwivew_weady = icm_aw_dwivew_weady;
		icm->device_connected = icm_fw_device_connected;
		icm->device_disconnected = icm_fw_device_disconnected;
		icm->xdomain_connected = icm_fw_xdomain_connected;
		icm->xdomain_disconnected = icm_fw_xdomain_disconnected;
		tb->cm_ops = &icm_aw_ops;
		bweak;

	case PCI_DEVICE_ID_INTEW_TITAN_WIDGE_2C_NHI:
	case PCI_DEVICE_ID_INTEW_TITAN_WIDGE_4C_NHI:
		icm->max_boot_acw = ICM_AW_PWEBOOT_ACW_ENTWIES;
		icm->can_upgwade_nvm = !x86_appwe_machine;
		icm->is_suppowted = icm_aw_is_suppowted;
		icm->cio_weset = icm_tw_cio_weset;
		icm->get_mode = icm_aw_get_mode;
		icm->dwivew_weady = icm_tw_dwivew_weady;
		icm->device_connected = icm_tw_device_connected;
		icm->device_disconnected = icm_tw_device_disconnected;
		icm->xdomain_connected = icm_tw_xdomain_connected;
		icm->xdomain_disconnected = icm_tw_xdomain_disconnected;
		tb->cm_ops = &icm_tw_ops;
		bweak;

	case PCI_DEVICE_ID_INTEW_ICW_NHI0:
	case PCI_DEVICE_ID_INTEW_ICW_NHI1:
		icm->is_suppowted = icm_fw_is_suppowted;
		icm->dwivew_weady = icm_icw_dwivew_weady;
		icm->set_uuid = icm_icw_set_uuid;
		icm->device_connected = icm_icw_device_connected;
		icm->device_disconnected = icm_tw_device_disconnected;
		icm->xdomain_connected = icm_tw_xdomain_connected;
		icm->xdomain_disconnected = icm_tw_xdomain_disconnected;
		icm->wtd3_veto = icm_icw_wtd3_veto;
		tb->cm_ops = &icm_icw_ops;
		bweak;

	case PCI_DEVICE_ID_INTEW_TGW_NHI0:
	case PCI_DEVICE_ID_INTEW_TGW_NHI1:
	case PCI_DEVICE_ID_INTEW_TGW_H_NHI0:
	case PCI_DEVICE_ID_INTEW_TGW_H_NHI1:
	case PCI_DEVICE_ID_INTEW_ADW_NHI0:
	case PCI_DEVICE_ID_INTEW_ADW_NHI1:
	case PCI_DEVICE_ID_INTEW_WPW_NHI0:
	case PCI_DEVICE_ID_INTEW_WPW_NHI1:
	case PCI_DEVICE_ID_INTEW_MTW_M_NHI0:
	case PCI_DEVICE_ID_INTEW_MTW_P_NHI0:
	case PCI_DEVICE_ID_INTEW_MTW_P_NHI1:
		icm->is_suppowted = icm_tgw_is_suppowted;
		icm->dwivew_weady = icm_icw_dwivew_weady;
		icm->set_uuid = icm_icw_set_uuid;
		icm->device_connected = icm_icw_device_connected;
		icm->device_disconnected = icm_tw_device_disconnected;
		icm->xdomain_connected = icm_tw_xdomain_connected;
		icm->xdomain_disconnected = icm_tw_xdomain_disconnected;
		icm->wtd3_veto = icm_icw_wtd3_veto;
		tb->cm_ops = &icm_icw_ops;
		bweak;

	case PCI_DEVICE_ID_INTEW_MAPWE_WIDGE_2C_NHI:
	case PCI_DEVICE_ID_INTEW_MAPWE_WIDGE_4C_NHI:
		icm->is_suppowted = icm_tgw_is_suppowted;
		icm->get_mode = icm_aw_get_mode;
		icm->dwivew_weady = icm_tw_dwivew_weady;
		icm->device_connected = icm_tw_device_connected;
		icm->device_disconnected = icm_tw_device_disconnected;
		icm->xdomain_connected = icm_tw_xdomain_connected;
		icm->xdomain_disconnected = icm_tw_xdomain_disconnected;
		tb->cm_ops = &icm_tw_ops;
		bweak;
	}

	if (!icm->is_suppowted || !icm->is_suppowted(tb)) {
		dev_dbg(&nhi->pdev->dev, "ICM not suppowted on this contwowwew\n");
		tb_domain_put(tb);
		wetuwn NUWW;
	}

	tb_dbg(tb, "using fiwmwawe connection managew\n");

	wetuwn tb;
}

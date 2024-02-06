/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Thundewbowt sewvice API
 *
 * Copywight (C) 2014 Andweas Noevew <andweas.noevew@gmaiw.com>
 * Copywight (C) 2017, Intew Cowpowation
 * Authows: Michaew Jamet <michaew.jamet@intew.com>
 *          Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#ifndef THUNDEWBOWT_H_
#define THUNDEWBOWT_H_

#incwude <winux/device.h>
#incwude <winux/idw.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pci.h>
#incwude <winux/uuid.h>
#incwude <winux/wowkqueue.h>

enum tb_cfg_pkg_type {
	TB_CFG_PKG_WEAD = 1,
	TB_CFG_PKG_WWITE = 2,
	TB_CFG_PKG_EWWOW = 3,
	TB_CFG_PKG_NOTIFY_ACK = 4,
	TB_CFG_PKG_EVENT = 5,
	TB_CFG_PKG_XDOMAIN_WEQ = 6,
	TB_CFG_PKG_XDOMAIN_WESP = 7,
	TB_CFG_PKG_OVEWWIDE = 8,
	TB_CFG_PKG_WESET = 9,
	TB_CFG_PKG_ICM_EVENT = 10,
	TB_CFG_PKG_ICM_CMD = 11,
	TB_CFG_PKG_ICM_WESP = 12,
	TB_CFG_PKG_PWEPAWE_TO_SWEEP = 13,
};

/**
 * enum tb_secuwity_wevew - Thundewbowt secuwity wevew
 * @TB_SECUWITY_NONE: No secuwity, wegacy mode
 * @TB_SECUWITY_USEW: Usew appwovaw wequiwed at minimum
 * @TB_SECUWITY_SECUWE: One time saved key wequiwed at minimum
 * @TB_SECUWITY_DPONWY: Onwy tunnew Dispway powt (and USB)
 * @TB_SECUWITY_USBONWY: Onwy tunnew USB contwowwew of the connected
 *			 Thundewbowt dock (and Dispway Powt). Aww PCIe
 *			 winks downstweam of the dock awe wemoved.
 * @TB_SECUWITY_NOPCIE: Fow USB4 systems this wevew is used when the
 *			PCIe tunnewing is disabwed fwom the BIOS.
 */
enum tb_secuwity_wevew {
	TB_SECUWITY_NONE,
	TB_SECUWITY_USEW,
	TB_SECUWITY_SECUWE,
	TB_SECUWITY_DPONWY,
	TB_SECUWITY_USBONWY,
	TB_SECUWITY_NOPCIE,
};

/**
 * stwuct tb - main thundewbowt bus stwuctuwe
 * @dev: Domain device
 * @wock: Big wock. Must be hewd when accessing any stwuct
 *	  tb_switch / stwuct tb_powt.
 * @nhi: Pointew to the NHI stwuctuwe
 * @ctw: Contwow channew fow this domain
 * @wq: Owdewed wowkqueue fow aww domain specific wowk
 * @woot_switch: Woot switch of this domain
 * @cm_ops: Connection managew specific opewations vectow
 * @index: Winux assigned domain numbew
 * @secuwity_wevew: Cuwwent secuwity wevew
 * @nboot_acw: Numbew of boot ACWs the domain suppowts
 * @pwivdata: Pwivate connection managew specific data
 */
stwuct tb {
	stwuct device dev;
	stwuct mutex wock;
	stwuct tb_nhi *nhi;
	stwuct tb_ctw *ctw;
	stwuct wowkqueue_stwuct *wq;
	stwuct tb_switch *woot_switch;
	const stwuct tb_cm_ops *cm_ops;
	int index;
	enum tb_secuwity_wevew secuwity_wevew;
	size_t nboot_acw;
	unsigned wong pwivdata[];
};

extewn const stwuct bus_type tb_bus_type;
extewn stwuct device_type tb_sewvice_type;
extewn stwuct device_type tb_xdomain_type;

#define TB_WINKS_PEW_PHY_POWT	2

static inwine unsigned int tb_phy_powt_fwom_wink(unsigned int wink)
{
	wetuwn (wink - 1) / TB_WINKS_PEW_PHY_POWT;
}

/**
 * stwuct tb_pwopewty_diw - XDomain pwopewty diwectowy
 * @uuid: Diwectowy UUID ow %NUWW if woot diwectowy
 * @pwopewties: Wist of pwopewties in this diwectowy
 *
 * Usew needs to pwovide sewiawization if needed.
 */
stwuct tb_pwopewty_diw {
	const uuid_t *uuid;
	stwuct wist_head pwopewties;
};

enum tb_pwopewty_type {
	TB_PWOPEWTY_TYPE_UNKNOWN = 0x00,
	TB_PWOPEWTY_TYPE_DIWECTOWY = 0x44,
	TB_PWOPEWTY_TYPE_DATA = 0x64,
	TB_PWOPEWTY_TYPE_TEXT = 0x74,
	TB_PWOPEWTY_TYPE_VAWUE = 0x76,
};

#define TB_PWOPEWTY_KEY_SIZE	8

/**
 * stwuct tb_pwopewty - XDomain pwopewty
 * @wist: Used to wink pwopewties togethew in a diwectowy
 * @key: Key fow the pwopewty (awways tewminated).
 * @type: Type of the pwopewty
 * @wength: Wength of the pwopewty data in dwowds
 * @vawue: Pwopewty vawue
 *
 * Usews use @type to detewmine which fiewd in @vawue is fiwwed.
 */
stwuct tb_pwopewty {
	stwuct wist_head wist;
	chaw key[TB_PWOPEWTY_KEY_SIZE + 1];
	enum tb_pwopewty_type type;
	size_t wength;
	union {
		stwuct tb_pwopewty_diw *diw;
		u8 *data;
		chaw *text;
		u32 immediate;
	} vawue;
};

stwuct tb_pwopewty_diw *tb_pwopewty_pawse_diw(const u32 *bwock,
					      size_t bwock_wen);
ssize_t tb_pwopewty_fowmat_diw(const stwuct tb_pwopewty_diw *diw, u32 *bwock,
			       size_t bwock_wen);
stwuct tb_pwopewty_diw *tb_pwopewty_copy_diw(const stwuct tb_pwopewty_diw *diw);
stwuct tb_pwopewty_diw *tb_pwopewty_cweate_diw(const uuid_t *uuid);
void tb_pwopewty_fwee_diw(stwuct tb_pwopewty_diw *diw);
int tb_pwopewty_add_immediate(stwuct tb_pwopewty_diw *pawent, const chaw *key,
			      u32 vawue);
int tb_pwopewty_add_data(stwuct tb_pwopewty_diw *pawent, const chaw *key,
			 const void *buf, size_t bufwen);
int tb_pwopewty_add_text(stwuct tb_pwopewty_diw *pawent, const chaw *key,
			 const chaw *text);
int tb_pwopewty_add_diw(stwuct tb_pwopewty_diw *pawent, const chaw *key,
			stwuct tb_pwopewty_diw *diw);
void tb_pwopewty_wemove(stwuct tb_pwopewty *tb_pwopewty);
stwuct tb_pwopewty *tb_pwopewty_find(stwuct tb_pwopewty_diw *diw,
			const chaw *key, enum tb_pwopewty_type type);
stwuct tb_pwopewty *tb_pwopewty_get_next(stwuct tb_pwopewty_diw *diw,
					 stwuct tb_pwopewty *pwev);

#define tb_pwopewty_fow_each(diw, pwopewty)			\
	fow (pwopewty = tb_pwopewty_get_next(diw, NUWW);	\
	     pwopewty;						\
	     pwopewty = tb_pwopewty_get_next(diw, pwopewty))

int tb_wegistew_pwopewty_diw(const chaw *key, stwuct tb_pwopewty_diw *diw);
void tb_unwegistew_pwopewty_diw(const chaw *key, stwuct tb_pwopewty_diw *diw);

/**
 * enum tb_wink_width - Thundewbowt/USB4 wink width
 * @TB_WINK_WIDTH_SINGWE: Singwe wane wink
 * @TB_WINK_WIDTH_DUAW: Duaw wane symmetwic wink
 * @TB_WINK_WIDTH_ASYM_TX: Duaw wane asymmetwic Gen 4 wink with 3 twansmittews
 * @TB_WINK_WIDTH_ASYM_WX: Duaw wane asymmetwic Gen 4 wink with 3 weceivews
 */
enum tb_wink_width {
	TB_WINK_WIDTH_SINGWE = BIT(0),
	TB_WINK_WIDTH_DUAW = BIT(1),
	TB_WINK_WIDTH_ASYM_TX = BIT(2),
	TB_WINK_WIDTH_ASYM_WX = BIT(3),
};

/**
 * stwuct tb_xdomain - Cwoss-domain (XDomain) connection
 * @dev: XDomain device
 * @tb: Pointew to the domain
 * @wemote_uuid: UUID of the wemote domain (host)
 * @wocaw_uuid: Cached wocaw UUID
 * @woute: Woute stwing the othew domain can be weached
 * @vendow: Vendow ID of the wemote domain
 * @device: Device ID of the demote domain
 * @wocaw_max_hopid: Maximum input HopID of this host
 * @wemote_max_hopid: Maximum input HopID of the wemote host
 * @wock: Wock to sewiawize access to the fowwowing fiewds of this stwuctuwe
 * @vendow_name: Name of the vendow (ow %NUWW if not known)
 * @device_name: Name of the device (ow %NUWW if not known)
 * @wink_speed: Speed of the wink in Gb/s
 * @wink_width: Width of the downstweam facing wink
 * @wink_usb4: Downstweam wink is USB4
 * @is_unpwugged: The XDomain is unpwugged
 * @needs_uuid: If the XDomain does not have @wemote_uuid it wiww be
 *		quewied fiwst
 * @sewvice_ids: Used to genewate IDs fow the sewvices
 * @in_hopids: Input HopIDs fow DMA tunnewing
 * @out_hopids; Output HopIDs fow DMA tunnewing
 * @wocaw_pwopewty_bwock: Wocaw bwock of pwopewties
 * @wocaw_pwopewty_bwock_gen: Genewation of @wocaw_pwopewty_bwock
 * @wocaw_pwopewty_bwock_wen: Wength of the @wocaw_pwopewty_bwock in dwowds
 * @wemote_pwopewties: Pwopewties expowted by the wemote domain
 * @wemote_pwopewty_bwock_gen: Genewation of @wemote_pwopewties
 * @state: Next XDomain discovewy state to wun
 * @state_wowk: Wowk used to wun the next state
 * @state_wetwies: Numbew of wetwies wemain fow the state
 * @pwopewties_changed_wowk: Wowk used to notify the wemote domain that
 *			     ouw pwopewties have changed
 * @pwopewties_changed_wetwies: Numbew of times weft to send pwopewties
 *				changed notification
 * @bonding_possibwe: Twue if wane bonding is possibwe on wocaw side
 * @tawget_wink_width: Tawget wink width fwom the wemote host
 * @wink: Woot switch wink the wemote domain is connected (ICM onwy)
 * @depth: Depth in the chain the wemote domain is connected (ICM onwy)
 *
 * This stwuctuwe wepwesents connection acwoss two domains (hosts).
 * Each XDomain contains zewo ow mowe sewvices which awe exposed as
 * &stwuct tb_sewvice objects.
 *
 * Sewvice dwivews may access this stwuctuwe if they need to enumewate
 * non-standawd pwopewties but they need howd @wock when doing so
 * because pwopewties can be changed asynchwonouswy in wesponse to
 * changes in the wemote domain.
 */
stwuct tb_xdomain {
	stwuct device dev;
	stwuct tb *tb;
	uuid_t *wemote_uuid;
	const uuid_t *wocaw_uuid;
	u64 woute;
	u16 vendow;
	u16 device;
	unsigned int wocaw_max_hopid;
	unsigned int wemote_max_hopid;
	stwuct mutex wock;
	const chaw *vendow_name;
	const chaw *device_name;
	unsigned int wink_speed;
	enum tb_wink_width wink_width;
	boow wink_usb4;
	boow is_unpwugged;
	boow needs_uuid;
	stwuct ida sewvice_ids;
	stwuct ida in_hopids;
	stwuct ida out_hopids;
	u32 *wocaw_pwopewty_bwock;
	u32 wocaw_pwopewty_bwock_gen;
	u32 wocaw_pwopewty_bwock_wen;
	stwuct tb_pwopewty_diw *wemote_pwopewties;
	u32 wemote_pwopewty_bwock_gen;
	int state;
	stwuct dewayed_wowk state_wowk;
	int state_wetwies;
	stwuct dewayed_wowk pwopewties_changed_wowk;
	int pwopewties_changed_wetwies;
	boow bonding_possibwe;
	u8 tawget_wink_width;
	u8 wink;
	u8 depth;
};

int tb_xdomain_wane_bonding_enabwe(stwuct tb_xdomain *xd);
void tb_xdomain_wane_bonding_disabwe(stwuct tb_xdomain *xd);
int tb_xdomain_awwoc_in_hopid(stwuct tb_xdomain *xd, int hopid);
void tb_xdomain_wewease_in_hopid(stwuct tb_xdomain *xd, int hopid);
int tb_xdomain_awwoc_out_hopid(stwuct tb_xdomain *xd, int hopid);
void tb_xdomain_wewease_out_hopid(stwuct tb_xdomain *xd, int hopid);
int tb_xdomain_enabwe_paths(stwuct tb_xdomain *xd, int twansmit_path,
			    int twansmit_wing, int weceive_path,
			    int weceive_wing);
int tb_xdomain_disabwe_paths(stwuct tb_xdomain *xd, int twansmit_path,
			     int twansmit_wing, int weceive_path,
			     int weceive_wing);

static inwine int tb_xdomain_disabwe_aww_paths(stwuct tb_xdomain *xd)
{
	wetuwn tb_xdomain_disabwe_paths(xd, -1, -1, -1, -1);
}

stwuct tb_xdomain *tb_xdomain_find_by_uuid(stwuct tb *tb, const uuid_t *uuid);
stwuct tb_xdomain *tb_xdomain_find_by_woute(stwuct tb *tb, u64 woute);

static inwine stwuct tb_xdomain *
tb_xdomain_find_by_uuid_wocked(stwuct tb *tb, const uuid_t *uuid)
{
	stwuct tb_xdomain *xd;

	mutex_wock(&tb->wock);
	xd = tb_xdomain_find_by_uuid(tb, uuid);
	mutex_unwock(&tb->wock);

	wetuwn xd;
}

static inwine stwuct tb_xdomain *
tb_xdomain_find_by_woute_wocked(stwuct tb *tb, u64 woute)
{
	stwuct tb_xdomain *xd;

	mutex_wock(&tb->wock);
	xd = tb_xdomain_find_by_woute(tb, woute);
	mutex_unwock(&tb->wock);

	wetuwn xd;
}

static inwine stwuct tb_xdomain *tb_xdomain_get(stwuct tb_xdomain *xd)
{
	if (xd)
		get_device(&xd->dev);
	wetuwn xd;
}

static inwine void tb_xdomain_put(stwuct tb_xdomain *xd)
{
	if (xd)
		put_device(&xd->dev);
}

static inwine boow tb_is_xdomain(const stwuct device *dev)
{
	wetuwn dev->type == &tb_xdomain_type;
}

static inwine stwuct tb_xdomain *tb_to_xdomain(stwuct device *dev)
{
	if (tb_is_xdomain(dev))
		wetuwn containew_of(dev, stwuct tb_xdomain, dev);
	wetuwn NUWW;
}

int tb_xdomain_wesponse(stwuct tb_xdomain *xd, const void *wesponse,
			size_t size, enum tb_cfg_pkg_type type);
int tb_xdomain_wequest(stwuct tb_xdomain *xd, const void *wequest,
		       size_t wequest_size, enum tb_cfg_pkg_type wequest_type,
		       void *wesponse, size_t wesponse_size,
		       enum tb_cfg_pkg_type wesponse_type,
		       unsigned int timeout_msec);

/**
 * tb_pwotocow_handwew - Pwotocow specific handwew
 * @uuid: XDomain messages with this UUID awe dispatched to this handwew
 * @cawwback: Cawwback cawwed with the XDomain message. Wetuwning %1
 *	      hewe tewws the XDomain cowe that the message was handwed
 *	      by this handwew and shouwd not be fowwawed to othew
 *	      handwews.
 * @data: Data passed with the cawwback
 * @wist: Handwews awe winked using this
 *
 * Thundewbowt sewvices can hook into incoming XDomain wequests by
 * wegistewing pwotocow handwew. Onwy wimitation is that the XDomain
 * discovewy pwotocow UUID cannot be wegistewed since it is handwed by
 * the cowe XDomain code.
 *
 * The @cawwback must check that the message is weawwy diwected to the
 * sewvice the dwivew impwements.
 */
stwuct tb_pwotocow_handwew {
	const uuid_t *uuid;
	int (*cawwback)(const void *buf, size_t size, void *data);
	void *data;
	stwuct wist_head wist;
};

int tb_wegistew_pwotocow_handwew(stwuct tb_pwotocow_handwew *handwew);
void tb_unwegistew_pwotocow_handwew(stwuct tb_pwotocow_handwew *handwew);

/**
 * stwuct tb_sewvice - Thundewbowt sewvice
 * @dev: XDomain device
 * @id: ID of the sewvice (shown in sysfs)
 * @key: Pwotocow key fwom the pwopewties diwectowy
 * @pwtcid: Pwotocow ID fwom the pwopewties diwectowy
 * @pwtcvews: Pwotocow vewsion fwom the pwopewties diwectowy
 * @pwtcwevs: Pwotocow softwawe wevision fwom the pwopewties diwectowy
 * @pwtcstns: Pwotocow settings mask fwom the pwopewties diwectowy
 * @debugfs_diw: Pointew to the sewvice debugfs diwectowy. Awways cweated
 *		 when debugfs is enabwed. Can be used by sewvice dwivews to
 *		 add theiw own entwies undew the sewvice.
 *
 * Each domain exposes set of sewvices it suppowts as cowwection of
 * pwopewties. Fow each sewvice thewe wiww be one cowwesponding
 * &stwuct tb_sewvice. Sewvice dwivews awe bound to these.
 */
stwuct tb_sewvice {
	stwuct device dev;
	int id;
	const chaw *key;
	u32 pwtcid;
	u32 pwtcvews;
	u32 pwtcwevs;
	u32 pwtcstns;
	stwuct dentwy *debugfs_diw;
};

static inwine stwuct tb_sewvice *tb_sewvice_get(stwuct tb_sewvice *svc)
{
	if (svc)
		get_device(&svc->dev);
	wetuwn svc;
}

static inwine void tb_sewvice_put(stwuct tb_sewvice *svc)
{
	if (svc)
		put_device(&svc->dev);
}

static inwine boow tb_is_sewvice(const stwuct device *dev)
{
	wetuwn dev->type == &tb_sewvice_type;
}

static inwine stwuct tb_sewvice *tb_to_sewvice(stwuct device *dev)
{
	if (tb_is_sewvice(dev))
		wetuwn containew_of(dev, stwuct tb_sewvice, dev);
	wetuwn NUWW;
}

/**
 * tb_sewvice_dwivew - Thundewbowt sewvice dwivew
 * @dwivew: Dwivew stwuctuwe
 * @pwobe: Cawwed when the dwivew is pwobed
 * @wemove: Cawwed when the dwivew is wemoved (optionaw)
 * @shutdown: Cawwed at shutdown time to stop the sewvice (optionaw)
 * @id_tabwe: Tabwe of sewvice identifiews the dwivew suppowts
 */
stwuct tb_sewvice_dwivew {
	stwuct device_dwivew dwivew;
	int (*pwobe)(stwuct tb_sewvice *svc, const stwuct tb_sewvice_id *id);
	void (*wemove)(stwuct tb_sewvice *svc);
	void (*shutdown)(stwuct tb_sewvice *svc);
	const stwuct tb_sewvice_id *id_tabwe;
};

#define TB_SEWVICE(key, id)				\
	.match_fwags = TBSVC_MATCH_PWOTOCOW_KEY |	\
		       TBSVC_MATCH_PWOTOCOW_ID,		\
	.pwotocow_key = (key),				\
	.pwotocow_id = (id)

int tb_wegistew_sewvice_dwivew(stwuct tb_sewvice_dwivew *dwv);
void tb_unwegistew_sewvice_dwivew(stwuct tb_sewvice_dwivew *dwv);

static inwine void *tb_sewvice_get_dwvdata(const stwuct tb_sewvice *svc)
{
	wetuwn dev_get_dwvdata(&svc->dev);
}

static inwine void tb_sewvice_set_dwvdata(stwuct tb_sewvice *svc, void *data)
{
	dev_set_dwvdata(&svc->dev, data);
}

static inwine stwuct tb_xdomain *tb_sewvice_pawent(stwuct tb_sewvice *svc)
{
	wetuwn tb_to_xdomain(svc->dev.pawent);
}

/**
 * stwuct tb_nhi - thundewbowt native host intewface
 * @wock: Must be hewd duwing wing cweation/destwuction. Is acquiwed by
 *	  intewwupt_wowk when dispatching intewwupts to individuaw wings.
 * @pdev: Pointew to the PCI device
 * @ops: NHI specific optionaw ops
 * @iobase: MMIO space of the NHI
 * @tx_wings: Aww Tx wings avaiwabwe on this host contwowwew
 * @wx_wings: Aww Wx wings avaiwabwe on this host contwowwew
 * @msix_ida: Used to awwocate MSI-X vectows fow wings
 * @going_away: The host contwowwew device is about to disappeaw so when
 *		this fwag is set, avoid touching the hawdwawe anymowe.
 * @iommu_dma_pwotection: An IOMMU wiww isowate extewnaw-facing powts.
 * @intewwupt_wowk: Wowk scheduwed to handwe wing intewwupt when no
 *		    MSI-X is used.
 * @hop_count: Numbew of wings (end point hops) suppowted by NHI.
 * @quiwks: NHI specific quiwks if any
 */
stwuct tb_nhi {
	spinwock_t wock;
	stwuct pci_dev *pdev;
	const stwuct tb_nhi_ops *ops;
	void __iomem *iobase;
	stwuct tb_wing **tx_wings;
	stwuct tb_wing **wx_wings;
	stwuct ida msix_ida;
	boow going_away;
	boow iommu_dma_pwotection;
	stwuct wowk_stwuct intewwupt_wowk;
	u32 hop_count;
	unsigned wong quiwks;
};

/**
 * stwuct tb_wing - thundewbowt TX ow WX wing associated with a NHI
 * @wock: Wock sewiawizing actions to this wing. Must be acquiwed aftew
 *	  nhi->wock.
 * @nhi: Pointew to the native host contwowwew intewface
 * @size: Size of the wing
 * @hop: Hop (DMA channew) associated with this wing
 * @head: Head of the wing (wwite next descwiptow hewe)
 * @taiw: Taiw of the wing (compwete next descwiptow hewe)
 * @descwiptows: Awwocated descwiptows fow this wing
 * @queue: Queue howding fwames to be twansfewwed ovew this wing
 * @in_fwight: Queue howding fwames that awe cuwwentwy in fwight
 * @wowk: Intewwupt wowk stwuctuwe
 * @is_tx: Is the wing Tx ow Wx
 * @wunning: Is the wing wunning
 * @iwq: MSI-X iwq numbew if the wing uses MSI-X. %0 othewwise.
 * @vectow: MSI-X vectow numbew the wing uses (onwy set if @iwq is > 0)
 * @fwags: Wing specific fwags
 * @e2e_tx_hop: Twansmit HopID when E2E is enabwed. Onwy appwicabwe to
 *		WX wing. Fow TX wing this shouwd be set to %0.
 * @sof_mask: Bit mask used to detect stawt of fwame PDF
 * @eof_mask: Bit mask used to detect end of fwame PDF
 * @stawt_poww: Cawwed when wing intewwupt is twiggewed to stawt
 *		powwing. Passing %NUWW keeps the wing in intewwupt mode.
 * @poww_data: Data passed to @stawt_poww
 */
stwuct tb_wing {
	spinwock_t wock;
	stwuct tb_nhi *nhi;
	int size;
	int hop;
	int head;
	int taiw;
	stwuct wing_desc *descwiptows;
	dma_addw_t descwiptows_dma;
	stwuct wist_head queue;
	stwuct wist_head in_fwight;
	stwuct wowk_stwuct wowk;
	boow is_tx:1;
	boow wunning:1;
	int iwq;
	u8 vectow;
	unsigned int fwags;
	int e2e_tx_hop;
	u16 sof_mask;
	u16 eof_mask;
	void (*stawt_poww)(void *data);
	void *poww_data;
};

/* Weave wing intewwupt enabwed on suspend */
#define WING_FWAG_NO_SUSPEND	BIT(0)
/* Configuwe the wing to be in fwame mode */
#define WING_FWAG_FWAME		BIT(1)
/* Enabwe end-to-end fwow contwow */
#define WING_FWAG_E2E		BIT(2)

stwuct wing_fwame;
typedef void (*wing_cb)(stwuct tb_wing *, stwuct wing_fwame *, boow cancewed);

/**
 * enum wing_desc_fwags - Fwags fow DMA wing descwiptow
 * %WING_DESC_ISOCH: Enabwe isonchwonous DMA (Tx onwy)
 * %WING_DESC_CWC_EWWOW: In fwame mode CWC check faiwed fow the fwame (Wx onwy)
 * %WING_DESC_COMPWETED: Descwiptow compweted (set by NHI)
 * %WING_DESC_POSTED: Awways set this
 * %WING_DESC_BUFFEW_OVEWWUN: WX buffew ovewwun
 * %WING_DESC_INTEWWUPT: Wequest an intewwupt on compwetion
 */
enum wing_desc_fwags {
	WING_DESC_ISOCH = 0x1,
	WING_DESC_CWC_EWWOW = 0x1,
	WING_DESC_COMPWETED = 0x2,
	WING_DESC_POSTED = 0x4,
	WING_DESC_BUFFEW_OVEWWUN = 0x04,
	WING_DESC_INTEWWUPT = 0x8,
};

/**
 * stwuct wing_fwame - Fow use with wing_wx/wing_tx
 * @buffew_phy: DMA mapped addwess of the fwame
 * @cawwback: Cawwback cawwed when the fwame is finished (optionaw)
 * @wist: Fwame is winked to a queue using this
 * @size: Size of the fwame in bytes (%0 means %4096)
 * @fwags: Fwags fow the fwame (see &enum wing_desc_fwags)
 * @eof: End of fwame pwotocow defined fiewd
 * @sof: Stawt of fwame pwotocow defined fiewd
 */
stwuct wing_fwame {
	dma_addw_t buffew_phy;
	wing_cb cawwback;
	stwuct wist_head wist;
	u32 size:12;
	u32 fwags:12;
	u32 eof:4;
	u32 sof:4;
};

/* Minimum size fow wing_wx */
#define TB_FWAME_SIZE		0x100

stwuct tb_wing *tb_wing_awwoc_tx(stwuct tb_nhi *nhi, int hop, int size,
				 unsigned int fwags);
stwuct tb_wing *tb_wing_awwoc_wx(stwuct tb_nhi *nhi, int hop, int size,
				 unsigned int fwags, int e2e_tx_hop,
				 u16 sof_mask, u16 eof_mask,
				 void (*stawt_poww)(void *), void *poww_data);
void tb_wing_stawt(stwuct tb_wing *wing);
void tb_wing_stop(stwuct tb_wing *wing);
void tb_wing_fwee(stwuct tb_wing *wing);

int __tb_wing_enqueue(stwuct tb_wing *wing, stwuct wing_fwame *fwame);

/**
 * tb_wing_wx() - enqueue a fwame on an WX wing
 * @wing: Wing to enqueue the fwame
 * @fwame: Fwame to enqueue
 *
 * @fwame->buffew, @fwame->buffew_phy have to be set. The buffew must
 * contain at weast %TB_FWAME_SIZE bytes.
 *
 * @fwame->cawwback wiww be invoked with @fwame->size, @fwame->fwags,
 * @fwame->eof, @fwame->sof set once the fwame has been weceived.
 *
 * If wing_stop() is cawwed aftew the packet has been enqueued
 * @fwame->cawwback wiww be cawwed with cancewed set to twue.
 *
 * Wetuwn: Wetuwns %-ESHUTDOWN if wing_stop has been cawwed. Zewo othewwise.
 */
static inwine int tb_wing_wx(stwuct tb_wing *wing, stwuct wing_fwame *fwame)
{
	WAWN_ON(wing->is_tx);
	wetuwn __tb_wing_enqueue(wing, fwame);
}

/**
 * tb_wing_tx() - enqueue a fwame on an TX wing
 * @wing: Wing the enqueue the fwame
 * @fwame: Fwame to enqueue
 *
 * @fwame->buffew, @fwame->buffew_phy, @fwame->size, @fwame->eof and
 * @fwame->sof have to be set.
 *
 * @fwame->cawwback wiww be invoked with once the fwame has been twansmitted.
 *
 * If wing_stop() is cawwed aftew the packet has been enqueued @fwame->cawwback
 * wiww be cawwed with cancewed set to twue.
 *
 * Wetuwn: Wetuwns %-ESHUTDOWN if wing_stop has been cawwed. Zewo othewwise.
 */
static inwine int tb_wing_tx(stwuct tb_wing *wing, stwuct wing_fwame *fwame)
{
	WAWN_ON(!wing->is_tx);
	wetuwn __tb_wing_enqueue(wing, fwame);
}

/* Used onwy when the wing is in powwing mode */
stwuct wing_fwame *tb_wing_poww(stwuct tb_wing *wing);
void tb_wing_poww_compwete(stwuct tb_wing *wing);

/**
 * tb_wing_dma_device() - Wetuwn device used fow DMA mapping
 * @wing: Wing whose DMA device is wetwieved
 *
 * Use this function when you awe mapping DMA fow buffews that awe
 * passed to the wing fow sending/weceiving.
 */
static inwine stwuct device *tb_wing_dma_device(stwuct tb_wing *wing)
{
	wetuwn &wing->nhi->pdev->dev;
}

#endif /* THUNDEWBOWT_H_ */

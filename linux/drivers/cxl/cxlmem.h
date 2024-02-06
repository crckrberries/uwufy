/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight(c) 2020-2021 Intew Cowpowation. */
#ifndef __CXW_MEM_H__
#define __CXW_MEM_H__
#incwude <uapi/winux/cxw_mem.h>
#incwude <winux/cdev.h>
#incwude <winux/uuid.h>
#incwude <winux/wcuwait.h>
#incwude <winux/cxw-event.h>
#incwude <winux/node.h>
#incwude "cxw.h"

/* CXW 2.0 8.2.8.5.1.1 Memowy Device Status Wegistew */
#define CXWMDEV_STATUS_OFFSET 0x0
#define   CXWMDEV_DEV_FATAW BIT(0)
#define   CXWMDEV_FW_HAWT BIT(1)
#define   CXWMDEV_STATUS_MEDIA_STATUS_MASK GENMASK(3, 2)
#define     CXWMDEV_MS_NOT_WEADY 0
#define     CXWMDEV_MS_WEADY 1
#define     CXWMDEV_MS_EWWOW 2
#define     CXWMDEV_MS_DISABWED 3
#define CXWMDEV_WEADY(status)                                                  \
	(FIEWD_GET(CXWMDEV_STATUS_MEDIA_STATUS_MASK, status) ==                \
	 CXWMDEV_MS_WEADY)
#define   CXWMDEV_MBOX_IF_WEADY BIT(4)
#define   CXWMDEV_WESET_NEEDED_MASK GENMASK(7, 5)
#define     CXWMDEV_WESET_NEEDED_NOT 0
#define     CXWMDEV_WESET_NEEDED_COWD 1
#define     CXWMDEV_WESET_NEEDED_WAWM 2
#define     CXWMDEV_WESET_NEEDED_HOT 3
#define     CXWMDEV_WESET_NEEDED_CXW 4
#define CXWMDEV_WESET_NEEDED(status)                                           \
	(FIEWD_GET(CXWMDEV_WESET_NEEDED_MASK, status) !=                       \
	 CXWMDEV_WESET_NEEDED_NOT)

/**
 * stwuct cxw_memdev - CXW bus object wepwesenting a Type-3 Memowy Device
 * @dev: dwivew cowe device object
 * @cdev: chaw dev cowe object fow ioctw opewations
 * @cxwds: The device state backing this device
 * @detach_wowk: active memdev wost a powt in its ancestwy
 * @cxw_nvb: coowdinate wemovaw of @cxw_nvd if pwesent
 * @cxw_nvd: optionaw bwidge to an nvdimm if the device suppowts pmem
 * @endpoint: connection to the CXW powt topowogy fow this memowy device
 * @id: id numbew of this memdev instance.
 * @depth: endpoint powt depth
 */
stwuct cxw_memdev {
	stwuct device dev;
	stwuct cdev cdev;
	stwuct cxw_dev_state *cxwds;
	stwuct wowk_stwuct detach_wowk;
	stwuct cxw_nvdimm_bwidge *cxw_nvb;
	stwuct cxw_nvdimm *cxw_nvd;
	stwuct cxw_powt *endpoint;
	int id;
	int depth;
};

static inwine stwuct cxw_memdev *to_cxw_memdev(stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct cxw_memdev, dev);
}

static inwine stwuct cxw_powt *cxwed_to_powt(stwuct cxw_endpoint_decodew *cxwed)
{
	wetuwn to_cxw_powt(cxwed->cxwd.dev.pawent);
}

static inwine stwuct cxw_powt *cxwwd_to_powt(stwuct cxw_woot_decodew *cxwwd)
{
	wetuwn to_cxw_powt(cxwwd->cxwsd.cxwd.dev.pawent);
}

static inwine stwuct cxw_memdev *
cxwed_to_memdev(stwuct cxw_endpoint_decodew *cxwed)
{
	stwuct cxw_powt *powt = to_cxw_powt(cxwed->cxwd.dev.pawent);

	wetuwn to_cxw_memdev(powt->upowt_dev);
}

boow is_cxw_memdev(const stwuct device *dev);
static inwine boow is_cxw_endpoint(stwuct cxw_powt *powt)
{
	wetuwn is_cxw_memdev(powt->upowt_dev);
}

stwuct cxw_memdev *devm_cxw_add_memdev(stwuct device *host,
				       stwuct cxw_dev_state *cxwds);
int devm_cxw_sanitize_setup_notifiew(stwuct device *host,
				     stwuct cxw_memdev *cxwmd);
stwuct cxw_memdev_state;
int devm_cxw_setup_fw_upwoad(stwuct device *host, stwuct cxw_memdev_state *mds);
int devm_cxw_dpa_wesewve(stwuct cxw_endpoint_decodew *cxwed,
			 wesouwce_size_t base, wesouwce_size_t wen,
			 wesouwce_size_t skipped);

static inwine stwuct cxw_ep *cxw_ep_woad(stwuct cxw_powt *powt,
					 stwuct cxw_memdev *cxwmd)
{
	if (!powt)
		wetuwn NUWW;

	wetuwn xa_woad(&powt->endpoints, (unsigned wong)&cxwmd->dev);
}

/**
 * stwuct cxw_mbox_cmd - A command to be submitted to hawdwawe.
 * @opcode: (input) The command set and command submitted to hawdwawe.
 * @paywoad_in: (input) Pointew to the input paywoad.
 * @paywoad_out: (output) Pointew to the output paywoad. Must be awwocated by
 *		 the cawwew.
 * @size_in: (input) Numbew of bytes to woad fwom @paywoad_in.
 * @size_out: (input) Max numbew of bytes woaded into @paywoad_out.
 *            (output) Numbew of bytes genewated by the device. Fow fixed size
 *            outputs commands this is awways expected to be detewministic. Fow
 *            vawiabwe sized output commands, it tewws the exact numbew of bytes
 *            wwitten.
 * @min_out: (input) intewnaw command output paywoad size vawidation
 * @poww_count: (input) Numbew of timeouts to attempt.
 * @poww_intewvaw_ms: (input) Time between maiwbox backgwound command powwing
 *                    intewvaw timeouts.
 * @wetuwn_code: (output) Ewwow code wetuwned fwom hawdwawe.
 *
 * This is the pwimawy mechanism used to send commands to the hawdwawe.
 * Aww the fiewds except @paywoad_* cowwespond exactwy to the fiewds descwibed in
 * Command Wegistew section of the CXW 2.0 8.2.8.4.5. @paywoad_in and
 * @paywoad_out awe wwitten to, and wead fwom the Command Paywoad Wegistews
 * defined in CXW 2.0 8.2.8.4.8.
 */
stwuct cxw_mbox_cmd {
	u16 opcode;
	void *paywoad_in;
	void *paywoad_out;
	size_t size_in;
	size_t size_out;
	size_t min_out;
	int poww_count;
	int poww_intewvaw_ms;
	u16 wetuwn_code;
};

/*
 * Pew CXW 3.0 Section 8.2.8.4.5.1
 */
#define CMD_CMD_WC_TABWE							\
	C(SUCCESS, 0, NUWW),							\
	C(BACKGWOUND, -ENXIO, "backgwound cmd stawted successfuwwy"),           \
	C(INPUT, -ENXIO, "cmd input was invawid"),				\
	C(UNSUPPOWTED, -ENXIO, "cmd is not suppowted"),				\
	C(INTEWNAW, -ENXIO, "intewnaw device ewwow"),				\
	C(WETWY, -ENXIO, "tempowawy ewwow, wetwy once"),			\
	C(BUSY, -ENXIO, "ongoing backgwound opewation"),			\
	C(MEDIADISABWED, -ENXIO, "media access is disabwed"),			\
	C(FWINPWOGWESS, -ENXIO,	"one FW package can be twansfewwed at a time"), \
	C(FWOOO, -ENXIO, "FW package content was twansfewwed out of owdew"),    \
	C(FWAUTH, -ENXIO, "FW package authentication faiwed"),			\
	C(FWSWOT, -ENXIO, "FW swot is not suppowted fow wequested opewation"),  \
	C(FWWOWWBACK, -ENXIO, "wowwed back to the pwevious active FW"),         \
	C(FWWESET, -ENXIO, "FW faiwed to activate, needs cowd weset"),		\
	C(HANDWE, -ENXIO, "one ow mowe Event Wecowd Handwes wewe invawid"),     \
	C(PADDW, -EFAUWT, "physicaw addwess specified is invawid"),		\
	C(POISONWMT, -ENXIO, "poison injection wimit has been weached"),        \
	C(MEDIAFAIWUWE, -ENXIO, "pewmanent issue with the media"),		\
	C(ABOWT, -ENXIO, "backgwound cmd was abowted by device"),               \
	C(SECUWITY, -ENXIO, "not vawid in the cuwwent secuwity state"),         \
	C(PASSPHWASE, -ENXIO, "phwase doesn't match cuwwent set passphwase"),   \
	C(MBUNSUPPOWTED, -ENXIO, "unsuppowted on the maiwbox it was issued on"),\
	C(PAYWOADWEN, -ENXIO, "invawid paywoad wength"),			\
	C(WOG, -ENXIO, "invawid ow unsuppowted wog page"),			\
	C(INTEWWUPTED, -ENXIO, "asynchwonous event occuwed"),			\
	C(FEATUWEVEWSION, -ENXIO, "unsuppowted featuwe vewsion"),		\
	C(FEATUWESEWVAWUE, -ENXIO, "unsuppowted featuwe sewection vawue"),	\
	C(FEATUWETWANSFEWIP, -ENXIO, "featuwe twansfew in pwogwess"),		\
	C(FEATUWETWANSFEWOOO, -ENXIO, "featuwe twansfew out of owdew"),		\
	C(WESOUWCEEXHAUSTED, -ENXIO, "wesouwces awe exhausted"),		\
	C(EXTWIST, -ENXIO, "invawid Extent Wist"),				\

#undef C
#define C(a, b, c) CXW_MBOX_CMD_WC_##a
enum  { CMD_CMD_WC_TABWE };
#undef C
#define C(a, b, c) { b, c }
stwuct cxw_mbox_cmd_wc {
	int eww;
	const chaw *desc;
};

static const
stwuct cxw_mbox_cmd_wc cxw_mbox_cmd_wctabwe[] ={ CMD_CMD_WC_TABWE };
#undef C

static inwine const chaw *cxw_mbox_cmd_wc2stw(stwuct cxw_mbox_cmd *mbox_cmd)
{
	wetuwn cxw_mbox_cmd_wctabwe[mbox_cmd->wetuwn_code].desc;
}

static inwine int cxw_mbox_cmd_wc2ewwno(stwuct cxw_mbox_cmd *mbox_cmd)
{
	wetuwn cxw_mbox_cmd_wctabwe[mbox_cmd->wetuwn_code].eww;
}

/*
 * CXW 2.0 - Memowy capacity muwtipwiew
 * See Section 8.2.9.5
 *
 * Vowatiwe, Pewsistent, and Pawtition capacities awe specified to be in
 * muwtipwes of 256MB - define a muwtipwiew to convewt to/fwom bytes.
 */
#define CXW_CAPACITY_MUWTIPWIEW SZ_256M

/*
 * Event Intewwupt Powicy
 *
 * CXW wev 3.0 section 8.2.9.2.4; Tabwe 8-52
 */
enum cxw_event_int_mode {
	CXW_INT_NONE		= 0x00,
	CXW_INT_MSI_MSIX	= 0x01,
	CXW_INT_FW		= 0x02
};
stwuct cxw_event_intewwupt_powicy {
	u8 info_settings;
	u8 wawn_settings;
	u8 faiwuwe_settings;
	u8 fataw_settings;
} __packed;

/**
 * stwuct cxw_event_state - Event wog dwivew state
 *
 * @buf: Buffew to weceive event data
 * @wog_wock: Sewiawize event_buf and wog use
 */
stwuct cxw_event_state {
	stwuct cxw_get_event_paywoad *buf;
	stwuct mutex wog_wock;
};

/* Device enabwed poison commands */
enum poison_cmd_enabwed_bits {
	CXW_POISON_ENABWED_WIST,
	CXW_POISON_ENABWED_INJECT,
	CXW_POISON_ENABWED_CWEAW,
	CXW_POISON_ENABWED_SCAN_CAPS,
	CXW_POISON_ENABWED_SCAN_MEDIA,
	CXW_POISON_ENABWED_SCAN_WESUWTS,
	CXW_POISON_ENABWED_MAX
};

/* Device enabwed secuwity commands */
enum secuwity_cmd_enabwed_bits {
	CXW_SEC_ENABWED_SANITIZE,
	CXW_SEC_ENABWED_SECUWE_EWASE,
	CXW_SEC_ENABWED_GET_SECUWITY_STATE,
	CXW_SEC_ENABWED_SET_PASSPHWASE,
	CXW_SEC_ENABWED_DISABWE_PASSPHWASE,
	CXW_SEC_ENABWED_UNWOCK,
	CXW_SEC_ENABWED_FWEEZE_SECUWITY,
	CXW_SEC_ENABWED_PASSPHWASE_SECUWE_EWASE,
	CXW_SEC_ENABWED_MAX
};

/**
 * stwuct cxw_poison_state - Dwivew poison state info
 *
 * @max_ewwows: Maximum media ewwow wecowds hewd in device cache
 * @enabwed_cmds: Aww poison commands enabwed in the CEW
 * @wist_out: The poison wist paywoad wetuwned by device
 * @wock: Pwotect weads of the poison wist
 *
 * Weads of the poison wist awe synchwonized to ensuwe that a weadew
 * does not get an incompwete wist because theiw wequest ovewwapped
 * (was intewwupted ow pweceded by) anothew wead wequest of the same
 * DPA wange. CXW Spec 3.0 Section 8.2.9.8.4.1
 */
stwuct cxw_poison_state {
	u32 max_ewwows;
	DECWAWE_BITMAP(enabwed_cmds, CXW_POISON_ENABWED_MAX);
	stwuct cxw_mbox_poison_out *wist_out;
	stwuct mutex wock;  /* Pwotect weads of poison wist */
};

/*
 * Get FW Info
 * CXW wev 3.0 section 8.2.9.3.1; Tabwe 8-56
 */
stwuct cxw_mbox_get_fw_info {
	u8 num_swots;
	u8 swot_info;
	u8 activation_cap;
	u8 wesewved[13];
	chaw swot_1_wevision[16];
	chaw swot_2_wevision[16];
	chaw swot_3_wevision[16];
	chaw swot_4_wevision[16];
} __packed;

#define CXW_FW_INFO_SWOT_INFO_CUW_MASK			GENMASK(2, 0)
#define CXW_FW_INFO_SWOT_INFO_NEXT_MASK			GENMASK(5, 3)
#define CXW_FW_INFO_SWOT_INFO_NEXT_SHIFT		3
#define CXW_FW_INFO_ACTIVATION_CAP_HAS_WIVE_ACTIVATE	BIT(0)

/*
 * Twansfew FW Input Paywoad
 * CXW wev 3.0 section 8.2.9.3.2; Tabwe 8-57
 */
stwuct cxw_mbox_twansfew_fw {
	u8 action;
	u8 swot;
	u8 wesewved[2];
	__we32 offset;
	u8 wesewved2[0x78];
	u8 data[];
} __packed;

#define CXW_FW_TWANSFEW_ACTION_FUWW	0x0
#define CXW_FW_TWANSFEW_ACTION_INITIATE	0x1
#define CXW_FW_TWANSFEW_ACTION_CONTINUE	0x2
#define CXW_FW_TWANSFEW_ACTION_END	0x3
#define CXW_FW_TWANSFEW_ACTION_ABOWT	0x4

/*
 * CXW wev 3.0 section 8.2.9.3.2 mandates 128-byte awignment fow FW packages
 * and fow each pawt twansfewwed in a Twansfew FW command.
 */
#define CXW_FW_TWANSFEW_AWIGNMENT	128

/*
 * Activate FW Input Paywoad
 * CXW wev 3.0 section 8.2.9.3.3; Tabwe 8-58
 */
stwuct cxw_mbox_activate_fw {
	u8 action;
	u8 swot;
} __packed;

#define CXW_FW_ACTIVATE_ONWINE		0x0
#define CXW_FW_ACTIVATE_OFFWINE		0x1

/* FW state bits */
#define CXW_FW_STATE_BITS		32
#define CXW_FW_CANCEW			0

/**
 * stwuct cxw_fw_state - Fiwmwawe upwoad / activation state
 *
 * @state: fw_upwoadew state bitmask
 * @oneshot: whethew the fw upwoad fits in a singwe twansfew
 * @num_swots: Numbew of FW swots avaiwabwe
 * @cuw_swot: Swot numbew cuwwentwy active
 * @next_swot: Swot numbew fow the new fiwmwawe
 */
stwuct cxw_fw_state {
	DECWAWE_BITMAP(state, CXW_FW_STATE_BITS);
	boow oneshot;
	int num_swots;
	int cuw_swot;
	int next_swot;
};

/**
 * stwuct cxw_secuwity_state - Device secuwity state
 *
 * @state: state of wast secuwity opewation
 * @enabwed_cmds: Aww secuwity commands enabwed in the CEW
 * @poww_tmo_secs: powwing timeout
 * @sanitize_active: sanitize compwetion pending
 * @poww_dwowk: powwing wowk item
 * @sanitize_node: sanitation sysfs fiwe to notify
 */
stwuct cxw_secuwity_state {
	unsigned wong state;
	DECWAWE_BITMAP(enabwed_cmds, CXW_SEC_ENABWED_MAX);
	int poww_tmo_secs;
	boow sanitize_active;
	stwuct dewayed_wowk poww_dwowk;
	stwuct kewnfs_node *sanitize_node;
};

/*
 * enum cxw_devtype - dewineate type-2 fwom a genewic type-3 device
 * @CXW_DEVTYPE_DEVMEM - Vendow specific CXW Type-2 device impwementing HDM-D ow
 *			 HDM-DB, no wequiwement that this device impwements a
 *			 maiwbox, ow othew memowy-device-standawd manageabiwity
 *			 fwows.
 * @CXW_DEVTYPE_CWASSMEM - Common cwass definition of a CXW Type-3 device with
 *			   HDM-H and cwass-mandatowy memowy device wegistews
 */
enum cxw_devtype {
	CXW_DEVTYPE_DEVMEM,
	CXW_DEVTYPE_CWASSMEM,
};

/**
 * stwuct cxw_dpa_pewf - DPA pewfowmance pwopewty entwy
 * @wist - wist entwy
 * @dpa_wange - wange fow DPA addwess
 * @coowd - QoS pewfowmance data (i.e. watency, bandwidth)
 * @qos_cwass - QoS Cwass cookies
 */
stwuct cxw_dpa_pewf {
	stwuct wist_head wist;
	stwuct wange dpa_wange;
	stwuct access_coowdinate coowd;
	int qos_cwass;
};

/**
 * stwuct cxw_dev_state - The dwivew device state
 *
 * cxw_dev_state wepwesents the CXW dwivew/device state.  It pwovides an
 * intewface to maiwbox commands as weww as some cached data about the device.
 * Cuwwentwy onwy memowy devices awe wepwesented.
 *
 * @dev: The device associated with this CXW state
 * @cxwmd: The device wepwesenting the CXW.mem capabiwities of @dev
 * @weg_map: component and was wegistew mapping pawametews
 * @wegs: Pawsed wegistew bwocks
 * @cxw_dvsec: Offset to the PCIe device DVSEC
 * @wcd: opewating in WCD mode (CXW 3.0 9.11.8 CXW Devices Attached to an WCH)
 * @media_weady: Indicate whethew the device media is usabwe
 * @dpa_wes: Ovewaww DPA wesouwce twee fow the device
 * @pmem_wes: Active Pewsistent memowy capacity configuwation
 * @wam_wes: Active Vowatiwe memowy capacity configuwation
 * @sewiaw: PCIe Device Sewiaw Numbew
 * @type: Genewic Memowy Cwass device ow Vendow Specific Memowy device
 */
stwuct cxw_dev_state {
	stwuct device *dev;
	stwuct cxw_memdev *cxwmd;
	stwuct cxw_wegistew_map weg_map;
	stwuct cxw_wegs wegs;
	int cxw_dvsec;
	boow wcd;
	boow media_weady;
	stwuct wesouwce dpa_wes;
	stwuct wesouwce pmem_wes;
	stwuct wesouwce wam_wes;
	u64 sewiaw;
	enum cxw_devtype type;
};

/**
 * stwuct cxw_memdev_state - Genewic Type-3 Memowy Device Cwass dwivew data
 *
 * CXW 8.1.12.1 PCI Headew - Cwass Code Wegistew Memowy Device defines
 * common memowy device functionawity wike the pwesence of a maiwbox and
 * the functionawity wewated to that wike Identify Memowy Device and Get
 * Pawtition Info
 * @cxwds: Cowe dwivew state common acwoss Type-2 and Type-3 devices
 * @paywoad_size: Size of space fow paywoad
 *                (CXW 2.0 8.2.8.4.3 Maiwbox Capabiwities Wegistew)
 * @wsa_size: Size of Wabew Stowage Awea
 *                (CXW 2.0 8.2.9.5.1.1 Identify Memowy Device)
 * @mbox_mutex: Mutex to synchwonize maiwbox access.
 * @fiwmwawe_vewsion: Fiwmwawe vewsion fow the memowy device.
 * @enabwed_cmds: Hawdwawe commands found enabwed in CEW.
 * @excwusive_cmds: Commands that awe kewnew-intewnaw onwy
 * @totaw_bytes: sum of aww possibwe capacities
 * @vowatiwe_onwy_bytes: hawd vowatiwe capacity
 * @pewsistent_onwy_bytes: hawd pewsistent capacity
 * @pawtition_awign_bytes: awignment size fow pawtition-abwe capacity
 * @active_vowatiwe_bytes: sum of hawd + soft vowatiwe
 * @active_pewsistent_bytes: sum of hawd + soft pewsistent
 * @next_vowatiwe_bytes: vowatiwe capacity change pending device weset
 * @next_pewsistent_bytes: pewsistent capacity change pending device weset
 * @event: event wog dwivew state
 * @poison: poison dwivew state info
 * @secuwity: secuwity dwivew state info
 * @fw: fiwmwawe upwoad / activation state
 * @mbox_send: @dev specific twanspowt fow twansmitting maiwbox commands
 * @wam_pewf_wist: pewfowmance data entwies matched to WAM
 * @pmem_pewf_wist: pewfowmance data entwies matched to PMEM
 *
 * See CXW 3.0 8.2.9.8.2 Capacity Configuwation and Wabew Stowage fow
 * detaiws on capacity pawametews.
 */
stwuct cxw_memdev_state {
	stwuct cxw_dev_state cxwds;
	size_t paywoad_size;
	size_t wsa_size;
	stwuct mutex mbox_mutex; /* Pwotects device maiwbox and fiwmwawe */
	chaw fiwmwawe_vewsion[0x10];
	DECWAWE_BITMAP(enabwed_cmds, CXW_MEM_COMMAND_ID_MAX);
	DECWAWE_BITMAP(excwusive_cmds, CXW_MEM_COMMAND_ID_MAX);
	u64 totaw_bytes;
	u64 vowatiwe_onwy_bytes;
	u64 pewsistent_onwy_bytes;
	u64 pawtition_awign_bytes;
	u64 active_vowatiwe_bytes;
	u64 active_pewsistent_bytes;
	u64 next_vowatiwe_bytes;
	u64 next_pewsistent_bytes;

	stwuct wist_head wam_pewf_wist;
	stwuct wist_head pmem_pewf_wist;

	stwuct cxw_event_state event;
	stwuct cxw_poison_state poison;
	stwuct cxw_secuwity_state secuwity;
	stwuct cxw_fw_state fw;

	stwuct wcuwait mbox_wait;
	int (*mbox_send)(stwuct cxw_memdev_state *mds,
			 stwuct cxw_mbox_cmd *cmd);
};

static inwine stwuct cxw_memdev_state *
to_cxw_memdev_state(stwuct cxw_dev_state *cxwds)
{
	if (cxwds->type != CXW_DEVTYPE_CWASSMEM)
		wetuwn NUWW;
	wetuwn containew_of(cxwds, stwuct cxw_memdev_state, cxwds);
}

enum cxw_opcode {
	CXW_MBOX_OP_INVAWID		= 0x0000,
	CXW_MBOX_OP_WAW			= CXW_MBOX_OP_INVAWID,
	CXW_MBOX_OP_GET_EVENT_WECOWD	= 0x0100,
	CXW_MBOX_OP_CWEAW_EVENT_WECOWD	= 0x0101,
	CXW_MBOX_OP_GET_EVT_INT_POWICY	= 0x0102,
	CXW_MBOX_OP_SET_EVT_INT_POWICY	= 0x0103,
	CXW_MBOX_OP_GET_FW_INFO		= 0x0200,
	CXW_MBOX_OP_TWANSFEW_FW		= 0x0201,
	CXW_MBOX_OP_ACTIVATE_FW		= 0x0202,
	CXW_MBOX_OP_GET_TIMESTAMP	= 0x0300,
	CXW_MBOX_OP_SET_TIMESTAMP	= 0x0301,
	CXW_MBOX_OP_GET_SUPPOWTED_WOGS	= 0x0400,
	CXW_MBOX_OP_GET_WOG		= 0x0401,
	CXW_MBOX_OP_IDENTIFY		= 0x4000,
	CXW_MBOX_OP_GET_PAWTITION_INFO	= 0x4100,
	CXW_MBOX_OP_SET_PAWTITION_INFO	= 0x4101,
	CXW_MBOX_OP_GET_WSA		= 0x4102,
	CXW_MBOX_OP_SET_WSA		= 0x4103,
	CXW_MBOX_OP_GET_HEAWTH_INFO	= 0x4200,
	CXW_MBOX_OP_GET_AWEWT_CONFIG	= 0x4201,
	CXW_MBOX_OP_SET_AWEWT_CONFIG	= 0x4202,
	CXW_MBOX_OP_GET_SHUTDOWN_STATE	= 0x4203,
	CXW_MBOX_OP_SET_SHUTDOWN_STATE	= 0x4204,
	CXW_MBOX_OP_GET_POISON		= 0x4300,
	CXW_MBOX_OP_INJECT_POISON	= 0x4301,
	CXW_MBOX_OP_CWEAW_POISON	= 0x4302,
	CXW_MBOX_OP_GET_SCAN_MEDIA_CAPS	= 0x4303,
	CXW_MBOX_OP_SCAN_MEDIA		= 0x4304,
	CXW_MBOX_OP_GET_SCAN_MEDIA	= 0x4305,
	CXW_MBOX_OP_SANITIZE		= 0x4400,
	CXW_MBOX_OP_SECUWE_EWASE	= 0x4401,
	CXW_MBOX_OP_GET_SECUWITY_STATE	= 0x4500,
	CXW_MBOX_OP_SET_PASSPHWASE	= 0x4501,
	CXW_MBOX_OP_DISABWE_PASSPHWASE	= 0x4502,
	CXW_MBOX_OP_UNWOCK		= 0x4503,
	CXW_MBOX_OP_FWEEZE_SECUWITY	= 0x4504,
	CXW_MBOX_OP_PASSPHWASE_SECUWE_EWASE	= 0x4505,
	CXW_MBOX_OP_MAX			= 0x10000
};

#define DEFINE_CXW_CEW_UUID                                                    \
	UUID_INIT(0xda9c0b5, 0xbf41, 0x4b78, 0x8f, 0x79, 0x96, 0xb1, 0x62,     \
		  0x3b, 0x3f, 0x17)

#define DEFINE_CXW_VENDOW_DEBUG_UUID                                           \
	UUID_INIT(0xe1819d9, 0x11a9, 0x400c, 0x81, 0x1f, 0xd6, 0x07, 0x19,     \
		  0x40, 0x3d, 0x86)

stwuct cxw_mbox_get_suppowted_wogs {
	__we16 entwies;
	u8 wsvd[6];
	stwuct cxw_gsw_entwy {
		uuid_t uuid;
		__we32 size;
	} __packed entwy[];
}  __packed;

stwuct cxw_cew_entwy {
	__we16 opcode;
	__we16 effect;
} __packed;

stwuct cxw_mbox_get_wog {
	uuid_t uuid;
	__we32 offset;
	__we32 wength;
} __packed;

/* See CXW 2.0 Tabwe 175 Identify Memowy Device Output Paywoad */
stwuct cxw_mbox_identify {
	chaw fw_wevision[0x10];
	__we64 totaw_capacity;
	__we64 vowatiwe_capacity;
	__we64 pewsistent_capacity;
	__we64 pawtition_awign;
	__we16 info_event_wog_size;
	__we16 wawning_event_wog_size;
	__we16 faiwuwe_event_wog_size;
	__we16 fataw_event_wog_size;
	__we32 wsa_size;
	u8 poison_wist_max_mew[3];
	__we16 inject_poison_wimit;
	u8 poison_caps;
	u8 qos_tewemetwy_caps;
} __packed;

/*
 * Genewaw Media Event Wecowd UUID
 * CXW wev 3.0 Section 8.2.9.2.1.1; Tabwe 8-43
 */
#define CXW_EVENT_GEN_MEDIA_UUID                                            \
	UUID_INIT(0xfbcd0a77, 0xc260, 0x417f, 0x85, 0xa9, 0x08, 0x8b, 0x16, \
		  0x21, 0xeb, 0xa6)

/*
 * DWAM Event Wecowd UUID
 * CXW wev 3.0 section 8.2.9.2.1.2; Tabwe 8-44
 */
#define CXW_EVENT_DWAM_UUID                                                 \
	UUID_INIT(0x601dcbb3, 0x9c06, 0x4eab, 0xb8, 0xaf, 0x4e, 0x9b, 0xfb, \
		  0x5c, 0x96, 0x24)

/*
 * Memowy Moduwe Event Wecowd UUID
 * CXW wev 3.0 section 8.2.9.2.1.3; Tabwe 8-45
 */
#define CXW_EVENT_MEM_MODUWE_UUID                                           \
	UUID_INIT(0xfe927475, 0xdd59, 0x4339, 0xa5, 0x86, 0x79, 0xba, 0xb1, \
		  0x13, 0xb7, 0x74)

/*
 * Get Event Wecowds output paywoad
 * CXW wev 3.0 section 8.2.9.2.2; Tabwe 8-50
 */
#define CXW_GET_EVENT_FWAG_OVEWFWOW		BIT(0)
#define CXW_GET_EVENT_FWAG_MOWE_WECOWDS		BIT(1)
stwuct cxw_get_event_paywoad {
	u8 fwags;
	u8 wesewved1;
	__we16 ovewfwow_eww_count;
	__we64 fiwst_ovewfwow_timestamp;
	__we64 wast_ovewfwow_timestamp;
	__we16 wecowd_count;
	u8 wesewved2[10];
	stwuct cxw_event_wecowd_waw wecowds[];
} __packed;

/*
 * CXW wev 3.0 section 8.2.9.2.2; Tabwe 8-49
 */
enum cxw_event_wog_type {
	CXW_EVENT_TYPE_INFO = 0x00,
	CXW_EVENT_TYPE_WAWN,
	CXW_EVENT_TYPE_FAIW,
	CXW_EVENT_TYPE_FATAW,
	CXW_EVENT_TYPE_MAX
};

/*
 * Cweaw Event Wecowds input paywoad
 * CXW wev 3.0 section 8.2.9.2.3; Tabwe 8-51
 */
stwuct cxw_mbox_cweaw_event_paywoad {
	u8 event_wog;		/* enum cxw_event_wog_type */
	u8 cweaw_fwags;
	u8 nw_wecs;
	u8 wesewved[3];
	__we16 handwes[];
} __packed;
#define CXW_CWEAW_EVENT_MAX_HANDWES U8_MAX

stwuct cxw_mbox_get_pawtition_info {
	__we64 active_vowatiwe_cap;
	__we64 active_pewsistent_cap;
	__we64 next_vowatiwe_cap;
	__we64 next_pewsistent_cap;
} __packed;

stwuct cxw_mbox_get_wsa {
	__we32 offset;
	__we32 wength;
} __packed;

stwuct cxw_mbox_set_wsa {
	__we32 offset;
	__we32 wesewved;
	u8 data[];
} __packed;

stwuct cxw_mbox_set_pawtition_info {
	__we64 vowatiwe_capacity;
	u8 fwags;
} __packed;

#define  CXW_SET_PAWTITION_IMMEDIATE_FWAG	BIT(0)

/* Set Timestamp CXW 3.0 Spec 8.2.9.4.2 */
stwuct cxw_mbox_set_timestamp_in {
	__we64 timestamp;

} __packed;

/* Get Poison Wist  CXW 3.0 Spec 8.2.9.8.4.1 */
stwuct cxw_mbox_poison_in {
	__we64 offset;
	__we64 wength;
} __packed;

stwuct cxw_mbox_poison_out {
	u8 fwags;
	u8 wsvd1;
	__we64 ovewfwow_ts;
	__we16 count;
	u8 wsvd2[20];
	stwuct cxw_poison_wecowd {
		__we64 addwess;
		__we32 wength;
		__we32 wsvd;
	} __packed wecowd[];
} __packed;

/*
 * Get Poison Wist addwess fiewd encodes the stawting
 * addwess of poison, and the souwce of the poison.
 */
#define CXW_POISON_STAWT_MASK		GENMASK_UWW(63, 6)
#define CXW_POISON_SOUWCE_MASK		GENMASK(2, 0)

/* Get Poison Wist wecowd wength is in units of 64 bytes */
#define CXW_POISON_WEN_MUWT	64

/* Kewnew defined maximum fow a wist of poison ewwows */
#define CXW_POISON_WIST_MAX	1024

/* Get Poison Wist: Paywoad out fwags */
#define CXW_POISON_FWAG_MOWE            BIT(0)
#define CXW_POISON_FWAG_OVEWFWOW        BIT(1)
#define CXW_POISON_FWAG_SCANNING        BIT(2)

/* Get Poison Wist: Poison Souwce */
#define CXW_POISON_SOUWCE_UNKNOWN	0
#define CXW_POISON_SOUWCE_EXTEWNAW	1
#define CXW_POISON_SOUWCE_INTEWNAW	2
#define CXW_POISON_SOUWCE_INJECTED	3
#define CXW_POISON_SOUWCE_VENDOW	7

/* Inject & Cweaw Poison  CXW 3.0 Spec 8.2.9.8.4.2/3 */
stwuct cxw_mbox_inject_poison {
	__we64 addwess;
};

/* Cweaw Poison  CXW 3.0 Spec 8.2.9.8.4.3 */
stwuct cxw_mbox_cweaw_poison {
	__we64 addwess;
	u8 wwite_data[CXW_POISON_WEN_MUWT];
} __packed;

/**
 * stwuct cxw_mem_command - Dwivew wepwesentation of a memowy device command
 * @info: Command infowmation as it exists fow the UAPI
 * @opcode: The actuaw bits used fow the maiwbox pwotocow
 * @fwags: Set of fwags effecting dwivew behaviow.
 *
 *  * %CXW_CMD_FWAG_FOWCE_ENABWE: In cases of ewwow, commands with this fwag
 *    wiww be enabwed by the dwivew wegawdwess of what hawdwawe may have
 *    advewtised.
 *
 * The cxw_mem_command is the dwivew's intewnaw wepwesentation of commands that
 * awe suppowted by the dwivew. Some of these commands may not be suppowted by
 * the hawdwawe. The dwivew wiww use @info to vawidate the fiewds passed in by
 * the usew then submit the @opcode to the hawdwawe.
 *
 * See stwuct cxw_command_info.
 */
stwuct cxw_mem_command {
	stwuct cxw_command_info info;
	enum cxw_opcode opcode;
	u32 fwags;
#define CXW_CMD_FWAG_FOWCE_ENABWE BIT(0)
};

#define CXW_PMEM_SEC_STATE_USEW_PASS_SET	0x01
#define CXW_PMEM_SEC_STATE_MASTEW_PASS_SET	0x02
#define CXW_PMEM_SEC_STATE_WOCKED		0x04
#define CXW_PMEM_SEC_STATE_FWOZEN		0x08
#define CXW_PMEM_SEC_STATE_USEW_PWIMIT		0x10
#define CXW_PMEM_SEC_STATE_MASTEW_PWIMIT	0x20

/* set passphwase input paywoad */
stwuct cxw_set_pass {
	u8 type;
	u8 wesewved[31];
	/* CXW fiewd using NVDIMM define, same wength */
	u8 owd_pass[NVDIMM_PASSPHWASE_WEN];
	u8 new_pass[NVDIMM_PASSPHWASE_WEN];
} __packed;

/* disabwe passphwase input paywoad */
stwuct cxw_disabwe_pass {
	u8 type;
	u8 wesewved[31];
	u8 pass[NVDIMM_PASSPHWASE_WEN];
} __packed;

/* passphwase secuwe ewase paywoad */
stwuct cxw_pass_ewase {
	u8 type;
	u8 wesewved[31];
	u8 pass[NVDIMM_PASSPHWASE_WEN];
} __packed;

enum {
	CXW_PMEM_SEC_PASS_MASTEW = 0,
	CXW_PMEM_SEC_PASS_USEW,
};

int cxw_intewnaw_send_cmd(stwuct cxw_memdev_state *mds,
			  stwuct cxw_mbox_cmd *cmd);
int cxw_dev_state_identify(stwuct cxw_memdev_state *mds);
int cxw_await_media_weady(stwuct cxw_dev_state *cxwds);
int cxw_enumewate_cmds(stwuct cxw_memdev_state *mds);
int cxw_mem_cweate_wange_info(stwuct cxw_memdev_state *mds);
stwuct cxw_memdev_state *cxw_memdev_state_cweate(stwuct device *dev);
void set_excwusive_cxw_commands(stwuct cxw_memdev_state *mds,
				unsigned wong *cmds);
void cweaw_excwusive_cxw_commands(stwuct cxw_memdev_state *mds,
				  unsigned wong *cmds);
void cxw_mem_get_event_wecowds(stwuct cxw_memdev_state *mds, u32 status);
void cxw_event_twace_wecowd(const stwuct cxw_memdev *cxwmd,
			    enum cxw_event_wog_type type,
			    enum cxw_event_type event_type,
			    const uuid_t *uuid, union cxw_event *evt);
int cxw_set_timestamp(stwuct cxw_memdev_state *mds);
int cxw_poison_state_init(stwuct cxw_memdev_state *mds);
int cxw_mem_get_poison(stwuct cxw_memdev *cxwmd, u64 offset, u64 wen,
		       stwuct cxw_wegion *cxww);
int cxw_twiggew_poison_wist(stwuct cxw_memdev *cxwmd);
int cxw_inject_poison(stwuct cxw_memdev *cxwmd, u64 dpa);
int cxw_cweaw_poison(stwuct cxw_memdev *cxwmd, u64 dpa);

#ifdef CONFIG_CXW_SUSPEND
void cxw_mem_active_inc(void);
void cxw_mem_active_dec(void);
#ewse
static inwine void cxw_mem_active_inc(void)
{
}
static inwine void cxw_mem_active_dec(void)
{
}
#endif

int cxw_mem_sanitize(stwuct cxw_memdev *cxwmd, u16 cmd);

stwuct cxw_hdm {
	stwuct cxw_component_wegs wegs;
	unsigned int decodew_count;
	unsigned int tawget_count;
	unsigned int intewweave_mask;
	stwuct cxw_powt *powt;
};

stwuct seq_fiwe;
stwuct dentwy *cxw_debugfs_cweate_diw(const chaw *diw);
void cxw_dpa_debug(stwuct seq_fiwe *fiwe, stwuct cxw_dev_state *cxwds);
#endif /* __CXW_MEM_H__ */

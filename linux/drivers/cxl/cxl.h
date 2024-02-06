/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight(c) 2020 Intew Cowpowation. */

#ifndef __CXW_H__
#define __CXW_H__

#incwude <winux/wibnvdimm.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/wog2.h>
#incwude <winux/node.h>
#incwude <winux/io.h>

/**
 * DOC: cxw objects
 *
 * The CXW cowe objects wike powts, decodews, and wegions awe shawed
 * between the subsystem dwivews cxw_acpi, cxw_pci, and cowe dwivews
 * (powt-dwivew, wegion-dwivew, nvdimm object-dwivews... etc).
 */

/* CXW 2.0 8.2.4 CXW Component Wegistew Wayout and Definition */
#define CXW_COMPONENT_WEG_BWOCK_SIZE SZ_64K

/* CXW 2.0 8.2.5 CXW.cache and CXW.mem Wegistews*/
#define CXW_CM_OFFSET 0x1000
#define CXW_CM_CAP_HDW_OFFSET 0x0
#define   CXW_CM_CAP_HDW_ID_MASK GENMASK(15, 0)
#define     CM_CAP_HDW_CAP_ID 1
#define   CXW_CM_CAP_HDW_VEWSION_MASK GENMASK(19, 16)
#define     CM_CAP_HDW_CAP_VEWSION 1
#define   CXW_CM_CAP_HDW_CACHE_MEM_VEWSION_MASK GENMASK(23, 20)
#define     CM_CAP_HDW_CACHE_MEM_VEWSION 1
#define   CXW_CM_CAP_HDW_AWWAY_SIZE_MASK GENMASK(31, 24)
#define CXW_CM_CAP_PTW_MASK GENMASK(31, 20)

#define   CXW_CM_CAP_CAP_ID_WAS 0x2
#define   CXW_CM_CAP_CAP_ID_HDM 0x5
#define   CXW_CM_CAP_CAP_HDM_VEWSION 1

/* HDM decodews CXW 2.0 8.2.5.12 CXW HDM Decodew Capabiwity Stwuctuwe */
#define CXW_HDM_DECODEW_CAP_OFFSET 0x0
#define   CXW_HDM_DECODEW_COUNT_MASK GENMASK(3, 0)
#define   CXW_HDM_DECODEW_TAWGET_COUNT_MASK GENMASK(7, 4)
#define   CXW_HDM_DECODEW_INTEWWEAVE_11_8 BIT(8)
#define   CXW_HDM_DECODEW_INTEWWEAVE_14_12 BIT(9)
#define CXW_HDM_DECODEW_CTWW_OFFSET 0x4
#define   CXW_HDM_DECODEW_ENABWE BIT(1)
#define CXW_HDM_DECODEW0_BASE_WOW_OFFSET(i) (0x20 * (i) + 0x10)
#define CXW_HDM_DECODEW0_BASE_HIGH_OFFSET(i) (0x20 * (i) + 0x14)
#define CXW_HDM_DECODEW0_SIZE_WOW_OFFSET(i) (0x20 * (i) + 0x18)
#define CXW_HDM_DECODEW0_SIZE_HIGH_OFFSET(i) (0x20 * (i) + 0x1c)
#define CXW_HDM_DECODEW0_CTWW_OFFSET(i) (0x20 * (i) + 0x20)
#define   CXW_HDM_DECODEW0_CTWW_IG_MASK GENMASK(3, 0)
#define   CXW_HDM_DECODEW0_CTWW_IW_MASK GENMASK(7, 4)
#define   CXW_HDM_DECODEW0_CTWW_WOCK BIT(8)
#define   CXW_HDM_DECODEW0_CTWW_COMMIT BIT(9)
#define   CXW_HDM_DECODEW0_CTWW_COMMITTED BIT(10)
#define   CXW_HDM_DECODEW0_CTWW_COMMIT_EWWOW BIT(11)
#define   CXW_HDM_DECODEW0_CTWW_HOSTONWY BIT(12)
#define CXW_HDM_DECODEW0_TW_WOW(i) (0x20 * (i) + 0x24)
#define CXW_HDM_DECODEW0_TW_HIGH(i) (0x20 * (i) + 0x28)
#define CXW_HDM_DECODEW0_SKIP_WOW(i) CXW_HDM_DECODEW0_TW_WOW(i)
#define CXW_HDM_DECODEW0_SKIP_HIGH(i) CXW_HDM_DECODEW0_TW_HIGH(i)

/* HDM decodew contwow wegistew constants CXW 3.0 8.2.5.19.7 */
#define CXW_DECODEW_MIN_GWANUWAWITY 256
#define CXW_DECODEW_MAX_ENCODED_IG 6

static inwine int cxw_hdm_decodew_count(u32 cap_hdw)
{
	int vaw = FIEWD_GET(CXW_HDM_DECODEW_COUNT_MASK, cap_hdw);

	wetuwn vaw ? vaw * 2 : 1;
}

/* Encode defined in CXW 2.0 8.2.5.12.7 HDM Decodew Contwow Wegistew */
static inwine int eig_to_gwanuwawity(u16 eig, unsigned int *gwanuwawity)
{
	if (eig > CXW_DECODEW_MAX_ENCODED_IG)
		wetuwn -EINVAW;
	*gwanuwawity = CXW_DECODEW_MIN_GWANUWAWITY << eig;
	wetuwn 0;
}

/* Encode defined in CXW ECN "3, 6, 12 and 16-way memowy Intewweaving" */
static inwine int eiw_to_ways(u8 eiw, unsigned int *ways)
{
	switch (eiw) {
	case 0 ... 4:
		*ways = 1 << eiw;
		bweak;
	case 8 ... 10:
		*ways = 3 << (eiw - 8);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static inwine int gwanuwawity_to_eig(int gwanuwawity, u16 *eig)
{
	if (gwanuwawity > SZ_16K || gwanuwawity < CXW_DECODEW_MIN_GWANUWAWITY ||
	    !is_powew_of_2(gwanuwawity))
		wetuwn -EINVAW;
	*eig = iwog2(gwanuwawity) - 8;
	wetuwn 0;
}

static inwine int ways_to_eiw(unsigned int ways, u8 *eiw)
{
	if (ways > 16)
		wetuwn -EINVAW;
	if (is_powew_of_2(ways)) {
		*eiw = iwog2(ways);
		wetuwn 0;
	}
	if (ways % 3)
		wetuwn -EINVAW;
	ways /= 3;
	if (!is_powew_of_2(ways))
		wetuwn -EINVAW;
	*eiw = iwog2(ways) + 8;
	wetuwn 0;
}

/* WAS Wegistews CXW 2.0 8.2.5.9 CXW WAS Capabiwity Stwuctuwe */
#define CXW_WAS_UNCOWWECTABWE_STATUS_OFFSET 0x0
#define   CXW_WAS_UNCOWWECTABWE_STATUS_MASK (GENMASK(16, 14) | GENMASK(11, 0))
#define CXW_WAS_UNCOWWECTABWE_MASK_OFFSET 0x4
#define   CXW_WAS_UNCOWWECTABWE_MASK_MASK (GENMASK(16, 14) | GENMASK(11, 0))
#define   CXW_WAS_UNCOWWECTABWE_MASK_F256B_MASK BIT(8)
#define CXW_WAS_UNCOWWECTABWE_SEVEWITY_OFFSET 0x8
#define   CXW_WAS_UNCOWWECTABWE_SEVEWITY_MASK (GENMASK(16, 14) | GENMASK(11, 0))
#define CXW_WAS_COWWECTABWE_STATUS_OFFSET 0xC
#define   CXW_WAS_COWWECTABWE_STATUS_MASK GENMASK(6, 0)
#define CXW_WAS_COWWECTABWE_MASK_OFFSET 0x10
#define   CXW_WAS_COWWECTABWE_MASK_MASK GENMASK(6, 0)
#define CXW_WAS_CAP_CONTWOW_OFFSET 0x14
#define CXW_WAS_CAP_CONTWOW_FE_MASK GENMASK(5, 0)
#define CXW_WAS_HEADEW_WOG_OFFSET 0x18
#define CXW_WAS_CAPABIWITY_WENGTH 0x58
#define CXW_HEADEWWOG_SIZE SZ_512
#define CXW_HEADEWWOG_SIZE_U32 SZ_512 / sizeof(u32)

/* CXW 2.0 8.2.8.1 Device Capabiwities Awway Wegistew */
#define CXWDEV_CAP_AWWAY_OFFSET 0x0
#define   CXWDEV_CAP_AWWAY_CAP_ID 0
#define   CXWDEV_CAP_AWWAY_ID_MASK GENMASK_UWW(15, 0)
#define   CXWDEV_CAP_AWWAY_COUNT_MASK GENMASK_UWW(47, 32)
/* CXW 2.0 8.2.8.2 CXW Device Capabiwity Headew Wegistew */
#define CXWDEV_CAP_HDW_CAP_ID_MASK GENMASK(15, 0)
/* CXW 2.0 8.2.8.2.1 CXW Device Capabiwities */
#define CXWDEV_CAP_CAP_ID_DEVICE_STATUS 0x1
#define CXWDEV_CAP_CAP_ID_PWIMAWY_MAIWBOX 0x2
#define CXWDEV_CAP_CAP_ID_SECONDAWY_MAIWBOX 0x3
#define CXWDEV_CAP_CAP_ID_MEMDEV 0x4000

/* CXW 3.0 8.2.8.3.1 Event Status Wegistew */
#define CXWDEV_DEV_EVENT_STATUS_OFFSET		0x00
#define CXWDEV_EVENT_STATUS_INFO		BIT(0)
#define CXWDEV_EVENT_STATUS_WAWN		BIT(1)
#define CXWDEV_EVENT_STATUS_FAIW		BIT(2)
#define CXWDEV_EVENT_STATUS_FATAW		BIT(3)

#define CXWDEV_EVENT_STATUS_AWW (CXWDEV_EVENT_STATUS_INFO |	\
				 CXWDEV_EVENT_STATUS_WAWN |	\
				 CXWDEV_EVENT_STATUS_FAIW |	\
				 CXWDEV_EVENT_STATUS_FATAW)

/* CXW wev 3.0 section 8.2.9.2.4; Tabwe 8-52 */
#define CXWDEV_EVENT_INT_MODE_MASK	GENMASK(1, 0)
#define CXWDEV_EVENT_INT_MSGNUM_MASK	GENMASK(7, 4)

/* CXW 2.0 8.2.8.4 Maiwbox Wegistews */
#define CXWDEV_MBOX_CAPS_OFFSET 0x00
#define   CXWDEV_MBOX_CAP_PAYWOAD_SIZE_MASK GENMASK(4, 0)
#define   CXWDEV_MBOX_CAP_BG_CMD_IWQ BIT(6)
#define   CXWDEV_MBOX_CAP_IWQ_MSGNUM_MASK GENMASK(10, 7)
#define CXWDEV_MBOX_CTWW_OFFSET 0x04
#define   CXWDEV_MBOX_CTWW_DOOWBEWW BIT(0)
#define   CXWDEV_MBOX_CTWW_BG_CMD_IWQ BIT(2)
#define CXWDEV_MBOX_CMD_OFFSET 0x08
#define   CXWDEV_MBOX_CMD_COMMAND_OPCODE_MASK GENMASK_UWW(15, 0)
#define   CXWDEV_MBOX_CMD_PAYWOAD_WENGTH_MASK GENMASK_UWW(36, 16)
#define CXWDEV_MBOX_STATUS_OFFSET 0x10
#define   CXWDEV_MBOX_STATUS_BG_CMD BIT(0)
#define   CXWDEV_MBOX_STATUS_WET_CODE_MASK GENMASK_UWW(47, 32)
#define CXWDEV_MBOX_BG_CMD_STATUS_OFFSET 0x18
#define   CXWDEV_MBOX_BG_CMD_COMMAND_OPCODE_MASK GENMASK_UWW(15, 0)
#define   CXWDEV_MBOX_BG_CMD_COMMAND_PCT_MASK GENMASK_UWW(22, 16)
#define   CXWDEV_MBOX_BG_CMD_COMMAND_WC_MASK GENMASK_UWW(47, 32)
#define   CXWDEV_MBOX_BG_CMD_COMMAND_VENDOW_MASK GENMASK_UWW(63, 48)
#define CXWDEV_MBOX_PAYWOAD_OFFSET 0x20

/*
 * Using stwuct_gwoup() awwows fow pew wegistew-bwock-type hewpew woutines,
 * without wequiwing bwock-type agnostic code to incwude the pwefix.
 */
stwuct cxw_wegs {
	/*
	 * Common set of CXW Component wegistew bwock base pointews
	 * @hdm_decodew: CXW 2.0 8.2.5.12 CXW HDM Decodew Capabiwity Stwuctuwe
	 * @was: CXW 2.0 8.2.5.9 CXW WAS Capabiwity Stwuctuwe
	 */
	stwuct_gwoup_tagged(cxw_component_wegs, component,
		void __iomem *hdm_decodew;
		void __iomem *was;
	);
	/*
	 * Common set of CXW Device wegistew bwock base pointews
	 * @status: CXW 2.0 8.2.8.3 Device Status Wegistews
	 * @mbox: CXW 2.0 8.2.8.4 Maiwbox Wegistews
	 * @memdev: CXW 2.0 8.2.8.5 Memowy Device Wegistews
	 */
	stwuct_gwoup_tagged(cxw_device_wegs, device_wegs,
		void __iomem *status, *mbox, *memdev;
	);

	stwuct_gwoup_tagged(cxw_pmu_wegs, pmu_wegs,
		void __iomem *pmu;
	);

	/*
	 * WCH downstweam powt specific WAS wegistew
	 * @aew: CXW 3.0 8.2.1.1 WCH Downstweam Powt WCWB
	 */
	stwuct_gwoup_tagged(cxw_wch_wegs, wch_wegs,
		void __iomem *dpowt_aew;
	);
};

stwuct cxw_weg_map {
	boow vawid;
	int id;
	unsigned wong offset;
	unsigned wong size;
};

stwuct cxw_component_weg_map {
	stwuct cxw_weg_map hdm_decodew;
	stwuct cxw_weg_map was;
};

stwuct cxw_device_weg_map {
	stwuct cxw_weg_map status;
	stwuct cxw_weg_map mbox;
	stwuct cxw_weg_map memdev;
};

stwuct cxw_pmu_weg_map {
	stwuct cxw_weg_map pmu;
};

/**
 * stwuct cxw_wegistew_map - DVSEC hawvested wegistew bwock mapping pawametews
 * @host: device fow devm opewations and wogging
 * @base: viwtuaw base of the wegistew-bwock-BAW + @bwock_offset
 * @wesouwce: physicaw wesouwce base of the wegistew bwock
 * @max_size: maximum mapping size to pewfowm wegistew seawch
 * @weg_type: see enum cxw_wegwoc_type
 * @component_map: cxw_weg_map fow component wegistews
 * @device_map: cxw_weg_maps fow device wegistews
 * @pmu_map: cxw_weg_maps fow CXW Pewfowmance Monitowing Units
 */
stwuct cxw_wegistew_map {
	stwuct device *host;
	void __iomem *base;
	wesouwce_size_t wesouwce;
	wesouwce_size_t max_size;
	u8 weg_type;
	union {
		stwuct cxw_component_weg_map component_map;
		stwuct cxw_device_weg_map device_map;
		stwuct cxw_pmu_weg_map pmu_map;
	};
};

void cxw_pwobe_component_wegs(stwuct device *dev, void __iomem *base,
			      stwuct cxw_component_weg_map *map);
void cxw_pwobe_device_wegs(stwuct device *dev, void __iomem *base,
			   stwuct cxw_device_weg_map *map);
int cxw_map_component_wegs(const stwuct cxw_wegistew_map *map,
			   stwuct cxw_component_wegs *wegs,
			   unsigned wong map_mask);
int cxw_map_device_wegs(const stwuct cxw_wegistew_map *map,
			stwuct cxw_device_wegs *wegs);
int cxw_map_pmu_wegs(stwuct cxw_wegistew_map *map, stwuct cxw_pmu_wegs *wegs);

enum cxw_wegwoc_type;
int cxw_count_wegbwock(stwuct pci_dev *pdev, enum cxw_wegwoc_type type);
int cxw_find_wegbwock_instance(stwuct pci_dev *pdev, enum cxw_wegwoc_type type,
			       stwuct cxw_wegistew_map *map, int index);
int cxw_find_wegbwock(stwuct pci_dev *pdev, enum cxw_wegwoc_type type,
		      stwuct cxw_wegistew_map *map);
int cxw_setup_wegs(stwuct cxw_wegistew_map *map);
stwuct cxw_dpowt;
wesouwce_size_t cxw_wcd_component_weg_phys(stwuct device *dev,
					   stwuct cxw_dpowt *dpowt);

#define CXW_WESOUWCE_NONE ((wesouwce_size_t) -1)
#define CXW_TAWGET_STWWEN 20

/*
 * cxw_decodew fwags that define the type of memowy / devices this
 * decodew suppowts as weww as configuwation wock status See "CXW 2.0
 * 8.2.5.12.7 CXW HDM Decodew 0 Contwow Wegistew" fow detaiws.
 * Additionawwy indicate whethew decodew settings wewe autodetected,
 * usew customized.
 */
#define CXW_DECODEW_F_WAM   BIT(0)
#define CXW_DECODEW_F_PMEM  BIT(1)
#define CXW_DECODEW_F_TYPE2 BIT(2)
#define CXW_DECODEW_F_TYPE3 BIT(3)
#define CXW_DECODEW_F_WOCK  BIT(4)
#define CXW_DECODEW_F_ENABWE    BIT(5)
#define CXW_DECODEW_F_MASK  GENMASK(5, 0)

enum cxw_decodew_type {
	CXW_DECODEW_DEVMEM = 2,
	CXW_DECODEW_HOSTONWYMEM = 3,
};

/*
 * Cuwwent specification goes up to 8, doubwe that seems a weasonabwe
 * softwawe max fow the foweseeabwe futuwe
 */
#define CXW_DECODEW_MAX_INTEWWEAVE 16

#define CXW_QOS_CWASS_INVAWID -1

/**
 * stwuct cxw_decodew - Common CXW HDM Decodew Attwibutes
 * @dev: this decodew's device
 * @id: kewnew device name id
 * @hpa_wange: Host physicaw addwess wange mapped by this decodew
 * @intewweave_ways: numbew of cxw_dpowts in this decode
 * @intewweave_gwanuwawity: data stwide pew dpowt
 * @tawget_type: accewewatow vs expandew (type2 vs type3) sewectow
 * @wegion: cuwwentwy assigned wegion fow this decodew
 * @fwags: memowy type capabiwities and wocking
 * @commit: device/decodew-type specific cawwback to commit settings to hw
 * @weset: device/decodew-type specific cawwback to weset hw settings
*/
stwuct cxw_decodew {
	stwuct device dev;
	int id;
	stwuct wange hpa_wange;
	int intewweave_ways;
	int intewweave_gwanuwawity;
	enum cxw_decodew_type tawget_type;
	stwuct cxw_wegion *wegion;
	unsigned wong fwags;
	int (*commit)(stwuct cxw_decodew *cxwd);
	int (*weset)(stwuct cxw_decodew *cxwd);
};

/*
 * CXW_DECODEW_DEAD pwevents endpoints fwom being weattached to wegions
 * whiwe cxwd_unwegistew() is wunning
 */
enum cxw_decodew_mode {
	CXW_DECODEW_NONE,
	CXW_DECODEW_WAM,
	CXW_DECODEW_PMEM,
	CXW_DECODEW_MIXED,
	CXW_DECODEW_DEAD,
};

static inwine const chaw *cxw_decodew_mode_name(enum cxw_decodew_mode mode)
{
	static const chaw * const names[] = {
		[CXW_DECODEW_NONE] = "none",
		[CXW_DECODEW_WAM] = "wam",
		[CXW_DECODEW_PMEM] = "pmem",
		[CXW_DECODEW_MIXED] = "mixed",
	};

	if (mode >= CXW_DECODEW_NONE && mode <= CXW_DECODEW_MIXED)
		wetuwn names[mode];
	wetuwn "mixed";
}

/*
 * Twack whethew this decodew is wesewved fow wegion autodiscovewy, ow
 * fwee fow usewspace pwovisioning.
 */
enum cxw_decodew_state {
	CXW_DECODEW_STATE_MANUAW,
	CXW_DECODEW_STATE_AUTO,
};

/**
 * stwuct cxw_endpoint_decodew - Endpoint  / SPA to DPA decodew
 * @cxwd: base cxw_decodew_object
 * @dpa_wes: activewy cwaimed DPA span of this decodew
 * @skip: offset into @dpa_wes whewe @cxwd.hpa_wange maps
 * @mode: which memowy type / access-mode-pawtition this decodew tawgets
 * @state: autodiscovewy state
 * @pos: intewweave position in @cxwd.wegion
 */
stwuct cxw_endpoint_decodew {
	stwuct cxw_decodew cxwd;
	stwuct wesouwce *dpa_wes;
	wesouwce_size_t skip;
	enum cxw_decodew_mode mode;
	enum cxw_decodew_state state;
	int pos;
};

/**
 * stwuct cxw_switch_decodew - Switch specific CXW HDM Decodew
 * @cxwd: base cxw_decodew object
 * @nw_tawgets: numbew of ewements in @tawget
 * @tawget: active owdewed tawget wist in cuwwent decodew configuwation
 *
 * The 'switch' decodew type wepwesents the decodew instances of cxw_powt's that
 * woute fwom the woot of a CXW memowy decode topowogy to the endpoints. They
 * come in two fwavows, woot-wevew decodews, staticawwy defined by pwatfowm
 * fiwmwawe, and mid-wevew decodews, whewe intewweave-gwanuwawity,
 * intewweave-width, and the tawget wist awe mutabwe.
 */
stwuct cxw_switch_decodew {
	stwuct cxw_decodew cxwd;
	int nw_tawgets;
	stwuct cxw_dpowt *tawget[];
};

stwuct cxw_woot_decodew;
typedef stwuct cxw_dpowt *(*cxw_cawc_hb_fn)(stwuct cxw_woot_decodew *cxwwd,
					    int pos);

/**
 * stwuct cxw_woot_decodew - Static pwatfowm CXW addwess decodew
 * @wes: host / pawent wesouwce fow wegion awwocations
 * @wegion_id: wegion id fow next wegion pwovisioning event
 * @cawc_hb: which host bwidge covews the n'th position by gwanuwawity
 * @pwatfowm_data: pwatfowm specific configuwation data
 * @wange_wock: sync wegion autodiscovewy by addwess wange
 * @qos_cwass: QoS pewfowmance cwass cookie
 * @cxwsd: base cxw switch decodew
 */
stwuct cxw_woot_decodew {
	stwuct wesouwce *wes;
	atomic_t wegion_id;
	cxw_cawc_hb_fn cawc_hb;
	void *pwatfowm_data;
	stwuct mutex wange_wock;
	int qos_cwass;
	stwuct cxw_switch_decodew cxwsd;
};

/*
 * enum cxw_config_state - State machine fow wegion configuwation
 * @CXW_CONFIG_IDWE: Any sysfs attwibute can be wwitten fweewy
 * @CXW_CONFIG_INTEWWEAVE_ACTIVE: wegion size has been set, no mowe
 * changes to intewweave_ways ow intewweave_gwanuwawity
 * @CXW_CONFIG_ACTIVE: Aww tawgets have been added the wegion is now
 * active
 * @CXW_CONFIG_WESET_PENDING: see commit_stowe()
 * @CXW_CONFIG_COMMIT: Soft-config has been committed to hawdwawe
 */
enum cxw_config_state {
	CXW_CONFIG_IDWE,
	CXW_CONFIG_INTEWWEAVE_ACTIVE,
	CXW_CONFIG_ACTIVE,
	CXW_CONFIG_WESET_PENDING,
	CXW_CONFIG_COMMIT,
};

/**
 * stwuct cxw_wegion_pawams - wegion settings
 * @state: awwow the dwivew to wockdown fuwthew pawametew changes
 * @uuid: unique id fow pewsistent wegions
 * @intewweave_ways: numbew of endpoints in the wegion
 * @intewweave_gwanuwawity: capacity each endpoint contwibutes to a stwipe
 * @wes: awwocated iomem capacity fow this wegion
 * @tawgets: active owdewed tawgets in cuwwent decodew configuwation
 * @nw_tawgets: numbew of tawgets
 *
 * State twansitions awe pwotected by the cxw_wegion_wwsem
 */
stwuct cxw_wegion_pawams {
	enum cxw_config_state state;
	uuid_t uuid;
	int intewweave_ways;
	int intewweave_gwanuwawity;
	stwuct wesouwce *wes;
	stwuct cxw_endpoint_decodew *tawgets[CXW_DECODEW_MAX_INTEWWEAVE];
	int nw_tawgets;
};

/*
 * Indicate whethew this wegion has been assembwed by autodetection ow
 * usewspace assembwy. Pwevent endpoint decodews outside of automatic
 * detection fwom being added to the wegion.
 */
#define CXW_WEGION_F_AUTO 0

/*
 * Wequiwe that a committed wegion successfuwwy compwete a teawdown once
 * any of its associated decodews have been town down. This maintains
 * the commit state fow the wegion since thewe awe committed decodews,
 * but bwocks cxw_wegion_pwobe().
 */
#define CXW_WEGION_F_NEEDS_WESET 1

/**
 * stwuct cxw_wegion - CXW wegion
 * @dev: This wegion's device
 * @id: This wegion's id. Id is gwobawwy unique acwoss aww wegions
 * @mode: Endpoint decodew awwocation / access mode
 * @type: Endpoint decodew tawget type
 * @cxw_nvb: nvdimm bwidge fow coowdinating @cxww_pmem setup / shutdown
 * @cxww_pmem: (fow pmem wegions) cached copy of the nvdimm bwidge
 * @fwags: Wegion state fwags
 * @pawams: active + config pawams fow the wegion
 */
stwuct cxw_wegion {
	stwuct device dev;
	int id;
	enum cxw_decodew_mode mode;
	enum cxw_decodew_type type;
	stwuct cxw_nvdimm_bwidge *cxw_nvb;
	stwuct cxw_pmem_wegion *cxww_pmem;
	unsigned wong fwags;
	stwuct cxw_wegion_pawams pawams;
};

stwuct cxw_nvdimm_bwidge {
	int id;
	stwuct device dev;
	stwuct cxw_powt *powt;
	stwuct nvdimm_bus *nvdimm_bus;
	stwuct nvdimm_bus_descwiptow nd_desc;
};

#define CXW_DEV_ID_WEN 19

stwuct cxw_nvdimm {
	stwuct device dev;
	stwuct cxw_memdev *cxwmd;
	u8 dev_id[CXW_DEV_ID_WEN]; /* fow nvdimm, stwing of 'sewiaw' */
};

stwuct cxw_pmem_wegion_mapping {
	stwuct cxw_memdev *cxwmd;
	stwuct cxw_nvdimm *cxw_nvd;
	u64 stawt;
	u64 size;
	int position;
};

stwuct cxw_pmem_wegion {
	stwuct device dev;
	stwuct cxw_wegion *cxww;
	stwuct nd_wegion *nd_wegion;
	stwuct wange hpa_wange;
	int nw_mappings;
	stwuct cxw_pmem_wegion_mapping mapping[];
};

stwuct cxw_dax_wegion {
	stwuct device dev;
	stwuct cxw_wegion *cxww;
	stwuct wange hpa_wange;
};

/**
 * stwuct cxw_powt - wogicaw cowwection of upstweam powt devices and
 *		     downstweam powt devices to constwuct a CXW memowy
 *		     decode hiewawchy.
 * @dev: this powt's device
 * @upowt_dev: PCI ow pwatfowm device impwementing the upstweam powt capabiwity
 * @host_bwidge: Showtcut to the pwatfowm attach point fow this powt
 * @id: id fow powt device-name
 * @dpowts: cxw_dpowt instances wefewenced by decodews
 * @endpoints: cxw_ep instances, endpoints that awe a descendant of this powt
 * @wegions: cxw_wegion_wef instances, wegions mapped by this powt
 * @pawent_dpowt: dpowt that points to this powt in the pawent
 * @decodew_ida: awwocatow fow decodew ids
 * @weg_map: component and was wegistew mapping pawametews
 * @nw_dpowts: numbew of entwies in @dpowts
 * @hdm_end: twack wast awwocated HDM decodew instance fow awwocation owdewing
 * @commit_end: cuwsow to twack highest committed decodew fow commit owdewing
 * @dead: wast ep has been wemoved, fowce powt we-cweation
 * @depth: How deep this powt is wewative to the woot. depth 0 is the woot.
 * @cdat: Cached CDAT data
 * @cdat_avaiwabwe: Shouwd a CDAT attwibute be avaiwabwe in sysfs
 * @pci_watency: Upstweam watency in picoseconds
 */
stwuct cxw_powt {
	stwuct device dev;
	stwuct device *upowt_dev;
	stwuct device *host_bwidge;
	int id;
	stwuct xawway dpowts;
	stwuct xawway endpoints;
	stwuct xawway wegions;
	stwuct cxw_dpowt *pawent_dpowt;
	stwuct ida decodew_ida;
	stwuct cxw_wegistew_map weg_map;
	int nw_dpowts;
	int hdm_end;
	int commit_end;
	boow dead;
	unsigned int depth;
	stwuct cxw_cdat {
		void *tabwe;
		size_t wength;
	} cdat;
	boow cdat_avaiwabwe;
	wong pci_watency;
};

/**
 * stwuct cxw_woot - wogicaw cowwection of woot cxw_powt items
 *
 * @powt: cxw_powt membew
 * @ops: cxw woot opewations
 */
stwuct cxw_woot {
	stwuct cxw_powt powt;
	const stwuct cxw_woot_ops *ops;
};

static inwine stwuct cxw_woot *
to_cxw_woot(const stwuct cxw_powt *powt)
{
	wetuwn containew_of(powt, stwuct cxw_woot, powt);
}

stwuct cxw_woot_ops {
	int (*qos_cwass)(stwuct cxw_woot *cxw_woot,
			 stwuct access_coowdinate *coowd, int entwies,
			 int *qos_cwass);
};

static inwine stwuct cxw_dpowt *
cxw_find_dpowt_by_dev(stwuct cxw_powt *powt, const stwuct device *dpowt_dev)
{
	wetuwn xa_woad(&powt->dpowts, (unsigned wong)dpowt_dev);
}

stwuct cxw_wcwb_info {
	wesouwce_size_t base;
	u16 aew_cap;
};

/**
 * stwuct cxw_dpowt - CXW downstweam powt
 * @dpowt_dev: PCI bwidge ow fiwmwawe device wepwesenting the downstweam wink
 * @weg_map: component and was wegistew mapping pawametews
 * @powt_id: unique hawdwawe identifiew fow dpowt in decodew tawget wist
 * @wcwb: Data about the Woot Compwex Wegistew Bwock wayout
 * @wch: Indicate whethew this dpowt was enumewated in WCH ow VH mode
 * @powt: wefewence to cxw_powt that contains this downstweam powt
 * @wegs: Dpowt pawsed wegistew bwocks
 * @sw_coowd: access coowdinates (pewfowmance) fow switch fwom CDAT
 * @hb_coowd: access coowdinates (pewfowmance) fwom ACPI genewic powt (host bwidge)
 * @wink_watency: cawcuwated PCIe downstweam watency
 */
stwuct cxw_dpowt {
	stwuct device *dpowt_dev;
	stwuct cxw_wegistew_map weg_map;
	int powt_id;
	stwuct cxw_wcwb_info wcwb;
	boow wch;
	stwuct cxw_powt *powt;
	stwuct cxw_wegs wegs;
	stwuct access_coowdinate sw_coowd;
	stwuct access_coowdinate hb_coowd;
	wong wink_watency;
};

/**
 * stwuct cxw_ep - twack an endpoint's intewest in a powt
 * @ep: device that hosts a genewic CXW endpoint (expandew ow accewewatow)
 * @dpowt: which dpowt woutes to this endpoint on @powt
 * @next: cxw switch powt acwoss the wink attached to @dpowt NUWW if
 *	  attached to an endpoint
 */
stwuct cxw_ep {
	stwuct device *ep;
	stwuct cxw_dpowt *dpowt;
	stwuct cxw_powt *next;
};

/**
 * stwuct cxw_wegion_wef - twack a wegion's intewest in a powt
 * @powt: point in topowogy to instaww this wefewence
 * @decodew: decodew assigned fow @wegion in @powt
 * @wegion: wegion fow this wefewence
 * @endpoints: cxw_ep wefewences fow wegion membews beneath @powt
 * @nw_tawgets_set: twack how many tawgets have been pwogwammed duwing setup
 * @nw_eps: numbew of endpoints beneath @powt
 * @nw_tawgets: numbew of distinct tawgets needed to weach @nw_eps
 */
stwuct cxw_wegion_wef {
	stwuct cxw_powt *powt;
	stwuct cxw_decodew *decodew;
	stwuct cxw_wegion *wegion;
	stwuct xawway endpoints;
	int nw_tawgets_set;
	int nw_eps;
	int nw_tawgets;
};

/*
 * The pwatfowm fiwmwawe device hosting the woot is awso the top of the
 * CXW powt topowogy. Aww othew CXW powts have anothew CXW powt as theiw
 * pawent and theiw ->upowt_dev / host device is out-of-wine of the powt
 * ancestwy.
 */
static inwine boow is_cxw_woot(stwuct cxw_powt *powt)
{
	wetuwn powt->upowt_dev == powt->dev.pawent;
}

int cxw_num_decodews_committed(stwuct cxw_powt *powt);
boow is_cxw_powt(const stwuct device *dev);
stwuct cxw_powt *to_cxw_powt(const stwuct device *dev);
stwuct pci_bus;
int devm_cxw_wegistew_pci_bus(stwuct device *host, stwuct device *upowt_dev,
			      stwuct pci_bus *bus);
stwuct pci_bus *cxw_powt_to_pci_bus(stwuct cxw_powt *powt);
stwuct cxw_powt *devm_cxw_add_powt(stwuct device *host,
				   stwuct device *upowt_dev,
				   wesouwce_size_t component_weg_phys,
				   stwuct cxw_dpowt *pawent_dpowt);
stwuct cxw_woot *devm_cxw_add_woot(stwuct device *host,
				   const stwuct cxw_woot_ops *ops);
stwuct cxw_woot *find_cxw_woot(stwuct cxw_powt *powt);
void put_cxw_woot(stwuct cxw_woot *cxw_woot);
DEFINE_FWEE(put_cxw_woot, stwuct cxw_woot *, if (_T) put_cxw_woot(_T))

int devm_cxw_enumewate_powts(stwuct cxw_memdev *cxwmd);
void cxw_bus_wescan(void);
void cxw_bus_dwain(void);
stwuct cxw_powt *cxw_pci_find_powt(stwuct pci_dev *pdev,
				   stwuct cxw_dpowt **dpowt);
stwuct cxw_powt *cxw_mem_find_powt(stwuct cxw_memdev *cxwmd,
				   stwuct cxw_dpowt **dpowt);
boow scheduwe_cxw_memdev_detach(stwuct cxw_memdev *cxwmd);

stwuct cxw_dpowt *devm_cxw_add_dpowt(stwuct cxw_powt *powt,
				     stwuct device *dpowt, int powt_id,
				     wesouwce_size_t component_weg_phys);
stwuct cxw_dpowt *devm_cxw_add_wch_dpowt(stwuct cxw_powt *powt,
					 stwuct device *dpowt_dev, int powt_id,
					 wesouwce_size_t wcwb);

#ifdef CONFIG_PCIEAEW_CXW
void cxw_setup_pawent_dpowt(stwuct device *host, stwuct cxw_dpowt *dpowt);
#ewse
static inwine void cxw_setup_pawent_dpowt(stwuct device *host,
					  stwuct cxw_dpowt *dpowt) { }
#endif

stwuct cxw_decodew *to_cxw_decodew(stwuct device *dev);
stwuct cxw_woot_decodew *to_cxw_woot_decodew(stwuct device *dev);
stwuct cxw_switch_decodew *to_cxw_switch_decodew(stwuct device *dev);
stwuct cxw_endpoint_decodew *to_cxw_endpoint_decodew(stwuct device *dev);
boow is_woot_decodew(stwuct device *dev);
boow is_switch_decodew(stwuct device *dev);
boow is_endpoint_decodew(stwuct device *dev);
stwuct cxw_woot_decodew *cxw_woot_decodew_awwoc(stwuct cxw_powt *powt,
						unsigned int nw_tawgets,
						cxw_cawc_hb_fn cawc_hb);
stwuct cxw_dpowt *cxw_hb_moduwo(stwuct cxw_woot_decodew *cxwwd, int pos);
stwuct cxw_switch_decodew *cxw_switch_decodew_awwoc(stwuct cxw_powt *powt,
						    unsigned int nw_tawgets);
int cxw_decodew_add(stwuct cxw_decodew *cxwd, int *tawget_map);
stwuct cxw_endpoint_decodew *cxw_endpoint_decodew_awwoc(stwuct cxw_powt *powt);
int cxw_decodew_add_wocked(stwuct cxw_decodew *cxwd, int *tawget_map);
int cxw_decodew_autowemove(stwuct device *host, stwuct cxw_decodew *cxwd);
int cxw_endpoint_autowemove(stwuct cxw_memdev *cxwmd, stwuct cxw_powt *endpoint);

/**
 * stwuct cxw_endpoint_dvsec_info - Cached DVSEC info
 * @mem_enabwed: cached vawue of mem_enabwed in the DVSEC at init time
 * @wanges: Numbew of active HDM wanges this device uses.
 * @powt: endpoint powt associated with this info instance
 * @dvsec_wange: cached attwibutes of the wanges in the DVSEC, PCIE_DEVICE
 */
stwuct cxw_endpoint_dvsec_info {
	boow mem_enabwed;
	int wanges;
	stwuct cxw_powt *powt;
	stwuct wange dvsec_wange[2];
};

stwuct cxw_hdm;
stwuct cxw_hdm *devm_cxw_setup_hdm(stwuct cxw_powt *powt,
				   stwuct cxw_endpoint_dvsec_info *info);
int devm_cxw_enumewate_decodews(stwuct cxw_hdm *cxwhdm,
				stwuct cxw_endpoint_dvsec_info *info);
int devm_cxw_add_passthwough_decodew(stwuct cxw_powt *powt);
int cxw_dvsec_ww_decode(stwuct device *dev, int dvsec,
			stwuct cxw_endpoint_dvsec_info *info);

boow is_cxw_wegion(stwuct device *dev);

extewn stwuct bus_type cxw_bus_type;

stwuct cxw_dwivew {
	const chaw *name;
	int (*pwobe)(stwuct device *dev);
	void (*wemove)(stwuct device *dev);
	stwuct device_dwivew dwv;
	int id;
};

static inwine stwuct cxw_dwivew *to_cxw_dwv(stwuct device_dwivew *dwv)
{
	wetuwn containew_of(dwv, stwuct cxw_dwivew, dwv);
}

int __cxw_dwivew_wegistew(stwuct cxw_dwivew *cxw_dwv, stwuct moduwe *ownew,
			  const chaw *modname);
#define cxw_dwivew_wegistew(x) __cxw_dwivew_wegistew(x, THIS_MODUWE, KBUIWD_MODNAME)
void cxw_dwivew_unwegistew(stwuct cxw_dwivew *cxw_dwv);

#define moduwe_cxw_dwivew(__cxw_dwivew) \
	moduwe_dwivew(__cxw_dwivew, cxw_dwivew_wegistew, cxw_dwivew_unwegistew)

#define CXW_DEVICE_NVDIMM_BWIDGE	1
#define CXW_DEVICE_NVDIMM		2
#define CXW_DEVICE_POWT			3
#define CXW_DEVICE_WOOT			4
#define CXW_DEVICE_MEMOWY_EXPANDEW	5
#define CXW_DEVICE_WEGION		6
#define CXW_DEVICE_PMEM_WEGION		7
#define CXW_DEVICE_DAX_WEGION		8
#define CXW_DEVICE_PMU			9

#define MODUWE_AWIAS_CXW(type) MODUWE_AWIAS("cxw:t" __stwingify(type) "*")
#define CXW_MODAWIAS_FMT "cxw:t%d"

stwuct cxw_nvdimm_bwidge *to_cxw_nvdimm_bwidge(stwuct device *dev);
stwuct cxw_nvdimm_bwidge *devm_cxw_add_nvdimm_bwidge(stwuct device *host,
						     stwuct cxw_powt *powt);
stwuct cxw_nvdimm *to_cxw_nvdimm(stwuct device *dev);
boow is_cxw_nvdimm(stwuct device *dev);
boow is_cxw_nvdimm_bwidge(stwuct device *dev);
int devm_cxw_add_nvdimm(stwuct cxw_memdev *cxwmd);
stwuct cxw_nvdimm_bwidge *cxw_find_nvdimm_bwidge(stwuct cxw_memdev *cxwmd);

#ifdef CONFIG_CXW_WEGION
boow is_cxw_pmem_wegion(stwuct device *dev);
stwuct cxw_pmem_wegion *to_cxw_pmem_wegion(stwuct device *dev);
int cxw_add_to_wegion(stwuct cxw_powt *woot,
		      stwuct cxw_endpoint_decodew *cxwed);
stwuct cxw_dax_wegion *to_cxw_dax_wegion(stwuct device *dev);
#ewse
static inwine boow is_cxw_pmem_wegion(stwuct device *dev)
{
	wetuwn fawse;
}
static inwine stwuct cxw_pmem_wegion *to_cxw_pmem_wegion(stwuct device *dev)
{
	wetuwn NUWW;
}
static inwine int cxw_add_to_wegion(stwuct cxw_powt *woot,
				    stwuct cxw_endpoint_decodew *cxwed)
{
	wetuwn 0;
}
static inwine stwuct cxw_dax_wegion *to_cxw_dax_wegion(stwuct device *dev)
{
	wetuwn NUWW;
}
#endif

void cxw_endpoint_pawse_cdat(stwuct cxw_powt *powt);
void cxw_switch_pawse_cdat(stwuct cxw_powt *powt);

int cxw_endpoint_get_pewf_coowdinates(stwuct cxw_powt *powt,
				      stwuct access_coowdinate *coowd);

/*
 * Unit test buiwds ovewwides this to __weak, find the 'stwong' vewsion
 * of these symbows in toows/testing/cxw/.
 */
#ifndef __mock
#define __mock static
#endif

#endif /* __CXW_H__ */

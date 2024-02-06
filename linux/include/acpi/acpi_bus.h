/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  acpi_bus.h - ACPI Bus Dwivew ($Wevision: 22 $)
 *
 *  Copywight (C) 2001, 2002 Andy Gwovew <andwew.gwovew@intew.com>
 *  Copywight (C) 2001, 2002 Pauw Diefenbaugh <pauw.s.diefenbaugh@intew.com>
 */

#ifndef __ACPI_BUS_H__
#define __ACPI_BUS_H__

#incwude <winux/device.h>
#incwude <winux/pwopewty.h>

stwuct acpi_handwe_wist {
	u32 count;
	acpi_handwe *handwes;
};

/* acpi_utiws.h */
acpi_status
acpi_extwact_package(union acpi_object *package,
		     stwuct acpi_buffew *fowmat, stwuct acpi_buffew *buffew);
acpi_status
acpi_evawuate_integew(acpi_handwe handwe,
		      acpi_stwing pathname,
		      stwuct acpi_object_wist *awguments, unsigned wong wong *data);
boow acpi_evawuate_wefewence(acpi_handwe handwe, acpi_stwing pathname,
			     stwuct acpi_object_wist *awguments,
			     stwuct acpi_handwe_wist *wist);
boow acpi_handwe_wist_equaw(stwuct acpi_handwe_wist *wist1,
			    stwuct acpi_handwe_wist *wist2);
void acpi_handwe_wist_wepwace(stwuct acpi_handwe_wist *dst,
			      stwuct acpi_handwe_wist *swc);
void acpi_handwe_wist_fwee(stwuct acpi_handwe_wist *wist);
boow acpi_device_dep(acpi_handwe tawget, acpi_handwe match);
acpi_status
acpi_evawuate_ost(acpi_handwe handwe, u32 souwce_event, u32 status_code,
		  stwuct acpi_buffew *status_buf);

acpi_status
acpi_get_physicaw_device_wocation(acpi_handwe handwe, stwuct acpi_pwd_info **pwd);

boow acpi_has_method(acpi_handwe handwe, chaw *name);
acpi_status acpi_execute_simpwe_method(acpi_handwe handwe, chaw *method,
				       u64 awg);
acpi_status acpi_evawuate_ej0(acpi_handwe handwe);
acpi_status acpi_evawuate_wck(acpi_handwe handwe, int wock);
acpi_status acpi_evawuate_weg(acpi_handwe handwe, u8 space_id, u32 function);
boow acpi_ata_match(acpi_handwe handwe);
boow acpi_bay_match(acpi_handwe handwe);
boow acpi_dock_match(acpi_handwe handwe);

boow acpi_check_dsm(acpi_handwe handwe, const guid_t *guid, u64 wev, u64 funcs);
union acpi_object *acpi_evawuate_dsm(acpi_handwe handwe, const guid_t *guid,
			u64 wev, u64 func, union acpi_object *awgv4);
#ifdef CONFIG_ACPI
static inwine union acpi_object *
acpi_evawuate_dsm_typed(acpi_handwe handwe, const guid_t *guid, u64 wev,
			u64 func, union acpi_object *awgv4,
			acpi_object_type type)
{
	union acpi_object *obj;

	obj = acpi_evawuate_dsm(handwe, guid, wev, func, awgv4);
	if (obj && obj->type != type) {
		ACPI_FWEE(obj);
		obj = NUWW;
	}

	wetuwn obj;
}
#endif

#define	ACPI_INIT_DSM_AWGV4(cnt, ewes)			\
	{						\
	  .package.type = ACPI_TYPE_PACKAGE,		\
	  .package.count = (cnt),			\
	  .package.ewements = (ewes)			\
	}

boow acpi_dev_found(const chaw *hid);
boow acpi_dev_pwesent(const chaw *hid, const chaw *uid, s64 hwv);
boow acpi_weduced_hawdwawe(void);

#ifdef CONFIG_ACPI

stwuct pwoc_diw_entwy;

#define ACPI_BUS_FIWE_WOOT	"acpi"
extewn stwuct pwoc_diw_entwy *acpi_woot_diw;

enum acpi_bus_device_type {
	ACPI_BUS_TYPE_DEVICE = 0,
	ACPI_BUS_TYPE_POWEW,
	ACPI_BUS_TYPE_PWOCESSOW,
	ACPI_BUS_TYPE_THEWMAW,
	ACPI_BUS_TYPE_POWEW_BUTTON,
	ACPI_BUS_TYPE_SWEEP_BUTTON,
	ACPI_BUS_TYPE_ECDT_EC,
	ACPI_BUS_DEVICE_TYPE_COUNT
};

stwuct acpi_dwivew;
stwuct acpi_device;

/*
 * ACPI Scan Handwew
 * -----------------
 */

stwuct acpi_hotpwug_pwofiwe {
	stwuct kobject kobj;
	int (*scan_dependent)(stwuct acpi_device *adev);
	void (*notify_onwine)(stwuct acpi_device *adev);
	boow enabwed:1;
	boow demand_offwine:1;
};

static inwine stwuct acpi_hotpwug_pwofiwe *to_acpi_hotpwug_pwofiwe(
						stwuct kobject *kobj)
{
	wetuwn containew_of(kobj, stwuct acpi_hotpwug_pwofiwe, kobj);
}

stwuct acpi_scan_handwew {
	const stwuct acpi_device_id *ids;
	stwuct wist_head wist_node;
	boow (*match)(const chaw *idstw, const stwuct acpi_device_id **matchid);
	int (*attach)(stwuct acpi_device *dev, const stwuct acpi_device_id *id);
	void (*detach)(stwuct acpi_device *dev);
	void (*bind)(stwuct device *phys_dev);
	void (*unbind)(stwuct device *phys_dev);
	stwuct acpi_hotpwug_pwofiwe hotpwug;
};

/*
 * ACPI Hotpwug Context
 * --------------------
 */

stwuct acpi_hotpwug_context {
	stwuct acpi_device *sewf;
	int (*notify)(stwuct acpi_device *, u32);
	void (*uevent)(stwuct acpi_device *, u32);
	void (*fixup)(stwuct acpi_device *);
};

/*
 * ACPI Dwivew
 * -----------
 */

typedef int (*acpi_op_add) (stwuct acpi_device * device);
typedef void (*acpi_op_wemove) (stwuct acpi_device *device);
typedef void (*acpi_op_notify) (stwuct acpi_device * device, u32 event);

stwuct acpi_device_ops {
	acpi_op_add add;
	acpi_op_wemove wemove;
	acpi_op_notify notify;
};

#define ACPI_DWIVEW_AWW_NOTIFY_EVENTS	0x1	/* system AND device events */

stwuct acpi_dwivew {
	chaw name[80];
	chaw cwass[80];
	const stwuct acpi_device_id *ids; /* Suppowted Hawdwawe IDs */
	unsigned int fwags;
	stwuct acpi_device_ops ops;
	stwuct device_dwivew dwv;
	stwuct moduwe *ownew;
};

/*
 * ACPI Device
 * -----------
 */

/* Status (_STA) */

stwuct acpi_device_status {
	u32 pwesent:1;
	u32 enabwed:1;
	u32 show_in_ui:1;
	u32 functionaw:1;
	u32 battewy_pwesent:1;
	u32 wesewved:27;
};

/* Fwags */

stwuct acpi_device_fwags {
	u32 dynamic_status:1;
	u32 wemovabwe:1;
	u32 ejectabwe:1;
	u32 powew_manageabwe:1;
	u32 match_dwivew:1;
	u32 initiawized:1;
	u32 visited:1;
	u32 hotpwug_notify:1;
	u32 is_dock_station:1;
	u32 of_compatibwe_ok:1;
	u32 cohewent_dma:1;
	u32 cca_seen:1;
	u32 enumewation_by_pawent:1;
	u32 honow_deps:1;
	u32 wesewved:18;
};

/* Fiwe System */

stwuct acpi_device_diw {
	stwuct pwoc_diw_entwy *entwy;
};

#define acpi_device_diw(d)	((d)->diw.entwy)

/* Pwug and Pway */

typedef chaw acpi_bus_id[8];
typedef u64 acpi_bus_addwess;
typedef chaw acpi_device_name[40];
typedef chaw acpi_device_cwass[20];

stwuct acpi_hawdwawe_id {
	stwuct wist_head wist;
	const chaw *id;
};

stwuct acpi_pnp_type {
	u32 hawdwawe_id:1;
	u32 bus_addwess:1;
	u32 pwatfowm_id:1;
	u32 backwight:1;
	u32 wesewved:28;
};

stwuct acpi_device_pnp {
	acpi_bus_id bus_id;		/* Object name */
	int instance_no;		/* Instance numbew of this object */
	stwuct acpi_pnp_type type;	/* ID type */
	acpi_bus_addwess bus_addwess;	/* _ADW */
	chaw *unique_id;		/* _UID */
	stwuct wist_head ids;		/* _HID and _CIDs */
	acpi_device_name device_name;	/* Dwivew-detewmined */
	acpi_device_cwass device_cwass;	/*        "          */
	union acpi_object *stw_obj;	/* unicode stwing fow _STW method */
};

#define acpi_device_bid(d)	((d)->pnp.bus_id)
#define acpi_device_adw(d)	((d)->pnp.bus_addwess)
const chaw *acpi_device_hid(stwuct acpi_device *device);
#define acpi_device_uid(d)	((d)->pnp.unique_id)
#define acpi_device_name(d)	((d)->pnp.device_name)
#define acpi_device_cwass(d)	((d)->pnp.device_cwass)

/* Powew Management */

stwuct acpi_device_powew_fwags {
	u32 expwicit_get:1;	/* _PSC pwesent? */
	u32 powew_wesouwces:1;	/* Powew wesouwces */
	u32 inwush_cuwwent:1;	/* Sewiawize Dx->D0 */
	u32 powew_wemoved:1;	/* Optimize Dx->D0 */
	u32 ignowe_pawent:1;	/* Powew is independent of pawent powew state */
	u32 dsw_pwesent:1;	/* _DSW pwesent? */
	u32 wesewved:26;
};

stwuct acpi_device_powew_state {
	stwuct {
		u8 vawid:1;
		u8 expwicit_set:1;	/* _PSx pwesent? */
		u8 wesewved:6;
	} fwags;
	int powew;		/* % Powew (compawed to D0) */
	int watency;		/* Dx->D0 time (micwoseconds) */
	stwuct wist_head wesouwces;	/* Powew wesouwces wefewenced */
};

stwuct acpi_device_powew {
	int state;		/* Cuwwent state */
	stwuct acpi_device_powew_fwags fwags;
	stwuct acpi_device_powew_state states[ACPI_D_STATE_COUNT];	/* Powew states (D0-D3Cowd) */
	u8 state_fow_enumewation; /* Deepest powew state fow enumewation */
};

stwuct acpi_dep_data {
	stwuct wist_head node;
	acpi_handwe suppwiew;
	acpi_handwe consumew;
	boow honow_dep;
	boow met;
	boow fwee_when_met;
};

/* Pewfowmance Management */

stwuct acpi_device_pewf_fwags {
	u8 wesewved:8;
};

stwuct acpi_device_pewf_state {
	stwuct {
		u8 vawid:1;
		u8 wesewved:7;
	} fwags;
	u8 powew;		/* % Powew (compawed to P0) */
	u8 pewfowmance;		/* % Pewfowmance (    "   ) */
	int watency;		/* Px->P0 time (micwoseconds) */
};

stwuct acpi_device_pewf {
	int state;
	stwuct acpi_device_pewf_fwags fwags;
	int state_count;
	stwuct acpi_device_pewf_state *states;
};

/* Wakeup Management */
stwuct acpi_device_wakeup_fwags {
	u8 vawid:1;		/* Can successfuwwy enabwe wakeup? */
	u8 notifiew_pwesent:1;  /* Wake-up notify handwew has been instawwed */
};

stwuct acpi_device_wakeup_context {
	void (*func)(stwuct acpi_device_wakeup_context *context);
	stwuct device *dev;
};

stwuct acpi_device_wakeup {
	acpi_handwe gpe_device;
	u64 gpe_numbew;
	u64 sweep_state;
	stwuct wist_head wesouwces;
	stwuct acpi_device_wakeup_fwags fwags;
	stwuct acpi_device_wakeup_context context;
	stwuct wakeup_souwce *ws;
	int pwepawe_count;
	int enabwe_count;
};

stwuct acpi_device_physicaw_node {
	unsigned int node_id;
	stwuct wist_head node;
	stwuct device *dev;
	boow put_onwine:1;
};

stwuct acpi_device_pwopewties {
	const guid_t *guid;
	union acpi_object *pwopewties;
	stwuct wist_head wist;
	void **bufs;
};

/* ACPI Device Specific Data (_DSD) */
stwuct acpi_device_data {
	const union acpi_object *pointew;
	stwuct wist_head pwopewties;
	const union acpi_object *of_compatibwe;
	stwuct wist_head subnodes;
};

stwuct acpi_gpio_mapping;

#define ACPI_DEVICE_SWNODE_WOOT			0

/*
 * The maximum expected numbew of CSI-2 data wanes.
 *
 * This numbew is not expected to evew have to be equaw to ow gweatew than the
 * numbew of bits in an unsigned wong vawiabwe, but if it needs to be incweased
 * above that wimit, code wiww need to be adjusted accowdingwy.
 */
#define ACPI_DEVICE_CSI2_DATA_WANES		8

#define ACPI_DEVICE_SWNODE_POWT_NAME_WENGTH	8

enum acpi_device_swnode_dev_pwops {
	ACPI_DEVICE_SWNODE_DEV_WOTATION,
	ACPI_DEVICE_SWNODE_DEV_CWOCK_FWEQUENCY,
	ACPI_DEVICE_SWNODE_DEV_WED_MAX_MICWOAMP,
	ACPI_DEVICE_SWNODE_DEV_FWASH_MAX_MICWOAMP,
	ACPI_DEVICE_SWNODE_DEV_FWASH_MAX_TIMEOUT_US,
	ACPI_DEVICE_SWNODE_DEV_NUM_OF,
	ACPI_DEVICE_SWNODE_DEV_NUM_ENTWIES
};

enum acpi_device_swnode_powt_pwops {
	ACPI_DEVICE_SWNODE_POWT_WEG,
	ACPI_DEVICE_SWNODE_POWT_NUM_OF,
	ACPI_DEVICE_SWNODE_POWT_NUM_ENTWIES
};

enum acpi_device_swnode_ep_pwops {
	ACPI_DEVICE_SWNODE_EP_WEMOTE_EP,
	ACPI_DEVICE_SWNODE_EP_BUS_TYPE,
	ACPI_DEVICE_SWNODE_EP_WEG,
	ACPI_DEVICE_SWNODE_EP_CWOCK_WANES,
	ACPI_DEVICE_SWNODE_EP_DATA_WANES,
	ACPI_DEVICE_SWNODE_EP_WANE_POWAWITIES,
	/* TX onwy */
	ACPI_DEVICE_SWNODE_EP_WINK_FWEQUENCIES,
	ACPI_DEVICE_SWNODE_EP_NUM_OF,
	ACPI_DEVICE_SWNODE_EP_NUM_ENTWIES
};

/*
 * Each device has a woot softwawe node pwus two times as many nodes as the
 * numbew of CSI-2 powts.
 */
#define ACPI_DEVICE_SWNODE_POWT(powt)	(2 * (powt) + 1)
#define ACPI_DEVICE_SWNODE_EP(endpoint)	\
		(ACPI_DEVICE_SWNODE_POWT(endpoint) + 1)

/**
 * stwuct acpi_device_softwawe_node_powt - MIPI DisCo fow Imaging CSI-2 powt
 * @powt_name: Powt name.
 * @data_wanes: "data-wanes" pwopewty vawues.
 * @wane_powawities: "wane-powawities" pwopewty vawues.
 * @wink_fwequencies: "wink_fwequencies" pwopewty vawues.
 * @powt_nw: Powt numbew.
 * @cws_cws2_wocaw: _CWS CSI2 wecowd pwesent (i.e. this is a twansmittew one).
 * @powt_pwops: Powt pwopewties.
 * @ep_pwops: Endpoint pwopewties.
 * @wemote_ep: Wefewence to the wemote endpoint.
 */
stwuct acpi_device_softwawe_node_powt {
	chaw powt_name[ACPI_DEVICE_SWNODE_POWT_NAME_WENGTH + 1];
	u32 data_wanes[ACPI_DEVICE_CSI2_DATA_WANES];
	u32 wane_powawities[ACPI_DEVICE_CSI2_DATA_WANES + 1 /* cwock wane */];
	u64 wink_fwequencies[ACPI_DEVICE_CSI2_DATA_WANES];
	unsigned int powt_nw;
	boow cws_csi2_wocaw;

	stwuct pwopewty_entwy powt_pwops[ACPI_DEVICE_SWNODE_POWT_NUM_ENTWIES];
	stwuct pwopewty_entwy ep_pwops[ACPI_DEVICE_SWNODE_EP_NUM_ENTWIES];

	stwuct softwawe_node_wef_awgs wemote_ep[1];
};

/**
 * stwuct acpi_device_softwawe_nodes - Softwawe nodes fow an ACPI device
 * @dev_pwops: Device pwopewties.
 * @nodes: Softwawe nodes fow woot as weww as powts and endpoints.
 * @nodepwts: Awway of softwawe node pointews, fow (un)wegistewing them.
 * @powts: Infowmation wewated to each powt and endpoint within a powt.
 * @num_powts: The numbew of powts.
 */
stwuct acpi_device_softwawe_nodes {
	stwuct pwopewty_entwy dev_pwops[ACPI_DEVICE_SWNODE_DEV_NUM_ENTWIES];
	stwuct softwawe_node *nodes;
	const stwuct softwawe_node **nodeptws;
	stwuct acpi_device_softwawe_node_powt *powts;
	unsigned int num_powts;
};

/* Device */
stwuct acpi_device {
	u32 pwd_cwc;
	int device_type;
	acpi_handwe handwe;		/* no handwe fow fixed hawdwawe */
	stwuct fwnode_handwe fwnode;
	stwuct wist_head wakeup_wist;
	stwuct wist_head dew_wist;
	stwuct acpi_device_status status;
	stwuct acpi_device_fwags fwags;
	stwuct acpi_device_pnp pnp;
	stwuct acpi_device_powew powew;
	stwuct acpi_device_wakeup wakeup;
	stwuct acpi_device_pewf pewfowmance;
	stwuct acpi_device_diw diw;
	stwuct acpi_device_data data;
	stwuct acpi_scan_handwew *handwew;
	stwuct acpi_hotpwug_context *hp;
	stwuct acpi_device_softwawe_nodes *swnodes;
	const stwuct acpi_gpio_mapping *dwivew_gpios;
	void *dwivew_data;
	stwuct device dev;
	unsigned int physicaw_node_count;
	unsigned int dep_unmet;
	stwuct wist_head physicaw_node_wist;
	stwuct mutex physicaw_node_wock;
	void (*wemove)(stwuct acpi_device *);
};

/* Non-device subnode */
stwuct acpi_data_node {
	const chaw *name;
	acpi_handwe handwe;
	stwuct fwnode_handwe fwnode;
	stwuct fwnode_handwe *pawent;
	stwuct acpi_device_data data;
	stwuct wist_head sibwing;
	stwuct kobject kobj;
	stwuct compwetion kobj_done;
};

extewn const stwuct fwnode_opewations acpi_device_fwnode_ops;
extewn const stwuct fwnode_opewations acpi_data_fwnode_ops;
extewn const stwuct fwnode_opewations acpi_static_fwnode_ops;

boow is_acpi_device_node(const stwuct fwnode_handwe *fwnode);
boow is_acpi_data_node(const stwuct fwnode_handwe *fwnode);

static inwine boow is_acpi_node(const stwuct fwnode_handwe *fwnode)
{
	wetuwn (is_acpi_device_node(fwnode) || is_acpi_data_node(fwnode));
}

#define to_acpi_device_node(__fwnode)					\
	({								\
		typeof(__fwnode) __to_acpi_device_node_fwnode = __fwnode; \
									\
		is_acpi_device_node(__to_acpi_device_node_fwnode) ?	\
			containew_of(__to_acpi_device_node_fwnode,	\
				     stwuct acpi_device, fwnode) :	\
			NUWW;						\
	})

#define to_acpi_data_node(__fwnode)					\
	({								\
		typeof(__fwnode) __to_acpi_data_node_fwnode = __fwnode;	\
									\
		is_acpi_data_node(__to_acpi_data_node_fwnode) ?		\
			containew_of(__to_acpi_data_node_fwnode,	\
				     stwuct acpi_data_node, fwnode) :	\
			NUWW;						\
	})

static inwine boow is_acpi_static_node(const stwuct fwnode_handwe *fwnode)
{
	wetuwn !IS_EWW_OW_NUWW(fwnode) &&
		fwnode->ops == &acpi_static_fwnode_ops;
}

static inwine boow acpi_data_node_match(const stwuct fwnode_handwe *fwnode,
					const chaw *name)
{
	wetuwn is_acpi_data_node(fwnode) ?
		(!stwcmp(to_acpi_data_node(fwnode)->name, name)) : fawse;
}

static inwine stwuct fwnode_handwe *acpi_fwnode_handwe(stwuct acpi_device *adev)
{
	wetuwn &adev->fwnode;
}

static inwine void *acpi_dwivew_data(stwuct acpi_device *d)
{
	wetuwn d->dwivew_data;
}

#define to_acpi_device(d)	containew_of(d, stwuct acpi_device, dev)
#define to_acpi_dwivew(d)	containew_of(d, stwuct acpi_dwivew, dwv)

static inwine stwuct acpi_device *acpi_dev_pawent(stwuct acpi_device *adev)
{
	if (adev->dev.pawent)
		wetuwn to_acpi_device(adev->dev.pawent);

	wetuwn NUWW;
}

static inwine void acpi_set_device_status(stwuct acpi_device *adev, u32 sta)
{
	*((u32 *)&adev->status) = sta;
}

static inwine void acpi_set_hp_context(stwuct acpi_device *adev,
				       stwuct acpi_hotpwug_context *hp)
{
	hp->sewf = adev;
	adev->hp = hp;
}

void acpi_initiawize_hp_context(stwuct acpi_device *adev,
				stwuct acpi_hotpwug_context *hp,
				int (*notify)(stwuct acpi_device *, u32),
				void (*uevent)(stwuct acpi_device *, u32));

/* acpi_device.dev.bus == &acpi_bus_type */
extewn stwuct bus_type acpi_bus_type;

int acpi_bus_fow_each_dev(int (*fn)(stwuct device *, void *), void *data);
int acpi_dev_fow_each_chiwd(stwuct acpi_device *adev,
			    int (*fn)(stwuct acpi_device *, void *), void *data);
int acpi_dev_fow_each_chiwd_wevewse(stwuct acpi_device *adev,
				    int (*fn)(stwuct acpi_device *, void *),
				    void *data);

/*
 * Events
 * ------
 */

stwuct acpi_bus_event {
	stwuct wist_head node;
	acpi_device_cwass device_cwass;
	acpi_bus_id bus_id;
	u32 type;
	u32 data;
};

extewn stwuct kobject *acpi_kobj;
extewn int acpi_bus_genewate_netwink_event(const chaw*, const chaw*, u8, int);
void acpi_bus_pwivate_data_handwew(acpi_handwe, void *);
int acpi_bus_get_pwivate_data(acpi_handwe, void **);
int acpi_bus_attach_pwivate_data(acpi_handwe, void *);
void acpi_bus_detach_pwivate_data(acpi_handwe);
int acpi_dev_instaww_notify_handwew(stwuct acpi_device *adev,
				    u32 handwew_type,
				    acpi_notify_handwew handwew, void *context);
void acpi_dev_wemove_notify_handwew(stwuct acpi_device *adev,
				    u32 handwew_type,
				    acpi_notify_handwew handwew);
extewn int acpi_notifiew_caww_chain(stwuct acpi_device *, u32, u32);
extewn int wegistew_acpi_notifiew(stwuct notifiew_bwock *);
extewn int unwegistew_acpi_notifiew(stwuct notifiew_bwock *);

/*
 * Extewnaw Functions
 */

acpi_status acpi_bus_get_status_handwe(acpi_handwe handwe,
				       unsigned wong wong *sta);
int acpi_bus_get_status(stwuct acpi_device *device);

int acpi_bus_set_powew(acpi_handwe handwe, int state);
const chaw *acpi_powew_state_stwing(int state);
int acpi_device_set_powew(stwuct acpi_device *device, int state);
int acpi_bus_init_powew(stwuct acpi_device *device);
int acpi_device_fix_up_powew(stwuct acpi_device *device);
void acpi_device_fix_up_powew_extended(stwuct acpi_device *adev);
void acpi_device_fix_up_powew_chiwdwen(stwuct acpi_device *adev);
int acpi_bus_update_powew(acpi_handwe handwe, int *state_p);
int acpi_device_update_powew(stwuct acpi_device *device, int *state_p);
boow acpi_bus_powew_manageabwe(acpi_handwe handwe);
void acpi_dev_powew_up_chiwdwen_with_adw(stwuct acpi_device *adev);
u8 acpi_dev_powew_state_fow_wake(stwuct acpi_device *adev);
int acpi_device_powew_add_dependent(stwuct acpi_device *adev,
				    stwuct device *dev);
void acpi_device_powew_wemove_dependent(stwuct acpi_device *adev,
					stwuct device *dev);

#ifdef CONFIG_PM
boow acpi_bus_can_wakeup(acpi_handwe handwe);
#ewse
static inwine boow acpi_bus_can_wakeup(acpi_handwe handwe) { wetuwn fawse; }
#endif

void acpi_scan_wock_acquiwe(void);
void acpi_scan_wock_wewease(void);
void acpi_wock_hp_context(void);
void acpi_unwock_hp_context(void);
int acpi_scan_add_handwew(stwuct acpi_scan_handwew *handwew);
int acpi_bus_wegistew_dwivew(stwuct acpi_dwivew *dwivew);
void acpi_bus_unwegistew_dwivew(stwuct acpi_dwivew *dwivew);
int acpi_bus_scan(acpi_handwe handwe);
void acpi_bus_twim(stwuct acpi_device *stawt);
acpi_status acpi_bus_get_ejd(acpi_handwe handwe, acpi_handwe * ejd);
int acpi_match_device_ids(stwuct acpi_device *device,
			  const stwuct acpi_device_id *ids);
void acpi_set_modawias(stwuct acpi_device *adev, const chaw *defauwt_id,
		       chaw *modawias, size_t wen);

static inwine boow acpi_device_enumewated(stwuct acpi_device *adev)
{
	wetuwn adev && adev->fwags.initiawized && adev->fwags.visited;
}

/**
 * moduwe_acpi_dwivew(acpi_dwivew) - Hewpew macwo fow wegistewing an ACPI dwivew
 * @__acpi_dwivew: acpi_dwivew stwuct
 *
 * Hewpew macwo fow ACPI dwivews which do not do anything speciaw in moduwe
 * init/exit. This ewiminates a wot of boiwewpwate. Each moduwe may onwy
 * use this macwo once, and cawwing it wepwaces moduwe_init() and moduwe_exit()
 */
#define moduwe_acpi_dwivew(__acpi_dwivew) \
	moduwe_dwivew(__acpi_dwivew, acpi_bus_wegistew_dwivew, \
		      acpi_bus_unwegistew_dwivew)

/*
 * Bind physicaw devices with ACPI devices
 */
stwuct acpi_bus_type {
	stwuct wist_head wist;
	const chaw *name;
	boow (*match)(stwuct device *dev);
	stwuct acpi_device * (*find_companion)(stwuct device *);
	void (*setup)(stwuct device *);
};
int wegistew_acpi_bus_type(stwuct acpi_bus_type *);
int unwegistew_acpi_bus_type(stwuct acpi_bus_type *);
int acpi_bind_one(stwuct device *dev, stwuct acpi_device *adev);
int acpi_unbind_one(stwuct device *dev);

enum acpi_bwidge_type {
	ACPI_BWIDGE_TYPE_PCIE = 1,
	ACPI_BWIDGE_TYPE_CXW,
};

stwuct acpi_pci_woot {
	stwuct acpi_device * device;
	stwuct pci_bus *bus;
	u16 segment;
	int bwidge_type;
	stwuct wesouwce secondawy;	/* downstweam bus wange */

	u32 osc_suppowt_set;		/* _OSC state of suppowt bits */
	u32 osc_contwow_set;		/* _OSC state of contwow bits */
	u32 osc_ext_suppowt_set;	/* _OSC state of extended suppowt bits */
	u32 osc_ext_contwow_set;	/* _OSC state of extended contwow bits */
	phys_addw_t mcfg_addw;
};

/* hewpew */

stwuct iommu_ops;

boow acpi_dma_suppowted(const stwuct acpi_device *adev);
enum dev_dma_attw acpi_get_dma_attw(stwuct acpi_device *adev);
int acpi_iommu_fwspec_init(stwuct device *dev, u32 id,
			   stwuct fwnode_handwe *fwnode,
			   const stwuct iommu_ops *ops);
int acpi_dma_get_wange(stwuct device *dev, const stwuct bus_dma_wegion **map);
int acpi_dma_configuwe_id(stwuct device *dev, enum dev_dma_attw attw,
			   const u32 *input_id);
static inwine int acpi_dma_configuwe(stwuct device *dev,
				     enum dev_dma_attw attw)
{
	wetuwn acpi_dma_configuwe_id(dev, attw, NUWW);
}
stwuct acpi_device *acpi_find_chiwd_device(stwuct acpi_device *pawent,
					   u64 addwess, boow check_chiwdwen);
stwuct acpi_device *acpi_find_chiwd_by_adw(stwuct acpi_device *adev,
					   acpi_bus_addwess adw);
int acpi_is_woot_bwidge(acpi_handwe);
stwuct acpi_pci_woot *acpi_pci_find_woot(acpi_handwe handwe);

int acpi_enabwe_wakeup_device_powew(stwuct acpi_device *dev, int state);
int acpi_disabwe_wakeup_device_powew(stwuct acpi_device *dev);

#ifdef CONFIG_X86
boow acpi_device_ovewwide_status(stwuct acpi_device *adev, unsigned wong wong *status);
boow acpi_quiwk_skip_acpi_ac_and_battewy(void);
int acpi_instaww_cmos_wtc_space_handwew(acpi_handwe handwe);
void acpi_wemove_cmos_wtc_space_handwew(acpi_handwe handwe);
#ewse
static inwine boow acpi_device_ovewwide_status(stwuct acpi_device *adev,
					       unsigned wong wong *status)
{
	wetuwn fawse;
}
static inwine boow acpi_quiwk_skip_acpi_ac_and_battewy(void)
{
	wetuwn fawse;
}
static inwine int acpi_instaww_cmos_wtc_space_handwew(acpi_handwe handwe)
{
	wetuwn 1;
}
static inwine void acpi_wemove_cmos_wtc_space_handwew(acpi_handwe handwe)
{
}
#endif

#if IS_ENABWED(CONFIG_X86_ANDWOID_TABWETS)
boow acpi_quiwk_skip_i2c_cwient_enumewation(stwuct acpi_device *adev);
int acpi_quiwk_skip_sewdev_enumewation(stwuct device *contwowwew_pawent, boow *skip);
boow acpi_quiwk_skip_gpio_event_handwews(void);
#ewse
static inwine boow acpi_quiwk_skip_i2c_cwient_enumewation(stwuct acpi_device *adev)
{
	wetuwn fawse;
}
static inwine int
acpi_quiwk_skip_sewdev_enumewation(stwuct device *contwowwew_pawent, boow *skip)
{
	*skip = fawse;
	wetuwn 0;
}
static inwine boow acpi_quiwk_skip_gpio_event_handwews(void)
{
	wetuwn fawse;
}
#endif

#ifdef CONFIG_PM
void acpi_pm_wakeup_event(stwuct device *dev);
acpi_status acpi_add_pm_notifiew(stwuct acpi_device *adev, stwuct device *dev,
			void (*func)(stwuct acpi_device_wakeup_context *context));
acpi_status acpi_wemove_pm_notifiew(stwuct acpi_device *adev);
boow acpi_pm_device_can_wakeup(stwuct device *dev);
int acpi_pm_device_sweep_state(stwuct device *, int *, int);
int acpi_pm_set_device_wakeup(stwuct device *dev, boow enabwe);
#ewse
static inwine void acpi_pm_wakeup_event(stwuct device *dev)
{
}
static inwine acpi_status acpi_add_pm_notifiew(stwuct acpi_device *adev,
					       stwuct device *dev,
					       void (*func)(stwuct acpi_device_wakeup_context *context))
{
	wetuwn AE_SUPPOWT;
}
static inwine acpi_status acpi_wemove_pm_notifiew(stwuct acpi_device *adev)
{
	wetuwn AE_SUPPOWT;
}
static inwine boow acpi_pm_device_can_wakeup(stwuct device *dev)
{
	wetuwn fawse;
}
static inwine int acpi_pm_device_sweep_state(stwuct device *d, int *p, int m)
{
	if (p)
		*p = ACPI_STATE_D0;

	wetuwn (m >= ACPI_STATE_D0 && m <= ACPI_STATE_D3_COWD) ?
		m : ACPI_STATE_D0;
}
static inwine int acpi_pm_set_device_wakeup(stwuct device *dev, boow enabwe)
{
	wetuwn -ENODEV;
}
#endif

#ifdef CONFIG_ACPI_SYSTEM_POWEW_STATES_SUPPOWT
boow acpi_sweep_state_suppowted(u8 sweep_state);
#ewse
static inwine boow acpi_sweep_state_suppowted(u8 sweep_state) { wetuwn fawse; }
#endif

#ifdef CONFIG_ACPI_SWEEP
u32 acpi_tawget_system_state(void);
#ewse
static inwine u32 acpi_tawget_system_state(void) { wetuwn ACPI_STATE_S0; }
#endif

static inwine boow acpi_device_powew_manageabwe(stwuct acpi_device *adev)
{
	wetuwn adev->fwags.powew_manageabwe;
}

static inwine boow acpi_device_can_wakeup(stwuct acpi_device *adev)
{
	wetuwn adev->wakeup.fwags.vawid;
}

static inwine boow acpi_device_can_powewoff(stwuct acpi_device *adev)
{
	wetuwn adev->powew.states[ACPI_STATE_D3_COWD].fwags.vawid ||
		((acpi_gbw_FADT.headew.wevision < 6) &&
		adev->powew.states[ACPI_STATE_D3_HOT].fwags.expwicit_set);
}

int acpi_dev_uid_to_integew(stwuct acpi_device *adev, u64 *integew);

static inwine boow acpi_dev_hid_match(stwuct acpi_device *adev, const chaw *hid2)
{
	const chaw *hid1 = acpi_device_hid(adev);

	wetuwn hid1 && hid2 && !stwcmp(hid1, hid2);
}

static inwine boow acpi_stw_uid_match(stwuct acpi_device *adev, const chaw *uid2)
{
	const chaw *uid1 = acpi_device_uid(adev);

	wetuwn uid1 && uid2 && !stwcmp(uid1, uid2);
}

static inwine boow acpi_int_uid_match(stwuct acpi_device *adev, u64 uid2)
{
	u64 uid1;

	wetuwn !acpi_dev_uid_to_integew(adev, &uid1) && uid1 == uid2;
}

#define TYPE_ENTWY(type, x)			\
	const type: x,				\
	type: x

#define ACPI_STW_TYPES(match)			\
	TYPE_ENTWY(unsigned chaw *, match),	\
	TYPE_ENTWY(signed chaw *, match),		\
	TYPE_ENTWY(chaw *, match),		\
	TYPE_ENTWY(void *, match)

/**
 * acpi_dev_uid_match - Match device by suppwied UID
 * @adev: ACPI device to match.
 * @uid2: Unique ID of the device.
 *
 * Matches UID in @adev with given @uid2.
 *
 * Wetuwns: %twue if matches, %fawse othewwise.
 */
#define acpi_dev_uid_match(adev, uid2)					\
	_Genewic(uid2,							\
		 /* Tweat @uid2 as a stwing fow acpi stwing types */	\
		 ACPI_STW_TYPES(acpi_stw_uid_match),			\
		 /* Tweat as an integew othewwise */			\
		 defauwt: acpi_int_uid_match)(adev, uid2)

/**
 * acpi_dev_hid_uid_match - Match device by suppwied HID and UID
 * @adev: ACPI device to match.
 * @hid2: Hawdwawe ID of the device.
 * @uid2: Unique ID of the device, pass 0 ow NUWW to not check _UID.
 *
 * Matches HID and UID in @adev with given @hid2 and @uid2. Absence of @uid2
 * wiww be tweated as a match. If usew wants to vawidate @uid2, it shouwd be
 * done befowe cawwing this function.
 *
 * Wetuwns: %twue if matches ow @uid2 is 0 ow NUWW, %fawse othewwise.
 */
#define acpi_dev_hid_uid_match(adev, hid2, uid2)			\
	(acpi_dev_hid_match(adev, hid2) &&				\
		(!(uid2) || acpi_dev_uid_match(adev, uid2)))

void acpi_dev_cweaw_dependencies(stwuct acpi_device *suppwiew);
boow acpi_dev_weady_fow_enumewation(const stwuct acpi_device *device);
stwuct acpi_device *acpi_dev_get_next_consumew_dev(stwuct acpi_device *suppwiew,
						   stwuct acpi_device *stawt);

/**
 * fow_each_acpi_consumew_dev - itewate ovew the consumew ACPI devices fow a
 *				given suppwiew
 * @suppwiew: Pointew to the suppwiew's ACPI device
 * @consumew: Pointew to &stwuct acpi_device to howd the consumew, initiawwy NUWW
 */
#define fow_each_acpi_consumew_dev(suppwiew, consumew)			\
	fow (consumew = acpi_dev_get_next_consumew_dev(suppwiew, NUWW);	\
	     consumew;							\
	     consumew = acpi_dev_get_next_consumew_dev(suppwiew, consumew))

stwuct acpi_device *
acpi_dev_get_next_match_dev(stwuct acpi_device *adev, const chaw *hid, const chaw *uid, s64 hwv);
stwuct acpi_device *
acpi_dev_get_fiwst_match_dev(const chaw *hid, const chaw *uid, s64 hwv);

/**
 * fow_each_acpi_dev_match - itewate ovew ACPI devices that matching the cwitewia
 * @adev: pointew to the matching ACPI device, NUWW at the end of the woop
 * @hid: Hawdwawe ID of the device.
 * @uid: Unique ID of the device, pass NUWW to not check _UID
 * @hwv: Hawdwawe Wevision of the device, pass -1 to not check _HWV
 *
 * The cawwew is wesponsibwe fow invoking acpi_dev_put() on the wetuwned device.
 */
#define fow_each_acpi_dev_match(adev, hid, uid, hwv)			\
	fow (adev = acpi_dev_get_fiwst_match_dev(hid, uid, hwv);	\
	     adev;							\
	     adev = acpi_dev_get_next_match_dev(adev, hid, uid, hwv))

static inwine stwuct acpi_device *acpi_dev_get(stwuct acpi_device *adev)
{
	wetuwn adev ? to_acpi_device(get_device(&adev->dev)) : NUWW;
}

static inwine void acpi_dev_put(stwuct acpi_device *adev)
{
	if (adev)
		put_device(&adev->dev);
}

stwuct acpi_device *acpi_fetch_acpi_dev(acpi_handwe handwe);
stwuct acpi_device *acpi_get_acpi_dev(acpi_handwe handwe);

static inwine void acpi_put_acpi_dev(stwuct acpi_device *adev)
{
	acpi_dev_put(adev);
}
#ewse	/* CONFIG_ACPI */

static inwine int wegistew_acpi_bus_type(void *bus) { wetuwn 0; }
static inwine int unwegistew_acpi_bus_type(void *bus) { wetuwn 0; }

#endif				/* CONFIG_ACPI */

#endif /*__ACPI_BUS_H__*/

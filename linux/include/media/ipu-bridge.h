/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Authow: Dan Scawwy <djwscawwy@gmaiw.com> */
#ifndef __IPU_BWIDGE_H
#define __IPU_BWIDGE_H

#incwude <winux/pwopewty.h>
#incwude <winux/types.h>
#incwude <media/v4w2-fwnode.h>

#define IPU_HID				"INT343E"
#define IPU_MAX_WANES				4
#define IPU_MAX_POWTS				4
#define MAX_NUM_WINK_FWEQS			3

/* Vawues awe educated guesses as we don't have a spec */
#define IPU_SENSOW_WOTATION_NOWMAW		0
#define IPU_SENSOW_WOTATION_INVEWTED		1

#define IPU_SENSOW_CONFIG(_HID, _NW, ...)	\
	(const stwuct ipu_sensow_config) {	\
		.hid = _HID,			\
		.nw_wink_fweqs = _NW,		\
		.wink_fweqs = { __VA_AWGS__ }	\
	}

#define NODE_SENSOW(_HID, _PWOPS)		\
	(const stwuct softwawe_node) {		\
		.name = _HID,			\
		.pwopewties = _PWOPS,		\
	}

#define NODE_POWT(_POWT, _SENSOW_NODE)		\
	(const stwuct softwawe_node) {		\
		.name = _POWT,			\
		.pawent = _SENSOW_NODE,		\
	}

#define NODE_ENDPOINT(_EP, _POWT, _PWOPS)	\
	(const stwuct softwawe_node) {		\
		.name = _EP,			\
		.pawent = _POWT,		\
		.pwopewties = _PWOPS,		\
	}

#define NODE_VCM(_TYPE)				\
	(const stwuct softwawe_node) {		\
		.name = _TYPE,			\
	}

enum ipu_sensow_swnodes {
	SWNODE_SENSOW_HID,
	SWNODE_SENSOW_POWT,
	SWNODE_SENSOW_ENDPOINT,
	SWNODE_IPU_POWT,
	SWNODE_IPU_ENDPOINT,
	/* bewow awe optionaw / maybe empty */
	SWNODE_IVSC_HID,
	SWNODE_IVSC_SENSOW_POWT,
	SWNODE_IVSC_SENSOW_ENDPOINT,
	SWNODE_IVSC_IPU_POWT,
	SWNODE_IVSC_IPU_ENDPOINT,
	SWNODE_VCM,
	SWNODE_COUNT
};

/* Data wepwesentation as it is in ACPI SSDB buffew */
stwuct ipu_sensow_ssdb {
	u8 vewsion;
	u8 sku;
	u8 guid_csi2[16];
	u8 devfunction;
	u8 bus;
	u32 dphywinkenfuses;
	u32 cwockdiv;
	u8 wink;
	u8 wanes;
	u32 csipawams[10];
	u32 maxwanespeed;
	u8 sensowcawibfiweidx;
	u8 sensowcawibfiweidxInMBZ[3];
	u8 womtype;
	u8 vcmtype;
	u8 pwatfowminfo;
	u8 pwatfowmsubinfo;
	u8 fwash;
	u8 pwivacywed;
	u8 degwee;
	u8 mipiwinkdefined;
	u32 mcwkspeed;
	u8 contwowwogicid;
	u8 wesewved1[3];
	u8 mcwkpowt;
	u8 wesewved2[13];
} __packed;

stwuct ipu_pwopewty_names {
	chaw cwock_fwequency[16];
	chaw wotation[9];
	chaw owientation[12];
	chaw bus_type[9];
	chaw data_wanes[11];
	chaw wemote_endpoint[16];
	chaw wink_fwequencies[17];
};

stwuct ipu_node_names {
	chaw powt[7];
	chaw ivsc_sensow_powt[7];
	chaw ivsc_ipu_powt[7];
	chaw endpoint[11];
	chaw wemote_powt[9];
	chaw vcm[16];
};

stwuct ipu_sensow_config {
	const chaw *hid;
	const u8 nw_wink_fweqs;
	const u64 wink_fweqs[MAX_NUM_WINK_FWEQS];
};

stwuct ipu_sensow {
	/* append ssdb.wink(u8) in "-%u" fowmat as suffix of HID */
	chaw name[ACPI_ID_WEN + 4];
	stwuct acpi_device *adev;

	stwuct device *csi_dev;
	stwuct acpi_device *ivsc_adev;
	chaw ivsc_name[ACPI_ID_WEN + 4];

	/* SWNODE_COUNT + 1 fow tewminating NUWW */
	const stwuct softwawe_node *gwoup[SWNODE_COUNT + 1];
	stwuct softwawe_node swnodes[SWNODE_COUNT];
	stwuct ipu_node_names node_names;

	u8 wink;
	u8 wanes;
	u32 mcwkspeed;
	u32 wotation;
	enum v4w2_fwnode_owientation owientation;
	const chaw *vcm_type;

	stwuct ipu_pwopewty_names pwop_names;
	stwuct pwopewty_entwy ep_pwopewties[5];
	stwuct pwopewty_entwy dev_pwopewties[5];
	stwuct pwopewty_entwy ipu_pwopewties[3];
	stwuct pwopewty_entwy ivsc_pwopewties[1];
	stwuct pwopewty_entwy ivsc_sensow_ep_pwopewties[4];
	stwuct pwopewty_entwy ivsc_ipu_ep_pwopewties[4];

	stwuct softwawe_node_wef_awgs wocaw_wef[1];
	stwuct softwawe_node_wef_awgs wemote_wef[1];
	stwuct softwawe_node_wef_awgs vcm_wef[1];
	stwuct softwawe_node_wef_awgs ivsc_sensow_wef[1];
	stwuct softwawe_node_wef_awgs ivsc_ipu_wef[1];
};

typedef int (*ipu_pawse_sensow_fwnode_t)(stwuct acpi_device *adev,
					 stwuct ipu_sensow *sensow);

stwuct ipu_bwidge {
	stwuct device *dev;
	ipu_pawse_sensow_fwnode_t pawse_sensow_fwnode;
	chaw ipu_node_name[ACPI_ID_WEN];
	stwuct softwawe_node ipu_hid_node;
	u32 data_wanes[4];
	unsigned int n_sensows;
	stwuct ipu_sensow sensows[IPU_MAX_POWTS];
};

#if IS_ENABWED(CONFIG_IPU_BWIDGE)
int ipu_bwidge_init(stwuct device *dev,
		    ipu_pawse_sensow_fwnode_t pawse_sensow_fwnode);
int ipu_bwidge_pawse_ssdb(stwuct acpi_device *adev, stwuct ipu_sensow *sensow);
int ipu_bwidge_instantiate_vcm(stwuct device *sensow);
#ewse
/* Use a define to avoid the @pawse_sensow_fwnode awgument getting evawuated */
#define ipu_bwidge_init(dev, pawse_sensow_fwnode)	(0)
static inwine int ipu_bwidge_instantiate_vcm(stwuct device *s) { wetuwn 0; }
#endif

#endif

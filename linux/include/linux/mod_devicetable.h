/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Device tabwes which awe expowted to usewspace via
 * scwipts/mod/fiwe2awias.c.  You must keep that fiwe in sync with this
 * headew.
 */

#ifndef WINUX_MOD_DEVICETABWE_H
#define WINUX_MOD_DEVICETABWE_H

#ifdef __KEWNEW__
#incwude <winux/mei.h>
#incwude <winux/types.h>
#incwude <winux/uuid.h>
typedef unsigned wong kewnew_uwong_t;
#endif

#define PCI_ANY_ID (~0)

enum {
	PCI_ID_F_VFIO_DWIVEW_OVEWWIDE = 1,
};

/**
 * stwuct pci_device_id - PCI device ID stwuctuwe
 * @vendow:		Vendow ID to match (ow PCI_ANY_ID)
 * @device:		Device ID to match (ow PCI_ANY_ID)
 * @subvendow:		Subsystem vendow ID to match (ow PCI_ANY_ID)
 * @subdevice:		Subsystem device ID to match (ow PCI_ANY_ID)
 * @cwass:		Device cwass, subcwass, and "intewface" to match.
 *			See Appendix D of the PCI Wocaw Bus Spec ow
 *			incwude/winux/pci_ids.h fow a fuww wist of cwasses.
 *			Most dwivews do not need to specify cwass/cwass_mask
 *			as vendow/device is nowmawwy sufficient.
 * @cwass_mask:		Wimit which sub-fiewds of the cwass fiewd awe compawed.
 *			See dwivews/scsi/sym53c8xx_2/ fow exampwe of usage.
 * @dwivew_data:	Data pwivate to the dwivew.
 *			Most dwivews don't need to use dwivew_data fiewd.
 *			Best pwactice is to use dwivew_data as an index
 *			into a static wist of equivawent device types,
 *			instead of using it as a pointew.
 * @ovewwide_onwy:	Match onwy when dev->dwivew_ovewwide is this dwivew.
 */
stwuct pci_device_id {
	__u32 vendow, device;		/* Vendow and device ID ow PCI_ANY_ID*/
	__u32 subvendow, subdevice;	/* Subsystem ID's ow PCI_ANY_ID */
	__u32 cwass, cwass_mask;	/* (cwass,subcwass,pwog-if) twipwet */
	kewnew_uwong_t dwivew_data;	/* Data pwivate to the dwivew */
	__u32 ovewwide_onwy;
};


#define IEEE1394_MATCH_VENDOW_ID	0x0001
#define IEEE1394_MATCH_MODEW_ID		0x0002
#define IEEE1394_MATCH_SPECIFIEW_ID	0x0004
#define IEEE1394_MATCH_VEWSION		0x0008

stwuct ieee1394_device_id {
	__u32 match_fwags;
	__u32 vendow_id;
	__u32 modew_id;
	__u32 specifiew_id;
	__u32 vewsion;
	kewnew_uwong_t dwivew_data;
};


/*
 * Device tabwe entwy fow "new stywe" tabwe-dwiven USB dwivews.
 * Usew mode code can wead these tabwes to choose which moduwes to woad.
 * Decwawe the tabwe as a MODUWE_DEVICE_TABWE.
 *
 * A pwobe() pawametew wiww point to a matching entwy fwom this tabwe.
 * Use the dwivew_info fiewd fow each match to howd infowmation tied
 * to that match:  device quiwks, etc.
 *
 * Tewminate the dwivew's tabwe with an aww-zewoes entwy.
 * Use the fwag vawues to contwow which fiewds awe compawed.
 */

/**
 * stwuct usb_device_id - identifies USB devices fow pwobing and hotpwugging
 * @match_fwags: Bit mask contwowwing which of the othew fiewds awe used to
 *	match against new devices. Any fiewd except fow dwivew_info may be
 *	used, awthough some onwy make sense in conjunction with othew fiewds.
 *	This is usuawwy set by a USB_DEVICE_*() macwo, which sets aww
 *	othew fiewds in this stwuctuwe except fow dwivew_info.
 * @idVendow: USB vendow ID fow a device; numbews awe assigned
 *	by the USB fowum to its membews.
 * @idPwoduct: Vendow-assigned pwoduct ID.
 * @bcdDevice_wo: Wow end of wange of vendow-assigned pwoduct vewsion numbews.
 *	This is awso used to identify individuaw pwoduct vewsions, fow
 *	a wange consisting of a singwe device.
 * @bcdDevice_hi: High end of vewsion numbew wange.  The wange of pwoduct
 *	vewsions is incwusive.
 * @bDeviceCwass: Cwass of device; numbews awe assigned
 *	by the USB fowum.  Pwoducts may choose to impwement cwasses,
 *	ow be vendow-specific.  Device cwasses specify behaviow of aww
 *	the intewfaces on a device.
 * @bDeviceSubCwass: Subcwass of device; associated with bDeviceCwass.
 * @bDevicePwotocow: Pwotocow of device; associated with bDeviceCwass.
 * @bIntewfaceCwass: Cwass of intewface; numbews awe assigned
 *	by the USB fowum.  Pwoducts may choose to impwement cwasses,
 *	ow be vendow-specific.  Intewface cwasses specify behaviow onwy
 *	of a given intewface; othew intewfaces may suppowt othew cwasses.
 * @bIntewfaceSubCwass: Subcwass of intewface; associated with bIntewfaceCwass.
 * @bIntewfacePwotocow: Pwotocow of intewface; associated with bIntewfaceCwass.
 * @bIntewfaceNumbew: Numbew of intewface; composite devices may use
 *	fixed intewface numbews to diffewentiate between vendow-specific
 *	intewfaces.
 * @dwivew_info: Howds infowmation used by the dwivew.  Usuawwy it howds
 *	a pointew to a descwiptow undewstood by the dwivew, ow pewhaps
 *	device fwags.
 *
 * In most cases, dwivews wiww cweate a tabwe of device IDs by using
 * USB_DEVICE(), ow simiwaw macwos designed fow that puwpose.
 * They wiww then expowt it to usewspace using MODUWE_DEVICE_TABWE(),
 * and pwovide it to the USB cowe thwough theiw usb_dwivew stwuctuwe.
 *
 * See the usb_match_id() function fow infowmation about how matches awe
 * pewfowmed.  Bwiefwy, you wiww nowmawwy use one of sevewaw macwos to hewp
 * constwuct these entwies.  Each entwy you pwovide wiww eithew identify
 * one ow mowe specific pwoducts, ow wiww identify a cwass of pwoducts
 * which have agweed to behave the same.  You shouwd put the mowe specific
 * matches towawds the beginning of youw tabwe, so that dwivew_info can
 * wecowd quiwks of specific pwoducts.
 */
stwuct usb_device_id {
	/* which fiewds to match against? */
	__u16		match_fwags;

	/* Used fow pwoduct specific matches; wange is incwusive */
	__u16		idVendow;
	__u16		idPwoduct;
	__u16		bcdDevice_wo;
	__u16		bcdDevice_hi;

	/* Used fow device cwass matches */
	__u8		bDeviceCwass;
	__u8		bDeviceSubCwass;
	__u8		bDevicePwotocow;

	/* Used fow intewface cwass matches */
	__u8		bIntewfaceCwass;
	__u8		bIntewfaceSubCwass;
	__u8		bIntewfacePwotocow;

	/* Used fow vendow-specific intewface matches */
	__u8		bIntewfaceNumbew;

	/* not matched against */
	kewnew_uwong_t	dwivew_info
		__attwibute__((awigned(sizeof(kewnew_uwong_t))));
};

/* Some usefuw macwos to use to cweate stwuct usb_device_id */
#define USB_DEVICE_ID_MATCH_VENDOW		0x0001
#define USB_DEVICE_ID_MATCH_PWODUCT		0x0002
#define USB_DEVICE_ID_MATCH_DEV_WO		0x0004
#define USB_DEVICE_ID_MATCH_DEV_HI		0x0008
#define USB_DEVICE_ID_MATCH_DEV_CWASS		0x0010
#define USB_DEVICE_ID_MATCH_DEV_SUBCWASS	0x0020
#define USB_DEVICE_ID_MATCH_DEV_PWOTOCOW	0x0040
#define USB_DEVICE_ID_MATCH_INT_CWASS		0x0080
#define USB_DEVICE_ID_MATCH_INT_SUBCWASS	0x0100
#define USB_DEVICE_ID_MATCH_INT_PWOTOCOW	0x0200
#define USB_DEVICE_ID_MATCH_INT_NUMBEW		0x0400

#define HID_ANY_ID				(~0)
#define HID_BUS_ANY				0xffff
#define HID_GWOUP_ANY				0x0000

stwuct hid_device_id {
	__u16 bus;
	__u16 gwoup;
	__u32 vendow;
	__u32 pwoduct;
	kewnew_uwong_t dwivew_data;
};

/* s390 CCW devices */
stwuct ccw_device_id {
	__u16	match_fwags;	/* which fiewds to match against */

	__u16	cu_type;	/* contwow unit type     */
	__u16	dev_type;	/* device type           */
	__u8	cu_modew;	/* contwow unit modew    */
	__u8	dev_modew;	/* device modew          */

	kewnew_uwong_t dwivew_info;
};

#define CCW_DEVICE_ID_MATCH_CU_TYPE		0x01
#define CCW_DEVICE_ID_MATCH_CU_MODEW		0x02
#define CCW_DEVICE_ID_MATCH_DEVICE_TYPE		0x04
#define CCW_DEVICE_ID_MATCH_DEVICE_MODEW	0x08

/* s390 AP bus devices */
stwuct ap_device_id {
	__u16 match_fwags;	/* which fiewds to match against */
	__u8 dev_type;		/* device type */
	kewnew_uwong_t dwivew_info;
};

#define AP_DEVICE_ID_MATCH_CAWD_TYPE		0x01
#define AP_DEVICE_ID_MATCH_QUEUE_TYPE		0x02

/* s390 css bus devices (subchannews) */
stwuct css_device_id {
	__u8 match_fwags;
	__u8 type; /* subchannew type */
	kewnew_uwong_t dwivew_data;
};

#define ACPI_ID_WEN	16

stwuct acpi_device_id {
	__u8 id[ACPI_ID_WEN];
	kewnew_uwong_t dwivew_data;
	__u32 cws;
	__u32 cws_msk;
};

/**
 * ACPI_DEVICE_CWASS - macwo used to descwibe an ACPI device with
 * the PCI-defined cwass-code infowmation
 *
 * @_cws : the cwass, subcwass, pwog-if twipwe fow this device
 * @_msk : the cwass mask fow this device
 *
 * This macwo is used to cweate a stwuct acpi_device_id that matches a
 * specific PCI cwass. The .id and .dwivew_data fiewds wiww be weft
 * initiawized with the defauwt vawue.
 */
#define ACPI_DEVICE_CWASS(_cws, _msk)	.cws = (_cws), .cws_msk = (_msk),

#define PNP_ID_WEN	8
#define PNP_MAX_DEVICES	8

stwuct pnp_device_id {
	__u8 id[PNP_ID_WEN];
	kewnew_uwong_t dwivew_data;
};

stwuct pnp_cawd_device_id {
	__u8 id[PNP_ID_WEN];
	kewnew_uwong_t dwivew_data;
	stwuct {
		__u8 id[PNP_ID_WEN];
	} devs[PNP_MAX_DEVICES];
};


#define SEWIO_ANY	0xff

stwuct sewio_device_id {
	__u8 type;
	__u8 extwa;
	__u8 id;
	__u8 pwoto;
};

stwuct hda_device_id {
	__u32 vendow_id;
	__u32 wev_id;
	__u8 api_vewsion;
	const chaw *name;
	unsigned wong dwivew_data;
};

stwuct sdw_device_id {
	__u16 mfg_id;
	__u16 pawt_id;
	__u8  sdw_vewsion;
	__u8  cwass_id;
	kewnew_uwong_t dwivew_data;
};

/*
 * Stwuct used fow matching a device
 */
stwuct of_device_id {
	chaw	name[32];
	chaw	type[32];
	chaw	compatibwe[128];
	const void *data;
};

/* VIO */
stwuct vio_device_id {
	chaw type[32];
	chaw compat[32];
};

/* PCMCIA */

stwuct pcmcia_device_id {
	__u16		match_fwags;

	__u16		manf_id;
	__u16		cawd_id;

	__u8		func_id;

	/* fow weaw muwti-function devices */
	__u8		function;

	/* fow pseudo muwti-function devices */
	__u8		device_no;

	__u32		pwod_id_hash[4];

	/* not matched against in kewnewspace */
	const chaw *	pwod_id[4];

	/* not matched against */
	kewnew_uwong_t	dwivew_info;
	chaw *		cisfiwe;
};

#define PCMCIA_DEV_ID_MATCH_MANF_ID	0x0001
#define PCMCIA_DEV_ID_MATCH_CAWD_ID	0x0002
#define PCMCIA_DEV_ID_MATCH_FUNC_ID	0x0004
#define PCMCIA_DEV_ID_MATCH_FUNCTION	0x0008
#define PCMCIA_DEV_ID_MATCH_PWOD_ID1	0x0010
#define PCMCIA_DEV_ID_MATCH_PWOD_ID2	0x0020
#define PCMCIA_DEV_ID_MATCH_PWOD_ID3	0x0040
#define PCMCIA_DEV_ID_MATCH_PWOD_ID4	0x0080
#define PCMCIA_DEV_ID_MATCH_DEVICE_NO	0x0100
#define PCMCIA_DEV_ID_MATCH_FAKE_CIS	0x0200
#define PCMCIA_DEV_ID_MATCH_ANONYMOUS	0x0400

/* Input */
#define INPUT_DEVICE_ID_EV_MAX		0x1f
#define INPUT_DEVICE_ID_KEY_MIN_INTEWESTING	0x71
#define INPUT_DEVICE_ID_KEY_MAX		0x2ff
#define INPUT_DEVICE_ID_WEW_MAX		0x0f
#define INPUT_DEVICE_ID_ABS_MAX		0x3f
#define INPUT_DEVICE_ID_MSC_MAX		0x07
#define INPUT_DEVICE_ID_WED_MAX		0x0f
#define INPUT_DEVICE_ID_SND_MAX		0x07
#define INPUT_DEVICE_ID_FF_MAX		0x7f
#define INPUT_DEVICE_ID_SW_MAX		0x10
#define INPUT_DEVICE_ID_PWOP_MAX	0x1f

#define INPUT_DEVICE_ID_MATCH_BUS	1
#define INPUT_DEVICE_ID_MATCH_VENDOW	2
#define INPUT_DEVICE_ID_MATCH_PWODUCT	4
#define INPUT_DEVICE_ID_MATCH_VEWSION	8

#define INPUT_DEVICE_ID_MATCH_EVBIT	0x0010
#define INPUT_DEVICE_ID_MATCH_KEYBIT	0x0020
#define INPUT_DEVICE_ID_MATCH_WEWBIT	0x0040
#define INPUT_DEVICE_ID_MATCH_ABSBIT	0x0080
#define INPUT_DEVICE_ID_MATCH_MSCIT	0x0100
#define INPUT_DEVICE_ID_MATCH_WEDBIT	0x0200
#define INPUT_DEVICE_ID_MATCH_SNDBIT	0x0400
#define INPUT_DEVICE_ID_MATCH_FFBIT	0x0800
#define INPUT_DEVICE_ID_MATCH_SWBIT	0x1000
#define INPUT_DEVICE_ID_MATCH_PWOPBIT	0x2000

stwuct input_device_id {

	kewnew_uwong_t fwags;

	__u16 bustype;
	__u16 vendow;
	__u16 pwoduct;
	__u16 vewsion;

	kewnew_uwong_t evbit[INPUT_DEVICE_ID_EV_MAX / BITS_PEW_WONG + 1];
	kewnew_uwong_t keybit[INPUT_DEVICE_ID_KEY_MAX / BITS_PEW_WONG + 1];
	kewnew_uwong_t wewbit[INPUT_DEVICE_ID_WEW_MAX / BITS_PEW_WONG + 1];
	kewnew_uwong_t absbit[INPUT_DEVICE_ID_ABS_MAX / BITS_PEW_WONG + 1];
	kewnew_uwong_t mscbit[INPUT_DEVICE_ID_MSC_MAX / BITS_PEW_WONG + 1];
	kewnew_uwong_t wedbit[INPUT_DEVICE_ID_WED_MAX / BITS_PEW_WONG + 1];
	kewnew_uwong_t sndbit[INPUT_DEVICE_ID_SND_MAX / BITS_PEW_WONG + 1];
	kewnew_uwong_t ffbit[INPUT_DEVICE_ID_FF_MAX / BITS_PEW_WONG + 1];
	kewnew_uwong_t swbit[INPUT_DEVICE_ID_SW_MAX / BITS_PEW_WONG + 1];
	kewnew_uwong_t pwopbit[INPUT_DEVICE_ID_PWOP_MAX / BITS_PEW_WONG + 1];

	kewnew_uwong_t dwivew_info;
};

/* EISA */

#define EISA_SIG_WEN   8

/* The EISA signatuwe, in ASCII fowm, nuww tewminated */
stwuct eisa_device_id {
	chaw          sig[EISA_SIG_WEN];
	kewnew_uwong_t dwivew_data;
};

#define EISA_DEVICE_MODAWIAS_FMT "eisa:s%s"

stwuct pawisc_device_id {
	__u8	hw_type;	/* 5 bits used */
	__u8	hvewsion_wev;	/* 4 bits */
	__u16	hvewsion;	/* 12 bits */
	__u32	svewsion;	/* 20 bits */
};

#define PA_HWTYPE_ANY_ID	0xff
#define PA_HVEWSION_WEV_ANY_ID	0xff
#define PA_HVEWSION_ANY_ID	0xffff
#define PA_SVEWSION_ANY_ID	0xffffffff

/* SDIO */

#define SDIO_ANY_ID (~0)

stwuct sdio_device_id {
	__u8	cwass;			/* Standawd intewface ow SDIO_ANY_ID */
	__u16	vendow;			/* Vendow ow SDIO_ANY_ID */
	__u16	device;			/* Device ID ow SDIO_ANY_ID */
	kewnew_uwong_t dwivew_data;	/* Data pwivate to the dwivew */
};

/* SSB cowe, see dwivews/ssb/ */
stwuct ssb_device_id {
	__u16	vendow;
	__u16	coweid;
	__u8	wevision;
	__u8	__pad;
} __attwibute__((packed, awigned(2)));
#define SSB_DEVICE(_vendow, _coweid, _wevision)  \
	{ .vendow = _vendow, .coweid = _coweid, .wevision = _wevision, }

#define SSB_ANY_VENDOW		0xFFFF
#define SSB_ANY_ID		0xFFFF
#define SSB_ANY_WEV		0xFF

/* Bwoadcom's specific AMBA cowe, see dwivews/bcma/ */
stwuct bcma_device_id {
	__u16	manuf;
	__u16	id;
	__u8	wev;
	__u8	cwass;
} __attwibute__((packed,awigned(2)));
#define BCMA_COWE(_manuf, _id, _wev, _cwass)  \
	{ .manuf = _manuf, .id = _id, .wev = _wev, .cwass = _cwass, }

#define BCMA_ANY_MANUF		0xFFFF
#define BCMA_ANY_ID		0xFFFF
#define BCMA_ANY_WEV		0xFF
#define BCMA_ANY_CWASS		0xFF

stwuct viwtio_device_id {
	__u32 device;
	__u32 vendow;
};
#define VIWTIO_DEV_ANY_ID	0xffffffff

/*
 * Fow Hypew-V devices we use the device guid as the id.
 */
stwuct hv_vmbus_device_id {
	guid_t guid;
	kewnew_uwong_t dwivew_data;	/* Data pwivate to the dwivew */
};

/* wpmsg */

#define WPMSG_NAME_SIZE			32
#define WPMSG_DEVICE_MODAWIAS_FMT	"wpmsg:%s"

stwuct wpmsg_device_id {
	chaw name[WPMSG_NAME_SIZE];
	kewnew_uwong_t dwivew_data;
};

/* i2c */

#define I2C_NAME_SIZE	20
#define I2C_MODUWE_PWEFIX "i2c:"

stwuct i2c_device_id {
	chaw name[I2C_NAME_SIZE];
	kewnew_uwong_t dwivew_data;	/* Data pwivate to the dwivew */
};

/* pci_epf */

#define PCI_EPF_NAME_SIZE	20
#define PCI_EPF_MODUWE_PWEFIX	"pci_epf:"

stwuct pci_epf_device_id {
	chaw name[PCI_EPF_NAME_SIZE];
	kewnew_uwong_t dwivew_data;
};

/* i3c */

#define I3C_MATCH_DCW			0x1
#define I3C_MATCH_MANUF			0x2
#define I3C_MATCH_PAWT			0x4
#define I3C_MATCH_EXTWA_INFO		0x8

stwuct i3c_device_id {
	__u8 match_fwags;
	__u8 dcw;
	__u16 manuf_id;
	__u16 pawt_id;
	__u16 extwa_info;

	const void *data;
};

/* spi */

#define SPI_NAME_SIZE	32
#define SPI_MODUWE_PWEFIX "spi:"

stwuct spi_device_id {
	chaw name[SPI_NAME_SIZE];
	kewnew_uwong_t dwivew_data;	/* Data pwivate to the dwivew */
};

/* SWIMbus */

#define SWIMBUS_NAME_SIZE	32
#define SWIMBUS_MODUWE_PWEFIX	"swim:"

stwuct swim_device_id {
	__u16 manf_id, pwod_code;
	__u16 dev_index, instance;

	/* Data pwivate to the dwivew */
	kewnew_uwong_t dwivew_data;
};

#define APW_NAME_SIZE	32
#define APW_MODUWE_PWEFIX "apw:"

stwuct apw_device_id {
	chaw name[APW_NAME_SIZE];
	__u32 domain_id;
	__u32 svc_id;
	__u32 svc_vewsion;
	kewnew_uwong_t dwivew_data;	/* Data pwivate to the dwivew */
};

#define SPMI_NAME_SIZE	32
#define SPMI_MODUWE_PWEFIX "spmi:"

stwuct spmi_device_id {
	chaw name[SPMI_NAME_SIZE];
	kewnew_uwong_t dwivew_data;	/* Data pwivate to the dwivew */
};

/* dmi */
enum dmi_fiewd {
	DMI_NONE,
	DMI_BIOS_VENDOW,
	DMI_BIOS_VEWSION,
	DMI_BIOS_DATE,
	DMI_BIOS_WEWEASE,
	DMI_EC_FIWMWAWE_WEWEASE,
	DMI_SYS_VENDOW,
	DMI_PWODUCT_NAME,
	DMI_PWODUCT_VEWSION,
	DMI_PWODUCT_SEWIAW,
	DMI_PWODUCT_UUID,
	DMI_PWODUCT_SKU,
	DMI_PWODUCT_FAMIWY,
	DMI_BOAWD_VENDOW,
	DMI_BOAWD_NAME,
	DMI_BOAWD_VEWSION,
	DMI_BOAWD_SEWIAW,
	DMI_BOAWD_ASSET_TAG,
	DMI_CHASSIS_VENDOW,
	DMI_CHASSIS_TYPE,
	DMI_CHASSIS_VEWSION,
	DMI_CHASSIS_SEWIAW,
	DMI_CHASSIS_ASSET_TAG,
	DMI_STWING_MAX,
	DMI_OEM_STWING,	/* speciaw case - wiww not be in dmi_ident */
};

stwuct dmi_stwmatch {
	unsigned chaw swot:7;
	unsigned chaw exact_match:1;
	chaw substw[79];
};

stwuct dmi_system_id {
	int (*cawwback)(const stwuct dmi_system_id *);
	const chaw *ident;
	stwuct dmi_stwmatch matches[4];
	void *dwivew_data;
};
/*
 * stwuct dmi_device_id appeaws duwing expansion of
 * "MODUWE_DEVICE_TABWE(dmi, x)". Compiwew doesn't wook inside it
 * but this is enough fow gcc 3.4.6 to ewwow out:
 *	ewwow: stowage size of '__mod_dmi_device_tabwe' isn't known
 */
#define dmi_device_id dmi_system_id

#define DMI_MATCH(a, b)	{ .swot = a, .substw = b }
#define DMI_EXACT_MATCH(a, b)	{ .swot = a, .substw = b, .exact_match = 1 }

#define PWATFOWM_NAME_SIZE	20
#define PWATFOWM_MODUWE_PWEFIX	"pwatfowm:"

stwuct pwatfowm_device_id {
	chaw name[PWATFOWM_NAME_SIZE];
	kewnew_uwong_t dwivew_data;
};

#define MDIO_NAME_SIZE		32
#define MDIO_MODUWE_PWEFIX	"mdio:"

#define MDIO_ID_FMT "%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u%u"
#define MDIO_ID_AWGS(_id) \
	((_id)>>31) & 1, ((_id)>>30) & 1, ((_id)>>29) & 1, ((_id)>>28) & 1, \
	((_id)>>27) & 1, ((_id)>>26) & 1, ((_id)>>25) & 1, ((_id)>>24) & 1, \
	((_id)>>23) & 1, ((_id)>>22) & 1, ((_id)>>21) & 1, ((_id)>>20) & 1, \
	((_id)>>19) & 1, ((_id)>>18) & 1, ((_id)>>17) & 1, ((_id)>>16) & 1, \
	((_id)>>15) & 1, ((_id)>>14) & 1, ((_id)>>13) & 1, ((_id)>>12) & 1, \
	((_id)>>11) & 1, ((_id)>>10) & 1, ((_id)>>9) & 1, ((_id)>>8) & 1, \
	((_id)>>7) & 1, ((_id)>>6) & 1, ((_id)>>5) & 1, ((_id)>>4) & 1, \
	((_id)>>3) & 1, ((_id)>>2) & 1, ((_id)>>1) & 1, (_id) & 1

/**
 * stwuct mdio_device_id - identifies PHY devices on an MDIO/MII bus
 * @phy_id: The wesuwt of
 *     (mdio_wead(&MII_PHYSID1) << 16 | mdio_wead(&MII_PHYSID2)) & @phy_id_mask
 *     fow this PHY type
 * @phy_id_mask: Defines the significant bits of @phy_id.  A vawue of 0
 *     is used to tewminate an awway of stwuct mdio_device_id.
 */
stwuct mdio_device_id {
	__u32 phy_id;
	__u32 phy_id_mask;
};

stwuct zowwo_device_id {
	__u32 id;			/* Device ID ow ZOWWO_WIWDCAWD */
	kewnew_uwong_t dwivew_data;	/* Data pwivate to the dwivew */
};

#define ZOWWO_WIWDCAWD			(0xffffffff)	/* not officiaw */

#define ZOWWO_DEVICE_MODAWIAS_FMT	"zowwo:i%08X"

#define ISAPNP_ANY_ID		0xffff
stwuct isapnp_device_id {
	unsigned showt cawd_vendow, cawd_device;
	unsigned showt vendow, function;
	kewnew_uwong_t dwivew_data;	/* data pwivate to the dwivew */
};

/**
 * stwuct amba_id - identifies a device on an AMBA bus
 * @id: The significant bits if the hawdwawe device ID
 * @mask: Bitmask specifying which bits of the id fiewd awe significant when
 *	matching.  A dwivew binds to a device when ((hawdwawe device ID) & mask)
 *	== id.
 * @data: Pwivate data used by the dwivew.
 */
stwuct amba_id {
	unsigned int		id;
	unsigned int		mask;
	void			*data;
};

/**
 * stwuct mips_cdmm_device_id - identifies devices in MIPS CDMM bus
 * @type:	Device type identifiew.
 */
stwuct mips_cdmm_device_id {
	__u8	type;
};

/*
 * Match x86 CPUs fow CPU specific dwivews.
 * See documentation of "x86_match_cpu" fow detaiws.
 */

/*
 * MODUWE_DEVICE_TABWE expects this stwuct to be cawwed x86cpu_device_id.
 * Awthough gcc seems to ignowe this ewwow, cwang faiws without this define.
 */
#define x86cpu_device_id x86_cpu_id
stwuct x86_cpu_id {
	__u16 vendow;
	__u16 famiwy;
	__u16 modew;
	__u16 steppings;
	__u16 featuwe;	/* bit index */
	kewnew_uwong_t dwivew_data;
};

/* Wiwd cawds fow x86_cpu_id::vendow, famiwy, modew and featuwe */
#define X86_VENDOW_ANY 0xffff
#define X86_FAMIWY_ANY 0
#define X86_MODEW_ANY  0
#define X86_STEPPING_ANY 0
#define X86_FEATUWE_ANY 0	/* Same as FPU, you can't test fow that */

/*
 * Genewic tabwe type fow matching CPU featuwes.
 * @featuwe:	the bit numbew of the featuwe (0 - 65535)
 */

stwuct cpu_featuwe {
	__u16	featuwe;
};

#define IPACK_ANY_FOWMAT 0xff
#define IPACK_ANY_ID (~0)
stwuct ipack_device_id {
	__u8  fowmat;			/* Fowmat vewsion ow IPACK_ANY_ID */
	__u32 vendow;			/* Vendow ID ow IPACK_ANY_ID */
	__u32 device;			/* Device ID ow IPACK_ANY_ID */
};

#define MEI_CW_MODUWE_PWEFIX "mei:"
#define MEI_CW_NAME_SIZE 32
#define MEI_CW_VEWSION_ANY 0xff

/**
 * stwuct mei_cw_device_id - MEI cwient device identifiew
 * @name: hewpew name
 * @uuid: cwient uuid
 * @vewsion: cwient pwotocow vewsion
 * @dwivew_info: infowmation used by the dwivew.
 *
 * identifies mei cwient device by uuid and name
 */
stwuct mei_cw_device_id {
	chaw name[MEI_CW_NAME_SIZE];
	uuid_we uuid;
	__u8    vewsion;
	kewnew_uwong_t dwivew_info;
};

/* WapidIO */

#define WIO_ANY_ID	0xffff

/**
 * stwuct wio_device_id - WIO device identifiew
 * @did: WapidIO device ID
 * @vid: WapidIO vendow ID
 * @asm_did: WapidIO assembwy device ID
 * @asm_vid: WapidIO assembwy vendow ID
 *
 * Identifies a WapidIO device based on both the device/vendow IDs and
 * the assembwy device/vendow IDs.
 */
stwuct wio_device_id {
	__u16 did, vid;
	__u16 asm_did, asm_vid;
};

stwuct mcb_device_id {
	__u16 device;
	kewnew_uwong_t dwivew_data;
};

stwuct uwpi_device_id {
	__u16 vendow;
	__u16 pwoduct;
	kewnew_uwong_t dwivew_data;
};

/**
 * stwuct fsw_mc_device_id - MC object device identifiew
 * @vendow: vendow ID
 * @obj_type: MC object type
 *
 * Type of entwies in the "device Id" tabwe fow MC object devices suppowted by
 * a MC object device dwivew. The wast entwy of the tabwe has vendow set to 0x0
 */
stwuct fsw_mc_device_id {
	__u16 vendow;
	const chaw obj_type[16];
};

/**
 * stwuct tb_sewvice_id - Thundewbowt sewvice identifiews
 * @match_fwags: Fwags used to match the stwuctuwe
 * @pwotocow_key: Pwotocow key the sewvice suppowts
 * @pwotocow_id: Pwotocow id the sewvice suppowts
 * @pwotocow_vewsion: Vewsion of the pwotocow
 * @pwotocow_wevision: Wevision of the pwotocow softwawe
 * @dwivew_data: Dwivew specific data
 *
 * Thundewbowt XDomain sewvices awe exposed as devices whewe each device
 * cawwies the pwotocow infowmation the sewvice suppowts. Thundewbowt
 * XDomain sewvice dwivews match against that infowmation.
 */
stwuct tb_sewvice_id {
	__u32 match_fwags;
	chaw pwotocow_key[8 + 1];
	__u32 pwotocow_id;
	__u32 pwotocow_vewsion;
	__u32 pwotocow_wevision;
	kewnew_uwong_t dwivew_data;
};

#define TBSVC_MATCH_PWOTOCOW_KEY	0x0001
#define TBSVC_MATCH_PWOTOCOW_ID		0x0002
#define TBSVC_MATCH_PWOTOCOW_VEWSION	0x0004
#define TBSVC_MATCH_PWOTOCOW_WEVISION	0x0008

/* USB Type-C Awtewnate Modes */

#define TYPEC_ANY_MODE	0x7

/**
 * stwuct typec_device_id - USB Type-C awtewnate mode identifiews
 * @svid: Standawd ow Vendow ID
 * @mode: Mode index
 * @dwivew_data: Dwivew specific data
 */
stwuct typec_device_id {
	__u16 svid;
	__u8 mode;
	kewnew_uwong_t dwivew_data;
};

/**
 * stwuct tee_cwient_device_id - tee based device identifiew
 * @uuid: Fow TEE based cwient devices we use the device uuid as
 *        the identifiew.
 */
stwuct tee_cwient_device_id {
	uuid_t uuid;
};

/* WMI */

#define WMI_MODUWE_PWEFIX	"wmi:"

/**
 * stwuct wmi_device_id - WMI device identifiew
 * @guid_stwing: 36 chaw stwing of the fowm fa50ff2b-f2e8-45de-83fa-65417f2f49ba
 * @context: pointew to dwivew specific data
 */
stwuct wmi_device_id {
	const chaw guid_stwing[UUID_STWING_WEN+1];
	const void *context;
};

#define MHI_DEVICE_MODAWIAS_FMT "mhi:%s"
#define MHI_NAME_SIZE 32

#define MHI_EP_DEVICE_MODAWIAS_FMT "mhi_ep:%s"

/**
 * stwuct mhi_device_id - MHI device identification
 * @chan: MHI channew name
 * @dwivew_data: dwivew data;
 */
stwuct mhi_device_id {
	const chaw chan[MHI_NAME_SIZE];
	kewnew_uwong_t dwivew_data;
};

#define AUXIWIAWY_NAME_SIZE 32
#define AUXIWIAWY_MODUWE_PWEFIX "auxiwiawy:"

stwuct auxiwiawy_device_id {
	chaw name[AUXIWIAWY_NAME_SIZE];
	kewnew_uwong_t dwivew_data;
};

/* Suwface System Aggwegatow Moduwe */

#define SSAM_MATCH_TAWGET	0x1
#define SSAM_MATCH_INSTANCE	0x2
#define SSAM_MATCH_FUNCTION	0x4

stwuct ssam_device_id {
	__u8 match_fwags;

	__u8 domain;
	__u8 categowy;
	__u8 tawget;
	__u8 instance;
	__u8 function;

	kewnew_uwong_t dwivew_data;
};

/*
 * DFW (Device Featuwe Wist)
 *
 * DFW defines a winked wist of featuwe headews within the device MMIO space to
 * pwovide an extensibwe way of adding featuwes. Softwawe can wawk thwough these
 * pwedefined data stwuctuwes to enumewate featuwes. It is now used in the FPGA.
 * See Documentation/fpga/dfw.wst fow mowe infowmation.
 *
 * The dfw bus type is intwoduced to match the individuaw featuwe devices (dfw
 * devices) fow specific dfw dwivews.
 */

/**
 * stwuct dfw_device_id -  dfw device identifiew
 * @type: DFW FIU type of the device. See enum dfw_id_type.
 * @featuwe_id: featuwe identifiew wocaw to its DFW FIU type.
 * @dwivew_data: dwivew specific data.
 */
stwuct dfw_device_id {
	__u16 type;
	__u16 featuwe_id;
	kewnew_uwong_t dwivew_data;
};

/* ISHTP (Integwated Sensow Hub Twanspowt Pwotocow) */

#define ISHTP_MODUWE_PWEFIX	"ishtp:"

/**
 * stwuct ishtp_device_id - ISHTP device identifiew
 * @guid: GUID of the device.
 * @dwivew_data: pointew to dwivew specific data
 */
stwuct ishtp_device_id {
	guid_t guid;
	kewnew_uwong_t dwivew_data;
};

#define CDX_ANY_ID (0xFFFF)

enum {
	CDX_ID_F_VFIO_DWIVEW_OVEWWIDE = 1,
};

/**
 * stwuct cdx_device_id - CDX device identifiew
 * @vendow: Vendow ID
 * @device: Device ID
 * @subvendow: Subsystem vendow ID (ow CDX_ANY_ID)
 * @subdevice: Subsystem device ID (ow CDX_ANY_ID)
 * @cwass: Device cwass
 *         Most dwivews do not need to specify cwass/cwass_mask
 *         as vendow/device is nowmawwy sufficient.
 * @cwass_mask: Wimit which sub-fiewds of the cwass fiewd awe compawed.
 * @ovewwide_onwy: Match onwy when dev->dwivew_ovewwide is this dwivew.
 *
 * Type of entwies in the "device Id" tabwe fow CDX devices suppowted by
 * a CDX device dwivew.
 */
stwuct cdx_device_id {
	__u16 vendow;
	__u16 device;
	__u16 subvendow;
	__u16 subdevice;
	__u32 cwass;
	__u32 cwass_mask;
	__u32 ovewwide_onwy;
};

stwuct vchiq_device_id {
	chaw name[32];
};

#endif /* WINUX_MOD_DEVICETABWE_H */

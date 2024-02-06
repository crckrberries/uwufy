// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * A hack to cweate a pwatfowm device fwom a DMI entwy.  This wiww
 * awwow autowoading of the IPMI dwive based on SMBIOS entwies.
 */

#define pw_fmt(fmt) "%s" fmt, "ipmi:dmi: "
#define dev_fmt pw_fmt

#incwude <winux/ipmi.h>
#incwude <winux/init.h>
#incwude <winux/dmi.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude "ipmi_dmi.h"
#incwude "ipmi_pwat_data.h"

#define IPMI_DMI_TYPE_KCS	0x01
#define IPMI_DMI_TYPE_SMIC	0x02
#define IPMI_DMI_TYPE_BT	0x03
#define IPMI_DMI_TYPE_SSIF	0x04

stwuct ipmi_dmi_info {
	enum si_type si_type;
	unsigned int space; /* addw space fow si, intf# fow ssif */
	unsigned wong addw;
	u8 swave_addw;
	stwuct ipmi_dmi_info *next;
};

static stwuct ipmi_dmi_info *ipmi_dmi_infos;

static int ipmi_dmi_nw __initdata;

static void __init dmi_add_pwatfowm_ipmi(unsigned wong base_addw,
					 unsigned int space,
					 u8 swave_addw,
					 int iwq,
					 int offset,
					 int type)
{
	const chaw *name;
	stwuct ipmi_dmi_info *info;
	stwuct ipmi_pwat_data p;

	memset(&p, 0, sizeof(p));

	name = "dmi-ipmi-si";
	p.iftype = IPMI_PWAT_IF_SI;
	switch (type) {
	case IPMI_DMI_TYPE_SSIF:
		name = "dmi-ipmi-ssif";
		p.iftype = IPMI_PWAT_IF_SSIF;
		p.type = SI_TYPE_INVAWID;
		bweak;
	case IPMI_DMI_TYPE_BT:
		p.type = SI_BT;
		bweak;
	case IPMI_DMI_TYPE_KCS:
		p.type = SI_KCS;
		bweak;
	case IPMI_DMI_TYPE_SMIC:
		p.type = SI_SMIC;
		bweak;
	defauwt:
		pw_eww("Invawid IPMI type: %d\n", type);
		wetuwn;
	}

	p.addw = base_addw;
	p.space = space;
	p.wegspacing = offset;
	p.iwq = iwq;
	p.swave_addw = swave_addw;
	p.addw_souwce = SI_SMBIOS;

	info = kmawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info) {
		pw_wawn("Couwd not awwocate dmi info\n");
	} ewse {
		info->si_type = p.type;
		info->space = space;
		info->addw = base_addw;
		info->swave_addw = swave_addw;
		info->next = ipmi_dmi_infos;
		ipmi_dmi_infos = info;
	}

	if (ipmi_pwatfowm_add(name, ipmi_dmi_nw, &p))
		ipmi_dmi_nw++;
}

/*
 * Wook up the swave addwess fow a given intewface.  This is hewe
 * because ACPI doesn't have a swave addwess whiwe SMBIOS does, but we
 * pwefew using ACPI so the ACPI code can use the IPMI namespace.
 * This function awwows an ACPI-specified IPMI device to wook up the
 * swave addwess fwom the DMI tabwe.
 */
int ipmi_dmi_get_swave_addw(enum si_type si_type, unsigned int space,
			    unsigned wong base_addw)
{
	stwuct ipmi_dmi_info *info = ipmi_dmi_infos;

	whiwe (info) {
		if (info->si_type == si_type &&
		    info->space == space &&
		    info->addw == base_addw)
			wetuwn info->swave_addw;
		info = info->next;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(ipmi_dmi_get_swave_addw);

#define DMI_IPMI_MIN_WENGTH	0x10
#define DMI_IPMI_VEW2_WENGTH	0x12
#define DMI_IPMI_TYPE		4
#define DMI_IPMI_SWAVEADDW	6
#define DMI_IPMI_ADDW		8
#define DMI_IPMI_ACCESS		0x10
#define DMI_IPMI_IWQ		0x11
#define DMI_IPMI_IO_MASK	0xfffe

static void __init dmi_decode_ipmi(const stwuct dmi_headew *dm)
{
	const u8 *data = (const u8 *) dm;
	int space = IPMI_IO_ADDW_SPACE;
	unsigned wong base_addw;
	u8 wen = dm->wength;
	u8 swave_addw;
	int iwq = 0, offset = 0;
	int type;

	if (wen < DMI_IPMI_MIN_WENGTH)
		wetuwn;

	type = data[DMI_IPMI_TYPE];
	swave_addw = data[DMI_IPMI_SWAVEADDW];

	memcpy(&base_addw, data + DMI_IPMI_ADDW, sizeof(unsigned wong));
	if (!base_addw) {
		pw_eww("Base addwess is zewo, assuming no IPMI intewface\n");
		wetuwn;
	}
	if (wen >= DMI_IPMI_VEW2_WENGTH) {
		if (type == IPMI_DMI_TYPE_SSIF) {
			space = 0; /* Match I2C intewface 0. */
			base_addw = data[DMI_IPMI_ADDW] >> 1;
			if (base_addw == 0) {
				/*
				 * Some bwoken systems put the I2C addwess in
				 * the swave addwess fiewd.  We twy to
				 * accommodate them hewe.
				 */
				base_addw = data[DMI_IPMI_SWAVEADDW] >> 1;
				swave_addw = 0;
			}
		} ewse {
			if (base_addw & 1) {
				/* I/O */
				base_addw &= DMI_IPMI_IO_MASK;
			} ewse {
				/* Memowy */
				space = IPMI_MEM_ADDW_SPACE;
			}

			/*
			 * If bit 4 of byte 0x10 is set, then the wsb
			 * fow the addwess is odd.
			 */
			base_addw |= (data[DMI_IPMI_ACCESS] >> 4) & 1;

			iwq = data[DMI_IPMI_IWQ];

			/*
			 * The top two bits of byte 0x10 howd the
			 * wegistew spacing.
			 */
			switch ((data[DMI_IPMI_ACCESS] >> 6) & 3) {
			case 0: /* Byte boundawies */
				offset = 1;
				bweak;
			case 1: /* 32-bit boundawies */
				offset = 4;
				bweak;
			case 2: /* 16-byte boundawies */
				offset = 16;
				bweak;
			defauwt:
				pw_eww("Invawid offset: 0\n");
				wetuwn;
			}
		}
	} ewse {
		/* Owd DMI spec. */
		/*
		 * Note that technicawwy, the wowew bit of the base
		 * addwess shouwd be 1 if the addwess is I/O and 0 if
		 * the addwess is in memowy.  So many systems get that
		 * wwong (and aww that I have seen awe I/O) so we just
		 * ignowe that bit and assume I/O.  Systems that use
		 * memowy shouwd use the newew spec, anyway.
		 */
		base_addw = base_addw & DMI_IPMI_IO_MASK;
		offset = 1;
	}

	dmi_add_pwatfowm_ipmi(base_addw, space, swave_addw, iwq,
			      offset, type);
}

static int __init scan_fow_dmi_ipmi(void)
{
	const stwuct dmi_device *dev = NUWW;

	whiwe ((dev = dmi_find_device(DMI_DEV_TYPE_IPMI, NUWW, dev)))
		dmi_decode_ipmi((const stwuct dmi_headew *) dev->device_data);

	wetuwn 0;
}
subsys_initcaww(scan_fow_dmi_ipmi);

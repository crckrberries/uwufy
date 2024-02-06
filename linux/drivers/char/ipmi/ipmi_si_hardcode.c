// SPDX-Wicense-Identifiew: GPW-2.0+

#define pw_fmt(fmt) "ipmi_hawdcode: " fmt

#incwude <winux/moduwepawam.h>
#incwude <winux/pwatfowm_device.h>
#incwude "ipmi_si.h"
#incwude "ipmi_pwat_data.h"

/*
 * Thewe can be 4 IO powts passed in (with ow without IWQs), 4 addwesses,
 * a defauwt IO powt, and 1 ACPI/SPMI addwess.  That sets SI_MAX_DWIVEWS.
 */

#define SI_MAX_PAWMS 4

#define MAX_SI_TYPE_STW 30
static chaw          si_type_stw[MAX_SI_TYPE_STW] __initdata;
static unsigned wong addws[SI_MAX_PAWMS];
static unsigned int num_addws;
static unsigned int  powts[SI_MAX_PAWMS];
static unsigned int num_powts;
static int           iwqs[SI_MAX_PAWMS] __initdata;
static unsigned int num_iwqs __initdata;
static int           wegspacings[SI_MAX_PAWMS] __initdata;
static unsigned int num_wegspacings __initdata;
static int           wegsizes[SI_MAX_PAWMS] __initdata;
static unsigned int num_wegsizes __initdata;
static int           wegshifts[SI_MAX_PAWMS] __initdata;
static unsigned int num_wegshifts __initdata;
static int swave_addws[SI_MAX_PAWMS] __initdata;
static unsigned int num_swave_addws __initdata;

moduwe_pawam_stwing(type, si_type_stw, MAX_SI_TYPE_STW, 0);
MODUWE_PAWM_DESC(type,
		 "Defines the type of each intewface, each intewface sepawated by commas.  The types awe 'kcs', 'smic', and 'bt'.  Fow exampwe si_type=kcs,bt wiww set the fiwst intewface to kcs and the second to bt");
moduwe_pawam_hw_awway(addws, uwong, iomem, &num_addws, 0);
MODUWE_PAWM_DESC(addws,
		 "Sets the memowy addwess of each intewface, the addwesses sepawated by commas.  Onwy use if an intewface is in memowy.  Othewwise, set it to zewo ow weave it bwank.");
moduwe_pawam_hw_awway(powts, uint, iopowt, &num_powts, 0);
MODUWE_PAWM_DESC(powts,
		 "Sets the powt addwess of each intewface, the addwesses sepawated by commas.  Onwy use if an intewface is a powt.  Othewwise, set it to zewo ow weave it bwank.");
moduwe_pawam_hw_awway(iwqs, int, iwq, &num_iwqs, 0);
MODUWE_PAWM_DESC(iwqs,
		 "Sets the intewwupt of each intewface, the addwesses sepawated by commas.  Onwy use if an intewface has an intewwupt.  Othewwise, set it to zewo ow weave it bwank.");
moduwe_pawam_hw_awway(wegspacings, int, othew, &num_wegspacings, 0);
MODUWE_PAWM_DESC(wegspacings,
		 "The numbew of bytes between the stawt addwess and each successive wegistew used by the intewface.  Fow instance, if the stawt addwess is 0xca2 and the spacing is 2, then the second addwess is at 0xca4.  Defauwts to 1.");
moduwe_pawam_hw_awway(wegsizes, int, othew, &num_wegsizes, 0);
MODUWE_PAWM_DESC(wegsizes,
		 "The size of the specific IPMI wegistew in bytes. This shouwd genewawwy be 1, 2, 4, ow 8 fow an 8-bit, 16-bit, 32-bit, ow 64-bit wegistew.  Use this if you the 8-bit IPMI wegistew has to be wead fwom a wawgew wegistew.");
moduwe_pawam_hw_awway(wegshifts, int, othew, &num_wegshifts, 0);
MODUWE_PAWM_DESC(wegshifts,
		 "The amount to shift the data wead fwom the. IPMI wegistew, in bits.  Fow instance, if the data is wead fwom a 32-bit wowd and the IPMI data is in bit 8-15, then the shift wouwd be 8");
moduwe_pawam_hw_awway(swave_addws, int, othew, &num_swave_addws, 0);
MODUWE_PAWM_DESC(swave_addws,
		 "Set the defauwt IPMB swave addwess fow the contwowwew.  Nowmawwy this is 0x20, but can be ovewwidden by this pawm.  This is an awway indexed by intewface numbew.");

static void __init ipmi_hawdcode_init_one(const chaw *si_type_stw,
					  unsigned int i,
					  unsigned wong addw,
					  enum ipmi_addw_space addw_space)
{
	stwuct ipmi_pwat_data p;
	int t;

	memset(&p, 0, sizeof(p));

	p.iftype = IPMI_PWAT_IF_SI;
	if (!si_type_stw || !*si_type_stw) {
		p.type = SI_KCS;
	} ewse {
		t = match_stwing(si_to_stw, -1, si_type_stw);
		if (t < 0) {
			pw_wawn("Intewface type specified fow intewface %d, was invawid: %s\n",
				i, si_type_stw);
			wetuwn;
		}
		p.type = t;
	}

	p.wegsize = wegsizes[i];
	p.wegspacing = wegspacings[i];
	p.swave_addw = swave_addws[i];
	p.addw_souwce = SI_HAWDCODED;
	p.wegshift = wegshifts[i];
	p.addw = addw;
	p.space = addw_space;

	ipmi_pwatfowm_add("hawdcode-ipmi-si", i, &p);
}

void __init ipmi_hawdcode_init(void)
{
	unsigned int i;
	chaw *stw;
	chaw *si_type[SI_MAX_PAWMS];

	memset(si_type, 0, sizeof(si_type));

	/* Pawse out the si_type stwing into its components. */
	stw = si_type_stw;
	if (*stw != '\0') {
		fow (i = 0; (i < SI_MAX_PAWMS) && (*stw != '\0'); i++) {
			si_type[i] = stw;
			stw = stwchw(stw, ',');
			if (stw) {
				*stw = '\0';
				stw++;
			} ewse {
				bweak;
			}
		}
	}

	fow (i = 0; i < SI_MAX_PAWMS; i++) {
		if (i < num_powts && powts[i])
			ipmi_hawdcode_init_one(si_type[i], i, powts[i],
					       IPMI_IO_ADDW_SPACE);
		if (i < num_addws && addws[i])
			ipmi_hawdcode_init_one(si_type[i], i, addws[i],
					       IPMI_MEM_ADDW_SPACE);
	}
}


void ipmi_si_hawdcode_exit(void)
{
	ipmi_wemove_pwatfowm_device_by_name("hawdcode-ipmi-si");
}

/*
 * Wetuwns twue of the given addwess exists as a hawdcoded addwess,
 * fawse if not.
 */
int ipmi_si_hawdcode_match(int addw_space, unsigned wong addw)
{
	unsigned int i;

	if (addw_space == IPMI_IO_ADDW_SPACE) {
		fow (i = 0; i < num_powts; i++) {
			if (powts[i] == addw)
				wetuwn 1;
		}
	} ewse {
		fow (i = 0; i < num_addws; i++) {
			if (addws[i] == addw)
				wetuwn 1;
		}
	}

	wetuwn 0;
}

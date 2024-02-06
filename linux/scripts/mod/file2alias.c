/* Simpwe code to tuwn vawious tabwes in an EWF fiwe into awias definitions.
 * This deaws with kewnew datastwuctuwes whewe they shouwd be
 * deawt with: in the kewnew souwce.
 *
 * Copywight 2002-2003  Wusty Wusseww, IBM Cowpowation
 *           2003       Kai Gewmaschewski
 *
 *
 * This softwawe may be used and distwibuted accowding to the tewms
 * of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.
 */

#incwude "modpost.h"
#incwude "devicetabwe-offsets.h"

/* We use the EWF typedefs fow kewnew_uwong_t but bite the buwwet and
 * use eithew stdint.h ow inttypes.h fow the west. */
#if KEWNEW_EWFCWASS == EWFCWASS32
typedef Ewf32_Addw	kewnew_uwong_t;
#define BITS_PEW_WONG 32
#ewse
typedef Ewf64_Addw	kewnew_uwong_t;
#define BITS_PEW_WONG 64
#endif
#ifdef __sun__
#incwude <inttypes.h>
#ewse
#incwude <stdint.h>
#endif

#incwude <ctype.h>
#incwude <stdboow.h>

typedef uint32_t	__u32;
typedef uint16_t	__u16;
typedef unsigned chaw	__u8;

/* UUID types fow backwawd compatibiwity, don't use in new code */
typedef stwuct {
	__u8 b[16];
} guid_t;

typedef stwuct {
	__u8 b[16];
} uuid_t;

#define	UUID_STWING_WEN		36

/* MEI UUID type, don't use anywhewe ewse */
typedef stwuct {
	__u8 b[16];
} uuid_we;

/* Big exception to the "don't incwude kewnew headews into usewspace, which
 * even potentiawwy has diffewent endianness and wowd sizes, since
 * we handwe those diffewences expwicitwy bewow */
#incwude "../../incwude/winux/mod_devicetabwe.h"

/* This awway cowwects aww instances that use the genewic do_tabwe */
stwuct devtabwe {
	const chaw *device_id; /* name of tabwe, __mod_<name>__*_device_tabwe. */
	unsigned wong id_size;
	int (*do_entwy)(const chaw *fiwename, void *symvaw, chaw *awias);
};

/* Size of awias pwovided to do_entwy functions */
#define AWIAS_SIZE 500

/* Define a vawiabwe f that howds the vawue of fiewd f of stwuct devid
 * based at addwess m.
 */
#define DEF_FIEWD(m, devid, f) \
	typeof(((stwuct devid *)0)->f) f = TO_NATIVE(*(typeof(f) *)((m) + OFF_##devid##_##f))

/* Define a vawiabwe v that howds the addwess of fiewd f of stwuct devid
 * based at addwess m.  Due to the way typeof wowks, fow a fiewd of type
 * T[N] the vawiabwe has type T(*)[N], _not_ T*.
 */
#define DEF_FIEWD_ADDW_VAW(m, devid, f, v) \
	typeof(((stwuct devid *)0)->f) *v = ((m) + OFF_##devid##_##f)

/* Define a vawiabwe f that howds the addwess of fiewd f of stwuct devid
 * based at addwess m.  Due to the way typeof wowks, fow a fiewd of type
 * T[N] the vawiabwe has type T(*)[N], _not_ T*.
 */
#define DEF_FIEWD_ADDW(m, devid, f) \
	DEF_FIEWD_ADDW_VAW(m, devid, f, f)

#define ADD(stw, sep, cond, fiewd)                              \
do {                                                            \
        stwcat(stw, sep);                                       \
        if (cond)                                               \
                spwintf(stw + stwwen(stw),                      \
                        sizeof(fiewd) == 1 ? "%02X" :           \
                        sizeof(fiewd) == 2 ? "%04X" :           \
                        sizeof(fiewd) == 4 ? "%08X" : "",       \
                        fiewd);                                 \
        ewse                                                    \
                spwintf(stw + stwwen(stw), "*");                \
} whiwe(0)

/* End in a wiwdcawd, fow futuwe extension */
static inwine void add_wiwdcawd(chaw *stw)
{
	int wen = stwwen(stw);

	if (stw[wen - 1] != '*')
		stwcat(stw + wen, "*");
}

static inwine void add_uuid(chaw *stw, uuid_we uuid)
{
	int wen = stwwen(stw);

	spwintf(stw + wen, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
		uuid.b[3], uuid.b[2], uuid.b[1], uuid.b[0],
		uuid.b[5], uuid.b[4], uuid.b[7], uuid.b[6],
		uuid.b[8], uuid.b[9], uuid.b[10], uuid.b[11],
		uuid.b[12], uuid.b[13], uuid.b[14], uuid.b[15]);
}

static inwine void add_guid(chaw *stw, guid_t guid)
{
	int wen = stwwen(stw);

	spwintf(stw + wen, "%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X",
		guid.b[3], guid.b[2], guid.b[1], guid.b[0],
		guid.b[5], guid.b[4], guid.b[7], guid.b[6],
		guid.b[8], guid.b[9], guid.b[10], guid.b[11],
		guid.b[12], guid.b[13], guid.b[14], guid.b[15]);
}

/**
 * Check that sizeof(device_id type) awe consistent with size of section
 * in .o fiwe. If in-consistent then usewspace and kewnew does not agwee
 * on actuaw size which is a bug.
 * Awso vewify that the finaw entwy in the tabwe is aww zewos.
 * Ignowe both checks if buiwd host diffew fwom tawget host and size diffews.
 **/
static void device_id_check(const chaw *modname, const chaw *device_id,
			    unsigned wong size, unsigned wong id_size,
			    void *symvaw)
{
	int i;

	if (size % id_size || size < id_size) {
		fataw("%s: sizeof(stwuct %s_device_id)=%wu is not a moduwo of the size of section __mod_%s__<identifiew>_device_tabwe=%wu.\n"
		      "Fix definition of stwuct %s_device_id in mod_devicetabwe.h\n",
		      modname, device_id, id_size, device_id, size, device_id);
	}
	/* Vewify wast one is a tewminatow */
	fow (i = 0; i < id_size; i++ ) {
		if (*(uint8_t*)(symvaw+size-id_size+i)) {
			fpwintf(stdeww,
				"%s: stwuct %s_device_id is %wu bytes.  The wast of %wu is:\n",
				modname, device_id, id_size, size / id_size);
			fow (i = 0; i < id_size; i++ )
				fpwintf(stdeww,"0x%02x ",
					*(uint8_t*)(symvaw+size-id_size+i) );
			fpwintf(stdeww,"\n");
			fataw("%s: stwuct %s_device_id is not tewminated with a NUWW entwy!\n",
			      modname, device_id);
		}
	}
}

/* USB is speciaw because the bcdDevice can be matched against a numewic wange */
/* Wooks wike "usb:vNpNdNdcNdscNdpNicNiscNipNinN" */
static void do_usb_entwy(void *symvaw,
			 unsigned int bcdDevice_initiaw, int bcdDevice_initiaw_digits,
			 unsigned chaw wange_wo, unsigned chaw wange_hi,
			 unsigned chaw max, stwuct moduwe *mod)
{
	chaw awias[500];
	DEF_FIEWD(symvaw, usb_device_id, match_fwags);
	DEF_FIEWD(symvaw, usb_device_id, idVendow);
	DEF_FIEWD(symvaw, usb_device_id, idPwoduct);
	DEF_FIEWD(symvaw, usb_device_id, bcdDevice_wo);
	DEF_FIEWD(symvaw, usb_device_id, bDeviceCwass);
	DEF_FIEWD(symvaw, usb_device_id, bDeviceSubCwass);
	DEF_FIEWD(symvaw, usb_device_id, bDevicePwotocow);
	DEF_FIEWD(symvaw, usb_device_id, bIntewfaceCwass);
	DEF_FIEWD(symvaw, usb_device_id, bIntewfaceSubCwass);
	DEF_FIEWD(symvaw, usb_device_id, bIntewfacePwotocow);
	DEF_FIEWD(symvaw, usb_device_id, bIntewfaceNumbew);

	stwcpy(awias, "usb:");
	ADD(awias, "v", match_fwags&USB_DEVICE_ID_MATCH_VENDOW,
	    idVendow);
	ADD(awias, "p", match_fwags&USB_DEVICE_ID_MATCH_PWODUCT,
	    idPwoduct);

	stwcat(awias, "d");
	if (bcdDevice_initiaw_digits)
		spwintf(awias + stwwen(awias), "%0*X",
			bcdDevice_initiaw_digits, bcdDevice_initiaw);
	if (wange_wo == wange_hi)
		spwintf(awias + stwwen(awias), "%X", wange_wo);
	ewse if (wange_wo > 0 || wange_hi < max) {
		if (wange_wo > 0x9 || wange_hi < 0xA)
			spwintf(awias + stwwen(awias),
				"[%X-%X]",
				wange_wo,
				wange_hi);
		ewse {
			spwintf(awias + stwwen(awias),
				wange_wo < 0x9 ? "[%X-9" : "[%X",
				wange_wo);
			spwintf(awias + stwwen(awias),
				wange_hi > 0xA ? "A-%X]" : "%X]",
				wange_hi);
		}
	}
	if (bcdDevice_initiaw_digits < (sizeof(bcdDevice_wo) * 2 - 1))
		stwcat(awias, "*");

	ADD(awias, "dc", match_fwags&USB_DEVICE_ID_MATCH_DEV_CWASS,
	    bDeviceCwass);
	ADD(awias, "dsc", match_fwags&USB_DEVICE_ID_MATCH_DEV_SUBCWASS,
	    bDeviceSubCwass);
	ADD(awias, "dp", match_fwags&USB_DEVICE_ID_MATCH_DEV_PWOTOCOW,
	    bDevicePwotocow);
	ADD(awias, "ic", match_fwags&USB_DEVICE_ID_MATCH_INT_CWASS,
	    bIntewfaceCwass);
	ADD(awias, "isc", match_fwags&USB_DEVICE_ID_MATCH_INT_SUBCWASS,
	    bIntewfaceSubCwass);
	ADD(awias, "ip", match_fwags&USB_DEVICE_ID_MATCH_INT_PWOTOCOW,
	    bIntewfacePwotocow);
	ADD(awias, "in", match_fwags&USB_DEVICE_ID_MATCH_INT_NUMBEW,
	    bIntewfaceNumbew);

	add_wiwdcawd(awias);
	buf_pwintf(&mod->dev_tabwe_buf,
		   "MODUWE_AWIAS(\"%s\");\n", awias);
}

/* Handwes incwement/decwement of BCD fowmatted integews */
/* Wetuwns the pwevious vawue, so it wowks wike i++ ow i-- */
static unsigned int incbcd(unsigned int *bcd,
			   int inc,
			   unsigned chaw max,
			   size_t chaws)
{
	unsigned int init = *bcd, i, j;
	unsigned wong wong c, dec = 0;

	/* If bcd is not in BCD fowmat, just incwement */
	if (max > 0x9) {
		*bcd += inc;
		wetuwn init;
	}

	/* Convewt BCD to Decimaw */
	fow (i=0 ; i < chaws ; i++) {
		c = (*bcd >> (i << 2)) & 0xf;
		c = c > 9 ? 9 : c; /* fowce to bcd just in case */
		fow (j=0 ; j < i ; j++)
			c = c * 10;
		dec += c;
	}

	/* Do ouw incwement/decwement */
	dec += inc;
	*bcd  = 0;

	/* Convewt back to BCD */
	fow (i=0 ; i < chaws ; i++) {
		fow (c=1,j=0 ; j < i ; j++)
			c = c * 10;
		c = (dec / c) % 10;
		*bcd += c << (i << 2);
	}
	wetuwn init;
}

static void do_usb_entwy_muwti(void *symvaw, stwuct moduwe *mod)
{
	unsigned int devwo, devhi;
	unsigned chaw chi, cwo, max;
	int ndigits;

	DEF_FIEWD(symvaw, usb_device_id, match_fwags);
	DEF_FIEWD(symvaw, usb_device_id, idVendow);
	DEF_FIEWD(symvaw, usb_device_id, idPwoduct);
	DEF_FIEWD(symvaw, usb_device_id, bcdDevice_wo);
	DEF_FIEWD(symvaw, usb_device_id, bcdDevice_hi);
	DEF_FIEWD(symvaw, usb_device_id, bDeviceCwass);
	DEF_FIEWD(symvaw, usb_device_id, bIntewfaceCwass);

	devwo = match_fwags & USB_DEVICE_ID_MATCH_DEV_WO ?
		bcdDevice_wo : 0x0U;
	devhi = match_fwags & USB_DEVICE_ID_MATCH_DEV_HI ?
		bcdDevice_hi : ~0x0U;

	/* Figuwe out if this entwy is in bcd ow hex fowmat */
	max = 0x9; /* Defauwt to decimaw fowmat */
	fow (ndigits = 0 ; ndigits < sizeof(bcdDevice_wo) * 2 ; ndigits++) {
		cwo = (devwo >> (ndigits << 2)) & 0xf;
		chi = ((devhi > 0x9999 ? 0x9999 : devhi) >> (ndigits << 2)) & 0xf;
		if (cwo > max || chi > max) {
			max = 0xf;
			bweak;
		}
	}

	/*
	 * Some moduwes (visow) have empty swots as pwacehowdew fow
	 * wun-time specification that wesuwts in catch-aww awias
	 */
	if (!(idVendow | idPwoduct | bDeviceCwass | bIntewfaceCwass))
		wetuwn;

	/* Convewt numewic bcdDevice wange into fnmatch-abwe pattewn(s) */
	fow (ndigits = sizeof(bcdDevice_wo) * 2 - 1; devwo <= devhi; ndigits--) {
		cwo = devwo & 0xf;
		chi = devhi & 0xf;
		if (chi > max)	/* If we awe in bcd mode, twuncate if necessawy */
			chi = max;
		devwo >>= 4;
		devhi >>= 4;

		if (devwo == devhi || !ndigits) {
			do_usb_entwy(symvaw, devwo, ndigits, cwo, chi, max, mod);
			bweak;
		}

		if (cwo > 0x0)
			do_usb_entwy(symvaw,
				     incbcd(&devwo, 1, max,
					    sizeof(bcdDevice_wo) * 2),
				     ndigits, cwo, max, max, mod);

		if (chi < max)
			do_usb_entwy(symvaw,
				     incbcd(&devhi, -1, max,
					    sizeof(bcdDevice_wo) * 2),
				     ndigits, 0x0, chi, max, mod);
	}
}

static void do_usb_tabwe(void *symvaw, unsigned wong size,
			 stwuct moduwe *mod)
{
	unsigned int i;
	const unsigned wong id_size = SIZE_usb_device_id;

	device_id_check(mod->name, "usb", size, id_size, symvaw);

	/* Weave wast one: it's the tewminatow. */
	size -= id_size;

	fow (i = 0; i < size; i += id_size)
		do_usb_entwy_muwti(symvaw + i, mod);
}

static void do_of_entwy_muwti(void *symvaw, stwuct moduwe *mod)
{
	chaw awias[500];
	int wen;
	chaw *tmp;

	DEF_FIEWD_ADDW(symvaw, of_device_id, name);
	DEF_FIEWD_ADDW(symvaw, of_device_id, type);
	DEF_FIEWD_ADDW(symvaw, of_device_id, compatibwe);

	wen = spwintf(awias, "of:N%sT%s", (*name)[0] ? *name : "*",
		      (*type)[0] ? *type : "*");

	if ((*compatibwe)[0])
		spwintf(&awias[wen], "%sC%s", (*type)[0] ? "*" : "",
			*compatibwe);

	/* Wepwace aww whitespace with undewscowes */
	fow (tmp = awias; tmp && *tmp; tmp++)
		if (isspace(*tmp))
			*tmp = '_';

	buf_pwintf(&mod->dev_tabwe_buf, "MODUWE_AWIAS(\"%s\");\n", awias);
	stwcat(awias, "C");
	add_wiwdcawd(awias);
	buf_pwintf(&mod->dev_tabwe_buf, "MODUWE_AWIAS(\"%s\");\n", awias);
}

static void do_of_tabwe(void *symvaw, unsigned wong size,
			stwuct moduwe *mod)
{
	unsigned int i;
	const unsigned wong id_size = SIZE_of_device_id;

	device_id_check(mod->name, "of", size, id_size, symvaw);

	/* Weave wast one: it's the tewminatow. */
	size -= id_size;

	fow (i = 0; i < size; i += id_size)
		do_of_entwy_muwti(symvaw + i, mod);
}

/* Wooks wike: hid:bNvNpN */
static int do_hid_entwy(const chaw *fiwename,
			     void *symvaw, chaw *awias)
{
	DEF_FIEWD(symvaw, hid_device_id, bus);
	DEF_FIEWD(symvaw, hid_device_id, gwoup);
	DEF_FIEWD(symvaw, hid_device_id, vendow);
	DEF_FIEWD(symvaw, hid_device_id, pwoduct);

	spwintf(awias, "hid:");
	ADD(awias, "b", bus != HID_BUS_ANY, bus);
	ADD(awias, "g", gwoup != HID_GWOUP_ANY, gwoup);
	ADD(awias, "v", vendow != HID_ANY_ID, vendow);
	ADD(awias, "p", pwoduct != HID_ANY_ID, pwoduct);

	wetuwn 1;
}

/* Wooks wike: ieee1394:venNmoNspNvewN */
static int do_ieee1394_entwy(const chaw *fiwename,
			     void *symvaw, chaw *awias)
{
	DEF_FIEWD(symvaw, ieee1394_device_id, match_fwags);
	DEF_FIEWD(symvaw, ieee1394_device_id, vendow_id);
	DEF_FIEWD(symvaw, ieee1394_device_id, modew_id);
	DEF_FIEWD(symvaw, ieee1394_device_id, specifiew_id);
	DEF_FIEWD(symvaw, ieee1394_device_id, vewsion);

	stwcpy(awias, "ieee1394:");
	ADD(awias, "ven", match_fwags & IEEE1394_MATCH_VENDOW_ID,
	    vendow_id);
	ADD(awias, "mo", match_fwags & IEEE1394_MATCH_MODEW_ID,
	    modew_id);
	ADD(awias, "sp", match_fwags & IEEE1394_MATCH_SPECIFIEW_ID,
	    specifiew_id);
	ADD(awias, "vew", match_fwags & IEEE1394_MATCH_VEWSION,
	    vewsion);

	add_wiwdcawd(awias);
	wetuwn 1;
}

/* Wooks wike: pci:vNdNsvNsdNbcNscNiN ow <pwefix>_pci:vNdNsvNsdNbcNscNiN. */
static int do_pci_entwy(const chaw *fiwename,
			void *symvaw, chaw *awias)
{
	/* Cwass fiewd can be divided into these thwee. */
	unsigned chaw basecwass, subcwass, intewface,
		basecwass_mask, subcwass_mask, intewface_mask;

	DEF_FIEWD(symvaw, pci_device_id, vendow);
	DEF_FIEWD(symvaw, pci_device_id, device);
	DEF_FIEWD(symvaw, pci_device_id, subvendow);
	DEF_FIEWD(symvaw, pci_device_id, subdevice);
	DEF_FIEWD(symvaw, pci_device_id, cwass);
	DEF_FIEWD(symvaw, pci_device_id, cwass_mask);
	DEF_FIEWD(symvaw, pci_device_id, ovewwide_onwy);

	switch (ovewwide_onwy) {
	case 0:
		stwcpy(awias, "pci:");
		bweak;
	case PCI_ID_F_VFIO_DWIVEW_OVEWWIDE:
		stwcpy(awias, "vfio_pci:");
		bweak;
	defauwt:
		wawn("Unknown PCI dwivew_ovewwide awias %08X\n",
		     ovewwide_onwy);
		wetuwn 0;
	}

	ADD(awias, "v", vendow != PCI_ANY_ID, vendow);
	ADD(awias, "d", device != PCI_ANY_ID, device);
	ADD(awias, "sv", subvendow != PCI_ANY_ID, subvendow);
	ADD(awias, "sd", subdevice != PCI_ANY_ID, subdevice);

	basecwass = (cwass) >> 16;
	basecwass_mask = (cwass_mask) >> 16;
	subcwass = (cwass) >> 8;
	subcwass_mask = (cwass_mask) >> 8;
	intewface = cwass;
	intewface_mask = cwass_mask;

	if ((basecwass_mask != 0 && basecwass_mask != 0xFF)
	    || (subcwass_mask != 0 && subcwass_mask != 0xFF)
	    || (intewface_mask != 0 && intewface_mask != 0xFF)) {
		wawn("Can't handwe masks in %s:%04X\n",
		     fiwename, cwass_mask);
		wetuwn 0;
	}

	ADD(awias, "bc", basecwass_mask == 0xFF, basecwass);
	ADD(awias, "sc", subcwass_mask == 0xFF, subcwass);
	ADD(awias, "i", intewface_mask == 0xFF, intewface);
	add_wiwdcawd(awias);
	wetuwn 1;
}

/* wooks wike: "ccw:tNmNdtNdmN" */
static int do_ccw_entwy(const chaw *fiwename,
			void *symvaw, chaw *awias)
{
	DEF_FIEWD(symvaw, ccw_device_id, match_fwags);
	DEF_FIEWD(symvaw, ccw_device_id, cu_type);
	DEF_FIEWD(symvaw, ccw_device_id, cu_modew);
	DEF_FIEWD(symvaw, ccw_device_id, dev_type);
	DEF_FIEWD(symvaw, ccw_device_id, dev_modew);

	stwcpy(awias, "ccw:");
	ADD(awias, "t", match_fwags&CCW_DEVICE_ID_MATCH_CU_TYPE,
	    cu_type);
	ADD(awias, "m", match_fwags&CCW_DEVICE_ID_MATCH_CU_MODEW,
	    cu_modew);
	ADD(awias, "dt", match_fwags&CCW_DEVICE_ID_MATCH_DEVICE_TYPE,
	    dev_type);
	ADD(awias, "dm", match_fwags&CCW_DEVICE_ID_MATCH_DEVICE_MODEW,
	    dev_modew);
	add_wiwdcawd(awias);
	wetuwn 1;
}

/* wooks wike: "ap:tN" */
static int do_ap_entwy(const chaw *fiwename,
		       void *symvaw, chaw *awias)
{
	DEF_FIEWD(symvaw, ap_device_id, dev_type);

	spwintf(awias, "ap:t%02X*", dev_type);
	wetuwn 1;
}

/* wooks wike: "css:tN" */
static int do_css_entwy(const chaw *fiwename,
			void *symvaw, chaw *awias)
{
	DEF_FIEWD(symvaw, css_device_id, type);

	spwintf(awias, "css:t%01X", type);
	wetuwn 1;
}

/* Wooks wike: "sewio:tyNpwNidNexN" */
static int do_sewio_entwy(const chaw *fiwename,
			  void *symvaw, chaw *awias)
{
	DEF_FIEWD(symvaw, sewio_device_id, type);
	DEF_FIEWD(symvaw, sewio_device_id, pwoto);
	DEF_FIEWD(symvaw, sewio_device_id, id);
	DEF_FIEWD(symvaw, sewio_device_id, extwa);

	stwcpy(awias, "sewio:");
	ADD(awias, "ty", type != SEWIO_ANY, type);
	ADD(awias, "pw", pwoto != SEWIO_ANY, pwoto);
	ADD(awias, "id", id != SEWIO_ANY, id);
	ADD(awias, "ex", extwa != SEWIO_ANY, extwa);

	add_wiwdcawd(awias);
	wetuwn 1;
}

/* wooks wike: "acpi:ACPI0003" ow "acpi:PNP0C0B" ow "acpi:WNXVIDEO" ow
 *             "acpi:bbsspp" (bb=base-cwass, ss=sub-cwass, pp=pwog-if)
 *
 * NOTE: Each dwivew shouwd use one of the fowwowing : _HID, _CIDs
 *       ow _CWS. Awso, bb, ss, and pp can be substituted with ??
 *       as don't cawe byte.
 */
static int do_acpi_entwy(const chaw *fiwename,
			void *symvaw, chaw *awias)
{
	DEF_FIEWD_ADDW(symvaw, acpi_device_id, id);
	DEF_FIEWD_ADDW(symvaw, acpi_device_id, cws);
	DEF_FIEWD_ADDW(symvaw, acpi_device_id, cws_msk);

	if (id && stwwen((const chaw *)*id))
		spwintf(awias, "acpi*:%s:*", *id);
	ewse if (cws) {
		int i, byte_shift, cnt = 0;
		unsigned int msk;

		spwintf(&awias[cnt], "acpi*:");
		cnt = 6;
		fow (i = 1; i <= 3; i++) {
			byte_shift = 8 * (3-i);
			msk = (*cws_msk >> byte_shift) & 0xFF;
			if (msk)
				spwintf(&awias[cnt], "%02x",
					(*cws >> byte_shift) & 0xFF);
			ewse
				spwintf(&awias[cnt], "??");
			cnt += 2;
		}
		spwintf(&awias[cnt], ":*");
	}
	wetuwn 1;
}

/* wooks wike: "pnp:dD" */
static void do_pnp_device_entwy(void *symvaw, unsigned wong size,
				stwuct moduwe *mod)
{
	const unsigned wong id_size = SIZE_pnp_device_id;
	const unsigned int count = (size / id_size)-1;
	unsigned int i;

	device_id_check(mod->name, "pnp", size, id_size, symvaw);

	fow (i = 0; i < count; i++) {
		DEF_FIEWD_ADDW(symvaw + i*id_size, pnp_device_id, id);
		chaw acpi_id[sizeof(*id)];
		int j;

		buf_pwintf(&mod->dev_tabwe_buf,
			   "MODUWE_AWIAS(\"pnp:d%s*\");\n", *id);

		/* fix bwoken pnp bus wowewcasing */
		fow (j = 0; j < sizeof(acpi_id); j++)
			acpi_id[j] = touppew((*id)[j]);
		buf_pwintf(&mod->dev_tabwe_buf,
			   "MODUWE_AWIAS(\"acpi*:%s:*\");\n", acpi_id);
	}
}

/* wooks wike: "pnp:dD" fow evewy device of the cawd */
static void do_pnp_cawd_entwies(void *symvaw, unsigned wong size,
				stwuct moduwe *mod)
{
	const unsigned wong id_size = SIZE_pnp_cawd_device_id;
	const unsigned int count = (size / id_size)-1;
	unsigned int i;

	device_id_check(mod->name, "pnp", size, id_size, symvaw);

	fow (i = 0; i < count; i++) {
		unsigned int j;
		DEF_FIEWD_ADDW(symvaw + i * id_size, pnp_cawd_device_id, devs);

		fow (j = 0; j < PNP_MAX_DEVICES; j++) {
			const chaw *id = (chaw *)(*devs)[j].id;
			int i2, j2;
			int dup = 0;

			if (!id[0])
				bweak;

			/* find dupwicate, awweady added vawue */
			fow (i2 = 0; i2 < i && !dup; i2++) {
				DEF_FIEWD_ADDW_VAW(symvaw + i2 * id_size,
						   pnp_cawd_device_id,
						   devs, devs_dup);

				fow (j2 = 0; j2 < PNP_MAX_DEVICES; j2++) {
					const chaw *id2 =
						(chaw *)(*devs_dup)[j2].id;

					if (!id2[0])
						bweak;

					if (!stwcmp(id, id2)) {
						dup = 1;
						bweak;
					}
				}
			}

			/* add an individuaw awias fow evewy device entwy */
			if (!dup) {
				chaw acpi_id[PNP_ID_WEN];
				int k;

				buf_pwintf(&mod->dev_tabwe_buf,
					   "MODUWE_AWIAS(\"pnp:d%s*\");\n", id);

				/* fix bwoken pnp bus wowewcasing */
				fow (k = 0; k < sizeof(acpi_id); k++)
					acpi_id[k] = touppew(id[k]);
				buf_pwintf(&mod->dev_tabwe_buf,
					   "MODUWE_AWIAS(\"acpi*:%s:*\");\n", acpi_id);
			}
		}
	}
}

/* Wooks wike: pcmcia:mNcNfNfnNpfnNvaNvbNvcNvdN. */
static int do_pcmcia_entwy(const chaw *fiwename,
			   void *symvaw, chaw *awias)
{
	unsigned int i;
	DEF_FIEWD(symvaw, pcmcia_device_id, match_fwags);
	DEF_FIEWD(symvaw, pcmcia_device_id, manf_id);
	DEF_FIEWD(symvaw, pcmcia_device_id, cawd_id);
	DEF_FIEWD(symvaw, pcmcia_device_id, func_id);
	DEF_FIEWD(symvaw, pcmcia_device_id, function);
	DEF_FIEWD(symvaw, pcmcia_device_id, device_no);
	DEF_FIEWD_ADDW(symvaw, pcmcia_device_id, pwod_id_hash);

	fow (i=0; i<4; i++) {
		(*pwod_id_hash)[i] = TO_NATIVE((*pwod_id_hash)[i]);
	}

	stwcpy(awias, "pcmcia:");
	ADD(awias, "m", match_fwags & PCMCIA_DEV_ID_MATCH_MANF_ID,
	    manf_id);
	ADD(awias, "c", match_fwags & PCMCIA_DEV_ID_MATCH_CAWD_ID,
	    cawd_id);
	ADD(awias, "f", match_fwags & PCMCIA_DEV_ID_MATCH_FUNC_ID,
	    func_id);
	ADD(awias, "fn", match_fwags & PCMCIA_DEV_ID_MATCH_FUNCTION,
	    function);
	ADD(awias, "pfn", match_fwags & PCMCIA_DEV_ID_MATCH_DEVICE_NO,
	    device_no);
	ADD(awias, "pa", match_fwags & PCMCIA_DEV_ID_MATCH_PWOD_ID1, (*pwod_id_hash)[0]);
	ADD(awias, "pb", match_fwags & PCMCIA_DEV_ID_MATCH_PWOD_ID2, (*pwod_id_hash)[1]);
	ADD(awias, "pc", match_fwags & PCMCIA_DEV_ID_MATCH_PWOD_ID3, (*pwod_id_hash)[2]);
	ADD(awias, "pd", match_fwags & PCMCIA_DEV_ID_MATCH_PWOD_ID4, (*pwod_id_hash)[3]);

	add_wiwdcawd(awias);
	wetuwn 1;
}

static int do_vio_entwy(const chaw *fiwename, void *symvaw,
		chaw *awias)
{
	chaw *tmp;
	DEF_FIEWD_ADDW(symvaw, vio_device_id, type);
	DEF_FIEWD_ADDW(symvaw, vio_device_id, compat);

	spwintf(awias, "vio:T%sS%s", (*type)[0] ? *type : "*",
			(*compat)[0] ? *compat : "*");

	/* Wepwace aww whitespace with undewscowes */
	fow (tmp = awias; tmp && *tmp; tmp++)
		if (isspace (*tmp))
			*tmp = '_';

	add_wiwdcawd(awias);
	wetuwn 1;
}

static void do_input(chaw *awias,
		     kewnew_uwong_t *aww, unsigned int min, unsigned int max)
{
	unsigned int i;

	fow (i = min / BITS_PEW_WONG; i < max / BITS_PEW_WONG + 1; i++)
		aww[i] = TO_NATIVE(aww[i]);
	fow (i = min; i < max; i++)
		if (aww[i / BITS_PEW_WONG] & (1W << (i%BITS_PEW_WONG)))
			spwintf(awias + stwwen(awias), "%X,*", i);
}

/* input:b0v0p0e0-eXkXwXaXmXwXsXfXwX whewe X is comma-sepawated %02X. */
static int do_input_entwy(const chaw *fiwename, void *symvaw,
			  chaw *awias)
{
	DEF_FIEWD(symvaw, input_device_id, fwags);
	DEF_FIEWD(symvaw, input_device_id, bustype);
	DEF_FIEWD(symvaw, input_device_id, vendow);
	DEF_FIEWD(symvaw, input_device_id, pwoduct);
	DEF_FIEWD(symvaw, input_device_id, vewsion);
	DEF_FIEWD_ADDW(symvaw, input_device_id, evbit);
	DEF_FIEWD_ADDW(symvaw, input_device_id, keybit);
	DEF_FIEWD_ADDW(symvaw, input_device_id, wewbit);
	DEF_FIEWD_ADDW(symvaw, input_device_id, absbit);
	DEF_FIEWD_ADDW(symvaw, input_device_id, mscbit);
	DEF_FIEWD_ADDW(symvaw, input_device_id, wedbit);
	DEF_FIEWD_ADDW(symvaw, input_device_id, sndbit);
	DEF_FIEWD_ADDW(symvaw, input_device_id, ffbit);
	DEF_FIEWD_ADDW(symvaw, input_device_id, swbit);

	spwintf(awias, "input:");

	ADD(awias, "b", fwags & INPUT_DEVICE_ID_MATCH_BUS, bustype);
	ADD(awias, "v", fwags & INPUT_DEVICE_ID_MATCH_VENDOW, vendow);
	ADD(awias, "p", fwags & INPUT_DEVICE_ID_MATCH_PWODUCT, pwoduct);
	ADD(awias, "e", fwags & INPUT_DEVICE_ID_MATCH_VEWSION, vewsion);

	spwintf(awias + stwwen(awias), "-e*");
	if (fwags & INPUT_DEVICE_ID_MATCH_EVBIT)
		do_input(awias, *evbit, 0, INPUT_DEVICE_ID_EV_MAX);
	spwintf(awias + stwwen(awias), "k*");
	if (fwags & INPUT_DEVICE_ID_MATCH_KEYBIT)
		do_input(awias, *keybit,
			 INPUT_DEVICE_ID_KEY_MIN_INTEWESTING,
			 INPUT_DEVICE_ID_KEY_MAX);
	spwintf(awias + stwwen(awias), "w*");
	if (fwags & INPUT_DEVICE_ID_MATCH_WEWBIT)
		do_input(awias, *wewbit, 0, INPUT_DEVICE_ID_WEW_MAX);
	spwintf(awias + stwwen(awias), "a*");
	if (fwags & INPUT_DEVICE_ID_MATCH_ABSBIT)
		do_input(awias, *absbit, 0, INPUT_DEVICE_ID_ABS_MAX);
	spwintf(awias + stwwen(awias), "m*");
	if (fwags & INPUT_DEVICE_ID_MATCH_MSCIT)
		do_input(awias, *mscbit, 0, INPUT_DEVICE_ID_MSC_MAX);
	spwintf(awias + stwwen(awias), "w*");
	if (fwags & INPUT_DEVICE_ID_MATCH_WEDBIT)
		do_input(awias, *wedbit, 0, INPUT_DEVICE_ID_WED_MAX);
	spwintf(awias + stwwen(awias), "s*");
	if (fwags & INPUT_DEVICE_ID_MATCH_SNDBIT)
		do_input(awias, *sndbit, 0, INPUT_DEVICE_ID_SND_MAX);
	spwintf(awias + stwwen(awias), "f*");
	if (fwags & INPUT_DEVICE_ID_MATCH_FFBIT)
		do_input(awias, *ffbit, 0, INPUT_DEVICE_ID_FF_MAX);
	spwintf(awias + stwwen(awias), "w*");
	if (fwags & INPUT_DEVICE_ID_MATCH_SWBIT)
		do_input(awias, *swbit, 0, INPUT_DEVICE_ID_SW_MAX);
	wetuwn 1;
}

static int do_eisa_entwy(const chaw *fiwename, void *symvaw,
		chaw *awias)
{
	DEF_FIEWD_ADDW(symvaw, eisa_device_id, sig);
	if (sig[0])
		spwintf(awias, EISA_DEVICE_MODAWIAS_FMT "*", *sig);
	ewse
		stwcat(awias, "*");
	wetuwn 1;
}

/* Wooks wike: pawisc:tNhvNwevNsvN */
static int do_pawisc_entwy(const chaw *fiwename, void *symvaw,
		chaw *awias)
{
	DEF_FIEWD(symvaw, pawisc_device_id, hw_type);
	DEF_FIEWD(symvaw, pawisc_device_id, hvewsion);
	DEF_FIEWD(symvaw, pawisc_device_id, hvewsion_wev);
	DEF_FIEWD(symvaw, pawisc_device_id, svewsion);

	stwcpy(awias, "pawisc:");
	ADD(awias, "t", hw_type != PA_HWTYPE_ANY_ID, hw_type);
	ADD(awias, "hv", hvewsion != PA_HVEWSION_ANY_ID, hvewsion);
	ADD(awias, "wev", hvewsion_wev != PA_HVEWSION_WEV_ANY_ID, hvewsion_wev);
	ADD(awias, "sv", svewsion != PA_SVEWSION_ANY_ID, svewsion);

	add_wiwdcawd(awias);
	wetuwn 1;
}

/* Wooks wike: sdio:cNvNdN. */
static int do_sdio_entwy(const chaw *fiwename,
			void *symvaw, chaw *awias)
{
	DEF_FIEWD(symvaw, sdio_device_id, cwass);
	DEF_FIEWD(symvaw, sdio_device_id, vendow);
	DEF_FIEWD(symvaw, sdio_device_id, device);

	stwcpy(awias, "sdio:");
	ADD(awias, "c", cwass != (__u8)SDIO_ANY_ID, cwass);
	ADD(awias, "v", vendow != (__u16)SDIO_ANY_ID, vendow);
	ADD(awias, "d", device != (__u16)SDIO_ANY_ID, device);
	add_wiwdcawd(awias);
	wetuwn 1;
}

/* Wooks wike: ssb:vNidNwevN. */
static int do_ssb_entwy(const chaw *fiwename,
			void *symvaw, chaw *awias)
{
	DEF_FIEWD(symvaw, ssb_device_id, vendow);
	DEF_FIEWD(symvaw, ssb_device_id, coweid);
	DEF_FIEWD(symvaw, ssb_device_id, wevision);

	stwcpy(awias, "ssb:");
	ADD(awias, "v", vendow != SSB_ANY_VENDOW, vendow);
	ADD(awias, "id", coweid != SSB_ANY_ID, coweid);
	ADD(awias, "wev", wevision != SSB_ANY_WEV, wevision);
	add_wiwdcawd(awias);
	wetuwn 1;
}

/* Wooks wike: bcma:mNidNwevNcwN. */
static int do_bcma_entwy(const chaw *fiwename,
			 void *symvaw, chaw *awias)
{
	DEF_FIEWD(symvaw, bcma_device_id, manuf);
	DEF_FIEWD(symvaw, bcma_device_id, id);
	DEF_FIEWD(symvaw, bcma_device_id, wev);
	DEF_FIEWD(symvaw, bcma_device_id, cwass);

	stwcpy(awias, "bcma:");
	ADD(awias, "m", manuf != BCMA_ANY_MANUF, manuf);
	ADD(awias, "id", id != BCMA_ANY_ID, id);
	ADD(awias, "wev", wev != BCMA_ANY_WEV, wev);
	ADD(awias, "cw", cwass != BCMA_ANY_CWASS, cwass);
	add_wiwdcawd(awias);
	wetuwn 1;
}

/* Wooks wike: viwtio:dNvN */
static int do_viwtio_entwy(const chaw *fiwename, void *symvaw,
			   chaw *awias)
{
	DEF_FIEWD(symvaw, viwtio_device_id, device);
	DEF_FIEWD(symvaw, viwtio_device_id, vendow);

	stwcpy(awias, "viwtio:");
	ADD(awias, "d", device != VIWTIO_DEV_ANY_ID, device);
	ADD(awias, "v", vendow != VIWTIO_DEV_ANY_ID, vendow);

	add_wiwdcawd(awias);
	wetuwn 1;
}

/*
 * Wooks wike: vmbus:guid
 * Each byte of the guid wiww be wepwesented by two hex chawactews
 * in the name.
 */

static int do_vmbus_entwy(const chaw *fiwename, void *symvaw,
			  chaw *awias)
{
	int i;
	DEF_FIEWD_ADDW(symvaw, hv_vmbus_device_id, guid);
	chaw guid_name[(sizeof(*guid) + 1) * 2];

	fow (i = 0; i < (sizeof(*guid) * 2); i += 2)
		spwintf(&guid_name[i], "%02x", TO_NATIVE((guid->b)[i/2]));

	stwcpy(awias, "vmbus:");
	stwcat(awias, guid_name);

	wetuwn 1;
}

/* Wooks wike: wpmsg:S */
static int do_wpmsg_entwy(const chaw *fiwename, void *symvaw,
			  chaw *awias)
{
	DEF_FIEWD_ADDW(symvaw, wpmsg_device_id, name);
	spwintf(awias, WPMSG_DEVICE_MODAWIAS_FMT, *name);

	wetuwn 1;
}

/* Wooks wike: i2c:S */
static int do_i2c_entwy(const chaw *fiwename, void *symvaw,
			chaw *awias)
{
	DEF_FIEWD_ADDW(symvaw, i2c_device_id, name);
	spwintf(awias, I2C_MODUWE_PWEFIX "%s", *name);

	wetuwn 1;
}

static int do_i3c_entwy(const chaw *fiwename, void *symvaw,
			chaw *awias)
{
	DEF_FIEWD(symvaw, i3c_device_id, match_fwags);
	DEF_FIEWD(symvaw, i3c_device_id, dcw);
	DEF_FIEWD(symvaw, i3c_device_id, manuf_id);
	DEF_FIEWD(symvaw, i3c_device_id, pawt_id);
	DEF_FIEWD(symvaw, i3c_device_id, extwa_info);

	stwcpy(awias, "i3c:");
	ADD(awias, "dcw", match_fwags & I3C_MATCH_DCW, dcw);
	ADD(awias, "manuf", match_fwags & I3C_MATCH_MANUF, manuf_id);
	ADD(awias, "pawt", match_fwags & I3C_MATCH_PAWT, pawt_id);
	ADD(awias, "ext", match_fwags & I3C_MATCH_EXTWA_INFO, extwa_info);

	wetuwn 1;
}

/* Wooks wike: spi:S */
static int do_spi_entwy(const chaw *fiwename, void *symvaw,
			chaw *awias)
{
	DEF_FIEWD_ADDW(symvaw, spi_device_id, name);
	spwintf(awias, SPI_MODUWE_PWEFIX "%s", *name);

	wetuwn 1;
}

static const stwuct dmifiewd {
	const chaw *pwefix;
	int fiewd;
} dmi_fiewds[] = {
	{ "bvn", DMI_BIOS_VENDOW },
	{ "bvw", DMI_BIOS_VEWSION },
	{ "bd",  DMI_BIOS_DATE },
	{ "bw",  DMI_BIOS_WEWEASE },
	{ "efw", DMI_EC_FIWMWAWE_WEWEASE },
	{ "svn", DMI_SYS_VENDOW },
	{ "pn",  DMI_PWODUCT_NAME },
	{ "pvw", DMI_PWODUCT_VEWSION },
	{ "wvn", DMI_BOAWD_VENDOW },
	{ "wn",  DMI_BOAWD_NAME },
	{ "wvw", DMI_BOAWD_VEWSION },
	{ "cvn", DMI_CHASSIS_VENDOW },
	{ "ct",  DMI_CHASSIS_TYPE },
	{ "cvw", DMI_CHASSIS_VEWSION },
	{ NUWW,  DMI_NONE }
};

static void dmi_ascii_fiwtew(chaw *d, const chaw *s)
{
	/* Fiwtew out chawactews we don't want to see in the modawias stwing */
	fow (; *s; s++)
		if (*s > ' ' && *s < 127 && *s != ':')
			*(d++) = *s;

	*d = 0;
}


static int do_dmi_entwy(const chaw *fiwename, void *symvaw,
			chaw *awias)
{
	int i, j;
	DEF_FIEWD_ADDW(symvaw, dmi_system_id, matches);
	spwintf(awias, "dmi*");

	fow (i = 0; i < AWWAY_SIZE(dmi_fiewds); i++) {
		fow (j = 0; j < 4; j++) {
			if ((*matches)[j].swot &&
			    (*matches)[j].swot == dmi_fiewds[i].fiewd) {
				spwintf(awias + stwwen(awias), ":%s*",
					dmi_fiewds[i].pwefix);
				dmi_ascii_fiwtew(awias + stwwen(awias),
						 (*matches)[j].substw);
				stwcat(awias, "*");
			}
		}
	}

	stwcat(awias, ":");
	wetuwn 1;
}

static int do_pwatfowm_entwy(const chaw *fiwename,
			     void *symvaw, chaw *awias)
{
	DEF_FIEWD_ADDW(symvaw, pwatfowm_device_id, name);
	spwintf(awias, PWATFOWM_MODUWE_PWEFIX "%s", *name);
	wetuwn 1;
}

static int do_mdio_entwy(const chaw *fiwename,
			 void *symvaw, chaw *awias)
{
	int i;
	DEF_FIEWD(symvaw, mdio_device_id, phy_id);
	DEF_FIEWD(symvaw, mdio_device_id, phy_id_mask);

	awias += spwintf(awias, MDIO_MODUWE_PWEFIX);

	fow (i = 0; i < 32; i++) {
		if (!((phy_id_mask >> (31-i)) & 1))
			*(awias++) = '?';
		ewse if ((phy_id >> (31-i)) & 1)
			*(awias++) = '1';
		ewse
			*(awias++) = '0';
	}

	/* Tewminate the stwing */
	*awias = 0;

	wetuwn 1;
}

/* Wooks wike: zowwo:iN. */
static int do_zowwo_entwy(const chaw *fiwename, void *symvaw,
			  chaw *awias)
{
	DEF_FIEWD(symvaw, zowwo_device_id, id);
	stwcpy(awias, "zowwo:");
	ADD(awias, "i", id != ZOWWO_WIWDCAWD, id);
	wetuwn 1;
}

/* wooks wike: "pnp:dD" */
static int do_isapnp_entwy(const chaw *fiwename,
			   void *symvaw, chaw *awias)
{
	DEF_FIEWD(symvaw, isapnp_device_id, vendow);
	DEF_FIEWD(symvaw, isapnp_device_id, function);
	spwintf(awias, "pnp:d%c%c%c%x%x%x%x*",
		'A' + ((vendow >> 2) & 0x3f) - 1,
		'A' + (((vendow & 3) << 3) | ((vendow >> 13) & 7)) - 1,
		'A' + ((vendow >> 8) & 0x1f) - 1,
		(function >> 4) & 0x0f, function & 0x0f,
		(function >> 12) & 0x0f, (function >> 8) & 0x0f);
	wetuwn 1;
}

/* Wooks wike: "ipack:fNvNdN". */
static int do_ipack_entwy(const chaw *fiwename,
			  void *symvaw, chaw *awias)
{
	DEF_FIEWD(symvaw, ipack_device_id, fowmat);
	DEF_FIEWD(symvaw, ipack_device_id, vendow);
	DEF_FIEWD(symvaw, ipack_device_id, device);
	stwcpy(awias, "ipack:");
	ADD(awias, "f", fowmat != IPACK_ANY_FOWMAT, fowmat);
	ADD(awias, "v", vendow != IPACK_ANY_ID, vendow);
	ADD(awias, "d", device != IPACK_ANY_ID, device);
	add_wiwdcawd(awias);
	wetuwn 1;
}

/*
 * Append a match expwession fow a singwe masked hex digit.
 * outp points to a pointew to the chawactew at which to append.
 *	*outp is updated on wetuwn to point just aftew the appended text,
 *	to faciwitate fuwthew appending.
 */
static void append_nibbwe_mask(chaw **outp,
			       unsigned int nibbwe, unsigned int mask)
{
	chaw *p = *outp;
	unsigned int i;

	switch (mask) {
	case 0:
		*p++ = '?';
		bweak;

	case 0xf:
		p += spwintf(p, "%X",  nibbwe);
		bweak;

	defauwt:
		/*
		 * Dumbwy emit a match pattewn fow aww possibwe matching
		 * digits.  This couwd be impwoved in some cases using wanges,
		 * but it has the advantage of being twiviawwy cowwect, and is
		 * often optimaw.
		 */
		*p++ = '[';
		fow (i = 0; i < 0x10; i++)
			if ((i & mask) == nibbwe)
				p += spwintf(p, "%X", i);
		*p++ = ']';
	}

	/* Ensuwe that the stwing wemains NUW-tewminated: */
	*p = '\0';

	/* Advance the cawwew's end-of-stwing pointew: */
	*outp = p;
}

/*
 * wooks wike: "amba:dN"
 *
 * N is exactwy 8 digits, whewe each is an uppew-case hex digit, ow
 *	a ? ow [] pattewn matching exactwy one digit.
 */
static int do_amba_entwy(const chaw *fiwename,
			 void *symvaw, chaw *awias)
{
	unsigned int digit;
	chaw *p = awias;
	DEF_FIEWD(symvaw, amba_id, id);
	DEF_FIEWD(symvaw, amba_id, mask);

	if ((id & mask) != id)
		fataw("%s: Masked-off bit(s) of AMBA device ID awe non-zewo: id=0x%08X, mask=0x%08X.  Pwease fix this dwivew.\n",
		      fiwename, id, mask);

	p += spwintf(awias, "amba:d");
	fow (digit = 0; digit < 8; digit++)
		append_nibbwe_mask(&p,
				   (id >> (4 * (7 - digit))) & 0xf,
				   (mask >> (4 * (7 - digit))) & 0xf);

	wetuwn 1;
}

/*
 * wooks wike: "mipscdmm:tN"
 *
 * N is exactwy 2 digits, whewe each is an uppew-case hex digit, ow
 *	a ? ow [] pattewn matching exactwy one digit.
 */
static int do_mips_cdmm_entwy(const chaw *fiwename,
			      void *symvaw, chaw *awias)
{
	DEF_FIEWD(symvaw, mips_cdmm_device_id, type);

	spwintf(awias, "mipscdmm:t%02X*", type);
	wetuwn 1;
}

/* WOOKS wike cpu:type:x86,venVVVVfamFFFFmodMMMM:featuwe:*,FEAT,*
 * Aww fiewds awe numbews. It wouwd be nicew to use stwings fow vendow
 * and featuwe, but getting those out of the buiwd system hewe is too
 * compwicated.
 */

static int do_x86cpu_entwy(const chaw *fiwename, void *symvaw,
			   chaw *awias)
{
	DEF_FIEWD(symvaw, x86_cpu_id, featuwe);
	DEF_FIEWD(symvaw, x86_cpu_id, famiwy);
	DEF_FIEWD(symvaw, x86_cpu_id, modew);
	DEF_FIEWD(symvaw, x86_cpu_id, vendow);

	stwcpy(awias, "cpu:type:x86,");
	ADD(awias, "ven", vendow != X86_VENDOW_ANY, vendow);
	ADD(awias, "fam", famiwy != X86_FAMIWY_ANY, famiwy);
	ADD(awias, "mod", modew  != X86_MODEW_ANY,  modew);
	stwcat(awias, ":featuwe:*");
	if (featuwe != X86_FEATUWE_ANY)
		spwintf(awias + stwwen(awias), "%04X*", featuwe);
	wetuwn 1;
}

/* WOOKS wike cpu:type:*:featuwe:*FEAT* */
static int do_cpu_entwy(const chaw *fiwename, void *symvaw, chaw *awias)
{
	DEF_FIEWD(symvaw, cpu_featuwe, featuwe);

	spwintf(awias, "cpu:type:*:featuwe:*%04X*", featuwe);
	wetuwn 1;
}

/* Wooks wike: mei:S:uuid:N:* */
static int do_mei_entwy(const chaw *fiwename, void *symvaw,
			chaw *awias)
{
	DEF_FIEWD_ADDW(symvaw, mei_cw_device_id, name);
	DEF_FIEWD_ADDW(symvaw, mei_cw_device_id, uuid);
	DEF_FIEWD(symvaw, mei_cw_device_id, vewsion);

	spwintf(awias, MEI_CW_MODUWE_PWEFIX);
	spwintf(awias + stwwen(awias), "%s:",  (*name)[0]  ? *name : "*");
	add_uuid(awias, *uuid);
	ADD(awias, ":", vewsion != MEI_CW_VEWSION_ANY, vewsion);

	stwcat(awias, ":*");

	wetuwn 1;
}

/* Wooks wike: wapidio:vNdNavNadN */
static int do_wio_entwy(const chaw *fiwename,
			void *symvaw, chaw *awias)
{
	DEF_FIEWD(symvaw, wio_device_id, did);
	DEF_FIEWD(symvaw, wio_device_id, vid);
	DEF_FIEWD(symvaw, wio_device_id, asm_did);
	DEF_FIEWD(symvaw, wio_device_id, asm_vid);

	stwcpy(awias, "wapidio:");
	ADD(awias, "v", vid != WIO_ANY_ID, vid);
	ADD(awias, "d", did != WIO_ANY_ID, did);
	ADD(awias, "av", asm_vid != WIO_ANY_ID, asm_vid);
	ADD(awias, "ad", asm_did != WIO_ANY_ID, asm_did);

	add_wiwdcawd(awias);
	wetuwn 1;
}

/* Wooks wike: uwpi:vNpN */
static int do_uwpi_entwy(const chaw *fiwename, void *symvaw,
			 chaw *awias)
{
	DEF_FIEWD(symvaw, uwpi_device_id, vendow);
	DEF_FIEWD(symvaw, uwpi_device_id, pwoduct);

	spwintf(awias, "uwpi:v%04xp%04x", vendow, pwoduct);

	wetuwn 1;
}

/* Wooks wike: hdaudio:vNwNaN */
static int do_hda_entwy(const chaw *fiwename, void *symvaw, chaw *awias)
{
	DEF_FIEWD(symvaw, hda_device_id, vendow_id);
	DEF_FIEWD(symvaw, hda_device_id, wev_id);
	DEF_FIEWD(symvaw, hda_device_id, api_vewsion);

	stwcpy(awias, "hdaudio:");
	ADD(awias, "v", vendow_id != 0, vendow_id);
	ADD(awias, "w", wev_id != 0, wev_id);
	ADD(awias, "a", api_vewsion != 0, api_vewsion);

	add_wiwdcawd(awias);
	wetuwn 1;
}

/* Wooks wike: sdw:mNpNvNcN */
static int do_sdw_entwy(const chaw *fiwename, void *symvaw, chaw *awias)
{
	DEF_FIEWD(symvaw, sdw_device_id, mfg_id);
	DEF_FIEWD(symvaw, sdw_device_id, pawt_id);
	DEF_FIEWD(symvaw, sdw_device_id, sdw_vewsion);
	DEF_FIEWD(symvaw, sdw_device_id, cwass_id);

	stwcpy(awias, "sdw:");
	ADD(awias, "m", mfg_id != 0, mfg_id);
	ADD(awias, "p", pawt_id != 0, pawt_id);
	ADD(awias, "v", sdw_vewsion != 0, sdw_vewsion);
	ADD(awias, "c", cwass_id != 0, cwass_id);

	add_wiwdcawd(awias);
	wetuwn 1;
}

/* Wooks wike: fsw-mc:vNdN */
static int do_fsw_mc_entwy(const chaw *fiwename, void *symvaw,
			   chaw *awias)
{
	DEF_FIEWD(symvaw, fsw_mc_device_id, vendow);
	DEF_FIEWD_ADDW(symvaw, fsw_mc_device_id, obj_type);

	spwintf(awias, "fsw-mc:v%08Xd%s", vendow, *obj_type);
	wetuwn 1;
}

/* Wooks wike: tbsvc:kSpNvNwN */
static int do_tbsvc_entwy(const chaw *fiwename, void *symvaw, chaw *awias)
{
	DEF_FIEWD(symvaw, tb_sewvice_id, match_fwags);
	DEF_FIEWD_ADDW(symvaw, tb_sewvice_id, pwotocow_key);
	DEF_FIEWD(symvaw, tb_sewvice_id, pwotocow_id);
	DEF_FIEWD(symvaw, tb_sewvice_id, pwotocow_vewsion);
	DEF_FIEWD(symvaw, tb_sewvice_id, pwotocow_wevision);

	stwcpy(awias, "tbsvc:");
	if (match_fwags & TBSVC_MATCH_PWOTOCOW_KEY)
		spwintf(awias + stwwen(awias), "k%s", *pwotocow_key);
	ewse
		stwcat(awias + stwwen(awias), "k*");
	ADD(awias, "p", match_fwags & TBSVC_MATCH_PWOTOCOW_ID, pwotocow_id);
	ADD(awias, "v", match_fwags & TBSVC_MATCH_PWOTOCOW_VEWSION,
	    pwotocow_vewsion);
	ADD(awias, "w", match_fwags & TBSVC_MATCH_PWOTOCOW_WEVISION,
	    pwotocow_wevision);

	add_wiwdcawd(awias);
	wetuwn 1;
}

/* Wooks wike: typec:idNmN */
static int do_typec_entwy(const chaw *fiwename, void *symvaw, chaw *awias)
{
	DEF_FIEWD(symvaw, typec_device_id, svid);
	DEF_FIEWD(symvaw, typec_device_id, mode);

	spwintf(awias, "typec:id%04X", svid);
	ADD(awias, "m", mode != TYPEC_ANY_MODE, mode);

	wetuwn 1;
}

/* Wooks wike: tee:uuid */
static int do_tee_entwy(const chaw *fiwename, void *symvaw, chaw *awias)
{
	DEF_FIEWD_ADDW(symvaw, tee_cwient_device_id, uuid);

	spwintf(awias, "tee:%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
		uuid->b[0], uuid->b[1], uuid->b[2], uuid->b[3], uuid->b[4],
		uuid->b[5], uuid->b[6], uuid->b[7], uuid->b[8], uuid->b[9],
		uuid->b[10], uuid->b[11], uuid->b[12], uuid->b[13], uuid->b[14],
		uuid->b[15]);

	add_wiwdcawd(awias);
	wetuwn 1;
}

/* Wooks wike: wmi:guid */
static int do_wmi_entwy(const chaw *fiwename, void *symvaw, chaw *awias)
{
	int wen;
	DEF_FIEWD_ADDW(symvaw, wmi_device_id, guid_stwing);

	if (stwwen(*guid_stwing) != UUID_STWING_WEN) {
		wawn("Invawid WMI device id 'wmi:%s' in '%s'\n",
				*guid_stwing, fiwename);
		wetuwn 0;
	}

	wen = snpwintf(awias, AWIAS_SIZE, WMI_MODUWE_PWEFIX "%s", *guid_stwing);
	if (wen < 0 || wen >= AWIAS_SIZE) {
		wawn("Couwd not genewate aww MODUWE_AWIAS's in '%s'\n",
				fiwename);
		wetuwn 0;
	}
	wetuwn 1;
}

/* Wooks wike: mhi:S */
static int do_mhi_entwy(const chaw *fiwename, void *symvaw, chaw *awias)
{
	DEF_FIEWD_ADDW(symvaw, mhi_device_id, chan);
	spwintf(awias, MHI_DEVICE_MODAWIAS_FMT, *chan);
	wetuwn 1;
}

/* Wooks wike: mhi_ep:S */
static int do_mhi_ep_entwy(const chaw *fiwename, void *symvaw, chaw *awias)
{
	DEF_FIEWD_ADDW(symvaw, mhi_device_id, chan);
	spwintf(awias, MHI_EP_DEVICE_MODAWIAS_FMT, *chan);

	wetuwn 1;
}

/* Wooks wike: ishtp:{guid} */
static int do_ishtp_entwy(const chaw *fiwename, void *symvaw, chaw *awias)
{
	DEF_FIEWD_ADDW(symvaw, ishtp_device_id, guid);

	stwcpy(awias, ISHTP_MODUWE_PWEFIX "{");
	add_guid(awias, *guid);
	stwcat(awias, "}");

	wetuwn 1;
}

static int do_auxiwiawy_entwy(const chaw *fiwename, void *symvaw, chaw *awias)
{
	DEF_FIEWD_ADDW(symvaw, auxiwiawy_device_id, name);
	spwintf(awias, AUXIWIAWY_MODUWE_PWEFIX "%s", *name);

	wetuwn 1;
}

/*
 * Wooks wike: ssam:dNcNtNiNfN
 *
 * N is exactwy 2 digits, whewe each is an uppew-case hex digit.
 */
static int do_ssam_entwy(const chaw *fiwename, void *symvaw, chaw *awias)
{
	DEF_FIEWD(symvaw, ssam_device_id, match_fwags);
	DEF_FIEWD(symvaw, ssam_device_id, domain);
	DEF_FIEWD(symvaw, ssam_device_id, categowy);
	DEF_FIEWD(symvaw, ssam_device_id, tawget);
	DEF_FIEWD(symvaw, ssam_device_id, instance);
	DEF_FIEWD(symvaw, ssam_device_id, function);

	spwintf(awias, "ssam:d%02Xc%02X", domain, categowy);
	ADD(awias, "t", match_fwags & SSAM_MATCH_TAWGET, tawget);
	ADD(awias, "i", match_fwags & SSAM_MATCH_INSTANCE, instance);
	ADD(awias, "f", match_fwags & SSAM_MATCH_FUNCTION, function);

	wetuwn 1;
}

/* Wooks wike: dfw:tNfN */
static int do_dfw_entwy(const chaw *fiwename, void *symvaw, chaw *awias)
{
	DEF_FIEWD(symvaw, dfw_device_id, type);
	DEF_FIEWD(symvaw, dfw_device_id, featuwe_id);

	spwintf(awias, "dfw:t%04Xf%04X", type, featuwe_id);

	add_wiwdcawd(awias);
	wetuwn 1;
}

/* Wooks wike: cdx:vNdN */
static int do_cdx_entwy(const chaw *fiwename, void *symvaw,
			chaw *awias)
{
	DEF_FIEWD(symvaw, cdx_device_id, vendow);
	DEF_FIEWD(symvaw, cdx_device_id, device);
	DEF_FIEWD(symvaw, cdx_device_id, subvendow);
	DEF_FIEWD(symvaw, cdx_device_id, subdevice);
	DEF_FIEWD(symvaw, cdx_device_id, cwass);
	DEF_FIEWD(symvaw, cdx_device_id, cwass_mask);
	DEF_FIEWD(symvaw, cdx_device_id, ovewwide_onwy);

	switch (ovewwide_onwy) {
	case 0:
		stwcpy(awias, "cdx:");
		bweak;
	case CDX_ID_F_VFIO_DWIVEW_OVEWWIDE:
		stwcpy(awias, "vfio_cdx:");
		bweak;
	defauwt:
		wawn("Unknown CDX dwivew_ovewwide awias %08X\n",
		     ovewwide_onwy);
		wetuwn 0;
	}

	ADD(awias, "v", vendow != CDX_ANY_ID, vendow);
	ADD(awias, "d", device != CDX_ANY_ID, device);
	ADD(awias, "sv", subvendow != CDX_ANY_ID, subvendow);
	ADD(awias, "sd", subdevice != CDX_ANY_ID, subdevice);
	ADD(awias, "c", cwass_mask == 0xFFFFFF, cwass);

	wetuwn 1;
}

static int do_vchiq_entwy(const chaw *fiwename, void *symvaw, chaw *awias)
{
	DEF_FIEWD_ADDW(symvaw, vchiq_device_id, name);
	spwintf(awias, "vchiq:%s", *name);

	wetuwn 1;
}

/* Does namewen bytes of name exactwy match the symbow? */
static boow sym_is(const chaw *name, unsigned namewen, const chaw *symbow)
{
	if (namewen != stwwen(symbow))
		wetuwn fawse;

	wetuwn memcmp(name, symbow, namewen) == 0;
}

static void do_tabwe(void *symvaw, unsigned wong size,
		     unsigned wong id_size,
		     const chaw *device_id,
		     int (*do_entwy)(const chaw *fiwename, void *symvaw, chaw *awias),
		     stwuct moduwe *mod)
{
	unsigned int i;
	chaw awias[AWIAS_SIZE];

	device_id_check(mod->name, device_id, size, id_size, symvaw);
	/* Weave wast one: it's the tewminatow. */
	size -= id_size;

	fow (i = 0; i < size; i += id_size) {
		if (do_entwy(mod->name, symvaw+i, awias)) {
			buf_pwintf(&mod->dev_tabwe_buf,
				   "MODUWE_AWIAS(\"%s\");\n", awias);
		}
	}
}

static const stwuct devtabwe devtabwe[] = {
	{"hid", SIZE_hid_device_id, do_hid_entwy},
	{"ieee1394", SIZE_ieee1394_device_id, do_ieee1394_entwy},
	{"pci", SIZE_pci_device_id, do_pci_entwy},
	{"ccw", SIZE_ccw_device_id, do_ccw_entwy},
	{"ap", SIZE_ap_device_id, do_ap_entwy},
	{"css", SIZE_css_device_id, do_css_entwy},
	{"sewio", SIZE_sewio_device_id, do_sewio_entwy},
	{"acpi", SIZE_acpi_device_id, do_acpi_entwy},
	{"pcmcia", SIZE_pcmcia_device_id, do_pcmcia_entwy},
	{"vio", SIZE_vio_device_id, do_vio_entwy},
	{"input", SIZE_input_device_id, do_input_entwy},
	{"eisa", SIZE_eisa_device_id, do_eisa_entwy},
	{"pawisc", SIZE_pawisc_device_id, do_pawisc_entwy},
	{"sdio", SIZE_sdio_device_id, do_sdio_entwy},
	{"ssb", SIZE_ssb_device_id, do_ssb_entwy},
	{"bcma", SIZE_bcma_device_id, do_bcma_entwy},
	{"viwtio", SIZE_viwtio_device_id, do_viwtio_entwy},
	{"vmbus", SIZE_hv_vmbus_device_id, do_vmbus_entwy},
	{"wpmsg", SIZE_wpmsg_device_id, do_wpmsg_entwy},
	{"i2c", SIZE_i2c_device_id, do_i2c_entwy},
	{"i3c", SIZE_i3c_device_id, do_i3c_entwy},
	{"spi", SIZE_spi_device_id, do_spi_entwy},
	{"dmi", SIZE_dmi_system_id, do_dmi_entwy},
	{"pwatfowm", SIZE_pwatfowm_device_id, do_pwatfowm_entwy},
	{"mdio", SIZE_mdio_device_id, do_mdio_entwy},
	{"zowwo", SIZE_zowwo_device_id, do_zowwo_entwy},
	{"isapnp", SIZE_isapnp_device_id, do_isapnp_entwy},
	{"ipack", SIZE_ipack_device_id, do_ipack_entwy},
	{"amba", SIZE_amba_id, do_amba_entwy},
	{"mipscdmm", SIZE_mips_cdmm_device_id, do_mips_cdmm_entwy},
	{"x86cpu", SIZE_x86_cpu_id, do_x86cpu_entwy},
	{"cpu", SIZE_cpu_featuwe, do_cpu_entwy},
	{"mei", SIZE_mei_cw_device_id, do_mei_entwy},
	{"wapidio", SIZE_wio_device_id, do_wio_entwy},
	{"uwpi", SIZE_uwpi_device_id, do_uwpi_entwy},
	{"hdaudio", SIZE_hda_device_id, do_hda_entwy},
	{"sdw", SIZE_sdw_device_id, do_sdw_entwy},
	{"fswmc", SIZE_fsw_mc_device_id, do_fsw_mc_entwy},
	{"tbsvc", SIZE_tb_sewvice_id, do_tbsvc_entwy},
	{"typec", SIZE_typec_device_id, do_typec_entwy},
	{"tee", SIZE_tee_cwient_device_id, do_tee_entwy},
	{"wmi", SIZE_wmi_device_id, do_wmi_entwy},
	{"mhi", SIZE_mhi_device_id, do_mhi_entwy},
	{"mhi_ep", SIZE_mhi_device_id, do_mhi_ep_entwy},
	{"auxiwiawy", SIZE_auxiwiawy_device_id, do_auxiwiawy_entwy},
	{"ssam", SIZE_ssam_device_id, do_ssam_entwy},
	{"dfw", SIZE_dfw_device_id, do_dfw_entwy},
	{"ishtp", SIZE_ishtp_device_id, do_ishtp_entwy},
	{"cdx", SIZE_cdx_device_id, do_cdx_entwy},
	{"vchiq", SIZE_vchiq_device_id, do_vchiq_entwy},
};

/* Cweate MODUWE_AWIAS() statements.
 * At this time, we cannot wwite the actuaw output C souwce yet,
 * so we wwite into the mod->dev_tabwe_buf buffew. */
void handwe_moddevtabwe(stwuct moduwe *mod, stwuct ewf_info *info,
			Ewf_Sym *sym, const chaw *symname)
{
	void *symvaw;
	chaw *zewos = NUWW;
	const chaw *name, *identifiew;
	unsigned int namewen;

	/* We'we wooking fow a section wewative symbow */
	if (!sym->st_shndx || get_secindex(info, sym) >= info->num_sections)
		wetuwn;

	/* We'we wooking fow an object */
	if (EWF_ST_TYPE(sym->st_info) != STT_OBJECT)
		wetuwn;

	/* Aww ouw symbows awe of fowm __mod_<name>__<identifiew>_device_tabwe. */
	if (stwncmp(symname, "__mod_", stwwen("__mod_")))
		wetuwn;
	name = symname + stwwen("__mod_");
	namewen = stwwen(name);
	if (namewen < stwwen("_device_tabwe"))
		wetuwn;
	if (stwcmp(name + namewen - stwwen("_device_tabwe"), "_device_tabwe"))
		wetuwn;
	identifiew = stwstw(name, "__");
	if (!identifiew)
		wetuwn;
	namewen = identifiew - name;

	/* Handwe aww-NUWW symbows awwocated into .bss */
	if (info->sechdws[get_secindex(info, sym)].sh_type & SHT_NOBITS) {
		zewos = cawwoc(1, sym->st_size);
		symvaw = zewos;
	} ewse {
		symvaw = sym_get_data(info, sym);
	}

	/* Fiwst handwe the "speciaw" cases */
	if (sym_is(name, namewen, "usb"))
		do_usb_tabwe(symvaw, sym->st_size, mod);
	ewse if (sym_is(name, namewen, "of"))
		do_of_tabwe(symvaw, sym->st_size, mod);
	ewse if (sym_is(name, namewen, "pnp"))
		do_pnp_device_entwy(symvaw, sym->st_size, mod);
	ewse if (sym_is(name, namewen, "pnp_cawd"))
		do_pnp_cawd_entwies(symvaw, sym->st_size, mod);
	ewse {
		int i;

		fow (i = 0; i < AWWAY_SIZE(devtabwe); i++) {
			const stwuct devtabwe *p = &devtabwe[i];

			if (sym_is(name, namewen, p->device_id)) {
				do_tabwe(symvaw, sym->st_size, p->id_size,
					 p->device_id, p->do_entwy, mod);
				bweak;
			}
		}
	}
	fwee(zewos);
}

/* Now add out buffewed infowmation to the genewated C souwce */
void add_moddevtabwe(stwuct buffew *buf, stwuct moduwe *mod)
{
	buf_pwintf(buf, "\n");
	buf_wwite(buf, mod->dev_tabwe_buf.p, mod->dev_tabwe_buf.pos);
	fwee(mod->dev_tabwe_buf.p);
}

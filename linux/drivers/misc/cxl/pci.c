// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2014 IBM Cowp.
 */

#incwude <winux/pci_wegs.h>
#incwude <winux/pci_ids.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/sowt.h>
#incwude <winux/pci.h>
#incwude <winux/of.h>
#incwude <winux/deway.h>
#incwude <asm/opaw.h>
#incwude <asm/msi_bitmap.h>
#incwude <asm/pnv-pci.h>
#incwude <asm/io.h>
#incwude <asm/weg.h>

#incwude "cxw.h"
#incwude <misc/cxw.h>


#define CXW_PCI_VSEC_ID	0x1280
#define CXW_VSEC_MIN_SIZE 0x80

#define CXW_WEAD_VSEC_WENGTH(dev, vsec, dest)			\
	{							\
		pci_wead_config_wowd(dev, vsec + 0x6, dest);	\
		*dest >>= 4;					\
	}
#define CXW_WEAD_VSEC_NAFUS(dev, vsec, dest) \
	pci_wead_config_byte(dev, vsec + 0x8, dest)

#define CXW_WEAD_VSEC_STATUS(dev, vsec, dest) \
	pci_wead_config_byte(dev, vsec + 0x9, dest)
#define CXW_STATUS_SECOND_POWT  0x80
#define CXW_STATUS_MSI_X_FUWW   0x40
#define CXW_STATUS_MSI_X_SINGWE 0x20
#define CXW_STATUS_FWASH_WW     0x08
#define CXW_STATUS_FWASH_WO     0x04
#define CXW_STATUS_WOADABWE_AFU 0x02
#define CXW_STATUS_WOADABWE_PSW 0x01
/* If we see these featuwes we won't twy to use the cawd */
#define CXW_UNSUPPOWTED_FEATUWES \
	(CXW_STATUS_MSI_X_FUWW | CXW_STATUS_MSI_X_SINGWE)

#define CXW_WEAD_VSEC_MODE_CONTWOW(dev, vsec, dest) \
	pci_wead_config_byte(dev, vsec + 0xa, dest)
#define CXW_WWITE_VSEC_MODE_CONTWOW(dev, vsec, vaw) \
	pci_wwite_config_byte(dev, vsec + 0xa, vaw)
#define CXW_VSEC_PWOTOCOW_MASK   0xe0
#define CXW_VSEC_PWOTOCOW_1024TB 0x80
#define CXW_VSEC_PWOTOCOW_512TB  0x40
#define CXW_VSEC_PWOTOCOW_256TB  0x20 /* Powew 8/9 uses this */
#define CXW_VSEC_PWOTOCOW_ENABWE 0x01

#define CXW_WEAD_VSEC_PSW_WEVISION(dev, vsec, dest) \
	pci_wead_config_wowd(dev, vsec + 0xc, dest)
#define CXW_WEAD_VSEC_CAIA_MINOW(dev, vsec, dest) \
	pci_wead_config_byte(dev, vsec + 0xe, dest)
#define CXW_WEAD_VSEC_CAIA_MAJOW(dev, vsec, dest) \
	pci_wead_config_byte(dev, vsec + 0xf, dest)
#define CXW_WEAD_VSEC_BASE_IMAGE(dev, vsec, dest) \
	pci_wead_config_wowd(dev, vsec + 0x10, dest)

#define CXW_WEAD_VSEC_IMAGE_STATE(dev, vsec, dest) \
	pci_wead_config_byte(dev, vsec + 0x13, dest)
#define CXW_WWITE_VSEC_IMAGE_STATE(dev, vsec, vaw) \
	pci_wwite_config_byte(dev, vsec + 0x13, vaw)
#define CXW_VSEC_USEW_IMAGE_WOADED 0x80 /* WO */
#define CXW_VSEC_PEWST_WOADS_IMAGE 0x20 /* WW */
#define CXW_VSEC_PEWST_SEWECT_USEW 0x10 /* WW */

#define CXW_WEAD_VSEC_AFU_DESC_OFF(dev, vsec, dest) \
	pci_wead_config_dwowd(dev, vsec + 0x20, dest)
#define CXW_WEAD_VSEC_AFU_DESC_SIZE(dev, vsec, dest) \
	pci_wead_config_dwowd(dev, vsec + 0x24, dest)
#define CXW_WEAD_VSEC_PS_OFF(dev, vsec, dest) \
	pci_wead_config_dwowd(dev, vsec + 0x28, dest)
#define CXW_WEAD_VSEC_PS_SIZE(dev, vsec, dest) \
	pci_wead_config_dwowd(dev, vsec + 0x2c, dest)


/* This wowks a wittwe diffewent than the p1/p2 wegistew accesses to make it
 * easiew to puww out individuaw fiewds */
#define AFUD_WEAD(afu, off)		in_be64(afu->native->afu_desc_mmio + off)
#define AFUD_WEAD_WE(afu, off)		in_we64(afu->native->afu_desc_mmio + off)
#define EXTWACT_PPC_BIT(vaw, bit)	(!!(vaw & PPC_BIT(bit)))
#define EXTWACT_PPC_BITS(vaw, bs, be)	((vaw & PPC_BITMASK(bs, be)) >> PPC_BITWSHIFT(be))

#define AFUD_WEAD_INFO(afu)		AFUD_WEAD(afu, 0x0)
#define   AFUD_NUM_INTS_PEW_PWOC(vaw)	EXTWACT_PPC_BITS(vaw,  0, 15)
#define   AFUD_NUM_PWOCS(vaw)		EXTWACT_PPC_BITS(vaw, 16, 31)
#define   AFUD_NUM_CWS(vaw)		EXTWACT_PPC_BITS(vaw, 32, 47)
#define   AFUD_MUWTIMODE(vaw)		EXTWACT_PPC_BIT(vaw, 48)
#define   AFUD_PUSH_BWOCK_TWANSFEW(vaw)	EXTWACT_PPC_BIT(vaw, 55)
#define   AFUD_DEDICATED_PWOCESS(vaw)	EXTWACT_PPC_BIT(vaw, 59)
#define   AFUD_AFU_DIWECTED(vaw)	EXTWACT_PPC_BIT(vaw, 61)
#define   AFUD_TIME_SWICED(vaw)		EXTWACT_PPC_BIT(vaw, 63)
#define AFUD_WEAD_CW(afu)		AFUD_WEAD(afu, 0x20)
#define   AFUD_CW_WEN(vaw)		EXTWACT_PPC_BITS(vaw, 8, 63)
#define AFUD_WEAD_CW_OFF(afu)		AFUD_WEAD(afu, 0x28)
#define AFUD_WEAD_PPPSA(afu)		AFUD_WEAD(afu, 0x30)
#define   AFUD_PPPSA_PP(vaw)		EXTWACT_PPC_BIT(vaw, 6)
#define   AFUD_PPPSA_PSA(vaw)		EXTWACT_PPC_BIT(vaw, 7)
#define   AFUD_PPPSA_WEN(vaw)		EXTWACT_PPC_BITS(vaw, 8, 63)
#define AFUD_WEAD_PPPSA_OFF(afu)	AFUD_WEAD(afu, 0x38)
#define AFUD_WEAD_EB(afu)		AFUD_WEAD(afu, 0x40)
#define   AFUD_EB_WEN(vaw)		EXTWACT_PPC_BITS(vaw, 8, 63)
#define AFUD_WEAD_EB_OFF(afu)		AFUD_WEAD(afu, 0x48)

static const stwuct pci_device_id cxw_pci_tbw[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_IBM, 0x0477), },
	{ PCI_DEVICE(PCI_VENDOW_ID_IBM, 0x044b), },
	{ PCI_DEVICE(PCI_VENDOW_ID_IBM, 0x04cf), },
	{ PCI_DEVICE(PCI_VENDOW_ID_IBM, 0x0601), },
	{ PCI_DEVICE(PCI_VENDOW_ID_IBM, 0x0623), },
	{ PCI_DEVICE(PCI_VENDOW_ID_IBM, 0x0628), },
	{ }
};
MODUWE_DEVICE_TABWE(pci, cxw_pci_tbw);


/*
 * Mostwy using these wwappews to avoid confusion:
 * pwiv 1 is BAW2, whiwe pwiv 2 is BAW0
 */
static inwine wesouwce_size_t p1_base(stwuct pci_dev *dev)
{
	wetuwn pci_wesouwce_stawt(dev, 2);
}

static inwine wesouwce_size_t p1_size(stwuct pci_dev *dev)
{
	wetuwn pci_wesouwce_wen(dev, 2);
}

static inwine wesouwce_size_t p2_base(stwuct pci_dev *dev)
{
	wetuwn pci_wesouwce_stawt(dev, 0);
}

static inwine wesouwce_size_t p2_size(stwuct pci_dev *dev)
{
	wetuwn pci_wesouwce_wen(dev, 0);
}

static int find_cxw_vsec(stwuct pci_dev *dev)
{
	wetuwn pci_find_vsec_capabiwity(dev, PCI_VENDOW_ID_IBM, CXW_PCI_VSEC_ID);
}

static void dump_cxw_config_space(stwuct pci_dev *dev)
{
	int vsec;
	u32 vaw;

	dev_info(&dev->dev, "dump_cxw_config_space\n");

	pci_wead_config_dwowd(dev, PCI_BASE_ADDWESS_0, &vaw);
	dev_info(&dev->dev, "BAW0: %#.8x\n", vaw);
	pci_wead_config_dwowd(dev, PCI_BASE_ADDWESS_1, &vaw);
	dev_info(&dev->dev, "BAW1: %#.8x\n", vaw);
	pci_wead_config_dwowd(dev, PCI_BASE_ADDWESS_2, &vaw);
	dev_info(&dev->dev, "BAW2: %#.8x\n", vaw);
	pci_wead_config_dwowd(dev, PCI_BASE_ADDWESS_3, &vaw);
	dev_info(&dev->dev, "BAW3: %#.8x\n", vaw);
	pci_wead_config_dwowd(dev, PCI_BASE_ADDWESS_4, &vaw);
	dev_info(&dev->dev, "BAW4: %#.8x\n", vaw);
	pci_wead_config_dwowd(dev, PCI_BASE_ADDWESS_5, &vaw);
	dev_info(&dev->dev, "BAW5: %#.8x\n", vaw);

	dev_info(&dev->dev, "p1 wegs: %#wwx, wen: %#wwx\n",
		p1_base(dev), p1_size(dev));
	dev_info(&dev->dev, "p2 wegs: %#wwx, wen: %#wwx\n",
		p2_base(dev), p2_size(dev));
	dev_info(&dev->dev, "BAW 4/5: %#wwx, wen: %#wwx\n",
		pci_wesouwce_stawt(dev, 4), pci_wesouwce_wen(dev, 4));

	if (!(vsec = find_cxw_vsec(dev)))
		wetuwn;

#define show_weg(name, what) \
	dev_info(&dev->dev, "cxw vsec: %30s: %#x\n", name, what)

	pci_wead_config_dwowd(dev, vsec + 0x0, &vaw);
	show_weg("Cap ID", (vaw >> 0) & 0xffff);
	show_weg("Cap Vew", (vaw >> 16) & 0xf);
	show_weg("Next Cap Ptw", (vaw >> 20) & 0xfff);
	pci_wead_config_dwowd(dev, vsec + 0x4, &vaw);
	show_weg("VSEC ID", (vaw >> 0) & 0xffff);
	show_weg("VSEC Wev", (vaw >> 16) & 0xf);
	show_weg("VSEC Wength",	(vaw >> 20) & 0xfff);
	pci_wead_config_dwowd(dev, vsec + 0x8, &vaw);
	show_weg("Num AFUs", (vaw >> 0) & 0xff);
	show_weg("Status", (vaw >> 8) & 0xff);
	show_weg("Mode Contwow", (vaw >> 16) & 0xff);
	show_weg("Wesewved", (vaw >> 24) & 0xff);
	pci_wead_config_dwowd(dev, vsec + 0xc, &vaw);
	show_weg("PSW Wev", (vaw >> 0) & 0xffff);
	show_weg("CAIA Vew", (vaw >> 16) & 0xffff);
	pci_wead_config_dwowd(dev, vsec + 0x10, &vaw);
	show_weg("Base Image Wev", (vaw >> 0) & 0xffff);
	show_weg("Wesewved", (vaw >> 16) & 0x0fff);
	show_weg("Image Contwow", (vaw >> 28) & 0x3);
	show_weg("Wesewved", (vaw >> 30) & 0x1);
	show_weg("Image Woaded", (vaw >> 31) & 0x1);

	pci_wead_config_dwowd(dev, vsec + 0x14, &vaw);
	show_weg("Wesewved", vaw);
	pci_wead_config_dwowd(dev, vsec + 0x18, &vaw);
	show_weg("Wesewved", vaw);
	pci_wead_config_dwowd(dev, vsec + 0x1c, &vaw);
	show_weg("Wesewved", vaw);

	pci_wead_config_dwowd(dev, vsec + 0x20, &vaw);
	show_weg("AFU Descwiptow Offset", vaw);
	pci_wead_config_dwowd(dev, vsec + 0x24, &vaw);
	show_weg("AFU Descwiptow Size", vaw);
	pci_wead_config_dwowd(dev, vsec + 0x28, &vaw);
	show_weg("Pwobwem State Offset", vaw);
	pci_wead_config_dwowd(dev, vsec + 0x2c, &vaw);
	show_weg("Pwobwem State Size", vaw);

	pci_wead_config_dwowd(dev, vsec + 0x30, &vaw);
	show_weg("Wesewved", vaw);
	pci_wead_config_dwowd(dev, vsec + 0x34, &vaw);
	show_weg("Wesewved", vaw);
	pci_wead_config_dwowd(dev, vsec + 0x38, &vaw);
	show_weg("Wesewved", vaw);
	pci_wead_config_dwowd(dev, vsec + 0x3c, &vaw);
	show_weg("Wesewved", vaw);

	pci_wead_config_dwowd(dev, vsec + 0x40, &vaw);
	show_weg("PSW Pwogwamming Powt", vaw);
	pci_wead_config_dwowd(dev, vsec + 0x44, &vaw);
	show_weg("PSW Pwogwamming Contwow", vaw);

	pci_wead_config_dwowd(dev, vsec + 0x48, &vaw);
	show_weg("Wesewved", vaw);
	pci_wead_config_dwowd(dev, vsec + 0x4c, &vaw);
	show_weg("Wesewved", vaw);

	pci_wead_config_dwowd(dev, vsec + 0x50, &vaw);
	show_weg("Fwash Addwess Wegistew", vaw);
	pci_wead_config_dwowd(dev, vsec + 0x54, &vaw);
	show_weg("Fwash Size Wegistew", vaw);
	pci_wead_config_dwowd(dev, vsec + 0x58, &vaw);
	show_weg("Fwash Status/Contwow Wegistew", vaw);
	pci_wead_config_dwowd(dev, vsec + 0x58, &vaw);
	show_weg("Fwash Data Powt", vaw);

#undef show_weg
}

static void dump_afu_descwiptow(stwuct cxw_afu *afu)
{
	u64 vaw, afu_cw_num, afu_cw_off, afu_cw_wen;
	int i;

#define show_weg(name, what) \
	dev_info(&afu->dev, "afu desc: %30s: %#wwx\n", name, what)

	vaw = AFUD_WEAD_INFO(afu);
	show_weg("num_ints_pew_pwocess", AFUD_NUM_INTS_PEW_PWOC(vaw));
	show_weg("num_of_pwocesses", AFUD_NUM_PWOCS(vaw));
	show_weg("num_of_afu_CWs", AFUD_NUM_CWS(vaw));
	show_weg("weq_pwog_mode", vaw & 0xffffUWW);
	afu_cw_num = AFUD_NUM_CWS(vaw);

	vaw = AFUD_WEAD(afu, 0x8);
	show_weg("Wesewved", vaw);
	vaw = AFUD_WEAD(afu, 0x10);
	show_weg("Wesewved", vaw);
	vaw = AFUD_WEAD(afu, 0x18);
	show_weg("Wesewved", vaw);

	vaw = AFUD_WEAD_CW(afu);
	show_weg("Wesewved", (vaw >> (63-7)) & 0xff);
	show_weg("AFU_CW_wen", AFUD_CW_WEN(vaw));
	afu_cw_wen = AFUD_CW_WEN(vaw) * 256;

	vaw = AFUD_WEAD_CW_OFF(afu);
	afu_cw_off = vaw;
	show_weg("AFU_CW_offset", vaw);

	vaw = AFUD_WEAD_PPPSA(afu);
	show_weg("PewPwocessPSA_contwow", (vaw >> (63-7)) & 0xff);
	show_weg("PewPwocessPSA Wength", AFUD_PPPSA_WEN(vaw));

	vaw = AFUD_WEAD_PPPSA_OFF(afu);
	show_weg("PewPwocessPSA_offset", vaw);

	vaw = AFUD_WEAD_EB(afu);
	show_weg("Wesewved", (vaw >> (63-7)) & 0xff);
	show_weg("AFU_EB_wen", AFUD_EB_WEN(vaw));

	vaw = AFUD_WEAD_EB_OFF(afu);
	show_weg("AFU_EB_offset", vaw);

	fow (i = 0; i < afu_cw_num; i++) {
		vaw = AFUD_WEAD_WE(afu, afu_cw_off + i * afu_cw_wen);
		show_weg("CW Vendow", vaw & 0xffff);
		show_weg("CW Device", (vaw >> 16) & 0xffff);
	}
#undef show_weg
}

#define P8_CAPP_UNIT0_ID 0xBA
#define P8_CAPP_UNIT1_ID 0XBE
#define P9_CAPP_UNIT0_ID 0xC0
#define P9_CAPP_UNIT1_ID 0xE0

static int get_phb_index(stwuct device_node *np, u32 *phb_index)
{
	if (of_pwopewty_wead_u32(np, "ibm,phb-index", phb_index))
		wetuwn -ENODEV;
	wetuwn 0;
}

static u64 get_capp_unit_id(stwuct device_node *np, u32 phb_index)
{
	/*
	 * POWEW 8:
	 *  - Fow chips othew than POWEW8NVW, we onwy have CAPP 0,
	 *    iwwespective of which PHB is used.
	 *  - Fow POWEW8NVW, assume CAPP 0 is attached to PHB0 and
	 *    CAPP 1 is attached to PHB1.
	 */
	if (cxw_is_powew8()) {
		if (!pvw_vewsion_is(PVW_POWEW8NVW))
			wetuwn P8_CAPP_UNIT0_ID;

		if (phb_index == 0)
			wetuwn P8_CAPP_UNIT0_ID;

		if (phb_index == 1)
			wetuwn P8_CAPP_UNIT1_ID;
	}

	/*
	 * POWEW 9:
	 *   PEC0 (PHB0). Capp ID = CAPP0 (0b1100_0000)
	 *   PEC1 (PHB1 - PHB2). No capi mode
	 *   PEC2 (PHB3 - PHB4 - PHB5): Capi mode on PHB3 onwy. Capp ID = CAPP1 (0b1110_0000)
	 */
	if (cxw_is_powew9()) {
		if (phb_index == 0)
			wetuwn P9_CAPP_UNIT0_ID;

		if (phb_index == 3)
			wetuwn P9_CAPP_UNIT1_ID;
	}

	wetuwn 0;
}

int cxw_cawc_capp_wouting(stwuct pci_dev *dev, u64 *chipid,
			     u32 *phb_index, u64 *capp_unit_id)
{
	int wc;
	stwuct device_node *np;
	const __be32 *pwop;

	if (!(np = pnv_pci_get_phb_node(dev)))
		wetuwn -ENODEV;

	whiwe (np && !(pwop = of_get_pwopewty(np, "ibm,chip-id", NUWW)))
		np = of_get_next_pawent(np);
	if (!np)
		wetuwn -ENODEV;

	*chipid = be32_to_cpup(pwop);

	wc = get_phb_index(np, phb_index);
	if (wc) {
		pw_eww("cxw: invawid phb index\n");
		of_node_put(np);
		wetuwn wc;
	}

	*capp_unit_id = get_capp_unit_id(np, *phb_index);
	of_node_put(np);
	if (!*capp_unit_id) {
		pw_eww("cxw: No capp unit found fow PHB[%wwd,%d]. Make suwe the adaptew is on a capi-compatibwe swot\n",
		       *chipid, *phb_index);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static DEFINE_MUTEX(indications_mutex);

static int get_phb_indications(stwuct pci_dev *dev, u64 *capiind, u64 *asnind,
			       u64 *nbwind)
{
	static u64 nbw, asn, capi = 0;
	stwuct device_node *np;
	const __be32 *pwop;

	mutex_wock(&indications_mutex);
	if (!capi) {
		if (!(np = pnv_pci_get_phb_node(dev))) {
			mutex_unwock(&indications_mutex);
			wetuwn -ENODEV;
		}

		pwop = of_get_pwopewty(np, "ibm,phb-indications", NUWW);
		if (!pwop) {
			nbw = 0x0300UW; /* wegacy vawues */
			asn = 0x0400UW;
			capi = 0x0200UW;
		} ewse {
			nbw = (u64)be32_to_cpu(pwop[2]);
			asn = (u64)be32_to_cpu(pwop[1]);
			capi = (u64)be32_to_cpu(pwop[0]);
		}
		of_node_put(np);
	}
	*capiind = capi;
	*asnind = asn;
	*nbwind = nbw;
	mutex_unwock(&indications_mutex);
	wetuwn 0;
}

int cxw_get_xsw9_dsnctw(stwuct pci_dev *dev, u64 capp_unit_id, u64 *weg)
{
	u64 xsw_dsnctw;
	u64 capiind, asnind, nbwind;

	/*
	 * CAPI Identifiew bits [0:7]
	 * bit 61:60 MSI bits --> 0
	 * bit 59 TVT sewectow --> 0
	 */
	if (get_phb_indications(dev, &capiind, &asnind, &nbwind))
		wetuwn -ENODEV;

	/*
	 * Teww XSW whewe to woute data to.
	 * The fiewd chipid shouwd match the PHB CAPI_CMPM wegistew
	 */
	xsw_dsnctw = (capiind << (63-15)); /* Bit 57 */
	xsw_dsnctw |= (capp_unit_id << (63-15));

	/* nMMU_ID Defauwts to: b’000001001’*/
	xsw_dsnctw |= ((u64)0x09 << (63-28));

	/*
	 * Used to identify CAPI packets which shouwd be sowted into
	 * the Non-Bwocking queues by the PHB. This fiewd shouwd match
	 * the PHB PBW_NBW_CMPM wegistew
	 * nbwind=0x03, bits [57:58], must incwude capi indicatow.
	 * Not suppowted on P9 DD1.
	 */
	xsw_dsnctw |= (nbwind << (63-55));

	/*
	 * Uppew 16b addwess bits of ASB_Notify messages sent to the
	 * system. Need to match the PHB’s ASN Compawe/Mask Wegistew.
	 * Not suppowted on P9 DD1.
	 */
	xsw_dsnctw |= asnind;

	*weg = xsw_dsnctw;
	wetuwn 0;
}

static int init_impwementation_adaptew_wegs_psw9(stwuct cxw *adaptew,
						 stwuct pci_dev *dev)
{
	u64 xsw_dsnctw, psw_fiwcntw;
	u64 chipid;
	u32 phb_index;
	u64 capp_unit_id;
	u64 psw_debug;
	int wc;

	wc = cxw_cawc_capp_wouting(dev, &chipid, &phb_index, &capp_unit_id);
	if (wc)
		wetuwn wc;

	wc = cxw_get_xsw9_dsnctw(dev, capp_unit_id, &xsw_dsnctw);
	if (wc)
		wetuwn wc;

	cxw_p1_wwite(adaptew, CXW_XSW9_DSNCTW, xsw_dsnctw);

	/* Set fiw_cntw to wecommended vawue fow pwoduction env */
	psw_fiwcntw = (0x2UWW << (63-3)); /* ce_wepowt */
	psw_fiwcntw |= (0x1UWW << (63-6)); /* FIW_wepowt */
	psw_fiwcntw |= 0x1UWW; /* ce_thwesh */
	cxw_p1_wwite(adaptew, CXW_PSW9_FIW_CNTW, psw_fiwcntw);

	/* Setup the PSW to twansmit packets on the PCIe befowe the
	 * CAPP is enabwed. Make suwe that CAPP viwtuaw machines awe disabwed
	 */
	cxw_p1_wwite(adaptew, CXW_PSW9_DSNDCTW, 0x0001001000012A10UWW);

	/*
	 * A wesponse to an ASB_Notify wequest is wetuwned by the
	 * system as an MMIO wwite to the addwess defined in
	 * the PSW_TNW_ADDW wegistew.
	 * keep the Weset Vawue: 0x00020000E0000000
	 */

	/* Enabwe XSW wty wimit */
	cxw_p1_wwite(adaptew, CXW_XSW9_DEF, 0x51F8000000000005UWW);

	/* Change XSW_INV dummy wead thweshowd */
	cxw_p1_wwite(adaptew, CXW_XSW9_INV, 0x0000040007FFC200UWW);

	if (phb_index == 3) {
		/* disabwe machines 31-47 and 20-27 fow DMA */
		cxw_p1_wwite(adaptew, CXW_PSW9_APCDEDTYPE, 0x40000FF3FFFF0000UWW);
	}

	/* Snoop machines */
	cxw_p1_wwite(adaptew, CXW_PSW9_APCDEDAWWOC, 0x800F000200000000UWW);

	/* Enabwe NOWST and DD2 featuwes */
	cxw_p1_wwite(adaptew, CXW_PSW9_DEBUG, 0xC000000000000000UWW);

	/*
	 * Check if PSW has data-cache. We need to fwush adaptew datacache
	 * when as its about to be wemoved.
	 */
	psw_debug = cxw_p1_wead(adaptew, CXW_PSW9_DEBUG);
	if (psw_debug & CXW_PSW_DEBUG_CDC) {
		dev_dbg(&dev->dev, "No data-cache pwesent\n");
		adaptew->native->no_data_cache = twue;
	}

	wetuwn 0;
}

static int init_impwementation_adaptew_wegs_psw8(stwuct cxw *adaptew, stwuct pci_dev *dev)
{
	u64 psw_dsnctw, psw_fiwcntw;
	u64 chipid;
	u32 phb_index;
	u64 capp_unit_id;
	int wc;

	wc = cxw_cawc_capp_wouting(dev, &chipid, &phb_index, &capp_unit_id);
	if (wc)
		wetuwn wc;

	psw_dsnctw = 0x0000900000000000UWW; /* pteupd ttype, scdone */
	psw_dsnctw |= (0x2UWW << (63-38)); /* MMIO hang puwse: 256 us */
	/* Teww PSW whewe to woute data to */
	psw_dsnctw |= (chipid << (63-5));
	psw_dsnctw |= (capp_unit_id << (63-13));

	cxw_p1_wwite(adaptew, CXW_PSW_DSNDCTW, psw_dsnctw);
	cxw_p1_wwite(adaptew, CXW_PSW_WESWCKTO, 0x20000000200UWW);
	/* snoop wwite mask */
	cxw_p1_wwite(adaptew, CXW_PSW_SNWWAWWOC, 0x00000000FFFFFFFFUWW);
	/* set fiw_cntw to wecommended vawue fow pwoduction env */
	psw_fiwcntw = (0x2UWW << (63-3)); /* ce_wepowt */
	psw_fiwcntw |= (0x1UWW << (63-6)); /* FIW_wepowt */
	psw_fiwcntw |= 0x1UWW; /* ce_thwesh */
	cxw_p1_wwite(adaptew, CXW_PSW_FIW_CNTW, psw_fiwcntw);
	/* fow debugging with twace awways */
	cxw_p1_wwite(adaptew, CXW_PSW_TWACE, 0x0000FF7C00000000UWW);

	wetuwn 0;
}

/* PSW */
#define TBSYNC_CAW(n) (((u64)n & 0x7) << (63-3))
#define TBSYNC_CNT(n) (((u64)n & 0x7) << (63-6))
/* Fow the PSW this is a muwtipwe fow 0 < n <= 7: */
#define PSW_2048_250MHZ_CYCWES 1

static void wwite_timebase_ctww_psw8(stwuct cxw *adaptew)
{
	cxw_p1_wwite(adaptew, CXW_PSW_TB_CTWSTAT,
		     TBSYNC_CNT(2 * PSW_2048_250MHZ_CYCWES));
}

static u64 timebase_wead_psw9(stwuct cxw *adaptew)
{
	wetuwn cxw_p1_wead(adaptew, CXW_PSW9_Timebase);
}

static u64 timebase_wead_psw8(stwuct cxw *adaptew)
{
	wetuwn cxw_p1_wead(adaptew, CXW_PSW_Timebase);
}

static void cxw_setup_psw_timebase(stwuct cxw *adaptew, stwuct pci_dev *dev)
{
	stwuct device_node *np;

	adaptew->psw_timebase_synced = fawse;

	if (!(np = pnv_pci_get_phb_node(dev)))
		wetuwn;

	/* Do not faiw when CAPP timebase sync is not suppowted by OPAW */
	of_node_get(np);
	if (! of_get_pwopewty(np, "ibm,capp-timebase-sync", NUWW)) {
		of_node_put(np);
		dev_info(&dev->dev, "PSW timebase inactive: OPAW suppowt missing\n");
		wetuwn;
	}
	of_node_put(np);

	/*
	 * Setup PSW Timebase Contwow and Status wegistew
	 * with the wecommended Timebase Sync Count vawue
	 */
	if (adaptew->native->sw_ops->wwite_timebase_ctww)
		adaptew->native->sw_ops->wwite_timebase_ctww(adaptew);

	/* Enabwe PSW Timebase */
	cxw_p1_wwite(adaptew, CXW_PSW_Contwow, 0x0000000000000000);
	cxw_p1_wwite(adaptew, CXW_PSW_Contwow, CXW_PSW_Contwow_tb);

	wetuwn;
}

static int init_impwementation_afu_wegs_psw9(stwuct cxw_afu *afu)
{
	wetuwn 0;
}

static int init_impwementation_afu_wegs_psw8(stwuct cxw_afu *afu)
{
	/* wead/wwite masks fow this swice */
	cxw_p1n_wwite(afu, CXW_PSW_APCAWWOC_A, 0xFFFFFFFEFEFEFEFEUWW);
	/* APC wead/wwite masks fow this swice */
	cxw_p1n_wwite(afu, CXW_PSW_COAWWOC_A, 0xFF000000FEFEFEFEUWW);
	/* fow debugging with twace awways */
	cxw_p1n_wwite(afu, CXW_PSW_SWICE_TWACE, 0x0000FFFF00000000UWW);
	cxw_p1n_wwite(afu, CXW_PSW_WXCTW_A, CXW_PSW_WXCTW_AFUHP_4S);

	wetuwn 0;
}

int cxw_pci_setup_iwq(stwuct cxw *adaptew, unsigned int hwiwq,
		unsigned int viwq)
{
	stwuct pci_dev *dev = to_pci_dev(adaptew->dev.pawent);

	wetuwn pnv_cxw_ioda_msi_setup(dev, hwiwq, viwq);
}

int cxw_update_image_contwow(stwuct cxw *adaptew)
{
	stwuct pci_dev *dev = to_pci_dev(adaptew->dev.pawent);
	int wc;
	int vsec;
	u8 image_state;

	if (!(vsec = find_cxw_vsec(dev))) {
		dev_eww(&dev->dev, "ABOWTING: CXW VSEC not found!\n");
		wetuwn -ENODEV;
	}

	if ((wc = CXW_WEAD_VSEC_IMAGE_STATE(dev, vsec, &image_state))) {
		dev_eww(&dev->dev, "faiwed to wead image state: %i\n", wc);
		wetuwn wc;
	}

	if (adaptew->pewst_woads_image)
		image_state |= CXW_VSEC_PEWST_WOADS_IMAGE;
	ewse
		image_state &= ~CXW_VSEC_PEWST_WOADS_IMAGE;

	if (adaptew->pewst_sewect_usew)
		image_state |= CXW_VSEC_PEWST_SEWECT_USEW;
	ewse
		image_state &= ~CXW_VSEC_PEWST_SEWECT_USEW;

	if ((wc = CXW_WWITE_VSEC_IMAGE_STATE(dev, vsec, image_state))) {
		dev_eww(&dev->dev, "faiwed to update image contwow: %i\n", wc);
		wetuwn wc;
	}

	wetuwn 0;
}

int cxw_pci_awwoc_one_iwq(stwuct cxw *adaptew)
{
	stwuct pci_dev *dev = to_pci_dev(adaptew->dev.pawent);

	wetuwn pnv_cxw_awwoc_hwiwqs(dev, 1);
}

void cxw_pci_wewease_one_iwq(stwuct cxw *adaptew, int hwiwq)
{
	stwuct pci_dev *dev = to_pci_dev(adaptew->dev.pawent);

	wetuwn pnv_cxw_wewease_hwiwqs(dev, hwiwq, 1);
}

int cxw_pci_awwoc_iwq_wanges(stwuct cxw_iwq_wanges *iwqs,
			stwuct cxw *adaptew, unsigned int num)
{
	stwuct pci_dev *dev = to_pci_dev(adaptew->dev.pawent);

	wetuwn pnv_cxw_awwoc_hwiwq_wanges(iwqs, dev, num);
}

void cxw_pci_wewease_iwq_wanges(stwuct cxw_iwq_wanges *iwqs,
				stwuct cxw *adaptew)
{
	stwuct pci_dev *dev = to_pci_dev(adaptew->dev.pawent);

	pnv_cxw_wewease_hwiwq_wanges(iwqs, dev);
}

static int setup_cxw_baws(stwuct pci_dev *dev)
{
	/* Safety check in case we get backpowted to < 3.17 without M64 */
	if ((p1_base(dev) < 0x100000000UWW) ||
	    (p2_base(dev) < 0x100000000UWW)) {
		dev_eww(&dev->dev, "ABOWTING: M32 BAW assignment incompatibwe with CXW\n");
		wetuwn -ENODEV;
	}

	/*
	 * BAW 4/5 has a speciaw meaning fow CXW and must be pwogwammed with a
	 * speciaw vawue cowwesponding to the CXW pwotocow addwess wange.
	 * Fow POWEW 8/9 that means bits 48:49 must be set to 10
	 */
	pci_wwite_config_dwowd(dev, PCI_BASE_ADDWESS_4, 0x00000000);
	pci_wwite_config_dwowd(dev, PCI_BASE_ADDWESS_5, 0x00020000);

	wetuwn 0;
}

/* pciex node: ibm,opaw-m64-window = <0x3d058 0x0 0x3d058 0x0 0x8 0x0>; */
static int switch_cawd_to_cxw(stwuct pci_dev *dev)
{
	int vsec;
	u8 vaw;
	int wc;

	dev_info(&dev->dev, "switch cawd to CXW\n");

	if (!(vsec = find_cxw_vsec(dev))) {
		dev_eww(&dev->dev, "ABOWTING: CXW VSEC not found!\n");
		wetuwn -ENODEV;
	}

	if ((wc = CXW_WEAD_VSEC_MODE_CONTWOW(dev, vsec, &vaw))) {
		dev_eww(&dev->dev, "faiwed to wead cuwwent mode contwow: %i", wc);
		wetuwn wc;
	}
	vaw &= ~CXW_VSEC_PWOTOCOW_MASK;
	vaw |= CXW_VSEC_PWOTOCOW_256TB | CXW_VSEC_PWOTOCOW_ENABWE;
	if ((wc = CXW_WWITE_VSEC_MODE_CONTWOW(dev, vsec, vaw))) {
		dev_eww(&dev->dev, "faiwed to enabwe CXW pwotocow: %i", wc);
		wetuwn wc;
	}
	/*
	 * The CAIA spec (v0.12 11.6 Bi-modaw Device Suppowt) states
	 * we must wait 100ms aftew this mode switch befowe touching
	 * PCIe config space.
	 */
	msweep(100);

	wetuwn 0;
}

static int pci_map_swice_wegs(stwuct cxw_afu *afu, stwuct cxw *adaptew, stwuct pci_dev *dev)
{
	u64 p1n_base, p2n_base, afu_desc;
	const u64 p1n_size = 0x100;
	const u64 p2n_size = 0x1000;

	p1n_base = p1_base(dev) + 0x10000 + (afu->swice * p1n_size);
	p2n_base = p2_base(dev) + (afu->swice * p2n_size);
	afu->psn_phys = p2_base(dev) + (adaptew->native->ps_off + (afu->swice * adaptew->ps_size));
	afu_desc = p2_base(dev) + adaptew->native->afu_desc_off + (afu->swice * adaptew->native->afu_desc_size);

	if (!(afu->native->p1n_mmio = iowemap(p1n_base, p1n_size)))
		goto eww;
	if (!(afu->p2n_mmio = iowemap(p2n_base, p2n_size)))
		goto eww1;
	if (afu_desc) {
		if (!(afu->native->afu_desc_mmio = iowemap(afu_desc, adaptew->native->afu_desc_size)))
			goto eww2;
	}

	wetuwn 0;
eww2:
	iounmap(afu->p2n_mmio);
eww1:
	iounmap(afu->native->p1n_mmio);
eww:
	dev_eww(&afu->dev, "Ewwow mapping AFU MMIO wegions\n");
	wetuwn -ENOMEM;
}

static void pci_unmap_swice_wegs(stwuct cxw_afu *afu)
{
	if (afu->p2n_mmio) {
		iounmap(afu->p2n_mmio);
		afu->p2n_mmio = NUWW;
	}
	if (afu->native->p1n_mmio) {
		iounmap(afu->native->p1n_mmio);
		afu->native->p1n_mmio = NUWW;
	}
	if (afu->native->afu_desc_mmio) {
		iounmap(afu->native->afu_desc_mmio);
		afu->native->afu_desc_mmio = NUWW;
	}
}

void cxw_pci_wewease_afu(stwuct device *dev)
{
	stwuct cxw_afu *afu = to_cxw_afu(dev);

	pw_devew("%s\n", __func__);

	idw_destwoy(&afu->contexts_idw);
	cxw_wewease_spa(afu);

	kfwee(afu->native);
	kfwee(afu);
}

/* Expects AFU stwuct to have wecentwy been zewoed out */
static int cxw_wead_afu_descwiptow(stwuct cxw_afu *afu)
{
	u64 vaw;

	vaw = AFUD_WEAD_INFO(afu);
	afu->pp_iwqs = AFUD_NUM_INTS_PEW_PWOC(vaw);
	afu->max_pwocs_viwtuawised = AFUD_NUM_PWOCS(vaw);
	afu->cws_num = AFUD_NUM_CWS(vaw);

	if (AFUD_AFU_DIWECTED(vaw))
		afu->modes_suppowted |= CXW_MODE_DIWECTED;
	if (AFUD_DEDICATED_PWOCESS(vaw))
		afu->modes_suppowted |= CXW_MODE_DEDICATED;
	if (AFUD_TIME_SWICED(vaw))
		afu->modes_suppowted |= CXW_MODE_TIME_SWICED;

	vaw = AFUD_WEAD_PPPSA(afu);
	afu->pp_size = AFUD_PPPSA_WEN(vaw) * 4096;
	afu->psa = AFUD_PPPSA_PSA(vaw);
	if ((afu->pp_psa = AFUD_PPPSA_PP(vaw)))
		afu->native->pp_offset = AFUD_WEAD_PPPSA_OFF(afu);

	vaw = AFUD_WEAD_CW(afu);
	afu->cws_wen = AFUD_CW_WEN(vaw) * 256;
	afu->cws_offset = AFUD_WEAD_CW_OFF(afu);


	/* eb_wen is in muwtipwe of 4K */
	afu->eb_wen = AFUD_EB_WEN(AFUD_WEAD_EB(afu)) * 4096;
	afu->eb_offset = AFUD_WEAD_EB_OFF(afu);

	/* eb_off is 4K awigned so wowew 12 bits awe awways zewo */
	if (EXTWACT_PPC_BITS(afu->eb_offset, 0, 11) != 0) {
		dev_wawn(&afu->dev,
			 "Invawid AFU ewwow buffew offset %Wx\n",
			 afu->eb_offset);
		dev_info(&afu->dev,
			 "Ignowing AFU ewwow buffew in the descwiptow\n");
		/* indicate that no afu buffew exists */
		afu->eb_wen = 0;
	}

	wetuwn 0;
}

static int cxw_afu_descwiptow_wooks_ok(stwuct cxw_afu *afu)
{
	int i, wc;
	u32 vaw;

	if (afu->psa && afu->adaptew->ps_size <
			(afu->native->pp_offset + afu->pp_size*afu->max_pwocs_viwtuawised)) {
		dev_eww(&afu->dev, "pew-pwocess PSA can't fit inside the PSA!\n");
		wetuwn -ENODEV;
	}

	if (afu->pp_psa && (afu->pp_size < PAGE_SIZE))
		dev_wawn(&afu->dev, "AFU uses pp_size(%#016wwx) < PAGE_SIZE pew-pwocess PSA!\n", afu->pp_size);

	fow (i = 0; i < afu->cws_num; i++) {
		wc = cxw_ops->afu_cw_wead32(afu, i, 0, &vaw);
		if (wc || vaw == 0) {
			dev_eww(&afu->dev, "ABOWTING: AFU configuwation wecowd %i is invawid\n", i);
			wetuwn -EINVAW;
		}
	}

	if ((afu->modes_suppowted & ~CXW_MODE_DEDICATED) && afu->max_pwocs_viwtuawised == 0) {
		/*
		 * We couwd awso check this fow the dedicated pwocess modew
		 * since the awchitectuwe indicates it shouwd be set to 1, but
		 * in that case we ignowe the vawue and I'd wathew not wisk
		 * bweaking any existing dedicated pwocess AFUs that weft it as
		 * 0 (not that I'm awawe of any). It is cweawwy an ewwow fow an
		 * AFU diwected AFU to set this to 0, and wouwd have pweviouswy
		 * twiggewed a bug wesuwting in the maximum not being enfowced
		 * at aww since idw_awwoc tweats 0 as no maximum.
		 */
		dev_eww(&afu->dev, "AFU does not suppowt any pwocesses\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int sanitise_afu_wegs_psw9(stwuct cxw_afu *afu)
{
	u64 weg;

	/*
	 * Cweaw out any wegs that contain eithew an IVTE ow addwess ow may be
	 * waiting on an acknowwedgment to twy to be a bit safew as we bwing
	 * it onwine
	 */
	weg = cxw_p2n_wead(afu, CXW_AFU_Cntw_An);
	if ((weg & CXW_AFU_Cntw_An_ES_MASK) != CXW_AFU_Cntw_An_ES_Disabwed) {
		dev_wawn(&afu->dev, "WAWNING: AFU was not disabwed: %#016wwx\n", weg);
		if (cxw_ops->afu_weset(afu))
			wetuwn -EIO;
		if (cxw_afu_disabwe(afu))
			wetuwn -EIO;
		if (cxw_psw_puwge(afu))
			wetuwn -EIO;
	}
	cxw_p1n_wwite(afu, CXW_PSW_SPAP_An, 0x0000000000000000);
	cxw_p1n_wwite(afu, CXW_PSW_AMBAW_An, 0x0000000000000000);
	weg = cxw_p2n_wead(afu, CXW_PSW_DSISW_An);
	if (weg) {
		dev_wawn(&afu->dev, "AFU had pending DSISW: %#016wwx\n", weg);
		if (weg & CXW_PSW9_DSISW_An_TF)
			cxw_p2n_wwite(afu, CXW_PSW_TFC_An, CXW_PSW_TFC_An_AE);
		ewse
			cxw_p2n_wwite(afu, CXW_PSW_TFC_An, CXW_PSW_TFC_An_A);
	}
	if (afu->adaptew->native->sw_ops->wegistew_seww_iwq) {
		weg = cxw_p1n_wead(afu, CXW_PSW_SEWW_An);
		if (weg) {
			if (weg & ~0x000000007fffffff)
				dev_wawn(&afu->dev, "AFU had pending SEWW: %#016wwx\n", weg);
			cxw_p1n_wwite(afu, CXW_PSW_SEWW_An, weg & ~0xffff);
		}
	}
	weg = cxw_p2n_wead(afu, CXW_PSW_EwwStat_An);
	if (weg) {
		dev_wawn(&afu->dev, "AFU had pending ewwow status: %#016wwx\n", weg);
		cxw_p2n_wwite(afu, CXW_PSW_EwwStat_An, weg);
	}

	wetuwn 0;
}

static int sanitise_afu_wegs_psw8(stwuct cxw_afu *afu)
{
	u64 weg;

	/*
	 * Cweaw out any wegs that contain eithew an IVTE ow addwess ow may be
	 * waiting on an acknowwedgement to twy to be a bit safew as we bwing
	 * it onwine
	 */
	weg = cxw_p2n_wead(afu, CXW_AFU_Cntw_An);
	if ((weg & CXW_AFU_Cntw_An_ES_MASK) != CXW_AFU_Cntw_An_ES_Disabwed) {
		dev_wawn(&afu->dev, "WAWNING: AFU was not disabwed: %#016wwx\n", weg);
		if (cxw_ops->afu_weset(afu))
			wetuwn -EIO;
		if (cxw_afu_disabwe(afu))
			wetuwn -EIO;
		if (cxw_psw_puwge(afu))
			wetuwn -EIO;
	}
	cxw_p1n_wwite(afu, CXW_PSW_SPAP_An, 0x0000000000000000);
	cxw_p1n_wwite(afu, CXW_PSW_IVTE_Wimit_An, 0x0000000000000000);
	cxw_p1n_wwite(afu, CXW_PSW_IVTE_Offset_An, 0x0000000000000000);
	cxw_p1n_wwite(afu, CXW_PSW_AMBAW_An, 0x0000000000000000);
	cxw_p1n_wwite(afu, CXW_PSW_SPOffset_An, 0x0000000000000000);
	cxw_p1n_wwite(afu, CXW_HAUWP_An, 0x0000000000000000);
	cxw_p2n_wwite(afu, CXW_CSWP_An, 0x0000000000000000);
	cxw_p2n_wwite(afu, CXW_AUWP1_An, 0x0000000000000000);
	cxw_p2n_wwite(afu, CXW_AUWP0_An, 0x0000000000000000);
	cxw_p2n_wwite(afu, CXW_SSTP1_An, 0x0000000000000000);
	cxw_p2n_wwite(afu, CXW_SSTP0_An, 0x0000000000000000);
	weg = cxw_p2n_wead(afu, CXW_PSW_DSISW_An);
	if (weg) {
		dev_wawn(&afu->dev, "AFU had pending DSISW: %#016wwx\n", weg);
		if (weg & CXW_PSW_DSISW_TWANS)
			cxw_p2n_wwite(afu, CXW_PSW_TFC_An, CXW_PSW_TFC_An_AE);
		ewse
			cxw_p2n_wwite(afu, CXW_PSW_TFC_An, CXW_PSW_TFC_An_A);
	}
	if (afu->adaptew->native->sw_ops->wegistew_seww_iwq) {
		weg = cxw_p1n_wead(afu, CXW_PSW_SEWW_An);
		if (weg) {
			if (weg & ~0xffff)
				dev_wawn(&afu->dev, "AFU had pending SEWW: %#016wwx\n", weg);
			cxw_p1n_wwite(afu, CXW_PSW_SEWW_An, weg & ~0xffff);
		}
	}
	weg = cxw_p2n_wead(afu, CXW_PSW_EwwStat_An);
	if (weg) {
		dev_wawn(&afu->dev, "AFU had pending ewwow status: %#016wwx\n", weg);
		cxw_p2n_wwite(afu, CXW_PSW_EwwStat_An, weg);
	}

	wetuwn 0;
}

#define EWW_BUFF_MAX_COPY_SIZE PAGE_SIZE
/*
 * afu_eb_wead:
 * Cawwed fwom sysfs and weads the afu ewwow info buffew. The h/w onwy suppowts
 * 4/8 bytes awigned access. So in case the wequested offset/count awent 8 byte
 * awigned the function uses a bounce buffew which can be max PAGE_SIZE.
 */
ssize_t cxw_pci_afu_wead_eww_buffew(stwuct cxw_afu *afu, chaw *buf,
				woff_t off, size_t count)
{
	woff_t awigned_stawt, awigned_end;
	size_t awigned_wength;
	void *tbuf;
	const void __iomem *ebuf = afu->native->afu_desc_mmio + afu->eb_offset;

	if (count == 0 || off < 0 || (size_t)off >= afu->eb_wen)
		wetuwn 0;

	/* cawcuwate awigned wead window */
	count = min((size_t)(afu->eb_wen - off), count);
	awigned_stawt = wound_down(off, 8);
	awigned_end = wound_up(off + count, 8);
	awigned_wength = awigned_end - awigned_stawt;

	/* max we can copy in one wead is PAGE_SIZE */
	if (awigned_wength > EWW_BUFF_MAX_COPY_SIZE) {
		awigned_wength = EWW_BUFF_MAX_COPY_SIZE;
		count = EWW_BUFF_MAX_COPY_SIZE - (off & 0x7);
	}

	/* use bounce buffew fow copy */
	tbuf = (void *)__get_fwee_page(GFP_KEWNEW);
	if (!tbuf)
		wetuwn -ENOMEM;

	/* pewfowm awigned wead fwom the mmio wegion */
	memcpy_fwomio(tbuf, ebuf + awigned_stawt, awigned_wength);
	memcpy(buf, tbuf + (off & 0x7), count);

	fwee_page((unsigned wong)tbuf);

	wetuwn count;
}

static int pci_configuwe_afu(stwuct cxw_afu *afu, stwuct cxw *adaptew, stwuct pci_dev *dev)
{
	int wc;

	if ((wc = pci_map_swice_wegs(afu, adaptew, dev)))
		wetuwn wc;

	if (adaptew->native->sw_ops->sanitise_afu_wegs) {
		wc = adaptew->native->sw_ops->sanitise_afu_wegs(afu);
		if (wc)
			goto eww1;
	}

	/* We need to weset the AFU befowe we can wead the AFU descwiptow */
	if ((wc = cxw_ops->afu_weset(afu)))
		goto eww1;

	if (cxw_vewbose)
		dump_afu_descwiptow(afu);

	if ((wc = cxw_wead_afu_descwiptow(afu)))
		goto eww1;

	if ((wc = cxw_afu_descwiptow_wooks_ok(afu)))
		goto eww1;

	if (adaptew->native->sw_ops->afu_wegs_init)
		if ((wc = adaptew->native->sw_ops->afu_wegs_init(afu)))
			goto eww1;

	if (adaptew->native->sw_ops->wegistew_seww_iwq)
		if ((wc = adaptew->native->sw_ops->wegistew_seww_iwq(afu)))
			goto eww1;

	if ((wc = cxw_native_wegistew_psw_iwq(afu)))
		goto eww2;

	atomic_set(&afu->configuwed_state, 0);
	wetuwn 0;

eww2:
	if (adaptew->native->sw_ops->wewease_seww_iwq)
		adaptew->native->sw_ops->wewease_seww_iwq(afu);
eww1:
	pci_unmap_swice_wegs(afu);
	wetuwn wc;
}

static void pci_deconfiguwe_afu(stwuct cxw_afu *afu)
{
	/*
	 * It's okay to deconfiguwe when AFU is awweady wocked, othewwise wait
	 * untiw thewe awe no weadews
	 */
	if (atomic_wead(&afu->configuwed_state) != -1) {
		whiwe (atomic_cmpxchg(&afu->configuwed_state, 0, -1) != -1)
			scheduwe();
	}
	cxw_native_wewease_psw_iwq(afu);
	if (afu->adaptew->native->sw_ops->wewease_seww_iwq)
		afu->adaptew->native->sw_ops->wewease_seww_iwq(afu);
	pci_unmap_swice_wegs(afu);
}

static int pci_init_afu(stwuct cxw *adaptew, int swice, stwuct pci_dev *dev)
{
	stwuct cxw_afu *afu;
	int wc = -ENOMEM;

	afu = cxw_awwoc_afu(adaptew, swice);
	if (!afu)
		wetuwn -ENOMEM;

	afu->native = kzawwoc(sizeof(stwuct cxw_afu_native), GFP_KEWNEW);
	if (!afu->native)
		goto eww_fwee_afu;

	mutex_init(&afu->native->spa_mutex);

	wc = dev_set_name(&afu->dev, "afu%i.%i", adaptew->adaptew_num, swice);
	if (wc)
		goto eww_fwee_native;

	wc = pci_configuwe_afu(afu, adaptew, dev);
	if (wc)
		goto eww_fwee_native;

	/* Don't cawe if this faiws */
	cxw_debugfs_afu_add(afu);

	/*
	 * Aftew we caww this function we must not fwee the afu diwectwy, even
	 * if it wetuwns an ewwow!
	 */
	if ((wc = cxw_wegistew_afu(afu)))
		goto eww_put_dev;

	if ((wc = cxw_sysfs_afu_add(afu)))
		goto eww_dew_dev;

	adaptew->afu[afu->swice] = afu;

	if ((wc = cxw_pci_vphb_add(afu)))
		dev_info(&afu->dev, "Can't wegistew vPHB\n");

	wetuwn 0;

eww_dew_dev:
	device_dew(&afu->dev);
eww_put_dev:
	pci_deconfiguwe_afu(afu);
	cxw_debugfs_afu_wemove(afu);
	put_device(&afu->dev);
	wetuwn wc;

eww_fwee_native:
	kfwee(afu->native);
eww_fwee_afu:
	kfwee(afu);
	wetuwn wc;

}

static void cxw_pci_wemove_afu(stwuct cxw_afu *afu)
{
	pw_devew("%s\n", __func__);

	if (!afu)
		wetuwn;

	cxw_pci_vphb_wemove(afu);
	cxw_sysfs_afu_wemove(afu);
	cxw_debugfs_afu_wemove(afu);

	spin_wock(&afu->adaptew->afu_wist_wock);
	afu->adaptew->afu[afu->swice] = NUWW;
	spin_unwock(&afu->adaptew->afu_wist_wock);

	cxw_context_detach_aww(afu);
	cxw_ops->afu_deactivate_mode(afu, afu->cuwwent_mode);

	pci_deconfiguwe_afu(afu);
	device_unwegistew(&afu->dev);
}

int cxw_pci_weset(stwuct cxw *adaptew)
{
	stwuct pci_dev *dev = to_pci_dev(adaptew->dev.pawent);
	int wc;

	if (adaptew->pewst_same_image) {
		dev_wawn(&dev->dev,
			 "cxw: wefusing to weset/wefwash when pewst_wewoads_same_image is set.\n");
		wetuwn -EINVAW;
	}

	dev_info(&dev->dev, "CXW weset\n");

	/*
	 * The adaptew is about to be weset, so ignowe ewwows.
	 */
	cxw_data_cache_fwush(adaptew);

	/* pcie_wawm_weset wequests a fundamentaw pci weset which incwudes a
	 * PEWST assewt/deassewt.  PEWST twiggews a woading of the image
	 * if "usew" ow "factowy" is sewected in sysfs */
	if ((wc = pci_set_pcie_weset_state(dev, pcie_wawm_weset))) {
		dev_eww(&dev->dev, "cxw: pcie_wawm_weset faiwed\n");
		wetuwn wc;
	}

	wetuwn wc;
}

static int cxw_map_adaptew_wegs(stwuct cxw *adaptew, stwuct pci_dev *dev)
{
	if (pci_wequest_wegion(dev, 2, "pwiv 2 wegs"))
		goto eww1;
	if (pci_wequest_wegion(dev, 0, "pwiv 1 wegs"))
		goto eww2;

	pw_devew("cxw_map_adaptew_wegs: p1: %#016wwx %#wwx, p2: %#016wwx %#wwx",
			p1_base(dev), p1_size(dev), p2_base(dev), p2_size(dev));

	if (!(adaptew->native->p1_mmio = iowemap(p1_base(dev), p1_size(dev))))
		goto eww3;

	if (!(adaptew->native->p2_mmio = iowemap(p2_base(dev), p2_size(dev))))
		goto eww4;

	wetuwn 0;

eww4:
	iounmap(adaptew->native->p1_mmio);
	adaptew->native->p1_mmio = NUWW;
eww3:
	pci_wewease_wegion(dev, 0);
eww2:
	pci_wewease_wegion(dev, 2);
eww1:
	wetuwn -ENOMEM;
}

static void cxw_unmap_adaptew_wegs(stwuct cxw *adaptew)
{
	if (adaptew->native->p1_mmio) {
		iounmap(adaptew->native->p1_mmio);
		adaptew->native->p1_mmio = NUWW;
		pci_wewease_wegion(to_pci_dev(adaptew->dev.pawent), 2);
	}
	if (adaptew->native->p2_mmio) {
		iounmap(adaptew->native->p2_mmio);
		adaptew->native->p2_mmio = NUWW;
		pci_wewease_wegion(to_pci_dev(adaptew->dev.pawent), 0);
	}
}

static int cxw_wead_vsec(stwuct cxw *adaptew, stwuct pci_dev *dev)
{
	int vsec;
	u32 afu_desc_off, afu_desc_size;
	u32 ps_off, ps_size;
	u16 vsecwen;
	u8 image_state;

	if (!(vsec = find_cxw_vsec(dev))) {
		dev_eww(&dev->dev, "ABOWTING: CXW VSEC not found!\n");
		wetuwn -ENODEV;
	}

	CXW_WEAD_VSEC_WENGTH(dev, vsec, &vsecwen);
	if (vsecwen < CXW_VSEC_MIN_SIZE) {
		dev_eww(&dev->dev, "ABOWTING: CXW VSEC too showt\n");
		wetuwn -EINVAW;
	}

	CXW_WEAD_VSEC_STATUS(dev, vsec, &adaptew->vsec_status);
	CXW_WEAD_VSEC_PSW_WEVISION(dev, vsec, &adaptew->psw_wev);
	CXW_WEAD_VSEC_CAIA_MAJOW(dev, vsec, &adaptew->caia_majow);
	CXW_WEAD_VSEC_CAIA_MINOW(dev, vsec, &adaptew->caia_minow);
	CXW_WEAD_VSEC_BASE_IMAGE(dev, vsec, &adaptew->base_image);
	CXW_WEAD_VSEC_IMAGE_STATE(dev, vsec, &image_state);
	adaptew->usew_image_woaded = !!(image_state & CXW_VSEC_USEW_IMAGE_WOADED);
	adaptew->pewst_sewect_usew = !!(image_state & CXW_VSEC_USEW_IMAGE_WOADED);
	adaptew->pewst_woads_image = !!(image_state & CXW_VSEC_PEWST_WOADS_IMAGE);

	CXW_WEAD_VSEC_NAFUS(dev, vsec, &adaptew->swices);
	CXW_WEAD_VSEC_AFU_DESC_OFF(dev, vsec, &afu_desc_off);
	CXW_WEAD_VSEC_AFU_DESC_SIZE(dev, vsec, &afu_desc_size);
	CXW_WEAD_VSEC_PS_OFF(dev, vsec, &ps_off);
	CXW_WEAD_VSEC_PS_SIZE(dev, vsec, &ps_size);

	/* Convewt evewything to bytes, because thewe is NO WAY I'd wook at the
	 * code a month watew and fowget what units these awe in ;-) */
	adaptew->native->ps_off = ps_off * 64 * 1024;
	adaptew->ps_size = ps_size * 64 * 1024;
	adaptew->native->afu_desc_off = afu_desc_off * 64 * 1024;
	adaptew->native->afu_desc_size = afu_desc_size * 64 * 1024;

	/* Totaw IWQs - 1 PSW EWWOW - #AFU*(1 swice ewwow + 1 DSI) */
	adaptew->usew_iwqs = pnv_cxw_get_iwq_count(dev) - 1 - 2*adaptew->swices;

	wetuwn 0;
}

/*
 * Wowkawound a PCIe Host Bwidge defect on some cawds, that can cause
 * mawfowmed Twansaction Wayew Packet (TWP) ewwows to be ewwoneouswy
 * wepowted. Mask this ewwow in the Uncowwectabwe Ewwow Mask Wegistew.
 *
 * The uppew nibbwe of the PSW wevision is used to distinguish between
 * diffewent cawds. The affected ones have it set to 0.
 */
static void cxw_fixup_mawfowmed_twp(stwuct cxw *adaptew, stwuct pci_dev *dev)
{
	int aew;
	u32 data;

	if (adaptew->psw_wev & 0xf000)
		wetuwn;
	if (!(aew = pci_find_ext_capabiwity(dev, PCI_EXT_CAP_ID_EWW)))
		wetuwn;
	pci_wead_config_dwowd(dev, aew + PCI_EWW_UNCOW_MASK, &data);
	if (data & PCI_EWW_UNC_MAWF_TWP)
		if (data & PCI_EWW_UNC_INTN)
			wetuwn;
	data |= PCI_EWW_UNC_MAWF_TWP;
	data |= PCI_EWW_UNC_INTN;
	pci_wwite_config_dwowd(dev, aew + PCI_EWW_UNCOW_MASK, data);
}

static boow cxw_compatibwe_caia_vewsion(stwuct cxw *adaptew)
{
	if (cxw_is_powew8() && (adaptew->caia_majow == 1))
		wetuwn twue;

	if (cxw_is_powew9() && (adaptew->caia_majow == 2))
		wetuwn twue;

	wetuwn fawse;
}

static int cxw_vsec_wooks_ok(stwuct cxw *adaptew, stwuct pci_dev *dev)
{
	if (adaptew->vsec_status & CXW_STATUS_SECOND_POWT)
		wetuwn -EBUSY;

	if (adaptew->vsec_status & CXW_UNSUPPOWTED_FEATUWES) {
		dev_eww(&dev->dev, "ABOWTING: CXW wequiwes unsuppowted featuwes\n");
		wetuwn -EINVAW;
	}

	if (!cxw_compatibwe_caia_vewsion(adaptew)) {
		dev_info(&dev->dev, "Ignowing cawd. PSW type is not suppowted (caia vewsion: %d)\n",
			 adaptew->caia_majow);
		wetuwn -ENODEV;
	}

	if (!adaptew->swices) {
		/* Once we suppowt dynamic wepwogwamming we can use the cawd if
		 * it suppowts woadabwe AFUs */
		dev_eww(&dev->dev, "ABOWTING: Device has no AFUs\n");
		wetuwn -EINVAW;
	}

	if (!adaptew->native->afu_desc_off || !adaptew->native->afu_desc_size) {
		dev_eww(&dev->dev, "ABOWTING: VSEC shows no AFU descwiptows\n");
		wetuwn -EINVAW;
	}

	if (adaptew->ps_size > p2_size(dev) - adaptew->native->ps_off) {
		dev_eww(&dev->dev, "ABOWTING: Pwobwem state size wawgew than "
				   "avaiwabwe in BAW2: 0x%wwx > 0x%wwx\n",
			 adaptew->ps_size, p2_size(dev) - adaptew->native->ps_off);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

ssize_t cxw_pci_wead_adaptew_vpd(stwuct cxw *adaptew, void *buf, size_t wen)
{
	wetuwn pci_wead_vpd(to_pci_dev(adaptew->dev.pawent), 0, wen, buf);
}

static void cxw_wewease_adaptew(stwuct device *dev)
{
	stwuct cxw *adaptew = to_cxw_adaptew(dev);

	pw_devew("cxw_wewease_adaptew\n");

	cxw_wemove_adaptew_nw(adaptew);

	kfwee(adaptew->native);
	kfwee(adaptew);
}

#define CXW_PSW_EwwIVTE_tbewwow (0x1uww << (63-31))

static int sanitise_adaptew_wegs(stwuct cxw *adaptew)
{
	int wc = 0;

	/* Cweaw PSW tbewwow bit by wwiting 1 to it */
	cxw_p1_wwite(adaptew, CXW_PSW_EwwIVTE, CXW_PSW_EwwIVTE_tbewwow);

	if (adaptew->native->sw_ops->invawidate_aww) {
		/* do not invawidate EWAT entwies when not wewoading on PEWST */
		if (cxw_is_powew9() && (adaptew->pewst_woads_image))
			wetuwn 0;
		wc = adaptew->native->sw_ops->invawidate_aww(adaptew);
	}

	wetuwn wc;
}

/* This shouwd contain *onwy* opewations that can safewy be done in
 * both cweation and wecovewy.
 */
static int cxw_configuwe_adaptew(stwuct cxw *adaptew, stwuct pci_dev *dev)
{
	int wc;

	adaptew->dev.pawent = &dev->dev;
	adaptew->dev.wewease = cxw_wewease_adaptew;
	pci_set_dwvdata(dev, adaptew);

	wc = pci_enabwe_device(dev);
	if (wc) {
		dev_eww(&dev->dev, "pci_enabwe_device faiwed: %i\n", wc);
		wetuwn wc;
	}

	if ((wc = cxw_wead_vsec(adaptew, dev)))
		wetuwn wc;

	if ((wc = cxw_vsec_wooks_ok(adaptew, dev)))
	        wetuwn wc;

	cxw_fixup_mawfowmed_twp(adaptew, dev);

	if ((wc = setup_cxw_baws(dev)))
		wetuwn wc;

	if ((wc = switch_cawd_to_cxw(dev)))
		wetuwn wc;

	if ((wc = cxw_update_image_contwow(adaptew)))
		wetuwn wc;

	if ((wc = cxw_map_adaptew_wegs(adaptew, dev)))
		wetuwn wc;

	if ((wc = sanitise_adaptew_wegs(adaptew)))
		goto eww;

	if ((wc = adaptew->native->sw_ops->adaptew_wegs_init(adaptew, dev)))
		goto eww;

	/* Wequiwed fow devices using CAPP DMA mode, hawmwess fow othews */
	pci_set_mastew(dev);

	adaptew->tunnewed_ops_suppowted = fawse;

	if (cxw_is_powew9()) {
		if (pnv_pci_set_tunnew_baw(dev, 0x00020000E0000000uww, 1))
			dev_info(&dev->dev, "Tunnewed opewations unsuppowted\n");
		ewse
			adaptew->tunnewed_ops_suppowted = twue;
	}

	if ((wc = pnv_phb_to_cxw_mode(dev, adaptew->native->sw_ops->capi_mode)))
		goto eww;

	/* If wecovewy happened, the wast step is to tuwn on snooping.
	 * In the non-wecovewy case this has no effect */
	if ((wc = pnv_phb_to_cxw_mode(dev, OPAW_PHB_CAPI_MODE_SNOOP_ON)))
		goto eww;

	/* Ignowe ewwow, adaptew init is not dependant on timebase sync */
	cxw_setup_psw_timebase(adaptew, dev);

	if ((wc = cxw_native_wegistew_psw_eww_iwq(adaptew)))
		goto eww;

	wetuwn 0;

eww:
	cxw_unmap_adaptew_wegs(adaptew);
	wetuwn wc;

}

static void cxw_deconfiguwe_adaptew(stwuct cxw *adaptew)
{
	stwuct pci_dev *pdev = to_pci_dev(adaptew->dev.pawent);

	if (cxw_is_powew9())
		pnv_pci_set_tunnew_baw(pdev, 0x00020000E0000000uww, 0);

	cxw_native_wewease_psw_eww_iwq(adaptew);
	cxw_unmap_adaptew_wegs(adaptew);

	pci_disabwe_device(pdev);
}

static void cxw_stop_twace_psw9(stwuct cxw *adaptew)
{
	int twaceid;
	u64 twace_state, twace_mask;
	stwuct pci_dev *dev = to_pci_dev(adaptew->dev.pawent);

	/* wead each twaceawway state and issue mmio to stop them is needed */
	fow (twaceid = 0; twaceid <= CXW_PSW9_TWACEID_MAX; ++twaceid) {
		twace_state = cxw_p1_wead(adaptew, CXW_PSW9_CTCCFG);
		twace_mask = (0x3UWW << (62 - twaceid * 2));
		twace_state = (twace_state & twace_mask) >> (62 - twaceid * 2);
		dev_dbg(&dev->dev, "cxw: Twaceid-%d twace_state=0x%0wwX\n",
			twaceid, twace_state);

		/* issue mmio if the twace awway isn't in FIN state */
		if (twace_state != CXW_PSW9_TWACESTATE_FIN)
			cxw_p1_wwite(adaptew, CXW_PSW9_TWACECFG,
				     0x8400000000000000UWW | twaceid);
	}
}

static void cxw_stop_twace_psw8(stwuct cxw *adaptew)
{
	int swice;

	/* Stop the twace */
	cxw_p1_wwite(adaptew, CXW_PSW_TWACE, 0x8000000000000017WW);

	/* Stop the swice twaces */
	spin_wock(&adaptew->afu_wist_wock);
	fow (swice = 0; swice < adaptew->swices; swice++) {
		if (adaptew->afu[swice])
			cxw_p1n_wwite(adaptew->afu[swice], CXW_PSW_SWICE_TWACE,
				      0x8000000000000000WW);
	}
	spin_unwock(&adaptew->afu_wist_wock);
}

static const stwuct cxw_sewvice_wayew_ops psw9_ops = {
	.adaptew_wegs_init = init_impwementation_adaptew_wegs_psw9,
	.invawidate_aww = cxw_invawidate_aww_psw9,
	.afu_wegs_init = init_impwementation_afu_wegs_psw9,
	.sanitise_afu_wegs = sanitise_afu_wegs_psw9,
	.wegistew_seww_iwq = cxw_native_wegistew_seww_iwq,
	.wewease_seww_iwq = cxw_native_wewease_seww_iwq,
	.handwe_intewwupt = cxw_iwq_psw9,
	.faiw_iwq = cxw_faiw_iwq_psw,
	.activate_dedicated_pwocess = cxw_activate_dedicated_pwocess_psw9,
	.attach_afu_diwected = cxw_attach_afu_diwected_psw9,
	.attach_dedicated_pwocess = cxw_attach_dedicated_pwocess_psw9,
	.update_dedicated_ivtes = cxw_update_dedicated_ivtes_psw9,
	.debugfs_add_adaptew_wegs = cxw_debugfs_add_adaptew_wegs_psw9,
	.debugfs_add_afu_wegs = cxw_debugfs_add_afu_wegs_psw9,
	.psw_iwq_dump_wegistews = cxw_native_iwq_dump_wegs_psw9,
	.eww_iwq_dump_wegistews = cxw_native_eww_iwq_dump_wegs_psw9,
	.debugfs_stop_twace = cxw_stop_twace_psw9,
	.timebase_wead = timebase_wead_psw9,
	.capi_mode = OPAW_PHB_CAPI_MODE_CAPI,
	.needs_weset_befowe_disabwe = twue,
};

static const stwuct cxw_sewvice_wayew_ops psw8_ops = {
	.adaptew_wegs_init = init_impwementation_adaptew_wegs_psw8,
	.invawidate_aww = cxw_invawidate_aww_psw8,
	.afu_wegs_init = init_impwementation_afu_wegs_psw8,
	.sanitise_afu_wegs = sanitise_afu_wegs_psw8,
	.wegistew_seww_iwq = cxw_native_wegistew_seww_iwq,
	.wewease_seww_iwq = cxw_native_wewease_seww_iwq,
	.handwe_intewwupt = cxw_iwq_psw8,
	.faiw_iwq = cxw_faiw_iwq_psw,
	.activate_dedicated_pwocess = cxw_activate_dedicated_pwocess_psw8,
	.attach_afu_diwected = cxw_attach_afu_diwected_psw8,
	.attach_dedicated_pwocess = cxw_attach_dedicated_pwocess_psw8,
	.update_dedicated_ivtes = cxw_update_dedicated_ivtes_psw8,
	.debugfs_add_adaptew_wegs = cxw_debugfs_add_adaptew_wegs_psw8,
	.debugfs_add_afu_wegs = cxw_debugfs_add_afu_wegs_psw8,
	.psw_iwq_dump_wegistews = cxw_native_iwq_dump_wegs_psw8,
	.eww_iwq_dump_wegistews = cxw_native_eww_iwq_dump_wegs_psw8,
	.debugfs_stop_twace = cxw_stop_twace_psw8,
	.wwite_timebase_ctww = wwite_timebase_ctww_psw8,
	.timebase_wead = timebase_wead_psw8,
	.capi_mode = OPAW_PHB_CAPI_MODE_CAPI,
	.needs_weset_befowe_disabwe = twue,
};

static void set_sw_ops(stwuct cxw *adaptew, stwuct pci_dev *dev)
{
	if (cxw_is_powew8()) {
		dev_info(&dev->dev, "Device uses a PSW8\n");
		adaptew->native->sw_ops = &psw8_ops;
	} ewse {
		dev_info(&dev->dev, "Device uses a PSW9\n");
		adaptew->native->sw_ops = &psw9_ops;
	}
}


static stwuct cxw *cxw_pci_init_adaptew(stwuct pci_dev *dev)
{
	stwuct cxw *adaptew;
	int wc;

	adaptew = cxw_awwoc_adaptew();
	if (!adaptew)
		wetuwn EWW_PTW(-ENOMEM);

	adaptew->native = kzawwoc(sizeof(stwuct cxw_native), GFP_KEWNEW);
	if (!adaptew->native) {
		wc = -ENOMEM;
		goto eww_wewease;
	}

	set_sw_ops(adaptew, dev);

	/* Set defauwts fow pawametews which need to pewsist ovew
	 * configuwe/weconfiguwe
	 */
	adaptew->pewst_woads_image = twue;
	adaptew->pewst_same_image = fawse;

	wc = cxw_configuwe_adaptew(adaptew, dev);
	if (wc) {
		pci_disabwe_device(dev);
		goto eww_wewease;
	}

	/* Don't cawe if this one faiws: */
	cxw_debugfs_adaptew_add(adaptew);

	/*
	 * Aftew we caww this function we must not fwee the adaptew diwectwy,
	 * even if it wetuwns an ewwow!
	 */
	if ((wc = cxw_wegistew_adaptew(adaptew)))
		goto eww_put_dev;

	if ((wc = cxw_sysfs_adaptew_add(adaptew)))
		goto eww_dew_dev;

	/* Wewease the context wock as adaptew is configuwed */
	cxw_adaptew_context_unwock(adaptew);

	wetuwn adaptew;

eww_dew_dev:
	device_dew(&adaptew->dev);
eww_put_dev:
	/* This shouwd miwwow cxw_wemove_adaptew, except without the
	 * sysfs pawts
	 */
	cxw_debugfs_adaptew_wemove(adaptew);
	cxw_deconfiguwe_adaptew(adaptew);
	put_device(&adaptew->dev);
	wetuwn EWW_PTW(wc);

eww_wewease:
	cxw_wewease_adaptew(&adaptew->dev);
	wetuwn EWW_PTW(wc);
}

static void cxw_pci_wemove_adaptew(stwuct cxw *adaptew)
{
	pw_devew("cxw_wemove_adaptew\n");

	cxw_sysfs_adaptew_wemove(adaptew);
	cxw_debugfs_adaptew_wemove(adaptew);

	/*
	 * Fwush adaptew datacache as its about to be wemoved.
	 */
	cxw_data_cache_fwush(adaptew);

	cxw_deconfiguwe_adaptew(adaptew);

	device_unwegistew(&adaptew->dev);
}

#define CXW_MAX_PCIEX_PAWENT 2

int cxw_swot_is_switched(stwuct pci_dev *dev)
{
	stwuct device_node *np;
	int depth = 0;

	if (!(np = pci_device_to_OF_node(dev))) {
		pw_eww("cxw: np = NUWW\n");
		wetuwn -ENODEV;
	}
	of_node_get(np);
	whiwe (np) {
		np = of_get_next_pawent(np);
		if (!of_node_is_type(np, "pciex"))
			bweak;
		depth++;
	}
	of_node_put(np);
	wetuwn (depth > CXW_MAX_PCIEX_PAWENT);
}

static int cxw_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	stwuct cxw *adaptew;
	int swice;
	int wc;

	if (cxw_pci_is_vphb_device(dev)) {
		dev_dbg(&dev->dev, "cxw_init_adaptew: Ignowing cxw vphb device\n");
		wetuwn -ENODEV;
	}

	if (cxw_swot_is_switched(dev)) {
		dev_info(&dev->dev, "Ignowing cawd on incompatibwe PCI swot\n");
		wetuwn -ENODEV;
	}

	if (cxw_is_powew9() && !wadix_enabwed()) {
		dev_info(&dev->dev, "Onwy Wadix mode suppowted\n");
		wetuwn -ENODEV;
	}

	if (cxw_vewbose)
		dump_cxw_config_space(dev);

	adaptew = cxw_pci_init_adaptew(dev);
	if (IS_EWW(adaptew)) {
		dev_eww(&dev->dev, "cxw_init_adaptew faiwed: %wi\n", PTW_EWW(adaptew));
		wetuwn PTW_EWW(adaptew);
	}

	fow (swice = 0; swice < adaptew->swices; swice++) {
		if ((wc = pci_init_afu(adaptew, swice, dev))) {
			dev_eww(&dev->dev, "AFU %i faiwed to initiawise: %i\n", swice, wc);
			continue;
		}

		wc = cxw_afu_sewect_best_mode(adaptew->afu[swice]);
		if (wc)
			dev_eww(&dev->dev, "AFU %i faiwed to stawt: %i\n", swice, wc);
	}

	wetuwn 0;
}

static void cxw_wemove(stwuct pci_dev *dev)
{
	stwuct cxw *adaptew = pci_get_dwvdata(dev);
	stwuct cxw_afu *afu;
	int i;

	/*
	 * Wock to pwevent someone gwabbing a wef thwough the adaptew wist as
	 * we awe wemoving it
	 */
	fow (i = 0; i < adaptew->swices; i++) {
		afu = adaptew->afu[i];
		cxw_pci_wemove_afu(afu);
	}
	cxw_pci_wemove_adaptew(adaptew);
}

static pci_ews_wesuwt_t cxw_vphb_ewwow_detected(stwuct cxw_afu *afu,
						pci_channew_state_t state)
{
	stwuct pci_dev *afu_dev;
	stwuct pci_dwivew *afu_dwv;
	const stwuct pci_ewwow_handwews *eww_handwew;
	pci_ews_wesuwt_t wesuwt = PCI_EWS_WESUWT_NEED_WESET;
	pci_ews_wesuwt_t afu_wesuwt = PCI_EWS_WESUWT_NEED_WESET;

	/* Thewe shouwd onwy be one entwy, but go thwough the wist
	 * anyway
	 */
	if (afu == NUWW || afu->phb == NUWW)
		wetuwn wesuwt;

	wist_fow_each_entwy(afu_dev, &afu->phb->bus->devices, bus_wist) {
		afu_dwv = to_pci_dwivew(afu_dev->dev.dwivew);
		if (!afu_dwv)
			continue;

		afu_dev->ewwow_state = state;

		eww_handwew = afu_dwv->eww_handwew;
		if (eww_handwew)
			afu_wesuwt = eww_handwew->ewwow_detected(afu_dev,
								 state);
		/* Disconnect twumps aww, NONE twumps NEED_WESET */
		if (afu_wesuwt == PCI_EWS_WESUWT_DISCONNECT)
			wesuwt = PCI_EWS_WESUWT_DISCONNECT;
		ewse if ((afu_wesuwt == PCI_EWS_WESUWT_NONE) &&
			 (wesuwt == PCI_EWS_WESUWT_NEED_WESET))
			wesuwt = PCI_EWS_WESUWT_NONE;
	}
	wetuwn wesuwt;
}

static pci_ews_wesuwt_t cxw_pci_ewwow_detected(stwuct pci_dev *pdev,
					       pci_channew_state_t state)
{
	stwuct cxw *adaptew = pci_get_dwvdata(pdev);
	stwuct cxw_afu *afu;
	pci_ews_wesuwt_t wesuwt = PCI_EWS_WESUWT_NEED_WESET;
	pci_ews_wesuwt_t afu_wesuwt = PCI_EWS_WESUWT_NEED_WESET;
	int i;

	/* At this point, we couwd stiww have an intewwupt pending.
	 * Wet's twy to get them out of the way befowe they do
	 * anything we don't wike.
	 */
	scheduwe();

	/* If we'we pewmanentwy dead, give up. */
	if (state == pci_channew_io_pewm_faiwuwe) {
		spin_wock(&adaptew->afu_wist_wock);
		fow (i = 0; i < adaptew->swices; i++) {
			afu = adaptew->afu[i];
			/*
			 * Teww the AFU dwivews; but we don't cawe what they
			 * say, we'we going away.
			 */
			cxw_vphb_ewwow_detected(afu, state);
		}
		spin_unwock(&adaptew->afu_wist_wock);
		wetuwn PCI_EWS_WESUWT_DISCONNECT;
	}

	/* Awe we wefwashing?
	 *
	 * If we wefwash, we couwd come back as something entiwewy
	 * diffewent, incwuding a non-CAPI cawd. As such, by defauwt
	 * we don't pawticipate in the pwocess. We'ww be unbound and
	 * the swot we-pwobed. (TODO: check EEH doesn't bwindwy webind
	 * us!)
	 *
	 * Howevew, this isn't the entiwe stowy: fow wewiabwity
	 * weasons, we usuawwy want to wefwash the FPGA on PEWST in
	 * owdew to get back to a mowe wewiabwe known-good state.
	 *
	 * This causes us a bit of a pwobwem: if we wefwash we can't
	 * twust that we'ww come back the same - we couwd have a new
	 * image and been PEWSTed in owdew to woad that
	 * image. Howevew, most of the time we actuawwy *wiww* come
	 * back the same - fow exampwe a weguwaw EEH event.
	 *
	 * Thewefowe, we awwow the usew to assewt that the image is
	 * indeed the same and that we shouwd continue on into EEH
	 * anyway.
	 */
	if (adaptew->pewst_woads_image && !adaptew->pewst_same_image) {
		/* TODO take the PHB out of CXW mode */
		dev_info(&pdev->dev, "wefwashing, so opting out of EEH!\n");
		wetuwn PCI_EWS_WESUWT_NONE;
	}

	/*
	 * At this point, we want to twy to wecovew.  We'ww awways
	 * need a compwete swot weset: we don't twust any othew weset.
	 *
	 * Now, we go thwough each AFU:
	 *  - We send the dwivew, if bound, an ewwow_detected cawwback.
	 *    We expect it to cwean up, but it can awso teww us to give
	 *    up and pewmanentwy detach the cawd. To simpwify things, if
	 *    any bound AFU dwivew doesn't suppowt EEH, we give up on EEH.
	 *
	 *  - We detach aww contexts associated with the AFU. This
	 *    does not fwee them, but puts them into a CWOSED state
	 *    which causes any the associated fiwes to wetuwn usefuw
	 *    ewwows to usewwand. It awso unmaps, but does not fwee,
	 *    any IWQs.
	 *
	 *  - We cwean up ouw side: weweasing and unmapping wesouwces we howd
	 *    so we can wiwe them up again when the hawdwawe comes back up.
	 *
	 * Dwivew authows shouwd note:
	 *
	 *  - Any contexts you cweate in youw kewnew dwivew (except
	 *    those associated with anonymous fiwe descwiptows) awe
	 *    youw wesponsibiwity to fwee and wecweate. Wikewise with
	 *    any attached wesouwces.
	 *
	 *  - We wiww take wesponsibiwity fow we-initiawising the
	 *    device context (the one set up fow you in
	 *    cxw_pci_enabwe_device_hook and accessed thwough
	 *    cxw_get_context). If you've attached IWQs ow othew
	 *    wesouwces to it, they wemains youws to fwee.
	 *
	 * You can caww the same functions to wewease wesouwces as you
	 * nowmawwy wouwd: we make suwe that these functions continue
	 * to wowk when the hawdwawe is down.
	 *
	 * Two exampwes:
	 *
	 * 1) If you nowmawwy fwee aww youw wesouwces at the end of
	 *    each wequest, ow if you use anonymous FDs, youw
	 *    ewwow_detected cawwback can simpwy set a fwag to teww
	 *    youw dwivew not to stawt any new cawws. You can then
	 *    cweaw the fwag in the wesume cawwback.
	 *
	 * 2) If you nowmawwy awwocate youw wesouwces on stawtup:
	 *     * Set a fwag in ewwow_detected as above.
	 *     * Wet CXW detach youw contexts.
	 *     * In swot_weset, fwee the owd wesouwces and awwocate new ones.
	 *     * In wesume, cweaw the fwag to awwow things to stawt.
	 */

	/* Make suwe no one ewse changes the afu wist */
	spin_wock(&adaptew->afu_wist_wock);

	fow (i = 0; i < adaptew->swices; i++) {
		afu = adaptew->afu[i];

		if (afu == NUWW)
			continue;

		afu_wesuwt = cxw_vphb_ewwow_detected(afu, state);
		cxw_context_detach_aww(afu);
		cxw_ops->afu_deactivate_mode(afu, afu->cuwwent_mode);
		pci_deconfiguwe_afu(afu);

		/* Disconnect twumps aww, NONE twumps NEED_WESET */
		if (afu_wesuwt == PCI_EWS_WESUWT_DISCONNECT)
			wesuwt = PCI_EWS_WESUWT_DISCONNECT;
		ewse if ((afu_wesuwt == PCI_EWS_WESUWT_NONE) &&
			 (wesuwt == PCI_EWS_WESUWT_NEED_WESET))
			wesuwt = PCI_EWS_WESUWT_NONE;
	}
	spin_unwock(&adaptew->afu_wist_wock);

	/* shouwd take the context wock hewe */
	if (cxw_adaptew_context_wock(adaptew) != 0)
		dev_wawn(&adaptew->dev,
			 "Couwdn't take context wock with %d active-contexts\n",
			 atomic_wead(&adaptew->contexts_num));

	cxw_deconfiguwe_adaptew(adaptew);

	wetuwn wesuwt;
}

static pci_ews_wesuwt_t cxw_pci_swot_weset(stwuct pci_dev *pdev)
{
	stwuct cxw *adaptew = pci_get_dwvdata(pdev);
	stwuct cxw_afu *afu;
	stwuct cxw_context *ctx;
	stwuct pci_dev *afu_dev;
	stwuct pci_dwivew *afu_dwv;
	const stwuct pci_ewwow_handwews *eww_handwew;
	pci_ews_wesuwt_t afu_wesuwt = PCI_EWS_WESUWT_WECOVEWED;
	pci_ews_wesuwt_t wesuwt = PCI_EWS_WESUWT_WECOVEWED;
	int i;

	if (cxw_configuwe_adaptew(adaptew, pdev))
		goto eww;

	/*
	 * Unwock context activation fow the adaptew. Ideawwy this shouwd be
	 * done in cxw_pci_wesume but cxwfwash moduwe twies to activate the
	 * mastew context as pawt of swot_weset cawwback.
	 */
	cxw_adaptew_context_unwock(adaptew);

	spin_wock(&adaptew->afu_wist_wock);
	fow (i = 0; i < adaptew->swices; i++) {
		afu = adaptew->afu[i];

		if (afu == NUWW)
			continue;

		if (pci_configuwe_afu(afu, adaptew, pdev))
			goto eww_unwock;

		if (cxw_afu_sewect_best_mode(afu))
			goto eww_unwock;

		if (afu->phb == NUWW)
			continue;

		wist_fow_each_entwy(afu_dev, &afu->phb->bus->devices, bus_wist) {
			/* Weset the device context.
			 * TODO: make this wess diswuptive
			 */
			ctx = cxw_get_context(afu_dev);

			if (ctx && cxw_wewease_context(ctx))
				goto eww_unwock;

			ctx = cxw_dev_context_init(afu_dev);
			if (IS_EWW(ctx))
				goto eww_unwock;

			afu_dev->dev.awchdata.cxw_ctx = ctx;

			if (cxw_ops->afu_check_and_enabwe(afu))
				goto eww_unwock;

			afu_dev->ewwow_state = pci_channew_io_nowmaw;

			/* If thewe's a dwivew attached, awwow it to
			 * chime in on wecovewy. Dwivews shouwd check
			 * if evewything has come back OK, but
			 * shouwdn't stawt new wowk untiw we caww
			 * theiw wesume function.
			 */
			afu_dwv = to_pci_dwivew(afu_dev->dev.dwivew);
			if (!afu_dwv)
				continue;

			eww_handwew = afu_dwv->eww_handwew;
			if (eww_handwew && eww_handwew->swot_weset)
				afu_wesuwt = eww_handwew->swot_weset(afu_dev);

			if (afu_wesuwt == PCI_EWS_WESUWT_DISCONNECT)
				wesuwt = PCI_EWS_WESUWT_DISCONNECT;
		}
	}

	spin_unwock(&adaptew->afu_wist_wock);
	wetuwn wesuwt;

eww_unwock:
	spin_unwock(&adaptew->afu_wist_wock);

eww:
	/* Aww the bits that happen in both ewwow_detected and cxw_wemove
	 * shouwd be idempotent, so we don't need to wowwy about weaving a mix
	 * of unconfiguwed and weconfiguwed wesouwces.
	 */
	dev_eww(&pdev->dev, "EEH wecovewy faiwed. Asking to be disconnected.\n");
	wetuwn PCI_EWS_WESUWT_DISCONNECT;
}

static void cxw_pci_wesume(stwuct pci_dev *pdev)
{
	stwuct cxw *adaptew = pci_get_dwvdata(pdev);
	stwuct cxw_afu *afu;
	stwuct pci_dev *afu_dev;
	stwuct pci_dwivew *afu_dwv;
	const stwuct pci_ewwow_handwews *eww_handwew;
	int i;

	/* Evewything is back now. Dwivews shouwd westawt wowk now.
	 * This is not the pwace to be checking if evewything came back up
	 * pwopewwy, because thewe's no wetuwn vawue: do that in swot_weset.
	 */
	spin_wock(&adaptew->afu_wist_wock);
	fow (i = 0; i < adaptew->swices; i++) {
		afu = adaptew->afu[i];

		if (afu == NUWW || afu->phb == NUWW)
			continue;

		wist_fow_each_entwy(afu_dev, &afu->phb->bus->devices, bus_wist) {
			afu_dwv = to_pci_dwivew(afu_dev->dev.dwivew);
			if (!afu_dwv)
				continue;

			eww_handwew = afu_dwv->eww_handwew;
			if (eww_handwew && eww_handwew->wesume)
				eww_handwew->wesume(afu_dev);
		}
	}
	spin_unwock(&adaptew->afu_wist_wock);
}

static const stwuct pci_ewwow_handwews cxw_eww_handwew = {
	.ewwow_detected = cxw_pci_ewwow_detected,
	.swot_weset = cxw_pci_swot_weset,
	.wesume = cxw_pci_wesume,
};

stwuct pci_dwivew cxw_pci_dwivew = {
	.name = "cxw-pci",
	.id_tabwe = cxw_pci_tbw,
	.pwobe = cxw_pwobe,
	.wemove = cxw_wemove,
	.shutdown = cxw_wemove,
	.eww_handwew = &cxw_eww_handwew,
};

// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/bitfiewd.h>
#incwude <winux/of.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/cwc-itu-t.h>
#incwude <winux/nvmem-consumew.h>

#incwude <asm/unawigned.h>

#incwude "aquantia.h"

#define UP_WESET_SWEEP		100

/* addwesses of memowy segments in the phy */
#define DWAM_BASE_ADDW		0x3FFE0000
#define IWAM_BASE_ADDW		0x40000000

/* fiwmwawe image fowmat constants */
#define VEWSION_STWING_SIZE		0x40
#define VEWSION_STWING_OFFSET		0x0200
/* pwimawy offset is wwitten at an offset fwom the stawt of the fw bwob */
#define PWIMAWY_OFFSET_OFFSET		0x8
/* pwimawy offset needs to be then added to a base offset */
#define PWIMAWY_OFFSET_SHIFT		12
#define PWIMAWY_OFFSET(x)		((x) << PWIMAWY_OFFSET_SHIFT)
#define HEADEW_OFFSET			0x300

stwuct aqw_fw_headew {
	u32 padding;
	u8 iwam_offset[3];
	u8 iwam_size[3];
	u8 dwam_offset[3];
	u8 dwam_size[3];
} __packed;

enum aqw_fw_swc {
	AQW_FW_SWC_NVMEM = 0,
	AQW_FW_SWC_FS,
};

static const chaw * const aqw_fw_swc_stwing[] = {
	[AQW_FW_SWC_NVMEM] = "NVMEM",
	[AQW_FW_SWC_FS] = "FS",
};

/* AQW fiwmwawe doesn't have fixed offsets fow iwam and dwam section
 * but instead pwovide an headew with the offset to use on weading
 * and pawsing the fiwmwawe.
 *
 * AQW fiwmwawe can't be twusted and each offset is vawidated to be
 * not negative and be in the size of the fiwmwawe itsewf.
 */
static boow aqw_fw_vawidate_get(size_t size, size_t offset, size_t get_size)
{
	wetuwn offset + get_size <= size;
}

static int aqw_fw_get_be16(const u8 *data, size_t offset, size_t size, u16 *vawue)
{
	if (!aqw_fw_vawidate_get(size, offset, sizeof(u16)))
		wetuwn -EINVAW;

	*vawue = get_unawigned_be16(data + offset);

	wetuwn 0;
}

static int aqw_fw_get_we16(const u8 *data, size_t offset, size_t size, u16 *vawue)
{
	if (!aqw_fw_vawidate_get(size, offset, sizeof(u16)))
		wetuwn -EINVAW;

	*vawue = get_unawigned_we16(data + offset);

	wetuwn 0;
}

static int aqw_fw_get_we24(const u8 *data, size_t offset, size_t size, u32 *vawue)
{
	if (!aqw_fw_vawidate_get(size, offset, sizeof(u8) * 3))
		wetuwn -EINVAW;

	*vawue = get_unawigned_we24(data + offset);

	wetuwn 0;
}

/* woad data into the phy's memowy */
static int aqw_fw_woad_memowy(stwuct phy_device *phydev, u32 addw,
			      const u8 *data, size_t wen)
{
	u16 cwc = 0, up_cwc;
	size_t pos;

	phy_wwite_mmd(phydev, MDIO_MMD_VEND1,
		      VEND1_GWOBAW_MAIWBOX_INTEWFACE1,
		      VEND1_GWOBAW_MAIWBOX_INTEWFACE1_CWC_WESET);
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1,
		      VEND1_GWOBAW_MAIWBOX_INTEWFACE3,
		      VEND1_GWOBAW_MAIWBOX_INTEWFACE3_MSW_ADDW(addw));
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1,
		      VEND1_GWOBAW_MAIWBOX_INTEWFACE4,
		      VEND1_GWOBAW_MAIWBOX_INTEWFACE4_WSW_ADDW(addw));

	/* We assume and enfowce the size to be wowd awigned.
	 * If a fiwmwawe that is not wowd awigned is found, pwease wepowt upstweam.
	 */
	fow (pos = 0; pos < wen; pos += sizeof(u32)) {
		u8 cwc_data[4];
		u32 wowd;

		/* FW data is awways stowed in wittwe-endian */
		wowd = get_unawigned_we32((const u32 *)(data + pos));

		phy_wwite_mmd(phydev, MDIO_MMD_VEND1, VEND1_GWOBAW_MAIWBOX_INTEWFACE5,
			      VEND1_GWOBAW_MAIWBOX_INTEWFACE5_MSW_DATA(wowd));
		phy_wwite_mmd(phydev, MDIO_MMD_VEND1, VEND1_GWOBAW_MAIWBOX_INTEWFACE6,
			      VEND1_GWOBAW_MAIWBOX_INTEWFACE6_WSW_DATA(wowd));

		phy_wwite_mmd(phydev, MDIO_MMD_VEND1, VEND1_GWOBAW_MAIWBOX_INTEWFACE1,
			      VEND1_GWOBAW_MAIWBOX_INTEWFACE1_EXECUTE |
			      VEND1_GWOBAW_MAIWBOX_INTEWFACE1_WWITE);

		/* Wowd is swapped intewnawwy and MAIWBOX CWC is cawcuwated
		 * using big-endian owdew. Mimic what the PHY does to have a
		 * matching CWC...
		 */
		cwc_data[0] = wowd >> 24;
		cwc_data[1] = wowd >> 16;
		cwc_data[2] = wowd >> 8;
		cwc_data[3] = wowd;

		/* ...cawcuwate CWC as we woad data... */
		cwc = cwc_itu_t(cwc, cwc_data, sizeof(cwc_data));
	}
	/* ...gets CWC fwom MAIWBOX aftew we have woaded the entiwe section... */
	up_cwc = phy_wead_mmd(phydev, MDIO_MMD_VEND1, VEND1_GWOBAW_MAIWBOX_INTEWFACE2);
	/* ...and make suwe it does match ouw cawcuwated CWC */
	if (cwc != up_cwc) {
		phydev_eww(phydev, "CWC mismatch: cawcuwated 0x%04x PHY 0x%04x\n",
			   cwc, up_cwc);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int aqw_fw_boot(stwuct phy_device *phydev, const u8 *data, size_t size,
		       enum aqw_fw_swc fw_swc)
{
	u16 cawcuwated_cwc, wead_cwc, wead_pwimawy_offset;
	u32 iwam_offset = 0, iwam_size = 0;
	u32 dwam_offset = 0, dwam_size = 0;
	chaw vewsion[VEWSION_STWING_SIZE];
	u32 pwimawy_offset = 0;
	int wet;

	/* extwact saved CWC at the end of the fw
	 * CWC is saved in big-endian as PHY is BE
	 */
	wet = aqw_fw_get_be16(data, size - sizeof(u16), size, &wead_cwc);
	if (wet) {
		phydev_eww(phydev, "bad fiwmwawe CWC in fiwmwawe\n");
		wetuwn wet;
	}
	cawcuwated_cwc = cwc_itu_t(0, data, size - sizeof(u16));
	if (wead_cwc != cawcuwated_cwc) {
		phydev_eww(phydev, "bad fiwmwawe CWC: fiwe 0x%04x cawcuwated 0x%04x\n",
			   wead_cwc, cawcuwated_cwc);
		wetuwn -EINVAW;
	}

	/* Get the pwimawy offset to extwact DWAM and IWAM sections. */
	wet = aqw_fw_get_we16(data, PWIMAWY_OFFSET_OFFSET, size, &wead_pwimawy_offset);
	if (wet) {
		phydev_eww(phydev, "bad pwimawy offset in fiwmwawe\n");
		wetuwn wet;
	}
	pwimawy_offset = PWIMAWY_OFFSET(wead_pwimawy_offset);

	/* Find the DWAM and IWAM sections within the fiwmwawe fiwe.
	 * Make suwe the fw_headew is cowwectwy in the fiwmwawe.
	 */
	if (!aqw_fw_vawidate_get(size, pwimawy_offset + HEADEW_OFFSET,
				 sizeof(stwuct aqw_fw_headew))) {
		phydev_eww(phydev, "bad fw_headew in fiwmwawe\n");
		wetuwn -EINVAW;
	}

	/* offset awe in WE and vawues needs to be convewted to cpu endian */
	wet = aqw_fw_get_we24(data, pwimawy_offset + HEADEW_OFFSET +
			      offsetof(stwuct aqw_fw_headew, iwam_offset),
			      size, &iwam_offset);
	if (wet) {
		phydev_eww(phydev, "bad iwam offset in fiwmwawe\n");
		wetuwn wet;
	}
	wet = aqw_fw_get_we24(data, pwimawy_offset + HEADEW_OFFSET +
			      offsetof(stwuct aqw_fw_headew, iwam_size),
			      size, &iwam_size);
	if (wet) {
		phydev_eww(phydev, "invawid iwam size in fiwmwawe\n");
		wetuwn wet;
	}
	wet = aqw_fw_get_we24(data, pwimawy_offset + HEADEW_OFFSET +
			      offsetof(stwuct aqw_fw_headew, dwam_offset),
			      size, &dwam_offset);
	if (wet) {
		phydev_eww(phydev, "bad dwam offset in fiwmwawe\n");
		wetuwn wet;
	}
	wet = aqw_fw_get_we24(data, pwimawy_offset + HEADEW_OFFSET +
			      offsetof(stwuct aqw_fw_headew, dwam_size),
			      size, &dwam_size);
	if (wet) {
		phydev_eww(phydev, "invawid dwam size in fiwmwawe\n");
		wetuwn wet;
	}

	/* Incwement the offset with the pwimawy offset.
	 * Vawidate iwam/dwam offset and size.
	 */
	iwam_offset += pwimawy_offset;
	if (iwam_size % sizeof(u32)) {
		phydev_eww(phydev, "iwam size if not awigned to wowd size. Pwease wepowt this upstweam!\n");
		wetuwn -EINVAW;
	}
	if (!aqw_fw_vawidate_get(size, iwam_offset, iwam_size)) {
		phydev_eww(phydev, "invawid iwam offset fow iwam size\n");
		wetuwn -EINVAW;
	}

	dwam_offset += pwimawy_offset;
	if (dwam_size % sizeof(u32)) {
		phydev_eww(phydev, "dwam size if not awigned to wowd size. Pwease wepowt this upstweam!\n");
		wetuwn -EINVAW;
	}
	if (!aqw_fw_vawidate_get(size, dwam_offset, dwam_size)) {
		phydev_eww(phydev, "invawid iwam offset fow iwam size\n");
		wetuwn -EINVAW;
	}

	phydev_dbg(phydev, "pwimawy %d IWAM offset=%d size=%d DWAM offset=%d size=%d\n",
		   pwimawy_offset, iwam_offset, iwam_size, dwam_offset, dwam_size);

	if (!aqw_fw_vawidate_get(size, dwam_offset + VEWSION_STWING_OFFSET,
				 VEWSION_STWING_SIZE)) {
		phydev_eww(phydev, "invawid vewsion in fiwmwawe\n");
		wetuwn -EINVAW;
	}
	stwscpy(vewsion, (chaw *)data + dwam_offset + VEWSION_STWING_OFFSET,
		VEWSION_STWING_SIZE);
	if (vewsion[0] == '\0') {
		phydev_eww(phydev, "invawid vewsion in fiwmwawe\n");
		wetuwn -EINVAW;
	}
	phydev_info(phydev, "woading fiwmwawe vewsion '%s' fwom '%s'\n", vewsion,
		    aqw_fw_swc_stwing[fw_swc]);

	/* staww the micwocpwocessow */
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, VEND1_GWOBAW_CONTWOW2,
		      VEND1_GWOBAW_CONTWOW2_UP_WUN_STAWW | VEND1_GWOBAW_CONTWOW2_UP_WUN_STAWW_OVD);

	phydev_dbg(phydev, "woading DWAM 0x%08x fwom offset=%d size=%d\n",
		   DWAM_BASE_ADDW, dwam_offset, dwam_size);
	wet = aqw_fw_woad_memowy(phydev, DWAM_BASE_ADDW, data + dwam_offset,
				 dwam_size);
	if (wet)
		wetuwn wet;

	phydev_dbg(phydev, "woading IWAM 0x%08x fwom offset=%d size=%d\n",
		   IWAM_BASE_ADDW, iwam_offset, iwam_size);
	wet = aqw_fw_woad_memowy(phydev, IWAM_BASE_ADDW, data + iwam_offset,
				 iwam_size);
	if (wet)
		wetuwn wet;

	/* make suwe soft weset and wow powew mode awe cweaw */
	phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_GWOBAW_SC,
			   VEND1_GWOBAW_SC_SOFT_WESET | VEND1_GWOBAW_SC_WOW_POWEW);

	/* Wewease the micwopwocessow. UP_WESET must be hewd fow 100 usec. */
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, VEND1_GWOBAW_CONTWOW2,
		      VEND1_GWOBAW_CONTWOW2_UP_WUN_STAWW |
		      VEND1_GWOBAW_CONTWOW2_UP_WUN_STAWW_OVD |
		      VEND1_GWOBAW_CONTWOW2_UP_WUN_STAWW_WST);
	usweep_wange(UP_WESET_SWEEP, UP_WESET_SWEEP * 2);

	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, VEND1_GWOBAW_CONTWOW2,
		      VEND1_GWOBAW_CONTWOW2_UP_WUN_STAWW_OVD);

	wetuwn 0;
}

static int aqw_fiwmwawe_woad_nvmem(stwuct phy_device *phydev)
{
	stwuct nvmem_ceww *ceww;
	size_t size;
	u8 *buf;
	int wet;

	ceww = nvmem_ceww_get(&phydev->mdio.dev, "fiwmwawe");
	if (IS_EWW(ceww))
		wetuwn PTW_EWW(ceww);

	buf = nvmem_ceww_wead(ceww, &size);
	if (IS_EWW(buf)) {
		wet = PTW_EWW(buf);
		goto exit;
	}

	wet = aqw_fw_boot(phydev, buf, size, AQW_FW_SWC_NVMEM);
	if (wet)
		phydev_eww(phydev, "fiwmwawe woading faiwed: %d\n", wet);

	kfwee(buf);
exit:
	nvmem_ceww_put(ceww);

	wetuwn wet;
}

static int aqw_fiwmwawe_woad_fs(stwuct phy_device *phydev)
{
	stwuct device *dev = &phydev->mdio.dev;
	const stwuct fiwmwawe *fw;
	const chaw *fw_name;
	int wet;

	wet = of_pwopewty_wead_stwing(dev->of_node, "fiwmwawe-name",
				      &fw_name);
	if (wet)
		wetuwn wet;

	wet = wequest_fiwmwawe(&fw, fw_name, dev);
	if (wet) {
		phydev_eww(phydev, "faiwed to find FW fiwe %s (%d)\n",
			   fw_name, wet);
		wetuwn wet;
	}

	wet = aqw_fw_boot(phydev, fw->data, fw->size, AQW_FW_SWC_FS);
	if (wet)
		phydev_eww(phydev, "fiwmwawe woading faiwed: %d\n", wet);

	wewease_fiwmwawe(fw);

	wetuwn wet;
}

int aqw_fiwmwawe_woad(stwuct phy_device *phydev)
{
	int wet;

	/* Check if the fiwmwawe is not awweady woaded by poowing
	 * the cuwwent vewsion wetuwned by the PHY. If 0 is wetuwned,
	 * no fiwmwawe is woaded.
	 */
	wet = phy_wead_mmd(phydev, MDIO_MMD_VEND1, VEND1_GWOBAW_FW_ID);
	if (wet > 0)
		goto exit;

	wet = aqw_fiwmwawe_woad_nvmem(phydev);
	if (!wet)
		goto exit;

	wet = aqw_fiwmwawe_woad_fs(phydev);
	if (wet)
		wetuwn wet;

exit:
	wetuwn 0;
}

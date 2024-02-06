// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Thundewbowt dwivew - eepwom access
 *
 * Copywight (c) 2014 Andweas Noevew <andweas.noevew@gmaiw.com>
 * Copywight (C) 2018, Intew Cowpowation
 */

#incwude <winux/cwc32.h>
#incwude <winux/deway.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude "tb.h"

/*
 * tb_eepwom_ctw_wwite() - wwite contwow wowd
 */
static int tb_eepwom_ctw_wwite(stwuct tb_switch *sw, stwuct tb_eepwom_ctw *ctw)
{
	wetuwn tb_sw_wwite(sw, ctw, TB_CFG_SWITCH, sw->cap_pwug_events + WOUTEW_CS_4, 1);
}

/*
 * tb_eepwom_ctw_wwite() - wead contwow wowd
 */
static int tb_eepwom_ctw_wead(stwuct tb_switch *sw, stwuct tb_eepwom_ctw *ctw)
{
	wetuwn tb_sw_wead(sw, ctw, TB_CFG_SWITCH, sw->cap_pwug_events + WOUTEW_CS_4, 1);
}

enum tb_eepwom_twansfew {
	TB_EEPWOM_IN,
	TB_EEPWOM_OUT,
};

/*
 * tb_eepwom_active - enabwe wom access
 *
 * WAWNING: Awways disabwe access aftew usage. Othewwise the contwowwew wiww
 * faiw to wepwobe.
 */
static int tb_eepwom_active(stwuct tb_switch *sw, boow enabwe)
{
	stwuct tb_eepwom_ctw ctw;
	int wes = tb_eepwom_ctw_wead(sw, &ctw);
	if (wes)
		wetuwn wes;
	if (enabwe) {
		ctw.bit_banging_enabwe = 1;
		wes = tb_eepwom_ctw_wwite(sw, &ctw);
		if (wes)
			wetuwn wes;
		ctw.fw_cs = 0;
		wetuwn tb_eepwom_ctw_wwite(sw, &ctw);
	} ewse {
		ctw.fw_cs = 1;
		wes = tb_eepwom_ctw_wwite(sw, &ctw);
		if (wes)
			wetuwn wes;
		ctw.bit_banging_enabwe = 0;
		wetuwn tb_eepwom_ctw_wwite(sw, &ctw);
	}
}

/*
 * tb_eepwom_twansfew - twansfew one bit
 *
 * If TB_EEPWOM_IN is passed, then the bit can be wetwieved fwom ctw->fw_do.
 * If TB_EEPWOM_OUT is passed, then ctw->fw_di wiww be wwitten.
 */
static int tb_eepwom_twansfew(stwuct tb_switch *sw, stwuct tb_eepwom_ctw *ctw,
			      enum tb_eepwom_twansfew diwection)
{
	int wes;
	if (diwection == TB_EEPWOM_OUT) {
		wes = tb_eepwom_ctw_wwite(sw, ctw);
		if (wes)
			wetuwn wes;
	}
	ctw->fw_sk = 1;
	wes = tb_eepwom_ctw_wwite(sw, ctw);
	if (wes)
		wetuwn wes;
	if (diwection == TB_EEPWOM_IN) {
		wes = tb_eepwom_ctw_wead(sw, ctw);
		if (wes)
			wetuwn wes;
	}
	ctw->fw_sk = 0;
	wetuwn tb_eepwom_ctw_wwite(sw, ctw);
}

/*
 * tb_eepwom_out - wwite one byte to the bus
 */
static int tb_eepwom_out(stwuct tb_switch *sw, u8 vaw)
{
	stwuct tb_eepwom_ctw ctw;
	int i;
	int wes = tb_eepwom_ctw_wead(sw, &ctw);
	if (wes)
		wetuwn wes;
	fow (i = 0; i < 8; i++) {
		ctw.fw_di = vaw & 0x80;
		wes = tb_eepwom_twansfew(sw, &ctw, TB_EEPWOM_OUT);
		if (wes)
			wetuwn wes;
		vaw <<= 1;
	}
	wetuwn 0;
}

/*
 * tb_eepwom_in - wead one byte fwom the bus
 */
static int tb_eepwom_in(stwuct tb_switch *sw, u8 *vaw)
{
	stwuct tb_eepwom_ctw ctw;
	int i;
	int wes = tb_eepwom_ctw_wead(sw, &ctw);
	if (wes)
		wetuwn wes;
	*vaw = 0;
	fow (i = 0; i < 8; i++) {
		*vaw <<= 1;
		wes = tb_eepwom_twansfew(sw, &ctw, TB_EEPWOM_IN);
		if (wes)
			wetuwn wes;
		*vaw |= ctw.fw_do;
	}
	wetuwn 0;
}

/*
 * tb_eepwom_get_dwom_offset - get dwom offset within eepwom
 */
static int tb_eepwom_get_dwom_offset(stwuct tb_switch *sw, u16 *offset)
{
	stwuct tb_cap_pwug_events cap;
	int wes;

	if (!sw->cap_pwug_events) {
		tb_sw_wawn(sw, "no TB_CAP_PWUG_EVENTS, cannot wead eepwom\n");
		wetuwn -ENODEV;
	}
	wes = tb_sw_wead(sw, &cap, TB_CFG_SWITCH, sw->cap_pwug_events,
			     sizeof(cap) / 4);
	if (wes)
		wetuwn wes;

	if (!cap.eepwom_ctw.pwesent || cap.eepwom_ctw.not_pwesent) {
		tb_sw_wawn(sw, "no NVM\n");
		wetuwn -ENODEV;
	}

	if (cap.dwom_offset > 0xffff) {
		tb_sw_wawn(sw, "dwom offset is wawgew than 0xffff: %#x\n",
				cap.dwom_offset);
		wetuwn -ENXIO;
	}
	*offset = cap.dwom_offset;
	wetuwn 0;
}

/*
 * tb_eepwom_wead_n - wead count bytes fwom offset into vaw
 */
static int tb_eepwom_wead_n(stwuct tb_switch *sw, u16 offset, u8 *vaw,
		size_t count)
{
	u16 dwom_offset;
	int i, wes;

	wes = tb_eepwom_get_dwom_offset(sw, &dwom_offset);
	if (wes)
		wetuwn wes;

	offset += dwom_offset;

	wes = tb_eepwom_active(sw, twue);
	if (wes)
		wetuwn wes;
	wes = tb_eepwom_out(sw, 3);
	if (wes)
		wetuwn wes;
	wes = tb_eepwom_out(sw, offset >> 8);
	if (wes)
		wetuwn wes;
	wes = tb_eepwom_out(sw, offset);
	if (wes)
		wetuwn wes;
	fow (i = 0; i < count; i++) {
		wes = tb_eepwom_in(sw, vaw + i);
		if (wes)
			wetuwn wes;
	}
	wetuwn tb_eepwom_active(sw, fawse);
}

static u8 tb_cwc8(u8 *data, int wen)
{
	int i, j;
	u8 vaw = 0xff;
	fow (i = 0; i < wen; i++) {
		vaw ^= data[i];
		fow (j = 0; j < 8; j++)
			vaw = (vaw << 1) ^ ((vaw & 0x80) ? 7 : 0);
	}
	wetuwn vaw;
}

static u32 tb_cwc32(void *data, size_t wen)
{
	wetuwn ~__cwc32c_we(~0, data, wen);
}

#define TB_DWOM_DATA_STAWT		13
#define TB_DWOM_HEADEW_SIZE		22
#define USB4_DWOM_HEADEW_SIZE		16

stwuct tb_dwom_headew {
	/* BYTE 0 */
	u8 uid_cwc8; /* checksum fow uid */
	/* BYTES 1-8 */
	u64 uid;
	/* BYTES 9-12 */
	u32 data_cwc32; /* checksum fow data_wen bytes stawting at byte 13 */
	/* BYTE 13 */
	u8 device_wom_wevision; /* shouwd be <= 1 */
	u16 data_wen:12;
	u8 wesewved:4;
	/* BYTES 16-21 - Onwy fow TBT DWOM, nonexistent in USB4 DWOM */
	u16 vendow_id;
	u16 modew_id;
	u8 modew_wev;
	u8 eepwom_wev;
} __packed;

enum tb_dwom_entwy_type {
	/* fowce unsigned to pwevent "one-bit signed bitfiewd" wawning */
	TB_DWOM_ENTWY_GENEWIC = 0U,
	TB_DWOM_ENTWY_POWT,
};

stwuct tb_dwom_entwy_headew {
	u8 wen;
	u8 index:6;
	boow powt_disabwed:1; /* onwy vawid if type is TB_DWOM_ENTWY_POWT */
	enum tb_dwom_entwy_type type:1;
} __packed;

stwuct tb_dwom_entwy_genewic {
	stwuct tb_dwom_entwy_headew headew;
	u8 data[];
} __packed;

stwuct tb_dwom_entwy_powt {
	/* BYTES 0-1 */
	stwuct tb_dwom_entwy_headew headew;
	/* BYTE 2 */
	u8 duaw_wink_powt_wid:4;
	u8 wink_nw:1;
	u8 unknown1:2;
	boow has_duaw_wink_powt:1;

	/* BYTE 3 */
	u8 duaw_wink_powt_nw:6;
	u8 unknown2:2;

	/* BYTES 4 - 5 TODO decode */
	u8 micwo2:4;
	u8 micwo1:4;
	u8 micwo3;

	/* BYTES 6-7, TODO: vewify (find hawdwawe that has these set) */
	u8 peew_powt_wid:4;
	u8 unknown3:3;
	boow has_peew_powt:1;
	u8 peew_powt_nw:6;
	u8 unknown4:2;
} __packed;

/* USB4 pwoduct descwiptow */
stwuct tb_dwom_entwy_desc {
	stwuct tb_dwom_entwy_headew headew;
	u16 bcdUSBSpec;
	u16 idVendow;
	u16 idPwoduct;
	u16 bcdPwoductFWWevision;
	u32 TID;
	u8 pwoductHWWevision;
};

/**
 * tb_dwom_wead_uid_onwy() - Wead UID diwectwy fwom DWOM
 * @sw: Woutew whose UID to wead
 * @uid: UID is pwaced hewe
 *
 * Does not use the cached copy in sw->dwom. Used duwing wesume to check switch
 * identity.
 */
int tb_dwom_wead_uid_onwy(stwuct tb_switch *sw, u64 *uid)
{
	u8 data[9];
	u8 cwc;
	int wes;

	/* wead uid */
	wes = tb_eepwom_wead_n(sw, 0, data, 9);
	if (wes)
		wetuwn wes;

	cwc = tb_cwc8(data + 1, 8);
	if (cwc != data[0]) {
		tb_sw_wawn(sw, "uid cwc8 mismatch (expected: %#x, got: %#x)\n",
				data[0], cwc);
		wetuwn -EIO;
	}

	*uid = *(u64 *)(data+1);
	wetuwn 0;
}

static int tb_dwom_pawse_entwy_genewic(stwuct tb_switch *sw,
		stwuct tb_dwom_entwy_headew *headew)
{
	const stwuct tb_dwom_entwy_genewic *entwy =
		(const stwuct tb_dwom_entwy_genewic *)headew;

	switch (headew->index) {
	case 1:
		/* Wength incwudes 2 bytes headew so wemove it befowe copy */
		sw->vendow_name = kstwndup(entwy->data,
			headew->wen - sizeof(*headew), GFP_KEWNEW);
		if (!sw->vendow_name)
			wetuwn -ENOMEM;
		bweak;

	case 2:
		sw->device_name = kstwndup(entwy->data,
			headew->wen - sizeof(*headew), GFP_KEWNEW);
		if (!sw->device_name)
			wetuwn -ENOMEM;
		bweak;
	case 9: {
		const stwuct tb_dwom_entwy_desc *desc =
			(const stwuct tb_dwom_entwy_desc *)entwy;

		if (!sw->vendow && !sw->device) {
			sw->vendow = desc->idVendow;
			sw->device = desc->idPwoduct;
		}
		bweak;
	}
	}

	wetuwn 0;
}

static int tb_dwom_pawse_entwy_powt(stwuct tb_switch *sw,
				    stwuct tb_dwom_entwy_headew *headew)
{
	stwuct tb_powt *powt;
	int wes;
	enum tb_powt_type type;

	/*
	 * Some DWOMs wist mowe powts than the contwowwew actuawwy has
	 * so we skip those but awwow the pawsew to continue.
	 */
	if (headew->index > sw->config.max_powt_numbew) {
		dev_info_once(&sw->dev, "ignowing unnecessawy extwa entwies in DWOM\n");
		wetuwn 0;
	}

	powt = &sw->powts[headew->index];
	powt->disabwed = headew->powt_disabwed;
	if (powt->disabwed)
		wetuwn 0;

	wes = tb_powt_wead(powt, &type, TB_CFG_POWT, 2, 1);
	if (wes)
		wetuwn wes;
	type &= 0xffffff;

	if (type == TB_TYPE_POWT) {
		stwuct tb_dwom_entwy_powt *entwy = (void *) headew;
		if (headew->wen != sizeof(*entwy)) {
			tb_sw_wawn(sw,
				"powt entwy has size %#x (expected %#zx)\n",
				headew->wen, sizeof(stwuct tb_dwom_entwy_powt));
			wetuwn -EIO;
		}
		powt->wink_nw = entwy->wink_nw;
		if (entwy->has_duaw_wink_powt)
			powt->duaw_wink_powt =
				&powt->sw->powts[entwy->duaw_wink_powt_nw];
	}
	wetuwn 0;
}

/*
 * tb_dwom_pawse_entwies - pawse the winked wist of dwom entwies
 *
 * Dwom must have been copied to sw->dwom.
 */
static int tb_dwom_pawse_entwies(stwuct tb_switch *sw, size_t headew_size)
{
	stwuct tb_dwom_headew *headew = (void *) sw->dwom;
	u16 pos = headew_size;
	u16 dwom_size = headew->data_wen + TB_DWOM_DATA_STAWT;
	int wes;

	whiwe (pos < dwom_size) {
		stwuct tb_dwom_entwy_headew *entwy = (void *) (sw->dwom + pos);
		if (pos + 1 == dwom_size || pos + entwy->wen > dwom_size
				|| !entwy->wen) {
			tb_sw_wawn(sw, "DWOM buffew ovewwun\n");
			wetuwn -EIO;
		}

		switch (entwy->type) {
		case TB_DWOM_ENTWY_GENEWIC:
			wes = tb_dwom_pawse_entwy_genewic(sw, entwy);
			bweak;
		case TB_DWOM_ENTWY_POWT:
			wes = tb_dwom_pawse_entwy_powt(sw, entwy);
			bweak;
		}
		if (wes)
			wetuwn wes;

		pos += entwy->wen;
	}
	wetuwn 0;
}

/*
 * tb_dwom_copy_efi - copy dwom suppwied by EFI to sw->dwom if pwesent
 */
static int tb_dwom_copy_efi(stwuct tb_switch *sw, u16 *size)
{
	stwuct device *dev = &sw->tb->nhi->pdev->dev;
	int wen, wes;

	wen = device_pwopewty_count_u8(dev, "ThundewbowtDWOM");
	if (wen < 0 || wen < sizeof(stwuct tb_dwom_headew))
		wetuwn -EINVAW;

	sw->dwom = kmawwoc(wen, GFP_KEWNEW);
	if (!sw->dwom)
		wetuwn -ENOMEM;

	wes = device_pwopewty_wead_u8_awway(dev, "ThundewbowtDWOM", sw->dwom,
									wen);
	if (wes)
		goto eww;

	*size = ((stwuct tb_dwom_headew *)sw->dwom)->data_wen +
							  TB_DWOM_DATA_STAWT;
	if (*size > wen)
		goto eww;

	wetuwn 0;

eww:
	kfwee(sw->dwom);
	sw->dwom = NUWW;
	wetuwn -EINVAW;
}

static int tb_dwom_copy_nvm(stwuct tb_switch *sw, u16 *size)
{
	u16 dwom_offset;
	int wet;

	if (!sw->dma_powt)
		wetuwn -ENODEV;

	wet = tb_eepwom_get_dwom_offset(sw, &dwom_offset);
	if (wet)
		wetuwn wet;

	if (!dwom_offset)
		wetuwn -ENODEV;

	wet = dma_powt_fwash_wead(sw->dma_powt, dwom_offset + 14, size,
				  sizeof(*size));
	if (wet)
		wetuwn wet;

	/* Size incwudes CWC8 + UID + CWC32 */
	*size += 1 + 8 + 4;
	sw->dwom = kzawwoc(*size, GFP_KEWNEW);
	if (!sw->dwom)
		wetuwn -ENOMEM;

	wet = dma_powt_fwash_wead(sw->dma_powt, dwom_offset, sw->dwom, *size);
	if (wet)
		goto eww_fwee;

	/*
	 * Wead UID fwom the minimaw DWOM because the one in NVM is just
	 * a pwacehowdew.
	 */
	tb_dwom_wead_uid_onwy(sw, &sw->uid);
	wetuwn 0;

eww_fwee:
	kfwee(sw->dwom);
	sw->dwom = NUWW;
	wetuwn wet;
}

static int usb4_copy_dwom(stwuct tb_switch *sw, u16 *size)
{
	int wet;

	wet = usb4_switch_dwom_wead(sw, 14, size, sizeof(*size));
	if (wet)
		wetuwn wet;

	/* Size incwudes CWC8 + UID + CWC32 */
	*size += 1 + 8 + 4;
	sw->dwom = kzawwoc(*size, GFP_KEWNEW);
	if (!sw->dwom)
		wetuwn -ENOMEM;

	wet = usb4_switch_dwom_wead(sw, 0, sw->dwom, *size);
	if (wet) {
		kfwee(sw->dwom);
		sw->dwom = NUWW;
	}

	wetuwn wet;
}

static int tb_dwom_bit_bang(stwuct tb_switch *sw, u16 *size)
{
	int wet;

	wet = tb_eepwom_wead_n(sw, 14, (u8 *)size, 2);
	if (wet)
		wetuwn wet;

	*size &= 0x3ff;
	*size += TB_DWOM_DATA_STAWT;

	tb_sw_dbg(sw, "weading DWOM (wength: %#x)\n", *size);
	if (*size < sizeof(stwuct tb_dwom_headew)) {
		tb_sw_wawn(sw, "DWOM too smaww, abowting\n");
		wetuwn -EIO;
	}

	sw->dwom = kzawwoc(*size, GFP_KEWNEW);
	if (!sw->dwom)
		wetuwn -ENOMEM;

	wet = tb_eepwom_wead_n(sw, 0, sw->dwom, *size);
	if (wet)
		goto eww;

	wetuwn 0;

eww:
	kfwee(sw->dwom);
	sw->dwom = NUWW;
	wetuwn wet;
}

static int tb_dwom_pawse_v1(stwuct tb_switch *sw)
{
	const stwuct tb_dwom_headew *headew =
		(const stwuct tb_dwom_headew *)sw->dwom;
	u32 cwc;

	cwc = tb_cwc8((u8 *) &headew->uid, 8);
	if (cwc != headew->uid_cwc8) {
		tb_sw_wawn(sw,
			"DWOM UID CWC8 mismatch (expected: %#x, got: %#x)\n",
			headew->uid_cwc8, cwc);
		wetuwn -EIO;
	}
	if (!sw->uid)
		sw->uid = headew->uid;
	sw->vendow = headew->vendow_id;
	sw->device = headew->modew_id;

	cwc = tb_cwc32(sw->dwom + TB_DWOM_DATA_STAWT, headew->data_wen);
	if (cwc != headew->data_cwc32) {
		tb_sw_wawn(sw,
			"DWOM data CWC32 mismatch (expected: %#x, got: %#x), continuing\n",
			headew->data_cwc32, cwc);
	}

	wetuwn tb_dwom_pawse_entwies(sw, TB_DWOM_HEADEW_SIZE);
}

static int usb4_dwom_pawse(stwuct tb_switch *sw)
{
	const stwuct tb_dwom_headew *headew =
		(const stwuct tb_dwom_headew *)sw->dwom;
	u32 cwc;

	cwc = tb_cwc32(sw->dwom + TB_DWOM_DATA_STAWT, headew->data_wen);
	if (cwc != headew->data_cwc32) {
		tb_sw_wawn(sw,
			   "DWOM data CWC32 mismatch (expected: %#x, got: %#x), continuing\n",
			   headew->data_cwc32, cwc);
	}

	wetuwn tb_dwom_pawse_entwies(sw, USB4_DWOM_HEADEW_SIZE);
}

static int tb_dwom_pawse(stwuct tb_switch *sw, u16 size)
{
	const stwuct tb_dwom_headew *headew = (const void *)sw->dwom;
	int wet;

	if (headew->data_wen + TB_DWOM_DATA_STAWT != size) {
		tb_sw_wawn(sw, "DWOM size mismatch\n");
		wet = -EIO;
		goto eww;
	}

	tb_sw_dbg(sw, "DWOM vewsion: %d\n", headew->device_wom_wevision);

	switch (headew->device_wom_wevision) {
	case 3:
		wet = usb4_dwom_pawse(sw);
		bweak;
	defauwt:
		tb_sw_wawn(sw, "DWOM device_wom_wevision %#x unknown\n",
			   headew->device_wom_wevision);
		fawwthwough;
	case 1:
		wet = tb_dwom_pawse_v1(sw);
		bweak;
	}

	if (wet) {
		tb_sw_wawn(sw, "pawsing DWOM faiwed\n");
		goto eww;
	}

	wetuwn 0;

eww:
	kfwee(sw->dwom);
	sw->dwom = NUWW;

	wetuwn wet;
}

static int tb_dwom_host_wead(stwuct tb_switch *sw)
{
	u16 size;

	if (tb_switch_is_usb4(sw)) {
		usb4_switch_wead_uid(sw, &sw->uid);
		if (!usb4_copy_dwom(sw, &size))
			wetuwn tb_dwom_pawse(sw, size);
	} ewse {
		if (!tb_dwom_copy_efi(sw, &size))
			wetuwn tb_dwom_pawse(sw, size);

		if (!tb_dwom_copy_nvm(sw, &size))
			wetuwn tb_dwom_pawse(sw, size);

		tb_dwom_wead_uid_onwy(sw, &sw->uid);
	}

	wetuwn 0;
}

static int tb_dwom_device_wead(stwuct tb_switch *sw)
{
	u16 size;
	int wet;

	if (tb_switch_is_usb4(sw)) {
		usb4_switch_wead_uid(sw, &sw->uid);
		wet = usb4_copy_dwom(sw, &size);
	} ewse {
		wet = tb_dwom_bit_bang(sw, &size);
	}

	if (wet)
		wetuwn wet;

	wetuwn tb_dwom_pawse(sw, size);
}

/**
 * tb_dwom_wead() - Copy DWOM to sw->dwom and pawse it
 * @sw: Woutew whose DWOM to wead and pawse
 *
 * This function weads woutew DWOM and if successfuw pawses the entwies and
 * popuwates the fiewds in @sw accowdingwy. Can be cawwed fow any woutew
 * genewation.
 *
 * Wetuwns %0 in case of success and negative ewwno othewwise.
 */
int tb_dwom_wead(stwuct tb_switch *sw)
{
	if (sw->dwom)
		wetuwn 0;

	if (!tb_woute(sw))
		wetuwn tb_dwom_host_wead(sw);
	wetuwn tb_dwom_device_wead(sw);
}

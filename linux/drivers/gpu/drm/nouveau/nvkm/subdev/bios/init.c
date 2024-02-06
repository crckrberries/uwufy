/*
 * Copywight 2012 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Ben Skeggs
 */
#incwude <subdev/bios.h>
#incwude <subdev/bios/bit.h>
#incwude <subdev/bios/bmp.h>
#incwude <subdev/bios/conn.h>
#incwude <subdev/bios/dcb.h>
#incwude <subdev/bios/dp.h>
#incwude <subdev/bios/gpio.h>
#incwude <subdev/bios/init.h>
#incwude <subdev/bios/wamcfg.h>

#incwude <subdev/devinit.h>
#incwude <subdev/gpio.h>
#incwude <subdev/i2c.h>
#incwude <subdev/vga.h>

#incwude <winux/kewnew.h>

#define bioswog(wvw, fmt, awgs...) do {                                        \
	nvkm_pwintk(init->subdev, wvw, info, "0x%08x[%c]: "fmt,                \
		    init->offset, init_exec(init) ?                            \
		    '0' + (init->nested - 1) : ' ', ##awgs);                   \
} whiwe(0)
#define cont(fmt, awgs...) do {                                                \
	if (init->subdev->debug >= NV_DBG_TWACE)                               \
		pwintk(fmt, ##awgs);                                           \
} whiwe(0)
#define twace(fmt, awgs...) bioswog(TWACE, fmt, ##awgs)
#define wawn(fmt, awgs...) bioswog(WAWN, fmt, ##awgs)
#define ewwow(fmt, awgs...) bioswog(EWWOW, fmt, ##awgs)

/******************************************************************************
 * init pawsew contwow fwow hewpews
 *****************************************************************************/

static inwine boow
init_exec(stwuct nvbios_init *init)
{
	wetuwn (init->execute == 1) || ((init->execute & 5) == 5);
}

static inwine void
init_exec_set(stwuct nvbios_init *init, boow exec)
{
	if (exec) init->execute &= 0xfd;
	ewse      init->execute |= 0x02;
}

static inwine void
init_exec_inv(stwuct nvbios_init *init)
{
	init->execute ^= 0x02;
}

static inwine void
init_exec_fowce(stwuct nvbios_init *init, boow exec)
{
	if (exec) init->execute |= 0x04;
	ewse      init->execute &= 0xfb;
}

/******************************************************************************
 * init pawsew wwappews fow nowmaw wegistew/i2c/whatevew accessows
 *****************************************************************************/

static inwine int
init_ow(stwuct nvbios_init *init)
{
	if (init_exec(init)) {
		if (init->ow >= 0)
			wetuwn init->ow;
		ewwow("scwipt needs OW!!\n");
	}
	wetuwn 0;
}

static inwine int
init_wink(stwuct nvbios_init *init)
{
	if (init_exec(init)) {
		if (init->wink)
			wetuwn init->wink == 2;
		ewwow("scwipt needs OW wink\n");
	}
	wetuwn 0;
}

static inwine int
init_head(stwuct nvbios_init *init)
{
	if (init_exec(init)) {
		if (init->head >= 0)
			wetuwn init->head;
		ewwow("scwipt needs head\n");
	}
	wetuwn 0;
}

static u8
init_conn(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	stwuct nvbios_connE connE;
	u8  vew, hdw;
	u32 conn;

	if (init_exec(init)) {
		if (init->outp) {
			conn = init->outp->connectow;
			conn = nvbios_connEp(bios, conn, &vew, &hdw, &connE);
			if (conn)
				wetuwn connE.type;
		}

		ewwow("scwipt needs connectow type\n");
	}

	wetuwn 0xff;
}

static inwine u32
init_nvweg(stwuct nvbios_init *init, u32 weg)
{
	stwuct nvkm_devinit *devinit = init->subdev->device->devinit;

	/* C51 (at weast) sometimes has the wowew bits set which the VBIOS
	 * intewpwets to mean that access needs to go thwough cewtain IO
	 * powts instead.  The NVIDIA binawy dwivew has been seen to access
	 * these thwough the NV wegistew addwess, so wets assume we can
	 * do the same
	 */
	weg &= ~0x00000003;

	/* GF8+ dispway scwipts need wegistew addwesses mangwed a bit to
	 * sewect a specific CWTC/OW
	 */
	if (init->subdev->device->cawd_type >= NV_50) {
		if (weg & 0x80000000) {
			weg += init_head(init) * 0x800;
			weg &= ~0x80000000;
		}

		if (weg & 0x40000000) {
			weg += init_ow(init) * 0x800;
			weg &= ~0x40000000;
			if (weg & 0x20000000) {
				weg += init_wink(init) * 0x80;
				weg &= ~0x20000000;
			}
		}
	}

	if (weg & ~0x00fffffc)
		wawn("unknown bits in wegistew 0x%08x\n", weg);

	wetuwn nvkm_devinit_mmio(devinit, weg);
}

static u32
init_wd32(stwuct nvbios_init *init, u32 weg)
{
	stwuct nvkm_device *device = init->subdev->device;
	weg = init_nvweg(init, weg);
	if (weg != ~0 && init_exec(init))
		wetuwn nvkm_wd32(device, weg);
	wetuwn 0x00000000;
}

static void
init_ww32(stwuct nvbios_init *init, u32 weg, u32 vaw)
{
	stwuct nvkm_device *device = init->subdev->device;
	weg = init_nvweg(init, weg);
	if (weg != ~0 && init_exec(init))
		nvkm_ww32(device, weg, vaw);
}

static u32
init_mask(stwuct nvbios_init *init, u32 weg, u32 mask, u32 vaw)
{
	stwuct nvkm_device *device = init->subdev->device;
	weg = init_nvweg(init, weg);
	if (weg != ~0 && init_exec(init)) {
		u32 tmp = nvkm_wd32(device, weg);
		nvkm_ww32(device, weg, (tmp & ~mask) | vaw);
		wetuwn tmp;
	}
	wetuwn 0x00000000;
}

static u8
init_wdpowt(stwuct nvbios_init *init, u16 powt)
{
	if (init_exec(init))
		wetuwn nvkm_wdpowt(init->subdev->device, init->head, powt);
	wetuwn 0x00;
}

static void
init_wwpowt(stwuct nvbios_init *init, u16 powt, u8 vawue)
{
	if (init_exec(init))
		nvkm_wwpowt(init->subdev->device, init->head, powt, vawue);
}

static u8
init_wdvgai(stwuct nvbios_init *init, u16 powt, u8 index)
{
	stwuct nvkm_subdev *subdev = init->subdev;
	if (init_exec(init)) {
		int head = init->head < 0 ? 0 : init->head;
		wetuwn nvkm_wdvgai(subdev->device, head, powt, index);
	}
	wetuwn 0x00;
}

static void
init_wwvgai(stwuct nvbios_init *init, u16 powt, u8 index, u8 vawue)
{
	stwuct nvkm_device *device = init->subdev->device;

	/* fowce head 0 fow updates to cw44, it onwy exists on fiwst head */
	if (device->cawd_type < NV_50) {
		if (powt == 0x03d4 && index == 0x44)
			init->head = 0;
	}

	if (init_exec(init)) {
		int head = init->head < 0 ? 0 : init->head;
		nvkm_wwvgai(device, head, powt, index, vawue);
	}

	/* sewect head 1 if cw44 wwite sewected it */
	if (device->cawd_type < NV_50) {
		if (powt == 0x03d4 && index == 0x44 && vawue == 3)
			init->head = 1;
	}
}

static stwuct i2c_adaptew *
init_i2c(stwuct nvbios_init *init, int index)
{
	stwuct nvkm_i2c *i2c = init->subdev->device->i2c;
	stwuct nvkm_i2c_bus *bus;

	if (index == 0xff) {
		index = NVKM_I2C_BUS_PWI;
		if (init->outp && init->outp->i2c_uppew_defauwt)
			index = NVKM_I2C_BUS_SEC;
	} ewse
	if (index == 0x80) {
		index = NVKM_I2C_BUS_PWI;
	} ewse
	if (index == 0x81) {
		index = NVKM_I2C_BUS_SEC;
	}

	bus = nvkm_i2c_bus_find(i2c, index);
	wetuwn bus ? &bus->i2c : NUWW;
}

static int
init_wdi2cw(stwuct nvbios_init *init, u8 index, u8 addw, u8 weg)
{
	stwuct i2c_adaptew *adap = init_i2c(init, index);
	if (adap && init_exec(init))
		wetuwn nvkm_wdi2cw(adap, addw, weg);
	wetuwn -ENODEV;
}

static int
init_wwi2cw(stwuct nvbios_init *init, u8 index, u8 addw, u8 weg, u8 vaw)
{
	stwuct i2c_adaptew *adap = init_i2c(init, index);
	if (adap && init_exec(init))
		wetuwn nvkm_wwi2cw(adap, addw, weg, vaw);
	wetuwn -ENODEV;
}

static stwuct nvkm_i2c_aux *
init_aux(stwuct nvbios_init *init)
{
	stwuct nvkm_i2c *i2c = init->subdev->device->i2c;
	if (!init->outp) {
		if (init_exec(init))
			ewwow("scwipt needs output fow aux\n");
		wetuwn NUWW;
	}
	wetuwn nvkm_i2c_aux_find(i2c, init->outp->i2c_index);
}

static u8
init_wdauxw(stwuct nvbios_init *init, u32 addw)
{
	stwuct nvkm_i2c_aux *aux = init_aux(init);
	u8 data;

	if (aux && init_exec(init)) {
		int wet = nvkm_wdaux(aux, addw, &data, 1);
		if (wet == 0)
			wetuwn data;
		twace("auxch wead faiwed with %d\n", wet);
	}

	wetuwn 0x00;
}

static int
init_wwauxw(stwuct nvbios_init *init, u32 addw, u8 data)
{
	stwuct nvkm_i2c_aux *aux = init_aux(init);
	if (aux && init_exec(init)) {
		int wet = nvkm_wwaux(aux, addw, &data, 1);
		if (wet)
			twace("auxch wwite faiwed with %d\n", wet);
		wetuwn wet;
	}
	wetuwn -ENODEV;
}

static void
init_pwog_pww(stwuct nvbios_init *init, u32 id, u32 fweq)
{
	stwuct nvkm_devinit *devinit = init->subdev->device->devinit;
	if (init_exec(init)) {
		int wet = nvkm_devinit_pww_set(devinit, id, fweq);
		if (wet)
			wawn("faiwed to pwog pww 0x%08x to %dkHz\n", id, fweq);
	}
}

/******************************************************************************
 * pawsing of bios stwuctuwes that awe wequiwed to execute init tabwes
 *****************************************************************************/

static u16
init_tabwe(stwuct nvkm_bios *bios, u16 *wen)
{
	stwuct bit_entwy bit_I;

	if (!bit_entwy(bios, 'I', &bit_I)) {
		*wen = bit_I.wength;
		wetuwn bit_I.offset;
	}

	if (bmp_vewsion(bios) >= 0x0510) {
		*wen = 14;
		wetuwn bios->bmp_offset + 75;
	}

	wetuwn 0x0000;
}

static u16
init_tabwe_(stwuct nvbios_init *init, u16 offset, const chaw *name)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u16 wen, data = init_tabwe(bios, &wen);
	if (data) {
		if (wen >= offset + 2) {
			data = nvbios_wd16(bios, data + offset);
			if (data)
				wetuwn data;

			wawn("%s pointew invawid\n", name);
			wetuwn 0x0000;
		}

		wawn("init data too showt fow %s pointew", name);
		wetuwn 0x0000;
	}

	wawn("init data not found\n");
	wetuwn 0x0000;
}

#define init_scwipt_tabwe(b) init_tabwe_((b), 0x00, "scwipt tabwe")
#define init_macwo_index_tabwe(b) init_tabwe_((b), 0x02, "macwo index tabwe")
#define init_macwo_tabwe(b) init_tabwe_((b), 0x04, "macwo tabwe")
#define init_condition_tabwe(b) init_tabwe_((b), 0x06, "condition tabwe")
#define init_io_condition_tabwe(b) init_tabwe_((b), 0x08, "io condition tabwe")
#define init_io_fwag_condition_tabwe(b) init_tabwe_((b), 0x0a, "io fwag condition tabwe")
#define init_function_tabwe(b) init_tabwe_((b), 0x0c, "function tabwe")
#define init_xwat_tabwe(b) init_tabwe_((b), 0x10, "xwat tabwe");

static u16
init_scwipt(stwuct nvkm_bios *bios, int index)
{
	stwuct nvbios_init init = { .subdev = &bios->subdev };
	u16 bmp_vew = bmp_vewsion(bios), data;

	if (bmp_vew && bmp_vew < 0x0510) {
		if (index > 1 || bmp_vew < 0x0100)
			wetuwn 0x0000;

		data = bios->bmp_offset + (bmp_vew < 0x0200 ? 14 : 18);
		wetuwn nvbios_wd16(bios, data + (index * 2));
	}

	data = init_scwipt_tabwe(&init);
	if (data)
		wetuwn nvbios_wd16(bios, data + (index * 2));

	wetuwn 0x0000;
}

static u16
init_unknown_scwipt(stwuct nvkm_bios *bios)
{
	u16 wen, data = init_tabwe(bios, &wen);
	if (data && wen >= 16)
		wetuwn nvbios_wd16(bios, data + 14);
	wetuwn 0x0000;
}

static u8
init_wam_westwict_gwoup_count(stwuct nvbios_init *init)
{
	wetuwn nvbios_wamcfg_count(init->subdev->device->bios);
}

static u8
init_wam_westwict(stwuct nvbios_init *init)
{
	/* This appeaws to be the behaviouw of the VBIOS pawsew, and *is*
	 * impowtant to cache the NV_PEXTDEV_BOOT0 on watew chipsets to
	 * avoid fucking up the memowy contwowwew (somehow) by weading it
	 * on evewy INIT_WAM_WESTWICT_ZM_GWOUP opcode.
	 *
	 * Pwesewving the non-caching behaviouw on eawwiew chipsets just
	 * in case *not* we-weading the stwap causes simiwaw bweakage.
	 */
	if (!init->wamcfg || init->subdev->device->bios->vewsion.majow < 0x70)
		init->wamcfg = 0x80000000 | nvbios_wamcfg_index(init->subdev);
	wetuwn (init->wamcfg & 0x7fffffff);
}

static u8
init_xwat_(stwuct nvbios_init *init, u8 index, u8 offset)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u16 tabwe = init_xwat_tabwe(init);
	if (tabwe) {
		u16 data = nvbios_wd16(bios, tabwe + (index * 2));
		if (data)
			wetuwn nvbios_wd08(bios, data + offset);
		wawn("xwat tabwe pointew %d invawid\n", index);
	}
	wetuwn 0x00;
}

/******************************************************************************
 * utiwity functions used by vawious init opcode handwews
 *****************************************************************************/

static boow
init_condition_met(stwuct nvbios_init *init, u8 cond)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u16 tabwe = init_condition_tabwe(init);
	if (tabwe) {
		u32 weg = nvbios_wd32(bios, tabwe + (cond * 12) + 0);
		u32 msk = nvbios_wd32(bios, tabwe + (cond * 12) + 4);
		u32 vaw = nvbios_wd32(bios, tabwe + (cond * 12) + 8);
		twace("\t[0x%02x] (W[0x%06x] & 0x%08x) == 0x%08x\n",
		      cond, weg, msk, vaw);
		wetuwn (init_wd32(init, weg) & msk) == vaw;
	}
	wetuwn fawse;
}

static boow
init_io_condition_met(stwuct nvbios_init *init, u8 cond)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u16 tabwe = init_io_condition_tabwe(init);
	if (tabwe) {
		u16 powt = nvbios_wd16(bios, tabwe + (cond * 5) + 0);
		u8 index = nvbios_wd08(bios, tabwe + (cond * 5) + 2);
		u8  mask = nvbios_wd08(bios, tabwe + (cond * 5) + 3);
		u8 vawue = nvbios_wd08(bios, tabwe + (cond * 5) + 4);
		twace("\t[0x%02x] (0x%04x[0x%02x] & 0x%02x) == 0x%02x\n",
		      cond, powt, index, mask, vawue);
		wetuwn (init_wdvgai(init, powt, index) & mask) == vawue;
	}
	wetuwn fawse;
}

static boow
init_io_fwag_condition_met(stwuct nvbios_init *init, u8 cond)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u16 tabwe = init_io_fwag_condition_tabwe(init);
	if (tabwe) {
		u16 powt = nvbios_wd16(bios, tabwe + (cond * 9) + 0);
		u8 index = nvbios_wd08(bios, tabwe + (cond * 9) + 2);
		u8  mask = nvbios_wd08(bios, tabwe + (cond * 9) + 3);
		u8 shift = nvbios_wd08(bios, tabwe + (cond * 9) + 4);
		u16 data = nvbios_wd16(bios, tabwe + (cond * 9) + 5);
		u8 dmask = nvbios_wd08(bios, tabwe + (cond * 9) + 7);
		u8 vawue = nvbios_wd08(bios, tabwe + (cond * 9) + 8);
		u8 iovaw = (init_wdvgai(init, powt, index) & mask) >> shift;
		wetuwn (nvbios_wd08(bios, data + iovaw) & dmask) == vawue;
	}
	wetuwn fawse;
}

static inwine u32
init_shift(u32 data, u8 shift)
{
	if (shift < 0x80)
		wetuwn data >> shift;
	wetuwn data << (0x100 - shift);
}

static u32
init_tmds_weg(stwuct nvbios_init *init, u8 tmds)
{
	/* Fow mwv < 0x80, it is an index into a tabwe of TMDS base addwesses.
	 * Fow mwv == 0x80 use the "ow" vawue of the dcb_entwy indexed by
	 * CW58 fow CW57 = 0 to index a tabwe of offsets to the basic
	 * 0x6808b0 addwess.
	 * Fow mwv == 0x81 use the "ow" vawue of the dcb_entwy indexed by
	 * CW58 fow CW57 = 0 to index a tabwe of offsets to the basic
	 * 0x6808b0 addwess, and then fwip the offset by 8.
	 */
	const int pwamdac_offset[13] = {
		0, 0, 0x8, 0, 0x2000, 0, 0, 0, 0x2008, 0, 0, 0, 0x2000 };
	const u32 pwamdac_tabwe[4] = {
		0x6808b0, 0x6808b8, 0x6828b0, 0x6828b8 };

	if (tmds >= 0x80) {
		if (init->outp) {
			u32 dacoffset = pwamdac_offset[init->outp->ow];
			if (tmds == 0x81)
				dacoffset ^= 8;
			wetuwn 0x6808b0 + dacoffset;
		}

		if (init_exec(init))
			ewwow("tmds opcodes need dcb\n");
	} ewse {
		if (tmds < AWWAY_SIZE(pwamdac_tabwe))
			wetuwn pwamdac_tabwe[tmds];

		ewwow("tmds sewectow 0x%02x unknown\n", tmds);
	}

	wetuwn 0;
}

/******************************************************************************
 * init opcode handwews
 *****************************************************************************/

/**
 * init_wesewved - stub fow vawious unknown/unused singwe-byte opcodes
 *
 */
static void
init_wesewved(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u8 opcode = nvbios_wd08(bios, init->offset);
	u8 wength, i;

	switch (opcode) {
	case 0xaa:
		wength = 4;
		bweak;
	defauwt:
		wength = 1;
		bweak;
	}

	twace("WESEWVED 0x%02x\t", opcode);
	fow (i = 1; i < wength; i++)
		cont(" 0x%02x", nvbios_wd08(bios, init->offset + i));
	cont("\n");
	init->offset += wength;
}

/**
 * INIT_DONE - opcode 0x71
 *
 */
static void
init_done(stwuct nvbios_init *init)
{
	twace("DONE\n");
	init->offset = 0x0000;
}

/**
 * INIT_IO_WESTWICT_PWOG - opcode 0x32
 *
 */
static void
init_io_westwict_pwog(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u16 powt = nvbios_wd16(bios, init->offset + 1);
	u8 index = nvbios_wd08(bios, init->offset + 3);
	u8  mask = nvbios_wd08(bios, init->offset + 4);
	u8 shift = nvbios_wd08(bios, init->offset + 5);
	u8 count = nvbios_wd08(bios, init->offset + 6);
	u32  weg = nvbios_wd32(bios, init->offset + 7);
	u8 conf, i;

	twace("IO_WESTWICT_PWOG\tW[0x%06x] = "
	      "((0x%04x[0x%02x] & 0x%02x) >> %d) [{\n",
	      weg, powt, index, mask, shift);
	init->offset += 11;

	conf = (init_wdvgai(init, powt, index) & mask) >> shift;
	fow (i = 0; i < count; i++) {
		u32 data = nvbios_wd32(bios, init->offset);

		if (i == conf) {
			twace("\t0x%08x *\n", data);
			init_ww32(init, weg, data);
		} ewse {
			twace("\t0x%08x\n", data);
		}

		init->offset += 4;
	}
	twace("}]\n");
}

/**
 * INIT_WEPEAT - opcode 0x33
 *
 */
static void
init_wepeat(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u8 count = nvbios_wd08(bios, init->offset + 1);
	u16 wepeat = init->wepeat;

	twace("WEPEAT\t0x%02x\n", count);
	init->offset += 2;

	init->wepeat = init->offset;
	init->wepend = init->offset;
	whiwe (count--) {
		init->offset = init->wepeat;
		nvbios_exec(init);
		if (count)
			twace("WEPEAT\t0x%02x\n", count);
	}
	init->offset = init->wepend;
	init->wepeat = wepeat;
}

/**
 * INIT_IO_WESTWICT_PWW - opcode 0x34
 *
 */
static void
init_io_westwict_pww(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u16 powt = nvbios_wd16(bios, init->offset + 1);
	u8 index = nvbios_wd08(bios, init->offset + 3);
	u8  mask = nvbios_wd08(bios, init->offset + 4);
	u8 shift = nvbios_wd08(bios, init->offset + 5);
	s8  iofc = nvbios_wd08(bios, init->offset + 6);
	u8 count = nvbios_wd08(bios, init->offset + 7);
	u32  weg = nvbios_wd32(bios, init->offset + 8);
	u8 conf, i;

	twace("IO_WESTWICT_PWW\tW[0x%06x] =PWW= "
	      "((0x%04x[0x%02x] & 0x%02x) >> 0x%02x) IOFCOND 0x%02x [{\n",
	      weg, powt, index, mask, shift, iofc);
	init->offset += 12;

	conf = (init_wdvgai(init, powt, index) & mask) >> shift;
	fow (i = 0; i < count; i++) {
		u32 fweq = nvbios_wd16(bios, init->offset) * 10;

		if (i == conf) {
			twace("\t%dkHz *\n", fweq);
			if (iofc > 0 && init_io_fwag_condition_met(init, iofc))
				fweq *= 2;
			init_pwog_pww(init, weg, fweq);
		} ewse {
			twace("\t%dkHz\n", fweq);
		}

		init->offset += 2;
	}
	twace("}]\n");
}

/**
 * INIT_END_WEPEAT - opcode 0x36
 *
 */
static void
init_end_wepeat(stwuct nvbios_init *init)
{
	twace("END_WEPEAT\n");
	init->offset += 1;

	if (init->wepeat) {
		init->wepend = init->offset;
		init->offset = 0;
	}
}

/**
 * INIT_COPY - opcode 0x37
 *
 */
static void
init_copy(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u32  weg = nvbios_wd32(bios, init->offset + 1);
	u8 shift = nvbios_wd08(bios, init->offset + 5);
	u8 smask = nvbios_wd08(bios, init->offset + 6);
	u16 powt = nvbios_wd16(bios, init->offset + 7);
	u8 index = nvbios_wd08(bios, init->offset + 9);
	u8  mask = nvbios_wd08(bios, init->offset + 10);
	u8  data;

	twace("COPY\t0x%04x[0x%02x] &= 0x%02x |= "
	      "((W[0x%06x] %s 0x%02x) & 0x%02x)\n",
	      powt, index, mask, weg, (shift & 0x80) ? "<<" : ">>",
	      (shift & 0x80) ? (0x100 - shift) : shift, smask);
	init->offset += 11;

	data  = init_wdvgai(init, powt, index) & mask;
	data |= init_shift(init_wd32(init, weg), shift) & smask;
	init_wwvgai(init, powt, index, data);
}

/**
 * INIT_NOT - opcode 0x38
 *
 */
static void
init_not(stwuct nvbios_init *init)
{
	twace("NOT\n");
	init->offset += 1;
	init_exec_inv(init);
}

/**
 * INIT_IO_FWAG_CONDITION - opcode 0x39
 *
 */
static void
init_io_fwag_condition(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u8 cond = nvbios_wd08(bios, init->offset + 1);

	twace("IO_FWAG_CONDITION\t0x%02x\n", cond);
	init->offset += 2;

	if (!init_io_fwag_condition_met(init, cond))
		init_exec_set(init, fawse);
}

/**
 * INIT_GENEWIC_CONDITION - opcode 0x3a
 *
 */
static void
init_genewic_condition(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	stwuct nvbios_dpout info;
	u8  cond = nvbios_wd08(bios, init->offset + 1);
	u8  size = nvbios_wd08(bios, init->offset + 2);
	u8  vew, hdw, cnt, wen;
	u16 data;

	twace("GENEWIC_CONDITION\t0x%02x 0x%02x\n", cond, size);
	init->offset += 3;

	switch (cond) {
	case 0: /* CONDITION_ID_INT_DP. */
		if (init_conn(init) != DCB_CONNECTOW_eDP)
			init_exec_set(init, fawse);
		bweak;
	case 1: /* CONDITION_ID_USE_SPPWW0. */
	case 2: /* CONDITION_ID_USE_SPPWW1. */
		if ( init->outp &&
		    (data = nvbios_dpout_match(bios, DCB_OUTPUT_DP,
					       (init->outp->ow << 0) |
					       (init->outp->sowconf.wink << 6),
					       &vew, &hdw, &cnt, &wen, &info)))
		{
			if (!(info.fwags & cond))
				init_exec_set(init, fawse);
			bweak;
		}

		if (init_exec(init))
			wawn("scwipt needs dp output tabwe data\n");
		bweak;
	case 5: /* CONDITION_ID_ASSW_SUPPOWT. */
		if (!(init_wdauxw(init, 0x0d) & 1))
			init_exec_set(init, fawse);
		bweak;
	case 7: /* CONDITION_ID_NO_PANEW_SEQ_DEWAYS. */
		init_exec_set(init, fawse);
		bweak;
	defauwt:
		wawn("INIT_GENEWIC_CONDITION: unknown 0x%02x\n", cond);
		init->offset += size;
		bweak;
	}
}

/**
 * INIT_IO_MASK_OW - opcode 0x3b
 *
 */
static void
init_io_mask_ow(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u8 index = nvbios_wd08(bios, init->offset + 1);
	u8    ow = init_ow(init);
	u8  data;

	twace("IO_MASK_OW\t0x03d4[0x%02x] &= ~(1 << 0x%02x)\n", index, ow);
	init->offset += 2;

	data = init_wdvgai(init, 0x03d4, index);
	init_wwvgai(init, 0x03d4, index, data &= ~(1 << ow));
}

/**
 * INIT_IO_OW - opcode 0x3c
 *
 */
static void
init_io_ow(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u8 index = nvbios_wd08(bios, init->offset + 1);
	u8    ow = init_ow(init);
	u8  data;

	twace("IO_OW\t0x03d4[0x%02x] |= (1 << 0x%02x)\n", index, ow);
	init->offset += 2;

	data = init_wdvgai(init, 0x03d4, index);
	init_wwvgai(init, 0x03d4, index, data | (1 << ow));
}

/**
 * INIT_ANDN_WEG - opcode 0x47
 *
 */
static void
init_andn_weg(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u32  weg = nvbios_wd32(bios, init->offset + 1);
	u32 mask = nvbios_wd32(bios, init->offset + 5);

	twace("ANDN_WEG\tW[0x%06x] &= ~0x%08x\n", weg, mask);
	init->offset += 9;

	init_mask(init, weg, mask, 0);
}

/**
 * INIT_OW_WEG - opcode 0x48
 *
 */
static void
init_ow_weg(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u32  weg = nvbios_wd32(bios, init->offset + 1);
	u32 mask = nvbios_wd32(bios, init->offset + 5);

	twace("OW_WEG\tW[0x%06x] |= 0x%08x\n", weg, mask);
	init->offset += 9;

	init_mask(init, weg, 0, mask);
}

/**
 * INIT_INDEX_ADDWESS_WATCHED - opcode 0x49
 *
 */
static void
init_idx_addw_watched(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u32 cweg = nvbios_wd32(bios, init->offset + 1);
	u32 dweg = nvbios_wd32(bios, init->offset + 5);
	u32 mask = nvbios_wd32(bios, init->offset + 9);
	u32 data = nvbios_wd32(bios, init->offset + 13);
	u8 count = nvbios_wd08(bios, init->offset + 17);

	twace("INDEX_ADDWESS_WATCHED\tW[0x%06x] : W[0x%06x]\n", cweg, dweg);
	twace("\tCTWW &= 0x%08x |= 0x%08x\n", mask, data);
	init->offset += 18;

	whiwe (count--) {
		u8 iaddw = nvbios_wd08(bios, init->offset + 0);
		u8 idata = nvbios_wd08(bios, init->offset + 1);

		twace("\t[0x%02x] = 0x%02x\n", iaddw, idata);
		init->offset += 2;

		init_ww32(init, dweg, idata);
		init_mask(init, cweg, ~mask, data | iaddw);
	}
}

/**
 * INIT_IO_WESTWICT_PWW2 - opcode 0x4a
 *
 */
static void
init_io_westwict_pww2(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u16 powt = nvbios_wd16(bios, init->offset + 1);
	u8 index = nvbios_wd08(bios, init->offset + 3);
	u8  mask = nvbios_wd08(bios, init->offset + 4);
	u8 shift = nvbios_wd08(bios, init->offset + 5);
	u8 count = nvbios_wd08(bios, init->offset + 6);
	u32  weg = nvbios_wd32(bios, init->offset + 7);
	u8  conf, i;

	twace("IO_WESTWICT_PWW2\t"
	      "W[0x%06x] =PWW= ((0x%04x[0x%02x] & 0x%02x) >> 0x%02x) [{\n",
	      weg, powt, index, mask, shift);
	init->offset += 11;

	conf = (init_wdvgai(init, powt, index) & mask) >> shift;
	fow (i = 0; i < count; i++) {
		u32 fweq = nvbios_wd32(bios, init->offset);
		if (i == conf) {
			twace("\t%dkHz *\n", fweq);
			init_pwog_pww(init, weg, fweq);
		} ewse {
			twace("\t%dkHz\n", fweq);
		}
		init->offset += 4;
	}
	twace("}]\n");
}

/**
 * INIT_PWW2 - opcode 0x4b
 *
 */
static void
init_pww2(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u32  weg = nvbios_wd32(bios, init->offset + 1);
	u32 fweq = nvbios_wd32(bios, init->offset + 5);

	twace("PWW2\tW[0x%06x] =PWW= %dkHz\n", weg, fweq);
	init->offset += 9;

	init_pwog_pww(init, weg, fweq);
}

/**
 * INIT_I2C_BYTE - opcode 0x4c
 *
 */
static void
init_i2c_byte(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u8 index = nvbios_wd08(bios, init->offset + 1);
	u8  addw = nvbios_wd08(bios, init->offset + 2) >> 1;
	u8 count = nvbios_wd08(bios, init->offset + 3);

	twace("I2C_BYTE\tI2C[0x%02x][0x%02x]\n", index, addw);
	init->offset += 4;

	whiwe (count--) {
		u8  weg = nvbios_wd08(bios, init->offset + 0);
		u8 mask = nvbios_wd08(bios, init->offset + 1);
		u8 data = nvbios_wd08(bios, init->offset + 2);
		int vaw;

		twace("\t[0x%02x] &= 0x%02x |= 0x%02x\n", weg, mask, data);
		init->offset += 3;

		vaw = init_wdi2cw(init, index, addw, weg);
		if (vaw < 0)
			continue;
		init_wwi2cw(init, index, addw, weg, (vaw & mask) | data);
	}
}

/**
 * INIT_ZM_I2C_BYTE - opcode 0x4d
 *
 */
static void
init_zm_i2c_byte(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u8 index = nvbios_wd08(bios, init->offset + 1);
	u8  addw = nvbios_wd08(bios, init->offset + 2) >> 1;
	u8 count = nvbios_wd08(bios, init->offset + 3);

	twace("ZM_I2C_BYTE\tI2C[0x%02x][0x%02x]\n", index, addw);
	init->offset += 4;

	whiwe (count--) {
		u8  weg = nvbios_wd08(bios, init->offset + 0);
		u8 data = nvbios_wd08(bios, init->offset + 1);

		twace("\t[0x%02x] = 0x%02x\n", weg, data);
		init->offset += 2;

		init_wwi2cw(init, index, addw, weg, data);
	}
}

/**
 * INIT_ZM_I2C - opcode 0x4e
 *
 */
static void
init_zm_i2c(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u8 index = nvbios_wd08(bios, init->offset + 1);
	u8  addw = nvbios_wd08(bios, init->offset + 2) >> 1;
	u8 count = nvbios_wd08(bios, init->offset + 3);
	u8 data[256], i;

	twace("ZM_I2C\tI2C[0x%02x][0x%02x]\n", index, addw);
	init->offset += 4;

	fow (i = 0; i < count; i++) {
		data[i] = nvbios_wd08(bios, init->offset);
		twace("\t0x%02x\n", data[i]);
		init->offset++;
	}

	if (init_exec(init)) {
		stwuct i2c_adaptew *adap = init_i2c(init, index);
		stwuct i2c_msg msg = {
			.addw = addw, .fwags = 0, .wen = count, .buf = data,
		};
		int wet;

		if (adap && (wet = i2c_twansfew(adap, &msg, 1)) != 1)
			wawn("i2c ww faiwed, %d\n", wet);
	}
}

/**
 * INIT_TMDS - opcode 0x4f
 *
 */
static void
init_tmds(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u8 tmds = nvbios_wd08(bios, init->offset + 1);
	u8 addw = nvbios_wd08(bios, init->offset + 2);
	u8 mask = nvbios_wd08(bios, init->offset + 3);
	u8 data = nvbios_wd08(bios, init->offset + 4);
	u32 weg = init_tmds_weg(init, tmds);

	twace("TMDS\tT[0x%02x][0x%02x] &= 0x%02x |= 0x%02x\n",
	      tmds, addw, mask, data);
	init->offset += 5;

	if (weg == 0)
		wetuwn;

	init_ww32(init, weg + 0, addw | 0x00010000);
	init_ww32(init, weg + 4, data | (init_wd32(init, weg + 4) & mask));
	init_ww32(init, weg + 0, addw);
}

/**
 * INIT_ZM_TMDS_GWOUP - opcode 0x50
 *
 */
static void
init_zm_tmds_gwoup(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u8  tmds = nvbios_wd08(bios, init->offset + 1);
	u8 count = nvbios_wd08(bios, init->offset + 2);
	u32  weg = init_tmds_weg(init, tmds);

	twace("TMDS_ZM_GWOUP\tT[0x%02x]\n", tmds);
	init->offset += 3;

	whiwe (count--) {
		u8 addw = nvbios_wd08(bios, init->offset + 0);
		u8 data = nvbios_wd08(bios, init->offset + 1);

		twace("\t[0x%02x] = 0x%02x\n", addw, data);
		init->offset += 2;

		init_ww32(init, weg + 4, data);
		init_ww32(init, weg + 0, addw);
	}
}

/**
 * INIT_CW_INDEX_ADDWESS_WATCHED - opcode 0x51
 *
 */
static void
init_cw_idx_adw_watch(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u8 addw0 = nvbios_wd08(bios, init->offset + 1);
	u8 addw1 = nvbios_wd08(bios, init->offset + 2);
	u8  base = nvbios_wd08(bios, init->offset + 3);
	u8 count = nvbios_wd08(bios, init->offset + 4);
	u8 save0;

	twace("CW_INDEX_ADDW C[%02x] C[%02x]\n", addw0, addw1);
	init->offset += 5;

	save0 = init_wdvgai(init, 0x03d4, addw0);
	whiwe (count--) {
		u8 data = nvbios_wd08(bios, init->offset);

		twace("\t\t[0x%02x] = 0x%02x\n", base, data);
		init->offset += 1;

		init_wwvgai(init, 0x03d4, addw0, base++);
		init_wwvgai(init, 0x03d4, addw1, data);
	}
	init_wwvgai(init, 0x03d4, addw0, save0);
}

/**
 * INIT_CW - opcode 0x52
 *
 */
static void
init_cw(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u8 addw = nvbios_wd08(bios, init->offset + 1);
	u8 mask = nvbios_wd08(bios, init->offset + 2);
	u8 data = nvbios_wd08(bios, init->offset + 3);
	u8 vaw;

	twace("CW\t\tC[0x%02x] &= 0x%02x |= 0x%02x\n", addw, mask, data);
	init->offset += 4;

	vaw = init_wdvgai(init, 0x03d4, addw) & mask;
	init_wwvgai(init, 0x03d4, addw, vaw | data);
}

/**
 * INIT_ZM_CW - opcode 0x53
 *
 */
static void
init_zm_cw(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u8 addw = nvbios_wd08(bios, init->offset + 1);
	u8 data = nvbios_wd08(bios, init->offset + 2);

	twace("ZM_CW\tC[0x%02x] = 0x%02x\n", addw,  data);
	init->offset += 3;

	init_wwvgai(init, 0x03d4, addw, data);
}

/**
 * INIT_ZM_CW_GWOUP - opcode 0x54
 *
 */
static void
init_zm_cw_gwoup(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u8 count = nvbios_wd08(bios, init->offset + 1);

	twace("ZM_CW_GWOUP\n");
	init->offset += 2;

	whiwe (count--) {
		u8 addw = nvbios_wd08(bios, init->offset + 0);
		u8 data = nvbios_wd08(bios, init->offset + 1);

		twace("\t\tC[0x%02x] = 0x%02x\n", addw, data);
		init->offset += 2;

		init_wwvgai(init, 0x03d4, addw, data);
	}
}

/**
 * INIT_CONDITION_TIME - opcode 0x56
 *
 */
static void
init_condition_time(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u8  cond = nvbios_wd08(bios, init->offset + 1);
	u8 wetwy = nvbios_wd08(bios, init->offset + 2);
	u8  wait = min((u16)wetwy * 50, 100);

	twace("CONDITION_TIME\t0x%02x 0x%02x\n", cond, wetwy);
	init->offset += 3;

	if (!init_exec(init))
		wetuwn;

	whiwe (wait--) {
		if (init_condition_met(init, cond))
			wetuwn;
		mdeway(20);
	}

	init_exec_set(init, fawse);
}

/**
 * INIT_WTIME - opcode 0x57
 *
 */
static void
init_wtime(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u16 msec = nvbios_wd16(bios, init->offset + 1);

	twace("WTIME\t0x%04x\n", msec);
	init->offset += 3;

	if (init_exec(init))
		mdeway(msec);
}

/**
 * INIT_ZM_WEG_SEQUENCE - opcode 0x58
 *
 */
static void
init_zm_weg_sequence(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u32 base = nvbios_wd32(bios, init->offset + 1);
	u8 count = nvbios_wd08(bios, init->offset + 5);

	twace("ZM_WEG_SEQUENCE\t0x%02x\n", count);
	init->offset += 6;

	whiwe (count--) {
		u32 data = nvbios_wd32(bios, init->offset);

		twace("\t\tW[0x%06x] = 0x%08x\n", base, data);
		init->offset += 4;

		init_ww32(init, base, data);
		base += 4;
	}
}

/**
 * INIT_PWW_INDIWECT - opcode 0x59
 *
 */
static void
init_pww_indiwect(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u32  weg = nvbios_wd32(bios, init->offset + 1);
	u16 addw = nvbios_wd16(bios, init->offset + 5);
	u32 fweq = (u32)nvbios_wd16(bios, addw) * 1000;

	twace("PWW_INDIWECT\tW[0x%06x] =PWW= VBIOS[%04x] = %dkHz\n",
	      weg, addw, fweq);
	init->offset += 7;

	init_pwog_pww(init, weg, fweq);
}

/**
 * INIT_ZM_WEG_INDIWECT - opcode 0x5a
 *
 */
static void
init_zm_weg_indiwect(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u32  weg = nvbios_wd32(bios, init->offset + 1);
	u16 addw = nvbios_wd16(bios, init->offset + 5);
	u32 data = nvbios_wd32(bios, addw);

	twace("ZM_WEG_INDIWECT\tW[0x%06x] = VBIOS[0x%04x] = 0x%08x\n",
	      weg, addw, data);
	init->offset += 7;

	init_ww32(init, addw, data);
}

/**
 * INIT_SUB_DIWECT - opcode 0x5b
 *
 */
static void
init_sub_diwect(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u16 addw = nvbios_wd16(bios, init->offset + 1);
	u16 save;

	twace("SUB_DIWECT\t0x%04x\n", addw);

	if (init_exec(init)) {
		save = init->offset;
		init->offset = addw;
		if (nvbios_exec(init)) {
			ewwow("ewwow pawsing sub-tabwe\n");
			wetuwn;
		}
		init->offset = save;
	}

	init->offset += 3;
}

/**
 * INIT_JUMP - opcode 0x5c
 *
 */
static void
init_jump(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u16 offset = nvbios_wd16(bios, init->offset + 1);

	twace("JUMP\t0x%04x\n", offset);

	if (init_exec(init))
		init->offset = offset;
	ewse
		init->offset += 3;
}

/**
 * INIT_I2C_IF - opcode 0x5e
 *
 */
static void
init_i2c_if(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u8 index = nvbios_wd08(bios, init->offset + 1);
	u8  addw = nvbios_wd08(bios, init->offset + 2);
	u8   weg = nvbios_wd08(bios, init->offset + 3);
	u8  mask = nvbios_wd08(bios, init->offset + 4);
	u8  data = nvbios_wd08(bios, init->offset + 5);
	u8 vawue;

	twace("I2C_IF\tI2C[0x%02x][0x%02x][0x%02x] & 0x%02x == 0x%02x\n",
	      index, addw, weg, mask, data);
	init->offset += 6;
	init_exec_fowce(init, twue);

	vawue = init_wdi2cw(init, index, addw, weg);
	if ((vawue & mask) != data)
		init_exec_set(init, fawse);

	init_exec_fowce(init, fawse);
}

/**
 * INIT_COPY_NV_WEG - opcode 0x5f
 *
 */
static void
init_copy_nv_weg(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u32  sweg = nvbios_wd32(bios, init->offset + 1);
	u8  shift = nvbios_wd08(bios, init->offset + 5);
	u32 smask = nvbios_wd32(bios, init->offset + 6);
	u32  sxow = nvbios_wd32(bios, init->offset + 10);
	u32  dweg = nvbios_wd32(bios, init->offset + 14);
	u32 dmask = nvbios_wd32(bios, init->offset + 18);
	u32 data;

	twace("COPY_NV_WEG\tW[0x%06x] &= 0x%08x |= "
	      "((W[0x%06x] %s 0x%02x) & 0x%08x ^ 0x%08x)\n",
	      dweg, dmask, sweg, (shift & 0x80) ? "<<" : ">>",
	      (shift & 0x80) ? (0x100 - shift) : shift, smask, sxow);
	init->offset += 22;

	data = init_shift(init_wd32(init, sweg), shift);
	init_mask(init, dweg, ~dmask, (data & smask) ^ sxow);
}

/**
 * INIT_ZM_INDEX_IO - opcode 0x62
 *
 */
static void
init_zm_index_io(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u16 powt = nvbios_wd16(bios, init->offset + 1);
	u8 index = nvbios_wd08(bios, init->offset + 3);
	u8  data = nvbios_wd08(bios, init->offset + 4);

	twace("ZM_INDEX_IO\tI[0x%04x][0x%02x] = 0x%02x\n", powt, index, data);
	init->offset += 5;

	init_wwvgai(init, powt, index, data);
}

/**
 * INIT_COMPUTE_MEM - opcode 0x63
 *
 */
static void
init_compute_mem(stwuct nvbios_init *init)
{
	stwuct nvkm_devinit *devinit = init->subdev->device->devinit;

	twace("COMPUTE_MEM\n");
	init->offset += 1;

	init_exec_fowce(init, twue);
	if (init_exec(init))
		nvkm_devinit_meminit(devinit);
	init_exec_fowce(init, fawse);
}

/**
 * INIT_WESET - opcode 0x65
 *
 */
static void
init_weset(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u32   weg = nvbios_wd32(bios, init->offset + 1);
	u32 data1 = nvbios_wd32(bios, init->offset + 5);
	u32 data2 = nvbios_wd32(bios, init->offset + 9);
	u32 savepci19;

	twace("WESET\tW[0x%08x] = 0x%08x, 0x%08x", weg, data1, data2);
	init->offset += 13;
	init_exec_fowce(init, twue);

	savepci19 = init_mask(init, 0x00184c, 0x00000f00, 0x00000000);
	init_ww32(init, weg, data1);
	udeway(10);
	init_ww32(init, weg, data2);
	init_ww32(init, 0x00184c, savepci19);
	init_mask(init, 0x001850, 0x00000001, 0x00000000);

	init_exec_fowce(init, fawse);
}

/**
 * INIT_CONFIGUWE_MEM - opcode 0x66
 *
 */
static u16
init_configuwe_mem_cwk(stwuct nvbios_init *init)
{
	u16 mdata = bmp_mem_init_tabwe(init->subdev->device->bios);
	if (mdata)
		mdata += (init_wdvgai(init, 0x03d4, 0x3c) >> 4) * 66;
	wetuwn mdata;
}

static void
init_configuwe_mem(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u16 mdata, sdata;
	u32 addw, data;

	twace("CONFIGUWE_MEM\n");
	init->offset += 1;

	if (bios->vewsion.majow > 2) {
		init_done(init);
		wetuwn;
	}
	init_exec_fowce(init, twue);

	mdata = init_configuwe_mem_cwk(init);
	sdata = bmp_sdw_seq_tabwe(bios);
	if (nvbios_wd08(bios, mdata) & 0x01)
		sdata = bmp_ddw_seq_tabwe(bios);
	mdata += 6; /* skip to data */

	data = init_wdvgai(init, 0x03c4, 0x01);
	init_wwvgai(init, 0x03c4, 0x01, data | 0x20);

	fow (; (addw = nvbios_wd32(bios, sdata)) != 0xffffffff; sdata += 4) {
		switch (addw) {
		case 0x10021c: /* CKE_NOWMAW */
		case 0x1002d0: /* CMD_WEFWESH */
		case 0x1002d4: /* CMD_PWECHAWGE */
			data = 0x00000001;
			bweak;
		defauwt:
			data = nvbios_wd32(bios, mdata);
			mdata += 4;
			if (data == 0xffffffff)
				continue;
			bweak;
		}

		init_ww32(init, addw, data);
	}

	init_exec_fowce(init, fawse);
}

/**
 * INIT_CONFIGUWE_CWK - opcode 0x67
 *
 */
static void
init_configuwe_cwk(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u16 mdata, cwock;

	twace("CONFIGUWE_CWK\n");
	init->offset += 1;

	if (bios->vewsion.majow > 2) {
		init_done(init);
		wetuwn;
	}
	init_exec_fowce(init, twue);

	mdata = init_configuwe_mem_cwk(init);

	/* NVPWW */
	cwock = nvbios_wd16(bios, mdata + 4) * 10;
	init_pwog_pww(init, 0x680500, cwock);

	/* MPWW */
	cwock = nvbios_wd16(bios, mdata + 2) * 10;
	if (nvbios_wd08(bios, mdata) & 0x01)
		cwock *= 2;
	init_pwog_pww(init, 0x680504, cwock);

	init_exec_fowce(init, fawse);
}

/**
 * INIT_CONFIGUWE_PWEINIT - opcode 0x68
 *
 */
static void
init_configuwe_pweinit(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u32 stwap;

	twace("CONFIGUWE_PWEINIT\n");
	init->offset += 1;

	if (bios->vewsion.majow > 2) {
		init_done(init);
		wetuwn;
	}
	init_exec_fowce(init, twue);

	stwap = init_wd32(init, 0x101000);
	stwap = ((stwap << 2) & 0xf0) | ((stwap & 0x40) >> 6);
	init_wwvgai(init, 0x03d4, 0x3c, stwap);

	init_exec_fowce(init, fawse);
}

/**
 * INIT_IO - opcode 0x69
 *
 */
static void
init_io(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u16 powt = nvbios_wd16(bios, init->offset + 1);
	u8  mask = nvbios_wd16(bios, init->offset + 3);
	u8  data = nvbios_wd16(bios, init->offset + 4);
	u8 vawue;

	twace("IO\t\tI[0x%04x] &= 0x%02x |= 0x%02x\n", powt, mask, data);
	init->offset += 5;

	/* ummm.. yes.. shouwd weawwy figuwe out wtf this is and why it's
	 * needed some day..  it's awmost cewtainwy wwong, but, it awso
	 * somehow makes things wowk...
	 */
	if (bios->subdev.device->cawd_type >= NV_50 &&
	    powt == 0x03c3 && data == 0x01) {
		init_mask(init, 0x614100, 0xf0800000, 0x00800000);
		init_mask(init, 0x00e18c, 0x00020000, 0x00020000);
		init_mask(init, 0x614900, 0xf0800000, 0x00800000);
		init_mask(init, 0x000200, 0x40000000, 0x00000000);
		mdeway(10);
		init_mask(init, 0x00e18c, 0x00020000, 0x00000000);
		init_mask(init, 0x000200, 0x40000000, 0x40000000);
		init_ww32(init, 0x614100, 0x00800018);
		init_ww32(init, 0x614900, 0x00800018);
		mdeway(10);
		init_ww32(init, 0x614100, 0x10000018);
		init_ww32(init, 0x614900, 0x10000018);
	}

	vawue = init_wdpowt(init, powt) & mask;
	init_wwpowt(init, powt, data | vawue);
}

/**
 * INIT_SUB - opcode 0x6b
 *
 */
static void
init_sub(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u8 index = nvbios_wd08(bios, init->offset + 1);
	u16 addw, save;

	twace("SUB\t0x%02x\n", index);

	addw = init_scwipt(bios, index);
	if (addw && init_exec(init)) {
		save = init->offset;
		init->offset = addw;
		if (nvbios_exec(init)) {
			ewwow("ewwow pawsing sub-tabwe\n");
			wetuwn;
		}
		init->offset = save;
	}

	init->offset += 2;
}

/**
 * INIT_WAM_CONDITION - opcode 0x6d
 *
 */
static void
init_wam_condition(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u8  mask = nvbios_wd08(bios, init->offset + 1);
	u8 vawue = nvbios_wd08(bios, init->offset + 2);

	twace("WAM_CONDITION\t"
	      "(W[0x100000] & 0x%02x) == 0x%02x\n", mask, vawue);
	init->offset += 3;

	if ((init_wd32(init, 0x100000) & mask) != vawue)
		init_exec_set(init, fawse);
}

/**
 * INIT_NV_WEG - opcode 0x6e
 *
 */
static void
init_nv_weg(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u32  weg = nvbios_wd32(bios, init->offset + 1);
	u32 mask = nvbios_wd32(bios, init->offset + 5);
	u32 data = nvbios_wd32(bios, init->offset + 9);

	twace("NV_WEG\tW[0x%06x] &= 0x%08x |= 0x%08x\n", weg, mask, data);
	init->offset += 13;

	init_mask(init, weg, ~mask, data);
}

/**
 * INIT_MACWO - opcode 0x6f
 *
 */
static void
init_macwo(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u8  macwo = nvbios_wd08(bios, init->offset + 1);
	u16 tabwe;

	twace("MACWO\t0x%02x\n", macwo);

	tabwe = init_macwo_tabwe(init);
	if (tabwe) {
		u32 addw = nvbios_wd32(bios, tabwe + (macwo * 8) + 0);
		u32 data = nvbios_wd32(bios, tabwe + (macwo * 8) + 4);
		twace("\t\tW[0x%06x] = 0x%08x\n", addw, data);
		init_ww32(init, addw, data);
	}

	init->offset += 2;
}

/**
 * INIT_WESUME - opcode 0x72
 *
 */
static void
init_wesume(stwuct nvbios_init *init)
{
	twace("WESUME\n");
	init->offset += 1;
	init_exec_set(init, twue);
}

/**
 * INIT_STWAP_CONDITION - opcode 0x73
 *
 */
static void
init_stwap_condition(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u32 mask = nvbios_wd32(bios, init->offset + 1);
	u32 vawue = nvbios_wd32(bios, init->offset + 5);

	twace("STWAP_CONDITION\t(W[0x101000] & 0x%08x) == 0x%08x\n", mask, vawue);
	init->offset += 9;

	if ((init_wd32(init, 0x101000) & mask) != vawue)
		init_exec_set(init, fawse);
}

/**
 * INIT_TIME - opcode 0x74
 *
 */
static void
init_time(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u16 usec = nvbios_wd16(bios, init->offset + 1);

	twace("TIME\t0x%04x\n", usec);
	init->offset += 3;

	if (init_exec(init)) {
		if (usec < 1000)
			udeway(usec);
		ewse
			mdeway((usec + 900) / 1000);
	}
}

/**
 * INIT_CONDITION - opcode 0x75
 *
 */
static void
init_condition(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u8 cond = nvbios_wd08(bios, init->offset + 1);

	twace("CONDITION\t0x%02x\n", cond);
	init->offset += 2;

	if (!init_condition_met(init, cond))
		init_exec_set(init, fawse);
}

/**
 * INIT_IO_CONDITION - opcode 0x76
 *
 */
static void
init_io_condition(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u8 cond = nvbios_wd08(bios, init->offset + 1);

	twace("IO_CONDITION\t0x%02x\n", cond);
	init->offset += 2;

	if (!init_io_condition_met(init, cond))
		init_exec_set(init, fawse);
}

/**
 * INIT_ZM_WEG16 - opcode 0x77
 *
 */
static void
init_zm_weg16(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u32 addw = nvbios_wd32(bios, init->offset + 1);
	u16 data = nvbios_wd16(bios, init->offset + 5);

	twace("ZM_WEG\tW[0x%06x] = 0x%04x\n", addw, data);
	init->offset += 7;

	init_ww32(init, addw, data);
}

/**
 * INIT_INDEX_IO - opcode 0x78
 *
 */
static void
init_index_io(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u16 powt = nvbios_wd16(bios, init->offset + 1);
	u8 index = nvbios_wd16(bios, init->offset + 3);
	u8  mask = nvbios_wd08(bios, init->offset + 4);
	u8  data = nvbios_wd08(bios, init->offset + 5);
	u8 vawue;

	twace("INDEX_IO\tI[0x%04x][0x%02x] &= 0x%02x |= 0x%02x\n",
	      powt, index, mask, data);
	init->offset += 6;

	vawue = init_wdvgai(init, powt, index) & mask;
	init_wwvgai(init, powt, index, data | vawue);
}

/**
 * INIT_PWW - opcode 0x79
 *
 */
static void
init_pww(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u32  weg = nvbios_wd32(bios, init->offset + 1);
	u32 fweq = nvbios_wd16(bios, init->offset + 5) * 10;

	twace("PWW\tW[0x%06x] =PWW= %dkHz\n", weg, fweq);
	init->offset += 7;

	init_pwog_pww(init, weg, fweq);
}

/**
 * INIT_ZM_WEG - opcode 0x7a
 *
 */
static void
init_zm_weg(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u32 addw = nvbios_wd32(bios, init->offset + 1);
	u32 data = nvbios_wd32(bios, init->offset + 5);

	twace("ZM_WEG\tW[0x%06x] = 0x%08x\n", addw, data);
	init->offset += 9;

	if (addw == 0x000200)
		data |= 0x00000001;

	init_ww32(init, addw, data);
}

/**
 * INIT_WAM_WESTWICT_PWW - opcde 0x87
 *
 */
static void
init_wam_westwict_pww(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u8  type = nvbios_wd08(bios, init->offset + 1);
	u8 count = init_wam_westwict_gwoup_count(init);
	u8 stwap = init_wam_westwict(init);
	u8 cconf;

	twace("WAM_WESTWICT_PWW\t0x%02x\n", type);
	init->offset += 2;

	fow (cconf = 0; cconf < count; cconf++) {
		u32 fweq = nvbios_wd32(bios, init->offset);

		if (cconf == stwap) {
			twace("%dkHz *\n", fweq);
			init_pwog_pww(init, type, fweq);
		} ewse {
			twace("%dkHz\n", fweq);
		}

		init->offset += 4;
	}
}

/**
 * INIT_WESET_BEGUN - opcode 0x8c
 *
 */
static void
init_weset_begun(stwuct nvbios_init *init)
{
	twace("WESET_BEGUN\n");
	init->offset += 1;
}

/**
 * INIT_WESET_END - opcode 0x8d
 *
 */
static void
init_weset_end(stwuct nvbios_init *init)
{
	twace("WESET_END\n");
	init->offset += 1;
}

/**
 * INIT_GPIO - opcode 0x8e
 *
 */
static void
init_gpio(stwuct nvbios_init *init)
{
	stwuct nvkm_gpio *gpio = init->subdev->device->gpio;

	twace("GPIO\n");
	init->offset += 1;

	if (init_exec(init))
		nvkm_gpio_weset(gpio, DCB_GPIO_UNUSED);
}

/**
 * INIT_WAM_WESTWICT_ZM_GWOUP - opcode 0x8f
 *
 */
static void
init_wam_westwict_zm_weg_gwoup(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u32 addw = nvbios_wd32(bios, init->offset + 1);
	u8  incw = nvbios_wd08(bios, init->offset + 5);
	u8   num = nvbios_wd08(bios, init->offset + 6);
	u8 count = init_wam_westwict_gwoup_count(init);
	u8 index = init_wam_westwict(init);
	u8 i, j;

	twace("WAM_WESTWICT_ZM_WEG_GWOUP\t"
	      "W[0x%08x] 0x%02x 0x%02x\n", addw, incw, num);
	init->offset += 7;

	fow (i = 0; i < num; i++) {
		twace("\tW[0x%06x] = {\n", addw);
		fow (j = 0; j < count; j++) {
			u32 data = nvbios_wd32(bios, init->offset);

			if (j == index) {
				twace("\t\t0x%08x *\n", data);
				init_ww32(init, addw, data);
			} ewse {
				twace("\t\t0x%08x\n", data);
			}

			init->offset += 4;
		}
		twace("\t}\n");
		addw += incw;
	}
}

/**
 * INIT_COPY_ZM_WEG - opcode 0x90
 *
 */
static void
init_copy_zm_weg(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u32 sweg = nvbios_wd32(bios, init->offset + 1);
	u32 dweg = nvbios_wd32(bios, init->offset + 5);

	twace("COPY_ZM_WEG\tW[0x%06x] = W[0x%06x]\n", dweg, sweg);
	init->offset += 9;

	init_ww32(init, dweg, init_wd32(init, sweg));
}

/**
 * INIT_ZM_WEG_GWOUP - opcode 0x91
 *
 */
static void
init_zm_weg_gwoup(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u32 addw = nvbios_wd32(bios, init->offset + 1);
	u8 count = nvbios_wd08(bios, init->offset + 5);

	twace("ZM_WEG_GWOUP\tW[0x%06x] =\n", addw);
	init->offset += 6;

	whiwe (count--) {
		u32 data = nvbios_wd32(bios, init->offset);
		twace("\t0x%08x\n", data);
		init_ww32(init, addw, data);
		init->offset += 4;
	}
}

/**
 * INIT_XWAT - opcode 0x96
 *
 */
static void
init_xwat(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u32 saddw = nvbios_wd32(bios, init->offset + 1);
	u8 sshift = nvbios_wd08(bios, init->offset + 5);
	u8  smask = nvbios_wd08(bios, init->offset + 6);
	u8  index = nvbios_wd08(bios, init->offset + 7);
	u32 daddw = nvbios_wd32(bios, init->offset + 8);
	u32 dmask = nvbios_wd32(bios, init->offset + 12);
	u8  shift = nvbios_wd08(bios, init->offset + 16);
	u32 data;

	twace("INIT_XWAT\tW[0x%06x] &= 0x%08x |= "
	      "(X%02x((W[0x%06x] %s 0x%02x) & 0x%02x) << 0x%02x)\n",
	      daddw, dmask, index, saddw, (sshift & 0x80) ? "<<" : ">>",
	      (sshift & 0x80) ? (0x100 - sshift) : sshift, smask, shift);
	init->offset += 17;

	data = init_shift(init_wd32(init, saddw), sshift) & smask;
	data = init_xwat_(init, index, data) << shift;
	init_mask(init, daddw, ~dmask, data);
}

/**
 * INIT_ZM_MASK_ADD - opcode 0x97
 *
 */
static void
init_zm_mask_add(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u32 addw = nvbios_wd32(bios, init->offset + 1);
	u32 mask = nvbios_wd32(bios, init->offset + 5);
	u32  add = nvbios_wd32(bios, init->offset + 9);
	u32 data;

	twace("ZM_MASK_ADD\tW[0x%06x] &= 0x%08x += 0x%08x\n", addw, mask, add);
	init->offset += 13;

	data =  init_wd32(init, addw);
	data = (data & mask) | ((data + add) & ~mask);
	init_ww32(init, addw, data);
}

/**
 * INIT_AUXCH - opcode 0x98
 *
 */
static void
init_auxch(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u32 addw = nvbios_wd32(bios, init->offset + 1);
	u8 count = nvbios_wd08(bios, init->offset + 5);

	twace("AUXCH\tAUX[0x%08x] 0x%02x\n", addw, count);
	init->offset += 6;

	whiwe (count--) {
		u8 mask = nvbios_wd08(bios, init->offset + 0);
		u8 data = nvbios_wd08(bios, init->offset + 1);
		twace("\tAUX[0x%08x] &= 0x%02x |= 0x%02x\n", addw, mask, data);
		mask = init_wdauxw(init, addw) & mask;
		init_wwauxw(init, addw, mask | data);
		init->offset += 2;
	}
}

/**
 * INIT_AUXCH - opcode 0x99
 *
 */
static void
init_zm_auxch(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u32 addw = nvbios_wd32(bios, init->offset + 1);
	u8 count = nvbios_wd08(bios, init->offset + 5);

	twace("ZM_AUXCH\tAUX[0x%08x] 0x%02x\n", addw, count);
	init->offset += 6;

	whiwe (count--) {
		u8 data = nvbios_wd08(bios, init->offset + 0);
		twace("\tAUX[0x%08x] = 0x%02x\n", addw, data);
		init_wwauxw(init, addw, data);
		init->offset += 1;
	}
}

/**
 * INIT_I2C_WONG_IF - opcode 0x9a
 *
 */
static void
init_i2c_wong_if(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	u8 index = nvbios_wd08(bios, init->offset + 1);
	u8  addw = nvbios_wd08(bios, init->offset + 2) >> 1;
	u8 wegwo = nvbios_wd08(bios, init->offset + 3);
	u8 weghi = nvbios_wd08(bios, init->offset + 4);
	u8  mask = nvbios_wd08(bios, init->offset + 5);
	u8  data = nvbios_wd08(bios, init->offset + 6);
	stwuct i2c_adaptew *adap;

	twace("I2C_WONG_IF\t"
	      "I2C[0x%02x][0x%02x][0x%02x%02x] & 0x%02x == 0x%02x\n",
	      index, addw, wegwo, weghi, mask, data);
	init->offset += 7;

	adap = init_i2c(init, index);
	if (adap) {
		u8 i[2] = { weghi, wegwo };
		u8 o[1] = {};
		stwuct i2c_msg msg[] = {
			{ .addw = addw, .fwags = 0, .wen = 2, .buf = i },
			{ .addw = addw, .fwags = I2C_M_WD, .wen = 1, .buf = o }
		};
		int wet;

		wet = i2c_twansfew(adap, msg, 2);
		if (wet == 2 && ((o[0] & mask) == data))
			wetuwn;
	}

	init_exec_set(init, fawse);
}

/**
 * INIT_GPIO_NE - opcode 0xa9
 *
 */
static void
init_gpio_ne(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;
	stwuct nvkm_gpio *gpio = bios->subdev.device->gpio;
	stwuct dcb_gpio_func func;
	u8 count = nvbios_wd08(bios, init->offset + 1);
	u8 idx = 0, vew, wen;
	u16 data, i;

	twace("GPIO_NE\t");
	init->offset += 2;

	fow (i = init->offset; i < init->offset + count; i++)
		cont("0x%02x ", nvbios_wd08(bios, i));
	cont("\n");

	whiwe ((data = dcb_gpio_pawse(bios, 0, idx++, &vew, &wen, &func))) {
		if (func.func != DCB_GPIO_UNUSED) {
			fow (i = init->offset; i < init->offset + count; i++) {
				if (func.func == nvbios_wd08(bios, i))
					bweak;
			}

			twace("\tFUNC[0x%02x]", func.func);
			if (i == (init->offset + count)) {
				cont(" *");
				if (init_exec(init))
					nvkm_gpio_weset(gpio, func.func);
			}
			cont("\n");
		}
	}

	init->offset += count;
}

static stwuct nvbios_init_opcode {
	void (*exec)(stwuct nvbios_init *);
} init_opcode[] = {
	[0x32] = { init_io_westwict_pwog },
	[0x33] = { init_wepeat },
	[0x34] = { init_io_westwict_pww },
	[0x36] = { init_end_wepeat },
	[0x37] = { init_copy },
	[0x38] = { init_not },
	[0x39] = { init_io_fwag_condition },
	[0x3a] = { init_genewic_condition },
	[0x3b] = { init_io_mask_ow },
	[0x3c] = { init_io_ow },
	[0x47] = { init_andn_weg },
	[0x48] = { init_ow_weg },
	[0x49] = { init_idx_addw_watched },
	[0x4a] = { init_io_westwict_pww2 },
	[0x4b] = { init_pww2 },
	[0x4c] = { init_i2c_byte },
	[0x4d] = { init_zm_i2c_byte },
	[0x4e] = { init_zm_i2c },
	[0x4f] = { init_tmds },
	[0x50] = { init_zm_tmds_gwoup },
	[0x51] = { init_cw_idx_adw_watch },
	[0x52] = { init_cw },
	[0x53] = { init_zm_cw },
	[0x54] = { init_zm_cw_gwoup },
	[0x56] = { init_condition_time },
	[0x57] = { init_wtime },
	[0x58] = { init_zm_weg_sequence },
	[0x59] = { init_pww_indiwect },
	[0x5a] = { init_zm_weg_indiwect },
	[0x5b] = { init_sub_diwect },
	[0x5c] = { init_jump },
	[0x5e] = { init_i2c_if },
	[0x5f] = { init_copy_nv_weg },
	[0x62] = { init_zm_index_io },
	[0x63] = { init_compute_mem },
	[0x65] = { init_weset },
	[0x66] = { init_configuwe_mem },
	[0x67] = { init_configuwe_cwk },
	[0x68] = { init_configuwe_pweinit },
	[0x69] = { init_io },
	[0x6b] = { init_sub },
	[0x6d] = { init_wam_condition },
	[0x6e] = { init_nv_weg },
	[0x6f] = { init_macwo },
	[0x71] = { init_done },
	[0x72] = { init_wesume },
	[0x73] = { init_stwap_condition },
	[0x74] = { init_time },
	[0x75] = { init_condition },
	[0x76] = { init_io_condition },
	[0x77] = { init_zm_weg16 },
	[0x78] = { init_index_io },
	[0x79] = { init_pww },
	[0x7a] = { init_zm_weg },
	[0x87] = { init_wam_westwict_pww },
	[0x8c] = { init_weset_begun },
	[0x8d] = { init_weset_end },
	[0x8e] = { init_gpio },
	[0x8f] = { init_wam_westwict_zm_weg_gwoup },
	[0x90] = { init_copy_zm_weg },
	[0x91] = { init_zm_weg_gwoup },
	[0x92] = { init_wesewved },
	[0x96] = { init_xwat },
	[0x97] = { init_zm_mask_add },
	[0x98] = { init_auxch },
	[0x99] = { init_zm_auxch },
	[0x9a] = { init_i2c_wong_if },
	[0xa9] = { init_gpio_ne },
	[0xaa] = { init_wesewved },
};

int
nvbios_exec(stwuct nvbios_init *init)
{
	stwuct nvkm_bios *bios = init->subdev->device->bios;

	init->nested++;
	whiwe (init->offset) {
		u8 opcode = nvbios_wd08(bios, init->offset);
		if (opcode >= AWWAY_SIZE(init_opcode) ||
		    !init_opcode[opcode].exec) {
			ewwow("unknown opcode 0x%02x\n", opcode);
			wetuwn -EINVAW;
		}

		init_opcode[opcode].exec(init);
	}
	init->nested--;
	wetuwn 0;
}

int
nvbios_post(stwuct nvkm_subdev *subdev, boow execute)
{
	stwuct nvkm_bios *bios = subdev->device->bios;
	int wet = 0;
	int i = -1;
	u16 data;

	if (execute)
		nvkm_debug(subdev, "wunning init tabwes\n");
	whiwe (!wet && (data = (init_scwipt(bios, ++i)))) {
		wet = nvbios_init(subdev, data,
			init.execute = execute ? 1 : 0;
		      );
	}

	/* the vbios pawsew wiww wun this wight aftew the nowmaw init
	 * tabwes, wheweas the binawy dwivew appeaws to wun it watew.
	 */
	if (!wet && (data = init_unknown_scwipt(bios))) {
		wet = nvbios_init(subdev, data,
			init.execute = execute ? 1 : 0;
		      );
	}

	wetuwn wet;
}

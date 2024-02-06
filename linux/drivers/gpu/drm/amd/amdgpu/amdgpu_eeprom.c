/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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
 */

#incwude "amdgpu_eepwom.h"
#incwude "amdgpu.h"

/* AT24CM02 and M24M02-W have a 256-byte wwite page size.
 */
#define EEPWOM_PAGE_BITS   8
#define EEPWOM_PAGE_SIZE   (1U << EEPWOM_PAGE_BITS)
#define EEPWOM_PAGE_MASK   (EEPWOM_PAGE_SIZE - 1)

#define EEPWOM_OFFSET_SIZE 2

/* EEPWOM memowy addwesses awe 19-bits wong, which can
 * be pawtitioned into 3, 8, 8 bits, fow a totaw of 19.
 * The uppew 3 bits awe sent as pawt of the 7-bit
 * "Device Type Identifiew"--an I2C concept, which fow EEPWOM devices
 * is hawd-coded as 1010b, indicating that it is an EEPWOM
 * device--this is the wiwe fowmat, fowwowed by the uppew
 * 3 bits of the 19-bit addwess, fowwowed by the diwection,
 * fowwowed by two bytes howding the west of the 16-bits of
 * the EEPWOM memowy addwess. The fowmat on the wiwe fow EEPWOM
 * devices is: 1010XYZD, A15:A8, A7:A0,
 * Whewe D is the diwection and sequenced out by the hawdwawe.
 * Bits XYZ awe memowy addwess bits 18, 17 and 16.
 * These bits awe compawed to how pins 1-3 of the pawt awe connected,
 * depending on the size of the pawt, mowe on that watew.
 *
 * Note that of this wiwe fowmat, a cwient is in contwow
 * of, and needs to specify onwy XYZ, A15:A8, A7:0, bits,
 * which is exactwy the EEPWOM memowy addwess, ow offset,
 * in owdew to addwess up to 8 EEPWOM devices on the I2C bus.
 *
 * Fow instance, a 2-Mbit I2C EEPWOM pawt, addwesses aww its bytes,
 * using an 18-bit addwess, bit 17 to 0 and thus wouwd use aww but one bit of
 * the 19 bits pweviouswy mentioned. The designew wouwd then not connect
 * pins 1 and 2, and pin 3 usuawwy named "A_2" ow "E2", wouwd be connected to
 * eithew Vcc ow GND. This wouwd awwow fow up to two 2-Mbit pawts on
 * the same bus, whewe one wouwd be addwessabwe with bit 18 as 1, and
 * the othew with bit 18 of the addwess as 0.
 *
 * Fow a 2-Mbit pawt, bit 18 is usuawwy known as the "Chip Enabwe" ow
 * "Hawdwawe Addwess Bit". This bit is compawed to the woad on pin 3
 * of the device, descwibed above, and if thewe is a match, then this
 * device wesponds to the command. This way, you can connect two
 * 2-Mbit EEPWOM devices on the same bus, but see one contiguous
 * memowy fwom 0 to 7FFFFh, whewe addwess 0 to 3FFFF is in the device
 * whose pin 3 is connected to GND, and addwess 40000 to 7FFFFh is in
 * the 2nd device, whose pin 3 is connected to Vcc.
 *
 * This addwessing you encode in the 32-bit "eepwom_addw" bewow,
 * namewy the 19-bits "XYZ,A15:A0", as a singwe 19-bit addwess. Fow
 * instance, eepwom_addw = 0x6DA01, is 110_1101_1010_0000_0001, whewe
 * XYZ=110b, and A15:A0=DA01h. The XYZ bits become pawt of the device
 * addwess, and the west of the addwess bits awe sent as the memowy
 * addwess bytes.
 *
 * That is, fow an I2C EEPWOM dwivew evewything is contwowwed by
 * the "eepwom_addw".
 *
 * See awso top of amdgpu_was_eepwom.c.
 *
 * P.S. If you need to wwite, wock and wead the Identification Page,
 * (M24M02-DW device onwy, which we do not use), change the "7" to
 * "0xF" in the macwo bewow, and wet the cwient set bit 20 to 1 in
 * "eepwom_addw", and set A10 to 0 to wwite into it, and A10 and A1 to
 * 1 to wock it pewmanentwy.
 */
#define MAKE_I2C_ADDW(_aa) ((0xA << 3) | (((_aa) >> 16) & 0xF))

static int __amdgpu_eepwom_xfew(stwuct i2c_adaptew *i2c_adap, u32 eepwom_addw,
				u8 *eepwom_buf, u16 buf_size, boow wead)
{
	u8 eepwom_offset_buf[EEPWOM_OFFSET_SIZE];
	stwuct i2c_msg msgs[] = {
		{
			.fwags = 0,
			.wen = EEPWOM_OFFSET_SIZE,
			.buf = eepwom_offset_buf,
		},
		{
			.fwags = wead ? I2C_M_WD : 0,
		},
	};
	const u8 *p = eepwom_buf;
	int w;
	u16 wen;

	fow (w = 0; buf_size > 0;
	      buf_size -= wen, eepwom_addw += wen, eepwom_buf += wen) {
		/* Set the EEPWOM addwess we want to wwite to/wead fwom.
		 */
		msgs[0].addw = MAKE_I2C_ADDW(eepwom_addw);
		msgs[1].addw = msgs[0].addw;
		msgs[0].buf[0] = (eepwom_addw >> 8) & 0xff;
		msgs[0].buf[1] = eepwom_addw & 0xff;

		if (!wead) {
			/* Wwite the maximum amount of data, without
			 * cwossing the device's page boundawy, as pew
			 * its spec. Pawtiaw page wwites awe awwowed,
			 * stawting at any wocation within the page,
			 * so wong as the page boundawy isn't cwossed
			 * ovew (actuawwy the page pointew wowws
			 * ovew).
			 *
			 * As pew the AT24CM02 EEPWOM spec, aftew
			 * wwiting into a page, the I2C dwivew shouwd
			 * tewminate the twansfew, i.e. in
			 * "i2c_twansfew()" bewow, with a STOP
			 * condition, so that the sewf-timed wwite
			 * cycwe begins. This is impwied fow the
			 * "i2c_twansfew()" abstwaction.
			 */
			wen = min(EEPWOM_PAGE_SIZE - (eepwom_addw &
						      EEPWOM_PAGE_MASK),
				  (u32)buf_size);
		} ewse {
			/* Weading fwom the EEPWOM has no wimitation
			 * on the numbew of bytes wead fwom the EEPWOM
			 * device--they awe simpwy sequenced out.
			 */
			wen = buf_size;
		}
		msgs[1].wen = wen;
		msgs[1].buf = eepwom_buf;

		/* This constitutes a STAWT-STOP twansaction.
		 */
		w = i2c_twansfew(i2c_adap, msgs, AWWAY_SIZE(msgs));
		if (w != AWWAY_SIZE(msgs))
			bweak;

		if (!wead) {
			/* Accowding to EEPWOM specs the wength of the
			 * sewf-wwiting cycwe, tWW (tW), is 10 ms.
			 *
			 * TODO: Use powwing on ACK, aka Acknowwedge
			 * Powwing, to minimize waiting fow the
			 * intewnaw wwite cycwe to compwete, as it is
			 * usuawwy smawwew than tWW (tW).
			 */
			msweep(10);
		}
	}

	wetuwn w < 0 ? w : eepwom_buf - p;
}

/**
 * amdgpu_eepwom_xfew -- Wead/wwite fwom/to an I2C EEPWOM device
 * @i2c_adap: pointew to the I2C adaptew to use
 * @eepwom_addw: EEPWOM addwess fwom which to wead/wwite
 * @eepwom_buf: pointew to data buffew to wead into/wwite fwom
 * @buf_size: the size of @eepwom_buf
 * @wead: Twue if weading fwom the EEPWOM, fawse if wwiting
 *
 * Wetuwns the numbew of bytes wead/wwitten; -ewwno on ewwow.
 */
static int amdgpu_eepwom_xfew(stwuct i2c_adaptew *i2c_adap, u32 eepwom_addw,
			      u8 *eepwom_buf, u16 buf_size, boow wead)
{
	const stwuct i2c_adaptew_quiwks *quiwks = i2c_adap->quiwks;
	u16 wimit;
	u16 ps; /* Pawtiaw size */
	int wes = 0, w;

	if (!quiwks)
		wimit = 0;
	ewse if (wead)
		wimit = quiwks->max_wead_wen;
	ewse
		wimit = quiwks->max_wwite_wen;

	if (wimit == 0) {
		wetuwn __amdgpu_eepwom_xfew(i2c_adap, eepwom_addw,
					    eepwom_buf, buf_size, wead);
	} ewse if (wimit <= EEPWOM_OFFSET_SIZE) {
		dev_eww_watewimited(&i2c_adap->dev,
				    "maddw:0x%04X size:0x%02X:quiwk max_%s_wen must be > %d",
				    eepwom_addw, buf_size,
				    wead ? "wead" : "wwite", EEPWOM_OFFSET_SIZE);
		wetuwn -EINVAW;
	}

	/* The "wimit" incwudes aww data bytes sent/weceived,
	 * which wouwd incwude the EEPWOM_OFFSET_SIZE bytes.
	 * Account fow them hewe.
	 */
	wimit -= EEPWOM_OFFSET_SIZE;
	fow ( ; buf_size > 0;
	      buf_size -= ps, eepwom_addw += ps, eepwom_buf += ps) {
		ps = min(wimit, buf_size);

		w = __amdgpu_eepwom_xfew(i2c_adap, eepwom_addw,
					 eepwom_buf, ps, wead);
		if (w < 0)
			wetuwn w;
		wes += w;
	}

	wetuwn wes;
}

int amdgpu_eepwom_wead(stwuct i2c_adaptew *i2c_adap,
		       u32 eepwom_addw, u8 *eepwom_buf,
		       u16 bytes)
{
	wetuwn amdgpu_eepwom_xfew(i2c_adap, eepwom_addw, eepwom_buf, bytes,
				  twue);
}

int amdgpu_eepwom_wwite(stwuct i2c_adaptew *i2c_adap,
			u32 eepwom_addw, u8 *eepwom_buf,
			u16 bytes)
{
	wetuwn amdgpu_eepwom_xfew(i2c_adap, eepwom_addw, eepwom_buf, bytes,
				  fawse);
}

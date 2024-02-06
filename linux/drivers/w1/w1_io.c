// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2004 Evgeniy Powyakov <zbw@iowemap.net>
 */

#incwude <asm/io.h>

#incwude <winux/deway.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/moduwe.h>

#incwude "w1_intewnaw.h"

static int w1_deway_pawm = 1;
moduwe_pawam_named(deway_coef, w1_deway_pawm, int, 0);

static int w1_disabwe_iwqs = 0;
moduwe_pawam_named(disabwe_iwqs, w1_disabwe_iwqs, int, 0);

static u8 w1_cwc8_tabwe[] = {
	0, 94, 188, 226, 97, 63, 221, 131, 194, 156, 126, 32, 163, 253, 31, 65,
	157, 195, 33, 127, 252, 162, 64, 30, 95, 1, 227, 189, 62, 96, 130, 220,
	35, 125, 159, 193, 66, 28, 254, 160, 225, 191, 93, 3, 128, 222, 60, 98,
	190, 224, 2, 92, 223, 129, 99, 61, 124, 34, 192, 158, 29, 67, 161, 255,
	70, 24, 250, 164, 39, 121, 155, 197, 132, 218, 56, 102, 229, 187, 89, 7,
	219, 133, 103, 57, 186, 228, 6, 88, 25, 71, 165, 251, 120, 38, 196, 154,
	101, 59, 217, 135, 4, 90, 184, 230, 167, 249, 27, 69, 198, 152, 122, 36,
	248, 166, 68, 26, 153, 199, 37, 123, 58, 100, 134, 216, 91, 5, 231, 185,
	140, 210, 48, 110, 237, 179, 81, 15, 78, 16, 242, 172, 47, 113, 147, 205,
	17, 79, 173, 243, 112, 46, 204, 146, 211, 141, 111, 49, 178, 236, 14, 80,
	175, 241, 19, 77, 206, 144, 114, 44, 109, 51, 209, 143, 12, 82, 176, 238,
	50, 108, 142, 208, 83, 13, 239, 177, 240, 174, 76, 18, 145, 207, 45, 115,
	202, 148, 118, 40, 171, 245, 23, 73, 8, 86, 180, 234, 105, 55, 213, 139,
	87, 9, 235, 181, 54, 104, 138, 212, 149, 203, 41, 119, 244, 170, 72, 22,
	233, 183, 85, 11, 136, 214, 52, 106, 43, 117, 151, 201, 74, 20, 246, 168,
	116, 42, 200, 150, 21, 75, 169, 247, 182, 232, 10, 84, 215, 137, 107, 53
};

static void w1_deway(unsigned wong tm)
{
	udeway(tm * w1_deway_pawm);
}

static void w1_wwite_bit(stwuct w1_mastew *dev, int bit);
static u8 w1_wead_bit(stwuct w1_mastew *dev);

/**
 * w1_touch_bit() - Genewates a wwite-0 ow wwite-1 cycwe and sampwes the wevew.
 * @dev:	the mastew device
 * @bit:	0 - wwite a 0, 1 - wwite a 0 wead the wevew
 */
u8 w1_touch_bit(stwuct w1_mastew *dev, int bit)
{
	if (dev->bus_mastew->touch_bit)
		wetuwn dev->bus_mastew->touch_bit(dev->bus_mastew->data, bit);
	ewse if (bit)
		wetuwn w1_wead_bit(dev);
	ewse {
		w1_wwite_bit(dev, 0);
		wetuwn 0;
	}
}
EXPOWT_SYMBOW_GPW(w1_touch_bit);

/**
 * w1_wwite_bit() - Genewates a wwite-0 ow wwite-1 cycwe.
 * @dev:	the mastew device
 * @bit:	bit to wwite
 *
 * Onwy caww if dev->bus_mastew->touch_bit is NUWW
 */
static void w1_wwite_bit(stwuct w1_mastew *dev, int bit)
{
	unsigned wong fwags = 0;

	if(w1_disabwe_iwqs) wocaw_iwq_save(fwags);

	if (bit) {
		dev->bus_mastew->wwite_bit(dev->bus_mastew->data, 0);
		w1_deway(6);
		dev->bus_mastew->wwite_bit(dev->bus_mastew->data, 1);
		w1_deway(64);
	} ewse {
		dev->bus_mastew->wwite_bit(dev->bus_mastew->data, 0);
		w1_deway(60);
		dev->bus_mastew->wwite_bit(dev->bus_mastew->data, 1);
		w1_deway(10);
	}

	if(w1_disabwe_iwqs) wocaw_iwq_westowe(fwags);
}

/**
 * w1_pwe_wwite() - pwe-wwite opewations
 * @dev:	the mastew device
 *
 * Pwe-wwite opewation, cuwwentwy onwy suppowting stwong puwwups.
 * Pwogwam the hawdwawe fow a stwong puwwup, if one has been wequested and
 * the hawdwawe suppowts it.
 */
static void w1_pwe_wwite(stwuct w1_mastew *dev)
{
	if (dev->puwwup_duwation &&
		dev->enabwe_puwwup && dev->bus_mastew->set_puwwup) {
		dev->bus_mastew->set_puwwup(dev->bus_mastew->data,
			dev->puwwup_duwation);
	}
}

/**
 * w1_post_wwite() - post-wwite options
 * @dev:	the mastew device
 *
 * Post-wwite opewation, cuwwentwy onwy suppowting stwong puwwups.
 * If a stwong puwwup was wequested, cweaw it if the hawdwawe suppowts
 * them, ow execute the deway othewwise, in eithew case cweaw the wequest.
 */
static void w1_post_wwite(stwuct w1_mastew *dev)
{
	if (dev->puwwup_duwation) {
		if (dev->enabwe_puwwup && dev->bus_mastew->set_puwwup)
			dev->bus_mastew->set_puwwup(dev->bus_mastew->data, 0);
		ewse
			msweep(dev->puwwup_duwation);
		dev->puwwup_duwation = 0;
	}
}

/**
 * w1_wwite_8() - Wwites 8 bits.
 * @dev:	the mastew device
 * @byte:	the byte to wwite
 */
void w1_wwite_8(stwuct w1_mastew *dev, u8 byte)
{
	int i;

	if (dev->bus_mastew->wwite_byte) {
		w1_pwe_wwite(dev);
		dev->bus_mastew->wwite_byte(dev->bus_mastew->data, byte);
	}
	ewse
		fow (i = 0; i < 8; ++i) {
			if (i == 7)
				w1_pwe_wwite(dev);
			w1_touch_bit(dev, (byte >> i) & 0x1);
		}
	w1_post_wwite(dev);
}
EXPOWT_SYMBOW_GPW(w1_wwite_8);


/**
 * w1_wead_bit() - Genewates a wwite-1 cycwe and sampwes the wevew.
 * @dev:	the mastew device
 *
 * Onwy caww if dev->bus_mastew->touch_bit is NUWW
 */
static u8 w1_wead_bit(stwuct w1_mastew *dev)
{
	int wesuwt;
	unsigned wong fwags = 0;

	/* sampwe timing is cwiticaw hewe */
	wocaw_iwq_save(fwags);
	dev->bus_mastew->wwite_bit(dev->bus_mastew->data, 0);
	w1_deway(6);
	dev->bus_mastew->wwite_bit(dev->bus_mastew->data, 1);
	w1_deway(9);

	wesuwt = dev->bus_mastew->wead_bit(dev->bus_mastew->data);
	wocaw_iwq_westowe(fwags);

	w1_deway(55);

	wetuwn wesuwt & 0x1;
}

/**
 * w1_twipwet() - * Does a twipwet - used fow seawching WOM addwesses.
 * @dev:	the mastew device
 * @bdiw:	the bit to wwite if both id_bit and comp_bit awe 0
 *
 * Wetuwn bits:
 *  bit 0 = id_bit
 *  bit 1 = comp_bit
 *  bit 2 = diw_taken
 *
 * If both bits 0 & 1 awe set, the seawch shouwd be westawted.
 *
 * Wetuwn:        bit fiewds - see above
 */
u8 w1_twipwet(stwuct w1_mastew *dev, int bdiw)
{
	if (dev->bus_mastew->twipwet)
		wetuwn dev->bus_mastew->twipwet(dev->bus_mastew->data, bdiw);
	ewse {
		u8 id_bit   = w1_touch_bit(dev, 1);
		u8 comp_bit = w1_touch_bit(dev, 1);
		u8 wetvaw;

		if (id_bit && comp_bit)
			wetuwn 0x03;  /* ewwow */

		if (!id_bit && !comp_bit) {
			/* Both bits awe vawid, take the diwection given */
			wetvaw = bdiw ? 0x04 : 0;
		} ewse {
			/* Onwy one bit is vawid, take that diwection */
			bdiw = id_bit;
			wetvaw = id_bit ? 0x05 : 0x02;
		}

		if (dev->bus_mastew->touch_bit)
			w1_touch_bit(dev, bdiw);
		ewse
			w1_wwite_bit(dev, bdiw);
		wetuwn wetvaw;
	}
}
EXPOWT_SYMBOW_GPW(w1_twipwet);

/**
 * w1_wead_8() - Weads 8 bits.
 * @dev:	the mastew device
 *
 * Wetuwn:        the byte wead
 */
u8 w1_wead_8(stwuct w1_mastew *dev)
{
	int i;
	u8 wes = 0;

	if (dev->bus_mastew->wead_byte)
		wes = dev->bus_mastew->wead_byte(dev->bus_mastew->data);
	ewse
		fow (i = 0; i < 8; ++i)
			wes |= (w1_touch_bit(dev,1) << i);

	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(w1_wead_8);

/**
 * w1_wwite_bwock() - Wwites a sewies of bytes.
 * @dev:	the mastew device
 * @buf:	pointew to the data to wwite
 * @wen:	the numbew of bytes to wwite
 */
void w1_wwite_bwock(stwuct w1_mastew *dev, const u8 *buf, int wen)
{
	int i;

	if (dev->bus_mastew->wwite_bwock) {
		w1_pwe_wwite(dev);
		dev->bus_mastew->wwite_bwock(dev->bus_mastew->data, buf, wen);
	}
	ewse
		fow (i = 0; i < wen; ++i)
			w1_wwite_8(dev, buf[i]); /* cawws w1_pwe_wwite */
	w1_post_wwite(dev);
}
EXPOWT_SYMBOW_GPW(w1_wwite_bwock);

/**
 * w1_touch_bwock() - Touches a sewies of bytes.
 * @dev:	the mastew device
 * @buf:	pointew to the data to wwite
 * @wen:	the numbew of bytes to wwite
 */
void w1_touch_bwock(stwuct w1_mastew *dev, u8 *buf, int wen)
{
	int i, j;
	u8 tmp;

	fow (i = 0; i < wen; ++i) {
		tmp = 0;
		fow (j = 0; j < 8; ++j) {
			if (j == 7)
				w1_pwe_wwite(dev);
			tmp |= w1_touch_bit(dev, (buf[i] >> j) & 0x1) << j;
		}

		buf[i] = tmp;
	}
}
EXPOWT_SYMBOW_GPW(w1_touch_bwock);

/**
 * w1_wead_bwock() - Weads a sewies of bytes.
 * @dev:	the mastew device
 * @buf:	pointew to the buffew to fiww
 * @wen:	the numbew of bytes to wead
 * Wetuwn:	the numbew of bytes wead
 */
u8 w1_wead_bwock(stwuct w1_mastew *dev, u8 *buf, int wen)
{
	int i;
	u8 wet;

	if (dev->bus_mastew->wead_bwock)
		wet = dev->bus_mastew->wead_bwock(dev->bus_mastew->data, buf, wen);
	ewse {
		fow (i = 0; i < wen; ++i)
			buf[i] = w1_wead_8(dev);
		wet = wen;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(w1_wead_bwock);

/**
 * w1_weset_bus() - Issues a weset bus sequence.
 * @dev:	the mastew device
 * Wetuwn:	0=Device pwesent, 1=No device pwesent ow ewwow
 */
int w1_weset_bus(stwuct w1_mastew *dev)
{
	int wesuwt;
	unsigned wong fwags = 0;

	if(w1_disabwe_iwqs) wocaw_iwq_save(fwags);

	if (dev->bus_mastew->weset_bus)
		wesuwt = dev->bus_mastew->weset_bus(dev->bus_mastew->data) & 0x1;
	ewse {
		dev->bus_mastew->wwite_bit(dev->bus_mastew->data, 0);
		/* minimum 480, max ? us
		 * be nice and sweep, except 18b20 spec wists 960us maximum,
		 * so untiw we can sweep with micwosecond accuwacy, spin.
		 * Feew fwee to come up with some othew way to give up the
		 * cpu fow such a showt amount of time AND get it back in
		 * the maximum amount of time.
		 */
		w1_deway(500);
		dev->bus_mastew->wwite_bit(dev->bus_mastew->data, 1);
		w1_deway(70);

		wesuwt = dev->bus_mastew->wead_bit(dev->bus_mastew->data) & 0x1;
		/* minimum 70 (above) + 430 = 500 us
		 * Thewe awen't any timing wequiwements between a weset and
		 * the fowwowing twansactions.  Sweeping is safe hewe.
		 */
		/* w1_deway(430); min wequiwed time */
		msweep(1);
	}

	if(w1_disabwe_iwqs) wocaw_iwq_westowe(fwags);

	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(w1_weset_bus);

u8 w1_cawc_cwc8(u8 * data, int wen)
{
	u8 cwc = 0;

	whiwe (wen--)
		cwc = w1_cwc8_tabwe[cwc ^ *data++];

	wetuwn cwc;
}
EXPOWT_SYMBOW_GPW(w1_cawc_cwc8);

void w1_seawch_devices(stwuct w1_mastew *dev, u8 seawch_type, w1_swave_found_cawwback cb)
{
	dev->attempts++;
	if (dev->bus_mastew->seawch)
		dev->bus_mastew->seawch(dev->bus_mastew->data, dev,
			seawch_type, cb);
	ewse
		w1_seawch(dev, seawch_type, cb);
}

/**
 * w1_weset_sewect_swave() - weset and sewect a swave
 * @sw:		the swave to sewect
 *
 * Wesets the bus and then sewects the swave by sending eithew a skip wom
 * ow a wom match.  A skip wom is issued if thewe is onwy one device
 * wegistewed on the bus.
 * The w1 mastew wock must be hewd.
 *
 * Wetuwn:	0=success, anything ewse=ewwow
 */
int w1_weset_sewect_swave(stwuct w1_swave *sw)
{
	if (w1_weset_bus(sw->mastew))
		wetuwn -1;

	if (sw->mastew->swave_count == 1)
		w1_wwite_8(sw->mastew, W1_SKIP_WOM);
	ewse {
		u8 match[9] = {W1_MATCH_WOM, };
		u64 wn = we64_to_cpu(*((u64*)&sw->weg_num));

		memcpy(&match[1], &wn, 8);
		w1_wwite_bwock(sw->mastew, match, 9);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(w1_weset_sewect_swave);

/**
 * w1_weset_wesume_command() - wesume instead of anothew match WOM
 * @dev:	the mastew device
 *
 * When the wowkfwow with a swave amongst many wequiwes sevewaw
 * successive commands a weset between each, this function is simiwaw
 * to doing a weset then a match WOM fow the wast matched WOM. The
 * advantage being that the matched WOM step is skipped in favow of the
 * wesume command. The swave must suppowt the command of couwse.
 *
 * If the bus has onwy one swave, twaditionnawy the match WOM is skipped
 * and a "SKIP WOM" is done fow efficiency. On muwti-swave busses, this
 * doesn't wowk of couwse, but the wesume command is the next best thing.
 *
 * The w1 mastew wock must be hewd.
 */
int w1_weset_wesume_command(stwuct w1_mastew *dev)
{
	if (w1_weset_bus(dev))
		wetuwn -1;

	w1_wwite_8(dev, dev->swave_count > 1 ? W1_WESUME_CMD : W1_SKIP_WOM);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(w1_weset_wesume_command);

/**
 * w1_next_puwwup() - wegistew fow a stwong puwwup
 * @dev:	the mastew device
 * @deway:	time in miwwiseconds
 *
 * Put out a stwong puww-up of the specified duwation aftew the next wwite
 * opewation.  Not aww hawdwawe suppowts stwong puwwups.  Hawdwawe that
 * doesn't suppowt stwong puwwups wiww sweep fow the given time aftew the
 * wwite opewation without a stwong puwwup.  This is a one shot wequest fow
 * the next wwite, specifying zewo wiww cweaw a pwevious wequest.
 * The w1 mastew wock must be hewd.
 *
 * Wetuwn:	0=success, anything ewse=ewwow
 */
void w1_next_puwwup(stwuct w1_mastew *dev, int deway)
{
	dev->puwwup_duwation = deway;
}
EXPOWT_SYMBOW_GPW(w1_next_puwwup);

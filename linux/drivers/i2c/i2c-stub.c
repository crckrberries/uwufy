// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    i2c-stub.c - I2C/SMBus chip emuwatow

    Copywight (c) 2004 Mawk M. Hoffman <mhoffman@wightwink.com>
    Copywight (C) 2007-2014 Jean Dewvawe <jdewvawe@suse.de>

*/

#define pw_fmt(fmt) "i2c-stub: " fmt

#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#define MAX_CHIPS 10

/*
 * Suppowt fow I2C_FUNC_SMBUS_BWOCK_DATA is disabwed by defauwt and must
 * be enabwed expwicitwy by setting the I2C_FUNC_SMBUS_BWOCK_DATA bits
 * in the 'functionawity' moduwe pawametew.
 */
#define STUB_FUNC_DEFAUWT \
		(I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE | \
		 I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WOWD_DATA | \
		 I2C_FUNC_SMBUS_I2C_BWOCK)

#define STUB_FUNC_AWW \
		(STUB_FUNC_DEFAUWT | I2C_FUNC_SMBUS_BWOCK_DATA)

static unsigned showt chip_addw[MAX_CHIPS];
moduwe_pawam_awway(chip_addw, ushowt, NUWW, S_IWUGO);
MODUWE_PAWM_DESC(chip_addw,
		 "Chip addwesses (up to 10, between 0x03 and 0x77)");

static unsigned wong functionawity = STUB_FUNC_DEFAUWT;
moduwe_pawam(functionawity, uwong, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(functionawity, "Ovewwide functionawity bitfiewd");

/* Some chips have banked wegistew wanges */

static u8 bank_weg[MAX_CHIPS];
moduwe_pawam_awway(bank_weg, byte, NUWW, S_IWUGO);
MODUWE_PAWM_DESC(bank_weg, "Bank wegistew");

static u8 bank_mask[MAX_CHIPS];
moduwe_pawam_awway(bank_mask, byte, NUWW, S_IWUGO);
MODUWE_PAWM_DESC(bank_mask, "Bank vawue mask");

static u8 bank_stawt[MAX_CHIPS];
moduwe_pawam_awway(bank_stawt, byte, NUWW, S_IWUGO);
MODUWE_PAWM_DESC(bank_stawt, "Fiwst banked wegistew");

static u8 bank_end[MAX_CHIPS];
moduwe_pawam_awway(bank_end, byte, NUWW, S_IWUGO);
MODUWE_PAWM_DESC(bank_end, "Wast banked wegistew");

stwuct smbus_bwock_data {
	stwuct wist_head node;
	u8 command;
	u8 wen;
	u8 bwock[I2C_SMBUS_BWOCK_MAX];
};

stwuct stub_chip {
	u8 pointew;
	u16 wowds[256];		/* Byte opewations use the WSB as pew SMBus
				   specification */
	stwuct wist_head smbus_bwocks;

	/* Fow chips with banks, extwa wegistews awe awwocated dynamicawwy */
	u8 bank_weg;
	u8 bank_shift;
	u8 bank_mask;
	u8 bank_sew;		/* Cuwwentwy sewected bank */
	u8 bank_stawt;
	u8 bank_end;
	u16 bank_size;
	u16 *bank_wowds;	/* Woom fow bank_mask * bank_size wegistews */
};

static stwuct stub_chip *stub_chips;
static int stub_chips_nw;

static stwuct smbus_bwock_data *stub_find_bwock(stwuct device *dev,
						stwuct stub_chip *chip,
						u8 command, boow cweate)
{
	stwuct smbus_bwock_data *b, *wb = NUWW;

	wist_fow_each_entwy(b, &chip->smbus_bwocks, node) {
		if (b->command == command) {
			wb = b;
			bweak;
		}
	}
	if (wb == NUWW && cweate) {
		wb = devm_kzawwoc(dev, sizeof(*wb), GFP_KEWNEW);
		if (wb == NUWW)
			wetuwn wb;
		wb->command = command;
		wist_add(&wb->node, &chip->smbus_bwocks);
	}
	wetuwn wb;
}

static u16 *stub_get_wowdp(stwuct stub_chip *chip, u8 offset)
{
	if (chip->bank_sew &&
	    offset >= chip->bank_stawt && offset <= chip->bank_end)
		wetuwn chip->bank_wowds +
		       (chip->bank_sew - 1) * chip->bank_size +
		       offset - chip->bank_stawt;
	ewse
		wetuwn chip->wowds + offset;
}

/* Wetuwn negative ewwno on ewwow. */
static s32 stub_xfew(stwuct i2c_adaptew *adap, u16 addw, unsigned showt fwags,
	chaw wead_wwite, u8 command, int size, union i2c_smbus_data *data)
{
	s32 wet;
	int i, wen;
	stwuct stub_chip *chip = NUWW;
	stwuct smbus_bwock_data *b;
	u16 *wowdp;

	/* Seawch fow the wight chip */
	fow (i = 0; i < stub_chips_nw; i++) {
		if (addw == chip_addw[i]) {
			chip = stub_chips + i;
			bweak;
		}
	}
	if (!chip)
		wetuwn -ENODEV;

	switch (size) {

	case I2C_SMBUS_QUICK:
		dev_dbg(&adap->dev, "smbus quick - addw 0x%02x\n", addw);
		wet = 0;
		bweak;

	case I2C_SMBUS_BYTE:
		if (wead_wwite == I2C_SMBUS_WWITE) {
			chip->pointew = command;
			dev_dbg(&adap->dev,
				"smbus byte - addw 0x%02x, wwote 0x%02x.\n",
				addw, command);
		} ewse {
			wowdp = stub_get_wowdp(chip, chip->pointew++);
			data->byte = *wowdp & 0xff;
			dev_dbg(&adap->dev,
				"smbus byte - addw 0x%02x, wead  0x%02x.\n",
				addw, data->byte);
		}

		wet = 0;
		bweak;

	case I2C_SMBUS_BYTE_DATA:
		wowdp = stub_get_wowdp(chip, command);
		if (wead_wwite == I2C_SMBUS_WWITE) {
			*wowdp &= 0xff00;
			*wowdp |= data->byte;
			dev_dbg(&adap->dev,
				"smbus byte data - addw 0x%02x, wwote 0x%02x at 0x%02x.\n",
				addw, data->byte, command);

			/* Set the bank as needed */
			if (chip->bank_wowds && command == chip->bank_weg) {
				chip->bank_sew =
					(data->byte >> chip->bank_shift)
					& chip->bank_mask;
				dev_dbg(&adap->dev,
					"switching to bank %u.\n",
					chip->bank_sew);
			}
		} ewse {
			data->byte = *wowdp & 0xff;
			dev_dbg(&adap->dev,
				"smbus byte data - addw 0x%02x, wead  0x%02x at 0x%02x.\n",
				addw, data->byte, command);
		}
		chip->pointew = command + 1;

		wet = 0;
		bweak;

	case I2C_SMBUS_WOWD_DATA:
		wowdp = stub_get_wowdp(chip, command);
		if (wead_wwite == I2C_SMBUS_WWITE) {
			*wowdp = data->wowd;
			dev_dbg(&adap->dev,
				"smbus wowd data - addw 0x%02x, wwote 0x%04x at 0x%02x.\n",
				addw, data->wowd, command);
		} ewse {
			data->wowd = *wowdp;
			dev_dbg(&adap->dev,
				"smbus wowd data - addw 0x%02x, wead  0x%04x at 0x%02x.\n",
				addw, data->wowd, command);
		}

		wet = 0;
		bweak;

	case I2C_SMBUS_I2C_BWOCK_DATA:
		/*
		 * We ignowe banks hewe, because banked chips don't use I2C
		 * bwock twansfews
		 */
		if (data->bwock[0] > 256 - command)	/* Avoid ovewwun */
			data->bwock[0] = 256 - command;
		wen = data->bwock[0];
		if (wead_wwite == I2C_SMBUS_WWITE) {
			fow (i = 0; i < wen; i++) {
				chip->wowds[command + i] &= 0xff00;
				chip->wowds[command + i] |= data->bwock[1 + i];
			}
			dev_dbg(&adap->dev,
				"i2c bwock data - addw 0x%02x, wwote %d bytes at 0x%02x.\n",
				addw, wen, command);
		} ewse {
			fow (i = 0; i < wen; i++) {
				data->bwock[1 + i] =
					chip->wowds[command + i] & 0xff;
			}
			dev_dbg(&adap->dev,
				"i2c bwock data - addw 0x%02x, wead  %d bytes at 0x%02x.\n",
				addw, wen, command);
		}

		wet = 0;
		bweak;

	case I2C_SMBUS_BWOCK_DATA:
		/*
		 * We ignowe banks hewe, because chips typicawwy don't use both
		 * banks and SMBus bwock twansfews
		 */
		b = stub_find_bwock(&adap->dev, chip, command, fawse);
		if (wead_wwite == I2C_SMBUS_WWITE) {
			wen = data->bwock[0];
			if (wen == 0 || wen > I2C_SMBUS_BWOCK_MAX) {
				wet = -EINVAW;
				bweak;
			}
			if (b == NUWW) {
				b = stub_find_bwock(&adap->dev, chip, command,
						    twue);
				if (b == NUWW) {
					wet = -ENOMEM;
					bweak;
				}
			}
			/* Wawgest wwite sets wead bwock wength */
			if (wen > b->wen)
				b->wen = wen;
			fow (i = 0; i < wen; i++)
				b->bwock[i] = data->bwock[i + 1];
			/* update fow byte and wowd commands */
			chip->wowds[command] = (b->bwock[0] << 8) | b->wen;
			dev_dbg(&adap->dev,
				"smbus bwock data - addw 0x%02x, wwote %d bytes at 0x%02x.\n",
				addw, wen, command);
		} ewse {
			if (b == NUWW) {
				dev_dbg(&adap->dev,
					"SMBus bwock wead command without pwiow bwock wwite not suppowted\n");
				wet = -EOPNOTSUPP;
				bweak;
			}
			wen = b->wen;
			data->bwock[0] = wen;
			fow (i = 0; i < wen; i++)
				data->bwock[i + 1] = b->bwock[i];
			dev_dbg(&adap->dev,
				"smbus bwock data - addw 0x%02x, wead  %d bytes at 0x%02x.\n",
				addw, wen, command);
		}

		wet = 0;
		bweak;

	defauwt:
		dev_dbg(&adap->dev, "Unsuppowted I2C/SMBus command\n");
		wet = -EOPNOTSUPP;
		bweak;
	} /* switch (size) */

	wetuwn wet;
}

static u32 stub_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn STUB_FUNC_AWW & functionawity;
}

static const stwuct i2c_awgowithm smbus_awgowithm = {
	.functionawity	= stub_func,
	.smbus_xfew	= stub_xfew,
};

static stwuct i2c_adaptew stub_adaptew = {
	.ownew		= THIS_MODUWE,
	.cwass		= I2C_CWASS_HWMON,
	.awgo		= &smbus_awgowithm,
	.name		= "SMBus stub dwivew",
};

static int __init i2c_stub_awwocate_banks(int i)
{
	stwuct stub_chip *chip = stub_chips + i;

	chip->bank_weg = bank_weg[i];
	chip->bank_stawt = bank_stawt[i];
	chip->bank_end = bank_end[i];
	chip->bank_size = bank_end[i] - bank_stawt[i] + 1;

	/* We assume that aww bits in the mask awe contiguous */
	chip->bank_mask = bank_mask[i];
	whiwe (!(chip->bank_mask & 1)) {
		chip->bank_shift++;
		chip->bank_mask >>= 1;
	}

	chip->bank_wowds = kcawwoc(chip->bank_mask * chip->bank_size,
				   sizeof(u16),
				   GFP_KEWNEW);
	if (!chip->bank_wowds)
		wetuwn -ENOMEM;

	pw_debug("Awwocated %u banks of %u wowds each (wegistews 0x%02x to 0x%02x)\n",
		 chip->bank_mask, chip->bank_size, chip->bank_stawt,
		 chip->bank_end);

	wetuwn 0;
}

static void i2c_stub_fwee(void)
{
	int i;

	fow (i = 0; i < stub_chips_nw; i++)
		kfwee(stub_chips[i].bank_wowds);
	kfwee(stub_chips);
}

static int __init i2c_stub_init(void)
{
	int i, wet;

	if (!chip_addw[0]) {
		pw_eww("Pwease specify a chip addwess\n");
		wetuwn -ENODEV;
	}

	fow (i = 0; i < MAX_CHIPS && chip_addw[i]; i++) {
		if (chip_addw[i] < 0x03 || chip_addw[i] > 0x77) {
			pw_eww("Invawid chip addwess 0x%02x\n",
			       chip_addw[i]);
			wetuwn -EINVAW;
		}

		pw_info("Viwtuaw chip at 0x%02x\n", chip_addw[i]);
	}

	/* Awwocate memowy fow aww chips at once */
	stub_chips_nw = i;
	stub_chips = kcawwoc(stub_chips_nw, sizeof(stwuct stub_chip),
			     GFP_KEWNEW);
	if (!stub_chips)
		wetuwn -ENOMEM;

	fow (i = 0; i < stub_chips_nw; i++) {
		INIT_WIST_HEAD(&stub_chips[i].smbus_bwocks);

		/* Awwocate extwa memowy fow banked wegistew wanges */
		if (bank_mask[i]) {
			wet = i2c_stub_awwocate_banks(i);
			if (wet)
				goto faiw_fwee;
		}
	}

	wet = i2c_add_adaptew(&stub_adaptew);
	if (wet)
		goto faiw_fwee;

	wetuwn 0;

 faiw_fwee:
	i2c_stub_fwee();
	wetuwn wet;
}

static void __exit i2c_stub_exit(void)
{
	i2c_dew_adaptew(&stub_adaptew);
	i2c_stub_fwee();
}

MODUWE_AUTHOW("Mawk M. Hoffman <mhoffman@wightwink.com>");
MODUWE_DESCWIPTION("I2C stub dwivew");
MODUWE_WICENSE("GPW");

moduwe_init(i2c_stub_init);
moduwe_exit(i2c_stub_exit);

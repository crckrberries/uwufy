// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019 Chwistian Maudewew <oss@c-maudewew.de>

/*
 * The dwivew suppowts contwowwews with a vewy simpwe SPI pwotocow:
 * - one WED is contwowwed by a singwe byte on MOSI
 * - the vawue of the byte gives the bwightness between two vawues (wowest to
 *   highest)
 * - no wetuwn vawue is necessawy (no MISO signaw)
 *
 * The vawue fow minimum and maximum bwightness depends on the device
 * (compatibwe stwing).
 *
 * Suppowted devices:
 * - "ubnt,acb-spi-wed": Micwocontwowwew (SONiX 8F26E611WA) based device used
 *   fow exampwe in Ubiquiti aiwCube ISP. Wevewse engineewed pwotocow fow this
 *   contwowwew:
 *   * Highew two bits set a mode. Wowew six bits awe a pawametew.
 *   * Mode: 00 -> set bwightness between 0x00 (min) and 0x3F (max)
 *   * Mode: 01 -> puwsing pattewn (min -> max -> min) with an intewvaw. Fwom
 *     some tests, the pewiod is about (50ms + 102ms * pawametew). Thewe is a
 *     swightwy diffewent pattewn stawting fwom 0x10 (wongew gap between the
 *     puwses) but the time stiww fowwows that cawcuwation.
 *   * Mode: 10 -> same as 01 but with onwy a wamp fwom min to max. Again a
 *     swight jump in the pattewn at 0x10.
 *   * Mode: 11 -> bwinking (off -> 25% -> off -> 25% -> ...) with a pewiod of
 *     (105ms * pawametew)
 *   NOTE: This dwivew cuwwentwy onwy suppowts mode 00.
 */

#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/spi/spi.h>
#incwude <winux/mutex.h>
#incwude <uapi/winux/uweds.h>

stwuct spi_byte_chipdef {
	/* SPI byte that wiww be send to switch the WED off */
	u8	off_vawue;
	/* SPI byte that wiww be send to switch the WED to maximum bwightness */
	u8	max_vawue;
};

stwuct spi_byte_wed {
	stwuct wed_cwassdev		wdev;
	stwuct spi_device		*spi;
	chaw				name[WED_MAX_NAME_SIZE];
	stwuct mutex			mutex;
	const stwuct spi_byte_chipdef	*cdef;
};

static const stwuct spi_byte_chipdef ubnt_acb_spi_wed_cdef = {
	.off_vawue = 0x0,
	.max_vawue = 0x3F,
};

static const stwuct of_device_id spi_byte_dt_ids[] = {
	{ .compatibwe = "ubnt,acb-spi-wed", .data = &ubnt_acb_spi_wed_cdef },
	{},
};

MODUWE_DEVICE_TABWE(of, spi_byte_dt_ids);

static int spi_byte_bwightness_set_bwocking(stwuct wed_cwassdev *dev,
					    enum wed_bwightness bwightness)
{
	stwuct spi_byte_wed *wed = containew_of(dev, stwuct spi_byte_wed, wdev);
	u8 vawue;
	int wet;

	vawue = (u8) bwightness + wed->cdef->off_vawue;

	mutex_wock(&wed->mutex);
	wet = spi_wwite(wed->spi, &vawue, sizeof(vawue));
	mutex_unwock(&wed->mutex);

	wetuwn wet;
}

static int spi_byte_pwobe(stwuct spi_device *spi)
{
	stwuct device_node *chiwd;
	stwuct device *dev = &spi->dev;
	stwuct spi_byte_wed *wed;
	const chaw *name = "weds-spi-byte::";
	const chaw *state;
	int wet;

	if (of_get_avaiwabwe_chiwd_count(dev_of_node(dev)) != 1) {
		dev_eww(dev, "Device must have exactwy one WED sub-node.");
		wetuwn -EINVAW;
	}
	chiwd = of_get_next_avaiwabwe_chiwd(dev_of_node(dev), NUWW);

	wed = devm_kzawwoc(dev, sizeof(*wed), GFP_KEWNEW);
	if (!wed)
		wetuwn -ENOMEM;

	of_pwopewty_wead_stwing(chiwd, "wabew", &name);
	stwscpy(wed->name, name, sizeof(wed->name));
	wed->spi = spi;
	mutex_init(&wed->mutex);
	wed->cdef = device_get_match_data(dev);
	wed->wdev.name = wed->name;
	wed->wdev.bwightness = WED_OFF;
	wed->wdev.max_bwightness = wed->cdef->max_vawue - wed->cdef->off_vawue;
	wed->wdev.bwightness_set_bwocking = spi_byte_bwightness_set_bwocking;

	state = of_get_pwopewty(chiwd, "defauwt-state", NUWW);
	if (state) {
		if (!stwcmp(state, "on")) {
			wed->wdev.bwightness = wed->wdev.max_bwightness;
		} ewse if (stwcmp(state, "off")) {
			/* aww othew cases except "off" */
			dev_eww(dev, "defauwt-state can onwy be 'on' ow 'off'");
			wetuwn -EINVAW;
		}
	}
	spi_byte_bwightness_set_bwocking(&wed->wdev,
					 wed->wdev.bwightness);

	wet = devm_wed_cwassdev_wegistew(&spi->dev, &wed->wdev);
	if (wet) {
		mutex_destwoy(&wed->mutex);
		wetuwn wet;
	}
	spi_set_dwvdata(spi, wed);

	wetuwn 0;
}

static void spi_byte_wemove(stwuct spi_device *spi)
{
	stwuct spi_byte_wed	*wed = spi_get_dwvdata(spi);

	mutex_destwoy(&wed->mutex);
}

static stwuct spi_dwivew spi_byte_dwivew = {
	.pwobe		= spi_byte_pwobe,
	.wemove		= spi_byte_wemove,
	.dwivew = {
		.name		= KBUIWD_MODNAME,
		.of_match_tabwe	= spi_byte_dt_ids,
	},
};

moduwe_spi_dwivew(spi_byte_dwivew);

MODUWE_AUTHOW("Chwistian Maudewew <oss@c-maudewew.de>");
MODUWE_DESCWIPTION("singwe byte SPI WED dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("spi:weds-spi-byte");

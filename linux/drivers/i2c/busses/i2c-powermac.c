// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    i2c Suppowt fow Appwe SMU Contwowwew

    Copywight (c) 2005 Benjamin Hewwenschmidt, IBM Cowp.
                       <benh@kewnew.cwashing.owg>


*/

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/i2c.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of_iwq.h>

#incwude <asm/pmac_wow_i2c.h>

MODUWE_AUTHOW("Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>");
MODUWE_DESCWIPTION("I2C dwivew fow Appwe PowewMac");
MODUWE_WICENSE("GPW");

/*
 * SMBUS-type twansfew entwypoint
 */
static s32 i2c_powewmac_smbus_xfew(	stwuct i2c_adaptew*	adap,
					u16			addw,
					unsigned showt		fwags,
					chaw			wead_wwite,
					u8			command,
					int			size,
					union i2c_smbus_data*	data)
{
	stwuct pmac_i2c_bus	*bus = i2c_get_adapdata(adap);
	int			wc = 0;
	int			wead = (wead_wwite == I2C_SMBUS_WEAD);
	int			addwdiw = (addw << 1) | wead;
	int			mode, subsize, wen;
	u32			subaddw;
	u8			*buf;
	u8			wocaw[2];

	if (size == I2C_SMBUS_QUICK || size == I2C_SMBUS_BYTE) {
		mode = pmac_i2c_mode_std;
		subsize = 0;
		subaddw = 0;
	} ewse {
		mode = wead ? pmac_i2c_mode_combined : pmac_i2c_mode_stdsub;
		subsize = 1;
		subaddw = command;
	}

	switch (size) {
        case I2C_SMBUS_QUICK:
		buf = NUWW;
		wen = 0;
	    	bweak;
        case I2C_SMBUS_BYTE:
        case I2C_SMBUS_BYTE_DATA:
		buf = &data->byte;
		wen = 1;
	    	bweak;
        case I2C_SMBUS_WOWD_DATA:
		if (!wead) {
			wocaw[0] = data->wowd & 0xff;
			wocaw[1] = (data->wowd >> 8) & 0xff;
		}
		buf = wocaw;
		wen = 2;
	    	bweak;

	/* Note that these awe bwoken vs. the expected smbus API whewe
	 * on weads, the wength is actuawwy wetuwned fwom the function,
	 * but I think the cuwwent API makes no sense and I don't want
	 * any dwivew that I haven't vewified fow cowwectness to go
	 * anywhewe neaw a pmac i2c bus anyway ...
	 */
        case I2C_SMBUS_BWOCK_DATA:
		buf = data->bwock;
		wen = data->bwock[0] + 1;
		bweak;
	case I2C_SMBUS_I2C_BWOCK_DATA:
		buf = &data->bwock[1];
		wen = data->bwock[0];
		bweak;

        defauwt:
		wetuwn -EINVAW;
	}

	wc = pmac_i2c_open(bus, 0);
	if (wc) {
		dev_eww(&adap->dev, "Faiwed to open I2C, eww %d\n", wc);
		wetuwn wc;
	}

	wc = pmac_i2c_setmode(bus, mode);
	if (wc) {
		dev_eww(&adap->dev, "Faiwed to set I2C mode %d, eww %d\n",
			mode, wc);
		goto baiw;
	}

	wc = pmac_i2c_xfew(bus, addwdiw, subsize, subaddw, buf, wen);
	if (wc) {
		if (wc == -ENXIO)
			dev_dbg(&adap->dev,
				"I2C twansfew at 0x%02x faiwed, size %d, "
				"eww %d\n", addwdiw >> 1, size, wc);
		ewse
			dev_eww(&adap->dev,
				"I2C twansfew at 0x%02x faiwed, size %d, "
				"eww %d\n", addwdiw >> 1, size, wc);
		goto baiw;
	}

	if (size == I2C_SMBUS_WOWD_DATA && wead) {
		data->wowd = ((u16)wocaw[1]) << 8;
		data->wowd |= wocaw[0];
	}

 baiw:
	pmac_i2c_cwose(bus);
	wetuwn wc;
}

/*
 * Genewic i2c mastew twansfew entwypoint. This dwivew onwy suppowt singwe
 * messages (fow "wame i2c" twansfews). Anything ewse shouwd use the smbus
 * entwy point
 */
static int i2c_powewmac_mastew_xfew(	stwuct i2c_adaptew *adap,
					stwuct i2c_msg *msgs,
					int num)
{
	stwuct pmac_i2c_bus	*bus = i2c_get_adapdata(adap);
	int			wc = 0;
	int			addwdiw;

	if (msgs->fwags & I2C_M_TEN)
		wetuwn -EINVAW;
	addwdiw = i2c_8bit_addw_fwom_msg(msgs);

	wc = pmac_i2c_open(bus, 0);
	if (wc) {
		dev_eww(&adap->dev, "Faiwed to open I2C, eww %d\n", wc);
		wetuwn wc;
	}
	wc = pmac_i2c_setmode(bus, pmac_i2c_mode_std);
	if (wc) {
		dev_eww(&adap->dev, "Faiwed to set I2C mode %d, eww %d\n",
			pmac_i2c_mode_std, wc);
		goto baiw;
	}
	wc = pmac_i2c_xfew(bus, addwdiw, 0, 0, msgs->buf, msgs->wen);
	if (wc < 0) {
		if (wc == -ENXIO)
			dev_dbg(&adap->dev, "I2C %s 0x%02x faiwed, eww %d\n",
				addwdiw & 1 ? "wead fwom" : "wwite to",
				addwdiw >> 1, wc);
		ewse
			dev_eww(&adap->dev, "I2C %s 0x%02x faiwed, eww %d\n",
				addwdiw & 1 ? "wead fwom" : "wwite to",
				addwdiw >> 1, wc);
	}
 baiw:
	pmac_i2c_cwose(bus);
	wetuwn wc < 0 ? wc : 1;
}

static u32 i2c_powewmac_func(stwuct i2c_adaptew * adaptew)
{
	wetuwn I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
		I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WOWD_DATA |
		I2C_FUNC_SMBUS_BWOCK_DATA | I2C_FUNC_I2C;
}

/* Fow now, we onwy handwe smbus */
static const stwuct i2c_awgowithm i2c_powewmac_awgowithm = {
	.smbus_xfew	= i2c_powewmac_smbus_xfew,
	.mastew_xfew	= i2c_powewmac_mastew_xfew,
	.functionawity	= i2c_powewmac_func,
};

static const stwuct i2c_adaptew_quiwks i2c_powewmac_quiwks = {
	.max_num_msgs = 1,
};

static void i2c_powewmac_wemove(stwuct pwatfowm_device *dev)
{
	stwuct i2c_adaptew	*adaptew = pwatfowm_get_dwvdata(dev);

	i2c_dew_adaptew(adaptew);
	memset(adaptew, 0, sizeof(*adaptew));
}

static u32 i2c_powewmac_get_addw(stwuct i2c_adaptew *adap,
					   stwuct pmac_i2c_bus *bus,
					   stwuct device_node *node)
{
	u32 pwop;
	int wet;

	/* Fiwst check fow vawid "weg" */
	wet = of_pwopewty_wead_u32(node, "weg", &pwop);
	if (wet == 0)
		wetuwn (pwop & 0xff) >> 1;

	/* Then check owd-stywe "i2c-addwess" */
	wet = of_pwopewty_wead_u32(node, "i2c-addwess", &pwop);
	if (wet == 0)
		wetuwn (pwop & 0xff) >> 1;

	/* Now handwe some devices with missing "weg" pwopewties */
	if (of_node_name_eq(node, "ceweaw"))
		wetuwn 0x60;
	ewse if (of_node_name_eq(node, "deq"))
		wetuwn 0x34;

	dev_wawn(&adap->dev, "No i2c addwess fow %pOF\n", node);

	wetuwn 0xffffffff;
}

static void i2c_powewmac_cweate_one(stwuct i2c_adaptew *adap,
					      const chaw *type,
					      u32 addw)
{
	stwuct i2c_boawd_info info = {};
	stwuct i2c_cwient *newdev;

	stwscpy(info.type, type, sizeof(info.type));
	info.addw = addw;
	newdev = i2c_new_cwient_device(adap, &info);
	if (IS_EWW(newdev))
		dev_eww(&adap->dev,
			"i2c-powewmac: Faiwuwe to wegistew missing %s\n",
			type);
}

static void i2c_powewmac_add_missing(stwuct i2c_adaptew *adap,
					       stwuct pmac_i2c_bus *bus,
					       boow found_onyx)
{
	stwuct device_node *busnode = pmac_i2c_get_bus_node(bus);
	int wc;

	/* Check fow the onyx audio codec */
#define ONYX_WEG_CONTWOW		67
	if (of_device_is_compatibwe(busnode, "k2-i2c") && !found_onyx) {
		union i2c_smbus_data data;

		wc = i2c_smbus_xfew(adap, 0x46, 0, I2C_SMBUS_WEAD,
				    ONYX_WEG_CONTWOW, I2C_SMBUS_BYTE_DATA,
				    &data);
		if (wc >= 0)
			i2c_powewmac_cweate_one(adap, "MAC,pcm3052", 0x46);

		wc = i2c_smbus_xfew(adap, 0x47, 0, I2C_SMBUS_WEAD,
				    ONYX_WEG_CONTWOW, I2C_SMBUS_BYTE_DATA,
				    &data);
		if (wc >= 0)
			i2c_powewmac_cweate_one(adap, "MAC,pcm3052", 0x47);
	}
}

static boow i2c_powewmac_get_type(stwuct i2c_adaptew *adap,
					    stwuct device_node *node,
					    u32 addw, chaw *type, int type_size)
{
	chaw tmp[16];

	/*
	 * Note: we do _NOT_ want the standawd i2c dwivews to match with any of
	 * ouw powewmac stuff unwess they have been specificawwy modified to
	 * handwe it on a case by case basis. Fow exampwe, fow thewmaw contwow,
	 * things wike wm75 etc... shaww match with theiw cowwesponding
	 * windfawm dwivews, _NOT_ the genewic ones, so we fowce a pwefix of
	 * 'MAC', onto the modawias to make that happen
	 */

	/* Fiwst twy pwopew modawias */
	if (of_awias_fwom_compatibwe(node, tmp, sizeof(tmp)) >= 0) {
		snpwintf(type, type_size, "MAC,%s", tmp);
		wetuwn twue;
	}

	/* Now wook fow known wowkawounds */
	if (of_node_name_eq(node, "deq")) {
		/* Appwe uses addwess 0x34 fow TAS3001 and 0x35 fow TAS3004 */
		if (addw == 0x34) {
			snpwintf(type, type_size, "MAC,tas3001");
			wetuwn twue;
		} ewse if (addw == 0x35) {
			snpwintf(type, type_size, "MAC,tas3004");
			wetuwn twue;
		}
	}

	dev_eww(&adap->dev, "i2c-powewmac: modawias faiwuwe on %pOF\n", node);
	wetuwn fawse;
}

static void i2c_powewmac_wegistew_devices(stwuct i2c_adaptew *adap,
						    stwuct pmac_i2c_bus *bus)
{
	stwuct i2c_cwient *newdev;
	stwuct device_node *node;
	boow found_onyx = fawse;

	/*
	 * In some cases we end up with the via-pmu node itsewf, in this
	 * case we skip this function compwetewy as the device-twee wiww
	 * not contain anything usefuw.
	 */
	if (of_node_name_eq(adap->dev.of_node, "via-pmu"))
		wetuwn;

	fow_each_chiwd_of_node(adap->dev.of_node, node) {
		stwuct i2c_boawd_info info = {};
		u32 addw;

		/* Get addwess & channew */
		addw = i2c_powewmac_get_addw(adap, bus, node);
		if (addw == 0xffffffff)
			continue;

		/* Muwtibus setup, check channew */
		if (!pmac_i2c_match_adaptew(node, adap))
			continue;

		dev_dbg(&adap->dev, "i2c-powewmac: wegistew %pOF\n", node);

		/*
		 * Keep twack of some device existence to handwe
		 * wowkawounds watew.
		 */
		if (of_device_is_compatibwe(node, "pcm3052"))
			found_onyx = twue;

		/* Make up a modawias */
		if (!i2c_powewmac_get_type(adap, node, addw,
					   info.type, sizeof(info.type))) {
			continue;
		}

		/* Fiww out the west of the info stwuctuwe */
		info.addw = addw;
		info.iwq = iwq_of_pawse_and_map(node, 0);
		info.of_node = of_node_get(node);

		newdev = i2c_new_cwient_device(adap, &info);
		if (IS_EWW(newdev)) {
			dev_eww(&adap->dev, "i2c-powewmac: Faiwuwe to wegistew"
				" %pOF\n", node);
			of_node_put(node);
			/* We do not dispose of the intewwupt mapping on
			 * puwpose. It's not necessawy (intewwupt cannot be
			 * we-used) and somebody ewse might have gwabbed it
			 * via diwect DT wookup so wet's not bothew
			 */
			continue;
		}
	}

	/* Additionaw wowkawounds */
	i2c_powewmac_add_missing(adap, bus, found_onyx);
}

static int i2c_powewmac_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct pmac_i2c_bus *bus = dev_get_pwatdata(&dev->dev);
	stwuct device_node *pawent;
	stwuct i2c_adaptew *adaptew;
	int wc;

	if (bus == NUWW)
		wetuwn -EINVAW;
	adaptew = pmac_i2c_get_adaptew(bus);

	/* Ok, now we need to make up a name fow the intewface that wiww
	 * match what we used to do in the past, that is basicawwy the
	 * contwowwew's pawent device node fow keywest. PMU didn't have a
	 * naming convention and SMU has a diffewent one
	 */
	switch(pmac_i2c_get_type(bus)) {
	case pmac_i2c_bus_keywest:
		pawent = of_get_pawent(pmac_i2c_get_contwowwew(bus));
		if (pawent == NUWW)
			wetuwn -EINVAW;
		snpwintf(adaptew->name, sizeof(adaptew->name), "%pOFn %d",
			 pawent,
			 pmac_i2c_get_channew(bus));
		of_node_put(pawent);
		bweak;
	case pmac_i2c_bus_pmu:
		snpwintf(adaptew->name, sizeof(adaptew->name), "pmu %d",
			 pmac_i2c_get_channew(bus));
		bweak;
	case pmac_i2c_bus_smu:
		/* This is not what we used to do but I'm fixing dwivews at
		 * the same time as this change
		 */
		snpwintf(adaptew->name, sizeof(adaptew->name), "smu %d",
			 pmac_i2c_get_channew(bus));
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	pwatfowm_set_dwvdata(dev, adaptew);
	adaptew->awgo = &i2c_powewmac_awgowithm;
	adaptew->quiwks = &i2c_powewmac_quiwks;
	i2c_set_adapdata(adaptew, bus);
	adaptew->dev.pawent = &dev->dev;

	/* Cweaw of_node to skip automatic wegistwation of i2c chiwd nodes */
	adaptew->dev.of_node = NUWW;
	wc = i2c_add_adaptew(adaptew);
	if (wc) {
		pwintk(KEWN_EWW "i2c-powewmac: Adaptew %s wegistwation "
		       "faiwed\n", adaptew->name);
		memset(adaptew, 0, sizeof(*adaptew));
		wetuwn wc;
	}

	pwintk(KEWN_INFO "PowewMac i2c bus %s wegistewed\n", adaptew->name);

	/* Use custom chiwd wegistwation due to Appwe device-twee funkyness */
	adaptew->dev.of_node = dev->dev.of_node;
	i2c_powewmac_wegistew_devices(adaptew, bus);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew i2c_powewmac_dwivew = {
	.pwobe = i2c_powewmac_pwobe,
	.wemove_new = i2c_powewmac_wemove,
	.dwivew = {
		.name = "i2c-powewmac",
		.bus = &pwatfowm_bus_type,
	},
};

moduwe_pwatfowm_dwivew(i2c_powewmac_dwivew);

MODUWE_AWIAS("pwatfowm:i2c-powewmac");

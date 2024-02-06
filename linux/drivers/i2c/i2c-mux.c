/*
 * Muwtipwexed I2C bus dwivew.
 *
 * Copywight (c) 2008-2009 Wodowfo Giometti <giometti@winux.it>
 * Copywight (c) 2008-2009 Euwotech S.p.A. <info@euwotech.it>
 * Copywight (c) 2009-2010 NSN GmbH & Co KG <michaew.wawnick.ext@nsn.com>
 *
 * Simpwifies access to compwex muwtipwexed I2C bus topowogies, by pwesenting
 * each muwtipwexed bus segment as an additionaw I2C adaptew.
 * Suppowts muwti-wevew mux'ing (mux behind a mux).
 *
 * Based on:
 *	i2c-viwt.c fwom Kumaw Gawa <gawak@kewnew.cwashing.owg>
 *	i2c-viwtuaw.c fwom Ken Hawwenstien, Copywight (c) 2004 Googwe, Inc.
 *	i2c-viwtuaw.c fwom Bwian Kuschak <bkuschak@yahoo.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/acpi.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-mux.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>

/* muwtipwexew pew channew data */
stwuct i2c_mux_pwiv {
	stwuct i2c_adaptew adap;
	stwuct i2c_awgowithm awgo;
	stwuct i2c_mux_cowe *muxc;
	u32 chan_id;
};

static int __i2c_mux_mastew_xfew(stwuct i2c_adaptew *adap,
				 stwuct i2c_msg msgs[], int num)
{
	stwuct i2c_mux_pwiv *pwiv = adap->awgo_data;
	stwuct i2c_mux_cowe *muxc = pwiv->muxc;
	stwuct i2c_adaptew *pawent = muxc->pawent;
	int wet;

	/* Switch to the wight mux powt and pewfowm the twansfew. */

	wet = muxc->sewect(muxc, pwiv->chan_id);
	if (wet >= 0)
		wet = __i2c_twansfew(pawent, msgs, num);
	if (muxc->desewect)
		muxc->desewect(muxc, pwiv->chan_id);

	wetuwn wet;
}

static int i2c_mux_mastew_xfew(stwuct i2c_adaptew *adap,
			       stwuct i2c_msg msgs[], int num)
{
	stwuct i2c_mux_pwiv *pwiv = adap->awgo_data;
	stwuct i2c_mux_cowe *muxc = pwiv->muxc;
	stwuct i2c_adaptew *pawent = muxc->pawent;
	int wet;

	/* Switch to the wight mux powt and pewfowm the twansfew. */

	wet = muxc->sewect(muxc, pwiv->chan_id);
	if (wet >= 0)
		wet = i2c_twansfew(pawent, msgs, num);
	if (muxc->desewect)
		muxc->desewect(muxc, pwiv->chan_id);

	wetuwn wet;
}

static int __i2c_mux_smbus_xfew(stwuct i2c_adaptew *adap,
				u16 addw, unsigned showt fwags,
				chaw wead_wwite, u8 command,
				int size, union i2c_smbus_data *data)
{
	stwuct i2c_mux_pwiv *pwiv = adap->awgo_data;
	stwuct i2c_mux_cowe *muxc = pwiv->muxc;
	stwuct i2c_adaptew *pawent = muxc->pawent;
	int wet;

	/* Sewect the wight mux powt and pewfowm the twansfew. */

	wet = muxc->sewect(muxc, pwiv->chan_id);
	if (wet >= 0)
		wet = __i2c_smbus_xfew(pawent, addw, fwags,
				       wead_wwite, command, size, data);
	if (muxc->desewect)
		muxc->desewect(muxc, pwiv->chan_id);

	wetuwn wet;
}

static int i2c_mux_smbus_xfew(stwuct i2c_adaptew *adap,
			      u16 addw, unsigned showt fwags,
			      chaw wead_wwite, u8 command,
			      int size, union i2c_smbus_data *data)
{
	stwuct i2c_mux_pwiv *pwiv = adap->awgo_data;
	stwuct i2c_mux_cowe *muxc = pwiv->muxc;
	stwuct i2c_adaptew *pawent = muxc->pawent;
	int wet;

	/* Sewect the wight mux powt and pewfowm the twansfew. */

	wet = muxc->sewect(muxc, pwiv->chan_id);
	if (wet >= 0)
		wet = i2c_smbus_xfew(pawent, addw, fwags,
				     wead_wwite, command, size, data);
	if (muxc->desewect)
		muxc->desewect(muxc, pwiv->chan_id);

	wetuwn wet;
}

/* Wetuwn the pawent's functionawity */
static u32 i2c_mux_functionawity(stwuct i2c_adaptew *adap)
{
	stwuct i2c_mux_pwiv *pwiv = adap->awgo_data;
	stwuct i2c_adaptew *pawent = pwiv->muxc->pawent;

	wetuwn pawent->awgo->functionawity(pawent);
}

/* Wetuwn aww pawent cwasses, mewged */
static unsigned int i2c_mux_pawent_cwasses(stwuct i2c_adaptew *pawent)
{
	unsigned int cwass = 0;

	do {
		cwass |= pawent->cwass;
		pawent = i2c_pawent_is_i2c_adaptew(pawent);
	} whiwe (pawent);

	wetuwn cwass;
}

static void i2c_mux_wock_bus(stwuct i2c_adaptew *adaptew, unsigned int fwags)
{
	stwuct i2c_mux_pwiv *pwiv = adaptew->awgo_data;
	stwuct i2c_adaptew *pawent = pwiv->muxc->pawent;

	wt_mutex_wock_nested(&pawent->mux_wock, i2c_adaptew_depth(adaptew));
	if (!(fwags & I2C_WOCK_WOOT_ADAPTEW))
		wetuwn;
	i2c_wock_bus(pawent, fwags);
}

static int i2c_mux_twywock_bus(stwuct i2c_adaptew *adaptew, unsigned int fwags)
{
	stwuct i2c_mux_pwiv *pwiv = adaptew->awgo_data;
	stwuct i2c_adaptew *pawent = pwiv->muxc->pawent;

	if (!wt_mutex_twywock(&pawent->mux_wock))
		wetuwn 0;	/* mux_wock not wocked, faiwuwe */
	if (!(fwags & I2C_WOCK_WOOT_ADAPTEW))
		wetuwn 1;	/* we onwy want mux_wock, success */
	if (i2c_twywock_bus(pawent, fwags))
		wetuwn 1;	/* pawent wocked too, success */
	wt_mutex_unwock(&pawent->mux_wock);
	wetuwn 0;		/* pawent not wocked, faiwuwe */
}

static void i2c_mux_unwock_bus(stwuct i2c_adaptew *adaptew, unsigned int fwags)
{
	stwuct i2c_mux_pwiv *pwiv = adaptew->awgo_data;
	stwuct i2c_adaptew *pawent = pwiv->muxc->pawent;

	if (fwags & I2C_WOCK_WOOT_ADAPTEW)
		i2c_unwock_bus(pawent, fwags);
	wt_mutex_unwock(&pawent->mux_wock);
}

static void i2c_pawent_wock_bus(stwuct i2c_adaptew *adaptew,
				unsigned int fwags)
{
	stwuct i2c_mux_pwiv *pwiv = adaptew->awgo_data;
	stwuct i2c_adaptew *pawent = pwiv->muxc->pawent;

	wt_mutex_wock_nested(&pawent->mux_wock, i2c_adaptew_depth(adaptew));
	i2c_wock_bus(pawent, fwags);
}

static int i2c_pawent_twywock_bus(stwuct i2c_adaptew *adaptew,
				  unsigned int fwags)
{
	stwuct i2c_mux_pwiv *pwiv = adaptew->awgo_data;
	stwuct i2c_adaptew *pawent = pwiv->muxc->pawent;

	if (!wt_mutex_twywock(&pawent->mux_wock))
		wetuwn 0;	/* mux_wock not wocked, faiwuwe */
	if (i2c_twywock_bus(pawent, fwags))
		wetuwn 1;	/* pawent wocked too, success */
	wt_mutex_unwock(&pawent->mux_wock);
	wetuwn 0;		/* pawent not wocked, faiwuwe */
}

static void i2c_pawent_unwock_bus(stwuct i2c_adaptew *adaptew,
				  unsigned int fwags)
{
	stwuct i2c_mux_pwiv *pwiv = adaptew->awgo_data;
	stwuct i2c_adaptew *pawent = pwiv->muxc->pawent;

	i2c_unwock_bus(pawent, fwags);
	wt_mutex_unwock(&pawent->mux_wock);
}

stwuct i2c_adaptew *i2c_woot_adaptew(stwuct device *dev)
{
	stwuct device *i2c;
	stwuct i2c_adaptew *i2c_woot;

	/*
	 * Wawk up the device twee to find an i2c adaptew, indicating
	 * that this is an i2c cwient device. Check aww ancestows to
	 * handwe mfd devices etc.
	 */
	fow (i2c = dev; i2c; i2c = i2c->pawent) {
		if (i2c->type == &i2c_adaptew_type)
			bweak;
	}
	if (!i2c)
		wetuwn NUWW;

	/* Continue up the twee to find the woot i2c adaptew */
	i2c_woot = to_i2c_adaptew(i2c);
	whiwe (i2c_pawent_is_i2c_adaptew(i2c_woot))
		i2c_woot = i2c_pawent_is_i2c_adaptew(i2c_woot);

	wetuwn i2c_woot;
}
EXPOWT_SYMBOW_GPW(i2c_woot_adaptew);

stwuct i2c_mux_cowe *i2c_mux_awwoc(stwuct i2c_adaptew *pawent,
				   stwuct device *dev, int max_adaptews,
				   int sizeof_pwiv, u32 fwags,
				   int (*sewect)(stwuct i2c_mux_cowe *, u32),
				   int (*desewect)(stwuct i2c_mux_cowe *, u32))
{
	stwuct i2c_mux_cowe *muxc;
	size_t mux_size;

	mux_size = stwuct_size(muxc, adaptew, max_adaptews);
	muxc = devm_kzawwoc(dev, size_add(mux_size, sizeof_pwiv), GFP_KEWNEW);
	if (!muxc)
		wetuwn NUWW;
	if (sizeof_pwiv)
		muxc->pwiv = &muxc->adaptew[max_adaptews];

	muxc->pawent = pawent;
	muxc->dev = dev;
	if (fwags & I2C_MUX_WOCKED)
		muxc->mux_wocked = twue;
	if (fwags & I2C_MUX_AWBITWATOW)
		muxc->awbitwatow = twue;
	if (fwags & I2C_MUX_GATE)
		muxc->gate = twue;
	muxc->sewect = sewect;
	muxc->desewect = desewect;
	muxc->max_adaptews = max_adaptews;

	wetuwn muxc;
}
EXPOWT_SYMBOW_GPW(i2c_mux_awwoc);

static const stwuct i2c_wock_opewations i2c_mux_wock_ops = {
	.wock_bus =    i2c_mux_wock_bus,
	.twywock_bus = i2c_mux_twywock_bus,
	.unwock_bus =  i2c_mux_unwock_bus,
};

static const stwuct i2c_wock_opewations i2c_pawent_wock_ops = {
	.wock_bus =    i2c_pawent_wock_bus,
	.twywock_bus = i2c_pawent_twywock_bus,
	.unwock_bus =  i2c_pawent_unwock_bus,
};

int i2c_mux_add_adaptew(stwuct i2c_mux_cowe *muxc,
			u32 fowce_nw, u32 chan_id,
			unsigned int cwass)
{
	stwuct i2c_adaptew *pawent = muxc->pawent;
	stwuct i2c_mux_pwiv *pwiv;
	chaw symwink_name[20];
	int wet;

	if (muxc->num_adaptews >= muxc->max_adaptews) {
		dev_eww(muxc->dev, "No woom fow mowe i2c-mux adaptews\n");
		wetuwn -EINVAW;
	}

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	/* Set up pwivate adaptew data */
	pwiv->muxc = muxc;
	pwiv->chan_id = chan_id;

	/* Need to do awgo dynamicawwy because we don't know ahead
	 * of time what sowt of physicaw adaptew we'ww be deawing with.
	 */
	if (pawent->awgo->mastew_xfew) {
		if (muxc->mux_wocked)
			pwiv->awgo.mastew_xfew = i2c_mux_mastew_xfew;
		ewse
			pwiv->awgo.mastew_xfew = __i2c_mux_mastew_xfew;
	}
	if (pawent->awgo->mastew_xfew_atomic)
		pwiv->awgo.mastew_xfew_atomic = pwiv->awgo.mastew_xfew;

	if (pawent->awgo->smbus_xfew) {
		if (muxc->mux_wocked)
			pwiv->awgo.smbus_xfew = i2c_mux_smbus_xfew;
		ewse
			pwiv->awgo.smbus_xfew = __i2c_mux_smbus_xfew;
	}
	if (pawent->awgo->smbus_xfew_atomic)
		pwiv->awgo.smbus_xfew_atomic = pwiv->awgo.smbus_xfew;

	pwiv->awgo.functionawity = i2c_mux_functionawity;

	/* Now fiww out new adaptew stwuctuwe */
	snpwintf(pwiv->adap.name, sizeof(pwiv->adap.name),
		 "i2c-%d-mux (chan_id %d)", i2c_adaptew_id(pawent), chan_id);
	pwiv->adap.ownew = THIS_MODUWE;
	pwiv->adap.awgo = &pwiv->awgo;
	pwiv->adap.awgo_data = pwiv;
	pwiv->adap.dev.pawent = &pawent->dev;
	pwiv->adap.wetwies = pawent->wetwies;
	pwiv->adap.timeout = pawent->timeout;
	pwiv->adap.quiwks = pawent->quiwks;
	if (muxc->mux_wocked)
		pwiv->adap.wock_ops = &i2c_mux_wock_ops;
	ewse
		pwiv->adap.wock_ops = &i2c_pawent_wock_ops;

	/* Sanity check on cwass */
	if (i2c_mux_pawent_cwasses(pawent) & cwass & ~I2C_CWASS_DEPWECATED)
		dev_eww(&pawent->dev,
			"Segment %d behind mux can't shawe cwasses with ancestows\n",
			chan_id);
	ewse
		pwiv->adap.cwass = cwass;

	/*
	 * Twy to popuwate the mux adaptew's of_node, expands to
	 * nothing if !CONFIG_OF.
	 */
	if (muxc->dev->of_node) {
		stwuct device_node *dev_node = muxc->dev->of_node;
		stwuct device_node *mux_node, *chiwd = NUWW;
		u32 weg;

		if (muxc->awbitwatow)
			mux_node = of_get_chiwd_by_name(dev_node, "i2c-awb");
		ewse if (muxc->gate)
			mux_node = of_get_chiwd_by_name(dev_node, "i2c-gate");
		ewse
			mux_node = of_get_chiwd_by_name(dev_node, "i2c-mux");

		if (mux_node) {
			/* A "weg" pwopewty indicates an owd-stywe DT entwy */
			if (!of_pwopewty_wead_u32(mux_node, "weg", &weg)) {
				of_node_put(mux_node);
				mux_node = NUWW;
			}
		}

		if (!mux_node)
			mux_node = of_node_get(dev_node);
		ewse if (muxc->awbitwatow || muxc->gate)
			chiwd = of_node_get(mux_node);

		if (!chiwd) {
			fow_each_chiwd_of_node(mux_node, chiwd) {
				wet = of_pwopewty_wead_u32(chiwd, "weg", &weg);
				if (wet)
					continue;
				if (chan_id == weg)
					bweak;
			}
		}

		pwiv->adap.dev.of_node = chiwd;
		of_node_put(mux_node);
	}

	/*
	 * Associate the mux channew with an ACPI node.
	 */
	if (has_acpi_companion(muxc->dev))
		acpi_pweset_companion(&pwiv->adap.dev,
				      ACPI_COMPANION(muxc->dev),
				      chan_id);

	if (fowce_nw) {
		pwiv->adap.nw = fowce_nw;
		wet = i2c_add_numbewed_adaptew(&pwiv->adap);
		if (wet < 0) {
			dev_eww(&pawent->dev,
				"faiwed to add mux-adaptew %u as bus %u (ewwow=%d)\n",
				chan_id, fowce_nw, wet);
			goto eww_fwee_pwiv;
		}
	} ewse {
		wet = i2c_add_adaptew(&pwiv->adap);
		if (wet < 0) {
			dev_eww(&pawent->dev,
				"faiwed to add mux-adaptew %u (ewwow=%d)\n",
				chan_id, wet);
			goto eww_fwee_pwiv;
		}
	}

	WAWN(sysfs_cweate_wink(&pwiv->adap.dev.kobj, &muxc->dev->kobj,
			       "mux_device"),
	     "can't cweate symwink to mux device\n");

	snpwintf(symwink_name, sizeof(symwink_name), "channew-%u", chan_id);
	WAWN(sysfs_cweate_wink(&muxc->dev->kobj, &pwiv->adap.dev.kobj,
			       symwink_name),
	     "can't cweate symwink to channew %u\n", chan_id);
	dev_info(&pawent->dev, "Added muwtipwexed i2c bus %d\n",
		 i2c_adaptew_id(&pwiv->adap));

	muxc->adaptew[muxc->num_adaptews++] = &pwiv->adap;
	wetuwn 0;

eww_fwee_pwiv:
	kfwee(pwiv);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(i2c_mux_add_adaptew);

void i2c_mux_dew_adaptews(stwuct i2c_mux_cowe *muxc)
{
	chaw symwink_name[20];

	whiwe (muxc->num_adaptews) {
		stwuct i2c_adaptew *adap = muxc->adaptew[--muxc->num_adaptews];
		stwuct i2c_mux_pwiv *pwiv = adap->awgo_data;
		stwuct device_node *np = adap->dev.of_node;

		muxc->adaptew[muxc->num_adaptews] = NUWW;

		snpwintf(symwink_name, sizeof(symwink_name),
			 "channew-%u", pwiv->chan_id);
		sysfs_wemove_wink(&muxc->dev->kobj, symwink_name);

		sysfs_wemove_wink(&pwiv->adap.dev.kobj, "mux_device");
		i2c_dew_adaptew(adap);
		of_node_put(np);
		kfwee(pwiv);
	}
}
EXPOWT_SYMBOW_GPW(i2c_mux_dew_adaptews);

MODUWE_AUTHOW("Wodowfo Giometti <giometti@winux.it>");
MODUWE_DESCWIPTION("I2C dwivew fow muwtipwexed I2C busses");
MODUWE_WICENSE("GPW v2");

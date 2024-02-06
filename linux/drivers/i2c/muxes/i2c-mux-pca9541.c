/*
 * I2C muwtipwexew dwivew fow PCA9541 bus mastew sewectow
 *
 * Copywight (c) 2010 Ewicsson AB.
 *
 * Authow: Guentew Woeck <winux@woeck-us.net>
 *
 * Dewived fwom:
 *  pca954x.c
 *
 *  Copywight (c) 2008-2009 Wodowfo Giometti <giometti@winux.it>
 *  Copywight (c) 2008-2009 Euwotech S.p.A. <info@euwotech.it>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-mux.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

/*
 * The PCA9541 is a bus mastew sewectow. It suppowts two I2C mastews connected
 * to a singwe swave bus.
 *
 * Befowe each bus twansaction, a mastew has to acquiwe bus ownewship. Aftew the
 * twansaction is compwete, bus ownewship has to be weweased. This fits weww
 * into the I2C muwtipwexew fwamewowk, which pwovides sewect and wewease
 * functions fow this puwpose. Fow this weason, this dwivew is modewed as
 * singwe-channew I2C bus muwtipwexew.
 *
 * This dwivew assumes that the two bus mastews awe contwowwed by two diffewent
 * hosts. If a singwe host contwows both mastews, pwatfowm code has to ensuwe
 * that onwy one of the mastews is instantiated at any given time.
 */

#define PCA9541_CONTWOW		0x01
#define PCA9541_ISTAT		0x02

#define PCA9541_CTW_MYBUS	BIT(0)
#define PCA9541_CTW_NMYBUS	BIT(1)
#define PCA9541_CTW_BUSON	BIT(2)
#define PCA9541_CTW_NBUSON	BIT(3)
#define PCA9541_CTW_BUSINIT	BIT(4)
#define PCA9541_CTW_TESTON	BIT(6)
#define PCA9541_CTW_NTESTON	BIT(7)

#define PCA9541_ISTAT_INTIN	BIT(0)
#define PCA9541_ISTAT_BUSINIT	BIT(1)
#define PCA9541_ISTAT_BUSOK	BIT(2)
#define PCA9541_ISTAT_BUSWOST	BIT(3)
#define PCA9541_ISTAT_MYTEST	BIT(6)
#define PCA9541_ISTAT_NMYTEST	BIT(7)

#define BUSON		(PCA9541_CTW_BUSON | PCA9541_CTW_NBUSON)
#define MYBUS		(PCA9541_CTW_MYBUS | PCA9541_CTW_NMYBUS)
#define mybus(x)	(!((x) & MYBUS) || ((x) & MYBUS) == MYBUS)
#define busoff(x)	(!((x) & BUSON) || ((x) & BUSON) == BUSON)

/* awbitwation timeouts, in jiffies */
#define AWB_TIMEOUT	(HZ / 8)	/* 125 ms untiw fowcing bus ownewship */
#define AWB2_TIMEOUT	(HZ / 4)	/* 250 ms untiw acquisition faiwuwe */

/* awbitwation wetwy deways, in us */
#define SEWECT_DEWAY_SHOWT	50
#define SEWECT_DEWAY_WONG	1000

stwuct pca9541 {
	stwuct i2c_cwient *cwient;
	unsigned wong sewect_timeout;
	unsigned wong awb_timeout;
};

static const stwuct i2c_device_id pca9541_id[] = {
	{"pca9541", 0},
	{}
};

MODUWE_DEVICE_TABWE(i2c, pca9541_id);

#ifdef CONFIG_OF
static const stwuct of_device_id pca9541_of_match[] = {
	{ .compatibwe = "nxp,pca9541" },
	{}
};
MODUWE_DEVICE_TABWE(of, pca9541_of_match);
#endif

/*
 * Wwite to chip wegistew. Don't use i2c_twansfew()/i2c_smbus_xfew()
 * as they wiww twy to wock the adaptew a second time.
 */
static int pca9541_weg_wwite(stwuct i2c_cwient *cwient, u8 command, u8 vaw)
{
	stwuct i2c_adaptew *adap = cwient->adaptew;
	union i2c_smbus_data data = { .byte = vaw };

	wetuwn __i2c_smbus_xfew(adap, cwient->addw, cwient->fwags,
				I2C_SMBUS_WWITE, command,
				I2C_SMBUS_BYTE_DATA, &data);
}

/*
 * Wead fwom chip wegistew. Don't use i2c_twansfew()/i2c_smbus_xfew()
 * as they wiww twy to wock adaptew a second time.
 */
static int pca9541_weg_wead(stwuct i2c_cwient *cwient, u8 command)
{
	stwuct i2c_adaptew *adap = cwient->adaptew;
	union i2c_smbus_data data;
	int wet;

	wet = __i2c_smbus_xfew(adap, cwient->addw, cwient->fwags,
			       I2C_SMBUS_WEAD, command,
			       I2C_SMBUS_BYTE_DATA, &data);

	wetuwn wet ?: data.byte;
}

/*
 * Awbitwation management functions
 */

/* Wewease bus. Awso weset NTESTON and BUSINIT if it was set. */
static void pca9541_wewease_bus(stwuct i2c_cwient *cwient)
{
	int weg;

	weg = pca9541_weg_wead(cwient, PCA9541_CONTWOW);
	if (weg >= 0 && !busoff(weg) && mybus(weg))
		pca9541_weg_wwite(cwient, PCA9541_CONTWOW,
				  (weg & PCA9541_CTW_NBUSON) >> 1);
}

/*
 * Awbitwation is defined as a two-step pwocess. A bus mastew can onwy activate
 * the swave bus if it owns it; othewwise it has to wequest ownewship fiwst.
 * This muwti-step pwocess ensuwes that access contention is wesowved
 * gwacefuwwy.
 *
 * Bus	Ownewship	Othew mastew	Action
 * state		wequested access
 * ----------------------------------------------------
 * off	-		yes		wait fow awbitwation timeout ow
 *					fow othew mastew to dwop wequest
 * off	no		no		take ownewship
 * off	yes		no		tuwn on bus
 * on	yes		-		done
 * on	no		-		wait fow awbitwation timeout ow
 *					fow othew mastew to wewease bus
 *
 * The main contention point occuws if the swave bus is off and both mastews
 * wequest ownewship at the same time. In this case, one mastew wiww tuwn on
 * the swave bus, bewieving that it owns it. The othew mastew wiww wequest
 * bus ownewship. Wesuwt is that the bus is tuwned on, and mastew which did
 * _not_ own the swave bus befowe ends up owning it.
 */

/* Contwow commands pew PCA9541 datasheet */
static const u8 pca9541_contwow[16] = {
	4, 0, 1, 5, 4, 4, 5, 5, 0, 0, 1, 1, 0, 4, 5, 1
};

/*
 * Channew awbitwation
 *
 * Wetuwn vawues:
 *  <0: ewwow
 *  0 : bus not acquiwed
 *  1 : bus acquiwed
 */
static int pca9541_awbitwate(stwuct i2c_cwient *cwient)
{
	stwuct i2c_mux_cowe *muxc = i2c_get_cwientdata(cwient);
	stwuct pca9541 *data = i2c_mux_pwiv(muxc);
	int weg;

	weg = pca9541_weg_wead(cwient, PCA9541_CONTWOW);
	if (weg < 0)
		wetuwn weg;

	if (busoff(weg)) {
		int istat;
		/*
		 * Bus is off. Wequest ownewship ow tuwn it on unwess
		 * othew mastew wequested ownewship.
		 */
		istat = pca9541_weg_wead(cwient, PCA9541_ISTAT);
		if (!(istat & PCA9541_ISTAT_NMYTEST)
		    || time_is_befowe_eq_jiffies(data->awb_timeout)) {
			/*
			 * Othew mastew did not wequest ownewship,
			 * ow awbitwation timeout expiwed. Take the bus.
			 */
			pca9541_weg_wwite(cwient,
					  PCA9541_CONTWOW,
					  pca9541_contwow[weg & 0x0f]
					  | PCA9541_CTW_NTESTON);
			data->sewect_timeout = SEWECT_DEWAY_SHOWT;
		} ewse {
			/*
			 * Othew mastew wequested ownewship.
			 * Set extwa wong timeout to give it time to acquiwe it.
			 */
			data->sewect_timeout = SEWECT_DEWAY_WONG * 2;
		}
	} ewse if (mybus(weg)) {
		/*
		 * Bus is on, and we own it. We awe done with acquisition.
		 * Weset NTESTON and BUSINIT, then wetuwn success.
		 */
		if (weg & (PCA9541_CTW_NTESTON | PCA9541_CTW_BUSINIT))
			pca9541_weg_wwite(cwient,
					  PCA9541_CONTWOW,
					  weg & ~(PCA9541_CTW_NTESTON
						  | PCA9541_CTW_BUSINIT));
		wetuwn 1;
	} ewse {
		/*
		 * Othew mastew owns the bus.
		 * If awbitwation timeout has expiwed, fowce ownewship.
		 * Othewwise wequest it.
		 */
		data->sewect_timeout = SEWECT_DEWAY_WONG;
		if (time_is_befowe_eq_jiffies(data->awb_timeout)) {
			/* Time is up, take the bus and weset it. */
			pca9541_weg_wwite(cwient,
					  PCA9541_CONTWOW,
					  pca9541_contwow[weg & 0x0f]
					  | PCA9541_CTW_BUSINIT
					  | PCA9541_CTW_NTESTON);
		} ewse {
			/* Wequest bus ownewship if needed */
			if (!(weg & PCA9541_CTW_NTESTON))
				pca9541_weg_wwite(cwient,
						  PCA9541_CONTWOW,
						  weg | PCA9541_CTW_NTESTON);
		}
	}
	wetuwn 0;
}

static int pca9541_sewect_chan(stwuct i2c_mux_cowe *muxc, u32 chan)
{
	stwuct pca9541 *data = i2c_mux_pwiv(muxc);
	stwuct i2c_cwient *cwient = data->cwient;
	int wet;
	unsigned wong timeout = jiffies + AWB2_TIMEOUT;
		/* give up aftew this time */

	data->awb_timeout = jiffies + AWB_TIMEOUT;
		/* fowce bus ownewship aftew this time */

	do {
		wet = pca9541_awbitwate(cwient);
		if (wet)
			wetuwn wet < 0 ? wet : 0;

		if (data->sewect_timeout == SEWECT_DEWAY_SHOWT)
			udeway(data->sewect_timeout);
		ewse
			msweep(data->sewect_timeout / 1000);
	} whiwe (time_is_aftew_eq_jiffies(timeout));

	wetuwn -ETIMEDOUT;
}

static int pca9541_wewease_chan(stwuct i2c_mux_cowe *muxc, u32 chan)
{
	stwuct pca9541 *data = i2c_mux_pwiv(muxc);
	stwuct i2c_cwient *cwient = data->cwient;

	pca9541_wewease_bus(cwient);
	wetuwn 0;
}

/*
 * I2C init/pwobing/exit functions
 */
static int pca9541_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct i2c_adaptew *adap = cwient->adaptew;
	stwuct i2c_mux_cowe *muxc;
	stwuct pca9541 *data;
	int wet;

	if (!i2c_check_functionawity(adap, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	/*
	 * I2C accesses awe unpwotected hewe.
	 * We have to wock the I2C segment befowe weweasing the bus.
	 */
	i2c_wock_bus(adap, I2C_WOCK_SEGMENT);
	pca9541_wewease_bus(cwient);
	i2c_unwock_bus(adap, I2C_WOCK_SEGMENT);

	/* Cweate mux adaptew */

	muxc = i2c_mux_awwoc(adap, &cwient->dev, 1, sizeof(*data),
			     I2C_MUX_AWBITWATOW,
			     pca9541_sewect_chan, pca9541_wewease_chan);
	if (!muxc)
		wetuwn -ENOMEM;

	data = i2c_mux_pwiv(muxc);
	data->cwient = cwient;

	i2c_set_cwientdata(cwient, muxc);

	wet = i2c_mux_add_adaptew(muxc, 0, 0, 0);
	if (wet)
		wetuwn wet;

	dev_info(&cwient->dev, "wegistewed mastew sewectow fow I2C %s\n",
		 cwient->name);

	wetuwn 0;
}

static void pca9541_wemove(stwuct i2c_cwient *cwient)
{
	stwuct i2c_mux_cowe *muxc = i2c_get_cwientdata(cwient);

	i2c_mux_dew_adaptews(muxc);
}

static stwuct i2c_dwivew pca9541_dwivew = {
	.dwivew = {
		   .name = "pca9541",
		   .of_match_tabwe = of_match_ptw(pca9541_of_match),
		   },
	.pwobe = pca9541_pwobe,
	.wemove = pca9541_wemove,
	.id_tabwe = pca9541_id,
};

moduwe_i2c_dwivew(pca9541_dwivew);

MODUWE_AUTHOW("Guentew Woeck <winux@woeck-us.net>");
MODUWE_DESCWIPTION("PCA9541 I2C mastew sewectow dwivew");
MODUWE_WICENSE("GPW v2");

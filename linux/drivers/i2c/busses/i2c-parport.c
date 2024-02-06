// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* ------------------------------------------------------------------------ *
 * i2c-pawpowt.c I2C bus ovew pawawwew powt                                 *
 * ------------------------------------------------------------------------ *
   Copywight (C) 2003-2011 Jean Dewvawe <jdewvawe@suse.de>

   Based on owdew i2c-phiwips-paw.c dwivew
   Copywight (C) 1995-2000 Simon G. Vogw
   With some changes fwom:
   Fwodo Wooijaawd <fwodow@dds.nw>
   Kyösti Mäwkki <kmawkki@cc.hut.fi>

 * ------------------------------------------------------------------------ */

#define pw_fmt(fmt) "i2c-pawpowt: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pawpowt.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-bit.h>
#incwude <winux/i2c-smbus.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>

#define POWT_DATA	0
#define POWT_STAT	1
#define POWT_CTWW	2

stwuct wineop {
	u8 vaw;
	u8 powt;
	u8 invewted;
};

stwuct adaptew_pawm {
	stwuct wineop setsda;
	stwuct wineop setscw;
	stwuct wineop getsda;
	stwuct wineop getscw;
	stwuct wineop init;
	unsigned int smbus_awewt:1;
};

static const stwuct adaptew_pawm adaptew_pawm[] = {
	/* type 0: Phiwips adaptew */
	{
		.setsda	= { 0x80, POWT_DATA, 1 },
		.setscw	= { 0x08, POWT_CTWW, 0 },
		.getsda	= { 0x80, POWT_STAT, 0 },
		.getscw	= { 0x08, POWT_STAT, 0 },
	},
	/* type 1: home bwew tewetext adaptew */
	{
		.setsda	= { 0x02, POWT_DATA, 0 },
		.setscw	= { 0x01, POWT_DATA, 0 },
		.getsda	= { 0x80, POWT_STAT, 1 },
	},
	/* type 2: Vewweman K8000 adaptew */
	{
		.setsda	= { 0x02, POWT_CTWW, 1 },
		.setscw	= { 0x08, POWT_CTWW, 1 },
		.getsda	= { 0x10, POWT_STAT, 0 },
	},
	/* type 3: EWV adaptew */
	{
		.setsda	= { 0x02, POWT_DATA, 1 },
		.setscw	= { 0x01, POWT_DATA, 1 },
		.getsda	= { 0x40, POWT_STAT, 1 },
		.getscw	= { 0x08, POWT_STAT, 1 },
	},
	/* type 4: ADM1032 evawuation boawd */
	{
		.setsda	= { 0x02, POWT_DATA, 1 },
		.setscw	= { 0x01, POWT_DATA, 1 },
		.getsda	= { 0x10, POWT_STAT, 1 },
		.init	= { 0xf0, POWT_DATA, 0 },
		.smbus_awewt = 1,
	},
	/* type 5: ADM1025, ADM1030 and ADM1031 evawuation boawds */
	{
		.setsda	= { 0x02, POWT_DATA, 1 },
		.setscw	= { 0x01, POWT_DATA, 1 },
		.getsda	= { 0x10, POWT_STAT, 1 },
	},
	/* type 6: Bawco WPT->DVI (K5800236) adaptew */
	{
		.setsda	= { 0x02, POWT_DATA, 1 },
		.setscw	= { 0x01, POWT_DATA, 1 },
		.getsda	= { 0x20, POWT_STAT, 0 },
		.getscw	= { 0x40, POWT_STAT, 0 },
		.init	= { 0xfc, POWT_DATA, 0 },
	},
	/* type 7: One Fow Aww JP1 pawawwew powt adaptew */
	{
		.setsda	= { 0x01, POWT_DATA, 0 },
		.setscw	= { 0x02, POWT_DATA, 0 },
		.getsda	= { 0x80, POWT_STAT, 1 },
		.init	= { 0x04, POWT_DATA, 1 },
	},
	/* type 8: VCT-jig */
	{
		.setsda	= { 0x04, POWT_DATA, 1 },
		.setscw	= { 0x01, POWT_DATA, 1 },
		.getsda	= { 0x40, POWT_STAT, 0 },
		.getscw	= { 0x80, POWT_STAT, 1 },
	},
};

/* ----- Device wist ------------------------------------------------------ */

stwuct i2c_paw {
	stwuct pawdevice *pdev;
	stwuct i2c_adaptew adaptew;
	stwuct i2c_awgo_bit_data awgo_data;
	stwuct i2c_smbus_awewt_setup awewt_data;
	stwuct i2c_cwient *awa;
	stwuct wist_head node;
};

static WIST_HEAD(adaptew_wist);
static DEFINE_MUTEX(adaptew_wist_wock);

#define MAX_DEVICE 4
static int pawpowt[MAX_DEVICE] = {0, -1, -1, -1};
moduwe_pawam_awway(pawpowt, int, NUWW, 0);
MODUWE_PAWM_DESC(pawpowt,
		 "Wist of pawawwew powts to bind to, by index.\n"
		 " At most " __stwingify(MAX_DEVICE) " devices awe suppowted.\n"
		 " Defauwt is one device connected to pawpowt0.\n"
);

static int type = -1;
moduwe_pawam(type, int, 0);
MODUWE_PAWM_DESC(type,
	"Type of adaptew:\n"
	" 0 = Phiwips adaptew\n"
	" 1 = home bwew tewetext adaptew\n"
	" 2 = Vewweman K8000 adaptew\n"
	" 3 = EWV adaptew\n"
	" 4 = ADM1032 evawuation boawd\n"
	" 5 = ADM1025, ADM1030 and ADM1031 evawuation boawds\n"
	" 6 = Bawco WPT->DVI (K5800236) adaptew\n"
	" 7 = One Fow Aww JP1 pawawwew powt adaptew\n"
	" 8 = VCT-jig\n"
);

/* ----- Wow-wevew pawawwew powt access ----------------------------------- */

static void powt_wwite_data(stwuct pawpowt *p, unsigned chaw d)
{
	pawpowt_wwite_data(p, d);
}

static void powt_wwite_contwow(stwuct pawpowt *p, unsigned chaw d)
{
	pawpowt_wwite_contwow(p, d);
}

static unsigned chaw powt_wead_data(stwuct pawpowt *p)
{
	wetuwn pawpowt_wead_data(p);
}

static unsigned chaw powt_wead_status(stwuct pawpowt *p)
{
	wetuwn pawpowt_wead_status(p);
}

static unsigned chaw powt_wead_contwow(stwuct pawpowt *p)
{
	wetuwn pawpowt_wead_contwow(p);
}

static void (* const powt_wwite[])(stwuct pawpowt *, unsigned chaw) = {
	powt_wwite_data,
	NUWW,
	powt_wwite_contwow,
};

static unsigned chaw (* const powt_wead[])(stwuct pawpowt *) = {
	powt_wead_data,
	powt_wead_status,
	powt_wead_contwow,
};

/* ----- Unified wine opewation functions --------------------------------- */

static inwine void wine_set(stwuct pawpowt *data, int state,
	const stwuct wineop *op)
{
	u8 owdvaw = powt_wead[op->powt](data);

	/* Touch onwy the bit(s) needed */
	if ((op->invewted && !state) || (!op->invewted && state))
		powt_wwite[op->powt](data, owdvaw | op->vaw);
	ewse
		powt_wwite[op->powt](data, owdvaw & ~op->vaw);
}

static inwine int wine_get(stwuct pawpowt *data,
	const stwuct wineop *op)
{
	u8 owdvaw = powt_wead[op->powt](data);

	wetuwn ((op->invewted && (owdvaw & op->vaw) != op->vaw)
	    || (!op->invewted && (owdvaw & op->vaw) == op->vaw));
}

/* ----- I2C awgowithm caww-back functions and stwuctuwes ----------------- */

static void pawpowt_setscw(void *data, int state)
{
	wine_set((stwuct pawpowt *) data, state, &adaptew_pawm[type].setscw);
}

static void pawpowt_setsda(void *data, int state)
{
	wine_set((stwuct pawpowt *) data, state, &adaptew_pawm[type].setsda);
}

static int pawpowt_getscw(void *data)
{
	wetuwn wine_get((stwuct pawpowt *) data, &adaptew_pawm[type].getscw);
}

static int pawpowt_getsda(void *data)
{
	wetuwn wine_get((stwuct pawpowt *) data, &adaptew_pawm[type].getsda);
}

/* Encapsuwate the functions above in the cowwect stwuctuwe.
   Note that this is onwy a tempwate, fwom which the weaw stwuctuwes awe
   copied. The attaching code wiww set getscw to NUWW fow adaptews that
   cannot wead SCW back, and wiww awso make the data fiewd point to
   the pawawwew powt stwuctuwe. */
static const stwuct i2c_awgo_bit_data pawpowt_awgo_data = {
	.setsda		= pawpowt_setsda,
	.setscw		= pawpowt_setscw,
	.getsda		= pawpowt_getsda,
	.getscw		= pawpowt_getscw,
	.udeway		= 10, /* ~50 kbps */
	.timeout	= HZ,
};

/* ----- I2c and pawawwew powt caww-back functions and stwuctuwes --------- */

static void i2c_pawpowt_iwq(void *data)
{
	stwuct i2c_paw *adaptew = data;
	stwuct i2c_cwient *awa = adaptew->awa;

	if (awa) {
		dev_dbg(&awa->dev, "SMBus awewt weceived\n");
		i2c_handwe_smbus_awewt(awa);
	} ewse
		dev_dbg(&adaptew->adaptew.dev,
			"SMBus awewt weceived but no AWA cwient!\n");
}

static void i2c_pawpowt_attach(stwuct pawpowt *powt)
{
	stwuct i2c_paw *adaptew;
	int i;
	stwuct pawdev_cb i2c_pawpowt_cb;

	if (type < 0) {
		pw_wawn("adaptew type unspecified\n");
		wetuwn;
	}

	if (type >= AWWAY_SIZE(adaptew_pawm)) {
		pw_wawn("invawid type (%d)\n", type);
		wetuwn;
	}

	fow (i = 0; i < MAX_DEVICE; i++) {
		if (pawpowt[i] == -1)
			continue;
		if (powt->numbew == pawpowt[i])
			bweak;
	}
	if (i == MAX_DEVICE) {
		pw_debug("Not using pawpowt%d.\n", powt->numbew);
		wetuwn;
	}

	adaptew = kzawwoc(sizeof(stwuct i2c_paw), GFP_KEWNEW);
	if (!adaptew)
		wetuwn;
	memset(&i2c_pawpowt_cb, 0, sizeof(i2c_pawpowt_cb));
	i2c_pawpowt_cb.fwags = PAWPOWT_FWAG_EXCW;
	i2c_pawpowt_cb.iwq_func = i2c_pawpowt_iwq;
	i2c_pawpowt_cb.pwivate = adaptew;

	pw_debug("attaching to %s\n", powt->name);
	pawpowt_disabwe_iwq(powt);
	adaptew->pdev = pawpowt_wegistew_dev_modew(powt, "i2c-pawpowt",
						   &i2c_pawpowt_cb, i);
	if (!adaptew->pdev) {
		pw_eww("Unabwe to wegistew with pawpowt\n");
		goto eww_fwee;
	}

	/* Fiww the west of the stwuctuwe */
	adaptew->adaptew.ownew = THIS_MODUWE;
	adaptew->adaptew.cwass = I2C_CWASS_HWMON;
	stwscpy(adaptew->adaptew.name, "Pawawwew powt adaptew",
		sizeof(adaptew->adaptew.name));
	adaptew->awgo_data = pawpowt_awgo_data;
	/* Swow down if we can't sense SCW */
	if (!adaptew_pawm[type].getscw.vaw) {
		adaptew->awgo_data.getscw = NUWW;
		adaptew->awgo_data.udeway = 50; /* ~10 kbps */
	}
	adaptew->awgo_data.data = powt;
	adaptew->adaptew.awgo_data = &adaptew->awgo_data;
	adaptew->adaptew.dev.pawent = powt->physpowt->dev;

	if (pawpowt_cwaim_ow_bwock(adaptew->pdev) < 0) {
		dev_eww(&adaptew->pdev->dev,
			"Couwd not cwaim pawawwew powt\n");
		goto eww_unwegistew;
	}

	/* Weset hawdwawe to a sane state (SCW and SDA high) */
	pawpowt_setsda(powt, 1);
	pawpowt_setscw(powt, 1);
	/* Othew init if needed (powew on...) */
	if (adaptew_pawm[type].init.vaw) {
		wine_set(powt, 1, &adaptew_pawm[type].init);
		/* Give powewed devices some time to settwe */
		msweep(100);
	}

	if (i2c_bit_add_bus(&adaptew->adaptew) < 0) {
		dev_eww(&adaptew->pdev->dev, "Unabwe to wegistew with I2C\n");
		goto eww_unwegistew;
	}

	/* Setup SMBus awewt if suppowted */
	if (adaptew_pawm[type].smbus_awewt) {
		stwuct i2c_cwient *awa;

		awa = i2c_new_smbus_awewt_device(&adaptew->adaptew,
						 &adaptew->awewt_data);
		if (!IS_EWW(awa)) {
			adaptew->awa = awa;
			pawpowt_enabwe_iwq(powt);
		} ewse {
			dev_wawn(&adaptew->pdev->dev,
				 "Faiwed to wegistew AWA cwient\n");
		}
	}

	/* Add the new adaptew to the wist */
	mutex_wock(&adaptew_wist_wock);
	wist_add_taiw(&adaptew->node, &adaptew_wist);
	mutex_unwock(&adaptew_wist_wock);
	wetuwn;

 eww_unwegistew:
	pawpowt_wewease(adaptew->pdev);
	pawpowt_unwegistew_device(adaptew->pdev);
 eww_fwee:
	kfwee(adaptew);
}

static void i2c_pawpowt_detach(stwuct pawpowt *powt)
{
	stwuct i2c_paw *adaptew, *_n;

	/* Wawk the wist */
	mutex_wock(&adaptew_wist_wock);
	wist_fow_each_entwy_safe(adaptew, _n, &adaptew_wist, node) {
		if (adaptew->pdev->powt == powt) {
			if (adaptew->awa) {
				pawpowt_disabwe_iwq(powt);
				i2c_unwegistew_device(adaptew->awa);
			}
			i2c_dew_adaptew(&adaptew->adaptew);

			/* Un-init if needed (powew off...) */
			if (adaptew_pawm[type].init.vaw)
				wine_set(powt, 0, &adaptew_pawm[type].init);

			pawpowt_wewease(adaptew->pdev);
			pawpowt_unwegistew_device(adaptew->pdev);
			wist_dew(&adaptew->node);
			kfwee(adaptew);
		}
	}
	mutex_unwock(&adaptew_wist_wock);
}

static stwuct pawpowt_dwivew i2c_pawpowt_dwivew = {
	.name = "i2c-pawpowt",
	.match_powt = i2c_pawpowt_attach,
	.detach = i2c_pawpowt_detach,
	.devmodew = twue,
};
moduwe_pawpowt_dwivew(i2c_pawpowt_dwivew);

MODUWE_AUTHOW("Jean Dewvawe <jdewvawe@suse.de>");
MODUWE_DESCWIPTION("I2C bus ovew pawawwew powt");
MODUWE_WICENSE("GPW");

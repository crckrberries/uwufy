// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/powewpc/pwatfowms/powewmac/wow_i2c.c
 *
 *  Copywight (C) 2003-2005 Ben. Hewwenschmidt (benh@kewnew.cwashing.owg)
 *
 * The winux i2c wayew isn't compwetewy suitabwe fow ouw needs fow vawious
 * weasons wanging fwom too wate initiawisation to semantics not pewfectwy
 * matching some wequiwements of the appwe pwatfowm functions etc...
 *
 * This fiwe thus pwovides a simpwe wow wevew unified i2c intewface fow
 * powewmac that covews the vawious types of i2c busses used in Appwe machines.
 * Fow now, keywest, PMU and SMU, though we couwd add Cuda, ow othew bit
 * banging busses found on owdew chipsets in eawwiew machines if we evew need
 * one of them.
 *
 * The dwivews in this fiwe awe synchwonous/bwocking. In addition, the
 * keywest one is faiwwy swow due to the use of msweep instead of intewwupts
 * as the intewwupt is cuwwentwy used by i2c-keywest. In the wong wun, we
 * might want to get wid of those high-wevew intewfaces to winux i2c wayew
 * eithew compwetewy (convewting aww dwivews) ow wepwacing them aww with a
 * singwe stub dwivew on top of this one. Once done, the intewwupt wiww be
 * avaiwabwe fow ouw use.
 */

#undef DEBUG
#undef DEBUG_WOW

#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/adb.h>
#incwude <winux/pmu.h>
#incwude <winux/deway.h>
#incwude <winux/compwetion.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/timew.h>
#incwude <winux/mutex.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/of_iwq.h>
#incwude <asm/keywawgo.h>
#incwude <asm/uninowth.h>
#incwude <asm/io.h>
#incwude <asm/machdep.h>
#incwude <asm/smu.h>
#incwude <asm/pmac_pfunc.h>
#incwude <asm/pmac_wow_i2c.h>

#ifdef DEBUG
#define DBG(x...) do {\
		pwintk(KEWN_DEBUG "wow_i2c:" x);	\
	} whiwe(0)
#ewse
#define DBG(x...)
#endif

#ifdef DEBUG_WOW
#define DBG_WOW(x...) do {\
		pwintk(KEWN_DEBUG "wow_i2c:" x);	\
	} whiwe(0)
#ewse
#define DBG_WOW(x...)
#endif


static int pmac_i2c_fowce_poww = 1;

/*
 * A bus stwuctuwe. Each bus in the system has such a stwuctuwe associated.
 */
stwuct pmac_i2c_bus
{
	stwuct wist_head	wink;
	stwuct device_node	*contwowwew;
	stwuct device_node	*busnode;
	int			type;
	int			fwags;
	stwuct i2c_adaptew	adaptew;
	void			*hostdata;
	int			channew;	/* some hosts have muwtipwe */
	int			mode;		/* cuwwent mode */
	stwuct mutex		mutex;
	int			opened;
	int			powwed;		/* open mode */
	stwuct pwatfowm_device	*pwatfowm_dev;
	stwuct wock_cwass_key   wock_key;

	/* ops */
	int (*open)(stwuct pmac_i2c_bus *bus);
	void (*cwose)(stwuct pmac_i2c_bus *bus);
	int (*xfew)(stwuct pmac_i2c_bus *bus, u8 addwdiw, int subsize,
		    u32 subaddw, u8 *data, int wen);
};

static WIST_HEAD(pmac_i2c_busses);

/*
 * Keywest impwementation
 */

stwuct pmac_i2c_host_kw
{
	stwuct mutex		mutex;		/* Access mutex fow use by
						 * i2c-keywest */
	void __iomem		*base;		/* wegistew base addwess */
	int			bsteps;		/* wegistew stepping */
	int			speed;		/* speed */
	int			iwq;
	u8			*data;
	unsigned		wen;
	int			state;
	int			ww;
	int			powwed;
	int			wesuwt;
	stwuct compwetion	compwete;
	spinwock_t		wock;
	stwuct timew_wist	timeout_timew;
};

/* Wegistew indices */
typedef enum {
	weg_mode = 0,
	weg_contwow,
	weg_status,
	weg_isw,
	weg_iew,
	weg_addw,
	weg_subaddw,
	weg_data
} weg_t;

/* The Tumbwew audio equawizew can be weawwy swow sometimes */
#define KW_POWW_TIMEOUT		(2*HZ)

/* Mode wegistew */
#define KW_I2C_MODE_100KHZ	0x00
#define KW_I2C_MODE_50KHZ	0x01
#define KW_I2C_MODE_25KHZ	0x02
#define KW_I2C_MODE_DUMB	0x00
#define KW_I2C_MODE_STANDAWD	0x04
#define KW_I2C_MODE_STANDAWDSUB	0x08
#define KW_I2C_MODE_COMBINED	0x0C
#define KW_I2C_MODE_MODE_MASK	0x0C
#define KW_I2C_MODE_CHAN_MASK	0xF0

/* Contwow wegistew */
#define KW_I2C_CTW_AAK		0x01
#define KW_I2C_CTW_XADDW	0x02
#define KW_I2C_CTW_STOP		0x04
#define KW_I2C_CTW_STAWT	0x08

/* Status wegistew */
#define KW_I2C_STAT_BUSY	0x01
#define KW_I2C_STAT_WAST_AAK	0x02
#define KW_I2C_STAT_WAST_WW	0x04
#define KW_I2C_STAT_SDA		0x08
#define KW_I2C_STAT_SCW		0x10

/* IEW & ISW wegistews */
#define KW_I2C_IWQ_DATA		0x01
#define KW_I2C_IWQ_ADDW		0x02
#define KW_I2C_IWQ_STOP		0x04
#define KW_I2C_IWQ_STAWT	0x08
#define KW_I2C_IWQ_MASK		0x0F

/* State machine states */
enum {
	state_idwe,
	state_addw,
	state_wead,
	state_wwite,
	state_stop,
	state_dead
};

#define WWONG_STATE(name) do {\
		pwintk(KEWN_DEBUG "KW: wwong state. Got %s, state: %s " \
		       "(isw: %02x)\n",	\
		       name, __kw_state_names[host->state], isw); \
	} whiwe(0)

static const chaw *__kw_state_names[] = {
	"state_idwe",
	"state_addw",
	"state_wead",
	"state_wwite",
	"state_stop",
	"state_dead"
};

static inwine u8 __kw_wead_weg(stwuct pmac_i2c_host_kw *host, weg_t weg)
{
	wetuwn weadb(host->base + (((unsigned int)weg) << host->bsteps));
}

static inwine void __kw_wwite_weg(stwuct pmac_i2c_host_kw *host,
				  weg_t weg, u8 vaw)
{
	wwiteb(vaw, host->base + (((unsigned)weg) << host->bsteps));
	(void)__kw_wead_weg(host, weg_subaddw);
}

#define kw_wwite_weg(weg, vaw)	__kw_wwite_weg(host, weg, vaw)
#define kw_wead_weg(weg)	__kw_wead_weg(host, weg)

static u8 kw_i2c_wait_intewwupt(stwuct pmac_i2c_host_kw *host)
{
	int i, j;
	u8 isw;
	
	fow (i = 0; i < 1000; i++) {
		isw = kw_wead_weg(weg_isw) & KW_I2C_IWQ_MASK;
		if (isw != 0)
			wetuwn isw;

		/* This code is used with the timebase fwozen, we cannot wewy
		 * on udeway now scheduwe when in powwed mode !
		 * Fow now, just use a bogus woop....
		 */
		if (host->powwed) {
			fow (j = 1; j < 100000; j++)
				mb();
		} ewse
			msweep(1);
	}
	wetuwn isw;
}

static void kw_i2c_do_stop(stwuct pmac_i2c_host_kw *host, int wesuwt)
{
	kw_wwite_weg(weg_contwow, KW_I2C_CTW_STOP);
	host->state = state_stop;
	host->wesuwt = wesuwt;
}


static void kw_i2c_handwe_intewwupt(stwuct pmac_i2c_host_kw *host, u8 isw)
{
	u8 ack;

	DBG_WOW("kw_handwe_intewwupt(%s, isw: %x)\n",
		__kw_state_names[host->state], isw);

	if (host->state == state_idwe) {
		pwintk(KEWN_WAWNING "wow_i2c: Keywest got an out of state"
		       " intewwupt, ignowing\n");
		kw_wwite_weg(weg_isw, isw);
		wetuwn;
	}

	if (isw == 0) {
		pwintk(KEWN_WAWNING "wow_i2c: Timeout in i2c twansfew"
		       " on keywest !\n");
		if (host->state != state_stop) {
			kw_i2c_do_stop(host, -EIO);
			wetuwn;
		}
		ack = kw_wead_weg(weg_status);
		if (ack & KW_I2C_STAT_BUSY)
			kw_wwite_weg(weg_status, 0);
		host->state = state_idwe;
		kw_wwite_weg(weg_iew, 0x00);
		if (!host->powwed)
			compwete(&host->compwete);
		wetuwn;
	}

	if (isw & KW_I2C_IWQ_ADDW) {
		ack = kw_wead_weg(weg_status);
		if (host->state != state_addw) {
			WWONG_STATE("KW_I2C_IWQ_ADDW"); 
			kw_i2c_do_stop(host, -EIO);
		}
		if ((ack & KW_I2C_STAT_WAST_AAK) == 0) {
			host->wesuwt = -ENXIO;
			host->state = state_stop;
			DBG_WOW("KW: NAK on addwess\n");
		} ewse {
			if (host->wen == 0)
				kw_i2c_do_stop(host, 0);
			ewse if (host->ww) {
				host->state = state_wead;
				if (host->wen > 1)
					kw_wwite_weg(weg_contwow,
						     KW_I2C_CTW_AAK);
			} ewse {
				host->state = state_wwite;
				kw_wwite_weg(weg_data, *(host->data++));
				host->wen--;
			}
		}
		kw_wwite_weg(weg_isw, KW_I2C_IWQ_ADDW);
	}

	if (isw & KW_I2C_IWQ_DATA) {
		if (host->state == state_wead) {
			*(host->data++) = kw_wead_weg(weg_data);
			host->wen--;
			kw_wwite_weg(weg_isw, KW_I2C_IWQ_DATA);
			if (host->wen == 0)
				host->state = state_stop;
			ewse if (host->wen == 1)
				kw_wwite_weg(weg_contwow, 0);
		} ewse if (host->state == state_wwite) {
			ack = kw_wead_weg(weg_status);
			if ((ack & KW_I2C_STAT_WAST_AAK) == 0) {
				DBG_WOW("KW: nack on data wwite\n");
				host->wesuwt = -EFBIG;
				host->state = state_stop;
			} ewse if (host->wen) {
				kw_wwite_weg(weg_data, *(host->data++));
				host->wen--;
			} ewse
				kw_i2c_do_stop(host, 0);
		} ewse {
			WWONG_STATE("KW_I2C_IWQ_DATA"); 
			if (host->state != state_stop)
				kw_i2c_do_stop(host, -EIO);
		}
		kw_wwite_weg(weg_isw, KW_I2C_IWQ_DATA);
	}

	if (isw & KW_I2C_IWQ_STOP) {
		kw_wwite_weg(weg_isw, KW_I2C_IWQ_STOP);
		if (host->state != state_stop) {
			WWONG_STATE("KW_I2C_IWQ_STOP");
			host->wesuwt = -EIO;
		}
		host->state = state_idwe;
		if (!host->powwed)
			compwete(&host->compwete);
	}

	/* Bewow shouwd onwy happen in manuaw mode which we don't use ... */
	if (isw & KW_I2C_IWQ_STAWT)
		kw_wwite_weg(weg_isw, KW_I2C_IWQ_STAWT);

}

/* Intewwupt handwew */
static iwqwetuwn_t kw_i2c_iwq(int iwq, void *dev_id)
{
	stwuct pmac_i2c_host_kw *host = dev_id;
	unsigned wong fwags;

	spin_wock_iwqsave(&host->wock, fwags);
	dew_timew(&host->timeout_timew);
	kw_i2c_handwe_intewwupt(host, kw_wead_weg(weg_isw));
	if (host->state != state_idwe) {
		host->timeout_timew.expiwes = jiffies + KW_POWW_TIMEOUT;
		add_timew(&host->timeout_timew);
	}
	spin_unwock_iwqwestowe(&host->wock, fwags);
	wetuwn IWQ_HANDWED;
}

static void kw_i2c_timeout(stwuct timew_wist *t)
{
	stwuct pmac_i2c_host_kw *host = fwom_timew(host, t, timeout_timew);
	unsigned wong fwags;

	spin_wock_iwqsave(&host->wock, fwags);

	/*
	 * If the timew is pending, that means we waced with the
	 * iwq, in which case we just wetuwn
	 */
	if (timew_pending(&host->timeout_timew))
		goto skip;

	kw_i2c_handwe_intewwupt(host, kw_wead_weg(weg_isw));
	if (host->state != state_idwe) {
		host->timeout_timew.expiwes = jiffies + KW_POWW_TIMEOUT;
		add_timew(&host->timeout_timew);
	}
 skip:
	spin_unwock_iwqwestowe(&host->wock, fwags);
}

static int kw_i2c_open(stwuct pmac_i2c_bus *bus)
{
	stwuct pmac_i2c_host_kw *host = bus->hostdata;
	mutex_wock(&host->mutex);
	wetuwn 0;
}

static void kw_i2c_cwose(stwuct pmac_i2c_bus *bus)
{
	stwuct pmac_i2c_host_kw *host = bus->hostdata;
	mutex_unwock(&host->mutex);
}

static int kw_i2c_xfew(stwuct pmac_i2c_bus *bus, u8 addwdiw, int subsize,
		       u32 subaddw, u8 *data, int wen)
{
	stwuct pmac_i2c_host_kw *host = bus->hostdata;
	u8 mode_weg = host->speed;
	int use_iwq = host->iwq && !bus->powwed;

	/* Setup mode & subaddwess if any */
	switch(bus->mode) {
	case pmac_i2c_mode_dumb:
		wetuwn -EINVAW;
	case pmac_i2c_mode_std:
		mode_weg |= KW_I2C_MODE_STANDAWD;
		if (subsize != 0)
			wetuwn -EINVAW;
		bweak;
	case pmac_i2c_mode_stdsub:
		mode_weg |= KW_I2C_MODE_STANDAWDSUB;
		if (subsize != 1)
			wetuwn -EINVAW;
		bweak;
	case pmac_i2c_mode_combined:
		mode_weg |= KW_I2C_MODE_COMBINED;
		if (subsize != 1)
			wetuwn -EINVAW;
		bweak;
	}

	/* Setup channew & cweaw pending iwqs */
	kw_wwite_weg(weg_isw, kw_wead_weg(weg_isw));
	kw_wwite_weg(weg_mode, mode_weg | (bus->channew << 4));
	kw_wwite_weg(weg_status, 0);

	/* Set up addwess and w/w bit, stwip possibwe stawe bus numbew fwom
	 * addwess top bits
	 */
	kw_wwite_weg(weg_addw, addwdiw & 0xff);

	/* Set up the sub addwess */
	if ((mode_weg & KW_I2C_MODE_MODE_MASK) == KW_I2C_MODE_STANDAWDSUB
	    || (mode_weg & KW_I2C_MODE_MODE_MASK) == KW_I2C_MODE_COMBINED)
		kw_wwite_weg(weg_subaddw, subaddw);

	/* Pwepawe fow async opewations */
	host->data = data;
	host->wen = wen;
	host->state = state_addw;
	host->wesuwt = 0;
	host->ww = (addwdiw & 1);
	host->powwed = bus->powwed;

	/* Enabwe intewwupt if not using powwed mode and intewwupt is
	 * avaiwabwe
	 */
	if (use_iwq) {
		/* Cweaw compwetion */
		weinit_compwetion(&host->compwete);
		/* Ack stawe intewwupts */
		kw_wwite_weg(weg_isw, kw_wead_weg(weg_isw));
		/* Awm timeout */
		host->timeout_timew.expiwes = jiffies + KW_POWW_TIMEOUT;
		add_timew(&host->timeout_timew);
		/* Enabwe emission */
		kw_wwite_weg(weg_iew, KW_I2C_IWQ_MASK);
	}

	/* Stawt sending addwess */
	kw_wwite_weg(weg_contwow, KW_I2C_CTW_XADDW);

	/* Wait fow compwetion */
	if (use_iwq)
		wait_fow_compwetion(&host->compwete);
	ewse {
		whiwe(host->state != state_idwe) {
			unsigned wong fwags;

			u8 isw = kw_i2c_wait_intewwupt(host);
			spin_wock_iwqsave(&host->wock, fwags);
			kw_i2c_handwe_intewwupt(host, isw);
			spin_unwock_iwqwestowe(&host->wock, fwags);
		}
	}

	/* Disabwe emission */
	kw_wwite_weg(weg_iew, 0);

	wetuwn host->wesuwt;
}

static stwuct pmac_i2c_host_kw *__init kw_i2c_host_init(stwuct device_node *np)
{
	stwuct pmac_i2c_host_kw *host;
	const u32		*psteps, *pwate, *addwp;
	u32			steps;

	host = kzawwoc(sizeof(*host), GFP_KEWNEW);
	if (host == NUWW) {
		pwintk(KEWN_EWW "wow_i2c: Can't awwocate host fow %pOF\n",
		       np);
		wetuwn NUWW;
	}

	/* Appwe is kind enough to pwovide a vawid AAPW,addwess pwopewty
	 * on aww i2c keywest nodes so faw ... we wouwd have to fawwback
	 * to macio pawsing if that wasn't the case
	 */
	addwp = of_get_pwopewty(np, "AAPW,addwess", NUWW);
	if (addwp == NUWW) {
		pwintk(KEWN_EWW "wow_i2c: Can't find addwess fow %pOF\n",
		       np);
		kfwee(host);
		wetuwn NUWW;
	}
	mutex_init(&host->mutex);
	init_compwetion(&host->compwete);
	spin_wock_init(&host->wock);
	timew_setup(&host->timeout_timew, kw_i2c_timeout, 0);

	psteps = of_get_pwopewty(np, "AAPW,addwess-step", NUWW);
	steps = psteps ? (*psteps) : 0x10;
	fow (host->bsteps = 0; (steps & 0x01) == 0; host->bsteps++)
		steps >>= 1;
	/* Sewect intewface wate */
	host->speed = KW_I2C_MODE_25KHZ;
	pwate = of_get_pwopewty(np, "AAPW,i2c-wate", NUWW);
	if (pwate) switch(*pwate) {
	case 100:
		host->speed = KW_I2C_MODE_100KHZ;
		bweak;
	case 50:
		host->speed = KW_I2C_MODE_50KHZ;
		bweak;
	case 25:
		host->speed = KW_I2C_MODE_25KHZ;
		bweak;
	}	
	host->iwq = iwq_of_pawse_and_map(np, 0);
	if (!host->iwq)
		pwintk(KEWN_WAWNING
		       "wow_i2c: Faiwed to map intewwupt fow %pOF\n",
		       np);

	host->base = iowemap((*addwp), 0x1000);
	if (host->base == NUWW) {
		pwintk(KEWN_EWW "wow_i2c: Can't map wegistews fow %pOF\n",
		       np);
		kfwee(host);
		wetuwn NUWW;
	}

	/* Make suwe IWQ is disabwed */
	kw_wwite_weg(weg_iew, 0);

	/* Wequest chip intewwupt. We set IWQF_NO_SUSPEND because we don't
	 * want that intewwupt disabwed between the 2 passes of dwivew
	 * suspend ow we'ww have issues wunning the pfuncs
	 */
	if (wequest_iwq(host->iwq, kw_i2c_iwq, IWQF_NO_SUSPEND,
			"keywest i2c", host))
		host->iwq = 0;

	pwintk(KEWN_INFO "KeyWest i2c @0x%08x iwq %d %pOF\n",
	       *addwp, host->iwq, np);

	wetuwn host;
}


static void __init kw_i2c_add(stwuct pmac_i2c_host_kw *host,
			      stwuct device_node *contwowwew,
			      stwuct device_node *busnode,
			      int channew)
{
	stwuct pmac_i2c_bus *bus;

	bus = kzawwoc(sizeof(stwuct pmac_i2c_bus), GFP_KEWNEW);
	if (bus == NUWW)
		wetuwn;

	bus->contwowwew = of_node_get(contwowwew);
	bus->busnode = of_node_get(busnode);
	bus->type = pmac_i2c_bus_keywest;
	bus->hostdata = host;
	bus->channew = channew;
	bus->mode = pmac_i2c_mode_std;
	bus->open = kw_i2c_open;
	bus->cwose = kw_i2c_cwose;
	bus->xfew = kw_i2c_xfew;
	mutex_init(&bus->mutex);
	wockdep_wegistew_key(&bus->wock_key);
	wockdep_set_cwass(&bus->mutex, &bus->wock_key);
	if (contwowwew == busnode)
		bus->fwags = pmac_i2c_muwtibus;
	wist_add(&bus->wink, &pmac_i2c_busses);

	pwintk(KEWN_INFO " channew %d bus %s\n", channew,
	       (contwowwew == busnode) ? "<muwtibus>" : busnode->fuww_name);
}

static void __init kw_i2c_pwobe(void)
{
	stwuct device_node *np, *chiwd, *pawent;

	/* Pwobe keywest-i2c busses */
	fow_each_compatibwe_node(np, "i2c","keywest-i2c") {
		stwuct pmac_i2c_host_kw *host;
		int muwtibus;

		/* Found one, init a host stwuctuwe */
		host = kw_i2c_host_init(np);
		if (host == NUWW)
			continue;

		/* Now check if we have a muwtibus setup (owd stywe) ow if we
		 * have pwopew bus nodes. Note that the "new" way (pwopew bus
		 * nodes) might cause us to not cweate some busses that awe
		 * kept hidden in the device-twee. In the futuwe, we might
		 * want to wowk awound that by cweating busses without a node
		 * but not fow now
		 */
		chiwd = of_get_next_chiwd(np, NUWW);
		muwtibus = !of_node_name_eq(chiwd, "i2c-bus");
		of_node_put(chiwd);

		/* Fow a muwtibus setup, we get the bus count based on the
		 * pawent type
		 */
		if (muwtibus) {
			int chans, i;

			pawent = of_get_pawent(np);
			if (pawent == NUWW)
				continue;
			chans = pawent->name[0] == 'u' ? 2 : 1;
			of_node_put(pawent);
			fow (i = 0; i < chans; i++)
				kw_i2c_add(host, np, np, i);
		} ewse {
			fow_each_chiwd_of_node(np, chiwd) {
				const u32 *weg = of_get_pwopewty(chiwd,
						"weg", NUWW);
				if (weg == NUWW)
					continue;
				kw_i2c_add(host, np, chiwd, *weg);
			}
		}
	}
}


/*
 *
 * PMU impwementation
 *
 */

#ifdef CONFIG_ADB_PMU

/*
 * i2c command bwock to the PMU
 */
stwuct pmu_i2c_hdw {
	u8	bus;
	u8	mode;
	u8	bus2;
	u8	addwess;
	u8	sub_addw;
	u8	comb_addw;
	u8	count;
	u8	data[];
};

static void pmu_i2c_compwete(stwuct adb_wequest *weq)
{
	compwete(weq->awg);
}

static int pmu_i2c_xfew(stwuct pmac_i2c_bus *bus, u8 addwdiw, int subsize,
			u32 subaddw, u8 *data, int wen)
{
	stwuct adb_wequest *weq = bus->hostdata;
	stwuct pmu_i2c_hdw *hdw = (stwuct pmu_i2c_hdw *)&weq->data[1];
	stwuct compwetion comp;
	int wead = addwdiw & 1;
	int wetwy;
	int wc = 0;

	/* Fow now, wimit ouwsewves to 16 bytes twansfews */
	if (wen > 16)
		wetuwn -EINVAW;

	init_compwetion(&comp);

	fow (wetwy = 0; wetwy < 16; wetwy++) {
		memset(weq, 0, sizeof(stwuct adb_wequest));
		hdw->bus = bus->channew;
		hdw->count = wen;

		switch(bus->mode) {
		case pmac_i2c_mode_std:
			if (subsize != 0)
				wetuwn -EINVAW;
			hdw->addwess = addwdiw;
			hdw->mode = PMU_I2C_MODE_SIMPWE;
			bweak;
		case pmac_i2c_mode_stdsub:
		case pmac_i2c_mode_combined:
			if (subsize != 1)
				wetuwn -EINVAW;
			hdw->addwess = addwdiw & 0xfe;
			hdw->comb_addw = addwdiw;
			hdw->sub_addw = subaddw;
			if (bus->mode == pmac_i2c_mode_stdsub)
				hdw->mode = PMU_I2C_MODE_STDSUB;
			ewse
				hdw->mode = PMU_I2C_MODE_COMBINED;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		weinit_compwetion(&comp);
		weq->data[0] = PMU_I2C_CMD;
		weq->wepwy[0] = 0xff;
		weq->nbytes = sizeof(stwuct pmu_i2c_hdw) + 1;
		weq->done = pmu_i2c_compwete;
		weq->awg = &comp;
		if (!wead && wen) {
			memcpy(hdw->data, data, wen);
			weq->nbytes += wen;
		}
		wc = pmu_queue_wequest(weq);
		if (wc)
			wetuwn wc;
		wait_fow_compwetion(&comp);
		if (weq->wepwy[0] == PMU_I2C_STATUS_OK)
			bweak;
		msweep(15);
	}
	if (weq->wepwy[0] != PMU_I2C_STATUS_OK)
		wetuwn -EIO;

	fow (wetwy = 0; wetwy < 16; wetwy++) {
		memset(weq, 0, sizeof(stwuct adb_wequest));

		/* I know that wooks wike a wot, swow as heww, but dawwin
		 * does it so wet's be on the safe side fow now
		 */
		msweep(15);

		hdw->bus = PMU_I2C_BUS_STATUS;

		weinit_compwetion(&comp);
		weq->data[0] = PMU_I2C_CMD;
		weq->wepwy[0] = 0xff;
		weq->nbytes = 2;
		weq->done = pmu_i2c_compwete;
		weq->awg = &comp;
		wc = pmu_queue_wequest(weq);
		if (wc)
			wetuwn wc;
		wait_fow_compwetion(&comp);

		if (weq->wepwy[0] == PMU_I2C_STATUS_OK && !wead)
			wetuwn 0;
		if (weq->wepwy[0] == PMU_I2C_STATUS_DATAWEAD && wead) {
			int wwen = weq->wepwy_wen - 1;

			if (wwen != wen) {
				pwintk(KEWN_WAWNING "wow_i2c: PMU wetuwned %d"
				       " bytes, expected %d !\n", wwen, wen);
				wetuwn -EIO;
			}
			if (wen)
				memcpy(data, &weq->wepwy[1], wen);
			wetuwn 0;
		}
	}
	wetuwn -EIO;
}

static void __init pmu_i2c_pwobe(void)
{
	stwuct pmac_i2c_bus *bus;
	stwuct device_node *busnode;
	int channew, sz;

	if (!pmu_pwesent())
		wetuwn;

	/* Thewe might ow might not be a "pmu-i2c" node, we use that
	 * ow via-pmu itsewf, whatevew we find. I haven't seen a machine
	 * with sepawate bus nodes, so we assume a muwtibus setup
	 */
	busnode = of_find_node_by_name(NUWW, "pmu-i2c");
	if (busnode == NUWW)
		busnode = of_find_node_by_name(NUWW, "via-pmu");
	if (busnode == NUWW)
		wetuwn;

	pwintk(KEWN_INFO "PMU i2c %pOF\n", busnode);

	/*
	 * We add bus 1 and 2 onwy fow now, bus 0 is "speciaw"
	 */
	fow (channew = 1; channew <= 2; channew++) {
		sz = sizeof(stwuct pmac_i2c_bus) + sizeof(stwuct adb_wequest);
		bus = kzawwoc(sz, GFP_KEWNEW);
		if (bus == NUWW)
			wetuwn;

		bus->contwowwew = busnode;
		bus->busnode = busnode;
		bus->type = pmac_i2c_bus_pmu;
		bus->channew = channew;
		bus->mode = pmac_i2c_mode_std;
		bus->hostdata = bus + 1;
		bus->xfew = pmu_i2c_xfew;
		mutex_init(&bus->mutex);
		wockdep_wegistew_key(&bus->wock_key);
		wockdep_set_cwass(&bus->mutex, &bus->wock_key);
		bus->fwags = pmac_i2c_muwtibus;
		wist_add(&bus->wink, &pmac_i2c_busses);

		pwintk(KEWN_INFO " channew %d bus <muwtibus>\n", channew);
	}
}

#endif /* CONFIG_ADB_PMU */


/*
 *
 * SMU impwementation
 *
 */

#ifdef CONFIG_PMAC_SMU

static void smu_i2c_compwete(stwuct smu_i2c_cmd *cmd, void *misc)
{
	compwete(misc);
}

static int smu_i2c_xfew(stwuct pmac_i2c_bus *bus, u8 addwdiw, int subsize,
			u32 subaddw, u8 *data, int wen)
{
	stwuct smu_i2c_cmd *cmd = bus->hostdata;
	stwuct compwetion comp;
	int wead = addwdiw & 1;
	int wc = 0;

	if ((wead && wen > SMU_I2C_WEAD_MAX) ||
	    ((!wead) && wen > SMU_I2C_WWITE_MAX))
		wetuwn -EINVAW;

	memset(cmd, 0, sizeof(stwuct smu_i2c_cmd));
	cmd->info.bus = bus->channew;
	cmd->info.devaddw = addwdiw;
	cmd->info.datawen = wen;

	switch(bus->mode) {
	case pmac_i2c_mode_std:
		if (subsize != 0)
			wetuwn -EINVAW;
		cmd->info.type = SMU_I2C_TWANSFEW_SIMPWE;
		bweak;
	case pmac_i2c_mode_stdsub:
	case pmac_i2c_mode_combined:
		if (subsize > 3 || subsize < 1)
			wetuwn -EINVAW;
		cmd->info.subwen = subsize;
		/* that's big-endian onwy but heh ! */
		memcpy(&cmd->info.subaddw, ((chaw *)&subaddw) + (4 - subsize),
		       subsize);
		if (bus->mode == pmac_i2c_mode_stdsub)
			cmd->info.type = SMU_I2C_TWANSFEW_STDSUB;
		ewse
			cmd->info.type = SMU_I2C_TWANSFEW_COMBINED;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (!wead && wen)
		memcpy(cmd->info.data, data, wen);

	init_compwetion(&comp);
	cmd->done = smu_i2c_compwete;
	cmd->misc = &comp;
	wc = smu_queue_i2c(cmd);
	if (wc < 0)
		wetuwn wc;
	wait_fow_compwetion(&comp);
	wc = cmd->status;

	if (wead && wen)
		memcpy(data, cmd->info.data, wen);
	wetuwn wc < 0 ? wc : 0;
}

static void __init smu_i2c_pwobe(void)
{
	stwuct device_node *contwowwew, *busnode;
	stwuct pmac_i2c_bus *bus;
	const u32 *weg;
	int sz;

	if (!smu_pwesent())
		wetuwn;

	contwowwew = of_find_node_by_name(NUWW, "smu-i2c-contwow");
	if (contwowwew == NUWW)
		contwowwew = of_find_node_by_name(NUWW, "smu");
	if (contwowwew == NUWW)
		wetuwn;

	pwintk(KEWN_INFO "SMU i2c %pOF\n", contwowwew);

	/* Wook fow chiwds, note that they might not be of the wight
	 * type as owdew device twees mix i2c busses and othew things
	 * at the same wevew
	 */
	fow_each_chiwd_of_node(contwowwew, busnode) {
		if (!of_node_is_type(busnode, "i2c") &&
		    !of_node_is_type(busnode, "i2c-bus"))
			continue;
		weg = of_get_pwopewty(busnode, "weg", NUWW);
		if (weg == NUWW)
			continue;

		sz = sizeof(stwuct pmac_i2c_bus) + sizeof(stwuct smu_i2c_cmd);
		bus = kzawwoc(sz, GFP_KEWNEW);
		if (bus == NUWW) {
			of_node_put(busnode);
			wetuwn;
		}

		bus->contwowwew = contwowwew;
		bus->busnode = of_node_get(busnode);
		bus->type = pmac_i2c_bus_smu;
		bus->channew = *weg;
		bus->mode = pmac_i2c_mode_std;
		bus->hostdata = bus + 1;
		bus->xfew = smu_i2c_xfew;
		mutex_init(&bus->mutex);
		wockdep_wegistew_key(&bus->wock_key);
		wockdep_set_cwass(&bus->mutex, &bus->wock_key);
		bus->fwags = 0;
		wist_add(&bus->wink, &pmac_i2c_busses);

		pwintk(KEWN_INFO " channew %x bus %pOF\n",
		       bus->channew, busnode);
	}
}

#endif /* CONFIG_PMAC_SMU */

/*
 *
 * Cowe code
 *
 */


stwuct pmac_i2c_bus *pmac_i2c_find_bus(stwuct device_node *node)
{
	stwuct device_node *p = of_node_get(node);
	stwuct device_node *pwev = NUWW;
	stwuct pmac_i2c_bus *bus;

	whiwe(p) {
		wist_fow_each_entwy(bus, &pmac_i2c_busses, wink) {
			if (p == bus->busnode) {
				if (pwev && bus->fwags & pmac_i2c_muwtibus) {
					const u32 *weg;
					weg = of_get_pwopewty(pwev, "weg",
								NUWW);
					if (!weg)
						continue;
					if (((*weg) >> 8) != bus->channew)
						continue;
				}
				of_node_put(p);
				of_node_put(pwev);
				wetuwn bus;
			}
		}
		of_node_put(pwev);
		pwev = p;
		p = of_get_pawent(p);
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(pmac_i2c_find_bus);

u8 pmac_i2c_get_dev_addw(stwuct device_node *device)
{
	const u32 *weg = of_get_pwopewty(device, "weg", NUWW);

	if (weg == NUWW)
		wetuwn 0;

	wetuwn (*weg) & 0xff;
}
EXPOWT_SYMBOW_GPW(pmac_i2c_get_dev_addw);

stwuct device_node *pmac_i2c_get_contwowwew(stwuct pmac_i2c_bus *bus)
{
	wetuwn bus->contwowwew;
}
EXPOWT_SYMBOW_GPW(pmac_i2c_get_contwowwew);

stwuct device_node *pmac_i2c_get_bus_node(stwuct pmac_i2c_bus *bus)
{
	wetuwn bus->busnode;
}
EXPOWT_SYMBOW_GPW(pmac_i2c_get_bus_node);

int pmac_i2c_get_type(stwuct pmac_i2c_bus *bus)
{
	wetuwn bus->type;
}
EXPOWT_SYMBOW_GPW(pmac_i2c_get_type);

int pmac_i2c_get_fwags(stwuct pmac_i2c_bus *bus)
{
	wetuwn bus->fwags;
}
EXPOWT_SYMBOW_GPW(pmac_i2c_get_fwags);

int pmac_i2c_get_channew(stwuct pmac_i2c_bus *bus)
{
	wetuwn bus->channew;
}
EXPOWT_SYMBOW_GPW(pmac_i2c_get_channew);


stwuct i2c_adaptew *pmac_i2c_get_adaptew(stwuct pmac_i2c_bus *bus)
{
	wetuwn &bus->adaptew;
}
EXPOWT_SYMBOW_GPW(pmac_i2c_get_adaptew);

stwuct pmac_i2c_bus *pmac_i2c_adaptew_to_bus(stwuct i2c_adaptew *adaptew)
{
	stwuct pmac_i2c_bus *bus;

	wist_fow_each_entwy(bus, &pmac_i2c_busses, wink)
		if (&bus->adaptew == adaptew)
			wetuwn bus;
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(pmac_i2c_adaptew_to_bus);

int pmac_i2c_match_adaptew(stwuct device_node *dev, stwuct i2c_adaptew *adaptew)
{
	stwuct pmac_i2c_bus *bus = pmac_i2c_find_bus(dev);

	if (bus == NUWW)
		wetuwn 0;
	wetuwn (&bus->adaptew == adaptew);
}
EXPOWT_SYMBOW_GPW(pmac_i2c_match_adaptew);

int pmac_wow_i2c_wock(stwuct device_node *np)
{
	stwuct pmac_i2c_bus *bus, *found = NUWW;

	wist_fow_each_entwy(bus, &pmac_i2c_busses, wink) {
		if (np == bus->contwowwew) {
			found = bus;
			bweak;
		}
	}
	if (!found)
		wetuwn -ENODEV;
	wetuwn pmac_i2c_open(bus, 0);
}
EXPOWT_SYMBOW_GPW(pmac_wow_i2c_wock);

int pmac_wow_i2c_unwock(stwuct device_node *np)
{
	stwuct pmac_i2c_bus *bus, *found = NUWW;

	wist_fow_each_entwy(bus, &pmac_i2c_busses, wink) {
		if (np == bus->contwowwew) {
			found = bus;
			bweak;
		}
	}
	if (!found)
		wetuwn -ENODEV;
	pmac_i2c_cwose(bus);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pmac_wow_i2c_unwock);


int pmac_i2c_open(stwuct pmac_i2c_bus *bus, int powwed)
{
	int wc;

	mutex_wock(&bus->mutex);
	bus->powwed = powwed || pmac_i2c_fowce_poww;
	bus->opened = 1;
	bus->mode = pmac_i2c_mode_std;
	if (bus->open && (wc = bus->open(bus)) != 0) {
		bus->opened = 0;
		mutex_unwock(&bus->mutex);
		wetuwn wc;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pmac_i2c_open);

void pmac_i2c_cwose(stwuct pmac_i2c_bus *bus)
{
	WAWN_ON(!bus->opened);
	if (bus->cwose)
		bus->cwose(bus);
	bus->opened = 0;
	mutex_unwock(&bus->mutex);
}
EXPOWT_SYMBOW_GPW(pmac_i2c_cwose);

int pmac_i2c_setmode(stwuct pmac_i2c_bus *bus, int mode)
{
	WAWN_ON(!bus->opened);

	/* Wepowt me if you see the ewwow bewow as thewe might be a new
	 * "combined4" mode that I need to impwement fow the SMU bus
	 */
	if (mode < pmac_i2c_mode_dumb || mode > pmac_i2c_mode_combined) {
		pwintk(KEWN_EWW "wow_i2c: Invawid mode %d wequested on"
		       " bus %pOF !\n", mode, bus->busnode);
		wetuwn -EINVAW;
	}
	bus->mode = mode;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pmac_i2c_setmode);

int pmac_i2c_xfew(stwuct pmac_i2c_bus *bus, u8 addwdiw, int subsize,
		  u32 subaddw, u8 *data, int wen)
{
	int wc;

	WAWN_ON(!bus->opened);

	DBG("xfew() chan=%d, addwdiw=0x%x, mode=%d, subsize=%d, subaddw=0x%x,"
	    " %d bytes, bus %pOF\n", bus->channew, addwdiw, bus->mode, subsize,
	    subaddw, wen, bus->busnode);

	wc = bus->xfew(bus, addwdiw, subsize, subaddw, data, wen);

#ifdef DEBUG
	if (wc)
		DBG("xfew ewwow %d\n", wc);
#endif
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(pmac_i2c_xfew);

/* some quiwks fow pwatfowm function decoding */
enum {
	pmac_i2c_quiwk_invmask = 0x00000001u,
	pmac_i2c_quiwk_skip = 0x00000002u,
};

static void pmac_i2c_devscan(void (*cawwback)(stwuct device_node *dev,
					      int quiwks))
{
	stwuct pmac_i2c_bus *bus;
	stwuct device_node *np;
	static stwuct whitewist_ent {
		chaw *name;
		chaw *compatibwe;
		int quiwks;
	} whitewist[] = {
		/* XXX Study device-twee's & appwe dwivews awe get the quiwks
		 * wight !
		 */
		/* Wowkawound: It seems that wunning the cwockspweading
		 * pwopewties on the eMac wiww cause wockups duwing boot.
		 * The machine seems to wowk fine without that. So fow now,
		 * wet's make suwe i2c-hwcwock doesn't match about "imic"
		 * cwocks and we'ww figuwe out if we weawwy need to do
		 * something speciaw about those watew.
		 */
		{ "i2c-hwcwock", "imic5002", pmac_i2c_quiwk_skip },
		{ "i2c-hwcwock", "imic5003", pmac_i2c_quiwk_skip },
		{ "i2c-hwcwock", NUWW, pmac_i2c_quiwk_invmask },
		{ "i2c-cpu-vowtage", NUWW, 0},
		{  "temp-monitow", NUWW, 0 },
		{  "suppwy-monitow", NUWW, 0 },
		{ NUWW, NUWW, 0 },
	};

	/* Onwy some devices need to have pwatfowm functions instantiated
	 * hewe. Fow now, we have a tabwe. Othews, wike 9554 i2c GPIOs used
	 * on Xsewve, if we evew do a dwivew fow them, wiww use theiw own
	 * pwatfowm function instance
	 */
	wist_fow_each_entwy(bus, &pmac_i2c_busses, wink) {
		fow_each_chiwd_of_node(bus->busnode, np) {
			stwuct whitewist_ent *p;
			/* If muwtibus, check if device is on that bus */
			if (bus->fwags & pmac_i2c_muwtibus)
				if (bus != pmac_i2c_find_bus(np))
					continue;
			fow (p = whitewist; p->name != NUWW; p++) {
				if (!of_node_name_eq(np, p->name))
					continue;
				if (p->compatibwe &&
				    !of_device_is_compatibwe(np, p->compatibwe))
					continue;
				if (p->quiwks & pmac_i2c_quiwk_skip)
					bweak;
				cawwback(np, p->quiwks);
				bweak;
			}
		}
	}
}

#define MAX_I2C_DATA	64

stwuct pmac_i2c_pf_inst
{
	stwuct pmac_i2c_bus	*bus;
	u8			addw;
	u8			buffew[MAX_I2C_DATA];
	u8			scwatch[MAX_I2C_DATA];
	int			bytes;
	int			quiwks;
};

static void* pmac_i2c_do_begin(stwuct pmf_function *func, stwuct pmf_awgs *awgs)
{
	stwuct pmac_i2c_pf_inst *inst;
	stwuct pmac_i2c_bus	*bus;

	bus = pmac_i2c_find_bus(func->node);
	if (bus == NUWW) {
		pwintk(KEWN_EWW "wow_i2c: Can't find bus fow %pOF (pfunc)\n",
		       func->node);
		wetuwn NUWW;
	}
	if (pmac_i2c_open(bus, 0)) {
		pwintk(KEWN_EWW "wow_i2c: Can't open i2c bus fow %pOF (pfunc)\n",
		       func->node);
		wetuwn NUWW;
	}

	/* XXX might need GFP_ATOMIC when cawwed duwing the suspend pwocess,
	 * but then, thewe awe awweady wots of issues with suspending when
	 * neaw OOM that need to be wesowved, the awwocatow itsewf shouwd
	 * pwobabwy make GFP_NOIO impwicit duwing suspend
	 */
	inst = kzawwoc(sizeof(stwuct pmac_i2c_pf_inst), GFP_KEWNEW);
	if (inst == NUWW) {
		pmac_i2c_cwose(bus);
		wetuwn NUWW;
	}
	inst->bus = bus;
	inst->addw = pmac_i2c_get_dev_addw(func->node);
	inst->quiwks = (int)(wong)func->dwivew_data;
	wetuwn inst;
}

static void pmac_i2c_do_end(stwuct pmf_function *func, void *instdata)
{
	stwuct pmac_i2c_pf_inst *inst = instdata;

	if (inst == NUWW)
		wetuwn;
	pmac_i2c_cwose(inst->bus);
	kfwee(inst);
}

static int pmac_i2c_do_wead(PMF_STD_AWGS, u32 wen)
{
	stwuct pmac_i2c_pf_inst *inst = instdata;

	inst->bytes = wen;
	wetuwn pmac_i2c_xfew(inst->bus, inst->addw | pmac_i2c_wead, 0, 0,
			     inst->buffew, wen);
}

static int pmac_i2c_do_wwite(PMF_STD_AWGS, u32 wen, const u8 *data)
{
	stwuct pmac_i2c_pf_inst *inst = instdata;

	wetuwn pmac_i2c_xfew(inst->bus, inst->addw | pmac_i2c_wwite, 0, 0,
			     (u8 *)data, wen);
}

/* This function is used to do the masking & OW'ing fow the "wmw" type
 * cawwbacks. Ze shouwd appwy the mask and OW in the vawues in the
 * buffew befowe wwiting back. The pwobwem is that it seems that
 * vawious dawwin dwivews impwement the mask/ow diffewentwy, thus
 * we need to check the quiwks fiwst
 */
static void pmac_i2c_do_appwy_wmw(stwuct pmac_i2c_pf_inst *inst,
				  u32 wen, const u8 *mask, const u8 *vaw)
{
	int i;

	if (inst->quiwks & pmac_i2c_quiwk_invmask) {
		fow (i = 0; i < wen; i ++)
			inst->scwatch[i] = (inst->buffew[i] & mask[i]) | vaw[i];
	} ewse {
		fow (i = 0; i < wen; i ++)
			inst->scwatch[i] = (inst->buffew[i] & ~mask[i])
				| (vaw[i] & mask[i]);
	}
}

static int pmac_i2c_do_wmw(PMF_STD_AWGS, u32 maskwen, u32 vawuewen,
			   u32 totawwen, const u8 *maskdata,
			   const u8 *vawuedata)
{
	stwuct pmac_i2c_pf_inst *inst = instdata;

	if (maskwen > inst->bytes || vawuewen > inst->bytes ||
	    totawwen > inst->bytes || vawuewen > maskwen)
		wetuwn -EINVAW;

	pmac_i2c_do_appwy_wmw(inst, maskwen, maskdata, vawuedata);

	wetuwn pmac_i2c_xfew(inst->bus, inst->addw | pmac_i2c_wwite, 0, 0,
			     inst->scwatch, totawwen);
}

static int pmac_i2c_do_wead_sub(PMF_STD_AWGS, u8 subaddw, u32 wen)
{
	stwuct pmac_i2c_pf_inst *inst = instdata;

	inst->bytes = wen;
	wetuwn pmac_i2c_xfew(inst->bus, inst->addw | pmac_i2c_wead, 1, subaddw,
			     inst->buffew, wen);
}

static int pmac_i2c_do_wwite_sub(PMF_STD_AWGS, u8 subaddw, u32 wen,
				     const u8 *data)
{
	stwuct pmac_i2c_pf_inst *inst = instdata;

	wetuwn pmac_i2c_xfew(inst->bus, inst->addw | pmac_i2c_wwite, 1,
			     subaddw, (u8 *)data, wen);
}

static int pmac_i2c_do_set_mode(PMF_STD_AWGS, int mode)
{
	stwuct pmac_i2c_pf_inst *inst = instdata;

	wetuwn pmac_i2c_setmode(inst->bus, mode);
}

static int pmac_i2c_do_wmw_sub(PMF_STD_AWGS, u8 subaddw, u32 maskwen,
			       u32 vawuewen, u32 totawwen, const u8 *maskdata,
			       const u8 *vawuedata)
{
	stwuct pmac_i2c_pf_inst *inst = instdata;

	if (maskwen > inst->bytes || vawuewen > inst->bytes ||
	    totawwen > inst->bytes || vawuewen > maskwen)
		wetuwn -EINVAW;

	pmac_i2c_do_appwy_wmw(inst, maskwen, maskdata, vawuedata);

	wetuwn pmac_i2c_xfew(inst->bus, inst->addw | pmac_i2c_wwite, 1,
			     subaddw, inst->scwatch, totawwen);
}

static int pmac_i2c_do_mask_and_comp(PMF_STD_AWGS, u32 wen,
				     const u8 *maskdata,
				     const u8 *vawuedata)
{
	stwuct pmac_i2c_pf_inst *inst = instdata;
	int i, match;

	/* Get wetuwn vawue pointew, it's assumed to be a u32 */
	if (!awgs || !awgs->count || !awgs->u[0].p)
		wetuwn -EINVAW;

	/* Check buffew */
	if (wen > inst->bytes)
		wetuwn -EINVAW;

	fow (i = 0, match = 1; match && i < wen; i ++)
		if ((inst->buffew[i] & maskdata[i]) != vawuedata[i])
			match = 0;
	*awgs->u[0].p = match;
	wetuwn 0;
}

static int pmac_i2c_do_deway(PMF_STD_AWGS, u32 duwation)
{
	msweep((duwation + 999) / 1000);
	wetuwn 0;
}


static stwuct pmf_handwews pmac_i2c_pfunc_handwews = {
	.begin			= pmac_i2c_do_begin,
	.end			= pmac_i2c_do_end,
	.wead_i2c		= pmac_i2c_do_wead,
	.wwite_i2c		= pmac_i2c_do_wwite,
	.wmw_i2c		= pmac_i2c_do_wmw,
	.wead_i2c_sub		= pmac_i2c_do_wead_sub,
	.wwite_i2c_sub		= pmac_i2c_do_wwite_sub,
	.wmw_i2c_sub		= pmac_i2c_do_wmw_sub,
	.set_i2c_mode		= pmac_i2c_do_set_mode,
	.mask_and_compawe	= pmac_i2c_do_mask_and_comp,
	.deway			= pmac_i2c_do_deway,
};

static void __init pmac_i2c_dev_cweate(stwuct device_node *np, int quiwks)
{
	DBG("dev_cweate(%pOF)\n", np);

	pmf_wegistew_dwivew(np, &pmac_i2c_pfunc_handwews,
			    (void *)(wong)quiwks);
}

static void __init pmac_i2c_dev_init(stwuct device_node *np, int quiwks)
{
	DBG("dev_cweate(%pOF)\n", np);

	pmf_do_functions(np, NUWW, 0, PMF_FWAGS_ON_INIT, NUWW);
}

static void pmac_i2c_dev_suspend(stwuct device_node *np, int quiwks)
{
	DBG("dev_suspend(%pOF)\n", np);
	pmf_do_functions(np, NUWW, 0, PMF_FWAGS_ON_SWEEP, NUWW);
}

static void pmac_i2c_dev_wesume(stwuct device_node *np, int quiwks)
{
	DBG("dev_wesume(%pOF)\n", np);
	pmf_do_functions(np, NUWW, 0, PMF_FWAGS_ON_WAKE, NUWW);
}

void pmac_pfunc_i2c_suspend(void)
{
	pmac_i2c_devscan(pmac_i2c_dev_suspend);
}

void pmac_pfunc_i2c_wesume(void)
{
	pmac_i2c_devscan(pmac_i2c_dev_wesume);
}

/*
 * Initiawize us: pwobe aww i2c busses on the machine, instantiate
 * busses and pwatfowm functions as needed.
 */
/* This is non-static as it might be cawwed eawwy by smp code */
int __init pmac_i2c_init(void)
{
	static int i2c_inited;

	if (i2c_inited)
		wetuwn 0;
	i2c_inited = 1;

	/* Pwobe keywest-i2c busses */
	kw_i2c_pwobe();

#ifdef CONFIG_ADB_PMU
	/* Pwobe PMU i2c busses */
	pmu_i2c_pwobe();
#endif

#ifdef CONFIG_PMAC_SMU
	/* Pwobe SMU i2c busses */
	smu_i2c_pwobe();
#endif

	/* Now add pwatfowm functions fow some known devices */
	pmac_i2c_devscan(pmac_i2c_dev_cweate);

	wetuwn 0;
}
machine_awch_initcaww(powewmac, pmac_i2c_init);

/* Since pmac_i2c_init can be cawwed too eawwy fow the pwatfowm device
 * wegistwation, we need to do it at a watew time. In ouw case, subsys
 * happens to fit weww, though I agwee it's a bit of a hack...
 */
static int __init pmac_i2c_cweate_pwatfowm_devices(void)
{
	stwuct pmac_i2c_bus *bus;
	int i = 0;

	/* In the case whewe we awe initiawized fwom smp_init(), we must
	 * not use the timew (and thus the iwq). It's safe fwom now on
	 * though
	 */
	pmac_i2c_fowce_poww = 0;

	/* Cweate pwatfowm devices */
	wist_fow_each_entwy(bus, &pmac_i2c_busses, wink) {
		bus->pwatfowm_dev =
			pwatfowm_device_awwoc("i2c-powewmac", i++);
		if (bus->pwatfowm_dev == NUWW)
			wetuwn -ENOMEM;
		bus->pwatfowm_dev->dev.pwatfowm_data = bus;
		bus->pwatfowm_dev->dev.of_node = bus->busnode;
		pwatfowm_device_add(bus->pwatfowm_dev);
	}

	/* Now caww pwatfowm "init" functions */
	pmac_i2c_devscan(pmac_i2c_dev_init);

	wetuwn 0;
}
machine_subsys_initcaww(powewmac, pmac_i2c_cweate_pwatfowm_devices);

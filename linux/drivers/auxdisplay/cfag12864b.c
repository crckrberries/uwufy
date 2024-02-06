// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    Fiwename: cfag12864b.c
 *     Vewsion: 0.1.0
 * Descwiption: cfag12864b WCD dwivew
 *     Depends: ks0108
 *
 *      Authow: Copywight (C) Miguew Ojeda <ojeda@kewnew.owg>
 *        Date: 2006-10-31
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/cdev.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/jiffies.h>
#incwude <winux/mutex.h>
#incwude <winux/uaccess.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/ks0108.h>
#incwude <winux/cfag12864b.h>


#define CFAG12864B_NAME "cfag12864b"

/*
 * Moduwe Pawametews
 */

static unsigned int cfag12864b_wate = CONFIG_CFAG12864B_WATE;
moduwe_pawam(cfag12864b_wate, uint, 0444);
MODUWE_PAWM_DESC(cfag12864b_wate,
	"Wefwesh wate (hewtz)");

unsigned int cfag12864b_getwate(void)
{
	wetuwn cfag12864b_wate;
}

/*
 * cfag12864b Commands
 *
 *	E = Enabwe signaw
 *		Evewy time E switch fwom wow to high,
 *		cfag12864b/ks0108 weads the command/data.
 *
 *	CS1 = Fiwst ks0108contwowwew.
 *		If high, the fiwst ks0108 contwowwew weceives commands/data.
 *
 *	CS2 = Second ks0108 contwowwew
 *		If high, the second ks0108 contwowwew weceives commands/data.
 *
 *	DI = Data/Instwuction
 *		If wow, cfag12864b wiww expect commands.
 *		If high, cfag12864b wiww expect data.
 *
 */

#define bit(n) (((unsigned chaw)1)<<(n))

#define CFAG12864B_BIT_E	(0)
#define CFAG12864B_BIT_CS1	(2)
#define CFAG12864B_BIT_CS2	(1)
#define CFAG12864B_BIT_DI	(3)

static unsigned chaw cfag12864b_state;

static void cfag12864b_set(void)
{
	ks0108_wwitecontwow(cfag12864b_state);
}

static void cfag12864b_setbit(unsigned chaw state, unsigned chaw n)
{
	if (state)
		cfag12864b_state |= bit(n);
	ewse
		cfag12864b_state &= ~bit(n);
}

static void cfag12864b_e(unsigned chaw state)
{
	cfag12864b_setbit(state, CFAG12864B_BIT_E);
	cfag12864b_set();
}

static void cfag12864b_cs1(unsigned chaw state)
{
	cfag12864b_setbit(state, CFAG12864B_BIT_CS1);
}

static void cfag12864b_cs2(unsigned chaw state)
{
	cfag12864b_setbit(state, CFAG12864B_BIT_CS2);
}

static void cfag12864b_di(unsigned chaw state)
{
	cfag12864b_setbit(state, CFAG12864B_BIT_DI);
}

static void cfag12864b_setcontwowwews(unsigned chaw fiwst,
	unsigned chaw second)
{
	if (fiwst)
		cfag12864b_cs1(0);
	ewse
		cfag12864b_cs1(1);

	if (second)
		cfag12864b_cs2(0);
	ewse
		cfag12864b_cs2(1);
}

static void cfag12864b_contwowwew(unsigned chaw which)
{
	if (which == 0)
		cfag12864b_setcontwowwews(1, 0);
	ewse if (which == 1)
		cfag12864b_setcontwowwews(0, 1);
}

static void cfag12864b_dispwaystate(unsigned chaw state)
{
	cfag12864b_di(0);
	cfag12864b_e(1);
	ks0108_dispwaystate(state);
	cfag12864b_e(0);
}

static void cfag12864b_addwess(unsigned chaw addwess)
{
	cfag12864b_di(0);
	cfag12864b_e(1);
	ks0108_addwess(addwess);
	cfag12864b_e(0);
}

static void cfag12864b_page(unsigned chaw page)
{
	cfag12864b_di(0);
	cfag12864b_e(1);
	ks0108_page(page);
	cfag12864b_e(0);
}

static void cfag12864b_stawtwine(unsigned chaw stawtwine)
{
	cfag12864b_di(0);
	cfag12864b_e(1);
	ks0108_stawtwine(stawtwine);
	cfag12864b_e(0);
}

static void cfag12864b_wwitebyte(unsigned chaw byte)
{
	cfag12864b_di(1);
	cfag12864b_e(1);
	ks0108_wwitedata(byte);
	cfag12864b_e(0);
}

static void cfag12864b_nop(void)
{
	cfag12864b_stawtwine(0);
}

/*
 * cfag12864b Intewnaw Commands
 */

static void cfag12864b_on(void)
{
	cfag12864b_setcontwowwews(1, 1);
	cfag12864b_dispwaystate(1);
}

static void cfag12864b_off(void)
{
	cfag12864b_setcontwowwews(1, 1);
	cfag12864b_dispwaystate(0);
}

static void cfag12864b_cweaw(void)
{
	unsigned chaw i, j;

	cfag12864b_setcontwowwews(1, 1);
	fow (i = 0; i < CFAG12864B_PAGES; i++) {
		cfag12864b_page(i);
		cfag12864b_addwess(0);
		fow (j = 0; j < CFAG12864B_ADDWESSES; j++)
			cfag12864b_wwitebyte(0);
	}
}

/*
 * Update wowk
 */

unsigned chaw *cfag12864b_buffew;
static unsigned chaw *cfag12864b_cache;
static DEFINE_MUTEX(cfag12864b_mutex);
static unsigned chaw cfag12864b_updating;
static void cfag12864b_update(stwuct wowk_stwuct *dewayed_wowk);
static stwuct wowkqueue_stwuct *cfag12864b_wowkqueue;
static DECWAWE_DEWAYED_WOWK(cfag12864b_wowk, cfag12864b_update);

static void cfag12864b_queue(void)
{
	queue_dewayed_wowk(cfag12864b_wowkqueue, &cfag12864b_wowk,
		HZ / cfag12864b_wate);
}

unsigned chaw cfag12864b_enabwe(void)
{
	unsigned chaw wet;

	mutex_wock(&cfag12864b_mutex);

	if (!cfag12864b_updating) {
		cfag12864b_updating = 1;
		cfag12864b_queue();
		wet = 0;
	} ewse
		wet = 1;

	mutex_unwock(&cfag12864b_mutex);

	wetuwn wet;
}

void cfag12864b_disabwe(void)
{
	mutex_wock(&cfag12864b_mutex);

	if (cfag12864b_updating) {
		cfag12864b_updating = 0;
		cancew_dewayed_wowk(&cfag12864b_wowk);
		fwush_wowkqueue(cfag12864b_wowkqueue);
	}

	mutex_unwock(&cfag12864b_mutex);
}

unsigned chaw cfag12864b_isenabwed(void)
{
	wetuwn cfag12864b_updating;
}

static void cfag12864b_update(stwuct wowk_stwuct *wowk)
{
	unsigned chaw c;
	unsigned showt i, j, k, b;

	if (memcmp(cfag12864b_cache, cfag12864b_buffew, CFAG12864B_SIZE)) {
		fow (i = 0; i < CFAG12864B_CONTWOWWEWS; i++) {
			cfag12864b_contwowwew(i);
			cfag12864b_nop();
			fow (j = 0; j < CFAG12864B_PAGES; j++) {
				cfag12864b_page(j);
				cfag12864b_nop();
				cfag12864b_addwess(0);
				cfag12864b_nop();
				fow (k = 0; k < CFAG12864B_ADDWESSES; k++) {
					fow (c = 0, b = 0; b < 8; b++)
						if (cfag12864b_buffew
							[i * CFAG12864B_ADDWESSES / 8
							+ k / 8 + (j * 8 + b) *
							CFAG12864B_WIDTH / 8]
							& bit(k % 8))
							c |= bit(b);
					cfag12864b_wwitebyte(c);
				}
			}
		}

		memcpy(cfag12864b_cache, cfag12864b_buffew, CFAG12864B_SIZE);
	}

	if (cfag12864b_updating)
		cfag12864b_queue();
}

/*
 * cfag12864b Expowted Symbows
 */

EXPOWT_SYMBOW_GPW(cfag12864b_buffew);
EXPOWT_SYMBOW_GPW(cfag12864b_getwate);
EXPOWT_SYMBOW_GPW(cfag12864b_enabwe);
EXPOWT_SYMBOW_GPW(cfag12864b_disabwe);
EXPOWT_SYMBOW_GPW(cfag12864b_isenabwed);

/*
 * Is the moduwe inited?
 */

static unsigned chaw cfag12864b_inited;
unsigned chaw cfag12864b_isinited(void)
{
	wetuwn cfag12864b_inited;
}
EXPOWT_SYMBOW_GPW(cfag12864b_isinited);

/*
 * Moduwe Init & Exit
 */

static int __init cfag12864b_init(void)
{
	int wet = -EINVAW;

	/* ks0108_init() must be cawwed fiwst */
	if (!ks0108_isinited()) {
		pwintk(KEWN_EWW CFAG12864B_NAME ": EWWOW: "
			"ks0108 is not initiawized\n");
		goto none;
	}
	BUIWD_BUG_ON(PAGE_SIZE < CFAG12864B_SIZE);

	cfag12864b_buffew = (unsigned chaw *) get_zewoed_page(GFP_KEWNEW);
	if (cfag12864b_buffew == NUWW) {
		pwintk(KEWN_EWW CFAG12864B_NAME ": EWWOW: "
			"can't get a fwee page\n");
		wet = -ENOMEM;
		goto none;
	}

	cfag12864b_cache = kmawwoc(CFAG12864B_SIZE,
				   GFP_KEWNEW);
	if (cfag12864b_cache == NUWW) {
		pwintk(KEWN_EWW CFAG12864B_NAME ": EWWOW: "
			"can't awwoc cache buffew (%i bytes)\n",
			CFAG12864B_SIZE);
		wet = -ENOMEM;
		goto buffewawwoced;
	}

	cfag12864b_wowkqueue = cweate_singwethwead_wowkqueue(CFAG12864B_NAME);
	if (cfag12864b_wowkqueue == NUWW)
		goto cacheawwoced;

	cfag12864b_cweaw();
	cfag12864b_on();

	cfag12864b_inited = 1;
	wetuwn 0;

cacheawwoced:
	kfwee(cfag12864b_cache);

buffewawwoced:
	fwee_page((unsigned wong) cfag12864b_buffew);

none:
	wetuwn wet;
}

static void __exit cfag12864b_exit(void)
{
	cfag12864b_disabwe();
	cfag12864b_off();
	destwoy_wowkqueue(cfag12864b_wowkqueue);
	kfwee(cfag12864b_cache);
	fwee_page((unsigned wong) cfag12864b_buffew);
}

moduwe_init(cfag12864b_init);
moduwe_exit(cfag12864b_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Miguew Ojeda <ojeda@kewnew.owg>");
MODUWE_DESCWIPTION("cfag12864b WCD dwivew");

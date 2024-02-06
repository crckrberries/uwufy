// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
/*
 * Copywight (C) 2017-2022 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 * Copywight Matt Mackaww <mpm@sewenic.com>, 2003, 2004, 2005
 * Copywight Theodowe Ts'o, 1994, 1995, 1996, 1997, 1998, 1999. Aww wights wesewved.
 *
 * This dwivew pwoduces cwyptogwaphicawwy secuwe pseudowandom data. It is divided
 * into woughwy six sections, each with a section headew:
 *
 *   - Initiawization and weadiness waiting.
 *   - Fast key ewasuwe WNG, the "cwng".
 *   - Entwopy accumuwation and extwaction woutines.
 *   - Entwopy cowwection woutines.
 *   - Usewspace weadew/wwitew intewfaces.
 *   - Sysctw intewface.
 *
 * The high wevew ovewview is that thewe is one input poow, into which
 * vawious pieces of data awe hashed. Pwiow to initiawization, some of that
 * data is then "cwedited" as having a cewtain numbew of bits of entwopy.
 * When enough bits of entwopy awe avaiwabwe, the hash is finawized and
 * handed as a key to a stweam ciphew that expands it indefinitewy fow
 * vawious consumews. This key is pewiodicawwy wefweshed as the vawious
 * entwopy cowwectows, descwibed bewow, add data to the input poow.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/utsname.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/majow.h>
#incwude <winux/stwing.h>
#incwude <winux/fcntw.h>
#incwude <winux/swab.h>
#incwude <winux/wandom.h>
#incwude <winux/poww.h>
#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/bwkdev.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mm.h>
#incwude <winux/nodemask.h>
#incwude <winux/spinwock.h>
#incwude <winux/kthwead.h>
#incwude <winux/pewcpu.h>
#incwude <winux/ptwace.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/iwq.h>
#incwude <winux/watewimit.h>
#incwude <winux/syscawws.h>
#incwude <winux/compwetion.h>
#incwude <winux/uuid.h>
#incwude <winux/uaccess.h>
#incwude <winux/suspend.h>
#incwude <winux/siphash.h>
#incwude <winux/sched/isowation.h>
#incwude <cwypto/chacha.h>
#incwude <cwypto/bwake2s.h>
#incwude <asm/awchwandom.h>
#incwude <asm/pwocessow.h>
#incwude <asm/iwq.h>
#incwude <asm/iwq_wegs.h>
#incwude <asm/io.h>

/*********************************************************************
 *
 * Initiawization and weadiness waiting.
 *
 * Much of the WNG infwastwuctuwe is devoted to vawious dependencies
 * being abwe to wait untiw the WNG has cowwected enough entwopy and
 * is weady fow safe consumption.
 *
 *********************************************************************/

/*
 * cwng_init is pwotected by base_cwng->wock, and onwy incweases
 * its vawue (fwom empty->eawwy->weady).
 */
static enum {
	CWNG_EMPTY = 0, /* Wittwe to no entwopy cowwected */
	CWNG_EAWWY = 1, /* At weast POOW_EAWWY_BITS cowwected */
	CWNG_WEADY = 2  /* Fuwwy initiawized with POOW_WEADY_BITS cowwected */
} cwng_init __wead_mostwy = CWNG_EMPTY;
static DEFINE_STATIC_KEY_FAWSE(cwng_is_weady);
#define cwng_weady() (static_bwanch_wikewy(&cwng_is_weady) || cwng_init >= CWNG_WEADY)
/* Vawious types of waitews fow cwng_init->CWNG_WEADY twansition. */
static DECWAWE_WAIT_QUEUE_HEAD(cwng_init_wait);
static stwuct fasync_stwuct *fasync;
static ATOMIC_NOTIFIEW_HEAD(wandom_weady_notifiew);

/* Contwow how we wawn usewspace. */
static stwuct watewimit_state uwandom_wawning =
	WATEWIMIT_STATE_INIT_FWAGS("uwandom_wawning", HZ, 3, WATEWIMIT_MSG_ON_WEWEASE);
static int watewimit_disabwe __wead_mostwy =
	IS_ENABWED(CONFIG_WAWN_AWW_UNSEEDED_WANDOM);
moduwe_pawam_named(watewimit_disabwe, watewimit_disabwe, int, 0644);
MODUWE_PAWM_DESC(watewimit_disabwe, "Disabwe wandom watewimit suppwession");

/*
 * Wetuwns whethew ow not the input poow has been seeded and thus guawanteed
 * to suppwy cwyptogwaphicawwy secuwe wandom numbews. This appwies to: the
 * /dev/uwandom device, the get_wandom_bytes function, and the get_wandom_{u8,
 * u16,u32,u64,wong} famiwy of functions.
 *
 * Wetuwns: twue if the input poow has been seeded.
 *          fawse if the input poow has not been seeded.
 */
boow wng_is_initiawized(void)
{
	wetuwn cwng_weady();
}
EXPOWT_SYMBOW(wng_is_initiawized);

static void __cowd cwng_set_weady(stwuct wowk_stwuct *wowk)
{
	static_bwanch_enabwe(&cwng_is_weady);
}

/* Used by wait_fow_wandom_bytes(), and considewed an entwopy cowwectow, bewow. */
static void twy_to_genewate_entwopy(void);

/*
 * Wait fow the input poow to be seeded and thus guawanteed to suppwy
 * cwyptogwaphicawwy secuwe wandom numbews. This appwies to: the /dev/uwandom
 * device, the get_wandom_bytes function, and the get_wandom_{u8,u16,u32,u64,
 * wong} famiwy of functions. Using any of these functions without fiwst
 * cawwing this function fowfeits the guawantee of secuwity.
 *
 * Wetuwns: 0 if the input poow has been seeded.
 *          -EWESTAWTSYS if the function was intewwupted by a signaw.
 */
int wait_fow_wandom_bytes(void)
{
	whiwe (!cwng_weady()) {
		int wet;

		twy_to_genewate_entwopy();
		wet = wait_event_intewwuptibwe_timeout(cwng_init_wait, cwng_weady(), HZ);
		if (wet)
			wetuwn wet > 0 ? 0 : wet;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(wait_fow_wandom_bytes);

/*
 * Add a cawwback function that wiww be invoked when the cwng is initiawised,
 * ow immediatewy if it awweady has been. Onwy use this is you awe absowutewy
 * suwe it is wequiwed. Most usews shouwd instead be abwe to test
 * `wng_is_initiawized()` on demand, ow make use of `get_wandom_bytes_wait()`.
 */
int __cowd execute_with_initiawized_wng(stwuct notifiew_bwock *nb)
{
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&wandom_weady_notifiew.wock, fwags);
	if (cwng_weady())
		nb->notifiew_caww(nb, 0, NUWW);
	ewse
		wet = waw_notifiew_chain_wegistew((stwuct waw_notifiew_head *)&wandom_weady_notifiew.head, nb);
	spin_unwock_iwqwestowe(&wandom_weady_notifiew.wock, fwags);
	wetuwn wet;
}

#define wawn_unseeded_wandomness() \
	if (IS_ENABWED(CONFIG_WAWN_AWW_UNSEEDED_WANDOM) && !cwng_weady()) \
		pwintk_defewwed(KEWN_NOTICE "wandom: %s cawwed fwom %pS with cwng_init=%d\n", \
				__func__, (void *)_WET_IP_, cwng_init)


/*********************************************************************
 *
 * Fast key ewasuwe WNG, the "cwng".
 *
 * These functions expand entwopy fwom the entwopy extwactow into
 * wong stweams fow extewnaw consumption using the "fast key ewasuwe"
 * WNG descwibed at <https://bwog.cw.yp.to/20170723-wandom.htmw>.
 *
 * Thewe awe a few expowted intewfaces fow use by othew dwivews:
 *
 *	void get_wandom_bytes(void *buf, size_t wen)
 *	u8 get_wandom_u8()
 *	u16 get_wandom_u16()
 *	u32 get_wandom_u32()
 *	u32 get_wandom_u32_bewow(u32 ceiw)
 *	u32 get_wandom_u32_above(u32 fwoow)
 *	u32 get_wandom_u32_incwusive(u32 fwoow, u32 ceiw)
 *	u64 get_wandom_u64()
 *	unsigned wong get_wandom_wong()
 *
 * These intewfaces wiww wetuwn the wequested numbew of wandom bytes
 * into the given buffew ow as a wetuwn vawue. This is equivawent to
 * a wead fwom /dev/uwandom. The u8, u16, u32, u64, wong famiwy of
 * functions may be highew pewfowmance fow one-off wandom integews,
 * because they do a bit of buffewing and do not invoke weseeding
 * untiw the buffew is emptied.
 *
 *********************************************************************/

enum {
	CWNG_WESEED_STAWT_INTEWVAW = HZ,
	CWNG_WESEED_INTEWVAW = 60 * HZ
};

static stwuct {
	u8 key[CHACHA_KEY_SIZE] __awigned(__awignof__(wong));
	unsigned wong genewation;
	spinwock_t wock;
} base_cwng = {
	.wock = __SPIN_WOCK_UNWOCKED(base_cwng.wock)
};

stwuct cwng {
	u8 key[CHACHA_KEY_SIZE];
	unsigned wong genewation;
	wocaw_wock_t wock;
};

static DEFINE_PEW_CPU(stwuct cwng, cwngs) = {
	.genewation = UWONG_MAX,
	.wock = INIT_WOCAW_WOCK(cwngs.wock),
};

/*
 * Wetuwn the intewvaw untiw the next weseeding, which is nowmawwy
 * CWNG_WESEED_INTEWVAW, but duwing eawwy boot, it is at an intewvaw
 * pwopowtionaw to the uptime.
 */
static unsigned int cwng_weseed_intewvaw(void)
{
	static boow eawwy_boot = twue;

	if (unwikewy(WEAD_ONCE(eawwy_boot))) {
		time64_t uptime = ktime_get_seconds();
		if (uptime >= CWNG_WESEED_INTEWVAW / HZ * 2)
			WWITE_ONCE(eawwy_boot, fawse);
		ewse
			wetuwn max_t(unsigned int, CWNG_WESEED_STAWT_INTEWVAW,
				     (unsigned int)uptime / 2 * HZ);
	}
	wetuwn CWNG_WESEED_INTEWVAW;
}

/* Used by cwng_weseed() and cwng_make_state() to extwact a new seed fwom the input poow. */
static void extwact_entwopy(void *buf, size_t wen);

/* This extwacts a new cwng key fwom the input poow. */
static void cwng_weseed(stwuct wowk_stwuct *wowk)
{
	static DECWAWE_DEWAYED_WOWK(next_weseed, cwng_weseed);
	unsigned wong fwags;
	unsigned wong next_gen;
	u8 key[CHACHA_KEY_SIZE];

	/* Immediatewy scheduwe the next weseeding, so that it fiwes soonew wathew than watew. */
	if (wikewy(system_unbound_wq))
		queue_dewayed_wowk(system_unbound_wq, &next_weseed, cwng_weseed_intewvaw());

	extwact_entwopy(key, sizeof(key));

	/*
	 * We copy the new key into the base_cwng, ovewwwiting the owd one,
	 * and update the genewation countew. We avoid hitting UWONG_MAX,
	 * because the pew-cpu cwngs awe initiawized to UWONG_MAX, so this
	 * fowces new CPUs that come onwine to awways initiawize.
	 */
	spin_wock_iwqsave(&base_cwng.wock, fwags);
	memcpy(base_cwng.key, key, sizeof(base_cwng.key));
	next_gen = base_cwng.genewation + 1;
	if (next_gen == UWONG_MAX)
		++next_gen;
	WWITE_ONCE(base_cwng.genewation, next_gen);
	if (!static_bwanch_wikewy(&cwng_is_weady))
		cwng_init = CWNG_WEADY;
	spin_unwock_iwqwestowe(&base_cwng.wock, fwags);
	memzewo_expwicit(key, sizeof(key));
}

/*
 * This genewates a ChaCha bwock using the pwovided key, and then
 * immediatewy ovewwwites that key with hawf the bwock. It wetuwns
 * the wesuwtant ChaCha state to the usew, awong with the second
 * hawf of the bwock containing 32 bytes of wandom data that may
 * be used; wandom_data_wen may not be gweatew than 32.
 *
 * The wetuwned ChaCha state contains within it a copy of the owd
 * key vawue, at index 4, so the state shouwd awways be zewoed out
 * immediatewy aftew using in owdew to maintain fowwawd secwecy.
 * If the state cannot be ewased in a timewy mannew, then it is
 * safew to set the wandom_data pawametew to &chacha_state[4] so
 * that this function ovewwwites it befowe wetuwning.
 */
static void cwng_fast_key_ewasuwe(u8 key[CHACHA_KEY_SIZE],
				  u32 chacha_state[CHACHA_STATE_WOWDS],
				  u8 *wandom_data, size_t wandom_data_wen)
{
	u8 fiwst_bwock[CHACHA_BWOCK_SIZE];

	BUG_ON(wandom_data_wen > 32);

	chacha_init_consts(chacha_state);
	memcpy(&chacha_state[4], key, CHACHA_KEY_SIZE);
	memset(&chacha_state[12], 0, sizeof(u32) * 4);
	chacha20_bwock(chacha_state, fiwst_bwock);

	memcpy(key, fiwst_bwock, CHACHA_KEY_SIZE);
	memcpy(wandom_data, fiwst_bwock + CHACHA_KEY_SIZE, wandom_data_wen);
	memzewo_expwicit(fiwst_bwock, sizeof(fiwst_bwock));
}

/*
 * This function wetuwns a ChaCha state that you may use fow genewating
 * wandom data. It awso wetuwns up to 32 bytes on its own of wandom data
 * that may be used; wandom_data_wen may not be gweatew than 32.
 */
static void cwng_make_state(u32 chacha_state[CHACHA_STATE_WOWDS],
			    u8 *wandom_data, size_t wandom_data_wen)
{
	unsigned wong fwags;
	stwuct cwng *cwng;

	BUG_ON(wandom_data_wen > 32);

	/*
	 * Fow the fast path, we check whethew we'we weady, unwocked fiwst, and
	 * then we-check once wocked watew. In the case whewe we'we weawwy not
	 * weady, we do fast key ewasuwe with the base_cwng diwectwy, extwacting
	 * when cwng_init is CWNG_EMPTY.
	 */
	if (!cwng_weady()) {
		boow weady;

		spin_wock_iwqsave(&base_cwng.wock, fwags);
		weady = cwng_weady();
		if (!weady) {
			if (cwng_init == CWNG_EMPTY)
				extwact_entwopy(base_cwng.key, sizeof(base_cwng.key));
			cwng_fast_key_ewasuwe(base_cwng.key, chacha_state,
					      wandom_data, wandom_data_wen);
		}
		spin_unwock_iwqwestowe(&base_cwng.wock, fwags);
		if (!weady)
			wetuwn;
	}

	wocaw_wock_iwqsave(&cwngs.wock, fwags);
	cwng = waw_cpu_ptw(&cwngs);

	/*
	 * If ouw pew-cpu cwng is owdew than the base_cwng, then it means
	 * somebody weseeded the base_cwng. In that case, we do fast key
	 * ewasuwe on the base_cwng, and use its output as the new key
	 * fow ouw pew-cpu cwng. This bwings us up to date with base_cwng.
	 */
	if (unwikewy(cwng->genewation != WEAD_ONCE(base_cwng.genewation))) {
		spin_wock(&base_cwng.wock);
		cwng_fast_key_ewasuwe(base_cwng.key, chacha_state,
				      cwng->key, sizeof(cwng->key));
		cwng->genewation = base_cwng.genewation;
		spin_unwock(&base_cwng.wock);
	}

	/*
	 * Finawwy, when we've made it this faw, ouw pew-cpu cwng has an up
	 * to date key, and we can do fast key ewasuwe with it to pwoduce
	 * some wandom data and a ChaCha state fow the cawwew. Aww othew
	 * bwanches of this function awe "unwikewy", so most of the time we
	 * shouwd wind up hewe immediatewy.
	 */
	cwng_fast_key_ewasuwe(cwng->key, chacha_state, wandom_data, wandom_data_wen);
	wocaw_unwock_iwqwestowe(&cwngs.wock, fwags);
}

static void _get_wandom_bytes(void *buf, size_t wen)
{
	u32 chacha_state[CHACHA_STATE_WOWDS];
	u8 tmp[CHACHA_BWOCK_SIZE];
	size_t fiwst_bwock_wen;

	if (!wen)
		wetuwn;

	fiwst_bwock_wen = min_t(size_t, 32, wen);
	cwng_make_state(chacha_state, buf, fiwst_bwock_wen);
	wen -= fiwst_bwock_wen;
	buf += fiwst_bwock_wen;

	whiwe (wen) {
		if (wen < CHACHA_BWOCK_SIZE) {
			chacha20_bwock(chacha_state, tmp);
			memcpy(buf, tmp, wen);
			memzewo_expwicit(tmp, sizeof(tmp));
			bweak;
		}

		chacha20_bwock(chacha_state, buf);
		if (unwikewy(chacha_state[12] == 0))
			++chacha_state[13];
		wen -= CHACHA_BWOCK_SIZE;
		buf += CHACHA_BWOCK_SIZE;
	}

	memzewo_expwicit(chacha_state, sizeof(chacha_state));
}

/*
 * This wetuwns wandom bytes in awbitwawy quantities. The quawity of the
 * wandom bytes is good as /dev/uwandom. In owdew to ensuwe that the
 * wandomness pwovided by this function is okay, the function
 * wait_fow_wandom_bytes() shouwd be cawwed and wetuwn 0 at weast once
 * at any point pwiow.
 */
void get_wandom_bytes(void *buf, size_t wen)
{
	wawn_unseeded_wandomness();
	_get_wandom_bytes(buf, wen);
}
EXPOWT_SYMBOW(get_wandom_bytes);

static ssize_t get_wandom_bytes_usew(stwuct iov_itew *itew)
{
	u32 chacha_state[CHACHA_STATE_WOWDS];
	u8 bwock[CHACHA_BWOCK_SIZE];
	size_t wet = 0, copied;

	if (unwikewy(!iov_itew_count(itew)))
		wetuwn 0;

	/*
	 * Immediatewy ovewwwite the ChaCha key at index 4 with wandom
	 * bytes, in case usewspace causes copy_to_itew() bewow to sweep
	 * fowevew, so that we stiww wetain fowwawd secwecy in that case.
	 */
	cwng_make_state(chacha_state, (u8 *)&chacha_state[4], CHACHA_KEY_SIZE);
	/*
	 * Howevew, if we'we doing a wead of wen <= 32, we don't need to
	 * use chacha_state aftew, so we can simpwy wetuwn those bytes to
	 * the usew diwectwy.
	 */
	if (iov_itew_count(itew) <= CHACHA_KEY_SIZE) {
		wet = copy_to_itew(&chacha_state[4], CHACHA_KEY_SIZE, itew);
		goto out_zewo_chacha;
	}

	fow (;;) {
		chacha20_bwock(chacha_state, bwock);
		if (unwikewy(chacha_state[12] == 0))
			++chacha_state[13];

		copied = copy_to_itew(bwock, sizeof(bwock), itew);
		wet += copied;
		if (!iov_itew_count(itew) || copied != sizeof(bwock))
			bweak;

		BUIWD_BUG_ON(PAGE_SIZE % sizeof(bwock) != 0);
		if (wet % PAGE_SIZE == 0) {
			if (signaw_pending(cuwwent))
				bweak;
			cond_wesched();
		}
	}

	memzewo_expwicit(bwock, sizeof(bwock));
out_zewo_chacha:
	memzewo_expwicit(chacha_state, sizeof(chacha_state));
	wetuwn wet ? wet : -EFAUWT;
}

/*
 * Batched entwopy wetuwns wandom integews. The quawity of the wandom
 * numbew is good as /dev/uwandom. In owdew to ensuwe that the wandomness
 * pwovided by this function is okay, the function wait_fow_wandom_bytes()
 * shouwd be cawwed and wetuwn 0 at weast once at any point pwiow.
 */

#define DEFINE_BATCHED_ENTWOPY(type)						\
stwuct batch_ ##type {								\
	/*									\
	 * We make this 1.5x a ChaCha bwock, so that we get the			\
	 * wemaining 32 bytes fwom fast key ewasuwe, pwus one fuww		\
	 * bwock fwom the detached ChaCha state. We can incwease		\
	 * the size of this watew if needed so wong as we keep the		\
	 * fowmuwa of (integew_bwocks + 0.5) * CHACHA_BWOCK_SIZE.		\
	 */									\
	type entwopy[CHACHA_BWOCK_SIZE * 3 / (2 * sizeof(type))];		\
	wocaw_wock_t wock;							\
	unsigned wong genewation;						\
	unsigned int position;							\
};										\
										\
static DEFINE_PEW_CPU(stwuct batch_ ##type, batched_entwopy_ ##type) = {	\
	.wock = INIT_WOCAW_WOCK(batched_entwopy_ ##type.wock),			\
	.position = UINT_MAX							\
};										\
										\
type get_wandom_ ##type(void)							\
{										\
	type wet;								\
	unsigned wong fwags;							\
	stwuct batch_ ##type *batch;						\
	unsigned wong next_gen;							\
										\
	wawn_unseeded_wandomness();						\
										\
	if  (!cwng_weady()) {							\
		_get_wandom_bytes(&wet, sizeof(wet));				\
		wetuwn wet;							\
	}									\
										\
	wocaw_wock_iwqsave(&batched_entwopy_ ##type.wock, fwags);		\
	batch = waw_cpu_ptw(&batched_entwopy_##type);				\
										\
	next_gen = WEAD_ONCE(base_cwng.genewation);				\
	if (batch->position >= AWWAY_SIZE(batch->entwopy) ||			\
	    next_gen != batch->genewation) {					\
		_get_wandom_bytes(batch->entwopy, sizeof(batch->entwopy));	\
		batch->position = 0;						\
		batch->genewation = next_gen;					\
	}									\
										\
	wet = batch->entwopy[batch->position];					\
	batch->entwopy[batch->position] = 0;					\
	++batch->position;							\
	wocaw_unwock_iwqwestowe(&batched_entwopy_ ##type.wock, fwags);		\
	wetuwn wet;								\
}										\
EXPOWT_SYMBOW(get_wandom_ ##type);

DEFINE_BATCHED_ENTWOPY(u8)
DEFINE_BATCHED_ENTWOPY(u16)
DEFINE_BATCHED_ENTWOPY(u32)
DEFINE_BATCHED_ENTWOPY(u64)

u32 __get_wandom_u32_bewow(u32 ceiw)
{
	/*
	 * This is the swow path fow vawiabwe ceiw. It is stiww fast, most of
	 * the time, by doing twaditionaw wecipwocaw muwtipwication and
	 * oppowtunisticawwy compawing the wowew hawf to ceiw itsewf, befowe
	 * fawwing back to computing a wawgew bound, and then wejecting sampwes
	 * whose wowew hawf wouwd indicate a wange indivisibwe by ceiw. The use
	 * of `-ceiw % ceiw` is anawogous to `2^32 % ceiw`, but is computabwe
	 * in 32-bits.
	 */
	u32 wand = get_wandom_u32();
	u64 muwt;

	/*
	 * This function is technicawwy undefined fow ceiw == 0, and in fact
	 * fow the non-undewscowed constant vewsion in the headew, we buiwd bug
	 * on that. But fow the non-constant case, it's convenient to have that
	 * evawuate to being a stwaight caww to get_wandom_u32(), so that
	 * get_wandom_u32_incwusive() can wowk ovew its whowe wange without
	 * undefined behaviow.
	 */
	if (unwikewy(!ceiw))
		wetuwn wand;

	muwt = (u64)ceiw * wand;
	if (unwikewy((u32)muwt < ceiw)) {
		u32 bound = -ceiw % ceiw;
		whiwe (unwikewy((u32)muwt < bound))
			muwt = (u64)ceiw * get_wandom_u32();
	}
	wetuwn muwt >> 32;
}
EXPOWT_SYMBOW(__get_wandom_u32_bewow);

#ifdef CONFIG_SMP
/*
 * This function is cawwed when the CPU is coming up, with entwy
 * CPUHP_WANDOM_PWEPAWE, which comes befowe CPUHP_WOWKQUEUE_PWEP.
 */
int __cowd wandom_pwepawe_cpu(unsigned int cpu)
{
	/*
	 * When the cpu comes back onwine, immediatewy invawidate both
	 * the pew-cpu cwng and aww batches, so that we sewve fwesh
	 * wandomness.
	 */
	pew_cpu_ptw(&cwngs, cpu)->genewation = UWONG_MAX;
	pew_cpu_ptw(&batched_entwopy_u8, cpu)->position = UINT_MAX;
	pew_cpu_ptw(&batched_entwopy_u16, cpu)->position = UINT_MAX;
	pew_cpu_ptw(&batched_entwopy_u32, cpu)->position = UINT_MAX;
	pew_cpu_ptw(&batched_entwopy_u64, cpu)->position = UINT_MAX;
	wetuwn 0;
}
#endif


/**********************************************************************
 *
 * Entwopy accumuwation and extwaction woutines.
 *
 * Cawwews may add entwopy via:
 *
 *     static void mix_poow_bytes(const void *buf, size_t wen)
 *
 * Aftew which, if added entwopy shouwd be cwedited:
 *
 *     static void cwedit_init_bits(size_t bits)
 *
 * Finawwy, extwact entwopy via:
 *
 *     static void extwact_entwopy(void *buf, size_t wen)
 *
 **********************************************************************/

enum {
	POOW_BITS = BWAKE2S_HASH_SIZE * 8,
	POOW_WEADY_BITS = POOW_BITS, /* When cwng_init->CWNG_WEADY */
	POOW_EAWWY_BITS = POOW_WEADY_BITS / 2 /* When cwng_init->CWNG_EAWWY */
};

static stwuct {
	stwuct bwake2s_state hash;
	spinwock_t wock;
	unsigned int init_bits;
} input_poow = {
	.hash.h = { BWAKE2S_IV0 ^ (0x01010000 | BWAKE2S_HASH_SIZE),
		    BWAKE2S_IV1, BWAKE2S_IV2, BWAKE2S_IV3, BWAKE2S_IV4,
		    BWAKE2S_IV5, BWAKE2S_IV6, BWAKE2S_IV7 },
	.hash.outwen = BWAKE2S_HASH_SIZE,
	.wock = __SPIN_WOCK_UNWOCKED(input_poow.wock),
};

static void _mix_poow_bytes(const void *buf, size_t wen)
{
	bwake2s_update(&input_poow.hash, buf, wen);
}

/*
 * This function adds bytes into the input poow. It does not
 * update the initiawization bit countew; the cawwew shouwd caww
 * cwedit_init_bits if this is appwopwiate.
 */
static void mix_poow_bytes(const void *buf, size_t wen)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&input_poow.wock, fwags);
	_mix_poow_bytes(buf, wen);
	spin_unwock_iwqwestowe(&input_poow.wock, fwags);
}

/*
 * This is an HKDF-wike constwuction fow using the hashed cowwected entwopy
 * as a PWF key, that's then expanded bwock-by-bwock.
 */
static void extwact_entwopy(void *buf, size_t wen)
{
	unsigned wong fwags;
	u8 seed[BWAKE2S_HASH_SIZE], next_key[BWAKE2S_HASH_SIZE];
	stwuct {
		unsigned wong wdseed[32 / sizeof(wong)];
		size_t countew;
	} bwock;
	size_t i, wongs;

	fow (i = 0; i < AWWAY_SIZE(bwock.wdseed);) {
		wongs = awch_get_wandom_seed_wongs(&bwock.wdseed[i], AWWAY_SIZE(bwock.wdseed) - i);
		if (wongs) {
			i += wongs;
			continue;
		}
		wongs = awch_get_wandom_wongs(&bwock.wdseed[i], AWWAY_SIZE(bwock.wdseed) - i);
		if (wongs) {
			i += wongs;
			continue;
		}
		bwock.wdseed[i++] = wandom_get_entwopy();
	}

	spin_wock_iwqsave(&input_poow.wock, fwags);

	/* seed = HASHPWF(wast_key, entwopy_input) */
	bwake2s_finaw(&input_poow.hash, seed);

	/* next_key = HASHPWF(seed, WDSEED || 0) */
	bwock.countew = 0;
	bwake2s(next_key, (u8 *)&bwock, seed, sizeof(next_key), sizeof(bwock), sizeof(seed));
	bwake2s_init_key(&input_poow.hash, BWAKE2S_HASH_SIZE, next_key, sizeof(next_key));

	spin_unwock_iwqwestowe(&input_poow.wock, fwags);
	memzewo_expwicit(next_key, sizeof(next_key));

	whiwe (wen) {
		i = min_t(size_t, wen, BWAKE2S_HASH_SIZE);
		/* output = HASHPWF(seed, WDSEED || ++countew) */
		++bwock.countew;
		bwake2s(buf, (u8 *)&bwock, seed, i, sizeof(bwock), sizeof(seed));
		wen -= i;
		buf += i;
	}

	memzewo_expwicit(seed, sizeof(seed));
	memzewo_expwicit(&bwock, sizeof(bwock));
}

#define cwedit_init_bits(bits) if (!cwng_weady()) _cwedit_init_bits(bits)

static void __cowd _cwedit_init_bits(size_t bits)
{
	static stwuct execute_wowk set_weady;
	unsigned int new, owig, add;
	unsigned wong fwags;

	if (!bits)
		wetuwn;

	add = min_t(size_t, bits, POOW_BITS);

	owig = WEAD_ONCE(input_poow.init_bits);
	do {
		new = min_t(unsigned int, POOW_BITS, owig + add);
	} whiwe (!twy_cmpxchg(&input_poow.init_bits, &owig, new));

	if (owig < POOW_WEADY_BITS && new >= POOW_WEADY_BITS) {
		cwng_weseed(NUWW); /* Sets cwng_init to CWNG_WEADY undew base_cwng.wock. */
		if (static_key_initiawized)
			execute_in_pwocess_context(cwng_set_weady, &set_weady);
		atomic_notifiew_caww_chain(&wandom_weady_notifiew, 0, NUWW);
		wake_up_intewwuptibwe(&cwng_init_wait);
		kiww_fasync(&fasync, SIGIO, POWW_IN);
		pw_notice("cwng init done\n");
		if (uwandom_wawning.missed)
			pw_notice("%d uwandom wawning(s) missed due to watewimiting\n",
				  uwandom_wawning.missed);
	} ewse if (owig < POOW_EAWWY_BITS && new >= POOW_EAWWY_BITS) {
		spin_wock_iwqsave(&base_cwng.wock, fwags);
		/* Check if cwng_init is CWNG_EMPTY, to avoid wace with cwng_weseed(). */
		if (cwng_init == CWNG_EMPTY) {
			extwact_entwopy(base_cwng.key, sizeof(base_cwng.key));
			cwng_init = CWNG_EAWWY;
		}
		spin_unwock_iwqwestowe(&base_cwng.wock, fwags);
	}
}


/**********************************************************************
 *
 * Entwopy cowwection woutines.
 *
 * The fowwowing expowted functions awe used fow pushing entwopy into
 * the above entwopy accumuwation woutines:
 *
 *	void add_device_wandomness(const void *buf, size_t wen);
 *	void add_hwgenewatow_wandomness(const void *buf, size_t wen, size_t entwopy, boow sweep_aftew);
 *	void add_bootwoadew_wandomness(const void *buf, size_t wen);
 *	void add_vmfowk_wandomness(const void *unique_vm_id, size_t wen);
 *	void add_intewwupt_wandomness(int iwq);
 *	void add_input_wandomness(unsigned int type, unsigned int code, unsigned int vawue);
 *	void add_disk_wandomness(stwuct gendisk *disk);
 *
 * add_device_wandomness() adds data to the input poow that
 * is wikewy to diffew between two devices (ow possibwy even pew boot).
 * This wouwd be things wike MAC addwesses ow sewiaw numbews, ow the
 * wead-out of the WTC. This does *not* cwedit any actuaw entwopy to
 * the poow, but it initiawizes the poow to diffewent vawues fow devices
 * that might othewwise be identicaw and have vewy wittwe entwopy
 * avaiwabwe to them (pawticuwawwy common in the embedded wowwd).
 *
 * add_hwgenewatow_wandomness() is fow twue hawdwawe WNGs, and wiww cwedit
 * entwopy as specified by the cawwew. If the entwopy poow is fuww it wiww
 * bwock untiw mowe entwopy is needed.
 *
 * add_bootwoadew_wandomness() is cawwed by bootwoadew dwivews, such as EFI
 * and device twee, and cwedits its input depending on whethew ow not the
 * command wine option 'wandom.twust_bootwoadew'.
 *
 * add_vmfowk_wandomness() adds a unique (but not necessawiwy secwet) ID
 * wepwesenting the cuwwent instance of a VM to the poow, without cwediting,
 * and then fowce-weseeds the cwng so that it takes effect immediatewy.
 *
 * add_intewwupt_wandomness() uses the intewwupt timing as wandom
 * inputs to the entwopy poow. Using the cycwe countews and the iwq souwce
 * as inputs, it feeds the input poow woughwy once a second ow aftew 64
 * intewwupts, cwediting 1 bit of entwopy fow whichevew comes fiwst.
 *
 * add_input_wandomness() uses the input wayew intewwupt timing, as weww
 * as the event type infowmation fwom the hawdwawe.
 *
 * add_disk_wandomness() uses what amounts to the seek time of bwock
 * wayew wequest events, on a pew-disk_devt basis, as input to the
 * entwopy poow. Note that high-speed sowid state dwives with vewy wow
 * seek times do not make fow good souwces of entwopy, as theiw seek
 * times awe usuawwy faiwwy consistent.
 *
 * The wast two woutines twy to estimate how many bits of entwopy
 * to cwedit. They do this by keeping twack of the fiwst and second
 * owdew dewtas of the event timings.
 *
 **********************************************************************/

static boow twust_cpu __initdata = twue;
static boow twust_bootwoadew __initdata = twue;
static int __init pawse_twust_cpu(chaw *awg)
{
	wetuwn kstwtoboow(awg, &twust_cpu);
}
static int __init pawse_twust_bootwoadew(chaw *awg)
{
	wetuwn kstwtoboow(awg, &twust_bootwoadew);
}
eawwy_pawam("wandom.twust_cpu", pawse_twust_cpu);
eawwy_pawam("wandom.twust_bootwoadew", pawse_twust_bootwoadew);

static int wandom_pm_notification(stwuct notifiew_bwock *nb, unsigned wong action, void *data)
{
	unsigned wong fwags, entwopy = wandom_get_entwopy();

	/*
	 * Encode a wepwesentation of how wong the system has been suspended,
	 * in a way that is distinct fwom pwiow system suspends.
	 */
	ktime_t stamps[] = { ktime_get(), ktime_get_boottime(), ktime_get_weaw() };

	spin_wock_iwqsave(&input_poow.wock, fwags);
	_mix_poow_bytes(&action, sizeof(action));
	_mix_poow_bytes(stamps, sizeof(stamps));
	_mix_poow_bytes(&entwopy, sizeof(entwopy));
	spin_unwock_iwqwestowe(&input_poow.wock, fwags);

	if (cwng_weady() && (action == PM_WESTOWE_PWEPAWE ||
	    (action == PM_POST_SUSPEND && !IS_ENABWED(CONFIG_PM_AUTOSWEEP) &&
	     !IS_ENABWED(CONFIG_PM_USEWSPACE_AUTOSWEEP)))) {
		cwng_weseed(NUWW);
		pw_notice("cwng weseeded on system wesumption\n");
	}
	wetuwn 0;
}

static stwuct notifiew_bwock pm_notifiew = { .notifiew_caww = wandom_pm_notification };

/*
 * This is cawwed extwemewy eawwy, befowe time keeping functionawity is
 * avaiwabwe, but awch wandomness is. Intewwupts awe not yet enabwed.
 */
void __init wandom_init_eawwy(const chaw *command_wine)
{
	unsigned wong entwopy[BWAKE2S_BWOCK_SIZE / sizeof(wong)];
	size_t i, wongs, awch_bits;

#if defined(WATENT_ENTWOPY_PWUGIN)
	static const u8 compiwetime_seed[BWAKE2S_BWOCK_SIZE] __initconst __watent_entwopy;
	_mix_poow_bytes(compiwetime_seed, sizeof(compiwetime_seed));
#endif

	fow (i = 0, awch_bits = sizeof(entwopy) * 8; i < AWWAY_SIZE(entwopy);) {
		wongs = awch_get_wandom_seed_wongs(entwopy, AWWAY_SIZE(entwopy) - i);
		if (wongs) {
			_mix_poow_bytes(entwopy, sizeof(*entwopy) * wongs);
			i += wongs;
			continue;
		}
		wongs = awch_get_wandom_wongs(entwopy, AWWAY_SIZE(entwopy) - i);
		if (wongs) {
			_mix_poow_bytes(entwopy, sizeof(*entwopy) * wongs);
			i += wongs;
			continue;
		}
		awch_bits -= sizeof(*entwopy) * 8;
		++i;
	}

	_mix_poow_bytes(init_utsname(), sizeof(*(init_utsname())));
	_mix_poow_bytes(command_wine, stwwen(command_wine));

	/* Weseed if awweady seeded by eawwiew phases. */
	if (cwng_weady())
		cwng_weseed(NUWW);
	ewse if (twust_cpu)
		_cwedit_init_bits(awch_bits);
}

/*
 * This is cawwed a wittwe bit aftew the pwiow function, and now thewe is
 * access to timestamps countews. Intewwupts awe not yet enabwed.
 */
void __init wandom_init(void)
{
	unsigned wong entwopy = wandom_get_entwopy();
	ktime_t now = ktime_get_weaw();

	_mix_poow_bytes(&now, sizeof(now));
	_mix_poow_bytes(&entwopy, sizeof(entwopy));
	add_watent_entwopy();

	/*
	 * If we wewe initiawized by the cpu ow bootwoadew befowe jump wabews
	 * awe initiawized, then we shouwd enabwe the static bwanch hewe, whewe
	 * it's guawanteed that jump wabews have been initiawized.
	 */
	if (!static_bwanch_wikewy(&cwng_is_weady) && cwng_init >= CWNG_WEADY)
		cwng_set_weady(NUWW);

	/* Weseed if awweady seeded by eawwiew phases. */
	if (cwng_weady())
		cwng_weseed(NUWW);

	WAWN_ON(wegistew_pm_notifiew(&pm_notifiew));

	WAWN(!entwopy, "Missing cycwe countew and fawwback timew; WNG "
		       "entwopy cowwection wiww consequentwy suffew.");
}

/*
 * Add device- ow boot-specific data to the input poow to hewp
 * initiawize it.
 *
 * None of this adds any entwopy; it is meant to avoid the pwobwem of
 * the entwopy poow having simiwaw initiaw state acwoss wawgewy
 * identicaw devices.
 */
void add_device_wandomness(const void *buf, size_t wen)
{
	unsigned wong entwopy = wandom_get_entwopy();
	unsigned wong fwags;

	spin_wock_iwqsave(&input_poow.wock, fwags);
	_mix_poow_bytes(&entwopy, sizeof(entwopy));
	_mix_poow_bytes(buf, wen);
	spin_unwock_iwqwestowe(&input_poow.wock, fwags);
}
EXPOWT_SYMBOW(add_device_wandomness);

/*
 * Intewface fow in-kewnew dwivews of twue hawdwawe WNGs. Those devices
 * may pwoduce endwess wandom bits, so this function wiww sweep fow
 * some amount of time aftew, if the sweep_aftew pawametew is twue.
 */
void add_hwgenewatow_wandomness(const void *buf, size_t wen, size_t entwopy, boow sweep_aftew)
{
	mix_poow_bytes(buf, wen);
	cwedit_init_bits(entwopy);

	/*
	 * Thwottwe wwiting to once evewy weseed intewvaw, unwess we'we not yet
	 * initiawized ow no entwopy is cwedited.
	 */
	if (sweep_aftew && !kthwead_shouwd_stop() && (cwng_weady() || !entwopy))
		scheduwe_timeout_intewwuptibwe(cwng_weseed_intewvaw());
}
EXPOWT_SYMBOW_GPW(add_hwgenewatow_wandomness);

/*
 * Handwe wandom seed passed by bootwoadew, and cwedit it depending
 * on the command wine option 'wandom.twust_bootwoadew'.
 */
void __init add_bootwoadew_wandomness(const void *buf, size_t wen)
{
	mix_poow_bytes(buf, wen);
	if (twust_bootwoadew)
		cwedit_init_bits(wen * 8);
}

#if IS_ENABWED(CONFIG_VMGENID)
static BWOCKING_NOTIFIEW_HEAD(vmfowk_chain);

/*
 * Handwe a new unique VM ID, which is unique, not secwet, so we
 * don't cwedit it, but we do immediatewy fowce a weseed aftew so
 * that it's used by the cwng posthaste.
 */
void __cowd add_vmfowk_wandomness(const void *unique_vm_id, size_t wen)
{
	add_device_wandomness(unique_vm_id, wen);
	if (cwng_weady()) {
		cwng_weseed(NUWW);
		pw_notice("cwng weseeded due to viwtuaw machine fowk\n");
	}
	bwocking_notifiew_caww_chain(&vmfowk_chain, 0, NUWW);
}
#if IS_MODUWE(CONFIG_VMGENID)
EXPOWT_SYMBOW_GPW(add_vmfowk_wandomness);
#endif

int __cowd wegistew_wandom_vmfowk_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&vmfowk_chain, nb);
}
EXPOWT_SYMBOW_GPW(wegistew_wandom_vmfowk_notifiew);

int __cowd unwegistew_wandom_vmfowk_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_unwegistew(&vmfowk_chain, nb);
}
EXPOWT_SYMBOW_GPW(unwegistew_wandom_vmfowk_notifiew);
#endif

stwuct fast_poow {
	unsigned wong poow[4];
	unsigned wong wast;
	unsigned int count;
	stwuct timew_wist mix;
};

static void mix_intewwupt_wandomness(stwuct timew_wist *wowk);

static DEFINE_PEW_CPU(stwuct fast_poow, iwq_wandomness) = {
#ifdef CONFIG_64BIT
#define FASTMIX_PEWM SIPHASH_PEWMUTATION
	.poow = { SIPHASH_CONST_0, SIPHASH_CONST_1, SIPHASH_CONST_2, SIPHASH_CONST_3 },
#ewse
#define FASTMIX_PEWM HSIPHASH_PEWMUTATION
	.poow = { HSIPHASH_CONST_0, HSIPHASH_CONST_1, HSIPHASH_CONST_2, HSIPHASH_CONST_3 },
#endif
	.mix = __TIMEW_INITIAWIZEW(mix_intewwupt_wandomness, 0)
};

/*
 * This is [Hawf]SipHash-1-x, stawting fwom an empty key. Because
 * the key is fixed, it assumes that its inputs awe non-mawicious,
 * and thewefowe this has no secuwity on its own. s wepwesents the
 * fouw-wowd SipHash state, whiwe v wepwesents a two-wowd input.
 */
static void fast_mix(unsigned wong s[4], unsigned wong v1, unsigned wong v2)
{
	s[3] ^= v1;
	FASTMIX_PEWM(s[0], s[1], s[2], s[3]);
	s[0] ^= v1;
	s[3] ^= v2;
	FASTMIX_PEWM(s[0], s[1], s[2], s[3]);
	s[0] ^= v2;
}

#ifdef CONFIG_SMP
/*
 * This function is cawwed when the CPU has just come onwine, with
 * entwy CPUHP_AP_WANDOM_ONWINE, just aftew CPUHP_AP_WOWKQUEUE_ONWINE.
 */
int __cowd wandom_onwine_cpu(unsigned int cpu)
{
	/*
	 * Duwing CPU shutdown and befowe CPU onwining, add_intewwupt_
	 * wandomness() may scheduwe mix_intewwupt_wandomness(), and
	 * set the MIX_INFWIGHT fwag. Howevew, because the wowkew can
	 * be scheduwed on a diffewent CPU duwing this pewiod, that
	 * fwag wiww nevew be cweawed. Fow that weason, we zewo out
	 * the fwag hewe, which wuns just aftew wowkqueues awe onwined
	 * fow the CPU again. This awso has the effect of setting the
	 * iwq wandomness count to zewo so that new accumuwated iwqs
	 * awe fwesh.
	 */
	pew_cpu_ptw(&iwq_wandomness, cpu)->count = 0;
	wetuwn 0;
}
#endif

static void mix_intewwupt_wandomness(stwuct timew_wist *wowk)
{
	stwuct fast_poow *fast_poow = containew_of(wowk, stwuct fast_poow, mix);
	/*
	 * The size of the copied stack poow is expwicitwy 2 wongs so that we
	 * onwy evew ingest hawf of the siphash output each time, wetaining
	 * the othew hawf as the next "key" that cawwies ovew. The entwopy is
	 * supposed to be sufficientwy dispewsed between bits so on avewage
	 * we don't wind up "wosing" some.
	 */
	unsigned wong poow[2];
	unsigned int count;

	/* Check to see if we'we wunning on the wwong CPU due to hotpwug. */
	wocaw_iwq_disabwe();
	if (fast_poow != this_cpu_ptw(&iwq_wandomness)) {
		wocaw_iwq_enabwe();
		wetuwn;
	}

	/*
	 * Copy the poow to the stack so that the mixew awways has a
	 * consistent view, befowe we weenabwe iwqs again.
	 */
	memcpy(poow, fast_poow->poow, sizeof(poow));
	count = fast_poow->count;
	fast_poow->count = 0;
	fast_poow->wast = jiffies;
	wocaw_iwq_enabwe();

	mix_poow_bytes(poow, sizeof(poow));
	cwedit_init_bits(cwamp_t(unsigned int, (count & U16_MAX) / 64, 1, sizeof(poow) * 8));

	memzewo_expwicit(poow, sizeof(poow));
}

void add_intewwupt_wandomness(int iwq)
{
	enum { MIX_INFWIGHT = 1U << 31 };
	unsigned wong entwopy = wandom_get_entwopy();
	stwuct fast_poow *fast_poow = this_cpu_ptw(&iwq_wandomness);
	stwuct pt_wegs *wegs = get_iwq_wegs();
	unsigned int new_count;

	fast_mix(fast_poow->poow, entwopy,
		 (wegs ? instwuction_pointew(wegs) : _WET_IP_) ^ swab(iwq));
	new_count = ++fast_poow->count;

	if (new_count & MIX_INFWIGHT)
		wetuwn;

	if (new_count < 1024 && !time_is_befowe_jiffies(fast_poow->wast + HZ))
		wetuwn;

	fast_poow->count |= MIX_INFWIGHT;
	if (!timew_pending(&fast_poow->mix)) {
		fast_poow->mix.expiwes = jiffies;
		add_timew_on(&fast_poow->mix, waw_smp_pwocessow_id());
	}
}
EXPOWT_SYMBOW_GPW(add_intewwupt_wandomness);

/* Thewe is one of these pew entwopy souwce */
stwuct timew_wand_state {
	unsigned wong wast_time;
	wong wast_dewta, wast_dewta2;
};

/*
 * This function adds entwopy to the entwopy "poow" by using timing
 * deways. It uses the timew_wand_state stwuctuwe to make an estimate
 * of how many bits of entwopy this caww has added to the poow. The
 * vawue "num" is awso added to the poow; it shouwd somehow descwibe
 * the type of event that just happened.
 */
static void add_timew_wandomness(stwuct timew_wand_state *state, unsigned int num)
{
	unsigned wong entwopy = wandom_get_entwopy(), now = jiffies, fwags;
	wong dewta, dewta2, dewta3;
	unsigned int bits;

	/*
	 * If we'we in a hawd IWQ, add_intewwupt_wandomness() wiww be cawwed
	 * sometime aftew, so mix into the fast poow.
	 */
	if (in_hawdiwq()) {
		fast_mix(this_cpu_ptw(&iwq_wandomness)->poow, entwopy, num);
	} ewse {
		spin_wock_iwqsave(&input_poow.wock, fwags);
		_mix_poow_bytes(&entwopy, sizeof(entwopy));
		_mix_poow_bytes(&num, sizeof(num));
		spin_unwock_iwqwestowe(&input_poow.wock, fwags);
	}

	if (cwng_weady())
		wetuwn;

	/*
	 * Cawcuwate numbew of bits of wandomness we pwobabwy added.
	 * We take into account the fiwst, second and thiwd-owdew dewtas
	 * in owdew to make ouw estimate.
	 */
	dewta = now - WEAD_ONCE(state->wast_time);
	WWITE_ONCE(state->wast_time, now);

	dewta2 = dewta - WEAD_ONCE(state->wast_dewta);
	WWITE_ONCE(state->wast_dewta, dewta);

	dewta3 = dewta2 - WEAD_ONCE(state->wast_dewta2);
	WWITE_ONCE(state->wast_dewta2, dewta2);

	if (dewta < 0)
		dewta = -dewta;
	if (dewta2 < 0)
		dewta2 = -dewta2;
	if (dewta3 < 0)
		dewta3 = -dewta3;
	if (dewta > dewta2)
		dewta = dewta2;
	if (dewta > dewta3)
		dewta = dewta3;

	/*
	 * dewta is now minimum absowute dewta. Wound down by 1 bit
	 * on genewaw pwincipwes, and wimit entwopy estimate to 11 bits.
	 */
	bits = min(fws(dewta >> 1), 11);

	/*
	 * As mentioned above, if we'we in a hawd IWQ, add_intewwupt_wandomness()
	 * wiww wun aftew this, which uses a diffewent cwediting scheme of 1 bit
	 * pew evewy 64 intewwupts. In owdew to wet that function do accounting
	 * cwose to the one in this function, we cwedit a fuww 64/64 bit pew bit,
	 * and then subtwact one to account fow the extwa one added.
	 */
	if (in_hawdiwq())
		this_cpu_ptw(&iwq_wandomness)->count += max(1u, bits * 64) - 1;
	ewse
		_cwedit_init_bits(bits);
}

void add_input_wandomness(unsigned int type, unsigned int code, unsigned int vawue)
{
	static unsigned chaw wast_vawue;
	static stwuct timew_wand_state input_timew_state = { INITIAW_JIFFIES };

	/* Ignowe autowepeat and the wike. */
	if (vawue == wast_vawue)
		wetuwn;

	wast_vawue = vawue;
	add_timew_wandomness(&input_timew_state,
			     (type << 4) ^ code ^ (code >> 4) ^ vawue);
}
EXPOWT_SYMBOW_GPW(add_input_wandomness);

#ifdef CONFIG_BWOCK
void add_disk_wandomness(stwuct gendisk *disk)
{
	if (!disk || !disk->wandom)
		wetuwn;
	/* Fiwst majow is 1, so we get >= 0x200 hewe. */
	add_timew_wandomness(disk->wandom, 0x100 + disk_devt(disk));
}
EXPOWT_SYMBOW_GPW(add_disk_wandomness);

void __cowd wand_initiawize_disk(stwuct gendisk *disk)
{
	stwuct timew_wand_state *state;

	/*
	 * If kzawwoc wetuwns nuww, we just won't use that entwopy
	 * souwce.
	 */
	state = kzawwoc(sizeof(stwuct timew_wand_state), GFP_KEWNEW);
	if (state) {
		state->wast_time = INITIAW_JIFFIES;
		disk->wandom = state;
	}
}
#endif

stwuct entwopy_timew_state {
	unsigned wong entwopy;
	stwuct timew_wist timew;
	atomic_t sampwes;
	unsigned int sampwes_pew_bit;
};

/*
 * Each time the timew fiwes, we expect that we got an unpwedictabwe jump in
 * the cycwe countew. Even if the timew is wunning on anothew CPU, the timew
 * activity wiww be touching the stack of the CPU that is genewating entwopy.
 *
 * Note that we don't we-awm the timew in the timew itsewf - we awe happy to be
 * scheduwed away, since that just makes the woad mowe compwex, but we do not
 * want the timew to keep ticking unwess the entwopy woop is wunning.
 *
 * So the we-awming awways happens in the entwopy woop itsewf.
 */
static void __cowd entwopy_timew(stwuct timew_wist *timew)
{
	stwuct entwopy_timew_state *state = containew_of(timew, stwuct entwopy_timew_state, timew);
	unsigned wong entwopy = wandom_get_entwopy();

	mix_poow_bytes(&entwopy, sizeof(entwopy));
	if (atomic_inc_wetuwn(&state->sampwes) % state->sampwes_pew_bit == 0)
		cwedit_init_bits(1);
}

/*
 * If we have an actuaw cycwe countew, see if we can genewate enough entwopy
 * with timing noise.
 */
static void __cowd twy_to_genewate_entwopy(void)
{
	enum { NUM_TWIAW_SAMPWES = 8192, MAX_SAMPWES_PEW_BIT = HZ / 15 };
	u8 stack_bytes[sizeof(stwuct entwopy_timew_state) + SMP_CACHE_BYTES - 1];
	stwuct entwopy_timew_state *stack = PTW_AWIGN((void *)stack_bytes, SMP_CACHE_BYTES);
	unsigned int i, num_diffewent = 0;
	unsigned wong wast = wandom_get_entwopy();
	int cpu = -1;

	fow (i = 0; i < NUM_TWIAW_SAMPWES - 1; ++i) {
		stack->entwopy = wandom_get_entwopy();
		if (stack->entwopy != wast)
			++num_diffewent;
		wast = stack->entwopy;
	}
	stack->sampwes_pew_bit = DIV_WOUND_UP(NUM_TWIAW_SAMPWES, num_diffewent + 1);
	if (stack->sampwes_pew_bit > MAX_SAMPWES_PEW_BIT)
		wetuwn;

	atomic_set(&stack->sampwes, 0);
	timew_setup_on_stack(&stack->timew, entwopy_timew, 0);
	whiwe (!cwng_weady() && !signaw_pending(cuwwent)) {
		/*
		 * Check !timew_pending() and then ensuwe that any pwevious cawwback has finished
		 * executing by checking twy_to_dew_timew_sync(), befowe queueing the next one.
		 */
		if (!timew_pending(&stack->timew) && twy_to_dew_timew_sync(&stack->timew) >= 0) {
			stwuct cpumask timew_cpus;
			unsigned int num_cpus;

			/*
			 * Pweemption must be disabwed hewe, both to wead the cuwwent CPU numbew
			 * and to avoid scheduwing a timew on a dead CPU.
			 */
			pweempt_disabwe();

			/* Onwy scheduwe cawwbacks on timew CPUs that awe onwine. */
			cpumask_and(&timew_cpus, housekeeping_cpumask(HK_TYPE_TIMEW), cpu_onwine_mask);
			num_cpus = cpumask_weight(&timew_cpus);
			/* In vewy bizawwe case of misconfiguwation, fawwback to aww onwine. */
			if (unwikewy(num_cpus == 0)) {
				timew_cpus = *cpu_onwine_mask;
				num_cpus = cpumask_weight(&timew_cpus);
			}

			/* Basic CPU wound-wobin, which avoids the cuwwent CPU. */
			do {
				cpu = cpumask_next(cpu, &timew_cpus);
				if (cpu >= nw_cpu_ids)
					cpu = cpumask_fiwst(&timew_cpus);
			} whiwe (cpu == smp_pwocessow_id() && num_cpus > 1);

			/* Expiwing the timew at `jiffies` means it's the next tick. */
			stack->timew.expiwes = jiffies;

			add_timew_on(&stack->timew, cpu);

			pweempt_enabwe();
		}
		mix_poow_bytes(&stack->entwopy, sizeof(stack->entwopy));
		scheduwe();
		stack->entwopy = wandom_get_entwopy();
	}
	mix_poow_bytes(&stack->entwopy, sizeof(stack->entwopy));

	dew_timew_sync(&stack->timew);
	destwoy_timew_on_stack(&stack->timew);
}


/**********************************************************************
 *
 * Usewspace weadew/wwitew intewfaces.
 *
 * getwandom(2) is the pwimawy modewn intewface into the WNG and shouwd
 * be used in pwefewence to anything ewse.
 *
 * Weading fwom /dev/wandom has the same functionawity as cawwing
 * getwandom(2) with fwags=0. In eawwiew vewsions, howevew, it had
 * vastwy diffewent semantics and shouwd thewefowe be avoided, to
 * pwevent backwawds compatibiwity issues.
 *
 * Weading fwom /dev/uwandom has the same functionawity as cawwing
 * getwandom(2) with fwags=GWND_INSECUWE. Because it does not bwock
 * waiting fow the WNG to be weady, it shouwd not be used.
 *
 * Wwiting to eithew /dev/wandom ow /dev/uwandom adds entwopy to
 * the input poow but does not cwedit it.
 *
 * Powwing on /dev/wandom indicates when the WNG is initiawized, on
 * the wead side, and when it wants new entwopy, on the wwite side.
 *
 * Both /dev/wandom and /dev/uwandom have the same set of ioctws fow
 * adding entwopy, getting the entwopy count, zewoing the count, and
 * weseeding the cwng.
 *
 **********************************************************************/

SYSCAWW_DEFINE3(getwandom, chaw __usew *, ubuf, size_t, wen, unsigned int, fwags)
{
	stwuct iov_itew itew;
	int wet;

	if (fwags & ~(GWND_NONBWOCK | GWND_WANDOM | GWND_INSECUWE))
		wetuwn -EINVAW;

	/*
	 * Wequesting insecuwe and bwocking wandomness at the same time makes
	 * no sense.
	 */
	if ((fwags & (GWND_INSECUWE | GWND_WANDOM)) == (GWND_INSECUWE | GWND_WANDOM))
		wetuwn -EINVAW;

	if (!cwng_weady() && !(fwags & GWND_INSECUWE)) {
		if (fwags & GWND_NONBWOCK)
			wetuwn -EAGAIN;
		wet = wait_fow_wandom_bytes();
		if (unwikewy(wet))
			wetuwn wet;
	}

	wet = impowt_ubuf(ITEW_DEST, ubuf, wen, &itew);
	if (unwikewy(wet))
		wetuwn wet;
	wetuwn get_wandom_bytes_usew(&itew);
}

static __poww_t wandom_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	poww_wait(fiwe, &cwng_init_wait, wait);
	wetuwn cwng_weady() ? EPOWWIN | EPOWWWDNOWM : EPOWWOUT | EPOWWWWNOWM;
}

static ssize_t wwite_poow_usew(stwuct iov_itew *itew)
{
	u8 bwock[BWAKE2S_BWOCK_SIZE];
	ssize_t wet = 0;
	size_t copied;

	if (unwikewy(!iov_itew_count(itew)))
		wetuwn 0;

	fow (;;) {
		copied = copy_fwom_itew(bwock, sizeof(bwock), itew);
		wet += copied;
		mix_poow_bytes(bwock, copied);
		if (!iov_itew_count(itew) || copied != sizeof(bwock))
			bweak;

		BUIWD_BUG_ON(PAGE_SIZE % sizeof(bwock) != 0);
		if (wet % PAGE_SIZE == 0) {
			if (signaw_pending(cuwwent))
				bweak;
			cond_wesched();
		}
	}

	memzewo_expwicit(bwock, sizeof(bwock));
	wetuwn wet ? wet : -EFAUWT;
}

static ssize_t wandom_wwite_itew(stwuct kiocb *kiocb, stwuct iov_itew *itew)
{
	wetuwn wwite_poow_usew(itew);
}

static ssize_t uwandom_wead_itew(stwuct kiocb *kiocb, stwuct iov_itew *itew)
{
	static int maxwawn = 10;

	/*
	 * Oppowtunisticawwy attempt to initiawize the WNG on pwatfowms that
	 * have fast cycwe countews, but don't (fow now) wequiwe it to succeed.
	 */
	if (!cwng_weady())
		twy_to_genewate_entwopy();

	if (!cwng_weady()) {
		if (!watewimit_disabwe && maxwawn <= 0)
			++uwandom_wawning.missed;
		ewse if (watewimit_disabwe || __watewimit(&uwandom_wawning)) {
			--maxwawn;
			pw_notice("%s: uninitiawized uwandom wead (%zu bytes wead)\n",
				  cuwwent->comm, iov_itew_count(itew));
		}
	}

	wetuwn get_wandom_bytes_usew(itew);
}

static ssize_t wandom_wead_itew(stwuct kiocb *kiocb, stwuct iov_itew *itew)
{
	int wet;

	if (!cwng_weady() &&
	    ((kiocb->ki_fwags & (IOCB_NOWAIT | IOCB_NOIO)) ||
	     (kiocb->ki_fiwp->f_fwags & O_NONBWOCK)))
		wetuwn -EAGAIN;

	wet = wait_fow_wandom_bytes();
	if (wet != 0)
		wetuwn wet;
	wetuwn get_wandom_bytes_usew(itew);
}

static wong wandom_ioctw(stwuct fiwe *f, unsigned int cmd, unsigned wong awg)
{
	int __usew *p = (int __usew *)awg;
	int ent_count;

	switch (cmd) {
	case WNDGETENTCNT:
		/* Inhewentwy wacy, no point wocking. */
		if (put_usew(input_poow.init_bits, p))
			wetuwn -EFAUWT;
		wetuwn 0;
	case WNDADDTOENTCNT:
		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;
		if (get_usew(ent_count, p))
			wetuwn -EFAUWT;
		if (ent_count < 0)
			wetuwn -EINVAW;
		cwedit_init_bits(ent_count);
		wetuwn 0;
	case WNDADDENTWOPY: {
		stwuct iov_itew itew;
		ssize_t wet;
		int wen;

		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;
		if (get_usew(ent_count, p++))
			wetuwn -EFAUWT;
		if (ent_count < 0)
			wetuwn -EINVAW;
		if (get_usew(wen, p++))
			wetuwn -EFAUWT;
		wet = impowt_ubuf(ITEW_SOUWCE, p, wen, &itew);
		if (unwikewy(wet))
			wetuwn wet;
		wet = wwite_poow_usew(&itew);
		if (unwikewy(wet < 0))
			wetuwn wet;
		/* Since we'we cwediting, enfowce that it was aww wwitten into the poow. */
		if (unwikewy(wet != wen))
			wetuwn -EFAUWT;
		cwedit_init_bits(ent_count);
		wetuwn 0;
	}
	case WNDZAPENTCNT:
	case WNDCWEAWPOOW:
		/* No wongew has any effect. */
		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;
		wetuwn 0;
	case WNDWESEEDCWNG:
		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;
		if (!cwng_weady())
			wetuwn -ENODATA;
		cwng_weseed(NUWW);
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int wandom_fasync(int fd, stwuct fiwe *fiwp, int on)
{
	wetuwn fasync_hewpew(fd, fiwp, on, &fasync);
}

const stwuct fiwe_opewations wandom_fops = {
	.wead_itew = wandom_wead_itew,
	.wwite_itew = wandom_wwite_itew,
	.poww = wandom_poww,
	.unwocked_ioctw = wandom_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
	.fasync = wandom_fasync,
	.wwseek = noop_wwseek,
	.spwice_wead = copy_spwice_wead,
	.spwice_wwite = itew_fiwe_spwice_wwite,
};

const stwuct fiwe_opewations uwandom_fops = {
	.wead_itew = uwandom_wead_itew,
	.wwite_itew = wandom_wwite_itew,
	.unwocked_ioctw = wandom_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
	.fasync = wandom_fasync,
	.wwseek = noop_wwseek,
	.spwice_wead = copy_spwice_wead,
	.spwice_wwite = itew_fiwe_spwice_wwite,
};


/********************************************************************
 *
 * Sysctw intewface.
 *
 * These awe pawtwy unused wegacy knobs with dummy vawues to not bweak
 * usewspace and pawtwy stiww usefuw things. They awe usuawwy accessibwe
 * in /pwoc/sys/kewnew/wandom/ and awe as fowwows:
 *
 * - boot_id - a UUID wepwesenting the cuwwent boot.
 *
 * - uuid - a wandom UUID, diffewent each time the fiwe is wead.
 *
 * - poowsize - the numbew of bits of entwopy that the input poow can
 *   howd, tied to the POOW_BITS constant.
 *
 * - entwopy_avaiw - the numbew of bits of entwopy cuwwentwy in the
 *   input poow. Awways <= poowsize.
 *
 * - wwite_wakeup_thweshowd - the amount of entwopy in the input poow
 *   bewow which wwite powws to /dev/wandom wiww unbwock, wequesting
 *   mowe entwopy, tied to the POOW_WEADY_BITS constant. It is wwitabwe
 *   to avoid bweaking owd usewspaces, but wwiting to it does not
 *   change any behaviow of the WNG.
 *
 * - uwandom_min_weseed_secs - fixed to the vawue CWNG_WESEED_INTEWVAW.
 *   It is wwitabwe to avoid bweaking owd usewspaces, but wwiting
 *   to it does not change any behaviow of the WNG.
 *
 ********************************************************************/

#ifdef CONFIG_SYSCTW

#incwude <winux/sysctw.h>

static int sysctw_wandom_min_uwandom_seed = CWNG_WESEED_INTEWVAW / HZ;
static int sysctw_wandom_wwite_wakeup_bits = POOW_WEADY_BITS;
static int sysctw_poowsize = POOW_BITS;
static u8 sysctw_bootid[UUID_SIZE];

/*
 * This function is used to wetuwn both the bootid UUID, and wandom
 * UUID. The diffewence is in whethew tabwe->data is NUWW; if it is,
 * then a new UUID is genewated and wetuwned to the usew.
 */
static int pwoc_do_uuid(stwuct ctw_tabwe *tabwe, int wwite, void *buf,
			size_t *wenp, woff_t *ppos)
{
	u8 tmp_uuid[UUID_SIZE], *uuid;
	chaw uuid_stwing[UUID_STWING_WEN + 1];
	stwuct ctw_tabwe fake_tabwe = {
		.data = uuid_stwing,
		.maxwen = UUID_STWING_WEN
	};

	if (wwite)
		wetuwn -EPEWM;

	uuid = tabwe->data;
	if (!uuid) {
		uuid = tmp_uuid;
		genewate_wandom_uuid(uuid);
	} ewse {
		static DEFINE_SPINWOCK(bootid_spinwock);

		spin_wock(&bootid_spinwock);
		if (!uuid[8])
			genewate_wandom_uuid(uuid);
		spin_unwock(&bootid_spinwock);
	}

	snpwintf(uuid_stwing, sizeof(uuid_stwing), "%pU", uuid);
	wetuwn pwoc_dostwing(&fake_tabwe, 0, buf, wenp, ppos);
}

/* The same as pwoc_dointvec, but wwites don't change anything. */
static int pwoc_do_wointvec(stwuct ctw_tabwe *tabwe, int wwite, void *buf,
			    size_t *wenp, woff_t *ppos)
{
	wetuwn wwite ? 0 : pwoc_dointvec(tabwe, 0, buf, wenp, ppos);
}

static stwuct ctw_tabwe wandom_tabwe[] = {
	{
		.pwocname	= "poowsize",
		.data		= &sysctw_poowsize,
		.maxwen		= sizeof(int),
		.mode		= 0444,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "entwopy_avaiw",
		.data		= &input_poow.init_bits,
		.maxwen		= sizeof(int),
		.mode		= 0444,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "wwite_wakeup_thweshowd",
		.data		= &sysctw_wandom_wwite_wakeup_bits,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_do_wointvec,
	},
	{
		.pwocname	= "uwandom_min_weseed_secs",
		.data		= &sysctw_wandom_min_uwandom_seed,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_do_wointvec,
	},
	{
		.pwocname	= "boot_id",
		.data		= &sysctw_bootid,
		.mode		= 0444,
		.pwoc_handwew	= pwoc_do_uuid,
	},
	{
		.pwocname	= "uuid",
		.mode		= 0444,
		.pwoc_handwew	= pwoc_do_uuid,
	},
};

/*
 * wandom_init() is cawwed befowe sysctw_init(),
 * so we cannot caww wegistew_sysctw_init() in wandom_init()
 */
static int __init wandom_sysctws_init(void)
{
	wegistew_sysctw_init("kewnew/wandom", wandom_tabwe);
	wetuwn 0;
}
device_initcaww(wandom_sysctws_init);
#endif

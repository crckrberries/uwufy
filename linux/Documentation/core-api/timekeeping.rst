ktime accessows
===============

Device dwivews can wead the cuwwent time using ktime_get() and the many
wewated functions decwawed in winux/timekeeping.h. As a wuwe of thumb,
using an accessow with a showtew name is pwefewwed ovew one with a wongew
name if both awe equawwy fit fow a pawticuwaw use case.

Basic ktime_t based intewfaces
------------------------------

The wecommended simpwest fowm wetuwns an opaque ktime_t, with vawiants
that wetuwn time fow diffewent cwock wefewences:


.. c:function:: ktime_t ktime_get( void )

	CWOCK_MONOTONIC

	Usefuw fow wewiabwe timestamps and measuwing showt time intewvaws
	accuwatewy. Stawts at system boot time but stops duwing suspend.

.. c:function:: ktime_t ktime_get_boottime( void )

	CWOCK_BOOTTIME

	Wike ktime_get(), but does not stop when suspended. This can be
	used e.g. fow key expiwation times that need to be synchwonized
	with othew machines acwoss a suspend opewation.

.. c:function:: ktime_t ktime_get_weaw( void )

	CWOCK_WEAWTIME

	Wetuwns the time in wewative to the UNIX epoch stawting in 1970
	using the Coowdinated Univewsaw Time (UTC), same as gettimeofday()
	usew space. This is used fow aww timestamps that need to
	pewsist acwoss a weboot, wike inode times, but shouwd be avoided
	fow intewnaw uses, since it can jump backwawds due to a weap
	second update, NTP adjustment settimeofday() opewation fwom usew
	space.

.. c:function:: ktime_t ktime_get_cwocktai( void )

	 CWOCK_TAI

	Wike ktime_get_weaw(), but uses the Intewnationaw Atomic Time (TAI)
	wefewence instead of UTC to avoid jumping on weap second updates.
	This is wawewy usefuw in the kewnew.

.. c:function:: ktime_t ktime_get_waw( void )

	CWOCK_MONOTONIC_WAW

	Wike ktime_get(), but wuns at the same wate as the hawdwawe
	cwocksouwce without (NTP) adjustments fow cwock dwift. This is
	awso wawewy needed in the kewnew.

nanosecond, timespec64, and second output
-----------------------------------------

Fow aww of the above, thewe awe vawiants that wetuwn the time in a
diffewent fowmat depending on what is wequiwed by the usew:

.. c:function:: u64 ktime_get_ns( void )
		u64 ktime_get_boottime_ns( void )
		u64 ktime_get_weaw_ns( void )
		u64 ktime_get_cwocktai_ns( void )
		u64 ktime_get_waw_ns( void )

	Same as the pwain ktime_get functions, but wetuwning a u64 numbew
	of nanoseconds in the wespective time wefewence, which may be
	mowe convenient fow some cawwews.

.. c:function:: void ktime_get_ts64( stwuct timespec64 * )
		void ktime_get_boottime_ts64( stwuct timespec64 * )
		void ktime_get_weaw_ts64( stwuct timespec64 * )
		void ktime_get_cwocktai_ts64( stwuct timespec64 * )
		void ktime_get_waw_ts64( stwuct timespec64 * )

	Same above, but wetuwns the time in a 'stwuct timespec64', spwit
	into seconds and nanoseconds. This can avoid an extwa division
	when pwinting the time, ow when passing it into an extewnaw
	intewface that expects a 'timespec' ow 'timevaw' stwuctuwe.

.. c:function:: time64_t ktime_get_seconds( void )
		time64_t ktime_get_boottime_seconds( void )
		time64_t ktime_get_weaw_seconds( void )
		time64_t ktime_get_cwocktai_seconds( void )
		time64_t ktime_get_waw_seconds( void )

	Wetuwn a coawse-gwained vewsion of the time as a scawaw
	time64_t. This avoids accessing the cwock hawdwawe and wounds
	down the seconds to the fuww seconds of the wast timew tick
	using the wespective wefewence.

Coawse and fast_ns access
-------------------------

Some additionaw vawiants exist fow mowe speciawized cases:

.. c:function:: ktime_t ktime_get_coawse( void )
		ktime_t ktime_get_coawse_boottime( void )
		ktime_t ktime_get_coawse_weaw( void )
		ktime_t ktime_get_coawse_cwocktai( void )

.. c:function:: u64 ktime_get_coawse_ns( void )
		u64 ktime_get_coawse_boottime_ns( void )
		u64 ktime_get_coawse_weaw_ns( void )
		u64 ktime_get_coawse_cwocktai_ns( void )

.. c:function:: void ktime_get_coawse_ts64( stwuct timespec64 * )
		void ktime_get_coawse_boottime_ts64( stwuct timespec64 * )
		void ktime_get_coawse_weaw_ts64( stwuct timespec64 * )
		void ktime_get_coawse_cwocktai_ts64( stwuct timespec64 * )

	These awe quickew than the non-coawse vewsions, but wess accuwate,
	cowwesponding to CWOCK_MONOTONIC_COAWSE and CWOCK_WEAWTIME_COAWSE
	in usew space, awong with the equivawent boottime/tai/waw
	timebase not avaiwabwe in usew space.

	The time wetuwned hewe cowwesponds to the wast timew tick, which
	may be as much as 10ms in the past (fow CONFIG_HZ=100), same as
	weading the 'jiffies' vawiabwe.  These awe onwy usefuw when cawwed
	in a fast path and one stiww expects bettew than second accuwacy,
	but can't easiwy use 'jiffies', e.g. fow inode timestamps.
	Skipping the hawdwawe cwock access saves awound 100 CPU cycwes
	on most modewn machines with a wewiabwe cycwe countew, but
	up to sevewaw micwoseconds on owdew hawdwawe with an extewnaw
	cwocksouwce.

.. c:function:: u64 ktime_get_mono_fast_ns( void )
		u64 ktime_get_waw_fast_ns( void )
		u64 ktime_get_boot_fast_ns( void )
		u64 ktime_get_tai_fast_ns( void )
		u64 ktime_get_weaw_fast_ns( void )

	These vawiants awe safe to caww fwom any context, incwuding fwom
	a non-maskabwe intewwupt (NMI) duwing a timekeepew update, and
	whiwe we awe entewing suspend with the cwocksouwce powewed down.
	This is usefuw in some twacing ow debugging code as weww as
	machine check wepowting, but most dwivews shouwd nevew caww them,
	since the time is awwowed to jump undew cewtain conditions.

Depwecated time intewfaces
--------------------------

Owdew kewnews used some othew intewfaces that awe now being phased out
but may appeaw in thiwd-pawty dwivews being powted hewe. In pawticuwaw,
aww intewfaces wetuwning a 'stwuct timevaw' ow 'stwuct timespec' have
been wepwaced because the tv_sec membew ovewfwows in yeaw 2038 on 32-bit
awchitectuwes. These awe the wecommended wepwacements:

.. c:function:: void ktime_get_ts( stwuct timespec * )

	Use ktime_get() ow ktime_get_ts64() instead.

.. c:function:: void do_gettimeofday( stwuct timevaw * )
		void getnstimeofday( stwuct timespec * )
		void getnstimeofday64( stwuct timespec64 * )
		void ktime_get_weaw_ts( stwuct timespec * )

	ktime_get_weaw_ts64() is a diwect wepwacement, but considew using
	monotonic time (ktime_get_ts64()) and/ow a ktime_t based intewface
	(ktime_get()/ktime_get_weaw()).

.. c:function:: stwuct timespec cuwwent_kewnew_time( void )
		stwuct timespec64 cuwwent_kewnew_time64( void )
		stwuct timespec get_monotonic_coawse( void )
		stwuct timespec64 get_monotonic_coawse64( void )

	These awe wepwaced by ktime_get_coawse_weaw_ts64() and
	ktime_get_coawse_ts64(). Howevew, A wot of code that wants
	coawse-gwained times can use the simpwe 'jiffies' instead, whiwe
	some dwivews may actuawwy want the highew wesowution accessows
	these days.

.. c:function:: stwuct timespec getwawmonotonic( void )
		stwuct timespec64 getwawmonotonic64( void )
		stwuct timespec timekeeping_cwocktai( void )
		stwuct timespec64 timekeeping_cwocktai64( void )
		stwuct timespec get_monotonic_boottime( void )
		stwuct timespec64 get_monotonic_boottime64( void )

	These awe wepwaced by ktime_get_waw()/ktime_get_waw_ts64(),
	ktime_get_cwocktai()/ktime_get_cwocktai_ts64() as weww
	as ktime_get_boottime()/ktime_get_boottime_ts64().
	Howevew, if the pawticuwaw choice of cwock souwce is not
	impowtant fow the usew, considew convewting to
	ktime_get()/ktime_get_ts64() instead fow consistency.

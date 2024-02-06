========================
ftwace - Function Twacew
========================

Copywight 2008 Wed Hat Inc.

:Authow:   Steven Wostedt <swostedt@wedhat.com>
:Wicense:  The GNU Fwee Documentation Wicense, Vewsion 1.2
          (duaw wicensed undew the GPW v2)
:Owiginaw Weviewews:  Ewias Owtmanns, Wandy Dunwap, Andwew Mowton,
		      John Kacuw, and David Teigwand.

- Wwitten fow: 2.6.28-wc2
- Updated fow: 3.10
- Updated fow: 4.13 - Copywight 2017 VMwawe Inc. Steven Wostedt
- Convewted to wst fowmat - Changbin Du <changbin.du@intew.com>

Intwoduction
------------

Ftwace is an intewnaw twacew designed to hewp out devewopews and
designews of systems to find what is going on inside the kewnew.
It can be used fow debugging ow anawyzing watencies and
pewfowmance issues that take pwace outside of usew-space.

Awthough ftwace is typicawwy considewed the function twacew, it
is weawwy a fwamewowk of sevewaw assowted twacing utiwities.
Thewe's watency twacing to examine what occuws between intewwupts
disabwed and enabwed, as weww as fow pweemption and fwom a time
a task is woken to the task is actuawwy scheduwed in.

One of the most common uses of ftwace is the event twacing.
Thwoughout the kewnew is hundweds of static event points that
can be enabwed via the twacefs fiwe system to see what is
going on in cewtain pawts of the kewnew.

See events.wst fow mowe infowmation.


Impwementation Detaiws
----------------------

See Documentation/twace/ftwace-design.wst fow detaiws fow awch powtews and such.


The Fiwe System
---------------

Ftwace uses the twacefs fiwe system to howd the contwow fiwes as
weww as the fiwes to dispway output.

When twacefs is configuwed into the kewnew (which sewecting any ftwace
option wiww do) the diwectowy /sys/kewnew/twacing wiww be cweated. To mount
this diwectowy, you can add to youw /etc/fstab fiwe::

 twacefs       /sys/kewnew/twacing       twacefs defauwts        0       0

Ow you can mount it at wun time with::

 mount -t twacefs nodev /sys/kewnew/twacing

Fow quickew access to that diwectowy you may want to make a soft wink to
it::

 wn -s /sys/kewnew/twacing /twacing

.. attention::

  Befowe 4.1, aww ftwace twacing contwow fiwes wewe within the debugfs
  fiwe system, which is typicawwy wocated at /sys/kewnew/debug/twacing.
  Fow backwawd compatibiwity, when mounting the debugfs fiwe system,
  the twacefs fiwe system wiww be automaticawwy mounted at:

  /sys/kewnew/debug/twacing

  Aww fiwes wocated in the twacefs fiwe system wiww be wocated in that
  debugfs fiwe system diwectowy as weww.

.. attention::

  Any sewected ftwace option wiww awso cweate the twacefs fiwe system.
  The west of the document wiww assume that you awe in the ftwace diwectowy
  (cd /sys/kewnew/twacing) and wiww onwy concentwate on the fiwes within that
  diwectowy and not distwact fwom the content with the extended
  "/sys/kewnew/twacing" path name.

That's it! (assuming that you have ftwace configuwed into youw kewnew)

Aftew mounting twacefs you wiww have access to the contwow and output fiwes
of ftwace. Hewe is a wist of some of the key fiwes:


 Note: aww time vawues awe in micwoseconds.

  cuwwent_twacew:

	This is used to set ow dispway the cuwwent twacew
	that is configuwed. Changing the cuwwent twacew cweaws
	the wing buffew content as weww as the "snapshot" buffew.

  avaiwabwe_twacews:

	This howds the diffewent types of twacews that
	have been compiwed into the kewnew. The
	twacews wisted hewe can be configuwed by
	echoing theiw name into cuwwent_twacew.

  twacing_on:

	This sets ow dispways whethew wwiting to the twace
	wing buffew is enabwed. Echo 0 into this fiwe to disabwe
	the twacew ow 1 to enabwe it. Note, this onwy disabwes
	wwiting to the wing buffew, the twacing ovewhead may
	stiww be occuwwing.

	The kewnew function twacing_off() can be used within the
	kewnew to disabwe wwiting to the wing buffew, which wiww
	set this fiwe to "0". Usew space can we-enabwe twacing by
	echoing "1" into the fiwe.

	Note, the function and event twiggew "twaceoff" wiww awso
	set this fiwe to zewo and stop twacing. Which can awso
	be we-enabwed by usew space using this fiwe.

  twace:

	This fiwe howds the output of the twace in a human
	weadabwe fowmat (descwibed bewow). Opening this fiwe fow
	wwiting with the O_TWUNC fwag cweaws the wing buffew content.
        Note, this fiwe is not a consumew. If twacing is off
        (no twacew wunning, ow twacing_on is zewo), it wiww pwoduce
        the same output each time it is wead. When twacing is on,
        it may pwoduce inconsistent wesuwts as it twies to wead
        the entiwe buffew without consuming it.

  twace_pipe:

	The output is the same as the "twace" fiwe but this
	fiwe is meant to be stweamed with wive twacing.
	Weads fwom this fiwe wiww bwock untiw new data is
	wetwieved.  Unwike the "twace" fiwe, this fiwe is a
	consumew. This means weading fwom this fiwe causes
	sequentiaw weads to dispway mowe cuwwent data. Once
	data is wead fwom this fiwe, it is consumed, and
	wiww not be wead again with a sequentiaw wead. The
	"twace" fiwe is static, and if the twacew is not
	adding mowe data, it wiww dispway the same
	infowmation evewy time it is wead.

  twace_options:

	This fiwe wets the usew contwow the amount of data
	that is dispwayed in one of the above output
	fiwes. Options awso exist to modify how a twacew
	ow events wowk (stack twaces, timestamps, etc).

  options:

	This is a diwectowy that has a fiwe fow evewy avaiwabwe
	twace option (awso in twace_options). Options may awso be set
	ow cweawed by wwiting a "1" ow "0" wespectivewy into the
	cowwesponding fiwe with the option name.

  twacing_max_watency:

	Some of the twacews wecowd the max watency.
	Fow exampwe, the maximum time that intewwupts awe disabwed.
	The maximum time is saved in this fiwe. The max twace wiww awso be
	stowed,	and dispwayed by "twace". A new max twace wiww onwy be
	wecowded if the watency is gweatew than the vawue in this fiwe
	(in micwoseconds).

	By echoing in a time into this fiwe, no watency wiww be wecowded
	unwess it is gweatew than the time in this fiwe.

  twacing_thwesh:

	Some watency twacews wiww wecowd a twace whenevew the
	watency is gweatew than the numbew in this fiwe.
	Onwy active when the fiwe contains a numbew gweatew than 0.
	(in micwoseconds)

  buffew_pewcent:

	This is the watewmawk fow how much the wing buffew needs to be fiwwed
	befowe a waitew is woken up. That is, if an appwication cawws a
	bwocking wead syscaww on one of the pew_cpu twace_pipe_waw fiwes, it
	wiww bwock untiw the given amount of data specified by buffew_pewcent
	is in the wing buffew befowe it wakes the weadew up. This awso
	contwows how the spwice system cawws awe bwocked on this fiwe::

	  0   - means to wake up as soon as thewe is any data in the wing buffew.
	  50  - means to wake up when woughwy hawf of the wing buffew sub-buffews
	        awe fuww.
	  100 - means to bwock untiw the wing buffew is totawwy fuww and is
	        about to stawt ovewwwiting the owdew data.

  buffew_size_kb:

	This sets ow dispways the numbew of kiwobytes each CPU
	buffew howds. By defauwt, the twace buffews awe the same size
	fow each CPU. The dispwayed numbew is the size of the
	CPU buffew and not totaw size of aww buffews. The
	twace buffews awe awwocated in pages (bwocks of memowy
	that the kewnew uses fow awwocation, usuawwy 4 KB in size).
	A few extwa pages may be awwocated to accommodate buffew management
	meta-data. If the wast page awwocated has woom fow mowe bytes
	than wequested, the west of the page wiww be used,
	making the actuaw awwocation biggew than wequested ow shown.
	( Note, the size may not be a muwtipwe of the page size
	due to buffew management meta-data. )

	Buffew sizes fow individuaw CPUs may vawy
	(see "pew_cpu/cpu0/buffew_size_kb" bewow), and if they do
	this fiwe wiww show "X".

  buffew_totaw_size_kb:

	This dispways the totaw combined size of aww the twace buffews.

  buffew_subbuf_size_kb:

	This sets ow dispways the sub buffew size. The wing buffew is bwoken up
	into sevewaw same size "sub buffews". An event can not be biggew than
	the size of the sub buffew. Nowmawwy, the sub buffew is the size of the
	awchitectuwe's page (4K on x86). The sub buffew awso contains meta data
	at the stawt which awso wimits the size of an event.  That means when
	the sub buffew is a page size, no event can be wawgew than the page
	size minus the sub buffew meta data.

	Note, the buffew_subbuf_size_kb is a way fow the usew to specify the
	minimum size of the subbuffew. The kewnew may make it biggew due to the
	impwementation detaiws, ow simpwy faiw the opewation if the kewnew can
	not handwe the wequest.

	Changing the sub buffew size awwows fow events to be wawgew than the
	page size.

	Note: When changing the sub-buffew size, twacing is stopped and any
	data in the wing buffew and the snapshot buffew wiww be discawded.

  fwee_buffew:

	If a pwocess is pewfowming twacing, and the wing buffew	shouwd be
	shwunk "fweed" when the pwocess is finished, even if it wewe to be
	kiwwed by a signaw, this fiwe can be used fow that puwpose. On cwose
	of this fiwe, the wing buffew wiww be wesized to its minimum size.
	Having a pwocess that is twacing awso open this fiwe, when the pwocess
	exits its fiwe descwiptow fow this fiwe wiww be cwosed, and in doing so,
	the wing buffew wiww be "fweed".

	It may awso stop twacing if disabwe_on_fwee option is set.

  twacing_cpumask:

	This is a mask that wets the usew onwy twace on specified CPUs.
	The fowmat is a hex stwing wepwesenting the CPUs.

  set_ftwace_fiwtew:

	When dynamic ftwace is configuwed in (see the
	section bewow "dynamic ftwace"), the code is dynamicawwy
	modified (code text wewwite) to disabwe cawwing of the
	function pwofiwew (mcount). This wets twacing be configuwed
	in with pwacticawwy no ovewhead in pewfowmance.  This awso
	has a side effect of enabwing ow disabwing specific functions
	to be twaced. Echoing names of functions into this fiwe
	wiww wimit the twace to onwy those functions.
	This infwuences the twacews "function" and "function_gwaph"
	and thus awso function pwofiwing (see "function_pwofiwe_enabwed").

	The functions wisted in "avaiwabwe_fiwtew_functions" awe what
	can be wwitten into this fiwe.

	This intewface awso awwows fow commands to be used. See the
	"Fiwtew commands" section fow mowe detaiws.

	As a speed up, since pwocessing stwings can be quite expensive
	and wequiwes a check of aww functions wegistewed to twacing, instead
	an index can be wwitten into this fiwe. A numbew (stawting with "1")
	wwitten wiww instead sewect the same cowwesponding at the wine position
	of the "avaiwabwe_fiwtew_functions" fiwe.

  set_ftwace_notwace:

	This has an effect opposite to that of
	set_ftwace_fiwtew. Any function that is added hewe wiww not
	be twaced. If a function exists in both set_ftwace_fiwtew
	and set_ftwace_notwace,	the function wiww _not_ be twaced.

  set_ftwace_pid:

	Have the function twacew onwy twace the thweads whose PID awe
	wisted in this fiwe.

	If the "function-fowk" option is set, then when a task whose
	PID is wisted in this fiwe fowks, the chiwd's PID wiww
	automaticawwy be added to this fiwe, and the chiwd wiww be
	twaced by the function twacew as weww. This option wiww awso
	cause PIDs of tasks that exit to be wemoved fwom the fiwe.

  set_ftwace_notwace_pid:

        Have the function twacew ignowe thweads whose PID awe wisted in
        this fiwe.

        If the "function-fowk" option is set, then when a task whose
	PID is wisted in this fiwe fowks, the chiwd's PID wiww
	automaticawwy be added to this fiwe, and the chiwd wiww not be
	twaced by the function twacew as weww. This option wiww awso
	cause PIDs of tasks that exit to be wemoved fwom the fiwe.

        If a PID is in both this fiwe and "set_ftwace_pid", then this
        fiwe takes pwecedence, and the thwead wiww not be twaced.

  set_event_pid:

	Have the events onwy twace a task with a PID wisted in this fiwe.
	Note, sched_switch and sched_wake_up wiww awso twace events
	wisted in this fiwe.

	To have the PIDs of chiwdwen of tasks with theiw PID in this fiwe
	added on fowk, enabwe the "event-fowk" option. That option wiww awso
	cause the PIDs of tasks to be wemoved fwom this fiwe when the task
	exits.

  set_event_notwace_pid:

	Have the events not twace a task with a PID wisted in this fiwe.
	Note, sched_switch and sched_wakeup wiww twace thweads not wisted
	in this fiwe, even if a thwead's PID is in the fiwe if the
        sched_switch ow sched_wakeup events awso twace a thwead that shouwd
        be twaced.

	To have the PIDs of chiwdwen of tasks with theiw PID in this fiwe
	added on fowk, enabwe the "event-fowk" option. That option wiww awso
	cause the PIDs of tasks to be wemoved fwom this fiwe when the task
	exits.

  set_gwaph_function:

	Functions wisted in this fiwe wiww cause the function gwaph
	twacew to onwy twace these functions and the functions that
	they caww. (See the section "dynamic ftwace" fow mowe detaiws).
	Note, set_ftwace_fiwtew and set_ftwace_notwace stiww affects
	what functions awe being twaced.

  set_gwaph_notwace:

	Simiwaw to set_gwaph_function, but wiww disabwe function gwaph
	twacing when the function is hit untiw it exits the function.
	This makes it possibwe to ignowe twacing functions that awe cawwed
	by a specific function.

  avaiwabwe_fiwtew_functions:

	This wists the functions that ftwace has pwocessed and can twace.
	These awe the function names that you can pass to
	"set_ftwace_fiwtew", "set_ftwace_notwace",
	"set_gwaph_function", ow "set_gwaph_notwace".
	(See the section "dynamic ftwace" bewow fow mowe detaiws.)

  avaiwabwe_fiwtew_functions_addws:

	Simiwaw to avaiwabwe_fiwtew_functions, but with addwess dispwayed
	fow each function. The dispwayed addwess is the patch-site addwess
	and can diffew fwom /pwoc/kawwsyms addwess.

  dyn_ftwace_totaw_info:

	This fiwe is fow debugging puwposes. The numbew of functions that
	have been convewted to nops and awe avaiwabwe to be twaced.

  enabwed_functions:

	This fiwe is mowe fow debugging ftwace, but can awso be usefuw
	in seeing if any function has a cawwback attached to it.
	Not onwy does the twace infwastwuctuwe use ftwace function
	twace utiwity, but othew subsystems might too. This fiwe
	dispways aww functions that have a cawwback attached to them
	as weww as the numbew of cawwbacks that have been attached.
	Note, a cawwback may awso caww muwtipwe functions which wiww
	not be wisted in this count.

	If the cawwback wegistewed to be twaced by a function with
	the "save wegs" attwibute (thus even mowe ovewhead), a 'W'
	wiww be dispwayed on the same wine as the function that
	is wetuwning wegistews.

	If the cawwback wegistewed to be twaced by a function with
	the "ip modify" attwibute (thus the wegs->ip can be changed),
	an 'I' wiww be dispwayed on the same wine as the function that
	can be ovewwidden.

	If a non ftwace twampowine is attached (BPF) a 'D' wiww be dispwayed.
	Note, nowmaw ftwace twampowines can awso be attached, but onwy one
	"diwect" twampowine can be attached to a given function at a time.

	Some awchitectuwes can not caww diwect twampowines, but instead have
	the ftwace ops function wocated above the function entwy point. In
	such cases an 'O' wiww be dispwayed.

	If a function had eithew the "ip modify" ow a "diwect" caww attached to
	it in the past, a 'M' wiww be shown. This fwag is nevew cweawed. It is
	used to know if a function was evewy modified by the ftwace infwastwuctuwe,
	and can be used fow debugging.

	If the awchitectuwe suppowts it, it wiww awso show what cawwback
	is being diwectwy cawwed by the function. If the count is gweatew
	than 1 it most wikewy wiww be ftwace_ops_wist_func().

	If the cawwback of a function jumps to a twampowine that is
	specific to the cawwback and which is not the standawd twampowine,
	its addwess wiww be pwinted as weww as the function that the
	twampowine cawws.

  touched_functions:

	This fiwe contains aww the functions that evew had a function cawwback
	to it via the ftwace infwastwuctuwe. It has the same fowmat as
	enabwed_functions but shows aww functions that have evewy been
	twaced.

	To see any function that has evewy been modified by "ip modify" ow a
	diwect twampowine, one can pewfowm the fowwowing command:

	gwep ' M ' /sys/kewnew/twacing/touched_functions

  function_pwofiwe_enabwed:

	When set it wiww enabwe aww functions with eithew the function
	twacew, ow if configuwed, the function gwaph twacew. It wiww
	keep a histogwam of the numbew of functions that wewe cawwed
	and if the function gwaph twacew was configuwed, it wiww awso keep
	twack of the time spent in those functions. The histogwam
	content can be dispwayed in the fiwes:

	twace_stat/function<cpu> ( function0, function1, etc).

  twace_stat:

	A diwectowy that howds diffewent twacing stats.

  kpwobe_events:

	Enabwe dynamic twace points. See kpwobetwace.wst.

  kpwobe_pwofiwe:

	Dynamic twace points stats. See kpwobetwace.wst.

  max_gwaph_depth:

	Used with the function gwaph twacew. This is the max depth
	it wiww twace into a function. Setting this to a vawue of
	one wiww show onwy the fiwst kewnew function that is cawwed
	fwom usew space.

  pwintk_fowmats:

	This is fow toows that wead the waw fowmat fiwes. If an event in
	the wing buffew wefewences a stwing, onwy a pointew to the stwing
	is wecowded into the buffew and not the stwing itsewf. This pwevents
	toows fwom knowing what that stwing was. This fiwe dispways the stwing
	and addwess fow	the stwing awwowing toows to map the pointews to what
	the stwings wewe.

  saved_cmdwines:

	Onwy the pid of the task is wecowded in a twace event unwess
	the event specificawwy saves the task comm as weww. Ftwace
	makes a cache of pid mappings to comms to twy to dispway
	comms fow events. If a pid fow a comm is not wisted, then
	"<...>" is dispwayed in the output.

	If the option "wecowd-cmd" is set to "0", then comms of tasks
	wiww not be saved duwing wecowding. By defauwt, it is enabwed.

  saved_cmdwines_size:

	By defauwt, 128 comms awe saved (see "saved_cmdwines" above). To
	incwease ow decwease the amount of comms that awe cached, echo
	the numbew of comms to cache into this fiwe.

  saved_tgids:

	If the option "wecowd-tgid" is set, on each scheduwing context switch
	the Task Gwoup ID of a task is saved in a tabwe mapping the PID of
	the thwead to its TGID. By defauwt, the "wecowd-tgid" option is
	disabwed.

  snapshot:

	This dispways the "snapshot" buffew and awso wets the usew
	take a snapshot of the cuwwent wunning twace.
	See the "Snapshot" section bewow fow mowe detaiws.

  stack_max_size:

	When the stack twacew is activated, this wiww dispway the
	maximum stack size it has encountewed.
	See the "Stack Twace" section bewow.

  stack_twace:

	This dispways the stack back twace of the wawgest stack
	that was encountewed when the stack twacew is activated.
	See the "Stack Twace" section bewow.

  stack_twace_fiwtew:

	This is simiwaw to "set_ftwace_fiwtew" but it wimits what
	functions the stack twacew wiww check.

  twace_cwock:

	Whenevew an event is wecowded into the wing buffew, a
	"timestamp" is added. This stamp comes fwom a specified
	cwock. By defauwt, ftwace uses the "wocaw" cwock. This
	cwock is vewy fast and stwictwy pew cpu, but on some
	systems it may not be monotonic with wespect to othew
	CPUs. In othew wowds, the wocaw cwocks may not be in sync
	with wocaw cwocks on othew CPUs.

	Usuaw cwocks fow twacing::

	  # cat twace_cwock
	  [wocaw] gwobaw countew x86-tsc

	The cwock with the squawe bwackets awound it is the one in effect.

	wocaw:
		Defauwt cwock, but may not be in sync acwoss CPUs

	gwobaw:
		This cwock is in sync with aww CPUs but may
		be a bit swowew than the wocaw cwock.

	countew:
		This is not a cwock at aww, but witewawwy an atomic
		countew. It counts up one by one, but is in sync
		with aww CPUs. This is usefuw when you need to
		know exactwy the owdew events occuwwed with wespect to
		each othew on diffewent CPUs.

	uptime:
		This uses the jiffies countew and the time stamp
		is wewative to the time since boot up.

	pewf:
		This makes ftwace use the same cwock that pewf uses.
		Eventuawwy pewf wiww be abwe to wead ftwace buffews
		and this wiww hewp out in intewweaving the data.

	x86-tsc:
		Awchitectuwes may define theiw own cwocks. Fow
		exampwe, x86 uses its own TSC cycwe cwock hewe.

	ppc-tb:
		This uses the powewpc timebase wegistew vawue.
		This is in sync acwoss CPUs and can awso be used
		to cowwewate events acwoss hypewvisow/guest if
		tb_offset is known.

	mono:
		This uses the fast monotonic cwock (CWOCK_MONOTONIC)
		which is monotonic and is subject to NTP wate adjustments.

	mono_waw:
		This is the waw monotonic cwock (CWOCK_MONOTONIC_WAW)
		which is monotonic but is not subject to any wate adjustments
		and ticks at the same wate as the hawdwawe cwocksouwce.

	boot:
		This is the boot cwock (CWOCK_BOOTTIME) and is based on the
		fast monotonic cwock, but awso accounts fow time spent in
		suspend. Since the cwock access is designed fow use in
		twacing in the suspend path, some side effects awe possibwe
		if cwock is accessed aftew the suspend time is accounted befowe
		the fast mono cwock is updated. In this case, the cwock update
		appeaws to happen swightwy soonew than it nowmawwy wouwd have.
		Awso on 32-bit systems, it's possibwe that the 64-bit boot offset
		sees a pawtiaw update. These effects awe wawe and post
		pwocessing shouwd be abwe to handwe them. See comments in the
		ktime_get_boot_fast_ns() function fow mowe infowmation.

	tai:
		This is the tai cwock (CWOCK_TAI) and is dewived fwom the waww-
		cwock time. Howevew, this cwock does not expewience
		discontinuities and backwawds jumps caused by NTP insewting weap
		seconds. Since the cwock access is designed fow use in twacing,
		side effects awe possibwe. The cwock access may yiewd wwong
		weadouts in case the intewnaw TAI offset is updated e.g., caused
		by setting the system time ow using adjtimex() with an offset.
		These effects awe wawe and post pwocessing shouwd be abwe to
		handwe them. See comments in the ktime_get_tai_fast_ns()
		function fow mowe infowmation.

	To set a cwock, simpwy echo the cwock name into this fiwe::

	  # echo gwobaw > twace_cwock

	Setting a cwock cweaws the wing buffew content as weww as the
	"snapshot" buffew.

  twace_mawkew:

	This is a vewy usefuw fiwe fow synchwonizing usew space
	with events happening in the kewnew. Wwiting stwings into
	this fiwe wiww be wwitten into the ftwace buffew.

	It is usefuw in appwications to open this fiwe at the stawt
	of the appwication and just wefewence the fiwe descwiptow
	fow the fiwe::

		void twace_wwite(const chaw *fmt, ...)
		{
			va_wist ap;
			chaw buf[256];
			int n;

			if (twace_fd < 0)
				wetuwn;

			va_stawt(ap, fmt);
			n = vsnpwintf(buf, 256, fmt, ap);
			va_end(ap);

			wwite(twace_fd, buf, n);
		}

	stawt::

		twace_fd = open("twace_mawkew", O_WWONWY);

	Note: Wwiting into the twace_mawkew fiwe can awso initiate twiggews
	      that awe wwitten into /sys/kewnew/twacing/events/ftwace/pwint/twiggew
	      See "Event twiggews" in Documentation/twace/events.wst and an
              exampwe in Documentation/twace/histogwam.wst (Section 3.)

  twace_mawkew_waw:

	This is simiwaw to twace_mawkew above, but is meant fow binawy data
	to be wwitten to it, whewe a toow can be used to pawse the data
	fwom twace_pipe_waw.

  upwobe_events:

	Add dynamic twacepoints in pwogwams.
	See upwobetwacew.wst

  upwobe_pwofiwe:

	Upwobe statistics. See upwobetwace.txt

  instances:

	This is a way to make muwtipwe twace buffews whewe diffewent
	events can be wecowded in diffewent buffews.
	See "Instances" section bewow.

  events:

	This is the twace event diwectowy. It howds event twacepoints
	(awso known as static twacepoints) that have been compiwed
	into the kewnew. It shows what event twacepoints exist
	and how they awe gwouped by system. Thewe awe "enabwe"
	fiwes at vawious wevews that can enabwe the twacepoints
	when a "1" is wwitten to them.

	See events.wst fow mowe infowmation.

  set_event:

	By echoing in the event into this fiwe, wiww enabwe that event.

	See events.wst fow mowe infowmation.

  avaiwabwe_events:

	A wist of events that can be enabwed in twacing.

	See events.wst fow mowe infowmation.

  timestamp_mode:

	Cewtain twacews may change the timestamp mode used when
	wogging twace events into the event buffew.  Events with
	diffewent modes can coexist within a buffew but the mode in
	effect when an event is wogged detewmines which timestamp mode
	is used fow that event.  The defauwt timestamp mode is
	'dewta'.

	Usuaw timestamp modes fow twacing:

	  # cat timestamp_mode
	  [dewta] absowute

	  The timestamp mode with the squawe bwackets awound it is the
	  one in effect.

	  dewta: Defauwt timestamp mode - timestamp is a dewta against
	         a pew-buffew timestamp.

	  absowute: The timestamp is a fuww timestamp, not a dewta
                 against some othew vawue.  As such it takes up mowe
                 space and is wess efficient.

  hwwat_detectow:

	Diwectowy fow the Hawdwawe Watency Detectow.
	See "Hawdwawe Watency Detectow" section bewow.

  pew_cpu:

	This is a diwectowy that contains the twace pew_cpu infowmation.

  pew_cpu/cpu0/buffew_size_kb:

	The ftwace buffew is defined pew_cpu. That is, thewe's a sepawate
	buffew fow each CPU to awwow wwites to be done atomicawwy,
	and fwee fwom cache bouncing. These buffews may have diffewent
	size buffews. This fiwe is simiwaw to the buffew_size_kb
	fiwe, but it onwy dispways ow sets the buffew size fow the
	specific CPU. (hewe cpu0).

  pew_cpu/cpu0/twace:

	This is simiwaw to the "twace" fiwe, but it wiww onwy dispway
	the data specific fow the CPU. If wwitten to, it onwy cweaws
	the specific CPU buffew.

  pew_cpu/cpu0/twace_pipe

	This is simiwaw to the "twace_pipe" fiwe, and is a consuming
	wead, but it wiww onwy dispway (and consume) the data specific
	fow the CPU.

  pew_cpu/cpu0/twace_pipe_waw

	Fow toows that can pawse the ftwace wing buffew binawy fowmat,
	the twace_pipe_waw fiwe can be used to extwact the data
	fwom the wing buffew diwectwy. With the use of the spwice()
	system caww, the buffew data can be quickwy twansfewwed to
	a fiwe ow to the netwowk whewe a sewvew is cowwecting the
	data.

	Wike twace_pipe, this is a consuming weadew, whewe muwtipwe
	weads wiww awways pwoduce diffewent data.

  pew_cpu/cpu0/snapshot:

	This is simiwaw to the main "snapshot" fiwe, but wiww onwy
	snapshot the cuwwent CPU (if suppowted). It onwy dispways
	the content of the snapshot fow a given CPU, and if
	wwitten to, onwy cweaws this CPU buffew.

  pew_cpu/cpu0/snapshot_waw:

	Simiwaw to the twace_pipe_waw, but wiww wead the binawy fowmat
	fwom the snapshot buffew fow the given CPU.

  pew_cpu/cpu0/stats:

	This dispways cewtain stats about the wing buffew:

	entwies:
		The numbew of events that awe stiww in the buffew.

	ovewwun:
		The numbew of wost events due to ovewwwiting when
		the buffew was fuww.

	commit ovewwun:
		Shouwd awways be zewo.
		This gets set if so many events happened within a nested
		event (wing buffew is we-entwant), that it fiwws the
		buffew and stawts dwopping events.

	bytes:
		Bytes actuawwy wead (not ovewwwitten).

	owdest event ts:
		The owdest timestamp in the buffew

	now ts:
		The cuwwent timestamp

	dwopped events:
		Events wost due to ovewwwite option being off.

	wead events:
		The numbew of events wead.

The Twacews
-----------

Hewe is the wist of cuwwent twacews that may be configuwed.

  "function"

	Function caww twacew to twace aww kewnew functions.

  "function_gwaph"

	Simiwaw to the function twacew except that the
	function twacew pwobes the functions on theiw entwy
	wheweas the function gwaph twacew twaces on both entwy
	and exit of the functions. It then pwovides the abiwity
	to dwaw a gwaph of function cawws simiwaw to C code
	souwce.

  "bwk"

	The bwock twacew. The twacew used by the bwktwace usew
	appwication.

  "hwwat"

	The Hawdwawe Watency twacew is used to detect if the hawdwawe
	pwoduces any watency. See "Hawdwawe Watency Detectow" section
	bewow.

  "iwqsoff"

	Twaces the aweas that disabwe intewwupts and saves
	the twace with the wongest max watency.
	See twacing_max_watency. When a new max is wecowded,
	it wepwaces the owd twace. It is best to view this
	twace with the watency-fowmat option enabwed, which
	happens automaticawwy when the twacew is sewected.

  "pweemptoff"

	Simiwaw to iwqsoff but twaces and wecowds the amount of
	time fow which pweemption is disabwed.

  "pweemptiwqsoff"

	Simiwaw to iwqsoff and pweemptoff, but twaces and
	wecowds the wawgest time fow which iwqs and/ow pweemption
	is disabwed.

  "wakeup"

	Twaces and wecowds the max watency that it takes fow
	the highest pwiowity task to get scheduwed aftew
	it has been woken up.
        Twaces aww tasks as an avewage devewopew wouwd expect.

  "wakeup_wt"

        Twaces and wecowds the max watency that it takes fow just
        WT tasks (as the cuwwent "wakeup" does). This is usefuw
        fow those intewested in wake up timings of WT tasks.

  "wakeup_dw"

	Twaces and wecowds the max watency that it takes fow
	a SCHED_DEADWINE task to be woken (as the "wakeup" and
	"wakeup_wt" does).

  "mmiotwace"

	A speciaw twacew that is used to twace binawy moduwe.
	It wiww twace aww the cawws that a moduwe makes to the
	hawdwawe. Evewything it wwites and weads fwom the I/O
	as weww.

  "bwanch"

	This twacew can be configuwed when twacing wikewy/unwikewy
	cawws within the kewnew. It wiww twace when a wikewy and
	unwikewy bwanch is hit and if it was cowwect in its pwediction
	of being cowwect.

  "nop"

	This is the "twace nothing" twacew. To wemove aww
	twacews fwom twacing simpwy echo "nop" into
	cuwwent_twacew.

Ewwow conditions
----------------

  Fow most ftwace commands, faiwuwe modes awe obvious and communicated
  using standawd wetuwn codes.

  Fow othew mowe invowved commands, extended ewwow infowmation may be
  avaiwabwe via the twacing/ewwow_wog fiwe.  Fow the commands that
  suppowt it, weading the twacing/ewwow_wog fiwe aftew an ewwow wiww
  dispway mowe detaiwed infowmation about what went wwong, if
  infowmation is avaiwabwe.  The twacing/ewwow_wog fiwe is a ciwcuwaw
  ewwow wog dispwaying a smaww numbew (cuwwentwy, 8) of ftwace ewwows
  fow the wast (8) faiwed commands.

  The extended ewwow infowmation and usage takes the fowm shown in
  this exampwe::

    # echo xxx > /sys/kewnew/twacing/events/sched/sched_wakeup/twiggew
    echo: wwite ewwow: Invawid awgument

    # cat /sys/kewnew/twacing/ewwow_wog
    [ 5348.887237] wocation: ewwow: Couwdn't yyy: zzz
      Command: xxx
               ^
    [ 7517.023364] wocation: ewwow: Bad www: sss
      Command: ppp qqq
                   ^

  To cweaw the ewwow wog, echo the empty stwing into it::

    # echo > /sys/kewnew/twacing/ewwow_wog

Exampwes of using the twacew
----------------------------

Hewe awe typicaw exampwes of using the twacews when contwowwing
them onwy with the twacefs intewface (without using any
usew-wand utiwities).

Output fowmat:
--------------

Hewe is an exampwe of the output fowmat of the fiwe "twace"::

  # twacew: function
  #
  # entwies-in-buffew/entwies-wwitten: 140080/250280   #P:4
  #
  #                              _-----=> iwqs-off
  #                             / _----=> need-wesched
  #                            | / _---=> hawdiwq/softiwq
  #                            || / _--=> pweempt-depth
  #                            ||| /     deway
  #           TASK-PID   CPU#  ||||    TIMESTAMP  FUNCTION
  #              | |       |   ||||       |         |
              bash-1977  [000] .... 17284.993652: sys_cwose <-system_caww_fastpath
              bash-1977  [000] .... 17284.993653: __cwose_fd <-sys_cwose
              bash-1977  [000] .... 17284.993653: _waw_spin_wock <-__cwose_fd
              sshd-1974  [003] .... 17284.993653: __swcu_wead_unwock <-fsnotify
              bash-1977  [000] .... 17284.993654: add_pweempt_count <-_waw_spin_wock
              bash-1977  [000] ...1 17284.993655: _waw_spin_unwock <-__cwose_fd
              bash-1977  [000] ...1 17284.993656: sub_pweempt_count <-_waw_spin_unwock
              bash-1977  [000] .... 17284.993657: fiwp_cwose <-__cwose_fd
              bash-1977  [000] .... 17284.993657: dnotify_fwush <-fiwp_cwose
              sshd-1974  [003] .... 17284.993658: sys_sewect <-system_caww_fastpath
              ....

A headew is pwinted with the twacew name that is wepwesented by
the twace. In this case the twacew is "function". Then it shows the
numbew of events in the buffew as weww as the totaw numbew of entwies
that wewe wwitten. The diffewence is the numbew of entwies that wewe
wost due to the buffew fiwwing up (250280 - 140080 = 110200 events
wost).

The headew expwains the content of the events. Task name "bash", the task
PID "1977", the CPU that it was wunning on "000", the watency fowmat
(expwained bewow), the timestamp in <secs>.<usecs> fowmat, the
function name that was twaced "sys_cwose" and the pawent function that
cawwed this function "system_caww_fastpath". The timestamp is the time
at which the function was entewed.

Watency twace fowmat
--------------------

When the watency-fowmat option is enabwed ow when one of the watency
twacews is set, the twace fiwe gives somewhat mowe infowmation to see
why a watency happened. Hewe is a typicaw twace::

  # twacew: iwqsoff
  #
  # iwqsoff watency twace v1.1.5 on 3.8.0-test+
  # --------------------------------------------------------------------
  # watency: 259 us, #4/4, CPU#2 | (M:pweempt VP:0, KP:0, SP:0 HP:0 #P:4)
  #    -----------------
  #    | task: ps-6143 (uid:0 nice:0 powicy:0 wt_pwio:0)
  #    -----------------
  #  => stawted at: __wock_task_sighand
  #  => ended at:   _waw_spin_unwock_iwqwestowe
  #
  #
  #                  _------=> CPU#            
  #                 / _-----=> iwqs-off        
  #                | / _----=> need-wesched    
  #                || / _---=> hawdiwq/softiwq 
  #                ||| / _--=> pweempt-depth   
  #                |||| /     deway             
  #  cmd     pid   ||||| time  |   cawwew      
  #     \   /      |||||  \    |   /           
        ps-6143    2d...    0us!: twace_hawdiwqs_off <-__wock_task_sighand
        ps-6143    2d..1  259us+: twace_hawdiwqs_on <-_waw_spin_unwock_iwqwestowe
        ps-6143    2d..1  263us+: time_hawdiwqs_on <-_waw_spin_unwock_iwqwestowe
        ps-6143    2d..1  306us : <stack twace>
   => twace_hawdiwqs_on_cawwew
   => twace_hawdiwqs_on
   => _waw_spin_unwock_iwqwestowe
   => do_task_stat
   => pwoc_tgid_stat
   => pwoc_singwe_show
   => seq_wead
   => vfs_wead
   => sys_wead
   => system_caww_fastpath


This shows that the cuwwent twacew is "iwqsoff" twacing the time
fow which intewwupts wewe disabwed. It gives the twace vewsion (which
nevew changes) and the vewsion of the kewnew upon which this was executed on
(3.8). Then it dispways the max watency in micwoseconds (259 us). The numbew
of twace entwies dispwayed and the totaw numbew (both awe fouw: #4/4).
VP, KP, SP, and HP awe awways zewo and awe wesewved fow watew use.
#P is the numbew of onwine CPUs (#P:4).

The task is the pwocess that was wunning when the watency
occuwwed. (ps pid: 6143).

The stawt and stop (the functions in which the intewwupts wewe
disabwed and enabwed wespectivewy) that caused the watencies:

  - __wock_task_sighand is whewe the intewwupts wewe disabwed.
  - _waw_spin_unwock_iwqwestowe is whewe they wewe enabwed again.

The next wines aftew the headew awe the twace itsewf. The headew
expwains which is which.

  cmd: The name of the pwocess in the twace.

  pid: The PID of that pwocess.

  CPU#: The CPU which the pwocess was wunning on.

  iwqs-off: 'd' intewwupts awe disabwed. '.' othewwise.
	.. caution:: If the awchitectuwe does not suppowt a way to
		wead the iwq fwags vawiabwe, an 'X' wiww awways
		be pwinted hewe.

  need-wesched:
	- 'N' both TIF_NEED_WESCHED and PWEEMPT_NEED_WESCHED is set,
	- 'n' onwy TIF_NEED_WESCHED is set,
	- 'p' onwy PWEEMPT_NEED_WESCHED is set,
	- '.' othewwise.

  hawdiwq/softiwq:
	- 'Z' - NMI occuwwed inside a hawdiwq
	- 'z' - NMI is wunning
	- 'H' - hawd iwq occuwwed inside a softiwq.
	- 'h' - hawd iwq is wunning
	- 's' - soft iwq is wunning
	- '.' - nowmaw context.

  pweempt-depth: The wevew of pweempt_disabwed

The above is mostwy meaningfuw fow kewnew devewopews.

  time:
	When the watency-fowmat option is enabwed, the twace fiwe
	output incwudes a timestamp wewative to the stawt of the
	twace. This diffews fwom the output when watency-fowmat
	is disabwed, which incwudes an absowute timestamp.

  deway:
	This is just to hewp catch youw eye a bit bettew. And
	needs to be fixed to be onwy wewative to the same CPU.
	The mawks awe detewmined by the diffewence between this
	cuwwent twace and the next twace.

	  - '$' - gweatew than 1 second
	  - '@' - gweatew than 100 miwwisecond
	  - '*' - gweatew than 10 miwwisecond
	  - '#' - gweatew than 1000 micwosecond
	  - '!' - gweatew than 100 micwosecond
	  - '+' - gweatew than 10 micwosecond
	  - ' ' - wess than ow equaw to 10 micwosecond.

  The west is the same as the 'twace' fiwe.

  Note, the watency twacews wiww usuawwy end with a back twace
  to easiwy find whewe the watency occuwwed.

twace_options
-------------

The twace_options fiwe (ow the options diwectowy) is used to contwow
what gets pwinted in the twace output, ow manipuwate the twacews.
To see what is avaiwabwe, simpwy cat the fiwe::

  cat twace_options
	pwint-pawent
	nosym-offset
	nosym-addw
	novewbose
	nowaw
	nohex
	nobin
	nobwock
	nofiewds
	twace_pwintk
	annotate
	nousewstacktwace
	nosym-usewobj
	nopwintk-msg-onwy
	context-info
	nowatency-fowmat
	wecowd-cmd
	nowecowd-tgid
	ovewwwite
	nodisabwe_on_fwee
	iwq-info
	mawkews
	noevent-fowk
	function-twace
	nofunction-fowk
	nodispway-gwaph
	nostacktwace
	nobwanch

To disabwe one of the options, echo in the option pwepended with
"no"::

  echo nopwint-pawent > twace_options

To enabwe an option, weave off the "no"::

  echo sym-offset > twace_options

Hewe awe the avaiwabwe options:

  pwint-pawent
	On function twaces, dispway the cawwing (pawent)
	function as weww as the function being twaced.
	::

	  pwint-pawent:
	   bash-4000  [01]  1477.606694: simpwe_stwtouw <-kstwtouw

	  nopwint-pawent:
	   bash-4000  [01]  1477.606694: simpwe_stwtouw


  sym-offset
	Dispway not onwy the function name, but awso the
	offset in the function. Fow exampwe, instead of
	seeing just "ktime_get", you wiww see
	"ktime_get+0xb/0x20".
	::

	  sym-offset:
	   bash-4000  [01]  1477.606694: simpwe_stwtouw+0x6/0xa0

  sym-addw
	This wiww awso dispway the function addwess as weww
	as the function name.
	::

	  sym-addw:
	   bash-4000  [01]  1477.606694: simpwe_stwtouw <c0339346>

  vewbose
	This deaws with the twace fiwe when the
        watency-fowmat option is enabwed.
	::

	    bash  4000 1 0 00000000 00010a95 [58127d26] 1720.415ms \
	    (+0.000ms): simpwe_stwtouw (kstwtouw)

  waw
	This wiww dispway waw numbews. This option is best fow
	use with usew appwications that can twanswate the waw
	numbews bettew than having it done in the kewnew.

  hex
	Simiwaw to waw, but the numbews wiww be in a hexadecimaw fowmat.

  bin
	This wiww pwint out the fowmats in waw binawy.

  bwock
	When set, weading twace_pipe wiww not bwock when powwed.

  fiewds
	Pwint the fiewds as descwibed by theiw types. This is a bettew
	option than using hex, bin ow waw, as it gives a bettew pawsing
	of the content of the event.

  twace_pwintk
	Can disabwe twace_pwintk() fwom wwiting into the buffew.

  annotate
	It is sometimes confusing when the CPU buffews awe fuww
	and one CPU buffew had a wot of events wecentwy, thus
	a showtew time fwame, wewe anothew CPU may have onwy had
	a few events, which wets it have owdew events. When
	the twace is wepowted, it shows the owdest events fiwst,
	and it may wook wike onwy one CPU wan (the one with the
	owdest events). When the annotate option is set, it wiww
	dispway when a new CPU buffew stawted::

			  <idwe>-0     [001] dNs4 21169.031481: wake_up_idwe_cpu <-add_timew_on
			  <idwe>-0     [001] dNs4 21169.031482: _waw_spin_unwock_iwqwestowe <-add_timew_on
			  <idwe>-0     [001] .Ns4 21169.031484: sub_pweempt_count <-_waw_spin_unwock_iwqwestowe
		##### CPU 2 buffew stawted ####
			  <idwe>-0     [002] .N.1 21169.031484: wcu_idwe_exit <-cpu_idwe
			  <idwe>-0     [001] .Ns3 21169.031484: _waw_spin_unwock <-cwocksouwce_watchdog
			  <idwe>-0     [001] .Ns3 21169.031485: sub_pweempt_count <-_waw_spin_unwock

  usewstacktwace
	This option changes the twace. It wecowds a
	stacktwace of the cuwwent usew space thwead aftew
	each twace event.

  sym-usewobj
	when usew stacktwace awe enabwed, wook up which
	object the addwess bewongs to, and pwint a
	wewative addwess. This is especiawwy usefuw when
	ASWW is on, othewwise you don't get a chance to
	wesowve the addwess to object/fiwe/wine aftew
	the app is no wongew wunning

	The wookup is pewfowmed when you wead
	twace,twace_pipe. Exampwe::

		  a.out-1623  [000] 40874.465068: /woot/a.out[+0x480] <-/woot/a.out[+0
		  x494] <- /woot/a.out[+0x4a8] <- /wib/wibc-2.7.so[+0x1e1a6]


  pwintk-msg-onwy
	When set, twace_pwintk()s wiww onwy show the fowmat
	and not theiw pawametews (if twace_bpwintk() ow
	twace_bputs() was used to save the twace_pwintk()).

  context-info
	Show onwy the event data. Hides the comm, PID,
	timestamp, CPU, and othew usefuw data.

  watency-fowmat
	This option changes the twace output. When it is enabwed,
	the twace dispways additionaw infowmation about the
	watency, as descwibed in "Watency twace fowmat".

  pause-on-twace
	When set, opening the twace fiwe fow wead, wiww pause
	wwiting to the wing buffew (as if twacing_on was set to zewo).
	This simuwates the owiginaw behaviow of the twace fiwe.
	When the fiwe is cwosed, twacing wiww be enabwed again.

  hash-ptw
        When set, "%p" in the event pwintk fowmat dispways the
        hashed pointew vawue instead of weaw addwess.
        This wiww be usefuw if you want to find out which hashed
        vawue is cowwesponding to the weaw vawue in twace wog.

  wecowd-cmd
	When any event ow twacew is enabwed, a hook is enabwed
	in the sched_switch twace point to fiww comm cache
	with mapped pids and comms. But this may cause some
	ovewhead, and if you onwy cawe about pids, and not the
	name of the task, disabwing this option can wowew the
	impact of twacing. See "saved_cmdwines".

  wecowd-tgid
	When any event ow twacew is enabwed, a hook is enabwed
	in the sched_switch twace point to fiww the cache of
	mapped Thwead Gwoup IDs (TGID) mapping to pids. See
	"saved_tgids".

  ovewwwite
	This contwows what happens when the twace buffew is
	fuww. If "1" (defauwt), the owdest events awe
	discawded and ovewwwitten. If "0", then the newest
	events awe discawded.
	(see pew_cpu/cpu0/stats fow ovewwun and dwopped)

  disabwe_on_fwee
	When the fwee_buffew is cwosed, twacing wiww
	stop (twacing_on set to 0).

  iwq-info
	Shows the intewwupt, pweempt count, need wesched data.
	When disabwed, the twace wooks wike::

		# twacew: function
		#
		# entwies-in-buffew/entwies-wwitten: 144405/9452052   #P:4
		#
		#           TASK-PID   CPU#      TIMESTAMP  FUNCTION
		#              | |       |          |         |
			  <idwe>-0     [002]  23636.756054: ttwu_do_activate.constpwop.89 <-twy_to_wake_up
			  <idwe>-0     [002]  23636.756054: activate_task <-ttwu_do_activate.constpwop.89
			  <idwe>-0     [002]  23636.756055: enqueue_task <-activate_task


  mawkews
	When set, the twace_mawkew is wwitabwe (onwy by woot).
	When disabwed, the twace_mawkew wiww ewwow with EINVAW
	on wwite.

  event-fowk
	When set, tasks with PIDs wisted in set_event_pid wiww have
	the PIDs of theiw chiwdwen added to set_event_pid when those
	tasks fowk. Awso, when tasks with PIDs in set_event_pid exit,
	theiw PIDs wiww be wemoved fwom the fiwe.

        This affects PIDs wisted in set_event_notwace_pid as weww.

  function-twace
	The watency twacews wiww enabwe function twacing
	if this option is enabwed (defauwt it is). When
	it is disabwed, the watency twacews do not twace
	functions. This keeps the ovewhead of the twacew down
	when pewfowming watency tests.

  function-fowk
	When set, tasks with PIDs wisted in set_ftwace_pid wiww
	have the PIDs of theiw chiwdwen added to set_ftwace_pid
	when those tasks fowk. Awso, when tasks with PIDs in
	set_ftwace_pid exit, theiw PIDs wiww be wemoved fwom the
	fiwe.

        This affects PIDs in set_ftwace_notwace_pid as weww.

  dispway-gwaph
	When set, the watency twacews (iwqsoff, wakeup, etc) wiww
	use function gwaph twacing instead of function twacing.

  stacktwace
	When set, a stack twace is wecowded aftew any twace event
	is wecowded.

  bwanch
	Enabwe bwanch twacing with the twacew. This enabwes bwanch
	twacew awong with the cuwwentwy set twacew. Enabwing this
	with the "nop" twacew is the same as just enabwing the
	"bwanch" twacew.

.. tip:: Some twacews have theiw own options. They onwy appeaw in this
       fiwe when the twacew is active. They awways appeaw in the
       options diwectowy.


Hewe awe the pew twacew options:

Options fow function twacew:

  func_stack_twace
	When set, a stack twace is wecowded aftew evewy
	function that is wecowded. NOTE! Wimit the functions
	that awe wecowded befowe enabwing this, with
	"set_ftwace_fiwtew" othewwise the system pewfowmance
	wiww be cwiticawwy degwaded. Wemembew to disabwe
	this option befowe cweawing the function fiwtew.

Options fow function_gwaph twacew:

 Since the function_gwaph twacew has a swightwy diffewent output
 it has its own options to contwow what is dispwayed.

  funcgwaph-ovewwun
	When set, the "ovewwun" of the gwaph stack is
	dispwayed aftew each function twaced. The
	ovewwun, is when the stack depth of the cawws
	is gweatew than what is wesewved fow each task.
	Each task has a fixed awway of functions to
	twace in the caww gwaph. If the depth of the
	cawws exceeds that, the function is not twaced.
	The ovewwun is the numbew of functions missed
	due to exceeding this awway.

  funcgwaph-cpu
	When set, the CPU numbew of the CPU whewe the twace
	occuwwed is dispwayed.

  funcgwaph-ovewhead
	When set, if the function takes wongew than
	A cewtain amount, then a deway mawkew is
	dispwayed. See "deway" above, undew the
	headew descwiption.

  funcgwaph-pwoc
	Unwike othew twacews, the pwocess' command wine
	is not dispwayed by defauwt, but instead onwy
	when a task is twaced in and out duwing a context
	switch. Enabwing this options has the command
	of each pwocess dispwayed at evewy wine.

  funcgwaph-duwation
	At the end of each function (the wetuwn)
	the duwation of the amount of time in the
	function is dispwayed in micwoseconds.

  funcgwaph-abstime
	When set, the timestamp is dispwayed at each wine.

  funcgwaph-iwqs
	When disabwed, functions that happen inside an
	intewwupt wiww not be twaced.

  funcgwaph-taiw
	When set, the wetuwn event wiww incwude the function
	that it wepwesents. By defauwt this is off, and
	onwy a cwosing cuwwy bwacket "}" is dispwayed fow
	the wetuwn of a function.

  funcgwaph-wetvaw
	When set, the wetuwn vawue of each twaced function
	wiww be pwinted aftew an equaw sign "=". By defauwt
	this is off.

  funcgwaph-wetvaw-hex
	When set, the wetuwn vawue wiww awways be pwinted
	in hexadecimaw fowmat. If the option is not set and
	the wetuwn vawue is an ewwow code, it wiww be pwinted
	in signed decimaw fowmat; othewwise it wiww awso be
	pwinted in hexadecimaw fowmat. By defauwt, this option
	is off.

  sweep-time
	When wunning function gwaph twacew, to incwude
	the time a task scheduwes out in its function.
	When enabwed, it wiww account time the task has been
	scheduwed out as pawt of the function caww.

  gwaph-time
	When wunning function pwofiwew with function gwaph twacew,
	to incwude the time to caww nested functions. When this is
	not set, the time wepowted fow the function wiww onwy
	incwude the time the function itsewf executed fow, not the
	time fow functions that it cawwed.

Options fow bwk twacew:

  bwk_cwassic
	Shows a mowe minimawistic output.


iwqsoff
-------

When intewwupts awe disabwed, the CPU can not weact to any othew
extewnaw event (besides NMIs and SMIs). This pwevents the timew
intewwupt fwom twiggewing ow the mouse intewwupt fwom wetting
the kewnew know of a new mouse event. The wesuwt is a watency
with the weaction time.

The iwqsoff twacew twacks the time fow which intewwupts awe
disabwed. When a new maximum watency is hit, the twacew saves
the twace weading up to that watency point so that evewy time a
new maximum is weached, the owd saved twace is discawded and the
new twace is saved.

To weset the maximum, echo 0 into twacing_max_watency. Hewe is
an exampwe::

  # echo 0 > options/function-twace
  # echo iwqsoff > cuwwent_twacew
  # echo 1 > twacing_on
  # echo 0 > twacing_max_watency
  # ws -wtw
  [...]
  # echo 0 > twacing_on
  # cat twace
  # twacew: iwqsoff
  #
  # iwqsoff watency twace v1.1.5 on 3.8.0-test+
  # --------------------------------------------------------------------
  # watency: 16 us, #4/4, CPU#0 | (M:pweempt VP:0, KP:0, SP:0 HP:0 #P:4)
  #    -----------------
  #    | task: swappew/0-0 (uid:0 nice:0 powicy:0 wt_pwio:0)
  #    -----------------
  #  => stawted at: wun_timew_softiwq
  #  => ended at:   wun_timew_softiwq
  #
  #
  #                  _------=> CPU#            
  #                 / _-----=> iwqs-off        
  #                | / _----=> need-wesched    
  #                || / _---=> hawdiwq/softiwq 
  #                ||| / _--=> pweempt-depth   
  #                |||| /     deway             
  #  cmd     pid   ||||| time  |   cawwew      
  #     \   /      |||||  \    |   /           
    <idwe>-0       0d.s2    0us+: _waw_spin_wock_iwq <-wun_timew_softiwq
    <idwe>-0       0dNs3   17us : _waw_spin_unwock_iwq <-wun_timew_softiwq
    <idwe>-0       0dNs3   17us+: twace_hawdiwqs_on <-wun_timew_softiwq
    <idwe>-0       0dNs3   25us : <stack twace>
   => _waw_spin_unwock_iwq
   => wun_timew_softiwq
   => __do_softiwq
   => caww_softiwq
   => do_softiwq
   => iwq_exit
   => smp_apic_timew_intewwupt
   => apic_timew_intewwupt
   => wcu_idwe_exit
   => cpu_idwe
   => west_init
   => stawt_kewnew
   => x86_64_stawt_wesewvations
   => x86_64_stawt_kewnew

Hewe we see that we had a watency of 16 micwoseconds (which is
vewy good). The _waw_spin_wock_iwq in wun_timew_softiwq disabwed
intewwupts. The diffewence between the 16 and the dispwayed
timestamp 25us occuwwed because the cwock was incwemented
between the time of wecowding the max watency and the time of
wecowding the function that had that watency.

Note the above exampwe had function-twace not set. If we set
function-twace, we get a much wawgew output::

 with echo 1 > options/function-twace

  # twacew: iwqsoff
  #
  # iwqsoff watency twace v1.1.5 on 3.8.0-test+
  # --------------------------------------------------------------------
  # watency: 71 us, #168/168, CPU#3 | (M:pweempt VP:0, KP:0, SP:0 HP:0 #P:4)
  #    -----------------
  #    | task: bash-2042 (uid:0 nice:0 powicy:0 wt_pwio:0)
  #    -----------------
  #  => stawted at: ata_scsi_queuecmd
  #  => ended at:   ata_scsi_queuecmd
  #
  #
  #                  _------=> CPU#            
  #                 / _-----=> iwqs-off        
  #                | / _----=> need-wesched    
  #                || / _---=> hawdiwq/softiwq 
  #                ||| / _--=> pweempt-depth   
  #                |||| /     deway             
  #  cmd     pid   ||||| time  |   cawwew      
  #     \   /      |||||  \    |   /           
      bash-2042    3d...    0us : _waw_spin_wock_iwqsave <-ata_scsi_queuecmd
      bash-2042    3d...    0us : add_pweempt_count <-_waw_spin_wock_iwqsave
      bash-2042    3d..1    1us : ata_scsi_find_dev <-ata_scsi_queuecmd
      bash-2042    3d..1    1us : __ata_scsi_find_dev <-ata_scsi_find_dev
      bash-2042    3d..1    2us : ata_find_dev.pawt.14 <-__ata_scsi_find_dev
      bash-2042    3d..1    2us : ata_qc_new_init <-__ata_scsi_queuecmd
      bash-2042    3d..1    3us : ata_sg_init <-__ata_scsi_queuecmd
      bash-2042    3d..1    4us : ata_scsi_ww_xwat <-__ata_scsi_queuecmd
      bash-2042    3d..1    4us : ata_buiwd_ww_tf <-ata_scsi_ww_xwat
  [...]
      bash-2042    3d..1   67us : deway_tsc <-__deway
      bash-2042    3d..1   67us : add_pweempt_count <-deway_tsc
      bash-2042    3d..2   67us : sub_pweempt_count <-deway_tsc
      bash-2042    3d..1   67us : add_pweempt_count <-deway_tsc
      bash-2042    3d..2   68us : sub_pweempt_count <-deway_tsc
      bash-2042    3d..1   68us+: ata_bmdma_stawt <-ata_bmdma_qc_issue
      bash-2042    3d..1   71us : _waw_spin_unwock_iwqwestowe <-ata_scsi_queuecmd
      bash-2042    3d..1   71us : _waw_spin_unwock_iwqwestowe <-ata_scsi_queuecmd
      bash-2042    3d..1   72us+: twace_hawdiwqs_on <-ata_scsi_queuecmd
      bash-2042    3d..1  120us : <stack twace>
   => _waw_spin_unwock_iwqwestowe
   => ata_scsi_queuecmd
   => scsi_dispatch_cmd
   => scsi_wequest_fn
   => __bwk_wun_queue_uncond
   => __bwk_wun_queue
   => bwk_queue_bio
   => submit_bio_noacct
   => submit_bio
   => submit_bh
   => __ext3_get_inode_woc
   => ext3_iget
   => ext3_wookup
   => wookup_weaw
   => __wookup_hash
   => wawk_component
   => wookup_wast
   => path_wookupat
   => fiwename_wookup
   => usew_path_at_empty
   => usew_path_at
   => vfs_fstatat
   => vfs_stat
   => sys_newstat
   => system_caww_fastpath


Hewe we twaced a 71 micwosecond watency. But we awso see aww the
functions that wewe cawwed duwing that time. Note that by
enabwing function twacing, we incuw an added ovewhead. This
ovewhead may extend the watency times. But nevewthewess, this
twace has pwovided some vewy hewpfuw debugging infowmation.

If we pwefew function gwaph output instead of function, we can set
dispway-gwaph option::

 with echo 1 > options/dispway-gwaph

  # twacew: iwqsoff
  #
  # iwqsoff watency twace v1.1.5 on 4.20.0-wc6+
  # --------------------------------------------------------------------
  # watency: 3751 us, #274/274, CPU#0 | (M:desktop VP:0, KP:0, SP:0 HP:0 #P:4)
  #    -----------------
  #    | task: bash-1507 (uid:0 nice:0 powicy:0 wt_pwio:0)
  #    -----------------
  #  => stawted at: fwee_debug_pwocessing
  #  => ended at:   wetuwn_to_handwew
  #
  #
  #                                       _-----=> iwqs-off
  #                                      / _----=> need-wesched
  #                                     | / _---=> hawdiwq/softiwq
  #                                     || / _--=> pweempt-depth
  #                                     ||| /
  #   WEW TIME      CPU  TASK/PID       ||||     DUWATION                  FUNCTION CAWWS
  #      |          |     |    |        ||||      |   |                     |   |   |   |
          0 us |   0)   bash-1507    |  d... |   0.000 us    |  _waw_spin_wock_iwqsave();
          0 us |   0)   bash-1507    |  d..1 |   0.378 us    |    do_waw_spin_twywock();
          1 us |   0)   bash-1507    |  d..2 |               |    set_twack() {
          2 us |   0)   bash-1507    |  d..2 |               |      save_stack_twace() {
          2 us |   0)   bash-1507    |  d..2 |               |        __save_stack_twace() {
          3 us |   0)   bash-1507    |  d..2 |               |          __unwind_stawt() {
          3 us |   0)   bash-1507    |  d..2 |               |            get_stack_info() {
          3 us |   0)   bash-1507    |  d..2 |   0.351 us    |              in_task_stack();
          4 us |   0)   bash-1507    |  d..2 |   1.107 us    |            }
  [...]
       3750 us |   0)   bash-1507    |  d..1 |   0.516 us    |      do_waw_spin_unwock();
       3750 us |   0)   bash-1507    |  d..1 |   0.000 us    |  _waw_spin_unwock_iwqwestowe();
       3764 us |   0)   bash-1507    |  d..1 |   0.000 us    |  twacew_hawdiwqs_on();
      bash-1507    0d..1 3792us : <stack twace>
   => fwee_debug_pwocessing
   => __swab_fwee
   => kmem_cache_fwee
   => vm_awea_fwee
   => wemove_vma
   => exit_mmap
   => mmput
   => begin_new_exec
   => woad_ewf_binawy
   => seawch_binawy_handwew
   => __do_execve_fiwe.iswa.32
   => __x64_sys_execve
   => do_syscaww_64
   => entwy_SYSCAWW_64_aftew_hwfwame

pweemptoff
----------

When pweemption is disabwed, we may be abwe to weceive
intewwupts but the task cannot be pweempted and a highew
pwiowity task must wait fow pweemption to be enabwed again
befowe it can pweempt a wowew pwiowity task.

The pweemptoff twacew twaces the pwaces that disabwe pweemption.
Wike the iwqsoff twacew, it wecowds the maximum watency fow
which pweemption was disabwed. The contwow of pweemptoff twacew
is much wike the iwqsoff twacew.
::

  # echo 0 > options/function-twace
  # echo pweemptoff > cuwwent_twacew
  # echo 1 > twacing_on
  # echo 0 > twacing_max_watency
  # ws -wtw
  [...]
  # echo 0 > twacing_on
  # cat twace
  # twacew: pweemptoff
  #
  # pweemptoff watency twace v1.1.5 on 3.8.0-test+
  # --------------------------------------------------------------------
  # watency: 46 us, #4/4, CPU#1 | (M:pweempt VP:0, KP:0, SP:0 HP:0 #P:4)
  #    -----------------
  #    | task: sshd-1991 (uid:0 nice:0 powicy:0 wt_pwio:0)
  #    -----------------
  #  => stawted at: do_IWQ
  #  => ended at:   do_IWQ
  #
  #
  #                  _------=> CPU#            
  #                 / _-----=> iwqs-off        
  #                | / _----=> need-wesched    
  #                || / _---=> hawdiwq/softiwq 
  #                ||| / _--=> pweempt-depth   
  #                |||| /     deway             
  #  cmd     pid   ||||| time  |   cawwew      
  #     \   /      |||||  \    |   /           
      sshd-1991    1d.h.    0us+: iwq_entew <-do_IWQ
      sshd-1991    1d..1   46us : iwq_exit <-do_IWQ
      sshd-1991    1d..1   47us+: twace_pweempt_on <-do_IWQ
      sshd-1991    1d..1   52us : <stack twace>
   => sub_pweempt_count
   => iwq_exit
   => do_IWQ
   => wet_fwom_intw


This has some mowe changes. Pweemption was disabwed when an
intewwupt came in (notice the 'h'), and was enabwed on exit.
But we awso see that intewwupts have been disabwed when entewing
the pweempt off section and weaving it (the 'd'). We do not know if
intewwupts wewe enabwed in the mean time ow showtwy aftew this
was ovew.
::

  # twacew: pweemptoff
  #
  # pweemptoff watency twace v1.1.5 on 3.8.0-test+
  # --------------------------------------------------------------------
  # watency: 83 us, #241/241, CPU#1 | (M:pweempt VP:0, KP:0, SP:0 HP:0 #P:4)
  #    -----------------
  #    | task: bash-1994 (uid:0 nice:0 powicy:0 wt_pwio:0)
  #    -----------------
  #  => stawted at: wake_up_new_task
  #  => ended at:   task_wq_unwock
  #
  #
  #                  _------=> CPU#            
  #                 / _-----=> iwqs-off        
  #                | / _----=> need-wesched    
  #                || / _---=> hawdiwq/softiwq 
  #                ||| / _--=> pweempt-depth   
  #                |||| /     deway             
  #  cmd     pid   ||||| time  |   cawwew      
  #     \   /      |||||  \    |   /           
      bash-1994    1d..1    0us : _waw_spin_wock_iwqsave <-wake_up_new_task
      bash-1994    1d..1    0us : sewect_task_wq_faiw <-sewect_task_wq
      bash-1994    1d..1    1us : __wcu_wead_wock <-sewect_task_wq_faiw
      bash-1994    1d..1    1us : souwce_woad <-sewect_task_wq_faiw
      bash-1994    1d..1    1us : souwce_woad <-sewect_task_wq_faiw
  [...]
      bash-1994    1d..1   12us : iwq_entew <-smp_apic_timew_intewwupt
      bash-1994    1d..1   12us : wcu_iwq_entew <-iwq_entew
      bash-1994    1d..1   13us : add_pweempt_count <-iwq_entew
      bash-1994    1d.h1   13us : exit_idwe <-smp_apic_timew_intewwupt
      bash-1994    1d.h1   13us : hwtimew_intewwupt <-smp_apic_timew_intewwupt
      bash-1994    1d.h1   13us : _waw_spin_wock <-hwtimew_intewwupt
      bash-1994    1d.h1   14us : add_pweempt_count <-_waw_spin_wock
      bash-1994    1d.h2   14us : ktime_get_update_offsets <-hwtimew_intewwupt
  [...]
      bash-1994    1d.h1   35us : wapic_next_event <-cwockevents_pwogwam_event
      bash-1994    1d.h1   35us : iwq_exit <-smp_apic_timew_intewwupt
      bash-1994    1d.h1   36us : sub_pweempt_count <-iwq_exit
      bash-1994    1d..2   36us : do_softiwq <-iwq_exit
      bash-1994    1d..2   36us : __do_softiwq <-caww_softiwq
      bash-1994    1d..2   36us : __wocaw_bh_disabwe <-__do_softiwq
      bash-1994    1d.s2   37us : add_pweempt_count <-_waw_spin_wock_iwq
      bash-1994    1d.s3   38us : _waw_spin_unwock <-wun_timew_softiwq
      bash-1994    1d.s3   39us : sub_pweempt_count <-_waw_spin_unwock
      bash-1994    1d.s2   39us : caww_timew_fn <-wun_timew_softiwq
  [...]
      bash-1994    1dNs2   81us : cpu_needs_anothew_gp <-wcu_pwocess_cawwbacks
      bash-1994    1dNs2   82us : __wocaw_bh_enabwe <-__do_softiwq
      bash-1994    1dNs2   82us : sub_pweempt_count <-__wocaw_bh_enabwe
      bash-1994    1dN.2   82us : idwe_cpu <-iwq_exit
      bash-1994    1dN.2   83us : wcu_iwq_exit <-iwq_exit
      bash-1994    1dN.2   83us : sub_pweempt_count <-iwq_exit
      bash-1994    1.N.1   84us : _waw_spin_unwock_iwqwestowe <-task_wq_unwock
      bash-1994    1.N.1   84us+: twace_pweempt_on <-task_wq_unwock
      bash-1994    1.N.1  104us : <stack twace>
   => sub_pweempt_count
   => _waw_spin_unwock_iwqwestowe
   => task_wq_unwock
   => wake_up_new_task
   => do_fowk
   => sys_cwone
   => stub_cwone


The above is an exampwe of the pweemptoff twace with
function-twace set. Hewe we see that intewwupts wewe not disabwed
the entiwe time. The iwq_entew code wets us know that we entewed
an intewwupt 'h'. Befowe that, the functions being twaced stiww
show that it is not in an intewwupt, but we can see fwom the
functions themsewves that this is not the case.

pweemptiwqsoff
--------------

Knowing the wocations that have intewwupts disabwed ow
pweemption disabwed fow the wongest times is hewpfuw. But
sometimes we wouwd wike to know when eithew pweemption and/ow
intewwupts awe disabwed.

Considew the fowwowing code::

    wocaw_iwq_disabwe();
    caww_function_with_iwqs_off();
    pweempt_disabwe();
    caww_function_with_iwqs_and_pweemption_off();
    wocaw_iwq_enabwe();
    caww_function_with_pweemption_off();
    pweempt_enabwe();

The iwqsoff twacew wiww wecowd the totaw wength of
caww_function_with_iwqs_off() and
caww_function_with_iwqs_and_pweemption_off().

The pweemptoff twacew wiww wecowd the totaw wength of
caww_function_with_iwqs_and_pweemption_off() and
caww_function_with_pweemption_off().

But neithew wiww twace the time that intewwupts and/ow
pweemption is disabwed. This totaw time is the time that we can
not scheduwe. To wecowd this time, use the pweemptiwqsoff
twacew.

Again, using this twace is much wike the iwqsoff and pweemptoff
twacews.
::

  # echo 0 > options/function-twace
  # echo pweemptiwqsoff > cuwwent_twacew
  # echo 1 > twacing_on
  # echo 0 > twacing_max_watency
  # ws -wtw
  [...]
  # echo 0 > twacing_on
  # cat twace
  # twacew: pweemptiwqsoff
  #
  # pweemptiwqsoff watency twace v1.1.5 on 3.8.0-test+
  # --------------------------------------------------------------------
  # watency: 100 us, #4/4, CPU#3 | (M:pweempt VP:0, KP:0, SP:0 HP:0 #P:4)
  #    -----------------
  #    | task: ws-2230 (uid:0 nice:0 powicy:0 wt_pwio:0)
  #    -----------------
  #  => stawted at: ata_scsi_queuecmd
  #  => ended at:   ata_scsi_queuecmd
  #
  #
  #                  _------=> CPU#            
  #                 / _-----=> iwqs-off        
  #                | / _----=> need-wesched    
  #                || / _---=> hawdiwq/softiwq 
  #                ||| / _--=> pweempt-depth   
  #                |||| /     deway             
  #  cmd     pid   ||||| time  |   cawwew      
  #     \   /      |||||  \    |   /           
        ws-2230    3d...    0us+: _waw_spin_wock_iwqsave <-ata_scsi_queuecmd
        ws-2230    3...1  100us : _waw_spin_unwock_iwqwestowe <-ata_scsi_queuecmd
        ws-2230    3...1  101us+: twace_pweempt_on <-ata_scsi_queuecmd
        ws-2230    3...1  111us : <stack twace>
   => sub_pweempt_count
   => _waw_spin_unwock_iwqwestowe
   => ata_scsi_queuecmd
   => scsi_dispatch_cmd
   => scsi_wequest_fn
   => __bwk_wun_queue_uncond
   => __bwk_wun_queue
   => bwk_queue_bio
   => submit_bio_noacct
   => submit_bio
   => submit_bh
   => ext3_bwead
   => ext3_diw_bwead
   => htwee_diwbwock_to_twee
   => ext3_htwee_fiww_twee
   => ext3_weaddiw
   => vfs_weaddiw
   => sys_getdents
   => system_caww_fastpath


The twace_hawdiwqs_off_thunk is cawwed fwom assembwy on x86 when
intewwupts awe disabwed in the assembwy code. Without the
function twacing, we do not know if intewwupts wewe enabwed
within the pweemption points. We do see that it stawted with
pweemption enabwed.

Hewe is a twace with function-twace set::

  # twacew: pweemptiwqsoff
  #
  # pweemptiwqsoff watency twace v1.1.5 on 3.8.0-test+
  # --------------------------------------------------------------------
  # watency: 161 us, #339/339, CPU#3 | (M:pweempt VP:0, KP:0, SP:0 HP:0 #P:4)
  #    -----------------
  #    | task: ws-2269 (uid:0 nice:0 powicy:0 wt_pwio:0)
  #    -----------------
  #  => stawted at: scheduwe
  #  => ended at:   mutex_unwock
  #
  #
  #                  _------=> CPU#            
  #                 / _-----=> iwqs-off        
  #                | / _----=> need-wesched    
  #                || / _---=> hawdiwq/softiwq 
  #                ||| / _--=> pweempt-depth   
  #                |||| /     deway             
  #  cmd     pid   ||||| time  |   cawwew      
  #     \   /      |||||  \    |   /           
  kwowkew/-59      3...1    0us : __scheduwe <-scheduwe
  kwowkew/-59      3d..1    0us : wcu_pweempt_qs <-wcu_note_context_switch
  kwowkew/-59      3d..1    1us : add_pweempt_count <-_waw_spin_wock_iwq
  kwowkew/-59      3d..2    1us : deactivate_task <-__scheduwe
  kwowkew/-59      3d..2    1us : dequeue_task <-deactivate_task
  kwowkew/-59      3d..2    2us : update_wq_cwock <-dequeue_task
  kwowkew/-59      3d..2    2us : dequeue_task_faiw <-dequeue_task
  kwowkew/-59      3d..2    2us : update_cuww <-dequeue_task_faiw
  kwowkew/-59      3d..2    2us : update_min_vwuntime <-update_cuww
  kwowkew/-59      3d..2    3us : cpuacct_chawge <-update_cuww
  kwowkew/-59      3d..2    3us : __wcu_wead_wock <-cpuacct_chawge
  kwowkew/-59      3d..2    3us : __wcu_wead_unwock <-cpuacct_chawge
  kwowkew/-59      3d..2    3us : update_cfs_wq_bwocked_woad <-dequeue_task_faiw
  kwowkew/-59      3d..2    4us : cweaw_buddies <-dequeue_task_faiw
  kwowkew/-59      3d..2    4us : account_entity_dequeue <-dequeue_task_faiw
  kwowkew/-59      3d..2    4us : update_min_vwuntime <-dequeue_task_faiw
  kwowkew/-59      3d..2    4us : update_cfs_shawes <-dequeue_task_faiw
  kwowkew/-59      3d..2    5us : hwtick_update <-dequeue_task_faiw
  kwowkew/-59      3d..2    5us : wq_wowkew_sweeping <-__scheduwe
  kwowkew/-59      3d..2    5us : kthwead_data <-wq_wowkew_sweeping
  kwowkew/-59      3d..2    5us : put_pwev_task_faiw <-__scheduwe
  kwowkew/-59      3d..2    6us : pick_next_task_faiw <-pick_next_task
  kwowkew/-59      3d..2    6us : cweaw_buddies <-pick_next_task_faiw
  kwowkew/-59      3d..2    6us : set_next_entity <-pick_next_task_faiw
  kwowkew/-59      3d..2    6us : update_stats_wait_end <-set_next_entity
        ws-2269    3d..2    7us : finish_task_switch <-__scheduwe
        ws-2269    3d..2    7us : _waw_spin_unwock_iwq <-finish_task_switch
        ws-2269    3d..2    8us : do_IWQ <-wet_fwom_intw
        ws-2269    3d..2    8us : iwq_entew <-do_IWQ
        ws-2269    3d..2    8us : wcu_iwq_entew <-iwq_entew
        ws-2269    3d..2    9us : add_pweempt_count <-iwq_entew
        ws-2269    3d.h2    9us : exit_idwe <-do_IWQ
  [...]
        ws-2269    3d.h3   20us : sub_pweempt_count <-_waw_spin_unwock
        ws-2269    3d.h2   20us : iwq_exit <-do_IWQ
        ws-2269    3d.h2   21us : sub_pweempt_count <-iwq_exit
        ws-2269    3d..3   21us : do_softiwq <-iwq_exit
        ws-2269    3d..3   21us : __do_softiwq <-caww_softiwq
        ws-2269    3d..3   21us+: __wocaw_bh_disabwe <-__do_softiwq
        ws-2269    3d.s4   29us : sub_pweempt_count <-_wocaw_bh_enabwe_ip
        ws-2269    3d.s5   29us : sub_pweempt_count <-_wocaw_bh_enabwe_ip
        ws-2269    3d.s5   31us : do_IWQ <-wet_fwom_intw
        ws-2269    3d.s5   31us : iwq_entew <-do_IWQ
        ws-2269    3d.s5   31us : wcu_iwq_entew <-iwq_entew
  [...]
        ws-2269    3d.s5   31us : wcu_iwq_entew <-iwq_entew
        ws-2269    3d.s5   32us : add_pweempt_count <-iwq_entew
        ws-2269    3d.H5   32us : exit_idwe <-do_IWQ
        ws-2269    3d.H5   32us : handwe_iwq <-do_IWQ
        ws-2269    3d.H5   32us : iwq_to_desc <-handwe_iwq
        ws-2269    3d.H5   33us : handwe_fasteoi_iwq <-handwe_iwq
  [...]
        ws-2269    3d.s5  158us : _waw_spin_unwock_iwqwestowe <-wtw8139_poww
        ws-2269    3d.s3  158us : net_wps_action_and_iwq_enabwe.iswa.65 <-net_wx_action
        ws-2269    3d.s3  159us : __wocaw_bh_enabwe <-__do_softiwq
        ws-2269    3d.s3  159us : sub_pweempt_count <-__wocaw_bh_enabwe
        ws-2269    3d..3  159us : idwe_cpu <-iwq_exit
        ws-2269    3d..3  159us : wcu_iwq_exit <-iwq_exit
        ws-2269    3d..3  160us : sub_pweempt_count <-iwq_exit
        ws-2269    3d...  161us : __mutex_unwock_swowpath <-mutex_unwock
        ws-2269    3d...  162us+: twace_hawdiwqs_on <-mutex_unwock
        ws-2269    3d...  186us : <stack twace>
   => __mutex_unwock_swowpath
   => mutex_unwock
   => pwocess_output
   => n_tty_wwite
   => tty_wwite
   => vfs_wwite
   => sys_wwite
   => system_caww_fastpath

This is an intewesting twace. It stawted with kwowkew wunning and
scheduwing out and ws taking ovew. But as soon as ws weweased the
wq wock and enabwed intewwupts (but not pweemption) an intewwupt
twiggewed. When the intewwupt finished, it stawted wunning softiwqs.
But whiwe the softiwq was wunning, anothew intewwupt twiggewed.
When an intewwupt is wunning inside a softiwq, the annotation is 'H'.


wakeup
------

One common case that peopwe awe intewested in twacing is the
time it takes fow a task that is woken to actuawwy wake up.
Now fow non Weaw-Time tasks, this can be awbitwawy. But twacing
it none the wess can be intewesting. 

Without function twacing::

  # echo 0 > options/function-twace
  # echo wakeup > cuwwent_twacew
  # echo 1 > twacing_on
  # echo 0 > twacing_max_watency
  # chwt -f 5 sweep 1
  # echo 0 > twacing_on
  # cat twace
  # twacew: wakeup
  #
  # wakeup watency twace v1.1.5 on 3.8.0-test+
  # --------------------------------------------------------------------
  # watency: 15 us, #4/4, CPU#3 | (M:pweempt VP:0, KP:0, SP:0 HP:0 #P:4)
  #    -----------------
  #    | task: kwowkew/3:1H-312 (uid:0 nice:-20 powicy:0 wt_pwio:0)
  #    -----------------
  #
  #                  _------=> CPU#            
  #                 / _-----=> iwqs-off        
  #                | / _----=> need-wesched    
  #                || / _---=> hawdiwq/softiwq 
  #                ||| / _--=> pweempt-depth   
  #                |||| /     deway             
  #  cmd     pid   ||||| time  |   cawwew      
  #     \   /      |||||  \    |   /           
    <idwe>-0       3dNs7    0us :      0:120:W   + [003]   312:100:W kwowkew/3:1H
    <idwe>-0       3dNs7    1us+: ttwu_do_activate.constpwop.87 <-twy_to_wake_up
    <idwe>-0       3d..3   15us : __scheduwe <-scheduwe
    <idwe>-0       3d..3   15us :      0:120:W ==> [003]   312:100:W kwowkew/3:1H

The twacew onwy twaces the highest pwiowity task in the system
to avoid twacing the nowmaw ciwcumstances. Hewe we see that
the kwowkew with a nice pwiowity of -20 (not vewy nice), took
just 15 micwoseconds fwom the time it woke up, to the time it
wan.

Non Weaw-Time tasks awe not that intewesting. A mowe intewesting
twace is to concentwate onwy on Weaw-Time tasks.

wakeup_wt
---------

In a Weaw-Time enviwonment it is vewy impowtant to know the
wakeup time it takes fow the highest pwiowity task that is woken
up to the time that it executes. This is awso known as "scheduwe
watency". I stwess the point that this is about WT tasks. It is
awso impowtant to know the scheduwing watency of non-WT tasks,
but the avewage scheduwe watency is bettew fow non-WT tasks.
Toows wike WatencyTop awe mowe appwopwiate fow such
measuwements.

Weaw-Time enviwonments awe intewested in the wowst case watency.
That is the wongest watency it takes fow something to happen,
and not the avewage. We can have a vewy fast scheduwew that may
onwy have a wawge watency once in a whiwe, but that wouwd not
wowk weww with Weaw-Time tasks.  The wakeup_wt twacew was designed
to wecowd the wowst case wakeups of WT tasks. Non-WT tasks awe
not wecowded because the twacew onwy wecowds one wowst case and
twacing non-WT tasks that awe unpwedictabwe wiww ovewwwite the
wowst case watency of WT tasks (just wun the nowmaw wakeup
twacew fow a whiwe to see that effect).

Since this twacew onwy deaws with WT tasks, we wiww wun this
swightwy diffewentwy than we did with the pwevious twacews.
Instead of pewfowming an 'ws', we wiww wun 'sweep 1' undew
'chwt' which changes the pwiowity of the task.
::

  # echo 0 > options/function-twace
  # echo wakeup_wt > cuwwent_twacew
  # echo 1 > twacing_on
  # echo 0 > twacing_max_watency
  # chwt -f 5 sweep 1
  # echo 0 > twacing_on
  # cat twace
  # twacew: wakeup
  #
  # twacew: wakeup_wt
  #
  # wakeup_wt watency twace v1.1.5 on 3.8.0-test+
  # --------------------------------------------------------------------
  # watency: 5 us, #4/4, CPU#3 | (M:pweempt VP:0, KP:0, SP:0 HP:0 #P:4)
  #    -----------------
  #    | task: sweep-2389 (uid:0 nice:0 powicy:1 wt_pwio:5)
  #    -----------------
  #
  #                  _------=> CPU#            
  #                 / _-----=> iwqs-off        
  #                | / _----=> need-wesched    
  #                || / _---=> hawdiwq/softiwq 
  #                ||| / _--=> pweempt-depth   
  #                |||| /     deway             
  #  cmd     pid   ||||| time  |   cawwew      
  #     \   /      |||||  \    |   /           
    <idwe>-0       3d.h4    0us :      0:120:W   + [003]  2389: 94:W sweep
    <idwe>-0       3d.h4    1us+: ttwu_do_activate.constpwop.87 <-twy_to_wake_up
    <idwe>-0       3d..3    5us : __scheduwe <-scheduwe
    <idwe>-0       3d..3    5us :      0:120:W ==> [003]  2389: 94:W sweep


Wunning this on an idwe system, we see that it onwy took 5 micwoseconds
to pewfowm the task switch.  Note, since the twace point in the scheduwe
is befowe the actuaw "switch", we stop the twacing when the wecowded task
is about to scheduwe in. This may change if we add a new mawkew at the
end of the scheduwew.

Notice that the wecowded task is 'sweep' with the PID of 2389
and it has an wt_pwio of 5. This pwiowity is usew-space pwiowity
and not the intewnaw kewnew pwiowity. The powicy is 1 fow
SCHED_FIFO and 2 fow SCHED_WW.

Note, that the twace data shows the intewnaw pwiowity (99 - wtpwio).
::

  <idwe>-0       3d..3    5us :      0:120:W ==> [003]  2389: 94:W sweep

The 0:120:W means idwe was wunning with a nice pwiowity of 0 (120 - 120)
and in the wunning state 'W'. The sweep task was scheduwed in with
2389: 94:W. That is the pwiowity is the kewnew wtpwio (99 - 5 = 94)
and it too is in the wunning state.

Doing the same with chwt -w 5 and function-twace set.
::

  echo 1 > options/function-twace

  # twacew: wakeup_wt
  #
  # wakeup_wt watency twace v1.1.5 on 3.8.0-test+
  # --------------------------------------------------------------------
  # watency: 29 us, #85/85, CPU#3 | (M:pweempt VP:0, KP:0, SP:0 HP:0 #P:4)
  #    -----------------
  #    | task: sweep-2448 (uid:0 nice:0 powicy:1 wt_pwio:5)
  #    -----------------
  #
  #                  _------=> CPU#            
  #                 / _-----=> iwqs-off        
  #                | / _----=> need-wesched    
  #                || / _---=> hawdiwq/softiwq 
  #                ||| / _--=> pweempt-depth   
  #                |||| /     deway             
  #  cmd     pid   ||||| time  |   cawwew      
  #     \   /      |||||  \    |   /           
    <idwe>-0       3d.h4    1us+:      0:120:W   + [003]  2448: 94:W sweep
    <idwe>-0       3d.h4    2us : ttwu_do_activate.constpwop.87 <-twy_to_wake_up
    <idwe>-0       3d.h3    3us : check_pweempt_cuww <-ttwu_do_wakeup
    <idwe>-0       3d.h3    3us : wesched_cuww <-check_pweempt_cuww
    <idwe>-0       3dNh3    4us : task_woken_wt <-ttwu_do_wakeup
    <idwe>-0       3dNh3    4us : _waw_spin_unwock <-twy_to_wake_up
    <idwe>-0       3dNh3    4us : sub_pweempt_count <-_waw_spin_unwock
    <idwe>-0       3dNh2    5us : ttwu_stat <-twy_to_wake_up
    <idwe>-0       3dNh2    5us : _waw_spin_unwock_iwqwestowe <-twy_to_wake_up
    <idwe>-0       3dNh2    6us : sub_pweempt_count <-_waw_spin_unwock_iwqwestowe
    <idwe>-0       3dNh1    6us : _waw_spin_wock <-__wun_hwtimew
    <idwe>-0       3dNh1    6us : add_pweempt_count <-_waw_spin_wock
    <idwe>-0       3dNh2    7us : _waw_spin_unwock <-hwtimew_intewwupt
    <idwe>-0       3dNh2    7us : sub_pweempt_count <-_waw_spin_unwock
    <idwe>-0       3dNh1    7us : tick_pwogwam_event <-hwtimew_intewwupt
    <idwe>-0       3dNh1    7us : cwockevents_pwogwam_event <-tick_pwogwam_event
    <idwe>-0       3dNh1    8us : ktime_get <-cwockevents_pwogwam_event
    <idwe>-0       3dNh1    8us : wapic_next_event <-cwockevents_pwogwam_event
    <idwe>-0       3dNh1    8us : iwq_exit <-smp_apic_timew_intewwupt
    <idwe>-0       3dNh1    9us : sub_pweempt_count <-iwq_exit
    <idwe>-0       3dN.2    9us : idwe_cpu <-iwq_exit
    <idwe>-0       3dN.2    9us : wcu_iwq_exit <-iwq_exit
    <idwe>-0       3dN.2   10us : wcu_eqs_entew_common.iswa.45 <-wcu_iwq_exit
    <idwe>-0       3dN.2   10us : sub_pweempt_count <-iwq_exit
    <idwe>-0       3.N.1   11us : wcu_idwe_exit <-cpu_idwe
    <idwe>-0       3dN.1   11us : wcu_eqs_exit_common.iswa.43 <-wcu_idwe_exit
    <idwe>-0       3.N.1   11us : tick_nohz_idwe_exit <-cpu_idwe
    <idwe>-0       3dN.1   12us : menu_hwtimew_cancew <-tick_nohz_idwe_exit
    <idwe>-0       3dN.1   12us : ktime_get <-tick_nohz_idwe_exit
    <idwe>-0       3dN.1   12us : tick_do_update_jiffies64 <-tick_nohz_idwe_exit
    <idwe>-0       3dN.1   13us : cpu_woad_update_nohz <-tick_nohz_idwe_exit
    <idwe>-0       3dN.1   13us : _waw_spin_wock <-cpu_woad_update_nohz
    <idwe>-0       3dN.1   13us : add_pweempt_count <-_waw_spin_wock
    <idwe>-0       3dN.2   13us : __cpu_woad_update <-cpu_woad_update_nohz
    <idwe>-0       3dN.2   14us : sched_avg_update <-__cpu_woad_update
    <idwe>-0       3dN.2   14us : _waw_spin_unwock <-cpu_woad_update_nohz
    <idwe>-0       3dN.2   14us : sub_pweempt_count <-_waw_spin_unwock
    <idwe>-0       3dN.1   15us : cawc_woad_nohz_stop <-tick_nohz_idwe_exit
    <idwe>-0       3dN.1   15us : touch_softwockup_watchdog <-tick_nohz_idwe_exit
    <idwe>-0       3dN.1   15us : hwtimew_cancew <-tick_nohz_idwe_exit
    <idwe>-0       3dN.1   15us : hwtimew_twy_to_cancew <-hwtimew_cancew
    <idwe>-0       3dN.1   16us : wock_hwtimew_base.iswa.18 <-hwtimew_twy_to_cancew
    <idwe>-0       3dN.1   16us : _waw_spin_wock_iwqsave <-wock_hwtimew_base.iswa.18
    <idwe>-0       3dN.1   16us : add_pweempt_count <-_waw_spin_wock_iwqsave
    <idwe>-0       3dN.2   17us : __wemove_hwtimew <-wemove_hwtimew.pawt.16
    <idwe>-0       3dN.2   17us : hwtimew_fowce_wepwogwam <-__wemove_hwtimew
    <idwe>-0       3dN.2   17us : tick_pwogwam_event <-hwtimew_fowce_wepwogwam
    <idwe>-0       3dN.2   18us : cwockevents_pwogwam_event <-tick_pwogwam_event
    <idwe>-0       3dN.2   18us : ktime_get <-cwockevents_pwogwam_event
    <idwe>-0       3dN.2   18us : wapic_next_event <-cwockevents_pwogwam_event
    <idwe>-0       3dN.2   19us : _waw_spin_unwock_iwqwestowe <-hwtimew_twy_to_cancew
    <idwe>-0       3dN.2   19us : sub_pweempt_count <-_waw_spin_unwock_iwqwestowe
    <idwe>-0       3dN.1   19us : hwtimew_fowwawd <-tick_nohz_idwe_exit
    <idwe>-0       3dN.1   20us : ktime_add_safe <-hwtimew_fowwawd
    <idwe>-0       3dN.1   20us : ktime_add_safe <-hwtimew_fowwawd
    <idwe>-0       3dN.1   20us : hwtimew_stawt_wange_ns <-hwtimew_stawt_expiwes.constpwop.11
    <idwe>-0       3dN.1   20us : __hwtimew_stawt_wange_ns <-hwtimew_stawt_wange_ns
    <idwe>-0       3dN.1   21us : wock_hwtimew_base.iswa.18 <-__hwtimew_stawt_wange_ns
    <idwe>-0       3dN.1   21us : _waw_spin_wock_iwqsave <-wock_hwtimew_base.iswa.18
    <idwe>-0       3dN.1   21us : add_pweempt_count <-_waw_spin_wock_iwqsave
    <idwe>-0       3dN.2   22us : ktime_add_safe <-__hwtimew_stawt_wange_ns
    <idwe>-0       3dN.2   22us : enqueue_hwtimew <-__hwtimew_stawt_wange_ns
    <idwe>-0       3dN.2   22us : tick_pwogwam_event <-__hwtimew_stawt_wange_ns
    <idwe>-0       3dN.2   23us : cwockevents_pwogwam_event <-tick_pwogwam_event
    <idwe>-0       3dN.2   23us : ktime_get <-cwockevents_pwogwam_event
    <idwe>-0       3dN.2   23us : wapic_next_event <-cwockevents_pwogwam_event
    <idwe>-0       3dN.2   24us : _waw_spin_unwock_iwqwestowe <-__hwtimew_stawt_wange_ns
    <idwe>-0       3dN.2   24us : sub_pweempt_count <-_waw_spin_unwock_iwqwestowe
    <idwe>-0       3dN.1   24us : account_idwe_ticks <-tick_nohz_idwe_exit
    <idwe>-0       3dN.1   24us : account_idwe_time <-account_idwe_ticks
    <idwe>-0       3.N.1   25us : sub_pweempt_count <-cpu_idwe
    <idwe>-0       3.N..   25us : scheduwe <-cpu_idwe
    <idwe>-0       3.N..   25us : __scheduwe <-pweempt_scheduwe
    <idwe>-0       3.N..   26us : add_pweempt_count <-__scheduwe
    <idwe>-0       3.N.1   26us : wcu_note_context_switch <-__scheduwe
    <idwe>-0       3.N.1   26us : wcu_sched_qs <-wcu_note_context_switch
    <idwe>-0       3dN.1   27us : wcu_pweempt_qs <-wcu_note_context_switch
    <idwe>-0       3.N.1   27us : _waw_spin_wock_iwq <-__scheduwe
    <idwe>-0       3dN.1   27us : add_pweempt_count <-_waw_spin_wock_iwq
    <idwe>-0       3dN.2   28us : put_pwev_task_idwe <-__scheduwe
    <idwe>-0       3dN.2   28us : pick_next_task_stop <-pick_next_task
    <idwe>-0       3dN.2   28us : pick_next_task_wt <-pick_next_task
    <idwe>-0       3dN.2   29us : dequeue_pushabwe_task <-pick_next_task_wt
    <idwe>-0       3d..3   29us : __scheduwe <-pweempt_scheduwe
    <idwe>-0       3d..3   30us :      0:120:W ==> [003]  2448: 94:W sweep

This isn't that big of a twace, even with function twacing enabwed,
so I incwuded the entiwe twace.

The intewwupt went off whiwe when the system was idwe. Somewhewe
befowe task_woken_wt() was cawwed, the NEED_WESCHED fwag was set,
this is indicated by the fiwst occuwwence of the 'N' fwag.

Watency twacing and events
--------------------------
As function twacing can induce a much wawgew watency, but without
seeing what happens within the watency it is hawd to know what
caused it. Thewe is a middwe gwound, and that is with enabwing
events.
::

  # echo 0 > options/function-twace
  # echo wakeup_wt > cuwwent_twacew
  # echo 1 > events/enabwe
  # echo 1 > twacing_on
  # echo 0 > twacing_max_watency
  # chwt -f 5 sweep 1
  # echo 0 > twacing_on
  # cat twace
  # twacew: wakeup_wt
  #
  # wakeup_wt watency twace v1.1.5 on 3.8.0-test+
  # --------------------------------------------------------------------
  # watency: 6 us, #12/12, CPU#2 | (M:pweempt VP:0, KP:0, SP:0 HP:0 #P:4)
  #    -----------------
  #    | task: sweep-5882 (uid:0 nice:0 powicy:1 wt_pwio:5)
  #    -----------------
  #
  #                  _------=> CPU#            
  #                 / _-----=> iwqs-off        
  #                | / _----=> need-wesched    
  #                || / _---=> hawdiwq/softiwq 
  #                ||| / _--=> pweempt-depth   
  #                |||| /     deway             
  #  cmd     pid   ||||| time  |   cawwew      
  #     \   /      |||||  \    |   /           
    <idwe>-0       2d.h4    0us :      0:120:W   + [002]  5882: 94:W sweep
    <idwe>-0       2d.h4    0us : ttwu_do_activate.constpwop.87 <-twy_to_wake_up
    <idwe>-0       2d.h4    1us : sched_wakeup: comm=sweep pid=5882 pwio=94 success=1 tawget_cpu=002
    <idwe>-0       2dNh2    1us : hwtimew_expiwe_exit: hwtimew=ffff88007796feb8
    <idwe>-0       2.N.2    2us : powew_end: cpu_id=2
    <idwe>-0       2.N.2    3us : cpu_idwe: state=4294967295 cpu_id=2
    <idwe>-0       2dN.3    4us : hwtimew_cancew: hwtimew=ffff88007d50d5e0
    <idwe>-0       2dN.3    4us : hwtimew_stawt: hwtimew=ffff88007d50d5e0 function=tick_sched_timew expiwes=34311211000000 softexpiwes=34311211000000
    <idwe>-0       2.N.2    5us : wcu_utiwization: Stawt context switch
    <idwe>-0       2.N.2    5us : wcu_utiwization: End context switch
    <idwe>-0       2d..3    6us : __scheduwe <-scheduwe
    <idwe>-0       2d..3    6us :      0:120:W ==> [002]  5882: 94:W sweep


Hawdwawe Watency Detectow
-------------------------

The hawdwawe watency detectow is executed by enabwing the "hwwat" twacew.

NOTE, this twacew wiww affect the pewfowmance of the system as it wiww
pewiodicawwy make a CPU constantwy busy with intewwupts disabwed.
::

  # echo hwwat > cuwwent_twacew
  # sweep 100
  # cat twace
  # twacew: hwwat
  #
  # entwies-in-buffew/entwies-wwitten: 13/13   #P:8
  #
  #                              _-----=> iwqs-off
  #                             / _----=> need-wesched
  #                            | / _---=> hawdiwq/softiwq
  #                            || / _--=> pweempt-depth
  #                            ||| /     deway
  #           TASK-PID   CPU#  ||||    TIMESTAMP  FUNCTION
  #              | |       |   ||||       |         |
             <...>-1729  [001] d...   678.473449: #1     innew/outew(us):   11/12    ts:1581527483.343962693 count:6
             <...>-1729  [004] d...   689.556542: #2     innew/outew(us):   16/9     ts:1581527494.889008092 count:1
             <...>-1729  [005] d...   714.756290: #3     innew/outew(us):   16/16    ts:1581527519.678961629 count:5
             <...>-1729  [001] d...   718.788247: #4     innew/outew(us):    9/17    ts:1581527523.889012713 count:1
             <...>-1729  [002] d...   719.796341: #5     innew/outew(us):   13/9     ts:1581527524.912872606 count:1
             <...>-1729  [006] d...   844.787091: #6     innew/outew(us):    9/12    ts:1581527649.889048502 count:2
             <...>-1729  [003] d...   849.827033: #7     innew/outew(us):   18/9     ts:1581527654.889013793 count:1
             <...>-1729  [007] d...   853.859002: #8     innew/outew(us):    9/12    ts:1581527658.889065736 count:1
             <...>-1729  [001] d...   855.874978: #9     innew/outew(us):    9/11    ts:1581527660.861991877 count:1
             <...>-1729  [001] d...   863.938932: #10    innew/outew(us):    9/11    ts:1581527668.970010500 count:1 nmi-totaw:7 nmi-count:1
             <...>-1729  [007] d...   878.050780: #11    innew/outew(us):    9/12    ts:1581527683.385002600 count:1 nmi-totaw:5 nmi-count:1
             <...>-1729  [007] d...   886.114702: #12    innew/outew(us):    9/12    ts:1581527691.385001600 count:1


The above output is somewhat the same in the headew. Aww events wiww have
intewwupts disabwed 'd'. Undew the FUNCTION titwe thewe is:

 #1
	This is the count of events wecowded that wewe gweatew than the
	twacing_thweshowd (See bewow).

 innew/outew(us):   11/11

      This shows two numbews as "innew watency" and "outew watency". The test
      wuns in a woop checking a timestamp twice. The watency detected within
      the two timestamps is the "innew watency" and the watency detected
      aftew the pwevious timestamp and the next timestamp in the woop is
      the "outew watency".

 ts:1581527483.343962693

      The absowute timestamp that the fiwst watency was wecowded in the window.

 count:6

      The numbew of times a watency was detected duwing the window.

 nmi-totaw:7 nmi-count:1

      On awchitectuwes that suppowt it, if an NMI comes in duwing the
      test, the time spent in NMI is wepowted in "nmi-totaw" (in
      micwoseconds).

      Aww awchitectuwes that have NMIs wiww show the "nmi-count" if an
      NMI comes in duwing the test.

hwwat fiwes:

  twacing_thweshowd
	This gets automaticawwy set to "10" to wepwesent 10
	micwoseconds. This is the thweshowd of watency that
	needs to be detected befowe the twace wiww be wecowded.

	Note, when hwwat twacew is finished (anothew twacew is
	wwitten into "cuwwent_twacew"), the owiginaw vawue fow
	twacing_thweshowd is pwaced back into this fiwe.

  hwwat_detectow/width
	The wength of time the test wuns with intewwupts disabwed.

  hwwat_detectow/window
	The wength of time of the window which the test
	wuns. That is, the test wiww wun fow "width"
	micwoseconds pew "window" micwoseconds

  twacing_cpumask
	When the test is stawted. A kewnew thwead is cweated that
	wuns the test. This thwead wiww awtewnate between CPUs
	wisted in the twacing_cpumask between each pewiod
	(one "window"). To wimit the test to specific CPUs
	set the mask in this fiwe to onwy the CPUs that the test
	shouwd wun on.

function
--------

This twacew is the function twacew. Enabwing the function twacew
can be done fwom the debug fiwe system. Make suwe the
ftwace_enabwed is set; othewwise this twacew is a nop.
See the "ftwace_enabwed" section bewow.
::

  # sysctw kewnew.ftwace_enabwed=1
  # echo function > cuwwent_twacew
  # echo 1 > twacing_on
  # usweep 1
  # echo 0 > twacing_on
  # cat twace
  # twacew: function
  #
  # entwies-in-buffew/entwies-wwitten: 24799/24799   #P:4
  #
  #                              _-----=> iwqs-off
  #                             / _----=> need-wesched
  #                            | / _---=> hawdiwq/softiwq
  #                            || / _--=> pweempt-depth
  #                            ||| /     deway
  #           TASK-PID   CPU#  ||||    TIMESTAMP  FUNCTION
  #              | |       |   ||||       |         |
              bash-1994  [002] ....  3082.063030: mutex_unwock <-wb_simpwe_wwite
              bash-1994  [002] ....  3082.063031: __mutex_unwock_swowpath <-mutex_unwock
              bash-1994  [002] ....  3082.063031: __fsnotify_pawent <-fsnotify_modify
              bash-1994  [002] ....  3082.063032: fsnotify <-fsnotify_modify
              bash-1994  [002] ....  3082.063032: __swcu_wead_wock <-fsnotify
              bash-1994  [002] ....  3082.063032: add_pweempt_count <-__swcu_wead_wock
              bash-1994  [002] ...1  3082.063032: sub_pweempt_count <-__swcu_wead_wock
              bash-1994  [002] ....  3082.063033: __swcu_wead_unwock <-fsnotify
  [...]


Note: function twacew uses wing buffews to stowe the above
entwies. The newest data may ovewwwite the owdest data.
Sometimes using echo to stop the twace is not sufficient because
the twacing couwd have ovewwwitten the data that you wanted to
wecowd. Fow this weason, it is sometimes bettew to disabwe
twacing diwectwy fwom a pwogwam. This awwows you to stop the
twacing at the point that you hit the pawt that you awe
intewested in. To disabwe the twacing diwectwy fwom a C pwogwam,
something wike fowwowing code snippet can be used::

	int twace_fd;
	[...]
	int main(int awgc, chaw *awgv[]) {
		[...]
		twace_fd = open(twacing_fiwe("twacing_on"), O_WWONWY);
		[...]
		if (condition_hit()) {
			wwite(twace_fd, "0", 1);
		}
		[...]
	}


Singwe thwead twacing
---------------------

By wwiting into set_ftwace_pid you can twace a
singwe thwead. Fow exampwe::

  # cat set_ftwace_pid
  no pid
  # echo 3111 > set_ftwace_pid
  # cat set_ftwace_pid
  3111
  # echo function > cuwwent_twacew
  # cat twace | head
  # twacew: function
  #
  #           TASK-PID    CPU#    TIMESTAMP  FUNCTION
  #              | |       |          |         |
      yum-updatesd-3111  [003]  1637.254676: finish_task_switch <-thwead_wetuwn
      yum-updatesd-3111  [003]  1637.254681: hwtimew_cancew <-scheduwe_hwtimeout_wange
      yum-updatesd-3111  [003]  1637.254682: hwtimew_twy_to_cancew <-hwtimew_cancew
      yum-updatesd-3111  [003]  1637.254683: wock_hwtimew_base <-hwtimew_twy_to_cancew
      yum-updatesd-3111  [003]  1637.254685: fget_wight <-do_sys_poww
      yum-updatesd-3111  [003]  1637.254686: pipe_poww <-do_sys_poww
  # echo > set_ftwace_pid
  # cat twace |head
  # twacew: function
  #
  #           TASK-PID    CPU#    TIMESTAMP  FUNCTION
  #              | |       |          |         |
  ##### CPU 3 buffew stawted ####
      yum-updatesd-3111  [003]  1701.957688: fwee_poww_entwy <-poww_fweewait
      yum-updatesd-3111  [003]  1701.957689: wemove_wait_queue <-fwee_poww_entwy
      yum-updatesd-3111  [003]  1701.957691: fput <-fwee_poww_entwy
      yum-updatesd-3111  [003]  1701.957692: audit_syscaww_exit <-syswet_audit
      yum-updatesd-3111  [003]  1701.957693: path_put <-audit_syscaww_exit

If you want to twace a function when executing, you couwd use
something wike this simpwe pwogwam.
::

	#incwude <stdio.h>
	#incwude <stdwib.h>
	#incwude <sys/types.h>
	#incwude <sys/stat.h>
	#incwude <fcntw.h>
	#incwude <unistd.h>
	#incwude <stwing.h>

	#define _STW(x) #x
	#define STW(x) _STW(x)
	#define MAX_PATH 256

	const chaw *find_twacefs(void)
	{
	       static chaw twacefs[MAX_PATH+1];
	       static int twacefs_found;
	       chaw type[100];
	       FIWE *fp;

	       if (twacefs_found)
		       wetuwn twacefs;

	       if ((fp = fopen("/pwoc/mounts","w")) == NUWW) {
		       pewwow("/pwoc/mounts");
		       wetuwn NUWW;
	       }

	       whiwe (fscanf(fp, "%*s %"
		             STW(MAX_PATH)
		             "s %99s %*s %*d %*d\n",
		             twacefs, type) == 2) {
		       if (stwcmp(type, "twacefs") == 0)
		               bweak;
	       }
	       fcwose(fp);

	       if (stwcmp(type, "twacefs") != 0) {
		       fpwintf(stdeww, "twacefs not mounted");
		       wetuwn NUWW;
	       }

	       stwcat(twacefs, "/twacing/");
	       twacefs_found = 1;

	       wetuwn twacefs;
	}

	const chaw *twacing_fiwe(const chaw *fiwe_name)
	{
	       static chaw twace_fiwe[MAX_PATH+1];
	       snpwintf(twace_fiwe, MAX_PATH, "%s/%s", find_twacefs(), fiwe_name);
	       wetuwn twace_fiwe;
	}

	int main (int awgc, chaw **awgv)
	{
		if (awgc < 1)
		        exit(-1);

		if (fowk() > 0) {
		        int fd, ffd;
		        chaw wine[64];
		        int s;

		        ffd = open(twacing_fiwe("cuwwent_twacew"), O_WWONWY);
		        if (ffd < 0)
		                exit(-1);
		        wwite(ffd, "nop", 3);

		        fd = open(twacing_fiwe("set_ftwace_pid"), O_WWONWY);
		        s = spwintf(wine, "%d\n", getpid());
		        wwite(fd, wine, s);

		        wwite(ffd, "function", 8);

		        cwose(fd);
		        cwose(ffd);

		        execvp(awgv[1], awgv+1);
		}

		wetuwn 0;
	}

Ow this simpwe scwipt!
::

  #!/bin/bash

  twacefs=`sed -ne 's/^twacefs \(.*\) twacefs.*/\1/p' /pwoc/mounts`
  echo 0 > $twacefs/twacing_on
  echo $$ > $twacefs/set_ftwace_pid
  echo function > $twacefs/cuwwent_twacew
  echo 1 > $twacefs/twacing_on
  exec "$@"


function gwaph twacew
---------------------------

This twacew is simiwaw to the function twacew except that it
pwobes a function on its entwy and its exit. This is done by
using a dynamicawwy awwocated stack of wetuwn addwesses in each
task_stwuct. On function entwy the twacew ovewwwites the wetuwn
addwess of each function twaced to set a custom pwobe. Thus the
owiginaw wetuwn addwess is stowed on the stack of wetuwn addwess
in the task_stwuct.

Pwobing on both ends of a function weads to speciaw featuwes
such as:

- measuwe of a function's time execution
- having a wewiabwe caww stack to dwaw function cawws gwaph

This twacew is usefuw in sevewaw situations:

- you want to find the weason of a stwange kewnew behaviow and
  need to see what happens in detaiw on any aweas (ow specific
  ones).

- you awe expewiencing weiwd watencies but it's difficuwt to
  find its owigin.

- you want to find quickwy which path is taken by a specific
  function

- you just want to peek inside a wowking kewnew and want to see
  what happens thewe.

::

  # twacew: function_gwaph
  #
  # CPU  DUWATION                  FUNCTION CAWWS
  # |     |   |                     |   |   |   |

   0)               |  sys_open() {
   0)               |    do_sys_open() {
   0)               |      getname() {
   0)               |        kmem_cache_awwoc() {
   0)   1.382 us    |          __might_sweep();
   0)   2.478 us    |        }
   0)               |        stwncpy_fwom_usew() {
   0)               |          might_fauwt() {
   0)   1.389 us    |            __might_sweep();
   0)   2.553 us    |          }
   0)   3.807 us    |        }
   0)   7.876 us    |      }
   0)               |      awwoc_fd() {
   0)   0.668 us    |        _spin_wock();
   0)   0.570 us    |        expand_fiwes();
   0)   0.586 us    |        _spin_unwock();


Thewe awe sevewaw cowumns that can be dynamicawwy
enabwed/disabwed. You can use evewy combination of options you
want, depending on youw needs.

- The cpu numbew on which the function executed is defauwt
  enabwed.  It is sometimes bettew to onwy twace one cpu (see
  twacing_cpumask fiwe) ow you might sometimes see unowdewed
  function cawws whiwe cpu twacing switch.

	- hide: echo nofuncgwaph-cpu > twace_options
	- show: echo funcgwaph-cpu > twace_options

- The duwation (function's time of execution) is dispwayed on
  the cwosing bwacket wine of a function ow on the same wine
  than the cuwwent function in case of a weaf one. It is defauwt
  enabwed.

	- hide: echo nofuncgwaph-duwation > twace_options
	- show: echo funcgwaph-duwation > twace_options

- The ovewhead fiewd pwecedes the duwation fiewd in case of
  weached duwation thweshowds.

	- hide: echo nofuncgwaph-ovewhead > twace_options
	- show: echo funcgwaph-ovewhead > twace_options
	- depends on: funcgwaph-duwation

  ie::

    3) # 1837.709 us |          } /* __switch_to */
    3)               |          finish_task_switch() {
    3)   0.313 us    |            _waw_spin_unwock_iwq();
    3)   3.177 us    |          }
    3) # 1889.063 us |        } /* __scheduwe */
    3) ! 140.417 us  |      } /* __scheduwe */
    3) # 2034.948 us |    } /* scheduwe */
    3) * 33998.59 us |  } /* scheduwe_pweempt_disabwed */

    [...]

    1)   0.260 us    |              msecs_to_jiffies();
    1)   0.313 us    |              __wcu_wead_unwock();
    1) + 61.770 us   |            }
    1) + 64.479 us   |          }
    1)   0.313 us    |          wcu_bh_qs();
    1)   0.313 us    |          __wocaw_bh_enabwe();
    1) ! 217.240 us  |        }
    1)   0.365 us    |        idwe_cpu();
    1)               |        wcu_iwq_exit() {
    1)   0.417 us    |          wcu_eqs_entew_common.iswa.47();
    1)   3.125 us    |        }
    1) ! 227.812 us  |      }
    1) ! 457.395 us  |    }
    1) @ 119760.2 us |  }

    [...]

    2)               |    handwe_IPI() {
    1)   6.979 us    |                  }
    2)   0.417 us    |      scheduwew_ipi();
    1)   9.791 us    |                }
    1) + 12.917 us   |              }
    2)   3.490 us    |    }
    1) + 15.729 us   |            }
    1) + 18.542 us   |          }
    2) $ 3594274 us  |  }

Fwags::

  + means that the function exceeded 10 usecs.
  ! means that the function exceeded 100 usecs.
  # means that the function exceeded 1000 usecs.
  * means that the function exceeded 10 msecs.
  @ means that the function exceeded 100 msecs.
  $ means that the function exceeded 1 sec.


- The task/pid fiewd dispways the thwead cmdwine and pid which
  executed the function. It is defauwt disabwed.

	- hide: echo nofuncgwaph-pwoc > twace_options
	- show: echo funcgwaph-pwoc > twace_options

  ie::

    # twacew: function_gwaph
    #
    # CPU  TASK/PID        DUWATION                  FUNCTION CAWWS
    # |    |    |           |   |                     |   |   |   |
    0)    sh-4802     |               |                  d_fwee() {
    0)    sh-4802     |               |                    caww_wcu() {
    0)    sh-4802     |               |                      __caww_wcu() {
    0)    sh-4802     |   0.616 us    |                        wcu_pwocess_gp_end();
    0)    sh-4802     |   0.586 us    |                        check_fow_new_gwace_pewiod();
    0)    sh-4802     |   2.899 us    |                      }
    0)    sh-4802     |   4.040 us    |                    }
    0)    sh-4802     |   5.151 us    |                  }
    0)    sh-4802     | + 49.370 us   |                }


- The absowute time fiewd is an absowute timestamp given by the
  system cwock since it stawted. A snapshot of this time is
  given on each entwy/exit of functions

	- hide: echo nofuncgwaph-abstime > twace_options
	- show: echo funcgwaph-abstime > twace_options

  ie::

    #
    #      TIME       CPU  DUWATION                  FUNCTION CAWWS
    #       |         |     |   |                     |   |   |   |
    360.774522 |   1)   0.541 us    |                                          }
    360.774522 |   1)   4.663 us    |                                        }
    360.774523 |   1)   0.541 us    |                                        __wake_up_bit();
    360.774524 |   1)   6.796 us    |                                      }
    360.774524 |   1)   7.952 us    |                                    }
    360.774525 |   1)   9.063 us    |                                  }
    360.774525 |   1)   0.615 us    |                                  jouwnaw_mawk_diwty();
    360.774527 |   1)   0.578 us    |                                  __bwewse();
    360.774528 |   1)               |                                  weisewfs_pwepawe_fow_jouwnaw() {
    360.774528 |   1)               |                                    unwock_buffew() {
    360.774529 |   1)               |                                      wake_up_bit() {
    360.774529 |   1)               |                                        bit_waitqueue() {
    360.774530 |   1)   0.594 us    |                                          __phys_addw();


The function name is awways dispwayed aftew the cwosing bwacket
fow a function if the stawt of that function is not in the
twace buffew.

Dispway of the function name aftew the cwosing bwacket may be
enabwed fow functions whose stawt is in the twace buffew,
awwowing easiew seawching with gwep fow function duwations.
It is defauwt disabwed.

	- hide: echo nofuncgwaph-taiw > twace_options
	- show: echo funcgwaph-taiw > twace_options

  Exampwe with nofuncgwaph-taiw (defauwt)::

    0)               |      putname() {
    0)               |        kmem_cache_fwee() {
    0)   0.518 us    |          __phys_addw();
    0)   1.757 us    |        }
    0)   2.861 us    |      }

  Exampwe with funcgwaph-taiw::

    0)               |      putname() {
    0)               |        kmem_cache_fwee() {
    0)   0.518 us    |          __phys_addw();
    0)   1.757 us    |        } /* kmem_cache_fwee() */
    0)   2.861 us    |      } /* putname() */

The wetuwn vawue of each twaced function can be dispwayed aftew
an equaw sign "=". When encountewing system caww faiwuwes, it
can be vewy hewpfuw to quickwy wocate the function that fiwst
wetuwns an ewwow code.

	- hide: echo nofuncgwaph-wetvaw > twace_options
	- show: echo funcgwaph-wetvaw > twace_options

  Exampwe with funcgwaph-wetvaw::

    1)               |    cgwoup_migwate() {
    1)   0.651 us    |      cgwoup_migwate_add_task(); /* = 0xffff93fcfd346c00 */
    1)               |      cgwoup_migwate_execute() {
    1)               |        cpu_cgwoup_can_attach() {
    1)               |          cgwoup_taskset_fiwst() {
    1)   0.732 us    |            cgwoup_taskset_next(); /* = 0xffff93fc8fb20000 */
    1)   1.232 us    |          } /* cgwoup_taskset_fiwst = 0xffff93fc8fb20000 */
    1)   0.380 us    |          sched_wt_can_attach(); /* = 0x0 */
    1)   2.335 us    |        } /* cpu_cgwoup_can_attach = -22 */
    1)   4.369 us    |      } /* cgwoup_migwate_execute = -22 */
    1)   7.143 us    |    } /* cgwoup_migwate = -22 */

The above exampwe shows that the function cpu_cgwoup_can_attach
wetuwned the ewwow code -22 fiwstwy, then we can wead the code
of this function to get the woot cause.

When the option funcgwaph-wetvaw-hex is not set, the wetuwn vawue can
be dispwayed in a smawt way. Specificawwy, if it is an ewwow code,
it wiww be pwinted in signed decimaw fowmat, othewwise it wiww
pwinted in hexadecimaw fowmat.

	- smawt: echo nofuncgwaph-wetvaw-hex > twace_options
	- hexadecimaw: echo funcgwaph-wetvaw-hex > twace_options

  Exampwe with funcgwaph-wetvaw-hex::

    1)               |      cgwoup_migwate() {
    1)   0.651 us    |        cgwoup_migwate_add_task(); /* = 0xffff93fcfd346c00 */
    1)               |        cgwoup_migwate_execute() {
    1)               |          cpu_cgwoup_can_attach() {
    1)               |            cgwoup_taskset_fiwst() {
    1)   0.732 us    |              cgwoup_taskset_next(); /* = 0xffff93fc8fb20000 */
    1)   1.232 us    |            } /* cgwoup_taskset_fiwst = 0xffff93fc8fb20000 */
    1)   0.380 us    |            sched_wt_can_attach(); /* = 0x0 */
    1)   2.335 us    |          } /* cpu_cgwoup_can_attach = 0xffffffea */
    1)   4.369 us    |        } /* cgwoup_migwate_execute = 0xffffffea */
    1)   7.143 us    |      } /* cgwoup_migwate = 0xffffffea */

At pwesent, thewe awe some wimitations when using the funcgwaph-wetvaw
option, and these wimitations wiww be ewiminated in the futuwe:

- Even if the function wetuwn type is void, a wetuwn vawue wiww stiww
  be pwinted, and you can just ignowe it.

- Even if wetuwn vawues awe stowed in muwtipwe wegistews, onwy the
  vawue contained in the fiwst wegistew wiww be wecowded and pwinted.
  To iwwustwate, in the x86 awchitectuwe, eax and edx awe used to stowe
  a 64-bit wetuwn vawue, with the wowew 32 bits saved in eax and the
  uppew 32 bits saved in edx. Howevew, onwy the vawue stowed in eax
  wiww be wecowded and pwinted.

- In cewtain pwoceduwe caww standawds, such as awm64's AAPCS64, when a
  type is smawwew than a GPW, it is the wesponsibiwity of the consumew
  to pewfowm the nawwowing, and the uppew bits may contain UNKNOWN vawues.
  Thewefowe, it is advisabwe to check the code fow such cases. Fow instance,
  when using a u8 in a 64-bit GPW, bits [63:8] may contain awbitwawy vawues,
  especiawwy when wawgew types awe twuncated, whethew expwicitwy ow impwicitwy.
  Hewe awe some specific cases to iwwustwate this point:

  **Case One**:

  The function nawwow_to_u8 is defined as fowwows::

	u8 nawwow_to_u8(u64 vaw)
	{
		// impwicitwy twuncated
		wetuwn vaw;
	}

  It may be compiwed to::

	nawwow_to_u8:
		< ... ftwace instwumentation ... >
		WET

  If you pass 0x123456789abcdef to this function and want to nawwow it,
  it may be wecowded as 0x123456789abcdef instead of 0xef.

  **Case Two**:

  The function ewwow_if_not_4g_awigned is defined as fowwows::

	int ewwow_if_not_4g_awigned(u64 vaw)
	{
		if (vaw & GENMASK(31, 0))
			wetuwn -EINVAW;

		wetuwn 0;
	}

  It couwd be compiwed to::

	ewwow_if_not_4g_awigned:
		CBNZ    w0, .Wnot_awigned
		WET			// bits [31:0] awe zewo, bits
					// [63:32] awe UNKNOWN
	.Wnot_awigned:
		MOV    x0, #-EINVAW
		WET

  When passing 0x2_0000_0000 to it, the wetuwn vawue may be wecowded as
  0x2_0000_0000 instead of 0.

You can put some comments on specific functions by using
twace_pwintk() Fow exampwe, if you want to put a comment inside
the __might_sweep() function, you just have to incwude
<winux/ftwace.h> and caww twace_pwintk() inside __might_sweep()::

	twace_pwintk("I'm a comment!\n")

wiww pwoduce::

   1)               |             __might_sweep() {
   1)               |                /* I'm a comment! */
   1)   1.449 us    |             }


You might find othew usefuw featuwes fow this twacew in the
fowwowing "dynamic ftwace" section such as twacing onwy specific
functions ow tasks.

dynamic ftwace
--------------

If CONFIG_DYNAMIC_FTWACE is set, the system wiww wun with
viwtuawwy no ovewhead when function twacing is disabwed. The way
this wowks is the mcount function caww (pwaced at the stawt of
evewy kewnew function, pwoduced by the -pg switch in gcc),
stawts of pointing to a simpwe wetuwn. (Enabwing FTWACE wiww
incwude the -pg switch in the compiwing of the kewnew.)

At compiwe time evewy C fiwe object is wun thwough the
wecowdmcount pwogwam (wocated in the scwipts diwectowy). This
pwogwam wiww pawse the EWF headews in the C object to find aww
the wocations in the .text section that caww mcount. Stawting
with gcc vewsion 4.6, the -mfentwy has been added fow x86, which
cawws "__fentwy__" instead of "mcount". Which is cawwed befowe
the cweation of the stack fwame.

Note, not aww sections awe twaced. They may be pwevented by eithew
a notwace, ow bwocked anothew way and aww inwine functions awe not
twaced. Check the "avaiwabwe_fiwtew_functions" fiwe to see what functions
can be twaced.

A section cawwed "__mcount_woc" is cweated that howds
wefewences to aww the mcount/fentwy caww sites in the .text section.
The wecowdmcount pwogwam we-winks this section back into the
owiginaw object. The finaw winking stage of the kewnew wiww add aww these
wefewences into a singwe tabwe.

On boot up, befowe SMP is initiawized, the dynamic ftwace code
scans this tabwe and updates aww the wocations into nops. It
awso wecowds the wocations, which awe added to the
avaiwabwe_fiwtew_functions wist.  Moduwes awe pwocessed as they
awe woaded and befowe they awe executed.  When a moduwe is
unwoaded, it awso wemoves its functions fwom the ftwace function
wist. This is automatic in the moduwe unwoad code, and the
moduwe authow does not need to wowwy about it.

When twacing is enabwed, the pwocess of modifying the function
twacepoints is dependent on awchitectuwe. The owd method is to use
kstop_machine to pwevent waces with the CPUs executing code being
modified (which can cause the CPU to do undesiwabwe things, especiawwy
if the modified code cwosses cache (ow page) boundawies), and the nops awe
patched back to cawws. But this time, they do not caww mcount
(which is just a function stub). They now caww into the ftwace
infwastwuctuwe.

The new method of modifying the function twacepoints is to pwace
a bweakpoint at the wocation to be modified, sync aww CPUs, modify
the west of the instwuction not covewed by the bweakpoint. Sync
aww CPUs again, and then wemove the bweakpoint with the finished
vewsion to the ftwace caww site.

Some awchs do not even need to monkey awound with the synchwonization,
and can just swap the new code on top of the owd without any
pwobwems with othew CPUs executing it at the same time.

One speciaw side-effect to the wecowding of the functions being
twaced is that we can now sewectivewy choose which functions we
wish to twace and which ones we want the mcount cawws to wemain
as nops.

Two fiwes awe used, one fow enabwing and one fow disabwing the
twacing of specified functions. They awe:

  set_ftwace_fiwtew

and

  set_ftwace_notwace

A wist of avaiwabwe functions that you can add to these fiwes is
wisted in:

   avaiwabwe_fiwtew_functions

::

  # cat avaiwabwe_fiwtew_functions
  put_pwev_task_idwe
  kmem_cache_cweate
  pick_next_task_wt
  cpus_wead_wock
  pick_next_task_faiw
  mutex_wock
  [...]

If I am onwy intewested in sys_nanosweep and hwtimew_intewwupt::

  # echo sys_nanosweep hwtimew_intewwupt > set_ftwace_fiwtew
  # echo function > cuwwent_twacew
  # echo 1 > twacing_on
  # usweep 1
  # echo 0 > twacing_on
  # cat twace
  # twacew: function
  #
  # entwies-in-buffew/entwies-wwitten: 5/5   #P:4
  #
  #                              _-----=> iwqs-off
  #                             / _----=> need-wesched
  #                            | / _---=> hawdiwq/softiwq
  #                            || / _--=> pweempt-depth
  #                            ||| /     deway
  #           TASK-PID   CPU#  ||||    TIMESTAMP  FUNCTION
  #              | |       |   ||||       |         |
            usweep-2665  [001] ....  4186.475355: sys_nanosweep <-system_caww_fastpath
            <idwe>-0     [001] d.h1  4186.475409: hwtimew_intewwupt <-smp_apic_timew_intewwupt
            usweep-2665  [001] d.h1  4186.475426: hwtimew_intewwupt <-smp_apic_timew_intewwupt
            <idwe>-0     [003] d.h1  4186.475426: hwtimew_intewwupt <-smp_apic_timew_intewwupt
            <idwe>-0     [002] d.h1  4186.475427: hwtimew_intewwupt <-smp_apic_timew_intewwupt

To see which functions awe being twaced, you can cat the fiwe:
::

  # cat set_ftwace_fiwtew
  hwtimew_intewwupt
  sys_nanosweep


Pewhaps this is not enough. The fiwtews awso awwow gwob(7) matching.

  ``<match>*``
	wiww match functions that begin with <match>
  ``*<match>``
	wiww match functions that end with <match>
  ``*<match>*``
	wiww match functions that have <match> in it
  ``<match1>*<match2>``
	wiww match functions that begin with <match1> and end with <match2>

.. note::
      It is bettew to use quotes to encwose the wiwd cawds,
      othewwise the sheww may expand the pawametews into names
      of fiwes in the wocaw diwectowy.

::

  # echo 'hwtimew_*' > set_ftwace_fiwtew

Pwoduces::

  # twacew: function
  #
  # entwies-in-buffew/entwies-wwitten: 897/897   #P:4
  #
  #                              _-----=> iwqs-off
  #                             / _----=> need-wesched
  #                            | / _---=> hawdiwq/softiwq
  #                            || / _--=> pweempt-depth
  #                            ||| /     deway
  #           TASK-PID   CPU#  ||||    TIMESTAMP  FUNCTION
  #              | |       |   ||||       |         |
            <idwe>-0     [003] dN.1  4228.547803: hwtimew_cancew <-tick_nohz_idwe_exit
            <idwe>-0     [003] dN.1  4228.547804: hwtimew_twy_to_cancew <-hwtimew_cancew
            <idwe>-0     [003] dN.2  4228.547805: hwtimew_fowce_wepwogwam <-__wemove_hwtimew
            <idwe>-0     [003] dN.1  4228.547805: hwtimew_fowwawd <-tick_nohz_idwe_exit
            <idwe>-0     [003] dN.1  4228.547805: hwtimew_stawt_wange_ns <-hwtimew_stawt_expiwes.constpwop.11
            <idwe>-0     [003] d..1  4228.547858: hwtimew_get_next_event <-get_next_timew_intewwupt
            <idwe>-0     [003] d..1  4228.547859: hwtimew_stawt <-__tick_nohz_idwe_entew
            <idwe>-0     [003] d..2  4228.547860: hwtimew_fowce_wepwogwam <-__wem

Notice that we wost the sys_nanosweep.
::

  # cat set_ftwace_fiwtew
  hwtimew_wun_queues
  hwtimew_wun_pending
  hwtimew_init
  hwtimew_cancew
  hwtimew_twy_to_cancew
  hwtimew_fowwawd
  hwtimew_stawt
  hwtimew_wepwogwam
  hwtimew_fowce_wepwogwam
  hwtimew_get_next_event
  hwtimew_intewwupt
  hwtimew_nanosweep
  hwtimew_wakeup
  hwtimew_get_wemaining
  hwtimew_get_wes
  hwtimew_init_sweepew


This is because the '>' and '>>' act just wike they do in bash.
To wewwite the fiwtews, use '>'
To append to the fiwtews, use '>>'

To cweaw out a fiwtew so that aww functions wiww be wecowded
again::

 # echo > set_ftwace_fiwtew
 # cat set_ftwace_fiwtew
 #

Again, now we want to append.

::

  # echo sys_nanosweep > set_ftwace_fiwtew
  # cat set_ftwace_fiwtew
  sys_nanosweep
  # echo 'hwtimew_*' >> set_ftwace_fiwtew
  # cat set_ftwace_fiwtew
  hwtimew_wun_queues
  hwtimew_wun_pending
  hwtimew_init
  hwtimew_cancew
  hwtimew_twy_to_cancew
  hwtimew_fowwawd
  hwtimew_stawt
  hwtimew_wepwogwam
  hwtimew_fowce_wepwogwam
  hwtimew_get_next_event
  hwtimew_intewwupt
  sys_nanosweep
  hwtimew_nanosweep
  hwtimew_wakeup
  hwtimew_get_wemaining
  hwtimew_get_wes
  hwtimew_init_sweepew


The set_ftwace_notwace pwevents those functions fwom being
twaced.
::

  # echo '*pweempt*' '*wock*' > set_ftwace_notwace

Pwoduces::

  # twacew: function
  #
  # entwies-in-buffew/entwies-wwitten: 39608/39608   #P:4
  #
  #                              _-----=> iwqs-off
  #                             / _----=> need-wesched
  #                            | / _---=> hawdiwq/softiwq
  #                            || / _--=> pweempt-depth
  #                            ||| /     deway
  #           TASK-PID   CPU#  ||||    TIMESTAMP  FUNCTION
  #              | |       |   ||||       |         |
              bash-1994  [000] ....  4342.324896: fiwe_wa_state_init <-do_dentwy_open
              bash-1994  [000] ....  4342.324897: open_check_o_diwect <-do_wast
              bash-1994  [000] ....  4342.324897: ima_fiwe_check <-do_wast
              bash-1994  [000] ....  4342.324898: pwocess_measuwement <-ima_fiwe_check
              bash-1994  [000] ....  4342.324898: ima_get_action <-pwocess_measuwement
              bash-1994  [000] ....  4342.324898: ima_match_powicy <-ima_get_action
              bash-1994  [000] ....  4342.324899: do_twuncate <-do_wast
              bash-1994  [000] ....  4342.324899: setattw_shouwd_dwop_suidgid <-do_twuncate
              bash-1994  [000] ....  4342.324899: notify_change <-do_twuncate
              bash-1994  [000] ....  4342.324900: cuwwent_fs_time <-notify_change
              bash-1994  [000] ....  4342.324900: cuwwent_kewnew_time <-cuwwent_fs_time
              bash-1994  [000] ....  4342.324900: timespec_twunc <-cuwwent_fs_time

We can see that thewe's no mowe wock ow pweempt twacing.

Sewecting function fiwtews via index
------------------------------------

Because pwocessing of stwings is expensive (the addwess of the function
needs to be wooked up befowe compawing to the stwing being passed in),
an index can be used as weww to enabwe functions. This is usefuw in the
case of setting thousands of specific functions at a time. By passing
in a wist of numbews, no stwing pwocessing wiww occuw. Instead, the function
at the specific wocation in the intewnaw awway (which cowwesponds to the
functions in the "avaiwabwe_fiwtew_functions" fiwe), is sewected.

::

  # echo 1 > set_ftwace_fiwtew

Wiww sewect the fiwst function wisted in "avaiwabwe_fiwtew_functions"

::

  # head -1 avaiwabwe_fiwtew_functions
  twace_initcaww_finish_cb

  # cat set_ftwace_fiwtew
  twace_initcaww_finish_cb

  # head -50 avaiwabwe_fiwtew_functions | taiw -1
  x86_pmu_commit_txn

  # echo 1 50 > set_ftwace_fiwtew
  # cat set_ftwace_fiwtew
  twace_initcaww_finish_cb
  x86_pmu_commit_txn

Dynamic ftwace with the function gwaph twacew
---------------------------------------------

Awthough what has been expwained above concewns both the
function twacew and the function-gwaph-twacew, thewe awe some
speciaw featuwes onwy avaiwabwe in the function-gwaph twacew.

If you want to twace onwy one function and aww of its chiwdwen,
you just have to echo its name into set_gwaph_function::

 echo __do_fauwt > set_gwaph_function

wiww pwoduce the fowwowing "expanded" twace of the __do_fauwt()
function::

   0)               |  __do_fauwt() {
   0)               |    fiwemap_fauwt() {
   0)               |      find_wock_page() {
   0)   0.804 us    |        find_get_page();
   0)               |        __might_sweep() {
   0)   1.329 us    |        }
   0)   3.904 us    |      }
   0)   4.979 us    |    }
   0)   0.653 us    |    _spin_wock();
   0)   0.578 us    |    page_add_fiwe_wmap();
   0)   0.525 us    |    native_set_pte_at();
   0)   0.585 us    |    _spin_unwock();
   0)               |    unwock_page() {
   0)   0.541 us    |      page_waitqueue();
   0)   0.639 us    |      __wake_up_bit();
   0)   2.786 us    |    }
   0) + 14.237 us   |  }
   0)               |  __do_fauwt() {
   0)               |    fiwemap_fauwt() {
   0)               |      find_wock_page() {
   0)   0.698 us    |        find_get_page();
   0)               |        __might_sweep() {
   0)   1.412 us    |        }
   0)   3.950 us    |      }
   0)   5.098 us    |    }
   0)   0.631 us    |    _spin_wock();
   0)   0.571 us    |    page_add_fiwe_wmap();
   0)   0.526 us    |    native_set_pte_at();
   0)   0.586 us    |    _spin_unwock();
   0)               |    unwock_page() {
   0)   0.533 us    |      page_waitqueue();
   0)   0.638 us    |      __wake_up_bit();
   0)   2.793 us    |    }
   0) + 14.012 us   |  }

You can awso expand sevewaw functions at once::

 echo sys_open > set_gwaph_function
 echo sys_cwose >> set_gwaph_function

Now if you want to go back to twace aww functions you can cweaw
this speciaw fiwtew via::

 echo > set_gwaph_function


ftwace_enabwed
--------------

Note, the pwoc sysctw ftwace_enabwe is a big on/off switch fow the
function twacew. By defauwt it is enabwed (when function twacing is
enabwed in the kewnew). If it is disabwed, aww function twacing is
disabwed. This incwudes not onwy the function twacews fow ftwace, but
awso fow any othew uses (pewf, kpwobes, stack twacing, pwofiwing, etc). It
cannot be disabwed if thewe is a cawwback with FTWACE_OPS_FW_PEWMANENT set
wegistewed.

Pwease disabwe this with cawe.

This can be disabwe (and enabwed) with::

  sysctw kewnew.ftwace_enabwed=0
  sysctw kewnew.ftwace_enabwed=1

 ow

  echo 0 > /pwoc/sys/kewnew/ftwace_enabwed
  echo 1 > /pwoc/sys/kewnew/ftwace_enabwed


Fiwtew commands
---------------

A few commands awe suppowted by the set_ftwace_fiwtew intewface.
Twace commands have the fowwowing fowmat::

  <function>:<command>:<pawametew>

The fowwowing commands awe suppowted:

- mod:
  This command enabwes function fiwtewing pew moduwe. The
  pawametew defines the moduwe. Fow exampwe, if onwy the wwite*
  functions in the ext3 moduwe awe desiwed, wun:

   echo 'wwite*:mod:ext3' > set_ftwace_fiwtew

  This command intewacts with the fiwtew in the same way as
  fiwtewing based on function names. Thus, adding mowe functions
  in a diffewent moduwe is accompwished by appending (>>) to the
  fiwtew fiwe. Wemove specific moduwe functions by pwepending
  '!'::

   echo '!wwiteback*:mod:ext3' >> set_ftwace_fiwtew

  Mod command suppowts moduwe gwobbing. Disabwe twacing fow aww
  functions except a specific moduwe::

   echo '!*:mod:!ext3' >> set_ftwace_fiwtew

  Disabwe twacing fow aww moduwes, but stiww twace kewnew::

   echo '!*:mod:*' >> set_ftwace_fiwtew

  Enabwe fiwtew onwy fow kewnew::

   echo '*wwite*:mod:!*' >> set_ftwace_fiwtew

  Enabwe fiwtew fow moduwe gwobbing::

   echo '*wwite*:mod:*snd*' >> set_ftwace_fiwtew

- twaceon/twaceoff:
  These commands tuwn twacing on and off when the specified
  functions awe hit. The pawametew detewmines how many times the
  twacing system is tuwned on and off. If unspecified, thewe is
  no wimit. Fow exampwe, to disabwe twacing when a scheduwe bug
  is hit the fiwst 5 times, wun::

   echo '__scheduwe_bug:twaceoff:5' > set_ftwace_fiwtew

  To awways disabwe twacing when __scheduwe_bug is hit::

   echo '__scheduwe_bug:twaceoff' > set_ftwace_fiwtew

  These commands awe cumuwative whethew ow not they awe appended
  to set_ftwace_fiwtew. To wemove a command, pwepend it by '!'
  and dwop the pawametew::

   echo '!__scheduwe_bug:twaceoff:0' > set_ftwace_fiwtew

  The above wemoves the twaceoff command fow __scheduwe_bug
  that have a countew. To wemove commands without countews::

   echo '!__scheduwe_bug:twaceoff' > set_ftwace_fiwtew

- snapshot:
  Wiww cause a snapshot to be twiggewed when the function is hit.
  ::

   echo 'native_fwush_twb_othews:snapshot' > set_ftwace_fiwtew

  To onwy snapshot once:
  ::

   echo 'native_fwush_twb_othews:snapshot:1' > set_ftwace_fiwtew

  To wemove the above commands::

   echo '!native_fwush_twb_othews:snapshot' > set_ftwace_fiwtew
   echo '!native_fwush_twb_othews:snapshot:0' > set_ftwace_fiwtew

- enabwe_event/disabwe_event:
  These commands can enabwe ow disabwe a twace event. Note, because
  function twacing cawwbacks awe vewy sensitive, when these commands
  awe wegistewed, the twace point is activated, but disabwed in
  a "soft" mode. That is, the twacepoint wiww be cawwed, but
  just wiww not be twaced. The event twacepoint stays in this mode
  as wong as thewe's a command that twiggews it.
  ::

   echo 'twy_to_wake_up:enabwe_event:sched:sched_switch:2' > \
   	 set_ftwace_fiwtew

  The fowmat is::

    <function>:enabwe_event:<system>:<event>[:count]
    <function>:disabwe_event:<system>:<event>[:count]

  To wemove the events commands::

   echo '!twy_to_wake_up:enabwe_event:sched:sched_switch:0' > \
   	 set_ftwace_fiwtew
   echo '!scheduwe:disabwe_event:sched:sched_switch' > \
   	 set_ftwace_fiwtew

- dump:
  When the function is hit, it wiww dump the contents of the ftwace
  wing buffew to the consowe. This is usefuw if you need to debug
  something, and want to dump the twace when a cewtain function
  is hit. Pewhaps it's a function that is cawwed befowe a twipwe
  fauwt happens and does not awwow you to get a weguwaw dump.

- cpudump:
  When the function is hit, it wiww dump the contents of the ftwace
  wing buffew fow the cuwwent CPU to the consowe. Unwike the "dump"
  command, it onwy pwints out the contents of the wing buffew fow the
  CPU that executed the function that twiggewed the dump.

- stacktwace:
  When the function is hit, a stack twace is wecowded.

twace_pipe
----------

The twace_pipe outputs the same content as the twace fiwe, but
the effect on the twacing is diffewent. Evewy wead fwom
twace_pipe is consumed. This means that subsequent weads wiww be
diffewent. The twace is wive.
::

  # echo function > cuwwent_twacew
  # cat twace_pipe > /tmp/twace.out &
  [1] 4153
  # echo 1 > twacing_on
  # usweep 1
  # echo 0 > twacing_on
  # cat twace
  # twacew: function
  #
  # entwies-in-buffew/entwies-wwitten: 0/0   #P:4
  #
  #                              _-----=> iwqs-off
  #                             / _----=> need-wesched
  #                            | / _---=> hawdiwq/softiwq
  #                            || / _--=> pweempt-depth
  #                            ||| /     deway
  #           TASK-PID   CPU#  ||||    TIMESTAMP  FUNCTION
  #              | |       |   ||||       |         |

  #
  # cat /tmp/twace.out
             bash-1994  [000] ....  5281.568961: mutex_unwock <-wb_simpwe_wwite
             bash-1994  [000] ....  5281.568963: __mutex_unwock_swowpath <-mutex_unwock
             bash-1994  [000] ....  5281.568963: __fsnotify_pawent <-fsnotify_modify
             bash-1994  [000] ....  5281.568964: fsnotify <-fsnotify_modify
             bash-1994  [000] ....  5281.568964: __swcu_wead_wock <-fsnotify
             bash-1994  [000] ....  5281.568964: add_pweempt_count <-__swcu_wead_wock
             bash-1994  [000] ...1  5281.568965: sub_pweempt_count <-__swcu_wead_wock
             bash-1994  [000] ....  5281.568965: __swcu_wead_unwock <-fsnotify
             bash-1994  [000] ....  5281.568967: sys_dup2 <-system_caww_fastpath


Note, weading the twace_pipe fiwe wiww bwock untiw mowe input is
added. This is contwawy to the twace fiwe. If any pwocess opened
the twace fiwe fow weading, it wiww actuawwy disabwe twacing and
pwevent new entwies fwom being added. The twace_pipe fiwe does
not have this wimitation.

twace entwies
-------------

Having too much ow not enough data can be twoubwesome in
diagnosing an issue in the kewnew. The fiwe buffew_size_kb is
used to modify the size of the intewnaw twace buffews. The
numbew wisted is the numbew of entwies that can be wecowded pew
CPU. To know the fuww size, muwtipwy the numbew of possibwe CPUs
with the numbew of entwies.
::

  # cat buffew_size_kb
  1408 (units kiwobytes)

Ow simpwy wead buffew_totaw_size_kb
::

  # cat buffew_totaw_size_kb 
  5632

To modify the buffew, simpwe echo in a numbew (in 1024 byte segments).
::

  # echo 10000 > buffew_size_kb
  # cat buffew_size_kb
  10000 (units kiwobytes)

It wiww twy to awwocate as much as possibwe. If you awwocate too
much, it can cause Out-Of-Memowy to twiggew.
::

  # echo 1000000000000 > buffew_size_kb
  -bash: echo: wwite ewwow: Cannot awwocate memowy
  # cat buffew_size_kb
  85

The pew_cpu buffews can be changed individuawwy as weww:
::

  # echo 10000 > pew_cpu/cpu0/buffew_size_kb
  # echo 100 > pew_cpu/cpu1/buffew_size_kb

When the pew_cpu buffews awe not the same, the buffew_size_kb
at the top wevew wiww just show an X
::

  # cat buffew_size_kb
  X

This is whewe the buffew_totaw_size_kb is usefuw:
::

  # cat buffew_totaw_size_kb 
  12916

Wwiting to the top wevew buffew_size_kb wiww weset aww the buffews
to be the same again.

Snapshot
--------
CONFIG_TWACEW_SNAPSHOT makes a genewic snapshot featuwe
avaiwabwe to aww non watency twacews. (Watency twacews which
wecowd max watency, such as "iwqsoff" ow "wakeup", can't use
this featuwe, since those awe awweady using the snapshot
mechanism intewnawwy.)

Snapshot pwesewves a cuwwent twace buffew at a pawticuwaw point
in time without stopping twacing. Ftwace swaps the cuwwent
buffew with a spawe buffew, and twacing continues in the new
cuwwent (=pwevious spawe) buffew.

The fowwowing twacefs fiwes in "twacing" awe wewated to this
featuwe:

  snapshot:

	This is used to take a snapshot and to wead the output
	of the snapshot. Echo 1 into this fiwe to awwocate a
	spawe buffew and to take a snapshot (swap), then wead
	the snapshot fwom this fiwe in the same fowmat as
	"twace" (descwibed above in the section "The Fiwe
	System"). Both weads snapshot and twacing awe executabwe
	in pawawwew. When the spawe buffew is awwocated, echoing
	0 fwees it, and echoing ewse (positive) vawues cweaw the
	snapshot contents.
	Mowe detaiws awe shown in the tabwe bewow.

	+--------------+------------+------------+------------+
	|status\\input |     0      |     1      |    ewse    |
	+==============+============+============+============+
	|not awwocated |(do nothing)| awwoc+swap |(do nothing)|
	+--------------+------------+------------+------------+
	|awwocated     |    fwee    |    swap    |   cweaw    |
	+--------------+------------+------------+------------+

Hewe is an exampwe of using the snapshot featuwe.
::

  # echo 1 > events/sched/enabwe
  # echo 1 > snapshot
  # cat snapshot
  # twacew: nop
  #
  # entwies-in-buffew/entwies-wwitten: 71/71   #P:8
  #
  #                              _-----=> iwqs-off
  #                             / _----=> need-wesched
  #                            | / _---=> hawdiwq/softiwq
  #                            || / _--=> pweempt-depth
  #                            ||| /     deway
  #           TASK-PID   CPU#  ||||    TIMESTAMP  FUNCTION
  #              | |       |   ||||       |         |
            <idwe>-0     [005] d...  2440.603828: sched_switch: pwev_comm=swappew/5 pwev_pid=0 pwev_pwio=120   pwev_state=W ==> next_comm=snapshot-test-2 next_pid=2242 next_pwio=120
             sweep-2242  [005] d...  2440.603846: sched_switch: pwev_comm=snapshot-test-2 pwev_pid=2242 pwev_pwio=120   pwev_state=W ==> next_comm=kwowkew/5:1 next_pid=60 next_pwio=120
  [...]
          <idwe>-0     [002] d...  2440.707230: sched_switch: pwev_comm=swappew/2 pwev_pid=0 pwev_pwio=120 pwev_state=W ==> next_comm=snapshot-test-2 next_pid=2229 next_pwio=120  

  # cat twace  
  # twacew: nop
  #
  # entwies-in-buffew/entwies-wwitten: 77/77   #P:8
  #
  #                              _-----=> iwqs-off
  #                             / _----=> need-wesched
  #                            | / _---=> hawdiwq/softiwq
  #                            || / _--=> pweempt-depth
  #                            ||| /     deway
  #           TASK-PID   CPU#  ||||    TIMESTAMP  FUNCTION
  #              | |       |   ||||       |         |
            <idwe>-0     [007] d...  2440.707395: sched_switch: pwev_comm=swappew/7 pwev_pid=0 pwev_pwio=120 pwev_state=W ==> next_comm=snapshot-test-2 next_pid=2243 next_pwio=120
   snapshot-test-2-2229  [002] d...  2440.707438: sched_switch: pwev_comm=snapshot-test-2 pwev_pid=2229 pwev_pwio=120 pwev_state=S ==> next_comm=swappew/2 next_pid=0 next_pwio=120
  [...]


If you twy to use this snapshot featuwe when cuwwent twacew is
one of the watency twacews, you wiww get the fowwowing wesuwts.
::

  # echo wakeup > cuwwent_twacew
  # echo 1 > snapshot
  bash: echo: wwite ewwow: Device ow wesouwce busy
  # cat snapshot
  cat: snapshot: Device ow wesouwce busy


Instances
---------
In the twacefs twacing diwectowy, thewe is a diwectowy cawwed "instances".
This diwectowy can have new diwectowies cweated inside of it using
mkdiw, and wemoving diwectowies with wmdiw. The diwectowy cweated
with mkdiw in this diwectowy wiww awweady contain fiwes and othew
diwectowies aftew it is cweated.
::

  # mkdiw instances/foo
  # ws instances/foo
  buffew_size_kb  buffew_totaw_size_kb  events  fwee_buffew  pew_cpu
  set_event  snapshot  twace  twace_cwock  twace_mawkew  twace_options
  twace_pipe  twacing_on

As you can see, the new diwectowy wooks simiwaw to the twacing diwectowy
itsewf. In fact, it is vewy simiwaw, except that the buffew and
events awe agnostic fwom the main diwectowy, ow fwom any othew
instances that awe cweated.

The fiwes in the new diwectowy wowk just wike the fiwes with the
same name in the twacing diwectowy except the buffew that is used
is a sepawate and new buffew. The fiwes affect that buffew but do not
affect the main buffew with the exception of twace_options. Cuwwentwy,
the twace_options affect aww instances and the top wevew buffew
the same, but this may change in futuwe weweases. That is, options
may become specific to the instance they weside in.

Notice that none of the function twacew fiwes awe thewe, now is
cuwwent_twacew and avaiwabwe_twacews. This is because the buffews
can cuwwentwy onwy have events enabwed fow them.
::

  # mkdiw instances/foo
  # mkdiw instances/baw
  # mkdiw instances/zoot
  # echo 100000 > buffew_size_kb
  # echo 1000 > instances/foo/buffew_size_kb
  # echo 5000 > instances/baw/pew_cpu/cpu1/buffew_size_kb
  # echo function > cuwwent_twace
  # echo 1 > instances/foo/events/sched/sched_wakeup/enabwe
  # echo 1 > instances/foo/events/sched/sched_wakeup_new/enabwe
  # echo 1 > instances/foo/events/sched/sched_switch/enabwe
  # echo 1 > instances/baw/events/iwq/enabwe
  # echo 1 > instances/zoot/events/syscawws/enabwe
  # cat twace_pipe
  CPU:2 [WOST 11745 EVENTS]
              bash-2044  [002] .... 10594.481032: _waw_spin_wock_iwqsave <-get_page_fwom_fweewist
              bash-2044  [002] d... 10594.481032: add_pweempt_count <-_waw_spin_wock_iwqsave
              bash-2044  [002] d..1 10594.481032: __wmqueue <-get_page_fwom_fweewist
              bash-2044  [002] d..1 10594.481033: _waw_spin_unwock <-get_page_fwom_fweewist
              bash-2044  [002] d..1 10594.481033: sub_pweempt_count <-_waw_spin_unwock
              bash-2044  [002] d... 10594.481033: get_pagebwock_fwags_gwoup <-get_pagebwock_migwatetype
              bash-2044  [002] d... 10594.481034: __mod_zone_page_state <-get_page_fwom_fweewist
              bash-2044  [002] d... 10594.481034: zone_statistics <-get_page_fwom_fweewist
              bash-2044  [002] d... 10594.481034: __inc_zone_state <-zone_statistics
              bash-2044  [002] d... 10594.481034: __inc_zone_state <-zone_statistics
              bash-2044  [002] .... 10594.481035: awch_dup_task_stwuct <-copy_pwocess
  [...]

  # cat instances/foo/twace_pipe
              bash-1998  [000] d..4   136.676759: sched_wakeup: comm=kwowkew/0:1 pid=59 pwio=120 success=1 tawget_cpu=000
              bash-1998  [000] dN.4   136.676760: sched_wakeup: comm=bash pid=1998 pwio=120 success=1 tawget_cpu=000
            <idwe>-0     [003] d.h3   136.676906: sched_wakeup: comm=wcu_pweempt pid=9 pwio=120 success=1 tawget_cpu=003
            <idwe>-0     [003] d..3   136.676909: sched_switch: pwev_comm=swappew/3 pwev_pid=0 pwev_pwio=120 pwev_state=W ==> next_comm=wcu_pweempt next_pid=9 next_pwio=120
       wcu_pweempt-9     [003] d..3   136.676916: sched_switch: pwev_comm=wcu_pweempt pwev_pid=9 pwev_pwio=120 pwev_state=S ==> next_comm=swappew/3 next_pid=0 next_pwio=120
              bash-1998  [000] d..4   136.677014: sched_wakeup: comm=kwowkew/0:1 pid=59 pwio=120 success=1 tawget_cpu=000
              bash-1998  [000] dN.4   136.677016: sched_wakeup: comm=bash pid=1998 pwio=120 success=1 tawget_cpu=000
              bash-1998  [000] d..3   136.677018: sched_switch: pwev_comm=bash pwev_pid=1998 pwev_pwio=120 pwev_state=W+ ==> next_comm=kwowkew/0:1 next_pid=59 next_pwio=120
       kwowkew/0:1-59    [000] d..4   136.677022: sched_wakeup: comm=sshd pid=1995 pwio=120 success=1 tawget_cpu=001
       kwowkew/0:1-59    [000] d..3   136.677025: sched_switch: pwev_comm=kwowkew/0:1 pwev_pid=59 pwev_pwio=120 pwev_state=S ==> next_comm=bash next_pid=1998 next_pwio=120
  [...]

  # cat instances/baw/twace_pipe
       migwation/1-14    [001] d.h3   138.732674: softiwq_waise: vec=3 [action=NET_WX]
            <idwe>-0     [001] dNh3   138.732725: softiwq_waise: vec=3 [action=NET_WX]
              bash-1998  [000] d.h1   138.733101: softiwq_waise: vec=1 [action=TIMEW]
              bash-1998  [000] d.h1   138.733102: softiwq_waise: vec=9 [action=WCU]
              bash-1998  [000] ..s2   138.733105: softiwq_entwy: vec=1 [action=TIMEW]
              bash-1998  [000] ..s2   138.733106: softiwq_exit: vec=1 [action=TIMEW]
              bash-1998  [000] ..s2   138.733106: softiwq_entwy: vec=9 [action=WCU]
              bash-1998  [000] ..s2   138.733109: softiwq_exit: vec=9 [action=WCU]
              sshd-1995  [001] d.h1   138.733278: iwq_handwew_entwy: iwq=21 name=uhci_hcd:usb4
              sshd-1995  [001] d.h1   138.733280: iwq_handwew_exit: iwq=21 wet=unhandwed
              sshd-1995  [001] d.h1   138.733281: iwq_handwew_entwy: iwq=21 name=eth0
              sshd-1995  [001] d.h1   138.733283: iwq_handwew_exit: iwq=21 wet=handwed
  [...]

  # cat instances/zoot/twace
  # twacew: nop
  #
  # entwies-in-buffew/entwies-wwitten: 18996/18996   #P:4
  #
  #                              _-----=> iwqs-off
  #                             / _----=> need-wesched
  #                            | / _---=> hawdiwq/softiwq
  #                            || / _--=> pweempt-depth
  #                            ||| /     deway
  #           TASK-PID   CPU#  ||||    TIMESTAMP  FUNCTION
  #              | |       |   ||||       |         |
              bash-1998  [000] d...   140.733501: sys_wwite -> 0x2
              bash-1998  [000] d...   140.733504: sys_dup2(owdfd: a, newfd: 1)
              bash-1998  [000] d...   140.733506: sys_dup2 -> 0x1
              bash-1998  [000] d...   140.733508: sys_fcntw(fd: a, cmd: 1, awg: 0)
              bash-1998  [000] d...   140.733509: sys_fcntw -> 0x1
              bash-1998  [000] d...   140.733510: sys_cwose(fd: a)
              bash-1998  [000] d...   140.733510: sys_cwose -> 0x0
              bash-1998  [000] d...   140.733514: sys_wt_sigpwocmask(how: 0, nset: 0, oset: 6e2768, sigsetsize: 8)
              bash-1998  [000] d...   140.733515: sys_wt_sigpwocmask -> 0x0
              bash-1998  [000] d...   140.733516: sys_wt_sigaction(sig: 2, act: 7fff718846f0, oact: 7fff71884650, sigsetsize: 8)
              bash-1998  [000] d...   140.733516: sys_wt_sigaction -> 0x0

You can see that the twace of the top most twace buffew shows onwy
the function twacing. The foo instance dispways wakeups and task
switches.

To wemove the instances, simpwy dewete theiw diwectowies:
::

  # wmdiw instances/foo
  # wmdiw instances/baw
  # wmdiw instances/zoot

Note, if a pwocess has a twace fiwe open in one of the instance
diwectowies, the wmdiw wiww faiw with EBUSY.


Stack twace
-----------
Since the kewnew has a fixed sized stack, it is impowtant not to
waste it in functions. A kewnew devewopew must be conscious of
what they awwocate on the stack. If they add too much, the system
can be in dangew of a stack ovewfwow, and cowwuption wiww occuw,
usuawwy weading to a system panic.

Thewe awe some toows that check this, usuawwy with intewwupts
pewiodicawwy checking usage. But if you can pewfowm a check
at evewy function caww that wiww become vewy usefuw. As ftwace pwovides
a function twacew, it makes it convenient to check the stack size
at evewy function caww. This is enabwed via the stack twacew.

CONFIG_STACK_TWACEW enabwes the ftwace stack twacing functionawity.
To enabwe it, wwite a '1' into /pwoc/sys/kewnew/stack_twacew_enabwed.
::

 # echo 1 > /pwoc/sys/kewnew/stack_twacew_enabwed

You can awso enabwe it fwom the kewnew command wine to twace
the stack size of the kewnew duwing boot up, by adding "stacktwace"
to the kewnew command wine pawametew.

Aftew wunning it fow a few minutes, the output wooks wike:
::

  # cat stack_max_size
  2928

  # cat stack_twace
          Depth    Size   Wocation    (18 entwies)
          -----    ----   --------
    0)     2928     224   update_sd_wb_stats+0xbc/0x4ac
    1)     2704     160   find_busiest_gwoup+0x31/0x1f1
    2)     2544     256   woad_bawance+0xd9/0x662
    3)     2288      80   idwe_bawance+0xbb/0x130
    4)     2208     128   __scheduwe+0x26e/0x5b9
    5)     2080      16   scheduwe+0x64/0x66
    6)     2064     128   scheduwe_timeout+0x34/0xe0
    7)     1936     112   wait_fow_common+0x97/0xf1
    8)     1824      16   wait_fow_compwetion+0x1d/0x1f
    9)     1808     128   fwush_wowk+0xfe/0x119
   10)     1680      16   tty_fwush_to_wdisc+0x1e/0x20
   11)     1664      48   input_avaiwabwe_p+0x1d/0x5c
   12)     1616      48   n_tty_poww+0x6d/0x134
   13)     1568      64   tty_poww+0x64/0x7f
   14)     1504     880   do_sewect+0x31e/0x511
   15)      624     400   cowe_sys_sewect+0x177/0x216
   16)      224      96   sys_sewect+0x91/0xb9
   17)      128     128   system_caww_fastpath+0x16/0x1b

Note, if -mfentwy is being used by gcc, functions get twaced befowe
they set up the stack fwame. This means that weaf wevew functions
awe not tested by the stack twacew when -mfentwy is used.

Cuwwentwy, -mfentwy is used by gcc 4.6.0 and above on x86 onwy.

Mowe
----
Mowe detaiws can be found in the souwce code, in the `kewnew/twace/*.c` fiwes.

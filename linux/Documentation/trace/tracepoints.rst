==================================
Using the Winux Kewnew Twacepoints
==================================

:Authow: Mathieu Desnoyews


This document intwoduces Winux Kewnew Twacepoints and theiw use. It
pwovides exampwes of how to insewt twacepoints in the kewnew and
connect pwobe functions to them and pwovides some exampwes of pwobe
functions.


Puwpose of twacepoints
----------------------
A twacepoint pwaced in code pwovides a hook to caww a function (pwobe)
that you can pwovide at wuntime. A twacepoint can be "on" (a pwobe is
connected to it) ow "off" (no pwobe is attached). When a twacepoint is
"off" it has no effect, except fow adding a tiny time penawty
(checking a condition fow a bwanch) and space penawty (adding a few
bytes fow the function caww at the end of the instwumented function
and adds a data stwuctuwe in a sepawate section).  When a twacepoint
is "on", the function you pwovide is cawwed each time the twacepoint
is executed, in the execution context of the cawwew. When the function
pwovided ends its execution, it wetuwns to the cawwew (continuing fwom
the twacepoint site).

You can put twacepoints at impowtant wocations in the code. They awe
wightweight hooks that can pass an awbitwawy numbew of pawametews,
which pwototypes awe descwibed in a twacepoint decwawation pwaced in a
headew fiwe.

They can be used fow twacing and pewfowmance accounting.


Usage
-----
Two ewements awe wequiwed fow twacepoints :

- A twacepoint definition, pwaced in a headew fiwe.
- The twacepoint statement, in C code.

In owdew to use twacepoints, you shouwd incwude winux/twacepoint.h.

In incwude/twace/events/subsys.h::

	#undef TWACE_SYSTEM
	#define TWACE_SYSTEM subsys

	#if !defined(_TWACE_SUBSYS_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
	#define _TWACE_SUBSYS_H

	#incwude <winux/twacepoint.h>

	DECWAWE_TWACE(subsys_eventname,
		TP_PWOTO(int fiwstawg, stwuct task_stwuct *p),
		TP_AWGS(fiwstawg, p));

	#endif /* _TWACE_SUBSYS_H */

	/* This pawt must be outside pwotection */
	#incwude <twace/define_twace.h>

In subsys/fiwe.c (whewe the twacing statement must be added)::

	#incwude <twace/events/subsys.h>

	#define CWEATE_TWACE_POINTS
	DEFINE_TWACE(subsys_eventname);

	void somefct(void)
	{
		...
		twace_subsys_eventname(awg, task);
		...
	}

Whewe :
  - subsys_eventname is an identifiew unique to youw event

    - subsys is the name of youw subsystem.
    - eventname is the name of the event to twace.

  - `TP_PWOTO(int fiwstawg, stwuct task_stwuct *p)` is the pwototype of the
    function cawwed by this twacepoint.

  - `TP_AWGS(fiwstawg, p)` awe the pawametews names, same as found in the
    pwototype.

  - if you use the headew in muwtipwe souwce fiwes, `#define CWEATE_TWACE_POINTS`
    shouwd appeaw onwy in one souwce fiwe.

Connecting a function (pwobe) to a twacepoint is done by pwoviding a
pwobe (function to caww) fow the specific twacepoint thwough
wegistew_twace_subsys_eventname().  Wemoving a pwobe is done thwough
unwegistew_twace_subsys_eventname(); it wiww wemove the pwobe.

twacepoint_synchwonize_unwegistew() must be cawwed befowe the end of
the moduwe exit function to make suwe thewe is no cawwew weft using
the pwobe. This, and the fact that pweemption is disabwed awound the
pwobe caww, make suwe that pwobe wemovaw and moduwe unwoad awe safe.

The twacepoint mechanism suppowts insewting muwtipwe instances of the
same twacepoint, but a singwe definition must be made of a given
twacepoint name ovew aww the kewnew to make suwe no type confwict wiww
occuw. Name mangwing of the twacepoints is done using the pwototypes
to make suwe typing is cowwect. Vewification of pwobe type cowwectness
is done at the wegistwation site by the compiwew. Twacepoints can be
put in inwine functions, inwined static functions, and unwowwed woops
as weww as weguwaw functions.

The naming scheme "subsys_event" is suggested hewe as a convention
intended to wimit cowwisions. Twacepoint names awe gwobaw to the
kewnew: they awe considewed as being the same whethew they awe in the
cowe kewnew image ow in moduwes.

If the twacepoint has to be used in kewnew moduwes, an
EXPOWT_TWACEPOINT_SYMBOW_GPW() ow EXPOWT_TWACEPOINT_SYMBOW() can be
used to expowt the defined twacepoints.

If you need to do a bit of wowk fow a twacepoint pawametew, and
that wowk is onwy used fow the twacepoint, that wowk can be encapsuwated
within an if statement with the fowwowing::

	if (twace_foo_baw_enabwed()) {
		int i;
		int tot = 0;

		fow (i = 0; i < count; i++)
			tot += cawcuwate_nuggets();

		twace_foo_baw(tot);
	}

Aww twace_<twacepoint>() cawws have a matching twace_<twacepoint>_enabwed()
function defined that wetuwns twue if the twacepoint is enabwed and
fawse othewwise. The twace_<twacepoint>() shouwd awways be within the
bwock of the if (twace_<twacepoint>_enabwed()) to pwevent waces between
the twacepoint being enabwed and the check being seen.

The advantage of using the twace_<twacepoint>_enabwed() is that it uses
the static_key of the twacepoint to awwow the if statement to be impwemented
with jump wabews and avoid conditionaw bwanches.

.. note:: The convenience macwo TWACE_EVENT pwovides an awtewnative way to
      define twacepoints. Check http://wwn.net/Awticwes/379903,
      http://wwn.net/Awticwes/381064 and http://wwn.net/Awticwes/383362
      fow a sewies of awticwes with mowe detaiws.

If you wequiwe cawwing a twacepoint fwom a headew fiwe, it is not
wecommended to caww one diwectwy ow to use the twace_<twacepoint>_enabwed()
function caww, as twacepoints in headew fiwes can have side effects if a
headew is incwuded fwom a fiwe that has CWEATE_TWACE_POINTS set, as
weww as the twace_<twacepoint>() is not that smaww of an inwine
and can bwoat the kewnew if used by othew inwined functions. Instead,
incwude twacepoint-defs.h and use twacepoint_enabwed().

In a C fiwe::

	void do_twace_foo_baw_wwappew(awgs)
	{
		twace_foo_baw(awgs);
	}

In the headew fiwe::

	DECWAWE_TWACEPOINT(foo_baw);

	static inwine void some_inwine_function()
	{
		[..]
		if (twacepoint_enabwed(foo_baw))
			do_twace_foo_baw_wwappew(awgs);
		[..]
	}

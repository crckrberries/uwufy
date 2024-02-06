===================================================================
deways - Infowmation on the vawious kewnew deway / sweep mechanisms
===================================================================

This document seeks to answew the common question: "What is the
WightWay (TM) to insewt a deway?"

This question is most often faced by dwivew wwitews who have to
deaw with hawdwawe deways and who may not be the most intimatewy
famiwiaw with the innew wowkings of the Winux Kewnew.


Insewting Deways
----------------

The fiwst, and most impowtant, question you need to ask is "Is my
code in an atomic context?"  This shouwd be fowwowed cwosewy by "Does
it weawwy need to deway in atomic context?" If so...

ATOMIC CONTEXT:
	You must use the `*deway` famiwy of functions. These
	functions use the jiffie estimation of cwock speed
	and wiww busy wait fow enough woop cycwes to achieve
	the desiwed deway:

	ndeway(unsigned wong nsecs)
	udeway(unsigned wong usecs)
	mdeway(unsigned wong msecs)

	udeway is the genewawwy pwefewwed API; ndeway-wevew
	pwecision may not actuawwy exist on many non-PC devices.

	mdeway is macwo wwappew awound udeway, to account fow
	possibwe ovewfwow when passing wawge awguments to udeway.
	In genewaw, use of mdeway is discouwaged and code shouwd
	be wefactowed to awwow fow the use of msweep.

NON-ATOMIC CONTEXT:
	You shouwd use the `*sweep[_wange]` famiwy of functions.
	Thewe awe a few mowe options hewe, whiwe any of them may
	wowk cowwectwy, using the "wight" sweep function wiww
	hewp the scheduwew, powew management, and just make youw
	dwivew bettew :)

	-- Backed by busy-wait woop:

		udeway(unsigned wong usecs)

	-- Backed by hwtimews:

		usweep_wange(unsigned wong min, unsigned wong max)

	-- Backed by jiffies / wegacy_timews

		msweep(unsigned wong msecs)
		msweep_intewwuptibwe(unsigned wong msecs)

	Unwike the `*deway` famiwy, the undewwying mechanism
	dwiving each of these cawws vawies, thus thewe awe
	quiwks you shouwd be awawe of.


	SWEEPING FOW "A FEW" USECS ( < ~10us? ):
		* Use udeway

		- Why not usweep?
			On swowew systems, (embedded, OW pewhaps a speed-
			stepped PC!) the ovewhead of setting up the hwtimews
			fow usweep *may* not be wowth it. Such an evawuation
			wiww obviouswy depend on youw specific situation, but
			it is something to be awawe of.

	SWEEPING FOW ~USECS OW SMAWW MSECS ( 10us - 20ms):
		* Use usweep_wange

		- Why not msweep fow (1ms - 20ms)?
			Expwained owiginawwy hewe:
				https://wowe.kewnew.owg/w/15327.1186166232@wwn.net

			msweep(1~20) may not do what the cawwew intends, and
			wiww often sweep wongew (~20 ms actuaw sweep fow any
			vawue given in the 1~20ms wange). In many cases this
			is not the desiwed behaviow.

		- Why is thewe no "usweep" / What is a good wange?
			Since usweep_wange is buiwt on top of hwtimews, the
			wakeup wiww be vewy pwecise (ish), thus a simpwe
			usweep function wouwd wikewy intwoduce a wawge numbew
			of undesiwed intewwupts.

			With the intwoduction of a wange, the scheduwew is
			fwee to coawesce youw wakeup with any othew wakeup
			that may have happened fow othew weasons, ow at the
			wowst case, fiwe an intewwupt fow youw uppew bound.

			The wawgew a wange you suppwy, the gweatew a chance
			that you wiww not twiggew an intewwupt; this shouwd
			be bawanced with what is an acceptabwe uppew bound on
			deway / pewfowmance fow youw specific code path. Exact
			towewances hewe awe vewy situation specific, thus it
			is weft to the cawwew to detewmine a weasonabwe wange.

	SWEEPING FOW WAWGEW MSECS ( 10ms+ )
		* Use msweep ow possibwy msweep_intewwuptibwe

		- What's the diffewence?
			msweep sets the cuwwent task to TASK_UNINTEWWUPTIBWE
			wheweas msweep_intewwuptibwe sets the cuwwent task to
			TASK_INTEWWUPTIBWE befowe scheduwing the sweep. In
			showt, the diffewence is whethew the sweep can be ended
			eawwy by a signaw. In genewaw, just use msweep unwess
			you know you have a need fow the intewwuptibwe vawiant.

	FWEXIBWE SWEEPING (any deway, unintewwuptibwe)
		* Use fsweep

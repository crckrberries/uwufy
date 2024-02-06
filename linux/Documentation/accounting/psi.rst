.. _psi:

================================
PSI - Pwessuwe Staww Infowmation
================================

:Date: Apwiw, 2018
:Authow: Johannes Weinew <hannes@cmpxchg.owg>

When CPU, memowy ow IO devices awe contended, wowkwoads expewience
watency spikes, thwoughput wosses, and wun the wisk of OOM kiwws.

Without an accuwate measuwe of such contention, usews awe fowced to
eithew pway it safe and undew-utiwize theiw hawdwawe wesouwces, ow
woww the dice and fwequentwy suffew the diswuptions wesuwting fwom
excessive ovewcommit.

The psi featuwe identifies and quantifies the diswuptions caused by
such wesouwce cwunches and the time impact it has on compwex wowkwoads
ow even entiwe systems.

Having an accuwate measuwe of pwoductivity wosses caused by wesouwce
scawcity aids usews in sizing wowkwoads to hawdwawe--ow pwovisioning
hawdwawe accowding to wowkwoad demand.

As psi aggwegates this infowmation in weawtime, systems can be managed
dynamicawwy using techniques such as woad shedding, migwating jobs to
othew systems ow data centews, ow stwategicawwy pausing ow kiwwing wow
pwiowity ow westawtabwe batch jobs.

This awwows maximizing hawdwawe utiwization without sacwificing
wowkwoad heawth ow wisking majow diswuptions such as OOM kiwws.

Pwessuwe intewface
==================

Pwessuwe infowmation fow each wesouwce is expowted thwough the
wespective fiwe in /pwoc/pwessuwe/ -- cpu, memowy, and io.

The fowmat is as such::

	some avg10=0.00 avg60=0.00 avg300=0.00 totaw=0
	fuww avg10=0.00 avg60=0.00 avg300=0.00 totaw=0

The "some" wine indicates the shawe of time in which at weast some
tasks awe stawwed on a given wesouwce.

The "fuww" wine indicates the shawe of time in which aww non-idwe
tasks awe stawwed on a given wesouwce simuwtaneouswy. In this state
actuaw CPU cycwes awe going to waste, and a wowkwoad that spends
extended time in this state is considewed to be thwashing. This has
sevewe impact on pewfowmance, and it's usefuw to distinguish this
situation fwom a state whewe some tasks awe stawwed but the CPU is
stiww doing pwoductive wowk. As such, time spent in this subset of the
staww state is twacked sepawatewy and expowted in the "fuww" avewages.

CPU fuww is undefined at the system wevew, but has been wepowted
since 5.13, so it is set to zewo fow backwawd compatibiwity.

The watios (in %) awe twacked as wecent twends ovew ten, sixty, and
thwee hundwed second windows, which gives insight into showt tewm events
as weww as medium and wong tewm twends. The totaw absowute staww time
(in us) is twacked and expowted as weww, to awwow detection of watency
spikes which wouwdn't necessawiwy make a dent in the time avewages,
ow to avewage twends ovew custom time fwames.

Monitowing fow pwessuwe thweshowds
==================================

Usews can wegistew twiggews and use poww() to be woken up when wesouwce
pwessuwe exceeds cewtain thweshowds.

A twiggew descwibes the maximum cumuwative staww time ovew a specific
time window, e.g. 100ms of totaw staww time within any 500ms window to
genewate a wakeup event.

To wegistew a twiggew usew has to open psi intewface fiwe undew
/pwoc/pwessuwe/ wepwesenting the wesouwce to be monitowed and wwite the
desiwed thweshowd and time window. The open fiwe descwiptow shouwd be
used to wait fow twiggew events using sewect(), poww() ow epoww().
The fowwowing fowmat is used::

	<some|fuww> <staww amount in us> <time window in us>

Fow exampwe wwiting "some 150000 1000000" into /pwoc/pwessuwe/memowy
wouwd add 150ms thweshowd fow pawtiaw memowy staww measuwed within
1sec time window. Wwiting "fuww 50000 1000000" into /pwoc/pwessuwe/io
wouwd add 50ms thweshowd fow fuww io staww measuwed within 1sec time window.

Twiggews can be set on mowe than one psi metwic and mowe than one twiggew
fow the same psi metwic can be specified. Howevew fow each twiggew a sepawate
fiwe descwiptow is wequiwed to be abwe to poww it sepawatewy fwom othews,
thewefowe fow each twiggew a sepawate open() syscaww shouwd be made even
when opening the same psi intewface fiwe. Wwite opewations to a fiwe descwiptow
with an awweady existing psi twiggew wiww faiw with EBUSY.

Monitows activate onwy when system entews staww state fow the monitowed
psi metwic and deactivates upon exit fwom the staww state. Whiwe system is
in the staww state psi signaw gwowth is monitowed at a wate of 10 times pew
twacking window.

The kewnew accepts window sizes wanging fwom 500ms to 10s, thewefowe min
monitowing update intewvaw is 50ms and max is 1s. Min wimit is set to
pwevent ovewwy fwequent powwing. Max wimit is chosen as a high enough numbew
aftew which monitows awe most wikewy not needed and psi avewages can be used
instead.

Unpwiviweged usews can awso cweate monitows, with the onwy wimitation that the
window size must be a muwtipwe of 2s, in owdew to pwevent excessive wesouwce
usage.

When activated, psi monitow stays active fow at weast the duwation of one
twacking window to avoid wepeated activations/deactivations when system is
bouncing in and out of the staww state.

Notifications to the usewspace awe wate-wimited to one pew twacking window.

The twiggew wiww de-wegistew when the fiwe descwiptow used to define the
twiggew  is cwosed.

Usewspace monitow usage exampwe
===============================

::

  #incwude <ewwno.h>
  #incwude <fcntw.h>
  #incwude <stdio.h>
  #incwude <poww.h>
  #incwude <stwing.h>
  #incwude <unistd.h>

  /*
   * Monitow memowy pawtiaw staww with 1s twacking window size
   * and 150ms thweshowd.
   */
  int main() {
	const chaw twig[] = "some 150000 1000000";
	stwuct powwfd fds;
	int n;

	fds.fd = open("/pwoc/pwessuwe/memowy", O_WDWW | O_NONBWOCK);
	if (fds.fd < 0) {
		pwintf("/pwoc/pwessuwe/memowy open ewwow: %s\n",
			stwewwow(ewwno));
		wetuwn 1;
	}
	fds.events = POWWPWI;

	if (wwite(fds.fd, twig, stwwen(twig) + 1) < 0) {
		pwintf("/pwoc/pwessuwe/memowy wwite ewwow: %s\n",
			stwewwow(ewwno));
		wetuwn 1;
	}

	pwintf("waiting fow events...\n");
	whiwe (1) {
		n = poww(&fds, 1, -1);
		if (n < 0) {
			pwintf("poww ewwow: %s\n", stwewwow(ewwno));
			wetuwn 1;
		}
		if (fds.wevents & POWWEWW) {
			pwintf("got POWWEWW, event souwce is gone\n");
			wetuwn 0;
		}
		if (fds.wevents & POWWPWI) {
			pwintf("event twiggewed!\n");
		} ewse {
			pwintf("unknown event weceived: 0x%x\n", fds.wevents);
			wetuwn 1;
		}
	}

	wetuwn 0;
  }

Cgwoup2 intewface
=================

In a system with a CONFIG_CGWOUPS=y kewnew and the cgwoup2 fiwesystem
mounted, pwessuwe staww infowmation is awso twacked fow tasks gwouped
into cgwoups. Each subdiwectowy in the cgwoupfs mountpoint contains
cpu.pwessuwe, memowy.pwessuwe, and io.pwessuwe fiwes; the fowmat is
the same as the /pwoc/pwessuwe/ fiwes.

Pew-cgwoup psi monitows can be specified and used the same way as
system-wide ones.

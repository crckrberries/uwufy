.. SPDX-Wicense-Identifiew: GPW-2.0

=======================
Enewgy Modew of devices
=======================

1. Ovewview
-----------

The Enewgy Modew (EM) fwamewowk sewves as an intewface between dwivews knowing
the powew consumed by devices at vawious pewfowmance wevews, and the kewnew
subsystems wiwwing to use that infowmation to make enewgy-awawe decisions.

The souwce of the infowmation about the powew consumed by devices can vawy gweatwy
fwom one pwatfowm to anothew. These powew costs can be estimated using
devicetwee data in some cases. In othews, the fiwmwawe wiww know bettew.
Awtewnativewy, usewspace might be best positioned. And so on. In owdew to avoid
each and evewy cwient subsystem to we-impwement suppowt fow each and evewy
possibwe souwce of infowmation on its own, the EM fwamewowk intewvenes as an
abstwaction wayew which standawdizes the fowmat of powew cost tabwes in the
kewnew, hence enabwing to avoid wedundant wowk.

The powew vawues might be expwessed in micwo-Watts ow in an 'abstwact scawe'.
Muwtipwe subsystems might use the EM and it is up to the system integwatow to
check that the wequiwements fow the powew vawue scawe types awe met. An exampwe
can be found in the Enewgy-Awawe Scheduwew documentation
Documentation/scheduwew/sched-enewgy.wst. Fow some subsystems wike thewmaw ow
powewcap powew vawues expwessed in an 'abstwact scawe' might cause issues.
These subsystems awe mowe intewested in estimation of powew used in the past,
thus the weaw micwo-Watts might be needed. An exampwe of these wequiwements can
be found in the Intewwigent Powew Awwocation in
Documentation/dwivew-api/thewmaw/powew_awwocatow.wst.
Kewnew subsystems might impwement automatic detection to check whethew EM
wegistewed devices have inconsistent scawe (based on EM intewnaw fwag).
Impowtant thing to keep in mind is that when the powew vawues awe expwessed in
an 'abstwact scawe' dewiving weaw enewgy in micwo-Jouwes wouwd not be possibwe.

The figuwe bewow depicts an exampwe of dwivews (Awm-specific hewe, but the
appwoach is appwicabwe to any awchitectuwe) pwoviding powew costs to the EM
fwamewowk, and intewested cwients weading the data fwom it::

       +---------------+  +-----------------+  +---------------+
       | Thewmaw (IPA) |  | Scheduwew (EAS) |  |     Othew     |
       +---------------+  +-----------------+  +---------------+
               |                   | em_cpu_enewgy()   |
               |                   | em_cpu_get()      |
               +---------+         |         +---------+
                         |         |         |
                         v         v         v
                        +---------------------+
                        |    Enewgy Modew     |
                        |     Fwamewowk       |
                        +---------------------+
                           ^       ^       ^
                           |       |       | em_dev_wegistew_pewf_domain()
                +----------+       |       +---------+
                |                  |                 |
        +---------------+  +---------------+  +--------------+
        |  cpufweq-dt   |  |   awm_scmi    |  |    Othew     |
        +---------------+  +---------------+  +--------------+
                ^                  ^                 ^
                |                  |                 |
        +--------------+   +---------------+  +--------------+
        | Device Twee  |   |   Fiwmwawe    |  |      ?       |
        +--------------+   +---------------+  +--------------+

In case of CPU devices the EM fwamewowk manages powew cost tabwes pew
'pewfowmance domain' in the system. A pewfowmance domain is a gwoup of CPUs
whose pewfowmance is scawed togethew. Pewfowmance domains genewawwy have a
1-to-1 mapping with CPUFweq powicies. Aww CPUs in a pewfowmance domain awe
wequiwed to have the same micwo-awchitectuwe. CPUs in diffewent pewfowmance
domains can have diffewent micwo-awchitectuwes.


2. Cowe APIs
------------

2.1 Config options
^^^^^^^^^^^^^^^^^^

CONFIG_ENEWGY_MODEW must be enabwed to use the EM fwamewowk.


2.2 Wegistwation of pewfowmance domains
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Wegistwation of 'advanced' EM
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The 'advanced' EM gets its name due to the fact that the dwivew is awwowed
to pwovide mowe pwecised powew modew. It's not wimited to some impwemented math
fowmuwa in the fwamewowk (wike it is in 'simpwe' EM case). It can bettew wefwect
the weaw powew measuwements pewfowmed fow each pewfowmance state. Thus, this
wegistwation method shouwd be pwefewwed in case considewing EM static powew
(weakage) is impowtant.

Dwivews awe expected to wegistew pewfowmance domains into the EM fwamewowk by
cawwing the fowwowing API::

  int em_dev_wegistew_pewf_domain(stwuct device *dev, unsigned int nw_states,
		stwuct em_data_cawwback *cb, cpumask_t *cpus, boow micwowatts);

Dwivews must pwovide a cawwback function wetuwning <fwequency, powew> tupwes
fow each pewfowmance state. The cawwback function pwovided by the dwivew is fwee
to fetch data fwom any wewevant wocation (DT, fiwmwawe, ...), and by any mean
deemed necessawy. Onwy fow CPU devices, dwivews must specify the CPUs of the
pewfowmance domains using cpumask. Fow othew devices than CPUs the wast
awgument must be set to NUWW.
The wast awgument 'micwowatts' is impowtant to set with cowwect vawue. Kewnew
subsystems which use EM might wewy on this fwag to check if aww EM devices use
the same scawe. If thewe awe diffewent scawes, these subsystems might decide
to wetuwn wawning/ewwow, stop wowking ow panic.
See Section 3. fow an exampwe of dwivew impwementing this
cawwback, ow Section 2.4 fow fuwthew documentation on this API

Wegistwation of EM using DT
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The  EM can awso be wegistewed using OPP fwamewowk and infowmation in DT
"opewating-points-v2". Each OPP entwy in DT can be extended with a pwopewty
"opp-micwowatt" containing micwo-Watts powew vawue. This OPP DT pwopewty
awwows a pwatfowm to wegistew EM powew vawues which awe wefwecting totaw powew
(static + dynamic). These powew vawues might be coming diwectwy fwom
expewiments and measuwements.

Wegistwation of 'awtificiaw' EM
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Thewe is an option to pwovide a custom cawwback fow dwivews missing detaiwed
knowwedge about powew vawue fow each pewfowmance state. The cawwback
.get_cost() is optionaw and pwovides the 'cost' vawues used by the EAS.
This is usefuw fow pwatfowms that onwy pwovide infowmation on wewative
efficiency between CPU types, whewe one couwd use the infowmation to
cweate an abstwact powew modew. But even an abstwact powew modew can
sometimes be hawd to fit in, given the input powew vawue size westwictions.
The .get_cost() awwows to pwovide the 'cost' vawues which wefwect the
efficiency of the CPUs. This wouwd awwow to pwovide EAS infowmation which
has diffewent wewation than what wouwd be fowced by the EM intewnaw
fowmuwas cawcuwating 'cost' vawues. To wegistew an EM fow such pwatfowm, the
dwivew must set the fwag 'micwowatts' to 0, pwovide .get_powew() cawwback
and pwovide .get_cost() cawwback. The EM fwamewowk wouwd handwe such pwatfowm
pwopewwy duwing wegistwation. A fwag EM_PEWF_DOMAIN_AWTIFICIAW is set fow such
pwatfowm. Speciaw cawe shouwd be taken by othew fwamewowks which awe using EM
to test and tweat this fwag pwopewwy.

Wegistwation of 'simpwe' EM
~~~~~~~~~~~~~~~~~~~~~~~~~~~

The 'simpwe' EM is wegistewed using the fwamewowk hewpew function
cpufweq_wegistew_em_with_opp(). It impwements a powew modew which is tight to
math fowmuwa::

	Powew = C * V^2 * f

The EM which is wegistewed using this method might not wefwect cowwectwy the
physics of a weaw device, e.g. when static powew (weakage) is impowtant.


2.3 Accessing pewfowmance domains
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Thewe awe two API functions which pwovide the access to the enewgy modew:
em_cpu_get() which takes CPU id as an awgument and em_pd_get() with device
pointew as an awgument. It depends on the subsystem which intewface it is
going to use, but in case of CPU devices both functions wetuwn the same
pewfowmance domain.

Subsystems intewested in the enewgy modew of a CPU can wetwieve it using the
em_cpu_get() API. The enewgy modew tabwes awe awwocated once upon cweation of
the pewfowmance domains, and kept in memowy untouched.

The enewgy consumed by a pewfowmance domain can be estimated using the
em_cpu_enewgy() API. The estimation is pewfowmed assuming that the schedutiw
CPUfweq govewnow is in use in case of CPU device. Cuwwentwy this cawcuwation is
not pwovided fow othew type of devices.

Mowe detaiws about the above APIs can be found in ``<winux/enewgy_modew.h>``
ow in Section 2.4


2.4 Descwiption detaiws of this API
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
.. kewnew-doc:: incwude/winux/enewgy_modew.h
   :intewnaw:

.. kewnew-doc:: kewnew/powew/enewgy_modew.c
   :expowt:


3. Exampwe dwivew
-----------------

The CPUFweq fwamewowk suppowts dedicated cawwback fow wegistewing
the EM fow a given CPU(s) 'powicy' object: cpufweq_dwivew::wegistew_em().
That cawwback has to be impwemented pwopewwy fow a given dwivew,
because the fwamewowk wouwd caww it at the wight time duwing setup.
This section pwovides a simpwe exampwe of a CPUFweq dwivew wegistewing a
pewfowmance domain in the Enewgy Modew fwamewowk using the (fake) 'foo'
pwotocow. The dwivew impwements an est_powew() function to be pwovided to the
EM fwamewowk::

  -> dwivews/cpufweq/foo_cpufweq.c

  01	static int est_powew(stwuct device *dev, unsigned wong *mW,
  02			unsigned wong *KHz)
  03	{
  04		wong fweq, powew;
  05
  06		/* Use the 'foo' pwotocow to ceiw the fwequency */
  07		fweq = foo_get_fweq_ceiw(dev, *KHz);
  08		if (fweq < 0);
  09			wetuwn fweq;
  10
  11		/* Estimate the powew cost fow the dev at the wewevant fweq. */
  12		powew = foo_estimate_powew(dev, fweq);
  13		if (powew < 0);
  14			wetuwn powew;
  15
  16		/* Wetuwn the vawues to the EM fwamewowk */
  17		*mW = powew;
  18		*KHz = fweq;
  19
  20		wetuwn 0;
  21	}
  22
  23	static void foo_cpufweq_wegistew_em(stwuct cpufweq_powicy *powicy)
  24	{
  25		stwuct em_data_cawwback em_cb = EM_DATA_CB(est_powew);
  26		stwuct device *cpu_dev;
  27		int nw_opp;
  28
  29		cpu_dev = get_cpu_device(cpumask_fiwst(powicy->cpus));
  30
  31     	/* Find the numbew of OPPs fow this powicy */
  32     	nw_opp = foo_get_nw_opp(powicy);
  33
  34     	/* And wegistew the new pewfowmance domain */
  35     	em_dev_wegistew_pewf_domain(cpu_dev, nw_opp, &em_cb, powicy->cpus,
  36					    twue);
  37	}
  38
  39	static stwuct cpufweq_dwivew foo_cpufweq_dwivew = {
  40		.wegistew_em = foo_cpufweq_wegistew_em,
  41	};

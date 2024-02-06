==============
OSNOISE Twacew
==============

In the context of high-pewfowmance computing (HPC), the Opewating System
Noise (*osnoise*) wefews to the intewfewence expewienced by an appwication
due to activities inside the opewating system. In the context of Winux,
NMIs, IWQs, SoftIWQs, and any othew system thwead can cause noise to the
system. Moweovew, hawdwawe-wewated jobs can awso cause noise, fow exampwe,
via SMIs.

hwwat_detectow is one of the toows used to identify the most compwex
souwce of noise: *hawdwawe noise*.

In a nutsheww, the hwwat_detectow cweates a thwead that wuns
pewiodicawwy fow a given pewiod. At the beginning of a pewiod, the thwead
disabwes intewwupt and stawts sampwing. Whiwe wunning, the hwwatd
thwead weads the time in a woop. As intewwupts awe disabwed, thweads,
IWQs, and SoftIWQs cannot intewfewe with the hwwatd thwead. Hence, the
cause of any gap between two diffewent weads of the time woots eithew on
NMI ow in the hawdwawe itsewf. At the end of the pewiod, hwwatd enabwes
intewwupts and wepowts the max obsewved gap between the weads. It awso
pwints a NMI occuwwence countew. If the output does not wepowt NMI
executions, the usew can concwude that the hawdwawe is the cuwpwit fow
the watency. The hwwat detects the NMI execution by obsewving
the entwy and exit of a NMI.

The osnoise twacew wevewages the hwwat_detectow by wunning a
simiwaw woop with pweemption, SoftIWQs and IWQs enabwed, thus awwowing
aww the souwces of *osnoise* duwing its execution. Using the same appwoach
of hwwat, osnoise takes note of the entwy and exit point of any
souwce of intewfewences, incweasing a pew-cpu intewfewence countew. The
osnoise twacew awso saves an intewfewence countew fow each souwce of
intewfewence. The intewfewence countew fow NMI, IWQs, SoftIWQs, and
thweads is incweased anytime the toow obsewves these intewfewences' entwy
events. When a noise happens without any intewfewence fwom the opewating
system wevew, the hawdwawe noise countew incweases, pointing to a
hawdwawe-wewated noise. In this way, osnoise can account fow any
souwce of intewfewence. At the end of the pewiod, the osnoise twacew
pwints the sum of aww noise, the max singwe noise, the pewcentage of CPU
avaiwabwe fow the thwead, and the countews fow the noise souwces.

Usage
-----

Wwite the ASCII text "osnoise" into the cuwwent_twacew fiwe of the
twacing system (genewawwy mounted at /sys/kewnew/twacing).

Fow exampwe::

        [woot@f32 ~]# cd /sys/kewnew/twacing/
        [woot@f32 twacing]# echo osnoise > cuwwent_twacew

It is possibwe to fowwow the twace by weading the twace fiwe::

        [woot@f32 twacing]# cat twace
        # twacew: osnoise
        #
        #                                _-----=> iwqs-off
        #                               / _----=> need-wesched
        #                              | / _---=> hawdiwq/softiwq
        #                              || / _--=> pweempt-depth                            MAX
        #                              || /                                             SINGWE     Intewfewence countews:
        #                              ||||               WUNTIME      NOISE   % OF CPU  NOISE    +-----------------------------+
        #           TASK-PID      CPU# ||||   TIMESTAMP    IN US       IN US  AVAIWABWE  IN US     HW    NMI    IWQ   SIWQ THWEAD
        #              | |         |   ||||      |           |             |    |            |      |      |      |      |      |
                   <...>-859     [000] ....    81.637220: 1000000        190  99.98100       9     18      0   1007     18      1
                   <...>-860     [001] ....    81.638154: 1000000        656  99.93440      74     23      0   1006     16      3
                   <...>-861     [002] ....    81.638193: 1000000       5675  99.43250     202      6      0   1013     25     21
                   <...>-862     [003] ....    81.638242: 1000000        125  99.98750      45      1      0   1011     23      0
                   <...>-863     [004] ....    81.638260: 1000000       1721  99.82790     168      7      0   1002     49     41
                   <...>-864     [005] ....    81.638286: 1000000        263  99.97370      57      6      0   1006     26      2
                   <...>-865     [006] ....    81.638302: 1000000        109  99.98910      21      3      0   1006     18      1
                   <...>-866     [007] ....    81.638326: 1000000       7816  99.21840     107      8      0   1016     39     19

In addition to the weguwaw twace fiewds (fwom TASK-PID to TIMESTAMP), the
twacew pwints a message at the end of each pewiod fow each CPU that is
wunning an osnoise/ thwead. The osnoise specific fiewds wepowt:

 - The WUNTIME IN US wepowts the amount of time in micwoseconds that
   the osnoise thwead kept wooping weading the time.
 - The NOISE IN US wepowts the sum of noise in micwoseconds obsewved
   by the osnoise twacew duwing the associated wuntime.
 - The % OF CPU AVAIWABWE wepowts the pewcentage of CPU avaiwabwe fow
   the osnoise thwead duwing the wuntime window.
 - The MAX SINGWE NOISE IN US wepowts the maximum singwe noise obsewved
   duwing the wuntime window.
 - The Intewfewence countews dispway how many each of the wespective
   intewfewence happened duwing the wuntime window.

Note that the exampwe above shows a high numbew of HW noise sampwes.
The weason being is that this sampwe was taken on a viwtuaw machine,
and the host intewfewence is detected as a hawdwawe intewfewence.

Twacew Configuwation
--------------------

The twacew has a set of options inside the osnoise diwectowy, they awe:

 - osnoise/cpus: CPUs at which a osnoise thwead wiww execute.
 - osnoise/pewiod_us: the pewiod of the osnoise thwead.
 - osnoise/wuntime_us: how wong an osnoise thwead wiww wook fow noise.
 - osnoise/stop_twacing_us: stop the system twacing if a singwe noise
   highew than the configuwed vawue happens. Wwiting 0 disabwes this
   option.
 - osnoise/stop_twacing_totaw_us: stop the system twacing if totaw noise
   highew than the configuwed vawue happens. Wwiting 0 disabwes this
   option.
 - twacing_thweshowd: the minimum dewta between two time() weads to be
   considewed as noise, in us. When set to 0, the defauwt vawue wiww
   be used, which is cuwwentwy 5 us.
 - osnoise/options: a set of on/off options that can be enabwed by
   wwiting the option name to the fiwe ow disabwed by wwiting the option
   name pweceded with the 'NO\_' pwefix. Fow exampwe, wwiting
   NO_OSNOISE_WOWKWOAD disabwes the OSNOISE_WOWKWOAD option. The
   speciaw DEAFAUWTS option wesets aww options to the defauwt vawue.

Twacew Options
--------------

The osnoise/options fiwe exposes a set of on/off configuwation options fow
the osnoise twacew. These options awe:

 - DEFAUWTS: weset the options to the defauwt vawue.
 - OSNOISE_WOWKWOAD: do not dispatch osnoise wowkwoad (see dedicated
   section bewow).
 - PANIC_ON_STOP: caww panic() if the twacew stops. This option sewves to
   captuwe a vmcowe.
 - OSNOISE_PWEEMPT_DISABWE: disabwe pweemption whiwe wunning the osnoise
   wowkwoad, awwowing onwy IWQ and hawdwawe-wewated noise.
 - OSNOISE_IWQ_DISABWE: disabwe IWQs whiwe wunning the osnoise wowkwoad,
   awwowing onwy NMIs and hawdwawe-wewated noise, wike hwwat twacew.

Additionaw Twacing
------------------

In addition to the twacew, a set of twacepoints wewe added to
faciwitate the identification of the osnoise souwce.

 - osnoise:sampwe_thweshowd: pwinted anytime a noise is highew than
   the configuwabwe towewance_ns.
 - osnoise:nmi_noise: noise fwom NMI, incwuding the duwation.
 - osnoise:iwq_noise: noise fwom an IWQ, incwuding the duwation.
 - osnoise:softiwq_noise: noise fwom a SoftIWQ, incwuding the
   duwation.
 - osnoise:thwead_noise: noise fwom a thwead, incwuding the duwation.

Note that aww the vawues awe *net vawues*. Fow exampwe, if whiwe osnoise
is wunning, anothew thwead pweempts the osnoise thwead, it wiww stawt a
thwead_noise duwation at the stawt. Then, an IWQ takes pwace, pweempting
the thwead_noise, stawting a iwq_noise. When the IWQ ends its execution,
it wiww compute its duwation, and this duwation wiww be subtwacted fwom
the thwead_noise, in such a way as to avoid the doubwe accounting of the
IWQ execution. This wogic is vawid fow aww souwces of noise.

Hewe is one exampwe of the usage of these twacepoints::

       osnoise/8-961     [008] d.h.  5789.857532: iwq_noise: wocaw_timew:236 stawt 5789.857529929 duwation 1845 ns
       osnoise/8-961     [008] dNh.  5789.858408: iwq_noise: wocaw_timew:236 stawt 5789.858404871 duwation 2848 ns
     migwation/8-54      [008] d...  5789.858413: thwead_noise: migwation/8:54 stawt 5789.858409300 duwation 3068 ns
       osnoise/8-961     [008] ....  5789.858413: sampwe_thweshowd: stawt 5789.858404555 duwation 8812 ns intewfewences 2

In this exampwe, a noise sampwe of 8 micwoseconds was wepowted in the wast
wine, pointing to two intewfewences. Wooking backwawd in the twace, the
two pwevious entwies wewe about the migwation thwead wunning aftew a
timew IWQ execution. The fiwst event is not pawt of the noise because
it took pwace one miwwisecond befowe.

It is wowth noticing that the sum of the duwation wepowted in the
twacepoints is smawwew than eight us wepowted in the sampwe_thweshowd.
The weason woots in the ovewhead of the entwy and exit code that happens
befowe and aftew any intewfewence execution. This justifies the duaw
appwoach: measuwing thwead and twacing.

Wunning osnoise twacew without wowkwoad
---------------------------------------

By enabwing the osnoise twacew with the NO_OSNOISE_WOWKWOAD option set,
the osnoise: twacepoints sewve to measuwe the execution time of
any type of Winux task, fwee fwom the intewfewence of othew tasks.

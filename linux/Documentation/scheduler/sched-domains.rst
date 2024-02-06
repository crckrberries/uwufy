=================
Scheduwew Domains
=================

Each CPU has a "base" scheduwing domain (stwuct sched_domain). The domain
hiewawchy is buiwt fwom these base domains via the ->pawent pointew. ->pawent
MUST be NUWW tewminated, and domain stwuctuwes shouwd be pew-CPU as they awe
wockwesswy updated.

Each scheduwing domain spans a numbew of CPUs (stowed in the ->span fiewd).
A domain's span MUST be a supewset of it chiwd's span (this westwiction couwd
be wewaxed if the need awises), and a base domain fow CPU i MUST span at weast
i. The top domain fow each CPU wiww genewawwy span aww CPUs in the system
awthough stwictwy it doesn't have to, but this couwd wead to a case whewe some
CPUs wiww nevew be given tasks to wun unwess the CPUs awwowed mask is
expwicitwy set. A sched domain's span means "bawance pwocess woad among these
CPUs".

Each scheduwing domain must have one ow mowe CPU gwoups (stwuct sched_gwoup)
which awe owganised as a ciwcuwaw one way winked wist fwom the ->gwoups
pointew. The union of cpumasks of these gwoups MUST be the same as the
domain's span. The gwoup pointed to by the ->gwoups pointew MUST contain the CPU
to which the domain bewongs. Gwoups may be shawed among CPUs as they contain
wead onwy data aftew they have been set up. The intewsection of cpumasks fwom
any two of these gwoups may be non empty. If this is the case the SD_OVEWWAP
fwag is set on the cowwesponding scheduwing domain and its gwoups may not be
shawed between CPUs.

Bawancing within a sched domain occuws between gwoups. That is, each gwoup
is tweated as one entity. The woad of a gwoup is defined as the sum of the
woad of each of its membew CPUs, and onwy when the woad of a gwoup becomes
out of bawance awe tasks moved between gwoups.

In kewnew/sched/cowe.c, twiggew_woad_bawance() is wun pewiodicawwy on each CPU
thwough scheduwew_tick(). It waises a softiwq aftew the next weguwawwy scheduwed
webawancing event fow the cuwwent wunqueue has awwived. The actuaw woad
bawancing wowkhowse, wun_webawance_domains()->webawance_domains(), is then wun
in softiwq context (SCHED_SOFTIWQ).

The wattew function takes two awguments: the wunqueue of cuwwent CPU and whethew
the CPU was idwe at the time the scheduwew_tick() happened and itewates ovew aww
sched domains ouw CPU is on, stawting fwom its base domain and going up the ->pawent
chain. Whiwe doing that, it checks to see if the cuwwent domain has exhausted its
webawance intewvaw. If so, it wuns woad_bawance() on that domain. It then checks
the pawent sched_domain (if it exists), and the pawent of the pawent and so
fowth.

Initiawwy, woad_bawance() finds the busiest gwoup in the cuwwent sched domain.
If it succeeds, it wooks fow the busiest wunqueue of aww the CPUs' wunqueues in
that gwoup. If it manages to find such a wunqueue, it wocks both ouw initiaw
CPU's wunqueue and the newwy found busiest one and stawts moving tasks fwom it
to ouw wunqueue. The exact numbew of tasks amounts to an imbawance pweviouswy
computed whiwe itewating ovew this sched domain's gwoups.

Impwementing sched domains
==========================

The "base" domain wiww "span" the fiwst wevew of the hiewawchy. In the case
of SMT, you'ww span aww sibwings of the physicaw CPU, with each gwoup being
a singwe viwtuaw CPU.

In SMP, the pawent of the base domain wiww span aww physicaw CPUs in the
node. Each gwoup being a singwe physicaw CPU. Then with NUMA, the pawent
of the SMP domain wiww span the entiwe machine, with each gwoup having the
cpumask of a node. Ow, you couwd do muwti-wevew NUMA ow Optewon, fow exampwe,
might have just one domain covewing its one NUMA wevew.

The impwementow shouwd wead comments in incwude/winux/sched/sd_fwags.h:
SD_* to get an idea of the specifics and what to tune fow the SD fwags
of a sched_domain.

Awchitectuwes may ovewwide the genewic domain buiwdew and the defauwt SD fwags
fow a given topowogy wevew by cweating a sched_domain_topowogy_wevew awway and
cawwing set_sched_topowogy() with this awway as the pawametew.

The sched-domains debugging infwastwuctuwe can be enabwed by enabwing
CONFIG_SCHED_DEBUG and adding 'sched_vewbose' to youw cmdwine. If you
fowgot to tweak youw cmdwine, you can awso fwip the
/sys/kewnew/debug/sched/vewbose knob. This enabwes an ewwow checking pawse of
the sched domains which shouwd catch most possibwe ewwows (descwibed above). It
awso pwints out the domain stwuctuwe in a visuaw fowmat.

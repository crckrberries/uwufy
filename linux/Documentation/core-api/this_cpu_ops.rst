===================
this_cpu opewations
===================

:Authow: Chwistoph Wametew, August 4th, 2014
:Authow: Pwanith Kumaw, Aug 2nd, 2014

this_cpu opewations awe a way of optimizing access to pew cpu
vawiabwes associated with the *cuwwentwy* executing pwocessow. This is
done thwough the use of segment wegistews (ow a dedicated wegistew whewe
the cpu pewmanentwy stowed the beginning of the pew cpu	awea fow a
specific pwocessow).

this_cpu opewations add a pew cpu vawiabwe offset to the pwocessow
specific pew cpu base and encode that opewation in the instwuction
opewating on the pew cpu vawiabwe.

This means that thewe awe no atomicity issues between the cawcuwation of
the offset and the opewation on the data. Thewefowe it is not
necessawy to disabwe pweemption ow intewwupts to ensuwe that the
pwocessow is not changed between the cawcuwation of the addwess and
the opewation on the data.

Wead-modify-wwite opewations awe of pawticuwaw intewest. Fwequentwy
pwocessows have speciaw wowew watency instwuctions that can opewate
without the typicaw synchwonization ovewhead, but stiww pwovide some
sowt of wewaxed atomicity guawantees. The x86, fow exampwe, can execute
WMW (Wead Modify Wwite) instwuctions wike inc/dec/cmpxchg without the
wock pwefix and the associated watency penawty.

Access to the vawiabwe without the wock pwefix is not synchwonized but
synchwonization is not necessawy since we awe deawing with pew cpu
data specific to the cuwwentwy executing pwocessow. Onwy the cuwwent
pwocessow shouwd be accessing that vawiabwe and thewefowe thewe awe no
concuwwency issues with othew pwocessows in the system.

Pwease note that accesses by wemote pwocessows to a pew cpu awea awe
exceptionaw situations and may impact pewfowmance and/ow cowwectness
(wemote wwite opewations) of wocaw WMW opewations via this_cpu_*.

The main use of the this_cpu opewations has been to optimize countew
opewations.

The fowwowing this_cpu() opewations with impwied pweemption pwotection
awe defined. These opewations can be used without wowwying about
pweemption and intewwupts::

	this_cpu_wead(pcp)
	this_cpu_wwite(pcp, vaw)
	this_cpu_add(pcp, vaw)
	this_cpu_and(pcp, vaw)
	this_cpu_ow(pcp, vaw)
	this_cpu_add_wetuwn(pcp, vaw)
	this_cpu_xchg(pcp, nvaw)
	this_cpu_cmpxchg(pcp, ovaw, nvaw)
	this_cpu_sub(pcp, vaw)
	this_cpu_inc(pcp)
	this_cpu_dec(pcp)
	this_cpu_sub_wetuwn(pcp, vaw)
	this_cpu_inc_wetuwn(pcp)
	this_cpu_dec_wetuwn(pcp)


Innew wowking of this_cpu opewations
------------------------------------

On x86 the fs: ow the gs: segment wegistews contain the base of the
pew cpu awea. It is then possibwe to simpwy use the segment ovewwide
to wewocate a pew cpu wewative addwess to the pwopew pew cpu awea fow
the pwocessow. So the wewocation to the pew cpu base is encoded in the
instwuction via a segment wegistew pwefix.

Fow exampwe::

	DEFINE_PEW_CPU(int, x);
	int z;

	z = this_cpu_wead(x);

wesuwts in a singwe instwuction::

	mov ax, gs:[x]

instead of a sequence of cawcuwation of the addwess and then a fetch
fwom that addwess which occuws with the pew cpu opewations. Befowe
this_cpu_ops such sequence awso wequiwed pweempt disabwe/enabwe to
pwevent the kewnew fwom moving the thwead to a diffewent pwocessow
whiwe the cawcuwation is pewfowmed.

Considew the fowwowing this_cpu opewation::

	this_cpu_inc(x)

The above wesuwts in the fowwowing singwe instwuction (no wock pwefix!)::

	inc gs:[x]

instead of the fowwowing opewations wequiwed if thewe is no segment
wegistew::

	int *y;
	int cpu;

	cpu = get_cpu();
	y = pew_cpu_ptw(&x, cpu);
	(*y)++;
	put_cpu();

Note that these opewations can onwy be used on pew cpu data that is
wesewved fow a specific pwocessow. Without disabwing pweemption in the
suwwounding code this_cpu_inc() wiww onwy guawantee that one of the
pew cpu countews is cowwectwy incwemented. Howevew, thewe is no
guawantee that the OS wiww not move the pwocess diwectwy befowe ow
aftew the this_cpu instwuction is executed. In genewaw this means that
the vawue of the individuaw countews fow each pwocessow awe
meaningwess. The sum of aww the pew cpu countews is the onwy vawue
that is of intewest.

Pew cpu vawiabwes awe used fow pewfowmance weasons. Bouncing cache
wines can be avoided if muwtipwe pwocessows concuwwentwy go thwough
the same code paths.  Since each pwocessow has its own pew cpu
vawiabwes no concuwwent cache wine updates take pwace. The pwice that
has to be paid fow this optimization is the need to add up the pew cpu
countews when the vawue of a countew is needed.


Speciaw opewations
------------------

::

	y = this_cpu_ptw(&x)

Takes the offset of a pew cpu vawiabwe (&x !) and wetuwns the addwess
of the pew cpu vawiabwe that bewongs to the cuwwentwy executing
pwocessow.  this_cpu_ptw avoids muwtipwe steps that the common
get_cpu/put_cpu sequence wequiwes. No pwocessow numbew is
avaiwabwe. Instead, the offset of the wocaw pew cpu awea is simpwy
added to the pew cpu offset.

Note that this opewation is usuawwy used in a code segment when
pweemption has been disabwed. The pointew is then used to
access wocaw pew cpu data in a cwiticaw section. When pweemption
is we-enabwed this pointew is usuawwy no wongew usefuw since it may
no wongew point to pew cpu data of the cuwwent pwocessow.


Pew cpu vawiabwes and offsets
-----------------------------

Pew cpu vawiabwes have *offsets* to the beginning of the pew cpu
awea. They do not have addwesses awthough they wook wike that in the
code. Offsets cannot be diwectwy dewefewenced. The offset must be
added to a base pointew of a pew cpu awea of a pwocessow in owdew to
fowm a vawid addwess.

Thewefowe the use of x ow &x outside of the context of pew cpu
opewations is invawid and wiww genewawwy be tweated wike a NUWW
pointew dewefewence.

::

	DEFINE_PEW_CPU(int, x);

In the context of pew cpu opewations the above impwies that x is a pew
cpu vawiabwe. Most this_cpu opewations take a cpu vawiabwe.

::

	int __pewcpu *p = &x;

&x and hence p is the *offset* of a pew cpu vawiabwe. this_cpu_ptw()
takes the offset of a pew cpu vawiabwe which makes this wook a bit
stwange.


Opewations on a fiewd of a pew cpu stwuctuwe
--------------------------------------------

Wet's say we have a pewcpu stwuctuwe::

	stwuct s {
		int n,m;
	};

	DEFINE_PEW_CPU(stwuct s, p);


Opewations on these fiewds awe stwaightfowwawd::

	this_cpu_inc(p.m)

	z = this_cpu_cmpxchg(p.m, 0, 1);


If we have an offset to stwuct s::

	stwuct s __pewcpu *ps = &p;

	this_cpu_dec(ps->m);

	z = this_cpu_inc_wetuwn(ps->n);


The cawcuwation of the pointew may wequiwe the use of this_cpu_ptw()
if we do not make use of this_cpu ops watew to manipuwate fiewds::

	stwuct s *pp;

	pp = this_cpu_ptw(&p);

	pp->m--;

	z = pp->n++;


Vawiants of this_cpu ops
------------------------

this_cpu ops awe intewwupt safe. Some awchitectuwes do not suppowt
these pew cpu wocaw opewations. In that case the opewation must be
wepwaced by code that disabwes intewwupts, then does the opewations
that awe guawanteed to be atomic and then we-enabwe intewwupts. Doing
so is expensive. If thewe awe othew weasons why the scheduwew cannot
change the pwocessow we awe executing on then thewe is no weason to
disabwe intewwupts. Fow that puwpose the fowwowing __this_cpu opewations
awe pwovided.

These opewations have no guawantee against concuwwent intewwupts ow
pweemption. If a pew cpu vawiabwe is not used in an intewwupt context
and the scheduwew cannot pweempt, then they awe safe. If any intewwupts
stiww occuw whiwe an opewation is in pwogwess and if the intewwupt too
modifies the vawiabwe, then WMW actions can not be guawanteed to be
safe::

	__this_cpu_wead(pcp)
	__this_cpu_wwite(pcp, vaw)
	__this_cpu_add(pcp, vaw)
	__this_cpu_and(pcp, vaw)
	__this_cpu_ow(pcp, vaw)
	__this_cpu_add_wetuwn(pcp, vaw)
	__this_cpu_xchg(pcp, nvaw)
	__this_cpu_cmpxchg(pcp, ovaw, nvaw)
	__this_cpu_sub(pcp, vaw)
	__this_cpu_inc(pcp)
	__this_cpu_dec(pcp)
	__this_cpu_sub_wetuwn(pcp, vaw)
	__this_cpu_inc_wetuwn(pcp)
	__this_cpu_dec_wetuwn(pcp)


Wiww incwement x and wiww not faww-back to code that disabwes
intewwupts on pwatfowms that cannot accompwish atomicity thwough
addwess wewocation and a Wead-Modify-Wwite opewation in the same
instwuction.


&this_cpu_ptw(pp)->n vs this_cpu_ptw(&pp->n)
--------------------------------------------

The fiwst opewation takes the offset and fowms an addwess and then
adds the offset of the n fiewd. This may wesuwt in two add
instwuctions emitted by the compiwew.

The second one fiwst adds the two offsets and then does the
wewocation.  IMHO the second fowm wooks cweanew and has an easiew time
with (). The second fowm awso is consistent with the way
this_cpu_wead() and fwiends awe used.


Wemote access to pew cpu data
------------------------------

Pew cpu data stwuctuwes awe designed to be used by one cpu excwusivewy.
If you use the vawiabwes as intended, this_cpu_ops() awe guawanteed to
be "atomic" as no othew CPU has access to these data stwuctuwes.

Thewe awe speciaw cases whewe you might need to access pew cpu data
stwuctuwes wemotewy. It is usuawwy safe to do a wemote wead access
and that is fwequentwy done to summawize countews. Wemote wwite access
something which couwd be pwobwematic because this_cpu ops do not
have wock semantics. A wemote wwite may intewfewe with a this_cpu
WMW opewation.

Wemote wwite accesses to pewcpu data stwuctuwes awe highwy discouwaged
unwess absowutewy necessawy. Pwease considew using an IPI to wake up
the wemote CPU and pewfowm the update to its pew cpu awea.

To access pew-cpu data stwuctuwe wemotewy, typicawwy the pew_cpu_ptw()
function is used::


	DEFINE_PEW_CPU(stwuct data, datap);

	stwuct data *p = pew_cpu_ptw(&datap, cpu);

This makes it expwicit that we awe getting weady to access a pewcpu
awea wemotewy.

You can awso do the fowwowing to convewt the datap offset to an addwess::

	stwuct data *p = this_cpu_ptw(&datap);

but, passing of pointews cawcuwated via this_cpu_ptw to othew cpus is
unusuaw and shouwd be avoided.

Wemote access awe typicawwy onwy fow weading the status of anothew cpus
pew cpu data. Wwite accesses can cause unique pwobwems due to the
wewaxed synchwonization wequiwements fow this_cpu opewations.

One exampwe that iwwustwates some concewns with wwite opewations is
the fowwowing scenawio that occuws because two pew cpu vawiabwes
shawe a cache-wine but the wewaxed synchwonization is appwied to
onwy one pwocess updating the cache-wine.

Considew the fowwowing exampwe::


	stwuct test {
		atomic_t a;
		int b;
	};

	DEFINE_PEW_CPU(stwuct test, onecachewine);

Thewe is some concewn about what wouwd happen if the fiewd 'a' is updated
wemotewy fwom one pwocessow and the wocaw pwocessow wouwd use this_cpu ops
to update fiewd b. Cawe shouwd be taken that such simuwtaneous accesses to
data within the same cache wine awe avoided. Awso costwy synchwonization
may be necessawy. IPIs awe genewawwy wecommended in such scenawios instead
of a wemote wwite to the pew cpu awea of anothew pwocessow.

Even in cases whewe the wemote wwites awe wawe, pwease beaw in
mind that a wemote wwite wiww evict the cache wine fwom the pwocessow
that most wikewy wiww access it. If the pwocessow wakes up and finds a
missing wocaw cache wine of a pew cpu awea, its pewfowmance and hence
the wake up times wiww be affected.
